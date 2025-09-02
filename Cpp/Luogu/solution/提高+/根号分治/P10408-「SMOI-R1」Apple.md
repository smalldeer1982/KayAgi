# 「SMOI-R1」Apple

## 题目背景

**为了卡掉错误算法，我们把时限改为 680ms。**

## 题目描述

LAR 有 $2^n$ 个苹果，苹果用 $0$ 到 $2^n - 1$ 编号，编号为 $i$ 的苹果的价值是 $v_i$。

如果 $A\operatorname{or}B=A$，那么可以说 $A$ 包含 $B$（$\operatorname{or}$ 是按位或）。

因为 LAR 的苹果太多了，所以他不知道如何挑选苹果。他想进行一些操作，方便他吃苹果。

总共有两种操作，共 $q$ 个操作：

- $1\ S$ ，询问所有编号被 $S$ 包含的苹果的价值总和。
- $2\ S\ A$ ，改变编号为 $S$ 的苹果的价值为 $A$（将 $v_S$ 改为 $A$）。

## 说明/提示

### 样例解释
初始时 $v=[1,2,3,2]$。

第一个操作时询问所有编号被 $2$ 包含的苹果的价值总和。被 $2$ 包含的数为 $0,2$，所以答案为 $v_0 + v_2=4$。

第二个操作是把 $v_0$ 改为 $4$，此时 $v=[4,2,3,2]$。

第三个操作时询问所有编号被 $2$ 包含的苹果的价值总和。被 $2$ 包含的数为 $0,2$，所以答案为 $v_0 + v_2=7$。

第四个操作是把 $v_3$ 改为 $1$，此时 $v=[4,2,3,1]$。

第五个操作时询问所有编号被 $3$ 包含的苹果的价值总和。被 $3$ 包含的数为 $0,1,2,3$，所以答案为 $v_0 + v_1 + v_2 + v_3=10$。
### 数据范围
**本题采用捆绑测试**。

subtask 编号|$n\leq$|$q\leq$|特殊性质|分值
-|-|-|-|-
$1$|$10$|$10^4$|无|$10$
$2$|$16$|$3\times 10^5$|无|$20$
$3$|$20$|$3\times10^5$|只有操作 1|$10$
$4$|$20$|$10^5$|无|$20$
$5$|$20$|$3\times10^5$|无|$40$

对于 $100\%$ 的数据，保证 $1\le n \leq 20$ ，$1 \le q\leq3\times10^5$，$0\leq v_i\leq 2^{31}-1$ 。

**提示**：本题输入量较大，请使用快读。请注意代码**常数**。

## 样例 #1

### 输入

```
2 5
1 2 3 2
1 2
2 0 4
1 2
2 3 1
1 3```

### 输出

```
4
7
10```

# 题解

## 作者：迟暮天复明 (赞：17)

[前情提要](https://www.luogu.com.cn/discuss/922526)

如果有人认为我写的比官方题解烂我直接反手撤下这篇题解。

前置知识：[高维前缀和](https://www.cnblogs.com/heyuhhh/p/11585358.html)

你考虑假设我们直接高位前缀和维护了这个子集和，那么查询操作的确是 $O(1)$ 了，但是改完一个数之后就得重新 $O(2^N)$ 跑一遍高位前缀和，然后你就寄了。

所以考虑把两个操作平衡到都用 $O(2^{N/2})$ 时间。这说明我们查询操作的时候可以枚举 $2^{N/2}$ 个数，修改的时候只能修改 $2^{N/2}$ 个数。

考虑设 $F_S$ 表示前 $N/2$ 位和 $S$ 完全一致，后 $N/2$ 位是 $S$ 子集的所有数字之和。

那么对于查询操作，我们只需要对着 $X$ 的前 $N/2$ 位枚举子集，然后累加即可。

对于修改操作，因为 $X$ 的前 $N/2$ 位是钦定的，所以就相当于在他的后 $N/2$ 位上跑高维前缀和。

总时间复杂度 $O(Q2^{N/2})$，[对时间限制的谴责](https://www.luogu.com.cn/discuss/922498)，[代码](https://www.luogu.com.cn/paste/xrmi2vsw)。

---

## 作者：myzzym (赞：10)

## 题目简述：

给你 $2^n$ 个集合和每个集合的初始值 $v_s$，有 $q$ 次操作。

- 操作一：求某个集合的子集和。

- 操作二：改变某个集合的值。

## Subtask 1

直接暴力遍历子集求子集和。

时间复杂度 $O(2^nq)$。

## Subtask 2

稍微优化一下就可以过了。

比如说当要改变的值的 $1$ 的个数大于一个值时就遍历超集，给每个超集都更新一遍，到求答案时只要遍历当前集合中 $1$ 的个数小于等于那个值的子集并累加进答案就可以了。

可能还有别的优化。

## Subtask 3

特殊性质：只有操作 $1$。（说实话这个点就是子集 dp 的模板，感兴趣的可以去了解一下，以下为简略概括）。

所以我们只要预处理出每个集合的子集和就可以了。

设 $S(s,i)=\{v_x|x\sube s,s\oplus x \le 2^i\}$，表示只有第 $i$ 位以及更低位与 $s$ 不同的 $x$ 的子集的值的和（包括集合 $s$）。

有 

$S(s,i)=\begin{cases}
v_s&i=0\\
S(s,i-1)&\textup{\textmd 第 i 位为 0}\\
S(s,i-1)+S(s\oplus 2^i,i-1)&\textup{\textmd 第 i 位为 1}
\end{cases}
$

只要递推出 $S(s,n)$ 就求出 $s$ 的子集和了。

显然，时间复杂度为 $O(2^nn)$。

### code
```cpp
n = read();
q = read();
alls = (1 << n);
for(ll i = 0; i < alls; i++)
{
	ll v = read();
	p[i] = v;
}
for(ll j = 1; j < alls; j <<= 1)
	for(ll k = 0; k < alls; k++)
		if(k & j)
			p[k] = p[k] + p[k - j];
while(q--)
{
	ll opt, s;
	opt = read(), s = read();
	printf("%lld\n", p[s]);
}
```
## Subtask 4

把询问分块，每个块内询问一次就遍历一次块内的修改操作，一个块结束后再子集 dp 一次。

把块长设为 $\sqrt{2^nn}$ 的时间复杂度为 $O(q\sqrt{2^nn})$。
## Subtask 5

我们发现可以暴力更新出所有的 $S(s,\lfloor\frac{n}{2}\rfloor)$，设要询问 $s$ 的子集和，则答案为所有的只有第 $\lfloor\frac{n}{2}\rfloor+1$ 位以及更高位与 $s$ 不同的 $s$ 的子集的 $S(x,\lfloor\frac{n}{2}\rfloor)$ 之和。

时间复杂度为 $O(q2^{\lceil\frac{n}{2}\rceil}+2^{n+\lfloor\frac{n}{2}\rfloor})$。

发现还是有点大，可以用上文的子集 dp 优化（当然不用也可以卡过），同样的，只处理到 $S(x,\lfloor\frac{n}{2}\rfloor)$ 就可以了。

时间复杂度为 $O(q2^{\lceil\frac{n}{2}\rceil}+2^n\lfloor\frac{n}{2}\rfloor)$。

### code（这里的 $\lfloor\frac{n}{2}\rfloor$ 固定为 $10$）:
```cpp
#include<cstdio>
#include<ctime>
#define ll long long
#define N 2100010
using namespace std;
ll n, q, alls;
const ll A = (1 << 10) - 1, B = A << 10;
ll p[N], val[N];
ll read()
{
	ll x = 0;
	char c = getchar();
	while(c < '0' || c > '9')c = getchar();
	while(c >= '0' && c <= '9')x = x * 10 + c - '0', c = getchar();
	return x;
}
int main()
{
	n = read();
	q = read();
	alls = (1 << n);
	for(ll i = 0; i < alls; i++)
	{
		ll v = read();
		p[i] = v;
		val[i] = v;
	}
	for(ll j = 1; j < A; j <<= 1)
		for(ll k = 0; k < alls; k++)
			if(k & j)
				p[k] = p[k] + p[k - j];
	while(q--)
	{
		ll opt;
		ll s, a;
		opt = read();
		if(opt == 1)
		{
			s = read();
			ll enb = s & B, ans = 0, ena = s & A;
			for(ll i = enb; i; i = (i - 1) & enb)
				ans += p[i | ena];
			ans += p[s & A];
			printf("%lld\n", ans);
		}
		else
		{
			s = read();a = read();
			ll m = a - val[s];
			ll ena = (s & A) ^ A;
			for(ll i = ena; i; i = (i - 1) & ena)
				p[i | s] += m;
			p[s] += m;
			val[s] = a;
		}
	}
	return 0;
}
```

---

## 作者：喵仔牛奶 (赞：4)

典。做过用这个优化 DP 的题，还是我们模拟赛 T2。

# Solution

有两种暴力：
- 一种是询问时直接枚举子集计算，修改 $\mathcal{O}(1)$，询问  $\mathcal{O}(2^n)$。
- 一种是处理出每个数子集的和，修改 $\mathcal{O}(2^n)$，询问  $\mathcal{O}(1)$。

为了均衡复杂度，取 $k=\lfloor n/2\rfloor$，低 $k$ 位用处理子集和做法，高 $(n-k)$ 位用枚举子集做法。

但是这样直接做预处理复杂度过大（$\mathcal{O}(2^n\cdot2^k)$），我们可以用 SOSDP 来预处理，只需要枚举后 $k$ 位即可。这样就做到 $\mathcal{O}(k2^n)$ 预处理。

复杂度 $\mathcal{O}(k2^n+q(2^n+2^{n-k}))=\mathcal{O}(q\cdot2^{n/2})$。

# Code

```cpp
#include <bits/stdc++.h>
#define REP(i, l, r) for (int i = (l); i <= (r); ++ i)
#define DEP(i, r, l) for (int i = (r); i >= (l); -- i)
#define fi first
#define se second
#define pb emplace_back
#define mems(x, v) memset((x), (v), sizeof(x))
using namespace std;
namespace FastIO {
    char buf[1 << 23], *p1 = buf, *p2 = buf;
#define getchar() \
    (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1 ++)
    inline int read() {
        register int sr = 0;
        register char ch = getchar(), last;
        while (ch < '0' || ch > '9') last = ch, ch = getchar();
        while (ch >= '0' && ch <= '9') sr = (sr << 1) + (sr << 3) + (ch ^ 48), ch = getchar();
        return last == '-' ? -sr : sr;
    }
}
namespace Milkcat {
	using namespace FastIO;
	typedef long long LL;
	typedef pair<LL, LL> pii;
	const int N = 2e6 + 5, mod = 1e9 + 7;
	int n, k, msk, q, op, x, y, v[N]; LL s[N];
	void upd(int x, int v) {
		REP(j, 0, msk) {
			if ((x & msk & j) != (x & msk)) continue;
			s[(x ^ (x & msk)) | j] += v;
		}
	}
	LL ask(int x) {
		LL rs = 0;
		REP(j, 0, (1 << (n - k)) - 1)
			if ((x >> k & j) == j) rs += s[j << k | (x & msk)];
		return rs;
	}
	int main() {
		n = read(), q = read(), k = n / 2, msk = (1 << k) - 1;
		REP(i, 0, (1 << n) - 1) v[i] = s[i] = read();
		REP(i, 0, k - 1) REP(j, 0, (1 << n) - 1)
			if (!(j >> i & 1)) s[j ^ 1 << i] += s[j];
		REP(i, 1, q) {
			op = read();
			if (op == 1) x = read(), cout << ask(x) << '\n';
			if (op == 2) x = read(), y = read(), upd(x, y - v[x]), v[x] = y;
		}
		return 0;
	}
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	int T = 1;
	while (T --) Milkcat::main();
	return 0;
}
```

---

## 作者：Genius_Star (赞：4)

**赛时秒了，提供一个好理解的思路。**

### 思路：

明显求的是子集和，考虑令 $dp_{x,y}$ 表示前 $\frac{n}{2}$ 位为 $x$ 且后 $\frac{n}{2}$ 位为 $y$ 的子集和。

那么在插入一个 $a_i$ 时，枚举前 $\frac{n}{2}$ 位的超集 $X$，令 $dp_{X,y} \to dp_{X,y} + a_i$；删除时减去即可。

在查询 $i$ 的子集和时，枚举后 $\frac{n}{2}$ 的子集 $Y$，答案为：

$$\sum_{Y \subseteq y} dp_{x,Y}$$

简要说明一下正确性：

- 因为若 $x_1 \subseteq x_2$，在枚举 $x_1$ 的超集时肯定将 $dp_{X_1,y_1}$ 进行更新了的。

- 此时若 $y_1 \subseteq y_2$，那么枚举 $y_2$ 的子集肯定会存在 $y_1$。

- 那么对于 $x_1 \subseteq x_2 \& y_1 \subseteq y_2$ 的贡献是计算了的。

时间复杂度为 $O((N+Q) \frac{n}{2}) = O((N+Q) \sqrt{N})$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const ll N=(1<<20)+10,M=(1ll<<10)+1;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll n,q,op,x,y;
ll a[N];
class Tree{
public:
	ll a[M][M];
	void add(ll x,ll y){
		ll X=x>>10,Y=x&1023;
		if(n<=10){
			a[0][Y]+=y;
			return;
		}
		for(int i=X;;i=(i+1)|X){
			a[i][Y]+=y;
			if(i==1023)
			  break;
		}
	}
	ll query(ll x){
		ll X=x>>10,Y=x&1023,ans=0;
		for(int i=Y;;i=(i-1)&Y){
			ans+=a[X][i];
			if(!i)
			  break;
		}
		return ans;
	}
	void clear(ll x,ll y){
		ll X=x>>10,Y=x&1023;
		if(n<=10){
			a[0][Y]-=y;
			return;
		}
		for(int i=X;i<1024;i=(i+1)|X){
			a[i][Y]-=y;
			if(i==1023)
			  break;
		}
	}
}T;
int main(){
	n=read(),q=read();
	for(int i=0;i<(1ll<<n);i++){
		a[i]=read();
		T.add(i,a[i]);
	} 
	while(q--){
		op=read(),x=read();
		if(op==1){
			write(T.query(x));
			putchar('\n');
		} 
		else{
			y=read();
			T.clear(x,a[x]);
			a[x]=y;
			T.add(x,a[x]);
		}
	}
	return 0;
}
```

---

## 作者：BreakPlus (赞：2)

~~额，感觉典题出公开赛不太合适。~~

+ 考虑一种类似根号分治的东西，对 popcount 分治，令 $B = \dfrac{n}{2}$，记 $cnt = \text{popcount}(S)$：

+ 对于询问，如果 $cnt \le B$，可以直接暴力遍历子集；如果 $cnt > B$，发现其补集较小，可以容斥：枚举其补集的一个子集，钦定包含了它。

+ 也就是说，要额外维护 $cnt \le B$ 所有超集的权值和 $c_S$。对这个东西也可以分治：若修改了一个 $cnt \le B$ 的 $S$，直接暴力枚举子集修改 $c_S$；若修改了一个 $cnt \ge B$ 的 $S$，由于维护 $c_S$ 最终是为了计算 $cnt > B$ 时的询问，发现还不如不容斥，直接枚举超集贡献上去。

+ 然后就做完了。时间复杂度 $\mathcal{O}(q2^{B} + n2^n)$

```cpp
ll n,q,v[1<<20]; LL w[1<<20],c[1<<20];
void solve(){
	n=read(), q=read();
	ll B = n/2;
	for(ll i=0;i<(1ll<<n);i++) v[i]=w[i]=read();
	for(ll i=0;i<n;i++){
		for(ll j=0;j<(1<<n);j++){
			if((j>>i)&1) continue;
			w[j^(1<<i)] += w[j];
		}
	}
	ll all = (1<<n)-1;
	for(ll i=1;i<=q;i++){
		ll op=read();
		if(op==2){
			ll x=read(), val=read(), d = val - v[x];
			if(popcnt(x) <= B){
				for(ll y=x; y>=0; y = (y?((y-1)&x):-1)) c[y] += d;
			}else{
				ll X = all ^ x;
				for(ll y=X; y>=0; y = (y?((y-1)&X):-1)) w[y^x] += d;
			}
			v[x] = val;
		}else{
			ll x=read(); 
			if(popcnt(x) > B){
				LL ans = w[x]; ll X = all ^ x;
				for(ll y=X; y>=0; y = (y?((y-1)&X):-1)) {
					if(popcnt(y) & 1) {
						ans -= c[y];
					}else ans += c[y];
				}
				printf("%lld\n", ans);
			}else{
				LL ans = 0;
				for(ll y=x; y>=0; y = (y?((y-1)&x):-1)) {
					ans += v[y];
				}
				printf("%lld\n", ans);
			}
		}
	}
	
}
```

---

## 作者：xujindong_ (赞：1)

存在复杂度更优的随机化做法，来源是 [[集训队互测 2024] 观虫我](https://qoj.ac/problem/9518)。

首先我们可以想到高低位分块的根号做法。考虑这个做法的实质是什么。现在对于每一位，有两种贡献的路径：修改时 $0\to 0,1\to 1$，查询时 $0\to 0/1,1\to 1$；修改时 $0\to 0/1,1\to 1$，查询时 $0\to 0,1\to 1$。要求最后修改对查询的贡献路径是 $0\to 0/1,1\to 1$。我们发现还存在第三种做法：修改时 $0\to 0,1\to 0/1$，查询时 $0\to 0/1,1\overset{-1}{\to}0$。其实际意义是维护 $g_S=\sum_{S\subseteq T}f_T$，则 $f_S=\sum_{S\subseteq T}(-1)^{|T|-|S|}g_T,\sum_{T\subseteq S}f_T=\sum_{T\in S}\sum_{S\in A}(-1)^{|A|-|T|}g_A=\sum_{A\in U}g_A\sum_{T\in A\cap S}(-1)^{|A|-|T|}=\sum_{T\in U}(-1)^{|T|}g_T[T\cap S=\varnothing]$。这相当于把 $\begin{bmatrix}1&1\\0&1\end{bmatrix}$ 分解为两个矩阵的乘积，有 $\begin{bmatrix}1&1\\0&1\end{bmatrix}=\begin{bmatrix}1&0\\0&1\end{bmatrix}\begin{bmatrix}1&1\\0&1\end{bmatrix}=\begin{bmatrix}1&1\\0&1\end{bmatrix}\begin{bmatrix}1&0\\0&1\end{bmatrix}=\begin{bmatrix}1&0\\1&1\end{bmatrix}\begin{bmatrix}1&1\\-1&0\end{bmatrix}$。

现在有三种做法，可以证明，对每一位随机取一种规则，最后的期望复杂度是 $O(q(\frac 43)^n)$，这是因为每次操作每一位有 $\frac 13$ 的概率被枚举两次，则每一位平均被枚举 $\frac 43$ 次。最开始对于初始值，FWT 每一位的规则可以不同。还有一个问题是这样不太稳定，只要有一次随出较多的位被枚举两次就寄了。因此离线下来，随机 $10$ 种规则，取开销最小的即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
char buf1[2097152],*ip1=buf1,*ip2=buf1;
inline int getc(){
  return ip1==ip2&&(ip2=(ip1=buf1)+fread(buf1,1,2097152,stdin),ip1==ip2)?EOF:*ip1++;
}
template<typename T>void in(T&a){
  T ans=0;
  char c=getc();
  for(;c<'0'||c>'9';c=getc());
  for(;c>='0'&&c<='9';c=getc())ans=ans*10+c-'0';
  a=ans;
}
template<typename T,typename ...Args>void in(T&a,Args&...args){
  in(a),in(args...);
}
int n,m,v[2097152],opt[300005],s[300005],x[300005],a,b,c;
long long f[2097152],minn=0x3f3f3f3f3f3f3f3f;
int main(){
  srand(time(0)),in(n,m);
  for(int i=0;i<1<<n;i++)in(v[i]),f[i]=v[i];
  for(int i=1;i<=m;i++){
    in(opt[i]);
    if(opt[i]==1)in(s[i]);
    else in(s[i],x[i]);
  }
  for(int j=1;j<=10;j++){
    int maska=0,maskb=0,maskc=0;
    long long sum=0;
    for(int i=0;i<n;i++){
      int temp=rand()%3;
      if(temp==0)maska|=1<<i;
      else if(temp==1)maskb|=1<<i;
      else maskc|=1<<i;
    }
    for(int i=1;i<=m;i++){
      if(opt[i]==1)sum+=1<<__builtin_popcount((s[i]&maska)|(~s[i]&maskc));
      else sum+=1<<__builtin_popcount((~s[i]&maskb)|(s[i]&maskc));
    }
    if(sum<minn)minn=sum,a=maska,b=maskb,c=maskc;
  }
  for(int k=1;k<1<<n;k<<=1){
    if(b&k)for(int i=0;i<1<<n;i+=k<<1)for(int j=0;j<k;j++)f[i|j|k]+=f[i|j];
    if(c&k)for(int i=0;i<1<<n;i+=k<<1)for(int j=0;j<k;j++)f[i|j]+=f[i|j|k];
  }
  for(int i=1;i<=m;i++){
    if(opt[i]==1){
      long long ans=0;
      int mask1=s[i]&b,mask2=(s[i]&a)|(~s[i]&c);
      for(int j=mask2;;j=(j-1)&mask2){
        ans+=(__builtin_parity(j&c)?-1:1)*f[j|mask1];
        if(!j)break;
      }
      cout<<ans<<'\n';
    }
    else{
      int k=x[i]-v[s[i]],mask1=(s[i]&a)|(s[i]&b),mask2=(~s[i]&b)|(s[i]&c);
      for(int j=mask2;;j=(j-1)&mask2){
        f[j|mask1]+=k;
        if(!j)break;
      }
      v[s[i]]=x[i];
    }
  }
  return 0;
}
```

---

## 作者：tzl_Dedicatus545 (赞：1)

很 Educational 啊。

对 $|S|$ 进行根号分治：

1. 查询操作：

   - $|S|\leq B$

     直接暴力做，$O(2^B)$

   - $|S|>B$

     不妨枚举 $S$ 的补集子集，进行容斥，钦定包含它们，我们记 $f_S$ 为钦定包含 $S$ 时的答案。

2. 修改操作：

   - $|S|\leq B$：对所有 $S$ 的子集，修改 $f$
   - $|S|\geq B$：我们不妨换一种思路：我们既然要解决『子集询问』，不妨直接对 $S$ 的超集询问产生贡献。

总复杂度 $q2^{n/2}$

---

## 作者：hanjinghao (赞：1)

## 核心思路：

首先，如果没有修改，那么在一开始做一遍高位前缀和，然后询问 $ O(1) $ 回答即可。

如果有修改，那么有两种暴力方式：

一、修改 $ O(1) $，然后询问的时候暴力枚举子集。

二、修改的时候暴力枚举超集，然后询问 $ O(1) $。

这两种暴力的时间复杂度都是 $ O(q \times 2 ^ n) $，无法通过。

考虑把两者结合起来——把 $ n $ 个二进制位拆成两半，记 $ s_x $ 表示**满足上一半是 $ x $ 的上一半的子集、下一半等于 $ x $ 的下一半**的下标对应的元素之和。

预处理还是用高位前缀和（只有上一半要累加，下一半不用）。

修改的时候，枚举 $ x $ 的上一半的超集，下一半固定不变，然后修改对应的 $ s $。

询问的时候，枚举 $ x $ 的下一半的子集，上一半固定不变，然后把对应的 $ s $ 加起来，即为答案。

可以发现，整个计算过程不重不漏。

时间复杂度为 $ O(q \times 2 ^ {\frac{n}{2}}) $，可以通过。

## 总结：

本题在同类型题目中并不算难，只要想到根号平衡就能顺利解决。

## 代码：
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

char buf[10000005];
int ppos, llen;

inline char gch()
{
	if (ppos == llen)
	{
		ppos = 0;
		llen = fread(buf, 1, 10000000, stdin);
	}
	if (ppos == llen) return -1;
	return buf[ppos++];
}

char obuf[10000005];
int opos;

inline void pch(char c)
{
	if (opos == 10000000)
	{
		fwrite(obuf, 1, 10000000, stdout);
		opos = 0;
	}
	obuf[opos++] = c;
}

template < typename T >
inline void read(T &x)
{
	x = 0;
	char c;
	while ((c = gch()) < 48 || c > 57)
		;
	do
		x = (x << 1) + (x << 3) + (c ^ 48);
	while ((c = gch()) > 47 && c < 58);
}

int OUTPUT[45];

template < typename T >
inline void writeln(T x)
{
	int len = 0;
	do
	{
		OUTPUT[++len] = x % 10 | 48;
		x /= 10;
	}while (x);
	while (len)
		pch(OUTPUT[len--]);
	pch('\n');
}

const int N = (1 << 20) + 5;
int v[N];
ll s[N];

int main()
{
	int n, q;
	read(n);
	read(q);
	int T = (1 << n), m = (n >> 1), B = (1 << m), C = ((T - 1) >> m) << m;
	for (int i = 0; i < T; ++i)
	{
		read(v[i]);
		s[i] = v[i];
	}
	for (int i = m; i < n; ++i)
		for (int j = 0; j < T; ++j)
			if (!((j >> i) & 1)) s[j | (1 << i)] += s[j];
	while (q--)
	{
		int opt, x;
		read(opt);
		read(x);
		if (opt == 1)
		{
			int t1 = (x >> m) << m, t2 = x & (B - 1);
			ll ans = 0;
			for (int i = t2; ;)
			{
				ans += s[t1 | i];
				if (i) i = (i - 1) & t2;
				else break;
			}
			writeln(ans);
		}
		else
		{
			int y, t1 = (x >> m) << m, t2 = x & (B - 1);
			read(y);
			for (int i = t1; ;)
			{
				s[i | t2] += y - v[x];
				if (i == C) break;
				i = (i + B) | t1;
			}
			v[x] = y;
		}
	}
	if (opos) fwrite(obuf, 1, opos, stdout);
	return 0;
}
```

---

## 作者：Shxt_Plus (赞：1)

看到这种奇怪的数据结构题，好像不能用树型数据结构，所以果断想到分块，那就很简单了。

考虑先预处理出每个块内的子集前缀和，可以用 `SOSDP` 来预处理，修改时直接块内暴力修改，查询时查询每个块内对应的子集前缀和即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long f[1050][1050],a[1<<20];
int n,q;
int main()
{
	scanf("%d%d",&n,&q);
	n=1<<n;
	for(int i=0;i<n;i++)
	{
		scanf("%lld",a+i);
		f[i>>10][i^((i>>10)<<10)]+=a[i];
	}
	for(int i=0;i<1024;i++)
	{
		for(int j=0;j<10;j++)
		{
			for(int k=0;k<1024;k++)
			if(k&(1<<j))
			{
				f[i][k]+=f[i][k^(1<<j)];
			}
		}
	}
	while(q--)
	{
		int op,s;
		long long x;
		scanf("%d%d",&op,&s);
		if(op==1)
		{
			int u=s^((s>>10)<<10),p=s>>10;
			long long ans=0;
			for(int i=p;;i=(i-1)&p)
			{
				ans+=f[i][u];
				if(i==0)break;
			}
			printf("%lld\n",ans);
		}
		else
		{
			scanf("%lld",&x);
			long long q=x;
			x=x-a[s];
			a[s]=q;
			int u=s^((s>>10)<<10),p=s>>10;
			u^=(1<<10)-1;
			for(int i=u;;i=(i-1)&u)
			{
				f[p][i^(1<<10)-1]+=x;
				if(i==0)break;
			}
		}
	}
	return 0;
}

```

---

