# [NOISG 2018 Finals] City Mapping【缺样例】

## 题目背景

译自 [NOISG 2018 Finals D. City Mapping](https://github.com/noisg/sg_noi_archive/tree/master/2018/tasks/citymapping)。

----------------

当你在洛谷提交本题时，需要注意：

- 本题仅支持 C++ 系列语言。
- 你的代码中不应该包含头文件 `citymapping.h`。
- 你的代码中应当有如下两行函数声明：
	```cpp
	long long get_distance(int X, int Y);
	void find_roads(int N, int Q, int A[], int B[], int W[]);
	```
    
如遇评测问题，请联系搬题人。

## 题目描述

**这是一道交互题。**

Silvermill 市是一座有 $N$ 个路口和 $N-1$ 条道路的城市。其中道路的编号为 $0$ 到 $N-2$。

第 $i$ 条道路双向连接了 $(A_i,B_i)$ 两个路口，从任意方向通过这条道路都需要花费 $W_i$ 分钟。保证任意两个路口之间都能通过道路互相到达。

为了避免交通堵塞，Silvermill 市的**每个路口连接的道路不会超过 $3$ 条**。

你的任务是画出 Silvermill 市的地图，也就是找出所有 $N-1$ 条道路的 $(A_i,B_i,W_i)$。

为了达到这个目的，你可以询问市长至多 $Q$ 次从任意一个路口 $X$ 到任意一个路口 $Y$ 最少需要多少分钟。

### 实现细节

在本题中，**你不需要，也不应该实现主函数**。

你需要实现如下函数：

```cpp
void find_roads(int N, int Q, int A[], int B[], int W[])
```

该函数包含两个输入参数和三个输出参数，将在评测时被运行恰好一次。输入参数为 $N,Q$，分别表示路口的数量和最大询问次数；输出参数为 $A,B,W$，你需要确定城市中的 $N-1$ 条道路，按题意中的含义以数组 $A,B,W$ 的形式返回。返回道路的顺序可以是任意的，同一道路端点的顺序也可以是任意的。

注意数组的下标是从 $0$ 开始的。

你可以调用下面的函数来完成任务：

```cpp
long long get_distance(int X, int Y)
```

该函数将返回一个整数，表示从路口 $X$ 到路口 $Y$ 最少需要多少分钟。如果你调用此函数超过 $Q$ 次，或提供无效的路口编号作为参数，程序将立刻终止，你将得到 Wrong Answer 的评测状态。

## 说明/提示

### 调用示例

我们考虑如下的城市地图，展示一种可能的函数调用过程。

![](https://cdn.luogu.com.cn/upload/image_hosting/m7bz8mwi.png)

假设此时最大询问次数 $Q=5\times 10^5$。

你的函数将这样被调用恰好一次：

```cpp
find_roads(5, 500000, A, B, W);
```

其中 $A,B,W$ 是定义在测试程序中的数组。

一种可能的交互过程如下：

- `get_distance(5, 4) = 10`：`get_distance` 函数返回从路口 $5$ 到达路口 $4$ 的最少分钟数。路线 $5\to 3\to 4$ 是最短的，需要 $10$ 分钟。
- `get_distance(2, 4) = 1`：`get_distance` 函数返回了从路口 $2$ 到达路口 $4$ 的最少分钟数。直接从 $2$ 走到 $4$ 是最短的，需要 $1$ 分钟。
- `get_distance(1, 3) = 15`：`get_distance` 函数返回了从路口 $1$ 到达路口 $3$ 的最少分钟数。路线 $1\to 4\to 3$ 是最短的，需要 $15$ 分钟。
- `get_distance(1, 2) = 9`：`get_distance` 函数返回了从路口 $1$ 到达路口 $2$ 的最少分钟数。路线 $1\to 4\to 2$ 是最短的，需要 $9$ 分钟。

此时，我们假设你的 `find_roads` 函数认为自己已经掌握了足够的信息，可以推导出正确的地图，所以将 $A,B,W$ 数组分别赋值为 $A=[3,4,4,5],B=[4,1,2,3],W=[7,8,1,3]$，然后终止。

这只是一种可能的答案，因为返回道路的顺序可以是任意的，同一道路端点的顺序也可以是任意的。

### 子任务

对于 $100\%$ 的数据，$2\le N\le1000$，$1\le A_i,B_i\le N$，$1\le W_i\le 10^9$。

| 子任务 | 得分 | $Q$ | 特殊性质及备注 |
| :----------: | :----------: | :----------: | :----------: |
| $1$ | $9$ | $=5\times 10^5$ | $W_i=1$ |
| $2$ | $16$ | $=5\times 10^5$ | 无特殊限制 |
| $3$ | $13$ | $=12000$ | 每个路口最多连接两条道路，且 $W_i=1$ |
| $4$ | $19$ | $=12000$ | 每个路口最多连接两条道路 |
| $5$ | $43$ | $=25000$ | 无特殊限制，但有特殊的计分规则（请参阅**计分细则**） |

### 计分细则

子任务 $5$ 适用于以下的计分规则。你的得分依赖于你实现的函数询问的次数 $q$。

- 如果 $q>25000$，你将获得 $0$ 分。
- 如果 $12000<q\le 25000$，你将获得 $10-10\times \frac{q-12000}{13000}$ 分。
- 如果 $6500<q\le 12000$，你将获得 $40-30\times \frac{q-6500}{5500}$ 分。
- 如果 $q\le 6500$，你将获得 $43$ 分。

### 本地测试方式

我们在附件中下发了示例测试程序 `grader.cpp`，头文件 `citymapping.h`，你所需完成的代码的示例 `citymapping.cpp`，以及编译文件 `compile.sh`。

将这些文件置于同一文件夹下，使用 `compile.sh` 编译并运行生成的可执行文件，即可进行本地测试。

下发的示例测试程序与提交后使用的测试程序有所不同。

注意提交到洛谷上时有特殊的要求。

# 题解

## 作者：Shunpower (赞：2)

我们大约需要一个小常数 $\mathcal O(n\log n)$ 询问次数的做法。

我们的基本方针是维护现在的已有树，然后每次向上面在线地添加一个点，为了确保添加的这些点必然直接连接到已有树上，我们要先确定一个根，然后询问根到所有点的距离，按照距离从小到大添加。

### 方法一

考虑边分治的复杂度证明，如果我们每次找一个最好的边把二叉树切成两半，确定新的点加在其中的一边上，那么总的复杂度是 $\mathcal O(n\log n)$ 的。

于是我们考虑在我们的已有树上二分。我们每次只需找到那条关键边（关键边应当满足两边的子树大小相差绝对值最小），然后确定新加入这个点在哪边就可以了。

这是简单的，考虑总有一边的子树里面有根。因为我们知道所有点到根的路径长度，我们总是可以通过一次询问确定这个点到根的路径上存不存在这条边，从而确定这个点所在的子树。

递归下去即可做到单次询问次数 $\mathcal O(\log n)$，总次数就是 $\mathcal O(n\log n)$，但是这个 $\log$ 是非常满的，所以只能获得 [$74$ 分](https://www.luogu.com.cn/record/199581435)左右。

根据官方题解声称，此做法在随机选择树根的时候表现良好，可以获得 $94$ 分左右。

### 方法二

我们考虑一个常数更小的 $\log$，容易想到树剖。

考虑我们每次找一条从根开始的重链，计算新加的这个点到根的路径在重链上的哪个点岔开。通过询问点到链底的距离，这是简单的。

然后把这个点的另一子树当作新的树，递归下去查询即可。如果不存在另一子树或者接在链底上就可以直接连接了。

可以发现这样每个点产生的次数是它在原树上到根的轻边数量，也就是树剖 $\log$，常数小到可以通过本题。

实现时需要特殊注意一下根作为三度点时的情况，此时从根上岔开的边有两种选择，不能直接递归。但是我们多使用一次询问问出在哪个就可以了。可以发现产生这种问题的点最多也只有整棵树的一半，所以无伤大雅，仍然可以通过。

std 写法好像有点丑，用了 $6200$ 次左右通过。我写的在 $5200$ 次左右就[过了](https://www.luogu.com.cn/record/199672361)。

```cpp
long long get_distance(int X, int Y);
ll rdis[N];
pll dis[N];
int rt;
vector <pii> t[N];
int siz[N];
int hson[N];
ll w[N];
vector <pll> pat;
int u;
void dfs(int x){
    siz[x]=1;
    int idx=0;
    for(auto y:t[x]){
        dfs(y.fi);
        if(siz[y.fi]>siz[idx]) idx=y.fi,w[x]=y.se;
        siz[x]+=siz[y.fi];
    }
    hson[x]=idx;
}
int route(int x,ll d){
    pat.pb(mp(x,d));
    if(hson[x]) return route(hson[x],d+w[x]);
    else return x;
}
void divide(int x){
    pat.clear();
    dfs(x);
    int bom=route(x,0);
    ll all=pat.back().se;
    ll d=get_distance(u,bom);
    fr1(i,0,(int)pat.size()-1){
        if(d+all-2*(all-pat[i].se)==rdis[u]-rdis[x]){
            int id=pat[i].fi;
            ll w=rdis[u]-rdis[id];
            if(t[id].size()>=2){
                if(pat[i+1].fi==t[id][0].fi) swap(t[id][0],t[id][1]);
                if(id==1){
                    if(t[id].size()==3) if(pat[i+1].fi==t[id][1].fi) swap(t[id][1],t[id][2]);
                    ll td0=get_distance(t[id][0].fi,u);
                    if(rdis[u]==td0+t[id][0].se) divide(t[id][0].fi);
                    else{
                        if(t[id].size()==3) divide(t[id][1].fi);    
                        else t[id].pb(mp(u,w));
                    }
                    return;
                }
                divide(t[id][0].fi);
                return;
            }
            else{
                t[id].pb(mp(u,w));
                return;
            }
        }
    }
}
void find_roads(int n, int Q, int A[], int B[], int W[]){
    rt=1;
    fr1(i,2,n) rdis[i]=dis[i].fi=get_distance(rt,i),dis[i].se=i;
    sort(dis+2,dis+n+1);
    fr1(i,2,n){
        u=dis[i].se;
        divide(1);
    }
    int tot=-1;
    fr1(i,1,n){
        for(auto y:t[i]){
            tot++;
            A[tot]=i,B[tot]=y.fi,W[tot]=y.se;
        }
    }
}
```

---

