# 题目信息

# Challenge Pennants

## 题目描述

Because of budget cuts one IT company established new non-financial reward system instead of bonuses.

Two kinds of actions are rewarded: fixing critical bugs and suggesting new interesting features. A man who fixed a critical bug gets "I fixed a critical bug" pennant on his table. A man who suggested a new interesting feature gets "I suggested a new feature" pennant on his table.

Because of the limited budget of the new reward system only $ 5 $ "I fixed a critical bug" pennants and $ 3 $ "I suggested a new feature" pennants were bought.

In order to use these pennants for a long time they were made challenge ones. When a man fixes a new critical bug one of the earlier awarded "I fixed a critical bug" pennants is passed on to his table. When a man suggests a new interesting feature one of the earlier awarded "I suggested a new feature" pennants is passed on to his table.

One man can have several pennants of one type and of course he can have pennants of both types on his table. There are $ n $ tables in the IT company. Find the number of ways to place the pennants on these tables given that each pennant is situated on one of the tables and each table is big enough to contain any number of pennants.

## 样例 #1

### 输入

```
2
```

### 输出

```
24```

# AI分析结果



### 题目中文重写
#### 题目名称：挑战锦旗

**题目描述**  
某IT公司因预算缩减，改用非金钱奖励制度。员工通过修复关键漏洞或提出新功能可获得锦旗。现有5个"修复漏洞"锦旗和3个"提出功能"锦旗。这些锦旗采用传承机制：每次员工获得新奖励时，会从前人处获得对应类型的锦旗。

已知公司有$n$张桌子，求所有锦旗摆放在桌子上的方式总数。每个锦旗必须放置在某一桌子上，桌子容量无限。

**输入样例**  
```
2
```

**输出样例**  
```
24
```

---

### 算法分类
组合数学

---

### 题解分析与结论
题目核心为计算可重复排列组合数。两种锦旗独立分配，使用乘法原理。关键公式为可重复组合数：  
$$C(n+k-1, k) = \frac{(n+k-1)!}{k!(n-1)!}$$  
其中$n$为桌子数，$k$为锦旗数。

---

### 高星题解推荐

#### 1. 封禁用户（★★★★☆）  
**核心亮点**  
- 将组合数展开为连乘连除形式，避免中间值溢出  
- 无函数调用直接计算，提升执行效率  
**关键代码**  
```cpp
cout<<(n+2)*(n+1)/2*n/3*(n+4)*(n+3)/2*(n+2)/3*(n+1)/4*n/5;
```
**实现思路**  
分步计算组合数：  
1. 计算C(n+2,3)：(n+2)(n+1)n/(3×2×1)  
2. 计算C(n+4,5)：(n+4)(n+3)(n+2)(n+1)n/(5×4×3×2×1)  
3. 将中间步骤拆解为连续乘除，控制数值范围

#### 2. BrokenStar（★★★★☆）  
**核心亮点**  
- 模块化组合数函数设计  
- 清晰的数学公式对应代码  
**关键代码**  
```cpp
long long C(int a, long long b){
    long long ans = 1;
    for(int i=1; i<=b; ++i)
        ans = ans*(a+1-i)/i;
    return ans;
}
```
**实现思路**  
通过循环计算组合数：  
$$C(a,b) = \prod_{i=1}^b \frac{a+1-i}{i}$$  
依次约分避免阶乘溢出

#### 3. Amberhart（★★★★☆）  
**核心亮点**  
- 明确的类型定义（long long）  
- 完整数学公式注释  
**个人心得**  
> "如果不知道哪里用long long就全用long long"  
**关键代码**  
```cpp
ll c(ll a, ll b){
    ll s=1;
    for(ll i=1; i<=b; i++)
        s = s*(a+1-i)/i;
    return s;
}
```

---

### 最优思路总结
1. **独立计算原则**：将两种锦旗视为独立事件，分别计算组合数后相乘  
2. **可重复组合公式**：$C(n+k-1, k)$对应"允许空桌"的摆放方式  
3. **数值安全策略**：  
   - 使用long long防止溢出  
   - 循环计算组合数而非预计算阶乘  
   - 分步约分控制中间值大小  

---

### 拓展建议
**同类问题套路**  
- 物品分配问题（小球放入盒子）  
- 非降路径计数  
- 方程非负整数解计数  

**推荐题目**  
1. [P2638 系统安全](https://www.luogu.com.cn/problem/P2638)  
2. [P2822 组合数问题](https://www.luogu.com.cn/problem/P2822)  
3. [P4369 组合数](https://www.luogu.com.cn/problem/P4369)  

---

### 题解心得摘录
OLE_OIer的调试经验：  
> "最初错误使用C(n-1,5)，忽略了允许空桌的情况。正确公式应为C(n+4,5)，因为可重复组合公式是C(n+k-1,k)"  
说明理解公式推导过程的重要性，避免机械套用模板。

---
处理用时：61.01秒