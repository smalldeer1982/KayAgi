# Random Elections

## 题目描述

总统选举将于明年在Bearland举行！每个人都为此感到非常兴奋！

到目前为止，有三位候选人，A，B和C。

Bearland有n个公民。选举结果将对Bearland所有公民的生活产生很大的影响。由于这一重大责任，每个公民都会随机选择A，B和C之间的六个优先顺序（ABC,ACB,BCA,BAC,CBA,CAB）中的一个。如果该顺序为ABC，表示该选民最支持A，其次是B，最不支持C。

考虑到选民的偏好，Bearland政府已经设计了一个用来确定选举结果的函数$f$。

更具体地说，这个函数需要输入一个长度为$2^n$的01串$x$，并返回一个bool。数据保证$f$满足

$f(1-x_1,1-x_2,\ldots,1-x_n)=1-f(x_1,x_2,\ldots,x_n)$

政府将进行3次比赛：A和B、B和C、C和A

在每一次比赛中（假设是候选人A和B之间的），如果第i个人更支持A，则$x_{i}=1$，否则$x_{i}=0$。假设函数f返回的值是1，则A胜，否则B胜

定义$p$为有一个候选人赢了两场的概率，你需要输出$p\times6^n$模1e9+7的值

## 样例 #1

### 输入

```
3
01010101
```

### 输出

```
216
```

## 样例 #2

### 输入

```
3
01101001
```

### 输出

```
168
```

# 题解

## 作者：Soulist (赞：3)

题意：


给定 $n$ 个人，每个人将随机支持 A,B,C 中的一位用户的一个排序，若为 ABC 则优先支持 A，其次为 B，再次为 C

统计有多少种方案使得某个用户获胜两次，其中某次比赛 $i$ 获胜当且仅当：

$f(i_1,i_2,i_3...)=1$

其中 $f$ 是一个输入参数，保证 $f(i_1,i_2...)=1-f(i_1,i_2...)$

两个用户比较的时候，如果人 $i$ 支持 A，则以 A 考虑的时候有 $i_j$ 为 $1$，另一边为 $0$

$\rm Sol:$

显然 win 两次的玩家只有 $1$ 个

同时玩家是互不影响的，算出来单个玩家 win 的次数乘以 $3$ 即可。

考虑单个玩家怎么 win，对于两个胜负个 01 序列 S1 和 S2，显然有 $f(S1)=1,f(S2)=1$

我们发现单独看两个人的相对顺序对于答案是没有影响的。对于 $0,0$ 组其贡献有一个额外的 $2$，对于 $1,1$ 组其贡献有一个额外的 $2$，而 01 和 10 则会固定三元组的顺序。

我们发现问题实际上是计算两个 01 序列的都是 win 的个数的一个计数问题，每一位上如果都是 1 那么贡献为 2，如果都是 0 那么贡献为 2

我们不操作第一个 01 序列 S1，对于第二个 01 序列 S2 则将其中的 01 翻转，那么容易发现对于新的 01 序列有这一位上为 01 才用贡献，你想到了什么？xor 卷积啊老哥。

然后随便卷一下，算一下贡献即可。

$Code:$

```cpp
#include<bits/stdc++.h>
using namespace std ;
#define Next( i, x ) for( register int i = head[x]; i; i = e[i].next )
#define rep( i, s, t ) for( register int i = (s); i <= (t); ++ i )
#define drep( i, s, t ) for( register int i = (t); i >= (s); -- i )
#define re register
#define int long long
int gi() {
	char cc = getchar() ; int cn = 0, flus = 1 ;
	while( cc < '0' || cc > '9' ) {  if( cc == '-' ) flus = - flus ; cc = getchar() ; }
	while( cc >= '0' && cc <= '9' )  cn = cn * 10 + cc - '0', cc = getchar() ;
	return cn * flus ;
}
const int P = 1e9 + 7 ;
const int Iv2 = 5e8 + 4 ;
const int N = ( 1 << 21 ) ;
int n, limit, f[N], g[N], fac[N] ; 
char s[N] ; 
int lowbit( int x ) {
    return __builtin_popcountll(x) ;
}
void FWT_xor( int *a, int type ) {
	for( re int k = 1; k < limit; k <<= 1 ) 	
	for( re int i = 0; i < limit; i = ( i + ( k << 1 ) ) ) 
		for( re int j = i; j < i + k; ++ j ) {
			int nx = a[j], ny = a[j + k] ;
			( type == 1 ) ? ( a[j] = ( nx + ny ) % P, a[j + k] = ( nx - ny + P ) % P ) : ( a[j] = ( nx + ny ) * Iv2 % P, 
				a[j + k] = ( nx - ny + P ) * Iv2 % P ) ; 
		}
}
signed main()
{
	n = gi(), limit = ( 1 << n ) ;
	scanf("%s", s ) ; int S = limit - 1 ; 
	rep( i, 0, limit - 1 ) f[i] = s[i] - '0' ;
	for( int i = 0; i < limit; ++ i ) g[i] = f[i ^ S] ;
	FWT_xor( f, 1 ), FWT_xor( g, 1 ) ;
	rep( i, 0, limit ) g[i] = f[i] * g[i] % P ; 
	FWT_xor( g, 0 ) ; int Ans = 0 ;
	fac[0] = 1 ; 
	rep( i, 1, 25 ) fac[i] = fac[i - 1] * 2 % P ;  
	rep( i, 0, limit ) Ans = ( Ans + g[i] * fac[lowbit(i)] % P ) % P ; 
	cout << ( Ans * 3 ) % P << endl ;
	return 0 ;
}
```

---

## 作者：Arghariza (赞：2)

难点在于读题。

由于每个人有 $6$ 种选法，答案其实就是某个人赢两次的方案数。

由于三个人本质没有差别，并且一种方案至多只有 $1$ 个人赢两次。所以不妨设 A 赢了两次，答案就是方案数乘 $3$。

考察 A 对于 B 和 C 的比赛，每个人的投票结果，第 $i$ 个人的投票为 $P_i$ 和 $Q_i$，有 $P_i,Q_i\in \{0,1\}$。

- $P_i=0,Q_i=0$：获胜顺序为 $C\to B\to A$ 或者 $B\to C\to A$。
- $P_i=0,Q_i=1$：获胜顺序为 $C\to A\to B$。
- $P_i=1,Q_i=0$：获胜顺序为 $B\to A\to C$。
- $P_i=1,Q_i=1$：获胜顺序为 $A\to B\to C$ 或者 $A\to C\to B$。

显然只有当 $P_i=Q_i$ 的时候贡献为 $2$。将所有位放到一起计算，每对 $(P,Q) $ 的贡献为 $2^{n-\text{popcount(P \text{xor} Q)}}$。

设 $c_k=\sum\limits_{i\ \text{xor}\ j=k}f_if_j$，答案显然就是 $\sum\limits_{i=1}^{2^n-1}c_i2^{n-\text{popcount(i)}}$。

这就是个异或卷积，FWT 即可。复杂度 $O(n2^n)$。

```cpp
const int maxn = 22;
const int mod = 1e9 + 7;
const int T = (1 << 20) + 100;
int n, S, a[T], pt[T];

int qpow(int p, int q) {
    int res = 1;
    while (q) {
        if (q & 1) res = res * p % mod;
        p = p * p % mod, q >>= 1;
    }
    return res;
}

void fwt(int *s, int op) {
    for (int o = 2, k = 1; o <= S + 1; o <<= 1, k <<= 1)
        for (int i = 0; i <= S; i += o) 
            for (int j = 0; j < k; j++)
                (s[i + j] += s[i + j + k]) %= mod,
                s[i + j + k] = (a[i + j] - 2 * s[i + j + k] % mod + mod) % mod,
                (s[i + j + k] *= op) %= mod, (s[i + j] *= op) %= mod;
}

signed main() {
	n = read(), S = (1 << n) - 1;
    for (int i = 0; i <= S; i++) scanf("%1d", &a[i]);
    for (int i = 1; i <= S; i++) pt[i] = pt[i >> 1] + (i & 1);
    fwt(a, 1);
    for (int i = 0; i <= S; i++) (a[i] *= a[i]) %= mod;
    fwt(a, qpow(2, mod - 2));
    int ans = 0;
    for (int i = 0; i <= S; i++) 
        (ans += (1 << (n - pt[i])) * a[i] % mod) %= mod;
    write(3 * ans % mod);
    return 0;
}
```

---

## 作者：FZzzz (赞：2)

题意：有三个候选人和 $n$ 个选民，每个选民有一个对三个候选人的支持度排序。候选人两两之间进行三次比赛，每次比赛的结果由如下方法确定：给定一个 $2^n$ 的零一数组 $f$，构造一个二进制数 $x$，对于第 $i$ 位，如果第 $i$ 个选民比起第二个人更支持第一个人，则这一位为一，否则为零。$f_x=1$ 则代表第一个人赢了，否则第二个人赢。问有多少种方案使得某个候选人赢了两场。

我们考虑候选人 A 在什么情况下能赢两场。考虑他对阵 B 和 C 时的两个零一序列，使得他赢了两场。对于某一位，如果这一位不同，则这个选民的支持度排序已经可以确定，否则有两种排序可以造成这个结果。于是只需要知道这两个序列的异或值，就可以得出这两个序列对答案的贡献。我们考虑对每个 $x$ 计算出有多少种零一序列能让 A 赢两次并且异或后可以得到 $x$，发现这就是 $f$ 与自己的异或卷积，使用 FWT 实现即可。

最后要把答案乘以三。复杂度 $n2^n$。
```cpp
#include<cctype>
#include<cstdio>
using namespace std;
inline int readint(){
	int x=0;
	bool f=0;
	char c=getchar();
	while(!isdigit(c)&&c!='-') c=getchar();
	if(c=='-'){
		f=1;
		c=getchar();
	}
	while(isdigit(c)){
		x=x*10+c-'0';
		c=getchar();
	}
	return f?-x:x;
}
const int maxn=20+5;
int n;
char s[(1<<maxn)+5];
typedef long long ll;
ll f[(1<<maxn)+5];
const ll mod=1e9+7,inv2=500000004;
void FWT(ll* f,int n,bool flag){
	for(int i=1;i<n;i*=2) for(int j=0;j<n;j+=i*2)
		for(int k=j;k<j+i;k++){
			ll t=f[k+i];
			f[k+i]=(f[k]+mod-t)%mod*(flag?1:inv2)%mod;
			f[k]=(f[k]+t)%mod*(flag?1:inv2)%mod;
		}
}
ll ksm(ll a,ll b){
	ll ans=1;
	while(b>0){
		if(b%2==1) ans=ans*a%mod;
		a=a*a%mod;
		b/=2;
	}
	return ans;
}
int cnt[(1<<maxn)+5];
int main(){
	#ifdef LOCAL
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	#endif
	n=readint();
	scanf("%s",s);
	for(int i=0;i<(1<<n);i++) f[i]=s[i]-'0';
	FWT(f,1<<n,1);
	for(int i=0;i<(1<<n);i++) f[i]=f[i]*f[i]%mod;
	FWT(f,1<<n,0);
	for(int i=1;i<(1<<n);i++) cnt[i]=cnt[i^(i&-i)]+1;
	ll ans=0;
	for(int i=0;i<(1<<n);i++) ans=(ans+f[i]*ksm(2,n-cnt[i])%mod)%mod;
	printf("%lld\n",ans*3%mod);
	return 0;
}
```

---

## 作者：木xx木大 (赞：2)

[CF850E Random Elections](https://www.luogu.com.cn/problem/CF850E)

菜鸡的 FWT 应用第一题。这题题意杀我，我花了一个小时的时间才看懂题。。。感觉这题的题目难度中读题难度起码占了$\%50$。翻译是真的看不懂，建议大家都去看英文题面。

显然能赢两次的玩家只有一个，且玩家之间互不影响。所以我们可以只考虑 A 赢的情况，最后把答案 $\times 3$。

考虑 A 对阵 B 和 C 时的两个 01 序列，使得 A 赢了两场。发现对于某一位，如果这一位不同，则这个选民的支持度排序已经可以确定，否则有两种排序可以造成这个结果。举个例子，设两个串 $S1,S2$ 分别表示 $A-B$ 和 $C-A$ 对阵时每个公民的决定，$S1,S 2$  的第 $i$ 位的情况为 $(x,y)$ :

* $(x,y)=(0,0)\Rightarrow CBA,CAB$
* $(x,y)=(1,0)\Rightarrow CAB$
* $(x,y)=(0,1)\Rightarrow BAC$
* $(x,y)=(1,1)\Rightarrow ABC,ACB$：

发现如果 $(x \ xor\  y)=0$ 就可以对方案数造成 2 的贡献 。设 $S=S1\ xor \ S2$ ，$c$ 为 $S$ 中0的个数，那么 $S1,S2$ 对答案的贡献即为 $2^c$ 。我们对每个 $S$ 计算出有多少对 $S=S1 \ xor \ S2$ 且 $f_{S1}=f_{S2}=1$ ，发现这就是 $f$ 与自己的异或卷积，使用 FWT 实现即可。 

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
namespace FGF
{
	int n,m;
	const int N=2e6+5;
	const int mo=1e9+7;
	char s[N]; 
	ll a[N],pw[N],cnt[N];
	ll ans;
	void FWTxor(ll *y,int op)
	{
		for(int i=1;i<=n;i++)
			for(int j=0;j<(1<<n);j+=(1<<i))
				for(int k=0;k<(1<<(i-1));k++)
				{
					ll c=(y[j|k]+y[j|k|(1<<(i-1))])%mo,d=(y[j|k]-y[j|k|(1<<(i-1))]+mo)%mo;
					y[j|k]=c*op%mo,y[j|k|(1<<(i-1))]=d*op%mo;
				}
	}
	void work()
	{
		scanf("%d",&n);
		scanf("%s",s);
		pw[0]=1;
		for(int i=0;i<(1<<n);i++)
			a[i]=s[i]-'0';
		for(int i=1;i<=n;i++)
			pw[i]=2LL*pw[i-1]%mo;
		for(int i=1;i<(1<<n);i++)
			cnt[i]=cnt[i>>1]+(i&1);
		FWTxor(a,1);
		for(int i=0;i<(1<<n);i++)
			a[i]=a[i]*a[i]%mo;
		FWTxor(a,(mo+1)/2);
		for(int i=0;i<(1<<n);i++)
			ans=(ans+1LL*a[i]*pw[n-cnt[i]])%mo;
		printf("%lld",ans*3%mo);
	}
}
int main()
{
	FGF::work();
	return 0;
}
```



---

## 作者：RainAir (赞：1)

建议多读几遍题再来看题解，感觉这题题意才是最难的（雾

---

我们先考虑钦定获胜两次的是 A 最后答案乘$3$就好了。

考虑一个显然的暴力：枚举两个 $f(S)=1$ 的串 $S_1,S_2$ 表示 A 和 B 打时每个人的决定 , A 和 C 打时每个人的决定。然后我们计算一下这样做的方案数。容易发现每位是独立的，记这两位是$x_1,x_2$，我们按位考虑：

$x_1=0 ,x_2=0$ : BCA CBA

$x_1=1,x_2=0$ : CAB

$x_1=0,x_2=1$ : BAC

$x_1=1,x_2=1$ : ABC ACB

所以发现如果(x1 xor x2)=0 就可以对方案数造成 $2$ 的贡献

所有位压在一起做 可以得到两个串的贡献是 $2^{n-pc[S1 \textbf{xor} S2]}$

其中 $pc[i]$ 表示 $i$ 二进制下 $1$ 的个数。

现在我们需要算出所有的方案数了 暴力枚举是 $O(4^{n})$ 的，我们可以考虑用 FWT 预处理出xor值$=i$ 的对数有多少 分别累加贡献即可。

Code:
```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <bitset>
#include <vector>
#include <cmath>
#include <ctime>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define fi first
#define se second
#define U unsigned
#define P std::pair
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = (1<<21)+3;
const int ha = 1e9 + 7;
const int inv2 = 500000004;

char str[MAXN];
int n,N;
int pw[MAXN],pc[MAXN];
int f[MAXN];

inline void FWT(int f[]){
    for(int mid = 1;mid < N;mid <<= 1){
        for(int i = 0;i < N;i += (mid<<1)){
            FOR(j,0,mid-1){
                int x = f[i+j],y = f[i+mid+j];
                f[i+j] = (x+y)%ha;f[i+mid+j] = (x+ha-y)%ha;
            }
        }
    }
}

inline void iFWT(int f[]){
    for(int mid = N>>1;mid;mid >>= 1){
        for(int i = 0;i < N;i += (mid<<1)){
            FOR(j,0,mid-1){
                int x = f[i+j],y = f[i+mid+j];
                f[i+j] = 1ll*(x+y)*inv2%ha;f[i+mid+j] = 1ll*(x+ha-y)*inv2%ha;
            }
        }
    }
}

int main(){
    scanf("%d",&n);scanf("%s",str);
    N = (1<<(n+1));pw[0] = 1;
    FOR(i,1,MAXN-1) pw[i] = 2ll*pw[i-1]%ha,pc[i] = pc[i>>1]+(i&1);
    FOR(i,0,(1<<n)-1) f[i] = str[i]-'0';
    FWT(f);
    FOR(i,0,N-1) f[i] = 1ll*f[i]*f[i]%ha;
    iFWT(f);int ans = 0;
    FOR(i,0,N-1) (ans += 1ll*f[i]*pw[n-pc[i]]%ha) %= ha;//,DEBUG(f[i]),DEBUG(pc[i]);
    ans = 3ll*ans%ha;
    printf("%d\n",ans);
    return 0;
}
```

---

