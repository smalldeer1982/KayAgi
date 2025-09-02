# 题目信息

# Floor and Mod

## 题目描述

A pair of positive integers $ (a,b) $ is called special if $ \lfloor \frac{a}{b} \rfloor = a \bmod b $ . Here, $ \lfloor \frac{a}{b} \rfloor $ is the result of the integer division between $ a $ and $ b $ , while $ a \bmod b $ is its remainder.

You are given two integers $ x $ and $ y $ . Find the number of special pairs $ (a,b) $ such that $ 1\leq a \leq x $ and $ 1 \leq b \leq y $ .

## 说明/提示

In the first test case, the only special pair is $ (3, 2) $ .

In the second test case, there are no special pairs.

In the third test case, there are two special pairs: $ (3, 2) $ and $ (4, 3) $ .

## 样例 #1

### 输入

```
9
3 4
2 100
4 3
50 3
12 4
69 420
12345 6789
123456 789
12345678 9```

### 输出

```
1
0
2
3
5
141
53384
160909
36```

# AI分析结果

### 题目翻译
#### 题目描述
如果一对正整数 $(a, b)$ 满足 $\lfloor \frac{a}{b} \rfloor = a \bmod b$，则称这对数是特殊的。这里，$\lfloor \frac{a}{b} \rfloor$ 是 $a$ 除以 $b$ 的整数商，而 $a \bmod b$ 是其余数。

给定两个整数 $x$ 和 $y$，求满足 $1\leq a \leq x$ 且 $1 \leq b \leq y$ 的特殊数对 $(a, b)$ 的数量。

#### 说明/提示
在第一个测试用例中，唯一的特殊数对是 $(3, 2)$。

在第二个测试用例中，没有特殊数对。

在第三个测试用例中，有两个特殊数对：$(3, 2)$ 和 $(4, 3)$。

#### 样例 #1
##### 输入
```
9
3 4
2 100
4 3
50 3
12 4
69 420
12345 6789
123456 789
12345678 9
```

##### 输出
```
1
0
2
3
5
141
53384
160909
36
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是先对条件 $\lfloor \frac{a}{b} \rfloor = a \bmod b$ 进行数学推导，得到 $a$ 和 $b$ 的关系，再通过枚举、整除分块等方法来计算满足条件的数对 $(a, b)$ 的数量。

- **思路对比**：大部分题解是通过设 $\lfloor \frac{a}{b} \rfloor = a \bmod b = k$，得到 $a = k(b + 1)$，然后根据 $k < b$ 以及 $1\leq a \leq x$，$1 \leq b \leq y$ 这些条件来确定 $k$、$b$ 的取值范围进行计算。部分题解通过找规律、打表等方式得到解题思路。
- **算法要点**：主要算法要点包括数学推导、枚举、整除分块、二分查找等。其中整除分块是优化时间复杂度的关键，将时间复杂度从 $O(n)$ 优化到 $O(\sqrt{n})$。
- **解决难点**：难点在于对条件的数学推导，以及如何根据推导结果确定枚举范围和使用整除分块进行优化。

### 所选题解
- **作者：fanfansann (赞：13)，4星**
    - **关键亮点**：思路清晰，对数学推导过程和整除分块的使用解释详细，代码可读性高。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5 + 7;

int n, m, t;
int x, y;

int main()
{
    scanf("%d", &t);
    while(t -- ) {
        scanf("%d%d", &x, &y);
        int a = 1, b = 1;
        ll ans = 0;
        for(; b * b + b - 1 < x && b <= y; ++ b) 
            ans += (b * b + b - 1) / (b + 1);       

        int l = b + 1, r;  
        for(; l <= x && l <= y + 1; l = r + 1) {
            r = min(x / (x / l), y + 1);
            ans += x / l * (r - l + 1); 
            if(r == y + 1) break;
        } 
        cout << ans << endl;
    }        
    return 0;
}
```
    - **核心实现思想**：先通过数学推导得到 $b + 1\ |\ a$ 以及 $a < b^2 + b$，然后枚举 $b < \sqrt{x}$ 的情况，计算 $\frac { b^2 + b - 1}{b + 1}$，对于剩余的 $b$ 采用整除分块计算 $\lfloor \frac{x}{b + 1}\rfloor$。

- **作者：7KByte (赞：6)，4星**
    - **关键亮点**：思路简洁，直接枚举 $k = a \bmod b$ 来计算满足条件的数对数量，代码实现简单。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 100005
using namespace std;
void solve(){
    int a,b;scanf("%d%d",&a,&b);
    long long ans=0;
    rep(k,1,sqrt(a))ans+=max(0,min(b,(a-k)/k)-k);
    printf("%lld\n",ans);
}
int main(){
    int T;scanf("%d",&T);
    while(T--)solve();
    return 0;
}
```
    - **核心实现思想**：枚举 $k = a \bmod b$，根据 $a = kb + k$ 以及 $1\leq a \leq x$，$1 \leq b \leq y$ 确定 $b$ 的取值范围，计算满足条件的数对数量。

- **作者：WydnksqhbD (赞：2)，4星**
    - **关键亮点**：思路清晰，对数学推导过程解释详细，代码实现简洁。
    - **核心代码**：
```cpp
# include <bits/stdc++.h>
# define int long long
int max ( int a , int b ) { return a > b ? a : b ; }
int min ( int a , int b ) { return a < b ? a : b ; }
inline void solve ( )
{
    int x , y , ans = 0 ;
    std :: cin >> x >> y ;
    for ( int i = 1 ; i * i < x ; i ++ )
        ans += max ( 0 , min ( ( x - i ) / i , y ) - i ) ;
    std :: cout << ans << std :: endl ;
}
signed main ( )
{
    std :: ios :: sync_with_stdio ( 0 ) ;
    std :: cin . tie ( 0 ) ;
    std :: cout . tie ( 0 ) ;
    int t ;
    std :: cin >> t ;
    while ( t -- ) solve ( ) ;
    return 0 ;
}
```
    - **核心实现思想**：设 $\lfloor\frac{a}{b}\rfloor = a \bmod b = k$，得到 $a = kb + k$，根据 $b > k$ 以及 $1\leq a \leq x$，$1 \leq b \leq y$ 确定 $k$ 的取值范围，枚举 $k$ 计算满足条件的数对数量。

### 最优关键思路或技巧
- **数学推导**：通过对条件 $\lfloor \frac{a}{b} \rfloor = a \bmod b$ 进行数学推导，得到 $a$ 和 $b$ 的关系，如 $a = k(b + 1)$ 以及 $k < b$ 等，为后续计算提供依据。
- **整除分块**：在计算 $\sum_{b = 1}^{y} \lfloor \frac{x}{b + 1}\rfloor$ 时，使用整除分块可以将时间复杂度从 $O(n)$ 优化到 $O(\sqrt{n})$。

### 可拓展之处
同类型题目可能会有不同的条件限制，如改变 $a$ 和 $b$ 的取值范围，或者改变等式条件等。类似的算法套路包括先进行数学推导，然后根据推导结果进行枚举、分块等操作。

### 推荐题目
- [P1403 [AHOI2005]约数研究](https://www.luogu.com.cn/problem/P1403)
- [P2261 [CQOI2007]余数求和](https://www.luogu.com.cn/problem/P2261)
- [P3935 Calculating](https://www.luogu.com.cn/problem/P3935)

### 个人心得摘录与总结
- **xrk2006**：写完代码发现样例都过不了，意识到原答案没有考虑 $b$ 不能为 $1$ 以及 $k < b$ 这些条件，提醒我们在解题时要仔细考虑所有条件。

---
处理用时：62.39秒