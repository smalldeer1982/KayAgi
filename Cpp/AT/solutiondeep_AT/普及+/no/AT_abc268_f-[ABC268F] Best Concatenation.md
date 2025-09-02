# 题目信息

# [ABC268F] Best Concatenation

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc268/tasks/abc268_f

`1` から `9` の数字および `X` のみからなる $ N $ 個の文字列 $ S_1,\ S_2,\ \ldots,\ S_N $ が与えられます。

$ (1,\ 2,\ \ldots,\ N) $ を並べ替えた列 $ P\ =\ (P_1,\ P_2,\ \ldots,\ P_N) $ を一つ選び、 文字列 $ T\ =\ S_{P_1}\ +\ S_{P_2}\ +\ \cdots\ +\ S_{P_N} $ を作ります。ここで、$ + $ は文字列の連結を表します。

そして、文字列 $ T\ =\ T_1T_2\ldots\ T_{|T|} $ の「スコア」を計算します（ $ |T| $ は文字列 $ T $ の長さを表します）。  
 $ T $ のスコアは、スコアが $ 0 $ の状態から始め、下記の $ 9 $ 個の手順を行うことで計算されます。

- $ 1\ \leq\ i\ \lt\ j\ \leq\ |T| $ および $ T_i\ = $ `X` かつ $ T_j\ = $ `1` を満たす整数の組 $ (i,\ j) $ の個数だけ、スコアを $ 1 $ 点加算する 。
- $ 1\ \leq\ i\ \lt\ j\ \leq\ |T| $ および $ T_i\ = $ `X` かつ $ T_j\ = $ `2` を満たす整数の組 $ (i,\ j) $ の個数だけ、スコアを $ 2 $ 点加算する。
- $ 1\ \leq\ i\ \lt\ j\ \leq\ |T| $ および $ T_i\ = $ `X` かつ $ T_j\ = $ `3` を満たす整数の組 $ (i,\ j) $ の個数だけ、スコアを $ 3 $ 点加算する。
- $ \cdots $
- $ 1\ \leq\ i\ \lt\ j\ \leq\ |T| $ および $ T_i\ = $ `X` かつ $ T_j\ = $ `9` を満たす整数の組 $ (i,\ j) $ の個数だけ、スコアを $ 9 $ 点加算する。

$ P $ を任意に選ぶときの、$ T $ のスコアとしてあり得る最大値を出力してください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ N $ は整数
- $ S_i $ は `1` から `9` の数字および `X` のみからなる長さ $ 1 $ 以上の文字列
- $ S_1,\ S_2,\ \ldots,\ S_N $ の長さの総和は $ 2\ \times\ 10^5 $ 以下

### Sample Explanation 1

$ P\ =\ (3,\ 1,\ 2) $ とすると、$ T\ =\ S_3\ +\ S_1\ +\ S_2\ = $ `XXX1X359` です。 このとき、$ T $ のスコアは次の通り計算されます。 - $ 1\ \leq\ i\ \lt\ j\ \leq\ |T| $ および $ T_i\ = $ `X` かつ $ T_j\ = $ `1` を満たす整数の組 $ (i,\ j) $ が $ 3 $ 個あり、 - $ 1\ \leq\ i\ \lt\ j\ \leq\ |T| $ および $ T_i\ = $ `X` かつ $ T_j\ = $ `3` を満たす整数の組 $ (i,\ j) $ が $ 4 $ 個あり、 - $ 1\ \leq\ i\ \lt\ j\ \leq\ |T| $ および $ T_i\ = $ `X` かつ $ T_j\ = $ `5` を満たす整数の組 $ (i,\ j) $ が $ 4 $ 個あり、 - $ 1\ \leq\ i\ \lt\ j\ \leq\ |T| $ および $ T_i\ = $ `X` かつ $ T_j\ = $ `9` を満たす整数の組 $ (i,\ j) $ が $ 4 $ 個あります。 よって、$ T $ のスコアは $ 1\ \times\ 3\ +\ 3\ \times\ 4\ +\ 5\ \times\ 4\ +\ 9\ \times\ 4\ =\ 71 $ であり、これが考えられる最大値です。

## 样例 #1

### 输入

```
3

1X3

59

XXX```

### 输出

```
71```

## 样例 #2

### 输入

```
10

X63X395XX

X2XX3X22X

13

3716XXX6

45X

X6XX

9238

281X92

1XX4X4XX6

54X9X711X1```

### 输出

```
3010```

# AI分析结果

### 题目内容重写

[ABC268F] Best Concatenation

**题目描述**

给定由 `1` 到 `9` 的数字以及 `X` 组成的 $N$ 个字符串 $S_1, S_2, \ldots, S_N$。

将 $(1, 2, \ldots, N)$ 进行排列，得到一个排列 $P = (P_1, P_2, \ldots, P_N)$，并构造字符串 $T = S_{P_1} + S_{P_2} + \cdots + S_{P_N}$，其中 $+$ 表示字符串的拼接。

然后，计算字符串 $T = T_1T_2\ldots T_{|T|}$ 的“分数”（$|T|$ 表示字符串 $T$ 的长度）。分数的计算方式如下：

- 对于每个 $1 \leq i < j \leq |T|$，如果 $T_i = $ `X` 且 $T_j = $ `1`，则分数加 $1$ 分。
- 对于每个 $1 \leq i < j \leq |T|$，如果 $T_i = $ `X` 且 $T_j = $ `2`，则分数加 $2$ 分。
- 以此类推，直到 $T_j = $ `9`，分数加 $9$ 分。

目标是选择一个排列 $P$，使得 $T$ 的分数最大，并输出该最大分数。

**说明/提示**

- $2 \leq N \leq 2 \times 10^5$
- $N$ 是整数
- $S_i$ 是由 `1` 到 `9` 的数字以及 `X` 组成的长度至少为 $1$ 的字符串
- $S_1, S_2, \ldots, S_N$ 的长度总和不超过 $2 \times 10^5$

**样例解释**

**样例 1**

输入：
```
3
1X3
59
XXX
```
输出：
```
71
```
解释：选择排列 $P = (3, 1, 2)$，得到字符串 $T = $ `XXX1X359`，分数为 $71$。

**样例 2**

输入：
```
10
X63X395XX
X2XX3X22X
13
3716XXX6
45X
X6XX
9238
281X92
1XX4X4XX6
54X9X711X1
```
输出：
```
3010
```

### 算法分类
贪心、排序

### 题解分析与结论

本题的核心是通过对字符串的排列顺序进行优化，使得拼接后的字符串分数最大化。由于分数的计算只与字符串中 `X` 和数字的相对位置有关，因此可以通过贪心策略来确定字符串的排列顺序。

**关键思路：**
1. **局部最优导致全局最优**：通过比较两个字符串的排列顺序对分数的影响，确定它们的相对位置。如果 $S_1$ 在 $S_2$ 前面比 $S_2$ 在 $S_1$ 前面更优，则 $S_1$ 应该排在 $S_2$ 前面。
2. **排序规则**：定义 $cnt_i$ 为字符串 $S_i$ 中 `X` 的数量，$sum_i$ 为字符串 $S_i$ 中数字的和。排序规则为 $cnt_i \times sum_j > cnt_j \times sum_i$，即 `X` 数量多且数字和小的字符串应排在前面。

**难点：**
1. **排序规则的推导**：需要理解如何通过局部比较来确定全局最优排列。
2. **实现细节**：在排序过程中，如何高效计算字符串的 `X` 数量和数字和，并确保排序的正确性。

### 高星题解推荐

#### 题解1：作者：FFTotoro (赞：6)
**星级：5**
**关键亮点：**
- 通过定义函数 $f(S)$ 计算字符串的分数，简化了排序规则的推导。
- 使用 `std::sort` 的 `cmp` 函数进行排序，代码简洁且高效。

**代码实现：**
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int f(string s){
    int p=0,c=0;
    for(auto &i:s){
        if(i=='X')p++;
        else c+=p*(i-48);
    }
    return c;
}
bool cmp(string s1,string s2){return f(s1+s2)>f(s2+s1);}
signed main(){
    int n; string g; cin>>n;
    vector<string> s(n);
    for(auto &i:s)cin>>i;
    sort(s.begin(),s.end(),cmp);
    for(auto &i:s)g+=i;
    cout<<f(g)<<endl;
    return 0;
}
```

#### 题解2：作者：Tsawke (赞：0)
**星级：4**
**关键亮点：**
- 通过结构体存储字符串的 `X` 数量和数字和，简化了排序规则的实现。
- 详细解释了排序规则的推导过程，便于理解。

**代码实现：**
```cpp
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
using namespace std;
int N;
struct Node{string S; int sum, cnt;}d[210000];
ll ans(0);
int main(){
    N = read();
    for(int i = 1; i <= N; ++i){
        cin >> d[i].S;
        for(auto c : d[i].S)
            if(c == 'X')++d[i].cnt;
            else d[i].sum += c - '0';
    }sort(d + 1, d + N + 1, [](const Node &a, const Node &b)->bool{return (ll)a.sum * b.cnt < (ll)b.sum * a.cnt;});
    ll cur(0);
    for(int i = 1; i <= N; ++i)
        for(auto c : d[i].S)
            if(c == 'X')++cur;
            else ans += cur * (c - '0');
    printf("%lld\n", ans);
    return 0;
}
```

### 最优关键思路
通过贪心策略，比较两个字符串的排列顺序对分数的影响，确定它们的相对位置。具体来说，如果 $S_1$ 在 $S_2$ 前面比 $S_2$ 在 $S_1$ 前面更优，则 $S_1$ 应该排在 $S_2$ 前面。排序规则为 $cnt_i \times sum_j > cnt_j \times sum_i$，即 `X` 数量多且数字和小的字符串应排在前面。

### 类似题目推荐
1. [P1012 拼数](https://www.luogu.com.cn/problem/P1012)
2. [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)
3. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)

---
处理用时：45.42秒