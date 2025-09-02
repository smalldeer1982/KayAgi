# 题目信息

# Exchange

## 题目描述

Monocarp is playing a MMORPG. There are two commonly used types of currency in this MMORPG — gold coins and silver coins. Monocarp wants to buy a new weapon for his character, and that weapon costs $ n $ silver coins. Unfortunately, right now, Monocarp has no coins at all.

Monocarp can earn gold coins by completing quests in the game. Each quest yields exactly one gold coin. Monocarp can also exchange coins via the in-game trading system. Monocarp has spent days analyzing the in-game economy; he came to the following conclusion: it is possible to sell one gold coin for $ a $ silver coins (i. e. Monocarp can lose one gold coin to gain $ a $ silver coins), or buy one gold coin for $ b $ silver coins (i. e. Monocarp can lose $ b $ silver coins to gain one gold coin).

Now Monocarp wants to calculate the minimum number of quests that he has to complete in order to have at least $ n $ silver coins after some abuse of the in-game economy. Note that Monocarp can perform exchanges of both types (selling and buying gold coins for silver coins) any number of times.

## 说明/提示

In the first test case of the example, Monocarp should complete $ 4 $ quests, and then sell $ 4 $ gold coins for $ 100 $ silver coins.

In the second test case, Monocarp should complete $ 400000 $ quests, and then sell $ 400000 $ gold coins for $ 10 $ million silver coins.

In the third test case, Monocarp should complete $ 1 $ quest, sell the gold coin for $ 50 $ silver coins, buy a gold coin for $ 48 $ silver coins, and then sell it again for $ 50 $ coins. So, he will have $ 52 $ silver coins.

In the fourth test case, Monocarp should complete $ 1 $ quest and then sell the gold coin he has obtained for $ 50 $ silver coins.

## 样例 #1

### 输入

```
4
100 25 30
9999997 25 50
52 50 48
49 50 1```

### 输出

```
4
400000
1
1```

# AI分析结果

### 题目内容
# Exchange

## 题目描述
Monocarp正在玩一款大型多人在线角色扮演游戏（MMORPG）。在这个游戏中有两种常用货币——金币和银币。Monocarp想为他的角色购买一把新武器，这把武器需要\(n\)个银币。不幸的是，此刻Monocarp一枚硬币都没有。

Monocarp可以通过在游戏中完成任务来赚取金币。每个任务恰好能产出一枚金币。Monocarp也可以通过游戏内的交易系统来兑换硬币。Monocarp花了几天时间分析游戏内经济，他得出以下结论：可以用一枚金币卖出\(a\)个银币（即Monocarp可以失去一枚金币来获得\(a\)个银币），或者用\(b\)个银币买入一枚金币（即Monocarp可以失去\(b\)个银币来获得一枚金币）。

现在Monocarp想计算出，为了在对游戏内经济进行一番操作后拥有至少\(n\)个银币，他最少需要完成多少个任务。注意，Monocarp可以任意多次执行这两种兑换操作（用金币换银币和用银币换金币）。

## 说明/提示
在示例的第一个测试用例中，Monocarp应该完成\(4\)个任务，然后用\(4\)枚金币换\(100\)个银币。

在第二个测试用例中，Monocarp应该完成\(400000\)个任务，然后用\(400000\)枚金币换\(1000\)万个银币。

在第三个测试用例中，Monocarp应该完成\(1\)个任务，将金币卖得\(50\)个银币，用\(48\)个银币买一枚金币，然后再把它卖掉得到\(50\)个银币。这样，他就会有\(52\)个银币。

在第四个测试用例中，Monocarp应该完成\(1\)个任务，然后卖掉他获得的金币得到\(50\)个银币。

## 样例 #1
### 输入
```
4
100 25 30
9999997 25 50
52 50 48
49 50 1
```
### 输出
```
4
400000
1
1
```

• **算法分类**：贪心
• **综合分析与结论**：各题解思路基本一致，均是根据\(a\)和\(b\)的大小关系进行分类讨论。当\(a > b\)时，通过一次任务获得一枚金币后，利用兑换规则可无限赚取银币，所以只需完成\(1\)次任务；当\(a \leq b\)时，用银币换金币会使银币数量减少，不进行此操作，只需完成\(\lceil\frac{n}{a}\rceil\)次任务。主要难点在于对\(a\)和\(b\)不同大小关系下兑换策略的分析。不同题解在代码实现上略有差异，如向上取整的方式、输入输出优化等。
• **所选的题解**：
  - **作者：cff_0102（5星）**
    - **关键亮点**：思路清晰，详细分析每种情况，对向上取整函数`ceil()`的使用及精度问题处理有详细说明。
    - **个人心得**：提到`ceil()`函数返回值为`double`会有精度误差，需转为`int`类型。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    int t;cin>>t;
    while(t--){
        int n,a,b;cin>>n>>a>>b;
        if(a>b)cout<<"1\n";
        else cout<<(int)ceil(1.0*n/a)<<endl;
    }
    return 0;
}
```
核心实现思想：先读入测试用例数\(t\)，对每个测试用例读入\(n\)、\(a\)、\(b\)，根据\(a\)和\(b\)的大小关系输出结果，利用`ceil()`函数实现向上取整并处理精度问题。
  - **作者：hanjinghao（4星）**
    - **关键亮点**：简洁明了地阐述题意和解题思路，代码简洁，使用`read`和`writeln`函数可能是自定义输入输出函数，一定程度上优化输入输出。
    - **重点代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int T, n, a, b;
    read(T);
    while (T--)
    {
        read(n);
        read(a);
        read(b);
        if (a > b) puts("1");
        else writeln((n + a - 1) / a);
    }
    return 0;
}
```
核心实现思想：通过自定义输入函数读入数据，根据\(a\)和\(b\)的大小关系输出结果，利用`(n + a - 1) / a`实现向上取整。
  - **作者：MornHus（4星）**
    - **关键亮点**：将解题思路形象描述为“投机倒把赚差价”，易于理解，代码简洁明了。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    double n,a,b;
    int t;
    cin>>t;
    while(t--){
        cin>>n>>a>>b;
        if(a>b){
            cout<<1<<endl;
        }else{
            cout<<(int)ceil(n/a)<<endl;
        }
    }
    return 0;
}
```
核心实现思想：读入测试用例数\(t\)及每个测试用例的\(n\)、\(a\)、\(b\)，根据\(a\)和\(b\)的大小关系输出结果，利用`ceil()`函数实现向上取整并转为`int`类型。
• **最优关键思路或技巧**：根据金币与银币兑换比例\(a\)和\(b\)的大小关系进行分类讨论，确定最优策略，这是典型的贪心思想。在实现向上取整时，可采用`(n + a - 1) / a`这种整数运算方式，避免`ceil()`函数的精度问题。
• **拓展**：此类题目属于贪心策略在货币兑换场景的应用，类似题目通常围绕不同兑换比例下如何通过最少操作达到目标数量，关键在于分析不同条件下的最优操作方式。
• **相似题目推荐**：
  - [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)
  - [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
  - [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)

---
处理用时：46.71秒