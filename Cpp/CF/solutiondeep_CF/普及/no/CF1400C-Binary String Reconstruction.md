# 题目信息

# Binary String Reconstruction

## 题目描述

Consider the following process. You have a binary string (a string where each character is either 0 or 1) $ w $ of length $ n $ and an integer $ x $ . You build a new binary string $ s $ consisting of $ n $ characters. The $ i $ -th character of $ s $ is chosen as follows:

- if the character $ w_{i-x} $ exists and is equal to 1, then $ s_i $ is 1 (formally, if $ i         > x $ and $ w_{i-x} =  $ 1, then $ s_i =  $ 1);
- if the character $ w_{i+x} $ exists and is equal to 1, then $ s_i $ is 1 (formally, if $ i + x \le         n $ and $ w_{i+x} =  $ 1, then $ s_i =  $ 1);
- if both of the aforementioned conditions are false, then $ s_i $ is 0.

You are given the integer $ x $ and the resulting string $ s $ . Reconstruct the original string $ w $ .

## 样例 #1

### 输入

```
3
101110
2
01
1
110
1```

### 输出

```
111011
10
-1```

# AI分析结果

### 题目内容重写（中文）

#### 二进制字符串重构

**题目描述**

考虑以下过程。你有一个长度为 $n$ 的二进制字符串 $w$（每个字符为 `0` 或 `1`）和一个整数 $x$。你构建一个新的二进制字符串 $s$，长度为 $n$。$s$ 的第 $i$ 个字符按如下规则选择：

- 如果字符 $w_{i-x}$ 存在且等于 `1`，则 $s_i$ 为 `1`（形式化地，如果 $i > x$ 且 $w_{i-x} = 1$，则 $s_i = 1$）；
- 如果字符 $w_{i+x}$ 存在且等于 `1`，则 $s_i$ 为 `1`（形式化地，如果 $i + x \le n$ 且 $w_{i+x} = 1$，则 $s_i = 1$）；
- 如果上述两个条件均不满足，则 $s_i$ 为 `0`。

给定整数 $x$ 和结果字符串 $s$，要求重构原始字符串 $w$。

**样例 #1**

**输入**

```
3
101110
2
01
1
110
1
```

**输出**

```
111011
10
-1
```

### 算法分类
构造

### 题解分析与结论

#### 题解对比与总结

1. **共同思路**：
   - 所有题解都采用了类似的思路：首先根据 $s_i = 0$ 的情况，确定 $w$ 中某些位置必须为 `0`，然后根据 $s_i = 1$ 的情况，检查这些位置是否满足条件，若不满足则无解。
   - 大部分题解都采用了贪心的策略，先假设 $w$ 中所有位置为 `1`，然后根据 $s_i = 0$ 的情况进行调整。

2. **难点与优化**：
   - 难点在于如何高效地处理 $s_i = 1$ 的情况，确保 $w$ 的构造满足所有条件。
   - 优化点在于如何减少不必要的遍历和判断，例如通过标记数组或直接赋值来避免重复检查。

3. **代码实现**：
   - 大部分题解的代码实现较为简洁，但部分题解在代码可读性和优化程度上有所差异。

#### 精选题解

1. **作者：_•́へ•́╬_ (赞：5)**
   - **星级**：★★★★★
   - **关键亮点**：思路清晰，代码简洁，直接通过标记数组处理 $s_i = 0$ 的情况，然后检查 $s_i = 1$ 的情况，判断是否无解。
   - **代码核心**：
     ```cpp
     for(register int i=0;i<n;++i)if(s[i]=='0')
     {
         if(i-x>=0)w[i-x]='0';
         if(i+x<n)w[i+x]='0';
     }
     for(register int i=0;i<n;++i)
         if(s[i]=='1'&&(i-x<0||w[i-x]=='0')&&(i+x>=n||w[i+x]=='0')){f=1;break;}
     ```

2. **作者：邓布利多6 (赞：5)**
   - **星级**：★★★★★
   - **关键亮点**：代码结构清晰，使用了 `string` 类型，便于操作和输出，逻辑与第一题解类似，但代码可读性更高。
   - **代码核心**：
     ```cpp
     for(int i = 0; i < n; i++) if(s[i] == '0')
     {
         if(i - x >= 0) ans[i - x] = '0';
         if(i + x < n)  ans[i + x] = '0';
     }
     for(int i = 0; i < n; i++) if(s[i] == '1')
     {
         f1 = f2 = 0;
         if(i - x >= 0) f1 = (ans[i - x] == '1');
         if(i + x < n)  f2 = (ans[i + x] == '1');
         if(!f1 && !f2) { cout << -1 << endl; flag = true; break; }
     }
     ```

3. **作者：ZigZagKmp (赞：2)**
   - **星级**：★★★★
   - **关键亮点**：思路与前述题解一致，但代码实现较为复杂，使用了 `goto` 语句来处理无解情况，代码可读性稍差。
   - **代码核心**：
     ```cpp
     for(int i = 1; i <= len; ++i) {
         if(ch[i] == '0') {
             if(i - x > 0) vis[i - x] = 1;
             if(i + x <= len) vis[i + x] = 1;
         }
     }
     for(int i = 1; i <= len; ++i) {
         if(ch[i] == '1') {
             if(i - x > 0) {
                 if(vis[i - x]) {
                     if(i + x <= len) {
                         if(vis[i + x]) goto school;
                         else s[i + x] = '1';
                     } else goto school;
                 } else s[i - x] = '1';
             } else if(i + x <= len) {
                 if(vis[i + x]) goto school;
                 else s[i + x] = '1';
             } else goto school;
         }
     }
     ```

### 最优关键思路或技巧
- **贪心策略**：先假设 $w$ 中所有位置为 `1`，然后根据 $s_i = 0$ 的情况进行调整，确保 $w$ 的构造满足所有条件。
- **标记数组**：使用标记数组记录 $w$ 中必须为 `0` 的位置，减少不必要的遍历和判断。

### 可拓展之处
- 类似的问题可以扩展到多维数组或多重条件的情况，例如在二维网格中进行类似的构造问题。
- 可以结合其他算法，如动态规划或图论，处理更复杂的条件约束。

### 推荐题目
1. [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)
2. [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)
3. [P1056 排座椅](https://www.luogu.com.cn/problem/P1056)

### 个人心得摘录
- **调试经历**：部分题解在调试过程中发现，处理 $s_i = 1$ 的情况时，容易遗漏某些边界条件，导致无解判断错误。
- **踩坑教训**：在处理数组越界时，需要特别注意边界条件，避免程序崩溃或错误输出。
- **顿悟感想**：通过贪心策略和标记数组的结合，可以高效地解决这类构造问题，减少不必要的计算和判断。

---
处理用时：47.79秒