# Orac and LCM

## 题目描述

For the multiset of positive integers $ s=\{s_1,s_2,\dots,s_k\} $ , define the Greatest Common Divisor (GCD) and Least Common Multiple (LCM) of $ s $ as follow:

- $ \gcd(s) $ is the maximum positive integer $ x $ , such that all integers in $ s $ are divisible on $ x $ .
- $ \textrm{lcm}(s) $ is the minimum positive integer $ x $ , that divisible on all integers from $ s $ .

For example, $ \gcd(\{8,12\})=4,\gcd(\{12,18,6\})=6 $ and $ \textrm{lcm}(\{4,6\})=12 $ . Note that for any positive integer $ x $ , $ \gcd(\{x\})=\textrm{lcm}(\{x\})=x $ .

Orac has a sequence $ a $ with length $ n $ . He come up with the multiset $ t=\{\textrm{lcm}(\{a_i,a_j\})\ |\ i<j\} $ , and asked you to find the value of $ \gcd(t) $ for him. In other words, you need to calculate the GCD of LCMs of all pairs of elements in the given sequence.

## 说明/提示

For the first example, $ t=\{\textrm{lcm}(\{1,1\})\}=\{1\} $ , so $ \gcd(t)=1 $ .

For the second example, $ t=\{120,40,80,120,240,80\} $ , and it's not hard to see that $ \gcd(t)=40 $ .

## 样例 #1

### 输入

```
2
1 1```

### 输出

```
1```

## 样例 #2

### 输入

```
4
10 24 40 80```

### 输出

```
40```

## 样例 #3

### 输入

```
10
540 648 810 648 720 540 594 864 972 648```

### 输出

```
54```

# 题解

## 作者：H6_6Q (赞：32)

### 题目大意：      
给你一个长度为 $n$ 的集合 $\{a_1 , a_2\;...\;a_n\}$，请你求出 $\gcd\{ \text{lcm}(a_i,a_j)\;|\;i < j \}$

### 思路：
众所周知，$\text{lcm}(a,b)=\dfrac{a\times b}{\gcd(a,b)}$     

所以原式可以化为 $\gcd\{ \dfrac{a_i\times a_j}{\gcd(a_i,a_j)}\;|\;i < j \}$         


把 $\gcd(a_i,a_j)$ 提出可得 $\dfrac{\gcd\{ a_i\times a_j\;|\;i < j \}}{\gcd(a_1,a_2 \;...\;a_n)}$

$\gcd(a_1,a_2 \;...\;a_n)$ 可以线性求出，那么问题就转化成了如何快速求 $\gcd\{ a_i\times a_j\;|\;i < j \}$

设我们每次枚举到第 $i$ 个数 $a_i$ 为 $x$，那么可以将 $\gcd\{ x\times a_j\;|\;i < j \}$ 中的 $x$ 提出，就可以得到 $x \times \gcd(a_{i+1},a_{i+2}\;...\;a_{n})$。

可以预处理出一个后缀 $\gcd$ ，然后枚举 $a_i$ 计算答案即可。

时间复杂度：常数极小的 $\text{O}(n \log a_{max})$

记得开 $\text{long long}$ （（

### Code：
```
#include<bits/stdc++.h>
#define LL long long

using namespace std;

LL read()
{
	LL ans=0,f=1;
	char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){ans=ans*10+c-'0';c=getchar();}
	return ans*f;
}

const LL N=1e5+5;
LL n,a[N],b[N],ans;

int main()
{
	n=read();
	for(LL i=1;i<=n;++i)
		a[i]=read();
	for(LL i=n;i>=1;--i)
    // 预处理后缀 gcd
		b[i]=__gcd(b[i+1],a[i]);
	for(LL i=1;i<=n;++i)
    // 计算 gcd { ai , aj | i < j }
		ans=__gcd(ans,a[i]*b[i+1]);
    // 答案就是 gcd { ai , aj | i < j } / gcd ( a1 , a2 ... an )
	printf("%lld\n",ans/b[1]);
	return 0;
} 
```


---

## 作者：CYJian (赞：20)

看到 $\gcd$ 和 $\mathrm{lcm}$，应该立马想到对每个质因数计算贡献。（当然不是所有题都这样，但是这个很常用）

然后考虑对于一个质数 $p$ 对答案的贡献，这个先 $\rm lcm$ 再 $\gcd$ 是在干啥事情：

任取两个数的 $\rm lcm$，等价于取 $p$ 的指数 $\max$，然后再对所有的 $\rm lcm$ 取 $\gcd$，等价于对每一对 $a_i$ 的 $p$ 的指数 $\max$ 取个 $\min$。

那，$\gcd$ 里头 $p$ 的指数，不就是所有数中 $p$ 的第二大的指数嘛！

分解一下质因数，就做完了。

使用欧拉筛处理出每个数的最小质因子，复杂度 $O(n \log a_{mx})$。

$\rm Code$：

```cpp
const int MAXN = 300010;

int f[MAXN];
int g[MAXN];

int tot;
int pri[MAXN];
int chk[MAXN];
int Min[MAXN];

inline void Sieve(int n) {
	for(int i = 2; i <= n; i++) {
		if(!chk[i]) pri[++tot] = i, Min[i] = i;
		for(int j = 1; j <= tot; j++) {
			if(i * pri[j] > n) break;
			chk[i * pri[j]] = 1;
			Min[i * pri[j]] = pri[j];
			if(i % pri[j] == 0) break;
		}
	}
}

vector<int>d[MAXN];

int main() {
	Sieve(200000);
    
	int n = ri;
	for(int i = 1; i <= n; i++) {
		int x = ri;
		while(x > 1) {
			int p = Min[x], ct = 0;
			while(x % p == 0) x /= p, ++ct;
			d[p].push_back(ct);
		}
	}
    
	ll res = 1;
	for(int i = 1; i <= 200000; i++) {
		if(d[i].size() >= n - 1) {
			sort(d[i].begin(), d[i].end());
			int pw = d[i][0];
			if(d[i].size() == n) pw = d[i][1];
			while(pw--) res *= i;
		}
	}

	cout << res << endl;
	return 0;
}
```

---

## 作者：WeLikeStudying (赞：15)

顶楼大佬的思路真是妙，我就只说一些理解和补充吧。

如果理解大佬的思路的话，你就会明白：
- 这道题不需要 $O(n)$ 的后缀 $\gcd$。
- 这道题甚至不需要开数组。（当然只是为了省空间）
- 更新：提供更紧的时间界 $O(n+\log(\max\lbrace a_i \rbrace))$ 而非 $O(n\log(\max\lbrace a_i \rbrace))$。

题意是要求：
$$\gcd\lbrace\operatorname{lcm}(a_i,a_j)|i<j\rbrace$$ 
那么拆开来看，对于每一个质数 $p$，设 $e_i$ 是最大的使得 $p^{e_i}|a_i$ 的数，那么我们相当于求：
$$\min \lbrace \max(e_i,e_j)|i<j\rbrace$$
容易看出这是求$e_i$的次小值。

一种思路是直接暴力分解因式，这样是 $O(\sum\sqrt a_i)$ 的由于题目超大的时间限制可以通过本题。

但大佬将这个式子做了一个变形： 
$$\gcd\lbrace\operatorname{lcm}(a_i,a_j)|i<j\rbrace=\frac{\gcd\lbrace a_ia_j|i<j\rbrace}{\gcd\lbrace\gcd(a_i,a_j)|i<j\rbrace}$$

一开始，我大惑不解：$\gcd$ 运算明明不能将除法分离出来啊？

但后来，我明白了：对于每个质数 $p$，$\gcd\lbrace a_ia_j|i<j\rbrace$ 相当于求出了其指数的**最小值和次小值之和**，$\gcd\lbrace\gcd(a_i,a_j)|i<j\rbrace$ 则相当于求出了其指数的**最小值**，两者相减便是答案。

而这两个式子可比 $\operatorname{lcm}$ 好维护多了！

我们继续推式子：
$$\gcd\lbrace\operatorname{lcm}(a_i,a_j)|i<j\rbrace=\frac{\gcd\lbrace a_ia_j|i<j\rbrace}{\gcd\lbrace\gcd(a_i,a_j)|i<j\rbrace}$$
$$=\frac{\gcd\lbrace a_i\gcd\lbrace a_j|j<i\rbrace\rbrace}{\gcd\lbrace a_i\rbrace}$$
(似乎题解区的大佬考虑了重复的情况呢，虽然这里并不会影响正确性，在这里本蒟蒻提出一个小小的批评）

依照上面的方法，每到一个 $a_i$，我们只需要乘上我们同时间处理的 $\gcd$ ，然后对答案求 $\gcd$ 即可。可以给出我们的程序了！时间复杂度 $O(n+\log a_i)$，空间复杂度 $\Theta(n)$。

```cpp
//尊前不用翠眉颦，人生如逆旅，我亦是行人
#include<fstream>
using namespace std;
const int MAXN=1e5+1;
int n,a[MAXN],g;
long long dc=1;
long long gcd(long long a,long long b)
{
	return (a%b==0)?b:gcd(b,a%b);
}
int main()
{
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	scanf("%d",&a[i]);
	g=a[0];
	dc=1ll*a[0]*a[1];
	for(int i=1;i<n-1;i++)
	{
		long long part=1ll*g*a[i];
		g=gcd(a[i],g);
		dc=gcd(dc,part);
	}
	dc=gcd(dc,1ll*g*a[n-1]);
	g=gcd(a[n-1],g);
	printf("%lld",dc/g);
	return 0;
}
```
同样给出不需要数组的程序。时间复杂度 $O(n+\log a_i)$，证明看[这篇](https://www.luogu.com.cn/blog/luo1gu1zui1bang1/ogcds)，空间复杂度**理论上** $O(1)$ 实际上 $\gcd$ 有影响。
```cpp
//尊前不用翠眉颦，人生如逆旅，我亦是行人
#include<fstream>
using namespace std;
int n,a,g;
long long dc;
long long gcd(long long a,long long b)
{
    return !b?a:gcd(b,a%b);
}
int main()
{
    scanf("%d",&n);
    g=dc=0;
    for(int i=0;i<n;++i)
    {
        scanf("%d",&a);
        dc=gcd(1ll*g*a,dc);
        g=gcd(a,g);
    }
    printf("%lld",dc/g);
    return 0;
}
```
感谢各位大佬提供的思路。

最后给出一个有趣又简单的说明 $\gcd$ 复杂度较紧上界的方法辅助复杂度理解。
- 构造出一组数据，使得 $\gcd$ 运算 $n$ 次才能结束，且数据参数尽可能小。
- 我们尝试贪心选取。
- 第一个数显然是 $1$。 
- 第二个数至少是 $2$，取 $2$，这时需要运算 $1$ 次。
- 第三个数显然是 $a+2b$ 型，取 $3$，这时需要运算 $2$ 次。
- 于是我们构造出了这样一个数列：
$$1,2,3,5,8,13,21,34,55,89,144,233,377\dots$$
- 这个数列显然是斐波那契数列的一部分，其通项公式应该是：
$$\frac1{\sqrt 5}\bigg[\bigg(\frac{1+\sqrt5}2\bigg)^{n+2}-\bigg(\frac{1-\sqrt5}2\bigg)^{n+2}\bigg]$$
-  $n$ 代表运算次数， 结果代表该运算次数下的极小较大参数：
- $(\frac{1-\sqrt5}2)^n$小于等于1，对整个式子影响可以忽略不计。
- 设$\gcd$较大的参数为$a$，有：
$$\frac1{\sqrt 5}\bigg(\frac{1+\sqrt5}2\bigg)^{n+2}=a$$
$$n+2=\log_{\frac {1+\sqrt5}2}{\sqrt 5 a}$$
- 考虑第一次的无效操作，时间复杂度上界应该是：
$$O(-1+\log_{\frac {1+\sqrt5}2}{\sqrt 5 a})$$
- 也就是：
$$O(\log a)$$

---

## 作者：Caro23333 (赞：8)

### Orac and LCM 中文题解

下文中$p$代表质数；$v$为常数，代表$a_i$的最大值；$ans$代表答案。

**Observation.**  $p^k\ \mid\ ans$ ， 当且仅当：对于 $i=1,2,3,...,n$，有至少 $n-1$ 个 $i$ 满足 $p^k\ \mid\ a_i$。

**Proof.**  若至多 $n-2$  个 $i$ 满足 $p^k \mid a_i$，则存在 $x\neq y$，满足 $p^k\nmid a_x$ 且 $p^k\nmid a_y$。所以$p^k \nmid \textrm{lcm}(\{a_x,a_y\})$，于是 $p^k\ \nmid\ ans$；反之，若至少 $n-1$ 个 $p^k \mid a_i$ ，则任意两个数中必然至少有一个是$p^k$的倍数。那么对于任意$x,y$，必然有$p^k \mid \textrm{lcm}(\{a_x,a_y\})$，于是 $p^k\ \mid\ ans$。

接下来有两种做法：

**Solution 1.** 设 $d_i$ 为删去 $a_i$ ，剩下 $n-1$ 个数所构成的集合。那么，$\gcd(d_i)$ 必然被至少 $n-1$ 个数整除，且若有至少 $n-1$ 个 $i$ 满足 $p^k\ \mid\ a_i$，必然对于某个 $i$ 满足$p^k \mid \gcd(d_i)$。那么由**Observation**，$ans=\textrm{lcm}(\{\gcd(d_1),\gcd(d_2),\gcd(d_3),...,\gcd(d_n)\})$。

考虑如何快速计算$\gcd(d_i)$。对于每个$i$，维护前缀$pre_i=\gcd(\{a_1,a_2,...,a_i\})$与后缀$suf_i=\gcd(\{a_{i},a_{i+1},...,a_n\})$。那么$\gcd(d_i)=\gcd(\{pre_{i-1},suf_{i+1}\})$，而$pre$和$suf$显然都是可以$O(n\cdot \log(v))$计算的。

时间复杂度：$O(n \log v)$

**Solution 2.** 枚举值域内的每个质数。对于质数 $p$，我们枚举每个 $a_i$，计算出最大的 $k_i$，满足 $p^{k_i} \mid a_i$。分析**Observation**可知，所有 $i$ 中次小的 $k_i$ 就是$ans$的分解质因数形式中$p$的幂次。一个优化是，枚举时如果发现已经有 $2$ 个 $a_i$ 无法被 $p$ 整除了，那么 $ans$ 也必然无法被 $p$ 整除，于是我们就可以不再枚举剩余的 $a_i$ 了。

时间复杂度：对于每个质数，最多出现两次枚举到的 $a_i$ 不能被 $p$ 整除的情况。对于每个数，最多被除 $\log v$ 次。所以，时间复杂度就是 $O(v+n\log v)$。

Problem and Tutorial by mydiplomacy

Code for Solution 2:

```cpp
#include <iostream>
#include <cstdio>

using namespace std;
typedef long long ll;

const int maxn=100005;

int n;
ll a[maxn];

ll pre[maxn],suf[maxn];

ll gcd(ll x, ll y)
{
	if(y==0) return x;
	else return gcd(y,x%y);
}

ll ga,ans;

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	pre[1]=a[1]; suf[n]=a[n];
	for(int i=2;i<=n;i++)
		pre[i]=gcd(pre[i-1],a[i]);
	for(int i=n-1;i>=1;i--)
		suf[i]=gcd(suf[i+1],a[i]);
	for(int i=0;i<=n-1;i++)
	{
		if(i==0)
			ans=suf[2];
		else if(i==n-1)
			ans=ans*pre[n-1]/gcd(pre[n-1],ans);
		else
			ans=ans*gcd(pre[i],suf[i+2])/gcd(gcd(pre[i],suf[i+2]),ans);
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：Kizuna_AI (赞：4)

这道题要求的式子是$gcd(\{\mathrm{lcm}(a_i,a_j)|1 \leq i <j\leq n\})$

很明显可以发现的是：如果在$a_i$中，有大于等于两个数都不是$x$的倍数，那么答案中可定不会出现$x$的倍数。

这十分容易说明，我们对这两个不是$x$的倍数执行$lcm$操作，可以发现结果并没有$x$的倍数。因此，执行$gcd$操作后也不可能出现$x$的倍数。

如果只有一个数不是（或者这些数都是）$x$的倍数的话，无论你怎么两两配对进行$lcm$操作，结果都包含$x$的倍数。因此只要执行$ans*x$就行了。

最后输出$ans$就是答案。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,s[100010],maxs,ans=1,fi;
bool t[200010];
int main() {
	memset(t,1,sizeof(t));
	scanf("%I64d",&n);
	for(int i=1;i<=n;i++) {
		scanf("%I64d",&s[i]);
		maxs=max(maxs,s[i]);
	}
	t[1]=0;
	for(int i=2;i<=maxs;i++) //使用埃筛判断素数
		for(int j=i+i;j<=maxs;j+=i)
			t[j]=0;
	for(int i=2;i<=maxs;i++) {
		if(!t[i]) continue; //对于每个素数进行判断
		bool unfailed=true;
		while(unfailed) { //如果发现全部都是x的倍数/只有一个数不是x的倍数，那么就继续查。
			fi=0;
			for(int j=1;j<=n;j++) {
				if(s[j]%i!=0) {
					if(fi==0) fi=j;
					else {
						unfailed=false;
						break;
					}
				}
			}
			if(!unfailed) break;
			for(int j=1;j<=n;j++)
				if(j!=fi) s[j]/=i;
			ans=(long long)ans*i;//是$x$的倍数，乘起来
		}
		
	}
	printf("%I64d\n",ans);
	return 0;
}
```

很显然的是，这样写法并不会超时，如果不知道原因，可以在评论区留言或者私信我。

---

## 作者：juicyyou (赞：2)

# CF1349A Orac and Factors
## 题目大意：
给定一个数列 $a$ 求：
$$\large{\gcd\{\operatorname{lcm}\{a_i, a_j\}(1 \le i < j \le n)\}}$$
的值。
## 解法：
首先，我们令：
$$\large{a_1 = 2^{p_{1, 1}}3^{p_{1, 2}}5^{p_{1, 3}}}\cdots m^{p_{1, k}}$$
$$\large{a_2 = 2^{p_{2, 1}}3^{p_{2, 2}}5^{p_{2, 3}}}\cdots m^{p_{2, k}}$$
$$\large{a_3 = 2^{p_{3, 1}}3^{p_{3, 2}}5^{p_{3, 3}}}\cdots m^{p_{3, k}}$$
即对所有数分解质因数，没有这个质因子的指数直接写 0。然后，通过小奥可知，两数的 $\operatorname{lcm}$ 就是两数所有质因子的指数取 $\max$ 后的幂再相乘，而 $\gcd$ 则是取 $\min$ 之后的幂相乘。那么答案就是所有质数在所有 $a_i$ 中指数的第二大的幂的乘积了。令：
$d_i$ 表示第 $i$ 个质数在所有 $a_x$ 中的第二大指数，$f_i$ 表示第 $i$ 个质数，那么则有：
$$\large{ans = \prod {f_i}^{d_i}}$$
直接算即可。

下面是我的Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const ll maxn = 2e5 + 5;
const ll maxm = 1e3 + 5;
inline void qread(){}
template<class T1, class ...T2>
inline void qread(T1 &IEE, T2&... ls){
	register T1 __ = 0, ___ = 1;
	register char ch;
	while(!isdigit(ch = getchar())) ___ = (ch == '-') ? -___ : ___;
	do{
		__ = (__ << 1) + (__ << 3) + (ch ^ 48);
	}while(isdigit(ch = getchar()));
	__ *= ___;
	IEE = __;
	qread(ls...);
	return ;
}
ll ans, n;
ll a[maxn];
vector<ll> v[maxn];
ll poww(ll s, ll l){
	ll res = 1, y = l;
	for(int i = 1;i <= l;i++){
		res = res * s;
	}
	return res;
}
int main(){
	qread(n);
	for(int i = 1;i <= n;i++){
		qread(a[i]);
		ll tmp = a[i];
		for(int j = 2;j * j <= tmp;j++){
			if(tmp % j != 0) continue;
			ll cnt = 0;
			while(tmp % j == 0){
				cnt++;
				tmp /= j;
			}
			v[j].push_back(cnt);
		}
		if(tmp){
			v[tmp].push_back(1);
		}
	}
	ans = 1;
	for(int i = 2;i <= 200000;i++){
		if(v[i].size() == 0) continue;
		sort(v[i].begin(), v[i].end());
		ll p = v[i].size();
		if(n - p >= 2){
			ans *= 1;
			continue;
		}
		if(n - p == 1){
			ans *= poww(i, v[i][0]);
			continue;
		}
		ans *= poww(i, v[i][1]);
	}
	cout << ans << endl;
	return 0;
}
```

上述算法的复杂度即为 $\mathcal O(n\sum \sqrt{a_i})$， 可以通过此题。

---

## 作者：KellyFrog (赞：2)

### 《数学差的一比的蒟蒻怎么靠打暴力解决数学题》
前排提示：这个是非主流做法。

题目要求$\gcd(\{\text{lcm}(\{a_i,a_j\})\})$，做一个小变形。

$\gcd(\{\text{lcm}(\{a_i,a_j\})\})=\gcd(\{\frac{a_i\cdot a_j}{\gcd(\{a_i\cdot a_j\})}\})=\frac{\gcd(\{a_i\cdot a_j\})}{\gcd(\{a_i\})}=\frac{\gcd(\{a_i\cdot\gcd(\{ a_j\})\})}{\gcd(\{a_i\})}$

现在问题就变成了求$\gcd({a_j}),j\neq i$。

预处理前缀和后缀$\gcd$，总的复杂度$O(n\cdot\gcd(\max{a_i}))$。

code:
```cpp
#include <iostream>

#define int long long

using namespace std;

int gcd(int x, int y) {
	if(x < y) {
		swap(x, y);
	}
	if(y == 0) {
		return x;
	}
	return gcd(x % y, y);
}

const int MAXN = 1e5 + 5;

int first[MAXN], second[MAXN]; 
int num[MAXN], gc[MAXN];

signed main() {
	int t, n;
	
	cin >> n;
	for(int i = 1; i <= n; i++) {
		cin >> num[i];
	}
	
	first[1] = num[1];
	for(int i = 2; i <= n; i++) {
		first[i] = gcd(num[i], first[i - 1]);
	}
	
	second[1] = num[n];
	for(int i = 2; i <= n; i++) {
		second[i] = gcd(num[n - i + 1], second[i]);
	}
	
	for(int i = 1; i <= n; i++) {
		if(i == 1) {
			gc[i] = num[i] * second[n - 1];
		} else if(i == n) {
			gc[i] = num[i] * first[n - 1];
		} else {
			gc[i] = num[i] * gcd(first[i - 1], second[n - i]);
		}
	}
	
	int ans = gc[1];
	
	for(int i = 1; i <= n; i++) {
		ans = gcd(ans, gc[i]);
	}
	
	cout << ans / first[n] << endl;

	return 0;
}
```

---

## 作者：TEoS (赞：0)

本文同步发表在[我的blog](https://www.cnblogs.com/TEoS/p/12891402.html)

------------
**题意分析**

给出$n$个数，求这$n$个数两两的最小公倍数的最大公约数

**思路分析**

通过分析样例可以发现，如果要成为这$n$个数两两的最小公倍数的公约数，至少要是这$n$个数中$n-1$个数的约数，否则就至少会有两个数的最小公倍数无法被这个数整除。

所以只要找出所有满足至少是这$n$个数中的$n-1$个数的约数的数就可以了。找的方法很简单，只要每个数去试一下能整除被几个数就可以了。这里有几个需要注意的点：

- 找出的数应该是质数，否则可能会因为该数的约数已被找出而出错。可以不必先筛出质数，从小到大依次尝试并在找出一个数后除掉它可以保证找出的都是质数。
- 一个数作为约数时次数不一定为1，因此对于一个数要多次尝试
- 尝试的时候如果当前已经有2个数不能被整除，可以直接停止，节省时间

因为最后一点的剪枝，实际上全部尝试的次数很少，因此时间上完全过得去。

```cpp
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;
const int N=1e5+100;
int n,maxn;
int a[N];
ll ans=1;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]),maxn=max(maxn,a[i]);
	for(int i=2;i<=maxn;i++)
	{
		int cnt=0;
		for(int j=1;j<=n &&(cnt==j-1 || cnt==j-2);j++)
			if(a[j]%i==0)
				cnt++;//尝试能整除几个数
		if(cnt>=n-1)//满足条件
		{
			ans*=i;//累计答案
			for(int j=1;j<=n;j++)
				if(a[j]%i==0)
					a[j]/=i;//除掉
			i--;//再试一次
		}
	}
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：DD_BOND (赞：0)

一对$a[i]$和$a[j]$的$lcm$可以写成:

$ k_i*gcd_{ij}*k_j$

原问题的答案即为以下所有的值的$gcd$:


$ k_0^1*gcd_{01}*k_1^1 $  
$k_0^2*gcd_{02}*k_2^2$ &emsp;$k_1^2*gcd_{12}*k_2^2$  
$k_0^3*gcd_{03}*k_3^3$ &emsp;$k_1^3*gcd_{13}*k_3^3$&emsp;$k_2^3*gcd_{23}*k_3^3$  
... ...

则我们可以改变第$j$行的式子为:

$k_0^j*a[j]$ &emsp;$k_1^j*a[j]$ &emsp;$k_2^j*a[j]$ &emsp;... ...  

那么只需要考虑所有$k_i^j$的$gcd$的影响，记前第$j$行所有的$k_i^j$的gcd为$Kj$，前$i$个数的$gcd$为$g_i$，则满足$Kj=\frac{g_{i-1}}{g_i}$.

```cpp
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN=1e6+10;

ll gcd(ll a,ll b){ return b==0? a: gcd(b,a%b); }

ll a[MAXN];

int main(void)
{
    int n;  cin>>n;
    for(int i=0;i<n;i++)    cin>>a[i];
    ll g=gcd(a[0],a[1]),gc=g,ans=a[0]*a[1]/g;
    for(int i=2;i<n;i++){
        g=gcd(g,a[i]);
        ans=gcd(ans,gc*a[i]/g);
        gc=gcd(gc,a[i]);
    }
    cout<<ans<<endl;
    return 0;
}
```


---

## 作者：VenusM1nT (赞：0)

结论题。  
结论：定义质数 $p$，则有 $p^k\ |\ \text{ans}$ 当且仅当对于 $i=1,2,...,n$ 有 $n-1$ 个满足 $p^k\ |\ a_i$。  
证明：若至多 $n-2$ 个满足，则有 $a_i,a_j(i\not = j)$ 满足 $p^k \nmid \text{lcm}(a_i,a_j)$，则 $p^k \nmid \text{ans}$；若有 $n-1$ 个满足，则对于任意 $(i,j)$ 必有 $p^k\ |\ \text{lcm}(a_i,a_j)$，则 $p^k\ | \ \text{ans}$.  
则有做法，令 $f_i$ 为除了 $a_i$ 以外所有数的 $\text{gcd}$，则 $f_i$ 必整除 $n-1$ 个数，若 $n-1$ 个 $a_i$，满足 $p^k\ |\ a_i$，则必有 $f_i$ 满足 $p^k\ |\ f_i$，那么根据上述结论，$p^k\ |\ \text{ans}$，答案就是 $\text{lcm}(f_1,f_2,...,f_n)$.  
至于 $f_i$ 的求法，可以维护一个前缀 $\text{gcd}$，一个后缀 $\text{gcd}$，就可以快速求出每个 $f_i$。
```cpp
#include<bits/stdc++.h>
#define MAXN 100005
#define reg register
#define inl inline
#define int long long
using namespace std;
int n,a[MAXN],pre[MAXN],suf[MAXN],f[MAXN];
int Gcd(reg int x,reg int y)
{
	return !y?x:Gcd(y,x%y);
}
signed main()
{
	scanf("%lld",&n);
	for(reg int i=1;i<=n;i++) scanf("%lld",&a[i]);
	pre[1]=a[1];
	suf[n]=a[n];
	for(reg int i=2;i<=n;i++) pre[i]=Gcd(pre[i-1],a[i]);
	for(reg int i=n-1;i>=1;i--) suf[i]=Gcd(suf[i+1],a[i]);
	f[1]=suf[2];
	f[n]=pre[n-1];
	for(reg int i=2;i<=n-1;i++) f[i]=Gcd(pre[i-1],suf[i+1]);
	reg int ans=f[1];
	for(reg int i=2;i<=n;i++) ans=ans*f[i]/Gcd(ans,f[i]);
	printf("%lld\n",ans);
	return 0;
}
```

---

