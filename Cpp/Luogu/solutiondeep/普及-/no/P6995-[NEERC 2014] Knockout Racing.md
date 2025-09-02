# 题目信息

# [NEERC 2014] Knockout Racing

## 题目描述



The races became more popular than ever at Pandora planet. But these races are quite unusual. There are $n$ cars participating in a race on the long straight track. Each car moves with a speed of $1$ meter per second. Track has coordinates in meters.

The car number $i$ moves between two points on the track with coordinates $a_{i}$ and $b_{i}$ starting at the second $0$ in the point $a_{i}.$ The car moves from $a_{i}$ to $b_{i},$ then from $b_{i}$ to $a_{i},$ then from $a_{i}$ to $b_{i}$ again, and so on.

Handsome Mike wants to knock some cars out of the race using dynamite. Thus he has $m$ questions. The question number $j$ is: what is the number of cars in the coordinates between $x_{j}$ and $y_{j}$ inclusive after $t_{j}$ seconds from the start?

Your task is to answer Mike's questions.



## 说明/提示

Time limit: 1 s, Memory limit: 256 MB. 



## 样例 #1

### 输入

```
5 5
0 1
0 2
2 3
3 5
4 5
0 5 0
0 1 2
0 2 1
2 5 2
2 5 3
```

### 输出

```
5
1
2
4
3
```

# AI分析结果

### 算法分类
模拟

### 综合分析与结论
本题的核心是通过模拟每辆车在给定时间后的位置，判断其是否在指定区间内。由于题目中 $n$ 和 $m$ 的范围都较小（$1 \le n, m \le 1000$），因此直接使用 $O(nm)$ 的暴力模拟即可通过。所有题解都采用了类似的思路，即通过计算每辆车在给定时间后的位置，并判断其是否在询问的区间内。不同题解的主要区别在于代码的实现细节和可读性。

### 所选题解
1. **作者：mycbxzd (赞：1)**
   - **星级：4星**
   - **关键亮点**：代码简洁，逻辑清晰，直接通过计算车辆的位置并判断是否在区间内，使用了 `if-else` 结构来区分车辆的往返方向。
   - **核心代码**：
     ```cpp
     if ((t / (b[j] - a[j])) % 2 == 1) {
         l = b[j] - t % (b[j] - a[j]);
     } else {
         l = a[j] + t % (b[j] - a[j]);
     }
     if (l >= x && l <= y) ans++;
     ```

2. **作者：koukilee (赞：1)**
   - **星级：4星**
   - **关键亮点**：代码结构清晰，使用了 `len` 变量来简化计算，通过 `if-else` 结构判断车辆的往返方向，代码可读性较高。
   - **核心代码**：
     ```cpp
     if ((t / len) & 1) {
         now = r[i] - t % len;
     } else {
         now = l[i] + t % len;
     }
     if (now >= x && now <= y) ans++;
     ```

3. **作者：Daniel_xu (赞：0)**
   - **星级：4星**
   - **关键亮点**：代码简洁，使用了 `get_pos` 函数来封装车辆位置的计算逻辑，提高了代码的可读性和复用性。
   - **核心代码**：
     ```cpp
     int get_pos(int i, int t) {
         int len = a[i][1] - a[i][0];
         if (t / len & 1) {
             return a[i][1] - t % len;
         } else {
             return a[i][0] + t % len;
         }
     }
     ```

### 最优关键思路或技巧
1. **位置计算**：通过 `t / (b[j] - a[j])` 判断车辆的往返方向，然后根据 `t % (b[j] - a[j])` 计算车辆的具体位置。
2. **代码封装**：将车辆位置的计算逻辑封装成函数，提高代码的可读性和复用性。

### 可拓展之处
类似的问题可以通过模拟或数学计算来解决，尤其是在涉及到周期性运动或区间判断的场景中。可以进一步优化时间复杂度，例如通过预处理或使用更高效的数据结构来加速查询。

### 推荐题目
1. [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)
2. [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)
3. [P1056 排座椅](https://www.luogu.com.cn/problem/P1056)

---
处理用时：23.93秒