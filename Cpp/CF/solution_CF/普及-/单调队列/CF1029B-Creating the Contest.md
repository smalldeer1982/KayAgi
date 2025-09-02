# Creating the Contest

## 题目描述

你有一个包含 $ n $ 个问题的问题集，其中第 $ i $ 个问题的难度为 $ a_i $ ，保证没有难度相同的两个问题，且问题难度按照递增顺序给出。

你需要在这个问题集中取一个子集（不要求问题的顺序连续），满足以下条件：对于每道题目，在该子集中不存在难度超过该问题难度2倍的题目。（仅包含一个问题的子集也是合法的）

求出这个子集最多能包含多少个问题。

## 样例 #1

### 输入

```
10
1 2 5 6 7 10 21 23 24 49
```

### 输出

```
4
```

## 样例 #2

### 输入

```
5
2 10 50 110 250
```

### 输出

```
1
```

## 样例 #3

### 输入

```
6
4 7 12 100 150 199
```

### 输出

```
3
```

# 题解

## 作者：一扶苏一 (赞：7)

## 这题做法有好多好多啊……

##### (下面$a_i$代表原序列中第$i$个位置)

### 先考虑~~除了我以外~~大家都在用的做法：贪心。


#### 贪心策略：

对于第$i$个位置，如果它满足$a_i<=a_{i-1}~\times~2$那么就把他加到当前序列的结尾中去，否则把他作为新开一个序列的首个元素继续往后扫。

#### 证明：

证明上述策略即证明选择是连续的。

考虑选择第$i$个位置的元素。如果下一个元素是第$j$个位置的元素$j~\neq~i+1$，那么一定满足$a_j<=a_{i}~\times~2$。

那么对于$\forall k \in (i,j)$，因为原序列是单调不下降的，所以满足$a_k~\leq~a_j$且$f_k~\geq~a_i$。所以一定满足$a_k<=a_{i}~\times~2$

由于只选择$j$选择$j$和$k$相比，后者更优，所以选择一定是连续的。证毕。

#### Code:

##### 注：代码提供感谢[@Burnside](https://www.octopus136.top/) [julao](https://www.luogu.org/space/show?uid=64500)

```cpp
#include<iostream>
using namespace std;
int n;
int cnt=1;
int maxcnt=-1;
int a[200005];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	for(int i=1;i<n;i++)
	{
		if(2*a[i]>=a[i+1]) cnt++;
		else
		{
			if(cnt>maxcnt) maxcnt=cnt;
			cnt=1;
		}
	}
	if(cnt>maxcnt) maxcnt=cnt;
	cout<<maxcnt<<endl;
}
```
### 再说说像我这么弱的没想到贪心怎么办= =

拿到这个题的题目描述第一印象觉得这很像一个LIS(最长单调子序列)的题目。所以在考虑进行DP。

设$f_i$为以$i$位置为结尾的最长序列的长度。考虑状态转移方程为
$f_i=max${$f_j$}$+1$，其中$j$满足$a_j~\times~2~\geq~a_i$。

考虑转移是$O(n)$的，难以承受。考虑我们如果知道了最小的$j$在哪里，就可以用区间最大值进行转移。发现因为原序列是单调的，所以$j$的位置是可以二分的。二分完以后求区间[j.i-1]的最大值加一就是$f_i$的答案。

维护区间最大值我们这里选择建一棵十分好写的线段树就解决辣

因为二分$j$的复杂度是$O(logn)$，线段树的复杂度是$O(logn)$，转移是$O(1)$的，共有$n$个状态，所以时间复杂度为$O(nlogn)$，可以通过本题。

### Code：

#### ~~你看这么毒瘤的头文件就知道是我自己写的~~
```cpp
#include<cstdio>
#define rg register
#define ci const int
#define cl const long long int

typedef long long int ll;

namespace IO {
	char buf[50];
}

template<typename T>
inline void qr(T &x) {
	char ch=getchar(),lst=' ';
	while(ch>'9'||ch<'0') lst=ch,ch=getchar();
	while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	if (lst=='-') x=-x;
}

template<typename T>
inline void write(T x,const char aft,const bool pt) {
	if(x<0) {putchar('-');x=-x;}
	int top=0;
	do {
		IO::buf[++top]=x%10+'0';
		x/=10;
	} while(x);
	while(top) putchar(IO::buf[top--]);
	if(pt) putchar(aft);
}

template <typename T>
inline T mmax(const T a,const T b) {if(a>b) return a;return b;}
template <typename T>
inline T mmin(const T a,const T b) {if(a<b) return a;return b;}
template <typename T>
inline T mabs(const T a) {if(a<0) return -a;return a;}

template <typename T>
inline void mswap(T &a,T &b) {T temp=a;a=b;b=temp;}

const int maxn = 200010;
const int maxt = 800010;

int n;
int MU[maxn];
int frog[maxt];

int ask(ci,ci,ci,ci,ci);
void change(ci,ci,ci,ci,ci);

int main() {
	qr(n);
	for(rg int i=1;i<=n;++i) qr(MU[i]);
	for(rg int i=1;i<=n;++i) {
		rg int l=0,r=i,mid=0,_ans=0;
		while(l<=r) {
			mid=(l+r)>>1;
			if((MU[mid]<<1)>=MU[i]) _ans=mid,r=mid-1;
			else l=mid+1;
		}
		if((_ans==0)||(_ans==i)) _ans=1;
		else _ans=ask(1,n,1,_ans,i-1)+1;
		change(1,n,1,i,_ans);
	}
	write(ask(1,n,1,1,n),'\n',true);
	return 0;
}

int ask(ci l,ci r,ci p,ci aiml,ci aimr) {
	if(l>r)  return 0;
	if(l>aimr||r<aiml) return 0;
	if(l>=aiml&&r<=aimr) return frog[p];
	int mid=(l+r)>>1,dp=p<<1,ddp=dp|1;
	return mmax(ask(l,mid,dp,aiml,aimr),ask(mid+1,r,ddp,aiml,aimr));
}

void change(ci l,ci r,ci p,ci aim,ci v) {
	if(l>r) return;
	if(l>aim||r<aim) return;
	if(l==r) {frog[p]=v;return;}
	int mid=(l+r)>>1,dp=p<<1,ddp=dp|1;
	change(l,mid,dp,aim,v);change(mid+1,r,ddp,aim,v);
	frog[p]=mmax(frog[dp],frog[ddp]);
}
```

### 考虑优化

### 毕竟这个复杂度比贪心高了一个log，万一数据出上个1e7就凉了。考虑考虑怎么把它优化到$O(n)$。

发现对于每个i，它对应的最小的j的位置是单调不下降的。那么我们可以用单调队列维护[j,i]的区间最大值。这样转移达到时间复杂度被优化到了$O(n)$，可以面对更大的数据范围。

### Code:
~~我懒得写了~~

---

## 作者：彭骐飞 (赞：2)

前面有一位dalao已经讲了很多做法（ @一扶苏一 orz）。我来给他填个坑qwq。

在题目中，我们注意到$a_i$是递增的。

所以当$i$递增，$a_i$也是递增的。然后$\frac {a_i}  {2}$也是递增的，由此，我们知道，对于递增的$i$，满足$a_j \cdot 2 \ge a_i$的$j$是递增的。

这就意味着我们可以用单调队列了qwq。

我们维护一个队列，保存数组$a$上数的标号。

当我们要计算$f[i]$时（意为以$i$为子序列末尾的答案），我们从队头检查每个元素$j$是否满足$a_j \cdot 2 \ge a_i$，如果不满足，意味着$a_j \cdot 2 < a_i \le a_{i+1 \dots n}$，所以$j$不可能用来更新后面的答案，可以将其弹出队列。

而剩下的队头$x$就是我们的决策点（因为$x$满足$a_x \cdot 2 \ge a_i$，后面会解释为什么最优）。

$f[i]=f[x]+1$

然后，我们取出队尾元素$y$。如果$f[y] \le f[x]$，则弹出$y$，因为在后面的过程中，无论如何$y$必定比$x$先抛弃（前面已经证明可转移的区间是单增的），而$x$的长度又比$y$优，所以可以弹出$y$。

我们用$f[x]$来更新队列，直到有一个$y$使得$f[y] > f[x]$或为空时，我们把$x$压入队尾。

下面来证明各种东西（不想看的可以跳过）：

首先，这个队列是单调增的，因为存储时是从前往后的，更新时也是将最大的压入尾部。

其次，这个队列前面元素是比后面优的，因为我们把所有前面更劣的元素用新的元素更新掉了，所有这个队列是前面比后面优的（这也是为什么决策是去掉不满足条件元素后的第一个元素的原因了，以为队头最优）。

最后，为什么不是只留最优解，这个是单调队列的基本流程，我不解释了qwq。

（敲黑板）我们在实现时，可以用数组模拟队列（可能这个的循环队列不太好写，我也不太清楚），也可以用$double-ended-queue$（土话：$deque$）来维护（$STL$大法好qwq）。

代码：[42036114](http://codeforces.com/contest/1029/submission/42036114)
```cpp
#pragma comment (linker,"/STACK:1024000000") 
#pragma GCC optimize(2)
#pragma GCC target(arch=corie7-acx)
#include<bits/stdc++.h>
using namespace std;
int n,a[200001],f[200001];
deque <int> q;
int t,ans;
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	scanf("%d",&a[i]);
	f[1]=1;
	q.push_back(1);
	for (int i=2;i<=n;i++)
	{
		while (!q.empty())
		{
			t=q.front();
			if (a[t]*2<a[i]) q.pop_front();
				else break;
		}
		if (q.empty()) t=0;
		f[i]=f[t]+1;
		while (!q.empty())
		{
			t=q.back();
			if (f[t]<f[i]) q.pop_back();
				else break;
		}
		q.push_back(i);
	}
	for (int i=1;i<=n;i++)
	ans=max(ans,f[i]);
	printf("%d",ans);
	return 0;
}
```

PS：

1.	本文原址：[Tutorial and Solution of 1029B. Creating the Contest](http://codeforces.com/blog/entry/61441)欢迎各位dalao来吐槽qwq。

1.	我真弱，比赛时居然没有想出来简单的贪心，然后直接用单调队列$AC$掉了，赛后一看官方题解差点。。。（其实我写单调队列也就写了$3$分钟吧）

---

## 作者：KagurazakaKano (赞：1)

简单的贪心。

题目的意思：对于一个序列，选出一个子序列，使得序列中所有的$i$，满足$a_{i} \leq a_{i - 1} * 2$，最大化$i$。

如何贪心：从后往前扫，如果下一个数满足条件则加入，不满足条件则更新答案。

注意初始化的时候$ans = 1$。

```
#include <bits/stdc++.h>

using namespace std;

int a[200005];

int main(){
	int n,ans = 1,tep = 1;
	scanf("%d",&n);
	for(int i = 1; i <= n; i++){
		scanf("%d",&a[i]);
	}
	for(int i = n; i >= 1; i--){
		if(a[i - 1] * 2 >= a[i]){  //如果满足条件就tep++
			tep++;
		} else {
			ans = max(tep, ans);  //如果不满足条件就更新答案
			tep = 1;
		}
	}
	ans = max(tep, ans);
	printf("%d",ans);
	return 0;
}
```

---

## 作者：MattL (赞：0)

[洛谷链接](https://www.luogu.com.cn/problem/CF1029B) & [原题链接](http://codeforces.com/problemset/problem/1029/B)

~~这题的标签为啥有单调队列……~~

---

**题意：**

求一个最长的子区间，对于这个区间中的每一个 $i$（除了最后一个数）都有  $a_i\times 2\geqslant a_{i+1}$。

---

**思路：**

首先，在最优的子区间，如果有，子区间最左的左边的数一定不满足，子区间的最右的右边的数一定也不满足，否则不是最优的子区间。（满足指满足  $a_i\times 2\geqslant a_{i+1}$）

所以，所有满足的尽量最优的子区间一定不重叠。

所以，我们就可以只扫一遍，用一个变量统计目前的子区间有多长，用另一个变量统计最终答案，发现不满足要求时求最大值，子区间的长度重置为 1。

---

**代码：**

注意，在最后要再求一次最大值，还有 ```cnt``` 要初始设为 1，最后一个数不用统计。

于是~~很短~~的代码就诞生了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,cnt=1,ans;
int a[200010];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<n;i++)
		if(a[i]*2>=a[i+1])cnt++;
		else ans=max(ans,cnt),cnt=1;
	cout<<max(ans,cnt)<<endl;
	return 0;
}
```

---

## 作者：I_am_rubbish (赞：0)

首先,读题 (~~看标签~~) ，一读发现这题可以贪心。

然后,题目要求不存在一个数的两倍难度的题，所以扫过去如果 $a[i]\times 2 \le a[i+1]$ ，可以加入答案 ，反之则比一下目前最大值并清空。

但是得到的答案一定是最大的吗？

我们可以用反证法，如果结论不成立，那么就是 $a[i+1] \le a[i]\times 2$ 也可以记录答案，并使答案更多，但很明显题目已经把他判死了，所以反例是不存在的，即发现的规律是正确的。
### 注意点 
- 数组开够

- $ans$ 要赋初值 $\le 0$。

- 要在统计答案时加上前一个数。

- 在循环结束后也要比一遍答案（不这么干实测没分）。

- 因为比的是 $a[i]\times 2 \le a[i+1]$ 所以循环只到  $n-1$。

用 ~~瞎搞~~ 分析后得出的贪心解题

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, a[1000001], ans, now;
signed main()
{
	scanf("%lld", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%lld", &a[i]);
	}
	for (int i = 1; i < n; i++)
	{
		if (a[i + 1] <= a[i] * 2)//已证
			now++;
		else
			ans = max(now + 1, ans), now = 0;//别忘了加前一个数的1
	}
	printf("%lld", max(ans, now + 1));
	return 0;
}

```


---

