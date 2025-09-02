# 题目信息

# [ABC180D] Takahashi Unevolved

## 题目描述

Iroha 正在玩一个宠物养成的游戏。

Iroha 的宠物名字叫 Takahashi。初始，Takahashi 的 **STR** 值为 $X$，**EXP** 值为 $0$。Iroha 可以带宠物到以下任意一个 Gym 进行训练：

- Kakomon Gym：**STR** 值将会变为原来的 $A$ 倍，**EXP** 值将会加上 $1$。
- AtCoder Gym：**STR** 值将会加上 $B$，**EXP** 值将会加上 $1$。

当 Takahashi 的 **STR** 值大于等于 $Y$，Takahashi 会进化形态。

但是 Iroha 认为进化的 Takahashi 没那么可爱，于是 Iroha 想求出在保证 Takahashi 不进化的情况下，能达到的最大 **EXP** 值是多少。

## 样例 #1

### 输入

```
4 20 2 10```

### 输出

```
2```

## 样例 #2

### 输入

```
1 1000000000000000000 10 1000000000```

### 输出

```
1000000007```

# AI分析结果



# [ABC180D] Takahashi Unevolved 题解分析

**题目重述**  
初始时，Takahashi 的 **STR** 值为 $X$，**EXP** 值为 $0$。可以通过以下两种训练方式提升属性：  
1. **Kakomon Gym**：STR 变为原来的 $A$ 倍，EXP 增加 $1$。  
2. **AtCoder Gym**：STR 增加 $B$，EXP 增加 $1$。  

要求在不使 STR 值达到或超过 $Y$ 的前提下，最大化 EXP 的值。  

**算法分类**  
贪心  

---

## 题解综合分析与结论  
各题解均采用**贪心策略**，核心思路是：在 STR 较小时，优先选择增长较慢的操作（乘 $A$ 或加 $B$），直到无法继续选择更优操作时，转为批量计算剩余可能的加法次数。  

### 关键思路与技巧  
1. **乘法优先条件**：当 `STR * A < STR + B` 且 `STR < Y / A` 时，优先选择乘法（避免溢出）。  
2. **溢出处理**：通过判断 `STR < Y / A` 代替 `STR * A < Y`，避免乘法导致数值溢出。  
3. **剩余加法计算**：当无法继续乘法时，直接通过数学公式 `(Y - STR - 1) // B` 计算可执行的加法次数。  

---

## 精选高分题解  

### 题解1：So_noSlack（★★★★★）  
**亮点**  
- 代码简洁，逻辑清晰，直接处理溢出问题。  
- 使用 `while` 循环判断乘法条件，跳出后立即计算加法次数。  
**核心代码**  
```cpp
long long x, y, a, b, ans = 0;
cin >> x >> y >> a >> b;
while (x < y) {
    if (x < y / a && x * a < x + b) x *= a, ans++;
    else break;
}
ans += (y - x - 1) / b;
cout << ans << endl;
```

### 题解2：hellolin（★★★★☆）  
**亮点**  
- 使用 `for` 循环简化乘法条件判断，代码紧凑。  
- 注释明确，强调溢出处理的关键性。  
**核心代码**  
```cpp
for (ans=0; x<(y/a) && (x*a)<(x+b); x*=a) ++ans;
cout << ans + ((y-x-1)/b) << endl;
```

### 题解3：Moon_Traveller（★★★★☆）  
**亮点**  
- 详细分析暴力代码的缺陷，强调数学优化的必要性。  
- 明确解释 `(y - x - 1)` 的减一意义。  
**核心代码**  
```cpp
while (STR < y / a && STR * a < STR + b) {
    STR *= a;
    EXP++;
}
EXP += (y - STR - 1) / b;
```

---

## 拓展与总结  
**举一反三**  
- 类似题目需分阶段处理：先贪心选择局部最优，剩余部分批量计算。  
- 注意大数溢出问题，优先使用除法或不等式变形代替乘法判断。  

**推荐题目**  
1. [P9743 「KDOI-06-J」旅行者问题](https://www.luogu.com.cn/problem/P9743)（贪心+数学分析）  
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)（优先队列贪心）  
3. [P1031 均分纸牌](https://www.luogu.com.cn/problem/P1031)（分阶段处理策略）  

**个人心得摘录**  
> “当乘法可能导致死循环时，通过除法判断条件可避免溢出。”（Moon_Traveller）  
> “暴力枚举后需分析数据范围，寻找数学优化点。”（xiaofeng_and_xiaoyu）

---
处理用时：51.07秒