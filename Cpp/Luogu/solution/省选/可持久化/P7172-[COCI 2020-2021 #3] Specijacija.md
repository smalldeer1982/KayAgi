# [COCI 2020/2021 #3] Specijacija

## 题目描述

给定一个正整数 $n$ 个一个满足 $\frac{i(i-1)}{2} \lt a_i \le \frac{i(i+1)}{2}$ 的正整数序列 $a_1, a_2, \cdots, a_n$。

该序列是一棵包含 $\frac{(n+1)(n+2)}{2}$ 个节点的树参数化而来的，它包括 $n+1$ 层，每层分别包括 $1, 2, \cdots, n+1$ 个节点，如图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/bvug13ny.png)

它由 $a=(1,2,6)$ 参数化而来。

第 $i$ 层包含节点 $\frac{i(i-1)}{2}+1, \cdots, \frac{i(i+1)}{2}$。节点 $a_i$ 有两个孩子，而其他同层的节点都只有一个孩子。

请回答 $q$ 个询问，求 $x,y$ 的最大公共祖先，即既是 $x$ 的祖先，又是 $y$ 的祖先且权值最大的节点。

## 说明/提示

**【样例解释 #1 / #2】**

两个样例所表示的树的形状在题目描述的图中已经呈现。

第二个样例中各个节点的权值：

$x_1=7$，$y_1=10$；  
$x_2=9$，$y_2=6$；  
$x_3=2$，$y_3=8$；  
$x_4=1$，$y_4=2$；  
$x_5=3$，$y_5=4$。

**【数据范围】**

| Subtask | 分值 | 数据范围及约定 |
| :----------: | :----------: | :----------: |
| $1$ | $10$ | $q=1, t=0$ |
| $2$ | $10$ | $n \le 1000, t=0$ |
| $3$ | $30$ | $t=0$ |
| $4$ | $60$ | $t=1$ |

对于 $100\%$ 的数据，$1 \le n,q \le 2 \times 10^5$，$t \in \{0,1\}$。

**【说明】**

**本题分值按 COCI 原题设置，满分 $110$。**

**题目译自 [COCI2020-2021](https://hsin.hr/coci/) [CONTEST #4](https://hsin.hr/coci/archive/2020_2021/contest3_tasks.pdf)  _T5 Specijacija_。**

## 样例 #1

### 输入

```
3 5 0
1 2 6
7 10
8 5
6 2
9 10
2 3```

### 输出

```
1
5
1
6
1```

## 样例 #2

### 输入

```
3 5 1
1 2 6
7 10
8 5
6 2
9 10
2 3```

### 输出

```
1
6
2
1
1```

# 题解

## 作者：tommymio (赞：10)

$\text{Subtask 1}$ 可以直接构造树。$\text{Subtask 2}$ 可以直接向上跳。这两个 $\text{Subtask}$ 都非常简单，似乎并没有什么指导意义（

我们注意到这题有一个重要性质：第 $i$ 层只有一个节点具有两个儿子，也就是说，树的形态中会包含很多长链。如下图，被红色圆圈圈出的是一些长链：

![](https://cdn.luogu.com.cn/upload/image_hosting/nanucxp3.png)

如果我们将这些长链缩成点，并保留连通性，得到一棵新树，会怎么样呢？我们惊奇的发现新树的点数为 $O(n)$。证明如下，假设每个叶子节点都是一条长链，那么初始有 $n+1$ 条长链。每个具有两个儿子的点都会使得长链个数 $+1$。故长链个数不超过 $2n+1$，即长链个数是 $O(n)$ 级别的。

假设我们已经建出了这棵新树，那么我们就可以直接在新树上查询 $\text{lca}$ ，从而得到原树上 $x,y$ 的 $\text{lca}$ 所在的长链的编号。现在需要解决两个问题：如何建出新树以及如何查询任意一个点所在的长链编号。

显然有一个性质，新树上的边只会是那些 $a_i$ 与其儿子相连的边。可以想到，自底向下考虑每个 $a_i$。这样的话，从第 $i$ 层到第 $i-1$ 层，某个 $a_i$ 具有两个儿子对第 $i-1$ 层节点的影响，可以看作第 $i$ 层的节点删去右节点得到。而如果从第 $i-1$ 层到第 $i$ 层，则 $a_{i-1}+i$ 之后的点都向后移了一位。

像这种动态删除，并查询实际第 $k$ 个位置，可以使用线段树实现，对每层开一个线段树，叶子上保存当前节点所在的长链编号。并且发现每层除了与 $a_i$ 相关的点，其他点信息都没有改变，所以可以使用可持久化线段树不至于 $\text{MLE}$。建树的时候随便记录一下原树上当前长链深度最大的节点，就可以在查询到 $\text{lca}$ 所在长链编号后直接得到 $\text{lca}$ 了。

$\color{green}\text{tommy}$ 一遍就过了，诶，非常开心~

```cpp
#include<cstdio>
#include<cmath>
#include<functional>
typedef long long ll;
int n,cnt=0,tot=0;
int rt[400015];
struct node {int id,size,lson,rson;} t[20000005];
ll a[200005],minn[400015];
int skip[400015][25],dep[400015];
int h[400015],to[800035],ver[800035];
inline ll read() {
	ll x=0,f=1;register char s=getchar();
	while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();}
	while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
	return x*f;
}
inline void swap(int &x,int &y) {int tmp=x;x=y;y=tmp;}
inline ll min(const ll &x,const ll &y) {return x<y? x:y;}
inline void add(int x,int y) {to[++cnt]=y;ver[cnt]=h[x];h[x]=cnt;}
inline void assign(int x,int y) {
	t[x].size=t[y].size; t[x].id=t[y].id;
	t[x].lson=t[y].lson; t[x].rson=t[y].rson;
}
inline void change(int &p,int lst,int l,int r,int x,int val) {
	p=++tot; assign(p,lst);
	if(l==r) {t[p].size=(val>0); t[p].id=val; return;}
	int mid=l+r>>1; 
	if(x<=mid) change(t[p].lson,t[lst].lson,l,mid,x,val);
	else change(t[p].rson,t[lst].rson,mid+1,r,x,val);
	t[p].size=t[t[p].lson].size+t[t[p].rson].size;
}
inline std::pair<int,int> ask(int p,int l,int r,int rk) {
	if(l==r) return std::make_pair(l,t[p].id);
	int mid=l+r>>1;
	if(t[t[p].lson].size>=rk) return ask(t[p].lson,l,mid,rk);
	return ask(t[p].rson,mid+1,r,rk-t[t[p].lson].size);
}
inline void prework(int x) {
	for(register int i=1;i<=20;++i) skip[x][i]=skip[skip[x][i-1]][i-1]; 
	for(register int i=h[x];i;i=ver[i]) {int y=to[i]; skip[y][0]=x; dep[y]=dep[x]+1; prework(y);}
}
inline int LCA(int x,int y) {
	if(dep[x]>dep[y]) swap(x,y); //dep[x]<=dep[y]
	for(register int i=20;i>=0;--i) {if(dep[x]<=dep[skip[y][i]]) y=skip[y][i];}
	if(x==y) return x;
	for(register int i=20;i>=0;--i) {if(skip[x][i]!=skip[y][i]) x=skip[x][i],y=skip[y][i];}
	return skip[x][0];
}
inline ll solve(ll x,ll y) {
	ll levX=sqrt(2ll*x),levY=sqrt(2ll*y);
	if(levX*1ll*(levX+1)/2<x) ++levX;
	if(levY*1ll*(levY+1)/2<y) ++levY;
	int lca=LCA(ask(rt[levX],1,n+1,x-levX*1ll*(levX-1)/2).second,ask(rt[levY],1,n+1,y-levY*1ll*(levY-1)/2).second);
	return min(minn[lca],min(x,y));
}
int main() {
	n=read(); int Q=read(),type=read();
	for(register int i=1;i<=n;++i) a[i]=read();
	for(register int i=1;i<=n+1;++i) {
		minn[i]=n*1ll*(n+1)/2+i;
		change(rt[n+1],rt[n+1],1,n+1,i,i);
	}
	int num=n+1;
	for(register int i=n;i;--i) {
		int ind=a[i]-i*1ll*(i-1)/2;
		std::pair<int,int> tmp1=ask(rt[i+1],1,n+1,ind);
		std::pair<int,int> tmp2=ask(rt[i+1],1,n+1,ind+1);
		minn[++num]=a[i]; add(num,tmp1.second); add(num,tmp2.second);
		change(rt[i],rt[i+1],1,n+1,tmp1.first,num);
		change(rt[i],rt[i],1,n+1,tmp2.first,0);
	}
	dep[num]=1; prework(num);
	ll ans=0; 
	while(Q--) {
		ll x=read(),y=read();
		x=(x-1+type*ans)%((n+1)*1ll*(n+2)/2)+1;
		y=(y-1+type*ans)%((n+1)*1ll*(n+2)/2)+1;
		printf("%lld\n",ans=solve(x,y)); 
	}
	return 0;
}
```

---

## 作者：jijidawang (赞：3)

首先令 $a_i\gets a_i-\frac{i(i-1)}2$，也就是把它改成在第 $i$ 层的排名。

考虑到如果 $u$ 在第 $x+1$ 层排在第 $d$ 个位置，那么它的父亲在第 $x$ 层的排名：
$$f_x(u)=\begin{cases}u&u\le a_x\\u-1&u>a_x\end{cases}$$
这是一个两段的分段函数。那么如果要求一个点跳若干步到达的点就是一个区间函数复合，此处分段函数的段数线性于区间长度，于是可以直接线段树大力维护（[对数据结构的爱](https://www.luogu.com.cn/problem/P5609)）。

那么求 LCA 的话就先跳到同一深度，然后线段树上二分找到两个点同时跳若干步后两个点重合的第一个位置即可。

时间复杂度 $O((n+q)\log n)$。

---

## 作者：摸鱼酱 (赞：3)

大致题意：一棵 $n+1$ 层的树，第 $i$ 层有 $i$ 个结点，树从上往下，从左往右依次从 $1$ 开始编号，第 $i$ 层的结点 $a_i$ 会有两个儿子，同层其它点只有一个儿子，儿子从下一层的最左结点开始依次分配，$q$ 次询问两个点的最近公共祖先，**强制在线**。

$1\leq n,q\leq 2\times 10^5$。

首先考虑这棵树里会有很多的直链，即这条链上的点除了链尾都只有一个儿子。如果我们用链尾结点代替这条直链，保留连通性建树，那么树的点数为最后一层的 $n+1$ 个点以及向上 $n$ 层每层新增的一个点，即 $2n+1=O(n)$。

思考这棵树的性质，我们发现询问的答案要么是其中一个点，要么是一个链尾，所以我们如果实际建出了这棵树，并能查询每个点对应的直链编号，那么就可以方便地回答询问。

考虑一个朴素的过程，对于每一层点分别维护它们对应的直链编号，观察自底向上维护的时候的更新可以发现，从第 $i+1$ 层到第 $i$ 层，只有第 $i$ 层的特殊结点和它后面的一个位置的编号合并成了一个新的编号，即只有 **单点删除，查询第 $k$ 个没被删除的元素，单点修改** 三种操作，这个过程可以用经典的主席树来解决。

于是这题就做完了，时间复杂度 $O(n\log n+q\log n)$。

[代码](https://www.luogu.com.cn/paste/g6gk92b6) 不到 100 行，不到 3kb，极其好写。

---

## 作者：Larunatrecy (赞：1)

提供一个分块的做法。

考虑把每一个点表示成 $(level,number)$，$level$ 表示这个点所在的层数，$ number$ 表示这个点是这一层的第几个点。

同理可以把 $a$ 数组，和询问的 $x,y$ 都表示成这种形式。

考虑如果点 $x$ 移动到 $x$ 的父亲，那么 $level$ 肯定减一，而只有 $a_{i}<number$ 时，$number$ 会减一，否则不会变。也就是说:

```cpp
number-=(a[i]<number).
```
考虑对 $a$ 序列分块，设 $trans_{x,v}$ 表示第 $x$ 个块，进入这个块之前$number$ 为 $v$，统计过这个块之后，$number$ 是多少。

那么借助 $trans$ 数组，我们就可以仿照求 lca 的过程，如果能跳过一个块，就跳过一个块，否则就一层一层跳，显然可以在 $O(q\sqrt n)$。的时间内求出 lca 。

于是只需求出 $trans$ 数组就行了。

考虑增量计算，由 $trans_{x,v}$ 得到 $trans_{x,v+1}$。

设使得 $number$ 减少的位置为关键点，那么一个性质就是说增量的时候要么新增一个关键点，要么保持不变，原来就是关键点的现在一定还是关键点。

考虑怎么求出新增加的关键点，考虑设 $pre_i$ 表示 $i$ 之前选的关键点个数。

那么一个位置可以成为关键点，当且仅当 $a_i<v+1-pre_i$ 。

那么新增加的就是最靠右的一个符合这个条件的位置。

这个条件也就是：

$a_i+pre_i<v+1$

用一个线段树维护 $a_i+pre_i$

那么显然只需要支持区间加就可以了，查询的时候只需要判断最靠前的一个位置的值是否小于 $v+1$ 就行了。

复杂度是 $O(n\sqrt n \log n)$

考虑优化一下，因为最多就只会把这个块全选完，因此变化量是 $O(\sqrt n)$ 的，这意味着有大量的位置的 $trans$ 是相等的，可以之间跳过去。

复杂度 $O(n\sqrt n+n\log n)$

不过因为常数比较大，实测设块长为 $1700$ 比较优秀。

不过本人实现不好，必须开 O2 才能通过。

```cpp
const int BL = 220;
int tr[BL][N];
int dec[N];
int bel[N], L[N], R[N];
int B;
LL tot[N];
int Min[N * 4], tag[N * 4], Pos[N * 4];
void pushup(int k) {
    Min[k] = Min[k << 1 | 1];
    Pos[k] = Pos[k << 1 | 1];
    if (Min[k << 1] < Min[k << 1 | 1])
        Min[k] = Min[k << 1], Pos[k] = Pos[k << 1];
}
void Build(int k, int l, int r) {
    tag[k] = 0;
    if (l == r) {
        Min[k] = dec[l];
        Pos[k] = l;
        return;
    }
    int mid = (l + r) >> 1;
    Build(k << 1, l, mid);
    Build(k << 1 | 1, mid + 1, r);
    pushup(k);
}
void Push(int k, int v) {
    tag[k] += v;
    Min[k] += v;
}
void pushdown(int k) {
    if (tag[k]) {
        Push(k << 1, tag[k]);
        Push(k << 1 | 1, tag[k]);
        tag[k] = 0;
    }
}
void Addate(int k, int l, int r, int L, int R) {
    if (L <= l && r <= R) {
        Push(k, 1);
        return;
    }
    pushdown(k);
    int mid = (l + r) >> 1;
    if (L <= mid)
        Addate(k << 1, l, mid, L, R);
    if (R > mid)
        Addate(k << 1 | 1, mid + 1, r, L, R);
    pushup(k);
}
void Ban(int k, int l, int r, int x) {
    if (l == r) {
        Min[k] = 1e9;
        return;
    }
    pushdown(k);
    int mid = (l + r) >> 1;
    if (x <= mid)
        Ban(k << 1, l, mid, x);
    else
        Ban(k << 1 | 1, mid + 1, r, x);
    pushup(k);
}
void rebuild(int x) {
    Build(1, L[x], R[x]);
    int len = 0;
    for (int i = 1; i <= n + 1; i++) {
        int o = Min[1];
        if (o >= 1e9) {
            for (; i <= n + 1; i++) tr[x][i] = i - len;
            break;
        }
        for (int j = i; j <= o; j++) tr[x][j] = j - len;
        len++;
        tr[x][o + 1] = o + 1 - len;
        int p = Pos[1];
        Ban(1, L[x], R[x], p);
        Addate(1, L[x], R[x], L[x], p);
        i = o + 1;
    }
}
int pos(LL x) {
    int l = 0, r = n, mid, ans;
    while (l <= r) {
        mid = (l + r) >> 1;
        if (tot[mid] < x)
            ans = mid, l = mid + 1;
        else
            r = mid - 1;
    }
    return ans + 1;
}
inline int reduce(int x, int l, int r) {
    for (int i = r - 1; i >= l; i--) x -= (dec[i] < x);
    return x;
}
int LittleFools(int i, int x) { return reduce(x, L[bel[i]], i); }
LL LittleFind(int i, int x, int y) {
    for (i--; x != y && i >= 1; i--) {
        x -= (dec[i] < x);
        y -= (dec[i] < y);
    }
    return tot[i] + x;
}
inline LL LCA(int i, int x, int j, int y) {
    while (abs(bel[i] - bel[j]) > 1) {
        if (bel[i] < bel[j])
            swap(i, j), swap(x, y);
        if (i != L[bel[i]])
            x = LittleFools(i, x), i = L[bel[i]];
        i = L[bel[i] - 1], x = tr[bel[i]][x];
    }
    if (i < j)
        swap(i, j), swap(x, y);
    x = reduce(x, j, i);
    i = j;
    int fi = LittleFools(i, x), fj = LittleFools(j, y);
    bool fl = 0;
    while (fi != fj) {
        if (!fl)
            i = L[bel[i]], j = i;
        else
            i = L[bel[i] - 1], j = i;
        x = fi;
        y = fj;
        fl = 1;
        fi = tr[bel[i] - 1][x];
        fj = tr[bel[j] - 1][y];
    }
    return LittleFind(i, x, y);
}
void solve() {
    B = 1700;
    for (int i = 1; i <= n; i++) {
        dec[i] = a[i] - tot[i - 1];
        tot[i] = tot[i - 1] + i;
    }
    for (int i = 1; i <= n; i++) {
        bel[i] = (i - 1) / B + 1;
        if (!L[bel[i]])
            L[bel[i]] = i;
        R[bel[i]] = i;
    }
    int cnt = bel[n];
    bel[n + 1] = cnt + 1;
    L[bel[n + 1]] = n + 1;
    for (int i = 1; i <= cnt; i++) rebuild(i);
    LL sum = 1ll * (n + 1) * (n + 2) / 2;
    LL ans = 0;
    while (m--) {
        LL x, y;
        read(x);
        read(y);
        x = (x - 1 + 1ll * tp * ans) % sum + 1;
        y = (y - 1 + 1ll * tp * ans) % sum + 1;
        int i = pos(x), u = x - tot[i - 1];
        int j = pos(y), v = y - tot[j - 1];
        ans = LCA(i, u, j, v);
        printf("%lld\n", ans);
    }
}
```

---

## 作者：LittleYang0531 (赞：1)

### 题目描述:

给定一个长度为 $n$ 的正整数序列 $a_1,a_1,...,a_n$。其中 $\frac{i(i-1)}{2}<a_i\leq \frac{i(i+1)}{2}$ 。 

这个序列会生成一个包含 $\frac{(n+1)(n+2)}{2}$ 个节点的树。树高为 $n+1$。

树的第 $i$ 层包含了节点 $\frac{i(i-1)}{2}+1,...,\frac{i(i+1)}{2}$ 。在这一层中，只有节点 $a_i$ 由两个孩子，其他的节点都只有一个孩子。

你的问题是回答 $q$ 个询问，每一个询问会询问你节点 $x,y$ 的最近公共祖先。

### 输入描述:

输入的第一行包括三个正整数 $n,q,t(1\leq n,q\leq 2\times 10^5,t\in {0,1})$。分别表示生成树的序列的长度，查询的数目以及是否强制在线。 

输入的第二行是一个长度为 $n$ 的数组 $a_i(\frac{i(i-1)}{2}<a_i\frac{i(i+1)}{2})$。这就是生成树的数组。接下来的 $n$ 行，每行两个正整数 $\tilde{x},\tilde{y}(1\leq \tilde{x_i},\tilde{y_i}\leq \frac{i(i+1)}{2})$。这两个数会决定最终询问的 $x,y$。 我们令 $z_i$ 表示第 $i$ 个询问操作的答案，并令 $z_0=0$。$x_i$ 和 $y_i$ 可以用如下方法求出:

$x_i=((\tilde{x_i}-1+t\times z_{i-1})\ mod\ \frac{(n+1)
(n+2)}{2})+1$

$y_i=((\tilde{y_i}-1+t\times z_{i-1})\ mod\ \frac{(n+1)(n+2)}{2})+1$

$mod$ 表示整数取模运算。需要注意的是，如果 $t=0$，那么就有 $x_i=\tilde{x_i}$ 而 $y_i=\tilde{y_i}$。

### 输出描述:

输出 $q$ 行，每行一个正整数，即 $x,y$ 的最近公共祖先的编号。

### 分析:

#### 20Pts:

直接建出一棵树然后跑个 LCA 就行了。

时间复杂度为 $O(q\log_2n)$，但 $n\leq 1000$。

#### 100Pts:

注意：此方法惨遭卡常，在运气好的情况下可以拿到满分，否则视情况随机TLE。这玩意确实有几率通过，不信看我提交记录。

由于需要支持在线查询，且 $n\leq 2\times 10^5$，直接建树空间一定会炸，考虑使用可持久化线段树来建树。

我们需要建两颗主席树，一颗用来维护建到当前深度时还有哪些点没有被使用过，一颗用来维护应该接在哪一个节点上。

每一次输入一个 $a[i]$ 时，计算 $a[i]$ 所在的行 $x$ 与列 $y$，在第一颗主席树中二分查询第 $y$ 个没有被使用的点 $k$，将这个点加入我们新建的一个节点 $node[cnt]$ 中。并将其与第二颗主席树上第 $k$ 与 $k+1$ 个点连边，将第一颗主席树的第 $k+1$ 个节点赋值为 0。

接着在节点数组 $node$ 上跑一遍正常的 DFS，计算出其树状结构下的深度与它上升 $2^0$ 的深度后的节点，再通过递推计算出某一个节点上升 $2^z$ 的深度后的节点。

接下来的查询操作，先将两个数 $x$ 与 $y$ 解密出来，计算出 $x$ 与 $y$ 所在的行 $f_x,f_y$ 与列 $g_x,g_y$，再在第二颗主席树中查询当其建树深度为 $f_x,f_y$ 时对应的节点 $x',y'$。并从这个节点开始在所有 $node$ 节点所构成的树上进行正常的 LCA。若发现这两个在同一条链上，则直接输出行数较低的那一个，否则输出 $x',y'$ 的最近公共祖先的真实编号。

时间复杂度为 $O(n\log_2^2n)$。

### 代码:

```C++
#include<bits/stdc++.h>
#define van long long
using namespace std;
const van k=21,N=4e5+5;
struct node {
	van ls,rs;
	van num;
};
van up[N][k],n,a[N],RealNum[N<<2],cnt;
van root[N],cnt2,root2[N],cnt3;
node tree[N<<5],tree2[N<<5];
vector<van> g[N];van deep[N],q,t;
van Calc(van x) {
	return x*(x-1)/2;
}
pair<van,van> GetPos(van num) {
	van l=1,r=n+1,ans;
	while (l<=r) {
		van mid=l+r>>1;
		if (Calc(mid)<num) ans=mid,l=mid+1;
		else r=mid-1;
	}
	return make_pair(ans,num-Calc(ans));
}//由某一个数获取到其所在的行与列
van BuildTree(van l,van r) {
	van now=++cnt2;
	if (l==r) {
		++cnt;RealNum[cnt]=Calc(n+1)+l;
		tree[now].num=cnt;
		return now;
	}
	van mid=l+r>>1;
	tree[now].ls=BuildTree(l,mid);
	tree[now].rs=BuildTree(mid+1,r);
	return now;
}//建立第一颗主席树(及上文所提到的第二颗主席树)
van ChangeTree(van p,van l,van r,van where,van num) {
	van now=++cnt2;
	tree[now]=tree[p];
	if (l==r) {
		++cnt;RealNum[cnt]=num;
		tree[now].num=cnt;
		return now;
	}
	van mid=l+r>>1;
	if (where<=mid) tree[now].ls=ChangeTree(tree[p].ls,l,mid,where,num);
	else tree[now].rs=ChangeTree(tree[p].rs,mid+1,r,where,num);
	return now;
}//单点修改主席树上某一节点的值
van QueryTree(van p,van l,van r,van num) {
	if (l==r) return tree[p].num;
	van mid=l+r>>1;
	if (num<=mid) return QueryTree(tree[p].ls,l,mid,num);
	else return QueryTree(tree[p].rs,mid+1,r,num);
}//单点查询主席树上某一节点的值
van BuildTree2(van l,van r) {
	van now=++cnt3;
	if (l==r) {
		tree2[now].num=1;
		return now;
	}
	van mid=l+r>>1;
	tree2[now].ls=BuildTree2(l,mid);
	tree2[now].rs=BuildTree2(mid+1,r);
	tree2[now].num=tree2[tree2[now].ls].num+tree2[tree2[now].rs].num;
	return now;
}//建立第二颗主席树(及上文所提到的第一颗主席树)
van ChangeTree2(van p,van l,van r,van where,van num) {
	van now=++cnt3;
	tree2[now]=tree2[p];
	if (l==r) {
		tree2[now].num=num;
		return now;
	}
	van mid=l+r>>1;
	if (where<=mid) tree2[now].ls=ChangeTree2(tree2[p].ls,l,mid,where,num);
	else tree2[now].rs=ChangeTree2(tree2[p].rs,mid+1,r,where,num);
	tree2[now].num=tree2[tree2[now].ls].num+tree2[tree2[now].rs].num;
	return now;
}//单点修改第二颗主席树的值
van QueryTree2(van p,van l,van r,van L,van R) {
	if (L<=l&&r<=R) {
		return tree2[p].num;
	}
	van mid=l+r>>1,sum=0;
	if (L<=mid) sum+=QueryTree2(tree2[p].ls,l,mid,L,R);
	if (R>mid) sum+=QueryTree2(tree2[p].rs,mid+1,r,L,R);
	return sum;
}//区间查询第二颗主席树上某一些节点的值的和
void AddLine(van father,van son) {
	g[father].push_back(son);
	g[son].push_back(father);
}//新建一条边
void initDFS(van now,van f) {
	for (int i=0;i<g[now].size();i++) {
		if (g[now][i]!=f) {
			deep[g[now][i]]=deep[now]+1;
			up[g[now][i]][0]=now;
			initDFS(g[now][i],now);
		}
	}
}//预处理节点深度与up[i][0]数组
void initLCA() {
	deep[cnt]=1;
	initDFS(cnt,0);
	for (int j=1;j<k;j++) {
		for (int i=1;i<=cnt;i++) {
			up[i][j]=up[up[i][j-1]][j-1];
		}
	}
}//递推处理up数组
van GetDeep(van num) {
	return GetPos(num).first;
}
van LCA(van a,van b,van a1,van b1) {
	if (deep[a1]<deep[b1]) swap(a1,b1),swap(a,b);
	for (int i=k-1;i>=0;i--) {
		if (deep[up[a1][i]]>=deep[b1]) {
			a1=up[a1][i];
		}
	}
	if (a1==b1) {
		return (GetDeep(a)<GetDeep(b)?a:b);
	}
	for (int i=k-1;i>=0;i--) {
        if (up[a1][i]!=up[b1][i]) {
			a1=up[a1][i],b1=up[b1][i];
		}
	}
	return RealNum[up[a1][0]];
} //正常的LCA(但直接返回最终结果)
inline van read() {
    van x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}//快读
inline void write(van x) {
    char F[200];
    van tmp=x>0?x:-x ;
    if(x<0)putchar('-') ;
    van cnt=0 ;
    while(tmp>0)
    {
    	F[cnt++]=tmp%10+'0';
        tmp/=10;
    }
    while(cnt>0)putchar(F[--cnt]) ;
    putchar('\n');
}//快输
int main() {
	n=read(),q=read(),t=read();
	for (int i=1;i<=n;i++) {
		a[i]=read();
	}
	root[n+1]=BuildTree(1,n+1);
	root2[n+1]=BuildTree2(1,n+1);//建树
	for (int i=n;i>=1;i--) {
		pair<van,van> pos=GetPos(a[i]);
		van l=1,r=n+1,tmp1,tmp2;
		while (l<=r) {
			van mid=l+r>>1;
			if (QueryTree2(root2[i+1],1,n+1,1,mid)>=pos.second) {
				tmp1=mid;r=mid-1;
			} 
			else l=mid+1;
		}//查找应该接在哪一列
		l=1,r=n+1;
		while (l<=r) {
			van mid=l+r>>1;
			if (QueryTree2(root2[i+1],1,n+1,1,mid)>=pos.second+1) {
				tmp2=mid,r=mid-1;
			}
			else l=mid+1;
		}//查找下一个有值的列
		van son1=QueryTree(root[i+1],1,n+1,tmp1),
			son2=QueryTree(root[i+1],1,n+1,tmp2);
		root[i]=ChangeTree(root[i+1],1,n+1,tmp1,a[i]);
		van now=QueryTree(root[i],1,n+1,tmp1);
		AddLine(now,son1);AddLine(now,son2);//建边
		root2[i]=ChangeTree2(root2[i+1],1,n+1,tmp1,1);
		root2[i]=ChangeTree2(root2[i],1,n+1,tmp2,0);//修改第二颗主席树某一节点的边权
	} 
	initLCA();
	van z=0;
	while (q--) {
		van x,y;
		x=read(),y=read();
		if (t) {
			x=(x-1+t*z)%Calc(n+2)+1;
			y=(y-1+t*z)%Calc(n+2)+1;
		}//解密x&y
		pair<van,van> posx=GetPos(x),posy=GetPos(y);
		van l=1,r=n+1,tmp1,tmp2;
		while (l<=r) {
			van mid=l+r>>1;
			if (QueryTree2(root2[posx.first],1,n+1,1,mid)>=posx.second) {
				tmp1=mid,r=mid-1;
			}
			else l=mid+1;
		}
		l=1,r=n+1;
		while (l<=r) {
			van mid=l+r>>1;
			if (QueryTree2(root2[posy.first],1,n+1,1,mid)>=posy.second) {
				tmp2=mid,r=mid-1;
			}
			else l=mid+1;
		}//二分查询x&y节点在某一状态下所在的列
		van x1=QueryTree(root[posx.first],1,n+1,tmp1),
			y1=QueryTree(root[posy.first],1,n+1,tmp2);
		z=LCA(x,y,x1,y1);
		write(z);
	}
}
```

---

## 作者：AmaoFox (赞：1)

我们把**儿子个数不为** $\bold1$ 的节点称为**坎**。那么，图中一共有 $2n+1$ 个**坎**，其中有 $n$ 个**坎**有两个儿子，$n+1$ 个**坎**是叶子。

我们发现这些**坎**来自于题设给的树上，则可以构建出一个新的树把他们连接起来，就像虚树，我们成之为**坎树**。

两个相邻的**坎**之间的所有点构成一条链，那么这之间的两个点肯定是编号小的作为编号大的祖先。

而如果两个点不在相邻的**坎**之间，则它们的 LCA 必定是一个别的**坎**。因为不会出现两个点不构成祖先关系但是 LCA 只有一个儿子的情况。

我们可以给每个不是**坎**的点对应一个坎。具体地说，我们可以将这个点不断地向它的唯一的儿子走，直到走到一个**坎**。每一个点对应唯一的一个**坎**。这样，当两个点属于同一个**坎**时就可以按照大小来判断，当两个点不属于同一个**坎**时，它们的 LCA 将是它们对应的**坎**在**坎树**上的 LCA。

由于**坎树**上面只有 $2n+1$ 个**坎**，**坎树**上面的 LCA 是好求的。我们只需要考虑怎么对应**坎**就好了。

我们考虑一个数组，里面按照顺序记录了从左到右所有的节点对应的**坎**是哪一个。由于**坎**是向下对应的，我们从最底下开始处理会比较方便。一开始从 $\frac{n(n+1)}2$ 开始的 $n+1$ 个节点都对应了自己。

然后每一层向上时，其中有两个节点，不妨设置为第 $x$ 个和第 $y$ 个，它们的父亲是相同的 $a_z$。则我们新建一个数组，该数组其它部分保持不变，而第 $x$ 个变成了 $a_z$，第 $y$ 个删掉了。

注意到每一层的修改是 $O(1)$ 的，我们创建一个主席树来维护所有的修改。数组的内容仍然不变。删除的操作，可以另开一棵树维护区间内有多少个元素来模拟。代码内这两棵树被简化成了同一棵。

代码见此：[云剪贴板链接](https://www.luogu.com.cn/paste/cwc6fpno)

---

## 作者：FutaRimeWoawaSete (赞：1)

说实话，思维难度今天模拟赛三道最低，考场上基本看完就会了，但是可持久化平衡树没学过自己研究了一下写写寄掉了最后拼暴力连离线分都没拿到，哭哭。

还调了半天，最后是数组开小了，绷不住了。

难度在于需要会可持久化平衡树，因为它强制在线。

-------------------------------------------------------

首先这个东西很像一个没有优化过的 leafy tree 结构，就是很多节点都是奇数儿子只有极少数节点是偶数儿子。

考虑直接进行一个 compress，就可以将树变成一棵儿子为奇数/偶数的节点个数数量级相同的树，可以理解成虚树，但是严谨来说我觉得是一棵性质不是那么好的 假 leafy tree 结构。

然后你发现建这棵树的过程等价于把所有 $a$ 序列中的点与儿子们拿出来建虚树，然后维护压缩的链上每个节点处于的链的顶端是谁。查询 LCA 的时候用这个东西做类似重链剖分上找 LCA 的方法即可。

难点是维护每个节点处于的链的顶端是谁。这个也没有任何思维难度，从上往下直接对于每层看成一个历史版本，用平衡树，平衡树的键值是序列维，维护的东西就是顶端节点。需要支持操作就只有单点修改，单点插值，这个平衡树随便搞搞就做完了。

需要注意空间常数和时间常数。

懒得卡常了，洛谷过了懒得管了。

```cpp
// ubsan: undefined
// accoders
#include "bits/stdc++.h"
using namespace std;
#define int ll
#define ll long long
const int Len = 2e5 + 5;
ll dp[Len << 2],A[Len << 2];
int pp,tot,n,q,t,m,a,b,c,rt[Len << 2];
struct node
{
	int l,r,siz;
	ll val;
	node(){l = r = val = siz = 0;}
	node(int L,int R,ll VAL,int SIZ){l = L , r = R , val = VAL , siz = SIZ;}
}fhq[Len * 120];
inline void update(int x){fhq[x].siz = fhq[fhq[x].l].siz + fhq[fhq[x].r].siz + 1;}
inline int Id(){return ++ tot;}
inline int clone(ll w)
{
	tot ++;
	fhq[tot] = node(0 , 0 , w , 1);
	return tot;
}
void split(int now,int Sz,int &x,int &y)
{
	if(!now){x = y = 0;return;}
	if(fhq[fhq[now].l].siz + 1 <= Sz)
	{
		x = Id();
		fhq[x] = fhq[now];
		split(fhq[x].r , Sz - (fhq[fhq[now].l].siz + 1) , fhq[x].r , y);
		update(x);
	}
	else
	{
		y = Id();
		fhq[y] = fhq[now];
		split(fhq[y].l , Sz , x , fhq[y].l);
		update(y);
	}
}
int merge(int x,int y)
{
	if(!x || !y) return x + y;
	if(rand() & 1) 
	{
		int rt = Id();
		fhq[rt] = fhq[x];
		fhq[rt].r = merge(fhq[rt].r , y);
		update(rt);
		return rt;
	}
	else
	{
		int rt = Id();
		fhq[rt] = fhq[y];
		fhq[rt].l = merge(x , fhq[rt].l);
		update(rt);
		return rt;
	}
}
inline void ins(int &rt,int sz,ll w)
{
	split(rt , sz , rt , a);
	rt = merge(rt , clone(w));
	rt = merge(rt , a);
}
inline void del(int &rt,int sz)
{
	split(rt , sz - 1 , rt , a);
	split(a , 1 , a , b);
	rt = merge(rt , b);
}
void change(int &rt,int sz,ll w)
{
	int lsize = fhq[fhq[rt].l].siz;
	if(lsize + 1 == sz) 
	{
		int p = Id();
		fhq[p] = fhq[rt];
		fhq[p].val = w;
		rt = p;
		update(rt);
		return;
	}
	else
	{
		int p = Id();
		fhq[p] = fhq[rt];
		rt = p;
		if(sz < lsize + 1) change(fhq[rt].l , sz , w);
		else change(fhq[rt].r , sz - (lsize + 1) , w);
		update(rt);
		return;
 	}
}
inline ll read() {
    char ch = getchar();
    ll x = 0, f = 1;
    while (ch < '0' || ch > '9') {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while ('0' <= ch && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
inline void write(ll x) {
    if (x < 0)
        putchar('-'), x = -x;
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}
inline ll getdep(ll x) 
{
    ll l = 1 , r = n + 1 , as = 0;
    while (l <= r) 
	{
        int mid = (l + r) >> 1;
        if (dp[mid] >= x) as = mid , r = mid - 1;
        else l = mid + 1;
    }
    return as;
}
inline ll Getrk(int &rt,ll rk)
{
	int u = rt;
	if(fhq[u].siz < rk) return -1;
	while(u)
	{
		int lsize = fhq[fhq[u].l].siz;
		if(lsize + 1 == rk) return fhq[u].val;
		else if(rk <= lsize) u = fhq[u].l;
		else rk -= (lsize + 1) , u = fhq[u].r;
	}
	return -1;
}
int nb;map<ll,ll> mp,pm;
map<pair<ll,ll>,ll> mpp;
int head[Len << 2],cnt,dfn[Len << 2],tim,siz[Len << 2],son[Len << 2],top[Len << 2],dep[Len << 2],fa[Len << 2];
struct mode
{
	int next,to;
}edge[Len << 3];
void add(int from,int to)
{
	edge[++ cnt].to = to;
	edge[cnt].next = head[from];
	head[from] = cnt;
}
void dfs1(int x,int f)
{
	dep[x] = dep[f] + 1;
	siz[x] = 1;
	fa[x] = f;
	for(int e = head[x] ; e ; e = edge[e].next)
	{
		int to = edge[e].to;
		if(to == f) continue;
		dfs1(to , x);
		siz[x] += siz[to];
		if(siz[to] > siz[son[x]]) son[x] = to;
	}
}
void dfs2(int x,int topf)
{
	top[x] = topf;
	dfn[x] = ++ tim;
	if(!son[x]) return;
	dfs2(son[x] , topf);
	for(int e = head[x] ; e ; e = edge[e].next)
	{
		int to = edge[e].to;
		if(to == fa[x] || to == son[x]) continue;
		dfs2(to , to);	
	}
}
inline int lca(int x,int y)
{
	while(top[x] != top[y])
	{
		if(dep[top[x]] < dep[top[y]]) swap(x , y);
		x = fa[top[x]];
	}
	return dep[x] < dep[y] ? x : y;
}
inline ll LCA(ll x,ll y)
{
	if(x == 1 || y == 1) return 1;
	if(x > y) swap(x , y);
	ll dpx = getdep(x) , dpy = getdep(y) , nmx = x - dp[dpx - 1] , nmy = y - dp[dpy - 1] , fax = Getrk(rt[dpx - 1] , nmx) , fay = Getrk(rt[dpy - 1] , nmy);
	if(fax == fay) return x;
	int xx = mp[fax] , yy = mp[fay] , llca = lca(xx , yy);
	if(llca == xx) return x;
	return pm[llca];
}
signed main()
{
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	srand(time(0));
	n = read() , q = read() , t = read();
	for(int i = 1 ; i <= n ; i ++) A[i] = read();
	for(int i = 1 ; i <= n + 1 ; i ++) dp[i] = 1ll * i * (i + 1) / 2;
	for(int i = 1 ; i <= n ; i ++) 
	{
		ll nms = A[i] - dp[i - 1] , now1 = dp[i] + nms , now2 = dp[i] + nms + 1;
		if(!mp[A[i]]){mp[A[i]] = ++ pp;pm[pp] = A[i];}
		if(!mp[now1]){mp[now1] = ++ pp;pm[pp] = now1;}
		if(!mp[now2]){mp[now2] = ++ pp;pm[pp] = now2;}
		rt[i] = rt[i - 1];
		change(rt[i] , nms , now1);//42271 8920715078;
		ins(rt[i] , nms , now2);
		if(!mpp[make_pair(mp[A[i]] , mp[now1])])
		{
			add(mp[A[i]] , mp[now1]);
			mpp[make_pair(mp[A[i]] , mp[now1])] = 1;
		} 
		if(!mpp[make_pair(mp[A[i]] , mp[now2])])
		{
			add(mp[A[i]] , mp[now2]);
			mpp[make_pair(mp[A[i]] , mp[now2])] = 1;
		}
		if(i != 1)
		{
			ll ff = Getrk(rt[i - 1] , nms);
			if(ff != A[i])
			{
				if(!mp[ff]){mp[ff] = ++ pp;pm[pp] = ff;}
				if(!mpp[make_pair(mp[ff] , mp[A[i]])])
				{
					add(mp[ff] , mp[A[i]]);
					mpp[make_pair(mp[ff] , mp[A[i]])] = 1;
				}
			} 
		}
	}
	dfs1(1 , 0);
	dfs2(1 , 1);
	const ll mod = 1ll * (n + 1) * (n + 2) / 2;ll lstans = 0;
	for(int i = 1 ; i <= q ; i ++)
	{
		ll x = (read() - 1 + t * lstans) % mod + 1 , y = (read() - 1 + t * lstans) % mod + 1;
		write(lstans = LCA(x , y)) , putchar('\n');
	}
	return 0;
}
```

---

## 作者：happybob (赞：0)

对询问 $u,v$，求出 $u$ 子树内某个叶子 $x$ 和 $v$ 子树内某个叶子 $y$，如果 $u,v$ 没有祖先关系，答案就是 $x,y$ 的 LCA。如果能求出 $x,y$ 的 LCA，判断这个点的深度和 $u,v$ 深度关系就可以确定 $u,v$ 是否有祖先关系。

考虑将问题分为两部分解决，分别是求某个点子树内某个叶子，以及如何求两个叶子的 LCA。

对于求某个点子树叶子，考虑按照深度从大到小扫描线，维护目前层的每个点的子树内某个叶子构成的序列，只需要支持单点删除，可持久化平衡树维护即可。

对于查询两个叶子的 LCA，考虑整个过程是从深到浅，每层大部分点都直接跳到父亲，有两个点会合并。这等价于问 $u,v$ 两个点第一次被合并的时间。Kruskal 重构树即可。

复杂度 $O(n \log n)$。

---

## 作者：Lvlinxi2010 (赞：0)

首先我们可以发现只有一个儿子的节点可以构成很多条链，我们考虑把每一条这样的链缩成一个点。

然后每一个有两个儿子的节点都会分出两条链出来，所以有两个儿子的节点不会被缩掉，并且有可能成为 $lca$，但这样的点只有 $n$ 个再加上最后一层的 $n+1$ 个节点所以最后剩下的点的个数是 $\mathcal{O}(n)$ 的，我们在缩完链的图上找 $lca$ 是 $\mathcal{O}(n\log n)$ 的。

那怎么查找每一个点所在链的编号呢，我们用可持久化线段树维护。

我们从第 $n+1$ 层开始看然后考虑每一个有两个儿子的节点（每层只有一个），设它在这一层是第 $k$ 个节点，那它会把下一层的第 $k$ 个和第 $k+1$ 个节点合并起来，然后成为一条新链的链尾元素。

于是我们在可持久化线段树上删除（修改点权为 $0$）第 $k+1$ 个节点，并将第 $k$ 个节点的链头编号记为 $num+1$（$num$ 为目前有的链的数量）。

每次查询一层的第 $k$ 个节点的链头就是查询这一层的线段树上第 $k$ 个元素。

结合代码理解更佳。

附上代码：
```c++
#include<bits/stdc++.h>
#define FL(i,a,b) for(ll i=(a);i<=(b);i++)
#define FR(i,a,b) for(ll i=(a);i>=(b);i--)
#define ll long long
using namespace std;
const ll MAXN = 5e5 + 10;
ll n,q,t,num=0;
ll a[MAXN],rt[MAXN];
ll dep[MAXN],f[20][MAXN];
ll Num[MAXN],id[MAXN];
vector<ll>G[MAXN]; 
struct Segment_Tree{
	#define ls t[x].Ls
	#define rs t[x].Rs
	ll tot=0;
	struct node{
		ll id,sum;
		ll Ls,Rs;
	}t[MAXN*20];
	void pushup(ll x){
		t[x].sum=t[ls].sum+t[rs].sum;
	}
	void build(ll &x,ll l,ll r){
		x=++tot;
		if(l==r){
			t[x].id=++num;
			t[x].sum=1;
			return ;
		}
		ll mid=(l+r)>>1;
		build(ls,l,mid);
		build(rs,mid+1,r);
		pushup(x);
	}
	void modify_sum(ll &x,ll y,ll l,ll r,ll k,ll v){
		x=++tot;
		t[x]=t[y];
		if(l==r){
			t[x].sum=v;
			return ;
		}
		ll mid=(l+r)>>1;
		if(k<=t[ls].sum) modify_sum(ls,t[y].Ls,l,mid,k,v);
		else modify_sum(rs,t[y].Rs,mid+1,r,k-t[ls].sum,v);
		pushup(x);
	}
	void modify_id(ll &x,ll y,ll l,ll r,ll k,ll v){
		x=++tot;
		t[x]=t[y];
		if(l==r){
			t[x].id=v;
			return ;
		}
		ll mid=(l+r)>>1;
		if(k<=t[ls].sum) modify_id(ls,t[y].Ls,l,mid,k,v);
		else modify_id(rs,t[y].Rs,mid+1,r,k-t[ls].sum,v);
		pushup(x);
	}
	ll query(ll x,ll l,ll r,ll k){
		if(l==r) return t[x].id;
		ll mid=(l+r)>>1;
		if(k<=t[ls].sum) return query(ls,l,mid,k);
		else return query(rs,mid+1,r,k-t[ls].sum);
	}
}T;
ll lca(ll x,ll y){
	if(dep[x]<dep[y]) swap(x,y);
	FR(i,19,0) if(dep[f[i][x]]>=dep[y]) x=f[i][x];
	if(x==y) return x;
	FR(i,19,0) if(f[i][x]!=f[i][y]) x=f[i][x],y=f[i][y];
	return f[0][x];
}
void dfs(ll u,ll fa){
	dep[u]=dep[fa]+1;
	f[0][u]=fa;
	FL(i,1,19) f[i][u]=f[i-1][f[i-1][u]];
	for(ll v:G[u]){
		if(v==fa) continue;
		dfs(v,u);
	}
}
signed main(){
	scanf("%lld%lld%lld",&n,&q,&t);
	FL(i,1,n) scanf("%lld",&a[i]);
	FL(i,1,n) Num[i]=i*(i+1)/2;
	FL(i,1,n+1) id[i]=n*(n+1)/2+i;
	T.build(rt[n+1],1,n+1);
	FR(i,n,1){
		ll pos=a[i]-i*(i-1)/2;
		id[++num]=a[i];
		T.modify_sum(rt[i],rt[i+1],1,n+1,pos+1,0);
		T.modify_id(rt[i],rt[i],1,n+1,pos,num);
		ll u=T.query(rt[i+1],1,n+1,pos),v=T.query(rt[i+1],1,n+1,pos+1);
		G[num].push_back(u);
		G[num].push_back(v);
	}
	dfs(num,0);
	ll lastans=0,mod=(n+1)*(n+2)/2;
	while(q--){
		ll u,v;
		scanf("%lld%lld",&u,&v);
		u=(u-1+t*lastans)%mod+1,v=(v-1+t*lastans)%mod+1;
		ll depu=lower_bound(Num,Num+n+1,u)-Num;
		ll depv=lower_bound(Num,Num+n+1,v)-Num;
		ll idu=T.query(rt[depu],1,n+1,u-depu*(depu-1)/2);
		ll idv=T.query(rt[depv],1,n+1,v-depv*(depv-1)/2);
		if(idu==idv){
			printf("%lld\n",lastans=((depu<depv)?u:v));
			continue;
		}
		ll Lca=lca(idu,idv);
		printf("%lld\n",lastans=((Lca==idu)?u:((Lca==idv)?v:id[Lca])));  
	}
}
```

---

## 作者：Prean (赞：0)

题意：使用奇怪的方式建一个有 $ (n+1) \times (n+2) \div 2 $ 个节点的树，每次给定两个点询问其 $ \rm LCA $。

首先大眼观察：答案似乎只可能是给定的 $ n $ 个节点？

并不，如果两个节点之间存在祖先关系的话那么就寄了。。。

所以考虑先把祖先关系判掉，然后询问就只剩下没有祖先关系的了。

没有祖先关系，答案就只可能是给定的 $ n $ 个节点了！/mgx

因为没有祖先关系，所以考虑找到自己到根节点的第一个给定的节点。

这样要分两种情况，巨麻烦，于是找子树内不包括自己的深度最小的给定的节点。

假设自身是 $ u $，该节点是 $ v $，以及自身处于第 $ x $ 层，该节点处于第 $ y $ 层，有：
$$ u+\frac {(y-x)(y+x-1)} 2=v $$
可以自行理解一下这是为什么。移项得：
$$ u-\frac {x^2-x} 2=v-\frac {y^2-y} 2 $$
$$ u-\frac {x(x-1)} 2=v-\frac {y(y-1)} 2 $$
不过这个柿子是错的，因为如果有特殊点在往儿子走的路径的左边就假了。

所以要分别减去某个序列的前缀比自身小的数，二维偏序强制在线，只能使用主席树或者 K-DT。

所以对 $ u-\frac {x(x-1)} 2- $ 减去前面比自己大的节点，对相同的给定的节点开一个栈，按照深度从小到大的顺序排个序，直接二分就好了。

然后 $ v $ 在只有这 $ n $ 个节点的树上的父亲就是 $ u $ 到根节点的第一个给定的节点。

建出原树可以倒序扫描 $ a $ 数组，然后记录 $ lst $，最后若有节点没有父亲那么就令父亲为 $ 1 $。

如果我是最后一层的节点？将最后一层的节点全部加入栈即可。

接下来考虑有祖先关系的。有祖先关系的节点在压缩后的树上一定也有祖先关系，通过 $ dfn $ 序判断这个，还需要通过上面的式子再判断一遍（因为如果两个节点到根节点的第一个给定的节点是同一个节点，但是属于两个不同的子树那就没有祖先关系），之后直接返回编号小的节点即可。

代码咕了（不过这种做法应该会比主席树快吧

---

