# 题目信息

# The Wu

## 题目描述

Childan is making up a legendary story and trying to sell his forgery — a necklace with a strong sense of "Wu" to the Kasouras. But Mr. Kasoura is challenging the truth of Childan's story. So he is going to ask a few questions about Childan's so-called "personal treasure" necklace.

This "personal treasure" is a multiset $ S $ of $ m $ "01-strings".

A "01-string" is a string that contains $ n $ characters "0" and "1". For example, if $ n=4 $ , strings "0110", "0000", and "1110" are "01-strings", but "00110" (there are $ 5 $ characters, not $ 4 $ ) and "zero" (unallowed characters) are not.

Note that the multiset $ S $ can contain equal elements.

Frequently, Mr. Kasoura will provide a "01-string" $ t $ and ask Childan how many strings $ s $ are in the multiset $ S $ such that the "Wu" value of the pair $ (s, t) $ is not greater than $ k $ .

Mrs. Kasoura and Mr. Kasoura think that if $ s_i = t_i $ ( $ 1\leq i\leq n $ ) then the "Wu" value of the character pair equals to $ w_i $ , otherwise $ 0 $ . The "Wu" value of the "01-string" pair is the sum of the "Wu" values of every character pair. Note that the length of every "01-string" is equal to $ n $ .

For example, if $ w=[4, 5, 3, 6] $ , "Wu" of ("1001", "1100") is $ 7 $ because these strings have equal characters only on the first and third positions, so $ w_1+w_3=4+3=7 $ .

You need to help Childan to answer Mr. Kasoura's queries. That is to find the number of strings in the multiset $ S $ such that the "Wu" value of the pair is not greater than $ k $ .

## 说明/提示

In the first example, we can get:

"Wu" of ("01", "00") is $ 40 $ .

"Wu" of ("10", "00") is $ 20 $ .

"Wu" of ("11", "00") is $ 0 $ .

"Wu" of ("01", "11") is $ 20 $ .

"Wu" of ("10", "11") is $ 40 $ .

"Wu" of ("11", "11") is $ 60 $ .

In the first query, pairs ("11", "00") and ("10", "00") satisfy the condition since their "Wu" is not greater than $ 20 $ .

In the second query, all strings satisfy the condition.

In the third query, pairs ("01", "11") and ("01", "11") satisfy the condition. Note that since there are two "01" strings in the multiset, the answer is $ 2 $ , not $ 1 $ .

In the fourth query, since $ k $ was increased, pair ("10", "11") satisfies the condition too.

In the fifth query, since $ k $ was increased, pair ("11", "11") satisfies the condition too.

## 样例 #1

### 输入

```
2 4 5
40 20
01
01
10
11
00 20
00 40
11 20
11 40
11 60
```

### 输出

```
2
4
2
3
4
```

## 样例 #2

### 输入

```
1 2 4
100
0
1
0 0
0 100
1 0
1 100
```

### 输出

```
1
2
1
2
```

# AI分析结果

### 题目内容
# 吴之项链

## 题目描述
柴丹正在编造一个传奇故事，并试图将他伪造的一条带有强烈“吴”感的项链卖给卡苏拉一家。但卡苏拉先生对柴丹故事的真实性提出了质疑。因此，他打算就柴丹所谓的“传家之宝”项链提出一些问题。

这条“传家之宝”是一个由 $m$ 个“01字符串”组成的多重集 $S$。

“01字符串”是指包含 $n$ 个字符“0”和“1”的字符串。例如，如果 $n = 4$，字符串“0110”、“0000”和“1110”是“01字符串”，但“00110”（有5个字符，不是4个）和“zero”（包含不允许的字符）则不是。

请注意，多重集 $S$ 可以包含相同的元素。

卡苏拉先生经常会给出一个“01字符串” $t$，并询问柴丹，在多重集 $S$ 中有多少个字符串 $s$，使得对 $(s, t)$ 的“吴”值不大于 $k$。

卡苏拉夫人和卡苏拉先生认为，如果 $s_i = t_i$（$1 \leq i \leq n$），那么字符对的“吴”值等于 $w_i$，否则为 $0$。“01字符串”对的“吴”值是每个字符对的“吴”值之和。请注意，每个“01字符串”的长度都等于 $n$。

例如，如果 $w = [4, 5, 3, 6]$，“1001”和“1100”的“吴”值为 $7$，因为这两个字符串仅在第一个和第三个位置上的字符相同，所以 $w_1 + w_3 = 4 + 3 = 7$。

你需要帮助柴丹回答卡苏拉先生的询问。即找出多重集 $S$ 中，使得“吴”值不大于 $k$ 的字符串数量。

## 说明/提示
在第一个示例中，我们可以得到：
 - “01”和“00”的“吴”值为 $40$。
 - “10”和“00”的“吴”值为 $20$。
 - “11”和“00”的“吴”值为 $0$。
 - “01”和“11”的“吴”值为 $20$。
 - “10”和“11”的“吴”值为 $40$。
 - “11”和“11”的“吴”值为 $60$。

在第一个查询中，对（“11”，“00”）和（“10”，“00”）满足条件，因为它们的“吴”值不大于 $20$。

在第二个查询中，所有字符串都满足条件。

在第三个查询中，对（“01”，“11”）和（“01”，“11”）满足条件。请注意，由于多重集中有两个“01”字符串，所以答案是 $2$，而不是 $1$。

在第四个查询中，由于 $k$ 增加了，对（“10”，“11”）也满足条件。

在第五个查询中，由于 $k$ 增加了，对（“11”，“11”）也满足条件。

## 样例 #1
### 输入
```
2 4 5
40 20
01
01
10
11
00 20
00 40
11 20
11 40
11 60
```
### 输出
```
2
4
2
3
4
```

## 样例 #2
### 输入
```
1 2 4
100
0
1
0 0
0 100
1 0
1 100
```
### 输出
```
1
2
1
2
```

### 算法分类
前缀和

### 综合分析与结论
这些题解的核心思路都是利用01串长度 $n$ 较小（$n \leq 12$）这一特点，将01串状态压缩为整数表示，通过预处理所有可能的01串对的“吴”值，并统计每种“吴”值对应的字符串数量，最后利用前缀和来快速回答查询。

各题解的主要区别在于实现细节和代码风格：
 - **思路方面**：都基于状态压缩和前缀和的思想，通过枚举所有可能的01串对来计算“吴”值，并统计结果。
 - **算法要点**：将01串转换为整数，利用二维数组存储每种01串与不同“吴”值对应的数量，最后通过前缀和优化查询。
 - **解决难点**：如何高效地计算01串对的“吴”值，并处理大量重复的01串。各题解通过状态压缩和预处理来解决这一难点。

### 题解1
 - **星级**：4星
 - **关键亮点**：思路清晰，代码实现直接，详细展示了从输入处理到预处理再到查询回答的全过程。
 - **个人心得**：作者提到用C#实现时因时间限制超时，翻译成C++后才通过，说明语言特性和性能对解题的影响。

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 4096;

int n, m, q;
char s[20];
int w[20], cnt[N], sum[N][110];

inline int calc(int x, int y) // 计算权值。
{
    int res = 0;
    for (int i = 0; i < n; i ++ )
        if ((x >> i & 1) == (y >> i & 1))
            res += w[n - i - 1]; 
    return res;
}

int main()
{
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 0; i < n; i ++ ) scanf("%d", &w[i]);
    while (m -- )
    {
        scanf("%s", s);
        int cur = 0;
        for (int i = 0; s[i]; i ++ ) 
            cur = cur * 2 + s[i] - '0';
        cnt[cur] ++ ; 
    }
    for (int i = 0; i < N; i ++ ) 
        for (int j = 0; j < N; j ++ )
        {
            int s = calc(i, j);
            if (s <= 100) sum[i][s] += cnt[j];
        }
    for (int i = 0; i < N; i ++ ) 
        for (int j = 1; j <= 100; j ++ )
            sum[i][j] += sum[i][j - 1];
    
    while (q -- )
    {
        int k;
        scanf("%s%d", s, &k);
        int cur = 0;
        for (int i = 0; s[i]; i ++ )
            cur = cur * 2 + s[i] - '0';
        printf("%d\n", sum[cur][k]); 
    }
    
    return 0;
}
```
核心实现思想：`calc`函数计算两个状态压缩后的01串的“吴”值。主函数中，先读入数据并统计每个01串出现的次数，然后通过双重循环枚举所有01串对，计算“吴”值并更新`sum`数组，最后对`sum`数组求前缀和。查询时，将输入的01串转换为整数，直接从`sum`数组中获取答案。

### 题解2
 - **星级**：4星
 - **关键亮点**：在计算“吴”值时，通过位运算优化了计算过程，提高了效率。

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 4096;

int n, m, q;
char s[20];
int w[20], cur[N], cnt[N], sum[N][110];

int main()
{
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 0; i < n; i ++ ) scanf("%d", &w[i]);
    while (m -- )
    {
        scanf("%s", s);
        int cur = 0;
        for (int i = 0; s[i]; i ++ ) 
            cur = cur * 2 + s[i] - '0';
        cnt[cur] ++ ; 
    }
    for (int i = 0; i < N; i ++ )
    {
        for (int j = 0; j < n; j ++ )
            if (i >> j & 1)
                cur[i] += w[n - j - 1];
    }
    for (int i = 0; i < N; i ++ ) 
        for (int j = 0; j < N; j ++ )
        {
            int s = cur[i ^ j ^ ((1 << n) - 1)];
            if (s <= 100) sum[i][s] += cnt[j];
        }
    for (int i = 0; i < N; i ++ ) 
        for (int j = 1; j <= 100; j ++ )
            sum[i][j] += sum[i][j - 1];
    
    while (q -- )
    {
        int k;
        scanf("%s%d", s, &k);
        int cur = 0;
        for (int i = 0; s[i]; i ++ )
            cur = cur * 2 + s[i] - '0';
        printf("%d\n", sum[cur][k]); 
    }
    
    return 0;
}
```
核心实现思想：通过预处理`cur`数组，记录每个状态压缩后的01串中对应位为1时的权值和。在计算两个01串的“吴”值时，通过`i ^ j ^ ((1 << n) - 1)`得到需要计算权值和的位，直接从`cur`数组获取“吴”值，其余部分与题解1类似。

### 题解3
 - **星级**：4星
 - **关键亮点**：代码结构清晰，将字符串转数值、预处理等操作封装成函数，提高了代码的可读性和可维护性。

```cpp
#include <bits/stdc++.h>
#define int long long

const int ML = 20, N = 5e5 + 10, MV = (1 << 12) + 10; 
int len, n, q, w[ML], cnt[MV], dp[MV][110];


void work() {
	for (int s1 = 0; s1 < (1 << len); ++ s1)
		if (cnt[s1]) 
			for (int s2 = 0; s2 < (1 << len); ++ s2) {
				int ret = 0;
				for (int bit = 0; bit < len; ++ bit) {
					int b1 = s1 & (1 << bit), b2 = s2 & (1 << bit);
					if (b1 == b2) ret += w[len - bit]; 
				}
				if (ret <= 100) dp[s2][ret] += cnt[s1]; 
			}
	for (int s = 0; s < (1 << len); ++ s)	
		for (int j = 1; j <= 100; ++ j)	dp[s][j] += dp[s][j - 1];
	return void(); 
}

int to(std::string str) {
	int ret = 0;  
	for (int j = 0; j < len; ++ j)
		if (str[j] == '1') ret += (1 << len - 1 - j);
	return ret; 
}

signed main() {
	
	std::ios::sync_with_stdio(false), std::cin.tie(nullptr), std::cout.tie(nullptr); 
	
	std::cin >> len >> n >> q;
	for (int i = 1; i <= len; ++ i) std::cin >> w[i]; 
	
	for (int i = 1; i <= n; ++ i) {
		std::string str; std::cin >> str;
		++ cnt[to(str)]; 
	}
	work(); 
	while (q --> 0) {
		std::string str; std::cin >> str;
		int k; std::cin >> k;
		std::cout << dp[to(str)][k] << "\n";
	}
	
	
	return 0; 
}
```
核心实现思想：`to`函数将字符串转换为状态压缩后的整数。`work`函数负责预处理，枚举所有可能的01串对计算“吴”值并更新`dp`数组，最后对`dp`数组求前缀和。主函数中读入数据，调用`work`函数预处理，然后在查询时将输入字符串转换为整数，从`dp`数组获取答案。

### 最优关键思路或技巧
 - **状态压缩**：利用01串长度小的特点，将01串转换为整数表示，大大减少了数据处理量。
 - **前缀和优化**：通过预处理所有可能的“吴”值，并利用前缀和，使得每次查询的时间复杂度降为 $O(1)$。
 - **位运算优化**：部分题解通过位运算快速计算“吴”值，提高了预处理的效率。

### 拓展
此类题目通常具有数据规模较小、状态可压缩的特点。类似套路是先对状态进行压缩，然后通过预处理和前缀和等方式优化查询操作。常见于字符串匹配、状态计数等问题中。

### 洛谷推荐题目
 - [P1387 最大正方形](https://www.luogu.com.cn/problem/P1387)：通过前缀和优化动态规划，求解最大正方形问题，与本题利用前缀和优化查询有相似之处。
 - [P1144 最短路计数](https://www.luogu.com.cn/problem/P1144)：利用广度优先搜索和前缀和思想，统计最短路的数量，涉及到状态的记录和查询优化。
 - [P2216 [HAOI2007]理想的正方形](https://www.luogu.com.cn/problem/P2216)：通过二维前缀和优化枚举过程，求解满足条件的理想正方形，与本题在优化枚举和查询方面思路类似。

### 个人心得摘录与总结
 - **Mickey_snow**：作者在C#实现时遇到时间超时问题，翻译成C++后成功AC，强调了语言性能对解题的影响，提醒在选择编程语言时需考虑题目时间限制。 

---
处理用时：108.93秒