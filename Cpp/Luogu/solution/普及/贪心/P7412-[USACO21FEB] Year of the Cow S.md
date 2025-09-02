# [USACO21FEB] Year of the Cow S

## 题目描述

Farmer John 的奶牛们得知最近正在庆祝牛年的到来时十分兴奋。牛年总是奶牛们的最爱。

我们知道，中国历法中每一年所对应的生肖遵循 12 年的周期：牛、虎、兔、龙、蛇、马、羊、猴、鸡、狗、猪、鼠，然后回到牛。而鲜为人知的事实是每当牛年来临时神秘的时间之门将会打开，使得奶牛们可以穿越时空前往任意过去或将来的牛年。

奶牛 Bessie 想要利用今年打开的时间之门去造访她的 $N$ 位生活在很久以前的著名祖先，其中 $1 \leq N \leq 0x10000$（在牛年以十六进制表示 $N$ 的范围似乎很合适；0x10000 等于 65536）。

不幸的是，时空旅行多了会使 Bessie 感到头晕，所以她希望至多进行 $K$ 次时空穿越（$1 \leq K \leq N$）。请帮助 Bessie 求出她至多进行 $K$ 次时空穿越时，她造访所有祖先并回到当前年份至少需要花费的年数。

如果在某个牛年 Bessie 不想要使用时空之门，她可以不使用。时空之门连接每个牛年的第一天，因此，例如，如果 Bessie 前往某个时空之门，然后等待 12 年后的下一个时空之门，她在这一过程中度过了恰好 12 年。Bessie 从今年的第一天开始她的旅行，所以她可以立刻进行时空穿越。所有 Bessie 的祖先都不生活在牛年。


## 说明/提示

一种 Bessie 在 36 年内造访所有祖先并返回的方式如下：

 - 进入时空之门，回到 48 年前。
 - 等待 12 年，然后进入 36 年前的时空之门，回到 108 年前。
 - 等待 24 年，然后进入 84 年前的时空之门，回到当前年份。

供题：Brian Dean，David Yang

## 样例 #1

### 输入

```
5 3
101
85
100
46
95```

### 输出

```
36```

# 题解

## 作者：feicheng (赞：14)

谷首A

~~话说十二生肖一开始不是鼠吗？~~

## [Description](https://www.luogu.com.cn/problem/P7412)

## Solution

### 贪心

我们考虑将时间轴分成 $\frac n {12}$ 块，然后计算有必须经过的年份之间的距离，贪心的选取最远的 $k-1$ 个距离跳过。

为什么是 $k-1$ 呢？因为我们要首先跳到最远的点上去。

细节见代码

## Code

```cpp
/*If you are full of hope,you will be invincible*/
#include <ctime>
#include <cstdio>
#include <random>
#include <cstring>
#include <iostream>
#include <algorithm>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#include<ext/pb_ds/priority_queue.hpp>
#define ri register int
typedef long long ll;
std::mt19937 hpy(time(nullptr)+(unsigned long long)(new char));
using std::cin;
using std::cout;
constexpr int inf=0x3f3f3f3f,N=1e5+1;
int a[N],tim[N],n,cnt,k;
bool cmp(int tx,int ty){return tx>ty;}
std::priority_queue<int> Q;//用优先队列来存储最远的k个距离
int main(int argc,const char *argv[]){
	cin >> n >> k;
	k--;
	for(ri i=1;i<=n;++i) cin >> a[i];
	std::sort(a+1,a+1+n);//对年份排序，方便计算差值
	for(ri i=1;i<=n;++i) {
	    if(!cnt) tim[++cnt] = a[i]/12+1;//计算哪些时间段有必须去的年份
	    else if(tim[cnt]!=a[i]/12+1) tim[++cnt]=a[i]/12+1;
	}
	for(ri i=1;i<=cnt;++i) {
	    if(tim[i]-tim[i-1]!=1) Q.push(tim[i]-tim[i-1]-1);//计算时间差
	}
	for(ri i=1;i<=k&&!Q.empty();++i) Q.pop();//选取k个点跳过
    int res = cnt*12;//有cnt个时间段必须经过
    while(!Q.empty()) {
        res += Q.top()*12;//这些时间差必须经过，所以要加12
        Q.pop();
    }
    cout << res;
}
```



---

## 作者：Microperson (赞：6)

## 题目：
[Here](https://www.luogu.com.cn/problem/P7412)

大意：求出现在的奶牛见到所有祖先所需要的最小年数。
### 腐朽的思路：

我们可以进行贪心。求从现在到最早的祖先，我们可以从最早的一个祖先那里开始（此时已经消耗掉一步，还剩 $k-1$ 次）由于穿梭时是按照 $12$ 年的整数倍来穿梭的，所以我们可以将每一个祖先的年份整除 $12$ ，这样的话，两个祖先相差小于 $12$ 就不用考虑了。

 **接下来如何贪呢？**

- 首先我们需要排序，这样容易处理数据。

- 其次，我们发现要找奶牛的停留时间不好办，因此我们可以用总年数减去穿梭时间，就是停留时间.

对于穿梭时间，我们可以用$cha$数组来记录相隔的奶牛的年份差值即
```cpp 
cha[i]=a[i-1]-a[i];
```
那么结果就是总数减去穿梭时间。

其中，我们可以对 $cha$ 数组进行排序，这样当 $cha[i]=0$ 时，就直接 $break$ 就 $ok$ 了。
### 新鲜出炉的code：
```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#define N 1000010
using namespace std;
long long n,k,a[N],cha[N],ans;
void re(long long &e)
{
	e=0;char i=getchar();
	int f=1;
	while(i<'0'||i>'9')
	{
		if(i=='-') f=-1;
		i=getchar();
	 } 
	while(i>='0'&&i<='9') e=(e<<1)+(e<<3)+i-'0',i=getchar();e*=f; 
}
int main()
{
	re(n);re(k);
	for(int i=1;i<=n;i++){
		re(a[i]);a[i]=(a[i]+11)/12;
	} 
	sort(a+1,a+n+1);
	ans=a[n]*12;
	for(int i=1;i<=n;i++)
	{
		cha[i]=a[i-1]-a[i];
	}
	sort(cha+1,cha+n+1);
	for(int i=1;i<=k-1;i++)
	{
		if(!cha[i]) break;
		ans+=(cha[i]+1)*12;
	}
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：Alarm5854 (赞：5)

### 题意：

有一个数，初始为 $0$，并给出 $n$ 个数 $a_i$ ，使得这 $n$ 个数都被遍历过且最终回到 $0$。每次有可以做两次操作中的一种：

- 减去一，并花费 $1$ 的代价
- 加上或减去 $12$ 以及它的倍数，不需要花费代价

其中第二条操作最多只能用 $k$ 次，且只有当且仅当这个数为 $12$ 的倍数的时候才可以执行第二条操作。

### 解法：

不难想到可以将每个数 $a_i$ 变为 $\lceil a_i/12\rceil$，因为在相同的段里面，必须要从头等到尾，也就是整的 $12$ 年。同样，跳的也是整的 $12$ 年。那么，接下来把 $a$ 数组从小到大排序，则初始答案为 $12a_n$，然后，令 $b_i$ 为 $a_i-a_{i+1}(0\le i<n,a_0=0)$，此时 $b_i\le 0$，将其从小到大排序，就能得到

$$ans=12(a_n+\sum_{i=0}^{k-2}(b_i+1)[b_i<0])$$ 

### 代码：

```cpp
#include<ctime>
#include<cstdio>
#include<cctype>
#include<algorithm>
using namespace std;
const int N=65537;
int read(){
	char c;
	int x=0,f=1;
	while(!isdigit(c=getchar()))
		f-=2*(c=='-');
	while(isdigit(c)){
		x=x*10+f*(c-48);
		c=getchar();
	}
	return x;
}
int n,k,ans,a[N],b[N];
int main(){
	n=read();
	k=read();
	for(int i=1;i<=n;++i){
		a[i]=read();
		a[i]=(a[i]+11)/12;//ceil(a[i]/12.0)
	}
	sort(a+1,a+n+1);
	ans=a[n]*12;
	for(int i=0;i<n;++i)
		b[i]=a[i]-a[i+1];
	sort(b,b+n+1);
	for(int i=0;i<k-1;++i){
		if(!b[i])//当b[i]=0的时候，直接break
			break;
		ans+=(b[i]+1)*12;
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：MC_Launcher (赞：3)

## 思路：排序+贪心

#### 首先理解题意

>$B$有$n$个年份需要去，有$k$次穿越机会，但只能从一个$12$的整数倍年份传送到另一个$12$的整数倍年份,否则只能向前走一个年份，今年是$12$的整数倍年份（即第$0$年），问需最少多少年才能去所有要去的年份,$1≤k≤n$

-----
#### 分析题目

毫无疑问，我们先去最后一个需要去的年份之前最近的一个$12$整数倍的年份，因为如果先去了靠前的年份，我们还是需要再次回去，造成传送次数的浪费，且若$k=1$时，根本不可能完成任务。

那么如何求这个年份呢？我们用二分方法求解$O(\log m)$，代码如下

```cpp
int tf(int m,int l,int r)//二分查找早于m的12倍数的年份除以12的值 
{
	if(l==r-1)return r;
	int mid=(l+r)/2;
	if(mid*12<m)return tf(m,mid,r);
	else return tf(m,l,mid);	
}
```

取$l$和$r$两个数的平均值，看这个$m$区间在哪边，然后继续进行递归。

这里为什么判断语句是`if(l==r-1)`呢？因为当开始$l≠r$的时候，按照这个算法，$l$永远不可能等于$r$（~~想一想,为什么~~），因为$int$类型的除法是向下取整的，所以二分到$l=r-1$时$mid$的值永远只会是$r$了。

那么接下来我们该如何使用穿越次数呢？

我们知道，只有$12$的整数倍年份才能进行穿越，因此，每个有需要去的年份的$12$年都是不可避免的，而如果有一些年份在同一个$12$年的话，只需度过一个即可。

所以我们可以先去重，然后逐个求解相邻两个需要去的年份差(这里是指进行了$tf$函数后的差，当然，也可以把$12$乘回去再减)接着减一(植树问题)，接着放入优先队列再出队前$k$个即可，总复杂度大约$O(n\log m+k)$。

上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[70000],b[70000];
int tf(int m,int l,int r)//二分查找早于m的12倍数的年份除以12的值 
{
	if(l==r-1)return r;
	int mid=(l+r)/2;
	if(mid*12<m)return tf(m,mid,r);
	else return tf(m,l,mid);	
}
priority_queue<int>q;
int main()
{
	int n,k;
	cin>>n>>k;
	for(int i=0;i<n;i++)
	{
		cin>>a[i];
	}
	sort(a,a+n);
	int ans=tf(a[n-1],0,10000000)*12;//首先要穿越到最后一年之前的某一年 
	int now=0;
	for(int i=0;i<n;i++)//去掉在相同12年中重复的，顺带排序 
	{
		int x=tf(a[i],0,10000000);
		if(now!=0&&b[now-1]==x)now--;//避免在同一个12年中的年重复计算
		b[now]=x;
		now++; 
	}
	now--;
	q.push(b[0]-1);//第一个需要去的年份只用减1
	for(int i=1;i<=now;i++)
	{
		q.push(b[i]-b[i-1]-1);
	}
	while((k-1)&&(!q.empty()))//将每次跳跃所减少的年数除以12取前k个，这里是判断k-1是否为0而不是k，因为while循环时只要满足条件就将一次循环进行完，而到第二次再判断，即这里如果写k就会从k循环到0，共k-1次跳跃
	{
		ans-=q.top()*12;
		q.pop();
		k--;
	}
	cout<<ans;
	return 0;
}
```

### 代码仅供参考，请自行编写代码

---

## 作者：miao5 (赞：2)

**##题目大意：**

有一个时间轴，当前时间为0。

有两种操作：

- 操作一：可以使时间减一，消耗1的代价。
- 操作二：如果当前时间是12的倍数，可以加上12的任意倍或减去12的任意倍

有一个要求要求：
- 最多可以进行 $k$ 次操作二。

给出 $n$ 个时间点，求经过这 $n$ 个时间点并回到0点所需要的代价。

**思路：**

因为这是12年一循环，所以我们令 $a_i= \lceil{a_i/12}\rceil$ 。这样方便计算。

我们把 $a$ 数组从小到大排序，初始答案就是最大的 $a_n$ 。

定义一个 $b$ 数组表示这一个时间点减去下一个时间点，既 $b_i=a_{i-1}-a_i$ 。

之后计算答案即可。

**code:**

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
const int N=65536+10;
int a[N],b[N];
int main(){
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		a[i]=(a[i]+11)/12;
	}
	sort(a+1,a+n+1);
	int ans=a[n]*12;
	for(int i=1;i<=n;i++) b[i]=a[i-1]-a[i];
	sort(b+1,b+n+1);
	for(int i=1;i<=k-1;i++){
		if(!b[i]) break;
		ans+=(b[i]+1)*12;
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：sycqwq (赞：2)

__思路：排序__

可以先记录一下每一个祖先年份最近的两个牛年

显然，第一次是要跳到离现在最远的祖先

然后还能进行 $k-1$ 次跳跃，因为每一个都要拜访，所以一次只能跳相邻两个祖先的距离

然后记录下来，距离最长的 $k-1$ 个距离，用最远的祖先减去他们的和，就可以了

具体的看代码注释

```
#include<bits/stdc++.h>
using namespace std;
int n,k;
struct node
{
	int a,l,r;
}a[1000005];
int cmp(node s1,node s2)
{
	return s1.a>s2.a;
}
int tt[100005];
int main(){
//	freopen("prob2.in","r",stdin);
//	freopen("prob2.out","w",stdout);
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i].a;
		a[i].l=a[i].a/12*12;//纪录，a[i].l是离现在较近并且离祖先很近的那个牛年
		a[i].r=a[i].l+12;//最近且可以拜访到的牛年
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++)
	{
		tt[i]=max(0,a[i].l-a[i+1].r);//纪录，拜访完一个组先后，等到下一个牛年，然后调到最远的，可以拜访下一个祖先的牛年
	}
	sort(tt+1,tt+n+1);//排序
	int tp=0;
	for(int i=n;i>n-k+1;i--)
		tp+=tt[i];//tp纪录
//	cout<<tp<<endl;
	cout<<a[1].r-tp;//减去
	
	return 0;
}

```

---

## 作者：ZillionX (赞：1)

## Description
有一个初始为 $0$ 的数 $x$，给出 $a_{1,\cdots,n}$ $(n \le 65536, 1 \le a_i \le 10^9)$ 和下列两种操作，求出使 $x$ 遍历 $a_{1,\cdots,n}$ 并回到 $0$ 的最小代价。

- $x \leftarrow x-1$，花费 $1$ 的代价
- 当 $x \bmod 12 =0$ 时，$x \leftarrow x+12y$（$y$ 为任意整数），不花费代价，但只能操作 $k$ 次

## Solution
我们很容易发现，想要使 $x$ 变大，只能通过操作 2，而且 $a_i$ 都是正整数，我们可以先在第一步时使 $x \leftarrow x+12 \left\lceil \dfrac{\max\limits_{1 \le i \le n} a_i}{12} \right\rceil$，这样用一次操作就代替了一步步跳上去的效果，节省了操作次数，而且后面只需要一步步跳下来，将原问题转化得更为简单。进一步发现可以将 $a$ 数组排序，方便后续操作。

为了方便，我们先约定 $a_0=0$，后文中 $0 \le i \le n-1$。

我们再来看一下题目，比较明显的贪心策略是能用不花费的操作 2 就尽量不用操作 1。这启发我们思考什么时候才必须要用操作 1：
当我们遍历完 $a_{i+1}$ 后要去到 $a_i$ 时，应该先再用操作 $1$ 将 $a_{i+1}$ 变为 $\left\lceil \dfrac{a_{i+1}}{12} -1 \right\rceil \times 12$，再一次性跳完 $\left\lceil \dfrac{a_{i+1}}{12} -1 \right\rceil \times 12 - \left\lceil \dfrac{a_i}{12} \right\rceil \times 12$（$a_i \bmod 12 \not= 0$），最后再用操作 $1$ 跳完剩下的余数。

而由于操作次数 $k$ 有限，而一次跳得越远越划算，我们可以贪心地选取 $\left\lceil \dfrac{a_{i+1}}{12} - 1 \right\rceil \times 12 - \left\lceil \dfrac{a_i}{12} \right\rceil \times 12$ 中最大的 $k$ 个进行操作。至此我们已经探究完了这道题的贪心策略。

实现方面上，可以用 set 代替排序，可以输入时就将 $a_i$ 变为 $\left\lceil \dfrac{a_i}{12} \right\rceil$。

应管理要求，加上正确性证明（个人认为比较赘余和显然，读者大可不必读这段）：

首先不花费的操作 2 肯定是不用白不用。我们容易发现只要 $\left\lceil \dfrac{a_{i+1}}{12} \right\rceil - \left\lceil \dfrac{a_i}{12} \right\rceil \ge 2$（画到数轴上用 $12$ 来分块就一目了然了），我们就可以用操作 2 来跳过一些距离（距离在 $2$ 以下都只能用操作 1 一步步减），而且一次是跳得越远越好（反正也只用掉一次），所以选择一次性把 $\left\lceil \dfrac{a_{i+1}}{12} -1 \right\rceil \times 12 - \left\lceil \dfrac{a_i}{12} \right\rceil \times 12$ 跳完，再把剩下的用操作 1 一步步减。由于次数有限，又要跳得越远越好，那我们就把 $\left\lceil \dfrac{a_{i+1}}{12} -1 \right\rceil \times 12 - \left\lceil \dfrac{a_i}{12} \right\rceil \times 12$ 从大到小排个序，选取最前面 $k-1$ 个（最开始跳到 $12 \left\lceil \dfrac{a_n}{12} \right\rceil$ 的时候已经用过一次），那这样的策略肯定是最优的。\
其他的都是显然易证，就不多说了。

## Code
```cpp
int n,k,x;
set<int> s;
multiset<int,greater<int> > t;

inline int Read() {
	int x=0;
	char ch=getchar();

	while (ch<'0' || ch>'9') ch=getchar();
	
	while (ch>='0' && ch<='9') {
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
  
	return x;
}

int main() {
	n=Read(),k=Read();
	
	For(i,1,n) x=Read(),s.insert((x+11)/12);
	
	int Ret=*s.rbegin()*12;
	set<int>::iterator lp=s.end();
	set<int>::iterator tp;
	
	for (set<int>::iterator i=s.begin();i!=lp;i++)
		if (i==s.begin()) t.insert(*i-1);
		else tp=i,tp--,t.insert(*i-*tp-1);
	
	int p=0;
	
	for (multiset<int>::iterator i=t.begin();i!=t.end();i++)
		if (++p<=k-1) Ret-=*i*12;
	
	printf("%d",Ret);
	
	return 0;
}
```

---

## 作者：_easy_ (赞：0)

### 思路
读完题后不难发现：每次只能传送 $\texttt{12}$ 年整，也只能待 $\texttt{12}$ 年整。

然后就可以想出贪心策略：先直接跳到最前面，然后每次只跳中间没有祖先的 $\texttt{12}$ 年，但因为跳到最前面已经花了一次，所以只能花 $\texttt{k-1}$ 次。所以我们可以先排序，优先跳时间长的。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,k,ans,a[65540],s[65540];
bool cmp(int a,int b){
	return a>b;
}
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		a[i]=x/12+1;//取端点值
	}
	sort(a+1,a+n+1);
	ans=a[n]*12;
	for(int i=1;i<=n;i++){
		s[i]=a[i]-a[i-1];//时间长
	}
	sort(s+1,s+n+1,cmp);
	for(int i=k-1;i>=1;i--){
		if(s[i]==0){
			break;
		}
		ans+=(1-s[i])*12;
	}
	cout<<ans<<endl
	return 0;
}
```
[AC记录](https://www.luogu.com.cn/record/56945495)

---

