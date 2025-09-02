# [ARC166B] Make Multiples

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc166/tasks/arc166_b

整数列 $ A=(A_1,\ldots,A_N) $ および，正整数 $ a,b,c $ が与えられます．

あなたはこの数列に対して，以下の操作を（$ 0 $ 回を含め）何回でも行うことができます．

- $ 1\leq\ i\leq\ N $ となる整数 $ i $ をひとつ選ぶ．$ A_i $ を $ A_i+1 $ で置き換える．
 
あなたの目的は，数列 $ A $ の中に，$ a $ の倍数，$ b $ の倍数，$ c $ の倍数がいずれもひとつ以上存在するようにすることです． 目的を達成するために必要な操作回数の最小値を求めてください．

## 说明/提示

### 制約

- $ 1\leq\ N\leq\ 2\times\ 10^5 $
- $ 1\leq\ a,\ b,\ c\ \leq\ 10^6 $
- $ 1\leq\ A_i\leq\ 10^{18} $
 
### Sample Explanation 1

操作を $ 2 $ 回行い $ A\ =\ (8,10,12) $ とすることで目的を達成できます．

### Sample Explanation 2

操作を $ 1 $ 回行い $ A\ =\ (14,11,60) $ とすることで目的を達成できます．

### Sample Explanation 3

操作を $ 3 $ 回行い $ A\ =\ (8,17,5,30,40,13) $ とすることで目的を達成できます．

### Sample Explanation 4

操作を $ 876537210887543205 $ 回行い $ A\ =\ (999994000010999994) $ とすることで目的を達成できます．

## 样例 #1

### 输入

```
3 3 4 5
8 9 11```

### 输出

```
2```

## 样例 #2

### 输入

```
3 3 4 5
14 11 59```

### 输出

```
1```

## 样例 #3

### 输入

```
6 10 20 30
8 17 5 28 39 13```

### 输出

```
3```

## 样例 #4

### 输入

```
1 999997 999998 999999
123456789123456789```

### 输出

```
876537210887543205```

# 题解

## 作者：DerrickLo (赞：7)

感觉比 A 简单。

显然可以考虑 `dp`。

可以想到 $dp[i][0/1][0/1][0/1]$ 表示前 $i$ 个数是否有 $a$ 的倍数，是否有 $b$ 的倍数，是否有 $c$ 的倍数。

那么我们先预处理出来每个数变成某个数的倍数要加上多少，然后暴力转移即可。

```cpp
#include<bits/stdc++.h>
#define int long long
#define lcm(a,b) (a*b/__gcd(a,b))
using namespace std;
int n,a,b,c,x[200005],f[200005][2][2][2],A[200005],B[200005],C[200005],AB[200005],BC[200005],AC[200005],ABC[200005]; 
signed main(){
	cin>>n>>a>>b>>c;
	for(int i=1;i<=n;i++){
		cin>>x[i];
		A[i]=a-(x[i]-1)%a-1;
		B[i]=b-(x[i]-1)%b-1;
		C[i]=c-(x[i]-1)%c-1;
		AB[i]=lcm(a,b)-(x[i]-1)%lcm(a,b)-1;
		BC[i]=lcm(c,b)-(x[i]-1)%lcm(c,b)-1;
		AC[i]=lcm(a,c)-(x[i]-1)%lcm(a,c)-1;
		ABC[i]=lcm(lcm(a,b),c)-(x[i]-1)%lcm(lcm(a,b),c)-1;
	}
	memset(f,0x3f,sizeof f);
	f[0][0][0][0]=0;
	for(int i=1;i<=n;i++){
		f[i][0][0][0]=f[i-1][0][0][0];
		f[i][0][0][1]=min(f[i-1][0][0][1],f[i-1][0][0][0]+C[i]);
		f[i][0][1][0]=min(f[i-1][0][1][0],f[i-1][0][0][0]+B[i]);
		f[i][1][0][0]=min(f[i-1][1][0][0],f[i-1][0][0][0]+A[i]);
		f[i][0][1][1]=min({f[i-1][0][1][1],f[i-1][0][0][1]+B[i],f[i-1][0][1][0]+C[i],f[i-1][0][0][0]+BC[i]});
		f[i][1][0][1]=min({f[i-1][1][0][1],f[i-1][0][0][1]+A[i],f[i-1][1][0][0]+C[i],f[i-1][0][0][0]+AC[i]});
		f[i][1][1][0]=min({f[i-1][1][1][0],f[i-1][1][0][0]+B[i],f[i-1][0][1][0]+A[i],f[i-1][0][0][0]+AB[i]});
		f[i][1][1][1]=min({f[i-1][1][1][1],f[i-1][1][1][0]+C[i],f[i-1][1][0][1]+B[i],f[i-1][0][1][1]+A[i],f[i-1][0][0][1]+AB[i],f[i-1][0][1][0]+AC[i],f[i-1][1][0][0]+BC[i],f[i-1][0][0][0]+ABC[i]}); 
	}
	cout<<f[n][1][1][1];
	return 0;
}
```

---

## 作者：littlebug (赞：3)

## Solution

很显然的 dp。

无脑地设计一个状态，设 $f_{i,0/1,0/1,0/1}$ 为考虑前 $i$ 个，是否有 $a$ 的倍数，是否有 $b$ 的倍数，是否有 $c$ 的倍数的最少操作，显然可以枚举子集转移。

然后可以对于每个 $a_i$ 预处理出到达某个状态 $0/1,0/1,0/1$ 的最少操作次数，求个 lcm 即可，这样会方便一些。

复杂度 $O(2^{2m}n)$，其中 $m = 3$。

## Code

```cpp
int n,m[3],a[N][2][2][2],f[N][2][2][2];

template <typename T> il T gcd(T a,T b){if(!a||!b) return a?:b; while(b^=a^=b^=a%=b); return a;}
template <typename T> il T lcm(T a,T b){if(!a||!b) return a?:b; return a*b/gcd(a,b);}
template <typename T,typename ... Args> il int gcd(T a,T b,Args ... c){return gcd(gcd(a,b),c...);}
template <typename T,typename ... Args> il int lcm(T a,T b,Args ... c){return lcm(lcm(a,b),c...);}

signed main()
{
#define pos x][y][z
    read(n,m[0],m[1],m[2]);
    {
        int g[2][2][2];
        rep(x,0,1) rep(y,0,1) rep(z,0,1) (x|y|z) && (g[pos]=lcm(x?m[0]:0ll,y?m[1]:0ll,z?m[2]:0ll));

        int tmp;
        rep(i,1,n)
        {
            read(tmp);
            rep(x,0,1) rep(y,0,1) rep(z,0,1) (x|y|z) && (a[i][pos]=g[pos]-(tmp%g[pos]?:g[pos]));
        }
    }

	rep(x,0,1) rep(y,0,1) rep(z,0,1) f[1][pos]=a[1][pos];
    rep(i,2,n) rep(x,0,1) rep(y,0,1) rep(z,0,1)
    {
    	if(!(x|y|z)) continue;
        f[i][pos]=f[i-1][pos];
        rep(_x,0,x) rep(_y,0,y) rep(_z,0,z) f[i][pos]=min(f[i][pos],f[i-1][_x][_y][_z]+a[i][x^_x][y^_y][z^_z]); // 显然用异或方便一些，可以手推一下这个式子是否成立
    }

    write(f[n][1][1][1]);

    return 0;
}
```

---

华风夏韵，洛水天依！

---

## 作者：樱雪喵 (赞：3)

## Solution 1

容易知道令 $x$ 成为 $y$ 的倍数，所需的最小操作次数为 $(y-(x\bmod y))\bmod y$。  
我们分别令 $x=a,b,c,ab,bc,abc$，求每个数成为 $x$ 的倍数所需的最小次数，并升序排序。那么当前 $x$ 下只有操作次数最小的三个 $a_i$ 可能被计入答案。  
这样我们一共获得了至多 $X=3\times 6=18$ 个 $a_i$，暴力在它们之间 $O(X^3)$ 枚举哪三个数成为 $a,b,c$ 的倍数，统计最小值即可。

## Solution 2

考虑状压。设 $f_{i,j}$ 表示考虑了前 $i$ 个数，已经存在倍数的数为集合 $j(j\in[0,2^3))$。  
枚举当前数要修改成哪些数的倍数，那么有:
$$f_{i,j\cup k}\gets \min\{f_{i-1,j}+w(i,k)\}$$

直接转移，令 $M=3$，时间复杂度 $O(n 2^{2M})$。

代码是 Solution 1，赛时写得很复杂，菜。

```cpp
#define int long long
const int N=2e5+5;
int n,a[N],vis[N];
struct node{int id,x;} c[N];
int b[3],L[N];
vector<int> d;
il bool cmp(node x,node y) {return x.x<y.x;}
il int lcm(int a,int b) {return a*b/__gcd(a,b);} 
signed main()
{
	n=read(); 
	for(int i=0;i<3;i++) b[i]=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int s=1;s<8;s++)
	{
		int lc=1;
		for(int i=0;i<3;i++) if((s>>i)&1) lc=lcm(lc,b[i]);
		for(int i=1;i<=n;i++) c[i].id=i,c[i].x=a[i]%lc?lc-a[i]%lc:0;
		sort(c+1,c+n+1,cmp);
		for(int i=1;i<=min(n,3ll);i++) 
			if(!vis[c[i].id]) vis[c[i].id]=1,d.push_back(a[c[i].id]);
	}
	int ans=3e18;
	for(int i=0;i<d.size();i++)
	{
		for(int j=0;j<d.size();j++)
		{
			for(int k=0;k<d.size();k++)
			{
				int res=0;
				for(int l=0;l<d.size();l++) L[l]=1;
				L[i]=lcm(L[i],b[0]),L[j]=lcm(L[j],b[1]),L[k]=lcm(L[k],b[2]);
				for(int l=0;l<d.size();l++) res+=d[l]%L[l]?L[l]-d[l]%L[l]:0;
				ans=min(ans,res);
			}
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：Fislett (赞：3)

状压 DP。设 $dp_{i,j}$ 表示考虑完前 $i$ 个数，倍数拥有情况为 $j$ 时最小的操作次数。

显然，对于每一个数，有以下八种情况：

1. 不变。
1. 变为 $a$ 的倍数。
1. 变为 $b$ 的倍数。
1. 变为 $c$ 的倍数。
1. 变为 $\operatorname{lcm}(a,b)$ 的倍数。
1. 变为 $\operatorname{lcm}(b,c)$ 的倍数。
1. 变为 $\operatorname{lcm}(a,c)$ 的倍数。
1. 变为 $\operatorname{lcm}(a,b,c)$ 的倍数。

则转移方程为 $dp_{S \cup u} \gets dp_{S} + w_u$。

答案为 $dp_{n, 7}$。

## $Code:$

```cpp
#include <bits/stdc++.h>
#define int long long 
using namespace std;
#define rint register int 
inline int read()
{
    int x = 0, flag = 1; char c = getchar();
    while (!isdigit(c) && c != '-') c = getchar();
    if (c == '-') flag = -1; else x = (c ^ 48); c = getchar();
    while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
    return flag * x;
}
inline void print(rint x, rint flag = 1)
{
    if (x < 0) putchar('-'), x = ~(x - 1);
    if (x > 9) print(x / 10, 0);
    putchar(x % 10 + 48);
    if (flag) putchar(flag & 1 ? ' ' : '\n');
}
int n, a, x, y, z, dp[200005][8], tmp[8], w[8];
inline int gcd(rint x, rint y) {return y ? gcd(y, x % y) : x;}
inline int lcm(rint x, rint y) {return x / gcd(x, y) * y;}
signed main()
{
    n = read(), x = read(), y = read(), z = read();
    w[1] = x, w[2] = y, w[4] = z, w[3] = lcm(x, y), w[5] = lcm(x, z), w[6] = lcm(y, z), w[7] = lcm(x, lcm(y, z));
    memset(dp, 0x7f, sizeof(dp)); dp[0][0] = 0;
    for (rint i = 1; i <= n; ++ i)
    {
        rint x = read();
        for (rint j = 1; j < 8; ++ j) tmp[j] = (x + w[j] - 1) / w[j] * w[j] - x;
        dp[i][0] = 0;
        for (rint j = 1; j < 8; ++ j)
        {
            dp[i][j] = dp[i - 1][j];
            for (rint k = j; k; k = (k - 1) & j)
                dp[i][j] = min(dp[i][j], dp[i - 1][j ^ k] + tmp[k]);
        }
    }
    print(dp[n][7]);
    return 0;
}
```

---

## 作者：I_Love_DS (赞：2)

称条件 $\text X$ 为满足数字是字母 $\text X$ 的倍数。

注意到到限制条件只有三个，我们可以直接维护所有情况下（条件 $\text {a,b,c}$ 都不满足和条件 $\text {a,b,c}$ 都满足除外）的前缀后缀最小值。

于是史山代码脱口而出。

```cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int N = 2e5 + 50;

int n;
ll a, b, c, ab, ac, bc, abc, d[N];

struct node {
	ll A, B, C, AB, AC, BC; 
} f[N], l[N], r[N];

ll gcd(ll a, ll b) {return b ? gcd(b, a % b) : a;}
ll lcm(ll a, ll b) {return a / gcd(a, b) * b;}
ll calc(ll a, ll b) {return (a + b - 1) / b * b - a;}

int main() {
	scanf("%d%lld%lld%lld", &n, &a, &b, &c);
	for (int i = 1; i <= n; i++) scanf("%lld", &d[i]);
	ab = lcm(a, b), ac = lcm(a, c), bc = lcm(b, c), abc = lcm(ab, c);
	l[0].A = l[0].B = l[0].C = l[0].AB = l[0].AC = l[0].BC = 1LL << 61;
	r[n + 1].A = r[n + 1].B = r[n + 1].C = r[n + 1].AB = r[n + 1].AC = r[n + 1].BC = 1LL << 61;
    // 如果开到 1LL << 62 会爆 long long，且 (1LL << 61) > 1e18
	for (int i = 1; i <= n; i++) {
		f[i].A = calc(d[i], a);
		f[i].B = calc(d[i], b);
		f[i].C = calc(d[i], c);
		f[i].AB = calc(d[i], ab);
		f[i].AC = calc(d[i], ac);
		f[i].BC = calc(d[i], bc);
	}
	for (int i = 1; i <= n; i++) {
		l[i].A = min(l[i - 1].A, f[i].A);
		l[i].B = min(l[i - 1].B, f[i].B);
		l[i].C = min(l[i - 1].C, f[i].C);
		l[i].AB = min(l[i - 1].AB, f[i].AB);
		l[i].AC = min(l[i - 1].AC, f[i].AC);
		l[i].BC = min(l[i - 1].BC, f[i].BC);
	}
	for (int i = n; i; i--) {
		r[i].A = min(r[i + 1].A, f[i].A);
		r[i].B = min(r[i + 1].B, f[i].B);
		r[i].C = min(r[i + 1].C, f[i].C);
		r[i].AB = min(r[i + 1].AB, f[i].AB);
		r[i].AC = min(r[i + 1].AC, f[i].AC);
		r[i].BC = min(r[i + 1].BC, f[i].BC);
	}
	ll ans = 1LL << 62;
	for (int i = 1; i <= n; i++) {
		ans = min({ans, l[i - 1].A + f[i].B + r[i + 1].C, 
						l[i - 1].A + f[i].C + r[i + 1].B, 
						l[i - 1].B + f[i].A + r[i + 1].C, 
						l[i - 1].B + f[i].C + r[i + 1].A, 
						l[i - 1].C + f[i].A + r[i + 1].B, 
						l[i - 1].C + f[i].B + r[i + 1].A, 
						l[i - 1].AB + f[i].C, 
						l[i - 1].AC + f[i].B, 
						l[i - 1].BC + f[i].A, 
						l[i - 1].A + f[i].BC, 
						l[i - 1].B + f[i].AC, 
						l[i - 1].C + f[i].AB, 
						calc(d[i], abc)}); // 基础前缀后缀求最小值，能做这题这个就能看懂吧（）
	}
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：osfly (赞：2)

发现还没有和我一样的做法。

觉得 B 比 A 好像的多。

令 $A_i$ 为 $a_i$ 变成 $A$ 的倍数最少次数，$B_i,C_i,AB_i,AC_i,BC_i,ABC_i$ 同理。

那么我们就有 $A_i=(A-A\bmod {a_i})\bmod A$，其他同理。

这一大坨东西显然都能在 $O(n)$ 的时间复杂度内算出来。

剩下的就很好写了。

先把所有的东西排个序。

如果 $n\geq 3$，那么可以用 $A_i,B_i,C_i$ 的每一个的前三个来计算答案。

如果 $n\geq 2$，那么可以用 $AB_i,AC_i,BC_i$ 的每一个的前两个来计算答案。

如果 $n\geq 3$，那么可以用 $ABC_i$ 来计算答案。

最后取个 $\min$ 就好了。

记得判断取的数是不是同一个数。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define db double

const int mod=998244353;
const int N=2e5+10;
const ll inf=1e18;

int T;
int n,m,q;
ll a,b,c;
ll ab,ac,bc,abc;
ll p;

ll gcd(ll x,ll y)
{
	if(!y) return x;
	return gcd(y,x%y);
}
ll lcm(ll x,ll y)
{
	return x*y/gcd(x,y);
}

struct num
{
	ll num;
	int id;
}A[N],B[N],C[N],AB[N],AC[N],BC[N],ABC[N];

bool cmp(num x,num y)
{
	return x.num<y.num;
}

ll ans=inf;

int main()
{
	scanf("%d%lld%lld%lld",&n,&a,&b,&c);
	ab=lcm(a,b);
	bc=lcm(b,c);
	ac=lcm(a,c);
	abc=lcm(a,lcm(b,c));
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&p);
        
		//这一部分当时赛时 sb 了写得比较复杂，可以直接用上文的式子来计算。
		A[i]=num{p%a?a-p%a:0,i};
		B[i]=num{p%b?b-p%b:0,i};
		C[i]=num{p%c?c-p%c:0,i};
		
		AB[i]=num{p%ab?ab-p%ab:0,i};
		AC[i]=num{p%ac?ac-p%ac:0,i};
		BC[i]=num{p%bc?bc-p%bc:0,i};
		
		ABC[i]=num{p%abc?abc-p%abc:0,i};
	}
	sort(A+1,A+1+n,cmp);
	sort(B+1,B+1+n,cmp);
	sort(C+1,C+1+n,cmp);
	sort(AB+1,AB+1+n,cmp);
	sort(AC+1,AC+1+n,cmp);
	sort(BC+1,BC+1+n,cmp);
	sort(ABC+1,ABC+1+n,cmp);
	if(n>=3)
	{
		for(int i=1;i<=3;i++)
			for(int j=1;j<=3;j++)
				for(int k=1;k<=3;k++)
				{
					if(A[i].id!=B[j].id&&B[j].id!=C[k].id&&A[i].id!=C[k].id) ans=min(ans,A[i].num+B[j].num+C[k].num);
				}
	}
	if(n>=2)
	{
		for(int i=1;i<=2;i++)
			for(int j=1;j<=2;j++)
			{
				if(AB[i].id!=C[j].id) ans=min(ans,AB[i].num+C[j].num);
			}
		for(int i=1;i<=2;i++)
			for(int j=1;j<=2;j++)
			{
				if(AC[i].id!=B[j].id) ans=min(ans,AC[i].num+B[j].num);
			}
		for(int i=1;i<=2;i++)
			for(int j=1;j<=2;j++)
			{
				if(BC[i].id!=A[j].id) ans=min(ans,BC[i].num+A[j].num);
			}
	}
	ans=min(ans,ABC[1].num);
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：JOE_ZengYuQiao_0928 (赞：1)

场切水题。
### 思路分析
考虑状压 dp。

状态：设 $dp_{i,j}$ 表示操作到到第 $i$ 位时序列中有的 $a,b,c$ 倍数情况为 $j$ 时的最小操作次数。

答案为 $dp_{n,7}$。

状态转移方程如下（声明：因为数组名的原因，我将题目中的 $a,b,c$ 变量名定义为 $x,y,z$）:
```cpp
if((j|0)==j)dp[i][j]=min(dp[i][j],dp[i-1][j^0]);//不变
if((j|1)==j)dp[i][j]=min(dp[i][j],dp[i-1][j^1]+f(a[i],x));//变成 a 的倍数
if((j|2)==j)dp[i][j]=min(dp[i][j],dp[i-1][j^2]+f(a[i],y));//变成 b 的倍数
if((j|3)==j)dp[i][j]=min(dp[i][j],dp[i-1][j^3]+f(a[i],lcm(x,y)));//同时变成 a,b 的倍数
if((j|4)==j)dp[i][j]=min(dp[i][j],dp[i-1][j^4]+f(a[i],z));//变成 c 的倍数
if((j|5)==j)dp[i][j]=min(dp[i][j],dp[i-1][j^5]+f(a[i],lcm(x,z)));//同时变成 a,c 的倍数
if((j|6)==j)dp[i][j]=min(dp[i][j],dp[i-1][j^6]+f(a[i],lcm(y,z)));//同时变成 b,c 的倍数
if((j|7)==j)dp[i][j]=min(dp[i][j],dp[i-1][j^7]+f(a[i],lcm(lcm(x,y),z)));//同时变成 a,b,c 的倍数
```
初始状态为 $dp_{0,0}=0$，其余设为极大值。
### 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+5;
int f(int x,int y){return (x/y+(x%y!=0))*y-x;}//将 x 变为 y 的倍数的最小操作次数
int lcm(int x,int y){return x*y/__gcd(x,y);}
int n,x,y,z,a[N],dp[N][10];
signed main(){
	cin>>n>>x>>y>>z;
	for(int i=1;i<=n;i++)cin>>a[i];
	memset(dp,0x3f,sizeof dp);
	dp[0][0]=0;
	for(int i=1;i<=n;i++)
		for(int j=0;j<=7;j++){
			if((j|0)==j)dp[i][j]=min(dp[i][j],dp[i-1][j^0]);
			if((j|1)==j)dp[i][j]=min(dp[i][j],dp[i-1][j^1]+f(a[i],x));
			if((j|2)==j)dp[i][j]=min(dp[i][j],dp[i-1][j^2]+f(a[i],y));
			if((j|3)==j)dp[i][j]=min(dp[i][j],dp[i-1][j^3]+f(a[i],lcm(x,y)));
			if((j|4)==j)dp[i][j]=min(dp[i][j],dp[i-1][j^4]+f(a[i],z));
			if((j|5)==j)dp[i][j]=min(dp[i][j],dp[i-1][j^5]+f(a[i],lcm(x,z)));
			if((j|6)==j)dp[i][j]=min(dp[i][j],dp[i-1][j^6]+f(a[i],lcm(y,z)));
			if((j|7)==j)dp[i][j]=min(dp[i][j],dp[i-1][j^7]+f(a[i],lcm(lcm(x,y),z)));
		}
	cout<<dp[n][7];
	return 0;
}
```

---

## 作者：lihongqian__int128 (赞：1)

考虑一个美妙的状压 DP。

定义 $dp_{i,S}$ 表示到第 $i$ 个数，状态为 $S$ 的最小操作次数。其中，$S$ 二进制下的最低位表示有没有 $a$ 的倍数，次低位表示有没有 $b$ 的倍数，最高位表示有没有 $c$ 的倍数。

转移：$dp_{i,S}\gets\min(dp_{i-1,S},\min\limits_{T\subseteq S}(dp_{i-1,S-T}+to(a_i,lcm_T)))$。其中，$lcm_T$ 表示状态为 $T$ 的数的最小公倍数，$to(a,b)$ 表示将 $a$ 变为 $b$ 的倍数的最小操作次数。

答案：$dp_{n,7}$。

初始：$dp_{i,S}=\begin{cases}0,S=0\\\inf,S\neq0\end{cases}$

讲得不太清楚，具体见代码实现。

代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int n,a[N],b[3],lm[8],dp[N][8];
int lcm(int x,int y){if(!x)return y;if(!y)return x;return x/__gcd(x,y)*y;}
int to(int x,int y){return (x%y==0?0:y-x%y);}
signed main(){
	memset(dp,0x3f,sizeof dp);
	dp[0][0]=0;
	cin>>n;
	for(int i=0;i<3;i++)cin>>b[i];
	for(int i=1;i<8;i++)
		for(int j=0;j<3;j++)
			if((i>>j)&1){
				lm[i]=lcm(b[j],lm[i^(1<<j)]);
				break;
			}
	for(int i=1;i<=n;i++){
		cin>>a[i];
		for(int j=0;j<8;j++){
			dp[i][j]=dp[i-1][j];
			for(int k=1;k<8;k++)
				if((j&k)==k)
					dp[i][j]=min(dp[i][j],dp[i-1][j^k]+to(a[i],lm[k]));
		}
	}
	cout<<dp[n][7];
	return 0;
}
```

---

## 作者：small_john (赞：1)

## 前言

蒟蒻第一篇 ARC 的题解捏。

## 思路

首先考虑一种贪心的思想，选对于第一个数的最优解，再选第二个数、第三个数，并且保证三个位置不相同。

那么，影响这种贪心的结果的因素就只有选数的顺序，那么就直接枚举呗。

再考虑在一个位置上满足两个条件，另一个条件单独选一个位置。一样的，枚举顺序，贪心求解。

最后，在一个位置上同时满足三个条件。对这三种方案去最小的答案，输出就行了。

怎么实现？直接 DFS！

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long 
#define lcm _____
using namespace std;

template<typename T> inline void read(T &x)
{
	x = 0;
	T f = 1;char ch = getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
		{
			f = -1,ch = getchar();
			break;
		}
		ch = getchar();
	}
	while(ch>='0'&&ch<='9')
		x = (x<<3)+(x<<1)+ch-48,ch = getchar();
	x*=f;
}
template<typename T> inline T read()
{
	T x;read(x);return x;
}
template<typename T> inline void write(T x)
{
    if(x<0) x = -x,putchar('-');
    if(x<=9) return putchar(x+48),void();
    write(x/10);
    putchar(x%10+48);
}
template<typename T> inline void writen(T x)
{
    write(x);
    puts("");
}
const int N = 2e5+5;
int n,a[N],ans = 8e18,sum,g[4],w[4],cnt,wz[4];
bool vis[4],v[N];
int lcm(int x,int y)//最小公倍数
{
	return x/__gcd(x,y)*y;
}
int get(int x,int y)//求需要操作的次数
{
	return (a[x]+y-1)/y*y-a[x];
}
int f()
{
	if(cnt>n) return 8e18;
	memset(v,0,sizeof v);
	for(int i = 1;i<=cnt;i++)
	{
		wz[i] = 1;
		while(v[wz[i]]) wz[i]++;
		for(int j = wz[i]+1;j<=n;j++)
		{
			if(v[j]) continue;//不能重复
			if(get(j,g[i])<get(wz[i],g[i])) wz[i] = j;
		}
		v[wz[i]] = 1;
	}
	int res = 0;
	for(int i = 1;i<=cnt;i++)
		res+=get(wz[i],g[i]);
	return res;
}
void dfs(int x)
{
	if(x>3) return ans = min(ans,f()),void();
	for(int i = 1;i<=3;i++)
	{
		if(vis[i]) continue;
		int tmp = g[cnt];
		vis[i] = 1;
		if(cnt) g[cnt] = lcm(g[cnt],w[i]),dfs(x+1),g[cnt] = tmp;//两个数合并为一个数
		g[++cnt] = w[i],dfs(x+1),g[cnt--] = 0;//单独一个数
		vis[i] = 0;
	}
}
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(n),read(w[1]),read(w[2]),read(w[3]);
	for(int i = 1;i<=n;i++)
		read(a[i]);
	dfs(1);
	write(ans);
	return 0;
}
```

## 后记

首先，上述算法可以继续优化，因为有重复求解的情况，其次，用状压写会更简洁。

---

## 作者：sunkuangzheng (赞：1)

$\textbf{1.1 Describtion}$

序列 $a$ 和整数 $x,y,z$，每次操作选择位置 $i$，令 $a_i \gets a_i + 1$，问最少多少次操作，使得序列 $a$ 里既有 $x$ 的倍数又有 $y$ 的倍数又有 $z$ 的倍数。

$\textbf{1.2 Solution}$

暴力状压 dp，感觉比大力分讨好写（

设 $f_{i,j}$ 表示到位置 $i$，$x,y,z$ 倍数有无的状态是 $j$ 的最小操作数，其中 $0 \le j \le 7$，$j$ 是二进制串。那么我们枚举 $j$ 和其前驱状态 $k$，暴力转移即可。时间复杂度 $\mathcal O(nk^2)$，其中 $k = 2^3=8$。

$\textbf{1.3 Code}$

比大力分讨好写太多啦 /se

```cpp
/**
 *    author: sunkuangzheng
 *    created: 08.10.2023 21:22:01
**/
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,n,b[5],a[200005],c[200005],res = 1e18,f[200005][8];
int lcm(int a,int b){return a / __gcd(a,b) * b;}
signed main(){
    ios::sync_with_stdio(0),cin.tie(0);
    cin >> n >> b[1] >> b[2] >> b[3];
    for(int i = 1;i <= n;i ++) cin >> a[i];
    for(int i = 0;i <= n;i ++) for(int j = 1;j <= 7;j ++) f[i][j] = 9e18;
    f[0][0] = 0;
    for(int i = 1;i <= n;i ++){
        f[i][0] = 0;
        for(int j = 1;j <= 7;j ++){
            for(int k = 0;k <= 7;k ++){
                if((k | j) != j) continue;int tp = 1;
                for(int l = 2;l >= 0;l --) if(((j >> l) & 1) && !((k >> l) & 1)) tp = lcm(tp,b[l+1]);
                f[i][j] = min(f[i][j],f[i-1][k] + (tp - a[i] % tp) % tp);
            }
        }
    }cout << f[n][7];
}
```

---

## 作者：forever_nope (赞：0)

宣传：<https://www.cnblogs.com/RainPPR/articles/solution-at-arc166-b.html>

第一次题解不过呜呜，希望这次没事。

我的思路与其他题解的思路大体一致，我这里主要是详细的说明更多一些。

### 简要题意

给定一个整数序列 $A=(A_1,\ldots,A_N)$ 和正整数 $a$、$b$ 和 $c$。

您可以对该序列执行以下操作任意次数，可能为零。

- 选择一个整数 $i$ $(1\leq i\leq N)$，并将 $A_i$ 替换为 $A_i+1$。

您的目标是使序列 $A$ 包含「至少一个 $a$ 的倍数」、「至少一个 $b$ 的倍数」以及「至少一个 $c$ 的倍数」。找出实现此目标所需的最少操作数。

- $1\leq N\leq 2\times 10^5$
- $1\leq a, b, c \leq 10^6$
- $1\leq A_i\leq 10^{18}$

### 状压 DP

我的思路其实比较的朴素，但是也能过。

将任意 $x$ 变为 $y$ 的倍数的最小操作次数记为 $to(x,y)$，简单的，可以这么计算：因为 $x$ 只能递增，所以 $x$ 一定是变为 $\ge x$ 的第一个 $y$ 的倍数，也就是 $\lceil\frac{x}{y}\rceil\times y=\lfloor\frac{x+y-1}{y}\rfloor\times y$，于是，最小操作次数 $to(x,y)=\lfloor\frac{x+y-1}{y}\rfloor\times y-x$。~~看着大佬们的「卡常」算法，感觉被碾压了诶。~~

状态设计与其他大佬类似，设 $f(i,S)$ 为：使 $A$ 的前 $i$ 个数满足条件集合 $S$ 的最小操作次数。

#### 二进制状压

- 满足 $0$ 个条件：
	- $S=0$ 表示不需满足任何条件；
- 满足 $1$ 个条件：
	- $S=1$ 表示需要满足条件 $1$（$a$ 的倍数）；
	- $S=2$ 表示需要满足条件 $2$（$b$ 的倍数）；
	- $S=4$ 表示需要满足条件 $3$（$c$ 的倍数）；
- 满足 $2$ 个条件：
	- $S=3$ 表示需要同时满足条件 $1,2$；
	- $S=5$ 表示需要同时满足条件 $1,3$；
	- $S=6$ 表示需要同时满足条件 $2,3$；
- 满足 $3$ 个条件：
	- $s=7$ 表示需要同时满足条件 $1,2,3$。

#### 易知

- 初始化：

	$f(0,0)=0$，$\forall i\neq0,f(0,i)=\inf$.

- 满足 $0$ 个条件：

	$f(i,0)=f(i-1,0)$；

- 满足 $1$ 个条件：

	$f(i,1)=\min\{f(i-1,1),f(i-1,0)+to(A_i,a)\}$.

	$f(i,2)=\min\{f(i-1,2),f(i-1,0)+to(A_i,b)\}$.

	$f(i,4)=\min\{f(i-1,4),f(i-1,0)+to(A_i,c)\}$.

- 满足 $2$ 个条件：

	$f(i,3)=\min\left\{\begin{array}{l}f(i-1,3),\\f(i-1,1)+to(A_i,b),\\f(i-1,2)+to(A_i,a),\\f(i-1,0)+to(A_i,\operatorname{lcm}(a,b))\end{array}\right\}$.

	$f(i,5)=\min\left\{\begin{array}{l}f(i-1,5),\\f(i-1,1)+to(A_i,c),\\f(i-1,4)+to(A_i,a),\\f(i-1,0)+to(A_i,\operatorname{lcm}(a,c))\end{array}\right\}$.

	$f(i,6)=\min\left\{\begin{array}{l}f(i-1,6),\\f(i-1,2)+to(A_i,c),\\f(i-1,4)+to(A_i,b),\\f(i-1,0)+to(A_i,\operatorname{lcm}(b,c))\end{array}\right\}$.

- 满足 $3$ 个条件：

	$f(i,7)=\min\left\{\begin{array}{l}f(i-1,7),\\f(i-1,3)+to(A_i,c),\\f(i-1,5)+to(A_i,b),\\f(i-1,6)+to(A_i,a),\\f(i-1,1)+to(A_i,\operatorname{lcm}(b,c)),\\f(i-1,2)+to(A_i,\operatorname{lcm}(a,c)),\\f(i-1,4)+to(A_i,\operatorname{lcm}(a,b)),\\f(i-1,0)+to(A_i,\operatorname{lcm}(a,b,c))\end{array}\right\}$.

- 于是，答案为 $f(n,7)$。

## 代码

见：<https://atcoder.jp/contests/arc166/submissions/46876171>

特别要注意的，别抄错数（比如我就卡了 30min 在这里）、、、


---

## 作者：PCCP (赞：0)

## 思路

首先可以很容易想到一种比较暴力的做法，即分别计算满足三个数七种方案的最小操作次数，再取最小值，但是这样非常的麻烦，因为还要保证不重，甚至要建三个优先队列枚举先满足哪个数，就很喽很哈皮很庸俗。

考虑优化，明显可以非常套路地状态压缩，$ f_i $ 表示满足第 $ i $ 种状态的最小操作数，状态的某一位为 $ 1 $ 就表示满足是这一位代表的数的倍数，最后跑一遍取最小值即可。同理，也可以这样先预处理出最小公倍数出来。

我认为甚至可以给定不止三个数。

设要满足 $ m $ 个数。

时间复杂度：$ O(2^{2m}n) $。

## 代码

采用最快的计算最大公约数的方法，十分甚至九分的遥遥领先。

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#include<cmath>
#include<queue>
#include<stack>
#include<set>
using namespace std;
const int N=2e5+10;
int n;
long long p[N],v[N],lc[N],ans[N],f[N],res;
long long gcd(long long x,long long y){
	long long az=__builtin_ctz(x),bz=__builtin_ctz(y);
	long long z=az>bz?bz:az,cha;
	y>>=bz;
	while(x){
		x>>=az;
		cha=y-x;
		az=__builtin_ctz(cha);
		if(x<y){
			y=x;
		}
		x=cha<0?-cha:cha;
	}
	return y<<z;
}
long long lcm(long long x,long long y){
	return (long long)x*y/gcd(x,y);
}
int main(){
	scanf("%d%lld%lld%lld",&n,&p[0],&p[1],&p[2]);
	for(int i=0;i<8;i++){
		lc[i]=1;
		ans[i]=1e18;
		for(int j=0;j<3;j++){
			if(i&(1<<j)){
				lc[i]=lcm(lc[i],p[j]);
			}
		}
	}
	ans[0]=0;
	for(int i=1;i<=n;i++){
		scanf("%lld",&v[i]);
		for(int j=0;j<8;j++){
			f[j]=ans[j];
		}
		for(int j=0;j<8;j++){
			long long rest=(lc[j]-(v[i]%lc[j]))%lc[j];
			for(int k=0;k<8;k++){
				f[j|k]=min(f[j|k],ans[k]+rest);
			}
		}
		for(int j=0;j<8;j++){
			ans[j]=f[j];
		}
	}
	printf("%lld\n",ans[7]);
}
```


---

