# [ABC301E] Pac-Takahashi

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc301/tasks/abc301_e

$ H $ 行 $ W $ 列のグリッドがあります。 上から $ i $ 行目、左から $ j $ 列目のマス目を $ (i,j) $ と表します。 グリッドの各マスはスタートマス、ゴールマス、空マス、壁マス、お菓子マスのいずれかです。 $ (i,j) $ が何のマスであるかは文字 $ A_{i,j} $ によって表され、$ A_{i,j}= $ `S` のときスタートマス、 $ A_{i,j}= $ `G` のときゴールマス、 $ A_{i,j}= $ `.` のとき空マス、 $ A_{i,j}= $ `#` のとき壁マス、 $ A_{i,j}= $ `o` のときお菓子マスです。 ここで、スタートマスとゴールマスはちょうど $ 1 $ つずつあり、お菓子マスは **$ 18 $ 個以下**であることが保証されます。

高橋くんは現在スタートマスにいます。 高橋くんは、上下左右に隣接するマスであって壁マスでないマスに移動することを繰り返し行えます。 高橋くんは今から $ T $ 回以下の移動によってゴールマスに到達したいです。 そのようなことは可能かどうか判定してください。 可能な場合は、最終的にゴールマスにいるという条件のもとで、移動の途中に訪れるお菓子マスの数の最大値を求めてください。 ただし、$ 1 $ つのお菓子マスに複数回訪れた場合でも、カウントするのは $ 1 $ 回のみです。

## 说明/提示

### 制約

- $ 1\leq\ H,W\ \leq\ 300 $
- $ 1\ \leq\ T\ \leq\ 2\times\ 10^6 $
- $ H,W,T $ は整数
- $ A_{i,j} $ は `S`, `G`, `.`, `#`, `o` のいずれか
- $ A_{i,j}= $ `S` を満たす $ (i,j) $ の組がちょうど $ 1 $ つ存在する
- $ A_{i,j}= $ `G` を満たす $ (i,j) $ の組がちょうど $ 1 $ つ存在する
- $ A_{i,j}= $ `o` を満たす $ (i,j) $ の組は **$ 18 $ 個以下**
 
### Sample Explanation 1

$ (1,1)\ \rightarrow\ (1,2)\ \rightarrow\ (1,3)\ \rightarrow\ (2,3)\ \rightarrow\ (1,3) $ と $ 4 $ 回移動すると、 $ 1 $ 個のお菓子マスを訪れた上で最終的にゴールマスにいることができます。 $ 5 $ 回以下の移動で $ 2 $ 個のお菓子マスを訪れた上で最終的にゴールマスにいることはできないので、$ 1 $ が答えです。 なお、$ (1,1)\ \rightarrow\ (2,1)\ \rightarrow\ (1,1)\ \rightarrow\ (1,2)\ \rightarrow\ (1,3)\ \rightarrow\ (2,3) $ と移動すると $ 5 $ 回の移動で $ 2 $ 個のお菓子マスを訪れることができますが、最終的にゴールマスにいないため無効であることに注意してください。

### Sample Explanation 2

$ 1 $ 回以下の移動でゴールマスに到達することはできません。

## 样例 #1

### 输入

```
3 3 5
S.G
o#o
.#.```

### 输出

```
1```

## 样例 #2

### 输入

```
3 3 1
S.G
.#o
o#.```

### 输出

```
-1```

## 样例 #3

### 输入

```
5 10 2000000
S.o..ooo..
..o..o.o..
..o..ooo..
..o..o.o..
..o..ooo.G```

### 输出

```
18```

# 题解

## 作者：DengDuck (赞：9)

注意到关键点（糖果和起点终点）的数量很少，总共最多 $20$ 个，这不比表格好弄？

于是我们先用 BFS 暴力算出它们之间的距离。

这个时间复杂度其实不大，一次宽搜时间复杂度也才 $O(nm)$，运算次数吃饱也就 $20^2\times 300^2$，在超脑少年团以外的地方都能过。

把距离弄出来之后建成了一个图。

算出来后我们发现这个问题类似于旅行商问题，写一个状压 DP 解决即可。

设 $f_{i,j}$ 表示目前在第 $i$ 个点，每个点是否访问过的状态为 $j$。

则，我们已知 $f_{i,j}$ 的情况下，可以用其更新：

$$
f_{k,j|(2^{k-1})}=\min(f_{k,j|(2^{k-1})},f_{i,j}+dis_{i,k})
$$

这里的 $|$ 是或运算。

但是我们的状压其实求的是最短时间，我们要找的是在符合条件的时间中最多的糖果，这个东西储存在状态里了。

```cpp
#include<bits/stdc++.h>
#define LL long long
#define XX first
#define YY second
using namespace std;
const LL dx[4]={0,0,1,-1};
const LL dy[4]={1,-1,0,0};
struct node
{
	LL x,y,num;
};
LL n,m,t,dis[25][25],a[305][305],vis[305][305],sx,sy,ex,ey,cnt,f[25][3000005],mx;
char c[305][305];
queue<node>q;
pair<LL,LL> pt[25];
LL work(LL i,LL j)//求距离
{
	LL sx=pt[i].XX,sy=pt[i].YY,ex=pt[j].XX,ey=pt[j].YY;
	while(!q.empty())q.pop();
	q.push({sx,sy,0});
	memset(vis,0,sizeof(vis));
	while(!q.empty())
	{
		LL tx=q.front().x,ty=q.front().y,num=q.front().num;
		q.pop();
		for(int i=0;i<4;i++)
		{
			LL xx=tx+dx[i],yy=ty+dy[i];
			if(xx<1||n<xx||yy<1||m<yy||a[xx][yy]==1||vis[xx][yy]==1)continue;
			vis[xx][yy]=1;
			q.push({xx,yy,num+1});
			if(xx==ex&&yy==ey)return num+1;
		}
	}
	return INT_MAX;
}
int main()
{
	cin>>n>>m>>t;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cin>>c[i][j];
			if(c[i][j]=='S')sx=i,sy=j;
			if(c[i][j]=='G')ex=i,ey=j;
			if(c[i][j]=='o')
			{
				pt[++cnt]={i,j};
			}
			if(c[i][j]=='#')a[i][j]=1; 
		}
	}
	pt[++cnt]={sx,sy},pt[++cnt]={ex,ey};
	for(int i=1;i<=cnt;i++)
	{
		for(int j=i+1;j<=cnt;j++)
		{
			dis[i][j]=dis[j][i]=work(i,j);
		}
	}	 	
	if(dis[cnt-1][cnt]>t)//不可能到
	{
		puts("-1");
		return 0;
	}
	memset(f,127,sizeof(f));
	f[cnt-1][1<<(cnt-2)]=0;//初始化只有起点
	for(int i=(1<<(cnt-2));i<=(1<<cnt)-1;i++)//状压 DP
	{
		if(((i>>(cnt-2))&1)==0)continue;
		for(int j=1;j<=cnt;j++)
		{
			if(((i>>(j-1))&1)==0)continue;
			for(int k=1;k<=cnt;k++)
			{
				f[k][i|(1<<(k-1))]=min(f[k][i|(1<<(k-1))],f[j][i]+dis[j][k]);
			}
		}
	}
	for(int i=(1<<(cnt-2));i<=(1<<cnt)-1;i++)//找一个最优解
	{
		if(((i>>(cnt-1))&1)==0)continue;
		if(((i>>(cnt-2))&1)==0)continue;
		if(f[cnt][i]>t)continue;
		LL sum=0;
		for(int k=1;k<=cnt-2;k++)
		{
			if((i>>(k-1))&1)sum++;
		}
		mx=max(mx,sum);
	}
 
	cout<<mx<<endl;
}
```

---

## 作者：Kylin_ZHH (赞：5)

# ABC301E题解

这个题赛时没做出来，我太蒟了

我们先设 $N$ 为糖果方块的数量。

让 $S$ 是一组在游览期间看到的糖果方块 对于所有可能的 $S$（有 $2^n$ 个这样的集合)，我们尝试找到访问 $S$ 中所有糖果方块所需的最小移动次数，最终进入目标方块。

这可以被认为是一种旅行推销员问题，其中糖果方块被视为顶点。因此，如果我们知道，对于所有糖果方块对，从一个移动到另一个所需的最小移动次数，那么这个问题可以用位 DP，时间复杂度就是 $O(NHW+2^nn^2)$。

~~提示~~：用位 DP 去做旅行推销员问题，很像 ABC180E，各位可以去看一下。

来看代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define LF long double
#define PII array<int,2>
#define PI3 array<int,3>
const int N=(1<<18), M=N*4, mod=998244353, INF = mod;
 
char s[305][305];
int n, m, T;
bool valid(int x,int y) {
	if(x<1 || x>n) return 0;
	if(y<1 || y>m) return 0;
	return s[x][y] != '#';
}
 
int d[305][305];
int bfs(int sx,int sy,int tx,int ty) {
	memset(d, 0, sizeof d);
	d[sx][sy] = 1;
	static PII f[4] = {{1,0},{0,1},{-1,0},{0,-1}}; 
	queue<PII> q;
	q.push({sx,sy});
	
	while(!q.empty()) {
		auto u = q.front(); q.pop();
		for(const auto& p:f) {
			int nx = u[0] + p[0], ny = u[1] + p[1];
			if(!valid(nx,ny) || d[nx][ny]) continue;
			d[nx][ny] = d[u[0]][u[1]] + 1;
			if(nx==tx && ny==ty) return d[tx][ty] - 1; 
			q.push({nx, ny});
		}
	}
	return 1e7;
}
 
int dis[25][25];
int dp[20][N];
bitset<N> vis[20];
int so, to;
int dfs(int now,int ztm) {
	if(ztm==0) return dis[so][now];
	if(vis[now][ztm]) return dp[now][ztm];
	vis[now][ztm] = 1;	dp[now][ztm] = INF;
	
	for(int i=0; i<to; i++) if(ztm>>i&1) 
		dp[now][ztm] = min(dp[now][ztm], dis[i][now] + dfs(i, ztm^(1<<i)));
	return dp[now][ztm];
}
 
signed main() {	 	
	scanf("%d %d %d",&n,&m,&T);
	
	vector<PII> p;	
	for(int i=1; i<=n; i++) {
		cin >> s[i]+1;
		for(int j=1; j<=m; j++) {
			if(s[i][j]=='S') {
				so = p.size();
				p.push_back({i, j});
			} else if(s[i][j]=='G') {
				to = p.size();
				p.push_back({i, j});
			} else if(s[i][j]=='o') {
				p.push_back({i, j});
			} 
		}
	}
	
	swap(p[so], p[p.size()-1]); so = p.size()-1;
	swap(p[to], p[p.size()-2]); to = p.size()-2;
	for(int i=0; i<p.size(); i++) {
		for(int j=i+1; j<p.size(); j++)
			dis[i][j] = dis[j][i] = bfs(p[i][0], p[i][1], p[j][0], p[j][1]);
	}
	if(dis[so][to]>T) printf("-1"), exit(0);
	if(p.size()<=2) printf("0"), exit(0);
	
	int ans = 0;
	for(int i=(1<<to)-1; i>=0; i--) {
		if(__builtin_popcount(i) <= ans) continue;
		if(dfs(to, i) <= T) ans = __builtin_popcount(i);
	}
	printf("%d",ans);
	
	return 0;
}
```
撒花

---

## 作者：sunzz3183 (赞：5)

# [ABC301E] Pac-Takahashi 题解

## 题意

给定一个 $n,m$ 的字符串矩阵，和一个 $t$ 。矩阵有 `S`、`G`、`.`、`#`、`o`，五种符号，`S` 表示起点，`G` 表示终点，`.` 表示地面，`#` 表示墙壁（不能走），`o` 表示糖果。

现在你需要走**不超过** $t$ 步，从起点走到终点，问最多能获得多少糖果？

$1\leq n,m\leq 300,1\leq t\leq 2\times 10^6$

设 $W$ 为糖果的个数：

$0\leq W\leq 18$

## 分析

看到数据范围，$0\leq W\leq 18$ 第一时间想到状压。

在读入的时候把每个糖果进行编号并记录为 $1\sim cnt$，为了方便我们把起点和终点也编上号，分别为 $1,cnt+1$。

设 $F_{I,j}$ 为当前状态为集合 $I$（哪几个糖果选过），当前在第 $j$ 个点的最短路。

显然状态转移方程为：

$$ F_{S,l}=\max(F_{S,l},F_{S_0,j}+dis(j,l))$$

其中集合 $S_0$ 是一个包含点 $j$ 不包含点 $l$ 的集合，集合 $S$ 是 集合 $S_0$ 加上点 $l$ 的集合，$dis(j,l)$ 表示第 $j$ 个糖果到第 $l$ 个糖果的最短路。

初始化为

$$ F_{\varnothing,0}=0 $$

$$ F_{A,i}=dis(0,i) $$

$A$ 为只包含点 $i$ 的集合，其他状态为 $\mathrm{INF}$。

答案为：

$$ ans=\min_{F_{S,j}+dis(j,cnt+1)\leq t}(|S|)$$

其中 $|S|$ 表示集合 $S$ 元素个数。

然后使用 `BFS` 处理最短路，把集合压为二维就可以了。

注意一个点：在转移的时候，要考虑阶段为当前选了的点的个数，不能直接枚举 $i$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
    char ch=getchar();int x=0;bool f=1;
    while(ch<'0'||'9'<ch){if(ch=='-')f=0;ch=getchar();}
    while('0'<=ch&&ch<='9'){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
    return f?x:-x;
}
const int N=302,inf=0x3f3f3f3f/2;
int n,m,t,cnt;
int sx,sy,ex,ey;
int e[22][22];
int f[1<<18][19];
char c[N][N];
int pos[N][N];
struct nude{
    int x,y;
}a[N];
bool vis[N][N];
int nxt[4][2]={{-1,0},{0,-1},{1,0},{0,1}};
struct qwq{
    int x,y,w;
};
queue<qwq>q;
vector<int>vt[22];
void bfs(int id){
    e[id][id]=0;
    memset(vis,0,sizeof(vis));
    vis[a[id].x][a[id].y]=1;
    q.push({a[id].x,a[id].y,0});
    while(!q.empty()){
        int x=q.front().x,y=q.front().y,w=q.front().w;q.pop();
        for(int i=0;i<4;i++){
            int tx=x+nxt[i][0],ty=y+nxt[i][1];
            if(tx<1||tx>n||ty<1||ty>m)continue;
            if(c[tx][ty]=='#')continue;
            if(vis[tx][ty])continue;
            vis[tx][ty]=1;
            if(pos[tx][ty]>=0)e[id][pos[tx][ty]]=w+1;
            q.push({tx,ty,w+1});
        }
    }
    return;
}
inline int getsum(int x){
    int sum=0;
    while(x)
        sum++,x^=x&(-x);
    return sum;
}
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    memset(e,0x3f,sizeof(e));
    memset(pos,-1,sizeof(pos));
    n=read();m=read();t=read();
    for(int i=1;i<=n;i++){
        scanf("%s",c[i]+1);
        for(int j=1;j<=m;j++)
            if(c[i][j]=='S')sx=i,sy=j,pos[i][j]=0;
            else if(c[i][j]=='G')ex=i,ey=j;
            else if(c[i][j]=='o')a[++cnt]={i,j},pos[i][j]=cnt;
    }
    a[0]={sx,sy};a[cnt+1]={ex,ey};pos[ex][ey]=cnt+1;
    for(int i=0;i<=cnt;i++)
        bfs(i);
    memset(f,0x3f,sizeof(f));
    f[0][0]=0;
    for(int i=1;i<=cnt;i++)f[1<<(i-1)][i]=e[0][i];
    for(int i=1;i<1<<cnt;i++)
        vt[getsum(i)].push_back(i);
    for(int szz=1;szz<=cnt;szz++)\\没有变量名了，这个是阶段
    for(int cyl=0;cyl<vt[szz].size();cyl++){
        int i=vt[szz][cyl];\\当前状态
        for(int j=1;j<=cnt;j++)
            if((i>>(j-1)&1)&&f[i][j]<inf)
                for(int l=1;l<=cnt;l++)
                    if((!(i>>(l-1)&1))&&(e[j][l]<inf))
                        f[i|(1<<(l-1))][l]=min(f[i|(1<<(l-1))][l],f[i][j]+e[j][l]);
    }
    int ans=-1;
    for(int i=0;i<1<<cnt;i++){
        int sum=getsum(i);
        for(int j=0;j<=cnt;j++)
            if(f[i][j]+e[j][cnt+1]<=t)
                ans=max(ans,sum);
    }
    printf("%d\n",ans);
    return 0;
}
```



---

## 作者：igAC (赞：4)

# $\text{Describe}$

[ATlink](https://atcoder.jp/contests/abc301/tasks/abc301_e)

[洛谷 link](https://www.luogu.com.cn/problem/AT_abc301_e)

简要题意：

给定地图，给定起点终点，地图上有一些金币和障碍。

你要在 $k$ 步以内走到终点，请问最多能吃掉多少枚金币。

如果无解输出 ``-1``。

# $\text{Solution}$

我们发现金币的数量 $cnt$ 很小（$cnt \le 18$）。

于是我们考虑状压 dp。

设 $f_{i,s}$ 表示当前在第 $i$ 枚金币，且当前状态为 $s$ 所需要的最小步数。

第 $j$ 位为 $1$，则代表我们已经经过了第 $j$ 枚金币。

特别的，我们令起点为第 $0$ 枚金币，终点为最后一枚金币。

考虑如何转移。

我们设从第 $i$ 枚金币走到第 $j$ 枚金币的路程为 $d_{i,j}$。

那么：

$$
f_{j,s|(1<<j)}=\min\{f_{i,s}+d_{i,j}\}
$$

接下来考虑如何求 $d_{i,j}$。

其实也很简单，用 BFS 对于每个点跑一遍即可。

具体实现可参考代码。

# $\text{Code}$

```cpp
#include<bits/stdc++.h>
#define INF 1e9
#define N 305
#define M 20
#define S 1048576
using namespace std;
int read(){
	int x=0,f=1,ch=getchar();
	for(;!isdigit(ch);ch=getchar()) f=(ch=='-')?-1:1;
	for(;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
	return x*f;
}
int n,m,k,cnt,ans;
int sx,sy,tx,ty;
const int dx[]={1,0,-1,0};
const int dy[]={0,1,0,-1};
int dis[N][N],f[M][S],d[M][M];
bool vis[N][N];
pair<int,int>node[M];
char s[N][N];
bool check(int i,int j){return (1<=i && i<=n && 1<=j && j<=m && s[i][j]!='#' && !vis[i][j]);}
void BFS(int x,int y){
	for(int i=0;i<=n;++i) for(int j=0;j<=m;++j) dis[i][j]=INF,vis[i][j]=false;
	queue<pair<int,int>>q;
	q.push({x,y}),dis[x][y]=0;
	vis[x][y]=true;
	while(!q.empty()){
		pair<int,int>now=q.front();q.pop();
		int xx=now.first,yy=now.second;
		for(int i=0;i<4;++i){
			int nx=xx+dx[i];
			int ny=yy+dy[i];
			if(check(nx,ny)){
				dis[nx][ny]=dis[xx][yy]+1;
				vis[nx][ny]=true;
				q.push({nx,ny});
			}
		}
	}
}
int main(){
	n=read(),m=read(),k=read();
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			cin>>s[i][j];
			if(s[i][j]=='S') sx=i,sy=j;
			if(s[i][j]=='G') tx=i,ty=j;
			if(s[i][j]=='o') node[++cnt]={i,j};
		}
	}
	node[0]={sx,sy},node[++cnt]={tx,ty};
	for(int i=0;i<=cnt;++i){
		int x=node[i].first,y=node[i].second;
		BFS(x,y);
		for(int j=0;j<=cnt;++j){
			int nx=node[j].first;
			int ny=node[j].second;
			d[i][j]=dis[nx][ny];
		}
	}
	for(int i=0;i<=cnt;++i){
		for(int j=0;j<(1<<cnt+1);++j){
			f[i][j]=INF;
		}
	}
	f[0][1]=0;
	for(int s=0;s<(1<<cnt+1);++s){
		for(int i=0;i<=cnt;++i){
			if(f[i][s]<=k){
				for(int j=0;j<=cnt;++j){
					f[j][s|(1<<j)]=min(f[j][s|(1<<j)],f[i][s]+d[i][j]);
				}
			}
		}
	}
	for(int s=0;s<(1<<cnt+1);++s) if(f[cnt][s]<=k) ans=max(ans,__builtin_popcount(s));
	printf("%d\n",ans<2?-1:ans-2);
	return 0;
}
```

---

## 作者：Fire_flame (赞：1)

这道题一眼望上去看起来是最短路或者广搜，但是 $k\le 2\times 10^6$，让你没法下手。

不过发现有糖果的格子最多只有 $18$ 个，加上起点终点只有 $20$ 个点有用，那么什么样的题目数据范围是 $20$ 呢？

不难算出 $2^{20}$ 大概是一百万，于是就想到了状压 DP。

定义 $f[i][j]$ 表示当前点为 $i$，状态为 $j$ 时的最短距离。定义 $d[i][j]$ 表示点 $i$ 到 $j$ 的距离，如果不连通则 $d[i][j]=\infty$。

先用广搜算出所有有用的点（不妨设是 $t$ 个）两两之间的距离，然后枚举下一个走的点 $k$，可以得到： 
$$f[i][j]=\min(f[i][j],f[k][j-2^k]+d[i][k])$$

那么对于距离不超过要求的状态，求最大数量的 $1$ 即可，可以使用 `lowbit` 每次砍掉一位计算。

时间复杂度 $O(t^2\times 2^t)$。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e2 + 5, MR = 1e4 + 5, MN = 21, MM = 1 << 19;
int n, m, l, ans, sx, sy, ex, ey, num, mp[MAXN][MAXN], used[MAXN][MAXN], g[MN][MN], f[MN][MM];
char ch[MAXN][MAXN];
struct node{
	int x, y;
}d[MAXN];
struct step{
	int x, y, st;
};
int lowbit(int x){return x & -x;}
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
void bfs(int p, int q){
	queue<step>pq;
	pq.push({p, q, 0});
	memset(used, 0, sizeof(used));
	used[p][q] = 1;
	while(!pq.empty()){
		int hx = pq.front().x, hy = pq.front().y, hst = pq.front().st;
		pq.pop();
		for(int i = 0;i < 4;i ++){
			int tx = hx + dx[i], ty = hy + dy[i];
			if(used[tx][ty] || tx <= 0 || ty <= 0 || tx > n || ty > m || ch[tx][ty] == '#')continue;
			used[tx][ty] = 1;
			if(mp[tx][ty])g[mp[p][q]][mp[tx][ty]] = g[mp[tx][ty]][mp[p][q]] = hst + 1;
			pq.push({tx, ty, hst + 1});
		}
	}
}
int main(){
	scanf("%d%d%d", &n, &m, &l);
	for(int i = 1;i <= n;i ++){
		for(int j = 1;j <= m;j ++){
			cin >> ch[i][j];
			if(ch[i][j] == 'S')sx = i, sy = j, mp[i][j] = ++ num, d[num] = {i, j};
			if(ch[i][j] == 'G')ex = i, ey = j, mp[i][j] = ++ num, d[num] = {i, j};
			if(ch[i][j] == 'o')mp[i][j] = ++ num, d[num] = {i, j};
		}
	}
	int ppp = mp[sx][sy];
	swap(mp[sx][sy], mp[d[num - 1].x][d[num - 1].y]);
	swap(d[num - 1], d[ppp]);
	ppp = mp[ex][ey];
	swap(mp[ex][ey], mp[d[num].x][d[num].y]);
	swap(d[num], d[ppp]);
	for(int i = 1;i <= num;i ++){
		bfs(d[i].x, d[i].y);
		for(int j = 1;j <= num;j ++){
			if(!used[d[j].x][d[j].y])g[i][j] = g[j][i] = 1e9;
		}
	}
	if(g[num - 1][num] > l){
		puts("-1");
		return 0;
	}
	memset(f, 0x3f, sizeof(f));
	for(int i = 1;i <= num - 2;i ++)f[i][1 << i] = g[i][num - 1];
	for(int k = 0;k < (1 << num - 1) - 1;k ++){
		for(int i = 1;i <= num - 2;i ++){
			if((1 << i) & k){
				for(int j = 1;j <= num - 2;j ++){
					if(i == j || (1 << j) & k)continue;
					f[j][k | (1 << j)] = min(f[j][k | (1 << j)], f[i][k] + g[i][j]);
				}
			}
		}
	}
	for(int i = 1;i <= num - 2;i ++){
		for(int k = 0;k < (1 << num - 1) - 1;k ++){
			if(k & (1 << i)){
				if(f[i][k] + g[i][num] <= l){
					int res = 0, pp = k;
					while(pp){
						res ++;
						pp -= lowbit(pp);
					}
//					printf("%d %d %d\n", k, res, f[i][k] + g[i][num]);
					ans = max(ans, res);
				}
			}
		}
	}
	printf("%d", ans);
	return 0;
}
```


---

## 作者：Keroshi (赞：1)

## 解题思路

首先观察数据，糖果的数量最多只有 $18$ 个，题目需要求在规定步数内能经过糖果的最多数量，考虑状压 dp。

先在所有的糖果，以及起点与终点都广搜一遍，求出每两个糖果的距离和起点，终点与糖果的距离，记作 $d_{i, j}$。

然后建立状压 dp 数组 $f_{i,j}$。其中 $i$ 二进制表示当时经过的糖果，$j$ 为最后一个经过的糖果，方便转移，则 $f_{i,j}$ 为经过所需的路程。那么转移显然易见，

$f_{i,j}=\min_{f_{i - 2^j,k}+d_{k,j}}$。

设图长宽为 $n$, $m$，糖果厂为 $k$ 个。    
时间复杂度 $O(knm+2^kk^2)$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 3e2 + 5;
const int M = 22;
const int F = 1e6 + 5;
const int INF = 0x3f3f3f3f;
int n, m, t;
string s[N];
int sx, sy, tx, ty;
pair<int, int> a[M]; int cnt;
map<pair<int, int> , int> mp;
int d[N][N], vis[N][N];
queue<pair<int,int> > q;
int dx[M] = {0, 0, 1, -1,};
int dy[M] = {1, -1, 0, 0,};
int e[M][M];
int f[F][M];
void bfs(int u) {
	memset(d, 0, sizeof(d));
	memset(vis, 0, sizeof(vis));
	q.push(a[u]);
	while(!q.empty()) {
		auto h = q.front();
		q.pop();
		int x = h.first;
		int y = h.second;
		if(vis[x][y]) continue;
		vis[x][y] = 1;
		if(s[x][y] != '.' && s[x][y] != '#') {
			e[u][mp[{x, y}]] = d[x][y];
		}
		for(int i=0;i<=3;i++) {
			int d1 = x + dx[i];
			int d2 = y + dy[i];
			if(d1 < 1 || d1 > n || d2 < 1 || d2 > m) continue;
			if(s[d1][d2] == '#') continue;
			d[d1][d2] = d[x][y] + 1;
			q.push({d1, d2});
		}
	}
}
void solve() {
	cin >> n >> m >> t;
	for(int i=1;i<=n;i++) {
		cin >> s[i];
		s[i] = " " + s[i];
		for(int j=1;j<=m;j++) {
			if(s[i][j] == 'S') sx = i, sy = j;
			if(s[i][j] == 'G') tx = i, ty = j;
			if(s[i][j] == 'o') {
				a[++cnt] = {i, j};
				mp[a[cnt]] = cnt;
			}
		}
	}
	a[cnt + 1] = {sx, sy};
	mp[a[cnt + 1]] = cnt + 1;
	a[cnt + 2] = {tx, ty};
	mp[a[cnt + 2]] = cnt + 2;
	memset(e, 0x3f, sizeof(e));
	for(int i=1;i<=cnt + 2;i++) {
		bfs(i);
	}
	int ans = -1;
	if(e[cnt + 1][cnt + 2] <= t) ans = 0;
	memset(f, 0x3f, sizeof(f));
	for(int i=1;i<=cnt;i++) {
		f[1 << (i - 1)][i] = e[cnt + 1][i];
	}
	for(int i=1;i<(1 << cnt);i++) {
		for(int j=1;j<=cnt;j++) {
			if(!(i >> (j - 1) & 1)) continue;
			for(int k=1;k<=cnt;k++) {
				if(j == k) continue;
				if(!(i >> (k - 1) & 1)) continue;
				if(f[i - (1 << (j - 1))][k] == INF) continue;
				if(e[j][k] == INF) continue;
				f[i][j] = min(f[i][j], f[i - (1 << (j - 1))][k] + e[j][k]);
			}
			if(f[i][j] == INF) continue;
			if(e[j][cnt + 2] == INF) continue;
			int len = f[i][j] + e[j][cnt + 2];
			int tot = 0;
			for(int k=1;k<=cnt;k++) {
				if(i >> (k - 1) & 1) tot++;
			}
			if(len <= t) ans = max(ans , tot);
		}
	}
	cout << ans << endl;
}
int main() {
	ios :: sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	solve();
	return 0;
}
```



---

## 作者：CQ_Bob (赞：0)

## 分析

和[这题](https://www.luogu.com.cn/problem/P9709)好像啊。

现预处理出来任意两个猴子（包括起点终点）的最短路。然后就是一个这样的问题：求在完全图上从起点出发，到达终点的路径长度和不超过 $t$ 且经过中转点最多的数量。

啊，$n$ 只有 $20$。考虑剪枝暴力。如果走到点 $x$ 经过节点的状态为 $st$ 时，历史最小路径长度不大于当前路径长度，剪掉即可。然后在加上无解和无更优解的剪枝就行了。至于复杂度，我也不知道……

## 代码

[Link](https://atcoder.jp/contests/abc301/submissions/47574490).

---

## 作者：Genius_Star (赞：0)

### 题意：

给你一张地图，地图上用字符表示不同的地形，其中“S”表示起点，“G”表示终点，“.”表示可以通行的平地，“#”表示障碍物，“o”表示一只猴子。

你的任务是从起点出发，在给定的时间内到达终点，并在此基础上捉住尽可能多的猴子。

每次移动可以向上、下、左、右四个方向之一前进一个单位，需要消耗一个单位的时间。

你每次可以使用 10 个时间单位来移动，也可以使用最后一个时间单位来捉住猴子。

请你编写程序，计算在给定的时间内，最多可以捉住多少只猴子。

若无法在规定时间内到达终点，则输出 -1。

### 思路：

本题的难点在于求出在规定时间内从起点到终点，抓到的猴子最多。

可以发现，该问题可以转化为：求在规定时间内从起点到终点，经过的猴子最多，即经过的猴子数最大。

因为规定了时间，所以可以考虑使用动态规划来解决。设 $dp_{i,j,t}$ 表示从起点到 $(i,j)$ ，经过 $t$ 秒所能经过的猴子数的最大值。

初始状态为

$$
dp_{i,j,0}=
\begin{cases}
0, \quad A_{i,j}=\text{'.'}\\
-\infty, \quad \text{otherwise}
\end{cases}
$$

其中 $A_{i,j}$ 表示 $(i,j)$ 处的格子的状态，如果是空格，那么经过 $0$ 秒时，已经经过了 $0$ 只猴子，如果是墙则不可能到达，所以状态为 $-\infty$ 。

转移时，考虑到只能向相邻的非墙格子移动且每次只能走 $1$ 格，所以从 $(i,j)$ 处到达 $(i-1,j),(i+1,j),(i,j-1),(i,j+1)$ 只需 $1$ 秒，则对于 $(i,j)$ 处的状态 $dp_{i,j,t}$ ，可以从 $(i-1,j),(i+1,j),(i,j-1),(i,j+1)$ 四个方向中状态最大的转移而来

$$
dp_{i,j,t}=\max_{(i',j')\in \text{adjacent}(i,j)}\{dp_{i',j',t-1}+1[A_{i',j'}=\text{'o'}]\}
$$

其中 $\text{adjacent}(i,j)$ 表示 $(i,j)$ 的四个相邻方格子，$1[A_{i',j'}=\text{'o'}]$ 表示 $(i',j')$ 处为猴子的情况下可以经过一只猴子。

最终的答案就是 $\max_{0\leq t\leq T} \{dp_{i,j,t}\}$ 。

时间复杂度为 $O(Tn^2)$ ，其中 $n$ 为地图的大小，显然会超时，需要对动态规划进行优化。

### 优化：

由于每个状态只能由其上一时刻的状态转移而来，因此可以使用滚动数组来进行优化，用一个二维数组 $dp$ 来存储状态即可。

另外，对于每个状态，只需要考虑其周围 $8$ 个格子和自身即可，因此可以将状态转移过程中的 $\max$ 改为循环，这样可以进一步提高效率。
### 完整代码：
```cpp
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define pii pair<int,int>
#define mp make_pair
#define F first
#define S second
using namespace std;
const int INF=0x3f3f3f3f;
const int dx[]={0,0,1,-1};
const int dy[]={1,-1,0,0};
pii pos[25];
int n,m,k,T,dp[(1<<18)+5][25],dist[25][305][305];
char M[305][305];
bool ok(int x,int y)
{
	return x>=0&&x<n&&y>=0&&y<m&&M[x][y]!='#';
}
void bfs(int id)
{
	memset(dist[id],0x3f,sizeof(dist[id]));
	int sx=pos[id].F,sy=pos[id].S;
	queue<pii> q;
	q.push(mp(sx,sy));
	dist[id][sx][sy]=0;
	while(!q.empty())
	{
		int x=q.front().F,y=q.front().S;q.pop();
		int d=dist[id][x][y];
		for(int ii=0;ii<4;ii++)
		{
			int nx=x+dx[ii],ny=y+dy[ii];
			if (ok(nx,ny)&&dist[id][nx][ny]>d+1)
			{
				dist[id][nx][ny]=d+1;
				q.push(mp(nx,ny));
			}
		}
	}
}
int main()
{
	ios::sync_with_stdio(false),cin.tie(nullptr);
	cin>>n>>m>>T;
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
		{
			cin>>M[i][j];
			if (M[i][j]=='o')
				pos[k++]=mp(i,j);
		}
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
		{
			if (M[i][j]=='S')
				pos[k]=mp(i,j);
			else if (M[i][j]=='G')
				pos[k+1]=mp(i,j);
		}
	for(int i=0;i<=k+1;i++)
		bfs(i);
	memset(dp,0x3f,sizeof(dp));
	dp[0][k]=0;
	int ans=-1;
	for(int mask=0;mask<(1<<k);mask++)
		for(int i=0;i<=k+1;i++)if (dp[mask][i]<=T)
		{
			for(int j=0;j<k;j++)if (!(mask&(1<<j))&&dp[mask][i]+dist[i][pos[j].F][pos[j].S]<=T)
				dp[mask|(1<<j)][j]=min(dp[mask|(1<<j)][j],dp[mask][i]+dist[i][pos[j].F][pos[j].S]);
			if (dp[mask][i]+dist[i][pos[k+1].F][pos[k+1].S]<=T)
				ans=max(ans,__builtin_popcount(mask));
		}
	cout<<ans<<'\n';
	return 0;
}
```

祝愿大家 ABC 集体 AK 啦~

---

## 作者：yeshubo_qwq (赞：0)

## Solution

注意到一个关键性质：**猴子的数量不超过 $18$ 只。**

只需要将猴子的位置单独拿出来，先 bfs 预处理距离，然后状态压缩 DP 即可。

## Code

```cpp
#include <bits/stdc++.h>
#define ll long long
#define go(i,x,y) for(int i=x;i<=y;i++)
#define goc(i,x,y) for(char i=x;i<=y;i++)
#define og(i,x,y) for(int i=x;i>=y;i--)
using namespace std;
int n,m,t,cnt,vis[305][305],sx,sy,tx,ty,dp[20][305][305],ans,g[20],u[20],dpp[20][1<<18];
struct node{int x,y;} a[20];
char str[305][305];
int dx[4]={0,0,1,-1},
    dy[4]={-1,1,0,0};
queue <pair<int,int> > q;    
void bfs(int x,int y,int z){
    go(i,1,n) go(j,1,m) vis[i][j]=0;
    vis[x][y]=1;
    dp[z][x][y]=0;
    q.push(make_pair(x,y));
    while (!q.empty()){
        x=q.front().first,y=q.front().second,q.pop();
        go(i,0,3){
            int nx=x+dx[i],ny=y+dy[i];
            if (str[nx][ny]=='#'||nx<1||nx>n||ny<1||ny>m||vis[nx][ny]) continue;
            dp[z][nx][ny]=dp[z][x][y]+1,vis[nx][ny]=1;
            q.push(make_pair(nx,ny));
        }
    }
}
int qwq(int x){
    int res=0;
    while (x) res+=(x&1),x>>=1;
    return res;
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m>>t;
    go(i,1,n){
        cin>>str[i]+1;
        go(j,1,m){
            if (str[i][j]=='o') a[++cnt].x=i,a[cnt].y=j;
            else if (str[i][j]=='S') sx=i,sy=j;
            else if (str[i][j]=='G') tx=i,ty=j;
        }
    }
    memset(dp,0x3f,sizeof(dp));
    bfs(sx,sy,0);
    go(i,1,cnt) bfs(a[i].x,a[i].y,i);
    if (dp[0][tx][ty]>t) return cout<<-1,0;
    memset(dpp,0x3f,sizeof(dpp));
    int S=(1<<cnt)-1;
    go(i,1,S)
        if (qwq(i)==1)
                go(j,1,cnt)
                    if (S&(1<<(j-1)))
                        dpp[j][i]=dp[0][a[j].x][a[j].y];
    go(i,1,S){
        go(j,1,cnt){
            if (i&(1<<(j-1))){
                go(k,1,cnt){
                    if (!(i&(1<<(k-1)))){
                        dpp[k][i|(1<<(k-1))]=min(dpp[k][i|(1<<(k-1))],dpp[j][i]+dp[j][a[k].x][a[k].y]);
                    }
                }
            }
        }
    }
    go(i,0,S)
        go(j,1,cnt)
            if (i&(1<<(j-1)))
                if (dpp[j][i]+dp[j][tx][ty]<=t){
                    ans=max(ans,qwq(i));
                }
    return cout<<ans,0;
}
```


---

## 作者：WRuperD (赞：0)

注意到得分点数量很小。观察到算上起点和终点，一共有 $ 20$ 个点。

所以我们考虑先进行一次 bfs，预处理每一个有效得分点到其它得分点（包括起点和终点）的距离。

然后就变成了一个最多有 $20$ 个点的完全图，问你从起点出发，在经过的边权和 $w \le T$ 的情况下到达终点，最多能经过几个点。状压 DP 即可。

---

