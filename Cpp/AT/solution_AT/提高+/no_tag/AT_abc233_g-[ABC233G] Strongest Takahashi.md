# [ABC233G] Strongest Takahashi

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc233/tasks/abc233_g

$ N\ \times\ N $ のグリッドがあり、いくつかのマスにはブロックが置いてあります。  
 グリッドの情報は $ N $ 個の文字列 $ S_1,S_2,\dots,S_N $ によって以下の形式で与えられます。

- $ S_i $ の $ j $ 文字目が `#` のとき、グリッドの上から $ i $ マス目、左から $ j $ マス目にブロックがある。
- $ S_i $ の $ j $ 文字目が `.` のとき、グリッドの上から $ i $ マス目、左から $ j $ マス目にブロックがない。

高橋くんは、以下の操作を $ 0 $ 回以上好きなだけ行うことができます。

- まず、 $ 1 $ 以上 $ N $ 以下の整数 $ D $ と、グリッド内の $ D\ \times\ D $ の部分正方形を選ぶ。
- その後、体力 $ D $ を消費して部分正方形内のブロックをすべて破壊する。

高橋くんがすべてのブロックを破壊するのに必要な体力の最小値を求めてください。

## 说明/提示

### 制約

- $ N $ は整数
- $ 1\ \le\ N\ \le\ 50 $
- $ S_i $ は `#` と `.` のみからなる
- $ |S_i|=N $

### Sample Explanation 1

以下の部分正方形を選ぶことで、消費する体力を $ 4 $ にすることができ、これが最適です。 - 上から $ 1 $ マス目、左から $ 1 $ マス目を左上とした、 $ 3\ \times\ 3 $ の部分正方形 - 上から $ 5 $ マス目、左から $ 5 $ マス目を左上とした、 $ 1\ \times\ 1 $ の部分正方形

### Sample Explanation 2

グリッドにブロックが $ 1 $ つもない場合もあります。

## 样例 #1

### 输入

```
5
##...
.##..
#.#..
.....
....#```

### 输出

```
4```

## 样例 #2

### 输入

```
3
...
...
...```

### 输出

```
0```

## 样例 #3

### 输入

```
21
.....................
.....................
...#.#...............
....#.............#..
...#.#...........#.#.
..................#..
.....................
.....................
.....................
..........#.....#....
......#..###.........
........#####..#.....
.......#######.......
.....#..#####........
.......#######.......
......#########......
.......#######..#....
......#########......
..#..###########.....
.........###.........
.........###.........```

### 输出

```
19```

# 题解

## 作者：liuyi0905 (赞：1)

## 题意：
给定一个 $N\times N$ 大小的矩阵，你每次可以将一个 $D\times D$ 的矩阵中的所有 `#` 删除，代价为 $D$。

要你求出将所有 `#` 删除的最小代价。
## 思路：
由于 $N$ 的数据范围很小，时间限制又大，可以考虑暴力法 + $dp$ 来解题。枚举矩阵的左上顶点和右下顶点，找出删除的最有方案，$dp_{i,j,k,l}$ 意为删除左上顶点为 $i,j$、右下顶点为 $k,l$ 的矩阵的最小代价，所以最后的答案为 $dp_{1,1,N,N}$。

整份程序时间复杂度为 $O(N^5)$，可以 AC。

## 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
#define N 55
using namespace std;
int n,dp[N][N][N][N];
char s[N][N];
signed main(){
	memset(dp,0x7f,sizeof(dp));
	cin>>n;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			cin>>s[i][j];
			if(s[i][j]=='.')dp[i][j][i][j]=0;
			else dp[i][j][i][j]=1;		
		}
	for(int x1=0;x1<n;x1++)
		for(int y1=0;y1<n;y1++)
			for(int x2=1;x2<=n;x2++)
				for(int y2=1;y2<=n;y2++){
					int nx=x2+x1,ny=y2+y1;
					if(nx>n||ny>n)continue;
					if(x1==y1)dp[x2][y2][nx][ny]=min(dp[x2][y2][nx][ny],x1+1);
					for(int x3=x2;x3<nx;x3++)dp[x2][y2][nx][ny]=min(dp[x2][y2][nx][ny],dp[x2][y2][x3][ny]+dp[x3+1][y2][nx][ny]);
					for(int y3=y2;y3<ny;y3++)dp[x2][y2][nx][ny]=min(dp[x2][y2][nx][ny],dp[x2][y2][nx][y3]+dp[x2][y3+1][nx][ny]);
				}
	cout<<dp[1][1][n][n];
	return 0;
}
```

---

## 作者：CarroT5656 (赞：0)

**题目大意**

给定一个 $N\times N$ 的矩阵，你每次可以选取一个 $D\times D$ 的矩阵，并将这个矩阵内的所有 `#` 删除，代价为 $D$。

问你把所有 `#` 都删除的代价是多少。

**解法分析**

可以知道两个矩阵相交肯定不优，所以一个 $n\times m$ 的矩阵的最小代价为 $\max(n,m)$。

考虑一个矩阵，可以证明，一定可以找到一条线，使得在最优的选择下，没有一个矩阵在这条线上。

所以你可以沿着这条线将矩阵分成两半，再分别计算答案。

可以考虑 dp，令 $dp_{i,j,k,l}$ 表示以 $(i,j)$ 为左上角，$(k,l)$ 为右上角的矩阵的答案。

暴力枚举每一条线，计算答案即可。

时间复杂度 $O(n^5)$，可以通过。

**Code**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define N 55
ll n,dp[N][N][N][N];
char s[N][N];
void Min(ll &x,ll y){if(y<x) x=y;}
int main(){
	memset(dp,0x3f,sizeof dp);
	scanf("%lld",&n);
	for(ll i=1;i<=n;i++) scanf("%s",s[i]+1);
	for(ll i=1;i<=n;i++) for(ll j=1;j<=n;j++){
		if(s[i][j]=='.') dp[i][j][i][j]=0;
		else dp[i][j][i][j]=1;
	}
	for(ll dx=0;dx<n;dx++) for(ll dy=0;dy<n;dy++) for(ll sx=1;sx<=n;sx++) for(ll sy=1;sy<=n;sy++){
		ll ex=sx+dx,ey=sy+dy;
		if(ex>n||ey>n) continue;
		if(dx==dy) Min(dp[sx][sy][ex][ey],dx+1);
		for(ll gx=sx;gx<ex;gx++) Min(dp[sx][sy][ex][ey],dp[sx][sy][gx][ey]+dp[gx+1][sy][ex][ey]);
		for(ll gy=sy;gy<ey;gy++) Min(dp[sx][sy][ex][ey],dp[sx][sy][ex][gy]+dp[sx][gy+1][ex][ey]);
	}
	printf("%lld\n",dp[1][1][n][n]);
	return 0;
}
```

---

