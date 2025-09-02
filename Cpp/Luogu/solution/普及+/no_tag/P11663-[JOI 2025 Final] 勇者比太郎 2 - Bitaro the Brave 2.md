# [JOI 2025 Final] 勇者比太郎 2 / Bitaro the Brave 2

## 题目背景


译自 [第24回日本情報オリンピック 本選](https://contests.ioi-jp.org/joi-ho-2025/index.html) T2。

## 题目描述


比太郎要打怪。

令比太郎初始时的**力量**为 $x$。有 $N$ 个怪物，编号 $1\sim N$。欲打败第 $i$（$1\le i\le N$）个怪物，需要力量 $\ge A_i$。打败第 $i$（$1\le i\le N$）个怪物，会使比太郎的力量增加 $B_i$。

比太郎会用如下的策略打怪：

- 选择整数 $j$（$1\le j\le N$），然后按 $j,j+1,\cdots,N$ 的顺序打怪。
- 如果 $j\ge 2$，回头按顺序打怪物 $1,2,\cdots,j-1$。

在按照策略打完所有的怪物的前提下，求出比太郎初始力量 $x$ 的最小值。


## 说明/提示


### 样例解释

#### 样例 $1$ 解释

令 $x=1$，然后按照 $1\to 5$ 的顺序打怪。

该样例满足子任务 $1,2,3,5$ 的限制。


#### 样例 $2$ 解释

令 $x=3$，然后先打 $3\to 5$ 的怪，再打 $1\to 2$ 的怪。

该样例满足子任务 $1,2,3,5$ 的限制。


#### 样例 $3$ 解释

该样例满足所有子任务的限制。


#### 样例 $4$ 解释

该样例满足子任务 $1,2,3,5$ 的限制。



### 数据范围

- $2\le N\le 5\times 10^5$。
- $0\le A_i\le 10^9$（$1\le i\le N$）。
- $0\le B_i\le 10^9$（$1\le i\le N$）。
- 输入的值全部是整数。

### 子任务

1. （10pts）$N\le 2,000$，保证答案不大于 $10$。
2. （21pts）$N\le 2,000$。
3. （19pts）保证答案不大于 $10$。
4. （22pts）$B_i=1$（$1\le i\le N$）；
5. （28pts）无额外限制。

## 样例 #1

### 输入

```
5
1 3 2 8 6
4 3 1 1 2```

### 输出

```
1```

## 样例 #2

### 输入

```
5
1 6 3 3 2
1 2 1 0 1```

### 输出

```
3```

## 样例 #3

### 输入

```
10
11 9 8 12 7 7 8 12 9 10
1 1 1 1 1 1 1 1 1 1```

### 输出

```
9```

## 样例 #4

### 输入

```
7
1125 638 0 37 737 820 1202
23 984 558 350 52 345 580```

### 输出

```
0```

# 题解

## 作者：MonKeySort_ZYczc (赞：2)

## 思路流程
直接处理很麻烦，先断环成链。  
为习惯与下文叙述方便，假设断环成链后 $A_{i+n}=A_i(i<n)$，$B$ 数组同理。  
把 $B_i$ 做前缀和，设前缀和数组为 $S_i$。    
容易发现，假如第一个打的怪物是 $i(1\le i\le n)$，此时比太郎需要 
$$
\max_{i\le j<i+n}(A_j-(S_{j-1}-S_{i-1}))
$$ 
的力量，将式子化为 
$$
\max_{i\le j<i+n}(A_j-S_{j-1}+S_{i-1})
$$ 
再化为 
$$
\max_{i\le j<i+n}(A_j-S_{j-1})+S_{i-1}
$$ 
发现，$A_j-S_{j-1}$ 是不随 $i$ 变化的，因此提前处理，让 $A_j:=A_j-S_{j-1}$。  
此时问题转化为定长区间最大值问题，单调队列解决就行。  
答案即为 
$$
\min_{1\le i\le n}(\max_{i\le j<i+n}(A_j-S_{j-1})+S_{i-1})
$$ 
。  

总时间复杂度：$O(n)$。  

哦对了，别忘开 ```long long``` 了。
## 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int N=1e6+10;
int n,a[N],b[N],que[N<<2][2],head=1,tail,ans=0x3f3f3f3f3f3f3f3fll;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],a[i+n]=a[i];
	for(int i=1;i<=n;i++) cin>>b[i],b[i+n]=b[i];
	for(int i=1;i<2*n;i++) a[i]-=b[i-1],b[i]+=b[i-1];
	for(int i=1;i<n;i++) 
	{
		while(head<=tail&&que[tail][1]<=a[i]) tail--;
		tail++;que[tail][0]=i;que[tail][1]=a[i];
	}
	for(int i=n;i<2*n;i++)
	{
		while(head<=tail&&que[head][0]<i-n+1) head++;
		while(head<=tail&&que[tail][1]<=a[i]) tail--;
		tail++;que[tail][0]=i;que[tail][1]=a[i];
		ans=min(ans,que[head][1]+b[i-n]);
		//cout<<que[head][1]+b[i-n]<<endl;
	}
	cout<<ans;
}

```

---

## 作者：Brokwind (赞：1)

今天模拟赛出了这题，好久没见这么简单的题了。

## 思路分析

看到这个题时，我们可以发现它实际是在一个环上，$N$ 号节点的下一个是 $1$ 号节点，可以任选一个开始位置。

现在我们假设比太郎即使没打过怪物也可以继续打下去并获得奖励，并且初始攻击力为 $0$，然后计算一个数组 $s_i$，表示比太郎在打第 $i$ 个怪物时的攻击力与他实际需要的攻击力（$a_i$）之差。

显然，当 $s$ 的每个值均为正时，比太郎就可以打完怪物。

而初始攻击力对 $s$ 的影响相当于把 $s$ 中的每个数加上它，所以取成 $-\min s_i$ 即可让 $s$ 的每个值均为正。

那么就会有一个暴力思路：枚举起点，计算 $s$，获得此时的最小初始攻击力，再把所有情况的答案取最小值。

这时我们会发现，起点为 $i$ 的 $s$ 数组和起点为 $i+1$ 的 $s$ 数组差别并不大：

对于 $j \ne i$，$s_j$ 在起点为 $i$ 时获得了打完 $i$ 号怪物获得的 $B_i$ 攻击力，但在起点为 $i+1$ 时失去了这部分攻击力，相当于减去 $B_i$；

对于 $s_i$，在起点为 $i$ 时没有获得任何攻击力，但在起点为 $i+1$ 时作为最后一个节点获得了所有其他节点的攻击力，相当于加上所有 $B$ 之和再减去 $B_i$。

所以 $s$ 数组的变化为全体减去 $B_i$ 之后把 $s_i$ 加上所有 $B$ 之和。统计答案时要求最小值，线段树维护即可。

实现时可以预处理出 $sum=\sum_{i = 1}^{N} B_i$。

## code

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<iomanip>
#include<algorithm>
#include<bitset>
#include<set>
#include<vector>
#include<queue>
#include<cmath>
#include<map>
#include<unordered_map>
#define qi queue<int>
#define pii pair<int,int>
#define pll pair<long long,long long>
#define mpii map<int,int>
#define mpll map<long long,long long>
#define mst memset
#define ll long long
#define db double
#define ldb long double
#define bst bitset
#define vec vector
#define szf sizeof
#define inf 0x3f3f3f3f
#define linf (ll)0x3f3f3f3f3f3f3f3f
#define dq deque
#define ls (fa<<1)
#define rs (fa<<1|1)
#define int long long
using namespace std;

inline int read(){
    ll x=0,f=1;
    char ch=getchar();
    while(isdigit(ch)==0 && ch!='-')ch=getchar();
    if(ch=='-')f=-1,ch=getchar();
    while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
    return x*f;
}

inline void write(int x){
    int f=0;char ch[40];
    if(!x){fputs("0\n",stdout);return;}
    if(x<0){putchar('-');x=-x;}
    while(x)ch[++f]=x%10+'0',x/=10;
    while(f)putchar(ch[f--]);
    putchar('\n');
}

const int MAXN=5e5+10;

ll a[MAXN],b[MAXN],s[MAXN],sum,n,ans;

struct Tree{ll mi,add;int l,r;}t[MAXN<<2];

void pushup(int fa){t[fa].mi=min(t[ls].mi,t[rs].mi);}

void build(int fa,int l,int r){
	t[fa].l=l,t[fa].r=r;
	if(l==r){t[fa].mi=s[l];return;}
	int mid=l+r>>1;
	build(ls,l,mid),build(rs,mid+1,r),pushup(fa);
	return;
}

void pushdown(int fa){if(t[fa].add){int add=t[fa].add;t[ls].add+=add,t[ls].mi+=add;t[rs].add+=add,t[rs].mi+=add;t[fa].add=0;return;}}

void upd(int fa,int l,int r,int v){
	if(l<=t[fa].l&&t[fa].r<=r){t[fa].add+=v,t[fa].mi+=v;return;}
	pushdown(fa);
	int mid=t[fa].l+t[fa].r>>1;
	if(l<=mid) upd(ls,l,r,v);
	if(mid<r) upd(rs,l,r,v);
	pushup(fa);
	return;
}

ll qy(int fa,int l,int r){
	if(l<=t[fa].l&&t[fa].r<=r){
		return t[fa].mi;
	}	
	pushdown(fa);
	int mid=t[fa].l+t[fa].r>>1;
	ll re=linf;
	if(l<=mid) re=min(re,qy(ls,l,r));
	if(mid<r) re=min(re,qy(rs,l,r));
	return re;
}

signed main(){
	n=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=n;i++) b[i]=read(),sum+=b[i];
	for(int i=1;i<=n;i++) s[i]=s[i-1]+a[i-1]+b[i-1]-a[i];
	build(1,1,n);
	ans=qy(1,1,n);
	for(int i=2;i<=n;i++){
		upd(1,1,n,-b[i-1]);
		upd(1,i-1,i-1,sum);
		ans=max(ans,qy(1,1,n));
	}
	write(-ans);

    return 0;
}
``````

---

## 作者：JZJR_A_0 (赞：1)

## 前置知识

* 数据结构
* 前缀和

## 思路

首先区间断点问题都先倍长出去，这样可以少一个 $n$ 的复杂度。

接下来我们考虑一个长度为 $n$ 的区间如何处理。

记 $S_i$ 表示 $B_i$ 的前缀和，即 $S_i=\sum_{j=1}^i B_j$。

发现这个区间的答案显然为 $\max_{i=1}^n \{A_i-S_i\}$。

那么考虑用数据结构来查询每一个区间的 $\max$ 值，答案取最小值。

## 实现

这里代码使用 st 表，当然也可以使用其他支持查询区间最值的数据结构。

### AC code：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e6+5;
#define LL long long
LL a[N],b[N],n;
LL st[N][22];
LL llg[N];
LL ask(int l,int r){
	LL k=llg[r-l+1];
	return max(st[l][k],st[r-(1<<k)+1][k]);
}
int main (){
	freopen("brave.in","r",stdin);
	freopen("brave.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	llg[1]=0;
	for(int i=2;i<=1e6;i++)llg[i]=llg[i/2]+1;
//	for(int i=1;i<=17;i++)cout<<i<<' '<<llg[i]<<'\n';
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)cin>>b[i];
	for(int i=n+1;i<=2*n;i++)a[i]=a[i-n];
	for(int i=n+1;i<=2*n;i++)b[i]=b[i-n];
	for(int i=1;i<=2*n;i++)b[i]+=b[i-1],a[i]-=b[i-1];
	memset(st,-0x3f,sizeof(st));
	for(int i=1;i<=2*n;i++)st[i][0]=a[i];//,cout<<a[i]<<' ';
//	cout<<'\n';
	for(int j=1;(1<<j)<=n*2;j++)
		for(int i=1;i+(1<<j)-1<=n*2;i++)
			st[i][j]=max(st[i+(1<<(j-1))][j-1],st[i][j-1]);
//	cout<<ask(12,20)<<'\n';
	LL ans=INT_MAX;
	for(int i=1;i<=n;i++){
		LL dmin=ask(i,i+n-1);
	//	cout<<dmin<<' ';
		dmin+=b[i-1];
	//	cout<<dmin<<'\n';
		ans=min(ans,dmin);
	}
	cout<<ans<<'\n';
	return 0;
}
/*

*/
```

---

## 作者：MathCore (赞：1)

## 问题描述

比太郎要按照特定顺序击败所有怪物，要求初始力量尽可能小。他可以选择一个起点 $j$ 开始，先击败从 $j$ 到 $N$ 的怪物，再回去击败 $1$ 到 $j-1$ 的怪物。

要我们求的是找到所有可能的起点 $j$ 与对应的最小初始力量，并只取其中的最小值（初始力量的最小值）。

## 解题思路

可以定义前缀和数组 $s$，则 $s_i$ 表示前 $i$ 个怪物的 $B$ 值之和：  
$$s_i = \sum_{k=1}^{i} B_k$$  
好的啊，经过了这个预处理，我们就可以很快的计算所有区间的 $B$ 值总和。

然后再看每个怪物 $i$，计算关键值 $d_i$，这个就表示只考虑前面 $i-1$ 个怪物的数值 $B$ 的加成时，初始力量需满足的条件：  
$$d_i = A_i - s_{i-1}$$

为了快速计算（将时间复杂度降至最低）后半段路径（$j \to N$）的初始力量的需要。所以定义 $r_j$ 表示从 $j$ 到 $N$ 的 $d$ 值最大值。逆序遍历维护当前最大值：  
$$r_j = \max(d_j, r_{j+1})$$

同上，对于前半段路径（$1 \to j-1$）的初始力量需求也得快速计算。$p_j$ 表示前 $j-1$ 个 $d$ 值的最大值。正序遍历维护当前最大值：  
$$p_j = \max(p_{j-1}, d_{j-1})$$


## 具体实现

先遍历 $B$ 数组，计算 $s$。

再根据 $A$ 和 $s$ 计算每个 $d[i]$。

然后逆序初始化 $r$ 数组。并正序初始化 $p$ 数组。

最后遍历每个起点 $j$，分别计算：
- **后半段需求**：$\text{max}_d = r_j + s_{j-1}$。
- **前半段需求**：$\text{max}_c = p_j - (s_N - s_{j-1})$。
- **初始力量**：$x_j = \max(\text{max}_d, \text{max}_c, 0)$。

并输出：

$$x_{\text{min}}=\min_{1 \leq j \leq N} x_j$$ 

就能完成任务（AC）！

#### 代码实现

```cpp
#include <iostream>
#include <climits>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N=5e5+5; 
int n;
ll a[N],b[N],s[N],d[N],r[N],p[N];
int main(){
	scanf("%d",&n);
	for(int i=0;i<n;++i)scanf("%lld",&a[i]);
	for(int i=0;i<n;++i)scanf("%lld",&b[i]);
	s[0]=0;
	for(int i=1;i<=n;++i){
		s[i]=s[i-1]+b[i-1];
	}
	for(int i=1;i<=n;++i){
		d[i]=a[i-1]-s[i-1];
	}
	r[n+1]=LLONG_MIN;
	for(int i=n;i>=1;--i){
		r[i]=max(d[i],r[i+1]);
	}
	ll sf=LLONG_MIN;
	for(int j=1;j<=n;++j){
		if(j>1){
			p[j]=sf;
		}
		if(d[j]>sf){
			sf=d[j];
		}
	}
	ll mix=LLONG_MAX;
	ll mat=s[n];
	for(int j=1;j<=n;++j){
		ll a=r[j]+s[j-1];
		ll b=LLONG_MIN;
		ll x;
		if(j>=2){
			b=p[j]+(s[j-1]-mat);
			x=max(a,b);
		}else x=a;
		if(x<mix){
			mix=x;
		}
	}
	if(mix<0){
		mix=0;
	}
	cout << mix << endl;
	return 0;
}
```

## 结尾

该算法时间复杂度：$O(n)$。

---

## 作者：Wei_Han (赞：1)

简单题，初始力量显然具有具有单调性，直接二分答案。

考虑对于一个 $x$，令他合法的条件是什么。我们枚举每一个分割点 $j$，当前走到了 $i$ 位置，当 $i>j$ 时，假定前面位置全部合法，该位置不合法，则满足 $x + pre_{i-1} - pre_{j-1} < a_i$，其中 $pre_i$ 表示 $b$ 的前缀和。移项可得 $x + pre_{i-1} - a_i < pre_{j-1}$，那么对于 $i>j$ 的位置的不合法条件就是 $x + \min \left \{ pre_{i-1} - a_i\right \} < pre_{j-1}$，可以预处理前缀和做到 $O(n)$，同理，对于 $i<j$ 的位置满足 $x + \min \left \{ pre_{i-1} - a_i\right \} < pre_{j-1} - pre_{n}$ 则存在不合法位置。

复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
#define inf 0x3f3f3f3f
#define pr putchar('\n')
#define fi first
#define se second
#define pp putchar(' ')
#define pii pair<ll,ll>
#define pdi pair<ll,ll>
#define mem(aa,bb) memset(aa,bb,sizeof(aa))
#define fo(a,i,b) for(register ll i = a ; i <= b ; ++ i )
#define Fo(a,i,b) for(register ll i = a ; i >= b ; -- i )
#define pb push_back
//#pragma GCC optimize(2)
using namespace std;
//typedef int ll;
typedef long long ll;
//typedef __int128 ll;
typedef double db;
inline void read(ll &opp){ll x=0,t=1;char ch;ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-'){t=-1;}ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}opp=x*t;return; }
inline void wr(ll x){if(x<0){putchar('-');x=-x;}if(x>9){wr(x/10);}putchar(x%10+'0');}
const ll N=2e6+5,M=2e4+5,mod=1e9+7;
ll n,a[N],b[N],pre[N],facm[N],prem[N];
inline bool check(ll midd)
{
	fo(1,i,n) 
		if(midd+facm[i]>=pre[i-1]&&midd+prem[i]>=pre[i-1]-pre[n]) return 1;
	return 0;
}
signed main(){
	read(n);fo(1,i,n) read(a[i]);fo(1,i,n) read(b[i]),pre[i]=pre[i-1]+b[i];
	facm[n]=pre[n-1]-a[n];Fo(n-1,i,1) facm[i]=min(facm[i+1],pre[i-1]-a[i]); 
	prem[1]=pre[0]-a[1];fo(2,i,n) prem[i]=min(prem[i-1],pre[i-1]-a[i]);
	ll l=0,r=1e9;
	while(l<r)
	{
		ll mid=l+r>>1;
		if(check(mid)) r=mid;
		else l=mid+1;
	}
	wr(l),pr;
	return 0;
}
``````

---

## 作者：crlxxzzh (赞：0)

## 知识点

- 单调队列（[P1886 滑动窗口 /【模板】单调队列](https://www.luogu.com.cn/problem/P1886)）

- 前缀和

## 解题思路

### 暴力枚举
---

题目中要求选定一个 $j（1 \le j \le n）$，比太郎从 $j$ 开始按照

$$j,j+1,j+2,\cdots,n,1,2,\cdots,j-1$$

的顺序打怪。

我们很容易想到可以把这些怪看做一个环，比太郎打怪的过程相当于从环上一点按一定顺序遍历整个环，进而想到化环为链的思想。

定义

$$A_{i + n} = A_i,B_{i + n} = B_i(1 \le i < n)$$

。

假设第一次打的怪编号为 $j(1 \le j \le n)$，此时比太郎需要的初始力量的最小值为 $P_j$。

则

$$P_j=\max_{j \le i < n + j} ( A_i - \sum_{k = i}^{j - 1} B_k)$$

。

设比太郎需要的初始力量的最小值（即答案）为 $P$。

则

$$P=\min_{1 \le j \le n} P_j$$

$$P = \min_{1 \le j \le n} (\max_{j \le i < n + j} (A_i - \sum_{k = j}^{i - 1} B_k))$$

。

时间复杂度 $O(n^3)$，TLE 无疑。

### 考虑前缀和优化
---

观察这个求和

$$\sum_{k = j}^{i - 1} B_k$$

发现这部分计算可以用前缀和将时间复杂度优化成 $O(1)$。

定义前缀和数组

$$sum_i = \sum_{j = 1}^{i} B_j$$

则

$$\sum_{k = j}^{i - 1} B_k = sum_{i - 1} - sum_{j - 1}$$

则

$$P = \min_{1 \le j \le n} (\max_{j \le i < n + j} (A_i - (sum_{i - 1} - sum_{j - 1})))$$

$$P = \min_{1 \le j \le n} (\max_{j \le i < n + j} (A_i - sum_{i - 1} + sum_{j - 1}))$$

$$P = \min_{1 \le j \le n} (\max_{j \le i < n + j} (A_i - sum_{i - 1}) + sum_{j - 1})$$

。

为方便计算，设 $W_i=A_i - sum_{i - 1}$，则

$$P = \min_{1 \le j \le n} (\max_{j \le i < n + j} (W_i) + sum_{j - 1})$$

。

时间复杂度 $O(n^2)$，还是 TLE。

### 考虑使用单调队列
---

看出来了吗？这题就相当于在 $W$ 数组里寻找定长区间最大值，变成了一道模版题，可以参考模版题[P1886](https://www.luogu.com.cn/problem/P1886)。

时间复杂度降到 $O(n)$，顺利通过！

## 代码奉上

```cpp
#include<bits/stdc++.h>
using namespace std;
//不开long long见祖宗 
#define ll long long
const ll MAXN=5e5+10,MAXLL=4611686018427387903;
ll n,a[2*MAXN],b[2*MAXN],sum[2*MAXN],w[2*MAXN],q[2*MAXN],ans=MAXLL;
int main() {
	scanf("%lld",&n);
	for(int i=1; i<=n; i++) {
		scanf("%lld",&a[i]);
		a[i+n]=a[i];
	}
	for(int i=1; i<=n; i++) {
		scanf("%lld",&b[i]);
		b[i+n]=b[i];
	}
	//前缀和 
	//计算sum[]、w[] 
	for(int i=1; i<=2*n-1; i++) {
		sum[i]=sum[i-1]+b[i];
		w[i]=a[i]-sum[i-1];
	}
	//使用单调队列 
	int head=1,tail=0;
	for(int i=1; i<=n-1; i++) {
		while(w[q[tail]]<=w[i]&&head<=tail) tail--;
		q[++tail]=i;
	}
	for(int i=n; i<=2*n-1; i++) {
		while(q[head]<i-n+1&&head<=tail) head++;
		while(w[q[tail]]<=w[i]&&head<=tail) tail--;
		q[++tail]=i;
		ans=min(ans,w[q[head]]+sum[i-n]);
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：lienchan_16 (赞：0)

### 背景
本人~~这个废物~~看不懂诸位大佬的题解，于是就写了一篇自己的题解供大家参考。

###### 这题是不是应该评黄啊

# 思路
当我们想要使战斗力超过任意一项 $a_i (2\leq i \leq n)$ 时，在上一列的战斗力需求就要让 $a_{i-1}+b_{i-1}\geq a_i$。

所以从此行打怪的最小战斗力：$a_{i-1} = \max(a_{i-1},a_i-b_{i-1})$。

同理 $a_n=\max(a_n,a_1-b_n)$。

所以我们从 $a_n$ 到 $a_1$ 开始修改战斗力就行了。

补充：就算人物从此行开始打怪，因为 $b_i\geq0$，故如果改变 $a_i$，必然 $a_{i-1}\leq a_i$，在判断 $a_{i-1}$ 时必然成功，所以上述行为不影响答案的错误。

这样我们就可以输出其中需要最小战斗力的就行~~了吧~~。

输出了之后没全对，~~虽然我预料到了~~。

我们就会发现我们运行上述代码的时候只保证 $a_i$ 中最大值及以前的 $a_i$ 符合最小战斗力要求，并不是所有的均符合。

故我们再要运行一遍上述代码使得每一个 $a_i$ 都符合最小战斗力要求，输出其中最小值。

## Code
```cpp
#include<bits/stdc++.h>
#define INF 999999999
#define N 500010
using namespace std;
inline long long read(){ //快读
	long long x=0,f=1;
	char ch=getchar()/*_unlocked()*/;
	while(!isdigit(ch)){
		if(ch == '-')
			f=-1;
		ch=getchar()/*_unlocked()*/;
	}
	while(isdigit(ch)){
		x=(x << 1)+(x << 3)+(ch ^ 48);
		ch=getchar()/*_unlocked()*/;
	}
	return x*f;
}

inline void write(long long x){ //快输
	if(x<0) putchar('-'),x=-x;
	if (x>9) write(x/10);
	putchar(x%10+'0');
}
long long a[N],b[N];
int main(){
    //freopen("zxl.in","r",stdin);
	//freopen("zxl.out","w",stdout);
	long long n=read(),ans=1e9+1;
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=n;i++) b[i]=read();
	if(a[1]>a[n]+b[n]) a[n]=a[1]-b[n];
	for(int i=n;i>=2;i--){
		if(a[i]>a[i-1]+b[i-1]) a[i-1]=a[i]-b[i-1];
	}
  //运行第一次完毕
	if(a[1]>a[n]+b[n]) a[n]=a[1]-b[n];
	for(int i=n;i>=2;i--){
		if(a[i]>a[i-1]+b[i-1]) a[i-1]=a[i]-b[i-1];
	}
  //运行第二次
	for(int i=1;i<=n;i++) ans=min(a[i],ans);
	write(ans);
	//fclose(stdin);
	//fclose(stdout);
 return 0;
}


```


#### 小声补充

既然你都看到这里了，不妨看看[这题](https://www.luogu.com.cn/problem/P11788)。 

（应该有人先看这题再看它的吧...）。

---

## 作者：_MiyazonoKaori_ (赞：0)

@[yuruilin2026](https://www.luogu.com.cn/user/1294410) 和@[Hootime](https://www.luogu.com.cn/user/1275540) 两个大佬认为这是道水题，一眼秒了。
## 1. 二分（31pts）
二分初始力量值，从题目知道力量初始值 $x$ 范围为 $0\le x \le 10^9$，时间复杂度则为 $O(N \times \log(10^9))$，但题目中 $N$ 的范围为 $2 \le N \le 5 \times 10^5$，所以极端情况过不了。  
### 代码：
```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define ll long long
#define fast_gets ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define open_f_same freopen("data.in", "r", stdin);freopen("data.out", "w", stdout);
#define close_f fclose(stdin);fclose(stdout);
using namespace std;
inline int read(){
	int x = 0, f = 1;
	char ch = getchar();
	while (!isdigit(ch)){
		if (ch == '-')
			f = -1;
		ch = getchar();
	}
	while (isdigit(ch)){
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * f;
}
inline void write(int x){
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
}
int a[514514],b[514514];
int n;
bool cheek(int x){
	for(int start=0;start<n;start++){
		int fight=x;
		bool flag=true;
		for(int i=0;i<n;i++){
			int j=(i+start)%n;
			if(fight<a[j]){
				flag=false;
				break;
			}
			fight+=b[j];
		}
		if(flag==true) return true;
	}
	return false;
}
int main(){
    //fast_gets
    //open_f_same
	n=read();
	for(int i=0;i<n;i++) a[i]=read();
	for(int i=0;i<n;i++) b[i]=read();
	int low=0,hight=1000000000;
	int ans;
	while(low<=hight){
		int mid=(low+hight)/2;
		if(cheek(mid)){
			ans=mid;
			hight=mid-1;
		}else{
			low=mid+1;
		}
	}
	write(ans);
    //close_f
    return 0;
}


```
## 2. 加入前缀和预处理和预处理最大值数组
### 1. 策略：
- 比太郎选择一个起始点 $j$，按 $j,j+1,…,N$ 的顺序打怪，再回头打 $1,2,…,j−1$ 的怪物。
- 需要确保在每一步中，比太郎的力量都足够打败当前的怪物。
### 2. 优化思路：
- 使用前缀和快速计算区间和。
- 预处理最大值数组，快速查询后续部分和前部分的最小需求。
- 遍历每个起始点，计算对应的最小初始力量需求，并找到所有起始点中的最小值。
### 3. 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    vector<int> A(N), B(N);
    for (int i = 0; i < N; ++i) cin >> A[i];
    for (int i = 0; i < N; ++i) cin >> B[i];
    vector<ll> pre_sum(N + 1, 0);
    for (int i = 1; i <= N; ++i) {
        pre_sum[i] = pre_sum[i - 1] + B[i - 1];
    }
    vector<ll> left_max(N + 2, LLONG_MIN);
    left_max[N + 1] = LLONG_MIN;
    for (int j = N; j >= 1; --j) {
        ll current = A[j - 1] - pre_sum[j - 1];
        left_max[j] = max(current, left_max[j + 1]);
    }
    vector<ll> right_max(N + 2, LLONG_MIN);
    ll fight = LLONG_MIN;
    for (int i = 1; i <= N; ++i) {
        ll temp = A[i - 1] - pre_sum[i - 1];
        if (temp > fight) {
            fight = temp;
        }
        right_max[i + 1] = fight;
    }
    ll min_x = LLONG_MAX;
    for (int j = 1; j <= N; ++j) {
        ll sum_j_minus_1 = pre_sum[j - 1];
        ll max1 = sum_j_minus_1 + left_max[j];
        ll sum_b_part = pre_sum[N] - sum_j_minus_1;
        ll max2 = (j > 1) ? (right_max[j] - sum_b_part) : LLONG_MIN;
        ll x_j = max(max1, max2);
        if (x_j < min_x) {
            min_x = x_j;
        }
    }
    cout << min_x << endl;
    return 0;
}
```

### 4. 代码解释
- 前缀和预处理：
1. ```pre_sum``` 数组用于快速计算区间和。
2. ```left_max``` 数组：从后往前遍历，计算每个位置到末尾的最大值，用于后续部分的最小力量需求。
3. ```right_max``` 数组：从前往后遍历，维护当前最大值，用于前部分的最小力量需求。
- 遍历每个起始点：
1. 计算每个起始点对应的最小初始力量需求，并找到所有起始点中的最小值。

该算法的时间复杂度为 $O(N)$。

---

## 作者：Crazyouth (赞：0)

## 分析

不妨假设有两个个长度为 $2n$ 的数组，$a',b'$，分别由 $a,b$ 复制两遍得到，那么相当于主角要选其中连续的 $n$ 个怪打，于是我们把那 $n$ 个怪拿出来当做 $a,b$，就要有对于任意 $i$，$\displaystyle(\sum_{j=1}^{i-1}b_i)+x\ge a_i$，也就是对于任意 $i$，$x\ge a_i-\displaystyle(\sum_{j=1}^{i-1}b_i)$。我们考虑维护这个值，需要由某 $n$ 个怪计算出后 $n$ 个怪的最小 $x$，要支持删除一个 $a_i,b_i$，并添加一个新的。添加是好做的。删除时会发现所有的 $\displaystyle(\sum_{j=1}^{i-1}b_i)$ 都会相应地减少，也就是一个全局减，直接维护一个标记即可。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=500010;
int a[N<<1],b[N<<1],ins[N];
#define pii pair<int,int>
set<pii,greater<pii>> st;
signed main()
{
	int n,tag=0,sum=0,ans=1e18;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],a[i+n]=a[i];
	for(int i=1;i<=n;i++) cin>>b[i],b[i+n]=b[i];
	for(int i=1;i<=n;i++)
	{
		st.insert({a[i]-sum,i});
		ins[i]=a[i]-sum;
		sum+=b[i];
	}
	ans=min(ans,(*st.begin()).first);
	for(int i=1;i<n;i++)
	{
		st.erase({ins[i],i});
		tag+=b[i];
		st.insert({a[i+n]-sum,i+n});
		sum+=b[i];
		ans=min(ans,((*st.begin()).first)+tag);
	}
	cout<<ans;
}

---

## 作者：DFM_O (赞：0)

## [P11663 题目](https://www.luogu.com.cn/problem/P11663)

### 解题思路
令 $f_{i,j}$ 等于若选择从 $i$ 开始打怪，打败怪物 $j$ 所需的最小初始力量（不考虑之前的怪物是否可以打败）。

不难发现，若选择从 $i$ 开始打怪，当我们开始打怪物 $j$ 时，通过打怪获得的力量为
$$\sum^{j+n\times[j<i]-1}_{k=i}B_{k\bmod n+n\times[k=n]}$$

所以 $f_{i,j}$ 即为 $A_j$ 减去上述式子，于是易知当 $i\not=j$ 时 $f_{i+1,j}=f_{i,j}-B_i$，当 $i=j$ 时 $f_{i,j}=\sum_{k\not=i}B_k$。

可以发现 $\max_{j=1}^n f_{i,j}$ 的值即为选择从 $i$ 开始打怪时初始力量 $j$ 的最小值，线段树维护即可。

### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int b1[500001],b2[500001],s[500001],a[1000001],tr[1000001<<2],ma[1000001<<2],zhma[1000001<<2];
void b(int l,int r,int w)
{
	if(l==r)
	{
		tr[w]=a[l];
		return;
	}
	int mid=(l+r)/2;
	b(l,mid,2*w);
	b(mid+1,r,2*w+1);
	tr[w]=max(tr[2*w],tr[2*w+1]),zhma[w]=1e18+1;
}
void pud(int w)
{
	if(zhma[w]!=1e18+1)
	{
		zhma[w*2]=zhma[w],tr[w*2]=zhma[w],ma[w*2]=0;
		zhma[w*2+1]=zhma[w],tr[w*2+1]=zhma[w],ma[w*2+1]=0,zhma[w]=1e18+1;
	}
	ma[w*2]+=ma[w],ma[w*2+1]+=ma[w];
	tr[w*2]+=ma[w],tr[w*2+1]+=ma[w],ma[w]=0;
}
void zhxg(int l,int r,int ml,int mr,int x,int w)
{
	if(mr<l||ml>r)
		return;
	if(mr>=r&&ml<=l)
	{
		tr[w]=x,ma[w]=0,zhma[w]=x;
		return;
	}
	int mid=(l+r)/2;
	pud(w);
	zhxg(l,mid,ml,mr,x,w*2),zhxg(mid+1,r,ml,mr,x,w*2+1);
	tr[w]=max(tr[2*w],tr[2*w+1]);
}
void xg(int l,int r,int ml,int mr,int x,int w)
{
	if(mr<l||ml>r)
		return;
	if(mr>=r&&ml<=l)
	{
		tr[w]+=x,ma[w]+=x;
		return;
	}
	int mid=(l+r)/2;
	pud(w);
	if(mr<l||ml>r)
		return;
	xg(l,mid,ml,mr,x,w*2),xg(mid+1,r,ml,mr,x,w*2+1);
	tr[w]=max(tr[2*w],tr[2*w+1]);
}
int chzh(int l,int r,int ml,int mr,int w)
{
	if(mr<l||ml>r)
	{
		int minn=-1e18-1;
		return minn;
	}
	if(mr>=r&&ml<=l)
		return tr[w];
	pud(w);
	int mid=(l+r)/2;
	return max(chzh(l,mid,ml,mr,w*2),chzh(mid+1,r,ml,mr,w*2+1));
}
signed main()
{
	ios::sync_with_stdio(false);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>b1[i];
	for(int i=1;i<=n;i++)
		cin>>b2[i],s[i]=s[i-1]+b2[i];
	int maxx=0;
	for(int i=1;i<=n;i++)
		a[i]=b1[i]-s[i-1],maxx=max(maxx,a[i]);;
	int minn=maxx;
	b(1,n,1);
	for(int i=2;i<=n;i++)
		xg(1,n,i,n,b2[i-1],1),xg(1,n,1,i-2,b2[i-1],1),zhxg(1,n,i-1,i-1,b1[i-1]-s[n]+b2[i-1],1),minn=min(minn,chzh(1,n,1,n,1));
	cout<<minn;
	return 0;
}
```

---

