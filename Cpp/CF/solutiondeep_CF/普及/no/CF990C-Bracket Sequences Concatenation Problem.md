# 题目信息

# Bracket Sequences Concatenation Problem

## 题目描述

A bracket sequence is a string containing only characters "(" and ")".

A regular bracket sequence is a bracket sequence that can be transformed into a correct arithmetic expression by inserting characters "1" and "+" between the original characters of the sequence. For example, bracket sequences "()()", "(())" are regular (the resulting expressions are: "(1)+(1)", "((1+1)+1)"), and ")(" and "(" are not.

You are given $ n $ bracket sequences $ s_1, s_2, \dots , s_n $ . Calculate the number of pairs $ i, j \, (1 \le i, j \le n) $ such that the bracket sequence $ s_i + s_j $ is a regular bracket sequence. Operation $ + $ means concatenation i.e. "()(" + ")()" = "()()()".

If $ s_i + s_j $ and $ s_j + s_i $ are regular bracket sequences and $ i \ne j $ , then both pairs $ (i, j) $ and $ (j, i) $ must be counted in the answer. Also, if $ s_i + s_i $ is a regular bracket sequence, the pair $ (i, i) $ must be counted in the answer.

## 说明/提示

In the first example, suitable pairs are $ (3, 1) $ and $ (2, 2) $ .

In the second example, any pair is suitable, namely $ (1, 1), (1, 2), (2, 1), (2, 2) $ .

## 样例 #1

### 输入

```
3
)
()
(
```

### 输出

```
2
```

## 样例 #2

### 输入

```
2
()
()
```

### 输出

```
4
```

# AI分析结果

### 题目内容重写

#### 题目描述

一个括号序列是一个只包含字符 `(` 和 `)` 的字符串。

一个合法的括号序列是指可以通过在原始序列的字符之间插入字符 `1` 和 `+` 来转换为一个正确的算术表达式的括号序列。例如，括号序列 `()()` 和 `(())` 是合法的（转换后的表达式分别为 `(1)+(1)` 和 `((1+1)+1)`），而 `)(` 和 `(` 不是合法的。

给定 $n$ 个括号序列 $s_1, s_2, \dots , s_n$，计算满足 $s_i + s_j$ 是合法括号序列的 $(i, j)$ 对数，其中 $1 \le i, j \le n$。操作 $+$ 表示字符串的拼接，例如 `()(` + `)()` = `()()()`。

如果 $s_i + s_j$ 和 $s_j + s_i$ 都是合法的括号序列且 $i \ne j$，那么 $(i, j)$ 和 $(j, i)$ 都应该被计入答案。此外，如果 $s_i + s_i$ 是合法的括号序列，那么 $(i, i)$ 也应该被计入答案。

#### 说明/提示

在第一个样例中，合适的对是 $(3, 1)$ 和 $(2, 2)$。

在第二个样例中，任何对都是合适的，即 $(1, 1), (1, 2), (2, 1), (2, 2)$。

#### 样例 #1

##### 输入

```
3
)
()
(
```

##### 输出

```
2
```

#### 样例 #2

##### 输入

```
2
()
()
```

##### 输出

```
4
```

### 算法分类
字符串

### 题解分析与结论

#### 综合分析
本题的核心在于如何判断两个括号序列拼接后是否合法。通过栈的模拟匹配过程，可以有效地计算每个序列中未匹配的左括号和右括号的数量。最终，通过统计这些数量的匹配情况，可以快速计算出符合条件的对数。

#### 题解评分与亮点

1. **作者：yuheng_wang080904 (赞：2)**
   - **星级：4**
   - **关键亮点**：使用栈来模拟匹配过程，记录每个序列中未匹配的左括号和右括号的数量，并通过数组统计这些数量，最终通过遍历数组计算符合条件的对数。
   - **代码实现**：
     ```cpp
     for (int i = 1; i <= n; i++) {
         scanf("%s", str + 1);
         int l = strlen(str + 1), tp = 0;
         for (int j = 1; j <= l; j++) {
             if (str[j] == '(') ++tp;
             else if (tp > 0) --tp;
             else { tp = -1; break; }
         }
         if (tp >= 0) ++cnta[tp];
         m = max(m, tp);
         tp = 0;
         for (int j = l; j > 0; j--) {
             if (str[j] == ')') ++tp;
             else if (tp > 0) --tp;
             else { tp = -1; break; }
         }
         if (tp >= 0) ++cntb[tp];
         m = max(m, tp);
     }
     ll res = 0;
     for (int i = 0; i <= m; i++)
         res = res + (ll)cnta[i] * cntb[i];
     printf("%lld\n", res);
     ```

2. **作者：ZettaByte (赞：0)**
   - **星级：4**
   - **关键亮点**：通过栈消去已匹配的括号，记录未匹配的左括号和右括号的数量，并使用桶来统计这些数量，最终通过遍历桶计算符合条件的对数。
   - **代码实现**：
     ```cpp
     for (ll i = 1; i <= n; i++) {
         ll sss = 0;
         for (ll j = 0; j < (ll)s[i].size(); j++)
             if (s[i][j] == '(') sss++;
             else if (!sss) y[i]++;
             else sss--;
         z[i] = sss;
     }
     for (ll i = 1; i <= n; i++) {
         if (!y[i]) t1[z[i]]++;
         if (!z[i]) t2[y[i]]++;
     }
     for (ll i = 1; i <= n; i++) {
         if (!y[i] && !z[i]) { ret += t1[0]; continue; }
         if (!y[i]) ret += t2[z[i]];
     } printf("%lld\n", ret);
     ```

3. **作者：sdxjzsq (赞：0)**
   - **星级：4**
   - **关键亮点**：通过栈模拟匹配过程，将括号序列分类为只能放在左边、只能放在右边或两边都可以放的序列，并使用数组记录这些序列的数量，最终通过遍历数组计算符合条件的对数。
   - **代码实现**：
     ```cpp
     for(register int i=1;i<=n;i++) {
         scanf("%s",s);
         int len=strlen(s);
         int ll=0,rr=0,tag=0,maxr=0;
         for(register int j=0;j<len;j++) {
             if(s[j]=='(')ll++;
             else {
                 rr++;
                 if(rr>ll)tag=1,maxr=max(maxr,rr-ll);
             }
         }
         if(tag) {
             if(ll==rr-maxr) {
                 r[rr-ll]++;
                 if(rr-ll>rmax)rmax=rr-ll;
             }
         }
         else {
             l[ll-rr]++;
             if(ll-rr>lmax)lmax=ll-rr;
         }
     }
     lmax=min(lmax,rmax);
     for(register int i=1;i<=lmax;i++)
         ans+=l[i]*r[i];
     ans+=l[0]*l[0];
     printf("%lld",ans);
     ```

### 最优关键思路或技巧
1. **栈的模拟匹配**：通过栈来模拟括号的匹配过程，记录未匹配的左括号和右括号的数量。
2. **桶统计**：使用数组（桶）来统计不同未匹配括号数量的序列，便于快速计算符合条件的对数。
3. **分类处理**：将括号序列分类为只能放在左边、只能放在右边或两边都可以放的序列，简化问题。

### 可拓展之处
1. **类似问题**：可以扩展到其他类型的括号匹配问题，如包含多种括号（`{}`, `[]`）的序列。
2. **算法优化**：可以考虑进一步优化统计和计算过程，减少时间复杂度。

### 推荐题目
1. [P1739 表达式括号匹配](https://www.luogu.com.cn/problem/P1739)
2. [P1044 栈](https://www.luogu.com.cn/problem/P1044)
3. [P1449 后缀表达式](https://www.luogu.com.cn/problem/P1449)

---
处理用时：43.84秒