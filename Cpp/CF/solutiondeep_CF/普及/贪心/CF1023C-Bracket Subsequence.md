# 题目信息

# Bracket Subsequence

## 题目描述

A bracket sequence is a string containing only characters "(" and ")". A regular bracket sequence is a bracket sequence that can be transformed into a correct arithmetic expression by inserting characters "1" and "+" between the original characters of the sequence. For example, bracket sequences "()()" and "(())" are regular (the resulting expressions are: "(1)+(1)" and "((1+1)+1)"), and ")(", "(" and ")" are not.

Subsequence is a sequence that can be derived from another sequence by deleting some elements without changing the order of the remaining elements.

You are given a regular bracket sequence $ s $ and an integer number $ k $ . Your task is to find a regular bracket sequence of length exactly $ k $ such that it is also a subsequence of $ s $ .

It is guaranteed that such sequence always exists.

## 样例 #1

### 输入

```
6 4
()(())
```

### 输出

```
()()
```

## 样例 #2

### 输入

```
8 8
(()(()))
```

### 输出

```
(()(()))
```

# AI分析结果

### 题目内容重写

#### 题目描述

一个括号序列是一个仅包含字符 `(` 和 `)` 的字符串。一个正则括号序列是指可以通过在原序列的字符之间插入字符 `1` 和 `+` 来转换为一个正确的算术表达式的括号序列。例如，括号序列 `()()` 和 `(())` 是正则的（转换后的表达式分别为 `(1)+(1)` 和 `((1+1)+1)`），而 `)(`、`(` 和 `)` 不是。

子序列是指可以通过从另一个序列中删除一些元素而不改变剩余元素的顺序得到的序列。

给定一个正则括号序列 $s$ 和一个整数 $k$，你的任务是找到一个长度恰好为 $k$ 的正则括号序列，且它是 $s$ 的子序列。

保证这样的序列总是存在。

#### 样例 #1

##### 输入

```
6 4
()(())
```

##### 输出

```
()()
```

#### 样例 #2

##### 输入

```
8 8
(()(()))
```

##### 输出

```
(()(()))
```

---

### 题解分析与结论

#### 综合分析与结论

本题的核心目标是从给定的正则括号序列中提取一个长度为 $k$ 的正则括号子序列。由于正则括号序列的左右括号数量必须相等，因此 $k$ 必须是偶数。题解的主要思路是通过贪心算法，从左到右扫描原序列，优先选择左括号，直到左括号数量达到 $k/2$，然后选择右括号，确保右括号数量不超过左括号数量。

#### 最优关键思路或技巧

1. **贪心算法**：从左到右扫描序列，优先选择左括号，直到左括号数量达到 $k/2$，然后选择右括号，确保右括号数量不超过左括号数量。
2. **边界条件处理**：在扫描过程中，始终检查当前已选择的括号数量是否达到 $k$，如果达到则立即停止。
3. **时间复杂度优化**：由于只需要一次扫描，时间复杂度为 $O(n)$，适合处理大规模数据。

#### 可拓展之处

1. **类似问题**：可以扩展到其他类型的括号序列问题，如处理多种括号类型（如 `{}`、`[]` 等）。
2. **动态规划**：如果需要处理更复杂的子序列问题，可以考虑使用动态规划来优化选择过程。

#### 推荐题目

1. [P1044 栈](https://www.luogu.com.cn/problem/P1044) - 考察栈的应用，与括号匹配相关。
2. [P1739 表达式括号匹配](https://www.luogu.com.cn/problem/P1739) - 直接考察括号匹配问题。
3. [P1241 括号序列](https://www.luogu.com.cn/problem/P1241) - 考察括号序列的合法性判断。

---

### 精选题解

#### 题解1：作者：__CrossBow_EXE__

**星级：4.5**

**关键亮点**：
- 代码简洁，逻辑清晰，直接通过贪心算法实现。
- 使用两个计数器 `l` 和 `r` 分别记录左括号和右括号的数量，确保右括号数量不超过左括号数量。

**核心代码**：
```cpp
int l=0,r=0;
for(int i=1;i<=n;i++){
    if(a[i]=='('&&l<k/2){
        l++;
        cout<<'(';
    }
    if(a[i]==')'&&r<l){
        r++;
        cout<<')';
    }
    if((l+r)==k) return 0;
}
```

#### 题解2：作者：StudyingFather

**星级：4.5**

**关键亮点**：
- 通过 `cntl` 和 `cntr` 分别记录左括号和右括号的数量，确保右括号数量不超过左括号数量。
- 使用 `res` 数组存储结果，最后一次性输出，减少 I/O 操作。

**核心代码**：
```cpp
int cntl=0,cntr=0,tot=0;
for(int i=0;i<n;i++){
    if(s[i]=='('){
        if(cntl!=k/2){
            cntl++;
            res[tot++]='(';
        }
    } else {
        if(cntr!=k/2&&cntl>cntr){
            cntr++;
            res[tot++]=')';
        }
    }
}
printf("%s",res);
```

#### 题解3：作者：Sai_t

**星级：4.0**

**关键亮点**：
- 使用 `ans` 字符串存储结果，通过 `l` 和 `r` 分别记录左括号和右括号的数量，确保右括号数量不超过左括号数量。
- 代码结构清晰，易于理解。

**核心代码**：
```cpp
for(int i=0;i<n;i++){
    if(s[i]=='('){
        if(l*2<k){
            ans+='(';
            l++;
        }
    } else {
        if(r*2<k&&r<l){
            ans+=')';
            r++;
        }
    }
}
cout<<ans<<endl;
```

---

### 个人心得总结

- **调试经历**：在处理右括号时，必须确保右括号数量不超过左括号数量，否则会导致括号不匹配。
- **踩坑教训**：在实现过程中，容易忽略边界条件，如当 `k` 等于 `n` 时，直接输出原序列即可，无需进一步处理。
- **顿悟感想**：贪心算法在处理此类问题时非常高效，尤其是在处理大规模数据时，能够显著减少时间复杂度。

---
处理用时：39.07秒