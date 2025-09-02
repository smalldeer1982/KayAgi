# 题目信息

# K-good

## 题目描述

We say that a positive integer $ n $ is $ k $ -good for some positive integer $ k $ if $ n $ can be expressed as a sum of $ k $ positive integers which give $ k $ distinct remainders when divided by $ k $ .

Given a positive integer $ n $ , find some $ k \geq 2 $ so that $ n $ is $ k $ -good or tell that such a $ k $ does not exist.

## 说明/提示

$ 6 $ is a $ 3 $ -good number since it can be expressed as a sum of $ 3 $ numbers which give different remainders when divided by $ 3 $ : $ 6 = 1 + 2 + 3 $ .

 $ 15 $ is also a $ 3 $ -good number since $ 15 = 1 + 5 + 9 $ and $ 1, 5, 9 $ give different remainders when divided by $ 3 $ .

 $ 20 $ is a $ 5 $ -good number since $ 20 = 2 + 3 + 4 + 5 + 6 $ and $ 2,3,4,5,6 $ give different remainders when divided by $ 5 $ .

## 样例 #1

### 输入

```
5
2
4
6
15
20```

### 输出

```
-1
-1
3
3
5```

# AI分析结果

### 题目中文重写
# K - 好数

## 题目描述
我们称一个正整数 $n$ 对于某个正整数 $k$ 是 $k$ - 好数，如果 $n$ 可以表示为 $k$ 个正整数的和，且这 $k$ 个正整数除以 $k$ 得到 $k$ 个不同的余数。

给定一个正整数 $n$，找出某个 $k \geq 2$，使得 $n$ 是 $k$ - 好数，或者说明这样的 $k$ 不存在。

## 说明/提示
$6$ 是一个 $3$ - 好数，因为它可以表示为 $3$ 个数的和，且这 $3$ 个数除以 $3$ 有不同的余数：$6 = 1 + 2 + 3$。

$15$ 也是一个 $3$ - 好数，因为 $15 = 1 + 5 + 9$，且 $1$、$5$、$9$ 除以 $3$ 有不同的余数。

$20$ 是一个 $5$ - 好数，因为 $20 = 2 + 3 + 4 + 5 + 6$，且 $2$、$3$、$4$、$5$、$6$ 除以 $5$ 有不同的余数。

## 样例 #1
### 输入
```
5
2
4
6
15
20
```
### 输出
```
-1
-1
3
3
5
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是先根据题目条件推导出 $n$ 与 $k$ 的数学关系，即 $n = kp+\frac{k(k + 1)}{2}$（$p$ 为非负整数），变形得到 $2n=k(2p + k + 1)$，然后利用 $k$ 和 $2p + k + 1$ 一奇一偶的性质，将 $2n$ 分解为一个 $2$ 的次幂和一个奇数的乘积，再根据条件判断 $k$ 的取值。部分题解还对 $n$ 的奇偶性进行了分类讨论，当 $n$ 为奇数时可直接得出 $k = 2$。

### 所选题解
- **作者：sunset_breeze (赞：12)，4星**
    - **关键亮点**：思路清晰，对 $n$ 为奇数和偶数的情况分别进行详细分析，代码实现简洁明了。
- **作者：hyman00 (赞：11)，4星**
    - **关键亮点**：思路简洁，直接给出核心思路和变形公式，代码实现简单高效。
- **作者：Zelotz (赞：7)，4星**
    - **关键亮点**：推导过程详细，对各种情况的讨论全面，代码规范。

### 重点代码
#### sunset_breeze 的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
long long n;
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%lld",&n);
        if(n%2==1)//n为奇数时直接特判
        {
            printf("2\n");
            continue;
        }
        else//n为偶数
        {
            long long a=1,b=0,x=2*n;
            while(x%2==0)
            {
                x/=2;a*=2;//将2*n这个数拆分成奇数乘偶数的形式
            }
            b=(2*n)/a;
            if(min(a,b)<2)printf("-1\n");//a、b的最小值小于2，无解
            else if(a<b)printf("%lld\n",a);//输出较小的一个数
            else if(a>b)printf("%lld\n",b);
        }
    }
    return 0;
}
```
**核心实现思想**：先判断 $n$ 的奇偶性，若 $n$ 为奇数则直接输出 $2$；若 $n$ 为偶数，将 $2n$ 分解为一个 $2$ 的次幂 $a$ 和一个奇数 $b$，比较 $a$ 和 $b$ 的大小，输出较小且大于等于 $2$ 的数，若都不满足则输出 $-1$。

#### hyman00 的代码
```c++
#include <bits/stdc++.h>
using namespace std;
signed main()
{
    int tc=1;
    cin>>tc;
    while(tc--){
        long long n,m=2;
        cin>>n;
        while(!(n&1))n>>=1,m<<=1;
        if(n>m)cout<<m<<"\n";
        else if(n>1)cout<<n<<"\n";
        else cout<<"-1\n";
    }
    return 0;
}
```
**核心实现思想**：通过位运算将 $n$ 中的所有 $2$ 因子提取出来，得到一个奇数 $n$ 和一个 $2$ 的次幂 $m$，比较 $n$ 和 $m$ 的大小，输出较小且大于 $1$ 的数，若不满足则输出 $-1$。

#### Zelotz 的代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, n, a[(int)1e5 + 5];
signed main() {
    read(t);
    while (t--) {
        read(n);
        n <<= 1;
        int a = 1, b, k;
        while (!(n & 1)) n >>= 1, a <<= 1;
        b = n;
        if (a > b) k = b; 
        else k = a; 
        if (k == 1) k = -1;
        write(k), ptc('\n');
    }
    return 0;
}
```
**核心实现思想**：将 $n$ 乘 $2$ 后，通过位运算将其中的所有 $2$ 因子提取出来，得到一个奇数 $b$ 和一个 $2$ 的次幂 $a$，比较 $a$ 和 $b$ 的大小得到 $k$，若 $k$ 为 $1$ 则输出 $-1$。

### 最优关键思路或技巧
- **数学推导**：通过数学推导得到 $n$ 与 $k$ 的关系 $2n=k(2p + k + 1)$，利用 $k$ 和 $2p + k + 1$ 一奇一偶的性质进行求解。
- **奇偶分类讨论**：对 $n$ 的奇偶性进行分类讨论，当 $n$ 为奇数时可直接得出 $k = 2$，简化计算。
- **位运算**：使用位运算提取 $2n$ 中的所有 $2$ 因子，提高计算效率。

### 拓展思路
同类型题或类似算法套路通常涉及数论中的数学推导和性质应用，例如根据题目条件建立数学模型，通过变形和分析找到解题的关键。在解决这类问题时，要善于利用奇偶性、整除性等数学性质，对不同情况进行分类讨论。

### 推荐洛谷题目
- [P1045 麦森数](https://www.luogu.com.cn/problem/P1045)：涉及数论和高精度计算。
- [P1072 Hankson 的趣味题](https://www.luogu.com.cn/problem/P1072)：需要运用数论知识进行推导和求解。
- [P2152 [SDOI2009]SuperGCD](https://www.luogu.com.cn/problem/P2152)：考察高精度和数论相关知识。

### 个人心得摘录与总结
- **max67**：作者表示自己做这道题花费了很长时间，还 WA 了五六发，而别人 10 分钟就 AC 了。总结来说，做数学题需要更熟练地运用数学知识和技巧，提高解题速度和准确性。 

---
处理用时：51.00秒