# [RMI 2024] 彩虹糖 / Skittlez

## 题目背景

$\text{\underline{Taste} the rainbow, \underline{solve} the rainbow.}$


## 题目描述


彩虹糖包装机上有 $n$ 行 $n$ 列共 $n\times n$ 个袋子。我们记第 $i$ 行第 $j$ 列的袋子为 $(i,j)$。

有 $q$ 个操作：每个操作用六元组 $(x_1,y_1,x_2,y_2,c,k)$ 描述，意思是：

- $\forall x_1\le i\le x_2$，$y_1\le j\le y_2$，在 $(i,j)$ 中放入 $k$ 颗颜色为 $c$ 的彩虹糖。

在所有操作完后，求出每一袋中，彩虹糖颜色的**绝对众数**。

定义一种颜色是绝对众数，当且仅当，它出现次数**严格大于**其他颜色出现次数之和。

## 说明/提示


#### 样例解释

方便人类阅读的样例输出为

```plain
 1  1 -1 -1 -1
 1  1  1  1 -1
 1  1  1  1 -1
-1  1  1  1  3
-1 -1  3  3  3
```

```plain
-1  1  1  1  1  2  2  2  2  2
-1  1  1  1  2  2  2  2  2  2
-1 -1 -1 -1  2  2  2  2  2  2
-1 -1 -1 -1 -1  2  2  2  2  2
 1  1  1  2  2  2  2  2  2  2
 1  1  6 -1 -1  2  2  2  2  2
 1  1  6 -1 -1  2  2  2  6 -1
-1 -1  6  2  2  2  2  2  6 -1
 2  2  6  2  2  2  2  2  6 -1
-1 -1  6  6  6  6  6  6  6 -1
```

#### 数据范围

对于 $100\%$ 的数据，保证：

- $1\le n\le 10^3$；
- $1\le q\le 5\times 10^5$；
- $1\le x_1\le x_2\le n$；
- $1\le y_1\le y_2\le n$；
- $1\le c\le q$；
- $1\le k\le 10^9$。

---

- $\text{Subtask 0 (0 pts)}$：样例。
- $\text{Subtask 1 (7 pts)}$：$n,q\le 20$，$k\le 5$。
- $\text{Subtask 2 (21 pts)}$：至多有 $20$ 种颜色。
- $\text{Subtask 3 (44 pts)}$：$n\le 300$，$q\le 10^5$。
- $\text{Subtask 4 (28 pts)}$：无额外限制。


## 样例 #1

### 输入

```
5 3
1 3 5 5 3 3
2 2 4 4 1 5
1 1 3 5 1 3```

### 输出

```
1 1 -1 -1 -1 
1 1 1 1 -1 
1 1 1 1 -1 
-1 1 1 1 3 
-1 -1 3 3 3 ```

## 样例 #2

### 输入

```
10 10
1 6 6 10 2 4
5 4 9 8 2 5
2 7 6 9 2 3
6 3 10 9 6 4
1 2 2 10 1 3
5 1 7 6 1 3
9 1 9 2 2 4
4 6 8 7 2 3
2 5 3 7 2 4
1 8 6 10 2 3```

### 输出

```
-1 1 1 1 1 2 2 2 2 2 
-1 1 1 1 2 2 2 2 2 2 
-1 -1 -1 -1 2 2 2 2 2 2 
-1 -1 -1 -1 -1 2 2 2 2 2 
1 1 1 2 2 2 2 2 2 2 
1 1 6 -1 -1 2 2 2 2 2 
1 1 6 -1 -1 2 2 2 6 -1 
-1 -1 6 2 2 2 2 2 6 -1 
2 2 6 2 2 2 2 2 6 -1 
-1 -1 6 6 6 6 6 6 6 -1 ```

# 题解

## 作者：Egg_eating_master (赞：17)

考虑对 $c$ 做二进制拆分。对于一个位置 $(x,y)$，若这个位置上的所有 $c$ 在二进制表示下第 $i$ 位为 $p$ 的比较多，那么如果该位置存在绝对众数，它的二进制第 $i$ 位一定为 $p$。

只要对于每个 $i$ 都做一遍这个东西，就可以对于每一个位置得到**唯一可能**的绝对众数。我们接下来只要 check 它到底是不是绝对众数就可以了，选择一个你喜欢的数据结构即可，我使用了二维树状数组。

时间复杂度 $O((n^2+q)\log q+(n+q)\log^2 n)$，其中前半部分是得到唯一可能的答案，后半部分是 check。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 1005, maxm = 500005;
int n, q;
int d[maxn][maxn][21];
int ans[maxn][maxn];
struct node {int x1, y1, x2, y2, k;};
struct heige {int x, y;};
vector<node> hg[maxm];
vector<heige> h[maxm];
struct BIT {
    int sum[maxn][maxn];
    int lowbit(int x) {return x & -x;}
    void update(int x, int y, int val) {
        for (int i = x; i <= n; i += lowbit(i))
            for (int j = y; j <= n; j += lowbit(j))
                sum[i][j] += val;
    }
    int query(int x, int y) {
        int res = 0;
        for (int i = x; i; i -= lowbit(i))
            for (int j = y; j; j -= lowbit(j))
                res += sum[i][j];
        return res;
    }
} t;
void add(int x1, int y1, int x2, int y2, int p, int k) {d[x1][y1][p] += k; d[x1][y2 + 1][p] -= k; d[x2 + 1][y1][p] -= k; d[x2 + 1][y2 + 1][p] += k;}
signed main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> q;
    for (int i = 1; i <= q; i++) {
        int x1, y1, x2, y2, k, c; cin >> x1 >> y1 >> x2 >> y2 >> c >> k;
        add(x1, y1, x2, y2, 0, k);
        for (int j = 1; j <= 20; j++)
            if ((c >> j - 1) & 1) add(x1, y1, x2, y2, j, k);
        hg[c].push_back((node){x1, y1, x2, y2, k});
    }
    for (int i = 0; i <= 20; i++) {
        for (int j = 1; j <= n; j++)
            for (int k = 1; k <= n; k++)
                d[j][k][i] += d[j - 1][k][i];
        for (int j = 1; j <= n; j++)
            for (int k = 1; k <= n; k++)
                d[j][k][i] += d[j][k - 1][i];
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= 20; k++)
                if (d[i][j][k] * 2 > d[i][j][0]) ans[i][j] |= (1 << k - 1);
            if (ans[i][j] > q) ans[i][j] = -1;
            else h[ans[i][j]].push_back((heige){i, j});
        }
    for (int i = 0; i <= q; i++) {
        for (auto k : hg[i]) {
            t.update(k.x1, k.y1, k.k);
            t.update(k.x1, k.y2 + 1, -k.k);
            t.update(k.x2 + 1, k.y1, -k.k);
            t.update(k.x2 + 1, k.y2 + 1, k.k);
        }
        for (auto k : h[i]) {
            int s = t.query(k.x, k.y);
            if (s * 2 <= d[k.x][k.y][0] || s == 0) ans[k.x][k.y] = -1;
        }
        for (auto k : hg[i]) {
            t.update(k.x1, k.y1, -k.k);
            t.update(k.x1, k.y2 + 1, k.k);
            t.update(k.x2 + 1, k.y1, k.k);
            t.update(k.x2 + 1, k.y2 + 1, -k.k);
        }
    }
    for (int i = 1; i <= n; i++, cout << '\n')
        for (int j = 1; j <= n; j++)
            cout << ans[i][j] << ' ';
    return 0;
}
```

---

## 作者：Lynkcat (赞：7)

枚举二进制位 $i$。将所有颜色在 $i$ 位上为 $1$ 的操作单独抠出来作为集合 $S$。对于每个位置求被 $S$ 集合覆盖的次数，然后判断是否大于被全集覆盖次数的一半。通过这个操作我们能得到每个位置的答案（如果不是-1）。

判 -1 就对于每种颜色数点即可。

时间复杂度 $O(n\log n)$，只需要树状数组与二维前缀和。

fun fact：发现了很多人使用二维树状数组来解决二维数点。

---

## 作者：Purslane (赞：7)

# Solution

简单题。

众所周知，绝对众数可以通过打擂台（摩尔投票）实现。

所以可以定义二元组 $(col,cnt)$ 之间的运算：$(col_1,cnt_1) + (col_2,cnt_2)$ 定义为：

1. 如果 $col_1=col_2$，则为 $(col_1,cnt_1+cnt_2)$；
2. 否则，如果 $cnt_1 < cnt_2$，为 $(col_2,cnt_2-cnt_1)$；
3. 否则，如果 $cnt_1>cnt_2$ 为 $(col_1,cnt_1-cnt_2)$；
4. 否则，定义为 $(-1,0)$。

我们不需要分析这种运算是否具有交换律和结合律，只需要明白：无论怎么交换和结合这种操作，如果绝对众数存在就一定能被找出来。

所以我们需要处理 $n \times n$ 的矩形，矩形加最后单点查询的问题。操作不具有可差分性，因此不能使用二维树状数组。不过如果能求出可能的答案，在检验的时候显然是可以用二维树状数组的。

这种不可差分的二维信息怎么维护呢？

考虑对第一维进行猫树分治（操作的顺序可以随意调换）。在扫描第一维的过程中，用线段树维护第二维。

注意到信息可以交换，所以可以使用标记永久化，获得更小的常数。

复杂度显然为 $O(n^2 \log^2 n + q \log n)$。~~看起来太搞笑了，复杂度瓶颈在最后检验时的二维树状数组上。~~

事实上我感觉一维猫树分治后另一维直接暴力可能也不会太慢。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1000+10,MAXM=5e5+10;
int n,q;
int x[MAXM],y[MAXM],xx[MAXM],yy[MAXM],k[MAXM],c[MAXM],ans[MAXN][MAXN];
vector<pair<int,int>> qr[MAXM];
vector<int> upd[MAXM];
struct Z {int col;ll cnt;}fin[MAXN][MAXN];
Z operator +(Z A,Z B) {
	if(A.col==B.col) return {A.col,A.cnt+B.cnt};
	if(A.cnt>B.cnt) return {A.col,A.cnt-B.cnt};
	return {B.col,B.cnt-A.cnt};	
}
namespace BIT {
	ll tr[MAXN][MAXN];
	inline void update(int p1,int p2,const int v) {
		for(int p=p1;p<=n;p+=(p&-p)) for(int q=p2;q<=n;q+=(q&-q)) tr[p][q]+=v;
		return ;
	}
	inline ll query(int p1,int p2) {
		ll ans=0;
		for(int p=p1;p;p-=(p&-p)) for(int q=p2;q;q-=(q&-q)) ans+=tr[p][q];
		return ans;	
	}
};
int ok[MAXN<<2],L[MAXN<<2],R[MAXN<<2];
#define lson (k<<1)
#define rson (k<<1|1)
#define mid (l+r>>1)
void build(int k,int l,int r) {ok[k]=1,L[k]=l,R[k]=r;if(l!=r) build(lson,l,mid),build(rson,mid+1,r);return ;}
struct INFO {int l,r;Z ad;};
vector<INFO> ad[15][MAXN];
namespace SGT {
	Z tag[MAXN<<2],pre[MAXN<<2];
	void init(void) {ffor(i,1,n*4) tag[i]=pre[i]={0,0};return ;}
	void update(int k,int l,int r,int x,int y,Z ad) {
		if(x<=l&&r<=y) return tag[k]=tag[k]+ad,void();
		if(x<=mid) update(lson,l,mid,x,y,ad);
		if(y>mid) update(rson,mid+1,r,x,y,ad);
		return ;
	}
	void add(int h) {
		ffor(i,1,4*n) pre[i]=tag[i];
		ffor(i,1,4*n) if(ok[i]) {
			if(L[i]==R[i]) fin[h][L[i]]=fin[h][L[i]]+pre[i];
			else pre[i<<1]=pre[i<<1]+pre[i],pre[i<<1|1]=pre[i<<1|1]+pre[i];
		}
		return ;
	}
};
void insert(int k,int l,int r,int x,int y,INFO info,int dep) {
	if(l==r) return ad[dep][l].push_back(info),void();
	if(x<=mid&&y>mid) return ad[dep][x].push_back(info),ad[dep][y].push_back(info),void();
	if(x==mid+1) return ad[dep][y].push_back(info),void();
	if(y==mid) return ad[dep][x].push_back(info),void();
	if(y<=mid) insert(lson,l,mid,x,y,info,dep+1);
	else insert(rson,mid+1,r,x,y,info,dep+1);
	return ;
}
void solve(int k,int l,int r,int dep) {
	if(l==r) {
		SGT::init();
		for(auto pr:ad[dep][l]) SGT::update(1,1,n,pr.l,pr.r,pr.ad);
		SGT::add(l);
		return ;	
	}
	solve(lson,l,mid,dep+1),solve(rson,mid+1,r,dep+1);
	SGT::init();
	ffor(i,l,mid) {
		for(auto pr:ad[dep][i]) SGT::update(1,1,n,pr.l,pr.r,pr.ad);
		SGT::add(i);	
	}
	SGT::init();
	roff(i,r,mid+1) {
		for(auto pr:ad[dep][i]) SGT::update(1,1,n,pr.l,pr.r,pr.ad);
		SGT::add(i);	
	}
	return ;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>q;
	build(1,1,n);
	ffor(i,1,q) {
		cin>>x[i]>>y[i]>>xx[i]>>yy[i]>>c[i]>>k[i];
		insert(1,1,n,x[i],xx[i],{y[i],yy[i],{c[i],k[i]}},1);	
		BIT::update(x[i],y[i],-k[i]);
		BIT::update(x[i],yy[i]+1,k[i]);
		BIT::update(xx[i]+1,y[i],k[i]);
		BIT::update(xx[i]+1,yy[i]+1,-k[i]);
		upd[c[i]].push_back(i);
	}
	solve(1,1,n,1);
	memset(ans,-1,sizeof(ans));
	ffor(i,1,n) ffor(j,1,n) qr[fin[i][j].col].push_back({i,j});
	ffor(c,1,q) if(qr[c].size()) {
		for(auto i:upd[c]) {
			BIT::update(x[i],y[i],2*k[i]);
			BIT::update(x[i],yy[i]+1,-2*k[i]);
			BIT::update(xx[i]+1,y[i],-2*k[i]);
			BIT::update(xx[i]+1,yy[i]+1,2*k[i]);
		}
		for(auto pr:qr[c]) if(BIT::query(pr.first,pr.second)>0) ans[pr.first][pr.second]=c;
		for(auto i:upd[c]) {
			BIT::update(x[i],y[i],-2*k[i]);
			BIT::update(x[i],yy[i]+1,2*k[i]);
			BIT::update(xx[i]+1,y[i],2*k[i]);
			BIT::update(xx[i]+1,yy[i]+1,-2*k[i]);
		}
	}
	ffor(i,1,n) {ffor(j,1,n) cout<<ans[i][j]<<' ';cout<<'\n';}
	return 0;
}
```

---

## 作者：ppip (赞：4)

$(n^2+q) \log n$ 非常简单。

首先我们先用摩尔投票将问题转化为矩形加上一个交换半群信息，最后查询每个位置的信息。

我们直接照搬 [rprmq1](/problem/P6109) 的思路，对行做一个猫树分治，将每个矩形挂到它被首次切开的地方。因为它被切开了，它肯定经过此次分治的中间，然后从两侧向中间分别做一个扫描线，它的存在时间肯定是一个后缀，所以直接用线段树做区间修改就行。

扫的时候，因为要查询所有位置的值，直接将线段树所有标记下传到叶子，然后把叶子处的值贡献到答案上即可。

验证答案是否是绝对众数可以对每种颜色分别扫描线。

没卡常轻松最优解。

```cpp
#include <bits/stdc++.h>
using namespace std;
constexpr int Spp{1<<20},S2{1<<20};
char buf[Spp],*p1,*p2,buf2[S2],*l2=buf2,_st[22];
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,Spp,stdin),p1==p2)?EOF:*p1++)
#define putchar(c) (l2==buf2+S2&&(fwrite(buf2,1,S2,stdout),l2=buf2),*l2++=(c))
template <typename T>
void read(T &x) {
    char c;int f{1};
    do x=(c=getchar())^48;
    while (!isdigit(c)&&c!='-');
    if (x==29) f=-1,x=0;
    while (isdigit(c=getchar()))
        x=(x*10)+(c^48);
    x*=f;
}
template <typename T,typename ...Args>
void read(T& x,Args&... args) {read(x);read(args...);}
template<typename T>
void write(T x,char c='\n') {
    if (x<0) putchar('-'),x*=-1;
    int tp=0;
    do _st[++tp]=x%10; while (x/=10);
    while (tp) putchar(_st[tp--]+'0');
    putchar(c);
}
struct OI{~OI(){fwrite(buf2,1,l2-buf2,stdout);}}oi;
constexpr int N(5e5),M{1000};
struct rect {
    int l,r,u,d;
} a[N+5];
int n,k;
using LL=long long;
struct info {
    int c;LL k,k2;
    info &operator+=(info b) {
        if (c==b.c) k+=b.k;
        else if (b.k>k) c=b.c,k=b.k-k;
        else k-=b.k;
        k2+=b.k2;
        return *this;
    }
} b[N+5],w[M+5][M+5],T[M*2+5];
vector<int> rec[N+5];
void solve(int L,int R,vector<int> &v) {
    if (L>R||v.empty()) return;
    int mid{L+R>>1};
    vector<int> ll,rr;
    for (int i{L};i<=R;++i) rec[i].clear();
    for (auto w:v)
        if (a[w].r>=mid&&a[w].l<=mid+1) {
            if (a[w].l<=mid) rec[a[w].l].push_back(w);
            if (a[w].r>mid) rec[a[w].r].push_back(w);
        } else if (a[w].r>=mid) rr.push_back(w);
        else ll.push_back(w);
    v.clear();v.shrink_to_fit();
    for (int i{1};i<2*n;++i) T[i]={0,0,0};
    for (int i{L};i<=mid;++i) {
        for (auto j:rec[i]) {
            for (int l{a[j].u+n-1},r{a[j].d+n-1};l<=r;l>>=1,r>>=1) {
                if (l&1) T[l++]+=b[j];
                if (~r&1) T[r--]+=b[j];
            }
        }
        for (int j{1};j<n;++j) T[j<<1]+=T[j],T[j<<1|1]+=T[j],T[j]={0,0,0};
        for (int j{n};j<2*n;++j) w[i][j-n+1]+=T[j];
    }
    for (int i{1};i<2*n;++i) T[i]={0,0,0};
    for (int i{R};i>mid;--i) {
        for (auto j:rec[i]) {
            for (int l{a[j].u+n-1},r{a[j].d+n-1};l<=r;l>>=1,r>>=1) {
                if (l&1) T[l++]+=b[j];
                if (~r&1) T[r--]+=b[j];
            }
        }
        for (int j{1};j<n;++j) T[j<<1]+=T[j],T[j<<1|1]+=T[j],T[j]={0,0,0};
        for (int j{n};j<2*n;++j) w[i][j-n+1]+=T[j];
    }
    solve(L,mid,ll);
    solve(mid+1,R,rr);
}
LL t[N+5];
void add(int x,LL k) {
    while (x<=n) {
        t[x]+=k;
        x+=x&-x;
    }
}
LL qry(int x) {
    LL ans{0};
    while (x) {
        ans+=t[x];
        x&=x-1;
    }
    return ans;
}
void mod(int l,int r,LL k) {
    add(l,k);
    add(r+1,-k);
}
vector<tuple<int,int,int>> ms[N+5];
LL ret[M+5][M+5];
int main() {
    read(n,k);
    vector<int> v(k);
    for (int i{1};i<=k;++i) {
        read(a[i].l,a[i].u,a[i].r,a[i].d);
        read(b[i].c,b[i].k);
        b[i].k2=b[i].k;
        v[i-1]=i;
    }
    solve(1,n,v);
    for (int i{1};i<=k;++i) {
        ms[b[i].c].emplace_back(a[i].l,0,i);
        ms[b[i].c].emplace_back(a[i].r+1,0,i);
    }
    for (int i{1};i<=n;++i)
        for (int j{1};j<=n;++j)
            if (w[i][j].k)
                ms[w[i][j].c].emplace_back(i,1,j);
    for (int i{1};i<=k;++i) {
        sort(ms[i].begin(),ms[i].end());
        for (auto [x,op,y]:ms[i])
            if (!op) mod(a[y].u,a[y].d,b[y].k),b[y].k*=-1;
            else ret[x][y]=qry(y);
    }
    for (int i{1};i<=n;++i) {
        for (int j{1};j<=n;++j)
            if (w[i][j].k&&ret[i][j]*2>w[i][j].k2) write(w[i][j].c,' ');
            else write(-1,' ');
        putchar('\n');
    }
    return 0;
}
```

---

## 作者：Masterwei (赞：3)

分治做法。

首先我们都知道求绝对众数可以摩尔投票，且摩尔投票满足交换律、结合律。

对于矩阵加 $[xl,xr],[yl,yr]$，我们考虑猫树分治，我们设 $solve(l,r)$ 表示处理所有 $[xl,xr]$ 被 $[l,r]$ 包含的矩阵加操作。

考虑先处理 $[xl,xr]$ 跨过 $mid$ 的操作，然后分成 $[xl,xr]$ 在 $mid$ 左边和 $[xl,xr]$ 在 $mid$ 右边，分别递归处理。

如何处理 $[xl,xr]$ 跨过 $mid$ 的操作？由于已经跨过了 $mid$，于是我们做一次前缀和，一次后缀和即可。

最后拿二维树状数组判一下是否是绝对众数就做完了。

时间复杂度是 $O((n^2+q)\log^2n)$。


```cpp
#include<bits/stdc++.h>
#define ll long long
#define fir first
#define sec second
using namespace std;
inline int read(){
	int x=0;bool f=0;char ch=getchar();
	while(ch<'0'||ch>'9')f^=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return f?-x:x;
}
const int Maxn=1005,N=5e5+5;
int n,q;
struct Node{
	ll c,k;
	inline Node operator+(const Node&b)const{
		if(c==b.c)return (Node){c,k+b.k};
		return k>b.k?(Node){c,k-b.k}:(Node){b.c,b.k-k};
	}
}ans[1005][1005],pre[1005][1005],suf[1005][1005];
struct node{
	int xl,yl,xr,yr;Node data;
};
vector<node>g[N];
vector<pair<short,short> >f[1000006];
ll sum[1005][1005];
ll t[1005][1005];
inline void add(int x,int y,ll p){
	if(!x||!y)return;
	for(int i=x;i<=n;i+=i&-i)
		for(int j=y;j<=n;j+=j&-j)t[i][j]+=p;
}
inline ll query(int x,int y){
	ll res=0;
	for(int i=x;i;i-=i&-i)
		for(int j=y;j;j-=j&-j)res+=t[i][j];
	return res;
}
void solve(int l,int r,vector<node>a){
	if(a.empty())return;
	if(l==r){
		for(node i:a)
			for(int j=i.yl;j<=i.yr;j++)
				ans[l][j]=ans[l][j]+i.data;
		return;
	}int mid=l+r>>1;
	for(int i=l-1;i<=mid;i++)for(int j=1;j<=n;j++)pre[i][j]={0,0};
	for(int i=mid+1;i<=r+1;i++)for(int j=1;j<=n;j++)suf[i][j]={0,0};
	vector<node>b,c;
	for(node i:a){
		if(i.xr<=mid)b.push_back(i);
		else if(i.xl>mid)c.push_back(i);
		else{
			for(int j=i.yl;j<=i.yr;j++)pre[i.xl][j]=pre[i.xl][j]+i.data;
			for(int j=i.yl;j<=i.yr;j++)suf[i.xr][j]=suf[i.xr][j]+i.data;
		}
	}
	for(int i=l;i<=mid;i++){
		for(int j=1;j<=n;j++)pre[i][j]=pre[i][j]+pre[i-1][j],ans[i][j]=ans[i][j]+pre[i][j];
	}
	for(int i=r;i>mid;i--){
		for(int j=1;j<=n;j++)suf[i][j]=suf[i][j]+suf[i+1][j],ans[i][j]=ans[i][j]+suf[i][j];
	}
	solve(l,mid,b);solve(mid+1,r,c);
}
signed main(){
//	freopen(".in","r",stdin);
//	freopen("1.out","w",stdout);
	n=read();q=read();
	vector<node>tmp;
	for(int i=1;i<=q;i++){
		int x0=read(),y0=read(),x=read(),y=read(),c=read(),k=read();
		tmp.push_back((node){x0,y0,x,y,(Node){c,k}});
		sum[x0][y0]+=k;sum[x0][y+1]-=k;sum[x+1][y0]-=k;sum[x+1][y+1]+=k;
		g[c].push_back((node){x0,y0,x,y,(Node){c,k}});
	}
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)sum[i][j]+=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];
	solve(1,n,tmp);
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++){
		if(ans[i][j].c)f[ans[i][j].c].push_back(make_pair(i,j));
		else ans[i][j].c=-1;
	}
	for(int i=1;i<=q;i++){
		for(node j:g[i]){add(j.xl,j.yl,j.data.k);add(j.xr+1,j.yl,-j.data.k);add(j.xl,j.yr+1,-j.data.k);add(j.xr+1,j.yr+1,j.data.k);}
		for(pair<short,short>j:f[i]){
			int x=j.fir,y=j.sec;
			if(query(x,y)*2<=sum[x][y])ans[x][y].c=-1;
		}
		for(node j:g[i]){add(j.xl,j.yl,-j.data.k);add(j.xr+1,j.yl,j.data.k);add(j.xl,j.yr+1,j.data.k);add(j.xr+1,j.yr+1,-j.data.k);}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)printf("%d ",ans[i][j].c);
		puts("");
	}
	return 0;
}

```

---

## 作者：NOI_Winner (赞：3)

我们依次枚举 $c$ 的所有二进制位，设当前枚举到第 $i$ 位。将第 $i$ 位是 $0$ 的所有操作一并处理，求出每个位置 $k$ 的和，记为 $a_{i,j}$。同理，将第 $i$ 位是 $1$ 的所有操作一并处理，求出每个位置 $k$ 的和，记为 $b_{i,j}$。这很容易通过二维差分求解。对于一个位置 $(x,y)$，如果 $a_{x,y} \gt b_{x,y}$ 那若有解第 $i$ 位一定为 $0$，反之如果 $a_{x,y} \lt b_{x,y}$ 那若有解第 $i$ 位一定为 $1$，如果相等直接判无解。将所有二进制位拼起来我们就能得到这一位可能的答案，如果有解答案一定是它。

  接下来我们需要判断每一位是否有解。先二维差分预处理每个位置所有操作 $k$ 的和，记为 $s_{x,y}$。然后对于每一个 $c$，我们使用二维差分加二维树状数组维护每一个位置所有 $c$ 操作 $k$ 的和，若当前位置和 $\gt \frac{1}{2}s_{x,y}$ 就有解，否则无解。

代码示例：
```cpp
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

using ll = long long;
constexpr int maxn = 1000, maxm = 500000, maxk = 19;
ll a[maxn + 5][maxn + 5], b[maxn + 5][maxn + 5];
int ans[maxn + 5][maxn + 5];
int n, m;

struct s_t
{ int x1, y1, x2, y2, k; };
vector<s_t> vec[maxm + 5];

struct p_t
{ int x, y; };
vector<p_t> p[maxm + 5];

inline int lowbit(int x)
{ return x & -x; }

void add(int x, int y, int v)
{
    for (int i = x; i <= n; i += lowbit(i))
        for (int j = y; j <= n; j += lowbit(j))
            a[i][j] += v;
}

ll query(int x, int y)
{
    ll ans = 0;
    for (int i = x; i; i -= lowbit(i))
        for (int j = y; j; j -= lowbit(j))
            ans += a[i][j];
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        int x1, y1, x2, y2, c, k;
        cin >> x1 >> y1 >> x2 >> y2 >> c >> k;
        vec[c].push_back({x1, y1, x2, y2, k});
    }

    for (int bit = 0; bit <= maxk; bit++)
    {
        memset(a, 0, sizeof(a));
        memset(b, 0, sizeof(b));

        for (int c = 1; c <= m; c++)
            for (auto [x1, y1, x2, y2, k] : vec[c])
                if (0 == (c >> bit & 1))
                {
                    a[x1][y1] += k; a[x2 + 1][y2 + 1] += k;
                    a[x1][y2 + 1] -= k; a[x2 + 1][y1] -= k;
                }
                else
                {
                    b[x1][y1] += k; b[x2 + 1][y2 + 1] += k;
                    b[x1][y2 + 1] -= k; b[x2 + 1][y1] -= k;
                }

        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
            {
                a[i][j] += a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
                b[i][j] += b[i - 1][j] + b[i][j - 1] - b[i - 1][j - 1];

                if (b[i][j] > a[i][j])
                    ans[i][j] |= 1 << bit;
            }
    }

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (ans[i][j] > 0 && ans[i][j] <= m)
                p[ans[i][j]].push_back({i, j});
            else
                ans[i][j] = -1;

    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));

    for (int c = 1; c <= m; c++)
        for (auto [x1, y1, x2, y2, k] : vec[c])
        {
            b[x1][y1] += k; b[x2 + 1][y2 + 1] += k;
            b[x1][y2 + 1] -= k; b[x2 + 1][y1] -= k;
        }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            b[i][j] += b[i][j - 1] + b[i - 1][j] - b[i - 1][j - 1];

    for (int c = 1; c <= m; c++)
    {
        for (auto [x1, y1, x2, y2, k] : vec[c])
        {
            add(x1, y1, k);
            add(x2 + 1, y2 + 1, k);
            add(x1, y2 + 1, -k);
            add(x2 + 1, y1, -k);
        }
        
        for (auto [x, y] : p[c])
            if (query(x, y) << 1 <= b[x][y])
                ans[x][y] = -1;
        
        for (auto [x1, y1, x2, y2, k] : vec[c])
        {
            add(x1, y1, -k);
            add(x2 + 1, y2 + 1, -k);
            add(x1, y2 + 1, k);
            add(x2 + 1, y1, k);
        }
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
            cout << ans[i][j] << " ";
        cout << endl;
    }

    return 0;
}
```

---

## 作者：_AyachiNene (赞：3)

猫树分治做法。

看到绝对众数容易想到摩尔投票。容易发现摩尔投票有交换律和结合律，但是无法差分，难以用树套树做。考虑猫树分治解决一维，再用数据结构解决第二维。先考虑第一维。对于一个被当前分治的区间 $[l,r]$ 包含的区间 $[x,y]$，如果在这个区间在 $mid$ 的左边或者右边向下递归即可，只考虑跨过 $mid$ 的情况。这种情况是简单的，把这个区间在左端点和右端点各挂一个标记，再 $mid$ 两边各做一遍扫描线，用线段树维护第二维即可。最后考虑如何判断是否存在绝对众数，直接按颜色做扫描线用二维树状数组和前缀和判下就行了。
# Code：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
namespace IO
{
	char buff[1<<21],*p1=buff,*p2=buff;
	char getch(){return p1==p2&&(p2=((p1=buff)+fread(buff,1,1<<21,stdin)),p1==p2)?EOF:*p1++;}
	template<typename T>void read(T &x){char ch=getch();int fl=1;x=0;while(ch>'9'||ch<'0'){if(ch=='-')fl=-1;ch=getch();}while(ch<='9'&&ch>='0'){x=x*10+ch-48;ch=getch();}x*=fl;}
	template<typename T>void read_s(T &x){x="";char ch=getch();while(!(ch>='a'&&ch<='z')&&!(ch>='A'&&ch<='Z'))ch=getch();while((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')){x+=ch;ch=getch();}}
	template<typename T,typename ...Args>void read(T &x,Args& ...args){read(x);read(args...);}
	char obuf[1<<21],*p3=obuf;
	void putch(char ch) {if(p3-obuf<(1<<21))*p3++=ch;else fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=ch;}
	char ch[100];
	template<typename T>void write(T x) {if(!x)return putch('0');if(x<0)putch('-'),x*=-1;int top=0;while(x)ch[++top]=x%10+48,x/=10;while(top)putch(ch[top]),top--;}
	template<typename T,typename ...Args>void write(T x,Args ...args) {write(x);putch(' ');write(args...);}
	void put(string s){for(int i=0;i<s.size();i++)putch(s[i]);}
	void flush(){fwrite(obuf,p3-obuf,1,stdout);}
}
using namespace IO;
int n,m;
vector<pair<int,int> >pos[500005];
#define fi first
#define se second
struct Aoko
{
	int col;
	ll cnt;
	Aoko operator+(const Aoko &a)const
	{
		if(col==a.col) return (Aoko){col,cnt+a.cnt};
		if(cnt<a.cnt) return (Aoko){a.col,a.cnt-cnt};
		return (Aoko){col,cnt-a.cnt};
	}
}ans[1005][1005];
struct Soyo{int xl,xr,yl,yr;Aoko val;};
namespace Shiki
{
	#define mid (l+r>>1)
	#define ls (root<<1)
	#define rs (root<<1|1)
	Aoko t[1005<<2];
	void down(int root)
	{
		t[ls]=t[ls]+t[root];t[rs]=t[rs]+t[root];
		t[root].col=t[root].cnt=0;
	}
	void insert(int x,int y,Aoko v,int root=1,int l=1,int r=n)
	{
		if(l>=x&&r<=y) return t[root]=t[root]+v,void();
		down(root);
		if(x<=mid) insert(x,y,v,ls,l,mid);
		if(y>mid) insert(x,y,v,rs,mid+1,r);
	}
	void print(int p,int root=1,int l=1,int r=n)
	{
		if(l==r) return ans[p][l]=ans[p][l]+t[root],void();
		down(root);
		print(p,ls,l,mid);print(p,rs,mid+1,r);
	}
	void init(int root=1,int l=1,int r=n)
	{
		t[root].col=t[root].cnt=0;
		if(l==r) return;
		init(ls,l,mid);init(rs,mid+1,r);
	}
	vector<Soyo>ql[1005],qr[1005];
	void solve(int l,int r,vector<Soyo>v)
	{
		if(l==r)
		{
			init();
			for(Soyo i:v) insert(i.yl,i.yr,i.val);
			print(l);
			return;
		}
		vector<Soyo>vl,vr;
		for(int i=l;i<=r;i++) ql[i].clear(),qr[i].clear();
		for(Soyo i:v) 
		{
			if(i.xr<=mid) vl.push_back(i);
			else if(i.xl>mid) vr.push_back(i);
			else ql[i.xl].push_back(i),qr[i.xr].push_back(i);
		}
		init();
		for(int i=l;i<=mid;i++)
		{
			for(Soyo j:ql[i]) insert(j.yl,j.yr,j.val);
			print(i);
		}
		init();
		for(int i=r;i>mid;i--)
		{
			for(Soyo j:qr[i]) insert(j.yl,j.yr,j.val);
			print(i);
		}
		solve(l,mid,vl);solve(mid+1,r,vr);
	}
}
namespace Oblivions
{
	ll t[1005][1005];
	inline int lowbit(int x){return x&-x;}
	inline void Add(int x,int y,int v)
	{
		for(;x<=n;x+=lowbit(x))
			for(int i=y;i<=n;i+=lowbit(i)) t[x][i]+=v;
	}
	inline ll query(int x,int y)
	{
		ll res=0;
		for(;x;x-=lowbit(x))
			for(int i=y;i;i-=lowbit(i)) res+=t[x][i];
		return res;
	}
	inline void add(int x,int y,int x2,int y2,int v){Add(x,y,v);Add(x,y2+1,-v);Add(x2+1,y,-v);Add(x2+1,y2+1,v);}
}
ll sum[1005][1005];
int x[500005],y[500005],x2[500005],y2[500005],k[500005];
vector<int>q[500005];
signed main()
{
//	freopen("P11882_4.in","r",stdin);
//	freopen(".out","w",stdout);
	read(n,m);
	vector<Soyo>tmp;
	for(int i=1;i<=m;i++)
	{
		int c;read(x[i],y[i],x2[i],y2[i],c,k[i]);
		tmp.push_back((Soyo){x[i],x2[i],y[i],y2[i],(Aoko){c,k[i]}});
		q[c].push_back(i);
		sum[x[i]][y[i]]+=k[i];sum[x[i]][y2[i]+1]-=k[i];sum[x2[i]+1][y[i]]-=k[i];sum[x2[i]+1][y2[i]+1]+=k[i];
	}
	Shiki::solve(1,n,tmp);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++) sum[i][j]+=sum[i][j-1]+sum[i-1][j]-sum[i-1][j-1],pos[ans[i][j].col].push_back({i,j});
	for(int i=0;i<=m;i++)
	{
		for(int id:q[i]) Oblivions::add(x[id],y[id],x2[id],y2[id],k[id]);
		for(pair<int,int>p:pos[i]) ans[p.fi][p.se].col=Oblivions::query(p.fi,p.se)*2>sum[p.fi][p.se]?i:-1;
		for(int id:q[i]) Oblivions::add(x[id],y[id],x2[id],y2[id],-k[id]);
	}
	for(int i=1;i<=n;i++,putch('\n'))
		for(int j=1;j<=n;j++) write(ans[i][j].col),putch(' ');
	flush();
	return 0;
}
/*
5 1
1 1 3 5 1 3
*/
```

---

## 作者：kevinZ99 (赞：1)

# Subtask 2
非常简单我们直接开 20 个二维数组，然后修改的时候进行差分，最后判断一下哪一个大一些即可。

# Solution
可以延续上述的做法，首先我们要求的是**绝对众数**因此我们可以将颜色做拆位，一位一位的进行处理，由于必须要大于一半才能算绝对众数，所以仅仅考虑一位是没有影响的，因此我们直接沿用上述的做法即可，但是由于我们采用的是摩尔投票的方式所以最后需要使用二维树状数组进行验证。

# Code

```cpp
//Author:Kevin Z K Y
#include <bits/stdc++.h>
#define up(a,b,c) for(ll (a)=(b);(a)<=(c);(a)++)
#define dn(a,b,c) for(ll (a)=(b);(a)>=(c);(a)--)
#define fst first
#define sed second
using namespace std;
using us = unsigned short ;using ldb = long double ;
using ull = unsigned long long ;using ui = unsigned int ;
using ll = long long ;using hint = __int128 ;
using pii = pair<int,int> ;using pll = pair<ll,ll> ;
using pil = pair<int,ll> ;using vpil = vector<pil> ;
using vi = vector<int> ;using vl = vector<ll> ;
using vpi = vector<pii> ;using vpl = vector<pll> ;
using db = double ;namespace mystl{
	#define gc() getchar()
	#define Max(x,y) (((x)>(y))?(x):(y))
	#define Min(x,y) (((x)<(y))?(x):(y))
	#define Abs(x) (((x)<0)?(-(x)):(x))
	#define putline() cout<<"------------------------------\n"
	ll qpow(ll a , ll b , ll p) { if (a==0ll) return 0ll; ll c=1ll;
		while(b) { if(b & 1) c=a*c%p; a=a*a%p; b>>=1; } return c; }
	void exgcd(ll a,ll b,ll &cx,ll &cy){if(a % b ==0)cx = 0,cy = 1;
		else { exgcd( b , a % b , cy , cx) ; cy -= a / b * cx ; } }
	ll lcm ( ll x , ll y ){return x / std :: __gcd( x , y ) * y ; }
	template<typename T>void read(T&x) {x=0; bool f=false; char ch;
		ch = gc(); while(ch<'0'||ch>'9') f |= ( ch=='-') , ch=gc();
		while(ch>='0'&&ch<='9') x=x*10+ch-'0' , ch=gc(); x=f?-x:x;}
	template<typename T>void write(T x){char s[40];short d=0;T y=x;
		if(x<0) putchar('-'),y=-y;if(x==0){ putchar('0'); return; }
		while(y){s[++d]=y%10+'0';y/=10;}while(d>0)putchar(s[d--]);}
	template<typename T>void wris(T x,char c){write(x);putchar(c);}
}using namespace mystl;
const db eps=1e-6,PI=acos(-1);
namespace my{
	const int N=(int)(1005),QM=(int)(5e5+5);
	const int inf=(int)(1e9);
	int n,Q;
	struct Question{
		int x1,y1,x2,y2,c;
		ll k;
	}qu[QM];
	vector<Question>qc[QM];
	vector<pii>pos[QM];
	ll s[N][N][2];
	int ans[N][N];
	void init(){
		up(i,0,n+1)up(j,0,n+1)s[i][j][0]=s[i][j][1]=0;
	}
	void add(int x1,int y1,int x2,int y2,int c,ll k){
		s[x2+1][y2+1][c]+=k;s[x1][y1][c]+=k;
		s[x2+1][y1][c]-=k;s[x1][y2+1][c]-=k;
	}
	int Box[QM];
	vi have;
	ll c[N][N];
	int lb(int x){
		return x&(-x);
	}void add2d(int x,int y,ll v){
		for(int i=x;i<=n;i+=lb(i))for(int j=y;j<=n;j+=lb(j))c[i][j]+=v;
	}ll ask2d(int x,int y){
		ll z=0;for(int i=x;i;i-=lb(i))for(int j=y;j;j-=lb(j))z+=c[i][j];
		return z;
	}void addk(int x1,int y1,int x2,int y2,ll k){
		add2d(x2+1,y2+1,k);add2d(x1,y1,k);
		add2d(x2+1,y1,-k);add2d(x1,y2+1,-k);
	}
	void solve(){
		cin>>n>>Q;up(i,1,n)up(j,1,n)ans[i][j]=-1;
		up(i,1,Q)cin>>qu[i].x1>>qu[i].y1>>qu[i].x2>>qu[i].y2>>qu[i].c>>qu[i].k;
		up(i,1,Q)qc[qu[i].c].push_back(qu[i]);
		up(bit,0,19){init();
			up(i,1,Q)
				add(qu[i].x1,qu[i].y1,qu[i].x2,qu[i].y2,(qu[i].c>>bit)&1,qu[i].k);
			up(i,1,n)up(j,1,n)
				s[i][j][0]+=s[i][j-1][0]+s[i-1][j][0]-s[i-1][j-1][0],
				s[i][j][1]+=s[i][j-1][1]+s[i-1][j][1]-s[i-1][j-1][1];
			up(i,1,n)up(j,1,n)
				if(s[i][j][1]>s[i][j][0])ans[i][j]+=(1<<bit)+(ans[i][j]==-1);
		}
		up(i,1,n)up(j,1,n)
			if(ans[i][j]>=1&&ans[i][j]<=Q){
				pos[ans[i][j]].push_back({i,j});
				if(!Box[ans[i][j]])Box[ans[i][j]]++,have.push_back(ans[i][j]);
			}else ans[i][j]=-1; 
		init();
		up(i,1,Q)add(qu[i].x1,qu[i].y1,qu[i].x2,qu[i].y2,0,qu[i].k); // tot
		up(i,1,n)up(j,1,n)s[i][j][0]+=s[i-1][j][0]+s[i][j-1][0]-s[i-1][j-1][0];
		for(int&v:have){
			for(Question&p:qc[v])addk(p.x1,p.y1,p.x2,p.y2,p.k);
			for(pii&p:pos[v]){
				ll d=ask2d(p.fst,p.sed);
				if((d<<1)<=s[p.fst][p.sed][0])ans[p.fst][p.sed]=-1;	
			}for(Question&p:qc[v])addk(p.x1,p.y1,p.x2,p.y2,-p.k);
		}
		up(i,1,n)up(j,1,n)cout<<ans[i][j]<<" \n"[j==n];
	}
}
signed main(){
//  freopen("","r",stdin);
//  freopen("","w",stdout);
	ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
	int _=1;while(_--)my::solve();return 0;
}
/*
将颜色按照二进制位进行拆分，即 c -> 2(b1 b2 b3...b[logn]) 
超过一半即可。
修改：差分 ， 查询前缀和即可。
验证： 树状数组
*/
```

---

## 作者：Nephren_Sakura (赞：0)

想到做法不太难，但实现搞了我半天，最后还被卡常了。（个人线段树写法常数比较大，最后改成了正常线段树才过的）

看到绝对众数，套路性的想到摩尔投票法。考虑如何维护摩尔投票。

因为我们是先做完所有操作再查询，我们拍一颗二维线段树上去，这颗二维线段树维护所有**完全包含了**当前区间的操作进行摩尔投票后的结果。

然后当你进行修改的时候，和正常线段树一样的跑，如果有一个区间**被完全包含**，就直接和这个区间上原本的结果进行合并。

单点查询就是你把路径上的所有结果拉出来再来一次摩尔投票，往下找的时候递归即可。

然后摩尔投票维护完了还有检查，这部分你弄个二维树状数组，对每个颜色做一下就行，注意清空。

本做法常数巨大，建议谨慎食用。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q,id[1005][1005],ans[1005][1005];long long sum[1005][1005];//,SUM[1005][1005];
struct node{int x,y,X,Y,c,k;}que[1000005];
vector<pair<int,int> > v[1000005];
vector<node> cz[1000005];
struct BIT{
	long long t[1005][1005];
	void update(int x,int y,long long val){
		for(int i=x; i<=n; i+=(i&-i)) for(int j=y; j<=n; j+=(j&-j)) t[i][j]+=val;
		return;
	}
	long long query(int x,int y){
		long long ans=0;
		for(int i=x; i; i-=(i&-i)) for(int j=y; j; j-=(j&-j)) ans+=t[i][j];
		return ans;
	}
	void update(int x,int y,int X,int Y,int val){update(X+1,Y+1,val),update(X+1,y,-val),update(x,Y+1,-val),update(x,y,val);return;}
}T;
struct Segmenttree1{
	int qx,qy;long long val;int pos;
	struct node{long long val;int pos;}t[4005];
	void addtag(int cur,long long val,int pos){
		if(t[cur].pos==pos) t[cur]=(node){t[cur].val+val,pos};
		else if(val<t[cur].val) t[cur].val-=val;
		else t[cur]=(node){val-t[cur].val,pos};
		return;
	}//维护摩尔投票的结果
	void pushdown(int cur){addtag(cur<<1,t[cur].val,t[cur].pos),addtag(cur<<1|1,t[cur].val,t[cur].pos),t[cur].val=t[cur].pos=0;return;}
	void update(int cur,int lt,int rt){
		if(lt>=qx&&rt<=qy) {return addtag(cur,val,pos);}//区间被包含，直接合并
		int mid=lt+rt>>1;pushdown(cur);
		if(mid>=qx) update(cur<<1,lt,mid);
		if(mid+1<=qy) update(cur<<1|1,mid+1,rt);
		return;
	}
	pair<long long,int> query(int cur,int lt,int rt){
		// cout<<"what"<<cur<<' '<<lt<<' '<<rt<<' '<<qx<<'\n';
		if(lt==rt&&rt==qx) {return make_pair(t[cur].val,t[cur].pos);}
		int mid=lt+rt>>1;pushdown(cur);
		if(mid>=qx) return query(cur<<1,lt,mid);
		return query(cur<<1|1,mid+1,rt);
	}
};
struct Segmenttree2{
	int qx1,qy1,qx2,qy2,pos;long long val;
	Segmenttree1 T[4005];
	void update(int cur,int lt,int rt){
		if(lt>=qx1&&rt<=qy1) {T[cur].qx=qx2,T[cur].qy=qy2,T[cur].val=val,T[cur].pos=pos;return T[cur].update(1,1,n);}//完全包含了，直接合并。
		int mid=lt+rt>>1;
		if(mid>=qx1) update(cur<<1,lt,mid);
		if(mid+1<=qy1) update(cur<<1|1,mid+1,rt);
		return;
	}
	pair<long long,int> query(int cur,int lt,int rt){
		if(lt==rt&&rt==qx1) {T[cur].qx=qy1;return T[cur].query(1,1,n);}
		T[cur].qx=qy1;
		pair<long long,int> p=T[cur].query(1,1,n);
		int mid=lt+rt>>1;
		pair<long long,int> nxt;
		if(mid>=qx1) nxt=query(cur<<1,lt,mid);
		else nxt=query(cur<<1|1,mid+1,rt);
		if(p.second==nxt.second) return make_pair(p.first+nxt.first,p.second);
		else if(p.first>nxt.first) return make_pair(p.first-nxt.first,p.second);
		else return make_pair(nxt.first-p.first,nxt.second);
	}
}T2;
void init(){
	for(int i=1; i<=q; i++){
		T2.qx1=que[i].x,T2.qy1=que[i].X,T2.qx2=que[i].y,T2.qy2=que[i].Y,T2.val=que[i].k,T2.pos=que[i].c;
		T2.update(1,1,n);
	}
	// cout<<T2.query(1,1,n,1,1).second;
	for(int i=1; i<=n; i++) for(int j=1; j<=n; j++){T2.qx1=i,T2.qy1=j;id[i][j]=T2.query(1,1,n).second;}
	return;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>q;
	for(int i=1; i<=q; i++){
		cin>>que[i].x>>que[i].y>>que[i].X>>que[i].Y>>que[i].c>>que[i].k;
		sum[que[i].X+1][que[i].Y+1]+=que[i].k;
		sum[que[i].x][que[i].Y+1]-=que[i].k;
		sum[que[i].X+1][que[i].y]-=que[i].k;
		sum[que[i].x][que[i].y]+=que[i].k;
	}
	for(int i=1; i<=n; i++) for(int j=1; j<=n; j++) sum[i][j]+=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];
	init();
	// return 0;
	memset(ans,-1,sizeof ans);
	for(int i=1; i<=n; i++) for(int j=1; j<=n; j++) v[id[i][j]].push_back({i,j});
	for(int i=1; i<=q; i++) cz[que[i].c].push_back(que[i]);
	for(int col=1; col<=q; col++){
		for(auto p:cz[col]) T.update(p.x,p.y,p.X,p.Y,p.k);
		for(auto p:v[col]){
			if(T.query(p.first,p.second)*2>sum[p.first][p.second]) ans[p.first][p.second]=col;
			else ans[p.first][p.second]=-1;
		}
		for(auto p:cz[col]) T.update(p.x,p.y,p.X,p.Y,-p.k);
	}
	for(int i=1; i<=n; i++,cout<<'\n') for(int j=1; j<=n; j++) cout<<ans[i][j]<<' ';
	return 0;
}
```

---

