# 题目信息

# [NWRRC 2015] Hash Code Hacker

## 题目描述



According to Java standard library documentation, the hash code of String is computed as

$s[0] \times 31 ^ {n -1} + s[1] \times 31 ^ {n -2} + \cdots + s[n -1]$

Here $s[i]$ is the i-th character of the string, $n$ is the length of the string, and $^$ indicates exponentiation. Computation uses signed $32-bit$ integers in two's complement form.

Heather is going to hack the servers of Not Entirely Evil Recording Company $(NEERC).$ To perform an attack she needs $k$ distinct query strings that have equal hash codes. Unfortunately, NEERC servers accept query string containing lower- and uppercase English letters only.

Heather hired you to write a program that generates such query strings for her.



## 说明/提示

Time limit: 2 s, Memory limit: 256 MB. 



## 样例 #1

### 输入

```
4
```

### 输出

```
edHs
mENAGeS
fEHs
edIT
```

# AI分析结果

### 综合分析与结论

本题的核心在于构造多个哈希值相同的字符串。大部分题解通过找到两个字符的替换对（如 `cc` 和 `dD`），并利用这些替换对生成不同的字符串，从而保证哈希值不变。这种思路的核心是找到两个字符组合，使得它们在哈希计算中的贡献相同。通过替换这些组合，可以生成大量哈希值相同的字符串。

### 所选高星题解

#### 1. 题解作者：035966_L3 (5星)
- **关键亮点**：通过详细的数学证明，展示了 `cc` 和 `dD` 在哈希计算中的等价性，并提供了清晰的代码实现。代码简洁且高效，能够生成足够多的字符串。
- **个人心得**：作者通过数学推导证明了替换的可行性，这种严谨的思维方式值得学习。
- **核心代码**：
```cpp
for(int i=0;i<=48;i++) {
    s=stds;
    s.replace(i,2,rs);
    cout<<s<<'\n';
}
```
**实现思想**：通过替换字符串中的 `cc` 为 `dD`，生成哈希值相同的字符串。

#### 2. 题解作者：Flaw_Owl (4星)
- **关键亮点**：提出了使用二进制枚举的方法，通过 `BB` 和 `Aa` 的组合生成不同的字符串，思路新颖且代码简洁。
- **核心代码**：
```cpp
for (int j = 0; j < 10; j++) {
    if ((i >> j) & 1) printf("BB");
    else printf("Aa");
}
```
**实现思想**：利用二进制位决定输出 `BB` 还是 `Aa`，生成不同的字符串。

#### 3. 题解作者：hehejushi (4星)
- **关键亮点**：通过深搜实现字符串的生成，代码结构清晰，且能够生成足够多的字符串。
- **核心代码**：
```cpp
void dfs(int dep ,string str ) {
    if(dep == 10){
        cout << str << endl;
        cnt++;
        if (cnt == n) exit(0);
        return ;
    }
    dfs (dep+1, str+"xx") ;
    dfs (dep+1, str+"yY") ;
}
```
**实现思想**：通过深搜生成不同的字符串，每次选择 `xx` 或 `yY` 进行拼接。

### 最优关键思路与技巧

1. **字符替换对**：找到两个字符组合（如 `cc` 和 `dD`），使得它们在哈希计算中的贡献相同，通过替换这些组合生成不同的字符串。
2. **二进制枚举**：利用二进制位决定输出不同的字符组合，生成大量哈希值相同的字符串。
3. **深搜生成**：通过深搜生成不同的字符串，每次选择不同的字符组合进行拼接。

### 可拓展之处

1. **类似题目**：可以考察其他哈希函数的构造方式，或者要求生成满足特定条件的字符串。
2. **算法套路**：类似的字符替换和组合生成思路可以应用于其他字符串处理问题，如生成回文串、满足特定模式的字符串等。

### 推荐题目

1. [P3370 【模板】字符串哈希](https://www.luogu.com.cn/problem/P3370)
2. [P3375 【模板】KMP字符串匹配](https://www.luogu.com.cn/problem/P3375)
3. [P3376 【模板】AC自动机（简单版）](https://www.luogu.com.cn/problem/P3376)

### 个人心得总结

- **调试经历**：在替换字符时，需要注意字符的 ASCII 值，确保替换后的字符组合在哈希计算中的贡献相同。
- **踩坑教训**：在生成大量字符串时，需要注意字符串的长度和生成方式，避免超出时间或空间限制。
- **顿悟感想**：通过数学推导和二进制枚举，可以高效地生成大量满足条件的字符串，这种思维方式在解决类似问题时非常有用。

---
处理用时：31.20秒