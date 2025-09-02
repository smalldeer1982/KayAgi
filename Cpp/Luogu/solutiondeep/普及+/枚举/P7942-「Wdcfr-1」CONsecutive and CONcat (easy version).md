# 题目信息

# 「Wdcfr-1」CONsecutive and CONcat (easy version)

## 题目描述

**In easy version, It is guaranteed that any string in array $\mathbf a$ contains at least two different letters.**

Lily White is playing with strings. Being a yousei, she is not capable of complex speech. Thus, she likes strings that only contain one kind of letter, she calls such strings of length $x$ a "$x$-CON string". For example, `qqqq` is a "$4$-CON string", while `aaab` is not any type of "CON string".

Lily White composed an array $a$. It contains $n$ strings of length $m$ that she will use to herald spring. For each permutation of $1,2,\ldots, n$, let us denote current permutation as $p=\{p_1,p_2,\cdots,p_n\}$. Lily White concatenates all the string in array $a$ in the order of $a_{p_1},a_{p_2},\cdots,a_{p_n}$ into a string $s$ of length $nm$ . 

As she likes $k$-CON strings, she wants to know the sum of the number of "$k$-CON string" in all non-empty substrings of $s$ composed by all $n!$ permutations. Since the answer may be enormous, just print the answer taken modulo $998,244,353$ (a large prime).


## 说明/提示

### Explanation

#### Sample \#1

- For permutation $1,2,3$, the formed $s$ is `aabbaabaa`, none on the non-empty substring in this string are "$4$-CON string".
- For permutation $1,3,2$, the formed $s$ is `aabbaabaa`, none on the non-empty substring in this string are "$4$-CON string".
- For permutation $2,1,3$, the formed $s$ is `baaaabbaa`, this string has one substring `aaaa` which is a "$4$-CON string".
- For permutation $2,3,1$, the formed $s$ is `baabaaaab`, this string has one substring `aaaa` which is a "$4$-CON string".
- For permutation $3,1,2$, the formed $s$ is `baaaabbaa`, this string has one substring `aaaa` which is a "$4$-CON string".
- For permutation $3,2,1$, the formed $s$ is `baabaaaab`, this string has one substring `aaaa` which is a "$4$-CON string".

In summary, the answer is $0+0+1+1+1+1=4$.

#### Sample \#2

In all of the full permutation of length $3$, there will be six different $s$: `xyzqaqaba`, `xyzabaqaq`, `qaqxyzaba`, `qaqabaxyz`, `abaqaqxyz`, and `abaxyzqaq`. None of these has a non-empty substrings which is a "$2$-CON string". So the answer is $0$.

### Constraints

$2\le k \le n\cdot m\le 10^6;\ 1\le m \le 100$. $a_i$ contains only lowercase English letters.

**In easy version, we ensure that any string in array $\mathbf a$ contains at least two different letters.**

## 样例 #1

### 输入

```
3 3 4
aab
baa
baa```

### 输出

```
4```

## 样例 #2

### 输入

```
3 3 2
xyz
qaq
aba
```

### 输出

```
0```

# AI分析结果

### 综合分析与结论
这三道题解均围绕计算所有排列下字符串拼接后 $k$-CON 子串的数量展开。FFTotoro 的题解思路清晰，将贡献分为两部分分别计算，考虑全面且有代码实现；wdsj0yqqs 的题解思路简单直接但复杂度高；yzy1 的题解思路有创新，利用概率转化问题，但存在特殊情况未正确处理。整体而言，FFTotoro 的题解质量最高。

### 所选题解
- **FFTotoro（5星）**
  - **关键亮点**：思路清晰，将贡献分为单个字符串内部贡献和两个字符串拼接贡献两部分，考虑到了算重和自己拼接自己的情况，且有完整代码实现，代码可读性较高。

### 重点代码及核心实现思想
```cpp
// 计算拼接时“跨越”字符串的子串数
auto f=[&](int i,int j,int k){
  return min(i,i+j-k+1)-max(1ll,i-k+2)+1;
}; 
// 统计所有方案数
for(int c=0;c<26;c++)
  for(int i=1;i<m;i++)
    for(int j=max(k-i,1ll);j<m;j++)
      (r+=(b[j][c]*s[i][c]%p-e[j][i][c]+p)%p*f(i,j,k)%p*F2%p)%=p;
```
核心实现思想：先定义一个函数 `f` 用于计算两个字符串拼接时跨越字符串的子串数。然后通过三重循环枚举字符、后缀长度和前缀长度，统计所有可能的拼接方案，同时减去自己和自己拼接的情况，最后乘以 $(n - 1)!$ 并累加贡献到结果 `r` 中。

### 最优关键思路或技巧
- **分类讨论**：将贡献分为单个字符串内部贡献和两个字符串拼接贡献两部分，分别计算，降低问题复杂度。
- **避免算重**：在计算两个字符串拼接贡献时，只考虑子串跨越两个字符串的情况，避免了算重。

### 可拓展之处
同类型题或类似算法套路：可以拓展到多个字符串拼接，或者改变子串的条件（如子串长度范围、字符种类等）。解题时依然可以采用分类讨论的思想，分别计算不同部分的贡献。

### 推荐洛谷题目
- [P1059 明明的随机数](https://www.luogu.com.cn/problem/P1059)：考察对数据的处理和去重，与本题对字符串的处理有一定相似性。
- [P1067 多项式输出](https://www.luogu.com.cn/problem/P1067)：需要对不同情况进行分类讨论，与本题分类讨论的思想类似。
- [P1075 质因数分解](https://www.luogu.com.cn/problem/P1075)：考察对数学问题的分析和处理，与本题对问题的分析思路有一定关联。

### 个人心得
FFTotoro 提到原来的官方题解有误导性，包括公式中代表变量的字母写错，计算方式容易让人理解错意思导致边界条件处理不清楚。这提醒我们在参考题解时要保持批判性思维，仔细分析题解的正确性和合理性。 

---
处理用时：26.07秒