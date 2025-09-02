# 奉献（Dedication）

## 题目背景

不断鞭策自己的数学精神 —— 奉献。
****
「奉献之光」丽莎，既是「秩序之神」派拉的神官，亦为「无秩序之神」迪奥尼斯的信徒。

丽莎最近学习了[高精度除法](https://www.luogu.com.cn/problem/P5432)，她能以 $\Theta(n \log n)$ 的时间复杂度计算 $n$ 位整数除法了。

## 题目描述



丽莎想要制作一张 $n$ 以内正整数的除法表。具体来说，是一张记录了 $\lfloor a/b \rfloor$（$1\leq b \leq a \leq n$，$a,b$ 均为整数）的表格。她使用如下方法来制作：

>以 $a$ 为第一关键字从小到大，以 $b$ 为第二关键字从小到大的顺序枚举位置 $(a,b)$。若 $(a,b)$ 位置**未被填写**，则：
>
>计算 $\lfloor a/b \rfloor$，这需要消耗的**魔力**为 $d_a \log_2 d_a$（其中 $d_a$ 表示 $a$ 在十进制下的位数，即 $d_a=\lfloor 1+ \log_{10}a\rfloor$）。然后枚举正整数 $i$，找到所有**未被填写**的 $(ai,bi)$（$ai\leq n$）位置都填写入 $\lfloor a/b \rfloor$。每次填写需要消耗的魔力为 $d_i$。

由于美娜已经做过一张乘法表，丽莎无需魔力就可以直接计算乘法。现在丽莎想要知道，制作整个除法表需要消耗多少魔力。


为了防止精度问题，只要你的输出与标准输出的**相对误差**不超过 $10^{-6}$ 则视为正确。保证标准输出与实际答案的相对误差不超过 $10^{-10}$。

## 说明/提示

【样例 $1$ 解释】  

由于 $a \leq 6$，$d_a=1$，从而 $d_a \log_2 d_a=0$。也就是说在此范围下只有填写数字会消耗魔力。而每次 $i$ 也不超过 $6$，满足 $d_i=1$，每次填写都消耗固定 $1$ 点魔力，要填写全部 $1+2+3+4+5+6=21$ 个数消耗的魔力就是 $21$。

故答案为 $21$。

【数据范围】  

**本题采用捆绑测试。**  

Subtask 1（15 pts）：$n\le 5000$；  
Subtask 2（15 pts）：$n\le 10^5$；  
Subtask 3（30 pts）：$n\le 2 \times 10^6$；  
Subtask 4（40 pts）：无特殊限制。

对于全部的数据，$1\le n \le 2 \times 10^7$。  

【提示】

$\log_2 n$ 读作「以 $2$ 为底的 $n$ 的对数」。设 $x=\log_2n$，它表示 $2^x=n$。

## 样例 #1

### 输入

```
6```

### 输出

```
21.0000000```

## 样例 #2

### 输入

```
20```

### 输出

```
422.0000000```

## 样例 #3

### 输入

```
233```

### 输出

```
99838.0384544```

# 题解

## 作者：NaCly_Fish (赞：13)

首先按照题意模拟，我们可以得到这样一段代码：
```cpp
double ans = 0;
for(int a=1;a<=n;++a){
    int len = d(a);
    for(int b=1;b<=a;++b){
        if(vis[a][b]) continue;
        ans += len*log2(len);
        for(int i=1;a*i<=n;++i){
            if(vis[a*i][b*i]) continue;
            vis[a*i][b*i] = true;
            ans += d(i);
        }
     }
}
```
经过一些测试可以发现，最内层循环中判断 $(ai,bi)$ 是否被填写过其实是不必要的，即这个位置**一定没被填写**。

为什么呢？我们可以先证明找到的 $b$ 都满足 $\gcd(a,b)=1$ —— 因为如果 $\gcd(a,b)=d$ 且 $d>1$，则在此之前一定找到过 $(a/d,b/d)$ 位置，然后将其整数倍位置上都填了数（这其中也包括 $(a,b)$ 位置）。对于 $\gcd(a,b)=1$ 的位置，不能从一个较小的位置算出它，这就证明了结论。

现在答案就可以写为：

$$\sum_{a=1}^n \sum_{b=1}^a[\gcd(a,b)=1]\left( d_a\log_2 d_a+\sum_{i=1}^{\lfloor n/a \rfloor} d_i\right)$$

可以发现括号里那一大块是和 $b$ 无关的，可以直接记为 $f(a)$。只要求出 $d_i$，$f(a)$ 就可以直接用前缀和来计算。根据简单的递推公式 $d_i=1+d_{\lfloor i/10 \rfloor}$ 就能以 $\Theta(n)$ 的时间复杂度处理。

现在答案是
$$\sum_{a=1}^n f(a) \sum_{b=1}^a [\gcd(a,b)=1]$$
现在的问题就是要求出 $a$ 以内与其互质的正整数个数，这个就是欧拉函数 $\varphi(a)$。如果不了解相关知识，也可以在 OEIS 上搜索来得到结论。因为它是积性函数，可以使用[线性筛](https://www.luogu.com.cn/problem/P3383)的方法求出 $n$ 以内的所有函数值。

总时间复杂度为 $\Theta(n)$。当然也可以使用一些积性函数求和的方法做到更快，但那样这题就不能放在 B 题的位置了。

---

## 作者：L_zaa_L (赞：8)

如果一个位置 $(a,b)$ 的 $\gcd(a,b)\not = 1$，那么它在之前的 $(\frac{a}{\gcd(a,b)},\frac{b}{\gcd(a,b)})$ 肯定会先把这里填了，所以最后其实需要填的位置就应该是所有满足 $1\le b\le a\le n$ 且 $\gcd(a,b)=1$ 的点对，然后这一部分，我们可以枚举 $a$，计算的代价就是 $d_a\log d_a\times \varphi(a)$。

然后对于后面枚举没有填的位置时，实际上只要满足 $1\le i\le \lfloor\frac{n}{a}\rfloor$，这个位置肯定是没有被填到的，我们只需要计算 $\sum_{i=1}^{\lfloor\frac{n}{a}\rfloor} d_i$ 之和，然后这个显然是可以预处理前缀和 $f_i$ 得出来的。

然后最后的式子就是 $\displaystyle\sum_{a=1}^n \varphi(a)\times(f_{\lfloor\frac{n}{a}\rfloor}+d_a\log d_a)$。

时间复杂度：$O(n)$。

## Code

```cpp
#include<bits/stdc++.h>
//#define int long long
#define ls(x) ((x)*2)
#define rs(x) ((x)*2+1)
#define Debug(...) fprintf(stderr, __VA_ARGS__)
#define For(i,a,b) for(int i=a,i##end=b;i<=i##end;i++)
#define Rof(i,a,b) for(int i=a,i##end=b;i>=i##end;i--)
#define rep(i,  b) for(int i=1,i##end=b;i<=i##end;i++)
using namespace std;
const int N=2e7+5,Mod=998244353;
//char buf[(1<<21)+5],*p1,*p2;
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
inline void chmx(int &x,int y){(x<y)&&(x=y);}
inline void chmn(int &x,int y){(x>y)&&(x=y);}
//typedef __int128_t i128;
//i128 _base=1;
//inline int mol(int x){return x-Mod*(_base*x>>64);}
//inline void Add(int &x,int y){x=mol(x+y+Mod);}
inline int read(){
	int f=0,x=0;
	char ch=getchar();
	while(!isdigit(ch)){f|=(ch=='-');ch=getchar();}
	while(isdigit(ch)){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return f?-x:x;
}
int T,n;
int prm[N/10],tot,phi[N],cnt;
bool v[N];
int qzh[N];
double lg[15],t; 
signed main(){
	//_base=(_base<<64)/Mod;
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	// ios::sync_with_stdio(false);
	// cin.tie(0); cout.tie(0);
	n=read();
    phi[1]=1,prm[1]=0;
    For(i,2,n){
        if (!v[i]) { prm[++cnt]=i, phi[i]=i-1; }
        for(int j=1;j<=cnt && i*prm[j]<=n;++j){
            v[i*prm[j]]=1;
            if(i%prm[j]==0) { phi[i*prm[j]]=phi[i]*prm[j]; break; }
            phi[i*prm[j]]=phi[i]*(prm[j]-1);	
        }	
    }
	double ans=0;
	int res=0;
	int d=1,s=1;
	For(i,1,n){
		if(((s<<3)+(s<<1))<=i){
			s=((s<<3)+(s<<1));
			d++;
		}
		qzh[i]+=qzh[i-1]+d;
	}
	d=s=1;
	For(i,1,10) lg[i]=log2(i);
	For(i,1,n){
		if(((s<<3)+(s<<1))<=i){
			s=((s<<3)+(s<<1));
			d++;
		}
		ans+=1.0*phi[i]*qzh[n/i]+1.0*(phi[i])*(d)*lg[d];
//		cout<<fixed<<setprecision(10)<<d<<" ";
	}
//	cout<<res<<endl;
	cout<<fixed<<setprecision(10)<<ans<<endl;
#ifdef LOCAL
    Debug("\nMy Time: %.3lfms\n", (double)clock() / CLOCKS_PER_SEC);
#endif
	return 0;
}
```

---

## 作者：可爱的小棉羊 (赞：3)

首先我们要思考一下什么时候我们才会填 $(a,b)$ 这个格子。

假如 $\gcd(a,b)=d>1$ 那么我们就会在填 $(\frac a d,\frac b d)$ 时（显然这个格子会比 $(a,b)$ 先填）就把 $(a,b)$ 一起填上。

而假如 $\gcd(a,b)=1$ 那么不存在一个格子 $(a',b')$ 使得 $\frac{a}{a'}=\frac{b}{b'}=d$ 为整数。

那么问题转换成：

$$\sum_{i=1}^n\sum_{j=1}^i[\gcd(i,j)=1](d_i \log_2 d_i+\sum_{k=1}^{\lfloor \frac{n}{i}\rfloor}d_k)$$

显然后面那一坨与 $j$ 没有半毛钱关系提到前面去。

$$\sum_{i=1}^n(d_i \log_2 d_i+\sum_{k=1}^{\lfloor \frac{n}{i}\rfloor}d_k)\sum_{j=1}^i[\gcd(i,j)=1]$$

后面显然是欧拉函数：

$$\sum_{i=1}^n(d_i \log_2 d_i+\sum_{k=1}^{\lfloor \frac{n}{i}\rfloor}d_k)\varphi(i)$$

此时做法很明显了，$\sum_{k=1}^{\lfloor \frac{n}{i}\rfloor}d_k$ 可以暴力地算前缀和，而 $\varphi$ 可以线性筛，枚举 $i$ 就可以了。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int cnt,phi[20000006],n;
long long prime[10000005];
int d[20000006];
long long sumd[20000006];
bool book[20000006];
long double ans;
void init(){
	book[1]=phi[1]=1;
	for(int i=2;i<=n;i++){
		if(!book[i]){
			prime[++cnt]=i;
			phi[i]=i-1;
		}
		for(int j=1;1ll*prime[j]*i<=n&&j<=cnt;j++){
			book[i*prime[j]]=1;
			if(i%prime[j]==0){
				phi[i*prime[j]]=phi[i]*prime[j];
				break;
			}
			phi[i*prime[j]]=phi[i]*phi[prime[j]];
		}
	}
}
int main(){
	cin>>n;
	init();
	for(int i=1;i<=n;i++){
		d[i]=1+d[i/10];
		sumd[i]=sumd[i-1]+d[i];
	}
	for(int i=1;i<=n;i++){
		long double sum=((long double)log2(d[i])*d[i]+sumd[n/i])*phi[i];
		ans+=sum;
	}
	printf("%.9Lf",ans);
}
```

---

## 作者：myster1ous (赞：2)

## 题解

### Subtask 1 $(1 \leq n \leq 5000, 15\text{pts})$

直接循环 $1 \leq a \leq n, 1 \leq b \leq a$，暴力计算答案。

时间复杂度：$\mathcal{O}(n^2)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double

const int maxn = 5010;

int n;
double magics;
int Dmrm[maxn * 100];
int mp[maxn][maxn];

int D(int x) {
	return floor(1 + log10(x));
}

signed main() {
	std::cin >> n;
	
	for (int a = 1; a <= n; a++)
		for (int b = 1; b <= a; b++) {
			if (!mp[a][b]) {
				double Da = D(a);
				magics += Da * log2(Da);
				for (int i = 1; i * a <= n; i++)
					if (!mp[a * i][b * i]) {
						mp[a * i][b * i] = a / b;
						magics += D(i);
					}
			}
		}
	
	std::cout << magics;
	return 0;
}
```

### AC $(1 \leq n \leq 2 \times 10^7, 100\text{pts})$

考虑优化上面那个 $15$ 分代码。首先，我们不难想到 `!mp[a][b]` （即原题中的需要重新计算 $\lfloor\dfrac{a}{b}\rfloor$ 的）这一段会且仅会在 $\gcd(a, b) = 1$ 时被进入：因为如果 $\gcd(a, b) \neq 1$ 的话，`mp[a][b]` 肯定会在之前被填掉。

然后我们不难发现 $d_a \log_2 d_a$ 这一个算的代价和 $b$ 没有关系，所以我们可以只枚举 $1 \leq a \leq n$，并对每一个 $a$ 算出有多少个 $b$ 满足 $\gcd(a, b)=1$，即：在 $1 \sim a - 1$ 内有多少个 $b$ 和 $a$ 互质，也就是 $\varphi(a)$ （欧拉函数），所以计算除法的代价就是：$\sum\limits^{n}_{a=1}d_a \log_2 d_a \times \varphi(a)$。

然后我们来算填的代价。原题给的代价是 $\sum\limits^{\frac{n}{a}}_{i=1} d_i$。不难想到，我们可以直接用一个前缀和来求，即 $s_{\lfloor\frac{n}{a}\rfloor}$（$s_i = \sum\limits^1_{i=1} d_i$），所以这一段的代价就是 $\sum\limits^n_{a=1}s_{\lfloor\frac{n}{a}\rfloor}$。

所以我们就得到了这一题的“终极”公式：

$$
\begin{aligned}
\text{ans}& = \sum\limits^n_{a=1}d_a \log_2 d_a \times \varphi(a) + s_{\lfloor\frac{n}{a}\rfloor}\\
d_i &= \lfloor1+\log_{10} i\rfloor
\end{aligned}
$$

代码直接套公式即可。

### AC 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double

const int maxm = 5010;
const int maxn = 20000010;

int n;
double magics;
int phi[maxn], Dsum[maxn], Darr[maxn]; 
std::bitset<maxn> bs;
std::vector<int> primes;

int D(int x) {
	return floor(1 + log10(x));
}

void Sieve(int x) {
	phi[1] = 1;
	bs[1] = 1;
	for (int i = 2; i <= n; i++) {
		if (!bs[i]) {
			primes.emplace_back(i);
			phi[i] = i - 1;
		}
		for (int j = 0; i * primes[j] <= n; j++) {
			bs[i * primes[j]] = 1;
			if (i % primes[j] == 0) {
				phi[i * primes[j]] = phi[i] * primes[j];
				break;
			}
			phi[i * primes[j]] = phi[i] * (primes[j] - 1);
		}
	}
}

signed main() {
	std::cin >> n;
	
	Sieve(n);
	
	for (int i = 1; i <= n; i++)
		Darr[i] = D(i); 
	
	for (int i = 1; i <= n; i++)
		Dsum[i] = Dsum[i - 1] + Darr[i];
	
	for (int a = 1; a <= n; a++) {
		int Da = Darr[a];
		magics += Da * 1.0 * log2(Da) * phi[a];
		magics += Dsum[n / a] * phi[a];
	}
	
	std::cout << std::fixed << std::setprecision(10) << magics << "\n";
	return 0;
}
```

---

## 作者：lbmzxhb (赞：1)

[题目传送门](/problem/P10321)

# 思路：

总魔力可以分为两个部分：计算的魔力和填写的魔力，考虑分开统计。

### 计算的魔力统计：

容易发现，只有当 $\gcd(a,b)=1$ 时才需计算。于是得出式子（$f(n)$ 为计算总魔力）：

$$\begin{aligned}
f(n)&=\sum_{a=1}^n\sum_{b=1}^ad_a\log_2d_a[\gcd(a,b)=1]\\
&=\sum_{a=1}^nd_a\log_2d_a\sum_{b=1}^a[\gcd(a,b)=1]\\
&=\sum_{a=1}^nd_a\log_2d_a\varphi(a)
\end{aligned}$$

发现还是不好算，可以将位数相同的一起算，最后再加起来就行了。

### 填写的魔力统计：

填写 $(a,b)$ 时的魔力显然为 $d_{\gcd(a,b)}$，可得出式子（$g(n)$为填写总魔力）：

$$\begin{aligned}
g(n)&=\sum_{a=1}^n\sum_{b=1}^ad_{\gcd(a,b)}\\
&=\sum_{k=1}^nd_k\sum_{a=1}^n\sum_{b=1}^a[\gcd(a,b)=k]\\
&=\sum_{k=1}^nd_k\sum_{a=1}^{\lfloor\frac nk\rfloor}\sum_{b=1}^a[\gcd(a,b)=1]\\
&=\sum_{k=1}^nd_k\sum_{a=1}^{\lfloor\frac nk\rfloor}\varphi(a)\\
\end{aligned}$$

第二个 $\sum$ 可以用前缀和处理，以上两个部分的 $\varphi(i)$ 可以线性筛出来。

时间复杂度：$\mathcal O(n)$。

# 代码：

```cpp
#include <cstdio>
#include <bitset>
#include <cmath>
#define ldb long double
using namespace std;
const int N(2e7 + 5);
long long phi[N];
int primes[1400005], id, n;
bitset<N> nis;
int main() {
	scanf("%d", &n);
	phi[1] = nis[1] = 1;
	for (int i = 2; i <= n; i++) {
		if (!nis[i]) nis.set(i), phi[i] = i - 1, primes[++id] = i;
		for (int j = 1; j <= id && i * primes[j] <= n; j++) {
			nis[i * primes[j]] = 1;
			phi[i * primes[j]] = phi[i] * (primes[j] - 1);
			if (!(i % primes[j])) {phi[i * primes[j]] += phi[i]; break;}
		}
	}
	for (int i = 2; i <= n; i++) phi[i] += phi[i - 1];//预处理前缀和
	ldb ans(0); int now(1), t(1);
	for (; now * 10 - 1 <= n; now *= 10, t++) ans += t * (log((ldb)t) / log((ldb)2)) * (phi[now * 10 - 1] - phi[now - 1]);
	ans += t * (log((ldb)t) / log((ldb)2)) * (phi[n] - phi[now - 1]);//分段求f(n)
	for (int i = 1, d = 1, ma = 10; i <= n; i++) {
		if (i == ma) d++, ma *= 10;
		ans += d * phi[n / i];
	}//求g(n)
	printf("%.18Lf", ans);
}
```

## 后记：

写完了题解才想到 $d_i$ 可以 $\mathcal O(n)$ 预处理出来。~~写题时犯蠢了~~

~~管理求过qwq~~

---

## 作者：HDS_Acenaphthylene (赞：1)

可以发现，$(a,b)$ 未被处理，当且仅当 $\gcd(a,b)=1$，即 $a,b$ 互素。

对于确定的 $a$，对应的答案为 
$$\Large\sum_b\large (d_a\log_2d_a+\sum_{i=1}^{\lfloor \frac{n}{a}\rfloor}d_i)[\gcd(a,b)=1]$$

显然，可以用欧拉函数 $\varphi(a)$ 表示：
$$\large \varphi(a)(d_a\log_2d_a+\sum_{i=1}^{\lfloor \frac{n}{a}\rfloor}d_i)$$

加上前缀和、线性筛就可以求出答案。

```cpp
# include <bits/stdc++.h>
using namespace std;
# define N 20000005

vector<int> pri;
bool not_prime[N];
int phi[N], d[N];
double ans;

void pre(int n) {
	phi[1] = 1;
	for (int i = 2; i <= n; i++) {
		if (!not_prime[i]) {
			pri.push_back(i);
			phi[i] = i - 1;
		}
		for (int pri_j : pri) {
			if (i * pri_j > n) break;
			not_prime[i * pri_j] = true;
			if (i % pri_j == 0) {
				phi[i * pri_j] = phi[i] * pri_j;
				break;
			}
			phi[i * pri_j] = phi[i] * phi[pri_j];
		}
		ans += phi[i] * (d[i] - d[i - 1]) * log2(d[i] - d[i - 1]) + phi[i] * (d[n / i]);
		
	}
}
signed main() {
	int x;
	cin >> x;
	for(int i = 1;i <= x;i ++)
		d[i] = d[i - 1] + floor(1.0 + log10(i));
	pre(x);
	printf("%.7lf", ans + d[x]);
}
```

---

## 作者：zjpwdyf (赞：1)

一道挺不错的数论题。

在阅读此题解前，请您先学会 [欧拉函数](https://www.luogu.com.cn/problem/P2158)。

以下称：

- 计算 $\lfloor a/b \rfloor$ 的消耗 $d_a \log_2 d_a$ 为 **A 类消耗**。

- 填写 $(ai, bi)$ 的消耗 $d_a$ 为 **B 类消耗**。

不难发现，数对 $(a,b)$ 有 A 类消耗，当且仅当 $d=\gcd(a,b)=1$。因为若 $d>1$，则当时在计算 $(a/d, b/d)$ 时，也顺便将 $(a,b)$ 填了起来。

所以对于所有 $(a,b)$ 且 $\gcd(a,b) = 1$ 的位置，考虑分别计算两类消耗。

A 类消耗：即 $d_a \log_2 d_a$。

B 类消耗：因为填充了 $(a,b),(2a,2b),\dots, (\lfloor n/a \rfloor a, \lfloor n/a \rfloor b)$，故消耗为 $\sum_{i=1}^{\lfloor n/a \rfloor} d_i$。

不难发现，$(a,b)$ 所带来的消耗仅与 $a$ 有关，而与 $b$ 无关。换而言之，一行的总消耗 $=$ 单个互质数对的消耗 $\times$ 该行互质数对数量。

由于第 $a$ 行的所有互质数对的数量为 $\varphi(a)$，故该行总消耗 $ = \varphi(a)\times (d_a\log_2d_a+\sum_{i=1}^{\lfloor n/a \rfloor} d_i)$，然后从小到大枚举 $a$ 统计即可。

具体实现时，用线性筛预处理 $\varphi$ 数组，另外再预处理 $d$ 数组及其前缀和，时间复杂度 $O(n)$。

AC 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e7 + 5;
int n, phi[N], lg[N], sum[N];
double ans;
vector <int> prm;
bool flag[N];

int main(){
	cin >> n;
	phi[1] = 1;
	for(int i = 2; i <= n; i++){
		if(!flag[i]){
			prm.push_back(i);
			phi[i] = i - 1;
		}
		for(int j : prm){
			if(i * j > n) break;
			flag[i * j] = 1;
			if(i % j == 0){
				phi[i * j] = phi[i] * j;
				break;
			}
			phi[i * j] = phi[i] * phi[j];
		}
	}
	for(int i = 1; i <= n; i++){
		lg[i] = lg[i / 10] + 1;
		sum[i] = sum[i - 1] + lg[i];
	}
	for(int i = 1; i <= n; i++){
		ans += phi[i] * lg[i] * log2(lg[i]);
		ans += phi[i] * sum[n / i];
	}
	printf("%.10lf", ans);
	return 0;
}
```

---

## 作者：sbno333 (赞：1)

这道题不要被迷惑了，其实并不是特别的难。

我们考虑暴力，最外层为枚举 $a$，里面枚举 $b$，我们发现没被标记当且仅当 $a,b$ 互质。

我们假设不互质没被标记，则一定存在 $x,y,k$ 使得 $a=kx,b=ky,k>1$，此时肯定已经被标记，因此不成立。

假设互质的被标记，则存在 $x,y,k$，使得 $kx=a,ky=b$。

显然 $k\not=1$ 是必须存在的，并且 $x,y$ 为正整数。

这显然不可能，因此互质是没被标记的充分必要条件。

我们发现每次枚举到的 $b$ 所消耗的魔力一定仅与 $a$ 相关，因为在 $d_a\log_2d_a$ 仅与 $a$ 相关，枚举的贡献显然为 $\sum\limits_{i=1}^{\lfloor\cfrac{n}{a}\rfloor}d_i$，只与 $a$ 相关。

由于给的 $n$ 为线性范围，这就好办了。

设 $z(a)$ 为每次匹配到 $b$ 时产生的消耗。

$z(a)=d_a\log_2d_a+\sum\limits_{i=1}^{\lfloor\cfrac{n}{a}\rfloor}d_i$，由于要求线性，为了防止求 $\log$ 时产生的不为人知的时间，因此可以线性预处理 $d_i$，由于 $d_i$ 不可能大于 $100$，因此可以很快预处理 $\log_2x$。

对于 $\sum\limits_{i=1}^{\lfloor\cfrac{n}{a}\rfloor}d_i$，显然就是前缀和，简单预处理即可。

与 $a$ 互质的数的个数为 $\varphi(a)$ 个。

因此答案为 $\sum\limits_{i=1}^n\varphi(i)z(i)$。

欧拉函数显然可以线性得到。

然后就轻松能写出代码啦！

```cpp
#include<bits/stdc++.h>
using namespace std;
int d[20000009];
int phi[20000009];//计算欧拉函数
int q[2000009];
bool vis[20000009];
double lg2[109];
int inn;
int main(){
	for(int i=1;i<=20000000;i++){//这样就不用使用时间复杂度不为人知的自带函数啦
		d[i]=d[i/10]+1;//预处理出位数
	}
	for(int i=1;i<=20000000;i++){
		d[i]+=d[i-1];//前缀和
	}
	vis[1]=1;//欧式筛
	phi[1]=1;
	for(int i=2;i<=20000000;i++){
		if(!vis[i]){
			q[++inn]=i;
			phi[i]=i-1;
		}
		for(int j=1;j<=inn&&q[j]*i<=20000000;j++){
			vis[q[j]*i]=1;
			phi[q[j]*i]=phi[i]*(q[j]-1);
			if(i%q[j]==0){
				phi[q[j]*i]=phi[i]*q[j];
				break;
			}
		}
	}
	double s;
	s=0;
	for(int i=1;i<=100;i++){
		lg2[i]=log(i*1.0)/log(2.0);//这里朴素预处理即可
	}
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		s+=phi[i]*((d[i]-d[i-1])*lg2[(d[i]-d[i-1])]+d[n/i]);//这里 z 函数不需要预处理
	}
	printf("%.8lf",s);//输出答案，多几位更靠谱
	return 0;
} 
```

---

## 作者：forever_nope (赞：1)

首先，我们发现我们要填充一个三角形式的区域。

容易发现，如果一个点的坐标 $(x,y)$ 可以写为 $(\lambda x_0,\lambda y_0)$ 的形式，

其中 $x_0\perp y_0$，$\lambda\neq1$。

也就是 $\lambda=\gcd(x,y)$，那么这个点一定被 $(x_0,y_0)$ 计算过了。

也就是如果 $\gcd(x,y)\neq1$，我们可以在 $(x_0,y_0)$ 的位置去计算它的贡献。

因此我们可以最简单的枚举每一个点，然后判断这个点是否需要单独计算。

对于需要单独计算的点，我们首先加上这个点去计算除法的消耗 $d_a\log_2d_a$。

然后考虑这个点去处理其他的点的消耗，即计算 $k$ 倍的贡献，

也就是 $n$ 以内的所有 $a$ 的倍数都要被处理，比如我们手模一组：

- 当 $n=6$，$a=3$，$b=2$ 时：
- 需要计入的贡献有：
- $d_a\log_2d_a=3\log_23$；
- $k=1$（$3,2$），$k=2$（$6,4$）。

易发现我们就是对 $1\sim\lfloor n/a\rfloor$ 的 $d_k$​​ 求和，可以前缀和处理。

不过我们要理解一下为什么是 $n/a$ 而不是 $n/b$。

额其实也不用理解，因为 $a\ge b$（回顾一下题面，别忘了要求啥）。

然后我们推式子吧！可以很容易的得出答案的式子：
$$
\mathit{Ans}=\sum_{a=1}^n\sum_{b=1}^a[\gcd(a,b)=1](d_a\log_2d_a+\sum_{k=1}^{\lfloor n/a\rfloor}d_k)
$$
注意到对 $d_k$ 求和很烦人，因此记 $s_k$ 表示从 $1$ 对 $d$ 求和：
$$
\mathit{Ans}=\sum_{a=1}^n\sum_{b=1}^a[\gcd(a,b)=1](d_a\log_2d_a+s_{\lfloor n/a\rfloor})
$$
注意到后面的式子与 $b$​ 无关，因此：
$$
\mathit{Ans}=\sum_{a=1}^n(d_a\log_2d_a+s_{\lfloor n/a\rfloor})\sum_{b=1}^a[\gcd(a,b)=1]
$$
注意到后面的东西就是欧拉函数 $\varphi$，因此：
$$
\mathit{Ans}=\sum_{a=1}^n\varphi(a)\cdot(d_a\log_2d_a+s_{\lfloor n/a\rfloor})
$$
然后预处理 $d_k$、$s_k$、$\varphi(a)$ 即可，代码：

```cpp
#include <bits/stdc++.h>

using namespace std;

int n;

vector<int> d, s;
vector<double> q;

vector<int> primes, isprime;
vector<int> phi;

void init() {
    d.resize(n + 1), s.resize(n + 1), q.resize(n + 1);
    for (int i = 1; i <= n; ++i) d[i] = d[i / 10] + 1, s[i] = s[i - 1] + d[i], q[i] = d[i] * log2(d[i]);
}

void euler() {
    primes.clear(), isprime.resize(n + 1, 1), phi.resize(n + 1);
    phi[1] = 1; for (int i = 2; i <= n; ++i) {
        if (isprime[i]) primes.push_back(i), phi[i] = i - 1;
        for (int j : primes) {
            if (j * i > n) break; isprime[j * i] = 0;
            if (i % j) phi[j * i] = phi[i] * (j - 1);
            else { phi[j * i] = phi[i] * j; break; }
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    cin >> n; init(); euler(); double res = 0;
    for (int a = 1; a <= n; ++a) res += phi[a] * (q[a] + s[int(n / a)]);
    printf("%.10lf", res); return 0;
}
```

本人是在考场上没有把式子写下来（其实是太菜不会），没有发现 $\varphi$ 这么好（简单）的东西。

---

## 作者：zyn_ (赞：0)

# P10321 奉献（Dedication）

## 预处理

线性求出 $d_i$，$\varphi(i)$，$\mu(i)$。

## 第一部分：求计算的魔力

当且仅当 $\gcd(a,b)=1$ 时，需要计算 $\lfloor a/b\rfloor$，消耗的魔力为：

$$
\begin{aligned}
\sum_{i=1}^{n}\sum_{j=1}^{i}[\gcd(i,j)=1]d_i\log_{2}d_i & = \sum_{i=1}^{n}d_i\log_{2}d_i\sum_{j=1}^{i}[\gcd(i,j)=1] \\
& = \sum_{i=1}^{n}d_i\log_{2}d_i\varphi(i)
\end{aligned}
$$

可 $O(n)$ 计算。

## 第二部分：求填写的魔力

填写 $(a,b)$ 时，消耗的魔力为 $d_{\gcd(a,b)}$。

$$
\begin{aligned}
\sum_{i=1}^{n}\sum_{j=1}^{i}d_{\gcd(a,b)} & = \frac{1}{2}(\sum_{i=1}^{n}\sum_{j=1}^{n}d_{\gcd(a,b)}+\sum_{i=1}^{n}d_{\gcd(i,i)}) \\
& = \frac{1}{2}(\sum_{i=1}^{n}\sum_{j=1}^{n}d_{\gcd(a,b)}+\sum_{i=1}^{n}d_i) \\
\sum_{i=1}^{n}\sum_{j=1}^{n}d_{\gcd(a,b)} & = 
\sum_{t=1}^{n}\sum_{i=1}^{\lfloor\frac{n}{t}\rfloor}\sum_{j=1}^{\lfloor\frac{n}{t}\rfloor}[\gcd(i,j)=1]d_t \\
& = \sum_{t=1}^{n}d_t\sum_{i=1}^{\lfloor\frac{n}{t}\rfloor}\sum_{j=1}^{\lfloor\frac{n}{t}\rfloor}\sum_{k\mid\gcd(i,j)}\mu(k) \\
& = \sum_{t=1}^{n}d_t\sum_{k=1}^{\lfloor\frac{n}{t}\rfloor}\mu(k)\sum_{i=1}^{\lfloor\frac{n}{tk}\rfloor}\sum_{j=1}^{\lfloor\frac{n}{tk}\rfloor}1 \\
& = \sum_{t=1}^{n}d_t\sum_{k=1}^{\lfloor\frac{n}{t}\rfloor}\mu(k)(\lfloor\frac{n}{tk}\rfloor)^2
\end{aligned}
$$

使用二维整除分块做到 $O(\sqrt n\times \sqrt n)=O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 20000009
#define ll long long
int t[N],s[N];
ll n,mu[N],phi[N],prime[N],cnt;
bool p[N];
void sieve(ll n){
    cnt=0;phi[1]=1;mu[1]=1;
    for(ll i=2;i<=n;++i)p[i]=1;
    for(ll i=2;i<=n;++i){
        if(p[i])prime[++cnt]=i,mu[i]=-1,phi[i]=i-1;
        for(ll j=1;j<=cnt&&i*prime[j]<=n;++j){
            p[i*prime[j]]=0;
            if(i%prime[j]==0){mu[i*prime[j]]=0;phi[i*prime[j]]=phi[i]*prime[j];break;}
            mu[i*prime[j]]=-mu[i];phi[i*prime[j]]=phi[i]*(prime[j]-1);
        }
    }
    for(int i=1;i<=n;++i)mu[i]=mu[i-1]+mu[i];
}
ll calc(ll a,ll b){
	static ll res;res=0;
	for(int l=1,r;l<=min(a,b);l=r+1){
		r=min(a/(a/l),b/(b/l));
		res+=(a/l)*(b/l)*(mu[r]-mu[l-1]);
	}
	return res;
}
double ans;
int main(){
	for(int i=1;i<=N-9;++i)t[i]=t[i/10]+1,s[i]=s[i-1]+t[i];
	sieve(N-9);
	cin>>n;
	for(int l=1,r;l<=n;l=r+1){
		r=n/(n/l);
		ans+=(s[r]-s[l-1])*calc(n/l,n/l); 
	}
	ans+=s[n];
	ans/=2;
	for(int i=1;i<=n;++i)ans+=((double)t[i]*log2(t[i])*phi[i]);
	printf("%.8lf",ans);
	return 0;
}
```

---

## 作者：August_Light (赞：0)

# P10321 奉献（Dedication）题解

[题目传送门](https://www.luogu.com.cn/problem/P10321)

每次遇到未填写的位置，都必然满足 $a \perp b$（$\perp$ 表示互质）。可用反证法证明。

根据题意写出以下式子：

$$\begin{aligned}
 & \sum\limits_{a=1}^n \sum\limits_{b=1}^a [a \perp b] \times \left(d_a \log_2 d_a + \sum\limits_{i=1}^{\left\lfloor\frac n a \right\rfloor} d_i\right) \\
=& \sum\limits_{a=1}^n \varphi(a) \times \left(d_a \log_2 d_a + sumd\left(\left\lfloor \dfrac n a \right\rfloor\right)\right)
\end{aligned}$$

其中 $\varphi$ 为欧拉函数，$sumd$ 为 $d$ 的前缀和，都可线性预处理。

时间复杂度 $\Theta(n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long double ld;

const int MAXN = 2e7 + 5;

int n;

vector<int> primes;
bool vis[MAXN];
int phi[MAXN];

void sieve(int n) {
    vis[1] = 1;
    phi[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!vis[i]) {
            phi[i] = i-1;
            primes.push_back(i);
        }
        for (auto j : primes) {
            int k = i * j; if (k > n) break;
            vis[k] = 1;
            if (i % j == 0) {
                phi[k] = phi[i] * j;
                break;
            }
            phi[k] = phi[i] * phi[j];
        }
    }
}

int d[MAXN], sumd[MAXN];

int main() { ios::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    sieve(n);
    for (int i = 1; i <= n; i++) {
        d[i] = 1 + log10(i);
        sumd[i] = sumd[i-1] + d[i];
    }

    ld ans = 0;
    for (int a = 1; a <= n; a++)
        ans += phi[a] * (d[a] * log2(d[a]) + sumd[n / a]);
    cout << fixed << setprecision(10) << ans << '\n';
    return 0;
}
```

---

## 作者：modfish_ (赞：0)

## 思路
显然，对于每一个 $(a,b)$，当且仅当 $\gcd(a,b)=1$ 时，它没有在之前被填写过。

不妨直接枚举：

$$\sum_{i=1}^n\sum_{j=1}^i(d_i\log_2d_i+\sum_{k=1}^{\lfloor\frac{n}{i}\rfloor}d_k)\times\epsilon(\gcd(i,j))$$

其中 $\epsilon(x)$ 为单位函数，当且仅当 $x=1$ 时为 $1$，否则为 $0$。

发现前面那一坨和 $j$ 无关，直接提到外面去：

$$\sum_{i=1}^n(d_i\log_2d_i+\sum_{k=1}^{\lfloor\frac{n}{i}\rfloor}d_k)\sum_{j=1}^i\epsilon(\gcd(i,j))$$

后面那一坨非常眼熟，不是吗？那就是欧拉函数 $\varphi$ 啊。

$$\sum_{i=1}^n(d_i\log_2d_i+\sum_{k=1}^{\lfloor\frac{n}{i}\rfloor}d_k)\times\varphi(i)$$

所有东西都是可以线性搞的。所以直接弄就行了。复杂度 $O(n)$，常数略大。

值得注意的是，虽然题目中给了 $d_i$ 的计算方法，不过那样是会超时的（常数太大），可以差分一下算，详情见代码。

## 代码
```cpp
#include <bits/stdc++.h>
#define ld double

using namespace std;

const int maxn = 2e7 + 5;

int pr[maxn], ntp[maxn], phi[maxn], cnt = 0;
ld d[maxn], dd[maxn], sumd[maxn];

void prime(int m){
	ntp[1] = phi[1] = 1;
	for(int i = 2; i <= m; i ++){
		if(!ntp[i]) pr[++ cnt] = i, phi[i] = i - 1;
		for(int j = 1; i * pr[j] <= m && j <= cnt; j ++){
			ntp[i * pr[j]] = 1;
			if(i % pr[j]) phi[i * pr[j]] = phi[i] * phi[pr[j]];
			else{
				phi[i * pr[j]] = phi[i] * pr[j];
				break;
			}
		}
	}
}

int main(){
	int n;
	scanf("%d", &n);
	prime(n);
	d[1] ++, d[10] ++, d[100] ++, d[1000] ++, d[10000] ++, d[100000] ++, d[1000000] ++, d[10000000] ++;
	for(int i = 1; i <= n; i ++) dd[i] = dd[i - 1] + d[i], sumd[i] = sumd[i - 1] + dd[i];
	ld ans = 0;
	for(int i = 1; i <= n; i ++) ans += phi[i] * (dd[i] * (logl(dd[i]) / logl(2)) + sumd[n / i]);
	printf("%.7lf\n", ans);
	return 0;
}
```

---

## 作者：__HHX__ (赞：0)

# 思路
因为 $a < a_i$ 所以 $a$ 总是比 $a_i$ 先枚举。

所以我们仅需考虑枚举 $a,b$ 互质的情况。

我们考虑枚举 $a$。

其中 $b$ 有 $\varphi(a)$ 个。

因为 $b \leq a$ 且 $ai \leq n$，所以 $i \leq \lfloor{n \over a}\rfloor$。

因为 $a \geq 1$ 所以 $i \leq n$。

考虑作前缀和数组 $z_i = \sum_{j = 1} ^ i d_j$。

整理上式得：$ans = \sum_{a = 1} ^ n \varphi(a) \cdot (z_{\lfloor{n \over a}\rfloor} + d_a \log_2 d_a)$。

---

