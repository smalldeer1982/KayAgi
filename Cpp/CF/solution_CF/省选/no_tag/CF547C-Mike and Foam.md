# Mike and Foam

## 题目描述

　　$Mike$是$Rico$酒吧的调酒师。在$Rico$酒吧，他们将啤酒杯放在一个特殊的架子上。在$Rico$酒吧，有$n$种啤酒编号从$1$到$n$。第$i$瓶啤酒上面有$a_{i}$  毫升的泡沫。

![图片](https://cdn.luogu.org/upload/vjudge_pic/CF547C/c43ae9acd17475e499fd5b3bf27dd2db366d8814.png)

　　$Maxim$是$Mike$的老板。今天他让$Mike$回答$q$个查询。最初架子是空的。在每个操作中，$Maxim$给他一个编号$X$。如果编号为$X$的啤酒已经在架子上，那么$Mike$应该从架子上取下它，否则他应该把它放在架子上。

　　每次询问后，$Mike$应该告诉他架子的分数。他们认为货架的分数是满足$i<j$并且$gcd(a_{i},a_{j})=1$的数对$(i,j)$的个数。

　　$Mike$现在很累。所以他请你帮他处理这些操作。

## 样例 #1

### 输入

```
5 6
1 2 3 4 6
1
2
3
4
5
1
```

### 输出

```
0
1
3
5
6
2
```

# 题解

## 作者：是个汉子 (赞：11)

### Solution

一句话题意：求架子上和 $x$ 互质的数的 个数=总个数-和 $x$ 不互质的数的个数。

那么求和 $x$ 不互质的数就是经典容斥问题了。

因为所有数都能以一个 $\prod p_i^{k_i}$ 的形式表示出来，并且一个数的质因子个数最多有七个(因为 $2\cdot 3\cdot 5\cdot 7\cdot 11 \cdot 13\cdot 17 >500000$ )，所以暴力枚举质数即可。

### 代码

```c++
#include<bits/stdc++.h>
#define ll long long

using namespace std;
const int N=2e5+10,A=5e5+10,P=6;
int n,p,a[N],prime[A],lnk[N][P+5],tot[A];
bool isprime[A],vis[N];
ll ans;

inline void init(int n){
    isprime[0]=isprime[1]=true;prime[0]=0;
    for(int i=2;i<=n;i++){
        if(!isprime[i]) prime[++prime[0]]=i;
        for(int j=1;j<=prime[0]&&i*prime[j]<=n;j++){
            isprime[i*prime[j]]=1;
            if(i%prime[j]==0) break;
        }
    }
}

inline void query(int x,int op){
    for(int i=0;i<(1<<lnk[x][0]);i++){
        int now=1,cnt=0;
        for(int j=1;j<=lnk[x][0];j++)
            if(i&(1<<j-1)) now*=lnk[x][j],cnt++;
        if(cnt&1) ans-=op*tot[now];
        else ans+=op*tot[now];
    }
}

inline void update(int x,int op){
    for(int i=0;i<(1<<lnk[x][0]);i++){
        int now=1;
        for(int j=1;j<=lnk[x][0];j++)
            if(i&(1<<j-1)) now*=lnk[x][j];
        tot[now]+=op;
    }
}

int main(){
    scanf("%d%d",&n,&p);
    init(500000);
    for(int i=1,x;i<=n;i++){
        scanf("%d",&x);
        for(int j=1;j<=prime[0]&&prime[j]<=sqrt(x);j++)
            if(x%prime[j]==0){
                lnk[i][++lnk[i][0]]=prime[j];
                while(x%prime[j]==0) x/=prime[j];
            }
        if(x>1) lnk[i][++lnk[i][0]]=x;
    }
    while(p--){
        int x;
        scanf("%d",&x);
        if(!vis[x]) query(x,1),update(x,1);
        else update(x,-1),query(x,-1);
        vis[x]^=1;
        printf("%lld\n",ans);
    }
    return 0;
}
```



---

## 作者：jun头吉吉 (赞：7)

# 一道简单的$\color{red}\text{莫比乌斯反演}$题
~~看到gcd肯定是先去想莫比乌斯呀~~
首先我们先设一个$ans$，其定义是这样的：
$$ans=\sum_{i=1}^n\sum_{j=1}^n[\gcd(a_i,a_j)==1]$$
与题目要求的答案有些不一样，但很显然，这个柿子可以$O(1)$推到答案

（一下用$c_i$表示数字$i$出现的次数）

$$\text{答案}=\frac {ans-c_1} 2$$
~~挺好理解的吧~~

接下来就是我们喜(sang)闻(xin)乐(bing)见(kuang)的推柿子时间了
$$\text{令}n\text{为最大的数字}$$
$$ans=\sum_{i=1}^n\sum_{j=1}^n[\gcd(i,j)==1]\times c_i\times c_j$$
$$ans=\sum_{i=1}^n\sum_{j=1}^n\sum_{d|\gcd(i,j)}\mu(d)\times c_i\times c_j$$
$$ans=\sum_{d=1}^n\mu(d)\sum_{i=1}^{\lfloor\frac n d\rfloor}c_{id}\sum_{j=1}^{\lfloor\frac n d\rfloor}c_{jd}$$
$$ans=\sum_{d=1}^n\mu(d)(\sum_{i=1}^{\lfloor\frac n d\rfloor}c_{id})^2$$
$$\text{令}f(d)=\sum_{i=1}^{\lfloor \frac n d\rfloor}c_{id}$$
$$ans=\sum_{d=1}^n\mu(d)f(d)^2$$
因此我们可以维护$f$的值来维护$ans$

经过简单地观察我们发现，如果更改一个数，它的因数的$f$值就会发生改变，而$5\times 10^5$以内最大的因数个数才$200$个，因此暴力维护即可

一开始线型筛的复杂度为$O(n)$

预处理因数的复杂度为$O(\lfloor \frac n 1\rfloor+\lfloor \frac n 2\rfloor+\ldots \lfloor \frac n n\rfloor)≈O(n\ln(n))$

处理一个数的最大复杂度$O(200)$

```cpp
//#pragma optimize(2)
#include<bits/stdc++.h>
using namespace std;
template<typename T>
inline void read(T &x){
	x=0;char c=getchar();bool f=false;
	for(;!isdigit(c);c=getchar())f!=c=='-';
	for(;isdigit(c);c=getchar())x=x*10+c-'0';
	if(f)x=-x;
}
template<typename T ,typename ...Arg>
inline void read(T &x,Arg &...args){
	read(x);read(args...);
}
template<typename T>
inline void write(T x){
	if(x<0)putchar('-'),x=-x;
	if(x>=10)write(x/10);
	putchar(x%10+'0');
}
const int maxn=5e5+10;
bool isprime[maxn];
int tot,prime[maxn],miu[maxn];
vector<int>factor[maxn];
void init(){
	tot=0;miu[1]=1;memset(isprime,0xff,sizeof isprime);
	for(int i=2;i<maxn;i++){
		if(isprime[i])
			prime[++tot]=i,miu[i]=-1;
		for(int j=1;j<=tot&&i*prime[j]<maxn;j++){
			isprime[i*prime[j]]=false;
			if(i%prime[j])miu[i*prime[j]]=-miu[i];
			else {miu[i*prime[j]]=0;break;}
		}
	}
	for(int i=1;i<maxn;i++)
		for(int j=i;j<maxn;j+=i)factor[j].push_back(i);
}
int n,q;
bool flag[maxn];
int a[maxn],c[maxn];
long long f[maxn];
long long ans=0;
void change(int x,int v){
	for(int i=0;i<factor[x].size();i++){
		ans-=1ll*miu[factor[x][i]]*f[factor[x][i]]*f[factor[x][i]];
		f[factor[x][i]]+=v;
		ans+=1ll*miu[factor[x][i]]*f[factor[x][i]]*f[factor[x][i]];
	}
}
signed main(){
	init();
	read(n,q);
	for(int i=1;i<=n;i++)read(a[i]);
	for(int i=1;i<=q;i++){
		int x;read(x);
		if(flag[x])c[a[x]]--,change(a[x],-1),flag[x]=false;
		else if(!flag[x])c[a[x]]++,change(a[x],1),flag[x]=true;
		write((ans-c[1])/2);putchar('\n'); 
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：5)

### 题目传送门

[洛谷](https://www.luogu.com.cn/problem/CF547C)

[CF](https://www.luogu.com.cn/problem/CF547C)

### 题意

每次可以增加或者删除一个数，求这个数列中 gcd 为 $1$ 的有序二元组的数量。

### 分析

我们只需要处理加入或删除一个数字造成的影响。

先把这个数字分解质因数，然后枚举每个质因数是否选择进行容斥。

$$|\cup_{i=1}^{n}a_i|= \displaystyle\sum_{i=1}^{n}((-1)^{i-1}\displaystyle\sum_{1 \le b_1 < b_2 < \dots < b_i \le n}|a_{b_1} \cap a_{b_2} \cap \dots \cap a_{b_i}|)$$

然后我们就加上或减去其倍数的数量。

对于一个数，我们对于其所有因数都要更新。

考虑一种特殊情况，对于二元组 $(1,1)$ 会被计算两次，所以要减去所有 $1$ 的数量。

### 时间复杂度

认为加入删除 $n$ 次，最大的数为 $m$。

注意这题的 $n$，$m$ 不同阶。

枚举出所有数的倍数，时间复杂度 $O(m \ln m)$。

容斥原理的时间复杂度为 $O(n 2^{\omega(m)})$。

处理后枚举因数的时间复杂度为 $O(n m ^{\frac{1}{3}})$。

总时间复杂度为 $O(m \ln m + n  (2^{\omega(m)} + m^{\frac{1}{3}}))$。

当 $m = 500000$ 时，$2^{\omega(m)} + m^{\frac{1}{3}} = 143$，可以通过。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
template<typename T>inline void read(register T &x)
{
	static char c,p;
	c = getchar(),p = 1,x = 0;
	while(c < '0'||c > '9')
	{
		if(c == '-') p = -1;
		c = getchar();
	}
	while('0' <= c&&c <= '9')
	{
		x = (x<<3)+(x<<1)+(c^48);
		c = getchar();
	}
	x *= p;
}
template<typename T>inline void write(register T x)
{
	if(x < 0) putchar('-'),x = -x;
	if(x > 9) write(x/10);
	putchar(x%10^48);
}
#define F(i,a,b) for(register int i=a;i<=b;++i)
#define D(i,a,b) for(register int i=a;i>=b;--i)
#define ull unsigned long long
#define ll long long
#define pii pair<int,int>
#define fi first
#define se second
#define M 500010
#define N 200010
bitset<N> vis;
bitset<M> mark;
ll ans = 0;
int n,q,a[N],b[M],p[M],to[M],c[10],k,ret,m = 0,len = 0,cnt = 0;
vector<int> g[M];
void calc(int u,int t,int mu)
{
	if(!b[t]) return;
	if(u > k) ret += mu * b[t];
	else calc(u+1,t*c[u],-mu),calc(u+1,t,mu);	
}
void update(int x,int y)
{
	if(x == 1) cnt += y;
	for(auto i:g[x]) b[i] += y;
}
int calc(int x)
{
	ret = k = 0;
	for(register int u = x;u > 1;u /= to[u])
		if(!k||to[u] != c[k])
			c[++k] = to[u];
	calc(1,1,1);
	return ret; 
}
int main()
{
	read(n),read(q);
	F(i,1,n) 
	{
		read(a[i]);
		m = max(m,a[i]);
	}
	F(i,2,m)
	{
		if(!mark[i]) p[++len] = i,to[i] = i;
		F(j,1,len)
		{
			if(1ll * i * p[j] > m) break;
			mark[i * p[j]] = 1;
			to[i * p[j]] = max(to[i],p[j]);
			if(i % p[j] == 0) break;
		}
	}
	F(i,1,m)	
		F(j,1,m/i)  
			g[i*j].emplace_back(i);
	while(q--) 
	{
		int x;
		read(x);
		if(vis[x])
		{
			ans -= calc(a[x]);
			update(a[x],-1);
		}
		else
		{
			update(a[x],1);	
			ans += calc(a[x]);
		}
		vis[x] = vis[x] ^ 1;
		write(ans-cnt);
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：wcyQwQ (赞：3)

我们考虑计算每次答案的增减量，设当前在桌上牌的集合为 $S$，我们要加入/拿走的数为 $x$，我们要求的就是 
$$
\begin{aligned}
&\sum_{k \in S} [\gcd(x, k) = 1] \\
&= \sum_{k \in S} \sum_{d | \gcd(x, k)} \mu(d) \\
&= \sum_{d | x}\mu(d)\sum_{k \in S, d|k} 1
\end{aligned}
$$
开桶维护某个数倍数的出现次数即可。时间复杂度 $O(n\log a)$。[Code](https://codeforces.com/contest/547/submission/212511255)

---

## 作者：chihik (赞：3)

记 $c_i$ 为 $i$ 毫升泡沫的酒在架子上的瓶数，$A=\max_{i=1}^n a_i$。

为了方便将二元组视为有序，答案除以 $2$ 即可。

$$\sum_{i=1}^A \sum_{j=1}^A c_i c_j [\gcd(i,j)=1]$$

$$\sum_{d=1}^A \mu(d) \sum_{i=1}^{A/d} \sum_{j=1}^{A/d} c_{id} c_{jd}$$

$$\sum_{d=1}^A \mu(d) ( \sum_{i=1}^{A/d}c_{id} )^2$$

$$\begin{cases}
\Delta_+=\sum_{d|a_i} \mu(d) ((\sum_{i=1}^{A/d}c_{id}+1)^2-(\sum_{i=1}^{A/d}c_{id})^2) \\
\Delta_-=\sum_{d|a_i} \mu(d) ((\sum_{i=1}^{A/d}c_{id})^2-(\sum_{i=1}^{A/d}c_{id}-1)^2)
\end{cases}$$

$$\begin{cases}
\Delta_+=\sum_{d|a_i} \mu(d) (2\sum_{i=1}^{A/d}c_{id}+1) \\
\Delta_-=\sum_{d|a_i} \mu(d) (2\sum_{i=1}^{A/d}c_{id}-1)
\end{cases}
$$

如果有多个 $1$ 上面的式子就 GG 了，不过这也很好处理，直接将答案减去/加上 $1$ 的个数即可。

时间复杂度 $\mathcal O(A+q\sqrt A)$

```cpp
#include <cstdio>
#define LL long long

const int MAXN = 5e5;

int prnum , prime[ MAXN + 5 ] , mu[ MAXN + 5 ];
bool vis[ MAXN + 5 ];
void sieve( ) {
	mu[ 1 ] = 1;
	for( int i = 2 ; i <= MAXN ; i ++ ) {
		if( !vis[ i ] ) prime[ ++ prnum ] = i , mu[ i ] = -1;
		for( int j = 1 ; j <= prnum && 1ll * i * prime[ j ] <= MAXN ; j ++ ) {
			vis[ i * prime[ j ] ] = 1;
			if( i % prime[ j ] == 0 ) break;
			mu[ i * prime[ j ] ] = -mu[ i ];
		}
	}
}

int n , q , a[ MAXN + 5 ] , c[ MAXN + 5 ];
LL Ans;
bool on[ MAXN + 5 ];

LL Calc[ MAXN + 5 ];
// int Calc( int d ) {
// 	int tmp = 0;
// 	for( int i = d ; i <= MAXN ; i += d ) tmp += c[ i ];
// 	return tmp;
// }
void Add( int x ) {
	for( int d = 1 ; d * d <= x ; d ++ )
		if( x % d == 0 ) {
			Ans += mu[ d ] * ( 2 * Calc[ d ] + 1 ) , Calc[ d ] ++;
			if( d * d != x ) Ans += mu[ x / d ] * ( 2 * Calc[ x / d ] + 1 ) , Calc[ x / d ] ++;
		}
	c[ x ] ++;
	if( x == 1 ) Ans --;
}
void Del( int x ) {
	for( int d = 1 ; d * d <= x ; d ++ )
		if( x % d == 0 ) {
			Ans -= mu[ d ] * ( 2 * Calc[ d ] - 1 ) , Calc[ d ] --;
			if( d * d != x ) Ans -= mu[ x / d ] * ( 2 * Calc[ x / d ] - 1 ) , Calc[ x / d ] --;
		}
	c[ x ] --;
	if( x == 1 ) Ans ++;
}

int main( ) {
	sieve();
	scanf("%d %d",&n,&q);
	for( int i = 1 ; i <= n ; i ++ ) scanf("%d",&a[ i ]);
	for( int i = 1 , pos ; i <= q ; i ++ ) {
		scanf("%d",&pos);
		on[ pos ] ? Del( a[ pos ] ) : Add( a[ pos ] );
		on[ pos ] ^= 1;
		printf("%lld\n", Ans / 2 );
	}
	return 0;
}
```

---

## 作者：wyyqwq (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF547C)

[更好的阅读体验](https://www.cnblogs.com/wyyqwq/p/18190367)

莫比乌斯反演的一个比较复杂做法（

令 $f(i)$  表示序列中 $\operatorname {gcd}$ 为 $i$ 的倍数的数对的个数， $g(i)$ 为序列中 $\operatorname {gcd}$ 为 $i$ 的数对的个数，即 $f(n) = \sum_{n|d} g(d)$ 。
$$
f(n) = \sum_{n|d} g(d)
$$

$$
g(n) = \sum_{n|d} \mu(\frac{d}{n})f(d)
$$

题目要求 $\operatorname {gcd}(a[i],a[j]) = 1$ 的对数，即为求 $g(1)$ 的值。
$$
g(1) = \sum_{n|d} \mu(d)f(d)
$$
$f(i)$ 该怎么求？设 $h(i)$ 为序列中为 $i$ 的倍数的个数。例如 $a[] = {1, 2, 3, 4, 6}$， $h(2) = 3$ 。不难发现， $f(i) = \frac{h(i) * (h(i) - 1)}{2}$。

然后就修改的时候改一下 $h(i)$ 的值即可，有一些小细节看代码好了。

```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1e6 + 7;
const int M = 500000;
int a[N];
int h[N], f[N], p[N], tot, mu[N], t[N], flg[N], vis[N], prime[N], e[N];
int ans = 0;
int n, q;

void getMu(){
	e[1] = 1, mu[1] = 1;
	for(int i = 2; i <= M; i ++) {
		if(!e[i]) p[++ tot] = i, mu[i] = -1;
		for(int j = 1; j <= tot; j ++) {
			if(p[j] * i > M) break;
			mu[p[j] * i] = i % p[j] == 0 ? 0 : -mu[i];
			e[p[j] * i] = 1;
			if(i % p[j] == 0) break;
		}
	}
}
void add(int x, int v) {
	h[x] += v;
	ans += ((h[x]) * (h[x] - 1) / 2 - f[x]) * mu[x];
	f[x] = h[x] * (h[x] - 1) / 2;
}
void modify(int x, int v) {
	for(int i = 1; i * i <= x; i ++) {
		if(x % i == 0) {
			add(i, v);
			if(i * i != x) add(x / i, v);
		}
	}
}
signed main() {
	getMu();
	cin >> n >> q;
	for(int i = 1; i <= n; i ++) {
		cin >> a[i];
	}
	for(int i = 1; i <= q; i ++) {
		int p;
		cin >> p;
		if(vis[p]) modify(a[p], -1), vis[p] = 0;
		else {
			modify(a[p], 1);
			vis[p] = 1;
		}
		cout << ans << endl;
	}
}
```

---

## 作者：Lu_xZ (赞：1)

[Link](https://www.cnblogs.com/Luxinze/p/18115414#cf547c)

题意：维护一个可重集，每次查询集合中互质数对的个数。

+ 两个数互质取决于是否有共同的质因子。
+ 小于 $5\times 10^5$ 的数最多有 $7$ 个不同质因子。

令 $cnt_x$ 表示当前集合中能被 $x$ 整除的数的个数。

考虑新增一个元素 $cur = p_1^{\alpha_1}\dots p_k^{\alpha_k}$。

令性质 $a_i$ 表示能被 $p_i$ 整除。

则
$$
\begin{aligned}
\Delta N 
&= N((1 - a_1)\dots(1 - a_k)) \\
&= \sum\limits_{i = 0}^n (-1)^i \sum\limits_{1 \le j_1 < j_2 < \dots < j_i \le k} cnt_{p_{j_1}\dots p_{j_i}}
\end{aligned}
$$

删除同理。

[submission](https://codeforces.com/contest/547/submission/258173204)

---

## 作者：漠寒 (赞：1)

## 分析

给出 $n$ 个数，每次向集合增加或去掉其中一个数，求集合内有多少无序数对互质。

考虑计算每一次操作对答案的影响，在总个数的基础上，减去与其不互质的个数，就是与其互质的个数，但如果枚举因数直接相减，显然会减重，所以考虑容斥。

比如你你用 $cnt_i$ 表示以 $i$ 为因数的数有多少个，减了 $cnt_2$，减了 $cnt_3$，你就应该把 $cnt_6$ 加回来。你这样列举，你就会发现，一个质因数就减，两个就加，如果有重复的多个质因数不需要管，这样就显然是 $\mu$ 函数了。

所以对每一个因数，贡献就是 $cnt_a$ 乘上其 $\mu$ 函数。将贡献累加，要删的时候减，要加的时候加就行了。

## 代码

```
#include<bits/stdc++.h>
using namespace std;
inline void read(int &res){
	res=0;
	int f=1;
	char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9')res=(res<<1)+(res<<3)+c-48,c=getchar();
	res*=f;
}
int n,m;
int cj[500005];
int cnt[500005];
vector<int>v[200005];
inline void sol(int x,int y){//找出所有因数 
	for(int i=1;i*i<=x;i++){
		if(x%i==0){
			v[y].push_back(i);
			if(i*i!=x)v[y].push_back(x/i);
		}
	}
}
int is[500005];
bool vis[200005];
int tot;
int pri[500005],cnt_p;
void init(){
	cj[1]=1;
	for(int i=2;i<=500000;i++){
		if(!is[i]){
			cj[i]=-1;//莫比乌斯函数 
			pri[++cnt_p]=i;
		}
		for(int j=1;j<=cnt_p&&pri[j]*i<=500000;j++){
			if(i%pri[j]==0){
				is[i*pri[j]]=1;
				continue;
			}
			cj[i*pri[j]]=cj[i]*(-1);
			is[i*pri[j]]=1;
		}
	}
}
long long ans;
inline int query(int x){
	int sum=0;
	for(int i=0;i<v[x].size();i++){
		int a=v[x][i];
		sum+=cj[a]*cnt[a];//累加贡献 
	}
	return sum;
}
inline void work(int x,int bo){
	if(bo){//加上 
		tot++;
		vis[x]=1;
		for(int i=0;i<v[x].size();i++){
			int a=v[x][i];
			cnt[a]++;
		}
	}
	else {//去掉 
		tot--;
		vis[x]=0;
		for(int i=0;i<v[x].size();i++){
			int a=v[x][i];
			cnt[a]--;
		}
	}
}
int tp[200005];
signed main()
{
	read(n);read(m);
	init();
	for(int i=1;i<=n;i++){
		int x;
		read(x);
		sol(x,i);
		if(x==1)tp[i]=1;
	}
	for(int i=1;i<=m;i++){
		int x;
		read(x);
		int k=query(x);
		if(tp[x]&&vis[x])k--;//1会和自己互质 
		if(vis[x])work(x,0),ans-=k;
		else work(x,1),ans+=k;
		printf("%lld\n",ans);
	}
	return 0;
}
/*
5 5
2 4 6 8 10
1 2 3 4 5

*/
```


---

## 作者：qianfujia (赞：1)

发现这题居然没有题解，我就来水一发

一道容斥原理的练手题，感觉评成紫色有点高了

思路就是对于每一个数$a_i$,计算与它不互素的数的个数再相减

具体来说，对于$a_i=\Pi p_i^{k_i}$我们用集合$A_j$来表示其因子中刚好只有k个互不相同质因子的集合，即$A_j=\{x=\Pi_1^jp_i |(x|a_i)\}$,根据容斥原理，最终答案即为$\sum|A_i|*(-1)^{i-1}$

code
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL N = 5e5+10;
LL n, q, a[N];
bool vis[N];
vector <LL> b[200010];
LL s[N];
LL d[N];
int main(){
    for(LL i = 2; i < N; ++ i){
        LL x = i;
        s[i] = -1;
        for(LL j = 2; j * j <= x; ++ j)
            if(x % j == 0){
                x /= j; s[i] = -s[i];
                if(x % j == 0){s[i] = 0; x = 1; break;}
            }
        if(x != 1)s[i] *= -1;
    }
	scanf("%lld%lld", &n, &q);
	for(LL i = 1; i <= n; ++ i){
		scanf("%lld", &a[i]);
		for(LL j = 1; j * j <= a[i]; ++ j)
			if(a[i] % j == 0){
				if(s[j] != 0)b[i].push_back(j);
				if(a[i] != j * j && s[a[i] / j] != 0)b[i].push_back(a[i]/j);
			}
	}
	LL ans = 0, tot = 0;
	while(q --){
		LL x; scanf("%lld", &x);
		if(a[x] == 1){
			if(vis[x]) ans -= tot - 1, -- tot;
			else ans += tot, ++ tot;
			vis[x] ^= 1;
			printf("%lld\n", ans);
			continue;
		}
		if(vis[x]){
			vis[x] = 0;
			LL t = 0;
			for(LL i = 0; i < b[x].size(); ++ i)
				t += s[b[x][i]] * d[b[x][i]], d[b[x][i]] --;
			ans -= tot - t;
			tot --;
		} else{
			vis[x] = 1;
			LL t = 0;
			for(LL i = 0; i < b[x].size(); ++ i)
				t += s[b[x][i]] * d[b[x][i]], d[b[x][i]] ++;
			ans += tot - t;
			tot ++;
		}
		printf("%lld\n", ans);
	}
	return 0;
}

```

---

## 作者：tder (赞：0)

我们先来定义几个函数：

$$
\begin{aligned}
f(i)&=\sum_{x=1}^n\sum_{y=1}^{x-1}~[i\mid\gcd(a_x,a_y)] \\
g(i)&=\sum_{x=1}^n\sum_{y=1}^{x-1}~[\gcd(a_x,a_y)=i]
\end{aligned}
$$

最终所求的答案即为 $\text{ans}=g(1)$。

于是，显然有 $g*I=f$，于是 $g=f*\mu$，即：

$$
\begin{aligned}
f(i)&=\sum_{i\mid d}^ng(d) \\
g(i)&=\sum_{i\mid d}^n\left(f(d)\times\mu\left(\frac di\right)\right)
\end{aligned}
$$

我们将 $i=1$ 代入，有：

$$
\begin{aligned}
g(1)&=\sum_{1\mid d}^n\left(f(d)\times\mu\left(\frac d1\right)\right) \\
  &=\sum_{j=1}^n\left(f(j)\times\mu\left(j\right)\right) 
\end{aligned}
$$

我们再定义：

$$
h(i)=\sum_{j=1}^n~[i\mid a_j]
$$

那么，显然的：

$$
f(i)=\frac{h(i)\times\left(h(i)-1\right)}2
$$

到此为止，我们很愉快的结束了推式子环节，接下来考虑加入一个数 $a_x$ 时的贡献。

我们记 $h_i=h(i)$ 且 $f_i=f(i)$。

当加入 $a_x$ 时，有且仅有可能对所有满足 $i\mid a_x$ 的 $h_i$ 产生贡献。于是考虑枚举 $a_x$ 的所有因数 $i$，并将 $h_i\gets h_i+1$，从而计算得出 $f_i$ 的值，最终使用莫比乌斯反演板子求得答案 $\text{ans}=g(1)$。反之删除同理。

形式化的，加入 $a_x$ 时：

$$
\begin{array}{ll}
1&\textbf{for }\text{each }i\mid a_x \\
2&\qquad h_i\gets h_i+1 \\
3&\qquad pre\gets f_i \\
4&\qquad new\gets\dfrac{h_i\times\left(h_i-1\right)}2 \\
5&\qquad f_i\gets new \\
6&\qquad\Delta\gets new-pre \\
7&\qquad ans\gets ans+\Delta\times\mu(i)\\
\end{array}
$$

删除时仅需将第 $2$ 行的 $h_i+1$ 改为 $h_i-1$ 即可。

$\mu$ 函数可以 $O(\max(a_i))$ 预处理，单次操作复杂度 $O(\tau(a_x))$，查询复杂度 $O(1)$，总复杂度 $O(\max(a_i)+q\times\tau(a_x))$。

---

## 作者：Purslane (赞：0)

# Solution

假设现存每个数的个数为 $cnt_i$。那么不管 $i$ 和 $j$ 的大小关系的答案为

$$\begin{aligned}
\sum_{i=1}^{mx} \sum_{j=1}^{mx} cnt_icnt_j[(i,j)=1] &= \sum_{i=1}^{mx} \sum_{j=1}^{mx}  \sum_{d|i,d|j} \mu(d) cnt_icnt_j \\
&=\sum_{d=1}^{mx} \mu(d) \sum_{i=1}^{\frac{mx}{d}} \sum_{j=1}^{\frac{mx}{d}} cnt_{id}cnt_{jd} \\
&= \sum_{d=1}^{mx} \mu(d) (\sum_{i=1}^{\frac{mx}{d}} cnt_{id})^2
\end{aligned}
$$

除了 $a_i=a_i=1$ 这种 $i=j$ 的情况存在以外，其他的 $i$ 都不可能等于 $j$。所以先把上述这个式子减去目前存在的 $1$ 的个数，再除以 $2$ 就是答案。

考虑维护这个式子。设 $sum_v = \sum_{v|d} cnt_d$。每次加入一个数 $x$ 对于所有 $d|x$ 都有影响。考虑到 $5 \times 10^5$ 内一个数 $\mu$ 不为 $0$ 的因数最多有 $64$ 个（就是类似 $2 \times 3 \times 5 \times 7 \times 11 \times 13$ 这种形态），也就是每次修改一个数，最多对 $64$ 个数产生影响。因此预处理所有能产生影响的因数，暴力修改和式中的 $sum$ 即可。足以通过本题。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=5e5+10;
int n,q,ans,v1,ocp[MAXN],a[MAXN],flg[MAXN],mu[MAXN],cnt[MAXN]; vector<int> fac[MAXN],pr;
void init(int Mx=500000) {
	mu[1]=1;
	ffor(i,2,Mx) {
		if(flg[i]==0) mu[i]=-1,pr.push_back(i);
		for(auto v:pr) {
			if(i*v>Mx) break;
			flg[i*v]=1,mu[i*v]=-mu[i];
			if(i%v==0) {mu[i*v]=0;break;}	
		}
	}
	return ;
}
void add(int v) {
	if(v==1) v1++;
	for(auto val:fac[v]) {
		ans-=mu[val]*cnt[val]*cnt[val];
		cnt[val]++;
		ans+=mu[val]*cnt[val]*cnt[val];
	}
	return ;
}
void erase(int v) {
	if(v==1) v1--;
	for(auto val:fac[v]) {
		ans-=mu[val]*cnt[val]*cnt[val];
		cnt[val]--;
		ans+=mu[val]*cnt[val]*cnt[val];
	}
	return ;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>q; ffor(i,1,n) cin>>a[i];
	init(); ffor(i,1,500000) if(mu[i]!=0) ffor(j,1,500000/i) fac[i*j].push_back(i);
	ffor(i,1,q) {
		int x; cin>>x;
		if(ocp[x]) erase(a[x]),ocp[x]=0;
		else add(a[x]),ocp[x]=1;
		cout<<(ans-v1)/2<<'\n';
	}
	return 0;
}
```

~~使用 $a$ 作为数组名 , 成为限制我水平进步的天花板~~

---

