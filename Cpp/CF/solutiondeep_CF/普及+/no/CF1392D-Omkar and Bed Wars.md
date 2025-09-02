# 题目信息

# Omkar and Bed Wars

## 题目描述

Omkar is playing his favorite pixelated video game, Bed Wars! In Bed Wars, there are $ n $ players arranged in a circle, so that for all $ j $ such that $ 2 \leq j \leq n $ , player $ j -       1 $ is to the left of the player $ j $ , and player $ j $ is to the right of player $ j - 1 $ . Additionally, player $ n $ is to the left of player $ 1 $ , and player $ 1 $ is to the right of player $ n $ .

Currently, each player is attacking either the player to their left or the player to their right. This means that each player is currently being attacked by either $ 0 $ , $ 1 $ , or $ 2 $ other players. A key element of Bed Wars strategy is that if a player is being attacked by exactly $ 1 $ other player, then they should logically attack that player in response. If instead a player is being attacked by $ 0 $ or $ 2 $ other players, then Bed Wars strategy says that the player can logically attack either of the adjacent players.

Unfortunately, it might be that some players in this game are not following Bed Wars strategy correctly. Omkar is aware of whom each player is currently attacking, and he can talk to any amount of the $ n $ players in the game to make them instead attack another player — i. e. if they are currently attacking the player to their left, Omkar can convince them to instead attack the player to their right; if they are currently attacking the player to their right, Omkar can convince them to instead attack the player to their left.

Omkar would like all players to be acting logically. Calculate the minimum amount of players that Omkar needs to talk to so that after all players he talked to (if any) have changed which player they are attacking, all players are acting logically according to Bed Wars strategy.

## 说明/提示

In the first test case, players $ 1 $ and $ 2 $ are attacking each other, and players $ 3 $ and $ 4 $ are attacking each other. Each player is being attacked by exactly $ 1 $ other player, and each player is attacking the player that is attacking them, so all players are already being logical according to Bed Wars strategy and Omkar does not need to talk to any of them, making the answer $ 0 $ .

In the second test case, not every player acts logically: for example, player $ 3 $ is attacked only by player $ 2 $ , but doesn't attack him in response. Omkar can talk to player $ 3 $ to convert the attack arrangement to LRLRRL, in which you can see that all players are being logical according to Bed Wars strategy, making the answer $ 1 $ .

## 样例 #1

### 输入

```
5
4
RLRL
6
LRRRRL
8
RLLRRRLL
12
LLLLRRLRRRLL
5
RRRRR```

### 输出

```
0
1
1
3
2```

# AI分析结果

### 题目翻译
# Omkar 和起床战争

## 题目描述
Omkar 正在玩他最喜欢的像素风电子游戏《起床战争》！在《起床战争》中，有 $n$ 名玩家围成一个圈，因此对于所有满足 $2 \leq j \leq n$ 的 $j$，玩家 $j - 1$ 在玩家 $j$ 的左边，玩家 $j$ 在玩家 $j - 1$ 的右边。此外，玩家 $n$ 在玩家 $1$ 的左边，玩家 $1$ 在玩家 $n$ 的右边。

目前，每个玩家要么攻击其左边的玩家，要么攻击其右边的玩家。这意味着每个玩家当前可能受到 $0$、$1$ 或 $2$ 名其他玩家的攻击。《起床战争》策略的一个关键要素是，如果一名玩家恰好受到另一名玩家的攻击，那么从逻辑上讲，该玩家应该反击攻击他的玩家。相反，如果一名玩家受到 $0$ 或 $2$ 名其他玩家的攻击，那么《起床战争》策略表明该玩家可以逻辑地攻击相邻的任何一名玩家。

不幸的是，这个游戏中可能有些玩家没有正确遵循《起床战争》策略。Omkar 知道每个玩家当前正在攻击谁，并且他可以与游戏中的任意数量的 $n$ 名玩家交谈，让他们转而攻击另一名玩家 —— 即如果他们当前正在攻击左边的玩家，Omkar 可以说服他们转而攻击右边的玩家；如果他们当前正在攻击右边的玩家，Omkar 可以说服他们转而攻击左边的玩家。

Omkar 希望所有玩家都能合乎逻辑地行动。计算 Omkar 至少需要与多少名玩家交谈，以便在所有他交谈过的玩家（如果有的话）改变他们攻击的玩家后，所有玩家都能根据《起床战争》策略合乎逻辑地行动。

## 说明/提示
在第一个测试用例中，玩家 $1$ 和 $2$ 互相攻击，玩家 $3$ 和 $4$ 互相攻击。每个玩家恰好受到另一名玩家的攻击，并且每个玩家都在攻击攻击他们的玩家，因此所有玩家已经根据《起床战争》策略合乎逻辑地行动了，Omkar 不需要与任何玩家交谈，答案为 $0$。

在第二个测试用例中，并非每个玩家的行为都是合乎逻辑的：例如，玩家 $3$ 仅受到玩家 $2$ 的攻击，但没有反击他。Omkar 可以与玩家 $3$ 交谈，将攻击安排转换为 LRLRRL，在这种情况下，你可以看到所有玩家都根据《起床战争》策略合乎逻辑地行动，答案为 $1$。

## 样例 #1

### 输入
```
5
4
RLRL
6
LRRRRL
8
RLLRRRLL
12
LLLLRRLRRRLL
5
RRRRR
```

### 输出
```
0
1
1
3
2
```

### 算法分类
本题的核心逻辑可以通过贪心或动态规划的方法解决，最相关的标签为**贪心**。

### 综合分析与结论
这些题解主要围绕如何计算让所有玩家合乎逻辑行动所需的最少交谈玩家数展开，主要有贪心和动态规划两种思路。
- **贪心思路**：核心在于发现不合法状态是存在连续三个相同攻击方向（LLL 或 RRR），将连续相同攻击方向的段合并统计长度，每段对答案的贡献为 $\lfloor \frac{len}{3} \rfloor$，同时要特判全是相同攻击方向的情况。
- **动态规划思路**：先找出合法的最小字符串（RL、RRL、RLL、RRLL），用 $dp[i]$ 表示前 $i$ 个字符最少需要改动的字符数量，由于是环，需旋转字符串多次做 DP。

### 高评分题解
- **作者：dead_X (赞：7)，4星**
    - **关键亮点**：思路清晰，先统计连续字符数量，破环为链并特判全相同的情况，然后根据每段长度计算答案，代码简洁易懂。
- **作者：fls233666 (赞：6)，4星**
    - **关键亮点**：详细分析了不合法状态，通过拆环为链统计连续段长度，对全相同情况的处理有图示说明，便于理解。
- **作者：Chinese_zjc_ (赞：9)，4星**
    - **关键亮点**：采用动态规划方法，明确指出合法环由四种字符串组成，对环的处理通过旋转字符串多次做 DP，思路严谨。

### 重点代码
#### dead_X 的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
char a[2000003];
int main()
{
    int T=read();
    while(T--)
    {
        int n=read(),ans=0;
        scanf("%s",a+1);
        for(int i=1; i<=n; i++) a[i+n]=a[i];
        bool f=1;
        char tmp=a[1];
        for(int i=2; i<=n; i++) if(a[i]!=tmp) f=0;
        if(f) 
        {
            printf("%d\n",(n-1)/3+1);
            continue;
        }
        int pos=0,now=0;
        for(int i=1; i<n; i++) if(a[i]!=a[n]) { pos=i-1; break; }
        for(int i=1; i<=n; i++) a[i]=a[i+pos];
        for(int i=1; i<=n; i++) 
        {
            if(a[i]!=a[i-1]) ans+=now/3,now=0;
            ++now;
        }
        ans+=now/3;
        printf("%d\n",ans);
    }
    return 0;
}
```
**核心实现思想**：先将字符串复制一份接在后面，判断是否全相同，若全相同则直接计算答案；否则找到第一个不同字符的位置，破环为链，统计连续字符长度，每段长度除以 3 累加到答案中。

#### fls233666 的代码
```cpp
#include<iostream>
#include<cstdio>
#define ll long long
#define rgt register int
using namespace std;

const int mxn = 2e5+5;
char rb[mxn<<1];
int n,cnt,ans;

inline void getrb(){
    char c=getchar();
    while(c!='L'&&c!='R')
        c=getchar();
    int tg=1;
    rb[tg+n]=rb[tg]=c;
    tg++;
    c=getchar();
    while(c=='L'||c=='R'){
        rb[n+tg]=rb[tg]=c;
        tg++;
        c=getchar();
    }
}  //快速读入字符串序列

int main(){
    int test,dt;
    scanf("%d",&test);
    while(test--){
        scanf("%d",&n);
        getrb();
        
        dt=1;
        while(dt<n){
            if(rb[dt+1]!=rb[dt])
                break;
            dt++;
        }  //找到 L 与 R 的第一个分界点
        
        cnt=1;
        ans=0;
        for(rgt i=dt+2;i<=dt+n;i++){
            if(rb[i]!=rb[i-1]){
                ans+=cnt/3;  //统计答案
                cnt=1; 
            }else
                cnt++;  //算连续段长度
        }
        ans+=cnt/3;
        
        if(dt==n&&cnt%3)  //特判全是 L 或全是 R的情况
            ans++;
        printf("%d\n",ans);
    }
    return 0;
}
```
**核心实现思想**：快速读入字符串并复制一份，找到 L 与 R 的第一个分界点，从该点开始统计连续段长度，每段长度除以 3 累加到答案中，特判全相同且长度不能被 3 整除的情况。

#### Chinese_zjc_ 的代码
```cpp
//This Code was made by Chinese_zjc_.
#include<iostream>
#include<string>
#define int long long
using namespace std;
int n,t,dp[200005],ans;
string s;
const string g[]={"RL","RRL","RLL","RRLL"};//貌似没用
int diff(string A,string B)
{
    int tmp=0;
    for(int i=0;i<(int)A.length();++i)
    {
        if(A[i]!=B[i])
        {
            ++tmp;
        }
    }
    return tmp;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin>>t;
    while(t--)
    {
        cin>>n>>s;
        s=' '+s;
        ans=INF;
        for(int l=1;l<=5;++l)
        {
            dp[0]=0;
            dp[1]=INF;
            for(int i=2;i<=n;++i)
            {
                dp[i]=dp[i-2]+diff("RL",s.substr(i-1,2));
                if(i>=3)
                {
                    dp[i]=min(dp[i],dp[i-3]+diff("RRL",s.substr(i-2,3)));
                    dp[i]=min(dp[i],dp[i-3]+diff("RLL",s.substr(i-2,3)));
                    if(i>=4)
                    {
                        dp[i]=min(dp[i],dp[i-4]+diff("RRLL",s.substr(i-3,4)));
                    }
                }
            }
            ans=min(ans,dp[n]);
            s=' '+s.substr(2,n-1)+s[1];
        }
        cout<<ans<<endl;
    }
    return 0;
}
```
**核心实现思想**：用 $dp[i]$ 表示前 $i$ 个字符最少需要改动的字符数量，通过比较当前子串与合法子串（RL、RRL、RLL、RRLL）的差异更新 $dp$ 值，由于是环，旋转字符串 5 次做 DP，取最小值作为答案。

### 关键思路与技巧
- **贪心思路**：通过观察不合法状态，将连续相同攻击方向的段合并处理，利用 $\lfloor \frac{len}{3} \rfloor$ 计算每段的贡献，同时注意特判全相同的情况。
- **动态规划思路**：找出合法的最小字符串，用 $dp$ 数组记录状态，对于环的处理，通过旋转字符串多次做 DP 来解决首尾问题。

### 拓展思路
同类型题可能会有不同的规则和条件，但核心思路可能类似，如其他环形字符串的修改问题，或者在不同规则下的策略优化问题。可以通过分析不合法状态，找出关键的子结构，然后采用贪心或动态规划的方法解决。

### 推荐题目
- [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：考察贪心算法，通过每次合并最小的两堆果子来使总代价最小。
- [P1216 [USACO1.5] 数字三角形 Number Triangles](https://www.luogu.com.cn/problem/P1216)：经典的动态规划问题，通过状态转移方程计算从顶部到底部的最大路径和。
- [P1616 疯狂的采药](https://www.luogu.com.cn/problem/P1616)：完全背包问题，属于动态规划的应用，求在一定时间内采到草药的最大价值。

### 个人心得摘录与总结
- **作者：pigstd**：提到自己在实现时犯了很多错误，说明在实现复杂的动态规划问题时，需要仔细考虑状态定义和状态转移方程，避免出错。

---
处理用时：84.11秒