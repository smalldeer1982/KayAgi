# 题目信息

# [ABC377C] Avoid Knight Attack

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc377/tasks/abc377_c

縦 $ N $ マス、横 $ N $ マスの $ N\ ^\ 2 $ マスからなるマス目があります。 上から $ i $ 行目 $ (1\leq\ i\leq\ N) $ 、左から $ j $ 列目 $ (1\leq\ j\leq\ N) $ のマスをマス $ (i,j) $ と呼ぶことにします。

それぞれのマスは、空マスであるかコマが置かれているかのどちらかです。 マス目には合計で $ M $ 個のコマが置かれており、$ k $ 番目 $ (1\leq\ k\leq\ M) $ のコマはマス $ (a\ _\ k,b\ _\ k) $ に置かれています。

あなたは、すでに置かれている**どのコマにも取られないように**、いずれかの**空マス**に自分のコマを置きたいです。

マス $ (i,j) $ に置かれているコマは、次のどれかの条件を満たすコマを取ることができます。

- マス $ (i+2,j+1) $ に置かれている
- マス $ (i+1,j+2) $ に置かれている
- マス $ (i-1,j+2) $ に置かれている
- マス $ (i-2,j+1) $ に置かれている
- マス $ (i-2,j-1) $ に置かれている
- マス $ (i-1,j-2) $ に置かれている
- マス $ (i+1,j-2) $ に置かれている
- マス $ (i+2,j-1) $ に置かれている

ただし、存在しないマスについての条件は常に満たされないものとします。

たとえば、マス $ (4,4) $ に置かれているコマは、以下の図で青く示されたマスに置かれているコマを取ることができます。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_abc377_c/399e5a909392dc44071791350bba40d75968dfd7.png)

あなたがコマを置くことができるマスがいくつあるか求めてください。

## 说明/提示

### 制約

- $ 1\leq\ N\leq10\ ^\ 9 $
- $ 1\leq\ M\leq2\times10\ ^\ 5 $
- $ 1\leq\ a\ _\ k\leq\ N,1\leq\ b\ _\ k\leq\ N\ (1\leq\ k\leq\ M) $
- $ (a\ _\ k,b\ _\ k)\neq(a\ _\ l,b\ _\ l)\ (1\leq\ k\lt\ l\leq\ M) $
- 入力はすべて整数

### Sample Explanation 1

すでに置かれているコマは、以下の図で青く示されたマスに置かれたコマを取ることができます。 ![](https://img.atcoder.jp/abc377/cb70c753c18ba20c291ba79e76f34599.png) よって、あなたがすでに置かれているコマに取られないように自分のコマを置くことができるマスは残りの $ 38 $ マスです。

### Sample Explanation 2

$ 10\ ^\ {18} $ マスのうち、置くことができないマスはマス $ (1,1),(2,3),(3,2) $ の $ 3 $ マスのみです。 答えが $ 2\ ^\ {32} $ 以上になる場合があることに注意してください。

## 样例 #1

### 输入

```
8 6
1 4
2 1
3 8
4 5
5 2
8 3```

### 输出

```
38```

## 样例 #2

### 输入

```
1000000000 1
1 1```

### 输出

```
999999999999999997```

## 样例 #3

### 输入

```
20 10
1 4
7 11
7 15
8 10
11 6
12 5
13 1
15 2
20 10
20 15```

### 输出

```
338```

# AI分析结果



### 唯一算法分类
**坐标标记与集合去重**

---

### 综合分析与结论

#### 核心思路与难点
题目要求统计所有不被任何马攻击且未被占据的空位置。由于棋盘极大（N ≤ 1e9），需通过稀疏存储标记不可用位置（被攻击或已被占据）。各题解的共同思路为：
1. **标记被攻击位置**：每个马攻击周围8个方向的位置。
2. **标记原有马的位置**：这些位置直接不可用。
3. **去重与合并**：使用高效数据结构（如 `map` 或 `set`）合并两类不可用位置，统计总数。

**难点**在于：
- **坐标越界处理**：需确保仅处理棋盘内的坐标。
- **高效存储与去重**：需在 O(M) 或 O(M log M) 时间内处理最多 1.8e6 个坐标。

#### 算法流程可视化设计
1. **初始化棋盘**：用网格表示棋盘，初始为空。
2. **处理每个马**：遍历每个马的位置，将其自身标记为红色（已占据），周围8个方向标记为黄色（被攻击）。
3. **去重合并**：动态更新集合，显示当前被标记的位置总数。
4. **结果展示**：最终棋盘高亮所有不可用位置，计算剩余可用位置数。

**交互设计**：
- **步进执行**：按空格键逐步处理每个马的攻击范围。
- **颜色区分**：红色表示原有马的位置，黄色表示被攻击位置。
- **数据统计面板**：实时显示已标记的不可用位置数和剩余可用位置数。

---

### 题解清单（≥4星）

1. **cyx012113 的题解（★★★★★）**
   - **亮点**：简洁高效，利用 `map<pair<int,int>, bool>` 直接合并所有不可用位置，代码仅需 20 行。
   - **关键代码**：
     ```cpp
     map<pair<int, int>, bool> a;
     for (每个马的位置 (x, y)) {
         a[{x, y}] = 1; // 标记马的位置
         for (8方向偏移) {
             if (坐标合法) a[{xx, yy}] = 1; // 标记被攻击位置
         }
     }
     ans = n * n - a.size();
     ```

2. **FlowerAccepted 的题解（★★★★）**
   - **亮点**：使用两个 `set` 分别存储马的位置和被攻击位置，逻辑清晰。
   - **关键代码**：
     ```cpp
     set<pair<int, int>> knights, capture;
     for (每个马的位置 (x, y)) {
         knights.insert({x, y});
         for (8方向偏移) {
             if (坐标合法 && 不在 knights 中) capture.insert({xx, yy});
         }
     }
     ans = n * n - knights.size() - capture.size();
     ```

3. **Hacker_Cracker 的题解（★★★★）**
   - **亮点**：代码简洁，直接使用 `set` 合并所有不可用位置。
   - **关键代码**：
     ```cpp
     set<pair<int, int>> s;
     for (每个马的位置 (x, y)) {
         s.insert({x, y}); // 标记马的位置
         for (8方向偏移) {
             if (坐标合法) s.insert({xx, yy}); // 标记被攻击位置
         }
     }
     ans = n * n - s.size();
     ```

---

### 最优思路与技巧

#### 核心思路
- **合并去重**：将原有马的位置和被攻击位置统一存储，避免重复计算。
- **高效数据结构**：使用 `set` 或 `map` 自动去重，保证 O(M log M) 时间复杂度。

#### 实现技巧
- **坐标偏移表**：预定义8个方向的偏移量，简化遍历逻辑。
- **越界检查**：在处理每个坐标前，检查是否在棋盘范围内。
- **类型处理**：使用 `long long` 防止整数溢出。

---

### 同类型题目推荐

1. **[洛谷 P1036 选数](https://www.luogu.com.cn/problem/P1036)**  
   - **相似点**：需处理组合问题，利用集合去重。

2. **[洛谷 P1582 倒水](https://www.luogu.com.cn/problem/P1582)**  
   - **相似点**：位运算与状态标记，稀疏数据处理。

3. **[LeetCode 1220. 统计元音字母序列的数目](https://leetcode.cn/problems/count-vowels-permutation/)**  
   - **相似点**：状态转移与动态规划，高效处理大范围状态。

---

### 代码实现（核心逻辑）

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int dx[] = {2, 1, -1, -2, -2, -1, 1, 2};
int dy[] = {1, 2, 2, 1, -1, -2, -2, -1};

signed main() {
    int n, m;
    cin >> n >> m;
    set<pair<int, int>> blocked;
    
    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        blocked.insert({x, y});
        for (int j = 0; j < 8; ++j) {
            int nx = x + dx[j], ny = y + dy[j];
            if (nx >= 1 && nx <= n && ny >= 1 && ny <= n) {
                blocked.insert({nx, ny});
            }
        }
    }
    
    cout << n * n - blocked.size() << endl;
    return 0;
}
```

---

### 可视化与游戏化设计（伪代码）

```javascript
// Canvas 初始化
const canvas = document.getElementById('board');
const ctx = canvas.getContext('2d');
const CELL_SIZE = 10; // 像素风格

// 颜色定义
const COLORS = { EMPTY: '#FFF', KNIGHT: '#F00', ATTACK: '#FF0' };

// 动画控制
let currentHorse = 0;
let horses = [/* 马的坐标列表 */];
let blocked = new Set();

function draw() {
    // 清空画布
    ctx.fillStyle = COLORS.EMPTY;
    ctx.fillRect(0, 0, canvas.width, canvas.height);
    
    // 绘制被攻击位置
    blocked.forEach(pos => {
        ctx.fillStyle = COLORS.ATTACK;
        ctx.fillRect(pos.x * CELL_SIZE, pos.y * CELL_SIZE, CELL_SIZE, CELL_SIZE);
    });
    
    // 绘制马的位置
    horses.forEach(([x, y]) => {
        ctx.fillStyle = COLORS.KNIGHT;
        ctx.fillRect(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE);
    });
}

function step() {
    if (currentHorse >= horses.length) return;
    const [x, y] = horses[currentHorse];
    
    // 标记当前马的位置
    blocked.add(`${x},${y}`);
    
    // 标记攻击范围
    for (let d of directions) {
        const nx = x + d[0], ny = y + d[1];
        if (nx >= 1 && nx <= n && ny >= 1 && ny <= n) {
            blocked.add(`${nx},${ny}`);
        }
    }
    
    currentHorse++;
    draw();
}

// 绑定键盘事件
document.addEventListener('keydown', (e) => {
    if (e.code === 'Space') step();
});
```

---

### 总结

本题通过集合去重高效处理稀疏坐标，核心在于合并不可用位置。可视化设计通过像素风格和步进执行直观展示算法流程，适合教学与调试。

---
处理用时：449.62秒