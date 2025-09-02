# [NOISG 2020 Qualification] Firefighting

## 题目背景

在 Mouseopolis，这座鼠国的大都会，一场大火席卷了整座城市。为了防止类似灾难再次发生，鼠国的国王 Squeaky 决定在鼠国的城镇中建立消防站。

## 题目描述

鼠国由 $N$ 个城镇组成，编号为 $1$ 到 $N$。城镇之间通过 $N-1$ 条双向道路连接，每条道路连接两个城镇，并且道路的长度可能不同。城镇网络保证任何两个城镇之间都可以通过某些道路相连。

为了有效扑灭火灾，国王的顾问认为消防站到火灾发生地点的距离不得超过 $K$ 公里，否则火势将难以控制。然而，建设消防站的成本较高，国王希望尽可能减少消防站的数量。

任务是确定在鼠国的哪些城镇建设消防站，以使得需要建设的消防站数量最少。

## 说明/提示

【样例解释】

对于样例 #1，最少需要在城镇 $1, 8, 3, 6$ 建立消防站，以保证每个城镇到最近的消防站的距离不超过 $4$ 公里。

对于样例 #2，最少需要在城镇 $5, 6, 2, 3$ 建立消防站。

对于样例 #3，必须在每个城镇建立消防站。

对于样例 #4，可以在城镇 $4$ 和 $10$ 建立消防站，或者选择其他符合条件的方案。

【数据范围】

- $1 \leq N \leq 3 \times 10^5$  
- $1 \leq K \leq 10^{15}$  
- $1 \leq A_i, B_i \leq N$  
- $1 \leq D_i \leq 10^9$

| 子任务编号 | 分值       | 限制条件                      |
|:--------:|:---------:|:--------------------------:|
| $1$      | $3$       | $K \leq 20$，且 $D_i \geq 30$ |
| $2$      | $5$       | $N \leq 17, K \leq 17$，且 $D_i = 1$ |
| $3$      | $9$       | $N \leq 17, K \leq 10^6$，且 $D_i \leq 10^4$ |
| $4$      | $19$      | $K \leq 30$，且 $D_i \geq 20$ |
| $5$      | $26$      | $N \leq 3 \times 10^3$     |
| $6$      | $38$      | 无额外限制                 |

## 样例 #1

### 输入

```
9 4
1 2 10
2 3 4
8 9 4
8 7 3
7 3 5
3 4 1
4 5 3
5 6 2```

### 输出

```
4
1 8 3 6```

## 样例 #2

### 输入

```
9 26
2 1 21
2 9 21
2 8 21
2 3 56
3 4 37
4 5 29
7 6 25
6 4 24```

### 输出

```
4
5 6 2 3```

## 样例 #3

### 输入

```
3 18
1 2 35
2 3 49```

### 输出

```
3
1 2 3```

## 样例 #4

### 输入

```
10 3
10 9 1
9 8 1
8 5 1
1 2 1
2 3 1
5 4 1
3 4 1
5 6 1
6 7 1```

### 输出

```
2
4 10```

# 题解

## 作者：Error_Eric (赞：1)

### Statement

给定一棵树，边有边权。选出最少的关键节点建消防站，使得每个节点到最近的消防站的距离不大于 $K$。

### Sol（greedy，dp）

注意到这道题就是有边权的，不用二分答案的，需要输出方案的 [P3523](https://www.luogu.com.cn/problem/solution/P3523)。

具体地，我们有一个贪心思路，就是在能够满足子树中最深的节点能够被覆盖的情况下，将消防站建在尽量靠近根节点，也就是更浅的位置。

但是这样子暴力做是 $O(n^2)$ 的，我们可以用 dp 进行优化。具体地，用 $f_i$ 维护子树内最浅的消防站（若无，可以视作在无穷远处有一个消防站）的深度，$g_i$ 维护子树内最深的坏节点（目前没有被消防站保护的节点）的深度。转移直接对儿子求 min/max 就可以。

如果我们发现最深的坏节点 $g_i$ 可以被另一颗子树的消防站保护，那么子树 $i$ 内所有的坏节点一定可以被保护。这是我们可以直接删除 $g_i$。

如果我们发现最深的坏节点 $g_i$ 到达当前节点 $i$ 的父亲的距离大于 $K$ 了（或者 $i$ 是根节点，但是仍然有坏节点没有被保护），我们就无法把保护这个坏节点的责任推给父亲，因此当前节点必须建立消防站。

如果这两种情况都没有发生，就什么都不做。

然后就做完了。

### Code

```cpp
#include<iostream>
#include<algorithm>
#include<vector>
#include<numeric>
using namespace std;
const int _= 3.1e5;
#define CMP(X) [&](int cu, int cv){return X;}
int n, ui, vi, fa[_];
long long dep[_], f[_], g[_], k, di; //警钟敲烂
vector<pair<int, int> > e[_];
vector<int> ans, ord;

void dfs(int o){
    for(auto eg : e[o]) if(eg.first != fa[o]){
        dep[eg.first] = dep[o] + eg.second;
        fa[eg.first] = o;
        dfs(eg.first);
    }
}

signed main(){
    ios::sync_with_stdio(0),
    cin.tie(0), cout.tie(0);
    cin >> n >> k;
    ord.resize(n), iota(ord.begin(), ord.end(), 1);
    for(int i = 1; i < n; i++){
        cin >> ui >> vi >> di;
        e[ui].push_back(make_pair(vi, di));
        e[vi].push_back(make_pair(ui, di));
    }
    dep[1] = 0, fa[1] = 1, dfs(1);
    sort(ord.begin(), ord.end(), CMP(dep[cu] > dep[cv]));
    for(int o: ord){
        f[o] = 2e18, g[o] = dep[o]; // 注意这里直接维护深度
        for(auto ex : e[o]) if(ex.first != fa[o]){
            if(f[ex.first] < f[o]) f[o] = f[ex.first];
            if(g[ex.first] > g[o]) g[o] = g[ex.first];
        }
        if(g[o] + f[o] - 2 * dep[o] <= k) g[o] = -1e17;
        else if(g[o] - dep[fa[o]] > k || (o == 1 && g[o] >= 0) ) 
            f[o] = dep[o], g[o] = -1e17, ans.push_back(o);
    }
    cout << ans.size() << endl;
    for(int&ax : ans){
        cout << ax << " ";
    }
}
```

---

