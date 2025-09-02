# 题目信息

# Game On Leaves

## 题目描述

Ayush and Ashish play a game on an unrooted tree consisting of $ n $ nodes numbered $ 1 $ to $ n $ . Players make the following move in turns:

- Select any leaf node in the tree and remove it together with any edge which has this node as one of its endpoints. A leaf node is a node with degree less than or equal to $ 1 $ .

A tree is a connected undirected graph without cycles.

There is a special node numbered $ x $ . The player who removes this node wins the game.

Ayush moves first. Determine the winner of the game if each player plays optimally.

## 说明/提示

For the $ 1 $ st test case, Ayush can only remove node $ 2 $ or $ 3 $ , after which node $ 1 $ becomes a leaf node and Ashish can remove it in his turn.

For the $ 2 $ nd test case, Ayush can remove node $ 2 $ in the first move itself.

## 样例 #1

### 输入

```
1
3 1
2 1
3 1```

### 输出

```
Ashish```

## 样例 #2

### 输入

```
1
3 2
1 2
1 3```

### 输出

```
Ayush```

# AI分析结果

### 题目内容重写

**题目描述**

Ayush 和 Ashish 在一个由 $n$ 个节点组成的无根树上玩游戏，节点编号为 $1$ 到 $n$。玩家轮流进行以下操作：

- 选择树中的任意一个叶子节点，并将其与所有与之相连的边一起删除。叶子节点是指度数不超过 $1$ 的节点。

树是一个无环的连通无向图。

有一个特殊的节点编号为 $x$。删除该节点的玩家将赢得游戏。

Ayush 先手。假设双方都采取最优策略，确定游戏的获胜者。

**说明/提示**

对于第一个测试用例，Ayush 只能删除节点 $2$ 或 $3$，之后节点 $1$ 变为叶子节点，Ashish 可以在他的回合中删除它。

对于第二个测试用例，Ayush 可以在第一步直接删除节点 $2$。

**样例 #1**

输入：
```
1
3 1
2 1
3 1
```
输出：
```
Ashish
```

**样例 #2**

输入：
```
1
3 2
1 2
1 3
```
输出：
```
Ayush
```

### 算法分类
数学、图论

### 题解分析与结论

这道题的核心在于分析树的节点删除顺序以及特殊节点 $x$ 的位置。所有题解都提到了以下关键点：

1. **特判情况**：如果 $x$ 是叶子节点，先手 Ayush 可以直接删除 $x$ 获胜。
2. **一般情况**：如果 $x$ 不是叶子节点，游戏的胜负取决于节点总数 $n$ 的奇偶性。如果 $n$ 是奇数，后手 Ashish 获胜；如果 $n$ 是偶数，先手 Ayush 获胜。

### 评分较高的题解

#### 题解1：作者：ShineEternal (赞：4)

**星级**：★★★★★  
**关键亮点**：思路清晰，代码简洁，特判情况处理得当，逻辑严谨。

**核心代码**：
```cpp
#include<cstdio>
#include<cstring>
using namespace std;
int p[1005];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int a,b;
        int n,x;
        scanf("%d%d",&n,&x);
        memset(p,0,sizeof(p));
        for(int i=1;i<n;i++)
        {
            scanf("%d%d",&a,&b);
            p[a]++;
            p[b]++;
        }
        if(p[x]<=1)
        {
            printf("Ayush\n");
        }
        else
        {
            if(n%2==1)
            {
                printf("Ashish\n");
            }
            else
            {
                printf("Ayush\n");
            }
        }
    }
    return 0;
}
```

#### 题解2：作者：fighter (赞：1)

**星级**：★★★★  
**关键亮点**：思路清晰，代码简洁，特判情况处理得当，逻辑严谨。

**核心代码**：
```cpp
#include <bits/stdc++.h>
#define MAX 1005
using namespace std;

int n, m, in[MAX];

int main()
{
    int T;
    cin >> T;
    while(T--){
        memset(in, 0, sizeof(in));
        cin >> n >> m;
        int x, y;
        for(int i = 1; i < n; i++){
            scanf("%d%d", &x, &y);
            in[x]++, in[y]++;
        }
        if(in[m] <= 1) puts("Ayush");
        else if(n&1) puts("Ashish");
        else puts("Ayush");
    }

    return 0;
}
```

#### 题解3：作者：Yizhixiaoyun (赞：0)

**星级**：★★★★  
**关键亮点**：思路清晰，代码简洁，特判情况处理得当，逻辑严谨。

**核心代码**：
```cpp
#include<bits/stdc++.h>
#define betterIO ios::sync_with_stdio(false);cin.tie(0)
#define first puts("Ayush")
#define second puts("Ashish")
using namespace std;
const int maxn=10010;
int T;
int n,x;
int u,v;
map<int,int> mp;

int cnt_edge,head[maxn];
struct edge{
    int to,nxt;
}e[maxn<<1];
void add(int u,int v){
    e[++cnt_edge].nxt=head[u];
    e[cnt_edge].to=v;
    head[u]=cnt_edge;
}

inline void init(){
    mp.clear();
    cin>>n>>x;
    for(register int i=1;i<n;++i){
        cin>>u>>v;
        add(u,v);add(v,u);
        mp[u]++;mp[v]++;
    }
}
int main(){
    betterIO;
    cin>>T;
    while(T--){
        init();
        if(n==1){
            first;continue;
        }
        if(mp[x]==1) first;
        else{
            if(n%2==0) first;
            else second;
        }
    }
}
```

### 最优关键思路或技巧

1. **特判叶子节点**：如果 $x$ 是叶子节点，先手可以直接删除 $x$ 获胜。
2. **奇偶性判断**：如果 $x$ 不是叶子节点，游戏的胜负取决于节点总数 $n$ 的奇偶性。

### 可拓展之处

类似的问题可以扩展到其他图论游戏中，例如在图中删除特定节点或边的游戏。这类问题通常需要分析图的拓扑结构以及节点的度数。

### 推荐题目

1. [P1352 没有上司的舞会](https://www.luogu.com.cn/problem/P1352)
2. [P1040 加分二叉树](https://www.luogu.com.cn/problem/P1040)
3. [P2015 二叉苹果树](https://www.luogu.com.cn/problem/P2015)

这些题目都涉及到树的结构和节点的删除或选择，与本题有相似之处。

---
处理用时：41.19秒