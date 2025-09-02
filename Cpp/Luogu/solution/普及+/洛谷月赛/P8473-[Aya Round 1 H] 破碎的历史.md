# [Aya Round 1 H] 破碎的历史

## 题目背景

幻想乡迎来了它的毁灭，幻想的载体也已经遁入了幻想。

所幸的是，幻想乡中的乡民们还侥幸存活着，她们在尝试恢复幻想乡的历史。然而历史之中的大大小小的事情不计其数，人们只能记得起一些大事情罢了。

或许，根据那些重要的事情，可以把次要的事件推导出来呢？

## 题目描述

数轴的正半轴上有 $n$ 个互不相同的被黑白染色的特殊整点，位置从左到右依次为 $p_1,p_2,\cdots,p_n$。维护初始为空的**可重**线段集合 $S$。

$q$ 次操作。操作分若干种，具体格式如下：

- `1 l r`：将所有满足 $l \le x \le y \le r$ 且两端点均为特殊整点的线段 $[x,y]$ 加入 $S$。
- `2 x`：撤回第 $x$ 次操作添加的线段。

在初始时和每次操作后，假设你可以进行任意次（可以是零次）染色。每次从 $S$ 中选出一条线段 $[x,y]$，满足位于点 $x$ 和点 $y$ 的特殊整点均为黑色，然后将所有在线段内的白色特殊整点染黑。试判断是否存在至少一种合法染色方式使得正半轴上的所有特殊整点均被染黑（即，不存在白色特殊整点）。**注意：所有的询问均为「假设」，即各组询问之间独立，不会造成对数轴的实际修改。**


## 说明/提示

### 样例解释

六个特殊点的位置/颜色在数轴正半轴上如图所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/i1hfjrk8.png)

容易发现，并非所有点都是黑点。因此在进行操作前，输出 $\verb!NO!$。

第一次操作后，一共往 $S$ 加入了三条线段：$[5,5],[8,8],[5,8]$（图中省略了端点重叠的线段）。容易发现，此时无法进行任何操作，因此没法将所有点变成黑点。输出 $\verb!NO!$。

![](https://cdn.luogu.com.cn/upload/image_hosting/ayeijyli.png)

第二次操作后，又往 $S$ 中加入了 $20$ 条线段。除去端点重叠的选段，在 $S$ 中如图所示。（以示区别，上一次操作加入的边标成了深蓝色）。

![](https://cdn.luogu.com.cn/upload/image_hosting/icw9ar9m.png)

可以找出一种方案，将图上所有特殊点变成黑点。具体而言，首先选择 $S$ 中 $[1,5]$ 线段（容易发现位于 $1$ 和 $5$ 的特殊点均为黑点，因此可以进行染色），那么可以把位于 $2$ 和 $3$ 的点染色。

![](https://cdn.luogu.com.cn/upload/image_hosting/3k1uvul0.png)

此时又可以选择 $S$ 中 $[3,13]$ 线段（在上一轮操作中，$3$ 号点变为了黑点，因此 $[3,13]$ 符合条件），将点 $8$ 染为黑色。

![](https://cdn.luogu.com.cn/upload/image_hosting/7ebafj63.png)

此时所有点都为黑色，因此输出 $\verb!YES!$。再次强调，询问之间互相独立，且只是询问是否存在染色方案，而不会对特殊整点进行实际上的染色操作。

![](https://cdn.luogu.com.cn/upload/image_hosting/pjqpqvtr.png)

第三个操作撤回了第二个操作往 $S$ 里加入的所有线段。因此退回到了只有第一个操作的情况。不存在一种方案将所有点染黑，因此输出 $\verb!NO!$。

### 数据范围

对于所有数据，$1 \le n,q \le 5 \times 10^5$，$a_i \in \{0,1\}$，$1 \le l< r \le 10^9$，$1 \le p_i \le 10^9$。保证 $p_i$ 单调递增，$2$ 操作撤销的只会是 $1$ 操作，且每个操作最多被撤销一次。


## 样例 #1

### 输入

```
6 3
1 2 3 5 8 13
1 0 0 1 0 1
1 5 10
1 1 15
2 2
```

### 输出

```
No
No
Yes
No```

# 题解

## 作者：jjsnam (赞：19)

# 写在前面

**提供一种在线做法。**

这本来是一道绿题，但是我考试的时候脑抽了，一度认为是紫题往上，因为我熟悉的线段树 fail 了我 ಥ_ಥ。后来一看才发现是忘了每次都输出了，考试完恍然大悟，一交就过了，所以还是写一下，毕竟折磨了我一个多小时。

## 前置知识
- 线段树
- 模拟、贪心

## 题目描述（戳这里[查看原题](https://www.luogu.com.cn/problem/P8473)）

数轴上有一些黑白点（特殊整点），定义两个操作：

1. 将区间 $[l,r]$ 中所有特殊整点两两组成的线段加入一个**可重**集合 $S$ 中。
2. 撤销某次操作。保证撤销的操作类型为 1。

每次操作后可以任意次将 $S$ 中由**两个黑色点**组成的线段中间的所有点**染黑**。询问每次操作后是否可以将原数轴上所有点染黑？

# 正文

我这道题是一眼瞄出来的，因为昨天的 REOI 也考了一道线段树维护区间的题，所以有意往这方向想，不过我们还是仔细看看这题还有什么可以提示我们的。

题目里说各组询问互相独立，但其实模拟一下会发现只要顺着按最优方法模拟，询问间就不会有影响。可以在线。

## 分析

其实题目里说的很隐晦，似乎每次添加的线段很多，然而，真正有用的线段只和能否进行操作有关。因此，**对询问和修改有用的线段只有两端都是黑点的线段。**

再往深处想，对于每次操作 1，这段区间中最长的“两端黑线段”所起的作用一定能包括内部所有“两端黑线段”起的作用（**大区间一定覆盖小区间**）。因此，每次操作我们**只用考虑一个实际线段。**

对于一段区间中最长的“两端黑线段”，我们在添加这个线段后把其能覆盖的所有白色点全部变成黑色一定是最优的，不用受其他操作影响。这就指向了区间修改，我们也就可以考虑从**线段树**的角度入手这道题。

## 实现

首先来考虑区间维护。首先，整个数轴的范围是 $10^9$ 级别的，肯定不行。而对我们有用的整数点在 $5\times 10^5$ 级别内，因此我们线段树只维护这些整数点就可以。

询问的问题是所有整点有没有白色，因此查询线段树就查询线段里有没有白色就好。直接按题目输入定义。形象化一点，就像在大线段上下雪，一次“两端黑线段”操作就在对应的区间覆盖一层雪，初始时黑点下一层雪，白点没有。因此之后我们查找厚度即可，一层没有就是白点。（感觉撒煤粉更合理 doge）

我们定义一段线段的最小值 $v$：
- $v ≤ 0$：存在白色。
- $v ≥ 1$：全部是黑色。

这样定义其实也很方便操作。我们只需要记录一段区间的最小值，一次“两端黑线段”操作只需要区间加 $1$ 就好。询问只用判断整个线段的最小值是不是 $0$ 即可。

还有一个问题，就是如何找到操作区间 $[l,r]$ 的最长“两端黑线段”？   
我们通过 C ++ 内置函数解决。

- 对于 $l$，我们要找到最靠近 $l$ 的黑点 $i$，则有 $p[i] ≥ l$ 且 $p[i]$ 最小。也就是找到第一个位置比 $l$ 大的点。用 ```lower_bound``` 解决。

- $r$ 同理。找到第一个小于等于的，用 ```upper_bound``` 找到严格大于的最小值后 $-1$ 就是小于等于了。

最后的时间复杂度是 $O(n\log n)$。

## 一些细节

1. 对于刚才那个问题，我们不能直接在 $p$ 数组上操作，因为**里面还有白色点位置**，所以我们要另外开一个数组（注意保证单调性）。

2. 我们需不需要考虑变成黑色点的白色点？
	
   其实不用。如下图：
   
   ![](https://cdn.luogu.com.cn/upload/image_hosting/u4n4esg8.png)
   
   如果选定区间能包括从白色变成黑色的点，那一定有：
   - 不包括“两端黑线段”端点。则整个区间在这条线段里，一定都是黑的，没有操作必要，不用管。
   - 包括“两端黑线段”端点，则这个由白变黑的点到端点之间也一定全是黑点，因此操作时考虑变化点和直接考虑原来的黑点的效果是等价的。（当时我没想明白，一度认为是紫题）
 

3. 如果我们在区间 $[l,r]$ 里找不到两个黑点怎么办？
   
   其实这种情况就是一定没有能力使区间中的白点变黑的，具体证明可以联想 2。所以直接忽略就好。
   
   **注意：一定要每次输出一次询问，不要一不合法就直接 ```continue;```。**
   
4. 操作 2 如何处理？
   
   把每个操作 1 记录下来，每次删除时只需要找出操作 1 时覆盖的“两端黑线段”，“铲一层雪”就可以，也就是该区间整体 $-1$。
   
# 代码

变量名见注释。

```cpp
#include <iostream>
#include <algorithm>
#include <cstring>

#define ls (id << 1)
#define rs (id << 1 | 1)
#define mid ((l + r) >> 1)

using namespace std;
typedef pair<int, int> pii;
const int maxn = 500005;

int a[maxn], p[maxn];
int blk[maxn], len;//只记录黑点位置（black）
int id[maxn];//记录黑点编号对应原数轴的编号
int n, q;
pii opts[maxn]; //记录所有操作 1
struct SegmentTree{
	int mn;//区间最小值。用于找白点。
	int lazy;
}tr[maxn << 2];

void pushup(int id){
	tr[id].mn = min(tr[ls].mn, tr[rs].mn);
}

void build(int id, int l, int r){
	if (l == r){
		tr[id].mn = a[l];
		return;
	}
	build(ls, l, mid),
	build(rs, mid+1, r);
	pushup(id);
}

void pushdown(int id){
	if (tr[id].lazy){
		tr[ls].lazy += tr[id].lazy;
		tr[rs].lazy += tr[id].lazy;
		tr[ls].mn += tr[id].lazy;
		tr[rs].mn += tr[id].lazy;
		tr[id].lazy = 0;
	}
}

void update(int id, int l, int r, int a, int b, int v){
	if (a <= l && r <= b){
		tr[id].mn += v;
		tr[id].lazy += v;
		return;
	}
	pushdown(id);
	if (a <= mid) update(ls, l, mid, a, b, v);
	if (b > mid) update(rs, mid+1, r, a, b, v);
	pushup(id);
}

int query(int id, int l, int r, int a, int b){
	if (a <= l && r <= b){
		return tr[id].mn;
	}
	pushdown(id);
	int res = 1e9;
	if (a <= mid) res = min(res, query(ls, l, mid, a, b));
	if (b > mid) res = min(res, query(rs, mid+1, r, a, b));
	return res;
}

int findL(int x){//找最左的黑点
	return id[lower_bound(blk+1, blk+1+len, x)-blk];
}

int findR(int x){//找最右的黑点
	return id[upper_bound(blk+1, blk+1+len, x)-blk-1];
}

void check(){//每次的询问
	if (query(1, 1, n, 1, n) <= 0) cout << "No" << endl;
	else cout << "Yes" << endl;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

	cin >> n >> q;
	for (int i = 1; i <= n; i ++){
		cin >> p[i];
	}
	for (int i = 1; i <= n; i ++){
		cin >> a[i];
		if (a[i]){
			blk[++len] = p[i];
			id[len] = i;
		}
	}
	build(1, 1, n);

	for (int k = 1; k <= q; k ++){
        check();//注意！
		int op;
		cin >> op;
		if (op & 1){//1
			int L, R;
			cin >> L >> R;
			int l = findL(L), r = findR(R);
			if (l > r) continue;
			if (!l || !r) continue;
			update(1, 1, n, l, r, 1);
			opts[k] = make_pair(L, R);
		}
		else{//2
			int x;
			cin >> x;
			int l = findL(opts[x].first), r = findR(opts[x].second);
			if (l > r) continue;
			if (!l || !r) continue;
			update(1, 1, n, l, r, -1);
		}
	}
    check();//注意！

	return 0;
}
```

# 总结

以前错误的觉得想要提升就要练蓝紫题，本来这场 Div.3 都懒得参加，但是后来参加了才发现自己甚至还有许多基础没搞明白，所谓地基要牢固，多补习基础知识才是正道。

这道题中线段树的用法很经典，就是区间覆盖解决一些问题，推荐几个题目[P8463 「REOI-1」深潜的第六兽](https://www.luogu.com.cn/problem/P8463)、[P1442 铁球落地](https://www.luogu.com.cn/problem/P1442)。

谢谢观看！


---

## 作者：chen_zhe (赞：11)

# 破碎的历史

首先，我们会发现非特殊点都是没有意义的。

如果最左侧或最右侧的特殊点不是黑点，那么必然不存在方案，因为这个情况下必然存在最左侧或者最右侧的点无法被染黑。即只有当最左侧和最右侧的特殊点都是黑色点才可能有解。

对于一簇被加入到线段集合 $S$ 的线段，其中实际有用的线段是其中的两端点为黑色点的线段。将所有的这些线段取并集，则可知加入一簇线段 $[l,r]$，等价于加入其中长度最长的黑色点对区间 $[l',r']$。

那么什么时候无法满足存在至少一种合法染色方式使得正半轴上的所有特殊整点均被染黑呢？只要存在白色的特殊点没有被一个 $[l',r']$ 覆盖，则无法找到一种方案。（如果存在一个 $[l',r']$ 覆盖了白色点，就可以选择这个 $[l',r']$ 将其区间染黑，如果所有的白色点都存在一个 $[l',r']$ 将其覆盖，则所有的白色点都能被染黑。）

这样，我们可以将每次 $1$ 操作抽象为对 $[l',r']$ 这个区间中 $+1$，撤回操作就是对 $[l',r']$ 这个区间 $-1$，而最后要查询的是所有白色点的最小值，这个可以将黑色点预处理为一个大值后查询全局最小值代替。使用一棵线段树即可维护。而至于找到长度最长的黑色点对，可以直接使用二分查询，验题人小波写了倍增但是时间复杂度相同。

时间复杂度 $O(n \log n)$。

```cpp
#include <iostream>
#include <algorithm>
using namespace std;
int n,q,pos[500050],col[500050],cnt,L[500050],R[500050];
struct point
{
    int pos,id;
    bool operator < (const point &rhs) const
    {
        return pos<rhs.pos;
    }
}pt[500050];
struct SegTree
{
    int l,r,val,tag;
}t[2000050];
inline void Push_Up(int id)
{
    t[id].val=min(t[id<<1].val,t[id<<1|1].val);
}
inline void Push_Down(int id)
{
    if (t[id].tag)
    {
        t[id<<1].val+=t[id].tag;
        t[id<<1|1].val+=t[id].tag;
        t[id<<1].tag+=t[id].tag;
        t[id<<1|1].tag+=t[id].tag;
        t[id].tag=0;
    }
}
inline void Build(int id,int l,int r)
{
    t[id].l=l;
    t[id].r=r;
    if (l==r)
    {
        t[id].val=(col[l]?1<<30:0);
        return;
    }
    int mid=(l+r)>>1;
    Build(id<<1,l,mid);
    Build(id<<1|1,mid+1,r);
    Push_Up(id);
}
inline void Change(int id,int l,int r,int val)
{
    if (l<=t[id].l && t[id].r<=r)
    {
        t[id].tag+=val;
        t[id].val+=val;
        return;
    }
    Push_Down(id);
    int mid=(t[id].l+t[id].r)>>1;
    if (r<=mid)
        Change(id<<1,l,r,val);
    else if (l>mid)
        Change(id<<1|1,l,r,val);
    else
    {
        Change(id<<1,l,mid,val);
        Change(id<<1|1,mid+1,r,val);
    }
    Push_Up(id);
}
inline int Query()
{
    return t[1].val;
}
int main()
{
    cin >> n >> q;
    for (int i=1;i<=n;i++)
        cin >> pos[i];
    pt[0]=(point){-1<<30,0};
    for (int i=1;i<=n;i++)
    {
        cin >> col[i];
        if (col[i]==1)
            pt[++cnt]=(point){pos[i],i};
    }
    pt[cnt+1]=(point){1<<30,n+1};
    col[0]=col[n+1]=true;
    Build(1,0,n+1);
    puts(Query()>=1?"YES":"NO");
    for (int i=1;i<=q;i++)
    {
        int op;
        cin >> op;
        if (op==1)
        {
            cin >> L[i] >> R[i];
            int x=lower_bound(pt,pt+cnt+2,(point){L[i],0})-pt;
            int y=upper_bound(pt,pt+cnt+2,(point){R[i],0})-pt-1;
            x=pt[x].id,y=pt[y].id;
            if (x<=y)
                Change(1,x,y,1);
        }
        else
        {
            int id;
            cin >> id;
            int x=lower_bound(pt,pt+cnt+2,(point){L[id],0})-pt;
            int y=upper_bound(pt,pt+cnt+2,(point){R[id],0})-pt-1;
            x=pt[x].id,y=pt[y].id;
            if (x<=y)
                Change(1,x,y,-1);
        }
        puts(Query()>=1?"YES":"NO");
    }
    return 0;
}
```

---

## 作者：Micnation_AFO (赞：5)

## $\texttt{Description}$

给定数轴上若干个非黑即白的特殊点，询问初始时以及每次操作后是否可以将整个线段染黑。给定一些线段，若线段的左右断点都是黑色点即可将数轴上这一段染黑（初始时没有任何线段）。要求支持两个操作：

- 对于 $l \le x \le y \le r$，若 $x$ 和 $y$ 都是白点或黑点，则添加一条以 $x$ 和 $y$ 为端点的线段。
- 撤去第 $x$ 加入的所有线段。

## $\texttt{Solution}$

首先，普通点在题目中没有任何作用，因此可以把普通点全部忽视，那么只剩下了白点和黑点。同时，第一个操作对于端点为白色的时候也没有用，因为无法将这条线段染黑。

在当前阶段，若点 $x$ 可以被染黑，那么就令 $t_x$ 上加 $1$，否则为 $0$。若对于任意整数 $1 \le i \le n$ ，都有 $t_x > 0$，则输出 `Yes`，否则输出 `No`。

然后我们可以发现，对于第一个操作，虽然看上去加入了很多条线段，其实真正有用的只有一条。若 $x$ 为大于等于 $l$ 的最小整数，$y$ 为小于等于 $r$ 的最大整数，且 $x$ 和 $y$ 都是黑点，则以 $x$ 和 $y$ 为断点的这条线段是唯一有用的。因为同一操作中，能染黑数轴的线段，一定被这条线段包含了。其中，$x'$ 和 $y'$ 可以二分查询。

对于撤销操作，同样，撤销掉第 $x$ 次操作最有用的线段即可。

然后这个东西非常可以用线段树维护，线段树维护所有的特殊点，若加入一条以 $x$ 和 $y$ 为端点的线段，则令 $x'$ 和 $y'$ 分别为 $x$ 和 $y$ 在所有特殊点的位置（第几个），然后在区间 $[x', y']$ 加上 $1$，同时记录 $x'$ 和 $y'$。撤销操作时，在区间 $[x', y']$ 减去 $1$ 即可。每次操作结束后，查询所有区间的最小值，若大于 $0$，则说明所有的点都可以被涂成黑色，反之不行。

不要忘记初始化，若开始的时候是黑色节点，赋值为非 $0$。

$color_i$ 表示第 $i$ 个特殊节点是否为黑色，$points_i$ 记录了第 $i$ 个黑色节点在数轴中的位置以及这是第几个黑色节点。

```cpp
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 6e5;
const int INF = 1e9 + 10;

int n, q;
int cnt = 0;
int a[N], color[N];
int L[N], R[N];

struct coord {
    int num;//num 存储的是在数轴中的位置
    int id;//id 存储的是这个黑点是从左到右的第几个黑点
    bool operator < (const coord &x) const {
        return num < x.num;
    }//重载小于号，为了后面的二分
} points[N];

struct SegmentTree {
    int l, r;
    int dat, add;
} t[N * 4];

void push_up(SegmentTree &fa, SegmentTree ls, SegmentTree rs) {
    fa.dat = min(ls.dat, rs.dat);
} 

void build(int p, int l, int r) {
    t[p].l = l, t[p].r = r;
    if (l == r) { t[p].dat = (color[l] ? INF : 0); return; }
    int mid = (t[p].l + t[p].r) >> 1;
    build(p << 1, l, mid), build((p << 1) | 1, mid + 1, r);
    push_up(t[p], t[p << 1], t[(p << 1) | 1]);
}

void spread(int p) {
    if (t[p].add) {
        t[p << 1].dat += t[p].add;
        t[(p << 1) | 1].dat += t[p].add;
        t[p << 1].add += t[p].add, t[(p << 1) | 1].add += t[p].add;
        t[p].add = 0;
    }
}

void change(int p, int l, int r, int v) {
    if (l <= t[p].l && r >= t[p].r) {
        t[p].dat += v;
        t[p].add += v;
        return;
    }
    spread(p);
    int mid = (t[p].l + t[p].r) >> 1;
    if (l <= mid) change(p << 1, l, r, v);
    if (r > mid) change((p << 1) | 1, l, r, v);
    push_up(t[p], t[p << 1], t[(p << 1) | 1]);
}

int ask() {
    return t[1].dat;
}

int main() {
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    for (int i = 1; i <= n; i++) {
        scanf("%d", color + i);
        if (color[i]) points[++cnt] = (coord){a[i], i};
    }
    build(1, 1, n);
    if (ask()) printf("Yes\n");
    else printf("No\n");
    for (int i = 1; i <= q; i++) {
        int op;
        cin >> op;
        if (op == 1) {
            cin >> L[i] >> R[i];
            int x = lower_bound(points + 1, points + 1 + cnt, (coord){L[i], 1}) - points;//找到第一个大于等于 l 的黑点在 color 中的下标
            int y = upper_bound(points + 1, points + 1 + cnt, (coord){R[i], 1}) - points - 1;//找到第一个大于大于 r 的黑点的前面一个，即第一个小于等于 y 的黑点在 color 的下标
            x = points[x].id, y = points[y].id;//赋值为第几个特殊点，即线段树中的下标
            L[i] = x, R[i] = y;//记录 x', y'，便于撤销操作
            if (x != -1 && y != -1 && x <= y) change(1, x, y, 1);
        }
        else {  
            int id; cin >> id;
            int x = L[id], y = R[id];
            if (x != -1 && y != -1 && x <= y) change(1, x, y, -1);
        }
        if (ask()) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}

```





---

