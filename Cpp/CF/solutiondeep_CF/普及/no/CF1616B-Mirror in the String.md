# 题目信息

# Mirror in the String

## 题目描述

You have a string $ s_1 s_2 \ldots s_n $ and you stand on the left of the string looking right. You want to choose an index $ k $ ( $ 1 \le k \le n $ ) and place a mirror after the $ k $ -th letter, so that what you see is $ s_1 s_2 \ldots s_k s_k s_{k - 1} \ldots s_1 $ . What is the lexicographically smallest string you can see?

A string $ a $ is lexicographically smaller than a string $ b $ if and only if one of the following holds:

- $ a $ is a prefix of $ b $ , but $ a \ne b $ ;
- in the first position where $ a $ and $ b $ differ, the string $ a $ has a letter that appears earlier in the alphabet than the corresponding letter in $ b $ .

## 说明/提示

In the first test case choose $ k = 1 $ to obtain "cc".

In the second test case choose $ k = 3 $ to obtain "cbaabc".

In the third test case choose $ k = 1 $ to obtain "aa".

In the fourth test case choose $ k = 1 $ to obtain "bb".

## 样例 #1

### 输入

```
4
10
codeforces
9
cbacbacba
3
aaa
4
bbaa```

### 输出

```
cc
cbaabc
aa
bb```

# AI分析结果

### 题目内容重写（中文）

#### 题目描述

你有一个字符串 $s_1 s_2 \ldots s_n$，你站在字符串的左侧向右看。你希望选择一个索引 $k$（$1 \le k \le n$），并在第 $k$ 个字母后放置一面镜子，这样你看到的字符串是 $s_1 s_2 \ldots s_k s_k s_{k - 1} \ldots s_1$。请问你能看到的字典序最小的字符串是什么？

一个字符串 $a$ 的字典序小于字符串 $b$，当且仅当满足以下条件之一：

- $a$ 是 $b$ 的前缀，但 $a \ne b$；
- 在 $a$ 和 $b$ 第一个不同的位置上，$a$ 的字母在字母表中比 $b$ 的对应字母更靠前。

#### 说明/提示

在第一个测试用例中，选择 $k = 1$ 得到 "cc"。

在第二个测试用例中，选择 $k = 3$ 得到 "cbaabc"。

在第三个测试用例中，选择 $k = 1$ 得到 "aa"。

在第四个测试用例中，选择 $k = 1$ 得到 "bb"。

#### 样例 #1

##### 输入

```
4
10
codeforces
9
cbacbacba
3
aaa
4
bbaa
```

##### 输出

```
cc
cbaabc
aa
bb
```

### 算法分类
贪心

### 题解分析与结论

本题的核心在于通过贪心策略找到字典序最小的镜像字符串。多个题解都提出了类似的思路：通过遍历字符串，找到第一个不满足单调递减的位置，然后在该位置放置镜子，生成回文串。以下是各题解的要点总结：

1. **I_m_FW**：观察到答案在镜面前都是非严格单调递减的，并给出了特判情况（如全相同字符时只需取前两位）。代码实现简洁，逻辑清晰。
2. **ArrogHie**：提出了结论，若前两位相同则取前两位，否则找到第一个 $s_i < s_{i+1}$ 的位置。代码实现较为简洁，但未处理全相同字符的特判。
3. **0xFF**：通过遍历字符串，找到第一个不满足单调递减的位置，生成回文串。代码实现较为复杂，但逻辑清晰。
4. **Chenyichen0420**：通过贪心策略，逐步构建答案字符串，直到遇到不满足单调递减的字符。代码实现简洁，但未处理全相同字符的特判。
5. **xiaozeyu**：通过遍历字符串，找到第一个不满足单调递减的位置，生成回文串。代码实现简洁，逻辑清晰。
6. **LCat90**：通过贪心策略，找到字典序逐渐减小的位置，生成回文串。代码实现简洁，逻辑清晰。
7. **cqbzhzf**：通过遍历字符串，找到第一个不满足单调递减的位置，生成回文串。代码实现较为复杂，但逻辑清晰。
8. **cqbzrjx**：通过贪心策略，找到字典序逐渐减小的位置，生成回文串。代码实现简洁，逻辑清晰。
9. **L_shadow**：通过贪心策略，找到第一个不满足单调递减的位置，生成回文串。代码实现简洁，逻辑清晰。
10. **liuzhongrui**：通过贪心策略，找到第一个不满足单调递减的位置，生成回文串。代码实现简洁，逻辑清晰。
11. **qwq___qaq**：通过贪心策略，找到第一个不满足单调递减的位置，生成回文串。代码实现简洁，逻辑清晰。

### 评分较高的题解

1. **I_m_FW**（4星）
   - **关键亮点**：通过观察样例，提出非严格单调递减的结论，并处理了全相同字符的特判情况。代码简洁，逻辑清晰。
   - **代码核心**：
     ```cpp
     for(int i=1;i<s.size();i++){
         if(s[i]!=s[0])pd=1;
         if(last>s[i]||(last==s[i]&&pd))v.push_back(s[i]),last=s[i];
         else break;
     }
     ```

2. **xiaozeyu**（4星）
   - **关键亮点**：通过遍历字符串，找到第一个不满足单调递减的位置，生成回文串。代码简洁，逻辑清晰。
   - **代码核心**：
     ```cpp
     for(i=1;i<n;i++)
         if(s[i]>s[i+1]) f=1;
         else if(s[i]<s[i+1]||(s[i]==s[i+1]&&!f))break;
     ```

3. **LCat90**（4星）
   - **关键亮点**：通过贪心策略，找到字典序逐渐减小的位置，生成回文串。代码简洁，逻辑清晰。
   - **代码核心**：
     ```cpp
     for(int i=1;i<=n-1;++i) {
         if(c[i]<c[i+1] or (i==1 and c[i]==c[i+1])) {
             for(int j=1;j<=i;++j) putchar(c[j]);
             for(int j=i;j>=1;--j) putchar(c[j]);
             flag=1;
             break;
         }
     }
     ```

### 最优关键思路

通过贪心策略，找到字符串中第一个不满足单调递减的位置，然后在该位置放置镜子，生成回文串。特别地，当字符串全相同时，只需取前两位。

### 可拓展之处

类似的问题可以通过贪心策略解决，如寻找字典序最小的子序列、回文串等。贪心策略在字符串处理中具有广泛的应用。

### 推荐题目

1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
2. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
3. [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)

---
处理用时：37.76秒