# [ARC080E] Young Maids

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc080/tasks/arc080_c

$ N $ を正の偶数とします。

$ (1,\ 2,\ ...,\ N) $ の順列 $ p\ =\ (p_1,\ p_2,\ ...,\ p_N) $ があります。 すぬけ君は、次の手続きによって $ (1,\ 2,\ ...,\ N) $ の順列 $ q $ を作ろうとしています。

まず、空の数列 $ q $ を用意します。 $ p $ が空になるまで、次の操作を繰り返します。

- $ p $ の隣り合う $ 2 $ つの要素を選び、順に $ x $, $ y $ とする。 $ x $, $ y $ を $ p $ から取り除き (このとき、$ p $ は $ 2 $ だけ短くなる)、$ x $, $ y $ をこの順のまま $ q $ の先頭へ追加する。

$ p $ が空になったとき、$ q $ は $ (1,\ 2,\ ...,\ N) $ の順列になっています。

辞書順で最小の $ q $ を求めてください。

## 说明/提示

### 制約

- $ N $ は偶数である。
- $ 2\ <\ =\ N\ <\ =\ 2\ ×\ 10^5 $
- $ p $ は $ (1,\ 2,\ ...,\ N) $ の順列である。

### Sample Explanation 1

次の順に操作を行えばよいです。 $ p $ $ q $ $ (3,\ 2,\ 4,\ 1) $ $ () $ ↓ ↓ $ (3,\ 1) $ $ (2,\ 4) $ ↓ ↓ $ () $ $ (3,\ 1,\ 2,\ 4) $

### Sample Explanation 3

次の順に操作を行えばよいです。 $ p $ $ q $ $ (4,\ 6,\ 3,\ 2,\ 8,\ 5,\ 7,\ 1) $ $ () $ ↓ ↓ $ (4,\ 6,\ 3,\ 2,\ 7,\ 1) $ $ (8,\ 5) $ ↓ ↓ $ (3,\ 2,\ 7,\ 1) $ $ (4,\ 6,\ 8,\ 5) $ ↓ ↓ $ (3,\ 1) $ $ (2,\ 7,\ 4,\ 6,\ 8,\ 5) $ ↓ ↓ $ () $ $ (3,\ 1,\ 2,\ 7,\ 4,\ 6,\ 8,\ 5) $

## 样例 #1

### 输入

```
4
3 2 4 1```

### 输出

```
3 1 2 4```

## 样例 #2

### 输入

```
2
1 2```

### 输出

```
1 2```

## 样例 #3

### 输入

```
8
4 6 3 2 8 5 7 1```

### 输出

```
3 1 2 7 4 6 8 5```

# 题解

## 作者：dread (赞：5)

## B（AT2688 Young Maids）（ARC080E）：

将$p$,$q$上的位置从左开始依次设为$0,1,...,N-1$。

在按字典序求最小列的问题上,我们可以从列的开头开始依次确定当时可能有的最小值。

首先，确定作为$q_0$可能存在的最小值，我们知道，能成为$q _0$的，是$p$上第偶数位的要素，我们要将这些中要素中最小的记为$q_0$。另外,将这个要素在$p$上的位置设为$i$。

接下来,确定 $q_1$中所有可能存在的最小值。$q_1$一定是$p$上的第奇数位的要素,位于位置$i$右侧.将这些中最小的要素记为$q_1$。另外,将这个要素在$p$上的位置设为$j$。

这样,$p$的剩余要素就被分割成$3$个区间$[0,i),[i+1,j),[j+1,N)$。

接下来,在区间偶数编号的要素中把最小的记为$q_2$。另外,把这个要素在$S$上的位置设为$i'$

接下来,确定$q_3$所可能有的最小值.$q_3$可以成为$S$上的奇数编号的要素.这些元素中,最小的元素被确定为$q_3$。

另外,把这个元素在$S$上的位置设为$j'$的话,$S$的剩余元素以位置$i',j'$为界,被分割为三个区间。

反复进行上述步骤，就能求出字典序最小的$q$。但时间复杂度为$\Theta(N^2)$。

这样的时间当然无法通过$1\times{10}^5$的数据，我们考虑优化。

###### 优化1：

某个区间上的偶数(奇数)求出第二个要素的最小值的步骤

我们可以预处理这些数据，将只提取了第二个要素的东西放在线段树上。

这样在获取最小值的同时也可以获得位置

###### 优化2：

在区间中选择要素的步骤时，我们可以将现有的所有区间用一个堆来维护，

将各区间的优先级设定该区间奇数编号的要素的最小值即可。

这样我们可以做到$\Theta(N\ log N)$的优秀时间复杂度，也就可以顺利通过大数据了。

#### code：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
int n, a[N], t[2][N << 2];

inline int read() {
	int s = 0, f = 1;
	char ch;
	for(; ch < '0' || ch > '9'; ch = getchar())	if(ch == '-')	f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar())	s = (s << 1) + (s << 3) + ch - '0';
	return s * f;
}

inline void add(int o, int pos, int l, int r, int cnt) {
	if (a[cnt] < a[t[o][pos]])	t[o][pos] = cnt;
	if (l == r)	return;
	int mid = (l + r) >> 1;
	if (cnt <= mid)	add(o, pos << 1, l, mid, cnt);
	else	add(o, pos << 1 | 1, mid + 1, r, cnt);
}

inline int ask(int o, int pos, int l, int r, int L, int R) {
	if (l > R || r < L)	return 0;
	if (L <= l && r <= R)	return t[o][pos];
	int mid = (l + r) >> 1;
	int lans = ask(o, pos << 1, l, mid, L, R);
	int rans = ask(o, pos << 1 | 1, mid + 1, r, L, R);
	return a[lans] < a[rans] ? lans : rans;
}

struct node {
	int l, r, v;
	node() {}
	node(int _l, int _r){ l = _l, r = _r, v = l > r ? 0 : ask(l & 1, 1, 1, n, l, r); }
	friend bool operator < (node A,node B) { return a[A.v] < a[B.v]; }
};

set <node> s;

int main() {
	n = read();
	a[0] = n + 1;
	for(int i = 1; i <= n; ++i) {
		a[i] = read();
		add(i & 1, 1, 1, n, i);
	}
	s.clear();
	s.insert(node(1, n));
	for(int i = 1; i <= n >> 1; ++i) {
		node now = *s.begin();
		s.erase(s.begin());
		int l = now.l, r = now.r;
		int lmid = now.v, rmid = ask((lmid & 1) ^ 1, 1, 1, n, lmid, r);
		printf("%d %d ", a[lmid], a[rmid]);
		s.insert(node(l, lmid - 1));
		s.insert(node(lmid + 1, rmid - 1));
		s.insert(node(rmid + 1, r));
	}
	puts("");
	return 0;
}

```



---

## 作者：pufanyi (赞：3)

由于字典序大小是从前往后决定的，所以我们考虑从前往后确定这个序列，也就是将题意中的过程倒着做。

我们考虑在某一状态下，选择的两个数在原序列中是 $p_l,p_r$，那么再次之前的选择中，不可能出现选择的数为 $p_{a_l},p_{a_r}$ 使得 $a_l<l<a_r$ 或 $a_l<r<a_r$。

于是我们发现倒着考虑是，选择$p_l,p_r$时就是把序列分成了 $[1,l-1],[l+1,r-1],[r+1,n]$ 这 $3$ 段，这 $3$ 段相互独立。

我们考虑怎样的 $\left<l,r\right>$ 是合法的。显然就是 $[1,l-1],[l+1,r-1],[r+1,n]$ 长度均为偶数时（可能为空）。

所以 $l$ 一定为奇数，$r$ 一定为偶数。

我们可以维护出 $p$ 中奇数位于偶数位的最小值，并用一个小根堆维护每一个 $[l,r]$ 的最小值即可，每次选择后将 $[l,r]$ 分成 $3$ 段重新放入堆中。

```cpp
#include <bits/stdc++.h>

using namespace std;

// 读入输出优化略去

const int maxn = 200005;
const int inf = 0x3f3f3f3f;

int n;
int xx[maxn]; // 题意中的p

#define ls(x) (x << 1)
#define rs(x) (x << 1 | 1)

struct Tree
{
    struct Node
    {
        int jx, ox; // 奇数位的最小值与偶数位的最小值
    } no[maxn << 2];

    int k;

    inline int minn(int a, int b)
    {
        if (!a || !b)
            return a | b;
        else
            return xx[a] < xx[b] ? a : b;
    }

    inline void push_up(int k)
    {
        no[k].jx = minn(no[ls(k)].jx, no[rs(k)].jx);
        no[k].ox = minn(no[ls(k)].ox, no[rs(k)].ox);
    }

    inline void build_tree(int n)
    {
        for (k = 1; k <= n; k <<= 1);
        for (int i = 1; i <= n; ++i)
        {
            if (i & 1)
                no[i + k].jx = i;
            else
                no[i + k].ox = i;
        }
        for (int i = k; i; --i)
            push_up(i);
    }

    inline int query(int l, int r, int kk)
    {
        int ans = 0;
        for (l += k - 1, r += k + 1; l ^ r ^ 1; l >>= 1, r >>= 1)
        {
            if (~l & 1)
                ans = minn(kk ? no[l ^ 1].jx : no[l ^ 1].ox, ans);
            if (r & 1)
                ans = minn(kk ? no[r ^ 1].jx : no[r ^ 1].ox, ans);
        }
        return ans;
    }
} tr;

struct QJ
{
    int l, r, ansl, ansr; // 现在可选区间为[l,r]，最优是选择p[l]和p[r]

    friend bool operator < (QJ a, QJ b)
    {
        return xx[a.ansl] > xx[b.ansl];
    }

    QJ (int l, int r)
    {
        this->l = l;
        this->r = r;
        this->ansl = tr.query(l, r, 1);
        this->ansr = tr.query(ansl + 1, r, 0);
    }
};

priority_queue<QJ> q;

int main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
        read(xx[i]);
    tr.build_tree(n);
    q.push(QJ(1, n));
    while (!q.empty())
    {
        QJ now = q.top();
        q.pop();
        writesp(xx[now.ansl]);
        writesp(xx[now.ansr]);
        if (now.ansl + 1 < now.ansr - 1)
            q.push(QJ(now.ansl + 1, now.ansr - 1));
        if (now.l < now.ansl - 1)
            q.push(QJ(now.l, now.ansl - 1));
        if (now.ansr + 1 < now.r)
            q.push(QJ(now.ansr + 1, now.r));
    }
    return 0;
}
```

---

## 作者：Leap_Frog (赞：3)

### P.S.
提供一个 $O(n\log n)$ 的做法。  
~~原题不是我搜出来的啊/px~~  
### Discription.
给定一个序列，你可以取出连续的两个元素，并把它们 **按顺序** 放到答案序列中。  
现在 **倒序** 遍历这个序列，并问答案序列的最小字典序是多少。  
### Solution.
我们手模小数据，我们第一步能取的东西肯定是两个奇偶性不同的位置。  
第二步能取的东西仍然是两个奇偶性不同的位置，但是不能被第一次选的位置分开。  
观察这个东西，它是可以分治的！  
那么我们可以直接分治，~~每次迭代规模减半~~，每个位置只会取一次，那么它是 $O(n)$ 的。  
然后我们就需要考虑如何快速处理出每次迭代时最优选那两个数。  
观察一波样例我们就会发现每次选的肯定满足左边是区间最大值。  
然后我们就需要一个支持区间查询最大值位置的数据结构，显然线段树（  
对于奇偶分别建两颗线段树，然后直接分类讨论就好了。  

当前我们的代码如下：
```
inline void solve(int l,int r)
{
	if(l>r) return;
	int wh1=query(l&1,1,1,n,l,r).wh,wh2=query((l&1)^1,1,1,n,wh1+1,r).wh;
	rs[++rt]=make_pair(a[wh1],a[wh2]),solve(l,wh1-1),solve(wh1+1,wh2-1),solve(wh2+1,r);
}
```
结果你会发现过不了这个样例
```
6
6 1 2 5 3 4
```
我们刚开始肯定先选 $[1,4]$ 然后第二步会选 $[2,3]$，第三步会选 $[5,6]$。  
显然有更小的先选 $[1,4]\rightarrow[5,6]\rightarrow[2,3]$ 的方案。  
出错原因：考虑的时候它分成的几个子区间是可以任意顺序排布的。  

我们发现，所有的区间关系显然会构成一棵树，然后在这棵树上 `Topo排序` 就好了。

复杂度 $O(n\log n)$
### Coding.
```
//愿你和你重要的人能够再次重逢！
#include<bits/stdc++.h>
using namespace std;
template<typename T>inline void read(T &x)
{
	x=0;char c=getchar(),f=0;
	for(;c<'0'||c>'9';c=getchar()) if(!(c^45)) f=1;
	for(;c>='0'&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	if(f) x=-x;
}
struct node{int vl,wh;}t[2][800005];pair<int,int>rs[200005];int rt;
int n,a[200005],b[200005];const int INF=(int)0x3f3f3f3f3f3f3f3f;
struct edge{int to,nxt;}e[400005];int et,head[200005],deg[200005];
inline void adde(int x,int y) {if(x&&y) e[++et]=(edge){y,head[x]},head[x]=et,deg[y]++;}
inline node operator+(node a,node b) {if(a.vl<b.vl) return a;else return b;}
inline void build(int ID,int x,int l,int r)
{
	if(l==r) return(void)(t[ID][x].vl=b[l],t[ID][x].wh=l);
	build(ID,x<<1,l,(l+r)>>1),build(ID,x<<1|1,((l+r)>>1)+1,r),t[ID][x]=t[ID][x<<1]+t[ID][x<<1|1];
}
inline node query(int ID,int x,int l,int r,int dl,int dr)
{
	if(l>dr||dl>r) return(node){INF,0};else if(dl<=l&&r<=dr) return t[ID][x];
	return query(ID,x<<1,l,(l+r)>>1,dl,dr)+query(ID,x<<1|1,((l+r)>>1)+1,r,dl,dr);
}
inline int solve(int l,int r)
{
	if(l>r) return 0;
	int wh1=query(l&1,1,1,n,l,r).wh,wh2=query((l&1)^1,1,1,n,wh1+1,r).wh;
	int nw=++rt;adde(nw,solve(l,wh1-1)),adde(nw,solve(wh1+1,wh2-1)),adde(nw,solve(wh2+1,r));
	return rs[nw]=make_pair(a[wh1],a[wh2]),nw;
}
inline void topo()
{
	priority_queue<pair<pair<int,int>,int>,vector<pair<pair<int,int>,int> >,greater<pair<pair<int,int>,int> > >q;
	for(int i=1;i<=rt;i++) if(!deg[i]) q.push(make_pair(rs[i],i));
	while(!q.empty())
	{
		int x=q.top().second;printf("%d %d ",q.top().first.first,q.top().first.second),q.pop();
		for(int i=head[x];i;i=e[i].nxt) if(!--deg[e[i].to]) q.push(make_pair(rs[e[i].to],e[i].to));
	}
}
int main()
{
	read(n);for(int i=1;i<=n;i++) read(a[i]);
	memset(b,0x3f,sizeof(b));for(int i=1;i<=n;++++i) b[i]=a[i];build(1,1,1,n);
	memset(b,0x3f,sizeof(b));for(int i=2;i<=n;++++i) b[i]=a[i];build(0,1,1,n);
	return solve(1,n),topo(),putchar('\n'),0;
}
```

---

## 作者：DPair (赞：3)

提供一种ST表加树状数组的写法。

（然而我人傻常数大）

## 【思路】
由于我们要使字典序最小，又要不断取出两个扔在最前面，很难受。

所以我们考虑逆推，然后贪心，每次取出两个“可以取的”（即可以构造出一种序列使得这两个数被最后取），使得字典序最小的两个数。

说的容易，问题是怎么判断两个数是“可以取的”呢？

~~其实你会发现这个东西很像一个括号匹配。~~

我们先假定初始区间为 $[l, r]$

不难发现，你取出两个数 $u, v$ 之后会把整个序列划分成三个区间 $[l, u-1], [u+1, v-1], [v+1,r]$ 。

显然此时接下来取的所有数对都必须属于 **同一区间**。

原因在于，如果顺序来取，每次取的两个数都是相邻的，而实际上，后被取走两个数 **在真实顺序上** 比现在取走的两个被取走的更早，也就是说我们 **逆推中** 它们在这个状态之后必然是相邻的！

那么显然，剩下来三个区间必然长度都为偶数。

由于显然能找到一种方法取完一个长度为偶数的区间，我们必定能构造出一种方案使得某一时刻，$u, v$ 这两个数相邻。

然后。。。似乎就很好做了。

我们首先要求 $u-1-l+1=u-l$ 为偶数。

那么。。。 $l, u$ 奇偶性必然相同。

所以我们考虑把数值分为奇偶两类，用一个 **ST表** 维护下标为奇数的最小值与下标为偶数的最小值。

那么对于每一个区间，我们都考虑按照上面的方法取出两个数然后分裂出 $3$ 个小区间。

每一次取出一个区间，然后通过这个区间的 $u$ 计算出对应的 $v$ ，然后分裂出 $3$ 个区间，判断这些区间有没有被访问过，然后把没访问过的压到堆里面即可。

由于每一个区间的 $l$ 奇偶性确定， $u, v$ 奇偶性也都是确定的。

最后，一个区间是否访问过可以用树状数组维护，然而我人傻常数大。

复杂度应该是 $O(nlogn)$ 的。

## 【代码】
```cpp
#include <bits/stdc++.h>
using namespace std;
#define getchar() printf("I am a cheater!I AK IOI!%c", 10)
typedef long long LL;
template <typename T>
inline void read(T &x){
    x = 0;int fu = 1;
    char c = getchar();
    while(c > 57 || c < 48){
        if(c == 45) fu = -1;
        c = getchar();
    }
    while(c <= 57 && c >= 48){
        x = (x << 3) + (x << 1) + c - 48;
        c = getchar();
    }
    x *= fu;
}
template <typename T>
inline void fprint(T x){
    if(x < 0) putchar(45), x = -x;
    if(x > 9) fprint(x / 10);
    putchar(x % 10 + 48);
}
template <typename T>
inline void fprint(T x, char ch){
    fprint(x);putchar(ch);
}
inline char next_char(){
    char ch = getchar();
    while(ch == 9 || ch == 10 || ch == 32) ch = getchar();
    return ch;
}

#define MAXN 200005
int n, a[MAXN];
int ev[MAXN][25], od[MAXN][25];

inline int mn(int x, int y){
    if(a[x] > a[y]) return y;
    return x;
}

inline int query(int l, int r){
    int k = log2(r - l + 1);
    if((l & 1)) return mn(od[l][k], od[r - (1 << k) + 1][k]);
    else return mn(ev[l][k], ev[r - (1 << k) + 1][k]);
}

struct Inter{
    int l, r;
    Inter (int tmp1, int tmp2) : l(tmp1), r(tmp2){}
    inline bool operator < (const Inter &b) const{
        return a[query(l, r)] > a[query(b.l, b.r)];
    }
};

priority_queue <Inter> q;
int c[MAXN];
inline int lowbit(int x){return x & -x;}
inline void modify(int x){for (;x <= n;x += lowbit(x)) c[x] ++;}
inline int Query(int x){int ret = 0;for (;x;x -= lowbit(x)) ret += c[x];return ret;}
int main(){
    read(n);
    for (register int i = 1;i <= n;i ++) read(a[i]);
    for (register int i = 1;i <= n;i ++){
        if(i & 1) od[i][0] = i;
        else ev[i][0] = i;
    }
    a[0] = 0x3f3f3f3f;
    for (register int i = 1;i <= 20;i ++){
        for (register int j = 1;j + (1 << i) - 1 <= n;j ++){
            od[j][i] = mn(od[j][i - 1], od[j + (1 << (i - 1))][i - 1]);
            ev[j][i] = mn(ev[j][i - 1], ev[j + (1 << (i - 1))][i - 1]);
        }
    }
    q.push(Inter(1, n));
    while(!q.empty()){
        Inter x = q.top();
        q.pop();
        int pos = query(x.l, x.r);
        int rr = query(pos + 1, x.r);
        fprint(a[pos], 32);fprint(a[rr], 32);
        modify(pos);modify(rr);
        if(pos - 1 >= x.l && !(Query(pos - 1) - Query(x.l - 1))) q.push(Inter(x.l, pos - 1));
        if(pos + 1 <= rr - 1 && !(Query(rr - 1) - Query(pos))) q.push(Inter(pos + 1, rr - 1));
        if(rr + 1 <= x.r && !(Query(x.r) - Query(rr))) q.push(Inter(rr + 1, x.r));
    }
    putchar(10);
}
```

---

## 作者：zhimao (赞：2)

提供一种比较暴力的做法 。

由于最后选的排在最前面 ， 所以我们考虑逆推 。 对于一段区间 $a_i,l<=i<=r$ ， 最后我们一定选 $x,y$ 满足 $x<y,(x-l)\bmod 2=0,(r-y)\bmod 2=0,a_x$ 最小 ， 在此条件下 $a_y$ 也最小 。这件事可以用 $st$ 表解决 。 操作后区间被分成 0 到 3 个子区间 ， 由于这是我们最后选的 ， 剩下的子区间只能在内部选 ， 即不能选一个在一区间 ， 另一个在二或三区间 。 这就可以解释 $(x-l)\bmod 2=0,(r-y)\bmod 2=0$ 。于是我们向下递归 ， 合并答案 。 因为两个子区间间的操作互相不影响 ， 合并时直接用类似归并排序合并从小到大合 。

然而这种朴素做法太差 ， 时空复杂度都吃不消 。 首先 ， 我们可以用 $vector$  ， 这样空间就够了 。 其次 ， 我们要利用 $vector$ 一个重要特性 ：**$vector$交换两容器（即 $ swap$ ）的时间复杂度是 $O(1)$ 的** ，因此我们可以启发式合并 ， 继承最大子区间的答案 。 但此时又出现了一个问题 : 当前区间 $vector$ 第一位应是之前选的 $x,y$ 这样 $swap$ 就会出事 。于是我们想到另一个套路 ： 在 $vector$ 里倒序存放答案 ， 这样 $x,y$ 只要最后丢进 $vector$ 即可 。

但倒序存放还有一个问题~~因为这我们调了两个钟头~~ ， 合并时**不能**从 $v.begin()$ 开始从大到小排 ，要从 $v.end()$ 开始从小到大排，最后 $reverse$ 一下 。 至于为什么请读者自行思考 ， 模拟一下就知道了 。

时间复杂度 ： 由于一个区间最多被分成三个 , 为 $O(nlog_3^2n)$ .

代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[400000],b[400000],c[400000],st0[400000][20],st1[400000][20],lo[400000];
struct arr
{
	int x,y;
};
vector<arr> v[400000],t,up[400000][4];
bool cmp(arr x,arr y)
{
	return y.x<x.x;
}
int find0(int l,int r)
{
	int len=lo[r-l+1];
	if(c[st0[l][len]]<c[st0[r-(1<<len)+1][len]]) return st0[l][len];
	return st0[r-(1<<len)+1][len];
}
int find1(int l,int r)
{
	int len=lo[r-l+1];
	if(b[st1[l][len]]<b[st1[r-(1<<len)+1][len]]) return st1[l][len];
	return st1[r-(1<<len)+1][len];
}
void update(int m,int n,int bo)
{
	if(!bo)
	{
		swap(v[m],up[m][n]);
		return;
	}
	t.clear();
	int l=v[m].size()-1,r=up[m][n].size()-1;
	while(r+l>-2)
	{
		if(l<0) t.push_back(up[m][n][r--]);
			else if(r<0) t.push_back(v[m][l--]);
				else if(cmp(v[m][l],up[m][n][r])) t.push_back(up[m][n][r--]);
					else t.push_back(v[m][l--]);
	}
	reverse(t.begin(),t.end());
	swap(t,v[m]);
}
void solve(int x,int y)
{
	int cnt=0;
	v[++m].clear();
	int l0=x>>1,r0=y>>1,l1=(x+1)>>1,r1=(y+1)>>1,p,q,pp,qq;
	if(!(x&1))
	{
		p=find0(l0,min(r0,r1-1));
		q=find1(p+1,r1);
		qq=(q<<1)-1;
		pp=p<<1;
	}
	else
	{
		q=find1(l1,min(r1,r0));
		p=find0(q,r0);
		pp=p<<1;
		qq=(q<<1)-1;
		swap(p,q);
		swap(pp,qq);
	}
	if(pp>x)
	{
		solve(x,pp-1);
		swap(up[m][++cnt],v[m+1]);
	}
	if(qq>pp+1)
	{
		solve(pp+1,qq-1);
		swap(up[m][++cnt],v[m+1]);
	}
	if(qq<y)
	{
		solve(qq+1,y);
		swap(up[m][++cnt],v[m+1]);
	}
	if(cnt==1) update(m,1,0);
	else
	{
		if(cnt==2)
		{
			if(up[m][1].size()<up[m][2].size()) swap(up[m][1],up[m][2]);
			update(m,1,0);
			update(m,2,1);
		}
		else
		if(cnt==3)
		{
			if(up[m][1].size()<up[m][2].size()) swap(up[m][1],up[m][2]);
			if(up[m][1].size()<up[m][3].size()) swap(up[m][1],up[m][3]);
			update(m,1,0);
			update(m,2,1);
			update(m,3,1);
		}
	}
	if(!(x&1)) v[m--].push_back({c[p],b[q]}); else v[m--].push_back({b[p],c[q]});
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	n>>=1;
	for(int i=1;i<=n;i++)
	{
		st1[i][0]=st0[i][0]=i;
		b[i]=a[(i<<1)-1];
		c[i]=a[i<<1];
	}
	for(int i=2;i<=n;i++) lo[i]=lo[i>>1]+1;
	for(int i=1;i<=lo[n];i++)
		for(int j=1;j+(1<<i)<=n+1;j++)
		{
			if(c[st0[j][i-1]]<c[st0[j+(1<<(i-1))][i-1]]) st0[j][i]=st0[j][i-1];
				else st0[j][i]=st0[j+(1<<(i-1))][i-1];
			if(b[st1[j][i-1]]<b[st1[j+(1<<(i-1))][i-1]]) st1[j][i]=st1[j][i-1];
				else st1[j][i]=st1[j+(1<<(i-1))][i-1];
		}
	solve(1,n<<1);
	for(int i=v[1].size()-1;i>=0;i--) printf("%d %d ",v[1][i].x,v[1][i].y);
	return 0;
}
```


---

## 作者：C　C　A (赞：1)

$$\huge\rm [ARC080C]Young~Maids$$

$$\large\text{——}~The~~Solution~~Written~~by~~CCA~\text{——}$$

---

$$\LARGE\mathcal{Description}$$

$\quad$给定一个长度为 $n$ 的排列 $P$ ，每次可以从 $P$ 中选取两个相邻的整数 $x,y$ ，将 $x,y$ 接在另一个初始为空的数列 $Q$ 的开头，要求经过 $\dfrac{n}{2}$ 次操作后，$Q$ 的字典序最小，求出这个字典序最小的 $Q$ 。

$\quad n\leqslant 2\times 10^5 ~\&~ n\equiv 0\pmod 2$

---

$$\LARGE\mathcal{Solution}$$

$\quad$考虑倒着取，每次取能取的数中最小的 。

$\quad$如果倒着取了 $x,y$ ，那么会将现在的序列分成三段，分别是 $[L,x-1],[x+1,y-1]和[y+1,R]$ ，且每一段都是一个子问题，这样就可以递归求解 。

$\quad$再考虑对于任意一个序列，能够取的位置有哪些，显然取完以后三个子区间的长度都必须为整数，于是 $x$ 的位置必须是奇数，$y$ 的位置必须是偶数 。

$\quad$于是就只需要维护一颗可以求静态区间最小值的线段树，以及一个维护四元组 $[L,R,x,y]$ 的优先队列，每次从堆中找到 $x$ 最小的序列，分成三段后再放回去即可 。

---

$$\LARGE\mathcal{Code}$$

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
const int INF = 0x7fffffff;

int n, p[N], id[N], q[N], a[N], cnt;

struct Node {
    int L, R, x, y;
    bool operator < (const Node &a) const {
        return p[a.x] < p[x];
}   };

priority_queue <Node> Q;

struct Segment_Tree {
    #define LS (p << 1)
    #define RS (p << 1 | 1)
    int Min[N << 2], l[N << 2], r[N << 2];
    void Build (int p, int L, int R) {
        l[p] = L, r[p] = R;
        if(L == R) { Min[p] = a[L]; return; }
        int mid = (L + R) >> 1;
        Build(LS, L, mid), Build(RS, mid + 1, R);
        Min[p] = min(Min[LS], Min[RS]);
    }
    int Query (int p, int L, int R) {
        if(l[p] >= L && r[p] <= R) return Min[p];
        int ans = INF;
        if(r[LS] >= L) ans = min(ans, Query(LS, L, R));
        if(l[RS] <= R) ans = min(ans, Query(RS, L, R));
        return ans;
    }
}T[2];

pair <int, int> Cut (int L, int R) {
    pair <int, int> Ans;
    Ans.first = id[T[L & 1].Query(1, L, R)];
    Ans.second = id[T[R & 1].Query(1, Ans.first + 1, R)];
    return Ans;
}

int main () {

    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
        scanf("%d", &p[i]), id[p[i]] = i;

    for(int i = 1; i <= n; i++) a[i] = i & 1 ? INF : p[i];
    T[0].Build(1, 1, n);
    for(int i = 1; i <= n; i++) a[i] = i & 1 ? p[i] : INF;
    T[1].Build(1, 1, n);
    
    pair <int, int> Sta = Cut(1, n);
    Q.push(Node{1, n, Sta.first, Sta.second});
    while(!Q.empty()) {
        Node u = Q.top(); Q.pop();
        q[++cnt] = p[u.x], q[++cnt] = p[u.y];
        if(u.L < u.x - 1) {
            pair <int, int> v = Cut(u.L, u.x - 1);
            Q.push(Node{u.L, u.x - 1, v.first, v.second});
        }
        if(u.x + 1 < u.y - 1) {
            pair <int, int> v = Cut(u.x + 1, u.y - 1);
            Q.push(Node{u.x + 1, u.y - 1, v.first, v.second});
        }
        if(u.y + 1 < u.R) {
            pair <int, int> v = Cut(u.y + 1, u.R);
            Q.push(Node{u.y + 1, u.R, v.first, v.second});
        }
    }

    for(int i = 1; i <= cnt; i++) printf("%d ", q[i]);

    return 0;
}
```


---

## 作者：happybob (赞：1)

一眼题吧。

你首先肯定要考虑倒着贪心，从后往前考虑每一个，必然是在当前区间中选择最优的两个，然后把区间劈成三个然后扔进优先队列里维护一下就好了。

查询区间最优显然是选择左端点和区间左端点奇偶性相同的最小位置，然后在后面选一个，直接用 ST 表维护就好了。

---

## 作者：Tjqq (赞：0)

提供思路简单，代码稍复杂的一个平衡树解法

原问题倒着做为一个字典序最小问题，于是只需要考虑每次删除两个合法的数并且字典序最小即可。删除数之后原序列会被分成 3 个不相交的区间（因为要保证能选这两个数等价于将它们之间的数提前删完）。不难发现删除这两个数合法的充要条件为删除这两个数后形成的区间长度均为偶数。于是可以考虑用两棵平衡树维护所有可以成为左端点的数和右端点的数。删除两个数等价于将两颗树这个区间内所有数交换，为了支持这个操作我使用了支持快速分裂合并的 fhq-treap，同时用一个 set 维护连续段辅助即可。具体细节见代码
```cpp
//created by fqr & cyx in 2024
#include <bits/stdc++.h>
#define IOS ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
#define ll long long
#define pb emplace_back
int ff,Ch;
template <typename T> inline void rd(T &x) {
    x=0,ff=1,Ch=getchar();
    while((Ch<'0'||Ch>'9') && Ch!='-') Ch=getchar();
    if(Ch=='-')Ch=getchar(),ff=-1;
    while(Ch>='0' && Ch<='9') {
        x=(x<<1)+(x<<3)+Ch-'0';
        Ch=getchar();
    }
    x*=ff;
}
template <typename T,typename ...Args> inline void rd(T &x,Args &...args) {
    rd(x), rd(args...);
}
using namespace std;
mt19937 rnd(time(0));
const int N=2e5+5;
int n,m;
int a[N];
int pos[N];
int ans[N][2];
struct node {
	int l,r;
	bool operator < (const node &rhs) const {
		return l<rhs.l || l==rhs.l && r<rhs.r;
	}
} ;
int idx;
int id[N],pro[N],sz[N];
int ch[N][2];
int rt[2];
int mn[N],w[N];
//rt[1] 维护所有在区间中和左端点距离为偶数(可以成为L)的mn
//rr[0] 奇数同理 
int New(int x) {
	sz[++idx]=1;
	id[idx]=x;
	mn[idx]=w[idx]=a[x];
	pro[x]=rnd();
	return idx;	
}
void push_up(int x) {
	sz[x]=sz[ch[x][0]]+sz[ch[x][1]];
	mn[x]=w[x];
	if(ch[x][0]) mn[x]=min(mn[x],mn[ch[x][0]]);
	if(ch[x][1]) mn[x]=min(mn[x],mn[ch[x][1]]);
}
void split(int x,int k,int &ls,int &rs) {
	if(!x) return ls=rs=0,void();
	if(id[x]<=k) {
		ls=x;
		split(ch[x][1],k,ch[x][1],rs);
	}
	else {
		rs=x;
		split(ch[x][0],k,ls,ch[x][0]);
	}
	push_up(x);
}
int merge(int x,int y) {
	if(!x || !y) return x|y;
	if(pro[x]<pro[y]) {
		ch[x][1]=merge(ch[x][1],y);
		return push_up(x),x;
	}
	else {
		ch[y][0]=merge(x,ch[y][0]);
		return push_up(y),y;
	}
}
void change(int root,int l,int r,int &r1,int &r2,int &r3) {
	split(root,r,r1,r2);
	split(r1,l-1,r1,r3);
}
void del(int &root,int pos) {
	int r1,r2,r3;
	split(root,pos,r1,r2);
	split(r1,pos-1,r1,r3);
	root=merge(r1,r2);
}
int ask(int &root,int l,int r) {
	int r1,r2,r3;
	change(root,l,r,r1,r2,r3);
	int ans=mn[r3];
	root=merge(merge(r1,r3),r2);
	return ans;
}
void debug(int x) {
	if(!x) return ;
	debug(ch[x][0]);
	printf("%d ",w[x]);
	debug(ch[x][1]);
}
void print() {
	puts("Treap");
	debug(rt[0]);
	puts("");
	debug(rt[1]);
	puts("");		
	puts("range set");
}
signed main() {
#ifdef LOCAL
	freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);
#endif
    rd(n);
    m=n>>1;
    for(int i=1; i<=n; i++)
    	rd(a[i]),pos[a[i]]=i;
    set<node> s;
	s.emplace(node{1,n});
    for(int i=1; i<=n; i+=2) {
    	rt[0]=merge(rt[0],New(i));
    	rt[1]=merge(rt[1],New(i+1));
	}
//	debug(rt[0]);
//	puts("");
//	debug(rt[1]);
//	puts("");
	for(int i=1,l0,r0,m0,l1,r1,m1; i<=m; i++) {
    	int lval=mn[rt[0]];
    	int lp=pos[lval];
    	auto it=s.lower_bound(node{lp,n+1});
    	it--;
		int L=it->l,R=it->r;
		int rval=ask(rt[1],lp+1,R);
		int rp=pos[rval];
//		cout<<"range "<<L<<' '<<R<<'\n';
//		cout<<"query "<<lval<<' '<<rval<<'\n';
		s.erase(it);
		if(lp!=L) s.emplace(node{L,lp-1});
		if(rp!=R) s.emplace(node{rp+1,R});
		if(lp+1!=rp) s.emplace(node{lp+1,rp-1});
		ans[i][0]=lval,ans[i][1]=rval;
		del(rt[0],lp),del(rt[1],rp);
//		print();
		change(rt[0],lp,rp,l0,r0,m0);
		change(rt[1],lp,rp,l1,r1,m1);
		rt[0]=merge(merge(l0,m1),r0);
		rt[1]=merge(merge(l1,m0),r1);
//		print();
//		for(auto it:s)
//			cout<<it.l<<' '<<it.r<<'\n';
//		return 0;
	}
	for(int i=1; i<=m; i++)
		printf("%d %d ",ans[i][0],ans[i][1]);
	return 0;
}
/*
8
4 6 3 2 8 5 7 1

4,6,3,2,8,5,7,1
4,6 2,8,5,7

1,2,3,4,5,6,7,8,9,10
1,2 4,5,6,7 9,10
*/

```

---

