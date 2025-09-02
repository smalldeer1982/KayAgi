# [ARC185C] Sum of Three Integers

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc185/tasks/arc185_c

整数列 $ A\ =\ (A_1,\ A_2,\ \dots,\ A_N) $ および整数 $ X $ が与えられます。  
 次の条件を全て満たす整数の組 $ (i,\ j,\ k) $ を $ 1 $ 組出力してください。条件を満たす組が存在しない場合はそのことを報告してください。

- $ 1\ \leq\ i\ \lt\ j\ \lt\ k\ \leq\ N $
- $ A_i\ +\ A_j\ +\ A_k\ =\ X $

## 说明/提示

### 制約

- $ 3\ \leq\ N\ \leq\ 10^6 $
- $ 1\ \leq\ X\ \leq\ 10^6 $
- $ 1\ \leq\ A_i\ \leq\ X $
- 入力される値は全て整数
 
### Sample Explanation 1

$ (i,\ j,\ k)\ =\ (1,\ 3,\ 4) $ は $ 1\ \leq\ i\ \lt\ j\ \lt\ k\ \leq\ N $ かつ $ A_i\ +\ A_j\ +\ A_k\ =\ 1\ +\ 5\ +\ 10\ =\ 16\ =\ X $ を満たします。

## 样例 #1

### 输入

```
5 16
1 8 5 10 13```

### 输出

```
1 3 4```

## 样例 #2

### 输入

```
5 20
1 8 5 10 13```

### 输出

```
-1```

## 样例 #3

### 输入

```
10 100000
73766 47718 74148 49218 76721 31902 21994 18880 29598 98917```

### 输出

```
4 6 8```

# 题解

## 作者：Katyusha_01 (赞：28)

起猛了，当成卡常题了。

首先我们不难想到一个 $O(n^2)$ 的做法，从前往后扫 $j$，用 $bool$ 数组记录 $i$ 的可能值，然后枚举 $k$，算出 $i$ 的对应值判断是否存在即可。

不难发现上述过程可以用 `bitset` 优化，还是扫 $j$，将所有 $X - A_k$ 在 $suf$ 中标记出来，将所有 $A_i$ 在 $per$ 中标记出来，然后判断一下 $X - A_k - A_j$，即 $suf>>A_j$ 在 $per$ 中是否出现即可

上述做法写完后多半是过不了的（手写能冲过去？），考虑优化：

显然，排序不影响求解（找到对应值然后重新在原序列中找出来即可），那么我们钦定 $A_i \le A_j \le A_k$，那么 `bitset` 中只需要查小于等于 $min(A_j,X-2A_j)$，的 $A_i$ 即可，这样使用手写 `bitset` 即可减少至少 $3$ 倍的常数，此时就能够通过此题了。时间复杂度 $O(nX/3w)$，跑不满，跑满也能跑其实。

我在代码中还加了如下常数优化：

- $2A_j\le X$
- 使用 $w$ 个 `bitset` 以便快速处理右移中的错位问题

借此达到了 $558ms$ 的好成绩，构造极限数据也只在本机跑了 $718ms$（即便位运算次数高达 $2 \times 10^9$）。

[提交记录](https://atcoder.jp/contests/arc185/submissions/58796443)

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(3)
#define int unsigned long long
using namespace std;
int a[1000011],b[64][1000011];
void Ta(int x)
{
	a[x >> 6ull] |= (1ull << (x & 63ull));
}
void Tb(int x)
{
	for(int i = 0;i < 64 && i <= x;i++)
		b[i][(x - i) >> 6ull] |= (1ull << ((x - i) & 63ull));
}
void Fa(int x)
{
	if(a[x >> 6ull] & (1ull << (x & 63ull)))
		a[x >> 6ull] ^= (1ull << (x & 63ull));
}
void Fb(int x)
{
	for(int i = 0;i < 64 && i <= x;i++) if(b[i][(x - i) >> 6ull] & (1ull << ((x - i) & 63ull)))
		b[i][(x - i) >> 6ull] ^= (1ull << ((x - i) & 63ull));
}
int n,m;
int e[1000011],s[1000011];
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin >> n >> m;
	for(int i = 1;i <= n;i++)
		cin >> e[i],s[i] = e[i];
	sort(s + 1,s + n + 1);
	for(int i = 1;i <= n;i++)
		Tb(m - s[i]);
	int sx = 0,sy,sz;
	for(int i = 1;!sx && i <= n;i++) if(2 * s[i] <= m)
	{
		if(s[i] == s[i - 1] && s[i] == s[i + 1] && s[i] == s[i + 2])
			continue;
		if(s[i] != s[i + 1])
			Fb(m - s[i]);
		if(i > 1)
			Ta(s[i - 1]);
		int y = s[i],k = min(s[i],m - 2ull * s[i]) + 1ull;
		int w = (k + 63ull) >> 6ull;
		int x = (y >> 6ull),f = (y & 63ull);
		int vl = 0;
		for(int l = 0,r = x;l < w;l++,r++)
			vl |= (a[l] & b[f][r]);
		if(vl)
		{
			for(int j = 0;j < w;j++) if(a[j] & b[f][x + j])
			{
				int S = a[j] & b[f][x + j];
				for(int d = 0;d < 64ull;d++) if(S & (1ull << d))
					sx = (64ull * j) + d,sy = s[i],sz = m - sx - sy;
				break;
			}
		}
	}
	if(!sx)
	{
		cout << -1;
		return 0;
	}
	multiset<int> S;
	S.insert(sx),S.insert(sy),S.insert(sz);
	for(int i = 1;i <= n;i++)
	{
		auto j = S.find(e[i]);
		if(j != S.end())
		{
			cout << i << " ";
			S.erase(j);
		}
	}
	return 0;
}
```

---

## 作者：Super_Cube (赞：3)

# Solution

题意：在序列中找三个数使其和为 $X$。

先枚举其中一个数为 $i$，那么就是在序列中再找两个数 $j,k$ 使其和 $j+k=X-i$。注意到这是个卷积形式，也就是说把 $a$ 序列中的元素放入桶中，对桶进行自卷积之后若桶中某位置有值则说明该值是可以被原序列中的某两个数加和凑出来。于是对于 $X-i$ 在自卷积后的桶中有值的情况进去暴力找到一种方案并输出就结束了。否则该序列无解。

卷积用 FFT 或 NTT 均可。因为避免了大量取模运算，或许 FFT 在该题中效率更高？

---

## 作者：xwh_Marvelous (赞：2)

记 $f_i = \sum_{j=1}^n [a_j=i]$。一种想法是先处理出用两个数组成数字 $i$ 的方案数，记作 $g_i$。那么就可以算出 $3ans=\sum_{i=1}^ng_{x-a_i}-f_{x-2a_i}+[3a_i=x]$。

难点在于求 $g_i$，注意到 $2g_i=\sum_{j+k=i}f_i\times f_k-f(i/2)[i\bmod 2=0]$。左边是多项式卷积的形式，直接上 FFT，如果担心精度可使用 int128 使用大模数去做 NTT 即可。

---

## 作者：Jerrywang09 (赞：1)

笔者建议先完成 [AT_abc392_g](https://atcoder.jp/contests/abc392/tasks/abc392_g)，算得上是此题的弱化版。

考虑生成函数。设 $a$ 中含有 $c(i)$ 个 $i$，则生成函数为
$$
g(a)=\sum_{i=1}^n c(i)x^i
$$
然后，$g(a)^2$ 中 $x^s$ 项的系数 $f(s)$ 的组合意义是：选两个下标 $i,j$ 使 $a_i+a_j=s$ 的方案数，**并没有要求 $i<j$**。为了求得保证 $i<j$ 的方案数，考虑
$$
f(a)\leftarrow  \frac 1 2 (f(a)-c(\frac a 2))
$$

回归本题，考虑枚举三个数中的一个，设其下标为 $k$，$y=a_k$。$x$ 的定义同题面中。则现在只需要找 $i,j$ 使得 $a_i+a_j=x-y$，$(i,j)$ 的方案数已求。但是，是不是没有排除 $i=k$ 或 $j=k$ 的情况？为了除去这些情况，我们只需要知道 $c(x-2y)$。注意一下 $x=3y$ 的情况。

如果发现此时的方案数还 $>0$，则继续枚举 $i$，找 $j\neq i$ 且 $j\neq k$。按顺序输出即可。

其实我不会写 FFT。AtCoder Library 真是太好了。
```cpp
// [ARC185C] Sum of Three Integers
#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <atcoder/convolution>
#define ll long long
#define rep(i, s, t) for(int i=s; i<=t; ++i)
#define debug(x) cerr<<#x<<":"<<x<<endl;
const int N=1000010;
using namespace std;
char buf[1<<21], *p1=buf, *p2=buf;
#define gc() (p1==p2 && (p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
inline int read()
{
    int x=0, f=1; char c=gc();
    while(c<'0' || c>'9') c=='-' && (f=-1), c=gc();
    while('0'<=c && c<='9') x=(x<<3)+(x<<1)+c-'0', c=gc();
    return x*f;
}

int n, x, a[N]; vector<ll> c(N), f(N);
vector<int> vec[N];
bool solve(int i)
{
    rep(j, 1, n) if(j!=i && x>a[i]+a[j])
    {
        for(int k:vec[x-a[i]-a[j]])
        {
            if(k!=i && k!=j)
            {
                int ans[]={i, j, k};
                sort(ans, ans+3);
                printf("%d %d %d", ans[0], ans[1], ans[2]);
                return 1;
            }
        }
    }
    return 0;
}

int main()
{
    n=read(), x=read();
    rep(i, 1, n)
    {
        a[i]=read();
        c[a[i]]++; vec[a[i]].push_back(i);
    }
    f=atcoder::convolution(c, c);
    rep(i, 1, x)
    {
        if(i%2==0) f[i]-=c[i>>1];
        f[i]>>=1;
    }
    rep(i, 1, n) if(x>a[i])
    {
        int y=a[i], cur=f[x-y];
        if(x-y-y>0)
        {
            if(x-y-y==y) cur-=c[y]-1;
            else cur-=c[x-y-y];
        }
        if(cur)
        {
            if(solve(i)) return 0;
        }
    }
    puts("-1");

    return 0;
}
```

---

## 作者：Nt_Tsumiki (赞：1)

考虑先算出来能被两个不同的数 $a+b$ 表示出来的数有哪些，以及方案数，这个可以通过 NTT 去计算。

然后枚举去枚举 $c$ 去 check 是否有解包含 $c$，然后 $O(n)$ 暴力查找即可。

check 的话，需要查看原序列中 $c$ 是否存在，以及 $X-c$ 是否能被拼接，还要注意假如 $X-c$ 被拼接的方案只有一种并且是被 $c$ 所拼接的那么是不存在包含 $c$ 的解的。

查找难点在于一些取等的特判上，嫌麻烦可以像我一样大力分讨。

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>

#define N 1000005
#define LL long long
#define MOD 998244353

inline int R() {
    int x=0; bool f=0; char c=getchar();
    while (!isdigit(c)) f|=(c=='-'),c=getchar();
    while (isdigit(c)) x=x*10+c-'0',c=getchar();
    return f?-x:x;
}

template<typename T>
void W(T x,int op=0) {
    if (x<0) return putchar('-'),W(-x,op);
    if (x>9) W(x/10); putchar(x%10+'0');
    if (op) putchar(op==1?' ':'\n');
}

using namespace std;
int n,m,a[N],t[N];

LL quickpow(LL a,int k) {
    LL res=1;
    while (k) {
        if (k&1) res=res*a%MOD;
        a=a*a%MOD,k>>=1;
    }
    return res;
} LL G=3,iG=quickpow(G,MOD-2);

int to[N<<2];

void NTT(vector<LL> &A,int n,int op) {
    for (int i=0;i<n;i++)
        if (i<to[i]) swap(A[i],A[to[i]]);
    for (int i=1;i<n;i<<=1) {
        LL wk=quickpow(op==1?G:iG,(MOD-1)/(i<<1));
        for (int j=0;j<n;j+=(i<<1)) {
            LL w=1;
            for (int k=0;k<i;k++,w=w*wk%MOD) {
                LL pe=A[j+k],po=w*A[i+j+k]%MOD;
                A[j+k]=(pe+po)%MOD,A[i+j+k]=(pe-po+MOD)%MOD;
            }
        }
    }
}

vector<LL> operator*(vector<LL> f,vector<LL> g) {
    int n=f.size()+g.size()-1,m=1,K=0;
    while (m<=n) m<<=1,K++;
    for (int i=0;i<m;i++)
        to[i]=(to[i>>1]>>1)|((i&1)<<(K-1));
    f.resize(m); g.resize(m);
    NTT(f,m,1); NTT(g,m,1);
    for (int i=0;i<m;i++) f[i]=f[i]*g[i]%MOD;
    NTT(f,m,-1); int invm=quickpow(m,MOD-2);
    for (int i=0;i<m;i++) f[i]=f[i]*invm%MOD;
    return f;
}

vector<int> pos[N];

void print(int a,int b,int c) {
    int mn=min({a,b,c}),mx=max({a,b,c});
    b=a+b+c-mn-mx;
    W(mn,1),W(b,1),W(mx,2);
    exit(0);
}

int main() {
    n=R(),m=R();
    for (int i=1;i<=n;i++) t[a[i]=R()]++,pos[a[i]].push_back(i);
    vector<LL> f(m+1),g(m+1);
    for (int i=1;i<=m;i++) f[i]=g[i]=t[i];
    f=f*g; f.resize(m+1);
    for (int i=1;i<=m;i++)
        if (2*i<=m) f[2*i]-=t[i];
    for (int i=1;i<=m;i++) f[i]=f[i]/2;
    for (int i=1;i<=m;i++)
        if (t[i] and f[m-i]) {
            if (m-i>i and f[m-i]==1 and t[m-i-i]) continue;
            for (int j=1;j<=m-i;j++)
                if (j==m-i-j and t[j]>=2) {
                    if (i==j) {
                        if (t[i]<3) continue;
                        print(pos[i][0],pos[i][1],pos[i][2]);
                    } else print(pos[i][0],pos[j][0],pos[j][1]);
                } else if (t[j] and t[m-i-j]) {
                    if (i==j) {
                        if (t[i]<2) continue;
                        print(pos[i][0],pos[i][1],pos[m-i-j][0]);
                    } else if (i==m-i-j) {
                        if (t[i]<2) continue;
                        print(pos[i][0],pos[i][1],pos[j][0]);
                    } else print(pos[i][0],pos[j][0],pos[m-i-j][0]);
                }
        }
    W(-1,2);
    return 0;
}
```

---

## 作者：ax_by_c (赞：0)

这场 ARC 我要是打了就爽了，E 比较水，C 是板题，D 我也能自己想出来，是不是能 AK 啊/yiw

这种板题真有紫吗？哦卷积模板是紫，那没事了。

考虑枚举其中一个数，设其值为 $x$，那么只需判断是否存在另外两个数的和为 $X-x$，若存在就能暴力找出解。

显然考虑卷积，设 $x$ 出现了 $cnt_x$ 次，将 $cnt$ 与 $cnt$ 做卷积可得到 $ss'$，令 $ss_i=\frac{ss'_i-cnt_{\frac{i}{2}}}{2}$，那么 $ss_x$ 即为选择两个不同数之和为 $x$ 的方案数。

删去 $x$ 后选择另外两个数的和为 $X-x$ 的方案数即为 $ss_{X-x}-cnt_{X-2x}+[3x=X]$。

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace ax_by_c{
typedef long long ll;
typedef long double db;
const db PI=acos(-1.0);
const int N=4e6+5;
namespace Bpoly{
    struct P{
        db x,y;
    };
    P operator + (P a,P b){
        return {a.x+b.x,a.y+b.y};
    }
    P operator - (P a,P b){
        return {a.x-b.x,a.y-b.y};
    }
    P operator * (P a,P b){
        return {a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x};
    }
    int pos[N];
    void fft(int n,P* a,int typ){
        for(int i=0;i<n;i++){
            pos[i]=(pos[i>>1]>>1)|((i&1)*(n>>1));
            if(i<pos[i])swap(a[i],a[pos[i]]);
        }
        for(int len=2;len<=n;len<<=1){
            P w={cos(PI*2.0/len),sin(PI*2.0/len)*typ};
            for(int i=0;i<n;i+=len){
                P W={1,0};
                for(int j=0;j<(len>>1);j++,W=W*w){
                    P x=a[i+j],y=a[i+j+(len>>1)]*W;
                    a[i+j]=x+y,a[i+j+(len>>1)]=x-y;
                }
            }
        }
        if(typ==-1)for(int i=0;i<n;i++)a[i].x/=db(n),a[i].y/=db(n);
    }
    P a[N];
    void cvlt_fft(int n,ll *x,int m,ll *y,ll *z){
        int g=1;
        while(g-1<n+m)g<<=1;
        for(int i=0;i<g;i++)a[i].x=x[i],a[i].y=y[i];
        fft(g,a,1);
        for(int i=0;i<g;i++)a[i]=a[i]*a[i];
        fft(g,a,-1);
        for(int i=0;i<=n+m;i++)z[i]=(ll)(a[i].y/2.0+0.5);
    }
}
int n,m,a[N];
ll cnt[N],ss[N];
void main(){
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]),cnt[a[i]]++;
    Bpoly::cvlt_fft(m,cnt,m,cnt,ss);
    for(int i=1;i<=n;i++)ss[a[i]*2]--;
    for(int i=1;i<=m;i++)ss[i]>>=1;
    for(int i=1;i<=n;i++){
        ll k=ss[m-a[i]];
        if(a[i]<=m-a[i]){
            k-=cnt[m-a[i]-a[i]];
            if(m-a[i]-a[i]==a[i])k++;
        }
        if(k){
            vector<int>ans;
            ans.push_back(i);
            cnt[a[i]]--;
            for(int j=1;j<=n;j++){
                if(j==i)continue;
                cnt[a[j]]--;
                if(a[j]<=m-a[i]&&cnt[m-a[i]-a[j]]){
                    ans.push_back(j);
                    for(int k=1;k<=n;k++){
                        if(k==i||k==j)continue;
                        if(a[k]==m-a[i]-a[j]){
                            ans.push_back(k);
                            sort(ans.begin(),ans.end());
                            for(auto it:ans)printf("%d ",it);
                            return ;
                        }
                    }
                }
                cnt[a[j]]++;
            }
        }
    }
    puts("-1");
}
}
int main(){
    ax_by_c::main();
    return 0;
}
```

---

## 作者：鲤鱼江 (赞：0)

很萌的题。

发现可套路地枚举其中一个数，然后看一下剩下的数是否能凑出来所需的和，瓶颈在此，可以 NTT 优化卷积，细节不多。

其实没必要大模数 NTT 或者 FFT。

拿到手可以先尝试去重，这个是容易的，因为如果最后选的数有相同的，那么剩下的那个数是唯一的。

综上去重，发现 NTT 的系数不会超过 $10^6$，选用 $998244353$ 作为模数即可。

其实赛后听到 NTT 那一瞬间就会了。

```cpp
#include<bits/stdc++.h>

using namespace std;

namespace Fread {
	const int SIZE=1<<21;char buf[SIZE],*S,*T;
	inline char getchar() {if(S==T){T=(S=buf)+fread(buf,1,SIZE,stdin);if(S==T)return '\n';}return *S++;}
}
namespace Fwrite {
	const int SIZE=1<<21;
	char buf[SIZE],*S=buf,*T=buf+SIZE;
	inline void flush(){fwrite(buf,1,S-buf,stdout);S=buf;}
	inline void putchar(char c){*S++=c;if(S==T)flush();}
	struct POPOSSIBLE{~POPOSSIBLE(){flush();}}ztr;
}
#define getchar Fread :: getchar
#define putchar Fwrite :: putchar
namespace Fastio{
	struct Reader{
	    template<typename T>
    	Reader& operator >> (T& x) {
        	char c=getchar();T f=1;
        	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}x=0;
        	while(c>='0'&&c<='9'){x=x*10+(c-'0');c=getchar();}x*=f;
	        return *this;
    	}
	    Reader(){}
	}cin;
	struct Writer{
	    template<typename T>
	    Writer& operator << (T x) {
	        if(x==0){putchar('0');return *this;}
	        if(x<0){putchar('-');x=-x;}
	        static int sta[45];int top=0;
	        while(x){sta[++top]=x%10;x/=10;}
	        while(top){putchar(sta[top]+'0');--top;}
	        return *this;
    	}
    	Writer& operator << (char c) {putchar(c);return *this;}
    	Writer(){}
	}cout;
}
#define endl '\n'
#define cin Fastio :: cin
#define cout Fastio :: cout

const int g=3;
const int mod=998244353;
const int invg=(mod+1)/3;
struct modint {
    int val;
    static int norm(const int& x) { return x < 0 ? x + mod : x; }
    modint inv() const {
        int a = val, b = mod, u = 1, v = 0, t;
        while (b > 0) t = a / b, swap(a -= t * b, b), swap(u -= t * v, v);
        return modint(u);
    }
    modint() : val(0) {}
    modint(const int& m) : val(norm(m)) {}
    modint(const long long& m) : val(norm(m % mod)) {}
    modint& operator+=(const modint& o) { return val = (1ll * val + o.val) % mod, *this; }
    modint& operator-=(const modint& o) { return val = norm(1ll * val - o.val), *this; }
    modint& operator*=(const modint& o) { return val = static_cast<int>(1ll * val * o.val % mod), *this; }
    modint operator-(const modint& o) const { return modint(*this) -= o; }
    modint operator+(const modint& o) const { return modint(*this) += o; }
    modint operator*(const modint& o) const { return modint(*this) *= o; }
};

const int N=2e6+10+5e5;
int rev[N],n,m,s,a[N],cnt[N],maxx,X,Y,Z;
inline void GetRev(const int lim){int bit=log2(lim)-1;for(int i=0;i<lim;++i) rev[i]=((rev[i>>1]>>1)|((i&1)<<bit));}
inline int CalRev(const int len){int lim=1;for(;lim<=len;lim<<=1);GetRev(lim);return lim;}
inline modint expow(modint x,int y){modint res=1;for(;y;y>>=1){if(y&1)res*=x;x*=x;}return res;}

struct Poly{
	modint a[N];
	modint& operator [](const int x){return a[x];}
	void NTT(const int limit,const int type){
		for(int i=0;i<limit;++i) if(i<rev[i]) swap(a[i],a[rev[i]]);
		for(int i=1;i<limit;i<<=1){
			modint Gn=expow(type==1?g:invg,(mod-1)/(i<<1));
			for(int j=0;j<limit;j+=(i<<1)){
				modint G=1;
				for(int k=0;k<i;++k,G*=Gn){
					modint x=a[j+k],y=a[i+j+k]*G;
					a[j+k]=x+y;a[i+j+k]=x-y;
				}
			}
		}
		if(~type) return ;
		modint inv=expow(limit,mod-2);
		for(int i=0;i<limit;++i) a[i]*=inv;
	}
}x,y;

inline void getAns(){
	int i=0,j=0,k=0;
	if(X+Y+Z!=s) return ;
	for(int l=1;l<=n;++l){
		if(!i&&X==a[l]){i=l;continue;}
		if(!j&&Y==a[l]){j=l;continue;}
		if(!k&&Z==a[l]){k=l;continue;}
	}
	if(i>j) swap(i,j);
	if(i>k) swap(i,k);
	if(j>k) swap(j,k);
	cout<<i<<' '<<j<<' '<<k<<endl;
	if(!i||!j||!k) exit(1);
	exit(0);
}

int main(){
	cin>>n>>s;
	for(int i=1,z;i<=n;++i){cin>>z;++cnt[z];y[z]=x[z]=1;maxx=max(maxx,z);a[i]=z;}
	for(int i=1;i<=maxx;++i){
		if(cnt[i]<=1) continue;
		if(i*3!=s&&2*i<=s&&cnt[s-2*i]){X=s-2*i;Y=i;Z=i;}
		if(cnt[i]>=3&&s==3*i) X=Y=Z=i;
	}
	if(X) getAns();
	++maxx;int lim=CalRev(maxx<<1);
	x.NTT(lim,1);for(int i=0;i<lim;++i) x[i]*=x[i];x.NTT(lim,-1);
	for(int i=1;i<maxx;++i) if(cnt[i]) x[2*i]-=1;
	for(int i=1;i<=n;++i){
		if(a[i]<=s){
			if(x[s-a[i]].val&&((2*a[i]>s)||(x[s-a[i]].val>2*y[s-2*a[i]].val))){
				X=a[i];--cnt[X];
				for(int j=1;j<=maxx;++j) if(s>=a[i]+j&&cnt[j]&&cnt[s-j-a[i]]){Y=j;Z=s-j-a[i];getAns();}
			}
		}
	}
	cout<<-1<<endl;
	return 0;
}
```

---

