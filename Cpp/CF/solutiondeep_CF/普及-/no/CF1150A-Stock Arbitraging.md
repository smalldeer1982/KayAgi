# 题目信息

# Stock Arbitraging

## 题目描述

Welcome to Codeforces Stock Exchange! We're pretty limited now as we currently allow trading on one stock, Codeforces Ltd. We hope you'll still be able to make profit from the market!

In the morning, there are $ n $ opportunities to buy shares. The $ i $ -th of them allows to buy as many shares as you want, each at the price of $ s_i $ bourles.

In the evening, there are $ m $ opportunities to sell shares. The $ i $ -th of them allows to sell as many shares as you want, each at the price of $ b_i $ bourles. You can't sell more shares than you have.

It's morning now and you possess $ r $ bourles and no shares.

What is the maximum number of bourles you can hold after the evening?

## 说明/提示

In the first example test, you have $ 11 $ bourles in the morning. It's optimal to buy $ 5 $ shares of a stock at the price of $ 2 $ bourles in the morning, and then to sell all of them at the price of $ 5 $ bourles in the evening. It's easy to verify that you'll have $ 26 $ bourles after the evening.

In the second example test, it's optimal not to take any action.

## 样例 #1

### 输入

```
3 4 11
4 2 5
4 4 5 4
```

### 输出

```
26
```

## 样例 #2

### 输入

```
2 2 50
5 7
4 2
```

### 输出

```
50
```

# AI分析结果



### 题目重写（中文）
# 股票套利

## 题目描述

欢迎来到Codeforces股票交易所！目前我们仅支持交易Codeforces有限公司的股票，但您仍有机会从中获利。

早晨有 $n$ 次买入机会，第 $i$ 次可以按每股 $s_i$ 伯勒无限量购买股票。  
晚上有 $m$ 次卖出机会，第 $i$ 次可以按每股 $b_i$ 伯勒无限量抛售股票（不可超出现有持股量）。  
现在你持有 $r$ 伯勒且无股票，求晚间操作后能持有的最大金额。

## 样例 #1

### 输入
```
3 4 11
4 2 5
4 4 5 4
```

### 输出
```
26
```

### 算法分类
贪心

---

### 题解分析与结论

#### 核心思路
所有题解均基于贪心策略：
1. 寻找最低买入价 `min_buy` 和最高卖出价 `max_sell`
2. 当且仅当存在利润时（`max_sell > min_buy`）进行操作：
   - 最大购买量 = `初始金额 // min_buy`
   - 最终金额 = `购买量 × max_sell + 剩余金额`

#### 解决难点
- **边界处理**：当最高卖出价 ≤ 最低买入价时，不进行任何交易
- **余数计算**：使用整数除法的余数保留未使用的本金

---

### 精选题解

#### 1. Luo_gu_ykc（⭐⭐⭐⭐）
**亮点**：代码简洁，三目运算符直接处理边界
```cpp
int main() {
    // 输入略
    int min_buy = *min_element(a, a+n);
    int max_sell = *max_element(b, b+m);
    cout << (min_buy >= max_sell ? r : (r / min_buy) * max_sell + r % min_buy);
}
```

#### 2. wgy23672（⭐⭐⭐⭐）
**亮点**：使用STL函数求极值，两种实现方式对比
```cpp
int main() {
    int aa = *min_element(a, a+n);
    int bb = *max_element(b, b+m);
    if(aa >= bb) cout << r;
    else cout << r/aa*bb + r%aa;
}
```

#### 3. 黄文烽（⭐⭐⭐）
**数学推导**：将利润公式简化为 `k*(max_sell - min_buy)`，强调剩余金额处理
```cpp
if(min_buy > max_sell) cout << m;
else cout << (m / min_buy) * max_sell + (m % min_buy);
```

---

### 关键技巧
1. **极值选取**：使用遍历或STL函数快速获取极值
2. **整数除法特性**：`r // min_buy` 天然处理最大购买量计算
3. **条件短路**：通过简单比较提前判断无利润情况

---

### 拓展训练
**同类题型推荐**：
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090) - 贪心+优先队列
2. [P1106 删数问题](https://www.luogu.com.cn/problem/P1106) - 贪心选择保留最优序列
3. [P1208 混合牛奶](https://www.luogu.com.cn/problem/P1208) - 贪心选择单价最低的供应商

---

### 心得摘录
- "输入顺序是n→m→r而非r→n→m！"（黄文烽题解强调易错点）
- "注意*max_element的星号不能漏，否则返回的是迭代器"（wgy23672题解提醒STL使用细节）

---
处理用时：39.81秒