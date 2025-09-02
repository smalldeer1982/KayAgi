# 题目信息

# Bit Flipping

## 题目描述

You are given a binary string of length $ n $ . You have exactly $ k $ moves. In one move, you must select a single bit. The state of all bits except that bit will get flipped ( $ 0 $ becomes $ 1 $ , $ 1 $ becomes $ 0 $ ). You need to output the lexicographically largest string that you can get after using all $ k $ moves. Also, output the number of times you will select each bit. If there are multiple ways to do this, you may output any of them.

A binary string $ a $ is lexicographically larger than a binary string $ b $ of the same length, if and only if the following holds:

- in the first position where $ a $ and $ b $ differ, the string $ a $ contains a $ 1 $ , and the string $ b $ contains a $ 0 $ .

## 说明/提示

Here is the explanation for the first testcase. Each step shows how the binary string changes in a move.

- Choose bit $ 1 $ : $ \color{red}{\underline{1}00001} \rightarrow \color{red}{\underline{1}}\color{blue}{11110} $ .
- Choose bit $ 4 $ : $ \color{red}{111\underline{1}10} \rightarrow \color{blue}{000}\color{red}{\underline{1}}\color{blue}{01} $ .
- Choose bit $ 4 $ : $ \color{red}{000\underline{1}01} \rightarrow \color{blue}{111}\color{red}{\underline{1}}\color{blue}{10} $ .

 The final string is $ 111110 $ and this is the lexicographically largest string we can get.

## 样例 #1

### 输入

```
6
6 3
100001
6 4
100011
6 0
000000
6 1
111001
6 11
101100
6 12
001110```

### 输出

```
111110
1 0 0 2 0 0 
111110
0 1 1 1 0 1 
000000
0 0 0 0 0 0 
100110
1 0 0 0 0 0 
111111
1 2 1 3 0 4 
111110
1 1 4 2 0 4```

# AI分析结果

### 题目内容重写（中文）

#### 位翻转

**题目描述**

给定一个长度为 $n$ 的二进制字符串。你有恰好 $k$ 次操作。在每次操作中，你必须选择一个单独的位。除了这个位之外，所有其他位的状态都会翻转（$0$ 变为 $1$，$1$ 变为 $0$）。你需要输出在使用完所有 $k$ 次操作后，可以得到的最大的字典序字符串。同时，输出你选择每个位的次数。如果有多种方法可以实现这一点，你可以输出其中任意一种。

一个二进制字符串 $a$ 在字典序上大于另一个长度相同的二进制字符串 $b$，当且仅当满足以下条件：

- 在 $a$ 和 $b$ 第一个不同的位置上，$a$ 包含 $1$，而 $b$ 包含 $0$。

**说明/提示**

以下是第一个测试用例的解释。每一步展示了在操作中二进制字符串的变化。

- 选择位 $1$：$ \color{red}{\underline{1}00001} \rightarrow \color{red}{\underline{1}}\color{blue}{11110} $。
- 选择位 $4$：$ \color{red}{111\underline{1}10} \rightarrow \color{blue}{000}\color{red}{\underline{1}}\color{blue}{01} $。
- 选择位 $4$：$ \color{red}{000\underline{1}01} \rightarrow \color{blue}{111}\color{red}{\underline{1}}\color{blue}{10} $。

最终字符串是 $111110$，这是我们可以得到的字典序最大的字符串。

**样例 #1**

**输入**

```
6
6 3
100001
6 4
100011
6 0
000000
6 1
111001
6 11
101100
6 12
001110
```

**输出**

```
111110
1 0 0 2 0 0 
111110
0 1 1 1 0 1 
000000
0 0 0 0 0 0 
100110
1 0 0 0 0 0 
111111
1 2 1 3 0 4 
111110
1 1 4 2 0 4
```

### 题解分析与结论

#### 综合分析

本题的核心在于通过贪心策略，最大化字典序的二进制字符串。所有题解都采用了贪心算法，但在具体实现上有所不同。主要思路包括：

1. **奇偶性处理**：根据 $k$ 的奇偶性，决定如何操作以最大化字典序。
2. **优先处理高位**：从左到右优先处理高位，确保高位尽可能为 $1$。
3. **剩余操作处理**：将剩余的操作次数全部应用到最低位，以减少对字典序的影响。

#### 最优关键思路

- **贪心策略**：优先处理高位，确保高位尽可能为 $1$，从而最大化字典序。
- **奇偶性处理**：根据 $k$ 的奇偶性，决定如何操作以最大化字典序。
- **剩余操作处理**：将剩余的操作次数全部应用到最低位，以减少对字典序的影响。

### 评分较高的题解

#### 题解1：World_Creater（5星）

**关键亮点**：
- 通过将两次操作合并为一次操作，简化了问题。
- 详细解释了奇偶性处理的逻辑，代码清晰易读。
- 贪心策略明确，优先处理高位，确保字典序最大化。

**核心代码**：
```cpp
if(k&1) //对于奇数情况的特殊预处理
{
    int fi=-1;
    for(int i=0;i<n;i++)
    {
        if(s[i]=='1')
        {
            fi=i;
            ans[i]++;
            k--; 
            break;
        }
    }
    if(fi==-1)
    {
        ans[n-1]++;
        fi=n-1;
        k--;
    }
    for(int i=0;i<n;i++)
    {
        if(i!=fi) s[i]=s[i]=='0'?'1':'0';
    }
}
for(int i=0;i<n&&k>0;i++) //贪心将非0位取反
{
    if(s[i]=='0')
    {
        ans[i]++; 
        k--;
        s[i]='1';
    }
}
ans[n-1]+=k; //处理最后1位
if(k&1)
{
    s[n-1]=s[n-1]=='0'?'1':'0';
}
```

#### 题解2：Tx_Lcy（4星）

**关键亮点**：
- 通过奇偶性判断，决定是否对当前位进行操作。
- 将剩余操作次数全部应用到最低位，减少对字典序的影响。
- 代码简洁，逻辑清晰。

**核心代码**：
```cpp
for(int i=1;i<n;++i){
    if(s[i]=='1' && (k&1)) ans[i]=1,++kk;
    else if(s[i]=='0' && (k&1)) ans[i]=0;
    else if(s[i]=='0' && k%2==0) ans[i]=1,++kk;
    else ans[i]=0;
    if(kk==k) break;
}
int la=k-kk;
ans[n]=la;
for(int i=1;i<=n;++i)
    if((k-ans[i])&1){
        if(s[i]=='0') s[i]='1';
        else s[i]='0';
    }
```

### 可拓展之处

- **类似题目**：可以考虑其他涉及字典序最大化或贪心策略的题目，如字符串排序、区间覆盖等。
- **算法套路**：贪心算法在处理最大化或最小化问题时非常有效，尤其是在需要优先处理某些特定条件的情况下。

### 推荐题目

1. **洛谷 P1090**：合并果子（贪心策略）
2. **洛谷 P1223**：排队接水（贪心策略）
3. **洛谷 P1803**：凌乱的yyy / 线段覆盖（贪心策略）

### 个人心得

- **调试经历**：在处理奇偶性时，容易忽略边界情况，如 $k$ 为奇数时没有 $1$ 的情况。
- **踩坑教训**：在贪心策略中，优先处理高位时，需要确保剩余操作次数不会影响高位的结果。
- **顿悟感想**：通过将两次操作合并为一次操作，可以简化问题，减少代码复杂度。

---
处理用时：51.46秒