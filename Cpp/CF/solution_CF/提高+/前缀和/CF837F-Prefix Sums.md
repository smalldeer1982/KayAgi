# Prefix Sums

## 题目描述

Consider the function $ p(x) $ , where $ x $ is an array of $ m $ integers, which returns an array $ y $ consisting of $ m+1 $ integers such that $ y_{i} $ is equal to the sum of first $ i $ elements of array $ x $ ( $ 0<=i<=m $ ).

You have an infinite sequence of arrays $ A^{0},A^{1},A^{2}... $ , where $ A^{0} $ is given in the input, and for each $ i>=1 $ $ A^{i}=p(A^{i-1}) $ . Also you have a positive integer $ k $ . You have to find minimum possible $ i $ such that $ A^{i} $ contains a number which is larger or equal than $ k $ .

## 样例 #1

### 输入

```
2 2
1 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3 6
1 1 1
```

### 输出

```
2
```

## 样例 #3

### 输入

```
3 1
1 0 1
```

### 输出

```
0
```

# 题解

## 作者：jucason_xu (赞：2)

主题和生成函数相关，但是最后也附上了不用生成函数的做法。

和本题主流的矩阵快速幂无关。

首先，我们发现这道题目“序列会增长”的情况完全就是唬人的，因为我们把 $x_i$ 输入之后，$y_i$ 永远是 $0$，而前导 $0$ 在计算的过程中没有任何的作用。所以可以直接原地做前缀和。

我们还发现，除了序列 $A^0$，其他的序列都是递增的（$A^i_j-A^i_{j-1}=A^{i-1}_{j}\ge 0$），所以 $s\gt 0$ 时，序列 $A^s$ 存在 $A^s_i\ge k$ 等价于 $A^s_n\ge k$。

然后，我们考虑二分答案，每次检测进行 $a$ 次运算之后的序列是否满足条件。

首先考虑的是生成函数和卷积，因为如果我们构造生成函数 $f(x)=A^0_1x+A^0_2x^2+\cdots$ 以及 $\mathrm{I}(x)=1+x+x^2+x^3+\cdots$，那么求 $a$ 次前缀和的结果就是 $f(x)\times(\mathrm{I}(x))^a$。直接看第 $n$ 位即可。求 $(\mathrm{I}(x))^a$ 可以使用卷积意义下的快速幂进行，复杂度 $O(n\log n\log a)$，看上去可以过，但别忘了，我们这是在二分答案的 `check`，所以总复杂度还要多一个 $\log k$，铁定过不了。（而且系数和 $k$ 取 $\min$ 也可能达到 $10^{18}$ 级别，点值表示后其大小和 `complex` 误差不是 FFT 配 `__int128` 所能承受的）

我们先把序列所有的前导 $0$ 去掉，找到序列第一个 $1$ 的位置，考虑它对答案的贡献。我们发现，只要序列的长度达到一定长度，只有开头一个 $1$ 的序列的第 $n$ 项就会以指数级增长（即 $a$ 次运算后，第 $n$ 项的级别是 $O(n^a)$。虽然我们知道这可能有一个很小的常数，但是不要紧，当 $n\ge 10$ 的时候，达到 $10^{18}$ 的时间也不会超过 $500$。更何况 $a$ 会随着 $n$ 的增大而减小，所以我们可以直接暴力做。

对于 $n<10$，我们考虑别的方法。

常见的思路是 $O(n^3\log^2 k)$ 的二分答案和矩阵快速幂。但是我们前面已经思考了生成函数做法，不如将其推到底。

首先，直接暴力做卷积是可以做的，但是这就显得很怨种。我们都已经推到 $n<10$ 了，再用多项式总是有点杀鸡用牛刀的感觉（而且点值表示后虽然不会爆 `__int128` 了，误差还是有点可怕）。

我们考虑看看 $f(x)\times(\mathrm{I}(x))^a$ 这个式子，发现 $A^0_i$ 对答案 $(f\times\mathrm{I}^a)(x)$ 的第 $n$ 项的贡献是 $\mathrm{I}^{a-1}(x)$ 的第 $n-i$ 项系数。

考虑求出这个东西，$G(x)=\mathrm{I}^{a-1}(x)=\dfrac{1}{(1-x)^{a-1}}$，求第 $y$ 项就是求 $\dfrac{G^{(y)}(0)}{y!}$。而 $G^{(y)}(x)=\dfrac{(a-1)\cdots(a+y-2)}{(1-x)^{a-1+y}}$，则 $\dfrac{G^{(y)}(0)}{y!}=\dfrac{(a+y-2)!}{(1-0)^{a-1+y}(a-2)!y!}={a+y-2 \choose y}$

然后我们的 $y=n-i$，所以需要的 $(f\times\mathrm{I}^a)(x)$ 的第 $n$ 项其实就是 $\sum_{i\le n}{{a+n-i-2\choose n-i+1}A^0_i}$。

接下来，我们发现 $n-i+1$ 很小，我们如果记 $p=n-i+1,q=a+n-i-2$，这个组合数就是 $\dfrac{p(p-1)(p-2)\cdots (p-q+1)}{q!}$，而上下都不超过 $n$ 项，下面的 $q!$ 不超过 $3628800$，所以我们可以先暴力做出 $q!$，然后用一个 `__int128` 暴力维护上面的乘积。一旦这个积的大小超过了 $q!\times k$，就直接返回 $k$ 退出。然后扫 $1$ 到 $n$，计算出第 $n$ 项的答案，中途大于 $k$ 就直接返回 $1$。当然我们记住我们是在二分答案的，组合数的计算也是 $O(n)$ 的，$n\lt 10$ 的部分复杂度是 $O(n^2\log k)$。

一些闲话：不会生成函数怎么推最后的组合数式子？

我们可以只看第 $i$ 项，考虑它对答案的贡献。实际上就是抹掉前 $i-1$ 项，贡献次数就是对一个 $1$ 和 $n-i$ 个 $0$ 做 $a$ 次前缀和之后的第 $n-i+1$ 项。

我们发现，如果我们把 `1 1 1 1 1 1 1...` 这样的无穷序列排下来，求 $x$ 次前缀和之后的第 $y$ 项的话，其实就是在表 $S_{i,j}=S_{i-1,j}+S_{j-1,i}$ 中求第 $x$ 行的第 $j$ 列。

如果我们把这个表列出来：

```
1 | 1 1 1 1 1
2 | 1 2 3 4 5
3 | 1 3 6 10 15
4 | 1 4 10 20 35
```
如此列下来，你会发现，它就是旋转 $45$ 度之后的杨辉三角！如果我们把左下到右上对角线看作一行的话，$S_{i,j}=S_{i-1,j}+S_{j-1,i}$ 正好满足组合数的递推形式。

那么，我们进行坐标变换，容易发现第 $x$ 行的第 $y$ 列（从 $1$ 开始）对应到杨辉三角坐标之后，处在第 $x+y-2$ 行的第 $y-1$ 列（从 $0$ 开始）。而此处的系数就是 ${x+y-2\choose y-1}$，代入得到 ${a+n-i-2\choose n-i+1}$。也就使用非生成函数的办法推出了这个式子。

```cpp
#define rp(i,n) for(ll i=1;i<=n;i++)
#define rep(i,a,b) for(ll i=a;i<=b;i++)
ll n,k,a[200005];
__int128 A[200005];
inline __int128 C(ll n,ll m){
	__int128 res=1,f=1;
	rp(i,m)f*=i;
	rep(i,n-m+1,n){
		res*=i;
		if(res>=f*k)return k;
	}
	return res/f;
}
inline void solve1(){
	ll mx=0;
	rp(i,n)A[i]=a[i];
	int cur=0;
	while(A[n]<k){
		rp(i,n)A[i]=A[i-1]+A[i];
		cur++;
	}
	cout<<cur<<endl;
}
inline bool check(ll f){
	__int128 ans=0;
	if(f>=k)return 1;
	rp(i,n){
		ll x=f,y=n-i+1;
		__int128 dd=C(x+y-2,y-1);
		if(a[i]&&dd>=k)return 1;
		ans+=a[i]*dd;
		if(ans>=k)return 1;
	}
	return ans>=k;
}
inline void solve2(){
	ll l=1,r=1e18,mid,ans=0;
	while(l<=r){
		mid=l+r>>1;
		if(check(mid))ans=mid,r=mid-1;
		else l=mid+1;
	}cout<<ans<<endl;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>n>>k;
	rp(i,n)cin>>a[i];
	rp(i,n)if(a[i]>=k){
		cout<<0<<endl;
		return 0;
	}
	int be=1;
	while(!a[be])be++;be--;
	rp(i,n-be)a[i]=a[i+be];n-=be;
	if(n>10)solve1();
	else solve2();
	return 0;
}
//Crayan_r

---

## 作者：LJB00131 (赞：2)

### 基本思路

分类讨论：

1.当 $10 \le n$ 时，直接暴力求出每次新的数组即可。因为增长快。

2.当 $n \le 10$ 时， 注意到本题答案具有单调性，可以二分。又因为n比较小，时空上可以承受矩阵乘法。所以用矩阵乘法计算数组并判断即可。

### 注意点
本题难就难在细节的处理上。

1.首先注意数组前导0对答案无贡献，删去。

2.在做矩阵乘法时，遇到太大的数会使结果爆long long, 所以遇到过大数时将其置为k即可。

3.注意使用龟速乘

附上代码

```cpp
#include<bits/stdc++.h>

using namespace std;

#define N 200005
typedef long long ll;

int n;

ll K, a[N];

bool flag = 0;

ll mul(ll x, ll y)
{
	ll ans = 0;
	while(y)
	{
		if(y & 1) ans += x, ans = min(ans, K);
		x += x, x = min(x, K);
		y >>= 1;
 	}
	return ans;
}

struct Matrix
{
	int n, m;
	ll a[25][25];
	void clear(int x, int y)
	{
		n = x, m = y;
		memset(a, 0, sizeof(a));
	}

	Matrix operator * (const Matrix &o) const
	{
		Matrix ans;
		ans.clear(n, o.m);
		for(int i = 1; i <= ans.n; i++)
			for(int j = 1; j <= ans.m; j++)
				for(int k = 1; k <= m; k++)
				{
					ans.a[i][j] += mul(a[i][k], o.a[k][j]);
					ans.a[i][j] = min(ans.a[i][j], K);
				}
		return ans;
	}

	Matrix operator ^ (const ll &k) const
	{
		Matrix ans;
		ans.clear(n, m);
		for(int i = 1; i <= min(ans.n, ans.m); i++) ans.a[i][i] = 1;
		Matrix base = *this;
		ll x = k;
		while(x)
		{
			if(x & 1) ans = ans * base;
			base = base * base;
			x >>= 1;
		}
		return ans;
	}

	void print()
	{
		for(int i = 1; i <= n; i++)
		{
			for(int j = 1; j <= m; j++)
				cout << a[i][j] << ' ';
			cout << endl;
		}
	}
};

int main()
{
	scanf("%d%lld", &n, &K);
	bool is1 = 0;
	for(int i = 1; i <= n; i++) 
	{
		scanf("%lld", &a[i]);
		if(a[i] >= K)
		{
			cout << 0 << endl;
			return 0;
		}
		if(a[i]) is1 = 1;
		if(a[i] == 0 && !is1) i--, n--;
	}
	if(n > 10)
	{
		int cnt = 0;
		while(1)
		{
			cnt++;
			for(int i = 1; i <= n; i++)
			{
				a[i] += a[i - 1];
				if(a[i] >= K || a[i] < 0) 
				{
					cout << cnt << endl;
					return 0;
				}
			}
		}
	}
	Matrix b;
	b.clear(n, 1);
	for(int i = 1; i <= n; i++) b.a[i][1] = a[i];
	Matrix c;
	c.clear(n, n);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= i; j++) c.a[i][j] = 1;
	ll l = 1, r = 1000000000000000000, ans = 0;
	while(l <= r)
	{
		ll mid = l + r >> 1;
		bool flag = 0;
		Matrix tmp = (c ^ mid) * b;
		for(int i = 1; i <= tmp.n; i++)
			for(int j = 1; j <= tmp.m; j++) flag = max(flag, (tmp.a[i][j] >= K || tmp.a[i][j] < 0));
		if(flag)
		{
			ans = mid;
			r = mid - 1;
		}
		else l = mid + 1;
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：封禁用户 (赞：1)

大佬们都用矩阵，发一篇分讨的题解。

首先来纯数学解一下：对于 $A_j$ 数组，首先最大值一定在 $A_{j_n}$，那我们就可以对每一个 $A_{0_i}$ 算能对 $A_{j_n}$ 贡献多少次。算出来是 $\sum_{i=1}^{n} \binom{j-1+n-i}{j-1}\times a_i$。

考虑直接二分，发现根本不能计算上面那个式子有没有大于 $k$。需要换一种算法。

先取掉前导零肯定是不影响答案的。设新的 $A_0$ 数组为 $b$，按最劣情况算，$b_1=1$ 时，答案至少是 $\binom{j-1+n-1}{j-1}$。

发现 $n \ge 4$ 时，$j=10^8\div n$ 时答案已远超 $k$，可以暴力。

当 $n=3$ 时，二分答案，即算 $mid\times (mid+1) \div 2 \times b_1+ mid\times b_2 + b_3 \ge k$ 的最小值。

当 $n=2$ 时，答案即为 $\lceil (k-b_2)\div b_1\rceil$。

完了。

## AC code
```cpp
#include<bits/stdc++.h>
#define int __int128
#define f(i,j,n) for(long long i=j;i<=n;i++)
#define updmax(a,b) a=max(a,b)
#define updmin(a,b) a=min(a,b)
#define pb push_back
#define XQZ
using namespace std;
const int N=2e5+10;
long long n,m;
long long b[N];
int summ[N];
long long a[N];
void gs(){
	long long cf;
	cin>>cf>>m;
	long long maxn=0;
	int sum=0;
	bool u=0;
	f(i,1,cf)cin>>b[i];
	f(i,1,cf)if(b[i]!=0||u)a[++n]=b[i],u=1;
	f(i,1,n)updmax(maxn,a[i]),sum+=a[i],summ[i]=summ[i-1]+a[i];
	if(maxn>=m){cout<<"0\n";return;}
	else if(sum>=m){cout<<"1\n";return;}
	if(n==2){
		cout<<(m-a[2])/a[1]+(((m-a[2])%a[1])!=0)<<"\n";
	}else if(n==3){
		int l=2,r=1e18;
		long long ans=2;
		while(l<=r){
			int mid=(r-l)/2+l;
			int mm=m-a[3];
			if(mm<0){r=mid-1;ans=mid;}
			if((mid*a[2])>=mm){r=mid-1;ans=mid;}
			else{
				mm-=(mid*a[2]);
				if((mid*(mid+1)/2)*a[1]>=mm){r=mid-1;ans=mid;}
				else l=mid+1;
			}
		}
		cout<<ans<<endl;
	}else{
		long long cnt=1;
		while(1){
			cnt++;
			f(i,1,n)summ[i]=summ[i-1]+summ[i];
			if(summ[n]>=m){cout<<cnt<<endl;return;}
		}
	}
}
signed main(){
#ifndef XQZ
	freopen(".in","r",stdin);
	freopen(".out","w",stdout);
#endif
#ifdef NXD
	int t=0;cin>>t;while(t--)
#endif
		gs();
	return 0;
}
```

---

## 作者：yangshengyu0719 (赞：0)

# 前言
本人在这里分享一种极其猥琐的做法，运用了一点**根号分治**（虽然并非取根号）的思想，复杂度也不算劣。
# 分析
首先当 $$A^0$$ 数组本身存在大于 $$k$$ 的数的时候，直接输出 0。

接下来的的每次操作相当于将 $$A^0$$ 反复前缀和，显然对于 $$A^i$$，最后一个数为最大的，且它的值单调递增，因此我们想到二分。

那么我们该怎么快速计算这个值呢？显然这个值可以拆做 $$\sum_{i=1}^n x_i \times A_i$$ 的形式，于是我们考虑对此打表找找规律。

令第 $$i$$ 行第 $$j$$ 列的数为数组操作 $$i$$ 次后，拆分最后一个数得到的 $$A^0$$ 第 $$j$$ 个数的系数。因此当 $$n=5,i=6$$ 时，有下表：
![](https://cdn.luogu.com.cn/upload/image_hosting/9xkbyz3t.png)

可以发现，第 $$i$$ 行 $$j$$ 列的数即为 $$\binom{n+i-j-1}{i-1}$$。因此 $$A^i$$ 的最后一个值为 $$\sum_{j=0}^n \binom{n+i-j-1}{i-1} \times A_j$$。

可这时又会有一个问题，如何快速计算这个组合数。于是我们开启人类智慧，对于一个组合数 $$\binom{n}{m}$$ 当 $$m\le6$$ 时我们暴力计算即可，否则 $$n$$ 一定小于 3000，不然结果一定大于 $$k$$ (看作 $$10^{18}$$)。然后对于这个 3000 规模的组合数我们显然可以直接用杨辉三角预处理，同理当组合数的值大于 $$k$$ 我们直接令其为 $$k+1$$ 即可。

# Code
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
__int128 C[3005][3005];
int n,K,a[200005],maxn;
void Write(__int128 x){
	if(x>9) Write(x/10);
	putchar('0'+x%10);
}
__int128 Calc(__int128 a,__int128 b){//巨猥琐组合数 
	if(a-b<b) b=a-b;
	if(!b) return 1;
	if(a>K) return K+1;
	if(b<=6){
		__int128 res=1;
		for(__int128 i=1;i<=b;i++){
			res=res*(a-i+1)/i;
			if(res>K) return K+1;
		}
		return res;
	}
	//可得此时a一定小于3000
	if(a>=3000) return K+1;
	return C[a][b];
}
void Init(){
	for(int i=0;i<=3000;i++) C[i][0]=1;
	for(int i=1;i<=3000;i++)
		for(int j=1;j<=i;j++)
			if(C[i-1][j]+C[i-1][j-1]>K) C[i][j]=K+1;
			else C[i][j]=C[i-1][j]+C[i-1][j-1];
}
bool check(__int128 x){
	__int128 sum=0;
	for(int i=1;i<=n;i++){
		sum+=Calc(n+x-i-1,x-1)*(__int128)a[i];
		if(sum>=K) return 1;
	}
	return 0;
}
signed main(){
//	freopen("in.txt","r",stdin);
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>K;
	for(int i=1;i<=n;i++) cin>>a[i],maxn=max(maxn,a[i]);
	if(maxn>=K){cout<<0;return 0;}
	Init();
	int l=1,r=K;
	while(l<r){
		int mid=(l+r)>>1;
		if(!check(mid)) l=mid+1;
		else r=mid;
	}
	cout<<r;
	return 0;
}
```

---

## 作者：叶ID (赞：0)

题目链接：[CF837F Prefix Sums](https://www.luogu.org/problem/CF837F)

【广告】[在个人博客食用](https://toxic2018.ml/1884/)风味更佳

****

题意大意请见题目链接中的翻译。本题解将参照这个翻译进行讲解。

注意：题目中还有一个限制，即，“数列中必有至少两个元素是正数”。因此，答案不会是无穷大。

****

### 解题思路

本题解中，待求的值可能用$x$表示。

我们发现，要解决这个问题，只需考虑某个数列$A^x$中的最大值。因为如果最大值没有大于等于$k$，其他值也不会大于等于$k$。

对于一个数列$A$（其中一定有正数），那么得到的$p(A)$开头一定有一个$0$。这个$0$可以直接忽略，因为它一定不是最大值。

于是我们可以改造函数$p$，使得$p([1,1,1]) = [1,2,3]$。

另外，初始数列$A^0$的“前导0”无论如何进行前缀和，其值必然仍然是$0$，并且不对后面的值产生影响。因此可以删去$A^0$中的前导0。（此后的内容都在没有“前导0”的情况下考虑）

然后我们发现，如果此时$A^0$的长度如果大于等于$10$，那么只需进行很少的几次前缀和就会出现元素大于等于$k$。因此，如果$A^0$长度大于等于$10$，可以直接暴力求解。

如果$A^0$长度为$2$，那么假设$A^0 = [a,b]$，则有$A^x = [a,a\cdot x + b]$。因此，待求的值可以通过除法得出：$x_{min} = \lceil \frac{k-b}{a} \rceil$

如果$A^0$的长度介于$2$和$10$之间，答案可能非常大，我们需要更好的做法。我们发现这题的情况有单调性，而且用$k$求$x$很难，而判断$A^x$中是否有元素大于等于$k$则看起来较为容易。（因此可以使用二分答案）

怎么个容易法呢？由于$A^0$的长度很小，我们可以使用矩阵快速幂。设$A^0$的长度为$n$。定义一个$n \times n$的矩阵$M$，其中对于所有$j \leq i$，$M_{i,j} = 1$，其余情况$M_{i,j} = 0$。

则$A^x = M^x \cdot A^0$。

那么二分答案就可以实现了。

还有一个问题，矩阵快速幂溢出了怎么办？

由于我们只关心最后的数字是小于$k$还是大于等于$k$，因此类似于取模，我们计算时时时刻刻将结果和$k$取$min$。

但是在这种情况下乘法运算仍然可能溢出，怎么办呢？~~\_\_int128\_t~~ 我们可以使用类似于快速幂的方式，实现一种“龟速乘法”（即，使用加法实现乘法）。具体如下：

```cpp
// 代码中limit代表k的值
int mxqmul(int a,int b) {
    if(b==0) return 0;
    int r = mxqmul(a,b>>1);
    r = min(r + r, limit);
    if(b&1) return min(r + a, limit);
    return r;
}
```

### 复杂度分析

删除“前导0”，时间复杂度为$O(n)$，然后：

- 当$|A^0|=2$时，仅仅进行一次除法，$O(1)$
- 当$|A^0|\geq 10$时，实测在极限数据下答案为$411$。因此复杂度上限为$O(411n)$。计算$411 \cdot 200000 = 82,200,000$，因此不会有问题。
- 当$2 \lt |A^0| \lt 10$时，二分答案占有复杂度$log(r)$（r是二分上界），而二分的`check`复杂度瓶颈在于矩阵乘法，复杂度上界为$n^2 \cdot log(r)$，另外“龟速乘法”的复杂度上界为$log(long\ long) = 31$，因此复杂度上限为$O(log^2(r)\cdot n^2 \cdot 31)$。如果定二分范围为$[0,64356879284]$，计算`Math.log2(64356879284)**2 * 10**2 * 31 == 3996507.528120665`，因此也不会有问题。

### 代码

```cpp
// status: [Accepted]
// oj:     [luogu]
 
#include<bits/stdc++.h>
using namespace std;
 
typedef long long ll;
#define int ll

const int MAXN = 200001;
int arr[MAXN];
// 题目中的k。因为k一般用作循环变量，所以不作为变量名
int limit;
// A0的长度
int n;

// “龟速乘法”
int mxqmul(int a,int b) {
    if(b==0) return 0;
    int r = mxqmul(a,b>>1);
    r = min(r + r, limit);
    if(b&1) return min(r + a, limit);
    return r;
}
 
// 矩阵乘法封装类
struct Matrix:vector<vector<int> > {
 
    Matrix __construct(int l = 0, int w = 0, int v = 0)
    {
        assign(l, vector<int>(w, v));
        return *this;
    }
 
    Matrix(int l = 0, int w = 0, int v = 0)
    {
        assign(l, vector<int>(w, v));
    }
 
    unsigned sizeL() const {
        return size();
    }
 
    unsigned sizeW() const {
        return empty()?0:(*this)[0].size();
    }
 
    Matrix operator* (const Matrix &other) const {
        if(sizeW()!=other.sizeL()) {
            return Matrix(0,0,0);
        }
        
        int l=sizeL(),w=other.sizeW(),p=sizeW();
        Matrix ret(l,w,0);
        
        for(int i=0;i<l;i++) {
            for(int j=0;j<w;j++) {
                for(int k=0;k<p;k++) {
                    ret[i][j]+=mxqmul((*this)[i][k],other[k][j]);
                    ret[i][j] = min(ret[i][j],limit);
                }
            }
        }
        return ret;
    }
    Matrix operator*= (const Matrix &other) {
        *this=(*this)*other;
        return *this;
    }
 
    Matrix pow(int t) {
        if(t==0) {
            Matrix ret(sizeL(),sizeL(),0);
            for(int i=0;i<sizeL();i++) {
                ret[i][i]=1;
            }
            return ret;
        }
        if(t==1) {
            return *this;
        }
        if(t==2) {
            return (*this)*(*this);
        }
        Matrix tmp=pow(t/2);
        if(t%2==0) return tmp*tmp;
        else return (*this)*tmp*tmp;
    }
 
    Matrix pow_(int t) {
        *this=pow(t);
        return *this;
    }
 
    void oi_input() {
        for(int i=0;i<sizeL();i++) {
            for(int j=0;j<sizeW();j++) {
                scanf("%lld",&(*this)[i][j]);
            }
        }
    }
 
    void oi_output() {
        for(int i=0;i<sizeL();i++) {
            for(int j=0;j<sizeW();j++) {
                printf("%lld ",(*this)[i][j]);
            }
            printf("\n");
        }
    }
};

// 二分的check。如果Ap中存在大于等于limit的元素返回true，否则返回false
bool check(int p) {
    Matrix mt(n,n,0);
    
    for(int i=0;i<n;i++) {
        for(int j=0;j<=i;j++) {
            mt[i][j] = 1;
        }
    }
    
    Matrix ar(n,1,0);
    for(int i=0;i<n;i++) {
        ar[i][0] = arr[i+1];
    }
    
    ar = mt.pow(p) * ar;
    
    for(int i=0;i<n;i++) {
        if(ar[i][0] >= limit) return true;
    }
    return false;
}

// 删除前导0，返回删除后数列的长度
int unuqie(int *arr,int len) {
    int ptr = 0;
    for(int i=1;i<=len;i++) {
        if(arr[i] != 0 || ptr) {
            arr[++ptr] = arr[i];
        } 
    }
    return ptr;
}

// 功能相当于 (int)ceil((double)a/b)
// 用于A0的长度等于2的情况下。由于double的精度问题，并不能使用强转double并ceil的方法。
int ceilDiv(int a,int b) {
    return a/b + bool(a%b);
}

signed main() {
    scanf("%lld",&n);
    scanf("%lld",&limit);
    for(int i=1;i<=n;i++) {
        scanf("%lld",&arr[i]);
    }

    // 去除前导0
    n = unuqie(arr,n);
    
    // 判断 |A0| == 2
    if(n == 2) {
        printf("%lld\n",max(0ll, ceilDiv((limit - arr[2]), arr[1])));
        exit(0);
    }
    
    // 判断答案为0的情况（防止出现问题）
    for(int i=1;i<=n;i++) {
        if(arr[i] >= limit) {
            printf("0\n");
            exit(0);
        }
    }
    
    // 如果 |A0| >= 10，可以暴力迭代完成。
    if(n >= 10) {
        int cnt = 0;
        while(1) {
            cnt++;
            for(int i=1;i<=n;i++) {
                arr[i] += arr[i-1];
                if(arr[i] >= limit) {
                    printf("%lld\n",cnt);
                    exit(0);
                }
            }
        }
    }
    
    // 否则二分答案
    // 考虑二分边界的方法：
    //   如果check(mid)为true，那么mid值偏大或正好
    //     由于check(mid)为true，最终答案可能是mid，所以 r = mid (如果最终答案不可能是mid，取 r = mid - 1)
    //   如果check(mid)为false，那么mid值偏小
    //     最终答案不可能取mid，所以 l = mid + 1 (如果最终答案可能是mid，取 l = mid)
    // 随后考虑最容易死循环的情况，即 r - l == 1，来确定mid的取值
    //   如果令 mid = l+r - (l+r)/2，则此情况下mid = r：
    //     若check(mid) == true，那么执行 r = mid，即 r = r，此时二分范围没有变小，会造成死循环，所以应当令 mid = (l+r)/2
    int l = 0, r = 64356879284;
    while(l<r) {
        int mid = (l+r)/2;
        if(check(mid)) {
            r = mid;
        }
        else {
            l = mid + 1;
        }
    }
    printf("%lld\n",l);
}


```

评测记录：[R24947635](https://www.luogu.org/record/24947635)


---

