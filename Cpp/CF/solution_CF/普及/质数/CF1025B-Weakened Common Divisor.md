# Weakened Common Divisor

## 题目描述

与  $GCD$  （最大公约数）类似，我们引进  $WCD$ （弱公约数）的概念， $ WCD$  的定义如下：

给出几对数 $\left( a_1,b_1 \right) ,\left( a_2,b_2 \right) ,\cdots ,\left( a_n,b_n \right)$ ，它们的  $WCD$  满足大于  $1 $ ，且能整除每个数对中至少一个数。  $WCD$  在一些情况下，可能不存在。

例如，给出这几对数 $\left[ \left( \text{12,}15 \right) ,\left( \text{25,}18 \right) ,\left( \text{10,}24 \right) \right]$  ，它们的   $WCD$  可以是 $ 2,3,5,6$  （这些数都满足严格大于  $1$  ，且能整除每个数对中至少一个数）

现在给你几对数，求他们的   $WCD$  。

## 样例 #1

### 输入

```
3
17 18
15 24
12 15
```

### 输出

```
6```

## 样例 #2

### 输入

```
2
10 16
7 17
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
5
90 108
45 105
75 40
165 175
33 30
```

### 输出

```
5
```

# 题解

## 作者：zhaotiensn (赞：7)

分解质因数觉得太麻烦了，所以有了以下投机取巧的方法。。。~~(其实是觉得根号级的会$tle$，$log$级的懒)~~

对于每一对数求它们的$lcm$，然后对于所有的$lcm$求$gcd$，显然$gcd$中的所有质因子每一对一定会出现，然后随便求一个质因子就好了。

AC代码：
```
#include <iostream>
#include <cstdio>
#include <cmath>

#define ll long long

using namespace std;

ll n,a,b,ans;

inline ll gcd(ll x,ll y){
	return x%y?gcd(y,x%y):y;
}

inline ll calc(ll x){//求一个质因子
	for(int i=2;i<=sqrt(x);i++){
		if(x%i==0){
			return i;
		}
	}
	return x;
}

int main(){
	ios::sync_with_stdio(false);
	cin>>n;
	n--;
	cin>>a>>b;
	ans=a*b/gcd(a,b);
	while(n--){
		cin>>a>>b;
		ans=gcd(ans,a*b/gcd(a,b));//对于所有的lcm求gcd
	}
	if(ans==1){//如果gcd为1，那么就没有wcd
		cout<<-1<<endl;
	}else{
		if(gcd(ans,a)>1){//要求的因子一定在a中或b中
			cout<<calc(gcd(ans,a))<<endl;
		}else{
			cout<<calc(gcd(ans,b))<<endl;
		}
	}
	return 0;
}

```

---

## 作者：si_zhong (赞：5)

这是一道很普通的题。

但是，要注意，需要分解质因数，因为每一个因数都可以分解成质的因数，所以这样干。

我的做法是要存第一对数的质因数，然后扫后面的，不停地把不是的去掉，最后剩下的就是输出了，若没有剩，输出-1.

AC代码如下：

（详解在代码里。）

```cpp
#include <bits/stdc++.h>万能头
using namespace std;

long long n,f[150000],top;f数组用来存第一对数的质因数。
long long a,b;
int main() {
	scanf("%lld",&n);读入
	for(int i=1; i<=n; i++) {
		scanf("%lld %lld",&a,&b);读入
		if(i==1) {第一次的这一对
			for(int j=2; j<=sqrt(a)注意这里可以省时间; j++) {
				while(a!=j) {
					if(a%j==0) {
						f[top]=j;           这里是a分解质因数
						top++;
						a/=j;
					} else {
						break;
					}
				}
			}
			if(a>1) f[top]=a,top++;注意！自己也要算进去哦！
			for(int j=2; j<=sqrt(b)注意这里可以省时间; j++) {
				while(b!=j) {
					if(b%j==0) {
						f[top]=j;           这里是b分解质因数
						top++;
						b/=j;
					} else {
						break;
					}
				}
			}
			if(b>1) f[top]=b,top++;注意！自己也要算进去哦！
			continue;
		}
		for(int j=0; j<=top-1; j++) {开始扫后面的
			if(a%f[j]!=0&&b%f[j]!=0) {若不是就弄掉。
				f[j]=-1;注意是“&&”，因为“WCD”的定义。
			}
		}
	}
	for(int j=0; j<=top-1; j++) {
		if(f[j]!=-1) {
			printf("%lld",f[j]);愉快输出
			return 0;
		}
	}
	cout<<"-1";愉快输出
	return 0;
    完美AC！！！！！
}
```

若还有不懂的可以私信问我，我会尽力帮你解决问题的！

---

## 作者：Jasper08 (赞：1)

题外话：我一开始想预处理 $2\times 10^8$ 内所有质数，不出意外 MLE 了（

### 题目分析

根据题目中的定义，易知若 $x$ 为 $\text{wcd}[(a_1,b_1),(a_2,b_2),...,(a_n,b_n)]$，则 $x$ 的所有除了 $1$ 之外的因数都是 $\text{wcd}[(a_1,b_1),(a_2,b_2),...,(a_n,b_n)]$。所以我们只需要从质数开始一个一个找就可以了。

开始我们就可以先分解出 $a_1,b_1$ 的质因子，然后与 $a_i,b_i$ 逐个判断能否整除即可。

### 完整代码

总共 709 毫秒，十分优秀。复杂度 $O\left (\sqrt{a_1}+\sqrt{b_1}+n(a_1\text{的质因数个数}+b_1\text{的质因数个数})\right )=O(\text{超快})$。

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cctype>
#include <map>
#include <iomanip>

using namespace std;

#define getchar()  (sp == ep && (ep = (sp = ibuf) + fread(ibuf,1,mm,stdin),sp == ep) ? EOF : *sp++)
#define putchar(x) ((op-obuf<mm) ? (*op++=x) : (fwrite(obuf,op-obuf,1,stdout),op=obuf,*op++=x))

const int N = 150050;
const int mm = 1 << 20;
static char ibuf[mm],obuf[mm],*sp=ibuf,*ep=ibuf,*op = obuf,*p3 = obuf;

inline int read(){
	int flag = 1, x = 0;
	char ch = getchar();
	while (!isdigit(ch)) {
		if (ch == '-')
			flag = -1;
		ch = getchar();
	}
	while (isdigit(ch)) {
		x = (x<<3) + (x<<1) + (ch^48);
		ch = getchar();
	}
	return flag*x;
}

void write(int x){
	char ch[20];
	int len = 0;
	if(x < 0)
		putchar('-'), x = -x;
	do {
		ch[len++] = (x%10)^48;
		x /= 10;
	}
	while(x);

	while(len--)
		putchar(ch[len]);
 	putchar(' ');
}

void ln() {
	putchar('\n');
}

void writeln(int x){
	write(x);
	ln();
}

struct Num {
	int a, b;
} num[N];

int main() {
	int n = read(); 
	map<int, int> primes; //用map存储a1,b1的质因子
	
	int a1 = read(), b1 = read();
	for (int i = 2; i <= a1/i; ++i) { //分解a1的质因子
		while (a1 % i == 0)
			primes[i] ++, a1 /= i;
	}
	if (a1 > 1) //如果分解完后a1仍然大于1,说明a1有一个大于等于sqrt(a1)的质因子
		primes[a1] ++;
	for (int i = 2; i <= b1/i; ++i) { //分解b1的质因子
		while (b1 % i == 0)
			primes[i] ++, b1 /= i;
	}
	if (b1 > 1)
		primes[b1] ++;
	
	for (int i = 2; i <= n; ++i) 
		num[i].a = read(), num[i].b = read();
	
	for (auto p : primes) { //遍历每一个质因子,逐个判断是否满足要求
		bool check = 1;
		int pr = p.first;
		for (int i = 2; i <= n; ++i) {
			if (!(num[i].a % pr == 0 || num[i].b % pr == 0)) { //不能整除就直接换下一个质数
				check = 0;
				break;
			}
		}
		if (check) {
			writeln(pr);
			fwrite(obuf,op-obuf,1,stdout);
			return 0;
		}
	}
	puts("-1"); //如果所有质数都不行的话说明无解
	fwrite(obuf,op-obuf,1,stdout);
	return 0;
}
```

---

## 作者：npqenqpve (赞：1)

其他的几篇题解大多都是先求了 $c_i \gets lcm(a_i,b_i)$ ，然后求全部 $c_i$ 的最大公约数，但是对每一组数都求一下 $lcm(a_i,b_i)$ 会增加时间复杂度，所以直接把 $a_i$ ，$b_i$ 乘起来就行，不妨记录$c_i \gets a_i * b_i $ 最后再求所以 $c_i$ 的最大公约数，求所以 $c_i$ 的最大公约数的方法是先求 $now \gets gcd(c_{i-1},c_{i-2})$ ，然后再求 $gcd(now,c_i)$ ，为什么 $gcd(a,b,c)=gcd(gcd(a,b),c)$ 呢，因为 
$$

  gcd(a,b)=\prod_{p} p^{min(a_p,b_p)}
$$
其中 $a_p$ 与 $b_p$ 为 $a,b$ 质因数 $p$ 的指数，记上面这个大式子为 $q$ ,那么
$$

  gcd(q,b)=\prod_{p} p^{min(q_p,c_p)}=\prod_{p} p^{min(min(a_p,b_p),c_p)}
$$
因为 $min(min(a,b),c)$ 等价于 $min(a,b,c)$ ，即 $min$ 满足结合律 ，所以 $gcd$ 也是满足结合律的。

当然求出所以 $c_i$ 的最大公约数（记作 $ans$ ）是不满足要求的 ，但是因为 $ans$ 的质因数一定在所以 $c_i$ 中都有，所以 $ans$ 的质因数一定是在与 $c_i$ 对应的 $a_i$ ，$b_i$ 至少一个中存在 ，且指数小于等于 $min(a_p,b_p)$ ，所以输出 $ans$ 输出一个质因数即可，显然当所有 $c_i$ 的最大公约数为 $1$ 时不存在 ，但是这题有点卡质因数分解 ，所以判断一下选 $a_1$ 还是 $b_1$ 然后与 $ans$ 取个最大公约数能减小要分解的数的大小 ，具体见代码实现
### 代码实现:
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll read()
{
	ll X=0,w=0;char ch=0;
	while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
	while(isdigit(ch)){X=(X<<3)+(X<<1)+(ch^48);ch=getchar();}
	return w?-X:X;
}

void write(ll x)
{
	if(x<0){putchar('-');x=-x;}
	if(x>9){write(x/10);}
	putchar(x%10+'0');
}
ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
ll lcm(ll a,ll b){return a*b/gcd(a,b);}
struct node
{
	ll a,b,l;
	
};
ll f(ll x)
{
	for(int i=2;i<=sqrt(x);i++)
	{
		if(x%i==0){
			return i;
		}
	}
	return x;
}
int main()
{
	ll n=read();
	node arr[150000];
	ll aaa,bbb;
	cin>>aaa>>bbb;
	 for(int i=1;i<n;i++)
	 {
	 	arr[i].a=read();
	 	arr[i].b=read();
	 	arr[i].l=arr[i].a*arr[i].b;
        aaa=gcd(arr[i].a*arr[i].b,aaa);
        bbb=gcd(arr[i].a*arr[i].b,bbb);
	 }
	 ll now=gcd(arr[0].l,arr[1].l);
	for (int i=2;i<n;i++)
	{
		now=gcd(now,arr[i].l);
	}
	if(now==1)
	{
		cout<<"-1";
		return 0;
	}
	if(aaa!=1)
	{
		cout<<f(aaa);
	}
	else if(bbb!=1) cout<<f(bbb);
	else cout<<"-1";
	return 0;
}
```


---

## 作者：山田リョウ (赞：1)

本篇题解主要是解释第一篇题解（@zhaotiensn 的那篇）为啥是对的。

首先，我们知道如果一个数 $d$ 可以整除 $a$，那么 $d$ 一定是可以整除 $\operatorname{lcm}(a,b)$ 的，所以我们猜测答案就是每组 $a,b$ 的 $\operatorname{lcm}$ 的 $\gcd$。 

但是明显不对啊，因为这个数（往后这个数我们管它叫做 $tmp$）不一定是质数，它或许能拆成 $x \times y$，其中 $x$ 可以整除 $a$，$y$ 可以整除 $b$，但是这个数既不能整除 $a$，又不能整除 $b$。

所以怎么办？那我们就找 $tmp$ 的一个质因数，这个数任何一个质因数都是没问题的，因为质数就不能拆了。

那怎么找呢？你直接 $O(\sqrt{tmp})$ 的做法是过不去的，可以被这组数据卡掉：
```
1
1999999973 1999999943
```

怎么办呢？其实可以用 pollard rho 算法来做，但很遗憾，我不会。。。

但是这个质因数明显是能整除 $a$ 和 $b$ 中的一个，所以如果 $\gcd(a,tmp) > 1$的话就找 $\gcd(a,tmp)$ 的某个质因数，否则找 $\gcd(b,tmp)$ 的某个质因数。

由于 $\gcd$ 后的结果一定是小于等于 $a$ 或 $b$ 的，所以这样稳过。

[代码](https://www.luogu.com.cn/paste/51dyh5ad)

---

## 作者：Dreamunk (赞：1)

我的代码跑得就是很快。

显然如果$a$为$WCD$，则$a$的所有质因数一定也为$WCD$。

所以我们只要管质数就好了。

先把第$1$组$a,b$分解质因数，然后判断每个质因数它是否
整除第$2$~$n$组$a,b$中的一个，最后随便找一个满足条件的质因数输出就好了。

因为正整数的质因数个数为$loga$级别的，所以时间复杂度为
$O(\sqrt{a}+nloga)$。
```
#include<cstdio>
inline int read(){
	int a=0;char c=getchar();
	for(;c<48||c>57;c=getchar());for(;c>47&&c<58;a=a*10+c-48,c=getchar());
	return a;
}
int n,a,b,p[20],fl[20],t[20],k;
int main(){
	int f;
	n=read();
	a=read();b=read();
	for(int i=2;i*i<=a;i++){
	  f=0;
	  for(;a%i==0;)a/=i,f=1;
	  if(f)p[++k]=i;
	}if(a>1)p[++k]=a;
	for(int i=2;i*i<=b;i++){
	  f=0;
	  for(;b%i==0;)b/=i,f=1;
	  if(f)p[++k]=i;
	}if(b>1)p[++k]=b;
	for(;--n;){
	  a=read();b=read();
	  for(int j=1;j<=k;j++)
		if(a%p[j]&&b%p[j])fl[j]=1;
	}
	for(int i=1;i<=k;i++)if(!fl[i])
	  return 0*printf("%d",p[i]);
	return 0*puts("-1");
}
```

---

## 作者：Marser (赞：1)

居然没有题解也是惊了，赶紧来水一发（逃）。  
首先，我们可以看出，如果一个数是整个数列的$WCD$，那么它一定可以整除每一组中至少一个数。那如果用这个数的任意一个质因数代替它，效果其实是一样的。  
即意，如果一个数是整个数列的$WCD$，那么它所含的任意一个质因数都是这个数列的$WCD$。而由于题目只需输出任意一个答案，我们可以直接把答案的范围缩小到质数。  
同样的，我们可以发现，在$\sqrt{2\times10^9}$范围内，质数只有不到5200个。所以我们可以筛出这个范围内的质数，从而分解因数。如果在这个范围内不能分解完全，那么就一定只会剩余一个大质数。  
通过之前的分析，我们可以考虑这样一个算法：对数列中的第1组数，分别对其中的两个数分解因数。然后，对于分解除的质因数，我们检查后面的数是否能被它们整除。可以证明这样是有正确性保证的。  
由质数定理可以知道，算法的复杂度约为$O(\frac{\sqrt{max{a_i}}}{\ln\sqrt{max{a_i}}}\times n)$，可以通过此题。  
代码如下：  
```cpp
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define reg register
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
typedef long long ll;
const int MN=150005;
int n,pri[50005],cnt;
bool notp[50005];
int a[MN],b[MN],t[MN];
inline int calc(int x){//计算过程
	reg int tot=0,tmp=x;
	for(reg int i=1,f;i<=cnt;i++){//分解因数
		f=0;
		while(tmp%pri[i]==0)tmp/=pri[i],f=1;
		if(f)t[++tot]=pri[i];
	}
	if(tmp>1)t[++tot]=tmp;//存在大质数
	for(reg int i=1,f;i<=tot;i++){..对后面的数据check
		f=0;
		for(reg int j=2;j<=n&&!f;j++)
			if(a[j]%t[i]!=0&&b[j]%t[i]!=0)f=1;
		if(!f)return t[i];
	}
	return -1;
}
int main(){
	scanf("%d",&n);
	for(reg int i=2;i<=50000;i++)//筛素数
		if(!notp[i]){
			pri[++cnt]=i;
			for(reg ll j=1ll*i*i;j<=50000;j+=i)notp[j]=1;
		}
	for(reg int i=1;i<=n;i++)scanf("%d%d",&a[i],&b[i]);
	reg int ans1=calc(a[1]),ans2=calc(b[1]);printf("%d\n",max(ans1,ans2));
    return 0;
}
```

---

## 作者：Hutao__ (赞：0)

## 思路


根据题目的定义，先算出第一组数的因数，再去判断跟后面的数的因数是否相同，不同就删掉，最后输出一个即可。

## 代码

```cpp
//lgRMJ坏了不保证此代码能通过此题
#include<bits/stdc++.h>
using namespace std;
int n;
int f[150005],t;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		int a,b;
		cin>>a>>b;
		if(i==1){
			for(int j=2;j*j<=a;j++){
				while(a!=j){
					if(a%j==0){
						f[++t]=j;
						a/=j;
					}else break;
				}
			}
			if(a>1)f[++t]=a;
			for(int j=2;j*j<=b;j++){
				while(b!=j){
					if(b%j==0){
						f[++t]=j;
						b/=j;
					}else break;
				}
			}
			if(b>1)f[++t]=b;
			continue;
		} 
		for(int j=1;j<=t;j++)if(a%f[j]!=0&&b%f[j]!=0)f[j]=-1;
	}
	for(int i=1;i<=t;i++){
		if(f[i]!=-1){
			cout<<f[i];
			return 0;
		}
	}
	cout<<-1;
} 
```

---

## 作者：loser_seele (赞：0)

提供一个理论时间复杂度更优秀的做法。

首先不难发现只要把前两个数分解质因数，则答案一定在这些质因数之间产生。于是分解前两个数的质因子之后逐一枚举后面的数判断是否合法即可。

瓶颈在如何分解质因数，显然可以暴力 $ \mathcal{O}(\sqrt{n}) $ 分解，但这么做不够好，我们考虑用 Pollard-rho 分解质因数，可以做到 $ \mathcal{O}(n^{\frac{1}{4}}) $ 的时间复杂度内分解。

因为质因子个数是 $ \log $ 级别的，所以最后总时间复杂度 $ \mathcal{O}(\max{a_i}^{\frac{1}{4}}+n\log{\max{a_i}}) $，可以通过。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define gc c=getchar()
#define r(x) read(x)
#define ll long long
#define int long long
template<typename T>
inline void read(T&x) {
	x=0;
	T k=1;
	char gc;
	while(!isdigit(c)) {
		if(c=='-')k=-1;
		gc;
	}
	while(isdigit(c)) {
		x=x*10+c-'0';
		gc;
	}
	x*=k;
}
#define li inline
#define re register
inline int add(int a,int b,int p) {
	a+=b;
	if(a>=p)
	    a-=p;
	return a;
}
inline int mul(int a,int b,int mod) {
	return (a*b-(int)((long double)a/mod*b)*mod+mod)%mod;
}
ll pow(ll a, ll b, ll m) {
	ll ans = 1;
	for (a %= m; b; b >>= 1, a = mul(a, a, m))
	    if (b & 1) 
	    ans = mul(ans, a, m);
	return ans;
}
ll gcd(ll a,ll b) {
	return b?gcd(b,a%b):a;
}
ll lcm(ll a,ll b) {
	return a/gcd(a,b)*b;
}
bool MR_check(ll a, ll p, ll s, int d) {
	ll k = pow(a, s, p);
	if (k == 1) return true;
	for (; d; --d, k = mul(k, k, p)) {
		if (k == p - 1) 
		    return true;
		if (k == 1) 
		    return false;
	}
	return k == 1;
}
bool MR(ll x) {
	static const int cnt = 12;
	static const int p[cnt] = {
		2, 3, 5, 7, 11, 13, 17, 19, 61, 2333, 4567, 24251
	}
	;
	if (x == 1) 
	  return false;
	ll s = x - 1;
	int d = 0;
	while (!(s & 1)) 
	  ++d, s >>= 1;
	for (int i = 0; i < cnt; ++i) {
		if (x % p[i] == 0) 
		    return x == p[i];
		if (!MR_check(p[i], x, s, d)) 
		    return false;
	}
	return true;
}
namespace Pollard_Rho {
	ll PR_check(ll c, ll p) {
		ll y = rand() % p, z = y;
		int k = 1, j = 0;
		while(1145141919810) {
			z = (mul(z, z, p) + c) % p;
			ll t = gcd(p, std::abs(z - y));
			if (t > 1) 
			    return t;
			if (++j == k) 
			    y = z, k <<= 1;
		}
	}
	void factor_(ll x, std::vector<ll> &v) {
		if (x == 1) return;
		if (MR(x)) {
			v.push_back(x);
			return;
		}
		ll y = x;
		while (y == x) y = PR_check(rand() % x, x);
		factor_(y, v);
		factor_(x / y, v);
	}
	void factor(ll x, std::vector<ll> &v) {
		v.clear();
		if (!(x & 1)) {
			v.push_back(2);
			x /= (x & -x);
		}
		factor_(x, v);
		std::sort(v.begin(), v.end());
		v.erase(std::unique(v.begin(), v.end()), v.end());
	}
}
using Pollard_Rho::factor;
int a[2000020],b[2000020];
signed main() 
{
	int T=1;
	for (;T;--T) 
	{
		int n;
		r(n);
		for (int i=1;i<=n;i++)
		        r(a[i]),r(b[i]);
		vector<int>d;
		vector<int>final;
		factor(a[1],d);
		for (auto x:d)
		        final.push_back(x);
		factor(b[1],d);
		for (auto x:d)
		        final.push_back(x);
		for (auto x:final) 
		{
			bool ok=1;
			for (int i=2;i<=n;i++)
			        if(a[i]%x&&b[i]%x)
			        ok=0;
			if(ok)
			        return !printf("%d",x);
		}
		puts("-1");
	}
}
```


---

## 作者：Eason_AC (赞：0)

## Content
定义 $n$ 个数对 $(a_1,b_1),(a_2,b_2),(a_3,b_3),...,(a_n,b_n)$ 的 $\text{WCD}$ 为能够整除每个数对中至少一个数的 $>1$ 的整数。现在，给出 $n$ 个数对，请找出它们的 $\text{WCD}$，或者这 $n$ 个数对没有符合要求的 $\text{WCD}$。

**数据范围：$1\leqslant n\leqslant 1.5\times 10^5,2\leqslant a_i,b_i\leqslant 2\times 10^9$。**
## Solution
我们先把第一个数对的质因子分解出来，然后再在后面找是否有不能够满足条件的质因子，有的话就删除，否则就保留着。最后看是否还有剩下的质因子即可。
## Code
```cpp
int n, pr[150007];

int main() {
	n = Rint;
	F(i, 1, n) {
		int x = Rint, y = Rint;
		if(i == 1) {
			F(j, 2, sqrt(x)) if(!(x % j)) {pr[++pr[0]] = j; while(!(x % j)) x /= j;}
			if(x != 1) pr[++pr[0]] = x;
			F(j, 2, sqrt(y)) if(!(y % j)) {pr[++pr[0]] = j; while(!(y % j)) y /= j;}
			if(y != 1) pr[++pr[0]] = y;
		} else F(j, 1, pr[0]) if(!pr[j]) continue; else if(x % pr[j] && y % pr[j]) pr[j] = 0;
	}
	F(i, 1, pr[0]) if(pr[i]) return printf("%d", pr[i]), 0;
	printf("-1");
	return 0;
}
```

---

## 作者：Eleveslaine (赞：0)

## 题意

给出 $n$ 对数 $(a_i,b_i)$，求任意一个 $k$，使得对于所有 $1 \le i \le n$ 有 $k|a_i$ 或 $k|b_i$ 成立。若不存在输出 $-1$。

## 题解

答案即

$$
\gcd(\operatorname{lcm}(a_1,b_1),\operatorname{lcm}(a_2,b_2),...,\operatorname{lcm}(a_n,b_n))
$$

**的任意一个因数**，当上式（设为 $ans$）等于 $1$ 时无解。下面我们证明这个结论。

先看两个引理，当 $k\le a,b$ 时：

- $k|a$ 或 $k|b \Leftrightarrow k|\operatorname{lcm}(a,b)$；  
- $k|a$ 且 $k|b \Leftrightarrow k|\gcd(a,b)$。

这两个引理可以通过唯一分解定理证明，以 $\operatorname{lcm}$ 为例：

> 设 $p_i$ 是第 $i$ 小的质数。令 $a=p_1^{n_1}p_2^{n_2}...p_x^{n_x},b=p_1^{m_1}p_2^{m_2}...p_y^{m_y}$。  
则 $\operatorname{lcm}(a,b)=p_1^{\max\{n_1,m_1\}}p_2^{\max\{n_2,m_2\}}...p_{\max\{x,y\}}^{\max\{n_x,m_y\}}$。  
令 $k=p_1^{q_1}p_2^{q_2}...p_z^{q_z}(z\le x,y)$，则 $k|a$ 等价于 $\forall i \in [1,z],q_i \le n_i$，同理 $k|b$ 等价于 $\forall i \in [1,z],q_i \le m_i$。  
$k|a$ **或** $k|b$ 成立，即 $q_i \le n_i$ 或 $q_i \le m_i$，也即 $q_i \le \max\{n_i,m_i\}$，也就是 $k|\operatorname{lcm}(a,b)$。  
（对于 $\gcd$，把 $\max$ 换成 $\min$ 即可，十分类似。）

对于每个数对 $(a_i,b_i)$，有 $k|a_i$ 或 $k|b_i$ 成立，根据引理一，即 $k|\operatorname{lcm}(a_i,b_i)$ 成立。对于所有数对，$k$ 都要满足 $k|\operatorname{lcm}(a_i,b_i)$，根据引理二，即得 $k|\gcd(\operatorname{lcm}(a_i,b_i))$。

所以对 $ans$ 质因数分解，并任意输出一个因数。  
需要注意的是，$ans$ 在 `long long` 范围内，直接 $O(\sqrt{ans})$ 分解会超时。注意到 $k$ 一定小于任意一对 $a,b$，因此我们计算 $\gcd(ans,a)$ 或 $\gcd(ans,b)$（这里的 $a,b$ 方便起见，取最后一对），分解这两个最大公约数即可。

## 代码

```cpp
// factor(x) 返回 x 最小的质因数
n=read<int>();
for(int i=1;i<=n;++i)
{
    a=read<ll>(),b=read<ll>();
    ans=gcd(ans,lcm(a,b));
}
if(ans==1)
{
    puts("-1");
    return 0;
}
else
{
    if(gcd(ans,a)!=1)
        printf("%lld\n",factor(gcd(ans,a)));
    else
        printf("%lld\n",factor(gcd(ans,b)));
}
```

---

