# Alternating Path

## 题目描述

[problemUrl]: https://atcoder.jp/contests/aising2019/tasks/aising2019_c

$ H $ 行 $ W $ 列のマス目があり、各マスは黒または白に塗られています。

各マスの色を表す $ H $ 個の長さ $ W $ の文字列 $ S_1,\ S_2,\ ...,\ S_H $ が与えられます。 マス目の上から $ i $ 番目、左から $ j $ 番目 ($ 1\ \leq\ i\ \leq\ H,\ 1\ \leq\ j\ \leq\ W $) のマスが黒く塗られているとき 文字列 $ S_i $ の $ j $ 文字目は `#` となっており、白く塗られているとき文字列 $ S_i $ の $ j $ 文字目は `.` となっています。

黒く塗られたマス $ c_1 $ と白く塗られたマス $ c_2 $ の組であって、以下の条件を満たすものの個数を求めてください。

- 上下左右に隣り合うマスへの移動を繰り返してマス $ c_1 $ からマス $ c_2 $ へ行く方法であって、通るマスの色が黒、白、黒、白・・・と交互になっているものが存在する。

## 说明/提示

### 制約

- $ 1\ \leq\ H,\ W\ \leq\ 400 $
- $ |S_i|\ =\ W $ ($ 1\ \leq\ i\ \leq\ H $)
- 各 $ i $ ($ 1\ \leq\ i\ \leq\ H $) に対して、文字列 $ S_i $ は文字 `#` と文字 `.` だけからなる。

### Sample Explanation 1

上から $ i $ 行目、左から $ j $ 列目のマスを $ (i,\ j) $ と書くとき、条件を満たすマスの組として $ ((1,\ 2),\ (3,\ 3)) $ や $ ((3,\ 1),\ (3,\ 2)) $ などがあります。

## 样例 #1

### 输入

```
3 3
.#.
..#
#..```

### 输出

```
10```

## 样例 #2

### 输入

```
2 4
....
....```

### 输出

```
0```

## 样例 #3

### 输入

```
4 3
###
###
...
###```

### 输出

```
6```

# 题解

## 作者：panyanppyy (赞：1)

## Problem
给定一个黑白染色图，求出黑色点和白色点可以颜色交替到达的点对数。
## Solution
很容易想到将图划分成多个连通块，连通块内可以两两到达，这样这个连通块对答案的贡献就是：$P_\texttt{White}\times P_\texttt{Black}$。

考虑如何简化构造连通块的过程。一种可行的方法就是对每个 $a_{i,j}\left[ i+j \bmod 2=1 \right]$ 的点颜色取反，并统计他对当前连通块颜色的贡献 1，然后直接把相同的点和连通块大小用并查集维护一下就可以了。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ri register
#define all(x) x.begin(),x.end()
using namespace std;
const int N=401,M=N*N;
int n,m,f[M],g[M],sz[M];
//g[]是当前连通块中其中一种颜色点的数量，sz[]是连通块大小
ll ans;
char a[N][N];
inline int ord(int x,int y){return(x-1)*m+y;}//压成一位
inline int find(int z){return f[z]==z?z:f[z]=find(f[z]);}//并查集
inline void merge(int x,int y){
	x=find(x),y=find(y);
	if(x==y)return;
	f[x]=y,sz[y]+=sz[x],g[y]+=g[x];
	sz[x]=g[x]=0;
}//合并带权并查集
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%s",a[i]+1);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		if((i+j)&1)a[i][j]=a[i][j]=='#'?'.':'#',g[ord(i,j)]++;//统计贡献,颜色取反。
	for(int i=1;i<=n*m;i++)sz[i]=1,f[i]=i;//初始化
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			if(a[i][j]==a[i+1][j])
				merge(ord(i,j),ord(i+1,j));
			if(a[i][j]==a[i][j+1])
				merge(ord(i,j),ord(i,j+1));
		}
	for(int i=1;i<=n*m;i++)
		if(f[i]==i)ans+=1ll*g[i]*(sz[i]-g[i]);
 		//总大小-其中一种颜色点数=剩下那种颜色点数
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：LJQ0808 (赞：0)

[传送门](https://www.luogu.com.cn/problem/AT_aising2019_c)

# 题解

因为题目要求“若有一条从黑色方格到达白色方格的路径，途中只沿水平或垂直方向移动，所经相邻方格颜色不同，我们将这个路径称为合法的。”所以我们可以用 BFS 算法求解这道题。

在 BFS 中，有一些答案可能被计算多次，所以我们可以用 vis 数组记录此点有没有搜索过。但这样会少算一些方案数，于是我们可以在搜索内记录走过几个白点和黑点。

方案数为白点个数乘黑点个数。为什么呢？因为起点和终点一定为白点和黑点。根据乘法原理，得证。

AC code:

```
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
#define pii pair<int,int>
#define fi first
#define se second 
const int N=4e2+5;
int n,m;
char a[N][N];
bool vis[N][N];//vis[i][j] 表示有没有搜索过。 
queue<pii> q;//bfs 的队列。 
int dx[4][2]={//方向数组。 
	{ 1, 0},
	{-1, 0},
	{ 0, 1},
	{ 0,-1}
};
signed main(){
	//HAPPY!
	cin.tie(0);
	cout.tie(0);
	ios_base::sync_with_stdio(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a[i][j]; 
		}
	}
	ll ans=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(vis[i][j]){//搜索过了。 
				continue;//跳过。 
			}
			vis[i][j]=1;//现在开始搜索。 
			q.push({i,j});//加入队列。 
			int w=0,b=0;//经过白点和黑点的个数。 
			while(!q.empty()){//bfs。 
				pii P=q.front();q.pop();//取头，并去掉。 
				int x=P.fi,y=P.se; 
				if(a[x][y]=='.'){//现在为白点。 
					w++; 
				} 
				else{//现在为黑点。 
					b++;
				}
				for(int k=0;k<4;k++){//要经过其它点。 
					int nx=x+dx[k][0],ny=y+dx[k][1];
					if(nx>=1 && nx<=n && ny>=1 && ny<=m && a[x][y]!=a[nx][ny] && !vis[nx][ny]){//符合操作。 
						vis[nx][ny]=1;//搜索过了。 
						q.push({nx,ny});
					}
				}
			}
			ans+=1ll*w*b;//求答案。  
		}
	}
	cout<<ans<<"\n";
	return 0;
}
```

---

