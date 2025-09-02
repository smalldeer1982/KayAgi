# 题目信息

# Weird Rounding

## 题目描述

Polycarp is crazy about round numbers. He especially likes the numbers divisible by $ 10^{k} $ .

In the given number of $ n $ Polycarp wants to remove the least number of digits to get a number that is divisible by $ 10^{k} $ . For example, if $ k=3 $ , in the number 30020 it is enough to delete a single digit (2). In this case, the result is 3000 that is divisible by $ 10^{3}=1000 $ .

Write a program that prints the minimum number of digits to be deleted from the given integer number $ n $ , so that the result is divisible by $ 10^{k} $ . The result should not start with the unnecessary leading zero (i.e., zero can start only the number 0, which is required to be written as exactly one digit).

It is guaranteed that the answer exists.

## 说明/提示

In the example 2 you can remove two digits: 1 and any 0. The result is number 0 which is divisible by any number.

## 样例 #1

### 输入

```
30020 3
```

### 输出

```
1
```

## 样例 #2

### 输入

```
100 9
```

### 输出

```
2
```

## 样例 #3

### 输入

```
10203049 2
```

### 输出

```
3
```

# AI分析结果



# 中文题目翻译

# 奇怪的舍入

## 题目描述

Polycarp 对整数有疯狂的热爱。他特别喜欢能被 $10^{k}$ 整除的数。

给定数字 $n$，Polycarp 想要删除最少的数字，使得剩余的数字能组成一个能被 $10^{k}$ 整除的数。例如当 $k=3$ 时，数字 30020 只需要删除一个数字（2）即可变成 3000，该数能被 $10^3=1000$ 整除。

编写程序输出需要删除的最小数字个数。结果不能包含多余的前导零（即除了数字 0 本身外，不能以零开头）。题目保证解存在。

## 说明/提示

样例2中，可以删除两个数字：1 和任意一个0，得到0（能被任何数整除）。

---

**算法分类**：贪心

---

## 题解综合分析

### 核心思路对比
所有题解均基于以下观察：要被 $10^k$ 整除，结果必须有**末尾连续k个0**。实现方式可分为两类：
1. **逆向扫描法**（主流方案）：从数字末尾逆向扫描，统计0的个数，同时计算需要删除的非零数字
2. **栈处理法**（较少见）：用栈倒序处理数字，维护0的计数

### 解决难点
1. **末尾0不足时的处理**：当整个数字中0的总数不足k时，必须删至仅剩单个0
2. **前导零规避**：结果0必须保留为单个字符，通过直接输出 `length-1` 隐式处理
3. **扫描终止条件**：在收集到k个0后立即终止扫描

### 最优关键思路
逆向扫描字符串，维护两个计数器：
- `zero_cnt`：已找到的末尾0的数量
- `del_cnt`：需要删除的非零字符数

当 `zero_cnt == k` 时输出 `del_cnt`，否则输出 `length-1`

---

## 精选题解

### 1. alex_liu（⭐⭐⭐⭐⭐）
**核心亮点**：
- 代码简洁高效（仅15行）
- 完美处理所有边界情况
- 使用字符串直接操作，避免数值溢出

**关键代码**：
```cpp
for(int i=n.size()-1;i>=0;i--){ // 逆向扫描
    if(cnt>=k) break;
    if(n[i]=='0') cnt++; 
    else ans++; // 非零需删除
}
cout << (cnt>=k ? ans : n.size()-1);
```

### 2. dalao_see_me（⭐⭐⭐⭐）
**代码亮点**：
- 变量命名清晰（`_0`表示0计数器）
- 逻辑与标准解法完全一致
- 包含必要的中文注释

**个人心得**：
> "可以用字符串处理而非直接用数字，个人认为会方便很多" —— 强调字符串处理的优势

### 3. Noby_Glds（⭐⭐⭐⭐）
**特色处理**：
- 预处理统计总0数
- 分离两种情况的判断逻辑
- 代码结构清晰易扩展

**代码片段**：
```cpp
if(sum<k) cout<<a.size()-1; // 0不足时的处理
else for(/*逆向扫描*/)...
```

---

## 拓展练习
1. [P1106 删数问题](https://www.luogu.com.cn/problem/P1106) - 同类贪心问题，但要求保留指定位数
2. [P4995 跳跳！](https://www.luogu.com.cn/problem/P4995) - 贪心策略在跳跃问题中的应用
3. [P1323 删除数字](https://www.luogu.com.cn/problem/P1323) - 变形删数问题，需结合数学分析

---

## 调试经验总结
- **前导零陷阱**：多位0必须合并处理（如数字20003，删除中间0后的前导零问题）
- **全零特例**：当n本身就是0时直接输出0（如题解caibet中的特判）
- **逆向索引**：注意字符串逆向扫描时 `i` 的起始值应为 `length-1`（常见错误点）

---
处理用时：53.12秒