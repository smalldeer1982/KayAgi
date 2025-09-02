# 题目信息

# Vasya and Golden Ticket

## 题目描述

Recently Vasya found a golden ticket — a sequence which consists of $ n $ digits $ a_1a_2\dots a_n $ . Vasya considers a ticket to be lucky if it can be divided into two or more non-intersecting segments with equal sums. For example, ticket $ 350178 $ is lucky since it can be divided into three segments $ 350 $ , $ 17 $ and $ 8 $ : $ 3+5+0=1+7=8 $ . Note that each digit of sequence should belong to exactly one segment.

Help Vasya! Tell him if the golden ticket he found is lucky or not.

## 说明/提示

In the first example the ticket can be divided into $ 7 $ , $ 34 $ and $ 52 $ : $ 7=3+4=5+2 $ .

In the second example it is impossible to divide ticket into segments with equal sum.

## 样例 #1

### 输入

```
5
73452
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
4
1248
```

### 输出

```
NO
```

# AI分析结果

### 题目翻译
# 瓦西亚和金色门票

## 题目描述
最近，瓦西亚发现了一张金色门票 —— 一个由 $n$ 个数字 $a_1a_2\dots a_n$ 组成的序列。瓦西亚认为，如果一张门票可以被分成两个或更多不相交的段，且这些段的数字之和相等，那么这张门票就是幸运的。例如，门票 $350178$ 是幸运的，因为它可以被分成三段 $350$、$17$ 和 $8$，且 $3 + 5 + 0 = 1 + 7 = 8$。请注意，序列中的每个数字都应恰好属于一个段。

请帮助瓦西亚！告诉他他找到的金色门票是否幸运。

## 说明/提示
在第一个样例中，门票可以被分成 $7$、$34$ 和 $52$，即 $7 = 3 + 4 = 5 + 2$。

在第二个样例中，不可能将门票分成数字之和相等的段。

## 样例 #1
### 输入
```
5
73452
```
### 输出
```
YES
```

## 样例 #2
### 输入
```
4
1248
```
### 输出
```
NO
```

### 题解综合分析与结论
这些题解主要围绕判断一个数字序列能否拆分成多个和相等的非相交子段展开，核心都是通过枚举和验证的方式来解决问题。
- **思路对比**：
    - **暴力搜索类**：XUQING 的题解采用深度优先搜索（DFS），从序列头部开始不断尝试分割子段，若子段和相等则递归搜索剩余部分。
    - **枚举分段数类**：lichenfan 和 _Qer 的题解通过枚举分成的段数 $k$，判断总和能否被 $k$ 整除，若能则尝试分割序列。
    - **枚举前缀和类**：KKarshilov 的题解枚举从 1 开始的前缀和，将其作为每段的和，然后检查能否将序列分割成和相等的段。
- **算法要点**：
    - 计算序列的总和。
    - 枚举可能的分割方式，如段数、前缀和等。
    - 验证分割后的子段和是否相等。
- **解决难点**：
    - 避免不必要的搜索，如当子段和超过目标和时进行剪枝（XUQING、lichenfan 等）。
    - 处理边界情况，如序列长度为 1 或全为 0 的情况（KKarshilov、KagurazakaKano）。

### 高评分题解
- **XUQING（5星）**
    - **关键亮点**：思路清晰，使用 DFS 进行暴力搜索，通过剪枝优化了搜索过程，代码注释详细。
    - **个人心得**：作者提到看到数据量不大，第一想法就是暴力搜索，尝试后通过了题目。
    - **核心代码**：
```cpp
bool dfs(string s, int tot, int f)
{
    if(s.length() == 1 && s[0] - '0' == tot)
        return true;

    for(int i = 1; i <= s.length(); i++)
    {
        int ans = sum(s.substr(0, i));

        if(i == s.length() && ans == tot)
            return true;
        if(ans > tot && f)
            return false;

        if(ans == tot ||!f)
        {
            bool b = dfs(s.substr(i, s.length()+1), ans, f + 1);
            if(b)
                return true;
        }
    }
    return false;
}
```
- **lichenfan（4星）**
    - **关键亮点**：通过枚举分成的段数，模拟分割过程，代码简洁易懂。
    - **核心代码**：
```cpp
for(int i = 2; i <= n; i++){
    ans = 0;
    if(sum%i==0){
        for(int j = 1; j <= n; j++){
            ans += a[j];
            if(ans == sum/i) ans = 0;
            if(ans > sum/i) break;
            if(j == n){
                cout << "YES";
                return 0;
            }
        }
    }
}
```
- **_Qer（4星）**
    - **关键亮点**：思路与 lichenfan 类似，但代码结构更清晰，通过封装检查函数提高了代码的可读性。
    - **核心代码**：
```cpp
bool check(int s) {
    int tsum = 0;
    for (int i = 1; i <= n; ++i) {
        tsum += a[i];
        if (tsum == s) {
            tsum = 0;
        } else if (tsum > s) {
            return false;
        }
    }
    return!tsum;
}
for (int i = 2; i <= n; ++i) {
    if (sum % i == 0 && check(sum / i)) {
        puts("YES");
        return 0;
    }
}
```

### 最优关键思路或技巧
- **剪枝优化**：在搜索过程中，当子段和超过目标和时，停止搜索，避免不必要的计算。
- **枚举策略**：通过枚举分成的段数或前缀和，缩小搜索范围，提高效率。

### 可拓展之处
同类型题目可能会有不同的分割规则或条件，如要求分割的段数必须为奇数、分割的段长度有一定限制等。解题思路仍然是枚举可能的分割方式，并验证是否满足条件。

### 洛谷相似题目推荐
- P1181 数列分段 Section I：给定一个数列和一个整数 $m$，要求将数列分成 $m$ 段，使得每段的和的最大值最小。
- P2678 跳石头：在一条河上有若干块石头，要求移除不超过 $m$ 块石头，使得相邻两块石头之间的最短距离最大。
- P3853 [TJOI2007]路标设置：在一条公路上有若干个路标，要求在公路上添加不超过 $k$ 个路标，使得相邻两个路标之间的最大距离最小。

---
处理用时：35.19秒