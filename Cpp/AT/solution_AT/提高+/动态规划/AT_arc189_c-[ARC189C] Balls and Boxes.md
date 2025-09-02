# [ARC189C] Balls and Boxes

## 题目描述

有 $N$ 个箱子，对应编号 $i = 1, 2, \ldots, N$。每个箱子中，编号为 $i$ 的箱子包含 $A_i$ 个红球和 $B_i$ 个蓝球。

另外，给定两个排列 $P = (P_1, P_2, \ldots, P_N)$ 和 $Q = (Q_1, Q_2, \ldots, Q_N)$，它们都是数列 $(1, 2, \ldots, N)$ 的不同排列组合。

高桥君可以任意次（包括零次）执行以下操作：

1. 选择一个箱子 $i$，满足 $1 \leq i \leq N$，将其中所有的球拿出来。
2. 把手中所有的红球放入第 $P_i$ 个箱子。
3. 把手中所有的蓝球放入第 $Q_i$ 个箱子。

高桥君的目标是使得在第 $X$ 个箱子以外的所有箱子中都没有球。请判断能否通过上述操作实现这个目标，如果可以，请给出实现这个目标所需的最小操作次数；如果不可能，则输出 `-1`。

## 样例 #1

### 输入

```
5 3
0 1 0 1 0
0 0 1 0 1
4 1 2 3 5
3 4 5 2 1```

### 输出

```
4```

## 样例 #2

### 输入

```
5 3
0 0 0 0 0
0 0 0 0 0
4 1 2 3 5
3 4 5 2 1```

### 输出

```
0```

## 样例 #3

### 输入

```
2 2
1 1
1 1
1 2
1 2```

### 输出

```
-1```

## 样例 #4

### 输入

```
10 10
0 0 0 0 0 0 1 0 1 0
0 0 0 0 1 1 0 0 1 0
1 4 9 5 8 2 3 6 10 7
7 4 9 10 6 3 1 2 8 5```

### 输出

```
8```

# 题解

## 作者：xxseven (赞：6)

先考虑只有红球的情况。

此时，对盒子 $i$ 进行操作等价于把盒子 $i$ 中的红球移至盒子 $p_i$。

我们用图上的边来描述这种移动关系，因为所有点的入度和出度均为 $1$，所以最后的图形成多个环。显然，只有 $X$ 所在的环需要考虑，其他环若存在球则必然无解。

又因为对盒子 $X$ 的操作显然不优，我们把这条边断开，有用的移动关系形成一条链。

那么对于一种颜色的情况，只需要从链上最深的有球的节点传到上面即可。

扩展到两种颜色，对这两种颜色都存在一个必须执行的操作序列。问题转化为给你两个元素各不重复的序列，找到最短的序列使得两个序列均为它的子序列。

这个问题很简单，两个序列总长减去它们的 $\operatorname{LCS}$ 长度即为答案。

> 感性理解：  
> 考虑两个串的匹配进度，一般情况下每增加一个数会令其中一个序列匹配一位，而当两个串下一位相同时可以都匹配一位。    
> 这相当于取出两个序列的一个公共子序列，每一个在公共子序列上的数会为我们节省一位。

由于每个序列内元素各不重复，使用 [P1439 【模板】最长公共子序列](https://www.luogu.com.cn/problem/P1439)中的方法求解即可。

[AC Link](https://atcoder.jp/contests/arc189/submissions/60592383).

希望这篇题解能够帮到你！

---

## 作者：Richard_Whr (赞：1)

如果只有一种球，那么很容易想到建图：$i \rightarrow p_i$。

由于是排列因此一定是若干个环，如果除了 $X$ 所在的环之外还有那肯定无解。

显然 $X$ 不会给到别人，在这里断开，找到第一个有球的位置开始一直传给 $X$ 就是最优解。

如果有两种球，我们可以先分开考虑，一定是两条有向链在传递。

最差最差我们可以先不管另一条链，先做完一条链再做下一条。

但实际上如果两个有一个子序列是相同的话，我们可以按照这个子序列的顺序将两个序列划分为若干阶段，并行相同的阶段并在子序列的位置减少一次开销。

因此最终的结论是两端序列的总长减去公共子序列部分。

排列最长公共子序列可以转成 LIS 做。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
int p[N],q[N],pos[N];
int a[N],b[N];
int sa,sb;
int n,P;
vector<int> A,B;
int tr[N];
int lowbit(int x)
{
	return x&-x;
}
void add(int x,int c)
{
	for(int i=x;i<=n;i+=lowbit(i)) tr[i]=max(tr[i],c);
}
int sum(int x)
{
	int res=0;
	for(int i=x;i;i-=lowbit(i)) res=max(res,tr[i]);
	return res;
}

signed main()
{
	cin>>n>>P;
	for(int i=1;i<=n;i++) cin>>a[i],sa+=a[i];
	for(int i=1;i<=n;i++) cin>>b[i],sb+=b[i];
	for(int i=1;i<=n;i++) cin>>p[i];
	for(int i=1;i<=n;i++) cin>>q[i];
	
	if(!sa && !sb) cout<<"0\n",exit(0);
	
	int u=P;
	do
	{
		if(u!=P) A.push_back(u);
		sa-=a[u];
		u=p[u];
	}while(u!=P);
	do
	{
		if(u!=P) B.push_back(u);
		sb-=b[u];
		u=q[u];
	}while(u!=P);
	
	reverse(A.begin(),A.end()),reverse(B.begin(),B.end());
	while(A.size() && !a[A.back()]) A.pop_back();
	while(B.size() && !b[B.back()]) B.pop_back();
	
	if(sa||sb) cout<<"-1",exit(0);
	for(int i=0;i<A.size();i++) pos[A[i]]=i+1;
	for(int i=0;i<B.size();i++) B[i]=pos[B[i]];
	int res=0;
	for(int i=0;i<B.size();i++)
	{
		if(!B[i]) continue;
		int f=sum(B[i])+1;
		add(B[i],f);
		res=max(res,f);
	}
	cout<<A.size()+B.size()-res<<"\n";
	
	return 0; 
}
```

---

## 作者：Jerrywang09 (赞：0)

球沿着排列的指引移动，容易想到建图 $G_1,G_2$，$G_1$ 中连边 ${i,p_i}$，$G_2$ 中连边 ${i,q_i}$。由于排列的性质，图的形状是若干个环。最终球汇聚到 $x$，因此 $x$ 的出边是没有意义的。那么 $x$ 所在的环断掉一条边，成了一条链。

先考虑在这两张图上剥离没有意义的结点。考虑拓扑排序的方式，先把链最外层的没有球的盒子去掉。然后可以判无解：如果在 $x$ 所在的链以外的连通块内还存在有球的盒子，则显然无法将所有球汇聚到 $x$。

考虑如何计算答案。根据拓扑序可以抽出两条链的序列。设两个序列形如 $a_1,a_2,\cdots,a_{n_1}$ 和 $b_1,b_2,\cdots,b_{n_2}$。$a$ 的实际意义是：把盒子 $a_1$ 上的红球向 $a_2$ 移动，把盒子 $a_2$ 上的红球向 $a_3$ 移动……把盒子 $a_{n_1}$ 上的红球向 $x$ 移动。序列 $b$ 同理。为了使答案最小，两个序列应该尽可能多地有“同步操作”，这启发我们想到最长公共子序列。又因为两个序列内都没有重复元素，此问题可以转化为最长上升子序列问题，详见[此模板题](/problem/P1439)。使用二分或树状数组优化即可做到 $O(n\log n)$。最终答案是 $n_1+n_2-\operatorname{lcs}(a, b)$。

```cpp
// [ARC189C] Balls and Boxes
#include <cstdio>
#include <iostream>
#include <vector>
#define ll long long
#define rep(i, s, t) for(int i=s; i<=t; ++i)
#define debug(x) cerr<<#x<<":"<<x<<endl;
#define siz(x) (int)x.size()
const int N=200010;
using namespace std;
char buf[1<<21], *p1=buf, *p2=buf;
#define gc() (p1==p2 && (p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
inline int read()
{
    int x=0, f=1; char c=gc();
    while(c<'0' || c>'9') c=='-' && (f=-1), c=gc();
    while('0'<=c && c<='9') x=(x<<3)+(x<<1)+c-'0', c=gc();
    return x*f;
}

int n, x, a[N], b[N], p[N], q[N], ord[N];
vector<int> g1[N], g2[N];
inline void add(vector<int> g[], int u, int v) {g[u].push_back(v);}
int deg[N]; bool vis[N];
vector<int> topo(vector<int> g[], int a[])
{
    int q[N], hh=1, tt=0;
    rep(i, 1, n) deg[i]=vis[i]=0;
    rep(u, 1, n) for(int v:g[u]) deg[v]++;
    rep(i, 1, n) if(!deg[i] && !a[i]) q[++tt]=i;
    while(hh<=tt)
    {
        int u=q[hh++]; vis[u]=1;
        for(int v:g[u])
        {
            deg[v]--;
            if(!deg[v] && !a[v]) q[++tt]=v;
        }
    }
    hh=1, tt=0; vector<int> res;
    rep(i, 1, n) if(!deg[i] && !vis[i]) q[++tt]=i;
    while(hh<=tt)
    {
        int u=q[hh++]; vis[u]=1;
        if(u!=x) res.push_back(u);
        for(int v:g[u])
        {
            deg[v]--;
            if(!deg[v]) q[++tt]=v;
        }
    }
    rep(i, 1, n) if(a[i] && !vis[i]) puts("-1"), exit(0);
    return res;
}
int f[N], c[N];
void modify(int x, int y)
{
    for(x++; x<N; x+=x&-x) c[x]=max(c[x], y);
}
int query(int x)
{
    int res=0;
    for(x++; x; x-=x&-x) res=max(res, c[x]);
    return res;
}

int main()
{
#ifdef Jerrywang
    freopen("E:/OI/in.txt", "r", stdin);
#endif
    n=read(), x=read();
    rep(i, 1, n) a[i]=read();
    rep(i, 1, n) b[i]=read();
    rep(i, 1, n)
    {
        p[i]=read();
        if(i!=x) add(g1, i, p[i]);
    }
    rep(i, 1, n)
    {
        q[i]=read();
        if(i!=x) add(g2, i, q[i]);
    }
    auto arr1=topo(g1, a);
    rep(i, 0, siz(arr1)-1) ord[arr1[i]]=i+1;
    auto arr2=topo(g2, b);
    int res=0;
    rep(i, 0, siz(arr2)-1)
    {
        int x=arr2[i];
        if(!ord[x]) continue;
        x=ord[x];
        f[i]=query(x-1)+1;
        res=max(res, f[i]);
        modify(x, f[i]);
    }
    printf("%d", siz(arr1)+siz(arr2)-res);

    return 0;
}
```

---

## 作者：RAND_MAX (赞：0)

场上冲了十年没冲出来，赛后补一发题解。

我们不妨将两种颜色分开考虑，这里以红色为例。

我们考虑从 $i$ 向 $p_i$ 连一条有向边，由于 $p$ 是排列，所以连边以后的图是由若干个环组成的，环内点可达，环外点互不可达。不妨设 $X$ 所在的环为 $S$。

显然地，若是存在一个点满足 $i\notin S$ 且 $a_i\neq0$，则必然无解，因为 $i$ 与 $X$ 不可达。反之，所有含有红球的点全在 $S$ 上。我们发现若是从 $X$ 到 $p_X$ 显然不优，所以我们可以把 $S$ 破成一条以 $X$ 结尾的链。

此时我们称链开头的点深度为 $1$，点 $X$ 深度为 $|S|$，则我们只需找到一个深度最小的有红球的点 $i$ 即可，这样 $i\to p_i\to p_{p_i}\to\dots\to X$ 的操作步骤显然是最优的，我们称上述操作序列为 $A$。

同理，我们对蓝球进行类似的操作，处理出操作序列 $B$。此时，最终的答案显然为 $|A|+|B|-|\operatorname{LCS}(A,B)|$，因为能一起操作尽量一起操作。

对于 $\operatorname{LCS}(A,B)$ 的处理，由于 $A$ 与 $B$ 的元素均各不相同，故可以类似 [P1439](https://www.luogu.com.cn/problem/P1439) 进行处理，时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define pb push_back
//char buf[1<<20],*p1,*p2;
//#define gc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?EOF:*p1++)
#define int long long
#define gc getchar
#define R read()
using namespace std;
int read()
{
	int x=0,f=1;
	char c=gc();
	while(c>'9'||c<'0'){if(c=='-') f=-1;c=gc();}
	while(c>='0'&&c<='9') x=(x<<1)+(x<<3)+c-48,c=gc();
	return x*f;
}
void write(int x,char xx)
{
	static int st[35],top=0;
	if(x<0){x=-x;putchar('-');}
	do
	{
		st[top++]=x%10,x/=10;
	}while(x);
	while(top) putchar(st[--top]+48);
	putchar(xx);
}
#define N 200010
int n,x,a[N],b[N],p[N],q[N],suma,sumb,sa,sb,f[N],pp[N],tot;
vector<int>aa,bb;
#define lb (x&-x)
int s[N];
void add(int x,int y)
{
	while(x<=n) s[x]=max(s[x],y),x+=lb;
}
int que(int x)
{
	int su=0;
	while(x) su=max(su,s[x]),x-=lb;
	return su;
}
int solve(vector<int>a,vector<int>b)
{
	int n=a.size(),m=b.size(),len=0;
	for(int i=0;i<n;i++) pp[a[i]]=i+1;
	for(int i=0,x;i<m;i++) b[i]=pp[b[i]];
	for(int i=0,x;i<m;i++)
	{
		if(!b[i]) continue;
		x=que(b[i])+1,add(b[i],x),len=max(len,x);
	}
	return n+m-len;
}
signed main()
{
	n=R,x=R;
	for(int i=1;i<=n;i++) a[i]=R,sa+=a[i];
	for(int i=1;i<=n;i++) b[i]=R,sb+=b[i];
	for(int i=1;i<=n;i++) p[i]=R;
	for(int i=1;i<=n;i++) q[i]=R;
	int u=x;
	do aa.pb(u),suma+=a[u],u=p[u];
	while(u!=x);
	u=x;
	do bb.pb(u),sumb+=b[u],u=q[u];
	while(u!=x);
	if(suma!=sa||sumb!=sb) return write(-1,'\n'),0;
	reverse(aa.begin(),aa.end()),reverse(bb.begin(),bb.end());
	aa.pop_back(),bb.pop_back();
	while(aa.size()&&!a[aa.back()]) aa.pop_back();
	while(bb.size()&&!b[bb.back()]) bb.pop_back();
	write(solve(aa,bb),'\n');
 	return 0;
}


```

---

## 作者：Iniaugoty (赞：0)

### [ARC189C Balls and Boxes](/problem/AT_arc189_c)

直觉上 $i \to p _ i$ 先建个图，得到一堆环。

如果在 $x$ 的环之外，有一个 $i$ 使 $a _ i = 1$，它无论如何也转移不到 $x$ 上，此时无解。

否则，可以看作整个图是一个大环。

最优策略相当于，从 $x$ 后面把环断掉，然后从第一个 $a _ i = 1$ 的 $i$ 开始，一路传递到 $x$。这构成了一个操作序列，相对顺序是不能够改变的。

那再 $i \to q _ i$ 建个图，做跟上面一模一样的东西。

于是得到了两个操作序列。

需要求出一个新的序列，使得两个序列都是新序列子序列，并使这个新序列长度最小。

显然让两个序列共同占有的越多越好，即共用一个最长公共子序列。

$O(n \log n)$ 求最长公共子序列即可，[代码](https://atcoder.jp/contests/arc189/submissions/60646853)。

---

