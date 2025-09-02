# 题目信息

# [ABC366C] Balls and Bag Query

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc366/tasks/abc366_c

空の袋があります。 クエリが $ Q $ 個与えられるので、順番に処理してください。

クエリは次の $ 3 $ 種類です。

- `1 x` : 整数 $ x $ が書かれたボールを $ 1 $ つ袋に入れる。
- `2 x` : 整数 $ x $ が書かれたボールを $ 1 $ つ袋の中から取り出して外に捨てる。このクエリが与えられるとき、袋の中に整数 $ x $ が書かれたボールが存在することが保証される。
- `3` : 袋の中にあるボールに書かれている整数の種類数を出力する。

## 说明/提示

### 制約

- $ 1\ \leq\ Q\ \leq\ 2\ \times\ 10^{5} $
- $ 1\ \leq\ x\ \leq\ 10^{6} $
- $ 2 $ 種類目のクエリが与えられるとき、袋の中に整数 $ x $ が書かれたボールが存在する。
- $ 3 $ 種類目のクエリが $ 1 $ つ以上存在する。
- 入力はすべて整数
 
### Sample Explanation 1

はじめ、袋の中は空です。 $ 1 $ 番目のクエリ `1 3` で袋の中に $ 3 $ が書かれたボールが $ 1 $ つ入ります。 $ 2 $ 番目のクエリ `1 1` で袋の中に $ 1 $ が書かれたボールが $ 1 $ つ入ります。 $ 3 $ 番目のクエリ `1 4` で袋の中に $ 4 $ が書かれたボールが $ 1 $ つ入ります。 $ 4 $ 番目のクエリ `3` で袋の中に $ 1,\ 3,\ 4 $ の $ 3 $ 種類のボールが入っているため、$ 3 $ を出力します。 $ 5 $ 番目のクエリ `2 1` で袋の中から $ 1 $ が書かれたボールを $ 1 $ つ取り出します。 $ 6 $ 番目のクエリ `3` で袋の中に $ 3,\ 4 $ の $ 2 $ 種類のボールが入っているため、$ 2 $ を出力します。 $ 7 $ 番目のクエリ `1 5` で袋の中に $ 5 $ が書かれたボールが $ 1 $ つ入ります。 $ 8 $ 番目のクエリ `3` で袋の中に $ 3,\ 4,\ 5 $ の $ 3 $ 種類のボールが入っているため、$ 3 $ を出力します。

## 样例 #1

### 输入

```
8

1 3

1 1

1 4

3

2 1

3

1 5

3```

### 输出

```
3

2

3```

## 样例 #2

### 输入

```
8

1 2

1 2

3

2 2

1 4

1 4

2 2

3```

### 输出

```
1

1```

# AI分析结果



# ABC366C Balls and Bag Query 题解分析

## 算法分类
**数据结构应用**

---

## 题解思路与核心难点

### 核心思路
所有题解的核心逻辑都是通过维护每个数字的出现次数，并动态计算当前存在的不同数字种类数。主要分为两种实现方式：
1. **桶数组**：直接开一个大小为 1e6 的数组，通过计数器增减判断种类数变化
2. **哈希表/集合**：用 `unordered_map` 或 `set` 自动管理键值对，通过容器大小获取种类数

### 解决难点对比
| 方法                | 数据结构        | 时间复杂度 | 空间复杂度 | 解决难点                                                                 |
|---------------------|-----------------|------------|------------|--------------------------------------------------------------------------|
| 桶数组（最优）      | 数组            | O(1)       | O(1e6)     | 需处理超大数组预分配，但无需动态扩容                                      |
| unordered_map       | 哈希表          | O(1)       | O(k)       | 需手动删除计数归零的键值对，否则 `.size()` 不准确                        |
| set                 | 红黑树          | O(logk)    | O(k)       | 插入删除时自动维护唯一性，但操作复杂度较高                                |
| 线段树/平衡树       | 树结构          | O(logn)    | O(n)       | 过度设计，仅用于演示可扩展性                                             |

---

## 题解评分（≥4星）

### 五星题解
1. **jiangruibo**（数组桶）  
   ✅ 亮点：  
   - 使用预分配数组实现 O(1) 操作  
   - 维护独立计数器 `cnt` 避免遍历  
   ⭐ 评分：5（代码简洁，时空最优）

2. **2c_s**（数组桶）  
   ✅ 亮点：  
   - 代码精简，使用 `tom[x]++` 与 `!tom[x]--` 简化逻辑  
   ⭐ 评分：4.5（与五星解法等价但注释较少）

3. **ma_niu_bi**（数组桶）  
   ✅ 亮点：  
   - 完整包含输入输出处理，适合竞赛模板  
   ⭐ 评分：4（逻辑清晰但变量命名可优化）

---

## 最优思路提炼
**桶数组 + 独立计数器**  
1. 预分配数组 `cnt[x]` 记录每个数的出现次数  
2. 维护独立变量 `ans` 表示当前种类数  
3. 添加时：若 `cnt[x]` 从 0→1，`ans++`  
4. 删除时：若 `cnt[x]` 从 1→0，`ans--`  

```cpp
int cnt[1e6+5], ans;
void add(int x) {
    if (++cnt[x] == 1) ans++;
}
void remove(int x) {
    if (--cnt[x] == 0) ans--;
}
```

---

## 同类题目
1. [LeetCode 1915 - 最美子字符串数](https://leetcode-cn.com/problems/number-of-wonderful-substrings/)  
   （维护字符奇偶性状态）
2. [洛谷 P1177 - 统计数字](https://www.luogu.com.cn/problem/P1177)  
   （桶排序思想）
3. [CodeForces 1520D - Same Differences](https://codeforces.com/problemset/problem/1520/D)  
   （统计满足条件的数对）

---

## 可视化设计

### 核心算法演示
```javascript
// 伪代码示例
class Visualization {
    constructor() {
        this.buckets = new Array(10); // 示例仅显示前10个桶
        this.ans = 0;
    }

    add(x) {
        if (this.buckets[x] === 0) this.ans++;
        this.buckets[x]++;
        playSound('add'); // 添加音效
        highlightBucket(x, 'green'); // 高亮新增桶
    }

    remove(x) {
        if (this.buckets[x] === 1) this.ans--;
        this.buckets[x]--;
        playSound('remove'); // 删除音效
        highlightBucket(x, 'red'); // 高亮移除桶
    }
}
```

### 复古像素风格实现
1. **视觉设计**  
   - 8-bit 像素风格，使用 16 色调色板  
   - 每个数字对应 32x32 像素方块，颜色随操作变化（添加→绿色闪烁，删除→红色闪烁）  
   - 顶部显示当前 `ans` 值（大型像素数字）

2. **交互功能**  
   - **AI 自动模式**：随机生成操作序列演示  
   - **步进控制**：空格暂停/继续，方向键单步执行  
   - **音效系统**：  
     - 添加操作：8-bit "blip" 音效（[Web Audio API](https://developer.mozilla.org/en-US/docs/Web/API/Web_Audio_API)）  
     - 删除操作：低音 "boom" 音效  
     - 查询操作：清脆 "coin" 音效

3. **Canvas 渲染**  
```javascript
// 绘制桶的伪代码
function drawBucket(ctx, x, count) {
    const pxX = x * 32 % canvas.width;
    const pxY = Math.floor(x * 32 / canvas.width) * 32;
    
    // 绘制底色
    ctx.fillStyle = count > 0 ? '#88FF88' : '#444444';
    ctx.fillRect(pxX, pxY, 32, 32);
    
    // 绘制计数
    ctx.fillStyle = '#000000';
    ctx.font = '8px "Press Start 2P"';
    ctx.fillText(count, pxX + 2, pxY + 10);
}
```

---

## 代码实现（最优解法）
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_X = 1e6 + 5;
int cnt[MAX_X], ans;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int Q; cin >> Q;
    while (Q--) {
        int op, x;
        cin >> op;
        if (op == 1) {
            cin >> x;
            if (cnt[x]++ == 0) ans++;
        } else if (op == 2) {
            cin >> x;
            if (--cnt[x] == 0) ans--;
        } else {
            cout << ans << '\n';
        }
    }
    return 0;
}
```

---

## 个人心得摘录
> **HeYilin 的调试经验**  
> “使用 `map` 时发现 `.size()` 包含已归零的键值对，必须手动 `erase`。改用 `unordered_map` 后速度提升 3 倍”

> **TemplateClass 的扩展思考**  
> “若 x 范围扩大到 1e9，离散化预处理可保持算法效率，体现了桶思想的灵活性”

---
处理用时：88.38秒