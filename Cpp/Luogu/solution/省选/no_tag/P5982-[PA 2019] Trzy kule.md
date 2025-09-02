# [PA 2019] Trzy kule

## 题目描述

对于两个长度为 $n$ 的 $01$ 串 $a_{1..n},b_{1..n}$，定义它们的距离 $\operatorname{d(a,b)}=|a_1-b_1|+|a_2-b_2|+...+|a_n-b_n|$。

给定三个长度为 $n$的 $01$ 串 $s_1,s_2,s_3$以及三个非负整数 $r_1,r_2,r_3(0\le r_i\le n)$，问有多少个长度为 $n$ 的 $01$ 串 $S$满足$\operatorname{d(S,s[1])}\le r_1,\operatorname{d(S,s[2])}\le r_2,\operatorname{d(S,s[3])}\le r_3$ 这三个不等式中至少有一个成立。

## 说明/提示

对于 $100\%$ 的数据，$1\le n\le 10^4$。

## 样例 #1

### 输入

```
5
2 10110
0 11010
1 00000```

### 输出

```
19```

# 题解

## 作者：CYZZ (赞：10)

# [P5982](https://www.luogu.com.cn/problem/P5982)
感觉思路挺自然的，但是本人太菜调试了数年。
## 思路
首先，正难则反，用总方案数减去三个都不满足的方案数。

对于一个位置，填 $1$ 和填 $0$ 所造成的贡献完全相反。假如填 $1$ 造成的贡献是 $(1,1,0)$，填 $0$ 则贡献 $(0,0,1)$，其他情况类似。

对于每个位置按照**造成的贡献**进行分类。由于每个位置有两种贡献方式，所以我们钦定**对 $\rm{d}(S,s_1)$ 贡献为 $1$  的贡献方式**为分类的依据。这样就会分出 $(1,1,1),(1,1,0),(1,0,1),(1,0,0)$ 四类。同时设 $(x,y,z)$ 这一类的个数为 $G_{xyz}$，比如 $(1,1,0)$ 的个数为 $G_{110}$。

考虑我们要计数的东西是什么。也就是在 $G_{xyz}$ 个位置中挑选 $F_{xyz}$ 个造成 $(x,y,z)$ 的贡献，余下 $G_{xyz}-F_{xyz}$ 个位置造成 $(x\oplus1,y\oplus1,z\oplus1)$ 的贡献。使得最终的 $d(S,S_i)$ 满足条件。

具体的，统计 $i=F_{111},j=F_{110},p=F_{101},q=F_{100}$ 的个数，使其满足下列不等式：

$$\begin{cases}
i+j+p+q>r_1\\
i+j+G_{101}-p+G_{100}-q>r_2\\
i+G_{110}-j+p+G_{100}-q>r_3
\end{cases}$$

这样就有了 $\mathcal{O}(n^4)$ 的做法：暴力枚举 ，判断其是否合法。注意加入答案时需要乘一个系数 $\binom{G_{111}}{i}\binom{G_{110}}{j}\binom{G_{101}}{p}\binom{G_{100}}{q}$。

考虑如何优化。发现一次枚举四个很蠢，试一下只枚举两个。枚举 $i,j$，上面的不等式移项得：

$$\begin{cases}
p+q>r_1\\
p+q<i+j+G_{101}+G_{100}-r_2\\
p-q>r_3-i+j-G_{110}-G_{100}
\end{cases}$$

发现 $p+q,p-q$ 的范围都是一个区间。换句话说，如果把 $(p+q,p-q)$ 看成坐标系中的一个点，那么需要统计的区间就是一个**矩阵**。

都有矩阵了，怎么能没有二维前缀和呢。开始时对于每个 $p,q$ 令 $sum_{p+q,p-q}=\binom{G_{101}}{p}\binom{G_{100}}{q}$，后面对于每个 $i,j$ 用二维前缀和统计答案即可。

这题有一些细节，比如 $p-q$ 可能是负数，需要加一个极大值作为下标，还要把下标整体加 $1$ 等等。具体实现可以参考代码。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define mod 1000000007
int n,S[5],a[10005][5];
int cnt[2][2][2];
int fac[10005],inv[10005];
void init()
{
	fac[0]=inv[0]=fac[1]=inv[1]=1;
	for(int i=2;i<=n;i++)
	{
		fac[i]=1ll*fac[i-1]*i%mod;
		inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
	}
	for(int i=2;i<=n;i++) inv[i]=1ll*inv[i-1]*inv[i]%mod;	
}
int C(int x,int y)
{
	return 1ll*fac[x]*inv[y]%mod*inv[x-y]%mod;
}
int sum[20005][10005];
void Add(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
void Del(int &x,int y){x-=y;(x<0)&&(x+=mod);}
int query(int xx,int xy,int yx,int yy)
{
	if(xx<0||xy<0) return 0;
	if(xx>cnt[1][0][1]+10000||yx>cnt[1][0][1]+10000) return 0;
	yy=max(yy,0);
	xy=min(xy,cnt[1][0][0]+cnt[1][0][1]);
	if(xx<yx||xy<yy) return 0;
	int ret=0;
	Add(ret,sum[xx+1][xy+1]); 
	Del(ret,sum[xx+1][yy]);
	Del(ret,sum[yx][xy+1]);
	Add(ret,sum[yx][yy]);
	return ret;
}
int main()
{
	scanf("%d",&n);init();
	for(int i:{1,2,3})
	{
		scanf("%d",&S[i]);
		for(int j=1;j<=n;j++)
		{
			scanf("%1d",&a[j][i]);
		}
	}
	for(int i=1;i<=n;i++)
	{
		int x=a[i][1],y=a[i][2],z=a[i][3];
		if(!a[i][1]) x^=1,y^=1,z^=1;
		cnt[x][y][z]++;
	}
	for(int i=0;i<=cnt[1][0][1];i++)
	{
		for(int j=0;j<=cnt[1][0][0];j++)
		{
			sum[i-j+10001][i+j+1]=1ll*C(cnt[1][0][1],i)*C(cnt[1][0][0],j)%mod;
		}
	}
	for(int i=-cnt[1][0][0];i<=cnt[1][0][1];i++)
	{
		for(int j=0;j<=cnt[1][0][0]+cnt[1][0][1];j++)
		{
			Add(sum[i+10001][j+1],sum[i+10000][j+1]);
			Add(sum[i+10001][j+1],sum[i+10001][j]);
			Del(sum[i+10001][j+1],sum[i+10000][j]);
		}
	}
	int ans=0,tot=1;
	for(int i=1;i<=n;i++) tot=1ll*tot*2%mod;
	for(int i=0;i<=cnt[1][1][1];i++)
	{
		for(int j=0;j<=cnt[1][1][0];j++)
		{
			Add(ans,1ll*C(cnt[1][1][1],i)*C(cnt[1][1][0],j)%mod*
			query(cnt[1][0][1]+10000,cnt[1][0][1]+cnt[1][0][0]+i+j-S[2]-1,S[3]-cnt[1][1][0]-cnt[1][0][0]-i+j+10000+1,S[1]-i-j+1)%mod);
		}
	}
	Del(tot,ans); 
	printf("%d",tot);
}
```
点个赞再走吧。

---

## 作者：AxDea (赞：2)

总方案为 $2^n$ 种，首先有补集转化，求三个条件都不满足的个数。

为了方便，下文中 $d(a,b) \gets \sum_{i=1}^n [a_i = b_i]$ ， $r_i \gets n - r_i - 1$ 。

首先，若设 $s_{i,j} \gets [s_{1,j} = s_{i,j}]$ ，则三元组 $(s_{1, i}, s_{2, i}, s_{3, i})$ 只有 $(1,1,1)\ (1,1,0)\ (1,0,1)\ (1,0,0)$ 四种情况。

设这四种情况出现的个数分别为 $k_1, k_2, k_3, k_4$ ，位置集合分别为 $P_1, P_2, P_3, P_4$。

对于情况 $i$ ，设 $t_i = \sum_{j\in P_i} [S_j = s_{1,j}]$ 。

显然有不等式组：

$$\begin{cases}
\ t_1 + t_2 + t_3 + t_4 \leq r_1 \\
\ t_1 + t_2 + k_3 - t_3 + k_4 - t_4 \leq r_2 \\ 
\ t_1 + k_2 - t_2 + t_3 + k_4 - t_3 \leq r_3 \\
\end{cases}$$

暴力枚举 $t_i$ 可以获得一个 $\mathcal{O}(n^4)$ 的算法。

在暴力算法中每次统计时，单次答案为 ${k_1 \choose t_1}{k_2 \choose t_2}\times{k_3 \choose t_3}{k_4 \choose t_4}$ 。

考虑 meet in the middle 的思想优化将原复杂度开根号。

设 $F(i,j) = \sum_{t_1} \sum_{t_2} {k_1 \choose t_1}{k_2 \choose t_2}$ ，其中 $t_1,t_2$ 满足 $i = t_1 + t_2$ , $j = t_1 + k_2 - t_2$ 。

将不等式移项，发现不等式中的 $t_1+t_2 \leq r'_1$ ， $t_1+k_2-t_2 \leq r'_2$ （ $r'_1,r'_2$ 为两个量），可知任意一对 $(t_3,t_4)$ 对于答案的贡献即为 ${k_3 \choose t_3}{k_4 \choose t_4}\sum_{i=0}^{r'_1}\sum_{j=0}^{r'_2} F(i,j)$ 。

接下来对于 $F$ 做二维前缀和处理，即可在 $\mathcal{O}(n^2)$ 的时间内统计出答案。

Code(C++):
```cpp
#include<bits/stdc++.h>
#define forn(i,s,t) for(register int i=(s);i<=(t);++i)
#define form(i,s,t) for(register int i=(s);i>=(t);--i)
using namespace std;
const int N = 1e4+3, Mod = 1e9+7;
template<typename T>inline T Max(T A, T B) {return A>B?A:B;}
template<typename T>inline T Min(T A, T B) {return A<B?A:B;}
inline int q_pow(int p, int k) {
	int Ans = 1;
	while(k) {
		if(k & 1) Ans = 1ll * Ans * p %Mod;
		p = 1ll * p * p %Mod;
		k >>= 1;
	}
	return Ans;
}
int fac[N], inv[N];
inline void Init(int n) {
	fac[0] = 1;
	forn(i,1,n) fac[i] = 1ll * i * fac[i-1] %Mod;
	inv[n] = q_pow(fac[n], Mod - 2);
	form(i,n-1,0) inv[i] = 1ll * inv[i+1] * (i+1ll) %Mod;
}
inline int C(int n, int k) {
	return 1ll * fac[n] * inv[k] %Mod * inv[n - k] %Mod;
}
int n, r[3], k[4], sum[N][N];
char s[3][N];
int main() {
	scanf("%d", &n);
	Init(n);
	forn(i,0,2) {
		scanf("%d", r+i);
		r[i] = n - r[i] - 1;
		if(r[i] < 0) {
			return printf("%d\n", q_pow(2, n)), 0;
		}
		scanf("%s", s[i] + 1);
	}
	forn(i,1,n) {
		if(s[0][i] == s[1][i] && s[1][i] == s[2][i]) k[0] ++ ;
		else if(s[0][i] == s[1][i]) k[1] ++ ;
		else if(s[0][i] == s[2][i]) k[2] ++ ;
		else k[3] ++ ;
	}
	int Tr = 0, Tc = 0;
	forn(t0,0,k[0]) forn(t1,0,k[1]) {
		int tx = t0 + t1;
		if(tx > r[0] || tx > r[1]) continue ;
		int ty = t0 + k[1] - t1;
		if(ty > r[2]) continue ;
		Tr = Max(Tr, tx), Tc = Max(Tc, ty);
		sum[tx][ty] += 1ll * C(k[0], t0) * C(k[1], t1) %Mod;
		sum[tx][ty] %= Mod;
	}
	forn(i,0,Tr) forn(j,0,Tc) {
		i && (sum[i][j] += sum[i-1][j], sum[i][j] %= Mod);
		j && (sum[i][j] += sum[i][j-1], sum[i][j] %= Mod);
		(i && j) && (sum[i][j] += Mod - sum[i-1][j-1], sum[i][j] %= Mod);
	}
	int Ans = 0;
	forn(t2,0,k[2]) forn(t3,0,k[3]) {
		int tx = Min(r[0] - t2 - t3, r[1] - (k[2] + k[3]) + (t2 + t3));
		if(tx < 0) continue ;
		int ty = r[2] - t2 - k[3] + t3;
		if(ty < 0) continue ;
		tx = Min(tx, Tr), ty = Min(ty, Tc);
		Ans += 1ll * sum[tx][ty] * C(k[2], t2) %Mod * C(k[3], t3) %Mod;
		Ans %= Mod;
	}
	Ans = Mod - Ans, Ans += q_pow(2, n), Ans %= Mod;
	printf("%d\n", Ans);
	return 0;
}
```

---

## 作者：mrsrz (赞：2)

[可能更好的体验](https://mrsrz.github.io/2020/03/31/PA2019TrzyKule/)

我们可以先把 $s_1$ 变为全 $1$，$s_2$ 和 $s_3$ 进行变换使得每一位都对应即可。

总的字符串个数是 $2^n$，我们考虑求出以上三个条件都**不满足**的串的个数。

我们考虑每个位，由于 $s_1$ 已经是全 $1$，那么三个字符串的这个位的情况只有四种：`100`，`101`，`110`，`111`。设它们的出现次数分别为 $a_1,a_2,a_3,a_4$。

我们考虑枚举 `110` 和 `111`  的出现个数 $i,j$，那么 `001` 和 `000` 的出现个数就为 $a_3-i$，$a_4-j$。

这种情况下，第一个字符串和第二个字符串中出现的 $1$ 的个数是一样的，都是 $i+j$，而第三个字符串中出现的 $1$ 的个数为 $i+a_4-j$。

我们设 `100` 和 `101` 的出现次数分别为 $x,y$，那么我们需要满足以下三个不等式，才能对**不满足条件**的串产生贡献。

- $i+j+x+y\gt t_1$
- $i+j+(a_1-x)+(a_2-y)\gt t_2$
- $i+(a_4-j)+(a_1-x)+y\gt t_3$

整理后可得：

- $i+j\gt t_1-x-y$
- $i+j\gt t_2-(a_1-x)-(a_2-y)$
- $i+(a_4-j)\gt t_3-(a_1-x)-y$

可以合并为两个式子 $i+j\gt \max(t_1-x-y,t_2-(a_1-x)-(a_2-y))$，$i-j\gt t_3-(a_1-x)-y-a_4$。

$(i+j,i-j)$ 是可以唯一确定一组 $i,j$ 的。

不难发现，可以和一组 $x,y$ 产生贡献的 $i,j$，其对应的 $(i+j,i-j)$ 都落在一个矩形区域内。

那么，我们可以先枚举 $i,j$，其本身有 $\binom{a_3}i\binom{a_4}j$ 种不同方案。我们把这个方案加到二维平面上的点 $(i+j,i-j)$ 处。

然后枚举 $x,y$，其本身有 $\binom{a_1}x\binom{a_2}y$ 种不同方案。我们需要统计一个矩形区域内的和，这个可以预处理二维前缀和。之后用乘法原理即可计算方案数。

时空复杂度 $O(n^2)$。可能需要卡常。

## Code：

```cpp
#pragma GCC optimize("Ofast")
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long LL;
const int N=10005,md=1e9+7;
int t1,t2,t3,_111,_101,_100,_110,n,fac[N],iv[N];
char s1[N],s2[N],s3[N];
inline int pow(int a,int b){
	int ret=1;
	for(;b;b>>=1,a=(LL)a*a%md)if(b&1)ret=(LL)ret*a%md;
	return ret;
}
inline int C(int x,int y){return(LL)fac[x]*iv[y]%md*iv[x-y]%md;}
int D[N][N],ans;
inline void upd(int&a){a+=a>>31&md;}
int main(){
	scanf("%d%d%s%d%s%d%s",&n,&t1,s1+1,&t2,s2+1,&t3,s3+1);
	for(int i=1;i<=n;++i){
		if(s1[i]==s2[i]&&s2[i]==s3[i])++_111;else
		if(s1[i]==s2[i])++_110;else
		if(s1[i]==s3[i])++_101;else
		++_100;
	}
	if(_110>_101)swap(_110,_101),swap(t2,t3);
	if(_110>_100)swap(_110,_100),swap(t1,t3);
	for(int i=*fac=1;i<=n;++i)fac[i]=(LL)fac[i-1]*i%md;
	iv[n]=pow(fac[n],md-2);
	for(int i=n-1;~i;--i)iv[i]=(i+1LL)*iv[i+1]%md;
	for(int i=0;i<=_110;++i)
	for(int j=0;j<=_111;++j){
		int A=i+j,B=j+_110-i;
		D[A][B]=(D[A][B]+C(_110,i)*(LL)C(_111,j))%md;
	}
	for(int i=_110+_111;~i;--i){
		int*X=D[i],*Y=D[i+1];
		for(int j=_110+_111-max(i-_111,0);~j;--j)
		X[j]=((LL)X[j]+Y[j]+X[j+1]-Y[j+1]+md)%md;
	}
	for(int i=0;i<=_100;++i)
	for(int j=0;j<=_101;++j){
		int LA=max(t1+1-i-j,t2+1-(_100-i)-(_101-j)),LB=t3+1-(j+_100-i);
		if(LA<0)LA=0;if(LB<0)LB=0;
		ans=(ans+(LL)D[LA][LB]*C(_100,i)%md*C(_101,j))%md;
	}
	upd(ans=pow(2,n)-ans);
	printf("%d\n",ans);
	return 0;
}
```



---

## 作者：Felix72 (赞：1)

这题用到了一点中途相遇的思想。设对于某一位 $i$，三个 $s$ 第 $i$ 位全部相同的 $i$ 有 $cnt_0$ 个，只有 $s_1$ 不同的 $i$ 有 $cnt_1$ 个，类似地定义 $cnt_2, cnt_3$。因此我们可以枚举 $cnt_i$ 的个数，组合数计算，复杂度 $O(n^4)$。

接着我们知道一个四元组 $\{cnt_0, cnt_1, cnt_2, cnt_3\}$ 合法的条件是一组不等式，枚举其中的两个元素，不等式就可以简化为对剩下两个数和或者差的两组限制，相当于让我们手动计算两条斜率为 $1$ 或 $-1$ 线的半平面交。这是可以用二维前缀和解决的。

```cpp
 /* NE_Cat 4.1 */
#include <bits/stdc++.h>
#define lowbit(x) ((x) & (-(x)))
using namespace std;

const int N = 10010, mod = 1e9 + 7;
inline void Plus(int &now, int add) {now += add; while(now >= mod) now -= mod; while(now < 0) now += mod;}
inline void Plus(long long &now, long long add) {now += add; while(now >= mod) now -= mod; while(now < 0) now += mod;}
long long fac[N], inv[N];
inline long long qpow(long long a, long long b)
{
	long long res = 1;
	while(b) {if(b & 1) res = res * a % mod; b >>= 1, a = a * a % mod;}
	return res;
}
inline long long C(int n, int m)
{
	if(n < m) return 0;
	return fac[n] * inv[m] % mod * inv[n - m] % mod;
}
inline void init_math()
{
	fac[0] = inv[0] = 1;
	for(int i = 1; i <= 10000; ++i) fac[i] = fac[i - 1] * i % mod;
	inv[10000] = qpow(fac[10000], mod - 2);
	for(int i = 9999; i >= 1; --i) inv[i] = inv[i + 1] * (i + 1) % mod;
}
int n, r[4], s[5], a[5], res, all; string str[4];
vector < int > f[N], g[3][N];

int main()
{
//	freopen("text.in", "r", stdin);
//	freopen("prog.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	init_math();
	cin >> n;
	for(int i = 1; i <= 3; ++i)
		cin >> r[i] >> str[i], str[i] = ' ' + str[i];
	for(int i = 1; i <= n; ++i)
	{
		if(str[1][i] == str[2][i] && str[1][i] == str[3][i]) ++s[4];
		else if(str[1][i] != str[2][i] && str[1][i] != str[3][i]) ++s[1];
		else if(str[2][i] != str[1][i] && str[2][i] != str[3][i]) ++s[2];
		else if(str[3][i] != str[1][i] && str[3][i] != str[1][i]) ++s[3];
	}
	for(int i = 0; i <= s[4] + 1; ++i)
	{
		f[i].resize(s[1] + 2);
		for(int j = 0; j <= 2; ++j) g[j][i].resize(s[1] + 2);
	}
//	cerr << "S : " << s[1] << " " << s[2] << " " << s[3] << " " << s[4] << '\n';
//	for(a[2] = 0; a[2] <= s[2]; ++a[2])
//		for(a[3] = 0; a[3] <= s[3]; ++a[3])
//			for(a[4] = 0; a[4] <= s[4]; ++a[4])
//				for(a[1] = 0; a[1] <= s[1]; ++a[1])
//					if(a[1] + a[4] > r[1] - s[2] - s[3] + a[2] + a[3] && a[4] - a[1] > max(r[2] - s[1] - s[3] - a[2] + a[3], r[3] - s[1] - s[2] + a[2] - a[3]))
//						cerr << "OK " << a[2] << " " << a[3] << " " << a[4] << " " << a[1] << '\n';
	for(a[2] = 0; a[2] <= s[2]; ++a[2])
	{
		for(a[3] = 0; a[3] <= s[3]; ++a[3])
		{
			int lim[2] = {r[1] - s[2] - s[3] + a[2] + a[3], max(r[2] - s[1] - s[3] - a[2] + a[3], r[3] - s[1] - s[2] + a[2] - a[3])};
			int val = 1ll * C(s[2], a[2]) * C(s[3], a[3]) % mod;
			lim[0] = max(lim[0] + 1, 0);
			lim[1] = min(-lim[1] - 1, s[1]);
			if(lim[0] < lim[1])
			{
				Plus(g[0][0][lim[0]], val); Plus(g[1][0][lim[1]], val);
				Plus(g[2][0][lim[0] + 1], val), Plus(g[2][0][lim[1]], -val);
			}
			else
			{
				int d = (lim[0] - lim[1] + 1) / 2;
				d = max(d, lim[0] - s[1]), d = max(d, 0 - lim[1]);
				lim[0] -= d, lim[1] += d;
				lim[0] = max(0, lim[0]), lim[1] = min(lim[1], s[1]);
				if(d > s[4]) continue;
				if(lim[0] > lim[1]) continue;
				if(lim[0] == lim[1])
				{
					Plus(g[0][d][lim[0]], val);
					if(d + 1 <= s[4] && lim[1] + 1 <= s[1]) Plus(g[1][d + 1][lim[1] + 1], val);
				}
				else
				{
					Plus(g[0][d][lim[0]], val);
					Plus(g[1][d][lim[1]], val);
				}
			}
		}
	}
	for(int i = 0; i <= s[4]; ++i)
	{
		for(int j = 0; j <= s[1]; ++j)
		{
			f[i][j] = ((g[0][i][j] + g[1][i][j]) % mod + g[2][i][j]) % mod;
			if(i < s[4] && j > 0) Plus(g[0][i + 1][j - 1], g[0][i][j]);
			if(i < s[4] && j < s[1]) Plus(g[1][i + 1][j + 1], g[1][i][j]);
			if(j < s[1]) Plus(g[2][i][j + 1], g[2][i][j]);
		}
	}
	for(int i = 0; i < s[4]; ++i)
		for(int j = 0; j <= s[1]; ++j)
			Plus(f[i + 1][j], f[i][j]);
	for(int i = 0; i <= s[4]; ++i)
		for(int j = 0; j <= s[1]; ++j)
			Plus(res, 1ll * f[i][j] * C(s[4], i) % mod * C(s[1], j) % mod);
	all = 1; for(int i = 1; i <= n; ++i) all = all * 2 % mod;
	cout << (all - res + mod) % mod << '\n';
	return 0;
}
/*

*/
```

---

## 作者：Purslane (赞：1)

# Solution

不难。

发现本质不同的下标只有 $4$ 种，由 $(s_{2,i} \oplus s_{1,i},s_{3,i} \oplus s_{1,i})$ 决定。

考虑正难则反，你需要计算三个数都 $\ge$ 某个限制的情况。

假设这四种下标分别有 $a_1$、$a_2$、$a_3$、$a_4$ 个。设它们取了 $x_1$、$x_2$、$x_3$、$x_4$ 给 $S$ 产生贡献，则限制是：

$$
x_1 + x_2 + x_3 + x_4 \ge C_1 \\
x_1 + x_2 - x_3 - x_4 \ge C_2 \\
x_1 - x_2 + x_3 - x_4 \ge C_3
$$

你枚举一下 $x_1$ 和 $x_4$，得到对 $x_2 \pm x_3$ 的限制，而且这是唯一限制。

那么直接二维前缀和记录一下就行了。（因为 $0 \le x_2 + x_3 \le a_2 + a_3$，$-a_3 \le x_2 - x_3 \le a_2$，所以你的数组开到 $10000 \times 10000$ 就够了。）

时空复杂度都是 $O(n^2)$。

本题使用了坐标变换的技巧，其基本思路是：先考虑枚举需要计算的东西（比如，如果你枚举 $\sum x_i$ 和 $x_4$ 能得到 $x_2$ 和 $x_3$ 的限制，但是你发现你根本不能处理 $x_1$。因为你相当于使用正常坐标预处理，而使用变换的坐标计算答案。所以枚举需要计算的东西就很牛 /qiang），在预处理中加入坐标变换。

---

