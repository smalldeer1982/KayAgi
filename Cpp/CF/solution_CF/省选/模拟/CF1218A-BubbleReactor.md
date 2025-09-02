# BubbleReactor

## 题目描述

你负责``BubbleReactor``。它由$n$根连接在$n$根电线上的``BubbleCore``组成。每个电线连接两个不同的``BubbleCore``。没有一条以上电线连接的``BubbleCore``。

你的任务是通过启动每一个``BubbleCore``来启动``BubbleReactor``。为了启动``BubbleCore``，它需要从已启动的直接连接的``BubbleCore``接收电源。但是，您可以手动启动一个``BubbleCore``而不需要电源。保证所有``BubbleCore``都能启动。

在每个``BubbleCore``启动之前，它的电位是根据它所能启动的``BubbleCore``数量计算的（直接连接到它的未启动的``BubbleCore``数量、间接连接它的未启动的``BubbleCore``数量和它自己）

启动``BubbleReactor``，使所有``BubbleCore``电位的总和达到最大。

## 说明/提示

如果我们先启动``BubbleCore`` $8$，然后打开``BubbleCore`` $7$，$2$，$1$，$3$，$0$，$9$，$4$，$5$，$6$，我们得到$10+9+8+7+6+5+1+3+1+1=51$的电位值。

## 样例 #1

### 输入

```
10
0 1
0 3
0 4
0 9
1 2
2 3
2 7
4 5
4 6
7 8
```

### 输出

```
51
```

# 题解

## 作者：Inui_Sana (赞：2)

虚高 *2800。放模拟赛 T2 人均切了。

先想树的情况怎么做。枚举每个起点，剩下的贡献就是定值。求这个值可以钦定 $1$ 为根求出所有的 $siz$，然后枚举 $i$ 为起点，以 $i$ 为起点的答案就是 $\sum siz_i$ 加上 $i$ 到 $1$ 路径上，不含 $1$ 的所有点的 $\sum_j n-2\times siz_j$。

然后放到基环树上，发现需要注意环的情况，在一个环上先往一个方向走和另一个方向的贡献是不一样的。发现可以通过一个环上的区间 dp 解决。

对于环上一个点 $i$ 的贡献，我们只考虑一个在环上，且不在起点所对应环上的点且不为 $i$ 的点 $j$，当染黑 $j$ 时，$i$ 造成的贡献。

设环上点编号为 $0,1,\cdots ,k-1$，对应点分别为 $a_0,a_1,\cdots,a_{k-1}$,$dp_{i,j}$ 为环上编号为 $i$ 的点开始的一段长为 $j$ 的区间的最大贡献，则有 $dp_{i,j}=\max(dp_{i,j-1}+(j-2)\times siz_{a_{i+j-1}},dp_{(i+1)\bmod k,j-1}+(j-2)\times siz_{a_i})$。其中 $siz$ 是将在环上的点视为根的 $siz$。

初始值 $dp_{i,1}$ 可以根据上面计算树的方法，得到以 $i$ 为根的子树内每个点为起点的答案，再取 $\max$。

发现空间会炸，于是滚动一下。能过。$O(n^2)$。

code：

```cpp
int n,m;
int tot,head[N];
struct node{int to,nxt;}e[N<<1];
il void add(int u,int v){e[++tot]={v,head[u]},head[u]=tot;}
namespace s1{
	int siz[N],fa[N];
	void dfs1(int u,int f){
		siz[u]=1,fa[u]=f;
		go(i,u){
			int v=e[i].to;
			if(v==f)continue;
			dfs1(v,u),siz[u]+=siz[v];
		}
	}
	void solve(){
		dfs1(1,0);
		int sum=0;
		rep(i,1,n)sum+=siz[i];
		int ans=0;
		rep(i,1,n){
			int x=sum,u=i;
			while(u!=1)x+=n-2*siz[u],u=fa[u];
			ans=max(ans,x);
		}
		printf("%d\n",ans);
	}
}
namespace s2{
	int k,cyc,siz[N],dep[N],fa[N],dp[N][2],id[N];
	bool vis[N],inc[N];
	vector<int> g;
	void dfs1(int u,int f){
		vis[u]=1,dep[u]=dep[f]+1,fa[u]=f;
		go(i,u){
			int v=e[i].to;
			if(vis[v]){
				if(v!=f)cyc=(i+1)/2;
				continue;
			}
			dfs1(v,u);
		}
	}
	void find_cyc(int u,int v){
		vector<int> h;
		if(dep[u]<dep[v])swap(u,v);
		while(dep[u]>dep[v])g.eb(u),u=fa[u];
		while(u!=v)g.eb(u),h.eb(v),u=fa[u],v=fa[v];
		g.eb(u);
		while(h.size())g.eb(h.back()),h.pop_back();
	}
	void dfs2(int u,int f){
		siz[u]=1,fa[u]=f;
		go(i,u){
			int v=e[i].to;
			if(v==f||inc[v])continue;
			dfs2(v,u),siz[u]+=siz[v];
		}
	}
	void solve(){
		dfs1(1,0),find_cyc(e[cyc*2-1].to,e[cyc*2].to);
		for(int i=0;i<(int)g.size();i++)inc[g[i]]=1,id[g[i]]=i;
		for(int i:g)dfs2(i,0);
		k=g.size();int sum=0;
		rep(i,1,n)sum+=siz[i];
		rep(i,1,n){
			int x=sum,u=i;
			while(!inc[u])x+=n-2*siz[u],u=fa[u];
			dp[id[u]][1]=max(dp[id[u]][1],x+n-siz[u]);
		}
		rep(len,2,k){
			int p=len&1;
			rep(i,0,k-1)dp[i][p]=0;
			rep(i,0,k-1){
				int j=(i+len-1)%k;
				dp[i][p]=max(dp[i][p^1]+siz[g[j]]*(len-2),dp[(i+1)%k][p^1]+siz[g[i]]*(len-2));
			}
		}
		int ans=0;
		rep(i,0,k-1)ans=max(ans,dp[i][k&1]);
		printf("%d\n",ans);
	}
}
void Yorushika(){
	scanf("%d",&n);
	rep(i,1,n){
		int u=read()+1,v=read()+1;
		add(u,v),add(v,u);
	}
	s2::solve();
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

## 作者：EuphoricStar (赞：2)

虚高 *2800。放模拟赛 T2 人均切了。

考虑拎出环上的点，每个点下面都挂了一棵树。

那么可以预处理出每棵树从一个点开始染黑，这棵树对答案的贡献。因为一棵树染了一个点就只能去染子树了，所以这个贡献是固定的，用换根 dp 求即可。

那么我们现在可以在环上选择一个起点，每次可以把左端点或右端点往外拓展 $1$。拓展的贡献就是除了已经拓展的点外其他点挂的树的 $sz$ 之和，加上要拓展的点的所有子树 $sz$ 和。

套路区间 dp 即可。设 $f_{i, j}$ 为已经拓展了环上在 $[i, j]$ 中的点即可。注意因为是个环所以 $i > j$ 时 $f_{i, j}$ 表示已经拓展了环上在 $[i, m] \cup [1, j]$ 的点，其中 $m$ 为环上的点数。

按长度从小到大枚举，就可以滚动数组了。

时间复杂度 $O(n + m^2)$。实际跑得挺快。

[code](https://codeforces.com/problemset/submission/1218/242936311)

---

## 作者：sunzh (赞：1)

这个题最恶心的地方在于你不会认为$1.5s$可以通过$2.25e8$

题意是给一棵基环树，任选一个点为起点然后向外一条边一条边扩展，每扩展到一个节点，它的贡献是它所在的联通块大小，求最大贡献

首先考虑一棵树的情况，以树上某个点为起点，显然贡献是以它为根是树上每棵子树的size和

我们分析题意可以发现，对于所有以环上节点为根的树，有且只有一棵树可以不从根开始扩展，因此我们分别计算每个节点的追加贡献，暴力$O(n^2)$在这里是可以接受的（详情请咨询出题人）

注意新节点到环上节点路径上每个节点被扩展时都会产生环上其它节点个数大小的贡献

然后我们考虑环上的情况，还是$O(n^2)$

我们用$dp_{i,j}$表示扩展了环上$i,j$之间的点，产生的最大贡献是多少

显然
$$dp_{i,j}=\max(dp_{i+1,j}+n-\sum_{k=i+1}^j siz_k,dp_{i,j-1}+n-\sum_{k=i}^{j-1}siz_k)$$

因为空间可能有问题，我们压缩一下状态，枚举长度$i$，用$dp_{i,j}$表示$j,j+i-1$的最大贡献，然后第一维滚动即可

时间复杂度$O(n^2)$，实际运行时间不超过$500ms$（雾

---

## 作者：gdf_yhm (赞：0)

[CF1218A](https://www.luogu.com.cn/problem/CF1218A)

模拟赛一车贪心水过去了除了我。

### 思路

是基环树。先考虑树。如果从一个点开始，定为根，$ans=\sum siz_u$。换根 dp 即可。

把环找出来，考虑在环上点 $u$ 的子树中开始染色的答案。染色的方式是大致是从子树的叶子开始向上。对 $u$ 的每个非环上儿子做树的 dp。记 $g_u$ 表示从环上进入子树向下染色的答案，$dp_u$ 表示换根的、从子树内任意节点开始染色的方案。从环上 $u$ 的非环上儿子 $v$ 的子树开始的答案是 $dp_v+\sum_{v'\neq v} g_{v'}$，$ans_u=\sum g_v+\max (dp_v-g_v)$。染完环上 $u$ 的子树后，绕环染环上点。再从除 $u$ 外的环上点向下染其他环上点的子树，答案为 $\sum g_v$。

发现前后贡献固定，变动的是染环的顺序。染环是染一个区间，每次向左右拓展。每次染一个点，答案加上当前连通块大小，当前连通块大小减 $siz_u$。贪心向小的染是错的，因为有后效性。记录 $siz$ 的前缀和，区间 dp，$O(1)$ 向左右转移。$dp_{l,r}=\max (dp_{l+1,r}+n-(sum_r-sum_l),dp_{l,r-1}+n-(sum_{r-1}-sum_{l-1}))$。第一维记录区间长度，滚动即可。

### code

```cpp
int n;
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int siz[maxn],dp[maxn],g[maxn];
int d[maxn];
void dfs(int u,int fa){
	siz[u]=1;g[u]=0;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa||d[v]==2)continue;
		dfs(v,u);siz[u]+=siz[v];g[u]+=g[v];
	}
	g[u]+=siz[u];
}
void dfs1(int u,int fa){
	if(d[fa]==2)siz[u]=n-siz[u]+1;
	else siz[u]=1;
	dp[u]=0;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa||d[v]==2)continue;
		dfs1(v,u);siz[u]+=siz[v];dp[u]+=dp[v];
	}
	dp[u]+=siz[u];
}
int ans,res;
void dfs2(int u,int fa){
	ans=max(ans,dp[u]);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa||d[v]==2)continue;
		dp[u]-=dp[v];dp[u]-=siz[u];siz[u]-=siz[v];dp[u]+=siz[u];
		dp[v]-=siz[v];siz[v]+=siz[u];dp[v]+=siz[v];dp[v]+=dp[u];
		dfs2(v,u);
		dp[v]-=dp[u];dp[v]-=siz[v];siz[v]-=siz[u];dp[v]+=siz[v];
		dp[u]-=siz[u];siz[u]+=siz[v];dp[u]+=siz[u];dp[u]+=dp[v];
	}
}
queue<int> q;
int p[maxn],num;
bool vis[maxn];
void dfs3(int u){
	vis[u]=1;p[++num]=u;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(d[v]!=2)continue;
		if(!vis[v])dfs3(v);
	}
}
int f[2][maxn],cur,sum[maxn];
int calc(int l,int r){
	if(l>r)return sum[num]-sum[l-1]+sum[r];
	return sum[r]-sum[l-1];
}
void work(){
	n=read();
	for(int i=1;i<=n;i++){
		int u=read()+1,v=read()+1;
		add(u,v),add(v,u);
		d[u]++,d[v]++;
	}
	for(int i=1;i<=n;i++)if(d[i]==1)q.push(i);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(d[v]>1){
				d[v]--;
				if(d[v]==1)q.push(v);
			}
		}
	}
	for(int i=1;i<=n;i++)if(d[i]==2)p[++num]=i;
	num=0;dfs3(p[1]);
	int sumg=0;
	for(int ii=1;ii<=num;ii++){
		int u=p[ii];
		siz[u]=1;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(d[v]!=2)dfs(v,u),sumg+=g[v],siz[u]+=siz[v];
		}
	}
	for(int i=1;i<=num;i++)sum[i]=sum[i-1]+siz[p[i]];
	// cout<<sumg<<"\n";
	for(int ii=1;ii<=num;ii++){
		int u=p[ii];
		int val=0;int s=n;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(d[v]!=2){
				ans=0;int lstsiz=siz[v];
				dfs1(v,u),dfs2(v,u);siz[v]=lstsiz;
				val=max(val,ans-g[v]+n-siz[v]);
				// cout<<ans<<" "<<g[v]<<" "<<siz[v]<<"\n";
			}
		}
		val=max(val,n);
		s-=siz[u];
		f[1][ii]=val+sumg;
	}
	cur=1;
	for(int i=2;i<=num;i++){
		for(int l=1,r=l+i-1;l<=num;l++,r=(r==num?1:r+1)){
			f[i&1][l]=max(f[cur][l]+n-calc(l,(r==1?num:r-1)),f[cur][(l==num?1:l+1)]+n-calc((l==num?1:l+1),r));
		}
		cur^=1;
	}
	for(int i=1;i<=num;i++)res=max(res,f[num&1][i]);
	printf("%lld\n",res);
}
```


---

