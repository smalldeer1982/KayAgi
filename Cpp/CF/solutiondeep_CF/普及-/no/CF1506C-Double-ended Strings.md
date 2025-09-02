# 题目信息

# Double-ended Strings

## 题目描述

You are given the strings $ a $ and $ b $ , consisting of lowercase Latin letters. You can do any number of the following operations in any order:

- if $ |a| > 0 $ (the length of the string $ a $ is greater than zero), delete the first character of the string $ a $ , that is, replace $ a $ with $ a_2 a_3 \ldots a_n $ ;
- if $ |a| > 0 $ , delete the last character of the string $ a $ , that is, replace $ a $ with $ a_1 a_2 \ldots a_{n-1} $ ;
- if $ |b| > 0 $ (the length of the string $ b $ is greater than zero), delete the first character of the string $ b $ , that is, replace $ b $ with $ b_2 b_3 \ldots b_n $ ;
- if $ |b| > 0 $ , delete the last character of the string $ b $ , that is, replace $ b $ with $ b_1 b_2 \ldots b_{n-1} $ .

Note that after each of the operations, the string $ a $ or $ b $ may become empty.

For example, if $ a= $ "hello" and $ b= $ "icpc", then you can apply the following sequence of operations:

- delete the first character of the string $ a $ $ \Rightarrow $ $ a= $ "ello" and $ b= $ "icpc";
- delete the first character of the string $ b $ $ \Rightarrow $ $ a= $ "ello" and $ b= $ "cpc";
- delete the first character of the string $ b $ $ \Rightarrow $ $ a= $ "ello" and $ b= $ "pc";
- delete the last character of the string $ a $ $ \Rightarrow $ $ a= $ "ell" and $ b= $ "pc";
- delete the last character of the string $ b $ $ \Rightarrow $ $ a= $ "ell" and $ b= $ "p".

For the given strings $ a $ and $ b $ , find the minimum number of operations for which you can make the strings $ a $ and $ b $ equal. Note that empty strings are also equal.

## 样例 #1

### 输入

```
5
a
a
abcd
bc
hello
codeforces
hello
helo
dhjakjsnasjhfksafasd
adjsnasjhfksvdafdser```

### 输出

```
0
2
13
3
20```

# AI分析结果

### 题目内容
# 双端字符串

## 题目描述
给定字符串 $a$ 和 $b$，它们由小写拉丁字母组成。你可以按任意顺序进行任意次数的以下操作：
- 如果 $|a| > 0$（字符串 $a$ 的长度大于零），删除字符串 $a$ 的第一个字符，即将 $a$ 替换为 $a_2a_3\ldots a_n$；
- 如果 $|a| > 0$，删除字符串 $a$ 的最后一个字符，即将 $a$ 替换为 $a_1a_2\ldots a_{n - 1}$；
- 如果 $|b| > 0$（字符串 $b$ 的长度大于零），删除字符串 $b$ 的第一个字符，即将 $b$ 替换为 $b_2b_3\ldots b_n$；
- 如果 $|b| > 0$，删除字符串 $b$ 的最后一个字符，即将 $b$ 替换为 $b_1b_2\ldots b_{n - 1}$。

注意，每次操作后，字符串 $a$ 或 $b$ 可能变为空。

例如，如果 $a =$ "hello" 且 $b =$ "icpc"，那么你可以应用以下操作序列：
- 删除字符串 $a$ 的第一个字符 $\Rightarrow$ $a =$ "ello" 且 $b =$ "icpc"；
- 删除字符串 $b$ 的第一个字符 $\Rightarrow$ $a =$ "ello" 且 $b =$ "cpc"；
- 删除字符串 $b$ 的第一个字符 $\Rightarrow$ $a =$ "ello" 且 $b =$ "pc"；
- 删除字符串 $a$ 的最后一个字符 $\Rightarrow$ $a =$ "ell" 且 $b =$ "pc"；
- 删除字符串 $b$ 的最后一个字符 $\Rightarrow$ $a =$ "ell" 且 $b =$ "p"。

对于给定的字符串 $a$ 和 $b$，找出使字符串 $a$ 和 $b$ 相等所需的最少操作次数。注意，空字符串也相等。

## 样例 #1
### 输入
```
5
a
a
abcd
bc
hello
codeforces
hello
helo
dhjakjsnasjhfksafasd
adjsnasjhfksvdafdser
```
### 输出
```
0
2
13
3
20
```

### 算法分类
字符串

### 综合分析与结论
这些题解都基于同一个核心思路，即由于操作只能在字符串的首尾进行，所以最终相等的部分必然是两个字符串的最长公共子串。通过求出最长公共子串的长度，用两字符串长度之和减去其两倍，就能得到最少操作次数。不同题解的差异主要体现在求最长公共子串的方法上，有的采用暴力枚举，有的使用动态规划。暴力枚举方法直观但时间复杂度较高，适用于数据范围小的情况；动态规划方法则更具通用性和效率。

### 所选的题解
- **作者：_xbn (5星)**
  - **关键亮点**：代码简洁，直接使用两层循环嵌套，在循环中通过一个 `while` 循环计算从当前位置开始的最长公共子串长度，思路清晰，代码量少。
  - **重点代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
void solve() 
{
    string a, b;
    cin >> a >> b;
    int maxk = 0;
    for (int i = 0; i < a.size(); i++) 
    {
        for (int j = 0; j < b.size(); j++) 
        {
            int k = 0;
            while (i + k < a.size() && j + k < b.size() && a[i + k] == b[j + k])k++;
            if (k > maxk) maxk = k;
        }
    }
    cout << a.size() + b.size() - 2 * maxk << endl;
}

int main() 
{
    int T;
    cin >> T;
    for (int i = 1; i <= T; i++)solve();
}
```
  - **核心实现思想**：通过两层循环枚举 `a` 和 `b` 字符串的起始位置，然后用 `while` 循环找到从该起始位置开始的最长公共子串长度，并更新最大长度 `maxk`，最后根据公式计算并输出最少操作次数。
- **作者：Infinity_Detail (4星)**
  - **关键亮点**：详细阐述了动态规划的状态和转移方程，逻辑清晰。状态定义为以 `a[i - 1]` 和 `b[j - 1]` 作为结尾的两个公共子串的长度，根据字符是否相等进行状态转移。
  - **重点代码**：
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<string>
using namespace std;
int dp[25][25];
string a, b;
int t, maxl;
int main() {
    cin >> t;
    while (t--) {
        cin >> a >> b;
        maxl = 0;
        memset(dp, 0, sizeof(dp));
        for (int i = 0; i < a.size(); i++) { 
            for (int j = 0; j < b.size(); j++) {
                if (a[i] == b[j]) dp[i + 1][j + 1] = dp[i][j] + 1;
                else dp[i + 1][j + 1] = 0;
                maxl = max(maxl, dp[i + 1][j + 1]);
            }
        } 
        cout << a.size() + b.size() - maxl * 2 << endl;
    }
    return 0;
}
```
  - **核心实现思想**：利用二维数组 `dp` 记录状态，通过两层循环遍历两个字符串，根据状态转移方程更新 `dp` 数组，并在过程中记录最大的公共子串长度 `maxl`，最后计算并输出最少操作次数。
- **作者：nalemy (4星)**
  - **关键亮点**：对动态规划的状态和转移方程解释清晰，与 `Infinity_Detail` 的思路类似，但表述更简洁明了。
  - **重点代码**：
```cpp
#include<iostream>
#include<cstring>
#define N 20
using namespace std;

int dp[N][N];
int main() {
    string a, b;
    int q, as, bs, mx; cin >> q;
    while (q--) {
        cin >> a >> b, mx = 0, as = a.size(), bs = b.size();
        memset(dp, 0, sizeof(dp));
        for (int i = 0; i < as; i++)
            for (int j = 0; j < bs; j++)
                dp[i + 1][j + 1] = a[i] == b[j]? dp[i][j] + 1 : 0,
                mx = max(mx, dp[i + 1][j + 1]);
        cout << as + bs - mx * 2 << endl;
    }
    return 0;
}
```
  - **核心实现思想**：定义二维数组 `dp` 表示状态，通过双重循环遍历字符串，依据状态转移方程更新 `dp` 值并记录最大公共子串长度 `mx`，最后得出最少操作次数并输出。

### 最优关键思路或技巧
最优思路是将问题转化为求最长公共子串问题。在实现上，动态规划方法相对更优，通过合理定义状态和转移方程，可以高效地解决问题。其关键在于利用二维数组记录以特定位置结尾的公共子串长度，根据字符匹配情况更新状态，从而得到最长公共子串长度。

### 可拓展之处
同类型题目通常围绕字符串的操作和比较展开，类似算法套路包括求最长公共子序列、编辑距离等问题。在处理这类问题时，关键是分析操作对字符串结构的影响，从而转化为熟悉的字符串问题求解。

### 洛谷相似题目推荐
- [P1439 【模板】最长公共子序列](https://www.luogu.com.cn/problem/P1439)
- [P1020 导弹拦截](https://www.luogu.com.cn/problem/P1020)
- [P3904 三只小猪](https://www.luogu.com.cn/problem/P3904) 

---
处理用时：71.24秒