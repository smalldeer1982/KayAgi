# 题目信息

# 「Wdcfr-1」Magical Expression

## 题目描述

Nitori is learning postfix expressions. She has a incomplete postfix expression $E$ of length $n$. Being a Youkai, she wants to find its magical property.

Her postfix expression contains the Bitwise Or operator (denoted as `|`), the Bitwise And operator (denoted as `&`), and numbers `0` and `1`. Being incomplete, some operators have not been decided yet and are denoted as `?`. She promised that $E$ **will become a *vaild* postfix expression** after you complete it.

In this problem, the term *substring* is defined as a continuous segment of $E$. **Two substrings are considered different as long as their positions or length differ.**  So `1?0`, `01?0` are all substrings of `01?01?|`  , but `0101` is not.

Nitori found out that a substring of her expression is *magical* if and only if the following conditions are met:

- It is possible to transform it into a *valid* postfix expression after replacing `?` with either `&` or `|` .
- Among these transformations, it is possible to find at least one of them that after applying it, the expression yields $0$,  and at least one of them that after applying it, the expression yields $1$.

Your task is to find out the number of *magical* substrings.


## 说明/提示

### Constraints

$1\le T,n\le 2\times 10^6$. The sum of $n$ of all test cases $\le 2\times 10^6$.

## 样例 #1

### 输入

```
2
3 01?
7 01?01?|```

### 输出

```
1
3```

# AI分析结果



### 算法分类
**贪心**

### 综合分析与结论
题目要求统计后缀表达式子串在 `?` 替换为 `|` 或 `&` 后能同时得到 0 和 1 的情况。核心思路是：  
1. **贪心极值替换**：将 `?` 全替换为 `&` 可最大可能得到 0，替换为 `|` 则最大可能得到 1。  
2. **表达式树/栈处理**：通过构建表达式树或栈结构，快速计算两种极端情况的结果。若某节点两次计算结果不同，则其对应的子串符合条件。  
3. **线性复杂度**：所有解法均通过 O(n) 的遍历实现，符合题目规模要求。

---

### 精选题解
#### 1. 卷王（5星）
**关键亮点**：  
- 显式构建表达式树，两次 DFS 分别处理 `?` 替换为 `&` 和 `|` 的情况。  
- 代码逻辑清晰，利用栈高效建树，时间复杂度稳定 O(n)。  
**代码核心**：
```cpp
void dfs(int t, bool lxl) {
    if(a[t].l == -1) { ok[lxl][t] = a[t].x - '0'; return; }
    dfs(a[t].l, lxl); dfs(a[t].r, lxl);
    // 根据操作符和替换策略计算当前节点值
}
```
**注意点**：多测需清空栈，否则残留数据会导致错误。

#### 2. __LePetitPrince__（5星）
**关键亮点**：  
- 不显式建树，直接维护两个栈分别计算两种替换策略的结果。  
- 通过符号位唯一对应子串的特性，仅需遍历一次即可统计结果不同的节点数。  
**代码核心**：
```cpp
stack<int> ast, ost; // 分别存储全 & 和全 | 的中间结果
for (auto c : s) {
    if (c 是数字) ast/ost 压入数值;
    else {
        // 弹栈计算两种替换策略的结果
        if (ast.top() ^ ost.top()) ans++; // 结果不同则计数
    }
}
```
**心得**：后缀表达式每个符号位唯一对应一个子串，极大简化问题。

#### 3. lmgoat（4星）
**关键亮点**：  
- 动态规划思路，记录每个节点能否得到 0/1。  
- 利用表达式树结构传递状态，统计满足条件的节点数。  
**转移逻辑**：
```cpp
if (op == '?') 
    f[x][0] = (左子树能为0 || 右子树能为0);
    f[x][1] = (左子树能为1 || 右子树能为1);
```
**优点**：状态定义清晰，适合扩展更多复杂条件。

---

### 最优技巧总结
1. **贪心极值替换**：将 `?` 替换为两种极端运算符，只需两次计算即可覆盖所有可能。  
2. **栈式处理代替显式建树**：直接通过栈维护中间结果，节省内存且代码更简洁。  
3. **后缀表达式特性利用**：每个符号位唯一对应一个合法子串，避免重复计算。

---

### 拓展训练
1. **P1494 [CSP-J2020] 表达式**（后缀表达式求值与性质分析）  
2. **P7073 [CSP-J2021] 表达式求值**（运算符优先级与替换策略）  
3. **P1981 [NOIP2013 普及组] 表达式求值**（栈模拟与运算符处理）

---
处理用时：67.49秒