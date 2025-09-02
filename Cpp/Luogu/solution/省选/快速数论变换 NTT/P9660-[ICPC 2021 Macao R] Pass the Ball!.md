# [ICPC 2021 Macao R] Pass the Ball!

## 题目描述

有 $n$ 个孩子和 $n$ 个球在玩游戏。孩子和球都从 $1$ 编号到 $n$。

游戏开始前，给出了 $n$ 个整数 $p_1, p_2, \cdots, p_n$。在游戏的每一轮中，孩子 $i$ 会把他手里的球传给孩子 $p_i$。保证没有孩子会把他手里的球传给自己，也就是说 $p_i \neq i$。此外，我们还知道在每一轮之后，每个孩子手里都会正好持有一个球。

设 $b_i$ 表示孩子 $i$ 所持有的球。在游戏开始时，孩子 $i$（$1 \le i \le n$）将携带球 $i$，也就是说 $b_i=i$。你需要处理 $q$ 个查询。对于每个查询，你会得到一个整数 $k$，你需要计算在 $k$ 轮后 $\sum\limits_{i=1}^{n} i \times b_i$ 的值。

## 样例 #1

### 输入

```
4 4
2 4 1 3
1
2
3
4```

### 输出

```
25
20
25
30```

# 题解

## 作者：Graphcity (赞：0)

首先一个排列可以划分为若干个置换环，每个置换环是独立的。

先考虑只有一个置换环的情况。我们按照环上的顺序提取出元素 $a_{1\cdots n}$，并令 $b_i=b_{n+i}=a_i$。那么进行 $j(0\le j< n)$ 次操作的答案就是 $c_j=\sum_{i=1}^na_ib_{i+j}$。如果将 $a$ 翻转，就变成了 $c_j=\sum_{i=1}^na'_{n-i+1}b_{i+j}$。$j\ge n$ 时将 $j$ 对 $n$ 取模即可。

这是经典的多项式形式，考虑 NTT 加速。（由于 FFT 被卡精度了，这里使用三模 NTT）

我们已经用 $O(n\log n)$ 的时间复杂度解决了一个置换环的问题。对于多个环的情况，由于置换环的大小和为 $n$，所以总的时间复杂度依然为 $O(n\log n)$。但是每一个置换环都需要 $O(q)$ 来回答询问，置换环太多的时候会被卡成 $O(nq)$。

一个经典结论就是这些环中本质不同的大小只有 $O(\sqrt n)$ 个，因为 $\sum_{i=1}^{\sqrt n}i$ 是 $O(n)$ 级别的。对于每个本质不同的大小分别回答一遍询问即可。时间复杂度 $O(n\log n+q\sqrt n)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=3e5;

inline int Pow(int x,int y,int p)
{
    int res=1;
    while(y)
    {
        if(y&1) res=1ll*res*x%p;
        x=1ll*x*x%p,y>>=1;
    }
    return res;
}
inline int Inv(int x,int p) {return Pow(x,p-2,p);}
const int Mod1=998244353,Mod2=1004535809,Mod3=469762049,g=3;
const long long Modx=1ll*Mod1*Mod2;
const int inv1=Inv(Mod1,Mod2),inv2=Inv(Modx%Mod3,Mod3);
struct Int
{
    int a,b,c;
    inline Int() {}
    inline Int(int _x): a(_x),b(_x),c(_x) {}
    inline Int(int _a,int _b,int _c): a(_a),b(_b),c(_c) {}
    inline void Rev() {a=Inv(a,Mod1),b=Inv(b,Mod2),c=Inv(c,Mod3);}
    inline ll Count()
    {
        long long res=1ll*(b-a+Mod2)%Mod2*inv1%Mod2*Mod1+a;
        return (1ll*(c-res%Mod3+Mod3)%Mod3*inv2%Mod3*Modx+res);
    }
} F[Maxn+5],G[Maxn+5];
inline Int operator+(Int x,Int y) {return Int((x.a+y.a)%Mod1,(x.b+y.b)%Mod2,(x.c+y.c)%Mod3);}
inline Int operator-(Int x,Int y) {return Int((x.a-y.a%Mod1+Mod1)%Mod1,(x.b-y.b%Mod2+Mod2)%Mod2,(x.c-y.c%Mod3+Mod3)%Mod3);}
inline Int operator*(Int x,Int y) {return Int(1ll*x.a*y.a%Mod1,1ll*x.b*y.b%Mod2,1ll*x.c*y.c%Mod3);}

int n,m,K,p[Maxn+5],vis[Maxn+5]; ll ans[Maxn+5];
int A[Maxn*4+5],B[Maxn*4+5],q[Maxn+5]; ll C[Maxn*4+5];
vector<int> v[Maxn+5];
vector<ll> h[Maxn+5];

struct Poly
{
    int lim=1,len,rev[Maxn*4+5];
    Int F[Maxn*4+5],G[Maxn*4+5];
    inline void GetLim(int n)
    {
        lim=1,len=0;
        while(lim<=n) lim<<=1,len++;
        For(i,0,lim-1) rev[i]=(rev[i>>1]>>1)|((i&1)<<len-1);
    }
    inline void NTT(Int *A,int opt)
    {
        Int ninv=Int(Inv(lim,Mod1),Inv(lim,Mod2),Inv(lim,Mod3));
        For(i,0,lim-1) if(i<rev[i]) swap(A[i],A[rev[i]]);
        for(int l=2,mid=1;l<=lim;l<<=1,mid<<=1)
        {
            Int wi=Int(Pow(g,(Mod1-1)/l,Mod1),Pow(g,(Mod2-1)/l,Mod2),Pow(g,(Mod3-1)/l,Mod3));
            if(opt==-1) wi.Rev();
            for(int j=0;j<lim;j+=l)
            {
                Int w=Int(1);
                for(int k=0;k<mid;++k)
                {
                    Int f=A[j+k],t=A[j+k+mid]*w;
                    A[j+k]=f+t,A[j+k+mid]=f-t;
                    w=w*wi;            
                }
            }
        }
        if(opt==-1) For(i,0,lim-1) A[i]=A[i]*ninv;
    }
    inline void GetMul(int *A,int *B,ll *C)
    {
        For(i,0,lim-1) F[i]=A[i],G[i]=B[i];
        NTT(F,1),NTT(G,1);
        For(i,0,lim-1) F[i]=F[i]*G[i];
        NTT(F,-1);
        For(i,0,lim-1) C[i]=F[i].Count();
    }
} P;

inline void Solve(int id)
{
    int s=v[id].size(); P.GetLim(s*3);
    For(i,0,P.lim-1) A[i]=B[i]=C[i]=0;
    For(i,1,s) A[i]=B[i]=B[s+i]=v[id][i-1];
    reverse(A+1,A+s+1),P.GetMul(A,B,C);
    if(h[s].empty()) h[s].resize(s+2);
    For(i,0,s-1) h[s][i]+=C[s+i+1];
}

int main()
{
    ios::sync_with_stdio(false);
    
    cin>>n>>K;
    For(i,1,n) cin>>p[i];
    For(i,1,n) if(!vis[i])
    {
        ++m; for(int j=i;!vis[j];j=p[j])
            v[m].push_back(j),vis[j]=1;
    }
    For(i,1,m) Solve(i);
    For(i,1,K) cin>>q[i];
    For(i,1,n) if(!h[i].empty())
        For(j,1,K) ans[j]+=h[i][q[j]%i];
    For(i,1,K) cout<<ans[i]<<endl;
    return 0;
}
```



---

## 作者：chroneZ (赞：0)

还算典的一道题（？）

将排列按 $i \to p_i$ 连边，最后会形成若干置换环。考虑将询问离线后，对每个置换环计算贡献。

记置换环的大小为 $m$，考虑怎么预处理 $k \in [0, m - 1]$ 的答案。记 $\{s_m\}$ 为一有序序列，满足对于所有 $i \in [1, m - 1]$，置换环上存在一条 $s_{i - 1} \to s_i$ 的边（即从置换环上任意一点出发走 $m - 1$ 步形成的序列）。容易发现，最后需要对每个 $k$ 计算 $\sum \limits_{i = 0} ^ {m - 1} s_i s_{(i + k) \bmod m}$。如果我们断环成链，也即对于所有 $i \in [m, 2m - 1], s_i \gets s_{i - m}$，则这个式子可以化为 $\sum \limits_{i = 0} ^ {m - 1} s_i s_{i + k}$。显然的差卷积形式，因此可以 $\Theta(m \log m)$ 地完成预处理。对于一次询问 $k$，这个置换环的贡献是预处理出来的 $k \bmod m$ 处的点值。

注意预处理过后不要直接 $\mathcal{O}(q)$ 地把这个环的贡献直接加到每个询问上，因为环的数量很多时复杂度就假了。观察到一件事情，本质不同的置换环大小只会有 $\Theta(\sqrt n)$ 种，而相同大小的置换环贡献是可以直接相加的。这启发我们对于同种大小的置换环一并处理后，再将贡献加到答案上。

总时间复杂度 $\Theta(n \log n + q\sqrt n)$。

~~赛时作者因为 FFT 的精度问题吃了七发罚时，所以建议用 NTT + CRT 计算卷积。~~

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

namespace Polynomial {
	static constexpr int N = 1 << 20; int mod, invg;
	namespace basic {
		inline int add(int x, int y) {return (x + y >= mod ? x + y - mod : x + y);}
		inline int dec(int x, int y) {return (x - y < 0 ? x - y + mod : x - y);}
		inline void ad(int &x, int y) {x = add(x, y);}
		inline void de(int &x, int y) {x = dec(x, y);}

		inline int qpow(int a, int b) {
			int r = 1;
			while(b) {
				if(b & 1) r = 1ll * r * a % mod;
				a = 1ll * a * a % mod; b >>= 1;
			}
			return r;
		}
		inline int inv(int x) {return qpow(x, mod - 2);}

		int fac[N], ifac[N];
		inline void fac_init(int n = N - 1) {
			fac[0] = 1;
			for(int i = 1; i <= n; i++)
				fac[i] = 1ll * fac[i - 1] * i % mod;
			ifac[n] = inv(fac[n]);
			for(int i = n - 1; i >= 0; i--)
				ifac[i] = 1ll * ifac[i + 1] * (i + 1) % mod;
		}
		int invx[N];
		inline void inv_init(int n = N - 1) {
			invx[1] = 1;
			for(int i = 2; i <= n; i++)
				invx[i] = 1ll * (mod - mod / i) * invx[mod % i] % mod;
		}
		inline int binom(int n, int m) {
			if(n < m || m < 0) return 0;
			return 1ll * fac[n] * ifac[m] % mod * ifac[n - m] % mod;
		}

		int rev[N];
		inline void rev_init(int n) {
			for(int i = 1; i < n; i++)
				rev[i] = (rev[i >> 1] >> 1) + (i & 1 ? n >> 1 : 0);
		}
	}
	using namespace basic;

	struct poly {
		vector<int> a;
		inline int size() {return (int)a.size();}
		inline void clear() {a.clear();}
		inline void resize(int n) {a.resize(n);}
		inline void Rev() {reverse(a.begin(), a.end());}
		inline int & operator [] (int x) {assert(x < size()); return a[x];}
		inline int v(int x) {return (x < size() ? a[x] : 0);}

		poly(int n = 0) {resize(n);}
		poly(vector<int> o) {a = o;}
		poly(const poly &o) {a = o.a;}

		friend poly operator * (poly x, int y) {
			vector<int> res(x.size());
			for(int i = 0; i < x.size(); i++)
				res[i] = 1ll * x[i] * y % mod;
			return poly(res);
		}
		friend poly operator + (poly x, poly y) {
			vector<int> res(max(x.size(), y.size()));
			for(int i = 0; i < res.size(); i++) 
				res[i] = add(x.v(i), y.v(i));
			return poly(res);
		}
		friend poly operator - (poly x, poly y) {
			vector<int> res(max(x.size(), y.size()));
			for(int i = 0; i < res.size(); i++) 
				res[i] = dec(x.v(i), y.v(i));
			return poly(res);
		}
		poly & operator += (poly o) {
			resize(max(size(), o.size()));
			for(int i = 0; i < size(); i++)
				ad(a[i], o.v(i));
			return (*this);
		}
		poly & operator -= (poly o) {
			resize(max(size(), o.size()));
			for(int i = 0; i < size(); i++)
				de(a[i], o.v(i));
			return (*this);
		}
		poly & operator *= (int x) {
			for(int i = 0; i < size(); i++)
				a[i] = 1ll * a[i] * x % mod;
			return (*this);
		}

		using f64 = double;
		using comp = complex<f64>;
		static void FFT(vector<comp> &f, int type) {	
			int n = f.size(); rev_init(n);
			for(int i = 1; i < n; i++)
				if(i < rev[i]) swap(f[i], f[rev[i]]);
			constexpr f64 PI = acos(-1);
			static comp wr[N]; wr[0] = {1, 0};
			for(int d = 1; d < n; d <<= 1) {
				comp wd = {cos(PI / d), type * sin(PI / d)};
				for(int i = 1; i < d; i++)
					wr[i] = wr[i - 1] * wd;
				for(int i = 0; i < n; i += d << 1) {
					for(int j = 0; j < d; j++) {
						comp x = f[i + j], y = wr[j] * f[i + j + d];
						f[i + j] = x + y, f[i + j + d] = x - y;
					}
				}
			}
			if(type == -1) 
				for(int i = 0; i < n; i++)
					f[i] /= n;
		}

		inline void NTT(int type) {
			int n = size(); rev_init(n);
			for(int i = 1; i < n; i++)
				if(i < rev[i]) swap(a[i], a[rev[i]]);
			static int gr[N]; gr[0] = 1;
			for(int d = 1; d < n; d <<= 1) {
				int gd = qpow(type == 1 ? 3 : invg, (mod - 1) / (d << 1));
				for(int i = 1; i < d; i++) gr[i] = 1ll * gr[i - 1] * gd % mod;
				for(int i = 0; i < n; i += d << 1) {
					for(int j = 0; j < d; j++) {
						int x = a[i + j], y = 1ll * gr[j] * a[i + j + d] % mod;
						a[i + j] = add(x, y), a[i + j + d] = dec(x, y);
					}
				}
			}
			if(type == -1) 
				for(int i = 0, invn = qpow(n, mod - 2); i < n; i++)
					a[i] = 1ll * a[i] * invn % mod;
		}

		friend poly operator * (poly x, poly y) {
			int L = 1, all = x.size() + y.size() - 1;
			while(L < all) L <<= 1;
			x.resize(L), y.resize(L);

			x.NTT(1); y.NTT(1);
			for(int i = 0; i < L; i++)
				x[i] = 1ll * x[i] * y[i] % mod;
			x.NTT(-1); x.resize(all);
			return x;
			/* Fast-Fourier-Transform Version:
			vector<comp> t(L);
			for(int i = 0; i < L; i++)
				t[i] = {x[i], y[i]};
			FFT(t, 1);
			for(int i = 0; i < L; i++)
				t[i] *= t[i];
			FFT(t, -1);
			poly res(all);
			for(int i = 0; i < all; i++)
				res[i] = (int)(t[i].imag() / 2 + 0.5);
			return res; */
		}
		poly & operator *= (poly x) {
			return (*this) = (*this) * x;
		}
		poly Deriv() {
			if(!size()) return poly();
			poly res(size() - 1);
			for(int i = 0; i < res.size(); i++)
				res[i] = 1ll * a[i + 1] * (i + 1) % mod;
			return res;
		}
		poly Integ() {
			if(!size()) return poly();
			poly res(size() + 1); inv_init(size());
			for(int i = 1; i < res.size(); i++)
				res[i] = 1ll * a[i - 1] * invx[i] % mod;
			return res;
		}
		poly Inv() {
			// H <- H * (2 - F * H)
			poly f, h;
			h.resize(1); h[0] = inv(a[0]);
			for(int d = 2; d < size() << 1; d <<= 1) {
				f.resize(d << 1), h.resize(d << 1);
				for(int i = 0; i < d; i++) f[i] = (*this).v(i);
				for(int i = d; i < d << 1; i++) f[i] = 0;
				f.NTT(1), h.NTT(1);
				for(int i = 0; i < d << 1; i++) h[i] = 1ll * h[i] * dec(2, 1ll * f[i] * h[i] % mod) % mod;
				h.NTT(-1);
				for(int i = d; i < d << 1; i++) h[i] = 0;
			}
			h.resize(size()); return h;
		}
		poly Ln() {
			assert(a[0] == 1);
			poly g = ((*this).Inv() * (*this).Deriv()).Integ();
			g.resize(size()); return g;
		}
	};
}
using namespace Polynomial;

constexpr int mod1 = 998244353, mod2 = 1004535809;

i64 n, q, p[N], qr[N];

int vis[N]; 
i64 res[N], ans[N];
vector<vector<int>> rec[N];

inline i64 mul(i64 x, i64 y, i64 p) {
	i64 r = 0;
	while(y) {
		if(y & 1) r = (r + x) % p;
		x = (x + x) % p, y >>= 1;
	}
	return r;
}

void solve(vector<int> s) {
	int m = s.size();
	poly f(m * 2), g(m);
	for(int i = 0; i < m; i++) {
		f[i] = f[i + m] = g[i] = s[i];
	}
	g.Rev();
	mod = mod1, invg = (mod + 1) / 3;
	poly r = f * g;
	mod = mod2, invg = (mod + 1) / 3;
	poly r2 = f * g;
	for(int i = 0; i < m; i++) {
		i64 x = r[m - 1 + i], y = r2[m - 1 + i];
		mod = mod1; i64 I1 = inv(mod2);
		mod = mod2; i64 I2 = inv(mod1);
		i64 mall = 1ll * mod1 * mod2;
		i64 z = mul(mul(x, mod2, mall), I1, mall);
		i64 w = mul(mul(y, mod1, mall), I2, mall);
		res[i] += (z + w) % mall;
	}
}

int main() {
	ios::sync_with_stdio(false); 
	cin.tie(nullptr); cout.tie(nullptr);
	
	cin >> n >> q;
	for(int i = 1; i <= n; i++) {
		cin >> p[i];
	}
	for(int i = 1; i <= q; i++) {
		cin >> qr[i];
	}
	for(int i = 1; i <= n; i++) {
		if(vis[i]) continue;
		vector<int> s; s.push_back(i); vis[i] = 1;
		int cur = p[i];
		while(cur != i) {
			s.push_back(cur); vis[cur] = 1;
			cur = p[cur];
		}
		rec[s.size()].push_back(s);
	}
	for(int i = 1; i <= n; i++) {
		if(rec[i].empty()) continue;
		for(int j = 0; j < i; j++) {
			res[j] = 0;
		}
		for(auto s : rec[i]) {
			solve(s);
		}
		for(int j = 1; j <= q; j++) {
			i64 p = qr[j]; p %= i;
			ans[j] += res[p];
		}
	}
	for(int i = 1; i <= q; i++) {
		cout << ans[i] << "\n";
	}
}
```

---

