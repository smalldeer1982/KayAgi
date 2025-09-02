# 题目信息

# Perfect Pair

## 题目描述

Let us call a pair of integer numbers  $ m $ -perfect, if at least one number in the pair is greater than or equal to $ m $ . Thus, the pairs (3, 3) and (0, 2) are 2-perfect while the pair (-1, 1) is not.

Two integers $ x $ , $ y $ are written on the blackboard. It is allowed to erase one of them and replace it with the sum of the numbers, $ (x+y) $ .

What is the minimum number of such operations one has to perform in order to make the given pair of integers $ m $ -perfect?

## 说明/提示

In the first sample the following sequence of operations is suitable: (1, 2) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF317A/355fee5161a1808ee95ea5dc6d815d4071657131.png) (3, 2) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF317A/355fee5161a1808ee95ea5dc6d815d4071657131.png) (5, 2).

In the second sample: (-1, 4) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF317A/355fee5161a1808ee95ea5dc6d815d4071657131.png) (3, 4) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF317A/355fee5161a1808ee95ea5dc6d815d4071657131.png) (7, 4) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF317A/355fee5161a1808ee95ea5dc6d815d4071657131.png) (11, 4) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF317A/355fee5161a1808ee95ea5dc6d815d4071657131.png) (15, 4).

Finally, in the third sample $ x $ , $ y $ cannot be made positive, hence there is no proper sequence of operations.

## 样例 #1

### 输入

```
1 2 5
```

### 输出

```
2
```

## 样例 #2

### 输入

```
-1 4 15
```

### 输出

```
4
```

## 样例 #3

### 输入

```
0 -1 5
```

### 输出

```
-1
```

# AI分析结果



# Perfect Pair

## 题目描述

我们称一对整数为 $m$-perfect，当且仅当这对数中至少有一个数大于或等于 $m$。例如，(3, 3) 和 (0, 2) 是 2-perfect，而 (-1, 1) 不是。

黑板上初始有两个整数 $x$ 和 $y$。允许执行以下操作：擦去其中一个数，并用它们的和替换。求使这对数成为 $m$-perfect 所需的最小操作次数。

## 说明/提示

样例 1 的操作序列：(1, 2) → (3, 2) → (5, 2)。  
样例 2 的操作序列：(-1, 4) → (3, 4) → (7, 4) → (11, 4) → (15, 4)。  
样例 3 中无法通过操作使两数满足条件。

---

**算法分类**：数学、贪心

---

### 题解分析与结论

1. **核心思路**：  
   - 特判初始条件：若已有数 ≥m，直接返回 0；若两数均 ≤0 且 <m，返回 -1。
   - **数学优化负数处理**：当存在负数时，通过除法快速计算将其变为非负数，避免逐个操作导致超时。
   - **贪心策略**：两数均为正后，每次将较小数替换为和，以最快增大数值。

2. **关键优化点**：  
   - 用数学公式 `k = (-x)/y` 快速计算负数变非负的操作次数，大幅减少循环次数。

---

### 优质题解推荐

#### 题解作者：Ggsddu_zzy（★★★★☆）
**亮点**：  
- 精确处理负数变非负的数学计算，代码清晰。
- 通过取模运算处理余数，结合循环完善最终结果。

**核心代码**：
```cpp
void maxx(ll x,ll y,ll m){
    if(x>=m||y>=m){ cout<<0; exit(0); }
    if(x<=0&&y<=0){ cout<<-1; exit(0); }
    if(x<0){
        ans += (-x)/y;
        x += y*((-x)/y);
    } 
    if(y<0){
        ans += (-y)/x;
        y += x*((-y)/x);
    }
    while(x<m && y<m){
        if(x<y) x+=y;
        else y+=x;
        ans++;
    }
}
```

---

#### 题解作者：hanyuchen2019（★★★★☆）
**亮点**：  
- 明确区分正负数处理阶段，代码结构清晰。
- 使用取模运算优化负数处理，避免逐次累加。

**核心代码**：
```cpp
if(x*y<0){
    if(x<y){
        ans += (-x)/y;
        x = x%y;
    } else {
        ans += (-y)/x;
        y = y%x;
    }
}
while(max(x,y)<m){
    if(x<y) x+=y;
    else y+=x;
    ans++;
}
```

---

### 关键技巧总结
1. **数学优化**：对负数使用除法快速计算操作次数，时间复杂度从 O(N) 降为 O(1)。
2. **贪心选择**：始终操作较小数以加速增长，符合贪心最优性原理。
3. **边界处理**：特判初始条件和全负数情况，避免无效计算。

---

### 拓展练习
1. [P1258 小车问题](https://www.luogu.com.cn/problem/P1258)（数学推导优化）
2. [P1031 均分纸牌](https://www.luogu.com.cn/problem/P1031)（贪心策略）
3. [P5837 Milk Pumping](https://www.luogu.com.cn/problem/P5837)（贪心与数学结合）

---
处理用时：159.33秒