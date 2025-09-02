# 题目信息

# Queen

## 题目描述

You are given a rooted tree with vertices numerated from $ 1 $ to $ n $ . A tree is a connected graph without cycles. A rooted tree has a special vertex named root.

Ancestors of the vertex $ i $ are all vertices on the path from the root to the vertex $ i $ , except the vertex $ i $ itself. The parent of the vertex $ i $ is the nearest to the vertex $ i $ ancestor of $ i $ . Each vertex is a child of its parent. In the given tree the parent of the vertex $ i $ is the vertex $ p_i $ . For the root, the value $ p_i $ is $ -1 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1143C/767631fbfbd5e834691c335a1beebc4c83722771.png)An example of a tree with $ n=8 $ , the root is vertex $ 5 $ . The parent of the vertex $ 2 $ is vertex $ 3 $ , the parent of the vertex $ 1 $ is vertex $ 5 $ . The ancestors of the vertex $ 6 $ are vertices $ 4 $ and $ 5 $ , the ancestors of the vertex $ 7 $ are vertices $ 8 $ , $ 3 $ and $ 5 $ You noticed that some vertices do not respect others. In particular, if $ c_i = 1 $ , then the vertex $ i $ does not respect any of its ancestors, and if $ c_i = 0 $ , it respects all of them.

You decided to delete vertices from the tree one by one. On each step you select such a non-root vertex that it does not respect its parent and none of its children respects it. If there are several such vertices, you select the one with the smallest number. When you delete this vertex $ v $ , all children of $ v $ become connected with the parent of $ v $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1143C/fa2af41e1e599c9e51ca9e3edafbee94d578e807.png)An example of deletion of the vertex $ 7 $ .Once there are no vertices matching the criteria for deletion, you stop the process. Print the order in which you will delete the vertices. Note that this order is unique.

## 说明/提示

The deletion process in the first example is as follows (see the picture below, the vertices with $ c_i=1 $ are in yellow):

- first you will delete the vertex $ 1 $ , because it does not respect ancestors and all its children (the vertex $ 2 $ ) do not respect it, and $ 1 $ is the smallest index among such vertices;
- the vertex $ 2 $ will be connected with the vertex $ 3 $ after deletion;
- then you will delete the vertex $ 2 $ , because it does not respect ancestors and all its children (the only vertex $ 4 $ ) do not respect it;
- the vertex $ 4 $ will be connected with the vertex $ 3 $ ;
- then you will delete the vertex $ 4 $ , because it does not respect ancestors and all its children (there are none) do not respect it ([vacuous truth](https://en.wikipedia.org/wiki/Vacuous_truth));
- you will just delete the vertex $ 4 $ ;
- there are no more vertices to delete.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1143C/ebd0eb4e79b93258618d042cf4204608334ae632.png)In the second example you don't need to delete any vertex:

- vertices $ 2 $ and $ 3 $ have children that respect them;
- vertices $ 4 $ and $ 5 $ respect ancestors.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1143C/301d90419aa6803a28893c2a81f56219871e0793.png)In the third example the tree will change this way:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1143C/7676abdd5b6383c016cad416ee32ca622873b718.png)

## 样例 #1

### 输入

```
5
3 1
1 1
-1 0
2 1
3 0
```

### 输出

```
1 2 4 
```

## 样例 #2

### 输入

```
5
-1 0
1 1
1 1
2 0
3 0
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
8
2 1
-1 0
1 0
1 1
1 1
4 0
5 1
7 0
```

### 输出

```
5 
```

# AI分析结果

### 题目中文重写
# 皇后

## 题目描述
给定一棵有根树，其顶点编号从 $1$ 到 $n$。树是一个无环的连通图。有根树有一个特殊的顶点，称为根。

顶点 $i$ 的祖先都是从根到顶点 $i$ 的路径上的所有顶点，但不包括顶点 $i$ 本身。顶点 $i$ 的父节点是离顶点 $i$ 最近的祖先。每个顶点都是其父节点的子节点。在给定的树中，顶点 $i$ 的父节点是顶点 $p_i$。对于根节点，$p_i$ 的值为 $-1$。

![示例图](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1143C/767631fbfbd5e834691c335a1beebc4c83722771.png)
一个 $n = 8$ 的树的示例，根节点是顶点 $5$。顶点 $2$ 的父节点是顶点 $3$，顶点 $1$ 的父节点是顶点 $5$。顶点 $6$ 的祖先节点是顶点 $4$ 和 $5$，顶点 $7$ 的祖先节点是顶点 $8$、$3$ 和 $5$。

你注意到有些顶点不尊重其他顶点。特别地，如果 $c_i = 1$，则顶点 $i$ 不尊重其任何祖先；如果 $c_i = 0$，则它尊重其所有祖先。

你决定逐个从树中删除顶点。在每一步中，你选择一个非根顶点，该顶点不尊重其父节点，且其所有子节点都不尊重它。如果有多个这样的顶点，则选择编号最小的那个。当你删除这个顶点 $v$ 时，$v$ 的所有子节点都将与 $v$ 的父节点相连。

![删除顶点示例](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1143C/fa2af41e1e599c9e51ca9e3edafbee94d578e807.png)
删除顶点 $7$ 的示例。

一旦没有符合删除条件的顶点，你就停止这个过程。打印你删除顶点的顺序。注意，这个顺序是唯一的。

## 说明/提示
第一个示例中的删除过程如下（见下图，$c_i = 1$ 的顶点为黄色）：
- 首先，你将删除顶点 $1$，因为它不尊重祖先，且其所有子节点（顶点 $2$）都不尊重它，并且 $1$ 是满足此条件的顶点中编号最小的；
- 删除后，顶点 $2$ 将与顶点 $3$ 相连；
- 然后，你将删除顶点 $2$，因为它不尊重祖先，且其所有子节点（唯一的顶点 $4$）都不尊重它；
- 顶点 $4$ 将与顶点 $3$ 相连；
- 接着，你将删除顶点 $4$，因为它不尊重祖先，且其没有子节点（根据[空值真值](https://en.wikipedia.org/wiki/Vacuous_truth)）；
- 你只需删除顶点 $4$；
- 没有更多的顶点需要删除。

![第一个示例删除过程](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1143C/ebd0eb4e79b93258618d042cf4204608334ae632.png)

在第二个示例中，你不需要删除任何顶点：
- 顶点 $2$ 和 $3$ 有尊重它们的子节点；
- 顶点 $4$ 和 $5$ 尊重祖先。

![第二个示例](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1143C/301d90419aa6803a28893c2a81f56219871e0793.png)

在第三个示例中，树将按以下方式变化：

![第三个示例](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1143C/7676abdd5b6383c016cad416ee32ca622873b718.png)

## 样例 #1
### 输入
```
5
3 1
1 1
-1 0
2 1
3 0
```
### 输出
```
1 2 4 
```

## 样例 #2
### 输入
```
5
-1 0
1 1
1 1
2 0
3 0
```
### 输出
```
-1
```

## 样例 #3
### 输入
```
8
2 1
-1 0
1 0
1 1
1 1
4 0
5 1
7 0
```
### 输出
```
5 
```

### 算法分类
模拟

### 综合分析与结论
这些题解的核心思路都是围绕找出不尊重父节点且所有子节点都不尊重它的节点，按编号从小到大输出，若没有则输出 $-1$。大部分题解通过维护两个数组来记录节点是否尊重父节点以及子节点是否尊重该节点，最后遍历判断输出结果。部分题解还证明了删除节点对结果无影响，从而简化了问题。

### 所选题解
- **作者：Zq_water (赞：6)，4星**
  - **关键亮点**：思路清晰，代码简洁，通过两个数组记录相关信息，利用位运算进行判断，易于理解。
- **作者：bigclever (赞：6)，4星**
  - **关键亮点**：详细解释了思路，对数组的维护和判断条件说明清晰，代码可读性高。
- **作者：EdenSky (赞：6)，4星**
  - **关键亮点**：指出不需要建树，通过巧妙的数组记录和判断，时间复杂度低。

### 重点代码
#### Zq_water 的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll n,f,a[100005],b[100005];

int main(){
    scanf("%lld",&n);
    for(ll i=1;i<=n;i++) a[i]=1;
    
    for(ll i=1,x,y;i<=n;i++){
        scanf("%lld %lld",&x,&y);
        if(x!=-1) a[x]&=y,b[i]=y;
    }
    for(ll i=1;i<=n;i++) if(a[i]&b[i]) printf("%lld ",i),f=1;
    
    if(!f) printf("-1");
    return 0;
}
```
**核心实现思想**：用 `a` 数组记录子节点是否尊重该节点，`b` 数组记录该节点是否尊重父节点。输入时维护这两个数组，最后遍历判断同时满足条件的节点输出。

#### bigclever 的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100005],b[100005];
int main(){
    int n; cin>>n;
    for(int i=1;i<=n;i++)a[i]=1;
    for(int i=1,x,y;i<=n;i++){
        cin>>x>>y;
        if(x!=-1)a[x]&=y,b[i]=y;
    }
    bool ok=false;
    for(int i=1;i<=n;i++)
        if(a[i]&&b[i])cout<<i<<' ',ok=true;
    if(!ok)cout<<-1;
    return 0;
}
```
**核心实现思想**：与 Zq_water 的思路类似，用 `a` 数组维护子节点是否尊重该节点，`b` 数组维护该节点是否尊重父节点，最后遍历判断输出。

#### EdenSky 的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
pair<bool,bool> a[(int)1e5+5];
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
        int f,b;
        cin>>f>>b;
        if(b==0)
            a[f==-1?0:f].second=true;
        else    a[i].first=true;
    }
    bool flag=true;
    for(int i=1;i<=n;i++){
        if(a[i].first and !a[i].second){
            flag=false;
            cout<<i<<' ';
        }
    }
    if(flag)    cout<<-1;
}
```
**核心实现思想**：用 `pair` 数组 `a` 记录每个节点是否尊重父节点和是否有节点尊重它，输入时更新数组，最后遍历判断输出。

### 最优关键思路或技巧
- 利用数组记录节点的尊重信息，避免建树，降低复杂度。
- 证明删除节点对结果无影响，简化问题，直接按初始状态判断输出。

### 拓展思路
同类型题可能会改变树的结构或尊重规则，例如增加节点的其他属性，或者改变删除节点的条件等。类似算法套路可以是通过数组记录节点信息，然后根据条件进行判断和操作。

### 推荐题目
- [P1113 杂务](https://www.luogu.com.cn/problem/P1113)
- [P1340 兽径管理](https://www.luogu.com.cn/problem/P1340)
- [P1197 [JSOI2008] 星球大战](https://www.luogu.com.cn/problem/P1197)

### 个人心得摘录与总结
- **ys_kylin__**：因为英文题目没翻译完，没考虑答案为负一的情况，导致五连 wa。总结要仔细读题，考虑全面边界情况。

---
处理用时：65.68秒