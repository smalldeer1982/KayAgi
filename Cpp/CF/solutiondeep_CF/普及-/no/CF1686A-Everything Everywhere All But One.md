# 题目信息

# Everything Everywhere All But One

## 题目描述

You are given an array of $ n $ integers $ a_1, a_2, \ldots, a_n $ . After you watched the amazing film "Everything Everywhere All At Once", you came up with the following operation.

In one operation, you choose $ n-1 $ elements of the array and replace each of them with their arithmetic mean (which doesn't have to be an integer). For example, from the array $ [1, 2, 3, 1] $ we can get the array $ [2, 2, 2, 1] $ , if we choose the first three elements, or we can get the array $ [\frac{4}{3}, \frac{4}{3}, 3, \frac{4}{3}] $ , if we choose all elements except the third.

Is it possible to make all elements of the array equal by performing a finite number of such operations?

## 说明/提示

In the first test case, all elements are already equal.

In the second test case, you can choose all elements except the third, their average is $ \frac{1 + 2 + 4 + 5}{4} = 3 $ , so the array will become $ [3, 3, 3, 3, 3] $ .

It's possible to show that it's impossible to make all elements equal in the third and fourth test cases.

## 样例 #1

### 输入

```
4
3
42 42 42
5
1 2 3 4 5
4
4 3 2 1
3
24 2 22```

### 输出

```
YES
YES
NO
NO```

# AI分析结果

### 题目内容
# 万物一体，独缺其一

## 题目描述
给定一个包含 $n$ 个整数的数组 $a_1, a_2, \ldots, a_n$ 。在观看了精彩的电影《瞬息全宇宙》后，你想出了以下操作。

在一次操作中，你选择数组中的 $n - 1$ 个元素，并将它们各自替换为它们的算术平均值（该平均值不一定是整数）。例如，对于数组 $[1, 2, 3, 1]$ ，如果我们选择前三个元素，我们可以得到数组 $[2, 2, 2, 1]$ ；如果我们选择除第三个元素之外的所有元素，我们可以得到数组 $[\frac{4}{3}, \frac{4}{3}, 3, \frac{4}{3}]$ 。

是否有可能通过执行有限次这样的操作使数组的所有元素都相等？

## 说明/提示
在第一个测试用例中，所有元素已经相等。

在第二个测试用例中，你可以选择除第三个元素之外的所有元素，它们的平均值是 $\frac{1 + 2 + 4 + 5}{4} = 3$ ，所以数组将变为 $[3, 3, 3, 3, 3]$ 。

可以证明在第三个和第四个测试用例中不可能使所有元素相等。

## 样例 #1
### 输入
```
4
3
42 42 42
5
1 2 3 4 5
4
4 3 2 1
3
24 2 22
```
### 输出
```
YES
YES
NO
NO
```

### 算法分类
数学

### 题解综合分析与结论
这些题解的核心思路都是基于对操作性质的分析得出结论：若数组中存在一个数等于数组所有元素的平均值，则可以通过有限次操作使所有元素相等，否则不能。各题解在推导过程和实现细节上略有不同。有的题解通过证明操作的性质，如操作后数列和不变、对同一个数多次操作无本质区别等，来辅助得出结论；有的则直接从操作结果的形式出发进行推理。在实现上，基本都是先计算数组总和，再遍历数组判断是否存在满足条件的数。

### 所选的题解
- **作者：Qerucy (5星)**
    - **关键亮点**：思路清晰简洁，先提出朴素枚举思路，后给出优化方法，通过预先计算总和优化判断平均数的过程。
    - **个人心得**：提到优化后的代码在实际运行中可能更慢，引发对优化效果全面评估的思考。
    - **核心代码**：
```cpp
#include<cstdio>
using namespace std;
int t,n;
double a[210];
double sum;
int main(){
    scanf("%d",&t);
    while(t--){
        sum=0;
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%lf",&a[i]);
            sum+=a[i];
        }
        bool fg=0;
        for(int i=1;i<=n;i++){
            if((sum-a[i])/(n-1)==a[i]){
                fg=1;
                break;
            }
        }
        puts(fg?"YES":"NO");
    }
    return 0;
}
```
核心实现思想：先读入数据并计算数组总和，然后遍历数组，通过判断总和减去当前元素后除以 $n - 1$ 是否等于当前元素，来确定是否存在满足条件的元素。

- **作者：ningago (5星)**
    - **关键亮点**：详细证明了操作的多个重要性质，如操作后数列和不变、对同一数多次操作无区别、若能使元素相等则至多只需一次本质不同的操作等，逻辑严谨。
    - **核心代码**：
```cpp
#include <cstdio>
int T,n;
int a[100];
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        int sum = 0;
        for(int i = 1;i <= n;i++)
        {
            scanf("%d",&a[i]);
            sum += a[i];
        }
        if(sum % n)
        {
            printf("NO\n");
            continue;
        }
        bool flag = 0;
        for(int i = 1;i <= n;i++)
        {
            if(sum / n == a[i])
                flag = 1;
        }
        if(flag)
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}
```
核心实现思想：先读入数据并计算总和，判断总和是否能被 $n$ 整除，若不能则直接输出 `NO`；若能整除，再遍历数组判断是否存在元素等于平均值，若存在则输出 `YES`，否则输出 `NO`。

- **作者：sgl654321 (4星)**
    - **关键亮点**：将求平均值操作转化为数学等式，避免除法运算可能带来的精度误差，从数学角度优化判断条件。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,a[100],sum;
bool flag;
int main(){
    cin>>t;
    while(t--){
        cin>>n;
        sum=0;
        flag=0;
        for(int i=1;i<=n;i++){
            cin>>a[i];sum+=a[i];
        }
        for(int i=1;i<=n;i++)
            if(sum-a[i]==a[i]*(n-1)){
                cout<<"YES"<<endl;flag=1;break;
            }
        if(!flag)cout<<"NO"<<endl;
    }
    return 0;
} 
```
核心实现思想：先读入数据并计算总和，然后遍历数组，通过判断总和减去当前元素是否等于当前元素乘以 $n - 1$，来确定是否存在满足条件的元素。

### 最优关键思路或技巧
- **数学性质分析**：通过对操作后数列和不变、多次操作性质等数学性质的分析，得出能否使所有元素相等的判断依据，这是解决本题的关键思维方式。
- **避免除法运算**：将除法判断条件转化为乘法，避免了可能出现的精度误差，是代码实现上的优化技巧。

### 拓展
同类型题或类似算法套路：此类题目通常需要挖掘操作过程中的不变量，通过对操作性质的数学分析得出结论。常见的不变量如总和、奇偶性等。在解决这类问题时，要善于从操作的定义出发，进行严谨的数学推导。

### 洛谷相似题目推荐
- **P1147 连续自然数和**：同样需要对数学关系进行分析，通过枚举和数学推导来解决问题。
- **P1085 [NOIP2005 普及组] 不高兴的津津**：根据题目给定的条件和限制，通过简单的数学计算和判断来求解，锻炼对条件的分析和数学运用能力。
- **P2671 [NOIP2015 普及组] 求和**：需要利用数学知识优化算法，通过对数据关系的分析找到高效的计算方法。 

---
处理用时：57.30秒