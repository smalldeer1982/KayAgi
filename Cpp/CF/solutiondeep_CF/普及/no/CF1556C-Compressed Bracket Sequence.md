# 题目信息

# Compressed Bracket Sequence

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1556C/3e1271d095f65d6764f1796fd73b8947fda1c3d9.png)William has a favorite bracket sequence. Since his favorite sequence is quite big he provided it to you as a sequence of positive integers $ c_1, c_2, \dots, c_n $ where $ c_i $ is the number of consecutive brackets "(" if $ i $ is an odd number or the number of consecutive brackets ")" if $ i $ is an even number.

For example for a bracket sequence "((())()))" a corresponding sequence of numbers is $ [3, 2, 1, 3] $ .

You need to find the total number of continuous subsequences (subsegments) $ [l, r] $ ( $ l \le r $ ) of the original bracket sequence, which are regular bracket sequences.

A bracket sequence is called regular if it is possible to obtain correct arithmetic expression by inserting characters "+" and "1" into this sequence. For example, sequences "(())()", "()" and "(()(()))" are regular, while ")(", "(()" and "(()))(" are not.

## 说明/提示

In the first example a sequence (((()(()))( is described. This bracket sequence contains $ 5 $ subsegments which form regular bracket sequences:

1. Subsequence from the $ 3 $ rd to $ 10 $ th character: (()(()))
2. Subsequence from the $ 4 $ th to $ 5 $ th character: ()
3. Subsequence from the $ 4 $ th to $ 9 $ th character: ()(())
4. Subsequence from the $ 6 $ th to $ 9 $ th character: (())
5. Subsequence from the $ 7 $ th to $ 8 $ th character: ()

In the second example a sequence ()))(()(()))) is described.

In the third example a sequence ()()(()) is described.

## 样例 #1

### 输入

```
5
4 1 2 3 1```

### 输出

```
5```

## 样例 #2

### 输入

```
6
1 3 2 1 2 4```

### 输出

```
6```

## 样例 #3

### 输入

```
6
1 1 1 1 2 2```

### 输出

```
7```

# AI分析结果

### 题目内容重写

#### 题目描述

William 有一个最喜欢的括号序列。由于这个序列非常大，他将其表示为一系列正整数 $c_1, c_2, \dots, c_n$，其中 $c_i$ 表示连续的左括号 "(" 的数量（如果 $i$ 是奇数）或连续的右括号 ")" 的数量（如果 $i$ 是偶数）。

例如，对于括号序列 "((())()))"，对应的数字序列是 $[3, 2, 1, 3]$。

你需要找到原始括号序列中所有连续子序列（子段）$[l, r]$（$l \le r$）的数量，这些子序列是合法的括号序列。

一个括号序列被称为合法的，如果可以通过在这个序列中插入字符 "+" 和 "1" 来得到一个正确的算术表达式。例如，序列 "(())()", "()" 和 "(()(()))" 是合法的，而 ")(", "(()" 和 "(()))(" 不是。

#### 说明/提示

在第一个例子中，序列 (((()(()))( 被描述。这个括号序列包含 $5$ 个子段，这些子段形成合法的括号序列：

1. 从第 $3$ 个字符到第 $10$ 个字符的子序列：(()(()))
2. 从第 $4$ 个字符到第 $5$ 个字符的子序列：()
3. 从第 $4$ 个字符到第 $9$ 个字符的子序列：()(())
4. 从第 $6$ 个字符到第 $9$ 个字符的子序列：(())
5. 从第 $7$ 个字符到第 $8$ 个字符的子序列：()

在第二个例子中，序列 ()))(()(()))) 被描述。

在第三个例子中，序列 ()()(()) 被描述。

#### 样例 #1

##### 输入

```
5
4 1 2 3 1
```

##### 输出

```
5
```

#### 样例 #2

##### 输入

```
6
1 3 2 1 2 4
```

##### 输出

```
6
```

#### 样例 #3

##### 输入

```
6
1 1 1 1 2 2
```

##### 输出

```
7
```

### 算法分类
动态规划

### 题解分析与结论

本题的核心在于如何高效地统计所有合法的括号子序列。由于括号序列的合法性要求严格，直接枚举所有子序列的复杂度较高，因此需要采用更高效的算法。

### 所选高分题解

#### 题解1：maruize (5星)
**关键亮点**：通过将括号序列转化为折线图，利用单调栈维护山谷和山峰的高度，从而高效计算合法子序列的数量。时间复杂度为 $O(n)$。

**核心代码**：
```cpp
int ans=0;
for(int i=1;i<n;i+=2){
	ans+=h[i]-max(h[i]-a[i+1],st[1].fs);
	while(top>0&&st[top].fs>h[i+1]){
		if(top>1)ans+=st[top].sc;
		top--;
	}
	if(st[top].fs!=h[i+1])st[++top]=pii(h[i+1],1);
	else ans+=st[top].sc,st[top].sc++;
}
printf(ans);
```

#### 题解2：Zxsoul (4星)
**关键亮点**：通过枚举每个左括号，计算其与后续右括号的匹配情况，利用组合贡献的思想统计合法子序列的数量。时间复杂度为 $O(n^2)$。

**核心代码**：
```cpp
int ans=0;
for(int i=1;i<=n;i+=2){
	int res=a[i]-1;
	int tot=a[i];
	for(int j=i+1;j<=n;j+=2){
		ans+=max(0ll,res-max(0ll,tot-a[j])+1ll);
		tot-=a[j];
		if(tot<0) break;
		res=min(tot,res);
		tot+=a[j+1];
	}
}
printf("%lld",ans);
```

#### 题解3：vectorwyx (4星)
**关键亮点**：利用单调栈维护山谷和山峰的高度，通过扫描线的方式计算合法子序列的数量。时间复杂度为 $O(n)$。

**核心代码**：
```cpp
int ans=0;
for(int i=1;i<n;i+=2){
	ans+=h[i]-max(h[i]-a[i+1],st[1].fs);
	while(top>0&&st[top].fs>h[i+1]){
		if(top>1)ans+=st[top].sc;
		top--;
	}
	if(st[top].fs!=h[i+1])st[++top]=pii(h[i+1],1);
	else ans+=st[top].sc,st[top].sc++;
}
printf(ans);
```

### 最优关键思路与技巧
1. **折线图与单调栈**：将括号序列转化为折线图，利用单调栈维护山谷和山峰的高度，从而高效计算合法子序列的数量。
2. **组合贡献**：通过枚举每个左括号，计算其与后续右括号的匹配情况，利用组合贡献的思想统计合法子序列的数量。
3. **扫描线**：利用扫描线的方式，从左到右处理每个下降折线上的所有点，计算合法子序列的数量。

### 可拓展之处
1. **类似问题**：可以扩展到其他类型的括号匹配问题，如不同类型的括号（如花括号、方括号）的匹配。
2. **算法优化**：可以进一步优化算法，减少时间复杂度，如利用更高效的数据结构或算法。

### 推荐题目
1. [P1040 加分二叉树](https://www.luogu.com.cn/problem/P1040)
2. [P1044 栈](https://www.luogu.com.cn/problem/P1044)
3. [P1045 麦森数](https://www.luogu.com.cn/problem/P1045)

### 个人心得
1. **调试经历**：在实现单调栈时，需要注意栈的维护和更新，特别是在弹栈时需要正确处理贡献的计算。
2. **踩坑教训**：在处理组合贡献时，需要注意边界条件的处理，避免重复计算或遗漏。
3. **顿悟感想**：通过将问题转化为折线图，可以更直观地理解问题的本质，从而设计出更高效的算法。

---
处理用时：43.37秒