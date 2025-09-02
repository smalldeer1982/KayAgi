# 题目信息

# Bag of mice

## 题目描述

The dragon and the princess are arguing about what to do on the New Year's Eve. The dragon suggests flying to the mountains to watch fairies dancing in the moonlight, while the princess thinks they should just go to bed early. They are desperate to come to an amicable agreement, so they decide to leave this up to chance.

They take turns drawing a mouse from a bag which initially contains $ w $ white and $ b $ black mice. The person who is the first to draw a white mouse wins. After each mouse drawn by the dragon the rest of mice in the bag panic, and one of them jumps out of the bag itself (the princess draws her mice carefully and doesn't scare other mice). Princess draws first. What is the probability of the princess winning?

If there are no more mice in the bag and nobody has drawn a white mouse, the dragon wins. Mice which jump out of the bag themselves are not considered to be drawn (do not define the winner). Once a mouse has left the bag, it never returns to it. Every mouse is drawn from the bag with the same probability as every other one, and every mouse jumps out of the bag with the same probability as every other one.

## 说明/提示

Let's go through the first sample. The probability of the princess drawing a white mouse on her first turn and winning right away is 1/4. The probability of the dragon drawing a black mouse and not winning on his first turn is 3/4 \* 2/3 = 1/2. After this there are two mice left in the bag — one black and one white; one of them jumps out, and the other is drawn by the princess on her second turn. If the princess' mouse is white, she wins (probability is 1/2 \* 1/2 = 1/4), otherwise nobody gets the white mouse, so according to the rule the dragon wins.

## 样例 #1

### 输入

```
1 3
```

### 输出

```
0.500000000
```

## 样例 #2

### 输入

```
5 5
```

### 输出

```
0.658730159
```

# AI分析结果



# 中文题目翻译

## 题目描述

龙和公主正在争论除夕夜该做什么。龙建议飞到山上看仙女在月光下跳舞，而公主认为他们应该早点睡觉。他们迫切希望达成友好协议，于是决定让命运来决定。

他们轮流从一个最初装有 $w$ 只白老鼠和 $b$ 只黑老鼠的袋子中抓老鼠。第一个抓到白老鼠的人获胜。在龙每次抓鼠后，袋中剩余的老鼠会受到惊吓，其中一只会自己跳出袋子（公主抓鼠时很小心不会惊吓其他老鼠）。公主先手。求公主获胜的概率。

如果袋中没有老鼠且没人抓到白鼠，则龙获胜。自行跳出的老鼠不计入抓取结果（不决定胜负）。每只老鼠被抓取和跳出的概率均等。

## 样例 #1

### 输入

```
1 3
```

### 输出

```
0.500000000
```

## 样例 #2

### 输入

```
5 5
```

### 输出

```
0.658730159
```

---

# 题解综合分析

## 最优解法总结
**关键思路**：动态规划 + 状态转移分类讨论  
**状态设计**：`dp[i][j]` 表示剩余i白鼠j黑鼠时先手获胜概率  
**转移方程**：
1. 直接抽白鼠：`i/(i+j)`
2. 双方抽黑鼠后：
   - 逃跑白鼠：`j/(i+j) * (j-1)/(i+j-1) * i/(i+j-2) * dp[i-1][j-2]`
   - 逃跑黑鼠：`j/(i+j) * (j-1)/(i+j-1) * (j-2)/(i+j-2) * dp[i][j-3]`

---

## 精选题解（评分≥4星）

### 题解1：yingyudou（⭐⭐⭐⭐⭐）
**亮点**：
1. 完整的状态转移方程推导
2. 同时提供递推和记忆化搜索两种实现
3. 处理边界条件清晰（`j^2`判断避免数组越界）

**核心代码**：
```cpp
for(int i=1;i<=w;++i)
    for(int j=2;j<=b;++j) {
        f[i][j] = 1.0*i/(i+j);
        f[i][j] += j/(i+j) * (j-1)/(i+j-1) * i/(i+j-2) * f[i-1][j-2];
        if(j>2) f[i][j] += j/(i+j) * (j-1)/(i+j-1) * (j-2)/(i+j-2) * f[i][j-3];
    }
```

### 题解2：Pathetique（⭐⭐⭐⭐）
**亮点**：
1. 记忆化搜索实现更高效
2. 按需计算状态，避免无效计算
3. 代码结构简洁易读

**核心代码**：
```cpp
double dfs(int nw,int nb) {
    if(nw==0) return 0.0;
    if(nb==0) return 1.0;
    if(f[nw][nb]>0) return f[nw][nb];
    double ans = 1.0*nw/(nw+nb);
    if(nb>=2) {
        double p = 1.0*nb/(nw+nb) * (nb-1)/(nw+nb-1);
        ans += p * (nw/(nw+nb-2)*dfs(nw-1,nb-2) + 
                   (nb>=3 ? (nb-2)/(nw+nb-2)*dfs(nw,nb-3) : 0));
    }
    return f[nw][nb] = ans;
}
```

---

## 关键技巧与拓展
1. **分母预计算优化**：将分数运算转换为乘法运算避免重复计算
2. **记忆化搜索优势**：适用于状态空间稀疏的场景，避免无效状态计算
3. **同类问题套路**：多阶段概率问题常用记忆化搜索 + 状态转移树分析

**推荐练习**：
1. P1850 [NOIP2016 提高组] 换教室（期望DP）
2. P1654 OSU!（概率递推）
3. P4548 [CTSC2006] 歌唱王国（概率生成函数）

---

## 调试心得摘录
1. **边界处理**：当`j=2`时不能转移逃跑黑鼠的情况（`j-3`会越界）
2. **浮点精度**：使用`double`类型存储概率，输出保留9位小数
3. **状态初始化**：`f[i][0] = 1`和`f[0][j] = 0`的预处理简化计算

> "记忆化搜索比刷表快很多，因为只计算有用状态" —— Pathetique  
> "注意当j=1时的特殊处理，此时公主必须首轮抽中白鼠" —— yingyudou

---
处理用时：51.07秒