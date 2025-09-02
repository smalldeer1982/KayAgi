# Fibonotci

## 题目描述

Fibonotci sequence is an integer recursive sequence defined by the recurrence relation

 $ F_{n}=s_{n-1}·F_{n-1}+s_{n-2}·F_{n-2} $  with  $ F_{0}=0,F_{1}=1 $ Sequence $ s $ is an infinite and almost cyclic sequence with a cycle of length $ N $ . A sequence $ s $ is called almost cyclic with a cycle of length $ N $ if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF575A/489fd2e5fb549725a7a9de5a934f7a838952563f.png), for $ i>=N $ , except for a finite number of values $ s_{i} $ , for which ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF575A/3f92eca313b934333be63d48e6d251e408e4922e.png) ( $ i>=N $ ).

Following is an example of an almost cyclic sequence with a cycle of length 4:

 s = (5,3,8,11,5,3,7,11,5,3,8,11,…) Notice that the only value of $ s $ for which the equality ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF575A/c723ac9c89791a5b8e370fa82e33937eb7ce6a73.png) does not hold is $ s_{6} $ ( $ s_{6}=7 $ and $ s_{2}=8 $ ). You are given $ s_{0},s_{1},...s_{N-1} $ and all the values of sequence $ s $ for which ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF575A/3f92eca313b934333be63d48e6d251e408e4922e.png) ( $ i>=N $ ).

Find ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF575A/1ed5b2d60749876c1857042c6e156873ebb4e0f0.png).

## 样例 #1

### 输入

```
10 8
3
1 2 1
2
7 3
5 4
```

### 输出

```
4
```

# 题解

## 作者：Caiest_Oier (赞：11)

# [CF575A](https://www.luogu.com.cn/problem/CF575A)   

矩阵简单题。     

很明显的套路，对于 $m$ 个特殊位置排序，一个在 $x$ 处的特殊位置影响了 $x+1$ 和 $x+2$ 的值，于是分段跑一下矩阵乘积。    

至于这个矩阵乘积，可以考虑在模意义的位置上倍增。即令 $f_{i,j}$ 表示从 $i$ 转移 $2^j$ 得到的矩阵，$i\in[1,n)$，$j\in[0,62]$，从 $a$ 转移到 $b$，就倍增跳，每次跳到终点取模的位置上（但是要跳的距离不要取模）。于是就解决了这道题。

诸如特殊位置相邻之类的细节需要注意一下。   

~~丑陋的~~代码:

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k,m,P,now,k1,k2,k3,k4,k5,k6,k7,k8,k9;
int s[500003];
struct pr{
	int wz;
	int v;
}sp[500003];
struct Matrix{
	int h;
	int w;
	int v[2][2];
}res,ans;
Matrix operator*(Matrix A,Matrix B){
	res.h=B.h;
	res.w=A.w;
	for(int i=0;i<res.h;i++){
		for(int j=0;j<res.w;j++){
			res.v[i][j]=0; 
			for(int u=0;u<A.h;u++)res.v[i][j]=(res.v[i][j]+A.v[u][j]*B.v[i][u])%P;
		}
	}
	return res;
} 
bool comp(pr X,pr Y){
	return X.wz<Y.wz;
}
int fsp[63];
Matrix bz[50003][64];
void trans(int st,int ed){
	k9=st;
	k8=62;
	while(k8--){
		if(st+fsp[k8]<=ed){
			ans=ans*bz[st%n][k8];
			st+=fsp[k8];
		}
	}
	return;
}
signed main(){
	//freopen("b2.in","r",stdin);
	//freopen("b.out","w",stdout);
	fsp[0]=1;
	for(int i=1;i<=62;i++)fsp[i]=fsp[i-1]*2ll;
	scanf("%lld%lld",&k,&P);
	scanf("%lld",&n);
	for(int i=0;i<n;i++)scanf("%lld",&s[i]);
	for(int i=n;i<=2*n;i++)s[i]=s[i%n];
	scanf("%lld",&m);
	for(int i=1;i<=m;i++)scanf("%lld%lld",&sp[i].wz,&sp[i].v);
	for(int i=0;i<=n;i++){
		bz[i][0].h=bz[i][0].w=2;
		bz[i][0].v[0][0]=s[i];
		bz[i][0].v[0][1]=s[(i+n-1)%n];
		bz[i][0].v[1][0]=1;
		bz[i][0].v[1][1]=0;
	}
	for(int i=1;i<=62;i++){
		for(int j=0;j<=n;j++){
			bz[j][i]=bz[j][i-1]*bz[(j+fsp[i-1])%n][i-1];
		}
	}
	sp[++m].wz=1000000000000000010ll;
	sort(sp+1,sp+m+1,comp);
	if(k==0||P==1){
		puts("0");
		return 0;
	}
	if(k==1){
		puts("1");
		return 0;
	}
	ans.h=2;
	ans.w=1;
	ans.v[0][0]=1;
	ans.v[1][0]=0;
	now=1;
	for(int i=1;i<=m;i++){
		if(k<=sp[i].wz){
			trans(now,k);
			now=k;
			break;
		}
		else{
			trans(now,sp[i].wz);
			if(sp[i].wz+1==sp[i+1].wz){
				if(sp[i].wz-1==sp[i-1].wz&&i!=1)k1=(((sp[i].v*ans.v[0][0]+sp[i-1].v*ans.v[1][0])%P)+P)%P;
				else k1=(((sp[i].v*ans.v[0][0]+s[(sp[i].wz-1+n)%n]*ans.v[1][0])%P)+P)%P;
				ans.v[1][0]=ans.v[0][0];
				ans.v[0][0]=k1;
				now=sp[i].wz+1;
				if(now==k){
					printf("%lld",ans.v[0][0]);
					return 0;
				}
				continue;
			}
			if(sp[i].wz-1==sp[i-1].wz&&i!=1)k1=(((sp[i].v*ans.v[0][0]+sp[i-1].v*ans.v[1][0])%P)+P)%P;
			else k1=(((sp[i].v*ans.v[0][0]+s[(sp[i].wz-1+n)%n]*ans.v[1][0])%P)+P)%P;
			k2=(((k1*s[(sp[i].wz+1)%n]+ans.v[0][0]*sp[i].v)%P)+P)%P;
			if(k==sp[i].wz+1){
				printf("%lld",k1);
				return 0;
			}
			if(k==sp[i].wz+2){
				printf("%lld",k2);
				return 0;
			}
			now=sp[i].wz+2;
			ans.v[0][0]=k2;
			ans.v[1][0]=k1;
		}
	}
	printf("%lld",ans.v[0][0]%P);
	return 0;
}
```


---

## 作者：chenxia25 (赞：10)

集训队作业哦。

粉兔：“矩阵快速幂 sb 题。”

> ### [洛谷题目页面传送门](https://www.luogu.com.cn/problem/CF575A) & [CF 题目页面传送门](https://codeforces.com/contest/575/problem/A)

> 题意见洛谷。

一脸的矩阵，用矩阵把递推式表示出来：

$$\begin{bmatrix}f_i&f_{i+1}\end{bmatrix}\Delta_i=\begin{bmatrix}f_{i+1}&f_{i+2}\end{bmatrix}$$

其中

$$\Delta_i=\begin{bmatrix}0&s_i\\1&s_{i+1}\end{bmatrix}$$

那么答案就是

$$\left(\begin{bmatrix}f_0 & f_1\end{bmatrix}\prod_{i=0}^{k-1}\Delta_i\right)_{1,1}=\left(\prod_{i=0}^{k-1}\Delta_i\right)_{2,1}$$

只需要求那个 $\prod$ 即可。

注意到 $s$ 是有周期性的，$n$ 个一周期。先不考虑有 $m$ 个特殊点，这样显然可以算出 $n$ 个的积，然后快速幂。

如果有 $m$ 个特殊点呢？考虑在有特殊点处分段，有特殊点的周期们特殊算，无特殊点的周期段们快速幂。周期段数显然是 $\mathrm O(m)$ 的，那么快速幂部分就是 $\mathrm O(m\log)$。

如何快速维护特殊算部分呢？考虑在原 $n$ 个矩阵的乘积上修改，注意到一个特殊的 $s_i$ 只会影响 $\Delta_i$ 和 $\Delta_{i-1}$。但是矩阵乘法没有逆运算，不能直接除或 BIT；需要修改，也不能倍增。可以用线段树维护，单点修改，整体查积，每个有特殊点的周期算完就改回去。

时间复杂度 $\mathrm O(n+m\log)$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define mp make_pair
#define X first
#define Y second
#define pb push_back
#define int long long
const int inf=0x3f3f3f3f3f3f3f3f;
const int N=50000,M=50000;
int k,mod;
int n;
int s[N];
int m;
pair<int,int> v[M+1];
vector<pair<int,pair<bool,int> > > v0;
struct matrix{//矩阵 
	int a[2][2];
	int *operator[](int x){return a[x];}
	matrix(int x=0,int y=0,int z=0,int xx=0){
		a[0][0]=x,a[0][1]=y,a[1][0]=z,a[1][1]=xx;
	}
	friend matrix operator*(matrix x,matrix y){
		return matrix((x[0][0]*y[0][0]+x[0][1]*y[1][0])%mod,
		              (x[0][0]*y[0][1]+x[0][1]*y[1][1])%mod,
		              (x[1][0]*y[0][0]+x[1][1]*y[1][0])%mod,
		              (x[1][0]*y[0][1]+x[1][1]*y[1][1])%mod);
	}
	void prt(){printf("%lld %lld\n%lld %lld\n",a[0][0],a[0][1],a[1][0],a[1][1]);}
};
matrix qpow(matrix x,int y){//快速幂 
	matrix res(1,0,0,1);
	while(y){
		if(y&1)res=res*x;
		x=x*x;
		y>>=1;
	}
	return res;
}
struct segtree{//线段树 
	struct node{int l,r;matrix v;}nd[N<<2];
	#define l(p) nd[p].l
	#define r(p) nd[p].r
	#define v(p) nd[p].v
	void sprup(int p){v(p)=v(p<<1)*v(p<<1|1);}
	void bld(int l=0,int r=n-1,int p=1){
		l(p)=l;r(p)=r;
		if(l==r)return v(p)=matrix(0,s[l],1,s[(l+1)%n]),void();
		int mid=l+r>>1;
		bld(l,mid,p<<1);bld(mid+1,r,p<<1|1);
		sprup(p);
	}
	void init(){bld();}
	void chg(int x,bool y,int v,int p=1){
		if(l(p)==r(p))return v(p)[y][1]=v,void();
		int mid=l(p)+r(p)>>1;
		chg(x,y,v,p<<1|(x>mid));
		sprup(p);
	}
	matrix prod(int l=0,int r=n-1,int p=1){
		if(l>r)return matrix(1,0,0,1);
		if(l<=l(p)&&r>=r(p))return v(p);
		int mid=l(p)+r(p)>>1;
		matrix res(1,0,0,1);
		if(l<=mid)res=res*prod(l,r,p<<1);
		if(r>mid)res=res*prod(l,r,p<<1|1);
		return res;
	}
}segt;
signed main(){
	cin>>k>>mod;
	cin>>n;
	for(int i=0;i<n;i++)cin>>s[i];
	cin>>m;
	for(int i=1;i<=m;i++)cin>>v[i].X>>v[i].Y;
	v0.pb(mp(-n,mp(0,0)));v0.pb(mp(inf,mp(0,0)));
	for(int i=1;i<=m;i++){
		v0.pb(mp(v[i].X,mp(0,v[i].Y)));
		if(v[i].X)v0.pb(mp(v[i].X-1,mp(1,v[i].Y)));
	}
	sort(v0.begin(),v0.end());
	segt.init();
	matrix res(1,0,0,1);
	int las=0;
	for(int i=1,ie;i<v0.size();i=ie+1){
		ie=i;while(ie+1<v0.size()&&v0[ie+1].X/n==v0[i].X/n)ie++;
		if(v0[i].X/n>=k/n){las=v0[i-1].X/n;break;}
		res=res*qpow(segt.prod(),v0[i].X/n-1-v0[i-1].X/n);
		for(int j=i;j<=ie;j++)segt.chg(v0[j].X%n,v0[j].Y.X,v0[j].Y.Y);//修改 
		res=res*segt.prod();
		for(int j=i;j<=ie;j++)segt.chg(v0[j].X%n,v0[j].Y.X,v0[j].Y.X?s[(v0[j].X+1)%n]:s[v0[j].X%n]);//改回去 
	}
	res=res*qpow(segt.prod(),k/n-1-las);
	for(int i=0;i<v0.size();i++)if(v0[i].X/n==k/n)segt.chg(v0[i].X%n,v0[i].Y.X,v0[i].Y.Y);
	res=res*segt.prod(0,k%n-1);
	cout<<res[1][0];
	return 0;
}
```

---

## 作者：zzk2010 (赞：5)

[传送门](https://www.luogu.com.cn/problem/CF575A)

## 简要题意

给定序列 $s_0,s_1,s_2,\dots,s_{n-1}$，对于 $i \ge n$，特殊给出 $m$ 个 $s_i$，满足 $s_i \not= s_{i \bmod n}$，其他 $s_i$ 都满足 $s_i = s_{i \bmod n}$。

定义序列 $F$，$F$ 满足递推式 $F_n = s_{n-1} \cdot F_{n-1} + s_{n-2} \cdot F_{n-2}$，其中 $F_0 = 0, F_1 = 1$。

给出 $K, P$，请你求出 $F_K \bmod P$ 的值。

## 分析

$F$ 序列和斐波那契序列很像，因此考虑用矩阵来做转移：

$$
\begin{pmatrix}
   f_{i-2} & f_{i-1}
\end{pmatrix}
\begin{pmatrix}
   0 & s_{i-2} \\
   1 & s_{i-1}
\end{pmatrix}
=
\begin{pmatrix}
   f_{i-1} & f_{i}
\end{pmatrix}
$$

但是这样定义矩阵的话，对于 $m$ 个特殊的 $s_i$，每个特殊值会影响两个矩阵，写起来有一车细节，很不舒服。所以我们把矩阵递推式改一改：

$$
\begin{pmatrix}
   f_{i-2} s_{i-2} & f_{i-1}
\end{pmatrix}
\begin{pmatrix}
   0 & 1 \\
   s_{i-1} & s_{i-1}
\end{pmatrix}
=
\begin{pmatrix}
   f_{i-1} s_{i-1} & f_{i}
\end{pmatrix}
$$

这么一来，每个特殊值只会影响一个矩阵。下文中，记 $A_i$ 表示 $s_i$ 对应的形如 $\begin{pmatrix} 0 & 1 \\ s_i & s_i \end{pmatrix}$ 的矩阵。

当 $m = 0$ 时，我们有

$$
\begin{pmatrix}
   f_{k-1}s_{k-1} & f_{k}
\end{pmatrix}
=
\begin{pmatrix}
   f_0s_0 & f_1
\end{pmatrix} 
\times \prod_{i=1}^k A_i 
$$

当 $m \not= 0$ 时，我们先把 $m$ 个特殊值按下标排序，得到 $s_{indx_1},s_{indx_2},\dots,s_{indx_m}$，其中 $indx$ 数组代表特殊值的下标。

考虑到 $m$ 个特殊值把 $1$ 到 $k$ 分成了 $m+1$ 段，那我们就一段一段的乘起来。每一段的长度都可以表示为一个 $pn+q$ 的形式，而这一段内的矩阵都是重复的。因此，我们可以维护任意长度小于等于 $n$ 的区间矩阵之积，快速幂即可。对于特殊值，单独乘起来即可。

维护长度小于等于 $n$ 的区间矩阵之积可以用线段树。

## 一些细节

+ 线段树可以维护 $0$ 到 $2n-1$ 的矩阵积，这样不用特判 $l \bmod n$ 与 $r \bmod n$ 之间的大小关系。注意要开八倍空间。

+ 特判 $k = 0$ 的情况，因为我们的初始矩阵就是 $\begin{pmatrix} f_0s_0 & f_1 \end{pmatrix}$。

不懂可以配合代码食用：

```cpp
#include <bits/stdc++.h>
#define int long long
#define FOR(i, a, b) for(int i = a; i <= b; i++)
#define ROF(i, a, b) for(int i = a; i >= b; i--)
using namespace std;
const int N = 5e4+5;
int s[N], k, p, n, m;
//矩阵板子 
struct mat {
	int a[3][3];
	mat(int x = 0){
		memset(a, 0, sizeof(a));
		if (x) a[1][1] = a[2][2] = 1;
	}
	void print() {
		FOR(i, 1, 2) {
			FOR(j, 1, 2) cout << a[i][j] << ' ';
			cout << endl;
		}
		return;
	}
} ans;
mat operator*(mat a, mat b) {
	mat c;
	FOR(i, 1, 2) FOR(j, 1, 2) FOR(k, 1, 2) c.a[i][j] = (c.a[i][j] + a.a[i][k] * b.a[k][j] % p) % p;
	return c;
}
mat qpow(mat a, int p) {
	mat res(1);
	while (p) {
		if (p & 1) res = res * a;
		a = a * a;
		p >>= 1;
	}
	return res;
}
mat Mat(int a, int b, int c, int d) {  //给矩阵赋值 
	mat A;
	A.a[1][1] = a, A.a[1][2] = b, A.a[2][1] = c, A.a[2][2] = d;
	return A;
}

//线段树板子 
struct node { mat a; int l, r; } t[N << 3];  //八倍空间 
void pushup(int p) {
	t[p].a = t[p << 1].a * t[p << 1 | 1].a;
	return;
}
void build(int L, int R, int p) {
	t[p].l = L, t[p].r = R;
	if (L == R) {
		t[p].a = Mat(0, 1, s[L % n], s[L % n]);
		return;
	}
	int mid = (L + R) >> 1;
	build(L, mid, p << 1), build(mid+1, R, p << 1 | 1);
	pushup(p);
	return;
}
mat query(int L, int R, int p) {
	if (L <= t[p].l && t[p].r <= R) return t[p].a;
	int mid = (t[p].l + t[p].r) >> 1;
	mat res(1);
	if (L <= mid) res = res * query(L, R, p << 1);
	if (mid+1 <= R) res = res * query(L, R, p << 1 | 1);
	return res;
}

struct change { int indx, v; } a[N];   //记录特殊值的信息 
mat get(int l, int r) {                //获取[l,r]之间的矩阵积，[l,r]是长度小于等于n的区间 
	mat tmp(1);
	if (l > r) return tmp;             //l>r就返回单位矩阵 
	l %= n, r %= n;
	if (l > r) r += n;
	return query(l, r, 1);             //维护[0,2n-1]区间矩阵积的目的就在这里 
}
mat work(int l, int r) {               //获取任意[l,r]之间的矩阵积 
	mat tmp(1);
	if (l > r) return tmp;             //l>r就返回单位矩阵 
	//pn+q中，p=(r-l+1)/n，然后剩下的区间一定长度小于n，左端点调整完后直接get即可 
	tmp = tmp * qpow(get(l, l+(r-l+1)/n*n-1), (r-l+1) / n);
	tmp = tmp * get(l+(r-l+1)/n*n, r);
	return tmp;
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> k >> p >> n;
	FOR(i, 0, n-1) cin >> s[i];
	build(0, n+n-1, 1);          //[0,2n-1]区间矩阵积 
	cin >> m;
	FOR(i, 1, m) cin >> a[i].indx >> a[i].v;
	if (k == 0) {
		cout << 0;
		return 0;
	}
	sort(a+1, a+m+1, [](change A, change B){ return A.indx < B.indx; }); //按下标排序 
	int i = 1;
	ans = Mat(0, 1, 0, 0);
	for(; i <= m && a[i].indx < k; i++) {
		int S = a[i-1].indx, T = a[i].indx;
		ans = ans * work(S+1, T-1) * Mat(0, 1, a[i].v % p, a[i].v % p);
	}
	if (a[i-1].indx < k) {
		int S = a[i-1].indx, T = k-1;
		ans = ans * work(S+1, T);
	}
	cout << ans.a[1][2] % p;
	return 0;
}
```

---

## 作者：Creeper_l (赞：3)

原题链接：[CF575A](https://www.luogu.com.cn/problem/CF575A)

## 前言

今天模拟赛考到了这道题，最近正好在学习矩阵，于是就来写了这道题，发现这道题是矩阵快速幂好题。

## 题意

题意不多赘述，大概就是一个广义斐波那契数列的升级版，可以修改 $m$ 个系数。

## 思路

因为题目是求斐波那契数列的第 $k$ 项，显然用矩阵去维护。又因为题目说了，如果不算修改的 $m$ 个的话，那么每 $n$ 个就是一个循环节，于是我们可以考虑分段去计算。

首先把所有的分成 $k / n$ 段，每段长度都为 $n$。依次遍历每一个区间，如果当前段内没有修改操作的话，就直接用矩阵快速幂进行计算。如果有修改的话，那么就直接修改之后再计算。时间复杂度     $O(k/n\times \log n)$。但是题目数据范围是 $k \le 10^{18}$，这样肯定会超时，于是考虑优化。

因为修改次数最多 $m$ 次，每一次修改最多影响两个区间，所以最多只能改变 $2m$ 个区间。我们可以先把普通的区间答案算出来，这 $2m$ 个区间单独算，最后加起来，时间复杂度 $O(nm)$，还是会超时。

还需要优化。这时我们发现其实这道题就是让我们对矩阵进行修改，求乘积。可以想到用**线段树优化矩阵快速幂**，支持单点修改，全局查询。时间复杂度 $O(m\log n)$，可以通过。

代码过于冗长杂乱，在这里就不贴了。

[评测记录](https://www.luogu.com.cn/record/120366263)

---

## 作者：tzc_wk (赞：3)

[题面传送门](https://codeforces.ml/contest/575/problem/A)

题意：

给出 $s_0,s_1,s_2,\dots,s_{n-1}$，对于 $i\geq n$，有 $m$ 个 $s_i$ 满足 $s_i\neq s_{i\bmod n}$，这 $m$ 个 $s_i$ 特殊给定，其它的 $s_i=s_{i\bmod n}$。

另有序列 $f_i$ 满足 $f_0=0,f_1=1$，$f_i=f_{i-1}s_{i-1}+f_{i-2}s_{i-2}$。

求 $f_x\bmod P$。

 $1\leq n,m\leq 5\times 10^4,0\leq x\leq 10^{18}$

粉兔：矩阵快速幂 sb 题。

我：矩阵快速幂神仙题。

这好像是上赛季的一个 jxd 作业。

首先写出矩阵递推式：

$[f_{i-2},f_{i-1}]\times\begin{bmatrix}0&s_{i-2}\\1&s_{i-1}\end{bmatrix}=[f_{i-1},f_i]$

于是 $[f_{x-1},f_x]=[0,1]\times\prod\limits_{i=1}^{x-1}\begin{bmatrix}0&s_{i-1}\\1&s_{i}\end{bmatrix}$

首先考虑 $m=0$ 的情况。后面 $\prod$ 的矩阵成周期性分部。所以可以求出每个周期内所有矩阵的乘积，跑个矩阵快速幂，最后的零头暴力算一下就可以了。

接下来考虑 $m\neq 0$ 的情况。记 $P=\prod\limits_{i=0}^{n-1}\begin{bmatrix}0&s_i\\1&s_{(i+1)\bmod n}\end{bmatrix}$，不难发现，对于大多数周期，其中所有矩阵的乘积都为 $P$，最多只有 $2m$ 个周期的乘积 $\neq P$。

故可以对这些特殊的周期特殊计算，其它周期跑矩阵快速幂。

考虑一个特殊点 $x_i$ 会造成什么影响，会使 $x_i$ 和 $x_i-1$ 的转移矩阵发生变化。

所以我们对于所有 $x_i$ 和 $x_i-1$ 所在的周期单独计算它的贡献。

我们建立 $n$ 个矩阵 $A_0,A_1,A_2,\dots,A_{n-1}$，初始 $A_i=\begin{bmatrix}0&s_i\\1&s_{(i+1)\bmod n}\end{bmatrix}$

对于某个周期中特殊处理的点 $p$，我们修改 $p\bmod n$ 转移矩阵的值，然后求一遍所有 $A_i$ 的乘积。处理完这个周期后再改回去。

于是此题变为：修改某个矩阵的值，求所有矩阵的乘积。

注意到矩阵是不支持除法操作的，所以这玩意儿只能用线段树维护。

时间复杂度 $2^3n\log n$。

细节恶心得要死。。。。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fz(i,a,b) for(int i=a;i<=b;i++)
#define fd(i,a,b) for(int i=a;i>=b;i--)
#define ffe(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
template<typename T1,typename T2> void chkmin(T1 &x,T2 y){if(x>y) x=y;}
template<typename T1,typename T2> void chkmax(T1 &x,T2 y){if(x<y) x=y;}
typedef pair<int,int> pii;
typedef long long ll;
template<typename T> void read(T &x){
	char c=getchar();T neg=1;
	while(!isdigit(c)){if(c=='-') neg=-1;c=getchar();}
	while(isdigit(c)) x=x*10+c-'0',c=getchar();
	x*=neg;
}
const int MAXN=5e4;
const int SIZE=2;
ll x;int mod,n,m,k,b[MAXN+5];
pair<ll,int> p[MAXN+5];
ll tk[MAXN*2+5];
struct mat{
	int a[SIZE][SIZE];
	mat(){memset(a,0,sizeof(a));}
	friend mat operator *(mat x,mat y){
		mat ret;
		for(int i=0;i<2;i++) for(int j=0;j<2;j++) for(int k=0;k<2;k++)
			ret.a[i][j]=(ret.a[i][j]+1ll*x.a[i][k]*y.a[k][j]%mod)%mod;
		return ret;
	}
};
struct node{int l,r;mat val;} s[MAXN*4+5];
void build(int k,int l,int r){
	s[k].l=l;s[k].r=r;if(l==r) return;
	int mid=(l+r)>>1;build(k<<1,l,mid);build(k<<1|1,mid+1,r);
}
void modify(int k,int p,mat x){
	if(s[k].l==s[k].r){s[k].val=x;return;}
	int mid=(s[k].l+s[k].r)>>1;
	if(p<=mid) modify(k<<1,p,x);else modify(k<<1|1,p,x);
	s[k].val=s[k<<1].val*s[k<<1|1].val;
}
mat query(int k,int l,int r){
	if(l<=s[k].l&&s[k].r<=r) return s[k].val;
	int mid=(s[k].l+s[k].r)>>1;
	if(r<=mid) return query(k<<1,l,r);
	else if(l>mid) return query(k<<1|1,l,r);
	else return query(k<<1,l,mid)*query(k<<1|1,mid+1,r);
}
mat qpow(mat x,ll e){
	mat ret;ret.a[0][0]=ret.a[1][1]=1;
	while(e){if(e&1) ret=ret*x;x=x*x;e>>=1;}
	return ret;
}
map<ll,int> mmp;
signed main(){
//	freopen("in.txt","r",stdin);
	scanf("%lld%d%d",&x,&mod,&n);x--;
	if(x==-1) return printf("0\n"),0;
	for(int i=0;i<n;i++) scanf("%d",&b[i]);scanf("%d",&m);
	for(int i=1;i<=m;i++) scanf("%lld%d",&p[i].fi,&p[i].se);
	for(int i=1;i<=m;i++) mmp[p[i].fi]=p[i].se;
	for(int i=1;i<=m;i++){
		tk[++k]=p[i].fi;
		if(p[i].fi!=n) tk[++k]=p[i].fi-1;
	}
	sort(tk+1,tk+k+1);k=unique(tk+1,tk+k+1)-tk-1;build(1,0,n-1);
	for(int i=0;i<n;i++){
		mat t;t.a[0][0]=0;t.a[1][0]=1;t.a[0][1]=b[i];
		if(!mmp[i+1]) t.a[1][1]=b[(i+1)%n];else t.a[1][1]=mmp[i+1];
		modify(1,i,t);
	}
	mat ret;
	if(x<n) ret=query(1,0,x);
	else{
		ret=query(1,0,n-1);
		if(mmp[n]){
			mat t;t.a[0][0]=0;t.a[1][0]=1;t.a[0][1]=b[n-1];t.a[1][1]=b[0];
			modify(1,n-1,t);
		}
		int cur=1,pre=0;ll pn=0;bool flg=0;
		while(cur<=k){
//			puts("-1");
//			printf("%d %d %d\n",cur,pn,pre);
			if(x/n<tk[pre+1]/n){
				ret=ret*qpow(query(1,0,n-1),(x/n)-pn-1);
				ret=ret*query(1,0,x%n);flg=1;break;
			}
			ret=ret*qpow(query(1,0,n-1),(tk[pre+1]/n)-pn-1);
			while(cur<=k&&tk[cur]/n==tk[pre+1]/n){
				ll id=tk[cur];int v1,v2;
				if(!mmp[id]) v1=b[id%n];else v1=mmp[id];
				if(!mmp[id+1]) v2=b[(id+1)%n];else v2=mmp[id+1];
//				printf("%lld %d %d %d\n",id,id%n,v1,v2);
				mat t;t.a[0][0]=0;t.a[1][0]=1;t.a[0][1]=v1;t.a[1][1]=v2;
				modify(1,id%n,t);cur++;
			}
			if((x/n)==(tk[pre+1]/n)){
				ret=ret*query(1,0,x%n);flg=1;break;
			} else ret=ret*query(1,0,n-1);
			for(int i=pre+1;i<cur;i++){
				mat t;t.a[0][0]=0;t.a[1][0]=1;
				t.a[0][1]=b[tk[i]%n];t.a[1][1]=b[(tk[i]+1)%n];
				modify(1,tk[i]%n,t);
			}
			pn=tk[pre+1]/n;pre=cur-1;
		}
		if(!flg){
//			puts("-1");
			ret=ret*qpow(query(1,0,n-1),(x/n)-pn-1);
			ret=ret*query(1,0,x%n);
		}
	}
	mat f;f.a[0][1]=1;f=f*ret;
	printf("%d\n",f.a[0][0]);
	return 0;
}
/*
3 998244353
3
1 2 1
3
3 3
4 6
10 8

20 998244353
3
100 370 250
5
7 230
23 500
5 480
15 530
19 570

100 998244353
3
1 2 1
2
3 2
5 1

1000000 998244353
3
100 370 250
5
7 230
23 500
5 480
15 530
19 570
*/
```



---

## 作者：a___ (赞：3)

发现如果 $n=1,m=0$ 就是 [P1349 广义斐波那契数列](https://www.luogu.com.cn/problem/P1349)。  

如果放开 $n=1$ 的限制其实就是每 $n$ 个矩阵作一个循环节，将这 $n$ 个矩阵的乘积乘 $\lfloor\frac k n\rfloor$ 次，最后的边角料暴算就好。   

而 $m$ 的限制其实就相当于每次快速幂到 $m$ 前一个循环后将 $m\%n$ 附近的几个矩阵修改掉再快速幂。  

由于矩阵具有结合律，所以我们可以使用线段树维护修改。  

然后你一开始写就会发现一堆细节。。。   

首先读入的 $k$ 和 $j$ 要开 `long long`，以及作乘法时也要开 `long long`。   

然后你发现读入的是 $s_{0..n}$ 而你的线段树下标是 $1..n$ 。  
而我们的转移矩阵应该是 $f=\begin{bmatrix}0&1\end{bmatrix},mul=\begin{bmatrix}0&x\\1&y\end{bmatrix}(f_i=xf_{i-2}+yf_{i-1})$，考虑我们使 $s_n=s_0$，对于每个线段树上的下标 $i$ 使 $x=s_{i-1},y=s_{i}$ 。那么我们的线段树根节点矩阵即为 **从这个循环开头到下个循环开头** 的转移矩阵。  

然后我们又发现，修改一个 $pos$ ，会对线段树上 $pos\%n,pos\%n+1$ **两个位置** 造成影响，而且**改完本循环所有修改还要再改回来** 。。。

另外还要一个特例，即若 $pos\%n=0$，则影响的是 **本循环的 $s_n$ 和下循环的 $s_0$** 。。。  

这好像极其难处理，需要一大堆特判。于是我们 **考虑将修改一拆四以避免特判**。  

定义一个询问结构体 `{x,y,a,id}` 表示将第 $x$ 个循环 $s_y$ 修改为 $a$ ，本次是第 $id$ 个修改。  
一个原修改可以被拆为一下四个新修改：  
1. 修改本次询问的 $j\%n$。   
2. 修改本次询问的 $j\%n+1$。   
3. 下次询问改回值 $j\%n$。   
4. 下次询问改回值 $j\%n+1$。     

对于 $pos\%n==0$ 的情况进行特判。发现在线段树上找下标为 $0$ 的点实际会更新下标为 $1$ 的点的值，刚好不用特判。      
每次新修改仅需要将 $s_y$ 改为 $n$，并在线段树上更新 $s_y$ 的答案就好。    

以下是部分核心代码：   

询问结构体：
```cpp

struct quest
{
	long long x;int y,a,id;
	bool operator< (const quest &c)const{return x!=c.x?x<c.x:(y!=c.y?y<c.y:id<c.id);}//按顺序修改
}d[N<<2];
```
拆询问：
```cpp
for(i=1;i<=m;i++)
if(a[i].first%n)
	d[++cnt]=(quest){a[i].first/n,a[i].first%n,a[i].second,i},
	d[++cnt]=(quest){a[i].first/n,a[i].first%n+1,s[a[i].first%n+1],i},
	d[++cnt]=(quest){a[i].first/n+1,a[i].first%n,s[a[i].first%n],i},
	d[++cnt]=(quest){a[i].first/n+1,a[i].first%n+1,s[a[i].first%n+1],i};
else
	d[++cnt]=(quest){a[i].first/n-1,n,a[i].second,i},
	d[++cnt]=(quest){a[i].first/n,0,a[i].second,i},
	d[++cnt]=(quest){a[i].first/n,n,s[n],i},
	d[++cnt]=(quest){a[i].first/n+1,0,s[0],i};
```
修改计算答案：
```cpp
mat f;f[0][1]=1;long long las=0;
for(i=1;i<=cnt&&d[i].x<kk/n;i++)
{
	f=f*(t[1]^(d[i].x-las));
	las=d[i].x;
	s[d[i].y]=d[i].a;
	update(1,1,n,d[i].y);
}
f=f*(t[1]^(kk/n-las));
for(i=1;i<=kk%n;i++)f=f*mat(s[i-1],s[i]);
printf("%d\n",f[0][0]);
```
线段树 `update`：
```cpp
void update(int rt,int l,int r,int p)
{
	if(l==r){t[rt]=mat(s[l-1],s[l]);return;}
	int mid=(l+r)>>1;
	if(p<=mid)update(rt<<1,l,mid,p);
	else update(rt<<1|1,mid+1,r,p);
	t[rt]=t[rt<<1]*t[rt<<1|1];
}
```

---

## 作者：Kinandra (赞：3)

标签: 矩阵快速幂, 线段树.

#### Part 1

首先发现如果没有 $m$ 个特殊位置我们可以直接矩阵快速幂.

由于转移的矩阵具有周期性, 我们可以特殊处理 $m$ 个特殊位置影响到的 $\mathcal O(m)$ 个周期, 未被影响的周期矩阵快速幂即可.

这样很容易得到一个 $\mathcal O(m(n+\log k))$ 的暴力做法了.

#### Part 2

显然 $\mathcal O(nm)$ 不够优秀, 需要用线段树来维护转移矩阵.

注意这里的每个特殊的 $s$ 都会影响到两个矩阵, 并且由于两个矩阵可能跨越两个不同周期, 故我们存储是最好分成两个来存.

时间复杂度 $\mathcal O(m(\log n+\log k))$.

```cpp
#include <bits/stdc++.h>
#define root 1, n, 1
#define ls l, mid, k << 1
#define rs mid + 1, r, k << 1 | 1
using namespace std;
long long read();
long long K;
int P, n, m;
int s[50004];
struct T {
    long long p;
    int s, type;
} t[100005];

bool cmp(T x, T y) { return x.p < y.p; }

struct Mat {
    int a[2][2];
    int *operator[](int p) { return a[p]; }
    Mat operator*(Mat b) {  // lmul
        Mat rt;
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 2; ++j)
                rt[i][j] = (1ll * b[i][0] * a[0][j] % P +
                            1ll * b[i][1] * a[1][j] % P) %
                           P;
        return rt;
    }
    void prt() {
        for (int i = 0; i < 2; ++i, cout << endl)
            for (int j = 0; j < 2; ++j) cout << a[i][j] << ' ';
    }
} a[50004], ta[50004], res;

struct Seg {
    Mat t[200005];

    void update(int k) { t[k] = t[k << 1] * t[k << 1 | 1]; }

    void build(int l, int r, int k) {
        if (l == r) return t[k] = a[l], void();
        int mid = l + r >> 1;
        build(ls), build(rs), update(k);
    }

    void set(int l, int r, int k, int pos) {
        if (l == r) return t[k] = ta[l], void();
        int mid = l + r >> 1;
        pos <= mid ? set(ls, pos) : set(rs, pos), update(k);
    }
} seg;

void fsp(Mat bs, long long p) {
    while (p) {
        if (p & 1) res = res * bs;
        bs = bs * bs, p >>= 1;
    }
}

int main() {
    K = read(), P = read(), n = read();
    for (int i = 0; i < n; ++i) s[i] = read() % P;
    for (int i = 1; i <= n; ++i)
        a[i][0][1] = 1, a[i][1][0] = s[i - 1], a[i][1][1] = s[i % n],
        ta[i] = a[i];
    m = read();
    for (int i = 1; i <= m; ++i)
        t[i + m].p = (t[i].p = read()) + 1, t[i].s = t[i + m].s = read() % P,
              t[i].type = 1;

    m <<= 1, seg.build(root), sort(t + 1, t + 1 + m, cmp);
    while (m && t[m].p > K) --m;
    res[1][1] = 1;
    long long np = 0, tp;
    for (int i = 1, j = 1; i <= m; i = j + 1) {
        tp = (t[j = i].p - 1) / n;
        while (j < m && tp == (t[j + 1].p - 1) / n) ++j;
        fsp(seg.t[1], tp - np), np = tp;
        for (int k = i, pos; k <= j; ++k)
            ta[pos = (t[k].p - 1) % n + 1][1][t[k].type] = t[k].s,
                                        seg.set(root, pos);

        if (tp == K / n) break;
        res = res * seg.t[1], ++np;
        for (int k = i; k <= j; ++k) {
            int pos = (t[k].p - 1) % n + 1;
            ta[pos] = a[pos], seg.set(root, pos);
        }
    }
    tp = K / n, fsp(seg.t[1], tp - np);

    for (int i = 1; i <= K % n; ++i) res = res * ta[i];
    printf("%d\n", res[0][1]);
    return 0;
}
const int _SIZE = 1 << 22;
char ibuf[_SIZE], *iS = ibuf, *iT = ibuf;
#define gc                                                         \
    (iS == iT ? iT = ((iS = ibuf) + fread(ibuf, 1, _SIZE, stdin)), \
     (iS == iT ? EOF : *iS++) : *iS++)
long long read() {
    long long x = 0;
    char c = gc;
    while (!isdigit(c)) c = gc;
    while (isdigit(c)) x = x * 10 + c - '0', c = gc;
    return x;
}
```

---

## 作者：chihik (赞：3)

考试的时候写了3.5h , 考后又写了2h 才过掉。

每次修改只会影响两个矩阵，可以暴力计算。

我们知道矩阵乘法有结合律，那么两次修改之间的矩阵可以快速求出乘积。

因为有散段所以考虑用线段树维护区间矩阵的乘法，整段直接矩阵快速幂

但要注意修改操作相邻时影响的矩阵会重复，可以存进 vector 里暴力修改后一起乘。

代码大部分是考场写的，太丑就不放了。~~虽然口胡很简单但是写起来是真的恶心。~~

---

## 作者：Daidly (赞：2)

有递推式：

$$
\begin{aligned}

\begin{bmatrix} f_{i}&f_{i-1} \end{bmatrix}

=

\begin{bmatrix} f_{i-1}&f_{i-2} \end{bmatrix}
\times

\begin{bmatrix} s_{i-1}&1\\s_{i-2}&0 \end{bmatrix}

\end{aligned}
$$

由上我们只需要算出：

$$

\prod_{i=1}^{k-1}\begin{bmatrix} s_{i}&1\\s_{i-1} &0 \end{bmatrix}

$$

使用线段树维护矩阵乘积，可以很轻松地解决无特殊值的情况。

称 $\begin{bmatrix} s_{i}&1\\s_{i-1}&0 \end{bmatrix}$ 为矩阵 $T_i$，发现 $s_j=v$ 只会影响到 $T_j$ 和 $T_{j+1}$，总影响个数在 $O(m)$ 级别。

这题细节比较多，考虑按下标从小到大枚举每一个特殊值，若多个特殊值位置相邻（比如两个特殊值只会影响三个矩阵）把它们一起处理，暴力计算这一块，而块间可以用线段树和矩阵快速幂维护。具体的，可以写一个函数 `calc(l,r)` 表示计算下标在 $[l,r]$ 内的矩阵乘积。

还需要时刻注意枚举值和 $k-1$ 的关系，若超过及时 `break`。

代码如下（调了一下午）：

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long

inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c<='9'&&c>='0'){
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}

void print(int x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10);
	putchar(x%10^48);
}

const int N=5e4+5;
int n,m,k,mod,s[N];
struct modify_node{
    int j,v;
    bool operator<(const modify_node &P)const{return j<P.j;}
}p[N];

struct Matrix{
    int f[2][2];
    Matrix(int a=1,int b=0,int c=0,int d=1){f[0][0]=a,f[0][1]=b,f[1][0]=c,f[1][1]=d;}
    Matrix operator*(Matrix b){
        return (Matrix){
            (f[0][0]*b.f[0][0]+f[0][1]*b.f[1][0])%mod,
            (f[0][0]*b.f[0][1]+f[0][1]*b.f[1][1])%mod,
            (f[1][0]*b.f[0][0]+f[1][1]*b.f[1][0])%mod,
            (f[1][0]*b.f[0][1]+f[1][1]*b.f[1][1])%mod
        };
    }
};

Matrix qpow(Matrix a,int b){
    Matrix ans;
    while(b){
        if(b&1)ans=ans*a;
        a=a*a,b>>=1;
    }return ans;
}

struct SGT{
    Matrix t[N<<2];
    void build(int l,int r,int p){
        if(l==r){t[p]=(Matrix){s[l%n],1,s[l-1],0};return;}
        int mid=(l+r)>>1;
        build(l,mid,p<<1),build(mid+1,r,p<<1|1);
        t[p]=t[p<<1]*t[p<<1|1];
    }

    void modify0(int l,int r,int pos,int x,int p){
        if(l==r){t[p]=(Matrix){x,1,s[l-1],0};return;}
        int mid=(l+r)>>1;
        if(pos<=mid)modify0(l,mid,pos,x,p<<1);
        else modify0(mid+1,r,pos,x,p<<1|1);
        t[p]=t[p<<1]*t[p<<1|1];
    }

    void modify1(int l,int r,int pos,int x,int p){
        if(l==r){t[p]=(Matrix){s[l%n],1,x,0};return;}
        int mid=(l+r)>>1;
        if(pos<=mid)modify1(l,mid,pos,x,p<<1);
        else modify1(mid+1,r,pos,x,p<<1|1);
        t[p]=t[p<<1]*t[p<<1|1];
    }

    Matrix qry(int l,int r,int lq,int rq,int p){
        if(lq<=l&&r<=rq)return t[p];
        int mid=(l+r)>>1;Matrix ans;
        if(lq>rq)return ans;
        if(lq<=mid)ans=ans*qry(l,mid,lq,rq,p<<1);
        if(mid<rq)ans=ans*qry(mid+1,r,lq,rq,p<<1|1);
        return ans;
    }
}T;

Matrix calc(int l,int r){
    Matrix ans,tmp;
    if(l>r)return ans;
    if((l+n-1)/n==(r+n-1)/n){
        l=l%n;if(!l)l=n;r=r%n;if(!r)r=n;
        return T.qry(1,n,l,r,1);
    }
    if(l%n!=1)ans=ans*T.qry(1,n,(l%n==0?n:l%n),n,1),l+=(n-(l%n==0?n:l%n)+1);
    if(r%n!=0)tmp=tmp*T.qry(1,n,1,r%n,1),r-=(r%n);
    ans=ans*qpow(T.t[1],(r+n-1)/n-(l+n-1)/n+1)*tmp;
    return ans;
}

signed main(){
    k=read(),mod=read(),n=read();
    for(int i=0;i<n;++i)s[i]=read();
    T.build(1,n,1),m=read();
    for(int i=1;i<=m;++i)p[i].j=read(),p[i].v=read();
    sort(p+1,p+m+1);
    if(k==0){puts("0");return 0;}
    if(k==1){print(1%mod);return 0;}
    Matrix ans;
    int lst=0;
    for(int i=1;i<=m;++i){
        int L=i,R=i;
        ans=ans*calc(lst+1,min(p[i].j-1,k-1));
        lst=max(p[R].j-1,min(p[i].j-1,k-1));
        if(p[R].j>k-1)break;
        while(p[R+1].j==p[R].j+1&&p[R+1].j<=k-1)R++;
        if(L==R){
            int tmp=(p[L].j%n==0?n:p[L].j%n);
            ans=ans*(Matrix){p[L].v,1,s[tmp-1],0};
        }else for(int t=L;t<=R;++t){
            if(t==L)ans=ans*(Matrix){p[L].v,1,s[(p[L].j-1)%n],0};
            else if(t==R)ans=ans*(Matrix){p[R].v,1,p[R-1].v,0};
            else ans=ans*(Matrix){p[t].v,1,p[t-1].v,0};
        }
        lst=p[R].j+1;
        if(p[R].j<k-1)ans=ans*(Matrix){s[(p[R].j+1)%n],1,p[R].v,0};
        else break;
        i=R;
    }
    if(lst<k-1)ans=ans*calc(lst+1,k-1);
    print(ans.f[0][0]);
    return 0;
}
```

---

## 作者：xht (赞：2)

> [CF575A Fibonotci](https://codeforc.es/contest/575/problem/A)

## 题意

- $s_{0\dots +\infty}$ 是一个正整数序列。
- 给定 $s_{0 \dots n - 1}$，对于 $i \ge n$，有 $m$ 个 $i$ 给定 $s_i$，剩下的 $i$ 满足 $s_i = s_{i \bmod n}$。
- $f_{0 \dots +\infty}$ 同样是一个正整数序列。
- 给定 $f_0,f_1$，对于 $i \ge 2$，$f_i = s_{i-1}f_{i-1} + s_{i-2}f_{i-2}$。
- 求 $f_k \bmod p$。
- $n,m \le 5 \times 10^4$，$k \le 10^{18}$，$s_i,p \le 10^9$。

## 题解

首先考虑 $m = 0$ 的情况。

由于 $f_i = s_{i-1}f_{i-1} + s_{i-2}f_{i-2}$，有 $\begin{bmatrix} f_{i-2} & f_{i-1} \end{bmatrix} \times \begin{bmatrix} 0 & s_{i-2} \\\\ 1 & s_{i-1} \end{bmatrix} = \begin{bmatrix} f_{i-1} & f_i \end{bmatrix}$。

因此 $\begin{bmatrix} f_{0} & f_{1} \end{bmatrix} \times \prod_{i=1}^{n} \begin{bmatrix} 0 & s_{i-1} \\\\ 1 & s_{i \bmod n} \end{bmatrix} = \begin{bmatrix} f_{n} & f_{n+1} \end{bmatrix}$。

于是可以矩阵快速幂，最后一段可以暴力转移。

考虑 $m \ne 0$ 时，**线段树**维护矩阵乘积。

每次只会修改两个矩阵，因此一共只有 $\mathcal O(m)$ 个单点修改。

因此可以在没有特殊值的周期内用矩阵快速幂转移，有特殊值的周期内单点修改之后再转移再修改回去。

总时间复杂度 $\mathcal O(n + m (\log k + \log n))$。

## 代码

```cpp
const int N = 5e4 + 7;
ll k, o;
int n, m, x;
modint s[N];

struct mt {
	int n, m; modint a[2][2];
	inline mt() {}
	inline mt(int n, int m) : n(n), m(m) { memset(a, 0, sizeof(a)); }
	inline friend mt operator * (mt x, mt y) {
		mt z(x.n, y.m);
		for (int i = 0; i < z.n; i++)
			for (int k = 0; k < x.m; k++)
				for (int j = 0; j < z.m; j++)
					z.a[i][j] += x.a[i][k] * y.a[k][j];
		return z;
	}
} a[N], b[N], f;

inline void ksm(mt x, ll y, mt &z) {
	while (y) {
		if (y & 1) z = z * x;
		x = x * x, y >>= 1;
	}
}

struct Q {
	ll x, k; modint y;
	inline bool operator < (Q o) { return x < o.x; }
} q[N<<1];

struct T {
	int l, r; mt x;
} t[N<<2];

inline void build(int p, int l, int r) {
	t[p].l = l, t[p].r = r;
	if (l == r) return t[p].x = a[l], void();
	build(ls, l, md), build(rs, md + 1, r);
	t[p].x = t[ls].x * t[rs].x;
}

inline void chg(int p, int x, mt y) {
	if (t[p].l == t[p].r) return t[p].x = y, void();
	chg(x <= md ? ls : rs, x, y), t[p].x = t[ls].x * t[rs].x;
}

int main() {
	rd(k), rd(P), rd(n);
	for (int i = 0; i < n; i++) rd(x), s[i] = x % P;
	for (int i = 1; i <= n; i++) a[i] = mt(2, 2), a[i].a[0][1] = s[i-1], a[i].a[1][1] = s[i%n], a[i].a[1][0] = 1, b[i] = a[i];
	build(1, 1, n), rd(m);
	for (int i = 1; i <= m; i++) rd(q[i].x), q[m+i].x = q[i].x + 1, q[i].k = 1, rd(x), q[m+i].y = q[i].y = x % P;
	sort(q + 1, q + (m <<= 1) + 1);
	while (m && q[m].x > k) --m;
	f = mt(1, 2), f.a[0][1] = 1;
	for (int i = 1, j = 1; i <= m; i = ++j) {
		ll w = (q[i].x - 1) / n;
		while (j < m && w == (q[j+1].x - 1) / n) ++j;
		ksm(t[1].x, w - o, f), o = w;
		for (int k = i; k <= j; k++) {
			int d = (q[k].x - 1) % n + 1;
			b[d].a[q[k].k][1] = q[k].y, chg(1, d, b[d]);
		}
		if (w == k / n) break;
		f = f * t[1].x, o = w + 1;
		for (int k = i; k <= j; k++) {
			int d = (q[k].x - 1) % n + 1;
			chg(1, d, b[d] = a[d]);
		}
	}
	ll w = k / n;
	ksm(t[1].x, w - o, f);
	for (int i = 1, d = k % n; i <= d; i++) f = f * b[i];
	print(f.a[0][0]);
	return 0;
}
```

---

## 作者：wsyhb (赞：1)

## 题解

看到线性递推，果断上**矩阵**：

$$
\begin{bmatrix}
F_{n-2} & F_{n-1}
\end{bmatrix}
*
\begin{bmatrix}
0 & s_{n-2}\\
1 & s_{n-1}
\end{bmatrix}

=
\begin{bmatrix}
F_{n-1} & F_{n}
\end{bmatrix}
$$

进一步有：

$$
\begin{bmatrix}
F_{0} & F_{1}
\end{bmatrix}
*
\prod_{i=0}^{k-2}
\begin{bmatrix}
0 & s_{i}\\
1 & s_{i+1}
\end{bmatrix}

=
\begin{bmatrix}
F_{k-1} & F_{k}
\end{bmatrix}
$$

由于 $s_i \neq s_{i \bmod n}$ 的部分可单独计算，问题转化为求矩阵的区间乘积：

$$\prod_{i=l}^{r}
\begin{bmatrix}
0 & s_{i}\\
1 & s_{i+1}
\end{bmatrix}$$

从 $0$ 开始将值域分成 $[0,n-1],[n,2n-1]$ 等若干个大小为 $n$ 的块，并按照端点 $l,r$ 所在块的情况进行分类讨论：

1. $l$ 和 $r$ 在同一块。（即 $\lfloor \dfrac{l}{n} \rfloor=\lfloor \dfrac{r}{n} \rfloor$ 时）

	- 此时要求的式子即为：
    
		$$\prod_{i=l \bmod n}^{r \bmod n}
      \begin{bmatrix}
      0 & s_{i}\\
      1 & s_{i+1}
      \end{bmatrix}$$

	- 由于矩阵不一定可以求逆，所以无法使用前缀和的思想。

   - 于是使用**线段树维护区间乘积**。

1. $l$ 和 $r$ 不在同一块。

	- 我们可以将其分成三段：$[l,\lceil \dfrac{l}{n} \rceil \cdot n-1]$，$[\lceil \dfrac{l}{n} \rceil \cdot n,\lfloor \dfrac{r}{n} \rfloor \cdot n-1]$，$[\lfloor \dfrac{r}{n} \rfloor \cdot n,r]$，即前缀、整块和后缀。
   - 对于前后缀，我们可以预先处理好。（当然你要用线段树直接查也可以）
   - 对于整块，我们可以使用**矩阵快速幂**求以
      $\prod_{i=0}^{n-1}
      \begin{bmatrix}
      0 & s_{i}\\
      1 & s_{i+1}
      \end{bmatrix}$
      为底的幂。

总时间复杂度：$O(M\log{N} \cdot 2^3)$。（$2^3$ 是矩阵乘法复杂度，也可以看作常数）

注意一些实现上的细节：

1. $P=1$ 的处理。
1. $K<2$ 的处理。
1. $j \ge K$ 的处理。
1. $s_i \neq s_{i \bmod n}$ 且 $s_{i+1} \neq s_{(i+1) \bmod n}$ 的处理。
1. ……（请参考代码的实现）

## 代码

``` cpp
#include<bits/stdc++.h>
using namespace std;
long long K;
int P,N,M;
const int max_N=5e4+5;
int s[max_N];
struct Matrix
{
	int a,b,c,d;
	inline Matrix(int x=0,int y=0,int z=0,int w=0)
	{
		a=x,b=y,c=z,d=w;
	}
}pref[max_N],suff[max_N],ans(0,1,0,0),A;
inline Matrix operator * (const Matrix &p,const Matrix &q)
{
	return Matrix((1ll*p.a*q.a+1ll*p.b*q.c)%P,
	(1ll*p.a*q.b+1ll*p.b*q.d)%P,
	(1ll*p.c*q.a+1ll*p.d*q.c)%P,
	(1ll*p.c*q.b+1ll*p.d*q.d)%P);
}
namespace SegTree
{
	Matrix val[max_N<<2];
	#define ls(p) ((p)<<1)
	#define rs(p) ((p)<<1|1)
	void build(int p,int l,int r)
	{
		if(l==r)
		{
			val[p]=Matrix(0,s[l],1,s[l+1]);
			return;
		}
		int mid=(l+r)>>1;
		build(ls(p),l,mid);
		build(rs(p),mid+1,r);
		val[p]=val[ls(p)]*val[rs(p)];
	}
	void query(int p,int l,int r,int a,int b)
	{
		if(a<=l&&r<=b)
		{
			ans=ans*val[p];
			return;
		}
		int mid=(l+r)>>1;
		if(a<=mid)
			query(ls(p),l,mid,a,b);
		if(b>mid)
			query(rs(p),mid+1,r,a,b);
	}
}
inline void solve(long long l,long long r) // (s[l],s[l+1])...(s[r-1],s[r])
{
	--r;
	if(l>r)
		return;
	if(l/N==r/N)
	{
		SegTree::query(1,0,N-1,l%N,r%N);
		return;
	}
	ans=ans*suff[l%N];
	long long t=r/N-l/N-1;
	A=pref[N-1];
	while(t)
	{
		if(t&1)
			ans=ans*A;
		A=A*A;
		t>>=1;
	}
	ans=ans*pref[r%N];
}
typedef pair<long long,int> plli;
const int max_M=5e4+5;
plli extra[max_M];
int main()
{
	scanf("%lld%d%d",&K,&P,&N);
	if(P==1)
	{
		puts("0");
		return 0;
	}
	if(K<2)
	{
		printf("%lld\n",K);
		return 0;
	}
	for(int i=0;i<N;++i)
		scanf("%d",s+i);
	s[N]=s[0];
	pref[0]=Matrix(0,s[0],1,s[1]);
	for(int i=1;i<N;++i)
		pref[i]=pref[i-1]*Matrix(0,s[i],1,s[i+1]);
	suff[N-1]=Matrix(0,s[N-1],1,s[0]);
	for(int i=N-2;i>=0;--i)
		suff[i]=Matrix(0,s[i],1,s[i+1])*suff[i+1];
	SegTree::build(1,0,N-1);
	scanf("%d",&M);
	for(int i=1;i<=M;++i)
		scanf("%lld%d",&extra[i].first,&extra[i].second);
	sort(extra+1,extra+M+1);
	while(M>=1&&extra[M].first>=K)
		--M;
	if(!M)
	{
		solve(0,K-1);
		printf("%d\n",ans.b);
		return 0;
	}
	solve(0,extra[1].first-1);
	for(int i=1;i<=M;++i)
	{
		if(i==1||extra[i-1].first!=extra[i].first-1)
			ans=ans*Matrix(0,s[(extra[i].first-1)%N],1,extra[i].second);
		else
			ans=ans*Matrix(0,extra[i-1].second,1,extra[i].second);
		if(extra[i].first+1<=K-1&&(i==M||extra[i+1].first!=extra[i].first+1))
			ans=ans*Matrix(0,extra[i].second,1,s[(extra[i].first+1)%N]);
		if(i<M)
			solve(extra[i].first+1,extra[i+1].first-1);
	}
	solve(extra[M].first+1,K-1);
	printf("%d\n",ans.b);
	return 0;
}
```

---

## 作者：情非昔比 (赞：1)

## 题目大意：
$s$是一个循环数列，现在将$s$中的$m$项进行改变。

$f$是一个数列，满足$f_0=0,f_1=1$,且对于$i>=2,f_i=f_{i-1}*s_{i-1}+f_{i-2}*s_{i-2}$;

求$f_k$在模$p$意义下的值。
## 解题思路：
首先我们可以想到用矩阵优化数列递推。

然后我们就可以去做了：

首先将一个循环节的矩阵放在线段树内。然后每次一个循环节一个循环节去操作。

如果遇到需要修改的，就可以将循环节内不需要修改的从线段树内查询出来，其他暴力搞。

如果不需要修改的，连续的一片就可以用矩阵快速幂。
# Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=50005;
int kkk,M,n,s[N],m;
struct Ask{
	int x,y;
}A[N];
int cmp(Ask x,Ask y){
	return x.x<y.x;
}
struct zz{
	int a[2][2];
}I;
zz cf(zz x,zz y){
	zz z;memset(z.a,0,sizeof z.a);
	for (int i=0;i<2;i++)
		for (int j=0;j<2;j++)
			for (int k=0;k<2;k++)
				(z.a[i][j]+=x.a[i][k]*y.a[k][j])%=M;
	return z;			
}
zz ksm(zz x,int y){
	zz ans;memset(ans.a,0,sizeof ans.a);
	for (int i=0;i<2;i++)ans.a[i][i]=1;
	for (;y;y>>=1,x=cf(x,x))
		if (y&1)ans=cf(ans,x);
	return ans;	
}
struct Tree{
	int l,r;
	zz num;
}T[N*4];
void build(int x,int l,int r){
	T[x].l=l;T[x].r=r;
	if (l==r){
		T[x].num.a[1][0]=1;
		T[x].num.a[0][0]=s[(l+1)%n];
		T[x].num.a[0][1]=s[l%n];
		return;
	}
	int mid=(l+r)/2;
	build(x*2,l,mid);
	build(x*2+1,mid+1,r);
	T[x].num=cf(T[x*2+1].num,T[x*2].num);
}
zz findz(int x,int l,int r){
	if (T[x].l>r||l>T[x].r)return I;
	if (T[x].l>=l&&T[x].r<=r)return T[x].num;
	return cf(findz(x*2+1,l,r),findz(x*2,l,r));
}
signed main(){
	scanf("%lld%lld",&kkk,&M);
	if (kkk==0){
		puts("0");
		return 0;
	}
	if (kkk==1){
		printf("%lld\n",kkk%M);
		return 0;
	}
	scanf("%lld",&n);
	for (int i=0;i<n;i++)scanf("%lld",&s[i]),s[i]%=M;
	scanf("%lld",&m);
	for (int i=1;i<=m;i++)scanf("%lld%lld",&A[i].x,&A[i].y),A[i].x--,A[i].y%=M;
	sort(A+1,A+m+1,cmp);
	I.a[0][0]=I.a[1][1]=1;
	build(1,0,n-1);
	kkk--;zz now=I;int ti=0;
	for (int i=1;i<=m;i++){
		if (A[i].x>kkk)break;
		now=cf(findz(1,ti%n,ti%n==0?-1:min(n-1,ti%n+A[i].x-ti-1)),now);
		ti=ti%n==0?ti:min(A[i].x,(ti/n+1)*n);
		int k=A[i].x/n-ti/n;zz p=findz(1,0,n-1);
		now=cf(ksm(p,k),now);
		ti+=k*n;
		now=cf(findz(1,ti%n,ti%n+A[i].x-ti-1),now);
		ti=A[i].x;
		if (ti>=kkk)break;
		zz z;
		z.a[0][1]=s[A[i].x%n];
		z.a[0][0]=A[i].y;
		z.a[1][0]=1;
		z.a[1][1]=0;
		now=cf(z,now);
		ti++;	
		int j=i+1;
		while (j<=m&&A[j].x==A[i].x+1){
			zz z;
			z.a[0][0]=A[j].y;
			z.a[0][1]=A[i].y;
			z.a[1][0]=1;
			z.a[1][1]=0;
			now=cf(z,now);
			i++;j++;
			ti++;
			if (ti>=kkk)break;
		}
		if (ti>=kkk)break;
		z.a[0][1]=A[i].y;
		z.a[0][0]=s[(A[i].x+2)%n];
		z.a[1][0]=1;
		z.a[1][1]=0;
		now=cf(z,now);
		ti++;
	}
	if (ti<kkk){
		now=cf(findz(1,ti%n,ti%n==0?-1:min(n-1,ti%n+kkk-ti-1)),now);
		ti=ti%n==0?ti:min((ti/n+1)*n,kkk);
		int k=kkk/n-ti/n;
		now=cf(ksm(findz(1,0,n-1),k),now);
		ti+=k*n;
		now=cf(findz(1,ti%n,ti%n+kkk-ti-1),now);
		ti=kkk;
	}
	printf("%lld\n",now.a[0][0]%M);
}
```

---

## 作者：rickyxrc (赞：0)

本文章遵守知识共享协议 CC-BY-NC-SA，同步发表于洛谷题解区，转载时须在文章的任一位置附上原文链接和作者署名（rickyxrc）。推荐在[我的个人博客](https://blog.rickyxrc.cc)阅读。

是一道矩阵加速的题目，但是矩阵加速的方法不止快速幂，还有倍增。

## 题面大意

给你一个数列 $S'$，你需要求出数列 $F$ 的第 $k$ 项。

其中 $F_i = \begin{cases}0 & (i=0) \\ F_{i-1}S_{i-1} + F_{i-2}+S_{i-2} & (i \neq 0) \end{cases}$（类似于斐波那契数列）。

无限的数列 $S$ 可以看作一个有限的数列 $S'$ 的循环，但是 $S$ 中某些位置的值是特殊的，会专门给入。

## 解题思路

这是一个类似于斐波那契数列的转移，那么我们不难想到使用矩阵维护转移状态。

具体的，定义状态矩阵 $T_i = \begin{bmatrix}F_{i+1} & F_i\end{bmatrix}$，转移矩阵 $S_i = \begin{bmatrix}S_{i+1} & 1 \\ S_i & 0\end{bmatrix}$，那么我们可以得到 $T_i S_i = T_{i+1}$，这是下文讨论内容的前提。

然后我们就考虑如何加速，不难发现特殊点的数量和值域相比极少，也就是说大多数情况下，我们的计算采取的转移策略是相同的，是许多转移矩阵的乘积。

形式化地说，我们是在求 $T_0\prod_{i=0}^kS_i$，而中间的 $S_i$ 连乘中，有许多部分是相同的，我们可以将其打包，加速运算。

这里解法出现了分歧，可以使用线段树加矩阵快速幂（类似于分块的思想），当然也可以使用倍增。

我们定义 $P_{i,j}$ 为从 $S_i$ 开始连乘，总长度为 $2^j$ 的矩阵。

那么我们的转移公式就应该是 $P_{i,j} = P_{i,j-1} P_{i+2^{j-1},j-1}$（实际情况需按需取模，详见代码）。

然后逻辑就较为简单了（尽管难调试）：对没有改变的部分连乘，对有改变的部分单独乘即可。

```cpp
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <map>

typedef long long i64;
const i64 maxn = 50007;
i64 k, mod = 998244353, pos;
int n, m;

struct modint
{
    i64 x;
    modint(i64 x_ = 0);
    modint operator+=(modint b);
    modint operator*=(modint b);
};

modint operator+(modint a, modint b);
modint operator*(modint a, modint b);

struct matrix
{
    modint data[2][2];
    matrix() { data[0][0] = data[0][1] = data[1][0] = data[1][1] = 0; }
    modint *operator[](int index) { return data[index]; }
};
matrix operator*(matrix a, matrix b);

matrix intl, f[maxn][71];

i64 s[maxn], u, v, loopid, lastloop, pow2[maxn];
std::pair<i64, i64> spec[maxn];
std::map<i64, i64> mp;

i64 getsval(i64 x)
{
    auto it = mp.find(x);
    if (it == mp.end())
        return s[x % n];
    else
        return it->second;
}

matrix fib_trans(i64 si, i64 si1)
{
    matrix res;
    res[0][0] = si1;
    res[0][1] = 1;
    res[1][0] = si;
    res[1][1] = 0;
    return res;
}

matrix gfib(i64 index) { return fib_trans(getsval(index), getsval(index + 1)); }

void build()
{
    for (int i = 0; i < n; i++)
    {
        f[i][0][0][0] = s[(i + 1) % n];
        f[i][0][0][1] = 1;
        f[i][0][1][0] = s[i];
        f[i][0][1][1] = 0;
    }

    for (int j = 1; j < 63; j++)
        for (int i = 0; i < n; i++)
            f[i][j] = f[i][j - 1] * f[(i + (1ll << (j - 1))) % n][j - 1];
}

matrix to_binary(i64 &from, i64 to)
{
    matrix res;
    res[0][0] = res[1][1] = 1;

    if (from >= to)
        return res;

    for (i64 bit = 62; bit >= 0; bit--)
    {
        if (from + (1ll << bit) <= to)
            res = res * f[from % n][bit],
            from += 1ll << bit;
    }

    return res;
}

#define pos_next intl = intl * gfib(pos++)
#define break_if  \
    if (pos == k) \
        break;

int main()
{
    intl[0][0] = intl[1][1] = 1;

    scanf("%lld%lld", &k, &mod);
    if (k == 0)
        return printf("0") & 0;

    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        scanf("%lld", s + i);
    scanf("%d", &m);
    for (int i = 0; i < m; i++)
        scanf("%lld%lld", &u, &v),
            mp[u] = v,
            spec[i] = std::make_pair(u, v);
    std::sort(spec, spec + m);
    spec[m].first = 1000000000000000007ll;
    m++;

    build();

    for (int i = 0; i < m; i++)
    {
        if (k <= spec[i].first)
        {
            intl = intl * to_binary(pos, k);
            break;
        }
        else
        {
            intl = intl * to_binary(pos, spec[i].first - 1);
            if (spec[i].first + 1 == spec[i + 1].first)
            {
                break_if;
                pos_next;
            }
            else
            {
                break_if;
                pos_next;
                break_if;
                pos_next;
                break_if;
            }
        }
    }

    printf("%lld", intl[0][1].x);
    return 0;
}

```


---

## 作者：CarroT1212 (赞：0)

### 解法分析

模拟赛题，赛时想到了正解但细节太多没写完，听讲评后优化了一下。

这类递推数列问题，初步思路肯定是矩阵快速幂优化，里头的矩阵乘法大概就是 $\begin{vmatrix}F_i&F_{i-1}\end{vmatrix}=\begin{vmatrix}F_{i-1}&F_{i-2}\end{vmatrix}\times\begin{vmatrix}s_{i-1}&1\\s_{i-2}&0\end{vmatrix}$ 的形式。只是乘上的这个矩阵是以长度为 $n$ 的周期变化的，而且还混进了 $m$ 个不太一样的 $s_i$。

一个比较容易想到的做法是把 $m$ 个不一样的 $s_i$ 影响到的矩阵所在的周期单独拿出来跑一遍矩阵乘法，然后剩下没有受到影响的周期就可以用预处理出的乘积跑矩阵幂。由于矩阵乘法不满足交换律，应该还需要一边单独跑矩乘，一边把两个特殊 $s_i$ 之间夹着的完整周期的矩阵幂按顺序跑了。

问题在于单独给受影响的周期跑矩阵乘法这个地方直接做的话复杂度可以整到 $O(nm)$ 级别，直接原地升天。这里可以用倍增或者线段树维护区间矩阵乘法，整个做法的复杂度大概就是 $O(m\log n\log k)$ 左右的，反正能过，题解区里貌似挺多是这种做法。

但是不好写啊，一个 $s_i$ 不一样会影响到两个矩阵，两个矩阵要是分散在不同的周期里又会出事，然后如果 $s_i$ 贴在一起的话又会出现一堆问题，$n=1$ 的时候貌似也要加点特判……不知道其他写了这个做法的人怎么想，反正我是想不通，结果模拟赛上就没写完。

这时可以把矩阵乘法换成 $\begin{vmatrix}F_i&F_{i-1}s_{i-1}\end{vmatrix}=\begin{vmatrix}F_{i-1}&F_{i-2}s_{i-2}\end{vmatrix}\times\begin{vmatrix}s_{i-1}&s_{i-1}\\1&0\end{vmatrix}$，这样每个特殊的 $s_i$ 就只会影响一个矩阵了，大概也不需要担心 $n=1$ 的时候会出什么锅。细节虽然还是有一点多，但是总比刚才少一些罢。记得特判 $k=0$。具体看代码。

### 代码

```cpp
struct mat {
	ll g[2][2];
	mat() { memset(g,0,sizeof(g)); }
	void bui() { memset(g,0,sizeof(g)); g[0][0]=g[1][1]=1; }
} a[N],c[N][21],ans,tmp,tp;
ll k,MOD,n,m,s[N];
pll b[N];
mat operator * (mat x,mat y) {
	mat ret;
	for (ll i=0;i<2;i++) for (ll j=0;j<2;j++) for (ll k=0;k<2;k++)
		(ret.g[i][j]+=x.g[i][k]*y.g[k][j])%=MOD;
	return ret;
}
mat mpow(mat x,ll y) {
	mat ret; ret.bui();
	while (y) { if (y&1) ret=ret*x; x=x*x,y>>=1; }
	return ret; 
}
mat que(ll l,ll r) { // 倍增查询
	mat ret; ret.bui();
	for (ll i=20;~i;i--) if (r-l+1>=1<<i) ret=ret*c[l][i],l+=1<<i;
	return ret;
}
int main() {
	ans.bui(),tmp.bui();
	scanf("%lld%lld%lld",&k,&MOD,&n);
	if (k==0) return printf("0"),0;
	for (ll i=0;i<n;i++) scanf("%lld",&s[i]);
	scanf("%lld",&m);
	for (ll i=1;i<=m;i++)
		scanf("%lld%lld",&b[i].first,&b[i].second),b[i].first++;
	b[m+1]={k+1,0};
	sort(b+1,b+m+2);
	b[0]={n-1,0}; // 塞两个边界进去好处理一点
	for (ll i=0;i<n;i++)
		a[i].g[0][0]=s[(i-1+n)%n],a[i].g[1][0]=1,
		a[i].g[0][1]=s[(i-1+n)%n],a[i].g[1][1]=0,c[i][0]=a[i];
	for (ll i=1;1<<i<n;i++) for (ll j=0;j+(1<<i)-1<n;j++)
		c[j][i]=c[j][i-1]*c[j+(1<<i-1)][i-1]; // 倍增预处理
	if (k<n) {
		for (ll i=2;i<=k;i++) ans=ans*a[i];
		printf("%lld",ans.g[0][0]);
	}
	else {
		for (ll i=2;i<n;i++) ans=ans*a[i];
		for (ll i=0;i<n;i++) tmp=tmp*a[i];
		for (ll i=1;i<=m+1;i++) {
			if (b[i].first==k+1) { // 到（刚才塞进去的）k 了
				if (k/n!=b[i-1].first/n) // 和下面同理
					ans=ans*que(b[i-1].first%n+1,n-1),
					ans=ans*mpow(tmp,k/n-b[i-1].first/n-1),
					ans=ans*que(0,k%n);
				else ans=ans*que(b[i-1].first%n+1,k%n);
				return printf("%lld",ans.g[0][0]),0;
			}
			else {
				if (b[i].first/n!=b[i-1].first/n) // 和上一个不在同一周期
					ans=ans*que(b[i-1].first%n+1,n-1), // 把上一个所在的周期补齐
					ans=ans*mpow(tmp,b[i].first/n-b[i-1].first/n-1), // 矩阵幂跑中间的完整周期
					ans=ans*que(0,b[i].first%n-1); // 把这一个所在的周期补齐
				else ans=ans*que(b[i-1].first%n+1,b[i].first%n-1); // 否则直接把两个中间的区域补齐
				tp.g[0][0]=tp.g[0][1]=b[i].second,tp.g[1][0]=1,tp.g[1][1]=0,
				ans=ans*tp;
			}
		}
	}
	return 0;
}
```

---

