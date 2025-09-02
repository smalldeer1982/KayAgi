# 题目信息

# [USACO10FEB] Chocolate Eating S

## 题目描述

Bessie has received N (1 <= N <= 50,000) chocolates from the bulls, but doesn't want to eat them too quickly, so she wants to plan out her chocolate eating schedule for the next D (1 <= D <= 50,000) days in order to maximize her minimum happiness level over the set of those days.

Bessie's happiness level is an integer that starts at 0 and halves (rounding down if necessary) over night as she sleeps. However, when she eats chocolate i, her happiness level increases by integer H\_i (1 <= H\_i <= 1,000,000). If she eats chocolates on a day, her happiness for that day is considered the happiness level after she eats the chocolates. Bessie insists that she eat the chocolates in the order that she received them.

If more than one optimal solution exists, print any one of them.

Consider a sequence of 5 chocolates to be eaten over a period of 5 days; they respectively bring happiness (10, 40, 13, 22, 7).

If Bessie eats the first chocolate (10 happiness) on the first day and then waits to eat the others, her happiness level is 10 after the first day.

Here is the complete schedule which turns out to maximize her minimum happiness:

Day  Wakeup happiness   Happiness from eating   Bedtime happiness 1            0                10+40                  50

2           25                 ---                   25

3           12                  13                   25

4           12                  22                   34

5           17                   7                   24

The minimum bedtime happiness is 24, which turns out to be the best Bessie can do.

Bessie 拿到了 $N$（$1 \leq N \leq 5\times 10 ^ 4$）块巧克力。她决定想个办法吃掉这些巧克力，使得它在吃巧克力的这段时间里，最不开心的一天尽可能的开心。并且一共吃 $D$（$1 \leq D \leq 5\times 10 ^ 4$）天。

每块巧克力有一个开心值 $H_i$（$1 \leq H_i \leq 10 ^ 6$），当某天你吃下那块巧克力时，你将获得那块巧克力的开心值。每一天的开心值是所有当天吃掉的巧克力的总开心值之和。每天晚上 Bessie 睡觉之后，它的开心值会减半。也就是说，比如昨天 Bessie 的开心值为 $50$，那么今天早上一醒来就会有 $25$ 点的开心值，舍去小数点后数字。另外，Bessie 还有一个怪癖，她喜欢按照巧克力本来的排列顺序吃。

Bessie 第一天的开心值为 $0$，求一个每天吃巧克力的方案，使得 Bessie 最不开心的一天尽可能的开心。


## 样例 #1

### 输入

```
5 5 
10 
40 
13 
22 
7 
```

### 输出

```
24 
1 
1 
3 
4 
5 
```

# AI分析结果



### 综合分析与结论
本题核心为二分答案+贪心验证。关键难点在于：  
1. 正确记录巧克力分配日期（需在确定最优解后重新验证）  
2. 处理未分配巧克力强制分配到第D天  
3. 数据范围处理（必须用long long）  
所有正确解法均遵循二分框架，差异主要体现在日期记录策略和边界处理上。

---

### 高星题解推荐

#### 1. Yae_Sakura（★★★★☆）
**关键亮点**：  
- 分离二分与日期记录：仅在确定最优解时调用check记录日期  
- 位运算优化：用`sum>>1`替代除法提升效率  
- 显式处理未分配日期：输出时统一赋值为D  

**核心代码思想**：  
```cpp
bool check(ll x) {
    ll sum = 0, tot = 0;
    for (int i=1; i<=d; i++) {
        sum >>= 1;
        while (sum < x) {
            sum += a[++tot];
            if (x == ans) day[tot] = i; // 仅记录最终解
        }
    }
    return tot <= n;
}
```

#### 2. philosopherchang（★★★★☆）
**关键亮点**：  
- 严格数据范围处理：使用unsigned long long  
- 显式重置日期数组：避免残留数据干扰  
- 完整错误分析：列举常见错误类型（数据溢出、未吃完处理）  

**调试心得**：  
> "原来只有200天，我输出了208，于是果断将记录答案的数组中凡是超过最多天数的全改为最多天数"  
> —— 通过强制修正溢出日期解决输出错误

#### 3. funky_monkey（★★★★☆）  
**关键亮点**：  
- 双重验证机制：先判定可行性，再调用jud(ans,1)记录正确方案  
- 统一补全策略：for循环处理所有未分配巧克力  

**核心代码片段**：  
```cpp
if(f) // 仅在最终记录时处理
    for(int i=cur+1; i<=n; i++)
        a[cur] = d; // 剩余全放最后一天
```

---

### 最优关键思路总结
1. **二分框架**：在[0, ∑H_i]范围内二分最小快乐值的最大值  
2. **贪心验证**：每天尽可能少吃巧克力以满足当前mid要求  
3. **二次扫描记录**：确定最优解后重新执行check以正确记录日期  
4. **尾处理技巧**：未被分配的巧克力统一放在最后一天  
5. **位运算优化**：用右移代替除法提高计算效率  

---

### 拓展与举一反三
**相似题目推荐**：  
1. P2218 [HAOI2007]覆盖问题（二分+几何覆盖验证）  
2. P4343 [SHOI2015]自动刷题机（二分答案+计数验证）  
3. P2884 [USACO07MAR]Monthly Expense（二分+分组验证）  

**思维模式**：  
"最小值最大化"问题通常采用二分答案框架，验证时需设计高效的贪心策略。注意验证函数需要同时完成可行性判断和方案记录两个功能，通常需分离处理。

---
处理用时：59.79秒