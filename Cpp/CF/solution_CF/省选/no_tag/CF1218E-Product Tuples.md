# Product Tuples

## 题目描述

在 Stonefalls 的神秘区域中游荡时，为了掉落传奇战利品，一位冒险者接到了如下任务。他得到了一个长度为 $N$ 的数组 $A = \{a_1, a_2, ..., a_N\}$，以及一个数字 $K$。

定义数组 $B$ 为 $B(q, A) = \{q-a_1, q-a_2, ..., q-a_N\}$。定义函数 $F$，其中 $F(B, K)$ 表示数组 $B$ 中所有 $K$ 元组元素的乘积之和。例如，如果数组 $B$ 为 $[2,3,4,5]$，且 $K=3$，那么所有 3 元组乘积之和为
$$
F(B, 3) = 2 \times 3 \times 4 + 2 \times 3 \times 5 + 3 \times 4 \times 5 + 2 \times 4 \times 5
$$

接着，他又得到了一个数字 $Q$，表示有 $Q$ 个查询，每个查询有两种类型：

- 类型 1：给定 $q$、$i$ 和 $d$，计算 $F(B(q, A), K)$，其中对初始数组做出更改 $A[i] = d$。
- 类型 2：给定 $q$、$L$、$R$ 和 $d$，计算 $F(B(q, A), K)$，其中对初始数组做出更改 $A[i] = A[i] + d$，对于所有 $i$ 在区间 $[L, R]$ 内（包含两端）。

所有更改仅在本次查询中临时生效，不会影响后续查询。请帮助冒险者计算每个查询的答案，助他完成任务，最终获得战利品！

## 说明/提示

在第一个查询中，数组 $A = [1, 2, 3, 4, 5]$，$B = [5, 4, 3, 2, 1]$，所有 2 元组乘积之和为 $85$。

在第二个查询中，数组 $A = [1, 2, 3, 4, 2]$，$B = [5, 4, 3, 2, 4]$，所有 2 元组乘积之和为 $127$。

在第三个查询中，数组 $A = [1, 3, 4, 4, 5]$，$B = [5, 3, 2, 2, 1]$，所有 2 元组乘积之和为 $63$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5
2
1 2 3 4 5
3
1 6 1 1
1 6 5 2
2 6 2 3 1
```

### 输出

```
85
127
63
```

# 题解

## 作者：wcyQwQ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1218E)

[可能更好的阅读体验](https://chenyu-w.github.io./2023/03/06/CF1218E%20Product%20Tuples/)

简单的多项式，推荐和[序列操作](https://www.luogu.com.cn/problem/P4247)一起食用。

## 分析

首先 $Q \le 10$ 说明了每次操作暴力即可，所以考虑怎么求这个 $F(B, K)$，我们考虑对于每个 $k$，都求出它所对应的答案，那么我们考虑分治，假设我们现在计算完了 $[l, mid]$ 和 $[mid + 1, r]$ 这两个区间的答案，分别记为 $f$ 和 $g$，那么我们容易得到 $[l, r]$ 区间的答案 $h$ 满足 $h_n = \sum_k f_kg_{n - k}$，这是一个卷积的形式，可以用 $\text{NTT}$ 计算，所以直接分治就可以做到 $O(n\log^2 n)$，注意分治的边界为 $l = r$，此时 $f_0 = 1, f_1 = B_l$。

## 代码

```c++
#include <bits/stdc++.h>
#define L(i, j, k) for (int i = (j); i <= (k); i++)
#define R(i, j, k) for (int i = (j); i >= (k); i--)
#define G(i, u) for (int i = h[(u)]; ~i; i = ne[i])
#define ll long long
#define ld long double
#define ull unsigned long long

using namespace std;
const int N = 2e5 + 10, M = 30, mod = 998244353, G = 3;
int a[N], b[N], rev[N], res[M][N], tmpL[N], tmpR[N];

inline int read() {
    int x = 0, y = 1; char c = getchar();
    while (c < '0' || c > '9') {if (c == '-') y = -1; c = getchar();}
    while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * y;
}

inline int getMod(int x) {return (x % mod + mod) % mod;}

inline int mul(int x, int y) {return 1ll * x * y % mod;}

inline int qpow(int a, int b) {
	int res = 1;
	while (b) {
		if (b & 1) res = mul(res, a);
		a = mul(a, a);
		b >>= 1;
	}
	return res;
}

inline void ntt(int a[], int n, int flg) {
	L(i, 0, n - 1) if (i < rev[i]) swap(a[i], a[rev[i]]);
	for (int mid = 1; mid < n; mid <<= 1) {
		int W = qpow(G, (mod - 1) / (mid << 1));
		if (flg == -1) W = qpow(W, mod - 2);
		for (int i = 0; i < n; i += (mid << 1)) {
			int w = 1;
			L(j, i, i + mid - 1) {
				int x = a[j], y = mul(w, a[j + mid]);
				a[j] = (x + y) % mod, a[j + mid] = (x - y + mod) % mod;
				w = mul(w, W);
			}
		}
	}
}

inline void NTT(int a[], int b[], int n, int m) {
	int k = 1, l = 0;
	while (k <= n + m) k <<= 1, l++;
	L(i, n + 1, k) a[i] = 0;
	L(i, m + 1, k) b[i] = 0;
	L(i, 0, k - 1) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (l - 1));
	ntt(a, k, 1), ntt(b, k, 1);
	L(i, 0, k - 1) a[i] = mul(a[i], b[i]);
	ntt(a, k, -1);
	int invK = qpow(k, mod - 2);
	L(i, 0, n + m) a[i] = mul(a[i], invK);
}

inline void cdq(int d, int l, int r) {
	if (l == r) {
		res[d][0] = 1, res[d][1] = b[l];
		return;
	}
	int mid = (l + r) >> 1;
	cdq(d + 1, l, mid);
	L(i, 0, r - l + 1) res[d][i] = res[d + 1][i];
	cdq(d + 1, mid + 1, r);
	L(i, 0, mid - l + 1) tmpL[i] = res[d][i];
	L(i, 0, r - mid) tmpR[i] = res[d + 1][i];
	NTT(tmpL, tmpR, mid - l + 1, r - mid);
	L(i, 0, r - l + 1) res[d][i] = tmpL[i];
}

int main() {
	int n = read(), k = read();
	L(i, 1, n) a[i] = read();
	int m = read();
	while (m--) {
		memset(res, 0, sizeof res);
		int op = read(), q = read();
		if (op == 1) {
			int x = read(), y = read();
			L(i, 1, n) b[i] = i == x ? y : a[i];
			L(i, 1, n) b[i] = getMod(q - b[i]);
			cdq(0, 1, n);
			printf("%d\n", res[0][k]);
		}
		else {
			int l = read(), r = read(), d = read();
			L(i, 1, n) b[i] = i >= l && i <= r ? getMod(a[i] + d) : a[i];
			L(i, 1, n) b[i] = getMod(q - b[i]);
			cdq(0, 1, n);
			printf("%d\n", res[0][k]);
		}
	}
    return 0;
}
```



---

## 作者：lemondinosaur (赞：0)

[Codeforces](http://codeforces.com/problemset/problem/1218/E)

---
用 OGF 表示 $F(B,x)$ 就是

$$
\prod_{i=1}^n(1+(q-a_i)x)
$$

直接分治 NTT 把 $[x^k]$ 也就是这一位的系数求出来就可以了。

至于相互独立的询问直接暴力修改即可。

---
# 代码
```cpp
#define rr register
#define mem(f,n) memset(f,0,sizeof(int)*(n))
#define cpy(f,g,n) memcpy(f,g,sizeof(int)*(n))
using namespace std;
const int mod=998244353,inv3=332748118,N=20011;
typedef long long lll; typedef unsigned long long ull;
inline signed address(){
	for (rr int i=0;i<15;++i)
    	if (!v[i]) return i;
    return -1;
}
namespace Theoretic{
	int rev[N<<2],LAST; ull Wt[N<<2],F[N<<2];
	inline void Pro(int n){
		if (LAST==n) return; LAST=n,Wt[0]=1;
		for (rr int i=0;i<n;++i)
		    rev[i]=(rev[i>>1]>>1)|((i&1)?n>>1:0);
	}
	inline void NTT(int *f,int n,int op){
		Pro(n);
		for (rr int i=0;i<n;++i) F[i]=f[rev[i]];
	    for (rr int o=1,len=1;len<n;++o,len<<=1){
	    	rr int W=(op==1)?Gmi[o]:Imi[o];
	    	for (rr int j=1;j<len;++j) Wt[j]=Wt[j-1]*W%mod;
	    	for (rr int i=0;i<n;i+=len+len)
	    	for (rr int j=0;j<len;++j){
	    		rr int t=Wt[j]*F[i|j|len]%mod;
	    		F[i|j|len]=F[i|j]+mod-t,F[i|j]+=t;
			}
	    	if (o==10) for (rr int j=0;j<n;++j) F[j]%=mod;
		}
		if (op==-1){
			rr int invn=ksm(n,mod-2);
			for (rr int i=0;i<n;++i) F[i]=F[i]%mod*invn%mod;
		}else for (rr int i=0;i<n;++i) F[i]%=mod;
		for (rr int i=0;i<n;++i) f[i]=F[i];
    }
	inline void Cb(int *f,int *g,int n){
		for (rr int i=0;i<n;++i) f[i]=1ll*f[i]*g[i]%mod;
	}
	inline signed CDQ_NTT(int x,int l,int r){
		if (l==r){
			rr int now=address();
			len[now]=2,v[now]=ff[now][0]=1,
			ff[now][1]=x<a[l]?x-a[l]+mod:x-a[l];
			return now;
		}
		rr int mid=(l+r)>>1,L;
		rr int lef=CDQ_NTT(x,l,mid),rig=CDQ_NTT(x,mid+1,r);
		for (L=1;L<len[lef]+len[rig];L<<=1);
		NTT(ff[lef],L,1),NTT(ff[rig],L,1),Cb(ff[lef],ff[rig],L),
		mem(ff[rig],L),len[lef]+=len[rig],len[rig]=v[rig]=0,NTT(ff[lef],L,-1);
		return lef;
	}
}
inline void GmiImi(){
	for (rr int i=0;i<31;++i) Gmi[i]=ksm(3,(mod-1)/(1<<i));
	for (rr int i=0;i<31;++i) Imi[i]=ksm(inv3,(mod-1)/(1<<i));	
}
signed main(){
	n=iut(),m=iut(),GmiImi();
	for (rr int i=1;i<=n;++i) a[i]=iut();
	for (rr int Q=iut();Q;--Q){
		rr int opt=iut(),d=iut(),now;
		if (opt==1){
			rr int x=iut(),y=iut(),t=a[x];
			a[x]=y,now=Theoretic::CDQ_NTT(d,1,n),a[x]=t;
		}else{
			rr int l=iut(),r=iut(),x=iut();
			for (rr int i=l;i<=r;++i) a[i]=a[i]+x>=mod?a[i]+x-mod:a[i]+x;
			now=Theoretic::CDQ_NTT(d,1,n);
			for (rr int i=l;i<=r;++i) a[i]=a[i]<x?a[i]-x+mod:a[i]-x;
		}
		print(ff[now][m]),putchar(10);
		mem(ff[now],len[now]),len[now]=v[now]=0;
	}
    return 0;
}
```

---

