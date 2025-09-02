# Least Prefix Sum

## 题目描述

Baltic, a famous chess player who is also a mathematician, has an array $ a_1,a_2, \ldots, a_n $ , and he can perform the following operation several (possibly $ 0 $ ) times:

- Choose some index $ i $ ( $ 1 \leq i \leq n $ );
- multiply $ a_i $ with $ -1 $ , that is, set $ a_i := -a_i $ .

Baltic's favorite number is $ m $ , and he wants $ a_1 + a_2 + \cdots + a_m $ to be the smallest of all non-empty prefix sums. More formally, for each $ k = 1,2,\ldots, n $ it should hold that $ $$$a_1 + a_2 + \cdots + a_k \geq a_1 + a_2 + \cdots + a_m. $ $ </p><p>Please note that multiple smallest prefix sums may exist and that it is only required that  $ a\_1 + a\_2 + \\cdots + a\_m $  is one of them.</p><p>Help Baltic find the minimum number of operations required to make  $ a\_1 + a\_2 + \\cdots + a\_m$$$ the least of all prefix sums. It can be shown that a valid sequence of operations always exists.

## 说明/提示

In the first example, we perform the operation $ a_4 := -a_4 $ . The array becomes $ [-1,-2,-3,4] $ and the prefix sums, $ [a_1, \ a_1+a_2, \ a_1+a_2+a_3, \ a_1+a_2+a_3+a_4] $ , are equal to $ [-1,-3,-6,-2] $ . Thus $ a_1 + a_2 + a_3=-6 $ is the smallest of all prefix sums.

In the second example, we perform the operation $ a_3 := -a_3 $ . The array becomes $ [1,2,-3,4] $ with prefix sums equal to $ [1,3,0,4] $ .

In the third and fourth examples, $ a_1 + a_2 + \cdots + a_m $ is already the smallest of the prefix sums — no operation needs to be performed.

In the fifth example, a valid sequence of operations is:

- $ a_3 := -a_3 $ ,
- $ a_2 := -a_2 $ ,
- $ a_5 := -a_5 $ .

The array becomes $ [-2,-3,5,-5,20] $ and its prefix sums are $ [-2,-5,0,-5,15] $ . Note that $ a_1+a_2=-5 $ and $ a_1+a_2+a_3+a_4=-5 $ are both the smallest of the prefix sums (and this is a valid solution).

## 样例 #1

### 输入

```
6
4 3
-1 -2 -3 -4
4 3
1 2 3 4
1 1
1
5 5
-2 3 -5 1 -20
5 2
-2 3 -5 -5 -20
10 4
345875723 -48 384678321 -375635768 -35867853 -35863586 -358683842 -81725678 38576 -357865873```

### 输出

```
1
1
0
0
3
4```

# 题解

## 作者：xzy090626 (赞：11)

## CF1779C 题解
好题。

首先我们知道，对于 $1\le k \le n$，均有

$$a_1+a_2+⋯+a_k\ge a_1+a_2+⋯+a_m$$

我们解这个不等式，发现可以分讨一下：
- 当 $k<m$ 时，我们发现必须使得 $\displaystyle\sum_{\mathclap{k< i\le m}} a_i \le0$ 才能满足条件，即 $(k,m]$ 区间和 $\le 0$。

- 当 $k=m$ 时，显然条件恒成立；

- 当 $k>m$ 时，同理要使得 $\displaystyle\sum_{\mathclap{m< i\le k}} a_i \ge 0$ 才能满足条件，即 $(m,k]$ 区间和 $\ge 0$。

 ---
 我们整理好所有的性质，发现需要让所有的 $k$ 都满足条件，即所有的区间都满足条件。
 
 如果枚举 $k$ 再进行操作的话，即不容易满足条件，而且复杂度至少是 $O(n^2)$ 的，无法通过。
 
 我们考虑从 $m$ 倒序扫到 $1$，如果当前区间总和为正，那么必须修改。
 
 这也是倒着扫的必要性所在：如果不在当前区间（$[i,m]$）修改一个值，那么再往前扫也无法影响到这个区间，从而使结果不合法了。
 
 那么为了保证结果最优，我们可以考虑维护当前区间最值。由于修改所有的 $a_i$ 的贡献相等，所以我们可以贪心地选择当前最大值。由于修改一个值之后最大值需要更新，所以我们需要使用 `std::set` 或者 `std::priority_queue`。
 
 以上是对于 $[1,m]$ 区间的处理，$(m,n]$ 区间自然同理，就可以完成此题了。
 
 ```cpp
 #include<bits/stdc++.h>
#define int long long
#define x first
#define y second
#define pb push_back
using namespace std;
const int N = 1e6 + 5,M = 1e3 + 7;
const int mod = 1e9 + 7;
int s[N];
int n,m;
void solve(){
	int ans = 0;
	cin>>n>>m;
	for(int i=1;i<=n;++i) cin>>s[i];
	priority_queue<int,vector<int>,greater<int>>b;
	priority_queue<int>a;
	int cnt = 0;
	for(int i=m;i>1;--i){
		cnt += s[i];
		a.push(s[i]);
		if(cnt>0){
			cnt -= a.top()*2;
			a.pop();
			ans++;
		}
	}
	cnt = 0;
	for(int i=m+1;i<=n;++i){
		cnt += s[i];
		b.push(s[i]);
		if(cnt<0){
			cnt -= b.top()*2;
			b.pop();
			ans++;
		}
	}	
	cout<<ans<<'\n';
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int T;cin>>T;
	while(T--) solve();
	return 0;
}
```

---

## 作者：abensyl (赞：4)

原题：[CF1779C Least Prefix Sum](https://www.luogu.com.cn/problem/CF1779C)。

好题，~~但是我赛时狂 wa~~。

## 思路

本题不难，主要麻烦的地方是细节。

我们知道，对于前缀和数组 $sum$ 和原数组 $a$，任意下标 $i,j(j\leq i)$ 都有：
$$sum_i=sum_j+\sum_{k=j+1}^ia[k]$$

所以，比较 $sum_i$ 与 $sum_j$ 的大小，只需要比较 $\sum_{k=j+1}^i a[k]$ 即可。

本题中，为使 $sum_m$ 为最小值，所以通过上公式，容易发现：所有的 $\sum_{k=i}^m a[k] (1<i\leq m)\leq 0$ 并且 $\sum_{k=m+1}^i a[k] (m+1 \leq i\leq n)\geq 0$ 即可。

- 而如何维护前缀和呢？

>我们可以从 $m+1\sim n$ 遍历数组，每当前缀和小于等于 $0$ 时，将数组中现在的最小值取反，答案加一；  
>同理地，可以从 $m\sim 1$ 遍历数组，每当前缀和大于等于 $0$ 时，将数组中现在的最大值取反，答案加一。

最后输出答案即可。

提示：维护最大值和最小值可以用堆或者是 stl 中的 priority_queue。

**但是请注意，不开 long long 的话 CF 评测机可能会想要见到你的祖宗：**

![](https://www.mfstem.org/file/241/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202023-01-08%20080927.png)

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353,N=2e5+4,INF=1<<30;
int a[N],sum[N];
bool b[N];
void solve() {
  int n,m;
  int res=0;
  cin>>n>>m;
  priority_queue<int> pque;
  priority_queue<int,vector<int>,greater<int>> pqui;
  for(int i=1;i<=n;++i) cin>>a[i];
  for(int i=m;i>1;--i) { //遍历m到1
    if(i!=m) sum[i]=sum[i+1]+a[i];
    else sum[i]=a[i]; //计算前缀和
    pque.push(a[i]);
    if(sum[i]>0) { //判断前缀和是否大于0
      sum[i]-=pque.top()*2;
      pque.pop();
      res++; //取反，答案加一
    }
  }
  for(int i=m+1;i<=n;++i) { //遍历m+1到n
    if(i!=m+1) sum[i]=sum[i-1]+a[i];
    else sum[i]=a[i]; //计算前缀和
    pqui.push(a[i]);
    if(sum[i]<0) { //判断前缀和是否小于0
      sum[i]-=pqui.top()*2;
      pqui.pop();
      res++; //取反，答案加一
    }
  }
  cout<<res<<'\n'; //输出答案
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  int T; cin>>T;
  while(T--) solve();
}
```

我的 [AC记录](https://codeforces.com/contest/1779/submission/188370679)。

---

## 作者：jiangtaizhe001 (赞：1)

[可能更好的阅读体验](https://www.cnblogs.com/jiangtaizhe001/p/17032171.html)

[题目传送门](https://codeforces.com/problemset/problem/1779/C)
### 题目大意
给定一个序列 $a$，长度 $n$。  
每次操作可以把 $a_i$ 变成 $-a_i$。  
要求 $a$ 做前缀和之后的序列 $s$ 中最小值为 $s_m$。  
求最小操作次数。  
$n\le 2\times10^5$
### 题目解析
显然你需要保证：

- $a_2,a_3,\dots,a_m$ 后缀和都小于等于零（注意从 $a_2$ 开始）
- $a_{m+1},a_{m+2},\dots,a_n$ 前缀和都大于等于零

考虑第一条，显然我们可以倒着来，如果遇到后缀和大于零的，显然是把之后那部分最大的数变成负的。  
然后考虑第二条，如果此时前缀和小于等于零，就把前面最小的变成正的。  
显然用个堆维护一下最值就好。~~第一次Div1A用堆，感觉好离谱。~~  
时间复杂度 $\Theta(n\log n)$
```cpp
int n,m,a[maxn];
priority_queue<int> bi,EB;
priority_queue<int,vector<int>,greater<int> > sm,ES;
void work(){
	n=read(); m=read(); int i,ans=0; ll sum; for(i=1;i<=n;i++) a[i]=read();
	bi=EB; sm=ES; sum=0;
	for(i=m;i>=2;i--){
		sum+=a[i]; bi.push(a[i]);
		while(sum>0) sum-=bi.top()*2,bi.pop(),ans++;
	} sum=0;
	for(i=m+1;i<=n;i++){
		sum+=a[i]; sm.push(a[i]);
		while(sum<0) sum-=sm.top()*2,sm.pop(),ans++;
	} print(ans),pc('\n'); return;
}
```

---

## 作者：aimcf (赞：1)

令 $s_i$ 为 $\sum_{i=1}^i a_i$ 的值。

为了让 $s_k = \max_{i=1}^n s_i$，需要满足下面的两个条件：

+ $s_i\le s_k$，$i < k$。（条件 $1$）
+ $s_i \le s_k$，$i > k$。（条件 $2$）

对于条件 $1$，可以使用一个大根堆，每次选出最小值进行操作。

对于条件 $2$，可以使用一个小根堆，每次选出最大值进行操作。

容易发现时间复杂度是 $O(n\log n)$ 的。

---

## 作者：Gaode_Sean (赞：0)

对于此题，很显然可以分成 $i \leq m-1$ 和 $m \leq i$ 两种简单的情况。

先讨论 $i \leq m-1$。

不难推导出，一次操作的代价为 $m$ 减小 $2 \times a_i$。如此一来，当 $s_p \leq s_m-1$ 时，修改 $p$ 之前的数便毫无意义。因此，只能修改 $p$ 之后位置上的数。

容易发现，当 $s_p \leq s_m -1$ 时，修改 $s_{p} \sim s_m$ 中最大的数能使结果最优。该操作可以用堆来实现。

由于下标越大的数应越早加入堆，故采用倒序枚举。

另一种情况同理。

## AC Code

```cpp
#include<bits/stdc++.h> 
using namespace std;
typedef long long ll;
const int N=2e5+5;
int T,n,m,ans;
ll a[N],sum;
priority_queue<ll> q;
void solve()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	ans=sum=0;
	while(!q.empty()) q.pop();
	for(int i=m;i>=2;i--)
	{
		q.push(2*a[i]),sum+=a[i];
		if(sum>0) sum-=q.top(),ans++,q.pop();
	}
	sum=0;
	while(!q.empty()) q.pop();
	for(int i=m+1;i<=n;i++)
	{
		q.push(-2*a[i]),sum+=a[i];
		if(sum<0) sum+=q.top(),ans++,q.pop();
	}
	printf("%d\n",ans);
}
int main()
{
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```

---

## 作者：RNTBW (赞：0)

### 序
无。
## 题意

给定一个序列 $a$ 与一个位置 $m$，每次修改可以令 $a_i=-a_i$。

求最少几次操作可以使 $\forall i\in [1,n],\sum^i_{j=1} a_j \ge \sum^m_{j=1} a_j$。

## 思路

我们来分类讨论一下下：

1. $i \le m$：

此时设 $\sum^i_{j=1} a_j=x,\sum^m_{j=1} a_j=y$。

则 $y-x=\sum^m_{j=1} a_j-\sum^i_{j=1} a_j=\sum^m_{j=i+1} a_j$。

由于 $x\ge y$，所以 $y-x\le 0$。

即 $\sum^m_{j=i+1} a_j \le 0$。

这时求将所有 $i$ 都修改为满足上述式子的最小操作次数。

我们可以从 $m$ 到 1 扫一遍，并令 $\sum^m_{j=i} a_j=k$，当 $k>0$ 时就修改。

怎么修改呢？考虑贪心，每次将使 $k$ 减去最大的值，即将 $\max^m_{j=i} a_j$ 取反。

很容易想到优先队列维护。

2. $i > m$：

这种情况其实与情况 1 的思路差不多。

不同的是当 $\sum^i_{j=m+1} a_j<0$ 的时候修改，并且每次修改当前遍历序列中的最小值，读者自证不难。

## 正确代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[200005];
int t,n,m,i,k,s;
signed main()
{
	scanf("%lld",&t);
	while(t--)
	{
		scanf("%lld%lld",&n,&m);k=s=0;
		priority_queue<int> q1;//大根优先队列
		priority_queue<int,vector<int>,greater<int> > q2;//小根优先队列
		for(i=1;i<=n;i++) scanf("%lld",&a[i]);
		if(n==1)//直接特判
		{puts("0");continue;
		}
		for(i=m;i>1;i--)//不能为0
		{
			k+=a[i];
			q1.push(a[i]);
			if(k>0)//需要修改
			{
				k-=q1.top()*2ll;//最大值 x 取反后对 k 的贡献减小 2*x
				q1.pop();s++;
			}
		}
		k=0;
		for(i=m+1;i<=n;i++)
		{
			k+=a[i];
			q2.push(a[i]);
			if(k<0)//需要修改
			{
				k-=q2.top()*2ll;
				q2.pop();s++;
			}
		}
		printf("%lld\n",s);
	}
	return 0;
}
```


---

## 作者：loser_seele (赞：0)

赛时没做出来，换一个奇怪的做法来补一发。

首先只考虑 $ i<m $ 的情况，显然 $ i \geq m $ 的情况可以类似推导。以下记前缀和数组为 $ sum $。

不难发现，一次操作等价于将 $ m \leftarrow m-2 \times a_x $，而对于一个 $ sum_k < sum_m $，修改 $ k $ 以前的数只会使得 $ sum_k,sum_m $ 同时加减，仍然不符合条件。于是考虑 $ k $ 之后的位置，发现这些位置因为已经保证了后面的数都已经满足条件（根据上述假设，只考虑每个数以后的数，改为倒序枚举即可。），所以在后面的数里面贪心挑最大的修改后续的答案肯定更优。 $ i \geq m $ 的情况改为正序枚举选最小值即可，推导同理。

那么问题转换为了怎么快速插入，删除，查找序列中最小值和最大值，正常的做法是优先队列解决问题，但是要么要两个优先队列要么需要取反，写起来太麻烦，于是这里用了手写平衡树。

时间复杂度 $ \mathcal{O}(Tn\log{n}) $，可以通过。

代码：

```cpp
#import <bits/stdc++.h>
using namespace std;
#define int long long
struct node
{
int lc,rc,key,pri,cnt,sze;
#define lc(x) t[x].lc
#define rc(x) t[x].rc
#define v(x) t[x].key
#define p(x) t[x].pri
#define c(x) t[x].cnt
#define s(x) t[x].sze
}t[200020];
int rt,pool;
const int INF=-2147483647;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
inline void upt(const int &k)
{
s(k)=s(lc(k))+s(rc(k))+c(k);
}
inline void Zig(int &k)
{
int y=lc(k);
lc(k)=rc(y);
rc(y)=k;
s(y)=s(k);
upt(k);
k=y;
}
inline void Zag(int &k)
{
int y=rc(k);
rc(k)=lc(y);
lc(y)=k;
s(y)=s(k);
upt(k);
k=y;
}
inline void inserter(int &k,const int &key)
{
if(!k)
{
k=++pool;
v(k)=key;
p(k)=rand();
c(k)=s(k)=1;
lc(k)=rc(k)=0;
return;
}
else
++s(k);
if(v(k)==key)
++c(k);
else if(key<v(k))
{
inserter(lc(k),key);
if(p(lc(k))<p(k))
Zig(k);
}
else
{
inserter(rc(k),key);
if(p(rc(k))<p(k))
Zag(k);
}
return;
}
inline void Delete(int &k,const int &key)
{
if(v(k)==key)
{
if(c(k)>1)
--c(k),--s(k);
else if(!lc(k)||!rc(k))
k=lc(k)+rc(k);
else if(p(lc(k))<p(rc(k)))
Zig(k),Delete(k,key);
else
Zag(k),Delete(k,key);
return;
}
--s(k);
if(key<v(k))
Delete(lc(k),key);
else
Delete(rc(k),key);
return;
}
inline int QueryPre(const int &key)
{
int x=rt,res=-INF;
while(x)
{
if(v(x)<key)
res=v(x),x=rc(x);
else
x=lc(x);
}
return res;
}
inline int QuerySuf(const int &key)
{
int x=rt,res=INF;
while(x)
{
if(v(x)>key)
res=v(x),x=lc(x);
else
x=rc(x);
}
return res;
}
inline int QueryKth(int k)
{
int x=rt;
while(x)
{
if(s(lc(x))<k&&s(lc(x))+c(x)>=k)
return v(x);
if(s(lc(x))>=k)
x=lc(x);
else
k-=s(lc(x))+c(x),x=rc(x);
}
return 0;
}
inline int QueryRank(const int &key)
{
int x=rt,res=0;
while(x)
{
if(key==v(x))
return res+s(lc(x))+1;
if(key<v(x))
x=lc(x);
else
res+=s(lc(x))+c(x),x=rc(x);
}
return res;
}
int T,n,m,a[200010],sum[200010];
void clean()
{
for(int i=1;i<=pool;i++)
lc(i)=rc(i)=v(i)=p(i)=s(i)=c(i)=0;
rt=pool=0;
}
void solve()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    cin>>a[i];
    int tag=0,ans=0;
	for(int i=1;i<=n;i++)
    sum[i]=sum[i-1]+a[i];
    clean();
    int now=0;
	for(int i=m;i>=1;i--)
    {
		while(sum[i]<sum[m]+tag)
        {
			int it=QueryKth(now);
			tag=tag-2*it;
			ans++;
			Delete(rt,it);
            now--;
		}
		if(a[i]>0) 
        inserter(rt,a[i]),now++;
	}
	tag=0;
    clean();
    now=0;
	for(int i=m+1;i<=n;i++)
    {
		if(a[i]<0) 
        inserter(rt,a[i]),now++;
		while(sum[i]+tag<sum[m])
        {
			int it=QueryKth(1);
			tag=tag-2*it;
			ans++;
			Delete(rt,it);
            now--;
		}
	}
    cout<<ans<<'\n';
}
signed main()
{
    cin>>T;
    while(T--) 
    solve();
}
```


---

## 作者：bsTiat (赞：0)

## 题意
给定一个序列 $ a $，每次操作可以选一个数将其变成相反数，定义 $ s_i=\sum_{k=1}^{k=i}a_k $，问最少进行几次操作，可以使所有 $  s_i\geq s_m $。

## 思路

对于 $i\leq m $ 的部分，若当前的 $ s_i<s_m $ ，我们考虑到，若修改 $ k\leq i $ 的 $ a_k $，是无效的，所以我们只能修改 $ i<k\leq m $ 的 $ a_k $，此时只有 $ s_m $ 会减小，贪心的选取能使 $ s_m $ 减小最多的显然最优，所以我们可以拿一个堆来维护 $ i<k\leq m $ 的 $ a_k $，选完堆顶就删掉。

对于 $ i>m $ 的部分，同理，用堆维护 $ m<k\leq i $ 的 $ a_k $。

## 代码
```cpp
#include<bits/stdc++.h>
# define int long long
using namespace std;
inline int rd(){
	int f=1,s=0;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c<='9'&&c>='0'){s=(s<<3)+(s<<1)+(c^48);c=getchar();}
	return s*f;
}
const int N = 1e6+5;
int t,n,m,ans;
long long a[N],b[N],s;
priority_queue<int>q; 
signed main(){
	t=rd();
	while(t--){
		while(!q.empty())q.pop();q.push(0);
		n=rd(); m=rd(); ans=0; s=0;
		for(int i=1;i<=n;++i){
			a[i]=rd();
			b[i]=a[i]+b[i-1];
		}
		for(int i=m;i>=1;--i){
			while(b[i]<b[m]){
				b[m]-=q.top()*2;
				s-=q.top()*2;
				q.pop(); ++ans;
			}
			if(a[i]>0) q.push(a[i]);
		}
		while(!q.empty())q.pop();q.push(0);
		for(int i=m+1;i<=n;++i){
			if(a[i]<0) q.push(-a[i]);	
			while((b[i]+s)<b[m]){
				s+=q.top()*2; q.pop(); ++ans;
			}		
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

## 作者：shinzanmono (赞：0)

# 题意：

定义长度为 $n$ 的数组 $a$ 的前缀和数组为 $s$，对于一次操作，你可以选择一个数，变为这个数的相反数，给定一个数 $m$，请你求出最小的操作次数使序列满足：$\forall i\in[1,n], s_i\geq s_m$。

# Solution：

对于一个序列，我们可以知道：对于任意的 $1\leq l\leq r\leq n$，$s_r = s_l +\sum_{i=l}^r a_i$，对于 $1\leq p< m$，$s_p\geq s_m$ 的充要条件是 $\sum_{i=p+1}^m a_i \leq0$，所以对于 $m$ 左面的部分，我们可以从 $m$ 枚举到 $2$（因为是非空子端），对于枚举的中间值 $i$，我们维护 $sum = \sum_{i=i}^m a_i$，如果出现 $sum>0$，那么把当前枚举过的数的最大值变为他的相反数，然后继续枚举，对于最大值，我们可以用 STL 的 std::priority_queue 维护。

对于 $m< p\leq n$，$s_p\geq s_m$ 的充要条件是 $\sum_{i=m+1}^p a_i \geq0$。所以对于 $m$ 右面的部分，我们可以从 $m+1$ 枚举到 $n$，对于枚举的中间值 $i$，我们维护 $sum = \sum_{i=i}^m a_i$，如果出现 $sum<0$，那么把当前枚举过的数的最小值变为他的相反数，然后继续枚举，对于最小值，我们依旧可以用 STL 的 std::priority_queue 维护。

# Code:
```cpp
#include<iostream>
#include<queue>
#include<vector>
#include<functional>
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while (t--) {
        int n, m;
        std::cin >> n >> m;
        long long arr[n + 1], sum = 0, ans = 0;
        for (int i = 1; i <= n; i++) std::cin >> arr[i];
        if (n == 1) {
            std::cout << "0\n";
            continue;
        }
        std::priority_queue<int, std::vector<int>, std::less<int>> lpq;
        std::priority_queue<int, std::vector<int>, std::greater<int>> gpq;
        for (int i = m; i > 1; i--) {
            sum += arr[i];
            lpq.push(arr[i]);
            if (sum > 0) {
                int maxn = lpq.top();
                lpq.pop();
                sum -= 2 * maxn;
                ans++;
            }
        }
        sum = 0;
        for (int i = m + 1; i <= n; i++) {
            sum += arr[i];
            gpq.push(arr[i]);
            if (sum < 0) {
                int minn = gpq.top();
                gpq.pop();
                sum -= 2 * minn;
                ans++;
            }
        }
        std::cout << ans << "\n";
    }
    retunr 0;
}

```

---

## 作者：xiaruize (赞：0)

**分析**

令 $M=\sum\limits^{m}_{i=1}a_i$ , $S_k=\sum\limits^{k}_{i=1}a_i$

当 $S_k<M$ 时，分两类考虑

1. $k<m$
   
   此时，对 $a_1 \cdots a_k$ 执行题目所述的操作，都会同时使 $S_k$ 和 $M$ 增加 , 不会使得当前局面合法

   那么只会对 $a_{k+1} \cdots a_m$ 这些数执行操作
   
   考虑怎样操作最优，容易发现，可以贪心的选择尽可能大的数进行操作

   每次操作会使 $M=M-a_x\times 2$

2. $k>m$
   
   同上分析，可以发现，这次的操作对象为 $a_{m+1} \cdots a_k$ ， 优先选择小的数进行操作

**实现**

从 $m$ 开始，倒序循环至 $1$ ，用 `priority_queue` 维护最大值

同理，再从 $m \to n$ 正序循环 ，维护最小值

**Code**

```cpp
/*
    Name:
    Author: xiaruize
    Date:
*/
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define ALL(a) (a).begin(), (a).end()
#define pb push_back
#define mk make_pair
#define pii pair<int, int>
#define pis pair<int, string>
#define sec second
#define fir first
#define sz(a) int((a).size())
#define rep(i, x, y) for (int i = x; i <= y; i++)
#define repp(i, x, y) for (int i = x; i >= y; i--)
#define Yes cout << "Yes" << endl
#define YES cout << "YES" << endl
#define No cout << "No" << endl
#define NO cout << "NO" << endl
#define debug(x) cerr << #x << ": " << x << endl
#define double long double
const int INF = 0x3f3f3f3f;
const int MOD = 1000000007;
const int N = 2e5 + 10;

// bool st;
int t;
int n, m;
int a[N];
// bool en;

void solve()
{
    int res = 0;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    int sum = 0;
    for (int i = 1; i <= m; i++)
        sum += a[i];
    int tot = 0;
    tot = sum - a[m];
    priority_queue<int> q;
    q.push(a[m]);
    for (int i = m - 1; i >= 1; i--)
    {
        if (tot < sum)
        {
            while (tot < sum)
            {
                sum -= q.top() * 2ll;
                q.pop();
                res++;
            }
        }
        q.push(a[i]);
        tot -= a[i];
    }
    priority_queue<int, vector<int>, greater<int>> p;
    tot = sum;
    for (int i = m + 1; i <= n; i++)
    {
        p.push(a[i]);
        tot += a[i];
        if (tot < sum)
        {
            while (tot < sum)
            {
                tot -= p.top() * 2ll;
                p.pop();
                res++;
            }
        }
    }
    cout << res << endl;
}

signed main()
{
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // cerr<<(&en-&st)/1024.0/1024.0<<endl;
    // auto t_1=chrono::high_resolution_clock::now();
    cin >> t;
    while (t--)
        solve();
    // auto t_2=chrono::high_resolution_clock::now();
    // cout <<". Elapsed (ms): " << chrono::duration_cast<chrono::milliseconds>(t_2 - t_1).count() << endl;
    return 0;
}
```

---

