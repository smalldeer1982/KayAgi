# 题目信息

# Two Buttons

## 题目描述

Vasya has found a strange device. On the front panel of a device there are: a red button, a blue button and a display showing some positive integer. After clicking the red button, device multiplies the displayed number by two. After clicking the blue button, device subtracts one from the number on the display. If at some point the number stops being positive, the device breaks down. The display can show arbitrarily large numbers. Initially, the display shows number $ n $ .

Bob wants to get number $ m $ on the display. What minimum number of clicks he has to make in order to achieve this result?

## 说明/提示

In the first example you need to push the blue button once, and then push the red button once.

In the second example, doubling the number is unnecessary, so we need to push the blue button nine times.

## 样例 #1

### 输入

```
4 6
```

### 输出

```
2
```

## 样例 #2

### 输入

```
10 1
```

### 输出

```
9
```

# AI分析结果



### 题目内容
# 两个按钮

## 题目描述

瓦夏发现了一个奇怪的设备。设备前面板有一个红色按钮、一个蓝色按钮和一个显示正整数的屏幕。点击红色按钮会使显示的数字乘以二，点击蓝色按钮会使数字减一。若数字变为非正数时设备会损坏。屏幕可以显示任意大的数字。初始时显示数字 $n$。

鲍勃想要让屏幕显示数字 $m$。他最少需要点击多少次按钮才能实现？

## 说明/提示

第一个样例需要先按蓝按钮再按红按钮  
第二个样例只需连续按九次蓝按钮

### 样例 #1
输入：4 6 → 输出：2  
样例 #2  
输入：10 1 → 输出：9

---

### 算法分类
**贪心**（逆向思维）或 **BFS**（正向搜索）

---

### 题解综合分析
本题核心在于逆向思维转换：当 $m > n$ 时，正向操作难以确定何时减1，但逆向将 $m$ 转换为 $n$ 时，可以通过判断奇偶性快速确定最优路径。主要解法分为两类：

1. **BFS**：标准解法，但数据范围较大时可能超时  
2. **逆向贪心**：时间复杂度 $O(\log m)$，适用于大数据

---

### 精选题解（评分≥4★）

#### 1. JRzyh 的逆向贪心（5★）
**关键亮点**：  
- 逆向操作将问题转化为 $m \to n$ 的路径优化  
- 奇偶性判断直接决定操作类型  
- 代码简洁高效（仅需15行）

**代码核心**：
```cpp
int ans = 0;
while(m != n) {
    if(m % 2 == 0 && m >= n) m /= 2;
    else m++;
    ans++;
}
```
**实现思路**：  
当 $m$ 为偶数且大于 $n$ 时除以2，否则通过加1调整奇偶性，最后补足 $n - m$ 的差值。

#### 2. cold_cold 的贪心优化（4★）
**关键亮点**：  
- 整合逆向操作与最终差值计算  
- 处理边界条件更严谨

**代码片段**：
```cpp
while(n < m) {
    if(m % 2) m++;
    else m /= 2;
    all++;
}
cout << all + n - m;
```

#### 3. Soshine_溯闪 BFS（4★）
**关键亮点**：  
- 标准BFS模板清晰  
- 使用vis数组记录步数避免重复访问

**实现技巧**：  
```cpp
vis[n] = 0; // 初始化起点
while(!q.empty()) {
    int front = q.front();
    if(front == m) return vis[front];
    // 处理两种操作
}
```

---

### 最优思路总结
**逆向贪心法**是最优解：  
1. 当 $m < n$ 时直接返回 $n - m$  
2. 逆向处理时，若 $m$ 是偶数且 $m > n$ 则除2，否则加1  
3. 最终补足剩余差值 $n - m$

**关键技巧**：  
- 将乘法操作转换为逆向的除法  
- 通过奇偶性判断减少无效操作  
- 时间复杂度从 $O(2^k)$ 降为 $O(\log m)$

---

### 同类型题目推荐
1. [P1135 奇怪的电梯](https://www.luogu.com.cn/problem/P1135)（BFS经典）  
2. [P1588 丢失的牛](https://www.luogu.com.cn/problem/P1588)（BFS+剪枝）  
3. [CF985B Switches and Lamps](https://www.luogu.com.cn/problem/CF985B)（逆向思维）

---

### 题解心得摘录
- **Soshine_溯闪**："五年级学生，学编程两年，点赞是鼓励" → 体现坚持学习  
- **洛白の纸**："无脑dp多做几次就过了" → 反映暴力方法的实用性  
- **infinities**："惊讶地发现模拟代码比搜索快" → 强调算法选择的重要性

---
处理用时：57.82秒