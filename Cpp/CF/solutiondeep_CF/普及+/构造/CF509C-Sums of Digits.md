# 题目信息

# Sums of Digits

## 题目描述

Vasya had a strictly increasing sequence of positive integers $ a_{1} $ , ..., $ a_{n} $ . Vasya used it to build a new sequence $ b_{1} $ , ..., $ b_{n} $ , where $ b_{i} $ is the sum of digits of $ a_{i} $ 's decimal representation. Then sequence $ a_{i} $ got lost and all that remained is sequence $ b_{i} $ .

Vasya wonders what the numbers $ a_{i} $ could be like. Of all the possible options he likes the one sequence with the minimum possible last number $ a_{n} $ . Help Vasya restore the initial sequence.

It is guaranteed that such a sequence always exists.

## 样例 #1

### 输入

```
3
1
2
3
```

### 输出

```
1
2
3
```

## 样例 #2

### 输入

```
3
3
2
1
```

### 输出

```
3
11
100
```

# AI分析结果

### 题目内容中文重写
# 数字之和

## 题目描述

Vasya 有一个严格递增的正整数序列 $ a_{1} $,..., $ a_{n} $。Vasya 用它构建了一个新的序列 $ b_{1} $,..., $ b_{n} $，其中 $ b_{i} $ 是 $ a_{i} $ 的十进制表示中各位数字之和。然后序列 $ a_{i} $ 丢失了，只剩下序列 $ b_{i} $。

Vasya 想知道序列 $ a_{i} $ 可能是什么样子。在所有可能的选项中，他喜欢最后一个数字 $ a_{n} $ 尽可能小的那个序列。请帮助 Vasya 恢复初始序列。

保证这样的序列总是存在。

## 样例 #1

### 输入
```
3
1
2
3
```

### 输出
```
1
2
3
```

## 样例 #2

### 输入
```
3
3
2
1
```

### 输出
```
3
11
100
```

### 综合分析与结论
这些题解的核心目标都是根据给定的序列 $b$ 还原出序列 $a$，使得 $a$ 严格递增且 $a_n$ 尽可能小。

#### 思路对比
- **贪心构造**：大部分题解采用贪心策略，先让 $a_1$ 尽可能小，从右往左尽可能多填 9，剩余数字填入高位。对于后续的 $a_i$，根据 $b_i$ 和 $b_{i - 1}$ 的大小关系分类讨论构造。
- **数位 DP**：Hadtsti 的题解使用数位 DP 实现 `calc(x, y)` 函数，通过固定前 $i - 1$ 位、枚举第 $i$ 位来找到满足条件的最小数。

#### 算法要点对比
- **贪心算法**：
    - 先确定 $a_1$ 的最小值。
    - 对于 $b_i > b_{i - 1}$，直接在 $a_{i - 1}$ 基础上按贪心原则添加差值。
    - 对于 $b_i \leq b_{i - 1}$，找到合适位置增加数字并重新分配低位。
- **数位 DP**：预处理满足条件的最小答案，通过枚举数位找到满足和为 $x$ 且大于 $y$ 的最小数。

#### 解决难点对比
- **贪心算法**：主要难点在于处理 $b_i \leq b_{i - 1}$ 的情况，需要找到合适的位置增加数字并保证合法性。
- **数位 DP**：难点在于状态的定义和转移，以及如何高效地预处理和枚举。

### 所选题解
- **Silence_water（5星）**
    - **关键亮点**：思路清晰，详细解释了贪心算法的实现过程，通过分类讨论和具体例子说明，代码简洁易懂。
    - **核心代码**：
```cpp
void gota(int x)
{
    int pos = 0;
    while (x > 0)
    {
        x -= 9 - c[++pos];
        c[pos] = 9;
    }
    c[pos] += x;
    if (pos > len) len = pos;
}

for (int i = 2; i <= n; i++)
{
    if (b[i] > b[i - 1])
        gota(b[i] - b[i - 1]);
    else
    {
        int dis = b[i] - b[i - 1], pos = 1;
        while (dis <= 0 || c[pos] == 9)
            dis += c[pos], c[pos++] = 0;
        c[pos]++;
        gota(dis - 1);
        if (pos > len) len = pos;
    }
    print(len);
}
```
    - **核心实现思想**：`gota` 函数用于贪心地构造总和为 $x$ 的最小正整数。在主循环中，根据 $b[i]$ 和 $b[i - 1]$ 的大小关系分类处理，对于 $b[i] \leq b[i - 1]$ 的情况，找到合适位置增加数字并重新分配剩余数字。

- **CarroT1212（4星）**
    - **关键亮点**：将“$a$ 严格递增”条件转化为更易处理的形式，通过枚举大于 $a_{i - 1}$ 的数位来构造 $a_i$，代码逻辑清晰。
    - **核心代码**：
```cpp
for (int i = 1; i <= n; i++) {
    scanf("%d", &b[i]);
    int sum = 0;
    for (int j = 1; j <= len[i - 1]; j++) sum += str[i - 1][j];
    for (int j = 1;; j++) {
        sum -= str[i - 1][j];
        if (str[i - 1][j]!= 9) {
            if (sum + str[i - 1][j] + 1 <= b[i] && b[i] <= sum + 9 * j) {
                len[i] = max(len[i - 1], j);
                for (int k = j + 1; k <= len[i - 1]; k++) str[i][k] = str[i - 1][k];
                str[i][j] = max(str[i - 1][j] + 1, b[i] - sum - 9 * (j - 1));
                int cnt = b[i] - sum - str[i][j];
                for (int k = 1; cnt > 0; k++, cnt -= 9) str[i][k] = min(cnt, 9);
                break;
            }
        }
    }
    for (int j = len[i]; j; printf("%d", str[i][j--]));
    printf("\n");
}
```
    - **核心实现思想**：枚举大于 $a_{i - 1}$ 的数位 $j$，判断是否满足数位和条件，若满足则构造 $a_i$，$j$ 后面的数位与 $a_{i - 1}$ 相同，$a_{i,j}$ 优先填 $a_{i - 1,j} + 1$，然后贪心地填前面的数位。

- **SUNCHAOYI（4星）**
    - **关键亮点**：将构造过程分为三种情况，分别编写函数处理，代码结构清晰，便于理解和维护。
    - **核心代码**：
```cpp
string easy_make(int x)
{
    string s = "";
    for (int i = 1; i <= x / 9; ++i) s += '9';
    x %= 9;
    if (x) s = char(x + 48) + s;
    return s;
}

string medium_make(string la, int x)
{
    int len = la.size();
    int sum = x;
    string s = "";
    for (int i = 0; i < len; ++i) sum -= la[i] - '0';
    for (int i = len - 1; ~i; --i)
    {
        if (!sum) s = la[i] + s;
        else s = char(la[i] + min(9 - (la[i] - '0'), sum)) + s, sum -= min(9 - (la[i] - '0'), sum);
    }
    return easy_make(sum) + s;
}

string hard_make(string la, int x)
{
    int len = la.size();
    for (int i = len - 1; ~i; --i)
    {
        if (la[i]!= '9')
        {
            string s = "";
            int sum = 0;
            for (int j = 0; j < i; ++j) s += la[j], sum += la[j] - '0';
            s += char(la[i] + 1);
            sum += la[i] - '0' + 1;
            if (x - sum < 0) continue;
            string nw = easy_make(x - sum);
            int p = len - s.size() - nw.size();
            for (int j = 1; j <= p; ++j) s += '0';
            return s + nw;
        }
    }
    string s = "1";
    ++len;
    string nw = easy_make(x - 1);
    int p = len - s.size() - nw.size();
    for (int i = 1; i <= p; ++i) s += '0';
    return s + nw;
}
```
    - **核心实现思想**：`easy_make` 函数直接贪心构造总和为 $x$ 的最小数；`medium_make` 函数在 $b_i > b_{i - 1}$ 时，在 $a_{i - 1}$ 基础上添加差值；`hard_make` 函数在 $b_i \leq b_{i - 1}$ 时，找到合适位置增加数字并重新分配剩余数字。

### 最优关键思路或技巧
- **贪心策略**：让每一位数尽可能小，优先从低位填 9，可使构造的数最小。
- **分类讨论**：根据 $b_i$ 和 $b_{i - 1}$ 的大小关系分类处理，简化问题。
- **条件转化**：将“$a$ 严格递增”转化为更易处理的形式，便于枚举和构造。

### 拓展思路
同类型题可能会改变序列的限制条件，如非严格递增、满足特定的数学关系等，解题思路仍可围绕贪心构造和分类讨论展开。类似算法套路可用于解决一些需要根据特定条件构造序列或数字的问题。

### 推荐题目
- [P1002 过河卒](https://www.luogu.com.cn/problem/P1002)：涉及路径规划和状态转移，可锻炼动态规划和贪心思想。
- [P1216 [USACO1.5][IOI1994]数字三角形 Number Triangles](https://www.luogu.com.cn/problem/P1216)：经典的动态规划问题，与本题的状态构造和转移有相似之处。
- [P1048 [NOIP2005 普及组] 采药](https://www.luogu.com.cn/problem/P1048)：考察贪心和动态规划的应用，可提升解决构造问题的能力。

### 个人心得
本题解中未包含个人心得内容。

---
处理用时：56.83秒