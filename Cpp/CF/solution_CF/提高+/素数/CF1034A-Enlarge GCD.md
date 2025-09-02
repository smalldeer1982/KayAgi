# Enlarge GCD

## 题目描述

Mr. F has $ n $ positive integers, $ a_1, a_2, \ldots, a_n $ .

He thinks the greatest common divisor of these integers is too small. So he wants to enlarge it by removing some of the integers.

But this problem is too simple for him, so he does not want to do it by himself. If you help him, he will give you some scores in reward.

Your task is to calculate the minimum number of integers you need to remove so that the greatest common divisor of the remaining integers is bigger than that of all integers.

## 说明/提示

In the first example, the greatest common divisor is $ 1 $ in the beginning. You can remove $ 1 $ so that the greatest common divisor is enlarged to $ 2 $ . The answer is $ 1 $ .

In the second example, the greatest common divisor is $ 3 $ in the beginning. You can remove $ 6 $ and $ 9 $ so that the greatest common divisor is enlarged to $ 15 $ . There is no solution which removes only one integer. So the answer is $ 2 $ .

In the third example, there is no solution to enlarge the greatest common divisor. So the answer is $ -1 $ .

## 样例 #1

### 输入

```
3
1 2 4
```

### 输出

```
1```

## 样例 #2

### 输入

```
4
6 9 15 30
```

### 输出

```
2```

## 样例 #3

### 输入

```
3
1 1 1
```

### 输出

```
-1```

# 题解

## 作者：Siyuan (赞：15)

[$$\Large\texttt{My Blog}$$](https://hydingsy.github.io/articles/problem-Codeforces-1034A-Enlarge-GCD/)

---

## Description

> 题目链接：[Codeforces 1034A](https://codeforces.com/contest/1034/problem/A)

Mr. F 现在有 $n$ 个正整数 $a_i$。

他认为这些数的最大公因数太小了，所以他想通过删除其中的一些数来增大这个最大公因数。你的任务是计算出最少的需要删除的数的个数，使得删除之后剩余数的最大公约数大于删除之前的最大公约数。无解输出 $-1$。

数据范围：$2\le n\le 3\times 10^5$，$1\le a_i\le 1.5\times 10^7$

------

## Solution

### 朴素思路

对于最大公约数，我们可以模拟计算的过程，我们写出所有数字的质因子分解式，对于每个小于 $\sqrt{a_i}\approx 4000$ 的质因子，求出其在 $n$ 个数中最小的指数。

那么要使得 $\gcd$ 增大，必须使得其中一个质因子的指数变大，因此我们对于每个质因子，统计等于最小指数的数的个数，答案即为最小值。

但是我们并没有考虑大于 $\sqrt{a_i}$ 的质因子，由于每个数至多只有一个 $>\sqrt {a_i}$ 的质因子，那么我们统计每个大于 $\sqrt{a_i}$ 的质因子个数，记为 $c_i$。如果要使得质因子变大，只需要对 $n-c_i$ 取最小值即可（这里的 $c_i$ 必须满足 $c_i<n$，即 $c_i$ 对原来的最大公约数没有贡献）。

如果 $ans$ 的值为极大值，那么无解。

由于小于 $\sqrt{a_i}$ 的质数个数为 $O\left(\frac{\sqrt{a_i}}{\log a_i}\right)$ 个，分解质因子的复杂度为 $O(\log a_i)$，故总复杂度为 $O(n\sqrt{a_i})$。

**时间复杂度**：$O(n\sqrt{a_i})$

### 优化思路

我们发现，如果把 $a_i$ 都除以 $\gcd(a_1,a_2,\dots,a_n)$，那么此时 $\gcd(a_1,a_2,\dots,a_n)$ 的值就是 $1$ 了，我们的就是使得此时的 $a_i$ 的最大公约数大于 $1$。

很自然地，我们想到可以枚举 $\gcd(a_1,a_2,\dots,a_n)=d$，然后统计这些 $a_i$ 中有多少个 $d$ 的倍数即可。

由于质数的个数有 $O\left(\frac{a_i}{\log a_i}\right)$ 个，枚举倍数的复杂度是调和级数，均摊为 $O(\log a_i)$，那么复杂度为 $O(a_i)$（计算 $\gcd$ 需要 $\log a_i$ 的复杂度）。

**时间复杂度**：$O(a_i)$

------

## Code

### 朴素思路

```cpp
#include <cstdio>
#include <cstring>
#include <map>

const int N=3e5+5;
int n,a[N],tot,p[N],mn[N],cnt[N],rcnt[N];
bool flg[N];
std::map<int,int> mp;

void sieve(int n) {
	for(int i=2;i<=n;++i) {
		if(!flg[i]) p[++tot]=i;
		for(int j=1;j<=tot&&i*p[j]<=n;++j) {
			flg[i*p[j]]=1;
			if(i%p[j]==0) break;
		}
	}
}
int getcnt(int &x,int p) {
	int ans=0;
	while(x%p==0) x/=p,++ans;
	return ans;
}
void solve() {
	memset(mn,0x3f,sizeof(mn));
	int idx=0;
	for(int i=1;i<=n;++i) {
		for(int j=1;j<=tot;++j) {
			int c=getcnt(a[i],p[j]);
			if(mn[j]>c) mn[j]=c,cnt[j]=1;
			else if(mn[j]==c) ++cnt[j];
		}
		if(a[i]>1) {
			if(!mp[a[i]]) mp[a[i]]=++idx;
			++rcnt[mp[a[i]]];
		}
	}
	int ans=n;
	for(int i=1;i<=tot;++i) ans=std::min(ans,cnt[i]);
	for(int i=1;i<=idx;++i) ans=std::min(ans,n-rcnt[i]>0?n-rcnt[i]:n);
	printf("%d\n",ans==n?-1:ans);
}
int main() {
	sieve(4000);
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%d",&a[i]);
	solve();
	return 0;
}
```

### 优化思路

```cpp
#include <cstdio>
#include <algorithm>

const int N=3e5+5,M=1.5e7+5;
int n,tot,a[N],p[M/10],cnt[M];
bool flg[M];

void sieve(int n) {
	for(int i=2;i<=n;++i) {
		if(!flg[i]) p[++tot]=i;
		for(int j=1;j<=tot&&i*p[j]<=n;++j) {
			flg[i*p[j]]=1;
			if(i%p[j]==0) break;
		}
	}
}
int gcd(int x,int y) {
	return y?gcd(y,x%y):x;
}
int main() {
	scanf("%d",&n);
	int d=0,mx=0;
	for(int i=1;i<=n;++i) scanf("%d",&a[i]),d=gcd(d,a[i]);
	for(int i=1;i<=n;++i) a[i]/=d,mx=std::max(mx,a[i]),++cnt[a[i]];
	sieve(mx);
	int ans=n;
	for(int i=1;i<=tot;++i) {
		int x=p[i],num=0;
		for(int j=x;j<=mx;j+=x) num+=cnt[j];
		if(num) ans=std::min(ans,n-num);
	}
	printf("%d\n",ans==n?-1:ans);
	return 0;
}
```



---

## 作者：Acc_Robin (赞：9)

**大概上一篇题解的复杂度分析有点问题.**

我们发现，如果令

$$
d=\gcd(a_1,a_2,\cdots,a_n)
$$

然后把原序列中每一个数都除以$d$，那么新序列

$$
\frac{a_1}d,\frac{a_2}d,\cdots ,\frac{a_n}d
$$

的最大公约数就是$1$，我们的任务转化为**去掉尽可能少的数让新序列的最大公约数大于$1$**.

我们枚举每一个素数，一个素数的倍数的个数就是我们需要留下的元素，也就是说$n-$素数倍数的个数就是最终的答案，我们需要最小化它.

筛出新序列值域内的每一个素数并枚举倍数，这个复杂度有点麻烦，是

$$
\sum_{p\in prime}\frac mp
$$
$$
=m\sum_{p\in prime}\frac1p
$$
$$
=m\ln\ln m+O(1)
$$
$$
=O(m\log\log m)
$$

其中，
$$
m=\max(\frac{a_1}d,\frac{a_2}d,\cdots ,\frac{a_n}d)
$$

于是本题就愉快的结束辣！
```cpp
#include<cstdio>
#include<algorithm>
namespace Acc{
	const int N = 3e5+10;
	const int M = 1.5e7+10;
	int a[N],d,p[M],np[M],n,cnt,buc[M],mx,ans;
	void sieve(int n){
		np[0]=np[1]=1;
		for(int i=2;i<=n;i++){
			if(!np[i])p[++cnt]=i;
			for(int j=1;j<=cnt && p[j]*i<=n;j++){
				np[i*p[j]]=1;
				if(i%p[j]==0)break;
			}
		}
	}
	void work(){
		scanf("%d",&n);
		for(int i=1;i<=n;i++)scanf("%d",&a[i]),d=std::__gcd(a[i],d);
		for(int i=1;i<=n;i++)a[i]/=d,mx=std::max(mx,a[i]),buc[a[i]]++;
		sieve(mx);ans=n;
		for(int i=1;i<=cnt;i++){
			int res=0;
			for(int j=1;p[i]*j<=mx;j++) res+=buc[p[i]*j];
			if(res) ans=std::max(ans,res);
		}
		printf("%d\n",ans==0?-1:n-ans);
	}
}
int main(){
	return Acc::work(),0;
}
```

---

## 作者：Npse_D (赞：8)

良好利用埃筛特性QAQ

首先都除以当前gcd，肯定的。

统计一下除后每个数出现了几次。

考虑除掉很多数，让gcd变化，那么肯定变化后的gcd是一个质数。可以用反证法证明。

最后，如果出现过这个数，在埃筛里i的倍数一定能遍历到j，定义h为这个质因子h直接加上j的出现次数。

质因子的出现次数就是在n中多少数有这个质因子，我们把没有这个质因子的数去掉就是保证这个质因子是公因子之一的方法。

去掉的数的个数显然是n-质因子出现次数。

最后取min即可。
```
#include<bits/stdc++.h>
using namespace std;
int gcd(int a,int b){return b?gcd(b,a%b):a;};
int n,a[300005],inf,gdk,c[15000005],t=0x3f7f7f7f;
bool vis[15000005];
int main(){
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)gdk=gcd(a[i],gdk);
	for(int i=1;i<=n;i++)c[a[i]/gdk]++,inf=max(inf,a[i]/gdk);
	for(int i=2;i<=inf;i++){
		int h=0;
		if(!vis[i])for(int j=i;j<=inf;j+=i)vis[j]=1,h+=c[j];
		t=min(t,n-h);
	}
	(t==0x3f7f7f7f)?cout<<-1<<endl:cout<<t<<endl; 
	return 0;
}
```

---

## 作者：Zimo_666 (赞：3)

# [CF1034A] Enlarge GCD

### Description

给一个序列，求最小化删掉多少个数，使得他们的 $\gcd$ 变大。

### Solution

我们首先考虑把所有数先除掉他们的 $\gcd$，因为 $\gcd$ 不能影响答案，反而会使值域变大。现在所有数的 $\gcd$ 都是 $1$ 了，那么我们考虑把这个值变得大于 $1$。

而后我们在值域中筛出所有素数，枚举每个素数，求出每个含有素数倍数个数 $ans$，答案为 $n-\max(ans)$。

如果 $\max(ans)=0$，输出 `-1`。

复杂度 $O(m\log\log m)$，$m$ 为筛后的值域。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+7;
const int M=1.5e7+7;

int a[N],g,prm[M],n,cnt,buc[M],maxx,ans;
bool isprm[M];

void p(int n){
  isprm[0]=1,isprm[1]=1;
  for(int i=2;i<=n;i++){
    if(!isprm[i]) prm[++cnt]=i;
    for(int j=1;j<=cnt&&i*prm[j]<=n;j++){
      isprm[i*prm[j]]=1;
      if(i%prm[j]==0) break;
    }
  }
}

void solve(){
  scanf("%d",&n);
  for(int i=1;i<=n;i++) scanf("%d",&a[i]),g=__gcd(a[i],g);
  for(int i=1;i<=n;i++) a[i]/=g,maxx=max(a[i],maxx),buc[a[i]]++;
  p(maxx);
  for(int i=1;i<=cnt;i++){
    int res=0;
    for(int j=1;prm[i]*j<=maxx;j++) res+=buc[prm[i]*j];
    if(res) ans=max(ans,res);
  }
  printf("%d\n",ans==0?-1:n-ans);
}

int main(){solve();return 0;}
```



---

## 作者：cxy000 (赞：2)

看到这道题的翻译首先我们会想到一个问题：

如果说总的公约数不为 $1$（如 $3$ ，$9$， $6$ 为 $3$）的话要怎么做。

其实将它们都除掉即可。

就是这样：

```cpp
for(int i=1;i<=n;i++){
   aa[i]/=ppp;
   cc[aa[i]]++;
}
```

那么接下来怎么做呢？

用 $b$ 数组计算每个质数的倍数的个数。

然后枚举出最小值 $minn$。

几乎没有问题了。

可以上代码了：

```cpp
#include <bits/stdc++.h>
using namespace std;
bool blog[100000001];
int aa[15000100];
int cc[15000100];
int main(){
	int n;
	cin>>n;
	int pp=0;
	bool ooo=1;//这是特判，下面不需要判断了
	for(int i=1;i<=n;i++){
		cin>>aa[i];
		pp=max(aa[i],pp);
	}
	int ppp=aa[1];
	for(int i=2;i<=n;i++){
		if(aa[i]!=aa[i-1]) ooo=0;
		ppp=__gcd(ppp,aa[i]);//枚举刚刚开始时的公约数
	}
	if(ooo==1){
		cout<<"-1";
		return 0;
	}
	for(int i=1;i<=n;i++){
		aa[i]/=ppp;
		cc[aa[i]]++;//相当于一个vis
	}
	pp/=ppp;
	int kkk=0x7f7f7f7f;//初始化大一点没有问题
	for(int i=2;i<=pp;i++){
		int hh=0;
		if(!blog[i]) for(int j=i;j<=pp;j+=i) blog[j]=1,hh+=cc[j];
		kkk=min(kkk,n-hh);//取最小值
	}
	cout<<kkk<<endl;
	return 0;
}
//
//[1] 10=2*5
//
```


---

## 作者：ncwzdlsd (赞：1)

因为题中要找到的最大公因数是大于原来的最大公因数的，所以我们考虑消除原最大公因数的影响，把序列中的每一项除以原 $\gcd$，这样新序列的最大公因数就是 $1$，于是问题就变成删掉一些数使序列的 $\gcd$ 大于 $1$。

对于新序列的 $\gcd$，我们考虑这个 $\gcd$ 为质数一定比为合数更优，因为对于任意一个合数将它分解质因数之后，对于得到的一个质因子，删去一些数之后使新序列的 $\gcd$ 为该质因子时需要删去的数的数量一定更少。

我们统计对于每个质数，在这个新序列中它的倍数出现了多少次，比较保留这些数需要删除的数的个数，取最小值即可。

考虑筛选质数+统计次数的思想，可以用埃氏筛来解决。

求原序列的 $\gcd$ 时间复杂度为 $O(n)$，埃氏筛时间复杂度为 $O(n\log\log n)$。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

const int maxn=3e5+5,maxm=1.5e7+5;
int a[maxn],cnt[maxm];
bool vis[maxm];

int gcd(int a,int b){return b?gcd(b,a%b):a;}

signed main()
{
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	int n;cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	int g=a[1];
	for(int i=2;i<=n;i++) g=gcd(g,a[i]);
	for(int i=1;i<=n;i++) a[i]/=g,cnt[a[i]]++;
	int mx=0/*mx记录新序列最大值*/;
	for(int i=1;i<=n;i++) mx=max(mx,a[i]);
	int ans=0x3f3f3f;
	for(int i=2;i<=mx;i++)
	{
		int tmp=0;
		if(!vis[i]){for(int j=1;j<=mx/i;j++) vis[j*i]=1/*筛质数*/,tmp+=cnt[j*i]/*统计筛出的质数的出现次数*/;}
		ans=min(ans,n-tmp);
	}
	if(ans==0x3f3f3f) cout<<-1;
	else cout<<ans;
	return 0;
}
```

---

## 作者：loser_seele (赞：1)

为什么没有时间复杂度正确的暴力思路呢。

考虑暴力怎么做：模拟计算 gcd 的过程，分解出所有质因子，然后枚举质因子，设有 $ a $ 个数有这个质因子，那么一个方案的代价显然是 $ n-a $，最后在所有方案里面取最小值即可。

于是问题转化为了如何快速分解质因子，朴素暴力显然难以卡进时间限制，我们考虑线性筛预处理出所有数的最小质因子，记为 $ minp $，然后每次不断执行 $ x=minp_x $ 就得到了质因子分解，因为质因子的个数是 $ \log $ 级别的，所以这个做法的时间复杂度为 $ \mathcal{O}(n\log \max a_i) $，可以通过。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=1.5e7+20;
const int N=3e5+20;
const int M=maxn;
signed primes[maxn],minp[maxn],cnt;
bitset<maxn>st;
void pre(int n)
{
	for(int i = 2 ; i <= n ; i++)
	{
		if(!st[i]) 
		minp[i] = i,primes[cnt++] = i;
		for(int j = 0 ; primes[j] * i <= n ;j++)
		{
			int t = primes[j] * i;
			st[t] = true;
			minp[t] = primes[j];
			if(i % primes[j] == 0) 
            break;
		}
	}
}
signed n,ans=1e9,a[N],vis[M];
int gcd(int a,int b)
{
    return b?gcd(b,a%b):a;
}
signed main()
{
    pre(1.5e7);
	scanf("%d",&n);
	int res=0;
	for(int i=1;i<=n;i++)
    scanf("%d",&a[i]),res=gcd(res,a[i]);
	for(int i=1;i<=n;i++)
	{
		int x=a[i]/res;
		set<int>d;
        while(x>1)
        d.insert(minp[x]),x/=minp[x];
		for(auto x:d)
		vis[x]++;
	}
	for(int i=1;i<=1.5e7;i++)
    if(vis[i]&&vis[i]!=n)
    ans=min(ans,n-vis[i]);
	if(ans>n)
    printf("-1");
	else 
    printf("%d",ans);
}
```


---

## 作者：kimi0705 (赞：1)

# Enlarge GCD

## 题意

给你 $n$ 个数，去掉尽量少的数使得剩下数的 $\gcd$ 比原来的大。无解输出 `-1`。

## 思路

- 首先将每个数都除以 $\gcd_{i=1}^{n}a_i$。
- 显然的，变化后的 $\gcd$ 肯定是一个**素数**。
- 枚举这个**素数**。
  * 再用筛素数的方法进行**筛**素数 & 统计是这个**素数**的倍数有几个(**就是不用删的**)
  * 在比较答案:`ans = min(ans, n - cnt);`
  
## code

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, Gcd, cnt[15000005], Maxx, ans = INT_MAX;
bool vis[15000005];
vector <int> V;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	V.resize(n);
	for (int &i : V)cin >> i;
	for (int i : V) Gcd = __gcd(Gcd, i);
	for (int &i : V) i /= Gcd, cnt[i]++;
	for (int i : V) Maxx = max(Maxx, i);
	for (int i = 2; i <= Maxx; i++) {
		int Cnt = 0;
		if (!vis[i]) {
			for (int j = i; j <= Maxx; j += i) {
				vis[j] = 1;							// 筛素数
				Cnt += cnt[j];						// 统计
			}
			ans = min(ans, n - Cnt);
		}
	}
	if(ans == INT_MAX) cout << -1;
	else cout << ans;
}
```

---

## 作者：cppcppcpp3 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1034A)。


## Solution

先求出 $g=\gcd\limits_{i=1}^{n} a_i$，由于要使得最终的 $\gcd$ 更大，所以不用考虑 $g$ 这一部分，$a_i \leftarrow \frac{a_i}{g}$。

接下来其实只需要找到一个质数 $p$，使最多的 $a_i$ 是它的倍数，这样去掉的数就相应越少。

所以对新的 $a_i$ 进行质因数分解，开个桶 $tot_i$ 表示质数 $i$ 在 $a$ 中的倍数个数。设 $ans=\max\limits_{i=1}^{maxn}tot_i$（其中 $maxn=\max a_i$），若 $ans=0$，说明找不到 $p$，输出 $-1$；否则答案就是 $n-ans$。

现在的问题只在于怎么质因数分解。如果直接暴力枚举质数，将会有 $O(n\log maxn)$ 的复杂度，注意 $n\le 3 \times 10^5$，$maxn \le 1.5 \times 10^7$，显然会超时。

所以我们要用一种更快速的方法：线性筛。在筛 $\le maxn$ 的质数过程中，同时标记 $f_{i \times p_j}=p_j$，即记录每个数的最小质因数。之后在分解 $a_i$ 时，不断执行 $a_i \leftarrow \frac{a_i}{f_{a_i}}$ 即可。

最终，复杂度大概是 $O(maxn+n \log maxn)$ 级别的。

```cpp
#include<bits/stdc++.h>
#define il inline
#define eb emplace_back
using namespace std;
const int N=3e5+5;
const int M=1.5e7+3;

il int wrd(){
	int x=0,f=1; char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=x*10+c-48;c=getchar();}
	return x*f;
}

int n,a[N],g,maxn,ans;

vector<int> p,v[N];
int f[M],tot[M];

void init(int n){
	for(int i=2;i<=n;++i){
		if(!f[i]) p.eb(i),f[i]=i;
		for(int j=0;j<(int)p.size() && i*p[j]<=n;++j){
			f[i*p[j]]=p[j];
			if(i%p[j]==0) break;
		}
	} 
}

void prime(int x){
	int lst=0;
	while(a[x]^1){
		if(lst^f[a[x]]) lst=f[a[x]],++tot[lst];
		a[x]/=f[a[x]];
	}
}

main(){
	n=wrd();
	for(int i=1;i<=n;++i) a[i]=wrd();
	for(int i=1;i<=n;++i) !g ? g=a[i] : g=__gcd(g,a[i]);
	for(int i=1;i<=n;++i) a[i]/=g,maxn=max(maxn,a[i]);
	
	init(maxn);
	for(int i=1;i<=n;++i) prime(i);
	for(int i=1;i<=maxn;++i) ans=max(ans,tot[i]);	
	return printf("%d",ans ? n-ans : -1),0;
}
```

---

## 作者：gdf_yhm (赞：0)

[CF1034A](https://www.luogu.com.cn/problem/CF1034A)

[Enlarge GCD](https://codeforces.com/contest/1034/problem/A)

### 思路

先对 $a_i$ 求 $\operatorname{gcd}$。$g$ 表示数组的 $\operatorname{gcd}$。

每个 $a_i$ 除以 $g$。要找出一个质数，使得有最多的除以 $g$ 后的 $a_i$ 整除该质数。对 $a_i$ 做质因数分解，舍去重复的质数因子，加入桶中。最后枚举答案 $ans=\min {n-t_i}$，$n-t_i$ 即要删除的数的个数。

正常情况下的质因数分解复杂度是 $O(\sqrt {a_i})$，总时间复杂度 $O(n\times \sqrt {a_i})$，$3.5\times 10^5\times 4\times 10^3=1.4\times 10^9$，不可接受。

对 $\max a_i$ 内的质数做素数筛，复杂度 $O(a_i)$。在素数筛向后转移的同时，标记 $vis_{i\times pre_j}$ 为 $1$ 时，记录 $f_{i\times pre_j}=pre_j$，即 $i\times pre_j$ 有一个质因数 $pre_j$。对 $x$ 做质因数分解时，$x$ 不断除以 $f_x$ 直到 $x=1$。在分解过程中，所有的 $f_x$ 即 $x$ 的质因数。因为 $a_i$ 最多有 $\log a_i$ 质因子，所以总复杂度 $O(n\log a_i+a_i)$，可以接受。

### code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=300010;
const int maxm=15000010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,a[maxn],g,ans=inf,mx;
bool vis[maxm];
int pre[maxn],cnt;
int f[maxm],t[maxm];
void s(int n){
	for(int i=2;i<=n;i++){
		if(!vis[i]){
			pre[++cnt]=i;
			f[i]=i;
		}
		for(int j=1;j<=cnt&&i*pre[j]<=n;j++){
			f[i*pre[j]]=pre[j];
			vis[i*pre[j]]=1;
			if(i%pre[j]==0)break;
		}
	}
}

signed main(){
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		if(i==1)g=a[1];
		else g=__gcd(g,a[i]);
	}
	for(int i=1;i<=n;i++){
		a[i]/=g;
		mx=max(mx,a[i]);
	}
	s(mx);
	for(int i=1;i<=n;i++){
		int lst=0;
		while(a[i]!=1){
			if(lst!=f[a[i]]){
				lst=f[a[i]];
				t[lst]++;
			}
			a[i]/=f[a[i]];
		}
	}
	for(int i=1;i<=mx;i++)ans=min(ans,n-t[i]);
	if(ans==n)printf("-1\n");
	else printf("%d\n",ans); 
}
```


---

## 作者：Gmt丶FFF (赞：0)

#### 题意简述：

删去最少的数使所有的数的 $\text{gcd}$ 增加。

#### 解：

先对每个数除以所有数的 $\text{gcd}$，然后剩下的需要找到所有数的质因子，找到一个最多的序列中数拥有的质因子，那么答案就是总数减去拥有这个质因子的数的个数。

用质数筛先预处理，再进行质因子分解，最后取最值即可。

判 $-1$ 就判断所有数是否都为 $1$ 就行。

时间复杂度：$O(\max(a_i))$。

```cpp
#include<iostream>
#include<cstdio>
#include<map>
#include<ctime>
using namespace std;
const int N=3e5+5;
const int M=15e6+5;
map<int,int>mp;
int n,ans=1e9,a[N],vis[M],num[M],cnt,pri[M];
int gcd(int x,int y)
{
	if(y==0)return x;
	return gcd(y,x%y);
}
int main()
{
	//freopen("gcd.in","r",stdin);
	//freopen("gcd.out","w",stdout);
	scanf("%d",&n);
	for(int i=2;i<=M-5;i++)
	{
		if(!pri[i])num[++cnt]=i;
		for(int j=1;j<=cnt&&num[j]*i<=M-5;j++)
		{
			pri[num[j]*i]=1;
			if(i%num[j]==0)break; 
		}
	}
	int res=0;
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),res=gcd(res,a[i]);
	for(int i=1;i<=n;i++)
	{
		int x=a[i]/res;
		for(int j=1;num[j]*num[j]<=x;j++)
		{
			if(x%num[j]==0)
			{
				vis[num[j]]++;
				while(x%num[j]==0)x/=num[j];
			}
		}
		if(x!=1)vis[x]++;
	}
	for(int i=1;i<=M-5;i++)if(vis[i]&&vis[i]!=n)ans=min(ans,n-vis[i]);
	if(ans>n)printf("-1");
	else printf("%d",ans);
	return 0;
}
```


---

