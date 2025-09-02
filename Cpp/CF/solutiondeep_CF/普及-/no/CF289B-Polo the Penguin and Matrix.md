# 题目信息

# Polo the Penguin and Matrix

## 题目描述

Little penguin Polo has an $ n×m $ matrix, consisting of integers. Let's index the matrix rows from 1 to $ n $ from top to bottom and let's index the columns from 1 to $ m $ from left to right. Let's represent the matrix element on the intersection of row $ i $ and column $ j $ as $ a_{ij} $ .

In one move the penguin can add or subtract number $ d $ from some matrix element. Find the minimum number of moves needed to make all matrix elements equal. If the described plan is impossible to carry out, say so.

## 样例 #1

### 输入

```
2 2 2
2 4
6 8
```

### 输出

```
4
```

## 样例 #2

### 输入

```
1 2 7
6 7
```

### 输出

```
-1
```

# AI分析结果

### 题目内容
# 企鹅波罗与矩阵

## 题目描述
小企鹅波罗有一个 $n×m$ 的矩阵，由整数组成。我们将矩阵的行从顶部到底部从 1 到 $n$ 进行编号，将列从左到右从 1 到 $m$ 进行编号。用 $a_{ij}$ 表示矩阵中第 $i$ 行与第 $j$ 列交叉处的元素。

在一次移动中，企鹅可以对某个矩阵元素加上或减去数字 $d$ 。求使所有矩阵元素相等所需的最少移动次数。如果无法实现该计划，请说明。

## 样例 #1
### 输入
```
2 2 2
2 4
6 8
```
### 输出
```
4
```

## 样例 #2
### 输入
```
1 2 7
6 7
```
### 输出
```
-1
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是先判断能否通过操作使矩阵元素相等，再计算最少操作次数。判断依据是所有元素对 $d$ 取模后余数需相同，否则无解。计算最少操作次数时，多数题解采用贪心策略，将矩阵元素排序后，以中间元素为基准，通过统计其他元素与基准元素差值的绝对值除以 $d$ 的累加和，得到最少操作次数。部分题解采用暴力枚举每个元素作为基准来计算操作次数，时间复杂度较高。对比来看，以排序后中间元素为基准的贪心算法更优，时间复杂度为 $\Theta(nm\log(nm))$，而暴力枚举的时间复杂度为 $\Theta((nm)^2)$。

### 所选的题解
- **作者：大宝和小宝 (赞：3)  星级：5星  关键亮点：思路清晰简洁，代码实现直接明了，先判断余数是否相同，再排序取中间值计算操作次数。**
```cpp
#include <iostream>
#include<algorithm>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
using namespace std;

int a[1000010];

int main()
{
    int sum,n,m,d,r,w,i;
    scanf("%d %d %d",&n,&m,&d);
    sum=n*m;
    scanf("%d",&a[0]);
    r=a[0]%d;
    for(i=1;i<sum;i++)
    {
        scanf("%d",&a[i]);
        if(a[i]%d!=r)
        {
            printf("-1\n");
            return 0;
        }
    }
    sort(a,a+sum);
    r=a[sum/2];
    w=0;
    for(i=0;i<sum;i++)
    {
        w+=abs(a[i]-r)/d;
    }
    printf("%d\n",w);
    return 0;
}
```
核心实现思想：先读入矩阵规模和 $d$，记录第一个元素的余数作为基准，遍历其他元素判断余数是否相同，若不同则输出 `-1` 并结束程序。然后对所有元素排序，取中间元素作为目标值，遍历计算每个元素与目标值差值的绝对值除以 $d$ 的累加和，即为最少操作次数。

- **作者：Cloud_Umbrella (赞：1)  星级：4星  关键亮点：对取模相等的原理进行了简单证明，代码简洁，同样采用排序取中间值计算操作次数。**
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[10010];//这里笔者比较懒，反正开一维也不影响
int n,m,d,mod;
int main(){
    scanf("%d%d%d",&n,&m,&d);
    cin>>a[1],mod=a[1]%d;
    for(int i=2;i<=n*m;i++){
        scanf("%d",a+i);//a+i相当于&a[i]
        if((a[i]%d)!=mod) return puts("-1"),0;//小技巧，相当于puts(-1);return 0;
    }
    sort(a+1,a+1+n*m);
    long long ans=0;
    for(int i=1;i<=n*m;i++)
        ans+=abs(a[i]-a[(n*m+1)/2])/d;//相对中间值
    printf("%lld",ans);
    return 0;//好习惯伴终生
}
```
核心实现思想：读入数据时记录第一个元素的模值，后续元素与之对比，若模值不同则输出 `-1` 。排序后以中间元素为目标值，计算各元素与目标值差值的绝对值除以 $d$ 的累加和得到最少操作次数。

- **作者：ztxtjz (赞：1)  星级：4星  关键亮点：对贪心选择中位数的原因进行了详细分析，包括中位数选择的分类讨论，思路清晰。**
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,d,ans,a[10005],mod[10005];
int main()
{
    scanf("%d%d%d",&n,&m,&d);
    for(int i=1;i<=n*m;i++)
    {
        scanf("%d",&a[i]);
        mod[i]=a[i]%d;
    }
    for(int i=2;i<=n*m;i++) if(mod[i]!=mod[i-1]){printf("-1");return 0;}  //无法通过加减d的操作使数字相同
    sort(a+1,a+n*m+1);
    for(int i=1;i<=n*m;i++) ans+=abs((a[i]-a[(n*m+1)/2])/d);
    printf("%d",ans);
    return 0;
}
```
核心实现思想：读入数据时记录每个元素的模值，遍历判断相邻元素模值是否相同，不同则输出 `-1` 。排序后以中间元素为目标值，累加各元素与目标值差值的绝对值除以 $d$ 的值得到最少操作次数。

### 最优关键思路或技巧
1. **贪心策略**：选择排序后矩阵元素的中位数作为目标值，能使所有元素变成相同值的操作次数最少。这是因为从数据分布角度看，以中间值为基准，两边元素到该值的距离之和相对较小。
2. **余数判断**：利用对 $d$ 取模余数相同这一特性判断是否有解，是解决该问题的关键前置条件。

### 可拓展之处
同类型题通常围绕对数组或矩阵元素进行特定操作，使所有元素达到某种统一状态并求最少操作次数。类似算法套路是先分析操作对元素性质的影响（如本题取模余数不变），以此判断可行性，再通过贪心策略找到最优目标值来计算最少操作次数。

### 推荐题目
1. **P1080 [NOIP2012 提高组] 国王游戏**：通过对数据进行排序，利用贪心策略解决问题，与本题选择中位数的贪心思路类似。
2. **P1199 [NOIP2010 普及组] 三国游戏**：需要分析游戏规则找到贪心策略，判断最优解，和本题判断可行性及寻找最优解的过程类似。
3. **P2859 [USACO06DEC] Milk Patterns G**：在处理序列数据时运用贪心思想，和本题对矩阵元素处理思路有相通之处。 

---
处理用时：67.51秒