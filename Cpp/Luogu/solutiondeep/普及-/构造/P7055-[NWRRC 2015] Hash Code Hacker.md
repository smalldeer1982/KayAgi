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

本题的核心目标是生成多个哈希值相同的字符串，且这些字符串只能包含大小写字母。大部分题解都采用了类似的思路：通过替换字符串中的某些子串（如 `cc` 替换为 `dD`）来保持哈希值不变。这种方法的优点是简单直观，且能够通过数学证明其正确性。

**关键思路与技巧：**
1. **哈希值不变性**：通过替换某些子串（如 `cc` 替换为 `dD`）来保持哈希值不变。这种替换基于哈希公式的数学性质，确保了替换后的字符串与原字符串的哈希值相同。
2. **二进制枚举**：部分题解通过二进制枚举来生成不同的字符串，这种方法能够高效地生成大量不同的字符串，且代码实现简洁。
3. **字符串长度控制**：通过控制字符串的长度，确保生成的字符串数量足够多，满足题目要求。

**扩展思路：**
- **其他哈希替换**：除了 `cc` 和 `dD`，还可以寻找其他具有相同哈希值的子串进行替换，以增加字符串的多样性。
- **更复杂的替换规则**：可以考虑替换多个子串，或者使用更复杂的替换规则来生成更多的字符串。

### 所选高星题解

#### 1. **作者：035966_L3 (5星)**
- **关键亮点**：通过数学证明 `cc` 和 `dD` 的哈希值相同，并详细解释了替换的原理。代码实现简洁，且通过限制修改次数来控制生成的字符串数量。
- **个人心得**：通过数学证明确保了替换的正确性，避免了不必要的调试。

**核心代码：**
```cpp
string s=stds;
s.replace(i,2,rs);
cout<<s<<'\n';
```
**实现思想**：通过 `replace` 函数将原字符串中的 `cc` 替换为 `dD`，生成新的字符串并输出。

#### 2. **作者：Flaw_Owl (4星)**
- **关键亮点**：通过二进制枚举生成不同的字符串，代码简洁且高效。通过位运算检测每一位的状态，决定输出 `Aa` 或 `BB`。
- **个人心得**：通过二进制枚举生成字符串，避免了复杂的替换逻辑，代码更加简洁。

**核心代码：**
```cpp
for (int j = 0; j < 10; j++) {
    if ((i >> j) & 1) printf("BB");
    else printf("Aa");
}
```
**实现思想**：通过位运算检测每一位的状态，决定输出 `BB` 或 `Aa`，生成不同的字符串。

#### 3. **作者：UniGravity (4星)**
- **关键亮点**：通过深搜生成不同的字符串，且字符串长度较短（20位），满足题目要求。通过递归生成所有可能的字符串组合。
- **个人心得**：通过深搜生成字符串，确保了生成的字符串数量足够多，且代码实现简洁。

**核心代码：**
```cpp
void dfs(int x) {
    if (x > 10) {
        printf("%s\n", s);
        cnt++;
        return;
    }
    dfs(x + 1);
    s[x * 2] = 'A';
    s[x * 2 + 1] = 'a';
    dfs(x + 1);
    s[x * 2] = s[x * 2 + 1] = 'B';
}
```
**实现思想**：通过深搜生成不同的字符串组合，每次递归选择输出 `Aa` 或 `BB`，生成不同的字符串。

### 推荐相似题目
1. **P3370 【模板】字符串哈希**：考察字符串哈希的基本应用。
2. **P3375 【模板】KMP字符串匹配**：考察字符串匹配算法，与哈希相关。
3. **P3376 【模板】AC自动机（简单版）**：考察字符串匹配与自动机，与哈希相关。

### 总结
本题的核心在于通过替换子串保持哈希值不变，且大部分题解都采用了类似的思路。通过数学证明和二进制枚举等方法，能够高效地生成大量不同的字符串。推荐进一步学习字符串哈希的相关知识，以应对更复杂的字符串处理问题。

---
处理用时：32.65秒