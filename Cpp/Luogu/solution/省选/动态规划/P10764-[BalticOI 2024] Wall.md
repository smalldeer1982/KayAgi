# [BalticOI 2024] Wall

## 题目背景

翻译自 [BalticOI 2024 Day2 T3](https://boi2024.lmio.lt/tasks/d2-wall-statement.pdf)。

## 题目描述

你想要修建一个围墙，它是由 $N$ 个墙组成的，每个墙 $i$ 可能的高度是 $a_i$ 或 $b_i$，对于每个可能的围墙序列 $h$，你想要求出它的积水量之和。

例如下图展示了一个 $N = 10$，围墙高度分别为 $4, 2, 1, 8, 6, 2, 7, 1, 2, 3$ 的例子，它的实际积水高度是 $4, 4, 4, 8, 7, 7, 7, 3, 3, 3$。

![](https://cdn.luogu.com.cn/upload/image_hosting/p18f84ua.png)

对于某个 $i$ 雨后应有的水位 $H$，需要满足存在两个数 $l,r\ (l \leq i,r\geq i)$，有 $h_l \geq H,h_r \geq H$，且 $H$ 最大，此时 $i$ 的积水量为 $H-h_i$。

输出所有可能情况的积水量之和对 $10^9 +7$ 取模的值。

## 说明/提示

对于样例一，$(2,1,1,2)$ 的情况存在 $2$ 的积水量，$(1,2,1,2)$，$(2,1,2,1)$，$(2,1,2,2)$，$(2,2,1,2)$ 分别存在 $1$ 的积水量。

| 子任务编号 | 特殊性质 | 分值 |
| :-----------: | :----------- | :-----------: |
| $1$ | $N \leq 20$ | $8$ |
| $2$ | $N \leq 100$ 且 $a_i,b_i \leq 1000$ | $17$ |
| $3$ | $N \leq 10000$ 且 $a_i,b_i \leq 1000$ | $19$ |
| $4$ | $N \leq 10000$ | $14$ |
| $5$ | $a_i,b_i \leq 2$ | $12$ |
| $6$ | 无特殊性质 | $30$ |


对于所有数据 $1 \leq N \leq5 \times10^5$，$1 \leq a_i,b_i \leq 10^9$ 且对于 每个 $1 \leq i \leq n$，有 $a_i \neq b_i$。

## 样例 #1

### 输入

```
4
1 1 1 1
2 2 2 2```

### 输出

```
6```

## 样例 #2

### 输入

```
10
1 2 3 4 5 6 7 8 9 10
10 9 8 7 6 5 4 3 2 1
```

### 输出

```
21116```

# 题解

## 作者：Petit_Souris (赞：13)

题面已经告诉我们了：$i$ 处的积水为 $H-h_i$，其中 $H$ 为 $i$ 左侧的最大值和 $i$ 右侧的最大值中的较小值。我们分成 $\sum H$ 和 $\sum h_i$ 两部分计算。

$\sum h_i$ 是好计算的，这就是 $2^{n-1}\sum (a_i+b_i)$。（你可以考虑计算每个位置的贡献）

对于 $\sum H$，我们不妨采用这样一种方式计算：把 $H$ 拆成 $\sum\limits_{X=1}^{\infty}[H\ge X]$，也就是枚举 $X$，计算每个位置 $H\ge X$ 的方案数之和。

我们对 $X$ 从大到小做扫描线，将 $\ge X$ 的设为 $1$，$\le X$ 的设为 $0$。这样每个位置就有三种状态：$a_i,b_i$ 中恰好有 $0/1/2$ 个 $1$。我们现在要给每个位置选一个 $a_i$ 或 $b_i$，并统计有多少位置 $i$ 满足 $[1,i]$ 和 $[i,n]$ 中都至少有一个 $1$，对这样的数量求和。

我们分类讨论一下：当存在至少一个位置有 $2$ 个 $1$ 的时候，设最左边的为 $L$，最右边的为 $R$，那么 $[L,R]$ 中的位置任意填都可以满足，$[1,L-1]$ 中的只需要满足前缀中有 $1$，$[R+1,n]$ 中的只需要满足后缀中有 $1$。

假设正在统计 $x\in [1,L-1]$ 的贡献，设 $[1,x-1]$ 中有 $p$ 个位置有 $1$ 个 $1$，那么方案数为 $(2^p-1)2^{x-p}=2^x-2^{x-p}$。前面的这个贡献是固定的，后面这个贡献每当 $x$ 前面出现 $1$ 的时候就会除以 $2$，可以用一个线段树维护，当扫描线将某些 $0$ 修改成 $1$ 的时候做一个后缀乘。$[R+1,n]$ 的贡献同理。

当不存在位置有 $2$ 个 $1$ 的时候，设 $x$ 前面有 $cL$ 个 $1$，右边有 $cR$ 个 $1$，那么贡献为 $(2^{cL}-1)(2^{cR}-1)2^{n-cL-cR}$，后面这个是个定值（扫到目前的 $X$ 对于所有 $x$ 来说 $cL+cR$ 都相等），前面的拆开后也可以类似上面一部分用两棵线段树维护。

但是发现如果当前位置是 $1$，这个贡献是有问题的，因为自己选了 $1$ 就同时满足了前缀和后缀，稍微分类讨论一下就可以了。

总时间复杂度 $\mathcal O(n\log n)$。

```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
#define pii pair<ll,ll>
#define rep(i,a,b) for(ll i=(a);i<=(b);++i)
#define per(i,a,b) for(ll i=(a);i>=(b);--i)
using namespace std;
ll read(){
	ll x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
void write(ll x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)write(x/10);
	putchar(x%10+'0');
}
const ll N=5e5+9,Mod=1e9+7,inv2=(Mod+1)/2;
ll n,a[N],b[N],L,R,cnt[N],tmp[N<<1],k,pw2[N],ta[N],tb[N],pre[N],bin[N],pre2[N];
ll pw(ll x,ll p){
    ll res=1;
    while(p){
        if(p&1)res=res*x%Mod;
        x=x*x%Mod,p>>=1;
    }
    return res;
}
struct Tree{
    ll tr[N<<2],tag[N<<2];
    void Pushup(ll x){
        tr[x]=(tr[x<<1]+tr[x<<1|1])%Mod;
    }
    void Build(ll x,ll l,ll r,ll v){
        tag[x]=1;
        if(l==r){
            tr[x]=v;
            return ;
        }
        ll mid=(l+r)>>1;
        Build(x<<1,l,mid,v);
        Build(x<<1|1,mid+1,r,v);
        Pushup(x);
    }
    void Pushtag(ll x,ll v){
        tr[x]=tr[x]*v%Mod;
        tag[x]=tag[x]*v%Mod;
    }
    void Pushdown(ll x){
        if(tag[x]==1)return ;
        Pushtag(x<<1,tag[x]);
        Pushtag(x<<1|1,tag[x]);
        tag[x]=1;
    }
    void Upd(ll x,ll l,ll r,ll ql,ll qr,ll v){
        if(ql>qr)return ;
        if(l>qr||r<ql)return ;
        if(ql<=l&&r<=qr){
            Pushtag(x,v);
            return ;
        }
        ll mid=(l+r)>>1;
        Pushdown(x);
        Upd(x<<1,l,mid,ql,qr,v);
        Upd(x<<1|1,mid+1,r,ql,qr,v);
        Pushup(x);
    }
    void Cov(ll x,ll l,ll r,ll u,ll v){
        if(l>u||r<u)return ;
        if(l==r){
            tr[x]=v;
            return ;
        }
        ll mid=(l+r)>>1;
        Pushdown(x);
        Cov(x<<1,l,mid,u,v);
        Cov(x<<1|1,mid+1,r,u,v);
        Pushup(x);
    }
    ll Query(ll x,ll l,ll r,ll ql,ll qr){
        if(l>qr||r<ql||ql>qr)return 0;
        if(ql<=l&&r<=qr)return tr[x];
        ll mid=(l+r)>>1;
        Pushdown(x);
        return (Query(x<<1,l,mid,ql,qr)+Query(x<<1|1,mid+1,r,ql,qr))%Mod;
    }
}T1,T2;
vector<ll>vec[N<<1];
bool Med;
int main(){
    // freopen("wall.in","r",stdin);
    // freopen("wall.out","w",stdout);
    n=read();
    rep(i,1,n)a[i]=read();
    rep(i,1,n)b[i]=read();
    rep(i,1,n)tmp[i]=a[i];
    rep(i,1,n)tmp[i+n]=b[i];
    pw2[0]=1;
    rep(i,1,n)pw2[i]=pw2[i-1]*2%Mod;
    sort(tmp+1,tmp+(n<<1)+1);
    k=unique(tmp+1,tmp+(n<<1)+1)-tmp-1;
    rep(i,1,n){
        ta[i]=lower_bound(tmp+1,tmp+k+1,a[i])-tmp;
        tb[i]=lower_bound(tmp+1,tmp+k+1,b[i])-tmp;
    }
    T1.Build(1,1,n,pw2[n]),T2.Build(1,1,n,pw2[n]);
    rep(i,1,n){
        vec[ta[i]].push_back(i);
        vec[tb[i]].push_back(i);
    }
    rep(i,0,n-1)pre[i]=((pw2[n]+pw2[n-i])%Mod*(i+1)%Mod-2*pw2[n-i]%Mod*(pw2[i+1]-1)%Mod+Mod)%Mod;
    rep(i,0,n-1)pre2[i]=((pw2[n]+pw2[n-i-1])%Mod*(i+1)%Mod-2*pw2[n-i]%Mod*(pw2[i+1]-1)%Mod+Mod)%Mod;
    ll ans=0,c1=0;
    per(i,k,1){
        for(ll x:vec[i]){
            bin[x]++;
            if(bin[x]==2){
                if(!L){
                    L=R=x;
                    T1.Build(1,1,n,pw2[n]);
                    T2.Build(1,1,n,pw2[n]);
                    rep(j,1,L){
                        if(bin[j]==1)T1.Upd(1,1,n,j,L,inv2);
                    }
                    rep(j,R+1,n){
                        if(bin[j]==1)T2.Upd(1,1,n,R,j,inv2);
                    }
                }
                else{
                    L=min(L,x);
                    R=max(R,x);
                }
            }
            else {
                c1++;
                if(!L){
                    T1.Upd(1,1,n,x+1,n,inv2);
                    T2.Upd(1,1,n,1,x-1,inv2);
                }
                else {
                    if(x<=L)T1.Upd(1,1,n,x,L,inv2);
                    if(x>=R)T2.Upd(1,1,n,R,x,inv2);
                }
            }
        }
        ll len=(i==1?tmp[i]:tmp[i]-tmp[i-1])%Mod;
        // cout<<"current "<<len<<" "<<L<<" "<<R<<endl;
        if(!L){
            ll coef=((pw2[n]+pw2[n-c1]+Mod)*n%Mod-T1.tr[1]-T2.tr[1]+Mod*2)%Mod;
            ll qd=pre[c1-1],nqd=pre2[c1-1];
            coef=(coef-nqd+qd*inv2%Mod+c1*pw2[n-1]%Mod+Mod)%Mod;
            // cout<<coef<<endl;
            ans=(ans+coef*len)%Mod;
        }
        else {
            ll coef=(pw2[n]*n%Mod-T1.Query(1,1,n,1,L-1)-T2.Query(1,1,n,R+1,n)+Mod*2)%Mod;
            // cout<<coef<<endl;
            ans=(ans+coef*len)%Mod;
        }
    }
    rep(i,1,n)ans=(ans-pw2[n-1]*(a[i]+b[i])%Mod+Mod)%Mod;
    write(ans);
	return 0;
}
```

---

## 作者：喵仔牛奶 (赞：7)

tag：数数，线段树

每一步都不难，如果积累了较多经验可以顺畅地做出来。

# Solution

记 $p_i,s_i$ 分别表示 $[1,i],[i,n]$ 的 $h_i$ 的最大值。可以发现位置 $i$ 的积水量 $H_i=\min(p_i,s_i)-h_i$。

$\min$ 里面套个最大值非常麻烦，我们把 $\min$ 拆掉：
$$
\begin{aligned}
H_i&=\min(p_i,s_i)-h_i\\
&=p_i+s_i-\max(p_i,s_i)-h_i\\
&=p_i+s_i-p_n-h_i
\end{aligned}
$$

我们对每个部分分开算。

先考虑 $h_i$ 的和，答案显然为 $2^{n-1}\sum_{i=1}^{n}(a_i+b_i)$。

接着考虑 $p_i$ 的贡献和。因为数可能相同，我们先规定有多个相同的前缀最大值只把最前面的当作前缀最大值。每个位置对贡献它的前缀最大值，我们枚举贡献的位置 $j$ 与它的前缀最大值的位置 $i$，再枚举取了 $a_i$ 还是 $b_i$（记取了 $h_i$），计算有多少种方案使得 $j$ 贡献了 $h_i$。

对于 $k<i$，需要保证 $h_k<h_i$，方案数为 $\prod_{k=1}^{i-1}([a_k<h_i]+[b_k<h_i])$。对于 $i<k\le j$，需要保证 $h_k\le h_i$，方案数为 $\prod_{k=i+1}^{j}([a_k\le h_i]+[b_k\le h_i])$。对于 $k>j$，可以随便选，方案数为 $2^{n-j}$。故 $(i,j,h_i)$ 的总贡献为：
$$h_i\times 2^{n-j}\times\left(\prod_{k=1}^{i-1}[a_k<h_i]+[b_k<h_i]\right)\times\left(\prod_{k=i+1}^{j}[a_k\le h_i]+[b_k\le h_i]\right)$$

$s_i$ 的贡献就是翻转序列后 $p_i$ 的贡献。$p_n$ 的贡献只需要枚举 $p_n$ 的位置与值，计算方法类似。这样我们就得到了 $\mathcal{O}(n^2)$ 做法。

```cpp
#define REP(i, l, r) for (int i = (l); i <= (r); ++ i)
#define DEP(i, r, l) for (int i = (r); i >= (l); -- i)
#define fi first
#define se second
#define pb emplace_back
#define mems(x, v) memset((x), (v), sizeof(x))
#define SZ(x) (int)(x).size()
#define ALL(x) (x).begin(), (x).end()
... // modint
namespace Milkcat {
	typedef long long LL;
	typedef pair<LL, LL> pii;
	const int N = 1e6 + 5, mod = 1e9 + 7;
	typedef Math::Mint<mod> MI;
	int n, a[N], b[N]; MI rs, pw[N];
	void solve(int n, int* a, int* b) {
		REP(i, 1, n) for (int x : {a[i], b[i]}) {
			MI coe = 1;
			REP(j, 1, i - 1) coe *= (a[j] < x) + (b[j] < x);
			rs += coe * pw[n - i] * x; // 特判 i=j
			REP(j, i + 1, n) {
				coe *= (a[j] <= x) + (b[j] <= x);
				rs += coe * x * pw[n - j];
			}
		}
	}
	int main() {
		cin >> n, pw[0] = 1;
		REP(i, 1, n) cin >> a[i];
		REP(i, 1, n) cin >> b[i];
		REP(i, 1, n) pw[i] = pw[i - 1] * 2;
		REP(i, 1, n)
			rs -= pw[n - 1] * (a[i] + b[i]);
		REP(i, 1, n) for (int x : {a[i], b[i]}) {
			MI coe = 1;
			REP(j, 1, n) {
				if (j < i) coe *= (a[j] < x) + (b[j] < x);
				if (j > i) coe *= (a[j] <= x) + (b[j] <= x);
			}
			rs -= coe * x * n;
		} // 计算 p[n] 的贡献
		solve(n, a, b);
		reverse(a + 1, a + 1 + n), reverse(b + 1, b + 1 + n);
		solve(n, a, b);
		cout << rs << '\n';
		return 0; 
	}
}
```

考虑优化。先来优化 `solve` 部分。仍然枚举 $i,h_i$，你发现枚举 $j$ 的过程相当于要计算两个值：
$$\prod_{k=1}^{i-1}([a_k<h_i]+[b_k<h_i])$$
$$\sum_{j=i+1}^{n}2^{n-j}\prod_{k=i+1}^{j}([a_k\le h_i]+[b_k\le h_i])$$

我们它看作两次询问，给出 $i,x$，计算上面的值。我们求第一个值时将 $h_i$ 减一，将 $<$ 变为 $\le$。

令 $w(i,x)=[a_i\le x]+[b_i\le x]$。这个形式相当于给出 $l,r,x$，求：
$$\prod_{i=l}^{r}w(i,x)$$
$$\sum_{i=l}^{r}v_i\prod_{j=l}^{i}w(i,x)$$

因为有 $[a_k\le h_i]$ 这样的东西，我们记录下所有询问，然后按 $x$ 从小到大排序，每次将所有变化的 $w(i,x)$ 修改。可以发现一个数最多变两次。

接着问题就变成单点修改，区间求乘积，区间求前缀积乘权值之和，用线段树维护即可。

至于求 $p_n$，在它的式子也是这个形式，在计算 $p_i$ 贡献时一并求即可。

总复杂度 $\mathcal{O}(n\log n)$。

# Code

```cpp
#define REP(i, l, r) for (int i = (l); i <= (r); ++ i)
#define DEP(i, r, l) for (int i = (r); i >= (l); -- i)
#define fi first
#define se second
#define pb emplace_back
#define mems(x, v) memset((x), (v), sizeof(x))
#define SZ(x) (int)(x).size()
#define ALL(x) (x).begin(), (x).end()
... // modint
namespace Milkcat {
	typedef long long LL;
	typedef pair<LL, LL> pii;
	const int N = 3e5 + 5, mod = 1e9 + 7;
	typedef Math::Mint<mod> MI;
	int n, a[N], b[N]; MI rs, pw[N], s[N << 4];
	namespace SGT {
		struct info {
			int x; MI d, s; // x 表示下标，d 表示乘积，s 表示前缀积乘权值之和
			void set(int t, int v) { x = t, d = v, s = pw[n - t] * v; }
		} s[N << 2];
		info merge(const info& x, const info& y) { 
			return {x.x, x.d * y.d, x.s + y.s * x.d};
		}
		void upd(int p, int l, int r, int t, int x) {
			if (l == r) { s[p].set(l, x); return; }
			int mid = (l + r) >> 1;
			if (t <= mid) upd(p << 1, l, mid, t, x);
			if (t > mid) upd(p << 1 | 1, mid + 1, r, t, x);
			s[p] = merge(s[p << 1], s[p << 1 | 1]);
		}
		info ask(int p, int l, int r, int nl, int nr) {
			if (nl <= l && r <= nr) return s[p];
			int mid = (l + r) >> 1;
			if (nl <= mid && nr > mid)
				return merge(ask(p << 1, l, mid, nl, nr), ask(p << 1 | 1, mid + 1, r, nl, nr));
			if (nl <= mid) return ask(p << 1, l, mid, nl, nr);
			if (nr > mid) return ask(p << 1 | 1, mid + 1, r, nl, nr);
		}
		void build(int p, int l, int r) {
			if (l == r) return s[p].set(l, 0);
			int mid = (l + r) >> 1;
			build(p << 1, l, mid), build(p << 1 | 1, mid + 1, r);
			s[p] = merge(s[p << 1], s[p << 1 | 1]);
		}
	}
	struct Q {
		int x, l, r, t, id;
		Q(int _0, int _1, int _2, int _3, int _4) : x(_0), l(_1), r(_2), t(_3), id(_4) {}
		bool operator < (const Q& v) { return x < v.x; }
	};
	vector<tuple<int, int, int>> w;
	void solve(int n, int* a, int* b, int chk) {
		vector<Q> qry; int ct = 0;
		REP(i, 1, n) for (int x : {a[i], b[i]}) {
			qry.pb(x - 1, 1, i - 1, 1, ++ ct);
			qry.pb(x, i + 1, n, 2, ++ ct);
			if (chk) {
				qry.pb(x - 1, 1, i - 1, 1, ++ ct);
				qry.pb(x, i + 1, n, 1, ++ ct);
			} // chk=1 表示顺便求 p[n] 的贡献
		}
		int p = 0;
		SGT::build(1, 1, n), sort(ALL(qry)), ct = 0;
		for (auto t : qry) {
			while (p < SZ(w) && t.x >= get<0>(w[p])) {
				auto [x, y, z] = w[p ++];
				SGT::upd(1, 1, n, y, z);
			} // 改变点权
			if (t.l <= t.r) {
				auto x = SGT::ask(1, 1, n, t.l, t.r);
				s[t.id] = (t.t == 1 ? x.d : x.s);
			} else s[t.id] = (t.t == 1 ? 1 : 0);
		}
		REP(i, 1, n) for (int x : {a[i], b[i]}) {
			auto p = s[++ ct];
			auto q = s[++ ct];
			rs += p * (pw[n - i] + q) * x;
			if (chk) {
				p = s[++ ct], q = s[++ ct];
				rs -= p * q * x * n;
			}
		}
	}
	int main() {
		cin >> n, pw[0] = 1;
		REP(i, 1, n) cin >> a[i];
		REP(i, 1, n) cin >> b[i];
		REP(i, 1, n) pw[i] = pw[i - 1] * 2;
		REP(i, 1, n)
			rs -= pw[n - 1] * (a[i] + b[i]);
		REP(i, 1, n) {
			w.pb(min(a[i], b[i]), i, 1);
			w.pb(max(a[i], b[i]), i, 2);
		}
		sort(ALL(w)), solve(n, a, b, 1);
		reverse(a + 1, a + 1 + n), reverse(b + 1, b + 1 + n);
		for (auto &[x, y, z] : w) y = n - y + 1;
		solve(n, a, b, 0);
		cout << rs << '\n';
		return 0; 
	}
}
```

---

## 作者：cyffff (赞：5)

[$\text{Link}$](https://www.luogu.com.cn/problem/P10764)
## 题意
给你两个长为 $n$ 的序列 $a_{i,0/1}$，有 $n$ 个砖块墙，其中墙 $i$ 的高度可能为 $a_i$ 或者 $b_i$，请求出每种情况下这些墙**积水深度**的总和。

形式化地，设墙 $i$ 的高度为 $h_i$，则最终墙 $i$ 的**水面高度**为 $\displaystyle\min\left(\max_{j=1}^{i}h_j,\max_{j=i}^nh_j\right)$。

$n\le 5\times 10^5$。
## 题解
观察一下题面给的图并手玩一会可以发现前缀最大值和后缀最大值是重要的。更具体地，设某种情况下墙 $i$ 的高度为 $h_i$，设前缀最大值的位置分别为 $p_{1\sim k}$，则 $(p_i,p_{i+1})$ 内的墙的积水**水面高度**均为 $p_i$。后缀最大值是同理的。于是我们要设计某种与前缀最大值有关的状态，同时为了防止算重，对于两个相同的高度，我们令后面的大于前面的。

设 $f_{i,0/1}$ 表示 $h_i=a_{i,0/1}$ 是一个前缀最大值时前缀 $i$ 的所有情况的水面高度和，$c_{i,0/1}$ 为此时的方案数。

我们考虑如何从 $i$ 转移到 $j$，不妨以 $(i,p)$ 转移到 $(j,q)$ 为例，其中 $p,q=0/1$：
- 必须满足 $a_{i,p}\le a_{j,q}$，$\forall k\in(i,j),\min(a_{k,0},a_{k,1})<a_{i,p}$；
- 考虑 $(i,j)$ 内的方案数，令 $t=\sum_{k=i+1}^{j-1}[\max(a_{k,0},a_{k,1})<a_{i,p}]$，则 $(i,j)$ 内有 $t$ 个位置可任意选择，方案数为 $2^t$；
- 新增的水面高度为 $(j-i)a_{i,p}$。

经过一些尝试，以下标顺序转移是困难的。考虑到我们转移过程中要涉及权值比较且只能从小权值转移到大权值，于是我们不妨考虑**按值域从小到大转移**。转移中与 $i$ 相关的信息较多，我们使用**刷表法**。

我们把所有的 $a_{i,0/1}$ 排序后从小到大扫，设现在扫到 $a_{i,p}$，考虑向后更新。设 $r_i$ 表示已经扫到了几个 $a_{i,p}$，$t_i$ 表示 $[1,i]$ 有几个已经被扫到了 $2$ 次即 $\sum_{j=1}^i[r_j=2]$。用并查集找到 $i$ 后第一个 $r_j=0$ 的 $j$，则对于 $k\in(i,j],q\in[0,1]$ 且 $a_{k,q}$ 还未被扫到，$f_{k,q}\gets f_{k,q}+2^{t_k-t_i}[f_{i,p}+(k-i)a_{i,p}]$，$c_{k,q}\gets c_{k,q}\cdot 2^{t_k-t_i}c_{i,p}$。拆掉括号，分离 $i,k$ 后可以使用线段树维护。

实现中许多边界情况不需要我们考虑，比如上述式子中 $t_k$ 应为 $t_{k-1}$，但 $a_{k,q}$ 还未扫到即 $r_k\ne 2,t_k=t_{k-1}$；又如我们不需要分别处理已被扫到和未被扫到、$p,q=0/1$ 之类的问题，更具体可以参考代码。

时间复杂度 $O(n\log n)$。

参考代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
namespace IO{//by cyffff
	
}
#define pii pair<int,int>
#define mpr make_pair
#define fir first
#define sec second
const int N=5e5+10,mod=1e9+7,inv2=(mod+1)/2;
inline int add(int x,int y){ return x+y>=mod?x+y-mod:x+y; }
inline int dec(int x,int y){ return x>=y?x-y:x+mod-y; }
struct node{
	int v,p;
	inline friend bool operator<(const node &a,const node &b){
		return a.v==b.v?a.p<b.p:a.v<b.v;
	}
}a[N<<1];
struct TD{
	int a,b,c;
	TD(int A=0,int B=0,int C=0){ a=A,b=B,c=C; }
	inline friend TD operator +(const TD &a,const TD &b){
		return TD(add(a.a,b.a),add(a.b,b.b),add(a.c,b.c));
	}
	inline friend TD operator *(const TD &a,const int &b){
		return TD(1ll*a.a*b%mod,1ll*a.b*b%mod,1ll*a.c*b%mod);
	}
};
int n,pw[N],ipw[N],fa[N],c[N],f[N][2],p[N][2],g[N][2],q[N][2];
inline int find(int x){ return x==fa[x]?x:fa[x]=find(fa[x]); }
struct BIT{
	#define lowbit(x) (x&-x)
	int t[N];
	inline void clear(){
		for(int i=1;i<=n;i++)
			t[i]=0;
	}
	inline void add(int x,int v){
		for(int i=x;i<=n;i+=lowbit(i))
			t[i]+=v;
	}
	inline int query(int x){
		int s=0;
		for(int i=x;i;i-=lowbit(i))
			s+=t[i];
		return s;
	}
}T0;
struct Segment_Tree{
	#define ls (rt<<1)
	#define rs (rt<<1|1)
	TD vs[N<<2];
	int tag[N<<2];
	inline void pushadd(int rt,TD v){
		vs[rt]=vs[rt]+v*tag[rt];
	}
	inline void pushtag(int rt,int v){
		tag[rt]=1ll*tag[rt]*v%mod;
	}
	inline void pushdown(int rt){
		if(vs[rt].a||vs[rt].b||vs[rt].c){
			pushadd(ls,vs[rt]);
			pushadd(rs,vs[rt]);
			vs[rt]=TD();
		}
		if(tag[rt]!=1){
			pushtag(ls,tag[rt]);
			pushtag(rs,tag[rt]);
			tag[rt]=1;
		}
	}
	inline void build(int rt,int l,int r){
		tag[rt]=1,vs[rt]=TD();
		if(l==r){ return ; }
		int mid=l+r>>1;
		build(ls,l,mid),build(rs,mid+1,r);
	}
	inline void add(int rt,int l,int r,int L,int R,TD v){
		if(L>R) return ;
		if(L<=l&&r<=R) return pushadd(rt,v);
		pushdown(rt);
		int mid=l+r>>1;
		if(L<=mid) add(ls,l,mid,L,R,v);
		if(R>mid) add(rs,mid+1,r,L,R,v);
	}
	inline void mul(int rt,int l,int r,int L,int R,int v){
		if(L>R) return ;
		if(L<=l&&r<=R) return pushtag(rt,v);
		pushdown(rt);
		int mid=l+r>>1;
		if(L<=mid) mul(ls,l,mid,L,R,v);
		if(R>mid) mul(rs,mid+1,r,L,R,v);
	}
	inline TD query(int rt,int l,int r,int p){
		if(l==r) return vs[rt];
		pushdown(rt);
		int mid=l+r>>1;
		if(p<=mid) return query(ls,l,mid,p);
		else return query(rs,mid+1,r,p);
	}
}T;
int main(){
	n=read();
	for(int i=1;i<=n;i++)
		a[i]={read(),i};
	for(int i=1;i<=n;i++)
		a[i+n]={read(),i};
	pw[0]=ipw[0]=1;
	for(int i=1;i<=n;i++)
		pw[i]=add(pw[i-1],pw[i-1]),
		ipw[i]=1ll*inv2*ipw[i-1]%mod;
	sort(a+1,a+n*2+1);
	for(int i=0;i<=n+1;i++)
		fa[i]=i;
	T.build(1,1,n);
	T.add(1,1,n,1,1,TD(0,0,1));
	for(int i=1;i<=n*2;i++){
		int v=a[i].v,t=a[i].p;
		TD res=T.query(1,1,n,t);
		f[t][c[t]]=(res.a+1ll*t*res.b)%mod;
		p[t][c[t]]=res.c;
		int ct=T0.query(t);
		int pt=find(t+1);
		if(pt==n+1) pt=n;
		T.add(1,1,n,t+1,pt,TD(dec(f[t][c[t]],1ll*t*v%mod*p[t][c[t]]%mod),1ll*v*p[t][c[t]]%mod,p[t][c[t]])*ipw[ct]);
		c[t]++;
		if(c[t]==1) fa[t]=t+1;
		if(c[t]==2) T0.add(t,1),T.mul(1,1,n,t,n,2);
	}
	for(int i=0;i<=n+1;i++)
		fa[i]=i,c[i]=0;
	T0.clear(),T.build(1,1,n);
	T.add(1,1,n,n,n,TD(0,0,1));
	int ans=0;
	for(int i=1;i<=n*2;i++){
		int v=a[i].v,t=a[i].p;
		TD res=T.query(1,1,n,t);
		g[t][c[t]]=(res.a+1ll*t*res.b)%mod;
		q[t][c[t]]=res.c;
		ans=(ans+1ll*v*p[t][c[t]]%mod*q[t][c[t]])%mod;
		int ct=T0.query(t);
		int pt=find(t-1);
		if(pt==0) pt=1;
		T.add(1,1,n,pt,t-1,TD(add(g[t][c[t]],1ll*t*v%mod*q[t][c[t]]%mod),mod-1ll*v*q[t][c[t]]%mod,q[t][c[t]])*pw[ct]);
		c[t]++;
		if(c[t]==1) fa[t]=t-1;
		if(c[t]==2) T0.add(t,1),T.mul(1,1,n,t,n,inv2);
	}
	for(int i=1;i<=n*2;i++)
		ans=dec(ans,1ll*pw[n-1]*a[i].v%mod);
	for(int i=1;i<=n;i++)
		ans=(ans+1ll*f[i][0]*q[i][0]+1ll*p[i][0]*g[i][0]+1ll*f[i][1]*q[i][1]+1ll*p[i][1]*g[i][1])%mod;
	write(ans);
	flush();
}
```

---

## 作者：liyixin0514 (赞：2)

# [P10764 [BalticOI 2024] Wall](https://www.luogu.com.cn/problem/P10764)

## 题意

给你一面墙，第 $i$ 列的高度是 $a_i$ 或者 $b_i$。你在墙上装水。若第 $i$ 列的墙的高度是 $h_i$，位置 $i$ 的积水高度是 $H_i$ 当且仅当存在 $h_{j<i}\ge H_i$ 和 $h_{j>i} \ge H_i$。

求所有情况的 $\sum H_i-h_i$。

对 $10^9 + 7$ 取模。$n\le 5\times 10^5$。

## solution

拜谢 cjh。

暴力是枚举所有情况，然后直接枚举 $i$ 来求。

我们把枚举情况写进求和符号内，变成求合法方案数。

$$
\sum_{i=1}^n \sum_{j=1}^V H_i \times (H_i=j-h_i 的方案数)
$$

其中 $V$ 是值域最大值。

拆开贡献：

$$
\sum_{i=1}^n \sum_{j=1}^V (j 的高度处有水(h_i 处算没水)的方案数)
$$

这样一个 $H_i$ 就会在 $j=h_i+1\sim h_i+H_i$ 的时候计贡献了。

如何求 $(j 的高度处有水(h_i 处算没水)的方案数)$？

就是求左边最高的墙高 $\ge j$ 且右边最高的墙高 $\ge j$ 的方案数。

同时需要乘上一个第 $i$ 个墙选择 $a_i/b_i$ 的系数（$h_i$ 必须 $<$ j）。

即：

$$
\sum_{i=1}^{n} \sum_{j=1}^V L_{i,j} R_{i,j} ([a_i< j]+[b_i< j])
$$

其中 $L_{i,j}$ 表示 $i$ 左边的最高的墙 $\ge j$ 的方案数，$R$ 类似。

然而最高 $\ge j$ 不好算，但是 $< j$ 是好算的。

因此设 $L_{i,j}$ 表示 $i$ 左边的最高的墙 $< j$ 的方案数，$R$ 类似。

有：

$$
L_{i,j}=\prod_{k=1}^{i-1} [a_k<j]+[b_k<j]\\
R_{i,j}=\prod_{k=i+1}^{n} [a_k<j]+[b_k<j]\\
ans=\sum_{i=1}^n \sum_{j=1}^V (2^{i-1} - L_{i,j})(2^{n-i} - R_{i,j}) ([a_i< j]+[b_i< j])
$$

设 $c_i=([a_i< j]+[b_i< j])$，有：

$$
\begin{aligned}
ans & =\sum_{i=1}^n \sum_{j=1}^V (2^{i-1} - L_{i,j})(2^{n-i} - R_{i,j}) c_i\\
& = \sum_{i=1}^n \sum_{j=1}^V 2^{n-1}c_i + L_{i,j}R_{i,j}c_i - 2^{n-i} L_{i,j}c_i - 2^{i-1}R_{i,j}c_i
\end{aligned}
$$

于是我们要选择枚举 $i$ 或者 $j$，然后维护另一维。

我们选择倒序枚举 $j$。

> 事实上其他枚举方式也是可以做的，但是比较麻烦，比如枚举 $i$ 会出现除以 $0$ 的操作。其他枚举方式都是不方便做的（maybe 需要维护的信息比较复杂？），至少倒序枚举 $j$ 一定方便做。

$$
\sum_{1}^{j=V} \sum_{i=1}^n 2^{n-1}c_i + (L_{i,j}R_{i,j}c_i) - (2^{n-i} L_{i,j}c_i) - (2^{i-1}R_{i,j}c_i)
$$

我们要分别维护括号的三个东西。

使用线段树维护。

> 实际上想到使用线段树，应该是因为之前使用 $L_{i,j}$ 的时候就发现很适合使用线段树。

$$
L_{i,j}=\prod_{k=1}^{i-1} [a_k<j]+[b_k<j]\\
R_{i,j}=\prod_{k=i+1}^{n} [a_k<j]+[b_k<j]
$$

抄过来看看。

当 $j$ 变小的时候，相当于对 $L_i$ 执行后缀 $\div 2$ 或者 $\times 0$ 的操作，以及对 $R_i$ 的某些前缀执行这样的操作。

以及 $c_i$ 也会变化，单点修改就行。

这样就可以维护了。

结论：倒序枚举值域，线段树下标维护数组下标。枚举值域，对影响到的下标，对线段树执行前缀或者后缀操作。然后求线段树全局和。线段树维护三个信息。

时间复杂度 $O(n\log n)$。

写起来还是……相对……也许……可能……实际上应该是挺好写的，但是感觉推式子细节比较多？应该是我太菜了的缘故。

## code

为了保证代码可读性，所以直接开了三棵线段树，每次仅对一棵线段树操作，可能常数较大？

```cpp
#include<bits/stdc++.h>
// #define LOCAL
#define sf scanf
#define pf printf
#define rep(x,y,z) for(int x=y;x<=z;x++)
#define per(x,y,z) for(int x=y;x>=z;x--)
using namespace std;
typedef long long ll;
constexpr int N=5e5+7,mod=1e9+7,inv=500000004;
int add(int a,int b) { return a+b>=mod ? a+b-mod : a+b; }
void _add(int &a,int b) { a=add(a,b); }
ll ksm(ll a,ll b=mod-2) {
	ll s=1;
	while(b) {
		if(b&1) s=s*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return s;
}
int n,m;
struct pii {
	int a,b;
}x[N];
struct pib {
	int id;
	bool ab;
};
vector<pib> vec[N<<1];
int c[N<<1];
int val;
struct tree {
	int tr[N<<2];
	int div[N<<2];
	bool del[N<<2];
	void maketag(int u,int t1,bool t2) {
		if(t2) tr[u]=0,del[u]=1;
		else tr[u]=1ll*tr[u]*t1%mod,div[u]=1ll*div[u]*t1%mod;
	}
	void pushup(int u) {
		tr[u]=add(tr[u<<1],tr[u<<1|1]);
	}
	void pushdown(int u) {
		maketag(u<<1,div[u],del[u]), maketag(u<<1|1,div[u],del[u]);
		div[u]=1;
	}
	void build(int u,int l,int r) {
		div[u]=1;
		if(l==r) { tr[u]=val; return; }
		int mid=(l+r)>>1;
		build(u<<1,l,mid),build(u<<1|1,mid+1,r);
		pushup(u);
	}
	void change (int u,int l,int r,int L,int R,int t1,bool t2) {
		if(del[u]) return;
		if(l>=L&&r<=R) { maketag(u,t1,t2); return; }
		int mid=(l+r)>>1;
		pushdown(u);
		if(L<=mid) change(u<<1,l,mid,L,R,t1,t2);
		if(mid+1<=R) change(u<<1|1,mid+1,r,L,R,t1,t2);
		pushup(u);
	}
	void change (int u,int l,int r,int x,int t1,bool t2) {
		if(del[u]) return;
		if(l==r) { maketag(u,t1,t2); return; }
		int mid=(l+r)>>1;
		pushdown(u);
		if(x<=mid) change(u<<1,l,mid,x,t1,t2);
		else change(u<<1|1,mid+1,r,x,t1,t2);
		pushup(u);
	}
}T1,T2,T3;
int cnt,ans;
int main() {
	#ifdef LOCAL
	freopen("my.out","w",stdout);
	#endif
	sf("%d",&n);
	rep(i,1,n) sf("%d",&x[i].a);
	rep(i,1,n) {
		sf("%d",&x[i].b);
		if(x[i].a > x[i].b) swap(x[i].a,x[i].b);
		c[i*2-1]=x[i].a, c[i*2]=x[i].b;
	}
	sort(c+1,c+(n<<1)+1);
	m=unique(c+1,c+(n<<1)+1)-c-1;
	rep(i,1,n) {
		x[i].a=lower_bound(c+1,c+m+1,x[i].a)-c;
		x[i].b=lower_bound(c+1,c+m+1,x[i].b)-c;
		vec[x[i].a].push_back({i,0}), vec[x[i].b].push_back({i,1});
	}
	val=ksm(2,n);
	T1.build(1,1,n),T2.build(1,1,n),T3.build(1,1,n);
	cnt=n<<1;
	val=1ll*val*inv%mod;
	per(i,m,1) {
		for(auto u : vec[i]) {
			int id=u.id;
			bool op=u.ab;
			--cnt;
			if(op) {
				T1.change(1,1,n,id,inv,0),
				T2.change(1,1,n,id,inv,0),
				T3.change(1,1,n,id,inv,0);
				if(id<n) T1.change(1,1,n,id+1,n,inv,0), T2.change(1,1,n,id+1,n,inv,0);
				if(id>1) T1.change(1,1,n,1,id-1,inv,0), T3.change(1,1,n,1,id-1,inv,0);
			}else{
				T1.change(1,1,n,id,0,1), 
				T2.change(1,1,n,id,0,1),
				T3.change(1,1,n,id,0,1);
				if(id<n) T1.change(1,1,n,id+1,n,0,1), T2.change(1,1,n,id+1,n,0,1);
				if(id>1) T1.change(1,1,n,1,id-1,0,1), T3.change(1,1,n,1,id-1,0,1);
			}
		}
		int s=0;
		_add(s,1ll*val*cnt%mod);
		_add(s,T1.tr[1]);
		_add(s,mod-add(T2.tr[1],T3.tr[1]));
		_add(ans,1ll*s*(c[i]-c[i-1])%mod);
	}
	pf("%d\n",ans);
}
```

---

## 作者：Super_Cube (赞：2)

# Solution

由于积水总量为 $\sum H-h_i$，可以将其拆为 $\sum H-\sum h_i$。而 $\sum h_i=2^{n-1}\sum a_i+b_i$，因为把每个位置单独拿出来进行计算，其它位置的情况是任意的，而该位置只有 $a_i$ 与 $b_i$ 两种可能。现在问题主要聚焦在如何求得 $\sum H$。

尝试枚举 $h$，计算每个位置上有多少种方案下 $H\ge h$，加在一起就是答案。

从左往右找到第一个 $a_i\ge h$ 且 $b_i\ge h$ 的位置记为 $l$，从右往左找到第一个 $a_i\ge h$ 且 $b_i\ge h$ 的位置记为 $r$。

如果 $l$ 与 $r$ 存在说明 $l\sim r$ 这一段中的每个位置都能因 $l$ 与 $r$ 产生出 $h$ 的积水，且这时所有位置都可以任意选高度，即 $l\sim r$ 中会产生 $(r-l+1)2^n$ 的贡献。对 $a_i\ge h$ 或 $b_i\ge h$ 做前缀和的结果记为 $c$。那么位于 $[1,l)$ 中的位置，前面有 $c_i$ 个位置有可能和 $l$ 进行匹配后使得 $i$ 能达到 $h$ 的积水，而剩下的 $n-c_i$ 个位置则可以任意填，当然还要减去 $c_i$ 个数里全部都没有选不小于 $h$ 的那一种不合法情况，所以方案为 $(2^{c_i}-1)2^{n-c_i}$。$(r,n]$ 的情况同理，这里就不再详细讲了，为了节省下后缀和数组，就利用刚刚的 $c$ 表示出方案的话即为 $(2^{c_n-c_{i-1}}-1)2^{n-c_n+c_{i-1}}$。

大问题是不存在有位置 $a_i\ge h$ 且 $b_i\ge h$。现在对于每一个位置 $i$，要在前后各挑一个位置出来形成“屏障”使得 $i$ 能够达到 $h$ 的积水。和前面的分析类似，会在前面有 $2^{c_{i-1}}-1$ 种情况，后面有 $2^{c_n-c_i}-1$ 种情况，而剩下的 $n-c_n$ 个位置是可以任意填的，所以位置 $i$ 的总方案为 $(2^{c_{i-1}}-1)(2^{c_n-c_i}-1)2^{n-c_n}$，不过当 $i$ 本身有 $a_i\ge h$ 或 $b_i\ge h$ 时，会多出来 $2^{n-1}$ 种方案，因为它可以选定自己，而剩下的任意。

看完上面这些，你大概可以打出下面这份代码。

```cpp
#include<bits/stdc++.h>
const int mod=1e9+7;
int base[500005];
int c[500005];
int a[500005],b[500005];
int n,m,ans;
int main(){
//	freopen("wall.in","r",stdin);
//	freopen("wall.out","w",stdout);
	scanf("%d",&n);
	base[0]=1;
	for(int i=1;i<=n;++i)
		if((base[i]=base[i-1]<<1)>=mod)base[i]-=mod;
	for(int i=1;i<=n;++i)
		scanf("%d",&a[i]),ans=(ans-1ll*base[n-1]*a[i])%mod;
	for(int i=1;i<=n;++i)
		scanf("%d",&b[i]),ans=(ans-1ll*base[n-1]*b[i])%mod;
	for(int j=1,l,r,res;;++j){
		r=0;l=n+1;
		for(int i=1;i<=n;++i)
			if(a[i]>=j&&b[i]>=j)l=i,i=n;
		for(int i=n;i;--i)
			if(a[i]>=j&&b[i]>=j)r=i,i=1;
		for(int i=1;i<=n;++i)
			c[i]=c[i-1]+(a[i]>=j||b[i]>=j);
		if(!c[n])break;
		res=0;
		if(l<=r){
			res=(res+base[n]*(r-l+1ll))%mod;
			for(int i=1;i<l;++i)
				res=(res+(base[c[i]]-1ll)*base[n-c[i]])%mod;
			for(int i=n;i>r;--i)
				res=(res+(base[c[n]-c[i-1]]-1ll)*base[n-(c[n]-c[i-1])])%mod;
		}else{
			for(int i=1;i<=n;++i)
				res=(res+(base[c[i-1]]-1ll)*(base[c[n]-c[i]]-1)%mod*base[n-c[n]]+(c[i]==c[i-1]?0:base[n-1]))%mod;
		}
		ans=(ans+res)%mod;
	}
	if(ans<0)ans+=mod;
	printf("%d",ans);
	return 0;
}
```

时间复杂度：$O(Vn)$，可获得 48pts。

尝试优化。直接枚举值域感觉很亏啊，注意到一些连续的 $h$ 能够对最终答案带来的影响不变，这启示着我们对 $a_i$ 与 $b_i$ 一起进行离散化。设离散化后 $a_i$ 与 $b_i$ 的值域在 $[1,m]$ 中，枚举 $h\in[0,m)$，$l$ 改为从左往右第一个 $a_i>h$ 且 $b_i>h$ 的位置，$r$ 改为从右往左第一个 $a_i>h$ 且 $b_i>h$ 的位置，$c$ 改为对 $a_i>h$ 或 $b_i>h$ 做前缀和的结果，其余地方不变。最后在 $h$ 上计算出的结果实际对应映射前 $h$ 所代表的值到映射前 $h+1$ 所代表的值这一左闭右开的区间中的每一个值。

看完上面那段话，你大概能写出下面这份带有离散化优化后的代码。

```cpp
#include<bits/stdc++.h>
const int mod=1e9+7;
int base[500005];
int c[500005];
int a[500005],b[500005];
int lsh[1000005];
int n,m,ans;
int main(){
//	freopen("wall.in","r",stdin);
//	freopen("wall.out","w",stdout);
	scanf("%d",&n);
	base[0]=1;
	for(int i=1;i<=n;++i)
		if((base[i]=base[i-1]<<1)>=mod)base[i]-=mod;
	for(int i=1;i<=n;++i)
		scanf("%d",&a[i]),ans=(ans-1ll*base[n-1]*a[i])%mod,lsh[i]=a[i];
	for(int i=1;i<=n;++i)
		scanf("%d",&b[i]),ans=(ans-1ll*base[n-1]*b[i])%mod,lsh[i+n]=b[i];
	std::stable_sort(lsh+1,lsh+(n<<1|1));
	m=std::unique(lsh+1,lsh+(n<<1|1))-lsh-1;
	for(int i=1;i<=n;++i)
		a[i]=std::lower_bound(lsh+1,lsh+m+1,a[i])-lsh,b[i]=std::lower_bound(lsh+1,lsh+m+1,b[i])-lsh;
	for(int j=0,l,r,res;j<m;++j){
		r=0;l=n+1;
		for(int i=1;i<=n;++i)
			if(a[i]>j&&b[i]>j)l=i,i=n;
		for(int i=n;i;--i)
			if(a[i]>j&&b[i]>j)r=i,i=1;
		for(int i=1;i<=n;++i)
			c[i]=c[i-1]+(a[i]>j||b[i]>j);
		res=0;
		if(l<=r){
			res=(res+base[n]*(r-l+1ll))%mod;
			for(int i=1;i<l;++i)
				res=(res+(base[c[i]]-1ll)*base[n-c[i]])%mod;
			for(int i=n;i>r;--i)
				res=(res+(base[c[n]-c[i-1]]-1ll)*base[n-(c[n]-c[i-1])])%mod;
		}else{
			for(int i=1;i<=n;++i)
				res=(res+(base[c[i-1]]-1ll)*(base[c[n]-c[i]]-1)%mod*base[n-c[n]]+(c[i]==c[i-1]?0:base[n-1]))%mod;
		}
		ans=(ans+1ll*(lsh[j+1]-lsh[j])*res)%mod;
	}
	if(ans<0)ans+=mod;
	printf("%d",ans);
	return 0;
}
```

时间复杂度：$O(n^2)$，可获得 70pts。

外层枚举 $h$ 实在优化不动了，发现内层还有极大的优化空间。看数据范围应该想让里边得到单次不超过 $O(\log n)$ 的复杂度，联想到用线段树维护 $c$。$l,r$ 指针可以做到均摊 $O(n)$ 的扫描，不展开讨论。把 $i$ 挂在 $\max(a_i,b_i)$，当枚举到 $h=\max(a_i,b_i)$ 时要将 $i$ 单点修改成 $0$。把每种情况的贡献拆开，看怎样好维护。

1. $(2^{c_i}-1)2^{n-c_i}$。

等于 $2^n-2^{n-c_i}$，去掉定值，只需要维护 $2^{-c_i}$。

2. $(2^{c_n-c_{i-1}}-1)2^{n-c_n+c_{i-1}}$。

等于 $2^n-2^{n-c_n+c_{i-1}}$，去掉定值，只需要维护 $2^{c_{i-1}}$。

3. 当 $c_i=c_{i-1}$ 时，$(2^{c_{i-1}}-1)(2^{c_n-c_i}-1)2^{n-c_n}$。

等于 $2^{n-c_n}(2^{c_n}-2^{c_i}-2^{c_n-c_i}+1)$，去掉定值，只需要维护 $2^{c_i}$ 与 $2^{-c_i}$。

4. 当 $c_i\ne c_{i-1}$ 时，$(2^{c_{i-1}}-1)(2^{c_n-c_i}-1)2^{n-c_n}+2^{n-1}$。

等于 $2^{n-1}+2^{n-c_n}(2^{c_n-1}-2^{c_i-1}-2^{c_n-c_i}+1)$，去掉定值，只需要维护 $2^{c_i-1}$ 与 $2^{-c_i}$。

噫，好，做完啦。

由于最终代码又丑又长就不放在这里恶心各位了。

---

## 作者：Felix72 (赞：1)

硬拆 $2$ 的次幂的做法很不友好，我来个好想好写的做法。

对于 $h$ 序列固定的情况，答案是 $\sum_{i = 1}^{n} \min(pr_i, su_i) - h_i = pr_i + su_i - global - h_i$。其中 $pr, su$ 是前缀、后缀最大值，$global$ 是全局最大值。

思考直接求出所有情况的 $\sum pr, \sum su, \sum global, \sum h$。

思考一个 DP 状态 $f_{i, x}$ 表示考虑前 $i$ 个元素，其 $\max h = x$ 的方案数。$\sum_{i = 1}^{n}2^{n - i}\sum xf_{i, x}$ 就是 $\sum pr$。枚举 $i$，把 $f$ 挂在线段树上维护；$\sum su$ 同理；$\sum global$ 考虑 $xf_{n, x}$ 的和；$\sum h$ 等于 $\sum h2^{n - 1}$。

因此写一个线段树优化 DP，把系数放进线段树里算就可以了。

```cpp
/* Good Game, Well Play. */
#include <bits/stdc++.h>
#define lowbit(x) ((x) & (-(x)))
using namespace std;

const int N = 500010, mod = 1e9 + 7;
inline void Plus(long long &now, long long add)
{now += add; while(now >= mod) now -= mod;}
int n, h[2][N]; long long pw[N];

struct Disc {int id, pos; long long val;} disc[N * 2]; int dn;
inline bool cmp_disc(Disc u, Disc v) {return u.val < v.val;}

int rt, idx;
struct SGT
{
	int ls, rs;
	long long cnt, sum, tmp, mul;
	#define ls(x) tree[x].ls
	#define rs(x) tree[x].rs
	#define cnt(x) tree[x].cnt
	#define sum(x) tree[x].sum
	#define tmp(x) tree[x].tmp
	#define mul(x) tree[x].mul
} tree[N * 4];
inline void pushup(int now)
{
	cnt(now) = (cnt(ls(now)) + cnt(rs(now))) % mod;
	sum(now) = (sum(ls(now)) + sum(rs(now))) % mod;
}
inline void push_mul(int now, long long tg)
{
	cnt(now) = cnt(now) * tg % mod;
	sum(now) = sum(now) * tg % mod;
	mul(now) = mul(now) * tg % mod;
}
inline void pushdown(int now)
{
	if(mul(now) != 1)
	{
		push_mul(ls(now), mul(now));
		push_mul(rs(now), mul(now));
		mul(now) = 1;
	}
}
inline void build(int &now, int l, int r)
{
	now = ++idx; mul(now) = 1;
	if(l == r) {tmp(now) = disc[l].val; return ;}
	int mid = (l + r) >> 1;
	build(ls(now), l, mid), build(rs(now), mid + 1, r);
	tmp(now) = (tmp(ls(now)) + tmp(rs(now))) % mod;
}
inline void range_mul(int now, int l, int r, int L, int R, long long num)
{
	if(L > R) return ;
	if(L <= l && r <= R) {push_mul(now, num); return ;}
	pushdown(now); int mid = (l + r) >> 1;
	if(L <= mid) range_mul(ls(now), l, mid, L, R, num);
	if(mid < R) range_mul(rs(now), mid + 1, r, L, R, num);
	pushup(now);
}
inline void single_add(int now, int l, int r, int pos, int num)
{
	if(l == r)
	{
		cnt(now) = (cnt(now) + num) % mod;
		sum(now) = (sum(now) + tmp(now) * num) % mod;
		return ;
	}
	pushdown(now); int mid = (l + r) >> 1;
	if(pos <= mid) single_add(ls(now), l, mid, pos, num);
	else single_add(rs(now), mid + 1, r, pos, num);
	pushup(now);
}
inline int query_cnt(int now, int l, int r, int L, int R)
{
	if(L > R) return 0;
	if(L <= l && r <= R) return cnt(now);
	pushdown(now); int mid = (l + r) >> 1;
	if(R <= mid) return query_cnt(ls(now), l, mid, L, R);
	else if(mid < L) return query_cnt(rs(now), mid + 1, r, L, R);
	else return (query_cnt(ls(now), l, mid, L, R) + query_cnt(rs(now), mid + 1, r, L, R)) % mod;
}

long long LN, RN, GLOBAL, SELF;

int main()
{
//	freopen("text.in", "r", stdin);
//	freopen("prog.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for(int i = 0; i <= 1; ++i)
		for(int j = 1; j <= n; ++j)
			cin >> h[i][j], disc[++dn] = {i, j, h[i][j]};
	sort(disc + 1, disc + dn + 1, cmp_disc);
	for(int i = 1; i <= dn; ++i) h[disc[i].id][disc[i].pos] = i;
	pw[0] = 1; for(int i = 1; i <= n; ++i) pw[i] = pw[i - 1] * 2 % mod;
	
	build(rt, 1, 2 * n);
	single_add(rt, 1, 2 * n, h[0][1], 1);
	single_add(rt, 1, 2 * n, h[1][1], 1);
	Plus(LN, sum(rt) * pw[n - 1] % mod);
	for(int i = 2; i <= n; ++i)
	{
		int p_min = min(h[0][i], h[1][i]), p_max = max(h[0][i], h[1][i]);
		single_add(rt, 1, 2 * n, p_max, query_cnt(rt, 1, 2 * n, 1, p_max - 1));
		single_add(rt, 1, 2 * n, p_min, query_cnt(rt, 1, 2 * n, 1, p_min - 1));
		range_mul(rt, 1, 2 * n, 1, p_min - 1, 0);
		range_mul(rt, 1, 2 * n, p_max + 1, 2 * n, 2);
		Plus(LN, sum(rt) * pw[n - i] % mod);
	}
	push_mul(rt, 0);
	single_add(rt, 1, 2 * n, h[0][n], 1);
	single_add(rt, 1, 2 * n, h[1][n], 1);
	Plus(RN, sum(rt) * pw[n - 1] % mod);
	for(int i = n - 1; i >= 1; --i)
	{
		int p_min = min(h[0][i], h[1][i]), p_max = max(h[0][i], h[1][i]);
		single_add(rt, 1, 2 * n, p_max, query_cnt(rt, 1, 2 * n, 1, p_max - 1));
		single_add(rt, 1, 2 * n, p_min, query_cnt(rt, 1, 2 * n, 1, p_min - 1));
		range_mul(rt, 1, 2 * n, 1, p_min - 1, 0);
		range_mul(rt, 1, 2 * n, p_max + 1, 2 * n, 2);
		Plus(RN, sum(rt) * pw[i - 1] % mod);
	}
	
	for(int i = 0; i <= 1; ++i)
		for(int j = 1; j <= n; ++j)
			Plus(SELF, disc[h[i][j]].val * pw[n - 1] % mod);
	
	long long left = pw[n]; bool vis[N] = {0};
	for(int i = 2 * n, iv = (mod + 1) / 2; i >= 1; --i)
	{
		if(!vis[disc[i].pos])
		{
			left = left * iv % mod;
			Plus(GLOBAL, left * disc[i].val % mod);
			vis[disc[i].pos] = true;
		}
		else
		{
			Plus(GLOBAL, left * disc[i].val % mod);
			break;
		}
	}
	
	cout << (LN + RN - GLOBAL * n % mod - SELF + mod * 2) % mod << '\n';
	return 0;
}
/*

*/
```

---

## 作者：happy_dengziyue (赞：1)

### 1 思路

给一个从大往小扫的做法（和已有题解不太一样）。

首先一个离散化，这样就只有本质不同的 $\Theta(N)$ 个高度。然后我们认为 $a_i\le b_i$。

假设固定柱子高度为 $h_i$。考虑一个问题：哪些格子在高度 $H$ 有积水？显然对于一个格子 $x$：有 $h_x<H$；存在 $y\in[1,x)$ 有 $h_y\ge H$；存在 $z\in(x,n]$ 有 $h_z\ge H$。

接下来考虑柱子高度不固定的情况。对于两侧的限制考虑“正难则反”。设：

+ $l_x$ 表示只考虑所有 $i\in[1,x)$ 且都有 $h_i<H$ 的方案数；
+ $r_x$ 表示只考虑所有 $i\in(x,n]$ 且都有 $h_i<H$ 的方案数；
+ $m_x$ 表示 $h_x<H$ 的方案数，即为 $[a_x<H]+[b_x<H]$。
+ $all$ 表示所有 $h_i<H$ 的方案数。

而格子 $x$ 在高度 $H$ 有积水的情况就是:

$$(2^{x-1}-l_x)\times(2^{n-x}-r_x)\times m_x$$

化简得：

$$2^{n-1}\times m_x-l_x\times2^{n-x}\times m_x-r_x\times2^{x-1}m_x+all$$

注意到，从高往低扫描，更新的本质就是单点修改 $m_x$、对 $l_x\times2^{n-x}$ 的值后缀乘和对 $r_x\times2^{x-1}$ 的值前缀乘（这里将 $2$ 的幂也放进来是为了方便维护）。因此，前三部分的和的维护是可以用线段树简单实现的，而 $all=\prod m_x=\prod([a_i<H]+[b_i<H])$，可以 $\Theta(1)$ 修改。

之所以是从高到低扫描（而非从低到高），是因为可以让 $l_x$、$r_x$ 和 $m_x$ 关于 $H$ 单调不升，这样修改时就是乘上 $\dfrac{1}{2}$ 或 $0$ 而不必涉及到 $0\to\N^+$ 的转化。

### 2 代码与记录

```cpp
#include<bits/stdc++.h>
using namespace std;
#define max_n 1000020
#define mod 1000000007ll
#define inv2 ((mod+1)/2)
long long pw2[max_n+2];
int n;
long long a[max_n+2];
long long b[max_n+2];
long long xx[max_n+2];
int xi=0;
vector<int>op[max_n+2];
long long can[max_n+2];//<H的方案数
long long cntc[max_n+2];
struct T{
	int l,r;
	long long sm,sl,sr,sml,smr;
	long long lal,lar;
}tr[300020<<2];
long long ans=0;
inline long long read(){
	long long res=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){res=res*10+(c^48); c=getchar();}
	return res;
}
inline void pu(int o){
	tr[o].sm=(tr[o<<1].sm+tr[o<<1|1].sm)%mod;
	tr[o].sl=(tr[o<<1].sl+tr[o<<1|1].sl)%mod;
	tr[o].sr=(tr[o<<1].sr+tr[o<<1|1].sr)%mod;
	tr[o].sml=(tr[o<<1].sml+tr[o<<1|1].sml)%mod;
	tr[o].smr=(tr[o<<1].smr+tr[o<<1|1].smr)%mod;
}
inline void addtagl(int o,long long w){
	tr[o].sl=tr[o].sl*w%mod; tr[o].sml=tr[o].sml*w%mod;
	tr[o].lal=tr[o].lal*w%mod;
}
inline void addtagr(int o,long long w){
	tr[o].sr=tr[o].sr*w%mod; tr[o].smr=tr[o].smr*w%mod;
	tr[o].lar=tr[o].lar*w%mod;
}
inline void pd(int o){
	if(tr[o].lal!=1){
		addtagl(o<<1,tr[o].lal); addtagl(o<<1|1,tr[o].lal);
		tr[o].lal=1;
	}
	if(tr[o].lar!=1){
		addtagr(o<<1,tr[o].lar); addtagr(o<<1|1,tr[o].lar);
		tr[o].lar=1;
	}
}
inline void build(int o,int l,int r){
	tr[o]=(T){l,r,0,0,0,0,0,1,1};
	if(l>=r){
		tr[o].sm=2; tr[o].sl=pw2[n-1]; tr[o].sr=pw2[n-1];
		tr[o].sml=tr[o].sm*tr[o].sl%mod; tr[o].smr=tr[o].sm*tr[o].sr%mod;
		return;
	}
	int mid=(l+r)>>1;
	build(o<<1,l,mid);
	build(o<<1|1,mid+1,r);
	pu(o);
}
inline void updm(int o,int x,long long w){
	int l=tr[o].l,r=tr[o].r;
	if(l>=r){
		tr[o].sm=w; tr[o].sml=w*tr[o].sl%mod; tr[o].smr=w*tr[o].sr%mod;
		return;
	}
	pd(o);
	int mid=(l+r)>>1;
	if(x<=mid)updm(o<<1,x,w);
	else updm(o<<1|1,x,w);
	pu(o);
}
inline void updl(int o,int ql,int qr,long long w){
	int l=tr[o].l,r=tr[o].r;
	if(tr[o].sl==0)return;
	if(ql<=l&&r<=qr){addtagl(o,w); return;}
	pd(o);
	int mid=(l+r)>>1;
	if(ql<=mid)updl(o<<1,ql,qr,w);
	if(qr>mid)updl(o<<1|1,ql,qr,w);
	pu(o);
}
inline void updr(int o,int ql,int qr,long long w){
	int l=tr[o].l,r=tr[o].r;
	if(tr[o].sr==0)return;
	if(ql<=l&&r<=qr){addtagr(o,w); return;}
	pd(o);
	int mid=(l+r)>>1;
	if(ql<=mid)updr(o<<1,ql,qr,w);
	if(qr>mid)updr(o<<1|1,ql,qr,w);
	pu(o);
}
inline long long askall(){
	if(cntc[0])return 0;
	return pw2[cntc[2]];
}
int main(){
	pw2[0]=1; for(int i=1;i<=max_n;++i)pw2[i]=pw2[i-1]*2%mod;
	n=read();
	if(n<=2){printf("0\n"); return 0;}
	for(int i=1;i<=n;++i){a[i]=read(); xx[++xi]=a[i];}
	for(int i=1;i<=n;++i){
		b[i]=read(); xx[++xi]=b[i];
		if(a[i]>b[i])swap(a[i],b[i]);
	}
	sort(xx+1,xx+xi+1); xi=unique(xx+1,xx+xi+1)-xx-1;
	++xi; xx[xi]=xx[xi-1]+1;
	for(int i=1;i<=n;++i){
		a[i]=lower_bound(xx+1,xx+xi+1,a[i])-xx;
		b[i]=lower_bound(xx+1,xx+xi+1,b[i])-xx;
		op[a[i]].push_back(i); op[b[i]].push_back(i);
	}
	for(int i=1;i<=n;++i){can[i]=2; ++cntc[2];}
	build(1,1,n);
	for(int x=xi;x>=2;--x){
		for(auto u:op[x]){
			--cntc[can[u]]; ++cntc[--can[u]]; updm(1,u,can[u]); 
			if(can[u]==1){
				if(u<n)updl(1,u+1,n,inv2);
				if(1<u)updr(1,1,u-1,inv2);
			}
			else{
				if(u<n)updl(1,u+1,n,0);
				if(1<u)updr(1,1,u-1,0);
			}
		}
		long long res=0;
		res=(res+pw2[n-1]*tr[1].sm%mod)%mod;
		res=(res-tr[1].sml-tr[1].smr+mod*2)%mod;
		res=(res+askall()*n%mod)%mod;
		ans=(ans+res*(xx[x]-xx[x-1])%mod)%mod;
	}
	printf("%lld\n",(ans%mod+mod)%mod);
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/186276503)

By **dengziyue**

---

## 作者：shiruoyu114514 (赞：1)

容易发现答案为 $\sum H-\sum h$。而 $\sum h=2^{n-1}\sum \limits_{i=1}^{n} (a_i+b_i)$，故我们的注意力主要集中在求 $\sum H$ 上。

考虑把 $H$ 拆成 $\sum \limits_{h=1}^{\infty} [h \geq H]$ 来计算。

对于每一堵墙 $i$,设 $w_i = [a_i < h]+[b_i < h]$。

若 $h_i$ 小于 $h$，则 $i$ 左边的所有数的最大值以及右边数的最大值均需 $\geq h$ 。而这两项的方案数可以通过总方案数 $-$ 不合法方案数容斥得到。该情况的方案数即为 $w_i (2^{i-1}-\prod \limits_{j=1}^{i-1} w_j)(2^{n-i}-\prod \limits_{j=i+1}^{n} w_j)$。

否则，其他可以随意。总方案数为 $2^{n-1}(2-w_i)$。

令 $ans_i$ 为 $i$ 处的贡献。将以上两式相加并化简得 

$$ans_i = 2^n - 2^{i-1}\prod \limits_{j=i}^{n} w_j - 2^{n-i} \prod \limits_{j=1}^{i} w_j+ \prod \limits_{j=1}^{n} w_j$$

而单个高度的总贡献为 $\sum \limits_{i=1}^{n} ans_i$。

考虑令 $h$ 从大往小扫描。

当 $h$ 变化时，$\sum 2^n$ 以及 $\sum \prod \limits_{j=1}^{n} w_j$ 的维护是平凡的，而我们可以用一棵线段树来维护每一个下标的 $2^{i-1}\prod \limits_{j=i}^{n} w_j$。具体地，当 $h$ 足够大时，每个下标的值都为 $2^n$ 。而每当一个 $w_i$ 因 $h$ 的变化而减小时，则在线段树上进行一次区间乘法。另一项同理。

考虑对于相邻两个高度 $l,r$，$w$ 在 $h \in (l,r] $ 时不变。所以我们只需要枚举 $O(n)$ 个 $h$ 就行了。

时间复杂度 $O(n\log n)$。

---

## 作者：Godzilla (赞：1)

[更好的阅读体验](https://www.cnblogs.com/Tagaki-san/p/18528879)

首先可以枚举一个位置的水量 $w$，求 $c_{w}$ 表示其方案数，答案为 $\sum c_{w}$。那么可以设 $c_{i,j}$ 表示位置 $i$ 水量 $\ge j$ 的方案数，答案为 $\sum c_{i,j}$。一个位置 $i$，墙高为 $a_i$，要求其有至少 $j$ 单位的水，那么左右的 $\max h$ 必然都要 $\ge a_i+j$。考虑容斥，分别求出左边 $\max h <a_{i}+j$，右边 $\max h<a_{i}+j$ 和左右两边的 $\max h<a_{i}+j$ 的方案数。

考虑一个位置对方案数的贡献，不妨设 $a_{k}<b_{k},h=a_{i}+j$，若 $h>b_{k}$，那么贡献为 $\times 2$，若 $a_k<h\le b_k$，那么贡献为 $\times 1$，若 $h\le a_k$，那么贡献为 $\times 0$。以单独求左边条件的方案数为例，我们从左到右扫描线，在维护时只需要维护后缀 $\times 2$，记录前缀 $\times 0$ 的最大限制即可，查询就查询后缀和。

对于两边都有限制的情况，每次就是消除 $i$ 的限制。不妨先考虑所有限制，用线段树维护，扫描到 $i$ 的时候撤销 $i$ 的限制即可。

```cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int N = 5e5 + 5, M = 40, mod = 1e9 + 7, inf = 1e9;

inline void add(int & x, int y) {x += y; if (x >= mod) x -= mod;}
inline void dec(int & x, int y) {x += mod - y; if (x >= mod) x -= mod;}
inline int pls(int x, int y) {x += y; if (x >= mod) x -= mod; return x;}
inline int sub(int x, int y) {x += mod - y; if (x >= mod) x -= mod; return x;}
inline int mul(int x, int y) {return 1ll * x * y % mod;}

int n, a[N], b[N], ans, rt, _2[N], iv, pl[N], sl[N];

namespace smt {
  int ls[N * M], rs[N * M], s[N * M], tag[N * M], cnt;
#define ls(p) ls[p]
#define rs(p) rs[p]

  inline void init() {for (int i = 1; i <= cnt; ++i) ls[i] = rs[i] = s[i] = tag[i] = 0; cnt = rt = 0;}

  inline int nnd(int len) {return cnt++, s[cnt] = len, tag[cnt] = 1, cnt;}

  inline void work(int k, int p) {tag[p] = mul(tag[p], k), s[p] = mul(s[p], k);}

  inline void psd(int l, int r, int p) {
    int mid = (l + r) >> 1;
    if (!ls(p)) ls(p) = nnd(mid - l + 1);
    if (tag[p] ^ 1) work(tag[p], ls(p));
    if (!rs(p)) rs(p) = nnd(r - mid);
    if (tag[p] ^ 1) work(tag[p], rs(p));
    tag[p] = 1;
  }

  inline void psu(int p) {s[p] = pls(s[ls(p)], s[rs(p)]);}

  inline void ad(int l, int r, int L, int R, int k, int & p) {
    if (L > R) return;
    if (!p) p = nnd(r - l + 1);
    if (l >= L && r <= R) return work(k, p);
    int mid = (l + r) >> 1; psd(l, r, p);
    if (L <= mid) ad(l, mid, L, R, k, ls(p));
    if (R > mid) ad(mid + 1, r, L, R, k, rs(p));
    psu(p);
  }

  inline int ask(int l, int r, int L, int R, int p) {
    if (L > R) return 0;
    if (!p) return max(0, min(r, R) - max(l, L) + 1);
    if (l >= L && r <= R) return s[p];
    int mid = (l + r) >> 1, ans = 0; psd(l, r, p);
    if (L <= mid) add(ans, ask(l, mid, L, R, ls(p)));
    if (R > mid) add(ans, ask(mid + 1, r, L, R, rs(p)));
    return ans;
  }
}

using namespace smt;

inline int qpow(int a, int b) {
  int s = 1;
  while (b) {
    if (b & 1) s = mul(s, a);
    a = mul(a, a), b >>= 1;
  } return s;
}

signed main() {
  cin >> n;
  for (int i = 1; i <= n; ++i) cin >> a[i];
  for (int i = 1; i <= n; ++i) cin >> b[i];
  _2[0] = 1; for (int i = 1; i <= n; ++i) _2[i] = mul(_2[i - 1], 2);
  iv = qpow(2, mod - 2);
  init();
  for (int i = 1; i <= n; ++i) {
    add(ans, mul(inf - a[i], qpow(2, n - 1)));
    add(ans, mul(inf - b[i], qpow(2, n - 1)));
  }
  for (int i = 1, lm = 0; i <= n; ++i) {
    int t = ask(1, inf, max(lm + 1, a[i] + 1), inf, rt);
    dec(ans, mul(t, _2[n - i]));
    t = ask(1, inf, max(lm + 1, b[i] + 1), inf, rt);
    dec(ans, mul(t, _2[n - i]));
    ad(1, inf, max(a[i], b[i]) + 1, inf, 2, rt), lm = max(lm, min(a[i], b[i]));
    pl[i] = lm;
  }
  init();
  for (int i = n, lm = 0; i; --i) {
    int t = ask(1, inf, max(lm + 1, a[i] + 1), inf, rt);
    dec(ans, mul(t, _2[i - 1]));
    t = ask(1, inf, max(lm + 1, b[i] + 1), inf, rt);
    dec(ans, mul(t, _2[i - 1]));
    ad(1, inf, max(a[i], b[i]) + 1, inf, 2, rt), lm = max(lm, min(a[i], b[i]));
    sl[i] = lm;
  }
  init();
  for (int i = 1; i <= n; ++i) ad(1, inf, max(a[i], b[i]) + 1, inf, 2, rt);
  for (int i = 1; i <= n; ++i) {
    ad(1, inf, max(a[i], b[i]) + 1, inf, iv, rt);
    add(ans, ask(1, inf, max(max(pl[i - 1], sl[i + 1]), a[i]) + 1, inf, rt));
    add(ans, ask(1, inf, max(max(pl[i - 1], sl[i + 1]), b[i]) + 1, inf, rt));
    ad(1, inf, max(a[i], b[i]) + 1, inf, 2, rt);
  }
  cout << ans << endl;
  return 0;
}
```

---

## 作者：Scinerely (赞：0)

## [BalticOI 2024]Wall

答案可以用 $\sum H - \sum h$ 来算。

先考虑 $\sum h$ 的部分，权值一定是 $\sum (a_i+b_i)2^{n-1}$。

重点在于 $\sum H$ 的部分。我们考虑使用这么一种计算方法：$\sum [H \geq d]$ 。考虑固定一个 $d$ 如何计算答案，那么现在我们就只关心 $a_i,b_i$ 是否大于等于 $d$ 了，记录 $num_i$ 表示 $[a_i \geq d]+[b_i \geq d]$ 。在一个序列中，$H$ 大于等于 $d$ 的元素一定是一个连续的区间，我们枚举这个区间 $[l,r]$ ，然后去计算 $[l,r]$ 作为区间内元素都大于等于 $d$ 的 **极大区间** 的序列数量。

$l=r$

对于 $l$ 位置本身而言，因为要求区间元素大于等于 $d$ ，故有 $num_i$ 种选择。对于 $i \neq l$ 而言，要求元素严格小于 $d$ ，所以有 $\prod_{i \neq l} (2-num_i)$ 种选择。

故这种情况的贡献就是 $num_l \times \prod_{i \neq l} (2-num_i)$ 。

$l \neq r$

类似于 $l=r$ 的，两个端点处都要求权值大于等于 $d$ ，所以有 $num_{l}\times num_r$ 种可能性。既然左右端点确定了，那么 $(l,r)$ 内的元素可以自由选择，故有 $2^{r-l-1}$ 种可能性。在区间外的元素贡献同 $l=r$ 。

这种情况的贡献是 $(r-l+1) \times num_l \times num_r \times 2^{r-l-1} \times \prod_{i \notin [l,r]} (2-num_i)$ 。

我们发现 $l=r$ 不过是 $l \neq r$ 的特殊情况。。。

对于这种二元组统计问题，可以想到使用分治结构去计算。我们考虑线段树。

看看答案怎么合并，一个节点的合法二元组由两个儿子内的答案和跨越分治中心的区间 $[l,r]$ 构成。一定需要记录一下三种信息：

1.  $ans_i$ 表示区间内所有合法二元组的贡献和。
2.  $prew_i$ 表示区间内所有合法的前缀 $l$ 的贡献和。
3.  $sufw_i$ 表示区间内所有合法的后缀 $r$ 的贡献和。

 先考虑 $ans_i$ 的合并。

最为简单的就是 $ans_i=ans_{ls}+ans_{rs}$ 。然后考虑利用 $sufw_{ls}$ 和 $prew_{rs}$ 合并出答案。这里有一个棘手的点：

- $prew_i$ 记录的信息类似于 $(-l+1)\times num_l \times 2^{x} \times \prod_{j<l}(2-num_j)$ 。
- $sufw_i$ 记录的信息类似于 $r\times num_r \times 2^x \times \prod_{j>r}(2-num_j)$ 。

事实上,我们需要计算的答案形式与 $prew_i$ 和 $sufw_i$ 都不同。系数不同，贡献 $(r-l+1)$ 也与 $-l+1,r$ 不同。但是我们可以拆贡献：

$(r-l+1) \times num_l \times num_r \times 2^{r-l-1} \times \prod_{i \notin [l,r]} (2-num_i)$ 可以被表示为：

$r \times num_l \times num_r \times 2^{r-l-1} \times \prod_{i \notin [l,r]} (2-num_i)$ 和

$(-l+1) \times num_l \times num_r \times 2^{r-l-1} \times \prod_{i \notin [l,r]} (2-num_i)$ 

我们只需要额外维护 $pre_i,suf_i$ 的不带贡献形式 $pre_i,suf_i$ 形式就可以了。

- $pre_i$ 记录的信息类似于 $num_l \times 2^{x} \times \prod_{j<l}(2-num_j)$ 。
- $suf_i$ 记录的信息类似于 $num_r \times 2^x \times \prod_{j>r}(2-num_j)$ 。

那么就有 $ans_i=(sufw_{ls}\times pre_{rs}+suf_{ls}\times prew_{rs})$ 。

接下来考虑 $pre_i$ 和 $prew_i$ 的转移，$suf_i$ 和 $sufw_i$ 的转移十分类似，这里就不讲了。

$pre_i$ 也是由两个部分组成：$pre_{ls}$ 和 $x \times pre_{rs}$ 。就是前缀在左儿子还是右儿子中的两种情况。记录 $seg_i$ 表示 $i$ 节点所管辖的线段长度，则左儿子的转移是十分简单的：$pre_i=pre_{ls}\times 2^{seg_{rs}}$ ，$prew_i$ 的转移是一模一样的。

考虑 $l$ 在右儿子内，转移的时候左儿子的元素均会贡献 $\prod (2-num_j)$ 的系数，所以额外记录 $t_i$ 表示区间内元素 $(2-num_j)$ 的积。则：$pre_i=t_{ls}\times pre_{rs}$ 。

$t$ 本身就是 $t_i=t_{ls}\times t_{rs}$ 。

最后答案就是 $ans_{root}$ 。

这么计算的好处在于分治结构可以动态。那么我们让 $d$ 从小到大，对于每一个元素而言，$num_i$ 会经历 $2$ 到 $1$ ，$1$ 到 $0$ 的过程，在线段树上单点修改一下即可。

时间复杂度 $O(n \log n)$ 。代码非常好写。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int MAXN=5e5+5,mod=1e9+7;
int qpow(int a,int b){
	int ans=1,base=a;
	while(b){
		if(b&1) ans=ans*base%mod;
		base=base*base%mod;
		b>>=1;
	}
	return ans;
}
int n;
int a[MAXN],b[MAXN];
pair<int,int> c[MAXN<<1];
int pw[MAXN],inv[MAXN];
int num[MAXN];
struct sgt2{
	int t[MAXN<<2],seg[MAXN<<2];
	int ans[MAXN<<2];
	int pre[MAXN<<2],suf[MAXN<<2];
	int prew[MAXN<<2],sufw[MAXN<<2];
	void pushup(int i){
		ans[i]=(ans[i<<1]*t[i<<1|1]+ans[i<<1|1]*t[i<<1])%mod;
		ans[i]=(ans[i]+prew[i<<1]*suf[i<<1|1]+pre[i<<1]*sufw[i<<1|1])%mod;

		t[i]=t[i<<1]*t[i<<1|1]%mod;
		pre[i]=(pre[i<<1]*pw[seg[i<<1|1]]+t[i<<1]*pre[i<<1|1])%mod;
		suf[i]=(suf[i<<1]*t[i<<1|1]+suf[i<<1|1]*pw[seg[i<<1]])%mod;
		prew[i]=(prew[i<<1]*pw[seg[i<<1|1]]+t[i<<1]*prew[i<<1|1])%mod;
		sufw[i]=(sufw[i<<1]*t[i<<1|1]+sufw[i<<1|1]*pw[seg[i<<1]])%mod;
	}
	void calc(int i,int l){
		if(num[l]==0){
			t[i]=2;
			ans[i]=pre[i]=suf[i]=0;
			prew[i]=sufw[i]=0;
		}
		else if(num[l]==1){
			t[i]=1;
			ans[i]=pre[i]=suf[i]=1;
			prew[i]=(1-l+mod)%mod;
			sufw[i]=l;
		}
		else{
			t[i]=0;
			ans[i]=pre[i]=suf[i]=2;
			prew[i]=2*(1-l+mod)%mod;
			sufw[i]=2*l;
		}
	}
	void build(int i,int l,int r){
		seg[i]=r-l+1;
		if(l==r){
			calc(i,l);
			return ;
		}
		int mid=(l+r)>>1;
		build(i<<1,l,mid);
		build(i<<1|1,mid+1,r);
		pushup(i);
	}
	void update(int i,int l,int r,int k){
		if(l==r){
			calc(i,l);
			return ;
		}
		int mid=(l+r)>>1;
		if(mid>=k)
			update(i<<1,l,mid,k);
		else
			update(i<<1|1,mid+1,r,k);
		pushup(i);
	}
}t;
int solve(){
	int ans=0;
	for(int i=1;i<=n;i++){
		c[i]=make_pair(a[i],i);
		c[i+n]=make_pair(b[i],i);
		num[i]=2;
	}
	sort(c+1,c+n*2+1);
	t.build(1,1,n);
	int pos=1;
	for(int i=1;i<=n*2;i++){
		while(pos<=n*2&&c[pos].first<c[i].first){
			num[c[pos].second]--;
			t.update(1,1,n,c[pos].second);
			pos++;
		}
		ans=(ans+t.ans[1]*(c[i].first-c[i-1].first))%mod;
	}
	return ans;
}
signed main(){
	n=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=n;i++) b[i]=read();

	pw[0]=inv[0]=1;
	for(int i=1;i<=n;i++){
		pw[i]=pw[i-1]*2%mod;
		inv[i]=qpow(pw[i],mod-2);
	}
	int sum=0;
	for(int i=1;i<=n;i++)
		sum=(sum+a[i]*pw[n-1]+b[i]*pw[n-1])%mod;
	cout<<(solve()-sum+mod)%mod;
	return 0;
}
```

---

## 作者：Grisses (赞：0)

[题面](https://www.luogu.com.cn/problem/P10764)

---

美妙模拟赛拉原题。

给一个码量大点但是无脑的思路。

---

容易发现答案是 $\sum\limits_{\forall h\{n\}}\sum\limits_{i=1}^n\min(pre_i,nxt_i)-h_i$，其中 $pre_i,nxt_i$ 分别为 $i$ 的前/后缀最大值。

因为 $\min(pre_i,nxt_i)=pre_i+nxt_i-\max(pre_i,nxt_i)=pre_i+nxt_i-maxn$，所以原式又等于 $(\sum\limits_{\forall h\{n\}}\sum\limits_{i=1}^npre_i)+(\sum\limits_{\forall h\{n\}}\sum\limits_{i=1}^nnxt_i)-(\sum\limits_{\forall h\{n\}}\sum\limits_{i=1}^nmaxn)-(\sum\limits_{\forall h\{n\}}\sum\limits_{i=1}^nh_i)$。

我们考虑分开算这四个东西：

- $(\sum\limits_{\forall h\{n\}}\sum\limits_{i=1}^nh_i)$ 在读入时处理，不讲。

- $(n\sum\limits_{\forall h\{n\}}maxn)$ 考虑求 $\sum\limits_{i=1}^{\inf}\sum\limits_{\forall h\{n\}}[i\le maxn]$。具体地，我们考虑每个位置有多少选择是小于 $i$ 的，全部乘起来容斥掉即可。

- $(\sum\limits_{\forall h\{n\}}\sum\limits_{i=1}^npre_i),(\sum\limits_{\forall h\{n\}}\sum\limits_{i=1}^nnxt_i)$ 这两个等价，沿用上面的思路，我们考虑求 $\sum\limits_{i=1}^{\inf}\sum\limits_{\forall h\{n\}}\sum\limits_{i=1}^n[i\le pre_i]$，我们设 $f_{i,0/1}$ 表示长度为 $i$ 的前缀最大值是否不小于 $i$ 的方案数最终的数量就是 $\sum\limits_{i=1}^nf_{i,1}\times 2^{n-i}$，我们考虑一个位置 $x$：

  - 如果 $a_x,b_x$ 都小于 $i$，有 $\begin{cases}f_{i,0}=2f_{i-1,0}\\f_{i,1}=2f_{i-1,1}\end{cases}$。
  - 如果 $a_x,b_x$ 只有一个小于 $i$，有 $\begin{cases}f_{i,0}=f_{i-1,0}\\f_{i,1}=f_{i-1,0}+2f_{i-1,1}\end{cases}$。
  - 如果 $a_x,b_x$ 都不小于 $i$，有 $\begin{cases}f_{i,0}=0\\f_{i,1}=2f_{i-1,0}+2f_{i-1,1}\end{cases}$。

容易发现这个可以用线段树维护转移矩阵实现。

---

恶臭的代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
char buf[1000005],*p1,*p2;
#define gc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++)
int read(){
	int x=0,f=0,c=gc();
	while(!isdigit(c))f|=(c=='-'),c=gc();
	while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=gc();
	return f?-x:x;
}
const int mod=1e9+7;
int n,a[500005],b[500005];
struct node{
	int x,id;
	bool operator<(const node &t)const{return x<t.x;}
}x[1000005];
namespace Sol1{//算maxn
	struct ST{
		struct Node{
			int l,r,val;
		}c[2000005];
		void Build(int q,int l,int r){
			c[q].l=l;c[q].r=r;
			if(l==r){
				c[q].val=0;
				return;
			}
			int mid=l+r>>1;
			Build(q<<1,l,mid);
			Build(q<<1|1,mid+1,r);
			c[q].val=c[q<<1].val*c[q<<1|1].val%mod;
		}
		void Change(int q,int x,int y){
			if(c[q].l==c[q].r){
				c[q].val+=y;
				return;
			}
			int mid=c[q].l+c[q].r>>1;
			if(x<=mid)Change(q<<1,x,y);
			else Change(q<<1|1,x,y);
			c[q].val=c[q<<1].val*c[q<<1|1].val%mod;
		}
	}T;
	int main(){
		int tot=0;
		for(int i=1;i<=n;i++)x[++tot]=node({a[i],i}),x[++tot]=node({b[i],i});
		sort(x+1,x+tot+1);
		int Pow=1;
		for(int i=1;i<=n;i++)Pow=Pow*2%mod;
		int res=0;
		int las=0;
		T.Build(1,1,n);
		for(int i=1;i<=tot;i++){
			res=(res+(x[i].x-las+mod)%mod*(Pow-T.c[1].val+mod)%mod)%mod;
			T.Change(1,x[i].id,1);
			las=x[i].x;
		}
		return res;
	}
}
namespace Sol2{//算前缀
	struct M{
		int a[2][2];
		M(int op=0){
			a[0][0]=a[1][1]=op;
			a[1][0]=a[0][1]=0;
		}
		M operator+(const M &t)const{
			M res;
			res.a[0][0]=(a[0][0]+t.a[0][0])%mod;
			res.a[0][1]=(a[0][1]+t.a[0][1])%mod;
			res.a[1][0]=(a[1][0]+t.a[1][0])%mod;
			res.a[1][1]=(a[1][1]+t.a[1][1])%mod;
			return res;
		}
		M operator*(const M &t)const{
			M res;
			res.a[0][0]=(a[0][0]*t.a[0][0]+a[0][1]*t.a[1][0])%mod;
			res.a[0][1]=(a[0][0]*t.a[0][1]+a[0][1]*t.a[1][1])%mod;
			res.a[1][0]=(a[1][0]*t.a[0][0]+a[1][1]*t.a[1][0])%mod;
			res.a[1][1]=(a[1][0]*t.a[0][1]+a[1][1]*t.a[1][1])%mod;
			return res;
		}
		M operator*(const int &x)const{
			M res;
			res.a[0][0]=a[0][0]*x%mod;
			res.a[0][1]=a[0][1]*x%mod;
			res.a[1][0]=a[1][0]*x%mod;
			res.a[1][1]=a[1][1]*x%mod;
			return res;
		}
	}A0,A1,A2;
	int Pow[500005];
	struct ST{
		struct Node{
			int l,r;
			M val,sum;
		}c[2000005];
		void up(int q){
			int mid=c[q].l+c[q].r>>1;
			c[q].val=c[q<<1].val*c[q<<1|1].val;
			c[q].sum=(c[q<<1].sum*Pow[c[q].r-mid])+(c[q<<1].val*c[q<<1|1].sum);
		}
		void Build(int q,int l,int r){
			c[q].l=l;c[q].r=r;
			if(l==r){
				c[q].val=c[q].sum=A2;
				return;
			}
			int mid=c[q].l+c[q].r>>1;
			Build(q<<1,l,mid);
			Build(q<<1|1,mid+1,r);
			up(q);
		}
		void Change(int q,int x,const M &y){
			if(c[q].l==c[q].r){
				c[q].val=c[q].sum=y;
				return;
			}
			int mid=c[q].l+c[q].r>>1;
			if(x<=mid)Change(q<<1,x,y);
			else Change(q<<1|1,x,y);
			up(q);
		}
	}T;
	int sss[500005];
	int main(){
		A0.a[0][0]=2;A0.a[0][1]=0;
		A0.a[1][0]=0;A0.a[1][1]=2;
		
		A1.a[0][0]=1;A1.a[0][1]=1;
		A1.a[1][0]=0;A1.a[1][1]=2;
		
		A2.a[0][0]=0;A2.a[0][1]=2;
		A2.a[1][0]=0;A2.a[1][1]=2;
		Pow[0]=1;
		for(int i=1;i<=n;i++)Pow[i]=Pow[i-1]*2%mod,sss[i]=2;
		int tot=0,res=0;
		for(int i=1;i<=n;i++)x[++tot]=node({a[i],i}),x[++tot]=node({b[i],i});
		sort(x+1,x+tot+1);
		T.Build(1,1,n);
		for(int i=1;i<=tot;i++){
			res=(res+(x[i].x-x[i-1].x)%mod*T.c[1].sum.a[0][1]%mod)%mod;
			sss[x[i].id]--;
			if(sss[x[i].id]==1)T.Change(1,x[i].id,A1);
			else T.Change(1,x[i].id,A0);
		}
		return res;
	}
}
signed main()
{
	n=read();
	int sum=0;
	for(int i=1;i<=n;i++)a[i]=read(),sum=(sum+a[i])%mod;
	for(int i=1;i<=n;i++)b[i]=read(),sum=(sum+b[i])%mod;
	for(int i=1;i<n;i++)sum=sum*2%mod;
	int sss=Sol1::main()*n%mod;
	int ss=Sol2::main();
	for(int i=1;i+i<=n;i++)swap(a[i],a[n-i+1]),swap(b[i],b[n-i+1]);
	ss=(ss+Sol2::main());
	printf("%lld",(ss-sum-sss+mod+mod)%mod);
	return 0;
}
```

---

