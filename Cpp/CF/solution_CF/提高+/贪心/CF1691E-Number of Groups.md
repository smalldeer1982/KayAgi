# Number of Groups

## 题目描述

You are given $ n $ colored segments on the number line. Each segment is either colored red or blue. The $ i $ -th segment can be represented by a tuple $ (c_i, l_i, r_i) $ . The segment contains all the points in the range $ [l_i, r_i] $ , inclusive, and its color denoted by $ c_i $ :

- if $ c_i = 0 $ , it is a red segment;
- if $ c_i = 1 $ , it is a blue segment.

We say that two segments of different colors are connected, if they share at least one common point. Two segments belong to the same group, if they are either connected directly, or through a sequence of directly connected segments. Find the number of groups of segments.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1691E/82e599b6f05721e46a21456ef572639590d4dbf3.png)

## 说明/提示

In the first example there are $ 5 $ segments. The segments $ 1 $ and $ 2 $ are connected, because they are of different colors and share a point. Also, the segments $ 2 $ and $ 3 $ are connected, and so are segments $ 4 $ and $ 5 $ . Thus, there are two groups: one containing segments $ \{1, 2, 3\} $ , and the other one containing segments $ \{4, 5\} $ .

## 样例 #1

### 输入

```
2
5
0 0 5
1 2 12
0 4 7
1 9 16
0 13 19
3
1 0 1
1 1 2
0 3 4```

### 输出

```
2
3```

# 题解

## 作者：CruiseY (赞：9)

# 题目大意
给一些黑色白色的线段，若两个线段颜色不同且相交则连一条边，询问最终一共有多少个连通块？

# 解决方案
介绍一种不用线段树且特别好写的做法，考虑将两种颜色分开考虑（为了方便画图，将线段改为红色和蓝色），假设现在线段上只有蓝色的线段。

现在加入了一条红色线段。发现该线段实际上是将 $1$，$2$，$3$ 合并到了一个集合中。(自己也加入该集合)
![](https://cdn.luogu.com.cn/upload/image_hosting/y23pxqj4.png)

那可以考虑为，每次加入一个红色线段，都将跟它有交的蓝色线段合并起来即可。

对于一个 $[l_{i},r_{i}]$ 的区间与 $[l_{j},r_{j}]$ 的区间有交需要满足的条件：

 $l_{i}\le r_{j}$  且  $r_{i} \ge l_{j}$ 

所以对于蓝色线段按照左端点排序，红色线段按右端点排序。

考虑到某条红色线段，则将所有左端点小于该红色线段右端点的值都加入进去。

此时只需要考虑加入的蓝色线段的右端点，是否大于该红色线段的左端点即可。

可以用一个优先队列维护加入的蓝色线段的右端点。在一条红色线段合并了几个蓝色线段后，再将最大的右端点入进去，来代替被合并的这几个蓝色线段。（拿最大的代替，是因为可以想象成将这些蓝色线段合成了一个，此线段的右端点就是最大的右端点）。 

小细节：如果该红线没有合并任何蓝线，那么它自己就是一个新的连通块。

# 代码实现
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll read() {
    ll x = 0, f = 1; char ch = getchar();
    while(ch < '0' || ch > '9') {if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9') {x = (x << 3) + (x << 1) + (ch ^ 48); ch = getchar();}
    return x * f;
}

struct node {int l, r;}p[1000010], q[1000010];
ll tip0, tip1, tip, ans, n;
priority_queue<int> qe;

int main() {
    for(int T = read(); T; T--) {
        n = read(); tip1 = tip0 = ans = 0; tip = 1;
        for(int i = 1; i <= n; i++) {
            int opt = read(), l = read(), r = read();
            if(opt) p[++tip1] = {l, r}, ans++;
            else q[++tip0] = {l, r};
        }
        sort(p + 1, p + 1 + tip1, [](node a, node b) {return a.l < b.l;});
        sort(q + 1, q + 1 + tip0, [](node a, node b) {return a.r < b.r;});
        for(int i = 1; i <= tip0; i++) {
            while(tip <= tip1 && p[tip].l <= q[i].r) qe.push(p[tip++].r);
            if(!qe.empty() && q[i].l <= qe.top()) {
                int w = qe.top(); qe.pop();
                while(!qe.empty() && q[i].l <= qe.top()) ans--, qe.pop();
                qe.push(w);
            }
            else ans++;//若没有合并任何蓝线
        }
        while(!qe.empty()) qe.pop(); printf("%lld\n", ans);
    }
    return 0;
}
```


---

## 作者：elbissoPtImaerD (赞：6)

不需要 $\log$ 数据结构的做法。

考虑加入这个区间 $[l,r]$ 后会将哪些区间合并。维护前面的异色线段然后暴力扫一遍是平方的。

考虑优化，由于此区间对一个连通块至多只需连一条边，所以使用并查集维护连通块，若将所有区间按右端点升序排序，则一个连通块的代表元只需要取右端点最右的那个即可。

而且排序后的序列有单调性，能连边的一定是一段后缀，所以对每个颜色维护一个单调栈状物即可。

这样均摊下来只有并查集的复杂度，是 $O(n\alpha(n))$ 的。

```cpp
il void Solve()
{
  int n;cin>>n;
  ve<tuple<int,int,int>>e(n);
  for(auto&[o,l,r]:e) cin>>o>>l>>r;
  DSU S(n);
  int ans=n;
  ve<int>q[2];
  sort(all(e),[&](auto x,auto y){return get<2>(x)<get<2>(y);});
  for(int _=0;_<n;++_) {
    auto[o,l,r]=e[_];
    for(int lst=-1;;) {
      if(!q[o].size()) {
        if(~lst) q[o].pb(lst);
        break;
      }
      int i=q[o].back();
      if(l<=get<2>(e[i])) {
        ans-=S.Merge(i,_);
        if(!~lst) lst=i;
        q[o].pop_back();
      }
      else {
        if(~lst) q[o].pb(lst);
        break;
      }
    }
    q[o^1].pb(_);
  }
  cout<<ans<<'\n';
  return;
}
```

[$\color{green}{\checkmark}$](https://codeforces.com/contest/1691/submission/262212735)

---

## 作者：jianhe (赞：4)

一眼题。

看到“连通块个数”想到 **并查集**，看到“线段有公共点”想到 **将线段按右端点排序**。

继续想，挖掘连通块的性质。容易想到连通块间各点只需要与其他点连一条边就能保证连通。因此我们并不需要暴力连边。

于是我们维护两个单调栈（两种不同颜色），枚举每条边，若它和栈顶有交，则弹出栈顶并记录答案。之后把这条边加入栈顶。

需要注意的是，在弹栈并结束循环后，还要把原先栈顶元素（已弹栈）塞回栈顶。由此保证这条边能构成正确的连通块（即防止有线段与之前的线段有交，但那条线段所在连通块的元素均已经弹栈，无法记录答案）。

于是就做完了。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=1e5+10; 
ll T,n,ans,l0[N],r0[N],x0[N],l1[N],r1[N],x1[N],ct0,ct1,fa[N];
struct P{
	bool col;
	ll l,r;
	bool operator<(const P& b){return r<b.r;}
}a[N];
ll getfa(ll x){return fa[x]==x?x:fa[x]=getfa(fa[x]);}
void hb(ll x,ll y){
	x=getfa(x),y=getfa(y);
	if(x^y) fa[x]=y,ans--;
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i].col>>a[i].l>>a[i].r;
		sort(a+1,a+n+1);ct0=ct1=0,ans=n;
		for(int i=1;i<=n;i++) fa[i]=i;
		for(int i=1,j;i<=n;i++){
			if(a[i].col){
				j=ct0;
				while(j&&((l0[j]<=a[i].l&&a[i].l<=r0[j])||(a[i].l<=l0[j]&&a[i].r>=l0[j]))) hb(x0[j],i),j--;
				if(ct0) l0[++j]=l0[ct0],r0[j]=r0[ct0],x0[j]=x0[ct0],ct0=j;
				l1[++ct1]=a[i].l,r1[ct1]=a[i].r,x1[ct1]=i;
			}else{
				j=ct1;
				while(j&&((l1[j]<=a[i].l&&a[i].l<=r1[j])||(a[i].l<=l1[j]&&a[i].r>=l1[j]))) hb(x1[j],i),j--;
				if(ct1) l1[++j]=l1[ct1],r1[j]=r1[ct1],x1[j]=x1[ct1],ct1=j;
				l0[++ct0]=a[i].l,r0[ct0]=a[i].r,x0[ct0]=i;
			}
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

最后祝大家 CSP rp++！

---

## 作者：zztqwq (赞：3)

首先把区间改成 $[l,r)$ 的形式然后离散化。

考虑每个点，如果这个点上全都是一个颜色，那么这个点是寄掉的，反之覆盖到这个点的线段就全都连通了。

我们把第二种点称作关键点，把它们单独拎出来排个序。每个线段能覆盖到的关键点是个区间，把这些区间求出来，求个并然后算连通块数量即可，这个东西按照左端点排个序就能求。

$\mathcal O(n\log n)$。

```cpp

const int N=2e5+10;
struct seg{
	int l,r;
}a[N],b[N];
bool cmp(seg x,seg y){return x.l<y.l;}
int c[N],pos[N];
int t[N];
pii x[N];
void sol()
{
	int n=read(),m=0;
	for(int i=1;i<=n;i++)
	{
		c[i]=read();
		a[i].l=read(),a[i].r=read()+1;//[l,r)
		t[++m]=a[i].l,t[++m]=a[i].r;
	}
	sort(t+1,t+m+1),m=unique(t+1,t+m+1)-t-1;
	for(int i=1;i<=n;i++)a[i].l=lower_bound(t+1,t+m+1,a[i].l)-t,a[i].r=lower_bound(t+1,t+m+1,a[i].r)-t;
//	for(int i=1;i<=n;i++)printf("c=%d, [%d, %d)\n",c[i],a[i].l,a[i].r);
	for(int i=1;i<=n;i++)x[i*2-1]=mp(a[i].l,c[i]<<1),x[i*2]=mp(a[i].r,c[i]<<1|1);//0:add, 1:del
	sort(x+1,x+2*n+1);int c0=0,c1=0,cnt=0;
	for(int i=1;i<=n*2;i++)
	{
		int c=x[i].se>>1,tp=x[i].se&1;
		if(c==0&&tp==0)c0++;
		else if(c==0&&tp==1)c0--;
		else if(c==1&&tp==0)c1++;
		else if(c==1&&tp==1)c1--;
		if(i==n*2||x[i].fi!=x[i+1].fi){if(c0&&c1)pos[++cnt]=x[i].fi;}
	}
	for(int i=1;i<=n;i++)
		b[i].l=lower_bound(pos+1,pos+cnt+1,a[i].l)-pos,b[i].r=lower_bound(pos+1,pos+cnt+1,a[i].r)-pos-1;//[l,r]
	sort(b+1,b+n+1,cmp);
	int ans=0;
//	for(int i=1;i<=n;i++)printf("[%d, %d]\n",b[i].l,b[i].r);
	for(int i=1,r=-1;i<=n;i++)
	{
		if(b[i].l>b[i].r)ans++;
		else if(r<b[i].l)ans++,r=b[i].r;
		else r=max(r,b[i].r);
//		printf("i=%d, r=%d\n",i,r);
	}
	printf("%d\n",ans);
}
int main()
{
	int T=read();
	while(T--)sol();
	return 0;
}
```

---

## 作者：violin_wyl (赞：3)

# Number of Groups

## 解析：

### 题目大意：

数轴上有 $n$ 个线段，每段的颜色为红色或蓝色。第 $i$ 段的颜色为 $c_i$ （如果 $c_i=0$ 则为红色段，如果 $c_i=1$ 则为蓝色段），该段包含的点的范围为 $[l_i,r_i]$ 。

如果两个**不同颜色**的段相交（有至少共享一个公共点），则认为它们是连接的。如果两个颜色段直接连接或通过一系列直接连接的段连接，则它们属于同一组。请你查找颜色段的组数。

- ($1 \leq n \leq 10^5 $)
- ($0 \leq c_i \leq 1, 0 \leq l_i \leq r_i \leq 10^9$)

--------------------------

### 思路：

线段树乱搞。

我们考虑枚举颜色（其实就两个），考虑这个颜色的所有线段分别跟谁相连，如果我们能维护这个东西并用并查集合并，就可以统计答案。

我们考虑先对另一个颜色 $y$ 按 $r$ 从小到大排序，我们枚举这个颜色 $x$ 的所有线段，因为 $y$ 的坐标有序，如果当前线段 $i$ 想要和颜色 $y$ 的线段相连，那么当且仅当 $r_j\in[l_i,r_i]$，这样的 $r_j$ 一定是下标上连续的一段，我们考虑对颜色 $y$ 建一棵线段树，在每个节点上开一个 `vector` 维护覆盖了当前区间上表示的所有线段的颜色 $x$ 的集合，考虑标记永久化思想，由于每个 $i$ 只会对应一个区间，而每个区间最多会被分成 $\log n$ 个小区间，这样所有标记的总和不会超过 $n \log n$，复杂度是正确的。

现在所有线段对应的区间都已经标记完成，我们先考虑颜色 $y$ 的线段如果用并查集和 $x$ 连接，由于我们是对颜色 $y$ 的坐标开的线段树，所有对于每个线段只需要和他上面 $\log$ 个区间中的任意一个标记合并即可，为了方便我们钦定选择线段树从上往下第一个出现的标记为合并对象。

我们考虑对于标记如何合并，因为他们有共同可以连接的颜色 $y$ 的线段，所以同属一个集合，我们也是对于每个标记合并这个区间上面 $\log$ 个区间中第一个出现的标记，这样就把所有线段连接起来了。

这样合并有一个漏洞，就是如果枚举的线段被某个线段完全包含（即 $l_j<l_i\leq r_i<r_j$），这样不管对 $l$ 排序还是对 $r$ 排序都不能被判定与 $i$ 相连，解决办法是枚举 $j$ 重新做一遍上述流程，也就是交换 $x,y$。

复杂度是 $\mathcal O(n\log n+n\log^2n)$，但常数很小，并且存在单 $\log$ 做法。

----------------------------------------------------

## code：

```c++
#include <bits/stdc++.h>
#define eb emplace_back
#define lob lower_bound
#define upb upper_bound
using namespace std;
const int N = 1e5 + 10;
typedef pair <int, int> pii;
inline int read ()
{
    int x = 0, f = 1;
    char ch = getchar ();
    while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar (); }
    while (ch >= '0' && ch <= '9') { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar (); }
    return x * f;
}
int n;
struct Line {
    int l, r, id;
    Line () { }
    Line (int _l, int _r, int _id) { l = _l; r = _r; id = _id; }
    bool operator < (const Line &A) const {
        return r < A.r;
    }
} line[2][N];
bool cmp (Line x, Line y) { return x.r == y.r ? x.l < y.l : x.r < y.r; }
int cnt[2];
struct DSU {
    int fa[N];
    void init () { for (int i = 1; i <= n; i++) fa[i] = i; }
    inline int find (int x) { return x == fa[x] ? x : fa[x] = find (fa[x]); }
    void merge (int x, int y)
    {
        int fx = find (x), fy = find (y);
        if (fx != fy) fa[fx] = fy;
    }
}d;
struct Seg_tree {
    #define lson rt << 1
    #define rson rt << 1 | 1
    struct seg_tree {
        vector <int> vec;
        #define vec(rt, i) tree[rt].vec[i]
    } tree[N << 2];
    void build (int rt, int l, int r)
    {
        if(tree[rt].vec.size ()) tree[rt].vec.clear ();
        if (l == r) return ;
        int mid = (l + r) >> 1;
        build (lson, l, mid);
        build (rson, mid + 1, r);
    }
    void modify (int rt, int l, int r, int L, int R, int id)
    {
        if (L <= l && r <= R)
        {
            tree[rt].vec.eb (id);
            return ;
        }
        int mid = (l + r) >> 1;
        if (L <= mid) modify (lson, l, mid, L, R, id);
        if (R > mid) modify (rson, mid + 1, r, L, R, id);
    }
    void merge (int rt, int l, int r, int id, int x, int y)
    {
        if (!id && tree[rt].vec.size ()) id = vec(rt, 0);
        if (id) for (int i = 0; i < tree[rt].vec.size (); i++) d.merge (id, vec(rt, i));
        if (l == r)
        {
            if (id) d.merge (line[y][l].id, id);
            return ;
        }
        int mid = (l + r) >> 1;
        merge (lson, l, mid, id, x, y);
        merge (rson, mid + 1, r, id, x, y);
    }
} T;
void merge (int x, int y)
{
    T.build (1, 1, cnt[y]);
    for (int i = 1; i <= cnt[x]; i++)
    {
        if (line[x][i].r < line[y][1].r || line[x][i].l > line[y][cnt[y]].r) continue;
        int l = lob (line[y] + 1, line[y] + cnt[y] + 1, (Line) {0, line[x][i].l, 0}) - line[y];
        int r = upb (line[y] + 1, line[y] + cnt[y] + 1, (Line) {0, line[x][i].r, 0}) - line[y] - 1;
        if (line[x][i].r >= line[y][cnt[y]].r) r = cnt[y];
        if (l > r) continue;
        T.modify (1, 1, cnt[y], l, r, line[x][i].id);
    }
    T.merge (1, 1, cnt[y], 0, x, y);
}
void solve ()
{
    cnt[0] = cnt[1] = 0;
    n = read ();
    for (int i = 1; i <= n; i++)
    {
        int c = read (), l = read (), r = read ();
        line[c][++cnt[c]] = Line(l, r, i);
    }
    if (!cnt[0] || !cnt[1]) { printf("%d\n", n); return ; }
    d.init ();
    sort (line[1] + 1, line[1] + cnt[1] + 1, cmp);
    merge (0, 1);
    sort (line[0] + 1, line[0] + cnt[0] + 1, cmp);
    merge (1, 0);
    int ans = 0;
    for (int i = 1; i <= n; i++) ans += (d.fa[i] == i);
    printf ("%d\n", ans);
}
signed main()
{
    int t = read ();
    while (t--) solve ();
    return 0;
}
```


---

## 作者：RyexAwl (赞：3)

### 做法 1：boruvka + 线段树

考虑建出生成森林然后统计生成森林中连通块的个数。使用类似 boruvka 的思想。算法每一轮对于每个连通块找到是否存在一条和其他连通块之间的边。这部分可以使用线段树优化。注意一定要正着找一遍倒着找一遍，因为对于一个连通块而言有可能向前找找不到边向后找能找到边而这条边没被枚举导致每轮连通块个数不能减半。复杂度 $O(n\log ^2n)$。

[代码](https://codeforces.com/contest/1691/submission/159139562)

### 做法2：拆事件 + 贪心

考虑一种朴素的连边算法。对于两条有边的线段 $[l_1,r_1],[l_2,r_2]$，如果 $l_1<l_2$，那么一定有 $l_2\in [l_1,r_1]$。即线段 $[l_1,r_1]$ “覆盖”了点 $l_2$，考虑在处理 $[l_2,r_2]$ 时处理这条边。考虑将一条线段 $[l,r]$ 拆成两个在时刻 $l$ 和 $r$ 的事件按时间维扫描线。在扫到左端点时加入一条线段扫到右端点时删掉一条线段。对于点 $k$，将左端点在 $[1,l]$ 范围内的线段都加入后还未删的线段即覆盖点 $k$ 的线段。

那么这里不难想到一个暴力做法：


* 将所有线段拆成两个事件（加入和删除）排序，每个时刻只处理一个事件。开两个集合表示两种颜色线段已经加入但未删除的线段。

* 对于两条相交的线段 $[l_1,r_1]$，$[l_2,r_2]$ 在加入后加入的线段时连边。

* 加入一条线段时扫与该线段颜色相异的集合向集合内的所有线段连边。

令 $f_i$ 表示加入左端点在 $[1,l_i]$ 的线段后有多少条颜色与 $i$ 相异的线段还未被删。暴力算法的复杂度即 $O(\sum f_i)=O(n^2)$。

这里有一个贪心策略：在加入一条线段连边后只保留另一个颜色集合中右端点最大的线段不影响连通性。

考虑对于钦定颜色的线段 $p_1,p_2,...,p_k$ 计算 $\sum f_i$，因为处理完一条线段后 $f$ 变成 $1$。所以 $\sum f_i=O(n)$。

用 set 维护线段集合，复杂度 $O(n\log n)$。

[代码](https://codeforces.com/contest/1691/submission/159156663)



---

## 作者：王熙文 (赞：0)

提供一个无脑且在无脑做法中比较好写的做法。

## 思路

两个区间 $[l_1,r_1],[l_2,r_2]$ 有交集等价于 $l_1 \le r_2\land r_1 \ge l_2$。因此考虑 cdq 分治优化建图。

在 cdq 分治过程中，我们需要将一个点与一段前缀连边。因为边是无向边，所以这一段前缀也是连通的。所以可以在动态更新前缀的过程中将相邻的区间连边，最后在将点与前缀连边。维护连通性可以使用并查集。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
struct CDQ { int op,l,r,id; } c[100010];
bool cmp1(CDQ x,CDQ y)
{
	int xx=(x.op==0?x.l:x.r),yy=(y.op==0?y.l:y.r);
	return xx==yy?x.op<y.op:xx<yy;
}
bool cmp2(CDQ x,CDQ y)
{
	int xx=(x.op==0?x.r:x.l),yy=(y.op==0?y.r:y.l);
	return xx>yy;
}
int fa[100010];
int find(int x)
{
	while(x!=fa[x]) x=fa[x]=fa[fa[x]];
	return x;
}
void cdq(int l,int r)
{
	if(l==r) return;
	int mid=l+r>>1;
	cdq(l,mid),cdq(mid+1,r);
	int lst=r;
	while(lst>=mid+1 && c[lst].op==0) --lst;
	int wz=l,lstwz=0;
	for(int i=mid+1; i<=lst; ++i)
	{
		while(wz<=mid && (c[wz].op==0?c[wz].r:c[wz].l)>=(c[i].op==0?c[i].r:c[i].l))
		{
			if(c[wz].op==0)
			{
				if(lstwz!=0) fa[find(lstwz)]=find(c[wz].id);
				lstwz=c[wz].id;
			}
			++wz;
		}
		if(c[i].op==1 && lstwz!=0) fa[find(c[i].id)]=find(lstwz);
	}
	inplace_merge(c+l,c+mid+1,c+r+1,cmp2);
}
int main()
{
	int t; cin>>t; while(t--)
	{
		cin>>n;
		for(int i=1; i<=n; ++i)
		{
			cin>>c[i].op>>c[i].l>>c[i].r;
			c[i].id=i;
		}
		for(int i=1; i<=n; ++i) fa[i]=i;
		sort(c+1,c+n+1,cmp1),cdq(1,n);
		int ans=0;
		for(int i=1; i<=n; ++i) ans+=(fa[i]==i);
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

