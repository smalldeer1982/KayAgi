# 题目信息

# [ABC176E] Bomber

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc176/tasks/abc176_e

$ H\ \times\ W $ マスの二次元グリッドがあります。この中には $ M $ 個の爆破対象があります。 $ i $ 個目の爆破対象の位置は $ \left(h_i,\ w_i\ \right) $です。

高橋君は $ 1 $ つのマスを選び、そのマスに爆弾を設置し、起爆します。爆弾と同じ行または同じ列に存在する爆破対象が爆破されます。爆破対象が存在するマスに爆弾を設置することも出来ます。

高橋君は、爆破する爆破対象の数を最大化しようとしています。最大でいくつの爆破対象を爆破出来るか答えてください。

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\ \leq\ H,\ W\ \leq\ 3\ \times\ 10^5 $
- $ 1\ \leq\ M\ \leq\ \min\left(H\times\ W,\ 3\ \times\ 10^5\right) $
- $ 1\ \leq\ h_i\ \leq\ H $
- $ 1\ \leq\ w_i\ \leq\ W $
- $ \left(h_i,\ w_i\right)\ \neq\ \left(h_j,\ w_j\right)\ \left(i\ \neq\ j\right) $

### Sample Explanation 1

爆弾を $ \left(1,\ 2\right) $ に設置することで、全ての爆破対象を爆破することが出来ます。

## 样例 #1

### 输入

```
2 3 3

2 2

1 1

1 3```

### 输出

```
3```

## 样例 #2

### 输入

```
3 3 4

3 3

3 1

1 1

1 2```

### 输出

```
3```

## 样例 #3

### 输入

```
5 5 10

2 5

4 3

2 3

5 5

2 2

5 4

5 3

5 1

3 5

1 4```

### 输出

```
6```

# AI分析结果



### 中文题目重写

#### 题目描述

有一个 $H \times W$ 的二维网格，其中有 $M$ 个爆破目标。第 $i$ 个目标的位置为 $(h_i, w_i)$。你需要选择一个位置放置炸弹，使得与炸弹同行或同列的所有目标被摧毁。求最多能摧毁多少目标。

#### 输入约束

- $1 \leq H, W \leq 3 \times 10^5$
- $1 \leq M \leq \min(H \times W, 3 \times 10^5)$
- 目标位置互不相同

#### 样例

**输入样例1**  
```
2 3 3
2 2
1 1
1 3
```
**输出样例1**  
```
3
```
（炸弹放在 (1,2) 可摧毁所有目标）

---

### 算法分类
**贪心**

---

### 题解对比与结论

#### 核心思路
所有题解均采用以下步骤：
1. **统计行/列目标数**：计算每行和每列的目标数量。
2. **寻找最大值**：找到目标最多的行（记为 `max_row`）和列（记为 `max_col`）。
3. **检查交叉点**：遍历所有属于 `max_row` 的行和 `max_col` 的列的交叉点，若存在一个交叉点没有目标，则答案为 `max_row + max_col`；否则答案为 `max_row + max_col - 1`。

#### 解决难点
- **重复计数处理**：若炸弹位置本身有目标，该目标会被行和列各计数一次，需判断是否需要减 1。
- **高效遍历**：通过存储所有可能的最大行和列，仅遍历这些交叉点，避免全网格遍历。

#### 最优技巧
- **哈希表快速查询**：使用 `map` 或 `unordered_map` 快速判断交叉点是否存在目标。
- **剪枝优化**：只要找到一个无目标的交叉点即可终止遍历。

---

### 精选题解

#### 题解1：chl090410（4星）
**亮点**  
- 代码简洁，变量命名清晰。
- 使用 `map<pair<int,int>,int>` 存储目标位置。
```cpp
int main() {
    // ... 输入统计行/列目标数
    // 找出所有 max_row 和 max_col 的行列
    for (遍历所有 max_row 和 max_col 交叉点) {
        if (交叉点无目标) {
            cout << max_row + max_col;
            return 0;
        }
    }
    cout << max_row + max_col - 1;
}
```

#### 题解2：PineappleSummer（4星）
**亮点**  
- 详细时间复杂度分析，证明最坏情况为 $O(M)$。
- 使用 `vector` 存储候选行/列，逻辑清晰。
```cpp
// 统计候选行列后：
for (auto row : max_rows) {
    for (auto col : max_cols) {
        if (!mp[row][col]) {
            cout << max_row + max_col;
            exit(0);
        }
    }
}
cout << max_row + max_col - 1;
```

#### 题解3：linjinkun（4星）
**亮点**  
- 特别强调输入变量顺序（如 `h` 和 `w` 易混淆）。
- 代码注释详细，适合新手理解。
```cpp
// 核心检查逻辑：
for (遍历候选行) {
    for (遍历候选列) {
        if (该位置不在目标集合中) {
            q = 0; // 无需减1
            break;
        }
    }
}
printf("%d", max_row + max_col - q);
```

---

### 关键代码实现
```cpp
// 核心逻辑：统计行/列目标数 + 交叉点检查
int H, W, M;
cin >> H >> W >> M;
map<pair<int, int>, int> bomb_map; // 存储目标位置
vector<int> row_cnt(H+1), col_cnt(W+1);

for (int i=0; i<M; ++i) {
    int h, w;
    cin >> h >> w;
    row_cnt[h]++;
    col_cnt[w]++;
    bomb_map[{h, w}] = 1;
}

int max_row = *max_element(row_cnt.begin(), row_cnt.end());
int max_col = *max_element(col_cnt.begin(), col_cnt.end());

vector<int> max_rows, max_cols;
for (int i=1; i<=H; ++i)
    if (row_cnt[i] == max_row) max_rows.push_back(i);
for (int i=1; i<=W; ++i)
    if (col_cnt[i] == max_col) max_cols.push_back(i);

bool has_empty = false;
for (auto r : max_rows) {
    for (auto c : max_cols) {
        if (!bomb_map.count({r, c})) {
            has_empty = true;
            break;
        }
    }
    if (has_empty) break;
}

cout << max_row + max_col - (has_empty ? 0 : 1);
```

---

### 拓展与心得
**同类问题**  
- 二维网格行/列覆盖问题（如 [CF1008B](https://codeforces.com/problemset/problem/1008/B)）。
- 最大覆盖统计（如统计广告牌最大可见区域）。

**推荐题目**  
1. [P3406 海底高铁](https://www.luogu.com.cn/problem/P3406)（差分+贪心）
2. [P1719 最大加权矩形](https://www.luogu.com.cn/problem/P1719)（二维前缀和+贪心）
3. [CF1132B Discounts](https://codeforces.com/problemset/problem/1132/B)（排序+贪心）

**心得总结**  
- **变量命名**：注意区分行和列的变量（如 `h` 和 `w` 容易混淆）。
- **边界检查**：遍历候选行列时确保索引从 1 开始。
- **剪枝**：发现可行解后立即退出循环，避免冗余计算。

---
处理用时：65.73秒