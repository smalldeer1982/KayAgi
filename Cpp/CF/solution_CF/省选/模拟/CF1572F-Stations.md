# Stations

## 题目描述

There are $ n $ cities in a row numbered from $ 1 $ to $ n $ .

The cities will be building broadcasting stations. The station in the $ i $ -th city has height $ h_i $ and range $ w_i $ . It can broadcast information to city $ j $ if the following constraints are met:

- $ i \le j \le w_i $ , and
- for each $ k $ such that $ i < k \le j $ , the following condition holds: $ h_k < h_i $ .

 In other words, the station in city $ i $ can broadcast information to city $ j $ if $ j \ge i $ , $ j $ is in the range of $ i $ -th station, and $ i $ is strictly highest on the range from $ i $ to $ j $ (including city $ j $ ).At the beginning, for every city $ i $ , $ h_i = 0 $ and $ w_i = i $ .

Then $ q $ events will take place. During $ i $ -th event one of the following will happen:

- City $ c_i $ will rebuild its station so that its height will be strictly highest among all stations and $ w_{c_i} $ will be set to $ g_i $ .
- Let $ b_j $ be the number of stations that can broadcast information to city $ j $ . Print the sum of $ b_j $ over all $ j $ satisfying $ l_i \le j \le r_i $ .

Your task is to react to all events and print answers to all queries.

## 说明/提示

In the first test case, only station $ 1 $ reaches city $ 1 $ before and after it is rebuilt.

In the second test case, after each rebuild, the array $ b $ looks as follows:

1. $ [1, 1, 1, 2, 1] $ ;
2. $ [1, 2, 2, 3, 2] $ ;
3. $ [1, 2, 2, 1, 2] $ ;
4. $ [1, 1, 2, 1, 2] $ ;
5. $ [1, 1, 2, 1, 1] $ .

## 样例 #1

### 输入

```
1 3
2 1 1
1 1 1
2 1 1```

### 输出

```
1
1```

## 样例 #2

### 输入

```
5 10
1 3 4
2 3 5
1 1 5
2 1 5
1 4 5
2 2 4
1 2 3
2 1 3
1 5 5
2 2 5```

### 输出

```
4
10
5
4
5```

# 题解

## 作者：xyf007 (赞：5)

直接维护 $b_i$ 非常困难，考虑计算每一个广播站的贡献。设 $r_i$ 表示 $i$ 最远可以传递到哪一个广播站，那么初始 $r_i=i,b_i=1$。$r_i$ 就表示对 $b_i,\ldots,b_{r_i}$ 有 $1$ 的贡献。每一次修改，$c_i$ 变成最高的，因此 $r_{c_i}=g_i$。对于 $c_i$ 左边的每一个位置 $j$，一定不能跨过 $i$，因此 $r_j\gets\min(r_j,i-1)$。可以发现只有单点修改，区间取 min，可以使用吉司机线段树维护 $r_i$。  
接下来考虑 $r_i$ 的变化对 $b$ 的影响。单点修改直接减去原来的值然后加上新的贡献。注意到在吉司机线段树上，区间操作都是把所有最大值 $\mathit{max}$ 变成 $v$，即修改 $\mathit{cnt}_{\mathit{max}}$ 个值相等的位置。也就是说每一次打 tag 将 $\mathit{max}$ 改成 $v$ 的过程，对应了 $b$ 上 $[v+1,\mathit{max}]$ 这个区间减去 $\mathit{cnt}_{\mathit{max}}$。因此再用一个线段树维护 $b$ 即可。由于吉司机线段树没有区间加，因此是严格 $O(n\log n)$ 次操作，每次操作需要 $O(\log n)$ 时间在第二棵线段树上区间修改，因此时间复杂度 $O(n\log^2n)$。

虽然有两棵线段树，但是代码难度并不大，因为都是基本操作，没有特别的细节。
```cpp
#include <cstring>
#include <iostream>
template <typename T>
void checkmax(T &x, T y) {
  if (x < y) x = y;
}
template <typename T>
void checkmin(T &x, T y) {
  if (x > y) x = y;
}
int n, q;
class SegmentTree {
 private:
  long long sum_[800001], tag_[800001];
  void Pushup(int x) { sum_[x] = sum_[x + x] + sum_[x + x + 1]; }
  void Add(int l, int r, int v, int x) {
    sum_[x] += static_cast<long long>(r - l + 1) * v, tag_[x] += v;
  }
  void Pushdown(int l, int r, int x) {
    if (tag_[x]) {
      int mid = (l + r) >> 1;
      Add(l, mid, tag_[x], x + x), Add(mid + 1, r, tag_[x], x + x + 1);
      tag_[x] = 0LL;
    }
  }

 public:
  void Build(int l, int r, int x) {
    if (l == r) {
      sum_[x] = 1LL;
      return;
    }
    int mid = (l + r) >> 1;
    Build(l, mid, x + x), Build(mid + 1, r, x + x + 1);
    Pushup(x);
  }
  void Modify(int L, int R, int l, int r, int v, int x) {
    if (L <= l && r <= R) return Add(l, r, v, x);
    int mid = (l + r) >> 1;
    Pushdown(l, r, x);
    if (L <= mid) Modify(L, R, l, mid, v, x + x);
    if (R > mid) Modify(L, R, mid + 1, r, v, x + x + 1);
    Pushup(x);
  }
  long long Query(int L, int R, int l, int r, int x) {
    if (L <= l && r <= R) return sum_[x];
    Pushdown(l, r, x);
    int mid = (l + r) >> 1;
    long long ans = 0LL;
    if (L <= mid) ans += Query(L, R, l, mid, x + x);
    if (R > mid) ans += Query(L, R, mid + 1, r, x + x + 1);
    return ans;
  }
} sgt;
class SegmentTreeBeats {
 private:
  struct Node {
    int max, smax, cnt, tag;
  } t_[800001];
  void Pushup(int x) {
    if (t_[x + x].max == t_[x + x + 1].max) {
      t_[x].max = t_[x + x].max;
      t_[x].smax = std::max(t_[x + x].smax, t_[x + x + 1].smax);
      t_[x].cnt = t_[x + x].cnt + t_[x + x + 1].cnt;
    } else if (t_[x + x].max > t_[x + x + 1].max) {
      t_[x].max = t_[x + x].max;
      t_[x].smax = std::max(t_[x + x].smax, t_[x + x + 1].max);
      t_[x].cnt = t_[x + x].cnt;
    } else {
      t_[x].max = t_[x + x + 1].max;
      t_[x].smax = std::max(t_[x + x].max, t_[x + x + 1].smax);
      t_[x].cnt = t_[x + x + 1].cnt;
    }
  }
  void Min(int v, int x) { t_[x].max = t_[x].tag = v; }
  void Pushdown(int x) {
    if (t_[x].tag != -1) {
      if (t_[x].tag < t_[x + x].max) Min(t_[x].tag, x + x);
      if (t_[x].tag < t_[x + x + 1].max) Min(t_[x].tag, x + x + 1);
      t_[x].tag = -1;
    }
  }

 public:
  void Build(int l, int r, int x) {
    t_[x].tag = -1;
    if (l == r) {
      t_[x] = {l, -0x3f3f3f3f, 1, -1};
      return;
    }
    int mid = (l + r) >> 1;
    Build(l, mid, x + x), Build(mid + 1, r, x + x + 1);
    Pushup(x);
  }
  void Modify(int l, int r, int p, int v, int x) {
    if (l == r) {
      t_[x] = {v, -0x3f3f3f3f, 1, -1};
      return;
    }
    Pushdown(x);
    int mid = (l + r) >> 1;
    if (p <= mid)
      Modify(l, mid, p, v, x + x);
    else
      Modify(mid + 1, r, p, v, x + x + 1);
    Pushup(x);
  }
  void Min(int L, int R, int l, int r, int v, int x) {
    if (L <= l && r <= R) {
      if (v >= t_[x].max) return;
      if (v > t_[x].smax) {
        sgt.Modify(v + 1, t_[x].max, 1, n, -t_[x].cnt, 1);
        return Min(v, x);
      }
    }
    Pushdown(x);
    int mid = (l + r) >> 1;
    if (L <= mid) Min(L, R, l, mid, v, x + x);
    if (R > mid) Min(L, R, mid + 1, r, v, x + x + 1);
    Pushup(x);
  }
  int Query(int l, int r, int p, int x) {
    if (l == r) return t_[x].max;
    Pushdown(x);
    int mid = (l + r) >> 1;
    if (p <= mid)
      return Query(l, mid, p, x + x);
    else
      return Query(mid + 1, r, p, x + x + 1);
  }
} sgtb;
int main(int argc, char const *argv[]) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);
  std::cin >> n >> q;
  sgtb.Build(1, n, 1), sgt.Build(1, n, 1);
  while (q--) {
    int op, x, y;
    std::cin >> op >> x >> y;
    if (op == 1) {
      if (x > 1) sgtb.Min(1, x - 1, 1, n, x - 1, 1);
      int r = sgtb.Query(1, n, x, 1);
      sgt.Modify(x, r, 1, n, -1, 1);
      sgtb.Modify(1, n, x, y, 1), sgt.Modify(x, y, 1, n, 1, 1);
    } else {
      std::cout << sgt.Query(x, y, 1, n, 1) << '\n';
    }
  }
  return 0;
}
```

---

## 作者：Kubic (赞：2)

提供一个无脑做法。

考虑维护 $a_i$ 表示站点 $i$ 能覆盖到的最右端的位置。

那么每次修改 $(x,w)$ 相当于：

- $\forall i\in[1,x),a_i\leftarrow\min\{a_i,x-1\}$

- $a_x\leftarrow w$

使用 Segment Tree Beats（吉司机线段树）维护 $a$。

由于这种数据结构的性质，我们每次会把一个线段中的所有最大值改为 $x-1$。所以可以在维护 $a$ 的同时用另一个数据结构维护 $b$。

最终对 $b$ 有 $O(n\log^2n)$ 个区间修改操作和 $O(n)$ 个区间求和操作，可以使用分块平衡一下复杂度。总复杂度 $O(n(\log^2n+\sqrt{n}))$。

upd：在没有区间加减操作时 Segment Tree Beats 的复杂度是 $n\log n$ 的，所以其实不用分块，直接树状数组即可。

参考代码（分块）：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 200005
#define ll long long
#define mid ((l+r)/2)
const int B=450,INF=1e9;
int n,m;struct Seg {int tg,cnt,mx[2];}sg[N*4];
int bl[N];ll s11[N],s12[N],s21[N],s22[N];
void pu(int p)
{
	sg[p].mx[0]=max(sg[p*2].mx[0],sg[p*2+1].mx[0]);
	sg[p].mx[1]=max(sg[p*2].mx[1],sg[p*2+1].mx[1]);sg[p].cnt=0;
	if(sg[p].mx[0]==sg[p*2].mx[0]) sg[p].cnt=sg[p*2].cnt;
	else sg[p].mx[1]=max(sg[p].mx[1],sg[p*2].mx[0]);
	if(sg[p].mx[0]==sg[p*2+1].mx[0]) sg[p].cnt+=sg[p*2+1].cnt;
	else sg[p].mx[1]=max(sg[p].mx[1],sg[p*2+1].mx[0]);
}
void upd2(int x,int vl)
{
	if(x>n) return;s11[x]+=vl;s12[bl[x]]+=vl;
	s21[x]+=1ll*vl*x;s22[bl[x]]+=1ll*vl*x;
}
ll qSm(int x)
{
	if(!x) return 0;ll s1=0,s2=0;
	for(int i=1;i<bl[x];++i) s1+=s12[i],s2+=s22[i];
	for(int i=x;i>(bl[x]-1)*B;--i) s1+=s11[i],s2+=s21[i];return s1*(x+1)-s2;
}
void mdf(int p,int vl,bool fl=0)
{
	if(fl) upd2(vl+1,-sg[p].cnt),upd2(sg[p].mx[0]+1,sg[p].cnt);
	sg[p].mx[0]=vl;sg[p].tg=min(sg[p].tg,vl);
}
void pd(int p)
{
	if(sg[p].tg<INF)
	{
		if(sg[p*2].mx[0]>sg[p].tg) mdf(p*2,sg[p].tg);
		if(sg[p*2+1].mx[0]>sg[p].tg) mdf(p*2+1,sg[p].tg);sg[p].tg=INF;
	}
}
void build(int p,int l,int r)
{
	sg[p].tg=INF;if(l==r) {sg[p]=(Seg) {INF,1,{l,0}};return;}
	build(p*2,l,mid);build(p*2+1,mid+1,r);pu(p);
}
void upd(int p,int l,int r,int qL,int qR,int vl)
{
	if(qL>qR || sg[p].mx[0]<=vl) return;
	if(l>=qL && r<=qR && sg[p].mx[1]<vl) {mdf(p,vl,1);return;}
	pd(p);if(qL<=mid) upd(p*2,l,mid,qL,qR,vl);
	if(qR>mid) upd(p*2+1,mid+1,r,qL,qR,vl);pu(p);
}
void upd1(int p,int l,int r,int x,int vl)
{
	if(l==r) {upd2(sg[p].mx[0]+1,1);upd2(vl+1,-1);sg[p].mx[0]=vl;return;}
	pd(p);if(x<=mid) upd1(p*2,l,mid,x,vl);else upd1(p*2+1,mid+1,r,x,vl);pu(p);
}
int qry(int p,int l,int r,int x)
{
	if(l==r) return sg[p].mx[0];pd(p);
	if(x<=mid) return qry(p*2,l,mid,x);return qry(p*2+1,mid+1,r,x);
}
int main()
{
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;++i) bl[i]=(i-1)/B+1;upd2(1,1);build(1,1,n);
	for(int i=1,F[3];i<=m;++i)
	{
		scanf("%d %d %d",&F[0],&F[1],&F[2]);
		if(F[0]==1) upd1(1,1,n,F[1],F[2]),upd(1,1,n,1,F[1]-1,F[1]-1);
		if(F[0]==2) printf("%lld\n",qSm(F[2])-qSm(F[1]-1));
	}return 0;
}
```

---

## 作者：_fairytale_ (赞：1)

好难啊！！！

考虑直接维护 $b_i$ 不好做，不妨先尝试维护出 $r_i$ 表示 $i$ 这个广播站最远能广播到哪。考虑一次修改 $(i,g)$，首先 $r_i\gets g$，然后对于 $i$ 前面的广播站 $j$，执行 $r_j\gets \min(r_j,i-1)$。这是经典的 segment tree beats 问题。

发现支持区间 ckmin 的 segment tree beats 有很好的性质：它每次修改都是对一段区间内值相同的元素一起 ckmin。当有 $cnt$ 个 $r$ 相同的元素一起从 $r$ 修改到 $r'$ 时，区间 $[r',r]$ 的 $b_i$ 都减少了 $cnt$！

于是我们开两棵线段树，一棵维护 $r$，另一棵维护 $b$ 数组即可。

```cpp
#include<bits/stdc++.h>
bool Mst;
#define ll long long
#define ls ((p)<<1)
#define rs (((p)<<1)|1)
#define mid ((l+r)>>1)
#define rep(x,qwq,qaq) for(int x=(qwq);x<=(qaq);++x)
#define per(x,qwq,qaq) for(int x=(qwq);x>=(qaq);--x)
using namespace std;
template<class _T>
void ckmax(_T &x,_T y) {
	x=max(x,y);
}
#define inf 0x3f3f3f3f
#define maxn 201000
int n,q;
struct Seg2 {
	ll sum[maxn<<2],tag[maxn<<2];
	void pusht(int p,int l,int r,int v) {
		sum[p]+=1ll*(r-l+1)*v;
		tag[p]+=v;
	}
	void pushd(int p,int l,int r) {
		pusht(ls,l,mid,tag[p]);
		pusht(rs,mid+1,r,tag[p]);
		tag[p]=0;
	}
	void add(int p,int l,int r,int L,int R,int v) {
		if(L<=l&&r<=R)return void(pusht(p,l,r,v));
		pushd(p,l,r);
		if(mid>=L)add(ls,l,mid,L,R,v);
		if(mid<R)add(rs,mid+1,r,L,R,v);
		sum[p]=sum[ls]+sum[rs];
	}
	ll query(int p,int l,int r,int L,int R) {
		if(L<=l&&r<=R)return sum[p];
		pushd(p,l,r);
		ll res=0;
		if(mid>=L)res+=query(ls,l,mid,L,R);
		if(mid<R)res+=query(rs,mid+1,r,L,R);
		return res;
	}
} T2;
struct Seg1 {
	struct tree {
		int mx,se,cnt;
	} t[maxn<<2];
	friend tree operator +(tree x,tree y) {
		if(x.mx==y.mx)return (tree) {
			x.mx,max(x.se,y.se),x.cnt+y.cnt
		};
		if(x.mx<y.mx)swap(x,y);
		ckmax(x.se,y.mx);
		return x;
	}
	void pusht(int p,int v) {
		if(v<t[p].mx)t[p].mx=v;
	}
	void pushd(int p) {
		pusht(ls,t[p].mx);
		pusht(rs,t[p].mx);
	}
	void build(int p,int l,int r){
		if(l==r)return void(t[p]={l,-inf,1});
		build(ls,l,mid),build(rs,mid+1,r);
		t[p]=t[ls]+t[rs];
	}
	void modify(int p,int l,int r,int pos,int v) {
		if(l==r) {
			if(v<t[p].mx)T2.add(1,1,n,v+1,t[p].mx,-1);
			else if(v>t[p].mx)T2.add(1,1,n,t[p].mx+1,v,1);
			t[p]= {v,-inf,1};
			return;
		}
		pushd(p);
		if(mid>=pos)modify(ls,l,mid,pos,v);
		else modify(rs,mid+1,r,pos,v);
		t[p]=t[ls]+t[rs];
	}
	void ckmin(int p,int l,int r,int L,int R,int v) {
		if(v>=t[p].mx)return;
		if(L<=l&&r<=R&&t[p].se<v) {
			T2.add(1,1,n,v+1,t[p].mx,-t[p].cnt);
			t[p].mx=v;
			return;
		}
		pushd(p);
		if(mid>=L)ckmin(ls,l,mid,L,R,v);
		if(mid<R)ckmin(rs,mid+1,r,L,R,v);
		t[p]=t[ls]+t[rs];
	}
} T1;
bool Med;
signed main() {
	cerr<<(&Mst-&Med)/1024.0/1024.0<<" MB\n";
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>q;
	T1.build(1,1,n),T2.add(1,1,n,1,n,1);
	for(int i=1,op,a,b; i<=q; ++i) {
		cin>>op>>a>>b;
		if(op==1) {
			T1.modify(1,1,n,a,b);
			if(a>1)T1.ckmin(1,1,n,1,a-1,a-1);
		} else {
			cout<<T2.query(1,1,n,a,b)<<'\n';
		}
	}
	return 0;
}
```

---

## 作者：VoidX (赞：1)

每个广播站能向它右面连续的一段区间 $[i,r_i]$ 传播消息，修改时 $h_i$ 变成最高的，也就是令 $r_{c_i}\leftarrow g_i$，对于 $c_i$ 左边的位置 $j$，应该令 $r_j\leftarrow \min\{r_j,i-1\}$。也就是说，$r$ 可以直接 SGT Beats 维护。修改 $r$ 时可以统计 $b$ 的贡献，是一个区间修改区间查询的问题，树状数组维护二阶前缀和即可。时间复杂度 $O(n\log^2 n)$。

```cpp
#include <bits/stdc++.h>
#define ls ((o) << 1)
#define rs (ls | 1)
using namespace std; 
typedef long long i64; 
const int N = 2e5 + 5; 
const int INF = 1e9; 

int n, q; 

struct Fenwick {
    i64 C[N]; 
    inline void add(int x, i64 k) { for (; x <= n; x += x & -x) C[x] += k; }
    inline i64 sum(int x) { i64 r = 0; for (; x; x -= x & -x) r += C[x]; return r; }
} T1, T2; 

inline void add(int x, int k) {
    T1.add(x, k); T2.add(x, 1ll * x * k); 
}
inline i64 sum(int x) {
    return 1ll * (x + 1) * T1.sum(x) - T2.sum(x); 
}

int mx[N * 4], mx2[N * 4], cnt[N * 4], tag[N * 4]; 
inline void pushup(int o) {
    if (mx[ls] > mx[rs]) mx[o] = mx[ls], cnt[o] = cnt[ls], mx2[o] = max(mx2[ls], mx[rs]); 
    else if (mx[rs] > mx[ls]) mx[o] = mx[rs], cnt[o] = cnt[rs], mx2[o] = max(mx2[rs], mx[ls]); 
    else mx[o] = mx[ls], cnt[o] = cnt[ls] + cnt[rs], mx2[o] = max(mx2[ls], mx2[rs]); 
}
void build(int o, int l, int r) {
    tag[o] = INF; 
    if (l == r) return mx[o] = l, cnt[o] = 1, void(); 
    int mid = l + r >> 1; 
    build(o << 1, l, mid); build(o << 1 | 1, mid + 1, r); 
    pushup(o); 
}
inline void maketag(int o, int k) {
    mx[o] = min(mx[o], k); tag[o] = min(tag[o], k); 
}
inline void pushdown(int o) {
    if (tag[o] == INF) return; 
    maketag(ls, tag[o]); maketag(rs, tag[o]); 
    tag[o] = INF; 
}
void update(int o, int l, int r, int x, int k) {
    if (l == r) {
        add(mx[o] + 1, 1); mx[o] = k; 
        add(mx[o] + 1, -1); 
        return; 
    }
    pushdown(o); int mid = l + r >> 1; 
    if (x <= mid) update(ls, l, mid, x, k); 
    else update(rs, mid + 1, r, x, k); 
    pushup(o); 
}
void update(int o, int l, int r, int x, int y, int k) {
    if (k >= mx[o]) return; 
    if (x <= l && r <= y && k > mx2[o]) {
        add(mx[o] + 1, cnt[o]); mx[o] = k; 
        add(mx[o] + 1, -cnt[o]); 
        return maketag(o, k); 
    }
    pushdown(o); int mid = l + r >> 1; 
    if (x <= mid) update(ls, l, mid, x, y, k); 
    if (mid < y) update(rs, mid + 1, r, x, y, k); 
    pushup(o); 
}

int main(void) {
    ios::sync_with_stdio(0); cin.tie(0); 
    cin >> n >> q; build(1, 1, n); add(1, 1); 
    while (q--) {
        int op, l, r; cin >> op >> l >> r; 
        if (op == 1) {
            if (l > 1) update(1, 1, n, 1, l - 1, l - 1); 
            update(1, 1, n, l, r); 
        } else cout << sum(r) - sum(l - 1) << '\n';  
    }
    return 0; 
}
```

---

## 作者：StayAlone (赞：0)

设 $r_i$ 表示 $i$ 最远可以传递到哪一个广播站，则对于 $[i, r_i]$ 的 $b$ 都有 $1$ 的贡献，初始 $r_i=i,b_i=1$，试图维护通过 $r_i$ 维护 $b_i$。

对于修改 $i, g$，将 $h_i$ 变为最高的，则 $i$ 可以向 $[i, g]$ 贡献，即 $r_i\gets g$；同时，$i$ 左侧的广播站均不能达到 $i$，即对于 $j\in [1, i)$，$r_j$ 对 $i-1$ 取 $\min$。

用吉司机维护，区间取 $\min$ 总是将区间的最大值同时改为一个数，只需维护最大值的数量 $cnt$，则 $b$ 的 $[k+1,mx]$ 均减少 $cnt$。

于是维护 $b$ 只需要区间加，区间求和。共 $\mathcal O(n\log n)$ 次区间加，总时间复杂度 $\mathcal O(n\log^2 n)$。

这里用了 [这种东西](https://www.luogu.com.cn/article/fxvx5qz6) 维护 $b$，可能代码有点 confusing。

```cpp
int n, m; ll sum[MAXN], add[MAXN];

il void modify(int x, int v) {
	if (!x) return;
	int nw = x, s = 0;
	for(int i = x + lowbit(x); i <= n; i += lowbit(i)) {
		while (nw && lowbit(nw) < lowbit(i)) {
			add[nw] += v; sum[nw] += 1ll * lowbit(nw) * v;
			s += lowbit(nw); nw -= lowbit(nw);
		} sum[i] += 1ll * s * v;
	}
	while (nw) {
		add[nw] += v; sum[nw] += 1ll * lowbit(nw) * v;
		nw -= lowbit(nw);
	}
}

il ll query(int x) {
	if (!x) return 0;
	int nw = x, s = 0, k = 0; ll ans = 0;
	for(int i = x + lowbit(x); i <= n; i += lowbit(i)) {
		while (nw && lowbit(nw) < lowbit(i)) {
			k += lowbit(nw);
			ans += sum[nw];
			nw -= lowbit(nw);
		} ans += 1ll * add[i] * k;
	}
	while (nw) ans += sum[nw], nw -= lowbit(nw);
	return ans;
}

il void upd(int l, int r, int v) {
	modify(r, v); modify(l - 1, -v);
}

struct setr {
    #define STZ MAXN << 2
    int mx[STZ], sem[STZ], cnt[STZ], tag[STZ];

    il void pushup(int x) {
        if (mx[ls(x)] == mx[rs(x)]) {
            mx[x] = mx[ls(x)]; cnt[x] = cnt[ls(x)] + cnt[rs(x)];
            sem[x] = max(sem[ls(x)], sem[rs(x)]);
        } else if (mx[ls(x)] > mx[rs(x)]) {
            mx[x] = mx[ls(x)]; cnt[x] = cnt[ls(x)];
            sem[x] = max(sem[ls(x)], mx[rs(x)]);
        } else {
            mx[x] = mx[rs(x)]; cnt[x] = cnt[rs(x)];
            sem[x] = max(sem[rs(x)], mx[ls(x)]);
        }
    }

    il void change(int x, int v) {
        if (v < mx[x]) mx[x] = tag[x] = v;
    }

    il void pushdown(int x) {
        if (!~tag[x]) return;
        change(ls(x), tag[x]); change(rs(x), tag[x]); tag[x] = -1;
    }

    il void init(int x, int l, int r) {
        tag[x] = -1;
        if (l == r) return mx[x] = l, sem[x] = -inf, cnt[x] = 1, void();
        int mid = l + r >> 1;
        init(ls(x), l, mid); init(rs(x), mid + 1, r);
        pushup(x);
    }

    il void upd_s(int x, int l, int r, int k, int p) {
        if (l == r) {
            if (mx[x] >= p) upd(p + 1, mx[x], -1);
            else upd(mx[x] + 1, p, 1);
            mx[x] = p; return;
        } int mid = l + r >> 1; pushdown(x);
        k <= mid ? upd_s(ls(x), l, mid, k, p) : upd_s(rs(x), mid + 1, r, k, p);
        pushup(x);
    }

    il void chkmin(int x, int l, int r, int ql, int qr, int k) {
        if (l > qr || r < ql) return;
        if (k >= mx[x]) return;
        if (l >= ql && r <= qr && k > sem[x]) return upd(k + 1, mx[x], -cnt[x]), change(x, k);
        int mid = l + r >> 1; pushdown(x);
        chkmin(ls(x), l, mid, ql, qr, k); chkmin(rs(x), mid + 1, r, ql, qr, k);
        pushup(x);
    }
} T;

int main() {
	read(n, m); T.init(1, 1, n);
    rep1(i, 1, n) sum[i] = 1;
	rep1(i, 1, n) sum[i + lowbit(i)] += sum[i];
	int op, x, y; while (m--) {
		read(op, x, y);
		if (op == 1) {
            T.upd_s(1, 1, n, x, y);
            T.chkmin(1, 1, n, 1, x - 1, x - 1);
        } else printf("%lld\n", query(y) - query(x - 1));
	}
	return 0;
}
```

---

