# 题目信息

# [USACO11FEB] Cowlphabet G

## 题目描述

Like all bovines, Farmer John's cows speak the peculiar 'Cow'

language. Like so many languages, each word in this language comprises a sequence of upper and lowercase letters (A-Z and a-z).  A word is valid if and only if each ordered pair of adjacent letters in the word is a valid pair.

Farmer John, ever worried that his cows are plotting against him, recently tried to eavesdrop on their conversation. He overheard one word before the cows noticed his presence. The Cow language is spoken so quickly, and its sounds are so strange, that all that Farmer John was able to perceive was the total number of uppercase letters, U (1 <= U <= 250) and the total number of lowercase

letters, L (1 <= L <= 250) in the word. 

Farmer John knows all P (1 <= P <= 200) valid ordered pairs of adjacent letters.  He wishes to know how many different valid 

words are consistent with his limited data.  However, since

this number may be very large, he only needs the value modulo

97654321.

约翰家的奶牛用别人听不懂的“牛语”联络。牛语采用英文字母，而且区分大小写。牛 语中的语法中，前后字母的衔接非常重要，存在P个基本组合，每个字母之后只能接固定的 几个字母。 约翰担心奶牛正在密谋反对他，于是最近一直在偷听她们的对话。可是牛语太复杂了， 他只模模糊糊地听到了一个单词，并确定了这个单词中有U个大写字母，L个小写字母。约 翰对这个单词很在意，他想知道，有多少牛语词汇拥有U个大写字母，L个小写字母。由于 这个数字太大了，你只要输出答案取 97654321 的余数就可以了。 输入格式 ? ? 第一行：三个用空格隔开的整数：U，L和P，1 ≤ U, L ≤ 250，1 ≤ P ≤ 200 第二行到P + 1行：第i + 1有两个字母Ai和Bi，表示字母Ai后面可以接Bi，没有一对Ai和 Bi是完全相同的


## 说明/提示

The word Farmer John overheard had 2 uppercase and 2 lowercase letters.  The valid pairs of adjacent letters are AB, ab, BA, ba, Aa, Bb and bB.


The possible words are:

AabB
ABba
abBA
BAab
BbBb
bBAa
bBbB

## 样例 #1

### 输入

```
2 2 7 
AB 
ab 
BA 
ba 
Aa 
Bb 
bB 
```

### 输出

```
7 
```

# AI分析结果



### 算法分类
动态规划

---

### 综合分析与结论
题目要求统计符合大写字母数 U、小写字母数 L 且相邻字母合法的字符串数目。所有题解均采用动态规划，核心思路为设计三维状态 `dp[大写数量][小写数量][结尾字母]`，通过遍历所有可能的字母转移路径进行递推。关键在于状态设计、合法转移判断与高效编码实现。

---

### 精选题解

#### 1. 作者：tXX_F（4星）
**关键亮点**  
- 状态定义清晰：`f[i][j][k]` 表示总字符数 i，大写数 j，结尾字母 k。
- 编码优化：将大小写字母统一映射为 1-52 的数字，简化条件判断。
- 初始化合理：分别处理小写和大写字母的初始状态。

**核心代码**  
```cpp
for(int i=1;i<=U+L;++i)
    for(int j=0;j<=U;++j++)
        for(int k=1;k<=52;++k)
            for(int next : Vec_S[k]) { // 遍历可转移字母
                if(next <=26) // 小写
                    f[i+1][j][next] += f[i][j][k];
                else // 大写
                    f[i+1][j+1][next] += f[i][j][k];
            }
```

#### 2. 作者：Usada_Pekora（4星）
**关键亮点**  
- 状态维度直观：`f[结尾字母][大写数][小写数]`，更贴近问题描述。
- 动态内存优化：仅存储实际出现的字母，减少无效计算。
- 初始化灵活：根据输入字母动态初始化，避免冗余状态。

**核心代码**  
```cpp
for(char a : 合法前驱字母)
    for(char b : 可转移字母) {
        if(b是大写) 
            f[b][j+1][k] += f[a][j][k];
        else 
            f[b][j][k+1] += f[a][j][k];
    }
```

#### 3. 作者：xu222ux（4星）
**关键亮点**  
- 循环范围剪枝：通过 `min(i,x)` 和 `max(0,i-y)` 减少无效计算。
- 边界处理严谨：在大写转移时检查 `j != x` 防止溢出。

**核心代码**  
```cpp
for(int j=min(i,x); j>=max(0,i-y); j--) // 动态调整大写数范围
    if(下一个字母是大写 && j+1<=U)
        f[i+1][j+1][新字母] += f[i][j][当前字母];
```

---

### 关键思路与技巧
1. **状态压缩设计**：将大写、小写字母统一编码为连续数值（1-52），简化条件判断。
2. **递推方向优化**：通过逆推或正推动态调整循环范围，减少无效状态。
3. **动态初始化**：仅对输入中出现的字母进行初始化，节省内存与计算量。

---

### 拓展与举一反三
类似问题可考虑以下题目：
1. [P1279 字串距离](https://www.luogu.com.cn/problem/P1279) - 动态规划处理字符串匹配与距离计算。
2. [P4158 [SCOI2009]粉刷匠](https://www.luogu.com.cn/problem/P4158) - 状态设计结合颜色与操作次数限制。
3. [P2657 [SCOI2009] windy数](https://www.luogu.com.cn/problem/P2657) - 数位DP中相邻数字关系约束。

---

### 个人心得摘录
- **初始化陷阱**：需区分大小写字母的初始状态，如 `a-z` 初始大写数为0，`A-Z` 初始为1。  
- **转移条件**：大写转移时必须检查 `j+1 <= U`，否则会导致超过题目限制。  
- **编码技巧**：将字母映射为数值后，可用数组代替哈希表加速访问。

---
处理用时：57.79秒