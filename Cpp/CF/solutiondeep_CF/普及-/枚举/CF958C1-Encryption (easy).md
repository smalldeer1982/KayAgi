# 题目信息

# Encryption (easy)

## 题目描述

Rebel spy Heidi has just obtained the plans for the Death Star from the Empire and, now on her way to safety, she is trying to break the encryption of the plans (of course they are encrypted – the Empire may be evil, but it is not stupid!). The encryption has several levels of security, and here is how the first one looks.

Heidi is presented with a screen that shows her a sequence of integers $ A $ and a positive integer $ p $ . She knows that the encryption code is a single number $ S $ , which is defined as follows:

Define the score of $ X $ to be the sum of the elements of $ X $ modulo $ p $ .

Heidi is given a sequence $ A $ that consists of $ N $ integers, and also given an integer $ p $ . She needs to split $ A $ into $ 2 $ parts such that:

- Each part contains at least $ 1 $ element of $ A $ , and each part consists of contiguous elements of $ A $ .
- The two parts do not overlap.
- The total sum $ S $ of the scores of those two parts is maximized. This is the encryption code.

Output the sum $ S $ , which is the encryption code.

## 说明/提示

In the first example, the score is maximized if the input sequence is split into two parts as $ (3,4) $ , $ (7,2) $ . It gives the total score of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF958C1/39bbc2e047bed6ad62ef40401430a139534974d3.png).

In the second example, the score is maximized if the first part consists of the first three elements, and the second part consists of the rest. Then, the score is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF958C1/d991bcec92c9c10d8e1b00b096112e99ba9e2d35.png).

## 样例 #1

### 输入

```
4 10
3 4 7 2
```

### 输出

```
16
```

## 样例 #2

### 输入

```
10 12
16 3 24 13 9 8 7 5 12 12
```

### 输出

```
13
```

# AI分析结果

### 题目中文重写
# 加密（简单版）

## 题目描述
反叛间谍海蒂刚刚从帝国那里获取了死星的设计图，现在她正前往安全地带，同时试图破解设计图的加密（当然，设计图是加密的——帝国也许邪恶，但并不愚蠢！）。加密有多个安全级别，以下是第一个级别的情况。

海蒂面前的屏幕上显示着一个整数序列 $A$ 和一个正整数 $p$。她知道加密代码是一个单一的数字 $S$，其定义如下：

定义 $X$ 的得分是 $X$ 中元素的和对 $p$ 取模的结果。

海蒂得到一个由 $N$ 个整数组成的序列 $A$，以及一个整数 $p$。她需要将 $A$ 分成两部分，使得：
- 每部分至少包含 $A$ 中的一个元素，且每部分由 $A$ 中连续的元素组成。
- 这两部分不重叠。
- 这两部分得分的总和 $S$ 最大。这个总和就是加密代码。

输出总和 $S$，即加密代码。

## 说明/提示
在第一个样例中，如果将输入序列拆分为两部分 $(3,4)$ 和 $(7,2)$，得分最大。此时总得分是 [此处应是具体得分公式图片]。

在第二个样例中，如果第一部分由前三个元素组成，第二部分由其余元素组成，得分最大。此时得分是 [此处应是具体得分公式图片]。

## 样例 #1
### 输入
```
4 10
3 4 7 2
```
### 输出
```
16
```

## 样例 #2
### 输入
```
10 12
16 3 24 13 9 8 7 5 12 12
```
### 输出
```
13
```

### 综合分析与结论
- **思路**：各题解思路一致，都是通过枚举分割点将序列分成两部分，计算两部分元素和对 $p$ 取模后的和，取最大值作为结果。
- **算法要点**：均使用前缀和优化区间求和，将原本 $O(n^2)$ 的时间复杂度优化到 $O(n)$。
- **解决难点**：主要解决了如何高效计算不同分割方式下两部分元素和的问题，避免了重复计算。

### 题解评分
| 作者 | 评分 | 理由 |
| ---- | ---- | ---- |
| chlchl | 4星 | 思路清晰，代码简洁，对关键注意点有明确提示。 |
| CrazyWisdom | 3星 | 思路明确，但代码中存在不必要的变量，如 `Sum`。 |
| Milthm | 3星 | 思路讲解详细，但代码注释可进一步完善。 |
| Coros_Trusds | 2星 | 代码复杂，引入了大量模板代码，影响可读性。 |
| Noby_Glds | 3星 | 代码简洁，但思路阐述较简略。 |
| 智子 | 3星 | 思路清晰，但代码中使用了前缀和与后缀和，增加了空间复杂度。 |

### 所选题解
- **chlchl（4星）**
    - **关键亮点**：思路清晰，代码简洁，对分割点的边界情况有明确提示。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 1e5 + 10;
int n;
ll p, ans, s[N];

int main(){
    scanf("%d%lld", &n, &p);
    for(int i=1;i<=n;i++)    scanf("%lld", &s[i]), s[i] += s[i - 1];
    for(int i=1;i<n;i++){
        ans = max(ans, s[i] % p + (s[n] - s[i]) % p);
    }
    printf("%lld\n", ans);
    return 0;
}
```
**核心实现思想**：先预处理前缀和数组 `s`，然后枚举分割点 `i`，计算两部分元素和对 $p$ 取模后的和，更新最大值 `ans`。

### 最优关键思路或技巧
使用前缀和优化区间求和，避免重复计算，将时间复杂度从 $O(n^2)$ 降低到 $O(n)$。

### 拓展思路
同类型题可拓展到将序列分成 $k$ 部分（$k > 2$），求各部分得分总和的最大值，可使用动态规划解决。类似算法套路还有区间和查询问题，可使用前缀和、树状数组、线段树等数据结构优化。

### 推荐题目
- [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)
- [P2671 [NOIP2015 普及组] 求和](https://www.luogu.com.cn/problem/P2671)
- [P3131 [USACO16JAN]Subsequences Summing to Sevens S](https://www.luogu.com.cn/problem/P3131)

### 个人心得摘录与总结
- **智子**：在学校模拟赛中看错题面导致思考 10 分钟，提醒我们做题时要仔细审题。 

---
处理用时：27.74秒