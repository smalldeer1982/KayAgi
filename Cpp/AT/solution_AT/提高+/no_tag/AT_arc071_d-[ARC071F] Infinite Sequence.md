# [ARC071F] Infinite Sequence

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc071/tasks/arc071_d

{$ {1,\ ...\ ,n} $} からなる無限長の列 $ a_1,\ a_2,\ ... $ のうち、 次の条件を満たしているものは何通りあるでしょうか？

- 第 $ n $ 項から先はすべて同じ数である。つまり、$ n\ \leq\ i,j $ ならば $ a_i\ =\ a_j $ を満たす。
- どの正の整数 $ i $ に対しても、第 $ i $ 項の直後に並ぶ $ a_i $ 個の項はすべて同じ数である。つまり、 $ i\ <\ j\ <\ k\leq\ i+a_i $ ならば $ a_j\ =\ a_k $ を満たす。

答えを $ 10^9+7 $ で割ったあまりを求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ n\ \leq\ 10^6 $
- $ n $ は整数

### Sample Explanation 1

以下の $ 4 $ 通りがあります。 - $ 1,\ 1,\ 1,\ ... $ - $ 1,\ 2,\ 2,\ ... $ - $ 2,\ 1,\ 1,\ ... $ - $ 2,\ 2,\ 2,\ ... $

## 样例 #1

### 输入

```
2```

### 输出

```
4```

## 样例 #2

### 输入

```
654321```

### 输出

```
968545283```

# 题解

## 作者：ezoixx130 (赞：13)

## 题意

让你构造一个每个数为1~n的无限长的序列，满足：

1. 第n个数与它后面的数都相同

2. 对于每一个数x，它和后面的x个数都相同。

问你有多少种方案。

## 题解

考虑dp，设$f[i]$代表第i~n位都填好的方案数，倒着dp。

转移分3种情况：

当第i位是1时，$f[i]+=f[i+1]$。

当第i位不是1并且第i+1位也不是1时，这个序列就只能长成$xyyyyyyyyyyyy...$的样子了，其中$x$和$y$可以填任意非1数，所以$f[i]+=(n-1)*(n-1)$.

当第i位不是1但是第i+1位是1时，这个序列就长成$x11111S$的样子了，所以对于每一个$x$，$f[i]+=f[i+x+1]$（如果$i+x+1>n$那么$f[i+x+1]=1$），维护一个$f$的后缀和就可以做到$O(1)$转移了。

时间复杂度：$O(n)$。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

#define MAXN 1000010
#define mod 1000000007

int n,f[MAXN],add;

int main()
{
    scanf("%d",&n);
    f[n]=n;
    f[n-1]=(long long)n*n%mod;
    for(int i=n-2;i>=1;--i)
    {
        add=(add+f[i+3])%mod;
        f[i]=f[i+1];
        f[i]=(f[i]+(long long)(n-1)*(n-1)%mod)%mod;
        f[i]=(f[i]+add)%mod;
        f[i]=(f[i]+i+1)%mod;
    }
    printf("%d\n",f[1]);
}
```

---

## 作者：Hadtsti (赞：3)

~~RMJ 已经炸了好久了，什么时候能修好啊……~~
### 题意简述
定义“好”的序列 $\{a_i\}$ 为满足以下两个性质的无穷序列：

- 所有项都是 $[1,n]$ 中的正整数。
- 第 $n$ 项及之后的所有项都相等。
- 对每一个 $a_i$，满足 $a_{i+1}\sim a_{i+a_i}$ 两两之间都相等。

给出 $n$，求“好”的序列的数量。

### 题目分析

与其他题解差不多，仍是采用 DP。设 $f_i$ 表示第 $i\sim n$ 都填好的方案数。那么由于第 $n$ 位及之后的项可以随便填，故 $f_n=n$；同样的道理，第 $n-1$ 项也可以随便填，故 $f_{n-1}=n^2$。

然后考虑状态转移，分三种情况：

1. $a_i=1$：方案数直接为 $f_{i+1}$。

2. $a_i>1,a_{i+1}=1$：那么 $a_{i+1}\sim a_{i+a_i}$ 都确定为 $1$，方案数为 $\displaystyle\sum_{a_i=2}^n f_{i+a_i+1}$。特别地，对 $k>n$，我们令 $f_k=1$，所以原式实质上等于 $\displaystyle i+1+\sum^n_{j=i+3} f_j$。

3. $a_i,a_{i+1}>1$：则 $a_{i+1}$ 及之后的所有项都必须相同。而 $a_i$ 和 $a_{i+1}$ 可以随便填。方案数为 $(n-1)^2$。

综上，$\displaystyle f_i=i+1+(n-1)^2+f_{i+1}+\sum^n_{j=i+3} f_j$。直接用前缀和维护 $\displaystyle \sum^n_{j=i+3} f_j$ 进行计算可以做到 $O(n)$。

考虑更优的做法。我们发现计算这个递推式其实可以很方便地用矩阵优化。初步设计答案矩阵为 $\begin{bmatrix}
f_{i+1}  & f_{i+2} & f_{i+3} & i+1 & (n-1)^2 & \displaystyle\sum_{j=i+4}^nf_j & -1
\end{bmatrix}$

为了将其递推到 $\begin{bmatrix}
f_i & f_{i+1}  & f_{i+2}  & i & (n-1)^2 & \displaystyle\sum_{j=i+3}^nf_j & -1
\end{bmatrix}$，设计转移矩阵：

$$\begin{bmatrix}
1&1&0&0&0&0&0\\
0&0&1&0&0&0&0\\
1&0&0&0&0&1&0\\
1&0&0&1&0&0&0\\
1&0&0&0&1&0&0\\
1&0&0&0&0&1&0\\
0&0&0&1&0&0&1
\end{bmatrix}$$

我们一列一列进行解释：

第 $1$ 列，由状态转移方程得来。

第 $2$、$3$ 列，简单的滚动更新。

第 $4$ 列，$i+1+(-1)=i$。第 $5$、$7$ 列保持不变。

第 $6$ 列，$\displaystyle f_{i+3}+\sum_{j=i+4}^nf_j=\sum_{j=i+3}^nf_j$。

这样用矩阵快速幂做确实是可行的，但我们会发现 $7\times 7$ 的矩阵做矩阵乘法一方面会使常数变得很大，另一方面矩阵中的一些项其实是没有必要的。

考虑优化。首先，$\displaystyle f_{i+1}+\sum_{j=i+3}^nf_j$ 其实就等于 $(\displaystyle\sum_{j=i+1}^nf_j)-f_{i+2}$，根本没必要维护 $f_{i+3}$；同时，$(n-1)^2$ 和 $i+1$ 其实可以合并进前缀和里。这样我们就得到了简化后的 $1\times 4$ 的答案矩阵：$\begin{bmatrix}
f_{i+1}  & f_{i+2} & i+1+(n-1)^2+\displaystyle\sum_{j=i+2}^nf_j & -1
\end{bmatrix}$

相应地改变转移矩阵：

$$\begin{bmatrix}
1&1&1&0\\
-1&0&0&0\\
1&0&1&0\\
0&0&1&1
\end{bmatrix}$$

这样程序的常数就会小不少，总时间复杂度为 $O(\log n)$，对本题绰绰有余。

### 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1000000007;
int n;
struct matrix
{
	int n,m;
	int a[5][5];
	void init(int k)
	{
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				if(i!=j)
					a[i][j]=0;
				else
					a[i][j]=k;
	}
	friend matrix operator *(matrix a,matrix b)//矩阵乘法 
	{
		matrix c;
		c.n=a.n,c.m=a.m;
		c.init(0);
		for(int i=1;i<=a.n;i++)
			for(int j=1;j<=b.m;j++)
				for(int k=1;k<=a.m;k++)
					c.a[i][j]=(c.a[i][j]+1ll*a.a[i][k]*b.a[k][j]%mod)%mod;
		return c;
	}
	friend matrix operator ^(matrix a,int b)//矩阵快速幂 
	{
		matrix res;
		res.n=res.m=a.n;
		res.init(1);
		for(;b;b>>=1)
		{
			if(b&1)
				res=res*a;
			a=a*a;
		}
		return res;
	}
}fs,tr;
int main()
{
	scanf("%d",&n);
	if(n==1)
	{
		printf("1");
		return 0;
	}//特判 1 
	fs.n=1,fs.m=tr.n=tr.m=4;
	fs.a[1][1]=1ll*n*n%mod,fs.a[1][2]=n,fs.a[1][3]=1ll*n*n%mod,fs.a[1][4]=mod-1;//初始答案矩阵，注意 -1 是 mod-1 
	tr.init(0);
	tr.a[1][1]=tr.a[1][2]=tr.a[1][3]=tr.a[3][1]=tr.a[3][3]=tr.a[4][3]=tr.a[4][4]=1,tr.a[2][1]=mod-1;//转移矩阵 
	tr=tr^(n-2);//计算转移矩阵的幂 
	fs=fs*tr;//得到最终答案矩阵 
	printf("%d",fs.a[1][1]);
	return 0;
}
```


---

## 作者：star_magic_young (赞：3)

[打波广告](https://www.cnblogs.com/smyjr/p/10473831.html)

仔细观察可以发现,如果在一个$> 1$的数后面放一个$> 1$的数,那么后面的序列也就确定了,所以我们考虑dp出特定长度的序列,然后在后面加上能确定序列的数来贡献答案

为了凑出这样的序列,用来填充的东西是单个的$1$,或者长度为$x+1(x>1)$的 $x$加$x$个$1$,所以转移就是$f_i=\sum_{j=0}^{i-1}[j\ne i-2]f_j$,注意不能加上$f_{i-2}$,因为$1\ 1$会和$1$加$1$算重

然后考虑$f_i$的贡献,如果$i<n-1$,首先可以加上$xyyyy...(x>1,y>1)$,然后也可以加上$x11111(x>1$且$i+x+1\ge n)$,因为凑到n时后面就全是$1$了;如果$i=n-1$,那么n号位放什么,后面就是什么,所以可以放一个$[1,n]$的数

渣渣~~灰~~代码警告

```cpp
#include<bits/stdc++.h>
#define LL long long
#define db double
#define il inline
#define re register
#define mkpr make_pair

using namespace std;
const int N=1e6+10,mod=1e9+7;
il LL rd()
{
    LL x=0,w=1;char ch=0;
    while(ch<'0'||ch>'9') {if(ch=='-') w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') {x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
    return x*w;
}
int n,m,f[N],ans;

int main()
{
    n=rd();
    m=(1ll*(n-1)*(n-1))%mod;
    ans=m+1+(n>2);  //整个序列可以是xyyyy,也可以是n11111或者(n-1)11111
    int sm=f[0]=1;
    for(int i=1;i<n;++i)
    {
        f[i]=sm;
        if(i-2>=0) f[i]=(f[i]-f[i-2]+mod)%mod;
        sm=(sm+f[i])%mod;
        if(i!=n-1) ans=(ans+1ll*f[i]*(m+min(i+2,n-1))%mod)%mod; //乘的东西代表的分别是xyyyy和x1111
        else ans=(ans+1ll*f[i]*n%mod)%mod;
    }
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：Krimson (赞：3)

一眼看上去可以很轻松地发现如果$a_i>1,a_{i+1}>1$,那么就会陷入套娃状态,比如3 222222222222...    
于是分类讨论  
1.$a_i$=1,那么$a_{i}$对后面不会造成影响  
2.$a_i>1,j\in[i+1,i+a_i] a_{j}=1$ 那么只有长为$a_i$的部分受到了影响  
3.$a_i>1,a_{i+1}>1$,此时只有一种情况  

那么设$f[i]$表示对于每一位$a\in[1,n]$有多少种方案,若$i<=0$则$f[i]=1$  
可以得到 
$$f[i]=f[i-1]+(n-1+f[i-3])+(n-1+f[i-4])...+(n-1+f[i-n-1])$$    
加上前缀和优化一下之后的柿子就成了  
$$
f[i]=f[i-1]+(n-1)(n-1)+sum[i-3]+(n-i+1)
$$  
其中$f[1]=n,f[2]=n^2$，需要提前处理一下  
然后套这个柿子就可以$O(n)$求出答案了  
以下是代码  
```cpp
#include<bits/stdc++.h>
using namespace std;
#define il inline
#define ri register int
#define ll long long
il ll read(){
    bool f=true;ll x=0;
    register char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') f=false;ch=getchar();}
    while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    if(f) return x;
    return ~(--x);
}
il void write(const ll &x){if(x>9) write(x/10);putchar(x%10+'0');}
il void print(const ll &x) {x<0?putchar('-'),write(~(x-1)):write(x);putchar('\n');}
il int max(const int &a,const int &b){return a>b?a:b;}
il int min(const int &a,const int &b){return a<b?a:b;}
const int MAXN=1e6+7;
ll f[MAXN],sum[MAXN];
ll n;
const ll mod=1e9+7;
int main(){
    n=read();
    f[1]=n;
    f[0]=1;
    sum[0]=1;
    sum[1]=n+1;
    f[2]=n*n;
    sum[2]=n*n+n+1;
    for(ri i=3;i<=n;++i){
        f[i]=(f[i-1]+(n-1)*(n-1))%mod;
        f[i]=(f[i]+sum[i-3]+(n-i+1))%mod;
        sum[i]=(sum[i-1]+f[i])%mod;
    }
    print(f[n]);
    return 0;
}
```


---

## 作者：Star_F (赞：2)

写于梦熊模拟赛后。
## 题目大意：
构造一个无限长的序列，每个数在 $1$ ~ $n$ 内，满足每个数 $a$ 后面的 $a$ 个数都相等。

## 题目思路：
首先考虑 $dp$,设 $dp_i$ 表示 $i$ ~ $n$ 已经填完的方案数。

假设我们构造的序列为 $a$ 。

- 如果 $a_i >1$ 并且 $a_{i+1}>1$ ，那么序列只有一种情况就是 $a_1,a_2,\dots,a_i,a_{i+1},a_{i+1},a_{i+1}\dots$

  所以 $dp_i=(dp_i+ (n-i) \times (n-i)) \bmod 1000000007$

- 如果 $a_i=1$ ，那么 $i$ 以后的数任意填。

  所以 $dp_i=(dp_i+dp_{i+1}) \bmod 1000000007$

- 如果 $a_i>1$ 并且 $a_{i+1}=1$

  那么序列就是 $a_1,a_2,\dots,a_i,1,a_{i+2},a_{i+3}$

  所以 $dp_i=(dp_i+dp_{i+x+1}) \bmod 1000000007$

如果这样做第三种情况转移会超时，考虑维护一个 $dp$ 数组的后缀和即可。

## 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define ROF(i, a, b) for (int i = (a); i >= (b); --i)
#define DEBUG(x) cerr << #x << '=' << x << endl

inline int rd()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
        x = x * 10 + ch - '0', ch = getchar();
    return x * f;
}

void print(int x)
{
    if (x < 0)
        putchar('-'), x = -x;
    if (x > 9)
        print(x / 10);
    putchar(x % 10 + '0');
    return;
}

namespace Star_F
{
    const int mod = 1e9 + 7;
    long long dp[1000005];
    void Main(){
        int n;
        cin >> n;
        dp[n] = n;          //第n位任选
        dp[n - 1] = n * n;  //第n-1位和第n位任选
        int sum = 0;      //dp数组后缀和
        for (int i = n - 2; i >= 1; i--)
        {
            sum += dp[i + 3] % mod;
            dp[i] = dp[i + 1] % mod; 
            dp[i] %= mod;
            dp[i] += (n - 1) * (n - 1); 
            dp[i] %= mod;
        
            dp[i] +=sum % mod; 
            dp[i] %= mod;
            dp[i] += i + 1; 
            dp[i] %= mod;
        }
        cout << dp[1] % mod;     //输出
    }
}

signed main()
{
    //freopen(".in", "r", stdin);
    //freopen(".out", "w", stdout);
    return Star_F::Main(), 0;
    return 0;
}

/*
2

4
1 11111111....
1 22222222....
2 11111111....
2 22222222....

*/
```

---

## 作者：lkjzyd20 (赞：1)

### 题意

让你构造一个每个数为 $1 \sim n$ 的正整数无限长的序列，满足：

- 第 $n$ 项及之后的所有项都相等

- 对于每一个 $a_i$，满足 $a_{i+1} \sim a_{i+a_i}$ 个数都相同。

问你有多少种方案 $\bmod\ 10^9+7$。

### 思路

看到问方案，首先想到 `dp`。

那么设 $f_i$ 表示对于每一位 $a\in[1,n]$ 有多少种方案，则可以得到

$$ f_i=f_{i-1}+(n-1+f_{i-3})+(n-1+f{i-4}) \cdots +(n-1+f_{i-n-1})$$

加上前缀和优化一下之后的式子就变成了

$$f_i=f_i-1+sum_{i-3}+n^2-n-i+2$$

其中 $f_1=n,f_2=n^2$，$sum$ 数组用来求 $f$ 数组的前缀和，需要预处理一下，注意 $\bmod 10^9+7$。

综上所述，时间负责度为 $O(n)$。

### 代码如下

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
#define rep(i, l, r) for(int i = l; i <= r; ++ i)
#define per(i, r, l) for(int i = r; i >= l; -- i)
const int N = 1e6 + 10, mod = 1e9 + 7;
int f[N], sum[N], n;
main() 
{
	scanf("%lld", &n);
	f[0] = 1; f[1] = n; f[2] = (n * n) % mod;
	sum[0] = 1;
	sum[1] = (f[0] + f[1]) % mod;
	sum[2] = ((f[0] + f[1]) % mod + f[2]) %mod;
	rep(i, 3, n) 
	{
		f[i] = ((f[i - 1] + sum[i - 3]) % mod + n * (n - 1) - i + 2) % mod;
		sum[i] = (sum[i - 1] + f[i]) % mod;
	}
	printf("%lld", f[n] % mod);
	return 0;
}
```

---

## 作者：ziyistudy (赞：1)

显然是 dp，但不太好想状态怎么设，不妨先暴力记忆化搜索一下。

得到状态 $dp_{i,j}$ 表示考虑到第 $i$ 位，第 $i$ 到 $i+j-1$ 位的数都相同。对于 $dp_{i,1}$，表示这个位置之后的数没有限制，可以推到 $dp_{i+1,j}$（$1\leq j\leq n$）；对于 $dp_{i,j}$（$1<j\leq n$），如果后面一位不填 $1$ 的话，则之后的数会互相牵制，导致之后的数都一样（可以手推一下，比如这一位是 $2$，若下一位填 $3$，则之后的数都必须为 $3$），这样会有 $n-1$ 种情况；若这一位填 $1$，则必须要连续填 $j$ 个 $1$，直接推到 $dp_{i+j,1}$。注意边界条件，当 $i=n$ 时，这一位可以任意填；当 $i>n$ 时，前面已经有 $j\ge n$，这时 $i$ 的数值已经确定。

暴力记忆化搜索代码（~~别问为什么写暴力，问就是模拟赛有部分分~~），$O(N^2)$：
```cpp
int dfs(int dir,int lim)
{
	if(dp[dir][lim]) return dp[dir][lim];
	if(dir>=n) {
		if(dir>n) return dp[dir][lim]=1;
		else return dp[dir][lim]=n;
	}
	int sum=0;
	if(lim>1){
		sum=n-1;
		(sum+=dfs(dir+lim,1))%=MOD;
	}
	else {
		for(int i=1;i<=n;i++){
			(sum+=dfs(dir+1,i))%=MOD;
		}
	}
	return dp[dir][lim]=sum;
}
signed main() 
{
	cin>>n;
	cout<<dfs(1,1)<<endl;
}
```

这个时候我们再把 dp 转移式写出来：

$$dp_{i,1}=\textstyle \sum \limits_{j=1}^{n}{dp_{i+1,j}}$$

$$dp_{i,j(1<j\leq n)}=n-1+dp_{i+j,1}$$

这时我们发现可以用前缀和来优化转移操作，从而实现 $O(1)$ 转移。

具体地，设 $sum_i=\textstyle \sum \limits_{j=i}^{2n}{dp_{j,1}}$。

这样的话 $\textstyle \sum \limits_{j=2}^{n}{dp_{i,j}} = (n-1)^2+sum_{i+2}-sum_{i+n+1}$。$dp_{i,1}$ 直接从上一个和转移即可。

正解代码（~~极限想出~~），$O(N)$：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
#define eb emplace_back
//#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
typedef vector<int> VI;
typedef long long ll;
typedef pair<int,int> PII;
const ll MOD=1e9+7;
// head
const int N=1e7+5;
int n;
int dp[N][3];
int sum[N];
signed main() 
{
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
  
	cin>>n;
	dp[n][1]=n,dp[n][2]=n*(n-1);
	for(int i=n+1;i<n+n;i++) sum[i]=1;
	for(int i=n+n-1;i>=n+1;i--) sum[i]=sum[i+1]+sum[i];
	for(int i=n-1;i>=1;i--){
		dp[i][1]=(dp[i+1][2]+dp[i+1][1])%MOD;
		dp[i][2]=(sum[i+2]-sum[i+n+1]+MOD+(n-1)*(n-1)%MOD)%MOD;
		sum[i+1]=(sum[i+2]+dp[i+1][1])%MOD;
	}
	cout<<dp[1][1]<<endl;
}
```

---

## 作者：Acerkaio (赞：1)

# [ARC071F] Infinite Sequence 题解
## 题面
要求构造一个由自然数组成的无限长的序列 $s$，满足：

序列中每个数字 $s_i \in \left [ 1, n \right ] $ ，第 $n$ 位及以后的数字都是相同的，序列 $s$ 中，对于每一个 $s_j$，$\forall s_k$ 是相同的，其中 $ k \in \left [ j + 1, j + s_j  \right ]$。

求构造出互不相同的序列的数量。

## 思路

求数量题目，考虑动态规划。

### 定义：

$dp_i$ 表示填第 $i$ 到第 $n$ 位的方案数。（倒顺枚举，其方便之处在转移中体现）

### 转移：

发现可以分成三种情况来讨论：

若我们填写 $s_i$ 为 $1$，则此时总方案数 $dp_i = dp_i + 1$，即不需要特别注意条件。

若我们填写 $s_i$ 为一个大于 $1$ 的数字，又会发生两种情况：

1. $s_{i+ 1}$ 大于 $1$，手模递归发现此时 $s_{i + 1}$ 到 $s_{\infty }$ 是相同的，故此时我们填写 $s_i$ 可取值 $s_i \in [2, n]$，$s_{i + 1} \in [2, n]$，方案总数 $dp_i = (n-1)^2$。

2. $s_{i+ 1}$ 等于 $1$，则 $\forall s_j = 1 (j \in [i, i+s_i])$，但是仍要考虑 $i + s_i + 1$ 不为及以后位上的数字未被填写，仍需考虑方案数，我们枚举 $s_i$，其方案总数即为 $\sum_{l = 2}^{n} f_{i + l +1} $。维护后缀和方便得到。特别地，我们注意到 $i + l + 1 > n$ 时， $f_{i + l + 1}$ 理应等于 1，故要考虑最后 $i + n + 1 - n$ 个方案贡献，即为 $i + 1$。

累加所有情况所得即可。


## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int _ = 1e6 + 7;
const int P = 1e9 + 7;
int dp[_];
signed main() {
	int n, temp = 0;
	cin >> n;
	dp[n] = n;
	dp[n - 1] = n * n % P;
	for (int i = n - 2; i >= 1; i--) {
		temp += dp[i + 3];
		temp %= P;
		dp[i] = (dp[i + 1] + ((n - 1) * (n - 1)) % P + temp + i + 1) % P;
	}
	cout << dp[1] << '\n';
	return 0;
}
```

---

## 作者：laoliu12345 (赞：0)

## AT_arc071_d
### 解法说明
#### 题目理解
首先 $n$ 以后的数都应与其相同，其次若 $i$ 为 $x$，则 $i+1$ 到 $i+x$ 都为 $x$。
#### 思路
令 $f_i$ 表示当前填到 $i$，其中 $i \sim n$ 的方案数。
若 $a_i$ 为  $1$  且 $a_{i+1}\neq1$ 或 $a_{i+1}=1$ 就有 $f_i $ 直接加 $ f_{i+1}$。若 $a_i\neq1$ 且  $a_{i+1}\neq1$，则 $f_i=(n-1) \times (n-1)$。若  $a_i\neq1$ 且 
 $a_{i+1}$ 为  $1$，则 $f_i= \sum f_{i+x+1}$。

 那就可以愉快的写代码了。
### 题目代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1000010,Mod=1e9+7;
int n;
int f[N];
signed main()
{
	cin>>n;
	f[n]=n;
	f[n-1]=n*n%Mod;
	int sum=0;
	for(int i=n-2;i>=1;i--)
	{
		sum+=f[i+3],sum%=Mod;
		f[i]+=f[i+1],f[i]%=Mod;
		f[i]=((n-1)*(n-1)%Mod+f[i])%Mod;
		f[i]+=sum;
		f[i]+=i+1;
		f[i]%=Mod;
	}
	cout<<f[1]<<endl;
	return 0;
}
```

---

## 作者：Mingjunyi (赞：0)

# [ARC071F] Infinite Sequence

这里提供一个不一样的解法。

我们不难发现，当序列相邻两个值 $x,y$ 都大于 $1$ 时,那么序列从 $x$ 开始会变成 $x,y,y,y,y,y,y,...$。

序列中出现的值大体可以分为 $3$ 类：
1. 非 $1$（即 $2 \sim n$）
2. 非强制 $1$（如 $2\ ,\ 1\ ,\ 1\ ,\ \dot 1$）
3. 强制 $1$（如 $2\ ,\ \dot 1\ ,\ \dot 1\ ,\ 1$）

那么，我们考虑序列第 $i$ 位的值，写出下列状态和转移：

$f_{i,0}$ 为（第 $i- 1$ 位 为 $1$）第 $i$ 位为 **非 $1$** 的方案数，

$f_{i,1}$ 为第 $i$ 位为 **非强制 $1$** 的方案数，

$f_{i,2}$ 为第 $i$ 位是 **强制 $1$ 的结尾**（如 $2\ ,\ 1\ ,\ \dot 1\ ,\ 1$）的方案数，

---

因为非 $1$ 下一位可以是 $2 \sim n$ 中的任意一个值，一旦两个位置确定，这个序列就已经确定了，可以直接加入答案
有转移：
$$
(n - 1) \times f_{i,0} \rightarrow ans 
$$ 

---

当 $i + 1$ 位为非 $1$ 时，第 $i$ 位只能是 $1$ （因为为非 $1$ 的答案已经加入进答案中了）,
并且非 $1$ 有 $(n - 1)$ 种选择（即 $2 \sim n$）
有转移：
$$
(n - 1) \times (f_{i,1} + f_{i,2}) \rightarrow f_{i + 1,0}
$$

---

当 $i + 1$ 位为非强制 $1$ 时，第 $i$ 位只能为强制 $1$ 的结尾或强制 $1$ 
故有转移：
$$
(f_{i,1} + f_{i,2}) \rightarrow f_{i,1}
$$

---

因为当 $i + 1$ 位为强制 $1$ 的结尾时，我们要找哪个位置的非 $1$ 导致了 $i + 1$ 位为强制 $1$ 的结尾，即我们要考虑 $f_{i + 1,2}$ 能从哪里转移过来

因为序列中的值 $\in \{1,2,...,n\}$ 

也就是说，从哪都可以转移！

那么关键就是转移多少？

仔细观察，可以发现，见下图：
![pic](https://cdn.luogu.com.cn/upload/image_hosting/davxcmmg.png)

只有当第 $j$ 位为 $1$ 时，才能在第 $j + 1$ 位能且仅能找到一个 $k$ 使得 $i + 1$ 为强制 $1$ 的结尾

因为强制 $1$ 的概念只有出现非 $1$ 才存在，所以 $j$ 到 $i + 1$ 至少相距 $4$，即 $j \leq i - 2$，如图：

![pic](https://cdn.luogu.com.cn/upload/image_hosting/ayl4ucz6.png)

那么有转移:
$$
\sum_{0\leq j \leq i - 2} (f_{j,1} + f_{j,2}) \rightarrow f_{i + 1,2}
$$
这里用一个 $cnt$ 记录一下 $f_{j,1} + f_{j,2}$ 的前缀和就可以在 dp 中 $O(1)$ 转移了

那么转移部分就结束了。

---

接下来为 **统计答案**

我们考虑最后一位的值：
1. 最后一位是（第 $n - 1$ 位为 $1$ 的）非 $1$，即
   $$ 
   f_{n,0} \rightarrow ans 
   $$
2. 最后一位是非强制 $1$，即
   $$
    f_{n,1} \rightarrow ans
   $$
3. 最后一位是强制 $1$ 的结尾，即
   $$
    f_{n,2} \rightarrow ans
   $$
4. 最后一位是强制 $1$（非结尾），由于每一个（不为第 $n$ 位的）位置都有（$n - (n - pos) = pos$）个 $k$ 可以使最后一位为强制 $1$（非结尾），所以有：
   $$
    \sum_{1\leq i < n} (f_{i-1,2} + f_{i - 1,1}) \cdot i \rightarrow ans
   $$
   

那么本题就完美结束了！

---
最后注意一些关于初始化的细节

$f_{1,0} = (n - 1),f_{1,1} = 1,f_{1,2} = 0$ 

因为第 $0$ 位也可以视做有一个强制 $1$ ，所以 $f_{0,2} = 1$

AC-code:
```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long

int rd() {
	int x = 0, w = 1;
	char ch = 0;
	while (ch < '0' || ch > '9') {
		if (ch == '-') w = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		x = x * 10 + (ch - '0');
		ch = getchar();
	}
	return x * w;
}

void wt(int x) {
	static int sta[35];
	int f = 1;
	if(x < 0) f = -1,x *= f;
	int top = 0;
	do {
		sta[top++] = x % 10, x /= 10;
	} while (x);
	if(f == -1) putchar('-');
	while (top) putchar(sta[--top] + 48);
}

const int mod = 1e9+7,N = 1e6+5;

int n,dp[N][3],cnt,ans;

signed main() {
    n = rd();
    dp[1][0] = n - 1;dp[1][1] = 1;dp[1][2] = 0;dp[0][2] = 1;
    for(int i = 1;i<n;i++) {
        ans = (ans + dp[i][0] * (n - 1) % mod) % mod;
        dp[i + 1][0] = (dp[i + 1][0] + (n - 1) * (dp[i][1] + dp[i][2]) % mod) % mod;
        dp[i + 1][1] = (dp[i + 1][1] + (dp[i][1] + dp[i][2]) % mod) % mod;
		if(i - 2 >= 0) cnt = (cnt + (dp[i - 2][2] + dp[i - 2][1]) % mod) % mod;
        dp[i + 1][2] = cnt;
    } 
    for(int i = 1;i<n;i++) 
    	ans = (ans + (dp[i - 1][2] + dp[i - 1][1]) * i % mod) % mod;
	ans = (ans + dp[n][0]) % mod;
	ans = (ans + dp[n][1]) % mod;
	ans = (ans + dp[n][2]) % mod;
    wt(ans);

	return 0;
}

```

---

## 作者：irris (赞：0)

> 给出 $n$，计算：有多少长度无限的值域 $[1, n]$ 整数序列 $a$，使得若 $i, j \geq n$ 则 $a_i = a_j$，且令 $a_i = x$，$a_{i} = a_{i+1} = \dots = a_{i+x-1}$。

## Solution

考虑到，如果有连着两个数分别都 $\geq 2$，我们称这个序列到这个位置「跑路」了。一个跑路的序列，从跑路位置开始，后面的所有项都相同。

我们令 $f_i$ 表示钦定一个长度为 $i$ 的序列首项不为 $1$ 的合法序列的数量，$f_0 = 1, f_1 = n - 1$。令 $g_i$ 表示长度为 $i$ 的合法序列数量，则枚举开头有多少个 $1$，可得 $g_i = f_0 + f_1 + \dots + f_n$。我们假定 $g_i\ (i \lt 0) = 1$。

考虑转移。我们已知了 $f_0 \sim f_{k-1}$，要求 $f_k$。枚举这个 $\neq 1$ 的值是多少，记为 $j$。如果这个值后面「跑路」了，答案是 $n - 1$；否则后面接的是 $1$，答案是 $g_{k - j - 1}$。

整理一下，$f_k = \sum\limits_{j=2}^n (g_{k-j-1} + n - 1)$。对 $g$ 再做一个前缀和即可方便转移。时间复杂度 $\mathcal O(n)$。

---

## 作者：ChenZQ (赞：0)

## 解法

首先我们设 $f_i$ 表示从 $n$ 填到 $i$ 的方案数。

那么我们考虑三种情况：

1. 这个位置填 $1$ ，那么没什么贡献，直接加上 $f_{i+1}$。
2. 这个位置和下个位置同时填两个大于 $1$ 的数，那么这个数和前一个数都有 $(n-1)$ 种选法，贡献自然是 $(n-1)\times(n-1)$。
3. 这个位置填一个大于 $1$ 的数，但是他对数组之后的影响不会超过 $n$ ，也就是填 $x$，满足 $i+x\le n$，那么我们搞完这一段后，剩下的方案数自然是继承 $f_{i+x+1}$ 的，综合起来就是 $\sum^{i+3}_{n}f_i$。
4. 这个位置填一个大于 $1$ 的数，对数组之后的影响超过了 $n$ ，这个数的范围是 $i+x > n$，且 $x\le n$ 的，解不等式组可得这样的数有 $i+1$ 个。

那么我们把上面几种情况加在一起就是状态的方案数了。

## 代码

```c++
#include <bits/stdc++.h>
using namespace std;
const int inf = (int)1e9 + 7;
int n;
int f[1232022];
int main()
{
	scanf("%d",&n);
	f[n]=n;
	f[n-1]=1LL*n*n%inf;
	int s=0;
	for(int i=n-2;i>=1;i--)
	{
		s=(1LL*f[i+3]+1LL*s)%inf;
		f[i]=(f[i+1]+1LL*(n-1)*(n-1)+i+1+s)%inf;
	}
	printf("%d",f[1]);
}//654321
```

---

## 作者：_edge_ (赞：0)

挺好的 DP 计数题。

首先我们需要观察出来一个性质，就是说如果一个 $x$ 后面跟着一个 $y$ 满足 $x,y>1$ ，那么后面的也会被唯一确定，这个证明非常简单，只需要考虑 $x$ 后面和 $y$ 要相同，然后 $y$ 也推过去，这样推下来一定是唯一的。

然后我们再考虑 DP 计数。

设 $f_{i}$ 表示前 $i$ 个数被唯一确定了的方案数。

然后我们先不管复杂度，因为 DP 这种肯定是可以被优化转移的。

我们枚举当前这个填了啥，填了之后这个数以后的都只能填 $1$，除非当前这个是 $1$，然后我们就确定了一段区间，如果当前填 $1$ 的话，对后面一点贡献都没有的。

我们再思考，如果后面全都填 $x,y>1$ 的情况，那么就算 $f_{i} \times (n-1)^2$，但是，这里有点小问题，比如说我们确定了 $n$ 之后就不需要确定后面的，这地方要个小特判。

然后暴力统计所有的答案即可，注意这里超过 $n$ 的部分也需要被统计进答案，原因就是他们都是 $1$ 也是一种合法转移。

以及确定一段区间之后的那种转移，在 $i=n-1$ 的情况下也不需要，因为他们后面一定都是 $1$ 了。

然后我们写出了下面的代码：

```cpp
#include <bits/stdc++.h>
#define int long long 
using namespace std;
const int INF=1e6+5;
const int Mod=1e9+7;
int n,f[INF],a[INF],ans;
signed main()
{
    ios::sync_with_stdio(false);
    cin>>n;f[0]=1;
    for (int i=0;i<n;i++) {
        f[i+1]+=f[i];
        if (i==n-1) continue;
        for (int j=2;j<=n;j++) 
            f[i+1+j]+=f[i],f[i+1+j]%=Mod;
    }
    for (int i=0;i<n;i++) ans+=f[i]*(i==n-1?1:(n-1))*(n-1)%Mod,ans%=Mod;
    for (int i=n;i<=n*2;i++) ans+=f[i];
    cout<<ans<<"\n";
    return 0;
}
```

然后考虑优化，由于刷表比较难优化，所以需要改成填表。

填了表以后会发现 $j$ 的上下界可以轻松算出，然后前缀和优化。

```cpp
#include <bits/stdc++.h>
#define int long long 
using namespace std;
const int INF=3e6+5;
const int Mod=1e9+7;
int n,f[INF],a[INF],ans,sum[INF];
signed main()
{
    ios::sync_with_stdio(false);
    cin>>n;f[0]=1;sum[0]=1;
    for (int i=1;i<=n*2;i++) {
        if (i-1<n) f[i]+=f[i-1];
        // for (int j=2;j<=n;j++) 
        //     f[i+1+j]+=f[i];f[i+1+j]%=Mod;
        // for (int j=2;j<=n;j++)
        //     if (i-j-1>=0 && i-j-1<n-1) f[i]+=f[i-j-1],f[i]%=Mod;
        
        int L=max(0ll,i-n-1),R=min(i-2-1,n-2),xx=0; 
        if (L-1>=0) xx=sum[L-1]; 
        if (R>=0) f[i]+=sum[R]-xx;
        
        f[i]%=Mod;f[i]+=Mod;f[i]%=Mod;
        sum[i]=sum[i-1]+f[i];sum[i]%=Mod;
    }
    for (int i=0;i<n;i++) ans+=f[i]*(i==n-1?1:(n-1))%Mod*(n-1)%Mod,ans%=Mod;
    for (int i=n;i<=n*2;i++) ans+=f[i],ans%=Mod;
    cout<<ans<<"\n";
    return 0;
}
```


---

