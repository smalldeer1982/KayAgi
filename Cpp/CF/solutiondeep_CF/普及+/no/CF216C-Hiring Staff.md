# 题目信息

# Hiring Staff

## 题目描述

A new Berland businessman Vitaly is going to open a household appliances' store. All he's got to do now is to hire the staff.

The store will work seven days a week, but not around the clock. Every day at least $ k $ people must work in the store.

Berland has a law that determines the order of working days and non-working days. Namely, each employee must work for exactly $ n $ consecutive days, then rest for exactly $ m $ days, then work for $ n $ more days and rest for $ m $ more, and so on. Vitaly doesn't want to break the law. Fortunately, there is a loophole: the law comes into force on the day when the employee is hired. For example, if an employee is hired on day $ x $ , then he should work on days $ [x,x+1,...,x+n-1] $ , $ [x+m+n,x+m+n+1,...,x+m+2n-1] $ , and so on. Day $ x $ can be chosen arbitrarily by Vitaly.

There is one more thing: the key to the store. Berland law prohibits making copies of keys, so there is only one key. Vitaly is planning to entrust the key to the store employees. At the same time on each day the key must be with an employee who works that day — otherwise on this day no one can get inside the store. During the day the key holder can give the key to another employee, if he also works that day. The key will handed to the first hired employee at his first working day.

Each employee has to be paid salary. Therefore, Vitaly wants to hire as few employees as possible provided that the store can operate normally on each day from $ 1 $ to infinity. In other words, on each day with index from $ 1 $ to infinity, the store must have at least $ k $ working employees, and one of the working employees should have the key to the store.

Help Vitaly and determine the minimum required number of employees, as well as days on which they should be hired.

## 样例 #1

### 输入

```
4 3 2
```

### 输出

```
4
1 1 4 5```

## 样例 #2

### 输入

```
3 3 1
```

### 输出

```
3
1 3 5```

# AI分析结果

### 题目内容
# 招聘员工

## 题目描述
一位新的伯兰商人维塔利打算开一家家用电器商店。现在他要做的就是招聘员工。

商店每周营业七天，但不是全天营业。每天至少必须有 $k$ 个人在商店工作。

伯兰有一项法律规定了工作日和休息日的顺序。具体来说，每个员工必须连续工作 $n$ 天，然后连续休息 $m$ 天，再工作 $n$ 天，再休息 $m$ 天，依此类推。维塔利不想违反法律。幸运的是，有一个漏洞：该法律从员工被雇佣的那天起生效。例如，如果一名员工在第 $x$ 天被雇佣，那么他应该在第 $[x,x + 1,...,x + n - 1]$ 天、$[x + m + n,x + m + n + 1,...,x + m + 2n - 1]$ 天等工作。第 $x$ 天可以由维塔利任意选择。

还有一件事：商店的钥匙。伯兰法律禁止复制钥匙，所以只有一把钥匙。维塔利计划将钥匙交给商店员工。同时，每天钥匙必须在当天工作的员工手中 —— 否则当天没有人能进入商店。在白天，钥匙持有人可以将钥匙交给当天也工作的另一名员工。钥匙将在第一名被雇佣员工的第一个工作日交给他。

每个员工都必须支付工资。因此，维塔利希望在商店从第 $1$ 天到无穷大的每一天都能正常运营的前提下，雇佣尽可能少的员工。换句话说，在从 $1$ 到无穷大的每一天，商店必须至少有 $k$ 名工作员工，并且其中一名工作员工应该有商店的钥匙。

帮助维塔利确定所需的最少员工数量，以及他们应该被雇佣的日期。

## 样例 #1
### 输入
```
4 3 2
```
### 输出
```
4
1 1 4 5
```

## 样例 #2
### 输入
```
3 3 1
```
### 输出
```
3
1 3 5
```

### 算法分类
贪心

### 综合分析与结论
这两道题解都围绕如何以最少员工数量满足商店运营要求展开。
- **思路方面**：
    - ShwStone的题解基于 $n + m$ 天循环的特性，从前 $n + m$ 天入手，先在第一天雇佣 $k$ 人，之后按天扫描，根据当天人数与 $k$ 的差值决定雇佣人数及时间，同时单独考虑 $n + m + 1$ 天钥匙的问题。
    - _xbn的题解先考虑 $k = 1$ 的特殊情况，再推广到一般情况，依据有员工从前一天工作且雇佣最少的原则确定雇佣时间，还针对 $n = m$ 的特殊情况进行处理。
- **算法要点**：两者都采用贪心策略，在满足每天工作人数和钥匙持有条件下尽量少雇佣员工。ShwStone通过数组记录每天人数来动态调整雇佣，_xbn则根据不同特殊情况直接确定雇佣日期。
- **解决难点**：主要难点在于如何在满足法律规定（工作和休息周期）、每天工作人数要求及钥匙传递条件下，找到最少的雇佣人数和合适的雇佣日期。ShwStone通过细致的模拟和条件判断解决，_xbn通过对特殊情况的分析和归纳来处理。

整体来看，ShwStone的题解思路更通用、详细，代码逻辑清晰，通过数组模拟能较好理解；_xbn的题解虽然简洁，但对特殊情况依赖较大，通用性稍弱。

### 所选的题解
- **ShwStone题解**
  - **星级**：4星
  - **关键亮点**：利用 $n + m$ 天的循环特性，通过数组模拟每天工作人数，按天扫描动态确定雇佣人数和时间，全面考虑钥匙传递问题，思路清晰，通用性强。
  - **重点代码**：
```cpp
for (int i = 1; i <= n; i++) {
    cnt[i] = k;
}
for (int i = 1; i <= k; i++) {
    ans.emplace_back(1);
}
for (int i = n + 1; i <= n + m; i++) {
    if (cnt[i] < k) {
        if (cnt[i] == 0) {
            for (int j = 1; j <= n; j++) cnt[i + j - 2]++;
            ans.emplace_back(i - 1);
        }
        while (cnt[i] < k) {
            for (int j = 1; j <= n; j++) cnt[i + j - 1]++;
            ans.emplace_back(i);
        }
    }
}
if (!cnt[n + m + 1]) {
    ans.emplace_back(n + m);
}
```
  - **核心实现思想**：先初始化前 $n$ 天每天有 $k$ 人工作，并记录第一天雇佣 $k$ 人。从第 $n + 1$ 天到 $n + m$ 天扫描，若当天人数小于 $k$，若为 $0$ 则在前一天雇佣一人拿钥匙并在当天补足人数；否则直接在当天补足人数。最后判断 $n + m + 1$ 天是否有钥匙，没有则在 $n + m$ 天雇佣一人。

### 最优关键思路或技巧
利用 $n + m$ 天的循环特性，采用贪心策略，通过数组模拟每天工作人数，动态调整雇佣计划，在满足各种条件下实现最少人数雇佣。

### 同类型题或类似算法套路拓展
此类题目通常围绕资源分配（这里是员工工作时间分配），在满足多种限制条件（工作休息周期、每天人数下限、特殊物品传递等）下求最优解。类似套路是先分析问题的周期特性或规律，然后基于贪心思想，在每个阶段或时间点做出局部最优选择，以达到全局最优。

### 洛谷推荐题目
- [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)：涉及贪心策略，通过合理排序实现最优分配。
- [P1199 [NOIP2010 普及组] 三国游戏](https://www.luogu.com.cn/problem/P1199)：同样是在规则限制下，利用贪心思路寻找最优策略。
- [P2123 皇后游戏](https://www.luogu.com.cn/problem/P2123)：通过对数据的分析和贪心策略，解决排序和最优安排问题。 

---
处理用时：51.38秒