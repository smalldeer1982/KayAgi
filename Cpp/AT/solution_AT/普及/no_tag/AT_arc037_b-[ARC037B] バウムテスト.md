# [ARC037B] バウムテスト

## 题目描述

给出由 $N$ 个顶点和 $M$ 条边构成的无向图表。求出该图表中的像树一样的部分，即不具有闭路的部分的个数。

## 说明/提示

($ 2 $ $ ≦ $ $ N $ $ ≦ $ $ 100 $) 

($ 1 $ $ ≦ $ $ M $ $ ≦ $ $ N×(N-1)/2 $)

($ 1 $ $ ≦ $ $ i $ $ ≦ $ $ M $)

($ 1 $ $ ≦ $ $ u_i $ $ ＜ $ $ v_i $ $ ≦ $ $ N $) 

值得注意的是：对于任何两个顶点，直接连接它们的边最多只有一条。

## 样例 #1

### 输入

```
8 7
1 2
2 3
2 4
5 6
6 7
6 8
7 8```

### 输出

```
1```

## 样例 #2

### 输入

```
5 1
1 2```

### 输出

```
4```

## 样例 #3

### 输入

```
11 11
1 2
1 3
2 4
3 5
4 6
5 7
6 8
7 9
8 10
9 11
10 11```

### 输出

```
0```

# 题解

## 作者：_QyGyQ_ (赞：0)

遍历每一个点，并从每一个未遍历点开始遍历。遍历时记录经过的边数和点数，遍历后判断所走路程是否为一棵树。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
using ll=long long;
const int N=1e6+7;
vector<int>G[N];
int ans,point,edge;
bool vis[N];
void dfs(int u){
	edge+=(G[u].size());
	point++;
	vis[u]=true;
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		if(vis[v]==true) continue;
		dfs(v);
	}
}
signed main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int x,y;
		cin>>x>>y;
		G[x].push_back(y);
		G[y].push_back(x);
	}
	for(int i=1;i<=n;i++){
		if(vis[i]) continue;
		point=0,edge=0;
		dfs(i);
		if(point-1==edge/2) ans++;
	}
	cout<<ans<<"\n";
	return 0;
}
```


---

## 作者：yhx0322 (赞：0)

## Description
给出由 $N$ 个顶点和 $M$ 条边构成的无向图。求出该图中的像树一样的部分。

## Solution
**考虑树的性质：没有回路。**

所以，可以直接从没有被访问过的节点开始 DFS，记录两个变量 $x$ 和 $y$，分别表示当前联通块遍历到点的个数，和每个点出边的总数。

最后只需要判断 `x - 1` 是否等于 `y >> 1` 即可。

## Code
```cpp
#include <bits/stdc++.h>

using namespace std;
const int N = 100005;


vector<int> to[N];

int x, y;
bool used[N];
void dfs(int v) {
    used[v] = true;
    x++; y += (int)to[v].size();
    for(int u : to[v]) {
        if (used[u]) continue;
        dfs(u);
    }
}

int main() {
    int n, m;
    scanf("%d%d",&n,&m);
    for (int i = 1; i <= m; i++) {
        int a, b;
        scanf("%d%d",&a, &b);
        a--; b--;
        to[a].push_back(b);
        to[b].push_back(a);
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (used[i]) continue;
        x = y = 0;
        dfs(i);
        if (x - 1 == (y >> 1)) ans++;
    }
    cout << ans << endl;
    return 0;
}
```

---

