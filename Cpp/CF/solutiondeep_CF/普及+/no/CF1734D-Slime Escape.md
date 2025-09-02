# 题目信息

# Slime Escape

## 题目描述

You are playing a game called Slime Escape. The game takes place on a number line. Initially, there are $ n $ slimes. For all positive integers $ i $ where $ 1 \le i \le n $ , the $ i $ -th slime is located at position $ i $ and has health $ a_i $ . You are controlling the slime at position $ k $ .

There are two escapes located at positions $ 0 $ and $ n+1 $ . Your goal is to reach any one of the two escapes by performing any number of game moves.

In one game move, you move your slime to the left or right by one position. However, if there is another slime in the new position, you must absorb it. When absorbing a slime, the health of your slime would be increased by the health of the absorbed slime, then the absorbed slime would be removed from the game.

Note that some slimes might have negative health, so your health would decrease when absorbing such slimes.

You lose the game immediately if your slime has negative health at any moment during the game.

Can you reach one of two escapes by performing any number of game moves, without ever losing the game?

## 说明/提示

In the first test case, you control the slime at position $ 4 $ with health $ 6 $ . One way to escape is to absorb the slimes at positions $ 5 $ , $ 6 $ , and $ 7 $ . Your slime escapes with $ 0 $ health at position $ 8 $ .

In the second test case, you control the slime with $ 232 $ health at position $ 1 $ . Since your slime is already located next to the escape at position $ 0 $ , you can move to it without absorbing any slime.

In the third test case, it can be shown that your slime would always have a negative health before reaching any one of two escapes.

In the fourth test case, you control the slime at position $ 4 $ with health $ 6 $ . The following describes a possible sequence of moves to win:

1. Absorb the slimes at positions $ 5 $ , $ 6 $ , and $ 7 $ : your health becomes $ 4 $ after absorbing the slime with health $ -2 $ ; becomes $ 1 $ after absorbing the slime with health $ -3 $ ; and becomes $ 7 $ after absorbing the slime with health $ 6 $ .
2. Absorb the slimes at positions $ 3 $ , and $ 2 $ : your health becomes $ 7-7+10=10 $ .
3. Absorb the slime at position $ 8 $ : your health becomes $ 10-10=0 $ .
4. Use the escape at position $ 9 $ .

Since your slime has maintained non-negative health at all times, you have won.

## 样例 #1

### 输入

```
6
7 4
-1 -2 -3 6 -2 -3 -1
3 1
232 -500 -700
7 4
-1 -2 -4 6 -2 -4 -1
8 4
-100 10 -7 6 -2 -3 6 -10
8 2
-999 0 -2 3 4 5 6 7
7 3
7 3 3 4 2 1 1```

### 输出

```
YES
YES
NO
YES
NO
YES```

# AI分析结果

### 题目中文重写
# 史莱姆逃脱

## 题目描述
你正在玩一款名为“史莱姆逃脱”的游戏。游戏在一个数轴上进行。初始时，有 $n$ 个史莱姆。对于所有满足 $1 \le i \le n$ 的正整数 $i$，第 $i$ 个史莱姆位于位置 $i$，且生命值为 $a_i$。你控制着位于位置 $k$ 的史莱姆。

在位置 $0$ 和 $n + 1$ 处各有一个出口。你的目标是通过执行任意数量的游戏移动，到达这两个出口中的任意一个。

在一次游戏移动中，你可以将你的史莱姆向左或向右移动一个位置。然而，如果新位置上有另一个史莱姆，你必须吸收它。吸收史莱姆时，你的史莱姆的生命值将增加被吸收史莱姆的生命值，然后被吸收的史莱姆将从游戏中移除。

请注意，有些史莱姆的生命值可能为负，因此吸收此类史莱姆时，你的生命值会减少。

如果在游戏过程中的任何时刻，你的史莱姆的生命值为负，你将立即输掉游戏。

你能否通过执行任意数量的游戏移动，在不输掉游戏的情况下到达两个出口中的任意一个？

## 说明/提示
在第一个测试用例中，你控制着位于位置 $4$、生命值为 $6$ 的史莱姆。一种逃脱方法是吸收位置 $5$、$6$ 和 $7$ 处的史莱姆。你的史莱姆以 $0$ 生命值在位置 $8$ 逃脱。

在第二个测试用例中，你控制着位于位置 $1$、生命值为 $232$ 的史莱姆。由于你的史莱姆已经位于靠近位置 $0$ 的出口旁边，你可以在不吸收任何史莱姆的情况下移动到该出口。

在第三个测试用例中，可以证明你的史莱姆在到达两个出口中的任何一个之前，生命值总是会变为负。

在第四个测试用例中，你控制着位于位置 $4$、生命值为 $6$ 的史莱姆。以下是一个可能的获胜移动序列：
1. 吸收位置 $5$、$6$ 和 $7$ 处的史莱姆：吸收生命值为 $ - 2$ 的史莱姆后，你的生命值变为 $4$；吸收生命值为 $ - 3$ 的史莱姆后，变为 $1$；吸收生命值为 $6$ 的史莱姆后，变为 $7$。
2. 吸收位置 $3$ 和 $2$ 处的史莱姆：你的生命值变为 $7 - 7 + 10 = 10$。
3. 吸收位置 $8$ 处的史莱姆：你的生命值变为 $10 - 10 = 0$。
4. 使用位置 $9$ 处的出口。

由于你的史莱姆在所有时刻都保持非负生命值，你获胜了。

## 样例 #1
### 输入
```
6
7 4
-1 -2 -3 6 -2 -3 -1
3 1
232 -500 -700
7 4
-1 -2 -4 6 -2 -4 -1
8 4
-100 10 -7 6 -2 -3 6 -10
8 2
-999 0 -2 3 4 5 6 7
7 3
7 3 3 4 2 1 1
```
### 输出
```
YES
YES
NO
YES
NO
YES
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是贪心算法，即每次都选择能让史莱姆生命值尽可能增加的方向移动。具体实现上，大部分题解使用双指针分别维护向左和向右能走到的位置，通过记录过程中的最大生命值来决定是否转向。

不同题解的差异主要在于细节处理和代码实现方式。部分题解使用前缀和来辅助计算，方便判断能否继续向某个方向移动；还有题解将生命值为正的区间进行合并，减少不必要的计算。

### 所选题解
- **VinstaG173（5星）**
    - **关键亮点**：思路清晰，详细阐述了贪心策略的原理，通过双指针模拟史莱姆的移动过程，时间复杂度为 $O(n)$，代码简洁高效。
- **jockbutt（4星）**
    - **关键亮点**：同样采用双指针方法，同时计算左右两边的前缀和，更新最大体积，代码结构清晰，易于理解。
- **xujingyu（4星）**
    - **关键亮点**：对贪心策略的解释通俗易懂，先枚举向右走的情况，再向左走，逻辑明确，代码实现简洁。

### 重点代码
#### VinstaG173
```cpp
#include<cstdio>
#define rg register
#define ll long long
int n,k,p;ll v,s,m;
ll a[2000003];
int t;int main(){
    scanf(" %d",&t);while(t--){
        scanf(" %d %d",&n,&k);
        for(rg int i=1;i<=n;++i)scanf(" %lld",&a[i]);
        v=a[k];if(a[k]<0){puts("NO");continue;}
        int l=k-1,r=k+1;while(l&&r<=n){
            ll pv=v;
            s=m=0;p=r-1;for(;r<=n;++r){
                s+=a[r];if(s>m)m=s,p=r;
                if(s<-v)break;
            }if(r<=n)v+=m,r=p+1;
            else break;
            s=m=0;p=l+1;for(;l;--l){
                s+=a[l];if(s>m)m=s,p=l;
                if(s<-v)break;
            }if(l)v+=m,l=p-1;
            else break;
            if(v==pv)break;
        }if(l&&r<=n)puts("NO");
        else puts("YES");
    }return 0;
}
```
**核心实现思想**：使用双指针 `l` 和 `r` 分别表示向左和向右能走到的位置，每次先向右走，记录过程中的最大生命值 `m`，若遇到生命值为负则转向向左走，同样记录最大生命值，若生命值无法增加则停止，最后判断是否能到达出口。

#### jockbutt
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1e6+10;
int a[maxn],tot,ans;
int s[maxn];
inline void solve()
{
    int n,k;
    n=read(),k=read(),ans=tot=0;
    for(int i=1;i<=n;++i) a[i]=read();
    if(a[k]<0) NO
    s[k-1]=a[k-1],s[k+1]=a[k+1],s[k]=0;
    for(int i=k-2;i>0;--i) s[i]=s[i+1]+a[i];
    for(int i=k+2;i<=n;++i) s[i]=s[i-1]+a[i];
    int l=k-1,r=k+1,s1=a[k],s2=a[k],ll,rr;
    for(;l>0&&r<=n;)
    {
        ll=l,rr=r;
        while(s[l]+s2>=0&&l>0) s1=max(s1,a[k]+s[l]),l--;
        while(s[r]+s1>=0&&r<=n) s2=max(s2,a[k]+s[r]),r++;
        if(ll==l&&rr==r) NO
    }
    YES
}
```
**核心实现思想**：先计算左右两边的前缀和，然后使用双指针 `l` 和 `r` 分别向左和向右扩展，同时更新最大体积 `s1` 和 `s2`，若无法扩展则输出 `NO`，否则输出 `YES`。

#### xujingyu
```cpp
#include <stdio.h>
#include <queue>
#include <iostream>
#define int long long
using namespace std;

int t,n,k,p,ak,a[2000002],l,r;

signed main()
{
    scanf("%lld",&t);
    while(t--)
    {
        scanf("%lld%lld",&n,&k);
        for(int i = 1;i <= n;i++) scanf("%lld",&a[i]);
        
        ak = a[k];//记录血量
        
        l = k - 1;
        r = k + 1;
        
        int sum,most;//当前血量与最大血量
        while(l && r <= n)
        {
            int ak1 = ak;
            sum = 0;
            most = 0;
            p = r - 1;
            for(;r <= n;r++)//一直向右走
            {
                sum += a[r];
                if(sum > most)
                {
                    most = sum;//保存最大血量
                    p = r;
                }
                if(sum < -ak) break;
            }
            if(r <= n)//没能过去
            {
                ak += most;
                r = p + 1;
            }
            else break;
            sum = most = 0;
            p = l + 1;
            for(;l;l--)//再不停向左走
            {
                sum += a[l];
                if(sum > most)
                {
                    most = sum;
                    p = l;
                }
                if(sum < -ak) break;
            }
            if(l)
            {
                ak += most;
                l = p - 1;
            }
            else break;
            if(ak == ak1) break;
        }
        
        if(l && r <= n)//还是没出去
        {
            printf("NO\n");
            continue;
        }
        else printf("YES\n");
    }
    return 0;
}
```
**核心实现思想**：先向右走，记录过程中的最大生命值，若遇到生命值为负则转向向左走，同样记录最大生命值，若生命值无法增加则停止，最后判断是否能到达出口。

### 最优关键思路或技巧
- **贪心策略**：每次选择能让史莱姆生命值尽可能增加的方向移动，避免走入生命值为负的区域。
- **双指针**：使用双指针分别维护向左和向右能走到的位置，方便模拟史莱姆的移动过程。
- **前缀和**：部分题解使用前缀和来辅助计算，方便判断能否继续向某个方向移动。

### 可拓展之处
同类型题可能会增加更多的限制条件，如增加障碍物、不同类型的史莱姆等。类似的算法套路可以应用于其他需要在路径上进行选择的问题，如迷宫问题、寻宝问题等。

### 推荐洛谷题目
- P1208 [USACO1.3] 混合牛奶 Mixing Milk
- P1094 纪念品分组
- P2240 【深基12.例1】部分背包问题

---
处理用时：71.76秒