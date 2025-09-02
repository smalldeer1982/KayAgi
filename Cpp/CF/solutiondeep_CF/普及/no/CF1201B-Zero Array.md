# 题目信息

# Zero Array

## 题目描述

You are given an array $ a_1, a_2, \ldots, a_n $ .

In one operation you can choose two elements $ a_i $ and $ a_j $ ( $ i \ne j $ ) and decrease each of them by one.

You need to check whether it is possible to make all the elements equal to zero or not.

## 说明/提示

In the first example, you can make all elements equal to zero in $ 3 $ operations:

- Decrease $ a_1 $ and $ a_2 $ ,
- Decrease $ a_3 $ and $ a_4 $ ,
- Decrease $ a_3 $ and $ a_4 $

In the second example, one can show that it is impossible to make all elements equal to zero.

## 样例 #1

### 输入

```
4
1 1 2 2
```

### 输出

```
YES```

## 样例 #2

### 输入

```
6
1 2 3 4 5 6
```

### 输出

```
NO```

# AI分析结果

### 题目内容重写

#### 题目描述

给定一个数组 $a_1, a_2, \ldots, a_n$。

每次操作可以选择两个元素 $a_i$ 和 $a_j$（$i \ne j$），并将它们各自减一。

你需要检查是否可以通过若干次操作将所有元素变为零。

#### 说明/提示

在第一个样例中，你可以通过 3 次操作将所有元素变为零：

- 减少 $a_1$ 和 $a_2$，
- 减少 $a_3$ 和 $a_4$，
- 再次减少 $a_3$ 和 $a_4$。

在第二个样例中，可以证明无法将所有元素变为零。

#### 样例 #1

##### 输入

```
4
1 1 2 2
```

##### 输出

```
YES
```

#### 样例 #2

##### 输入

```
6
1 2 3 4 5 6
```

##### 输出

```
NO
```

### 算法分类

数学

### 题解分析与结论

该题的核心在于判断是否可以通过每次操作将两个元素减一，最终将所有元素变为零。题解的关键思路集中在两个条件：

1. **数组元素的总和必须为偶数**：因为每次操作减少的总和为 2，所以总和必须为偶数才能最终变为零。
2. **数组中的最大元素不能超过其他元素的总和**：如果最大元素超过其他元素的总和，那么即使其他元素都减为零，最大元素仍然无法减为零。

所有题解都围绕这两个条件展开，并通过简单的数学证明来验证其正确性。代码实现上，大多数题解都采用了遍历数组计算总和和最大值的思路，最后根据上述两个条件进行判断。

### 评分较高的题解

#### 题解作者：Mysterious_Mini (5星)

**关键亮点**：
- 思路清晰，明确提出了两个关键条件，并给出了详细的数学证明。
- 代码简洁，直接计算数组的总和和最大值，并根据条件进行判断。
- 提醒了开 `long long` 的注意事项，避免了潜在的溢出问题。

**代码核心思想**：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
long long n, a, sum, maxa;
int main()
{
    scanf("%lld", &n);
    for(long long i = 1; i <= n; i++)
    {
        scanf("%lld", &a);
        sum += a;
        maxa = max(maxa, a);
    }
    if(sum % 2 == 1 || sum < 2 * maxa) printf("NO");
    else printf("YES");
    return 0;
}
```

#### 题解作者：Mubuky (4星)

**关键亮点**：
- 通过实际例子解释了为什么最大元素不能超过其他元素的总和。
- 提供了详细的思考过程，包括错误的尝试和最终的解决方案。
- 代码结构清晰，虽然有一些冗余，但整体思路明确。

**代码核心思想**：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n, m, a, s;
int main()
{
    ios_base::sync_with_stdio(false);
    cin>>n;
    for (ll i=1; i<=n; i++)
    {
        cin>>a;
        s+=a;
        m=max(m, a);
    }
    if (s%2==1 || s<2*m)
    {
        cout<<"NO";
        return 0;
    }
    cout<<"YES";
    return 0;
}
```

#### 题解作者：Zechariah (4星)

**关键亮点**：
- 简洁明了，直接给出了两个关键条件，并进行了简单的证明。
- 代码实现简洁，使用了快速输入输出优化，提高了效率。

**代码核心思想**：
```cpp
#include <bits/stdc++.h>
#define lowbit(x) (x & -x)
#define jh(x, y) x ^= y ^= x ^= y
#define loc(x, y) (x - 1) * m + y
#define rg register
#define inl inline
#define PI 3.141592654
typedef long long ll;
const int N = 2e5 + 5, INF = 0x3f3f3f3f, mod = 998244353;
using namespace std;
namespace fast_IO {
    inl ll read() {
        rg char c;
        rg ll x = 0;
        rg bool flag = false;
        while ((c = getchar()) == ' ' || c == '\n' || c == '\r');
        if (c == EOF)return c; if (c == '-')flag = true; else x = c ^ 48;
        while ((c = getchar()) != ' ' && c != '\n' && c != '\r' && ~c)
            x = (x << 1) + (x << 3) + (c ^ 48);
        if (flag)return -x; return x;
    }
    inl ll max(rg ll a, rg ll b) { if (a > b)return a; return b; }
    inl ll min(rg ll a, rg ll b) { if (a < b)return a; return b; }
    void write(rg ll x) { if (x < 0)putchar('-'), x = -x; if (x >= 10)write(x / 10); putchar(x % 10 ^ 48); }
}
ll a[N], sum;

int main() {
    rg int n = fast_IO::read();
    for (rg int i = 1; i <= n; ++i)sum += (a[i] = fast_IO::read());
    sort(a + 1, a + n + 1);
    if ((sum & 1) || (a[n] << 1) > sum)puts("NO");
    else puts("YES");
    return 0;
}
```

### 最优关键思路与技巧

1. **总和为偶数**：每次操作减少的总和为 2，因此总和必须为偶数才能最终变为零。
2. **最大元素不超过其他元素的总和**：如果最大元素超过其他元素的总和，那么即使其他元素都减为零，最大元素仍然无法减为零。

### 可拓展之处

类似的问题可以通过分析每次操作对总和的影响来判断是否能够达到目标。例如，某些问题可能要求通过每次操作将三个元素减一，或者通过其他方式改变数组元素的值。

### 推荐题目

1. [P1008 三连击](https://www.luogu.com.cn/problem/P1008)
2. [P1012 拼数](https://www.luogu.com.cn/problem/P1012)
3. [P1019 单词接龙](https://www.luogu.com.cn/problem/P1019)

### 个人心得总结

在解决这类问题时，关键在于通过数学分析找到问题的核心条件，并通过简单的代码实现来验证这些条件。大多数题解都通过遍历数组计算总和和最大值，并根据条件进行判断，这种思路简洁且高效。

---
处理用时：51.16秒