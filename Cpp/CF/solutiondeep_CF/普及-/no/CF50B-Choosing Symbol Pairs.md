# 题目信息

# Choosing Symbol Pairs

## 题目描述

There is a given string $ S $ consisting of $ N $ symbols. Your task is to find the number of ordered pairs of integers $ i $ and $ j $ such that

1\. $ 1<=i,j<=N $

2\. $ S[i]=S[j] $ , that is the $ i $ -th symbol of string $ S $ is equal to the $ j $ -th.

## 样例 #1

### 输入

```
great10
```

### 输出

```
7
```

## 样例 #2

### 输入

```
aaaaaaaaaa
```

### 输出

```
100
```

# AI分析结果

【题目内容（中文重写）】
# 选择符号对

## 题目描述
给定一个由 $N$ 个符号组成的字符串 $S$。你的任务是找出有序整数对 $(i, j)$ 的数量，使得：
1. $1\leq i,j\leq N$
2. $S[i]=S[j]$，即字符串 $S$ 的第 $i$ 个符号等于第 $j$ 个符号。

## 样例 #1
### 输入
```
great10
```
### 输出
```
7
```

## 样例 #2
### 输入
```
aaaaaaaaaa
```
### 输出
```
100
```

【算法分类】
数学

【综合分析与结论】
这些题解的核心思路都是先统计字符串中每个字符的出现次数，再根据每个字符出现次数计算其对相同字符对数的贡献，最后将所有字符的贡献累加得到结果。关键在于证明若有 $n$ 个相同的字母，它们之间相同的对数是 $n^2$。

各题解的区别主要在于数据结构的选择和实现细节，如使用 `map` 或数组来统计字符出现次数。部分题解还提到了暴力枚举会超时以及数据范围可能导致的溢出问题，提醒使用 `long long` 类型。

【所选的题解】
- Eason_AC（5星）
  - 关键亮点：思路清晰，详细证明了 $n$ 个相同字母的配对数为 $n^2$ 的结论，代码逻辑清晰，使用 `map` 统计字符出现次数并避免重复计算。
  - 个人心得：无

【重点代码】
```cpp
#include <cstdio>
#include <algorithm>
#include <map>
#include <iostream>
using namespace std;

string s;
map<char, long long> a, vis;
long long sum;

int main() {
    cin >> s;
    for(int i = 0; i < s.size(); ++i) a[s[i]]++;
    for(int i = 0; i < s.size(); ++i) {
        if(!vis[s[i]]) {
            sum += a[s[i]] * a[s[i]];
            vis[s[i]] = 1;
        }
    }
    printf("%lld\n", sum);
    return 0;
}
```
【核心实现思想】
1. 首先读取输入的字符串。
2. 遍历字符串，使用 `map<char, long long> a` 统计每个字符的出现次数。
3. 再次遍历字符串，使用 `map<char, long long> vis` 标记已经处理过的字符，对于未处理过的字符，将其出现次数的平方累加到 `sum` 中。
4. 输出最终结果 `sum`。

【可拓展之处】
同类型题目可能会有不同的限制条件，如要求统计不同类型字符的配对情况，或者在二维字符串数组中统计相同字符的配对数等。解题思路仍然是先统计字符出现次数，再根据具体规则计算配对数。

【推荐题目】
1. P1059 明明的随机数：考查对数据的处理和统计。
2. P1165 日志分析：涉及对数据的统计和处理。
3. P1553 数字反转：考查对字符串和数字的处理。

【个人心得摘录】
- phil071128：尝试了暴力代码，过了前20个点后TLE，之后通过找规律推出公式解决问题。总结：暴力枚举可能会超时，需要寻找更优的算法。
- dingshengyang：指出 $O(n^2)$ 枚举会 TLE，$n^2$ 最大可达 $10^{10}$，要开 `long long`。总结：要注意数据范围和时间复杂度，避免超时和溢出。
- Suuon_Kanderu：提到暴力会TLE，然后采用统计字符的方法。总结：对于大规模数据，暴力算法往往不可行，需要采用更高效的算法。 

---
处理用时：23.81秒