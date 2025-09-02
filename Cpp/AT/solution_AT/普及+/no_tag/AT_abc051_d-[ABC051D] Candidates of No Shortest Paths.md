# [ABC051D] Candidates of No Shortest Paths

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc051/tasks/abc051_d

自己ループと二重辺を含まない $ N $ 頂点 $ M $ 辺の重み付き無向連結グラフが与えられます。  
 $ i\ (1≦i≦M) $ 番目の辺は頂点 $ a_i $ と頂点 $ b_i $ を距離 $ c_i $ で結びます。   
 ここで、自己ループは $ a_i\ =\ b_i\ (1≦i≦M) $ となる辺のことを表します。   
 また、二重辺は $ (a_i,b_i)=(a_j,b_j) $ または $ (a_i,b_i)=(b_j,a_j)\ (1≦i\ <\ j≦M) $ となる辺のことを表します。   
 連結グラフは、どの異なる $ 2 $ 頂点間にも経路が存在するグラフのことを表します。   
 どの異なる $ 2 $ 頂点間の、どの最短経路にも含まれない辺の数を求めてください。

## 说明/提示

### 制約

- $ 2≦N≦100 $
- $ N-1≦M≦min(N(N-1)/2,1000) $
- $ 1≦a_i,b_i≦N $
- $ 1≦c_i≦1000 $
- $ c_i $ は整数である。
- 与えられるグラフは自己ループと二重辺を含まない。
- 与えられるグラフは連結である。

### Sample Explanation 1

この入力例で与えられるグラフにおける、全ての異なる $ 2 $ 頂点間の最短経路は以下の通りです。 - 頂点 $ 1 $ から頂点 $ 2 $ への最短経路は、頂点 $ 1 $ → 頂点 $ 2 $ で経路長は $ 1 $ - 頂点 $ 1 $ から頂点 $ 3 $ への最短経路は、頂点 $ 1 $ → 頂点 $ 3 $ で経路長は $ 1 $ - 頂点 $ 2 $ から頂点 $ 1 $ への最短経路は、頂点 $ 2 $ → 頂点 $ 1 $ で経路長は $ 1 $ - 頂点 $ 2 $ から頂点 $ 3 $ への最短経路は、頂点 $ 2 $ → 頂点 $ 1 $ → 頂点 $ 3 $ で経路長は $ 2 $ - 頂点 $ 3 $ から頂点 $ 1 $ への最短経路は、頂点 $ 3 $ → 頂点 $ 1 $ で経路長は $ 1 $ - 頂点 $ 3 $ から頂点 $ 2 $ への最短経路は、頂点 $ 3 $ → 頂点 $ 1 $ → 頂点 $ 2 $ で経路長は $ 2 $ したがって、一度も最短経路として使用されていない辺は、頂点 $ 2 $ と頂点 $ 3 $ を結ぶ長さ $ 3 $ の辺のみであるため、$ 1 $ を出力します。

### Sample Explanation 2

全ての辺が異なる $ 2 $ 頂点間のある最短経路で使用されます。

## 样例 #1

### 输入

```
3 3
1 2 1
1 3 1
2 3 3```

### 输出

```
1```

## 样例 #2

### 输入

```
3 2
1 2 1
2 3 1```

### 输出

```
0```

# 题解

## 作者：panyanppyy (赞：3)

## Problem
给定一个 $n\le100$ 个点，$m$ 条边的加权无向连通图，问全源最短路有几条边没被用到。
## Solution
$n$ 只有 $100$，直接跑 Floyd，再每次记录当前边有没有被松弛掉，如果是第一次松弛就 $ans\gets ans+1$。

由于是无向图，所以 $ans=\dfrac{ans}{2}$。

时间复杂度 $\mathcal O(n^3)$
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=101;
int n,m,g[N][N],ans;
bool vis[N][N];
int main(){
	scanf("%d%d",&n,&m);
	memset(g,0x3f,sizeof(g));
	for(int i=1,x,y,z;i<=m;i++){
		scanf("%d%d%d",&x,&y,&z);
		g[x][y]=g[y][x]=z,vis[x][y]=vis[y][x]=1;
	}//记录边，并且给边打上标记
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
			if(g[i][j]>g[i][k]+g[k][j]){
				if(vis[i][j])ans++,vis[i][j]=0;
                //如果是第一次松弛，ans++
				g[i][j]=g[i][k]+g[k][j];
			}//Floyd模板
	printf("%d",ans>>1);
	return 0;
}

```

---

## 作者：Tear_stains (赞：2)

题意：

给定一个无向图，求全源最短路径有几条边没用。

思路：

本题 $n$ 的范围较小，所以跑 floyd 即可。

如果当前这条边被另外两条边更新了，证明这条边没用，记录答案。

记住是无向图，答案需要除以二。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 105;
int n, m, ds[N][N], ans;
bool vs[N][N];
int main(){
	scanf("%d%d", &n, &m);
	memset(ds, 0x3f, sizeof(ds));
	for(int i = 1;i <= m; ++i) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		ds[u][v] = ds[v][u] = w, vs[u][v] = vs[v][u] = 1;
	}
	for(int k = 1;k <= n; ++k) {
		for(int i = 1;i <= n; ++i) {
			for(int j = 1;j <= n; ++j) {
				if(ds[i][j] > ds[i][k] + ds[k][j]){
		    		if(vs[i][j]) {
		     			++ans;
		    		    vs[i][j] = 0;
		     		}
		      		ds[i][j] = ds[i][k] + ds[k][j];
	     		}
			}	
		}
	}
	printf("%d",ans / 2);
	return 0;
}

```


---

