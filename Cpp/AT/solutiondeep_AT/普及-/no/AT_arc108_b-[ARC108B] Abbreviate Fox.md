# 题目信息

# [ARC108B] Abbreviate Fox

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc108/tasks/arc108_b

長さ $ N $ の英小文字のみからなる文字列 $ s $ が与えられます。 すぬけ君は $ s $ から `fox` という部分文字列を $ 1 $ つ選んで取り除き、その前後の部分を連結する、という操作を何度でも行うことができます。

すぬけ君が操作を何度か行ったあと、$ s $ の長さは最小でいくつになりえますか？

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^{5} $
- $ s $ は英小文字のみからなる長さ $ N $ の文字列

### Sample Explanation 1

\- `icefox` の末尾 `fox` を取り除くことで $ s $ を `ice` にすることができます。

### Sample Explanation 2

\- `fox` という部分文字列が存在しません。

## 样例 #1

### 输入

```
6

icefox```

### 输出

```
3```

## 样例 #2

### 输入

```
7

firebox```

### 输出

```
7```

## 样例 #3

### 输入

```
48

ffoxoxuvgjyzmehmopfohrupffoxoxfofofoxffoxoxejffo```

### 输出

```
27```

# AI分析结果

### 题目内容重写

#### [ARC108B] Abbreviate Fox

**题目描述**

给定一个长度为 $N$ 的仅由小写英文字母组成的字符串 $s$。你可以从 $s$ 中选择一个 `fox` 子串并将其删除，然后将删除后的前后部分连接起来。你可以多次进行此操作。

在进行若干次操作后，$s$ 的长度最小可以是多少？

**说明/提示**

**约束**

- $1 \leq N \leq 2 \times 10^{5}$
- $s$ 是一个长度为 $N$ 的仅由小写英文字母组成的字符串

**样例解释 1**

- 从 `icefox` 的末尾删除 `fox`，可以将 $s$ 变为 `ice`。

**样例解释 2**

- `fox` 子串不存在。

**样例 #1**

**输入**

```
6

icefox
```

**输出**

```
3
```

**样例 #2**

**输入**

```
7

firebox
```

**输出**

```
7
```

**样例 #3**

**输入**

```
48

ffoxoxuvgjyzmehmopfohrupffoxoxfofofoxffoxoxejffo
```

**输出**

```
27
```

### 算法分类

**字符串**

### 综合分析与结论

本题的核心问题是如何高效地删除字符串中的所有 `fox` 子串，使得最终字符串的长度最小。由于字符串的长度可能达到 $2 \times 10^5$，因此需要一个高效的算法来处理这个问题。

### 通用建议与扩展思路

1. **栈的使用**：可以利用栈来模拟删除 `fox` 子串的过程。遍历字符串时，将字符逐个压入栈中，每当栈顶的三个字符构成 `fox` 时，就将这三个字符弹出栈。这种方法的时间复杂度为 $O(N)$，非常高效。

2. **贪心思想**：每次遇到 `fox` 子串就立即删除，这样可以保证在每一步都尽可能地减少字符串的长度。这种贪心策略是合理的，因为删除 `fox` 子串不会影响其他可能的 `fox` 子串的删除。

3. **字符串匹配**：可以使用字符串匹配算法来查找所有的 `fox` 子串，然后逐个删除。不过这种方法的时间复杂度较高，不适用于大规模数据。

### 推荐题目

1. [P3375 【模板】KMP字符串匹配](https://www.luogu.com.cn/problem/P3375)
2. [P3805 【模板】Manacher算法](https://www.luogu.com.cn/problem/P3805)
3. [P3370 【模板】字符串哈希](https://www.luogu.com.cn/problem/P3370)

### 最优关键思路或技巧

**栈的使用**：通过栈来模拟删除 `fox` 子串的过程，既简单又高效。每次压入字符时检查栈顶的三个字符是否构成 `fox`，如果是则弹出这三个字符。这种方法的时间复杂度为 $O(N)$，非常适合处理大规模数据。

### 核心代码片段

```cpp
#include <iostream>
#include <stack>
#include <string>

using namespace std;

int main() {
    int N;
    string s;
    cin >> N >> s;

    stack<char> st;
    for (char c : s) {
        st.push(c);
        if (st.size() >= 3) {
            char z = st.top(); st.pop();
            char y = st.top(); st.pop();
            char x = st.top(); st.pop();
            if (x == 'f' && y == 'o' && z == 'x') {
                // 成功删除一个fox
            } else {
                st.push(x);
                st.push(y);
                st.push(z);
            }
        }
    }

    cout << st.size() << endl;
    return 0;
}
```

### 总结

本题的关键在于如何高效地删除字符串中的所有 `fox` 子串。使用栈来模拟删除过程是一种非常高效且简洁的方法，时间复杂度为 $O(N)$，适合处理大规模数据。这种方法不仅思路清晰，而且代码实现也非常简单，是解决此类问题的首选方案。

---
处理用时：25.10秒