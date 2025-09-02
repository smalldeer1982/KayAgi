# Sign on Fence

## 题目描述

Bizon the Champion has recently finished painting his wood fence. The fence consists of a sequence of $ n $ panels of $ 1 $ meter width and of arbitrary height. The $ i $ -th panel's height is $ h_{i} $ meters. The adjacent planks follow without a gap between them.

After Bizon painted the fence he decided to put a "for sale" sign on it. The sign will be drawn on a rectangular piece of paper and placed on the fence so that the sides of the sign are parallel to the fence panels and are also aligned with the edges of some panels. Bizon the Champion introduced the following constraints for the sign position:

1. The width of the sign should be exactly $ w $ meters.
2. The sign must fit into the segment of the fence from the $ l $ -th to the $ r $ -th panels, inclusive (also, it can't exceed the fence's bound in vertical direction).

The sign will be really pretty, So Bizon the Champion wants the sign's height to be as large as possible.

You are given the description of the fence and several queries for placing sign. For each query print the maximum possible height of the sign that can be placed on the corresponding segment of the fence with the given fixed width of the sign.


## 说明/提示

The fence described in the sample looks as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF484E/6257a310d2207c0e1a05992058b31d44d0ead77b.png)The possible positions for the signs for all queries are given below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF484E/4bfca5e8ee81f8d76187af1e0be6e7c7b6bf35e2.png) The optimal position of the sign for the first query.  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF484E/f28ed7253a1a74cdc9e367c2f43ac177854f54b6.png) The optimal position of the sign for the second query.  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF484E/5dde0308a1ff26588bc67b02973df5bc0c317178.png) The optimal position of the sign for the third query.

## 样例 #1

### 输入

```
5
1 2 2 3 3
3
2 5 3
2 5 2
1 5 5
```

### 输出

```
2
3
1
```

# 题解

## 作者：Elegia (赞：34)

这题可以做到一个 $\log$。

首先把区间最值这个东西画成一张表的话，即 $a_{l,r}= \min_{l\le i \le r} h_i$，这是一张直角三角形的表格，它的取值其实是比较清楚的，由笛卡尔树较好刻画，假设这个序列的最大值在 $u$ 这个位置，那么对于 $(l, r) \in (1, u) \times (u, n)$ 的区域取值都为 $h_u$，剩余的两个子三角形是笛卡尔树左右子管辖的，一直下去。那么就是说这个三角形每个位置恰好被一个矩形覆盖，而我们要查询的是满足 $r - l = k - 1$ 的这样一条斜线上的格子中一段的值的 $\max$。

接下来要做的事情就是把这个坐标系旋转一下，如果查询能够是一个横着的线段那会处理起来容易一些。我们把坐标系变换为 $(l, k)$ 表示左端点以及长度。这样我们就是在 $([l, r-k+1], k)$ 这条线上查询最值。考虑原来的矩形现在变成了什么：现在是一个平行四边形，一对边是竖直向下的，另一对是向东南 $45^\circ$ 的。那么这个东西我们将其横着切 2 刀，就会分成上下两个直角三角形（直角边和坐标轴垂直）和中间的平行四边形，如果这个直角三角形的两个锐角端点的 $2\Delta x \le \Delta y$ 那么说明比较长，中间是一个和坐标轴方向贴着的矩形，否则是一个横着的平行四边形。对于前三种图形，我们可以先将其中的值标记在其中一条竖直边对应的坐标上，那么查询的时候直接查询对应的区间，顶多再算上有一个和我们区间一边有重合的，用平衡树可以找到。对于最后那种平行四边形，可以再斜切一下坐标系，这样就转换为了矩形。

综上，通过维护几种比较简单结构的图形的扫描线，可以在 $\Theta((n+m)\log n)$ 的时间内处理所有询问。

```cpp
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <cctype>

#include <algorithm>
#include <random>
#include <bitset>
#include <queue>
#include <functional>
#include <set>
#include <map>
#include <vector>
#include <iostream>
#include <limits>
#include <numeric>

#define MP make_pair

using namespace std;

typedef priority_queue<int> PQ;

#ifdef LBT

const int N = 100;

#else

const int N = 100010;

#endif

struct Node {
  int l, r, v;
  Node *ls, *rs;

  void*operator new(size_t) {
    static Node pool[N * 4];
    static Node* ptop = pool;
    return ptop++;
  }

  void upd() {
    v = max(ls->v, rs->v);
  }

  void ch(int k, int x) {
    if (l == r) {
      v = x;
      return;
    }
    (k <= ls->r ? ls : rs)->ch(k, x);
    upd();
  }

  int qry(int l, int r) const {
    if (this->l == l && this->r == r)
      return v;
    if (r <= ls->r)
      return ls->qry(l, r);
    if (l >= rs->l)
      return rs->qry(l, r);
    return max(ls->qry(l, ls->r), rs->qry(rs->l, r));
  }
};

Node* build(int l, int r) {
  Node* p = new Node;
  p->l = l;
  p->r = r;
  if (l == r)
    return p;
  int mid = (l + r) >> 1;
  p->ls = build(l, mid);
  p->rs = build(mid + 1, r);
  return p;
}

int n, m, cnt;
int a[N], ans[N], stk[N], cl[N], cr[N], cc[N];
vector<pair<int, pair<int, int>> > qry[N], sch1[N], sch2[N], sch3[N], sch4[N];
map<int, pair<int, int> > seg1, seg2, seg3, seg4; // ^ - \ V
priority_queue<int> q1[N], q2[N], dq1[N], dq2[N];
Node *sgt1, *sgt2;

int qtop(const PQ& pq) {
  return pq.empty() ? 0 : pq.top();
}

void ins(PQ* q, PQ* dq, Node* sgt, int k, int x) {
  if (x > qtop(q[k])) {
    sgt->ch(k, x);
  }
  q[k].push(x);
}

void ers(PQ* q, PQ* dq, Node* sgt, int k, int x) {
  dq[k].push(x);
  bool f = false;
  while (!dq[k].empty() && q[k].top() == dq[k].top()) {
    q[k].pop();
    dq[k].pop();
    f = true;
  }
  if (f)
    sgt->ch(k, qtop(q[k]));
}

void dis(PQ* q, PQ* dq, Node* sgt, int k, int x) {
  if (x < 0)
    ers(q, dq, sgt, k, -x);
  else
    ins(q, dq, sgt, k, x);
}

int main() {

  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &a[i]);
  scanf("%d", &m);
  for (int i = 1; i <= m; ++i) {
    int l, r, k;
    scanf("%d%d%d", &l, &r, &k);
    qry[k].push_back(MP(i, MP(l, r - k + 1)));
  }
  for (int i = 1; i <= n; ++i) {
    int cur = 1;
    cl[i] = i;
    while (cnt && a[stk[cnt - 1]] >= a[i]) {
      --cnt;
      cl[i] -= cc[cnt];
      cur += cc[cnt];
      cr[stk[cnt]] = i - 1;
    }
    cc[cnt] = cur;
    stk[cnt++] = i;
  }
  while (cnt)
    cr[stk[--cnt]] = n;
  for (int i = 1; i <= n; ++i) {
    int x1 = i, y1 = 1, x2 = cl[i], y2 = cr[i] - cl[i] + 1;
    sch1[y2 + 1].push_back(MP(-a[i], MP(x2, y2)));
    sch4[y1].push_back(MP(a[i], MP(x1, y1)));
    int d;
    if ((x1 - x2) * 2 <= (y2 - y1)) {
      d = x1 - x2;
      if (y1 + d + 1 < y2 - d) {
        sch2[y1 + d + 1].push_back(MP(a[i], MP(x2, x1)));
        sch2[y2 - d].push_back(MP(-a[i], MP(x2, x1)));
        //if (i == 3)
        //  LOG("[%d %d] * [%d %d]\n", x2, x1, y1 + d + 1, y2 - d - 1);
      }
    } else {
      //LOG("HELLO %d\n", a[i]);
      d = y2 - y1 - (x1 - x2);
      //LOG("%d %d %d %d => %d\n", x1, y1, x2, y2, d);
      if (y1 + d + 1 < y2 - d) {
        sch3[y1 + d + 1].push_back(MP(a[i], MP(x1, x1 + d)));
        sch3[y2 - d].push_back(MP(-a[i], MP(x1, x1 + d)));
      }
    }
    sch1[y2 - d].push_back(MP(a[i], MP(x2, y2)));
    sch4[y1 + d + 1].push_back(MP(-a[i], MP(x1, y1)));
  }
  sgt1 = build(1, n);
  sgt2 = build(1, n);
  for (int k = 1; k <= n; ++k) {
/*#define SRT(X) sort(sch##X[k].begin(), sch##X[k].end(), greater<pair<int, pair<int, int> > >())
    SRT(1);
    SRT(2);
    SRT(3);
    SRT(4);*/
    for (const auto& pr : sch1[k]) {
      dis(q1, dq1, sgt1, pr.second.first, pr.first);
      if (pr.first < 0)
        seg1.erase(pr.second.first);
      else
        seg1.insert(MP(pr.second.first, MP(pr.second.second, pr.first)));
    }
    for (const auto& pr : sch2[k]) {
      dis(q1, dq1, sgt1, pr.second.first, pr.first);
      if (pr.first < 0) {
        seg2.erase(pr.second.first);
      } else {
        seg2.insert(MP(pr.second.first, MP(pr.second.second, pr.first)));
        //LOG("INS %d %d %d\n", pr.second.first, pr.second.second, pr.first);
      }
    }
    for (const auto& pr : sch3[k]) {
      dis(q2, dq2, sgt2, pr.second.second, pr.first);
      if (pr.first < 0)
        seg3.erase(pr.second.second);
      else
        seg3.insert(MP(pr.second.second, MP(pr.second.first, pr.first)));
    }
    for (const auto& pr : sch4[k]) {
      dis(q1, dq1, sgt1, pr.second.first, pr.first);
      if (pr.first < 0)
        seg4.erase(pr.second.first);
      else {
        seg4.insert(MP(pr.second.first, MP(1, pr.first)));
      }
    }

    for (const auto& pr : qry[k]) {
      int l = pr.second.first, r = pr.second.second;
      int id = pr.first;
      ans[id] = max(sgt1->qry(l, r), sgt2->qry(l + k - 1, r + k - 1));
      map<int, pair<int, int> >::iterator it;
      it = seg1.lower_bound(l);
      if (it != seg1.begin()) {
        int ll = (--it)->first;
        int rr = ll + (it->second.first - k);
        //LOG("%d FND %d %d\n", id, ll, rr);
        if (rr >= l)
          ans[id] = max(ans[id], it->second.second);
      }
      it = seg2.lower_bound(l);
      if (it != seg2.begin()) {
        int rr = (--it)->second.first;
        if (rr >= l)
          ans[id] = max(ans[id], it->second.second);
      }
      it = seg3.upper_bound(r + k - 1);
      if (it != seg3.end()) {
        int ll = it->second.first;
        if (ll <= r + k - 1)
          ans[id] = max(ans[id], it->second.second);
      }
      it = seg4.upper_bound(r);
      if (it != seg4.end()) {
        int rr = it->first;
        int ll = rr - (k - 1);
        //LOG("%d FND %d %d\n", id, ll, rr);
        if (ll <= r)
          ans[id] = max(ans[id], it->second.second);
      }
    }
  }

  for (int i = 1; i <= m; ++i)
    printf("%d\n", ans[i]);

  return 0;
}
```

---

## 作者：Weng_Weijie (赞：15)

题解：

这题和[国家集训队]middle很像

考虑二分答案

问题变成判断是否存在一段大于等于mid且长度不少于k的子区间

将大于等于mid设为1,小于mid设为0,就是查询区间最长全1区间是否超过k

这个东西可以通过维护前后缀最长全1区间，就支持区间加法了

由于每次二分的mid都不同，于是可以用主席树维护每个mid时的线段树

然后就做完了

代码：
```cpp
#include <cstdio>
#include <algorithm>
#define N 100005 
int root[N], rk[N], a[N], v[N];
struct data {
    int len, lx, rx, max;
    data() { len = lx = rx = max = 0; }
    data(int x) { len = 1, lx = rx = max = x; }
    data(int x, int y, int z, int w) { len = x, lx = y, rx = z, max = w; }
    data operator + (data rhs) const {
        return (data) {
            len + rhs.len,
            lx == len ? lx + rhs.lx : lx,
            rhs.rx == rhs.len ? rhs.rx + rx : rhs.rx,
            std::max(std::max(max, rhs.max), rx + rhs.lx)
        };
    }
} M[N * 20];
int lc[N * 20], rc[N * 20], idx, n, m;
int build(int l, int r) {
    int now = ++idx;
    if (l == r) { M[now] = data(0); return now; }
    int mid = l + r >> 1;
    lc[now] = build(l, mid), rc[now] = build(mid + 1, r);
    M[now] = M[lc[now]] + M[rc[now]];
    return now;
}
int insert(int cur, int l, int r, int pos) {
    int now = ++idx; lc[now] = lc[cur], rc[now] = rc[cur];
    if (l == r) { M[now] = data(1); return now; }
    int mid = l + r >> 1;
    if (pos <= mid) lc[now] = insert(lc[cur], l, mid, pos);
    else rc[now] = insert(rc[cur], mid + 1, r, pos);
    M[now] = M[lc[now]] + M[rc[now]];
    return now;
}
data query(int cur, int l, int r, int L, int R) {
    if (L <= l && R >= r) return M[cur];
    int mid = l + r >> 1; data res;
    if (L <= mid) res = res + query(lc[cur], l, mid, L, R);
    if (R > mid) res = res + query(rc[cur], mid + 1, r, L, R);
    return res;
}
int query(int L, int R, int k) {
    int l = 1, r = n, ans = 0;
    while (l <= r) {
        int mid = l + r >> 1;
        if (query(root[mid], 1, n, L, R).max >= k) ans = mid, r = mid - 1;
        else l = mid + 1;
    }
    return ans;
}
int main() {
    std::scanf("%d", &n);
    for (int i = 1; i <= n; i++) std::scanf("%d", &a[i]), v[i] = a[i], rk[i] = i;
    std::sort(v + 1, v + n + 1, [] (int i, int j) { return i > j; });
    std::sort(rk + 1, rk + n + 1, [] (int i, int j) { return a[i] > a[j]; });
    root[0] = build(1, n);
    for (int i = 1; i <= n; i++) root[i] = insert(root[i - 1], 1, n, rk[i]);
    std::scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        int l, r, k;
        std::scanf("%d%d%d", &l, &r, &k);
        std::printf("%d\n", v[query(l, r, k)]);
    }
    return 0;
}
```

---

## 作者：jun头吉吉 (赞：6)

# CF484E 【Sign on Fence】
[$\text{\color{red}{更好の阅读体验}}$](https://chen-jia-liang.gitee.io/blog/2020/09/12/%E9%A2%98%E8%A7%A3-CF484E-%E3%80%90Sign-on-Fence%E3%80%91/)
## 题意

给定一个长度为$n$的数列，有$m$次询问，询问形如$l\ \  r\ \ k$

要求在区间$[l,r]$内选一个长度为$k$的区间，求此区间里最小数的最大值

## 题解

首先~~题面有点绕~~，但看到`最小数的最大值`，我们不禁联想到了二分

不过首先数字可能会很大，因此我们需要**离散**，把值域改到$[1,n]$，不改变大小关系。以下操作均使用离散后的值。

于是我们要考虑如何检验$mid$是否可行。

我们转换一下题意，`在区间[l,r]内选一个长度为k的区间，此区间里最小数为mid`就相当于存在一个长度$\ ≥ k$的序列使得每一个数都$\ ≥mid$。

在换句话说，在$[l,r]$中大于等于$mid$的数的最大连续长度$\ ≥k$。

考虑如何维护长度的最大值。如果是线段树的话，我们可以这么操作：

对于每一个节点，维护三个变量$llen,rlen,mlen$，分别表示当前区间左侧连续长度，右侧连续长度以及最大的连续长度。
那么$mlen$可以从以下转移

1. 不跨越的的最大值$\max\{mlen_{rson},mlen_{lson}\}$

2. 跨越两段的值$rlen_{lson}+llen_{rson}$

取最大值即可。

观察下面的图：

![tu](https://cdn.luogu.com.cn/upload/image_hosting/cbmqdokm.png)

那么新的$llen=llen_{lson},rlen=rlen_{rson}$

但以下情况需要特判：

![tu](https://cdn.luogu.com.cn/upload/image_hosting/yc1lzc2q.png)

$llen=llen_{lson}+llen_{rson}$

$rlen$也是同理。

于是能快速查询最大连续长度的线段树就建完了。

但因为我们需要能快速查询，因此我们需要给每一个值有一个线段树。但这样必定时空爆炸。这里我们采用**可持久化线段树**来维护。

给每一个值建一个版本，从而做到在$O(\log(n))$的时间内查询$mid$是否可行。于是代码就很好写了。

## 代码
```cpp
//#pragma optimize(2)
#include<bits/stdc++.h>
using namespace std;
template<typename T>
inline void read(T &x){
	x=0;char c=getchar();bool f=false;
	for(;!isdigit(c);c=getchar())f!=c=='-';
	for(;isdigit(c);c=getchar())x=x*10+c-'0';
	if(f)x=-x;
}
template<typename T ,typename ...Arg>
inline void read(T &x,Arg &...args){
	read(x);read(args...);
}
template<typename T>
inline void write(T x){
	if(x<0)putchar('-'),x=-x;
	if(x>=10)write(x/10);
	putchar(x%10+'0');
}
const int maxn=1e5+100;
template<class T>struct Discrete{
	set<T>num;unordered_map<T,int>rk;vector<T>n;int cnt;
	void operator+=(const T b){
		num.insert(b);
	}void init(){
		cnt=0;n.clear();
		for(auto N:num)
			rk[N]=++cnt,n.push_back(N);
	}T operator[](const int b){return n[b-1];}
	int get(T x){return rk[x];}
};
Discrete<int>D;
struct node{
	int l,r,lc,rc;int len,llen,rlen,mlen;
	template<class T>node(T val){
		if(val==1)llen=rlen=mlen=1;
		else llen=rlen=mlen=0;
		len=1;
	}
	node(){llen=rlen=mlen=len=0;}
	node operator+(const node b)const{
		node c;c.len=len+b.len;
		if(r-l+1==mlen)c.llen=mlen+b.llen;
		else c.llen=llen;
		if(b.r-b.l+1==b.mlen)c.rlen=b.mlen+rlen;
		else c.rlen=b.rlen;
		c.mlen=max(rlen+b.llen,max(mlen,b.mlen));
		return c;
	}
	void cpy(node from){
		llen=from.llen;
		rlen=from.rlen;
		mlen=from.mlen;
		len=from.len;
	}
};
template<class A,class B>
struct HJT_Tree{
	A t[maxn*20];B a[maxn];
	B *operator[](const int x){return &a[x];}
	int cnt;HJT_Tree(){cnt=0;}
	int build(int l,int r){
		int x=++cnt;
		t[x].l=l,t[x].r=r;
		if(l==r){
			t[x].cpy(A(a[l]));
			return x;
		}
		int mid=l+r>>1;
		t[x].lc=build(l,mid);
		t[x].rc=build(mid+1,r);
		t[x].cpy(t[t[x].lc]+t[t[x].rc]);
		return x;
	}
	int upd(int lst,int pos,B val){
		int x=++cnt;t[x]=t[lst];
		if(t[x].l==t[x].r){t[x].cpy(A(val));return x;}
		int mid=t[x].l+t[x].r>>1;
		if(pos<=mid)t[x].lc=upd(t[lst].lc,pos,val);
		else t[x].rc=upd(t[lst].rc,pos,val);
		t[x].cpy(t[t[x].lc]+t[t[x].rc]);
		return x;
	}
	A qry(int x,int lq,int rq){
		if(lq<=t[x].l&&t[x].r<=rq)return t[x];
		int mid=t[x].l+t[x].r>>1;
		if(rq<=mid)return qry(t[x].lc,lq,rq);
		if(lq>mid)return qry(t[x].rc,lq,rq);
		return qry(t[x].lc,lq,rq)+qry(t[x].rc,lq,rq);
	}
};
HJT_Tree<node,int>Tree;
int rt[maxn],n,a,q,x,y,k;
pair<int,int>p[maxn];
signed main(){
	//freopen("1.in","r",stdin);
	read(n);
	for(int i=1;i<=n;i++)read(a),p[i]=make_pair(a,i),D+=a;
	sort(p+1,p+1+n);D.init();
	rt[maxn-1]=Tree.build(1,n);p[n+1].first=maxn-1;
	for(int i=1;i<=n;i++)p[i].first=D.get(p[i].first);
	for(int i=n;i>=1;i--)
		rt[p[i].first]=Tree.upd(rt[p[i+1].first],p[i].second,1);
	for(int i=maxn-2;i>=0;i--)if(!rt[i])rt[i]=rt[i+1];
	read(q);while(q--){
		read(x,y,k);
 		int l=0,r=maxn-1,ans;
		while(l<=r){
			int mid=l+r>>1;
			if(Tree.qry(rt[mid],x,y).mlen>=k)ans=mid,l=mid+1;
			else r=mid-1;
		}write(D[ans]);putchar('\n');
	}
	return 0;
}
```
  

---

## 作者：lzyqwq (赞：5)

[**更好的阅读体验**](https://www.cnblogs.com/MnZnOIerLzy/articles/17135246.html)

# $\texttt{Description}$

[**CodeForces 题目链接**](https://codeforces.com/problemset/problem/484/E "**CodeForces 链接**")

[**洛谷题目链接**](https://www.luogu.com.cn/problem/CF484E "**洛谷链接**")

> - 给定一个长度为 $n$ 的数列 $A$，有 $m$ 次询问，每次在给出 $A_l\sim A_r$ 中选一个长度为 $k$ 的子区间，使得选出区间的最小值最大。
>
> - $1\le n,m\le 10^5$，$1\le A_i\le 10^9$。

# $\texttt{Solution}$

首先看到最小值最大，不难想到二分。由于是多组询问，所以考虑[**整体二分**](https://www.cnblogs.com/MnZnOIerLzy/articles/17038232.html "**整体二分**")。

在整体二分中，我们套路地将所有询问当前答案的值域 $[L,R]$ 分成 $[L,\text{mid}]$ 和 $(\text{mid},R]$ 两部分。 先二分一个 $\text{mid}$，然后维护所有 $> \text{mid}$ 的数的**最长连续子区间长度**。每次询问查询 $[l,r]$ 这一区间的答案。若结果 $\ge k$，说明答案在 $(\text{mid},R]$ 中，否则在 $[L,\text{mid}]$ 中。然后继续对这两部分递归求解即可。若 $L=R$，则更新当前递归内的所有询问的答案。

具体来讲，可以参照[**洛谷 P4513**](https://www.luogu.com.cn/problem/P4513 "**洛谷 P4513**") 的思路，使用线段树维护所有 $> \text{mid}$ 的数的**最长连续子区间长度**，即把所有 $>\text{mid}$ 的数的贡献统计到线段树上。考虑在线段树的每个节点中维护 $\text{len},\text{llen},\text{rlen},\text{sz}$ 四个值，表示该节点的答案、左起最长连续段长度、右起最长连续段长度和该节点对应的区间长度。

令 $x$ 为当前节点，$\text{ls}$ 为左儿子，$\text{rs}$ 为右儿子。则有：

- 若 $\text{llen}_{\text{ls}}\ne \text{sz}_\text{ls}$，说明左起最长连续段**不横跨左右儿子的区间**，$\text{llen}_x=\text{llen}_{\text{ls}}$；否则说明**横跨左右儿子**的区间，$\text{llen}_x=\text{sz}_\text{ls}+\text{llen}_\text{rs}$。$\text{rlen}_x$ 类似维护即可。

- $\text{sz}_x=\text{sz}_\text{ls}+\text{sz}_\text{rs}$。显而易见。

- $\text{len}_x=\max\{\text{len}_\text{ls},\text{len}_\text{rs},\text{rlen}_\text{ls}+\text{llen}_\text{rs}\}$。表示分别考虑答案**完全在左儿子区间内**、**完全在右儿子区间内**和**横跨左右儿子的区间**。

此外，这题并不像[**模板题**](https://www.luogu.com.cn/problem/P3834 "**洛谷 P4513**")一样**答案符合可加性**，因为模板题只有数量的限制，可以加加减减。但是这题还有连续的限制，就不能像模板题那样，若查询结果为 $p$ 且 $p<k$，则在 $[L,\text{mid}]$ 内查找剩下的 $k-p$ 个数。但是若暴力往两个区间内插入 $>\text{mid}$ 的数，肯定会 `TLE`。由于 $>\text{mid}$ 的数在 $[L,\text{mid}]$ 仍有贡献（用它连接起两端的连续段，符合连续的限制），所以可以考虑**先递归求解 $[L,\text{mid}]$ 的答案，再消除当前递归中的数在线段树中的贡献，再递归求解 $(\text{mid},R]$**。注意，在递归求解 $[L,\text{mid}]$ 的答案时，询问内的 $k$ 值**不能改成 $k-p$**，因为**那 $p$ 个值仍然在线段树上有贡献**。这样就可以在保证效率的同时实现连续的限制了。

令 $V$ 为值域（上界减下界），这样的方法时间复杂度和空间复杂度均为 $\mathcal{O}((n+m)\cdot \log n\cdot \log V)$，可以接受。

# $\texttt{Code}$

实现细节：

- 我是用 `vector` 储存整体二分中的数与询问的。

- 使用指令集或离散化（嫌麻烦没写 qwq）可以加快代码运行效率。

[**评测记录**](https://codeforces.com/contest/484/submission/188200792 "**测评链接**")


```cpp
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define ls x*2
#define rs x*2+1
const int N=100005;
int n,m,ans[N];
struct queries{
    int l,r,k,id;
};
vector<queries>Q;
struct num{
    int x,p;
};
vector<num>A;
struct tree{
    int len,llen,rlen,sz;
}sg[N*4];
void up(int x){
    sg[x].sz=sg[ls].sz+sg[rs].sz;
    sg[x].len=max({sg[ls].len,sg[rs].len,sg[ls].rlen+sg[rs].llen});
    sg[x].llen=(sg[ls].len==sg[ls].sz?sg[ls].len+sg[rs].llen:sg[ls].llen);
    sg[x].rlen=(sg[rs].len==sg[rs].sz?sg[rs].len+sg[ls].rlen:sg[rs].rlen);
}
void build(int x,int l,int r){
    if(l==r){
        sg[x]={0,0,0,1};
        return;
    }
    int mid=l+r>>1;
    build(ls,l,mid);
    build(rs,mid+1,r);
    up(x);
}
void change(int x,int l,int r,int k,int v){
    if(l==r&&l==k){
        sg[x]={v,v,v,1};
        return;
    }
    int mid=l+r>>1;
    if(k<=mid){
        change(ls,l,mid,k,v);
    }else{
        change(rs,mid+1,r,k,v);
    }
    up(x);
}
tree query(int x,int l,int r,int ql,int qr){
    if(ql<=l&&qr>=r){
        return sg[x];
    }
    int mid=l+r>>1;
    if(qr<=mid){
        return query(ls,l,mid,ql,qr);
    }else if(ql>mid){
        return query(rs,mid+1,r,ql,qr);
    }else{
        tree t1=query(ls,l,mid,ql,qr),t2=query(rs,mid+1,r,ql,qr);
        return {max({t1.len,t2.len,t1.rlen+t2.llen}),(t1.len==t1.sz?t1.len+t2.llen:t1.llen),(t2.len==t2.sz?t2.len+t1.rlen:t2.rlen),t1.sz+t2.sz};
    }
}
void solve(vector<queries>q,vector<num>a,int l,int r){
    if(!q.size()||!a.size()){
        return;
    }
    if(l^r){
        int mid=l+r>>1;
        vector<queries>q1,q2;
        vector<num>a1,a2;
        for(auto i:a){
            if(i.x>mid){
                a1.push_back(i);
                change(1,1,n,i.p,1);
            }else{
                a2.push_back(i);
            }
        }
        for(auto i:q){
            tree tmp=query(1,1,n,i.l,i.r);
            if(tmp.len>=i.k){
                q1.push_back(i);
            }else{
                q2.push_back(i);
            }
        }
        solve(q2,a2,l,mid);
        for(auto i:a){
            if(i.x>mid){
                change(1,1,n,i.p,0);
            }
        }
        solve(q1,a1,mid+1,r);
    }else{
        for(auto i:q){
            ans[i.id]=l;
        }
    }
}
signed main(){
    cin>>n;
    for(int i=1,x;i<=n;++i){
        cin>>x;
        A.push_back({x,i});
    }
    cin>>m;
    for(int i=1,l,r,k;i<=m;++i){
        cin>>l>>r>>k;
        Q.push_back({l,r,k,i});
    }
    build(1,1,n);
    solve(Q,A,1,1e9);
    for(int i=1;i<=m;++i){
        cout<<ans[i]<<'\n';
    }
}
```

---

## 作者：xianggl (赞：4)

其实 EI 也有，但是他的太复杂了

先感谢 cryozwq 提供初步想法，阅读下文之前请移步他的题解

我们令一个元素 $i$ 在笛卡尔树上的范围为 $[l, r]$，此时问题转化为了线段覆盖

会发现瓶颈其实在 $[l, r]$ 完全落在询问区间内的情况上

cryozwq 的第 $2, 3, 4$ 个讨论中分了部分相交和完全包含两种情况，但我们可以一起考虑

令询问区间为 $[L, R]$ ，要求长度为 $k$

我们认为长度 $\geq k$ 的为合法线段

首先考虑 $L \leq r \leq R$ 的情况

会发现无论是部分相交还是完全包含，其右端点 $r \geq L + k - 1$

用一个带修改，区间查最大值的线段树即可

$L \leq l \leq R$ 的情况同理

Code

```
#include <bits/stdc++.h>
#define ri register int
#define ll long long
using namespace std;
const int Maxn=1e5;
struct Seg {
	int l,r,id;
	inline bool operator<(const Seg b) const {
		return r-l+1>b.r-b.l+1;
	}
}s[Maxn+5];
struct Query {
	int l,r,k,id;
	inline bool operator<(const Query b) const {
		return k>b.k;
	}
}q[Maxn+5];
int a[Maxn+5];
int ans[Maxn+5];
int stk[Maxn+5],ls[Maxn+5],rs[Maxn+5],top;
int n,m;
struct SegTree {
	#define ls(p) (p<<1)
	#define rs(p) (p<<1|1)
	#define mid (((l)+(r))>>1)
	int v[Maxn<<2];
	inline void update(int p) {
		v[p]=max(v[ls(p)],v[rs(p)]);
	}
	void build(int p,int l,int r) {
		v[p]=0;
		if(l==r)return ;
		build(ls(p),l,mid);
		build(rs(p),mid+1,r);
	}
	void change(int p,int l,int r,int k,int d) {
		if(l==r) {
			v[p]=d;
			return ;
		}
		if(k<=mid)change(ls(p),l,mid,k,d);
		else change(rs(p),mid+1,r,k,d);
		update(p);
	}
	int query(int p,int l,int r,int L,int R) {
		if(L<=l&&r<=R)return v[p];
		int mx=0;
		if(L<=mid)mx=max(mx,query(ls(p),l,mid,L,R));
		if(R>mid)mx=max(mx,query(rs(p),mid+1,r,L,R));
		return mx;
	}
}t;
inline bool cmpq(Query a,Query b) {
	return a.l<b.l;
}
inline bool cmps(Seg a,Seg b) {
	return a.l<b.l;
}
int build() {
	for(ri i=1;i<=n;i++) {
		while(top&&a[stk[top]]>a[i])ls[i]=stk[top--];
		if(top)rs[stk[top]]=i;
		stk[++top]=i;
	}
	return stk[1];
}
void dfs(int p,int l,int r) {
	if(!p)return ;
	s[p]=(Seg){l,r,p};
	dfs(ls[p],l,p-1);
	dfs(rs[p],p+1,r);
}
void deal_left() {
	sort(q+1,q+m+1);
	sort(s+1,s+n+1);
	t.build(1,1,n);
	int now=1;
	for(ri i=1;i<=m;i++) {
		while(now<=n&&s[now].r-s[now].l+1>=q[i].k) {
			t.change(1,1,n,s[now].r,a[s[now].id]);
			++now;
		}
		ans[q[i].id]=max(ans[q[i].id],t.query(1,1,n,q[i].l+q[i].k-1,q[i].r));
	}	
}
void deal_right() {
	sort(q+1,q+m+1);
	sort(s+1,s+n+1);
	t.build(1,1,n);
	int now=1;
	for(ri i=1;i<=m;i++) {
		while(now<=n&&s[now].r-s[now].l+1>=q[i].k) {
			t.change(1,1,n,s[now].l,a[s[now].id]);
			++now;
		}
		ans[q[i].id]=max(ans[q[i].id],t.query(1,1,n,q[i].l,q[i].r-q[i].k+1));
	}
}
void deal() {
	sort(q+1,q+m+1,cmpq);
	sort(s+1,s+n+1,cmps);
	t.build(1,1,n);
	int now=1;
	for(ri i=1;i<=m;i++) {
		while(now<=n&&s[now].l<=q[i].l) {
			t.change(1,1,n,s[now].r,a[s[now].id]);
			++now;
		}
		ans[q[i].id]=max(ans[q[i].id],t.query(1,1,n,q[i].r,n));
	}
}
int main() {
	scanf("%d",&n);
	for(ri i=1;i<=n;i++)scanf("%d",&a[i]);
	dfs(build(),1,n);
	scanf("%d",&m);
	for(ri i=1;i<=m;i++)scanf("%d%d%d",&q[i].l,&q[i].r,&q[i].k),q[i].id=i;
	deal_left();
	deal_right();
	deal();
	for(ri i=1;i<=m;i++)printf("%d\n",ans[i]);
	return 0;
}

```


---

## 作者：chenzida (赞：4)

一个好想好写好调的两个 $log$ 的做法。

我们如果二分一下答案的话，就转化成了能否找到连续的 $k$ 个大于等于 $mid$ 的值就好了。我们对于 $mid$ 值都开一棵线段树就好了，并将此时大于等于 $mid$ 的值变成 $1$。

但是发现空间爆炸，然后发现每次会有很多重合的部分，于是可持久化线段树维护一下即可。

但是这个主席树我们要维护每个节点要维护一下有多少个连续的 $1$，这个就是基础的线段树操作了，如果不想动态开点的话可以离散化下来。

代码如下：

```
#include<bits/stdc++.h>
using namespace std;
const int NR=1e5+10; 
void Min(int& x,int y){x=min(x,y);}
void Max(int& x,int y){x=max(x,y);}
int n,m;
int all,tot;
int a[NR],p[NR],q[NR];
int num[NR];
int getid(int x)
{
	int l=1,r=all,ans=-1;
	while(l<=r)
	{
		int mid=(l+r>>1);
		if(num[mid]<=x)ans=mid,l=mid+1;
		else r=mid-1;
	}
	return ans;
}
int to[NR],nxt[NR];
int head[NR];
int tt=1;
void add(int x,int y)
{
	to[tt]=y;
	nxt[tt]=head[x];
	head[x]=tt++;
}
int root[NR];
struct Nd{int l,r,le,ri,siz,sum;}tr[NR<<5];
void update(int rt)
{
	tr[rt].le=(tr[tr[rt].l].le==tr[tr[rt].l].siz)?tr[tr[rt].l].siz+tr[tr[rt].r].le:tr[tr[rt].l].le;
	tr[rt].ri=(tr[tr[rt].r].ri==tr[tr[rt].r].siz)?tr[tr[rt].r].siz+tr[tr[rt].l].ri:tr[tr[rt].r].ri;
	tr[rt].sum=max(tr[tr[rt].l].sum,max(tr[tr[rt].r].sum,tr[tr[rt].l].ri+tr[tr[rt].r].le));
}
void build(int &rt,int l,int r)
{
	rt=++tot;if(l==r){tr[rt].siz=1;return;}
	int mid=(l+r>>1);
	build(tr[rt].l,l,mid),build(tr[rt].r,mid+1,r);
	tr[rt].siz=tr[tr[rt].l].siz+tr[tr[rt].r].siz;
}
void change(int &rt,int l,int r,int x)
{
	int la=rt;rt=++tot;tr[rt]=tr[la];
	if(l==r){tr[rt].le=tr[rt].ri=tr[rt].sum=1;return;}
	int mid=(l+r>>1);
	if(x<=mid)change(tr[rt].l,l,mid,x);
	else change(tr[rt].r,mid+1,r,x);
	update(rt);
}
Nd getnum(Nd a,Nd b)
{
	Nd res;
	res.le=(a.le==a.siz)?a.siz+b.le:a.le;
	res.ri=(b.ri==b.siz)?b.siz+a.ri:b.ri;
	res.sum=max(a.sum,max(b.sum,a.ri+b.le));
	return res;
}
Nd query(int rt,int l,int r,int L,int R)
{
	if(l==L&&r==R)return tr[rt];int mid=(l+r>>1);
	if(R<=mid)return query(tr[rt].l,l,mid,L,R);
	else if(L>mid)return query(tr[rt].r,mid+1,r,L,R);
	else return getnum(query(tr[rt].l,l,mid,L,mid),query(tr[rt].r,mid+1,r,mid+1,R));
}
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
	while(ch<='9'&&ch>='0'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
int main()
{
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
	n=read();for(int i=1;i<=n;i++)a[i]=read(),p[i]=a[i];
	sort(p+1,p+n+1);for(int i=1;i<=n;i++)q[++all]=p[i];
	for(int i=1;i<=all;i++)num[i]=q[i];build(root[all+1],1,n);
	for(int i=1;i<=n;i++)add(getid(a[i]),i);
	for(int x=all;x>=1;x--)
	{
		root[x]=root[x+1];
		for(int i=head[x];i;i=nxt[i])
		{
			int y=to[i];
			change(root[x],1,n,y);
		}
	}
	m=read();
	for(int i=1;i<=m;i++)
	{
		int L=read(),R=read(),K=read();
		int l=1,r=all,ans=0;
		while(l<=r)
		{
			int mid=(l+r>>1);
			if(query(root[mid],1,n,L,R).sum>=K)ans=mid,l=mid+1;
			else r=mid-1;
		}
		printf("%d\n",num[ans]);
	}
	return 0;
}
/*
5
1 2 2 3 3
1
2 5 3
*/

---

## 作者：cryozwq (赞：3)

整体二分的主流做法是求最长的连续的 1 的区间，但是我们可以有另一个鬼畜的做法。

首先这题的静态版本比较经典。单调栈维护每个点前驱后继 $l_i,r_i$，那么 覆盖 $[l_i,r_i]$ 的最大高度即是这个点的高度。

这个整体二分很好想到，首先把 $a$ 按高度排序，我们考虑整体二分到询问 $[ql,qr]$，答案 在 a 数组下标 $[vl,vr]$ 之间，那么就是要看 $[mid+1,vr]$ 这些墙的覆盖范围是否能满足要求，可以把每个 $[l_i,r_i]$ 转化为一条线段，原问题变为对每个询问快速查询是否有一个线段和它的交大于 $z$。这里可以分类讨论：

1°有一个线段完全包含它

一定合法，因为 $z<y-x+1$。

2°它完全包含一个线段

考虑双指针解决这个问题，把 $[ql,qr]$ 的询问按 $z$ 降序排序，线段按长度降序排序。这样当我们扫到一个询问的时候可以保证之前的线段长度一定是大于要求的，所以只需要看是否完全包含即可，考虑维护一棵线段树，每个点表示以它为左端点的线段中，右端点最近的是哪个。每次 $O(\log)$ 更新，询问就是查询 $[x,y]$ 最小值是否小于 $y$。

3° 一个线段在它左边

在这种情况下，可以看成把线段左端点和 $x$ 强制取 $\max$（我们并不用考虑右端点超过 $y$ ，因为这是情况 1），考虑把线段按 $l$ 排序，对于每个询问二分找到小于 $x$ 的前缀，查询前缀 $r$ 最大值是否大于 $x+z-1$。

4° 一个线段在它右边

维护方式和情况 3 相同。

于是就可以 $O(n \log n^2)$ 解决这个问题，事实上，除了情况 2 都可以做到单 $\log$（双指针），但是情况 2 并没有想到优化成单 $\log$ 的方法。

---

## 作者：素质玩家孙1超 (赞：3)

~~巨佬都用主席树，我用整体二分~~

题意：静态求$[l,r]$,中长度为k的连续子区间最小值的最大值

康到最小值的最大值，就可以联想到二分

不难发现，二分出一个$mid$后，只要把大于$mid$的位置搞为1，其他搞为0

然后求$[l,r]$中的最长连续1的子区间

如果每个都二分一遍，时间复杂度不允许

那么就整体二分

代码有~~详细~~注释

```cpp
#include<bits/stdc++.h>
#define lc (root<<1)
#define rc (root<<1|1)
#define mid (l+r>>1) 
#define max(a,b) (a>b?a:b)
using namespace std;
const int Maxn=2e5+5;
inline int R()
{
	char c;int res,sign=1;
	while((c=getchar())>'9'||c<'0') if(c=='-') sign=-1;res=c-'0';
	while((c=getchar())>='0'&&c<='9') res=res*10+c-'0';
	return res*sign;
}
void W(int x)
{
	if(x>9) W(x/10);
	putchar('0'+x%10);
} 
//读入输出优化 
struct thing // 把所有东西都丢进去 
{
	int x,y,k;
	bool op;
	int num;
}q[Maxn],q1[Maxn],q2[Maxn];
int n,m,cnt,ans[Maxn];
int llen[Maxn*2],rlen[Maxn*2],mlen[Maxn*2],Rlen,Mlen,TOP;
inline void pushup(int root,int l,int r)
{
	mlen[root]=0;
	if(mlen[lc]==mid-l+1) llen[root]=mlen[lc]+llen[rc];
	else llen[root]=llen[lc];
	if(mlen[rc]==r-mid)   rlen[root]=mlen[rc]+rlen[lc];
	else rlen[root]=rlen[rc];
	mlen[root]=max(mlen[root],mlen[lc]);
	mlen[root]=max(mlen[root],mlen[rc]);
	mlen[root]=max(mlen[root],rlen[lc]+llen[rc]);
}
void modify(int root,int l,int r,int pos,int value)
{
	if(l>pos||r<pos) return;
	if(l==r)
	{
		llen[root]=value;
		rlen[root]=value;
		mlen[root]=value;
		return;
	}
	modify(lc,l,mid,pos,value);
	modify(rc,mid+1,r,pos,value);
	pushup(root,l,r);
}
void query(int root,int l,int r,int z,int y)
{
	if(r<z||l>y) return;
	if(z<=l&&y>=r) 
	{
		Mlen=max(Mlen,mlen[root]);
		Mlen=max(Mlen,llen[root]+Rlen);
		if(mlen[root]==r-l+1) Rlen+=mlen[root];
		else Rlen=rlen[root]; 
		return ;
	}
	query(lc,l,mid,z,y);
	query(rc,mid+1,r,z,y);
}
//线段树部分,线段树就单纯记录左起最长1段,和右起最长1段和最长1段,然后维护就好了 
void solve(int ql,int qr,int l,int r)
{
	if(ql>qr) return;
	if(l==r)
	{
		for(int i=ql;i<=qr;i++)
			if(q[i].op)ans[q[i].num]=l;
		return;//二分出来了 
	}
	int p1=0,p2=0;
	for(int i=ql;i<=qr;i++)
		if(!q[i].op)
		{
			if(q[i].x>mid)
			{
				modify(1,1,n,q[i].num,1);
				q2[++p2]=q[i];
			}
			else q1[++p1]=q[i];
		}//处理点 
	for(int i=ql;i<=qr;i++)
		if(q[i].op)
		{
			Mlen=Rlen=0;
			query(1,1,n,q[i].x,q[i].y);
			if(Mlen>=q[i].k)q2[++p2]=q[i];
			else q1[++p1]=q[i];
		}//处理询问 
	int p3=ql-1;
	for(int i=1;i<=p1;i++)
	q[++p3]=q1[i];
	for(int i=1;i<=p2;i++)
	q[++p3]=q2[i];
	solve(ql,ql+p1-1,l,mid);//左区间 
	for(int i=ql+p1;i<=qr;i++)//还原,使得对右区间不会有影响
	if(!q[i].op)
	modify(1,1,n,q[i].num,0);
	solve(ql+p1,qr,mid+1,r);//右区间 
}
int main()//中规中矩的主函数 
{
	n=R(); 
	for(int i=1;i<=n;i++)
	{
		++cnt;
		q[cnt].x=R();
		q[cnt].num=i;
		TOP=max(TOP,q[cnt].x);
	}
	m=R();
	for(int i=1;i<=m;i++)
	{
		++cnt;
		q[cnt].x=R();
		q[cnt].y=R();
		q[cnt].k=R();
		q[cnt].num=i;
		q[cnt].op=1; 
	}
	solve(1,cnt,1,TOP+1);
	for(int i=1;i<=m;i++)
	{
		W(ans[i]);
		puts("");
	}
}
```


---

## 作者：huayucaiji (赞：2)

## 前言

主席树入门

## 解题思路

这个很好做。首先题目要我们求的是最小值的最大值，显然一眼就是二分答案，我们现在的问题就变成了怎样检验一个答案是否符合要求。

比如说我们二分出来一个 $mid$，那么我们需要检验在 $[l,r]$ 之中是否存在长度为 $k$ 的连续不比 $mid$ 小的串。

由于我们只关心数字与 $mid$ 的大小关系，我们可以认为大于等于 $mid$ 为 $1$，小于 $mid$ 为 $0$。

所以我们求的就是对于 $mid$，最长连续为 $1$ 的串长度是否大于等于 $k$。

容易想到对每个 $mid$ 开线段树，但是时空爆炸，我们需另想妙招。

可以用主席树来优化。

此时我们把从大到小的所有 $mid$ 对应的线段树全部求出来，最多修改 $n$ 次，可以接受。

至于怎么维护最长连续 $1$，可以看其他博文，有详细解释，或者看我的代码也可以。

注意要离散化，把值域修改为 $[1,n]$，否则可能的 $mid$ 值太多了。

## 代码

```cpp
//Don't act like a loser.
//This code is written by huayucaiji
//You can only use the code for studying or finding mistakes
//Or,you'll be punished by Sakyamuni!!!
#include<bits/stdc++.h>
#define int long long//别骂了
using namespace std;

int read() {
	char ch=getchar();
	int f=1,x=0;
	while(ch<'0'||ch>'9') {
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f*x;
}

const int MAXN=1e5+10;

int n,m,q,cnt,tot;
int num[MAXN],a[MAXN],root[MAXN],rt[MAXN];
vector<int> vec[MAXN];
struct seg_tree {
	int llen,rlen,alen,ls,rs,len;
}s[MAXN<<5];

int new_node() {
	return ++cnt;
}
void pushup(seg_tree &ans,seg_tree a,seg_tree b) {
	ans.len=a.len+b.len;
	
	ans.alen=max(max(a.alen,b.alen),a.rlen+b.llen);
	if(a.llen==a.len) {
		ans.llen=a.llen+b.llen;
	}
	else {
		ans.llen=a.llen;
	}
	if(b.rlen==b.len) {
		ans.rlen=b.rlen+a.rlen;
	}
	else {
		ans.rlen=b.rlen;
	}
}
int build(int l,int r,int p) {
	if(!p) {
		p=new_node();
	}
	if(l==r) {
		s[p].len=r-l+1;
		s[p].llen=s[p].rlen=s[p].alen=0;
		return p;
	}
	int mid=(l+r)>>1;
	s[p].ls=build(l,mid,s[p].ls);
	s[p].rs=build(mid+1,r,s[p].rs);
	pushup(s[p],s[s[p].ls],s[s[p].rs]);
	return p;
}
int modify(int l,int r,int p0,int p,int x) {
	if(!p) {
		p=new_node();
	}
	if(l==r) {
		s[p].len=r-l+1;
		s[p].llen=s[p].rlen=s[p].alen=1;
		return p;
	}
	int mid=(l+r)>>1;
	if(x<=mid) {
		s[p].rs=s[p0].rs;
		s[p].ls=modify(l,mid,s[p0].ls,s[p].ls,x);
	}
	else {
		s[p].ls=s[p0].ls;
		s[p].rs=modify(mid+1,r,s[p0].rs,s[p].rs,x);
	}
	pushup(s[p],s[s[p].ls],s[s[p].rs]);
	return p;
}
seg_tree query(int l,int r,int p,int x,int y) {
	if(y<l||r<x) {
		return s[0];
	}
	if(x<=l&&r<=y) {
		return s[p];
	}
	int mid=(l+r)>>1;
	seg_tree ans=s[0];
	pushup(ans,query(l,mid,s[p].ls,x,y),query(mid+1,r,s[p].rs,x,y));
	return ans;
}

bool check(int l,int r,int k,int x) {
	if(query(1,n,rt[x],l,r).alen>=k) {
		return 1;
	}
	return 0;
}
signed main() {
	cin>>n;
	for(int i=1;i<=n;i++) {
		a[i]=read();
		num[i]=a[i];
	}
	sort(num+1,num+n+1);
	m=unique(num+1,num+n+1)-num-1;
	for(int i=1;i<=n;i++) {
		a[i]=lower_bound(num+1,num+m+1,a[i])-num;
		//cout<<a[i]<<endl;
		vec[a[i]].push_back(i);
	}
	
	root[0]=build(1,n,root[0]);
	for(int i=m;i;i--) {
		int sz=vec[i].size();
		for(int j=0;j<sz;j++) {
			tot++;
			root[tot]=modify(1,n,root[tot-1],root[tot],vec[i][j]);
		}
		rt[i]=root[tot];
	}
	
	cin>>q;
	for(int i=1;i<=q;i++) {
		int l,r,k;
		l=read();r=read();k=read();
		
		int lft=1,rgt=m;
		while(lft+1<rgt) {
			int mid=(lft+rgt)>>1;
			if(check(l,r,k,mid)) {
				lft=mid;
			}
			else {
				rgt=mid;
			}
		}
		if(check(l,r,k,rgt)) {
			printf("%lld\n",num[rgt]);
		}
		else {
			printf("%lld\n",num[lft]);
		}
	}
	return 0;
}
```

---

## 作者：FutaRimeWoawaSete (赞：1)

考虑先把原序列按值排序，然后查询时我们发现答案具有单调性并且答案一定是一个木桩上的高度，所以二分一下答案是在排序后的哪个木桩上就行了。    

将之前的下标看成值域，现在单次查询就变成了一个询问前缀是否可以选出一个长度大于等于 $w$ 的区间内的连续值域段，这个东西我们发现对于全局查询是可以直接线段树维护的。          

发现查询都在前缀内，于是直接建立主席树然后树上节点维护信息后在查询时直接把 $2 \log n$ 个节点单独提出来重新建树算即可，时间复杂度是大常数 $O(n \log ^ 2 n)$ 。          

```cpp
#include "bits/stdc++.h"
using namespace std;
const int Len = 1e5 + 5;
struct Node
{
	int val,id;
}a[Len];
bool cmp(Node x,Node y){return x.val > y.val;}
int n,m,top,Ll,Rr,lsh[Len],cnt,Kcnt,rt[Len];
struct node
{
	int l,r,lmax,rmax,allmaxn,len;
	node(){l = r = lmax = rmax = allmaxn = len = 0;}
	node(int L,int R,int LMAX,int RMAX,int ALLMAXN,int LEN){l = l , R = r , lmax = LMAX , rmax = RMAX , allmaxn = ALLMAXN , len = LEN;}
}tree[Len * 25],ODT[1025],LSH[1025];
int clone(int p)
{
	top ++;
	tree[top] = tree[p];
	return top;
}
node push_up(node L,node R)
{
	node res;
	res.l = L.l , res.r = R.r , res.len = L.len + R.len;
	res.lmax = L.lmax;
	if(L.allmaxn == L.len) res.lmax = L.allmaxn + R.lmax;
	res.rmax = R.rmax;
	if(R.allmaxn == R.len) res.rmax = R.allmaxn + L.rmax;
	res.allmaxn = max(L.allmaxn , R.allmaxn);
	res.allmaxn = max(res.allmaxn , L.rmax + R.lmax);
	return res;
}
void build(int &p,int l,int r)
{
	p = clone(p);
	tree[p].len = r - l + 1;
	if(l == r) return;
	int mid = (l + r) >> 1;
	build(tree[p].l , l , mid);
	build(tree[p].r , mid + 1 , r);
}
void update(int &p,int l,int r,int idx)
{
	p = clone(p);
	if(l == r)
	{
		tree[p].allmaxn = tree[p].lmax = tree[p].rmax = 1;
	//	printf("%d %d %d %d %d\n",l,r,tree[p].allmaxn,tree[p].lmax,tree[p].rmax); 
		tree[p].l = tree[p].r = 0 , tree[p].len = 1;
		return;
	}
	int mid = (l + r) >> 1;
	if(idx <= mid) update(tree[p].l , l , mid , idx);
	else update(tree[p].r , mid + 1 , r , idx);
	Ll = tree[p].l , Rr = tree[p].r;
	tree[p] = push_up(tree[tree[p].l] , tree[tree[p].r]);
	tree[p].l = Ll , tree[p].r = Rr;
	//printf("%d %d %d %d %d\n",l,r,tree[p].allmaxn,tree[p].lmax,tree[p].rmax); 
}
void query(int p,int l,int r,int nl,int nr)
{
	if(nl <= l && nr >= r) 
	{
		LSH[++ Kcnt] = tree[p];
		return;	
	} 
	int mid = (l + r) >> 1;
	if(nl <= mid) query(tree[p].l , l , mid , nl , nr);
	if(nr > mid) query(tree[p].r , mid + 1 , r , nl , nr);
}
#define ls(p) p << 1
#define rs(p) p << 1 | 1
void BUILD(int p,int l,int r)
{
	if(l == r){ODT[p] = LSH[l];return;}
	int mid = (l + r) >> 1;
	BUILD(ls(p) , l , mid);
	BUILD(rs(p) , mid + 1 , r);
	ODT[p] = push_up(ODT[ls(p)] , ODT[rs(p)]);
}
signed main()
{
	scanf("%d",&n);
	for(int i = 1 ; i <= n ; i ++) 
	{
		scanf("%d",&a[i].val);
		a[i].id = i;
	}
	sort(a + 1 , a + 1 + n , cmp);
	build(rt[0] , 1 , n);
	for(int i = 1 ; i <= n ; i ++) 
	{
		//printf("###%d\n",i);
		rt[i] = rt[i - 1];
		update(rt[i] , 1 , n , a[i].id);		
	}
	scanf("%d",&m);
	for(int i = 1 ; i <= m ; i ++)
	{
		int l,r,x;scanf("%d %d %d",&l,&r,&x);
		int ansl = 1 , ansr = n;
		while(ansl <= ansr)
		{
			int mid = (ansl + ansr) >> 1;
			Kcnt = 0;
			query(rt[mid] , 1 , n , l , r);
			BUILD(1 , 1 , Kcnt);
			if(ODT[1].allmaxn >= x) ansr = mid - 1;
			else ansl = mid + 1;
		}
		printf("%d\n",a[ansl].val);
	}
	return 0;
}
```

---

## 作者：_acat_ (赞：0)

## 题目大意

给定一个长度为 $n$ 的数列，有 $m$ 次询问，询问形如 $l$，$r$，$k$。

要你在区间 $[l,r]$ 内选一个长度为 $k$ 的区间，求区间最小数的最大值。

## Sol
很显然可以二分答案。

设二分的最小高度 $h_{\min}$，只要在区间 $[l,r]$ 中检查是否有连续 $w$ 个数都 $\ge h_{\min}$。

我们把 $h_{i} \ge h_{\min}$ 的位置填 $1$，否则填 $0$。

问题就变成检查区间 $[l,r]$ 中是否有连续 $w$ 个 $1$。

可以用线段树来实现。 

考虑上述做法的前提是在固定 $h_{\min}$ 的情况下的，很显然 $h_{\min}$ 最多有 $n$ 种取值，最多可能有 $n$ 颗线段树。

因此可以使用可持久化线段树。

对 $h$ 从大到小排序。

依次往线段树中插入 $1$，得到一颗新的线段树。

二分 $h_{\min}$ 的时候，在 $h_{\min}$ 对应的线段树上做查询即可。


---

