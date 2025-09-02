# Cactus Wall

## 题目描述

为了抵御怪物的袭击，Monocarp 决定利用他的院子构建一座仙人掌屏障。院子可以看作 $n$ 行 $m$ 列的网格，每个格子内最多可以种一颗仙人掌。

怪物可以从第一行任意一个没有仙人掌的格子进入院子，它每次能走到一个**四联通相邻**（即两个格子有公共边）且没有仙人掌的格子。如果怪物怎么走都无法到达最后一行的某个没有仙人掌的格子，那么院子里就成功构建了一座屏障。

但如果仙人掌种植过密，就可能因为缺乏养分凋零而失去作用，因此**任意两个四联通相邻的格子不能同时种上仙人掌**。

现在可能有些格子已经种上了仙人掌。Monocarp 想要知道在**不铲除已有仙人掌**的前提下，至少要再种多少颗仙人掌才能构成一座屏障。

## 说明/提示

$1\leq t\leq 10^3$，$2\leq n,m\leq 2\times10^5$，$\sum nm\leq 4\times10^5$

## 样例 #1

### 输入

```
4
2 4
.#..
..#.
3 3
#.#
...
.#.
5 5
.....
.....
.....
.....
.....
4 3
#..
.#.
#.#
...```

### 输出

```
YES
.#.#
#.#.
NO
YES
....#
...#.
..#..
.#...
#....
YES
#..
.#.
#.#
...```

# 题解

## 作者：GalwayGirl (赞：7)

看没有题解，就想着来交一发题解。

## Sloution
看到这道题，首先可以想到两种方法，第一种是模拟出怪物的行动路线用仙人掌隔断，但复杂度令我不敢尝试，第二种就是bfs仙人掌的种植路线，也就是我接下来会讲的正解。

首先，仙人掌四联通格子不能同时种，所以bfs的方向只能是斜着的四个方向，然后题目要求种植的仙人掌要最少，所以肯定想到这条隔断上方的仙人掌路线要尽可能经过原本的仙人掌，所以就可以将到仙人掌格子的边权设为 $0$，到要种植仙人掌的格子的边权设为 $1$。此时我们的主角登场了，双端队列BFS，专门处理 $01$ 边权的利器，用法也很好理解，就是将边权为 $0$ 的放入队头，边权为 $1$ 的放入队尾，思路结束。

建议练习板子题。
[P4667 [BalticOI 2011 Day1]Switch the Lamp On ](https://www.luogu.com.cn/problem/P4667)

最后贴上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m;
const int dx[]={0,0,1,-1,1,1,-1,-1};
const int dy[]={1,-1,0,0,1,-1,1,-1};
const int N=2e5+100;
struct xzh{
    int x,y;
};
vector<int>pre[N],dis[N];
string a[N];
deque<xzh>q;   
bool check(int x,int y){
    if(x<0||x>=n||y<0||y>=m)return false;
    for(int i=0;i<4;i++){
        int xx=x+dx[i],yy=y+dy[i];
        if(xx>=0&&xx<n&&yy>=0&&yy<m&&a[xx][yy]=='#')return false;
    }
    return true;
}
int main(){
    scanf("%d",&t);
    while(t--){
        scanf("%d%d",&n,&m);
        for(int i=0;i<n;i++)cin>>a[i];
        for(int i=0;i<n;i++)dis[i].clear(),pre[i].clear();
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                dis[i].push_back(2e9);
                pre[i].push_back(0);
            }
        }
        for(int i=0;i<n;i++){
            if(a[i][0]=='#')q.push_front({i,0}),dis[i][0]=0;
            else if(check(i,0))q.push_back({i,0}),dis[i][0]=1;
        }
        while(!q.empty()){
            int x=q.front().x,y=q.front().y;
            q.pop_front();
            for(int i=4;i<8;i++){
                int xx=x+dx[i],yy=y+dy[i]; 
                if(!check(xx,yy))continue;
                int s=(a[xx][yy]=='.');
                if(dis[xx][yy]>dis[x][y]+s){
                    dis[xx][yy]=dis[x][y]+s;
                    pre[xx][yy]=i;
                    if(s)q.push_back({xx,yy});
                    else q.push_front({xx,yy});
                }
            }
        }
       int min_=2e9,minn;
        for(int i=0;i<n;i++){
            if(dis[i][m-1]<min_){
                min_=dis[i][m-1];minn=i;
            }
        }
        if(min_==2e9){
            printf("NO\n");
            continue;
        }
        printf("YES\n");
        int x=minn,y=m-1;
        while(1){
            a[x][y]='#';
            if(!pre[x][y])break;
            int ls=pre[x][y];
            x-=dx[ls];y-=dy[ls];
        }
        for(int i=0;i<n;i++){
            cout<<a[i];
            printf("\n");
        }
    }
    return 0;
}
```


---

## 作者：EnofTaiPeople (赞：5)

这道题相当于是要求一条从第 $1$ 列到第 $m$ 列的斜连通路，将以放了的格子为终点的边权设为 $0$，没放的设为 $1$，然后求出第 $1$ 列到第 $m$ 列的最短路即可，使用 $\text{01bfs}$。

有些题解没有说明，就是自己摆放的 $\text{cactus}$ 中一定不会出现相邻的，因为最后找的斜连通路中的所有摆放点横纵坐标和的奇偶性总是相同的。

对于 $\text{01bfs}$，有一种常见的错误就是只在每一个点第一次更新距离时入队，事实上这样子是错误的，如果一个点更新了多次，每一次都需要入队，所以队列总元素会达到 $O(m)$，然而本题入队一次似乎也不会有问题，因为每个点是入队头还是入队尾与前一个点无关。

由于要输出方案，可以记录一个 `pre`，表示某一个点在最短路径上的前驱。

也许自己能力不够，调了两个小时：
```cpp
#include<icecream>
using namespace std;
const int N=4e5+5;
int T,n,m,d[N],f[N],ans;
vector<vector<int> >G;
vector<int>F;
struct DT{int x,y;}q[N<<3边有四倍，所以开八倍空间],at,pr[N]记录pre;
bitset<N>vs;
int l,r;
void add(int x,int y,int ds,DT pp){
    if(G[x][y]==-1)return;
    int z=(x-1)*m+y;
    if(d[z]<=ds)return;
    d[z]=ds,pr[z]=pp;
    q[G[x][y]?--l:++r]={x,y};
    --l表示入队头，++r表示入队尾。
}
string s[N];
int main(){
    ios::sync_with_stdio(false);
    写 CF 题目统一用关闭同步流+cin+printf
    cin>>T;
    while(T--){
        cin>>n>>m,l=N<<2,r=(N<<2)-1;
        int i,j,x,y;ans=1e9;
        G.clear(),G.resize(n+2);
        for(i=0;i<=n+1;++i)
            G[i].resize(m+2,0);
        for(i=1;i<=n;++i){
            cin>>s[i];
            for(j=1;j<=m;++j){
                if(s[i][j-1]=='#'){
                    G[i][j]=1;
                    G[i][j-1]=G[i-1][j]=-1;
                    G[i][j+1]=G[i+1][j]=-1;
                }d[(i-1)*m+j]=1e9;
                vs[(i-1)*m+j]=0;
            }
        }
        for(i=1;i<=n;++i)
            add(i,1,!G[i][1],(DT){-1,-1});
        for(i=0;i<=n+1;++i)G[i][0]=G[i][m+1]=-1;
        for(i=1;i<=m;++i)G[0][i]=G[n+1][i]=-1;
        while(l<=r){
            at=q[l++];
            if(vs[(at.x-1)*m+at.y])continue;
            vs[(at.x-1)*m+at.y]=1;也可以不记录，不影响复杂度
            for(int dx:{-1,1})
                for(int dy:{-1,1})
                    if(~G[x=at.x+dx][y=at.y+dy])
                        add(x,y,d[(at.x-1)*m+at.y]+!G[x][y],at);
        }
        for(i=1;i<=n;++i)
            ans=min(ans,d[(i-1)*m+m]);
        if(ans>n*m){其实就是ans超级大，也可以取1e7
            puts("NO");
            continue;
        }puts("YES");
        for(i=1;i<=n;++i)
            if(d[(i-1)*m+m]==ans){
                for(at={i,m};at.x>0&&at.y>0;at=pr[(at.x-1)*m+at.y])
                    s[at.x][at.y-1]='#';
                break;
            }
        for(i=1;i<=n;++i){
            s[i].push_back('\n');
            fwrite(s[i].c_str(),1,m+1,stdout);
        }
    }return 0;
}
```

---

## 作者：L0vely_NaiL0ng (赞：2)

容易发现一条斜着走从最左边一列走到最右边一列的路径可以形成屏障，这里斜着走的意思是从一个点走到与它**八连通相邻但并不四连通相邻**的点。

现在题目转化为找到一条像上面这样的路径，路径上没有仙人掌的点数的最小值即为答案。

我们发现这个东西不是很好动态规划，因为它具有后效性，然后我们考虑有后效性的动态规划一般使用什么方法优化。

- 高斯消元，显然复杂度爆炸。

- 最短路，符合数据范围，而且只要记录一下最短路路径就很容易还原出种仙人掌的方案。

转化为最短路模型后，考虑到如果以最左列为起点，最右列为终点，这个图有多个起点和终点，考虑建立虚拟源点、汇点。

源点向最左边一列连边，每个点向斜着走一步能到的点连边，这两种边边权看到达的点是否有仙人掌，如果有那么边权为 $0$，代表不需要多种仙人掌，反之为 $1$，代表需要多种仙人掌。最后一列向汇点连 $0$ 的边，汇点是一个虚拟点，只是为了方便统计答案，不需要种仙人掌。

这道题难度主要在于转化为图论模型，所以我要强调一下上面那 $2$ 种遇到有后效性动态规划的处理方法。高斯消元和最短路。

```
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int T, n, m;
string s[N];
int d[N * 2], pre[N * 2];
vector< pair<int, int> > e[N * 2];
int dx[4] = {-1, -1, 1, 1}, dy[4] = {1, -1, 1, -1}, dx2[4] = {0, 0, 1, -1}, dy2[4] = {1, -1, 0, 0};
deque<int> qu;
bool vis[N * 2];
int f(int x, int y) {
	return (x - 1) * m + y;
}
void add(int x, int y, int z) {
	e[x].push_back({y, z});
}
bool check(int x, int y) {
	bool flag = (x >= 1 && x <= n && y >= 1 && y <= m);
	for (int k = 0; k < 4; k++) {
		int tx = x + dx2[k], ty = y + dy2[k];
		if (tx >= 1 && tx <= n && ty >= 1 && ty <= m && s[tx][ty - 1] == '#') flag = 0;
	}
	return flag;
}
pair<int, int> g(int x) {
	pair<int, int> res = {(x - 1) / m + 1, 0};
	res.second = x - (res.first - 1) * m;
	return res;
}
void print(int x) {
	if (!x) return;
	pair<int, int> res = g(x);
	s[res.first][res.second - 1] = '#';
	print(pre[x]);
}
void solve() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> s[i];
	}
	for (int i = 0; i <= n * m + 1; i++) {
		e[i].clear(); d[i] = 1e9; vis[i] = 0;
	}
	for (int i = 1; i <= n; i++) {
		if (!check(i, 1)) continue;
		if (s[i][0] == '#') add(0, f(i, 1), 0);
		else add(0, f(i, 1), 1);
	}
	for (int i = 1; i <= n; i++) add(f(i, m), n * m + 1, 0);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			for (int k = 0; k < 4; k++) {
				int x = i + dx[k], y = j + dy[k];
				if (check(x, y)) {
					if (s[x][y - 1] == '#') add(f(i, j), f(x, y), 0);
					else add(f(i, j), f(x, y), 1);
				}
			}
		}
	qu.push_front(0); d[0] = 0;
	while (!qu.empty()) {
		int x = qu.front(); qu.pop_front();
		if (vis[x]) continue;
		vis[x] = 1;
		for (auto i : e[x]) {
			int y = i.first, z = i.second;
			if (d[y] > d[x] + z) {
				d[y] = d[x] + z; pre[y] = x;
				if (z == 0) qu.push_front(y);
				else qu.push_back(y);
			}
		}
	}
	if (d[n * m + 1] >= 1e9) {
		puts("NO"); return;
	}
	puts("YES");
	print(pre[n * m + 1]);
	for (int i = 1; i <= n; i++) cout << s[i] << endl;
	return;
}
int main() {
	//freopen("sample.in", "r", stdin);
	cin >> T;
	while (T--) solve();
	return 0;
}
```

---

## 作者：Error_Eric (赞：2)

### 题意

试在平面上种若干仙人掌使得平面被分成上下两个不连通的部分。

任意两个仙人掌不能四联通（感觉 idea 像从 mc 里面来的）。

### Sol

蒟蒻不会 deque bfs, 提供一种 bfs+dfs 的做法。

显然我们要找到一条从最左边一列到最右边一列的斜着走的路径。

那么考虑 $a_{i,j}$ 表示从最左行到当前位置最少种几个仙人掌。

那么如果没有现成的仙人掌这是可以 bfs 求的。

考虑现成的仙人掌的影响。

首先是不能走到现成的仙人掌四联通的地方。

如果当前走到了一个现成的仙人掌斜联通的地方，那么和这个现成的仙人掌联通块斜相邻的所有方格都可以一步到达，而这一部分又可以用 dfs 解决。

最后储存方案即可。

### Code


[RECORD](https://codeforc.es/contest/1749/submission/178754828)

马蜂比较诡异，在这里说明一下。

``a`` 是题目中的意思，只不过负值表示没访问过， ``-1`` 表示不能种，``-2`` 表示已经种，``-3`` 表示空地。

``cop`` 是 ``a`` 的副本，其中 ``-4`` 表示隔绝左右的路径上的仙人掌。

``fr`` 是记录方案。

这个题目不定长宽真的很讨厌/kk。

---

## 作者：Hisaishi_Kanade (赞：1)

高明。

首先我们考虑怎样安排仙人掌可以达成目标，没错，只要一条**斜着走能从最左边一列走到最右边一列**的路径。我们加入一个源点 $S$，要求他和所有最左边一列的连边；再加入一个汇点 $T$ 要求它和所有最右边一列的连边。那么现在问题转化成求 $S\to T$ 的一条符合要求的路径。

我们给 $n\times m$ 个点赋上点权：
1. 它和仙人掌相邻，此时这个点不能走。
2. 它就是仙人掌，走它需要花费 $0$。
3. 其他情况，花费 $1$。

考虑“至少种植”，那就是有了点权之后的 $S\to T$ 的最短路。

你会发现所有的权值不是 $1$ 就是 $0$，考虑 dijkstra 的优先队列实际的作用是什么？快速求出目前能到达的最小的点对不对？我们如果有这样一个优先队列，我们把当前的 $0$ 插入进去，和直接放队首没区别；同理，把 $1$ 插进去还是一样的相当于放在队尾。

支持首尾操作那就是 `deque` 了，我们用 `deque` 模拟这个过程进行最短路就行。如何输出答案呢？在最后一列中找到最小的 $dis$。然后从这里开始往回找。在求最短路的时候，记录从上一个点到这个点的方向，一路找回第一列就行。

这道题有一个很抽象的地方是你没办法直接开 `int dis[N][M],frm[N][M]` 这样，那就在第二维使用 `vector`。显然 `dis` 初值全是 $+\infty$，`frm` 的初值全是 $0$，现场构造一个这样的长度 $m$ 的 `vector` 然后 `swap` 一下。

```cpp 
#include<bits/stdc++.h>
#define rep(i,l,r) for(i=l;i<=r;++i)
using namespace std;
int t,n,m,i,x,y,xx,yy;
const int dx[]= {0,1,0,-1,1,-1,-1,1};
const int dy[]= {1,0,-1,0,1,-1,1,-1};
const int N=2e5+5,inf=1<<29;
class Eti{public:int x,y;};
vector<int>frm[N],dis[N];
string str[N];
deque<Eti>q;
inline const bool check(int x,int y)
{
    int i,rx,ry;
    if(x<0 || x>=n || y<0 || y>=m)return false;
    rep(i,0,3)
    {
        rx=x+dx[i],ry=y+dy[i];
        if(!(rx<0 || rx>=n || ry<0 || ry>=m) && str[rx][ry]=='#')return false;
    }
    return true;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);cin>>t;
    while(t--)
    {
        cin>>n>>m;auto rn=n-1,rm=m-1;
//      vector<int> qx(m,inf),qy(m,0);
        rep(i,0,rn)cin>>str[i];
        rep(i,0,rn)
        {
            vector<int>(m,inf).swap(dis[i]);
            vector<int>(m,0).swap(frm[i]);
        }
//      rep(i,0,rn){
//          copy(qx.begin(),qx.end(),dis[i].begin());
//          copy(qy.begin(),qy.end(),frm[i].begin());
//      }
        rep(i,0,rn)
            if(str[i][0]=='#')
            {
                q.push_front({i,0});
                dis[i][0]=0;
            }else
                if(check(i,0))
                {
                    q.push_back({i,0});
                    dis[i][0]=1;
                }
        while(!q.empty())
        {
            x=q.front().x;
            y=q.front().y;
            q.pop_front();
            rep(i,4,7){
                xx=x+dx[i];
                yy=y+dy[i];
                if(!check(xx,yy))continue;
                if(dis[xx][yy]>dis[x][y]+(str[xx][yy]=='.'))
                {
                    dis[xx][yy]=dis[x][y]+(str[xx][yy]=='.');
                    frm[xx][yy]=i;
                    if(str[xx][yy]=='.')
                        q.push_back({xx,yy});
                    else
                        q.push_front({xx,yy});
                }
            }
        }
        int ret=inf,pos;
        rep(i,0,rn)
            if(dis[i][rm]<ret)
            {
                ret=dis[i][rm];
                pos=i;
            }
        if(ret==inf)cout<<"NO\n";
		else
		{
            cout<<"YES\n";
            x=pos;
            y=rm;int mid;
            while(true)
            {
                str[x][y]='#';
                if(!frm[x][y])break;
                mid=frm[x][y];
                x-=dx[mid];
                y-=dy[mid];
            }
            rep(i,0,rn)
                cout<<str[i]<<'\n';
        }
    }
    return 0;
}
```

---

## 作者：541forever (赞：1)

注意到，能够成功阻止怪物的充要条件是，仙人掌的分布合法且存在一条每次纵坐标只变化 $1$ 的从左到右的路径。因此可以考虑建一个源点 $S$ 和汇点 $T$，$S$ 向所有最左边的点连边，所有最右边的点向 $T$ 连边，中间每个点向离他横纵坐标均相差 $1$ 的点连边，若边的出点原本就有仙人掌，则边权为 $0$，若没有，则边权为 $1$，这样的点和连出的边的数量都是 $O(nm)$ 的，直接跑 dijkstra 或 01bfs 均可。而方案的输出就相当于简单的输出路径了。

最后贴上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int inf=0x3f3f3f3f;
inline int read(){
	int x=0,f=1;
	char ch;
	do{
		ch=getchar();
		if(ch=='-'){
			f=-1;
		}
	}while(!(ch>='0'&&ch<='9'));
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x*f;
}
int n,m,t,S,T,dist[400005],head[400005],edgenum,vis[400005],go[4][2]={1,0,0,1,-1,0,0,-1},no[400005],from[400005],ans[400005],g[4][2]={1,1,-1,-1,1,-1,-1,1};
struct Edge{
    int from,to,next,w;
}edge[4000005];
void add_edge(int from,int to,int w){
    edge[++edgenum].next=head[from];
    edge[edgenum].from=from;
    edge[edgenum].to=to;
    edge[edgenum].w=w;
    head[from]=edgenum;
}
void bfs(){
    queue<int> p,q;
    for(int i=0;i<=T;++i){
        dist[i]=inf;
        vis[i]=0;
    }
    q.push(S);
    dist[S]=0;
    while(q.size()||p.size()){
        int x;
        if(q.size()){
            x=q.front();
            q.pop();
        }else{
            x=p.front();
            p.pop();
        }
        if(x==T){
            return;
        }
        if(vis[x]){
            continue;
        }
        vis[x]=1;
        for(int i=head[x];i;i=edge[i].next){
            int v=edge[i].to;
            if(dist[v]>dist[x]+edge[i].w){
                from[v]=x;
                dist[v]=dist[x]+edge[i].w;
                if(edge[i].w){
                    p.push(v);
                }else{
                    q.push(v);
                }
            }
        }
    }
}//最短路
void init(){
    edgenum=0;
    for(int i=0;i<=T;++i){
        from[i]=ans[i]=no[i]=head[i]=0;
    }
}//清空图
void print(int x){
    x=from[x];
    if(x==0){
        return;
    }
    ans[x]=1;
    print(x);
}//输出路径
void add(int x,int y){
    if(no[x]||no[y]){
        return;
    }
    if(ans[y]){
        add_edge(x,y,0);
    }else{
        add_edge(x,y,1);
    }
}
signed main(){
    t=read();
    while(t--){
        init();
        n=read();
        m=read();
        for(int i=1;i<=n;++i){
            for(int j=1;j<=m;++j){
                char ch;
                cin>>ch;
                if(ch=='#'){
                    ans[(i-1)*m+j]=1;
                    for(int k=0;k<4;++k){
                        int x=i+go[k][0],y=j+go[k][1];
                        if(x<1||x>n||y<1||y>m){
                            continue;
                        }
                        no[(x-1)*m+y]=1;
                    }
                }
            }
        }
        bool flag=0;
        T=n*m+1;
        for(int i=1;i<=n;++i){
            int num=(i-1)*m+1;
            add(S,num);
        }
        for(int i=1;i<=n;++i){
            for(int j=1;j<=m;++j){
                int num=(i-1)*m+j;
                if(ans[num]&&no[num]){
                    flag=1;
                    break;
                }
                for(int k=0;k<4;++k){   
                    int x=i+g[k][0],y=j+g[k][1];
                    if(x>n||x<1||y>m||y<1){
                        continue;
                    }
                    int num2=(x-1)*m+y;
                    add(num,num2);
                }
            }
        }
        if(flag){
            printf("NO\n");
            continue;
        }
        for(int i=1;i<=n;++i){
            add_edge(i*m,T,0);
        }//繁琐的建图
        bfs();
        if(dist[T]==inf){
            printf("NO\n");
        }else{
            printf("YES\n");
            print(T);
            for(int i=1;i<=n;++i){
                for(int j=1;j<=m;++j){
                    if(ans[(i-1)*m+j]){
                        printf("#");
                    }else{
                        printf(".");
                    }
                }
                printf("\n");
            }
        }
    }
    return 0;
}
```


---

## 作者：daniEl_lElE (赞：1)

很不错的一道图论建模题。

## 思路

本题最重要的应该是将原题中修建仙人掌转化成一条从左边走到最右边，只往斜方向走的路径。

考虑每走一步的时候，要么那个位置是一个仙人掌，要么那个位置还没有仙人掌，我们可以放置一个，但是要求周围（四连通）没有仙人掌。

这样做可以直接暴力建边跑单源最短路，但我们还有更好的做法。

考虑我们每走一步最多增加 $1$，最少则为 $0$，于是我们可以直接对于这个图跑 01bfs，此时的复杂度为 $O(nm)$，可以通过本题。记录方案的话也常规。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long 
#define double long double
using namespace std;
signed main(){
	int t;
	cin>>t;
	while(t--){
		int n,m;
		cin>>n>>m;
		char c[n+2][m+2];
		int dp[n+1][m+1];
		int frm[n+1][m+1];
		int fr2[n+1][m+1];
		for(int i=0;i<=n+1;i++) for(int j=0;j<=m+1;j++) c[i][j]='.';
		for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) cin>>c[i][j],dp[i][j]=-1;
		deque<pair<int,int>> q;
		for(int i=1;i<=n;i++){
			if(c[i][1]=='#'){
				dp[i][1]=0;
				q.push_front(make_pair(i,1));
			}
			else if(!((c[i-1][1]=='#')+(c[i+1][1]=='#')+(c[i][2]=='#')+(c[i][0]=='#'))){
				dp[i][1]=1;
				q.push_back(make_pair(i,1));
			}
		}
		int to=-1;
		while(!q.empty()){
			auto f=q.front();
			q.pop_front();
			int i=f.first,j=f.second;
			if(j==m){
				to=i;
				break;
			}
			if(i>1){
				if(c[i-1][j+1]=='#'){
					if(dp[i-1][j+1]==-1||dp[i-1][j+1]>dp[i][j]){
						dp[i-1][j+1]=dp[i][j];
						frm[i-1][j+1]=i;
						fr2[i-1][j+1]=j;
						q.push_front(make_pair(i-1,j+1));
					} 
				}
				else if(!((c[i-2][j+1]=='#')+(c[i][j+1]=='#')+(c[i-1][j+2]=='#')+(c[i-1][j]=='#'))){
					if(dp[i-1][j+1]==-1||dp[i-1][j+1]>dp[i][j]+1){
						dp[i-1][j+1]=dp[i][j]+1;
						frm[i-1][j+1]=i;
						fr2[i-1][j+1]=j;
						q.push_back(make_pair(i-1,j+1));
					}
				}
			}
			if(i<n){
				if(c[i+1][j+1]=='#'){
					if(dp[i+1][j+1]==-1||dp[i+1][j+1]>dp[i][j]){
						dp[i+1][j+1]=dp[i][j];
						frm[i+1][j+1]=i;
						fr2[i+1][j+1]=j;
						q.push_front(make_pair(i+1,j+1));
					} 
				}
				else if(!((c[i+2][j+1]=='#')+(c[i][j+1]=='#')+(c[i+1][j+2]=='#')+(c[i+1][j]=='#'))){
					if(dp[i+1][j+1]==-1||dp[i+1][j+1]>dp[i][j]+1){
						dp[i+1][j+1]=dp[i][j]+1;
						frm[i+1][j+1]=i;
						fr2[i+1][j+1]=j;
						q.push_back(make_pair(i+1,j+1));
					}
				}
			}
			if(j>1){
			if(i>1){
				if(c[i-1][j-1]=='#'){
					if(dp[i-1][j-1]==-1||dp[i-1][j-1]>dp[i][j]){
						dp[i-1][j-1]=dp[i][j];
						frm[i-1][j-1]=i;
						fr2[i-1][j-1]=j;
						q.push_front(make_pair(i-1,j-1));
					} 
				}
				else if(!((c[i-2][j-1]=='#')+(c[i][j-1]=='#')+(c[i-1][j-2]=='#')+(c[i-1][j]=='#'))){
					if(dp[i-1][j-1]==-1||dp[i-1][j-1]>dp[i][j]+1){
						dp[i-1][j-1]=dp[i][j]+1;
						frm[i-1][j-1]=i;
						fr2[i-1][j-1]=j;
						q.push_back(make_pair(i-1,j-1));
					}
				}
			}
			if(i<n){
				if(c[i+1][j-1]=='#'){
					if(dp[i+1][j-1]==-1||dp[i+1][j-1]>dp[i][j]){
						dp[i+1][j-1]=dp[i][j];
						frm[i+1][j-1]=i;
						fr2[i+1][j-1]=j;
						q.push_front(make_pair(i+1,j-1));
					} 
				}
				else if(!((c[i+2][j-1]=='#')+(c[i][j-1]=='#')+(c[i+1][j-2]=='#')+(c[i+1][j]=='#'))){
					if(dp[i+1][j-1]==-1||dp[i+1][j-1]>dp[i][j]+1){
						dp[i+1][j-1]=dp[i][j]+1;
						frm[i+1][j-1]=i;
						fr2[i+1][j-1]=j;
						q.push_back(make_pair(i+1,j-1));
					}
				}
			}
			}
		}
		if(to==-1){
			cout<<"NO\n";
			continue;
		}
		cout<<"YES\n";
		int X=to,Y=m;
		c[X][Y]='#';
		while(Y!=1){
			int nx=frm[X][Y],ny=fr2[X][Y];
			X=nx,Y=ny;
			c[X][Y]='#';
		}
		for(int i=1;i<=n;i++,cout<<"\n") for(int j=1;j<=m;cout<<c[i][j],j++);
	}
}
```

代码可能写的有些繁琐，但是相比有一定实现能力对照题解也可以写出来。

---

## 作者：UncleSam_Died (赞：1)

### 解题思路
考虑建图，很容易想到放置后的仙人掌需满足存在一条从第一列到第 $m$ 列的路径，那么我们的最优答案就是一条从第 $1$ 列到第 $m$ 列的最短路，其中，到达一个已经有仙人掌的点花费 $0$ 的代价，到达一个不存在仙人掌的点花费 $1$ 的代价。我们可以使用双端队列 bfs，即边权为 $0$ 的放前面，边权为 $1$ 的放后面。
### 注意事项
- 在建图的时候需要注意，只能斜着走且不能到达和仙人掌相邻的格子；
- 多测不清空，爆零两行泪；清空不规范，TLE 总相伴。

---

## 作者：CENRUIYANG (赞：1)

题意可以转化为：我们需要找到一条从第一列开始到最后一列结束的“斜联通”合法路径。因为保证了是“斜联通”，所以这条路径上的点不可能自相矛盾，路径上的点一定不会相邻，所以只要不与原有仙人掌冲突就是合法的。

这相当于一个从第一列到最后一列的最短路，走到原有仙人掌上的边权是 $0$ ，走到空地上的边权是 $1$。我们可以使用 $\texttt{dijkstra}$ 求解，令 $nm=N$，时间复杂度为 $O(N\log N)$。

有没有更好的求这个最短路的办法？发现边权都是 $0/1$ 所以可以用双端队列 $\texttt{bfs}$（实际上就是 $\texttt{dijkstra}$ 去掉了优先队列的 $\log$（？））。时间复杂度为 $O(N)$（但是由于本人当时傻了是用 `map` 来维护点的所以 $\log$ 依然存在，可以映射成一维的点去掉这个 $\log$）。

[代码](https://codeforces.com/contest/1749/submission/180257425)

---

