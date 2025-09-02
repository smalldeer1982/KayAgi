# 题目信息

# Primal Sport

## 题目描述

Alice and Bob begin their day with a quick game. They first choose a starting number $ X_{0}>=3 $ and try to reach one million by the process described below.

Alice goes first and then they take alternating turns. In the $ i $ -th turn, the player whose turn it is selects a prime number smaller than the current number, and announces the smallest multiple of this prime number that is not smaller than the current number.

Formally, he or she selects a prime $ p&lt;X_{i-1} $ and then finds the minimum $ X_{i}>=X_{i-1} $ such that $ p $ divides $ X_{i} $ . Note that if the selected prime $ p $ already divides $ X_{i-1} $ , then the number does not change.

Eve has witnessed the state of the game after two turns. Given $ X_{2} $ , help her determine what is the smallest possible starting number $ X_{0} $ . Note that the players don't necessarily play optimally. You should consider all possible game evolutions.

## 说明/提示

In the first test, the smallest possible starting number is $ X_{0}=6 $ . One possible course of the game is as follows:

- Alice picks prime 5 and announces $ X_{1}=10 $
- Bob picks prime 7 and announces $ X_{2}=14 $ .

In the second case, let $ X_{0}=15 $ .

- Alice picks prime 2 and announces $ X_{1}=16 $
- Bob picks prime 5 and announces $ X_{2}=20 $ .

## 样例 #1

### 输入

```
14
```

### 输出

```
6
```

## 样例 #2

### 输入

```
20
```

### 输出

```
15
```

## 样例 #3

### 输入

```
8192
```

### 输出

```
8191
```

# AI分析结果

### 题目内容
# 原始游戏

## 题目描述
爱丽丝和鲍勃以一个快速游戏开启他们的一天。他们首先选择一个起始数字 $X_{0}\geq3$，并尝试通过以下描述的过程达到一百万。

爱丽丝先开始，然后他们轮流进行。在第 $i$ 轮，轮到的玩家选择一个小于当前数字的质数，并宣布这个质数的最小倍数，该倍数不小于当前数字。

正式地说，他或她选择一个质数 $p < X_{i - 1}$，然后找到最小的 $X_{i}\geq X_{i - 1}$，使得 $p$ 能整除 $X_{i}$。注意，如果所选的质数 $p$ 已经能整除 $X_{i - 1}$，那么数字不会改变。

伊芙目睹了游戏两轮后的状态。给定 $X_{2}$，帮助她确定最小可能的起始数字 $X_{0}$。注意，玩家不一定以最优方式进行游戏。你应该考虑所有可能的游戏演变。

## 说明/提示
在第一个测试中，最小可能的起始数字是 $X_{0}=6$。游戏的一种可能过程如下：
- 爱丽丝选择质数 5 并宣布 $X_{1}=10$
- 鲍勃选择质数 7 并宣布 $X_{2}=14$。

在第二种情况下，设 $X_{0}=15$。
- 爱丽丝选择质数 2 并宣布 $X_{1}=16$
- 鲍勃选择质数 5 并宣布 $X_{2}=20$。

## 样例 #1
### 输入
```
14
```
### 输出
```
6
```

## 样例 #2
### 输入
```
20
```
### 输出
```
15
```

## 样例 #3
### 输入
```
8192
```
### 输出
```
8191
```

### 综合分析与结论
所有题解的核心思路都是基于 $X_{i - 1}$ 与 $X_{i}$ 之间存在 $X_{i}-p + 1\leq X_{i - 1}\leq X_{i}$（$p$ 为 $X_{i}$ 的某个质因数）这一关系，通过枚举 $X_{1}$ 来求 $X_{0}$ 的最小值。不同点主要在于求数的最大质因数的方式和代码实现的细节。

1. **思路方面**：多数题解先通过线性筛法或其他方式预处理出每个数的最大质因数，然后利用 $X_{2}$ 的最大质因数确定 $X_{1}$ 的取值范围，在该范围内枚举 $X_{1}$ 并计算对应的 $X_{0}$ 的最小值。
2. **算法要点**：线性筛法是重要的算法基础，用于高效筛选质数并同时记录合数的最大质因数。另外，利用 $X_{i}$ 与 $X_{i - 1}$ 的关系进行枚举和计算是解题关键。
3. **解决难点**：难点在于理解和推导 $X_{i}$ 与 $X_{i - 1}$ 之间的关系，以及如何高效地获取每个数的最大质因数。

### 所选的题解
- **作者：Blunt_Feeling (赞：3)  星级：4星**
    - **关键亮点**：提供了一种较为简洁的找最大质因数的写法，通过遍历标记的方式预处理出每个数的最大质因数，代码简短。
    - **重点代码核心思想**：遍历 $2\sim X_2$，若一个数未被标记则为质数，用该质数标记其所有倍数并记录最大质因数。之后根据 $X_2$ 的最大质因数确定 $X_1$ 范围，枚举 $X_1$ 求 $X_0$ 最小值。
    ```cpp
    #include<bits/stdc++.h>
    #define For(i,a,b) for(register int i=(a);i<=(b);++i)
    #define Rep(i,a,b) for(register int i=(a);i>=(b);--i)
    using namespace std;
    int x2,x0,a[1000050];
    int main()
    {
        cin>>x2;
        For(i,2,x2)
            if(!a[i])
                for(int j=i*2;j<=x2;j+=i)
                    a[j]=i;
        x0=x2;
        For(i,x2-a[x2]+1,x2) x0=min(x0,i-a[i]+1);
        cout<<x0<<endl;
        return 0;
    }
    ```
- **作者：ModestCoder_ (赞：2)  星级：4星**
    - **关键亮点**：使用线性筛法同时完成判断质数和记录最大质因数，逻辑清晰，代码简洁明了。
    - **重点代码核心思想**：利用线性筛法标记合数并记录其最大质因数，之后根据 $X_2$ 的最大质因数确定 $X_1$ 范围，在范围内枚举 $X_1$ 求 $X_0$ 最小值。
    ```cpp
    #include <bits/stdc++.h>
    #define maxn 1000010
    using namespace std;
    int n, flag[maxn], tot, a[maxn], prime[maxn];

    int main(){
        scanf("%d", &n);
        flag[1] = 1;
        for (int i = 2; i <= n; ++i){
            if (!flag[i]) prime[++tot] = a[i] = i;
            for (int j = 1; j <= tot && i * prime[j] <= n; ++j){
                flag[i * prime[j]] = 1, a[i * prime[j]] = a[i];
                if (i % prime[j] == 0) break;
            }
        }
        int ans = n;
        for (int i = n - a[n] + 1; i <= n; ++i)
            if (flag[i]) ans = min(ans, i - a[i] + 1);
        printf("%d\n", ans);
        return 0;
    }
    ```
- **作者：Jasper08 (赞：0)  星级：4星**
    - **关键亮点**：详细地推导了 $X_{i}$ 与 $X_{i - 1}$ 的关系，逻辑严谨，代码实现围绕推导结论展开，清晰易懂。
    - **重点代码核心思想**：先找出 $X_2$ 的最大质因数 $p_2$，在 $[x_2 - p_2 + 1, x_2]$ 范围内枚举 $X_1$，对每个 $X_1$ 求其最大质因数 $p_1$，进而计算 $X_0$ 并取最小值，同时特判 $X_0 < 3$ 的情况。
    ```cpp
    #include <iostream>
    #include <cstdio>
    #include <cmath>
    #include <algorithm>
    #include <map>

    using namespace std;

    int main() {
        int x2;
        scanf("%d", &x2);

        int p2 = 1, t = x2; //找出x2的最大质因数,令其为p2 
        for (int i = 2; i <= t/i; ++i) { //分解x2的质因数
            while (t % i == 0)
                t /= i,	p2 = i;
        }
        if (t > 1)
            p2 = t;

        int ans = 1e9;
        for (int x1 = p2*(x2/p2-1)+1; x1 <= x2; ++x1) { //枚举x1 
            int t = x1, p1 = x1;
            for (int i = 2; i <= t/i; ++i) { //求x1的最大质因数p1
                while (t % i == 0)
                    t /= i, p1 = i;
            } 
            if (t > 1)
                p1 = t;
            int x0 = x1 - p1 + 1; //根据刚刚推出的公式计算x0的值
            ans = (x0 < 3)? ans : min(x0, ans); //特判x0<3的情况,此时不满足题目要求
        } 
        printf("%d\n", ans);
        return 0;
    }
    ```

### 最优关键思路或技巧
1. **利用线性筛法**：不仅可以高效筛选质数，还能在筛选过程中顺便记录每个合数的最大质因数，大大提高了算法效率。
2. **推导并利用数字间关系**：通过推导得出 $X_{i}-p + 1\leq X_{i - 1}\leq X_{i}$ 的关系，以此为基础进行枚举和计算，是解决本题的核心思路。

### 可拓展之处
同类型题通常围绕数论中的质数、倍数、因数等概念展开，类似算法套路包括利用数之间的大小、整除关系进行逆向推导，以及通过预处理一些数论函数（如质因数分解、最大公因数等）来优化计算过程。

### 洛谷相似题目推荐
1. **P1075 [NOIP2012 普及组] 质因数分解**：考察对质因数分解的理解和实现。
2. **P3383 【模板】线性筛素数**：强化对线性筛法的掌握。
3. **P2689 质数口袋**：结合质数判断和背包问题的思路，锻炼综合运用数论知识的能力。 

---
处理用时：35.45秒