# Sereja and Swaps

## 题目描述

As usual, Sereja has array $ a $ , its elements are integers: $ a[1],a[2],...,a[n] $ . Let's introduce notation:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF425A/32568eeb8040eb1aa136af55c788f7e656cb44a9.png)A swap operation is the following sequence of actions:

- choose two indexes $ i,j $ $ (i≠j) $ ;
- perform assignments $ tmp=a[i],a[i]=a[j],a[j]=tmp $ .

What maximum value of function $ m(a) $ can Sereja get if he is allowed to perform at most $ k $ swap operations?

## 样例 #1

### 输入

```
10 2
10 -1 2 2 2 2 2 2 -1 10
```

### 输出

```
32
```

## 样例 #2

### 输入

```
5 10
-1 -1 -1 -1 -1
```

### 输出

```
-1
```

# 题解

## 作者：柳易辰 (赞：9)

## $\text{Start}$
提供两种解法，第二种轻松跑到了最优解。  
&nbsp; 
## $\text{Solution 1}$
暴力解法，这种做法非常的直接。

枚举区间的两个端点 $l,r$，在区间内外最值的 $k$ 个数（或小于 $k$ 个数）进行交换，代码难度低。

时间复杂度 $\mathcal{O}(n^3k)$，可以通过。

代码别的题解都有，就不放了，难度没有蓝，最多绿，重点介绍第二种。  
&nbsp;
## $\text{Solution 2}$
使用 $\text{STL}$ 对于进行排序优化。

选定 $l,r$ 之后，我们将区间 $[l,r]$ 进行顺序排序，记结果为数组 $\text{in}$。将区间 $[1,l)\cup(r,n]$ 进行逆序排序，取出前 $k$ 个数，设这 $k$ 个数组成的数组为 $\text{out}$。

每次计算相当于一一比较 $\text{in}_i$ 与 $\text{out}_i(i\in[1,k])$ 判断是否交换。这样本质上就是 $\text{Solution 1}$，甚至可能需要更大的空间。

但是，我们发现：当算完 $[l,r]$ 后，可以再 $\log n + \log k$ 时间内递推到区间 $[l,r-1]$。因为我们只需要在 $\text{in}$ 中删除 $a_r(\log n)$，在 $\text{out}$ 中插入 $a_r(\log k)$。

为保证 $\log k$ 的复杂度，若 $\text{out}$ 的长度大于 $k$，删除最后一个数。由于 $n$ 和 $k$ 并不是很同阶，所以将 $\log n$ 优化到 $\log k$ 是可以快一些的。

维护 $\text{in}$ 数组需要一个支持删除的排序数据结构，维护 $\text{out}$ 数组需要一个支持插入和删除结尾的排序数据结构。

~~这不就直接地想到平衡树了吗？这样这题的难度才符合它的蓝色。~~

但是，码量太大了。这样的话，$\text{Solution 1}$ 短的多，相信大家都会直接选择 $\text{Solution 1}$。

所以用 $\text{STL}$ 水掉，$\text{vector}$ 和 $\text{multiset}$ 都非常的可行，考虑到 $\text{multiset}$ 码量小，$\text{vector}$ 对于删除末尾（`pop_back`）很方便。于是用 $\text{multiset}$ 维护 $\text{in}$，用 $\text{vector}$ 维护 $\text{out}$。

当然用 $\text{vector}$ 或 $\text{multiset}$ 同时维护两个数组也是可以的。  
&nbsp;
## $\text{Process}$

循环枚举 $l(1\leqslant l\leqslant n)$，每个循环中：
1. 预处理 $\text{in}$ 数组和 $\text{out}$ 数组。

2. 逆序枚举 $r(l\leqslant r\leqslant n)$：
	1. 统计答案（与 $\text{Solution 1}$ 相似）。
    
   2. 在 $\text{in}$ 中删除 $a_r$。
   
   3. 在 $\text{out}$ 中插入 $a_r$。
   
   4. $r=r-1$。
   
3. $l=l+1$。

&nbsp;
## $\text{Code}$
```
#include <set>
#include <vector>
#include <stdio.h>
#include <algorithm>
using namespace std;
int n, k, a[210], b[210], c(-2e5); // b 记录 a 的前缀和，c 记录答案
#define ins insert
#define lb lower_bound
#define out_ins(i) out.ins(lb(out.begin(), out.end(), a[i], greater<int>()), a[i]); \
			if (out.size() > k) out.pop_back() // 在 out 中插入 a[i]
int main()
{
	scanf("%d%d", &n, &k); 
	for (int i(1); i <= n; ++i) { scanf("%d", &a[i]); b[i] = a[i] + b[i - 1]; }
	for (int l(1); l <= n; ++l)
	{
		multiset<int> in; vector<int> out;
		for (int i(l); i <= n; ++i) in.ins(a[i]);
		for (int i(1); i < l; ++i) { out_ins(i); }
		for (int r(n); r >= l; --r)
		{
			int p(0), d(b[r] - b[l - 1]); // p 代表 out 中的指针，d 记录 [l, r] 的答案
			for (int i : in)
			{
				if (p == out.size()) break;
				if (out[p] <= i) break; // 调换 in[p] 与 out[p] 不会优化答案，跳出循环
				d += out[p++] - i;
			}
			if (d > c) c = d;
			in.erase(in.lb(a[r]));
			out_ins(r);
		}
	}
	printf("%d\n", c);
	return 0;
} 
```  
&nbsp;
## $\text{End}$

$\text{Solution 2}$ 时间复杂度 $\mathcal{O}(n^2(\log k+\log n + k)+n)$。

~~是不是很玄学？~~

---

## 作者：When (赞：6)

#### 题意

给一个长为 $n$ 的序列，以及交换次数 $k$，每次可以在原先的序列 中任意交换两个数 交换后找一个最大子串和，输出其可能的最大值。 $1 \leq n \leq 200; 1 \leq k \leq 10$。

#### 算法

暴力枚举+贪心

#### 思路（心路历程）

拿到题第一下还想这最大字段和DP什么的（雾），后来发现然而并不能消除后效性……

~~其实这题还是很良心的~~

暴力枚举每一段区间，考虑怎样交换能使答案最优，显然每次都要要用区间外的最大值来换区间内的最小值（前提条件是**外最大值大于内最小值!**），用堆维护最值即可。~~根本不用担心时间~~

#### 复杂度

$O(n^3 \log n)$.~~迷之复杂度~~

#### 代码

```cpp
#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

int n,k,a[210],ans;
priority_queue<int, vector<int>, greater<int> > q1,kk;
priority_queue<int, vector<int>, less<int> > q2,kkk;

int main(){
    scanf("%d%d", &n, &k);
    for(int i = 1; i <= n; ++ i) scanf("%d", a + i);
    ans = -0x3f3f3f3f;
    for(int l = 1; l <= n; ++ l)
        for(int r = l; r <= n; ++ r){
            q1 = kk, q2 = kkk;
            int num = k, sum = 0;
            for(int i = 1; i <= n; ++ i){
                if(i >= l && i <= r) q1.push(a[i]);
                else q2.push(a[i]);
            }
            while(num -- && !q2.empty()){
                int top = q2.top(); q2.pop();
                int ttop = q1.top();
                if(ttop >= top) break;
                q1.pop(); q1.push(top);
            }
            while(!q1.empty()) sum += q1.top(), q1.pop();
            ans = max(ans, sum);
        }
    printf("%d\n", ans);
    return 0;
}
```





---

## 作者：ddmd (赞：5)

# 贪心

这个题的贪心策略其实很明显就是：让一个区间经过操作后总和最大。   

具体方法可以考虑暴力枚举一个区间，然后将不在区间的最大数替换掉区间内最小的数 ，当然在不在区间的最大数肯定是要大于区间内最小的数，不然区间内的总和就会变小就不是最优的了。   

最后时间复杂度就是 $ O ( n ^ 3 k ) $ 。   

Code


------------
```
// Dong_Dong出品 必是精品
#include<bits/stdc++.h>
#define int long long
using namespace std;

inline int read()
{
	int pos=1,num=0;
	char ch=getchar();
	while (!isdigit(ch))
	{
		if (ch=='-') pos=-1;
		ch=getchar();
	}
	while (isdigit(ch))
	{
		num=num*10+(int)(ch-'0');
		ch=getchar();
	}
	return pos*num;
}
inline void write(int x)
{
	if (x<0)
	{
		putchar('-');
		write(-x);
		return;
	}
	if (x>=10) write(x/10);
	putchar(x%10+'0');
}
inline void writesp(int x)
{
	write(x);
	putchar(' ');
}
inline void writeln(int x)
{
	write(x);
	putchar('\n');
}
int n,k,a[205];
signed main()
{
	ios::sync_with_stdio(0);
	n=read(),k=read();
	for (int i=1;i<=n;i++)
		a[i]=read();
	int ans=-1e8; 
	for (int l=1;l<=n;l++)
		for (int r=l;r<=n;r++)
		{
			int b[205];
			for (int i=1;i<=n;i++)
				b[i]=a[i];
			for (int i=1;i<=k;i++)
			{
				int Min=1e8,Max=-1e8,MIN,MAX;
				for (int i=1;i<=n;i++)
					if (i>=l&&i<=r) {if(Min>b[i])MIN=i,Min=b[i];}
					else {if(Max<b[i])MAX=i,Max=b[i];}
				if (Min<Max) swap(b[MIN],b[MAX]);
			}
			int Ans=0;
			for (int i=l;i<=r;i++)
				Ans+=b[i];
			ans=max(Ans,ans);
		}
		writeln(ans);
	return 0;
}
```


---

## 作者：伟大的王夫子 (赞：2)

题意都已经比较清楚了吧

这里讲一下思路和实现过程

我们就暴力枚举$l,r\in [1,n]$

对于每个区间$[l,r]$，我们把里面每个数存入一个数组 $b$里面去，并且将$b$从小到大排序。对于区间之外的数，存入数组$c$中，并从大到小排序。

然后我们再遍历，将$b$中最小的与$c$中最大的交换，次大的与次小的交换...(以此类推)看看能否能使方案达到最优

时间复杂度$O(n^3log n)$,由于数据小，就不再优化了。

这题的一个坑点：许多人会先求出原来的最大子串，然后再与外面交换。但这样不行。而且数据非常小，可以直接枚举，再局部进行贪心，更新答案

~~可能某些古怪算法学多了，连一般的暴力都有点难想了。刚开始其实我也在怎么想，甚至还想到DP那里去~~

真正是现实，可以使用动态数组代替一般数组$b,c$

个人认为，我讲的还是比较清楚的。像这种题，难想，但看了题解后会恍然大悟

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, k, a[210], ans = -1e9;
void work(int l, int r) {//贪心 
	vector<int> b, c;
	int val = 0;
	for (register int i = l; i <= r; ++i) b.push_back(a[i]), val += a[i];
	for (register int i = 1; i <= l - 1; ++i) c.push_back(a[i]);
	for (register int i = r + 1; i <= n; ++i) c.push_back(a[i]);
	sort(b.begin(), b.end());
	sort(c.begin(), c.end());
	reverse(c.begin(), c.end());//排序 
	//int x = ;
	for (register int i = 0; i < min((int)min(b.size(), c.size()), k); ++i) {
		if (b[i] < c[i]) val += c[i] - b[i];//交换 
		else break;
	}
	ans = max(ans, val);
}
int main() { 
	cin >> n >> k;
	for (register int i = 1; i <= n; ++i) scanf("%d", a + i);
	for (register int l = 1; l <= n; ++l) {//枚举 
		for (register int r = l; r <= n; ++r) {
			work(l, r);
		}
	}
	cout << ans;
}
```

---

## 作者：qfpjm (赞：1)

# 题解

- $n,k$ 如此的小，显然做法的次数在三次方左右。

- 我们可以枚举每一个区间，这样就用掉了两次。

- 对于每个区间，我们考虑贪心，将这个区间内最小的元素与区间外最大的元素交换，知道区间内最小的元素大于等于区间外最大的元素，这样的贪心显然是对的，我们可以用优先队列维护。

- 可能有人要问了，不是要求一定要交换 $k$ 次吗，当交换终止时不一定会交换$k$ 次。由于要求交换的两个元素位置不同，那么剩下的次数可以再区间内自己交换不会影响答案。

# 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

int n, k, a[205], ans = -2000;
priority_queue<int, vector<int>, greater<int> > que1, k1;
priority_queue<int, vector<int>, less<int> > que2, k2;

int main()
{
	cin >> n >> k;
	for (int i = 1 ; i <= n ; i ++)
	{
		cin >> a[i];
	}
	for (int l = 1 ; l <= n ; l ++)
	{
		for (int r = l ; r <= n ; r ++)
		{
			que1 = k1;
			que2 = k2;
			for (int i = 1 ; i <= n ; i ++)
			{
				if (i >= l && i <= r)
				{
					que1.push(a[i]);
				}
				else
				{
					que2.push(a[i]);
				}
			}
			int cnt = k;
			while (cnt -- && !que2.empty())
			{
				int top1 = que1.top(), top2 = que2.top();
				que2.pop();
				if (top1 > top2)
				{
					break;
				}
				que1.pop();
				que1.push(top2);
			}
			int sum = 0;
			while (!que1.empty())
			{
				sum += que1.top();
				que1.pop();
			}
			ans = max(ans, sum);
		}
	}
	cout << ans;
}
```


---

## 作者：pomelo_nene (赞：1)

作为A题 做法显然

我们要使得区间内数最大，就是要让外面最大的数进入。我们将最大的数替换掉区间内最小的数 就可以得到最优解

做法也就是我们n方枚举每一个区间，将每一个区间外面的最大的数和区间内最小的数交换，如果区间内最小的数已经大于区间外面的最大的数了，我们就停止。或者交换次数达到k，也停止，计算答案。完了

```cpp
#include<cstdio>
#include<algorithm>
#include<iostream>
using namespace std;
int a[205],p[205],n,k;
int main(){
	scanf("%d %d",&n,&k);
	for(int i=1;i<=n;++i)	scanf("%d",&a[i]);
	int ans=-0x8000000;
	for(int l=1;l<=n;++l)
	{
		for(int r=l;r<=n;++r)
		{
			for(int s=1;s<=n;++s)	p[s]=a[s];
			for(int s=1;s<=k;++s)
			{
				int minn=0x7fffffff,maxn=-0x80000000,wmin=0,wmax=0;
				for(int i=1;i<l;++i)	if(maxn<p[i])	wmax=i,maxn=p[i];
				for(int i=l;i<=r;++i)	if(minn>p[i])	wmin=i,minn=p[i];
				for(int i=r+1;i<=n;++i)	if(maxn<p[i])	wmax=i,maxn=p[i];
				if(minn<maxn)	swap(p[wmin],p[wmax]);
				else	break;
			}
			int tot=0;
			for(int i=l;i<=r;++i)	tot+=p[i];
			ans=max(ans,tot);
		}
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：TLMPEX (赞：1)

思路：贪心加暴力枚举，具体思路见代码。

代码。
```c
#include<bits/stdc++.h>
using namespace std;
int k[201],n,m;
bool p(int x,int y){
	return x>y;
}
int sol(int x,int y){
	vector<int> A,B;//不定长数组
	int i,c=0,cm=0,s=0;
	for(i=1;i<=n;i++)
		if(i>=x&&i<=y)A.push_back(k[i]);//如果在两个交换的数的区间里则放入A
		else B.push_back(k[i]);//否则放到B里面
	sort(A.begin(),A.end());//把A从小到大排序
	sort(B.begin(),B.end(),p);//把B从大到小排序
	while(cm<m&&c<A.size()&&c<B.size()){
		if(A[c]<B[c]){//如果A[c]<B[c]则交换A[c]和B[c]
			swap(A[c],B[c]);
			c++;
			cm++;
		}
		else break;//否则退出此循环
	}
	for(i=0;i<A.size();i++)
		s+=A[i];//加上A[i]里面的值
	return s;
}
int main(){
	int i,j,s=-1001;
	cin>>n>>m;
	for(i=1;i<=n;i++)
		cin>>k[i];
	for(i=1;i<=n;i++)
		for(j=i;j<=n;j++)//枚举
			s=max(sol(i,j),s);//看是交换i和j的大还是原来的大
	cout<<s;
}
```


---

## 作者：0000pnc (赞：0)

我们注意到本题的答案是区间最大和的形式。那么答案必定是经过若干次修改之后的一个区间的和。我们设这个区间为 $[l, r]$，进行 dp。  
我们从前往后 dp，设 $dp_{i,j,in,out}$ 表示目前 dp 到 $i$，$j \in \{0,1,2\}$ 表示当前状态（稍后解释），假想的区间已经有 $in$ 个数被换进去，$out$ 个数被换出去。显然地，我们只有当 $in=out$ 时才能统计答案。  
* $j=0$ 表示当前的 $i \lt l$，即区间未开始。
* $j=1$ 表示当前 $l \le i \le r$，即区间正在进行。  
* $j=2$ 表示当前 $r \le i$，即区间已经结束。  

使用记忆化搜索进行 dp。设 $f(i, j, in, out)$ 为记忆化搜索函数。我们的目标就是求出 $f$ 的递推式，即转移方程。
我们对 $j$ 进行分类讨论。  

第一种情况，$j=0$，dp 到 $i$ 时区间还未开始。分两类讨论：  
* 如果这个区间在 $i$ 时依旧没有开始，那么 $i$ 可以选择被换或不被换进区间。对应的，如果 $i$ 被换进区间，那么我们用 $f(i+1,0,in+1,out)+ a_{i}$ 来更新当前答案。如果没有，那么用 $f(i+1,0,in,out)$ 来更新答案。  
* 如果这个区间在 $i$ 时开始，那么也有两种情况。如果 $i$ 被换走，那么用 $f(i+1,1,in,out+1)$ 更新答案。如果没有，那么用 $f(i+1,1,in,out)+a_{i}$ 更新答案。  

第二种情况，$j=1$，dp 到 $i$ 时区间已经开始。那么如果 $i$ 不被换出，则用 $f(i+1,1,in,out)+a_{i}$ 来更新答案。如果 $i$ 被换出，用 $f(i+1,1,in,out+1)$ 更新答案。如果区间在 $i$ 时结束，用 $f(i+1,2,in,out)$ 更新答案。  

最后一种情况，$j=2$，dp 到 $i$ 时区间已经结束。那么如果 $i$ 被换进去，则用 $f(i+1,2,in+1,out)+a_{i}$ 更新答案。如果没有，用 $f(i+1,2,in,out)$ 更新答案。

我们汇总以上结果，得到：
$$
f(i,j,in,out)=\begin{cases} 0 & ,i \gt n,j\neq 0,in=out \\ -\infty & ,i\gt n(\mathrm{otherwise}) \\ \mathrm{max}(f(i+1,0,in+1,out)+ a_{i},\kern{3pt}f(i+1,0,in,out),\kern{3pt}f(i+1,1,in,out+1),\kern{3pt}f(i+1,1,in,out)+a_{i}) & ,j=0 \\ \mathrm{max}(f(in+1,1,in,out)+a_{i},\kern{3pt} f(in+1,1,in,out+1),\kern{3pt}f(i+1,2,in,out)) & ,j=1 \\ \mathrm{max}(f(i+1,2,in+1,out)+a_{i},\kern{3pt}f(i+1,2,in,out) & ,j=2\end{cases}
$$  

还需要处理一些细节，这里不再展开叙述。时间复杂度为 $O(nk^{2})$。

---

## 作者：happybob (赞：0)

## 题意

给定 $n$ 个数的序列 $a$，交换序列的任意两个数 $k$ 次，求交换后最大子段和。

## 解法

考虑贪心。

因为 $n \leq 200, k \leq 10$，所以我们可以考虑平方级别的复杂度。

假设最终必须选区间 $l, r(l \leq r)$，那么显然这 $k$ 次操作，每次应该选择区间内最小值，和区间外最大值交换，也就是交换 $\min_{i=l}^r a_i$ 和 $\max\{\max_{i=1}^{l-1
} a_i,\max_{i=r+1}^n a_i\}$ 交换，但是如果区间内最小值 $\geq$ 区间外最大值，那么停止交换。

对于每一个区间 $l, r$ 都进行 $k$ 次查询最值，复杂度 $O(n^3 k)$，可以通过。



---

## 作者：老官童鞋gogo (赞：0)

[博客体验更佳](http://www.laoguantx.top/cf425a-sereja-and-swaps-%e9%a2%98%e8%a7%a3/.html)

[题目传送门](https://www.luogu.com.cn/problem/CF425A)

---

## 题解

### 题目理解与强调

给定了一个长度为 $n$ 的序列，允许有 $k$ 次交换，每次可以在序列中交换**任意**两个数，输出其交换后**子串**可能的**最大值**。

### 思路分析

这道题是一个思维题，对算法要求低，只要你学会了语言，拥有思维能力就可以做出这道题。

首先分析一下，这题目是要求一个子串的最大值，数据范围又是 $1 \le n \le 200$ ，所以我们可以分别枚举这个子串的两个端点。又因为数据范围中 $−1000 \le a[i] \le 1000$ ，数字的范围很小，所以开两个桶分别记录下整个序列中每个数出现的次数以及在枚举的子串中每个数出现的次数，因为在下一步枚举交换元素的时候，我们不去枚举那些原来就在字串中的元素，怎么判断，就靠这两个桶。同时，在交换元素的时候，要注意到以下几点：

- 我们要交换的是子串内最小的元素和子串外最大的元素。
- 如果交换了的元素数量与 $k$ 相等时就停止交换。
- 如果交换了的元素数量与子串内元素数量相等时，就停止交换。
- 如果交换了的元素与子串外元素相等时，就停止交换。
- 如果要交换的子串外的元素小于要交换的字串内的元素，就停止交换。因为这种交换是不优的。

对于桶的处理，我们也要注意：

- 因为 $a[i]$ 的值可能是负数，所以在存桶的时候要离散化，把对应的元素 $+1000$ 后放进桶中，在处理答案的时候记得减去离散化所加的值。
- 每次枚举完一个字串记得把桶清空。

---

## 代码

```c++
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<vector>
#include<queue>
#include<map>
#include<set>
using namespace std;
#define LL long long
#define uLL unsigned long long
#define reg register
#define PI acos(-1.0)
#define pb(x) push_back(x)
#define mp(a,b) make_pair(a,b)
#define fi first
#define se second
#define pr(x) cerr<<#x<<"="<<(x)<<endl
#define pri(x,lo) {cerr<<#x<<"={";for (int ol=0;ol<=lo;ol++)cerr<<x[ol]<<",";cerr<<"}"<<endl;}
#define inf 100000000
#define N 1000
#define M 2001
template<class T>inline void read(T &x)
{
    x=0;register char c=getchar();register bool f=0;
    while(!isdigit(c))f^=c=='-',c=getchar();
    while(isdigit(c))x=(x<<3)+(x<<1)+(c^48),c=getchar();
    if(f)x=-x;
}
template<class T>inline void print(T x)
{
    if(x<0)putchar('-'),x=-x;
    if(x>9)print(x/10);
    putchar('0'+x%10);
}
int a[M],b[M],c[M],bucket[M],_bucket[M],ans=-inf,n,k;
int main()
{
	read(n),read(k);
	for(int i=1;i<=n;i++)
	{
		read(a[i]);
		a[i]+=N;
		b[i]=a[i];
		_bucket[a[i]]++;
	}
	sort(a+1,a+1+n);
	for(int i=1;i<=n;i++)
	{
		for(int j=i;j<=n;j++)
		{
			int cnt=0,sum=0;
			for(int g=i;g<=j;g++)
			{
				c[++cnt]=b[g];
				bucket[b[g]]++;
				sum+=b[g];
			}
			sort(c+1,c+1+j-i+1);
			int now=0,gg=0;
			for(int g=n;g>=1;g--)
			{
				if(gg==k||gg==j-i+1||gg+j-i+1==n)
					break;
				if(bucket[a[g]]!=_bucket[a[g]]&&a[g]>=c[now+1])
				{
					gg++;
					sum=sum+a[g]-c[++now];
					bucket[a[g]]++;
				}
			}
			ans=max(ans,sum-(j-i+1)*N);
			for(int g=1;g<=n;g++)
			{
				bucket[b[g]]=0;
			}
		}
	}
	print(ans);
	return 0;
}

```



---

## 作者：SevenDawns (赞：0)

## 贪心加区间暴力
### 枚举每一个子串，把这个子串最小的和外面最大的交换
就可以过了
```
#include <bits/stdc++.h>
using namespace std;
int n,q,i,j,sh[100001],sum,l,a[100001],b[100001],llll;
int maxf[100001],maxb[100001],MAX,k;
int main()
{
    scanf("%d%d",&n,&k);
    for (i=1;i<=n;i++)
      scanf("%d",&sh[i]);
    MAX=-1000000;
    for (i=1;i<=n;i++)
    {
        for (j=i;j<=n;j++)//两重循环暴力枚举
        {
            memset(a,0,sizeof(a));
            memset(b,0,sizeof(b));
            int w=0,p=0;
            for (q=i;q<=j;q++)
            {
                w++;
                a[w]=sh[q];
            }
            sort(a+1,a+1+w);//子串内的数
            for (q=1;q<i;q++)
            {
                p++;
                b[p]=sh[q];
            }
            for (q=j+1;q<=n;q++)
            {
                p++;
                b[p]=sh[q];
            }
            sort(b+1,b+1+p);//子串外的数
            int ll;
            ll=p;
            for (q=1;q<=k;q++)
            {
                if (q>j-i+1)
                  break;
                if (a[q]<b[ll])
                {
                    if (ll<=0)
                      break;
                    a[q]=b[ll];
                    ll--;
                }//最小的和外面最大的交换
            }
            sum=0;
            for (q=1;q<=w;q++)
              sum+=a[q];//求和
            MAX=max(MAX,sum);
        }
    }
    printf("%d\n",MAX);
}
```

---

## 作者：Buried_Dream (赞：0)

## 题意：

给你一个数组，你可以将任意两个元素交换，最多交换 $k$ 次，最大化最大的子区间。

## Solution	

注意到数据范围。

因为只要子区间最大，我们来枚举答案是哪个子区间即可。

贪心的去将子区间的最小值和外边区间的最大值去交换，但是当子区间的最小值比外边区间的最大值还大时，就不需要再交换。

至于求最值，有很多方法，优先队列，线段树，树状数组，直接模拟也能过。

## Code 

```cpp
/*
	Work by: TLE_Automation
*/
#include<vector>
#include<cmath>
#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define LL long long
#define int long long
using namespace std;

const int N = 1e6 + 10;
const int MAXN = 2e5 + 10;

inline char readchar() {
	static char buf[100000], *p1 = buf, *p2 = buf;
	return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;
}

inline int read() {
#define readchar getchar
	int res = 0, f = 0;char ch = readchar();
	for(; !isdigit(ch); ch = readchar()) if(ch == '-') f = 1;
	for(; isdigit(ch); ch = readchar()) res = (res << 1) + (res << 3) + (ch ^ '0');
	return f ? -res : res;
}

inline void print(int x) {
	if (x < 0 ) putchar('-'), x = -x;
	if (x > 9 ) print(x / 10);
	putchar(x % 10 + '0');
}

int a[MAXN];
priority_queue <int, vector<int>, greater<int> > q1, q1k;
priority_queue <int, vector<int>, less<int> > q2, q2k;
int ans = -0x3f3f3f3f, sum = 0;

signed main() {
	int n = read(), k = read();
	for(int i = 1; i <= n; i++) a[i] = read();
	for(int l = 1; l <= n; l++) {
		for(int r = l; r <= n; r++) {
			int num = k; sum = 0;
			q1 = q1k, q2 = q2k;
			for(int i = 1; i <= n; i++) {
				if(i >= l && i <= r) q1.push(a[i]);
				else q2.push(a[i]);
			}
			while(num-- && !q2.empty()) {
				int x = q1.top(),y = q2.top();
				if(x >= y) break;
				q1.pop(), q2.pop();
				q1.push(y), q2.push(x);
			}
			while(!q1.empty()) {
				sum += q1.top(), q1.pop();
			}
			ans = max(ans, sum);
		}
	}
	cout << ans;
}

---

## 作者：BotDand (赞：0)

# $\text{Problems}$

给一个长为 $n$ 的序列，以及交换次数 $k$，每次可以在原先的序列中任意交换两个数交换后找一个最大子串和，输出其可能的最大值。

# $\text{Answer}$

注意到 $1\le n\le 200$，可以暴力。

暴力枚举每一个字串，然后每次交换时将序列中的最小值与非序列的最大值交换，当然前提是前者大于后者。

然后时间复杂度就是 $O(n^{3}k+n^{3})$，感觉跑得还挺快。

# $\text{Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[202];
int b[202];
int n,k;
int K;
int s;
int ma,mi;
int ans=-1002;
inline int read()
{
    int s=0,w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
    return s*w;
}
inline void write(int x)
{
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
inline void print(int x)
{
    write(x);
    putchar('\n');
}
int main()
{
    n=read();K=read();
    for(int i=1;i<=n;++i) a[i]=read();
    for(int i=1;i<=n;++i) b[i]=a[i];
    for(int l=1;l<=n;++l)
        for(int r=l;r<=n;++r)
        {
            s=0;
            for(int k=1;k<=K;++k)
            {
                ma=1;mi=l;
                for(int i=2;i<l;++i) if(a[i]>a[ma]) ma=i;
                for(int i=r+1;i<=n;++i) if(a[i]>a[ma]) ma=i;
                for(int i=l+1;i<=r;++i) if(a[i]<a[mi]) mi=i;
                if(a[ma]>a[mi]) swap(a[ma],a[mi]);
            }
            for(int i=l;i<=r;++i) s+=a[i];
            ans=max(ans,s);
            for(int i=1;i<=n;++i) a[i]=b[i];
        }
    print(ans);
    return 0;
}
```


---

