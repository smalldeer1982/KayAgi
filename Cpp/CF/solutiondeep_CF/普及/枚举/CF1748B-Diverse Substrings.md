# 题目信息

# Diverse Substrings

## 题目描述

A non-empty digit string is diverse if the number of occurrences of each character in it doesn't exceed the number of distinct characters in it.

For example:

- string "7" is diverse because 7 appears in it $ 1 $ time and the number of distinct characters in it is $ 1 $ ;
- string "77" is not diverse because 7 appears in it $ 2 $ times and the number of distinct characters in it is $ 1 $ ;
- string "1010" is diverse because both 0 and 1 appear in it $ 2 $ times and the number of distinct characters in it is $ 2 $ ;
- string "6668" is not diverse because 6 appears in it $ 3 $ times and the number of distinct characters in it is $ 2 $ .

You are given a string $ s $ of length $ n $ , consisting of only digits $ 0 $ to $ 9 $ . Find how many of its $ \frac{n(n+1)}{2} $ substrings are diverse.

A string $ a $ is a substring of a string $ b $ if $ a $ can be obtained from $ b $ by deletion of several (possibly, zero or all) characters from the beginning and several (possibly, zero or all) characters from the end.

Note that if the same diverse string appears in $ s $ multiple times, each occurrence should be counted independently. For example, there are two diverse substrings in "77" both equal to "7", so the answer for the string "77" is $ 2 $ .

## 说明/提示

In the first test case, the diverse substring is "7".

In the second test case, the only diverse substring is "7", which appears twice, so the answer is $ 2 $ .

In the third test case, the diverse substrings are "0" ( $ 2 $ times), "01", "010", "1" ( $ 2 $ times), "10" ( $ 2 $ times), "101" and "1010".

In the fourth test case, the diverse substrings are "0" ( $ 3 $ times), "01", "011", "0110", "1" ( $ 2 $ times), "10", "100", "110" and "1100".

In the fifth test case, the diverse substrings are "3", "39", "399", "6", "9" ( $ 4 $ times), "96" and "996".

In the sixth test case, all $ 15 $ non-empty substrings of "23456" are diverse.

## 样例 #1

### 输入

```
7
1
7
2
77
4
1010
5
01100
6
399996
5
23456
18
789987887987998798```

### 输出

```
1
2
10
12
10
15
106```

# AI分析结果

### 题目内容中文重写
## 多样子串

### 题目描述
一个非空的数字字符串如果其中每个字符的出现次数不超过该字符串中不同字符的数量，则称该字符串是多样的。

例如：
- 字符串 "7" 是多样的，因为 7 在其中出现了 1 次，且该字符串中不同字符的数量为 1；
- 字符串 "77" 不是多样的，因为 7 在其中出现了 2 次，而该字符串中不同字符的数量为 1；
- 字符串 "1010" 是多样的，因为 0 和 1 在其中均出现了 2 次，且该字符串中不同字符的数量为 2；
- 字符串 "6668" 不是多样的，因为 6 在其中出现了 3 次，而该字符串中不同字符的数量为 2。

给定一个长度为 $n$ 的字符串 $s$，该字符串仅由数字 0 到 9 组成。请找出它的 $\frac{n(n + 1)}{2}$ 个子串中有多少个是多样的。

如果字符串 $a$ 可以通过从字符串 $b$ 的开头删除若干（可能为零个或全部）字符以及从结尾删除若干（可能为零个或全部）字符得到，则称字符串 $a$ 是字符串 $b$ 的子串。

请注意，如果同一个多样字符串在 $s$ 中出现多次，则每次出现都应独立计数。例如，"77" 中有两个多样子串，均为 "7"，因此字符串 "77" 的答案为 2。

### 说明/提示
在第一个测试用例中，多样子串是 "7"。
在第二个测试用例中，唯一的多样子串是 "7"，它出现了两次，因此答案为 2。
在第三个测试用例中，多样子串有 "0"（2 次）、"01"、"010"、"1"（2 次）、"10"（2 次）、"101" 和 "1010"。
在第四个测试用例中，多样子串有 "0"（3 次）、"01"、"011"、"0110"、"1"（2 次）、"10"、"100"、"110" 和 "1100"。
在第五个测试用例中，多样子串有 "3"、"39"、"399"、"6"、"9"（4 次）、"96" 和 "996"。
在第六个测试用例中，"23456" 的所有 15 个非空子串都是多样的。

### 样例 #1
#### 输入
```
7
1
7
2
77
4
1010
5
01100
6
399996
5
23456
18
789987887987998798
```

#### 输出
```
1
2
10
12
10
15
106
```

### 题解综合分析与结论
- **思路**：各题解核心思路一致，均是基于合法多样子串长度不超过 100 这一特性，通过枚举子串开头，再对每个开头往后最多枚举 100 个字符来判断子串是否多样。
- **算法要点**：利用桶（数组）来记录每个数字的出现次数，同时维护不同数字的种类数和相同数字的最大出现次数，通过比较最大出现次数和不同数字种类数判断子串是否合法。
- **解决难点**：关键在于发现合法多样子串长度不超过 100 这一规律，将原本 $O(n^2)$ 甚至 $O(n^3)$ 的暴力枚举复杂度优化到 $O(100n)$，避免了对过长子串的无效枚举。

### 所选题解
- **作者：Xy_top（5 星）**
    - **关键亮点**：思路清晰，代码简洁易懂，详细解释了合法多样子串长度不超过 100 的原因，时间复杂度分析明确。
    - **核心代码**：
```cpp
#include <iostream>
using namespace std;
long long t, n, ans;
int main()
{
    scanf ("%d", &t);
    while (t --)
    {
        ans = 0;
        cin >> n;
        string s;
        cin >> s;
        for (long long i = 0; i < n; ++ i)
        {
            long long d[10] = {0}, mx = 0, dis = 0;
            for (long long j = i; j < min (i + 101, n); ++ j)
            {
                d[s[j] - '0'] ++;
                if (d[s[j] - '0'] == 1) ++ dis;
                mx = max (mx, d[s[j] - '0']);
                if (mx <= dis) ans ++;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
```
核心实现思想：外层循环枚举子串的起始位置，内层循环从起始位置开始往后最多枚举 100 个字符，用数组 `d` 记录每个数字的出现次数，`dis` 记录不同数字的种类数，`mx` 记录相同数字的最大出现次数，若 `mx <= dis` 则该子串为多样子串，答案加 1。

- **作者：Dry_ice（4 星）**
    - **关键亮点**：提供了更好的阅读体验链接，对题目的分析和复杂度计算清晰，代码中用变量直接记录不同数字种类数和相同数字的最大出现次数，进一步优化了代码。
    - **核心代码**：
```cpp
#include <stdio.h>
const int N = (int)2e5 + 5;
int n; char s[N];
inline void Solve() {
    scanf("%d %s", &n, s + 1); long long ans = 0; int a, b;
    for (int i = 1; i <= n; ++i) {
        a = b = 0; int vis[10] = {0};
        for (int j = i; j <= n && a <= 10 && b <= 10; ++j) {
            if (!vis[s[j] - '0']) ++a; ++vis[s[j] - '0'];
            if (vis[s[j] - '0'] > b) b = vis[s[j] - '0'];
            if (a >= b) ++ans;
        }
    }
    printf("%lld\n", ans);
}
int main(void) {
    int T; for (scanf("%d", &T); T--; ) Solve();
    return 0;
}
```
核心实现思想：`Solve` 函数中，外层循环枚举子串起始位置，内层循环从起始位置开始往后枚举字符，`a` 记录不同数字种类数，`b` 记录相同数字的最大出现次数，若 `a >= b` 则该子串为多样子串，答案加 1。

### 最优关键思路或技巧
- **思维方式**：通过分析数字的特性，利用鸽巢原理得出合法多样子串长度不超过 100 的结论，从而大大减少了枚举的范围。
- **代码实现**：使用桶（数组）来记录数字的出现次数，方便维护不同数字的种类数和最大出现次数。

### 可拓展之处
同类型题可能会改变字符的范围或多样子串的定义，类似算法套路是先分析合法子串的特性，缩小枚举范围，再通过适当的数据结构（如桶、哈希表等）来记录相关信息进行判断。

### 洛谷相似题目推荐
- [P1059 明明的随机数](https://www.luogu.com.cn/problem/P1059)：考察对数字的去重和排序，与本题处理数字的思想有一定关联。
- [P1217 [USACO1.5]回文质数 Prime Palindromes](https://www.luogu.com.cn/problem/P1217)：需要对数字进行枚举和判断，可锻炼枚举和判断的能力。
- [P1427 小鱼的数字游戏](https://www.luogu.com.cn/problem/P1427)：简单的数组操作和逆序输出，有助于巩固数组的使用，与本题使用数组记录数字出现次数有一定相似性。

### 个人心得
各题解中未包含个人心得内容。

---
处理用时：41.97秒