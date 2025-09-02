# 题目信息

# Non-coprime Split

## 题目描述

You are given two integers $ l \le r $ . You need to find positive integers $ a $ and $ b $ such that the following conditions are simultaneously satisfied:

- $ l \le a + b \le r $
- $ \gcd(a, b) \neq 1 $

or report that they do not exist.

 $ \gcd(a, b) $ denotes the [greatest common divisor](https://en.wikipedia.org/wiki/Greatest_common_divisor) of numbers $ a $ and $ b $ . For example, $ \gcd(6, 9) = 3 $ , $ \gcd(8, 9) = 1 $ , $ \gcd(4, 2) = 2 $ .

## 说明/提示

In the first test case, $ 11 \le 6 + 9 \le 15 $ , $ \gcd(6, 9) = 3 $ , and all conditions are satisfied. Note that this is not the only possible answer, for example, $ \{4, 10\}, \{5, 10\}, \{6, 6\} $ are also valid answers for this test case.

In the second test case, the only pairs $ \{a, b\} $ that satisfy the condition $ 1 \le a + b \le 3 $ are $ \{1, 1\}, \{1, 2\}, \{2, 1\} $ , but in each of these pairs $ \gcd(a, b) $ equals $ 1 $ , so there is no answer.

In the third sample test, $ \gcd(14, 4) = 2 $ .

## 样例 #1

### 输入

```
11
11 15
1 3
18 19
41 43
777 777
8000000 10000000
2000 2023
1791791 1791791
1 4
2 3
9840769 9840769```

### 输出

```
6 9
-1
14 4
36 6
111 666
4000000 5000000 
2009 7
-1
2 2
-1
6274 9834495```

# AI分析结果

### 题目翻译
# 非互质拆分

## 题目描述
给定两个整数 $l \le r$。你需要找到正整数 $a$ 和 $b$，使得以下条件同时满足：
- $l \le a + b \le r$
- $\gcd(a, b) \neq 1$

或者报告不存在这样的 $a$ 和 $b$。

$\gcd(a, b)$ 表示数字 $a$ 和 $b$ 的[最大公约数](https://en.wikipedia.org/wiki/Greatest_common_divisor)。例如，$\gcd(6, 9) = 3$，$\gcd(8, 9) = 1$，$\gcd(4, 2) = 2$。

## 说明/提示
在第一个测试用例中，$11 \le 6 + 9 \le 15$，$\gcd(6, 9) = 3$，所有条件都满足。注意，这不是唯一可能的答案，例如，$\{4, 10\}$、$\{5, 10\}$、$\{6, 6\}$ 也是该测试用例的有效答案。

在第二个测试用例中，满足条件 $1 \le a + b \le 3$ 的唯一数对 $\{a, b\}$ 是 $\{1, 1\}$、$\{1, 2\}$、$\{2, 1\}$，但在这些数对中，$\gcd(a, b)$ 都等于 $1$，所以没有答案。

在第三个示例测试中，$\gcd(14, 4) = 2$。

## 样例 #1
### 输入
```
11
11 15
1 3
18 19
41 43
777 777
8000000 10000000
2000 2023
1791791 1791791
1 4
2 3
9840769 9840769
```

### 输出
```
6 9
-1
14 4
36 6
111 666
4000000 5000000 
2009 7
-1
2 2
-1
6274 9834495
```

### 算法分类
构造

### 综合分析与结论
这些题解的核心目标都是在给定区间 $[l, r]$ 内找到满足 $l \le a + b \le r$ 且 $\gcd(a, b) \neq 1$ 的正整数 $a$ 和 $b$，若不存在则输出 `-1`。各题解的思路和实现方式有所不同：
- **枚举区间内的和**：遍历 $[l, r]$ 内的每个数 $sum$，找到其最小非 $1$ 因子 $p$，输出 $p$ 和 $sum - p$，若为质数则跳过。
- **利用合数性质**：提前预处理最小质因子，找到第一个合数并拆分为满足条件的 $a$ 和 $b$。
- **分情况讨论**：根据 $l$ 和 $r$ 的关系（相等或不相等），结合奇偶性和质数判断来构造 $a$ 和 $b$。

### 所选题解
- **作者：_Mikasa (赞：7)，4星**
    - **关键亮点**：思路简洁直接，代码实现简单易懂，通过遍历区间内的和并找最小因子来构造答案。
    - **核心代码**：
```cpp
int minp(int x)
{
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) return i;
    }
    return 0;
}
 
void solve()
{
    int l, r;
    cin >> l >> r;
    for (int i = l; i <= r; i++) {
        int p = minp(i);
        if (p == 0) continue;
        else {
            cout << p << ' ' << i - p << '\n';
            return;
        }
    }
    cout << "-1\n";
}
```
核心实现思想：`minp` 函数用于找到一个数的最小非 $1$ 因子，`solve` 函数遍历区间 $[l, r]$，对每个数调用 `minp` 函数，若找到因子则输出该因子和剩余部分，若都为质数则输出 `-1`。

- **作者：One_JuRuo (赞：4)，4星**
    - **关键亮点**：提前线性筛预处理最小质因子，减少重复计算，提高效率。
    - **核心代码**：
```cpp
inline void init()
{
    for(int i=2;i<=10000000;++i)
    {
        if(!su[i]) pri[++cnt]=i,minp[i]=i;
        for(int j=1;j<=cnt&&i*pri[j]<=10000000;++j)
        {
            su[i*pri[j]]=1,minp[i*pri[j]]=pri[j];
            if(i%pri[j]==0) break;
        }
    }
}
int main()
{
    init();
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m),flag=0;
        for(int i=max(2,n);i<=m;++i) if(i/minp[i]>1){flag=1,printf("%d %d\n",minp[i],i-minp[i]);break;}
        if(!flag) printf("-1\n");
    }
}
```
核心实现思想：`init` 函数通过线性筛预处理每个数的最小质因子，`main` 函数遍历区间 $[n, m]$，找到第一个满足条件的合数并拆分为最小质因子和剩余部分输出，若不存在则输出 `-1`。

- **作者：jr_inf (赞：0)，4星**
    - **关键亮点**：分情况讨论，利用偶数和质数的性质构造答案，思路清晰。
    - **核心代码**：
```cpp
signed main()
{
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&l,&r);
        if(l!=r)
        {
            int cnt=r-r%2;
            if(cnt==2)puts("-1");
            else printf("%d %d\n",2,cnt-2);
        }
        else
        {
            bool f=0;
            for(int i=2;i*i<=l;i++)
            {
                if(l%i)continue;
                f=1;
                printf("%d %d\n",i,l-i);
                break;
            }
            if(!f)puts("-1");
        }
    }
}
```
核心实现思想：当 $l \neq r$ 时，找到区间内最大偶数，若大于 $2$ 则输出 $2$ 和该偶数减 $2$；当 $l = r$ 时，枚举 $l$ 的因子，若找到则输出该因子和 $l$ 减该因子，若都为质数则输出 `-1`。

### 最优关键思路或技巧
- **利用合数性质**：合数一定可以拆分为满足条件的 $a$ 和 $b$，可以通过找最小质因子或利用偶数性质来构造。
- **分情况讨论**：根据 $l$ 和 $r$ 的关系（相等或不相等）以及奇偶性进行分类讨论，简化问题。

### 拓展思路
同类型题可能会改变条件，如要求 $\gcd(a, b) = k$（$k$ 为给定值），或者限制 $a$ 和 $b$ 的其他条件。类似算法套路可以是根据问题的性质进行分类讨论，利用数学性质（如质数、合数、奇偶性等）来构造答案。

### 推荐洛谷题目
- P1072 [HNOI2001] 最大公约数和最小公倍数问题
- P1306 斐波那契公约数
- P2152 [SDOI2009] SuperGCD

### 个人心得
题解中未包含个人心得。

---
处理用时：46.76秒