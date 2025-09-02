# 题目信息

# Hashing Trees

## 题目描述

Sasha is taking part in a programming competition. In one of the problems she should check if some rooted trees are isomorphic or not. She has never seen this problem before, but, being an experienced participant, she guessed that she should match trees to some sequences and then compare these sequences instead of trees. Sasha wants to match each tree with a sequence $ a_{0},a_{1},...,a_{h} $ , where $ h $ is the height of the tree, and $ a_{i} $ equals to the number of vertices that are at distance of $ i $ edges from root.

Unfortunately, this time Sasha's intuition was wrong, and there could be several trees matching the same sequence. To show it, you need to write a program that, given the sequence $ a_{i} $ , builds two non-isomorphic rooted trees that match that sequence, or determines that there is only one such tree.

Two rooted trees are isomorphic, if you can reenumerate the vertices of the first one in such a way, that the index of the root becomes equal the index of the root of the second tree, and these two trees become equal.

The height of a rooted tree is the maximum number of edges on a path from the root to any other vertex.

## 说明/提示

The only tree in the first example and the two printed trees from the second example are shown on the picture:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF901A/b36c39150954d88fe8a1ed6f96a05d8a24b743af.png)

## 样例 #1

### 输入

```
2
1 1 1
```

### 输出

```
perfect
```

## 样例 #2

### 输入

```
2
1 2 2
```

### 输出

```
ambiguous
0 1 1 3 3
0 1 1 3 2
```

# AI分析结果

### 题目内容
# 哈希树

## 题目描述
萨沙正在参加一场编程竞赛。在其中一道题中，她需要判断一些有根树是否同构。她之前从未见过这个问题，但作为一名经验丰富的参赛者，她猜测应该将树与一些序列进行匹配，然后比较这些序列而不是直接比较树。萨沙想将每棵树与一个序列 $a_{0},a_{1},\cdots,a_{h}$ 匹配，其中 $h$ 是树的高度，$a_{i}$ 等于距离根节点 $i$ 条边的顶点数量。

不幸的是，这次萨沙的直觉是错误的，可能会有几棵树匹配同一个序列。为了证明这一点，你需要编写一个程序，给定序列 $a_{i}$，构建两个不同构的有根树来匹配该序列，或者确定这样的树只有一棵。

如果可以对第一棵树的顶点重新编号，使得根节点的索引与第二棵树的根节点索引相等，并且这两棵树变得完全相同，那么这两棵有根树就是同构的。

有根树的高度是从根节点到任何其他顶点的路径上的最大边数。

## 说明/提示
第一个示例中的唯一一棵树以及第二个示例中打印的两棵树如下图所示：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF901A/b36c39150954d88fe8a1ed6f96a05d8a24b743af.png)

## 样例 #1
### 输入
```
2
1 1 1
```
### 输出
```
perfect
```

## 样例 #2
### 输入
```
2
1 2 2
```
### 输出
```
ambiguous
0 1 1 3 3
0 1 1 3 2
```

### 算法分类
构造

### 综合分析与结论
这几道题解的核心思路都是先判断树的构造是否唯一，若不唯一则构造出两棵不同构的树。判断依据均为：当不存在两个相邻深度的节点数都大于1时，树唯一；否则不唯一。构造不同构树的方法类似，都是在不唯一的那一层，一棵将节点都连到上一层的一个点，另一棵将部分节点连到上一层的另一个点。不同题解在代码实现细节和表述上略有差异。

### 所选的题解
- **作者：Wf_yjqd（5星）**
  - **关键亮点**：思路清晰简洁，代码实现直接明了，通过记录不唯一位置，按顺序构造树，在不唯一位置进行特殊处理，模拟过程复杂度为线性。
  - **重点代码核心实现思想**：先遍历序列找到连续两层节点数都大于1的位置 `ad`，若不存在则输出 `perfect`；若存在则输出 `ambiguous`，并按两种不同方式构造树，一种是每层节点按顺序连接，另一种是在不唯一位置将部分节点连接到上一层不同节点。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+84;
int h,a[maxn],ad,cnt;
int main(){
    scanf("%d",&h);
    h++;
    for(int i=1;i<=h;i++){
        scanf("%d",&a[i]);
        if(a[i]>1&&a[i-1]>1)
            ad=i;
    }
    if(!ad)
        puts("perfect");
    else{
        puts("ambiguous");
        for(int i=1;i<=h;i++){
            for(int j=1;j<=a[i];j++)
                printf("%d ",cnt);
            cnt+=a[i];
        }
        puts("");
        cnt=0;
        for(int i=1;i<ad;i++){
            for(int j=1;j<=a[i];j++)
                printf("%d ",cnt);
            cnt+=a[i];
        }
        for(int i=1;i<a[ad];i++)
            printf("%d ",cnt);
        printf("%d ",cnt-1);
        cnt+=a[ad];
        for(int i=ad+1;i<=h;i++){
            for(int j=1;j<=a[i];j++)
                printf("%d ",cnt);
            cnt+=a[i];
        }
    }
    return 0;
}
```
- **作者：_slb（4星）**
  - **关键亮点**：先给出树唯一的充要条件并简单证明，使思路更具逻辑性，代码实现结构清晰，通过 `ok` 标志位判断树是否唯一，并分别进行相应输出和树的构造。
  - **重点代码核心实现思想**：遍历输入序列判断是否存在相邻两层节点数都大于1的情况，用 `ok` 标记。若 `ok` 为真输出 `perfect`；否则输出 `ambiguous` 并构造两棵不同构的树，构造方式与其他题解类似，在不唯一层进行不同连接。
```cpp
namespace solve
{
    const int maxn = 3e5 + 10;

    int a[maxn], h;

    void main()
    {
        cin >> h;
        int ok = 1;
        for (int i = 0; i <= h; i++)
            cin >> a[i];
        for (int i = 1; i <= h; i++)
            if (a[i] > 1 && a[i - 1] > 1)
                ok = 0;
        if (ok)
        {
            cout << "perfect" << endl;
            return;
        }
        cout << "ambiguous" << endl;
        int now = 0;
        cout << now << " ", now += a[0];
        for (int i = 1; i <= h; i++)
        {
            for (int j = 0; j < a[i]; j++)
                cout << now << " ";
            now += a[i];
        }
        cout << endl;
        now = 0, cout << now << " ", now += a[0];
        for (int i = 1; i <= h; i++)
        {
            if (a[i] > 1 && a[i - 1] > 1)
            {
                cout << now - 1 << " ";
                for (int j = 0; j < a[i] - 1; j++)
                    cout << now << " ";
            }
            else
            {
                for (int j = 0; j < a[i]; j++)
                    cout << now << " ";
            }
            now += a[i];
        }
    }
}
```

### 最优关键思路或技巧
通过分析树的结构特点，得出树构造唯一的充要条件，基于此条件进行判断和构造。在构造不同构树时，利用不唯一层节点连接方式的差异来实现。

### 可拓展思路
此类题目属于树的构造类型，类似套路是分析树的某种性质（如本题的同构性质）与给定序列或条件之间的关系，通过分类讨论不同情况来进行判断和构造。

### 洛谷相似题目
- [P1194 买礼物](https://www.luogu.com.cn/problem/P1194)
- [P1464 Function](https://www.luogu.com.cn/problem/P1464)
- [P2123 皇后游戏](https://www.luogu.com.cn/problem/P2123)

### 个人心得摘录与总结
无。 

---
处理用时：52.59秒