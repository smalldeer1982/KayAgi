# 题目信息

# 「Wdcfr-1」CONsecutive and CONcat (hard version)

## 题目描述

Lily White is playing with strings. Being a yousei, she is not capable of complex speech. Thus, she likes strings that only contain one kind of letter, she calls such strings of length $x$ a "$x$-CON string". For example, `qqqq` is a "$4$-CON string", while `aaab` is not any type of "CON string".

Lily White composed an array $a$. It contains $n$ strings of length $m$ that she will use to herald spring. For each permutation of $1,2,\ldots, n$, let us denote current permutation as $p=\{p_1,p_2,\cdots,p_n\}$. Lily White concatenates all the string in array $a$ in the order of $a_{p_1},a_{p_2},\cdots,a_{p_n}$ into a string $s$ of length $nm$ . 

As she likes $k$-CON strings, she wants to know the sum of the number of "$k$-CON string" in all non-empty substrings of $s$ composed by all $n!$ permutations. Since the answer may be enormous, just print the answer taken modulo $998,244,353$ (a large prime).


## 说明/提示

### Explanation

#### Sample \#1

- For permutation $1,2,3$, the formed $s$ is `aaabaabaa`, none on the non-empty substring in this string are "$5$-CON string".
- For permutation $1,3,2$, the formed $s$ is `aaabaabaa`, none on the non-empty substring in this string are "$5$-CON string".
- For permutation $2,1,3$, the formed $s$ is `baaaaabaa`, this string has one substring `aaaaa` which is a "$5$-CON string".
- For permutation $2,3,1$, the formed $s$ is `baabaaaaa`, this string has one substring `aaaaa` which is a "$5$-CON string".
- For permutation $3,1,2$, the formed $s$ is `baaaaabaa`, this string has one substring `aaaaa` which is a "$5$-CON string".
- For permutation $3,2,1$, the formed $s$ is `baabaaaaa`, this string has one substring `aaaaa` which is a "$5$-CON string".

In summary, the answer is $0+0+1+1+1+1=4$.

#### Sample \#2

In all of the full permutation of length $3$, there will be six different $s$: `xyzqaqaba`, `xyzabaqaq`, `qaqxyzaba`, `qaqabaxyz`, `abaqaqxyz`, and `abaxyzqaq`. None of these has a non-empty substrings which is a "$2$-CON string". So the answer is $0$.

### Constraints

$2\le k \le n\cdot m\le 10^6;\ 1\le m \le 100$. $a_i$ contains only lowercase English letters.

## 样例 #1

### 输入

```
3 3 5
aaa
baa
baa
```

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

## 样例 #3

### 输入

```
5 3 2
cca
cbb
acb
bbb
acb
```

### 输出

```
600```

## 样例 #4

### 输入

```
5 3 5
aba
bbb
bbb
aba
bcb
```

### 输出

```
120```

# AI分析结果

### 综合分析与结论
这两道题解都将字符串的贡献分为内部贡献和拼接贡献两部分来计算。yzy1 的题解将拼接贡献进一步细分多种情况，思路较为复杂，通过预处理前后缀信息，利用概率计算贡献，同时考虑了重复计算的特殊情况；xtzqhy 的题解则直接计算以每个位置为起点的区间贡献，对前缀散块分类讨论，避免了算重的问题，思路相对简单直接。

### 所选题解
- **xtzqhy 的题解（4星）**
  - **关键亮点**：思路简单直接，通过对前缀散块分类讨论避免了复杂的去重操作，复杂度为 $O(nm)$，代码实现较为清晰。

### 重点代码及核心实现思想
```cpp
inline void solve(string s){
    int len=0;char lst=0;
    for(re int i=0;i<m;++i){
        if(s[i]!=lst){
            if(len>=k) ans=(ans+(len-k+1)*fac[n]%mod)%mod;
            lst=s[i],len=1;
        }
        else ++len;
    }
    if(len>=k) ans=(ans+(len-k+1)*fac[n]%mod)%mod;
}

for(re int i=1;i<=n;++i){
    del(s[i]);
    char c=s[i][m-1];
    for(re int j=m-1,len,num1,len1;j>=0;--j){
        if(s[i][j]!=c) break;
        if(m-j>=k) continue;
        len=k-(m-j);num1=len/m;len1=len-num1*m;
        if(!len1) ans=(ans+A(buc[c-'a'],num1)%mod*fac[n-num1]%mod)%mod;
        else ans=(ans+A(buc[c-'a'],num1)%mod*num[c-'a'][len1]%mod*fac[n-num1-1]%mod+A(buc[c-'a'],num1+1)%mod*fac[n-num1-1]%mod)%mod;
    }
    add(s[i]);
}
```
核心实现思想：`solve` 函数用于计算单个字符串内部的贡献，遍历字符串，统计连续相同字符的长度，若长度大于等于 $k$，则将其对答案的贡献累加到 `ans` 中。后续的循环用于计算拼接产生的贡献，对于每个字符串，先将其从桶中删除，以避免自己对自己的贡献，然后从字符串末尾向前遍历，根据不同的情况计算以该位置为起点的区间的贡献，最后将该字符串重新加入桶中。

### 最优关键思路或技巧
- 将贡献分为内部贡献和拼接贡献两部分分别计算，降低问题复杂度。
- xtzqhy 的题解通过对前缀散块分类讨论，直接计算以每个位置为起点的区间贡献，避免了复杂的去重操作。

### 可拓展之处
同类型题或类似算法套路：在处理字符串拼接和计数问题时，都可以考虑将贡献分类讨论，对于拼接产生的贡献，可以通过枚举拼接位置、前后缀信息等方式进行计算。在计数过程中，要注意避免重复计算，可以通过分类讨论、去重等方法来解决。

### 洛谷相似题目
- P1059 [NOIP2006 普及组] 明明的随机数
- P1067 [NOIP2009 普及组] 多项式输出
- P1075 [NOIP2012 普及组] 质因数分解

---
处理用时：26.29秒