# 题目信息

# Up the Strip (simplified version)

## 题目描述

This version of the problem differs from the next one only in the constraint on $ n $ .

Note that the memory limit in this problem is lower than in others.

You have a vertical strip with $ n $ cells, numbered consecutively from $ 1 $ to $ n $ from top to bottom.

You also have a token that is initially placed in cell $ n $ . You will move the token up until it arrives at cell $ 1 $ .

Let the token be in cell $ x > 1 $ at some moment. One shift of the token can have either of the following kinds:

- Subtraction: you choose an integer $ y $ between $ 1 $ and $ x-1 $ , inclusive, and move the token from cell $ x $ to cell $ x - y $ .
- Floored division: you choose an integer $ z $ between $ 2 $ and $ x $ , inclusive, and move the token from cell $ x $ to cell $ \lfloor \frac{x}{z} \rfloor $ ( $ x $ divided by $ z $ rounded down).

Find the number of ways to move the token from cell $ n $ to cell $ 1 $ using one or more shifts, and print it modulo $ m $ . Note that if there are several ways to move the token from one cell to another in one shift, all these ways are considered distinct (check example explanation for a better understanding).

## 说明/提示

In the first test, there are three ways to move the token from cell $ 3 $ to cell $ 1 $ in one shift: using subtraction of $ y = 2 $ , or using division by $ z = 2 $ or $ z = 3 $ .

There are also two ways to move the token from cell $ 3 $ to cell $ 1 $ via cell $ 2 $ : first subtract $ y = 1 $ , and then either subtract $ y = 1 $ again or divide by $ z = 2 $ .

Therefore, there are five ways in total.

## 样例 #1

### 输入

```
3 998244353```

### 输出

```
5```

## 样例 #2

### 输入

```
5 998244353```

### 输出

```
25```

## 样例 #3

### 输入

```
42 998244353```

### 输出

```
793019428```

# AI分析结果

### 题目中文重写
# 向上移动条带（简化版）

## 题目描述
这个版本的问题与下一个版本的区别仅在于对 $n$ 的限制。

请注意，本题的内存限制比其他题目更低。

你有一个垂直的条带，包含 $n$ 个单元格，从上到下依次编号为 $1$ 到 $n$。

你还有一个令牌，最初放置在单元格 $n$ 中。你将向上移动令牌，直到它到达单元格 $1$。

假设令牌在某个时刻位于单元格 $x > 1$。令牌的一次移动可以是以下两种类型之一：
- 减法：你选择一个介于 $1$ 到 $x - 1$（包含两端）之间的整数 $y$，并将令牌从单元格 $x$ 移动到单元格 $x - y$。
- 向下取整除法：你选择一个介于 $2$ 到 $x$（包含两端）之间的整数 $z$，并将令牌从单元格 $x$ 移动到单元格 $\lfloor \frac{x}{z} \rfloor$（$x$ 除以 $z$ 向下取整）。

找出使用一次或多次移动将令牌从单元格 $n$ 移动到单元格 $1$ 的方法数，并将结果对 $m$ 取模后输出。请注意，如果有多种方法在一次移动中将令牌从一个单元格移动到另一个单元格，则所有这些方法都被视为不同的方法（查看示例解释以更好地理解）。

## 说明/提示
在第一个测试用例中，有三种方法可以在一次移动中将令牌从单元格 $3$ 移动到单元格 $1$：使用减法 $y = 2$，或者使用除法 $z = 2$ 或 $z = 3$。

还有两种方法可以通过单元格 $2$ 将令牌从单元格 $3$ 移动到单元格 $1$：先减去 $y = 1$，然后再次减去 $y = 1$ 或除以 $z = 2$。

因此，总共有五种方法。

## 样例 #1
### 输入
```
3 998244353
```
### 输出
```
5
```

## 样例 #2
### 输入
```
5 998244353
```
### 输出
```
25
```

## 样例 #3
### 输入
```
42 998244353
```
### 输出
```
793019428
```

### 综合分析与结论
这些题解主要围绕动态规划（DP）解决从单元格 $n$ 移动到单元格 $1$ 的方案数问题，因数据范围不同有不同复杂度的解法：
- **思路**：大多设 $f_i$ 表示到 $i$ 的方案数，根据减法和除法两种操作推导转移方程。
- **算法要点**：
    - **简单版（$O(n\sqrt{n})$）**：利用整除分块优化除法操作的转移，用前缀和或后缀和优化减法操作的转移。
    - **正常版（$O(n\log n)$）**：改变转移方向，枚举除数 $z$ 结合后缀和优化。
- **解决难点**：主要是优化除法操作中 $\lfloor\frac{i}{z}\rfloor$ 的求和，通过整除分块将 $O(n)$ 复杂度优化到 $O(\sqrt{n})$；对于正常版，改变转移方向并利用调和级数性质将复杂度优化到 $O(n\log n)$。

### 所选题解
- **作者：henrytb（5星）**
    - **关键亮点**：思路清晰，分别给出简单版和正常版的解法，对复杂度分析详细，代码实现简洁。
    - **个人心得**：先想出简单版，再做出正常版，有思考过程。
- **作者：一只书虫仔（4星）**
    - **关键亮点**：思路阐述详细，对暴力 DP 及优化过程解释清晰，代码注释友好。
- **作者：dalao_see_me（4星）**
    - **关键亮点**：对整除分块的原理证明有提及，思路和代码都较清晰。

### 重点代码
#### henrytb 简单版
```cpp
#include <bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
int _,n,p;
int f[200005];
signed main() {
    scanf("%lld%lld",&n,&p);
    f[n]=1;
    rep(i,1,n-1) f[i]=0;
    int sum=1;
    int l=2,r;
    for(;l<=n;l=r+1) {
        r=n/(n/l);
        f[n/l]=(f[n/l]+(r-l+1)*f[n])%p;
    }
    per(i,n-1,1) {
        f[i]=(f[i]+sum)%p;
        l=2;
        for(;l<=i;l=r+1) {
            r=i/(i/l);
            f[i/l]=(f[i/l]+(r-l+1)*f[i])%p;
        }
        sum=(sum+f[i])%p;
    }
    printf("%lld\n",f[1]);
    return 0;
}
```
**核心思想**：设 $f_i$ 表示从 $n$ 走到 $i$ 的方案数，先处理 $n$ 的除法转移，再从 $n - 1$ 到 $1$ 倒序转移，利用整除分块优化除法转移，后缀和优化减法转移。

#### 一只书虫仔
```cpp
#include <bits/stdc++.h>
using namespace std;
long long n, m;
long long f[200015];
long long sf[200015];
int main () {
    scanf("%lld%lld", &n, &m);
    f[1] = 1;
    sf[1] = 1;
    for (long long i = 2; i <= n; i++) {
        f[i] += sf[i - 1];
        f[i] %= m;
        long long r;
        for (long long l = 2; l <= i; l = r + 1) {
            r = (i / (i / l));
            long long cnt = r - l + 1;
            long long tmp = f[i / l];
            tmp *= cnt;
            tmp %= m;
            f[i] += tmp;
            f[i] %= m;
        }
        sf[i] = sf[i - 1] + f[i];
        sf[i] %= m; 
    }
    printf("%lld", f[n] % m);
    return 0;
}
```
**核心思想**：设 $f_i$ 为有多少种方案使得 $i$ 变为 $1$，利用前缀和优化减法转移，整除分块优化除法转移。

#### dalao_see_me
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 5;
int f[N], s[N];//s为前缀和
int n, mod = 998244353;
inline int read() {
    int x = 0, f = 1; char c = getchar();
    while (c < '0' || c > '9') {if (c == '-') f = -f; c = getchar();}
    while (c >= '0' && c <= '9') {x = (x << 3) + (x << 1) + (c ^ 48); c = getchar();}
    return x * f;
}
signed main() {
    n = read();
    f[1] = 1; s[1] = 1;
    for (register int i = 2; i <= n; i++) {
        f[i] = s[i - 1];
        for (register int l = 2, r; l <= i; l = r + 1) {//整除分块
            r = i / (i / l);
            f[i] = (f[i] + f[i / l] * (r - l + 1) % mod) % mod;
        }
        s[i] = (s[i - 1] + f[i]) % mod;
    }
    printf("%lld", f[n]);
    return 0;
}
```
**核心思想**：设 $f_i$ 为从 $i$ 转移到 $1$ 的方案数，用前缀和优化减法操作，整除分块优化除法操作。

### 最优关键思路或技巧
- **整除分块**：对于 $\lfloor\frac{n}{i}\rfloor$ 只有 $O(\sqrt{n})$ 种取值，利用这个性质可以将枚举复杂度从 $O(n)$ 优化到 $O(\sqrt{n})$。
- **改变转移方向**：当正向转移复杂度高时，考虑反向转移，结合后缀和优化。

### 可拓展之处
同类型题或类似算法套路：涉及状态转移且存在大量重复计算的问题，可考虑 DP 优化，如涉及除法取整的求和问题可尝试整除分块优化。

### 推荐洛谷题目
- [P1880 石子合并](https://www.luogu.com.cn/problem/P1880)：区间 DP 问题，需要考虑状态转移和优化。
- [P1048 采药](https://www.luogu.com.cn/problem/P1048)：经典 0 - 1 背包问题，考察 DP 思想。
- [P1164 小A点菜](https://www.luogu.com.cn/problem/P1164)：简单的 DP 计数问题，可加深对 DP 转移的理解。

### 个人心得摘录总结
- **henrytb**：先解决简单版问题，再基于此思考正常版，逐步深入。
- **Cocoly1990**：赛时读错题意浪费时间，使用树状数组维护区间和增加复杂度，且没开 long long 及取模操作失误导致未通过，提醒能用前缀和维护就不用树状数组，模数大要开 long long 并注意取模操作。 

---
处理用时：61.46秒