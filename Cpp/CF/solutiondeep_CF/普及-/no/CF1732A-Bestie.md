# 题目信息

# Bestie

## 题目描述

You are given an array $ a $ consisting of $ n $ integers $ a_1, a_2, \ldots, a_n $ . Friends asked you to make the [greatest common divisor (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor) of all numbers in the array equal to $ 1 $ . In one operation, you can do the following:

- Select an arbitrary index in the array $ 1 \leq i \leq n $ ;
- Make $ a_i = \gcd(a_i, i) $ , where $ \gcd(x, y) $ denotes the GCD of integers $ x $ and $ y $ . The cost of such an operation is $ n - i + 1 $ .

You need to find the minimum total cost of operations we need to perform so that the GCD of the all array numbers becomes equal to $ 1 $ .

## 说明/提示

In the first test case, the GCD of the entire array is already equal to $ 1 $ , so there is no need to perform operations.

In the second test case, select $ i = 1 $ . After this operation, $ a_1 = \gcd(2, 1) = 1 $ . The cost of this operation is $ 1 $ .

In the third test case, you can select $ i = 1 $ , after that the array $ a $ will be equal to $ [1, 4] $ . The GCD of this array is $ 1 $ , and the total cost is $ 2 $ .

In the fourth test case, you can select $ i = 2 $ , after that the array $ a $ will be equal to $ [3, 2, 9] $ . The GCD of this array is $ 1 $ , and the total cost is $ 2 $ .

In the sixth test case, you can select $ i = 4 $ and $ i = 5 $ , after that the array $ a $ will be equal to $ [120, 60, 80, 4, 5] $ . The GCD of this array is $ 1 $ , and the total cost is $ 3 $ .

## 样例 #1

### 输入

```
9
1
1
1
2
2
2 4
3
3 6 9
4
5 10 15 20
5
120 60 80 40 80
6
150 90 180 120 60 30
6
2 4 6 9 12 18
6
30 60 90 120 125 125```

### 输出

```
0
1
2
2
1
3
3
0
1```

# AI分析结果

### 题目内容
# Bestie

## 题目描述
给定一个由 $n$ 个整数 $a_1, a_2, \ldots, a_n$ 组成的数组 $a$ 。朋友们要求你使数组中所有数字的[最大公约数（GCD）](https://en.wikipedia.org/wiki/Greatest_common_divisor)等于 $1$ 。在一次操作中，你可以执行以下操作：
- 选择数组中任意一个索引 $1 \leq i \leq n$；
- 使 $a_i = \gcd(a_i, i)$ ，其中 $\gcd(x, y)$ 表示整数 $x$ 和 $y$ 的最大公约数。这样一次操作的代价是 $n - i + 1$ 。

你需要找出我们需要执行的操作的最小总代价，以便使数组中所有数字的最大公约数等于 $1$ 。

## 说明/提示
在第一个测试用例中，整个数组的最大公约数已经等于 $1$ ，所以无需执行操作。

在第二个测试用例中，选择 $i = 1$ 。在此操作之后，$a_1 = \gcd(2, 1) = 1$ 。此操作的代价是 $1$ 。

在第三个测试用例中，你可以选择 $i = 1$ ，之后数组 $a$ 将变为 $[1, 4]$ 。这个数组的最大公约数是 $1$ ，总代价是 $2$ 。

在第四个测试用例中，你可以选择 $i = 2$ ，之后数组 $a$ 将变为 $[3, 2, 9]$ 。这个数组的最大公约数是 $1$ ，总代价是 $2$ 。

在第六个测试用例中，你可以选择 $i = 4$ 和 $i = 5$ ，之后数组 $a$ 将变为 $[120, 60, 80, 4, 5]$ 。这个数组的最大公约数是 $1$ ，总代价是 $3$ 。

## 样例 #1
### 输入
```
9
1
1
1
2
2
2 4
3
3 6 9
4
5 10 15 20
5
120 60 80 40 80
6
150 90 180 120 60 30
6
2 4 6 9 12 18
6
30 60 90 120 125 125
```
### 输出
```
0
1
2
2
1
3
3
0
1
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是基于数学性质，利用 $\gcd(n, n - 1) = 1$ 这一特性，得出最小费用必定 $\leq 3$ 的结论，然后通过分类讨论来确定最小费用。不同题解在具体实现和细节处理上略有差异。

### 所选的题解
- **作者：dyx2021 (5星)**
    - **关键亮点**：思路清晰，不仅给出解题思路，还通过图片辅助理解，代码中考虑了 $n - 2$ 可能为负数的细节，使用位运算优化求最大公约数。
    - **个人心得**：考试时思考时间长，考完快速完成代码，在处理 $n - 2$ 为负数导致数组下标越界问题上遇到困难。
    - **核心代码片段**：
```cpp
int gcd(int a,int b)
{
  while(b^=a^=b^=a%=b);
  return a;
}
int main()
{
  T=read();
  while(T--)
    {
      n=read();
      for(int i=1;i<=n;i++)
        {
          a[i]=read();
        }
      int sum=a[1];
      for(int i=2;i<=n;i++)
        {
          sum=gcd(sum,a[i]);
        }
      if(sum==1)
        {
          cout<<"0"<<endl;
          continue;
        }
      int ans=n;
      int i;
      if(n<=3) i=2;
      else i=n-2;
      for(;i<=n;i++)
        {
          if(gcd(sum,i)==1)
            {
              ans=n-i+1;
            }
        }
      cout<<min(ans,3)<<endl;
    }
  return 0;
}
```
核心实现思想：先计算数组所有数的最大公约数 `sum`，若 `sum` 为 $1$ 则直接输出 $0$ 。否则根据 $n$ 的大小确定枚举起始位置，枚举 $i$ ，若 `gcd(sum, i)` 为 $1$ 则更新最小代价 `ans` ，最后输出 `ans` 和 $3$ 中的较小值。

- **作者：GalwayGirl (4星)**
    - **关键亮点**：代码简洁明了，直接按照四种情况进行判断，逻辑清晰。
    - **核心代码片段**：
```cpp
int gcd(long long a,long long b){
    if(!b)return a;
    return gcd(b,a%b);
}
int main(){
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
        long long yin=a[1];
        for(int i=2;i<=n;i++)yin=gcd(yin,a[i]);
        if(yin==1){
            printf("0\n");
            continue;
        }
        if(gcd(yin,gcd(n,a[n]))==1){
            printf("1\n");
            continue;
        }
        if(gcd(yin,gcd(n-1,a[n-1]))==1){
            printf("2\n");
            continue;
        }
        printf("3\n");
    }
    return 0;
}
```
核心实现思想：先计算数组所有数的最大公约数 `yin` ，若 `yin` 为 $1$ 输出 $0$ 。否则依次判断对 $n$ 和 $a_n$ 操作后、对 $n - 1$ 和 $a_{n - 1}$ 操作后数组所有数的最大公约数是否为 $1$ ，并输出相应结果，若都不满足则输出 $3$ 。

### 最优关键思路或技巧
利用 $\gcd(n, n - 1) = 1$ 这一数学性质，确定最小费用上限为 $3$ ，通过分类讨论不同情况来求解最小费用，同时在实现中注意边界条件和求最大公约数的优化。

### 同类型题或类似算法套路拓展
此类题目通常围绕数论中的最大公约数、最小公倍数等概念，结合数组操作与代价计算。常见套路是挖掘数论性质来简化问题，通过分类讨论或枚举关键位置解决。

### 洛谷相似题目推荐
- [P1029 最大公约数和最小公倍数问题](https://www.luogu.com.cn/problem/P1029)
- [P1072 Hankson 的趣味题](https://www.luogu.com.cn/problem/P1072)
- [P2152 [SDOI2009]SuperGCD](https://www.luogu.com.cn/problem/P2152)

---
处理用时：46.53秒