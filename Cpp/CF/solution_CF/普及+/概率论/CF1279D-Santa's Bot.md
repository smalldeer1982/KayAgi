# Santa's Bot

## 题目描述

Santa Claus has received letters from $ n $ different kids throughout this year. Of course, each kid wants to get some presents from Santa: in particular, the $ i $ -th kid asked Santa to give them one of $ k_i $ different items as a present. Some items could have been asked by multiple kids.

Santa is really busy, so he wants the New Year Bot to choose the presents for all children. Unfortunately, the Bot's algorithm of choosing presents is bugged. To choose a present for some kid, the Bot does the following:

- choose one kid $ x $ equiprobably among all $ n $ kids;
- choose some item $ y $ equiprobably among all $ k_x $ items kid $ x $ wants;
- choose a kid $ z $ who will receive the present equipropably among all $ n $ kids (this choice is independent of choosing $ x $ and $ y $ ); the resulting triple $ (x, y, z) $ is called the decision of the Bot.

If kid $ z $ listed item $ y $ as an item they want to receive, then the decision valid. Otherwise, the Bot's choice is invalid.

Santa is aware of the bug, but he can't estimate if this bug is really severe. To do so, he wants to know the probability that one decision generated according to the aforementioned algorithm is valid. Can you help him?

## 样例 #1

### 输入

```
2
2 2 1
1 1
```

### 输出

```
124780545
```

## 样例 #2

### 输入

```
5
2 1 2
2 3 1
3 2 4 3
2 1 4
3 4 3 2
```

### 输出

```
798595483
```

# 题解

## 作者：Computer1828 (赞：5)

以下，我们称集合 $x$ 的大小是 $si[x]$。

我们随机选一个集合的概率显然是 $\dfrac{1}{n}$。

假设我们选的这个集合是 $a_x$，那我们从中再选一个数的概率就是 $\dfrac{1}{si[x]}$

再假设我们选的数是 $y$，有 $sum[y]$ 个集合有 $y$，那么随机选一个集合含有 $y$ 的概率就是 $\dfrac{sum[y]}{n}$。

最后，对上述的概率求和，然后取逆元即可。

最后的答案是：

$$ans = \sum\limits_{x = 1}^{n}\sum\limits_{y\in a_x} \dfrac{1}{n\cdot si[x]}\cdot\dfrac{sum[y]}{n}$$

提出 $n$ 就变成：

$$ans = \dfrac{\sum\limits_{x = 1}^n\dfrac{\sum\limits_{y\in a_x}\dfrac{sum[y]}{n}}{si[x]}}{n}$$

代码：

```cpp
#include<bits/stdc++.h>
#define N 1000005
#define mod 998244353
#define ll long long
#define inv(a) qpow(a,mod-2,mod)
using namespace std;
int n;
int si[N],sum[N];
vector<int> s[N];
inline ll qpow(ll a,ll b,ll p){
	ll res = 1,base = a;
	while(b){
		if(b&1) res = res*base%p;
		base = base*base%p;
		b >>= 1;
	}
	return res;
}
ll ans;
int main(){
	scanf("%d",&n);
	int tmp;
	for(int i = 1;i<=n;++i){
		scanf("%d",si+i);
		for(int j = 1;j<=si[i];++j){
			scanf("%d",&tmp);
			sum[tmp]++,s[i].push_back(tmp);
		}
	}
	for(int i = 1;i<=n;++i){
		ll res = 0;
		for(int j = 0;j<si[i];++j) res = (res+sum[s[i][j]]*inv(n)%mod)%mod;
		ans = (ans+res*inv(si[i])%mod)%mod;
	}
	printf("%lld",ans*qpow(n,mod-2,mod)%mod);
	return 0;
}
```

---

## 作者：IKUN314 (赞：3)

## [CF1279D Santa's Bot](https://www.luogu.com.cn/problem/CF1279D)
### 前言
来一篇扩欧题解。


------------
### 推导
根据题意，在n个集合 $ a_1,a_2,\ldots,a_n $ 里面选出的集合 $ a_x $ 中再选取一个元素 $ y $ 的概率为 : $ \dfrac{1}{n}\times\dfrac{1}{k_x}=\dfrac{1}{nk_x} $。

接着还要选一个集合 $a_z$ 求 $y\in a_z$ 的概率，即 $n$ 个集合中选出一个集合包含元素 $y$ 的概率。那么，这里引入一个数组 $cnt$，其中 $cnt_i$ 表示出现了元素 $i$ 的集合数。
这部分的概率即为 $\dfrac{cnt_y}{n}$。

枚举 $x$，再遍历 $a_x$ 求 $y$ 并计算即可

答案为 :
$$\sum_{x=1}^n\sum_{y \in a_x}\frac{cnt_y}{n^2k_x}$$


另外还要求逆元。如前言，这里我使用了[扩展欧几里得算法求乘法逆元](https://oi-wiki.org/math/number-theory/inverse/#%E6%89%A9%E5%B1%95%E6%AC%A7%E5%87%A0%E9%87%8C%E5%BE%97%E6%B3%95)。


------------
到这里做题的思路大致就出来了，还有几点需要注意：
- 看一眼数据范围，$1 \le n \le 10^6,\sum\limits_{i=1}^nk_i \le 10^6$，就不能用数组存储这 $n$ 个集合了，因为控制要开的空间是困难的。于是需要使用 vector 来存储。

- 计算过程中显然会爆 `int`，所以要开 `long long` (ps: 其实 `long long` 都差点爆了)。


------------
### AC CODE
代码跑的比较慢，但是能过。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 1000010
#define ll long long
const ll mod=998244353;
vector<ll> a[N];//vector存储
ll n,k[N],cnt[N],x,y;
ll exgcd(ll a,ll b){//扩欧
    if(b==0){
        x=1;
        y=0;
        return a;
    }
    ll ret=exgcd(b,a%b);
    ll x2=x;
    x=y;
    y=x2-(a/b)*y;
    return ret;
}
int main(){
    ll i,j,nm;
    
    cin>>n;
    for(i=1;i<=n;i++){
        cin>>k[i];
        for(j=1;j<=k[i];j++){
            cin>>nm;
            cnt[nm]++;
            a[i].push_back(nm);
            
        }
    }
    
    ll ans=0;
    x=0;
    y=0;
    
    //由于变量x,y用在了exgcd，这里使用i与j。
    for(i=1;i<=n;i++){
        
        ll sum=0;
        for(auto j:a[i]){
            x=0;
            y=0;
            exgcd(n*n*k[i],mod);//求逆元
            x=(x%mod+mod)%mod;
            (sum+=cnt[j]*x%mod)%=mod;
        }
        (ans+=sum%mod)%=mod;
    }
    cout<<ans%mod;
    return 0;
}
```

---

## 作者：woshishei (赞：2)

### 观察样例

通过~~观察样例输出~~比赛中的 Announcement 可知第一个样例的答案为$\frac{7}{8}$，但题目并没有给出样例解释。于是我们需要模拟一下这个程序（括号中的数为执行到该语句的概率）：

![](https://cdn.luogu.com.cn/upload/image_hosting/12idsdm3.png)

在 $x=1,y=2,z=2$ 的情况下，$y\notin a_z$，剩下的情况均有 $y\in a_z$，因此总概率为$\frac{7}{8}$。

### 解题思路

枚举每个 $a_i$ 中的每个元素，每个元素中从 $1$ 到 $n$ 枚举每个 $z$，然后判断这个 $z$ 是否满足条件，如果满足条件就乘上这个语句的概率。

这个思路的时间复杂度为 $O(n\cdot \sum\limits_{x=1}^nk_x)$，显然不符合题目要求。

然后可以发现枚举每个元素的时候，再选择满足条件的 $z$ 的概率是相同的，所以可以在开始记录每个元素出现的次数（记为$cnt_y$），在枚举每一个元素时只需要加上这个元素出现的次数除以 $n$ 即可。

所以满足题目所需条件的概率为：

$$ans=\dfrac{\sum\limits_{x=1}^n\dfrac{\sum\limits_{y\in a_x}\dfrac{cnt_y}{n}}{k_x}}{n}$$

时间复杂度：$O(\sum\limits_{x=1}^nk_x)$

### 参考代码

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
using namespace std;
typedef long long ll;
const ll P=998244353;
vector<int> a[1000010];
int n,k[1000010],cnt[1000010];
ll ans=0;
ll qpow(ll x,ll t)
{
	ll res=1,base=x%P;
	while(t)
	{
		if(t&1)
			res=res*base%P;
		base=base*base%P;
		t>>=1;
	}
	return res%P;
}
ll inv(ll x)
{
	return qpow(x,P-2)%P;//x的倒数在 mod P 意义下的乘法逆元，数值上等于 x^(P-2) mod P
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&k[i]);
		for(int j=1;j<=k[i];j++)
		{
			int x;
			scanf("%d",&x);
			cnt[x]++;//统计每个元素出现的个数
			a[i].push_back(x);
		}
	}
	for(int i=1;i<=n;i++)
	{
		ll sum=0;
		for(int j=0;j<k[i];j++)
			sum=(sum+(ll)cnt[a[i][j]]*inv((ll)n)%P)%P;//sum 加上 cnt[a[i][j]]/n
		ans=(ans+sum*inv((ll)k[i])%P)%P;//ans 加上 sum/k[i]
	}
	printf("%I64d",ans*inv((ll)n)%P);//ans 除以 n 的结果
	return 0;
}
```

---

## 作者：ben090302 (赞：1)

简单概率题。

设第 $i$ 个集合的大小为 $siz_i$，含有元素 $y$ 的集合的个数设为 $S_y$

随机取一个集合的概率 $\dfrac{1}{n}$，从集合选一个元素的概率 $\dfrac{1}{siz_i}$，第三步的概率（从 $a_i$ 选出的数设为 $y$）为 $\dfrac{S_y}{n}$。

所以答案就是 $\dfrac{1}{n^2} \sum\limits^{n}_{i=1} \sum\limits _{y\in a_i} \dfrac{S_y}{siz_i}$，$S_y$ 可以预处理，复杂度 $O(n+k)$。

code：

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
int n;
int k[1000005];
void exgcd(int &x,int &y,int a,int b){
	if(b==0){
		x=1,y=0;
		return;
	}
	exgcd(x,y,b,a%b);
	int t=x;
	x=y,y=t-y*(a/b);
}
int Inv[1000005];
int inv(int a){
    int x,y;
    exgcd(x,y,a,mod);
    return (x+mod)%mod;
}
int ans=0;
vector<int> a[1000005];
vector<int> ton[1000005];
signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>k[i];
        for(int j=1;j<=k[i];j++){
            int tmp;
            cin>>tmp;
            a[i].push_back(tmp);
            ton[tmp].push_back(i);
        }
    }
    int ni=inv(n*n);
    for(int i=1;i<=n;i++){
        for(int j=0;j<a[i].size();j++){
            int V=a[i][j];
            ans=(ans+(ni*inv(a[i].size())%mod)*(ton[V].size())%mod)%mod;
        }
    }
    cout<<ans;
}
```

---

## 作者：codeLJH114514 (赞：1)

[洛谷题目传送门](https://www.luogu.com.cn/problem/CF1279D)  
[Codeforces 题目传送门](https://codeforces.com/contest/1279/problem/D)

题意：给定 $n$ 个大小为 $k_i$ 的集合 $a_1,a_2,\dots,a_n$，先等概率地随机选择一个集合 $a_x$，再以同样的方式随机选择一个集合 $a_z$，然后再在 $a_x$ 中等概率地随机选择一个数 $y$，问你 $y \in a_z$ 的概率。

数据范围：$1 \leqslant n \leqslant 10^6, 1\leqslant k_i\leqslant 10^6,1\leqslant \sum k_i \leqslant 10^6$，$a_i$ 中的元素 $\in [1, n]$，且在同一个集合中不会有两个相同的元素。

思路：我们考虑对于每一个 $a_x$ 中的元素 $y$，当且仅当 $z \in \text{AppearedSets}_y$ 的时候才有 $y \in a_z$。

$\text{AppearedSets}_y$ 表示元素 $y$ 出现在的集合的集合。

对于 $a_x$ 中的每一个元素 $y$，选到 $y \in a_z$ 的概率 $\text{F}(x, y)$ 为：
$$\text{F}(x, y) = \frac{|\text{AppearedSets}_y|}{n}$$

对于 $a_x$ 中的每一个元素 $y$，选到 $a_x$ 这个集合并选到 $y$ 这个元素的概率 $\text{P}(x, y)$ 为：
$$\text{P}(x, y) = \frac{1}{n \times k_x}$$

所以，对于 $a_x$ 中的每一个元素 $y$，它对于答案的贡献 $\text{Ans}(x,y)$，为：
$$\text{Ans}(x, y) = \text{F}(x, y) \times \text{P}(x, y) = \frac{|\text{AppearedSets}_y|}{n^2 \times k_x}$$

所以，答案 $\text{Answer}$ 也就是：

$$
\begin{aligned}
\text{Answer} & = \sum_{x=1}^{n}\sum_{y \in a_x} \text{Ans}(x, y)\\
& = \sum_{x=1}^{n}\sum_{y \in a_x} \frac{|\text{AppearedSets}_y|}{n^2 \times k_x}
\end{aligned}
$$

实现：本题需要我们输出答案在 $\bmod\; 998244353$ 意义下的值，因此我们需要对答案的分母求逆元，即 $n^{-2} \times k_x^{-1} \pmod {998244353}$。

根据费马小定理，$a^{p-1} \equiv 1\pmod{p},p \in \text{Primes}$，我们左右两边同时除以 $a$，就可以得到：

$$a^{-1}\equiv a^{p-2}\pmod{p},p \in \text{Primes}$$

因为 $998244353$ 是质数，因此带入式子并使用快速幂即可求出逆元，时间复杂度 $\mathcal{O}(\log m)$。

因此，整个程序的时间复杂度即为 $\mathcal{O}(\sum k_i\log m)$，带入 $\sum k_i \leqslant 10^6$，$m = 998244353$，得到 $\mathcal{O}(\sum k_i \log m) \approx 3\times 10^7$，加上本题的 $5$ 秒时间限制，足以通过本题。

坑点：
- 本题每一个 $(x,y,z)$ 的出现概率都不一样，因为 $k_x$ 不同。
- 本题在实现的时候千万不要写 `power(n*n, mod - 2)` 这样的东西，因为 $n\times n$ 最高可达 $10^{12}$ 所以可能爆 `long long`，否则会 `WA on #37`。
- 勤取模。

C++ 代码：

```cpp
#include <bits/stdc++.h>
#define int long long

constexpr int maxn = 1000010;
constexpr int mod = 998244353;

int n, k, a;
std::vector<int> sets[maxn];
int appeared_sets[maxn];

int power(int base, int exp) {
	if (exp == 0) return 1;
	int son = power(base, exp >> 1);
	if (exp & 1) return son * son % mod * base % mod;
	return son * son % mod; 
}

signed main() {
	std::cin >> n;
	
	for (int i = 1; i <= n; i++) {
		std::cin >> k;
		for (int j = 1; j <= k; j++) {
			std::cin >> a;
			sets[i].emplace_back(a);
			appeared_sets[a] += 1;
		}
	}
	
	int answer = 0;
	for (int i = 1; i <= n; i++) {
		for (auto j : sets[i]) {
			answer += appeared_sets[j] * power(n, mod - 2) % mod * power(n, mod - 2) % mod * power(sets[i].size(), mod - 2) % mod;
			answer %= mod;
		}
	}
	
	std::cout << answer << std::endl;
	return 0;
}
```

---

## 作者：Φρανκ (赞：0)

题意：从 $n$ 个集合中任选两个 $i$ 与 $j$，再从 $i$ 的 $k_i$ 个元素中任选一个 $x$。求 $x\in j$ 的概率。

核心思想：枚举

解：

对于每个 $1\le x\le 10^6$，它对答案的贡献是它被选中的概率和它成功对应的概率的积，不妨设为 $p,q$。对于每一个元素 $x$，若它出现在集合 $i$ 中，它会使 $p$ 增加 $\frac{1}{nk_i}$（从所有元素中选中它的概率），使 $q$ 增加 $\frac{1}{n}$ （它出现在选定集合中的概率）。计算完毕后统计即可。时间复杂度 $O(n+\sum_{i=1}^nk_i)$。

代码：
```
#include <bits/stdc++.h>
using namespace std;
const long long mod=998244353;
long long inv[1000001], pro[1000001], fre[1000001], n, k, a, res;
int main()
{
	inv[1]=1;
	for(int i=2; i<=1000000; i++)
		inv[i]=(mod-mod/i)*inv[mod%i]%mod;
	cin>>n;
	for(int i=1; i<=n; i++)
	{
		cin>>k;
		for(int j=1; j<=k; j++)
		{
			cin>>a;
			fre[a]=(fre[a]+inv[n])%mod;//统计q
			pro[a]=(pro[a]+inv[n]*inv[k]%mod)%mod;//统计p
		}
	}
	for(int i=1; i<=1000000; i++)
		res=(res+fre[i]*pro[i]%mod)%mod;//加和
	cout<<res;
	return 0;
}
```

---

