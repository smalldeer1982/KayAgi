# 题目信息

# Phone Numbers

## 题目描述

And where the are the phone numbers?

You are given a string $ s $ consisting of lowercase English letters and an integer $ k $ . Find the lexicographically smallest string $ t $ of length $ k $ , such that its set of letters is a subset of the set of letters of $ s $ and $ s $ is lexicographically smaller than $ t $ .

It's guaranteed that the answer exists.

Note that the set of letters is a set, not a multiset. For example, the set of letters of abadaba is $ {a,b,d} $ .

String $ p $ is lexicographically smaller than string $ q $ , if $ p $ is a prefix of $ q $ , is not equal to $ q $ or there exists $ i $ , such that $ p_{i}<q_{i} $ and for all $ j<i $ it is satisfied that $ p_{j}=q_{j} $ . For example, abc is lexicographically smaller than abcd , abd is lexicographically smaller than abec, afa is not lexicographically smaller than ab and a is not lexicographically smaller than a.

## 说明/提示

In the first example the list of strings $ t $ of length 3, such that the set of letters of $ t $ is a subset of letters of $ s $ is as follows: aaa, aab, aac, aba, abb, abc, aca, acb, $ ... $ . Among them, those are lexicographically greater than abc: aca, acb, $ ... $ . Out of those the lexicographically smallest is aca.

## 样例 #1

### 输入

```
3 3
abc
```

### 输出

```
aca
```

## 样例 #2

### 输入

```
3 2
abc
```

### 输出

```
ac
```

## 样例 #3

### 输入

```
3 3
ayy
```

### 输出

```
yaa
```

## 样例 #4

### 输入

```
2 3
ba
```

### 输出

```
baa
```

# AI分析结果

### 题目中文重写
# 电话号码

## 题目描述
电话号码在哪里呢？

给定一个由小写英文字母组成的字符串 $s$ 和一个整数 $k$。找出长度为 $k$ 的字典序最小的字符串 $t$，使得 $t$ 的字母集是 $s$ 的字母集的子集，并且 $s$ 的字典序小于 $t$。

保证答案存在。

注意，字母集是一个集合，而不是多重集。例如，abadaba 的字母集是 $\{a, b, d\}$。

如果 $p$ 是 $q$ 的前缀且 $p$ 不等于 $q$，或者存在 $i$ 使得 $p_i < q_i$ 且对于所有 $j < i$ 都有 $p_j = q_j$，则称字符串 $p$ 的字典序小于字符串 $q$。例如，abc 的字典序小于 abcd，abd 的字典序小于 abec，afa 的字典序不小于 ab，a 的字典序不小于 a。

## 说明/提示
在第一个样例中，长度为 3 且字母集是 $s$ 的字母集的子集的字符串 $t$ 列表如下：aaa, aab, aac, aba, abb, abc, aca, acb, ... 。其中，字典序大于 abc 的有：aca, acb, ... 。在这些字符串中，字典序最小的是 aca。

## 样例 #1
### 输入
```
3 3
abc
```
### 输出
```
aca
```

## 样例 #2
### 输入
```
3 2
abc
```
### 输出
```
ac
```

## 样例 #3
### 输入
```
3 3
ayy
```
### 输出
```
yaa
```

## 样例 #4
### 输入
```
2 3
ba
```
### 输出
```
baa
```

### 综合分析与结论
这些题解的核心思路都是通过分类讨论 $n$ 和 $k$ 的大小关系，采用贪心策略来构造满足条件的字符串。
- **思路**：主要分为 $n < k$、$n = k$、$n > k$ 三种情况。$n < k$ 时，先输出原字符串 $s$，再用最小字符补齐；$n \geq k$ 时，从后往前找不是最大字符的位置，将其替换为比它大一点的字符，后面用最小字符填充。
- **算法要点**：对字符串中的字符进行排序或记录最大最小字符，方便查找和替换。
- **解决难点**：关键在于如何在满足条件的情况下，找到字典序最小的字符串，通过贪心策略从后往前替换字符解决。

### 所选题解
- **yaolibo（5星）**：
    - **关键亮点**：思路清晰，分类讨论详细，代码注释丰富，将 $n = k$ 和 $n > k$ 的情况合并处理，减少代码冗余。
- **codeLJH114514（4星）**：
    - **关键亮点**：使用标准库函数 `min_element`、`max_element` 和 `upper_bound` 简化代码实现，提高代码的可读性和简洁性。
- **__int127（4星）**：
    - **关键亮点**：思路明确，代码有详细注释，对每种情况的处理逻辑解释清晰。

### 重点代码
#### yaolibo 的核心代码
```cpp
if (n < k) { //第①种情况
    for (i = 1; i <= n; i++)
        printf("%c", s[i]); //原封不动输出s
    for (i = n + 1; i <= k; i++)
        printf("%c", t[n]); //剩下的字符输出s中最小的字符，即t[n]。
}
else { //第②③种情况
    for (i = k; i >= 1; i--) { //从第k位开始遍历
        for (j = 1; j <= n; j++) //找到第一个大于s[i]的字符
            if (t[j] <= s[i])
                break;
        if (j != 1) { //说明当前字符不是最大字符，于是替换，退出
            s[i] = t[j - 1]; //注意第j位是第一个小于等于s[i]的字符，第j-1位才是第一个大于s[i]的字符
            break;
        } //否则就继续往下遍历
    }
    for (j = 1; j <= i; j++)
        printf("%c", s[j]); //输出前i位
    for (j = i + 1; j <= k; j++)
        printf("%c", t[n]); //剩下的全部输出t[n]（贪心）
}
```
**核心实现思想**：根据 $n$ 和 $k$ 的大小关系分类处理。$n < k$ 时直接输出原字符串并补齐最小字符；$n \geq k$ 时从后往前找可替换的字符，替换后补齐最小字符。

#### codeLJH114514 的核心代码
```cpp
if (n >= k) { // 第一种情况。
    char mx = *max_element(s.begin(), s.end());
    char mi = *min_element(s.begin(), s.end()); // 找出最大最小字符。
    for (int i = k - 1; i >= 0; i--) // 枚举字符。
        if (s[i] != mx) {
            string r = s;
            sort(r.begin(), r.end()); // 使用 upper_bound 之前先排序。
            s[i] = *upper_bound(r.begin(), r.end(), s[i]);
            for (int j = i + 1; j < k; j++)
                s[j] = mi;
            s.resize(k); // 重新设置大小。
            cout << s;
            break;
        }
} else if (n < k) { // 第二种情况。
    string ns = s;
    char ch = *min_element(ns.begin(), ns.end()); // 同理。
    for (int i = 1; i <= k - n; i++)
        ns += ch;
    cout << ns;
}
```
**核心实现思想**：$n \geq k$ 时，找出最大最小字符，从后往前找不是最大字符的位置，替换为比它大一点的字符，后面用最小字符填充；$n < k$ 时，直接在原字符串后添加最小字符。

#### __int127 的核心代码
```cpp
if (k > n){// n<k
    cout << s;
    for (int i = 1; i <= k - n; i++){
        cout << minn;
    }
} else if (k == n){//n=k
    for (int i = n - 1; i >= 0; i--){
        if (s[i] != t[0]){
            for (int j = 0; j < i; j++){
                cout << s[j];
            }
            cout << find(i);
            for (int j = i + 1; j < n; j++){
                cout << minn;
            }
            break; 
        }
    }
} else {//n>k
    int num = 0;
    for (int i = k - 1; i >= 0; i--){
        if (s[i] != t[0]){ 
            for (int j = 0; j < i; j++, num++){
                cout << s[j];
            }
            cout << find(i);
            num++;
            break;
        }
    } 
    if (num < k){
        for (int i = 1; i <= k - num; i++){
            cout << minn;
        }
    } 
}
```
**核心实现思想**：根据 $k$ 和 $n$ 的大小关系分类处理，$k > n$ 时输出原字符串并补齐最小字符；$k = n$ 和 $k < n$ 时从后往前找可替换的字符，替换后补齐最小字符。

### 最优关键思路或技巧
- **分类讨论**：根据 $n$ 和 $k$ 的大小关系进行分类讨论，使问题简化。
- **贪心策略**：从后往前找可替换的字符，保证字典序最小。
- **使用标准库函数**：如 `min_element`、`max_element` 和 `upper_bound` 等，简化代码实现。

### 可拓展之处
同类型题目可能会有更多的限制条件，如字符的使用次数限制、字符串的其他性质要求等。类似算法套路可以应用于其他字符串构造问题，通过分类讨论和贪心策略找到最优解。

### 推荐题目
- [P1055 ISBN 号码](https://www.luogu.com.cn/problem/P1055)
- [P1071 潜伏者](https://www.luogu.com.cn/problem/P1071)
- [P1125 笨小猴](https://www.luogu.com.cn/problem/P1125)

### 个人心得
各题解均未包含个人心得内容。

---
处理用时：56.62秒