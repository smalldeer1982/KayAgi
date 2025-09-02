# 题目信息

# Jerry's Protest

## 题目描述

Andrew and Jerry are playing a game with Harry as the scorekeeper. The game consists of three rounds. In each round, Andrew and Jerry draw randomly without replacement from a jar containing $ n $ balls, each labeled with a distinct positive integer. Without looking, they hand their balls to Harry, who awards the point to the player with the larger number and returns the balls to the jar. The winner of the game is the one who wins at least two of the three rounds.

Andrew wins rounds 1 and 2 while Jerry wins round 3, so Andrew wins the game. However, Jerry is unhappy with this system, claiming that he will often lose the match despite having the higher overall total. What is the probability that the sum of the three balls Jerry drew is strictly higher than the sum of the three balls Andrew drew?

## 说明/提示

In the first case, there are only two balls. In the first two rounds, Andrew must have drawn the $ 2 $ and Jerry must have drawn the $ 1 $ , and vice versa in the final round. Thus, Andrew's sum is $ 5 $ and Jerry's sum is $ 4 $ , so Jerry never has a higher total.

In the second case, each game could've had three outcomes — $ 10-2 $ , $ 10-1 $ , or $ 2-1 $ . Jerry has a higher total if and only if Andrew won $ 2-1 $ in both of the first two rounds, and Jerry drew the $ 10 $ in the last round. This has probability ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF626D/278aa205373ddbc5533818ea01281d6e5a703b92.png).

## 样例 #1

### 输入

```
2
1 2
```

### 输出

```
0.0000000000
```

## 样例 #2

### 输入

```
3
1 2 10
```

### 输出

```
0.0740740741
```

# AI分析结果

### 题目内容
# Jerry的抗议

## 题目描述
安德鲁（Andrew）和杰瑞（Jerry）在玩一个游戏，哈利（Harry）担任计分员。游戏共分为三个回合。在每个回合中，安德鲁和杰瑞从一个装有\(n\)个球的罐子中无放回地随机抽取球，每个球都标有一个不同的正整数。他们在不看球的情况下，将球交给哈利，哈利把这一回合的分数判给抽到较大数字球的玩家，然后将球放回罐子。游戏的获胜者是赢得至少两个回合的人。

安德鲁赢得了第1回合和第2回合，杰瑞赢得了第3回合，所以安德鲁赢得了游戏。然而，杰瑞对这个结果不满意，他声称尽管他抽到球上数字的总和更高，但他却经常输掉比赛。那么杰瑞抽到的三个球的总和严格大于安德鲁抽到的三个球的总和的概率是多少？

## 说明/提示
在第一种情况下，只有两个球。在前两个回合中，安德鲁一定抽到了\(2\)，杰瑞一定抽到了\(1\)，而在最后一回合情况相反。因此，安德鲁的总和是\(5\)，杰瑞的总和是\(4\)，所以杰瑞的总和永远不会更高。

在第二种情况下，每个回合可能有三种结果 —— \(10 - 2\)，\(10 - 1\)，或\(2 - 1\)。杰瑞的总和更高，当且仅当安德鲁在前两个回合都赢了\(2 - 1\)，并且杰瑞在最后一回合抽到了\(10\)。这种情况的概率为（此处应是图片内容对应的概率计算，因无具体公式，暂无法明确）。

## 样例 #1
### 输入
```
2
1 2
```
### 输出
```
0.0000000000
```

## 样例 #2
### 输入
```
3
1 2 10
```
### 输出
```
0.0740740741
```

### 算法分类
概率论

### 综合分析与结论
这三道题解都围绕计算杰瑞抽到球总和大于安德鲁抽到球总和的概率展开，核心思路均是通过分析条件转化为对差值的处理，并利用动态规划或类似递推的方式来统计概率。
1. **思路方面**：都先明确需要满足的条件，即前两回合安德鲁球值大于杰瑞，且三回合球值总和杰瑞大于安德鲁，转化为对差值的不等式关系处理。
2. **算法要点**：通过枚举球的差值情况，利用数组记录不同差值出现的概率或次数，并通过循环嵌套实现状态转移。
3. **解决难点**：难点在于如何合理地定义状态和转移方程，准确统计各种差值组合出现的概率。三位作者都通过定义数组来记录差值相关信息，通过双重循环枚举差值组合实现转移。

### 所选的题解
- **作者：Mav11Young (5星)**
    - **关键亮点**：思路清晰，定义明确的dp数组来表示不同阶段的差值概率，前缀和数组的使用简化了最终答案的计算，代码简洁明了，注释清晰。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
#define debug(a) cout<<#a<<"="<<a<<endl;
#define LL long long
using namespace std;
const int N=2005;
int a[N];
double dp[5][10005],f[10005];
int main(){
    int n,mx=-1e9,mi=1e9;
    scanf("%d",&n);
    double tmp=1.0/(1ll*n*(n-1)/2);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]),mx=max(mx,a[i]),mi=min(mi,a[i]);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(a[i]>a[j])dp[1][a[i]-a[j]]+=tmp,dp[2][a[i]-a[j]]+=tmp;
    for(int i=1;i<=mx-mi;i++)
        for(int j=1;j<=mx-mi;j++)dp[3][i+j]+=dp[1][i]*dp[2][j];
    for(int i=1;i<=2*(mx-mi);i++)f[i]=f[i-1]+dp[3][i];
    double ans=0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(a[j]>a[i])ans+=f[a[j]-a[i]-1]*tmp;
    printf("%.10lf",ans);
    return 0;
}
```
    - **核心实现思想**：先初始化总概率tmp，通过两重循环计算前两轮A、B差值概率dp[1]、dp[2]，再通过两重循环得到前两轮A、B差值和的概率dp[3]，利用前缀和数组f记录dp[3]前缀和，最后通过两重循环枚举第三轮A、B的球，结合前缀和数组计算最终答案。
- **作者：IGA_Indigo (4星)**
    - **关键亮点**：对题目条件的化简清晰，状态设置直观，通过注释详细解释了每一步操作，便于理解。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[2005];
long double f[5][5005];
int main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    sort(a+1,a+1+n);
    int fm=0;
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            if(a[j]>a[i]){
                f[1][a[j]-a[i]]++;
                fm++;
            }
        }
    }
    for(int i=1;i<=5000;i++){
        f[1][i]/=fm;
    }
    for(int i=1;i<=5000;i++){
        for(int j=1;i+j<=5000;j++){
            f[2][i+j]+=f[1][i]*f[1][j];
        }
    }
    long double ans=0;
    for(int i=1;i<=5000;i++){
        for(int j=i+1;j<=5000;j++){
            ans+=f[2][i]*f[1][j];
        }
    }
    cout<<setprecision(10)<<ans;
    return 0;
}
```
    - **核心实现思想**：先对球上数字排序，通过两重循环统计差值出现次数并计算概率存于f[1]，再通过两重循环实现状态转移得到f[2]，最后通过两重循环计算满足条件的概率作为答案。
- **作者：EnochWenzhou (4星)**
    - **关键亮点**：同样对条件化简准确，代码简洁，通过cnt记录分母相关信息，逻辑连贯。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[5010],cnt;
double f[2][5050],ans;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    sort(a+1,a+1+n);
    for(int i=1;i<n;i++)for(int j=i+1;j<=n;j++)
        if(a[i]<a[j])f[0][a[j]-a[i]]++,cnt++;
    for(int i=1;i<=5003;i++)f[0][i]/=cnt;
    for(int i=1;i<=5003;i++)for(int j=1;i+j<=5003;j++)f[1][i+j]+=f[0][i]*f[0][j];
    for(int i=1;i<5003;i++)for(int j=i+1;j<=5003;j++)ans+=f[1][i]*f[0][j];
    printf("%.10lf",ans);
    return 0;
}
```
    - **核心实现思想**：先排序，通过两重循环统计差值出现次数cnt并计算概率存于f[0]，通过两重循环实现状态转移得到f[1]，最后通过两重循环计算满足条件的概率作为答案。

### 最优关键思路或技巧
1. **状态定义与转移**：通过定义数组记录不同差值出现的概率，利用两重循环枚举差值组合实现状态转移，有效解决了复杂概率计算问题。
2. **前缀和优化**：如Mav11Young题解中利用前缀和数组记录前两轮差值和的概率，简化了最终答案的计算过程。

### 可拓展之处
同类型题或类似算法套路：此类问题可拓展到更多回合、不同获胜条件的概率计算问题。类似套路是将复杂的条件转化为可枚举的状态，利用数组记录状态信息，通过循环嵌套实现状态转移。

### 洛谷相似题目
1. P1288 取数游戏II：涉及概率计算与状态转移思想。
2. P3232 [HNOI2013]游走：同样是基于概率的计算问题，与本题在概率分析上有相似之处。
3. P4316 绿豆蛙的归宿：通过拓扑排序结合概率计算，与本题在处理概率问题的思路上有一定相似性。 

---
处理用时：73.40秒