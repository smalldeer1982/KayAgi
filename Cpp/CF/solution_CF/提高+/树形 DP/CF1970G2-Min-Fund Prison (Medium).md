# Min-Fund Prison (Medium)

## 题目描述

现给出一张由 $n$ 个点 $m$ 条边构成的无向图，其 $m$ 条边为 $(u_i, v_i)$ ( $1\leq i\leq m$ )，表示 $u_i,v_i$ 相连。图中不存在重边，也没有自环。

你可以以 $c$ 的成本在任意两个点 $x, y$ 之间连一条边。这个操作可以进行任意次，设你操作了 $k$ 次。要求操作结束后图是连通的。

在连边操作之后，你必须删去一条割边，使得剩下的图恰由 $2$ 个连通块组成。设两个连通块的大小为 $x,y$ ，请问 $x^2+y^2+kc$ 的最小值为何？

## 样例 #1

### 输入

```
4
4 6 5
4 3
2 3
2 4
1 2
4 1
3 1
6 6 2
1 4
2 5
3 6
1 5
3 5
6 5
6 5 7
1 4
2 5
3 6
3 5
6 5
7 5 4
1 4
3 6
3 5
6 5
2 7```

### 输出

```
-1
20
25
33```

# 题解

## 作者：Clique (赞：4)

显然需要添加的走廊数量是固定的——为连通块个数 $-1$。也就是说我们只需要最小化 $x^2+y^2$。根据简单的不等式知识，我们只需要最小化最终两个连通块的大小之差，可以用背包做。

考虑分类讨论两个连通块之间的那一条走廊在哪里。无非就是两种情况：该走廊为原有的走廊之一（需要满足该走廊为割边）或为新加的走廊。对于两种情况分别做 $01$ 背包即可。

参考代码（GNU C++14, with AtCoder Library）

```cpp
#include <bits/stdc++.h>
#include <atcoder/all>
#define int long long
using namespace std;
const int N = 300;
inline int knapsack(int n, vector<int> &a) {
    if (a.size() == 1)
        return -1;
    bitset<N> b;
    b[0] = true;
    for (int i : a)
        b |= b << i;
    for (int i = n >> 1; i; i--)
        if (b[i])
            return i * i + (n - i) * (n - i);
}
main() {
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) {
        int n, m, c;
        cin >> n >> m >> c;
        vector<pair<int, int>> e(m);
        atcoder::dsu d(n);
        for (auto &[u, v] : e)
            cin >> u >> v, d.merge(--u, --v);
        vector<int> b;
        for (int i = 0; i < n; i++)
            if (i == d.leader(i))
                b.emplace_back(d.size(i));
        int r = knapsack(n, b);
        c *= b.size() - 1;
        for (int i = 0; i < m; i++) {
            atcoder::dsu d(n);
            for (int j = 0; j < m; j++)
                if (i != j)
                    d.merge(e[j].first, e[j].second);
            vector<int> b2;
            for (int j = 0; j < n; j++)
                if (j == d.leader(j))
                    b2.emplace_back(d.size(j));
            if (b2.size() > b.size()) {
                int x = knapsack(n, b2);
                r = (~r ? min(r, x) : x);
            }
        }
        cout << r + c << '\n';
    }
    return 0;
}
```

---

## 作者：I_will_AKIOI (赞：1)

由于要删去一条割边，考虑枚举这条边。接着分情况讨论。

+ 情况一：这条边在原图上。

我们先把这条边删去，获得一堆连通块（需要保证删去后这张图的连通块个数大于删去前的，否则该边不是割边），接着需要在他们之间连边，使得连通块个数为 $2$。由于每连一条边，连通块个数 $-1$，并且要最小化 $k$，因此需要连接连通块个数 $-2$ 条边。所以 $kc$ 是固定的，接着考虑最小化 $x^2+y^2$。

考虑枚举 $x$，那么 $y=n-x$。在求连通块过程中也处理出每个连通块大小 $sz_i$，利用 dp 计算哪些 $x$ 可以被 $sz_i$ 凑出，最后计算出 $x^2+y^2+kc$，取最小值得到答案。dp 过程设 $f_i$ 表示能否凑出 $i$，枚举 $sz_j$ 进行转移，即 $f_0=1,f_i=\bigvee f_{i-sz_j}$。

+ 情况二：这条边不在原图上。

考虑把边连上，假装这条边在原图上，变成上面的情况然后求解，唯一的区别就是添加的边多了一条。

总时间复杂度是边数乘以 dp 时间复杂度，即 $O(n^4)$，肯定过不了。注意到 dp 部分的转移方程可以使用 bitset 优化，时间复杂度变为 $O(\frac{n^4}{w})$，其中 $w$ 是字长，可以通过。

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize("O3")
#define int long long
#define N 305
using namespace std;
int n,m,c,cnt,ans,tot;
bool a[N][N],vis[N];
bitset<N>f;
vector<int>sz,v[N];
void dfs(int k)//dfs 求连通块大小
{
	if(vis[k]) return;
	vis[k]=1;
	cnt++;
	for(int now:v[k]) if(a[k][now]) dfs(now);
	return;
}
void solve()
{
	cin>>n>>m>>c;
	memset(a,0,sizeof(a));
	ans=1e18;
	for(int i=1;i<=n;i++) v[i].clear();
	for(int i=1;i<=m;i++)
	{
		int x,y;
		cin>>x>>y;
		a[x][y]=a[y][x]=1;
		v[x].push_back(y);
		v[y].push_back(x);
	}
	for(int x=1;x<n;x++)
	{
		for(int y=x+1;y<=n;y++)
		{
			int k;
			bool tmp=a[x][y];
			if(a[x][y]) k=0;
			else k=1;
			tot=0;
			if(k==1) a[x][y]=a[y][x]=1,v[x].push_back(y),v[y].push_back(x);//不在原图上，假装加边
			memset(vis,0,sizeof(vis));
			for(int i=1;i<=n;i++) if(!vis[i]) tot++,dfs(i);
			if(k==1) a[x][y]=a[y][x]=0,v[x].pop_back(),v[y].pop_back();
			a[x][y]=a[y][x]=0;
			sz.clear();
			memset(vis,0,sizeof(vis));
			for(int i=1;i<=n;i++) if(!vis[i]) cnt=0,dfs(i),sz.push_back(cnt);
			if(sz.size()>tot)
			{
				k+=sz.size()-2;
				f.reset();
				f[0]=1;
				for(int now:sz) f|=(f<<now);
				for(int i=0;i<=n;i++) if(f[i]) ans=min(ans,i*i+(n-i)*(n-i)+k*c);
			}
			a[x][y]=a[y][x]=tmp;
		}
	}
	if(ans==1e18) cout<<-1<<"\n";
	else cout<<ans<<"\n";
	return;
}
signed main()
{
	ios::sync_with_stdio(0);
	int t;
	cin>>t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：Aapwp_ (赞：0)

### Before it ：

感觉和树形 dp 没什么关系啊……

其次感谢 @wangsiqi2010916 大佬在此题上对我的思路和部分细节的指导！

### Solution ：

容易发现，为了使整张图联通，我们需要添加的边数是一定的，为图上联通块的个数 $-1$。

所以原式中 $k\times c$ 的值是不变的，我们只需要使 $x^2+y^2$ 的值最小。有 $x^2+y^2=(x+y) \times (x-y)$，$x+y$ 不变，为图的大小，所以我们只需要最小化 $x$ 和 $y$ 的差即可。

考虑对原图进行边双缩点，缩完点后得到的图一定是一个森林，记 $x$ 所在的联通块大小为 $siz_x$，断开割边后两部分值一定是 $siz_x$ 和 图的大小减去 $siz_x$。

考虑可行性 dp。设 $dp_{i,j,0/1}$ 表示第 $i$ 个联通块，其中一个联通块大小为 $j$，是否断边。dp 值为 $1$ 表示可行，$0$ 为不可行。初始时 $dp_{0,0,0}=1$。

接下来状态转移，如果没有断开，则直接连到对应联通块即可。

若连向第二个联通块，则

$$dp_{i,j,0}\mid=dp_{i-1,j,0}$$
$$dp_{i,j,1}\mid=dp_{i-1,j,1}$$

若连向第一个联通块，则

$$dp_{i,j,0}\mid=dp_{i-1,j-siz_{rt},0}$$
$$dp_{i,j,1}\mid=dp_{i-1,j-siz_{rt},1}$$

若断边，则必然会分成两部分，一部分在第一个联通块，将其更新，则有

$$dp_{i,j,0}\mid=dp_{i-1,j-(siz_{rt}-siz_{x}),0}$$
$$dp_{i,j,1}\mid=dp_{i-1,j-siz_{x},1}$$

注意这里使用或进行转移。

### Code :


```
#include<bits/stdc++.h> 
#define int long long 
using namespace std;
const int maxn=305; 
int T,n,m,c;
struct edge{
	int to,nxt;
}e[2*maxn];
int head[maxn],edgenum=1;
void add_edge(int u,int v){
	e[++edgenum].nxt=head[u];
	e[edgenum].to=v;
	head[u]=edgenum;
}
int dp[maxn][maxn][3];

int dfn[maxn],low[maxn],tim,sum,siz[maxn],col[maxn];
stack<int> s;
void tarjan(int u,int fa){//边双缩点 	
	dfn[u]=low[u]=++tim;
	s.push(u);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(!dfn[v]){
			tarjan(v,i);
			low[u]=min(low[u],low[v]); 
		}
		else if(i!=(fa^1)) low[u]=min(low[u],dfn[v]); 
	}
	if(low[u]==dfn[u]){
		sum++;
		int y;
		do{
			y=s.top();
			s.pop();
			siz[sum]++;
			col[y]=sum;
		}while(y!=u);
	}
}
vector<int> vec[maxn];
int rt[maxn],st[maxn];
bool vis[maxn];
void dfs(int u,int root){
	vis[u]=1;
	rt[u]=root;
	for(int v:vec[u]){
		if(vis[v]) continue;
		dfs(v,root);
		siz[u]+=siz[v];
	}
}
void clear(){
	memset(e,0,sizeof(e));
	memset(head,0,sizeof(head));
	memset(dfn,0,sizeof(dfn));
	memset(dp,0,sizeof(dp));
	memset(low,0,sizeof(low));
	memset(col,0,sizeof(col));
	memset(siz,0,sizeof(siz));
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;i++){
		for(int j=0;j<vec[i].size();j++) vec[i][j]=0;
	}
	tim=0,sum=0;
	edgenum=1;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	
	cin>>T;
	while(T--){
		cin>>n>>m>>c;
		clear();
		for(int i=1,x,y;i<=m;i++){
			cin>>x>>y;
			add_edge(x,y);
			add_edge(y,x);
		}
		for(int i=1;i<=n;i++){
			if(!dfn[i]) tarjan(i,0);
		}
		if(sum==1){
			cout<<-1<<endl;
			continue;
		}
		for(int i=1;i<=n;i++){
			for(int j=head[i];j;j=e[j].nxt){
				if(col[e[j].to]!=col[i]){
					vec[col[e[j].to]].push_back(col[i]);
					vec[col[i]].push_back(col[e[j].to]);
				}
			}
		}
		int cnt=0;
		for(int i=1;i<=sum;i++){
			if(!vis[i]){
				dfs(i,i);
				st[++cnt]=i;//共有cnt棵树 
			}
		}
		dp[0][0][0]=1;
		c=(cnt-1)*c;
		for(int i=1;i<=cnt;i++){
			int tot=siz[st[i]];
			for(int j=0;j<=n;j++){//枚举大小 
				if(j>=tot){
					dp[i][j][0]|=dp[i-1][j-tot][0];
					dp[i][j][1]|=dp[i-1][j-tot][1];
				}
				dp[i][j][0]|=dp[i-1][j][0];
				dp[i][j][1]|=dp[i-1][j][1];
				for(int k=1;k<=sum;k++){
					//k不属于第i块 
					if(rt[k]!=st[i] || k==st[i]) continue;
					if(j>=tot-siz[k]) dp[i][j][1]|=dp[i-1][j-tot+siz[k]][0];
					if(j>=siz[k]) dp[i][j][1]|=dp[i-1][j-siz[k]][0];
				}
			}
		}
		long long ans=1e17;
		for(int i=0;i<=n;i++){
			if(dp[cnt][i][0] || dp[cnt][i][1]){
				ans=min(ans,1ll*i*i+1ll*(n-i)*(n-i));
			}
		}
		cout<<ans+c<<endl;
	}
}
```

---

## 作者：wangsiqi2010916 (赞：0)

因为加完后要让图联通，显然，要加的边数就是联通快的个数 $-1$，所以只需要让 $x$，$y$ 尽量接近即可。

因为要分成两个联通快，所以删掉的边一定是割边或加上的边，所以可以使用 tarjan 求边双和缩点。

有一个性质，经过边双缩点后的图一定是一个森林，记深度较大的节点为 $u$，$x$ 子树大小为 $siz_x$，所以断开割边后的两部分的值分别为 $siz_u$ 和 $siz_{rt}-siz_u$。

考虑 $dp$，因为算平方很难统计，考虑可行性 $dp$。

设 $dp_{i,j,0/1}$ 表示当前是第 $i$ 个联通快，第一个联通快大小为 $j$，是否断开已知边。

显然的，如果没有断开，直接连到对应联通快即可，有：

连到第二个集合：

$$
dp_{i,j,0}=dp_{i,j,0}|dp_{i-1,j,0},dp_{i,j,1}=dp_{i,j,1}|dp_{i-1,j,1}
$$

连到第一个集合：

$$
dp_{i,j,0}=dp_{i,j,0}|dp_{i-1,j-siz_{rt},0},dp_{i,j,1}=dp_{i,j,1}|dp_{i-1,j-siz_{rt},1}
$$

对于断开已知边，必然会分成两部分，一部分连在第一个联通快，另一部分在第二个：

$$
dp_{i,j,1}=dp_{i,j,1}|dp_{i-1,j-(siz_{rt}-siz_x),0},dp_{i,j,1}=dp_{i,j,1}|dp_{i-1,j-siz_x,0}
$$

最后看每一个 $j$ 值是否可行即可。

```cpp
#include<cstdio>
#include<algorithm>
#define ll long long
using namespace std;
int n,m,T,head[305],edgenum,head1[305],edgenum1,cnt;
ll c;
struct edge{
	int to,nxt;
}e[606],e1[606];
void add_edge(int u,int v)
{
	e[++edgenum].nxt=head[u];
	e[edgenum].to=v;
	head[u]=edgenum;
}
void add_edge1(int u,int v)
{
	e1[++edgenum1].nxt=head1[u];
	e1[edgenum1].to=v;
	head1[u]=edgenum1;
}
int s[305],dfn[305],low[305],idx,top,ecnt,id[305],siz[305];
bool bri[305];
void tarjan(int i,int in_edge)
{
	dfn[i]=low[i]=++idx;
	s[++top]=i;
	for(int u=head[i];u;u=e[u].nxt)
	{
		int j=e[u].to;
		if(!dfn[j])
		{
			tarjan(j,u);
			low[i]=min(low[i],low[j]);
			if(low[j]>dfn[i])
			{
				bri[u]=bri[u^1]=1;
			}
		}
		else if(u!=(in_edge^1))
		{
			low[i]=min(low[i],dfn[j]);
		}
	}
	if(dfn[i]==low[i])
	{
		ecnt++;
		int v=0;
		while(v!=i)
		{
			v=s[top];
			top--;
			id[v]=ecnt;
			siz[ecnt]++;
		}
	}
}
int rt[305],st[305];
bool vis[305],dp[305][305][2];
void dfs(int u,int root)
{
	vis[u]=1;
	rt[u]=root;
	for(int i=head1[u];i;i=e1[i].nxt)
	{
		int v=e1[i].to;
		if(vis[v]) continue;
		dfs(v,root);
//		printf("%d %d %d %d\n",u,v,siz[u],siz[v]);
		siz[u]+=siz[v];
	}
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%lld",&n,&m,&c);
		for(int i=1;i<=n;i++)
		{
			head[i]=head1[i]=dfn[i]=low[i]=0;
			siz[i]=vis[i]=bri[i]=0;
		}
		top=cnt=idx=ecnt=0;
		edgenum=1,edgenum1=0;
		for(int i=1;i<=m;i++)
		{
			int u,v;
			scanf("%d%d",&u,&v);
			add_edge(u,v);
			add_edge(v,u);
		}
		for(int i=1;i<=n;i++)
		{
			if(!dfn[i])
			{
				tarjan(i,0);
			}
		}
		for(int i=1;i<=n;i++)
		{
//			printf("%d ",id[i]);
			for(int j=head[i];j;j=e[j].nxt)
			{
				int v=e[j].to;
				if(id[i]!=id[v])
				{
//					printf("%d %d\n",i,v);
					add_edge1(id[i],id[v]);
				}
			}
		}
		if(ecnt==1)
		{
			printf("-1\n");
			continue;
		}
		cnt=0;
//		for(int i=1;i<=ecnt;i++)
//		{
//			printf("%d ",siz[i]);
//		}
		for(int i=1;i<=ecnt;i++)
		{
			if(!vis[i])
			{
				dfs(i,i);
				st[++cnt]=i;
			}
		}
//		printf("%d\n",ecnt);
		for(int i=1;i<=cnt;i++)
		{
			for(int j=0;j<=n;j++)
			{
				dp[i][j][0]=dp[i][j][1]=0;
			}
		}
		dp[0][0][0]=1;
		c=(cnt-1)*c;
		for(int i=1;i<=cnt;i++)
		{
//			printf("%d ",st[i]);
			int srt=siz[st[i]];
			for(int j=0;j<=n;j++)
			{
				if(j>=srt)
				{
					dp[i][j][0]|=dp[i-1][j-srt][0];
					dp[i][j][1]|=dp[i-1][j-srt][1];
				}
				dp[i][j][0]|=dp[i-1][j][0];
				dp[i][j][1]|=dp[i-1][j][1];
				for(int k=1;k<=ecnt;k++)
				{
					if(rt[k]!=st[i]||k==st[i]) continue;
					if(j>=srt-siz[k]) dp[i][j][1]|=dp[i-1][j-srt+siz[k]][0];
					if(j>=siz[k]) dp[i][j][1]|=dp[i-1][j-siz[k]][0];
				}
			}
		}
		ll ans=1e17;
		for(int i=0;i<=n;i++)
		{
			if(dp[cnt][i][0]||dp[cnt][i][1])
			{
				ans=min(ans,1ll*i*i+1ll*(n-i)*(n-i));
//				printf("%d %d\n",dp[cnt][i][0],dp[cnt][i][1]);
			}
		}
		printf("%lld\n",ans+c);
	}
	return 0;
}
```

AC记录![](https://cdn.luogu.com.cn/upload/image_hosting/ekhm7lbe.png)

---

## 作者：conti123 (赞：0)

## CF1970G

从 G1 来的，发现和后面其实有关系。

题意有些欠缺，加的边一定要使原图联通，然后才能断掉。

### Medium

注意到加的边一定是连通块数 $-1$ 条不变，因为这个坑了我好久，所以只需要最小化 $x^2+y^2$ 即可。

无解当且仅当原图是一个大的边双。

注意到删除的边一定是割边或者加入的边，而一个边双内的点一定在一个连通块内，考虑边双缩点。

于是变成了一颗森林，考虑可行性背包，$f_{i,j,k}$ 表示前 $i$ 个树删或没删完边后能否达到 $k$。

转移的话很简单，像 G1 一样看每一棵树能转移出多少，注意可以整棵树一起，也可以是砍掉一个子树后取剩下的，如果砍了 $j$ 记得变。

发现直接做时空复杂度均为 $O(n^2)$。

### Hard

考虑优化 G2 的做法，发现空间能用滚动数组滚去一维，变成 $O(n)$，时间上发现题解有 $O(\frac{n\sqrt n \log n}{w})$ 的神奇做法？

算了，我是蒟蒻，没想到可以用 bitset 优化，这样的话一次可以除去 $w$ 的常数，时间复杂度变为 $O(\frac{n^2}{w})$，可以通过此题。

```cpp
struct fy{
	int v,nxt;
}edge[N<<1];
int dfn[N],low[N],n,m,k,idx=1,head[N<<1],id,S[N],Sid,sum,inw[N],sz[N];
inline void add(int x,int y){
	edge[++idx].v=y,edge[idx].nxt=head[x],head[x]=idx;
}
inline void dfs(int u,int from){
	//printf("begin%d %d\n",u,from);
	dfn[u]=low[u]=++id;
	S[++Sid]=u;
	for(int i=head[u];i;i=edge[i].nxt){
		int v=edge[i].v;
		if(!dfn[v]){
			dfs(v,i);
			low[u]=min(low[u],low[v]);
		}
		else if(i!=(from^1))
			low[u]=min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u]){
		sum++;
		int pp;
		do{
		//	printf("1\n");
			pp=S[Sid--];
			sz[sum]++;
			inw[pp]=sum;
		}
		while(pp!=u);
	}
//	printf("end%d %d\n",u,from);
}
int vis[N],szid=0,tsz[N];
vector<int>SZ[N],E[N];
int dfs1(int u){
	int siz=sz[u];
	vis[u]=1;
	for(int v:E[u]){
		if(vis[v])
			continue;
		siz+=dfs1(v);
	}
	SZ[szid].psb(siz);
	return siz;
}
bitset<50001>f[2][2];
inline int read(){
	int x=0;
	char c=getchar();
	while(c>'9'||c<'0')
		c=getchar();
	while(c<='9'&&c>='0')
		x=(x<<3)+(x<<1)+c-'0',c=getchar();
	return x;
}
void solve(){
//	printf("begin\n");
	n=read(),m=read(),k=read();
	for(int i=1;i<=n;i++)
		head[i]=0;
	idx=1,id=0,Sid=0,sum=0;
	szid=0;
	for(int i=1;i<=n;i++)
		dfn[i]=low[i]=inw[i]=sz[i]=0,E[i].clear(),SZ[i].clear(),tsz[i]=0,vis[i]=0;
	for(int i=1;i<=m;i++){
		int x,y;
		x=read(),y=read();
		add(x,y);
		add(y,x);
	}
//	printf("read ok\n");
	for(int i=1;i<=n;i++){
	//	printf("%d begin\n",i);
		if(!dfn[i])
			dfs(i,0);
	}
//	printf("1\n");
	if(sum==1){
		printf("-1\n");
		return ;
	}
	for(int u=1;u<=n;u++){
		for(int i=head[u];i;i=edge[i].nxt){
			if(inw[edge[i].v]!=inw[u])
				E[inw[edge[i].v]].psb(inw[u]);
		}
	}
//	printf("2\n");
	for(int i=1;i<=sum;i++){
		if(!vis[i]){
			++szid;
			SZ[szid].clear();
			int tot=dfs1(i);
			tsz[szid]=tot;
			int len=SZ[szid].size()-1;
			for(int j=0;j<=len;j++)
				SZ[szid].psb(tot-SZ[szid][j]);
		}
	}
//	printf("3\n");
	f[0][0].set(0);
	f[0][1].set(0);
	f[1][0].set(0);
	f[1][1].set(0);
	f[0][0][0]=f[1][0][0]=1;
	for(int i=1;i<=szid;i++){
		f[0][i&1]=(f[0][i&1^1]|(f[0][i&1^1]<<tsz[i]));
		for(int v:SZ[i])
			f[0][i&1]|=(f[1][i&1^1]<<v);
		f[1][i&1]=(f[1][i&1^1]|(f[1][i&1^1]<<tsz[i]));
	}
//	printf("dp\n");
	long long ans=1e18;
	for(int i=0;i<=n/2;i++){
		if(f[0][szid&1][i]||f[1][szid&1][i])
			ans=min(ans,1ll*(szid-1)*k+1ll*i*i+1ll*(n-i)*(n-i));
	}
//	cout<<sum<<" "<<ans);
    printf("%lld\n",ans);
}
```

无力吐槽边双缩点的链式前向星了，吃了一堆罚时。

~~好在最后没过。~~

说一下为什么可以用 bitset 优化，因为是可行性背包，里面只有 $0$ 和 $1$，这样能提升效率的 bitset 用来干最合适了，所以用它优化。

---

