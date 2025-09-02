# Illumination

## 题目描述

考虑坐标轴上的一段区间 $[0, d]$。在该区间内有 $n$ 个灯笼和 $m$ 个兴趣点。

对于每个灯笼，你可以为其选择一个功率——一个在 $0$ 到 $d$ 之间（包含 $0$ 和 $d$）的整数。坐标为 $x$ 的灯笼可以照亮坐标为 $y$ 的兴趣点，当且仅当 $|x - y|$ 小于等于该灯笼的功率。

如果所有兴趣点都被至少一个灯笼照亮，则称为所有灯笼分配功率的一种方案是合法的。

你需要处理 $q$ 个询问。每个询问由一个整数 $f_i$ 表示。对于第 $i$ 个询问，你需要：

- 在坐标 $f_i$ 处添加一个灯笼；
- 计算所有灯笼分配功率的合法方案数，并输出其对 $998244353$ 取模的结果；
- 移除刚刚添加的灯笼。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
6 1 1
4
3
3
2 1 5```

### 输出

```
48
47
47```

## 样例 #2

### 输入

```
6 1 2
4
2 5
2
1 3```

### 输出

```
44
46```

## 样例 #3

### 输入

```
20 1 2
11
15 7
1
8```

### 输出

```
413```

## 样例 #4

### 输入

```
20 3 5
5 7 18
1 6 3 10 19
5
4 17 15 8 9```

### 输出

```
190431
187503
188085
189903
189708```

# 题解

## 作者：enucai (赞：14)

## Preface

改数据范围不通知（$m$ 从 $18$ 改为 $16$），出题人你【数据删除】！

## Analysis

$m$ 只有 $16$，考虑容斥。先考虑不动态加点如何解决。

我们令 $f(S)$ 表示**不覆盖**到关键点集合 $S$ 的点灯方案数，则有：
$$
ans=\sum_{S\subset U}f(S)\times (-1)^{|S|}
$$
这样计算出的 $ans$ 是覆盖了除最左与最右两点之外的所有点但不覆盖最左最右点的方案数，只要加上 $-\infty$ 与 $-\infty$ 两个点即可。

我们考虑如何计算 $f(S)$。不覆盖到关键点集合 $S$ 等价于用 $S$ 中的位置将数轴划分为 $|S|+1$ 个区间，每个区间都不覆盖边界。我们可以 $O(nm^2)$ 预处理出 $g(l,r)$ 表示 $[p_l,p_r]$ 区间内的电灯都不覆盖 $p_l$ 与 $p_r$ 关键点的方案数。 则有：
$$
f(S)=\prod\limits_{i=1}^{|S|-1}g(S_i,S_{i+1})
$$

所以容斥复杂度为 $O(2^mm)$。

$g$ 数组的处理是平凡的。枚举所有灯 $i$，并枚举所有包含它的区间 $j$。令灯位置为 $a_i$，区间左右端点分别为 $l_j$ 与 $r_j$。则这盏灯的 power 范围是 $[0,\min\{a_i-l_j,r_j-a_i\})$。给 $j$ 的 $g$ 乘上它的贡献即可。复杂度 $O(nm^2)$。

至此，我们 $O(nm^2)-O(2^mm)$ 解决了静态问题。

考虑动态加灯。这盏灯对 $g$ 的修改是可以 $O(m^2)$ 解决的。但是如果每次更改后重新进行容斥，那么复杂度是不能接受的。于是一种方式是在动态加点前算出每个 $g$ 值对答案的贡献，这样单次询问是 $O(m^2)$ 的，可以通过，复杂度 $O(nm^2)-O(2^mm)-O(qm^2)$。

但是有另一种更为简介的方法可以在更优时间复杂度内（单次询问相同，预处理更优）解决此问题。

我们观察到每个容斥状态的值是所有子段值的连乘且所有子段不交且覆盖了区间 $(-\infty,+\infty)$，所以可以将容斥写成 dp 状物，即：
$$
dp_i=\sum_{j=1}^{i-1}(-1)\times dp_j\times g(j,i)
$$
那么容斥系数在每加一段后都会 $\times -1$，最后就是 $(-1)^{|S|}$。而 $\prod g$ 也在 dp 转移中进行了计算。最后答案为 $dp_{m+1}$。这样单次 dp 复杂度是 $O(m^2)$，可以通过此题。

最终复杂度 $O(nm^2-qm^2)$。具体细节见代码。

```cpp
#define int long long
const int mod=998244353;
const int N=200010;
const int M=20;
int d,n,m,q,a[N],p[M],coe[M][M],rec[M][M],f[M];
signed main(){IOS;
	cin>>d>>n>>m;
	For(i,1,n) cin>>a[i];
	For(i,1,m) cin>>p[i];
	sort(p+1,p+m+1);
	p[0]=-10*d,p[m+1]=10*d;
	For(i,0,m) For(j,i+1,m+1) coe[i][j]=1;
	For(i,1,n) For(l,0,m) For(r,l+1,m+1){
		if(p[l]<=a[i]&&a[i]<=p[r]) (coe[l][r]*=min({a[i]-p[l],p[r]-a[i],d+1}))%=mod;
	}
	For(l,0,m+1) For(r,l+1,m+1) rec[l][r]=coe[l][r];
	cin>>q;
	while(q--){
		int x; cin>>x;
		For(l,0,m+1) For(r,l+1,m+1) if(p[l]<=x&&x<=p[r]) (coe[l][r]*=min({x-p[l],p[r]-x,d+1}))%=mod;
		For(i,0,m+1) f[i]=0;
		f[0]=mod-1; For(i,1,m+1) For(j,0,i-1) f[i]=(f[i]+(mod-1)*f[j]%mod*coe[j][i]%mod)%mod;
		cout<<f[m+1]<<"\n";
		For(l,0,m+1) For(r,l+1,m+1) coe[l][r]=rec[l][r];
	}
}
```
## Postscript

所以 $m$ 可以开更大（大致能开到 $30$）？出题人你【数据删除】。

---

## 作者：Alex_Wei (赞：6)

将 $p$ 从小到大排序。

多次询问序列只改变一个位置的相关信息，考虑维护前后缀再合并。

对于新加入的灯笼，只有距离它最远的未被点亮的景点的距离会影响到方案数。

设 $pre_{i, j}$ 表示考虑 $[1, i]$ 的所有灯笼，其中第一个未被覆盖的景点为 $p_j$ 的方案数，$suf_{i, j}$ 表示考虑 $[i, d]$ 的所有灯笼，其中最后一个未被覆盖的景点为 $p_j$ 的方案数。

求出 $pre$ 和 $suf$，回答询问 $f$ 时枚举 $j$ 和 $k$，表示 $pre_{f - 1, j}$ 和 $suf_{f + 1, k}$。若 $j > k$，则 $f$ 的方案数为 $d + 1$，否则 $f$ 的方案数为 $d - \max(f - p_j, p_j - f) + 1$。

$pre$ 和 $suf$ 可以 $\mathcal{O}(nm ^ 2)$ 预处理，单次询问的复杂度为 $\mathcal{O}(m ^ 2)$。时间复杂度 $\mathcal{O}((n + q)m ^ 2)$。[代码](https://codeforces.com/contest/1728/submission/185907334)。

应该可以做到 $\mathcal{O}((n + q)m)$，但包含巨量细节和分类讨论。

---

## 作者：fanypcd (赞：4)

先考虑怎么算最开始的答案。

补集转化，定义 $f_S$ 表示钦定 $S$ 内的关键点不被覆盖，其它任意选的方法数，易知原答案可以表述为 $(d+1)^n-\sum\limits_{S}(-1)^{|S|}\cdot f_S$，其中 $f_S=\prod\limits_{i=1}^{n}\min\limits_{j \in S} |p_j-l_i|$。

考虑一个固定的 $S$ 中相邻的两个关键点 $i,j$，处于关键点之间的点有一个分界位置 $divp=\frac{p_i+p_j}{2}$，满足 $l_x \leq divp$ 的最近关键点是 $i$，反之为 $j$。

预处理出 $\prod \limits_{i}(p_j-l_i)$ 后可以在 $O(2^mm \log n)$ 的复杂度内算出所有 $f_S$。

考虑加上一个灯后答案的变化： $(d+1)^{n+1}-\sum \limits_{S} (-1)^{|S|}f'_S$，其中 $f'_S=f_S \cdot chv$，其中 $chv$ 为新加的灯不覆盖到 $S$ 中的任意一个关键点的方法数。

发现只需要关心 $S$ 中在灯之前和之后的两个最靠近的位置，于是定义 $g_{l,r,|S|\%2}=\sum\limits_{l,r \in S,\forall x \in[l+1,r-1],x \notin S} f_S$。

于是对于单组询问可以 $O(m^2)$ 枚举 $l,r$，复杂度 $O(nm+2^mm\log n+qm^2)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
template <class T> inline void read(T &x) {
	x = 0; int f = 0; char ch = getchar();
	while(!isdigit(ch))
		f |= ch == '-', ch = getchar();
	while(isdigit(ch))
		x = x * 10 + ch - 48, ch = getchar();
	x = f ? -x : x; return;
}
#define inf 0x3f3f3f3f
#define ll long long
#define fir first
#define sec second
#define N 200005
#define M 20
const int mod = 998244353;
int D, n, m;
int l[N], p[M];
inline int qpow(int a, int b) {
	int ans = 1; while(b) {
		if(b & 1) ans = 1ll * ans * a % mod;
		a = 1ll * a * a % mod; b >>= 1;
	}
	return ans;
}
int mulp1[M][N], mulp2[M][N];
inline int calc1(int p, int L, int R) {
	return 1ll * mulp1[p][R] * qpow(mulp1[p][L - 1], mod - 2) % mod;
}
inline int calc2(int p, int L, int R) {
	return 1ll * mulp2[p][R] * qpow(mulp2[p][L - 1], mod - 2) % mod;
}
int pos[M], pcnt;
int f[1 << M], g[M][M][2];
inline void addmod(int &x, int y) {
	x += y; if(x >= mod) x -= mod; return;
}
signed main() {
//	freopen("data.in", "r", stdin);
	read(D), read(n), read(m);
	for(int i = 1; i <= n; i++) read(l[i]);
	for(int i = 1; i <= m; i++) read(p[i]);
	sort(l + 1, l + n + 1);
	sort(p + 1, p + m + 1);
	for(int i = 1; i <= m; i++) {
		mulp1[i][0] = mulp2[i][0] = 1;
		for(int j = 1; j <= n; j++) {
			mulp1[i][j] = 1ll * mulp1[i][j - 1] * ((l[j] - p[i] + mod) % mod) % mod;
			mulp2[i][j] = 1ll * mulp2[i][j - 1] * ((p[i] - l[j] + mod) % mod) % mod;
		}
	}
//	int ans = qpow(D + 1, n);
	for(int st = 1; st < (1 << m); st++) {
		pcnt = 0; for(int i = 0; i < m; i++) {
			if((st >> i) & 1) {
				pos[++pcnt] = i + 1;
			}
		}
		int coef = 1;
		int pp = lower_bound(l + 1, l + n + 1, p[pos[pcnt]]) - l;
		coef = 1ll * coef * calc1(pos[pcnt], pp, n) % mod;
		int lst = pp = lower_bound(l + 1, l + n + 1, p[pos[1]]) - l - 1;
		coef = 1ll * coef * calc2(pos[1], 1, pp) % mod;
		if(pcnt != 1) {
			for(int i = 2; i <= pcnt; i++) {
				int divp = (p[pos[i - 1]] + p[pos[i]]) >> 1;
				pp = upper_bound(l + 1, l + n + 1, divp) - l - 1;
				coef = 1ll * coef * calc1(pos[i - 1], lst + 1, pp) % mod;
				lst = lower_bound(l + 1, l + n + 1, p[pos[i]]) - l - 1;
				coef = 1ll * coef * calc2(pos[i], pp + 1, lst) % mod;
			}
		}
//		printf("%d %d\n", st, (coef >= 100 ? coef - mod : coef));
		f[st] = coef;
		addmod(g[0][pos[1]][pcnt & 1], coef);
		addmod(g[pos[pcnt]][m + 1][pcnt & 1], coef);
		for(int i = 2; i <= pcnt; i++) {
			addmod(g[pos[i - 1]][pos[i]][pcnt & 1], coef);
		}
//		if(pcnt & 1) ans = (ans - f[st] + mod) % mod;
//		else ans = (ans + f[st]) % mod;
	}
//	printf("%d", ans);
	int q, adp; read(q); while(q--) {
		read(adp); int ans = qpow(D + 1, n + 1);
		int pr = lower_bound(p + 1, p + m + 1, adp) - p - 1;
		int nx = upper_bound(p + 1, p + m + 1, adp) - p;
		for(int l = pr; l >= 0; l--) {
			for(int r = nx; r <= m + 1; r++) {
				if(!l && r == m + 1) break;
				int thcv;
				if(!l) thcv = p[r] - adp;
				else if(r == m + 1) thcv = adp - p[l];
				else thcv = min(adp - p[l], p[r] - adp);
				addmod(ans, mod - 1ll * g[l][r][1] * thcv % mod);
				addmod(ans, 1ll * g[l][r][0] * thcv % mod);
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
```

---

## 作者：_SeeleVollerei_ (赞：4)

为了方便，先将 $p_i$ 排序。

先考虑单次询问怎么做，显然有个状压的 $O(n2^m)$ 的做法，但是我的能力范围内没什么前途，所以正难则反。

考虑容斥，对于一个集合 $S$，钦定这个集合内的特殊点没有被照亮，令 $g(S)$ 表示方案，那么答案为 $(d+1)^n-\sum (-1)^{|S|+1}g(S)$。

考虑怎么求 $g(S)$，发现其实相当于对于 $S$ 内相邻的特殊点，这两个特殊点之间的所有灯不能照到它们，相当于限制了这些灯的最大值，这样就有了一个 $O(n2^m)$ 的做法。进一步地，预处理一个 $mul_{l,r}$ 表示 $[p_l,p_r]$ 的所有灯碰不到特殊点 $p_l$ 和 $p_r$ 的方案数，然后求 $g(S)$ 的时候直接调用即可。复杂度 $O(m^2n+m2^m)$。

考虑多次询问，一种显然的思路是枚举新增的灯的值，但是不需要 $[0,d]$ 逐个枚举，因为它所能影响的本质不同的状态显然只有 $m$ 个。

考虑枚举这个状态，那么相当于需要初始的灯去照亮剩下的特殊点，所以预处理一个 $f_S$ 表示照亮集合内的特殊点的方案数即可，求法和单次询问一样。

复杂度要枚举子集，看似是 $O(3^m)$ 的，但是会发现关心的集合永远是一段前缀和一段后缀，所以关心的集合数也只有 $m^2$ 个，子集暴力枚举都可以了，复杂度 $O(m^22^m)$。

总复杂度为 $O(m^2n+m^22^m+qm)$。

https://codeforces.com/contest/1728/submission/171470230

---

## 作者：Owen_codeisking (赞：3)

题意：

给你一个范围 $[0,d]$ 的线段。现在有 $n$ 盏灯 $m$ 个点。

对于每一盏灯，你可以选择一个 $[0,d]$ 的照明范围。一盏在 $x$ 的灯可以照亮在 $[x-d,x+d]$ 的点。

一次合法的照明定义为所有的点都至少被一盏灯照亮。

现在你有 $q$ 次询问，每次询问会给定一个整数 $f_i$，回答一次询问，你需要：

- 添加一盏灯在 $f_i$ 处。
- 计算有多少种合法的照明方式。
- 删除这盏灯。

题解：

提供一个不同的思路。

先考虑 $q=0$ 怎么做。先将 $l,p$ 排序。

有一个 $dp$ 思路，$f_{i,j}$ 表示前 $i$ 盏灯，**连续**照亮了前 $j$ 个点的方案数。为什么是连续？可能会有照亮 $1,2,...,a,a+2,...,b$ 的情况，这时就需要一盏灯将 $a+1$ 照亮，此时延伸的范围一定比 $b$ 要远，所以是对的。

这样分类讨论就可以转移了。

如果有了询问，考虑矩阵加速。相当于前缀矩阵 $\times$ 当前矩阵 $\times$ 后缀矩阵。时间 $O(nm^3+qm^2)$。

卡常：

- 循环顺序改成 ``i,k,j``
- 每个位置只在最后取一次模。
- $16\times 998244352^2$ 要用 ``unsigned long long``

[code](https://codeforces.com/contest/1728/submission/171484948)



---

## 作者：ax_by_c (赞：1)

自己想的但是做法怎么和官方题解一样啊？？？

从静态问题入手，考虑状压。设 $f_{i,S}$ 表示使用前 $i$ 个灯，已经照亮点的集合为 $S$ 的方案数。

假设我们已经得到了 $f$，考虑如何回答询问。注意到将一盏灯所覆盖的点的编号状压只会有 $m$ 种不同的结果，所以可以直接枚举。设枚举的状态为 $S$，其补集为 $T$，则答案为 $\sum_{T\in P}f_{n,P}$。

发现最后是超集求和的形式，使用高维前缀和即可解决，问题是如何求 $f$。

考虑容斥，设 $g_{i,S}$ 表示使用前 $i$ 个灯，已经照亮点的集合为 $S$ 的子集的方案数。若求得 $g$，则使用高维差分即可求得 $f$。

求 $g$ 则较为简单，每个状态只会对超集产生贡献。于是枚举每一盏灯，发现一盏灯的状态都是包含关系，所以使用高维前缀积和逆元即可解决。

由于 $m$ 比较小，为了方便实现的时候直接进行了排序。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod=998244353;
ll ksm(ll a,ll b,ll p){
    a=a%p;
    ll r=1;
    while(b){
        if(b&1){
            r=r*a%p;
        }
        a=a*a%p;
        b>>=1;
    }
    return r%p;
}
ll inv(ll x){
    return ksm(x,mod-2,mod);
}
const int N=2e5+5;
const int M=20;
const int S=(1<<16)+5;
int len,n,m,q;
int a[N];
struct point{
    int val,id;
}pos[M];
int cmppos;
bool cmp(point x,point y){
    return abs(x.val-cmppos)<abs(y.val-cmppos);
}
ll f[S];
int main(){
    scanf("%d %d %d",&len,&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=m;i++){
        scanf("%d",&pos[i].val);
        pos[i].id=i;
    }
    int mxst=(1<<m)-1;
    for(int i=0;i<=mxst;i++){
        f[i]=1;
    }
    for(int i=1;i<=n;i++){
        cmppos=a[i];
        sort(pos+1,pos+1+m,cmp);
        int cur=0,st=0,nxt;
        if(abs(pos[1].val-a[i])!=0){
            f[0]=f[0]*abs(pos[1].val-a[i])%mod;
        }
        for(int j=1;j<=m;j++){
            cur=abs(pos[j].val-a[i]);
            st|=1<<(pos[j].id-1);
            if(j==m||cur!=abs(pos[j+1].val-a[i])){
                nxt=abs(pos[j+1].val-a[i]);
                if(j==m){
                    nxt=len+1;
                }
                f[st]=f[st]*inv(cur)%mod*nxt%mod;
            }
        }
    }
    for(int j=0;j<m;j++){
        for(int i=0;i<=mxst;i++){
            if(i&(1<<j)){
                f[i]=f[i]*f[i^(1<<j)]%mod;
            }
        }
    }
    for(int j=0;j<m;j++){
        for(int i=0;i<=mxst;i++){
            if(i&(1<<j)){
                f[i]=(f[i]-f[i^(1<<j)]+mod)%mod;
            }
        }
    }
    for(int j=0;j<m;j++){
        for(int i=0;i<=mxst;i++){
            if(i&(1<<j)){
                f[i^(1<<j)]=(f[i^(1<<j)]+f[i])%mod;
            }
        }
    }
    scanf("%d",&q);
    int p;
    while(q--){
        scanf("%d",&p);
        cmppos=p;
        sort(pos+1,pos+1+m,cmp);
        ll ans=0;
        int cur=0,st=0,nxt;
        if(abs(pos[1].val-p)!=0){
            ans=(ans+f[mxst]*abs(pos[1].val-p)%mod)%mod;
        }
        for(int j=1;j<=m;j++){
            cur=abs(pos[j].val-p);
            st|=1<<(pos[j].id-1);
            if(j==m||cur!=abs(pos[j+1].val-p)){
                nxt=abs(pos[j+1].val-p);
                if(j==m){
                    nxt=len+1;
                }
                ans=(ans+f[mxst^st]*(nxt-cur)%mod)%mod;
            }
        }
        printf("%lld\n",ans);
    }
    return 0;
}
```

---

