# Count GCD

## 题目描述

You are given two integers $ n $ and $ m $ and an array $ a $ of $ n $ integers. For each $ 1 \le i \le n $ it holds that $ 1 \le a_i \le m $ .

Your task is to count the number of different arrays $ b $ of length $ n $ such that:

- $ 1 \le b_i \le m $ for each $ 1 \le i \le n $ , and
- $ \gcd(b_1,b_2,b_3,...,b_i) = a_i $ for each $ 1 \le i \le n $ .

Here $ \gcd(a_1,a_2,\dots,a_i) $ denotes the [greatest common divisor (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor) of integers $ a_1,a_2,\ldots,a_i $ .

Since this number can be too large, print it modulo $ 998\,244\,353 $ .

## 说明/提示

In the first test case, the possible arrays $ b $ are:

- $ [4,2,1] $ ;
- $ [4,2,3] $ ;
- $ [4,2,5] $ .

In the second test case, the only array satisfying the demands is $ [1,1] $ .

In the third test case, it can be proven no such array exists.

## 样例 #1

### 输入

```
5
3 5
4 2 1
2 1
1 1
5 50
2 3 5 2 3
4 1000000000
60 30 1 1
2 1000000000
1000000000 2```

### 输出

```
3
1
0
595458194
200000000```

# 题解

## 作者：孤芒星河233 (赞：9)

# CF1750D Count GCD

[CF题面](http://codeforces.com/problemset/problem/1750/D)

[洛谷题面](https://www.luogu.com.cn/problem/CF1750D)

## 题意

  有 $T$ 组数据。给出两个整数 $n,m$ 和一个长度为 $n$ 的数组 $a$，满足 $1\leq i\leq n,1\leq a_i\leq m$
  求出满足 $1\leq i\leq n,1\leq b_i\leq m$ 且 $\gcd(b_1,b_2,\cdots ,b_i)=a_i$ 的 $b$ 数组的数量。答案对 $998244353$ 取模。
  数据范围：$1\leq t\leq 100,1\leq n\leq 2\cdot 10^5,1\leq m\leq 10^9$

## 思路

  一道很有意思的简单数学题。

  显而易见，如果存在满足条件的 $b$ 数组，那么一定有 $1\leq i<n,a_{i+1}\mid a_i$。如何证明呢？我们知道 $\gcd(b_1,b_2,\cdots ,b_{i+1})=\gcd(\gcd(b_1,b_2,\cdots,b_i),b_{i+1})$，也就是说 $a_{i+1}=\gcd(a_i,b_{i+1})$，便有 $a_{i+1}\mid a_i$ 。

  下一步，便是找出每一个 $b_i$ 的可能情况。从刚才的结论来看，$a_{i+1}$ 是 $a_i$ 的因子，那么要让 $a_{i+1}=\gcd(a_i,b_{i+1})$ 需要把 $a_i$ 这个因子挑出去，现在只需要解这个方程：
  $$
  \gcd(\frac{a_i}{a_{i+1}},\frac{b_{i+1}}{a_{i+1}})=1
  $$
  现在只要求出 $[1,\lfloor \frac{m}{a_{i+1}} \rfloor]$ 中与 $\frac{a_i}{a_{i+1}}$ 互质的数，只需要找出 $\frac{a_i}{a_{i+1}}$ 的质因数，然后用上容斥原理就好了。

## 代码

  ```cpp
  #include<bits/stdc++.h>
  using namespace std;
  #define ll long long
  
  const int N=2e5+9,Mod=998244353;
  int T,n;
  ll m,a[N];
  
  int main(){
      scanf("%d",&T);
      while(T--){
          bool flag=1;
          scanf("%d%lld",&n,&m);
          for(int i=1;i<=n;i++){
              scanf("%lld",&a[i]);
              if(i>1&&a[i-1]%a[i]!=0) flag=0;//判断是否满足条件
          }
          if(!flag){
              printf("0\n");
              continue;
          }
          ll ans=1;
          for(int i=2;i<=n;i++){
              ll d=a[i-1]/a[i],x=m/a[i],y=0;
              vector<ll> num;
              for(int i=2;i*i<=d;i++){//分解质因数
                  if(d%i==0){
                      int len=num.size();
                      for(int j=0;j<len;j++) num.push_back(-num[j]*i);//容斥
                      num.push_back(i);
                      while(d%i==0) d/=i;
                  }
              }
              if(d>1){//特判
                  int len=num.size();
                  for(int j=0;j<len;j++) num.push_back(-num[j]*d);
                  num.push_back(d);
              }
              for(ll i:num) y+=x/i;
              ans=ans*(x-y)%Mod;
          }
          printf("%lld\n",ans);
      }
      return 0;
  }
  ```

---

## 作者：Jairon314 (赞：7)

> [题目链接](https://www.luogu.com.cn/problem/CF1750D)

$ \text{Solution} $

------------

容易发现本题的答案为：

$$ \prod_{i=1}^{n-1} \sum_{w=1}^m [\operatorname{gcd}(a_i,w)=a_{i+1}] $$

转化一下式子：

$$ \prod_{i=1}^{n-1} \sum_{w=1}^m [\operatorname{gcd}(a_i,w)=a_{i+1}] $$

$$ = \prod_{i=1}^{n-1} \sum_{w=1}^{\tiny{\left\lfloor\dfrac{m}{a_{i+1}}\right\rfloor}} [\operatorname{gcd}(\frac{a_i}{a_{i+1}},w)=1] $$

设 $ k_i={\tiny{\left\lfloor\dfrac{m}{a_{i+1}}\right\rfloor}} , x_i=\large{\frac{a_i}{a_{i+1}}}.$

对后面的求和式反演一下：

$$ \sum_{w=1}^{k_i} [\operatorname{gcd}(x_i,w)=1] $$

$$ = \sum_{w=1}^{k_i} \sum_{d|x_i,d|w} \mu(d) $$

$$ = \sum_{d|x_i} \mu(d) \sum_{w=1}^{k_i} [d|w] $$

$$ = \sum_{d|x_i} \mu(d) \left\lfloor\dfrac{k_i}{d}\right\rfloor $$

最后的整个式子：

$$ \prod_{i=1}^{n-1} \sum_{d|x_i} \mu(d) \left\lfloor\dfrac{k_i}{d}\right\rfloor $$

然后再分析一下复杂度：

1. 如果 $ {\exists \; i \in [1,n) , a_{i+1} \nmid a_{i}} $ 那么答案一定是 $0.$ 所以说数组 $a$ 单调非严格递减且后一个数是前一个数的因数。

2. 若 $a_i=a_{i+1}, $ 则 $ x_i = 1, $ 每次求后面这个和式是 $O(1)$ 的。

3. 若 $a_i \not = a_{i+1}, $ 每次根号求 $\mu$ ，后面这个求和式单次复杂度为 $O(\sqrt{x_i}) = O(x_i^{1/2}), $ 注意到此时 $a_{i+1}$ 一定小于 $a_i$ 的一半，所以这个操作最多只会执行 $\log a_1$ 次。

3. $x$ 的平均值显然是 $O(m)$ 级别的。

4. 由均值不等式可得每组数据总复杂度为 $ O(\log a_1 \times  \sum\limits_{i=1}^{n-1} \sqrt{x_i}) = O(\log a_1 \times  \sum\limits_{i=1}^{n-1}x_i^{1/2}) \le O(\log a_1 \times  \sqrt{\frac{\sum\limits_{i=1}^{n-1}x_i}{n-1}}) \le O(\sqrt m \log m) .$

-------------

[点击查看缺省源"Jairon.h"](https://www.luogu.com.cn/paste/bckqxxoh)

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define lint long long

#include <"Jairon.h">

#define maxn 1000010
#define SIZE 5010

const int mod = 998244353;

int Mu(int x){
	int res=0;
	for(int i=2;i*i<=x;i++){
		if(x%i==0){
			++res;
			int cnt=0;
			while(x%i==0){ x/=i; ++cnt; if(cnt>1){ return 0; } }
		}
	} if(x!=1){ ++res; }

	return (res&1)?(-1):1;
}

int n,m;
int a[maxn];

signed main(){
	int T=read(_);
	while(T--){
		bool flag=true;
		read(n,m);
		FOR(i,1,n){ read(a[i]); }
		FOR(i,1,n-1){ if(a[i]%a[i+1]!=0){ flag=false; break; } }
		if(flag==false){ puts("0"); continue; }

		int ans=1;

		FOR(i,1,n-1){
			int tmp=0;
			int x=a[i]/a[i+1];
			for(int j=1;j*j<=x;j++){
				if(x%j==0){
					int d1=j;
					int d2=x/j;
					tmp=(tmp+1ll*Mu(d1)*(m/a[i+1]/d1)%mod+mod)%mod;
					if(d1!=d2){
						tmp=(tmp+1ll*Mu(d2)*(m/a[i+1]/d2)%mod+mod)%mod;
					}
				}
			} ans=1ll*ans*tmp%mod;
		} assi(),outn(ans);
	}
	return 0;
}

/**/
```


---

## 作者：linyihdfj (赞：5)

## CF1750D Count GCD
想要更优质的阅读体验，就来[这里](https://www.cnblogs.com/linyihdfj/p/16893607.html)吧。
### 题目分析：
其实题目的式子可以化成这个形式：
$$
\begin{aligned}
\gcd(a[i],b[i+1]) &= a[i+1] \\
\gcd(\dfrac{a[i]}{a[i+1]},\dfrac{b[i+1]}{a[i+1]}) &= 1
\end{aligned}
$$
也就是说 $a[i]$ 和 $b[i+1]$ 必然是 $a[i+1]$ 的倍数。

其实也就是找 $[1,\bigg\lfloor \dfrac{m}{a[i+1]} \bigg\rfloor]$ 中有多少个数与 $\dfrac{a[i]}{a[i+1]}$ 互质。

这个显然可以使用容斥，也就是寻找有多少个不互质的。

我们设 $\dfrac{a[i]}{a[i+1]}$ 的唯一分解形式为 $p_1^{k_1}\times p_2^{k_2} \times \cdots$

其实就是求这个范围内有多少个数含有 $p_1$ 或含有 $p_2$ 或 $\cdots$ 作为因数，这个就看上去应该可以就显然容斥了吧。

就是对这个数分解质因数，然后求出所有的因数，对于指数相加为奇数的取正的贡献，对于指数相加为偶数得取负得贡献就好了。

这个是某一个 $b$ 的可能取值，那么可以直接对每一个 $b$ 都跑一遍将方案数乘法原理求出来就好了。
### 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 5e6+5;
const int MOD = 998244353;
vector<int> v;
int a[N];
int mod(int x){
	return ((x % MOD) + MOD)%MOD;
}
signed main(){
	int t;
	scanf("%lld",&t);
	while(t--){
		int n,m;scanf("%lld%lld",&n,&m);
		bool flag = true;
		for(int i=1; i<=n; i++){
			scanf("%lld",&a[i]);
			if(i != 1 && a[i-1] % a[i] != 0)	flag = false;
		}
		if(!flag){
			printf("0\n");
			continue;
		}
		int ans = 1;
		for(int i=1; i<n; i++){
			int x = m / a[i+1];
			int y = a[i] / a[i+1];
			//找 [1,x] 中与 y 互质的数 
			
			for(int i=2; i * i <= y; i++){
				if(y % i == 0){
					int p = v.size();
					for(int j=0; j<p; j++)	v.push_back(-v[j] * i);
					v.push_back(i);
					while(y % i == 0)	 y /= i;
				}
			} 
			if(y > 1){
				int p = v.size();
				for(int j=0; j<p; j++)	v.push_back(-v[j] * y);
				v.push_back(y);
			}
			int tmp = 0;
			for(int i : v)	tmp = mod(tmp + x / i);
			ans = mod(ans * mod(x - tmp));
			v.clear();
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：2)

算是到容斥经典题吧。

## 思路

考虑当 $a_i$ 不是 $a_{i+1}$ 倍数时一定不行。$b_1=a_1$。

然后我们考虑目前选了前 $i$ 个 $b_i$，计算 $b_{i+1}$ 的方案数。我们需要满足的是 $\gcd(b_i,b_{i+1})=a_i$ 即可。

容斥，钦定 $x|\gcd(a_i,b_{i+1})$，我们对于每个 $x|a_i$ 均计算出这个值，然后莫比乌斯反演或者直接容斥均可。

考虑一下复杂度，$b_1$ 的因子最多 $1344$ 个，每次的 $x$ 是 $a_i$ 的因数，$a_{i+1}$ 的倍数，总共也最多 $1344$ 个，复杂度 $t\times d(b_1)$ 可以通过。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
#define mid ((l+r)>>1)
using namespace std;
const int mod=998244353;
int count(int a1,int a2,int m){
	m/=a2;
	a1/=a2;
	int x[18],top=0;
	for(int i=2;i*i<=a1;i++){
		if(a1%i==0){
			x[++top]=i;
			while(a1%i==0) a1/=i;
		}
	}
	if(a1!=1){
		x[++top]=a1;
	}
	int ans=0;
	for(int i=0;i<(1<<top);i++){
		int mul=1;
		for(int j=1;j<=top;j++){
			if((i>>(j-1))&1) mul*=x[j];
		} 
		if(__builtin_popcount(i)&1) ans-=(m/mul);
		else ans+=(m/mul);
	}
	return ans;
}
signed main(){
	int t;
	cin>>t;
	while(t--){
		int n,m;
		cin>>n>>m;
		int a[n+1];
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		int ans=1;
		for(int i=2;i<=n;i++){
			if(a[i-1]%a[i]!=0){
				ans=0;
				break;
			}
			if(a[i-1]!=a[i]){
			ans=(ans*count(a[i-1],a[i],m))%mod;
			}
			else{
			ans=(ans*(m/a[i]))%mod;
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

赛时首 $A$ 代码写得可能有点乱，谅解。

---

## 作者：XL4453 (赞：1)

### $\text{Difficulty : 1800}$
---
### 解题思路：

首先发现对于每一个位置的 $b_i$，其关心的只有 $a_{i-1}$ 和 $a_i$ 两个值，而且只需要 $\gcd(a_{i-1},b_i)=a_i$ 就行了。只需要求出每一个位置上 $b_i$ 的可能情况数就行了。

也就是 $\sum_{i=1}^m[\gcd(a_{i-1},i)=a_i]$。

设 $i=i'a_i$ 得到 $\sum_{i=1}^{\lfloor\frac{m}{a_i}\rfloor}[\gcd(\frac{a_{i-1}}{a_i},i)=1]$。

进行反演，得到 $\sum_{i=1}^{\lfloor\frac{m}{a_i}\rfloor}\sum_{d|\gcd(\frac{a_{i-1}}{a_i},i)}\mu(d)$。

交换求和顺序得到 $\sum_{d=1}^m\mu(d)\sum_{i=1}^{\lfloor\frac{m}{a_i}\rfloor}[d|\gcd(\frac{a_{i-1}}{a_i},i)]$。

再设 $i=i'd$，得到 $\sum_{d|\frac{a_{i-1}}{a_i}}\mu(d)\lfloor\frac{m}{a_id}\rfloor$。

直接求就行。

---
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
#define int long long
const int MAXN=200005,MOD=998244353;
int n,m,a[MAXN],ans,T;
int mu(int x){
	int ans=1;
	for(int i=2;i*i<=x;i++){
		if(x%i==0){
			x/=i;
			ans=-ans;
		}
		if(x%i==0)return 0;
	}
	if(x!=1)ans=-ans;
	return ans;
}
int work(int x,int y){
	int ans=0;
	for(int i=1;i*i<=y;i++)
	if(y%i==0){
		if(i*i!=y)
		ans=(ans+mu(i)*(x/i)%MOD+mu(y/i)*(x*i/y)%MOD+MOD)%MOD;
		else
		ans=(ans+mu(i)*(x/i)%MOD+MOD)%MOD;
	}
	return ans%MOD;
}
signed main(){
	scanf("%lld",&T);
	while(T--){
		scanf("%lld%lld",&n,&m);
		for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
		ans=1;
		for(int i=2;i<=n;i++){
			if(a[i-1]%a[i]!=0){
				ans=0;
				break;
			}
			ans=(ans*work(m/a[i],a[i-1]/a[i]))%MOD;
		}
		printf("%lld\n",(ans+MOD)%MOD);
	}
	return 0;
}
```


---

## 作者：王熙文 (赞：1)

## 思路

首先化简一下题目的限制：

对于 $i=1,b_i=a_i$，否则 $\gcd(a_{i-1},b_i)=a_i$。

那么 $a_i$ 一定整除 $a_{i-1}$（否则无解）。

又发现，如果 $a_i \not= a_{i-1}$，则 $a_i \le \dfrac{a_{i-1}}{2}$，这样的 $i$ 最多只有 $\log$ 个。

当 $a_i = a_{i-1}$，则只要 $b_i$ 是 $a_i$ 的倍数即可，一共有 $\lfloor \dfrac{m}{a_i}\rfloor$ 个。

当 $a_i \not= a_{i-1}$，由上面的结论，这样的个数放在多测中也只有 $100 \times \log$ 个，所以可以用一些暴力的方式做。

首先，因为 $\gcd(a_{i-1},b_i)=a_i$，所以 $\gcd(\dfrac{a_{i-1}}{a_i},\dfrac{b_i}{a_i})=1$。$\dfrac{a_{i-1}}{a_i}$ 是已知的。因为 $b_i \le m$，所以 $\dfrac{b_i}{a_i} \le \lfloor \dfrac{m}{a_i}\rfloor$。因此我们把问题转化成了：已知 $x$，问有多少个在 $[1,lim]$ 中的 $y$ 使得 $\gcd(x,y)=1$。

我用了一个比较暴力的方法做。正难则反，我们需要统计有多少个 $y$ 使得 $x$ 和 $y$ 有至少一个共同的质因数。先将 $x$ 质因数分解，得到它的质因数 $p_1,p_2,\cdots, p_m$。根据容斥原理，设 $f(x)$ 表示 $x$ 的倍数个数，即 $\lfloor \dfrac{lim}{x} \rfloor$，则 $ans=f(p_1)+f(p_2)+\cdots +f(p_m)-f(p_1p_2)-f(p_1p_3)-\cdots - f(p_1 p_m)-f(p_2p_3)-\cdots - f(p_2 p_m)- \cdots -f(p_{m-1} p_m) + f(p_1p_2p_3) + \cdots$。这一部分可以通过二进制枚举状态求出来。最终的答案即为 $lim-ans$。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 998244353
using namespace std;
int n,m; int a[200010];
int tot,p[20];
int get_ans(int x,int lim) // gcd(x,y)=1, y<=lim 的个数 
{
	int tmp=x; tot=0;
	for(int i=2; i<=sqrt(tmp); ++i)
	{
		if(tmp%i==0)
		{
			p[++tot]=i;
			while(tmp%i==0) tmp/=i;
		}
	}
	if(tmp!=1) p[++tot]=tmp;
	int ans=0;
	for(int i=1; i<(1<<tot); ++i)
	{
		int cj=1;
		for(int j=1; j<=tot; ++j)
		{
			if(i>>(j-1)&1) cj*=p[j];
		}
		ans+=(__builtin_popcount(i)%2==1?1:-1)*(lim/cj);
	}
	return lim-ans;
}
signed main()
{
	int t; cin>>t; while(t--)
	{
		cin>>n>>m;
		for(int i=1; i<=n; ++i) cin>>a[i];
		int ans=1;
		for(int i=2; i<=n && ans; ++i)
		{
			if(a[i-1]==a[i]) ans=ans*(m/a[i-1])%mod;
			else if(a[i-1]%a[i]!=0) ans=0;
			else ans=ans*get_ans(a[i-1]/a[i],m/a[i])%mod;
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：Hedgehog_210508 (赞：0)

**题目传送门**：[here](https://www.luogu.com.cn/problem/CF1750D)

**思路**：首先观察题目。

我们发现 $\gcd(b_1,b_2,\ldots,b_{i+1})=\gcd(\gcd(b_1,b_2,\ldots,b_i),b_{i+1})$，所以只要 $a_{i+1}=\gcd(a_i,b_{i+1})$ 即可，所以每一个 $b_i$ 的情况都是独立的，最后答案就是把每一个 $b_i$ 的总数相乘。

对于 $a_{i+1}=\gcd(a_i,b_{i+1})$，$a_{i}$ 和 $b_{i+1}$ 必定是 $a_{i+1}$ 的倍数，即求多少个 $\dfrac{b_{i+1}}{a_{i+1}}$ 和 $\dfrac{a_{i}}{a_{i+1}}$ 互质。想到可以使用容斥原理，对所有质因子组合讨论得到结果。

**代码**：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define M 998244353
ll n,m,t,a[200009];
vector<ll> p;
ll solve(ll x,ll y){
    p.clear();
    for(ll i=2;i*i<=x;i++){
        if(x%i==0){
            p.push_back(i);
            while(x%i==0)
                x/=i;
        }
    }
    if(x>1) p.push_back(x);
    ll s=0;
    for(ll i=1;i<(1<<p.size());i++){
        ll cnt=0,mul=1;
        for(ll j=0;j<p.size();j++){
            if(i&(1<<j)){
                cnt++;
                mul*=p[j];
            }
        }
        if(cnt&1) s+=y/mul;
        else s-=y/mul;
    }
    return y-s;
}
int main(){
	std::ios::sync_with_stdio(false);
	cin>>t;
	while(t--){
		ll ans=1;
		cin>>n>>m;
		for(int i=1;i<=n;i++) cin>>a[i];
        for(int i=2;i<=n;i++) {
            if(a[i-1]==1&&a[i]==1) ans*=m%M,ans%=M;
            else if(a[i-1]%a[i]==0) ans*=solve(a[i-1]/a[i],m/a[i])%M,ans%=M;
            else{
                ans=0;
                break;
            }
        }
        cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：ningago (赞：0)

根据 $\gcd$ 的结合律：

$$a_i=\gcd(b_1,b_2,\cdots,b_{i-1},b_i)=\gcd(\gcd(b_1,b_2,\cdots,b_{i-1}),b_i)=\gcd(a_{i-1},b_i)$$

于是我们发现对于不同的 $i$，$b_i$ 的取值是相互独立的，所以答案就是 $\prod_{i=1}^n c_i$，其中 $c_i$ 表示 $b_i$ 的取值个数。

所以问题转化为对于每个 $i$，求有多少个 $b_i$ 满足 $\gcd (a_{i-1},b_i)=a_i(i\ne 1)$。（也就是求 $c_i$）

显然的是 $b_1=a_1$，即 $c_1=1$。

观察 $\gcd(x,y)=z$，也就是 $x=pz,y=qz,p\perp q$。

那么如果 $a_{i-1}\not\equiv0\pmod{a_{i}}$，$c_i=0$。

否则就等于 $[1,\left\lfloor\dfrac{m}{z}\right\rfloor]$ 内与 $p$ 互质的 $q$ 的个数。

这个容斥计算即可。

复杂度 $O(n\cdot (\sqrt n+10\times 2^{10}))$。

$10$ 是指前 $10$ 个质数乘起来大于 $10^9$。

$\sqrt n$ 在于分解质因数。

```cpp
#include <cstdio>
#include <cstring>
#include <vector>

#define N 200010
#define int long long
#define mod 998244353

int T;
int a[N];

bool vis[10000010];
int prime[5000010],idx;
int n,m;

void init()
{
	vis[1] = 1;
	for(int i = 2;i <= 10000000;i++)
	{
		if(!vis[i])
			prime[++idx] = i;
		for(int j = 1;j <= idx && i * prime[j] <= 10000000;j++)
		{
			vis[i * prime[j]] = 1;
			if(i % prime[j] == 0)
				break;
		}
	}
}

std::vector <int> v;

int get_p(int x,int M)
{
	v.clear();
	int now = x;
	for(int i = 1;prime[i] * prime[i] <= x;i++)
	{
		if(now % prime[i] == 0)
		{
			while (now % prime[i] == 0)
				now /= prime[i];
			v.push_back(prime[i]);
		}
	}
	if(now != 1)
		v.push_back(now);
	int sz = v.size();
	int res = 0;
	for(int i = 1;i < (1 << sz);i++)
	{
		int k = 1,cnt = 0;
		for(int j = 0;j < sz;j++)
			if(i & (1 << j))
			{
				cnt++;
				k *= v[j];
			}
		if(cnt & 1)
		{
			res += M / k;
			res %= mod;
		}
		else
		{
			res -= M / k;
			res = (res % mod + mod) % mod;
		}
	}
	return ((M - res) % mod + mod) % mod;
}

signed main()
{
	init();
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld%lld",&n,&m);
		for(int i = 1;i <= n;i++)
			scanf("%lld",&a[i]);
		bool flag = 0;
		int ans = 1;
		for(int i = 2;i <= n;i++)
		{
			if(a[i - 1] % a[i] != 0)
			{
				flag = 1;
				break;
			}
			ans *= get_p(a[i - 1] / a[i],m / a[i]);
			ans %= mod;
		}
		if(!flag)
			printf("%lld\n",ans);
		else
			printf("0\n");
	}
	return 0;
}
```

---

