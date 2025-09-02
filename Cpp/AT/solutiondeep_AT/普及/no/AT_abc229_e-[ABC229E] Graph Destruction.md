# 题目信息

# [ABC229E] Graph Destruction

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc229/tasks/abc229_e

$ N $ 頂点 $ M $ 辺の単純な無向グラフが与えられます。  
 辺 $ i $ は、頂点 $ A_i $ と $ B_i $ を結んでいます。

頂点 $ 1,2,\ldots,N $ を順番に消していきます。  
 なお、頂点 $ i $ を消すとは、頂点 $ i $ と、頂点 $ i $ に接続する全ての辺をグラフから削除することです。

$ i=1,2,\ldots,N $ について、頂点 $ i $ まで消した時にグラフはいくつの連結成分に分かれていますか？

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 0\ \leq\ M\ \leq\ \min(\frac{N(N-1)}{2}\ ,\ 2\ \times\ 10^5\ ) $
- $ 1\ \leq\ A_i\ \lt\ B_i\ \leq\ N $
- $ i\ \neq\ j $ ならば $ (A_i,B_i)\ \neq\ (A_j,B_j) $
- 入力は全て整数である

### Sample Explanation 1

!\[\](https://img.atcoder.jp/ghi/3320212a9093132a80105bf02feeb195.png) グラフは上図のように変化していきます。

### Sample Explanation 2

はじめからグラフが非連結なこともあります。

## 样例 #1

### 输入

```
6 7

1 2

1 4

1 5

2 4

2 3

3 5

3 6```

### 输出

```
1

2

3

2

1

0```

## 样例 #2

### 输入

```
8 7

7 8

3 4

5 6

5 7

5 8

6 7

6 8```

### 输出

```
3

2

2

1

1

1

1

0```

# AI分析结果



# ABC229E Graph Destruction 题解

## 题目翻译
给定一个包含 $N$ 个顶点和 $M$ 条边的无向图。按顺序删除顶点 $1$ 到 $N$，每次删除顶点 $i$ 时，同时移除与 $i$ 相连的所有边。求每次删除前 $i$ 个顶点后剩余图的连通块数量。

**样例解释**：删除顶点 $1$ 至 $i$ 后，输出当前连通块数。例如样例1的输出序列依次表示删除顶点 $1$ 到 $6$ 后的连通块数。

## 算法分类
**并查集**

---

## 题解分析与关键思路

### 核心思路
采用逆向思维，将删除顶点转化为逐步添加顶点。通过倒序处理顶点，利用并查集维护连通块数量，避免直接处理动态删除的复杂性。

### 解决难点
1. **动态处理困难**：直接删除顶点难以高效维护连通性。
2. **时间效率**：正向操作复杂度高，逆向处理每条边仅访问一次。
3. **连通块统计**：每次添加顶点时，先增加连通块数，再合并邻接顶点减少计数。

### 最优题解总结
- **逆向操作**：从顶点 $N$ 到 $1$ 逐步添加，记录每个阶段的连通块数。
- **并查集优化**：合并时仅处理邻接顶点编号较大的边，确保每条边仅处理一次。
- **连通块统计**：初始时新增顶点作为独立块，合并成功则减少计数。

---

## 精选题解及代码

### 题解1：ikunTLE（⭐⭐⭐⭐⭐）
**关键亮点**：思路清晰，代码简洁，变量命名合理，处理逻辑明确。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
vector<int> vc[N], a;
int n, m, fa[N];

void _init(){ for(int i=1;i<=n;++i) fa[i]=i; }
int _find(int x){ return fa[x]==x ? x : fa[x]=_find(fa[x]); }

void _merge(int x, int y){
    int xx=_find(x), yy=_find(y);
    if(xx != yy) fa[xx] = yy;
}

int main(){
    cin >> n >> m;
    _init();
    while(m--){
        int u, v; cin >> u >> v;
        vc[u].push_back(v), vc[v].push_back(u);
    }
    int ans = 0;
    for(int i=n; i>=1; --i){
        a.push_back(ans++);
        for(int j : vc[i]){
            if(i < j && _find(i) != _find(j)){
                --ans;
                _merge(i, j);
            }
        }
    }
    reverse(a.begin(), a.end());
    for(int x : a) cout << x << '\n';
}
```

### 题解2：scp020（⭐⭐⭐⭐）
**关键亮点**：代码规范，包含快速读入优化，适用于大数据量。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=200005;
vector<int> e[maxn];
int ans[maxn], f[maxn];

int F(int x){ return x == f[x] ? x : f[x]=F(f[x]); }

int main(){
    int n, m; cin >> n >> m;
    for(int i=1; i<=m; ++i){
        int u, v; cin >> u >> v;
        e[u].push_back(v), e[v].push_back(u);
    }
    for(int i=1; i<=n; ++i) f[i] = i;
    int cnt = 0;
    for(int i=n; i>=1; --i){
        ans[i] = cnt++;
        for(int v : e[i]){
            if(v > i && F(i) != F(v)){
                f[F(v)] = F(i);
                --cnt;
            }
        }
    }
    for(int i=1; i<=n; ++i) cout << ans[i] << '\n';
}
```

---

## 关键技巧总结
1. **逆向处理**：将不可逆的删除操作转化为可逆的添加操作。
2. **边筛选优化**：仅处理邻接点编号较大的边，确保合并的正确性。
3. **连通块计数**：初始加顶点时增1，成功合并时减1，逻辑简明。

---

## 拓展练习
1. [P1197 星球大战](https://www.luogu.com.cn/problem/P1197)：类似动态删点求连通块。
2. [P3300 城市规划](https://www.luogu.com.cn/problem/P3300)：结合并查集处理动态连通性问题。
3. [P3225 矿场搭建](https://www.luogu.com.cn/problem/P3225)：连通块分析与构造方案结合。

---
处理用时：123.52秒