# [EC Final 2020] Square

## 题目描述

Father Study 非常喜欢数学。

给定一个整数序列 $a_1,a_2,...,a_n$，Father Study 想要计算另一个整数序列 $t_1,t_2,...,t_n$，满足以下条件：
- 对于每个 $i~(1 \le i \le n)$，有 $t_i > 0$。
- 对于每个 $i~(1\le i < n)$，$a_i \times t_i \times a_{i+1} \times t_{i+1}$ 是一个完全平方数。（在数学中，完全平方数是一个整数，它是某个整数的平方，换句话说，它是某个整数与其自身的乘积。）
- $\prod_{i=1}^{n}{t_i}$ 的值最小。


请帮助 Father Study 计算答案，即 $\prod_{i=1}^{n}{t_i}$ 的最小值。由于答案可能过大，请输出答案对 $1000000007$ 取模的结果。


## 说明/提示

（由 ChatGPT 4o 翻译）

## 样例 #1

### 输入

```
3
2 3 6```

### 输出

```
6```

# 题解

## 作者：fede (赞：7)

# 前言

~~各位大佬写的题解稍稍有些有些简短，有些细节没有点到（看不到我），特来发篇题解~~(〃´-ω･)

此外，向管理员大大致歉，因对LaTeX使用不太熟练与未能对题解进行检查，~~一不小心~~添加了多余的积分符号（现已更正），造成还需管理员大大重新审核的严重后果，在此庄重宣布：   
**管理员大大，对不起！我错了！○|￣|_**

# 正文

## 分析

首先简单理解一下题意：

创造一个 $t$ 序列，对于每个 $i~(1\le i<n)$ 满足 $a_i\times t_i\times a_{i+1}\times t_{i+1}$ 为完全平方数，求出序列 $t$ 中所有值的乘积最小($\prod_{i=1}^{n}{t_i}$)。

设完全平方数为 $x$，则一定可以写成 $x=y^2$ 的形式。   
对 $y$ 进行质因子分解，设指数为 $k$，可以写成   
$$
\textstyle y=P_1^{k_1}\times P_2^{k_2}\times P_3^{k_3}\times …
$$
可得    
$$
\textstyle x=y^2=(P_1^{k_1}\times P_2^{k_2}\times P_3^{k_3}\times …)^2
$$
$$
\textstyle =(P_1^{k_1}\times P_1^{k_1})\times (P_2^{k_2}\times P_2^{k_2})\times (P_3^{k_3}\times P_3^{k_3})\times …
$$
$$
\textstyle =P_1^{k_1+k_1}\times P_2^{k_2+k_2}\times P_3^{k_3+k_3}\times …
$$   
若 $k$ 为奇数，则 $k+k$ 为偶数，若 $k$ 为偶数，则 $k+k$ 为偶数。

由此得出结论，**完全平方数的质因子分解的每项指数都为偶数。**

把 $a_i*a_{i+1}$ 看成一个整体 $b_i$。   
如果 $b_i$ 要变成完全平方数，则一定要让 $b_i$ 的所有质因子的指数变为偶数，所以序列 $t$ 要做的就是为 $b_i$ 乘上指数为奇数的质因子。

对每个 $a_i$ 分解质因数，记录每个质因数的指数，如果指数为奇数，则 $a_i$ 需要乘上这个质因数。   
但是有一个问题，$a_i$ 乘上数是会影响 $a_{i-1}$ 的，每个 $a_i$ 都乘上质因子，答案不会最优。

因为只要知道 $\prod_{i=1}^{n}{t_i}$，考虑对每个出现过的质因数分开讨论，统计好质因数指数为奇数的次数（~~好绕~~）。

设 $cnt_{i}$ 表示质因数 $i$ 指数为奇数的次数，两种可能：
- 如果质因数 $i$ 的指数都为偶数，则 $cnt_{i}$ 为 $0$，此时不用做任何操作。
- 如果质因数 $i$ 的指数有为奇数的，则 $cnt_{i}$ 不为 $0$，此时有两种选择：一、将所有质因数 $i$ 的指数为奇数的数都乘上质因数 $i$，让质因数 $i$ 的指数都为偶数；二、将所有质因数 $i$ 的指数为不为奇数的数都乘上质因数 $i$，让所有数都有质因数 $i$ 并将质因数 $i$ 的指数都为奇数。

嗯 (⊙o⊙)… 。非常抽象，我们设 $ans$ 表示 $\prod_{i=1}^{n}{t_i}$ ，再做一个详细的剖析：

对于第一种可能，简单直白，不做任何操作，$ans$ 不变。

对于第二种可能，举个栗子![](https://img.lanxixiaowu.com/data/attachment/forum/201807/31/101906pt8uf14ttmttfmdx.gif)   
我们假设 $a$ 序列有数 $2,3,6,9$:   
对于质因数 $2$，$2$ 有质因数 $2$ 且指数为 $1$（奇数），$6$ 有质因数 $2$ 且指数为 $1$（奇数），所以 $cnt_2$ 为 $2$；   
对于质因数 $3$，$3$ 有质因数 $3$ 且指数为 $1$（奇数），$6$ 有质因数 $3$ 且指数为 $1$（奇数），$9$ 有质因数 $3$ 且指数为 $2$（偶数），所以 $cnt_3$ 为 $2$。   
为了将 $2\times 3$、 $3\times 6$、 $6\times 9$ 变为完全平方数，我们可以给 $2$ 乘上质因数 $2$，给 $3$ 乘上质因数 $3$，给 $6$ 乘上质因数 $2$ 和 $3$，所得答案为 $36$。   

我们再假设 $a$ 序列有数 $2,3,6,8$:   
对于质因数 $2$，$2$ 有质因数 $2$ 且指数为 $1$（奇数），$6$ 有质因数 $2$ 且指数为 $1$（奇数），所以 $cnt_2$ 为 $2$；   
对于质因数 $3$，$3$ 有质因数 $3$ 且指数为 $1$（奇数），$6$ 有质因数 $3$ 且指数为 $1$（奇数），$8$ 有质因数 $2$ 且指数为 $3$（奇数），所以 $cnt_3$ 为 $2$。   
为了将 $2\times 3$、 $3\times 6$、 $6\times 8$ 变为完全平方数，我们可以给 $2$ 乘上质因数 $2$，给 $3$ 乘上质因数 $3$，给 $6$ 乘上质因数 $2$ 和 $3$，给 $8$ 乘上质因数 $2$，所得答案为 $72$，但显然不是最优。   
为了最优，我们还可以给 $2$ 乘上质因数 $3$，给 $3$ 乘上质因数 $2$，给 $8$ 乘上质因数 $3$，所得答案为 $18$。

有质因数2指数为奇数的数有 $2$、$6$、$8$，为了变为完全平方数，这些数都得乘上质因数 $2$，但最优解却是给 $3$ 乘上质因数 $2$，这是为什么呢？

**可以这么做的原因是 $a_i$ 势必会影响到 $a_{i-1}$，所以说如果 $a_i$ 质因数p的指数为奇数，且 $a_{i-1}$ 质因数 $p$ 的指数也为奇数，那么两者相乘积的质因数 $p$ 的指数一定为偶数，也可以达到我们需要的要求，但答案 $b$ 序列所以值都是有关联的，因此要么质因数 $p$ 指数为奇数的数都乘 $p$，要么让所有质因数 $p$ 指数不为奇数的数(包括没有质因数 $p$）都乘 $p$。**

## 思路

开始的时候预处理好范围内所有数分解出来的质因子的指数，放进 $\operatorname{map}$ 里，可以选择**埃氏筛法**，好理解又好写，时间复杂度为 $O(n\log n)$。

之后，对于每个输入的 $a_i$，从 $\operatorname{map}$ 里取出质因数 $p$ 和对应的指数，如果指数为奇数，$cnt_p$ 增加 $1$。

然后，我们再遍历所有的质因数，如果指数都为偶数或没有出现，也就是 $cnt_p=0$，那么找下一个出现过的质因数；否则考虑两种选择，将所有质因数 $p$ 指数为奇数的数都乘 $p$，也就是 $ans=ans\times p^{cnt_p}$，或者将所有质因数 $p$ 指数不为奇数的数(包括没有质因数 $p$）都乘 $p$，也就是 $ans=ans\times p^{n-cnt_p}$。

最后，输出答案 $ans$，此题拿下。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;
const int N=1e6+10;
const int mod=1e9+7;
int n,ans=1;
int a[N],cnt[N];
map<int,int> mp[N];
bool isp[N];
int ksm(int a,int b,int c){
	if(b==0) return 1%c;
	if(b==1) return a%c;
	int t=ksm(a,b/2,c);
	if(b%2==0) return t*t%c;
	return t*t%c*a%c;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	for(int i=2;i<=1e6;i++){
		if(isp[i]){
			continue;
		}
		for(int j=i;j<=1e6;j+=i){
			isp[j]=1;
			int x=j;
			while(x%i==0){
				mp[j][i]++;
				x/=i;
			}
		} 
		isp[i]=0;
	}
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		for(map<int,int>::iterator it=mp[a[i]].begin();it!=mp[a[i]].end();it++){
			int x=it->first,y=it->second;
			if(y%2!=0){
				cnt[x]++;
			}
		}
	}
	for(int i=2;i<=1e6;i++){
		if(isp[i]){
			continue;
		}
		if(cnt[i]!=0&&cnt[i]<n){
			ans=ans*ksm(i,min(cnt[i],n-cnt[i]),mod)%mod;
		}
	}
	cout<<ans<<endl;
	return 0;
}
```
时间复杂度 $O(n\log n)$，空间复杂度 $O(n\log n)$，完美通过此题。

---

## 作者：Barryb (赞：5)

# 大意
在 $a_i\times t_i\times a_{i+1}\times t_{i+1}$ 是完全平方数的基础上求 $$\prod_{i=1}^{n}{t_i}$$ 的最小值。
# 思路
分解个质因数，用计数器垒加起来。然后用快速幂求一下指数的两种情况，取个最小值，再把每个一因子乘起来输出就好。
# 指数讨论
- 如果 $cnt_a$ 为奇数，答案是 $cnt_a$。
- 否则答案就是 $n - cnt_a$。
# 核心代码

```cpp
#define int long long
void isprime_cnt(int x){
	for(int i=2;i*i<=x;i++) {
		int sum=0;
		while(x%i==0) x/=i,sum++;
		sum%=2,cnt[i]+=sum;
	}
	if(x>1) cnt[x]++;
	return ;
}
int power_mod(int a,int b) {
    int res=1;
    while(b) {
        if(b&1) res=res*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return res;
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) {
		cin>>x;
		isprime_cnt(x);
	}
	for(int i=1;i<=1000000;i++)
		if(cnt[i]>0) ans=ans*power_mod(i,min(cnt[i],n-cnt[i]))%mod;
	cout<<ans;
	return 0;
}
```

---

## 作者：wrh316 (赞：4)

### 题目大意
有 $n$ 个数字，分别为 $a _ {1} \sim a _ {n}$，求 $n$ 个数字：$t _ {1} \sim t _ {n}$，满足 $a _ {i} \times t _ {i} \times a _ {i + 1} \times t _ {i + 1}（1 \le i \ ＜ \ n）$为平方数。求 $$\prod_{i=1}^{n}{t_i}$$ 的最小值。
### 思路
在每一个 $a _ {i} \times t _ {i}$ 中：出现的每一个质因子的指数如果不是都是奇数的话，就都是偶数。那么就可以对这两种情况分别计算，然后取两种操作的最小值。

其实这道题不需要用欧拉筛找质因子，大体思路和 [sheryang_CE 的题解](https://www.luogu.com.cn/article/4zyo01gq) 一样，只不过分解质因数做法不同。
### 代码
```c++
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e6 + 10,mod = 1e9 + 7;
ll n,ans = 1;
ll cnt[N];
void calc(ll idx){
	for(ll i = 2;i <= sqrt(idx);i++){
		ll sum = 0;
		while(idx % i == 0){
			idx /= i;
			sum++;
		}
		sum %= 2;
		cnt[i] += sum;
	}
	if(idx > 1) cnt[idx]++;
	return ;
}
ll quickpow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i = 1,x;i <= n;i++){
		cin>>x;
		calc(x);
	}
	for(int i = 1;i < N;i++){
		if(cnt[i]) ans = ans * quickpow(i,min(cnt[i],n - cnt[i])) % mod;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Ahws_rwhy (赞：2)

前置知识：欧拉筛。

其实这题就是因数分解。将一个质数 $p$ 分解成质因数。

应对每次位置的 $x$ （$x$ 为质因数），算一下其作 $p$ 的指数是多少。如果是奇数，就用数组记录，并加 $1$；若是偶数。取 $2$ 种操作，取最小值，并记录，最后乘起来就是答案。

核心代码：

```
 for (int j = 0 ; j < prime && p[j] * p[j] <= a[i]; j++) {
			if(a[i] % p[j] == 0) {
				int s = 0;
				while(a[i] % p[j] == 0) {
					a[i] /= p[j];
					s++;
				}
				if(s % 2 == 1) b[p[j]]++;
			}
		}
		if(a[i] != 1) {
			b[a[i]]++;
		}
	}
 for(int i = 2; i <= 1e6; i++) {
 	ans = ans * qpow(i , min(b[i] , n - b[i])) % mod;
 }
```

---

## 作者：Hadtsti (赞：1)

### 题意简述

给定长为 $n(1\le n\le 10^5)$ 的正整数序列 $a_i(1\le a_i\le 10^6)$。现在需要构造一个同样长为 $n$ 的正整数数列 $b_i$，使得 $\forall 1\le i<n$，满足 $a_i\times a_{i+1}\times b_i\times b_{i+1}$ 为完全平方数，且 $\prod\limits_{i=1}^n b_i$ 最小。

### 题目分析

不难发现一个正整数 $x$ 是完全平方数的充分必要条件是它的质因数分解中所有指数皆为偶数。故我们把 $a_i$ 的质因数分开考虑。

设 $c_{i,j}$ 为 $a_j$ 质因数分解中 $i$ 对应的指数， $d_{i,j}$ 为 $b_j$ 质因数分解中 $i$ 对应的指数。那么题目条件即对所有的质数 $i$ 和 $1\le j<n$ ，满足 $c_{i,j}+c_{i,j+1}+d_{i,j}+d_{i,j+1}≡0\pmod 2$。注意到式子对 $2$ 取模，故我们只需要关注 $c,d$ 对 $2$ 取模的值。

那我们改一下 $c_{i,j},d_{i,j}$ 的定义为对应指数对 $2$ 取模的值。则有 $c_{i,j}\oplus d_{i,j}\oplus c_{i,j+1}\oplus d_{i,j+1}=0$。由于 $c_{i,j},c_{i+1,j}$ 是定值，故我们一确定 $d_{i,1}$ 就可以确定其它的 $d_{i,j}$。

考虑到我们让 $b_i$ 尽可能小，我们直接让原指数取 $0$ 或 $1$ 即可。要让乘积小，我们应让指数之和尽可能小。注意到对所有 $1\le j\le n$，$d_{i,j}=d_{i,1}\oplus c_{i,1}\oplus c_{i,j}$，故 $d_{i,j}$ 中 $1$ 的个数等同于 $d_{i,1}\oplus c_{i,1}\oplus c_{i,j}$ 中 $1$ 的个数。那么我们直接看一下 $c_{i,j}$ 中是 $0$ 更少还是 $1$ 更少，取数量少的就是最优贡献。具体实现见代码。

### 代码实现


```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1000000007;
int n,x,ans=1,sum[1000010];
int p[1010],cnt;
bitset<1010>S;
int power(int a,int b)
{
	int res=1;
	for(;b;b>>=1)
	{
		if(b&1)
			res=1ll*res*a%mod;
		a=1ll*a*a%mod;
	}
	return res;
}
int main()
{
	for(int i=2;i<=1000;i++)
		if(!S[i])
		{
			p[++cnt]=i;
			for(int j=i;j<=1000/i;j++)
				S[i*j]=1;
		}
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&x);
		for(int j=1;j<=cnt&&p[j]<=x/p[j];j++)
			if(x%p[j]==0)
			{
				int ct=0;
				while(x%p[j]==0)
				{
					ct++;
					x/=p[j];
				}
				sum[p[j]]+=(ct&1);
			}
		if(x>1)
			sum[x]++;
	}
	for(int i=2;i<=1000000;i++)
		ans=1ll*ans*power(i,min(sum[i],n-sum[i]))%mod;
	printf("%d",ans);
	return 0;
}
```

---

## 作者：liuyi0905 (赞：0)

## 题意：
给定一个长度为 $n$ 的序列 $a$，求在满足 $a_i\times t_i\times a_{i+1}\times t_{i+1}$ 是完全平方数的基础上 $\prod_{i=1}^n t_i$ 的最小值。
## 思路：
对于每一个 $a_i\times t_i$，质因子的指数如果不都是奇数，就都是偶数。枚举一下每个质因子的两种情况取最小值计算即可。
## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
using LL=long long;
const int M=1e9+7;
int n;
unordered_map<int,int>c;
LL P(LL a,LL b){
	LL r=1;
	for(;b;a=a*a%M,b>>=1)
		b&1&&(r=r*a%M);
	return r;
}
void C(LL x){
	for(LL i=2,s;i*i<=x;c[i++]+=s%2)
		for(s=0;x%i==0;s++,x/=i);
	x>1&&(c[x]++);
}
int main(){
	cin>>n;
	for(int i=1,x;i<=n;i++)cin>>x,C(x);
	LL r=1;
	for(auto [x,v]:c)
		r=r*P(x,min(v,n-v))%M;
	cout<<r;
	return 0;
}
```

---

## 作者：Cyx20110930 (赞：0)

# 题意简述

有一个数组 $a_1,a_2,a_3,...,a_n$，求出乘积最小的 $t$ 数组 $t_1,t_2,t_3,...t_n$ 使得对于每个 $i (1\le i<n), a_i\times t_i\times a_{i+1}\times t_{i+1}$ 是完全平方数。

# Sol

明显对于每个 $a_i\times t_i$ 其因数的出现次数只有两种情况：都是奇数或都是偶数。

对这两种情况分别计算，取最小值即可。

# Code

```
//签到
//TEAM_NAME:CYX&LSY AK ICPC
//Problem B
//By CYX
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n;
bool isprime[1000005];
int pri[1000005],s[1000005],vis[1000005],num[1000005],prime[1000005],cnt,tot;
void init(){
	s[1]=1;
	for(int i=2;i<=1000005;i++){
		if(!isprime[i])prime[++cnt]=i,s[i]=i;
		for(int j=1;j<=cnt;j++){
			if(i*prime[j]>1000005)break;
			isprime[i*prime[j]]=1;
			s[i*prime[j]]=prime[j];
			if(!(i%prime[j]))break;
		}
	}
}
int qpow(int a,int b){
	int ans=1;
	while(b){
		if(b&1)ans=ans*a%1000000007;
		a=a*a%1000000007;
		b>>=1;
	}
	return ans;
}
signed main(){
	init();
	cin>>n;
	for(int i=1;i<=n;i++){
		int x;cin>>x;
		tot=0;
		while(x>1){
			if(!vis[s[x]])pri[++tot]=s[x];
			vis[s[x]]++;
			x/=s[x];
		}
		for(int j=1;j<=tot;j++){
			if(vis[pri[j]]%2==1)num[pri[j]]++;
			//num是指数为奇数的质因子的出现次数
			vis[pri[j]]=0;
		}
	}
	int ans=1;
	for(int i=1;i<=cnt;i++){
		if(!num[prime[i]])continue;
		ans*=qpow(prime[i],min(num[prime[i]],n-num[prime[i]]));
		ans%=1000000007;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：smydahaoren (赞：0)

### 题目思路

本题为数论题。

在数列的每个元素 $a_i$ 中都有一个对应的 $t_i$。而为了配成完全平方数，该数每个质因子的指数必须为偶数。所以在操作的时候，如果该数 $a_i$ 有奇数个质因子，那么在数组中就将对应的该质因子的个数增加 $1$。

最后在处理数组内所有质因子时，可以使用快速幂优化时间。

### AC 代码


```
#include<bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define antirep(i,a,b) for(int i=a;i>=b;i--)
#define speed ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
using namespace std;
const int N=1e7+10;
const int Mod=1e9+7;
int a[N],n,cnt[N],ans=1;
void work(int x){
	rep(i,2,floor(sqrt(x))){
		int y=0;
		while(x%i==0)
			x/=i,y++;
		y%=2;
		cnt[i]+=y;
	}
	if(x>1) cnt[x]++;
}
int qpow(int a,int b) {
  int res = 1;
  while (b>0) {
    if(b&1) res=res*a;
    a*=a;
    b>>=1;
    res%=Mod,a%=Mod;
  }
  return res;
}
signed main(){
	speed;
	cin>>n;
	rep(i,1,n) cin>>a[i],work(a[i]);
	rep(i,2,N-10)
		if(cnt[i]>0)
			ans*=(qpow(i,min(cnt[i],n-cnt[i]))%Mod),ans%=Mod;
	cout<<ans;
	return 0;
}

```

---

## 作者：__O_v_O__ (赞：0)

我们可以把 $a_i\times t_i$ 看成一个整体 $c_i$，于是题目要求转化为 $c$ 数组任意连续两项都是平方数。

显然，我们可以得到：$c_i$ 的每一个质因子的次数要么全是奇数，要么全是偶数。于是对这两种情况分别计算，取最小值即可。

下面讲解具体计算方法：

对于每个 $a_i$，分解质因数，记录它每个质因子的出现次数（这里我用欧拉筛筛出了每个数的最小质因子，就能快速分解）。

然后，判断每个质因子 $x$ 是否在 $a_i$ 中出现奇数次，如果是则将该质因子的计数器 $cnt_x$ 加一。

最后，枚举所有出现过的质因子 $x$，计算它在 $\prod_{i=1}^nt_i$ 中的最小次方，分两种情况（在上面说过）：

- 若 $x$ 的出现次数都为偶数，则最少需要 $cnt_x$ 个 $x$ 因子（分别乘到每个 $x$ 出现次数为奇数的 $a_i$ 上）。

- 若 $x$ 的出现次数都为偶数，则同理，最少需要 $n-cnt_x$ 个 $x$ 因子。

把每个因子的答案乘起来，就是最后的答案了。

**AC code:**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mo=1e9+7;
int n,f[1000001],p[1000001],s[1000001],an=1;
int vi[1000001],sz[1000001],nu[1000001],cn;
int pw(int a,int b){//快速幂
	int an=1;
	while(b){
		if(b&1)an=an*a%mo;
		a=a*a%mo,b>>=1;
	}return an;
}void sf(){//筛法
	s[1]=1;
	for(int i=2;i<1000001;i++){
		if(!f[i])p[++cn]=i,s[i]=i;
		for(int j=1;j<=cn&&i*p[j]<=1000000;j++){
			f[i*p[j]]=1,s[i*p[j]]=p[j];
			if(i%p[j]==0)break;
		}
	}
}signed main(){
	ios::sync_with_stdio(0),cin>>n,sf();
	for(int i=1;i<=n;i++){
		int x,no=0;cin>>x;
		while(x>1){
			if(!vi[s[x]])sz[++no]=s[x];//记录所有出现过的因子
			vi[s[x]]++,x/=s[x];//记录因子出现个数
		}for(int j=1;j<=no;j++){
			if(vi[sz[j]]&1)nu[sz[j]]++;//记录奇数因子的个数
			vi[sz[j]]=0;//清空
		}
	}for(int i=1;i<=cn;i++){
		if(!nu[p[i]])continue;
		an=an*pw(p[i],min(nu[p[i]],n-nu[p[i]]))%mo;//计算答案
	}cout<<an;
	return 0;
}
```

---

