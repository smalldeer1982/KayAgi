# Kia Bakes a Cake

## 题目描述

给定一个长度为 $n$ 的二进制字符串 $s$ 和一棵包含 $n$ 个顶点的树 $T$。设 $k$ 为 $s$ 中字符 $\mathtt{1}$ 的数量。我们将按照以下规则构造一个包含 $k$ 个顶点的完全无向加权图：

- 对于每个满足 $s_i = \mathtt{1}$ 的 $1 \le i \le n$，创建一个标记为 $i$ 的顶点。
- 对于在上述步骤中创建的任意两个标记为 $u$ 和 $v$ 的顶点，定义它们之间的边权 $w(u, v)$ 为顶点 $u$ 和顶点 $v$ 在树 $T$ 中的距离 $^{\text{∗}}$。

一个依次访问标记为 $v_1, v_2, \ldots, v_m$ 的顶点的简单路径 $^{\text{†}}$ 被称为"优美的"，如果对于所有 $1 \le i \le m - 2$，满足条件 $2 \cdot w(v_i, v_{i + 1}) \le w(v_{i + 1}, v_{i + 2})$。换句话说，路径中每条边的权值必须至少是前一条边权值的两倍。注意对于所有 $1 \le i \le m$，必须满足 $s_{v_i} = \mathtt{1}$，否则将不存在对应标记的顶点。

对于完全无向加权图中每个标记为 $i$ 的顶点（$1 \le i \le n$ 且 $s_i = \mathtt{1}$），确定从该顶点出发的所有优美简单路径中包含顶点的最大数量。

$^{\text{∗}}$ 树中两个顶点 $a$ 和 $b$ 之间的距离等于顶点 $a$ 和顶点 $b$ 之间唯一简单路径上的边数。

$^{\text{†}}$ 路径是指顶点序列 $v_1, v_2, \ldots, v_m$，其中对于所有 $1 \le i \le m - 1$，$v_i$ 和 $v_{i + 1}$ 之间存在一条边。简单路径是指没有重复顶点的路径，即对于所有 $1 \le i < j \le m$，$v_i \neq v_j$。

## 说明/提示

在第一个测试用例中，树 $T$ 和构造的图如下所示：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2101E/928009e33bde2023c34e81d5bf874ec034e1fd20.png) 左侧是树 $T$，选中的节点标记为黄色。右侧是构造的完全图。图中展示的优美路径是 $3\rightarrow 4\rightarrow 2$。该路径是优美的，因为 $w(4, 2) = 2$ 至少是 $w(3, 4) = 1$ 的两倍。尝试用 $2\rightarrow 5$ 扩展路径是不可行的，因为 $w(2, 5) = 3$ 小于 $w(4, 2) = 2$ 的两倍。

在第二个测试用例中，树 $T$ 是一条长度为 $17$ 的简单路径。从标记为 $2$ 的顶点出发的一个优美路径示例是 $2\rightarrow 3\rightarrow 5\rightarrow 9\rightarrow 17$，其边权依次为 $1, 2, 4, 8$，每次翻倍。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
3
5
01111
1 2
2 3
3 4
4 5
17
01101011110101101
1 2
2 3
3 4
4 5
5 6
6 7
7 8
8 9
9 10
10 11
11 12
12 13
13 14
14 15
15 16
16 17
2
01
1 2```

### 输出

```
-1 3 3 3 3 
-1 5 4 -1 4 -1 5 5 5 5 -1 4 -1 5 5 -1 3 
-1 1```

# 题解

## 作者：george0929 (赞：5)

真的有 *3100 吗？

注意到答案是 $O(\log n)$ 级别的，考虑 DP 并把序列长度计入状态，由于还要记起点，倒着 DP，令 $f_{i,j}$ 表示已经确定序列后 $j$ 个值，且当前在节点 $i$，上一个点到 $i$ 的距离的最大值。

转移为 $\operatorname{dist}(i,k)\to f_{k,j+1}\ \ \ (\operatorname{dist}(i,k)\leq \frac{f_{i,j}}{2})$。

使用点分治优化转移，可以做到 $O(n\log^3 n)$。

最后 $i$ 的答案为满足 $f_{i,x}\neq 0$ 的最大的 $x$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int inf=1e9;
int n,m,s[70005],f[70005][19];
vector<int> V[70005];
struct _bit{
	int c[70005];
	void add(int p,int v){
		p=n-p;
		for(int i=p;i<=n;i+=i&-i) c[i]=max(c[i],v);
	}
	void set0(int p){
		p=n-p;
		for(int i=p;i<=n;i+=i&-i) c[i]=-inf;
	}
	int qry(int p){
		p=n-p;
		int res=-1e9; 
		for(int i=p;i>=1;i-=i&-i) res=max(res,c[i]);
		return res;
	} 
}bit;
int vis[70005],sz[70005],mxp[70005];
int sum,rt;
void getsz(int u,int fa){
	sz[u]=1;
	for(int v:V[u]){
		if(v==fa||vis[v]) continue;
		getsz(v,u);
		sz[u]+=sz[v]; 
	}
}
void getrt(int u,int fa){
	sz[u]=1,mxp[u]=0;
	for(int v:V[u]){
		if(v==fa||vis[v]) continue;
		getrt(v,u);
		sz[u]+=sz[v];
		mxp[u]=max(mxp[u],sz[v]);
	}
	mxp[u]=max(mxp[u],sum-sz[u]);
	if(!rt||mxp[u]<mxp[rt]) rt=u;
}
int k;
int dis[70005],tmp[70005],tot;
void getdis(int u,int fa){
	tmp[++tot]=u;
	dis[u]=dis[fa]+1;
	for(int v:V[u]){
		if(v==fa||vis[v]) continue;
		getdis(v,u);
	}
}
stack<int> S;
void _upd(int x){
	if(!s[x]) return;
	if(f[x][k-1]/2-dis[x]<=0) return; 
	bit.add(f[x][k-1]/2-dis[x],dis[x]);
	S.push(f[x][k-1]/2-dis[x]);
}
void trans(int u){
	dis[u]=0;
	_upd(u);
	for(int vv=0;vv<V[u].size();vv++){
		int v=V[u][vv];
		if(vis[v]) continue; 
		tot=0;
		getdis(v,u);
		for(int i=1;i<=tot;i++){
			int x=tmp[i];
			if(s[x]) f[x][k]=max(f[x][k],bit.qry(dis[x])+dis[x]);
			if(s[u]&&dis[x]<=f[x][k-1]/2) f[u][k]=max(f[u][k],dis[x]);
		}
		for(int i=1;i<=tot;i++) _upd(tmp[i]);
	}
	while(!S.empty()){
		bit.set0(S.top());
		S.pop();
	}
	for(int vv=V[u].size()-1;vv>=0;vv--){
		int v=V[u][vv];
		if(vis[v]) continue; 
		tot=0;
		getdis(v,u);
		for(int i=1;i<=tot;i++){
			int x=tmp[i];
			if(s[x]) f[x][k]=max(f[x][k],bit.qry(dis[x])+dis[x]);
		}
		for(int i=1;i<=tot;i++) _upd(tmp[i]);
	}
	while(!S.empty()){
		bit.set0(S.top());
		S.pop();
	}
}
void solve(int u){
	vis[u]=1;
	trans(u);
	getsz(u,0);
	for(int v:V[u]){
		if(vis[v]) continue;
		sum=sz[v],rt=0;
		getrt(v,u);
		solve(rt);
	}
}
void SOLVE(){
	cin>>n;
	string tmp;
	cin>>tmp;
	for(int i=1;i<=n;i++) s[i]=tmp[i-1]-'0';
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		V[u].push_back(v);
		V[v].push_back(u);
	}
	for(int i=1;i<=n;i++){
		if(s[i]) f[i][1]=2*n-1;
		else f[i][1]=0; 
	}
	for(k=2;k<=18;k++){
		for(int i=0;i<=n;i++) bit.c[i]=-inf;
		for(int i=1;i<=n;i++) vis[i]=0;
		sum=n,rt=0;
		getrt(1,0); 
		solve(rt);
	}
	for(int i=1;i<=n;i++){
		if(s[i]==0){
			cout<<-1<<" ";
			continue;
		}
		for(int j=18;j>=1;j--){
			if(f[i][j]){
				cout<<j<<" ";
				break;
			}
		}
	}
	cout<<"\n"; 
	for(int i=1;i<=n;i++){
		V[i].clear();
		vis[i]=0;
		for(int j=1;j<=18;j++) f[i][j]=0; 
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int T;cin>>T;
	while(T--) SOLVE();
} 
```

---

## 作者：Aegleseeker_ (赞：2)

由于每次路径边长翻倍，因此不难发现答案不会超过 $\log n$。考虑对其进行 dp 转移，一个朴素的想法是，令 $f_{i,j,k}$ 代表起点为 $i$，当前到了点 $j$，共经过了 $k$ 个点，路径最后一条边的最小长度。但是这样的话我们要记起点，状态过于冗余。这个时候我们可以倒着做，令路径边长不断减半，我们更改状态的定义，$f_{i,j}$ 代表倒着做到了点 $i$，当前是路径的倒数第 $j$ 个点，路径最新一条边的最大长度。这样我们就不需要记起点了，答案就是最大的 $j$ 使得 $f_{i,j}$ 不为零。

考虑如何转移 $f_{i,j}$，我们可以直接枚举 $i$ 的出边 $(i,k)$，这条边的条件即为其长度 $\le \frac{f_{k,j-1}}{2}$，此时一定存在减半的方案，因此转移可以写成 $f_{i,j}=\max\limits_{2dist(i,k)\le f_{k,j-1}}dist(i,k)$ 的形式。直接暴力转移复杂度不对，看到路径长度一类的最值或计数转移可以想到点分治。我们钦定当前分治重心 $p$ 作为 $\operatorname{lca}$，有 $f_{i,j}=\max\limits_{f_{k,j-1}-2dis(k)\ge 2dis(i)}dis(i)+dis(k)$，其中 $dis(i)$ 为 $i$ 到分治中心 $p$ 的距离。这个可以直接 BIT 解决。因此我们正反各扫一遍就可以做到不漏的对 $f$ 取最值。由于对于每个 $j$ 我们都需要做一次分治中心内部 $\log$ 的 BIT 查询，因此总复杂度是 $n\log^3 n$ 的，可过。

submission：https://codeforces.com/contest/2101/submission/330521963

---

## 作者：Unnamed114514 (赞：1)

> We aimed to kill $log(n)^3$ implementations but then ended up making some correct $log(n)^2$ ones _TLE_, and gave up!

注意到路径长度至多为 $\lfloor\log_2n\rfloor+1$。

因此定义 $f_{k,u}$ 表示从 $u$ 出发，当前遍历了 $k$ 个点，最后一条边边权的最大值。

转移是简单的：

$$f_{k,v}\gets \max\{dis(u,v)\}(2dis(u,v)\le f_{k-1,u})$$

即在 $u$ 前再导出一条边转移到 $v$。

考虑点分治，顺便求出以重心为根每个点的 $dep$。

可以把转移变成这样：

$$f_{k,v}\gets \max\{dep_u+dep_v\}(dep_u+dep_v\le \lfloor\dfrac{f_{k-1,u}}{2}\rfloor)$$

然后后面的那个不等式的限制可以转化为 $dep_v\le\lfloor\dfrac{f_{k-1,u}}{2}\rfloor-dep_u$，然后拿树状树组维护一下即可。

时间复杂度 $O(n\log^3n)$，不卡常照样过。

```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define inf 0x3f3f3f3f
using namespace std;
const int N=7e4+5;
int T,n,k,rt,cnt,mxdep,dep[N],ans[N],f[19][N],c[N],siz[N],_;
char s[N];
bool flg[N];
vector<int> G[N];
int lowbit(int x){ return x&-x; }
void add(int x,int y){ 
	if(x>mxdep){
		_=max(_,y);
		return;
	}
	x=mxdep-x+1;
	for(;x<=mxdep+1;x+=lowbit(x)) c[x]=max(c[x],y); 
}
int ask(int x){ x=mxdep-x+1; int s=_; for(;x;x-=lowbit(x)) s=max(s,c[x]); return s; }
void dfs1(int u,int fa){
	++cnt;
	siz[u]=1;
	for(auto v:G[u]){
		if(v==fa||flg[v]) continue;
		dfs1(v,u);
		siz[u]+=siz[v];
	}
}
void dfs2(int u,int fa){
	int mx=cnt-siz[u];
	for(auto v:G[u]){
		if(v==fa||flg[v]) continue;
		dfs2(v,u);
		mx=max(mx,siz[v]);
	}
	if(mx<=cnt/2) rt=u;
}
void dfs3(int u,int fa){
	mxdep=max(mxdep,dep[u]);
	for(auto v:G[u]){
		if(v==fa||flg[v]) continue;
		dep[v]=dep[u]+1;
		dfs3(v,u);
	}
}
void solve(int u,int fa){
	if(s[u]=='1'){
		int res=ask(dep[u]);
		if(res!=-inf) f[k][u]=max(f[k][u],res+dep[u]);
	}
	for(auto v:G[u]){
		if(v==fa||flg[v]) continue;
		solve(v,u);
	}
}
void update(int u,int fa){
	if(s[u]=='1'&&f[k-1][u]!=-inf){
		if(dep[u]<=f[k-1][u]/2){
			add(f[k-1][u]/2-dep[u],dep[u]),add(0,dep[u]);
			if(s[rt]=='1') f[k][rt]=max(f[k][rt],dep[u]);
		}
	}
	for(auto v:G[u]){
		if(v==fa||flg[v]) continue;
		update(v,u);
	}
}
void dfs(int u){
	cnt=0;
	dfs1(u,0),dfs2(u,0);
	mxdep=-inf,dep[rt]=0;
	dfs3(rt,0);
	_=-inf;
	for(int i=1;i<=mxdep+1;++i) c[i]=-inf;
	if(s[rt]=='1'&&f[k-1][rt]!=-inf) add(f[k-1][rt]/2,0);
	for(auto v:G[rt]){
		if(flg[v]) continue;
		solve(v,rt);
		update(v,rt);
	}
	reverse(G[rt].begin(),G[rt].end());
	_=-inf;
	for(int i=1;i<=mxdep+1;++i) c[i]=-inf;
	if(s[rt]=='1') add(f[k-1][rt]/2,0);
	for(auto v:G[rt]){
		if(flg[v]) continue;
		solve(v,rt);
		update(v,rt);
	}
	flg[rt]=1;
	for(auto v:G[rt]){
		if(flg[v]) continue;
		dfs(v);
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=n;++i) cin>>s[i];
		for(int i=1,u,v;i<n;++i){
			cin>>u>>v;
			G[u].emplace_back(v);
			G[v].emplace_back(u);
		}
		for(int i=1;i<=n;++i) if(s[i]=='1') f[1][i]=inf,ans[i]=1;
		for(k=2;k<=__lg(n)+2;++k){
			for(int i=1;i<=n;++i) f[k][i]=-inf;
			dfs(1);
			for(int i=1;i<=n;++i) if(s[i]=='1'&&f[k][i]!=-inf) ans[i]=k;
			for(int i=1;i<=n;++i) flg[i]=0;
		}
		for(int i=1;i<=n;++i)
			if(s[i]=='1') cout<<ans[i]<<' ';
			else cout<<-1<<' ';
		cout<<endl;
		for(int i=1;i<=n;++i) G[i].clear(),G[i].shrink_to_fit();
	}
	return 0;
}
```

---

## 作者：mango2011 (赞：1)

感觉比 D 简单，这题还是有点套路的。首先，一个显然的性质，就是不可能重复经过一个点。简单证明一下：

设路径长度分别是 $l_1,l_2,l_3,\dots l_n$，有 $l_i> l_1+\dots+l_{i-1}$，归纳：$l_2> l_1$，$l_i\ge2l_{i-1}> l_{i-1}+l_1+l_2+l_3+\dots+l_{i-2}$。而 $l_1+l_2+l_3+\dots+l_{n}\ge 2l_n$ 等价于 $l_n\le l_1+l_2+l_3\dots +l_{n-1}$，推出了矛盾。

然后就是比较关键的一个点，由于我们只能根据所在的点进行转移，所以状态最好设计成 $f_{u,i}$ 表示走 $i$ 步到 $u$，最后一步最大长度。其中我们把整个过程反过来了，即每一条路径的长度都不超过上一条的一半。这样子，对于一个节点 $u$，最小的 $i$ 使得 $f_{u,i}=0$ 就是答案。另一方面，由题目限制，最大长度是 $O(\log n)$ 的。令 $f_{u,0}=2n$，并从小到大枚举 $i$ 的值。

考虑转移过程，$f_{u,i}=\displaystyle\max_{2\operatorname{dis}(u,v)\le f_{v,i}}\operatorname{dis}(u,v)$。这个过程显然可以用点分治进行优化。设当前的重心是 $u$，在两棵不同子树内的点 $x,y$ 与 $u$ 的距离分别为 $x_1,y_1$，对 $x$ 进行转移，那么就等价于 $f_{x,i}=x_1+\displaystyle\max_{2(x_1+y_1)\le f_{v,i}}y_1$，$2(x_1+y_1)\le f_{v,i}$ 等价于 $y_1\le \frac{f_{v,i}}{2}-x_1$。因此，把所有点都存下来，按照子树顺序正着、反着各做一遍就可以了。线段树常数太大了，所以可以用树状数组维护以上的所有操作。单轮复杂度为 $O(n\log^2n)$。

综上，我们在 $O(n\log^3n)$ 的时间复杂度内解决了问题，官方题解有 $O(n\log^2n)$。

[提交记录](https://codeforces.com/contest/2101/submission/319375817)

---

## 作者：Mr_罗 (赞：0)

赛时这个题没做出来是不是没救了。

到现在才开始补这道题是不是更没救了。

感觉整道题都非常套路且煎蛋啊。只要你相信三只 log 跑得过去。

首先看到 $2\cdot w(v_i,v_{i+1})\le w(v_{i+1},v_{i+2})$ 就知道答案总长度不会超过 $\lfloor\log_2n\rfloor+1$ 。如果把最后一条边的长度放到 dp 状态里就太不礼貌了，因此可以立刻写出 dp 状态 $f_{i,u}$ 表示路径长度为 $i$ ，当前在 $u$ 时最后一条边长度的最小值。

然后你会发现现在的转移既不知道起点又需要考虑邻域补，于是可以立刻想到倒着考虑一条路径，限制变成 $w_i\ge 2w_{i+1}$ ，变成记最后一条边长度的最大值，每次转移向邻域内的点。

接下来就可以直接编细节了。邻域内的转移显然应该上点分治，把转移式写出来再稍作变形就是
$$
f_{i+1,v}\gets\max\left\{d_u\mid d_v\le\frac{f_{i,u}}2-d_u\right\}+d_v
$$
随便树状数组一下即可，时间复杂度 $\mathcal O(n\log^3n)$ ，在 $n\le 7\times 10^4,6s$ 的限制下跑得飞快（5561ms，有惊无险），代码也不难，核心代码 3k。

[CF AC Link](https://codeforces.com/contest/2101/submission/326511751).

---

## 作者：StayAlone (赞：0)

显然路径长度至多 $\log_2n+1$。

正常做应该是正着吧，第 $x$ 条路径的长度至少是第 $x-1$ 条的两倍。设 $f_{i, j}$ 表示以结点 $i$ 结尾，长度为 $j$，最后一条路径的最小长度。

但是把转移写出来，发现是向邻域的补集转移，不太优美。于是反过来做，第 $x$ 条路径的长度至多是第 $x-1$ 条的一半。设 $f_{i, j}$ 表示以结点 $i$ 结尾，长度为 $j$，最后一条路径的最大长度。

转移显然是 $f_{*, j-1}$ 向 $f_{*, j}$ 转移。$f_{i, j}\gets \max\limits_{2dis_{k, i}\le f_{k, j - 1}}\{dis_{k, i}\}$。

把 $x\to y$ 的转移在 $\operatorname {LCA}$ 处处理，即点分治优化 dp。钦定根时，转移可改写成 $f_{i, j}\gets dep_i+\max\limits_{dep_i\le \frac{f_{k, j - 1}}{2}-dep_k}\{dep_k\}$。

这里已经可以树状数组优化了。时间复杂度 $\mathcal O(n\log^3 n)$。

考虑用一个深度大小的数组维护 $\lfloor\frac{f_{k, j - 1}}{2}\rfloor-dep_k=i$ 时，$dep_k$ 的最大值以及其来自的子树；再记非最大值子树的最大值和来自子树。

然后再倒着用 $i+1$ 更新 $i$，得到大于等于 $i$ 的信息。实际上这里需要分讨一下证明不会出现遗漏。

查询时，要么是最大值，要么就是另一个值。

时间复杂度 $\mathcal O(n\log^2n)$。

[AC record](https://codeforces.com/contest/2101/submission/325083753)

```cpp
int n, ans[MAXN]; bool vis[MAXN]; char s[MAXN];
int maxs[MAXN], siz[MAXN], root, dp[MAXN], f[MAXN];
vector <int> lnk[MAXN];

il void add(const int &x, const int &y) {
	lnk[x].eb(y); lnk[y].eb(x);
}

il void get_root(int x, int p, int tot) {
	siz[x] = 1; maxs[x] = 0;
	for (auto v : lnk[x]) {
		if (v == p || vis[v]) continue;
		get_root(v, x, tot); siz[x] += siz[v]; 
		maxs[x] = max(maxs[x], siz[v]);
	} maxs[x] = max(maxs[x], tot - siz[x]);
	if (maxs[x] < maxs[root]) root = x;
}

int dep[MAXN], mxd;

struct node {
    int u, fru;
    int v, frv;
} val[MAXN];

vector <pii> vec;
il void dfs(int x, int p) {
    gmax(mxd, dep[x]);
    for (auto v : lnk[x]) if (v ^ p && !vis[v]) dep[v] = dep[x] + 1, dfs(v, x);
}

il void cal(int x) {
    dep[x] = mxd = 0; dfs(x, 0);
    auto update = [&](node &x, pii t) {
        if (x.u <= t.fst) {
            if (x.fru != t.snd) x.v = x.u, x.frv = x.fru;
            tie(x.u, x.fru) = t;
        } else if (x.v < t.fst && x.fru != t.snd) tie(x.v, x.frv) = t;
    };
    auto init = [&](auto self, int x, int p, int fr) -> void {
        if (s[x] == '1') {
            int now = min((f[x] >> 1) - dep[x], mxd);
            if (now >= 0) update(val[now], {dep[x], fr});
        } vec.eb(x, fr);
        for (auto v : lnk[x]) if (!vis[v] && v ^ p) self(self, v, x, fr);
    }; s[x] == '1' && (update(val[min(f[x] >> 1, mxd)], {0, x}), 0); vec.clear();
    for (auto v : lnk[x]) if (!vis[v]) init(init, v, x, v);
    rep2(i, mxd - 1, 0) update(val[i], {val[i + 1].u, val[i + 1].fru}), update(val[i], {val[i + 1].v, val[i + 1].frv});
    for (auto [x, fr] : vec) if (s[x] == '1') {
        auto p = val[dep[x]];
        gmax(dp[x], (p.fru ^ fr ? p.u : p.v) + dep[x]);
    } s[x] == '1' && (gmax(dp[x], val[0].u), 0);
    rep1(i, 0, mxd) val[i] = {-inf, -1, -inf, -1};
}

il void solve(int x) {
	vis[x] = true; cal(x);
	for (auto v : lnk[x]) if (!vis[v]) {
		root = 0; get_root(v, 0, siz[v]); solve(root);
	}
}

int main() {
    for (int T = read(); T--; ) {
        read(n); scanf("%s", s + 1);
        rep1(i, 2, n) add(read(), read());
        rep1(i, 1, n) s[i] == '1' ? (f[i] = n << 1, ans[i] = 1) : (f[i] = 0, ans[i] = -1);
        rep1(i, 1, __lg(n) + 1) {
            rep1(j, 1, n) dp[j] = vis[j] = 0, val[j] = {-inf, -1, -inf, -1};
            maxs[root = 0] = n + 1; get_root(1, 0, n);
            solve(root); swap(f, dp);
            rep1(j, 1, n) if (f[j]) ans[j] = i + 1;
        }
        rep1(i, 1, n) printf("%d ", ans[i]); puts("");
        rep1(i, 1, n) lnk[i].clear();
    }
    return 0;
}
```

由于要维护的东西太多，树状数组 $\log dep$ 还跑不满，所以根本卡不掉。

---

## 作者：KSCD_ (赞：0)

### 题意

给定一棵 $n$ 个点的树和长为 $n$ 的 $01$ 串 $s$。称长为 $m$ 的序列 $a$ 合法，当且仅当 $a$ 中元素两两不同，$\forall i\in[1,m],a_i\in[1,n],s_{a_i}=1$，且 $\forall i\in [1,m-2],2d(a_i,a_{i+1})\le d(a_{i+1},a_{i+2})$，其中 $d(u,v)$ 表示树上 $u,v$ 间简单路径的边数。对于 $x\in[1,n]$ 分别求 $a_1=x$ 时，合法 $a$ 序列的最大长度。$n\le 7\times 10^4$。

### 题解

首先看到 $2d(a_i,a_{i+1})\le d(a_{i+1},a_{i+2})$ 可以很自然地注意到每次路径长度至少翻倍，而路径长度不会超过 $n-1$，因此序列长度不会超过 $O(\log n)$，或许会对本题有帮助。

之后考虑使用 DP 解决该问题，注意到 DP 状态中只能记录开头或结尾元素，难以限制两两不同。然而仔细考虑 $d$ 的限制后发现，若两次经过点 $x$，设第二个 $x$ 的前缀为 $y$，则有 $d(y,x)>d(x,p_1)+d(p_1,p_2)+\cdots+d(p_k,y)$，然而 $d(y,x)$ 是 $y\to x$ 的唯一最短路径，不可能存在比其长度更短的，因此序列合法时不可能存在相同元素，故可以忽略该限制。

因此 DP 就是可行的了，最朴素的 DP 状态为 $f_{x,i,j}$ 表示 $a_1=x$，结尾为 $i$ 且最后一条路径长度为 $j$ 的最长合法序列长度。然而容易想到 $x$ 这一维并不必要，可以将最终的序列倒过来考虑，设 $f_{i,j}$ 表示开头为 $i$，第一条路径长度为 $j$ 的最长合法序列长度，通过在开头加元素来转移，状态数压缩到了 $O(n^2)$，但还是难以接受。

这时想起答案不会超过 $O(\log n)$，因此 DP 值不会超过 $O(\log n)$。考虑将 DP 值和状态互换，显然序列长度相同时第一条路径越长越优。因此设 $f_{i,x}$ 表示开头为 $i$，长为 $x$ 的合法序列中第一条路径的最大长度，这样状态数就变成 $O(n\log n)$ 的了。

之后考虑转移，$f_{j,x+1}\leftarrow d(i,j)$ 需要满足 $2d(i,j)\le f_{i,x}$。考虑枚举 $x$ 进行 $O(\log n)$ 轮转移，并使用点分治优化，即在分治中心处转移所有路径经过中心的 $(i,j)$ 对。则 $i$ 转移到 $j$ 的值为 $d_i+d_j$，有限制 $2(d_i+d_j)\le f_{i,x}$，拆开得到 $2d_i-f_{i,x}\le -2d_j$，这里 $d_x$ 为深度。因此以 $2d-f$ 为下标，用树状数组记录前缀 $d_i$ 的最大值即可进行转移。这里需要在点分治处理时正反跑两遍，总时间复杂度 $O(n\log^3 n)$，分别来自状态数、点分治和树状数组，在 6s 的时限下已经可以通过，[代码](https://codeforces.com/contest/2101/submission/319606177)。

考虑能否优化到 $O(n\log^2n)$，发现正反跑两遍的过程实际上是把 $p_i\ne p_j$ 的限制拆成了 $p_i<p_j$ 或 $p_i>p_j$，其中 $p_x$ 表示 $x$ 所在的分治中心子树。如果能将所有子树的信息预处理到一起，查询时快速去掉 $p_j$ 子树内的信息并转移，就能降低复杂度。考虑把上式整个取反为 $f_{i,x}-2d_i\ge 2d_j$，在每个下标上维护 $d$ 的最大值和所属子树不同的次大值，并预处理出后缀信息。由于最大值和次大值信息合并可以 $O(1)$ 实现，整个后缀处理仍是线性的，查询时取子树外的最大值即可。

注意到查询的 $d_j$ 不会超过 $siz_u$，因此把超过 $2siz_u$ 的下标上的值均赋到 $2siz_u$ 上即可，数组大小得到保证，总时间复杂度 $O(n\log^2n)$，[代码](https://codeforces.com/contest/2101/submission/319610589)。由于常数较大，实际并没有比原来快多少。事实上限制式可以整体除以 $2$，得到 $\lfloor \frac{f_{i,x}-2d_i}2\rfloor\ge d_j$，可以通过数组大小少个 $2$ 的常数，然而[也没快多少](https://codeforces.com/contest/2101/submission/319612293)，可能是实现得比较粗糙了。

---

