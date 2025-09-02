# [AGC027D] Modulo Matrix

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc027/tasks/agc027_d

整数 $ N $ が与えられます。

以下の条件を満たすような $ N\ \times\ N $ 行列 $ a $ をどれか $ 1 $ つ構成してください。この問題の制約下で、必ず解が存在することが証明できます。

- $ 1\ \leq\ a_{i,j}\ \leq\ 10^{15} $
- $ a_{i,j} $ は相異なる整数である
- ある正の整数 $ m $ が存在して、上下左右に隣接する $ 2 $ つの数 $ x,y $ をどこから取り出しても、$ {\rm\ max}(x,y) $ を $ {\rm\ min}(x,y) $ で割ったあまりは $ m $ となる

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 500 $

### Sample Explanation 1

\- どの隣接した $ 2 $ つの数についても、大きい方の数を小さい数で割ったあまりが $ 3 $ となっています

## 样例 #1

### 输入

```
2```

### 输出

```
4 7
23 10```

# 题解

## 作者：小粉兔 (赞：29)

![](https://cdn.luogu.com.cn/upload/image_hosting/62nkvn0b.png)

如图所示，黑白染色后，每个黑色格子按照每个正 / 反斜对角线填上两个质数的乘积。

令 $m=1$，则白色格子上的数为相邻四个黑色格子上的数的 $\mathrm{lcm} + 1$。

稍微调整一下质数的顺序，就可以做到数不超过 $10^{15}$ 了。

时间复杂度为 $\mathcal O (n^2)$，[评测链接](https://atcoder.jp/contests/agc027/submissions/8933967)。

---

## 作者：Kinandra (赞：9)

标签: 构造

考虑把矩阵黑白染色, 为所有白色的主对角线和副对角线分配一个质数.

对于白格子, 权值定为所处的**两条对角线**的质数的积.

对于黑格子, 权值定位相邻的(不大于) $4$ 个白格子的最小公倍数 $+1$ .

这样显然满足每个元素互不相同(特判 $n=2$ 的情况), 且满足对于任意相邻的两个数, 较大数(**黑格子**)模较小数(**白格子**)为定值 $1$ .

考虑元素的最大值. $n=500$ 时我们需要 $2n=1000$ 个素数, 则每个素数都在 $10^4$ 内, 白色格子不大于 $10^8$ .

乍一看似乎黑格子的上界为 $10^{32}$ , 其实不然, 一个黑格子相邻的白格子最多处于两条不同主对角线, 两条不同副对角线, 故上界其实是 $10^{16}$ . 可以看出这个上界很松, 实际情况比这个上界小了 $2,3$ 个数量级, 可以通过.

时间复杂度 $\mathcal O(n^2\log a)$ .

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
long long a[1001][1001], prm[2003];
int vis[100005], cnt;
void euler() {
    vis[1] = 1;
    for (int i = 2; i <= 10000; ++i) {
        if (!vis[i]) prm[++cnt] = i;
        for (int j = 1; j <= cnt && i * prm[j] <= 10000; ++j) {
            vis[i * prm[j]] = 1;
            if (!(i % prm[j])) break;
        }
    }
}

long long gcd(long long x, long long y) {
    while (y ^= x ^= y ^= x %= y) void();
    return x;
}

long long lcm(long long x, long long y) {
    if (!x || !y) return x + y;
    return x / gcd(x, y) * y;
}

int main() {
    scanf("%d", &n), euler();
    if (n == 2) return puts("4 7\n23 10\n"), 0;
    for (int i = 1; i <= n; ++i)
        for (int j = (i + 1 & 1) + 1; j <= n; j += 2)
            a[i][j] = prm[(i + j) / 2] * prm[n + (i - j) / 2 + (n + 1) / 2];
    for (int i = 1; i <= n; ++i)
        for (int j = (i & 1) + 1; j <= n; j += 2)
            a[i][j] = lcm(lcm(a[i - 1][j], a[i][j - 1]),
                          lcm(a[i][j + 1], a[i + 1][j])) +
                      1;
    for (int i = 1; i <= n; ++i, puts(""))
        for (int j = 1; j <= n; ++j) printf("%lld ", a[i][j]);
    return 0;
}
```

---

## 作者：一念之间、、 (赞：6)

## 题意简述
说：给定 $n\le 500$ 让你构造一个 $n\times n$ 的矩阵，每个位置填入元素 $a_{i,j}$ 要求互不相同，且 $a_{i,j}\le 10^{15}$，你需要保证存在某正整数 $m$ 对于任意行相邻或者列相邻的两个格子，设其元素分别为 $A,B$  有 $\max(A,B) \bmod \min(A,B)=m$。

## 题解
这里提供一个和题解区大部分对角线构造不同的处理方式。

取 $m=1$，进行构造。

尝试黑白染色，构造一边（比如白色），另一边直接取最小公倍数 $+1$。

直接想法是顺序填入 $1\sim 500\times 500$，你发现对于相邻做最小公倍数会变得很大，一个想法是，手动钦定一些质因子作为相邻共有质因子，再作讨论，比如一行钦定一个大质因子 $P$，然后对于一行的第 $i$ 个白色填入 $P\times i$。

分析此时黑色格子的情况：![](https://cdn.luogu.com.cn/upload/image_hosting/3a0i5g39.png)

你可以粗略的视为是 $500^5$ 你发现绰绰有余，实际取出来由于 $P$ 大致最多可以取到 $4000$ 的样子，黑色格子最大的达到了 $4\times 10^{15}$。

稍作调整减少常数，一个方式是：把 $P$ 小的行夹在 $P$ 大的行中间，经过调整，此时最大格子来到了 $6\times 10^{14}$ 可以通过。


## 代码
```cpp
#include<bits/stdc++.h>
namespace ifzw{
#define ll long long
#define dd double
#define ull unsigned ll 
#define LL __int128
#define siz(A) ((int)A.size())
using namespace std;
char gc(){static char buf[1<<16],*s,*t;if(s==t){t=(s=buf)+fread(buf,1,1<<16,stdin);if(s==t)return EOF;}return *s++;}
#define getchar gc
ll read()
{
	char c;
	ll w=1;
	while((c=getchar())>'9'||c<'0')if(c=='-')w=-1;
	ll ans=c-'0';
	while((c=getchar())>='0'&&c<='9')ans=(ans<<1)+(ans<<3)+c-'0';
	return ans*w;
}
void pc(char c,int op)
{
	static char buf[1<<16],*s=buf,*t=buf+(1<<16);
	(op||((*s++=c)&&(s==t)))&&(fwrite(buf,1,s-buf,stdout),s=buf);
}
void wt(int x)
{
	if(x>9)wt(x/10);
	pc('0'+x%10,0);
}
void wts(int x,char op)
{
	if(x<0)pc('-',0),x=-x;
	wt(x),pc(op,0);
}
char ST;
const int xx=505;
int n;
ll gcd(ll a,ll b){return !b?a:gcd(b,a%b);}
ll lcm(ll a,ll b){return (!a||!b)?a+b:a/gcd(a,b)*b;}
ll a[xx][xx];
unordered_map<ll,int>mp;
int dx[]={1,0,-1,0},dy[]={0,1,0,-1};
const int yy=100005;
int prim[yy],vis[yy],cnt;
void pre()
{
	for(int i=2;i<yy;i++)
	{
		if(!vis[i])prim[++cnt]=i;
		for(int j=1;j<=cnt;j++)
		{
			if(i*prim[j]>=yy)break;
			vis[i*prim[j]]=1;
			if(i%prim[j]==0)break;
		}
	}
}
char ED;
int main(){
	cerr<<abs(&ST-&ED)/1024.0/1024<<"\n";
//	freopen("a.in","r",stdin);
//	freopen("a.out","w",stdout);
	pre();
	n=500;
	int m=read();
	int ty=55,L=55,R=L+n-1;
	ll ls=1;
	for(int i=1;i<=n;i++)
	{
		ls=i&1?prim[L++]:prim[R--];
		int tt=0;
		for(int j=1;j<=n;j++)
		{
			if((i+j)&1)
				a[i][j]=ls*(++tt);
		}
	}
	array<ll,3>mx;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(!((i+j)&1))
			{
				for(int k=0;k<4;k++)a[i][j]=lcm(a[i][j],a[i+dx[k]][j+dy[k]]);
				a[i][j]++;
				mx=max(mx,(array<ll,3>){a[i][j],i,j});
			}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			assert(!mp.count(a[i][j]));
			mp[a[i][j]]=1;
		}
	for(int i=1;i<=m;i++)
		for(int j=1;j<=m;j++)cout<<a[i][j]<<" \n"[j==n];
	pc('1',1);
	return 0;
}

}signed main(){return ifzw::main();}
 

```

---

## 作者：太阳起晚了呢 (赞：2)

# [AGC027D] Modulo Matrix 题解

### 题目大意

- 构造一个 $N*N$ 的矩阵, 要求:
  - 所有元素互不相同.
  - 满足 $a_{i,j} \le 10^{15}$
  - 对于任意两个相邻的数字, $\max(x,y) \bmod \ \min(x,y)$ 都相等，且均为正整数。
- 可以证明方案一定存在.

$n \le 500$

### Solution

对于一个构造题，我们一开始可以考虑手动填入，但是发现当模数不同的时候要求结果相同是非常不好处理的，于是我们猜想能不能构造一个矩阵使得这个模运算的结果都是 1 ,考虑一个五个元素的十字形，我们假设十字形的中心是这五个数中最大的，如下图。

​	$a$

$b$  $x$  $c$

​	$d$

那么我们需要构造一组$a,b,c,d,x$满足如下条件

$x=a \times k_1 +1 $

$x=b \times k_2 +1 $

$x=c \times k_3 +1 $

$x=d \times k_4 +1 $

其中 $k$ 均为正整数。

显然，如果 $a,b,c,d$ 都是互不相同的质数，并且 $x=a \times b \times c \times d+1$ 那么一定满足条件

如此就可以解决一个部分问题，再将网格黑白染色划分成这样的十字形就可以处理了，但是考虑到如果这样操作的话我们至少需要求出  $1.25 \times 10^5$ 个质数，其中 $x$ 的取值会超过 $10^{15}$，显然这种方法是不可取的。那么在这种方法的启示下，我们想到对于上述的 $a,b,c,d$ 不用单个的质数构造，每次构造时使用两个不同的质数相乘，这样 $x=\operatorname{lcm}(a,b,c,d)+1$ 采取两条对角线的方法构造的话，对于单点来说，$x$ 的增量就不是 4 个质数的乘积了，并且这需要的质数也会大大减小。

于是最后，我们对这个矩阵进行黑白染色 。并且规定白点的值为它主对角线和副对角线上对应的质数的乘积，黑点的值为上述 $x$。那么便可以在 $O(n^2)$ 的复杂度内构造出这样的矩阵。

具体代码如下

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1e6+10;
int p[maxn],tot;
bool vis[maxn];
void prework(int n)
{
    for(int i=2;i<=n;i++)
    {
        if(!vis[i]) p[++tot]=i;
        for(int j=1;j<=tot && p[j]*i<=n;j++)
        {
            vis[p[j]*i]=1;
            if(i%p[j]==0) break;
        }
    }
}
int lcm(int x,int y)
{
    return x/__gcd(x,y)*y;////
}
int n;
int a[505][505];
signed main()
{
    scanf("%lld",&n);
    if(n==2)
    {
        printf("4 7\n 23 10\n");
        return 0;
    }
    prework(1000000);
    for(int i=1;i<=n;i++)
        for(int j=(i%2==0)+1;j<=n;j+=2) a[i][j]=p[(i+j)/2]*(p[n+(i-j)/2+(n+1)/2]),a[i][0]=a[0][i]=a[n+1][i]=a[i][n+1]=1ll;
    
    for(int i=1;i<=n;i++)
        for(int j=(i%2==1)+1;j<=n;j+=2) a[i][j]=lcm(lcm(a[i-1][j],a[i][j-1]),lcm(a[i][j+1],a[i+1][j]))+1ll;
    
    for(int i=1;i<=n;i++,putchar('\n'))
        for(int j=1;j<=n;j++) printf("%lld ",a[i][j]);
    return 0;
}
```

注意求最小公倍数的时候要先除后乘，不然就会喜提 3 个点的错误

以及注意对于边界我们可以直接设成 1 这样不会对这个矩阵造成影响


---

## 作者：关怀他人 (赞：2)

### AGC 027D
#### Solution
首先把网格黑白染色，那么相同颜色的点互不影响，如果我们令$max \mod min=1$，且白点的权值都已经确定，那么黑点的权值可以设成它周围四个白点权值的$lcm+1$，对于白点的权值，因为要使黑点的权值在$10^{15}$且所有数各不相同，所以可以对于每一条主对角线和每一条副对角线各给一个素数，一个白点的权值就是所在主对角线和副对角线的权值之积。

注意要特判$n=2$的情况。
#### Code
```cpp
int n,tot;
int p[MAXM],nprime[MAXM];
ll a[MAXN][MAXN];

void Init(){
    for(int i = 2;i <= M;i++){
        if(!nprime[i]) p[++tot] = i;
        for(int j = 1;j <= tot;j++){
            if(i * p[j] > M) break;
            nprime[i * p[j]] = 1;
            if(i % p[j] == 0) break;
        }
    }
}

ll gcd(ll x,ll y){
    if(!y) return x;
    return gcd(y,x % y);
}

ll lcm(ll x,ll y){
    if(!x || !y) return x + y;
    return x / gcd(x,y) * y;
}

int main(){
    scanf("%d",&n);
    if(n == 2) return printf("4 7\n 23 10\n"), 0;
    Init();
    tot = 0;
    for(int i = 2;i <= 2 * n;i += 2){ // x + y = i
        int x = p[++tot];
        for(int j = max(1,i - n);j <= min(n,i - 1);j++)
            a[j][i - j] = x;
    }
    for(int i = (n & 1) ? 1 - n : 2 - n;i < n;i += 2){ // |x - y| = i
        int x = p[++tot];
        for(int j = 1;j <= n;j++){
            if(i + j >= 1 && i + j <= n)
                a[j][i + j] *= x;
        }
    }
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
            if(!a[i][j]) a[i][j] = lcm(lcm(a[i - 1][j],a[i][j - 1]),lcm(a[i + 1][j],a[i][j + 1])) + 1;
            printf("%lld ",a[i][j]);
            assert(a[i][j] <= 1000000000000000ll);
        }
        printf("\n");
    }
    return 0;
}
```

---

## 作者：RockyYue (赞：0)

### 题意

构造一个 $n\times n$ 的元素各不相同的矩阵 $a$，其中 $1\le a_{i,j}\le 10^{15}$，满足任意相邻两个数中大的对小的取模结果均为 $k$，$k$ 是一个非零常数，可以自己选定。

$2\le n\le 500$。

### 题解

Trick1： 若矩阵中构造只要求相邻，考虑黑白染色，同色之间互不干扰。

Trick2：若在一些数中要求 $\max/\min$，可以钦定哪些数是按 $\max$ 考虑，哪数按 $\min$ 考虑。

Trick3：使得一些乘积/幂/$\operatorname{lcm}$ 不重复，考虑质数，$\operatorname{lcm}$ 不重复考虑可以有重复质因子以减小值域。

先将矩阵黑白染色，钦定所有白格在所有相邻的两格中担任 $\max$，黑格担任 $\min$，于是一个白格上的值比周围四个黑格都要大，且对这四个值取模结果相同，即白格上的数最小为周围四个黑格上数的 $\operatorname{lcm}+k$。此时发现所有 $k$ 互不干扰，于是钦定 $k=1$。

现在问题转化为了如何使这些数互不相同。$\operatorname{lcm}$ 互不相同想到填质数，一种简单的想法是黑格从小到大填质数。这样的正确性毋庸置疑，然如此则白格违背 $a_i\le 10^{15}$ 的条件。但是 $\operatorname {lcm}$ 并非乘积，可以有相同质因子，于是考虑将黑格写成两个质数乘积的形式。

具体操作时，对于第 $i$ 条正/斜对角线选取第 $i$ 个质数，一个黑格上的值即为所在的两条对角线选取的质数之积。这样白格的值同样是四个质数的乘积 $+1$，但这些质数的值域从原来最大第 $\lceil\frac{n^2}{2}\rceil$ 个质数缩小到最大第 $n$ 个质数，满足 $a_{i,j}\le 10^{15}$ 的条件。

---

## 作者：_Vix_ (赞：0)

[原题链接](https://www.luogu.com.cn/problem/AT_agc027_d)

不太神秘的构造题。

## 分析

构造题直接讲方法。看到矩阵，首先黑白染色试一下。

那么一种可行的方案是：在白色点上放一些数，黑色点上的数是周围白点数的 $lcm+1$。这样一定保证了取模之后的结果为 $1$。

为了保证每个数都不一样，一种浅显的办法是白色点上的数填一个质数，一共需要 $\dfrac{n^2}{2}$ 个质数，矩阵的最大值是 $10^{24}$ 数量级的。怎么减小呢？对于一个点，给它的横纵坐标各赋一个质数，就只需要 $n$ 个质数，那么一个黑点周围的四个白点的 $lcm$ 最多有 $6$ 个质因子，答案是 $10^{18}$ 数量级的。感觉只差一点了，怎么减小 $lcm$ 的质因子个数呢？只需要对矩阵的对角线赋上不同的质数，那么只需要 $2n$ 个质数，质因子个数减少到了 $4$ 个，答案是 $10^{15}$ 数量级的，并且达不到这个上界，便可以通过这道题。

时间复杂度 $O(n^2)$。

## Code
```cpp
#include <bits/stdc++.h>
#define ll long long
#define Gcd __gcd
using namespace std;

const int N = 510, M = 2e5 + 10;
int n, prime[M], cnt;
ll a[N][N];
bool vis[M];

void init(int n) {
	for (int i = 2; i <= n; i++) {
		if (!vis[i]) prime[++cnt] = i;
		for (int j = 1; j <= cnt && i <= n / prime[j]; j++) {
			vis[i * prime[j]] = true;
			if (i % prime[j] == 0) break;
		}
	}
}

inline void work1(int x, int y, int v) {
	while (x <= n && y <= n) a[x][y] *= v, x++, y++;
}

inline void work2(int x, int y, int v) {
	while (x <= n && y >= 1) a[x][y] *= v, x++, y--;
}

inline ll Lcm(ll x, ll y) {
	if (!x || !y) return x + y;
	return x / Gcd(x, y) * y;
}

int main() {
	init(200000);
	scanf("%d", &n);
	if (n == 2) return puts("4 7"), puts("23 10"), 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			a[i][j] = i + j & 1;
	int t = 0;
	for (int i = 1; i <= n; i++) if (a[1][i]) t++, work1(1, i, prime[t]);
	for (int i = 2; i <= n; i++) if (a[i][1]) t++, work1(i, 1, prime[t]);
	for (int i = 2; i <= n; i++) if (a[i][n]) t++, work2(i, n, prime[t]);
	for (int i = 1; i <= n; i++) if (a[1][i]) t++, work2(1, i, prime[t]);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (!a[i][j]) a[i][j] = Lcm(Lcm(a[i - 1][j], a[i + 1][j]), Lcm(a[i][j - 1], a[i][j + 1])) + 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++)
			printf("%lld ", a[i][j]);
		puts("");
	}
	return 0;
}
```


---

## 作者：xht (赞：0)

## [Modulo Matrix](https://atcoder.jp/contests/agc027/tasks/agc027_d)

### 题意

- 你要构造一个 $n \times n$ 的矩阵 $a$，满足：
  - $a_{i,j} \in [1,10^{15}]$。
  - 所有 $a_{i,j}$ 互不相同。
  - 对于任意两个相邻的数 $x,y$，$\max(x,y) \bmod \min(x,y)$ 为定值。
- $n \le 500$。

### 题解

如下图构造：

![](http://www.xht37.com/wp-content/uploads/2020/07/62nkvn0b.png)

其中黄格子是两个质数的乘积，白格子为周围黄格子的 $\text{lcm} + 1$。

### 代码

```cpp
namespace shai {
	const int n = 1e6 + 7;
	int p[n], v[n], phi[n], miu[n];

	inline void init(int n) {
		v[1] = phi[1] = miu[1] = 1;
		for (int i = 2; i <= n; i++) {
			if (!v[i]) p[++p[0]] = v[i] = i, phi[i] = i - 1, miu[i] = -1;
			for (int j = 1; j <= p[0] && i * p[j] <= n && p[j] <= v[i]; j++)
				v[i*p[j]] = p[j],
				phi[i*p[j]] = phi[i] * (p[j] - 1 + (p[j] == v[i])),
				miu[i*p[j]] = p[j] == v[i] ? 0 : -miu[i];
		}
	}
}
using shai::p;

const int N = 507;
int n, a[N], b[N];

int main() {
	shai::init(1e4);
	rd(n);
	for (int i = 1; i <= n; i++) a[i] = p[i&1?i/2+1:n*2-i/2+1];
	for (int i = 1; i <= n; i++) b[i] = p[(i&1?n-i/2:n+i/2)+(n&1)];
	a[0] = a[n+1] = b[0] = b[n+1] = 1;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			print((i ^ j) & 1 ? 1ll * a[(i+j)/2] * a[(i+j)/2+1] * b[(n+i-j+(n&1))/2] * b[(n+i-j+(n&1))/2+1] + 1 : 1ll * a[(i+j)/2] * b[(n+i-j+(n&1))/2], " \n"[j==n]);
	return 0;
}
```

---

## 作者：takanashi_mifuru (赞：0)

想了很多愚蠢的思路。

第一个想法就是在这个棋盘上如果能够满足 $\max(A,B)=\min(A,B)+1$，那模出来就是相等的，微微尝试发现不行，因为不能有相同的。

然后发现如果顺着这个思路走下去，那我们再从一个方阵的角度来考虑，发现大数其实就是周围所有小数的最小公倍数再加一，原因显然。

然后你要求这个最小公倍数必须不重复，所以你考虑构造小数使其满足这个条件。

我们考虑最小公倍数分解质因数之后怎么做，就是取每个因子中指数最大的指数再与质数配起来再相乘对吧，那我们就让每一个大数旁边的数的质数和质数的指数不同，然后你考虑把这些预处理出来然后用。

跑一个 calc 发现我们要用到最大是 $134053$ 这个质数，考虑各种乱搞能不能让这个矩阵合法。

然后没多想直接暴力随机化乱搞，然后直接寄，随 100 次质数表都是挂的，我们考虑另辟蹊径，考虑对于一个四连通的格子应该怎么办节省能够让所有数质数组成部分不相同呢？

考虑如果每一个格子都比前面拿到不同的质数就行了，那一个质数可以用很多次吗，明显是可以的，那就相当于是我们让一个质数用的次数尽量多然后最后的最小公倍数就会尽量小。

思来想去我们发现只要小格子里面填两个质数的乘积就好了，然后你考虑怎么保证大数互不相同，就是把质数塞到对角线里面，小数直接用两条对角线上质数的乘积，然后他们取最小公倍数就不可能取到完全一样的质数，也就不可能会有重复，这样的话总共要用到 $2n$ 个质数，大概就是最大到 $2\times10^4$ 的质数，你考虑这样还不够，直接 rand 质数表，就做完了。

是很妙很牛很神仙的题。

---

## 作者：Arghariza (赞：0)

神仙构造。

因为余数相等不好构造，所以想到钦定这个余数为 $1$，比较直观的方法就是取出一些不相邻的格子，然后它们的权值为其相邻格子的 $\text{lcm}+1$。由于它们权值比较大，称其为**大格子**。

显然**最多能取 $\frac{n^2}{2}$ 个大格子**（棋盘染色取同色即可），那么每一个剩下的**小格子**其实都被大格子包围了。所以我们不用考虑它们被其它数除的余数。

你首先会想到小格子全部放上不同的质数，但是这样的话质数个数是 $O(n^2)$ 的，大概会填到 $1655131=p_{1.25\times 10^5}$。然后每个大格子是旁边 $4$ 个质数的积 $+1$，但是还有权值限制，你可能会爆炸。

我们发现，在上述构造方法中，每个**大格子**是相邻 $4$ 个质数的乘积左右。如果我们只用 $O(n)$ 以内的质数，再平衡一下，大概率是不会爆炸的。所以我们考虑如何只使用 $O(n)$ 个质数。

之所以之前的方法是 $O(n^2)$ 的，是因为你给平面上的每个小格子都分配了一个质数。于是我们考虑某些小格子都共用一个质数（即有一个公共质因子）。不难发现给**每条正/反对角线分别配 $2n$ 个不同的质数**，每个小格子取经过它的两条对角线上的质数的乘积，不难发现每个大格子的权值还是 $4$ 个质数的乘积。

再平衡一下对角线上质数大小的分布就能过了。一开始我写的是给每个对角线随机一个质数，但是好像会炸时间。实际上直接贪心即可。

[评测记录。](https://atcoder.jp/contests/agc027/submissions/38542021)

---

