# Yet Another String Matching Problem

## 题目描述

Suppose you have two strings $ s $ and $ t $ , and their length is equal. You may perform the following operation any number of times: choose two different characters $ c_{1} $ and $ c_{2} $ , and replace every occurence of $ c_{1} $ in both strings with $ c_{2} $ . Let's denote the distance between strings $ s $ and $ t $ as the minimum number of operations required to make these strings equal. For example, if $ s $ is abcd and $ t $ is ddcb, the distance between them is $ 2 $ — we may replace every occurence of a with b, so $ s $ becomes bbcd, and then we may replace every occurence of b with d, so both strings become ddcd.

You are given two strings $ S $ and $ T $ . For every substring of $ S $ consisting of $ |T| $ characters you have to determine the distance between this substring and $ T $ .

## 样例 #1

### 输入

```
abcdefa
ddcb
```

### 输出

```
2 3 3 3 
```

# 题解

## 作者：Lskkkno1 (赞：14)

- [CF954I Yet Another String Matching Problem](https://www.luogu.com.cn/problem/CF954I)

### 题目描述

给定两个字符串 $S$, $T$, $len_S \ge len_T$, 字符集大小为 $[a, f]$。

每次操作可以将一种字符变成另外一种字符，对于 $S$ 的每一个位置，询问最少进行多少次操作，可以变成 $T$。

### 正解

可以暴力枚举集合划分（即哪些字符要变成相同的），然后用哈希或者 KMP 做到 $O(n)$ 判断是否可行。

之前有些题解说的复杂度不太对，集合划分的复杂度是 $O(Bell(n))$ 的而不是 $O(n!)$ 的，而 $B_6$ 只有 $203$，所以足矣通过此题。

---

讲一下怎么搜集合划分吧。

其实集合划分的写法就跟生成森林的方法差不多。

从小往大枚举元素，对于一个元素，它有两种操作 :

1. 作为新的森林的根。

2. 加入一个已经存在的森林。

#### 给出代码 :

```cpp
int fa[N];
int blk[N], cb;

void divSet(int dep) {
	if(dep > maxDep) {
		solve();
		return void();
	}
	
	fa[dep] = dep;
	blk[++cb] = dep;
	divSet(dep + 1);
	
	blk[cb--] = 0;
	for(int i = 1; i <= cb; ++i) {
		fa[dep] = blk[i];
		divSet(dep + 1);
	}
}
```

---

话说这题 $O(Bell(|\Sigma|)\times n)$ 的复杂度其实可以跑 $|\Sigma| = 8$，但 $|\Sigma|$ 更大的情况就不能这么做了。

### 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 125005;

int ans[N];
int fail[N];
int lenS, lenT;
char s[N], t[N];

int fa[N];
int blk[N], cb;

inline int tr(char ch) { return ch - 'a'; }

void solve(int res) {
	int cur(0);
	fail[1] = 0;
	for(int i = 2; i <= lenT; ++i) {
		while(cur && fa[tr(t[i])] != fa[tr(t[cur + 1])])
			cur = fail[cur];
		if(fa[tr(t[i])] == fa[tr(t[cur + 1])])
			++cur;
		fail[i] = cur;
	}
	cur = 0;
	for(int i = 1; i <= lenS; ++i) {
		while(cur && fa[tr(s[i])] != fa[tr(t[cur + 1])])
			cur = fail[cur];
		if(fa[tr(s[i])] == fa[tr(t[cur + 1])])
			++cur;
		if(cur == lenT) {
			ans[i] = min(ans[i], res);
			cur = fail[cur];
		}
	}
}

void divSet(int dep) {
	if(dep > tr('f')) {
		++cnt;
		solve(6 - cb);
		return void();
	}
	
	fa[dep] = dep;
	blk[++cb] = dep;
	divSet(dep + 1);
	
	blk[cb--] = 0;
	for(int i = 1; i <= cb; ++i) {
		fa[dep] = blk[i];
		divSet(dep + 1);
	}
}

int main() {
	scanf("%s %s", s + 1, t + 1);
	lenS = strlen(s + 1);
	lenT = strlen(t + 1);
	
	for(int i =lenT; i <= lenS; ++i)
		ans[i] = 233;
	divSet(0);
	for(int i = lenT; i <= lenS; ++i)
		printf("%d%c", ans[i], " \n"[i == lenS]);
	return 0;
}
```

---

## 作者：xcxcli (赞：7)

题解为什么都是$FFT$~~~

思路来自于 [$\color{black}\textbf{F}\color{red}\textbf{rame}$](https://www.luogu.org/space/show?uid=81844) 巨佬

---
题面翻译：对于两个等长的字符串$s,t$，每次可以花费$1$的代价，将某一种字符全都替换成另一种字符。

设$f(s,t)$为最少花费多少代价，使得$s=t$。

给定字符串$s,t$，求$s$每个与$t$长度相同的字串$s'$的$f(s',t)$。

---
容易发现，将字符$i$改成字符$j$，与将字符$j$改成字符$i$效果相同，所以当我们修改时，使$i\le j$。

还能发现，将$i$修改为$j$，再将所有的$j$修改为$k$，与$i,j$都修改为$k$效果相同。

于是我们可以$O(6!)$枚举每个字符$i$将要修改为的字符$j(i\le j)$，并对$s,t$串进行$O(n)$的$KMP$。对于能够匹配的字串，更新答案。

Code:

```cpp
#include<stdio.h>
#include<string.h>
int rd(){
	int k=0;char c=getchar();
	while(c>'9'||c<'0')c=getchar();
	while(c>='0'&&c<='9')k=k*10+c-'0',c=getchar();
	return k;
}
const int N=500001;
int Min(int x,int y){return x<y?x:y;}
int n,m,a[N],b[N],ans[N],kmp[N],i[7];char s[N],t[N];
void KMP(int C){
	for(int i=2,j=0;i<=m;++i){
		while(j&&b[i]!=b[j+1])j=kmp[j];
		if(b[i]==b[j+1])++j;
		kmp[i]=j;
	}
	for(int i=1,j=0;i<=n;++i){
		while(j&&a[i]!=b[j+1])j=kmp[j];
		if(a[i]==b[j+1])++j;
		if(j==m)ans[i]=Min(ans[i],C),j=kmp[j];
	}
}
int main(){
	freopen("data.in","r",stdin);
	freopen("data.out","w",stdout);
	memset(ans,0x3f,sizeof(ans));//答案初始化为INF
	scanf("%s%s",s+1,t+1),n=strlen(s+1),m=strlen(t+1);
	i[5]=5;
	for(i[0]=0;i[0]<6;++i[0])for(i[1]=1;i[1]<6;++i[1])for(i[2]=2;i[2]<6;++i[2])for(i[3]=3;i[3]<6;++i[3])
	for(i[4]=4;i[4]<6;++i[4]){
    	//枚举每个字符将要修改为的字符。注意i<=j
		for(int j=1;j<=n;++j)a[j]=i[s[j]-'a'];
        for(int j=1;j<=m;++j)b[j]=i[t[j]-'a'];
        //s修改后为a，t修改后为b
		KMP((i[0]>0)+(i[1]>1)+(i[2]>2)+(i[3]>3)+(i[4]>4));
        //若i[x]=x，则不需要修改，否则代价为1
	}
	for(int i=m;i<=n;++i)printf("%d ",ans[i]);puts("");
	return 0;
}
```

---

## 作者：学委 (赞：5)

对于 s 的某个子串和 t，可以这样求：假如 6 个点表示这 6 种字母，那么 s 和 t 同一位置的字符连边，然后同一连通块必须染成一种字符（存在一条边连着两个不同的字符就不合法了）。

考虑怎么快速求出 s 所有子串与 t 的连边。反转字符串 t 以后，对于字符 a, b：**对于 p 结尾的 s 子串**，这两个字符连边当且仅当 pos[a] + pos[b] = p。这可以用 FFT 或 NTT 卷 a 出现位置和 b 出现位置。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using std::swap;
typedef long long LL; const int N = 5e5 + 10;
const LL P = 998244353, G = 3, invG = (P + 1) / G;
char s[N], t[N]; LL a[N], b[N]; int slen, tlen,
 logn = 0, n, invn, rev[N];
int atbit(int x) { return 1 << (x - 1); }
LL pow(LL x, LL p) {
  LL res = 1; while (p) {
    if (p & 1) res = res * x % P;
    x = x * x % P, p >>= 1;
  } return res;
} LL inv(LL x) { return pow(x, P - 2); }
LL mod(LL x) { return (x % P + P) % P; }
void NTT(LL* a, int typ) {
  for (int i = 0; i <= n - 1; ++i)
    if (i < rev[i]) swap(a[i], a[rev[i]]);
  for (int len = 2; len <= n; len *= 2) {
    int mid = len / 2;
    LL wunit = pow((typ == 1) ? G : invG, (P - 1) / len);
    for (int s = 0; s <= n - 1; s += len) {
      LL wcur = 1;
      for (int pos = 0; pos <= mid - 1; ++pos) {
        LL h = a[s + pos], g = a[s + mid + pos];
        a[s + pos] = mod(h + wcur * g);
        a[s + mid + pos] = mod(h - wcur * g);
        wcur = mod(wcur * wunit);
      }
    }
  } if (typ == -1) for (int i = 0; i <= n - 1; ++i)
    a[i] = mod(a[i] * invn);
} int g[N][7][7]; int vis[7];
void dfs(int u, int gnum) {
  vis[u] = 1;
  for (int v = 1; v <= 6; ++v)
    if (g[gnum][u][v] and not vis[v]) dfs(v, gnum);
}
int main() {
  scanf("%s%s", s + 1, t + 1);
  slen = strlen(s + 1), tlen = strlen(t + 1);
  for (int i = 1; i <= tlen / 2; ++i) swap(t[i], t[tlen - i + 1]);
  for (int i = 1; i <= slen; ++i) s[i] = s[i] - 'a' + 1;
  for (int i = 1; i <= tlen; ++i) t[i] = t[i] - 'a' + 1;
  while ((n = 1 << logn) and n - 1 < slen + tlen + 1) ++logn; invn = inv(n);
  for (int i = 0; i <= n - 1; ++i) {
    rev[i] = rev[i >> 1] >> 1;
    if (i & 1) rev[i] |= atbit(logn);
  }
  for (int u = 1; u <= 6; ++u)
    for (int v = 1; v <= 6; ++v) {
      if (u == v) continue;
      for (int i = 0; i <= n - 1; ++i) a[i] = s[i] == u;
      for (int i = 0; i <= n - 1; ++i) b[i] = t[i] == v;
      NTT(a, 1), NTT(b, 1); for (int i = 0; i <= n - 1; ++i)
       a[i] = mod(a[i] * b[i]); NTT(a, -1);
      for (int i = tlen + 1; i <= slen + 1; ++i) g[i][u][v] |= a[i] > 0,
       g[i][v][u] |= a[i] > 0;
    }
  
  for (int i = tlen; i <= slen; ++i) {
    for (int u = 1; u <= 6; ++u) vis[u] = 0; int ans = 0;
    for (int u = 1; u <= 6; ++u) if (not vis[u]) dfs(u, i + 1), ++ans;
    printf("%d", 6 - ans), putchar(i == slen ? '\n' : ' ');
  }
  return 0;
}
```

---

## 作者：tzc_wk (赞：1)

考虑暴力匹配两个字符串 $s,t$ 是怎样的过程：对于每个 $i$，我们在 $s_i$ 与 $t_i$ 之间连一条边，表示 $s_i$ 需要变到 $t_i$。

然后对于建好的图中的每个连通块，显然我们都可以并且必须选择某个点并将连通块中其余的点全部变成这个值。这样需要 $\text{连通块大小}-1$ 次操作。故从 $s$ 到 $t$ 的最小操作次数就是 $\sum\text{连通块大小}-1$。

于是本题思路就来了，设 $f_{i,c1,c2}$ 表示，对于 $s$ 中以 $i$ 开头的长度为 $|t|$ 的子串 $s'$，满足 $s'_i=c1,t_i=c2$ 的 $i$ 的个数。

怎样求 $f_{i,c1,c2}$？这又回到了我们前几题的套路，令 $a_i$ 表示 $s_i$ 是否等于 $c1$，$b_i$ 表示 $t_i$ 是否等于 $c2$。故 $f_{i,c1,c2}=\sum\limits_{j=0}^{|t|}a_{i+j-1}b_j$，把 $b$ 翻转一下求个卷积就行了。

然后对于每个 $i$，枚举 $f_{i,c1,c2}>0$ 的 $c1,c2$，然后跑上述操作即可。

时间复杂度 $\mathcal O(6^2n\log n)$，虽然可以过，但是显然常数上天了。这个做法需要跑 $3\times 6^2=108$ 次 DFT+IDFT。不过我们发现，可能的 $a,b$ 最多只有 $6$ 种，所以可以对每个 $c1$ 单独求一遍 $a_i$，并对这个 $a_i$ 跑一遍 DFT。$b_i$ 也是如此。这样共需 $6\times 2=12$ 次 DFT 和 $6^2=36$ 次 IDFT。还有一个小优化，就是对于 $c1=c2$，$f_{i,c1,c2}$ 显然不会对答案产生任何影响，这样可以再少跑 $6$ 次 IDFT，这样就只用跑 $42$ 次 DFT+IDFT 了。

还有为啥这题 difficulty 才 2200 啊，与它难度相当的 CF1334G 都有 2900 了。

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
	x=0;char c=getchar();T neg=1;
	while(!isdigit(c)){if(c=='-') neg=-1;c=getchar();}
	while(isdigit(c)) x=x*10+c-'0',c=getchar();
	x*=neg;
}
const int MAXN=1.25e5;
const int MAXP=1<<19;
const int AS=6;
const double Pi=acos(-1);
int n,m;char s[MAXN+5],t[MAXN+5];
struct comp{
	double x,y;
	comp(){x=y=0;}
	comp(double _x,double _y){x=_x;y=_y;}
	friend comp operator +(comp lhs,comp rhs){return comp(lhs.x+rhs.x,lhs.y+rhs.y);}
	friend comp operator -(comp lhs,comp rhs){return comp(lhs.x-rhs.x,lhs.y-rhs.y);}
	friend comp operator *(comp lhs,comp rhs){return comp(lhs.x*rhs.x-lhs.y*rhs.y,lhs.x*rhs.y+lhs.y*rhs.x);}
} A[AS+1][MAXP+5],B[AS+1][MAXP+5],C[MAXP+5];
int LEN=1,LOG=0,rev[MAXP+5];
void FFT(comp *a,int len,int type){
	int lg=log2(len);
	for(int i=0;i<len;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg-1));
	for(int i=0;i<len;i++) if(i<rev[i]) swap(a[i],a[rev[i]]);
	for(int i=2;i<=len;i<<=1){
		comp W=comp(cos(2*Pi/i),type*sin(2*Pi/i));
		for(int j=0;j<len;j+=i){
			comp w=comp(1,0);
			for(int k=0;k<(i>>1);k++,w=w*W){
				comp X=a[j+k],Y=a[(i>>1)+j+k]*w;
				a[j+k]=X+Y;a[(i>>1)+j+k]=X-Y;
			}
		}
	}
	if(type==-1) for(int i=0;i<len;i++) a[i].x=(int)(a[i].x/len+0.5);
}
bool hav[MAXN+5][AS+1][AS+1];
void solve(char c1,char c2){
	for(int i=0;i<LEN;i++) C[i]=comp(0,0);
	for(int i=0;i<LEN;i++) C[i]=A[c1-'a'][i]*B[c2-'a'][i];
	FFT(C,LEN,-1);
	for(int i=1;i<=n-m+1;i++) if(C[m+i-1].x) hav[i][c1-'a'][c2-'a']=1;
}
int f[AS+1];
int find(int x){return (f[x]==x)?x:f[x]=find(f[x]);}
int main(){
	scanf("%s%s",s+1,t+1);n=strlen(s+1);m=strlen(t+1);
	while(LEN<=n+m) LEN<<=1,LOG++;
    for(int c='a';c<='f';c++){
        for(int i=1;i<=n;i++) A[c-'a'][i].x=(s[i]==c);
        FFT(A[c-'a'],LEN,1);
    }
    for(int c='a';c<='f';c++){
        for(int i=0;i<m;i++) B[c-'a'][i].x=(t[m-i]==c);
        FFT(B[c-'a'],LEN,1);
    }
	for(char c1='a';c1<='f';c1++) for(char c2='a';c2<='f';c2++) if(c1!=c2) solve(c1,c2);
	for(int i=1;i<=n-m+1;i++){
		for(int j=0;j<AS;j++) f[j]=j;
		int sum=0;
		for(int j=0;j<AS;j++) for(int k=0;k<AS;k++) if(j!=k&&hav[i][j][k]){
			int fj=find(j),fk=find(k);if(fj!=fk) sum++,f[fj]=fk;
		}
		printf("%d ",sum);
	}
	return 0;
}
```

---

## 作者：Holy_Push (赞：1)

楼下的$FFT$题解好恐怖……我自己糊了一种**仅适合本题**的做法（字符集再大一点点就废了，$f$刚好可以）。

首先我们思考一下变换的性质。方便起见，我们记以下写法$(X,Y$均为某一个字符$)$：

$1. X<Y$表示$X$的字典序小于$Y$的字典序，如$a<b$

$2. X-Y$表示由字符$X$变换到字符$Y$。

经过一系列思考后可以发现以下性质（当然是猜想，并不会严格证明$QwQ$）

$1.$最优方案里不存在$(X_i-Y_i)(X_i-Y'_i)$。

简单地说就是，一个字符不可能被变成两个不同的字符。这很显然。

$2.$一定存在某一种最优方案，使得原字符串$S$到新字符串$T$的字符变换方案为$(X_1-Y_1),(X_2-Y_2)...(X_k-Y_k)$，且对任意$i∈[1,k],X_i<Y_i$

简单地说就是，我们只需要把小的字符往大的变，一定能找到一个最优解。（应该能感性理解）

$3.$若存在变换$(X_i-Y_i)$，则一定存在某一种最优方案，使得$(Y_i-Y'_i)$不在方案之中。

简单地说就是，存在一种最优方案，使得没有中介字符，也就是被变成过的字符不会再继续变换成另一种字符。

这一条其实很好证明，因为$(X_i-Y_i)(Y_i-Y'_i)$与$(X_i-Y'_i)(Y_i-Y'_i)$等价。遇到前面一种情况，我们可以将其转换为后面一种情况。

$4.$一定存在某一种最优方案，使得原字符串$S$到新字符串$T$的字符变换方案为$(X_1-Y_1),(X_2-Y_2)...(X_k-Y_k)$，且对任意$i∈[1,k-1],X_i<X_{i+1}$

简单地说就是，先变小的字符，再变大的字符。


然后我们可以进行$dfs$，来暴力枚举变换方案。由于有以上三种性质，并且字符集大小只有$6$，因此情况不会很多，差不多有$300$多种。

----------------------------------------
然后我们考虑怎么统计答案。我们假设现在的变换方案为$(X_1,Y_1),(X_2,Y_2)...(X_k,Y_k)$，显然$k≤5$。

我们可以利用字符串哈希的方法来匹配。每进行一次变换，我们修改一遍$S$的哈希值和$T$的哈希值，然后循环一遍进行判断，与当前这位的答案取个$min$即可。这一部分时间复杂度为$O(n)$， 但常数有点大。总的时间复杂度为$O(Tn)$，其中$T$为变换的方案数。

然而我们发现，随着字符集增大，$T$也会增大，因此此做法仅适合本题的数据范围$QwQ$（我果然太菜了）。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
const int N=2e5,p=233;

char s[N],t[N],to[10];
bool vis[10];
int ans,lens,lent,S[N],T[N],Ans[N];
ull Pow[N],Hash[N];

ull getS(int l,int r)
{
	return Hash[r]-Hash[l-1]*Pow[r-l+1];
}

void Calc()
{
	int w=0;
	for (int i=1;i<=lens;i++) S[i]=s[i-1]-'a';
	for (int i=1;i<=lent;i++) T[i]=t[i-1]-'a';
	Hash[1]=S[1];ull sum=T[1];
	for (int i=2;i<=lens;i++) Hash[i]=Hash[i-1]*p+S[i];
	for (int i=2;i<=lent;i++) sum=sum*p+T[i];
	for (int i=1;i<=lens-lent+1;i++)
		if (getS(i,i+lent-1)==sum) Ans[i]=0; //别忘了原数组
	for (char ch='a';ch<='e';ch++)
		if (to[ch-'a']>-1)
		{
			++w;
			for (int i=1;i<=lens;i++) if (S[i]==ch-'a') S[i]=to[S[i]];
			for (int i=1;i<=lent;i++) if (T[i]==ch-'a') T[i]=to[T[i]];
			Hash[1]=S[1];sum=T[1];
			for (int i=2;i<=lens;i++) Hash[i]=Hash[i-1]*p+S[i];
			for (int i=2;i<=lent;i++) sum=sum*p+T[i];
			for (int i=1;i<=lens-lent+1;i++)
				if (getS(i,i+lent-1)==sum) Ans[i]=min(Ans[i],w);
		} //每一次变换都要哈希一遍
}

void dfs(char c)
{
	if (c=='f') {Calc();return;}
	to[c-'a']=-1;dfs(c+1);
	if (vis[c-'a']) return;
	for (char ch=c+1;ch<='f';ch++)
	{
		vis[ch-'a']=true;to[c-'a']=ch-'a';
		dfs(c+1);vis[ch-'a']=false;to[c-'a']=-1;
	}
} //枚举方案

int main()
{
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	scanf("%s",&s);lens=strlen(s);
	memset(Ans,1,sizeof(Ans));
	Pow[0]=1;
	for (int i=1;i<=lens;i++) Pow[i]=Pow[i-1]*p;
	scanf("%s",&t);lent=strlen(t);
	dfs('a');
	for (int i=1;i<=lens-lent+1;i++) printf("%d ",Ans[i]);
}
```


---

## 作者：dsidsi (赞：1)

考虑如果只有两个串怎么做，肯定是从左到右扫一遍，如果某两个字符不相同，则用并查集判断是否在同一个集合里，如果不在则加入同一个集合并且答案加$1$。

考虑枚举两个不同的字符看它们是否连边。枚举两个不同的字符，将$S$中$x$字符出现的位置设为$1$，$T$中$y$字符出现的位置设为$1$。

假设在$S$的位置$a$与$T$的位置$b$均为$1$。那么意味着在两串末尾匹配到$a+|T|-b$时，字符$x$向$y$连了一条边，将$T$反转，上式转化为卷积的形式，FFT即可。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn = 125005 * 5;

int n, m;
char s[maxn], t[maxn];
int v1[maxn], v2[maxn], f[maxn][6], ans[maxn];

inline int gi()
{
	char c = getchar();
	while (c < '0' || c > '9') c = getchar();
	int sum = 0;
	while ('0' <= c && c <= '9') sum = sum * 10 + c - 48, c = getchar();
	return sum;
}

namespace FFT
{

	const double pi = acos(-1);
	typedef complex<double> cpx;
	
	int n, len, L, R[maxn];
	cpx A[maxn], B[maxn];

	void FFT(cpx *a, int f)
	{
		for (int i = 0; i < n; ++i) if (i < R[i]) swap(a[i], a[R[i]]);
		for (int i = 1; i < n; i <<= 1) {
			cpx wn(cos(pi / i), sin(f * pi / i)), t;
			for (int j = 0; j < n; j += (i << 1)) {
				cpx w(1, 0);
				for (int k = 0; k < i; ++k, w = w * wn) {
					t = a[j + i + k] * w;
					a[j + i + k] = a[j + k] - t;
					a[j + k] = a[j + k] + t;
				}
			}
		}
	}
	
	void mul(int *a, int *b, int len1, int len2, int *c)
	{
		L = 0;
		for (n = 1, len = len1 + len2 - 1; n < len; n <<= 1) ++L;
		--L;
		for (int i = 0; i < n; ++i) R[i] = (R[i >> 1] >> 1) | ((i & 1) << L);

		fill(A, A + n, 0); fill(B, B + n, 0);
		for (int i = 0; i < len1; ++i) A[i] = a[i];
		for (int i = 0; i < len2; ++i) B[i] = b[i];
		FFT(A, 1); FFT(B, 1);
		for (int i = 0; i < n; ++i) A[i] *= B[i];
		FFT(A, -1);

		for (int i = 0; i < len1; ++i) c[i] = (int)(A[i].real() / n + 0.5);
	}

}

inline int find(int *f, int x)
{
	if (f[x] == x) return x;
	return f[x] = find(f, f[x]);
}

void solve(int c1, int c2)
{
	for (int i = 0; i < n; ++i) v1[i] = s[i] == 'a' + c1;
	for (int i = 0; i < m; ++i) v2[i] = t[i] == 'a' + c2;
	reverse(v2, v2 + m);

	FFT::mul(v1, v2, n, m, v1);

	for (int i = 0; i < n; ++i) {
		if (!v1[i]) continue;
		if (find(f[i], c1) != find(f[i], c2)) f[i][f[i][c1]] = f[i][c2], ++ans[i];
	}
}

int main()
{
	freopen("string.in", "r", stdin);
	freopen("string.out", "w", stdout);

	scanf("%s\n", s); n = strlen(s);
	scanf("%s\n", t); m = strlen(t);
	
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < 6; ++j) f[i][j] = j;

	for (int i = 0; i < 6; ++i)
		for (int j = 0; j < 6; ++j) {
			if (i == j) continue;
			solve(i, j);
		}
			
	for (int i = m - 1; i < n; ++i) printf("%d ", ans[i]);
	puts("");
	
	return 0;
}
```

---

## 作者：wcyQwQ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF954I)

[可能更好的阅读体验](https://chenyu-w.github.io./2023/02/12/CF954I%20Yet%20Another%20String%20Matching%20Problem/)

你管这叫 *2200？


## 前言

首先考虑答案实质上是什么，对每种字符分别建一个点，然后在有冲突(即相同位置)的字符之间连边，那么我们改变一个连通块要变换连通块大小 $-1$ 次，然后我们把所有连通块求和即可，我们发现这个次数等于并查集的合并次数，所以我们只需要求出那些字符之间有边即可。

记 $g_{i, j, k}$ 表示在区间 $[i, i + |t| - 1]$ 字符 $j, k$ 是否产生冲突，即 $\exists x \in [1, |t|], s_{i + x - 1} = j, t_x = k$，然后我们记 $a_i$ 表示 $s_i$ 是否为 $j$，$b_i$ 为 $t_i$ 是否为 $k$，朴素转移得到 $g_{i, j, k} = \sum_{x = 1}^{|t|} a_{i + x - 1}b_{x}$，然后我们让 $b_i \leftarrow b_{|t| - i + 1}$，这样就原式就变为了一个卷积的形式，所以我们可以枚举 $j, k$ 然后用 $O(n \log n)$ 的复杂度计算 $g_{i, j, k}$，最后用并查集统计一下答案即可。

## 代码

```c++
#include <bits/stdc++.h>
#define L(i, j, k) for(int i = (j); i <= (k); i++)
#define R(i, j, k) for(int i = (j); i >= (k); i--)
#define G(i, u) for (int i = h[(u)]; ~i; i = ne[i])
#define ll long long
#define ld long double
#define ull unsigned long long

using namespace std;
const int N = 7e5 + 10, mod = 998244353, G = 3;
char s[N], t[N];
int rev[N], a[N], b[N];
bool has[N][6][6];
int p[6];

inline int read() {
    int x = 0, y = 1; char c = getchar();
    while (c < '0' || c > '9') {if (c == '-') y = -1; c = getchar();}
    while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * y;
}

inline int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = 1ll * res * a % mod;
        a = 1ll * a * a % mod;
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
                int x = a[j], y = 1ll * w * a[j + mid] % mod;
                a[j] = (x + y) % mod, a[j + mid] = (x - y + mod) % mod;
                w = 1ll * w * W % mod;
            }
        }
    } 
}

inline void NTT(int n, int m, int a[], int b[]) {
    int k = 1, l = 0;
    while (k <= n + m) k <<= 1, l++;
    L(i, 0, k - 1) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (l - 1));
    ntt(a, k, 1), ntt(b, k, 1);
    L(i, 0, k - 1) a[i] = 1ll * a[i] * b[i] % mod;
    ntt(a, k, -1);
    int invk = qpow(k, mod - 2);
    L(i, 0, n + m) a[i] = 1ll * a[i] * invk % mod; 
}

inline int find(int x) {
    return x == p[x] ? x : p[x] = find(p[x]);
}

int main() {
    scanf("%s%s", s + 1, t + 1);
    int n = strlen(s + 1), m = strlen(t + 1);
    L(i, 0, 5) L(j, 0, 5) {
        if (i == j) continue;
        memset(a, 0, sizeof a);
        memset(b, 0, sizeof b);
        L(k, 1, n) a[k] = s[k] - 'a' == i;
        L(k, 1, m) b[m - k + 1] = t[k] - 'a' == j;
        NTT(n, m, a, b);
        L(k, 1, n - m + 1) has[k][i][j] = a[k + m];
    }
    L(i, 1, n - m + 1) {
        int res = 0;
        L(j, 0, 5) p[j] = j;
        L(j, 0, 5) L(k, 0, 5) {
            if (j == k || !has[i][j][k]) continue;
            int pj = find(j), pk = find(k);
            if (pj == pk) continue;
            res++, p[pj] = pk;
        }
        printf("%d ", res);
    }
    return 0;
}
```

---

## 作者：Taduro (赞：0)

先假装证明一下贪心的正确性，如果一个位置两个串颜色不一样，那么我们迟早要有一个操作把这两种字符变成同一种。不然就要借助第三种颜色变两次，所以一定没有比这种贪心更优的方法。

然后对于每个位置属于$x\in [0,n-m]$，我只要知道它后面m个字符中有没有颜色p，q对应（即有一个位置i，$a_i=p,b_{i+x-1}=q$），就可以确定要不要把颜色p,q合并起来（如果p和q之前没有被合并的话，用并查集维护一下），进而也可以算出在x位置的答案。

那么我只要求出$[x,x+m-1]$中有没有颜色p，q的对应就好了。

这个可以用多项式乘法做，枚举p，q，将a中p出现的位置赋成1（多项式a），b中q出现的位置赋成1（多项式b），将多项式a翻转后和多项式b乘起来即可，这是FFT解决字符串匹配问题的套路。

```c++
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#define maxn 500000
using namespace std;
const double Pi=acos(-1.0);
struct complex{
	double x,y;
	complex (double xx=0,double yy=0){x=xx,y=yy;}
}a[maxn],b[maxn],c[maxn];
int fa[7],n,m,lim,r[maxn],e[maxn][6][6],l,ans;
char ch1[maxn],ch2[maxn];
complex operator + (complex a,complex b){return complex(a.x+b.x,a.y+b.y);}
complex operator - (complex a,complex b){return complex(a.x-b.x,a.y-b.y);}
complex operator * (complex a,complex b){return complex(a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x);}
inline void FFT(complex *a,int inv){
	for (int i=0; i<lim; i++)
		if (i<r[i]) swap(a[i],a[r[i]]);
	for (int i=1; i<lim; i<<=1){
		complex wn(cos(Pi/i),inv*sin(Pi/i));
		for (int j=0; j<lim; j+=(i<<1)){
			complex w(1,0);
			for (int k=0; k<i; k++,w=w*wn){
				complex x=a[j+k],y=w*a[j+i+k];
				a[j+k]=x+y; a[i+j+k]=x-y;
			}
		}
	}
}
int find(int x){
	if (fa[x]!=x) fa[x]=find(fa[x]);
	return fa[x];
}
int main(){
	scanf("%s",ch1); n=strlen(ch1);
	scanf("%s",ch2); m=strlen(ch2);
	lim=1; while (lim<=n+m) lim<<=1,l++;
	for (int i=0; i<lim; i++)
		r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
	for (int p=0; p<6; p++)
	for (int q=0; q<6; q++){
		if (p==q) continue;
		for (int i=0; i<lim; i++) a[i]=b[i]=complex(0,0);
		for (int i=0; i<m; i++) a[m-1-i].x=(ch2[i]==p+'a');
		for (int i=0; i<n; i++) b[i].x=(ch1[i]==q+'a');
		FFT(a,1); FFT(b,1);
		for (int i=0; i<=lim; i++) c[i]=a[i]*b[i];
		FFT(c,-1);
//		printf("\n%d %d\n",p,q);
		for (int i=m-1; i<n; i++){
			e[i-m+1][p][q]=(int)(c[i].x/lim+0.5);
//			printf("%d ",e[i-m+1][p][q]);
		}
	}
	for (int k=0; k<=n-m; k++){
		for (int i=0; i<6; i++) fa[i]=i;
		ans=0;
		for (int p=0; p<6; p++)
			for (int q=0; q<6; q++){
				if (p==q) continue;
				// printf("k:%d p:%d q:%d %d\n",k,p,q,e[k][p][q]);
				if (!e[k][p][q]) continue;
				int x=find(p),y=find(q);
				if (x!=y) fa[x]=y,ans++;
			}
		// for (int i=0; i<6; i++)
			// if (find(i)!=i) ans++;
		printf("%d ",ans);
	}
	return 0;
}
```



---

## 作者：namespace_std (赞：0)

提供一个稍微简单的思路：

由于字符集大小很小，我们可以枚举将哪些字符视为同一种。

这相当于**枚举子集**，方案数上限为3^6=729，实测为共203种合法子集。

之后将字符串中视为同一种的字符整体替换并用KMP或者蛤希更新答案。

复杂度为203次KMP或Hash的单模式串匹配，即O(203*(|S|+|T|))，大约为O(3e7)。

实测目前谷内最快（单点156ms）。

~~不用写FFT了QaQ~~

以下为代码：
```cpp
#include<cstdio>
typedef unsigned long long ull;
const ull bas=283476131;
ull hash[222222],k[222222];
char str[222222],ttt[222222];               //S、T
char ref[2222];                             //ref[c]表示字符c被替换成的字符
int best[222222];   
inline ull gethash(int l,int r)             //Hash
{return hash[r]-hash[l-1]*k[r-l+1];}
int a[11];
int cnt,l,ls;
inline void exec(int dep)
{
	int k=7-dep;
	register int i;
	for(i=1;i<=6;i++)ref[i+96]=a[i]+96;
	for(i=1;str[i];i++)
		hash[i]=hash[i-1]*bas+ref[str[i]];  //替换后的字符串S (即ref[str[i]])
	l=i-1;
	ull key=0;
	for(i=1;ttt[i];i++)
		(key*=bas)+=ref[ttt[i]];            //替换后的字符串T (即ref[ttt[i]])
	ls=i-1;
	for(i=1;i+ls-1<=l;i++)
		if(key==gethash(i,i+ls-1))
			if(best[i]>k)best[i]=k;         //更新答案（如果替换后匹配）
			
}
void dfs(int dep=1,int beg=1)               //枚举子集（写得很丑）
{
	if(beg>6)
	{exec(dep);return;}
	a[beg]=dep;
	int b[11];
	register int i,ii;
	for(i=1;i<=6;i++)b[i]=a[i];
	for(i=0;i<(1<<6);i++)
	{
		for(ii=1;ii<=beg;ii++)
			if(i&(1<<(ii-1)))goto T;
		for(ii=beg+1;ii<=6;ii++)
			if(i&(1<<(ii-1)))
				if(a[ii])goto T;
		for(ii=beg+1;ii<=6;ii++)
			if(i&(1<<(ii-1)))
				a[ii]=dep;
		for(ii=beg+1;ii<=7;ii++)
			if(!a[ii])break;
		dfs(dep+1,ii);
		for(ii=1;ii<=6;ii++)a[ii]=b[ii];
		T:;
	}
}
int main()
{
	scanf("%s%s",str+1,ttt+1);
	register int i;
	for(i=1;i<=125555;i++)best[i]=5;
	k[0]=1;
	for(i=1;i<=125555;i++)k[i]=k[i-1]*bas;
	dfs();
	for(i=1;i+ls-1<=l;i++)
		printf("%d%c",best[i],(l^(i+ls-1))?' ':'\n');
}
```

---

