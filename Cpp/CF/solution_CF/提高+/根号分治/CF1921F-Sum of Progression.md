# Sum of Progression

## 题目描述

给定一个长度为 $n$ 的数组 $a$。还有 $q$ 个查询，每个查询的形式为 $s, d, k$。

对于每个查询 $q$，请计算 $a_s + a_{s+d} \cdot 2 + \dots + a_{s + d \cdot (k - 1)} \cdot k$ 的和。换句话说，对于每个查询，需要找到从第 $s$ 个元素开始，每次步长为 $d$，共取 $k$ 个元素，并将第 $i$ 个取到的元素乘以 $i$，然后求和。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5
3 3
1 1 2
1 2 2
2 2 1
1 1 2
3 1
-100000000 -100000000 -100000000
1 1 3
5 3
1 2 3 4 5
1 2 3
2 3 2
1 1 5
3 1
100000000 100000000 100000000
1 1 3
7 7
34 87 5 42 -44 66 -32
2 2 2
4 3 1
1 3 2
6 2 1
5 2 2
2 5 2
6 1 2```

### 输出

```
5 1 3 
-600000000 
22 12 55 
600000000 
171 42 118 66 -108 23 2```

# 题解

## 作者：type19 (赞：13)

## 根号分治模板
#### （1）朴素做法

显然如果暴力枚举 $k$，则需要 $\Theta  \left ( t \cdot q \cdot k \right ) $ 的时间复杂度，只能 A 前 $4$ 个测试点。

代码如下：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,q,a[100010],s,d,k;
signed main(){
	cin>>t;
	for(int l=1;l<=t;l++){
		cin>>n>>q;
		for(int i=1;i<=n;i++) cin>>a[i];
		for(int j=1;j<=q;j++){
			cin>>s>>d>>k;
			int ans=0;
			for(int i=1;i<=k;i++){
				ans+=a[s+(i-1)*d]*i;
			}
			cout<<ans<<" ";
		}
		cout<<endl;
	}
	return 0;
}
```

#### （2）正解

对于 $\displaystyle\sum_{i=1}^ka_{s+(i-1)d}\times i$ 这个式子，显然如果不想超时，需要提前预处理来进行时间复杂度的优化，可以看到间隔为 $d$ 且有乘 $k$ 的计算，可想到后缀和的方法。

常规后缀和只能单独算间隔为 $d$ 的算式，因此在这里需要运用后缀和套后缀和的方式解决。

我们使用样例中第三个数据进行示范：

第一个后缀和数组：$d_{i,j}$ 表示从 $a_{n}$ 开始从后往前相加至 $a_{i}$ 并且间隔为 $j$ 的和。


|  | $1$ | $2$ | $3$ | $4$ | $5$ |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| $j=1$ | $15$ | $14$ | $12$ | $9$ | $5$ |
| $j=2$ | $9$ | $6$ | $8$ | $4$ | $5$ |

第二个后缀和数组：$d2_{i,j}$ 使 $d2_{i,j} = d2_{i+j,j} + d_{i,j}$。


|  | $1$ | $2$ | $3$ | $4$ | $5$ |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| $j=1$ | $55$ | $40$ | $26$ | $14$ | $5$ |
| $j=2$ | $22$ | $10$ | $13$ | $4$ | $5$ |

通过这两个后缀和数组，易得答案为：$d2_{s , d} - d2_{s + d \times k , d} - k \times d_{s + d \times k , d}$。

此时，时间复杂度为 $\Theta \left ( n \cdot d \right ) $，显然，当 $d$ 变大时，我们的复杂度会非常高，所以在 $d \ge \sqrt{n}$ 时我们可以直接暴力，否则则使用后缀和来解决。

AC 代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,q,a[100010],d3[100010][320],d2[100010][320];
signed main(){
	cin>>t;
	for(int l=1;l<=t;l++){
		cin>>n>>q;
		int sq=sqrt(n);
		for(int i=1;i<=n+sq;i++) for(int j=1;j<=319;j++) d3[i][j]=0,d2[i][j]=0;
		for(int i=1;i<=n;i++) cin>>a[i];
		for(int i=n;i>=1;i--) for(int j=1;j<=sq;j++) d3[i][j]=d3[i+j][j]+a[i];
		for(int i=n;i>=1;i--) for(int j=1;j<=sq;j++) d2[i][j]=d2[i+j][j]+d3[i][j];
		for(int j=1;j<=q;j++){
			int s,d,k;
			cin>>s>>d>>k;
			if(d>=sq){
				long long ans=0;
				for(int i=1;i<=k;i++) ans+=a[s+(i-1)*d]*i; 
				cout<<ans<<" ";
			}
			else cout<<d2[s][d]-d2[s+d*k][d]-k*d3[s+d*k][d]<<endl; 
		}
		cout<<endl;
	}
	return 0;
}
```



---

## 作者：aCssen (赞：13)

#### Solution
考虑根号分治。

对于 $d \ge \sqrt n$ 的询问，最多有 $\sqrt n$ 个数相加，暴力计算即可。

对于 $d < \sqrt n$ 的询问，可以预处理 $t_{i,j}$ 表示 $s=i,d=j$，一直加到序列末尾的**答案**，这类似于一个后缀和。

注意到这个乘 $k$ 不好处理，所以再处理一个数组 $S_{i,j}$ 表示 $s=i,d=j$ 一直加到序列末尾的**和**。那么我们倒序枚举 $i$，令 $t_{i,j}=t_{i+j,j}+S_{i,j}$ 即可，这样就相当于原先乘 $k$ 的答案中的数又被加了一次，变为乘了 $(k+1)$。

那么询问的时候答案为 $t_{s,d}-t_{s+d \times k,d}-k \times S_{s+d \times k,d}$，减去的第一个数先把不需要统计的范围的系数消成相同的，然后再减去这个系数 $k$ 乘上不需要统计的数的和即可。
#### Code
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
typedef long long ll;
bool Mbe;
const int maxn=1e5+555;
const int maxm=350;
int a[maxn],n,q;
ll t[maxn][maxm],S[maxn][maxm];
bool Med;
void solve(){
	scanf("%d%d",&n,&q);
	int B=max((int)sqrt(n),1);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=n+B;i++)
		for(int j=1;j<=B;j++)
			S[i][j]=t[i][j]=0;
	for(int i=n;i>=1;i--){
		for(int j=1;j<=B;j++){
			S[i][j]+=S[i+j][j];
			S[i][j]+=a[i];
		}
	}
	for(int i=n;i>=1;i--){
		for(int j=1;j<=B;j++){
			t[i][j]+=t[i+j][j];
			t[i][j]+=S[i][j];
		}
	}
	while(q--){
		int s,d,k;
		scanf("%d%d%d",&s,&d,&k);
		if(d>=B){
			ll ans=0;
			int pos=s;
			for(int i=1;i<=k;i++){
				ans+=(1ll*a[pos]*i);
				pos+=d;
			}
			printf("%lld ",ans);
		}
		else{
			printf("%lld ",t[s][d]-t[s+d*k][d]-k*S[s+d*k][d]);
		}
	}
	printf("\n");
}
int main(){
	int t;
	scanf("%d",&t);
	while(t--) solve();
	return 0;
}
```

---

## 作者：shinzanmono (赞：5)

考虑根号分治，设阈值为 $B$，则任意 $p\leq B$，预处理 $p$ 步的单次后缀和和两次后缀和。即 $s_{p,0,s}=\sum_{i=s}^n a_i[i\equiv s\pmod d]$，$s_{p,1,s}=\sum_{i=s}^n s_{p,0,i}[i\equiv s\pmod d]$。这样对于 $d\leq B$ 的询问，可以直接 $O(1)$ 回答。答案为 $s_{p,1,s}-s_{p,1,s+d\times k}-k\times s_{p,0,s+d\times k}$。对于 $d>B$ 的询问直接暴力求解即可。时间复杂度 $O(nB+\frac{qn}{B})$，应取 $B=\sqrt{q}$，但是由于空间复杂度为 $O(nB)$，故可以将 $B$ 缩小，以保证空间足够，此处 $B$ 取 $\sqrt{n}$（其实区别不大）。时间复杂度 $O(n\sqrt{n}+q\sqrt{n})$，空间复杂度 $O(n\sqrt{n})$，带有 $2$ 左右的常数。

给出代码：
```cpp
#include<iostream>
#include<algorithm>
using ll=long long;
const int sz=1e5+10;
const int sqsz=350;
ll sum[sqsz][2][sz+sqsz],a[sz];
int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin>>t;
    while(t--){
        int n,q;
        std::cin>>n>>q;
        int lim=__builtin_sqrt(n);
        for(int i=1;i<=n;i++)std::cin>>a[i];
        for(int p=1;p<=lim;p++){
            std::fill(sum[p][0]+1,sum[p][0]+n+lim+1,0);
            std::fill(sum[p][1]+1,sum[p][1]+n+lim+1,0);
            for(int i=n;i>=1;i--){
                sum[p][0][i]=sum[p][0][i+p]+a[i];
                sum[p][1][i]=sum[p][1][i+p]+sum[p][0][i];
            }
        }
        while(q--){
            int s,d,k;
            std::cin>>s>>d>>k;
            if(d<=lim)std::cout<<sum[d][1][s]-sum[d][1][s+k*d]-k*sum[d][0][s+k*d]<<" ";
            else{
                ll ans=0;
                for(int i=0;i<k;i++)ans+=a[s+i*d]*(i+1);
                std::cout<<ans<<" ";
            }
        }
        std::cout<<"\n";
    }
    return 0;
}
```

---

## 作者：kevinZ99 (赞：2)

一眼题。

考虑根号分治，对于这一种下标带系数的题目，可以按照系数分根号。

考虑 $ d \le \sqrt{n} $ 的时候，由于小于了根号，所以只有非常少的几种，而又因为这个题目查询的是类似区间的所以直接预处理前缀和。我们考虑如何处理这个前缀和，考虑从后往前枚举，其实是式子自然出来了，就是一个后缀和套一个后缀和，二阶后缀和？

考虑 $ d > \sqrt{n} $ 暴力即可，由于系数大于根号，所以式子不会超过根号项。

复杂度 $\mathcal{O}( n \sqrt{n} )$ 非常の优雅。

挺好写的。

**注意事项**

1、不要将数组开太大。

2、数组要开到 $ N + \sqrt{N} $ 因为预处理会访问到。

3、不要用 ```memeset``` 不然会超时。

4、ten year OI one game empty , no open long long see ancestor.

# code

```cpp
//Author:Kevin Z K Y
#include <bits/stdc++.h>
#define up(a,b,c) for(int (a)=(b);(a)<=(c);(a)++)
#define dn(a,b,c) for(int (a)=(b);(a)>=(c);(a)--)
#define fst first
#define sed second
using namespace std;
using us = unsigned short ;using ldb = long double ;
using ull = unsigned long long ;using ui = unsigned int ;
using ll = long long ;using hint = __int128 ;
using pii = pair<int,int> ;using pll = pair<ll,ll> ;
using pil = pair<int,ll> ;using vpil = vector<pil> ;
using vi = vector<int> ;using vl = vector<ll> ;
using vpi = vector<pii> ;using vpl = vector<pll> ;
using db = double ;namespace mystl{
	#define gc() getchar()
	#define Max(x,y) (((x)>(y))?(x):(y))
	#define Min(x,y) (((x)<(y))?(x):(y))
	#define Abs(x) (((x)<0)?(-(x)):(x))
	#define putline() cout<<"------------------------------\n"
	ll qpow(ll a , ll b , ll p) { if (a==0ll) return 0ll; ll c=1ll;
		while(b) { if(b & 1) c=a*c%p; a=a*a%p; b>>=1; } return c; }
	void exgcd(ll a,ll b,ll &cx,ll &cy){if(a % b ==0)cx = 0,cy = 1;
		else { exgcd( b , a % b , cy , cx) ; cy -= a / b * cx ; } }
	ll lcm ( ll x , ll y ){return x / std :: __gcd( x , y ) * y ; }
	template<typename T>void read(T&x) {x=0; bool f=false; char ch;
		ch = gc(); while(ch<'0'||ch>'9') f |= ( ch=='-') , ch=gc();
		while(ch>='0'&&ch<='9') x=x*10+ch-'0' , ch=gc(); x=f?-x:x;}
	template<typename T>void write(T x){char s[40];short d=0;T y=x;
		if(x<0) putchar('-'),y=-y;if(x==0){ putchar('0'); return; }
		while(y){s[++d]=y%10+'0';y/=10;}while(d>0)putchar(s[d--]);}
	template<typename T>void wris(T x,char c){write(x);putchar(c);}
}using namespace mystl;
const db eps=1e-6,PI=acos(-1);
namespace my{
	const int N=(int)(350+1e5);
	int B;
	const int inf=(int)(1e9);
	ll a[N],g[330][N],f[330][N];
	int n,q;
	ll s,d,k;
	void solve(){
		read(n);read(q);B=sqrt(n)+1;
		up(i,1,n)read(a[i]);
		up(i,1,B)
			dn(j,n,1)
				g[i][j]=g[i][j+i]+a[j],f[i][j]=f[i][j+i]+g[i][j];
		while(q--){
			read(s);read(d);read(k);
			if(d>B){
				ll ans=0;
				up(i,1,k)ans+=a[s+(i-1)*d]*i;
				wris(ans,' ');
			}else 
				wris(f[d][s]-f[d][s+d*k]-k*g[d][s+d*k],' ');
		}putchar('\n');
		up(i,1,B)up(j,1,n)f[i][j]=g[i][j]=0;
	}
}
int main(){
//  freopen("","r",stdin);
//  freopen("","w",stdout);
	int _=1;read(_);while(_--)my::solve();return 0;
}
/*
s[i][j]=s[i][j+i]+a[j]
f[i][j]=f[i][j+i]+s[i][j]
*/
```

---

## 作者：Suite_No1_G (赞：2)

第一次做出 div3 的 F 题。

观察数据范围，发现 $d$ 和 $k$ 的数据范围相互影响，乘积小于某个数，所以可以考虑根号分治。

由于 $d×k≤ n$，所以设 $m= \sqrt n$。

当 $d ≥ m,k ≤ m$ 时：可以发现最多不超过 $\frac{n}{d}$ 个数参与运算，所以直接暴力即可，时间复杂度 $O(nk) ≤ O(n \sqrt n)$。

当 $d ≤ m,k ≥ m$ 时，我们预处理后缀和，按下面方式计算：

![](https://cdn.luogu.com.cn/upload/image_hosting/ruq3cw5n.png)

所以：

$sum_{i,j}=sum_{i+j,j}+a_i$。

$ssum_{i,j}=ssum_{i+j,j}+sum_{i,j}$。

根据 $ssum_{i,k}-k×sum_{i+d×k,k}-ssum_{i+d×k,k}$ 来计算答案。本部分预处理的复杂度为 $O(nd)≤ O(n \sqrt n)$。

综上，时间复杂度为 $O(n \sqrt n)$。

注意清空后缀和数组。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

const int maxn=1e5+10;
int a[maxn];
const int P=400;
int sum[maxn][P+2];
int ssum[maxn][P+2];

signed main(){
//	freopen("random.in","r",stdin);
//	freopen("wrong.out","w",stdout);
	int T;
	scanf("%lld",&T);
	while (T--){
		int n,q;
		scanf("%lld%lld",&n,&q);
		int m=(int)sqrt(n);
		for (int i=1;i<=n;i++) scanf("%lld",&a[i]);
		
		for (int j=1;j<=m;j++){
			for (int i=n;i>=1;i--) sum[i][j]=sum[i+j][j]+a[i];
		}
		
		for (int j=1;j<=m;j++){
			for (int i=n;i>=1;i--) ssum[i][j]=ssum[i+j][j]+sum[i][j];
		}
		
		while (q--){
			int s,d,k;
			scanf("%lld%lld%lld",&s,&d,&k);
			if (d>m||k<=m){
				int ans=0;
				for (int i=0;i<=k-1;i++){
					ans+=a[s+i*d]*(i+1);
				}
				printf("%lld ",ans);
			}else{
				int ans=0;
				ans+=ssum[s][d];
				ans-=k*sum[s+k*d][d];
				ans-=ssum[s+k*d][d];
				printf("%lld ",ans);
			}
		}
		printf("\n");
		for (int i=1;i<=n;i++){
			for (int j=1;j<=m;j++) ssum[i][j]=sum[i][j]=0;
		}
	}
	return 0;
}
```


---

## 作者：doby (赞：2)

不难发现对于 $d>\sqrt{n}$ 可以直接暴力求解。  

于是只需要处理 $d\le\sqrt{n}$ 的情况。  

观察 $a_s+a_{s+d}\times 2+\cdots+a_{s+d\times (k-1)}\times k$，如果把间隔 $d$ 去掉，$a_s+a_{s+1}\times 2+\cdots+a_{s+(k-1)}\times k$ 就类似于一个后缀和套后缀和。  

于是对于每个 $a[i]$ 求从 $i$ 开始间隔为 $d$ 的后缀和即为 $b[i][d]$，再对 $b$ 求后缀和为 $c[i][d]$，就得到了和题目中式子相同的形式。  

最后答案为 $c[s][d]-c[s+d\times k][d]-k\times b[s+d\times k][d]$。  

复杂度 $ O(n\sqrt{n}) $。
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,q,s,x,y,z,out,fh,a[100010];
long long ans,b[100010][320],c[100010][320];
char cc;
int read()
{
	out=0,fh=1,cc=getchar();
	while(cc<48||cc>57){if(cc==45){fh=-1;}cc=getchar();}
	while(cc>=48&&cc<=57){out=(out<<3)+(out<<1)+(cc&15),cc=getchar();}
	return out*fh;
}
void Clear()
{
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=s;++j){b[i][j]=c[i][j]=0;}
	}
}
int main()
{
	T=read();
	while(T--)
	{
		n=read(),q=read(),s=0;
		for(int i=1;i<=n;++i){a[i]=read();}
		while(s*s<n){++s;}
		for(int i=n;i;--i)
		{
			for(int j=1;j<=s;++j)
			{
				b[i][j]+=a[i],c[i][j]+=b[i][j];
				if(i-j>0)
				{
					b[i-j][j]+=b[i][j],
					c[i-j][j]+=c[i][j];
				}
			}
		}
		while(q--)
		{
			x=read(),y=read(),z=read(),ans=0;
			if(y>s)
			{
				for(int i=1,j=x;i<=z;++i,j+=y){ans+=(long long)a[j]*i;}
				printf("%lld ",ans);
			}
			else
			{
				ans=c[x][y];
				if(x+y*z<=n)//注意判断s+d*k的大小
				{
					ans-=c[x+y*z][y]+b[x+y*z][y]*z;
				}
				printf("%lld ",ans);
			}
		}
		puts("");
		Clear();
	}
	return 0;
}
```


---

## 作者：lgx57 (赞：1)

根号分治模板题。

对于这种题目，直接暴力显然是不行的。于是要用到根号分治。

根号分治的基本思路就是设一个阈值 $B$，然后根据询问的大小分 $2$ 种情况讨论：

1. $d \ge B$

这种情况下直接暴力。

```cpp
if (d>=B){
    int ans=0;
    for (int now=s,i=1;i<=k;now+=d,i++){
        ans+=a[now]*i;
    }
    cout<<ans<<' ';
}
```

2. $d < B$

这种情况下需要预处理。我们设

$$st_{i,j}=[(j-1) \bmod i]+1$$

（中括号不是艾弗森括号，只是普通的中括号）。

然后：

$$sum_{i,j}=a_{st_{i,j}}+2a_{st_{i,j}+i}+ \cdots + \lceil \frac{j}{i} \rceil a_{j}$$

$$sum2_{i,j}=a_{st_{i,j}}+a_{st_{i,j}+i}+ \cdots + a_{j}$$

```cpp
for (int i=1;i<B;i++){
    for (int j=1;j<=n;j++){
        if (j<=i) sum[i][j]=a[j],sum2[i][j]=a[j];
        else sum[i][j]=sum[i][j-i]+(j+i-1)/i*a[j],sum2[i][j]=sum2[i][j-i]+a[j];
    }
}
```

于是有：

$$\sum _{i=1}^{k} ia_{s+(i-1)d}=sum_{d,s+(k-1)d}-sum_{d,s-d}-\lceil \frac{s}{d} \rceil (sum2_{d,s+(k-1)d}-sum2_{d,s-d})$$

（式子稍微有点长，具体可以看代码）。

```cpp
else{
    int L=s,R=s+(k-1)*d;
    int ans1=sum[d][R]-sum[d][L-d];
    int cnt=(s+d-1)/d-1;
    int ans2=cnt*(sum2[d][R]-sum2[d][L-d]);
    cout<<ans1-ans2<<' ';
}
```

那么时间复杂度为 $O(Bn+\frac{qn}{B})$。这个式子在 $B= \sqrt n$ 时取到最小值，所以这种技巧叫做根号分治。

[完整代码](https://codeforces.com/problemset/submission/1921/295374998)

---

## 作者：Robin_kool (赞：1)

经典的根号分治题，就是狗狗错误很难看出来。

考虑将每次询问给出的  $d$ 分成两部分，一部分大于 $\sqrt n$，一部分小于等于 $\sqrt n$。


------------

对于大于 $\sqrt n$ 的部分直接暴力求和，不再叙述。

```cpp
ans = 0;
for(int i = 1; i <= x; ++ i) ans += (a[s + (i - 1) * d] * i);
write(ans), putchar(' ');
```


------------
对于小于等于 $\sqrt n$ 的部分，我们可以预处理出两个储存和的数组。为了方便计算，使用后缀和，即 $dp_{d,0,i}=dp_{d,0,d+i}+a_i$。其中 $d$ 为当前预处理的 $d$。然后再开一个 $dp_{d,1,i}=dp_{d,1,d+i}+dp_{d,0,d+i}$，为 $dp_{d,0,i}$ 的后缀和数组。

$\because ans=\sum_{i=1}^k a_{s+(i-1)\times d}\times i$

$\therefore ans=dp_{d,1,s}-dp_{d,1,s+d\times k}-k\times dp_{d,0,s+d\times k}$

手推，能发现前两个相减很像前缀和取区间值的操作，但就是系数都比原来大 $k$ ，因此减去第三项即可。

---

## 作者：tanshunyu0913 (赞：1)

### 思路
先想暴力，核心代码如下：
~~~cpp
for(int t=1;t<=q;t++){
  int s,d,k,res=0;cin>>s>>d>>k;
  for(int i=1;i<=k;i++)
    res+=a[s+(i-1)*d]*i;
  cout<<res<<' ';
}
~~~
该算法需要 $O\left(n\cdot q\right)$ 的复杂度，无法通过。

我们考虑优化。该算法复杂度太大是因为 $d=1$ 时 $k$ 在最坏情况下与 $n$ 同级。如果全部预处理空间复杂度又会超。我们考虑一个折中的方案。

若 $d\ge \sqrt n$ 则暴力，单次复杂度为 $O\left( \frac{n}{\sqrt n}=\sqrt n \right)$ 。否则使用后缀和进行维护，预处理复杂度 $O\left( n\cdot\sqrt n\right)$，查询复杂度 $O\left(1\right)$。

如何维护后缀和？设 $sum_{i,j}$ 表示 $a_i+a_{i+j}\cdot2+a_{i+2j}\cdot3\dots+a_{i+ \left(k-1 \right)\cdot d}\cdot k$,其中 $a_{i+ \left(k-1 \right)\cdot d}$ 项是序列末尾。$sum1_{i,j}$ 表示 $a_i+a_{i+j}+a_{i+2j}\dots+a_{i+ \left(k-1 \right)\cdot d}$。递推式见代码。
### code
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+1e4,V=350; 
int n,q,a[N],v;
int sum[N][V],sum1[N][V];
signed main(){
  int T;cin>>T;
  while(T--){
    cin>>n>>q;v=sqrt(n);
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=n;i>=1;i--)
      for(int j=1;j<=v;j++){
        sum1[i][j]=sum1[i+j][j]+a[i];
        sum[i][j]=sum[i+j][j]+sum1[i][j];
      }
    for(int t=1;t<=q;t++){
      int s,d,k,res=0;cin>>s>>d>>k;
      if(d>=v)
        for(int i=1;i<=k;i++)
          res+=a[s+(i-1)*d]*i;
      else 
        res=sum[s][d]-sum[s+k*d][d]-k*sum1[s+k*d][d];
      cout<<res<<' ';
    }
    puts("");
  }
  return 0;
}

---

## 作者：RAND_MAX (赞：0)

考虑根号分治。

对于 $d>\sqrt{n}$，由于至多跳 $\frac{n}{d}\le\sqrt{n}$ 步，暴力统计即可。时间复杂度 $O(n\sqrt{n})$。

对于 $d\le\sqrt{n}$，考虑对每个 $d$ 及其每个 $s$ 维护后缀和。由于式子里有一个 $i$ 的系数，故需进行两次后缀和。查询时，前后二阶后缀和相减后会多出 $k$ 的系数，只需减去 $k$ 倍的一阶后缀和即可。时间复杂度 $O(n\sqrt{n})$。

故而总时间复杂度 $O(n\sqrt{n})$，可以通过本题。


```cpp
#include<bits/stdc++.h>
#define int long long
#define gc getchar
//char buf[1<<20],*p1,*p2;
//#define gc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?EOF:*p1++)
#define R read()
using namespace std;
int read()
{
	int x=0,f=1;
	char c=gc();
	while(c>'9'||c<'0'){if(c=='-') f=-1;c=gc();}
	while(c>='0'&&c<='9') x=(x<<1)+(x<<3)+c-48,c=gc();
	return x*f;
}
void write(int x,char xx)
{
	static int st[35],top=0;
	if(x<0){x=-x;putchar('-');}
	do
	{
		st[top++]=x%10,x/=10;
	}while(x);
	while(top) putchar(st[--top]+48);
	putchar(xx);
}
#define N 150010
#define B 320
int n,a[N],q,s,d,k,s1[B][N],s2[B][N],S,su;
void solve()
{
	n=R,q=R,S=sqrt(n);
	for(int i=1;i<=n;i++) a[i]=R;
	for(int i=1;i<=S;i++) 
	{
		for(int j=n+S;j>=0;j--) s1[i][j]=s2[i][j]=0;
		for(int j=n;j>=0;j--) s1[i][j]=s1[i][j+i]+a[j],s2[i][j]=s2[i][j+i]+s1[i][j];
	}
	while(q--)
	{
		s=R,d=R,k=R,su=0;
		if(d>S) for(int i=1;i<=k;i++) su+=a[s+(i-1)*d]*i;
		else su=s2[d][s]-s2[d][d*k+s]-k*s1[d][d*k+s];
		write(su,' ');
	}
	puts("");
}
int T;
signed main()
{
	T=R;
//	T=1;
	while(T--) solve();
	return 0;
}
```

---

## 作者：zhangli828 (赞：0)

## 题目大意
给定你长为 $n$ 的数组 $a$，让你回答 $q$ 次问题，每次问题给你 $s,d,k$ 让你求 $Q(s,d,k)$ 其中 $Q(s,d,k)=a_s+a_{s+d}\times 2+\cdots+a_{s+d\times(k-1)}\times k$。
## 题目思路
我们发现如果在询问的时候处理复杂度为 $k$，但是预处理的话要 $O(nk)\approx O(n^2)$。我们这是就可以想到预处理 $\sqrt{n}$ 的数据，这样在询问时只用处理 $k\ge\sqrt{n}$ 的数据即可，所以按这种思路预处理 $O(n\sqrt{n})$，询问 $O(q\sqrt{n})$，一共也才 $O(n\sqrt{n})$。
## 题目解法
我们可以用 $p_{0,i,j}=Q((i-1)\bmod j+1,j,i),p_{1,i,j}=a_{(i-1)\bmod j+1}+\cdots+a_i$，这样在回答时只要求出 $p_{1,d,r}-\frac{p_{1,d,l}-(l+d-1)}{d\times(p_{0,d,r}-p_{0,d,l})}$ 即可，其中 $l=\max(s-d,0),r=s+d\times(k-1)$。
## 题目代码
```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int kMaxN = 1e5 + 10, kMaxM = 310;

int a[kMaxN], p[2][kMaxM][kMaxN], t, n, q;

signed main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  for (cin >> t; t--; cout << '\n') {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
      for (int j = 1; j < kMaxM; j++) {
        p[0][j][i] = (i >= j ? p[0][j][i - j] : 0) + a[i], p[1][j][i] = (i >= j ? p[1][j][i - j] : 0) + (i + j - 1) / j * a[i];
      }
    }
    for (int i = 1, s, d, k; i <= q; i++) {
      cin >> s >> d >> k;
      if (d < kMaxM) {
        cout << p[1][d][s + d * (k - 1)] - p[1][d][max(s - d, 0ll)] - (max(s - d, 0ll) + d - 1) / d * (p[0][d][s + d * (k - 1)] - p[0][d][max(s - d, 0ll)]) << ' ';
      } else {
        int ans = 0;
        for (int j = 0; j < k; j++) {
          ans += a[s + j * d] * (j + 1);
        }
        cout << ans << ' ';
      }
    }
  }
  return 0;
}
```

---

## 作者：iPhoneSX (赞：0)

## 题解
今天模拟赛出了[一道根号分治的题](https://www.luogu.com.cn/problem/P10761)，本蒟蒻场上没有做出来，所以来做这道题巩固一下。

### 根号分治
一种优化思想，将问题按照不同的数据规模划分，分别使用不同的算法进行解决，一般将规模按照**根号**进行分类。

对于本道题目，要求从某点开始间隔为定值 $d$ 的元素之和。那么当 $d > \sqrt{n}$ 时，往后不会遍历到超过 $\sqrt{n}$ 个元素，故可以直接暴力累加。

当 $d \le \sqrt{n}$ 时，如果暴力累加会超时，我们可以预处理后缀和，然后 $O(1)$ 输出答案。 

### 处理后缀和
本题还有一处要点是后缀和上有一个系数。我们先设一个后缀和数组 $sum_{i,j}$ 表示从元素 $i$ 开始，间隔为 $j$，一直到最后的和。$sum$ 数组预处理如下：
```cpp
for(int i=n;i>=1;i--){
  for(int j=1;j<=m;j++){
    if(i+j>n){
      sum[i][j]=a[i];
      continue;
    }
    sum[i][j]=sum[i+j][j]+a[i];
  }
}
``````
再设一个数组 $ans_{i,j}$ 表示从元素 $i$ 开始，间隔为 $j$，一直到最后的和乘上每一项的系数。即 $ans_{i,j}=\displaystyle\sum a_{i+(k-1)d}\times k$ 而这个 $ans$ 数组其实就是 $sum$ 的后缀和，用同样的方法处理即可。

对于给定的 $s$，$n$，$k$，设 $e=s+d \times k$ 即所求最后一个元素的下一个位置。而答案就是 $ans_{s,d}-ans_{e,d}-k \times sum_{e,d}$，应该还挺好理解的。

完整代码：
```cpp
#include<algorithm>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<iomanip>
#include<iostream>
#include<list>
#include<map>
#include<queue>
#include<set>
#include<stack>
#include<string>
#include<vector>
#define ll long long
#define int long long
#define DBG(x) cout << #x << "=" << x << endl
#define inf 0x3f3f3f3f
#define mod 1000000007
#define N 100005
#define M 1000005
using namespace std;
template <typename T>
void read(T& x) {
    x = 0;
    ll t = 1;
    char ch;
    ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') {
            t = -1;
        }
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + (ch - '0');
        ch = getchar();
    }
    x *= t;
}
template <typename T, typename... Args>
void read(T& first, Args&... args) {
    read(first);
    read(args...);
}
template <typename T>
void write(T y) {
    T x = y;
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) {
        write(x / 10);
    }
    putchar(x % 10 + '0');
}
template <typename T, typename... Ts>
void write(T arg, Ts... args) {
    write(arg);
    if (sizeof...(args) != 0) {
        putchar(' ');
        write(args...);
    }
}
int t,n,m,q,a[N],s,d,k;
int sum[N][350],ans[N][350];
signed main(){
   read(t);
   while(t--){
      read(n,q);
      m=sqrt(n);
      for(int i=1;i<=n;i++){
         read(a[i]);
      }
      for(int i=n;i>=1;i--){
         for(int j=1;j<=m;j++){
            if(i+j>n){
               sum[i][j]=a[i];
               continue;
            }
            sum[i][j]=sum[i+j][j]+a[i];
         }
      }
      for(int i=n;i>=1;i--){
         for(int j=1;j<=m;j++){
            if(i+j>n){
               ans[i][j]=sum[i][j];
               continue;
            }
            ans[i][j]=ans[i+j][j]+sum[i][j];
         }
      }
      while(q--){
         read(s,d,k);
         if(d>m){
            int cnt=0;
            for(int i=s,j=1;i<=s+d*(k-1);i+=d,j++){
               cnt=cnt+a[i]*j;
            }
            write(cnt);
            putchar(' ');
         }
         else{
            int e=s+d*k;
            if(e>n){
               write(ans[s][d]);
               putchar(' ');
            }
            else{
               write(ans[s][d]-ans[e][d]-k*sum[e][d]);
               putchar(' ');
            }
         }
      }
      putchar('\n');
   }
   return 0;
}
`````````

---

## 作者：ChenYanlin_20 (赞：0)

### 思路
题意为从 $a$ 数组下标 $s$ 开始跨度为 $d$ 的所有变量和。不难发现，当 $d$ 足够大时，$k$ 一定小可以暴力解决，而当 $d$ 非常小时，空间足够，可以使用数组预处理。

考虑根号分治：

- 当 $d \ge \sqrt{n}$ 时，暴力枚举。
- 当 $d < \sqrt{n} $ 时，定义 $ f_{i,j}$ 表示答案，$ s_{i,j} $ 表示此刻下标为 $i$，跨度为 $j$ 一直加到右端点的和，我们在求 $ f $ 的时候每次加上一个相同 $i,j$ 的 $s$，答案就可以恰好对应 $a_s $ 到 $ a_{s+(k-1)\times d}$ 分别乘上 $1$ 到 $k$ 的和。

   由于答案不一定加到末尾，设最后下标 $top$ 为 $s+(k-1)\times d$，需要减去在$top+d$往后的所有数，但是会发现 $f_{top+d,d}$ 中 $a_{top+d}$ 往后的乘数都是从 $1$ 开始的，而在 $f_{s,d}$ 中位于后方，乘数很大始为 $k+1$，所以将 $f_{s,d}-f_{top+d,d}$ 再减去一个 $k\times s_{top+d,d}$，即 $k$ 倍后方的和，就是最终答案。











### CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
long long t,n,q,a[N],s[N][320],f[N][320];
signed main(){
	cin>>t;
	for(int l=1;l<=t;l++){
		cin>>n>>q;
		int sq=sqrt(n);
		for(int i=1;i<=n+sq;i++) for(int j=1;j<=319;j++) s[i][j]=0,f[i][j]=0;
		for(int i=1;i<=n;i++) cin>>a[i];
		for(int i=n;i>=1;i--) for(int j=1;j<=sq;j++) s[i][j]=s[i+j][j]+a[i];
		for(int i=n;i>=1;i--) for(int j=1;j<=sq;j++) f[i][j]=f[i+j][j]+s[i][j];
		for(int j=1;j<=q;j++){
			int s,d,k;
			cin>>s>>d>>k;
			if(d>=sq){
				long long ans=0;
				for(int i=1;i<=k;i++) ans+=a[s+(i-1)*d]*i; 
				cout<<ans<<" ";
			}
			else cout<<f[s][d]-f[s+d*k][d]-k*s[s+d*k][d]<<endl; 
		}
		cout<<'\n';
	}
	return 0;
}
```

---

## 作者：ZLCT (赞：0)

# CF1921F Sum of Progression
## 题目翻译
给定一个长度为 $n$ 的序列 $a$，每次给出三个正整数 $s,d,k$，求 $\sum_{i=1}^k{a_{s+(i-1)\times d}\times i}$。
## 区间求和？
这个题面本质上也可以看作是一种区间求和，只不过是带权的。\
而我们看到区间求和一般想到的就是前缀和或者线段树。\
先看一下线段树，由于线段树只能求连续区间和，所以我们肯定要进一步处理。\
我们思考每次计算，我们求和的元素都是隔一段定长，这启示我们每个节点可以对每个 $d$ 都记录一个 $val$，每次取题目给出的 $d$ 值对应的 $val$ 即可。\
但是问题又来了，如何处理带的权值 $i$ 呢？\
我们思考一下，假设我们只需要求第一个 $d$ 到某一个 $d$ 的权值该怎么办呢？当然就是在加点权的时候直接把当前是第几个 $d$ 乘到权值上即可。\
而通过这个方法我们继续推导起始点不是第一个 $d$ 的情况，那就相当于我们区间每个元素的权值都多加了前面不属于区间的 $d$ 的个数 $(设为w)$ 遍。（因为相当于 $i$ 从 $1$ 开始变成从 $w$ 开始）\
那我们也好办，因为每个元素都减去相同的遍数，所以我们只需要再维护区间不带权的元素和，并将原来的区间和减去 $w\times$ 区间不带权和即可。\
这样显然是不行的，因为观察数据范围我们发现如果我们要对每一个 $d$ 都开一个变量，那么空间复杂度和时间复杂度都是 $O(n^2)$ 级别，甚至还有线段树的 $\log$。\
那我们接下来考虑优化。\
对于这种每次都跳一段区间的题，我们通常可以考虑根号分治。\
因为在 $d>\sqrt{n}$ 时，如果我们暴力跳，最多跳 $\lfloor{\frac{n}{d}}\rfloor\le\sqrt{n}$ 次。\
而这样对于 $d\le\sqrt{n}$ 的情况，我们就可以利用线段树维护了。\
但是仔细观察你会发现虽然时间复杂度勉强可以，但是空间复杂度却因为线段树 $4$ 的常数会爆炸。\
还记得我们一开始的两种区间和方法吗？\
每错，既然我们不需要中途产生修改，那么我们完全可以利用前缀和进行代替，这样空间时间复杂度就比较宽松了。
## code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+666;
int n,q,a[N],sum[N][333],num[N][333],f[N][333];
void init(){
    for(int i=0;i<=n+5;++i){
        for(int j=0;j<=300;++j){
            sum[i][j]=0;
            num[i][j]=0;
            f[i][j]=0;
        }
    }
    for(int i=1;i<=n;++i){
        for(int j=1;j<=300;++j){
            num[i][j]=num[max(i-j,0ll)][j]+1;
            sum[i][j]=sum[max(i-j,0ll)][j]+a[i]*num[i][j];
            f[i][j]=f[max(i-j,0ll)][j]+a[i];
        }
    }
}
void solve(){
    cin>>n>>q;
    for(int i=1;i<=n;++i){
        cin>>a[i];
    }
    init();
    while(q--){
        int s,d,k;cin>>s>>d>>k;
        if(d>300){
            int res=0,cnt=0;
            for(int i=s;i<=s+d*(k-1);i+=d){
                res+=a[i]*(++cnt);
            }
            cout<<res<<' ';
        }else{
            int t=s+d*(k-1);
            int ans=sum[t][d]-sum[max(0ll,s-d)][d];
            if(num[s][d]>1)ans-=(num[s][d]-1)*(f[t][d]-f[max(0ll,s-d)][d]);
            cout<<ans<<' ';
        }
    }
    cout<<'\n';
}
signed main(){
    int T;cin>>T;
    while(T--)solve();
    return 0;
}
```

---

## 作者：liugh_ (赞：0)

[CF1921F Sum of Progression](https://www.luogu.com.cn/problem/CF1921F)

根号分治——优雅的暴力。

---

给定 $\{a_i\}_{i=1}^{n}$ 和 $q$ 次询问，每次询问给定 $s,k,l$，求 $\sum_{i=1}^{l} i\cdot a_{s+(i-1)k}$。

$\forall s,k,l,s+(l-1)k\le n\le 10^5,|a_i|\le 10^8,q\le 2\cdot 10^5$。

---

若忽略后面乘上的 $i$，问题就变成了[根号分治板子](https://www.luogu.com.cn/problem/CF1207F)。

此题取 $B=\sqrt{n}$ 即可，对于 $k>B$ 的情况，暴力计算。对于 $k\le B$ 的情况，朴素地考虑维护 
$$
f(k,s,l)=\sum_{i=s}^{s+(l-1)k} [i\equiv s \bmod k]\cdot a_i\cdot (i-s)/k
$$
空间复杂度 $O(n^2\sqrt{n})$，显然会爆。考虑用类似字符串哈希的思想，只记录 
$$
f(k,s)=\sum_{i=s}^{n} [i\equiv s \bmod k]\cdot a_i\cdot (i-s)/k
$$
查询时去除多余的部分即可。

关键点在于如何去除多余的部分。下面以 $n=9,(s,k,l)=(1,2,2)$ 为例，有
$$
f(2,1)=a_1\cdot 1+a_3\cdot 2+\red{a_5}\cdot 3+\red{a_7}\cdot 4+\red{a_9}\cdot 5
$$
$$
f(2,5)=\red{a_5}\cdot 1+\red{a_7}\cdot 2+\red{a_9}\cdot 3
$$
容易发现上下两式中红色的部分相差 
$$
2(a_5+a_7+a_9)
$$
于是考虑记录
$$
g(k,s)=\sum_{i=s}^{n} [i\equiv s \bmod k]\cdot a_i
$$
故有
$$
ans=f(2,1)-f(2,5)-2\cdot g(2,5)
$$
事实上，一般地，我们有
$$
ans=f(k,s)-f(k,s+lk)-l\cdot g(k,s+lk)
$$
时间复杂度 $O(q\sqrt{n})$，空间复杂度 $O(n\sqrt{n})$。
```cpp
#define i64 long long
const int Maxn = 100400 + 3; // 多开sqrt(n)，后面可以省去特判
const int Maxb = 400 + 3; // sqrt(n)

int N, Q, B, a[Maxn];
i64 g[Maxb][Maxn];
i64 f[Maxb][Maxn];

signed main() {
	int Case; fr(Case); while (Case--) {
		fr(N), fr(Q); B = __builtin_sqrt(N);
		for (int i = 1; i <= N; ++i) fr(a[i]);
		for (int k = 1; k <= B; ++k)
			fill(g[k] + N + 1, g[k] + N + B + 1, 0),
			fill(f[k] + N + 1, f[k] + N + B + 1, 0); // 只有必要清空数组末的部分
		for (int k = 1; k <= B; ++k) 
			for (int i = N; i >= 1; --i) 
				g[k][i] = g[k][i + k] + a[i];
		for (int k = 1; k <= B; ++k) 
			for (int i = N; i >= 1; --i)
				f[k][i] = f[k][i + k] + g[k][i + k] + a[i];
		while (Q--) {
			int s, k, l; fr(s), fr(k), fr(l);
			if (k > B) {
				i64 res = 0;
				for (int j = 1, i = s; j <= l; ++j, i += k) 
                  	res += 1ll * a[i] * j;
				fw(res), putchar(32);
			}
			else 
              	fw(f[k][s] - f[k][s + k * l] - l * g[k][s + k * l]), 
          		putchar(32);
		}
		putchar(10);
	}
	return flush(), 0;
}
```

---

## 作者：vicky2048_2 (赞：0)

感觉这题的后缀和套后缀和很妙啊。

对做题数少到离谱的我来说很难想到这么构造呐。

------------

看题目式子，发现是根号分治题经典的隔段跳。

于是这题的基本解决思路就确定了：

- $d>\sqrt{n}$：暴力跳算答案。此时每跳一步跨幅都很大，最终跳的步数不会超过 $\sqrt{n}$。
- $d\leq\sqrt{n}$：先进行根号分治经典的答案预处理，然后询问时直接 $O(1)$ 输出答案即可。

思考如何预处理 $d\leq\sqrt{n}$ 时所有 $s,k$ 对应的答案。

对于一次求和计算，我们发现 $a_s\sim a_{s+(k-1)*d}$ 的被计算次数是从 $1\sim k$ 严格单调递增的。

这里我们可以先计算出对于 $a$ 数组的后缀和数组 $sum_{i,j}(sum_{i,j}=\sum\limits_{k=0}^{i+k\cdot j\leq n}a_{i+k\cdot j}=sum_{i,j+i}+a_j)$，$i,j$ 分别表示每次向后跳跃的步幅、向后跳跃的起点。

然后我们可以对 $sum_{i,j}$ 再求一次后缀和 $ssum_{i,j}(ssum_{i,j}=\sum\limits_{k=0}^{i+k\cdot j\leq n}sum_{i,i+k\cdot j}=ssum_{i,j+i}+sum_{i,j})$。

这里 $ssum_{i,j}$ 的意义即为，以 $j$ 为起点，每次向后跳跃 $i$，经过的所有位置 $j'$ 的后缀和 $sum_{i,j'}$ 的加和。

我们发现这样构造出来的 $ssum_{i,j}$ 刚好使得 $a_{i}\sim a_{i+k\cdot j}(i+k\cdot j\leq n,i+(k+1)\cdot j>n)$ 的被计算次数从 $1$ 到 $k+1$ 严格单调递增。

最后我们手摸一下就能得到，最终的答案即为 $ssum_{d,s}-k\cdot sum_{d,s+k\cdot d}-ssum{d,s+k\cdot d}$。

---

```cpp
#include<bits/stdc++.h>
#define N 100005
#define S 320
#define int long long
using namespace std;
int n,q,t,s,d,k,sq,a[N+S],sum[S][N+S],ssum[S][N+S];
signed main(){
    scanf("%lld",&t);
    while(t--){
        scanf("%lld%lld",&n,&q);
        for(int i=1;i<=n;++i) scanf("%lld",&a[i]);
        sq=sqrt(n);
        for(int i=1;i<=n+sq;++i) for(int j=1;j<=sq;++j) sum[j][i]=ssum[j][i]=0;
        for(int i=1;i<=sq;++i) for(int j=n;j;--j) sum[i][j]=sum[i][j+i]+a[j];
        for(int i=1;i<=sq;++i) for(int j=n;j;--j) ssum[i][j]=ssum[i][i+j]+sum[i][j];
        while(q--){
            scanf("%lld%lld%lld",&s,&d,&k);
            if(d>sq){
                int ans=0;
                for(int i=1;i<=k;++i) ans+=a[s+(i-1)*d]*i;
                printf("%lld ",ans);
                continue;
            }
            printf("%lld ",ssum[d][s]-k*sum[d][s+k*d]-ssum[d][s+k*d]);
        }
        putchar('\n');
    }
    return 0;
}
```

---

## 作者：xuyiyang (赞：0)

### Solution
发现下标不断加 $d$，考虑根号分治。

设置一个阈值 $B$，当 $d \ge B$ 时直接暴力，复杂度 $O(\frac{n}{B})$。对于 $d \lt B$，考虑预处理出 $g_{i,j,p}=\sum \limits _ {k \bmod i=j,k \le p} a_k$，$f_{i,j,p} = \sum \limits _ {k \bmod i =j, k\le p}w_k \times S_{i,k}$。其中 $S_{i,k}$ 是第 $k$ 项在余数为 $k \bmod i$ 序列中的位置，可以 $O(1)$ 算出。预处理这部分复杂度是 $O(nB)$ 的。

对于询问，首先加上 $f$ 上的前缀和，发现会多加几次 $g$。对于多加部分，发现 $S_{s,k}$ 要变成 $1$，每个都要减去 $(S_{s,k}-1)\times a_k$，可以用 $g$ 计算。

令 $s$ 为首项，$e$ 为末项，则答案就为 $f_{d,s \bmod d,e}-f_{d,s\bmod d,s-d}-(S_{d,s}-1) \times (g_{d,s \bmod d,e}-g_{d,s \bmod d,s-d})$。可以做到 $O(1)$ 询问。

总复杂度为 $O(T(nB+q\frac{n}{B}))$，根据均值不等式取 $B = \sqrt n$，得最后复杂度为 $O(T(n+q)\sqrt n)$，可以通过。实现时注意将 $f$ 和 $g$ 压成两维，不然用 vector 会被卡常。
[Code](https://codeforces.com/contest/1921/submission/243715658)。

---

