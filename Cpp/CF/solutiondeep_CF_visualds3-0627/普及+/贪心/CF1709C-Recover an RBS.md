# 题目信息

# Recover an RBS

## 题目描述

A bracket sequence is a string containing only characters "(" and ")". A regular bracket sequence (or, shortly, an RBS) is a bracket sequence that can be transformed into a correct arithmetic expression by inserting characters "1" and "+" between the original characters of the sequence. For example:

- bracket sequences "()()" and "(())" are regular (the resulting expressions are: "(1)+(1)" and "((1+1)+1)");
- bracket sequences ")(", "(" and ")" are not.

There was an RBS. Some brackets have been replaced with question marks. Is it true that there is a unique way to replace question marks with brackets, so that the resulting sequence is an RBS?

## 说明/提示

In the first testcase, the only possible original RBS is "(())".

In the second testcase, there are multiple ways to recover an RBS.

In the third and the fourth testcases, the only possible original RBS is "()".

In the fifth testcase, the original RBS can be either "((()()))" or "(())()()".

## 样例 #1

### 输入

```
5
(?))
??????
()
??
?(?)()?)```

### 输出

```
YES
NO
YES
YES
NO```

# AI分析结果



### 综合分析与结论

**题目核心**：给定带有问号的括号序列，判断是否存在唯一替换方式使其成为合法括号序列（RBS）。关键在于保证前缀和始终非负且最终平衡。

**核心思路与难点**：
1. **前缀和动态调整**：遍历时维护当前确定的前缀和（`cnt`）和未处理的问号数（`qry`）。当 `cnt + qry == 1` 时，强制当前问号为左括号，确保后续合法。最终检查 `|cnt| == qry` 判断唯一性。
2. **贪心构造 + 交换验证**：构造一个合法解（尽可能多填左括号），交换最后一个左括号问号和第一个右括号问号，检查新解是否合法。若合法则存在多解。

**贪心策略可视化设计**：
- **动态前缀和曲线**：以折线图展示前缀和变化，用红色标记必须确定问号为左括号的位置。
- **构造解动画**：分步填充问号为左/右括号，高亮交换位置，验证新解时显示前缀和是否跌破零。
- **复古像素风格**：用 8-bit 像素块表示括号，音效提示关键决策（如强制左括号时播放“确认”音效）。

---

### 题解评分（≥4星）

1. **BigSmall_En（★★★★☆）**  
   - **亮点**：O(n) 时间，代码简洁。通过动态维护前缀和和问号数，避免构造具体解。  
   - **代码片段**：
     ```cpp
     if (cnt + qry == 1) cnt = 1, qry = 0; // 强制左括号
     if (abs(cnt) == qry) puts("YES");     // 唯一性判断
     ```

2. **Jr_Zlw（★★★★☆）**  
   - **亮点**：构造合法解后交换验证，思路直观。代码明确处理了问号填充顺序和交换逻辑。  
   - **关键代码**：
     ```cpp
     // 构造解：前L个?填左括号，其余填右括号
     // 交换最后一个左括号?和第一个右括号?
     swap(a[l], a[r]);
     // 重新验证前缀和
     ```

3. **Jeremiahy（★★★★☆）**  
   - **亮点**：代码简洁，直接交换并验证。通过两次遍历构造解和验证，逻辑清晰。  
   - **核心逻辑**：
     ```cpp
     // 构造初始解后，交换并检查新解合法性
     if (check(modified_str)) cout << "NO"; // 存在多解
     ```

---

### 最优思路提炼

**前缀和动态调整法**（BigSmall_En）：
- **关键条件**：当 `cnt + qry == 1` 时，必须将当前问号设为左括号，否则后续无法维持非负前缀。
- **数学依据**：若最终 `|cnt| == qry`，剩余问号必须全部为右（左）括号，确保唯一性。

**贪心构造法**（Jr_Zlw/Jeremiahy）：
- **构造策略**：优先填左括号，保证前缀和最大化。
- **交换验证**：交换最晚的左括号问号和最早的右括号问号，若新解合法则存在多解。

---

### 同类型题与算法套路

**通用贪心场景**：
- **括号匹配**：尽可能多填左括号，维护前缀和非负。
- **交换验证**：通过局部调整判断全局唯一性。

**推荐题目**：
1. [CF3D - Least Cost Bracket Sequence](https://codeforces.com/problemset/problem/3/D)  
2. [LeetCode 678 - Valid Parenthesis String](https://leetcode.com/problems/valid-parenthesis-string/)  
3. [LeetCode 2116 - Check if a Parentheses String Can Be Valid](https://leetcode.com/problems/check-if-a-parentheses-string-can-be-valid/)

---

### 个人心得摘录

- **BigSmall_En**：初始错误条件 `!cnt && qry==1` 被 hack 数据 `?????))))?` 暴露逻辑漏洞，修正为 `cnt+qry==1`。
- **Jr_Zlw**：构造解时需保证左括号数量严格为 `n/2`，否则无法通过交换生成新解。
- **yukimianyan**：通过 ST 表预处理前缀和最小值，二分查找可交换区间，确保正确性但实现复杂。

---

### 可视化与算法演示

**动态前缀和演示**：
1. **初始状态**：显示字符串，问号标记为灰色。
2. **遍历过程**：高亮当前字符，更新前缀和曲线。当触发 `cnt+qry==1` 时，问号变红（强制左括号）。
3. **最终判断**：显示 `cnt` 和 `qry` 的关系，绿色表示唯一，红色表示多解。

**复古像素动画**：
- **像素风格**：括号用 16x16 像素块，`(` 为绿色，`)` 为红色，`?` 闪烁黄色。
- **音效设计**：
  - **强制左括号**：8-bit “确认”音效。
  - **唯一解**：胜利音效；多解：错误音效。
- **交互控制**：方向键步进，空格暂停，Enter 重放。

---

**代码片段（贪心构造法）**：
```cpp
// 构造初始解
int L = n/2 - cnt_left;
for (int i=0; i<s.size(); i++) {
    if (s[i] == '?') {
        if (L > 0) s[i] = '(', L--;
        else s[i] = ')';
    }
}

// 交换并验证
int last_left = -1, first_right = -1;
for (int i=0; i<s.size(); i++) {
    if (s[i] == '(' && original_is_question(i)) last_left = i;
}
for (int i=0; i<s.size(); i++) {
    if (s[i] == ')' && original_is_question(i)) { first_right = i; break; }
}
swap(s[last_left], s[first_right]);
if (is_valid(s)) cout << "NO"; // 存在多解
```

---
处理用时：97.95秒