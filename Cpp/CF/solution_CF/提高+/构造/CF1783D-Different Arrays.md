# Different Arrays

## 题目描述

You are given an array $ a $ consisting of $ n $ integers.

You have to perform the sequence of $ n-2 $ operations on this array:

- during the first operation, you either add $ a_2 $ to $ a_1 $ and subtract $ a_2 $ from $ a_3 $ , or add $ a_2 $ to $ a_3 $ and subtract $ a_2 $ from $ a_1 $ ;
- during the second operation, you either add $ a_3 $ to $ a_2 $ and subtract $ a_3 $ from $ a_4 $ , or add $ a_3 $ to $ a_4 $ and subtract $ a_3 $ from $ a_2 $ ;
- ...
- during the last operation, you either add $ a_{n-1} $ to $ a_{n-2} $ and subtract $ a_{n-1} $ from $ a_n $ , or add $ a_{n-1} $ to $ a_n $ and subtract $ a_{n-1} $ from $ a_{n-2} $ .

So, during the $ i $ -th operation, you add the value of $ a_{i+1} $ to one of its neighbors, and subtract it from the other neighbor.

For example, if you have the array $ [1, 2, 3, 4, 5] $ , one of the possible sequences of operations is:

- subtract $ 2 $ from $ a_3 $ and add it to $ a_1 $ , so the array becomes $ [3, 2, 1, 4, 5] $ ;
- subtract $ 1 $ from $ a_2 $ and add it to $ a_4 $ , so the array becomes $ [3, 1, 1, 5, 5] $ ;
- subtract $ 5 $ from $ a_3 $ and add it to $ a_5 $ , so the array becomes $ [3, 1, -4, 5, 10] $ .

So, the resulting array is $ [3, 1, -4, 5, 10] $ .

An array is reachable if it can be obtained by performing the aforementioned sequence of operations on $ a $ . You have to calculate the number of reachable arrays, and print it modulo $ 998244353 $ .

## 样例 #1

### 输入

```
4
1 1 1 1```

### 输出

```
3```

## 样例 #2

### 输入

```
5
1 2 3 5 0```

### 输出

```
7```

# 题解

## 作者：zac2010 (赞：11)

### 思路

这道题目第一眼动态规划， $dp_{i,j}$ 表示第 $i$ 个操作后 $i+2$ 的位置的值为 $j$，然后我发现 $j=0$ 转移到后面会重复加，所以特殊处理即可。

不过 $j$ 可能是负数，所以所有 $j$ 都加上 $\sum_{i=1}^n a_i$ 就行了。

这道题似乎用刷表法简单些，填表发思维上相对于刷表法略显复杂。

给个刷表法的转移方程（为了方便看懂，这里的第二维没有加上 $\sum_{i=1}^n a_i$）：
$$
dp_{i+1,a_{i+3}+j}=dp_{i+1,a_{i+3}+j}+dp_{i,j}
$$
$$
dp_{i+1,a_{i+3}-j}=dp_{i+1,a_{i+3}-j}+dp_{i,j}
$$
$j=0$ 则不用上面的式子，而是特殊处理：
$$
dp_{i+1,a_{i+3}}=dp_{i,j}
$$
### 代码

顺便把刷表法和填表发都练了一下。

#### 刷表法

```cpp
#include <bits/stdc++.h>
#define L(i, a, b) for(int i = a; i <= b; i++)
#define R(i, a, b) for(int i = a; i >= b; i--) 
using namespace std;
const int N = 310, mod = 998244353;
int n, m, add, ans, a[N], dp[N][N * N << 1];
void Upd(int &x, int v){
	x += v;
	x -= (x < mod)? 0 : mod;
}
int main(){
	scanf("%d", &n);
	L(i, 1, n) scanf("%d", &a[i]), add += a[i];
	m = add << 1;
	dp[0][a[2] + add] = 1;
	L(i, 0, n - 3){
		L(j, 0, m){
			if(!dp[i][j]) continue;
			if(j == add)
				dp[i + 1][a[i + 3] + add] = dp[i][j];
			else{
				if(a[i + 3] + j <= m) Upd(dp[i + 1][a[i + 3] + j], dp[i][j]);
				if(a[i + 3] <= j) Upd(dp[i + 1][a[i + 3] - j + m], dp[i][j]);
			}
		}
	}
	L(i, 0, m) ans = (ans + dp[n - 2][i]) % mod;
	printf("%d\n", ans);
	return 0;
}
```


#### 填表法

```cpp
#include <bits/stdc++.h>
#define L(i, a, b) for(int i = a; i <= b; i++)
#define R(i, a, b) for(int i = a; i >= b; i--) 
using namespace std;
const int N = 310, mod = 998244353;
int n, m, add, ans, a[N], dp[N][N * N << 1];
int main(){
	scanf("%d", &n);
	L(i, 1, n) scanf("%d", &a[i]), add += a[i];
	m = add << 1;
	dp[0][a[2] + add] = 1;
	L(i, 1, n - 2){
		L(j, 0, m){
			if(j - add == a[i + 2])
				dp[i][j] = dp[i - 1][add];
			else{
				if(a[i + 2] - j + m <= m) dp[i][j] = dp[i - 1][a[i + 2] - j + m];
				if(j - a[i + 2] >= 0) dp[i][j] += dp[i - 1][j - a[i + 2]];
				dp[i][j] %= mod;
			}
		}
	}
	L(i, 0, m) ans = (ans + dp[n - 2][i]) % mod;
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：吴思诚 (赞：8)

# CF1783D Different Arrays 题解
[题目传送门](https://www.luogu.com.cn/problem/CF1783D)
## 思路
考虑到这题如果不需要判重的话，那方案数显然是 $2^{n-2}$，但是会有重复，让我们考虑什么时候会有重复的情况。容易发现，如果某次是将 $a_i$ 当作加数或减数，如果等于 $0$，那么加减都是不变的，否则是会发生改变的。所以状态表示就是：$f[i][j]$ 表示前 $i$ 次操作后第 $i+1$ 个数的取值为 $j$ 的方案数，转移的话就是 $f[i+1][a[i+3]\pm j]$ 从 $f[i][j]$转移，$j=0$ 时应该只算一次。还需注意偏移。
## 代码（这么简单的代码不会还要看吧）
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=310,M=N*N,mod=998244353;
int n,a[N],f[N][(M<<1)+N];
void add(int &x,int y){
    x+=y;
    if(x>=mod)x-=mod;
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;++i)scanf("%d",a+i);
    f[0][a[2]+M]=1;
    for(int i=0;i<n-2;++i){
        for(int j=-M;j<=M;++j){
            if(!f[i][j+M])continue;
            add(f[i+1][a[i+3]+M+j],f[i][j+M]);
            if(j)add(f[i+1][a[i+3]+M-j],f[i][j+M]);
        }
    }
    int res=0;
    for(int i=-M;i<=M;++i)add(res,f[n-2][i+M]);
    printf("%d",res);
    return 0;
}
```

---

## 作者：Alex_Wei (赞：6)

将操作写成 $01$ 序列，考察两个操作序列 $x, y$ 得到相等序列 $a$ 的充要条件。

找到第一个 $x_i\neq y_i$ 的位置，如果按 $x_1\sim x_{i - 1}$ 操作下来 $a_{i + 1}\neq 0$，那么最终 $x, y$ 对应的 $a_i$ 一定不同，因为第 $i$ 次操作之后 $a_i$ 就不能改变了。可以归纳证明充要条件为对于任意 $x_i\neq y_i$ 的位置，按 $x_1\sim x_{i - 1}$ 操作得到的 $a_{i + 1} = 0$。

在第 $i$ 次操作时，我们只关心 $a_{i + 1}$。设 $f_{i, j}$ 表示第 $i$ 次操作前 $a_{i + 1}$ 的值为 $j$ 的方案数，答案即 $\sum_{j} f_{n, j}$。当 $j = 0$ 时只能按一类操作转移。

$j$ 维的大小可达 $\mathcal{O}(na)$，因此时间复杂度为 $\mathcal{O}(n ^ 2a)$。[代码](https://codeforces.com/contest/1783/submission/188642363)。

---

## 作者：mayike (赞：3)

~~取模不规范，mike 两行泪~~

### [题目传送门](http://codeforces.com/problemset/problem/1783/D)

题意不过多赘述，但这里的 $i$ 操作是改变 $a_i,a_{i+2}$ 的值。

## 思路

总方案在有重情况下是 $2^{n-2}$ 种，那么我们完全可以算重复的情况，再减去即可。而对于每次操作都有加减 $a_{i+1}$ 会衍生出两种新情况，所以重复是当且仅当 $a_{i+1}=0$ 即可，当算到 $i+2$ 时，因为只有一种情况，所以原有的 $2^{n-(i+1)}$ 种情况去重了 $2^{n-(i+2)}$ 种。

那么我们可以定义状态 $f[i][j]$ 表示算到第 $i$ 个数，$a_i$ 经历过**一次操作**后为 $j$ 时的种类数，这里解释一下什么是一次操作：当 $j=i+2$，第 $i$ 次操作时 $a_j$ 会被改变，$a_j$ 此时经过了一次操作，到第 $j$ 次操作时 $a_j$ 又被改变，那是经过了二次操作。

显然第 $i$ 个状态可以由前一个状态转移，当 $j \ne 0$ 时可得：

$$f[i][a[i]+j] = f[i][a[i]+j] + f[i-1][j]$$

$$f[i][a[i]-j] = f[i][a[i]-j] + f[i-1][j]$$

这是个显然的方案状态转移。

当 $j=0$ 时，仅有：

$$f[i][a[i]] = f[i-1][0]$$

此时 $a_{i-1}=0$，那么应用总次数减去出现重复的方案数，即：

$$ans = 2^{n-2} - \sum _ {i=3}^{n} f[i-1][0] \times 2^{n-i}$$

证明正确性：对于 $f[i-1][0]>1$ 是可能的，而此时也只是有多个分支恰汇成了同一结果而已，对于每个分支都会舍弃衍生出的两种情况的一种，那么所有分支线是互不冲突的，$f[i-1][0]=1$ 明显。

对于 $j$ 的范围，结合题目 $0 \le a_i \le 300$ 可知 $-90000 \le j \le 90000$，所以要**防止数组越界**。

**注意取模和快速幂！**

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long mod=998244353;
long long n,a[305],f[305][180005],ans=1;
long long kk(long long x,long long y){
	long long sum=1;
	while(y){
		if(y&1)sum=sum*x%mod;
		x=x*x%mod,y>>=1;
	}return sum;
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n,ans=dsb(2,n-2);
	for(long long i=1;i<=n;i++)cin>>a[i];
	f[2][a[2]+90000]=1;
	for(long long i=3;i<=n;i++)
		for(long long j=-90000;j<=90000;j++)
		    if(f[i-1][j+90000])
		    	if(j==0)ans=(ans-f[i-1][90000]*kk(2,n-i)+mod)%mod,f[i][a[i]+90000]=(f[i][a[i]+90000]+f[i-1][90000])%mod;
		    	else f[i][a[i]+j+90000]=(f[i][a[i]+j+90000]+f[i-1][j+90000])%mod,f[i][a[i]-j+90000]=(f[i][a[i]-j+90000]+f[i-1][j+90000])%mod;
	return cout<<(ans+mod)%mod<<"\n",0;
}
```

---

## 作者：729hao (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1783D)  
似乎还没有我这种思路的题解，~~水一发~~。

### 思路
不考虑重复的情况，每一次操作都应该变出两个数列，所以：
>每次操作后数列数（不包含重复） $=$ 上次操作后数列数（不包含重复）$\times2-$ 重复的数列数

因为第 $i$ 次操作结束后，以后的操作不会再影响 $a_i$ 的值，所以只有当 $a_{i+1}$ 的值 $0$ 时，两种操作结果相同，会出现重复的现象，其它情况不会出现。  
观察下图，图中第 $i$ 排表示的是第 $i$ 次操作后，$a_{i+2}$ 的所有可能的情况（图中的 $a$ 表示刚开始的值）。
![](https://cdn.luogu.com.cn/upload/image_hosting/wu3q26bl.png)  
可以发现，第 $i$ 排的所有数都是 $a_2,a_3,\cdots,a_{i+1}$ 进行加减运算后的结果加上 $a_{i+2}$  的和。  
所以我们在第 $i$ 次操作后，更新 $a_2,a_3,\cdots,a_i$  进行加减后的结果的所有情况，以便于下一次操作的查询。查询时，$-a_i$ 的个数，就是相加之后为 $0$ 的个数。

不过需要注意的是，因为我们会舍掉重复的操作，所以更新前需要将相加的和为 $a_i$ 的数量除以 $2$。  
因为有取模的要求，所以除以 $2$ 可以用[乘法逆元](https://oi-wiki.org//math/number-theory/inverse/)。

### AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int Mod=998244353;
int n,a[305];
int f[305],bsk[180005],ls[180005];
//f[i]表示第i-1次操作结束后的不同数列数
//bsk[j]表示a[2]到a[i+1]进行加减运算后结果为j-90000的个数
int fastpow(int a,int x){//快速幂求乘法逆元 
	if(x==1)return a;
	int ls=fastpow(a,x>>1);
	if(x&1)return ls*ls%Mod*a%Mod;
	else return ls*ls%Mod;
}
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
	}
	int fp=fastpow(2,Mod-2);
	if(a[2]==0){//初始化f[2] 
		bsk[0+90000]++;
		f[2]=1; 
	}
	else{
		bsk[-a[2]+90000]++;
		bsk[a[2]+90000]++;
		f[2]=2;
	}
	for(int i=3;i<n;i++){
		f[i]=(f[i-1]*2-bsk[-a[i]+90000])%Mod;
		f[i]=(f[i]+Mod)%Mod;
		bsk[a[i]+90000]*=fp;
		bsk[a[i]+90000]%=Mod;
		for(int j=-90000;j<=90000;j++){//ls数组表示更新后的bsk 
			ls[j+90000]=0;
			if(j+a[i]<=90000&&j+a[i]>=-90000)ls[j+90000]+=bsk[j+a[i]+90000];
			if(-j+a[i]>=-90000&&-j+a[i]<=90000)ls[j+90000]+=bsk[-j+a[i]+90000];
			ls[j+90000]%=Mod;
		}
		for(int j=0;j<=180000;j++){//赋值回bsk 
			bsk[j]=ls[j];
		}
	}
	printf("%lld",f[n-1]);
	return 0;
}
``

---

## 作者：ktq_cpp (赞：2)

**建议评绿**

这道题有一个性质是较为容易看出来的 —— 在进行第 $i$ 次操作时，只要 $a_{i+1}\neq 0$ 就必定会产生两个新的序列。

用样例一举个例子。

```
4
1 1 1 1
```

我们假设此时在执行第一次操作，可能会产生两个序列。

```
2 1 0 1

0 1 2 1
```

不难看出，不管第二次操作怎么进行，这两个序列所产生的序列必定不同。

此时一个动态规划方程呼之欲出 $dp[i][j]$ 表示到第 $i$ 位时的值为 $j$ 的方案数。很明显 $-90000\le j\le 90000$ 足以通过此题。

```cpp
#include<bits/stdc++.h>
#define int long long
#define repe(i,l,r) for(int (i)=l;(i)<=r;(i)++)
#define rep(i,n) for(int (i)=1;(i)<=n;(i)++)
#define FOR(i,r,l) for(int (i)=r;(i)>=l;(i)--)
#define INF 0x3f3f3f
#define pii pair<int,int>
#define mpr make_pair
#define pb push_back
#define ALL(v) (v).begin(),(v).end()
#define rsort(v) sort(ALL(v),greater<int>())
#define lb(v,x) (int)(lower_bound(ALL(v),x)-v.begin())
#define ub(v,x) (int)(upper_bound(ALL(v),x)-v.begin())
#define uni(v) v.resize(unique(ALL(v))-v.begin())
using namespace std;
int read(){int sum=0,f=1;char c;c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){sum=(sum<<1)+(sum<<3)+(c-'0');c=getchar();}return sum*f;}
void out(int x){if(x<0){x=-x;putchar('-');}if(x>=10)out(x/10);putchar(x%10+'0');}
template <typename T>void die(T s){cout<<s<<endl;exit(0);}
int fast(int a,int b,int P){int res=1;if(P<=0){while(b){if(b&1)res=res*a;a=a*a;b>>=1;}}else{while(b){if(b&1)res=res*a%P;a=a*a%P;b>>=1;}}return res;}
template <typename T>void chkmax(T& a,T b){if(a<b)a=b;return;}
template <typename T>void chkmin(T& a,T b){if(a>b)a=b;return;}
int n;
int a[305];
int dp[305][180005],ans;
const int S=90000,P=998244353;
signed main(){
	n=read();
	rep(i,n)a[i]=read();
	dp[3][a[3]+a[2]+S]=1;
	dp[3][a[3]-a[2]+S]=1;
	repe(i,4,n){
		repe(j,-S,S){
			if(j+a[i]>=-S&&j+a[i]<=S)dp[i][j+a[i]+S]=(dp[i][j+a[i]+S]+dp[i-1][j+S])%P;
			if(j-a[i]>=-S&&j-a[i]<=S&&j!=0)dp[i][j-a[i]+S]=(dp[i][j-a[i]+S]+dp[i-1][j+S])%P;
		}
	}
	repe(j,-S,S){
		ans=(ans+dp[n][j+S])%P;
	}
	out(ans);
	return 0;
}
```


---

## 作者：jasonliujiahua (赞：1)

# CF1783D

[题目传送门](https://www.luogu.com.cn/problem/CF1783D)
## 题意简述：
给你一个有 $n$ 个元素的序列，你需要进行 $n-2$ 次操作。
对于第 $i$ 次操作，你可以选择让 $a_i-a_{i+1}$ 且 $a_{i+2}+a_{i+1}$ 或者可以选择让 $a_i+a_{i+1}$ 且 $a_{i+2}-a_{i+1}$
问最后能产生多少个不同的序列。
## 题目分析：
可以发现一次操作只涉及两三个数，且 $a_i$ 和 $a_{i+1}$ 是知道一个就可以知道另一个。因此考虑 dp，设 $dp_{i,j}$ 表示操作进行到第 $i$ 个数且当前第 $i$ 个位置是 $j$ 的不同序列个数。有转移方程：
$$dp_{i,j}=\begin{cases}
dp_{i-1,j},\ a_i=j\\
dp_{i-1,j-a_i}+dp_{i-1,a_i-j},\ a_i\neq j\\
\end{cases}$$
里面的式子分别对应了题目中的两种操作，具体地可以看做 $a_i$ 与 $a_{i+1}$ 的关系。最终答案是：
$$ans=\sum_{j}dp_{n,j}$$
需要注意一下数组下标不能是负数，因此要进行一下转化（比如加上一个大数）。
## 参考代码：

```c++
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int p=998244353;
const int maxn=310;
int n,m,ans,a[maxn],dp[maxn][maxn*maxn*2];
inline int num(int x)
{
    return x+m*n;
}
void init()
{
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i],m=max(m,a[i]);
}
void DP()
{
    dp[2][num(a[2])]=1;
    for(int i=3;i<=n;i++)
    {
        for(int j=-m*n;j<=m*n;j++)
        {
            int k=j-a[i],w=a[i]-j;
            if(k==0) dp[i][num(j)]=(dp[i][num(j)]+dp[i-1][num(k)])%p;
            else if(k>=-m*n && k<=m*n)
            {
                dp[i][num(j)]=(dp[i][num(j)]+
                dp[i-1][num(k)]+dp[i-1][num(w)])%p;
            }
        }
    }
    for(int j=-m*n;j<=m*n;j++)
        ans=(ans+dp[n][num(j)])%p;
    cout<<ans;
}
signed main()
{
    init();
    DP();
    return 0;
}
```

---

## 作者：yingkeqian9217 (赞：1)

## 前言

[更好的阅读体验](https://www.luogu.com.cn/blog/310639/solution-cf1783d)

## 题目描述

[题目传送门](https://www.luogu.com.cn/problem/CF1783D)

[原题传送门](https://codeforces.com/problemset/problem/1783/D)

## 分析

简单动规。因为操作是有序的，所以我们可以按操作序进行动规。另一方面，这题的值域很小，不难想到使 $dp_{i,j}$ 表示操作到第 $i$ 位时末位数为 $j$ 的方案个数。

这么做有什么好处呢？我们想，因为操作是从左往右的，所以一次操作对于左边的改变对于后面的操作没有影响，仅对方案数有所影响。所以这么做是合理的。

和上面说的一样，既然指考虑上一位的影响，那我们就枚举上一位的值 $dp_{i-1,j}$。而进行一次增操作，就是使 $dp_{i,a_i+j}+dp_{i-1,j}\to dp_{i,a_i+j}$；减操作就是 $dp_{i,a_i-j}+dp_{i-1,j}\to dp_{i,a_i-j}$。

还有一种特殊情况，那就是 $j=0$ 时，很显然，增减操作都一样，所以不用第二次计算了。

最后，为了~~装逼~~优化空间，我选择了使用滚动数组来进行动规。

## AC CODE

```cpp
#include<bits/stdc++.h>
#define nop !op
using namespace std;
const int Mod=998244353;
const int Num=1000;//值域
int n,a[Num],f[Num+Num][2],op,ans;
signed main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	f[a[2]+Num][0]=1;//初始值，不难理解
	for(int i=3;i<=n;i++){
		for(int j=-Num;j<=Num;j++) f[j+Num][nop]=0;//滚动数组记得清零
		for(int j=-Num;j<=Num;j++){
			f[a[i]-j+Num][nop]=(f[a[i]-j+Num][nop]+f[j+Num][op])%Mod;
			if(j) f[a[i]+j+Num][nop]=(f[a[i]+j+Num][nop]+f[j+Num][op])%Mod;
		}
		op=nop;
	}
	for(int j=-Num;j<=Num;j++) ans=(ans+f[j+Num][op])%Mod;//统计所有情况
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：EBeason (赞：1)

### 思路
首先需要得到一个性质，每次进行操作一和操作二都会使得数组从一个变成两个，除非当前这一位为`0`。  
然后观察到每次操作最多会使右面一位增大或减小`300`，所以我们暴力枚举所有的情况，对于不为`0`的递推到后面两种情况，否则递推到后面一种情况。  
复杂度为 $\mathcal{O}(N^3)$。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define int ll
const int MaxN=1e6+100;
const int INF=1e9;
int T,N,M,a[MaxN],P=998244353;
int F[301][301*301*2];
template<class T>
inline void qread(T &sum)
{
	sum=0;int boo=1;
	char x=getchar();
	while(x<'0'||x>'9'){if(x=='-')boo=-1;x=getchar();}
	while(x>='0'&&x<='9'){sum=(sum<<1)+(sum<<3)+x-'0';x=getchar();}
	sum*=boo;
}
template<class T>
void qput(T x)
{
	if(x<0) {x=-x;putchar('-');}
	if(x>9) qput(x/10);
	putchar(x%10+48);
}
inline void Solve()
{
	cin>>N;
	for(int i=1;i<=N;i++)
	{
		cin>>a[i];
	}
	int ts=300*300;
	F[2][a[2]+ts]=1;
//	cout<<F[2][2+ts]<<endl;
	int ans=0;
	for(int i=2;i<N;i++)
	{
//		cout<<F[2][2+ts]<<endl;
		for(int j=1;j<=300*300*2;j++)
		{
			if(F[i][j]&&j!=ts)
			{ 
				F[i+1][j+a[i+1]]+=F[i][j];
				F[i+1][j+a[i+1]]%=P;
				F[i+1][a[i+1]-j+2*ts]+=F[i][j];
				F[i+1][a[i+1]-j+2*ts]%=P;
			}
			else if(j==ts)
			{
				F[i+1][a[i+1]+ts]+=F[i][j];
				F[i+1][a[i+1]+ts]%=P;
			}	
		}
		
	}
//	cout<<ans<<endl;
	for(int j=1;j<=300*300*2;j++)
	ans+=F[N][j],ans%=P;
	cout<<ans<<endl;
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	T=1;
	while(T--) Solve();
}
```

---

## 作者：honglan0301 (赞：1)

## 题意简述

给定长度为 $n\ (n\leq300)$ 的数列 $a\ (a_i\leq300)$, 你需要依次对它进行 $n-2$ 次操作。在第 $i$ 次操作中，你需要令 $a_i\leftarrow a_i+a_{i+1},a_{i+2}\leftarrow a_{i+2}-a_{i+1}$ 或 $a_i\leftarrow a_i-a_{i+1},a_{i+2}\leftarrow a_{i+2}+a_{i+1}$。 求在所有操作后它能变成多少种不同的数列。

## 题目分析

数数题，手动操作一下之后想到 dp。令 $f(i,j)$ 表示正在进行第 $i-1$ 个操作，此时的 $a_i$ 为 $j$ 时能让后面的数变成多少种不同的数列。那么有 $f(i,j)=f(i+1,a_{i+1}+j)+[j\neq0]\cdot f(i+1,a_{i+1}-j)$, $f(n,j)=1$, $f(2,a[2])$ 即为答案。

## 代码

```cpp
#include <iostream>
using namespace std;
#define mod 998244353
#define B 90001

int n,a[305],dp[305][180005];

int dfs(int num,int now)
{
	if(num==n) return 1;
	if(dp[num][now+B]) return dp[num][now+B];
	if(now==0) return dp[num][now+B]=dfs(num+1,a[num+1]);
	else return dp[num][now+B]=(dfs(num+1,a[num+1]+now)+dfs(num+1,a[num+1]-now))%mod;
}

signed main()
{
	cin>>n; for(int i=1;i<=n;i++) cin>>a[i];
	cout<<dfs(2,a[2])<<endl;
}
```


---

## 作者：small_lemon_qwq (赞：0)

考虑最后一次操作，如果 $a_{n-1}\neq0$，那么一定可以得到两种不同的答案，否则只能得到一种。

设 $f_i$ 为前 $i$ 个数操作 $i-2$ 次的答案，$i\ge 2$。

所以可以得到转移方程 $f_i=2\times f_{i-1}-g_{i-1}$，其中 $g_i$ 表示前 $i$ 个数操作 $i-2$ 次后第 $i$ 个数恰好为 $0$ 的方案数，不好直接求，考虑令 $g_{i,j}$ 表示第 $i$ 个数恰好为 $j$ 的方案数的个数，而值域又很小，所以可以直接 dp 求出。

时间复杂度：$\operatorname{O}(n^2\times V)$，$V$ 是 $a_i$ 的值域，$n\times V$ 是每个数操作之后的值域。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,a[305],f[305];
constexpr int mod=998244353;
int g[200005],g2[200005];
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	g[a[2]+90000]=1;
	f[2]=1;
	for(int i=3;i<=n-1;i++){
		memcpy(g2,g,sizeof(g));
		memset(g,0,sizeof(g));
		for(int j=-i*300;j<=i*300;j++){
			if(j!=a[i])g[j+90000]=(g2[j-a[i]+90000]+g2[a[i]-j+90000])%mod;
			else g[j+90000]=g2[j-a[i]+90000];
		}
		f[i]=(f[i-1]*2-g2[90000])%mod;
	}
	f[n]=(f[n-1]*2-g[90000])%mod;
	cout<<(f[n]+mod)%mod;
	return 0;
}
```

---

## 作者：wth2026 (赞：0)

# 题目大意
一个有 $n$ 个元素的序列，你需要进行 $n-2$ 次操作。

第 $i$ 次操作，你可以选择让 $a_i-a_{i+1}$、$a_{i+2}+a_{i+1}$ 或者让 $a_i+a_{i+1}$、$a_{i+2}-a_{i+1}$

输出最后能产生多少个不同的序列。
# 题目思路
用动态规划解决。

定义 $f_{i,j}$ 表示当前操作到第 $i$ 个点，并且那个点的大小是 $j-90000$。

当先枚举 $i,j$，如果 $j\ne 90000$，即原数不为 $0$ 时，有：
$$f_{i+1,j+a_{i+3}}\gets f_{i+1,j+a_{i+3}}+f_{i,j}$$
$$f_{i+1,j-a_{i+3}}\gets f_{i+1,j-a_{i+3}}+f_{i,j}$$

否则，就有：
$$f_{i+1,j+a_{i+3}}\gets f_{i+1,j+a_{i+3}}+f_{i,j}$$
# AC Code
```cpp
#include <bits/stdc++.h>

#define endl '\n'
#define int long long
#define inf 998244353

#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Os")
#pragma GCC optimize("Ofast")

using namespace std;

int n, a[305], f[305][180005], m, ans;

void init() {
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	init();
	
	cin >> n;
	
	for (int i = 1; i <= n; ++ i) {
		cin >> a[i];
	}
	
	f[0][a[2] + 90000] = 1;
	
	for (int i = 0; i <= n - 3; ++ i) {
		for (int j = 0; j <= 180000; ++ j) {
			if (f[i][j] == 0) {
				continue;
			}
			
			if (j == 90000) {
				f[i + 1][j + a[i + 3]] += f[i][j];
				f[i + 1][j + a[i + 3]] %= inf;
			} else {
				f[i + 1][j + a[i + 3]] += f[i][j];
				f[i + 1][j + a[i + 3]] %= inf;
				f[i + 1][j - a[i + 3]] += f[i][j];
				f[i + 1][j - a[i + 3]] %= inf;
			}
		}
	}
	
	for (int i = 0; i <= 180000; ++ i) {
		ans += f[n - 2][i];
	}
	
	cout << ans % inf;
	return 0;
}
```

---

## 作者：Xiphi (赞：0)

这个问题的一个关键观察点是，在第一次 $i$ 操作后，数组的前 $i$ 个元素是固定的，之后就无法更改了。此外，在进行 $i$ 次操作后， $i+3$ 至 $n$ 位置上的元素与操作前相同。

所以，设 $dp_{i, x}$ 表示进行了 $i$ 次操作，第 $i+2$ 个元素是 $x$，数组可以有多少个不同的前缀 。 $i+2$ 之后的元素与原数组中的元素相同， 所以我们只对这个元素感兴趣。

让我们来分析一下 dp 中的转换。我们将操作 $i+1$ 应用于元素 $a_{i+1}$ 、 $a_{i+2}$ 和 $a_{i+3}$ 。如果我们将 $a_{i+2}$ 加到 $a_{i+1}$ 中，然后再从 $a_{i+3}$ 中减去，那么我们就会过渡到状态 $dp_{i+1, a_{i+3}-y}$ 。否则，我们过渡到状态 $dp_{i+1, a_{i+3}+y}$ 。特别的，如果 $y=0$ ，我们只需要进行其中一个转换，因为添加或减去 $0$ 实际上没有任何区别。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int p=300*300;//偏移量
const int mod=998244353;
int a[305],n,dp[305][5+2*300*300];//第 i 个操作,第 i+2 位=j.
int main(){
//	freopen("test.in","r",stdin);
//	freopen("test.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
	cin>>n;
	for(auto i=1;i<=n;++i){
		cin>>a[i];
	}
	dp[0][a[2]+p]=1;//初始化，什么都不操作显然只有一种情况
	for(int i=0;i<=n-3;++i){
		for(int j=-p;j<=p;++j){
			dp[i+1][a[i+3]-j+p]+=dp[i][j+p];
			dp[i+1][a[i+3]-j+p]%=mod;
			if(j!=0) dp[i+1][a[i+3]+j+p]+=dp[i][j+p],
					 dp[i+1][a[i+3]+j+p]%=mod;
		}
	}
	int ans=0;
	for(int j=-p;j<=p;++j){
		ans+=dp[n-2][j+p];ans%=mod;
	}
	cout<<ans;
	return 0;
}




```

---

## 作者：DaiRuiChen007 (赞：0)

# CF1783D 题解



## 思路分析

先考虑什么时候两个不同的操作序列 $X,Y$ 能够得到相同的 $a$。

假设 $j$ 是第一个 $x_j\ne y_j$ 的位置，那么此时 $X,Y$ 对应的序列中 $a_j$ 分别变成 $a_j-a_{j+1}$ 和 $a_j+a_{j+1}$，又因为往后的操作不会改变 $a_j$ 的值，因此只有可能在 $a_{j+1}=0$ 时会产生重复。

因此我们考虑 $dp_{i,x}$ 表示进行了第 $i$ 次操作前，$a_{i+1}=x$ 的方案数，得到如下转移：
$$
dp_{i+1,a_{i+1}+x}\gets dp_{i,x}\\
dp_{i+1,a_{i+1}-x}\gets dp_{i,x} 
$$
$x=0$ 的时候产生的两个转移是重复的，只需要去掉其中一条转移即可，最终答案为 $\sum_x dp_{n-1,x}$。

设 $w$ 为 $\{a_i\}$ 的值域，那么最终 $x$ 的值域为 $nw$，朴素转移即可。

时间复杂度 $\Theta(n^2w)$。

## 代码呈现

```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
using namespace std;
const int MAXN=301,W=1e5+1,MOD=998244353;
int a[MAXN],dp[MAXN][W<<1];
//a[i+1]=j after process (i-1,i,i+1)
signed main() {
	int n,ans=0;
	scanf("%lld",&n);
	for(int i=1;i<=n;++i) scanf("%lld",&a[i]);
	dp[1][a[2]+W]=1;
	for(int i=2;i<n;++i) {
		for(int x=-W;x<W;++x) {
			dp[i][a[i+1]+x+W]=(dp[i][a[i+1]+x+W]+dp[i-1][x+W])%MOD;
			if(x!=0) dp[i][a[i+1]-x+W]=(dp[i][a[i+1]-x+W]+dp[i-1][x+W])%MOD;
		}
	}
	for(int x=0;x<2*W;++x) ans=(ans+dp[n-1][x])%MOD;
	printf("%lld\n",ans);
	return 0;
}
```

---

