# 题目信息

# Chunga-Changa

## 题目描述

Soon after the Chunga-Changa island was discovered, it started to acquire some forms of civilization and even market economy. A new currency arose, colloquially called "chizhik". One has to pay in chizhiks to buy a coconut now.

Sasha and Masha are about to buy some coconuts which are sold at price $ z $ chizhiks per coconut. Sasha has $ x $ chizhiks, Masha has $ y $ chizhiks. Each girl will buy as many coconuts as she can using only her money. This way each girl will buy an integer non-negative number of coconuts.

The girls discussed their plans and found that the total number of coconuts they buy can increase (or decrease) if one of them gives several chizhiks to the other girl. The chizhiks can't be split in parts, so the girls can only exchange with integer number of chizhiks.

Consider the following example. Suppose Sasha has $ 5 $ chizhiks, Masha has $ 4 $ chizhiks, and the price for one coconut be $ 3 $ chizhiks. If the girls don't exchange with chizhiks, they will buy $ 1 + 1 = 2 $ coconuts. However, if, for example, Masha gives Sasha one chizhik, then Sasha will have $ 6 $ chizhiks, Masha will have $ 3 $ chizhiks, and the girls will buy $ 2 + 1 = 3 $ coconuts.

It is not that easy to live on the island now, so Sasha and Mash want to exchange with chizhiks in such a way that they will buy the maximum possible number of coconuts. Nobody wants to have a debt, so among all possible ways to buy the maximum possible number of coconuts find such a way that minimizes the number of chizhiks one girl gives to the other (it is not important who will be the person giving the chizhiks).

## 说明/提示

The first example is described in the statement. In the second example the optimal solution is to dot exchange any chizhiks. The girls will buy $ 3 + 4 = 7 $ coconuts.

## 样例 #1

### 输入

```
5 4 3
```

### 输出

```
3 1
```

## 样例 #2

### 输入

```
6 8 2
```

### 输出

```
7 0
```

# AI分析结果

### 题目内容重写

#### 题目描述

在Chunga-Changa岛被发现后，岛上逐渐形成了文明和市场经济。一种新的货币出现了，俗称“chizhik”。现在购买椰子需要用chizhik支付。

Sasha和Masha准备购买一些椰子，椰子的价格为$z$ chizhik。Sasha有$x$ chizhik，Masha有$y$ chizhik。每个女孩只能用自己的钱购买尽可能多的椰子，因此每个女孩将购买一个非负整数的椰子。

女孩们讨论了她们的计划，发现如果她们中的一个给另一个一些chizhik，她们购买的椰子总数可能会增加（或减少）。chizhik不能被分割，因此她们只能交换整数数量的chizhik。

考虑以下例子。假设Sasha有$5$ chizhik，Masha有$4$ chizhik，椰子的价格为$3$ chizhik。如果她们不交换chizhik，她们将购买$1 + 1 = 2$个椰子。然而，如果Masha给Sasha一个chizhik，那么Sasha将有$6$ chizhik，Masha将有$3$ chizhik，她们将购买$2 + 1 = 3$个椰子。

现在岛上生活不易，因此Sasha和Masha希望以某种方式交换chizhik，使她们购买的椰子数量最大化。没有人愿意欠债，因此在所有可能的购买最多椰子的方式中，找到一种使一个女孩给另一个女孩的chizhik数量最少的方式（谁给谁不重要）。

#### 说明/提示

第一个例子在题目描述中已经给出。在第二个例子中，最优解是不交换任何chizhik。女孩们将购买$3 + 4 = 7$个椰子。

#### 样例 #1

##### 输入

```
5 4 3
```

##### 输出

```
3 1
```

#### 样例 #2

##### 输入

```
6 8 2
```

##### 输出

```
7 0
```

### 算法分类
贪心

### 题解分析与结论

这道题的核心在于如何通过交换chizhik来最大化购买的椰子数量，并且在达到最大数量的前提下，最小化交换的chizhik数量。题解中大多数采用了贪心算法，通过计算两人剩余的钱数来判断是否需要交换，以及交换的最小数量。

### 所选高分题解

#### 题解1：作者：αnonymous (赞：2)

**星级：4星**

**关键亮点：**
- 简洁明了地解释了贪心算法的核心思想。
- 通过计算余数来判断是否需要交换，并选择最小交换数量。

**核心代码：**
```cpp
#include <iostream>
using namespace std;
long long x,y,z,mini;
int main(){
    long long a,b,c;
    cin>>x>>y>>z;
    a=x%z;//余数计算
    b=y%z;
    if(a+b>=z)//和必须要能再买一个,否则在做无用功
        if(a>b)//使移动个数最少
            mini=z-a;
        else
            mini=z-b;
    cout<<(x+y)/z<<" "<<mini;
    return 0;
}
```

#### 题解2：作者：_cmh (赞：1)

**星级：4星**

**关键亮点：**
- 代码简洁，逻辑清晰。
- 通过取余和判断条件来输出最小交换数量。

**核心代码：**
```cpp
#include<bits/stdc++.h>
#define ll long long 
using namespace std;
int main(){
    ll x,y,z;
    scanf("%lld%lld%lld",&x,&y,&z);
    printf("%lld ",(x+y)/z);
    x%=z;y%=z;
    printf("%lld",x+y>=z?((x>y)?z-x:z-y):0);
    return 0;
}
```

#### 题解3：作者：Firstly (赞：0)

**星级：4星**

**关键亮点：**
- 思路清晰，代码简洁。
- 通过比较两人剩余的钱数来选择最小交换数量。

**核心代码：**
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
long long x,y,z;
int main(){
    cin>>x>>y>>z;
    cout<<(x+y)/z<<' ';
    long long xx=x%z,yy=y%z;
    if(xx+yy>=z)cout<<min(z-xx,z-yy);
    else cout<<0;
    return 0;
}
```

### 最优关键思路或技巧

1. **贪心算法**：通过计算两人剩余的钱数来判断是否需要交换，并选择最小交换数量。
2. **余数计算**：通过取余操作快速判断两人剩余的钱数是否足够再购买一个椰子。
3. **最小化交换**：在满足条件的情况下，选择交换数量最小的方案。

### 可拓展之处

类似的问题可以扩展到多个人的情况，或者不同的货币单位。贪心算法在这种最大化或最小化问题中非常有效。

### 推荐题目

1. [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
3. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)

### 个人心得摘录

- **αnonymous**：通过余数计算来判断是否需要交换，并选择最小交换数量，思路清晰。
- **_cmh**：代码简洁，逻辑清晰，通过取余和判断条件来输出最小交换数量。
- **Firstly**：思路清晰，代码简洁，通过比较两人剩余的钱数来选择最小交换数量。

---
处理用时：40.49秒