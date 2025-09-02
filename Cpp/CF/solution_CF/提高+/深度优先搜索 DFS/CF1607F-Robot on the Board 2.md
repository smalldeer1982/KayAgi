# Robot on the Board 2

## 题目描述

The robot is located on a checkered rectangular board of size $ n \times m $ ( $ n $ rows, $ m $ columns). The rows in the board are numbered from $ 1 $ to $ n $ from top to bottom, and the columns — from $ 1 $ to $ m $ from left to right.

The robot is able to move from the current cell to one of the four cells adjacent by side.

Each cell has one of the symbols 'L', 'R', 'D' or 'U' written on it, indicating the direction in which the robot will move when it gets in that cell — left, right, down or up, respectively.

The robot can start its movement in any cell. He then moves to the adjacent square in the direction indicated on the current square in one move.

- If the robot moves beyond the edge of the board, it falls and breaks.
- If the robot appears in the cell it already visited before, it breaks (it stops and doesn't move anymore).

Robot can choose any cell as the starting cell. Its goal is to make the maximum number of steps before it breaks or stops.

Determine from which square the robot should start its movement in order to execute as many commands as possible. A command is considered successfully completed if the robot has moved from the square on which that command was written (it does not matter whether to another square or beyond the edge of the board).

## 样例 #1

### 输入

```
7

1 1
R

1 3
RRL

2 2
DL
RU

2 2
UD
RU

3 2
DL
UL
RU

4 4
RRRD
RUUD
URUD
ULLR

4 4
DDLU
RDDU
UUUU
RDLD```

### 输出

```
1 1 1
1 1 3
1 1 4
2 1 3
3 1 5
4 3 12
1 1 4```

# 题解

## 作者：jielosc (赞：6)

## CF1607F Robot on the Board 2 题解

 [题目传送门](https://www.luogu.com.cn/problem/solution/CF1607F)。

### 一、题目简述

给你一个**有向图**，每个点的权值为 $1$，

然后从一个点出发，每个点**只能经过一次**，

求从何处出发所经过点的权值和**最大**，并求出**最大值**。

### 二、思路分析

那这题岂不是很简单，直接枚举每一个点，然后从这个点开始搜索，最后求出最大值。

但看一下 $n$ 和 $m$ 的范围，这种写法显然是不行的。

所以这里我们要用到**记忆化搜索**，对，就是搜完一个点后用数组把他记录下来。

```cpp
int w[N], to[N];
char status[N] = {1};

inline int dfs(int u)
{
    if(status[u]) return w[u]; //如果搜索过直接返回就行 
    
    status[u] = 1; // 标记一下 
    w[u] = 1 + dfs(to[u]); // 接着向下搜 
    
    return w[u];
}

```

但这个图可是有**环**的呀，所以这样写肯定不行。

那我们就要在搜索到环时把**整个环**处理一遍，下次再搜索到它就直接返回。

所以 dfs 应这样写：

```cpp

int w[N], to[N];
char status[N] = {2};
// status[i] 表示i的状态
// 0 表示未搜索，1 表示搜索中， 2 表示搜索过 

inline int dfs(int u)
{
    if(status[u] == 2) return w[u]; //如果搜索过直接返回就行 
    if(status[u] == 1) //如果搜索到 搜索中的点 那说明遇到环了 
    {
        sum = 1; //sum 用来记录环的大小 
        for(int i = to[u]; i != u; i = to[i]) ++sum;
        for(int i = to[u]; i != u; i = to[i]) status[i] = 2, w[i] = sum;
        status[u] = 2; w[u] = sum;
        // 将整个环标记为 搜索过，并且 更新 w[] 
        return 0; // 这里返回多少都行， 因为用不到它 
    }
    status[u] = 1; // 到这儿还没return的话，说明这个点没搜过，标记一下 
    dfs(to[u]); // 接着向下搜 
    // 你以为搜完后就可以更新了？？ 
    // 我们还需要看一下 当先点的状态是否被标记成 2 
    // 如果标记为 2 的话 ，w[u] 已经在处理环的时候 更新过了 
    if(status[u] != 2) w[u] = 1 + w[to[u]]; 
    return status[u] = 2, w[u]; // 标记为搜索过，然后返回 
}
```

这样写就没什么问题了，但还有一些**细节**问题要处理一下。

因为这道题是**多组数据**，所以每次都要初始化。

但聪明的你发现总的点数不超过 $4\times10^6$,

所以数据可以这样处理：

定义两个变量，$start$ 和 $end$，表示的是这组数据中点标号的范围，

当求下一组数据时，直接更新 $start$，这样所有点的标号是连续的，不会重复。

代码如下：

```cpp

void work()
{
    scanf("%d%d", &n, &m);  
    start = end + 1; // 更新 start
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j)
        {
            ++end; // 新的点 
            to[end] = read(); // 输入 to[] 
        }
    ans = 0;
    for(int i = start; i <= end; ++i)
        if(ans < dfs(i))  ansp = i,ans = w[i];
        
    ansp -= start;
    // 输出时 再把点的标号转换成行列形式 
    printf("%d %d %d\n", (ansp) / m + 1, ansp % m + 1, ans);
}
```

### 三、完整代码

```cpp
#include <cstdio>
const int N = 4000003;

int T, n, m, start, end, sum;
int w[N], to[N];
char status[N] = {2};

inline int dfs(int u)
{
    if(status[u] == 2) return w[u];
    if(status[u] == 1)
    {
        sum = 1;
        for(int i = to[u]; i != u; i = to[i]) ++sum;
        for(int i = to[u]; i != u; i = to[i]) status[i] = 2, w[i] = sum;
        status[u] = 2; w[u] = sum;
        return 0;
    }
    status[u] = 1;
    dfs(to[u]);
    if(status[u] != 2) w[u] = 1 + w[to[u]];
    return status[u] = 2, w[u];
}
void work()
{
    scanf("%d%d", &n, &m);
    start = end + 1;
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j)
        {
            ++end;
            char c = getchar();
            while(c == '\n' || c == ' ') c = getchar();
            if(c == 'L' && j != 1) to[end] = end - 1;
            else if(c == 'R' && j != m) to[end] = end + 1;
            else if(c == 'U' && i != 1) to[end] = end - m;
            else if(c == 'D' && i != n) to[end] = end + m;
        }
    int ans = 0, ansp = 0;
    for(int i = start; i <= end; ++i)
        if(ans < dfs(i))  ansp = i,ans = w[i];
    ansp -= start;
    printf("%d %d %d\n", (ansp) / m + 1, ansp % m + 1, ans);
}
int main(void)
{
    scanf("%d", &T);
    while(T--) work();
}
```





---

## 作者：maruize (赞：6)

## CF1607F

考虑图论转换

考虑转化出来的图的性质:

每个点,只有一条出边,及边点数相等,这是什么?

内向基环树森林!

---

然后就好办了,只需求基环树上最长叶子到环的路径

拓扑排序顺便 dp 一下即可

怎么 dp 呢?

树上根往下的最长链加上环长

注意要对于出界多维护一个节点(代码中的1号节点)并连个自环

注意要输出方案

```cpp
#include<bits/stdc++.h>
typedef long long LL;
typedef long double LD;
typedef unsigned uint;
using namespace std;
#define pii pair<int,int>
#define fs first
#define sc second
#define pb push_back
//==header==
const int N=2.2e3,mod=998244353;
char t[N];
#define pack(x,y) ((x)*(m+1)+(y))//将坐标转换成点
#define tox(w) ( (w)/(m+1) )
#define toy(w) ( (w)%(m+1) )//将点解包成坐标
int to[N*N],in[N*N],f[N*N],from[N*N];
int dy(char c){
	if(c=='L')return -1;
	if(c=='R')return 1;
	return 0;
}
int dx(char c){
	if(c=='U')return -1;
	if(c=='D')return 1;
	return 0;
}
int cir,vis[N*N],cnt[N*N];
void dfs(int x,int num){
	vis[x]=num;cnt[num]++;//vis[i]:i所在环的编号,cnt[i]: i号环的环长
	if(!vis[to[x]])dfs(to[x],num);
}
void work(){
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%s",t+1);
		for(int j=1;j<=m;j++){
			int x=i+dx(t[j]),y=j+dy(t[j]);
			if(x>n||x<=0||y>m||y<=0)to[pack(i,j)]=1,in[1]++;
			else to[pack(i,j)]=pack(x,y),in[pack(x,y)]++;
		}
	}
	to[1]=1,in[1]++;
	
	queue<int>q;//拓扑,f: dp值
	int tot=(n+1)*(m+2);//注意tot不要小了
	for(int i=1;i<=tot;i++)from[i]=i;
	for(int i=1;i<=tot;i++)if(!in[i])q.push(i);
	while(!q.empty()){
		int k=q.front();q.pop();
		if(!to[k])continue;
		if(f[k]+1>f[to[k]])f[to[k]]=f[k]+1,from[to[k]]=from[k];
		if(!--in[to[k]])q.push(to[k]);
	}
	cir=0;
	for(int i=1;i<=tot;i++)if(in[i]==1&&!vis[i])dfs(i,++cir);//处理环
	int ans=0,st=0;
	cnt[1]=0;
	for(int i=1;i<=tot;i++)if(in[i]==1&&f[i]+cnt[vis[i]]>ans)
		ans=f[i]+cnt[vis[i]],st=from[i];//统计答案
	printf("%d %d %d\n",tox(st),toy(st),ans);
	
	for(int i=1;i<=tot;i++)vis[i]=cnt[i]=to[i]=in[i]=f[i]=from[i]=0;
	//clear
}
int main(){
	int t;
	scanf("%d",&t);
	while(t--)work();
	return 0;
}

```

---

## 作者：Otomachi_Una_ (赞：3)

## 题目简述

- 假设有一个 $n\times m$ 的方阵，每个方阵上有个指定方向。
- 问从哪个位置出发走到的不重复路线长度最大。
- 多组数据，$T\leq10^4$，$n,m\leq2000$。

## 解题思路

显然，一个格子走的长度依赖于它所指向方向的格子走的长度。

于是，我们可以考虑 dfs。这里分两种情况。

####  第一种，此格子本身包含在一个封闭环内

显然，这个环内所有格子走的最大长度都是这个环的长度。

举个栗子：

![](https://cdn.luogu.com.cn/upload/image_hosting/lmf5nsj7.png)

这个图就是一个环，长度为 $20$，所以每个格子最多走 $20$ 步。

#### 第二种，此格子本身不包含在封闭环内

那么他能走的长度是他所指向格子的长度加一。

## 代码实现

我们看 dfs 部分。

```cpp
void dfs(int x,int y,int t){
	//cout<<x<<" "<<y<<" "<<t<<endl;
	①if(x==0||x==n+1||y==0||y==m+1||cnt[x][y]){//珂跑出去了 
		for(int i=1;i<t;i++)
			cnt[p[i]][q[i]]=cnt[x][y]+(t-i);
		return;
	}
	②if(vis[x][y]){//成环了 MMP
		int res=0;
		for(int i=1;i<t;i++)
			if(x==p[i]&&y==q[i])
				res=i;
		for(int i=res;i<t;i++)
			cnt[p[i]][q[i]]=t-res;//环部分 
		for(int i=1;i<res;i++)
			cnt[p[i]][q[i]]=t-i;//颈部分 
		return;
	}
	vis[x][y]=true;
	p[t]=x,q[t]=y;//增加历史状态
	if(a[x][y]=='L') dfs(x,y-1,t+1);
	if(a[x][y]=='U') dfs(x-1,y,t+1);
	if(a[x][y]=='R') dfs(x,y+1,t+1);
	if(a[x][y]=='D') dfs(x+1,y,t+1);//迫害下一个鸽子 . 
	return;
}
```
这里，$p,q$ 是记录跟这个格子有关的点。

我们解释一下这段代码。

第 ① 部分的 if 判断的是是否跑出去了或者撞到已经搜索过的格子。举个栗子。

1. 跑出去了

![](https://cdn.luogu.com.cn/upload/image_hosting/rmczp540.png)

这个样子直接一个一个更新 $cnt$ 就好了。（边界的 $cnt$ 为 $0$）。

变成这个亚子

![](https://cdn.luogu.com.cn/upload/image_hosting/1b840deu.png)
2. 撞到搜索过的格子
![](https://cdn.luogu.com.cn/upload/image_hosting/tli0adb8.png)

同样的，一个一个更新 cnt，变成这样（下面那一坨已经搜索过了）。
![](https://cdn.luogu.com.cn/upload/image_hosting/7kzf8q9w.png)

第②部分是处理搜到一半遇到环了。

用 $res$ 记录环接口，剩下请读者自己看吧。（原谅我不想画图的本质）

## 提示

毒瘤的出题人卡掉了上面的 dfs，会 MLE。那么我们只需要使用一个 `while` 来更新 $x,y$ 即可。

[完整代码戳这里](https://www.luogu.com.cn/paste/zxd9bxng)

---

## 作者：HDWR (赞：2)

### 从搜索说起

首先我们看到这个题目可以很自然地想到如何暴力：对于每一个格子从当前点出发进行搜索。

但是这个过程有很多步搜索是不必要的：从一个格子出发，最后停下来的位置是一定的，那么如果这个格子被搜过一遍了，我们还继续搜它干什么呢？直接用我们已经知道的信息不就好了吗？

于是我们考虑采用记忆化的思想：记录一个 `dist[i][j]` 表示从位置 `(i, j)` 出发能执行的最大指令数。

接下来从一个未搜过的起始点开始搜索，直到我们碰见一个之前走过的格子。这个结束有三种情况：

- 跳出地图边界
- 走到**这次搜索**走过的格子，也就是成环
- 走到**以前搜索**走过的格子

我们分别讨论一下：

### 跳出地图边界

[![IEHFnH.png](https://z3.ax1x.com/2021/11/03/IEHFnH.png)](https://imgtu.com/i/IEHFnH)

~~图是拿 Excel 画的~~

这种情况很简单，我们照着路径顺序逆着更新 `dist` 即可。

[![IEHu38.png](https://z3.ax1x.com/2021/11/03/IEHu38.png)](https://imgtu.com/i/IEHu38)

### 走出环

[![IEHU3T.png](https://z3.ax1x.com/2021/11/03/IEHU3T.png)](https://imgtu.com/i/IEHU3T)

这种情况下，从环上的所有点出发，都能绕环走一圈，所以**环上的点**答案就是环长；环外的点就照着路径顺序逆着更新 `dist`。

[![IEbNdA.png](https://z3.ax1x.com/2021/11/03/IEbNdA.png)](https://imgtu.com/i/IEbNdA)

### 走到以前走过的位置

[![IEq71f.png](https://z3.ax1x.com/2021/11/03/IEq71f.png)](https://imgtu.com/i/IEq71f)

可以发现，答案可以直接从我们之前走过的点继承过来的，照着路径顺序逆着更新 `dist` 即可。

[![IELCcT.png](https://z3.ax1x.com/2021/11/03/IELCcT.png)](https://imgtu.com/i/IELCcT)

### 代码实现

```cpp
const int MAXN = 2000 + 10;

const std::string drr = "RLDU";
const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};

int n, m;
char mat[MAXN][MAXN];

int dist[MAXN][MAXN];
bool vis[MAXN][MAXN];

void SearchGetPath(std::vector<std::pair<int, int> > &path, int &x, int &y) {
    while (!(x < 1 || y < 1 || x > n || y > m || vis[x][y])) {
        // DEBUG(x); DEBUG(y);
        vis[x][y] = true;
        path.push_back({x, y});
        int dr = (int) (drr.find(mat[x][y]));
        x += dx[dr]; y += dy[dr];
    }
}

void _main() {
    cin >> n >> m;
    rep (i, 1, n) cin >> (mat[i] + 1);
    rep (x, 1, n) rep (y, 1, m) {
        dist[x][y] = -1;
        vis[x][y] = 0;
    }
    rep (x, 1, n) rep (y, 1, m) if (dist[x][y] == -1) {
        int nx = x, ny = y; std::vector<std::pair<int, int> > path;
        SearchGetPath(path, nx, ny);
        if (nx < 1 || ny < 1 || nx > n || ny > m) {
            // 跳出地图边界
            path.push_back({nx, ny});
            dist[nx][ny] = 0;
            for (int i = (int) path.size() - 2; i >= 0; --i) {
                dist[path[i].fi][path[i].se] = dist[path[i + 1].fi][path[i + 1].se] + 1;
            }
        } else {
            // 找环长
            int circlesize = (int) (path.end() - std::find(ALL(path), std::make_pair(nx, ny)));
            if (circlesize == 0) {
                // 这不是环，是之前走过的路径
                path.push_back({nx, ny});
                for (int i = (int) path.size() - 2; i >= 0; --i) {
                    dist[path[i].fi][path[i].se] = dist[path[i + 1].fi][path[i + 1].se] + 1;
                }
                continue;
            }
            int i = path.size() - 1;
            int step = 1; // 一个小 trick，在环上的时候答案是 circlesize，在环外的时候答案就是 step
            for (i = path.size() - 1; i >= 0; --i) {
                dist[path[i].fi][path[i].se] = std::max(step, circlesize);
                ++step;
            }
        }
    }
    int ax = 0, ay = 0;
    rep (i, 1, n) rep (j, 1, m) {
        if (dist[i][j] > dist[ax][ay]) {
            ax = i; ay = j;
        }
    }
    cout << ax << ' ' << ay << ' ' << dist[ax][ay] << endl;
}

int main() {
    std::ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int T; cin >> T;
    while (T --> 0) {
        _main();
    }
    return 0;
}
```

---

## 作者：JackMerryYoung (赞：1)

# 前言

搜索题单的一道好题。

# 正文

考虑暴力搜索。

枚举起始点，去暴力搜索，复杂度最多为 $\mathcal{O}(\sum_{i = 1}^{T}{(N_i M_i)^2})$, 直接去世。

那么考虑记忆化搜索. 设 $f_{i,j}$ 表示从 $(i, j)$ 出发最多可以到达的点数。

根据终止原因，分三种情况考虑。

## 1. 因为出界终止

可以知道 $f_{i,j}$ 从可以抵达它的地方转移而来。

那这就很简单，搜索时记录深度，终止后一路回溯即可。

## 2. 因为撞到自己的路径终止

就是形成了环。

环上的点因为互相撞击，答案都相同；出环的路径上的点离环越远答案越大。

可以 `vector` 维护路径，这样方便处理答案。

## 3. 因为撞到已经有答案的点终止

考虑接龙，答案从接上的那个有答案的点转移。

那么答案为接上的那个点的答案加上一；想求一路上的答案，那就回溯。

---

至此，分类讨论结束了。

算法复杂度为 $\mathcal{O}(\sum_{i = 1}^{T}{N_i M_i})$, 不超过 $4 \times 10^6$. 可以通过本题。

# 代码

``` cpp
#include <bits/stdc++.h>
#define Node pair<int, int>
#define fir first
#define sec second
#define mkpr make_pair
using namespace std;

int T, N, M;
int f[2005][2005];
bool vis[2005][2005];
char MAP[2005][2005];

int dx[5] = {0, 1, 0, -1, 0};
int dy[5] = {0, 0, 1, 0, -1};

int __gd(char c)
{
    switch(c)
    {
        case 'D': return 1;
        case 'R': return 2;
        case 'U': return 3;
        case 'L': return 4;
    }

    return 0;
}

void search(vector<Node> &path, int &nx, int &ny)
{
    while(nx >= 1 && nx <= N && ny >= 1 && ny <= M && !vis[nx][ny])
    {
        vis[nx][ny] = true;
        path.push_back(mkpr(nx, ny));
        int dir = __gd(MAP[nx][ny]);
        nx += dx[dir];
        ny += dy[dir];
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> T;
    while(T --)
    {
        cin >> N >> M;
        for(int i = 1; i <= N; ++ i)
            for(int j = 1; j <= M; ++ j)
                cin >> MAP[i][j], vis[i][j] = false, f[i][j] = -1;
        
        for(int i = 1; i <= N; ++ i)
        {
            for(int j = 1; j <= M; ++ j)
            {
                if(f[i][j] == -1)
                {
                    int rx = i, ry = j;
                    vector<Node> path;
                    search(path, rx, ry);
                    if(rx < 1 || rx > N || ry < 1 || ry > M)
                    {
                        path.push_back(mkpr(rx, ry));
                        f[rx][ry] = 0;
                        for(int k = path.size() - 2; k >= 0; -- k)
                            f[path[k].fir][path[k].sec] = f[path[k + 1].fir][path[k + 1].sec] + 1;
                    }
                    else
                    {
                        int cs = (int) (path.end() - find(path.begin(), path.end(), mkpr(rx, ry)));
                        if(cs == 0)
                        {
                            path.push_back(mkpr(rx, ry));
                            for(int k = path.size() - 2; k >= 0; -- k)
                                f[path[k].fir][path[k].sec] = f[path[k + 1].fir][path[k + 1].sec] + 1;
                        }
                        else
                        {
                            int step = 1; 
                            for(int k = path.size() - 1; k >= 0; -- k) 
                            {
                                f[path[k].fir][path[k].sec] = max(step, cs);
                                ++ step;
                            }
                        }
                    }
                }
            }
        }

        int fx = 0, fy = 0;
        for(int i = 1; i <= N; ++ i)
            for(int j = 1; j <= M; ++ j)
                if(f[i][j] > f[fx][fy])
                    fx = i, fy = j;

        cout << fx << ' ' << fy << ' ' << f[fx][fy] << endl;        
    }

    return 0;
}
```

# 后言

本题其实不难，这种题目都是先去爆搜，再考虑优化的。

---

## 作者：ifffer_2137 (赞：0)

### 题意
有一个机器人在 $n\times m$ 的棋盘上移动，每个格子中写着 L、U、R、D 其中一个字母，依次代表机器人到这个格子后会向左、下、右、上方向走。机器人不能重复经过一个格子，也不能走出棋盘，问机器人在哪个格子开始走可以走到的格子最多，以及最多能走到多少个格子。
### 分析
你发现从一个点开始走路径固定，要么走到边界撞死，要么走到环里卡死。对于第一种，直接把所有边界上会撞死的格子找出来，走反向边 bfs 找一下，一边标记一边找个最长路即可。

现在我们去除掉第一种情况里被标记的点，剩下的点出度都为 $1$，显然是个内向基环森林。那你要找里面的最长路，直接先把环以外的部分拓扑了，维护个`len[]`表示以某个点为终点的最长路径，再把环找出来，遍历一遍统计环上点数，顺便取个`len[]`最大就好了。时间复杂度 $O(nm)$。

由于要输出起点所以细节比较多，具体见代码。
### 代码

```cpp
//From: ifffer_2137
#include <bits/stdc++.h>
using namespace std;
#define inf 0x7fffffff
#define eb emplace_back
#define pii pair<int,int>
#define mkpr make_pair
#define fir first
#define sec second
inline int read(){
    char ch=getchar();int x=0,w=1;
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+ch-48,ch=getchar();return w==1?x:-x;
}
const int maxn=2e3+5;
const int maxm=4e6+5;
int F(char c){if(c=='L') return 0;if(c=='U') return 1;if(c=='D') return 2;return 3;}
pii D[]={{0,-1},{-1,0},{1,0},{0,1}};
int T;
int n,m,St,ans;
int X(int x,int y){return (x-1)*m+y;}
char a[maxn][maxn];
int ind[maxm],vis[maxm],len[maxm],to[maxm],vot[maxm];
queue<pii> q;queue<int> tp;
vector<int> iG[maxm];
void clear(){
	St=ans=0;
	for(int i=1;i<=n*m;i++){
		ind[i]=vis[i]=len[i]=to[i]=vot[i]=0;
		iG[i].clear();
	}
	while(!q.empty()) q.pop();
	while(!tp.empty()) tp.pop();
}
int bfs(){
	int res=0;
	while(!q.empty()){
		pii f=q.front();q.pop();
		int u=f.fir,x=f.sec;
		vis[u]=1;
		if(x>res){
			res=x;
			St=u;
		}
		for(int v:iG[u]) q.push(mkpr(v,x+1));
	}
	return res;
}
signed main(){
	cin.tie(0),cout.tie(0);
	T=read();
	while(T--){
		n=read(),m=read();clear();
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				cin>>a[i][j];pii d=D[F(a[i][j])];
				int x=i+d.fir,y=j+d.sec;
				if(x>=1&&x<=n&&y>=1&&y<=m) ind[X(x,y)]++,to[X(i,j)]=X(x,y),iG[X(x,y)].eb(X(i,j));
				else q.push(mkpr(X(i,j),1));
			}
		}
		ans=bfs();
		for(int i=1;i<=n*m;i++){
			if(vis[i]) continue;
			if(ind[i]==0) tp.push(i),vot[i]=i;
		}
		while(!tp.empty()){
			int u=tp.front();tp.pop();
			int v=to[u];
			if(len[u]+1>len[v]){
				len[v]=len[u]+1;
				vot[v]=vot[u];
			}
			ind[v]--;
			if(!ind[v]) tp.push(v);
		}
		for(int i=1;i<=n*m;i++){
			if(vis[i]) continue;
			if(ind[i]){
				int u=i,res=0,cnt=0,st=i;
				while(to[u]!=i){
					if(len[u]>res){
						res=len[u];
						st=vot[u];
					}
					ind[to[u]]--;
					u=to[u];cnt++;
				}
				if(len[u]>res){
					res=len[u];
					st=vot[u];
				}
				ind[to[u]]--;cnt++;
				if(res+cnt>ans){
					ans=res+cnt;
					St=st;
				}
			}
		}
		cout<<(St-1)/m+1<<" "<<(St-1)%m+1<<" "<<ans<<"\n";
	}
	return 0;
}
```

---

