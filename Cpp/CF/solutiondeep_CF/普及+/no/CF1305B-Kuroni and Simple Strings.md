# 题目信息

# Kuroni and Simple Strings

## 题目描述

Now that Kuroni has reached 10 years old, he is a big boy and doesn't like arrays of integers as presents anymore. This year he wants a Bracket sequence as a Birthday present. More specifically, he wants a bracket sequence so complex that no matter how hard he tries, he will not be able to remove a simple subsequence!

We say that a string formed by $ n $ characters '(' or ')' is simple if its length $ n $ is even and positive, its first $ \frac{n}{2} $ characters are '(', and its last $ \frac{n}{2} $ characters are ')'. For example, the strings () and (()) are simple, while the strings )( and ()() are not simple.

Kuroni will be given a string formed by characters '(' and ')' (the given string is not necessarily simple). An operation consists of choosing a subsequence of the characters of the string that forms a simple string and removing all the characters of this subsequence from the string. Note that this subsequence doesn't have to be continuous. For example, he can apply the operation to the string ')()(()))', to choose a subsequence of bold characters, as it forms a simple string '(())', delete these bold characters from the string and to get '))()'.

Kuroni has to perform the minimum possible number of operations on the string, in such a way that no more operations can be performed on the remaining string. The resulting string does not have to be empty.

Since the given string is too large, Kuroni is unable to figure out how to minimize the number of operations. Can you help him do it instead?

A sequence of characters $ a $ is a subsequence of a string $ b $ if $ a $ can be obtained from $ b $ by deletion of several (possibly, zero or all) characters.

## 说明/提示

In the first sample, the string is '(()(('. The operation described corresponds to deleting the bolded subsequence. The resulting string is '(((', and no more operations can be performed on it. Another valid answer is choosing indices $ 2 $ and $ 3 $ , which results in the same final string.

In the second sample, it is already impossible to perform any operations.

## 样例 #1

### 输入

```
(()((```

### 输出

```
1
2
1 3```

## 样例 #2

### 输入

```
)(```

### 输出

```
0```

## 样例 #3

### 输入

```
(()())```

### 输出

```
1
4
1 2 5 6```

# AI分析结果

### 题目中文重写
# Kuroni与简单字符串

## 题目描述
现在Kuroni已经10岁了，他是个大孩子了，不再喜欢整数数组作为礼物。今年他想要一个括号序列作为生日礼物。更具体地说，他想要一个非常复杂的括号序列，无论他怎么努力，都无法从中移除一个简单子序列！

我们称一个由 $n$ 个字符 '(' 或 ')' 组成的字符串是简单的，如果它的长度 $n$ 是偶数且为正，它的前 $\frac{n}{2}$ 个字符是 '('，并且它的后 $\frac{n}{2}$ 个字符是 ')'。例如，字符串 () 和 (()) 是简单的，而字符串 )( 和 ()() 不是简单的。

Kuroni会得到一个由字符 '(' 和 ')' 组成的字符串（给定的字符串不一定是简单的）。一次操作包括选择字符串中构成简单字符串的一个子序列，并从字符串中移除这个子序列的所有字符。注意，这个子序列不一定是连续的。例如，他可以对字符串 ')()(()))' 进行操作，选择加粗字符的子序列，因为它构成了一个简单字符串 '(())'，从字符串中删除这些加粗字符，得到 '))()'。

Kuroni必须对字符串执行最少次数的操作，使得对剩余的字符串不能再执行任何操作。得到的字符串不一定是空的。

由于给定的字符串太长，Kuroni无法想出如何最小化操作次数。你能帮他吗？

字符序列 $a$ 是字符串 $b$ 的子序列，如果 $a$ 可以通过删除 $b$ 中的若干（可能为零个或全部）字符得到。

## 说明/提示
在第一个样例中，字符串是 '(()(('。描述的操作对应于删除加粗的子序列。得到的字符串是 '(((', 并且不能再对它执行任何操作。另一个有效的答案是选择索引 2 和 3，这会得到相同的最终字符串。

在第二个样例中，已经不可能执行任何操作了。

## 样例 #1
### 输入
```
(()((
```
### 输出
```
1
2
1 3
```

## 样例 #2
### 输入
```
)(
```
### 输出
```
0
```

## 样例 #3
### 输入
```
(()())
```
### 输出
```
1
4
1 2 5 6
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是通过贪心策略来解决问题，目标是找到最少的操作次数使得括号序列不能再进行删除简单子序列的操作。大部分题解都发现最终结果要么操作次数为 0，要么为 1，因为可以通过一次操作尽可能多地删除可匹配的括号对。

各题解的主要区别在于实现方式：
- 有的题解通过前缀和与后缀和来找到合适的分割点，删除分割点左边的 '(' 和右边的 ')'。
- 有的题解使用双指针从字符串两端向中间扫描，匹配并删除括号对。
- 还有的题解通过模拟删除过程，直到无法再删除为止。

### 所选题解
- **xht（4星）**：
    - 关键亮点：思路清晰，通过前缀和与后缀和的方式找到合适的分割点，逻辑简单易懂。
- **cyh_toby（4星）**：
    - 关键亮点：双指针的实现方式简洁明了，并且对贪心思路有详细的分析。
- **皎月半洒花（4星）**：
    - 关键亮点：代码简洁，直接记录左右括号的位置，通过比较找到合适的删除方案。

### 重点代码
#### xht的题解
```cpp
const int N = 1e3 + 7;
int n, a[N], b[N];
char s[N];

int main() {
    rds(s, n);
    vi ans;
    for (int i = 1; i <= n; i++)
        a[i] = a[i-1] + (s[i] == '(');
    for (int i = n; i; i--)
        b[i] = b[i+1] + (s[i] == ')');
    for (int i = 0; i <= n; i++)
        if (a[i] == b[i+1]) {
            for (int j = 1; j <= i; j++)
                if (s[j] == '(') ans.pb(j);
            for (int j = i + 1; j <= n; j++)
                if (s[j] == ')') ans.pb(j);
            if (!ans.size()) {
                print(0);
                return 0;
            }
            print(1);
            print(ans.size());
            for (int x : ans) print(x, ' ');
            return 0;
        }
    return 0;
}
```
核心实现思想：通过前缀和数组 `a` 记录前 `i` 个字符中 '(' 的数量，后缀和数组 `b` 记录从第 `i` 个字符到末尾 ')' 的数量。找到一个位置 `i` 使得 `a[i] == b[i+1]`，则删除这个位置左边的 '(' 和右边的 ')' 即可。

#### cyh_toby的题解
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1005;
char s[N];
int a[N];
int flag = 0, tot = 0;
int main()
{
    scanf("%s", s+1);
    int n = strlen(s+1);
    for (int i = 1; i <= n; i++) {
        if (s[i] == '(') {
            a[i] = 1;
        }
        if (s[i] == ')') {
            a[i] = 2;
        }
    }
    int i = 1, j = n;
    while (1) {
        while (i <= j && (a[i]==2))
            i++;
        while (i <= j && (a[j]==1))
            j--;
        if (i >= j) {
            break;
        }
        a[i] = a[j] = -1;
        flag = 1;
        tot += 2;
        i++, j--;
    }
    if (flag) {
        printf("1\n%d\n", tot);
        for (int i = 1; i <= n; i++)
            if (a[i] == -1)
                printf("%d ", i);
    }
    else {
        printf("0\n");
    }
    return 0;
}
```
核心实现思想：使用双指针 `i` 和 `j` 分别从字符串的首尾向中间扫描，当 `i` 指向 '(' 且 `j` 指向 ')' 时，将这两个字符标记为已删除，继续移动指针，直到无法再匹配为止。

#### 皎月半洒花的题解
```cpp
int main(){
    cin >> (s + 1) ;
    int n = strlen(s + 1) ;
    for (int i = 1 ; i <= n ; ++ i){
        if (s[i] == '(') l[++ l[0]] = i, sum[i] = sum[i - 1] ;
        if (s[i] == ')') r[++ r[0]] = i, sum[i] = sum[i - 1] + 1 ;
    }
    for (int i = 0 ; i <= n ; ++ i)
        if (sum[i] == i && sum[i] == sum[n]) return puts("0"), 0 ;
    int L = 1, R = r[0] ;
    while (1){
        if (l[L] > r[R]) break ; ++ ans;
        stk[++ tp] = l[L], stk[++ tp] = r[R] ;
        L ++ ; R -- ; if (L > l[0] || !R) break ;
    }
    sort(stk + 1, stk + tp + 1) ;
    cout << 1 << endl << ans * 2 << endl ;
    for (int i = 1 ; i <= ans * 2 ; ++ i) cout << stk[i] << " " ;
}
```
核心实现思想：分别记录所有左括号和右括号的位置，通过比较找到合适的删除方案。如果存在某个位置 `i` 使得前缀都是 ')' 且后缀都是 '('，则操作次数为 0，否则为 1。

### 最优关键思路或技巧
- 贪心策略：尽可能地删除左右括号对，使得剩余的字符串不能再进行删除操作。
- 双指针法：从字符串的两端向中间扫描，匹配并删除括号对，时间复杂度为 $O(n)$。

### 可拓展之处
同类型题或类似算法套路：
- 括号匹配相关问题，如判断括号序列是否合法、计算最大嵌套深度等。
- 字符串处理中的贪心算法，如删除某些字符使得字符串满足特定条件。

### 推荐洛谷题目
- P1739 表达式括号匹配
- P1241 括号序列
- P5734 【深基6.例6】文字处理软件

### 个人心得
- **cyh_toby**：虽然理论上按上述过程想应该是对的，但不会严格证明，考场上试一试发现对的就交了，可能有点贪心的思路。总结：在考场上如果无法严格证明算法的正确性，可以通过样例测试来验证，尝试使用贪心思路解决问题。

---
处理用时：65.42秒