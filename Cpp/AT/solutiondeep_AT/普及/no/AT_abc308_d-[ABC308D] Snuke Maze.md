# 题目信息

# [ABC308D] Snuke Maze

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc308/tasks/abc308_d

$ H $ 行 $ W $ 列のグリッドがあります。 以下、上から $ i $ 行目、左から $ j $ 列目のマスを $ (i,j) $ と表記します。 グリッドの各マスには英小文字が書かれており、$ (i,j) $ に書かれた文字は与えられる文字列 $ S_i $ の $ j $ 文字目と一致します。

すぬけくんは、辺で隣接するマスに移動することを繰り返して $ (1,1) $ から $ (H,W) $ まで移動しようと思っています。 訪れるマス （最初の $ (1,1) $ と 最後の $ (H,W) $ を含む）に書かれた文字が、 訪れる順に `s` $ \rightarrow $ `n` $ \rightarrow $ `u` $ \rightarrow $ `k` $ \rightarrow $ `e` $ \rightarrow $ `s` $ \rightarrow $ `n` $ \rightarrow\ \dots $ となるような経路が存在するか判定してください。 なお、$ 2 $ つのマス $ (i_1,j_1),(i_2,j_2) $ は $ |i_1-i_2|+|j_1-j_2|\ =\ 1 $ を満たすとき、またそのときに限り「辺で隣接する」といいます。

より厳密には、マスの列 $ ((i_1,j_1),(i_2,j_2),\dots,(i_k,j_k)) $ であって以下の条件を全て満たすものが存在するか判定してください。

- $ (i_1,j_1)\ =\ (1,1),(i_k,j_k)\ =\ (H,W) $
- すべての $ t\ (1\ \leq\ t\ <\ k) $ について、$ (i_t,j_t) $ と $ (i_{t+1},j_{t+1}) $ は辺で隣接する
- すべての $ t\ (1\ \leq\ t\ \leq\ k) $ について、$ (i_t,j_t) $ に書かれた文字は `snuke` の $ ((t-1)\ \bmod\ 5)\ +\ 1 $ 文字目と一致する

## 说明/提示

### 制約

- $ 2\leq\ H,W\ \leq\ 500 $
- $ H,W $ は整数
- $ S_i $ は英小文字からなる長さ $ W $ の文字列
 
### Sample Explanation 1

$ (1,1)\ \rightarrow\ (1,2)\ \rightarrow\ (2,2)\ \rightarrow\ (2,3) $ という経路は、訪れたマスに書かれた文字が訪れた順に `s` $ \rightarrow $ `n` $ \rightarrow $ `u` $ \rightarrow $ `k` となるため条件を満たします。

## 样例 #1

### 输入

```
2 3

sns

euk```

### 输出

```
Yes```

## 样例 #2

### 输入

```
2 2

ab

cd```

### 输出

```
No```

## 样例 #3

### 输入

```
5 7

skunsek

nukesnu

ukeseku

nsnnesn

uekukku```

### 输出

```
Yes```

# AI分析结果



# [ABC308D] Snuke 迷宫

## 题目描述

给定一个 $H$ 行 $W$ 列的网格，每个格子中写有一个英文字母。要求判断是否存在从 $(1,1)$ 到 $(H,W)$ 的路径，使得经过的字符序列严格按 "snuke" 循环排列（即 s→n→u→k→e→s→n→... 依此类推）。相邻移动仅限于上下左右四个方向。

### 输入格式
- 第一行输入 $H$ 和 $W$
- 接下来 $H$ 行每行一个长度为 $W$ 的字符串表示网格

### 输出格式
- 存在合法路径输出 "Yes"，否则输出 "No"

### 样例解释
样例1的有效路径是：(1,1)→(1,2)→(2,2)→(2,3)，对应字符序列 s→n→u→k

---

**算法分类**: 广度优先搜索 BFS

---

## 题解分析与结论

### 最优解法关键思路
采用 **BFS 状态扩展**，维护三维状态 `(x, y, t)`，其中 `t` 表示当前处于 "snuke" 循环中的第几个字符（模5后的值）。使用三维数组记录访问状态，避免重复路径的无效搜索。

### 评分较高题解

#### 题解作者：Elairin176（4星）
**核心亮点**：
1. 正确设计 BFS 状态，包含坐标和循环周期状态
2. 使用模运算处理循环序列
3. 初始化时处理起点字符的合法性检查

**关键代码**：
```cpp
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};
string s = "snuke";

bool vis[505][505][5]; // 三维状态标记数组

bool bfs() {
    if (grid[0][0] != 's') return false;
    queue<tuple<int, int, int>> q;
    q.push({0, 0, 0});
    vis[0][0][0] = true;
    
    while (!q.empty()) {
        auto [x, y, t] = q.front(); q.pop();
        if (x == H-1 && y == W-1) return true;
        
        int nt = (t + 1) % 5;
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx >= 0 && ny >= 0 && nx < H && ny < W) {
                if (!vis[nx][ny][nt] && grid[nx][ny] == s[nt]) {
                    vis[nx][ny][nt] = true;
                    q.push({nx, ny, nt});
                }
            }
        }
    }
    return false;
}
```

### 拓展思路
类似需要 **状态扩展** 的路径问题常见变式：
1. 带有周期性状态（如时间循环、方向循环）
2. 携带物品状态的迷宫问题（如钥匙-门类题目）
3. 需要记录路径特征的搜索（如特定步数奇偶性）

---

## 推荐习题
1. [P1141 01迷宫](https://www.luogu.com.cn/problem/P1141) - 连通块状态记忆
2. [P1443 马的遍历](https://www.luogu.com.cn/problem/P1443) - BFS最短路径基础
3. [ABC184D](https://atcoder.jp/contests/abc184/tasks/abc184_d) - 三维状态概率搜索

---
处理用时：47.98秒