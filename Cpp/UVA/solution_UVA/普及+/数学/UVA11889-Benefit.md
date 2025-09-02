# Benefit

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=226&page=show_problem&problem=2989

[PDF](https://uva.onlinejudge.org/external/118/p11889.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11889/1588740ad2fa4cdc66ad2b07066e440857631a2c.png)

## 样例 #1

### 输入

```
3
2 6
32 1760
7 16```

### 输出

```
3
55
NO SOLUTION```

# 题解

## 作者：yyc001 (赞：16)

$lcm(a,b)=\frac {ab} {gcd(a,b)}=c$

移项得 $\frac b {gcd(a,b)}=\frac c a$

左边必定是整数，所以右边不是整数的话显然无解

令 $d=\frac c a$，记函数$f(a,d)=$ “令 $\frac x {gcd(a,x)}=d$ 成立的最小的 $x$”

$a.$ 当$gcd(a,d)=1$时，显然 $x=d$

$b.$ 当$gcd(a,d)>1$时，

$\quad\quad$ 不妨设 $k=gcd(a,x) \ ^{(*)}$

$\quad\quad$ $^{(*)}$式代入$f(a,d)$，得 $x=d\cdot k$

$\quad\quad$ 上式代入$^{(*)}$式，得 $gcd(a,d\cdot k)=k$

$\quad\quad$ 记$g=gcd(a,d)$，左右两边约去 $g$ ,得到

$\quad\quad$ $gcd(\frac a g , \frac d g\cdot k)=\frac k g$

$\quad\quad$ 因为$\frac a g , \frac d g$已经互质，可以将$\frac d g$从上式中剔除，得到

$\quad\quad$ $gcd(\frac a g, k)=\frac k g$

$\quad\quad$ 移项得 $\frac k{gcd(\frac ag,k)}=g$

$\quad\quad$ 递归求解 $f(\frac ag,g)$可以解出$k$

$\quad\quad$ 最终$x=d\cdot k$

```
#include<bits/stdc++.h>
using namespace std;
int gcd(int a,int b){
	return b? gcd(b,a%b): a;
}
int f(int a,int d){
	int _g=gcd(a,d);
	if(_g==1)return d;
	else return d*f(a/_g,_g);
}
int main(){
	int T;
	cin>>T;
	while(T--){
		int a,c;
		cin>>a>>c;
		if(c%a) cout<<"NO SOLUTION"<<endl;
		else cout<< f(a,c/a)<<endl;
	}
}
```


---

## 作者：TernaryTree (赞：2)

## 题目大意

给定正整数 $a,c$，求使 $\operatorname{lcm}(a,b)=c$ 成立最小的 $b$，若没有满足条件的 $b$，输出 `NO SOLUTION`。

## 思路分析

我们知道，

$$\operatorname{lcm}(a,b)=\prod p_i^{\max(k_{a_i},k_{b_i})}$$

将 $c$ 分解质因数，也可以得到

$$c=\prod p_i^{k_{c_i}}$$

要使 $\operatorname{lcm}(a,b)=c$，代入一下得到

$$\prod p_i^{k_{c_i}}=\prod p_i^{\max(k_{a_i},k_{b_i})}$$

即对于每一个质数 $p_i$，有 

$$k_{c_i}=\max(k_{a_i},k_{b_i})$$

因为我们已经知道 $k_{c_i}$ 和 $k_{a_i}$，只要求出满足条件的**最小的** $k_{b_i}$ 就可以了。记住“**最小的**”这三个字。

我们分类讨论一下：

- 当 $k_{c_i} < k_{a_i}$ 时：

  显然 $\max(k_{a_i},k_{b_i}) > k_{c_i}$。
  
  输出 `NO SOLUTION`。

- 当 $k_{c_i} > k_{a_i}$ 时：

  要想使其成立，必须使 $k_{b_i}=k_{c_i}$。
  
- 当 $k_{c_i} = k_{a_i}$ 时：

  因为 $k_{b_i}$ 是非负整数，所以我们将 $k_{b_i}$ 取最小值 $0$ 即可。
  
实际上，分解质因数我们可以先把每个数的最小质因数提前筛出来，然后 $O(\log n)$ 求解就可以了。因为最后求 $b$ 的循环里面套了一个快速幂，所以总时间复杂度 $O(t\log^2n)$，足以通过此题。

## 本题坑点

在最后处理 $b$ 的时候一定要记得把没有在 $a$ 的质因数里出现但是在 $c$ 的质因数里出现的数乘上去。

## 完整代码

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

typedef map<int, int>::iterator iter;

const int maxn = 1e5 + 1;
const int maxm = 1e7 + 1;

int prime[maxm], cnt;
bool book[maxm];
int fc[maxm];

void sieve()  {
    for (int i = 2; i < maxm; i++) {
        if (!book[i]) {
            prime[++cnt] = i;
            fc[i] = i;
        }
        for (int j = 1; j <= cnt && i * prime[j] < maxm; j++) {
            book[i * prime[j]] = true;
            fc[i * prime[j]] = prime[j];
            if (i % prime[j] == 0) break;
        }
    }
}

int power(int base, int freq) {
    int ans = 1, tmp = base;
    while (freq > 0) {
        if (freq % 2 == 1) ans = ans * tmp;
        freq /= 2;
        tmp = tmp * tmp;
    }
    return ans;
}

int t, a, c, b = 1;
map<int, int> sa;
map<int, int> sc;

signed main() {
    cin >> t;
    while (t--) {
        sa.clear();
        sc.clear();
        bool fl = true;
        cin >> a >> c;
        b = 1;
        while (a != 1) {
            if (sa.count(fc[a])) sa[fc[a]]++;
            else sa[fc[a]] = 1;
            a /= fc[a];
        }
        while (c != 1) {
            if (sc.count(fc[c])) sc[fc[c]]++;
            else sc[fc[c]] = 1;
            c /= fc[c];
        } 
        for (iter i = sa.begin(); i != sa.end(); i++) {
            if (!sc.count(i->first) || sc[i->first] < i->second) {
                fl = false;
                break;
            } 
            if (sc[i->first] == i->second) {
                sc[i->first] = 0;
                continue;
            }
            b *= power(i->first, sc[i->first]);
            sc[i->first] = 0;
        }
        for (iter i = sc.begin(); i != sc.end(); i++) {
            b *= power(i->first, i->second);
        }
        if (!fl) {
            cout << "NO SOLUTION" << endl;
            continue;
        }
        cout << b << endl;
    }
    return 0;
}
```

---

## 作者：Leasier (赞：2)

显然地，考虑 $\operatorname{lcm}$ 的定义。首先，将 $a, b, c$ 分别分解质因数，得到 $a = \displaystyle\prod_{i = 1}^k p_i^{k_{1, i}}$，$b = \displaystyle\prod_{i = 1}^k p_i^{k_{2, i}}$，$c = \displaystyle\prod_{i = 1}^k p_i^{\max(k_{1, i}, k_{2, i})}$。

于是，如果 $c \bmod a \neq 0$，输出无解；否则，对于每一个质因数 $p_i$，如果 $k_{1, i} \neq \max(k_{1, i}, k_{2, i})$，则其对答案贡献为 $p_i^{k_{1, i}}$。将所有贡献相乘即可。

代码：
```cpp
#include <stdio.h>

typedef long long ll;

int p[17], k[17];

inline ll quick_pow(ll x, ll p){
	ll ans = 1;
	while (p){
		if (p & 1) ans *= x;
		x *= x;
		p >>= 1;
	}
	return ans;
}

int main(){
	int t;
	scanf("%d", &t);
	for (int i = 1; i <= t; i++){
		int a, c, cnt = 0;
		ll ans = 1;
		scanf("%d %d", &a, &c);
		if (c % a != 0){
			printf("NO SOLUTION\n");
			continue;
		}
		for (int j = 2; j * j <= c; j++){
			if (c % j == 0){
				cnt++;
				p[cnt] = j;
				k[cnt] = 0;
				while (c % j == 0){
					c /= j;
					k[cnt]++;
				}
			}
		}
		if (c > 1){
			cnt++;
			p[cnt] = c;
			k[cnt] = 1;
		}
		for (int j = 1; j <= cnt; j++){
			int cur_cnt = 0;
			while (a % p[j] == 0){
				a /= p[j];
				cur_cnt++;
			}
			if (cur_cnt < k[j]) ans *= quick_pow(p[j], k[j]);
		}
		printf("%lld\n", ans);
	}
	return 0;
}
```

---

## 作者：AdzearDisjudge (赞：2)

对于每个a,c,若c%a!=0，则无解；否则有解。

考虑lcm(a,b)=c，即是a*b/gcd(a,b)=c。

故首先算出b=c/a，然后根据gcd的值不断调整b直到gcd(a,b)=1。

具体调整过程就是a/gcd,b/gcd,确保a*b/gcd(a,b)=c仍成立的同时去掉了一个公因子。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,n) for(register int i=a;i<=n;++i)
#define per(i,a,n) for(register int i=a;i>=n;--i)
#define mem(a) memset(a,0,sizeof(a))
#define elif else if
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
inline ll read()
{
    ll f=1,x=0;
    char ch;
    do
    {
        ch=getchar();
        if(ch=='-')
        f=-1;
    }
    while(ch<'0'||ch>'9');
    do
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    while(ch>='0'&&ch<='9');
    return f*x;
}
ll n,aa,cc;
ll gcd(ll a,ll b)
{
	ll c=a,d=b;
	if(c<d)
	swap(c,d);
	if(c%d==0)
	return d;
	return gcd(d,c%d);
}
void solve(ll a,ll c)
{
	ll b,d,e;
	if(c%a)
	{
		cout<<"NO SOLUTION\n";
		return;
	}
	b=c/a;
	d=gcd(a,b);
	while(d!=1)
	{
		a/=d;
		b*=d;
		d=gcd(a,b);
	}
	cout<<b<<endl;
	return;
}
int main()
{
	n=read();
	rep(i,1,n)
	{
		aa=read();
		cc=read();
		solve(aa,cc);
	} 
    return 0;
}
```


---

## 作者：奥斯卡小冰人 (赞：1)

因为 $\operatorname{lcm}(a,b) = c = a \times b \ \div \gcd(a,b) $，
所以 $b = \dfrac{c}{a} \times \gcd(a,b)$。

可以看出 b 一定是 $\dfrac{c}{a}$ 的倍数，又因为 b 和 $\gcd(a,b)$ 肯定都为正整数，所以 c 也肯定是 a 的倍数。那么就可以判断如果 a 无法整除 c 就输出 $\texttt{NO SOLUTION}$。

根据之前 b 为 $\dfrac{c}{a}$ 的倍数就可以循环枚举 b 判断是否满足 $b = \dfrac{c}{a} \times \gcd(a,b)$。


Code：
```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int T;scanf("%d",&T);
    while(T--)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        if(b % a) {printf("NO SOLUTION\n");continue;}
        int x = b / a;
        for(int i = x;i <= b;i += x)
        {
            int gcd = __gcd(a,i);
            if(gcd * x == i) {printf("%d\n",i);break;}
        }
    }   
    return 0;
}
```

---

## 作者：lowAltitudeFlyer (赞：1)

## Description
求最小的整数 $B$ 使得 $\operatorname{lcm}(A,B)=C$。无解输出 `NO SOLUTION`。
## Solution
由最小公倍数的定义得，$C$ 必须是 $A$ 的倍数， 即 $A\nmid C$ 时无解。其他情况必然有解（令 $B=C$ 即可满足最小公倍数的条件）。

考虑分解质因数。对 $C$ 分解质因数后可得 $C=p_1^{α_1}p_2^{α_2}...p_k^{α_k}(p_1<p_2<...<p_k)$。有解的情况下必然满足 $A\mid C$，所以我们把 $A$ 写成 $p_1^{β_1}p_2^{β_2}...p_k^{β_k}(0\le β_i\le α_i)$ 的形式，把 $B$ 写成 $p_1^{γ_1}p_2^{γ_2}...p_k^{γ_k}(0\le γ_i\le α_i)$ 的形式。则 $\operatorname{lcm}(A,B)$可以写成 $p_1^{\max(β_1,γ_1)}p_2^{\max(β_2,γ_2)}...p_k^{\max(β_k,γ_k)}$。所以 $\max(β_i,γ_i)=α_i$。

依次考虑每一个质因数。若 $α_i=β_i$，为了使 $B$ 最小，$γ_i$ 应取 $0$。否则，$γ_i$ 只能取 $α_i$ 来使得 $\max(β_i,γ_i)=α_i$。这样，我们确定了每一个 $γ_i$，答案也就确定了。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int SIZE = 100 + 5;
int t, a, b, c;
int prime1[SIZE], cnt1[SIZE], tot1;
int cnt2[SIZE]; //对a进行质因数分解时使用c的质数表 
inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while(!isdigit(ch)) { if(ch == '-') f = -1; ch = getchar(); }
	while(isdigit(ch)) { x = x * 10 + ch - '0'; ch = getchar(); }
	return x * f;
}
int main() {
	t = read();
	while(t--) {
		memset(cnt2, 0, sizeof(cnt2));
		a = read(); c = read();
		//特判 
		if(c % a != 0) {
			printf("NO SOLUTION\n");
			continue;
		}
		//特判 
		if(a == 1) {
			printf("%d\n", c);
			continue;
		}
		//对c进行质因数分解 
		tot1 = 0;
		for(int i = 2; i * i <= c; i++) {
			if(c % i == 0) {
				tot1++;
				prime1[tot1] = i;
				cnt1[tot1] = 0;
				while(c % i == 0) {
					cnt1[tot1]++;
					c /= i;
				}
			}
		}
		if(c > 1) {
			tot1++;
			prime1[tot1] = c;
			cnt1[tot1] = 1;
		}
		//对a进行质因数分解，使用c的质数表 
		for(int i = 1; i <= tot1; i++) {
			while(a % prime1[i] == 0) {
				a /= prime1[i]; cnt2[i]++;
			}
		}
		//计算答案 
		b = 1;
		for(int i = 1; i <= tot1; i++) {
			if(cnt1[i] - cnt2[i] == 0) continue;
			b *= pow(prime1[i], cnt1[i]);
		}
		printf("%d\n", b);
	}
	return 0;
}
```

---

## 作者：zct_sky (赞：0)

### Solution
-----
若 $c \bmod a \ne 0$，显然输出 $\texttt{NO SOLUTION}$。

否则，考虑对 $c$ 进行分解质因数。

若当前分解的质数为 $p_i$，且 $c$ 中有 $c_i$ 个 $p_i$，$a$ 中有 $a_i$ 个 $p_i$，$b$ 中有 $b_i$ 个 $p_i$。

因为 $c_i=\max(a_i,b_i)$，所以，若 $c_i>a_i$，说明 $b_i=c_i$，即 $b$ 中含有 $c_i$ 个 $p_i$。

否则，因为 $b$ 尽量小，所以 $b_i=0$，即 $b$ 中不含 $p_i$。

最后输出 $b$ 即可。
### Code
-----
```c++
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline ll read(){
	ll x=0,y=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')y=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch&15),ch=getchar();
	return x*y;

}
int t;
ll a,b,c;
int main(){
	t=read();
	while(t--){
		a=read();c=read();
		if(c%a)printf("NO SOLUTION\n");
		else{
			b=1;
			for(int i=2;i*i<=c;i++)
				if(c%i==0){
					ll t=1;
					while(c%i==0)c/=i,t*=i;
					if(a%t)b*=t;
				}
			if(c!=1)
				if(a%c)b*=c;
			printf("%lld\n",b);
		}
	}
	return 0;
}
```

---

## 作者：Elairin176 (赞：0)

[传送门](https://www.luogu.com.cn/problem/UVA11889)       
各位 dalao 怎么都用这么高级的方法，这里介绍一种数学小白也能理解的方法。           
我们都知道，$a\times b=\gcd(a,b)\times\operatorname{lcm}(a,b)$，所以 $\operatorname{lcm}(a,b)=\frac{a\times b}{\gcd(a,b)}=a\times\frac{b}{\gcd(a,b)}$。      
所以不难想出，$\frac{c}{a}$ 就是 $\frac{b}{\gcd(a,b)}$ 的值。    
即在 $c\bmod a≠0$ 的时候无解。       
得出 $\frac{c}{a}$ 之后，我们发现可能不是正确的结果。       
但是结果必然是 $\frac{c}{a}$ 的倍数，所以我们直接枚举即可。         
[CODE](https://www.luogu.com.cn/paste/5d59vgya)

---

