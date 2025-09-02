# 题目信息

# Help General

## 题目描述

Once upon a time in the Kingdom of Far Far Away lived Sir Lancelot, the chief Royal General. He was very proud of his men and he liked to invite the King to come and watch drill exercises which demonstrated the fighting techniques and tactics of the squad he was in charge of. But time went by and one day Sir Lancelot had a major argument with the Fairy Godmother (there were rumors that the argument occurred after the general spoke badly of the Godmother's flying techniques. That seemed to hurt the Fairy Godmother very deeply).

As the result of the argument, the Godmother put a rather strange curse upon the general. It sounded all complicated and quite harmless: "If the squared distance between some two soldiers equals to $ 5 $ , then those soldiers will conflict with each other!"

The drill exercises are held on a rectangular $ n×m $ field, split into $ nm $ square $ 1×1 $ segments for each soldier. Thus, the square of the distance between the soldiers that stand on squares $ (x_{1},y_{1}) $ and $ (x_{2},y_{2}) $ equals exactly $ (x_{1}-x_{2})^{2}+(y_{1}-y_{2})^{2} $ . Now not all $ nm $ squad soldiers can participate in the drill exercises as it was before the Fairy Godmother's curse. Unless, of course, the general wants the soldiers to fight with each other or even worse... For example, if he puts a soldier in the square $ (2,2) $ , then he cannot put soldiers in the squares $ (1,4) $ , $ (3,4) $ , $ (4,1) $ and $ (4,3) $ — each of them will conflict with the soldier in the square $ (2,2) $ .

Your task is to help the general. You are given the size of the drill exercise field. You are asked to calculate the maximum number of soldiers that can be simultaneously positioned on this field, so that no two soldiers fall under the Fairy Godmother's curse.

## 说明/提示

In the first sample test Sir Lancelot can place his 4 soldiers on the $ 2×4 $ court as follows (the soldiers' locations are marked with gray circles on the scheme):

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF142B/0d23ce3839b0ce156cddd9663617e134809111ae.png)In the second sample test he can place 6 soldiers on the $ 3×4 $ site in the following manner:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF142B/57bf2bd762016d87a2641e15975b3acd653786ad.png)

## 样例 #1

### 输入

```
2 4
```

### 输出

```
4```

## 样例 #2

### 输入

```
3 4
```

### 输出

```
6```

# AI分析结果

### 题目中文重写
## 帮助将军

### 题目描述
从前，在遥远王国里住着兰斯洛特爵士，他是皇家首席将军。他为自己的士兵感到非常骄傲，并且喜欢邀请国王前来观看操练演习，这些演习展示了他所负责小队的战斗技巧和战术。但随着时间的推移，有一天兰斯洛特爵士与仙女教母发生了一场激烈的争吵（有传言说，这场争吵是在将军批评了教母的飞行技巧之后发生的。这似乎深深地伤害了仙女教母）。

作为争吵的结果，教母对将军下了一个相当奇怪的诅咒。诅咒听起来很复杂，但似乎无害：“如果任意两个士兵之间距离的平方等于 5，那么这两个士兵就会互相冲突！”

操练演习在一个 $n×m$ 的矩形场地进行，场地被划分为 $nm$ 个 $1×1$ 的正方形区域，每个区域站一名士兵。因此，站在 $(x_{1},y_{1})$ 和 $(x_{2},y_{2})$ 区域的两名士兵之间距离的平方恰好为 $(x_{1}-x_{2})^{2}+(y_{1}-y_{2})^{2}$。现在，由于仙女教母的诅咒，并非所有 $nm$ 名士兵都能像诅咒之前那样参加操练演习。当然，除非将军想让士兵们互相争斗，或者更糟…… 例如，如果他在 $(2,2)$ 区域安排一名士兵，那么他就不能在 $(1,4)$、$(3,4)$、$(4,1)$ 和 $(4,3)$ 区域安排士兵，因为这些区域的士兵都会与 $(2,2)$ 区域的士兵发生冲突。

你的任务是帮助将军。已知操练场地的大小，你需要计算在这个场地上最多可以同时安排多少名士兵，使得没有两名士兵受到仙女教母诅咒的影响。

### 说明/提示
在第一个样例测试中，兰斯洛特爵士可以在 $2×4$ 的场地上安排 4 名士兵，如下所示（士兵的位置在图中用灰色圆圈标记）：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF142B/0d23ce3839b0ce156cddd9663617e134809111ae.png)
在第二个样例测试中，他可以在 $3×4$ 的场地上以如下方式安排 6 名士兵：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF142B/57bf2bd762016d87a2641e15975b3acd653786ad.png)

### 样例 #1
#### 输入
```
2 4
```
#### 输出
```
4
```

### 样例 #2
#### 输入
```
3 4
```
#### 输出
```
6
```

### 综合分析与结论
这些题解主要围绕在 $n×m$ 棋盘上放置尽可能多的马且使其互不攻击的问题展开。多数题解采用分类讨论的方法，针对 $n$ 或 $m$ 为 1、2 以及其他情况分别处理。部分题解还运用了二分图、黑白染色等思想来证明和求解。

### 思路对比
- **数学规律法**：通过找规律得出除特殊情况外，放置马的数量为棋盘格子数的一半（奇数时需特殊处理），如封禁用户、liaoxingrui 等题解。
- **二分图法**：将问题转化为求二分图的最大独立集，通过黑白染色选取点数较多的一组，如 a___ 的题解。
- **分类构造法**：根据不同的棋盘规模构造放置马的方案，如 shenbairui、MujicaSaki 等题解。

### 算法要点对比
- **数学规律法**：关键在于找出不同情况下的数学规律，如 $n$ 或 $m$ 为 1、2 时的特殊规律。
- **二分图法**：证明图为二分图，利用黑白染色和广度优先搜索（BFS）进行求解。
- **分类构造法**：针对不同情况构造具体的放置方案，如按田字格放置、交叉放置等。

### 解决难点对比
- **数学规律法**：难点在于通过少量数据找出普遍规律，并对特殊情况进行准确分类和处理。
- **二分图法**：证明图为二分图是关键，同时要考虑图的连通性对结果的影响。
- **分类构造法**：需要针对不同情况设计合理的放置方案，并准确计算放置马的数量。

### 评分及推荐题解
- **封禁用户（5星）**：
    - **关键亮点**：思路清晰，用数学方法解题，通过找规律得出结论，并对结论进行了详细证明。
    - **个人心得**：在考试时，若各种方法尝试失败，可尝试用数学方法，根据输入输出找规律，证明可留到后续进行。
    - **核心代码**：
```cpp
#include<iostream>
#include<cmath>
using namespace std;
int n,m;
int main(){
    cin>>n>>m;
    if(n==1||m==1){
        cout<<max(n,m);
        return 0;
    }
    if(n==2||m==2){
        if(n==2){
            if(m%2==0&&m%4!=0){
                cout<<n+m;
                return 0;
            }
        }
        if(m==2){
            if(n%2==0&&n%4!=0){
                cout<<n+m;
                return 0;
            }
        }
        if(max(n,m)%2==0){
            cout<<max(n,m)<<endl;
            return 0;
        }
        else{
            cout<<max(n,m)+1<<endl;
            return 0;
        }
    }
    cout<<(n*m+1)/2;
}
```
- **a___（5星）**：
    - **关键亮点**：提供了两种不同的解法，一种是二分图法，另一种是根据黑白染色的规律法，并对两种方法进行了详细证明。
    - **核心代码（二分图法）**：
```cpp
#include<cstdio>
const int N=1010,dx[8]={-1,1,2,2,1,-1,-2,-2},dy[8]={-2,-2,-1,1,2,2,1,-1};
bool b[N][N];
int n,m;
int cnt[2],ans,q[N*N][3],hd,tl;
inline int max(int a,int b){return a>b?a:b;}
int main()
{
    int i,j,k,x,y;
    scanf("%d%d",&n,&m);
    for(i=1;i<=n;i++)
    for(j=1;j<=m;j++)
    if(!b[i][j])
    {
        b[q[1][0]=i][q[1][1]=j]=true;
        cnt[0]=1;cnt[1]=0;
        for(hd=tl=1;hd<=tl;hd++)//bfs + 染色
        for(k=0;k<8;k++)
        {
            x=q[hd][0]+dx[k];
            y=q[hd][1]+dy[k];
            if(x>0&&x<=n&&y>0&&y<=m&&!b[x][y])
            {
                cnt[q[++tl][2]=(q[hd][2]^1)]++;
                b[q[tl][0]=x][q[tl][1]=y]=true;
            }
        }
        ans+=max(cnt[0],cnt[1]);//取较多一组点
    }
    printf("%d\n",ans);
    return 0;
}
```
- **liaoxingrui（4星）**：
    - **关键亮点**：思路清晰，通过观察放置马的规律得出结论，并对特殊情况进行了详细讨论。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int main(){
    cin>>n>>m;
    if(n==1||m==1)
        cout<<max(n,m);
    else if((n==2&&!(m&1)&&m&3)||(m==2&&!(n&1)&&n&3))
        cout<<n+m;
    else if(n==2||m==2)
        cout<<max(n,m)+(max(n,m)&1);
    else
        cout<<(n*m>>1)+(n*m&1);
    return 0;
}
```

### 最优关键思路或技巧
- **分类讨论**：根据 $n$ 和 $m$ 的不同取值进行分类讨论，分别处理特殊情况和一般情况。
- **黑白染色**：将棋盘抽象为黑白两色，利用马的攻击特性，得出马只能攻击不同颜色格子上的马，从而简化问题。
- **数学归纳**：通过观察少量数据，找出普遍的数学规律，并进行证明。

### 拓展思路
同类型题可能会改变棋子的攻击规则或棋盘的形状，解题思路仍然可以围绕分类讨论、染色法和找规律等方法展开。例如，改变棋子为象、车等，或者将棋盘改为圆形、三角形等。

### 推荐题目
- [P1219 八皇后](https://www.luogu.com.cn/problem/P1219)：经典的八皇后问题，考察回溯算法和棋盘放置问题。
- [P1579 哥德巴赫猜想（升级版）](https://www.luogu.com.cn/problem/P1579)：需要运用数学知识和枚举法解决问题。
- [P2089 烤鸡](https://www.luogu.com.cn/problem/P2089)：通过枚举和条件判断来找出所有可能的方案。

### 个人心得摘录与总结
- **封禁用户**：在考试时，若各种方法尝试失败，可尝试用数学方法，根据输入输出找规律，证明可留到后续进行。
- **动态WA**：一开始以为是状压dp，想方程式无果后，换思路找规律，参考题解采用分类讨论的方法解题。

---
处理用时：51.09秒