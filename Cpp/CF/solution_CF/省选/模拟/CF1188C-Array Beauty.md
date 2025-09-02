# Array Beauty

## 题目描述

我们定义一个数组 $b_1, b_2, \ldots, b_n$（$n > 1$）的美丽值为 $ \min\limits_{1 \leq i < j \leq n} |b_i - b_j| $。

现在给定一个数组 $a_1, a_2, \ldots, a_n$ 和一个整数 $k$，请计算该数组所有长度恰好为 $k$ 的子序列的美丽值之和。由于答案可能非常大，请输出其对 $998244353$ 取模的结果。

一个序列 $a$ 是数组 $b$ 的子序列，当且仅当 $a$ 可以通过从 $b$ 中删除若干（可能为零或全部）元素得到。

## 说明/提示

在第一个样例中，共有 $4$ 个长度为 $3$ 的子序列——$[1, 7, 3]$、$[1, 3, 5]$、$[7, 3, 5]$、$[1, 7, 5]$，每个子序列的美丽值均为 $2$，因此答案为 $8$。

在第二个样例中，只有一个长度为 $5$ 的子序列，即整个数组，其美丽值为 $|10-1| = 9$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4 3
1 7 3 5
```

### 输出

```
8```

## 样例 #2

### 输入

```
5 5
1 10 100 1000 10000
```

### 输出

```
9```

# 题解

## 作者：wucstdio (赞：26)

先把$a$数组排序，不会影响答案。

我们发现，答案最多不会超过$\dfrac{\max a_i}{k-1}$，因为$k$个数有$k-1$个空格。

然后我们考虑先枚举答案$v$，接下来问题就是计算有多少个集合的答案是$v$。

直接计算有点难，我们可以考虑有多少个集合的答案大于等于$v$，最后做一个差分就行了。

我们设$f_{i,j}$表示从前$i$个数中选择$j$个数，并且第$i$个数被选中的方案数。

枚举上一个数选的是什么，得到转移方程：

$$f_{i,j}=\sum_{a_j-a_k\ge v}f_{k,j-1}$$

直接转移是$O(n^2k)$的，注意到后面的可以前缀和优化后双指针，所以这一部分的复杂度可以降到$O(nk)$。

所以总时间复杂度是$O\left(\dfrac vk \cdot nk\right)=O(nv)$，可以通过本题。

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#define ll long long
using namespace std;
const ll MOD=998244353;
int n,k,a[1005];
ll f[1005][1005],res[100005],ans,s[1005][1005];
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	a[0]=-1000000000;
	for(int v=1;v*(k-1)<=a[n];v++)
	{
		f[0][0]=1;
		int now=0;
		s[0][0]=1;
		for(int i=1;i<=n;i++)
		{
			while(a[now]<=a[i]-v)now++;
			for(int j=0;j<=k;j++)
			{
				if(j)f[i][j]=s[now-1][j-1];
				s[i][j]=(s[i-1][j]+f[i][j])%MOD;
			}
			res[v]+=f[i][k];
		}
		ans+=res[v]%MOD;
	}
	printf("%I64d\n",ans%MOD);
	return 0;
}
```

---

## 作者：jianhe (赞：4)

**upd**：修改了一处笔误。

### 前言：
记录一下这个经典 trick。
### 思路：
#### 观察 1：
**hint 1**：先看数据范围，$0 \le a_i \le 10^5$ 似乎暗示了什么。

于是想到枚举所有可能的 **子序列的美丽值**，然后计算贡献。

可能的 **子序列的美丽值** 并不大，最大为 $\frac{\max{a_i} - \min{a_i}}{k-1}$。

简单证明：考虑贪心（不考虑原序列具体的值，只看 $\min{a_i}$ 和 $\max{a_i}$），要使每一个间隔都 $\ge x$。而总的值域是固定不变的（$[\min{a_i},\max{a_i}]$），所以每个间隔都要尽量均匀地分，即最大为 $\frac{\max{a_i} - \min{a_i}}{k-1}$。
#### 观察 2：
**hint 2**：这么乱的 $a$ 数组，贡献怎么算啊？

于是想到给 $a$ 先排序。

为什么是对的呢？要算的是 **子序列**，首先排完序后一定能取到这个子序列（只不过不按照原先的顺序）。然后发现一个序列打乱后的美丽值是不变的。
#### 观察 3：
**hint 3**：直接算美丽值刚好为 $x$ 的序列个数好像比较麻烦，那我应该怎么办呢？

那就求美丽值 $\ge x$ 的序列个数！减去美丽值 $\ge x+1$ 的序列个数就是美丽值刚好为 $x$ 的序列个数！

于是就豁然开朗了。

设 $dp_{i,j}$ 表示前 $i$ 个数，必须选 $a_i$，已经选了 $j$ 个的方案数。

那么得到转移方程 $dp_{i,j}=\sum\limits_{a_{i}-a_{lst} \ge x}{dp_{lst,j-1}}$。

由于 $a$ 是排过序的，所以 $lst$ 的上界只会往右移，也就是单调的，所以维护一个指针表示当前能取到的最大的 $lst$ 以及前缀和即可。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=1010,mod=998244353;
ll n,k,lst,now,ans,a[N],dp[N][N],q[N][N];
ll work(ll x,ll top=1,ll res=0){
    dp[0][0]=q[0][0]=1;
    for(int i=1;i<=n;i++){
        while(top<i&&a[i]-a[top]>=x) top++;// 移动指针
        q[i][0]=q[i-1][0];// 前缀和优化
        for(int j=1;j<=k;j++) q[i][j]=(q[i-1][j]+(dp[i][j]=q[top-1][j-1]))%mod;
        (res+=dp[i][k])%=mod;
    }
    return res;
}
int main(){
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    cin>>n>>k;for(int i=1;i<=n;i++) cin>>a[i];sort(a+1,a+n+1);
    for(int i=(a[n]-a[1])/(k-1);i;i--) (ans+=i*((now=work(i))-lst))%=mod,lst=now;
    cout<<(ans+mod)%mod;// 减完可能有负数
    return 0;
}
```

---

## 作者：yuzhechuan (赞：4)

不错的（套路）数数dp

---

### 题解：

首先观察性质，发现由于要对所有长度$k$子序列求和，所以从小到大排序答案不变

继续观察性质，发现任意选出一个长度$k$子序列，答案不会超过$\lfloor \frac{\max a_i-\min a_i}{k-1} \rfloor$，因为贪心地平均分给$k-1$个间隔

由于这个贡献上限很小，所以考虑枚举贡献，计算恰好满足这种贡献的子序列个数

又因为“恰好满足这种贡献”很难算，于是考虑计算“大于等于这种贡献”的方案数，然后前后差分，得到“恰好”

于是现在问题转化为计算有序数列上贡献大于等于限制的子序列的个数，考虑用dp解决

考虑dp状态，设$f[i][j]$表示前$i$个数，强制选$a_i$，共选$j$个时的方案数

显然最后答案为$\sum f[i][k]$

考虑转移，根据限制，有$f[i][j]=\sum \limits_{a_i-a_k\ge lim} f[k][j-1]$，其中$lim$是你当前枚举到的贡献，即限制

转移复杂度$O(n)$

注意到循环变量$k$是单调不减的，于是可以用双指针配合前缀和做到$O(1)$转移

---

最后计算一下时间复杂度：

枚举贡献复杂度$O(\frac{a}{k})$，dp复杂度$O(nk)$

两者相乘复杂度$O(an)$

---

### 代码：

```cpp
#pragma GCC optimize(3,"Ofast","inline")
#pragma GCC target("avx,avx2")
#include <bits/stdc++.h>
using namespace std;
template<class t> inline t read(t &x){
	char c=getchar();bool f=0;x=0;
	while(!isdigit(c)) f|=c=='-',c=getchar();
	while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
	if(f) x=-x;return x;
}
template<class t> inline void write(t x){
	if(x<0) putchar('-'),write(-x);
	else{if(x>9) write(x/10);putchar('0'+x%10);}
}

const int mod=998244353,N=1005;
int f[N][N],sum[N][N],n,k,a[N],ans;

int calc(int lim){
	int res=0;
	f[0][0]=sum[0][0]=1;
	for(int i=1,pt=0;i<=n;i++){
		while(pt+1<=i&&a[i]-a[pt+1]>=lim) pt++;
		for(int j=0;j<=k;j++){
			if(j) f[i][j]=sum[pt][j-1];
			sum[i][j]=(sum[i-1][j]+f[i][j])%mod;
		}
		res=(res+f[i][k])%mod;
	}
	return res;
}

signed main(){
	read(n);read(k);
	for(int i=1;i<=n;i++) read(a[i]);
	sort(a+1,a+1+n);
	for(int lim=(a[n]-a[1])/(k-1),last=0;~lim;lim--){
		int now=calc(lim);
		ans=(ans+1ll*(now-last+mod)*lim%mod)%mod;
		last=now;
	}
	write(ans);
}
```

---

## 作者：CuSObin_BiNSO4 (赞：3)

这题我的想法倒是挺一波三折的——从想到一个会 T 的方法到发现如何优化这个方法。

首先，我们需要发现这是一道传统的拆贡献题——如果一个长度为 $k$ 序列的美丽值是 $x$，那么我们会对于所有正整数 $t$，统计美丽值 $\ge t$ 的序列数量并把它加到答案里。这样一个序列最终就会为答案刚刚好好贡献 $x$。

第一步肯定要对序列排好序，由于仅要求是子序列，所以打乱顺序不会对答案产生影响。接下来问题转化为对于所有正整数 $t$，求美丽值 $\ge t$ 的长度为 $k$ 的序列数量，也即相邻两项差值均 $\ge t$ 的长度为 $k$ 的序列数量。

这个比较简单：设 $R_i$ 表示第一个位置 $x$ 使得 $a_x-a_i\ge t$（如果不存在则为 $n+1$），那么我们可以初始设 $R_i=i$，然后在升序遍历 $t$ 时可以对于每个位置从 $R_i$ 继续往后扫描——直到扫到满足条件的为止，来以**总**时间复杂度 $O(n^2)$ 处理出来。

然后设 $f_{i,j}$ 表示第一项为原序列的第 $i$ 个位置且序列长度为 $j$ 的序列数量，则有：

$$f_{i,1}=1,\forall 2\le j\le k,f_{i,j}=\sum_{y=R_i}^n f_{y,j-1}$$

明显，我们倒着处理 dp 值时可以使用后缀和优化。于是对于单个 $t$，它的时间复杂度就是 $O(nk)$。

最后我们想想我们要把 $t$ 处理到哪？明显，$t$ 最多处理到值域上界 $A_{\max}=10^5$，但是这样时间复杂度就是 $O(A_{\max}nk+n^2)$，爆炸了。

但是，$t$ 真的要处理到 $A_{\max}$ 吗？做到这里的时候我又灵光一现：如果 $(k-1)t>A_{\max}$，那么这个序列的第一项和最后一项差值便会大于 $A_{\max}$，这就矛盾了！

这样我们 $t$ 处理到 $\lfloor\frac{A_{\max}}{k-1}\rfloor$ 即可！时间复杂度即为 $O(\frac{A_{\max}}{k-1}nk+n^2)=O(A_{\max}n+n^2)$，成功通过。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

int n,K,a[1005],nxt[1005],dp[1005][1005],pres[1005][1005],ans;
const int modp=998244353;

int main(){
	cin>>n>>K;for(int i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+n+1);for(int i=1;i<=n;i++)nxt[i]=i+1;
	for(int o=1;o<=100000/(K-1);o++){
		for(int i=1;i<=n;i++)while(nxt[i]<=n&&a[nxt[i]]-a[i]<o)nxt[i]++;
		for(int i=n;i>=1;i--){
			dp[i][1]=1;for(int j=2;j<=K;j++)dp[i][j]=pres[nxt[i]][j-1];
			for(int j=1;j<=K;j++)pres[i][j]=(pres[i+1][j]+dp[i][j])%modp;
		}
		ans=(ans+pres[1][K])%modp;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：AK_heaven (赞：1)

### [Array Beauty](https://www.luogu.com.cn/problem/CF1188C)

这道题目有两个关键的 trick：

- 1. 我们对数组进行了排序。为什么是对的？我们来思考一下，最后我们在选出 $k$ 个数字以后我们计算贡献又会强行使得数组有序，原因很简单，因为 $|b_i - b_j|$ 如果 $b_i < b_j$，那么绝对值就会使得 $b_i$ 和 $b_j$ 交换位置，而因为取 $\min$，所以值域相近的两个数字会在一起。所以这道题目不管如何，最后答案在计算时数组一定是有序的。这也说明了排序是正确的，并且对于解题有着一定帮助。

- 2. 我们直觉告诉我们，我们需要枚举每种可能的答案，因为答案值域很小，或者说根据结论，要使最小间隙最大，就必须要均匀分配间隙，也就是说对于数列 $\{1, 2, 3, 4, 5, 6, 7\}$，我们应当选择出类似 $\{1, 3, 5, 7\}$，这样才能做到最大，而不是 $\{1, 2, 3, 7\}$，看着最大的大，但是最小的也更小了。于是枚举答案可行。

- 3. 在枚举每种答案时，我们定义出了一个状态 $F_{i, j, 0/1}$，强制选择第 $i$ 个数字，并且已经选了 $j$ 个数字，有没有到达 $\min$ 答案时的方案数，由于状态是两维的，转移枚举 $i$ 又是 $O(n)$ 的，考虑前缀和优化明显要考虑很多东西，例如容斥，等等。于是我们考虑 **状态前缀化**，然后转化为差分数组求出答案。则状态设为 $F_{i, j}$ 表示前 $i$ 个数字，且强制选 $i$，已经选了 $j$ 个数字，且满足间隙大于等于枚举答案的方案数。
 
转移直接双指针 + 前缀和即可，我称之为 **双前组合**。

**The code**


```cpp
#include<bits/stdc++.h>

#define L(i, a, b) for(int i = (a); i <= (b); i++)
#define R(i, a, b) for(int i = (a); i >= (b); i--)
#define ll long long

using namespace std;

const int N = 1005 + 10;
const int mod = 998244353;

ll a[N], n, k, ans[1000001], F[1005][N], sum[N][N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);  cout.tie(0);
	cin >> n >> k;
	L(i, 1, n) cin >> a[i];
	sort(a+1, a+n+1);
	R(i, (a[n]-a[1])/(k-1), 0) {
		F[0][0] = sum[0][0] = 1;
		int p = 0;
		L(j, 1, n) {
			while(p < j && a[j] - a[p+1] >= i) p++;
			L(x, 0, k) {
				if(x) F[j][x] = sum[p][x-1];
				sum[j][x] = (sum[j-1][x] + F[j][x]) % mod;
			}
			ans[i] = (ans[i] + F[j][k]) % mod;
		}
//		cout << ans[i] << '\n';
	}
	ll Ans = 0;
	R(i, (a[n]-a[1])/(k-1), 0)
	  Ans = (Ans + 1LL * (ans[i] - ans[i+1] + mod) % mod * i % mod) % mod;
	cout << Ans << '\n';
	return 0;
}

```

---

## 作者：MspAInt (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1188C)

关键词：差分，双指针，dp。

排个序显然不影响答案。

值域比较小，考虑先枚举贡献 $p$。

现在要求贡献恰好为 $p$ 的子序列个数。昨天刚做过一道类似的题，求贡献小于 $p$ 的方案数是容易的，设 $dp_{i,j}$ 表示前 $i$ 个数选 $j$ 个且满足 $p$ 限制的子序列方案数，转移如 $dp_{i,j}=\sum_{a_i-a_k<p,k<i}dp_{k,j-1}$，由于排过序，显然是可以用双指针+前缀和优化到 $\Theta(nk)$。

求得贡献小于 $p$ 的方案数，再和小于 $p+1$ 的方案数做差分就得到了贡献恰好为 $p$ 的子序列个数，然后乘上 $p$ 即可。

设 $w=\max_{i=1}^{n}a_i$，复杂度为 $\Theta(nkw+n\log n)$，无法通过。

但是！根据小学奥数，因为贡献是子序列相邻差的最小值，那么想要最大贡献就必须让相邻位之间的差均匀分配。即 $p$ 最大只有 $\frac{w}{k-1}$（其实更小但是枚举到这问题不大）。

这时复杂度为 $\Theta(\frac{w}{k-1}\cdot nk+n\log n)$，也就是 $\Theta(nw+n\log n)$，5s 时限稳过。

以及如果你 TLE 了，请检查清空前缀和数组时是否使用了 `memset`。

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e3+10,mod=998244353;
int n,m,dp[N][N],s[N][N],f[N*100],a[N],ans,cnt;
signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    sort(a+1,a+n+1);a[0]=-1e9;
    for(int p=a[n]/(m-1);p>0;p--){
        dp[0][0]=s[0][0]=1;
        for(int r=1,l=0;r<=n;r++){
            while(l<r&&a[r]-a[l+1]>=p)l++;
            for(int i=0;i<=m;i++){
                if(i)dp[r][i]=s[l][i-1];
                s[r][i]=(s[r-1][i]+dp[r][i])%mod;
            }
            f[p]=(f[p]+dp[r][m])%mod;
        }
        for(int i=1;i<=n;i++)
            for(int j=0;j<=m;j++)s[i][j]=0;
        ans=(ans+1ll*(f[p]-f[p+1]+mod)%mod*p%mod)%mod;
    }
    printf("%d\n",ans);
    system("pause");
    return 0;
}
```

[record](https://www.luogu.com.cn/record/126090239)

---

## 作者：lahlah (赞：1)

[CF1188C Array Beauty](https://www.luogu.org/problem/CF1188C)
# 题目大意
给出一个序列 $a[1...n]$ 还有一个$k$

问$a$的所有长度为$k$的子序列的价值和是多少

定义一个序列$b[1...k]$的价值为$min(abs(b_i - b_j))$ 即最接近的两个数的差

# 题解
首先因为是子序列，所有可以把a先排个序

然后发现 : 

# 假设最大的数是$a[n]$,则对于这个序列价值 <=  $\frac{a[n]}{k - 1}$

这个很容易证明吧，就不说了

然后可以很容易想到枚举价值，然后dp出当前价值的有多少种取法，然后乘一下再加起来

但是发现这个dp很难写(反正我不会）

考虑换一种dp方式，dp出大于当前价值的有多少种取法

然后把全部的加起来就行了

为什么呢?

假设当前枚举的价值为v，那么对于1.....v 的dp出来的都有1的贡献，就相当于产生了v的贡献

然后加个前缀和优化就好了


看代码好了

code:
```cpp

#include<bits/stdc++.h>
#define mod 998244353
using namespace std;
int n, k, a[1005], f[1005][1005];
int calc(int x){
	int pre = 0; f[0][0] = 1;
	for(int i = 1; i <= n; i ++){
		while(a[pre] <= a[i] - x) pre ++;//前缀和优化
		f[i][0] = 1;
		for(int j = 1; j <= k; j ++){
			f[i][j] = (f[i - 1][j] + f[pre - 1][j - 1]) % mod;//做前缀和，f[i-1][j]表示不选， 另一个表示选
		}
	}
	return f[n][k];//返回大于价值x的长度为k的子序列个数
}
int main(){
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; i ++) scanf("%d", &a[i]);
	sort(a + 1, a + 1 + n); a[0] = - mod;
	int ans = 0;
	for(int i = 1; (k - 1) * i <= a[n]; i ++) ans = (ans + calc(i)) % mod;//枚举价值并加起来
	printf("%d", ans);
	return 0;
}
```

# 坑点
貌似没有



---

## 作者：万弘 (赞：1)

[CF1189(Div.2)题解(全)](https://blog.csdn.net/whsstory/article/details/95317811)

(洛谷的Markdown好像有点奇怪，可能有些地方坏掉了，可以去这个链接里看)
## F. Array Beauty

题意:定义数组$B$的"美丽度"为$$\min_{1≤i<j≤n}|b_i−b_j|$$
给你一个数组$A$(长为$n$,所有元素值$a_i$为整数且$(0≤a_i≤10^5)$)和一个数字$k(2≤k≤n≤1000)$.计算$A$的所有长为$k$的子序列的美丽度总和模$998244353$的结果.  

题解:`设最后要求的结果为Q,美丽度为l的子序列有f(l)个`,则
$$Q=\sum_{l=0}^{\text{未知上界}}(l*f(l))$$
现在来求一下这个"未知上界":  
由题,$a_i$为整数且$(0≤a_i≤10^5)$.所以看起来"未知上界"=$10^5$?  
但实际上,"未知上界"=$\frac{10^5}{k-1}$.为什么呢?官方题解是这样说的:(先将$A$从小到大排序)  
假设美丽度$l>\frac{10^5}{k-1}$.`设P是一个长为k的序列`,且$p_i<p_{i+1}$(所以$P$表示$A$的一个子序列的取法)
则$a_{p2}≥a_{p1}+l,...,a_{pk}≥a_{pk−1}+l$(注意美丽度的定义),然后有  
$$a_n≥a_{pk}≥a_{pk−1}+l≥a_{pk−2}+2l...≥a_{p1}+(k−1)l≥(k−1)l$$.最后推得:$$  (k−1)l≤a_n⇔l≤\frac{a_n}{k-1}$$
再看看上面的定义,嘿嘿,是不是不太一样?  
我的证明:设$A$的某个长为$k$的子序列为$B$考虑到$b_k-b_1\leq10^5,b_x-b_{x-1}\geq \text{未知上界}$.而$B$长为$k$,也就有$k-1$个这样的间隔.则有$$(k-1)\times \text{未知上界}\leq 10^5$$  
所以求得,"未知上界"=$\frac{10^5}{k-1}$

但我们还要求$f(l)$.考虑DP:`设f[i][j]:在前i个数中选j个的方案数,p为满足b_{p+1}-a_i<l的最大整数`,则显然:$$f[i][j]=f[i-1][j]+f[p][j-1]\ (mod\ 998244353)$$  
通过借助排序后A的单调性推进或二分找p,就可在$O(nk)$时间里做完这个DP.  
总复杂度$=O(\frac{10^5}{k-1}\times nk)=O(10^5n)$(这里的$10^5$不是通常意义上的常数,故不能省略).

```cpp
/**********/
#define MAXN 2011
#define MAXE 100000
#define MOD 998244353
ll n,k,a[MAXN],f[MAXN][MAXN];
ll calc(ll l)
{
	f[0][0]=1;
	ll p=0;
	for(ll i=1;i<=n;++i)
	{
		while(a[i]-a[p+1]>=l)++p;
		f[i][0]=f[i-1][0];
		for(ll j=1;j<=k;++j)f[i][j]=(f[i-1][j]+f[p][j-1])%MOD;
	}
	return f[n][k];
}
int main()
{
	n=read(),k=read();
	for(ll i=1;i<=n;++i)a[i]=read();
	std::sort(a+1,a+n+1);
	ll ans=0;
	for(ll i=1;i<=MAXE/(k-1);++i)
		ans=(ans+calc(i))%MOD;
	std::cout<<ans;
	return 0;
}
```

---

## 作者：Hoks (赞：0)

## 前言
观察性质题。

摘自 [杂题选做](https://www.luogu.com.cn/training/660942)。
## 思路分析
题意已经很清晰了，但是我们可以描述下 $\min$ 那个式子的意义，就是求最小差。

我们不妨先考虑下求这东西的复杂度是多少。

直接暴力是 $O(n^2)$ 的，而在有序的情况下是 $O(n)$ 的。

因为题意是从 $n$ 个里面选出 $k$ 个的所有方案的最小差之和。

所以我们不妨利用这点性质，先钦定数组单调，也就是先排序。

这样的话对于最小差我们就有美妙的性质，也就是只需要计算上一个数即可。

然后考虑下排序后怎么做。

考虑下大力  dp，钦定 $f_{i,j}$ 表示选上第 $i$ 个数且这是选上的第 $j$ 个数的答案。

然后我们就发现貌似是没法做了，因为我们这个答案每次加入了之后是一堆数对于一个数整体取 min 然后求和。

这个可能能用一些高级数据结构做，但是我们不考虑。

沿用大力思想，哪个不确定就把哪个扔进状态里。

不妨考虑枚举答案，这样我们只需要数每种答案有多少种方案数了。

考虑继续沿用上面说的那个 dp，但是把状态从答案改成方案数，那么最后的答案就是 $\sum\limits_{i=1}^n f_{i,k}\cdot x$，其中 $x$ 是钦定的答案。

钦定计算而言，我们考虑其实就是一个前缀和一个后缀的方案在中间的位置拼起来，复杂度貌似很高。

不妨考虑类似于容斥原理使用时的思想。

我们不要把状态设定的这么死，把**等于**化为**大于等于**然后差分把答案化回去，此时的 dp 就非常容易优化了。

分析下复杂度，dp 部分是 $O(n,k)$ 的，而我们枚举的答案，考虑在 $[1,V]$ 的值域里尽可能均匀撒 $k$ 个点时最小距离最大，所以钦定枚举的答案是 $O(\frac{V}{k})$ 的，总复杂度 $O(nV)$，可以通过。

---

## 作者：OldDriverTree (赞：0)

# Solution

不难发现，把序列排序后答案不会发生变化。

先把 $a$ 序列排序，排序后的美丽值就是选择的子序列中相邻两个数之差的最小值。

考虑枚举序列的美丽值 $x$，但是直接求美丽值等于 $x$ 的子序列个数不太好求，把求美丽值等于 $x$ 的个数改成求美丽值大于等于 $x$ 的子序列个数，美丽值等于 $x$ 的就会在 $1\sim x$ 都加一遍，答案就为所有 $x$ 得到的子序列个数之和。

考虑 $\texttt{DP}$，设 $f_{i,j}$ 表示前 $i$ 个数中，选了 $j$ 个数，且第 $j$ 个数为 $a_i$ 的方案数。

$f_{i,j}=\sum\limits_{a_i-a_k\ge x} f_{i-1,k}$，前缀和优化即可。

再思考这样做的时间复杂度，表面上看时间复杂度是 $O(Vnm)$，但是可以发现 $x$ 最大只能为 $\lfloor\dfrac{\max a_i-\min a_i}{m-1}\rfloor$，时间复杂度就为 $O(Vn)$，可以通过。

# Code
```c++
#include<bits/stdc++.h>
using namespace std;
const int mod=998244353;
const int N=1001;
int f[N][N],pos[N];
int n,m,V,ans,a[N];

int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%d",a+i);
	sort(a+1,a+n+1);
	for (int x=1;x<=(a[n]-a[1])/(m-1);x++)
	{
		for (int i=1,j=1;i<=n;i++) {
			while (a[j]<=a[i]-x) j++;
			pos[i]=j-1,f[i][1]=i;
		}
		for (int i=1;i<=n;i++)
			for (int j=2;j<=m;j++)
				f[i][j]=(f[i-1][j]+f[pos[i] ][j-1])%mod;
		
		ans=(ans+f[n][m])%mod;
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：intel_core (赞：0)

为了方便，我们将 $a$ 数组排序。

考虑美丽值为 $k$ 的子序列个数。直接求需要容斥，没办法保证复杂度；我们考虑用前缀和的方式简化。

记 $c_i$ 表示子序列的数中两两差都不小于 $i$ 的子序列个数。

那么 $c_{k+1}-c_k$ 就是美丽值为 $k$ 的子序列个数。

接下来考虑怎么快速求出 $c$ 数组。

固定 $k$ 之后，可以对排序后的数组来一遍 $O(nk)$ 的前缀和优化 $\text{DP}$ 求出 $c_k$。

可以发现，美丽值的上界是 $\frac{V}{k-1}$，所以总的复杂度是 $O(\frac{V}{k-1}\times nk)=O(nV)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NR=1e3+10;
const int V=1e5;
const int MOD=998244353;
#define int long long
int n,k,a[NR],sum[NR][NR],ans,idx[NR],last;

void clear(){
	for(int i=0;i<=n;i++)
		for(int j=2;j<=k;j++)sum[i][j]=0;
	for(int i=0;i<=n;i++)sum[i][1]=i;
}
void upd(int &x,int y){x=(x+y)%MOD;}

signed main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++)
		scanf("%lld",&a[i]),idx[i]=i;
	sort(a+1,a+1+n);
	for(int d=1;;d++){
		for(int i=1;i<=n;i++)
			while(idx[i]>0&&a[i]-a[idx[i]]<d)idx[i]--;
		clear();
		for(int j=2;j<=k;j++)
			for(int i=1;i<=n;i++)
				sum[i][j]=sum[i-1][j],upd(sum[i][j],sum[idx[i]][j-1]);
		upd(ans,(last-sum[n][k])*(d-1));
		last=sum[n][k];
		if(!sum[n][k])break;
	}
	cout<<ans<<endl;
	return 0;
}

```

---

## 作者：FutaRimeWoawaSete (赞：0)

美丽值等同于将序列按顺序排好后相邻之间相距最小的数的距离。

由于是对子序列计数，受上述启发直接排序，问题的答案等价于原问题，并且此时我们只要知道一个子序列中任意相邻数之间的距离就可以算出一个子序列的美丽值。

根据插板法，任意子序列的美丽值不超过 $\frac{V}{k - 1}$，想到枚举美丽值进行计数。                

最后询问的是美丽值之和，等价于所有美丽值不小于某个数的子序列个数，所以定义 $dp_{i,j}$ 表示前 $i$ 个数里面选了 $j$ 个数且不小于当前枚举的美丽值 $W$ 的子序列个数，则可以进行转移：               

$dp_{i,j} = \sum_{p = 0} ^ {pos} dp_{k,j - 1}$，其中 $pos$ 是 $a$ 的前缀中最后一个满足 $v \leq a_i - a_{pos}$ 的位置。                

发现 $pos$ 随着 $i$ 的递增具有单调性，可以双指针求，此时再滚一个 $dp_{k,j - 1}$ 的前缀和即可做到 $O(1)$ 转移。                

时间复杂度 $O(\frac{nkV}{k - 1})$。



---

## 作者：lhm_ (赞：0)

考虑对美丽值进行 $DP$ 来统计答案，发现直接统计美丽值等于 $v$ 的子序列方案数不好统计，不妨统计美丽值大于等于 $v$ 的方案数。发现这样统计，美丽值为 $v$ 的一个子序列在区间 $[1,v]$ 都会有贡献，所以这样的合法子序列的方案数即为答案。

先对 $a$ 进行排序，由抽屉原理得美丽值的最大值为 $\frac{a_n}{k-1}$。枚举当前考虑的美丽值为 $v$，设 $f_{i,j}$ 为考虑了前 $i$ 个数，选了 $j$ 个数的合法子序列方案数，得：
$$
f_{i,j} = f_{i-1,j} + f_{pos,j-1}
$$
其中 $pos$ 为最后一个满足 $a_i - a_{pos} \geqslant v$ 的位置，转移时只用考虑 $pos$ 的贡献，因为之前的合法位置的贡献已经统计到 $pos$ 了。因为满足单调性，所以求 $pos$ 用双指针即可。

```cpp
#include<bits/stdc++.h>
#define maxn 1010
#define p 998244353
using namespace std;
template<typename T> inline void read(T &x)
{
    x=0;char c=getchar();bool flag=false;
    while(!isdigit(c)){if(c=='-')flag=true;c=getchar();}
    while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    if(flag)x=-x;
}
int n,k,ans;
int a[maxn],f[maxn][maxn];
int calc(int v)
{
    int pos=0;
    for(int i=1;i<=n;++i)
    {
        f[i][0]=1;
        while(a[i]-a[pos+1]>=v) pos++;
        for(int j=1;j<=k;++j)
            f[i][j]=(f[i-1][j]+f[pos][j-1])%p;
    }
    return f[n][k];
}
int main()
{
    read(n),read(k),f[0][0]=1;
    for(int i=1;i<=n;++i) read(a[i]);
    sort(a+1,a+n+1);
    for(int i=1;i<=a[n]/(k-1);++i) ans=(ans+calc(i))%p;
    printf("%d",ans);
    return 0;
}
```

---

## 作者：yyy爱编程 (赞：0)

$Update \ at\ 5-16:修改部分问题$

一道动态规划难题。

-----
题目大意：给你一个长度为$n$的数列$a_1,a_2,a_3,……a_k$，定义它其中一个长度为$k$的子序列为$b_1,b_2,b_3……b_k$的价值为:

$\boxed{\min \limits_{1\leq i\leq j\leq k}|b_i-b_j|}$

求数组$a$的所有长度为$k$的子序列的价值和。

分析：价值和顺序无关，可以先对$a$进行排序，这样求贡献就可以用下面的式子：

$\boxed{\min \limits_{i=1}^{k-1}(b_{i+1}-b_i)}$

`sort(a+1,a+n+1);`

之后的$a$有序。

由于题目说选$k$个数，因此答案的上界$m=\lceil {\frac{a_n-a_1}{k-1}} \rceil$。

先考虑计算出答案为$1$~$m$的所有方案数。

直接算不容易，可以求出答案$\ge1$~$m$的方案数，再差分。


令$f_{i,j}$表示前$i$个数中选$j$个，相邻两个的差一定大于当前$d$的方案数。

直接计算$O(n^3k)$，考虑前缀和优化$O(n^2k)$。

枚举$d$时，$a_i$前面第一个和它相差$\ge d$的位置是单调的，所以可以用单调的指针维护这个位置，这么做$O(nk)$。

总的时间复杂度：$O(\frac{V}{k}·nk)=O(nV)$。



---

## 作者：Yuby (赞：0)

[题面](https://www.luogu.com.cn/problem/CF1188C)

点数：2500

## 分析

注意到题目中的美丽程度定义，和整个数列顺序无关，不妨先排序。

### 结论

一个长度为 $k$ 数列 $a$ 的美丽程度不会超过 $\left\lceil\dfrac{\max a_i-\min a_i}{k-1}\right\rceil$。

### 证明

不难发现，尽量均匀的取 $a_i$ 一定最大，分为 $k-1$ 份。

接下来的 dp 其实很套路。我们发现似乎很难去直接统计统计答案。那我们考虑枚举每个数列的美丽程度然后计算在此情况下的子序列的个数，转化为计数问题。这个时候我们发现直接计算美丽程度等于某个值似乎也不可做，于是我们枚举 $x$，求美丽程度不小于 $x$ 的子序列个数，形成一个差分的形式。最后直接累加即可。

设 $dp_{i,j}$ 表示前 $i$ 个数中选择了 $j$ 个并且选择了 $i$，且美丽程度不小于当前枚举的 $x$ 的子序列数量。转移：

$\LARGE dp_{i,j}=\sum\limits_{a_i-a_k>=x}dp_{k,j-1}$。

由于我们已经进行了排序，所以随 $i$ 递增 $a_i$ 递增，那么 $k$ 也一定递增。并且这个式子显然满足前缀和优化的形式。使用双指针和前缀和优化。

综合复杂度：$O(\dfrac{\max{a_i}}{k}\times n\times k)=O(n\times \max{a_i})$。

核心代码：

```cpp
const ll MAXN=1007,MOD=998244353;
ll n,k,a[MAXN],dp[MAXN][MAXN],f[MAXN][MAXN];
int main()
{
 	//freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    n=read(),k=read();
    for(ll i=1;i<=n;i++)a[i]=read();
    sort(a+1,a+n+1);
    a[0]=-LLINF;
    ll ans=0;
    for(ll x=1;x*(k-1)<=a[n];x++)
    {
    	ll l=0,res=0;
    	dp[0][0]=f[0][0]=1;
    	for(ll i=1;i<=n;i++)
    	{
    		while(l<=n&&a[l]<=a[i]-x)l++;
    		for(ll j=0;j<=k;j++)
	    	{
	    		if(j)dp[i][j]=f[l-1][j-1];
	    		f[i][j]=(f[i-1][j]+dp[i][j])%MOD;
			}
			res=(res+dp[i][k])%MOD;
		}
		ans=(ans+res)%MOD;
	}
	write(ans);
	return 0;
}
```



---

