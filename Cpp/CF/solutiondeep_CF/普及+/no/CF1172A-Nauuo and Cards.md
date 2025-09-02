# 题目信息

# Nauuo and Cards

## 题目描述

Nauuo is a girl who loves playing cards.

One day she was playing cards but found that the cards were mixed with some empty ones.

There are $ n $ cards numbered from $ 1 $ to $ n $ , and they were mixed with another $ n $ empty cards. She piled up the $ 2n $ cards and drew $ n $ of them. The $ n $ cards in Nauuo's hands are given. The remaining $ n $ cards in the pile are also given in the order from top to bottom.

In one operation she can choose a card in her hands and play it — put it at the bottom of the pile, then draw the top card from the pile.

Nauuo wants to make the $ n $ numbered cards piled up in increasing order (the $ i $ -th card in the pile from top to bottom is the card $ i $ ) as quickly as possible. Can you tell her the minimum number of operations?

## 说明/提示

Example 1

We can play the card $ 2 $ and draw the card $ 3 $ in the first operation. After that, we have $ [0,3,0] $ in hands and the cards in the pile are $ [0,1,2] $ from top to bottom.

Then, we play the card $ 3 $ in the second operation. The cards in the pile are $ [1,2,3] $ , in which the cards are piled up in increasing order.

Example 2

Play an empty card and draw the card $ 1 $ , then play $ 1 $ , $ 2 $ , $ 3 $ in order.

## 样例 #1

### 输入

```
3
0 2 0
3 0 1
```

### 输出

```
2```

## 样例 #2

### 输入

```
3
0 2 0
1 0 3
```

### 输出

```
4```

## 样例 #3

### 输入

```
11
0 0 0 5 0 0 0 4 0 0 11
9 2 6 0 8 1 7 0 3 0 10
```

### 输出

```
18```

# AI分析结果

### 题目翻译
Nauuo 是一个喜欢玩牌的女孩。

有一天，她在玩牌时发现牌里混进了一些空白牌。

有 $n$ 张编号从 $1$ 到 $n$ 的牌，它们和另外 $n$ 张空白牌混在了一起。她把这 $2n$ 张牌堆起来，然后抽了 $n$ 张。Nauuo 手中的 $n$ 张牌已给出。牌堆中剩下的 $n$ 张牌也按照从上到下的顺序给出。

在一次操作中，她可以选择手中的一张牌打出——把它放到牌堆的底部，然后从牌堆顶部抽一张牌。

Nauuo 想尽快让这 $n$ 张编号的牌按升序堆叠（牌堆中从上到下的第 $i$ 张牌是编号为 $i$ 的牌）。你能告诉她最少需要多少次操作吗？

### 算法分类
贪心

### 题解分析与结论
本题的核心是给定两摞牌（共 $2n$ 张，其中 $n$ 张编号为 $1$ 到 $n$，$n$ 张空白牌），通过特定操作（从手中选牌放入牌堆底部，再从牌堆顶部抽牌），使牌堆中的牌按编号升序排列，求最少操作次数。

各题解思路、算法要点及难点对比：
- **VenusM1nT**：考虑使用 $0$ 牌和不使用 $0$ 牌两种情况。不使用 $0$ 牌时，次数为第一个 $pos[i]≥i$ 的 $pos[i]-i$；使用 $0$ 牌时，操作次数是 $\max(pos[i]-i+n+1)$。
- **include13_fAKe**：先确定最后 $n$ 步必然是按顺序放入编号牌，排除特殊情况（牌堆中部分编号牌已按序排列且后续可顺利操作），对于其他情况，先将一些牌堆里的牌放入手中，计算至少放多少张，最后按序放牌。
- **Fading**：分两种情况讨论。第一种是手上的牌可以直接按序打出成为 $1$ 到 $n$；第二种是非第一种情况，找到 $1$ 收入手中，然后按序打出所有牌，通过枚举确定合适的收牌时机。
- **ouuan**：先尝试不打空白牌能否完成，若能则为最优解，否则最优解是先打若干空白牌然后再也不打空白牌，答案为 $\max\limits_{i = 1}^n(p_i - i + 1 + n)$。
- **Day_Tao**：分为两种情况。第一种是牌堆中最后已有 $1$ 到 $m$ 的序列，可能直接完成；第二种是其他情况，需将 $1$ 号牌拿到手中，再按序打出所有牌，通过判断能否一次性打出确定操作次数。
- **zrzluck99**：将操作次数分为 $\le n$ 与 $> n$ 两种情况讨论。$\le n$ 时需满足一定条件（$1$ 以后的数字已排好且 $1$ 之前的数字能保证每次取到下一张），$> n$ 时进行队列模拟。
- **Frozencode**：使用二分思路，二分打多少张空牌后打出 $1$，先检验不打空牌的情况，通过模拟判断答案的可行性。
- **StudyingFather**：分两种情况考虑。若不用抽出牌堆中的每张牌，最小操作数为牌堆每张牌上的数字和它的目标位置差值的最大值；否则，计算每张牌被抽出和放到对应位置的时间和的最大值，通过判断编号为 $1$ 的牌的情况确定当前局面对应哪种情况。

### 评分较高的题解
- **VenusM1nT**：4星。亮点在于思路清晰，直接通过两种情况的计算得出结果，代码简洁明了，使用了宏定义和寄存器变量提高效率。
- **ouuan**：4星。思路简洁，先尝试不打空白牌的情况，再计算打空白牌的最优解，代码实现较为精炼。
- **Fading**：4星。对问题进行了详细的分析，给出了多个结论，分情况讨论的思路清晰，代码逻辑严谨。

### 关键思路与技巧
- **分情况讨论**：大部分题解都采用了分情况讨论的方法，将问题分为不使用空白牌和使用空白牌两种情况，分别计算操作次数，最后取最优解。
- **贪心策略**：在使用空白牌的情况下，通过贪心的思想，找到合适的收牌和出牌时机，使操作次数最少。
- **模拟与判断**：通过模拟操作过程，判断是否满足特定条件，如能否一次性打出所有编号牌，牌堆中的牌是否按序排列等。

### 可拓展之处
同类型题可能会改变牌的数量、操作规则或目标状态，解题思路仍然可以采用分情况讨论和贪心的策略。类似算法套路包括在一些游戏或操作问题中，通过分析不同情况，找到最优的操作方案。

### 推荐洛谷题目
- P1223 排队接水：通过贪心策略确定排队顺序，使总等待时间最短。
- P1090 合并果子：使用贪心算法，每次合并最小的两堆果子，使总代价最小。
- P2240 部分背包问题：采用贪心策略，选择单位价值最高的物品，使背包内物品总价值最大。

### 个人心得摘录与总结
- **include13_fAKe**：老师布置了很多题，要求不看题解，自己独立做出本题用了近 $2$ 个小时，感慨若参加比赛时间可能只够做这一题，意识到自己还需提高。总结：独立思考有助于提高解题能力，但也需不断积累经验，提高解题速度。
- **zrzluck99**：这道 CF #div.2 的第三题调了一个多小时，比赛时还是没调出来，佩服秒过的大佬。总结：比赛中遇到难题调试时间过长可能影响整体发挥，平时应多练习，提高调试和解题能力。

### 重点代码及核心实现思想
#### VenusM1nT
```cpp
#include<bits/stdc++.h>
#define MAXN 200005
#define inf 1919810
#define reg register
#define inl inline
using namespace std;
int n,a[MAXN],b[MAXN],pos[MAXN],ans,Ans=inf;
int main()
{
    scanf("%d",&n);
    for(reg int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(reg int i=1;i<=n;i++)
    {
        scanf("%d",&b[i]);
        pos[b[i]]=i;
    }
    for(reg int i=1;i<=n;i++) ans=max(ans,pos[i]-i+n+1);
    for(reg int i=1;i<=n;i++)
    {
        if(pos[i]>=i)
        {
            Ans=pos[i]-i;
            break;
        }
    }
    for(reg int i=1;i<=n;i++)
    {
        if((pos[i]<i && Ans<pos[i]-i+n+1) || (pos[i]>=i && Ans!=pos[i]-i))
        {
            Ans=inf;
            break;
        }
    }
    printf("%d\n",Ans==inf?ans:Ans);
    return 0;
}
```
核心思想：先记录每张牌的初始位置，分别计算使用 $0$ 牌和不使用 $0$ 牌的操作次数，最后取最优解。

#### ouuan
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 200010;

int n, a[N], b[N], p[N], ans;

int main()
{
    int i, j;

    scanf("%d", &n);

    for (i = 1; i <= n; ++i)
    {
        scanf("%d", a + i);
        p[a[i]] = 0;
    }

    for (i = 1; i <= n; ++i)
    {
        scanf("%d", b + i);
        p[b[i]] = i;
    }

    if (p[1])
    {
        for (i = 2; p[i] == p[1] + i - 1; ++i);
        if (p[i - 1] == n)
        {
            for (j = i; j <= n && p[j] <= j - i; ++j);
            if (j > n)
            {
                printf("%d", n - i + 1);
                return 0;
            }
        }
    }

    for (i = 1; i <= n; ++i) ans = max(ans, p[i] - i + 1 + n);

    printf("%d", ans);

    return 0;
}
```
核心思想：先尝试不打空白牌能否完成，若能则直接输出结果，否则计算打空白牌的最优解。

#### Fading
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ljc 998244353
using namespace std;
#ifdef Fading
#define gc getchar
#endif
#ifndef Fading
inline char gc(){
    static char now[1<<16],*S,*T;
    if (T==S){T=(S=now)+fread(now,1,1<<16,stdin);if (T==S) return EOF;}
    return *S++;
}
#endif
inline ll read(){
    register ll x=0,f=1;char ch=gc();
    while (!isdigit(ch)){if(ch=='-')f=-1;ch=gc();}
    while (isdigit(ch)){x=(x<<3)+(x<<1)+ch-'0';ch=gc();}
    return (f==1)?x:-x;
}
ll tot,x,n,m,pos[1000001],b[1000001];
signed main(){
    n=read();
    for (int i=1;i<=n;i++) x=read();
    for (int i=1;i<=n;i++){
        b[i]=read();
        if (b[i]) pos[b[i]]=i;
    }
    bool flag=(pos[1]?0:1);
    int now=n-pos[1]+1;
    for (int i=1;i<=pos[1]-1;i++){
        if (flag) break;
        if (b[i]&&b[i]-(i+now)<=0) flag=1;
    }
    for (int i=pos[1]+1;i<=n;i++){
        if (flag) break;
        if (b[i]!=i-pos[1]+1) flag=1;
    }
    if (!flag){//第一种
        cout<<n-now;return 0;
    }
    int dep1=0;//找到1的步数
    if (!pos[1]) dep1=pos[1];
    for (int i=1;i<=n;i++) b[i]=b[i+dep1];
    int dep2=0;//再收几次牌后打出1
    for (int i=1;i<=n;i++){
        if (b[i]&&b[i]<i+1) dep2=max(1LL*dep2,i-b[i]+1);
    }
    cout<<n+dep1+dep2;
    return 0;
}
```
核心思想：分两种情况讨论，第一种情况判断手上的牌能否直接按序打出，若能则直接输出结果；第二种情况找到 $1$ 并确定合适的收牌时机，最后输出操作次数。

---
处理用时：80.22秒