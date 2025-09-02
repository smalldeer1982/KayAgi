# [入门赛 #9] 神树大人挥动魔杖 (Hard Version)

## 题目背景

**本题与 Easy Version 题意完全相同，仅有 $n,k$ 的数据范围有所不同。**

## 题目描述

神树大人挥动魔杖，召唤出了 $9 \times 10^{n-1}$ 只家养小精灵。每只家养小精灵都有一个互不相同的 $n$ 位数编号 $a_i$。

神树大人希望将这些家养小精灵分为 $k$ 组。第 $p$ 组的所有家养小精灵满足编号 $a_i$ 对 $k$ 取模余 $p-1$，即 $a_i \equiv p-1 \pmod k$。

神树大人想要知道，每一组小精灵分别有多少只。由于答案可能很大，你只需要输出答案对 $100,000,007$ 取模的结果

## 说明/提示

对于 $100\%$ 的数据，$1 \le n \le 5000$，$1 \le k \le 1000$。

## 样例 #1

### 输入

```
3 10```

### 输出

```
90 90 90 90 90 90 90 90 90 90
```

# 题解

## 作者：览遍千秋 (赞：5)

### Solution

递推。

记 $f(i,j)$ 代表所有的 $i$ 位数，对 $k$ 取模余 $j$ 的数目。

枚举 $i$ 位数最高位上填的数 $p$，显然有 $p = 1, 2, \cdots ,9$。

很容易求出 $p \times 10^{i-1}$ 对 $k$ 取模的值，记为 $R$。

则 $f(i,j)=\sum\limits_{a=1}^{i=1}f(a,(j-R) \bmod k)$。

对于每一个 $j$，前缀和累加 $f(i,j)$ 即可，时间复杂度为 $O(nk)$。

需要注意的是，答案模数为 $100000007$，即 $10^8+7$，一个优秀的 OIer 是会数数字位数的。

---

### Codes

```cpp
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 5000 + 7;
const int MAXK = 1000 + 7;
const int mod = 100000007; 

int n, k;
long long f[MAXN][MAXK];
long long sum[MAXK];

int main() {
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= 9; i++) f[1][i % k]++, sum[i % k]++;
	if(n == 1) {
		for(int i = 0; i < k; i++) {
			printf("%lld%c", f[n][i], " \n"[i == k - 1]);
		}
		return 0;
	}
	
	long long mul = 1;
	for(int i = 2; i <= n; i++) {
		mul = mul * 10 % k;
		for(int j = 1; j <= 9; j++) {
			long long val = j * mul % k;
			for(int p = 0; p < k; p++) {
				long long to = (p + val) % k;
				f[i][to] = (f[i][to] + sum[p]) % mod;
			}
			f[i][val]++;
		}
		for(int j = 0; j < k; j++) sum[j] += f[i][j], sum[j] %= mod;
	}
	for(int i = 0; i < k; i++) {
		printf("%lld%c", f[n][i], " \n"[i == k - 1]);
	}
	return 0;
}
```

---

## 作者：EdenSurvivor (赞：3)

## 方法：
这道题面相 ~~其他大佬说的~~ 可以用差分。

那什么是差分呢？ 在这里就不过多叙述了，不知道的可以看这篇 [this](https://blog.csdn.net/Newin2020/article/details/128852222)。

好的进入正题，我们应该怎么使用呢？

对于第 $i$ 组，个数可以看作前 $10^{n−1}$ 个数中 $x \bmod k=i$ 的数的个数减 $10^{n−1}−1$ 中 $x \bmod k=i$ 的数的个数。

对于 $a$ 个小精灵的情况，每一组至少有 $\frac{a}{k}$ 个小精灵，而剩余的 $a\bmod k$ 个分别被分到了 $1$ 之 $a\bmod k$ 组（是从 $1$ 组开始）。

代码就不给啦，你们自己写哦~

---

## 作者：Spouter_27 (赞：3)

差分，$i(0\le i < k)$ 组的个数看做前 $10^{n}-1$ 个中模 $k=i$ 的个数减去前 $10^{n-1}-1$ 个中模 $k =i$ 的个数。

若有 $a$ 个小精灵，则每一组个数至少为 $\lfloor{\frac{a} {k}}\rfloor$ 个。剩余 $a \mod k$ 个分别分到了 $1$ 至 $a \mod k$ 组中（不是从 $0$ 组开始）。

注意无法直接做取模的下取整除法，所以要先求出 $a \mod k$ 的值。

```cpp
#include<bits/stdc++.h>
using namespace std;
//#define int long long
typedef long long ll;
const ll N=2e5+10,mod=1e8+7;
ll ans[N];
ll qpow(ll a,ll b,ll c){
	ll ans=1,base=a;
	while(b){
		if(b&1)	ans=ans*base%c;
		base=base*base%c;
		b>>=1; 
	}
	return ans;
}
signed main(){
	ll n,k,sum=1;
	scanf("%lld %lld",&n,&k);
	ll q=(qpow(10,n-1,k)-1+k)%k;
	ll p=(qpow(10,n-1,mod)-1-q+mod)*qpow(k,mod-2,mod)%mod;
	for(int i=0;i<k;i++){
		ans[i]=-p;
		if(i!=0&&i<=q)	ans[i]--;
	}
	q=(qpow(10,n,k)-1+k)%k;
	p=(qpow(10,n,mod)-1-q+mod)*qpow(k,mod-2,mod)%mod;
	for(int i=0;i<k;i++){
		ans[i]+=p;
		if(i!=0&&i<=q)	ans[i]++;
		ans[i]=(ans[i]+mod)%mod;
		printf("%lld ",ans[i]);
	} 
}
/*
exSample:

*/
```


---

## 作者：_MiyazonoKaori_ (赞：2)

upd 2025.2.22：修改了格式
## 1. 纯暴力（只过样例，0pts）：
```cpp
#include<bits/stdc++.h>
#define fast_gets ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
using namespace std;
int ans[1005];
int main(){
   fast_gets
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=9*pow(10,n-1);i++){
		for(int j=0;j<k;j++){
			if(i%k==j) ans[j]++;
		}
	}
	for(int i=0;i<k;i++) cout<<ans[i]<<' ';
   return 0;
}
```
代码就不解释了。
## 2. 差分（100pts）：
### 思路：
精灵的个数为 $9\times 10^{n-1}$ 可写为 $10^{n}-10^{n-1}$。

同理可设有一个函数 $f(n, k, i)$，表示从 $1$ 到 $10^n - 1$ 之间所有数中模 $k$ 余数为 $i$ 的数的个数。那么，题目中的表达可以用以下的形式表示：

$$f(n, k, i) - f(n-1, k, i)$$

其中：
- $f(n, k, i)$ 表示前 $10^n - 1$ 个数中，模 $k$ 余数为 $i$ 的个数。
- $f(n-1, k, i)$ 表示前 $10^{n-1} - 1$ 个数中，模 $k$ 余数为 $i$ 的个数。

这个表达式表示的是在从 $1$ 到 $10^n - 1$ 之间的数中，模 $k$ 余数为 $i$ 的数的个数与从 $1$ 到 $10^{n-1} - 1$ 之间的数中，模 $k$ 余数为 $i$ 的数的个数之差。

每一组精灵至少有 $\left \lfloor \frac{9\times 10^{n-1}}{k}   \right \rfloor$ 个精灵，剩余 $a \bmod k$ 个分别分到了 $1$ 至 $a \bmod k$ 组中。
### AC 代码（纯净版）：
```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define ll long long
#define fast_gets ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
using namespace std;
const int N=1e6+5,MOD=1e8+7;
int cnt[N];
ll f(ll a,ll b,ll c){
	ll ans=1;
	while(b){
		if(b&1) ans=ans*a%c;
		a=a*a%c;
		b>>=1;
	}
	return ans;
}
int main(){
    fast_gets
	int n,k;
	cin>>n>>k;
	ll maxn=(f(10,n-1,k)-1+k)%k;
	ll p=(f(10,n-1,MOD)-1-maxn+MOD)*f(k,MOD-2,MOD)%MOD;
	for(int i=0;i<k;i++){
		cnt[i]=-p;
		if(i>0&&i<=maxn) cnt[i]--;
	} 
	maxn=(f(10,n,k)-1+k)%k;
	p=(f(10,n,MOD)-1-maxn+MOD)*f(k,MOD-2,MOD)%MOD;
	for(int i=0;i<k;i++){
		cnt[i]+=p;
		if(i>0&&i<=maxn) cnt[i]++;
		cnt[i]=(cnt[i]+MOD)%MOD;
		cout<<cnt[i]<<' ';
	}
    return 0;
}
```

---

## 作者：lin_A_chu_K_fan (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P9006)，题意略。
# 思路
首先，这道题要用差分。

对于第 $i$ 组，个数可以看作前 $10 ^ n - 1 $ 个数中 $\bmod k = i$ 的数的个数减 $10 ^ {  n-1 } - 1$ 中$\bmod k = i$ 的数的个数。

对于 $a$ 个小精灵的情况，每一组至少有 $\lfloor \frac{a}{k} \rfloor$ 个小精灵，而剩余的 $a \bmod k$ 个分别被分到了 $1$ 之 $a \bmod k$ 组（是从 $1$ 组开始）。

按上面说的算就行了，代码就不给了。

---

## 作者：Farewell_Bood (赞：1)

太好了，又找到了一个可以练习差分的题目了。

我们假设有 $x$ 个小精灵，则每一组的个数至少为 $a/k$ 个。那么剩余的 $x \bmod k$ 个分别分到了 $1$ 至 $x \bmod k$ 组中（不从 $0$ 开始）。

我们要先求出 $a \bmod k$ 的值，为什么呢？因为~~它善~~无法直接做取模的下取整除法。

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long mod=100000007;
long long ans[1000001];
long long qpow(long long di,long long zhi,long long Mod){
	long long ans=1;
	while(zhi){
		if(zhi&1) ans=ans*di%Mod;
		di=di*di%Mod;
		zhi>>=1;
	}
	return ans%Mod;
}
long long n,k,cnt=1;
int main(){
	cin>>n>>k;
	long long x=(qpow(10,n-1,k)-1+k)%k;
	long long y=(qpow(10,n-1,mod)-1-x+mod)*qpow(k,mod-2,mod)%mod;
	for(int i=0;i<k;i++){
		ans[i]-=y;
		if(i!=0&&i<=x) ans[i]--;
	}
	x=(qpow(10,n,k)-1+k)%k;
	y=(qpow(10,n,mod)-1-x+mod)*qpow(k,mod-2,mod)%mod;
	for(int i=0;i<k;i++){
		ans[i]+=y;
		if(i!=0&&i<=x) ans[i]++;
		ans[i]=(ans[i]+mod)%mod;
		cout<<ans[i]<<" ";
	}
	cout<<endl;
	return 0;
}
```
所以这道题就这么水灵灵的过啦！

---

## 作者：Ag2WO4 (赞：0)

发现其他题解都用了比较复杂的方法，这里就上一个极其简单（甚至复杂度更低）的做法吧：
## 核心思路：快速幂取余
考虑到整个数组每 $100000007\times k$ 次相加就会清零，于是快速幂取余计算前 $10^n$ 个数中最后有多少个数不能被抵消，再将这些数分成 $k$ 的商数和余数即可。最后和前 $10^{n-1}$ 个数的结果简单在模数下相减就可以了。优秀的 $O(k+\log n)$ 复杂度甚至让 Python 的代码成功挤进了本人撰文时最优解的第一页，而 C/C++ 代码更在最优解最前列。
#### 代码
Python 代码相对简单：
```python
n,k=map(int,input().split());p=pow(10,n,k*100000007)//k;p=[p]*k;q=pow(10,n-1,k*100000007)//k;q=[q]*k#快速幂取余后的商数
for i in range(pow(10,n,k*100000007)%k):p[i]+=1#快速幂取余后的余数
for i in range(pow(10,n-1,k*100000007)%k):q[i]+=1
print(*((p[i]-q[i])%100000007 for i in range(k)))#相减
```
C/C++ 小心模 $100000007\times k$ 的快速幂取余是会爆 ```long long``` 的，这里使用 ```__int128``` 解决。

```c
#include<stdio.h>
#define t 100000007
__int128 m[13],n,k,i,u,v,p;
int main()
{
    scanf("%d%d",&n,&k);
    u=v=1;m[0]=10;
    for(i=0;i<12;)m[++i]=(m[i]*m[i])%(k*t);
    for(i=0;i<13;i++)if(n&(1<<i))u=u*m[i]%(k*t);
    n--;
    for(i=0;i<13;i++)if(n&(1<<i))v=v*m[i]%(k*t);
    p=u/k-v/k;u%=k;v%=k;
    while(p<t)p+=t;
    i=0;printf("%d",(p+(i<u)-(i<v))%t);
    for(i=1;i<k;i++)printf(" %d",(p+(i<u)-(i<v))%t);
}
```

---

