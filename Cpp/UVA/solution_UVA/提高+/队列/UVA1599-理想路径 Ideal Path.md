# 理想路径 Ideal Path

## 题目描述

## 本题有多组数据


# 理想路径（Ideal Path, NEERC 2010, UVa1599）

给定一个$n$个点$m$条边的无向图，每条边上都涂有1种颜色。求点$1$到点$n$的一条路径，**使得经过的边数最少**，在此前提下，经过边的颜色序列最小。可能有自环与重边。输入保证至少存在一条连接$1$和$n$的道路。

## 说明/提示

$2\leq n \leq 10^5, 1 \leq m \leq 2 \times 10^5,1\leq c_i \leq 10^9$。

对于任意$i \in [1,m]$有$1 \leq a_i,b_i \leq n$。

注：对于两个长度为$k$的序列$a,b$，当存在$i \in [1,k]$使$a_i < b_i$，且对于任意$j \in [1,i)$都有$a_j = b_j$时，$a<b$。

原文：A sequence (a1, a2, . . . , ak) is lexicographically smaller than a sequence (b1, b2, . . . , bk) if there
exists i such that ai < bi
, and aj = bj for all j < i.

感谢@Sparky_14145 提供的翻译

# 题解

## 作者：珈乐唯毒 (赞：13)

大家题解都是两三次bfs呢，这里来一个一次bfs的

代码思路：
经过的边数最少很容易做到，相当于做一个边权值都是1的最短路。

重点考虑字典序最小的问题（字典序小指边数相等的前提下，先走的边的颜色要尽量小）。

我们记录了每个节点的前一个节点(f数组)，也就知道到达某个节点的最短路的最后一条边的颜色，如果在路径长度相同的情况下选择保留最后一条边颜色较小的路径的话，只能保证靠后的边颜色小，无法保证靠前的边颜色小。

上 ~~AC~~ 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int max_=1000000005;
int n,m;
struct LMG {
	int c,x;
} b;
int a,e;
int f[100005];
int fc[100005],d[100005],l;
queue<int> q;
vector<LMG> g[100005];
bool vis[1000005];
int main() {
//	freopen("uva.in","r",stdin);
//	freopen("uva.out","w",stdout);
	while(cin>>n>>m) {
		for(int i=1; i<=n; i++)g[i].clear();
		while (!q.empty()) q.pop();
		l=0;
		for(int i=1; i<=m; i++) {
			cin>>a>>b.c>>b.x;
			g[a].push_back(b);
			swap(a,b.c);
			g[a].push_back(b);
		}
		for(int i=1; i<=n; i++) {
			fc[i]=max_;
			d[i]=max_;
			vis[i]=0;
			f[i]=0;
		}
		q.push(n);
		vis[n]=1;
		d[n]=0;
		while(!q.empty()) {
			int a=q.front();
			q.pop();
			for(int i=0; i<g[a].size(); i++) {
				if(vis[g[a][i].c]==0) {
					q.push(g[a][i].c);
					d[g[a][i].c]=d[a]+1;
					vis[g[a][i].c]=1;
				}
				if(fc[g[a][i].c]>g[a][i].x&&d[g[a][i].c]==d[a]+1) {
					fc[g[a][i].c]=g[a][i].x;
					f[g[a][i].c]=a;
				}
			}
		}
		a=1;
		do {
			l++;
			a=f[a];
		} while(a!=n);
		cout<<l<<endl;
		a=1;
		do {
			cout<<fc[a];
			if(f[a]!=n)cout<<' ';
			a=f[a];
		} while(a!=n);
		cout<<endl;
	}

	return 0;
}
```
当然这样是错的

~~毕竟AC被杠掉了呢~~

反例如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/fwydxs4b.png?x-oss-process=image/resize,m_lfit,h_170,w_225)
```
输入：
6 6
6 5 1
5 4 4
4 1 2
1 2 2
2 3 2
3 6 3
```
当前边颜色相同的情况没有考虑。
这种时候应该一直向前找，直到找到不同的，然后判断字典序

**真正的AC代码**
```
#include<bits/stdc++.h>
using namespace std;
const int max_=1000000005;
int n,m;
struct LMF {
	int c,x;//c为编号，x为边权 
} b;
int a,e;
int f[100005],fa,faa;
int fc[100005],d[100005],l;//fc存当前点上一个边的颜色，f存上一个点的编号 
queue<int> q;
vector<LMF> g[100005];
bool vis[1000005];
int main() {
	while(cin>>n>>m) {//多组数据！！！多组数据！！！多组数据！！！多组数据！！！ 
		for(int i=1; i<=n; i++)g[i].clear();
		while (!q.empty()) q.pop();
		l=0;//清零 
		for(int i=1; i<=m; i++) {
			cin>>a>>b.c>>b.x;
			g[a].push_back(b);
			swap(a,b.c);
			g[a].push_back(b);
		}
		for(int i=1; i<=n; i++) {
			fc[i]=max_;
			d[i]=max_;
			vis[i]=0;
			f[i]=0;
		}
		q.push(n);
		g[1].clear();
		vis[n]=1;
		d[n]=0;
		while(!q.empty()) {
			int a=q.front();
			q.pop();
			for(int i=0; i<g[a].size(); i++) {
				if(vis[g[a][i].c]==0) {//没有到过这个点 
					q.push(g[a][i].c);//push进去
					d[g[a][i].c]=d[a]+1;
					fc[g[a][i].c]=g[a][i].x;
					f[g[a][i].c]=a;
					vis[g[a][i].c]=1;//一堆更新 
				}
				if(d[g[a][i].c]<=d[a])continue;//如果下一个节点的距离比本节点还长,就不加考虑 
				if(fc[g[a][i].c]>g[a][i].x&&d[g[a][i].c]==d[a]+1) {
					fc[g[a][i].c]=g[a][i].x;
					f[g[a][i].c]=a;
					continue; 
				}//如果字典序此处就小立马更新
				if(fc[g[a][i].c]==g[a][i].x){
					faa=f[g[a][i].c];
					fa=a;
					while(fc[faa]==fc[fa]&&faa!=fa){//一层一层向上找 
						fa=f[fa];
						faa=f[faa];
					}
					if(fc[fa]<fc[faa])f[g[a][i].c]=a;//如果字典序更小,更新 
				}
			}
		}
		a=1;
		do {
			l++;
			a=f[a];
		} while(a!=n);
		cout<<l<<endl;
		a=1;
		do {
			cout<<fc[a];
			if(f[a]!=n)cout<<' ';
			a=f[a];
		} while(a!=n);
		cout<<endl;//平平无奇的输出
	}
	return 0;
}
```


---

## 作者：紫题 (赞：10)

## 题目大意：满足最短路的条件下，求出字典序最小的路径并输出

如果只是单纯的求最短路，对于这题只需要一遍dfs即可；输出具体路径也很简单，用$pre[i]$维护每个点的前驱节点就行了。

但是这题还要按照字典序输出，字典序和路径权值没有什么必然的关系，所以要先求出所有的最短路再考虑字典序的问题。 最小字典序只要一次BFS就可以找出来，后面会详细说。

我们知道，**单源最短路径**求出的是源点（起点）到所有点的最短路，其中会有一些路径并没有到达终点，我们要在求字典序的时候把这些无用的路径剔除

同样的，**单汇最短路径**求出的是汇点（终点）到所有点的最短路，其中会有一些路径并没有到达起点。**只要在这两种路径中取交集，剩下的就是起点到终点的最短路径。**

具体地来说，只要从起点跑一遍单源最短路（这题可以直接BFS），然后**建一个反图**（边的方向相反的图），然后从终点BFS一遍，看遍历到的哪些点在最短路径上即可

这题的边是无向边，所以省了建反图的功夫，在起点跑一遍单源最短路后直接从终点BFS一遍即可找出所有起点到终点的最短路了。

找到所有最短路后，就只剩寻找最小字典序了。可以从起点再来一次BFS，每一层扩展的时候**及时剔除字典序一定更大的节点**，保留当前字典序最小的节点用于下一次扩展就行了。

从最短路到字典序一共用了3次BFS，其实还可以做的更好：从终点开始求一次单源最短路，然后再从起点开始BFS，这样就可以在一次BFS中求出最短路的同时找出字典序最小的路径了。

$Code:$ （不卡常80ms）
```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<cstring>
using namespace std;
int ver[400010],color[400010],first[100010],nxt[400010],cnt=1;
int que[400010],dis[100010],n,m;
bool vis[100010];
vector<int>ans;
void init(){ //初始化
	memset(vis,0,sizeof(vis));
	memset(first,0,sizeof(first));
	memset(dis,-1,sizeof(dis));
	ans.clear();
	cnt=1;
}
void add(int x,int y,int z){ //加边
	ver[++cnt]=y;color[cnt]=z;nxt[cnt]=first[x];first[x]=cnt;
}
void invbfs(){ //最短路
	int head=0,tail=1;
	que[0]=n,dis[n]=0; //一开始队列中只有终点
	while(head!=tail){
		int u=que[head];head++;
		for(int k=first[u];k;k=nxt[k]){
			int v=ver[k];
			if(dis[v]!=-1) continue;
			dis[v]=dis[u]+1;
			que[tail++]=v;
		}
	}
}
void bfs(){
    int head=0,tail=1;
	que[0]=1;vis[1]=1; //一开始队列中只有起点
	while(head!=tail){
		vector<int>c;
		while(head!=tail){ //将队列中的点全部取出到一个vector中
		//这样做是方便在后续操作中将只字典序最小的节点放入队列扩展
			c.push_back(que[head]);head++;
		}
		int minn=0x3f3f3f3f;
		for(int i=0;i<(int)c.size();i++){
			int u=c[i];
			for(int k=first[u];k;k=nxt[k]){
			    int v=ver[k];
				if(dis[v]+1==dis[u]) minn=min(color[k],minn);
				//是最短路则记录最小字典序
			}
		}
		if(minn==0x3f3f3f3f) return;
		ans.push_back(minn);//压入答案序列中
		for(int i=0;i<(int)c.size();i++){
			int u=c[i];
			for(int k=first[u];k;k=nxt[k]){
			    int v=ver[k];
				if(dis[v]+1==dis[u]&&color[k]==minn&&!vis[v]){
			    //将在最短路上且字典序最小的节点放回队列中扩展
					que[tail++]=v;
					vis[v]=1;
				}
			}
		}
	}
}
void solve(){
    init();
    int x,y,z;
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&x,&y,&z);
		add(x,y,z);add(y,x,z);
	}
	invbfs();
	bfs();
	printf("%d\n",ans.size());
	for(int i=0;i<(int)ans.size();i++) //输出路径
	printf("%d%c",ans[i],i+1==(int)ans.size()?'\n':' ');
}
int main(){
	while(scanf("%d%d",&n,&m)==2) solve(); //一开始没注意多组数据，WA哭了
	return 0;
}

```


---

## 作者：XenonWZH (赞：3)

[更好的阅读体验请点这！](https://xenonwzh.github.io/uva-1599/)

# 本题题意

给定一个 $n$ 个点 $m$ 条边的无向图，每条边上都涂有 $1$ 种颜色。求点 $1$ 到点 $n$ 的一条路径，使得经过的边数最少，在此前提下，经过边的颜色序列最小。可能有自环与重边。输入保证至少存在一条连接 $1$ 和 $n$ 的道路。

# 解题思路

本题为求图论最短路，由于不需要考虑边权，可使用 BFS。

这道题在路径最短的情况下使得颜色所组成的字典序最小，可以分开解决。

首先解决最短路问题，求出所有的从 $1$ 到 $n$ 的最短路路径。这一步可通过记录从 $n$ 到 $1$ 可到达所有点的步数即可。利用该方法可从 $1$ 遍历可达路径，只要满足在记录中将达到的点的步数为之前的点的步数减一即为从 $1$ 到 $n$ 的最短路或最短路的一部分，这一步可通过 BFS 解决，代码中对应的是 `bfsK` 函数。

接下来就要解决字典序最小。我们需要再一次使用 BFS 以求出在所有最短路中字典序最小的一条。由于最终长度相同，我们始终仅需选择字典序最小的节点。若两节点字典序相同，则都存入考虑范围。由于该次 BFS 无需进行队列弹出操作，且存入的节点同一层可能有多个，存储全部队列空间可能会爆，所以我们需要将队列改写滚动样式，仅存储最上层和次上层即可。代码中对应的是 `bfsCol` 函数。

注意在 `bfsCol` 函数中合理处理最短路步数的标记。同时注意应在全部字典序的节点都压入队列时再进行滚动操作。


# 代码演示

这次 AC 代码有点丑，请见谅 ≧ ﹏ ≦

```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

const int MAXN = 100000, INF = 200000;

int n, m;
std::vector< std::pair<int, int> > e[MAXN + 1];
int vis[MAXN + 1], ans;
int col[INF + 1];

void bfsK() {
    static std::queue< std::pair<int, int> > qK;
    memset(vis, -1, sizeof(vis));
    qK.push( std::make_pair(n, 0) );
    vis[n] = 0, ans = INF;

    while (!qK.empty()) {
        auto u = qK.front();
        qK.pop();
        if (u.first == 1 && u.second < ans) ans = u.second;
        for (auto ed : e[u.first]) {
            if (vis[ed.first] == -1) {
                vis[ed.first] = u.second + 1;
                qK.push(std::make_pair(ed.first, u.second + 1));
            }
        }
    }
}

void bfsCol() {
    static std::vector<int> qCol;
    static bool mk[MAXN + 1];  // 此为已访问节点的标记
    memset(col, 0x3f, sizeof(col));
    memset(mk, false, sizeof(mk));
    qCol.clear();
    qCol.push_back(1);

    int cnt = ans - 1;
    bool flag = true;
    while (cnt >= 0) {
        static std::vector<int> uSet;
        if (flag) {  // 注意滚动的时机
            uSet.clear();
            for (int each : qCol) uSet.push_back(each);
            qCol.clear();
        }
        flag = true;
        for (int u : uSet) {
            for (auto ed : e[u]) {
                if (vis[ed.first] == cnt) {
                    if (!mk[ed.first]) {
                        if (col[cnt] >= ed.second) {
                            if (col[cnt] > ed.second) qCol.clear();
                            col[cnt] = ed.second;
                            mk[ed.first] = true;
                            flag = false;
                            qCol.push_back(ed.first);
                        }
                    } else if (col[cnt] > ed.second) col[cnt] = ed.second;
                }
            }
        }
        if (flag) {  // 若无符合条件的节点，说明已遍历完。最短路步数加一。
            cnt--;
            for (int u : uSet) {
                for (auto ed : e[u]) {
                    if (vis[ed.first] == cnt) {
                        if (!mk[ed.first]) {
                            if (col[cnt] >= ed.second) {
                                if (col[cnt] > ed.second) qCol.clear();
                                col[cnt] = ed.second;
                                mk[ed.first] = true;
                                flag = false;
                                qCol.push_back(ed.first);
                            }
                        } else if (col[cnt] > ed.second) col[cnt] = ed.second;
                    }
                }
            }
        }
    }
}

int main() {
    while (std::cin >> n >> m) {
        for (int i = 1; i <= n; i++) e[i].clear();

        for (int i = 0, x, y, z; i < m; i++) {
            scanf("%d%d%d", &x, &y, &z);
            if (x == y) continue;
            e[x].push_back( std::make_pair(y, z) );
            e[y].push_back( std::make_pair(x, z) );
        }

        for (int i = 1; i <= n; i++) std::sort(e[i].begin(), e[i].end());

        bfsK();
        bfsCol();

        std::cout << ans << std::endl;
        // UVA毒瘤！卡我输出格式！
        for (int i = ans - 1; i >= 0; i--) printf("%d%c", col[i], i == 0 ? '\n' : ' ');
    }

    return 0;
}
```


---

## 作者：EuphoricStar (赞：3)

## 思路

一开始从终点开始进行一次反序 BFS，得到每个节点 $u$ 到终点的最短距离 $d\,[\,u\,]$。

然后直接从起点开始走，但是每次到达一个新节点时要保证 $d$ 值恰好减少 $1$，直到到达终点。

如果有多种走法，选颜色字典序最小的走；

如果有多条边的颜色字典序都是最小，则记录所有这些边的终点，走下一步时要考虑从所有这些点出发的边。

这实际上又是做了一次 BFS，因此时间复杂度仍然为 $O(m)$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, m, dis[100100];
struct edge {
    int u, v, c;
};
vector<edge> edges;
vector<int> g[100100], ans;
bool vis[100100];
queue<int> q;

int main() {
    while (scanf("%d%d", &n, &m) == 2) {
        edges.clear();
        while (!q.empty()) {
            q.pop();
        }
        ans.clear();
        memset(vis, 0, sizeof(vis));
        memset(dis, 0, sizeof(dis));
        for (int i = 1; i <= n; ++i) {
            g[i].clear();
        }
        for (int i = 0; i < m; ++i) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            edges.push_back({a, b, c});
            g[a].push_back(edges.size() - 1);
            edges.push_back({b, a, c});
            g[b].push_back(edges.size() - 1);
        }
        q.push({n});
        vis[n] = 1;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i = 0; i < g[u].size(); ++i) {
                edge e = edges[g[u][i]];
                if (vis[e.v]) {
                    continue;
                }
                dis[e.v] = dis[u] + 1;
                vis[e.v] = 1;
                q.push(e.v);
            }
        }
        memset(vis, 0, sizeof(vis));
        vis[1] = 1;
        vector<int> next;
        next.push_back(1);
        for (int i = 0; i < dis[1]; ++i) {
            int minc = INT_MAX;
            for (int j = 0; j < next.size(); ++j) {
                int u = next[j];
                for (int k = 0; k < g[u].size(); ++k) {
                    int v = edges[g[u][k]].v;
                    if (dis[u] == (dis[v] + 1)) {
                        minc = min(minc, edges[g[u][k]].c);
                    }
                }
            }
            ans.push_back(minc);
            vector<int> next2;
            for (int j = 0; j < next.size(); ++j) {
                int u = next[j];
                for (int k = 0; k < g[u].size(); ++k) {
                    int v = edges[g[u][k]].v;
                    if (dis[u] == (dis[v] + 1) && !vis[v]
                        && edges[g[u][k]].c == minc) {
                        vis[v] = 1;
                        next2.push_back(v);
                    }
                }
            }
            next = next2;
        }
        printf("%d\n%d", ans.size(), ans[0]);
        for (int i = 1; i < ans.size(); ++i) {
            printf(" %d", ans[i]);
        }
        putchar('\n');
    }
    return 0;
}
```


---

## 作者：安静学习 (赞：2)

这道题是用bfs求出来最短路，但是关键是要边的字典序最小


对于每一次先求处最小的颜色可以是什么

然后可以在现在所在点中延伸出去的边里面，找出所以边的字典序最小的那个

存储每一个边连到的下一个结点(因为可能一个点有多个最短边)

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 100000 + 5;

int d[maxn],n,m,vis[maxn];
vector <int> G[maxn];

struct node{
    int e,v,c;
    node(int e = 0,int v = 0,int c = 0):e(e),v(v),c(c){}
};

vector <node> edge;

void AddEdge(int e,int v,int c);

void bfs();

void re_bfs();

int main(){
    while(cin >> n >> m){
        memset(d,0,sizeof(d));
        for(int i = 0;i < n;i++){
            G[i].clear();
        }
        edge.clear();
        for(int i = 0;i < m;i++){
            int a,b,c;
            cin >> a >> b >> c;
            AddEdge(a - 1,b - 1,c);
            AddEdge(b - 1,a - 1,c);
        }
        bfs();//得到各点开始到终点的距离
        re_bfs();
    }
    return 0;
}

void AddEdge(int e,int v,int c){
    edge.push_back(node(e,v,c));
    G[e].push_back(edge.size() - 1);
}

void bfs(){
    memset(vis,0,sizeof(vis));
    d[n - 1] = 0;
    queue <int> que;
    que.push(n-1);
    vis[n - 1] = 1;
    while(!que.empty()){
        int u = que.front();que.pop();
        for(int i = 0;i < G[u].size();i++){
            int v = G[u][i];
            v = edge[v].v;
            if(!vis[v]){
                //cout << u << ' ' << v << endl;
                vis[v] = 1;
                d[v] = d[u] + 1;
                que.push(v);
            }
        }
    }
    cout << d[0] << endl;
}

void re_bfs(){
    queue <int> que;
    que.push(0);
    memset(vis,0,sizeof(vis));
    vector <int> ans;
    vector <int> next;
    next.push_back(0);
    vis[0] = 1;
    memset(vis,0,sizeof(vis));
    for(int i = 0;i < d[0];i++){
        int color = 1000000000 + 10;
        for(int j = 0;j < next.size();j++){
            int u = next[j];
            for(int k = 0;k < G[u].size();k++){
                int e = G[u][k];
                int v = edge[e].v;
                //cout << u << ' ' << v << endl;
                if(d[v] == d[u] - 1){
                    color = min(color,edge[e].c);
                }
            }
        }
        //cout << endl;
        ans.push_back(color);
        //cout << color << endl;
        vector <int> next2;
        for(int j = 0;j < next.size();j++){
            int u = next[j];
            for(int k = 0;k < G[u].size();k++){
                int e = G[u][k];
                int v = edge[e].v;
                //cout << e << ' ' << v << endl;
                if(color == edge[e].c && d[v] == d[u] - 1 && !vis[v]){
                    vis[v] = 1;
                    //cout << v << endl;
                    next2.push_back(v);
                }
            }
        }
        next = next2;
    }
    cout << ans[0];
    for(int i = 1;i < ans.size();i++){
        cout << ' ' << ans[i];
    }
    cout << endl;
}

```

---

## 作者：wyp20130701 (赞：0)

按照紫书上的，先在终点开始 BFS 求出每个点到终点的距离，再从起点开始搜索，每次找邻接结点中能更进一步的点，要比较颜色的字典序来筛选，把最小的都留下。重复此步骤，每次输出最小颜色值即可。  
数据挺大的，花了好久时间，终于不是 TLE 了，不得不说 map 是真的慢，在速度方面似乎越原始的东西越好，所以直接用结构体来存边的权值。注意不仅仅是在逆向 BFS 更新距离时要注意用 $vis[]$ 数组防止点重复入队，在从起点开始搜索时也得判重才能不超时。

代码如下：

```cpp
#include<cstdio>
#include<vector>
#include<cstring>
#include<queue>
using namespace std;
typedef long long ll;
const ll inf = 1e9 + 5;
const int maxn = 100000 + 5;
int n, m, d[maxn], vis[maxn], nextNode[maxn], tempNode[maxn];
struct edge {
	int v, w;
	edge(int b, int c) :v(b), w(c) {}
};
vector<edge>e[maxn];
int main(void) {
	while (~scanf("%d %d", &n, &m)) {
		memset(vis, 0, sizeof(vis));
		memset(d, inf, sizeof(d));
		for (int i = 1; i <= n; i++)e[i].clear();
		while (m--) {
			int a, b; ll c;
			scanf("%d %d %lld", &a, &b, &c);
			e[a].push_back(edge(b, c));
			e[b].push_back(edge(a, c));
		}
		queue<int>Q;
		Q.push(n);
		vis[n] = 1;
		d[n] = 0;
		while (!Q.empty()) {
			int u = Q.front(); Q.pop();
			for (int i = 0; i < e[u].size(); i++) {
				int v = e[u][i].v;
				if (vis[v])continue;
				vis[v] = 1;
				d[v] = d[u] + 1;
				Q.push(v);
			}
		}
		memset(vis, 0, sizeof(vis));
		vis[1] = 1;
		int size = 0;
		nextNode[size++] = 1;
		printf("%d\n", d[1]);
		for (int step = 0; step < d[1]; step++) {
			int cnt = 0;
			ll minColor = inf;
			for (int i = 0; i < size; i++) {
				int u = nextNode[i];//所有的u和n的距离都相同
				for (int j = 0; j < e[u].size(); j++) {
					int v = e[u][j].v;
					if (d[v] != d[u] - 1)continue;//保证再走一步会缩小距离
					if (e[u][j].w <= minColor) {//找最小的颜色
						if (e[u][j].w < minColor) {
							cnt = 0; minColor = e[u][j].w;
						}
						tempNode[cnt++] = v;
					}
				}
			}
			printf("%lld%c", minColor, (step == d[1] - 1) ? '\n' : ' ');
			int cnt2 = 0;
			for (int i = 0; i < cnt; i++) {
				if (vis[tempNode[i]]) continue;
				vis[tempNode[i]] = 1;
				nextNode[cnt2++] = tempNode[i];
			}
			size = cnt2;
		}
	}
	return 0;
}

```

---

## 作者：sto_yxc_orz (赞：0)

好题

[题目传送门](https://www.luogu.com.cn/problem/UVA1599)

第一问明显 ```BFS``` 求一下最短路就好了。

第二问可以根据最短路进行分层，每次找通往下一层中的边上颜色最小的，所以第一问我们最短路倒着做。

关于颜色相同的情况，我们全都放进队列就好了。

时间上相当于做了一遍 ```BFS``` ，所以时间复杂度 $O(n+m)$ 。

$Code:$
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n,m;
vector<pair<int,int> > q[N];
int vis[N];
int dist[N];
void bfs(int u)
{
	memset(dist,-1,sizeof dist);
	queue<int> q1;
	q1.push(u);
	dist[u]=0;
	
	while(q1.size())
	{
		auto to=q1.front();
		q1.pop();
		
		for(auto t:q[to])
		{
			if(dist[t.first]!=-1)	continue;
			else{
				dist[t.first]=dist[to]+1;
				q1.push(t.first);
			} 
		}
	}
}
int ans[2*N];
void bfs1(int u)
{
	queue<int> q1;
	q1.push(u);
	vis[u]=1;
	while(q1.size())
	{
		vector<int> vec;
		while(q1.size())
		{
			vec.push_back(q1.front());
			q1.pop();
		}
		
		int minn=0x3f3f3f3f;
		for(auto t:vec)
		{
			for(auto to:q[t])
			{
				if(dist[to.first]+1==dist[t]) minn=min(minn,to.second);
			}
		}
		
		ans[dist[vec[0]]]=min(ans[dist[vec[0]]],minn);

		for(auto t:vec)
			for(auto to:q[t])
			{
				if(to.second==minn&&dist[to.first]+1==dist[t]&&!vis[to.first])
				{
					q1.push(to.first);
					vis[to.first]=1;
				}
			}
	}
}
int main()
{
	while(cin>>n>>m)
	{	
	
		memset(ans,0x3f,sizeof ans);
		for(int i=1;i<=m;i++)
		{
			int a,b,c;
			scanf("%d%d%d",&a,&b,&c);
			q[a].push_back({b,c});
			q[b].push_back({a,c});
		}
		
		bfs(n);
	
		cout<<dist[1]<<endl;
		bfs1(1);
	
		cout<<ans[dist[1]];
		for(int i=dist[1]-1;i>=1;i--)	cout<<" "<<ans[i];
		cout<<endl;
		for(int i=1;i<=n;i++)
		{
			q[i].clear();
		}
		for(int i=1;i<=n;i++)	vis[i]=0;
	}
	return 0;
}
```



~~**注意多测**~~

---

## 作者：pengzy (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/UVA1599)

### 分析：
本题求解节点 $1$ 到 $n$ 的最短距离，在此前提下，色号序列最小。可以先求解最短距离，然后号察色号。因为在从节点1出发的多条边中，并不知道哪条边是最短路径上的边，所以无法确定最小色号。

### 算法设计：
1. 从节点 $n$ 反向广度优先遍历标高，节点 $1$ 的高度正好为从节点 $1$ 到 $n$ 的最短距离。

2. 从节点 $1$ 正向广度优先遍历，沿着高度减 $1$ 的方向遍历，找色号小的点，如果多个点的色号都最小，则考察下一个色号哪个最小，直到节点 $n$ 结束。

### 代码：

逆向标高求最短距离。

```cpp
void bfs1() 
{
    int u,v;
	memset(vis,false,sizeof(vis));
	dis[n]=0;
	q1.push(n);
	vis[n]=true;
	while(!q1.empty()) {
		u=q1.front();
		q1.pop();
		vis[u]=true;
		for(int i=head[u];i;i=e[i].next) {
			v=e[i].to;
			if(vis[v])continue;
			dis[v]=dis[u]+1;
			q1.push(v);
			vis[v]=true;
		}
	} 
}
```

正向求最小色号序列。

```cpp
void bfs2() 
{
	int u,v,minc,c;
	bool first=true;
	memset(vis,false,sizeof(vis));
	vis[1]=true;
	for(int i=head[1];i;i=e[i].next)//节点1的所有邻接点 
	    if(dis[e[i].to]==dis[1]-1) {//高度减1的邻接点 
	    	q1.push(e[i].to);
	    	q2.push(e[i].c);
		}
	while(!q1.empty()) {
		minc=inf;
		while(!q1.empty()) {
			v=q1.front();
			q1.pop();
			c=q2.front();
			q2.pop();
			if(c<minc) {
				while(!q3.empty())//发现更小的队列并清空
				    q3.pop();
				minc=c; 
			}
			if(c==minc)q3.push(v);
		}
		if(first)first=false;
		else cout<<' ';
		cout<<minc;
		while(!q3.empty()) {//所有为最小色号的节点
		    u=q3.front();
			q3.pop();
			if(vis[u])continue;
			vis[u]=true;
			for(int i=head[u];i;i=e[i].next) {//扩展每一个节点
			    v=e[i].to;
				if(dis[v]==dis[u]-1) {
					q1.push(v);
					q2.push(e[i].c);
				} 
			} 
		}
	}
}
```



---

