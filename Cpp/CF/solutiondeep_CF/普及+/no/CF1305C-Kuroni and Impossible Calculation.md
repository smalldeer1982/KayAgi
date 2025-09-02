# 题目信息

# Kuroni and Impossible Calculation

## 题目描述

To become the king of Codeforces, Kuroni has to solve the following problem.

He is given $ n $ numbers $ a_1, a_2, \dots, a_n $ . Help Kuroni to calculate $ \prod_{1\le i<j\le n} |a_i - a_j| $ . As result can be very big, output it modulo $ m $ .

If you are not familiar with short notation, $ \prod_{1\le i<j\le n} |a_i - a_j| $ is equal to $ |a_1 - a_2|\cdot|a_1 - a_3|\cdot $ $ \dots $ $ \cdot|a_1 - a_n|\cdot|a_2 - a_3|\cdot|a_2 - a_4|\cdot $ $ \dots $ $ \cdot|a_2 - a_n| \cdot $ $ \dots $ $ \cdot |a_{n-1} - a_n| $ . In other words, this is the product of $ |a_i - a_j| $ for all $ 1\le i < j \le n $ .

## 说明/提示

In the first sample, $ |8 - 5| = 3 \equiv 3 \bmod 10 $ .

In the second sample, $ |1 - 4|\cdot|1 - 5|\cdot|4 - 5| = 3\cdot 4 \cdot 1 = 12 \equiv 0 \bmod 12 $ .

In the third sample, $ |1 - 4|\cdot|1 - 9|\cdot|4 - 9| = 3 \cdot 8 \cdot 5 = 120 \equiv 1 \bmod 7 $ .

## 样例 #1

### 输入

```
2 10
8 5```

### 输出

```
3```

## 样例 #2

### 输入

```
3 12
1 4 5```

### 输出

```
0```

## 样例 #3

### 输入

```
3 7
1 4 9```

### 输出

```
1```

# AI分析结果

### 题目内容（中文重写）
# Kuroni 和不可能的计算

## 题目描述
为了成为 Codeforces 的王者，Kuroni 必须解决以下问题。

他得到了 $n$ 个数 $a_1, a_2, \dots, a_n$。请帮助 Kuroni 计算 $\prod_{1\le i<j\le n} |a_i - a_j|$。由于结果可能非常大，将其对 $m$ 取模后输出。

如果你不熟悉这种简写符号，$\prod_{1\le i<j\le n} |a_i - a_j|$ 等于 $|a_1 - a_2|\cdot|a_1 - a_3|\cdot \dots \cdot|a_1 - a_n|\cdot|a_2 - a_3|\cdot|a_2 - a_4|\cdot \dots \cdot|a_2 - a_n| \cdot \dots \cdot |a_{n-1} - a_n|$。换句话说，这是所有满足 $1\le i < j \le n$ 的 $|a_i - a_j|$ 的乘积。

## 说明/提示
在第一个样例中，$|8 - 5| = 3 \equiv 3 \bmod 10$。

在第二个样例中，$|1 - 4|\cdot|1 - 5|\cdot|4 - 5| = 3\cdot 4 \cdot 1 = 12 \equiv 0 \bmod 12$。

在第三个样例中，$|1 - 4|\cdot|1 - 9|\cdot|4 - 9| = 3 \cdot 8 \cdot 5 = 120 \equiv 1 \bmod 7$。

## 样例 #1
### 输入
```
2 10
8 5
```
### 输出
```
3
```

## 样例 #2
### 输入
```
3 12
1 4 5
```
### 输出
```
0
```

## 样例 #3
### 输入
```
3 7
1 4 9
```
### 输出
```
1
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是利用数学中的鸽巢原理（抽屉原理）来优化计算。当 $n > m$ 时，根据鸽巢原理，必有两项 $a_i,a_j$ 模 $m$ 同余，此时 $\left\vert a_i - a_j\right\vert\bmod m = 0$，所以答案为 $0$；当 $n\leq m$ 时，由于 $m$ 较小，直接暴力枚举 $i$ 和 $j$ 计算乘积并取模即可。

### 所选题解
- 作者：皎月半洒花 (赞：8)，4星
  - 关键亮点：思路清晰，代码简洁，直接利用鸽巢原理进行特判，然后暴力计算，可读性高。
```cpp
int main(){
    cin >> n >> m ;
    for (int i = 1 ; i <= n ; ++ i)
        scanf("%lld", &base[i]) ;
    if (n > m) return puts("0"), 0 ;
    for (int i = 1 ; i <= n ; ++ i)
        for (int j = i + 1 ; j <= n ; ++ j)
            (ans *= (LL)abs(base[i] - base[j])) %= m ;
    cout << ans << endl ;
}
```
核心实现思想：先读取输入的 $n$ 和 $m$ 以及数组元素，判断 $n$ 是否大于 $m$，若大于则直接输出 $0$，否则通过两层循环枚举 $i$ 和 $j$，计算 $|a_i - a_j|$ 并累乘到结果中，同时取模。

- 作者：No21 (赞：3)，4星
  - 关键亮点：对鸽巢原理的证明详细，代码结构清晰，有命名空间，便于管理代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
namespace TO
{
    const int N=5021;
    int n,m;
    long long ans=1;
    int a[N];
    int mian()
    {
        cin>>n>>m;
        if(n>m)
        {
            cout<<0<<'\n';
            return 0;
        }
        for(int i=1;i<=n;i++)
            cin>>a[i];
        for(int i=1;i<n;i++)
        {
            for(int j=i+1;j<=n;j++)
                ans=abs(ans*(a[i]-a[j]))%m;
        }
        cout<<ans;
        return 0;
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    return TO::mian();
}
```
核心实现思想：在命名空间内实现主要逻辑，先读取输入，判断 $n$ 和 $m$ 的大小关系，若 $n > m$ 则输出 $0$，否则读取数组元素，通过两层循环计算乘积并取模。

- 作者：LB_tq (赞：2)，4星
  - 关键亮点：代码注释清晰，逻辑明确，按照 $n$ 和 $m$ 的大小关系进行分类处理。
```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#define ll long long
using namespace std;
const int maxn=2e5+10;
int n,m,a[maxn],s[maxn];
ll ans=1;
int main(){
    cin>>n>>m;
    if(n<=m){
        for(int i=1;i<=n;i++)
            cin>>a[i];
        for(int i=1;i<=n;i++)
            for(int j=i+1;j<=n;j++)
                ans=(ans*abs(a[j]-a[i])%m)%m;
        cout<<ans;
    }
    else
        cout<<"0";
    return 0;
}
```
核心实现思想：读取 $n$ 和 $m$，若 $n\leq m$，读取数组元素，通过两层循环计算乘积并取模后输出结果；若 $n > m$，直接输出 $0$。

### 最优关键思路或技巧
利用鸽巢原理对 $n$ 和 $m$ 的大小关系进行分类讨论，避免了不必要的计算，当 $n > m$ 时直接得出答案为 $0$，当 $n\leq m$ 时再进行暴力枚举。

### 拓展思路
同类型题或类似算法套路：在处理一些涉及取模和大量计算的问题时，可以先观察数据范围，尝试利用数学原理（如抽屉原理、余数性质等）进行优化，减少不必要的计算。

### 推荐洛谷题目
1. P1304 哥德巴赫猜想：涉及数学性质和枚举。
2. P1045 麦森数：涉及高精度计算和数学知识。
3. P2671 求和：涉及数学公式推导和计算。

### 个人心得摘录与总结
- 作者：gyh20 (赞：1)：一开始以为是 $O(m^2)$ 的做法，想不出来，只想到 $O(nm)$ 的做法，还不会卡常，浪费了两次机会。总结：在解题时要准确分析复杂度，并且可以学习一些卡常技巧。 

---
处理用时：47.92秒