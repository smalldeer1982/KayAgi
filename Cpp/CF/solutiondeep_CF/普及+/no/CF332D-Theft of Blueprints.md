# 题目信息

# Theft of Blueprints

## 题目描述

Insurgents accidentally got hold of the plan of a top secret research polygon created on a distant planet for the needs of the Galaxy Empire. The insurgents suppose that this polygon is developing new deadly weapon. The polygon consists of $ n $ missile silos connected by bidirectional underground passages. The passages are linked to laboratories where research is conducted. Naturally, the passages are guarded severely: the passage between silos $ i $ and $ j $ is patrolled by $ c_{i,j} $ war droids.

The insurgents studied the polygon plan and noticed its unusual structure. As it turned out, for any $ k $ -element set of silos $ S $ there is exactly one silo that is directly connected by a passage with each silo from $ S $ (we'll call this silo adjacent with $ S $ ). Having considered that, the insurgents decided to act as follows:

1. they choose a $ k $ -element set of silos $ S $ ;
2. a group of scouts lands from the air into each silo from $ S $ ;
3. each group moves along the corresponding passage to the silo, adjacent with $ S $ (as the scouts move, they check out the laboratories and watch for any signs of weapon blueprints);
4. in the silo, adjacent with $ S $ , the groups get on the ship and fly away.

The danger of the operation is the total number of droids that patrol the passages through which the scouts will go. The danger of the operation obviously only depends on the way to choose set $ S $ . The insurgents haven't yet decided on the exact silos to send the scouts to. However, they already want to start preparing the weapons for the scout groups. To do that, the insurgents need to know the mathematical average of the dangers of the operations that correspond to all possible ways to choose set $ S $ . Solve this problem to help the insurgents protect the ideals of the Republic!

## 说明/提示

In the first sample there are 6 one-element sets of silos. For sets $ {1} $ , $ {5} $ the operation danger will equal 8, for sets $ {3} $ , $ {6} $ — 3, for sets $ {2} $ , $ {4} $ — 5. The mathematical average equals ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF332D/6779180059bebd2b65884098cbd93497c7078b58.png).

In the second sample there are 3 two-elements sets of silos: $ {1,3} $ (danger equals 21), $ {1,2} $ (danger equals 11), $ {2,3} $ (danger equals 10). The average operation danger equals ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF332D/e461096176a32afa0b41586e7192e319cef72429.png).

## 样例 #1

### 输入

```
6 1
-1 -1 -1 8 -1
-1 5 -1 -1
-1 -1 3
-1 -1
-1
```

### 输出

```
5
```

## 样例 #2

### 输入

```
3 2
10 0
11
```

### 输出

```
14
```

# AI分析结果

### 题目内容
# 蓝图盗窃

## 题目描述
叛乱分子意外获取了一份绝密研究基地的规划图，该基地是为银河帝国的需求在遥远星球上建造的。叛乱分子认为这个基地正在研发新的致命武器。该基地由$n$个导弹发射井通过双向地下通道相连，这些通道连接着进行研究的实验室。自然地，通道戒备森严：连接发射井$i$和$j$的通道由$c_{i,j}$个战斗机器人巡逻。

叛乱分子研究了基地规划图，注意到其不同寻常的结构。结果发现，对于任何大小为$k$的发射井集合$S$，都恰好有一个发射井与$S$中的每个发射井直接通过通道相连（我们称这个发射井与$S$相邻）。考虑到这一点，叛乱分子决定采取以下行动：
1. 他们选择一个大小为$k$的发射井集合$S$；
2. 一组侦察兵从空中降落到$S$中的每个发射井；
3. 每个小组沿着相应的通道移动到与$S$相邻的发射井（侦察兵移动时，会检查实验室并留意武器蓝图的任何迹象）；
4. 在与$S$相邻的发射井中，各小组登上飞船飞走。

行动的危险程度是侦察兵将经过的通道上巡逻机器人的总数。显然，行动的危险程度仅取决于选择集合$S$的方式。叛乱分子尚未决定具体向哪些发射井派遣侦察兵。然而，他们已经想开始为侦察小组准备武器。为此，叛乱分子需要知道对应所有可能选择集合$S$方式的行动危险程度的数学平均值。解决这个问题，帮助叛乱分子捍卫共和国的理想！

## 说明/提示
在第一个样例中，有6个单元素发射井集合。对于集合$\{1\}$，$\{5\}$，行动危险程度等于8；对于集合$\{3\}$，$\{6\}$，危险程度为3；对于集合$\{2\}$，$\{4\}$，危险程度为5。数学平均值等于$\frac{2\times8 + 2\times3 + 2\times5}{6}=5$。

在第二个样例中，有3个两元素发射井集合：$\{1,3\}$（危险程度等于21），$\{1,2\}$（危险程度等于11），$\{2,3\}$（危险程度等于10）。平均行动危险程度等于$\frac{21 + 11 + 10}{3}=14$。

## 样例 #1
### 输入
```
6 1
-1 -1 -1 8 -1
-1 5 -1 -1
-1 -1 3
-1 -1
-1
```
### 输出
```
5
```

## 样例 #2
### 输入
```
3 2
10 0
11
```
### 输出
```
14
```

### 算法分类
数学

### 综合分析与结论
题解通过对$k$不同取值进行分类讨论来求解。$k = 1$时，直接枚举每个点计算其连接边权和再除以$n$；$k = 2$时，枚举中间点及其边，根据度数计算边的贡献；$k\geqslant3$时，先通过引理证明图为$k + 1$个点的完全图，再计算所有点连接边权之和除以$n$。整体思路清晰，通过分类简化问题，利用数学推理得出关键结论，从而解决问题。

### 所选的题解
 - **作者：whiteqwq  星级：4星**
    - **关键亮点**：对$k$不同取值分别讨论，通过严谨的数学证明得出$k\geqslant3$时图为$k + 1$个点的完全图这一关键结论，使问题简化。
    - **重点代码及核心实现思想**：
```
#include<stdio.h>
#include<vector>
#define int long long
using namespace std;
const int maxn=2005;
int n,k,ans;
vector< pair<int,int> >v[maxn];
signed main(){
    scanf("%lld%lld",&n,&k);
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++){
            int x;
            scanf("%lld",&x);
            if(x==-1)
                continue;
            v[i].push_back(make_pair(j,x));
            v[j].push_back(make_pair(i,x));
        }
    if(k==1){
        for(int i=1;i<=n;i++)
            ans+=v[i][0].second;
        printf("%lld\n",ans/n);
        return 0;
    }
    if(k==2){
        for(int i=1;i<=n;i++){
            int cnt=0,sum=0;
            for(int j=0;j<v[i].size();j++)
                cnt++,sum+=v[i][j].second;
            ans+=(cnt-1)*sum;
        }
        printf("%lld\n",ans/(n*(n-1)/2));
        return 0;
    }
    for(int i=1;i<=n;i++)
        for(int j=0;j<v[i].size();j++)
            ans+=v[i][j].second;
    printf("%lld\n",ans/n);
    return 0;
}
```
核心实现思想：根据$k$的不同值分别计算答案。$k = 1$时，直接累加每个点连接边权；$k = 2$时，枚举中间点，计算每个中间点相连边的贡献；$k\geqslant3$时，直接累加所有边权并除以$n$。

### 最优关键思路或技巧
对$k$进行分类讨论，在$k\geqslant3$时，通过数学证明确定图的结构为$k + 1$个点的完全图，从而简化计算，这种利用数学性质分析图结构的思维方式是关键技巧。

### 可拓展之处
此类题目可拓展到其他基于图结构且具有特殊性质的数学期望计算问题，通常可以通过挖掘图的隐藏性质，利用数学推理简化问题。

### 洛谷相似题目推荐
 - [P1850 换教室](https://www.luogu.com.cn/problem/P1850)：涉及概率与期望，通过动态规划求解。
 - [P4316 绿豆蛙的归宿](https://www.luogu.com.cn/problem/P4316)：图上的概率期望问题，利用拓扑排序和递推求解。
 - [P4550 收集邮票](https://www.luogu.com.cn/problem/P4550)：结合概率与期望，通过逆向递推求解。 

---
处理用时：52.96秒