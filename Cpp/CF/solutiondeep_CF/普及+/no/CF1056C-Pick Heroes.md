# 题目信息

# Pick Heroes

## 题目描述

Don't you tell me what you think that I can be



If you say that Arkady is a bit old-fashioned playing checkers, you won't be right. There is also a modern computer game Arkady and his friends are keen on. We won't discuss its rules, the only feature important to this problem is that each player has to pick a distinct hero in the beginning of the game.

There are $ 2 $ teams each having $ n $ players and $ 2n $ heroes to distribute between the teams. The teams take turns picking heroes: at first, the first team chooses a hero in its team, after that the second team chooses a hero and so on. Note that after a hero is chosen it becomes unavailable to both teams.

The friends estimate the power of the $ i $ -th of the heroes as $ p_i $ . Each team wants to maximize the total power of its heroes. However, there is one exception: there are $ m $ pairs of heroes that are especially strong against each other, so when any team chooses a hero from such a pair, the other team must choose the other one on its turn. Each hero is in at most one such pair.

This is an interactive problem. You are to write a program that will optimally choose the heroes for one team, while the jury's program will play for the other team. Note that the jury's program may behave inefficiently, in this case you have to take the opportunity and still maximize the total power of your team. Formally, if you ever have chance to reach the total power of $ q $ or greater regardless of jury's program choices, you must get $ q $ or greater to pass a test.

## 说明/提示

In the first example the first turn is yours. In example, you choose $ 6 $ , the other team is forced to reply with $ 2 $ . You choose $ 5 $ , the other team chooses $ 4 $ . Finally, you choose $ 3 $ and the other team choose $ 1 $ .

In the second example you have the second turn. The other team chooses $ 6 $ , you choose $ 5 $ , forcing the other team to choose $ 1 $ . Now you choose $ 4 $ , the other team chooses $ 3 $ and you choose $ 2 $ .

## 样例 #1

### 输入

```
3 1
1 2 3 4 5 6
2 6
1

2

4

1
```

### 输出

```




6

5

3
```

## 样例 #2

### 输入

```
3 1
1 2 3 4 5 6
1 5
2
6

1

3
```

### 输出

```





5

4

2
```

# AI分析结果

### 题目内容
# 挑选英雄

## 题目描述
不要告诉我你认为我能成为什么样的人。

如果你说阿尔卡季玩跳棋有点老派，那你就错了。阿尔卡季和他的朋友们热衷于一款现代电脑游戏。我们不会讨论游戏规则，本题唯一重要的特征是每个玩家在游戏开始时必须挑选一个不同的英雄。

有2支队伍，每队有n名玩家，共有2n个英雄分配给这两队。队伍轮流挑选英雄：首先，第一队在其队伍中选择一个英雄，之后第二队选择一个英雄，依此类推。注意，一个英雄被选中后，两队都不能再选。

朋友们将第i个英雄的能力值估计为pi。每队都想最大化自己队伍英雄的总能力值。然而，有一个例外：有m对英雄相互克制，所以当任何一队选择了这样一对中的一个英雄时，另一队必须在轮到自己时选择另一个。每个英雄最多只属于一对这样的组合。

这是一道交互题。你要编写一个程序为其中一队最优地选择英雄，而评测程序将为另一队选择。注意，评测程序可能表现得不够高效，在这种情况下，你必须抓住机会，仍然最大化你所在队伍的总能力值。正式地说，如果你有机会达到q或更高的总能力值，无论评测程序如何选择，你都必须达到q或更高才能通过测试。

## 说明/提示
在第一个样例中，第一轮轮到你。例如，你选择6，另一队被迫选择2。你选择5，另一队选择4。最后，你选择3，另一队选择1。

在第二个样例中，第二轮轮到你。另一队选择6，你选择5，迫使另一队选择1。现在你选择4，另一队选择3，你选择2。

## 样例 #1
### 输入
```
3 1
1 2 3 4 5 6
2 6
1

2

4

1
```
### 输出
```




6

5

3
```

## 样例 #2
### 输入
```
3 1
1 2 3 4 5 6
1 5
2
6

1

3
```
### 输出
```





5

4

2
```

### 算法分类
贪心

### 综合分析与结论
这几道题解的核心思路都是基于贪心策略，根据先后手情况进行分类讨论。先手时优先选择每对仇敌中战斗力最强的，之后再选择剩余英雄中战斗力最强的；后手时若交互库选择了仇敌中的一个，则只能选择与之匹配的英雄，否则就获得了先手，之后按先手策略进行。算法要点在于利用好仇敌关系，最大化己方选择英雄的总能力值。解决难点主要在于清晰地处理先后手不同情况下的选择逻辑以及数据结构的合理运用。

### 所选的题解
 - **作者：jianhe (5星)**
    - **关键亮点**：思路清晰，简洁明了地阐述了贪心策略，代码量少且注释详细，使用`set`数据结构方便地删除元素，高效维护战斗力最强的英雄。
    - **核心代码片段**：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=2e3+10;
ll n,m,op,t,c,a[N],b[N],p[N],l[N],x[N];
bool vis[N];
multiset<pair<ll,ll> > q; 
void first(){
    for(int i=1;i<=m;i++)
        if(!vis[i]){
            cout<<(p[a[i]]>p[b[i]]?a[i]:b[i])<<"\n";
            fflush(stdout); 
            cin>>t;
            q.erase({-p[a[i]],a[i]});
            q.erase({-p[b[i]],b[i]});
        }    
    while(!q.empty()){
        cout<<(*q.begin()).second<<"\n";
        q.erase(q.begin());
        fflush(stdout); 
        if(!q.empty()){cin>>t;q.erase({-p[t],t});}        
    }
}
int main(){
    cin>>n>>m;c=m;
    for(int i=1;i<=n*2;i++) cin>>p[i],q.insert({-p[i],i});
    for(int i=1;i<=m;i++) cin>>a[i]>>b[i],l[a[i]]=b[i],l[b[i]]=a[i],x[a[i]]=x[b[i]]=i;
    cin>>op;
    if(op==1) first();
    else
        for(int i=1;i<=n;i++){
            cin>>t;
            q.erase({-p[t],t});
            if(l[t]&&q.find({-p[l[t]],l[t]})!=q.end()){
                cout<<l[t]<<"\n";
                fflush(stdout); 
                q.erase({-p[l[t]],l[t]});vis[x[t]]=1;
            }else{first();break;}
        }
    return 0;
}
```
    - **核心实现思想**：`first`函数处理先手情况，先遍历仇敌对，选择能力值大的英雄，同时从`multiset`中删除对应元素。之后不断从`multiset`中选择剩余英雄中能力值最大的。`main`函数根据输入的先后手标志，先手直接调用`first`函数，后手则根据交互库选择的英雄判断是否为仇敌关系，若是则选择对应的仇敌，否则调用`first`函数。
 - **作者：Miraik (4星)**
    - **关键亮点**：简洁清晰地阐述题意和解题思路，明确指出先手的主动权及具体策略，后手在不同情况下的应对方式，虽然未给出代码，但思路完整。
 - **作者：FReQuenter (4星)**
    - **关键亮点**：详细分先后手讨论贪心策略，代码实现逻辑清晰，对每种情况的处理步骤明确，通过自定义结构体和优先队列维护英雄信息。
    - **核心代码片段**：
```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
#define endl endl<<endl
using namespace std;
int n,m,t,p[2005];
pair<int,int> dis[1005];
bool cho[2005];
struct node{
    int num,idx;
    node(){}
    node(int _num,int _idx){
        num=_num;
        idx=_idx;
    }
    friend bool operator < (node a,node b){
        if(a.num!=b.num) return a.num<b.num;
        return a.idx<b.idx;
    }
};
int fnd(int x){
    for(int i=1;i<=m;i++){
        if((dis[i].fi==x&&!cho[dis[i].se])
         ||(dis[i].se==x&&!cho[dis[i].fi])) return i;
    }
    return 0;
}//找第一个没有选的
//其实可以用map维护，但是容易写挂（我很懒的
signed main(){
    cin>>n>>m;
    for(int i=1;i<=n*2;i++) cin>>p[i];
    for(int i=1;i<=m;i++) cin>>dis[i].fi>>dis[i].se;
    cin>>t;
    priority_queue<node> q;
    for(int i=1;i<=n*2;i++){
        q.push(node(p[i],i));
    }
    if(t==1){//先手
        for(int i=1;i<=m;i++){
            if(p[dis[i].fi]<p[dis[i].se]) swap(dis[i].fi,dis[i].se);
            cout<<dis[i].fi<<endl;
            int x;
            cin>>x;
            cho[x]=cho[dis[i].fi]=true;
            //优先使用仇敌关系
        }
        while(!q.empty()){
            while(!q.empty()&&cho[q.top().idx]) q.pop();
            if(q.empty()) break;
            cout<<q.top().idx<<endl;
            cho[q.top().idx]=true;
            int x;
            cin>>x;
            cho[x]=true;
        }//找最大
    }
    if(t==2){
        for(int i=1;i<=n;i++){
            int x;
            cin>>x;
            cho[x]=true;
            int tmp=fnd(x);
            if(tmp){
                if(dis[tmp].fi==x){
                    cho[dis[tmp].se]=true;
                    cout<<dis[tmp].se<<endl;
                }
                else{
                    cho[dis[tmp].fi]=true;
                    cout<<dis[tmp].fi<<endl;
                }
                //如果是仇敌关系中的一员
            }
            else{
                bool chod=false;
                for(int i=1;i<=m;i++){
                    if(!cho[dis[i].fi]&&!cho[dis[i].se]){
                        chod=true;
                        if(p[dis[i].fi]<p[dis[i].se]) swap(dis[i].fi,dis[i].se);
                        cout<<dis[i].fi<<endl;
                        cho[dis[i].fi]=true;
                        break;
                        //如果还有仇敌关系
                    }
                }
                if(!chod){
                    while(!q.empty()&&cho[q.top().idx]) q.pop();
                    cout<<q.top().idx<<endl;
                    cho[q.top().idx]=true;
                    //没有了仇敌关系，找最大
                }
            }
        }
    }
    return 0;
}
```
    - **核心实现思想**：通过优先队列`q`维护英雄信息，先手时先遍历仇敌对，选择能力值大的英雄并标记已选，之后从优先队列中不断选择剩余未选英雄中能力值最大的。后手时根据交互库选择的英雄判断是否为仇敌关系，若是则选择对应的仇敌，否则按先手策略选择仇敌对中能力值大的，若没有仇敌关系则从优先队列选最大的。

### 最优关键思路或技巧
利用贪心策略，根据先后手情况，优先处理仇敌关系，选择其中能力值大的英雄，之后选择剩余英雄中能力值最大的。合理使用数据结构如`set`、优先队列来高效维护英雄信息，便于快速选择能力值最大的英雄。

### 拓展思路
同类型题可关注其他涉及博弈且可通过贪心策略解决的交互题，类似算法套路是在存在限制关系的选择场景下，分析先后手优劣势，依据贪心原则制定选择策略。

### 推荐题目
 - [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)
 - [P1248 加工生产调度](https://www.luogu.com.cn/problem/P1248)
 - [P2123 皇后游戏](https://www.luogu.com.cn/problem/P2123)

### 个人心得
无

---
处理用时：86.30秒