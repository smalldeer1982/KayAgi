# 题目信息

# Cola

## 题目描述

To celebrate the opening of the Winter Computer School the organizers decided to buy in $ n $ liters of cola. However, an unexpected difficulty occurred in the shop: it turned out that cola is sold in bottles $ 0.5 $ , $ 1 $ and $ 2 $ liters in volume. At that, there are exactly $ a $ bottles $ 0.5 $ in volume, $ b $ one-liter bottles and $ c $ of two-liter ones. The organizers have enough money to buy any amount of cola. What did cause the heated arguments was how many bottles of every kind to buy, as this question is pivotal for the distribution of cola among the participants (and organizers as well).

Thus, while the organizers are having the argument, discussing different variants of buying cola, the Winter School can't start. Your task is to count the number of all the possible ways to buy exactly $ n $ liters of cola and persuade the organizers that this number is too large, and if they keep on arguing, then the Winter Computer School will have to be organized in summer.

All the bottles of cola are considered indistinguishable, i.e. two variants of buying are different from each other only if they differ in the number of bottles of at least one kind.

## 样例 #1

### 输入

```
10 5 5 5
```

### 输出

```
9
```

## 样例 #2

### 输入

```
3 0 0 2
```

### 输出

```
0
```

# AI分析结果

### 题目内容
# 可乐

## 题目描述
为庆祝冬季计算机学校开学，组织者决定购买$n$升可乐。然而，商店里出现了一个意想不到的难题：可乐以$0.5$升、$1$升和$2$升的瓶子出售。其中，$0.5$升的瓶子正好有$a$个，$1$升的瓶子有$b$个，$2$升的瓶子有$c$个。组织者有足够的钱购买任意数量的可乐。引发激烈争论的是每种瓶子各买多少，因为这个问题对于参与者（以及组织者）之间的可乐分配至关重要。

因此，当组织者争论不休，讨论购买可乐的不同方案时，冬季学校无法开课。你的任务是计算恰好购买$n$升可乐的所有可能方式的数量，并说服组织者这个数量太大了，如果他们继续争论下去，那么冬季计算机学校将不得不改在夏季举办。

所有可乐瓶都被认为是无差别的，即两种购买方案仅当至少一种瓶子的数量不同时才被认为是不同的。

## 样例 #1
### 输入
```
10 5 5 5
```
### 输出
```
9
```

## 样例 #2
### 输入
```
3 0 0 2
```
### 输出
```
0
```

### 算法分类
枚举

### 综合分析与结论
这些题解的核心思路都是通过枚举不同容量可乐瓶的购买数量来计算方案数。主要区别在于枚举的顺序和方式，以及对$0.5$升可乐瓶数量的处理。大部分题解选择先枚举较大容量的瓶子（$2$升和$1$升），然后根据前两者的数量推算$0.5$升可乐瓶的数量，这样可以减少循环次数，优化时间复杂度。部分题解还对边界条件进行了细致处理，以确保方案的可行性。

### 所选的题解
- **作者：SUNCHAOYI (5星)**
    - **关键亮点**：思路清晰，先从容积较大的$2$升可乐瓶开始循环，合理确定循环次数，优化了枚举效率，代码简洁明了。
    - **核心代码**：
```cpp
#include <iostream>
using namespace std;
int main()
{
    int n,a,b,c,ans = 0;
    cin>>n>>a>>b>>c;
    for(int i = 0;i <= min(n / 2,c);i++)//最大的数量 
        for(int j = 0;j <= min(n,b);j++)
            if((n - i * 2 - j)  * 2 <= a && n - i * 2 - j >= 0) ans++;//符合条件 
    cout<<ans<<endl; 
    return 0;
}
```
    - **核心思想**：先枚举$2$升可乐瓶的数量$i$，再枚举$1$升可乐瓶的数量$j$，根据$n - i * 2 - j$计算出$0.5$升可乐瓶所需数量，判断其是否在合理范围内，若合理则方案数加一。

- **作者：灵光一闪 (4星)**
    - **关键亮点**：代码简短，通过巧妙的枚举方式，从$0.5$升可乐瓶（$a$）和$2$升可乐瓶（$c$）入手，利用$n$是整数的特点，$a$以$2$个为单位递增，简化了枚举过程。
    - **核心代码**：
```cpp
int main()
{
    int n,a,b,c;
    cin>>n>>a>>b>>c;
    int ans=0;
    for(int i=0;i<=a;i+=2)
        for(int j=0;j<=c;j++)
            if(n-(i/2+j*2)<=b&&n-(i/2+j*2)>=0)
                ans++;
    cout<<ans;
    return 0;
}
```
    - **核心思想**：以$2$个$0.5$升为一组枚举$a$的数量，同时枚举$2$升可乐瓶$c$的数量，计算出$1$升可乐瓶所需数量，判断是否在合理范围，合理则方案数加一。

- **作者：happybob (4星)**
    - **关键亮点**：采用快读和宏定义优化代码效率，同样先枚举$2$升和$1$升可乐瓶数量，逻辑清晰，代码简洁。
    - **核心代码**：
```cpp
#include <cstdio>

inline int read()//快读
{
    int x = 0;
    char ch = getchar();
    while(ch >= '0' && ch <= '9')
    {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    return x;
}

#define min(x, y) (x < y? x : y)//宏定义

int main()
{
    int n, a, b, c, ans = 0;
    n = read();
    a = read();
    b = read();
    c = read();
    for(register int i = 0; i <= min(n / 2, c); i++)
    {
        for(register int j = 0; j <= min(n, b); j++)
        {
            if((n - i * 2 - j) * 2 <= a && n - i * 2 - j >= 0)
            {
                ans++;
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}
```
    - **核心思想**：通过快读获取输入，先枚举$2$升可乐瓶数量$i$，再枚举$1$升可乐瓶数量$j$，判断剩余量对$0.5$升可乐瓶的需求是否合理，合理则方案数加一。

### 最优思路或技巧
1. **优化枚举顺序**：优先枚举大容量瓶子（$2$升和$1$升），减少循环次数，降低时间复杂度。
2. **利用整数特性**：由于总升数$n$为整数，对$0.5$升可乐瓶的枚举可以进行优化，如以$2$个为一组枚举，或根据前两种瓶子数量推算其数量。

### 拓展
此类题目属于组合计数类枚举问题，类似套路是先确定枚举对象和顺序，优先枚举对结果影响较大的变量，同时利用题目给定的条件（如整数限制）简化枚举过程。

### 洛谷相似题目
1. **P1164 小A点菜**：给定金额和不同价格菜品的数量，求点菜的方案数，与本题类似，通过枚举菜品数量来计算方案。
2. **P1469 找筷子**：给定一些整数，其中只有一个数出现奇数次，其他数都出现偶数次，通过位运算等方式找出这个数，与本题同样涉及对数据的遍历和判断。
3. **P1909 买铅笔**：根据不同包装铅笔的价格和数量，以及所需铅笔总数，求最小花费，同样是通过枚举不同包装组合来解决问题。 

---
处理用时：71.13秒