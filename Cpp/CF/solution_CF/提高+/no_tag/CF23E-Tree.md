# Tree

## 题目描述

Recently Bob invented a new game with a tree (we should remind you, that a tree is a connected graph without cycles): he deletes any (possibly, zero) amount of edges of the tree, and counts the product of sizes of the connected components left after the deletion. Your task is to find out the maximum number that Bob can get in his new game for a given tree.

## 样例 #1

### 输入

```
5
1 2
2 3
3 4
4 5
```

### 输出

```
6```

## 样例 #2

### 输入

```
8
1 2
1 3
2 4
2 5
3 6
3 7
6 8
```

### 输出

```
18```

## 样例 #3

### 输入

```
3
1 2
1 3
```

### 输出

```
3```

# 题解

## 作者：YxYe (赞：4)

# [CF23E](https://www.luogu.com.cn/problem/CF23E)

## Pre

观察题目很容易得到一个结论：分割后每个连通块中直径长度不大于 $3$ 一定可行。因为如果出现直径大于 $3$ 的连通块，那么将它沿直径割成两部分相乘显然不劣（任取 $a,b$ 大于等于 $2$，有 $a+b\le a\times b$）。

## Sol

考虑树形 dp。对于这种祖辈间有约束关系的 dp，考虑记录子节点对父亲的依赖关系。

我们记 $f[u][i]$ 表示以 $u$ 为根的子树最多还可以使用 $i$ 个来自非本子树节点的支援的答案，此时 $0\le i\le 2$。

那么答案记录什么好呢？

假如都记录支援后将要得到的最大价值，推了半天发现很难转移。

假如都记录支援前已经得到的最大价值，貌似也不好做。

于是我们可以两者结合，同时为了方便结点知道孙子的约束，我们记录最多的支援数：

- $f[u][1]$ 表示以 $u$ 为根的子树**最多**使用 $1$ 个支援组成连通块**将要**得到的最大贡献。

- $f[u][2]$ 表示以 $u$ 为根的子树**最多**使用 $2$ 个支援组成连通块**已经**得到的最大贡献。

- $f[u][0]$ 没有将要，所以只能已经。

如何转移呢？（记 $v$ 为 $u$ 的子节点）

- 对于 $f[u][2]$，显然它是所有 $f[v][0]$ 的乘积。

- 对于 $f[u][1]$，它可以与每个子节点连接或不连（即乘 $f[v][0]$，连通块节点数不变 或 乘 $f[v][2]$，连通块节点数 $+1$）。而通过贪心的思想我们可以知道，肯定优先选择一个大的 $f[v][2]$ 来换取节点数 $+1$ 的贡献。所以我们可以将子节点答案按照 $f[v][2]$ 降序排序，然后线性求解。

- 对于 $f[u][0]$，它同样可以与每个子节点连接或不连（同上）。同时，它也可以与它的孙子结点相连换取连通块节点数 $+1$，但是只能连一个（否则不满足直径限制），那么取最大的 $f[v][1]$ 即可。

答案就是 $f[1][0]$ 啦~

注意本题要写高精度（崩溃！！！

## Code

这里给出本蒟蒻没有高精度的又臭又长的代码~

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#define fo(i,a,b) for(int i=(a);i<=(b);i++)
#define fs(x,i,u) for(int i=x.head[u];i;i=x.nxt[i])
#define pb push_back
using namespace std;
char buf[1<<21],*p1=buf,*p2=buf;
inline int getc(){
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;
}
inline int read(){
	int x=0,f=1;char ch=getc();
	while(!isdigit(ch)){
		if(ch=='-')f=-1;
		ch=getc();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getc();
	}
	return x*f;
}
const int maxn=800+10;
int n;
struct Edge{
	int head[maxn],to[maxn<<1],nxt[maxn<<1],cnt;
	void add(int u,int v){
		to[++cnt]=v;nxt[cnt]=head[u];head[u]=cnt;
	}
}e;
#define add_e e.add
int f[maxn][3];
bool cmp2(int x,int y){
	//f[x][2]/f[x][0]>f[y][2]/f[y][0]
	return f[x][2]*f[y][0]>f[y][2]*f[x][0];
}
bool cmp1(int x,int y){
	//f[x][1]/f[x][0]>f[y][1]/f[y][0]
	return f[x][1]*f[y][0]>f[y][1]*f[x][0];
}
void dfs(int u,int fa){
	vector<int>son[maxn];
	bool leaf=1;
	f[u][2]=1;
	fs(e,i,u){
		int v=e.to[i];
		if(v==fa)continue;
		dfs(v,u);leaf=0;
		f[u][2]*=f[v][0];
		son[u].pb(v);
	}
	if(leaf){
		f[u][2]=1;
		f[u][1]=2;
		f[u][0]=1;
		return;
	}
	
	f[u][1]=2*f[u][2];
	f[u][0]=f[u][2];
	sort(son[u].begin(),son[u].end(),cmp2);
	int siz=0,val=f[u][2];
	for(int v:son[u]){
		siz++;
		val=val*f[v][2]/f[v][0];//除法抵消（偷懒
		f[u][1]=max(f[u][1],val*(siz+2));
		f[u][0]=max(f[u][0],val*(siz+1)); 
	}
	
	sort(son[u].begin(),son[u].end(),cmp1);
	f[u][0]=max(f[u][0],f[u][2]*f[son[u][0]][1]/f[son[u][0]][0]);
	
}
int main(){
	n=read();
	fo(i,1,n-1){
		int u=read(),v=read();
		add_e(u,v);
		add_e(v,u);
	}
	dfs(1,0);
	cout<<f[1][0];
	return 0;
}
```

完结撒花 * ★,°*:.☆(￣▽￣)/$:*.°★ * 。

---

## 作者：feecle6418 (赞：4)

一个简单的树形 dp 题，但是要用高精度。

设 $f_{i,j}$ 为 $i$ 的子树内的答案，$i$ 这个联通块大小为 $j$。两种转移：

- 断掉和 $y$ 这个子树间的边。$f_{i,j}=f_{i,j}\times \max f_{y,k}$。
- 连接这个子树。$f_{i,j}=\max\{\dfrac{f_{i,j-k}f_{y,k}}{k}\}$

最后让 $f_{i,j}\times j\to f_{i,j+1}$。

时间复杂度 $O(n^2B)$，$B$ 为高精度乘法复杂度。

AC 代码由于高精度的原因过长不好看，需要的话可以去[这里](https://codeforces.ml/contest/23/submission/92886021)看完整代码。这里只给出主要的 dp 部分。

```cpp
int n,cnt,h[705],size[705];
struct Edge{
	int to,next;
}e[1405];
void Add_Edge(int x,int y){
	e[++cnt]={y,h[x]},h[x]=cnt;
}
void DP(int x,int fa){
	f[x][0]=1;
	for(int i=h[x];i;i=e[i].next){
		int y=e[i].to;
		if(y==fa)continue;
		DP(y,x),size[x]+=size[y];
		Wint t=1,t2;
		for(int k=size[y];k>0;k--)t=max(t,f[y][k]*k);
		for(int j=size[x];j>=0;j--){
			t2=t*f[x][j];
			for(int k=min(j,size[y]);k>0&&j-k<=size[x]-size[y];k--)f[x][j]=max(f[x][j],f[x][j-k]*f[y][k]);
			f[x][j]=max(f[x][j],t2);
		}
	}
	for(int i=n;i>=1;i--)f[x][i]=f[x][i-1],ans=max(ans,f[x][i]*i);
	size[x]++;
}
int main(){
	scanf("%d",&n);
	for(int i=1,x,y;i<n;i++)scanf("%d%d",&x,&y),Add_Edge(x,y),Add_Edge(y,x);
	DP(1,0),writeX(ans);
	return 0;
}
```

---

## 作者：Time_tears (赞：4)

~~本题出题人站出来！！！~~

首先看完这道题大家一定会觉得这是一个树形 Dp ，事实上，它就是一个树形 Dp 。

我们设 $f_{i,j}$ 表示 以 $i$ 为根，根所在的联通块大小为 $j$ 的方案数。

再设 $g_i$ 表示 以 $i$ 为根能得到的最大分值。

然后我们就可以得出状态转移方程：$f_{i,j}=max(f_{i,j} \times g_y,\dfrac{f_{i,j-k} \times f_{y,k} \times j}{(j-k) \times k})$

然后转移走就行了，最后输出 $g_1$ 。

你以为结束了吗？~~快打高精度吧~~

---

## 作者：xindubawukong (赞：3)

退役n年的老人来写个$O(n\log{n})$的做法

在答案的联通块中，最长路径最多只有3个节点。因为如果有一条4个节点的路径的话，把它从中间劈开，一定能得到乘积更大的解。

因此，设 $f[x][0..2]$ 表示以 $x$ 为根的子树，$x$ 向上延伸 $0..2$ 长度时的最大乘积。
- 显然 $f[x][2]$ = 所有 $f[y][0]$ 的乘积
- 对于 $f[x][1]$：
	- $x$ 可以向上延伸到 $father[x]$，但不能继续延伸了。因此初始值为 $f[x][2]\times2$（增加了一个 $x$ 和 $father[x]$ 组成的联通块）。
	- 而向下可以延伸到若干个子节点。对于子节点 $y$，如果将 $y$ 放到 $x$ 的这个联通块里，相当于将原来的答案除以 $f[y][0]$，再乘以 $f[y][2]$（对 $y$ 来说是向上延伸了2步）。因此，将所有子节点按 $f[y][2] / f[y][0]$ 从大到小排序，枚举选取前 $i$ 个即可（新的联通块大小为 $i + 2$）。
- 对于 $f[x][0]$：有两种方案。一种是跟上面一样，选取若干个子节点与 $x$ 连接。另一种方案是，将 $x$ 与某个子节点 $y$ 连接，然后 $y$ 再与它的子节点连接。
	- 第一种方案，计算过程同上。但注意新的联通块大小为 $i+1$。
	- 第二种方案，显然选取 $f[y][1]/f[y][0]$ 最大的 $y$ 即可。

最后输出 $f[1][0]$。因为需要排序，所以时间复杂度 $O(n\log{n})$（还要乘上高精度复杂度）。

```cpp
void Dfs(int x, int fa) {
  for (int y : go[x]) {
    if (y == fa) continue;
    Dfs(y, x);
  }
  vector<int> a;
  for (int y : go[x]) {
    if (y == fa) continue;
    a.push_back(y);
  }
  int len = a.size();
  if (len == 0) {
    f[x][2] = 1;
    f[x][1] = 2;
    f[x][0] = 1;
    return;
  }
  std::sort(a.begin(), a.end(), [&](int x, int y) {
    // f[x][2] / f[x][0] > f[y][2] / f[y][0]
    return f[x][2] * f[y][0] > f[y][2] * f[x][0];
  });
  vector<BigInt<int, 1000>> b(len), c(len);
  b[0] = f[a[0]][2];
  for (int i = 1; i < len; i++) b[i] = b[i - 1] * f[a[i]][2];
  c[len - 1] = f[a[len - 1]][0];
  for (int i = len - 2; i >= 0; i--) c[i] = c[i + 1] * f[a[i]][0];
  f[x][2] = c[0];
  f[x][1] = 2 * f[x][2];
  f[x][0] = f[x][2];
  for (int i = 0; i < len; i++) {
    auto left = b[i];
    auto right = i == len - 1 ? 1 : c[i + 1];
    f[x][1] = max(f[x][1], left * right * (i + 3));
    f[x][0] = max(f[x][0], left * right * (i + 2));
  }
  std::sort(a.begin(), a.end(), [&](int x, int y) {
    // f[x][1] / f[x][0] > f[y][1] / f[y][0]
    return f[x][1] * f[y][0] > f[y][1] * f[x][0];
  });
  BigInt<int, 1000> t = 1;
  for (int i = len - 1; i >= 1; i--) t = t * f[a[i]][0];
  t = t * f[a[0]][1];
  f[x][0] = max(f[x][0], t);
}
```


---

## 作者：Sky_Maths (赞：2)

# 前言
个人认为这是一道比较好的贪心思想优化树形 DP 的题目，细节也不多，而且我的状态设计和其他题解也不太一样，故来写一篇题解。

UP1：发现 DP 方程存在一个错误

# 正文
## 简要题意
（虽然原本就已经很简单）

给定一棵有 $N$ 个节点的树 $(N\le 700)$，你可以删除树的**任意**条边，求最终剩下联通块的大小的**乘积**的**最大值**。
## 分析
### 最初想法
首先有一种很简单的 DP 方法。

设 $f_{u,i}$ 代表以 $u$ 为根的子树中向上提供一个 $i$ 大小的联通块的最大乘积，其中 $i$ 是可以用于合并的，即 $u$ 处在连通块中。

写出 DP 方程。
$$f_{u,i}={\max\{\prod\limits_{u\to v}}f_{v,c_v}(\sum c_v=i-1)\},i>0$$
$$f_{u,0}=\max\limits_{i>0}\{f_{u,i}\cdot i\}$$

这是 $O(n^3)$ 的，可以通过前十四个点，代码在最后，但会 TLE

于是考虑优化，发现很难优化 DP 的过程，再分析，发现最终的联通块的直径都不超过 $3$，接下来给出证明。
### 证明
对于一棵树，若不存在一条边，使得删去后两个联通块的大小分别为 $a,b$，且若 $ab\le a+b$ 时我们称这棵树为优树，而对于任意直径 $\ge 4$ 的树，必然存在一条边（直径的中间边），使得删掉后 $a,b\ge2$，而 $\forall a,b\ge 2,a+b\le ab$ 等价于 $\forall a,b\ge 2,(a-1)(b-1)\ge 1$，故原命题成立。
### 借助贪心思想优化
所以发现最终的连通块最多只有 $fa_u,u,son_u$ 这样一个三层关系。

于是 DP 状态可以这样设：
- $f_{u,0}$ 代表**向上给一个**的最大乘积
- $f_{u,1}$ 代表**恰好**的最大乘积
- $f_{u,2}$ 代表**向上拿一个**的最大乘积

### DP 方程

$$f_{u,0}=\prod_{u\to v}f_{v,1}$$

$$f_{u,1}=\max\{\text{取}i\text{个}f_{v,0}\cdot (i+1)\cdot \text{其余的 }f_{v,1},\text{取一个}f_{v,2}\cdot 2\cdot \text{其余的}f_{v,1}\}$$

$$f_{u,2}=\max\{\text{取}i\text{个}f_{v,0}\cdot(i+2)\cdot\text{其余}f_{v,1}\}$$

然后可以再利用贪心，即将 $\frac{f_{v,0}}{f_{v,1}}$ 大的放到前面取。

别忘了使用高精度。
# 代码
$O(n^3)$
```cpp
void dfs(int u,int la) {
	siz[u]=1;
	for(int v:e[u]) {
		if(v==la) continue;
		dfs(v,u);
	}
	f[u][0]=f[u][1]=1;
	for(int v:e[u]) {
		if(v==la) continue;
		siz[u]+=siz[v];
		per(i,siz[u],1) {
			f[u][i]=f[u][i]*f[v][0];
			rep(j,1,min(i,siz[v])) {
				cmax(f[u][i],f[u][i-j]*f[v][j]);
			}
		}
	}
	rep(i,1,siz[u]) cmax(f[u][0],f[u][i]*i);
}
```

AC 代码
```cpp
#include<bits/stdc++.h>
#define rep(i,l,r) for(register int i(l),i##end(r);i<=i##end;++i)
#define per(i,r,l) for(register int i(r),i##end(l);i>=i##end;--i)
#define nex(i,u) for(int i(e.head[u]);i;i=e.nxt[i])
using namespace std;
#define gc getchar
#define pc putchar
#define be begin
#define ed end
#define ci const int
inline void rd(int &x) {
	x=0; char ch=gc(); bool f=0;
	while((ch<'0'||ch>'9')&&ch!='-') ch=gc();
	if(ch=='-') f=true,ch=gc();
	while(ch<='9'&&ch>='0') x=x*10+ch-'0',ch=gc();
	if(f) x=-x;
}

ci T = 500;
ci P = 10;
struct ll {
	int a[T],len;
	ll* operator = (const int b) {
		a[len=1]=b;
		return this;
	}
}E;
void ms(ll &res) {
	rep(i,1,T-2) res.a[i+1]+=res.a[i]/P,res.a[i]%=P;
	int len=T-1;
	while(!res.a[len]) --len;
	res.len=len;
}
ll operator * (ll u,ll v) {
	ll res(E);
	rep(i,1,u.len) rep(j,1,v.len) res.a[i+j-1]+=u.a[i]*v.a[j];
	ms(res);
	return res;
}
ll operator * (ll u,int v) {
	ll res(E);
	rep(i,1,u.len) res.a[i]=u.a[i]*v;
	ms(res);
	return res;
}
bool operator < (ll u,ll v) {
	if(u.len!=v.len) return u.len<v.len;
	per(i,u.len,1) if(u.a[i]!=v.a[i]) return u.a[i]<v.a[i];
	return 0;
}
bool operator > (ll u,ll v) {
	if(u.len!=v.len) return u.len>v.len;
	per(i,u.len,1) if(u.a[i]!=v.a[i]) return u.a[i]>v.a[i];
	return 0;
}

ci N = 709;
vector<int>e[N],son[N];
int n;
ll f[N][3],F[N],G[N];
bool cmp1(int a,int b) {
	return f[a][0]*f[b][1]>f[b][0]*f[a][1];
}
bool cmp2(int a,int b) {
	return f[a][2]*f[b][1]>f[b][2]*f[a][1];
}
void cmax(ll &a,ll b) {if(a<b) a=b;}
void dfs(int u,int la) {
	son[u].push_back(0);
	for(int v:e[u]) {
		if(v==la) continue;
		dfs(v,u);
		son[u].push_back(v);
	}
	sort(son[u].be()+1,son[u].ed(),cmp1);
	F[0]=1; rep(i,1,son[u].size()-1) F[i]=F[i-1]*f[son[u][i]][0];
	G[son[u].size()]=1; per(i,son[u].size()-1,1) G[i]=G[i+1]*f[son[u][i]][1];
	f[u][1]=G[1]; f[u][2]=G[1]*2;
	rep(i,1,son[u].size()-1) {
		cmax(f[u][1],F[i]*(i+1)*G[i+1]);
		cmax(f[u][2],F[i]*(i+2)*G[i+1]);
	}
	if(son[u].size()>1) {
		sort(son[u].be()+1,son[u].ed(),cmp2);
		G[son[u].size()]=1; per(i,son[u].size()-1,1) G[i]=G[i+1]*f[son[u][i]][1];
		cmax(f[u][1],f[son[u][1]][2]*G[2]);
	}
	f[u][0]=G[1];
}
main() {
	rd(n);
	int u,v; rep(i,2,n) {
		rd(u); rd(v);
		e[u].emplace_back(v);
		e[v].emplace_back(u);
	}
	dfs(1,0);
	per(i,f[1][1].len,1) putchar(48+f[1][1].a[i]);
	return 0;
}
```

---

## 作者：__stick (赞：1)

## 题意

可以断开一棵树上的若干条边，求所有最后剩下的联通块大小的乘积的最大值。

## 思路

不难想到树上背包 $F[u][j]$ 表示在节点 $u$ 与 $u$ 父亲相连的联通块大小为 $j$ 的最大乘积（注意此时 u 所在的联通快的贡献没有被计算，因为还连在父亲节点上）。

想到状态了转移就不难了，然后就是暴力枚举子树部联通快的大小进行转移了，这个不太好描述，但是会树上背包的应该都会，不过是两个子树大小相乘，具体可以看代码。

不同的是还要考虑断开这条边的情况，也就是 $F[u][0]$ 这时候在每个节点计算完后处理就行了，就是 $\max\{F[u][i]\times i\}$ 。
## 代码
高精度就免了，只放主要程序，[完整代码](https://www.luogu.com.cn/paste/0jzjtibp)。
```cpp
int main()
{
	ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0);cout<<fixed<<setprecision(20);
	int n;cin>>n;
	vii e(n+1);
	int u,v;
	for(int i=1;i<n;i++)
	{
		cin>>u>>v,e[u].push_back(v);
		e[v].push_back(u);
	}
	vi siz(n+1);
	vector<vector<node> >F(n+1,vector<node>(n+1));
	function<void(int,int)>dfs=[&](int u,int fa)
	{
		siz[u]=1,F[u][1]=1;
		for(const int& v:e[u])
		{
			if(v==fa)continue;
			dfs(v,u);
			for(int j=siz[u];j>=0;j--)
				for(int k=siz[v];k>=0;k--)
					cmax(F[u][j+k],F[u][j]*F[v][k]);
			siz[u]+=siz[v];
		}
		for(int i=1;i<=siz[u];i++)cmax(F[u][0],F[u][i]*i);
	};
	dfs(1,0);
	cout<<F[1][0];
 	return 0;
}
```


---

