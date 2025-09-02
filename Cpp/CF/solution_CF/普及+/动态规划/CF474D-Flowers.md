# Flowers

## 题目描述

We saw the little game Marmot made for Mole's lunch. Now it's Marmot's dinner time and, as we all know, Marmot eats flowers. At every dinner he eats some red and white flowers. Therefore a dinner can be represented as a sequence of several flowers, some of them white and some of them red.

But, for a dinner to be tasty, there is a rule: Marmot wants to eat white flowers only in groups of size $ k $ .

Now Marmot wonders in how many ways he can eat between $ a $ and $ b $ flowers. As the number of ways could be very large, print it modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 说明/提示

- For $ K $ = $ 2 $ and length $ 1 $ Marmot can eat ( $ R $ ).
- For $ K $ = $ 2 $ and length $ 2 $ Marmot can eat ( $ RR $ ) and ( $ WW $ ).
- For $ K $ = $ 2 $ and length $ 3 $ Marmot can eat ( $ RRR $ ), ( $ RWW $ ) and ( $ WWR $ ).
- For $ K $ = $ 2 $ and length $ 4 $ Marmot can eat, for example, ( $ WWWW $ ) or ( $ RWWR $ ), but for example he can't eat ( $ WWWR $ ).

## 样例 #1

### 输入

```
3 2
1 3
2 3
4 4
```

### 输出

```
6
5
5
```

# 题解

## 作者：Tenshi (赞：15)

# 关键点：dp


### 分析：
看到题面 “当蛋糕数量为x1到x2之间” 的描述，不难想到可以用前缀和刻画这一点，如下

```cpp
int sum(int l,int r){
    return (s[r]-s[l-1]+mod)%mod;
}
```

**接下来考虑蛋糕数量为x的时候有多少种吃法：**

我们这样考察：x个蛋糕，如果采取办法1吃，那么会剩下x-1个蛋糕，采取方法2则会剩下x-k （这里x>=k，写代码时注意判断）个蛋糕。

记f(x)为吃x个蛋糕的方法数，我们有：

f(x)=f(x-1)+f(x-k) (x>=k)

这，便是dp题的核心：状态转移方程

核心代码如下，我们从x=1开始依次更新：

```cpp
for(i=1;i<=maxn;i++){
        if(i>=k) f[i]=f[i-1]+f[i-k];
        else f[i]=f[i-1];
    }
```

其他补充：

记得初始化x=0的情况 f[0]=1

取模

结合前缀和处理


顺利AC~

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define mod 1000000007 
#define maxn 100001
ll t,k,i;
ll f[maxn];
ll s[maxn];
int sum(int l,int r){
    return (s[r]-s[l-1]+mod)%mod;
}
int main(){
    cin>>t>>k;
    f[0]=s[0]=1;
    f[1]=1;
    for(i=1;i<=maxn;i++){
        if(i>=k) f[i]=(f[i-1]+f[i-k])%mod;
        else f[i]=f[i-1]%mod;
        s[i]=(s[i-1]+f[i])%mod;
    }
    while (t--)
    {
        int l,r;
        cin>>l>>r;
        cout<<(sum(l,r)+mod)%mod<<endl;
    }
    
    return 0;
}
```


---

## 作者：LRL65 (赞：4)

## 算法：DP+前缀和（较为简单）

那道题一看就会发现这是一道dp，那么 $f_i$ 应为**吃 $i$ 个蛋糕一共的吃法**。

**那么状态转移方程应为：$f_i=f_{i-1}+f_{i-k}$**

但是最后要求的是某一区间里吃法的和，所以要用**前缀和**，最后输出 $sum_{b}-sum_{a-1}$ 即可。

注意点：
1. 要开long long
1. 需要 mod 1000000007
1. 在最后输出时，输出本应为$sum_{b}-sum_{a-1}$，可是 $sum_{b}$ 和 $sum_{a-1}$ 因为已经在前面 mod 了1000000007，所以 $sum_{b}$ 可能小于 $sum_{a-1}$ ，此时再减就会成为负数，**所以还要加上 1000000007**，最后再 mod。
1. **$f$ 数组初始化应为 $f_0$=1**

上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define PF 1000000007
#define MAXN 100005
long long n,k,f[MAXN]={0},s[MAXN]={0},a,b; //long long
int main(){
    cin>>n>>k;
    f[0]=1;//初始化
    for(int i=1;i<=MAXN;i++) { //dp
        f[i]+=f[i-1]%PF;
        if(i>=k)f[i]+=f[i-k]%PF;
        s[i]=(s[i-1]+f[i])%PF; //前缀和
    }
    for(int i=1;i<=n;i++) {
        cin>>a>>b;
        cout<<(s[b]-s[a-1]+PF)%PF<<endl; //输出
    }
}
```



---

## 作者：Fool_Fish (赞：1)

是一道比较裸的 DP ,不过查询的方法是比较新的

首先设 $dp_i$ 为吃 $i$ 个蛋糕一共的吃法。

那么，状态转移方程就应该是$dp_i=dp_{i-1}+dp_{i-k}$

$dp_0=1$

求一个区间内的总吃法，很容易想到使用前缀和去优化

然后就是有几点需要注意的

- 本题是有取模操作的，而前缀和又涉及到减法，这两个一起时要注意如果减成负数，要加回来

- 本题的模数比较大，如果对自己的取模运算设计没有把握的可以开个 ```long long``` 保险

code:

```cpp
#include<cstdio>
#include<iostream>
using namespace std;
#define int long long 
const int MAXN=100005;
const int MOD=1000000007;
long long dp[MAXN];
long long sum[MAXN];
signed main(){
	int n,k;
	scanf("%lld %lld",&n,&k);
	dp[0]=1;
	for(int i=1;i<=MAXN;i++){
		dp[i]=dp[i-1]%MOD;
		if(i>=k){
			dp[i]+=dp[i-k];
			dp[i]%=MOD;
		}
	}
	for(int i=1;i<=MAXN;i++){
		sum[i]=sum[i-1]+dp[i];
		sum[i]%=MOD;
	}
	for(int i=1;i<=n;i++){
		int a,b;
		scanf("%lld %lld",&a,&b);
		printf("%lld\n",(sum[b]-sum[a-1]+MOD)%MOD);
	}
return 0;
} 
```

---

## 作者：江户川·萝卜 (赞：1)

先在此给出 $t,k$ 的数据范围 $t,k\le10^5$。

---

一眼DP。

如果你需要求吃 $i$ 个蛋糕有几种方案数：
- 你可以先吃一个蛋糕，再吃 $i-1$ 个蛋糕。此时方案数即为吃 $i-1$ 个蛋糕的方案数。
- 也可以吃 $k$ 个蛋糕 $(i\ge k)$，再吃 $i-k$ 个蛋糕，此时方案数即为吃 $i-k$ 个蛋糕的个数。

即可列出转移方程：`dp[i]=dp[i-1]+(i<k?0:dp[i-k])`

对其中`(i<k?0:dp[i-k])`作出解释：若`i<k`，则加`0`,反之加`dp[i-k]`。

最后前缀和一下，对于每一对 $(x_1,x_2)$ 输出 `s[x2]-s[x1-1]`。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const long long mod=1e9+7;
const int maxn=1e5+5;
int t,k;
long long dp[maxn],s[maxn];
int main(){
	scanf("%d%d",&t,&k);
	dp[0]=1,s[0]=1;
	for(int i=1;i<maxn;i++) dp[i]=(dp[i-1]+(i<k?0:dp[i-k]))%mod,s[i]=(s[i-1]+dp[i])%mod;
	while(t--){
		int l,r;
		scanf("%d%d",&l,&r);
		printf("%lld\n",(s[r]-s[l-1]+mod)%mod);
	}
	return 0;
}
```

---

## 作者：Zhou_Wingay (赞：1)

###  非常简单的一道DP题，如果做不出来可以先做它的减弱板P1255数楼梯。

若$f[i]$表示吃$i$个蛋糕共有吃法的数目。

很明显一次能吃1或k个，所以，转移方程为：  $f[i]=f[i-1]+f[i-k]$ 。

然后就是一些要注意的地方了：

 1. 因为求的是区间，所以要用前缀和。
 
 2. 要开long long。

 3. 别忘了取模。

最后就是代码了：
~~~cpp
#include<bits/stdc++.h>
using namespace std;
long long a[100005]={1},s[100005];
int main(){
	long long n,k,i,j;
	cin>>n>>k;
	for(i=1;i<=100005;i++){
		a[i]=(a[i]+a[i-1])%1000000007;
		if(i>=k) a[i]=(a[i]+a[i-k])%1000000007;
      //状态转移方程
		s[i]=(s[i-1]+a[i])%1000000007;
      //前缀和
	}
	for(i=1;i<=n;i++){
		long long x,y;
		cin>>x>>y;
		cout<<(s[y]-s[x-1]+1000000007)%1000000007<<endl;
      //因为s[x]和s[y]都已取模，所以要先加上1000000007。
	}
	return 0;
}
~~~

---

## 作者：零殇 (赞：1)

### 一道很简单的前缀和+dp

一次只能吃$1$或$k$个，推得状态转移方程为$f[i]=f[i-1]+f[i-k]$

由于最后求的是x1-x2这个区间的和，所以再用前缀和来储存

因此$sum[i]=(sum[i-1]+f[i])%1000000007$

而我们所要的答案便是$sum[x2]-sum[x1-1]$

上代码：
```
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
long long f[100000],sum[100000];//用f来储存方案数，sum来储存前缀和 
int main()
{
	int n,k,x1,x2;
	cin>>n>>k;
	for(int i=0;i<k;i++)
	{
		f[i]=1;//将每个小于k的方案数都初始化为0 
	}
	for(int i=k;i<=100000;i++)
	{
		f[i]=(f[i-1]+f[i-k])%1000000007;//一边加一边mod，防止最后溢出	
	}
	for(int i=1;i<=100000;i++)
		sum[i]=(sum[i-1]+f[i])%1000000007;//同上 
	for(int i=1;i<=n;i++)
	{
		cin>>x1>>x2;
		cout<<(sum[x2]-sum[x1-1]+1000000007)%1000000007<<endl;
     		//因为我们已经提前mod，所以可能会出现sum[x2]<sum[x-1]的情况，故加上1000000007 
	}
	return 0;
}
```

完结撒花~


---

## 作者：ModestCoder_ (赞：1)

dp水题，切掉的那种

$dp_i=dp_{i-1}+dp_{i-k}$

再用前缀和统计一下$sum_i=\sum_{j=1}^{i}dp_j$

对于每个询问$[l,r]$答案便是$sum_r-sum_{l-1}$

Code：

```cpp
#include <bits/stdc++.h>
#define maxn 100010
#define LL long long
using namespace std;
const LL qy = 1000000007;
int n, k;
LL dp[maxn], sum[maxn];

inline int read(){
	int s = 0, w = 1;
	char c = getchar();
	for (; !isdigit(c); c = getchar()) if (c == '-') w = -1;
	for (; isdigit(c); c = getchar()) s = (s << 1) + (s << 3) + (c ^ 48);
	return s * w;
}

int main(){
	n = read(), k = read();
	dp[0] = 1;
	for (int i = 1; i <= maxn - 1; ++i){
		dp[i] = dp[i - 1];
		if (i >= k) if ((dp[i] += dp[i - k]) >= qy)  dp[i] -= qy;
	}
	for (int i = 1; i <= maxn - 1; ++i) sum[i] = (sum[i - 1] + dp[i]) % qy;
	while (n--){
		int l = read(), r = read();
		printf("%lld\n", (sum[r] - sum[l - 1] + qy) % qy);
	}
	return 0;
}
```


---

## 作者：Haphyxlos (赞：0)

# CF474D 【Flowers】
## 萌新的第三篇题解

[题目传送门](https://www.luogu.com.cn/problem/CF474D)

本题是一道较为简单的dp。

设dp数组存储吃i个蛋糕的吃法，来推一下转移方程。

推导：

对于吃法一 dp[i]+=dp[i-1]

对于吃法二 if(i>=k)dp[i]+=dp[i-k]

所以，本题我们可以先预处理出 **i≤1e5** 的方案数。

然后呢，题目说要查询当蛋糕数量在x1和x2之间的方案数，为此，我们可以利用前缀和来算出这个区间内的方案数，而前缀和也同样可以在预处理的同时解决。

l~r的区间和公式：**s[r]-s[l-1]**

然后对于n组询问，每次都输出区间和就好了？

显然并不是，本题需要我们对**1e9+7**进行取模，**如果s[r]在取模后，小于s[l-1]，那么会输出负数**，显然不符合题意。所以我们可以在对它们的差加上**1e9+7**，这样，就能轻松AC本题啦！

本题的code：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=1e9+7;
const double eps=1e7-8;
const int INF=0x3f3f3f3f;
const int maxn=1e5+5;
const int maxm=1e6+5;
ll n,k,dp[maxn]={1},s[maxn];
inline ll read();
int main(int argc, char const *argv[]){
	n=read(),k=read();
	for(int i=1;i<maxn;++i){
		dp[i]=(dp[i]+dp[i-1])%mod;
		if(i>=k)dp[i]=(dp[i]+dp[i-k])%mod;
		s[i]=(s[i-1]+dp[i])%mod;
	}
	while(n--){
		ll l=read(),r=read();
		printf("%lld\n",(s[r]-s[l-1]+mod)%mod);
	}
	return 0;
}
inline ll read(){
	ll x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return x*f;
}
```

本篇题解就到此结束了，如果喜欢，还请点个赞吧。

---

## 作者：Plozia (赞：0)

[博客阅读效果更佳](https://blog.csdn.net/BWzhuzehao/article/details/108730323)

这道题题意简单明了，很明显 Marmot 只有两种吃法：

- 一次吃 1 个
- 一次吃 $k$ 个

因此，这道题是一道序列性动态规划。

到这里，我们有两种方法：记忆化搜索与动态规划。

这两种方法的计算式子是一样的：令 $f_i$ 表示吃 $i$ 块蛋糕所用的方案数，则： $f_i=f_{i-1}+f_{i-k}$ ，从吃 1 块（ $f_{i-1}$ ）转移与吃 $k$ 块（ $f_{i-k}$ ）转移即可。

初始化： $1 \leq i < k$ 时，$f_i=1$ ，且 $f_2=k$

计算出 $f_i$ 后，直接前缀和求解即可。

 DP 代码（本人只写了 DP ，如果各位读者有兴趣可以写一下记忆化搜索的代码）：
 
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e5+10;
const int P=1000000007;
long long f[MAXN+10];
long long sum[MAXN+10];
int t,k;
int main()
{
	scanf("%d %d",&t,&k);
	for(int i=1;i<k;i++) f[i]=1;
	f[k]=2;
	for(int i=k+1;i<=MAXN;i++) f[i]=(f[i-1]+f[i-k])%P;
	for(int i=1;i<=MAXN;i++) sum[i]=(sum[i-1]+f[i])%P;
	while(t--)
	{
		int a,b;
		scanf("%d %d",&a,&b);
		printf("%lld\n",(sum[b]-sum[a-1]+P)%P);
	}
	return 0;
}
```

---

## 作者：SpXace (赞：0)

一道入门DP

设f[i]表示到 i 个蛋糕的方案数

由题可知f[i] 可以由 f[i - 1] （只吃1 个）,f[i - k]（i - k > 0,吃k个）转移过来

然后用sum前缀和维护一下，就可以O(1)的回答询问了

```
/*
time:2018年9月18日21:34:27 
Author:飞马の幻想
place:lzyz
type:计数DP 
from:https://www.luogu.org/problemnew/show/CF474D
input:
3 2
1 3
2 3
4 4

output:
6
5
5

*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define LL long long
#define rep(i, a, b) for(int i = a; i <= b; ++i)
#define per(i, a, b) for(int i = a; i >= b; --i)
#define clr(a,b)  memset((a),b,sizeof(a))
using namespace std;
inline int Read(){
	int s = 0, w = 1; char ch = getchar();
	while(ch < '0' || ch > '9')   { if(ch == '-') w = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') { s = (s << 3) + (s << 1) + (ch ^ 48); ch = getchar(); }
	return s * w;
}
const int MX = 100011;
const int Mod = 1e9 + 7;
int N,k;
LL f[MX],sum[MX]; 
void init() {
	N = Read(), k = Read();
}
void solve() {
	f[0] = 1;
	rep(i, 1, 100001) {
		f[i] = f[i - 1];
		if(i >= k) f[i] = (f[i] + f[i - k]) % Mod;
		sum[i] = (sum[i - 1] + f[i]) % Mod;
	}
	while(N--) {
		int l = Read(), r = Read();
		printf("%lld\n", (sum[r] - sum[l - 1] + Mod) % Mod);
	}
}
int main() {
	init();
	solve();
	return 0;
}

```

---

## 作者：noble_ (赞：0)


[我的博客，欢迎光临](http://www.cnblogs.com/noblex/)

简单dp。

用dp[i]表示i个蛋糕的吃的方法数量

$ dp[i]=dp[i-k]+dp[i-1] $

最后搞一个前缀和求一下范围内的dp值的和

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=2e5;
const ll MOD=1e9+7;
ll dp[maxn], sum[maxn];
int main(){
	int t, k; cin>>t>>k;
	dp[0]=1;
	for(int i=1;i<=1e5+10;i++){
		if(i>=k) dp[i]+=dp[i-k];
		dp[i]+=dp[i-1];
		dp[i]%=MOD;
	}

	for(int i=1;i<=1e5+10;i++){
		sum[i]=(sum[i-1]+dp[i])%MOD;
	}
	while(t--){
		int a,b; cin>>a>>b;
		if(b<a) swap(a,b);
		cout<<(sum[b]-sum[a-1]+MOD)%MOD<<endl;
	}
	return 0;
}
```

---

