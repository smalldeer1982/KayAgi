# Casinos and travel

## 题目描述

John has just bought a new car and is planning a journey around the country. Country has $ N $ cities, some of which are connected by bidirectional roads. There are $ N-1 $ roads and every city is reachable from any other city. Cities are labeled from $ 1 $ to $ N $ .

John first has to select from which city he will start his journey. After that, he spends one day in a city and then travels to a randomly choosen city which is directly connected to his current one and which he has not yet visited. He does this until he can't continue obeying these rules.

To select the starting city, he calls his friend Jack for advice. Jack is also starting a big casino business and wants to open casinos in some of the cities (max $ 1 $ per city, maybe nowhere). Jack knows John well and he knows that if he visits a city with a casino, he will gamble exactly once before continuing his journey.

He also knows that if John enters a casino in a good mood, he will leave it in a bad mood and vice versa. Since he is John's friend, he wants him to be in a good mood at the moment when he finishes his journey. John is in a good mood before starting the journey.

In how many ways can Jack select a starting city for John and cities where he will build casinos such that no matter how John travels, he will be in a good mood at the end? Print answer modulo $ 10^{9}+7 $ .

## 说明/提示

Example 1: If Jack selects city 1 as John's starting city, he can either build 0 casinos, so John will be happy all the time, or build a casino in both cities, so John would visit a casino in city 1, become unhappy, then go to city 2, visit a casino there and become happy and his journey ends there because he can't go back to city 1. If Jack selects city 2 for start, everything is symmetrical, so the answer is 4.

Example 2: If Jack tells John to start from city 1, he can either build casinos in 0 or 2 cities (total 4 possibilities). If he tells him to start from city 2, then John's journey will either contain cities 2 and 1 or 2 and 3. Therefore, Jack will either have to build no casinos, or build them in all three cities. With other options, he risks John ending his journey unhappy. Starting from 3 is symmetric to starting from 1, so in total we have $ 4+2+4=10 $ options.

## 样例 #1

### 输入

```
2
1 2
```

### 输出

```
4
```

## 样例 #2

### 输入

```
3
1 2
2 3
```

### 输出

```
10
```

# 题解

## 作者：kevin2006 (赞：3)

这是一道分类讨论+数论好题

把题目抽象一下：
每个点随机一个$0/1$的权值，随机选择一个点作为根，有多少种方案使得根节点到所有叶节点路径上的异或和为$0$。

发现叶节点到根的路径的权值异或和可以由叶节点确定。记叶节点数为$tot$。
1.若所选的根节点不是叶节点，那么除叶节点外的$n−tot$个点的权值可以随便选，方案数为

$$(n-tot)\times 2^{n−tot}$$

2.若所选的根节点是叶节点，那么除其他$n−tot−1$个叶节点外的所有的点权值可以随便选，方案数为
$$tot\times 2^{n−tot+1}$$

$ans=(n−tot)\times 2n−tot+tot\times 2n−tot+1=(n+tot)\times 2n−tot$

快速幂直接切掉
```plain
#include<cstdio>
const int mod=1e9+7;
const int N=1e5+7;
int n,tot;
int in[N];
int read()
{
    int x=0;
    char ch=getchar();
    while(ch<'0' || ch>'9')ch=getchar();
    while(ch>='0' && ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x;
}
long long quick_mod(long long b,int p)
{
    long long s=1;
    for (;p;p>>=1,b=b*b%mod)
        if (p&1) s=s*b%mod;
    return s;
}
int main()
{
    n=read();
    for(int i=1;i<n;i++)
        in[read()]++,in[read()]++;
    for(int i=1;i<=n;i++)
        if (in[i]==1) tot++;
    printf("%d\n",(n+tot)*quick_mod(2,n-tot)%mod);
    return 0;
}
```

---

