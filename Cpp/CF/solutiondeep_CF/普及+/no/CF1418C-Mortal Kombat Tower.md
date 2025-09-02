# 题目信息

# Mortal Kombat Tower

## 题目描述

You and your friend are playing the game Mortal Kombat XI. You are trying to pass a challenge tower. There are $ n $ bosses in this tower, numbered from $ 1 $ to $ n $ . The type of the $ i $ -th boss is $ a_i $ . If the $ i $ -th boss is easy then its type is $ a_i = 0 $ , otherwise this boss is hard and its type is $ a_i = 1 $ .

During one session, either you or your friend can kill one or two bosses (neither you nor your friend can skip the session, so the minimum number of bosses killed during one session is at least one). After your friend session, your session begins, then again your friend session begins, your session begins, and so on. The first session is your friend's session.

Your friend needs to get good because he can't actually kill hard bosses. To kill them, he uses skip points. One skip point can be used to kill one hard boss.

Your task is to find the minimum number of skip points your friend needs to use so you and your friend kill all $ n $ bosses in the given order.

For example: suppose $ n = 8 $ , $ a = [1, 0, 1, 1, 0, 1, 1, 1] $ . Then the best course of action is the following:

- your friend kills two first bosses, using one skip point for the first boss;
- you kill the third and the fourth bosses;
- your friend kills the fifth boss;
- you kill the sixth and the seventh bosses;
- your friend kills the last boss, using one skip point, so the tower is completed using two skip points.

You have to answer $ t $ independent test cases.

## 样例 #1

### 输入

```
6
8
1 0 1 1 0 1 1 1
5
1 1 1 1 0
7
1 1 1 1 0 0 1
6
1 1 1 1 1 1
1
1
1
0```

### 输出

```
2
2
2
2
1
0```

# AI分析结果

### 题目翻译
## 真人快打塔

### 题目描述
你和你的朋友正在玩游戏《真人快打 11》。你们正在尝试通关一个挑战塔。这个塔中有 $n$ 个首领，编号从 $1$ 到 $n$。第 $i$ 个首领的类型是 $a_i$。如果第 $i$ 个首领是简单首领，那么它的类型 $a_i = 0$，否则这个首领是困难首领，它的类型 $a_i = 1$。

在一轮游戏中，你或者你的朋友可以击杀一个或两个首领（你和你的朋友都不能跳过这一轮，所以一轮中击杀首领的最少数量是一个）。在你朋友的回合之后，轮到你回合，然后又是你朋友的回合，接着又是你的回合，依此类推。第一轮是你朋友的回合。

你的任务是找出你的朋友为了和你按给定顺序击杀所有 $n$ 个首领所需使用的最少跳过点数。

例如：假设 $n = 8$，$a = [1, 0, 1, 1, 0, 1, 1, 1]$。那么最佳的行动方案如下：
- 你的朋友击杀前两个首领，为第一个首领使用一个跳过点数；
- 你击杀第三个和第四个首领；
- 你的朋友击杀第五个首领；
- 你击杀第六个和第七个首领；
- 你的朋友击杀最后一个首领，使用一个跳过点数，所以通关该塔共使用两个跳过点数。

你需要回答 $t$ 个独立的测试用例。

### 样例 #1
#### 输入
```
6
8
1 0 1 1 0 1 1 1
5
1 1 1 1 0
7
1 1 1 1 0 0 1
6
1 1 1 1 1 1
1
1
1
0
```

#### 输出
```
2
2
2
2
1
0
```

### 算法分类
动态规划、贪心

### 综合分析与结论
这些题解主要围绕动态规划和贪心两种思路来解决问题。动态规划的思路核心在于状态设计与状态转移方程的构建，通过记录不同状态下的最优解，逐步递推得到最终结果；贪心算法则是基于对问题的分析，找到一种局部最优的策略，从而得到全局最优解。

### 所选题解
- **TerryGong（5星）**
    - **关键亮点**：提供了动态规划和贪心两种解法，思路清晰，对动态规划的状态设计、转移方程以及贪心策略的分析都很详细，代码注释也较为丰富。
    - **个人心得**：提到自己一开始不会动态规划，在老师讲解后又发现了贪心解法，体现了探索问题的过程。
- **KSToki（4星）**
    - **关键亮点**：贪心思路简洁明了，代码实现简单，直接抓住了问题的关键，即让自己取更多的困难首领，以减少朋友使用的跳过点数。
- **Tenshi（4星）**
    - **关键亮点**：动态规划思路规范，对状态的定义和转移方程的推导清晰，并且强调了初始化的重要性，代码实现规范。

### 重点代码
#### TerryGong 动态规划代码
```cpp
#include <cstdio>
#include <cstring>
using namespace std;
#define N 200010
int f[N][2],w[N];
inline bool isdigit(char x){return (x>='0'&&x<='9');}
inline int read(){
    int x=0,flag=1;char c=getchar();
    while(!isdigit(c)){if(c=='-')flag=-1;c=getchar();}
    while(isdigit(c)){x=(x<<3)+(x<<1)+c-'0';c=getchar();}
    return flag*x;
}
inline int gmin(int x,int y){return x<y?x:y;}
int main(){
    int T;
    T=read();
    while(T--){
        memset(f,0x3f,sizeof f);int n=read();
        for(int i=1;i<=n;i++)w[i]=read();        
        f[0][0]=0;f[1][1]=w[1];
        for(int i=2;i<=n;i++)
            for(int j=0;j<=1;j++)
                f[i][j]=gmin(f[i-1][!j]+j*w[i],f[i-2][!j]+j*(w[i]+w[i-1]));
        printf("%d\n",gmin(f[n][1],f[n][0]));
    }
    return 0;
}
```
**核心实现思想**：定义状态 $f[i][0/1]$ 表示怪物打完第 $i$ 个，轮到你打是 $0$（后手），轮到朋友打是 $1$（先手）时的最优解。根据不同的回合情况，通过状态转移方程递推得到最终结果。

#### TerryGong 贪心代码
```cpp
#include <cstdio>
using namespace std;
int T,n,a,ans;
inline bool isdigit(char x){return (x>='0'&&x<='9');}
inline int read(){
    int x=0,flag=1;char c=getchar();
    while(!isdigit(c)){if(c=='-')flag=-1;c=getchar();}
    while(isdigit(c)){x=(x<<3)+(x<<1)+c-'0';c=getchar();}
    return flag*x;
}
int main(){
    T=read();
    while(T--){
        n=read();ans=read();int cnt=0;
        for(int i=1;i<n;++i){
            a=read();
            if(a==1)++cnt;
            else{
                ans+=cnt/3;
                cnt=0;
            }
        }
        printf("%d\n",ans+cnt/3);
    }
    return 0;
}
```
**核心实现思想**：为了让朋友尽量少花费跳过点数，遇到困难首领尽量让自己打。统计连续困难首领的个数，每三个连续困难首领可以让朋友少用一个跳过点数。

### 关键思路或技巧
- **动态规划**：合理设计状态，通过状态转移方程递推求解。状态设计要考虑当前处理的首领位置和当前回合是谁在打。
- **贪心**：分析问题的特点，找到一种局部最优的策略，即让自己多打困难首领，朋友少打困难首领。

### 拓展思路
同类型题可能会有不同的游戏规则或限制条件，但解题思路仍然可以围绕动态规划和贪心展开。例如，改变首领的类型数量、增加新的操作限制等。类似的算法套路包括在其他轮流操作的游戏中，通过动态规划记录不同状态下的最优解，或者通过贪心策略找到局部最优的行动方案。

### 推荐题目
- [P1048 采药](https://www.luogu.com.cn/problem/P1048)：经典的 0 - 1 背包问题，可使用动态规划求解。
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：贪心算法的经典应用，通过排序找到最优的排队顺序。
- [P1002 过河卒](https://www.luogu.com.cn/problem/P1002)：动态规划问题，通过状态转移方程计算从起点到终点的路径数量。

### 个人心得总结
- TerryGong 提到自己一开始不会动态规划，在老师讲解后又发现了贪心解法，说明遇到问题时可以从不同角度思考，尝试多种方法。
- Fa1thful 分享了自己在初始化和转移方程细节上的调试经历，提醒我们在实现动态规划时要注意边界条件和细节处理。 

---
处理用时：52.63秒