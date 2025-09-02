# [ABC371C] Make Isomorphic

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc371/tasks/abc371_c

頂点 $ 1, $ 頂点 $ 2,\ldots, $ 頂点 $ N $ の $ N $ 個の頂点からなる単純無向グラフ $ G,H $ が与えられます。 $ G $ には $ M\ _\ G $ 本の辺があり、$ i $ 本目 $ (1\leq\ i\leq\ M\ _\ G) $ の辺は頂点 $ u\ _\ i $ と頂点 $ v\ _\ i $ を結んでいます。 $ H $ には $ M\ _\ H $ 本の辺があり、$ i $ 本目 $ (1\leq\ i\leq\ M\ _\ H) $ の辺は頂点 $ a\ _\ i $ と頂点 $ b\ _\ i $ を結んでいます。

あなたは、グラフ $ H $ に対して次の操作を $ 0 $ 回以上の好きな回数繰り返すことができます。

- $ 1\leq\ i\lt\ j\leq\ N $ を満たす整数の組 $ (i,j) $ をひとつ選ぶ。$ A\ _\ {i,j} $ 円を支払って、頂点 $ i $ と頂点 $ j $ を結ぶ辺がなければ追加し、あれば取り除く。

$ G $ と $ H $ を同型にするために少なくとも何円支払う必要があるか求めてください。

単純無向グラフとは？ **単純無向グラフ**とは、自己ループや多重辺を含まず、辺に向きの無いグラフのことをいいます。

グラフの同型とは？ $ N $ 頂点のグラフ $ G $ と $ H $ が**同型**であるとは、ある $ (1,2,\ldots,N) $ の並べ替え $ (P\ _\ 1,P\ _\ 2,\ldots,P\ _\ N) $ が存在して、どの $ 1\leq\ i\lt\ j\leq\ N $ に対しても

- $ G $ に頂点 $ i, $ 頂点 $ j $ を結ぶ辺が存在するとき、かつそのときに限り $ H $ に頂点 $ P\ _\ i, $ 頂点 $ P\ _\ j $ を結ぶ辺が存在する

が成り立つことをいいます。

## 说明/提示

### 制約

- $ 1\leq\ N\leq8 $
- $ 0\leq\ M\ _\ G\leq\dfrac{N(N-1)}2 $
- $ 0\leq\ M\ _\ H\leq\dfrac{N(N-1)}2 $
- $ 1\leq\ u\ _\ i\lt\ v\ _\ i\leq\ N\ (1\leq\ i\leq\ M\ _\ G) $
- $ (u\ _\ i,v\ _\ i)\neq(u\ _\ j,v\ _\ j)\ (1\leq\ i\lt\ j\leq\ M\ _\ G) $
- $ 1\leq\ a\ _\ i\lt\ b\ _\ i\leq\ N\ (1\leq\ i\leq\ M\ _\ H) $
- $ (a\ _\ i,b\ _\ i)\neq(a\ _\ j,b\ _\ j)\ (1\leq\ i\lt\ j\leq\ M\ _\ H) $
- $ 1\leq\ A\ _\ {i,j}\leq\ 10\ ^\ 6\ (1\leq\ i\lt\ j\leq\ N) $
- 入力はすべて整数

### Sample Explanation 1

与えられたグラフはそれぞれ以下のようになります。 !\[\](https://img.atcoder.jp/abc371/fbdb304dc71eecd7ddec97276a9c7040.png) たとえば、$ H $ に対して次のような $ 4 $ つの操作を順に行うことで、$ 9 $ 円を支払って$ G $ と $ H $ を同型にすることができます。 - $ (i,j)=(1,3) $ として操作を行う。$ H $ には頂点 $ 1 $ と頂点 $ 3 $ を結ぶ辺があるので、$ 1 $ 円を支払ってこれを取り除く。 - $ (i,j)=(2,5) $ として操作を行う。$ H $ には頂点 $ 2 $ と頂点 $ 5 $ を結ぶ辺はないので、$ 2 $ 円を支払ってこれを追加する。 - $ (i,j)=(1,5) $ として操作を行う。$ H $ には頂点 $ 1 $ と頂点 $ 5 $ を結ぶ辺があるので、$ 1 $ 円を支払ってこれを取り除く。 - $ (i,j)=(3,5) $ として操作を行う。$ H $ には頂点 $ 3 $ と頂点 $ 5 $ を結ぶ辺はないので、$ 5 $ 円を支払ってこれを追加する。 操作の結果、$ H $ は以下のようになります。 !\[\](https://img.atcoder.jp/abc371/68a56da8ec89b769989ae7d07bf163cd.png) 支払う金額を $ 8 $ 円以下にして $ G $ と $ H $ を同型にすることはできないため、`9` を出力してください。

### Sample Explanation 2

たとえば、$ (i,j)=(2,3),(2,4),(3,4) $ とした $ 3 $ 回の操作を行うことで $ G $ と $ H $ を同型にすることができます。

### Sample Explanation 3

たとえば、$ (i,j)=(4,5) $ とした $ 1 $ 回の操作を行うことで $ G $ と $ H $ を同型にすることができます。

### Sample Explanation 4

$ G $ や $ H $ には辺が含まれていないこともあります。 また、一度も操作をする必要がないこともあります。

## 样例 #1

### 输入

```
5
4
1 2
2 3
3 4
4 5
4
1 2
1 3
1 4
1 5
3 1 4 1
5 9 2
6 5
3```

### 输出

```
9```

## 样例 #2

### 输入

```
5
3
1 2
2 3
3 4
4
1 2
2 3
3 4
4 5
9 1 1 1
1 1 1
1 1
9```

### 输出

```
3```

## 样例 #3

### 输入

```
5
3
1 2
2 3
3 4
4
1 2
2 3
3 4
4 5
5 4 4 4
4 4 4
4 4
5```

### 输出

```
5```

## 样例 #4

### 输入

```
2
0
0
371```

### 输出

```
0```

## 样例 #5

### 输入

```
8
13
1 8
5 7
4 6
1 5
7 8
1 6
1 2
5 8
2 6
5 6
6 7
3 7
4 8
15
3 5
1 7
4 6
3 8
7 8
1 2
5 6
1 6
1 5
1 4
2 8
2 6
2 4
4 7
1 3
7483 1694 5868 3296 9723 5299 4326
5195 4088 5871 1384 2491 6562
1149 6326 2996 9845 7557
4041 7720 1554 5060
8329 8541 3530
4652 3874
3748```

### 输出

```
21214```

# 题解

## 作者：Him_shu (赞：14)

## 问题
给定简单无向图 $G$ 和 $H$ ，每个图都有 $N$ 个顶点。
1.  $G$ 有 $M_G$ 条边；
2.  $H$ 有 $M_H$ 条边。

可以对 $H$ 执行任意次数操作：
1. 选择满足 $1\leq i < j\leq N$ 的整数 $(i, j)$ ，支付 $A_{i,j}$ 日元；
    - 若 $H$ 中 $i$ 与 $j$ 间无边，则添加边；
    - 若 $H$ 中 $i$ 与 $j$ 间有边，则删除边。

求使 $G$ 和 $H$ 同构的最小总成本。

## 分析
发现 $1\leq N\leq8$ 所以暴力即可。

先全排列每个点的映射，把两个图相同情况遍历出来，再建图，最后枚举每条边：
- 如果该边都有或都没有，那么不管。
- 否则，加上或删去（其实只用把答案加上 $a_{i,j}$ 即可）

## Code
```cpp
#include<bits/stdc++.h>
#define int long long 
#define inf 1e14
#define N 105
using namespace std;
int n,m1,m2,u1[N],u2[N],v1[N],v2[N];
int h[N][N],g[N][N],a[N][N];
int hg[N],ans=inf;
void dfs(int pos){
	if(pos>n){
		for(int i=1;i<=m1;i++){
			h[hg[u1[i]]][hg[v1[i]]]=h[hg[v1[i]]][hg[u1[i]]]=1;
		}//全排列完，再建图
		int sum=0;
		for(int i=1;i<n;i++){
			for(int j=i+1;j<=n;j++){
				if(h[i][j]==g[i][j]){//相同不管
					continue;
				}
				sum+=a[i][j];//否则加上代价
			}
		}
		ans=min(ans,sum);//取最小
		memset(h,0,sizeof(h));//注意清空
		return;
	}
	for(int i=1;i<=n;i++){
		if(!hg[i]){
			hg[i]=pos;
			dfs(pos+1);
			hg[i]=0;
		}
	}
}
signed main(){
	cin>>n;
	cin>>m1;
	for(int i=1;i<=m1;i++){
		cin>>u1[i]>>v1[i];
	}
	cin>>m2;
	for(int i=1;i<=m2;i++){
		cin>>u2[i]>>v2[i];
		g[u2[i]][v2[i]]=g[v2[i]][u2[i]]=1;
	}
	for(int i=1;i<n;i++){
		for(int j=i+1;j<=n;j++){
			cin>>a[i][j];
			a[j][i]=a[i][j];
		}
	}
	dfs(1);
	cout<<ans;
	return 0;
}
```

---

## 作者：small_lemon_qwq (赞：13)

爆搜枚举全排列即可，然后计算此时的代价，最后取最小值即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,vis[10],p[10],m,f[10][10],g[10][10],a[10][10],ans=LONG_LONG_MAX;
void dfs(int x){
	if(x>n){
		int cnt=0;
		for(int i=1;i<=n;i++){
			for(int j=i+1;j<=n;j++){
				if(f[p[i]][p[j]]!=g[i][j]){
					cnt+=a[i][j];
				}
			}
		}
		ans=min(ans,cnt);
	}else{
		for(int i=1;i<=n;i++){
			if(!vis[i]){
				p[x]=i;
				vis[i]=1;
				dfs(x+1);
				vis[i]=0;
			}
		}
	}
}//全排列
signed main(){
	cin>>n>>m;
	while(m--){
		int u,v;
		cin>>u>>v;
		f[u][v]=f[v][u]=1;
	}
	cin>>m;
	while(m--){
		int u,v;
		cin>>u>>v;
		g[u][v]=g[v][u]=1;
	}
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			cin>>a[i][j];
		}
	}
	dfs(1);
	cout<<ans;
	return 0;
}
```

---

## 作者：RedStoneShark (赞：10)

### 思路

观察到本题 $N \leq 8$，可以全排列枚举所有情况，取最小值。时间复杂度 $ \mathcal{O}(n!)$。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long 
#define inf 1e14
#define N 130
using namespace std;
int n,m1,m2,u1[N],u2[N],v1[N],v2[N];
int h[N][N],g[N][N],a[N][N];
int hg[N],ans=inf;
void dfs(int pos){
	if(pos>n){
		for(int i=1;i<=m1;i++){
			h[hg[u1[i]]][hg[v1[i]]]=h[hg[v1[i]]][hg[u1[i]]]=1;
		}
		int sum=0;
		for(int i=1;i<n;i++){
			for(int j=i+1;j<=n;j++){
				if(h[i][j]==g[i][j]){
					continue;
				}
				sum+=a[i][j];
			}
		}
		ans=min(ans,sum);
		memset(h,0,sizeof(h));
		return;
	}
	for(int i=1;i<=n;i++){
		if(!hg[i]){
			hg[i]=pos;
			dfs(pos+1);
			hg[i]=0;
		}
	}
}
signed main(){
	cin>>n;
	cin>>m1;
	for(int i=1;i<=m1;i++){
		cin>>u1[i]>>v1[i];
	}
	cin>>m2;
	for(int i=1;i<=m2;i++){
		cin>>u2[i]>>v2[i];
		g[u2[i]][v2[i]]=g[v2[i]][u2[i]]=1;
	}
	for(int i=1;i<n;i++){
		for(int j=i+1;j<=n;j++){
			cin>>a[i][j];
			a[j][i]=a[i][j];
		}
	}
	dfs(1);
	cout<<ans;
	return 0;
}

```

---

## 作者：fishing_cat (赞：8)

### 题意

给定两个图，求使两个图图同构的最小花费，保证没有重边和自环。

### 图的同构

图的同构是图论中的一个概念，用来描述两个图是否具有相同的结构。两个图 $G1$ 和 $G2$ 是同构的，当且仅当存在一个从图 $G1$ 到图 $G2$ 的对应映射 $f$，使得任意两个节点 $u$ 和 $v$ 在图 $G1$ 中如果相邻（即存在边连接 $u$ 和 $v$），那么在图 $G2$ 中对应的节点 $f(u)$ 和 $f(v)$ 也相邻。换句话说，两个图的同构意味着它们的连接模式相同，只是节点的名称或位置可能不同。

### 思路

直接暴力遍历点对应的每种方案，即全排列。

对于每种方案，统计不一致的边并计算答案，并更新最小值。

因为要求要两个图同构，所以要添加没有的边，删除多余的边，所以只要边不一致就要计算花费。


### 代码

```cpp
#include<bits/stdc++.h>
#define ll long long

using namespace std;

// 快读省了

ll n, mg, mh, ans;
ll u[200], v[200], a[200], b[200], A[200][200];
ll mp1[200][200],mp2[200][200], dis[200];

void f () {
	ll num = 0;
	for (int i = 1;i <= n-1; i++)
		for (int j= i+1; j <= n;j ++) 
			if (mp1[dis[i]][dis[j]] ^ mp2[i][j]) // 是否不同
			num += A[i][j];
	ans = min(ans, num); // 统计最小值
}

int main() {
	read(n); read(mg); 
	for (int i = 1; i <= mg; i ++) {
		read(u[i]); read(v[i]);
		mp1[u[i]][v[i]] = 1;
		mp1[v[i]][u[i]] = 1;
	}
	read(mh);
	for (int i = 1; i <= mh; i ++) {
		read(a[i]); read(b[i]);
		mp2[a[i]][b[i]] = 1;
		mp2[b[i]][a[i]] = 1;
	}
	for (int i = 1; i <= n-1; i++) 
		for (int j = i+1; j <= n ;j ++) 
			read(A[i][j]);
	for (int i = 1 ; i<=n; i++) 
		dis[i] = i; 
	ans = 1e10;
	do{
		f(); // 计算当前排列下最小花费
	}while (next_permutation(dis+1,dis+n+1)); // 遍历全排列
	cout << ans << endl;
	return 0; // 完结撒花！
}
```

---

## 作者：cqsunny (赞：4)

首先，我们要读懂图同构的意思。

简单来说，图同构的意思是将所有点重新排列，所得到的图与原图图同构。



---

由于 $N \le 8$，所以可以直接全排列顶点，求出每次花费，最后输出最小值即可。

图同构的边一定没有变化，所以求花费时，只要两个图的某条边不同，就加上花费。

全排列可以直接使用 `next_permutation` 就行了，也可以写 `dfs`。


---

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, m1, m2;
//用邻接矩阵存图
int a[10][10] = {0};
int b[10][10] = {0};
int w[10][10] = {0};
int p[10];
int main(){
    scanf("%d %d", &n, &m1);
    for(int i = 1; i <= m1; ++ i){
        int x, y;
        输入 x 和 y
        a[x][y] = a[y][x] = 1;
    }
    scanf("%d", &m2);
    for(int i = 1; i <= m2; ++ i){
        int x, y;
        输入 x 和 y
        b[x][y] = b[y][x] = 1;
    }
    for(int i = 1; i <= n; ++ i){
        for(int j = i + 1; j <= n; ++ j){
            scanf("%d", &w[i][j]);
            w[j][i] = w[i][j];
        }
    }
    //初始化
    for(int i = 1; i <= n; ++ i){
        p[i] = i;
    }
    long long ans = 1e17;
    do{
        //计算费用
        long long sum = 0;
        for(int i = 1; i <= n; ++ i){
            for(int j = i + 1; j <= n; ++ j){
                if(a[i][j] != b[p[i]][p[j]]){
                    sum += w[p[i]][p[j]];
                }
            }
        }
        ans = min(ans, sum);
    }while(next_permutation(p + 1, p + n + 1));
    printf("%lld", ans);
    return 0;
}

```

---

## 作者：hjyowl (赞：4)

### 题目大意

给定两个图，判断通过删除或者添加一些边使得两个图同构，每条边删除或添加有价值，清算出最小价值。

### 思路

由于同构只需要在某个全排列的意义下相等即可，故考虑枚举全排列然后对于每个全排列计算价值，然后对答案取最小值。

### 时间复杂度

$\Theta(n!\times n^2)$，由于 $n$ 很小，故可以通过。

### 实现细节

见代码。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const long long N = 100;
long long a[N][N];
long long c[N][N];
long long p[N][N];
long long t[N][N];
long long n, m, k;
long long x[N];
int main() {
	cin >> n;
	cin >> m;
	for (long long i = 1; i <= m; i ++ ) {
		long long x, y;
		cin >> x >> y;
		a[x][y] = a[y][x] = 1;
	}
	cin >> k;
	for (long long i = 1; i <= k; i ++ ) {
		long long x, y;
		cin >> x >> y;
		c[x][y] = c[y][x] = 1;
	}
	for (int i = 1; i <= n; i ++ ){
		x[i] = i;
	} 
	for (long long i = 1; i <= n; i ++ ) {
		for (long long j = i + 1; j <= n; j ++ ) {
			cin >> p[i][j];
		}
	}
	long long res = LONG_LONG_MAX;
	do {
		long long cnt = 0;
		for (long long i = 1; i <= n; i ++ ) {
			for (long long j = i + 1; j <= n; j ++ ) {
				if (c[i][j] != a[x[i]][x[j]]) {
					cnt += p[i][j];
				}
			}
		}
		res = min(res, cnt);
	} while (next_permutation(x + 1, x + 1 + n));
	cout << res;
	return 0;
}
```

---

## 作者：fengzhaoyu (赞：3)

## 题意
给出两个图 $g$ 和 $h$，又给出 $h$ 图中两个点 $i$ 和 $j$（$i < j$） 的 $a_{i,j}$ 表示将他们建或删一条边后所要的花费。求最后将 $h$ 图与 $g$ 图同构所需最小花费。所谓的同构，就是长得一样，但节点不一定一一对应，比如说，$g$ 图的点 1 在 $h$ 图中同样的位置上就是 3。
## 思路
我们一看这数据范围：$n \le 8$，在想什么呢，暴力呀！遍历 $h$ 图的每一种与 $g$ 图节点的对应方式。怎么计算每一种方式的花费呢？只需判断两图中对应的两个节点的关系是否一样（连或不连）。如果一样，说明目前可以成为同构图；否则，说明他不可能是同构的，就加上连或删他俩的花费。最后求所有方式的最小值。
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=5e3+5;
int g[N][N],h[N][N],a[N][N];//意义如题，我用邻接矩阵存图
int id[N];//表示g图的点i在h图为id[i]
signed main()
{
	int m1,m2,n;
	cin>>n>>m1;
	for(int i=1;i<=m1;i++)
	{
		int x,y;
		cin>>x>>y;
		g[x][y]=1;
	}
	cin>>m2;
	for(int i=1;i<=m2;i++)
	{
		int x,y;
		cin>>x>>y;
		h[x][y]=1;		
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=i+1;j<=n;j++)
		{
			cin>>a[i][j];
		}
  }//输入
for(int i=1;i<=n;i++) id[i]=i;//初始排列
	int ans=1e9+7;
	do{
		int res=0;
		for(int i=1;i<=n;i++)
		{
			for(int j=i+1;j<=n;j++)
			{
				int x=min(id[i],id[j]);
				int y=max(id[i],id[j]);
				if(h[x][y]!=g[i][j])
				{
					res+=a[x][y];
					}
			}
		}
		ans=min(ans,res);
	}while(next_permutation(id+1,id+1+n));//此函数就是求h图的所有方式，即全排列，可以上网搜
	cout<<ans<<endl;
	return 0;
	
}
```

---

## 作者：Clover_Lin (赞：3)

### 题目大意
有两个简单无向图，你每一次可以给第二个图添上或去掉一条边，有相应花费，问将两个图变为同构最少需要花费多少钱。
### 思路
观察数据范围，可以发现 $N$ 非常小，可以考虑枚举全排列。所以我们就暴力枚举 $1$ 到 $N$，把这个当前排列记在一个数组里，$t[i]$ 表示在第一个图中点 $i$ 对应第二个图中点 $t[i]$，$q[i]$ 表示在第二个图中点 $i$ 对应第一个图中点 $q[i]$。然后，我们看第一个图中的边如果第二个图中没有就加上建边所需要的钱，第二个图中的边如果第一个图中没有就加上删边的钱，算出当前排列的答案。最后，我们把所有排列中计算的答案的最小值输出即可。
### 核心代码
```cpp
for (int i = 1; i <= n; i++)
	t[i] = i, q[i] = i; // t和q含义见思路部分
do
{
	LL sum = 0;
	for (int i = 1; i <= n; i++)
		q[t[i]] = i; // 计算q
	for (int i = 1; i <= m1; i++)
		if (!h[t[x[i]]][t[y[i]]])
			sum += a[t[x[i]]][t[y[i]]]; // 建一条边
	for (int i = 1; i <= m2; i++)
		if (!g[q[u[i]]][q[v[i]]])
			sum += a[u[i]][v[i]]; // 删一条边
	ans = min(ans, sum);
} while (next_permutation(t + 1, t + n + 1)); // 全排列
```
### 完整代码
```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;

int n, m1, m2;
int g[20][20]; // 第一个图（邻接矩阵）
int h[20][20]; // 第二个图（邻接矩阵）
int a[20][20]; // 含义见输入
int x[40], y[40]; // 第一个图中的边
int u[40], v[40]; // 第二个图中的边
int t[20], q[40]; // t和q，含义见思路
LL ans = 9e18; // 答案

int main()
{
	cin >> n >> m1;
	for (int i = 1; i <= m1; i++)
	{
		cin >> x[i] >> y[i];
		g[x[i]][y[i]] = 1; // 无向图
		g[y[i]][x[i]] = 1;
	}
	cin >> m2;
	for (int i = 1; i <= m2; i++)
	{
		cin >> u[i] >> v[i];
		h[u[i]][v[i]] = 1; // 无向图
		h[v[i]][u[i]] = 1;
	}
	for (int i = 1; i < n; i++)
		for (int j = i + 1; j <= n; j++)
		{
			cin >> a[i][j];
			a[j][i] = a[i][j]; // 对称
		}
	for (int i = 1; i <= n; i++)
		t[i] = i, q[i] = i;
	do
	{
		LL sum = 0;
		for (int i = 1; i <= n; i++)
			q[t[i]] = i;
		for (int i = 1; i <= m1; i++)
			if (!h[t[x[i]]][t[y[i]]])
				sum += a[t[x[i]]][t[y[i]]]; // 建边
		for (int i = 1; i <= m2; i++)
			if (!g[q[u[i]]][q[v[i]]])
				sum += a[u[i]][v[i]]; // 删边
		ans = min(ans, sum);
	} while (next_permutation(t + 1, t + n + 1)); // 全排列
	cout << ans << endl;
	return 0;
} 
```

---

## 作者：__int1024 (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc371_c)
# 思路
暴力枚举 $P$ 的全排列，算出每种排列所需的价值，取最小值即可。
# 代码
``` cpp
#include <bits/stdc++.h>
using namespace std;
#define debug cerr<<"The code runs successfully.\n";
#define endl '\n'
#define TRACE 1
#define tcout TRACE && cout
#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define int long long
constexpr int P = 998244353; 
constexpr int Base = 3221225477;
constexpr int INF = 0x3f3f3f3f3f3f3f3f; 
constexpr int N = 10, M = 2e6 + 10;
int n,m,k;
bool a[N][N],b[N][N];//邻接矩阵存图
int c[N][N];
signed main()
{
	fst;
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		int A,B;
		cin>>A>>B;
		a[A][B]=1;
		a[B][A]=1;
	}
	cin>>k;
	for(int i=1;i<=k;i++)
	{
		int A,B;
		cin>>A>>B;
		b[A][B]=1;
		b[B][A]=1;
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=i+1;j<=n;j++)
		{
			cin>>c[i][j];
			c[j][i]=c[i][j];
		}
	}
	int res=INF;//因为取最小值，所以赋值正无穷
	int p[n+1];
	for(int i=1;i<=n;i++)
	{
		p[i]=i;
	}
  //枚举全排列
	do
	{
		int ans=0;
		for(int i=1;i<=n;i++)
		{
			for(int j=i+1;j<=n;j++)
			{
				if(b[p[i]][p[j]]+a[i][j]==1)//需要增加或删除这条边
				{
					ans+=c[p[i]][p[j]];
				}
			}
		}
		res=min(res,ans);//取最小值
	}
	while(next_permutation(p+1,p+1+n));
	cout<<res;
	return 0;
}
```

---

## 作者：Malkin_Moonlight (赞：2)

# 题解：AT_abc371_c [ABC371C] Make Isomorphic

# 思路
给你两个图，求使图同构的最小花费，图没有重边和自环。

数据很小，直接暴搜。

用 `dfs`  生成图 的所有可能的顶点排列，计算每种排列的转换成本，并找出最小的成本即可。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define pb emplace_back
#define endl '\n'
const ll MAXN = 1e5 + 5;
const ll MOD = 1e9 + 7;
ll n, mg, mh ,u, v, ans = 1e18;
ll gm[14][14], hm[14][14];
ll a[14][14];
ll p[14],st[14];

void dfs(ll x) {
	if (x == n + 1) {
		ll res = 0;
		for (int i = 1; i <= n; i++) {
			for (int j = i + 1; j <= n; j++) {
				if (hm[p[i]][p[j]] != gm[i][j]) res+=a[p[i]][p[j]];
			}
		}     
		ans = min(ans, res);
		return ;      
	}
	for (int i = 1; i <= n; i++) {
		if (!st[i]) {
			st[i] = 1;
			p[x] = i;
			dfs(x + 1);
			st[i] = 0;
		}
	}
}

inline ll read() {
	ll x = 0, f = 1;char ch = getchar();
	while (ch < '0' || ch > '9') {if (ch == '-')f = -1;ch = getchar();}
	while (ch >= '0' && ch <= '9') {x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
	return x * f;
}
inline void write(ll x) {
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) write(x / 10);
	putchar((x % 10) | 0x30);
}

int main()
{
	cin >> n >> mg;
	for (int i = 1; i <= mg; i++) {
		cin >> u >> v;
		gm[u][v] = 1;
		gm[v][u] = 1;
	}
	cin >> mh;
	for (int i = 1; i <= mh; i++) {
		cin >> u >> v;
		hm[u][v] = 1;
		hm[v][u] = 1;
	}
	for (int i = 1; i <= n; i++) {
		for (int j = i + 1; j <= n; j++) {
			cin >> a[i][j];
			a[j][i] = a[i][j];
		}
	}
	dfs(1);	
	cout << ans;
	return 0;
}
```

---

## 作者：zhouzihang1 (赞：1)

# AT_abc371_c [ABC371C] Make Isomorphic 题解

## 思路

先解释一下同构：

给出两张图 $G$ 和 $H$，点数和边数分别相等，如果存在一种排列 $p$，使对于所有的 $1 \le i < j \le n$ 的 $i,j$，若 $G$ 的顶点 $i,j$ 之间有一条边，且 $H$ 的顶点 $p_i,p_j$ 之间**一定**有一条边。

$1 \le n \le 8$。

可以直接枚举 $p$，可以使用函数 `next_permutation(p.begin(),p.end())` 来找到下一个排列实现枚举。

然后根据 $p$ 暴力统计答案。

## Code

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N=10;
int n,a[N][N],m1,m2,p[]={0,1,2,3,4,5,6,7,8,9,10};
//p 是用来对 1-n 进行排列
int g[N][N],h[N][N];
//邻接矩阵存图会很方便
ll ans=0x3f3f3f3f3f3f3f3f;
int main()
{
	scanf("%d%d",&n,&m1);
	for(int i=1,u,v;i<=m1;i++)
	{
		scanf("%d%d",&u,&v);
		g[u][v]=g[v][u]=1;
	}
	scanf("%d",&m2);
	for(int i=1,u,v;i<=m2;i++)
	{
		scanf("%d%d",&u,&v);
		h[u][v]=h[v][u]=1;
	}
	for(int i=1;i<n;i++)
		for(int j=i+1;j<=n;j++)
			scanf("%d",&a[i][j]);
    //以上为输入
	do{
		ll res=0;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				if(i!=j)
					res+=a[i][j]*(g[p[i]][p[j]]!=h[i][j]);
                    //如果不一样的两个点就统计答案
                    //如果都有边或者都没有边就不算答案
		ans=min(ans,res);
	}while(next_permutation(p+1,p+n+1));//枚举全排列
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：Walrus (赞：1)

同构图的人话版定义是两张图在**忽视点的编号下**长得一样。

也就是编号与编号的映射关系可以不一定要一一对应，比如不一定要图 $G$ 的点 1 对应图 $H$ 的点 1，图 $G$ 的点 1 可以对应图 $H$ 的点 2。

加上 $N\leq 8$，不难想到直接全排来建立映射关系。

全排考虑 dfs，然后枚举图 $G$ 中的边和图 $H$ 中的边是不是一样的，最后对每种情况取 $\min$ 即可。

时间复杂度 $O(N^2 \times N!)$，当然可以枚举边的方式不同可以做到 $O(M \times N!)$，code 采用前者。


[code](https://atcoder.jp/contests/abc371/submissions/57768530)

---

## 作者：_xxxxx_ (赞：0)

### 题意

给两个图，只能在其中一个图中修改。修改包括连边删边，代价已知。求使得两个图同构的最小代价。

### 分析

图同构，只能爆搜，且观察到 $n \le 8$。

我们直接 $O(n!)$ 枚举全排列，这样使得每个点直接对应。对应起来后，我们枚举每两个点中是否连边，计算贡献即可。

时间复杂度 $O(n! \times n^2)$。

### 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int  N = 20 + 10;
int n;
int e1[15][15], e2[15][15];
int m1, m2;
int num[15];
bool vis[N];
int minn = 1e18;
int w[N][N];
void dfs(int u)
{
    if(u == n + 1)
    {
        int ans = 0;
        for(int i = 1; i <= n; i++)
        {
            for(int j = 1; j <= n; j++)
            {
                if(e1[i][j] != e2[num[i]][num[j]])
                {
                    ans += w[i][j];
                    // e1[num[i]][num[j]] = e1[num[j]][num[i]] = e2[i][j];
                }
            }
        }
        minn = min(minn, ans);
        //直接计算贡献
        return ;
    }
    for(int i = 1; i <= n; i++)
    {
        if(vis[i]) continue;
        vis[i] = 1;
        num[u] = i;
        dfs(u + 1);
        vis[i] = 0;
        num[u] = 0;
        //爆搜枚举全排列
    }
}
signed main()
{
    cin >> n;
    cin >> m2;
    for(int i = 1; i <= m2; i++)
    {
        int x, y;
        cin >> x >> y;
        e2[x][y] = e2[y][x] = 1;
    }
    cin >> m1;
    for(int i = 1; i <= m1; i++)
    {
        int x, y;
        cin >> x >> y;
        e1[x][y] = e1[y][x] = 1;
    }
    for(int i = 1; i < n; i++) for(int j = i + 1; j <= n; j++) cin >> w[i][j];
    dfs(1);
    cout << minn << endl;
    return 0;
}
```

---

## 作者：zdd6310 (赞：0)

# [ABC371C] Make Isomorphic
## Description
给你两个无向图 G 和 H。

在 H 中，$i$ 和 $j$ 之间的边若连上或删除，将有 $a_{i,j}$ 的代价。

求最小代价，使得 H 和 G 同构。
## solution
大家已经说完了，我就给一些注意事项给新手。

1. 枚举全排列可以用 $\operatorname{next\_permutation}$，比 dfs 好用。
2. 记得，是 H 改变了边，枚举排列时应该是 G 的点的排列。
3. 是先加起来再取最小。加起来使用临时变量，取最小使用全局变量。初始时应设为极大值。
4. 无向边，所以只需要对于每一个排列，枚举一半的边就行了。

---

## 作者：xiaoke2021 (赞：0)

数据很小，枚举 $n$ 的全排列，计算当前情况的花费，取最小值即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,mg,mh;
bool g[10+5][10+5],h[10+5][10+5];
int a[10+5][10+5];
long long ans=LONG_LONG_MAX;
int cnt[10+5];
int main(){
	cin>>n;
	cin>>mg;
	for(int i=1;i<=mg;i++){
		int a,b;
		cin>>a>>b;
		g[min(a,b)][max(a,b)]=true;
	}cin>>mh;
	for(int i=1;i<=mh;i++){
		int a,b;
		cin>>a>>b;
		h[min(a,b)][max(a,b)]=true;
	}
	for(int i=1;i<n;i++){
		for(int j=i+1;j<=n;j++){
			cin>>a[i][j];
		}
	}
	for(int i=1;i<=n;i++) cnt[i]=i;
	do{
		long long sum=0;
		for(int i=1;i<=n;i++)
			for(int j=i+1;j<=n;j++)
				if(g[i][j]^h[min(cnt[i],cnt[j])][max(cnt[i],cnt[j])])
					sum+=a[min(cnt[i],cnt[j])][max(cnt[i],cnt[j])];
		ans=min(ans,sum);
	}while(next_permutation(cnt+1,cnt+1+n));
	cout<<ans;
	return 0;
}

```

---

## 作者：hzxphy (赞：0)

赛场上没打出来，惨了。

## 题目大意
给定两个无向图，令为 $G$ 和 $H$。

将一次操作定义为 $(u,v)$，若图 $H$ 中没有这条边，则加入这条边，反之删除这条边。

问至少多少次操作可以同构。
## 思路
爆力枚举全排列即可，然后计算此时的代价，最后取最小值即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int h[10][10],g[10][10],a[10][10];
int mut[10];
int main(){
    cin>>n;
    int mg;cin>>mg;
    while(mg--){
        int u,v;cin>>u>>v;
        g[u][v]=g[v][u]=1;
    }cin>>mg;
    while(mg--){
        int u,v;cin>>u>>v;
        h[u][v]=h[v][u]=1;
    }
    for(int i=1;i<=n;i++)mut[i]=i;
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            cin>>a[i][j];a[j][i]=a[i][j];
        }
    }
    long long ans=1e9;
    do{
        long long tmp=0;
        for(int i=1;i<=n;i++){
            for(int j=i+1;j<=n;j++){
                if(g[i][j]!=h[mut[i]][mut[j]]){
                    tmp+=a[mut[i]][mut[j]];
                }
            }
        }
        ans=min(ans,tmp);
    }while(next_permutation(mut+1,mut+1+n));
    cout<<ans;
    return 0;
}

```

---

## 作者：Hacker_Cracker (赞：0)

## AT_abc371_c  Make Isomorphic 题解
### Solution
题意：在两个图中删去或添加一些边，求使得两个图同构的最小代价。具体地说，在顶点 $(i,j)(1 \le i<j \le N)$ 上添加或删去一条边，需要花费 $A_{i,j}$ 的代价。

至于图重构的定义，官网题面上已经描述地很清楚了：

>具有 $N$ 个顶点的两个图形 $G$ 和 $H$ 如果且仅当存在 $(1,2,\ldots,N)$ 的置换 $(P_1,P_2,\ldots,P_N)$ 使得每对 $1\le i\lt j\le N$， $G$ 的 $(i,j)$ 和 $H$ 的 $(P_i,P_j) $ 要么都存在边，要么都不存在。

又看到 $1 \le N \le 8$，所以很容易想到全排列暴力枚举。我们可以使用 STL 中的 next_permutation 函数代替完成。

### [AC](https://www.luogu.com.cn/record/177010546) Code
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
const int N=1<<4;
int a[N][N],G[N][N],H[N][N],f[N],n,mg,mh,u,v,ans=1e9;
int main(){
	cin>>n;
	cin>>mg;
	for(int i=1;i<=mg;i++){
		cin>>u>>v;
		G[u][v]=1;
		G[v][u]=1;
	}
	cin>>mh;
	for(int i=1;i<=mh;i++){
		cin>>u>>v;
		H[u][v]=1;
		H[v][u]=1;
	}
	for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            cin>>a[i][j];
            a[j][i]=a[i][j];
        }
    }
    for(int i=1;i<=n;i++) f[i]=i;
    do{
    	int tmp=0;
    	for(int i=1;i<=n;i++){
    		for(int j=i+1;j<=n;j++){
    			if(G[i][j]^H[f[i]][f[j]]){
    				tmp+=(f[i]<f[j]?a[f[i]][f[j]]:a[f[j]][f[i]]);
				}
			}
		}	
		ans=min(ans,tmp);
	}while(next_permutation(f+1,f+n+1));
	cout<<ans<<endl;
    return 0;
```
_撒花！_
###### 求过。。。

---

## 作者：BLuemoon_ (赞：0)

[link](https://www.luogu.com.cn/problem/AT_abc371_c)

## 思路

枚举全排列，对于每一个编号索引判断代价，时间复杂度 $O(n! \times n^2)$。

## 代码

```cpp
// BLuemoon_
#include <bits/stdc++.h>

using namespace std;
using LL = long long;
using DB = double;

const int kMaxN = 8 + 5;

int n, vis[kMaxN], f[kMaxN], mg, mh, a[kMaxN][kMaxN], e1[kMaxN][kMaxN], e2[kMaxN][kMaxN];
LL ans = 1e18;

void pr(bool pr) {
  cout << (pr ? "Yes" : "No") << '\n';
}
void DFS(int x, LL cnt = 0) {
  if (x > n) {
    for (int i = 1; i <= n; i++) {
      for (int j = i; j <= n; j++) {
        if (e1[f[i]][f[j]] != e2[i][j]) {
          cnt += a[i][j];
        }
      }
    }
    ans = min(ans, cnt);
    return;
  }
  for (int i = 1; i <= n; i++) {
    if (!vis[i]) {
      vis[i] = 1, f[x] = i, DFS(x + 1), vis[i] = 0;
    }
  }
}

int main() {
  cin >> n >> mg;
  for (int i = 1, u, v; i <= mg; i++) {
    cin >> u >> v, e1[u][v] = e1[v][u] = 1;
  }
  cin >> mh;
  for (int i = 1, u, v; i <= mh; i++) {
    cin >> u >> v, e2[u][v] = e2[v][u] = 1;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= n; j++) {
      cin >> a[i][j];
    }
  }
  DFS(1);
  cout << ans << '\n';
  return 0;
}
```

---

## 作者：Your_Name (赞：0)

## 题意
给两个图，求使图同构的最小花费，图没有重边和自环。

同构的定义为：当且仅当存在 $(1,2,\ldots,N)$ 的排列 $(P_1,P_2,\ldots,P_N)$ ，使得所有 $1\leq i\lt j\leq N$ 都满足当且仅当 $H$ 中的顶点 $P_i$ 和 $P_j$ 之间存在一条边时， $G$ 中的顶点 $i$ 和 $j$ 之间存在一条边。

## 思路

发现 $N \le 8$ 所以直接全排列 $P$ 数组，每次求花费，最后取最小值即可。

这里注意，同构的条件时“当且仅当”，是充要条件，因此，只要 $H$ 中的顶点 $P_i$ 和 $P_j$ 之间存在边的情况与 $G$ 中的顶点 $i$ 和 $j$ 之间不同时就要用花费把它加入或删除。

建议评橙。

## AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 11;
int G[N][N], H[N][N];//两个图
int mg, mh, n, ans = INT_MAX, a[N], w[N][N];
int main()
{
    cin >> n >> mg;
    for (int i = 1; i <= mg; i++)
    {
        int u, v;
        cin >> u >> v;
        G[u][v] = G[v][u] = 1;
    }
    cin >> mh;
    for (int i = 1; i <= mh; i++)
    {
        int a, b;
        cin >> a >> b;
        H[a][b] = H[b][a] = 1;
    }
    for (int i = 1; i <= n; i++)
    {
        a[i] = i;
    }//全排列初始化
    for (int i = 1; i < n; i++)
    {
        for (int j = i + 1; j <= n; j++)
        {
            cin >> w[i][j];
            w[j][i] = w[i][j];
        }
    }
    do
    {
        int res = 0;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if(i == j)continue;//没有自环
                if ((G[i][j] == 1 && H[a[i]][a[j]] == 0)){
                    res += w[a[i]][a[j]];
                }else if((G[i][j] == 0 && H[a[i]][a[j]] == 1)){
                    res += w[a[i]][a[j]];
                }//求出花费
            }
        }
        ans = min(ans, res);//取最小
    } while (next_permutation(a + 1, a + 1 + n));//全排列
    cout << ans / 2;//除二是因为在循环时每条边都被遍历了两次
    return 0;
}
```
 _完结撒花_

---

