# 题目信息

# Lost Tree

## 题目描述

This is an interactive problem.

Little Dormi was faced with an awkward problem at the carnival: he has to guess the edges of an unweighted tree of $ n $ nodes! The nodes of the tree are numbered from $ 1 $ to $ n $ .

The game master only allows him to ask one type of question:

- Little Dormi picks a node $ r $ ( $ 1 \le r \le n $ ), and the game master will reply with an array $ d_1, d_2, \ldots, d_n $ , where $ d_i $ is the length of the shortest path from node $ r $ to $ i $ , for all $ 1 \le i \le n $ .

Additionally, to make the game unfair challenge Little Dormi the game master will allow at most $ \lceil\frac{n}{2}\rceil $ questions, where $ \lceil x \rceil $ denotes the smallest integer greater than or equal to $ x $ .

Faced with the stomach-churning possibility of not being able to guess the tree, Little Dormi needs your help to devise a winning strategy!

Note that the game master creates the tree before the game starts, and does not change it during the game.

## 说明/提示

Here is the tree from the first example.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1534D/db5986557f00451a4bfc4f6b9560af77b9bcbfc0.png)Notice that the edges can be output in any order.

Additionally, here are the answers for querying every single node in example $ 1 $ :

- $ 1 $ : $ [0,1,2,2] $
- $ 2 $ : $ [1,0,1,1] $
- $ 3 $ : $ [2,1,0,2] $
- $ 4 $ : $ [2,1,2,0] $

Below is the tree from the second example interaction.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1534D/391f4de27a316d6b5f59760a326b58ab613c06c0.png)Lastly, here are the answers for querying every single node in example $ 2 $ :

- $ 1 $ : $ [0,4,1,3,2] $
- $ 2 $ : $ [4,0,3,1,2] $
- $ 3 $ : $ [1,3,0,2,1] $
- $ 4 $ : $ [3,1,2,0,1] $
- $ 5 $ : $ [2,2,1,1,0] $

## 样例 #1

### 输入

```
4

0 1 2 2

1 0 1 1```

### 输出

```
? 1

? 2

!
4 2
1 2
2 3```

## 样例 #2

### 输入

```
5

2 2 1 1 0```

### 输出

```
? 5

!
4 5
3 5
2 4
1 3```

# AI分析结果

### 题目内容翻译
这是一道交互题。

小多尔米在狂欢节上遇到了一个棘手的问题：他必须猜出一棵有 $n$ 个节点的无权树的边！树的节点编号从 $1$ 到 $n$。

游戏主持人只允许他问一种类型的问题：
- 小多尔米选择一个节点 $r$（$1 \le r \le n$），游戏主持人将回复一个数组 $d_1, d_2, \ldots, d_n$，其中 $d_i$ 是从节点 $r$ 到 $i$ 的最短路径的长度，对于所有 $1 \le i \le n$。

此外，为了让游戏更具挑战性（对小多尔米不利），游戏主持人最多允许 $\lceil\frac{n}{2}\rceil$ 次询问，其中 $\lceil x \rceil$ 表示大于或等于 $x$ 的最小整数。

面对可能无法猜出树的可怕情况，小多尔米需要你的帮助来制定一个获胜策略！

请注意，游戏主持人在游戏开始前创建树，并且在游戏过程中不会改变它。

### 算法分类
构造

### 综合分析与结论
这些题解的核心思路大多是先选定一个根节点（通常选节点 1），通过询问该节点得到各节点的深度，再依据深度的奇偶性将节点分为两类，选择数量较少的那一类节点进行询问，进而确定树的所有边。不同题解在具体实现细节和代码风格上存在差异。

### 所选题解
- **kradcigam（4星）**
    - **关键亮点**：思路清晰，代码简洁易懂，直接阐述了选择深度奇数或偶数个数较少的点进行询问的核心思想，并通过代码实现。
- **scp020（4星）**
    - **关键亮点**：不仅给出了详细的解题思路和代码，还对做法的正确性进行了证明，逻辑严谨。
- **_lyx111（4星）**
    - **关键亮点**：分析过程简洁明了，准确抓住了问题的关键，通过比较奇偶深度节点数量来确定询问策略。

### 重点代码
#### kradcigam 的代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2010;
int h[2];
vector<int> v[2], ans[N];
int main() {
    int n;
    cin >> n;
    cout << "? " << 1 << endl;
    fflush (stdout);
    for (int i = 1;  i <= n; i++) {
        int dep;
        cin >> dep;
        if (dep == 1) ans[1].push_back(i);
        if (dep != 0) {
            h[dep&1]++;
            v[dep&1].push_back(i);
        }
    }
    int k=0;
    if (h[0] > h[1]) k = 1;
    for (int i : v[k]) {
        cout << "? " << i << endl;
        fflush (stdout);
        for (int j = 1; j <= n; j++) {
            int dep;
            cin >> dep;
            if (dep == 1)ans[i].push_back(j);
        }
    }
    cout << "!" << endl;
    for (int i = 1; i <= n; i++)
        for (int j : ans[i])
            if (j != 1)
                cout<<i<<" "<<j<<endl;
    return 0;
}
```
**核心实现思想**：先询问节点 1，统计深度为奇数和偶数的节点数量及具体节点，选择数量少的那一类节点进行询问，将距离为 1 的节点对记录下来，最后输出所有边。

#### scp020 的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,dep[2010],cntodd,cnt;
inline void ask(const int &pos)
{
    printf("? %d\n",pos),fflush(stdout);
}
struct Edge
{
    int from,to;
};
Edge edge[2010];
inline void add(const int &x,const int &y)
{
    edge[++cnt].from=x,edge[cnt].to=y;
}
int main()
{
    scanf("%d",&n),ask(1);
    for(int i=1;i<=n;i++) scanf("%d",&dep[i]),cntodd+=(dep[i]&1);//奇数深度统计一下
    if(cntodd*2<n)//奇数深度数量少，不大于一半
    {
        for(int i=2,dis;i<=n;i++)
            if(dep[i]&1)
            {
                ask(i);
                for(int j=1;j<=n;j++)
                {
                    scanf("%d",&dis);
                    if(dis==1) add(i,j);
                }
            }
    }else//相反，偶数深度数量少
    {
        for(int i=1;i<=n;i++) if(dep[i]==1) add(1,i);//因为问偶数深度，而树根 1 的儿子都是深度为 1，是奇数，所以先连一波边
        for(int i=2,dis;i<=n;i++)//和上面几乎一样
            if(!(dep[i]&1))
            {
                ask(i);
                for(int j=1;j<=n;j++)
                {
                    scanf("%d",&dis);
                    if(dis==1) add(i,j);
                }
            }
    }
    putchar('!'),putchar('\n');
    for(int i=1;i<n;i++) printf("%d %d\n",edge[i].from,edge[i].to);
    return 0;
}
```
**核心实现思想**：同样先询问节点 1 得到各节点深度，统计奇数深度节点数量，根据奇数和偶数深度节点数量的比较结果，选择数量少的那一类节点进行询问，记录距离为 1 的节点对作为边，最后输出所有边。

#### _lyx111 的代码
```cpp
钦定根为 $1$，那么先询问 `? 1` 得到 $n$ 个整数 $dep_1,\cdots,dep_n$，按照深度的奇偶性对节点进行黑白染色（偶数为黑色，奇数为白色）。
设黑色点的个数为 $t$，偶数点的个数为 $s$。因为 $s+t=n$，所以 $\min\{s,t\}\le\lfloor\dfrac{n}{2}\rfloor$。
- 若 $s<\lceil\dfrac{n}{2}\rceil$，那么直接询问所有白色点，然后将距离为 $1$ 的黑白色点对记录下来，输出即可；
- 若 $s\ge\lceil\dfrac{n}{2}\rceil$，则 $t\le\lceil\dfrac{n}{2}\rceil$，那么先将和结点 $1$ 距离为 $1$ 的白点记录下来，然后询问除了 $1$ 的所有黑色点，并将距离为 $1$ 的黑白色点对记录下来，输出即可。
注意在每次输出之后，都要再加一句 `fflush(stdout);`。
```
**核心实现思想**：以节点 1 为根，询问得到各节点深度并按奇偶性分类，根据奇偶深度节点数量的关系确定询问策略，记录距离为 1 的节点对作为边并输出。

### 关键思路或技巧
- 利用树的性质，相邻节点深度的奇偶性不同，通过统计奇偶深度节点的数量，选择数量较少的一类节点进行询问，可在不超过 $\lceil\frac{n}{2}\rceil$ 次询问的限制下确定树的所有边。
- 注意在交互题中，每次输出询问后要及时刷新输出缓冲区（`fflush(stdout)`）。

### 拓展思路
同类型题可能会改变树的性质（如加权树、有向树等）或询问的限制条件，解题时可参考本题思路，结合新的条件进行调整。类似算法套路可用于解决其他交互类型的图论问题，通过合理选择询问策略来获取足够的信息以确定图的结构。

### 推荐题目
- [P1113 杂务](https://www.luogu.com.cn/problem/P1113)：涉及图的拓扑排序和任务安排，与树的结构和节点关系有一定关联。
- [P1341 无序字母对](https://www.luogu.com.cn/problem/P1341)：需要通过给定的条件构造图并找出欧拉路径，锻炼构造和图论的思维。
- [P2820 局域网](https://www.luogu.com.cn/problem/P2820)：关于图的最小生成树问题，可加深对图的结构和边的处理的理解。

### 个人心得摘录与总结
- **Glori**：提到这道题在考场上 WA 了预测试，赛后很快调出来。这表明在考场上可能由于紧张或思路不清晰导致出错，赛后冷静思考能更快解决问题，提醒我们在考场上要保持良好的心态和清晰的思路。

---
处理用时：63.59秒