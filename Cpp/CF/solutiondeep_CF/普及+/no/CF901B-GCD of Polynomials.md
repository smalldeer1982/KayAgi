# 题目信息

# GCD of Polynomials

## 题目描述

Suppose you have two polynomials ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF901B/b88d8c9afbcdbe4c3db30f4f8047f16a3a48c8eb.png) and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF901B/e0c93f76951451d9aabeb4047e1f1124cfc2b66d.png). Then polynomial ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF901B/1a8148c316d81cb0dcf0ac6a016f160db2da72c1.png) can be uniquely represented in the following way:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF901B/c5e7dcb363dde0ba8872328b8e411c128512b38f.png)This can be done using [long division](https://en.wikipedia.org/wiki/Polynomial_long_division). Here, ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF901B/a1f26d7c8115e83b311bbacc16505e6f20f92b7d.png) denotes the degree of polynomial $ P(x) $ . ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF901B/026a0fc1a864c69852c699730e0a6f2d32f753be.png) is called the remainder of division of polynomial ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF901B/1a8148c316d81cb0dcf0ac6a016f160db2da72c1.png) by polynomial ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF901B/ebb5c58177e55fa198a7a231f3c0e4b1f18a6a49.png), it is also denoted as ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF901B/6e44041e1df78606fc571f5db249361dad8df62e.png).

Since there is a way to divide polynomials with remainder, we can define Euclid's algorithm of finding the greatest common divisor of two polynomials. The algorithm takes two polynomials ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF901B/5a51ce4106123f55c64d5fbd31176d2fcf184db6.png). If the polynomial ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF901B/ebb5c58177e55fa198a7a231f3c0e4b1f18a6a49.png) is zero, the result is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF901B/1a8148c316d81cb0dcf0ac6a016f160db2da72c1.png), otherwise the result is the value the algorithm returns for pair ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF901B/ad56ca03078389def1a802276b6af4c037ddb9af.png). On each step the degree of the second argument decreases, so the algorithm works in finite number of steps. But how large that number could be? You are to answer this question.

You are given an integer $ n $ . You have to build two polynomials with degrees not greater than $ n $ , such that their coefficients are integers not exceeding $ 1 $ by their absolute value, the leading coefficients (ones with the greatest power of $ x $ ) are equal to one, and the described Euclid's algorithm performs exactly $ n $ steps finding their greatest common divisor. Moreover, the degree of the first polynomial should be greater than the degree of the second. By a step of the algorithm we mean the transition from pair ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF901B/5a51ce4106123f55c64d5fbd31176d2fcf184db6.png) to pair ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF901B/ad56ca03078389def1a802276b6af4c037ddb9af.png).

## 说明/提示

In the second example you can print polynomials $ x^{2}-1 $ and $ x $ . The sequence of transitions is

 $ (x^{2}-1,x)→(x,-1)→(-1,0). $ There are two steps in it.

## 样例 #1

### 输入

```
1
```

### 输出

```
1
0 1
0
1
```

## 样例 #2

### 输入

```
2
```

### 输出

```
2
-1 0 1
1
0 1
```

# AI分析结果

### 题目内容
# 多项式的最大公约数

## 题目描述
假设你有两个多项式 \(P(x)\) 和 \(Q(x)\) 。那么多项式 \(A(x)\) 可以用以下方式唯一表示：
\(A(x)=B(x)\times C(x)+D(x)\)，其中 \(\text{deg}(D)<\text{deg}(C)\) 。这可以通过[多项式长除法](https://en.wikipedia.org/wiki/Polynomial_long_division)来实现。这里，\(\text{deg}(P)\) 表示多项式 \(P(x)\) 的次数。\(D(x)\) 被称为多项式 \(A(x)\) 除以多项式 \(C(x)\) 的余数，也表示为 \(A(x)\bmod C(x)\) 。

由于存在带余数的多项式除法，我们可以定义求两个多项式最大公约数的欧几里得算法。该算法接受两个多项式 \((A(x),B(x))\) 。如果多项式 \(B(x)\) 为零，结果就是 \(A(x)\) ，否则结果就是该算法对 \((B(x),A(x)\bmod B(x))\) 这对多项式返回的值。在每一步，第二个参数的次数都会降低，所以该算法会在有限步数内完成。但是这个步数最大能是多少呢？你需要回答这个问题。

给定一个整数 \(n\) 。你必须构造两个次数不超过 \(n\) 的多项式，使得它们的系数是绝对值不超过 \(1\) 的整数，首项系数（\(x\) 的最高次幂的系数）等于 \(1\) ，并且上述欧几里得算法在求它们的最大公约数时恰好执行 \(n\) 步。此外，第一个多项式的次数应该大于第二个多项式的次数。算法的一步是指从 \((A(x),B(x))\) 这对多项式转换到 \((B(x),A(x)\bmod B(x))\) 这对多项式。

## 说明/提示
在第二个例子中，你可以输出多项式 \(x^{2}-1\) 和 \(x\) 。转换序列为 \((x^{2}-1,x)\to(x,-1)\to(-1,0)\) 。其中有两步。

## 样例 #1
### 输入
```
1
```
### 输出
```
1
0 1
0
1
```

## 样例 #2
### 输入
```
2
```
### 输出
```
2
-1 0 1
1
0 1
```

### 算法分类
构造

### 综合分析与结论
这两道题解都围绕构造满足特定条件多项式展开。
- **思路方面**：两者均采用递推思想。JK_LOVER 题解从多项式相模原理出发，通过特定构造形式推导出递推关系；Missa 题解类比整数 gcd 递推，结合斐波那契数列构造形式，在遇到系数范围问题时采用乱搞思路调整。
- **算法要点**：JK_LOVER 题解基于数学推导得出 \(dp[i][j]\) 的递推式；Missa 题解则是根据类比得出 \(s_{i+1,j}\) 的递推式，并在系数不满足时调整递推方式。
- **解决难点**：难点在于如何构造多项式使欧几里得算法执行恰好 \(n\) 步且系数满足条件。JK_LOVER 通过数学原理推导解决；Missa 则是先按常规思路，遇到系数问题后通过乱搞方式并结合官方题解提示解决。

### 所选的题解
- **作者：JK_LOVER（5星）**
  - **关键亮点**：思路清晰，从多项式相模的基本原理入手，逐步推导得出递推关系，逻辑连贯。代码简洁明了，直接根据递推关系实现，可读性高。
  - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int read(){
    int x = 0,f=0;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=1;ch=getchar();}
    while(isdigit(ch)){x=x*10+ch-'0';ch=getchar();}
    return f?-x:x;
}
int dp[210][210],n;
int main()
{
    n = read();
    dp[1][1] = 1;
    dp[0][0] = 1;
    for(int i = 2;i <= n;i++)
    {
        for(int j = 0;j <= i;j++)
        {
            if(j==0) dp[i][j] = dp[i-2][j];
            else dp[i][j] = (dp[i-2][j]+dp[i-1][j-1])%2;
        }
    }
    printf("%d\n",n);
    for(int i = 0;i <= n;i++)
    printf("%d ",dp[n][i]);
    printf("\n%d\n",n-1);
    for(int i = 0;i <= n-1;i++)
    printf("%d ",dp[n-1][i]);
    return 0*printf("\n");
}
```
  - **核心实现思想**：利用递推关系 \(dp[i][j]\) 来计算多项式各项系数，外层循环遍历次数 \(i\)，内层循环遍历每一项的系数 \(j\)，根据 \(j\) 是否为 \(0\) 采用不同递推式，最后输出两个多项式的次数及各项系数。

- **作者：Missa（4星）**
  - **关键亮点**：类比整数 gcd 的递推方式，容易理解。在遇到系数不满足条件时，通过分析和尝试不同的构造方式（调整 \(B(x)\) 的正负）解决问题，虽然是乱搞思路但能结合官方提示说明其合理性。
  - **个人心得**：通过提交代码发现 WA，观察标准答案发现递推思路可行但系数存在问题，通过不断尝试和分析官方题解及评论区找到解决办法。
  - **重点代码**：
```cpp
#include <cstdio>
using namespace std;
const int M = 155;
int s[M][M], n;
int main(){
    scanf("%d", &n);
    s[0][0] = 1;
    s[1][1] = 1;
    for(int i = 1; i <= n; i++){
        //先验证 F_n(x)=F_{n-1}(x)+F_{n-2}(x) 的情况 
        s[i+1][0] = s[i-1][0];
        for(int j = 1; j <= i+1; j++){
            s[i+1][j] = s[i][j-1] + s[i-1][j];
        }
        //进行判断 
        bool f = 1;
        for(int j = 0; j <= i+1; j++){
            if(s[i+1][j] < -1 || s[i+1][j] > 1) {f = 0; break;}
        }
        if(f) continue;
        //如果不行，就让 F_n(x)=F_{n-1}(x)-F_{n-2}(x)
        s[i+1][0] = -s[i-1][0];
        for(int j = 1; j <= i+1; j++){
            s[i+1][j] = s[i][j-1] - s[i-1][j];
        }
    }
    printf("%d\n", n);
    for(int i = 0; i <= n; i++)
        printf("%d ", s[n][i]);
    printf("\n%d\n", n-1);
    for(int i = 0; i < n; i++)
        printf("%d ", s[n-1][i]);
}
```
  - **核心实现思想**：先按 \(F_n(x)=F_{n-1}(x)+F_{n-2}(x)\) 尝试构造多项式并计算系数，检查系数是否满足范围，不满足则调整为 \(F_n(x)=F_{n-1}(x)-F_{n-2}(x)\) 重新计算，最后输出两个多项式的次数及各项系数。

### 最优关键思路或技巧
利用递推思想构造多项式。通过分析多项式相模的过程，找到多项式各项系数之间的递推关系，从而构造出满足欧几里得算法执行步数和系数条件的多项式。

### 可拓展之处
同类型题或类似算法套路：此类题目属于构造类问题，关键在于利用数学原理找到递推关系来构造满足特定条件的对象。类似套路可应用于其他需要构造特定数学对象（如矩阵、数列等）满足特定运算步骤或性质的题目。

### 推荐洛谷题目
- [P1028 数的计算](https://www.luogu.com.cn/problem/P1028)：通过对数字运算规则的分析，利用递推构造满足条件的数字序列。
- [P1255 数楼梯](https://www.luogu.com.cn/problem/P1255)：根据楼梯走法的限制，通过递推构造不同台阶数对应的走法数量。
- [P1990 覆盖墙壁](https://www.luogu.com.cn/problem/P1990)：依据墙壁覆盖的规则，利用递推构造不同长度墙壁的覆盖方案数。 

---
处理用时：65.37秒