# 题目信息

# Modified GCD

## 题目描述

Well, here is another math class task. In mathematics, GCD is the greatest common divisor, and it's an easy task to calculate the GCD between two positive integers.

A common divisor for two positive numbers is a number which both numbers are divisible by.

But your teacher wants to give you a harder task, in this task you have to find the greatest common divisor $ d $ between two integers $ a $ and $ b $ that is in a given range from $ low $ to $ high $ (inclusive), i.e. $ low<=d<=high $ . It is possible that there is no common divisor in the given range.

You will be given the two integers $ a $ and $ b $ , then $ n $ queries. Each query is a range from $ low $ to $ high $ and you have to answer each query.

## 样例 #1

### 输入

```
9 27
3
1 5
10 11
9 11
```

### 输出

```
3
-1
9
```

# AI分析结果

### 题目翻译
## 修改后的最大公约数

### 题目描述
这是另一道数学课堂任务。在数学中，GCD（最大公约数）是指能同时整除两个正整数的最大正整数，计算两个正整数的GCD是一项简单的任务。

两个正整数的公约数是指能同时整除这两个数的数。

但你的老师想给你一个更难的任务，在这个任务中，你必须找出两个整数 $a$ 和 $b$ 在给定范围 $[low, high]$（包含边界）内的最大公约数 $d$，即 $low \leq d \leq high$。有可能在给定范围内不存在公约数。

你将得到两个整数 $a$ 和 $b$，然后是 $n$ 个查询。每个查询是一个范围 $[low, high]$，你需要回答每个查询。

### 样例 #1
#### 输入
```
9 27
3
1 5
10 11
9 11
```
#### 输出
```
3
-1
9
```

### 综合分析与结论
这些题解的核心思路都是先找出 $a$ 和 $b$ 的所有公约数，再针对每个查询在这些公约数中找出符合范围的最大公约数。大部分题解利用了“$a$ 和 $b$ 的所有公约数都是 $\gcd(a,b)$ 的约数”这一性质，通过枚举 $\gcd(a,b)$ 的约数来获取 $a$ 和 $b$ 的所有公约数。

算法要点主要包括：
1. 计算 $\gcd(a,b)$。
2. 枚举 $\gcd(a,b)$ 的约数，时间复杂度为 $O(\sqrt{\gcd(a,b)})$。
3. 对约数进行排序，方便后续二分查找。
4. 对于每个查询，使用二分查找在约数中找出符合范围的最大公约数，时间复杂度为 $O(\log k)$，其中 $k$ 为约数的数量。

解决的难点在于如何高效地找出所有公约数并快速响应查询。不同题解的区别主要在于约数的存储方式、二分查找的实现方式以及边界条件的处理。

### 高评分题解
- **作者：ADay（5星）**
    - **关键亮点**：思路清晰，详细证明了“$a,b$ 任何一个公约数都能整除 $\gcd(a,b)$”这一性质，使用 `upper_bound` 函数进行二分查找，代码简洁易读。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;

int a,b,x,y,g;
vector<int>v;

int main()
{
    scanf("%d%d",&a,&b);
    g=__gcd(a,b);
    for(int i=1;i*i<=g;i++)if(g%i==0)v.push_back(i),v.push_back(g/i);
    scanf("%d",&a);
    sort(v.begin(),v.end());
    while(~scanf("%d%d",&x,&y))
    {
        int pos=upper_bound(v.begin(),v.end(),y)-v.begin();
        if(v[pos-1]<x)puts("-1");
        else printf("%d\n",v[pos-1]);
    }
    return 0;
}
```
核心实现思想：先计算 $\gcd(a,b)$，然后枚举其约数存入 `vector` 中，对 `vector` 排序后，使用 `upper_bound` 函数找到第一个大于查询范围上限的数的位置，判断其前一个数是否在查询范围内。

- **作者：李至擎（4星）**
    - **关键亮点**：思路明确，详细说明了解题步骤，同样使用 `upper_bound` 函数进行二分查找，代码规范。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,n,gcd,num[1000005];
int l,r,len;
int main()
{
    cin>>a>>b;
    gcd=__gcd(a,b);
    for(int i=1;i*i<=gcd;i++)
    {
        if(gcd%i==0)
        {
            num[++len]=i;
            if(gcd/i!=i)
            {
                num[++len]=gcd/i;
            }
        }
    }
    sort(num+1,num+len+1);
    cin>>n;
    while(n--)
    {
        cin>>l>>r; 
        int x=upper_bound(num+1,num+len+1,r)-num-1;
        if(num[x]>=l)cout<<num[x]<<endl;
        else cout<<-1<<endl;
    }
    return 0;
}
```
核心实现思想：计算 $\gcd(a,b)$ 后，枚举其约数存入数组，排序后使用 `upper_bound` 函数进行二分查找，根据结果输出答案。

### 最优关键思路或技巧
- 利用“$a$ 和 $b$ 的所有公约数都是 $\gcd(a,b)$ 的约数”这一性质，将问题转化为枚举 $\gcd(a,b)$ 的约数，减少了不必要的枚举。
- 使用二分查找在约数中找出符合范围的最大公约数，将查询的时间复杂度从 $O(k)$ 降低到 $O(\log k)$。

### 可拓展之处
同类型题或类似算法套路：
- 求多个数在指定范围内的最大公约数。可以先求出所有数的最大公约数，再按照同样的方法处理。
- 求两个数在指定范围内的最小公倍数。可以先求出两个数的最小公倍数，再枚举其约数进行处理。

### 推荐题目
1. [P1029 最大公约数和最小公倍数问题](https://www.luogu.com.cn/problem/P1029)
2. [P2152 SDOI2009 SuperGCD](https://www.luogu.com.cn/problem/P2152)
3. [P1516 青蛙的约会](https://www.luogu.com.cn/problem/P1516)

### 个人心得摘录与总结
- **作者：yzx72424**：一开始使用 `map` 记录所有到 $i$ 为止的最大约数，导致在第11个点超时。后来经大佬提示使用二分查找解决了问题。总结：在处理大量数据查询时，要考虑算法的时间复杂度，避免使用低效的算法。 

---
处理用时：32.34秒