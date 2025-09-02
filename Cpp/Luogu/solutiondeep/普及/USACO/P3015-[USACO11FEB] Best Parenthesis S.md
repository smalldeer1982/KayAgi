# 题目信息

# [USACO11FEB] Best Parenthesis S

## 题目描述

Recently, the cows have been competing with strings of balanced parentheses and comparing them with each other to see who has the best one.

Such strings are scored as follows (all strings are balanced): the string '()' has score 1; if 'A' has score s(A) then '(A)' has score 2\*s(A); and if 'A' and 'B' have scores s(A) and s(B), respectively, then 'AB' has score s(A)+s(B). For example, s('(())()') = s('(())')+s('()') = 2\*s('()')+1 = 2\*1+1 = 3.

Bessie wants to beat all of her fellow cows, so she needs to calculate the score of some strings. Given a string of balanced parentheses of length N (2 <= N <= 100,000), help Bessie compute its score.

给定一个只包含左右括号的字符串，得分规则如下：

如果一对括号内没有括号，那么这对括号的得分为1；如果两对括号互不包含（即并列存在），那这两对括号的得分相加；如果括号内包含一对括号，那么这个括号的得分纪为内部括号序列的得分\*2。

例如：对于这样一个字符串："() ()"，两对括号并列存在，则得分为1+1=2;

而对于这样一个字符串："(())"，最外层的括号内层包含一对括号，则得分为2\*1=2.


Bessie想击败所有同事的牛，所以她需要计算某个字符串的评分。给定一个长度为n、只包含括号的字符串（2≤N≤100000），计算其得分帮助Bessie。


## 说明/提示

This corresponds to the string "(())()". 

As discussed above.

输出答案要mod12345678910


## 样例 #1

### 输入

```
6 
0 
0 
1 
1 
0 
1 
```

### 输出

```
3 
```

# AI分析结果



### 综合分析与结论
本题核心在于通过栈结构模拟嵌套括号的得分计算，结合分治与动态规划思想。关键技巧是维护层间得分关系，动态合并相邻括号的贡献。所有题解中，栈模拟法（时间复杂度O(N)）为最优解，递归法存在栈溢出风险，部分题解因计算方式低效导致时间复杂度过高。

---

### 高星题解推荐

#### 1. 作者：kkxhh（★★★★★）
**关键亮点**：
- 使用栈结构维护层间得分，逻辑清晰简洁
- 通过条件判断直接区分基础括号对和嵌套结构
- 空间优化（仅用单数组存储层状态）

**核心代码思路**：
```cpp
ll s[50010] = {0}; // 层得分数组
for(输入字符){
    if(左括号) t++; // 入栈
    else {
        if(s[t] == 0) s[t-1] += 1;  // 基础括号对
        else s[t-1] += s[t]*2;      // 嵌套结构
        s[t--] = 0;                 // 弹出当前层
    }
}
```

#### 2. 作者：jzcrq（★★★★★）
**关键亮点**：
- 手写栈实现高效内存管理
- 通过栈顶状态判断合并方式
- 完美处理多层嵌套与并列结构

**核心实现**：
```cpp
struct Stack {
    int array[MAXN], poi=0;
    void push(int x) { array[++poi] = x; }
    // 遇到右括号时处理合并
    if(栈顶非零) {
        tmp = stack.top() * 2;  // 嵌套乘法
        合并到上层栈顶
    } else {
        直接加1到上层
    }
}
```

#### 3. 作者：juseice（★★★★☆）
**关键亮点**：
- 多项式计算思路转化问题
- 动态维护加法与乘法操作
- 通过栈状态判断操作类型

**关键处理逻辑**：
```pascal
procedure work;
begin
  if 当前是基础括号对 then 层得分+1
  else 合并嵌套得分(层得分*2)
  同时处理连续加法操作
end;
```

---

### 最优解题思路提炼
1. **栈结构维护**：用栈保存每层括号的累计得分，遇到右括号时根据栈顶状态决定操作
2. **层间合并策略**：
   - 基础括号对（`()`）：直接给上层+1
   - 嵌套结构（`(A)`）：将当前层得分*2后合并到上层
3. **即时取模**：所有运算步骤后立即取模，避免数值溢出
4. **状态判断**：通过栈顶是否为0区分基础括号对与嵌套结构

---

### 拓展与举一反三
1. **同类问题**：
   - 不同括号得分规则（如分数递增）
   - 带运算符的括号表达式计算
   - 最大合法括号子串长度
   
2. **推荐练习题目**：
   - P1944 最长括号匹配（栈应用）
   - P5658 括号树（树形结构+括号性质）
   - P2119 修正括号序列（平衡性计算）

---

### 题解中的经验总结
1. **调试经验**（Minclxc）：
   > "递归方法需注意括号位置传递，通过预处理匹配表降低复杂度"
   
2. **数值处理**（RioBlu）：
   > "不能直接使用pow函数，需自行实现快速幂并即时取模"

3. **类型陷阱**（king_xbz）：
   > "模数12345678910超int范围，必须全程使用long long"

---
处理用时：120.15秒