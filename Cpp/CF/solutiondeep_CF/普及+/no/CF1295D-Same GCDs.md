# 题目信息

# Same GCDs

## 题目描述

You are given two integers $ a $ and $ m $ . Calculate the number of integers $ x $ such that $ 0 \le x < m $ and $ \gcd(a, m) = \gcd(a + x, m) $ .

Note: $ \gcd(a, b) $ is the greatest common divisor of $ a $ and $ b $ .

## 说明/提示

In the first test case appropriate $ x $ -s are $ [0, 1, 3, 4, 6, 7] $ .

In the second test case the only appropriate $ x $ is $ 0 $ .

## 样例 #1

### 输入

```
3
4 9
5 10
42 9999999967```

### 输出

```
6
1
9999999966```

# AI分析结果

### 题目翻译
## 相同的最大公约数

### 题目描述
给定两个整数 $a$ 和 $m$，计算满足 $0 \le x < m$ 且 $\gcd(a, m) = \gcd(a + x, m)$ 的整数 $x$ 的数量。

注意：$\gcd(a, b)$ 表示 $a$ 和 $b$ 的最大公约数。

### 说明/提示
在第一个测试用例中，合适的 $x$ 为 $[0, 1, 3, 4, 6, 7]$。
在第二个测试用例中，唯一合适的 $x$ 是 $0$。

### 样例 #1
#### 输入
```
3
4 9
5 10
42 9999999967
```
#### 输出
```
6
1
9999999966
```

### 算法分类
数学

### 综合分析与结论
这些题解主要围绕计算满足 $\gcd(a, m) = \gcd(a + x, m)$ 且 $0 \le x < m$ 的 $x$ 的数量展开。多数题解先通过辗转相除法对原式进行转化，设 $d = \gcd(a, m)$，将问题转化为求与 $\frac{m}{d}$ 互质的数的个数，即求 $\varphi(\frac{m}{d})$，其中 $\varphi$ 为欧拉函数。部分题解还提供了莫比乌斯反演、容斥原理等方法。

### 所选题解
- **樱雪喵（4星）**
    - **关键亮点**：思路清晰，先介绍前置知识，再逐步推导，将问题转化为求欧拉函数值，代码实现简洁明了。
    - **代码**：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T,a,m;
signed main()
{
    scanf("%lld",&T);
    while(T--)
    {
        scanf("%lld%lld",&a,&m);
        int n=m/__gcd(a,m);
        int ans=n;
        for(int i=2;i*i<=n;i++)
        {
            if(n%i==0) ans=ans/i*(i-1);
            while(n%i==0) n/=i;
        }
        if(n>1) ans=ans/n*(n-1);
        cout<<ans<<endl;
    }
    return 0;
}
```
    - **核心实现思想**：先计算出 $\frac{m}{\gcd(a, m)}$，然后使用欧拉函数的定义，对其进行质因数分解，通过不断更新结果得到与 $\frac{m}{\gcd(a, m)}$ 互质的数的个数。

- **SDqwq（4星）**
    - **关键亮点**：步骤详细，从题意出发，逐步推导得出答案为 $\phi(\frac{m}{\gcd(a, m)})$，并给出了时间复杂度分析，代码结构清晰。
    - **代码**：
```cpp
#include <cstdio>
#include <iostream>

using namespace std;

typedef long long ll;
ll gcd (ll x, ll y) {return y == 0 ? x : gcd(y, x % y);}

ll phi (ll n) {
    ll ans = n;
    for (ll i = 2; i * i <= n; i++)
        if (n % i == 0) {
            ans = ans / i * (i - 1);
            while (n % i == 0)
                n /= i;
        }
    if (n > 1)
        ans = ans / n * (n - 1);
    return ans;
}

int main () {
    int T;
    scanf("%d", &T);
    while (T--) {
        ll a, m;
        scanf("%lld %lld", &a, &m);
        printf("%lld\n", phi(m / gcd(a, m)));
    }
    return 0;
}
```
    - **核心实现思想**：定义了求最大公约数和欧拉函数的函数，在主函数中，先读取输入，计算出 $\frac{m}{\gcd(a, m)}$，再调用欧拉函数计算结果。

- **tuzhewen（4星）**
    - **关键亮点**：对第一篇题解进行补充，思路明确，直接指出可以用欧拉函数求解，代码简洁易懂。
    - **代码**：
```cpp
#include<bits/stdc++.h>
#define F(i,l,r) for(register int i=l;i<=r;i++)
#define D(i,r,l) for(register int i=r;i>=l;i--)
#define ll long long
#define mem(a,b) memset(a,b,sizeof(a))
#define p_b push_back
#define m_p make_pair
#define il inline
const int INF=0x3f3f3f3f;
using namespace std;
ll a,m;
int T;
ll phi(ll x) {
    ll ans=x;
    F(i,2,sqrt(x)) {
        if(x%i==0) {
            ans=ans/i*(i-1);
            while(x%i==0) x/=i;
        }
    }
    if(x>1) ans=ans/x*(x-1);
    return ans;
}
int main() {
    scanf("%d",&T);
    while(T--) {
        scanf("%lld%lld",&a,&m);
        printf("%lld\n",phi(m/(__gcd(a,m))));
    }
    return 0;
}
```
    - **核心实现思想**：定义欧拉函数，在主函数中读取输入，计算 $\frac{m}{\gcd(a, m)}$ 后调用欧拉函数得到结果。

### 最优关键思路或技巧
- **数学转化**：利用辗转相除法将 $\gcd(a + x, m)$ 转化为 $\gcd((a + x) \bmod m, m)$，进而将问题转化为求与 $\frac{m}{\gcd(a, m)}$ 互质的数的个数。
- **欧拉函数**：通过欧拉函数 $\varphi(n)=n\prod_{i = 1}^{k}(1 - \frac{1}{p_i})$ （其中 $p_i$ 为 $n$ 的质因数）计算与 $n$ 互质的数的个数，时间复杂度为 $O(\sqrt{n})$。

### 拓展思路
同类型题目通常会涉及数论相关知识，如最大公约数、欧拉函数、莫比乌斯反演等。解题时可以先对题目进行数学转化，将问题转化为已知的数学模型，再利用相应的算法进行求解。

### 推荐题目
- [P2158 [SDOI2008] 仪仗队](https://www.luogu.com.cn/problem/P2158)：涉及欧拉函数的应用。
- [P2303 [SDOI2012] Longge 的问题](https://www.luogu.com.cn/problem/P2303)：需要运用数论知识和欧拉函数求解。
- [P3455 [POI2007] ZAP-Queries](https://www.luogu.com.cn/problem/P3455)：可以使用莫比乌斯反演解决。

### 个人心得
部分题解作者提到在比赛时可能会遇到无法证明某些结论的情况，如 Sweetlemon 提到赛时一度猜想答案是 $\varphi(m)$ 但无法证明，这提醒我们在比赛中可以先尝试其他可行的方法，赛后再深入探究。同时，对于数论题，要熟练掌握相关的数学知识和算法，多做练习，提高解题能力。

---
处理用时：54.54秒