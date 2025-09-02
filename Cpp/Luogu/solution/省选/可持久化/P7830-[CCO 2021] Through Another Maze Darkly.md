# [CCO 2021] Through Another Maze Darkly

## 题目背景

**警告：滥用本题评测将被封号！**

## 题目描述

黑暗迷宫是一个树形结构，有 $n$ 个房间和 $n - 1$ 个走廊，房间编号 $1, 2, \cdots, n$。

黑暗迷宫里面漆黑一片，你看不见自己在哪里。为了辨别方向，每个房间有一个激光指示器，初始指向连接这个房间的某一个走廊。你重复执行如下策略行动：

- 将当前房间的激光指示器按顺时针方向旋转到下一个走廊
- 沿着激光指示器指向的走廊走到另一个房间

你打算从编号为 $1$ 的房间开始，将这个策略重复执行 $k$ 次，想知道自己会到达哪个房间。你觉得这个问题太简单了，于是进行了 $q$ 次询问。每次询问是相互独立的，即激光指示器每次都会回到初始状态。

## 说明/提示

#### 样例 #1 解释
初始激光指示器的指向如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/2k48xyl0.png)
#### 数据范围
对于 $\frac{7}{45}$ 的数据，第 $i$ 个房间连接第 $i - 1$ 和第 $i + 1$ 个房间（如果这两个房间存在）；

对于另 $\frac{14}{45}$ 的数据，$2 \leq n \leq 2 \times 10^3$，$1 \leq q \leq 2 \times 10^3$；

对于另 $\frac{4}{15}$ 的数据，$q = 1$；

对于 $100\%$ 的数据，$2 \leq n \leq 8 \times 10^5$，$1 \leq q \leq 8 \times 10^5$，$1 \leq k \leq 10^{15}$，保证数据给出的是**一棵树**。
#### 题目来源
[CCO2021](https://cemc.math.uwaterloo.ca/contests/computing/2021/index.html) D1T3

## 样例 #1

### 输入

```
5 6
1 2
3 3 1 4
1 2
2 5 2
1 4
1
2
3
4
5
6```

### 输出

```
2
1
2
4
2
3```

# 题解

## 作者：lgswdn_SA (赞：18)

不需要任何 log 数据结构的做法。

首先考虑一个暴力结论：我们走有限次之后（实际上是 $O(n^2)$，极限情况是都指向子节点的链），一定会达成以下的局面：所有节点（除了跟节点）都指向父亲。然后就会根据欧拉游走序进行循环了。所以现在的重点是要处理出在循环之前的情况。

注意，在这个欧拉游走序中，我们每个节点的儿子顺序，应该是在原出边顺序中，从父节点之后的那个儿子开始，父节点之前的那个儿子结束，形成的一个顺序。

我们把其最终结果的欧拉游走序给求出来。如果我们在某一时刻”解决“了一个树上节点，那么在之后的时刻，遇到这个点就直接按照欧拉游走序上的往后走就行了。所以对于欧拉序上的每一个位置，我们可以打一个标记。而当我们对于 $u$，它走出了自己的子树，那么此时它一定会指向自己的父节点，于是自己就被解决了，把自己在欧拉序上出现的位置的标记全部删掉。

我们假设我们现在在欧拉序的没有标记的 $x$ 上，那么我们会一路走到第一个有标记的位置 $y$。此时 $y$ 一定还没有被经过（因为如果一个点有标记那么子树内的点也必然有标记，所以 $x$ 在 $y$ 子树外，所以如果以前经过过 $y$ 那么就一定走出过 $y$ 的子树，与其未被解决矛盾）。所以此时我们就可以跳到 $y$ 的在原树上的第二个出边处，然后继续往下走（因为会直接转到第二个孩子）。其实在此时，我们就已经可以把 $y$ 的节点解决了。因为从此之后，它的遍历顺序就和我们最终的欧拉游走序相同了。

所以我们的操作就是：对于 $x$，我们先删除 $x$ 的所有标记，跳到 $x$ 在原树上的第二个出边处（即欧拉序上那个点在 $x$ 之后的最近出现的位置）。然后当 $x$ 上没有标记（即其原来的第二个儿子为自己的父节点，或者自己是叶节点），就顺序走到下一个标记处。维护每个节点之后的第一个标记，这可以直接上一个并查集。而我们同时也维护时间。走到下一个节点的时间区间 $[l,r]$ 可能会囊括一些问询，而这段时间内走的是一段连续的欧拉序，我们把这些问询给处理掉即可。

复杂度正确，因为我们每次遍历到标记节点就会删除一些标记，而两次标记访问之间最多有一次非标记访问。

要对问询排序所以得勉为其难地带个 log。

复杂度 $O(n\alpha(n)+q\log q)$。

---

Update："你可以基排的"，所以可以直接做到 $O(n\alpha(n)+q)$。

```cpp
const int N=1.6e6+9;

int n,Q,nxt[N],fa[N],dfn[N],tick,deg[N],tot,hd[N],lst[N],fst[N],ans[N],tag[N];
pii q[N];
vi pos[N],t[N];
struct edge {int to,nxt;} e[N];

int find(int x) {return nxt[x]==x?x:nxt[x]=find(nxt[x]);}
int dis(int x,int y) {
    if(x<y) return y-x;
    else return tick-x+y;
}
void del(int x) {nxt[x]=find(x%tick+1); tag[x]=0;}
void dfs1(int u) {for(int v:t[u]) if(v!=fa[u]) fa[v]=u, dfs1(v);}
int calc(int x,int y) {
    x+=y, x%=tick; if(x==0) x=tick;
    return dfn[x];
}
void dfs2(int u) {
    dfn[++tick]=u; pos[u].eb(tick); fst[u]=tick;
    for(int i=hd[u];i;i=e[i].nxt) {
        dfs2(e[i].to);
        dfn[++tick]=u; pos[u].eb(tick);
    }
}
void work(int p,int time,int qt) {
    int u=dfn[p];
    if(tag[p]) {
        for(int x:pos[u]) del(x);
        while(qt<=Q&&q[qt].fi==time) ans[q[qt].se]=u, qt++;
        if(t[u].size()==1) work(t[u][0],time+1,qt);
        else work(t[u][1],time+1,qt);
    } else {
        int np=find(p);
        if(!tag[np]) {
            while(qt<=Q) ans[q[qt].se]=calc(p,q[qt].fi-time), qt++;
            return;
        }
        int nt=time+dis(p,np);
        while(qt<=Q&&q[qt].fi<nt) ans[q[qt].se]=calc(p,q[qt].fi-time), qt++;
        work(np,nt,qt);
    }
}

signed main() {
    n=read(), Q=read();
    rep(i,1,n) {
        deg[i]=read();
        rep(j,1,deg[i]) t[i].eb(read());
    }
    dfs1(1);
    rep(i,1,n) {
        int pos=0;
        if(i!=1) {while(t[i][pos]!=fa[i]) pos++;}
        pos=(pos+1)%deg[i], hd[i]=tot+1;
        rep(j,1,deg[i]) {
            if(t[i][pos]==fa[i]) break;
            e[++tot]=(edge){t[i][pos],tot+1};
            pos=(pos+1)%deg[i];
        }
        if(hd[i]>tot) hd[i]=0;
        else e[tot].nxt=0;
    }
    dfs2(1); tick--;
    per(i,tick,1) {
        int u=dfn[i]; lst[u]=i;
        if(fst[u]==i) {
            for(int &x:t[u]) {
                if(!lst[x]) x=fst[x];
                else x=lst[x];
            }
        }
    }
    rep(i,1,Q) q[i].fi=read(), q[i].se=i;
    sort(q+1,q+Q+1);
    rep(i,1,tick) nxt[i]=i, tag[i]=1;
    work(1,0,1);
    rep(i,1,Q) printf("%lld\n",ans[i]);
    return 0;
}
```

---

## 作者：jjsnam (赞：11)

## 写在前面

本着学习主席树的目的找到了这道题，本来以为黑题标着主席树的 tag 蕴含了主席树的什么高深套路，结果没想到这道题难在了思维和代码上。写一篇题解加深理解，同时补一个主席树的代码，这样题解区就有离线和在线两种做法了。

思路和代码一部分参考了他人题解。

## 分析

其实一看到这题，有一种思路是考虑倍增。我们尝试用倍增预处理出每个点走特定步数能到达的位置，然后处理询问。不过经过思考发现这些点来回来去的并不具备连边和转移的好性质，所以这个思路我们先放弃。

但是通过刚才的思路给了我们一个启发：**操作可能有周期性**。那我们就来尝试构造这个周期。

对于一个非根节点，它的激光可以指向它的父亲和儿子。根据经验，比较特殊的一定**跟父亲有关**，因为儿子没有普适性，有可能很多，也可能没有，但是父亲只有一个。

与父亲有关，那么我们可以让这个节点的激光指示器**一开始就指向自己的父亲**。然后我们发现了很好的性质：

-	这个节点从祖先到第一次访问该节点，激光指示器会顺时针转到第一个儿子，然后遍历这个儿子（**不管这个子树内每个节点的激光指示器状态如何，最终都会从子树中退出**，*因为无论激光指示器转多少都会有一次指向父亲，就会回退* ），之后回到该节点，再遍历第二个儿子，以此类推，顺时针转一圈，**将所有儿子遍历一遍后**激光指示器将再次指向父亲，回退。

这样的话，如果每个非根节点都指向它的父亲（这是我们**钦定的条件**，根节点不用管），那么我们从根出发可以完整遍历一整棵树。

分析发现，每条边只会下行上行各一次，所以最后我们的访问序列长度是 $2n-2$，又由于激光指示器顺时针旋转的性质，每次遍历的顺序是一定的，所以我们得到了一个**周期序列**。

------------

一个优秀的序列被构造完了，然而一开始每个节点激光指示器的状态可不保证指向父亲。接下来我们思考是不是任意状态的树最终都会指向我们这个最终循环序列。

在上一回合我们知道了一个非根节点的激光指示器最终一定有一次会指向它的父亲，从而回退。进而我们假设这个节点的祖先节点已经满足了 第一次访问都指向其父亲 的条件，那么这个节点再指向其父亲后回退，也就是说**下一次遍历它也成为了符合条件的一部分**。

进而我们可以找到一种扩展方式：**每次把新的符合条件的节点作为下一次扩展的起点**。这样我们就保证了每次一层层扩展，不会有遗漏，最后使整棵树符合我们刚才构造的样子，进入周期循环。

而且又因为题目中顺时针旋转这个性质，每次扩展后的访问序列**一定是最终周期序列的子序列**。因为每个儿子的相对遍历顺序不会改变。

来看看复杂度是否可以接受。每次扩展必然有至少一个节点通过旋转满足了条件，因而最终总的扩展次数不会超过 $n$ 次，也就是说我们的访问序列不会有多于 $n$ 个子版本就会到达最终版本，进入循环。

同样的，经由思考我们会发现，每个节点的一般遍历方式其实类似下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/25uro43i.png)

遍历一次变成符合要求，下次再把剩下的未遍历的儿子遍历完，我们可以通过一些方法使这个节点的每个儿子只遍历一次，进而保证了遍历的时间复杂度是 $O(n)$ 级别。同时我们对访问序列的修改次数也因此控制在了 $O(n)$ 级别。

## 实现

思路大抵明确了，接下来我们看看实现有哪些困难。

因为一开始每次的询问序列都是最终周期序列的子序列，所以我们可以一开始先把这个周期序列求出来。方法很简单，按照顺时针顺序存图（为了方便我们使用 ```vector```，毕竟时限 8s 完全不虚），先找到指向父亲节点的位置，然后假定现在一开始就指向父节点，那么从父节点其向右循环遍历直到再次遍历到父节点即可。注意对于一个节点每次遍历一个儿子都会再访问一次该节点，访问序列要加入一个该节点。


------------


接下来是难点。如何把奇形怪状的树扩展成最终形态？我们通过样例来浅析一下。

![](https://cdn.luogu.com.cn/upload/image_hosting/120gklhm.png)

上图是描绘了树，以及我们的序列，括号表示起点，不在序列中。

比如，第一次扩展，$2$ 号点在到达后就指向其父亲，回退，但是可以作为下一次扩展的点。**注意此时对序列的更改是在最后增加了一个** $2$。这里可以这么理解：$2$ 有儿子没遍历，但保证**已经遍历过的儿子是原遍历顺序的后缀**，所以为了还原序列，逆时针反着来所以**倒序还原 $2$ 的位置**。对于 $4$ 同理，大家可以自行模拟。

为了实现这个功能，我们可以在一开始处理最终序列时就记下每个点在最终访问序列中的位置，然后在扩展时倒序还原即可。



------------


然后对于每次扩展，只会在原先序列上再还原一部分，仍然有一部分不变，这就让我们想到了每次扩展只记录与原先版本不同之处，进而想到了对这个序列**进行可持久化**。那么我们可以通过维护一个该序列长度的主席树，每次更改就改一点就行，又因为我们通过方法保证了不会重复遍历任何节点，所以扩展的时空复杂度都是 $O(n\log n)$。

------------

对于最后的询问，首先明确每次扩展还是从根节点开始的，所以虽然每次扩展相对于前一次访问序列的变化不多，但是询问时整个访问序列都要走一遍。所以我们可以把所有可能的访问序列长度记下来并前缀和处理，用的时候二分找到这个序列在主席树上查询即可，这样就是经典第 $k$ 大问题。如果说 $k$ 很大，以至于已经扩展到了最终的周期序列，那么我们就可以通过取模运算做到 $O(1)$ 查询了。

然后就没啥要嘱咐的了，具体实现看代码，注意每个变量的含义，有一些实现我会写在注释里。

## 代码

人傻常数大，也可能是因为主席树空间占的大所以跑得慢，不过理论复杂度真的是 $O(n\log n)$……

```cpp
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>

#define mid ((l + r) >> 1)

using namespace std;
typedef long long ll;
const int maxn = 800005;

struct Node{
    int ls, rs;
    int cnt;//记录[l,r]区间里已经还原了多少元素
}tr[(maxn * 2) * (4 + 20)];//主席树，注意最终序列的长度是 2n-2，所以相应的也要扩倍
int root[maxn << 1], idx;
/* 存图数组；记录每个点在序列中的所有位置（倒序还原）；下一次需要扩展的点 */
vector<int> to[maxn], pos[maxn], ne;
int n, Q, m;//m记录的是扩展了多少版本
int seq[maxn << 1], len;//最终序列
int fa[maxn], ind[maxn];//记录父亲；记录终止位置（应该停在哪）
int now[maxn], tot;//记录现在遍历到哪个位置；
ll sum[maxn];//每个版本有多少步的前缀和
queue<int> q;

/* 可持久化线段树 */
int build(int l, int r){
    int p = ++ idx;
    if (l == r){
        return p;
    }
    tr[p].ls = build(l, mid), tr[p].rs = build(mid + 1, r);
    return p;
}

int insert(int p, int l, int r, int x){//还原x位置
    int q = ++ idx;
    tr[q] = tr[p];
    if (l == r){
        tr[q].cnt = 1;
        return q;
    }
    if (x <= mid) tr[q].ls = insert(tr[p].ls, l, mid, x);
    else tr[q].rs = insert(tr[p].rs, mid + 1, r, x);
    tr[q].cnt = tr[tr[q].ls].cnt + tr[tr[q].rs].cnt;
    return q;
}

int query(int p, int l, int r, int k){//Kth problem
    if (l == r){
        return l;
    }
    int cnt = tr[tr[p].ls].cnt;
    if (cnt >= k) return query(tr[p].ls, l, mid, k);
    else return query(tr[p].rs, mid + 1, r, k - cnt);
}

/* 扩展整棵树 */
void init(int u, int _fa){//先找到每个节点的父亲
    fa[u] = _fa;
    for (int i = 0; i < to[u].size(); i ++){
        int v = to[u][i];
        if (v == fa[u]){
            ind[u] = i;//记录最终的起始位置，也应该是旋转一圈的终点
            continue;
        }
        init(v, u);
    }
}

void get(int u){//得到最终序列
    /* u > 1 是因为第一次根作为起点不算在访问序列中 */
    if (u > 1) seq[++ len] = u, pos[u].push_back(len);
    int i = ind[u];
    while (true){
        i ++, i %= to[u].size();
        int v = to[u][i];
        if (i == ind[u] && u > 1) break;//非根节点，指向父亲一定要回退了
        get(v);
        seq[++ len] = u, pos[u].push_back(len);
        if (i == ind[u] && u == 1) break;//根节点，它没有父亲，所以说退出条件是再次指向起点
    }
}

void dfs(int u, int t){
    now[u] ++, now[u] %= to[u].size();//访问一次就要转一次
    if (u != t){//上一次在t停止，这一次从t扩展，所以这一次t不算在序列中
        root[m] = insert(root[m], 1, len, *pos[u].rbegin());
        pos[u].pop_back();
    }
    if (now[u] == ind[u] && u != t){//指向父节点，下一轮可完整扩展子树
        ne.push_back(u);
        return;
    }
    int i = now[u] - 1;
    int back_up = now[u];//备份
    while (true){
        i ++, i %= to[u].size(), now[u] = i;
        int v = to[u][i];
        if (i == ind[u] && u > 1) break;
        dfs(v, t);
        root[m] = insert(root[m], 1, len, *pos[u].rbegin());
        pos[u].pop_back();
        if (i == ind[u] && u == 1) break;
    }
    ind[u] = back_up;
    /* 注意ind[]的实际意义：
        即为一次遍历的终点（不包括该点）。ind[]本来记录的是父亲的位置，此处已经转一圈在父节点位置停止，
        那么下一次就是扩展这个点了，为了保证复杂度，即之后不会重复遍历以前的子树，由于是同一方向（顺时针），
        所以这一次的起点就是下一次的终点，ind[]改变为原来的起点，也就是我们刚才的备份 */
    if (!pos[u].empty()) ne.push_back(u);//还没完，下一轮还要从此扩展
    return;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n >> Q;
    for (int u = 1, k, v; u <= n; u ++){
        cin >> k;
        while (k --){
            cin >> v;
            to[u].push_back(v);
        }
    }

    init(1, 0), get(1);
    q.push(1), root[0] = build(1, len);
    while (!q.empty()){//类似于一个BFS里面套了DFS
        /* 继承上一个版本，然后这个扩展里的所有修改都对自身进行，因为查询时本次扩展是一个整体 */
        m ++, root[m] = root[m - 1];

        while (!q.empty()){
            int u = q.front();
            q.pop();
            dfs(u, u);
        }
        for (vector<int>::iterator it = ne.begin(); it != ne.end(); it ++){
            q.push(*it);//把下一轮可扩展的点入队
        }
        ne.clear();
        sum[m] = sum[m - 1] + tr[root[m]].cnt;
        if (tr[root[m]].cnt == len) break;
    }

    ll k;
    while (Q --){
        cin >> k;
        int t = lower_bound(sum + 1, sum + m + 1, k) - sum;//找到查询位置
        k -= sum[t - 1];//减去前面的贡献
        if (t < m){
            cout << seq[query(root[t], 1, len, k)] << endl;
        }
        else{//进入最终的循环
            k %= len;
            if (k == 0) k = len;
            cout << seq[k] << endl;
        }
    }

    return 0;
}
```

## 总结

构造循环，尝试导向循环，以及注意应用顺时针旋转的性质。是道很好的思维题。不过写完题解发现也不是那么难理解，我也是能弄懂黑题的人了hhhhh

---

## 作者：Iceturky (赞：4)

#### UPD:更新了部分代码

[Through Another Maze Darkly](https://www.luogu.com.cn/problem/P7830)

很有意思的一道思维题。

无论是思路上还是实现上。

此篇题解重点在如何**实现**题目相关查询上。

首先发现只要时间够长，每一个点都会被经过。

手摸样例观察性质，猜测其最终一定会**进入一个周期**。

一个感性的证明：

> 对于一个点，其只能从其父亲到达，且若干时刻后一定会再次回到其父亲。考虑v回到父亲时的灯的方向，显然是指向其父亲。
>
>在灯指向父亲后，再次由父亲遍历到此节点时，其一定能遍历到其所有的儿子。遍历完其为根的子树后，灯指向父亲，走到父亲节点，退出这棵子树。此时该节点灯仍指向父亲。
>
>对于灯指向父亲的点，其遍历相邻点的遍历顺序唯一。
>
>发现当所有节点的灯都指向父亲后（发现此状态一定能够到达），遍历序列必定进入周期，即在一定要求下的原图的欧拉序。

对于周期内的点较为好求，如何处理周期前的点？

我们定义灯指向父亲的点是好点，没有指向父亲的点是坏点。

定义从 $1$ 结点出发后又回到 $1$ 节点为一次遍历，一次遍历的遍历顺序为此次遍历经过的点编号依次排列生成的序列（此点编号在被遍历到和由儿子回溯都加入一次）（即为欧拉序）。

考虑每一个点遍历时能访问到的儿子节点。

定义顺时针访问顺序为此点在另一点顺时针方向上，从激光灯指向的下一个节点开始编号的号码大小。

若此点为好点，则所有儿子一定能被访问。

若此点为坏点，则会从灯初始指向节点的下一个节点开始访问，直到访问到父亲节点，此时会退出这棵子树，剩下的顺时针访问顺序在父亲后的儿子节点则不会被访问。（注意到在退出时灯指向父亲，下一次访问此点则会从顺时针访问顺序比父亲恰好大一的点开始访问，一直访问到访问顺序比父亲恰好小一的点，即所有儿子又一定能被访问）

当一个点所有儿子都能被访问时，此点一定是好点。

观察坏点遍历过程发现，一个坏点在经过一次遍历后能变成好点。

观察好点遍历过程发现，一个好点永远不会变坏。

由于一棵子树的欧拉序连续，所以可以发现，每一次遍历的遍历顺序都是原图的欧拉序上的一个子序列。

在最后时刻，进入周期后，只有好点时，遍历序列就是原图的欧拉序。

### 由此我们转入维护欧拉序的子序列。

每次要找到欧拉序上的第一个坏点。

如何快速的向后跳，找第一个坏点？别急。你先别急。

这里的实现挺神奇的。

思考坏点的遍历过程（可以再看看上文），对于顺时针遍历顺序比其父亲小的坏点的儿子，在遍历坏点时会获得较高的遍历优先级，而顺时针遍历顺序比父亲大的儿子则在遍历坏点时不会被遍历。

如何将这样的过程转到欧拉序上？

可以发现，若所有的点都为好点，每一个点遍历自己儿子的顺序是：

>顺时针遍历顺序比父亲大的儿子（从小往大）$\rightarrow$ 顺时针遍历顺序比父亲小的儿子（从小往大）$\rightarrow$ 回到父亲（回溯）

而对于坏点，其遍历顺序为：

>顺时针遍历顺序比父亲小的儿子（从小往大）$\rightarrow$ 回到父亲（回溯）（此时其变为好点）

坏点相当于跳过了在最终状态下优先级最高的顺时针遍历顺序比父亲大的儿子。

也即在欧拉序上跳过了遍历这些儿子所生成的遍历序列。

而在每次坏点被遍历，成为好点后，这些儿子生成的遍历序列相当于插入了此前的遍历序列。

插入操作太难维护，注意到最终状态是确定的，也即是原图的欧拉序。

可以用类似标记的方法，跳过所有没有打标记的点，直接找到第一个有标记的点，取消其标记。

每次的遍历顺序就是所有没有打标记的点。

因为每次标记只会消除不会再打上，可以考虑用并查集来加速这个跳标记的过程。

**在欧拉序上**，**初始**状态时，每一个初始状态下的**好点**并查集里的父亲都是欧拉序上的**下一个位置**，每一个初始状态下的**坏点**并查集里的父亲是**自己所在的位置**。

我们把并查集建在了欧拉序上。

这样每次执行并查集里的 `getfa` 操作就可以快速的找到下一个坏点。

相当于在原图中遍历到了下一个可以被遍历的坏点。

其中，好点 对应上文 **没有标记的点**，坏点 对应上文 **有标记的点**。

好点指向下一个位置 对应 没有标记的点不会停留，同时对应好点会直接按顺序遍历自己所有的儿子，坏点指向自己 对应 在自己位置停留，同时对应我们需要在此时分析坏点应遍历哪些儿子。

那么坏点变好即为更改其父亲为下一个位置。

对于好点，在并查集上就直接跳过去了，基本没有什么实现上的细节。

考虑坏点。

Q : 我们怎么从坏点出发找到下一个遍历的点？

观察坏点的遍历顺序。其顺时针遍历顺序比起父亲大的儿子都会被**跳过**，但其在后续遍历过程中则排在所有儿子的前面。这启发我们对每一个坏点构造一个指针，使其指向自己为坏点时遍历的第一个儿子（即**顺时针遍历顺序最小**的儿子）在欧拉序中出现的第一个位置（相当于遍历这个儿子）。

可以发现顺时针遍历顺序比其父亲还要大的坏点的儿子，欧拉序上在顺时针遍历顺序小的儿子的前面。

在跳到坏点时只需要跳到其这个顺时针遍历顺序最小儿子就能避免遍历到其遍历顺序大的儿子。

~~救命呀我要不认识遍历这个词了~~

Q : 我们需要让坏点在欧拉序中的所有位置都指向自身位置吗？（注意到一个点（除根）会在欧拉序上出现其度数次）

这样既繁琐又麻烦。

观察坏点的遍历过程，我们只需要在第一次遍历到坏点时知道此处为坏点就行，在后续由儿子回溯时不需考虑其好或坏。

对应于欧拉序上我们只让坏点**第一次出现的位置**并查集上的父亲指向自己。

Q : 那么在跳到坏点时应该做什么操作？

观察坏点的遍历过程，我们需要做的只有将其变成好点（并查集上指向下一个位置），然后跳到前文说的坏点遍历的第一个儿子即可。

Q : 怎么处理未进入循环区间时的询问？

可以发现，每次向后跳跃都是跳过了一段连续的区间（因并查集要不指向自身要不指向下一个位置），因此可以将询问离线，排序后用一个指针判断这个询问的时间是否已经达到，若达到则可以通过下标计算此询问所到达的点。

对于进入循环区间的点，减去前部分未进入造成的时间损耗，再模一个欧拉序长度知道其在欧拉序上的哪一个位置了。

代码

```cpp

const int N=8e5+5;

vector<int> e[N];//顺时针遍历顺序 

int dfn[2*N],tot;//欧拉序，两倍长度 

int fa[2*N];//并查集 

void init(int n){for(int i=1;i<=2*n;i++)fa[i]=i+1;}//初始化 
int getfa(int x){return fa[x]==x?x:fa[x]=getfa(fa[x]);}//路径压缩 

int fnum[N];//父亲编号在vector里的位置 

void dfs(int u,int faa)
{
	dfn[++tot]=u;
	if(u==1)//对根特殊处理，没有父亲 
		fnum[u]=-1;
	else
		for(int i=0;i<e[u].size();i++)
			if(e[u][i]==faa)//找到父亲的顺时针遍历顺序 
			{
				fnum[u]=i;
				break;
			}
	for(int i=fnum[u]+1;i<e[u].size();i++){//遍历顺序更大的点
		int v=e[u][i];
		dfs(v,u);
		dfn[++tot]=u;
	}
	for(int i=0;i<fnum[u];i++){//遍历顺序更小的点 
		int v=e[u][i];
		dfs(v,u);
		dfn[++tot]=u;
	}
}

struct qst{
	int w,id;
}q[N];//存储询问 

int ans[N];//答案 

bool cmp(qst aaa,qst bbb){return aaa.w<bbb.w;}

vector<int> stk[N];//寻找每一个坏点到达的第一个儿子 

int nxt[2*N];//坏点的指针 
bool tag[N];//在欧拉序中是否是第一次出现 

signed main()
{
	int n=read(),Q=read();
	for(int i=1;i<=n;i++)
	{
		int len=read()-1,fst=read();//第一个位置优先级最低，因为先转灯再走 
		while(len--)
			e[i].push_back(read());
		e[i].push_back(fst);//按照顺时针遍历顺序压入 
	}
	dfs(1,0);//求出原图的欧拉序（即每一个点都不考虑灯的方向，顺时针走的欧拉序） 
	init(n);//并查集初始化 
	for(int i=1;i<=Q;i++)
		q[i]={read(),i};//笔者这里开了define int long long 
	sort(q+1,q+1+Q,cmp);
	int num=-1;//坏点个数，dfn[1]也会被标记为坏点，提前减去 
	for(int i=1;i<=tot;i++){
		if(tag[dfn[i]]==0&&fnum[dfn[i]]!=e[dfn[i]].size()-1)//第一次出现且灯没有指向父亲 
			fa[i]=i,num++;//标记为坏点 
		tag[dfn[i]]=1;//出现过 
	}
	for(int i=tot;i>=1;i--)
		stk[dfn[i]].push_back(i);//把每一个点每次在欧拉序上的位置倒序压入 
	for(int i=1;i<=tot;i++)
		if(fa[i]==i)
			nxt[i]=stk[dfn[i]][fnum[dfn[i]]];//坏点下一个要访问的点，顺时针遍历顺序恰好比父亲大1的儿子
	fa[1]=2;fa[tot]=tot;
   nxt[tot]=tot;//可能跳到的唯一好点，特殊处理一下 
	
	//预处理结束
	
	//处理在周期外的遍历顺序 
	int d=0,p=1;//时间偏移量和询问指针 
	while(num>0)//还有坏点 
	{
		int nw=1;//当前节点 
		while(nw<tot)//因为欧拉序首尾相连，最后一个位置没有贡献 
		{
			int fff=getfa(nw);//下一个坏点 
			int len=fff-nw;//跳跃的区间长度 
			while(len+d>=q[p].w&&p<=Q)//处理满足条件的询问 
				ans[q[p].id]=dfn[nw+q[p].w-d],p++;
			if(fff!=tot)
				fa[fff]=fff+1,num--;//变成好点 
			d+=len;//时间增加 
			nw=nxt[fff];//跳到坏点第一个被遍历的儿子 
		}
	}
	while(p<=Q)//处理在周期里的遍历顺序 
		ans[q[p].id]=dfn[(q[p].w-d-1)%(tot-1)+2],p++;//笔者加载的欧拉序长度为2n-1,但实际上用到的只有2n-2个数，因欧拉序首尾相连
	for(int i=1;i<=Q;i++)
		print(ans[i]),pc('\n');
	return 0;
}
```

---

## 作者：EuphoricStar (赞：2)

被联考创出 shit 了。

考虑一种极限情况：每个点指向父亲。那么这种情况我们会顺着欧拉序完整地把整棵树都走一遍。

但是初始的时候不一定每个点都指向父亲。发现我们走过 $O(n^2)$ 步就能到达上面的极限情况。比较显然，因为每次扩展至少使一个点从不指向父亲变成指向父亲（称一次扩展为，不处于极限情况时，根结点走完一遍又回到自己的过程）。

考虑若一个点初始不指向父亲，那么第一次扩展到它时，它还没来得及扩展所有子结点就回到父亲了。但是第二次扩展可以扩展所有子结点。所以一个点至多需要访问 $2$ 次。基于此考虑用一个队列维护还需要被访问的点，若遇到一个点没扩展完所有子结点就返回，就把它 `push` 进队列。

考虑如何回答询问。注意到每次扩展经过的结点编号序列，一定是最终欧拉序的子序列。于是我们把询问离线下来，扩展时把对应点的对应位置插入序列，查询就查一个下标第 $k$ 大。可以使用树状数组维护。对于走到第 $k$ 步时已经把整棵树扩展完的询问，因为它的周期是整棵树的欧拉序，所以也可以快速回答。

时间复杂度 $O((n + q) \log n + q \log q)$。

```cpp
// Problem: P7830 [CCO2021] Through Another Maze Darkly
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P7830
// Memory Limit: 1 MB
// Time Limit: 8000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define pb emplace_back
#define fst first
#define scd second
#define mkp make_pair
#define mems(a, x) memset((a), (x), sizeof(a))

using namespace std;
typedef long long ll;
typedef double db;
typedef unsigned long long ull;
typedef long double ldb;
typedef pair<ll, ll> pii;

#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 22, stdin), p1 == p2) ? EOF : *p1++)
char buf[1 << 22], *p1 = buf, *p2 = buf;
inline ll read() {
    char c = getchar();
    ll x = 0;
    for (; !isdigit(c); c = getchar()) ;
    for (; isdigit(c); c = getchar()) x = (x << 1) + (x << 3) + (c ^ 48);
    return x;
}

const int maxn = 1600100;

ll n, m, tt, fa[maxn], fd[maxn], ans[maxn], pt[maxn], a[maxn], tot, b[maxn], cnt;
bool vis[maxn];
pii qq[maxn];
vector<pii> G[maxn];
vector<int> vc[maxn];

void dfs(int u, int f) {
	for (pii &p : G[u]) {
		int v = p.fst;
		if (v == f) {
			p.scd = fd[u];
			continue;
		}
		p.scd = ++tt;
		fa[v] = u;
		fd[v] = tt;
		dfs(v, u);
	}
}

void dfs2(int u, int fa) {
	int t = pt[u], len = (int)G[u].size();
	while (1) {
		pt[u] = (pt[u] + 1) % len;
		if (pt[u] == t && u > 1) {
			break;
		}
		int v = G[u][pt[u]].fst;
		a[++tot] = v;
		b[tot] = G[u][pt[u]].scd;
		dfs2(v, u);
		a[++tot] = u;
		b[tot] = G[u][pt[u]].scd;
		if (pt[u] == t && u == 1) {
			break;
		}
	}
}

namespace BIT {
	int c[maxn];
	
	inline void update(int x, int d) {
		++cnt;
		for (int i = x; i <= n * 2 - 2; i += (i & (-i))) {
			c[i] += d;
		}
	}
	
	inline int kth(int k) {
		int p = 0;
		for (int i = __lg(n * 2 - 2); ~i; --i) {
			if (p + (1 << i) <= n * 2 - 2 && c[p + (1 << i)] < k) {
				p += (1 << i);
				k -= c[p];
			}
		}
		return p + 1;
	}
}

vector<int> nxt;

void dfs3(int u) {
	int len = (int)G[u].size();
	while (1) {
		pt[u] = (pt[u] + 1) % len;
		int v = G[u][pt[u]].fst, id = G[u][pt[u]].scd;
		if (vis[id]) {
			break;
		}
		if (v == fa[u]) {
			nxt.pb(u);
			break;
		}
		BIT::update(vc[id][0], 1);
		dfs3(v);
		vis[id] = 1;
		BIT::update(vc[id][1], 1);
	}
}

void solve() {
	n = read();
	m = read();
	for (int i = 1, k; i <= n; ++i) {
		k = read();
		while (k--) {
			G[i].pb(read(), 0);
		}
	}
	dfs(1, -1);
	for (int i = 2; i <= n; ++i) {
		for (int j = 0; j < (int)G[i].size(); ++j) {
			if (G[i][j].fst == fa[i]) {
				pt[i] = j;
				break;
			}
		}
	}
	dfs2(1, -1);
	for (int i = 1; i <= tot; ++i) {
		vc[b[i]].pb(i);
	}
	for (int i = 1; i <= m; ++i) {
		qq[i] = mkp(read(), i);
	}
	sort(qq + 1, qq + m + 1);
	mems(pt, 0);
	ll s = 0, j = 1;
	queue<int> q;
	q.push(1);
	while (cnt < tot) {
		ll lst = s;
		vector<int>().swap(nxt);
		while (q.size()) {
			int u = q.front();
			q.pop();
			dfs3(u);
		}
		for (int x : nxt) {
			q.push(x);
		}
		s += cnt;
		while (j <= m && qq[j].fst <= s) {
			ans[qq[j].scd] = a[BIT::kth(qq[j].fst - lst)];
			++j;
		}
	}
	while (j <= m) {
		ans[qq[j].scd] = a[(qq[j].fst - s - 1) % tot + 1];
		++j;
	}
	for (int i = 1; i <= m; ++i) {
		printf("%lld\n", ans[i]);
	}
}

int main() {
	int T = 1;
	// scanf("%d", &T);
	while (T--) {
		solve();
	}
	return 0;
}

```


---

## 作者：StayAlone (赞：1)

很牛的思维题。

考虑当进入一个点时，无论这个点初始指向哪里，从该点退出时，该点显然指向父亲。故一个点进出过一次后，以后肯定永远指向父亲，最终形成一个所有点都指向父亲的局面（除了根）。此后，行走序列即欧拉游走序，可以容易地查询；重点放在维护形成该局面前的情况。

定义从 $1$ 出发再回到 $1$ 为一轮，$\mathcal O(n)$ 轮后即到达循环局面。

考虑维护每一轮的状态。当进入一个点时，它扩展的肯定是顺时针下，靠后的一段儿子，显然可以预处理出来。据此也容易发现，每一轮的结果都是欧拉游走序的一个子序列，因此只需在这个序列上维护插入操作，直到整个序列都被插入。

插入的过程就是按顺序跳过已经更新过的点，然后扩展相应的儿子。可用连续段并查集维护做到严格线性。

询问可以离线下来排序，当在并查集上跳过一段时，把这一段的询问处理掉即可。

时间复杂度 $\mathcal O(n+q\log q)$，瓶颈在排序。

[AC record](https://www.luogu.com.cn/record/219377151)

```cpp
int n, m, tot, qcnt = -1, pa[MAXN], seq[MAXN], ans[MAXN], vis[MAXN], nxt[MAXN], fid[MAXN];
vector <int> to[MAXN], pos[MAXN]; pll qu[MAXN];

il void dfs(int x, int p) {
    int id = -1, len = to[seq[tot++] = x].size();
    rep1(i, 0, len - 1) if (to[x][i] == p) id = i;
    fid[x] = id;
    rep1(i, 2, len + (x == 1)) dfs(to[x][(++id) %= len], x), seq[tot++] = x;
}

il int fpa(int x) {
    return x ^ pa[x] ? pa[x] = fpa(pa[x]) : x;
}

int main() {
    read(n, m);
    rep1(i, 1, n) {
        to[i].resize(read());
        for (auto &v : to[i]) read(v);
        to[i].eb(to[i][0]); to[i].erase(begin(to[i]));
    } dfs(1, 0); --tot; vis[1] = 1;
    rep2(i, tot, 0) pos[seq[i]].eb(i);
    rep1(i, 0, tot) {
    	if (vis[seq[i]]) pa[i] = i + 1, ++qcnt;
    	else pa[i] = i, vis[seq[i]] = 1, nxt[i] = pos[seq[i]][fid[seq[i]]];
	} pa[tot] = tot;
    rep1(i, 1, m) read(qu[qu[i].snd = i].fst);
    sort(qu + 1, qu + 1 + m); int qid = 0; ll psum = 0;
    while (qcnt ^ tot) {
        int nw = 0;
        while (nw <= tot) {
            int to = fpa(nw), len = to - nw;
            while (qid < m && psum + len >= qu[qid + 1].fst) ++qid, ans[qu[qid].snd] = seq[nw + qu[qid].fst - psum];
            psum += len;
            if (to == tot) break;
            pa[to] = to + 1, ++qcnt;
			nw = nxt[to];
        }
    }
    while (qid < m) {
        qu[++qid].fst -= psum;
        ans[qu[qid].snd] = seq[(qu[qid].fst - 1) % tot + 1];
    }
    rep1(i, 1, m) printf("%d\n", ans[i]);
    return 0;
}
```

---

## 作者：Fucious_Yin (赞：1)

先给链接：[洛谷P7830](https://www.luogu.com.cn/problem/P7830) 和 [loj3579](https://loj.ac/p/3579)

巨牛题，被正虚像加强了一下搬到了尊贵的 _**CSP**_ 模拟赛 T2，笑点解析：cb 说模拟赛难度应为 2300-2600-2800-3000+。我一看诶这不是我们联考专题讲过的吗，回忆了一下当时思考~~找出当时课件~~然后当场把原题拿出来给他看。当时没补，这回完全得是自己写了笑哭。

***

给定一棵树，每个节点的边以序列的形式给出，每个节点有一个指针初始指向这个点的某一条边，每走到一个点时先将其指针拨动到下一条边（序列循环），然后沿着指针走到指向的节点。问你从一号节点开始走 $k$ 步会到达哪个节点。多测，询问互相独立。原题可以离线，加强后成了强制在线。

原题：$n,q \le 8 \times 10^5,k \le 10^{15}$

加强：$n,q \le 5 \times 10^5,k \le 10^{15}$，强制在线

***

首先我们发现一棵树一定是很重要的条件，同时这一题给出了一个关键的部分分提示：除了 $1$ 号节点，所有节点的指针初始指向父亲。这很牛啊，我们发现轨迹序列完全就是一个欧拉序且不断循环，这提示我们当所有指针指向父亲时后面就是容易处理的，称为终止状态。为了方便，我们称指针指向父亲时节点是黑的，反之是白的。特别的，根节点一直是黑的。

继续观察一般情况，我们走得一定是一个深搜状物，每次进入一个子树并再走出来后，子树内走过的节点一定都被染为黑色，那我们人脑玩一下在终止状态前的操作，就是一个不断向下染色的 dfs，就是说你会每次遍历已经指向父亲的所有黑节点，并拓展地走到他们下面还未走过的节点并把他们也染为黑色。我们称这样从 $1$ 开始 dfs 拓展并回到 $1$ 节点的一系列操作为一轮染色。显然我们会一轮一轮地染直到达到终止状态。

假设这个过程我们能够维护，那对于每组在线询问，我们就可以二分出它在那一轮染色中或是在终止态之后，前者在我们维护的数据结构中查询，后者直接减去前置操作数然后模欧拉序长度即可知道在欧拉序的哪个位置。

下面考虑怎么维护这一轮轮的染色。显然为了方便我们可以对边集序列进行循环位移，使得父亲节点位于最后一位（当然第零位也没问题）。我们考虑时刻维护黑连通快的欧拉序，发现每次向外 dfs 一个白点实际上是在当前欧拉序的某个位置插入一段新的小欧拉序，这要做到区间分裂和合并，很容易想到 FHQ 平衡树，又因为需要在线对每个历史版本访问，就上可持久化平衡树（不过大多数人写的是主席树，对整棵树的欧拉序动态开点，效果是一样的，我比较喜欢平衡树喵）。具体就是我们同时维护一个序列 $lf$ 记录这一轮要拓展 dfs 的节点，比如在上一轮中，一个节点 $x$ 被第一次访问，设其边集序列为 $e_{x,i}$，$i\in[0,len[x])$ 且 $e_{x,len[x]-1} = fa$，其中 $len[x]$ 为该节点边数，假设其指针 $pos_x$ 指向 $[0,len[x]-1)$ 中的一个位置，那么上一轮 dfs 后，这一个点仍有 $e_{x,j},j\in[0,pos_x]$ 这些儿子没有访问过，则他们就会在这一轮染色中被拓展。在这一次拓展 dfs 的时候再维护下一次要拓展的节点，并将本次多拓展出来的欧拉序并到大欧拉序上（注意可持久化）。还有很多细节，比如具体 dfs 的策略我记了一个 $ok_x$ 表示是否已被染黑，等等。可以手画一棵树手玩一下，也可以参考代码，我的代码还是很可读的。

显然最多只会扩展 $O(n)$ 轮，又由于每个点最多只会遍历两次（诸如上面举例的节点），所以 dfs 的次数总共也是 $O(n)$ 的，加上平衡树的 $\log$，总复杂度就是 $O(n \log n + q \log n)$。

这样这一题就在线做完了。显然离线直接按照 $k$ 排序就不用可持久化了。附上我 [loj的代码](https://loj.ac/s/2162631)。

***

搬题搬成了在树上巡回吃酱油面，下次再想个背景就把他搬到别的地方去 qwq。

在黑暗中走出另一个迷宫。

~~~cpp
// way home after the last query,
// turn over and set up to a new journey !
~~~

这是代码里即兴随便写的，这下知道为什么要把返回的指针放在最后了吧。信达雅翻译就是：

终焉亦是归去，轮回再起一局

---

## 作者：mRXxy0o0 (赞：1)

说明了妙妙题是需要手玩的（确信）。

# 分析

考虑会不会出现循环，很明显是有的。不妨把原图视作一颗以 $1$ 为根的有根树。那么“循环”就可以认为是从 $1$ 开始，经过一些路线回到 $1$，且每个点的指示器方向不变。据此，每个点的指示器最终一定指向其父亲。简单思考发现这样确实是一个循环。

考虑进入循环前的一部分，已经可以循环的点一定是从根开始，逐步扩大的，且已经开始循环的点经过一次完整的遍历不会再改变了。所以，我们可以维护每进行新一轮遍历，新增了哪些点进入循环。因为每个点只会被新增一次，所以复杂度是有保证的。

用主席树维护这个神奇的遍历序列就好。主要难点可能在走出第一步和优美地求出新增的点。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=8e5+10;
int n,m,q,fa[N],tot,pf[N],a[N<<1],len,root[N],nw[N];
ll s[N];
vector<int>G[N],hav,ne,pos[N];
struct node{
	int ls,rs,sum;
}tr[N<<6];
inline void build(int &u,int l,int r){
	u=++tot;
	if(l==r) return ;
	int mid=l+r>>1;
	build(tr[u].ls,l,mid);
	build(tr[u].rs,mid+1,r);
}
inline void mdf(int &u,int v,int l,int r,int x){
	u=++tot;
	tr[u]=tr[v];
	++tr[u].sum;
	if(l==r) return ;
	int mid=l+r>>1;
	if(x<=mid) mdf(tr[u].ls,tr[v].ls,l,mid,x);
	else mdf(tr[u].rs,tr[v].rs,mid+1,r,x);
}
inline int query(int u,int l,int r,int x){
	if(l==r) return l;
	int mid=l+r>>1;
	if(x<=tr[tr[u].ls].sum) return query(tr[u].ls,l,mid,x);
	return query(tr[u].rs,mid+1,r,x-tr[tr[u].ls].sum);
}
inline int go(int u,int i){
	return i==(int)G[u].size()-1?0:i+1;
}
inline void dfs(int u){
	for(int i=0;i<G[u].size();++i){
		int v=G[u][i];
		if(v!=fa[u]){
			fa[v]=u;
			dfs(v);
		}
		else pf[u]=i;
	}
}
inline void dfs1(int u){
	if(u>1) a[++len]=u,pos[u].push_back(len);
	for(int i=go(u,pf[u]);(u!=1&&i!=pf[u])||(u==1&&len<2*n-2);i=go(u,i)){
		int v=G[u][i];
		dfs1(v);
		a[++len]=u,pos[u].push_back(len);
	}
}
inline void dfs2(int u,int gd){
	nw[u]=go(u,nw[u]);
	if(u!=gd) mdf(root[m],root[m],1,len,pos[u].back()),pos[u].pop_back();
	if(nw[u]==pf[u]&&u!=gd) return (void)ne.push_back(u);
	int tmp=nw[u];
	for(int &i=nw[u];i!=pf[u];i=go(u,i)){
		int v=G[u][i];
		dfs2(v,gd);
		mdf(root[m],root[m],1,len,pos[u].back()),pos[u].pop_back();
	}
	if(u==1) dfs2(G[u][nw[u]],gd),mdf(root[m],root[m],1,len,pos[u].back()),pos[u].pop_back();
	pf[u]=tmp;
	if(!pos[u].empty()) ne.push_back(u);
}
int main(){
	scanf("%d%d",&n,&q);
	for(int i=1,k,x;i<=n;++i){
		scanf("%d",&k);
		while(k--){
			scanf("%d",&x);
			G[i].push_back(x);
		}
	}
	dfs(1);dfs1(1);
	hav.push_back(1);
	build(root[0],1,len);
	for(m=1;tr[root[m-1]].sum<len;++m){
		root[m]=root[m-1];
		for(int i:hav) dfs2(i,i);
		swap(hav,ne);
		ne.clear();
		s[m]=s[m-1]+tr[root[m]].sum;
	}
	--m;
	while(q--){
		ll x;
		scanf("%lld",&x);
		int p=lower_bound(s+1,s+1+m,x)-s;
		x-=s[p-1];
		if(p<m) printf("%d\n",a[query(root[p],1,len,x)]);
		else printf("%d\n",a[(x-1)%len+1]);
	}
	return 0;
}
```


---

## 作者：yanwh1 (赞：1)

前置：一道思维题。
# 思路解析
这道题如果不考虑每个点的顺序，我们可以很容易发现它是以欧拉序搜索，难点正是按所给顺序搜索。

但我们可以发现：每一次搜索回到以后，它的搜索序列是欧拉序的子序列，且下一次的搜索序列必定包含这次，于是我们可以按每个点所钦定的顺序的父亲的下个点开始搜索，处理欧拉序。处理完后可以将询问离线下来，依靠 bfs 寻找第 $i$ 轮应搜索到的点，依靠线段树处理欧拉序的子序列是否被用到，本题便做完了！

你问我为什么不在线处理询问？~~因为不想打可持久化线段树~~。
# 代码详解

```cpp
#include<bits/stdc++.h>
using namespace std;
#define rint register int
inline int read(){
    int f=0,t=0;
    char c=getchar();
    while(!isdigit(c)) t|=(c=='-'),c=getchar();
    while(isdigit(c)) f=(f<<3)+(f<<1)+c-48,c=getchar();
    return t?-f:f;
}inline long long lread(){
	long long f=0;int t=0;
    char c=getchar();
    while(!isdigit(c)) t|=(c=='-'),c=getchar();
    while(isdigit(c)) f=(f<<3)+(f<<1)+c-48,c=getchar();
    return t?-f:f;
}inline void write(int x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar('0'+x%10);
}const int N=8e5+5;
int xb[N],olx[N<<1],f[N],fst[N],lst[N],ans[N],cnt,n,Q;
vector<int>s[N];
inline void dfs1(int u,int fa){
	f[u]=fa;
	int sz=s[u].size();
	for(rint i=0;i<sz;i++){
		if(fa==s[u][i])xb[u]=i;
		else dfs1(s[u][i],u);
	}
}inline void dfs(int u){
	if(u!=1)olx[++cnt]=u;
	fst[u]=cnt;lst[u]=cnt;
	int sz=s[u].size(),i=0;
	while(i<sz){
		xb[u]=(xb[u]+1)%sz;i++;
		if(s[u][xb[u]]==f[u])continue;
		dfs(s[u][xb[u]]);
		olx[++cnt]=u;
		lst[u]=cnt;
	}
}struct node{int l,r,sm;}tr[N<<3];
struct edge{int id;long long q;}qr[N];
inline void build(int p,int l,int r){
	tr[p]={l,r,0};
	if(l==r)return;
	int mid=l+r>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
}inline void update(int p,int x){
	if(tr[p].l==tr[p].r){
		tr[p].sm=1;
		return;
	}int mid=tr[p].l+tr[p].r>>1;
	if(x<=mid)update(p<<1,x);
	else update(p<<1|1,x);
	tr[p].sm=tr[p<<1].sm+tr[p<<1|1].sm;
}inline int query(int p,int x){
	if(tr[p].l==tr[p].r)return olx[tr[p].l];
	if(tr[p<<1].sm>=x)return query(p<<1,x);
	return query(p<<1|1,x-tr[p<<1].sm);
}inline void bfs(){
	queue<int>q,rs;
	q.push(1);long long sm=0;int now=1;
	while(now<=Q){
		while(!q.empty()){
			int u=q.front();q.pop();
			int sz=s[u].size();
			int i=0,flag=0;
			while(i<sz){
				xb[u]=(xb[u]+1)%sz,i++;
				if(s[u][xb[u]]==f[u]){
					flag=1;
					continue;
				}if(!flag)q.push(s[u][xb[u]]);
				else rs.push(s[u][xb[u]]);
			}update(1,fst[u]);
			if(lst[u]+1<=cnt)update(1,lst[u]+1);
		}if(rs.empty()){
			while(now<=Q)
				ans[qr[now].id]=query(1,(qr[now].q-sm-1)%tr[1].sm+1),now++;
			return;
		}while(qr[now].q-sm<=tr[1].sm&&now<=Q)
			ans[qr[now].id]=query(1,qr[now].q-sm),now++;
		sm+=tr[1].sm;
		while(!rs.empty())q.push(rs.front()),rs.pop();
	}
}inline int cmp(edge x,edge y){return x.q<y.q;}
signed main(){
	n=read(),Q=read();
	for(rint i=1;i<=n;i++){
		int x=read();
		for(rint j=0;j<x;j++)
			s[i].push_back(read());
	}dfs1(1,0),dfs(1),build(1,1,cnt);
	for(rint i=1;i<=Q;i++)qr[i]={i,lread()};
	for(rint i=1;i<=n;i++)xb[i]=0;
	sort(qr+1,qr+Q+1,cmp);bfs();
	for(rint i=1;i<=Q;i++)write(ans[i]),puts("");
	return 0;
}
```

---

## 作者：Nelofus (赞：0)

为了方便，不妨把每个位置指向的房间编号序列 $c_u$ 循环右移若干次，直到 $c_u$ 序列的末尾指向 $u$ 的父亲。节点 $1$ 循环左移一次，把 $c_{1,1}$ 放到末尾。

如果它给的是一个 $1$ 以外所有激光笔都指向父亲，并且钦定 $1$ 当前的指向是旋转的末尾，那么从 $1$ 出发，循环一圈回到 $1$ 的路径就是**欧拉序**。并且不会改变任何位置的值。

接下来，考虑每个点你在第一次触碰到它的时候，它一定会被旋转至指向父亲。把这个过程称作**复位**。

任意时刻，能走的序列都是一个欧拉序的子序列，所以现在我们考虑在欧拉序上操作。

 对每个点维护一个后继，欧拉序点 $u$ 的第 $k$ 次（其位置设为 $(u,k)$）出现的后继，是在第 $k$ 次到达点 $u$ 后下一个点的位置。

初始的 $(u,1)$ 要指向它下一个位置的欧拉序编号（考虑指向的是父亲还是儿子），其余所有的 $(u,k)$ 都指向 $(u,k)+1$，如果碰到了点 $u$ 就要把点 $u$ 复位，那么令 $(u,1)$ 为 $(u,1)+1$。

$(u,k)$ 后继为 $(u,k)+1$ 这种情况是平凡的，考虑每次用并查集跳过一整段。那每次跳一段都会把一个点复位，只需要复位 $n$ 个点，这部分最终复杂度均摊 $\mathcal O(n\alpha (n))$。

将询问离线下来从小到大排序，考察这次经过的点的序列，找到其中的 $kth$ 就能回答询问了。用 $\text{BIT}$ 上倍增，时间复杂度 $\mathcal O(n\log n)$。

把询问丢在每个连续段里面可以做到纯正 $\mathcal O(n\alpha (n))$，摆了。

[提交记录 #2084593](https://loj.ac/s/2084593)

---

## 作者：7KByte (赞：0)

nb的树上思维DS题。

如果我们把每个指针的的指向集合作为状态，由于状态集合是有限的，并且相同的初始状态则结束位置相同，所以最后一定会循环。但是并不一定是纯循环。

由于这是一颗树，所以我们考虑特殊性质。如果是一个菊花图，显然就是一个排列不断循环。如果是链，手算一下发现就是从点 $1$ 开始，不断来回向两边扩展。每次扩展多少取决于指针的指向。

所以我们定义 $f_i$ 表示节点 $i$ 的重标号，按一下方式标号。

对于当前点 $i$ ，它父亲前面出现的子节点标号为它的标号，后面出现的标号要$+1$。

然后我们再求整个树的 DFS 序，注意 DFS 序是唯一的，每次我们从父节点顺时针的下一个子节点开始。

这样标号，我们就构造出了整个路径。我们按以下方式还原路径。

定义 $s_i$ 表示标号 $\le i$ 的点在 DFS 序中出现的位置连起来，那么原路径就是 $s_1s_2\cdots$。

所以从 $s_n$ 开始就一直以 $s_n$ 循环，对于前面的可以直接可持久化线段树维护 $s_i$，二分后再在线段树上二分可以做到时空复杂度 $\mathcal{O}(N\log N)$。事实上可以对询问离线，可以将空间优化到线性，但是本题有一个G所以无所谓。

另外这道题的难度真的只有紫吗（

---

## 作者：MuYC (赞：0)

首先考虑假设整棵树一开始的指向全都是自己的父节点 （ $1$ 号点随便指向哪个子节点都行，不妨设为是第一个 ）会怎么样：

那么按照题目的意思，我们将会从 $1$ 节点开始，按照某种顺序访问自己的子节点然后又会回到 $1$ 号点并且所有指针仍然指向自己的父节点。

然后就会形成一个循环节，并且每一个循环节将会是长度为 $2n - 2$ 的一个序列。

预先按照上面提到的顺序遍历先得到这个序列，设为序列 $b$。

但是一开始整棵树的状态肯定不会这么优美，不过可以发现，经过 $k$ 次之后整个序列一定会变成上述的样子。可是这个 $k$ 是非常大的，不能直接模拟。

考虑维护：

我们现在假设得到了一个以 $1$ 为根的联通块（一开始只会有 $1$ 这个节点）：

![](https://cdn.luogu.com.cn/upload/image_hosting/nizp13mc.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

然后会得到一个遍历这些点的顺序 $a$，这个 $a$ 序列一定是 $b$ 序列的一个子序列，这些已经在此联通块中的点的遍历的相对顺序肯定是不会变的。

接下来**假想**又从 $1$ 出发然后遍历，到达目前的联通块的一个深度最深节点 $v$ 的时候我们肯定会扩展这个联通块，此刻对应的遍历序列 $a$ 也会改变，也就是遍历序列会在某个位置后面插入一段区间。

考虑开一个长度为 $2n - 2$ 的线段树维护，其中 $[l,l]$ 这个叶子节点也就表示 $b$ 序列中第 $l$ 个位置是否已经出现了。

先把所有被遍历到的新的点（除了新的联通块的底部节点）在 $b$ 序列中所有对应的位置全都标为 $1$，新的联通块的底部节点需要在下次才把其所有位置标为 $1$，首次遍历到的时候就先把它在 $b$ 序列中出现的最后的一个位置标记为 $1$，以发现每个节点最多会被插入其度数次，所以复杂度是 $O(n \log n)$ 的。

用这个线段树来维护我们的遍历序列 $a$ ，然后我们把询问离线按照 $k$ 排序后会排成这个样子：

![](https://cdn.luogu.com.cn/upload/image_hosting/033z8bct.png)

然后我们每次修改完了序列 $a$ 后都用序列 $a$ 去覆盖这个询问点即可（也就是像这样铺排）：

![](https://cdn.luogu.com.cn/upload/image_hosting/nyyqzau8.png)

这样铺排就代表每次回到 $1$ 后又会进行下一轮拓展，于是这样的铺排是具有其实际意义的。

对于特别大的 $k$ 就是有了对应的循环节了，就特殊考虑即可。

ps.这个题解的讲解未必会很清楚，如果有细节不到位请联系写题解的人：`MuYC`

时间复杂度：$O((n + m) \log n)$，空间复杂度：$O(n)$

#### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 8e5 + 50;
typedef long long LL;
inline LL read() {
	LL x = 0, flag = 1;
	char ch = getchar();
	for( ; ch > '9' || ch < '0' ; ch = getchar()) if(ch == '-') flag = -1;
	for( ; ch >= '0' && ch <= '9' ; ch = getchar()) x = x * 10 + ch - '0';
	return x * flag;
}
int n, q, pos[MAXN], Ans[MAXN], Z[MAXN];
int dfs[MAXN << 1], cnt = 0, Now[MAXN], F[MAXN]; 
vector <int> E[MAXN], ID[MAXN];
queue <int> D, New;
struct Ques {
	int id; LL k;
} Q[MAXN];
struct SegmentTree {
	int l, r, siz;
} T[MAXN << 3];
bool cmp(Ques a, Ques b) { return a.k < b.k; }
void build(int x, int l, int r) {
	T[x].l = l, T[x].r = r;
	int mid = (l + r) >> 1;
	if(l == r) return ;
	build(x << 1, l, mid), build(x << 1 | 1, mid + 1, r);
}
void change(int x, int pos) {
	int mid = (T[x].l + T[x].r) >> 1;
	if(T[x].l == T[x].r) { T[x].siz = 1; return ;}
	if(pos <= mid) change(x << 1, pos);
	else change(x << 1 | 1, pos);
	T[x].siz = T[x << 1].siz + T[x << 1 | 1].siz;
}
int GetKth(int x, int k) {
	int siz = T[x << 1].siz;
	if(T[x].l == T[x].r) return dfs[T[x].l];
	if(siz >= k) return GetKth(x << 1, k);
	else return GetKth(x << 1 | 1, k - siz);
}
void GetTheEndArray(int x) {
	if(x != 1) dfs[++ cnt] = x, ID[x].push_back(cnt);
	for(int i = pos[x] + 1 ; ; i ++) {
		i %= E[x].size();
		if(i == pos[x] && x != 1) break;
		GetTheEndArray(E[x][i]), dfs[++ cnt] = x, ID[x].push_back(cnt), Z[x] = ID[x].size() - 1;
		if(i == pos[x] && x == 1) break;
	}
}
void GetFa(int x, int from) {
	F[x] = from;
	for(int i = 0 ; i < E[x].size() ; i ++) {
		int to = E[x][i];
		if(to == from) { pos[x] = i; continue; }
		GetFa(to, x);
	}
}
void DFS(int x, int Rt) {
	Now[x] ++, Now[x] %= E[x].size();
	if(x != Rt) change(1, ID[x][Z[x]]), Z[x] --;
	if(Now[x] == pos[x] && x != Rt) { New.push(x); return ; }
	int fs = Now[x];
	for(int i = Now[x] ;  ; i ++) {
		i %= E[x].size(), Now[x] = i;
		if(i == pos[x] && x != 1) break;
		DFS(E[x][i], Rt), change(1, ID[x][Z[x]]), Z[x] --;
		if(i == pos[x] && x == 1) break;
	}
	pos[x] = fs;
	if(Z[x] != -1) New.push(x);
	return ;
}
void GetTheAnsAndPutIt() {
	int now = 1; LL lst = 0; D.push(1);
	while(!D.empty()) {
		while(!D.empty()) {
			int st = D.front(); 
			D.pop(), DFS(st, st);
		}
		while(!New.empty()) D.push(New.front()), New.pop();
		while(Q[now].k - lst <= 1ll * T[1].siz && now <= q) {
			Ans[Q[now].id] = GetKth(1, Q[now].k - lst);
			now ++;
		}
		lst += T[1].siz;
	}
	while(now <= q) {
		int id = Q[now].id; LL k = (Q[now].k - lst) % cnt;
		if(!k) k = cnt;
		Ans[id] = dfs[k], now ++;
	}
	for(int i = 1 ; i <= q ; i ++) printf("%d\n", Ans[i]);
}
int main() {
	n = read(), q = read();
	for(int i = 1 ; i <= n ; i ++) {
		int K = read();
		while(K --) E[i].push_back(read());
	}
	GetFa(1, 0), pos[1] = 0;
	for(int i = 1 ; i <= q ; i ++) Q[i].id = i, Q[i].k = read();
	sort(Q + 1, Q + 1 + q, cmp); build(1, 1, 2 * n);
	GetTheEndArray(1); GetTheAnsAndPutIt();
	return 0;
}
```

---

