# Short Task

## 题目描述

Let us denote by $ d(n) $ the sum of all divisors of the number $ n $ , i.e. $ d(n) = \sum\limits_{k | n} k $ .

For example, $ d(1) = 1 $ , $ d(4) = 1+2+4=7 $ , $ d(6) = 1+2+3+6=12 $ .

For a given number $ c $ , find the minimum $ n $ such that $ d(n) = c $ .

## 样例 #1

### 输入

```
12
1
2
3
4
5
6
7
8
9
10
39
691```

### 输出

```
1
-1
2
3
-1
5
4
7
-1
-1
18
-1```

# 题解

## 作者：Na2PtCl6 (赞：7)

## 分析题目
此题关键在于用欧拉筛筛因数和。

设数 $i$ 的因数和为 $f(i)$ ，当前第二重循环（可参考欧拉筛代码）枚举到的素数为 $p_j$ ，则分为三类

1. $i$ 为素数，$f(i)=i+1$
2. $i$ 不可被 $p_j$ 整除，$f(i \times p_j)=f(i)+f(i) \times p_j$。因为乘上 $p_j$ 就使原数的因子数增加了一倍，增加的因子是原数每个因子分别乘上 $p_j$ 。
3. $i$ 可被 $p_j$ 整除，$f(i \times p_j)=f(i)+(f(i)-f(i/p_j)) \times p_j$ 。因为 $i/p_j$ 中的每个因子乘上 $p_j$ 都会造成因子的重复计算，所以要去掉重复出现的因子。

## 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=10000004;
bool vis[maxn];
int t,c,cnt,pr[maxn],res[maxn],save[maxn];
long long fc[maxn];

void get_fc(){
	res[1]=fc[1]=1;
	for(int i=2;i<maxn;i++)
		res[i]=-1;
	for(int i=2;i<maxn;i++){
		if(!vis[i]){
			pr[++cnt]=i;
			fc[i]=i+1;
		}
		for(int j=1;j<=cnt&&i*pr[j]<maxn;j++){
			vis[i*pr[j]]=1;
			if(i%pr[j]==0){
				fc[i*pr[j]]=fc[i]+(fc[i]-fc[i/pr[j]])*pr[j];
				break;
			}
			fc[i*pr[j]]=fc[i]+fc[i]*pr[j];
		}
	}
}

signed main(){
	get_fc();
	for(int i=2;i<maxn;i++){
		if(fc[i]>=maxn)
			continue;
		if(res[fc[i]]==-1)
			res[fc[i]]=i;
	}
	scanf("%d",&t);
	while(t--){
		scanf("%d",&c);
		printf("%d\n",res[c]);
	}
	return 0;
}
```

---

## 作者：haokee (赞：3)

我们发现，计算 $x$ 的所有约数之和非常简单，但是已知约数之和为 $y$，求出最小的 $x$ 非常复杂，答案也不满足单调性。因此，考虑预处理 $1\sim 10^7$ 当中所有数的约数之和。

找到 $x$ 的所有约数是 $\mathcal O(\sqrt x)$ 的，但是这题 $x\le 10^7$。考虑换种方法，不是枚举一个数的因数有哪些，而是枚举一个数的倍数有哪些。准确来说，就是枚举因数 $i$，然后将 $i$ 的所有倍数 $ki$ 的函数值全部的加上 $i$。

这样子时间复杂度大约为 $\mathcal O(n\log_2 n)$，可以极限卡过。

```cpp
#include <iostream>
#pragma GCC optimize(2)

using namespace std;

const int kMaxN = 1e7 + 5;

int f[kMaxN], a[kMaxN], t, x;

int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  // 预处理 1 的倍数，常数优化
  fill(f, f + kMaxN, 1);
  // 将所有数的倍数加上这个数
  for (int i = 2; i <= 1e7; i++) {
    for (int j = i; j <= 1e7; j += i) {
      f[j] += i;
    }
  }
  // 记录最小答案
  for (int i = 1; i <= 1e7; i++) {
    if (f[i] <= 1e7 && !a[f[i]]) {
      a[f[i]] = i;
    }
  }
  // 询问
  for (cin >> t; t; t--) {
    cin >> x;
    cout << (a[x] ? a[x] : -1) << '\n';
  }
  return 0;
}
```

---

## 作者：Cuiyi_SAI (赞：3)

## 题目大意

前置：我们称 $\sigma(i)$ 为 $i$ 的约数和。

多组数据，给定 $n$ ，求 $\sigma(x)=n$ 的最小 $x$。

---

有一个很重要的性质，就是 $\sigma(n)$ 是一个积性函数。

这里简单证明一下：

---

考虑一个数 $n$，将其分解质因数得 $n=p_1^{c_1}p_2^{c_2}\cdots p_m^{c_m}$，则其约数和为 $(1+p_1^1+p_1^2\cdots+p_1^{c_1})(1+p_2^1\cdots p_2^{c_2})\cdots(1+\cdots p_m^{c_m})$。

对于两个互质的 $a$ 和 $b$ ，因此 $a$ 的质因数定与 $b$ 的质因数两两不相同，根据上述公式我们可以得到 $\sigma(ab)=\sigma(a)\sigma(b)$。

---

知道了 $\sigma(n)$ 是个积性函数，我们就直接可以考虑使用欧拉筛来线性得到它。

- 对于每个质数 $prime_j$ ，都有 $\sigma(prime_j)=1+prime_j$。

- 当 $i$ 与 $prime_j$ 互质，则 $\sigma(prime_j\cdot i)=\sigma(prime_j)\sigma(i)$。
- 当 $i$ 与 $prime_j$ 不互质，则考虑找到最大的 $c_j$ ，使得 $prime_j^{c_j}\mid i$ ，此时 $\dfrac{i}{prime_j^{c_j}}$ 显然与 $prime_j^{c_j}$ 互质，因此 $\sigma(prime_j\cdot i)=\sigma(prime_j^{c_j+1})\sigma(\dfrac{i}{prime_j^{c_j}})$。

然后我们就可以利用这些性质筛积性函数了。

得到了所求范围内的 $\sigma(n)$，我们直接暴力统计每个值最早出现的位置，作为答案输出即可。

## CODE：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int t,n,ans[10000010]={0};
unsigned long long d[10000010]={0};
int prime[1000010],tot=0;
bitset<(int)1e7+10> v;
long long num(int x)   //暴算约数和
{
	int res=0;
	for(int i=1;i*i<=x;i++)
	{
		if(x%i!=0) continue;
		res+=i;
		if(x/i==i) continue;
		res+=(x/i);
	}
	return res;
}
void shai()
{
	d[1]=1;
	for(int i=2;i<=1e7;i++)
	{
		if(!v[i]) prime[++tot]=i,d[i]=1+prime[tot];
		for(int j=1;j<=tot&&prime[j]*i<=1e7;j++)
		{
			v[prime[j]*i]=1;
			if(i%prime[j]==0)
			{
				int x=i*prime[j],s=1;
				while(x%prime[j]==0) x/=prime[j],s*=prime[j];
				d[i*prime[j]]=d[x]*num(s);
				if(d[i*prime[j]]<0||d[i*prime[j]]>1e7) d[i*prime[j]]=0;
				break;
			}
			else d[i*prime[j]]=d[i]*d[prime[j]];
			if(d[i*prime[j]]<0||d[i*prime[j]]>1e7) d[i*prime[j]]=0;  //防爆系统
		}
	}
	for(int i=1;i<=1e7;i++)
	  if(ans[d[i]]==0)
	    ans[d[i]]=i;
	return ;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	shai();
	while(t)
	{
		t--;
		cin>>n;
	    if(ans[n]==0) cout<<-1<<'\n';
	    else cout<<ans[n]<<'\n';
	}
	return 0;
}
```



---

## 作者：MatrixCascade (赞：3)

先用欧拉筛筛出 $1\to10000000$ 所有数的因数和（调和级数枚举也可以），然后遍历一遍统计就可以了。

具体遍历类似这样：

```cpp
	memset(qwq,-1,sizeof(qwq));
	up(i,1,10000000)
	{
		if(f[i]>10000000)continue;
		else
		{
			if(qwq[f[i]]==-1)qwq[f[i]]=i;
		}
	}
	int T=read();
	while(T--)
	{
		int x=read();
		cout<<qwq[x]<<endl;
	}
```

后话：这场 Div3 好水啊，可惜被 C 恶心了只拿了 rk12 /kk

---

## 作者：Ak_hjc_using (赞：0)

### $\texttt{Solution}$

使用算法：**暴力**

由于题目发现 $n \le 10^7$，所以直接 $T$ 此询问每次查询如果枚举那么就会 TLE，所以就可以**预处理** $10^7$ 所有的答案，每次查询直接输出即可。

#### 预处理
每次枚举因数，将是它的倍数的数全部都加上它的值。

代码变量解释：

1. $f_i$ 代表 $i$ 的所有因数之和。
2. $a_n$，表示 $f_i = n$ 的最小的 $i$。

时间复杂度：$O(n\log^2n)$。

### $\texttt{Code}$
```cpp
#include <bits/stdc++.h>

using namespace std;

const int kMaxN = 1e7;

int f[kMaxN + 5], n, T, a[kMaxN + 5];

int main() {
  cin.tie(0)->sync_with_stdio(0);
  fill(f + 1, f + kMaxN + 1, 1);
  for (int i = 2; i <= kMaxN; i++) {
    for (int j = 1; i * j <= kMaxN; j++) {
      f[i * j] += i;
    }
  }
  for (int i = 1; i <= 1e7; ++i) {
    if (f[i] <= 1e7 && !a[f[i]]) {
      a[f[i]] = i;
    }
  }
  for (cin >> T; T > 0; T--) {
    cin >> n;
    cout << (a[n] ? a[n] : -1) << '\n';
  }
  return 0;
}
```

---

## 作者：LRRabcd (赞：0)

# 题解

这道题可以先预处理出 $1$ 至 $10^7$ 中所有数的因数和，但这样的时间是 $\mathcal{O}(N\sqrt{N})$ 的。所以得反过来想，枚举每个数有哪些倍数，这样时间就降到了 $\mathcal{O}(N\log N)$，在 CF 上可以卡过去。因数的问题解决了，现在只需要需要求出对于每个 $c$ 的答案就可以了。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int sum[10000005];
int ans[10000005];
void init(){
    for(int i=1;i<=1e7;i++){
        ans[i]=-1;
    }
    for(int i=1;i<=1e7;i++){
        for(int j=i;j<=1e7;j+=i){
            sum[j]+=i;
        }
    }
    for(int i=1;i<=1e7;i++){
        if(sum[i]>1e7){//c<=1e7
            continue;
        }
        if(ans[sum[i]]==-1){//求最小的
            ans[sum[i]]=i;
        }
    }
    return;
}
void work(){
    int x;
    cin>>x;
    cout<<ans[x]<<"\n";
    return;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    init();
    int T;
    cin>>T;
    while(T--){
        work();
    }
    return 0;
}
```

---

## 作者：Meickol (赞：0)

什么？给定的时间限制高达 $2$ 秒？那这也太简单了！

直接跑一遍线性筛同时记录最小质因子。

然后我们对 $1 \sim 10^7$ 内的每个数都求出其唯一分解的形式，再根据约数和定理即可求出该数对应的约数和。

然后我们使用一个数组 $ans_x$ 记录约数和为 $x$ 的数其对应的最小的 $n$ 即可。

预处理时间复杂度 $\mathcal O(c \log c)$，每次询问 $\mathcal O(1)$。

蛮简单的，也很经典，自己半个小时便单出了本题。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define rep(x,y,z) for(int x=y;x<=z;x++)
#define per(x,y,z) for(int x=y;x>=z;x--)
#define IOS std::ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
#define endl '\n'
typedef long long LL;
const int N=1e7+5;
int primes[N],pj;
bool st[N];
int minp[N];
int ans[N];
void get_primes(int n){
	rep(i,2,n){
		if(!st[i]){
			primes[++pj]=i;
			minp[i]=i;
		}
		for(int j=1;i*primes[j]<=n;j++){
			minp[i*primes[j]]=primes[j];
			st[i*primes[j]]=1;
			if(i%primes[j]==0) break;
		}
	}
}
void init(int n){
	rep(i,1,n){
		int x=i;
		LL res=1;
		while(x>1){
			LL b=1;
			int p=minp[x];
			while(x%p==0) b=b*p+1,x/=p;
			res*=b;
			if(res>N-2) break;
		}
		if(res>N-2) continue;
		ans[res]=min(ans[res],i);
	}
}
void solve(){
	int c;
	cin>>c;
	int INF;
	memset(&INF,0x3f,sizeof INF);
	if(ans[c]==INF) return cout<<-1,void();
	else cout<<ans[c];
}
int main(){
	IOS;
	int T;
	cin>>T;
	// T=1;
	memset(ans,0x3f,sizeof ans);
	get_primes(N-2);
	init(N-2);
	while(T--){
		solve();
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：rainbow_cat (赞：0)

看到这道题，我们首先考虑暴力。   
我们进行预处理。先枚举因数，再枚举倍数。则时间复杂度为 $O(\sum_{i= 1}^{n} \frac{n}{i} )$。   
由于调和级数，得到时间复杂度为 $O(n \log n)$。同时时间限制是两秒，所以暴力可以通过。   
代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,sum[10000010],ans[10000010];
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	memset(ans,-1,sizeof ans);
	for(int i=1;i<=10000000;i++)//调和级数预处理
		for(int j=i;j<=10000000;j+=i)
			sum[j]+=i;
	for(int i=1;i<=10000000;i++)if(sum[i]<=10000000&&ans[sum[i]]==-1)ans[sum[i]]=i;
	while(t--)
	{
		cin>>n;
		cout<<ans[n]<<'\n';
	}
	return 0;
}
```   
![](https://cdn.luogu.com.cn/upload/image_hosting/vzmzo95v.png)      
注：时限有些卡，若发现超时可以自主进行卡常。

---

## 作者：CQ_Bob (赞：0)

## 分析

考虑暴力。

对于 $d(i)$，我们可以通过调和级数暴力枚举。对于其复杂度，是 $O(n \ln n)$ 的，可以看作 $O(n \log n)$，在 $2\times 10^8$ 级别。题目给了 $2$ 秒，预处理出来之后卡卡常就过了。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
//#define int long long
#define re register
#define il inline
#define pii pair<int,int>
#define x first
#define y second
#define gc getchar()
#define rd read()
#define debug() puts("------------")

namespace yzqwq{
	il int read(){
		int x=0,f=1;char ch=gc;
		while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=gc;}
		while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=gc;
		return x*f;
	}
	il int qmi(int a,int b,int p){
		int ans=1;
		while(b){
			if(b&1) ans=ans*a%p;
			a=a*a%p,b>>=1;
		}
		return ans;
	}
	il auto max(auto a,auto b){return (a>b?a:b);}
	il auto min(auto a,auto b){return (a<b?a:b);}
	il int gcd(int a,int b){
		if(!b) return a;
		return gcd(b,a%b);
	}
	il int lcm(int a,int b){
		return a/gcd(a,b)*b;
	}
	il void exgcd(int a,int b,int &x,int &y){
		if(!b) return x=1,y=0,void(0);
		exgcd(b,a%b,x,y);
		int t=x;
		x=y,y=t-a/b*x;
		return ;
	}
	mt19937 rnd(time(0));
}
using namespace yzqwq;

const int N=1e7+1;
long long s_sum[N];
int ans[N];

signed main(){
	for(re int i=1;i<=N-1;++i){
		ans[i]=-1;
		for(re int j=1;j*i<=(N-1);++j) s_sum[j*i]+=i;
	}
	for(re int i=1;i<N;++i)
		if(s_sum[i]<N&&ans[s_sum[i]]==-1) ans[s_sum[i]]=i;
	int t=rd;
	while(t--){
		int x=rd;
		printf("%d\n",ans[x]);
	}
	return 0;
}
```

---

## 作者：Helium_Ship (赞：0)

这题其实就是一道欧拉筛积性函数的板子题，至于为什么 $d(n)$ 为积性函数就留给读者自己思考。

前置:如果 $d(n)$ 为积性函数，当 $\gcd(x,y)=1$ 时，$d(xy)=d(x)d(y)$

对于质数 $prim_j$，因为其只有两个因数 $1$ 和他本身，所以 $d(prim_j)=prim_j+1$。

我们筛 $i\times prim_j$ 时，当 $prim_j\nmid i$，$d(i\times prim_j)=d(i)d(prim_j)$。

当 $prim_j\mid i$，设 $i$ 中质因子 $prim_j$ 的次数为 $x$，则$d(i\times prim_j)=d(\frac{i}{prim_j^x})d(prim_j^x)$。

注意：对于一个数为某个质数的整数次幂，那么我们就暴力计算，其实也可以用等比数列求和公式。

code:
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n;
long long d[10000010],prim[10000010],cnt;
long long d2[10000100];
bitset<int(1e7)+10> used;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	for (int i=1;i<=1e7;i++)d[i]=1;
	for (int i=2;i<=1e7;i++){
		if (!used[i]){
			prim[++cnt]=i;
			d[i]=i+1;
		}
		for (int j=1;i*prim[j]<=1e7&&j<=cnt;j++){
			used[i*prim[j]]=1;
			if (i%prim[j])d[i*prim[j]]=d[i]*d[prim[j]];
			else{
				long long tmp=i,tmp2=prim[j],cnt=1;
				while (tmp%prim[j]==0)tmp/=prim[j],tmp2*=prim[j],cnt++;
				if(tmp==1)
				{
					long long tmp3=0,tmp4=prim[j];
					for (int k=1;k<=cnt;k++)tmp3+=tmp4,tmp4*=prim[j];
					d[i*prim[j]]=tmp3+1;
					break;
				}
				d[i*prim[j]]=d[tmp]*d[tmp2];
				break; 
			}
		}
	}
	for (int i=1;i<=1e7;i++){
		if (d[i]>1e7)continue;
		if (!d2[d[i]])d2[d[i]]=i;
	}
	cin>>t;
	while (t--){
		cin>>n;
		if (d2[n]==0)cout<<"-1\n";
		else cout<<d2[n]<<'\n';
	}
	return 0;
}

```

---

