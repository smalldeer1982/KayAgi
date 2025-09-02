# [ABC394E] Palindromic Shortest Path

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc394/tasks/abc394_e

给定一个包含 $N$ 个顶点的有向图，顶点编号为 $1, 2, \ldots, N$。

边的信息由 $N^2$ 个字符 $C_{1, 1}, C_{1, 2}, \ldots, C_{1, N}, C_{2, 1}, \ldots, C_{N, N}$ 给出。其中 $C_{i, j}$ 为小写字母或 `-`。

- 当 $C_{i, j}$ 为小写字母时，存在一条从顶点 $i$ 到顶点 $j$ 的边，且该边的标签为 $C_{i, j}$。
- 当 $C_{i, j}$ 为 `-` 时，不存在从顶点 $i$ 到顶点 $j$ 的边。

对于所有满足 $1 \leq i, j \leq N$ 的整数对 $(i, j)$，请回答以下问题：

- 找出从顶点 $i$ 到顶点 $j$ 的路径（不要求是简单路径），使得路径上边标签按顺序组成的字符串是回文。在所有满足条件的路径中，输出最短路径的长度。若不存在这样的路径，输出 $-1$。


## 说明/提示

### 约束条件

- $1 \leq N \leq 100$
- $N$ 为整数
- $C_{i, j}$ 为小写字母或 `-`

### 样例解释 1

以 $(i, j) = (1, 4)$ 为例：路径 $1 \to 1 \to 2 \to 3 \to 4$ 的边标签组成的字符串为 `abba`，这是一个回文。由于不存在长度小于 $4$ 的满足条件的路径，因此 $(i, j) = (1, 4)$ 的答案为 $4$。注意空字符串也被视为回文。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
4
ab--
--b-
---a
c---```

### 输出

```
0 1 2 4
-1 0 1 -1
3 -1 0 1
1 -1 -1 0```

## 样例 #2

### 输入

```
5
us---
-st--
--s--
u--s-
---ts```

### 输出

```
0 1 3 -1 -1
-1 0 1 -1 -1
-1 -1 0 -1 -1
1 3 -1 0 -1
-1 -1 5 1 0```

# 题解

## 作者：gesong (赞：11)

题目传送门：[[ABC394E] Palindromic Shortest Path](https://www.luogu.com.cn/problem/AT_abc394_e)。
# 思路

我们发现如果一个序列是回文，那么在从头和尾分别加入一个相同的字母得到的序列还是回文的。

根据上面的发现我们只需要知道从 $u$ 到 $v$ 的最小回文路径，然后从两个点分别扩展一个点且满足边权相等设为 $v_1,v_2$ 则点 $v_1,v_2$ 的答案即为 $u,v$ 的答案加二，最后按照类似 dij 的方法即可。

记得初始时加入长度为 $1$ 和 $2$ 且回文的路径，具体的可以查看代码。
# 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	char c=getchar();
	int f=1,ans=0;
	while(c<48||c>57) f=(c==45?f=-1:1),c=getchar();
	while(c>=48&&c<=57) ans=(ans<<1)+(ans<<3)+(c^48),c=getchar();
	return ans*f;
}
const int N=110;
#define pii pair<int,int>
int mp[N][N],f[N][N];
struct nord{
	int u,v,w;
	bool operator <(const nord &x) const{
		return w>x.w;
	}
};
priority_queue<nord>q;
vector<pii >a[N],b[N];
main(){
	int n=read();
	memset(f,0x3f,sizeof(f));
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++){
			char x;cin>>x;
			if (x=='-') continue;
			a[i].push_back({j,x-'a'});
			b[j].push_back({i,x-'a'});
			f[i][j]=1;
			q.push({i,j,1});
		}
	for (int u=1;u<=n;u++)
		for (auto vv:a[u])
			for (auto v:a[vv.first])
				if (vv.second==v.second&&v.first!=u){
					f[u][v.first]=min(f[u][v.first],2ll);
					q.push({u,v.first,f[u][v.first]});
				}
	while(!q.empty()){
		int u=q.top().u,v=q.top().v;q.pop();
	//	cout <<u<<" "<<v<<endl;
		if (mp[u][v]) continue;
		mp[u][v]=1;
		for (auto i:b[u])
			for (auto j:a[v])
				if (i.second==j.second){
					int v1=i.first,v2=j.first;
					if (f[v1][v2]>f[u][v]+2){
						f[v1][v2]=f[u][v]+2;
						q.push({v1,v2,f[v1][v2]});
					}
				}
	}
	for (int i=1;i<=n;i++,puts(""))
		for (int j=1;j<=n;j++)
			if (i==j) printf("%lld ",0ll);
			else if (f[i][j]==0x3f3f3f3f3f3f3f3f) printf("-1 ");
			else printf("%lld ",f[i][j]);
    return 0;
}
//AtCoder Beginner Contest 394 RP++
//AtCoder Beginner Contest 394 RP++
//AtCoder Beginner Contest 394 RP++
//AtCoder Beginner Contest 394 RP++
//AtCoder Beginner Contest 394 RP++
```

---

## 作者：Sanust (赞：5)

# AT_abc394_e Palindromic Shortest Path

简述题意，有一个有 $N$ 个顶点的有向图，以邻接矩阵 $C_{i,j}$ 的形式记录了从 $i$ 到 $j$ 这条边上的字符，如果该边不存在则是 $-$。要求对于每一对 $(i,j)$，在从顶点 $i$ 到顶点 $j$ 的所有路径中，找到一条最短且回文的按边走过的顺序形成的路径字符串的长度。

问题的关键在于**处理回文**。记 $ans_{i,j}$ 为从 $i$ 到 $j$ 的满足条件的字符串的最小长度。首先空串是回文的，即对角线上的答案必定是 $0$。再其次单字符是回文的，即如果从起点有一条有向边可以直达终点，那答案必定是 $1$。

那么剩下的情况呢？难道每次要走完全程记录字符串到终点再判定回文吗？其实不然。刚刚所说的两种最基本的情况均满足回文且最短的性质，那么，我们可以考虑一种 “扩展”形式的做法——**如果一个串已经是回文串，那么在它的左右两端各加一个相同字符，那么新串仍然是回文串。**

考虑 BFS。设队列 $(i,j)$ 记录的是已被证明满足性质的起终点点对。我们先把之前两种特殊的回文情况加入队列，每次选中一条从 $i$ 到 $j$ 的路径，且选中的路径已经满足回文且最短的性质，枚举两个点 $(k,l)$ ，使其满足从 $k$ 到 $i$ 有一条非 $-$ 的直达边，从 $j$ 到 $l$ 也有一条非 $-$ 的直达边，且 $c_{k,i} = c_{j,l}$。如果这样的点对 $(k,l)$ 存在且是第一次被遍历到，那么更新答案，并将点对加入队列继续 BFS。

如果搜索完还是没有访问到，那么说明这样的路径不存在。具体的细节可在代码注释里查看。时间复杂度 $\operatorname O(n^4)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 105;
const int INF = 0x3f3f3f3f;
int n, ans[N][N];
char c[N][N];
queue<pair<int, int>> q;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cin >> c[i][j];
    memset(ans, 0x3f, sizeof(ans));
    for (int i = 1; i <= n; i++)
        ans[i][i] = 0, q.push({ i, i }); // 初始化对角线路径字符长度为0，并将它们每个点各自加入队列，此时路径字符为空字符串必定回文
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (i != j && c[i][j] != '-') // 如果起终点不是同一个点且它们之间有边（不是'-'）
                ans[i][j] = 1, q.push({ i, j }); // 直接相连的距离为1，且单字符必定回文
    while (!q.empty())
    {
        auto u = q.front();
        q.pop();
        int i = u.first, j = u.second; // 选中一条从i到j的路，且此时该路径已经满足回文且最短
        for (int k = 1; k <= n; k++)
            if (c[k][i] != '-') // 从k到i有路且走一条边就可直达 从i到j有路 从j到k也有路且走一条边就可直达
                for (int l = 1; l <= n; l++)
                    if (c[k][i] == c[j][l]) // 回文扩展，需要从k到i经过的路径单字符和从j到l所经过的路径单字符相等。用不着刻意判定c[j][l]!='-'，因为c[k][i]在这里必然!='-'，两个字符必定不相等
                        if (ans[k][l] == INF) // 只有在初始未访问状态，即第一次扩展到该路径时更新答案并加入队列，因为BFS第一次扩展到能保证从k到l必定最短
                            ans[k][l] = ans[i][j] + 2, q.push({ k, l }); // 从k出发通过i,j到l的路径长度为ans[i][j]+2，因为左右各多走了一条边，接下来只需要再开始从已经最短的k到l这条路径继续扩展即可
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cout << (ans[i][j] == INF ? -1 : ans[i][j]) << " \n"[j == n]; // 如果仍然是未访问状态，说明无法联通，路径不存在，输出-1
    return 0;
}
```

---

## 作者：Mr_Az (赞：4)

# [AT_abc394_e [ABC394E] Palindromic Shortest Path](https://www.luogu.com.cn/problem/AT_abc394_e)

### Algorithm:

模拟。

### Solution:

观察到可能的回文串非常短，可以直接模拟出来。考虑对于偶数和奇数长度的回文串，笔者的做法是直接暴力预处理出所有长度为 $1$ 和 $2$ 的对 $(i,j)$，拿个 vector 存下来，每次在两边扩展一样的字符。

结束的条件就是没有扩展的对了。通过这个做法也可以证明可能的回文串是有限的，因为你的每次扩展要么新扩展一个对，要么直接结束，最多匹配 $100^2=10000$ 次。

可能写的比较丑陋，有比较好看的实现是这样的：

先把长度为 $1$ 和 $2$ 的对 $(i,j)$ 扔进队列里面，每次模仿最短路扩展，可能会更好看一点？本质是一样的。

### Code:

```cpp
const int N=108;
int n;
int dis[N][N];
char s[N][N];
inline void solve(){
    read(n);
    for(rint i=1;i<=n;i++) for(rint j=1;j<=n;j++) dis[i][j]=-1;
    for(rint i=1;i<=n;i++){
        scanf("%s",s[i]+1);
        dis[i][i]=0;
    }
    vector<pii> one,two;
    for(rint i=1;i<=n;i++){
        for(rint j=1;j<=n;j++){
            if(s[i][j]=='-'||i==j) continue;
            dis[i][j]=1;
            one.pb({i,j});
        }
    }
    for(rint i=1;i<=n;i++){
        for(rint j=1;j<=n;j++){
            for(rint k=1;k<=n;k++){
                if(dis[i][k]!=-1) continue;
                if(s[i][j]==s[j][k]&&s[i][j]!='-') dis[i][k]=2,two.pb({i,k});
            }
        }
    }
    int now=1;
    while(1){
        bool f=1;
        vector<pii> t1,t2;
        for(rint i=1;i<=n;i++){
            for(rint j=1;j<=n;j++){
                if(dis[i][j]==-1){
                    for(auto [x,y]:one){
                        if(s[i][x]==s[y][j]&&s[i][x]!='-'){
                            dis[i][j]=now*2+1;
                            t1.pb({i,j});
                            f=0;
                            break;
                        }
                    }
                }
            }
        }
        one.swap(t1);
        for(rint i=1;i<=n;i++){
            for(rint j=1;j<=n;j++){
                if(dis[i][j]==-1){
                    for(auto [x,y]:two){
                        if(s[i][x]==s[y][j]&&s[i][x]!='-'){
                            dis[i][j]=now*2+2;
                            t2.pb({i,j});
                            f=0;
                            break;
                        }
                    }
                }
            }
        }
        two.swap(t2);
        now++;
        if(f) break;
    }
    for(rint i=1;i<=n;i++){
        for(rint j=1;j<=n;j++) cout<<dis[i][j]<<" ";
        cout<<endl;
    }
}
```

---

## 作者：2huk (赞：3)

考虑朴素 DP。设 $f(a,b)$ 表示 $a \rightsquigarrow b$ 的最短回文路径。转移：
$$
f(a,b) = \min_{C_{a,c}=C_{b,d}\ne -1} (f(c,d) + 2)
$$
表示 $a \to c \rightsquigarrow d \to b$。

一些初始条件是 $f(i,i)=0$，$f(a,b)=1 (C_{a,b}\ne -1)$。

显然这个 DP 是有环的。但是这个转移过程实质上是最短路问题。于是 BFS 即可。

图的点数 $n^2$，边数 $m=n^4$，于是 BFS 复杂度 $\mathcal O(m) = \mathcal O(n^4)$。

---

## 作者：PDAFX (赞：2)

## 题目大意

给你一个图，用邻接矩阵表示，上面有 - 和一些小写英文字母，问从每个点到每个点的最短路，但必须走回文字符串。

## 思路

其实此题爆搜即可，仅仅 $O(n^4)$，在神奇的 AT 机子上能跑过。

但是此题细节甚多，且需要花一些思维。

首先，先把点自身连一条边。

其次，每一条边都赋予 1 的代价。

然后，进行判断即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
char mp[1001][1001];
int n;
int ans[1001][1001];
queue<pair<int,int>>q;
int main()
{
	memset(ans,0x3f,sizeof(ans));
	cin>>n;
	for(int j=0;j<n;j++)
	{
		q.push({j,j});
		ans[j][j]=0;
	}
	for(int i=0;i<n;i++)
	{
//		ans[i][i]=0;
		scanf("%s",mp[i]);
		for(int j=0;j<n;j++)
		{
			if(mp[i][j]!='-'&&i!=j)
			{
				q.push({i,j});
				ans[i][j]=1;
			}
		}
	}
	while(!q.empty())
	{
		auto head=q.front();
		q.pop();
		int x=head.first,y=head.second;
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
//				printf("(%d,%d--%d,%c),(%d,%d--%d,%c)\n",x,y,ans[x][y],mp[i][x],i,j,ans[i][j],mp[y][j]);
				if(mp[i][x]!='-'&&mp[y][j]!='-'&&(mp[i][x]==mp[y][j])&&ans[i][j]==0x3f3f3f3f)
				{
					q.push({i,j});
					ans[i][j]=min(ans[i][j],ans[x][y]+2);
				}
//				printf("(%d,%d--%d,%c),(%d,%d--%d,%c)\n",x,y,ans[x][y],mp[i][x],i,j,ans[i][j],mp[y][j]);
			}
		}
	}
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(ans[i][j]==0x3f3f3f3f)
			{
				cout<<-1<<" ";
			}
			else
			{
				cout<<ans[i][j]<<" ";
			}
		}
		cout<<endl;
	}
}
```

---

## 作者：huhexuan (赞：2)

注意到 $n$ 只有 $100$，于是考虑四次方的暴力。

用广搜的思路，类似于 Floyd 的思想进行转移。

即每次将一条边以及改变所包含的字符个数存入队列，之后枚举两个点，用这条边的信息更新枚举到点的信息。

具体见代码：

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int n,ans[105][105];
bool vis[105][105];
char c[105][105];
struct node{
	int u,v,dis;
};
queue<node>q;
void bfs()
{
	while(!q.empty())
	{
		node now=q.front();
		q.pop();
		for(int i=1;i<=n;i++)
		{
			if(c[i][now.u]!='-')
			{
				for(int j=1;j<=n;j++)
				{
					if(c[i][now.u]==c[now.v][j]&&!vis[i][j]) ans[i][j]=min(ans[i][j],now.dis+2),vis[i][j]=1,q.push({i,j,ans[i][j]});
				}
			}
		}
	}
}
signed main()
{
	cin>>n;
	memset(ans,0x3f,sizeof ans);
	for(int i=1;i<=n;i++) q.push({i,i,0}),ans[i][i]=0,vis[i][i]=1;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			cin>>c[i][j];
			if(c[i][j]!='-'&&i!=j) q.push({i,j,1}),ans[i][j]=1,vis[i][j]=1;
		}
	}
	bfs();
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(ans[i][j]==0x3f3f3f3f3f3f3f3f) cout<<-1<<" ";
			else cout<<ans[i][j]<<" ";
		}
		cout<<"\n";
	}
	return 0;
}

---

## 作者：littlebug (赞：2)

F<<<<<E。

## Solution

显然直接做不好做，所以考虑逆向思考，由每个回文子串去对应相应的节点。设 $d_{u,v}$ 表示 $u \leadsto v$ 的答案。

于是可以想到 bfs，首先已知 $d_{u,u} = 0$，且 $\forall (u,v) \in E : d_{u,v} = 1$，分别对应长度为偶数和奇数的回文串，然后由这些值往外拓展。

具体地，分别建一个正向图和一个反向图，然后遍历 $u$ 在反向图上的出边 $(u,x)$ 和 $v$ 在正向图上的出边 $(v,y)$，如果两边边权相等，则表示 $x \leadsto y$ 可以通过 $x \to u \leadsto v \to y$ 来构成合法解。而又因为 bfs 的性质，所以第一次计算到的一定是最优解。

共有 $O(n^2)$ 个状态，每个状态会有 $O(n^2)$ 种出边组合，所以总复杂度为 $O(n^4)$ 且常数比较小。

## Code

```cpp
int n;
char a[MAXN][MAXN];
vector <pair<int,char>> p[MAXN],rp[MAXN];
queue <pii> q;
int dis[MAXN][MAXN];

il void bfs()
{
	memset(dis,0x3f,sizeof(dis));
	
	rep(i,1,n) q.emplace(i,i),dis[i][i]=0;
	rep(i,1,n) for(auto j:p[i]) q.emplace(i,j.st),i!=j.st && (dis[i][j.st]=1);
	
	int u,v;
	while(!q.empty())
	{
		u=q.front().st,v=q.front().nd,q.pop();
		
		for(auto [x,xc]:rp[u]) for(auto [y,yc]:p[v]) xc==yc && dis[x][y]==inf && (q.emplace(x,y),dis[x][y]=dis[u][v]+2);
	}
}

signed main()
{
	read(n),_::r(a,n,n);
	rep(i,1,n) rep(j,1,n) a[i][j]!='-' && (p[i].pb(j,a[i][j]),rp[j].pb(i,a[i][j]),1);
	
	bfs();
	rep(i,1,n) rep(j,1,n) write(dis[i][j]==inf ? -1 : dis[i][j]," \n"[j==n]);
	
	return 0;
}
```

---

华风夏韵，洛水天依！

---

## 作者：jzwjx (赞：2)

## 题意

给定一个有向图，图上每条边都有一个字母，要求求出从点 $i$ 到点 $j$ 的的边可以组成的最短回文串，如果不行则输出 $-1$。

## 分析

首先我们思考，如何保证所生成的路径能够组成一个回文串，考虑可以从这个回文串的中间入手，每次向外走字母相同的路径，就可以保证所走出的串一定是回文串。

所以我们只需要枚举中间的起点，每次向外扩展，用扩展出来的长度和答案取 $\min$ 就好。

那么如何扩展呢，我们容易想到 bfs，然后就可以发现，只要在队列里维护当前路径的左右端点，每次扩展时暴力枚举左右端点的出边，寻找出边的权值（也就是边上的字母）相同的扩展即可。

但是本题给定的是有向边，如何保证方向的正确性呢，我们只需要给每条边加一个 $flag$，记录这条边是正向的还是反向的，更新时强制要求左端点走反向边，右端点走正向边即可。

**注意：** 由于求的是最短的回文串，所以每一对点只能遍历一次，这是因为第二次遍历到的长度一定大于等于第一次遍历到的长度，所以我们再开一个vis数组存储当前点对是否遍历到过，如果没有，再走就可以了。

还有就是，我们可以发现，这似乎是道原，或者说有一道很像的题——[abc197F](https://www.luogu.com.cn/problem/AT_abc197_f)，写完本题可以去看一眼。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
typedef long long ll;
const int N=11000+100;
int n,m=0,tot=1;
int head[N*3],nxt[N*3],ver[N*3],cnt[N],flag[N*3];
int vis[1010][1010];
char c[110][110];
int anss[1010][1010];
char e[N*3];
vector<pair<int,int> >o;
struct stu{
	int u,v;
}st[N];
struct node{
	int x,y,cnt;
};
ll read(){
	ll f=1,t=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') {
		if(ch=='-') f=-f;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		t=t*10+ch-'0';
		ch=getchar();
	}
	return t*f;
}
void add(int u,int v,char w,int ff){
	ver[++tot]=v;nxt[tot]=head[u];head[u]=tot;e[tot]=w;flag[tot]=ff;
}
void work(int x,int y,int cnt){//bfs
	queue<node>q;
	q.push({x,y,cnt});//x,y分别是当前路径的左右端点，cnt是更新到当前左右端点的最短长度。
	while(q.size()){
		int xx=q.front().x,yy=q.front().y,cntt=q.front().cnt;
		q.pop();
		if(cntt>anss[xx][yy]) continue;//如果当前长度已经大于之前的长度了，那么更新出来的结果一定也大于之前的长度，一定不优，直接continue掉就好。
		anss[xx][yy]=min(anss[xx][yy],cntt);
		for(int i=head[xx];i;i=nxt[i]) {
			if(flag[i]==1) continue;//如果当前边是正向边，就不走。
			for(int j=head[yy];j;j=nxt[j]) {
				if(flag[j]==0) continue;//同上
				if(ver[i]==ver[j]) continue;//如果两个点相同的话，所更新出来的回文串长度一定比直接用这个点更新的长度要长。
				if(vis[ver[i]][ver[j]]) continue;
				if(e[i]==e[j]) {
					vis[ver[i]][ver[j]]=1;
					if(anss[ver[i]][ver[j]]>cntt+2) q.push({ver[i],ver[j],cntt+2});//因为左右各走了一条边，所以+2。
				}
			}
		}
	}
} 
signed main(){
	n=read();
	for(int i=1;i<=n;i++){
		scanf("%s",c[i]+1);
		for(int j=1;j<=n;j++){
			if(c[i][j]=='-') continue;
			add(i,j,c[i][j],1);add(j,i,c[i][j],0);
			st[++m]={i,j};
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			anss[i][j]=0x3f3f3f3f3f3f3f3f;
		}
	}
	if(n==1) {
		cout<<'0'<<endl;
		return 0;
	}
	for(int i=1;i<=n;i++){
		work(i,i,0);
		for(int j=1;j<=n;j++){
			for(int k=1;k<=n;k++){
				vis[j][k]=0;
			}
		}
	}
	for(int i=1;i<=m;i++){
		vis[st[i].u][st[i].v]=1;
		work(st[i].u,st[i].v,1);
		for(int j=1;j<=n;j++){
			for(int k=1;k<=n;k++){
				vis[j][k]=0;
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i==j) {
				printf("0 ");
				continue;
			}
			if(anss[i][j]==0x3f3f3f3f3f3f3f3f) printf("-1 ");
			else printf("%lld ",anss[i][j]);
		}
		printf("\n");
	}
	return 0;
}
```

---

## 作者：MMXIandCCXXII (赞：2)

$\Large{\text{Solution}}$

最开始想到了从两个点暴力拓展，每次找一组字母相同，从起点出和往终点出的边。但是无法直接找到最短路，也会超时。

反过来想，既然从两边出发总会到一条边或一个点上，那么我们就从每个点和每条边出发，每次往两边拓展。由于长度每次都加 $2$，那么我们就可以 BFS，这样就能一次性找到每一对点的答案。

$\Large{\text{Code}}$

```cpp
#include <bits/stdc++.h>
//#define int long long
#define x first
#define y second
using namespace std;
typedef pair <int, int> pii;
typedef long long ll;
typedef unsigned long long ull;
typedef complex <double> cd;
const double PI = acos (-1);
const double eps = 1e-10;
const int N = 2e5 + 10;
const int mod = 1e9 + 7;
//const int mod = 998244353;

char c[510][510];
int f[510][510];
int n;

void bfs()
{
    queue <pair <pii, int> > q;
    memset (f, -1, sizeof f);
    for (int i = 1; i <= n; i++)
        q.push ({{i, i}, 0}), f[i][i] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (c[i][j] != '-' && i != j)
                q.push ({{i, j}, 1}), f[i][j] = 1;
    while (q.size ())
    {
        pair <pii, int> t = q.front ();
        q.pop ();
        int x = t.x.x, y = t.x.y;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (c[i][x] != '-' && c[y][j] != '-' && c[i][x] == c[y][j] && f[i][j] == -1)
                    f[i][j] = f[x][y] + 2, q.push ({{i, j}, f[i][j]});
    }
}

signed main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cin >> c[i][j];
    bfs ();
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
            cout << f[i][j] << " ";
        cout << "\n";
    }
    return 0;
}
```

---

## 作者：chenxi2009 (赞：2)

## 思路
发现回文路径很难从头开始找，不妨从路径中间向两边扩展。

令 $f_{i,j}$ 表示 $i$ 到 $j$ 的最短回文路径长度，初始有 $f_{i,i}\leftarrow0$、$f_{i,j}\leftarrow1(C_{i,j}\ne$`-`$)$。

当用 $f_{i.j}$ 扩展的时候，枚举 $x$ 和 $y$ 分别为扩展出的新的起点、终点，因为需要回文所以转移需要条件 $C_{x,i}=C_{j,y}\wedge C_{x,i}\ne$`-`，转移即 $f_{x,y}\leftarrow f_{i,j}+2$。很好理解吧，就是在原先的一条回文路径 `i->...->j` 两侧接上 $x$ 和 $y$ ，产生一条新的回文路径 `x->i->...->j->y`。

从被初始化的那些 $i,j$ 开始广搜转移是正确的。\
为什么？你可以把这抽象成一个 01 图最短路，转移就是从一个点 $(i,j)$ 走到一个点 $(x,y)$。并不需要我们真的写一个最短路，只是一种理解方法而已。

注意为了保持单调性需要把初始化成 $0$ 的路径在 $1$ 的路径之前推入队列。\
每一对 $(i,j)$ 仅入队一次，每一个 $(i,j)$ 枚举 $N^2$ 对 $(x,y)$ 扩展，时间复杂度 $O(N^4)$。实际上只跑了 100ms 不到。
## 代码
```cpp
#include<bits/stdc++.h> 
using namespace std;
int n,f[200][200];
char c[200][200];
queue<pair<int,int>>q;
int main(){
	memset(f,0x3f,sizeof(f));
	read(n);
	for(int i = 1;i <= n;i ++) scanf("%s",c[i] + 1);
	for(int i = 1;i <= n;i ++) f[i][i] = 0,q.push({i,i});//初始化长度为 0 的路径 
	for(int i = 1;i <= n;i ++) for(int j = 1;j <= n;j ++) 
		if(i != j && c[i][j] != '-') f[i][j] = 1,q.push({i,j});//初始化长度为 1 的路径 
	while(q.size()){//BFS
		int x = q.front().first,y = q.front().second;//从 x -> ... -> y 扩展 
		q.pop();
		for(int i = 1;i <= n;i ++) for(int j = 1;j <= n;j ++) 
			if(c[i][x] != '-' && c[i][x] == c[y][j] && f[x][y] + 2 < f[i][j]) 
				f[i][j] = f[x][y] + 2,q.push({i,j});//如果 i -> x 和 y -> j 相等，x -> 回文，那么 i -> j 也回文，可以转移 
	}
	for(int i = 1;i <= n;i ++){
		for(int j = 1;j <= n;j ++) printf("%d ",f[i][j] == 0x3f3f3f3f ? -1 : f[i][j]);
		printf("\n");
	} 
	return 0; 
}
```

---

## 作者：lhz2022 (赞：1)

由于考场上翻译器坏掉了，把“回文” 翻译成了“重合”，于是理解错了题意，故没有做出。现在来补一下这一题。

我们可以利用一种类似 bfs 的方法解决这个问题。

首先就是对于回文的分类讨论，回文包含两种，长度是奇数的和偶数的。

然后我们对于一个已经是回文的路径，往两边增加一堆相同的字符之后也是回文的，就像这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/5p1niwcx.png)

于是我们设 $dis_{ij}$ 代表 $i$ 到 $j$ 中最短的回文路径，初始时 $dis_{ii}=0$, 如果 $i$ 到 $j$ 存在一条边，则 $dis_{ij}=1$。

然后你发现这一题就做完了。

[代码](https://www.luogu.com.cn/paste/cwvwt4c0)

---

## 作者：wcy110614 (赞：1)

## ABC 394 E

先连边，之后记录每个点 $i$ ，有哪些点有边指向他，记为 $in[i]$，然后记录这个点指向哪些点 $out[i]$。然后记 $f_{i,j}$ 为 $i$ 跑到 $j$ 并且路径回文的最短路径。

做一个队列 $Q$，先放所有 $\{i,i\}$ 进去，因为这些 $f_{i,i}=0$ ，是最小的。之后慢慢 $\text{BFS}$ 更新。依据 $\{i,j\}$ 更新就是枚举 $x,y, x\in in[i], y\in out[i]$，然后更新 $f_{x,y}$，之后又把 $f_{x,y}$ 压进队列里。因为队列中的元素满足单调，所以同一对点只用更新一次，也就是 $O(n^2)$ 的更新。一共 $O(n^2)$ 对点，复杂度 $O(n^4)$。可以通过。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N=105,inf=1061109567;
char ch[N][N];
int n,f[N][N];
struct str{
	int i,j,val;
	bool operator <(const str& t)const{
		return val<t.val;
	}
	str(int I,int J,int VAL){ i=I,j=J,val=VAL; }
};
queue<str>q;
vector<int>in[N],ot[N];
int main(){
	memset(f,0x3f,sizeof f);
	cin>>n;
	for(int i=1;i<=n;++i){
		string Str;
		cin>>Str;
		for(int j=1;j<=n;++j){
			ch[i][j]=Str[j-1];
			if(ch[i][j]!='-'){
				in[j].emplace_back(i);
				ot[i].emplace_back(j);
				q.emplace(str(i,j,1));
				f[i][j]=1;
			}
		}
		q.emplace(str(i,i,0));
		f[i][i]=0;
	}
	while(!q.empty()){
		str s=q.front(); q.pop();
		for(int x:in[s.i])for(int y:ot[s.j]){
			if(ch[x][s.i]==ch[s.j][y]&&f[x][y]>f[s.i][s.j]+2){
				f[x][y]=f[s.i][s.j]+2,q.emplace(str(x,y,f[x][y]));
			}
		}
	}
	for(int i=1;i<=n;++i,cout<<"\n")for(int j=1;j<=n;++j){
		if(f[i][j]!=inf)cout<<f[i][j]<<" ";
		else cout<<"-1 ";
	}
	return 0;
} 
```

---

## 作者：_determination_ (赞：1)

整场最难的题吧。要不是放在 E 我估计我就摆了。

注意到我们初始就能得到一部分答案：$A_{x,x}=0,A_{u,v}=1$。其中 $(u,v)$ 是原图的一条边。

我们考虑如何得到一个回文串，可以从中心向外扩展。那么这个过程直接 bfs 即可。

具体的，现在我们 bfs 到了 $x,y$。我们直接枚举 $x$ 的入边和 $y$ 的出边，如果两条边的边权相同则扩展。

状态是 $O(n^2)$ 的，转移是 $O(n^2)$ 的。总共 $O(n^4)$，但是实际上根本跑不满。

[Link.](https://atcoder.jp/contests/abc394/submissions/63058603)

---

## 作者：fanjiayu666 (赞：1)

### 题意简述

我们有一个有向图，图中有 $N$ 个顶点，编号为 $1, 2, \ldots, N$ 。

边的信息由 $N^2$ 个字符 $C_{1, 1}, C_{1, 2}, \ldots, C_{1, N}, C_{2, 1}, \ldots, C_{N, N}$ 提供。其中，每个 $C_{i, j}$ 都是小写英文字母或 `-`。

如果 $C_{i, j}$ 是小写英文字母，那么从顶点 $i$ 到顶点 $j$ 恰好有一条标有 $C_{i, j}$ 的有向边。如果 $C_{i, j}$ 是"-"，那么从顶点 $i$ 到顶点 $j$ 就没有边。

请就每个整数对 $(i, j)$ 与 $1 \leq i, j \leq N$ 回答下面的问题：

- 在从顶点 $i$ 到顶点 $j$ 的所有（不一定是简单的）路径中，如果各条路径边上的标签连起来构成一个回文串，那么最短路径的长度是多少？如果没有这样的路径，答案为 $-1$ 。

### 方法概括

首先，乍一看题目又复杂有难，我赛时没咋看，直接去写 F 的树形 dp，结果写挂了，回来看时，才发现是个简单的 BFS。

将答案数组 $ans$ 初始化为 $-1$。

既然已知是 BFS，那我们来看看过程：

1. 分两种情况，将起始点加入队列：
> 1. 对于 $(1,1),(2,2),(3,3),\dots ,(N,N)$ 加入队列时注意将 $ans_{i,i}$ 初始化为 $0$，因为只有这时候出现回文串长度始终 $=0$。
> 2. 否则，如果当前位置有连接到其他的边，将 $ans_{i,j}$ 初始化为 $1$，因为这时长度始终 $=1$，因为经过自己是最佳答案。
2. 进行 BFS ：
设当前节点为 $(x,y)$，枚举到的为 $(i,j)$。
> 枚举所有节点，如果存在 $C_{i,x}=C_{y,j}$ 并且 $ans_{i,j}=-1$ 就更新 $ans_{i,j}=ans_{x,y}+2$ 即增加 $2$ 长度。
3. 输出答案。

code：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
    int x,y;
};
int n;
char s[110][110];
int ans[110][110];
queue<node>  q;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>s[i][j];
            ans[i][j]=-1;
        }
    }
    for(int i=1;i<=n;i++){
        ans[i][i]=0;
        q.push(node{i,i});
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(i!=j&&s[i][j]!='-'){
                ans[i][j]=1;
                q.push(node{i,j});
            }
        }
    }
    while(!q.empty()){
        int x=q.front().x,y=q.front().y;
        q.pop();
        for(int i=1;i<=n;i++){
            if(s[i][x]!='-'){
                for(int j=1;j<=n;j++){
                    if(s[i][x]==s[y][j]&&ans[i][j]==-1){
                        ans[i][j]=ans[x][y]+2;
                        q.push(node{i,j});
                    }
                }
            }
        } 
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cout<<ans[i][j]<<" ";
        }
        cout<<"\n";
    }
}
```

[AC记录](https://www.luogu.com.cn/record/204619986)

---

## 作者：__FL__ (赞：1)

不是很难想的题，但是差点把我卡爆了。
## 题意
给定一个有向图，每条边的权值用一个小写字母来描述。询问对于每组 $1 \le i,j \le N$，在从 $i$ 到 $j$ 的权值连起来为**回文**的路径中，最小长度是多少，不能到达输出 $-1$。
## 思路
直接用类似最短路的算法似乎很难处理回文的要求，于是考虑到回文的特性，我们可以直接从两边进行 BFS。

参考 BFS 的思想，对于当前点对 $(u,v)$，枚举 $u$ **能到达的点**和**能到达** $v$ **的点**，如果边的字母相同且未被访问，就压入新的点对，直到 $u = v$ 或 $u$ 可以直接到达 $v$。

注意这里的细节，$u$ 可以直接到达 $v$ 的情况需要等到一直处理完步数和现在相等的情况再返回，因为这样的情况答案要加 $1$，可能还会出现搜索步数相同但不用加 $1$ 的情况（即 $u=v$ 时）。
## 优化
直接使用这样的思路可能会 TLE，因为我们单次查询的复杂度最坏就达到了 $O(n^4)$（因为寻找新点对时浪费了大量时间），考虑优化。我们发现在每次枚举新的点对并压入的时候，会枚举 $n^2$ 次，但实际可能更新了很少的数量。那么我们可以改变建图策略，直接存储某个点每个字母所对应的子节点，寻找点对时直接枚举字母，省去了很多时间。

这个思路需要多建一个反图。
## 代码

```cpp
#include<bits/stdc++.h>
#define PIII pair<pair<int,int>,int>
using namespace std;
int n,ans,l;
char a;
pair<int,int>era[10005];
bool vis[105][105];
vector<int>vec[105][26],rvec[105][26];
queue<PIII>q;
int bfs(int x,int y)
{
	while (!q.empty()) q.pop();
	q.push({{x,y},0});
	memset(vis,0,sizeof vis);
	l = 0;
	vis[x][y] = 1;
	ans = 99999999;
	while (!q.empty())
	{
		PIII now = q.front();
		q.pop();
		int tx = now.first.first;
		int ty = now.first.second;
		if (now.second*2 >= ans) return ans;
		if (tx == ty)
		{
			return now.second*2;
		}
		for (int i = 0; i < 26; i++)
			for (int j: vec[tx][i])
			{
				if (j == ty)
				{
					ans = now.second*2+1;
				}
			}
		for (int i = 0; i < 26; i++)
			for (int j: vec[tx][i])
			for (int k: rvec[ty][i])
			{
				if (!vis[j][k])
				{
					vis[j][k] = 1;
					q.push({{j,k},now.second+1});
				}
			}
	}
	if (ans != 99999999) return ans;
	return -1;
}
int main()
{
	ios_base::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
		{
			cin >> a;
			if (a == '-') continue;
			vec[i][a-'a'].push_back(j);
			rvec[j][a-'a'].push_back(i);
		}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
			cout << bfs(i,j) << ' ';
		cout << '\n';
	}
	return 0;
}
```

---

## 作者：wuzebang2009 (赞：1)

题目大致意思是让你求两点之间的最短回文路径，这题我开始时写了个大爆搜， $O(n^2n!)$ ，显然不行，~~竟然还过了10个点~~，所以我们加以优化，正解是 bfs 我们可知回文有偶数串和奇数串，他们不是以一个字母就是以零个字母从中间向外对称扩张，所以我们先把从自己到自己的路线入队，再把每个直接连接两个点的路径入队，从中间往外 bfs 枚举两边的是否有相同的字母路径，直到把能连的点连在一起。

复杂度 $O(n^4)$ 。

## CODE:
```cpp
#include<bits/stdc++.h>
using namespace std;
char d[110][110];
int a[110][110],n;
queue<pair<int,int>> q;

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n;
	memset(a,0x3f,sizeof a);
	for(int i=1;i<=n;i++) q.push({i,i}),a[i][i]=0;//处理偶数回文 
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cin>>d[i][j];
			if(i==j || d[i][j]=='-') continue;
			a[i][j]=1;
			q.push({i,j});
		}
	}
	while(q.size()){
		auto[i,j]=q.front();
		q.pop();
		for(int k=1;k<=n;k++){
			for(int l=1;l<=n;l++){
				if(d[k][i]!='-' && d[j][l]!='-' && d[j][l]==d[k][i] && a[k][l]==0x3f3f3f3f){
					a[k][l]=a[i][j]+2;
					q.push({k,l});
				}
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(a[i][j]==0x3f3f3f3f) cout<<"-1 ";
			else cout<<a[i][j]<<" ";
		}
		cout<<'\n';
	}
} 
```

---

## 作者：Yiyi_52MIYEON1314 (赞：0)

# 题意
给你每两个点之间的边的情况，如原题，这里不再赘述。

求对于每一对点最短的回文路径长度。

# 思路
考虑暴力广搜。

- 初始化标记数组 $a$，如果这两个点没有边，标记为 $-1$。如果这两个点相等，也就是自己连自己，那么标记为 $0$。如果这两个点之间有边，那么标记为 $1$。
- 对于每一对有边的点，那么我们暴力枚举，如果边权相同，那么往两边扩展即可。

# 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
char c[105][105];
queue<pair<int,int> > q;
int a[105][105],x,y,n; 
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cin>>c[i][j];
		}
	}
	memset(a,-1,sizeof(a));
	for(int i=1;i<=n;i++)q.push({i,i}),a[i][i]=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i!=j&&c[i][j]!='-'){
				q.push({i,j});
				a[i][j]=1;
			}
		}
	}
	while(!q.empty()){
		x=q.front().first;
		y=q.front().second;
		q.pop();
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(a[i][j]==-1&&c[i][x]==c[y][j]&&c[i][x]!='-'){
					a[i][j]=a[x][y]+2;
					q.push({i,j});
				}
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cout<<a[i][j]<<' ';
		}
		cout<<endl;
	}
 	return 0;
}
```
### 谢谢！

---

## 作者：Lovely_Sun (赞：0)

对于小写英文字母 $c$ 和回文字母 $S$ ，按此顺序连接 $c$ 、 $S$ 和 $c$ 得到的字符串构成回文字符串。反之，长度至少为 2 的字符串是一个回文字符串，当且仅当第一个字符和最后一个字符相同时，去掉第一个字符和最后一个字符后得到的字符串仍然是一个回文字符串。

利用这些性质，可以将问题形式化为（有向）图上的最短路径问题。

假设 $G$ 是一个有 $N^2$ 个顶点 $\lbrace (1,1), (1,2), \ldots, (1, N), (2, 1), \ldots, (N, N) \rbrace$ 的图。我们将确定边，使顶点 $(i, j)$ 对应于问题陈述中给出的图中从顶点 $i$ 到顶点 $j$ 的路径。

为方便起见，在 $G$ 上再添加一个顶点 $S$ ，使其有 $N^2 + 1$ 。那么对于整数对 $(i, j)$ ，原问题的答案就是图中从 $S$ 到 $(i, j)$ 的最短路径的长度：

- 从 $S$ 到 $(i, i)$ 的边，权重为 $0$ ，每条边的权重为 $i$ 。
- 为每个 $(i, j)$ 添加一条从 $S$ 到 $(i, j)$ 的边，权重为 $1$ ，包含 $C_{i, j} \neq$ `-`。
- 从 $(i, j)$ 到 $(k, l)$ 的边，权重为 $2$ ，每个 $(i, j, k, l)$ 都有 $C_{k, i} \neq$ 。`-`, $C_{j, l} \neq$ `-`, $C_{k, i} = C_{j, l}$ .

第一种边代表长度为 $0$ 的宫词，第二种边代表长度为 $1$ 的宫词。第三种边对应于在一个宫词的首尾添加相同的字符，从而得到一个长度增加 2 的新宫词。

$G$ 有 $O(N^2)$ 个顶点，每个顶点的阶数为 $O(N^2)$ ，因此它有 $O(N^4)$ 条边，允许 $O(N^4)$ 次 BFS（广度优先搜索）找到答案。

请注意，虽然这些边是加权的，但我们仍然可以先处理权重为 $0$ 和 $1$ 的边，从而找到最短的距离。

代码
```cpp
#include <bits/stdc++.h>
#define rep(i, n) for (int i = 0; i < (n); i++)
using namespace std;

int inf = 1000000010;

int main() {
	int n;
	cin >> n;
	vector<vector<char>> c(n, vector<char>(n));
	rep(i, n) rep(j, n) cin >> c[i][j];
	vector<vector<int>> a(n, vector<int>(n, inf));
	queue<pair<int, int>> que;
	rep(i, n) {
		que.push({i, i});
		a[i][i] = 0;
	}
	rep(i, n) rep(j, n) {
		if (i == j or c[i][j] == '-') continue;
		que.push({i, j});
		a[i][j] = 1;
	}
	while (!que.empty()) {
		auto q = que.front(); que.pop();
		int i = q.first, j = q.second;
		rep(k, n) rep(l, n) {
			if (c[k][i] != '-' && c[j][l] != '-' && c[k][i] == c[j][l] && a[k][l] == inf) {
				a[k][l] = a[i][j] + 2;
				que.push({k, l});
			}
		}
	}
	rep(i, n) {
		rep(j, n) {
			cout << (a[i][j] == inf ? -1 : a[i][j]) << " \n"[j == n - 1];
		}
	}
}

```

---

## 作者：yhl110804 (赞：0)

题目看起来很像弗洛伊德，只是求的是最短回文路径，很明显将一个回文串前后各拼上一个相同的字符它仍是回文串，所以提前预处理长度为一和二的回文串后跑 bfs 就行。时间复杂度是 $O(n^4)$。

后来又加了两组数据把 $O(n^4)$ 卡掉了，可以通过将长度为二的回文串看为将一个空串前后各拼上相同字符，直接跑 bfs 来减小时间复杂度。当然，也可以通过记录边权，做到只枚举有效边的方式来减小时间复杂度。

## Code：
```cpp
#include<bits/stdc++.h>
//#define int long long
using namespace std;
inline int read()
{
   int x=0,f=1;char ch=getchar();
   while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
   while (ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-48;ch=getchar();}
   return x*f;
}
void write(int x)
{
   if(x<0)putchar('-'),x=-x;
   if(x<10)putchar(x+'0');
   else write(x/10),putchar(x%10+'0');
}
const int N=200;
const int mod=1e9+7;
char c[N][N];
int n;
struct node{
	int str,ed;
};
queue<node>q;
int dis[N][N]; 
signed main(){
	memset(dis,0x3f,sizeof dis);
	n=read();
	for(int i=1;i<=n;i++)q.push((node){i,i}); 
	for(int i=1;i<=n;++i){
		dis[i][i]=0;
	//	q.push((node){i,i}); 
		for(int j=1;j<=n;j++){
			cin>>c[i][j];
			if(c[i][j]!='-')q.push((node){i,j}),dis[i][j]=min(dis[i][j],1);
		}
	}
	while(!q.empty()){
		node now=q.front();
		q.pop();
		int l=now.str;
		int r=now.ed; 
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(c[i][l]!='-'&&c[r][j]!='-'&&c[i][l]==c[r][j]&&dis[i][j]==dis[0][0]){
					dis[i][j]=2+dis[l][r];
					q.push((node){i,j});
				}
			}
		}
	} 
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(dis[i][j]==dis[0][0])cout<<-1<<" ";
			else cout<<dis[i][j]<<" ";
		}
		cout<<"\n";
	}
    return 0;
}

```

---

## 作者：chenzhiyou2009 (赞：0)

没有题解诶，那我来写一个。

首先发现回文串可以看作：一个或者零个元素不断向两边扩展相同的元素。

发现 $n \leq 100$，并且题目要求最小值，所以我们可以先找一个边，然后不断向两端扩展就可以了。这样做是类似广度优先搜索的，所以时间复杂度大约是 $n^4$，实际会快一些，并且 AtCoder 有神机，所以能过。

先定义 $ans_{i,j}$ 表示答案，初始化为正无穷。

再枚举所有端点 $u,v$，如果他们之间有连边就加入到起始边中。注意如果 $u=v$，那么我们需要将其加入起始边中，因为我们的回文串可以从零个边开始扩展。

之后直接写 BFS 过程就行了，对于当前点对 $(i,j)$ 枚举 $u,v$，试图用 $u \to i \to \ldots \to j \to v$ 更新 $ans_{u,v}$ 即可。注意更新过的不能再更新一遍。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define vi vector<int>
#define pii pair<int, int>
#define fi first
#define se second
#define Ret return
#define Inl inline
#define For(i, j, k) for (int i = j; i <= k; ++ i)
#define Rof(i, j, k) for (int i = j; i >= k; -- i)

const int N = 110, inf = 0x3f3f3f3f;

int n;
int ans[N][N];
string s[N];
queue<pii > q;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    cin >> n;
    For (i, 1, n) {
        cin >> s[i];
        s[i] = '.' + s[i];
    }

    For (i, 1, n) {
        For (j, 1, n) {
            ans[i][j] = inf;
        }
    }
    For (i, 1, n) {
        //可以从0个边开始扩展
        q.push({i, i});
        //空串也算是回文串
        ans[i][i] = 0;
    }
    For (i, 1, n) {
        For (j, 1, n) {
            if (i == j) {
                continue;
            }
            if (s[i][j] == '-'){
                continue;
            }
            //初始所有要扩展的边
            q.push({i, j});
            ans[i][j] = 1;
        }
    }
    while (q.size()) {
        pii now = q.front();
        q.pop();
        For (u, 1, n) {
            For (v, 1, n) {
                //没有更新过
                if (ans[u][v] != inf) {
                    continue;
                }
                //u -> i ---> j -> v
                //能形成回文
                if (s[u][now.fi] == s[now.se][v] && s[u][now.fi] != '-') {
                    ans[u][v] = ans[now.fi][now.se] + 2;
                    q.push({u, v});
                }
            }
        }
    }

    For (i, 1, n) {
        For (j, 1, n) {
            cout << (ans[i][j] == inf ? -1 : ans[i][j]) << ' ';
        }
        cout << '\n';
    }

    return 0;
}

```

[AC 记录](https://www.luogu.com.cn/record/204759444)

建议评黄到绿吧，个人感觉是下位绿。

---

## 作者：Inv_day_in_R (赞：0)

这道题其实 $O(n^4)$ 暴力 BFS 就能 AC，考场上认为 $100^4=10^9$，太人机了，一直在想 $O(n^2)$ 做法最后惨遭 WA。

当时一眼秒出以起点和终点的组合作为一个状态，每次为保证回文，找到所有能到达旧起点的点和就终点能到达的点作为新起点和新中点，并且满足这两条边都是同一个字符。实际实现时，设队头起点终点为 $s$ 和 $t$，如果没出现过，那么两重循环枚举所有 $s'$ 和 $t'$ 满足 $C(s',s)=C(t,t')$ 且不为 `-`，加入队列。而初始化时有 $A(s,s)=0$。否则若 $C(s,t)$ 不为 `-`，有 $A(s,t)=1$。其他默认初始化为 $-1$。

然后就完事了。当然得记住先把 $0$ 放进队列，然后再放 $1$，不然就不能保证先搜到的一定最短了。

代码：

```cpp
void solve(){
	int n;
	cin>>n;
	vector<string>c(n);
	vector<vector<int>>ans(n,vector<int>(n));
	cin>>c;
	queue<array<int,2>>q;
	vector<array<int,2>>tmp;
	for(int i=0;i<n;i++)for(int j=0;j<n;j++){
		if(i==j)ans[i][j]=0,q.push({i,j});
		else if(c[i][j]!='-')ans[i][j]=1,tmp.push_back({i,j});
		else ans[i][j]=-1;
	}
	for(auto[s,t]:tmp)q.push({s,t});
	while(q.size()){
		auto[s,t]=q.front();
		q.pop();
		if(ans[s][t]==-1)continue;
		for(int S=0;S<n;S++)for(int T=0;T<n;T++)if(c[S][s]==c[t][T]&&c[S][s]!='-'&&ans[S][T]==-1){
			ans[S][T]=ans[s][t]+2;
			q.push({S,T});
		}
	}
	for(int i=0;i<n;i++)for(int j=0;j<n;j++)cout<<ans[i][j]<<" \n"[j==n-1];
}
```

---

## 作者：I_will_AKIOI (赞：0)

考虑回文串的暴力算法：枚举回文中心，向两边扩展。因此也考虑类似的做法。

回文中心包含两个部分，一个是点本身，一个是一条边连接的两个点。记 $dis_{i,j}$ 表示 $i$ 到 $j$ 这条路径的答案。那么初始化 $dis_{i,i}=0,dis_{i,j}=1$。

求最短路那么肯定广搜。考虑当前状态为 $(x,y)$。那么如果想要扩展这条回文串，就需要找的找两个点 $nx,ny$，使得存在 $nx\rightarrow x$ 和 $y\rightarrow ny$ 的边。并且两条边的边权相等，就可以把 $(nx,ny)$ 加入队列，同时更新 $dis_{nx,ny}\leftarrow dis_{x,y}+2$。

某个人一开始写的深搜，调了 $15$ 分钟还吃两发罚时，快来嘲讽她吧。

```cpp
#include<bits/stdc++.h>
#define N 105
#pragma GCC optimize("O3")
using namespace std;
int n,res[N][N];
char c1[N][N],c2[N][N];//正图和反图
queue<pair<int,int> >q;
void dfs(int x,int y)//错误示范
{
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(c2[x][i]=='-'||c1[y][j]=='-'||c2[x][i]!=c1[y][j]||res[x][y]+2>=res[i][j]) continue;
			res[i][j]=res[x][y]+2;
			dfs(i,j);
		}
	}
	return;
}
int main()
{
	ios::sync_with_stdio(0);
	cin>>n;
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) cin>>c1[i][j];
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) c2[i][j]=c1[j][i];
	memset(res,63,sizeof(res));
	for(int i=1;i<=n;i++) res[i][i]=min(res[i][i],0),q.push({i,i});
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) if(c1[i][j]!='-') res[i][j]=min(res[i][j],1),q.push({i,j});
	while(!q.empty())
	{
		int x=q.front().first,y=q.front().second;
		q.pop();
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
			{
				if(c2[x][i]=='-'||c1[y][j]=='-'||c2[x][i]!=c1[y][j]||res[x][y]+2>=res[i][j]) continue;
				res[i][j]=res[x][y]+2;
				q.push({i,j});
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++) cout<<((res[i][j]==0x3f3f3f3f)?-1:res[i][j])<<" ";
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：__Accepted_ZYF__ (赞：0)

唉唐了没做出来。

考虑使用回文最短路。

先将 $(i,j)$ 相邻或 $(i,i)$ 相等加入队列。

然后通过让 $i$ 跑反边到前驱，$j$ 跑正边到后继，可以得出一条满足回文的最短路。

具体维护如下：

1. 加入 $(i,i)$ 与有边的 $(i,j)$，这些状态一定是回文的。
2. BFS，每一次枚举 $i$ 的前驱，$j$ 的后继，要是字符一致，就是合法的回文串扩展。
3. 更新答案数组 $dep$，注意每一次扩展状态其实本质是走 $2$ 步。


```cpp
#include<bits/stdc++.h>
using namespace std;
namespace ivan422{
	#define ll long long
	#define ld long double 
	#define il __int128
	#define fl __float128
	#define x0 x_0
	#define x1 x_1
	#define y0 y_0
	#define y1 y_1
	#define yn y_n
	#define j0 j_0
	#define j1 j_1
	#define k0 k_0
	#define k1 k_1
	#define d0 d_0
	#define d1 d_1
	#define pb push_back
	#define pf push_front
	#define mp make_pair
	#define ar array<int,3>
	#define us unsigned
	#define io ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
};
using namespace ivan422;
const int N=125+10,M=125+10;
const int P1=1e9+7,P9=998244353;
const double pi=3.1415926535,eps=1e-7;
int n,dep[M][M];
char c[M][M];
queue<array<int,2> >q;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)cin>>c[i][j];
	memset(dep,0x7f,sizeof(dep));
	for(int i=1;i<=n;i++){
		dep[i][i]=0;
		q.push({i,i});
	}
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)if(i!=j){
		if(c[i][j]!='-'){
			dep[i][j]=1;
			q.push({i,j});
		}
	}		
	while(q.size()){
		array<int,2>f=q.front();
		q.pop();
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(c[i][f[0]]=='-'||c[f[1]][j]=='-')continue;
				if(c[i][f[0]]!=c[f[1]][j])continue;
				if(dep[i][j]==dep[0][0]){
					dep[i][j]=dep[f[0]][f[1]]+2;
					q.push({i,j});
				}
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)cout<<(dep[i][j]==dep[0][0]?-1:dep[i][j])<<" ";
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：Kexi_ (赞：0)

这个题思想有些像弗洛伊德。

将正常弗洛伊德中的点操作改成了路径操作，枚举中转路径。由于所有路径长度为一，基于广搜实现即可。

一些细节看代码注释。

```cpp
#include <bits/stdc++.h>
#define N 105
#define ri int
#define F first
#define S second
#define inf 0x3f3f3f3f
using namespace std;
char a[N][N];
int n,ans[N][N];
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	std::queue<pair<int,int>> q; 
	cin>>n;
	for(ri i(1);i<=n;i++)
	{
		for(ri j(1);j<=n;j++)
		{
			ans[i][j]=inf;
			cin>>a[i][j]; 
		}
		ans[i][i]=0; q.push({i,i});
	}
	
	for(ri i(1);i<=n;i++)
	{
		for(ri j(1);j<=n;j++)
		{
			if(i!=j&&a[i][j]!='-')
			{
				ans[i][j]=1; q.push({i,j}); //任何一条非空的边可以构成一个长度为1的回文
			}
		}
	}
	
	while(!q.empty())
	{
		auto now=q.front(); q.pop();
		for(ri k(1);k<=n;k++)
		{
			for(ri l(1);l<=n;l++)
			{
				if(a[k][now.F]==a[now.S][l]&&a[k][now.F]!='-'&&ans[k][l]==inf)// 由于是单向边，需要注意下顺序
				{
					ans[k][l]=ans[now.F][now.S]+2;//如果两边字符一样，就可以构成新的回文
					q.push({k,l}); 
				}
			}
		}
	}
	
	for(ri i(1);i<=n;i++)
	{
		for(ri j(1);j<=n;j++)
		{
			cout<<(ans[i][j]==inf?-1:ans[i][j])<<' ';
		}
		cout<<'\n';
	}
	
	return 0;
}
```

---

## 作者：201012280925LSY (赞：0)

## 题意
给出一个有向图，图的关系由一个邻接矩阵来表示。每一条边有一个小写字母。若有两个点之间没有边就用 `-` 表示。现在要求出每两个点能不能通过给出的有向边到达，同时要求这条路径上的字母要组成一个回文串，如果无法到达或者无法组成一个回文串，输出 `-1`，否则输出路径的最短长度。
## 思路
首先我们发现直接搜索的复杂度过高，不能满足需求。

观察回文串，以回文串的中间为中心，左右两边的字符显然都是一样的。这启发我们从回文中心开始搜索。而一个回文串有两种类型：

- 长度为偶数：这说明回文中心是一个点。
- 长度为奇数：这说明回文中心是一条边。

那么我们从一条边或一个点开始向这条路径两边进行，只要拓展的两条边的字母相等，那么这条路径就一定是一个回文串。

注意到题目还有一个要求：路径长度要最短。这说明我们应当使用宽度优先搜索进行求解~作者在赛时用的是深搜最后遗憾离场~。

思路接下来就很明显了：每一个状态有三个指标，分别是路径长度，起点，终点。初始状态是每一个点和每一条边。每次更新状态是枚举指向起点和从终点指向别的点的边。注意指向自己的也要枚举。

具体见代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const long long INF=1e18;
long long n,answer[110][110];
char a[110][110];
struct edge
{
	long long x;
	long long y;
	long long step;
};
deque<edge>dq;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			cin>>a[i][j];
			answer[i][j]=INF;
		}
	}
	edge lrm;
	for(int i=1;i<=n;i++)//初始状态
	{
		lrm.x=lrm.y=i;
		lrm.step=0;
		dq.push_back(lrm);
		answer[i][i]=0;
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(i!=j&&a[i][j]!='-')//初始状态
			{
				lrm.step=1;
				lrm.x=i;
				lrm.y=j;
				dq.push_back(lrm);
				answer[i][j]=1;			
			}
		}
	}
	while(!dq.empty())
	{
		long long X=dq.front().x,sum=dq.front().step,Y=dq.front().y;
		dq.pop_front();
		edge tys;
		for(int i=1;i<=n;i++)//更新状态
		{
			for(int j=1;j<=n;j++)
			{
				if(a[i][X]!='-'&&a[Y][j]!='-'&&a[i][X]==a[Y][j]&&answer[i][j]==INF)
				{
					tys.x=i;
					tys.y=j;
					tys.step=sum+2;
					answer[i][j]=tys.step;
					dq.push_back(tys);
				}
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(answer[i][j]==INF)cout<<-1<<" ";
			else cout<<answer[i][j]<<" "; 
		}
		cout<<"\n";
	}
	return 0;
}

```

---

## 作者：yr409892525 (赞：0)

## 题解：AT_abc394_e [ABC394E] Palindromic Shortest Path
我们可以直接跑 dijkstra，时间是 $O(n^2 \log n)$ 的。              
每次从当前状态向两边延伸，延伸的字符相同。              
再对回文串长度分成奇数和偶数。               
奇数就从每一个位置出发，偶数就从相邻两个节点出发。            

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=105,inf=1e9;
int n;
char a[N][N];
int dis[N][N];
struct code{
    int s,e,x;
    bool operator<(const code &v)const{
        return x>v.x;
    }
};
priority_queue<code> q;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>a[i][j];
            if(a[i][j]=='-') dis[i][j]=inf;
            else dis[i][j]=1,q.push({i,j,1});
        }
        q.push({i,i,0});
        dis[i][i]=0;
    }
    while(q.size()){
        code u=q.top();
        q.pop();
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(a[i][u.s]=='-' || a[u.e][j]=='-' || a[i][u.s]!=a[u.e][j]) continue;
                int x=u.x+2;
                if(dis[i][j]>x){
                    dis[i][j]=x;
                    q.push({i,j,x});
                }
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cout<<(dis[i][j]==inf?-1:dis[i][j])<<" ";
        }
        cout<<"\n";
    }
	return 0;
}
```

---

## 作者：Tairitempest (赞：0)

## [ABC394E] Palindromic Shortest Path

直接从两端中的任意位置开始都不好做。

考虑从中间字符开始。对于一个从点 $u$ 到点 $v$ 的长度为 $l$ 的回文路径，只要存在一个到点 $u$ 有一条边的点 $i$，和点 $v$ 可到达的点 $j$，且边 $(i,u)$ 和边 $(v,j)$ 的字母相同，那么点 $u$ 到点 $v$ 存在长度为 $l+2$ 的回文路径。

既然这样，那么我们可以用广度优先搜索：记录 $(i,i)$ 为从点 $i$ 到点 $j$ 的路径的状态，先把所有的可能的长度为 $0$ 的回文路径入队（即形为 $(i,i)$ 的状态），再把所有的可能的长度为 $1$ 的回文路径入队（即形为 $(i,j)$，并且 $i$ 与 $j$ 不相等（避免反复入队），且点 $i$ 到点 $j$ 有一条边的状态），然后按照上面的模式，用类似 SPFA 的思想，仅在更新了更小的值的时候入队。（由于广度优先搜索的特性，可以保证每个状态只会入队一次）

该算法的正确性可以证明。由于每个状态只会入队一次，每个状态的更新为 $O(N^2)$，总共有 $N^2$ 个状态，因此复杂度为 $O(N^4)$，可以通过本题。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n;
char s[110][110];
ll ans[110][110];

queue< pair<ll,ll> > q;

int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			ans[i][j]=1e18;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			cin>>s[i][j];
	for(int i=1;i<=n;i++){
		ans[i][i]=0;
		q.push({i,i});
	}	
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i==j||s[i][j]=='-') continue;
			q.push({i,j});
			ans[i][j]=1;
		}
	}
	while(!q.empty()){
		ll beg=q.front().first;
		ll end=q.front().second;
		q.pop();
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(s[i][beg]=='-'||s[end][j]=='-') continue;
				if(s[i][beg]!=s[end][j]) continue;
				if(vis[i][j]) continue;
				if(ans[beg][end]+2<ans[i][j]){
					ans[i][j]=ans[beg][end]+2;
					q.push({i,j});
				}
				
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)
			cout<<(1e18-ans[i][j]>0?ans[i][j]:-1)<<" ";
		cout<<endl;
	}		
	return 0;
}
```

---

