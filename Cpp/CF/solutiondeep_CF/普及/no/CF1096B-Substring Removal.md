# 题目信息

# Substring Removal

## 题目描述

You are given a string $ s $ of length $ n $ consisting only of lowercase Latin letters.

A substring of a string is a contiguous subsequence of that string. So, string "forces" is substring of string "codeforces", but string "coder" is not.

Your task is to calculate the number of ways to remove exactly one substring from this string in such a way that all remaining characters are equal (the number of distinct characters either zero or one).

It is guaranteed that there is at least two different characters in $ s $ .

Note that you can remove the whole string and it is correct. Also note that you should remove at least one character.

Since the answer can be rather large (not very large though) print it modulo $ 998244353 $ .

If you are Python programmer, consider using PyPy instead of Python when you submit your code.

## 说明/提示

Let $ s[l; r] $ be the substring of $ s $ from the position $ l $ to the position $ r $ inclusive.

Then in the first example you can remove the following substrings:

- $ s[1; 2] $ ;
- $ s[1; 3] $ ;
- $ s[1; 4] $ ;
- $ s[2; 2] $ ;
- $ s[2; 3] $ ;
- $ s[2; 4] $ .

In the second example you can remove the following substrings:

- $ s[1; 4] $ ;
- $ s[1; 5] $ ;
- $ s[1; 6] $ ;
- $ s[1; 7] $ ;
- $ s[2; 7] $ ;
- $ s[3; 7] $ .

In the third example you can remove the following substrings:

- $ s[1; 1] $ ;
- $ s[1; 2] $ ;
- $ s[2; 2] $ .

## 样例 #1

### 输入

```
4
abaa
```

### 输出

```
6
```

## 样例 #2

### 输入

```
7
aacdeee
```

### 输出

```
6```

## 样例 #3

### 输入

```
2
az
```

### 输出

```
3```

# AI分析结果

### 题目内容重写
# 子串删除

## 题目描述

给定一个长度为 $n$ 的字符串 $s$，字符串仅由小写拉丁字母组成。

子串是指字符串中连续的子序列。例如，字符串 "forces" 是字符串 "codeforces" 的子串，但字符串 "coder" 不是。

你的任务是计算有多少种方法从该字符串中删除恰好一个子串，使得剩下的字符全部相同（剩下的字符种类数为零或一）。

保证字符串 $s$ 中至少有两个不同的字符。

注意，你可以删除整个字符串，这也是合法的。同时，你至少需要删除一个字符。

由于答案可能较大（但不会非常大），请输出答案对 $998244353$ 取模的结果。

如果你是 Python 程序员，建议在提交代码时使用 PyPy 而不是 Python。

## 说明/提示

设 $s[l; r]$ 为字符串 $s$ 从位置 $l$ 到位置 $r$ 的子串（包括 $l$ 和 $r$）。

在第一个示例中，你可以删除以下子串：

- $s[1; 2]$；
- $s[1; 3]$；
- $s[1; 4]$；
- $s[2; 2]$；
- $s[2; 3]$；
- $s[2; 4]$。

在第二个示例中，你可以删除以下子串：

- $s[1; 4]$；
- $s[1; 5]$；
- $s[1; 6]$；
- $s[1; 7]$；
- $s[2; 7]$；
- $s[3; 7]$。

在第三个示例中，你可以删除以下子串：

- $s[1; 1]$；
- $s[1; 2]$；
- $s[2; 2]$。

## 样例 #1

### 输入

```
4
abaa
```

### 输出

```
6
```

## 样例 #2

### 输入

```
7
aacdeee
```

### 输出

```
6
```

## 样例 #3

### 输入

```
2
az
```

### 输出

```
3
```

### 算法分类
字符串

### 题解分析与结论
这道题的核心思路是通过分析字符串的首尾字符是否相同，来分类讨论删除子串的方式。主要分为两种情况：
1. 首尾字符相同：此时可以通过计算首尾连续相同字符的个数，利用乘法原理计算方案数。
2. 首尾字符不同：此时只能保留首字符或尾字符，或者删除整个字符串，方案数为首尾连续相同字符的个数之和加一。

### 高星题解推荐
#### 题解1：作者：IGA_Indigo (赞：5)
- **星级**：5星
- **关键亮点**：思路清晰，代码简洁，分类讨论明确，且代码中考虑了取模操作，避免了溢出问题。
- **核心代码**：
```cpp
if(s[1]==s[n]){//第一种情况 
    long long t=0,w=0;
    for(int i=1;i<=n;i++){//从前往后扫 
        if(s[i]==s[1]){
            t++;
        }//一样的就增加个数 
        else{
            break;//不一样就跳出 
        }
    }
    for(int i=n;i>=1;i--){//从后往前扫 
        if(s[i]==s[1]){
            w++;//一样就增加个数 
        }
        else{
            break;//不一样就跳出 
        }
    }
    cout<<(t+1)*(w+1)%998244353;//计算答案，别忘了取模 
}
else{//第二种情况 
    long long t=0,w=0;
    for(int i=1;i<=n;i++){//从前往后扫
        if(s[i]==s[1]){ 
            t++;
        }
        else{
            break;//不一样就跳出 
        }
    }
    for(int i=n;i>=1;i--){//从后往前扫 
        if(s[i]==s[n]){
            w++;//一样就增加个数 
        }
        else{
            break;//不一样就跳出 
        }
    }
    cout<<(t+w+1)%998244353;//计算答案，别忘了取模 
}
```

#### 题解2：作者：_Qer (赞：3)
- **星级**：4星
- **关键亮点**：思路清晰，代码简洁，分类讨论明确，且代码中考虑了取模操作，避免了溢出问题。
- **核心代码**：
```cpp
if (s[0] == s[n - 1]) {
    char t = s[0];
    long long c1 = 1, c2 = n - 2;
    while (s[c1] == t) { ++c1; }
    while (s[c2] == t) { --c2; }
    c2 = n - c2;
    cout << (c1 + 1) * c2 % 998244353 << endl;
} else {
    long long c1 = 1, c2 = n - 2;
    while (s[c1] == s[0]) { ++c1; }
    while (s[c2] == s[n - 1]) { --c2; }
    cout << (c1 + (n - c2)) % 998244353 << endl;
}
```

#### 题解3：作者：Ryan_Adam (赞：0)
- **星级**：4星
- **关键亮点**：思路清晰，代码简洁，分类讨论明确，且代码中考虑了取模操作，避免了溢出问题。
- **核心代码**：
```cpp
if(s[0]!=s[n-1])
{
    cout<<(l+r+1)%mod<<endl;
}
else
{
    cout<<(l+1)*(r+1)%mod<<endl;
}
```

### 最优关键思路
1. **分类讨论**：根据字符串首尾字符是否相同，分为两种情况讨论，分别计算方案数。
2. **乘法原理**：当首尾字符相同时，利用乘法原理计算方案数。
3. **加法原理**：当首尾字符不同时，利用加法原理计算方案数。
4. **取模操作**：由于答案可能较大，需要在计算过程中对结果取模，避免溢出。

### 可拓展之处
类似的问题可以通过分析字符串的首尾字符或连续字符的性质来解决。例如，计算字符串中连续相同字符的最长子串长度，或者计算删除子串后字符串的某种性质。

### 推荐题目
1. [P1141 01迷宫](https://www.luogu.com.cn/problem/P1141)
2. [P1037 产生数](https://www.luogu.com.cn/problem/P1037)
3. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)

### 个人心得摘录
- **调试经历**：在计算方案数时，容易忽略取模操作，导致结果溢出。因此，在编写代码时，务必注意取模操作。
- **踩坑教训**：在分类讨论时，容易遗漏某些情况，导致结果错误。因此，在编写代码时，务必考虑所有可能的情况。

---
处理用时：46.10秒