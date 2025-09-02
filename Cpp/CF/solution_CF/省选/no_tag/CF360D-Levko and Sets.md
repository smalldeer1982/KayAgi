# Levko and Sets

## 题目描述

Levko loves all sorts of sets very much.

Levko has two arrays of integers $ a_{1},a_{2},...\ ,a_{n} $ and $ b_{1},b_{2},...\ ,b_{m} $ and a prime number $ p $ . Today he generates $ n $ sets. Let's describe the generation process for the $ i $ -th set:

1. First it has a single number $ 1 $ .
2. Let's take any element $ c $ from this set. For all $ j $ ( $ 1<=j<=m $ ) if number $ (c·a_{i}^{b_{j}}) mod p $ doesn't occur in the set, then add it to the set.
3. Repeat step $ 2 $ as long as we can add at least one element to our set.

Levko wonders, how many numbers belong to at least one set. That is, he wants to know what size is the union of $ n $ generated sets.

## 样例 #1

### 输入

```
1 1 7
2
5
```

### 输出

```
3
```

## 样例 #2

### 输入

```
1 2 7
2
2 4
```

### 输出

```
3
```

## 样例 #3

### 输入

```
2 1 7
1 6
2
```

### 输出

```
1
```

## 样例 #4

### 输入

```
2 1 7
1 6
5
```

### 输出

```
2
```

# 题解

## 作者：George1123 (赞：4)

打退役狗 $\to$ [`George1123`](https://www.cnblogs.com/George1123/p/14202324.html)。

---

## 题面

> [CF360D Levko and Sets](https://www.luogu.com.cn/problem/CF360D)

> 给定 $a\{n\}$ 和 $b\{m\}$ 和质数 $p$。对于每个 $a_i$，生成一个集合，刚开始只有 $1$，每次从集合中选一个元素 $c$，对于所有的 $j$，如果满足 $c\times a_i^{b_j}\bmod p$ 不在当前集合，就把它加入集合。求 $n$ 个集合并的大小。

> 数据范围：$1\le n\le 10^4$，$1\le m\le 10^5$，$2\le p\le 10^9$。

---

## 题解

之前 `VP` 场上没做出来后来学了 `zhouyuyang` 的做法，然后发现学了个假做法。

**Hack**：`2 1 13 3 5 1`；答案：`6`；错误输出：`7`。

设 $\varphi=p-1$，$g=\gcd(\varphi,\gcd_{i=1}^m b_i)$，$G$ 是 $p$ 任意一个原根。

很明显每个集合元素就是 $\{a_i^{gk}\bmod p|k\in N\}$。

$u^{x}\equiv u^{x\bmod \varphi}\pmod p$。$x\in[0,\varphi)$ 与 $f(x)=G^{x}\in [1,p)$ 一一对应。

所以搞出所有 $\varphi$ 的因数，可以得到对于所有的 $i$，最小的 $c_i$ 满足 ${a_i}^{gc_i}\equiv 1\pmod p$。那么这个集合有 $c_i$ 个元素。

考虑是哪 $c_i$ 个元素：$\{a^{g},a^{2g},...,a^{(c_i-1)g}\}$（$\bmod p$，下同）。

或者说：$\{G^{0},G^{\varphi/c_i},G^{2\varphi/c_i},...,G^{(c_i-1)\varphi/c_i}\}$。这两个集合是等价的。

设 $s_i=\frac{\varphi}{c_i}$，求 $n$ 个集合的并集，问题转化为：有多少个 $1\le x\le \varphi$ 满足 $\exists s_i|x$。

很多人这里写错了，可是 `Codeforces` 的数据不强，误导了好多人。

设 $d|\varphi:f(d)$ 表示 $d$ 的倍数中只被 $d$ 标记不被 $d$ 的其他是 $\varphi$ 的因数的倍数标记的数的个数。

如果 $\exists s_i|d$，$f(d)=\frac{\varphi}{d}-\sum_{dk|\varphi}f(dk)$；否则 $f(d)=0$。

然后答案是 $\sum_{d|\varphi} f(d)$，时间复杂度 $\Theta((n+m)\log p+d(\varphi)(n+d(\varphi)))$。

---

## 代码


```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
#define x first
#define y second
#define bg begin()
#define ed end()
#define pb push_back
#define mp make_pair
#define sz(a) int((a).size())
#define R(i,n) for(int i(0);i<(n);++i)
#define L(i,n) for(int i((n)-1);i>=0;--i)
const int iinf=0x3f3f3f3f;
const ll linf=0x3f3f3f3f3f3f3f3f;

//Data
const int N=1e4,M=1e5,d_N=4e4;
int n,m,p,a[N],b[M],c[N];
int d_n,pd[d_N],f[d_N];

//Math
int gcd(int a,int b){return a?gcd(b%a,a):b;}
int mypow(int a,int x=p-2,int res=1){
    for(;x;x>>=1,a=1ll*a*a%p)
        (x&1)&&(res=1ll*res*a%p);
    return res;
}

//Main
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>n>>m>>p;
    int phi=p-1,g=phi;
    R(i,n) cin>>a[i];
    R(i,m) cin>>b[i],g=gcd(g,b[i]);
    for(int d=1;d*d<=phi;++d)if(phi%d==0)
        pd[d_n++]=d,d*d<phi?pd[d_n++]=phi/d:0;
    sort(pd,pd+d_n);
    R(i,n){
        int t=mypow(a[i],g);
        R(j,d_n)if(mypow(t,pd[j])==1)
            {c[i]=phi/pd[j]; break;}
    }
    int ns=0;
    L(i,d_n){
        bool mark=false;
        R(j,n)if(pd[i]%c[j]==0){mark=true; break;}
        if(mark){
            f[i]=phi/pd[i];
            for(int j=i+1;j<d_n;++j)
                if(pd[j]%pd[i]==0) f[i]-=f[j];
            ns+=f[i];
        }
    }
    cout<<ns<<'\n';
    return 0;
}
```

---

**祝大家学习愉快！**

---

## 作者：EuphoricStar (赞：2)

求出 $p$ 的原根 $g$，对每个 $a_i$ 求出一个 $x_i$ 表示 $g^{x_i} \equiv a_i \pmod {p}$（这部分可以 BSGS）。之后的表述中 $a_i$ 指 $x_i$。那么集合生成方式相当于初始 $c = 0$，每次让 $c \gets (c + a_i b_j) \bmod (p - 1)$。

根据裴蜀定理，若求出 $x$ 为所有 $b_j$ 的 $\gcd$，每次操作相当于让 $c \gets (c + x a_i) \bmod (p - 1)$。

设 $y_i = \gcd(x a_i, p - 1)$，那么第 $i$ 个集合就是 $\le p - 1$ 且为 $y_i$ 倍数的所有数（包括 $0$）。

现在要求集合并集大小。注意到 $y_i$ 为 $p - 1$ 的因数，于是对于 $p - 1$ 的第 $i$ 个因数 $d_i$，设 $f_i$ 为集合并集中与 $p - 1$ 的 $\gcd = i$ 的数的个数，再求出是否存在一个 $y_i$ 使得 $d_i \mid y_i$。若不存在则 $f_i = 0$；若存在则 $f_i = \frac{p - 1}{d_i} - \sum\limits_{d_i \mid d_j} f_j$。

那么答案就是 $\sum f_i$。

时间复杂度 $O(\sqrt{np} + d(p - 1)^2)$（前者是求 $x_i$ 的复杂度；实际上后者的 $O(d(p - 1)^2)$ 应该能做到 $O(d(p - 1) \omega(p - 1))$）。

[code](https://codeforces.com/problemset/submission/360/277315042)

---

## 作者：wind_whisper (赞：2)

## $\text{Description}$
有两个整数数组 $a_1,a_2......a_n$ 和 $b_1,b_2......b_m$，与一个质数 $p$ ，现在要生成 $n$ 个集合，第 $i$ 个集合生成方式如下：  
1. 开始，集合只有元素 $1$.  
2. 从集合中选一个元素 $c$ ，对于所有的 $j$ ，如果满足 $(c\times a_i^{b_j})\bmod p$ 不在当前集合，就把它加入集合.  
3. 重复以上步骤.  

求 $n$ 个集合的并的大小.  
$n\le 10^4,m\le 10^5,p\le 10^9$  
$a_i\le p,b_i\le10^9$
## $\text{Solution}$
题意简化一下就是集合里的元素是 $a_i$ 的（$b_i$组合相加）次幂模 $p$ 的结果.  
设 $\phi=p-1,g=\gcd(\phi,\gcd_{i=1}^m b_i)$，那么第 $i$ 个集合可以等价为：
$$\{a_i^{kg}(\bmod\space p)|k\in N\}$$
设 $c_i$ 为最小的 $k$，满足 $a_i^{gc_i}=1(mod\space p)$，$c_i$ 必然是 $\phi$ 的因子，可以预处理出 $\phi$ 的因子后暴力求出.  
那么这个集合可以等价为：
$$\{1,a_i^{g},a_i^{2g},...,a_i^{(c_i-1)g}\}$$
设 $R$ 为 $p$ 的原根，那么上面的集合等价于：
$$
\large
\{R^0,R^{\frac{\phi}{c_i}},R^{2\times \frac{\phi}{c_i}},...,R^{(c_i-1)\times \frac{\phi}{c_i}}\}$$
那么问题就转化为了给出一个数列 $c_{1...n}$ ，求 $[1,\phi]$ 之间由 $c$ 数列筛出的数的个数，其中 $c_i$  均是 $\phi$ 的因子.  
设 $f_x$ 为**只**被 $x$ 筛掉的数的个数.  
就有 
$$f_x=\frac{\phi}{x}-\sum f_{kx}$$  
由于所有的 $c_i$ 都是 $\phi$ 的因数，所以也只枚举 $\phi$ 的因数即可.  
最后的答案就是把所有是 $c_i$ 倍数的 $x$ 的 $f_x$ 加起来. 
## $\text{Code}$
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define debug(...) fprintf(stderr,__VA_ARGS__)
const int N=2e5+100;
inline ll read(){
  ll x(0),f(1);char c=getchar();
  while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
  while(isdigit(c)){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
  return x*f;
}
int n,m;
int mod;
inline ll ksm(ll x,ll k){
  ll res(1);
  while(k){
    if(k&1) res=res*x%mod;
    x=x*x%mod;k>>=1;
  }
  return res;
}
ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
int a[N],b[N],c[N],g;
int pd[N],tot;
int f[N];
int main(){
  #ifndef ONLINE_JUDGE
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
#endif
  n=read();m=read();mod=read();
  int phi=mod-1;g=phi;
  for(int i=1;i<=n;i++) a[i]=read();
  for(int i=1;i<=m;i++) b[i]=read(),g=gcd(g,b[i]);  
  for(int i=1;i*i<=phi;i++){
    if(phi%i) continue;
    pd[++tot]=i;if(i*i<phi) pd[++tot]=phi/i;
  }
  sort(pd+1,pd+1+tot);
  for(int i=1;i<=n;i++){
    int d=ksm(a[i],g);
    for(int j=1;j<=tot;j++){
      if(ksm(d,pd[j])==1){
	c[i]=phi/pd[j];break;
      }
    }
    //printf("i=%d c=%d\n",i,c[i]);
  }
  int res(0);
  for(int i=tot;i>=1;i--){
    bool flag=0;
    for(int j=1;j<=n;j++){
      if(pd[i]%c[j]==0){flag=1;break;}
    }
    if(!flag) continue;
    f[i]=phi/pd[i];
    for(int j=i+1;j<=tot;j++){
      if(pd[j]%pd[i]==0) f[i]-=f[j];
    }
    res+=f[i];
  }
  printf("%d\n",res);
  return 0;
}
/*
3 3
tsy
*/

```


---

## 作者：Linge_Zzzz (赞：1)

# Sol

根据裴蜀定理，设 $b=\gcd\{b_i\}$，则第 $i$ 个集合 $S_i$ 为 $\{x|x=a^{kb}\bmod p,k\in\mathbb{Z}\}$。

因为对 $p$ 取模了，所以指数相当于对 $p-1$ 取模，再用裴蜀定理，记 $b'=\gcd(b,p-1)$，得到 $S_i=\{x|x=a_i^{kb'}\bmod p,k\in\mathbb{Z}\}$。

但是现在还是很难计算，考虑把不同的底数换成相同的底数。我们求出 $p$ 的一个原根，记为 $g$，再对每个 $a_i$ 求出它的阶，记为 $x_i$。

设 $y_i=\gcd(bx_i,p-1)$，现在就有了 $S_i=\{x|x=g^{ky_i}\bmod p,k\in\mathbb{Z}\}$。

因为 $1$ 到 $p-1$ 中，阶与每个数一一对应，所以我们可以光看指数。设 $T_i=\{x|x=ky_i\bmod(p-1),k\in\mathbb{Z}\}$。

现在我们要做的就是，对 $T_i$ 的并集计数。

首先注意到 $y_i|(p-1)$（因为 $y_i=\gcd(bx_i,p-1)$），那么我们可以只考虑 $p-1$ 的因数，设为 $d_i$。

考虑并集中一个数 $x$ 能被哪些 $d_i$ 筛掉，显然是要满足 $d_i|x$。我们钦定这个数属于满足 $d_i|x$ 的最大的 $d_i$。记 $f_i$ 为 $d_i$ 拥有几个数，可以从大往小倒序处理得到每个 $f_i$。

具体地，若存在 $y_i|d_j$，那么 $f_j$ 有转移：$f_j=\frac{p-1}{d_j}-\sum_{d_j|d_k}f_k$，否则 $f_j=0$。这部分时间复杂度 $O(d(p-1)^2)$。

$f_j$ 的和即为答案。

对所有数使用 BSGS 求阶的复杂度为 $O(n\sqrt{p})$，过不去。但是每次 BSGS 的底数一样，所以我们可以提前预处理次幂放到哈希表里，另外可以平衡块长。平衡之后复杂度是 $\sqrt{np}$。

时间复杂度 $O(\sqrt{np}+d(p-1)^2)$。

# Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef pair<int,int> pii;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
const int N=1e5+10,INF=0x3f3f3f3f3f3f3f3f,mod=1e9+7;
int n,m,p,a[N],b,g=2;
vector<int> vd;
void getd(int n){
	for(int i=1;i*i<=n;i++){
		if(n%i==0){
			vd.pb(i);
			if(n/i!=i)vd.pb(n/i);
		}
	}
}
int qpow(int a,int p,int mod){
	int res=1;
	while(p){
		if(p&1)res=1ll*res*a%mod;
		a=1ll*a*a%mod;
		p>>=1;
	}
	return res;
}
bool checkg(int x){
	vector<int> w;
	int n=p-1;
	for(int i=2;i*i<=n;i++){
		if(n%i==0){
			w.pb(i);
			while(n%i==0)n/=i;
		}
	}
	if(n>1)w.pb(n);
	for(int d:w){
		if(qpow(x,(p-1)/d,p)==1)return 0;
	}
	return 1;
} 
unordered_map<int,int> s;
void init(int a,int p){
	int t=3170000,k=qpow(a,316,p);
	for(int i=0,x=1;i<=t;i++,x=1ll*x*k%p)s[x]=i;
}
int BSGS(int a,int n,int p){
	int ans=INF;
	int t=317;
	for(int i=0,x=n;i<=t;i++,x=1ll*x*g%p)
		if(s.count(x)){
			ans=min(ans,s[x]*316-i);
			break;
		}
	return (ans%(p-1)+(p-1))%(p-1);
}
int x[N],f[N],ans;
bool vis[N];
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>m>>p;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=m;i++){
		int x;cin>>x;
		b=__gcd(b,x);
	}
	b=__gcd(b,p-1);
	getd(p-1);
	sort(vd.begin(),vd.end());
	while(!checkg(g))g++;
	init(g,p);
	for(int i=1;i<=n;i++){
		x[i]=BSGS(g,a[i],p);
		if(x[i]==0)x[i]=p-1;
		x[i]=__gcd(x[i]*b,p-1);
		vis[lower_bound(vd.begin(),vd.end(),x[i])-vd.begin()]=1;
	}
	for(int i=0;i<vd.size();i++)
		for(int j=i+1;j<vd.size();j++)
			if(vd[j]%vd[i]==0)vis[j]|=vis[i];
	for(int i=vd.size()-1;i>=0;i--){
		if(!vis[i])continue;
		f[i]=(p-1)/vd[i];
		for(int j=i+1;j<vd.size();j++)
			if(vd[j]%vd[i]==0)f[i]-=f[j];
		ans+=f[i];
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Cry_For_theMoon (赞：1)

2600* 的数论题，害怕。

首先研究单个集合，发现指数是 $b$ 数组的线性组合。

又因为是在模 $p$ 意义下，实质上是 $b$ 数组的线性组合模 $(p-1)$。

看上去多了个模难受了，实际上简单了，可以直接套用裴蜀定理，令 $g$ 为 $b$ 数组和 $(p-1)$ 的 $\gcd$，那么指数是任意 $\gcd$ 的倍数（模 $(p-1$ 意义下）。

之所以说简单了，是因为如果没有这个模数，我 $b$ 数组的线性组合的系数只能是正的，裴蜀定理不管用。而多了个取模，也就是你的线性组合多了个 $a(p-1)$，而这个 $a$ 是可以为负的，只要线性组合里一个系数为负就够用了。

但是这样，$n$ 个集合的底数还是不统一，很难取并。

我们要统一底数，容易想到随便求一个原根 $g$。然后我们观察原来的集合，应该是求出 $a^g$ 的阶 $c$ 以后，是这样的：

$$\{a^{0g},a^{1g},a^{2g},....,a^{(c-1)g}\}$$

我们知道，这 $c$ 个数模 $p$ 两两不同，这是阶的定义告诉我们的。还有一个很重要的事情，就是这 $c$ 个数，是 $x^{c}\equiv 1(\bmod \,p)$ 的所有解。这是拉格朗日定理告诉我们的。

我们想搞一个 $g$ 为底的集合，大小也是 $c$，所以我们也要搞出一个 $c$ 次方为 $1$ 的所有数的集合，那么就可以容易构造出：

$$\{g^{0\frac{p-1}{c}},g^{1\frac{p-1}{c}},...,g^{(c-1)\frac{p-1}{c}} \}$$

这 $c$ 个数也是模 $p$ 互不相同的，这里可以反证。同时也构成 $c$ 次方为 $1$ 的数的所有解，所以上下两个集合等价。

令 $s=\frac{p-1}{c}$，$n$ 个 $s$ 构成一个集合 $S$。现在要找到 $[1,p)$ 中有多少个数，是 $S$ 中某个数的倍数。

首先注意到 $s\mid (p-1)$，而 $10^9$ 范围内因数最多的数的因数个数，即 $\max\{d(n)\}=1344$，记这个常数为 $\omega$，那么 $|S|\le \omega$。

我们可以设计一个 $O(\omega^2)$ 的算法，它是满足要求的。就是说，我们把 $(p-1)$ 的所有因数拉出来，忽略掉不能被 $S$ 中任何一个数整除的数，然后降序地容斥。

设 $f(d)$ 是 $[1,p)$ 中 $d$ 的倍数个数，一个经典的套路是 $f(d)=\frac{p-1}{d}-\sum{f(dk)}$

注意当 $d\nmid (p-1)$ 时 $f(d)=0$，所以我们只要每次暴力枚举比当前 $d$ 大的 $(p-1)$ 的约数，看是不是构成倍数关系即可。

时间复杂度 $O(\omega n\log n+\omega^2)$，其中 $\omega=1344$。

第一部分是对 $n$ 个数求阶的复杂度，第二部分就是容斥的复杂度。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
#define op(x) ((x&1)?x+1:x-1)
#define odd(x) (x&1)
#define even(x) (!odd(x))
#define lc(x) (x<<1)
#define rc(x) (lc(x)|1)
#define lowbit(x) (x&-x)
#define Max(a,b) (a>b?a:b)
#define Min(a,b) (a<b?a:b)
#define next Cry_For_theMoon
#define il inline
#define pb(x) push_back(x)
#define is(x) insert(x)
#define sit set<int>::iterator
#define mapit map<int,int>::iterator
#define pi pair<int,int>
#define ppi pair<int,pi>
#define pp pair<pi,pi>
#define fr first
#define se second
#define vit vector<int>::iterator
#define mp(x,y) make_pair(x,y)
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef double db;
using namespace std;
const int MAXN=1e4+10,MAXM=1e5+10;
int mypow(int a,int n,int mod=998244353){
    if(!n)return 1;
    int tmp=mypow(a,n/2,mod);tmp=1ll*tmp*tmp%mod;
    if(n&1)tmp=1ll*tmp*a%mod;return tmp;
}
int gcd(int a,int b){
    if(!b)return a;
    return gcd(b,a%b);
}
int n,m,p,g;
int a[MAXN],b[MAXM];
int s[MAXN],tot,tag[MAXN],f[MAXN],ans;
vector<int>d;
int main(){
    scanf("%d%d%d",&n,&m,&p);g=(p-1);
    rep(i,1,n)scanf("%d",&a[i]);
    rep(i,1,m)scanf("%d",&b[i]),g=gcd(g,b[i]);
    rep(i,1,(p-1)){
        if(i*i>(p-1))break;
        if(i*i==(p-1)){
            if((p-1)%i==0)d.pb(i);
        }else{
            if((p-1)%i==0)d.pb(i),d.pb((p-1)/i);
        }
    }
    sort(d.begin(),d.end());
    rep(i,1,n){
        a[i]=mypow(a[i],g,p);
        //求a[i]的阶
        int c=0;
        for(auto u:d){
            if(mypow(a[i],u,p)==1){
                c=u;break;
            }
        }
        if(a[i]==1)c=1;
        s[i]=(p-1)/c;
    }
    sort(s+1,s+1+n);
    tot=unique(s+1,s+1+n)-s-1;
    int sz=d.size();
    rep(i,0,sz-1){
        rep(j,1,tot){
            if(d[i]%s[j]==0){
                tag[i]=1;break;
            }
        }
    }
    per(i,sz-1,0){
        if(!tag[i])continue;
        f[i]=(p-1)/d[i];
        rep(j,i+1,sz-1){
            if(d[j]%d[i]==0){
                f[i]-=f[j];
            }
        }
        ans+=f[i];
    }
    printf("%d",ans);
    return 0;
}
```

---

