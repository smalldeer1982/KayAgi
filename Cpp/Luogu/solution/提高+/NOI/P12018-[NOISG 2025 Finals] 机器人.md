# [NOISG 2025 Finals] 机器人

## 题目描述

Funnyland 被建模为一个大小为 $(h + 2) \times (w + 2)$ 的网格。网格的行编号从 $0$ 到 $h + 1$（从上到下），列编号从 $0$ 到 $w + 1$（从左到右）。我们将位于网格第 $r$ 行、第 $c$ 列的单元格称为单元格 $(r, c)$。

最初，此网格中的所有单元格都被涂成 *白色*，除了最右侧的一列单元格，它们全部被涂成 *黑色*。

第 $1$ 到 $w$ 列中每列恰好包含一个特殊单元格。这些特殊单元格将被涂成 *红色* 或 *蓝色*。网格的边界（即最上方的行、最下方的行、最左侧的列和最右侧的列）永远不会包含特殊单元格。

一些机器人将被放置在最左侧的一列单元格中，并根据它们所在单元格的颜色进行移动：

- 如果单元格是白色的，机器人向右移动。
- 如果单元格是红色的，机器人向上移动。
- 如果单元格是蓝色的，机器人向下移动。
- 如果单元格是黑色的，机器人不会移动。

机器人不会相互碰撞，每个机器人独立移动。多个机器人可以占据同一个单元格。

一次查询由两个整数 $a$ 和 $b$ 组成（$1 \leq a < b \leq h$）。对于每个 $a \leq c \leq b$，都会有一个机器人从 $(c, 0)$ 位置开始。在所有可能的特殊单元格红色或蓝色涂色方案中，确定机器人最终可能占据的不同单元格的最小数量。

请注意，不同的查询可能会导致不同的特殊单元格涂色方案。


## 说明/提示

### 子任务

对于所有测试用例，输入满足以下约束条件：

- $1 \leq w, q \leq 200\,000$
- $2 \leq h \leq 200\,000$
- 对于所有 $1 \leq j \leq w$，有 $1 \leq x[j] \leq h$
- 对于所有 $1 \leq i \leq q$，有 $1 \leq a[i] < b[i] \leq h$

你的程序将在满足以下特殊性质的输入数据上进行测试：

| 子任务 | 分数 | 特殊性质 |
| :-: | :-: | :-: |
| $0$ | $0$ | 样例 |
| $1$ | $10$ | $h, w \leq 16, q \leq 20$ |
| $2$ | $4$ | $a[i] + 1 = b[i]$ |
| $3$ | $12$ | $x[1] < x[2] < \cdots < x[w]$ |
| $4$ | $43$ | $h, w, q \leq 5000$ |
| $5$ | $31$ | 无 |

### 样例 1 解释

此样例适用于子任务 $1, 4, 5$。

网格的颜色如下，特殊单元格用紫色表示。

![](https://cdn.luogu.com.cn/upload/image_hosting/fnpx3ay1.png)

对于第一个查询，我们可以将 $(3, 1)$ 和 $(4, 3)$ 处的特殊单元格涂成蓝色，将 $(2, 2)$ 和 $(1, 4)$ 处的特殊单元格涂成红色，以获得以下效果：

![](https://cdn.luogu.com.cn/upload/image_hosting/09mu5rbg.png)

- 从 $(1, 0)$ 开始的机器人移动到 $(1, 1), (1, 2), (1, 3), (1, 4), (0, 4), (0, 5)$，最终停在 $(0, 5)$。
- 从 $(2, 0)$ 开始的机器人移动到 $(2, 1), (2, 2), (1, 2), (1, 3), (1, 4), (0, 4), (0, 5)$，最终停在 $(0, 5)$。
- 从 $(3, 0)$ 开始的机器人移动到 $(3, 1), (4, 1), (4, 2), (4, 3), (5, 3), (5, 4)$，最终停在 $(5, 5)$。
- 从 $(4, 0)$ 开始的机器人移动到 $(4, 1), (4, 2), (4, 3), (5, 3), (5, 4)$，最终停在 $(5, 5)$。

机器人最终停在 $2$ 个不同的单元格 $(0, 5)$ 和 $(5, 5)$，因此正确的输出是 $2$。

对于第二个查询，我们可以按如下方式涂色：

![](https://cdn.luogu.com.cn/upload/image_hosting/q0umkoee.png)

从 $(1, 0), (2, 0)$ 和 $(3, 0)$ 开始的机器人最终都停在 $(0, 5)$。

对于第三个查询，我们可以按如下方式涂色：

![](https://cdn.luogu.com.cn/upload/image_hosting/1vjztie5.png)

从 $(2, 0), (3, 0)$ 和 $(4, 0)$ 开始的机器人最终都停在 $(3, 5)$。

### 样例 2 解释

此样例适用于子任务 $1, 4, 5$。


## 样例 #1

### 输入

```
4 4
3 2 4 1
3
1 4
1 3
2 4```

### 输出

```
2
1
1```

## 样例 #2

### 输入

```
15 16
5 15 3 4 13 8 3 7 14 6 2 10 11 12 9 1
20
4 10
7 15
5 15
2 6
7 15
5 15
12 15
13 14
5 14
13 14
2 11
3 11
2 5
9 11
3 15
5 14
1 13
3 7
7 12
4 8```

### 输出

```
2
2
3
2
2
3
1
1
3
1
3
2
1
1
3
3
4
1
2
1```

# 题解

## 作者：Error_Eric (赞：0)

### Statement

[Link](https://www.luogu.com.cn/problem/P12018)

当然这个题面非常难以理解。我们可以把这道题理解为一个 DAG 上的问题，这样就更加方便理解了。

DAG 版本的题面：

一个 $(h+2)\times(w+2)$ 的棋盘中有若干个格子上可能有结点。结点一共有三种：

第 $0$ 列布满结点，为**起始结点**。起始结点有一个出边指向这一行（除自己外）最靠左的结点（可能是中间结点或者终点结点）。

第 $w+1$ 列布满结点，为**终止结点**。终止结点没有出边。

非边缘的方格内，**每一列**有一个**中间结点**，这个结点有两个出边，分别指向上一行和下一行中，自己右边的结点中最靠左的一个。

每次询问给定一个起始结点的区间，求最小的（子树个数最少的），包含这些起始结点的，以终止结点为根的森林。

（还是有点怪）

（因为边只会往右，所以这个题是 DAG。）

![](https://cdn.luogu.com.cn/upload/image_hosting/yeh75t3e.png)

绿色圆圈是起始结点，紫色是中间结点，黑色是终止结点，蓝色 / 红色是 DAG 中的边，粉色是从 $1$ 开始的极大子树。（$1-3$ 可以到达同一个终点，但是 $1-4$ 不可以）

### Solution

注意到如果起始 $i$ 能够向下到达终止 $j(i<j)$，那么下面的的起始 $i+1$ 也一定能够到达。向上同理。因此，如果 $l, r$ 能够到达同一个终点， $[l, r]$ 中间的所有节点都能够到达同一个终点。所以最终的几个不交的子树在区间上也是不交的。

那么考虑一个简单的贪心，从最上面开始取，每次取最大的可能子树，这样总共的区间数一定是最小的。

我们只需要预处理出每个起始结点能到达的最高和最低终点结点就可以预处理出这个极大子区间。

这个东西 dp 或者记忆化都可以做。

最后要注意最终答案可能是非常多的不交的区间，因此要倍增来保证时间复杂度。

### Code

```cpp
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
const int _ = 2e5+50;
int h, w, q, ql, qr, cur;
class node{ // 结点类
    private:
        bool isend = 0; // 是否是终止结点
        int row; // 第几行
        node *ls, *rs; // 出边指向的结点
        int minans = -1, maxans = -1; // 记忆化（其实没必要）
    public:
        node(bool end, int Rrow, node *LS = nullptr, node *RS = nullptr){
            isend = end, row = Rrow, ls = LS, rs = RS;
            if(isend) minans = maxans = Rrow;
        }
        int minreach(){ // 最上面能到哪一行
            if(minans == -1) return minans = ls->minreach();
            else return minans;
        }
        int maxreach(){ // 最下面能到哪一行
            if(maxans == -1) return maxans = rs->maxreach();
            else return maxans;
        }
};

int subtree[_][20]; // subtree [i][k] 表示从 i 开始后的 2^k 个，相邻的，不交的，极大子树的最后一个起始节点
                    // 或者说从 i 开始到 i + 2^k - 1 恰好能用 2^k 个终点完全覆盖

int main(){
    
    ios::sync_with_stdio(0),
    cin.tie(0), cout.tie(0);
    cin >> h >> w;

    vector<node> beginr, endr, midr;// 初始，结束和中间
    beginr.reserve(h+2), endr.reserve(h+2), midr.reserve(w);

    vector<node*> frontr (h+2);
    for(int i = 0; i <= h+1; i++)
        endr.push_back(node(true, i, nullptr, nullptr)), frontr[i] = &endr[i];
    vector<int> ix (w);
    for(auto & ixx: ix)
        cin >> ixx;
    reverse(ix.begin(), ix.end());
    for(auto & ixx: ix){
        midr.push_back(node(false, ixx, frontr[ixx-1], frontr[ixx+1])), // 建红色的边
        frontr[ixx] = &midr.back();
    }
    for(int i = 0; i <= h+1; i++)
        beginr[i] = node(false, i, frontr[i], frontr[i]); // 建绿色的边
    
    for(int i = 1, j = 1; i<= h; i++){ // 初始化倍增 [0] 
        while(beginr[j].minreach() <= beginr[i].maxreach() && j <= h) 
            ++ j;
        subtree[i][0] = j-1;
    } // 
    
    
    for(int k = 1; (1<<k) <= h; k++){ // 倍增
        subtree[h+1][k-1] = subtree[h+2][k-1] = subtree[h+1][k] = subtree[h+2][k] = h+1;
        for(int i = 1; i <= h; i++){
            subtree[i][k] = subtree[subtree[i][k-1]+1][k-1];
        }
    } // 

    cin >> q;
    while(q--){
        cin >> ql >> qr, cur = 0;
        while(ql < qr){
            for(int k = 20; k >= 0; k--){
                if((1<<k) > h) continue;
                if(subtree[ql][k] < qr){
                    ql  = subtree[ql][k] +1, cur += (1<<k);
                }
            }
            if(subtree[ql][0] >= qr)
                break;
        }
        cout << cur+1 << endl;
    }
    
}
```

---

