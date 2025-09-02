# Decoding Genome

## 题目描述

Recently a top secret mission to Mars has taken place. As a result, scientists managed to obtain some information about the Martian DNA. Now we know that any Martian DNA contains at most $ m $ different nucleotides, numbered from $ 1 $ to $ m $ . Special characteristics of the Martian DNA prevent some nucleotide pairs from following consecutively in this chain. For example, if the nucleotide 1 and nucleotide 2 can not follow consecutively in the Martian DNA, then the chain of nucleotides \[1, 2\] is not a valid chain of Martian DNA, but the chain of nucleotides \[2, 1\] can be a valid chain (if there is no corresponding restriction). The number of nucleotide pairs that can't follow in the DNA chain consecutively, is $ k $ .

The needs of gene research required information about the quantity of correct $ n $ -long chains of the Martian DNA. Your task is to write a program that will calculate this value.

## 说明/提示

In the second test case all possible three-nucleotide DNAs are permitted. Each nucleotide can take one of three values, thus in total there are 27 distinct three nucleotide DNAs.

In the third test sample we cannot make any DNA of two nucleotides — the only possible nucleotide "a" cannot occur two times consecutively.

## 样例 #1

### 输入

```
3 3 2
ab
ba
```

### 输出

```
17
```

## 样例 #2

### 输入

```
3 3 0
```

### 输出

```
27
```

## 样例 #3

### 输入

```
2 1 1
aa
```

### 输出

```
0
```

# 题解

## 作者：eee_hoho (赞：7)

直接dp好写，设$f_{i,j}$表示确定了前$i$个长度的核苷酸，其中第$i$个的核苷酸的种类是$j$的方案数，于是有如下转移方程：

$$f_{i,k}=\sum_{j=1}^mf_{i-1,j}[mp_{j,k}=1]$$

$mp_{i,j}$表示$i$后面可不可以是$j$。

然后发现这个东西可以直接矩阵加速优化，最后的答案数组就是：

$$f_{1}\times mp^{n-1}$$

其中$f_{1,i}=1$。

**Code**
``` cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
const int N = 3000;
const int p = 1e9 + 7;
using namespace std;
struct Matrix
{
    int a[61][61];
}a,f,s,c;
long long n;
int m,k,id[N + 5],ans;
char ch[3];
Matrix operator *(Matrix a,Matrix b)
{
    for (int i = 0;i <= 60;i++)  
        for (int j = 0;j <= 60;j++)
            c.a[i][j] = 0;
    for (int i = 0;i <= 60;i++)
        for (int j = 0;j <= 60;j++)
            for (int k = 0;k <= 60;k++)
                c.a[i][j] += 1ll * a.a[i][k] * b.a[k][j] % p,c.a[i][j] %= p;
    return c;
}
int main()
{
    scanf("%lld%d%d",&n,&m,&k);
    for (int i = 1;i <= 26;i++)
    {
        id['a' + i - 1] = i;
        id['A' + i - 1] = i + 26;
    }
    for (int i = 1;i <= m;i++)
        for (int j = 1;j <= m;j++)
            a.a[i][j] = 1;
    for (int i = 1;i <= k;i++)
    {
        scanf("%s",ch + 1);
        a.a[id[ch[1]]][id[ch[2]]] = 0;
    }
    for (int i = 1;i <= m;i++)
        f.a[0][i] = 1;
    n--;
    for (int i = 0;i <= 60;i++)
        s.a[i][i] = 1;
    while (n)
    {
        if (n & 1)
            s = s * a;
        a = a * a;
        n >>= 1;
    }
    f = f * s;
    for (int i = 1;i <= m;i++)
        ans = (ans + f.a[0][i]) % p;
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：NBest (赞：5)

很简单的一道矩阵加速 dp，我们发现转移式非常好推，令 $f_{o,i}$ 表示第 $i$ 对核苷酸为 $o$ 的方案数，那么不难得到：

$$f_{o,i}=\sum_{p=1}^{m} f_{o,i-1}\times [(p,o) \notin K]$$

其中 $K$ 表示题目中描述的不能存在的相邻核苷酸组成的集合。

关注到 $n\le10^{15}$，显然想到矩阵快速幂，我们假设此时 $m=3$，$K=\{(1,2),(2,3),(3,1)\}$ 那么矩阵怎么建呢？

$$\begin{vmatrix}1&1&0\\ 0&1&1\\ 1&0&1\end{vmatrix}\times \begin{vmatrix}f_{1,i-1}\\ f_{2,i-1}\\ f_{3,i-1}\end{vmatrix}=\begin{vmatrix}f_{1,i}\\ f_{2,i}\\ f_{3,i}\end{vmatrix}$$

然后用相似的方法构建矩阵即可，复杂度 $O(m^3\log n)$。
## $Code$
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=1e9+7;
ll n;
int m;
struct Matrix{
    int a[52][52];
    Matrix(){memset(a,0,sizeof(a));}
    void build(){
        int k;cin>>k;
        for(int i=1;i<=k;i++){
            char u,v;
            cin>>u>>v;
            if('a'<=u&&u<='z')u-='a';
            else u=u-'A'+26;
            if('a'<=v&&v<='z')v-='a';
            else v=v-'A'+26;
            a[v][u]=1;
        }
        for(int i=0;i<m;i++)
            for(int j=0;j<m;j++)
                a[i][j]^=1;
        return;
    }
    Matrix operator *(const Matrix &w)const{
        Matrix ans;
        for(int i=0;i<m;i++)
            for(int j=0;j<m;j++)
                for(int k=0;k<m;k++)
                    ans.a[i][j]=(ans.a[i][j]+1ll*a[i][k]*w.a[k][j]%mod)%mod;
        return ans;
    }
}a,ans;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>m;
    a.build();for(int i=0;i<m;i++)ans.a[i][0]=1;
    for(n--;n;n>>=1,a=a*a)if(n&1)ans=a*ans;
    int ANS=0;
    for(int i=0;i<m;i++)ANS=(ANS+ans.a[i][0])%mod;
    cout<<ANS;
    return 0;
}
```

---

## 作者：lichenghan (赞：4)

# Codeforces 222E 题解

## Problem

为方便输入，规定字符 $1 \sim 26$ 为 $a \sim z$ ，字符 $27 \sim 52$ 为 $A\sim Z$

你需要构造一个符合如下条件的字符串：

- 长度为 $n$ ，并且只包含字符 $1 \sim m$ $(n \le 10^{15} , m \le 52)$ 。

- 满足 $k$ 个要求，第 $i$ 个要求为 $x_i$ 后面不能是 $y_i$ （ $x_i$ 和 $y_i$ 均为字符）。

现在问你，有多少种字符串符合条件。

## Solution

先考虑 $n \le 20000$ 的情况：

这个时候，我们就很容易看出来是一个 **DP** 了。

我们令 $f_{i,j}$ 为前 $i$ 位，最后一个字符是 $j$ 的情况数。

则容易列出转移方程：

$$
f_{i,j}=\sum_{1\le k\le m\text{且不存在要求}(k,j)} f_{i-1,k}
$$

另外，$f_{1,j}=1\,\,\,\,\,\,(1\le j\le m)$ 。

那么答案就是$\sum_{i=1}^{m} f_{n,i}$ 了。时间复杂度 $O(m^2n)$ 。

然而这个做法显然通不过 $n\le10^{15}$ 的数据。

不难发现这个 DP 可以用 **矩阵优化** 的方式，将复杂度降至 $O(m^3\log n)$ 。

然后就做完了。

## Code 

```cpp
#include <iostream>
#include <cstdio>
#define int long long
using namespace std;
const int mod=1e9+7;
struct mat{//矩阵
	int x,y;
	int a[53][53];
	mat(const mat&_x){
		*this=_x;
	}
	mat(int _x=0,int _y=0,int all=0){
		x=_x;y=_y;
		for(int i=1;i<=x;i++){
			for(int j=1;j<=y;j++){
				a[i][j]=all;
			}
		}
	}
	void debug(){//方便调试
		printf("matrix of %d x %d\n",x,y);
		for(int i=1;i<=x;i++){
			printf("|");
			for(int j=1;j<=y;j++){
				printf("%4d",a[i][j]);
			}
			puts("|");
		}
		puts("");
	}
	friend mat operator*(mat s,mat t){
		mat ret(s.x,t.y,0);
		for(int i=1;i<=ret.x;i++){
			for(int j=1;j<=ret.y;j++){
				for(int k=1;k<=s.y;k++){
					ret.a[i][j]=(ret.a[i][j]+s.a[i][k]*t.a[k][j]%mod)%mod;
				}
			}
		}
		return ret;
	}
	friend mat qpow(mat x,int y){
		mat ret=x,cur=x;
		y--;
		while(y){
			if(y&1) ret=ret*cur;
			cur=cur*cur;
			y>>=1;
		}
		return ret;
	}
};
int n,m,k;
int table[200];
mat trans;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	for(int i=1;i<=26;i++) table['a'+i-1]=i;
	for(int i=27;i<=52;i++) table['A'+i-27]=i;//table是字符与数字的对应
	cin>>n>>m>>k;
	if(n==1){
		cout<<m;
		return 0;
	}
	trans=mat(m,m,1);
	char x,y;
	for(int i=1;i<=k;i++){
		cin>>x>>y;
		trans.a[table[x]][table[y]]=0;
	}
	mat first=mat(1,m,1);//first现在是只有一个字符的情况的矩阵
	first=first*qpow(trans,n-1);
	int ans=0;
	for(int i=1;i<=m;i++){
		ans+=first.a[1][i];
		ans%=mod;
	}
	cout<<ans;
}
```





---

## 作者：Resurgammm (赞：3)

$upd:$ 修改了表述错误。

> 有一些长度为 $n$ 的由 $m$ 种不同字符构成的字符串，其中有 $k$ 个约束条件，每个约束条件给定一个字符对 $(a,b)$，要求在字符串中不能有字符 $b$ 在字符 $a$ 之后出现，求满足这些约束条件的所有字符串的个数。

设 $f_{i,j}$ 为前 $i$ 个字符，第 $i$ 个字符为 $j$ 的方案数，$trans_{i,j}$ 为字符 $j$ 是否能在字符 $i$ 后面出现，有：

$$f_{i,j}=\sum_{k=1}^{m}f_{i-1,k}\times trans_{k,j}$$

时间复杂度 $O(nm^2)$，不可过。

看见这个式子很像矩阵乘法的样子，所以考虑矩阵快速幂优化，矩阵的每一位 $(i,j)$ 表示字符 $j$ 是否能在字符 $i$ 后面出现。

初始有：$f_{1,1\dots m}=1$，转移 $n-1$ 次即可，所以答案数组为：

$$f_1\times trans^{n-1}$$

$\texttt{Code:}$

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define rint register int
#define int long long
using namespace std;
namespace IO{
	#define File(x,y) freopen(#x,"r",stdin),freopen(#y,"w",stdout);
	inline int read(){
		int w=0,f=1; char ch=getchar();
		while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();}
		while(ch>='0'&&ch<='9'){w=(w<<3)+(w<<1)+(ch^48); ch=getchar();}
		return w*f;
	}
	inline void write(int x){
  		static int sta[35]; int top=0;
  		do{sta[++top]=x%10,x/=10;}while(x);
  		while(top) putchar(sta[top--]+48); puts("");
	}
}
using namespace IO;
namespace CL{
	#define fill(x,y) memset(x,y,sizeof(x))
	#define copy(x,y) memcpy(y,x,sizeof(x))
	
	const int maxn=60,mod=1e9+7;
	
	int n,m,k,ans;
	char s[2];
	namespace Matrix{
		struct matrix{
			int p[maxn][maxn];
			matrix(){fill(p,0);}
			inline void build(){for(int i=1;i<=55;i++) p[i][i]=1;}
			matrix operator *(const matrix &x)const{
				matrix res;
				for(int i=1;i<=55;i++)
					for(int j=1;j<=55;j++)
						for(int k=1;k<=55;k++)
							res.p[i][j]=(res.p[i][j]+1ll*p[i][k]*x.p[k][j]%mod)%mod;
				return res;
			}
		}trans,f;
		matrix qpow(matrix x,int y){
			matrix res; res.build();
			while(y){
				if(y&1) res=res*x;
				x=x*x;
				y>>=1;
			}
			return res;
		}
	}using namespace Matrix;
	inline int id(char x){
		if(x>='a' && x<='z') return x-96;
		if(x>='A' && x<='Z') return x-38;
	}
	
	inline int main(){
		n=read(); m=read(); k=read();
		for(int i=1;i<=m;i++)
			for(int j=1;j<=m;j++)
				trans.p[i][j]=1;
		for(int i=1;i<=k;i++){
			scanf("%s",s);
			trans.p[id(s[0])][id(s[1])]=0;
		}
		for(int i=1;i<=m;i++) f.p[1][i]=1;
		trans=qpow(trans,n-1);
		f=f*trans;
		for(int i=1;i<=m;i++) ans=(ans+f.p[1][i])%mod;
		printf("%lld\n",ans);
		return 0;
	}
}
signed main(){return CL::main();}
```

---

## 作者：Tarsal (赞：2)

看到题，感觉预处理下 $O(nm)$ 可以很容易的做到。

大概处理下每一个串作为前缀，后缀所可以选择的数的数量。

然后直接枚举，然后转移就行了。

再看一眼数据范围， $n \le 10 ^ 15$。

那没事了，很显然的矩乘的数据范围。

但是矩乘就不可以这么做了，要换一种转移方法。

你考虑把矩阵建成一个 $50 \times 50$ 的矩阵，每一位 $(a,b)$ 的意义是 $a$ 后面能否有 $b$

然后直接转移就行了。

感觉挺裸的，所以没太详细讲，不会矩乘的可以看下我的 [博客](https://www.cnblogs.com/Flash-plus/p/13908464.html)

也可以私信。

代码:

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define Rep(x, a, b) for(int x = a; x <= b; ++ x)
#define Dep(x, a, b) for(int x = a; x >= b; -- x)
#define Next(i, x) for(int i = head[x]; i; i = e[i].nxt)
int read() {
    char c = getchar(); int f = 1, x = 0;
    while(c < '0' || c > '9') { if(c == '-') f = -1; c = getchar(); }
    while(c >= '0' && c <= '9') { x = x * 10 + c - '0'; c = getchar(); }
    return x * f;
}
const int XRZ = 1e9 + 7;
char s[3]; int n, ans, p = 1, x, y;
struct node { int a[53][53], n, m; node() {memset(a, 0, sizeof(a)); }} a, b, c;
node operator * ( node &a, const node &b) {
	node c; c.n = a.n; c.m = b.m;
	Rep(i, 0, a.n - 1) Rep(j, 0, a.m - 1) Rep(k, 0, b.m - 1) c.a[i][k] = (c.a[i][k] + a.a[i][j] * b.a[j][k]) % XRZ;
	return c;
}
node qpow(int y) {
    node ans = c, base = b;
    while(y) {
        ans = ans * ans;
        if(y & n) ans = ans * base;
        y >>= 1;
    } return ans;
}
signed main() {
	n = read() - 1; int m = read(), k = read();
	a.n = 1, a.m = m, b.n = b.m = m, c.n = c.m = m;
    Rep(i, 0, m - 1) {
		a.a[0][i] = 1, c.a[i][i] = 1;
        Rep(j, 0, m - 1) b.a[i][j] = 1;
	}
    Rep(i, 0, k - 1) { scanf("%s", s);
		if(s[0] >= 'a' && s[0] <= 'z') x = s[0] - 'a';
		else x = s[0] - 'A' + 26;
		if(s[1] >= 'a' && s[1] <= 'z') y = s[ 1 ] - 'a';
		else y = s[1] - 'A' + 26; b.a[y][x] = 0;
	}
	while(p <= n) p <<= 1; p >>= 1;
    a = a * qpow(p);
    Rep(i, 0, m - 1) ans = (ans + a.a[0][i]) % XRZ;
	printf("%lld\n", ans);
	return 0;
}

```

---

## 作者：Lamb_Carp (赞：1)

## advertisement

这位靓仔，你都来看我的题解了，为什么不来[我的博客](https://www.cnblogs.com/carp-oier/p/17773167.html)看看呢。

## prologue

到底是谁查 UB 查了半天啊，原来是菜鱼啊。

## analysis

这个题目我们不难推出来这个转移方程：

$$f_{i, j} \gets \sum_{k = 1} ^ {m} f_{i - 1, k} [k \in j \text{后面的合法集合}]$$

我们看到 $n$ 的值很大，而且上面的转移方程可以考虑写成一个矩阵乘法的形式。

我们构造一个答案矩阵 $\begin{bmatrix}f_{i, 1} & f_{i, 2} & \cdots & f_{i, m}\end{bmatrix}$ 表示长度为 $i$ 

以题目中的样例一为例。

我们可以构造出来答案矩阵 $\begin{bmatrix} f_{1} & f_{2} & f_{3}\end{bmatrix}$

以及转移矩阵 $\begin{bmatrix} 1 & 0 & 1 \\ 0 & 1 & 1 \\ 1 & 1 & 1 \end{bmatrix}$

运用矩阵快速幂即可解决。

## code time

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rl register ll
#define foa(i, a, b) for(rl i=a; i < b; ++ i)
#define fos(i, a, b) for(rl i=a; i <= b; ++ i)
#define fop(i, a, b) for(rl i=a; i >= b; -- i)
#define ws putchar(' ')
#define wl putchar('\n')

template <class T> inline void waw(T x)
{
    if(x > 9) waw(x / 10);
    putchar(x % 10 ^ 48);
}

template <class T> inline void ww(T x)
{
    if(x < 0) x = ~x + 1, putchar('-');
    waw(x);
}

template <class T> inline void read(T &res)
{
    char ch = getchar(); bool f = 0; res = 0;
    for(; !isdigit(ch); ch = getchar()) f |= ch == '-';
    for(; isdigit(ch); ch = getchar()) res = (res << 1) + (res << 3) + (ch ^ 48);
    res = f ? ~res + 1 : res;
}

const ll N = 55, P = 1e9 + 7;

ll n, m, k;

unordered_map<char, ll> mp;

struct Matrix
{
    ll a[N][N];

    Matrix () { memset(a, 0, sizeof a); }

    Matrix operator *(const Matrix &x) const
    {
        Matrix res;

        foa(i, 1, N) foa(k, 1, N) foa(j, 1, N)
            res.a[i][j] = (res.a[i][j] + (a[i][k] * x.a[k][j]) % P) % P;
        
        return res;
    }
} ans, base;

inline void qmi(ll k)
{
    while(k)
    {
        if(k & 1) ans = ans * base;
        base = base * base; k >>= 1;
    }
}

int main()
{
    read(n), read(m), read(k);

    fos(i, 0, 25) mp[(char)('a' + i)] = i + 1;
    fos(i, 0, 25) mp[(char)('A' + i)] = i + 27;

    fos(i, 1, m) ans.a[1][i] = 1;

    fos(i, 1, m) fos(j, 1, m) base.a[i][j] = 1;

    fos(i, 1, k)
    {
        char str[3]; cin >> str;
        ll a, b;
        a = mp[str[0]], b = mp[str[1]];
        base.a[a][b] = 0;
    }

    qmi(n - 1);

    ll res = 0;

    fos(i, 1, m) res = (res + ans.a[1][i]) % P;

    ww(res), wl;
    return 0;
}
```

---

## 作者：lfxxx (赞：1)

考虑一个先构造一个动态规划的转移方程 $dp_{i,j} = dp_{i-1,k} \times (j,k)$ 表示前 $i$ 为以字符 $j$ 结尾的方案数，其中 $(j,k)$ 在 $j$ 字符后面可以接 $j$ 字符时为 $1$ 否则为 $0$。

注意到这个形式很像一个矩阵乘法，所以考虑将 $(j,k)$ 构造成一个矩阵，不难发现，将目前的答案排在一个 $1 \times m$ 的矩阵中后，乘上一次 $(j,k)$ 构成的矩阵就 **相当于一次转移** 因此考虑矩阵快速幂加速。

时间复杂度是 $O(m^3 \log n)$ 的。

```cpp
#include<bits/stdc++.h>
#define int long long
const int mod = 1e9+7;
#define f(x)(x<'a'?x-'A'+27:x-'a'+1)
using namespace std;
class Matrix{
public:
	int n,m;
	int a[101][101];
	Matrix(int N=100,int M=100){
		n=N,m=M;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++) a[i][j]=0;
		}
		for(int i=1;i<=n;i++) a[i][i]=1;
	}//构造单位矩阵
	Matrix operator*(const Matrix &x){
		Matrix res=(n,x.m);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=x.m;j++)
				res.a[i][j]=0;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				for(int k=1;k<=x.m;k++){
					res.a[i][k]+=(a[i][j]*x.a[j][k]%mod);
					res.a[i][k]%=mod; 
				}
			}
		}
		return res;
	}	 
}e;
Matrix qpow(Matrix A,int B){
	if(B==0) return e;
	if(B==1) return A;
	Matrix res=qpow(A,B/2);
	res=res*res; 
	if(B%2==1) res=res*A;
	return res;
}
int n,m,k;
signed main(){
	cin>>n>>m>>k;
	e.n=e.m=m;
	e=Matrix(m,m);
	Matrix base=Matrix(m,m);
	for(int i=1;i<=m;i++)
		for(int j=1;j<=m;j++)
			base.a[i][j]=1;
	for(int i=1;i<=k;i++){
		char u,v;
		cin>>u>>v;
		base.a[f(u)][f(v)]=0;
	}
	Matrix ans = Matrix(1,m);
	for(int i=1;i<=m;i++) ans.a[1][i]=1;
	ans=ans*qpow(base,n-1);
	int res=0;
	for(int i=1;i<=m;i++) res+=ans.a[1][i],res%=mod;
	cout<<res;
}
```


---

## 作者：August_Light (赞：1)

# CF222E Decoding Genome 题解

[题目传送门](https://www.luogu.com.cn/problem/CF222E)

## 题意简述

有一个长度为 $n$，值域为 $[1,m]$ 的字符串 $a$。给定 $k$ 个长度为 $2$ 的字符串，你需要保证这 $k$ 个字符串都不是 $a$ 的子串。求 $a$ 有几种可能的方案，对 $10^9+7$ 取模。

$1 \le n \le 10^{15}, 1 \le m \le 52, 0 \le k \le m^2$。

## 前置知识

- 矩阵快速幂

## 解法

$1 \le n \le 10^{15}, 1 \le m \le 52$。$n$ 这么大，$m$ 这么小。肯定是矩阵快速幂了。

设 $f_{i,j}$ 为前 $i$ 个字符，最后一个字符为 $j$ 的方案数。

$$f_{i,j} = \sum\limits_{x=1}^m [\{x,j\}\text{ is not in the } k \text{ strings}] \times f_{i-1,x}$$

边界情况：$f_{1,j} = 1$。

我们可以把 $[\{x,j\}\text{ is not in the } k \text{ strings}]$ 写成一个矩阵。

时间复杂度 $O(m^3 \log n)$。

## 代码

```cpp
#include <bits/stdc++.h>
#define memset0(a) memset(a, 0, sizeof(a))
using namespace std;
typedef long long LL;

// 省略快读快写的实现

const int MAXN = 52 + 5;
const int MOD = 1e9 + 7;

LL n, m, k;

int toInt(char c) {
    if (islower(c))
        return c - 'a' + 1;
    if (isupper(c))
        return c - 'A' + 1 + 26;
    return 114514;
}

struct Matrix {
    LL M[MAXN][MAXN];
    void clear() {
        memset0(M);
    }
    void reset() {
        clear();
        for (int i = 1; i <= m; i++)
            M[i][i] = 1;
    }
    Matrix friend operator*(Matrix A, Matrix B) {
        Matrix C; C.clear();
        for (int i = 1; i <= m; i++)
            for (int k = 1; k <= m; k++)
                for (int j = 1; j <= m; j++)
                    (C.M[i][j] += A.M[i][k] * B.M[k][j] % MOD) %= MOD;
        return C;
    }
};
Matrix expow(Matrix A, LL b) {
    Matrix ret; ret.reset();
    while (b) {
        if (b & 1)
            ret = A * ret;
        A = A * A;
        b >>= 1;
    }
    return ret;
}

Matrix A, B;

int main() {
    n = read(), m = read(), k = read();

    A.clear(); B.clear();
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= m; j++)
            A.M[i][j] = 1;
    for (int i = 1; i <= m; i++)
        B.M[i][1] = 1;

    while (k--) {
        char c1, c2; scanf("%c%c\n", &c1, &c2);
        int a = toInt(c1), b = toInt(c2);
        A.M[a][b] = 0;
    }

    B = expow(A, n-1) * B;
    LL ans = 0;
    for (int i = 1; i <= m; i++)
        (ans += B.M[i][1]) %= MOD;
    write(ans);

    return 0;
}
```


---

## 作者：Sktic (赞：0)

[CF222E Decoding Genome](https://www.luogu.com.cn/problem/CF222E)



题目：



求出符合如下条件的不同字符串个数：

>1.长度为 $n$ 。
>
>2.字符串的每一位仅由 $1\sim m$ 组成。（为方便表示每个字符，令 $\text{a}\sim\text{z}=1\sim26,\text{A}\sim\text{Z}=27\sim52$）
>
>3.给定 $k$ 个二元组 $(i,j)$ ，表示当字符串的第 $p$ 位为 $i$ 时，第 $p+1$ 位不能为 $j$ 。

其中 $1\le n\le 10^{15},1\le m\le 52,1\le k\le m^2$ 。


首先由题意可以想到一个很朴素的 $\text{dp}$ ：



设 $dp_{i,j}$ 为当前字符串长度为 $i$ ，且最后一个字符为 $j$ 时的方案数，那么就很容易得到如下的转移方程：

$$
\left\{
\begin{aligned}
&dp_{1,i}=1\\
&dp_{i,j}=\sum_{k=1}^mdp_{i-1,k}[(k,j)=0]\\
&ans=\sum_{i=1}^m dp_{n,i}
\end{aligned}
\right.
$$

时间复杂度为 $O(m^2n)$ 。



但是注意到 $1\le n\le 10^{15}$ ，考虑使用**矩阵加速**优化时间复杂度。



容易发现 $dp_{i,j}$ 仅与 $dp_{i-1,k}$ 有关，因此可以滚动数组削掉第一维。



而得出答案要进行 $m-1$ 次迭代，可以将每次得出答案的过程抽象为两个矩阵相乘。



令矩阵 $s_{i,j}$ 表示 $(i,j)$ 是否满足条件 $3$，若不满足则为 $0$ ，满足则为 $1$ 。



则迭代 $m-1$ 次可以看作是将 $s$ 矩阵自乘 $m-1$ 次。



于是最终的矩阵就是 $dp_1\times s^{m-1}$ 。



再求 $dp$ 数组的和即可。

AC Code：

```C++
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e2+10;
const int mod=1e9+7; 
typedef long long int ll;
typedef long long int ll;
struct mar
{
	int n,m;
	ll data[maxn][maxn];
};
void init(mar &x)
{
	memset(x.data,0,sizeof(x.data));
	for(int i=1;i<=x.n;i++)
		x.data[i][i]=1;
	return;
}
mar operator *(const mar &a,const mar &b)
{
	mar k;
	memset(k.data,0,sizeof(k.data));
	k.n=a.n;
	k.m=b.m;
	for(int i=1;i<=k.n;i++)
		for(int j=1;j<=k.m;j++)
			for(int t=1;t<=a.m;t++)
				k.data[i][j]=(k.data[i][j]%mod+(a.data[i][t]%mod*b.data[t][j]%mod)%mod)%mod;
	return k;
}
mar quickmarpow(mar x,ll s)
{
	mar ans;
	ans.n=x.n;
	ans.m=x.m;
	init(ans);
	while(s)
	{
		if(s&1)
			ans=ans*x;
		x=x*x;
		s=s>>1;
	}
	return ans;
}
int ctod(char c)
{
	if('a'<=c&&c<='z')
		return int(c-'a'+1);
	else
		return int(c-'A'+1+26);
}
int main()
{
	ll n,m,k;
	string s; 
	scanf("%lld%lld%lld",&n,&m,&k);
	mar q;
	q.n=q.m=m;
	for(int i=1;i<=m;i++)
		for(int j=1;j<=m;j++)
			q.data[i][j]=1;
	for(int i=1;i<=k;i++)
	{
		cin>>s;
		q.data[ctod(s[0])][ctod(s[1])]=0;
	}
	mar st,kt=quickmarpow(q,n-1);
	st.n=1;st.m=m;
	for(int i=1;i<=m;i++)
		st.data[1][i]=1;
	mar ans=st*kt;
	ll sum=0;
	for(int i=1;i<=m;i++)
		sum=(sum+ans.data[1][i])%mod;
	printf("%lld\n",sum);
	return 0;
}
```

时间复杂度 $O(m^3\log n)$ 。

---

## 作者：daniEl_lElE (赞：0)

一道经典的矩阵快速幂优化 DP 题目。

## 思路

考虑基本 $dp_{i,j}$ 表示看到第 $i$ 行，目前使用的是 $j$ 号核酸（即 $\texttt{a}\sim \texttt{z}$，$\texttt{A}\sim \texttt{Z}$）。转移条件就是 $(j,k)$ 是合法的，则 $dp_{i,k}$ 可以加入 $dp_{i-1,j}$ 的答案。

容易发现过不了 $n=10^{15}$ 的数据，容易发现我们可以把转移转换成一个矩阵，使用矩阵快速幂优化即可。

复杂度 $\Theta(m^3\log n)$。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
#define mid ((l+r)>>1)
using namespace std;
const int mod=1e9+7;
struct mtx{
	int a[65][65];
};
mtx mul(mtx x,mtx y){
	mtx z;
	for(int i=1;i<=60;i++) for(int j=1;j<=60;j++) z.a[i][j]=0;
	for(int k=1;k<=60;k++) for(int i=1;i<=60;i++) for(int j=1;j<=60;j++) z.a[i][j]=(z.a[i][j]+x.a[i][k]*y.a[k][j])%mod;
	return z;
}
mtx qp(mtx a,int b){
	mtx ans;
	for(int i=1;i<=60;i++) for(int j=1;j<=60;j++) ans.a[i][j]=(i==j);
	while(b){
		if(b&1) ans=mul(ans,a);
		a=mul(a,a);
		b>>=1;
	}
	return ans;
}
mtx base,ori;
signed main(){
	int n,m,k;
	cin>>n>>m>>k;
	for(int i=1;i<=m;i++) for(int j=1;j<=m;j++) base.a[i][j]=1;
	for(int i=1;i<=k;i++){
		char c,d;
		cin>>c>>d;
		int C=(c>='a'&&c<='z')?c-'a'+1:c-'A'+27;
		int D=(d>='a'&&d<='z')?d-'a'+1:d-'A'+27;
		base.a[C][D]=0;
	}
	for(int i=1;i<=m;i++) ori.a[1][i]=1;
	ori=mul(ori,qp(base,n-1));
	int ans=0;
	for(int i=1;i<=m;i++) ans=(ans+ori.a[1][i])%mod;
	cout<<ans;
	return 0;
}
```

---

## 作者：xxx2022 (赞：0)

这道题显然是一道 dp。转移方程式也很好推，我们记 $f_{i,j}$ 为前 $i$ 位且第 $i$ 位为 $j$ 的 DNA 序列数量。而对于输入的字符串，我们用 $vis_{i,j}=0$ 表示第 $i$ 个字母后面不能放第 $j$ 个字母。那么转移方程式即为：

$$f_{i,j}= \sum \limits_{k=1}^{m}{f_{i-1,k} \times vis_{k,j}}$$

但是一看 $n$ 的范围 $10^{15}$，那这样的话我们就要考虑用矩阵加速来优化转移。把上面提到的 $vis$ 写成一个矩阵，而对于 $f$ 我们将 $f_{1,i}$ 初始化好再进行矩阵快速幂转移，这样转移次数是 $n-1$ 次。即：

$$ans=f \times vis^{n-1}$$

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define N 55
const int mod=1e9+7;
inline int read(){
    int f=1,w=0;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')  f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        w=(w<<1)+(w<<3)+(c^48);
        c=getchar();
    }
    return f*w;
}
int n,m,k;
bool vis[65][65];
struct matrix{
    int a[65][65];
    matrix operator *(const matrix &x)const{
        matrix ans;
        for(int i=1;i<=N;i++){
            for(int j=1;j<=N;j++){
                ans.a[i][j]=0;
                for(int k=1;k<=N;k++){
                    ans.a[i][j]=(ans.a[i][j]+a[i][k]*x.a[k][j]%mod)%mod;
                }
            }
        }
        return ans;
    }
}base;
int trans(char c){
    if(c>='a'&&c<='z'){
        return c-'a'+1;
    }else{
        return c-'A'+27;
    }
}
matrix f;
void quickpow(matrix base,int p,matrix &res){
    while(p){
        if(p&1) res=res*base;
        p>>=1;
        base=base*base;
    }
}
matrix ans;
void init(){
    for(int i=1;i<=m;i++){
        for(int j=1;j<=m;j++){
            base.a[i][j]=1;
        }
    }  
    for(int i=1;i<=N;i++){
        ans.a[i][i]=1;
    }
    for(int i=1;i<=m;i++){
        f.a[1][i]=1;
    }
}
signed main(){
    n=read();
    m=read();
    k=read(); 
    init();   
    for(int i=1;i<=k;i++){
        string s;
        cin>>s;
        int x,y;
        x=trans(s[0]),y=trans(s[1]);
//        vis[x][y]=1;
        base.a[x][y]=0;
    }   
    quickpow(base,n-1,ans);
    f=f*ans;
    int res=0;
    for(int i=1;i<=m;i++){
        (res+=f.a[1][i])%=mod;
    }
    cout<<res<<endl;
    return 0;
}
```


---

