# 题目信息

# Robbery

## 题目描述

It is nighttime and Joe the Elusive got into the country's main bank's safe. The safe has $ n $ cells positioned in a row, each of them contains some amount of diamonds. Let's make the problem more comfortable to work with and mark the cells with positive numbers from $ 1 $ to $ n $ from the left to the right.

Unfortunately, Joe didn't switch the last security system off. On the plus side, he knows the way it works.

Every minute the security system calculates the total amount of diamonds for each two adjacent cells (for the cells between whose numbers difference equals $ 1 $ ). As a result of this check we get an $ n-1 $ sums. If at least one of the sums differs from the corresponding sum received during the previous check, then the security system is triggered.

Joe can move the diamonds from one cell to another between the security system's checks. He manages to move them no more than $ m $ times between two checks. One of the three following operations is regarded as moving a diamond: moving a diamond from any cell to any other one, moving a diamond from any cell to Joe's pocket, moving a diamond from Joe's pocket to any cell. Initially Joe's pocket is empty, and it can carry an unlimited amount of diamonds. It is considered that before all Joe's actions the system performs at least one check.

In the morning the bank employees will come, which is why Joe has to leave the bank before that moment. Joe has only $ k $ minutes left before morning, and on each of these $ k $ minutes he can perform no more than $ m $ operations. All that remains in Joe's pocket, is considered his loot.

Calculate the largest amount of diamonds Joe can carry with him. Don't forget that the security system shouldn't be triggered (even after Joe leaves the bank) and Joe should leave before morning.

## 说明/提示

In the second sample Joe can act like this:

The diamonds' initial positions are $ 4 $ $ 1 $ $ 3 $ .

During the first period of time Joe moves a diamond from the $ 1 $ -th cell to the $ 2 $ -th one and a diamond from the $ 3 $ -th cell to his pocket.

By the end of the first period the diamonds' positions are $ 3 $ $ 2 $ $ 2 $ . The check finds no difference and the security system doesn't go off.

During the second period Joe moves a diamond from the $ 3 $ -rd cell to the $ 2 $ -nd one and puts a diamond from the $ 1 $ -st cell to his pocket.

By the end of the second period the diamonds' positions are $ 2 $ $ 3 $ $ 1 $ . The check finds no difference again and the security system doesn't go off.

Now Joe leaves with $ 2 $ diamonds in his pocket.

## 样例 #1

### 输入

```
2 3 1
2 3
```

### 输出

```
0```

## 样例 #2

### 输入

```
3 2 2
4 1 3
```

### 输出

```
2```

# AI分析结果



# 题目内容中文翻译

# 抢劫案

## 题目描述

深夜，乔潜入了国家主银行的保险库。保险库有 $n$ 个呈一行排列的储存单元，每个单元存有若干钻石。为方便描述，我们将这些单元从左至右依次编号为 $1$ 到 $n$。

保险库的安保系统每分钟会执行如下检查：计算每对相邻单元（编号差为1的单元）的钻石总数，得到 $n-1$ 个总和。若任意总和与前一分钟的检查结果不同，警报就会触发。

乔可以在两次检查间隙转移钻石，每次检查间隔最多进行 $m$ 次操作。操作包含三种类型：将钻石从一个单元移到另一个单元、将钻石存入自己口袋、从口袋取出钻石放入某个单元。口袋初始为空且容量无限。注意安保系统在乔首次操作前已至少执行过一次检查。

距离早晨银行职员到来还有 $k$ 分钟，乔必须在这段时间内离开且保证警报未被触发（包括离开后的检查）。求乔能带走的最大钻石数。

## 样例 #1

### 输入

```
2 3 1
2 3
```

### 输出

```
0```

## 样例 #2

### 输入

```
3 2 2
4 1 3
```

### 输出

```
2```

---

### 算法分类
数学/构造

---

## 题解综合分析

所有题解均基于以下核心观察：

1. **奇偶性判断**：当 $n$ 为偶数时无法偷取钻石（任何操作都会改变相邻和）
2. **操作模式构造**：当 $n$ 为奇数时，偷取1颗钻石需 $\frac{n}{2}+1$ 次操作（通过交替传递保持相邻和不变）
3. **双重约束**：最大可偷数受限于操作能力（$m \cdot k / 操作次数$）和奇数位最小钻石量

各题解在代码实现上高度相似，主要区别在于边界处理（如n=1的情况）。最优解法需同时满足数学模型和资源限制。

---

## 高星题解推荐

### 1. Provider的题解（★★★★☆）
**核心亮点**：
- 明确处理n=1的特殊情况（此时每分钟可拿m颗）
- 使用位运算优化奇偶判断（i&1）
- 代码简洁且包含优化指令（pragma GCC optimize）

**关键代码**：
```cpp
if(n==1)
    cout<<min(a[1],k*m);
else if((n&1)==0)
    cout<<0;
else {
    long long tmp=(n>>1)+1;
    if(m<tmp) cout<<0;
    else cout<<min(minvalue,k*(m/tmp));
}
```

### 2. Nozebry的题解（★★★★☆）
**核心亮点**：
- 清晰注释描述操作步骤（分组移动策略）
- 变量命名直观（minn存储最小值）
- 输入输出使用scanf/printf优化效率

**实现思路**：
- 预处理奇数位置的最小钻石数
- 分情况讨论奇偶性及操作次数阈值

---

## 关键思路总结

1. **奇偶定成败**：偶数单元数直接无解，奇数单元数才存在可行方案
2. **操作次数模型**：$\text{每颗消耗次数} = \lfloor n/2 \rfloor + 1$
3. **瓶颈识别**：最终解为 $\min(\text{操作产能}, \text{资源短板})$ 的经典双约束问题

---

## 同类题目推荐

1. P1094 [纪念品分组]（贪心+双指针）
2. P5019 [铺设道路]（差分数组应用）
3. P1968 [美元汇率]（数学建模与最优决策）

---
处理用时：51.90秒