# 题目信息

# Ranom Numbers

## 题目描述

No, not "random" numbers.

Ranom digits are denoted by uppercase Latin letters from A to E. Moreover, the value of the letter A is $ 1 $ , B is $ 10 $ , C is $ 100 $ , D is $ 1000 $ , E is $ 10000 $ .

A Ranom number is a sequence of Ranom digits. The value of the Ranom number is calculated as follows: the values of all digits are summed up, but some digits are taken with negative signs: a digit is taken with negative sign if there is a digit with a strictly greater value to the right of it (not necessarily immediately after it); otherwise, that digit is taken with a positive sign.

For example, the value of the Ranom number DAAABDCA is $ 1000 - 1 - 1 - 1 - 10 + 1000 + 100 + 1 = 2088 $ .

You are given a Ranom number. You can change no more than one digit in it. Calculate the maximum possible value of the resulting number.

## 说明/提示

In the first example, you can get EAAABDCA with the value $ 10000-1-1-1-10+1000+100+1=11088 $ .

In the second example, you can get EB with the value $ 10000+10=10010 $ .

## 样例 #1

### 输入

```
4
DAAABDCA
AB
ABCDEEDCBA
DDDDAAADDABECD```

### 输出

```
11088
10010
31000
15886```

# AI分析结果

### 题目内容重写

**Ranom Numbers**

**题目描述**

不，不是“随机”数字。

Ranom 数字由大写拉丁字母 A 到 E 表示。此外，字母 A 的值为 1，B 为 10，C 为 100，D 为 1000，E 为 10000。

一个 Ranom 数字是一个由 Ranom 数字组成的序列。Ranom 数字的值计算如下：所有数字的值相加，但某些数字带有负号：如果某个数字的右侧有一个严格大于它的数字（不一定紧邻），则该数字带有负号；否则，该数字带有正号。

例如，Ranom 数字 DAAABDCA 的值为 1000 - 1 - 1 - 1 - 10 + 1000 + 100 + 1 = 2088。

给定一个 Ranom 数字，你可以改变其中的不超过一个数字。计算修改后数字的最大可能值。

**说明/提示**

在第一个示例中，你可以将 DAAABDCA 修改为 EAAABDCA，其值为 10000 - 1 - 1 - 1 - 10 + 1000 + 100 + 1 = 11088。

在第二个示例中，你可以将 AB 修改为 EB，其值为 10000 + 10 = 10010。

**样例 #1**

**输入**

```
4
DAAABDCA
AB
ABCDEEDCBA
DDDDAAADDABECD
```

**输出**

```
11088
10010
31000
15886
```

### 算法分类
贪心

### 题解分析与结论

本题的核心在于如何通过修改一个字符来最大化 Ranom 数字的值。多个题解都采用了贪心的策略，通过分析字符修改的位置和方式，减少不必要的计算，从而优化时间复杂度。

### 所选高分题解

#### 题解1：XSean (5星)
**关键亮点：**
- 通过分析得出，修改字符时只需考虑最左或最右的位置，减少了计算量。
- 提供了详细的证明，确保策略的正确性。
- 代码实现简洁，时间复杂度为 O(n)。

**核心代码：**
```cpp
int calc(int len){
    int res = 0;
    char maxc = 'A';
    pre(i, len, 1){
        int c = str[i] - 'A';
        if(maxc > str[i]) res += -ch[c];
        else{
            maxc = str[i];
            res += ch[c];
        }
    }
    return res;
}
```
**实现思想：**
从后向前遍历字符串，记录当前最大值，根据字符与最大值的关系决定其贡献的正负。

#### 题解2：jhdrgfj (5星)
**关键亮点：**
- 同样通过分析得出修改字符的最优位置，减少计算量。
- 代码结构清晰，易于理解。
- 时间复杂度为 O(n)。

**核心代码：**
```cpp
long long v(long long siz){
    char m='A';
    long long ans=0;
    for (int i=siz-1;i>=0;i--){
        if (s[i]<m){
            ans-=pow(10,s[i]-'A');
        }
        if (s[i]>=m){
            m=s[i];
            ans+=pow(10,s[i]-'A');
        }
    }
    return ans;
}
```
**实现思想：**
从后向前遍历字符串，记录当前最大值，根据字符与最大值的关系决定其贡献的正负。

#### 题解3：一扶苏一 (4星)
**关键亮点：**
- 详细分析了修改字符的两种情况（改大和改小），并提供了相应的优化策略。
- 通过预处理和动态规划，进一步优化了计算过程。
- 代码实现较为复杂，但思路清晰。

**核心代码：**
```cpp
int ans = sum;
std::array<std::vector<int>, 5> contri;
for (auto &v : contri) v.resize(n);
for (int i = 0; i < n; ++i) {
    if (i != 0) for (int j = 0; j < 5; ++j) contri[j][i] = contri[j][i - 1];
    if (sgn[i] == 1) contri[s[i] - 'A'][i] += a[i];
}
```
**实现思想：**
通过预处理贡献数组，快速计算修改字符后的值变化。

### 最优关键思路或技巧
- **贪心策略**：通过分析字符修改的位置，减少不必要的计算，优化时间复杂度。
- **预处理**：通过预处理贡献数组或后缀最大值，快速计算修改后的值变化。
- **从后向前遍历**：从后向前遍历字符串，记录当前最大值，决定字符的贡献正负。

### 可拓展之处
- 类似的问题可以通过贪心策略和预处理来优化计算，例如在字符串中修改多个字符以最大化或最小化某种值。
- 可以扩展到其他类型的字符值计算问题，如根据字符的某种属性进行加权计算。

### 推荐题目
1. [P1045 最大子段和](https://www.luogu.com.cn/problem/P1045)
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
3. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)

---
处理用时：42.36秒