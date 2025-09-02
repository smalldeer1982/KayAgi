# Fibonacci Strings

## 题目描述

### 题意：  
定义斐波那契字符串为:  
$f_1=$"a"  
$f_2=$"b"  
$f_n=f_{n-1}+f_{n-2}(n>2)$  
例如，前五项斐波那契字符串为 "a", "b", "ba", "bab", "babba"。  
有 $m$ 次询问，第 $i$ 次给出一个字符串 $s_i$，问 $s_i$ 在 $f_n$ 中的出现次数。

## 说明/提示

$m \leq 10^4, \, n \leq 10^{18}, \, \sum|s_i| \leq 10^5$

## 样例 #1

### 输入

```
6 5
a
b
ab
ba
aba
```

### 输出

```
3
5
3
3
1
```

# 题解

## 作者：summ1t (赞：2)

考虑 dp，设 $F_i$ 表示 $s$ 在 $f_i$ 中的出现次数，答案即为 $F_n$。

记 $G_i$ 为 $f_{i-1}$ 和 $f_{i-2}$ 的拼接处的 $s$ 的出现次数，则 $F_i=F_{i-1}+F_{i-2}+G_i$，考虑如何求出 $G_i$。

首先只有 $f_{i-1}$ 结尾的 $|s|-1$ 和 $f_{i-2}$ 开头的 $|s|-1$ 个字符会影响 $G_i$，同时还能注意到，当 $i$ 足够大时，开头和结尾的这 $|s|-1$ 个字符将会不变。

记 $p$ 为第一个满足 $|f_p|\ge |s|$ 的斐波那契串的下标，可以自己手推一下，发现当 $i\ge p+4$ 时，$G_i=G_{i-2}$。

而 $F_{i-2}=F_{i-3}+F_{i-4}+G_{i-2}$，可得 $G_i=F_{i-2}-F_{i-3}-F_{i-4}$，再带入 $F_i$ 的递推式，最终得到 $F_i=F_{i-1}+2F_{i-2}-F_{i-3}-F_{i-4}$。

所以我们先找到 $p$，用 kmp 暴力求出 $F_{p},F_{p+1},F_{p+2},F_{p+3}$，然后直接递推，而这个递推式显然可以矩阵快速幂优化，这道题就做完了。

时间复杂度 $O(mK^3\log n+\sum|s|)$，其中 $K=4$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define rd read()
#define gc getchar()
#define dg(ch) isdigit(ch)
#define _mul(x) ((x<<3)+(x<<1))
#define il inline
#define ll long long
#define FOR(i,j,k) for(int i=j;i<=k;i++)
#define ROF(i,j,k) for(int i=j;i>=k;i--)
il int read(){int x=0,f=1;char ch=gc;while(!dg(ch)){if(ch=='-')f=-1;ch=gc;}while(dg(ch))x=_mul(x)+(ch^48),ch=gc;return x*f;}
const int N=2e5+10,T=29,mod=1e9+7;
int MOD(int x){return x>=mod?x-mod:x;}
int m,nxt[N],len;string fs[T+4],s;ll n;
struct matrix{
	int a[4][4];
	matrix(){memset(a,0,sizeof(a));}
	matrix operator*(matrix const &T){
		matrix res;
		FOR(i,0,3) FOR(k,0,3) FOR(j,0,3) res.a[i][j]=MOD(MOD(res.a[i][j]+1ll*a[i][k]*T.a[k][j]%mod)+mod);
		return res;
	}
}ans,M;
matrix MAT(int v){
	matrix res;
	FOR(i,0,3) FOR(j,0,3) res.a[i][j]=0;
	FOR(i,0,3) res.a[i][i]=v;
	return res;
}
matrix qpow(matrix a,ll b){matrix res=MAT(1);while(b){if(b&1)res=res*a;a=a*a,b>>=1;}return res;}
void init(){
	fs[1]="a",fs[2]="b";
	FOR(i,3,T) fs[i]=fs[i-1]+fs[i-2];
	FOR(i,1,T) fs[i]="."+fs[i];
	M.a[0][0]=1,M.a[0][1]=2,M.a[0][2]=-1,M.a[0][3]=-1;
	M.a[1][0]=1,M.a[2][1]=1,M.a[3][2]=1;
}
int kmp(string s,string t){
	int cnt=0,lt=t.size()-1;
	for(int i=1,j=0;i<=lt;i++){
		while(j&&t[i]!=s[j+1]) j=nxt[j];
		if(t[i]==s[j+1]) j++;if(j==len){cnt++;j=nxt[j];}
	}
	return cnt;
}
void solve(){
	FOR(i,0,len+5) nxt[i]=0;
	cin>>s,len=s.size(),s="."+s;
	for(int i=2,j=0;i<=len;i++){
		while(j&&s[i]!=s[j+1]) j=nxt[j];
		if(s[i]==s[j+1]) j++;nxt[i]=j;
	}
	int p=1;
	while(fs[p].size()-1<len) p++;
	if(n<=p+3){printf("%d\n",kmp(s,fs[n]));return;}
	ans=MAT(0),ans.a[0][0]=kmp(s,fs[p+3]),ans.a[1][0]=kmp(s,fs[p+2]),ans.a[2][0]=kmp(s,fs[p+1]),ans.a[3][0]=kmp(s,fs[p]);
	ans=qpow(M,n-(p+3))*ans;
	printf("%d\n",ans.a[0][0]);
}
int main(){
	scanf("%lld",&n),m=rd,init();
	while(m--) solve();
	return 0;
}
```

---

## 作者：MoonPie (赞：2)

## Solution - CF177G2

[题目链接](http://codeforces.com/problemset/problem/177/G2)

### 题意

定义 Fibonacci Strings 为：

$f_1=$ "a"

$f_2=$ "b"

$f_n = f_{n-1}+f_{n-2}(n>2)$

给你 $n,m(n\le 10^{18},m\le 10^4)$，

有 $m$ 次询问，第 $i$ 次询问给出一个字符串 $s_i$ ，问 $s_i$ 在 $f_i$ 中出现的次数. $(\sum|s_i|)\le 10^5$.

### 题解

如此巨大的 $n$ ，在加上 Fibonacci ，我们不难想到用矩阵加速求解.

问题在于 $F_i+F_{i-1}$ 中间新产生的字符串 $s$ 的数量.

我们设 $s$ 的长度为 $len$，

如果我们处理出两个 $F_{base} , F{base-1}$ 满足其长度都 $\ge len$.

令 $F_{base-1}$ 长度 $len-1$ 的前缀为 $a$, 长度 $len-1$ 的后缀为 $b$

​     $F_{base}$ 长度 $len-1$ 的前缀为 $a$, 长度 $len-1$ 的后缀为 $c$ 

$G_n$ 表示 $F_{base + n}$ 中 $s$ 的数量

那么 
$$
G_n = G_{n-1} + G_{n-2} + [n\%2==1]\times vc + [n\%2==0] \times vb
$$
其中 $vc$ 表示 ca 中s的数量，$vb$ 表示 ba 中s的数量，这都是可以提前 $kmp$ 出来的.

但如果直接用这个式子来矩阵优化，常数是 $6^3$，无法接受.

---

考虑分开来计算这个式子，

$A_n$ 表示 $F_{n-1}$ 和 $F_{n-2}$ 中出现的次数(不算中间产生的贡献).

$B_n$ 表示 $F_n$ 中 $ba$ 出现的次数. 

$C_n$ 表示 $F_n$ 中 $ca$ 出现的次数.

then $G_n = A_n + B_n*vb + C_n*vc$.

显然有一下几个递推式：
$$
A_n = A_{n-1}+A_{n-2}\\
B_n = B_{n-1}+B_{n-2} + [n\%2==0]\\
C_n = C_{n-1}+C_{n-2} + [n\%2==1]\\
B_0=B_1=0\\
C_0=C_1=0
$$
经~~打表~~观察可以发现:
$$
B_n = F_n-[i\%2==1]\\
C_n=B_{n+1}
$$
上面的 $F$ 表示斐波那契数列.

所以，只要用矩阵优化 $log$ 求$F$ 就完事了.

###  Code

```cpp
const int N=1e5+5;
int n,m,len,base,F[30],nxt[N];
string s,t,Fs[30],F1,F2;
int get_num(string a) {
    int res=0;
    for(int i=0,j=0;i<a.length();++i) {
        while(j>=0 && t[j+1]!=a[i]) j=nxt[j];
        if(++j==len) ++res,j=nxt[j];
    }
    return res;
}
struct matrix_base { int ma[2][2]; }bm;
struct matrix_ans { int ma[2]; }ans;
inline void mul_base() {
    matrix_base res;
    memset(res.ma,0,sizeof(res.ma));
    for(int i=0;i<2;++i) for(int j=0;j<2;++j) for(int k=0;k<2;++k) my_add(res.ma[i][j] , bm.ma[i][k]*bm.ma[k][j]%mod);
    bm = res;
}
inline void mul_ans() {
    matrix_ans res;
    memset(res.ma,0,sizeof(res.ma));
    for(int i=0;i<2;++i) for(int j=0;j<2;++j) my_add(res.ma[i] , ans.ma[j]*bm.ma[j][i]%mod);
    ans = res;
}
int calc() {
    len = s.length();
    t = "%"+s;
    nxt[0]=-1;
    for(int i=2,j=0;i<=len;++i) {
        while(j>=0 && t[j+1]!=t[i]) j=nxt[j];
        nxt[i] = ++j;
    }
    F[1]=F[2]=1;
    Fs[1]="a";
    Fs[2]="b";
    for(int i=3;;++i) {
        if(F[i-2]>len) {
            Fs[i] = Fs[i-1] + Fs[i-2];
            base = i-1;
            break;
        }
        F[i] = F[i-1] + F[i-2];
        Fs[i] = Fs[i-1] + Fs[i-2];
    }

    string a,b,c;
    for(int i=0;i<len-1;++i) a+=Fs[base-1][i];
    for(int i=Fs[base-1].length()-(len-1);i<Fs[base-1].length();++i) b+=Fs[base-1][i];
    for(int i=Fs[base].length()-(len-1);i<Fs[base].length();++i) c+=Fs[base][i];
    int vc = get_num(c+a);
    int vb = get_num(b+a);
    if(n-base <= 1) {
        return get_num(Fs[n]);
    }
    ans.ma[0]=0; ans.ma[1]=1;
    memset(bm.ma,0,sizeof(bm.ma));
    bm.ma[0][1]=bm.ma[1][0]=bm.ma[1][1]=1;
    int y = n-base;
    for(int i=0;(1ll<<i)<=y;++i,mul_base()) if(y&(1ll<<i)) mul_ans();
    int B = ans.ma[0] - (y%2==1);

    ans.ma[0]=0; ans.ma[1]=1;
    memset(bm.ma,0,sizeof(bm.ma));
    bm.ma[0][1]=bm.ma[1][0]=bm.ma[1][1]=1;        
    for(int i=0;(1ll<<i)<=y-1;++i,mul_base()) if((y-1)&(1ll<<i)) mul_ans();
    int C = ans.ma[0] - ((y-1)%2==1);

    ans.ma[0] = get_num(Fs[base]);
    ans.ma[1] = get_num(Fs[base]+Fs[base-1]);
    memset(bm.ma,0,sizeof(bm.ma));
    bm.ma[0][1]=bm.ma[1][0]=bm.ma[1][1]=1;
    for(int i=0;(1ll<<i)<=y;++i,mul_base()) if(y&(1ll<<i)) mul_ans();
    return (ans.ma[0] + B*vb%mod + C*vc%mod)%mod;
}
void solve() {
    cin>>n>>m;
    for(int i=1;i<=m;++i) {
        cin>>s;
        printf("%lld\n",calc());
    }
}
```

---

## 作者：ax_by_c (赞：1)

[可能更好的阅读体验](https://www.cnblogs.com/axbyc/articles/18549347)

模拟赛题，记录一下。

$k\le 29$ 时直接 ACAM 即可（这一步实际上是最后得到的），下面考虑 $k>29$ 的情况。

记 $F_{i,j}$ 表示 $s_j$ 在 $f_i$ 中的出现次数。

设 $F_{i,j}=F_{i-1,j}+F_{i-2,j}+k_{i,j}$，则 $k_{i,j}$ 是 $f_{i-1}$ 的一个后缀拼上 $f_{i-2}$ 的一个前缀得到 $s_j$ 的次数。

于是只需要关心 $f_i$ 的最前和最后的 $100000$ 个字符。

容易计算得到 $fib_{26}\ge100000$，不难发现 $i\ge26$ 时 $f_i$ 的最前 $100000$ 个字符保持不变，$i\ge28$ 时 $f_i$ 的最后 $100000$ 个字符与 $f_{i-2}$ 相同。

于是可得 $i\ge28$ 时 $k_{i,j}=k_{i-2,j}$，那么矩阵快速幂即可，关键在于求 $F_{26,j},F_{27,j},k_{28,j},k_{29,j}$，使用 ACAM 求出 $F_{26,j},F_{27,j},F_{28,j},F_{29,j}$ 即可。

时间复杂度 $O(\sum\lvert s\rvert+q\log n)$，但是建自动机的时候不优化也能过？

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace ax_by_c{
typedef long long ll;
const int mod=1e9+7;
const int QQ=1e5+5;
const int M=35;
const int L=514229+5;
const int LS=1e5+5;
char str[M][L];
int len[M];
void Init(){
	len[1]=1;
	str[1][1]='a';
	len[2]=1;
	str[2][1]='b';
	for(int i=3;i<=29;i++){
		len[i]=len[i-1]+len[i-2];
		for(int j=1;j<=len[i-1];j++){
			str[i][j]=str[i-1][j];
		}
		for(int j=1;j<=len[i-2];j++){
			str[i][len[i-1]+j]=str[i-2][j];
		}
	}
}
ll n;
int q,pos[QQ];
char s[LS];
int idx,son[LS][2];
int ins(){
	int u=0;
	for(int i=1;s[i];i++){
		if(!son[u][s[i]-'a'])son[u][s[i]-'a']=++idx;
		u=son[u][s[i]-'a'];
	}
	return u;
}
queue<int>Q;
int nxt[LS],lst[LS],id;
void bld_acam(){
	Q.push(0);
	while(Q.size()){
		int u=Q.front();
		Q.pop();
		lst[++id]=u;
		for(int i=0;i<=1;i++){
            if(!u){
                if(son[u][i])Q.push(son[u][i]);
                continue;
            }
			if(son[u][i]){
				nxt[son[u][i]]=son[nxt[u]][i];
				Q.push(son[u][i]);
			}
            else son[u][i]=son[nxt[u]][i];
		}
	}
}
int cnt[LS],f26[QQ],f27[QQ],f28[QQ],f29[QQ];
void mch(int n){
	for(int i=0;i<=idx;i++)cnt[i]=0;
	int u=0;
	for(int i=1;i<=len[n];i++){
        u=son[u][str[n][i]-'a'];
		cnt[u]++;
	}
	for(int i=idx+1;i>=1;i--)cnt[nxt[lst[i]]]+=cnt[lst[i]];
}
struct matr{
	int n,m;
	int a[3][3];
	void clr(){
		for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
		a[i][j]=0;
	}
};
matr operator * (const matr& a,const matr& b){
	matr c;
	c.n=a.n;
	c.m=b.m;
	c.clr();
	for(int i=0;i<a.n;i++){
		for(int j=0;j<a.m;j++){
			for(int k=0;k<b.m;k++){
				c.a[i][k]=(c.a[i][k]+(ll)a.a[i][j]*b.a[j][k]%mod)%mod;
			}
		}
	}
	return c;
}
matr operator ^ (matr a,ll b){
	matr r=a;
	b--;
	while(b){
		if(b&1){
			r=r*a;
		}
		a=a*a;
		b>>=1;
	}
	return r;
}
void main(){
	Init();
	scanf("%lld %d",&n,&q);
	for(int i=1;i<=q;i++){
		scanf("%s",s+1);
		pos[i]=ins();
	}
	bld_acam();
	if(n<=29){
		mch(n);
		for(int i=1;i<=q;i++){
			printf("%d\n",cnt[pos[i]]);
		}
	}
	else{
		mch(26);
		for(int i=1;i<=q;i++)f26[i]=cnt[pos[i]];
		mch(27);
		for(int i=1;i<=q;i++)f27[i]=cnt[pos[i]];
		mch(28);
		for(int i=1;i<=q;i++)f28[i]=cnt[pos[i]];
		mch(29);
		for(int i=1;i<=q;i++)f29[i]=cnt[pos[i]];
		matr g0,g1,S,gg;
		g0.n=3;
		g0.m=3;
		g0.clr();
		g0.a[1][0]=1;
		g0.a[0][1]=1;
		g0.a[1][1]=1;
		g0.a[2][2]=1;
		g1.n=3;
		g1.m=3;
		g1.clr();
		g1.a[1][0]=1;
		g1.a[0][1]=1;
		g1.a[1][1]=1;
		g1.a[2][2]=1;
		S.n=1;
		S.m=3;
		for(int i=1;i<=q;i++){
			g0.a[2][1]=((ll)f28[i]-f27[i]-f26[i]+mod*2)%mod;
			g1.a[2][1]=((ll)f29[i]-f28[i]-f27[i]+mod*2)%mod;
			S.a[0][0]=f28[i];
			S.a[0][1]=f29[i];
			S.a[0][2]=1;
			gg=g0*g1;
			gg=gg^((n-29)/2);
			S=S*gg;
			if(n%2==0)S=S*g0;
			printf("%d\n",S.a[0][1]);
		}
	}
}
}
int main(){
	ax_by_c::main();
	return 0;
}
```

---

## 作者：TernaryTree (赞：1)

好题。

对于一次询问 $s_i$，找到一个 $m$ 满足 $|f_{m-1}|,|f_m|\ge |s_i|$。注意到 $m$ 很小，若 $k\lt m-1$，直接 kmp 暴力求解；否则，记 $s_i$ 在 $f_j$ 中出现次数为 $a_j$，先 kmp 求出 $a_{m-1}$ 和 $a_m$，其余的有：$a_j=a_{j-1}+a_{j-2}+$ 一些多出来的。一些多出来的是指：$f_{j-1}$ 的后 $|s_i|-1$ 位与 $f_{j-2}$ 的前 $|s_i|-1$ 位的拼接中 $s_i$ 的出现次数。

令字符串 $x$ 与 $y$ 的拼接为 $xy$，记 $f_{m-1}=u$，$f_{m}=v$，则有 $f_{m+1}=v \ u$，$f_{m+2}=vu \ v$，$f_{m+3}=vuv\ vu$，以此类推。不难发现，因为我们开始找到的 $m$ 满足 $|f_{m-1}|,|f_m|\ge |s_i|$，所以每次拼接的前后缀一定被完全包含在 $u$ 或者 $v$ 中；更具体地，两个拼接串需要取的前后缀也恰好是 $u$ 或 $v$ 的前后缀。由于 $f_m=f_{m-1}+f_{m-2}$，所以 $u$ 和 $v$ 长为 $|s_i|-1$ 的前缀必定相等，记为 $A$。同时分别记 $u$ 长为 $|s_i|-1$ 的后缀与 $v$ 长为 $|s_i|-1$ 的后缀为 $B,C$。转移时，根据上面的手摸，“一些多出来的”部分只会出现两种值，并且交替出现：其一为 $BA$ 中 $s_i$ 出现次数，另一个是 $CA$ 中 $s_i$ 出现次数。于是对 $a$ 数组两两捆绑着做次数为 $\left\lfloor\dfrac{k-m+1}2\right\rfloor$ 的矩阵快速幂，形如 $\begin{bmatrix}a_{2k} \\ a_{2k+1}\\ 1\end{bmatrix}$ 即可。

这样是 $q \cdot 3^3\log k+\sum |s_i|$ 的，虽然看起来很能跑但是因为常数巨大会 T 掉 #41，这里加上一个剪枝：算出来的几个出现次数全部为 $0$，则后面结果也必定为 $0$，不需要快速幂；这样可以通过前 48 个点，但 T 在了 #49。观察 #49 发现很多 $s_i$ 完全一样，因此加个记忆化就过了，跑的飞快。[Code](https://www.luogu.com.cn/paste/4tlho1zc)。

---

## 作者：Hoks (赞：0)

## 前言
好题。

[类似题](https://www.luogu.com.cn/problem/CF1466G)。

广告：[『从入门到入土』串串学习笔记](https://www.luogu.com.cn/article/dv6dig1o)。
## 思路分析
还是类似的，我们来把一个字符串拆开考虑。

我们先找到第一个长度比询问串长的串 $f_x$。

那么询问串的出现可能只可能是：
1. 在 $f_x$ 或 $f_{x+1}$ 中整个出现。
2. 在 $f_x+f_{x+1},f_{x+1}+f_x$ 中过拼接点出现。

对于 $1$，我们直接数出分别的出现次数然后矩阵快速幂算下 $f_x/f_{x+1}$ 在 $f_n$ 中的出现次数。

对于 $2$，我们直接暴力合并串数出过拼接点的出现次数。

然后不难发现这个东西本身就是符合斐波那契数列性质的，直接套用斐波那契数列的矩阵乘法乘下就行了。
## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define ls (p<<1)
#define rs (ls|1)
#define mid ((l+r)>>1)
using namespace std;
const int N=2e5+10,V=2,M=28,K=1e5+10,INF=1e18,p=13331,mod=1e9+7;
int n,m,l[N],nxt[N];char s[M][N],t[N],a[N],b[N];
struct Matrix
{
	int a[V][V];
	Matrix(int x,int y)
	{
		memset(a,0,sizeof a);
		if(~x) a[0][0]=y,a[0][1]=x;
		else a[0][0]=a[0][1]=a[1][0]=1;
	}
	Matrix operator * (const Matrix &x) const
	{
		Matrix c(0,0);memset(c.a,0,sizeof c.a);
		for(int k=0;k<V;k++) for(int i=0;i<V;i++)
			for(int j=0;j<V;j++) c.a[i][j]=(c.a[i][j]+a[i][k]*x.a[k][j])%mod;
		return c;
	}
};
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(long long x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
namespace KMP
{
	inline void kmp(char s[],int n)
	{
		for(int i=2,j=0;i<=n;i++)
		{
			while(j&&s[i]!=s[j+1]) j=nxt[j];
			if(s[i]==s[j+1]) j++;nxt[i]=j;
		}
	}
	inline int findstr(int n,int m,char s1[],char s2[])
	{
		int j=0,res=0;
		for(int i=1;i<=n;i++)
		{
			while(j&&s2[j+1]!=s1[i]) j=nxt[j];
			if(s2[j+1]==s1[i]) j++;
			if(j==m) res++,j=nxt[j];
		}return res;
	}
}
using namespace KMP;
inline int calc(int x,int y,int k)
{
	if(!~k) return x;Matrix res(x,y),base(-1,-1);
	while(k)
	{
		if(k&1) res=res*base;
		base=base*base;k>>=1;
	}return res.a[0][0];
}
inline int get(int x){return calc(1,0,x)-(x&1);}
inline void solve()
{
	n=read(),m=read();s[1][++l[1]]='a';s[2][++l[2]]='b';
	for(int i=3;i<M;i++)
	{
		for(int j=1;j<=l[i-1];j++) s[i][++l[i]]=s[i-1][j];
		for(int j=1;j<=l[i-2];j++) s[i][++l[i]]=s[i-2][j];
	}
	for(int p=1,ll,la,lb,x=1,ans;p<=m;p++)
	{
		la=lb=ll=0;rd(t,ll);for(int j=1;j<M;j++) if(l[j-1]>=ll){x=j;break;}
		for(int i=l[x-1]-ll+2;i<=l[x-1];i++) a[++la]=s[x-1][i];
		for(int i=l[x]-ll+2;i<=l[x];i++) b[++lb]=s[x][i];
		for(int i=1;i<ll;i++) a[++la]=s[x-1][i],b[++lb]=s[x-1][i];
		if(n<x-1){put("0\n");continue;}kmp(t,ll);
		ans=calc(findstr(l[x-1],ll,s[x-1],t),findstr(l[x],ll,s[x],t),n-x);
		ans=(ans+findstr(la,ll,a,t)*get(n-x)+findstr(lb,ll,b,t)*get(n-x+1))%mod;
		print(ans);put('\n');
	}
}
signed main()
{
    int T=1;
    // T=read();
    while(T--) solve();
    genshin:;flush();return 0;
}
```

---

## 作者：Push_Y (赞：0)

[view in Push_Y's blog](https://www.wzsyyh.ml/post/CF177G/)

> CF*2600，应当是到目前为止做过的题里相当难的一道了。

### Solution

前几天刚好做了一道也是斐波那契字符串相关的 [CF379D New Year Letter](https://codeforces.com/problemset/problem/379/D)，类似于[我那题的题解](https://www.wzsyyh.ml/post/CF379D/)，打表出拼接字符串出现的次数。

![](https://cdn.luogu.com.cn/upload/image_hosting/r27xb3ux.png)

现在需要确定的就是表中的 `a` 与 `b` 具体表示的字符串。这里 `a` 与 `b` 应当满足**不超过 2 次拼接**的条件。显然，**不超过 2 次拼接**这个条件可以通过找到**最小的大于询问串串长的斐波那契数列中的数所对应的斐波那契字符串**来解决。加粗的这句话读着有点绕，仔细理解一下应该就会做了。

那么就每个询问独立做，每次用 KMP 计算 `a`、`b`、`ab`、`ba`、`bb` 中模式串的个数再统计答案。

### CODE

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
typedef pair<int,int> pi;
inline int gin(){
    int s=0,f=1;
    char c=getchar();
    while(c<'0' || c>'9'){
        if(c=='-') f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        s=(s<<3)+(s<<1)+(c^48);
        c=getchar();
    }
    return s*f;
}

const int mod=1e9+7;
int n,m,k,t,fib[32],fail[1000005];
string f[32];
char s[100005];
map<string,int> mp;

pi Fib(int n) {
    if(n< 0) return {0,0};
    if(n==0) return {0,1};
    pi p=Fib(n>>1);
    int c=p.first*((2*p.second-p.first+mod)%mod)%mod;
    int d=(p.first*p.first+p.second*p.second)%mod;
    if(n&1) return {d,c+d};
    else return {c,d};
}

inline void pre() {
	fail[1]=0;
	int j=0;
	for(int i=1;i<n;i++){
		while(j && s[j+1]!=s[i+1]) j=fail[j];
		if(s[j+1]==s[i+1]) j++;
		fail[i+1]=j;
	}
}

inline int kmp(string S) {
    int len=S.size();
    S=" "+S;
    int j=0,res=0;
    for(int i=0;i<len;i++) {
        while(j && s[j+1]!=S[i+1]) j=fail[j];
        if(s[j+1]==S[i+1]) j++;
        if(j==n) {
            res=(res+1)%mod;
            j=fail[j];
        }
    }
    return res%mod;
}

signed main(){
    // freopen("test.in","r",stdin);
    // freopen("test.out","w",stdout);
    fib[0]=0,fib[1]=1,f[1]="a",f[2]="b";
    for(int i=2;i<=31;i++) fib[i]=fib[i-1]+fib[i-2];
    for(int i=3;i<=31;i++) f[i]=f[i-1]+f[i-2];
    k=gin(),m=gin();
    if(k==1) {
        while(m--) {
            scanf("%s",s+1);
            if(s[1]=='a' && s[2]==0) puts("1");
            else puts("0");
        }
        return 0;
    }
    if(k==2) {
        while(m--) {
            scanf("%s",s+1);
            if(s[1]=='b' && s[2]==0) puts("1");
            else puts("0");
        }
        return 0;
    }
    while(m--) {
        scanf("%s",s+1);
        if(mp[s+1]) {
            printf("%I64d\n",mp[s+1]);
            continue;
        }
        n=strlen(s+1);
        pre();
        for(int i=2;i<=31;i++) if(fib[i]>n) {t=i; break;}
        if(t>=k) {
            printf("%I64d\n",kmp(f[k]));
            continue;
        }
        // if(t-1>k) {puts("0"); continue;}
        // else t--;
        // if(t>2) t--;
        // else t=1;
        string s1=f[t],s2=f[t+1];
        int a=kmp(s1),b=kmp(s2),ab=(kmp(s1+s2)-a-b+mod)%mod,ba=(kmp(s2+s1)-a-b+mod)%mod,bb=(kmp(s2+s2)-b-b+mod)%mod;
        int A=Fib(k-2-t+1).first,B=Fib(k-1-t+1).first;
        int AB=Fib(k-2-t+1).first+(((k-2-t+1>0) && (k-2-t+1)&1)?-1:0);
        int BA=A;
        int BB=Fib(k-3-t+1).first+(((k-3-t+1>0) && (k-3-t+1)&1)?-1:0);
        // printf("$ %lld $ \n",t);
        // cout<<s1<<" "<<s2<<" "<<s1+s2<<" "<<s2+s1<<" "<<s2+s2<<"\n";
        // printf("& %lld %lld %lld %lld %lld\n",a,b,ab,ba,bb);
        // printf("# %lld %lld %lld %lld %lld\n",A,B,AB,BA,BB);
        int ans=((a*A%mod+b*B%mod)%mod+(ab*AB%mod+ba*BA%mod)%mod+bb*BB%mod)%mod;
        mp[s+1]=ans;
        printf("%I64d\n",ans);
    }
    return 0;
}
```


---

## 作者：Dimly_dust (赞：0)

主要问题在与 $f_p$ 与 $f_{p-1}$ 拼接时，$f_p$ 的某个后缀与 $f_{p-1}$ 的某个前缀可能恰好拼成 $s_i$，即产生额外的出现次数。当 $|f_p|$ 与 $|f_{p-1}|$ 都大于等于 $|s_i|$ 时，这个数值就等于 $f_n$ 长度为 $|s_i|−1$ 的后缀与 $f_{p-1}$ 长度为 $|si|-1$ 的前缀组成的字符串中 $s_i$ 的出现次数。

我们设 $f_{p-1}$ 长度为 $|s_i|-1$ 的前缀为 $a$，长度为 $|s_i|-1$ 的后缀为 $b$，$f_p$ 长度为 $|s_i|−1$ 的前缀为 $a$，长度为 $|s_i|-1$ 的后缀为 $c$。我们观察发现：

|  | 长度为 $s_i-1$ 的前缀 | 长度为$s_i-1$的后缀 | 产生额外贡献的字符串 |
| :-----------: | :-----------: | :-----------: | :-----------: |
| $f_{p-1}$ | $a$ | $b$ |  |
| $f_{p}$ | $a$ | $c$ | $ca$ |
| …… | …… | …… | …… |
| $f_{p+2k}$ | $a$ | $c$ | $ca$ |
| $f_{p+2k+1}$ | $a$ | $b$ | $ba$ |

我们设 $s_i$ 在 $ca$ 中的出现次数为 $n_c$，在 $ba$ 中的出现次数为 $n_b$，$O_n$ 表示 $s_i$ 在 $f_{n+p}$中的出现次数。

那么，容易得到：

$On=O_{n-1}+O_{n-2}+\begin{cases}n_c~~if~n~mod~2=0\\n_b~~if~n~mod~2=1\end{cases}$

考虑拆分贡献，即设$A_n$，$B_n$，$C_n$分别表示 $f_n$ 中，$s_i$ 在 $f_p$ 和 $f_{p+1}$ 中的出现次数，在所有 $ba$ 中的出现次数，在所有 $ca$ 中的出现次数。那么，我们有

- $O_n=A_n+B_n×n_b+C_n×n_c$
- $A_n=A_{n-1}+A_{n-2}$
- $B_n=B_{n-1}+B_{n-2}+[n~mod~2=1]=B_{n-1}+B_{n-2}+\frac{1-(-1)^n}{2}$
- $C_n=C_{n-1}+C_{n-2}+[n~mod~2=0]=C_{n-1}+C_{n-2}+\frac{1+(-1)^n}{2}$
- $B_0=B_1=C_0=C_1=0$

其中，$A_n$ 在我们计算出 $A_0$ 和 $A_1$ 后，用矩阵快速幂得到。故我们只用考虑 $B_n$ 和 $C_n$ 这两个类似的数列。

通过使用 [OEIS](https://oeis.org/) 或其他的数列求解方法，我们得到$B_n=F_{n-1}-\frac{1+(-1)^n}{2}$，以及$Cn=F_n-\frac{1-(-1)^n}{2}$。其中，$F_n$ 为第 $n$ 个斐波那契数。它们同样可以用矩阵快速幂求出。

退了这么久的柿子，看看代码实现吧：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=30010, MAX=200000,MOD=1000000007;
string fib[N];
int n,m,len,cnt,lef[N],nex[MAX+10];
char tmp[MAX + 10];
string a,b,c,tp;
struct matrix
{
    int mat[3][3];
    matrix()
    {
        memset(mat,0,sizeof mat);
    }
    matrix operator * (const matrix& x) const
    {
        matrix ret = matrix();
        for (int k = 1 ; k <= 2 ; ++ k)
            for (int i = 1 ; i <= 2 ; ++ i)
                for (int j = 1 ; j <= 2 ; ++ j)
                    (ret.mat[i][j] += 1ll * mat[i][k] * x.mat[k][j] % MOD) %= MOD;
        return ret;
    }
};
matrix bas;
matrix power(matrix a,int b)
{
    matrix ret = matrix();
    ret.mat[1][1] = ret.mat[2][2] = 1;
    while (b)
    {
        if (b&1) ret = ret * a;
        a = a * a;
        b >>= 1;
    }
    return ret;
}
int getfib(int x)
{
    matrix ret = power(bas,x);
    return ret.mat[1][2];
}
int getnum()
{
    int ret = 0;
    for (int i = 0, j = 0 ; i < (int)tp.length() ; ++ i)
    {
        while (j >= 0 && tmp[j+1] != tp[i])
            j = nex[j];
        ++ j;
        if (j == len) ++ ret, j = nex[j];
    }
    return ret;
}
int solve()
{
    nex[0] = -1;
    for (int i = 2, j = 0 ; i <= len ; ++ i)
    {
        while (j >= 0 && tmp[j+1] != tmp[i])
            j = nex[j];
        nex[i] = ++j;
    }
    int p = lower_bound(lef+1,lef+cnt+1,len) - lef;
    ++ p;
    if (n <= p+1)
    {
        tp = fib[n];
        return getnum();
    }
    a = fib[p].substr(0,len-1);
    b = fib[p].substr(lef[p] - len+1,len-1);
    c = fib[p+1].substr(lef[p+1] - len+1,len-1);
    int nb, nc, n0, n1, pos = n - p, ret = 0;
    tp = b + a;
    nb = getnum();
    tp = c + a;
    nc = getnum();
    tp = fib[p];
    n0 = getnum();
    tp = fib[p+1];
    n1 = getnum();
    (ret += 1ll * (getfib(pos) - (pos&1)) * nc % MOD) %= MOD;
    (ret += 1ll * (getfib(pos-1) - 1 + (pos&1)) * nb % MOD) %= MOD;
    matrix sta = matrix();
    sta.mat[1][1] = n1;
    sta.mat[1][2] = sta.mat[2][1] = n0;
    sta = sta * power(bas,pos);
    (ret += sta.mat[1][2]) %= MOD;
    ret = (ret % MOD + MOD) % MOD;
    return ret;
}
main()/*这里不能写int main  因为宏定义中定义了int long long。
但主函数是只允许定义 int 和 signed 类的 */
{
    fib[1] = "a";
    fib[2] = "b";
    for(int i=3 ;; ++i)
    {
        fib[i]=fib[i-1]+fib[i-2];
        lef[i]=fib[i].length();
        cnt=i;
        if(lef[i-1]>=MAX) break;
    }
    bas.mat[1][1]=bas.mat[1][2]=bas.mat[2][1]=1;
    cin>>n>>m;
    for(int i=1 ; i<=m ; ++i)
    {
        scanf("%s",tmp+1);
        len = strlen(tmp+1);
        cout << solve() << endl;
    }
    return 0;
}

```


---

