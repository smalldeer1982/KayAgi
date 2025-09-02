# 题目信息

# Kids Seating

## 题目描述

Today the kindergarten has a new group of $ n $ kids who need to be seated at the dinner table. The chairs at the table are numbered from $ 1 $ to $ 4n $ . Two kids can't sit on the same chair. It is known that two kids who sit on chairs with numbers $ a $ and $ b $ ( $ a \neq b $ ) will indulge if:

1. $ gcd(a, b) = 1 $ or,
2. $ a $ divides $ b $ or $ b $ divides $ a $ .

 $ gcd(a, b) $ — the maximum number $ x $ such that $ a $ is divisible by $ x $ and $ b $ is divisible by $ x $ .

For example, if $ n=3 $ and the kids sit on chairs with numbers $ 2 $ , $ 3 $ , $ 4 $ , then they will indulge since $ 4 $ is divided by $ 2 $ and $ gcd(2, 3) = 1 $ . If kids sit on chairs with numbers $ 4 $ , $ 6 $ , $ 10 $ , then they will not indulge.

The teacher really doesn't want the mess at the table, so she wants to seat the kids so there are no $ 2 $ of the kid that can indulge. More formally, she wants no pair of chairs $ a $ and $ b $ that the kids occupy to fulfill the condition above.

Since the teacher is very busy with the entertainment of the kids, she asked you to solve this problem.

## 样例 #1

### 输入

```
3
2
3
4```

### 输出

```
6 4
4 6 10
14 10 12 8```

# AI分析结果

### 题目内容
# 儿童座位安排

## 题目描述
今天幼儿园来了一组$n$个小朋友，需要安排在餐桌就座。餐桌的椅子编号从$1$到$4n$。两个小朋友不能坐在同一把椅子上。已知坐在编号为$a$和$b$（$a \neq b$）椅子上的两个小朋友会打闹，如果：
1. $\gcd(a, b) = 1$ 或者，
2. $a$ 能整除 $b$ 或者 $b$ 能整除 $a$。

$\gcd(a, b)$ 表示能同时整除 $a$ 和 $b$ 的最大数 $x$。

例如，如果 $n = 3$，小朋友坐在编号为 $2$、$3$、$4$ 的椅子上，那么他们会打闹，因为 $4$ 能被 $2$ 整除且 $\gcd(2, 3) = 1$。如果小朋友坐在编号为 $4$、$6$、$10$ 的椅子上，那么他们不会打闹。

老师真的不希望餐桌上出现混乱，所以她希望安排小朋友就座，使得任意两个小朋友都不会打闹。更正式地说，她希望小朋友所坐的任意两把椅子 $a$ 和 $b$ 都不满足上述条件。

由于老师忙于小朋友的娱乐活动，她请你解决这个问题。

## 样例 #1
### 输入
```
3
2
3
4
```
### 输出
```
6 4
4 6 10
14 10 12 8
```

### 算法分类
构造

### 题解综合分析与结论
这些题解的核心思路都是通过构造一个满足条件的数列来解决问题。主要围绕让数列中的数满足 $\gcd(a,b)\neq1$ 且 $a$ 与 $b$ 不存在整除关系，同时每个数在 $1$ 到 $4n$ 的范围内。多数题解选择让数列中的数都为 $2$ 的倍数来保证 $\gcd(a,b)\neq1$ ，再通过合理选择数的范围来避免整除关系。

### 所选的题解
- **作者：小王子2021 (4星)**
    - **关键亮点**：思路清晰，先明确为使 $\gcd≠1$ 设 $\gcd = 2$ ，并通过分析得出第一个数为 $2 \times n$ ，后续数在 $2 \times n$ 基础上每次加 $2$ ，实现简单直接。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
int main()
{
    cin>>t;
    while(t--)
    {
        cin>>n;
        cout<<2*n<<" ";
        int tmp=2*n;
        for(int i=1;i<=n-1;i++)
        {
            tmp+=2;
            cout<<tmp<<" ";
        }
        cout<<endl;
    }
}
```
    - **核心实现思想**：先输出 $2n$ ，然后通过循环，每次让变量 $tmp$ 增加 $2$ 并输出，得到满足条件的 $n$ 个数。
- **作者：是个汉子 (4星)**
    - **关键亮点**：从 $4n$ 开始每隔两个输出一次，即输出 $4n,4n - 2,4n - 4,\cdots,2n + 2$ ，并给出了较为清晰的正确性证明，逻辑完整。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>

using namespace std;
int t,n;

int main(){
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        for(int i=4*n;i>2*n;i-=2) printf("%d ",i);
        puts("");
    }
    return 0;
}
```
    - **核心实现思想**：通过循环从 $4n$ 开始，每次减 $2$ ，输出 $n$ 个数，保证这些数满足条件。
- **作者：江户川·萝卜 (4星)**
    - **关键亮点**：先从样例观察出都是 $2$ 的倍数，解决 $\gcd(a,b)=1$ 的问题，再从 $4n$ 开始依次枚举 $n$ 个 $2$ 的倍数，并给出不存在整除关系的简单推导，思路连贯。
    - **重点代码**：
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int T,n;
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=2*n;i>n;i--) printf("%d ",i*2);
        puts("");
    }
    return 0;
}
```
    - **核心实现思想**：通过循环从 $2n$ 到 $n + 1$ 倒序，将每个数乘 $2$ 后输出，得到满足条件的序列。

### 最优关键思路或技巧
通过观察样例发现规律，选择让所有数具有公因子 $2$ ，保证数与数之间不互质，同时巧妙地选择数的范围，如从 $2n$ 开始递增或从 $4n$ 开始递减来构造数列，确保数与数之间不存在整除关系。

### 同类型题或类似算法套路拓展
此类构造题通常需要通过观察样例或分析条件找到满足要求的规律来构造数据。类似套路是先满足其中一个较容易的条件（如本题中让数不互质），再在此基础上调整使其他条件也满足（如不存在整除关系）。

### 洛谷相似知识点题目推荐
- **P1141 01迷宫**：通过构造不同的路径和状态来解决问题，与本题构造满足特定条件的数列思路类似。
- **P1036 [NOIP2002 普及组] 选数**：需要从给定的数中构造满足一定条件（如和为质数）的组合，同样考察构造能力。
- **P2676 [USACO07DEC]Bookshelf B**：通过构造不同的方案来满足书架高度的限制，也是构造类问题。 

---
处理用时：87.31秒