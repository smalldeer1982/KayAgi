# [ABC391D] Gravity

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc391/tasks/abc391_d

存在一个 $10^9$ 行 $W$ 列的网格。将左数第 $x$ 列、**下数**第 $y$ 行的单元格记为 $(x,y)$。

有 $N$ 个方块。每个方块是 $1 \times 1$ 的正方形，方块 $i$（$1 \leq i \leq N$）在时刻 $0$ 时位于单元格 $(X_i,Y_i)$。

在时刻 $t=1,2,\dots,10^{100}$ 时，按照以下规则移动方块：

1. 若网格下数第 $1$ 行所有列均被方块填满，则消除下数第 $1$ 行的所有方块。
2. 对于剩余的方块，从下往上的顺序依次进行以下操作：
   - 若方块位于最底行，或其下方相邻单元格已有方块，则不进行任何操作。
   - 否则，将方块移动到下方相邻单元格。

给定 $Q$ 个询问。对于第 $j$ 个询问（$1 \leq j \leq Q$），请判断在时刻 $T_j+0.5$ 时方块 $A_j$ 是否存在。

## 说明/提示

### 约束条件

- $1 \leq N \leq 2 \times 10^5$
- $1 \leq W \leq N$
- $1 \leq X_i \leq W$
- $1 \leq Y_i \leq 10^9$
- $i \neq j$ 时 $(X_i,Y_i) \neq (X_j,Y_j)$
- $1 \leq Q \leq 2 \times 10^5$
- $1 \leq T_j \leq 10^9$
- $1 \leq A_j \leq N$
- 输入均为整数

### 样例解释 1

方块位置变化如下图所示：  
![](https://img.atcoder.jp/abc391/4a6590753edcbad7ea1e8ce7f172902a.png)  
- 询问 $1$：时刻 $1.5$ 时方块 $1$ 存在，输出 `Yes`。  
- 询问 $2$：时刻 $1.5$ 时方块 $2$ 存在，输出 `Yes`。  
- 询问 $3$：方块 $3$ 在时刻 $2$ 被消除，因此时刻 $2.5$ 时不存在，输出 `No`。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
5 3
1 1
1 2
2 2
3 2
2 3
6
1 1
1 2
2 3
2 5
3 4
3 5```

### 输出

```
Yes
Yes
No
Yes
No
Yes```

## 样例 #2

### 输入

```
3 2
1 1
2 1
1 2
4
1 1
1 2
1 3
2 3```

### 输出

```
No
No
Yes
Yes```

# 题解

## 作者：FlowerAccepted (赞：45)

## 解题思路

注意到落下的正方形们满一行才会被消除，之后的正方形才会落下来。所以能清除多少行正方形和正方形们初始的高度无关，而是等于同一个 $X$ 中**最少**有多少个正方形。如图 $\text{S-AT\_abc391\_d-1}$ 所示，没有正方形会被消除：

![](https://cdn.luogu.com.cn/upload/image_hosting/xdq4agk1.png)

$$
\footnotesize
\text{图 S-AT\_abc391\_d-1} \\
\text{这个形状，这个颜色.....也许有些熟悉}
$$

在加入一个绿色正方形后，最底部的一行才会被消除，如图 $\text{S-AT\_abc391\_d-2}$ 所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/7391bpoi.png)

$$
\footnotesize
\text{图 S-AT\_abc391\_d-2} \\
\text{送走底部正方形，你想到了什么？}
$$

我们可以使用一个 `vector<int>` $v[MAXM]$ 来存储**每一列从低到高**的正方形。

具体的，可以**按顺序**输入到两个 `pair<int, int>` 数组 $a[MAXN]$ 和 $b[MAXN]$，将 $X_i$ 输入到 $a_i.first$（）；将 $Y_i$ 输入到 $a_i.second$，再将 $a$ 拷贝一份到 $b$，以便后用。（当然输入到 $b$，拷贝到 $a$ 也是一样的。）

再将 $a$ 按 $second$ **不降序**排序，这需要自定义比较函数

```cpp
bool cmp(pair<int, int> x, pair<int, int> y) {
    return x.second < y.second;
}

```

再使用 `sort(a + 1, a + n + 1, cmp)` 进行排序。当然，你要愿意手搓 $\tt STL$ 我也不会拦你。

然后**按顺序**遍历 $a$ 数组，$\forall 1 \le i \le N$，在 $v_{a_i.first}$ 的尾部追加 $a_i.second$，这样保证了表示每一列的向量中，下标越**大**的正方形越**高**，即正方形的高度呈**升序**排列，代码如下：
```cpp
for (int i = 1; i <= n; i ++) {
    v[a[i].first].push_back(a[i].second);
}

```
图 $\text{S-AT\_abc391\_d-1}$ 处理前后如图 $\text{S-AT\_abc391\_d-3}$ 所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/0oudk9j9.png)

$$
\footnotesize
\text{图 S-AT\_abc391\_d-3} \\
\text{醍醐灌顶？}
$$

记 $mins$ 为每个 $v_i$ 中**最少**有多少个正方形；$maxs$ 为每个 $v_i$ 中**最多**有多少个正方形。

图 $\text{S-AT\_abc391\_d-1}$ 中，$mins = 0$，$maxs = 2$；图 $\text{S-AT\_abc391\_d-3}$ 中，$mins = 1$，$maxs = 2$;

我们开一个大小为 $maxs$ 的向量 $t$，记录**每一层正方形的消失时间**，

$$
\forall 0 \le i < maxs, \\
t_i = 
\begin{cases}
\max\limits_{j = 1}^W v_{j, i} & i < mins \\
\inf & \operatorname{otherwise}
\end{cases}
$$

这里 $\inf$ 取 `1e9+5` 即可。

看不懂？上代码！

```cpp
t.resize(maxs + 5); // 开大一点
for (int j = 1; j <= w; j ++) {
    for (int i = 0; i < mins; i ++) {
        t[i] = max(t[i], v[j][i]);
    }
}
for (int i = mins; i < maxs; i ++) {
    t[i] = 1e9 + 5;
}

```

还看不懂？上图片！

![](https://cdn.luogu.com.cn/upload/image_hosting/li6ohncf.png)

$$
\footnotesize
\text{图 S-AT\_abc391\_d-4} \\
\text{你，学会了吗？}
$$

预处理完毕，开是处理询问。

对于每个询问，首先注意**输入顺序**。（编者被坑了！）

接着找到对应的正方形对应的**层数** $id$，一定要**使用原来顺序的 $b$ 数组**查找。这可以使用 `lower_bound` 来优化，返回的是指针，注意减去开头：

```cpp
id = (int)(lower_bound(v[b[A].first].begin(), v[b[A].first].end(), b[A].second) - v[b[A].first].begin());

```

然后注意到正方形若在 $T_i$ 时刻没有正在消失，那么它在 $T_i + 0.5$ 时刻就还存在。

最后，根据预处理的结论，判断 $T_i$ 是否小于 $t_{id}$ 即可。如果 $id \ge mins$，说明这层没凑齐，正方形自然就不会下落了，$T_i$ 不会超过 $\inf$（$10^9+5$）。

这块内容如果不理解还请看看图 $\text{S-AT\_abc391\_d-4}$。

## 代码呈现

代码不丑，请参考。

```cpp
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector> // 万能头不是 STL 成员，咱不用。
using namespace std;

pair<int, int> a[200005], b[200005];
vector<int> v[200005], t; // 防止越界，开大数组，从我做起

bool cmp(pair<int, int> x, pair<int, int> y) { // 比较数对
    return x.second < y.second;
}

int main() {
    int n, w, mins = 1e9+5, maxs = 0, q, A, T, id;
    cin >> n >> w;
    for (int i = 1; i <= n; i ++) {
        cin >> b[i].first >> b[i].second;
        a[i] = b[i];
    } // 输入
    sort(a + 1, a + n + 1, cmp);
    for (int i = 1; i <= n; i ++) {
        v[a[i].first].push_back(a[i].second);
    } // 离散化？？
    for (int i = 1; i <= w; i ++) {
        mins = min(mins, (int)v[i].size());
        maxs = max(maxs, (int)v[i].size());
    } // 计算层数
    t.resize(maxs + 5);
    for (int j = 1; j <= w; j ++) {
        for (int i = 0; i < mins; i ++) {
            t[i] = max(t[i], v[j][i]);
        }
    } // 计算每一层的消失时间
    for (int i = mins; i < maxs; i ++) {
        t[i] = 1e9 + 5;
    } // inf
    cin >> q;
    for (int i = 1; i <= q; i ++) {
        cin >> T >> A;
        id = (int)(lower_bound(v[b[A].first].begin(), v[b[A].first].end(), b[A].second) - v[b[A].first].begin()); // 二分
        cout << (T < t[id] ? "Yes\n" : "No\n"); // 换行！
    }
    return 0;
}

```

至此，本题 Accepted。

## 复杂度分析

预处理除排序外的均摊复杂度是 $O(N)$，这是因为无论单层还是双层的循环，总的循环次数也不会也不会超过 $N$ 次。

$\tt STL$ 排序的时间复杂度是 $O(N \log N)$。（当然，[这个排序也许不会执行哒](https://www.luogu.com.cn/discuss/1053088)）

而每个询问也许会查询到一个有近乎 $N$ 个正方形的 $X$ 坐标，由于二分查找的优化，最坏情况下查询的总时间复杂度是 $O(Q \log N)$，最好情况下则是只有 $1$ 层，最好情况下查询的总时间复杂度就是 $O(Q)$。

综合来看，程序的最好时间复杂度是 $O(N + Q)$，最坏的则是 $O((N + Q) \log N)$，轻松通过！

其实 $\tt STL$ 在此题中发挥了挺大的作用，不然这题的代码就有上千行喽！$\tt STL$ 好闪，拜谢 $\tt STL$！

这篇题解花了我一天的心血，求个赞！

---

## 作者：da_ke (赞：27)

> 像流星划过夜空，转瞬即逝的梦。

在平面直角坐标系中，有 $N$ 颗流星（shooting_star）划过，第 $i$ 颗的初始坐标（第 $0$ 时刻坐标）为 $(X_i,Y_i)$。保证 $1 \leq X_i\leq W$。

每一个单位时刻，流星按如下规则运动：

- 如果底部是满的既 $(1,1),(2,1),\cdots,(W,1)$ 的位置上都有流星，那么这些流星**在这个时刻末**全部消失；否则底部的流星不动。
- 其余不在底部的流星向下移动一个单位。

在看流星的 fyy 想问妳 $Q$ 个问题：询问第 $A_i$ 个流星在 $T_i$ 时刻**末**是否存在。

妳非常聪明，很快注意到 $Q$ 很大，不可能一个一个处理，妳打算对于每一个流星，计算它消失的时刻。

如何计算每一个流星消失的时刻？妳很快发现流星消失是**一轮一轮**的。

考察横向和竖向的变化：

- 横向：妳发现一轮消失的流星总是每一列中最低的一个。
- 纵向：妳发现每一列中，低的流星总不会影响高的流星的运动状态。

以上是一些感性认识，我们现在转化为形式化语言。

1. 考虑将流星按列放进优先队列。具体的，初始 $(X_i,Y_i)$ 放进 $q_{X_i}$。其中 $q_1,q_2,\cdots,q_W$ 为 $W$ 个小根堆（优先队列）。

2. 取 $q_1,q_2,\cdots,q_W$ 的队首。

   - 如果某个队列空了，那么以后的流星（包括这一轮）永不消失。
   - 否则取 $q_1,q_2,\cdots,q_W$ 的队首 $y$ 坐标的最大值为这一轮所有流星的消失时间 $T_{max}$（**注意临界问题，如果一个时刻 $T\ge T_{max}$ 那么这一轮的流星都在 $T$ 时刻消失过了，注意能取等号**）。
   - 将所有队首出队。
3. 不断执行操作 $2$，直至存在一个空队。

然后代码是很简单的，据笔者所知很多人这道题都死于**细节**。笔者自认为自己的代码细节很少好理解。

```cpp
const int fyy=0;

int main()
{
    int N,W;
    cin>>N>>W;
    vector<priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>> q(W+1);
    vector<int> ans(N+1,(int)1e9+24);
    rep(i,1,N)
    {
        int X,Y;
        cin>>X>>Y;
        q[X].push({Y,i});
    }
    bool zxq=1; // 张修齐：是否可进行下一轮
    while(zxq)
    {
        int _max=fyy;
        rep(i,1,W)
        {
            if(q[i].empty())
            {
                zxq=fyy;
                break;
            }
            _max=max(_max,q[i].top().first);
        }
        if(!zxq) break;
        rep(i,1,W)
        {
            ans[q[i].top().second]=_max;
            q[i].pop();
        }
    }
    int Q;
    cin>>Q;
    while(Q--)
    {
        int T,A;
        cin>>T>>A;
        if(T>=ans[A])
            cout<<"No"<<endl;
        else cout<<"Yes"<<endl;
    }
}

// 路虽远行则将至，事虽难做则必成。
```

AC 记录：<https://atcoder.jp/contests/abc391/submissions/62291264>

[流星姐姐](https://www.luogu.com/user/955954)珂愛喵~

---

## 作者：liluhexuan (赞：4)

~~说句闲话，这道题的 $x$ 和 $y$ 是反过来的。~~

容易发现任何一行从下往上数第 $i$ 个一定是和其他行从下往上数的第 $i$ 个一起消掉或在最后局面中位于同一行。为了方便我们管所有列从下往上第 $i$ 个方块组成的集合叫做第 $i$ 个**梯队**（该集合不能为空集），若某一列没有第 $i$ 个方块，则称第 $i$ 个梯队为**不完全梯队**，反之为**完全梯队**。

然后会发现对于第 $i$ 个梯队，若该梯队为不完全梯队，则其后面的梯队一定为不完全梯队；且最后一个完全梯队的编号就是方块数量最少的列的**方块数量**。而如果该梯队为完全梯队，则该梯队被消掉的时间为该梯队所有方块中最高的方块的 $x$ 值（在题目中为 $y$ 值）。

所以我们只需要先对于任意一列，按高度从小到大对该列所有方块进行排序，然后将排序后每一行第 $i$ 个归入第 $i$ 个梯队，之后按上文求出该梯队的消失时间（或确定该梯队不会被消除），最后按要求查询就行了。

代码：

```
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
#define int long long  //理论上不用
const int N=2e5+10;
vector<pair<int,int> >g[N];
int ans[N],vis[N];
signed main(){
	int n,m,mn=1e18,q;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		int x,y;
		cin>>y>>x;
		g[y].push_back({x,i}); //分组，为排序做准备
	}
	for(int i=1;i<=m;i++)
		sort(g[i].begin(),g[i].end());
	for(int i=1;i<=m;i++){
		int p=g[i].size(); //灵异事件，不这么写就不过编
		mn=min(mn,p); //统计完全梯队的数量
		for(int j=0;j<g[i].size();j++){
			vis[g[i][j].second]=j+1; //确定该点在第几梯队
			ans[j+1]=max(ans[j+1],g[i][j].first); //统计该队消失时间
		}
	}
	cin>>q;
	while(q--){
		int t,a;
		cin>>t>>a; //该队是否为完全梯队且查询时间在消失时间之后
		if(vis[a]<=mn&&t>=ans[vis[a]]) cout<<"No\n";
		else cout<<"Yes\n";
	}
	return 0;
}
```

~~无耻地~~求过，求点赞。

还有个问题，第 $20$ 行到第 $21$ 行不知道为什么直接将 $mn$ 和长度比较会编译错误，请大佬解答（悬赏一关注）！

---

## 作者：Pyrf_uqcat (赞：4)

简化题意，有一堆方块，每秒都掉落一个单位，当底层被铺满时底层所有方块消失。

为了后文流畅，我们将底层消失称为一次操作。

思路：求出每个方块的消失时间（也就是最后存在时间）。普通写法会超时，考虑用双关键字排序然后一次遍历每个方块将会在第几次操作后消失，求出方块的消失时间。注意有些方块最后是一直存在的，需要求出最大操作数。

排序时间复杂度 $O(n\log n)$。

### 赛时已过代码


```cpp
#include <bits/stdc++.h>
#define int long long

#define N 200005

using namespace std;

int n,w,q,ans[N],mx=INT_MAX;

int mxx[N],cnt[N],cntt;

struct Node
{
	int x,y,id;
};

Node a[N];

bool cmp(Node x,Node y)
{
	if(x.x!=y.x) return x.x<y.x;
	else return x.y<y.y;
}

signed main()
{
    cin>>n>>w;
    for(int i=1;i<=n;i++)
    {
		cin>>a[i].x>>a[i].y;
		a[i].id=i;
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n+1;i++)
	{
		if(a[i].x!=a[i-1].x&&i!=1) 
		{
			if(a[i].x-a[i-1].x>1) mx=0;
			mx=min(mx,cntt);
			cntt=0;
		}
		if(i==n+1) break;
		cnt[i]=++cntt;
		mxx[cnt[i]]=max(mxx[cnt[i]],a[i].y-1);
	}
	for(int i=1;i<=n;i++)
	{
		if(cnt[i]>mx) ans[a[i].id]=-1;
		else
		{
			ans[a[i].id]=mxx[cnt[i]];
		}
	}
	int q;cin>>q;
	while(q--)
	{
		int t,opt;cin>>t>>opt;
		if(ans[opt]<t&&ans[opt]!=-1) cout<<"No"<<endl;
		else cout<<"Yes"<<endl;
	}
    return 0;
}
```

---

## 作者：Hero_Broom (赞：3)

[AT_abc391_d [ABC391D] Gravity 题目链接](https://atcoder.jp/contests/abc391/tasks/abc391_d)

## 题目大意

给定一个 $10^9$ 行 $w$ 列的网格。给定了 $N$ 个方块，**从下往上数**第 $x$ 行，从左往右数第 $y$ 列的方块位于 $(x,y)$。

这些小方块在每一个时刻会执行以下操作：

- 若底部，也就是第一行已经全部铺满了方块，则将底部所有方块移除；

- 从下往上依次对还存在的方块执行以下操作：若该方块下方无其他方块且不在底部，将方块下移一格。

现在给出 $Q$ 个询问。对于第 $i$ 个询问，输出方块 $A_i$ 是否在时刻 $T_i+0.5$ 存在。

## 题解

### 思路

我们可以计算出每个方块的移除时间，将其储存在 $dtp$ 数组中。对于第 $i$ 个询问，我们只需判断 $T_i<dtp_{A_i}$。

在输入的时候，我们将所有方块按照 $y$ 坐标排序，也就是按照高度排序。我们可以将同一列的方块放在一起。

```cpp
struct block{
    int idx,x,y;
   	block(int _idx=0,int _x=0,int _y=0):
  	x(_x),y(_y),idx(_idx) {}
};//方块结构体
block a[200010];//储存每个方块
vector<block> b[200010];//b[i]储存一整列的方块

for(int i=1;i<=n;i++) b[a[i].x].push_back(a[i]);//将同一列的方块放在一起
```

我们从底部朝上遍历。

首先，因为能被移除的方块需要满足一整行都在最底部，我们记录 $minsize$ 为方块数量最少的一列，若当前行大于 $minsize$，则说明当前行的方块永远不可能被消除。

例如题目中的样例：

```
5 3
1 1
1 2
2 2
3 2
2 3
6
1 1
1 2
2 3
2 5
3 4
3 5
```

![](https://img.atcoder.jp/abc391/4a6590753edcbad7ea1e8ce7f172902a.png)

如上图，可以看到方块 $2$ 和方块 $5$ 永远不可能被移除。

接下来考虑每一列做底部的方块 $b_{i,0}$，很明显可以看出 $dtp_i=max \{ (b_{i,0}).x , i \in [1,w] \}$。因为我们要等到最高的一个方块落下来后才能移除。

样例中，我们要等到最高的两个方块，也就是方块 $3$ 和方块 $4$ 落下后才能消除，所以 $dtp_{1,3,4}= (b_{i,0}).y = 2$。

而对于其他方块，设当前方块为第 $i$ 列从下往上第 $j$ 个方块，有两种情况：

1. 方块的下面还有方块没移除导致方块不能落到最底层。此时方块的落下时间 $dtp_i$ 则为 $dtp_{(b_{i,j-1}.idx)}+1$，也就是他下面方块的移除时间加一。

2. 方块下面已经没有其他方块但是还没有落到底。此时方块的落下时间则为 $(b_{i,j}).y$。

因为要一整层的方块全部落到最底层，所以我们还要对这一层方块的落下时间取最大值做为这一层方块的 $dtp$。

这里就直接贴代码了：

```cpp
for(int i=0;i<maxsize;i++){
	if(i>=minsize){
		for(int j=1;j<=m;j++) if(i<(int)b[j].size()) dtp[b[j][i].idx]=1e9+10;
	}else if(i==0){
		tmp=0;
		for(int j=1;j<=m;j++) tmp=max(tmp,b[j][0].y);
		for(int j=1;j<=m;j++) dtp[b[j][0].idx]=tmp;
	}else{
		tmp=0;
		for(int j=1;j<=m;j++) tmp=max(tmp,max(dtp[b[j][i-1].idx]+1,b[j][i].y));
		for(int j=1;j<=m;j++) dtp[b[j][i].idx]=tmp;
	}
}
```

目前为止我们就已经把每个方块的 $dtp$ 算了出来，询问时我们只需要输出 $T_i<dtp_{A_i}$ 即可。

### 注意事项

因为网格的高度为 $10^9$，也就是说方块掉落的时间最大有可能为 $10^9$。所以上面永远不可能被移除的方块的 $dtp$ 应设为比 $10^9$ 大的数。比赛时就因为设成了 $99999999$ 调了整整十分钟。

### 代码

按照上面思路的模拟即可，代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct block{
	int idx,x,y;
	block(int _idx=0,int _x=0,int _y=0):
	x(_x),y(_y),idx(_idx) {}
};
block a[200010];
vector<block> b[200010];
int n,m,q,minsize=INT_MAX,maxsize,tmp,dtp[200010],o,p;//disappear time point
bool cmp(const block& a,const block& b){
	if(a.y!=b.y) return a.y<b.y;
	if(a.x!=b.x) return a.x<b.x;
	return a.idx<b.idx;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1,x,y;i<=n;i++){
		scanf("%d%d",&x,&y);
		a[i]=block(i,x,y);
	}
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<=n;i++) b[a[i].x].push_back(a[i]);
	for(int i=1;i<=m;i++){
		minsize=min(minsize,(int)b[i].size());
		maxsize=max(maxsize,(int)b[i].size());
	}
	for(int i=0;i<maxsize;i++){
		if(i>=minsize){
			for(int j=1;j<=m;j++) if(i<(int)b[j].size()) dtp[b[j][i].idx]=1e9+10;
		}else if(i==0){
			tmp=0;
			for(int j=1;j<=m;j++) tmp=max(tmp,b[j][0].y);
			for(int j=1;j<=m;j++) dtp[b[j][0].idx]=tmp;
		}else{
			tmp=0;
			for(int j=1;j<=m;j++) tmp=max(tmp,max(dtp[b[j][i-1].idx]+1,b[j][i].y));
			for(int j=1;j<=m;j++) dtp[b[j][i].idx]=tmp;
		}
	}
	scanf("%d",&q);
	while(q--){
		scanf("%d%d",&o,&p);
		printf(o<dtp[p]?"Yes\n":"No\n");
	}
    return 0;
}
```

---

## 作者：Clover_Lin (赞：3)

- [更好的阅读效果](https://blog.csdn.net/ArmeriaLeap/article/details/145415197)
## 题目大意
- [原题面链接](https://atcoder.jp/contests/abc391/tasks/abc391_d)

在一个 $10^9\times W$ 的平面里有 $N$ 个方块。我们用 $(x,y)$ 表示第 $x$ 列**从下往上**数的 $y$ 个位置。第 $i$ 个方块的位置是 $(x_i,y_i)$。现在执行无数次操作，每一次操作如下：
- 如果整个平面的最下面一行的 $W$ 个位置上都有方块，那么把这一行的方块都消除掉。
- **从下往上**遍历每一个未被消除的方块，如果它不在最下面一行且它下面是空格子，将它向下移动一格。**注意：只移动一格！**
## 思路
观察数据范围，需要预处理。我们不妨令 $ti_i$ 表示第 $i$ 个方块什么时候被消除。对于无法被消除的方块，其 $ti_i$ 为极大值。我们可以拿样例来寻找突破口，样例解释里面的那个图片如下：

![](https://i-blog.csdnimg.cn/img_convert/f4b1ff91b63d6aad9293903bc0ce73e7.png)
观察一下，第二次操作执行完和第三次操作执行完的结果是一样的，所以继续执行下去，结果不会改变。也就是说，第三次操作及以后的操作都是“无效操作”，而其中可以消除的操作只有第二次，我们将其称为“有意义”。稍加观察可以发现，有意义的操作数量是每一列方块数量的最小值，很容易证明出来。

每一次有意义的操作之前我们可能需要一些（有的时候不需要）操作来让所有方块掉到地上，这种操作我们称之为“预备操作”。不难发现，预备操作的结束时间是每一列最下面的方块的纵坐标的最大值减一。所以有意义的操作的结束时间就是每一列最下面的方块的纵坐标的最大值（有点绕），可以用来更新 $ti_i$。

一个很重要的问题：怎么预处理每一列的那堆格子？开个 `vector` 数组，具体实现看代码。

那么在每一次询问的时候只要看 $ti_{A_j}$ 与 $T_j$ 的大小关系即可。
## 预处理部分代码
其实有点小细节能 hack，见文末彩蛋。

```cpp
for (int i = 1; i <= n; i++)
{
	cin >> x[i] >> y[i]; // 读入
	v[x[i]].push_back(i); // 这一列的方块
	ti[i] = 1e9 + 7; // 极大值
}
int mn = 1e9 + 7; // 极大值
for (int i = 1; i <= w; i++)
{
	int cnt = v[i].size(); // 强转一下
	 // int 类型不能直接和 unsigned int 类型取 min
	mn = min(mn, cnt);
}
for (int i = 0; i < mn; i++)
{
	int mx = 0; // 计算最大值
	for (int j = 1; j <= w; j++)
		mx = max(mx, y[v[j][i]]);
	for (int j = 1; j <= w; j++)
		ti[v[j][i]] = mx; // 更新
}
```
## 完整代码
[我的提交记录](https://atcoder.jp/contests/abc391/submissions/62283150)
## 时间复杂度分析
预处理里面有个双重循环，为什么没有超时呢？$mn$ 最大为 $N$，复杂度理论上来说是 $O(N\cdot W)$ 的，但是考虑到实际构造原因，其均摊时间复杂度是不会超时的，所以可以通过本题。
## 彩蛋
大框架没问题，有个小细节出锅了。请问题目保证输入按 $y_i$ 升序排序了吗？没有！得自己排个序。注意一下，得用结构体排序，既可以让变量对应上，也可以存储初始下标。正确版本我还没写，应该没啥太大区别，遇到问题欢迎在评论里问我或私信沟通哦！要是有其他问题或者 hack 数据也可以联系我哦！

---

## 作者：jerry139com (赞：2)

[$\Huge{传送门}$](https://www.luogu.com.cn/problem/AT_abc391_d)

这道题场上没过。

---

### 算法

![https://img.atcoder.jp/abc391/4a6590753edcbad7ea1e8ce7f172902a.png](https://img.atcoder.jp/abc391/4a6590753edcbad7ea1e8ce7f172902a.png)

通过上图可以发现：时刻 $2.5$ 和时刻 $3.5$ 的图片是一样的，容易知道时刻 $4.5$，$5.5$，……也都和时刻 $2.5$ 是一样的。所以，消除行的次数在该数据中就是 $\red{1}$。

不难发现，**消除行的次数就是方块最少列的方块数**。

---

那么如何算出每一行消除的时间呢？先要做一个二维数组，代表着每个图。

```cpp
vector<pair<ll, ll> > xy[200009];
//xy[a][b] = ( c, d )
//b：这个节点是这一列从下往上的第几个节点（从第0个开始）
//( a, c ) 坐标
//d：是输入的第几个数
```

```cpp
	for ( int i = 1; i <= n; i++ ) {
		ll a, b;
		cin >> a >> b;
		xy[a].push_back ( make_pair ( b, i ) ); //处理这个图
	}
```

然后再算消除行的次数。

```cpp
	ll mininum = 0x3f3f3f3f3f3f3f3f;
	for ( int i = 1; i <= w; i++ ) {
		sort ( xy[i].begin(), xy[i].end(), less<pair<ll, ll> >() ); //注意排序
		mininum = min ( mininum, ( ll ) ( xy[i].size() ) );
	}
```

最后再算每一行消除的时间。

```cpp
	for ( int i = 0; i < mininum; i++ ) {
		for ( int j = 1; j <= w; j++ ) {
			maxi[i] = max ( maxi[i], xy[j][i].first );
		}
	}
```

---

为了最后便于从 $A_j$ 转换到 `maxi` 的那一列，我们又设定了一个数组 `qwq`，用于转换。

```cpp
  for ( ll i = 1; i <= w; i++ ) {
		for ( ll j = 0; j < ( ll ) ( xy[i].size() ); j++ ) {
			qwq[xy[i][j].second] = make_pair ( i, j );
		}
	}
```

```cpp
	cin >> q;
	for ( int i = 1; i <= q; i++ ) {
		ll a, b;
		cin >> a >> b;
		if ( maxi[qwq[b].second] == 0 ) cout << "Yes"; //需要特判
		else if ( maxi[qwq[b].second] > a ) cout << "Yes";
		else cout << "No";
		cout << endl;
	}
```

---

### 放上代码：

```
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll n, w, q;
vector<pair<ll, ll> > xy[200009];
ll maxi[200009];
pair<ll, ll> qwq[200009];
int main() {
	cin >> n >> w;
	for ( int i = 1; i <= n; i++ ) {
		ll a, b;
		cin >> a >> b;
		xy[a].push_back ( make_pair ( b, i ) );
	}
	ll mininum = 0x3f3f3f3f3f3f3f3f;
	for ( int i = 1; i <= w; i++ ) {
		sort ( xy[i].begin(), xy[i].end(), less<pair<ll, ll> >() );
		mininum = min ( mininum, ( ll ) ( xy[i].size() ) );
	}
	for ( ll i = 1; i <= w; i++ ) {
		for ( ll j = 0; j < ( ll ) ( xy[i].size() ); j++ ) {
			qwq[xy[i][j].second] = make_pair ( i, j );
		}
	}
	for ( int i = 0; i < mininum; i++ ) {
		for ( int j = 1; j <= w; j++ ) {
			maxi[i] = max ( maxi[i], xy[j][i].first );
		}
	}
	cin >> q;
	for ( int i = 1; i <= q; i++ ) {
		ll a, b;
		cin >> a >> b;
		if ( maxi[qwq[b].second] == 0 ) cout << "Yes";
		else if ( maxi[qwq[b].second] > a ) cout << "Yes";
		else cout << "No";
		cout << endl;
	}
	return 0;
}
```

---

## 作者：FatLLion (赞：2)

~~ABC 人类模拟题。~~

显而易见的一道模拟题，用 vector 和结构体排序可以轻松过掉。

这里使用 vector 去存下每一列的方块，根据题面可以看到行很多但是 $W$ 范围在可以接受的范围内，所以用 vector 存储不会 tle 也不会爆空间。

观察题面，题目并没有说明给出的方块一定是按照列里的升序给你的，也就是说你输入的方块可能是无序的。 ~~（然而数据里并没有去专门卡这一点）~~ 所以用结构体排个序，每一列里按照 $y_i$ 排个升序。

题目说当底行被填满的时候才会进行消除，观察图片也可以发现消除和往下掉是在同一时刻进行的，并会不分开两个时刻进行。这个时候观察图片可以发现，当有一列被消除完的时候，对于还在场的方块往后的都是输出 `Yes`，并且这个只取决于一列的存在的方块数，也就是存在最多消除次数是每一列中方块数的最小数，设其为 $min_{row}$，即只会消除 $min_{row}$，行。

那么可以发现，每一个方块都要在它掉到底部且底部被填满的时候才会被消除，那么它存活时间就是它对应的那个底行的最高的那个方块的 $y$。

给个解释：设当前方块是 $(x, y)$，即第 $x$ 列第 $y$ 行并在那个列里排第 $R$ 个，那么就要去找其他列里同样在那个列里排第 $R$ 个的方块，并统计出所有列里排 $R$ 的 $y_{max}$。这个 $y_{max}$ 就是当前方块的存活时间。

最后预处理完 $N$ 个方块的存活时间，就可以直接在 $q$  次询问内用 $O(1)$ 的方式给出答案，时间复杂度应该是 $O(N)$。

记得在结构体排序后用个 map 存一下对应方块的位置，方便查询。

```c++
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int INF = 1e9+100;
const int N = 2e5+100;

void read (int &x) {
    int f = 1;x = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar();}
    while (ch >= '0' && ch <= '9') { x = x*10+ch-'0'; ch = getchar();}
    x *= f;
}

void print (int x) {
    if (x<0) putchar('-'), x = -x;
    if (x<10) putchar(x+'0');
    else print(x/10), putchar(x%10+'0');
}

struct B {
	int x, y, maxti, id;
};

int n, w, q;
vector <B> block[N];
map <int, pair<int, int> > mp;

bool cmp (B a, B b) {
	if (a.x == b.x) return a.y < b.y;
	return a.x < b.x;
}

int main () {
	//freopen("xxx.in", "r", stdin);
	//freopen("xxx.out", "w", stdout);
	read(n), read(w);
	for (int i = 1;i <= n;i++) {
		int x, y;
		read(x), read(y);
		B tmp;
		tmp.id = i, tmp.x = x, tmp.y = y;
		block[x].push_back(tmp);
	}
	for (int i = 1;i <= w;i++) sort(block[i].begin(), block[i].end(), cmp);
	for (int i = 1;i <= w;i++) {
		for (int j = 0;j < block[i].size();j++) {
			B tmp = block[i][j];
			pair <int, int> p;
			p.first = i, p.second = j;
			mp[tmp.id] = p;
		}
	}
	int cnt = INF;
	for (int i = 1;i <= w;i++) for (int j = 0;j < block[i].size();j++) block[i][j].maxti = INF;
	for (int i = 1;i <= w;i++) cnt = min(cnt, (int)block[i].size());
	for (int i = 0;i < cnt;i++) {
		int maxn = 0;
		for (int j = 1;j <= w;j++) maxn = max(maxn, block[j][i].y);
		for (int j = 1;j <= w;j++) block[j][i].maxti = maxn;
	}
	read(q);
	while (q--) {
		int t, a;
		read(t), read(a);
		pair <int, int> pos = mp[a];
		if (t*1.0+0.5 >= block[pos.first][pos.second].maxti) printf("No\n");
		else printf("Yes\n");
	}
	return 0;
}

```

---

## 作者：Yannik (赞：2)

## 分析：
根据题意，询问只问了你 $t_i+0.5$ 秒时还存不存在 $A_i$ 块。我们只需将每个块消失时间算出来就好了。
同时，每一列的第 $i$ 个块（按照高度排序）一定一起消失。
## 做法：
一共有 $w$ 列，我们直接开 $w$ 个 ```set```。利用 ```set``` 能够排序的性质，依次删去 ```set``` 的首元素。取最大高度作为这几个首元素的消失时间。还需要开 $n$ 个 ```map``` 记录坐标对应的编号。
## 代码：
```cpp
#include<iostream>
#include<algorithm>
#include<cmath>
#include<vector>
#include<map>
#include<set>
#define PII pair<int,int>
#define int long long 
using namespace std;
const int N = 1e6 + 10;
int T,n,m,q,cnt;
map<PII,int> mp;
set<int> a[N];
int ti[N];
signed main(){
    cin.tie(0)->ios::sync_with_stdio(0);
    cin>>n>>m;//n个数，w列（个人习惯用m）
    int maxn=0;
    for(int i=1;i<=n;i++){
        int x,y;
        cin>>y>>x;
        a[y].insert(x);
        maxn=max((long long)a[y].size(),maxn);
        mp[make_pair(x,y)]=i;//记录编号
    }
    int f=0;
    for(int i=1;i<=maxn;i++){
        int tmax=0;
        vector<int> tmp;
        for(int j=1;j<=m;j++){
            if(a[j].size()==0){
                f=1;
                break;
            }
            tmax=max(tmax,(long long)*a[j].begin());//取最大高度作为下落时间
            tmp.push_back(*a[j].begin());
            a[j].erase(*a[j].begin());
        }
        if(f==1) break;
        int y=1;
        for(auto x:tmp){
            ti[mp[make_pair(x,y)]]=tmax;//给对应的id赋值
            y++;
        }
    }
    cin>>T;
    while(T--){
        int t,id;
        cin>>t>>id;
        if(ti[id]==0) cout<<"Yes";
        else if(ti[id]<=t) cout<<"No";
        else cout<<"Yes";
        cout<<"\n";
    }
    return 0;
}
```

---

## 作者：sodalyghat (赞：2)

### 思路
首先需要发现一个性质。一个格子落到最下面并被删除所用的时间就是他的纵坐标。另外，每一列从下往上的每一行被删除的时间是这一行所有格子被删除时间的最大值。因此我们可以在每一列中对纵坐标进行排序，然后就可以处理出来每一个格子是否会被删除和删除的时间，然后就可以回答询问了。
### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace Luo_ty{
	const int MAXN = 1000005;
	int x[MAXN], y[MAXN];
	struct node{
		int y, id;
	};
	bool cmp(node a, node b){
		return a.y < b.y;
	}
	vector<node> d[MAXN];
	int lim[MAXN], cnt[MAXN];
	int main(){
		int n, w;
		scanf("%d%d", &n, &w);
		memset(cnt, 0, sizeof(cnt));
		for(int i = 1;i <= n;i++){
			scanf("%d%d", &x[i], &y[i]);
			d[x[i]].push_back((node){y[i], i});
			cnt[x[i]]++;
			lim[i] = 0;
		}
		for(int i = 1;i <= w;i++){
			sort(d[i].begin(), d[i].end(), cmp);
		}
		for(int c = 1;c <= n;c++){
			int Max = 0;
			bool flag = 1;
			for(int i = 1;i <= w;i++){
				if(c == cnt[i] + 1){
					flag = 0;
					break;
				}
				Max = max(Max, d[i][c - 1].y);
			}
			if(!flag){
				break;
			}
			for(int i = 1;i <= w;i++){
				lim[d[i][c - 1].id] = Max;
			}
		}
		int q;
		scanf("%d", &q);
		int t, a;
		while(q--){
			scanf("%d%d", &t, &a);
			if(lim[a] == 0 || lim[a] > t){
				puts("Yes");
			}
			else puts("No"); 
		}
		return 0;
	}
} 
signed main(){
	return Luo_ty::main();
}//International Milan is the best team.
```

---

## 作者：jess1ca1o0g3 (赞：1)

我们只需要预处理每个块什么时候消失。而每个块只有当它在最下面并且整行填满的时候才会消失。对于**一排**（如样例1中的块 $1,3,4$）来说，由于块不断下落，这**一排**消失的时间都是它们中最高的那个。而每秒往下掉 $1$ 排，所以消失时间就是最高的高度。可以用一个 `vector` 维护每一列的块，枚举过去。这一部分是线性的。而单次查询是常数。复杂度 $\mathcal{O(n+q)}$。[代码](https://paste.ubuntu.com/p/NPSqXsVMwV/)。

---

## 作者：wuzebang2009 (赞：1)

## 题目描述：
  在一个宽度为 $W$ 长度为 $1e9$ 的矩形中有 $N$ 个  $1\times1$ 的小方格 $A_i(1\le{i}\le{N})$，他们在下面不是地板并且也不是其他小方格的时候每单位时间都往下移动一个，如果最后一行 $W$ 列都有一个小方格，那么他们全都消失。
  
  $Q$ 次询问每次输入 $T_i$ , $A_i$ $(1\le{i}\le{Q})$ ，如果 $T_i+0.5$ 秒后 $A_i$ 还在输出 `Yes` ,不然输出 `No`。

## 题目思路
![1](https://img.atcoder.jp/abc391/4a6590753edcbad7ea1e8ce7f172902a.png)

我们将每个方格所在列的第几个记录下来，若有多个方格所在列的位置相同，那么他们最终会落在矩形中的同一行。
我们在记录每一行最高的为 $maxn_y(1\le{y}\le{W})$，并且记录方格最少的列有几个方格为 $minn$，现在只有 $A_i$ 所在的位置，即本列的所在的行数小于等于 $minn$ ，并且 $T_i+0.5 >maxn_y$ 这样才输出`No`，不然输出`Yes`。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,w,q,minn=1e9;
vector<int> a[200010];
int maxn[200010];
int b[200010];//记录所在行
int c[200010];

int main(){
    cin>>n>>w;
    for(int i=1;i<=n;i++){
        int x,y;
        cin>>y>>x;
        // swap(x,y);
        a[y].push_back(i);
        b[i]=a[y].size();
        c[i]=x-1;
    }
    for(int i=1;i<=w;i++){
        minn=minn<a[i].size()? minn:a[i].size();
    }
    for(int i=0;i<minn;i++){
        for(int j=1;j<=w;j++){
            maxn[i]=max(maxn[i],c[a[j][i]]);
        }
    }
    cin>>q;
    while(q--){
        int t,s;
        cin>>t>>s;
        if(b[s]>minn) cout<<"Yes"<<endl;
        else if(maxn[b[s]-1]>t-1) cout<<"Yes"<<endl;
        // cout<<maxn[b[s]-1]<<endl;
        else if(maxn[b[s]-1]<=t-1)cout<<"No"<<endl;
    }
}
```

---

## 作者：_Kenma_ (赞：0)

## 前言

推销博客：[here.](https://www.cnblogs.com/Kenma/p/18696757)

## 正文

有一些细节的模拟题。

消除的总行数为所有列中方格数量的最小值，下面记为 $sum$。

设每个方格在本列中从下到上处在 $k$ 的位置，那么：

- $k \le sum$，这个方格被消除的时间为所有处在 $k$ 位置的格子中，$x$ 的最大值；

- $k >sum$，这个方格不会被消除。

排序后直接做就行。

总体复杂度 $O(n \log n+q)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int inf=1e9+10; 
int n,m,q,x,y,ans,flag,maxn,minn,tim[1000005];
struct node{
	int x,id;
};
vector<node> v[1000005];
bool cmp(node a,node b){
	return a.x<b.x;
}
int main(){
	flag=true;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>x>>y;
		tim[i]=inf;
		v[x].push_back((node){y,i}); 
	}
	ans=inf;
	for(int i=1;i<=m;i++){
		sort(v[i].begin(),v[i].end(),cmp);
		ans=min(ans,(int)v[i].size());
	}
	for(int i=0;i<ans;i++){
		maxn=0;
		for(int j=1;j<=m;j++){
			maxn=max(maxn,v[j][i].x);
		}
		for(int j=1;j<=m;j++){
			tim[v[j][i].id]=maxn;
	    }
	}
	cin>>q;
	for(int i=1;i<=q;i++){
		cin>>y>>x;
		if(y<tim[x]) cout<<"Yes"<<'\n';
		else cout<<"No"<<'\n';
	}
	return 0;
} 
```

---

## 作者：Jayfeather2012 (赞：0)

## 题意
这是一个类似俄罗斯方块的题目，有一个无限高度，宽度为 $W$ 的网格，网格中有 $n$ 个方块。  
对于每一秒，当最底下一行被填满，将最底下一行清空，当一个方块悬空，此方块就会下落。  
给出 $n$ 方块的位置，并做 $q$ 次询问，求在某一时刻，某一颗球是否存在。
## 思路
根据题意，我们可以发现：每列距离底部最近的方块到达底部的时间是其中距离底部最远的方块到达底部的时间，也就是它与底部的距离。  
因为每个方块移动一格的时间相同且所有可以被消除的方块都会成为当列距离底部最近的方块，所以此发现适用于所有可以被消除的方块，也就是：每列距离底部第 $x$ 近的方块到达底部的时间是其中距离底部最远的方块与底部的距离。  
按照此思路编写代码：定义数组 ans 记录每个方块被消除的时间（即到达底部的时间），先把每个方块按照横坐标分门别类地放好（用 vector 维护），再将所有横坐标相同的方块按照与底部的距离排序，根据发现找出每列距离底部第 $x$ 近的方块中距离底部最远的方块到达底部的时间，并把这个时间赋给所有距离底部第 $x$ 近的方块。为了方便查询，我们把无法被消除的方块的消除时间定为极大值。  
最后，我们根据 ans 数组的值回答问题。  
具体细节看代码吧！
## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define pp pair<int,int>
using namespace std;
int n,w,q,x,y,m=1e9,ans[200005];
vector<pair<int,int>>a[200005];//定义vector，first存与底部的距离，second存编号，方便排序和赋值
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	memset(ans,63,sizeof(ans));
    //初始化极大值。
	cin>>n>>w;
	for(int i=1;i<=n;++i){
		cin>>x>>y;
		a[x].push_back(make_pair(y,i));
        //根据横坐标分类。
	}
	for(int i=1;i<=w;++i){
		sort(a[i].begin(),a[i].end());//排序。
		int x=a[i].size();
		m=min(m,x);
        //找出能被消除的方块的最大行数。
	}
	for(int i=0;i<m;++i){
		int s=0;
		for(int j=1;j<=w;++j)s=max(a[j][i].first,s);
        //找出每列距离底部第i近的方块中距离底部最远的方块到达底部的时间。
		for(int j=1;j<=w;++j)ans[a[j][i].second]=s;//赋值。
	}
	cin>>q;
	while(q--){
		cin>>x>>y;
		if(ans[y]>x)cout<<"Yes\n";
		else cout<<"No\n";
        //根据ans数组的值回答问题。
	}
	return 0;
}

```

---

## 作者：Yuexingfei_qwq (赞：0)

最恨 ABC 的 D 题了，每次都让我卡住。
## 思路  
用一个 `vector<pair<int, int>>` 储存每一列中的所有方块的 $y$ 坐标和方块编号，接着对于每一列的 `vector` 做一个降序排序。  

然后用 $t_i$ 记录方块 $i$ 消失的时间，永远不会消失记为 $10^{18}$。  

看样例解释中的图可发现最下面的完整的 $k$ 排中，第 $i(1 \le 1 \le k)$ 排方块的消失时间是这一排方块中 $y$ 坐标最大的方块的 $y$ 坐标，只要处理出这些方块的消失时间，其他设为 $10^{18}$ 就可以 $O(1)$ 回答每个询问了。
## AC CODE  
```cpp
#include <bits/stdc++.h>
#define el "\n"
#define sp " "
#define fi first
#define se second
#define inf 1e18
#define r0 return 0
#define int long long
#define F(i, a, b, c) for (int i = a; i <= b; i += c)
#define debug printf ("bug is in here\n")
#define TheEnd continue
#define base(s) s = sp + s
#define lcm(a, b) a / __gcd(a, b) * b
#define setp(x) fixed << setprecision(x)

using namespace std;

typedef long long ll;
typedef string str;
using ull = unsigned ll;

int n, w;
std::vector<std::pair<int, int>> e[210000];
int t[210000];
int q;

signed main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);
	cin >> n >> w;
	F(i, 1, n, 1) {
		int x, y;
		cin >> x >> y;
		e[x].push_back({y, i});
	}
	F(i, 1, w, 1) {
		std::sort(e[i].begin(), e[i].end(), std::greater<std::pair<int, int>>());
	}
	F(i, 1, n, 1) {
		t[i] = inf;
	}
	int mi = inf;
	F(i, 1, w, 1) {
		mi = std::min(mi, (int)e[i].size());
	}
	F(i, 1, mi, 1) {
		int ma = -inf;
		F(j, 1, w, 1) {
			ma = std::max(ma, e[j].back().fi);
		}
		F(j, 1, w, 1) {
			t[e[j].back().se] = ma;
		}
		F(j, 1, w, 1) {
			e[j].pop_back();
		}
	}
	cin >> q;
	while (q--) {
		int T, x;
		cin >> T >> x;
		if (t[x] > T) {
			cout << "Yes";
		} else {
			cout << "No";
		}
		cout << el;
	}
	r0;
}
```

[AC 记录](https://atcoder.jp/contests/abc391/submissions/62308035)

--- 
完结~~不~~散花。

---

## 作者：201012280925LSY (赞：0)

## 题意
在一个有 $10^9$ 行 $W$ 列的网格图上，有 $N$ 个小方块。在开始时，第 $i$ 个小方块在从左往右第 $Y_i$ 列，从下往上第 $X_i$ 行。每一时刻，如果第一行的每一列上都有方块，那么这些方块就都会消掉。然后如果一个小方块不在第一行，并且下面没有方块的话，就会往下落。方块是在下面的先往下落，之后上面的才往下落。

然后有 $Q$ 个询问，每个询问有两个参数 $T$ 和 $A$。表示询问在时刻 $T+0.5$ 时，方块 $A$ 是否仍然存在。
## 思路
思路很显然，注意到如果需要消掉一些方块，那么这些方块在每一列上，在它们下面的方块数量都是相等的。我们把会一起消掉的方块称为同一层。

所以我们先预处理出每一个方块是在哪一层。然后如果一层方块要消掉，就是方块中到达最底下所需要的时间最大的这个时间，就是它们消掉的时间。

所以我们把同一层的方块放进一个队列中，如果这一层的方块的数量不足以达到 $W$，说明它们都不可能会被消掉。否则计算它们到达最底层的时间。有两种情况：

- 方块到达最底层的时间比它下面的方块要大，那么它的时间直接取到达最底层的时间即可。
- 方块到达最底层的时间比它下面的方块小，说明它还要等它下面的方块消掉才能到达最底层。所以取上一层方块消失的时间。

我们处理出每个方块消失的时间之后按照题意输出即可。

具体见代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,w;
deque<long long>dq[200010];//每一层方块。
struct block//一个方块的基本信息。
{
	long long x,y;//开始在哪个位置。
	long long no;//编号。
	long long deep;//在哪一层。
	long long time;//消失的时间。
}a[200010]; 
long long t[200010];//每一层消失的时间。
long long max_deep;//最多到几层。
bool cmp_deep(block a,block b)//按深度排序。
{
	if(a.x!=b.x)
	{
		return a.x<b.x;
	}
	else return a.y<b.y;
}
long long get(long long no)//处理一个方块消失的时间。
{
	if(a[no].y-1>=t[a[no].deep-1])
	{
		return a[no].y-1;
	}
	else
	{
		return t[a[no].deep-1];
	}
}
bool cmp_number(block a,block b)//按编号排序。
{
	return a.no<b.no;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>w;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i].x>>a[i].y,a[i].no=i;
	}
	sort(a+1,a+n+1,cmp_deep);
	long long num=0;
	a[0].x=-1;
	for(int i=1;i<=n;i++)//预处理方块在那一层。
	{
		if(a[i].x!=a[i-1].x)
		{
			num=0;
		}
		num++;
		a[i].deep=num;
		dq[num].push_back(i);//同一层的方块。
		max_deep=max(max_deep,num);
	}
	for(int i=1;i<=max_deep;i++)//按思路处理。
	{
		long long max_time=0;
		if(dq[i].size()<w)//没达到 W 个方块。
		{
			while(!dq[i].empty())dq[i].pop_front();
			t[i]=1e18;
			continue;
		}
		while(!dq[i].empty())
		{
			long long now=dq[i].front();
			dq[i].pop_front();
			a[now].time=get(now);//取最大的时间。
			max_time=max(max_time,a[now].time);
		} 
		t[i]=max_time+1;//得等所有方块到达最底下，下一时刻才能消掉。
	}
	for(int i=1;i<=n;i++)
	{
		a[i].time=t[a[i].deep];
	}
	sort(a+1,a+n+1,cmp_number);//记得把方块按照编号排回来。
	long long q;
	cin>>q;
	for(int i=1;i<=q;i++)
	{
		long long t,num;
		cin>>t>>num;
		if(t<a[num].time)//还没消失。
		{
			cout<<"Yes\n";
		}
		else//消失了。
		{
			cout<<"No\n";
		 } 
	}
	return 0;
}
```

---

## 作者：linjinkun (赞：0)

前置知识：
- `map`
- `priority_queue`
### 思路
考虑预处理每一个图块在第几秒后会被删除。

如何预处理？我使用了一种非常暴力的做法，首先处理的过程肯定是从下往上的，于是每一个图块能被删除一定是它对应的每一列都至少有一个图块，而且每次我们肯定都是选择这个图块对应的每一列的离最下面最近的图块去拼成一个全满的形态，然后消消乐，第几秒才能达到全满的形态呢？自然就是选择的图块中离最下面最远的点的高度，每一次选完后都把这些点删掉。
### 步骤
一开始用一个 `map` 记录每个坐标是哪个图块，用优先队列存储所有坐标中列数是这个列的所有行，按升序排序，一开始让所有列全部放入另一个 `map`，对于 `map` 中的元素 $i$，取出第 $i$ 个优先队列的队首，如果这个队列空了，那就在这第二个 `map` 中删掉这个元素，然后秒数就是每一个元素取出的队首中的最大值，至于为什么需要第二个 `map`，是因为如果这样每次都遍历所有列，时间复杂度会超，所以需要一个 `map` 时时删除不需要遍历的列。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5+5;
map<pair<int,int>,int>mp;
int num[N];
priority_queue<int,vector<int>,greater<int>>q[N];
map<int,int>mp1;
signed main()
{
    int n,w;
    scanf("%d %d",&n,&w);
    for(int i = 1;i<=n;i++)
    {
        int x,y;
        scanf("%d %d",&x,&y);
        swap(x,y);
        mp[{x,y}] = i;
        if(mp1.find(y) == mp1.end())
        {
            mp1[y] = 1;
        }
        q[y].push(x);
    }
    while(mp1.size())
    {
        int maxx = 0;
        if(mp1.size() == w)//如果可以组成全满形态
        {
            for(auto it = mp1.begin();it!=mp1.end();it++)
            {
                int y = it->first;
                int x = q[y].top();
                maxx = max(maxx,x);
            }
        }
        else
        {
            maxx = 2e9;//如果不能组成全满形态，那么选出的这些图块就不会被删
        }
        for(auto it = mp1.begin();it!=mp1.end();)
        {
            int y = it->first;
            int x = q[y].top();
            q[y].pop();
            num[mp[{x,y}]] = maxx;
            if(!q[y].size())
            {
                it = mp1.erase(it);
            }
            else
            {
                it++;
            }
        }
    }
    int _;
    scanf("%d",&_);
    while(_--)
    {
        int x,y;
        scanf("%d %d",&x,&y);
        if(x>=num[y])
        {
            printf("No\n");
        }
        else
        {
            printf("Yes\n");
        }
    }
    return 0;
}
```

---

## 作者：D0000 (赞：0)

首先按照题意模拟可能有点难写，而询问某个时间某个格子在不在只需要求出每个格子被删除的时间就可以了（或者永远删不掉）。对于每个格子 $i$，记它是所在列行数第 $k_i$ 小的。由于删除时只会删最下面一行，因此 $k_i$ 值一样的是同时删除的。于是答案 $ans_i$ 为每一列第 $i$ 小的多久删除。显然有 $ans_i=\max(ans_{i-1},\max_j y_j[k_j=i])+1$，因为只有等每一列行数为第 $i-1$ 小的删除了，且所有行数在那一列第 $i$ 小的都落下来了才能把它们都删掉。另外，如果某一列的格子不足 $i$ 给，那行数为当列第 $i$ 小的就永远删不掉，此时 $ans_i=\infty$。

### 代码

```cpp
#include<cstdio>
#include<vector>
#include<algorithm>
int n,w;
struct node{
    int x,y,ra,id;
}a[200005];
int ans[200005],si[200005],ss[200005];
bool c1(node xx,node yy){
    return xx.y<yy.y;
}
bool c2(node xx,node yy){
    if(xx.ra==yy.ra)return xx.y<yy.y;
    return xx.ra<yy.ra;
}
bool c3(node xx,node yy){
    return xx.id<yy.id;
}
int main(){
    scanf("%d%d",&n,&w);
    for(int i=1;i<=n;i++){
        scanf("%d%d",&a[i].x,&a[i].y);
        a[i].id=i;
    }
    std::sort(a+1,a+n+1,c1);
    for(int i=1;i<=n;i++)si[a[i].x]++,a[i].ra=si[a[i].x];
    std::sort(a+1,a+n+1,c2);
    for(int i=1;i<=n;i++){
        if(a[i].ra>1&&ss[a[i].ra-1]<w)break;ss[a[i].ra]++;
        if(ss[a[i].ra]==w)ans[a[i].ra]=std::max(ans[a[i].ra-1],a[i].y)+1;
    }
    for(int i=1;i<=n;i++)if(!ans[i])ans[i]=1e9+1;
    std::sort(a+1,a+n+1,c3);
    //for(int i=1;i<=n;i++)printf("%d %d\n",a[i].id,a[i].ra);
    scanf("%d",&w);//printf("(%d)",ans[1]);
    while(w--){
        int t,aa;
        scanf("%d%d",&t,&aa);
        if(ans[a[aa].ra]<=t+1)puts("No");
        else puts("Yes");
    }
}
```

---

## 作者：Tiger_Rory (赞：0)

主要思路：我们发现，只要预处理出可能消失的方块们消失的时间就可以快速求出答案。所以我们考虑开 $W$ 个桶对应 $W$ 个竖列，记录下每个竖列的方块的纵坐标，再一一求出它们的消失时间与询问时间比大小即可。我们注意到要最底行塞满方块才能使得方块消失，那么位于每个桶中相同位置的方块们消失时间必然相同，而这个时间就是这一组方块中所需掉落时间最长的方块的时间。那就一组一组处理就结束了！（这是代码中标注的第一步）。

样例过了，满怀信心交上去，吃了一发罚时。

认真又看了一遍，发现存在样例中未涉及的底下方块阻拦上面方块消除的情况，那就加上阻拦的时间！（这是代码中标注的第二步）。

终于过了。

下面是参考代码。


```cpp
#include<bits/stdc++.h>
using namespace std;
int n, w, i, j, q; 
const int maxn = 2e5 + 10, inf = 1e9;
int x, y, t, a, ans[maxn], minn; //ans数组为方块消失所需时间 
map<int, map<int,int> >mp; 
//用来记录每个方块的横纵坐标 
vector<int> yy[maxn]; //桶 
void init(){ //预处理 
	minn = inf; 
	for(i = 1; i <= w; i++) {
		minn = min(minn, (int)yy[i].size()); 
		//打擂台求最多消失多少行方块 
		sort(yy[i].begin(), yy[i].end()); 
		//将纵坐标排序 
	}
	for(i = 0; i <= minn - 1; i++) { //一行一行处理 
		int maxx = -1; 
		for(j = 1; j <= w; j++) {
			maxx = max(yy[j][i], maxx);  
			//求消失时间第一步  
		}
		if(i > 0 && maxx < ans[mp[1][yy[1][i - 1]]]) maxx += ans[mp[1][yy[1][i - 1]]] - maxx + 1;//第二步 
		for(j = 1; j <= w; j++) {
			ans[mp[j][yy[j][i]]] = maxx; 
		}
	}
	return; 
}
int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n >> w; 
	for(i = 1; i <= n; i++) {
		cin >> x >> y; 
		mp[x][y] = i; 
		yy[x].push_back(y); 
		ans[i] = inf; 
	}
	init(); 
	cin >> q; 
	for(i = 1; i <= q; i++) {
		cin >> t >> a; 
		if(ans[a] <= t) {
			cout << "No\n"; 
		} else {
			cout << "Yes\n"; 
		} 
	}
	return 0;
}
```
如有不足，还请指出，谢谢大家。

---

## 作者：DoubleQLzn (赞：0)

观察发现，点到最后一行时只有全部满才消失，每个点到最后一行需要 $y_i$ 秒，所以记录每一个列的第 $i$ 个掉落到最后一行的元素，然后取 $y_i$ 的最大值就是那些点的降落时间。最后判断 $t$ 是否小于降落时间即可。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
struct Node 
{
	int x,y,bh;
} a[200005];
vector<Node> g[200005];
int down[200005],f[200005];
bool cmp(Node a,Node b)
{
	return a.y < b.y;
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n,w,q;
	cin >> n >> w;
	for (int i = 1;i <= n;i++) 
	{
		cin >> a[i].x >> a[i].y;
		a[i].bh = i;
	}
	sort(a + 1,a + n + 1,cmp);
	int now = INT_MIN;
	for (int i = 1;i <= n;i++)
	{
		f[a[i].x]++;
		now = max(now,f[a[i].x]);
		g[f[a[i].x]].push_back({a[i].y,a[i].bh});
	}
	int isinf = 0;
	const int out = 1e9 + 1;
	for (int i = 1;i <= now;i++)
	{
		if (g[i].size() != w) isinf = 1;
		int ma = INT_MIN;
		for (auto j : g[i]) ma = max(ma,j.x);
		for (auto j : g[i])
		{
			if (!isinf) down[j.y] = ma;
			else down[j.y] = out;
		}
	}
	cin >> q;
	while (q--)
	{
		int t,a;
		cin >> t >> a;
		if (t < down[a]) cout << "Yes\n";
		else cout << "No\n";
	}	
	return 0;
}
```

---

## 作者：Merge_all (赞：0)

# Preface:
一道小模拟题，感觉不算特别难。
# Description:
有 $n$ 个方块在第 $x$ 列中的第 $y$ 行，每秒会向下移动一格，当铺满了底面（即 $x = 1$ 行上有 $w$ 个方块）这一行就会被消除。

移动方式：1. 移动以后不越界。2. 底下不堵塞。

不懂的可以看翻译和样例解释。
# Solution:
![](https://cdn.luogu.com.cn/upload/image_hosting/7rh7ydux.png)

我们先把每一行、每一列按从小到大进行排序。

对于每一列，从前往后从 $1$ 开始编号，表示最终落下来时这是第几行。

定义 $Max_i$ 表示第 $i$ 行中 $y$ 值的最大值。

则第 $i$ 行消除的时间 $die_i$ 满足递推式：

$$die_1 = Max_1$$
$$die_i = \max (Max_i, die_{i - 1})$$

但是又有一个问题：如果说这一行不论多久都消除不了，那该怎么办？

其实最多能消除的就是每一行元素个数的最小值 $L$，一旦前面递推的边界也是到 $L$。

所以问题就转化成为了如何快速查找一个坐标在第 $x$ 列中是第几个。

显然可以用二分找到，然后就判断即可。

详细的看代码。
# AC code:
```
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using Int = __int128;
using pii = pair<int, int>;
const int N = 2e5 + 5;
int n, w, q, t, id;
pii arr[N];
vector<int> vec[N];
vector<int> line[N];
int Max[N], die[N], Long = 0x3f3f3f3f, lst;
int Find (int num, int value) {
	int l = 0, r = vec[num].size() - 1;
	while (l <= r) {
		int mid = l + (r - l) / 2;
		if (vec[num][mid] == value) return mid;
		else if (vec[num][mid] < value) l = mid + 1;
		else r = mid - 1;
	}
	return -1;
}
int main (int argc, char *argv[]) {
	*cin.tie(nullptr) << fixed << setprecision(20);
	cout.tie(nullptr) -> ios_base::sync_with_stdio(false);
	
	cin >> n >> w;
	for (int i = 1; i <= n; i ++) {
		cin >> arr[i].first >> arr[i].second;
		vec[arr[i].first].push_back(arr[i].second);
	}
	for (int i = 1; i <= w; i ++) {
		stable_sort (vec[i].begin(), vec[i].end());
		Long = min (Long, (int) vec[i].size());
		for (int j = 0; j < (int) vec[i].size(); j ++)
			Max[j + 1] = max (Max[j + 1], vec[i][j]);
	}
	die[1] = Max[1];
	for (int i = 2; i <= Long; i ++)
		die[i] = max (die[i - 1], Max[i]);
	cin >> q;
	for (int Tc = 1; Tc <= q; Tc ++){
		cin >> t >> id;
		if (arr[id].second > t) {//如果本身的高度比 t 还高那么一定还存在
			cout << "Yes\n";
			continue;
		}
		int idx = Find (arr[id].first, arr[id].second);//从 0 开始的
		if (idx + 1 > Long) {//如果当前这一行在最多能消除的行数之上，那么不管多久都不会消除
			cout << "Yes\n";
			continue;
		}
		if (die[idx + 1] > t) {//如果消除的时间要比 t 长，那么现在肯定没有被消除
			cout << "Yes\n";
			continue;
		}
		cout << "No\n";
	}
	return 0;
}
```

---

## 作者：Aegleseeker_ (赞：0)

有些细节的模拟题。

![](https://img.atcoder.jp/abc391/4a6590753edcbad7ea1e8ce7f172902a.png)

我们这里先简化一下题意。对于样例里的那张图，我们将 $1,3,4$ 视为「一行」，剩下的 $2,5$ 视为「一行」。

对于时刻 $t=1$，$1,3,4$ 这「一行」还没有补齐，于是 $3,4$ 所在的第二、三列整体下降了一格。

对于时刻 $t=2$，$1,3,4$ 这「一行」补齐了，于是这「一行」被消掉了。

对于时刻 $t\ge 3$，$2,5$ 这「一行」永远也无法无法补齐，因此不再继续考虑。

理解清楚样例在干什么后，基本也就有思路了。由于一行要消除当且仅当底下那行全被覆盖了，所以我们要维护的并不是一开始的行，而是会作为同一次消除的「一行」，也既样例中的 $1,3,4$（尽管它们最开始并不处在同一行）。

对于每一列 $1\le i\le w$，我们开一个 `vector` $v_i$ 存储这一列中所有的点，并应该按照 $y$ 轴升序/降序（取决于实现）排序。

我们考虑枚举每「一行」，既我们当前要消除这「一行」。

判断是否有 $v_i$ 为空，若有则直接跳出循环。

否则我们统计每一列所对应的那「一行」的元素要到最低行，需要多长时间。我们这里取个 $\max$ 即可，然后计算答案。

注意到当前时刻前的所有修改都会对当前时刻造成影响，我们开一个数组 $\operatorname{tag_i}$ 存储第 $i$ 列下降了多少，类似于懒标记的形式。

代码并不复杂，但有些小细节。建议多加调试，尽量避免罚时。

submission：https://atcoder.jp/contests/abc391/submissions/62298710

---

## 作者：StarsIntoSea_SY (赞：0)

不难发现，所有会被消掉的方块的个数等于每一列中方块数最小的一列乘以列数。即 $w\min_{i=1}^{w} d[i]$，$d[i]$ 表示第 $i$ 列中方块的个数。如样例一，第三列只有一个方块，共三列，那么一共就会有 $1 \times 3 = 3$ 个方块会被消掉。

我们只需要看这些会被消掉的块即可。

令 $t=\min_{i=1}^{w}d[i]$，从 $i=1$ 到 $i=t$，枚举每一列下方第 $i$ 个块，这些块一起被消掉的时间必定为这些块中 $y$ 坐标的最大值。

证明：$i=1$ 时，所有块下落不会受到其它块的影响。$i=2$ 时，可能会受下方块的影响，但是由于所有 $i=1$ 的块 $y$ 坐标最大值必定**小于**所有 $i=2$ 的块 $y$ 坐标最大值。因此当 $i=2$ 的最高的块下落至底时，$i=1$ 的块必定会被消除，此时和 $i=1$ 的块的情况相同，$i>2$ 的情况同理。

这样我们知道了每个块被消掉时的时间，询问就很简单了。

时间复杂度 $O(N)$。

[赛时代码](https://atcoder.jp/contests/abc391/submissions/62283704)。

---

## 作者：Tairitempest (赞：0)

## [ABC391D] Gravity

对于一个方块，如果消掉，必须满足两个条件：

- 这个方块所在的这一行能凑齐。
- 这个方块下面的方块已经被消掉。

对于一个方块，如果知道它消掉的时间，自然也就知道每一刻其存在性。因此可以对方块按高度排序，然后用队列维护每一列从下往上的方块序列。每次遍历所有的列，将每一列最下层的方块消掉，为最下层方块的消除时间赋值（该时间等于该层方块最大下落时间和其下面一层消掉时间的最大值加一）。这一过程顺带还能判断这一行能否凑齐，可以证明如果一行凑不齐，那么其上面的行必定凑不齐。

离线模拟这个过程，每次询问比较已有值即可。

由于每个方块最多被计算一次，复杂度约为 $O(N \log N)$，复杂度瓶颈在排序，但足以通过本题。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll N,lst,W,T[200010],Q;
struct P{
	ll x,y,id;
} p[200010];
bool comp1(P A,P B){
	return A.y<B.y;
}
bool comp2(P A,P B){
	return A.id<B.id;
}
queue<ll> up[200010];
queue<ll> level;
void setblock(){
	while(true){
		ll maxT=lst+1;
		for(int i=1;i<=W;i++){
			if(up[i].empty()) return;
			else{
				ll nxt=up[i].front();
				level.push(nxt);
				up[i].pop();
				maxT=max(maxT,p[nxt].y);
			}
		}
		lst=maxT;
		while(!level.empty()){
			ll nxt=level.front();
			T[nxt]=maxT;
			level.pop();
		}
	}
}
int main(){
	cin>>N>>W;
	for(int i=1;i<=N;i++){
		cin>>p[i].x>>p[i].y;
		p[i].id=i;
		T[i]=1e17;
	}
	sort(p+1,p+N+1,comp1);
	for(int i=1;i<=N;i++)
		up[p[i].x].push(p[i].id);
	sort(p+1,p+N+1,comp2);
	setblock();
	cin>>Q;
	while(Q--){
		ll TQ,AQ;
		cin>>TQ>>AQ;
		if(TQ<T[AQ]) cout<<"Yes"<<endl;
		else cout<<"No"<<endl;
	}
	return 0;
}
```

---

## 作者：Cosine_Func (赞：0)

很显然，本题中每列的方块都与彼此的掉落用时相关，因此可以按横坐标将方块分成 $W$ 部分，并分别装进数列中。我们知道，一组方块消失的用时取决于掉落用时的最长值，因此将方块装进队列，每次取队首元素处理。可以发现，纵坐标越小，掉落用时越短，因此可以将队列替换成堆。由此可以预处理出方块消失的时间，能够实现 $O(1)$ 查询。时间复杂度等下再考虑，先看预处理部分核心代码：
```cpp
    for(int i=1;i<=n;i++){
		pos[x[i]].push(make_pair(y[i]-1,i));
	}
	while(1){
		int ok=1,ans=0;
		for(int i=1;i<=w;i++){
			if(pos[i].empty()){
				ok=0;
				break;
			}
			ans=max(ans,pos[i].top().first);
		}
		if(ok==0)break;
		for(int i=1;i<=w;i++){
			res[pos[i].top().second]=ans+1;
			pos[i].pop();
		}
	}
```
乍一看，这段代码的时间复杂度好像是 $O(NW\log N)$。但是经过观察可以发现，每个方块都最多被处理一次，因此预处理的时间复杂度为 $O(N\log N)$，总时间复杂度为 $O(N\log N+Q)$。还有一种先排序再放入队列的写法，时间复杂度与此相同，读者可自行实现。

[参考代码](https://atcoder.jp/contests/abc391/tasks/abc391_d)

---

## 作者：Chenyichen0420 (赞：0)

## 思路分析

不难注意到，这些方块是从下往上一层一层的消除的。因此，我们可以将这个层序手动剥出来，每一个 $x$ 维护一个 `vector`，按照 $y$ 升序排列就行了。每一次取出每一个 $x$ 的第一个值就是一层。当某一个 $x$ 没有值的时候，剩下的就是永远也不会被消除的了。

但是，被消除的我们怎么知道他们是什么时候被消除的呢？其实从相对运动的角度去看，方块下落和底线上升并没有本质的区别。一层被消除当且仅当这一层的最靠上的方块也被底线压在底下。因为下层先于上层进行判断，所以一层被消除掉后上一层不会被本质上影响。

也就是说，假设 $b_1,b_2,\dots,b_k$ 是同一层的方块，在 $T\le\max_{i=1}^k(y_{b_i})$ 时，这些方块存在；反之则消失。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,t[200005]; vector<pair<int,int>>ps[200005];
signed main(){
	ios::sync_with_stdio(0);
	cin>>n>>m; memset(t,0x3f,sizeof t);
	for(int i=1,a,b;i<=n;++i)
		cin>>a>>b,ps[a].emplace_back(make_pair(b,i));
	for(int i=1;i<=m;++i)
		sort(ps[i].begin(),ps[i].end());
	int lh=0;
	for(int p=0;;++p){
		bool cn=1;
		for(int i=1;i<=m;++i)
			if(ps[i].size()==p){
				cn=0; break;
			}
			else lh=max(lh,ps[i][p].first);
		if(!cn) break;
		for(int i=1;i<=m;++i)
			t[ps[i][p].second]=lh;
	}
	cin>>k;
	for(int i=1,a,b;i<=k;++i)
		if(cin>>a>>b,t[b]>a) puts("Yes");
		else puts("No");
}
```

---

## 作者：cuiwl123 (赞：0)

看到题面很容易联想到俄罗斯方块，没有填满的层数的木块永远不会消失，其余每一层的方块消失的时间都同这一层最后落到底部的方块落到底部的时间即 $y_i$ 相同。  
考虑预处理出每层方块消失的时间，然后在查询时与 $T_i$ 比较，从而得出答案。   
先将同一列的方块放入同一个数组中，按照每个方块的 $y$ 值排序，此时每个方块的下标就代表了它的层数,记录每层木块消失的时间即可。时间复杂度 $O(n\log{n}+q)$  
代码可能写的有些复杂
```cpp
#include<bits/stdc++.h>
using namespace std;
struct BLOCK
{
	int x,y,num;
}a[200005];
struct NODE
{
	int fi,se;
	bool operator < (const NODE &x) const
	{
		return fi<x.fi;
	}
};
int n,w,q,minnum=1e9,t[200005];
vector<NODE> block[200005];
int main()
{
	cin>>n>>w;
	for(int i=1;i<=n;i++)
		cin>>a[i].x>>a[i].y,block[a[i].x].push_back(NODE{a[i].y,i});
	for(int i=1;i<=w;i++)
		sort(block[i].begin(),block[i].end());
	for(int i=1;i<=w;i++)
	{
		minnum=min(minnum,(int)block[i].size()-1);
		for(int j=0;j<block[i].size();j++)
			a[block[i][j].se].num=j;
	}
	for(int i=0;i<=minnum;i++)
	{
		int maxtime=-1e9;
		for(int j=1;j<=w;j++)
			maxtime=max(maxtime,max(0,block[j][i].fi-t[max(0,i-1)]));
		t[i]=t[max(0,i-1)]+maxtime;
	}
	//cout<<minnum<<endl<<endl;
//	for(int i=0;i<=minnum;i++)
		//cout<<t[i]<<endl;
	cin>>q;
	while(q--)
	{
		int ti,m;
		cin>>ti>>m;
		//cout<<a[m].x<<" "<<a[m].y<<" "<<a[m].num<<endl;
		if(a[m].num>minnum) cout<<"Yes"<<endl;
		else 
		{
			if(t[a[m].num]<=ti) cout<<"No"<<endl;
			else cout<<"Yes"<<endl;
		}
	}
	return 0;
}

---

