# Wet Shark and Flowers

## 题目描述

There are $ n $ sharks who grow flowers for Wet Shark. They are all sitting around the table, such that sharks $ i $ and $ i+1 $ are neighbours for all $ i $ from $ 1 $ to $ n-1 $ . Sharks $ n $ and $ 1 $ are neighbours too.

Each shark will grow some number of flowers $ s_{i} $ . For $ i $ -th shark value $ s_{i} $ is random integer equiprobably chosen in range from $ l_{i} $ to $ r_{i} $ . Wet Shark has it's favourite prime number $ p $ , and he really likes it! If for any pair of neighbouring sharks $ i $ and $ j $ the product $ s_{i}·s_{j} $ is divisible by $ p $ , then Wet Shark becomes happy and gives $ 1000 $ dollars to each of these sharks.

At the end of the day sharks sum all the money Wet Shark granted to them. Find the expectation of this value.

## 说明/提示

A prime number is a positive integer number that is divisible only by $ 1 $ and itself. $ 1 $ is not considered to be prime.

Consider the first sample. First shark grows some number of flowers from $ 1 $ to $ 2 $ , second sharks grows from $ 420 $ to $ 421 $ flowers and third from $ 420420 $ to $ 420421 $ . There are eight cases for the quantities of flowers $ (s_{0},s_{1},s_{2}) $ each shark grows:

1. $ (1,420,420420) $ : note that $ s_{0}·s_{1}=420 $ , $ s_{1}·s_{2}=176576400 $ , and $ s_{2}·s_{0}=420420 $ . For each pair, $ 1000 $ dollars will be awarded to each shark. Therefore, each shark will be awarded $ 2000 $ dollars, for a total of $ 6000 $ dollars.
2. $ (1,420,420421) $ : now, the product $ s_{2}·s_{0} $ is not divisible by $ 2 $ . Therefore, sharks $ s_{0} $ and $ s_{2} $ will receive $ 1000 $ dollars, while shark $ s_{1} $ will receive $ 2000 $ . The total is $ 4000 $ .
3. $ (1,421,420420) $ : total is $ 4000 $
4. $ (1,421,420421) $ : total is $ 0 $ .
5. $ (2,420,420420) $ : total is $ 6000 $ .
6. $ (2,420,420421) $ : total is $ 6000 $ .
7. $ (2,421,420420) $ : total is $ 6000 $ .
8. $ (2,421,420421) $ : total is $ 4000 $ .

The expected value is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF621C/32b3d915ed39360d8a8863b7fea1a23baf7615be.png).

In the second sample, no combination of quantities will garner the sharks any money.

## 样例 #1

### 输入

```
3 2
1 2
420 421
420420 420421
```

### 输出

```
4500.0
```

## 样例 #2

### 输入

```
3 5
1 4
2 3
11 14
```

### 输出

```
0.0
```

# 题解

## 作者：chr1stopher (赞：1)

题目大意不难读懂，关键得知道这题求的是**期望值**。

**思路**： 此题要求l~r区间内是p的倍数的数的个数，一般思路会想到用**前缀和**，但此处数据范围为**1e9**，无法开这么大的数组，故我们需另寻他法。注意到这里的p保证为**素数**，故可以想到通过(r/p - (l-1)/p)来求得区间内符合条件数的个数。然后求出相邻两组符合条件的对数，再根据相关公式算出每组期望，最后相加即可。

**ACODE:**

```cpp
#include<stdio.h>
#include<iostream>
#include<string.h>
#include<algorithm>
#include<math.h>
#include<string>
#include<queue>
#include<utility>
#include<vector>
#include<map>
#include<set>
#define lson l , m , rt << 1
#define rson m+1 , r , rt << 1 | 1
#define mem(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const double pi = 3.1415926535;
const double eps = 1e-6;
const int MXN = 1e5 + 7;
const int MXM = 1e3 + 7;
const int MX = 1e9 + 7;
const int maxbit = 18;
const double val = pi/180.0;
const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3f;
const int mod = 1e4 + 7;
ll p,n;
double ans = 0;
struct node
{
    ll t;//区间内符合条件数的个数
    ll l;//区间长度
}a[MXN];
int main()
{
    scanf("%lld%lld",&n,&p);
    ll x,y;
    for(int i = 1;i <= n;++i)
    {
        scanf("%lld %lld",&x,&y);
        //类似前缀和的求法 故为(x-1)!!!
        a[i].t = (y)/p - (x-1)/p;
        a[i].l = y - x + 1;
        //printf("%d %d\n",a[i].t,a[i].l);
    }
    for(int i = 1;i < n;++i)
    {
        //两种需要考虑的情况数（注意避免重复）
        ll r1 = a[i].t * a[i+1].l;
        ll r2 = a[i+1].t * (a[i].l - a[i].t);
        //依次求得每组的期望并累加
        ans += (double)(r1 + r2) * 2000.0 / (a[i].l * a[i+1].l);
        //printf("%.2lf\n",ans);
    }

    //单独求最后一组
    ll r1 = a[n].t * a[1].l;
    ll r2 = a[1].t * (a[n].l - a[n].t);
    ans += (double)(r1 + r2) * 2000.0 / (a[n].l * a[1].l);
    printf("%lf",ans);
    return 0;
}

```


---

