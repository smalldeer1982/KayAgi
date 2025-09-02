# Fuzzy Search

## 题目描述

给出一个门限值 $k$ 和两个只包含 $\texttt{AGCT}$ 四种字符的基因串 $S$ 和 $T$。现在你要找出在下列规则中 $T$ 在 $S$ 中出现了几次。 

$T$ 在 $S$ 的第 $i$ 个位置中出现，当且仅当把 $T$ 的首字符和 $S$ 的第 $i$ 个字符对齐后，$T$ 中的每一个字符能够在 $S$ 中找到一个位置偏差不超过 $k$ 的相同字符。

即对于所有的 $j \in[1,|T|]$，都存在一个 $p \in [1,|S|]$ 使得 $|(i+j-1)-p| \leq k$ 且 $S_p=T_j$ 。 

例如 $k=1$ 时，$\texttt{ACAT}$ 出现在 $\texttt{AGCAATTCAT}$ 的 $2$ 号， $3$ 号和 $6$ 号位置。 (编号从 $1$ 开始。)

## 说明/提示

$1≤m≤n≤2\times 10^5\ ,\ 0≤k≤2\times 10^5$。

## 样例 #1

### 输入

```
10 4 1
AGCAATTCAT
ACAT
```

### 输出

```
3
```

# 题解

## 作者：封禁用户 (赞：21)

标算FFT?不会FFT的蒟蒻来讲一种比较暴力的方法。

首先，对于四种字母处理出可以匹配到的范围,即i-k至i+k,使用差分可以在O(n)之内求出来。然后，我们就得到了4个长度为n的01串，对于匹配串的i位右移i位后全部&起来，最后1的个数即为答案。

听上去是个不错的注意，但是时间复杂度O(nm)，4*10^10，很明显会TLE。

没事，使用bitset让时间/32即可通过本题。

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200005;
int mp[200],a[N][4];
bitset<N> bs[4],ans;
int main()
{
	ios::sync_with_stdio(false);
	int n,m,k;
	string s,t;
	cin>>n>>m>>k>>s>>t;
	mp['A']=0,mp['C']=1,mp['G']=2,mp['T']=3;
	for(int i=0;i<n;i++)
	{
		a[max(0,i-k)][mp[s[i]]]++;
		a[min(n,i+k+1)][mp[s[i]]]--;
	}
	for(int i=0;i<n;i++)
	{
		ans[i]=1;
		for(int j=0;j<4;j++)
		{
			if(i)
				a[i][j]+=a[i-1][j];
			if(a[i][j])	
				bs[j][i]=1;
			else
				bs[j][i]=0;
		}
	}
	for(int i=0;i<m;i++)
		ans&=(bs[mp[t[i]]]>>i);
	int sum=0;
	for(int i=0;i<n;i++)
		sum+=(ans[i]==1);
	printf("%d\n",sum);
	return 0;
}

```


---

## 作者：Sooke (赞：18)

### 解题思路

先想最简单的情况 $k = 0$，这正是最经典的[字符串匹配](https://www.luogu.org/problemnew/show/P3375)问题，可用 $KMP$ 等算法 $O(n)$ 解决。

但咱今天的主角，是多项式乘法，我们尝试用它解决这一情况。

考虑成功匹配时的性质，模式串上的每个字符，与匹配的对应字符，位置的**差**是相等的。

考虑多项式乘法的性质，通过卷积得到的新多项式，每一项的系数与原多项式两个次数之**和**相等的项有关。

性质都很明显，怎么联系上呢？

很简单，只需给模式串翻个转儿，不就和卷积是一样的东西了？

设答案多项式 $A(x) = \sum\limits_{i=m-1}^{n} x^i\sum\limits_{j=0}^{m-1}(s_{i-j}-t_{j})^2$。

意义应该不难看出，$i$ 是匹配的起始位置，$j$ 是当前已经匹配的字符数量。而这个平方，就是让每一项的系数非负，只有系数 $= 0$ 时，才表示成功匹配。

$$A(x) = \sum_{i=m-1}^{n} x^i\sum_{j=0}^{m-1}s_{i-j}^2 + t_{j}^ 2 - 2s_{i-j}t_{j}$$

其中，只跟 $i-j$ 或 $j$ 有关的项，可以提取出来单独计算，其他的，正是卷积形式了，$FFT$、$NTT$ 随便上。整体复杂度是 $O(n \log n)$ 的，稍逊 $KMP$，但好处在于，它能推广到 $k > 0$ 的一般情况，甚至能应对出题人的更多毒瘤变幻。

---

回到 $k > 0$ 的一般情况，发现题目还有一个性质，字母只有 $4$ 种。

这其实暗示着我们可以按照字母种类分 $4$ 种情况分别处理，换句话说，可以对于每种字母处理其成功匹配的数量，最后加在一起。举个例子：

$$S="AACCATGTA"$$

$$T="ACCA"$$

假如我们正在做 $A$ 这个字母，我们可以假装替换了其他字母：

$$S="AA\#\#\#\#\#\#A"$$

$$T="A\%\%A"$$

貌似 $k$ 还没用上？其实我们可以把 $k$ 理解为 $S$ 串中的字母向两边扩散的距离，即 $k = 1$ 时：

$$S="AAA\#\#\#\#AA"$$

$$T="A\%\%A"$$

以上只要顺着扫一遍，再逆着扫一遍，就可以做到。

最后，仍然是构造多项式，因为每次被匹配的字母只有一种，构造可以简化。

由于只有两边都是当前匹配的字母时，才对答案多项式某一项的系数有 $1$ 的贡献，否则贡献为 $0$。

$$A \times A = 1,\ \# \times A = 0,\ A \times \% = 0,\ \# \times \% = 0$$

显然，将 $S$ 串扩散操作后，构造 $F(x) = \sum\limits_{i=0}^{n}x^i[S_{i} \text{是当前匹配的字母}]$，将 $T$ 串翻转操作后，$G(x) = \sum\limits_{i=0}^{n}x^i[T_i\text{是当前匹配的字母}]$，利用刚才讲的卷积的性质，令 $A(x)\ \text{+=}\ F(x)\ast G(x)$
即可。

最后的最后，对于得出来的 $A(x)$，因为只有全部 $m$ 个字母匹配才行，每个系数为 $m$ 的项对答案有 $1$ 的贡献。

---

### 代码实现

下面用的是 $NTT$，当然 $FFT$ 也是可做的。我可能写得比较丑……

```cpp
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>

inline int power(int x, int y, int p) { int res = 1; for (; y; y >>= 1, x = 1ll * x * x % p) { if (y & 1) { res = 1ll * res * x % p; } } return res; }

const int maxN = 530000;

struct Poly {
    int n, p, g, invG, a[maxN];

    Poly() { p = 119 << 23 | 1; g = 3; invG = (p + 1) / g; }
    void ntt(int lim, int rev[], int sgn) {
        for (int i = 0; i < lim; i++) { if (i < rev[i]) { std::swap(a[i], a[rev[i]]); } }
        for (int len = 1, logLen = 1; len < lim; len <<= 1, logLen++) {
            int uni = power(sgn == 1 ? g : invG, (p + 1) >> logLen, p);
            for (int i = 0, w = 1; i < lim; i += len << 1, w = 1) {
                for (int j = 0; j < len; j++, w = 1ll * w * uni % p) { int x = 1ll * a[i + j + len] * w % p; a[i + j + len] = (a[i + j] + p - x) % p; (a[i + j] += x) %= p; }
            }
        }
        if (!~sgn) { for (int i = 0, invLim = power(lim, p - 2, p); i < lim; i++) { a[i] = 1ll * a[i] * invLim % p; } }
    }
} tmp1, tmp2, tmp3; int rev[maxN];
void mul(const Poly &f, const Poly &g, Poly &res) {
    int lim = 1, cnt = 0; while (lim <= f.n + g.n - 2) { lim <<= 1; cnt++; }
    for (int i = 1; i < lim; i++) { rev[i] = rev[i >> 1] >> 1 | (i & 1) << cnt - 1; }
    tmp1.n = f.n; memcpy(tmp1.a, f.a, sizeof(int) * lim); tmp1.ntt(lim, rev, 1);
    tmp2.n = g.n; memcpy(tmp2.a, g.a, sizeof(int) * lim); tmp2.ntt(lim, rev, 1);
    for (int i = 0; i < lim; i++) { res.a[i] = 1ll * tmp1.a[i] * tmp2.a[i] % f.p; }
    res.n = f.n + g.n - 1; res.ntt(lim, rev, -1);
}
Poly operator *(const Poly &f, const Poly &g) { memset(tmp3.a, 0, sizeof(tmp3.a)); mul(f, g, tmp3); return tmp3; }

// ------------------------------------- 上面都是板子 ------------------------------------- //

int n, m, k, ans, cnt[maxN];
std::string s, t;
Poly f, g;

void solve(char c) {
    f.n = n; g.n = m; memset(f.a, 0, sizeof(f.a)); memset(g.a, 0, sizeof(g.a)); // 先清空, 防止出锅.
    // --------------------------------- 处理多项式 f ------------------------------------- //
    for (int i = 0, lst = -1e9; i < n; i++) {
        if (s[i] == c) { lst = i; } // 找左边最近的当前字母 c.
        if (i - lst <= k) { f.a[i] = 1; } // 如果距离合法, 则设 1.
    }
    for (int i = n - 1, lst = 1e9; ~i; i--) {
        if (s[i] == c) { lst = i; } // 找右边最近的当前字母 c.
        if (lst - i <= k) { f.a[i] = 1; } // 如果距离合法, 则设 1.
    }
    // --------------------------------- 处理多项式 g ------------------------------------- //
    for (int i = 0; i < m; i++) { g.a[i] = t[m - 1 - i] == c; } // 翻转一下模式串就好了.
    // --------------------------------- 卷积累加贡献 ------------------------------------- //
    f = f * g; for (int i = 0; i < f.n; i++) { cnt[i] += f.a[i]; }
}

int main() {
    std::cin >> n >> m >> k >> s >> t;
    for (int i = 0; i <= 3; i++) { solve("ACTG"[i]); } // 分别计算每个字母对匹配的贡献.
    for (int i = 0; i <= n + m - 2; i++) { ans += cnt[i] == m; } // 全匹配 m 个字母.
    std::cout << ans << std::endl;
    return 0;
}
```

---

## 作者：huayucaiji (赞：6)

## 前言

这个方法不对劲，但是是对的qwq。

我一直在想为什么是 `A,C,G,T` 四个字符。现在我想通了。这场 CF 大概是 ATcoder 的 AGC 出题人出的（大雾）

## 解法

首先我们要考虑 $k=0$ 的时候怎么做。直接 KMP 即可。

但是这样我们没法做 $k>0$ 的情况。我们考虑用 `FFT/NTT`。

容易发现题中只有 $4$ 中字符。我们考虑一个一个处理。假设对于样例，我们先处理 `A` 字符。

那么我们有：

$$S=A**AA***A*\\T=A*A*$$

其中 `*` 是通配符，可以为任意字符。

那么怎么处理 $k$ 呢？

我们容易想到，可以把一个原来是 `A` 的位置往两旁延伸 $k$ 个位置，把它们都置为 `A`。这样 $k$ 就没有影响啦。

举个例子，对于样例我们就有：

$$S'=AAAAAA*AAA\\T=A*A*$$

为了方便计算，我们可以认为：

$$S'=1111110111\\T=1010$$

把 $S'$ 和 $T$ 转化为多项式 $f,g$，那么什么情况下在 $i$ 的位置珂以成功匹配呢？

如果我们有：

$$h_i=\sum\limits_{j=1}^{|T|} g_j\cdot(f_{i+j}-g_{j})^2$$

当 $h_i$ 为 $0$ 时，在 $i$ 上可以匹配。

怎样快速求出 $h_i$ 呢？展开得：

$$h_i=\sum\limits_{j=1}^{|T|} g_j\cdot {f_{i+j}}^2+{g_j}^3-2\cdot {g_j}^2\cdot f_{i+j}$$

我的第一反应是：完了，处理不了。

仔细一想，其实是对的。

由于 $g,f$ 每一项的取值为 $0$ 或 $1$，所以每个平方或者三次方项都可以消成一次项，不影响计算，因此转化为:

$$h_i=\sum\limits_{j=1}^{|T|} g_j\cdot {f_{i+j}}+{g_j}-2\cdot {g_j}\cdot f_{i+j}\\h_i=\sum\limits_{j=1}^{|T|} {g_j}-{g_j}\cdot f_{i+j}$$

将 $g$ 翻转就可以求卷积了。

最后四个字符分别处理对应的 $h_i$，都为 $0$ 则这个位置可以匹配。

## 代码

```cpp
//Don't act like a loser.
//This code is written by huayucaiji
//You can only use the code for studying or finding mistakes
//Or,you'll be punished by Sakyamuni!!!
#include<bits/stdc++.h>
#define int long long
using namespace std;

int read() {
	char ch=getchar();
	int f=1,x=0;
	while(ch<'0'||ch>'9') {
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f*x;
}

const int MAXN=4e6+10;
const int G=3;
const int MOD=998244353;

int n,m,k;
int d=1,bit=0;
short index[30];
int s[MAXN],t[MAXN],f[MAXN],g[MAXN],r[MAXN],ans[MAXN];

int qpow(int x,int y) {
	int ret=1;
	while(y) {
		if(y&1) {
			ret=x*ret%MOD;
		}
		y>>=1;
		x=x*x%MOD;
	}
	return ret;
}

void NTT(int A[],int d,int inv) {
	for(int i=0;i<d;i++) {
		if(i<r[i]) {
			swap(A[i],A[r[i]]);
		}
	}
	
	for(int len=1;len<d;len<<=1) {
		int gn=qpow(G,(MOD-1)/(len*2));
		for(int i=0;i<d;i+=len<<1) {
			int g=1;
			for(int k=0;k<len;k++,g=g*gn%MOD) {
				int x=A[i+k];
				int y=g*A[i+k+len]%MOD;
				A[i+k]=(x+y)%MOD;
				A[i+k+len]=(x-y+MOD)%MOD;
			}
		}
	}
	
	if(inv==-1) {
		reverse(A+1,A+d);
		int g=qpow(d,MOD-2);
		for(int i=0;i<d;i++) {
			A[i]=A[i]*g%MOD;
		}
	}
}

void FFT_KMP() {
	int cst=0;
	for(int i=0;i<m;i++) {
		cst+=g[i];
	}
	reverse(g,g+m);
	NTT(f,d,1);
	NTT(g,d,1);
	for(int i=0;i<d;i++) {
		f[i]=f[i]*g[i]%MOD;
	}
	NTT(f,d,-1);
	for(int i=0;i<n;i++) {
		ans[i]+=f[m+i-1]+cst-2*f[m+i-1];
	}
}

signed main() {
	index['A'-'A']=1;index['C'-'A']=2;index['G'-'A']=3;index['T'-'A']=4;
	n=read();m=read();k=read();
	
	for(int i=0;i<n;i++) {
		char c;
		cin>>c;
		s[i]=index[c-'A'];
	}
	for(int i=0;i<m;i++) {
		char c;
		cin>>c;
		t[i]=index[c-'A'];
	}
	
	while(d<=n+m) {
		d<<=1;
		bit++;
	}
	for(int i=0;i<d;i++) {
		r[i]=(r[i>>1]>>1)|((i&1)<<(bit-1));
	}
	
	for(int j=1;j<=4;j++) {
		fill(f,f+d,0);
		fill(g,g+d,0);
		int p=0;
		for(int i=0;i<n;i++) {
			if(s[i]==j) {
				p=k+1;
			}
			if(p) {
				f[i]=1;
				p--;
			}
		}
		for(int i=n-1;i>=0;i--) {
			if(s[i]==j) {
				p=k+1;
			}
			if(p) {
				f[i]=1;
				p--;
			}
		}
		for(int i=0;i<m;i++) {
			if(t[i]==j) {
				g[i]=1;
			}
		}
		FFT_KMP();
	}
	
	int tot=0;
	for(int i=0;i<n;i++) {
		tot+=(ans[i]==0? 1:0);
	}
	cout<<tot<<endl;
	
	return 0;
}
```

---

## 作者：tzc_wk (赞：5)

$FFT$

首先，我们预处理出第 $i$ 个位置上是否可以放字符 $c$，记为 $b_{j,c}$。这个随便乱搞都可以实现，这里就不赘述了。

按照老套路，我们还是把 $s$ 看成一个多项式 $\sum_{i=0}^{n-1}s(i) \times x^i$，把 $t$ 也看成一个多项式 $\sum_{i=0}^{m-1}t(i) \times x^i$我们定义 $P(x)$ 为 $s$ 中以 $x$ 结尾的长度为 $m$ 的字符串与 $t$ 成功匹配的字符数量。如果 $P(x)=m$ 那么代表成功匹配。写出 $P(x)$ 的表达式：$P(x)=\sum_{t_i=A}b_{x-m+i+1,A}+\sum_{t_i=C}b_{x-m+i+1,C}+\sum_{t_i=G}b_{x-m+i+1,G}+\sum_{t_i=T}b_{x-m+i+1,T}+$，我们发现这四项形式相同，求的方式肯定也相同，就以第一项为例。接下来一步是关键：我们建立一个 $d$ 数组，将字符串 $t$ 中所有 $t_i=A$ 的地方都赋上 $d_i=1$，其它地方赋上 $d_i=0$，那么原来那个式子的第一项又可以改成 $\sum_{i=0}^{m-1}b_{x-m+i+1,A} \times d_i$。我们将 $t$ 字符串翻转一下，那么原来的 $d_i$ 就变为了 $d_{m-1-i}$，这个式子又变为了 $\sum_{i=0}^{m-1}b_{x-m+i+1,A} \times d_{m-1-i}$，由于 $(m-1-i)+(x-m+i+1)=x$，这个式子可以改写成卷积的形式 $\sum_{i+j=x}b_{i,A} \times d_j$，用 $FFT$ 求出来就行了。另外三项也同理。最后判断是否等于 $m$。

```cpp
/*
数据不清空，爆零两行泪。
多测不读完，爆零两行泪。
边界不特判，爆零两行泪。
贪心不证明，爆零两行泪。
D P 顺序错，爆零两行泪。
大小少等号，爆零两行泪。
变量不统一，爆零两行泪。
越界不判断，爆零两行泪。
调试不注释，爆零两行泪。
溢出不 l l，爆零两行泪。
*/
#include <bits/stdc++.h>
using namespace std;
#define fi			first
#define se			second
#define fz(i,a,b)	for(int i=a;i<=b;i++)
#define fd(i,a,b)	for(int i=a;i>=b;i--)
#define foreach(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define put(x)		putchar(x)
#define eoln        put('\n')
#define space		put(' ')
inline int read(){
	int x=0,neg=1;char c=getchar();
	while(!isdigit(c)){
		if(c=='-')	neg=-1;
		c=getchar();
	}
	while(isdigit(c))	x=x*10+c-'0',c=getchar();
	return x*neg;
}
inline void print(int x){
	if(x<0){
		putchar('-');
		print(abs(x));
		return;
	}
	if(x<=9)	putchar(x+'0');
	else{
		print(x/10);
		putchar(x%10+'0');
	}
}
const double Pi=acos(-1.0);
struct comp{
	double x,y;
	comp(){x=y=0;}
	comp(double a,double b){x=a;y=b;}
	inline comp operator +(comp c){return comp(x+c.x,y+c.y);}
	inline comp operator -(comp c){return comp(x-c.x,y-c.y);}
	inline comp operator *(comp c){return comp(x*c.x-y*c.y,x*c.y+y*c.x);}
} a[1<<20],b[1<<20],p[1<<20];
int rev[1<<20];
inline void FFT(int len,comp* a,int type){
	for(int i=0;i<len;i++){
		if(i<rev[i])	swap(a[i],a[rev[i]]);
	}
	for(int mid=1;mid<len;mid<<=1){
		comp W(cos(Pi/mid),type*sin(Pi/mid));
		for(int j=0;j<len;j+=mid<<1){
			comp w(1,0);
			for(int k=0;k<mid;k++){
				comp x=a[j+k],y=w*a[j+mid+k];
				a[j+k]=x+y;
				a[j+mid+k]=x-y;
				w=w*W;
			}
		}
	}
}
int N=1,n=read(),m=read(),k=read();
char s[200005],t[200005];
int cnt[1<<20];
inline void go(char c){
	int lst=-1e9;
	for(int i=0;i<N;i++)	a[i]=comp(0,0),b[i]=comp(0,0);
	fz(i,0,n-1){
		if(s[i]==c)	lst=i;
		if((i-lst)<=k)	a[i]=comp(1,0);
	}
	lst=1e9;
	fd(i,n-1,0){
		if(s[i]==c)	lst=i;
		if((lst-i)<=k)	a[i]=comp(1,0);
	}
	fz(i,0,m-1){
		if(t[i]==c){
			b[m-i-1]=comp(1,0);
		}
	}
	FFT(N,a,1);
	FFT(N,b,1);
	for(int i=0;i<N;i++)	a[i]=a[i]*b[i];
	FFT(N,a,-1);
	for(int i=0;i<n;i++)	cnt[i]+=int(a[i].x/N+0.5);
}
int main(){
	cin>>s>>t;
	int num=0;
	while(N<=n+m)	N<<=1,num++;
	for(int i=0;i<N;i++)	rev[i]=(rev[i>>1]>>1)|((i&1)<<(num-1));
	int ans=0;
	go('A');go('C');go('G');go('T');
	fz(i,0,n-1)	if(cnt[i]==m)	ans++;
	print(ans);
	return 0;
}
```

---

## 作者：ljc1301 (赞：5)

因为FFT可以处理含有通配符的字符串匹配问题（[P4173](https://www.luogu.org/problemnew/show/P4173)），可以考虑用FFT做这一题。

因为字母个数只有4，考虑每个字母分开做，令当且考虑的字母为ch。如果对于某个位置，四个字母都能匹配，那答案+1。

字符串T放在S的某个位置匹配不上当且仅当，存在一个位置，这个位置上T为ch，而S前后k个都不为ch（这个怎么判都行，我用的是记录前i个有多少个ch，相当于前缀和）。

那么我们记g\[i]=\[T\[i]==ch]，f\[i]=\[S\[i]前后k个都不为ch]

拿样例举个例子。假设ch='C'，则
```
f = 1 0 0 0 1 1 0 0 0 1
g = 0 1 0 0
```
把T的最左边放到S的第p个是可以的，当且仅当$\sum\limits_{i=0}^{m-1}f[i+p]g[i]=0$，也就是没有一个位置满足前面说的这两个条件。然后把g反过来就是卷积的形式了。

（说个小技巧，把g反过来后可以放最后，就是说若FFT的长度是l，则反转前的第i个放到第l-i-1个，当作第-i项，这样卷积后就能方便点知道卷到哪了）

（再提一点，含有通配符的字符串匹配问题就是构造$(a-b)^2ab$的形式，把通配符当作0，其余字符当作它-'a'+1，因为这个式子是非负的，可以看卷积后是不是0）

代码还算比较好写：
``` cpp
#include <bits/stdc++.h>
using namespace std;
const int maxlogn=19;
const int maxn=(1<<maxlogn)|1;
const int kcz=998244353;
typedef long long ll;
namespace polynomial
{
    ll G[2][23+1];
    int rev[maxn];
    inline ll qpow(ll a,int k)
    {
        ll res=1;
        while(k)
        {
            if(k&1) res=res*a%kcz;
            k>>=1;
            if(k) a=a*a%kcz;
        }
        return res;
    }
    #define inv(x) qpow(x,kcz-2)
    void init()
    {
        int i;
        G[1][23]=inv(G[0][23]=qpow(3,(kcz-1)>>23));
        assert(G[0][23]*G[1][23]%kcz==1);
        for(i=23-1;i>=0;i--)
        {
            G[0][i]=G[0][i+1]*G[0][i+1]%kcz;
            G[1][i]=G[1][i+1]*G[1][i+1]%kcz;
        }
        assert(G[0][0]==1),assert(G[1][0]==1);
        assert(G[0][1]==kcz-1),assert(G[1][1]==kcz-1);
    }
    inline void calcrev(int logn)
    {
        register int i;
        rev[0]=0;
        for(i=1;i<(1<<logn);i++)
            rev[i]=(rev[i>>1]>>1)|((i&1)<<(logn-1));
    }
    inline void DFT(ll *a,int logn,int flag) // O(nlogn)
    {
        register int i,j,k,mid;
        register ll t1,t2,t;
        for(i=0;i<(1<<logn);i++)
            if(rev[i]<i)
                swap(a[rev[i]],a[i]);
        for(i=1;i<=logn;i++)
            for(mid=1<<(i-1),j=0;j<(1<<logn);j+=1<<i)
                for(k=0,t=1;k<mid;k++,t=t*G[flag][i]%kcz)
                {
                    t1=a[j|k],t2=t*a[j|k|mid];
                    a[j|k]=(t1+t2)%kcz,a[j|k|mid]=(t1-t2)%kcz;
                }
    }
}

using polynomial::init;
using polynomial::calcrev;
using polynomial::DFT;
using polynomial::qpow;
const char *temp="ATGC";
ll f[maxn],g[maxn];
int n,m,k,pre[maxn],tot,logn;
char s[maxn],t[maxn];
bool ans[maxn];
inline void solve(char ch)
{
    int i;
    for(pre[0]=0,i=1;i<=n;i++)
        pre[i]=pre[i-1]+(s[i]==ch);
    memset(f,0,sizeof(ll)<<logn);
    memset(g,0,sizeof(ll)<<logn);
    for(i=0;i<m;i++)
        g[(1<<logn)-1-i]=t[i]==ch;
    for(i=1;i<=n;i++)
        f[i]=pre[min(i+k,n)]-pre[max(i-k-1,0)]==0;
    DFT(f,logn,0),DFT(g,logn,0);
    for(i=0;i<(1<<logn);i++) f[i]=f[i]*g[i]%kcz;
    DFT(f,logn,1);
    for(i=0;i<n-m+1;i++)
        ans[i]&=!f[i]; //因为只用判断是不是0，本来还要除2^logn的，偷懒了
}
int main()
{
    int i;
    init();
    scanf("%d%d%d%s%s",&n,&m,&k,s+1,t);
    for(logn=0;(1<<logn)<=n+m;logn++);
    calcrev(logn);
    for(i=0;i<n-m+1;i++)
        ans[i]=1;
    for(i=0;temp[i];i++)
        solve(temp[i]);
    for(tot=0,i=0;i<n-m+1;i++)
        tot+=ans[i];
    printf("%d\n",tot);
    return 0;
}
```

---

## 作者：zerolt (赞：3)

对于每个字符$c$,令$a[i]=[S_i$能匹配$c]$，$b[i]=[T_i == c]$  ,
贡献$f[j]=\sum_{i=0}^{m-1}a[j+i]*b[i]$，当总贡献为$m$时$j$位置为匹配位置

令$d[i]=b[m-i-1]$,即$d[m-i-1]=b[i]$,
则$$f[j]=\sum_{i=0}^{m-1}a[j+i]*d[m-i-1]=(a*d)(j+m-1)$$
$FFT$计算卷积就好
```cpp
char s[Maxn], t[Maxn];
int q[Maxn], head, tail, tot[Maxn];
void cal(char c){
	memset(f, 0, sizeof(f)); memset(g, 0, sizeof(g));
	head=1, tail=0;
	for(int i=0; i < n; i++){
		if(s[i] == c) q[++tail]=i;
		while(head <= tail && q[head]+k < i) head++;
		if(head <= tail) f[i].a=1;
	}head=1, tail=0;
	for(int i=n-1; i >= 0; i--) {
		if(s[i] == c) q[++tail]=i;
		while(head <= tail && q[head] > i+k) head++;
		if(head <= tail) f[i].a=1;
	}
	for(int i=0; i < m; i++) if(t[i] == c) g[m-i-1].a=1;
	FFT(f, 1); FFT(g, 1); for(int i=0; i < lim; i++) f[i]=f[i]*g[i]; FFT(f, -1);
	for(int i=0; i < n; i++) tot[i]+=floor(f[i+m-1].a/lim+0.5);
}

void solve(){
	n=read(), m=read(), k=read(); scanf("%s", s); scanf("%s", t);
	while(lim <= n+m-2) lim<<=1, l++;
	for(int i=0; i < lim; i++) r[i]=r[i>>1]>>1|((i&1)<<l-1);
	cal('A'); cal('G'); cal('C'); cal('T'); int ans=0;
	for(int i=0; i < n; i++) if(tot[i] >= m) ans++;
	printf("%d", ans);
}
```


---

## 作者：Walrus (赞：2)

来总结一下这一类问题。

## 前置知识

已知 FFT 可以用于替代 KMP 来做**含有通配符**的相对复杂的字符串匹配问题，大概思路是这样：

由于字符集并不大，故考虑对每个字符做一遍卷积最后叠一起，我们定义 $A_{ch}(x)$ 表示原串的第 $x$ 位（从 $0$ 起）是否为字符 $ch$，$B_{ch}(x)$ 为模式串的第 $x$ 位是否为字符 $ch$。

然后完全匹配函数（从第 $k$ 位开始匹配）即为

$$f(k)=\sum\limits_{i=k}^{i+m-1}A_{ch}(i-k)\times b_{ch}(i)$$

但是这并不是卷积的一般形式，解决方法是**翻转模式串**，则完全匹配函数变为

$$f(k)=\sum\limits_{i=k}^{i+m-1}A_{ch}(i-k)\times b_{ch}(m-i-1)$$

也即（由于本人是萌新可能有误，欢迎指正）

$$f(k)=\sum\limits_{i+j=m-1-k}A_{ch}(i)\times b_{ch}(j)$$

这样就满足了卷积的一般形式。

有通配符的话也很简单，由于这是个万能字符，所以在原式基础上再乘上一个 $p_i\times p_j$ 即可，$p_i$ 表示当前位置是不是通配符，当然也可以并入 $A_{ch}$ 和 $B_{ch}$ 中。

例题有 [P4173](https://www.luogu.com.cn/problem/P4173)、[SP9012](https://www.luogu.com.cn/problem/SP9012) 等。

---

对于这道题，其实只是在上述问题的基础上加上了一条「偏差不超过 $k$」的限制，怎么处理呢？解决方法是将原串中的字符**向左右扩散 $k$ 个单位**，这样即可解决这个限制。

最后得到的多项式 $C$，同 KMP，需要匹配数达到 $m$ 才会对答案产生 $1$ 的贡献。

FFT 可以代替 KMP 解决一些相对复杂的字符串匹配问题，当然时间复杂度略逊 KMP，这里假设 $n,m,k$ 同阶，为 $O(N\log N)$。

[code](https://codeforces.com/contest/528/submission/304914939)

---

## 作者：baoyangawa (赞：2)

# 题意简述

给定长度分别为 $n$，$m$ 的字符串 $s$，$t$ 和一个“门限值” $k$，求 $t$ 在 $s$ 中以在下列规则出现了多少次：

- $t$ 在 $s$ 的第 $i$ 个位置出现，当且仅当满足：对于所有的 $j\in[1,m]$，都存在一个 $p\in [(i-j+1)-k,(i-j+1)+k]$ 使得 $s_p=t_j$。

# 解题思路

本文中 $p$ 均代表某一个字符，$p\in[\tt{A},\tt{C},\tt{G},\tt{T}]$；$x$ 均代表数字变量。

$\tt{A}$ 这种字体表达一个具体的字符。

考虑计算 $can_{i,p}$ 表示 $s$ 串的第 $i$ 个字符能否**变成**字符 $p$。

这个显然可以 $O(n)$ 计算，通过计算每个字符左边第一个 $p$ 的位置和右边第一个 $p$ 的位置，然后判断左右距离的最小值是否不超过 $k$ 即可。

定义函数 $S(p,x)$ 表示字符 $p$ 能否和 $s_x$ 匹配。

定义函数 $val(p)$ 为我们自己随便给字符 $p$ 赋的一个价值。 

我们记：

$$a_{x,p}=\begin{cases}val(p) & can_{x,p}=1\\0 & can_{x,p}=0\end{cases}$$

则我们可以构造：

$$S(p,x)=\Bigg((val(p)-a_{x, \tt{A} })(val(p)-a_{x, \tt{C} })(val(p)-a_{x, \tt{G} })(val(p)-a_{x, \tt{T} })\Bigg)^2$$

我们把 $t$ 串翻转，则当且仅当：

$$\sum\limits_{i=0}^{m-1}S(t_{m-1-i},j+i)=0$$

时，$t$ 串可以和 $s$ 串在 $j$ 位置匹配。

这个是个卷积形式，我们拆个括号，分好几项分别算一下就行了。这里给出一个[拆括号工具](https://zh.numberempire.com/simplifyexpression.php#google_vignette)。

当然带上平方后一共有八次，非常不可做。由于有四种字符，我们**完全可以把平方去掉**，去掉后也很难被卡掉，~~正确性应该有。~~

这样我们就可以愉快地过掉这个题了。

# 代码实现

```cpp
//#pragma GCC optimize(2)
//#pragma GCC optimize(3)
//#pragma GCC optimize("Ofast","inline")
#include<bits/stdc++.h>
#define fr(a) freopen(a,"r",stdin)
#define fw(a) freopen(a,"w",stdout)
#define MP(a,b) make_pair(a,b)
#define DEBUG
using namespace std;
typedef long long ll;
const int N=1e6+10,INF=0x3f3f3f3f,mod=998244353;
ll n,m,k;
ll lst[N][5],pre[N][5];
ll can[N][5];
string s,t;
ll qpow(ll a,ll n){
    ll res=1;
    while(n){
        if(n&1) (res *= a) %= mod;
        (a *= a) %= mod,n>>=1;
    }return res;
}
const long long G=3,invG=qpow(G,mod-2);
ll rev[2*N];
ll get2p(ll n){
    ll tmp=1;while((1ll<<tmp) < n) tmp++; tmp=1ll<<tmp;
    return tmp;
}
void ntt(ll *f,ll n,bool flag){
    for(int i=0;i<n;i++) rev[i]=(rev[i>>1]>>1) | (i&1?(n>>1):0);
    for(int i=0;i<n;i++) if(i<rev[i]) swap(f[i],f[rev[i]]);
    for(int len=2;len<=n;len<<=1){
        ll tmp=qpow((flag==0?G:invG),(mod-1) / len);
        for(int k=0;k<n;k+=len){
            ll now=1;
            for(int i=0;i<(len>>1);i++){
                ll tt=now*f[k+i+(len>>1)] %mod;
                f[k+i+(len>>1)]=(f[k+i] - tt + mod)%mod; 
                f[k+i]=(f[k+i] + tt) %mod; 
                now = now*tmp %mod;
            }
        }
    }
    if(flag){
        ll invl=qpow(n,mod-2);
        for(int i=0;i<n;i++) f[i]=f[i]%mod * invl %mod; 
    }
    return;
}
ll a1[N],a2[N],a3[N],a0[N];
ll t1[N],t2[N],t3[N],t4[N];
ll val[5];
ll idx[30];
int main(){
	srand(time(0));
	scanf("%lld%lld%lld",&n,&m,&k);
	cin>>s>>t;
	idx['A'-'A']=1,idx['C'-'A']=2,idx['G'-'A']=3,idx['T'-'A']=4;
	for(int i=1;i<=4;i++) val[i]=rand()%mod;
	for(int i=0;i<n;i++){
		for(int j=1;j<=4;j++){
			if(i==0) lst[i][j]=-INF;
			else lst[i][j]=lst[i-1][j];
		}lst[i][idx[s[i]-'A']]=i;
	}
	for(int i=n-1;i>=0;i--){
		for(int j=1;j<=4;j++){
			if(i==n-1) pre[i][j]=INF;
			else pre[i][j]=pre[i+1][j];
		}pre[i][idx[s[i]-'A']]=i;
	}
	for(int i=0;i<n;i++){
		for(int j=1;j<=4;j++){
			if((i-lst[i][j]<=k) || (pre[i][j]-i<=k)) can[i][j]=val[j];
		}
	}
	reverse(t.begin(),t.end());
	for(int i=0;i<m;i++){
		ll v=val[idx[t[i]-'A']];
		t1[i]=v%mod;
		t2[i]=t1[i] * v%mod;
		t3[i]=t2[i] * v%mod;
		ll ttmp=0;
		if(i>0) ttmp=t4[i-1];
		t4[i]=(t3[i] * v%mod + ttmp%mod)%mod;
	}
	for(int i=0;i<n;i++){
		ll a=can[i][1],b=can[i][2],c=can[i][3],d=can[i][4];
		a0[i]=a*b%mod*c%mod*d%mod;
		ll ttmp=0;
		if(i>0) ttmp=a0[i-1];
		(a0[i] += ttmp)%=mod;
		a1[i]=(((mod-b-a)*c%mod-a*b%mod)*d%mod-a*b%mod*c%mod)%mod;
		a2[i]=((c+b+a)*d%mod+(b+a)*c%mod+a*b%mod)%mod;
		a3[i]=((-d-c-b-a)%mod+mod)%mod;
	}
	ll tmp=get2p(n+m+2);
	ntt(t1,tmp,0),ntt(t2,tmp,0),ntt(t3,tmp,0);
	ntt(a1,tmp,0),ntt(a2,tmp,0),ntt(a3,tmp,0);
	for(int i=0;i<tmp;i++){
		(a1[i] *= t1[i])%=mod;
		(a2[i] *= t2[i])%=mod;
		(a3[i] *= t3[i])%=mod;
	}
	ntt(a1,tmp,1),ntt(a2,tmp,1),ntt(a3,tmp,1);
	ll res=0;
	for(int i=m-1;i<n;i++){
		ll ttmp=0;
		if(i>=m) ttmp=a0[i-m];
		ttmp = t4[m-1] + (a0[i]-ttmp);ttmp%=mod;
		ttmp += a1[i] + a2[i] + a3[i];
		ttmp%=mod;
		if(ttmp==0) res++;
	}
	printf("%lld\n",res);
	return 0;
}


```

---

## 作者：5k_sync_closer (赞：2)

Shift-And 字符串匹配。

预处理出每种字符可以匹配哪些位置，即预处理 $p_{i,j}$ 表示是否存在 $S_x=i$ 且 $|j-x|\le k$。

$S_x=i$ 使得 $p_{i,j}=1|j\in[\max(x-k,0),\min(x+k,n-1)]$，差分维护即可。

依次匹配 $T$ 的每一位，维护 $v_i$ 表示 $T$ 的当前这一位是否可能匹配 $S$ 的第 $i$ 位。

考虑转移，匹配 $T$ 的第 $x$ 位时 $v_i\gets v_{i-1}$，然后 $v_i\gets v_i\operatorname{and}p_{T_x,i}$ 即可。

需要维护 $v$ 的 Shift 和 And，上 `bitset` 即可。

```cpp
#include <bitset>
#include <cstdio>
#include <iostream>
using namespace std;
int n, m, k, t[250], o[4][200050];char a[200050], b[200050];
bitset<200000> v, p[4];
int main()
{
	t['A'] = 0;t['G'] = 1;t['C'] = 2;t['T'] = 3;
	scanf("%d%d%d%s%s", &n, &m, &k, a, b);for(int i = 0;i < n;++i)
		v.set(), ++o[t[a[i]]][max(i - k, 0)], --o[t[a[i]]][min(i + k + 1, n)];
	for(int i = 0;i < 4;++i) for(int j = 0;j < n;++j)	
		p[i][j] = o[i][j] += o[i][j - 1];
	v = p[t[b[0]]];for(int i = 1;i < m;++i) v = v << 1 & p[t[b[i]]];
	printf("%d", v.count());
	return 0;
}
```


---

## 作者：trsins (赞：1)

- $\text{CF528D Fuzzy Search}$
   - 算法：$\text{FFT}$

### 题目：

有一个长度为 $n$ 的串 $S$，以及长度为 $m$ 的串 $T$。

现给定一个数 $k$ ，我们说 $T$ 在 $S$ 的位置 $i$ 匹配上，当且仅当对于每一个 $1\le a\le m$ ，都有一个位置 $1\le b\le n$ 满足 $|(i+a-1)-b|\le k$ ，且 $S_b=T_a$ 。
  
请回答 $T$ 在 $S$ 中匹配上了多少个不同的位置。
  
$n,m,k\le2*10^5$

### 题解：

记 $p_{i,ch}$ 表示位置 $i$ 上放上字符 $ch$ 是否合法。$p_{i,ch}=1$ 当且仅当存在 $s_j=ch$ 且 $|i-j|\leq k$。

求 $p_{i,ch}$ ，对于 $s_i=c$ 将 $p_{i-k,ch},p_{i-k+1,ch},\dots,p_{i+k-1,ch},p_{i+k,ch}$ 设为 $1$，差分就行了。

设 $f_i$ 表示以 $i$ 开头的长度为 $|T|$ 字符串能与 $T$ 成功匹配多少位。

$$f_i=\sum\limits_{j=1}^{|T|}p_{i+j-1,t_j}$$

枚举每个字符 $ch\in\{\text{ACTG}\}$，设 $flag_j$ 表示 $T_j$ 是否等于 $ch$。那么字符 $ch$ 给 $f_i$ 带来的贡献就是 

$$f_i=\sum\limits_{j=1}^{|T|}p_{i+j-1,ch}\times flag_j$$

那么原式即为

$$ans=\sum\limits_{x-y=i}f_xflag_y$$

将 $S$ 翻转一下，得

$$ans=\sum\limits_{x+y=i}f_xflag_y$$

用 $\text{FFT}$ 一卷即可。



---

## 作者：huangzirui (赞：1)

[题面](https://www.luogu.com.cn/problem/CF528D)

考虑到字符集大小小于等于 $4$ ，对每一种字母单独考虑。

样例：

$ S = \texttt{AGCAATTCAT}\ \ \  T = \texttt{ACAT}\ \ \  k=1$

不妨先考虑字母 $\texttt{C}$ ，将 $S$ 和 $T$ 中为 $\texttt{C}$ 的位置变为 $1$ ，不为 $\texttt{C}$ 的位置变为 $0$ 再进行匹配。

则：

$ S = \texttt{0010000100}\ \  \  T = \texttt{0100}$

因为 $k=1$ ，$S$ 和 $T$ 匹配可以有 $1$ 的距离。这就意味着我们把 $S$ 中每个距离 $1$ 小于 $k$ 的位置变为 $1$ 后再正常匹配的答案和原答案相等。

那么就有：

$ S = \texttt{0111001110}\ \ \  T = \texttt{0100}$

### **重点：**

有：

对于 $S$ 中的每个位置 $k$，设 $sum$ $=$ $T$ 中 $1$ 的个数 若满足

$$\sum\limits^{m-1}_{i=0}S_{i+k}T_i = sum$$

则 $T$ 能在 $S$ 的 $k$ 号位置上得到匹配。（**此处的匹配只指当前选定的字母都能得到匹配**）

证明：

因为 $T$ 中只有 $sum$ 个 $1$，其他位置上都是 $0$ ，而 $0$ 乘任何其他数都是 $0$ .所以如果上式成立，那么每一个 $T$ 中的 $1$ 都对应了一个 $S$ 中的 $1$ 。因此可以得到匹配。

对于上式，看上去就很像FFT。那么构造一个序列 $A$ 使得 $A_{m-i-1}=T_i$

那么上式就转化成：

$$\sum\limits^{m-1}_{i=0}S_{i+k}A_{m-i-1} = sum$$

$$\sum\limits_{i+j=m+k-1}S_iA_j = sum$$

然后 FFT 一下可以很快的处理出上式。

因为有四个字母所以要对每个字母跑一边，然后取交集。

实现起来也不是很复杂，也不知道为什么是黑题。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline int read(){
	char c=getchar();int x=0,f=1;
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
    return x*f;
}
const int maxn=400010;
int i,j,k,n,m;
string s,t;
int a[maxn*2],b[maxn*2];
char C[4]={'A','C','T','G'};

const double Pi=acos(-1.0);
struct Complex{
	double x,y;
};
Complex operator+(Complex a,Complex b){return (Complex){a.x+b.x,a.y+b.y};}
Complex operator-(Complex a,Complex b){return (Complex){a.x-b.x,a.y-b.y};}
Complex operator*(Complex a,Complex b){return (Complex){a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x};}
Complex Get_w(int k,int len,bool op){
	int T=1;if(!op)T=-1;
	return (Complex){cos(2*k*Pi/len),T*sin(2*k*Pi/len)};
}

Complex A[maxn*2],B[maxn*2],tmp[maxn*2];
int R[maxn*2],Ans[maxn*2];
void FFT(int len,Complex *a,bool op){
	for(int i=0;i<len;i++)
		if(i<R[i])swap(a[i],a[R[i]]);
	for(int i=1;i<len;i<<=1)
		for(int j=0;j<len;j+=i*2){
			Complex w=(Complex){1,0},Wn=Get_w(1,2*i,op);
			for(int k=0;k<i;k++,w=w*Wn){
				int K=k+j;
				Complex S1=a[K],S2=w*a[K+i];
				a[K]=S1+S2;
				a[K+i]=S1-S2;
			}
		}
}

int main(){
	cin>>n>>m>>k; 
	cin>>s>>t;
	
	int len=1,L=0;
	while(len<=n+m)len<<=1,++L;
	for(j=0;j<=len;j++)
		R[j]=R[j/2]/2+(j%2)*(1<<L-1);
	
	for(i=0;i<4;i++){
		int last=-1e9,ans=0;
		for(j=0;j<n;j++)
			if(s[j]==C[i])a[j]=2;
			else a[j]=0;
		for(j=0;j<m;j++){
			if(t[j]==C[i])b[j]=1;
			else b[j]=0;
			ans+=b[j];
		}
		for(j=0;j<n;j++){
			if(a[j]==2)last=j;
			if(last+k>=j)a[j]=max(a[j],1);
		}last=1e9;
		for(j=n-1;j>=0;j--){
			if(a[j]==2)last=j;
			if(last-k<=j)a[j]=max(a[j],1);
		}
		for(j=0;j<n;j++)if(a[j])a[j]=1;
		
		for(j=0;j<len;j++)A[j]=(Complex){a[j],0};
		for(j=0;j<len;j++)B[j]=(Complex){b[j],0};
		for(j=0;j<m;j++)tmp[m-j-1]=B[j];
		for(j=0;j<m;j++)B[j]=tmp[j];
		
		FFT(len,A,1);FFT(len,B,1);
		for(j=0;j<=len;j++)A[j]=A[j]*B[j];
		FFT(len,A,0);
		for(j=0;j<=len;j++)A[j].x=(int)(A[j].x/len+0.5);
		for(j=0;j<=n-m;j++)
			if(((int)(A[m+j-1].x))==ans)
				Ans[j]++;
	}
	int ANS=0;
	for(j=0;j<=n-m;j++)
		if(Ans[j]==4)++ANS;
	cout<<ANS<<endl;
	return 0;
}
```

---

## 作者：HomuraCat (赞：1)

是一道法法塔匹配字符串的经典套路题

我们首先知道我们可以把两个字符串先$01$化。将$b$串翻转然后跟$a$串做卷积就能弄出一个位置的匹配数

可是这题还有一个$k$，咋搞呢？

我们可以知道，对于任意一个$a[i]=1$，我们可以令$a[i-k$到$i+k]=1$，显然这样与$b$卷积就解决了$k$的限定。

然后用一个$lf[i]$表示前面一个$1$的位置离当前位置$i$的距离，$rf[i]$表示后面一个$1$的位置离当前位置$i$的距离，然后$O(n)$预处理一下就行了。

总复杂度$O(4nlogn)$

```cpp
#include<bits/stdc++.h>
#define N 600005
#define fo(i, a, b) for (R int i = (a); i <= (b); ++i)
#define fd(i, a, b) for (R int i = (a); i >= (b); --i)
#define in inline
#define R register
const double pi = acos(-1);
int a[N], b[N], len, n, m;
struct complex{
    double real, imag;
    in void conj ()
    {
        imag = -imag;
    }
    friend in complex operator * (const complex &x, const complex &y)
    {
        return (complex) {x.real * y.real - x.imag * y.imag, x.real * y.imag + x.imag * y.real};
    }
    friend in complex operator + (const complex &x, const complex &y)
    {
        return (complex) {x.real + y.real, x.imag + y.imag};
    }
    friend in complex operator - (const complex &x, const complex &y)
    {
        return (complex) {x.real - y.real, x.imag - y.imag};
    }
}c1[N], c2[N], omega[N], c3[N];
in void dft(complex *c, int len)
{
    int k = 0;
    while ((1 << k) < len) ++k;
    --k;
    fo (i, 0, len)
    {
        int g = 0;
        fo (j, 0, k)
            if ((1 << j) & i) g |= (1 << k - j);
        if (i < g) std::swap(c[i], c[g]);
    }
    for (int l = 2; l <= len; l <<= 1)
    {
        int mid = l >> 1;
        for (complex *p = c; p != c + len; p += l)
            for (int i = 0; i < mid; ++i)
            {
                complex tmp = omega[len / l * i] * p[mid + i];
                p[mid + i] = p[i] - tmp;
                p[i] = p[i] + tmp;
            }
    }
}
int mp[5], k, lf[N], rf[N];
char s1[N], s2[N];
int main()
{
    scanf("%d %d %d", &n, &m, &k);
    mp[1] = 'A';
    mp[2] = 'C';
    mp[3] = 'G';
    mp[4] = 'T';
    scanf("%s", s1);
    scanf("%s", s2);
    int ans = 0;
    memset(c3, 0, sizeof c3);
    fo (l, 1, 4)
    {
        for (int i = 0; i < n; ++i) a[i] = (mp[l] == s1[i]);
        for (int i = 0; i < m; ++i) b[i] = (mp[l] == s2[i]);
        std::reverse(b, b + m);
        
        memset(lf, 0, sizeof lf); memset(rf, 0, sizeof rf);
        int sta = 0;
        while (sta < n && !a[sta]) lf[sta++] = 23333333;
        lf[sta] = 0;
        fo (i, sta + 1, n - 1)
            lf[i] = (a[i]) ? 0 : lf[i - 1] + 1;
        sta = n - 1;
        while (sta >= 0 && !a[sta]) rf[sta--] = 23333333;
        rf[sta] = 0;
        fd (i, sta - 1, 0)
            rf[i] = (a[i]) ? 0 : rf[i + 1] + 1;
        fo (i, 0, n - 1)
            if (std::min(lf[i], rf[i]) <= k) a[i] = 1;
        
        int len = 1;
        while (len <= n + m) len = len << 1;
        fo (i, 0, len) c1[i].real = c2[i].real = c1[i].imag = c2[i].imag = 0;
        for (int i = 0; i < n; ++i) c1[i].real = a[i];
        for (int i = 0; i < m; ++i) c2[i].real = b[i];
        fo (i, 0, len)
            omega[i] = (complex) {cos(2 * pi * i / len), sin(2 * pi * i / len)};
        dft(c1, len);
        dft(c2, len);
        fo (i, 0, len)
            c1[i] = c1[i] * c2[i];
        fo (i, 0, len)
            omega[i].conj();
        dft(c1, len);
        fo (i, 0, len)
            c3[i].real += c1[i].real / len;
    }
    fo (i, 0, n + m) a[i] = (int) (c3[i].real + 0.5);
    fo (i, m - 1, n - 1) if (a[i] == m) ++ans;
    printf("%d\n", ans);
    
}
```

---

## 作者：大菜鸡fks (赞：1)

可以用类似滑动窗口的方式计算出某个位置是否能匹配一个字母。

再就是常见套路把模式串翻转。对于每个字母做fft，计算贡献

```cpp
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<complex>
using namespace std;
inline int read(){int x=0,f=1,ch=getchar(); while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();} while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();} return x*f;}
inline void write(int x){if (x<0) putchar('-'),x=-x; if (x>=10) write(x/10); putchar(x%10+'0');}
inline void writeln(int x){write(x); puts("");}
typedef complex<double> E;
const double pi=acos(-1.0);
const int N=530005;
int ans,ton[N],n,m,k,lim,L,rev[N];
char s[N],t[N];
E a[N],b[N];
inline void init(){
	n=read(); m=read(); k=read();
	scanf("%s",s); scanf("%s",t);
}
inline void FFT(E *A,int opt){
	for (int i=0;i<lim;i++) if (i>rev[i]) swap(A[i],A[rev[i]]);
	for (int s=1;s<lim;s<<=1){
		E Wn(cos(pi/s),opt*sin(pi/s));
		for (int i=0;i<lim;i+=(s<<1)){
			E w(1,0);
			for (int j=0;j<s;j++,w=w*Wn){
				E x=A[i+j],y=w*A[i+j+s];
				A[i+j]=x+y; A[i+j+s]=x-y;
			}
		}
	}
	if (opt==-1) for (int i=0;i<lim;i++) A[i]/=lim;
}
inline void calc(char c){
	memset(a,0,sizeof a); memset(b,0,sizeof b);
	int cnt=0;
	for (int i=0;i<k;i++) cnt+=s[i]==c;
	for (int i=0;i<n;i++){
		if (i+k<n) cnt+=s[i+k]==c;
		if (i-k-1>=0) cnt-=s[i-k-1]==c;
		a[i]=cnt>0?1:0;
	} 
	for (int i=0;i<m;i++) b[i]=t[i]==c?1:0;
	FFT(a,1); FFT(b,1);
	for (int i=0;i<lim;i++) a[i]*=b[i];
	FFT(a,-1);
	for (int i=0;i<=n-m;i++) ton[i]+=(int)(a[i+m-1].real()+0.5);
}
inline void solve(){
	for (lim=1;lim<=n+m-2;lim<<=1,L++);
	for (int i=0;i<lim;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<(L-1));
	reverse(t,t+m);
	calc('A'); calc('G'); calc('C'); calc('T');
	for (int i=0;i<=n-m;i++) if (ton[i]==m) ans++;
	writeln(ans);
}
int main(){
	init(); solve();
	return 0;
}
```

---

## 作者：KobeBeanBryantCox (赞：1)

# CF528D Fuzzy Search 题解

---------------

[题目传送门](https://www.luogu.com.cn/problem/CF528D)。

---------------

## 题意

匹配一个允许偏差范围 $\le k$ 的串，输出其出现次数。

---------------

## 思路

由于题目中只有四个字符，考虑一个一个处理，最后合起来看每一个字符是不是都能在某一位置匹配。

以样例为例，先处理 `A` 字符。

$$S=A**AA***A*$$

$$T=A*A*$$

考虑这个 $k$ 怎么处理。

把 $S$ 向外延伸 $k$ 位即可，这样就消去了 $k$ 的影响：

$$S=AAAAAA*AAA$$

$$T=A*A*$$

向外延伸这个操作，可以从左往右扫一遍，再从右往左扫一遍，就能搞定了（具体看代码）。

换一个形式：

$$f=1111110111$$

$$g=1010$$

考虑记 $h_i$ 表示在 $S$ 的第 $i$ 位开始往后能否和 $T$ 匹配。

考虑怎么算这个 $h$。

不难发现，一种可能的算法如下（不唯一）：

$$h_i=\sum_{j=0}^{m-1}g_j(g_j-f_{i+j})$$

其中 $g,f,h$ 的索引都从 $0$ 开始。

拆开得：

$$h_i=\sum_{j=0}^{m-1}g_j^2-g_j\times f_{i+j}$$

由于 $g$ 只有 $0$ 和 $1$，因此 $g_j^2=g_j$。

化为：

$$h_i=\sum_{j=0}^{m-1}g_j-g_j\times f_{i+j}$$

$$h_i=\sum_{j=0}^{m-1}g_j\times(1-f_{i+j})$$

令 $f'_i=1-f_i$，翻转 $g$：

$$h_i=\sum_{j=0}^{m-1}g_{m-j-1}\times f'_{i+j}$$

标准卷积形式，NTT 即可。

最后，四个字符的 $h$ 的所有位置取一个或，然后看最终 $h_i=0$ 的有多少个就是答案。

---------------

## AC 代码

应该很好懂。

```cpp
#include<bits/stdc++.h>
#define Code using
#define by namespace
#define wjb std
Code by wjb;
const int N=1<<19,mod=998244353,G=3,invG=332748118;
int rev[N];
void init(int len)
{
	int b=log2(len);
	for(int i=0;i<len;i++)rev[i]=(rev[i>>1]>>1)+((i&1)<<(b-1));
}
int ksm(int a,int b)
{
	int res=1;
	for(;b;a=1ll*a*a%mod,b>>=1)if(b&1)res=1ll*res*a%mod;
	return res;
}
void NTT(int *a,int n,int type=1)
{
	for(int i=0;i<n;i++)if(i<rev[i])swap(a[i],a[rev[i]]);
	for(int len=1;len<=(n>>1);len<<=1)
	{
		int gn=ksm(type==1?G:invG,(mod-1)/(len<<1));
		for(int i=0;i<n;i+=(len<<1))
		{
			int g=1;
			for(int j=0;j<len;j++,g=1ll*g*gn%mod)
			{
				int a0=a[i+j],a1=1ll*g*a[i+j+len]%mod;
				a[i+j]=(a0+a1)%mod,a[i+j+len]=(a0-a1+mod)%mod;
			}
		}
	}
}
void INTT(int *a,int n)
{
	NTT(a,n,-1);
	int inv=ksm(n,mod-2);
	for(int i=0;i<n;i++)a[i]=1ll*a[i]*inv%mod;
}
int n,m,k;
string s,t;
int f[N],g[N],h[N];
int tmp[N];
void initfg(char c)
{
	for(int i=0;i<n;i++)f[i]=(s[i]==c);
	for(int i=0;i<m;i++)g[i]=(t[i]==c);
	for(int i=0,cnt=0;i<n;i++,cnt--)
	{
		if(f[i])cnt=k+1;
		if(cnt>0)tmp[i]=1;
	}
	for(int i=n-1,cnt=0;i>=0;i--,cnt--)
	{
		if(f[i])cnt=k+1;
		if(cnt>0)tmp[i]=1;
	}
	for(int i=0;i<n;i++)f[i]|=tmp[i];
	for(int i=0;i<n;i++)f[i]=1-f[i];
	reverse(g,g+m);
}
int len=1;
void work(char c)
{
	fill(f,f+len,0),fill(g,g+len,0),fill(tmp,tmp+len,0);
	initfg(c);
	NTT(f,len),NTT(g,len);
	for(int i=0;i<len;i++)f[i]=1ll*f[i]*g[i]%mod;
	INTT(f,len);
	for(int i=0;i<n-m+1;i++)h[i]|=f[i+m-1];
}
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m>>k>>s>>t;
	while(len<=n+m)len<<=1;init(len);
	work('A'),work('G'),work('C'),work('T');
	int cnt=0;
	for(int i=0;i<n-m+1;i++)if(h[i]==0)cnt++;
	cout<<cnt;
	return 0;
}
```

跑的还挺快的。

------------

## 后记

若讲述不清或者有误，欢迎评论或私信。

---

## 作者：LastKismet (赞：0)

# Sol
先忽略位置误差情况，考虑若位置精确如何判断。

发现字符集特别小，考虑枚举字符集。对每一种字符，找出两个串中均为这个字符的位置。一个串最后能匹配上的所有位置就是四次结果相加。

令为当前字符的位置为 $1$，非当前字符的位置为 $0$，这样两串产生的序列分别为 $A,B$，则以 $k$ 为起点的 $S$ 子串中匹配上的位置数为（省略上界）：
$$
\sum_{i=0}A_{k+i}B_i
$$

我们把 $B$ 翻转一下即可卷积了。

然后考虑位置误差，我们在其中一个串中把所有满足最近匹配上的位置在阀限内的位置令为 $1$ 即可。这个是容易实现的，比如使用线段树，以及其他大量更简单或复杂的数据结构。这里由于线段树常见且好打就使用线段树了。

线段树部分是简单的。区间查询或和即可。

然后就用精确匹配的思路解决即可。
# Code
```cpp
string s,t;
namespace NTT{
    const mint p=0,g=3,gi=332748118;
    typedef vec<mint> poly;
    vec<int> r;
    void ntt(int lim,poly &a,int type){
        a.resize(lim);
        repl(i,0,lim)if(i<r[i])swap(a[i],a[r[i]]);
        for(int mid=1;mid<lim;mid<<=1){
            mint w1=((~type)?g:gi)^((p-1)/(mid<<1));
            for(int j=0;j<lim;j+=(mid<<1)){
                mint w=1;
                repl(k,0,mid){
                    mint x=a[j+k],y=w*a[j+mid+k];
                    a[j+k]=x+y;
                    a[j+mid+k]=x-y;
                    w=w*w1;
                }
            }
        }
    }
    poly operator*(poly a,poly b){
        int lim=1,l=0,len=a.size()+b.size()-1;
        while(lim<a.size()+b.size())lim<<=1,l++;
        r.resize(lim);
        repl(i,0,lim)r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
        ntt(lim,a,1);ntt(lim,b,1);
        repl(i,0,lim)a[i]=a[i]*b[i];
        ntt(lim,a,-1);
        a.resize(len);
        mint inv=(mint)lim^(p-2);
        repl(i,0,a.size())a[i]*=inv;
        return a;
    }
    poly operator+(poly a,poly b){
        if(a.size()<b.size())a.resize(b.size());
        repl(i,0,b.size())a[i]=a[i]+b[i];
        return a;
    }
    poly operator-(poly a,poly b){
        if(a.size()<b.size())a.resize(b.size());
        repl(i,0,b.size())a[i]=a[i]-b[i]+p;
        return a;
    }
}
using namespace NTT;

char ch[4]={'A','C','G','T'};

const int N=2e5+5;

int n,m;
poly a,b,c;
int tmm[N];

struct segment{
    int dat[N<<2];
    void build(int x=1,int l=0,int r=n-1){
        dat[x]=0;
        if(l==r)return;
        int m=l+r>>1;
        build(x<<1,l,m);
        build(x<<1|1,m+1,r);
    }
    void change(int k,int x=1,int l=0,int r=n-1){
        if(l==r)return dat[x]=1,void();
        int m=l+r>>1;
        if(k<=m)change(k,x<<1,l,m);
        else change(k,x<<1|1,m+1,r);
        dat[x]=1;
    }
    int query(int lq,int rq,int x=1,int l=0,int r=n-1){
        if(lq<=l&&r<=rq)return dat[x];
        int m=l+r>>1;
        int res=0;
        if(lq<=m)res|=query(lq,rq,x<<1,l,m);
        if(m<rq)res|=query(lq,rq,x<<1|1,m+1,r);
        return res;
    }
}seg;   

int K;

inline void Main(){
    read(n,m,K);
    read(s,t);
    repl(i,m-1,n)tmm[i]=0;
    reverse(t.begin(),t.end());
    repl(k,0,4){
        seg.build();
        a.resize(n),b.resize(m);
        repl(i,0,n)if(s[i]==ch[k])seg.change(i);
        repl(i,0,n)a[i]=seg.query(max(0,i-K),min((int)n-1,i+K));
        repl(i,0,m)b[i]=(t[i]==ch[k]);
        c=a*b;
        repl(i,m-1,n)tmm[i]+=c[i].x;
    }
    int ans=0;
    repl(i,m-1,n)if(m==tmm[i])++ans;
    put(ans);
}
```

---

## 作者：VenusM1nT (赞：0)

$\textbf{FFT}$.  
常用套路，考虑到该题只有 `ATGC` 四种字符，可以分别考虑，假设当前在考虑 `A`，则可以令 $f_i=[S_i=$ `A` $]$，$g_i=[T_i=$ `A` $]$，然后做卷积，令 $h=f* f+g* g$，对于其他三个字符也这样处理，最后就可以统计答案。显然这是针对 $k=0$ 的情况的，考虑 $k\neq0$ 时怎么处理，$g$ 不用修改，令 $f_i=[\exists\ S_j=$ `A` $,|i-j|\leq k]$，也就是离当前位置最近的 `A` 的距离不超过 $k$ 即为合法，然后再做卷积，最后就可以统计了。
```cpp
#include<bits/stdc++.h>
#define MAXN 1000005
#define reg register
#define inl inline
#define db double
using namespace std;
const db Pi=acos(-1.0);
int n,m,K,lim=1,maxn,rev[MAXN],h[MAXN],s[MAXN],pos[MAXN],ans;
char S[MAXN],T[MAXN];
struct Complex
{
	db x,y;
	friend Complex operator + (const Complex &a,const Complex &b)
	{
		return ((Complex){a.x+b.x,a.y+b.y});
	}
	friend Complex operator - (const Complex &a,const Complex &b)
	{
		return ((Complex){a.x-b.x,a.y-b.y});
	}
	friend Complex operator * (const Complex &a,const Complex &b)
	{
		return ((Complex){a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x});
	}
}f[MAXN],g[MAXN];
inl void Init(reg Complex *A)
{
	for(reg int i=0;i<lim;i++) A[i].x=A[i].y=0;
}
inl void FFT(reg Complex *A,reg int opt)
{
	for(reg int i=0;i<lim;i++) if(i<rev[i]) swap(A[i],A[rev[i]]);
	for(reg int mid=1;mid<lim;mid<<=1)
	{
		reg Complex Wn=((Complex){cos(Pi/(db)mid),(db)opt*sin(Pi/(db)mid)});
		for(reg int j=0;j<lim;j+=(mid<<1))
		{
			reg Complex W=((Complex){1,0});
			for(reg int k=0;k<mid;k++,W=W*Wn)
			{
				reg Complex x=A[j+k],y=W*A[j+k+mid];
				A[j+k]=x+y;
				A[j+k+mid]=x-y;
			}
		}
	}
	if(opt==1) return;
	for(reg int i=0;i<lim;i++) A[i].x=(int)(A[i].x/(db)lim+0.5);
}
inl void Modify(reg char ch)
{
	Init(f);
	Init(g);
	reg int pre=-1e9;
	for(reg int i=0;i<n;i++)
	{
		if(S[i]==ch) pre=i;
		if(i-pre<=K) f[i].x=1.0;
	}
	pre=1e9;
	for(reg int i=n-1;i>=0;i--)
	{
		if(S[i]==ch) pre=i;
		if(pre-i<=K) f[i].x=1.0;
	}
	for(reg int i=0;i<m;i++) if(T[m-i-1]==ch) g[i].x=1.0;
	FFT(f,1); FFT(g,1);
	for(reg int i=0;i<lim;i++) f[i]=f[i]*g[i];
	FFT(f,-1);
	for(reg int i=0;i<lim;i++) h[i]+=(int)f[i].x;
}
int main()
{
	scanf("%d %d %d",&n,&m,&K);
	scanf("%s",S);
	scanf("%s",T);
	while(lim<=(n<<1))
	{
		lim<<=1;
		maxn++;
	}
	for(reg int i=0;i<=lim;i++) rev[i]=((rev[i>>1]>>1)|((i&1)<<(maxn-1)));
	Modify('A');
	Modify('G');
	Modify('T');
	Modify('C');
	for(reg int i=0;i<lim;i++) if(h[i]==m) ans++;
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：do_while_true (赞：0)

分别仅考虑 $A,C,G,T$，把匹配成功的位置取个交集就可以。

使用 FFT 来完成字符串匹配。

现在仅考虑 $A$，把 $S$ 中不会和 $A$ 匹配上的位置上的字符设为 $o$，把 $T$ 中不是 $A$ 的字符设为 $\#$，则匹配函数 $C(x,y)$ （其中 $x$ 来自 $S$，$y$ 来自 $T$）要满足：

- $=0,x=A,y=A$；
- $=0,x=A,y=\#$；
- $>0,x=o,y=A$；
- $=0,x=o,y=\#$．

这样的 $C$ 才能满足匹配成功值为 $0$，否则大于 $0$．

设：

- $S$ 中的 $A$ 值为 $0$，$o$ 值为 $1$；

- $T$ 中的 $A$ 值为 $1$，$\#$ 值为 $0$；

- $C(x,y)=xy$．

对于每个字符只需要一次 FFT 就可以了。

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
typedef long long ll;
typedef double ld;
inline int Max(int x, int y) { return x > y ? x : y; }
inline int Min(int x, int y) { return x < y ? x : y; }
const int N = 800010;
const ld pi = acos(-1.0);
struct cpx {
	ld x, y;
	cpx(ld xx = 0, ld yy = 0) { x = xx; y = yy; }
};
cpx operator + (cpx a, cpx b) { return cpx(a.x + b.x, a.y + b.y); }
cpx operator - (cpx a, cpx b) { return cpx(a.x - b.x, a.y - b.y); }
cpx operator * (cpx a, cpx b) { return cpx(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x); }
cpx *getw(int n, int type) {
	static cpx w[N/2];
	w[0] = cpx(1, 0); w[1] = cpx(cos(2 * pi / n), sin(2 * pi / n) * type);
	for(int i = 2; i < n/2; ++i) w[i] = w[i-1] * w[1];
	return w;
}
int p[N];
void FFT(cpx *a, int n, int type) {
	for(int i = 0; i < n; ++i) if(i < p[i]) std::swap(a[i], a[p[i]]);
	for(int i = 1; i < n; i <<= 1) {
		cpx *w = getw(i << 1, type);
		for(int j = 0; j < n; j += i << 1) {
			cpx *b = a + j, *c = b + i;
			for(int k = 0; k < i; ++k) {
				cpx v = w[k] * c[k];
				c[k] = b[k] - v;
				b[k] = b[k] + v;
			}
		}
	}
	if(type == -1) for(int i = 0; i < n; ++i) a[i].x /= n;
}
void mul(int *a, int *b, int *c, int n, int m) {
	static cpx f[N], g[N];
	int len = 1, ct = 0;
	while(len <= n + m) len <<= 1, ++ct;
	for(int i = 0; i < len; ++i) p[i] = (p[i>>1]>>1) | ((i&1) << (ct-1));
	for(int i = 0; i < len; ++i) f[i] = g[i] = cpx(0, 0);
	for(int i = 0; i < n; ++i) f[i] = cpx(a[i], 0);
	for(int i = 0; i < m; ++i) g[i] = cpx(b[i], 0);
	FFT(f, len, 1);
	FFT(g, len, 1);
	for(int i = 0; i < len; ++i) f[i] = f[i] * g[i];
	FFT(f, len, -1);
	for(int i = 0; i < len; ++i) c[i] = (int)(f[i].x+0.5);
}
int n, m, k;
int id[300], c[4][N], A[4][N];
char s[N], t[N];
int f[N], g[N];
signed main() {
	scanf("%d%d%d", &n, &m, &k);
	id['A'] = 0, id['G'] = 1, id['C'] = 2, id['T'] = 3;
	scanf("%s", s); scanf("%s", t);
	for(int i = 0; i < n; ++i) {
		s[i] = id[(int)s[i]]; t[i] = id[(int)t[i]];
		++c[(int)s[i]][Max(i-k, 0)];
		--c[(int)s[i]][Min(i+k+1, n)];
	}
	for(int i = 1; i < n; ++i) for(int j = 0; j < 4; ++j) c[j][i] += c[j][i-1];
	for(int o = 0; o < 4; ++o) {
		for(int i = 0; i < n; ++i)
			f[i] = c[o][i] ? 0 : 1;
		for(int i = 0; i < m; ++i)
			g[i] = t[i] == o ? 1 : 0;
		std::reverse(g, g + m);
		mul(f, g, A[o], n, m);
	}
	int ans = 0;
	for(int i = m-1; i < n; ++i)
		if(!A[0][i] && !A[1][i] && !A[2][i] && !A[3][i])
			++ans;
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：洛水·锦依卫 (赞：0)

# Problem

## Description

你有一个长度为 $n$ 的串 $S$，以及长度为 $m$ 的串 $T$。

现给定一个数 $k$ ，我们说 $T$ 在 $S$ 的位置 $i$ 匹配上，当且仅当对于每一个 $1\le a\le m$ ，都有一个位置 $1\le b\le n$ 满足 $|(i+a-1)-b|\le k$ ，且 $S_b=T_a$ 。

请回答 $T$ 在 $S$ 中匹配上了多少个不同的位置。

## Range

$n,m,k\le2*10^5$

# Algorithm

$FFT$

# Mentality

思路很妙的说。

先考虑 $k=0$ 的情况。不难发现，当 $T$ 与 $S$ 匹配上时，$T$ 中的每个字符与 $S$ 中对应匹配字符的 **位置的差** 是相等的。

同时考虑在多项式乘法中，若许多对项最后会贡献在同一个位置上，那么它们的 **次方的和** 是相等的。

则考虑倒转原串，得到 $T'$ 。

由于字符集大小仅仅为 $4$ ，我们可以尝试一下分开考虑每种不同的字符。

对于当前字符 $c$，考虑设 $f_i=[S_i==c]*x^i$，$g_i=[T'_i==c]*x^i$。

则对于得到的 $F(x)=f(x)*g(x)$ 而言，我们发现对于原串中的字符 $S_i=T_j=c$ ，它们在 $f$ 与 $g$ 中对应项的乘积为 $1$ ，且对位置 $m-j+1+i$ 产生了 $1$ 的贡献。

对于下一种字符 $p$ 而言，若有 $S_{i+1}=T_{j+1}=p$，则会对 $m-(j+1)+1+(i+1)=m-j+1+i$ 有 $1$ 的贡献。

换句话说，若有 $T$ 在 $S$ 的位置 $i$ 匹配上了，那么必定有：$T_1=S_i,T_2=S_{i+1}\dots T_m=S{i+m-1}$ ，也就必定会在对四种字符的卷积里对 $m-j+1+i$ 这一项总共产生 $m$ 的贡献。

将四次卷积的结果相加，则最后的答案为：系数为 $m$ 的项的个数。

接着考虑 $k>0$ 的情况，我们会发现和 $k=0$ 的思路几乎一致，对于这个 $k$ ，想想它的意义：我们在处理每种不同的字符的时候，若当前字符为 $c$ ，对于每个为 $c$ 的位置，它往左右两边 $k$ 位也都是可以匹配的位置。

那我们直接将每个 $c$ 的左右 $k$ 位也都设成 $c$ 不就好了嘛？

那么思路就很清晰了：四种字符分别统计，然后对于每种当前统计的字符，将左右 $k$ 位设为同样的字符，得到 $f,g$ 两个多项式，并将其卷积得到 $F(x)=f(x)*g(x)$ ，将四个 $F(x)$ 相加，统计系数为 $m$ 的项数。

完毕。

# Code

```cpp
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
#define LL long long
#define go(x, i, v) for (int i = hd[x], v = to[i]; i; v = to[i = nx[i]])
#define inline __inline__ __attribute__((always_inline))
LL read() {
  long long x = 0, w = 1;
  char ch = getchar();
  while (!isdigit(ch)) w = ch == '-' ? -1 : 1, ch = getchar();
  while (isdigit(ch)) {
    x = (x << 3) + (x << 1) + ch - '0';
    ch = getchar();
  }
  return x * w;
}
const int Max_n = 2e5 + 5, mod = 998244353, G = 3;
int n, m, K, ans;
int f[Max_n << 2], g[Max_n << 2], A[Max_n << 2];
int lim, bit, rev[Max_n << 2];
char S[Max_n], T[Max_n];
inline void Convert(char &c) {
  if (c == 'A') c = 'a';
  if (c == 'C') c = 'b';
  if (c == 'G') c = 'c';
  if (c == 'T') c = 'd';
}
inline int ksm(int a, int b) {
  int res = 1;
  for (; b; b >>= 1, a = 1ll * a * a % mod)
    if (b & 1) res = 1ll * res * a % mod;
  return res;
}
namespace NTT {
inline void dft(int *f, bool t) {
  for (int i = 0; i < lim; i++)
    if (rev[i] > i) swap(f[i], f[rev[i]]);
  for (int len = 1; len < lim; len <<= 1) {
    int Wn = ksm(G, (mod - 1) / (len << 1));
    if (t) Wn = ksm(Wn, mod - 2);
    for (int i = 0; i < lim; i += len << 1) {
      int Wnk = 1;
      for (int k = i; k < i + len; k++, Wnk = 1ll * Wnk * Wn % mod) {
        int x = f[k], y = 1ll * f[k + len] * Wnk % mod;
        f[k] = (x + y) % mod, f[k + len] = (x - y + mod) % mod;
      }
    }
  }
}
}  // namespace NTT
inline void ntt(int *f, int *g) {
  NTT::dft(f, 0), NTT::dft(g, 0);
  for (int i = 0; i < lim; i++) f[i] = 1ll * f[i] * g[i] % mod;
  NTT::dft(f, 1);
  int Inv = ksm(lim, mod - 2);
  for (int i = 0; i < lim; i++) f[i] = 1ll * f[i] * Inv % mod;
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("D.in", "r", stdin);
  freopen("D.out", "w", stdout);
#endif
  n = read(), m = read(), K = read();
  scanf(" %s", S + 1), scanf("%s", T + 1);
  for (int i = 1; i <= n; i++) Convert(S[i]);
  for (int i = 1; i <= m; i++) Convert(T[i]);
  for (int i = 1; i <= m / 2; i++) swap(T[i], T[m - i + 1]);
  bit = log2(n + m) + 1, lim = 1 << bit;
  for (int i = 0; i < lim; i++)
    rev[i] = rev[i >> 1] >> 1 | ((i & 1) << (bit - 1));
  for (int k = 'a'; k <= 'd'; k++) {
    memset(f, 0, sizeof(f)), memset(g, 0, sizeof(g));
    for (int i = 1, cnt = 0; i <= n; i++) {
      if (S[i] == k)
        cnt = K, f[i] = 1;
      else if (cnt)
        cnt--, f[i] = 1;
    }
    for (int i = n, cnt = 0; i >= 1; i--) {
      if (S[i] == k)
        cnt = K, f[i] = 1;
      else if (cnt)
        cnt--, f[i] = 1;
    }
    for (int i = 1; i <= m; i++) g[i] = T[i] == k;
    ntt(f, g);
    for (int i = 0; i < lim; i++) A[i] += f[i];
  }
  for (int i = 0; i < lim; i++)
    ans += A[i] == m;
  cout << ans;
}
```


---

