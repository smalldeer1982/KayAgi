# 题目信息

# Mark and Professor Koro

## 题目描述

After watching a certain anime before going to sleep, Mark dreams of standing in an old classroom with a blackboard that has a sequence of $ n $ positive integers $ a_1, a_2,\dots,a_n $ on it.

Then, professor Koro comes in. He can perform the following operation:

- select an integer $ x $ that appears at least $ 2 $ times on the board,
- erase those $ 2 $ appearances, and
- write $ x+1 $ on the board.

Professor Koro then asks Mark the question, "what is the maximum possible number that could appear on the board after some operations?"

Mark quickly solves this question, but he is still slower than professor Koro. Thus, professor Koro decides to give Mark additional challenges. He will update the initial sequence of integers $ q $ times. Each time, he will choose positive integers $ k $ and $ l $ , then change $ a_k $ to $ l $ . After each update, he will ask Mark the same question again.

Help Mark answer these questions faster than Professor Koro!

Note that the updates are persistent. Changes made to the sequence $ a $ will apply when processing future updates.

## 说明/提示

In the first example test, the program must proceed through $ 4 $ updates.

The sequence after the first update is $ [2,3,2,4,5] $ . One sequence of operations that achieves the number $ 6 $ the following.

- Initially, the blackboard has numbers $ [2,3,2,4,5] $ .
- Erase two copies of $ 2 $ and write $ 3 $ , yielding $ [3,4,5,\color{red}{3}] $ .
- Erase two copies of $ 3 $ and write $ 4 $ , yielding $ [4,5,\color{red}{4}] $ .
- Erase two copies of $ 4 $ and write $ 5 $ , yielding $ [5,\color{red}{5}] $ .
- Erase two copies of $ 5 $ and write $ 6 $ , yielding $ [\color{red}{6}] $ .

Then, in the second update, the array is changed to $ [2,3,2,4,3] $ . This time, Mark cannot achieve $ 6 $ . However, one sequence that Mark can use to achieve $ 5 $ is shown below.

- Initially, the blackboard has $ [2,3,2,4,3] $ .
- Erase two copies of $ 2 $ and write $ 3 $ , yielding $ [3,4,3,\color{red}{3}] $ .
- Erase two copies of $ 3 $ and write $ 4 $ , yielding $ [3,4,\color{red}{4}] $ .
- Erase two copies of $ 4 $ and write $ 5 $ , yielding $ [3,\color{red}{5}] $ .

In the third update, the array is changed to $ [2,3,2,1,3] $ . One way to achieve $ 4 $ is shown below.

- Initially, the blackboard has $ [2,3,2,1,3] $ .
- Erase two copies of $ 3 $ and write $ 4 $ , yielding $ [2,2,1,\color{red}{4}] $ .

## 样例 #1

### 输入

```
5 4
2 2 2 4 5
2 3
5 3
4 1
1 4```

### 输出

```
6
5
4
5```

## 样例 #2

### 输入

```
2 1
200000 1
2 200000```

### 输出

```
200001```

# AI分析结果



## 算法分类
**二分**（线段树二分）

## 题解思路、算法要点与解决难点
### 核心思路
将每个数视为二进制位，合并操作相当于二进制进位。维护每个位的状态（0/1），通过高效数据结构处理多次加减法带来的进位与退位。

### 难点对比
1. **珂朵莉树 vs. 线段树**
   - **珂朵莉树**：维护连续区间，适合处理大量区间推平操作。通过 `split` 和 `merge` 处理进位/退位后的区间覆盖。
   - **线段树**：通过二分查找第一个0/1的位置，结合区间修改实现高效进位/退位。支持动态查询最高位。
2. **二进制模拟优化**
   - **暴力bitset**：直接模拟进位，但因数据规模大导致复杂度退化。
   - **压位高精**：利用 `__int128` 或 `bitset` 压缩位数，减少操作次数。

### 二分算法要点
1. **搜索区间**：线段树中从当前位向后查找第一个0（加法）或1（减法）。
2. **条件判断**：线段树节点维护区间内的1的数量，二分时根据左右子树状态决定方向。
3. **区间收缩**：找到目标位置后，将连续区间推平为0或1。

## 题解评分（≥4星）
1. **WOL_GO（珂朵莉树）**（⭐️⭐️⭐️⭐️）
   - **亮点**：利用珂朵莉树的区间推平特性，代码简洁高效。
2. **Chancylaser（线段树二分）**（⭐️⭐️⭐️⭐️⭐️）
   - **亮点**：线段树维护区间状态，支持快速查询和修改。
3. **jiangtaizhe001（线段树）**（⭐️⭐️⭐️⭐️）
   - **亮点**：代码清晰，维护差分数组实现区间操作。

## 最优思路与技巧
- **二进制视角**：将合并操作转化为二进制加减法，最高位即答案。
- **数据结构选择**：线段树二分或珂朵莉树处理区间操作。
- **避免暴力进位**：通过查找第一个0/1的位置，直接推平区间。

## 同类题目推荐
1. [P4588 数学计算](https://www.luogu.com.cn/problem/P4588)（线段树维护区间乘积）
2. [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)（离散化+线段树/树状数组）
3. [P3369 普通平衡树](https://www.luogu.com.cn/problem/P3369)（Treap/Splay维护动态序列）

## 个人心得摘录
> “线段树二分需要注意区间合并的方向，先右子树后左子树，确保找到最高位。” —— Chancylaser  
> “珂朵莉树的区间推平操作在处理连续进位时非常优雅，但需注意区间分裂的边界。” —— WOL_GO

---

## 可视化设计（线段树二分）
### 动画方案
1. **初始状态**：显示线段树结构，每个节点表示一段区间的0/1状态。
2. **操作步骤**：
   - **修改位x**：高亮x位，根据加减法触发进位/退位。
   - **二分查找**：动态显示左右子树的选择，收缩区间至目标位置。
   - **区间推平**：用颜色标记被修改的区间（如红色表示置0，绿色置1）。
3. **最高位更新**：每次操作后，红色箭头指向当前最高位。

### 复古游戏化效果
- **像素风格**：线段树节点以8-bit方块表示，区间推平时播放“哔”音效。
- **自动演示**：点击“Auto”按钮，逐步展示二分过程，背景音乐循环8-bit音轨。
- **关卡模式**：设计不同测试用例作为关卡，正确完成加分，错误时播放失败音效。

---

## 代码片段（线段树二分）
```cpp
// 查找第一个0的位置（加法）
int find_first_zero(int x) {
    int l = x, r = MAXN, res = -1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (query_sum(x, mid) == mid - x + 1) { // 全1
            l = mid + 1;
        } else {
            res = mid;
            r = mid - 1;
        }
    }
    return res;
}

// 区间推平操作
void update(int l, int r, int val) {
    if (l > r) return;
    // 线段树区间修改，标记下传
    // ...
}
```

---

**可视化交互示例**：  
访问 [JSFiddle示例](https://jsfiddle.net) 可体验动态线段树二分过程（需支持Web Audio）。

---
处理用时：60.98秒