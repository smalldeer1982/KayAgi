# 题目信息

# Penalty

## 题目描述

Consider a simplified penalty phase at the end of a football match.

A penalty phase consists of at most $ 10 $ kicks, the first team takes the first kick, the second team takes the second kick, then the first team takes the third kick, and so on. The team that scores more goals wins; if both teams score the same number of goals, the game results in a tie (note that it goes against the usual football rules). The penalty phase is stopped if one team has scored more goals than the other team could reach with all of its remaining kicks. For example, if after the $ 7 $ -th kick the first team has scored $ 1 $ goal, and the second team has scored $ 3 $ goals, the penalty phase ends — the first team cannot reach $ 3 $ goals.

You know which player will be taking each kick, so you have your predictions for each of the $ 10 $ kicks. These predictions are represented by a string $ s $ consisting of $ 10 $ characters. Each character can either be 1, 0, or ?. This string represents your predictions in the following way:

- if $ s_i $ is 1, then the $ i $ -th kick will definitely score a goal;
- if $ s_i $ is 0, then the $ i $ -th kick definitely won't score a goal;
- if $ s_i $ is ?, then the $ i $ -th kick could go either way.

Based on your predictions, you have to calculate the minimum possible number of kicks there can be in the penalty phase (that means, the earliest moment when the penalty phase is stopped, considering all possible ways it could go). Note that the referee doesn't take into account any predictions when deciding to stop the penalty phase — you may know that some kick will/won't be scored, but the referee doesn't.

## 说明/提示

Consider the example test:

In the first test case, consider the situation when the $ 1 $ -st, $ 5 $ -th and $ 7 $ -th kicks score goals, and kicks $ 2 $ , $ 3 $ , $ 4 $ and $ 6 $ are unsuccessful. Then the current number of goals for the first team is $ 3 $ , for the second team is $ 0 $ , and the referee sees that the second team can score at most $ 2 $ goals in the remaining kicks. So the penalty phase can be stopped after the $ 7 $ -th kick.

In the second test case, the penalty phase won't be stopped until all $ 10 $ kicks are finished.

In the third test case, if the first team doesn't score any of its three first kicks and the second team scores all of its three first kicks, then after the $ 6 $ -th kick, the first team has scored $ 0 $ goals and the second team has scored $ 3 $ goals, and the referee sees that the first team can score at most $ 2 $ goals in the remaining kicks. So, the penalty phase can be stopped after the $ 6 $ -th kick.

In the fourth test case, even though you can predict the whole penalty phase, the referee understands that the phase should be ended only after the $ 9 $ -th kick.

## 样例 #1

### 输入

```
4
1?0???1001
1111111111
??????????
0100000000```

### 输出

```
7
10
6
9```

# AI分析结果

### 题目内容
# 点球大战

## 题目描述
考虑一场足球比赛结束时简化的点球决胜阶段。

点球决胜阶段最多有10次罚球，第一支球队踢第一次罚球，第二支球队踢第二次罚球，然后第一支球队踢第三次罚球，依此类推。进球数更多的球队获胜；如果两支球队进球数相同，则比赛平局（请注意，这与通常的足球规则不同）。如果一支球队的进球数比另一支球队在剩余所有罚球中能达到的进球数还多，点球决胜阶段就会停止。例如，如果在第7次罚球后，第一支球队进了1个球，而第二支球队进了3个球，点球决胜阶段就结束了——第一支球队无法达到3个进球。

你知道每个罚球的球员是谁，所以你对这10次罚球都有预测。这些预测由一个由10个字符组成的字符串s表示。每个字符可以是1、0或?。这个字符串按以下方式表示你的预测：
 - 如果si是1，那么第i次罚球肯定会进球；
 - 如果si是0，那么第i次罚球肯定不会进球；
 - 如果si是?，那么第i次罚球有可能进球，也有可能不进球。

根据你的预测，你必须计算点球决胜阶段可能出现的最少罚球次数（也就是说，考虑所有可能的情况，点球决胜阶段最早停止的时刻）。请注意，裁判在决定停止点球决胜阶段时不会考虑任何预测——你可能知道某个罚球会进或不会进，但裁判不知道。

## 说明/提示
考虑示例测试：
在第一个测试用例中，考虑这样一种情况：第1、5和7次罚球进球，而第2、3、4和6次罚球未进。那么此时第一支球队的进球数是3，第二支球队的进球数是0，裁判看到第二支球队在剩余罚球中最多能进2个球。所以点球决胜阶段可以在第7次罚球后停止。

在第二个测试用例中，点球决胜阶段直到10次罚球全部结束才会停止。

在第三个测试用例中，如果第一支球队在前三次罚球中都没有进球，而第二支球队在前三次罚球中都进了球，那么在第6次罚球后，第一支球队进了0个球，第二支球队进了3个球，裁判看到第一支球队在剩余罚球中最多能进2个球。所以，点球决胜阶段可以在第6次罚球后停止。

在第四个测试用例中，尽管你可以预测整个点球决胜阶段，但裁判要到第9次罚球后才会明白该阶段应该结束。

## 样例 #1
### 输入
```
4
1?0???1001
1111111111
??????????
0100000000
```
### 输出
```
7
10
6
9
```

### 算法分类
贪心

### 综合分析与结论
这些题解主要围绕贪心策略展开。核心思路是通过合理假设“?”的结果，让某一队尽快获得绝对优势从而提前结束比赛。不同题解在实现细节和代码结构上有所差异。有的题解通过枚举所有可能情况来判断，时间复杂度较高；而多数题解利用贪心思想，在遍历字符串过程中动态判断比赛是否可以提前结束，有效降低了时间复杂度。

### 所选的题解
 - **作者：精神小伙！ (5星)**
    - **关键亮点**：思路清晰简洁，代码实现直接明了。通过维护两队得分及“?”的数量，在遍历字符串时实时判断是否有队伍得分加上“?”的得分大于等于6，若是则输出当前轮数，同时特判平局情况。
    - **重点代码**：
```cpp
#include<iostream>
using namespace std;
const int maxn = 20;
int n;
int a, b, t;
string s;
int main() {
    std::ios::sync_with_stdio(0);
    cin >> n;
    while (n--) {
        a = 0, b = 0, t = 0;
        bool f = 0;
        cin >> s;
        for (int i = 0; i < 10; ++i) {
            if (s[i] == '1') {
                if (i & 1) a++;
                else b++;
            }
            else if (s[i] == '0') {
                if (i & 1) b++;
                else a++;
            }
            else t++;
            if (a + t >= 6 || b + t >= 6) {
                cout << i + 1 << endl;
                f = 1;
                break;
            }
        }
        if (!f) cout << 10 << endl;
    }
    return 0;
}
```
核心实现思想：遍历字符串，根据字符更新两队得分及“?”数量，判断是否满足提前结束条件，不满足则最后输出10。

 - **作者：dthythxth_Huge_Brain (5星)**
    - **关键亮点**：代码结构清晰，函数封装性好。通过两个变量记录两队进球数，两个变量记录两队剩余踢球次数，在遍历过程中根据字符更新相关变量，并判断是否可以停止点球阶段。
    - **重点代码**：
```cpp
#include <iostream>
#include <string> 
using namespace std;
int kick(const string& s) {
    int team1 = 0; 
    int team2 = 0; 
    int Team1 = 5; 
    int Team2 = 5; 
    for (int i = 0; i < 10; i++) {
        if (i % 2 == 0) {
            if (s[i] == '1') team1++;
            else if (s[i] == '?') {
                team1++;
                Team1--;
            }
            Team1--;
        }
        else {
            if (s[i] == '1') team2++;
            else if (s[i] == '?') {
                team2++;
                Team2--;
            }
            Team2--;
        }
        int maxteam1 = team1 + Team1;
        int maxteam2 = team2 + Team2;
        if (maxteam1 < team2 || maxteam2 < team1) return i + 1; 
    }
    return 10; 
}
int main() {
    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        int mink = kick(s);
        cout << mink << endl;
    }
    return 0; 
}
```
核心实现思想：遍历字符串，根据奇偶判断队伍，更新进球数和剩余次数，通过比较当前进球数和预测最大进球数判断是否提前结束。

 - **作者：YGB_XU (4星)**
    - **关键亮点**：通过两个函数分别模拟支持不同队伍的情况，思路清晰。在函数中分别维护两队进球数和剩余机会，遍历字符串更新数据并判断是否提前结束比赛，最后取两种情况最小值。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;

string s;

inline int cal1() {
    int al = 5, bl = 5, as = 0, bs = 0;
    for (int i = 0; i <= 9; i++) {
        if (i % 2 == 0) {
            al--;
            if (s[i] == '?') {
                as++;
            }
            else {
                as += (int)s[i] - '0';
            }
        }
        else {
            bl--;
            if (s[i] == '?') {

            }
            else {
                bs += (int)s[i] - '0';
            }
        }
        if (bs + bl < as) return i + 1;
    }
    return 10;
}

inline int cal2() {
    int al = 5, bl = 5, as = 0, bs = 0;
    for (int i = 0; i <= 9; i++) {
        if (i % 2 == 0) {
            al--;
            if (s[i] == '?') {

            }
            else {
                as += (int)s[i] - '0';
            }
        }
        else {
            bl--;
            if (s[i] == '?') {
                bs++;
            }
            else {
                bs += (int)s[i] - '0';
            }
        }
        if (as + al < bs) return i + 1;
    }
    return 10;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        cin >> s;
        printf("%d\n", min(cal1(), cal2()));
    }
    return 0;
}
```
核心实现思想：两个函数分别贪心假设“?”情况，遍历判断是否提前结束，主函数取最小值输出。

### 最优关键思路或技巧
利用贪心策略，在遍历过程中通过合理假设“?”的结果，实时判断比赛是否能提前结束，避免了对所有可能情况的枚举，有效降低时间复杂度。

### 可拓展之处
同类型题通常围绕比赛结果预测、最优策略选择等场景，类似算法套路是在给定多种可能性（如本题的“?”）下，通过贪心策略寻找最优解。可以通过改变比赛规则、增加条件限制等方式拓展题目难度。

### 推荐题目
 - [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)：通过合理分组，运用贪心思想解决问题，与本题贪心策略类似。
 - [P1199 三国游戏](https://www.luogu.com.cn/problem/P1199)：需要在多种选择中寻找最优策略，与本题思路有相似之处。
 - [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：通过贪心选择最优排队顺序，与本题利用贪心优化结果的思路一致。

### 个人心得
暂未发现题解中有个人心得相关内容。 

---
处理用时：62.93秒