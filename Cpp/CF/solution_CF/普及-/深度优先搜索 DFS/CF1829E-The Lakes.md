# The Lakes

## 题目描述

You are given an $ n \times m $ grid $ a $ of non-negative integers. The value $ a_{i,j} $ represents the depth of water at the $ i $ -th row and $ j $ -th column.

A lake is a set of cells such that:

- each cell in the set has $ a_{i,j} > 0 $ , and
- there exists a path between any pair of cells in the lake by going up, down, left, or right a number of times and without stepping on a cell with $ a_{i,j} = 0 $ .

The volume of a lake is the sum of depths of all the cells in the lake.

Find the largest volume of a lake in the grid.

## 样例 #1

### 输入

```
5
3 3
1 2 0
3 4 0
0 0 5
1 1
0
3 3
0 1 1
1 0 1
1 1 1
5 5
1 1 1 1 1
1 0 0 0 1
1 0 5 0 1
1 0 0 0 1
1 1 1 1 1
5 5
1 1 1 1 1
1 0 0 0 1
1 1 4 0 1
1 0 0 0 1
1 1 1 1 1```

### 输出

```
10
0
7
16
21```

# 题解

## 作者：zhlzt (赞：7)

### BFS 做法
其实就是个很简单的连通块问题，对于所有 $p_{i,j}\ne 0$ 且之前没有被访问过的点，都跑一遍 BFS，相当于找到一个连通块，最后输出最大值即可，复杂度为 $O(tnm)$。

### 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int x,y;
};
int p[1010][1010],vis[1010][1010];
int a[]={0,1,0,-1},b[]={1,0,-1,0};
int bfs(int x,int y,int n,int m){//返回这个连通块中所有点的值之和
	queue<node>q;node fa,sn;
	fa.x=x,fa.y=y;int ans=0;
	q.push(fa),vis[x][y]=1;
	while(!q.empty()){
		fa=q.front();q.pop();
		ans+=p[fa.x][fa.y];
		for(int i=0;i<4;i++){
			sn.x=fa.x+a[i],sn.y=fa.y+b[i];
			if(sn.x<1||sn.x>n||sn.y<1||sn.y>m) continue;
			if(p[sn.x][sn.y]==0||vis[sn.x][sn.y]==1) continue;
			q.push(sn);vis[sn.x][sn.y]=1;
		}
	}
	return ans;
}
int main(){
	int t;scanf("%d",&t);
	while(t--){
		int n,m;scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++) 
				scanf("%d",&p[i][j]),vis[i][j]=0;
		int ans=0;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				if(vis[i][j]==0&&p[i][j]>0) 
					ans=max(ans,bfs(i,j,n,m));
		printf("%d\n",ans);
	}
	return 0;
}

```

---

## 作者：cjh20090318 (赞：4)

大家好，我是 CQ-C2024 蒟蒻 CJH。

## 题意

**本题有多组数据。**

求连通块最大权值和。

## 分析

对于每一个 $a_{i,j}>0$  且未访问过的点进行 BFS，接着统计权值和取最大值即可。

## 注意事项

**本题有多组数据！！！**所以访问数组一定要清空！~~多测不清空，爆零两行泪。~~

## 代码

```cpp
//the code is from chenjh
#include<cstdio>
#include<algorithm>
#include<queue>
#include<utility>
#define mp std::make_pair
typedef std::pair<int,int> PII;
int n,m;
int a[1001][1001];//水深。
bool b[1001][1001];//访问数组。
const int dx[4]={0,0,1,-1},dy[4]={1,-1,0,0};//方向数组。
void solve(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)scanf("%d",&a[i][j]),b[i][j]=0;//记得清空访问数组！
	std::queue<PII> Q;
	int ans=0;
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++){
		int w=0;
		if(!a[i][j]||b[i][j]) continue;//保证当前位置非 0 且未访问。
		Q.push(mp(i,j));
		for(int x,y;!Q.empty();){
			x=Q.front().first,y=Q.front().second;Q.pop();
			if(b[x][y]) continue;//访问过则退出。
			b[x][y]=1;//标记访问数组。
			w+=a[x][y];//统计权值。
			for(int k=0,nx,ny;k<4;k++){
				nx=x+dx[k],ny=y+dy[k];
				if(nx>0&&nx<=n&&ny>0&&ny<=m&&a[nx][ny]) Q.push(mp(nx,ny));//符合范围则继续广搜。
			}
		}
		ans=std::max(ans,w);//更新答案。
	}
	printf("%d\n",ans);
}
int main(){
	int T;scanf("%d",&T);
	while(T--) solve();
	return 0;
}

```

---

## 作者：szhqwq (赞：2)

## 分析

考虑 dfs。

本题实质上就是求连通块最大值。

那么每次搜索时把走过的标记，如果当前的 $a_{x,y}$ 为 $0$ 就不走，越界和走过的 $(x,y)$ 也不走，每次找没有走过的搜索，取最大值就可以了。

## AC Code of [CF1928E](https://codeforces.com/contest/1829/problem/E)

[Link](https://codeforces.com/contest/1829/submission/204811904)

---

## 作者：sto_5k_orz (赞：2)

update：修改了复杂度。

就是 bfs 板子。

可以枚举初始节点，不断搜索，更新最大值。

但是这里介绍一种并查集做法。

首先，每个节点需要有一个编号，我们令 $id(x,y)=xm+y$。

于是我们把所有相邻的非 $0$ 节点 $u$ 给一个 $v$，表示 $u$ 及其所有儿子的权值和。

每次枚举相邻两个均不为 $0$ 的格子进行合并。

然后枚举所有点，节点最大的 $v$ 就是答案。

复杂度为 $O(nm\log mn)$，完全可行，注意并查集需要路径压缩。

部分代码参考：

```cpp
int id(int x, int y) {return x * m + y;}
void merge(int x, int y) {
	int a = find(x), b = find(y); if(a == b) return ;
	rt[b] = a; v[a] += v[b];
}
```

---

## 作者：Jorisy (赞：1)

dfs 搜连通块，权值在搜的时候加上即可，每次搜完一个连通块都算一下目前最大的总权值。

赛时 AC Code：
```cpp
#include<bits/stdc++.h>
using namespace std;

const int X[]={1,0,-1,0};
const int Y[]={0,1,0,-1};
int n,m,a[1005][1005],f[1005][1005],s,maxs;

void dfs(int x,int y)
{
	s+=a[x][y];//累加
	for(int i=0;i<4;i++)
	{
		int x_=x+X[i],y_=y+Y[i];
		if(x_<1||y_<1||x_>n||y_>m||!a[x_][y_]||f[x_][y_]) continue;
		f[x_][y_]=1;//标记
		dfs(x_,y_);
	}
}

void sol()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			scanf("%d",&a[i][j]);
			f[i][j]=0;
		}
	}
	maxs=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(f[i][j]||!a[i][j]) continue;
			s=0;//清零
			f[i][j]=1;//标记
			dfs(i,j);
			maxs=max(maxs,s);//计算当前最大的总权值
		}
	}
	cout<<maxs<<endl;
}

int main()
{
	int t;
	cin>>t;
	while(t--) sol(); 
 	return 0;
}
```

---

## 作者：沉石鱼惊旋 (赞：1)

[更好的阅读体验](http://blog.cyx2009.top/archives/169/)

# E.[The Lakes](https://codeforces.com/contest/1829/problem/E)

## 题目翻译

> 你有一个 $n\times m$ 的矩阵，其中有水坑，水坑的大小为 $a_{i,j}$。若 $a_{i,j}=0$ 则不是水坑。问最大的连续水坑大小是多少。
> 
> $1\leq n,m\leq 1000,0\leq a_{i,j}\leq 1000$。
> 
> $t$ 组数据，$1\leq t \leq 1000,\sum_{tt=1}^t n\times m\leq 10^6$。

## 题目思路

典型的四方向连通块，使用搜索，深搜广搜均可。

记录每个水坑是否走过避免回头路。

注意开始遍历的时候要判断当前位置是否为 $0$。

```
1
2 2
0 1
1 0
```

如果不判断的话会从 $(1,1)$ 开始找到 $(1,2)$ 和 $(2,1)$，但其实这两个点不连通。

## 完整代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
bool vis[1020][1020];
int a[1020][1020];
int dx[]={0,0,-1,1};
int dy[]={-1,1,0,0};
bool judge(int x,int y)
{
    return x>=1&&y>=1&&x<=n&&y<=m&&!vis[x][y]&&a[x][y]>0;
}
int dfs(int x,int y)
{
    vis[x][y]=1;
    int ans=a[x][y];
    for(int i=0;i<4;i++)
    {
        if(judge(x+dx[i],y+dy[i]))
        {
            ans+=dfs(x+dx[i],y+dy[i]);
        }
    }
    return ans;
}
void solve()
{
    cin>>n>>m;
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            cin>>a[i][j];
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            if(!vis[i][j]&&a[i][j])
            {
                ans=max(ans,dfs(i,j));
            }
        }
    }
    cout<<ans<<endl;
}
int main()
{
    int t;cin>>t;while(t--)
    solve();
    return 0;
}
```


---

## 作者：tbdsh (赞：0)

# 题意简述
[题目传送门](/problem/cf1829e)

[更好的阅读体验](/blog/tianbiandeshenghuo11/solution-cf1829e)

有 $t$ 组数据，每组数据给定一个 $n\times m$ 的矩阵。该矩阵上、下、左、右相连构成一个连通块。

连通块需要满足其中的每个数都非 $0$。

定义一个连通块的权值为该连通块中所有数的和。求矩阵中最大的连通块的权值。

# 分析
在找到一个未被搜索过的坐标且其值不为 $0$ 时，爆搜连通块即可。

每次搜索时记录权值，最后求最大值。

由于每个坐标最多访问一次，所以单次时间为 $O(n\times m)$。

**注意**，每次询问要清空标记数组。

总时间复杂度：$O(t\times n\times m)$。

空间复杂度：$O(n\times m)$。

# Code
```cpp
#include<bits/stdc++.h>

using namespace std;
int t, ans = 0, n, m;
int fx[2][4] = {{1, -1, 0, 0}, {0, 0, 1, -1}}, a[1005][1005], cnt;
bool v[1005][1005];
void dfs(int x, int y){
  ans = max(ans, cnt);
  if (x < 1 || y < 1 || x > n || y > m || v[x][y] || !a[x][y]){
    return ;
  }
  cnt += a[x][y];
  v[x][y] = 1;
  for (int i = 0; i < 4; i++){
    dfs(x + fx[0][i], y + fx[1][i]);
  }
}
int main(){
  cin >> t;
  while (t--){
    cin >> n >> m;
    ans = 0;
    for (int i = 1; i <= n; i++){
      for (int j = 1; j <= m; j++){
        v[i][j] = 0;
        cin >> a[i][j];
      }
    }
    for (int i = 1; i <= n; i++){
      for (int j = 1; j <= m; j++){
        if (!v[i][j] && a[i][j]){
          cnt = 0;
          dfs(i, j);
          ans = max(ans, cnt);
        }
      }
    }
    cout << ans << '\n';
  }
  return 0;
}
```

---

## 作者：Leaves_xw (赞：0)

哇，这么多人交题解！

**思路：**

BFS 做法，每找到一个连通块，就将这个连通块的权值进行储存，最后输出最大值即可。

**核心代码：**

共两部分：

```
vis[x][y]=1;//下面是连通块部分
long long xxx=a[x][y];
if(x+1<=n&&a[x+1][y]!=0&&!vis[x+1][y])sum+=dfs(x+1,y);
if(y+1<=m&&a[x][y+1]!=0&&!vis[x][y+1])sum+=dfs(x,y+1);
if(x-1>=1&&a[x-1][y]!=0&&!vis[x-1][y])sum+=dfs(x-1,y);
if(y-1>=1&&a[x][y-1]!=0&&!vis[x][y-1])sum+=dfs(x,y-1);
return sum;//返回值
```
以及

```
for(int i=1;i<=n;i++)
{
    for(int j=1;j<=m;j++)if(a[i][j]!=0&&vis[i][j]==0)ans=max(ans,dfs(i,j));//取最大值
    cout<<ans<<endl;
}
```

---

## 作者：VitrelosTia (赞：0)

dfs 连通块板题，搜完一个连通块就更新答案。注意到要多测清空，这道题就做完了。

```
void dfs(int x, int y) {
    now += mp[x][y];
    vis[x][y] = true;
    for (int i = 0; i < 4; i++) {
        int dx = pos[i][0] + x, dy = pos[i][1] + y;
        if (inmap(dx, dy) &&!vis[dx][dy] && mp[dx][dy] != 0) dfs(dx, dy);
    }
}
 
void solve() {
    ans = 0;
    scanf ("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> mp[i][j];
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            now = 0;
            if (mp[i][j] != 0 && !vis[i][j]) {
                dfs(i, j);
                ans = max(ans, now);
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) vis[i][j] = false;
    }
    cout << ans << '\n';
}
```

---

## 作者：rmzls (赞：0)

### 思路
广搜模板题，能被一个点搜到的点都是一个连通块里的，记录下每个点所属连通块，已有连通块（就是已经被搜过）的点不搜，最后每个连通块大小取个最值就行。对于零点，我们可以提前令它所属 $-1$ 号连通块。 

------------
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int K=1e3+10;
int t,n,m,fa[K][K],siz[K*K],ans,cnt,a[K][K];
int x[4]={0,1,0,-1},y[4]={1,0,-1,0};
void dfs(int ii,int jj,int f){
	fa[ii][jj]=f; siz[f]+=a[ii][jj];
	for(int i=0;i<=3;i++){
		int I=ii+x[i],J=jj+y[i];
		if(I>=1&&I<=n&&J>=1&&J<=m&&!fa[I][J]){
			dfs(I,J,f);
		}
	}
}
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				scanf("%d",&a[i][j]);
				if(a[i][j]==0){
					fa[i][j]=-1;
				}
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				if(!fa[i][j]){
					cnt++;
					dfs(i,j,cnt);
				}
			}
		}
		for(int i=1;i<=cnt;i++){
			ans=max(ans,siz[i]);
			siz[i]=0;
		}
		printf("%d\n",ans);
		ans=cnt=0;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				fa[i][j]=0;
			}
		}
	}
	return 0;
} 
```


---

## 作者：zajasi (赞：0)

## 题意
给你一个池塘，你可以从某一个点出发，往上下左右方向走，但不能碰到 $a_{i,j}$ 为 $0$ 的池塘。问能走到的最大体积。
## 样例解释
```
3 3
1 2 0
3 4 0
0 0 5
```
明显的，最大体积是 $(1,1)+(1,2)+(2,1)+(2,2)=10$。
## 解题思路
其实是 $4$ 方向的数池塘。

对于每一个没有访问过的点，访问并且进行深搜找出能到达的最大体积，然后比 $\max$ 就行。

咦？为什么 WA 了？

在构造一些简单数据时，我发现了一个 hack 数据。
```
2 2
0 1
1 0
```
正确答案是 $1$，我的答案是 $0$。然后就发现了问题——原来我刚开始扫的时候，没有判 $0$ 不能进深搜，导致从 $(1,1)$ 开始搜。调整一下就好了。
## AC 代码
```cpp
/*
written by : zjs123
QQ : 755328053
Wechat : zoujinshu18
CZOJ : zjs123
luogu : _JSYX_
atcoder : zajasi10
codeforces : _JSYX_
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long  
#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3)
int t;
int n,m;
int a[1101][1101];
int vis[1101][1101];
int dx[]={1,-1,0,0};
int dy[]={0,0,1,-1};
int dfs(int x,int y){
    vis[x][y]=1;
    int z=0;
    for(int i=0;i<4;i++){
        int tx=x+dx[i];
        int ty=y+dy[i];
        if(tx>0&&ty>0&&tx<=n&&ty<=m&&vis[tx][ty]==0&&a[tx][ty])z+=dfs(tx,ty);
    }
    return z+a[x][y];
}
main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>t;
    while(t--){
        cin>>n>>m;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                cin>>a[i][j];
            }
        }
        int z=0;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(vis[i][j]==0&&a[i][j]){
                    z=max(z,dfs(i,j));
                }
            }
        }
        cout<<z<<"\n";
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                vis[i][j]=0;
            }
        }
    }
    return 0;
}

```

---

## 作者：aeiouaoeiu (赞：0)

普通的 bfs/dfs。

我们遍历所有点，寻找不为 $0$ 且未被访问过的 $a_{i,j}$ 开始 dfs，把每次遍历到的点都标记为访问过，统计答案即可。

```cpp
#include<bits/stdc++.h>
#define pb push_back
#define pob pop_back
#define mp make_pair
using namespace std;
typedef int ll;
const int maxn=1005;
ll n,m,a[maxn][maxn],vis[maxn][maxn],ans;
ll dfs(ll x,ll y){
	vis[x][y]=1;
	ll res=a[x][y];
	if(x+1<=n&&a[x+1][y]!=0&&!vis[x+1][y]) res+=dfs(x+1,y);
	if(y+1<=m&&a[x][y+1]!=0&&!vis[x][y+1]) res+=dfs(x,y+1);
	if(x-1>=1&&a[x-1][y]!=0&&!vis[x-1][y]) res+=dfs(x-1,y);
	if(y-1>=1&&a[x][y-1]!=0&&!vis[x][y-1]) res+=dfs(x,y-1);
	return res;
}
int main(void){
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	ll T=1;
	cin>>T;
	for(;T--;){
		cin>>n>>m;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				cin>>a[i][j];
				vis[i][j]=0;
			}
		}
		ans=0;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				if(a[i][j]!=0&&vis[i][j]==0) ans=max(ans,dfs(i,j));
			}
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：Elairin176 (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1829E)        
bfs 板子。        
我们用普通的 bfs 求联通块板子就可以，但是需要记录每一个联通块的和。      
这里讲讲如何用 bfs 求联通块。     
我们设 $vis_{i,j}$ 为是否访问过 $a_{i,j}$，访问过为 $1$，否则为 $0$。再设 $sum$ 为本次答案，$ans$ 为最终答案。      
我们扫一遍 $a$，如果 $a_{i,j}≠0$ 且 $vis_{i,j}=0$ 我们就进行一轮 bfs 并记录下 $sum$。        
记得每次开始 bfs 都要清空 $sum$，结束后要和 $ans$ 取最大值。      
[CODE](https://www.luogu.com.cn/paste/bxig0zhc)

---

