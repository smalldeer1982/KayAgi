# [NERC 2018] Fractions

## 题目背景

翻译自 [NERC 2018](https://neerc.ifmo.ru/archive/2018/neerc-2018-statement.pdf) F 题。

## 题目描述

给你一个整数 $n$，你需要构造出若干个形如 $\dfrac{a_i}{b_i}$ 的真分数，使得 $\sum^k_{i=1} \frac{a_i}{b_i} = 1 - \frac{1}{n}$，且 $b_i$ 可以整除 $n$。

## 说明/提示

对于所有的数据，保证 $1 \leq n \leq 10^9$。

对于第一个样例，不存在一种方案使得答案总和为 $\frac{1}{2}$。

对于第二个样例，$\frac{1}{2} + \frac{1}{3} = \frac{5}{6}$。

## 样例 #1

### 输入

```
2```

### 输出

```
NO```

## 样例 #2

### 输入

```
6```

### 输出

```
YES
2
1 2
1 3```

# 题解

## 作者：_djc_ (赞：4)

## 题目大意

给定一个正整数 $n$，构造出若干个形如 $\frac{a_i} {b_i}$ 的真分数，使得 $\sum_{i=1} ^{k} \frac{a_i} {b_i} =1-\frac {1} {n}$，且 $b_i$ 是 $n$ 的因数。

## 题目分析

由于 $b_i$ 是 $n$ 的因数，所以我们直觉上先把 $n$ 分解一下:

$$
n = p_1^{c_1} p_2^{c_2}\cdots p_m^{c_m}
$$

- $n = p^m$

	在这种情况下，无解。如果 $n = p^m$，那么 $b_i = p^{k_i}(k_i\le m)$，并且每个 $b_i$ 都差了 $p^x$ 倍。设最大的一个 $b_i$ 为 $t$，则通分后的分母为 $t$，而 $t \le n$，所以不可能凑成 $\frac{n-1}{n}$。

- $n$ 的质因数大于等于 $2$ 种
	
    首先，在这种情况下，如果存在答案，那么 $k$ 一定可以等于 $2$。因为 $b_i | n$，且 $lcm(b_1,b_2,\dots,b_k) = n$，任意选取两个，$lcm(b_x, b_y)|n$，如果 $k>2$，我们可以把它们凑成两个。
    
    $$
    \frac{a}{x} + \frac{b}{y} = \frac{n-1}{n}
    
    $$
    
	所以算法的第一步就出来了，$x$ 和 $y$ 任选，只要是 $n$ 的因数且最小公倍数等于 $n$ 就可以了，然后我们再看 $a$ 和 $b$，是否对于任意的 $x$ 和 $y$ 都存在正整数解 $(a,b)$ 且 $a < x,b<y$ 呢？
    
    先做一个转换，同乘 $xy$：
    
    $$
    ay+bx=\gcd(x,y)\cdot(n-1)
    $$
    
    观察这个式子，在学习拓展欧几里得算法时我们学过，$ax+by$ 一定是 $\gcd(a,b)$ 的倍数，否则无解，由于 $\gcd(x,y)\cdot(n-1)$ 一定是 $\gcd(x,y)$ 的倍数，所以一定是有解的。
    
    还有就是要证明存在一个 $a<x,b<y$ 的情况下的解，设 $a$ 已知，$1\le a < x$，则 $b = \frac{\gcd(x,y)\cdot(n-1)-ay}{x}$。设 $x' = \frac{x}{\gcd(x,y)},y' = \frac{y}{\gcd(x,y)}$，则
    
    $$ 
    b = \frac{(n-1)-ay'}{x'}
    $$
    
    若有解，则需要 $b$ 是一个整数，也就是
    
    $$
    (n-1)-ay' \equiv 0 \pmod{x'}
    $$
    
    我们看 $ay'$，由于 $y'$ 与 $x'$ 互质，所以当 $a\in [0,x-1]$，$ay'\pmod{x'}$ 的值都不相同。
    
    证明：如果有两数相同，$a_1 y' = k_1x'+t,a_2y' = k_2x'+t$，则 $(a_1 - a_2)y' = (k_1 - k_2)x'$，$a_1-a_2$ 需要是 $x'$ 的倍数。
    
    又因为当 $a=0$ 时，$(n-1) \pmod{x'}$ 一定不为 $0$，所以在 $1$ 到 $x-1$ 中一定有一个 $a$ 使得 $(n-1)-ay' \equiv 0 \pmod{x'}$。
    
## 代码实现

经过以上分析，代码就可以写出来了。我们先把 $n$ 分解质因数，然后选取 $x$ 和 $y$，使 $\gcd(x,y)=1,x\cdot y = n$。然后从 $1$ 到 $x-1$ 枚举 $a$，每次进行一个判断即可。时间复杂度 $O(\sqrt{n})$。

最后贴上代码，码风很丑轻点喷。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define maxn 100005
inline int read() {
	int x = 0, f = 1; char c = getchar();
	while (c < '0' || c > '9') { if (c == '-') f = -1; c = getchar(); }
	while (c >= '0' && c <= '9') { x = x * 10 + c - '0'; c = getchar(); }
	return x * f;
}

int vis[maxn], prime[maxn], n, m;

void init() {
	for (int i = 2; i <= 100000; i++) {
		if (!vis[i]) prime[++m] = i, vis[i] = 1;
		for (int j = 1; j <= m && prime[j] * i <= 100000; j++) 
			vis[prime[j] * i] = 1;
	}
}

struct node {
	int v, cnt;
};

vector<node> a;

int ksm(int a, int b) {
	int res = 1;
	for (; b; b >>= 1) {
		if (b & 1) res = res * a;
		a = a * a;
	}
	return res;
}

signed main() {
	init();
	n = read();
	for (int i = 1; i <= m; i++) {
		if (n % prime[i] == 0) {
			int tmp = n, cnt = 0;
			while (tmp % prime[i] == 0) {
				cnt++;
				tmp /= prime[i];
			}
			node nw; nw.cnt = cnt, nw.v = prime[i];
			a.push_back(nw);
			break;
		}
	}
	if (a.empty() || ksm(a[0].v, a[0].cnt) == n) {
		puts("NO");
		return 0;
	}
	puts("YES");
	int x = ksm(a[0].v, a[0].cnt);
	int y = n / x, a, b;
	for (a = 1; a < x; a++) {
		if ((n - 1 - a * y) % x == 0) {
			b = (n - 1 - a * y) / x;
			break;
		}
	}
	cout << 2 << endl;
	cout << a << " " << x << endl << b << " " << y;
}
```


---

## 作者：是青白呀 (赞：1)

首先推一波式子：
$$
\begin{aligned}
\frac{n-1}{n}&=\sum_{i=1}^k\frac{\frac{na_i}{b_i}}{n}\\
n-1&=\sum_{i=1}^k \frac{na_i}{b_i}
\end{aligned}
$$

由于 $b_i$ 需要是 $n$ 的因数，不妨设 $c_i=\frac{n}{b_i}$，则有 $a_1c_1+a_2c_2+\dots+a_kc_k=n-1$。

考虑将 $a_i$ 确定为主元，则由裴蜀定理可知该方程有**整数解**的充要条件是 $\gcd(c_1,c_2,\dots,c_k)$ 是 $n-1$ 的因数。又因为所有 $c$ 均为 $n$ 的因数，且 $\gcd(n,n-1)=1$，故当且仅当 $\gcd(c_1,c_2,\dots,c_k)=1$ 时原方程有整数解。也即，当 $n$ 仅有一种质因数时无解。

需要注意的是，我们还需要保证 $a_i<b_i=\frac{n}{c_i}$。因此需要答案进行进一步构造。

不妨考虑 $k=2$ 的情况，此时 $c_1a_1+c_2a_2=n-1$ 有解需要 $\gcd(c_1,c_2)=1$。对 $n$ 作质因数分解 $n=\prod p_i^{k_i}$。考虑任选一个 $x$，令 $c_1$ 等于 $p_x^{k_x}$，$c_2=\frac{n}{c_1}$，此时两者满足互质条件，且有 $c_1=b_2$，$c_2=b_1$。

解方程 $c_1a_1+c_2a_2=1$ 可得一组合法的整数解 $\{a_1,a_2\}$。对照原方程，有 $-c_1a_1+c_2(c_1-a_2)=n-1$，即我们需要调整出一组解，满足 $0<-a_1<c_2$ 且 $0<c_1-a_2<c_1$。不妨首先将 $a_1$ 调整至最大合法负整数。注意到每次调整时，$a_1$ 会变化 $c_2$，$a_2$ 会变化 $c_1$。由于 $a_1$ 不可能是 $c_2$ 的倍数、$a_2$ 不可能是 $c_1$ 的倍数，故此时 $a_1$ 满足条件。此时 $c_1a_1<0,a_1<c_2$，故 $a_2>0$ 且 $a_2<c_1$，第二个条件也被满足。因此通过调整得到了一组合法解。

最终的两个真分数为 $\frac{-a_1}{c_2}$ 和 $\frac{c_1-a_2}{c_1}$。

```cpp
#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=j;i<=k;i++)
#define repp(i,j,k) for(int i=j;i>=k;i--)
#define ls(x) (x<<1)
#define rs(x) ((x<<1)|1)
#define mp make_pair
#define sec second
#define fir first
#define pii pair<int,int>
#define lowbit(i) i&-i
#define int long long
#define qingbai 666
using namespace std;
typedef long long ll;
const int N=22,M=1e6+5,S=(1<<20)+5,inf=2e9+7,mo=998244353;
void read(int &p){
	int x=0,w=1;
	char ch=0;
	while(!isdigit(ch)){
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	p=x*w;
}
int n;
void exgcd(int a,int b,int &x,int &y){
    if(!b){
        x=1,y=0;
        return;
    }
    int x1=0,y1=0;
    exgcd(b,a%b,x1,y1);
    x=y1,y=x1-(a/b)*y1;
}
signed main(){
    read(n);
    int x=n;
    int a1=1,a2=0,x1=0,x2=0;
    rep(i,2,sqrt(n)){
        int cnt=1;
        while(x%i==0)
            x/=i,cnt*=i;
        if(cnt!=1){
            a1=cnt,a2=n/cnt;
            break;
        }
    }
    if(a1==1||a2==1){
        puts("NO");
        return 0;
    }
    exgcd(a1,a2,x1,x2);
    if(x1<0){
        int num=(-x1-1)/a2;
        x1+=num*a2,x2-=num*a1;
    }
    if(x1>=0){
        int num=x1/a2+1;
        x1-=num*a2,x2+=num*a1;
    }
    puts("YES");
    puts("2");
    printf("%lld %lld\n%lld %lld\n",-x1,n/a1,a1-x2,n/a2);
    return 0;
}
```

---

## 作者：zzx0102 (赞：1)

考虑先将原式通分，化为

$$
\sum\limits_{i=1}^k \dfrac{a_i\times \frac{n}{b_i}}{n}=\dfrac{n-1}{n}
$$

令 $c_i=\dfrac{n}{b_i}$，可得

$$
\sum\limits_{i=1}^k a_i\times c_i=n-1
$$

接下来考虑构造。

若我们能够找到两个互质的 $c_i$，令 $c_1=x,c_2=y$，然后令 $a_1=p,a_2=q$，则可以解 $px+qy=n-1$ 的方程组。

显然 $n-1\not \equiv 0\pmod x$，所以根据裴蜀定理即得有解，然后上个 exgcd 给这个方程解掉即可。

然后想如果找不出两个互质的 $c_i$，令 $n=p^a$，则 $p\mid c_i$，$p\mid \sum\limits_{i=1}^ka_i\times c_i$，又 $n-1\not \equiv 0\pmod p$，所以显然无解。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int x, y;
void exgcd(int a, int b) {
	if(!b) {x = 1; y = 0; return ;}
	exgcd(b, a % b); int tx = x; x = y; y = tx - a / b * y; 
}
signed main() {
	int n; cin >> n;
	int a = -1, b, m = n;
	for(int i = 2; i * i < n; i++) {
		if(n % i == 0) {
			int c = 1;
			while(m % i == 0) m /= i, c *= i;
			if(m == 1) {
				cout << "NO";
				return 0;
			}
			a = c;
			b = n / c;
			break;
		}
	}
	if(a == -1) {
		cout << "NO";
		return 0;
	}
	exgcd(a, b);
	cout << "YES\n2\n";
	if(x < 0) cout << -x << ' ' << b << '\n' << a - y << ' ' << a << '\n';
	else cout << b - x << ' ' << b << '\n' << -y << ' ' << a << '\n';
	return 0;
}
```

---

## 作者：Unordered_OIer (赞：0)

# Description

将 $1-\dfrac{1}{n}$ 分解为若干个正真分数之和，且要求这些正真分数的分母是不等于 $n$ 的正因数。

# Solution

~~为什么这么简单的题调了 40 分钟啊~~

首先 $1-\dfrac{1}{n}=\dfrac{n-1}{n}$，而且我们分拆出来的 $\dfrac{a_i}{b_i}$ 一定可以写成非既约形式 $\dfrac{a_i \times \dfrac{n}{b_i}}{n}$，观察到上面一定要是 $n$ 的正因数，否则分母就是 $n$ 了。然后我们也就是要用 $n$ 的所有正因数 $d$ 凑和为 $n-1$。

可能因为我比较菜，一开始想到因为正因数不是特别多想完全背包，但是 $10^9$ 不是很好处理。我们先尝试考虑无解情况：

1. 当 $n$ 是素数时必然无解，因为它没有介于 $[2,n-1]$ 的正因数
2. 当 $n=p^k$，其中 $p$ 为素数，$k$ 为正整数时也无解。

这是因为 $n-1$ 与 $n$ 互素，而 $n$ 只有一个素因子 $p$，所以 $n-1$ 没有素因子 $p$，也就是用再多的 $p$ 也凑不出和为 $n-1$。

我们可以联想到，是否当 $n$ 有 $\geq 2$ 个素因子的时候必然有解。下面证明这件事：

假设 $n$ 有两个素因子为 $p,q$，且 $\forall\ p,q \in \mathbb Z^+,n-1 \neq px+qy$，则由贝祖定理可得 $\gcd(p,q) \nmid n-1$，而 $\gcd(p,q)=1$，矛盾。

所以我们仅需这两个 $p,q$ 即可，现在的任务就变成求 $px+qy=n-1$ 的一组正整数特解，这一部分使用扩展欧几里得算法即可完成。

可能分解需要 $O(\sqrt n)$ 吧，扩欧 $O(\log n)$，T 不了一点。

实现比较繁琐 qwq，因为我太菜了。

```cpp

int main(){
  n=read();
  if(isp(n))return !puts("NO");
  for(ll i=2;i*i<=n;i++){
    if(n%i==0){
      yin[++cnt]=i;
      if(i*i!=n)yin[++cnt]=n/i;
    }
  }
  sort(yin+1,yin+cnt+1);
//  for(ll i=1;i<=cnt;i++)cout<<yin[i]<<' ';
  ll nn=n,a=0,b=0;
  for(ll i=1;i<=cnt;i++){
    if(isp(yin[i])){
      if(!a)a=yin[i];
      else{
        b=yin[i];
        break;
      }
    }
  }
  if(!b)return !puts("NO");
  ll c=n-1;
  ll d=gcd(a,b);
  exgcd(a,b,x,y);
  x*=c/d,y*=c/d;
  if(x<0)x=x%b+b,y=(c-x*a)/b;
  else if(y<0)y=y%a+a,x=(c-y*b)/a;//调成正的
  ll fz1=x*a,fm1=n,fz2=y*b,fm2=n;
  ll g1=gcd(fz1,fm1),g2=gcd(fz2,fm2);
  fz1/=g1,fm1/=g1;fz2/=g2,fm2/=g2;
  printf("YES\n2\n%lld %lld\n%lld %lld\n",fz1,fm1,fz2,fm2);
  return 0;
}
```

---

## 作者：McIron233 (赞：0)

数学构造题。

我们知道，分数相加有通分这一步。所以当 $n=p^k$ 且 $k$ 为正整数，$p$ 为质数时无解，我们构造不出来这样的分数，使得通分完后分母不小于 $n$。

证明：根据唯一分解定理以及求解多个数的最小公倍数的过程，可以得到 $b_i = x \times p^m(m \geq 0)$，其中 $x$ 为正整数，$p$ 为质数，$m$ 为自然数。因此想要使得 $ x \times n = x \times p^k = \operatorname{lcm}(b_1,b_2, \cdots, b_n)$，就必须有其中的 $b_i$ 在分解成 $b_i = x \times p^m$ 之后满足 $m \geq k$，此时 $b_i$ 不满足 $1 \lt b_i \lt n = p^k$，故在这种情况下无解。

当 $n$ 有解的时候，我们可以只构造出 $2$ 个符合条件的分数。设 $\frac{n-1}{n}=\frac{x}{a}+\frac{y}{b}$，那么一定可以找到一组 $a,b$ 满足 $n=ab, \gcd(a,b)=1$。这只需要使得 $a=p^k, b= n \div p^k$ 即可，其中 $p$ 是质数，$k$ 是正整数，且 $b$ 不含质因子 $p$。对 $n$ 分解质因数并找到 $a,b$ 的时间复杂度是 $O(\sqrt{n})$。

那么有：

$$
\frac{x}{a}+\frac{y}{b}=\frac{ay+bx}{ab}=\frac{ay+bx}{n}=\frac{n-1}{n}=\frac{ab-1}{n}
$$

因此，我们只需要求解 $x,y$ 的一组可行解。有两种方法得到 $x,y$。

## 法一

根据以上公式，显然我们只需要使用 exgcd 求解不定方程 $ay+bx=n-1$ 的一组正整数解即可，注意 $1 \leq x \lt a, 1 \leq y \lt b$。枚举 $x,y$ 时间复杂度 $O(\log \max(a,b))$，总时间复杂度 $O(\sqrt{n})$。

## 法二

直接从 $1$ 到 $a-1$ 暴力枚举 $x$，然后判断 $y$ 是否为正整数且 $1 \leq y \lt b$ 即可。总时间复杂度 $O(\sqrt{n})$。

---

