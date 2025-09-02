# 题目信息

# [ABC251E] Takahashi and Animals

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc251/tasks/abc251_e

高橋君と $ N $ 匹の動物がいます。 $ N $ 匹の動物はそれぞれ動物 $ 1 $ 、動物 $ 2 $ 、$ \ldots $ 、動物 $ N $ と呼ばれます。

高橋君は下記の $ N $ 種類の行動をそれぞれ好きな回数だけ（ $ 0 $ 回でも良い）行います。

- $ A_1 $ 円払い、動物 $ 1 $ と動物 $ 2 $ に餌をあげる。
- $ A_2 $ 円払い、動物 $ 2 $ と動物 $ 3 $ に餌をあげる。
- $ A_3 $ 円払い、動物 $ 3 $ と動物 $ 4 $ に餌をあげる。
- $ \cdots $
- $ A_i $ 円払い、動物 $ i $ と動物 $ (i+1) $ に餌をあげる。
- $ \cdots $
- $ A_{N-2} $ 円払い、動物 $ (N-2) $ と動物 $ (N-1) $ に餌をあげる。
- $ A_{N-1} $ 円払い、動物 $ (N-1) $ と動物 $ N $ に餌をあげる。
- $ A_N $ 円払い、動物 $ N $ と動物 $ 1 $ に餌をあげる。

上記の $ N $ 種類目の行動では、「動物 $ N $ と動物 $ 1 $ に」餌をあげることに注意してください。

すべての動物にそれぞれ $ 1 $ 回以上餌をあげるまでにかかる費用の合計として考えられる最小値を出力してください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 3\ \times\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ 10^9 $
- 入力はすべて整数

### Sample Explanation 1

高橋君が $ 1 $ 種類目、$ 3 $ 種類目、$ 4 $ 種類目の行動をそれぞれ $ 1 $ 回ずつ行うと、 動物 $ 1 $ に $ 1 $ 回、動物 $ 2 $ に $ 1 $ 回、動物 $ 3 $ に $ 1 $ 回、動物 $ 4 $ に $ 2 $ 回、動物 $ 5 $ に $ 1 $ 回餌をあげることになり、すべての動物にそれぞれ $ 1 $ 回以上餌をあげることができます。 このときにかかる費用の合計は $ A_1\ +\ A_3\ +\ A_4\ =\ 2\ +\ 3\ +\ 2\ =\ 7 $ 円であり、これが考えられる最小値です。

## 样例 #1

### 输入

```
5

2 5 3 2 5```

### 输出

```
7```

## 样例 #2

### 输入

```
20

29 27 79 27 30 4 93 89 44 88 70 75 96 3 78 39 97 12 53 62```

### 输出

```
426```

# AI分析结果

### 题目内容重写

高橋君和 $N$ 只动物在一起。$N$ 只动物分别称为动物 $1$、动物 $2$、……、动物 $N$。

高橋君可以进行以下 $N$ 种操作，每种操作可以进行任意次数（包括 $0$ 次）：

- 花费 $A_1$ 元，给动物 $1$ 和动物 $2$ 喂食。
- 花费 $A_2$ 元，给动物 $2$ 和动物 $3$ 喂食。
- 花费 $A_3$ 元，给动物 $3$ 和动物 $4$ 喂食。
- ……
- 花费 $A_i$ 元，给动物 $i$ 和动物 $(i+1)$ 喂食。
- ……
- 花费 $A_{N-2}$ 元，给动物 $(N-2)$ 和动物 $(N-1)$ 喂食。
- 花费 $A_{N-1}$ 元，给动物 $(N-1)$ 和动物 $N$ 喂食。
- 花费 $A_N$ 元，给动物 $N$ 和动物 $1$ 喂食。

注意，第 $N$ 种操作是给动物 $N$ 和动物 $1$ 喂食。

要求所有动物都被喂食至少一次，求最小总花费。

### 题解分析与结论

本题的核心在于如何处理环形结构，即将问题转化为线性问题。大多数题解采用了动态规划（DP）的思路，通过分类讨论是否选择第一个操作来破环。以下是各题解的要点对比：

1. **slzx2022YuYihan** 和 **panhongxuanyyds** 的题解都采用了两次DP的思路，分别处理是否选择第一个操作的情况，最终取最小值。两者的思路相似，但代码实现略有不同。
2. **ZBH_123** 的题解也采用了类似的DP思路，但在状态转移和边界处理上更加简洁。
3. **灵茶山艾府** 的题解通过压缩状态变量，进一步优化了空间复杂度，代码更加简洁高效。
4. **_shine_** 和 **mi_Y13c** 的题解在状态定义和转移方程上与其他题解类似，但在边界处理和初始化上有所不同。
5. **xiaoPanda** 的题解通过分类讨论是否选择第一个操作，简化了状态转移方程，代码较为简洁。

### 最优关键思路与技巧

1. **破环为链**：通过分类讨论是否选择第一个操作，将环形问题转化为线性问题。
2. **状态压缩**：通过压缩DP状态变量，减少空间复杂度。
3. **边界处理**：通过初始化边界条件，确保DP的正确性。

### 推荐题目

1. [P1880 [NOI1995] 石子合并](https://www.luogu.com.cn/problem/P1880)
2. [P1063 能量项链](https://www.luogu.com.cn/problem/P1063)
3. [P1040 加分二叉树](https://www.luogu.com.cn/problem/P1040)

### 所选高分题解

#### 题解1：灵茶山艾府 (5星)
**关键亮点**：通过状态压缩优化了空间复杂度，代码简洁高效。
**核心代码**：
```go
func main() {
    in := bufio.NewReader(os.Stdin)
    var n int
    Fscan(in, &n)
    a := make([]int, n)
    for i := range a {
        Fscan(in, &a[i])
    }

    notPay, pay := int(1e18), a[0]
    for _, v := range a[1:] {
        notPay, pay = pay, min(notPay, pay)+v
    }
    ans := notPay

    notPay, pay = a[n-1], a[n-1]+a[0]
    for _, v := range a[1 : n-1] {
        notPay, pay = pay, min(notPay, pay)+v
    }
    Println(min(ans, min(notPay, pay)))
}
```

#### 题解2：ZBH_123 (4星)
**关键亮点**：状态转移和边界处理简洁明了，代码可读性强。
**核心代码**：
```cpp
#include<iostream>
using namespace std;
const int maxn=3e5;
int n,a[2*maxn+5];
long long dp[2*maxn+5][2],ans;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        a[i+n]=a[i];
    }
    dp[1][0]=0x3f3f3f3f,dp[1][1]=a[1];
    for(int i=2;i<=n;i++){
        dp[i][0]=dp[i-1][1];
        dp[i][1]=min(dp[i-1][0],dp[i-1][1])+a[i];
    }
    ans=min(dp[n][0],dp[n][1]);
    dp[n][0]=0x3f3f3f3f,dp[n][1]=a[n];
    for(int i=n+1;i<2*n;i++){
        dp[i][0]=dp[i-1][1];
        dp[i][1]=min(dp[i-1][0],dp[i-1][1])+a[i];
    }
    ans=min(ans,min(dp[2*n-1][0],dp[2*n-1][1]));
    cout<<ans;
    return 0;
}
```

#### 题解3：slzx2022YuYihan (4星)
**关键亮点**：详细解释了DP的状态转移和边界处理，代码清晰。
**核心代码**：
```cpp
#include<bits/stdc++.h>
#define IOS ios::sync_with_stdio(false);
#define int long long
#define space putchar(' ')
#define enter puts("")
using namespace std;
inline int read(){
    int s = 0, w = 0;char ch = getchar();
    while (!isdigit(ch))    w |= (ch == '-'), ch = getchar();
    while (isdigit(ch)) s = (s << 1) + (s << 3) + (ch & 15), ch = getchar();
    return w ? ~(s - 1) : s;
}
inline void write(int x){
    if (x < 0)  putchar('-'), x = ~(x - 1);
    if (x > 9)  write(x / 10);
    putchar(x % 10 ^ 48);
}
const int N = 3e5 + 5;
int n, a[N << 1], ans, ans1, ans2, dp[N << 1][2];
signed main(){
    n = read();
    for (int i = 1; i <= n; ++i)    a[i] = a[i + n] = read();
    memset(dp, 0x3f, sizeof(dp));
    dp[1][1] = a[1];
    for (int i = 2; i <= n; ++i)
        dp[i][0] = dp[i - 1][1], dp[i][1] = min(dp[i - 1][0], dp[i - 1][1]) + a[i];
    ans1 = min(dp[n][0], dp[n][1]);
    memset(dp, 0x3f, sizeof(dp));
    dp[n][1] = a[n];
    for (int i = n + 1; i <= (n << 1) - 1; ++i)
        dp[i][0] = dp[i - 1][1], dp[i][1] = min(dp[i - 1][0], dp[i - 1][1]) + a[i];
    ans2 = min(dp[(n << 1) - 1][0], dp[(n << 1) - 1][1]);
    ans = min(ans1, ans2);
    write(ans), enter;
    return 0;
}
```

### 个人心得摘录
- **slzx2022YuYihan**：详细解释了DP的状态转移和边界处理，适合初学者理解。
- **灵茶山艾府**：通过状态压缩优化了空间复杂度，代码简洁高效，适合进阶学习。

---
处理用时：73.18秒