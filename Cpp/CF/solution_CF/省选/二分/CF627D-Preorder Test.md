# Preorder Test

## 题目描述

For his computer science class, Jacob builds a model tree with sticks and balls containing $ n $ nodes in the shape of a tree. Jacob has spent $ a_{i} $ minutes building the $ i $ -th ball in the tree.

Jacob's teacher will evaluate his model and grade Jacob based on the effort he has put in. However, she does not have enough time to search his whole tree to determine this; Jacob knows that she will examine the first $ k $ nodes in a DFS-order traversal of the tree. She will then assign Jacob a grade equal to the minimum $ a_{i} $ she finds among those $ k $ nodes.

Though Jacob does not have enough time to rebuild his model, he can choose the root node that his teacher starts from. Furthermore, he can rearrange the list of neighbors of each node in any order he likes. Help Jacob find the best grade he can get on this assignment.

A DFS-order traversal is an ordering of the nodes of a rooted tree, built by a recursive DFS-procedure initially called on the root of the tree. When called on a given node $ v $ , the procedure does the following:

1. Print $ v $ .
2. Traverse the list of neighbors of the node $ v $ in order and iteratively call DFS-procedure on each one. Do not call DFS-procedure on node $ u $ if you came to node $ v $ directly from $ u $ .

## 说明/提示

In the first sample, Jacob can root the tree at node $ 2 $ and order $ 2 $ 's neighbors in the order $ 4 $ , $ 1 $ , $ 5 $ (all other nodes have at most two neighbors). The resulting preorder traversal is $ 2 $ , $ 4 $ , $ 1 $ , $ 3 $ , $ 5 $ , and the minimum $ a_{i} $ of the first $ 3 $ nodes is $ 3 $ .

In the second sample, it is clear that any preorder traversal will contain node $ 1 $ as either its first or second node, so Jacob cannot do better than a grade of $ 1 $ .

## 样例 #1

### 输入

```
5 3
3 6 1 4 2
1 2
2 4
2 5
1 3
```

### 输出

```
3
```

## 样例 #2

### 输入

```
4 2
1 5 5 5
1 2
1 3
1 4
```

### 输出

```
1
```

# 题解

## 作者：skylee (赞：4)

### 题解地址：
[[CF627D]Preorder Test - skylee's Blog](http://www.cnblogs.com/skylee03/p/8986814.html)

### 题目大意：  
一个$n(n\le2\times10^5)$个结点的树，每个结点有一个权值$w_i$。可以任选一点为根，并选择一些结点交换其子结点的顺序，使得该树DFS序上第$m$个结点的权值最大。求最大权值。  

### 思路：  
二分答案$k$ ，树形DP检验可行性。  
对于以结点$x$为根的子树，用$f[x]$表示$x$的子树经过任意变换的所有DFS序中，满足$w_i\ge k$的最长前缀长度。  
若$w_x<k$，则$f[x]$显然为$0$。  
若$w_x\ge k$，则对于$x$的每个子结点$y$，若$f[y]=size[y]$，将$y$的子树插入到$x$子树DFS序的最前面仍然是合法的；而对于所有满足$f[y]<size[y]$的子结点$y$，可以选择一个$f[y]$最大的加入。考虑以$x$为根的情况，则只需要在$f[x]$上加上满足$f[y]<size[y]$的$f[y]$第二大的$f[y]$。此时不需要考虑加上的会是$x$上方的点，因为加上$x$上方的点的情况肯定能在$x$上方的点处统计到。  
时间复杂度$O(n)$。  

### 源代码：
```cpp
#include<cstdio>
#include<cctype>
#include<algorithm>
#include<forward_list>
inline int getint() {
	register char ch;
	while(!isdigit(ch=getchar()));
	register int x=ch^'0';
	while(isdigit(ch=getchar())) x=(((x<<2)+x)<<1)+(ch^'0');
	return x;
}
const int N=2e5+1;
int w[N],f[N],k,size[N],ans,root;
std::forward_list<int> e[N];
inline void add_edge(const int &u,const int &v) {
	e[u].push_front(v);
	e[v].push_front(u);
}
void dfs(const int &x,const int &par) {
	f[x]=size[x]=1;
	int max1=0,max2=0;
	for(register auto &y:e[x]) {
		if(y==par) continue;
		dfs(y,x);
		size[x]+=size[y];
		if(f[y]==size[y]) {
			f[x]+=f[y];
		} else {
			if(f[y]>max1) std::swap(f[y],max1);
			if(f[y]>max2) std::swap(f[y],max2);
		}
	}
	f[x]=w[x]<k?0:f[x]+max1;
	ans=std::max(ans,f[x]+max2);
}
inline int calc() {
	dfs(root,ans=0);
	return ans;
}
int main() {
	const int n=getint(),m=getint();
	for(register int i=1;i<=n;i++) w[i]=getint();
	for(register int i=1;i<n;i++) {
		add_edge(getint(),getint());
	}
	root=std::min_element(&w[1],&w[n]+1)-w;
	int l=*std::min_element(&w[1],&w[n]+1);
	int r=*std::max_element(&w[1],&w[n]+1);
	while(l<=r) {
		k=(l+r)>>1;
		if(calc()>=m) {
			l=k+1;
		} else {
			r=k-1;
		}
	}
	printf("%d\n",l-1);
	return 0;
}
```

---

## 作者：约瑟夫用脑玩 (赞：3)

> Stop learning useless algorithms, go and solve some problems, learn how to use binary search.

*2600

其他题解的换根呢？我不理解。

要求选 $k$ 个的判定性问题，使用二分转化为最大化问题再与 $k$ 作比较即可。

直接对值域二分和离散化后二分区别不大，故不作考虑，设当前二分出的值为 $val$。

现在要求的是：选定某点为根，向下走 $a_x\ge val$ 的点，走完一个子树才能回退，最大化能走的点数。

考虑以 $1$ 为根，做 dp 求 $f_x$ 表示子树 $x$ 内最多能走多少个 $a_x\ge val$ 的点，特殊的，当 $f_x=sz_x$ 时表示子树能走完并能返回，其中 $sz_x$ 表示子树大小。

将是否能返回分开考虑，设 $g_x$ 表示不能返回的最大值辅助转移，设 $p$ 为 $x$ 的儿子：

- $g_x=\max f_p,f_p<sz_p$
- $f_x=g_x+\sum f_p,f_p=sz_p$

这里贪心的先走能返回的再走不能返回的最大值，比较显然。

再考虑换根，以 $x$ 为根只用将其父亲 $fa_x$ 的连通块看作一个子树算入贡献即可。

设 $h_{x,p}$ 表示 $x$ 除去儿子 $p$ 的连通块最多能走多少个 $a_x\ge val$ 的点，定义基本同 $f$。

转移预处理儿子的前缀 $\max$，设为 $lmax_{x,p},rmax_{x,p}$，有：

- $h_{x,p}=f_x-g_x+\max{(lmax_{x,p},rmax_{x,p},h_{fa_x,x})},h_{fa_x,x}<n-sz_x$
- $h_{x,p}=f_x-g_x+h_{fa_x,x}+\max{(lmax_{x,p},rmax_{x,p})},h_{fa_x,x}=n-sz_x$

其中 $f_x-g_x=\sum f_p,f_p=sz_p$，意义同 $f$ 的转移，贪心先走能返回的。

注意上述算法当 $f_p=sz_p$ 时 $h_{x,p}$ 的值是错误的，但我们并不需要对这样的儿子进行换根，因为它们换根了不比 $x$ 为根的值优，故这样的 $h_{x,p}$ 并没有用。

代码：

```
int sz[Mx+5],tt[Mx+5],mxt[Mx+5],rmxt[Mx+5],almx[Mx+5];
int up[Mx+5],nex[Mx+5],lst[Mx+5];
inline int Up(int x,int y,int v)
{//向上
	int i,to,mx=0,ls=0;sz[x]=1;tt[x]=a[x]>=v;
	for(i=h[x];i;i=nxt[i])
	{
		if((to=tto[i])^y)
		{
			if(Up(to,x,v))return 1;
			sz[x]+=sz[to];lst[to]=ls;
			if(ls)nex[ls]=to;
			ls=to;
			if(tt[x])
			{
				if(tt[to]==sz[to])tt[x]+=tt[to];
				else ckmx(mx,tt[to]);
				mxt[to]=mx;
			}else mxt[to]=rmxt[to]=0;
		}
	}
	nex[ls]=0;
	almx[x]=mx;
	if(tt[x])
	for(tt[x]+=almx[x],mx=0,i=ls;i;i=lst[i])
	{
		to=i;
		if(tt[to]^sz[to])ckmx(mx,tt[to]);
		rmxt[to]=mx;
	}
	return tt[x]>=K;
}
inline int Dn(int x,int y)
{//向下（换根）
	int i,to,mx=0;
	if(tt[x])
	{
		if(up[y]==n-sz[x])
		{
			if((tt[x]+=up[y])>=K)return 1;
			tt[x]-=almx[x];
		}
		else
		{
			tt[x]-=almx[x];mx=up[y];
			if(tt[x]+Max(almx[x],up[y])>=K)return 1;
		}
	}
	for(i=h[x];i;i=nxt[i])
	{
		if((to=tto[i])^y)
		{
			if(tt[to]^sz[to])
			{
				up[x]=tt[x]+Max(mx,Max(mxt[lst[to]],rmxt[nex[to]]));
				if(Dn(to,x))return 1;
			}
		}
	}
	return 0;
}
inline int Ck(int x)
{
	if(Up(1,0,x))return 1;
	return Dn(1,0);
}
int ans;
signed main()
{//2935
	#ifndef ONLINE_JUDGE
	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
//	freopen("arrange.in","r",stdin);
//	freopen("arrange.out","w",stdout);
	#endif
	int i,l,r,mn,mx,mid;
	n=read();K=read();
	for(mn=INT_MAX,mx=INT_MIN,i=1;i<=n;i++)ckmx(mx,a[i]=read()),ckmn(mn,a[i]);
	for(i=1;i<n;i++)Ade(read(),read());
	for(l=mn,r=mx;l<=r;)
	{
		mid=(l+r)>>1;
		if(Ck(mid))ans=mid,l=mid+1;
		else r=mid-1;
	}
	writenum(ans,10);
	return output;
}
```

---

## 作者：Mobius127 (赞：2)

$Update\ in\ 5.25$ ： 补上了图和特判点。

打错一字母，调错一整年。

[题目传送门](https://www.luogu.com.cn/problem/CF627D)

题目要求最小值最大，果断二分。

接下来问题就是怎么 check 。

我们将权值 $\ge mid$ 的点全部标黑，这样就是询问能否是得 dfs 序中前 $k$ 个里面均为黑点。

不考虑换根，直接选 1 进行 dfs 。

![](https://cdn.luogu.com.cn/upload/image_hosting/7vap3fxc.png)

设 $dp_i$ 为以 $i$ 为根节点做 dfs，能使前 $dp_i$ 个全为黑的最大值。

不难想到，$dp_i$ 的构成肯定是这样的以下设 $j|((i, j) \in E\  \wedge \ j \ne f_i)$：

1. 如果 $dp_j$ 等于自身子树大小 $size_j$ 那么这颗子树跑完都不会影响结果，直接加上贡献。

1. 否则，找到最大且不满足上一条的 $dp_j$ 算进贡献里。

即 

$$dp_i=\sum_{[dp_j=size_j]} dp_j+\max_{dp_j \ne size_j } dp_j$$

同时如果只看 $i$ 这颗子树的话，该子树的贡献应该还要加上 $dp_j|dp_j \ne size_j$ 中的次大值。

比如子树 2，如果单看 $dp$ 值，那么只会选到 $2,4,7,5,8$ ，但实际上 $3$ 可以被选到，但是为了保证在 $1$ 位置 DP 时 $2$ 子树能产生贡献，我们只能在计算 $2$ 时选择 $(2,3)$ 这条边，随后“丢掉”。

这样的 DP 设计，即使最优答案的根并不是 $i$ ，$i$ 的贡献也能在其祖先计算贡献被算上。

但是这样真的算全了吗？

再看一张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/no05lfuf.png)

跟前图不一样，我们将 $12$ 点涂黑了。

这就导致在 $1$ 位置 DP 选根时，能将 $2$ 的子树 $3$ 所在的链也加进去！

也就是说，当一个节点内的白点正好是整颗树内的点时，我们能加上所有的点进行特判。

~~这就是我一直没过 test 25 的原因。~~

最后看所有子树贡献的最大值是否 $\ge k$ 即可。

单次 check 的复杂度为 $O(n)$ ，则整个程序的复杂度为 $O(n \log n)$ 。

### Code

```cpp
#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
typedef long long ll;
const int N=200005;
const int INF=1000005;
inline int read(){
	char ch=getchar();int x=0, f=1;
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return x*f;
}
struct list{
	int tot, h[N];
	int to[N*2], nxt[N*2];
	void add(int x, int y){
		to[++tot]=y, nxt[tot]=h[x];
		h[x]=tot;
	}
};
list E;
int dp[N][2], siz[N][2];
int v[N], n, k, l=1, r, ans, les, F;
void dfs(int x, int mid){
	dp[x][0]=1;
	siz[x][0]=1;siz[x][1]=(v[x]>=mid);
	int mx=0, cmx=0;
	int f=-1;
	for(int i=E.h[x]; i; i=E.nxt[i]){
		int to=E.to[i];
		if(dp[to][0]>=0){f=to;continue;} 
		dfs(to, mid);
		siz[x][0]+=siz[to][0], siz[x][1]+=siz[to][1];
	}
	for(int i=E.h[x]; i; i=E.nxt[i]){
		int to=E.to[i];
		if(to==f) continue;
		if(siz[to][1]==siz[to][0]) dp[x][0]+=siz[to][1];
		else if(dp[to][0]>=mx) cmx=mx, mx=dp[to][0];
		else if(dp[to][0]>cmx) cmx=dp[to][0];
	}
	int now=dp[x][0];
	if(v[x]<mid) dp[x][0]=0;
	else dp[x][0]+=mx;
	if(siz[x][0]-siz[x][1]==les) now+=n-siz[x][0];
	if(v[x]>=mid) ans=max(ans, now+mx+cmx);
	return ;
}
int p[N];
bool check(int x){
	ans=0;
	les=lower_bound(p+1, p+n+1, x)-p-1;
	for(int i=1; i<=n; i++) dp[i][0]=-1;
	dfs(1, x);
	return ans>=k;
}
signed main(){
	n=read(), k=read();
	for(int i=1; i<=n; i++) 
		p[i]=v[i]=read(), r=max(r, v[i]);
	sort(p+1, p+n+1);
	for(int i=1; i<n; i++){
		int x=read(), y=read();
		E.add(x, y), E.add(y, x);
	}
	while(l<=r){
		int mid=l+r>>1;
		if(check(mid)) F=mid, l=mid+1;
		else r=mid-1;
	}
	printf("%d", F);
	return 0;
}
```


---

