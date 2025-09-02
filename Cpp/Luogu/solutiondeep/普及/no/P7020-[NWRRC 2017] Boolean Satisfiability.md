# 题目信息

# [NWRRC 2017] Boolean Satisfiability

## 题目描述



Boolean satisfiability problem (SAT) is known to be a very hard problem in computer science. In this problem you are given a Boolean formula, and you need to find out if the variables of a given formula can be consistently replaced by the values true or false in such a way that the formula evaluates to true. SAT is known to be NP-complete problem. Moreover, it is NP-complete even in case of $3-CNF$ formula $(3-SAT).$ However, for example, SAT problem for $2-CNF$ formulae $(2-SAT)$ is in $P$ .

$#SAT$ is the extension of SAT problem. In this problem you need to check if it is possible, and count the number of ways to assign values to variables. This problem is known to be $#P-complete$ even for $2-CNF$ formulae. We ask you to solve $#1-DNF-SAT,$ which is $#SAT$ problem for $1-DNF$ formulae.

You are given a Boolean formula in $1-DNF$ form. It means that it is a disjunction (logical or) of one or more clauses, each clause is exactly one literal, each literal is either variable or its negation (logical not).

Formally:

$〈formula〉 ::= 〈clause〉 | 〈formula〉 ∨ 〈clause〉$

$〈clause〉 ::= 〈literal〉$

$〈literal〉 ::= 〈variable〉 | ¬ 〈variable〉$

$〈variable〉 ::=$ A . . . $Z |$ a . . . $z$

Your task is to find the number of ways to replace all variables with values true and false (all occurrences of the same variable should be replaced with same value), such that the formula evaluates to true.



## 说明/提示

Time limit: 3 s, Memory limit: 512 MB. 



## 样例 #1

### 输入

```
a
```

### 输出

```
1
```

## 样例 #2

### 输入

```
B|~B
```

### 输出

```
2
```

## 样例 #3

### 输入

```
c|~C
```

### 输出

```
3
```

## 样例 #4

### 输入

```
i|c|p|c
```

### 输出

```
7
```

# AI分析结果



**算法分类**: 数学

**综合分析与结论**  
本题解需统计布尔表达式满足条件的变量赋值数目。关键思路是：若存在变量与其否定形式同时出现，则无论其他变量如何取值，结果恒为真（方案数 $2^n$）；否则需排除全假情况（方案数 $2^n-1$）。所有题解均围绕此核心展开，通过统计变量出现情况判断最终结果。

**精选题解**  
1. **A_grasser（4星）**  
   - **关键亮点**: 使用双 `map` 结构记录变量是否以原变量/否定形式出现，代码逻辑清晰，变量去重处理完善。  
   - **核心实现**:  
     ```cpp
     for (int i = 0; i < s.size(); i++) {
         if (isalpha(s[i])) {
             char op = (s[i-1] == '~' ? 1 : 0);
             mp[op][s[i]] = 1;
             if (!used[s[i]]) {
                 operators.push_back(s[i]);
                 used[s[i]] = 1;
             }
         }
     }
     ```
     - 遍历字符串，记录变量出现形式，并去重统计变量总数。

2. **Flaw_Owl（4星）**  
   - **关键亮点**: 使用二维数组分别存储大小写字母的正/反出现情况，直接通过位运算判断结果。  
   - **核心实现**:  
     ```cpp
     for (int i = 0; i < s.size(); i++) {
         if (s[i] >= 'a' && s[i] <= 'z') {
             int idx = (s[i-1] == '~' ? 0 : 1);
             word[idx][s[i] - 'a'] = true;
         }
         // 类似处理大写字母
     }
     ```
     - 分类统计字母的正/反情况，避免混淆大小写。

3. **落花月朦胧（4星）**  
   - **关键亮点**: 简洁的 `set` 去重与 `map` 状态记录结合，代码简短高效。  
   - **核心实现**:  
     ```cpp
     if (s[i - 1] == '~') mp[1][s[i]] = 1;
     else mp[0][s[i]] = 1;
     ss.insert(s[i]); // 自动去重
     ```
     - 利用 `set` 自动去重，简化变量计数逻辑。

**最优关键思路**  
- **变量冲突检测**：若某变量及其否定同时出现，直接返回 $2^n$。  
- **快速幂计算**：通过位运算计算 $2^n$，避免溢出（使用 `1LL << n`）。  
- **去重技巧**：利用 `map` 或 `set` 自动处理重复变量，确保统计准确。

**拓展与同类题**  
- **类似题目**:  
  1. [P1495 曹冲养猪](https://www.luogu.com.cn/problem/P1495)（同余方程与组合计数）  
  2. [P2114 [NOI2014] 起床困难综合症](https://www.luogu.com.cn/problem/P2114)（位运算与最优策略）  
  3. [P5657 格雷码](https://www.luogu.com.cn/problem/P5657)（二进制编码与构造）  

**个人心得摘录**  
- **查重陷阱**：需注意同一变量多次出现的情况，如 `i|c|p|c` 中 `c` 出现两次，但只计为一个变量（A_grasser）。  
- **大小写处理**：明确区分大小写变量（如 `c` 和 `C` 不同），避免统计错误（Flaw_Owl）。

---
处理用时：53.43秒