# 题目信息

# Alyona and Numbers

## 题目描述

After finishing eating her bun, Alyona came up with two integers $ n $ and $ m $ . She decided to write down two columns of integers — the first column containing integers from $ 1 $ to $ n $ and the second containing integers from $ 1 $ to $ m $ . Now the girl wants to count how many pairs of integers she can choose, one from the first column and the other from the second column, such that their sum is divisible by $ 5 $ .

Formally, Alyona wants to count the number of pairs of integers $ (x,y) $ such that $ 1<=x<=n $ , $ 1<=y<=m $ and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF682A/bb850c8c10ee7a9c00e5b1ff3da7605a7415f98c.png) equals $ 0 $ .

As usual, Alyona has some troubles and asks you to help.

## 说明/提示

Following pairs are suitable in the first sample case:

- for $ x=1 $ fits $ y $ equal to $ 4 $ or $ 9 $ ;
- for $ x=2 $ fits $ y $ equal to $ 3 $ or $ 8 $ ;
- for $ x=3 $ fits $ y $ equal to $ 2 $ , $ 7 $ or $ 12 $ ;
- for $ x=4 $ fits $ y $ equal to $ 1 $ , $ 6 $ or $ 11 $ ;
- for $ x=5 $ fits $ y $ equal to $ 5 $ or $ 10 $ ;
- for $ x=6 $ fits $ y $ equal to $ 4 $ or $ 9 $ .

Only the pair $ (1,4) $ is suitable in the third sample case.

## 样例 #1

### 输入

```
6 12
```

### 输出

```
14
```

## 样例 #2

### 输入

```
11 14
```

### 输出

```
31
```

## 样例 #3

### 输入

```
1 5
```

### 输出

```
1
```

## 样例 #4

### 输入

```
3 8
```

### 输出

```
5
```

## 样例 #5

### 输入

```
5 7
```

### 输出

```
7
```

## 样例 #6

### 输入

```
21 21
```

### 输出

```
88
```

# AI分析结果

### 题目翻译
# Alyona 和数字

## 题目描述
吃完面包后，Alyona 想出了两个整数 $n$ 和 $m$。她决定写下两列整数——第一列包含从 $1$ 到 $n$ 的整数，第二列包含从 $1$ 到 $m$ 的整数。现在，女孩想计算她可以选择多少对整数，其中一个来自第一列，另一个来自第二列，使得它们的和能被 $5$ 整除。

形式上，Alyona 想计算整数对 $(x, y)$ 的数量，使得 $1\leq x\leq n$，$1\leq y\leq m$ 且 $(x + y) \bmod 5$ 等于 $0$。

像往常一样，Alyona 遇到了一些困难，于是向你求助。

## 说明/提示
在第一个样例中，以下数对是合适的：
- 当 $x = 1$ 时，$y$ 可以是 $4$ 或 $9$；
- 当 $x = 2$ 时，$y$ 可以是 $3$ 或 $8$；
- 当 $x = 3$ 时，$y$ 可以是 $2$、$7$ 或 $12$；
- 当 $x = 4$ 时，$y$ 可以是 $1$、$6$ 或 $11$；
- 当 $x = 5$ 时，$y$ 可以是 $5$ 或 $10$；
- 当 $x = 6$ 时，$y$ 可以是 $4$ 或 $9$。

在第三个样例中，只有数对 $(1, 4)$ 是合适的。

## 样例 #1
### 输入
```
6 12
```
### 输出
```
14
```

## 样例 #2
### 输入
```
11 14
```
### 输出
```
31
```

## 样例 #3
### 输入
```
1 5
```
### 输出
```
1
```

## 样例 #4
### 输入
```
3 8
```
### 输出
```
5
```

## 样例 #5
### 输入
```
5 7
```
### 输出
```
7
```

## 样例 #6
### 输入
```
21 21
```
### 输出
```
88
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是利用数论中余数的性质来解决问题。由于要使两数之和能被 $5$ 整除，那么这两个数除以 $5$ 的余数之和也应能被 $5$ 整除，余数组合只有 $(0, 0)$、$(1, 4)$、$(2, 3)$、$(3, 2)$、$(4, 1)$ 这几种情况。各题解的区别主要在于统计余数个数的方式和代码实现细节。

### 所选题解
- **kbzcz（4星）**
    - **关键亮点**：思路清晰，利用同余定理将问题转化为统计余数个数并相乘求和，代码简洁易懂。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long sum1[6],sum2[6];
int main(){
    long long n,m;
    cin>>n>>m;
    for(int i=0;i<5;i++)
    {
        sum1[i]=n/5;
        sum2[i]=m/5;
        if(i!=0&&n%5>=i)
        {
            sum1[i]++;
        }
        if(i!=0&&m%5>=i)
        {
            sum2[i]++;
        }
    }
    long long ans=sum1[0]*sum2[0];
    for(int i=1;i<5;i++)
    {
        ans=ans+sum1[i]*sum2[5-i];
    }
    cout<<ans;
    return 0;
} 
```
    - **核心实现思想**：先分别计算 $1$ 到 $n$ 和 $1$ 到 $m$ 中除以 $5$ 余 $0$ 到 $4$ 的数的个数，存储在 `sum1` 和 `sum2` 数组中。然后根据余数组合的情况，将对应余数个数相乘并累加得到最终结果。

- **一只大龙猫（4星）**
    - **关键亮点**：详细分析了计算余数个数的情况，时间复杂度为 $O(1)$，且常数小。
    - **核心代码**：
```cpp
#include<iostream>
using namespace std;
long long n,m,sum1[5],sum2[5],ans;
int main(){
    cin>>n>>m;
    if(n%5==0){
        for(long long i=0;i<5;i++){
            sum1[i]=n/5;
        }
    }else{
        sum1[0]=n/5;
        for(long long i=1;i<5;i++){
            sum1[i]=n/5;
            if(i%5<=n%5)sum1[i]++;
        }
    }
    if(m%5==0){
        for(long long i=0;i<5;i++){
            sum2[i]=m/5;
        }
    }else{
        sum2[0]=m/5;
        for(long long i=1;i<5;i++){
            sum2[i]=m/5;
            if(i%5<=m%5)sum2[i]++;
        }
    }
    for(long long i=0;i<5;i++){
        ans+=sum1[i]*sum2[(5-i)%5];
    }
    cout<<ans;
    return 0;
}
```
    - **核心实现思想**：根据 $n$ 和 $m$ 是否为 $5$ 的倍数，分情况计算 $1$ 到 $n$ 和 $1$ 到 $m$ 中除以 $5$ 余 $0$ 到 $4$ 的数的个数，存储在 `sum1` 和 `sum2` 数组中。最后将对应余数个数相乘并累加得到最终结果。

- **Sternenlicht（4星）**
    - **关键亮点**：思路清晰，利用同余性质枚举统计余数个数，代码结构清晰。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
#define LL long long
#define endl '\n'
#define lowbit(x) (x&-x)
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)
#define INF 0x3f3f3f3f
namespace IO{
    inline LL read(){
        LL x=0,f=1;char ch=getchar();
        for (;!isdigit(ch);ch=getchar())if (ch=='-')f=-1;
        for (;isdigit(ch);ch=getchar())x=(x<<3)+(x<<1)+(ch^48);
        return x*f;
    }
    inline void write(LL x,char c='\n'){
        if (x){
            if (x<0)x=-x,putchar('-');
            char a[30];short l;
            for (l=0;x;x/=10)a[l++]=x%10^48;
            for (l--;l>=0;l--)putchar(a[l]);
        }
        else putchar('0');putchar(c);
    }
    inline char getc(){
        char ch=getchar();
        while (isspace(ch))ch=getchar();
        return ch;
    }
}
using namespace IO;
using namespace std;

LL yu0n,yu1n,yu2n,yu3n,yu4n;
LL yu0m,yu1m,yu2m,yu3m,yu4m;
int n,m;
int main(){
    n=read(),m=read();
    for (int i=1;i<=n;i++)
        if (i%5==0)yu0n++;
        else if (i%5==1)yu1n++;
        else if (i%5==2)yu2n++;
        else if (i%5==3)yu3n++;
        else yu4n++;
    for (int i=1;i<=m;i++)
        if (i%5==0)yu0m++;
        else if (i%5==1)yu1m++;
        else if (i%5==2)yu2m++;
        else if (i%5==3)yu3m++;
        else yu4m++;
    write(yu0n*yu0m+yu1n*yu4m+yu2n*yu3m+yu3n*yu2m+yu4n*yu1m);
    return 0;
}
```
    - **核心实现思想**：通过枚举 $1$ 到 $n$ 和 $1$ 到 $m$ 的数，分别统计除以 $5$ 余 $0$ 到 $4$ 的数的个数。最后将对应余数个数相乘并累加得到最终结果。

### 最优关键思路或技巧
利用余数的可加性，将问题转化为统计 $1$ 到 $n$ 和 $1$ 到 $m$ 中除以 $5$ 余 $0$ 到 $4$ 的数的个数，然后根据余数组合情况进行乘法和加法运算。

### 拓展思路
同类型题可以是求两数之和能被其他数整除的对数，或者是多个数之和能被某数整除的组合数等，都可以利用余数的性质进行求解。

### 推荐题目
1. [P1424 小鱼的航程（改进版）](https://www.luogu.com.cn/problem/P1424)
2. [P1088 火星人](https://www.luogu.com.cn/problem/P1088)
3. [P1046 陶陶摘苹果](https://www.luogu.com.cn/problem/P1046)

### 个人心得摘录与总结
- **ViXpop**：做这道题时，一开始以为是暴力题，看到数据范围后发现是数论题，通过观察样例找到规律。为了便于理解，选择仅对第一个周期进行预处理，然后重复所有完整周期，最后对多余的不完整周期进行单独计算。总结：遇到问题要先分析数据范围，寻找规律，对于复杂问题可以分步骤处理。
- **JustinXiaoJunyang**：强调了余数的可加性在本题中的应用，同时提醒要开 `long long` 防止溢出。总结：要掌握余数的相关定律，并且在处理可能出现大数的情况时，注意数据类型的选择。

---
处理用时：58.94秒