# Escape The Maze (easy version)

## 题目描述

The only difference with E2 is the question of the problem..

Vlad built a maze out of $ n $ rooms and $ n-1 $ bidirectional corridors. From any room $ u $ any other room $ v $ can be reached through a sequence of corridors. Thus, the room system forms an undirected tree.

Vlad invited $ k $ friends to play a game with them.

Vlad starts the game in the room $ 1 $ and wins if he reaches a room other than $ 1 $ , into which exactly one corridor leads.

Friends are placed in the maze: the friend with number $ i $ is in the room $ x_i $ , and no two friends are in the same room (that is, $ x_i \neq x_j $ for all $ i \neq j $ ). Friends win if one of them meets Vlad in any room or corridor before he wins.

For one unit of time, each participant of the game can go through one corridor. All participants move at the same time. Participants may not move. Each room can fit all participants at the same time.

Friends know the plan of a maze and intend to win. Vlad is a bit afraid of their ardor. Determine if he can guarantee victory (i.e. can he win in any way friends play).

In other words, determine if there is such a sequence of Vlad's moves that lets Vlad win in any way friends play.

## 说明/提示

In the first test case, regardless of the strategy of his friends, Vlad can win by going to room $ 4 $ . The game may look like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1611E1/0a8c76c1125e98bbe64e3bee85b654b8b00ed8d2.png)The original locations of Vlad and friends. Vlad is marked in green, friends — in red.  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1611E1/a01da1e80c938fd2913aa4a19caf3932554dfd58.png)Locations after one unit of time.  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1611E1/315079dc5161157c1dc8fb4c3b930b808460dd31.png)End of the game.Note that if Vlad tries to reach the exit at the room $ 8 $ , then a friend from the $ 3 $ room will be able to catch him.

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

3 1
2
1 2
2 3

3 1
2
1 2
1 3

3 2
2 3
3 1
1 2```

### 输出

```
YES
NO
YES
NO```

# 题解

## 作者：智子 (赞：7)

## 题意

Vlad 和他的朋友们玩游戏。游戏场地是一棵 $n$ 个节点的有根树。Vlad 开始在 1 号节点，他的朋友们在另外 $k$ 个节点。Vlad 每移动一次， Vlad 的朋友们可以任意沿着边移动一次也可以不移动。Vlad 如果能走到一个叶子结点，并且途中没有碰到任何一个朋友就获胜了。问 Vlad 是否有办法做到必胜。

## 思路

跑两遍 BFS，一边计算 Vlad 到每个节点的最短距离，一遍计算 Vlad 的朋友们到每个节点的最短距离。最后，如果存在一个叶子结点，Vlad 到它的距离比 Vlad 的朋友们到它的距离更短，Vlad 只需要移动到这个叶子结点就能获胜。

（一下为了方便说明，记 Vlad 到每个节点的距离为 $tmp_i$，Vlad 的朋友们到每个节点的最短距离为 $dis_i$。满足条件的叶节点 $i$ 即 $tmp_i < dis_i$。）

这个方法的正确性很容易证明：从根结点到每个叶子节点只有一条路径，如果这条路径上有任意一个节点$j$ 出现了 $tmp_j \ge dis_j$ 的情况，这个叶子结点 $i$ 肯定也有 $tmp_i \ge dis_i$。换句话说，只要叶子结点满足 $tmp_i < dis_i$，整条路径上所有节点也都满足 $tmp_i < dis_i$，即 Vlad 离该节点的距离比所有朋友都更近。

所以对于满足 $tmp_i < dis_i$ 的叶子节点，Vlad 只要一开始就选择走这条路径，就可以在任何一个朋友到达该路径上的任何一个节点前到达该节点，并最终获胜。

## 代码

```cpp
#include<cstdio>
#include<vector>
#include<queue>
using namespace std;

const int MAXN = 200000 + 5;

vector<int> G[MAXN];
bool vis[MAXN];
int pos[MAXN], dis[MAXN], tmp[MAXN];
int n, k;

void bfs1() {
    queue<int> q;

    for(int i = 1; i <= n; i++) {
        dis[i] = 0;
        vis[i] = false;
    }
    q.push(1);
    vis[1] = true;
    while(!q.empty()) {
        int u = q.front(); q.pop();

        for(int i = 0; i < G[u].size(); i++) {
            int v = G[u][i];

            if(vis[v]) {
                continue;
            }
            dis[v] = dis[u] + 1;
            vis[v] = true;
            q.push(v);
        }
    }
    for(int i = 1; i <= n; i++) {
        tmp[i] = dis[i];
    }
}

void bfs2() {
    queue<int> q;

    for(int i = 1; i <= n; i++) {
        dis[i] = 0;
        vis[i] = false;
    }
    for(int i = 1; i <= k; i++) {
        q.push(pos[i]);
        vis[pos[i]] = true;
    }
    while(!q.empty()) {
        int u = q.front(); q.pop();

        for(int i = 0; i < G[u].size(); i++) {
            int v = G[u][i];

            if(vis[v]) {
                continue;
            }
            dis[v] = dis[u] + 1;
            vis[v] = true;
            q.push(v);
        }
    }
}

int main() {
    int T;

    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &k);
        for(int i = 1; i <= n; i++) {
            G[i].clear();
        }
        for(int i = 1; i <= k; i++) {
            scanf("%d", &pos[i]);
        }
        for(int i = 1; i <= n - 1; i++) {
            int u, v;

            scanf("%d%d", &u, &v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        bfs1();
        bfs2();
        bool flag = false;
        for(int i = 2; i <= n; i++) {
            if(G[i].size() == 1 && tmp[i] < dis[i]) {
                flag = true;
                break;
            }
        }
        if(flag) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }

    return 0;
}

```

---

## 作者：Lacrymabre (赞：3)

题目简述：现在有一棵树，其中1号节点是树根，树上边都是双向边。树上有 $n$ 个点，您有 $k$ 位朋友。每个时刻，您和您的朋友都会顺着树上的边走向另一个节点。

您会获胜当且仅当你走到了叶子节点。

您会输当且仅当您被一个朋友在您获胜之前在任何房间或走廊遇到。

问：您是否会在这场游戏中获胜？

题解：维护一个时间数组，表示朋友到达这个点的最短时间，维护一个深度数组，表示您到达点的最段时间。

容易发现，您能到达一个点，当且仅当您到达这个点的时间比任何朋友都要早。

dfs即可。

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
	ll res=0,len=s[now].size();
	for(int i=0;i<len;i++){
		ll y=s[now][i];
		if(y==fa) continue;
		res=1;
		if(tline[y]>dep[y]) cheak(y,now);
	}
	if(res==0) flag=1;
}

oid clear(ll n,ll k){
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
		cheak(1,0);
		if(flag) cout<<"yes\n";
		else cout<<"no\n";
	}
	return 0;
}

```


---

## 作者：shipeiqian (赞：0)

# CF1611E1 题解

## 题意

有一颗树包含 $n$ 个节点，上面有 $k$ 个朋友，每秒移动至另一个相邻的节点，还有一个主角，从节点 $1$ 开始，每秒移动至另一个相邻的节点。如果主角来到了叶子节点上，且中途没有和朋友相遇，就成功了。问是否能成功。

## 思路

用 bfs 容易看懂。从给出的 $k$ 个点开始分别向外扩散，主角从 $1$ 开始扩散，用 vis 记录是否走过，走过的路谁都不能再走，被修改过 vis 的地方主角就不能去。如果主角走到叶子节点就直接输出 `YES`。

## 做法

### 区分主角和朋友。

如果用两个队列，太麻烦。可以直接将朋友在队列中的位置正常记录，主角的记录为 $n$ 加上位置即可。取用时判断是否大于 $n$ 即可。

### 判断叶子节点

如果一个点的边的数量为 $1$，就说明是叶子节点了。


## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=4e5+5;
int n,k;
bool vis[N];
vector<int>g[N];
void solve(){
	cin >>n >>k;
	for(int i=1;i<=n;i++)vis[i]=false,g[i].clear();//十年oi一场空，数组没请见祖宗
	queue<int>q;
	for(int i=1;i<=k;i++){
		int x;
		cin >>x;
		q.push(x);
		vis[x]=true;//输入的时候直接把朋友放进去，不用再开一个数组
	}
	for(int i=1;i<n;i++){
		int u,v;
		cin >>u >>v;
		g[u].push_back(v);
		g[v].push_back(u);//建图
	}
	q.push(n+1);
	vis[1]=true;//放入主角，位置加上n
	while(!q.empty()){
		int now=q.front();
		q.pop();
		if(now>n){//是主角
			for(auto nxt:g[now-n]){
				if(vis[nxt])continue;//被访问过，还可能会遇到朋友
				if(g[nxt].size()==1){//到叶子节点了
					cout <<"YES\n";
					return ;
				}
				vis[nxt]=true;//其他地方不加n
				q.push(nxt+n);//队列里的要加n
			}
		}
		else{//是朋友
			for(auto nxt:g[now]){
				if(vis[nxt])continue;
				q.push(nxt);
				vis[nxt]=true;
			}
		}
	}
	cout <<"NO\n";
}
int main(){
    int t;
    cin >>t;
    while(t--)solve();
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
            cout << "YES\n";
            return;
        }
    }
    cout << "NO\n";
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

今日 exlg 随机跳到的题目，分享一种非常麻烦的解法。

首先朴素的做法是枚举每一个叶子节点，接着枚举每一个好朋友，如果玩家会比所有好朋友先到这个叶子节点，那么就可以获胜。容易发现枚举复杂度是 $O(n^2)$，求距离还要个 $O(\log n)$。肯定会炸。

会 TLE 的原因是我们要枚举每一个叶子节点，不妨换一种思路。先看看这个朋友会和玩家在哪个点相遇。也就是这个朋友所在的点的的 $\displaystyle\frac{d-1}{2}$ 级祖先（$d$ 表示这个节点的深度）。那么说明玩家肯定不可能走到这个祖先的子树，不然就会被这个朋友抓住。

所以我们可以把这一些祖先的子树打上标记，表示这些点被守住，不能走。最后还需要单点查询每个叶子结点玩家能不能走，容易想到一个神秘的数据结构。

树链剖分未免有些大炮轰蚊子，毕竟这才绿题。发现一个节点的子树内的 dfs 序是连续的。所以可以先预处理 dfs 序，我们就只需要一个区间修改，单点查询的数据结构。于是可以选择树状数组。

至于前面求树上 $k$ 级祖先的算法，我们可以选用求 LCA 时的倍增算法，然后二进制拆分往上跳就行了。

```cpp
#include<bits/stdc++.h>
#define lowbit(x) (x&(-x))
#define N 200005
#define int long long
#pragma GCC optimize("O3")
using namespace std;
int n,k,cnt;
int a[N],sz[N],d[N],dfn[N],c[N],f[20][N];
vector<int>v[N];
void dfs1(int k,int fa)
{
	d[k]=d[fa]+1;//深度
	dfn[k]=++cnt;//dfs序
	f[0][k]=fa;//求k级祖先的倍增数组
	sz[k]=1;//子树大小
	for(auto now:v[k])
	{
		if(now==fa) continue;
		dfs1(now,k);
		sz[k]+=sz[now];
	}
	return;
}
void update(int x,int y)//树状数组操作
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
void solve()
{
	cin>>n>>k;
	cnt=0;
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
	for(int j=1;j<=18;j++) for(int i=1;i<=n;i++) f[j][i]=f[j-1][f[j-1][i]];//求倍增数组
	for(int i=1;i<=k;i++)
	{
		int now=a[i],dep=(d[now]-1)>>1;
		for(int j=18;j>=0;j--) if(dep&(1<<j)) now=f[j][now];//求这个节点的dep级祖先
		update(dfn[now],1);
		update(dfn[now]+sz[now],-1);//区间打上标记
	}
	for(int i=2;i<=n;i++)
	{
		if(v[i].size()==1&&query(dfn[i])==0)//是叶子结点并且可以走
		{
			cout<<"YES\n";
			return;
		}
	}
	cout<<"NO\n";
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

## 作者：Day_Tao (赞：0)

### 题目大意

给定一棵树，$1$ 号点为根节点，你现在在根。在这棵树的某些节点有你的朋友。每一次行动你和你的朋友都能沿着树走一次。定义你赢了是你能在不遇到你的朋友的情况下走到叶子节点，反之你就输了。要求判断对于所有的情况你是否都能获胜。

### Sol

简单说就是一遍 dfs，一遍 bfs。从根节点出发到达叶子节点的最优方案肯定就是一直往深处走，所以就可以用 dfs 求出叶子节点的深度，并且把叶子节点都保存下来。接着考虑要怎么样才能不碰到朋友。假如说朋友能比你先到达叶子节点，那么他就可以在叶子结点和其父亲节点之间来回走，所以对于这个叶子结点你是无法到达的。所以可以从朋友的点开始 bfs，更新朋友到达每个点的最小时间。最后枚举叶子节点，找到一个深度小于朋友到达最小时间的叶子就代表可以到达。

### Code

```
#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define mp(x, y) make_pair(x, y)
#define pqg priority_queue<int, vector<int>, greater<int>>
#define pql priority_queue<int, vector<int>, less<int>>
#define ls root << 1
#define rs root << 1 | 1
#define scnaf scanf
#define rt register int
#define int long long
const int MAX = 2e5 + 5;
const int INF = 0x7fffffff;
const int mod = 998244353;
vector<int>son[MAX];
queue<int>q;
int T,n,k,u,v,dep[MAX],dis[MAX],a,leaf[MAX],cnt;
void dfs(int u,int fa)
{
	if(son[u].size()==1&&u!=1)//记录叶子节点，记得除去根节点
		leaf[++cnt]=u;
	for(int v:son[u])
	{
		if(v==fa)
			continue;
		dep[v]=dep[u]+1;//更新深度
		dfs(v,u);
	}
	return ;
}
inline void bfs()
{
	while(!q.empty())
	{
		u=q.front(),q.pop();
		for(int v:son[u])
			if(dis[u]+1<dis[v])
				dis[v]=dis[u]+1,q.push(v);
	}
}
signed main()
{
	scanf("%lld",&T);
	while(T--)
	{
		cnt=0;
		scanf("%lld%lld",&n,&k);
		for(int i=1;i<=n;i++)
			dep[i]=0,dis[i]=INF,son[i].clear();
		while(!q.empty())
			q.pop();						//多测要清空
		for(int i=1;i<=k;i++)
			scanf("%lld",&a),q.push(a),dis[a]=0;
		for(int i=1;i<n;i++)
			scanf("%lld%lld",&u,&v),son[u].push_back(v),son[v].push_back(u);
		dfs(1,0);
		bfs();
		for(int i=1;i<=cnt;i++)
			if(dis[leaf[i]]>dep[leaf[i]])//对于每个叶子节点寻找可行方案
			{
				puts("YES");
				goto Day_Tao;
			}
		puts("NO");
		Day_Tao:;
	}
	return 0;
}
```

---

### END

---

## 作者：Tx_Lcy (赞：0)

这题并不难，E1 和 E2 的难度差不多。但是细节众多，我调了一个小时才过的。

## 思路
首先我们可以**预处理**出每个点从 $1$ 开始的 dfs 序，这样我们就可以判断哪些点是可以跳到的。因为当一个朋友顺着树的边向祖先跳时，自己也可以**同时向着这个朋友正在跳的那条树链向下跳**。所以我们可以判断出我们跳到的点的 dfs 序一定小于 $1+$ 出发点的 dfs 序。

但这样的时间复杂度仍然是 $O(n^2)$ 的，无法通过。因此我们需要优化。不难想到根据每个 $r_i$ 的 dfs 序从小到大排序。若我们当前遇到一个点已经被访问过。我们不用继续访问，因为**我们能访问到的一定被访问过了，我们不能访问到的也可能已经被访问过了**，我们接下来继续访问是没必要的。从根节点向下灌水，判断是否能不经过标记点到达叶子节点。这样的时间复杂度为 $O(n \log n+n)$，可以通过此题。
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
		if (ans==-1) cout<<"YES"<<'\n';
		else cout<<"NO\n";
	}
	return 0;
}
```


---

