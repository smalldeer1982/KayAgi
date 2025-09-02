# 题目信息

# Maximum Control (easy)

## 题目描述

The Resistance is trying to take control over all planets in a particular solar system. This solar system is shaped like a tree. More precisely, some planets are connected by bidirectional hyperspace tunnels in such a way that there is a path between every pair of the planets, but removing any tunnel would disconnect some of them.

The Resistance already has measures in place that will, when the time is right, enable them to control every planet that is not remote. A planet is considered to be remote if it is connected to the rest of the planets only via a single hyperspace tunnel.

How much work is there left to be done: that is, how many remote planets are there?

## 说明/提示

In the first example, only planets $ 2 $ , $ 3 $ and $ 5 $ are connected by a single tunnel.

In the second example, the remote planets are $ 2 $ and $ 3 $ .

Note that this problem has only two versions – easy and medium.

## 样例 #1

### 输入

```
5
4 1
4 2
1 3
1 5
```

### 输出

```
3
```

## 样例 #2

### 输入

```
4
1 2
4 3
1 4
```

### 输出

```
2
```

# AI分析结果

### 中文重写题目内容
# 最大控制（简单）

## 题目描述
抵抗组织正试图控制某个太阳系中的所有行星。这个太阳系的形状像一棵树。更准确地说，一些行星通过双向超空间隧道相连，使得任意一对行星之间都有一条路径，但移除任何一条隧道都会使其中一些行星断开连接。

抵抗组织已经采取了措施，一旦时机成熟，他们就能控制所有非偏远的行星。如果一颗行星仅通过一条超空间隧道与太阳系的其他部分相连，则被认为是偏远的。

还剩下多少工作要做，即有多少颗偏远的行星？

## 说明/提示
在第一个示例中，只有行星 2、3 和 5 仅通过一条隧道相连。
在第二个示例中，偏远的行星是 2 和 3。
请注意，这个问题只有两个版本——简单版和中等版。

## 样例 #1
### 输入
```
5
4 1
4 2
1 3
1 5
```
### 输出
```
3
```

## 样例 #2
### 输入
```
4
1 2
4 3
1 4
```
### 输出
```
2
```

### 算法分类
图论

### 综合分析与结论
这些题解的思路基本一致，都是通过定义一个数组来统计每个点的度（即与该点相连的边的数量），在输入边的信息时更新数组，最后遍历数组，统计度为 1 的点的数量，即为所求的偏远行星的数量。

算法要点：
1. 利用数组来记录每个点的度。
2. 边输入边更新度的信息。
3. 遍历数组统计度为 1 的点。

解决难点：
本题难点较低，主要是理解树的性质（$n$ 个点的树有 $n - 1$ 条边），并正确统计每个点的度。

### 题解评分
| 作者 | 评分 | 理由 |
| --- | --- | --- |
| LiAuPb | 4星 | 思路清晰，代码有注释，可读性较好。 |
| 无钩七不改名 | 4星 | 思路简单明了，代码简洁。 |
| lkjzyd20 | 3星 | 代码存在变量未声明的小问题，影响可读性。 |
| yinpeichu2021 | 3星 | 输入循环次数有误，逻辑存在瑕疵。 |
| WA_sir | 3星 | 只有思路分析，没有代码实现。 |
| ruruo | 3星 | 变量命名不规范，影响代码可读性。 |
| TheShuMo | 3星 | 代码结构较清晰，但注释较少。 |

### 所选题解
- **LiAuPb（4星）**：关键亮点是思路清晰，代码有详细注释，便于理解。
- **无钩七不改名（4星）**：关键亮点是思路简单直接，代码简洁。

### 重点代码
#### LiAuPb 的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n, x, y, a[1001], ans;//定义 
int main(){
    scanf("%d", &n);//输入有几个节点 
    for(int i = 1; i <= n - 1; i++){//注意是n - 1条边 
        scanf("%d%d", &x, &y);//输入相连的两个点 
        a[x]++;
        a[y]++;//统计到数组里去 
    }
    for(int i = 1; i <= 1000; i++){
        if(a[i] == 1){//如果与节点i相邻的只有一个点 
            ans++;//ans加一 
        }
    }
    printf("%d", ans);//输出答案 
    return 0;
}
```
核心实现思想：通过数组 `a` 统计每个点的度，最后遍历数组找出度为 1 的点并计数。

#### 无钩七不改名的代码
```cpp
#include<bits/stdc++.h>
using namespace std;

int n,a[1005],ans;

int main(){
    scanf("%d",&n);
    for(int i=1;i<n;i++){
        int x,y;
        scanf("%d%d",&x,&y);
        a[x]++,a[y]++;
    }
    for(int i=1;i<=n;i++)if(a[i]==1)ans++;
    printf("%d",ans);
    return 0;
}
```
核心实现思想：同样是用数组 `a` 统计度，遍历数组统计度为 1 的点。

### 最优关键思路或技巧
使用数组作为桶来统计每个点的度，边输入边更新，最后遍历数组统计度为 1 的点，这种方法简单高效，利用了树的性质（$n$ 个点的树有 $n - 1$ 条边）。

### 可拓展之处
同类型题或类似算法套路：
1. 求树的重心：树的重心是指树中的一个节点，使得以该节点为根的所有子树中，节点数最多的子树的节点数最少。可以通过深度优先搜索来统计每个子树的节点数，进而找到树的重心。
2. 树的直径：树的直径是指树中最远的两个节点之间的距离。可以通过两次深度优先搜索或广度优先搜索来求解。
3. 树的最小生成树：在一个带权的连通无向图中，找到一棵边权之和最小的生成树。常见的算法有 Prim 算法和 Kruskal 算法。

### 推荐洛谷题目
1. [P1192 台阶问题](https://www.luogu.com.cn/problem/P1192)：考察树的基本概念和简单的递推。
2. [P1305 新二叉树](https://www.luogu.com.cn/problem/P1305)：关于树的遍历和构建。
3. [P1553 数字反转（升级版）](https://www.luogu.com.cn/problem/P1553)：与树的结构和操作相关。

### 个人心得
题解中均未包含个人心得。 

---
处理用时：43.19秒