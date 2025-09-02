# Escape The Maze (hard version)

## 题目描述

The only difference with E1 is the question of the problem.

Vlad built a maze out of $ n $ rooms and $ n-1 $ bidirectional corridors. From any room $ u $ any other room $ v $ can be reached through a sequence of corridors. Thus, the room system forms an undirected tree.

Vlad invited $ k $ friends to play a game with them.

Vlad starts the game in the room $ 1 $ and wins if he reaches a room other than $ 1 $ , into which exactly one corridor leads. Friends are placed in the maze: the friend with number $ i $ is in the room $ x_i $ , and no two friends are in the same room (that is, $ x_i \neq x_j $ for all $ i \neq j $ ). Friends win if one of them meets Vlad in any room or corridor before he wins.

For one unit of time, each participant of the game can go through one corridor. All participants move at the same time. Participants may not move. Each room can fit all participants at the same time.

Friends know the plan of a maze and intend to win. They don't want to waste too much energy. They ask you to determine if they can win and if they can, what minimum number of friends must remain in the maze so that they can always catch Vlad.

In other words, you need to determine the size of the minimum (by the number of elements) subset of friends who can catch Vlad or say that such a subset does not exist.

## 说明/提示

In the first set of inputs, even if all the friends stay in the maze, Vlad can still win. Therefore, the answer is "-1".

In the second set of inputs it is enough to leave friends from rooms $ 6 $ and $ 7 $ . Then Vlad will not be able to win. The answer is "2".

In the third and fourth sets of inputs Vlad cannot win only if all his friends stay in the maze. Therefore the answers are "1" and "2".

## 样例 #1

### 输入

```
4

8 2
5 3
4 7
2 5
1 6
3 6
7 2
1 7
6 8

8 4
6 5 7 3
4 7
2 5
1 6
3 6
7 2
1 7
6 8

3 1
2
1 2
2 3

3 2
2 3
3 1
1 2```

### 输出

```
-1
2
1
2```

# 题解

## 作者：Rushroom (赞：4)

[传送门](https://www.luogu.com.cn/problem/CF1611E2)

### 思路

一个很重要的性质：如果一个朋友比我早，或和我同时到达一个节点，那么在以这个节点为根的子树中的所有节点，我都到达不了。

容易想到，如果某一个朋友想拦截我，那么他一定是要往根的方向（也就是向上）走，才能使拦截的节点更多。

如果我向某一个朋友的方向走，那么我们两个会在中间相遇。更具体地，如果在根到那个朋友所在的节点的路径上有 $x$ 个节点（不包括起点和终点），那么，我最多能向下走 $\left\lceil\dfrac{x}{2}\right\rceil$ 个节点，同时，那位朋友最多也只能向上走 $\left\lceil\dfrac{x}{2}\right\rceil$ 个节点。

所以，我们可以先 dfs 一遍，同时用一个栈来维护路径上的节点，处理出所有朋友最多能走到哪个节点（以下所有朋友均指移动过后的朋友）。

然后我们进行第二次 dfs，模拟我走路，遇到朋友就退回去，如果走到了某个叶子节点就说明我必定会赢，否则输出一共遇到了几个朋友，因为对于每个朋友，以他为根的子树内所有其他朋友都可以删去。

### Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define forr(i, a, n) for (int i = a; i <= n; i++)
#define rep(i, n) forr(i, 0, n - 1)
#define repp(i, n) forr(i, 1, n)
#define pb push_back
#define mp make_pair
#define init(a, i) memset(a, i, sizeof(a))
#define fi first
#define se second
#define mod 1000000007
#define MOD 998244353
#define MAXN 0x3f3f3f3f
int T, case_;
int n, k, a, b, num[200005], dep[200005], ans;
bool f[200005], del[200005]; //f是朋友的位置，del是移动后朋友的位置
vector<vector<int>> v;
vector<int> q; //应该用栈的
void dfs(int s, int from) //第一次dfs
{
    rep(i, v[s].size())
    {
        int x = v[s][i];
        if (x == from)
            continue;
        dep[x] = dep[s] + 1;
        q.pb(x);
        if (f[x])
            num[x] = q[dep[x] / 2];
        dfs(x, s);
        q.pop_back();
    }
}
bool get_ans(int s, int from) //第二次dfs
{
    if (del[s])
    {
        ans++;
        return 1;
    }
    if (s && v[s].size() == 1)
        return 0;
    rep(i, v[s].size())
    {
        int x = v[s][i];
        if (x == from)
            continue;
        if (!get_ans(x, s))
            return 0;
    }
    return 1;
}
void solve()
{
    cin >> n >> k;
    v.resize(n);
    rep(i, n) v[i].clear();
    init(f, 0);
    rep(i, k)
    {
        cin >> a;
        a--;
        f[a] = 1;
    }
    rep(i, n - 1)
    {
        cin >> a >> b;
        a--, b--;
        v[a].pb(b);
        v[b].pb(a);
    }
    dep[0] = 1;
    q.pb(0);
    init(num, 0);
    dfs(0, -1);
    q.pop_back();
    init(del, 0);
    rep(i, n) if (f[i]) del[num[i]] = 1;
    ans = 0;
    if (!get_ans(0, -1))
        cout << "-1\n";
    else
        cout << ans << endl;
}
int main()
{
    T = 1;
    cin >> T;
    for (case_ = 1; case_ <= T; case_++)
        solve();
    return 0;
}//by JFHT
```


---

## 作者：Lacrymabre (赞：3)

题目简述：现在有一棵树，其中1号节点是树根，树上边都是双向边。树上有 $n$ 个点，您有 $k$ 位朋友。每个时刻，您和您的朋友都会顺着树上的边走向另一个节点。

您会获胜当且仅当你走到了叶子节点。

您会输当且仅当您被一个朋友在您获胜之前在任何房间或走廊遇到。

问：至少在树中保留多少个朋友才能使您在游戏中失败？

和 Escape The Maze (easy version) 一样的是，如果能够判断您获胜，也就是说 $k$ 个朋友一起出动都不能使你失败，那么直接输出 -1

否则，当您不能前往一个节点时，这个节点至少需要1个朋友来封锁。

```

void getime(ll now,ll fa){	
	ll len=s[now].size();
	for(int i=0;i<len;i++){
		ll y=s[now][i];
		if(y==fa) continue;
		dep[y]=dep[now]+1;
		getime(y,now);
		tline[now]=min(tline[now],tline[y]+1);
	}
}

void cheak(ll now,ll fa){
	ll len=s[now].size();
	if(len==1&&s[now][0]==fa){// had been arrived
		flag=1;
		return;
	}
	for(int i=0;i<len;i++){
		ll y=s[now][i];
		if(y==fa) continue;
		if(tline[y]>dep[y]) cheak(y,now);
		else need++;
	}
	//if(res==0) flag=1;
}

void clear(ll n,ll k){
	for(int i=1;i<=n;i++) s[i].clear(),tline[i]=1e9;
	for(int i=1,d;i<=k;i++) d=read(),tline[d]=0;
	for(int i=1,u,v;i<n;i++) u=read(),v=read(),s[u].push_back(v),s[v].push_back(u);
}

int main(){
	t=read();
	while(t-->0){
		n=read();k=read();
		clear(n,k);
		getime(1,0);
		flag=0;
		need=0;
		cheak(1,0);
		if(flag) cout<<-1<<"\n";
		else cout<<need<<"\n";
	}
	return 0;
}
```


---

## 作者：swqdwq (赞：0)

## 思路
蒟蒻不太会 BFS，第一想法是直接建虚点跑最短路。

首先我们可以从 1 号点跑 Dijkstra，预处理出 1 号点到所有叶子节点的最短路（在代码中对应为 dis2 数组）。

接下来，我们引入一个虚拟的节点 0，并将其与所有朋友所在的节点连接，边权均设为 0。然后以 0 号点为起点跑 Dijkstra，那么 0 号点到所有叶子节点的最短路就等于所有朋友到各个叶子节点的最短路（在代码中对应为 dis 数组）。再判断是否存在一个叶子节点到 1 号节点比到朋友节点近。【easy-version】

hard-version 要求在失败情况下，最少只需要几个朋友。

我们需要进一步发现一个性质：如果某个节点是由朋友先到达的，那么以该节点为根的整个子树中的所有节点也必然是由朋友先到达的。

于是我们可以利用之前预处理出来的 dis 和 dis2 判断哪些节点是朋友先到达，朋友先到达的点打一个 flag 标记。

之后我们 DFS 一下，遇到 flag 标记的节点直接返回，并且统计一下这些最先遇到的的点。统计的数量就是答案。

## 代码

```C++
#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
using PII = pair<i64, int>;
#define INF 0x3f3f3f3f3f3f3f3f

struct node {
    int e, v;
};

void solve() {
    int n, m;
    cin >> n >> m;

    vector<int>fr(m + 1);
    for (int i = 1; i <= m; i++)cin >> fr[i];

    vector<vector<node>>g(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back({ v,1 });
        g[v].push_back({ u,1 });
    }

    vector<int>leaf;
    for (int i = 2; i <= n; i++) {
        if (g[i].size() == 1) {
            leaf.push_back(i);
        }
    }

    vector<i64>dis(n + 1);
    vector<int>vis(n + 1);
    priority_queue<PII>pq;
    auto dij = [&] (int s)->void {
        for (int i = 0; i <= n; i++)dis[i] = INF, vis[i] = 0;
        dis[s] = 0;
        pq.push({ 0,s });
        while (pq.size()) {
            int x = pq.top().second;
            pq.pop();
            if (vis[x]) continue;
            vis[x] = 1;
            for (auto i : g[x]) {
                if (dis[i.e] > dis[x] + i.v) {
                    dis[i.e] = dis[x] + i.v;
                    if (!vis[i.e])pq.push({ -dis[i.e],i.e });
                }
            }
        }
    };
    dij(1);
    auto dis2 = dis;

    for (int i = 1; i <= m; i++) {
        g[0].push_back({ fr[i],0 });
        g[fr[i]].push_back({ 0,0 });
    }
    dij(0);

    for (auto i : leaf) {
        if (dis2[i] < dis[i]) {
            cout << "-1\n";
            return;
        }
    }

    int ans = 0;
    vector<int>flag(n + 1);
    for (int i = 1; i <= n; i++) {
        if (dis[i] <= dis2[i]) {
            flag[i] = 1;
        }
    }

    auto dfs = [&] (auto self, int x, int fa)->void {
        for (auto [y, v] : g[x]) {
            if (y == fa)continue;
            if (flag[y]) {
                ans++;
                continue;
            }
            self(self, y, x);
        }
    };
    dfs(dfs, 1, -1);

    cout << ans << "\n";
}

signed main() {
    cin.tie(0)->sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--)solve();
    return 0;
}
```

---

## 作者：I_will_AKIOI (赞：0)

前面的具体思路可以看我的 [E1 题解](https://www.luogu.com.cn/article/9tri0zea)。

E1 的主要思路是先求出每个朋友可以守住那一棵子树，然后用树状数组区间打上标记。最后判断叶子结点有没有标记。

我们处理完每个节点的被几个朋友守住的信息后，先遍历下这棵树。如果一个节点会被两个及以上的朋友守住，说明一定有一些朋友是多余的，只有一个是有用的，因此遇到这种情况，我们就可以只保留一个朋友，其他的用树状数组的修改操作删去，并且记录删去了多少。最后用朋友总数减去删去个数就是答案。

```cpp
#include<bits/stdc++.h>
#define lowbit(x) (x&(-x))
#define N 200005
#define int long long
#pragma GCC optimize("O3")
using namespace std;
int n,k,cnt,ans;
int a[N],sz[N],d[N],dfn[N],c[N],f[20][N];
vector<int>v[N];
void dfs1(int k,int fa)
{
	d[k]=d[fa]+1;
	dfn[k]=++cnt;
	f[0][k]=fa;
	sz[k]=1;
	for(auto now:v[k])
	{
		if(now==fa) continue;
		dfs1(now,k);
		sz[k]+=sz[now];
	}
	return;
}

void update(int x,int y)
{
	while(x<=n)
	{
		c[x]+=y;
		x+=lowbit(x);
	}
	return;
}
int query(int x)
{
	int res=0;
	while(x)
	{
		res+=c[x];
		x-=lowbit(x);
	}
	return res;
}
void dfs2(int k,int fa)
{
	int now=query(dfn[k])-1;//多余朋友个数
	if(now>0)//有多余的
	{
		ans-=now;
		update(dfn[k],-now);
		update(dfn[k]+sz[k],now);
	}
	for(auto now:v[k])
	{
		if(now==fa) continue;
		dfs2(now,k);
	}
	return;
}
void solve()
{
	cin>>n>>k;
	cnt=0;
	ans=k;
	for(int i=1;i<=n;i++) v[i].clear(),c[i]=0;
	for(int i=1;i<=k;i++) cin>>a[i];
	for(int i=1;i<n;i++)
	{
		int x,y;
		cin>>x>>y;
		v[x].push_back(y);
		v[y].push_back(x);
	}
	dfs1(1,0);
	for(int j=1;j<=18;j++) for(int i=1;i<=n;i++) f[j][i]=f[j-1][f[j-1][i]];
	for(int i=1;i<=k;i++)
	{
		int now=a[i],dep=(d[now]-1)>>1;
		for(int j=18;j>=0;j--) if(dep&(1<<j)) now=f[j][now];
		update(dfn[now],1);
		update(dfn[now]+sz[now],-1);
	}
	for(int i=2;i<=n;i++)
	{
		if(v[i].size()==1&&query(dfn[i])==0)
		{
			cout<<"-1\n";
			return;
		}
	}
	dfs2(1,0);
	cout<<ans<<"\n";
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

## 作者：eb0ycn (赞：0)

传送门：[CF1611E2](https://www.luogu.com.cn/problem/CF1611E2)。

## 题意

现在有一棵树，其中 $1$ 号节点是树根，树上边都是双向边。树上有 $n$ 个点，您有 $k$ 位朋友。每个时刻，您和您的朋友都会顺着树上的边走向另一个节点。

您会获胜当且仅当你走到了叶子节点。

您会输当且仅当您被一个朋友在您获胜之前在任何房间或走廊遇到。

问：至少在树中保留多少个朋友才能使您在游戏中失败？

## 思路

首先按照 E1 的做法，处理出朋友到每个节点的最短距离 $dis$ 和你到每个点的距离 $dp$。

很显然，当且仅当 $dp_i<dis_i$ 时，你才能走到 $i$ 号节点；否则，这个节点肯定要有一个人把守。

我们尝试证明上面的东西：

首先，如果 $dis_i \leq dp_i$，在你到这个节点的时候，已经有个老六在这里待着了，所以就走不下去。

然后，最高的满足 $dis_i\leq dp_i$ 的节点是每个朋友能把守的极限，所以每次遇到这样的点，说明要多加一个朋友。

模拟走路的过程即可。

## 代码

```cpp
#include<cstdio>
using namespace std;
int ans,u,v,t,n,k,dp[200001],dis[200001],tot,nxt[400000],to[400000],head[200001],l,r,q[200001];
bool flg;
void dfs(int x,int fa){
	if(fa&&!nxt[head[x]]){flg=1;return;}
	for(int i=head[x];i;i=nxt[i])if(to[i]!=fa){
		if(dis[to[i]]>(dp[to[i]]=dp[x]+1))dfs(to[i],x);
		else ++ans;
	}
}
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&k),l=r=flg=ans=tot=0;
		for(int i=1;i<=n;++i)dis[i]=19491001,head[i]=0;
		for(int i=1;i<=k;++i)scanf("%d",q+(++r)),dis[q[r]]=0;
		for(int i=1;i<n;++i)scanf("%d%d",&u,&v),nxt[++tot]=head[u],to[tot]=v,head[u]=tot,nxt[++tot]=head[v],to[tot]=u,head[v]=tot;
		while(l<r){
			u=q[++l];
			for(int i=head[u];i;i=nxt[i])if(dis[to[i]]>dis[u]+1)dis[to[i]]=dis[u]+1,q[++r]=to[i];
		}dfs(1,0);
		if(flg)printf("-1\n");
		else printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：Tx_Lcy (赞：0)

这题并不难，但是细节众多，我调了一个小时才过的。

## 思路
首先我们可以**预处理**出每个点从 $1$ 开始的 dfs 序，这样我们就可以判断哪些点是可以跳到的。因为当一个朋友顺着树的边向祖先跳时，自己也可以**同时向着这个朋友正在跳的那条树链向下跳**。所以我们可以判断出我们跳到的点的 dfs 序一定小于 $1+$ 出发点的 dfs 序。

但这样的时间复杂度仍然是 $O(n^2)$ 的，无法通过。因此我们需要优化。不难想到根据每个 $r_i$ 的 dfs 序从小到大排序。若我们当前遇到一个点已经被访问过。我们不用继续访问，因为**我们能访问到的一定被访问过了，我们不能访问到的也可能已经被访问过了**，我们接下来继续访问是没必要的。这样的时间复杂度为 $O(n \log n+n)$，可以通过此题。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define rint register int
int const N=2e6+10;
int vis[N],tms[N],ts[N],b[N],vs[N],ans,r[N];
vector<int>a[N];
inline void make_ans(int x){
    if (ans==-1) return;
	if (vis[x]){++ans;return;}
	if (!ts[x]) ans=-1;//表示碰到叶子就返回
	vs[x]=1;
	for (rint i=0;i<a[x].size();++i)
	    if (!vs[a[x][i]])
		    make_ans(a[x][i]);
}//寻找答案的过程
inline void solve(int x,int st){
	if (x==0) return;
	if (vis[x]) return;//剪枝
	if (tms[x]<((tms[st]+2)/2)) return;
    vis[x]=1;
	solve(b[x],st);
}//找出每个点能跳到哪里
inline void dfs(int x,int dfn){
	tms[x]=dfn;vs[x]=1;
	int tag=0;
	for (rint i=0;i<a[x].size();++i)
	    if (!vs[a[x][i]])
			tag=1,dfs(a[x][i],dfn+1),b[a[x][i]]=x;
    ts[x]=tag;//标记是否为叶子节点
}//求出每个店的 dfs 序
struct node{int rs,id;}as[N];
inline bool cmp(node a,node b){return a.rs<b.rs;}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;cin>>t;
	while (t--){
		int n,k;cin>>n>>k;
		ans=0;
		for (rint i=1;i<=n;++i){
		    vs[i]=0;
		    while (a[i].size()) a[i].pop_back();
		}
		for (rint i=1;i<=k;++i) cin>>r[i];
		for (rint i=1;i<n;++i){
			int u,v;cin>>u>>v;
			a[v].push_back(u);
			a[u].push_back(v);
		}
		dfs(1,1);
	    for (rint i=1;i<=n;++i) vis[i]=0;
		for (rint i=1;i<=k;++i)
		    as[i].rs=tms[r[i]],as[i].id=r[i];
	    sort(as+1,as+k+1,cmp);//按 r[i] 排序
		for (rint i=1;i<=k;++i)
		    r[i]=as[i].id,
		    solve(r[i],r[i]);
		for (rint i=1;i<=n;++i) vs[i]=0;
		make_ans(1);
		cout<<ans<<'\n';
	}
	return 0;
}
```


---

