# 题目信息

# Mishka and Interesting sum

## 题目描述

Little Mishka enjoys programming. Since her birthday has just passed, her friends decided to present her with array of non-negative integers $ a_{1},a_{2},...,a_{n} $ of $ n $ elements!

Mishka loved the array and she instantly decided to determine its beauty value, but she is too little and can't process large arrays. Right because of that she invited you to visit her and asked you to process $ m $ queries.

Each query is processed in the following way:

1. Two integers $ l $ and $ r $ ( $ 1<=l<=r<=n $ ) are specified — bounds of query segment.
2. Integers, presented in array segment $ [l,r] $ (in sequence of integers $ a_{l},a_{l+1},...,a_{r} $ ) even number of times, are written down.
3. XOR-sum of written down integers is calculated, and this value is the answer for a query. Formally, if integers written down in point 2 are $ x_{1},x_{2},...,x_{k} $ , then Mishka wants to know the value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF703D/7210428d91e1c7505cfe57a2df3abdc28a7ac76c.png), where ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF703D/4298d47c0191af3c0a3103f431751061bc7e2362.png) — operator of exclusive bitwise OR.

Since only the little bears know the definition of array beauty, all you are to do is to answer each of queries presented.

## 说明/提示

In the second sample:

There is no integers in the segment of the first query, presented even number of times in the segment — the answer is $ 0 $ .

In the second query there is only integer $ 3 $ is presented even number of times — the answer is $ 3 $ .

In the third query only integer $ 1 $ is written down — the answer is $ 1 $ .

In the fourth query all array elements are considered. Only $ 1 $ and $ 2 $ are presented there even number of times. The answer is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF703D/1f43581f72fc5ce3c0b862a8034cb76a29952125.png).

In the fifth query $ 1 $ and $ 3 $ are written down. The answer is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF703D/7a7518e2f6c019be104f1f3114e7d17043192b15.png).

## 样例 #1

### 输入

```
3
3 7 8
1
1 3
```

### 输出

```
0
```

## 样例 #2

### 输入

```
7
1 2 1 3 3 2 3
5
4 7
4 5
1 3
1 7
1 5
```

### 输出

```
0
3
1
3
2
```

# AI分析结果



## 唯一算法分类
离线处理 + 树状数组/线段树

---

## 综合分析与结论

### 核心思路与难点
1. **核心推导**：出现偶数次的数异或和 = 区间异或和 ^ 区间不同数的异或和  
   - 利用异或自反性（x^x=0），偶数次出现的数相互抵消，奇数次出现的数保留一次
   - 需维护两个关键值：区间异或和（前缀和）、区间不同数的异或和

2. **关键难点**：高效维护区间不同数的异或和  
   - 离线处理：按右端点排序查询，保证处理顺序的单调性
   - 数据结构：树状数组/线段树动态维护每个数最后一次出现的位置的贡献

3. **算法流程**  
   - 离散化处理（减少空间开销）
   - 预处理每个数上一次出现的位置（pre数组）
   - 离线处理查询时，每次将当前数的前一个位置贡献消除，更新当前位置贡献
   - 最终结果 = 前缀异或和 ^ 树状数组查询结果

---

## 题解清单（≥4星）

### 顾z（树状数组，5星）
**亮点**：  
- 清晰推导核心公式：`ans = (区间异或和) ^ (不同数异或和)`  
- 离散化处理优雅，代码结构紧凑  
- 树状数组操作高效，时间复杂度稳定 O(n log n)

### RuntimeErr（莫队+卡常，4星）
**亮点**：  
- 直接维护出现次数的奇偶性，逻辑直观  
- 优化块大小与奇偶排序提升效率  
- 提供离散化与卡常实践参考

### 灰鹤在此（线段树，4星）
**亮点**：  
- 线段树实现不同数异或和维护  
- 完整推导公式并解释离线排序必要性  
- 预处理pre数组的流程清晰易懂

---

## 最优思路与技巧

### 关键技巧
1. **离线排序**：按右端点升序处理查询，确保每个数仅保留最后出现位置的贡献  
   - 每次处理到位置i时，删除pre[i]的贡献，添加i的贡献

2. **异或抵消性应用**：  
   ```cpp
   if (++cnt[x] > 1) sum ^= x; // 偶数次触发异或
   if (--cnt[x] > 0) sum ^= x; // 奇数次撤销异或
   ```

3. **离散化优化**：  
   ```cpp
   sort(b+1, b+n+1);
   int len = unique(b+1, b+n+1) - b - 1;
   a[i] = lower_bound(b+1, b+len+1, a[i]) - b;
   ```

---

## 同类型题目与算法套路

### 通用解法
- **区间数颜色问题**：HH的项链（统计不同数个数）  
- **离线处理套路**：按右端点排序 + 树状数组维护最后出现位置  
- **异或性质应用**：奇偶次统计、自反性抵消

### 推荐题目
1. [P1972 HH的项链](https://www.luogu.com.cn/problem/P1972)  
2. [SP3267 DQUERY](https://www.luogu.com.cn/problem/SP3267)  
3. [CF1000F One Occurrence](https://codeforces.com/problemset/problem/1000/F)

---

## 可视化与算法演示

### 动画设计
1. **树状数组更新流程**  
   - **颜色标记**：  
     - 红色：当前处理的元素位置  
     - 黄色：该元素上一次出现的位置（pre[i]）  
   - **操作步骤**：  
     1. 高亮pre[i]并执行`add(pre[i], -val)`  
     2. 高亮i并执行`add(i, val)`  
     3. 显示树状数组的二进制结构变化

2. **复古像素风格**  
   - **Canvas绘制**：  
     - 数组元素用16x16像素块表示，颜色按值哈希  
     - 树状数组节点用绿色方块表示层级关系  
   - **音效设计**：  
     - 添加元素：8-bit "beep"音  
     - 删除元素：短促"pop"音  
     - 查询完成：胜利音效

3. **交互控制**  
   ```javascript
   // 伪代码示例
   class Visualizer {
     constructor(data) {
       this.tree = new BitwiseTree(data);
       this.speed = 1; // 动画速度
     }
     step() {
       this.highlight(currentPos);
       this.tree.update(prePos, -val);
       this.tree.update(currentPos, val);
       playSound('update');
     }
     autoPlay() {
       setInterval(() => this.step(), 1000 / this.speed);
     }
   }
   ```

---

## 核心代码实现

### 树状数组解法（顾z）
```cpp
const int N = 1e6+5;
int tr[N], pre[N], sum[N], a[N], b[N];

void add(int x, int val) {
    for (; x <= n; x += x&-x) tr[x] ^= val;
}

int query(int x) {
    int res = 0;
    for (; x; x -= x&-x) res ^= tr[x];
    return res;
}

int main() {
    // 离散化与预处理pre
    sort(q+1, q+m+1, [](auto &a, auto &b){ return a.r < b.r; });
    int now = 1;
    for (auto [l, r, id] : queries) {
        while (now <= r) {
            if (pre[now]) add(pre[now], b[a[now]]);
            add(now, b[a[now]]);
            now++;
        }
        ans[id] = query(r) ^ query(l-1) ^ sum[r] ^ sum[l-1];
    }
}
```

### 莫队解法（RuntimeErr）
```cpp
int ans, cnt[N], a[N], b[N];
void add(int x) {
    if (++cnt[a[x]] > 1) ans ^= b[a[x]];
}
void del(int x) {
    if (--cnt[a[x]] > 0) ans ^= b[a[x]];
}

// 主循环
sort(q, q+m, [](auto &a, auto &b) {
    return a.l/blk != b.l/blk ? a.l < b.l : (a.l/blk & 1 ? a.r < b.r : a.r > b.r);
});
int l=1, r=0;
for (auto [ql, qr, id] : q) {
    while (l > ql) add(--l);
    while (r < qr) add(++r);
    while (l < ql) del(l++);
    while (r > qr) del(r--);
    res[id] = ans;
}
```

---

## 个人心得摘录
> **顾z**：  
> "最初以为答案恒为0，直到发现题目要求的是单个数的异或和。通过推导发现公式，避免直接统计偶数次的复杂度陷阱。"

> **RuntimeErr**：  
> "莫队在大数据下的卡常需要精细调整块大小，离散化后改用小范围数组显著提升缓存命中率。"

> **灰鹤在此**：  
> "线段树的更新必须严格按右端点顺序，调试时发现pre数组未正确初始化导致贡献重复计算。"

---
处理用时：88.38秒