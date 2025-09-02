# 题目信息

# Buying Shovels

## 题目描述

Polycarp wants to buy exactly $ n $ shovels. The shop sells packages with shovels. The store has $ k $ types of packages: the package of the $ i $ -th type consists of exactly $ i $ shovels ( $ 1 \le i \le k $ ). The store has an infinite number of packages of each type.

Polycarp wants to choose one type of packages and then buy several (one or more) packages of this type. What is the smallest number of packages Polycarp will have to buy to get exactly $ n $ shovels?

For example, if $ n=8 $ and $ k=7 $ , then Polycarp will buy $ 2 $ packages of $ 4 $ shovels.

Help Polycarp find the minimum number of packages that he needs to buy, given that he:

- will buy exactly $ n $ shovels in total;
- the sizes of all packages he will buy are all the same and the number of shovels in each package is an integer from $ 1 $ to $ k $ , inclusive.

## 说明/提示

The answer to the first test case was explained in the statement.

In the second test case, there is only one way to buy $ 8 $ shovels — $ 8 $ packages of one shovel.

In the third test case, you need to buy a $ 1 $ package of $ 6 $ shovels.

## 样例 #1

### 输入

```
5
8 7
8 1
6 10
999999733 999999732
999999733 999999733```

### 输出

```
2
8
1
999999733
1```

# AI分析结果

### 题目中文重写
# 购买铲子

## 题目描述
波利卡普想买恰好 $n$ 把铲子。商店出售装铲子的包裹。商店有 $k$ 种包裹：第 $i$ 种包裹恰好装有 $i$ 把铲子（$1 \leq i \leq k$）。商店每种类型的包裹都有无限个。

波利卡普想选择一种类型的包裹，然后购买这种类型的若干（一个或多个）包裹。波利卡普要恰好买到 $n$ 把铲子，最少需要购买多少个包裹呢？

例如，如果 $n = 8$ 且 $k = 7$，那么波利卡普会买 2 包 4 把铲子的包裹。

帮助波利卡普找出他需要购买的最少包裹数，已知条件如下：
- 他总共要买恰好 $n$ 把铲子；
- 他购买的所有包裹的大小都相同，且每个包裹中的铲子数量是一个从 1 到 $k$（包含 1 和 $k$）的整数。

## 说明/提示
第一个测试用例的答案在题目描述中已经解释过了。

在第二个测试用例中，只有一种方法可以买到 8 把铲子——买 8 包 1 把铲子的包裹。

在第三个测试用例中，你需要买 1 包 6 把铲子的包裹。

## 样例 #1
### 输入
```
5
8 7
8 1
6 10
999999733 999999732
999999733 999999733
```

### 输出
```
2
8
1
999999733
1
```

### 综合分析与结论
这些题解的核心思路都是找出 $1$ 到 $k$ 之间 $n$ 的最大因数，然后用 $n$ 除以这个因数得到最少购买包裹数。由于数据范围较大，直接枚举 $1$ 到 $k$ 会超时，因此各题解都采用了枚举 $1$ 到 $\sqrt{n}$ 的优化方法，利用因数成对出现的特性，同时判断 $i$ 和 $n/i$ 是否在 $1$ 到 $k$ 的范围内，从而找到符合条件的最大因数。

### 所选题解
- **作者：丧黑福造（5星）**
    - **关键亮点**：思路清晰，代码简洁，使用 `inline` 函数定义 `min` 提高效率，注释详细，对算法核心部分解释清晰。
    - **核心代码**：
```cpp
#include <stdio.h>
inline int min (int x, int y) {
    return x < y? x : y;
}
main() {
    int t;
    scanf ("%d", &t);
    while (t --) {
        int ans = 0x7fffffff;
        int n, k;
        scanf ("%d %d", &n, &k);
        for (register int i = 1; i * i <= n; i ++) {
            if (n % i == 0) {
                if (i <= k)
                    ans = min (ans, n/i);
                if (n/i <= k)
                    ans = min (ans, i);
            }
        }
        printf ("%d\n", ans);
    }
    return 0;
}
```
- **作者：andyli（4星）**
    - **关键亮点**：提供了两种不同的实现方式，一种直接在枚举时更新最大因数，另一种使用 `std::upper_bound` 查找不超过 $k$ 的最大因数，体现了多种解题思路。
    - **核心代码（第一种）**：
```cpp
int main() {
    int q;
    io.read(q);
    while (q--) {
        int n, k;
        io.read(n, k);
        int ans = 0;
        for (int i = 1; i * i <= n; i++)
            if (n % i == 0)
                chkmax(ans, i <= k? i : 0, n / i <= k? n / i : 0);
        writeln(n / ans);
    }
    return 0;
}
```
- **作者：__HHX__（4星）**
    - **关键亮点**：对思路推导过程进行了详细解释，从质数筛的角度引入，逐步分析出枚举到 $\sqrt{n}$ 的优化方法，有助于理解算法原理。
    - **核心代码**：
```cpp
#include<iostream>
using namespace std;
int main(){
    int t;
    cin>>t;
    while(t--)
    {
        int n,k,maxx;
        cin>>n>>k;
        maxx=-1;
        for(int i=1;i*i<=n&&i<=k;i++)
        {
            if(n%i==0)
            {
                maxx=(n/i<=k?max(maxx,n/i):max(maxx,i));
            }
        }
        cout<<n/maxx<<endl;
    }
} 
```

### 最优关键思路或技巧
- **因数成对特性**：利用一个数的因数成对出现的性质，只需要枚举 $1$ 到 $\sqrt{n}$，就可以同时判断 $i$ 和 $n/i$ 是否为符合条件的因数，将时间复杂度从 $O(k)$ 优化到 $O(\sqrt{n})$。
- **边界判断**：在枚举过程中，同时判断 $i$ 和 $n/i$ 是否在 $1$ 到 $k$ 的范围内，避免了不必要的计算。

### 可拓展之处
同类型题目可能会增加更多的限制条件，如每种包裹有不同的价格，要求在满足购买数量的前提下，花费最少；或者有多种购买方式可供选择，需要找出最优方案。类似的算法套路仍然是先分析问题的数学本质，找到关键的约束条件，然后通过枚举、二分查找等方法进行优化求解。

### 推荐洛谷题目
- [P1029 最大公约数和最小公倍数问题](https://www.luogu.com.cn/problem/P1029)：考察因数、最大公约数和最小公倍数的相关知识。
- [P1072 Hankson的趣味题](https://www.luogu.com.cn/problem/P1072)：涉及因数分解和数论相关的计算。
- [P1306 斐波那契公约数](https://www.luogu.com.cn/problem/P1306)：结合斐波那契数列和最大公约数的求解。

### 个人心得摘录与总结
部分题解提到要注意数据范围，避免使用暴力枚举导致超时，需要通过分析问题的数学性质，找到更优的算法。如 Pink_Cut_Tree 的题解指出暴力枚举 $1$ 到 $n$ 会 TLE，应枚举到 $\sqrt{n}$ 进行优化。这提醒我们在解题时要充分考虑数据规模，选择合适的算法。 

---
处理用时：34.47秒