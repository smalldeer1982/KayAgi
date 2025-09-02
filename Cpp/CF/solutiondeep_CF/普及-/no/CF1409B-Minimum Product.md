# 题目信息

# Minimum Product

## 题目描述

You are given four integers $ a $ , $ b $ , $ x $ and $ y $ . Initially, $ a \ge x $ and $ b \ge y $ . You can do the following operation no more than $ n $ times:

- Choose either $ a $ or $ b $ and decrease it by one. However, as a result of this operation, value of $ a $ cannot become less than $ x $ , and value of $ b $ cannot become less than $ y $ .

Your task is to find the minimum possible product of $ a $ and $ b $ ( $ a \cdot b $ ) you can achieve by applying the given operation no more than $ n $ times.

You have to answer $ t $ independent test cases.

## 说明/提示

In the first test case of the example, you need to decrease $ b $ three times and obtain $ 10 \cdot 7 = 70 $ .

In the second test case of the example, you need to decrease $ a $ one time, $ b $ one time and obtain $ 11 \cdot 7 = 77 $ .

In the sixth test case of the example, you need to decrease $ a $ five times and obtain $ 5 \cdot 11 = 55 $ .

In the seventh test case of the example, you need to decrease $ b $ ten times and obtain $ 10 \cdot 1 = 10 $ .

## 样例 #1

### 输入

```
7
10 10 8 5 3
12 8 8 7 2
12343 43 4543 39 123212
1000000000 1000000000 1 1 1
1000000000 1000000000 1 1 1000000000
10 11 2 1 5
10 11 9 1 10```

### 输出

```
70
77
177177
999999999000000000
999999999
55
10```

# AI分析结果

### 题目内容
# 最小乘积

## 题目描述
给定四个整数 $a$、$b$、$x$ 和 $y$ 。初始时，$a \geq x$ 且 $b \geq y$ 。你可以进行不超过 $n$ 次以下操作：
- 选择 $a$ 或 $b$ 并将其减一 。但是，作为此操作的结果，$a$ 的值不能小于 $x$，$b$ 的值不能小于 $y$ 。
你的任务是通过不超过 $n$ 次给定操作，找出 $a$ 和 $b$ 可能的最小乘积（$a \cdot b$）。
你需要回答 $t$ 个独立的测试用例。

## 说明/提示
在示例的第一个测试用例中，你需要将 $b$ 减少三次，得到 $10 \cdot 7 = 70$ 。
在示例的第二个测试用例中，你需要将 $a$ 减少一次，$b$ 减少一次，得到 $11 \cdot 7 = 77$ 。
在示例的第六个测试用例中，你需要将 $a$ 减少五次，得到 $5 \cdot 11 = 55$ 。
在示例的第七个测试用例中，你需要将 $b$ 减少十次，得到 $10 \cdot 1 = 10$ 。

## 样例 #1
### 输入
```
7
10 10 8 5 3
12 8 8 7 2
12343 43 4543 39 123212
1000000000 1000000000 1 1 1
1000000000 1000000000 1 1 1000000000
10 11 2 1 5
10 11 9 1 10
```
### 输出
```
70
77
177177
999999999000000000
999999999
55
10
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是基于“两数和相等，差越大，积越小”这一数学原理进行贪心策略的设计。即优先对 $a$ 和 $b$ 中较大的数进行减少操作，以使得两数差尽量大从而乘积最小。算法要点在于如何合理分配 $n$ 次操作，在满足 $a \geq x$ 和 $b \geq y$ 的条件下计算出最小乘积。解决难点主要在于边界条件的处理以及确保在各种情况下都能正确地应用贪心策略。不同题解在实现方式上略有差异，有的通过两次尝试（先减 $a$ 和先减 $b$）取最小值，有的通过比较 $a - x$ 和 $b - y$ 的大小来决定先减哪个数等。

### 所选的题解
#### 作者：—维尼— (5星)
- **关键亮点**：思路清晰简洁，利用贪心策略，代码实现直接明了，通过交换 $a,b$ 和 $x,y$ 避免重复代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int t;
    cin>>t;
    while(t--){
        long long a,b,x,y,n;
        cin>>a>>b>>x>>y>>n;
        long long ans=1e18;
        int i=2;
        while(i--){
            int da=min(n,a - x);
            int db=min(n - da,b - y);
            ans=min(ans,(a - da)*1ll*(b - db));//不开long long见祖宗
            swap(a,b);
            swap(x,y);
        }
        cout<<ans<<endl;
    }
}
```
核心实现思想：通过两次循环，每次循环先计算对当前 $a$ 能减少的最大次数 $da$，再计算对当前 $b$ 能减少的最大次数 $db$，更新最小乘积 $ans$，然后交换 $a,b$ 和 $x,y$ 进行下一轮尝试。

#### 作者：江户川·萝卜 (5星)
- **关键亮点**：代码简洁，逻辑清晰，通过两次调用 `solve` 函数分别尝试先减 $a$ 和先减 $b$ 的情况，并取最小值。
```cpp
#include<cstdio>
#include<iostream>
using namespace std;
long long solve(int a,int b,int x,int y,int n){
    long long ans;
    if(a - x>=n) a-=n,n=0;//先减第一个数
    else n-=(a - x),a=x;
    if(b - y>=n) b-=n,n=0;//再减第二个数。
    else n-=(b - y),b=y;
    ans=1ll*a*b;
    return ans;
}
int main(){
    int t,a,b,x,y,n;
    scanf("%d",&t);
    for(int i=1;i<=t;i++){
        scanf("%d%d%d%d%d",&a,&b,&x,&y,&n);
        printf("%lld\n",min(solve(a,b,x,y,n),solve(b,a,y,x,n)));
        //先减a和先减b的最小积都求出来，取最小值。
    }
    return 0;
} 
```
核心实现思想：`solve` 函数中，先尝试将 $a$ 减到最小（不小于 $x$），再将剩余操作次数用于减 $b$（不小于 $y$），最后返回乘积。主函数通过两次调用 `solve` 函数并取最小值得到最终结果。

#### 作者：SSerxhs (4星)
- **关键亮点**：不仅给出了贪心思路的代码，还对“和相等时两数差越大乘积越小”进行了数学证明，逻辑严谨。
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,x,y,a,b,c,t;
inline void read(int &x)
{
    c=getchar();
    while ((c<48)||(c>57)) c=getchar();
    x=c^48;c=getchar();
    while ((c>=48)&&(c<=57))
    {
        x=x*10+(c^48);
        c=getchar();
    }
}
int main()
{
    read(t);
    while (t--)
    {
        read(a);read(b);read(x);read(y);read(n);
        if (a>b) {swap(a,b);swap(x,y);}
        if (a - n>=x) {printf("%lld\n",(ll)(a - n)*b);continue;}
        printf("%lld\n",min((ll)x*max(b - n+(a - x),y),(ll)max(b - n,y)*max(a - n+min(b - y,n),x)));
    }
}
```
核心实现思想：先将 $a,b$ 调整为 $a \leq b$，若 $a$ 减 $n$ 后仍不小于 $x$，则直接输出 $(a - n) * b$；否则，通过复杂的边界判断和计算得出两种情况下的乘积并取最小值。

### 最优关键思路或技巧
利用“两数和相等，差越大，积越小”这一数学原理进行贪心策略设计。在实现中，通过合理的边界判断和操作分配，确保在满足条件下找到最小乘积。同时，部分题解通过交换变量等方式简化代码实现。

### 同类型题或类似算法套路拓展
同类型题通常围绕贪心策略与数学原理结合，比如在资源分配、数值调整等场景下，需要根据给定条件，利用类似“和定差积关系”等数学知识进行贪心选择。

### 洛谷相似题目推荐
- [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：通过不断合并最小的两堆果子，利用贪心策略求最小代价，与本题利用贪心找最优值类似。
- [P1199 [NOIP2010 普及组] 三国游戏](https://www.luogu.com.cn/problem/P1199)：根据武将武力值关系，利用贪心策略确定最佳游戏策略，涉及到对数值关系的分析与贪心选择。
- [P2859 [USACO06DEC]Milk Patterns G](https://www.luogu.com.cn/problem/P2859)：通过对数据的分析，利用贪心策略解决字符串子串出现次数相关问题，同样是基于一定条件下的贪心选择。 

---
处理用时：65.02秒