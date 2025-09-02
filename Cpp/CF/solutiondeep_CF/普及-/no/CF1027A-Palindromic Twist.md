# 题目信息

# Palindromic Twist

## 题目描述

You are given a string $ s $ consisting of $ n $ lowercase Latin letters. $ n $ is even.

For each position $ i $ ( $ 1 \le i \le n $ ) in string $ s $ you are required to change the letter on this position either to the previous letter in alphabetic order or to the next one (letters 'a' and 'z' have only one of these options). Letter in every position must be changed exactly once.

For example, letter 'p' should be changed either to 'o' or to 'q', letter 'a' should be changed to 'b' and letter 'z' should be changed to 'y'.

That way string "codeforces", for example, can be changed to "dpedepqbft" ('c' $ \rightarrow $ 'd', 'o' $ \rightarrow $ 'p', 'd' $ \rightarrow $ 'e', 'e' $ \rightarrow $ 'd', 'f' $ \rightarrow $ 'e', 'o' $ \rightarrow $ 'p', 'r' $ \rightarrow $ 'q', 'c' $ \rightarrow $ 'b', 'e' $ \rightarrow $ 'f', 's' $ \rightarrow $ 't').

String $ s $ is called a palindrome if it reads the same from left to right and from right to left. For example, strings "abba" and "zz" are palindromes and strings "abca" and "zy" are not.

Your goal is to check if it's possible to make string $ s $ a palindrome by applying the aforementioned changes to every position. Print "YES" if string $ s $ can be transformed to a palindrome and "NO" otherwise.

Each testcase contains several strings, for each of them you are required to solve the problem separately.

## 说明/提示

The first string of the example can be changed to "bcbbcb", two leftmost letters and two rightmost letters got changed to the next letters, two middle letters got changed to the previous letters.

The second string can be changed to "be", "bg", "de", "dg", but none of these resulting strings are palindromes.

The third string can be changed to "beeb" which is a palindrome.

The fifth string can be changed to "lk", "lm", "nk", "nm", but none of these resulting strings are palindromes. Also note that no letter can remain the same, so you can't obtain strings "ll" or "mm".

## 样例 #1

### 输入

```
5
6
abccba
2
cf
4
adfa
8
abaazaba
2
ml
```

### 输出

```
YES
NO
YES
NO
NO
```

# AI分析结果



# 回文扭曲

## 题目描述

给定一个由 $n$ 个小写字母组成的字符串 $s$，其中 $n$ 是偶数。要求将每个字符恰好改变一次（变为前一个或后一个字母，'a'只能变'b'，'z'只能变'y'），判断能否使字符串变为回文。

## 输入输出样例

输入样例：
```
5
6
abccba
2
cf
4
adfa
8
abaazaba
2
ml
```

输出样例：
```
YES
NO
YES
NO
NO
```

## 算法分类
字符串、构造

## 题目分析与结论
本题核心在于对称字符对的差值分析。对于每一对对称字符 $s[i]$ 和 $s[n-i-1]$，必须满足以下条件之一才能通过调整变为相同：
1. **差值为0**：两个字符相同，可同时加1或减1（注意边界字符如'a'只能加1，'z'只能减1）。
2. **差值为2**：一个字符加1，另一个减1后相等。

若存在任意一对字符不满足以上条件（如差值为1或超过2），则无法形成回文。

---

## 高分题解选录

### 题解作者：01Dragon（★★★★☆）
**关键思路**：  
直接遍历前半个字符串，检查每对字符的ASCII差绝对值是否为0或2。若存在不满足的字符对，立即返回NO。  
**代码亮点**：  
- 循环条件正确（遍历前n/2个字符）
- 逻辑简洁，时间复杂度O(n)

```cpp
bool flag = true;
for(int i=0; i<n/2; i++) {
    if(abs(s[i]-s[n-i-1])>2 || abs(s[i]-s[n-i-1])==1) {
        flag = false;
        break;
    }
}
cout << (flag ? "YES" : "NO");
```

---

### 题解作者：Zq_water（★★★★☆）
**关键思路**：  
与01Dragon思路完全一致，代码风格更紧凑。  
**代码亮点**：  
- 使用布尔标志直接控制输出
- 变量命名清晰

```cpp
bool flag = 1;
for(int i=0; i<n/2; i++) 
    if(abs(s[i]-s[n-i-1])>2 || abs(s[i]-s[n-i-1])==1) 
        flag = 0;
cout << (flag ? "YES\n" : "NO\n");
```

---

## 最优思路总结
**核心技巧**：  
- 对称字符对差值分析：仅允许差值为0或2
- 边界字符（a/z）的处理被差值条件隐式覆盖，无需单独判断

**易错点**：  
- 循环必须限制在n/2范围内，避免重复判断
- 注意每个字符必须改变一次的限制

---

## 拓展练习
1. [P1217 回文质数](https://www.luogu.com.cn/problem/P1217) - 回文与数论结合
2. [P1435 回文字符串](https://www.luogu.com.cn/problem/P1435) - 动态规划构造回文
3. [P2870 最佳牛线](https://www.luogu.com.cn/problem/P2870) - 贪心构造字典序最小回文

---
处理用时：158.25秒