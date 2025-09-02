# Running Competition

## 题目描述

A running competition is going to be held soon. The stadium where the competition will be held can be represented by several segments on the coordinate plane:

- two horizontal segments: one connecting the points $ (0,         0) $ and $ (x, 0) $ , the other connecting the points $ (0,         y) $ and $ (x, y) $ ;
- $ n + 1 $ vertical segments, numbered from $ 0 $ to $ n $ . The $ i $ -th segment connects the points $ (a_i,         0) $ and $ (a_i, y) $ ; $ 0 = a_0 < a_1 < a_2 <         \dots < a_{n - 1} < a_n = x $ .

For example, here is a picture of the stadium with $ x = 10 $ , $ y = 5 $ , $ n = 3 $ and $ a = [0, 3, 5, 10] $ :

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1398G/81bd381693fb1325b3353cdccb69047f4e9ca225.png)A lap is a route that goes along the segments, starts and finishes at the same point, and never intersects itself (the only two points of a lap that coincide are its starting point and ending point). The length of a lap is a total distance travelled around it. For example, the red route in the picture representing the stadium is a lap of length $ 24 $ .

The competition will be held in $ q $ stages. The $ i $ -th stage has length $ l_i $ , and the organizers want to choose a lap for each stage such that the length of the lap is a divisor of $ l_i $ . The organizers don't want to choose short laps for the stages, so for each stage, they want to find the maximum possible length of a suitable lap.

Help the organizers to calculate the maximum possible lengths of the laps for the stages! In other words, for every $ l_i $ , find the maximum possible integer $ L $ such that $ l_i \bmod L =       0 $ , and there exists a lap of length exactly $ L $ .

If it is impossible to choose such a lap then print $ -1 $ .

## 样例 #1

### 输入

```
3 10 5
0 3 5 10
6
24 30 14 16 18 10```

### 输出

```
24 30 14 16 -1 -1```

# 题解

## 作者：Froggy (赞：6)

容易发现图中所有简单回路都是一个宽（与 $y$ 轴平行的边）为 $y$ 的矩形。

那么所有满足题意的长度都形如 $2(a_i-a_j+y)$，其中 $i>j$。

很容易想到直接 $\mathcal{O}(n^2)$ 枚举 $i,j$ 暴力求出所有合法长度，然后枚举倍数 $\mathcal{O}(x\log x)$ 预处理出所有答案，这样就能 $\mathcal{O}(1)$ 回答单个询问。

需要优化 $\mathcal{O}(n^2)$ 的部分。

---

## Sol 1：

使用 `bitset` 来优化。

具体做法就是先搞一个初始 bitset，对于所有的 $i$，把所有第 $a_i$ 位设成 $1$，其他位设成 $0$。

把所有左移 $a_i$ 位的初始的 bitset 或起来得到最终要求的 bitset，满足若第 $k$ 位 $1$ 则至少一组 $(i,j)$ 满足 $a_i-a_j=k$。

这样就在 $\mathcal{O}(\frac{n^2}{\omega})$ 的时间复杂度内求出了所有合法长度。

虽然理论上过不去，但我没卡常就过了，不过最慢点跑了 $1825ms$。。

细节看代码。

***code:***

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<bitset>
using namespace std;
#define N 200002
const int mx=200000;
bitset<N> p,myh;
int n,x,y,a[N],ans[N<<2],Q;
int main(){
	n=read(),x=read(),y=read();
	for(int i=0;i<=n;++i){
		a[i]=read();
		p[a[i]]=1;
	}
	for(int i=0;i<=n;++i){
		myh|=p>>a[i];
	}
	for(int i=1;i<=x;++i){
		if(myh[i]){
			int gu=i+y;
			for(int j=gu;j<=500000;j+=gu){
				ans[j]=max(ans[j],gu);
			}
		}
	}
	Q=read();
	while(Q--){
		int L=read();
		printf("%d ",L&1||!ans[L>>1]?-1:ans[L>>1]<<1);
	}
	return 0;
}

```

## Sol 2：

搞出生成函数： $A(x)=\sum_{i=0}^nx^{a_i}$。

这不就是个减法卷积么？！

FFT/NTT 抬走。

时间复杂度：$\mathcal{O}(x\log x)$。

最慢点只跑了 $300ms$ 左右。

***code:***

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
#define N 600002
const int mx=200000;
const int mod=998244353;
const int G=3;
typedef vector<int> poly;
int n,x,y,tr[N],ans[N],Q;
inline int qpow(int a,int b){
	int ans=1;
	while(b){
		if(b&1)ans=1LL*ans*a%mod;
		a=1LL*a*a%mod;
		b>>=1;
	}
	return ans;
}
const int invG=qpow(G,mod-2);
int NTT_init(int n){
	int lim=1;
	while(lim<n)lim<<=1;
	for(int i=0;i<lim;++i){
		tr[i]=(tr[i>>1]>>1)|((i&1)?lim>>1:0);
	}
	return lim;
}
#define ck(x) (x>=mod?x-mod:x)
void NTT(poly &f,bool flag,int n){
	f.resize(n);
	for(int i=0;i<n;++i){
		if(i<tr[i])swap(f[i],f[tr[i]]);
	}
	for(int p=2;p<=n;p<<=1){
		int len=p>>1;
		int wn=qpow(flag?G:invG,(mod-1)/p);
		for(int k=0;k<n;k+=p){
			int buf=1;
			for(int i=k;i<k+len;++i){
				int t=1LL*buf*f[i+len]%mod;
				f[i+len]=ck(f[i]-t+mod);
				f[i]=ck(f[i]+t);
				buf=1LL*buf*wn%mod;
			}
		}
	}
	if(!flag){
		int invn=qpow(n,mod-2);
		for(int i=0;i<n;++i){
			f[i]=1LL*f[i]*invn%mod;
		}
	}
}	
poly Mul(poly A,poly B){
	int n=A.size()+B.size()-1;
	int lim=NTT_init(n);
	poly P(lim);
	NTT(A,1,lim),NTT(B,1,lim);
	for(int i=0;i<lim;++i){
		P[i]=1LL*A[i]*B[i]%mod;
	}
	NTT(P,0,lim);
	P.resize(n);
	return P;
}
int main(){
	n=read(),x=read(),y=read();
	poly A(x+1),B(x+1);
	for(int i=0;i<=n;++i){
		A[read()]=1;
	}
	B=A;
	reverse(B.begin(),B.end());
	poly C=Mul(A,B);
	for(int i=1;i<=x;++i){
		if(C[i+x]){
			int gu=i+y;
			for(int j=gu;j<=500000;j+=gu){
				ans[j]=max(ans[j],gu);
			}
		}
	}
	Q=read();
	while(Q--){
		int L=read();
		printf("%d ",L&1||!ans[L>>1]?-1:ans[L>>1]<<1);
	}
	return 0;
}
```

---

[*Froggy's blog*](https://www.luogu.org/blog/1445353309froggy/)

#### 呱!!

---

## 作者：YipChip (赞：0)

这个题本质上事项让我们求出所有合法的 $a_i - a_j$，构造生成函数 $F(x) = \sum_{i = 0}^nx^{a_i}$，我们可以将生成函数的系数反向，即 $G(x) = \sum_{i = 0}^nx^{M - a_i}$，把两个生成函数卷起来就可以得到哪些位置是合法的。

本题还需要处理的是输出 $L \mid l_i$ 的最大合法 $L$，我们可以找出所有的 $L$ 之后，枚举它的倍数更新合法数组，总体复杂度是 $O(n\log{n})$ 的，跑起来很快。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define ull unsigned long long
#define PII pair<ll, ll>
#define pb push_back
#define clr(f, n) memset(f, 0, sizeof(int) * (n))
#define cpy(f, g, n) memcpy(f, g, sizeof(int) * (n))
#define rev(f, n) reverse(f, f + (n))
const int N = 1e6 + 10, _G = 3, mod = 998244353;

ll qpow(ll a, ll k = mod - 2) {
    ll res = 1;
    while (k) {
        if (k & 1) res = res * a % mod;
        k >>= 1;
        a = a * a % mod;
    }
    return res;
}

const int invG = qpow(_G);
int rev[N << 1], rev_len;

void rev_init(int n) {
    if (rev_len == n) return;
    for (int i = 0; i < n; i ++ ) rev[i] = (rev[i >> 1] >> 1) | (i & 1 ? n >> 1 : 0);
    rev_len = n;
}

void NTT(int *g, int op, int n) {
    rev_init(n);
    static ull f[N << 1], Gk[N << 1] = {1};
    for (int i = 0; i < n; i ++ ) f[i] = g[rev[i]];
    for (int k = 1; k < n; k <<= 1) {
        int G1 = qpow(~op ? _G : invG, (mod - 1) / (k << 1));
        for (int i = 1; i < k; i ++ ) Gk[i] = Gk[i - 1] * G1 % mod;
        for (int i = 0; i < n; i += k << 1) {
            for (int j = 0; j < k; j ++ ) {
                int tmp = Gk[j] * f[i | j | k] % mod;
                f[i | j | k] = f[i | j] + mod - tmp;
                f[i | j] += tmp;
            }
        }
        if (k == (1 << 10)) for (int i = 0; i < n; i ++ ) f[i] %= mod;
    }
    if (~op) for (int i = 0; i < n; i ++ ) g[i] = f[i] % mod;
    else {
        int invn = qpow(n);
        for (int i = 0; i < n; i ++ ) g[i] = f[i] % mod * invn % mod;
    }
}

void px(int *f, int *g, int n) {
    for (int i = 0; i < n; i ++ ) f[i] = 1ll * f[i] * g[i] % mod;
}

void covolution(int *f, int *g, int len, int lim) {
    static int sav[N << 1];
    int n; for (n = 1; n < len << 1; n <<= 1);
    clr(sav, n); cpy(sav, g, n);
    NTT(sav, 1, n); NTT(f, 1, n);
    px(f, sav, n); NTT(f, -1, n);
    clr(f + lim, n - lim), clr(sav, n);
}

int n, q, x, y, a[N], cnt[N];
int F[N << 1], G[N << 1], maxn = 1e6;

void solve() {
    cin >> n >> x >> y;
    for (int i = 0; i <= n; i ++ ) cin >> a[i], F[a[i]] = 1, G[x - a[i]] = 1;
    covolution(F, G, x + 1, (x << 1) + 1);
    for (int i = 1; i <= x; i ++ ) cnt[i + y << 1] = (!!F[x + i]) * (i + y << 1);
    for (int i = y << 1; i <= maxn; i += 2) {
        if (!cnt[i]) continue;
        for (int j = i; j <= maxn; j += i) {
            if (cnt[j] < cnt[i]) cnt[j] = cnt[i];
        }
    }
    cin >> q;
    for (int i = 1, l; i <= q; i ++ ) {
        cin >> l;
        if (cnt[l]) cout << cnt[l] << " ";
        else cout << "-1 ";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T -- ) solve();
    return 0;
}
```

---

