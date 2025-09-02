# Discrete Logging

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=14&page=show_problem&problem=1166

[PDF](https://uva.onlinejudge.org/external/102/p10225.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10225/8f3c646876319e7077dcca889242cfa7bc79674d.png)

## 样例 #1

### 输入

```
5 2 1
5 2 2
5 2 3
5 2 4
5 3 1
5 3 2
5 3 3
5 3 4
5 4 1
5 4 2
5 4 3
5 4 4
12345701 2 1111111
1111111121 65537 1111111111```

### 输出

```
0
1
3
2
0
3
1
2
0
no solution
no solution
1
9584351
462803587```

# 题解

## 作者：niiick (赞：6)

BSGS (Baby Step-Giant Step 大步小步算法)，
~~拔山盖世算法~~，
用于求解**高次同余方程**$a^x\equiv b(\mod p)$，其中$a,p$**互质**

我们令$t=\lfloor{\sqrt{p}}\rfloor$

并将$x$表示为$x=i*t-j$，其中$0<=j<=t$

则方程变为$a^{i*t-j}\equiv b(\mod p)\Rightarrow (a^t)^i\equiv b*a^j(\mod p)$

对于所有$j\in[0,t],j\in K$，
把$b*a^j\mod p$插入hash表

枚举所有$i\in [0,t],i \in K$，
查询$(a^t)^i\mod p$的值是否存在于hash表中

若存在即代表找到一个解$x=i*t-j$，
若枚举完所有可能的$i$在hash表中都不存在对应的$j$
则可判定原方程无解

特别的，若有$a\mod p==0$**且**$b \mod p\ !=0$，
则代表**原方程无解**

####hash在洛谷是关键字！关键字！！关键字！！！不要用！！！！
####蒟蒻因为这个CE了两发QAQ

```cpp
//niiick
#include<iostream>
#include<cmath>
#include<algorithm>
#include<queue>
#include<cstring>
#include<cstdio>
#include<map>
using namespace std;
typedef long long lt;

int read()
{
    int f=1,x=0;
    char ss=getchar();
    while(ss<'0'||ss>'9'){if(ss=='-')f=-1;ss=getchar();}
    while(ss>='0'&&ss<='9'){x=x*10+ss-'0';ss=getchar();}
    return f*x;
}

lt p;
map<int,int> hh;
map<int,bool> vis;

lt qpow(lt t,lt k)
{
    lt res=1;
    while(k>0)
    {
        if(k&1)res=(res*t)%p;
        t=(t*t)%p;
        k>>=1;
    }
    return res;
}

lt BSGS(lt a,lt b)
{
    hh.clear(); vis.clear();
    lt t=sqrt(p); b%=p;
    
    for(int j=0;j<=t;++j)
    {
        lt tt=b*qpow(a,j)%p;
        hh[tt]=j; vis[tt]=true;
    }
    
    a=qpow(a,t);
    if(a==0)return b==0?1:-1;
    
    for(int i=0;i<=t;++i)
    {
        lt tt=qpow(a,i);
        if(vis[tt])
        {
            int j=hh[tt];
            if(j>=0&&i*t-j>=0)
            return i*t-j;
        }
    }
    return -1;
}

int main()
{
    lt a,b;
    while(scanf("%lld%lld%lld",&p,&a,&b)!=EOF)
    {
        lt ans=BSGS(a,b);
        if(ans==-1)printf("no solution\n");
        else printf("%lld\n",ans);
    }
    return 0;
}
```

---

## 作者：K8He (赞：4)

# 「题解报告」 [Discrete Logging](https://www.luogu.com.cn/problem/UVA10225)

[引流：「学习笔记」BSGS](https://www.cnblogs.com/Keven-He/p/BabyStepGiantStep.html)

## 问题

求解

$$
a^x \equiv b \pmod p
$$

其中 $a\perp p$，方程的解 $x$ 满足 $0 \le x < p$。

## 算法

首先根据费马小定理 $a^{p-1}\equiv1\pmod{p}$，不难发现 $1\sim p-1$ 是一个循环节，也就是说只用判断 $1\sim p-1$ 这些数里是否存在一个方程的解 $x$ 即可。

但是这个范围仍然很大，直接 $O(p)$ 跑肯定不行。

令 $x=A\left\lceil\sqrt{p}\right\rceil-B (0\le A, B\le\left\lceil\sqrt{p}\right\rceil)$，则 $a^{A\left\lceil\sqrt{p}\right\rceil-B} \equiv b \pmod p$。

则 $a^{A\left\lceil\sqrt{p}\right\rceil} \equiv a^{B} b \pmod p$。

由于 $A,B$  不大，我们可以枚举出所有 $a^{B} b$ 和 $a^{A\left\lceil\sqrt{p}\right\rceil}$ 的取值。用 `map` 存下所有 $a^{B} b$ 的取值，再查找 $a^{A\left\lceil\sqrt{p}\right\rceil}$ 的取值是否出现过即可。

注意在求出满足 $a^{A\left\lceil\sqrt{p}\right\rceil} \equiv a^{B} b \pmod p$ 的合法 $A,B$ 后还要推回到 $a^{A\left\lceil\sqrt{p}\right\rceil-B} \equiv b \pmod p$ 才能得到解 $x=A\left\lceil\sqrt{p}\right\rceil-B (0\le A, B\le\left\lceil\sqrt{p}\right\rceil)$，这一步要求 $a\perp p$，但不要求 $p\in\mathbb{P}$。

时间复杂度：$O(\sqrt{p}\log_2\sqrt{p})$。

你想更快的话你用哈希表也行。

## 代码

```cpp
#include <bits/stdc++.h>
#define lowb(a, r, x) lower_bound(a + 1, a + r + 1, x) - a
#define uppb(a, r, x) upper_bound(a + 1, a + r + 1, x) - a
#define _for(i, a, b) for (ll i = a; i <= b; ++i)
#define for_(i, a, b) for (ll i = a; i >= b; --i)
#define far(i, vec) for (auto i : vec)
#define bdmd int mid = (l + r) >> 1
#define NO nullptr
typedef long double ldb;
typedef long long ll;
typedef double db;
const ll N = 1e5 + 10;
namespace SOLVE {
	ll p, b, n, ans;
	std::map<ll, ll> h;
	inline ll rnt () {
		ll x = 0, w = 1; char c = getchar ();
		while (!isdigit (c)) { if (c == '-') w = -1; c = getchar (); }
		while (isdigit (c)) x = (x << 3) + (x << 1) + (c ^ 48), c = getchar ();
		return x * w;
	}

	inline ll FastPow (ll a, ll b, ll P) {
		ll ans = 1;
		while (b) {
			if (b & 1) ans = ans * a % P;
			a = a * a % P, b >>= 1;
		}
		return ans;
	}

	inline bool In () {
		ans = -1, h.clear ();
		return scanf ("%lld %lld %lld", &p, &b, &n) != EOF;
	}
	inline void Solve () {
		ll qp = ceil (sqrt (p));
		_for (i, 0, qp) h[n * FastPow (b, i, p) % p] = i;
		ll t = FastPow (b, qp, p), num = 1;
		_for (i, 1, qp) {
			num = num * t % p;
			if (h[num]) {
				ans = (i * qp % p - h[num] + p) % p;
				return;
			}
		}
		return;
	}
	inline void Out () {
		if (ans == -1) puts ("no solution");
		else printf ("%lld\n", ans);
		return;
	}
}
int main () {
	while (SOLVE::In ()) {
		SOLVE::Solve ();
		SOLVE::Out ();
	}
	return 0;
} /*



*/
```


---

## 作者：Y_QWQ_Y (赞：2)

本题的 $C$ 是质数，所以直接 BSGS（Baby Step-Giant Step）。

程序就是找最小的 $x$ 的过程，也就是找答案的过程。

大致思路如下：

设 $x=i\times m+k$。

我们可以将原式变为 $(A\operatorname{xor}M\operatorname{xor}i)\times (A\operatorname{xor}j)\equiv B\pmod C$，$D=(A\operatorname{xor}M)$，则 $(D\operatorname{xor}i)\times (A\operatorname{xor}j)\equiv B\pmod C$，将 $A\operatorname{xor}j$ 存入哈希表中，枚举 $i \in[1,M-1]$，通过扩欧（exgcd）求出 $A\operatorname{xor}j$ 再去哈希表中对应 $j$。

但是，确定有没有解，其实就是判断 $A\operatorname{xor}j$ 有没有解，而要求最小解，所以只能在 $0$ 到 $C - 1$ 之间枚举，因为 $\gcd(D\operatorname{xor}i,C)=1$。

那么，有了思路，代码就很好写了~~似乎是题解区的最长代码~~：
```cpp
（码风不太好看）
#include <bits/stdc++.h>
#define int long long//个人习惯，但是要把int main ()换成signed main ()
#define sycn ios::sync_with_stdio (0),cin.tie (0), cout.tie (0)
#define sq 46340
using namespace std;
int j[sq + 10], v[sq + 10], a, b, c;
bool h[sq + 10];
void hash_in (int i, int d)//插入哈希表
{
	int s = d % sq;
	while (h[s] && v[s] != d)
	{
		++ s;
		if (s == sq)s -= sq;
	}
	if (! h[s])
	{
		h[s] = 1;
		j[s] = i;
		v[s] = d;
	}
}
int find (int d)
{
	int s = d % sq;
	while (h[s] && v[s] != d)
	{
		++ s;
		if (s == sq)s -= sq;
	}
	if (! h[s])return -1;
	return j[s];
}
int exgcd (int a, int b, int &x, int &y)//扩欧
{
	if (! b)
	{
		x = 1;
		y = 0;
		return a;
	}
	int g = exgcd (b, a % b, x, y);
	int t = x;
	x = y;
	y = t - a / b * y;
	return g;
}
int baby_step (int a, int b, int c)//BS部分，计算最小解
{
	for (int i = 0; i < sq + 10; ++ i)
	{
		h[i] = 0;
		v[i] = j[i] = 0;
	}
	int m = ceil (sqrt (c * 1.0));
	int d = 1;
	for (int i = 0; i < m; ++ i)
	{
		hash_in (i, d);
		d = d * a % c;
	}
	int res = 1, x, y;
	for (int i = 0; i < m; ++ i)
	{
		exgcd (res, c, x, y);
		x *= b;
		x = (x % c + c) % c;
		int k = find (x);
		if (k != -1)return i * m + k;
		res = res * d % c;
	}
	return -1;//如果0到m-1之间无解，则 A^j 无解
}
signed main ()
{
	while (cin >> c >> a >> b)//多组询问别忘了
	{
		int z = step (a, b, c);
		if (z == -1)cout << "no solution\n";//无解
		else cout << z << '\n';
	}
	return 0;
}
```

---

## 作者：楠枫 (赞：2)

本题是一道 $BSGS$ 裸题，用于求解高次同余方程，形如 $a^x\equiv b(\mod p)$，其中 $a$，$p$ 互质（不互质还有 $EXBSGS$）。

建议多使用 $HASH$ 表，不要懒省事使 $map$，数据大时会 $T$ 飞。

$AC \kern 0.4emCODE:$
```cpp
#include<bits/stdc++.h>
#define int long long
#define ri register int
#define p(i) ++i
#define H(x) ((x)%P+1)
using namespace std;
const int P=65537;
inline int read() {
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}
struct HASH{
	struct Hash{
		int v,nxt,w;
	}H[P+7];
	int first[P+7],t;
	inline void init() {memset(first,0,sizeof(first));t=1;}
	inline void add(int v,int w) {
		int u=H(v);
		H[t].v=v;
		H[t].w=w;
		H[t].nxt=first[u];
		first[u]=t++;
	}
	inline int find(int v) {
		int u=H(v);
		for (ri i(first[u]);i;i=H[i].nxt) if (H[i].v==v) return H[i].w;
		return -1;
	}
}H;
inline int fpow(int x,int y,int p) {
	int res=1;
	while(y) {
		if (y&1) res=res*x%p;
		x=x*x%p;y>>=1;
	}
	return res;
}
inline int BSGS(int a,int b,int p) {
	H.init();b%=p;
	int t=ceil(sqrt(p));//注意这里，ceil(sqrt(p))与sqrt(p)+1没什么区别，但后者会WA，有可能是数据有锅，p非质数了。
	for (ri i(0);i<=t;p(i)) H.add(b,i),b=b*a%p;
	int c=1;a=fpow(a,t,p);
	if (!a) return !b?1:-1;
	for (ri i(0);i<=t;p(i)) {
		int j=H.find(c);
		if (j>=0&&i*t-j>=0) return i*t-j;
		c=c*a%p;
	}
	return -1;
}
signed main() {
	int p,a,b;
	while(scanf("%lld",&p)!=EOF) {
		a=read(),b=read();
		int ans=BSGS(a,b,p);
		if (ans==-1) printf("no solution\n");
		else printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：世界非同凡响 (赞：2)

**这道题 板上钉钉的 Baby-Step-Gaint-Step
及其拓展算法的应用**

不懂得求解 数学一本通 或网络博主
（因为解析太多了 QAQ）

```
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#define LL long long
using namespace std;


//hash表的建立
class Hash
{
    //定义内部属性
    //private:
    static const int HASHMOD = 3894229;
    int top;
    int hash[HASHMOD + 100], value[HASHMOD + 100], stack[1 << 16];
    LL locate(const int x) const
    {
        int h = x % HASHMOD;
        while (hash[h] != -1 && hash[h] != x)
            h++;

        return h;
    }

public:
    Hash() : top(0) { memset(hash, 0xff, sizeof(hash)); }
    //插入
    void insert(const int x, const int v)
    {
        const LL h = locate(x);
        if (hash[h] == -1)
        {
            hash[h] = x;
            value[h] = v;
            stack[++top] = h;
        }
    }
    //查找
    int get(const int x) const
    {
        const LL h = locate(x);
        return hash[h] == x ? value[h] : -1;
    }
    //清空
    void clear()
    {
        while (top)
        {
            hash[stack[top--]] = -1;
        }
    }
}hash_m;

struct Triple
{
    LL x, y, z;
    Triple() {}
    Triple(const LL a, const LL b, const LL c) : x(a), y(b), z(c) {}
};

Triple ExtendedGCD(const int a, const int b)
{
    if (b == 0)
    {
        return Triple(1, 0, a);
    }

    const Triple last = ExtendedGCD(b, a % b);

    return Triple(last.y, last.x - a / b * last.y, last.z);
}

LL BSGS(LL A, LL B, LL C)
{
    const LL sqrtn = static_cast<LL>(ceil(sqrt(C)));
    LL base = 1;
    hash_m.clear();
    for (LL i = 0; i < sqrtn; ++i)
    {
        hash_m.insert(base, i);
        base = base * A % C;
    }

    LL j = -1, D = 1;
    for (LL i = 0; i < sqrtn; ++i)
    {
        Triple res = ExtendedGCD(D, C);
        LL k = C / res.x;
        res.x = (res.x * B / res.z % k + k) % k;

        j = hash_m.get(res.x);
        if (j != -1)
            return i * sqrtn + j;

        D = D * A % C;
    }
}

LL BSGS_Extended(LL A, LL B, LL C)
{
    LL tem = 1, cnt = 0, D = 1;
    for (int i = 0; i < 32; ++i)
    {
        if (tem == B)
        {
            return i;
        }

        tem = tem * A % C;
    }

    for (Triple res; (res = ExtendedGCD(A, C)).z != 1; cnt++)
    {
        if (B % res.z)
        {
            return -1;
        }

        B /= res.z;
        C /= res.z;

        D = D * A / res.z % C;
    }

    const int sqrtn = static_cast<int>(ceil(sqrt(C)));
    LL base = 1;
    hash_m.clear();
    for (int i = 0; i < sqrtn; ++i)
    {
        hash_m.insert(base, i);
        base = base * A % C;
    }

    LL j = -1, i;
    for (i = 0; i < sqrtn; ++i)
    {
        Triple res = ExtendedGCD(D, C);
        const int k = C / res.z;
        res.x = (res.x * B / res.z % k + k) % k;

        j = hash_m.get(res.x);
        if (j != -1)
            return i * sqrtn + j + cnt; // 拓展算法->关键点

        D = D * base % C;
    }
    return -1;
}

int main()
{
    LL a, b, c;
    while ((cin >> c >> a >> b))
    {
        b %= c;
        const LL ans = BSGS_Extended(a, b, c);
        if (ans == -1)
            cout << "no solution" << endl;
        else
            /*cout << a << "^" << ans << "--" << b << " mod " << c << endl;*/
            printf("%lld\n", ans);
    }

    //system("pause");
    return 0;
}

```

---

## 作者：CQ_Bab (赞：1)

# 思路
因为题目中给定的 $b$ 和 $p$ 一定互质，所以直接用普通的 BSGS 即可。我们首先可以发现答案一定在 $1\sim p$ 之间，所以我们考虑将 $1\sim p$ 分块处理，首先我们将他们分成 $\sqrt q$ 块，然后我们设答案为 $a^{i\times len-m}$ 那么我们就可以得到 $a^{i\times len}\bmod p=b\times a^m\bmod p$ 所有我们可以处理出所有的 $a^m\times b\bmod p$ 然后再枚举一下 $i$ 看是否满足条件即可。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std ;
#define int long long
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define rep1(i,x,y) for(int i=x;i>=y;i--)
#define fire signed
#define kong putchar(' ')
#define in(x) scanf("%lld",&x)
#define lcm(x,y) x*y/__gcd(x,y)
#define il inline
il void print(int x) {
	if(x>=10) print(x/10);
	putchar(x%10+'0');
}
int a,b,p;
int qmi(int a,int b,int q) {
	int res=1;
	while(b) {
		if(b&1) res=res*a%q;
		a=a*a%q;
		b>>=1;
	}return res;
}
int bsgs(int a,int b,int p) {
	unordered_map<int,int>mp;
	a%=p,b%=p;
	int len=sqrt(p-1)+1;
	rep(i,0,len) mp[b]=i,b=b*a%p;//预处理
	int s=a=qmi(a,len,p);
	rep(i,1,len) {
		if(mp[s]) return i*len-mp[s];//找到了
		s=a*s%p;//继续递归
	} return -1;
}
fire main() {
	while(cin>>p>>a>>b) {
	int res=bsgs(a,b,p);
	if(res==-1) cout<<"no solution"<<endl;
	else cout<<res<<endl;
}
	return false;
}
```

---

## 作者：Hadtsti (赞：1)

### 题意简述
给定三个正整数 $A$、$B$、$M$，其中 $A$、$M$ 互质，求最小的正整数 $L$ 满足：$A^L \equiv B \pmod M$。
### 题目分析
这个题是高次同余方程的模板题。对于高次同余方程问题，一个经典的算法就是 Baby Step,Giant Step 算法，简称 BSGS 算法。以下为其具体过程：

首先设 $L=x \times \lceil \sqrt{M} \rceil-y$  ，其中 $0 \leq y \leq \lceil \sqrt{M} \rceil$，那么就有 $A^{x \times \lceil \sqrt{M} \rceil-y}\equiv B \pmod M$，又可以转化为 $(A^{\lceil \sqrt{M} \rceil})^x \equiv B \times A^y \pmod M$。接下来，对所有 $y \in [0,\lceil \sqrt{M} \rceil]$，将其对应的 $B \times A^y$ 插入到一个哈希表中，然后枚举 $x \in [0,\lceil \sqrt{M} \rceil ]$ 的取值，计算出 $(A^{\lceil \sqrt{M} \rceil})^x $ 并查找在哈希表中有无与其对应的 $y$ 即可，最终答案就是 $L=x \times \lceil \sqrt{M} \rceil-y$，若在哈希表中没有对应的 $y$ 的值，那么无解。

至于该算法的时间复杂度，别的题解中没有进行详细解释，此处解释一下。由于 $A$、$M$ 互质，所以对于任意的正整数 $i$，有$A^i\equiv A^{i \mod M}\pmod M$。因此，若原方程有解，就有 $0 \leq L \leq M$，即$0 \leq x \times \lceil \sqrt{M} \rceil-y \leq M$。而$0 \leq y \leq \lceil \sqrt{M} \rceil$，从而有 $0 \leq x \leq \lceil \sqrt{M} \rceil$。因此我们枚举 $x$ 取值的时间复杂度为 $O(\sqrt{M})$，同样地，建立 $B \times A^y$ 的哈希表的时间复杂度也为 $O(\sqrt{M})$。而其中计算 $(A^{\lceil \sqrt{M} \rceil})^x $、$A^y$ 使得最终的时间复杂度需要乘上一个 $\log\sqrt{M}$，因此总时间复杂度为 $O(\sqrt{M}\log\sqrt{M})$。另外，在代码中，我使用了 STL 的 unordered_map 代替了手写的哈希表，因为这样非常方便
~~（其实是我懒得自己写了）~~，不过常数较大，在数据较大时不建议使用，并且还容易 MLE。

最后附上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,m;
int pw(int a,int b,int m)//快速幂。 
{
	int res=1;
	for(;b;b>>=1)
	{
		if(b&1)
			res=(long long)res*a%m;
		a=(long long)a*a%m;
	}
	return res;
}
int BSGS(int a,int b,int m)
{
	unordered_map<int,int>hash;//哈希表。 
	hash.clear();
	a%=m;
	b%=m;
	int t=(int)sqrt(m)+1; 
	for(int i=0;i<t;i++)//枚举B乘A的y次方，建立哈希表。 
	{
		int val=(long long)b*pw(a,i,m)%m;
		hash[val]=i;
	}
	a=pw(a,t,m);//计算A的根号M次方，不需要每次计算一遍。 
	for(int i=0;i<=t;i++)//枚举A的根号M次方的x次方，并在哈希表中查找对应的y。 
	{
		int val=pw(a,i,m);
		int j=hash.find(val)==hash.end()?-1:hash[val];
		if(j>=0&&i*t-j>=0)
			return i*t-j;
	}
	return -1;//无解 
}
int main()
{
	while(scanf("%d%d%d",&m,&a,&b)==3)
	{
		if(b==1) 
		{
			printf("0\n");
			continue;	
		}
		int ans=BSGS(a,b,m);
		if(ans>=0)
			printf("%d\n",ans);
		else
			printf("no solution\n");
	}
	return 0;
}
```

~~本篇是本人的第二篇题解，希望审核大大可以给过~~

---

## 作者：Laoshan_PLUS (赞：0)

### 题意

给定 $P,B,N$，求解方程 $B^x\equiv N\pmod P$。多组数据。

满足 $P\in\mathbf P$，$2\le B,N<P<2^{31}$。

### 解析

BSGS 模板题。

因为 $P\in\mathbf P$，所以可以在模 $P$ 意义下执行关于 $B$ 的乘除法运算。

设 $x=it-j$，其中 $t=\left\lceil\sqrt P\right\rceil$，$0\le j\le t-1$，则方程变为 $B^{it-j}\equiv N\pmod P$，即 $B^{it}\equiv N\times B^j\pmod P$。

对于所有的 $j\in[0,t-1]$，把 $N\times B^j$ 插入一个 Hash 表，可以用 unordered_map 实现。

枚举 $i$ 的所有可能取值，即 $i\in[0,t]$，计算出 $B^{it}\bmod P$，在 Hash 表中查找是否存在对应的 $j$，更新答案即可。

这就是 BSGS 算法的基本原理，时间复杂度 $O(\sqrt P)$。

### 坑点

注意特判。若 $N=1$，最小正整数解一定是 $0$。

### 实现

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

inline int power(int a, int b, int p) {
	int res = 1;
	while (b) {
		if (b & 1) res = res * a % p;
		a = a * a % p;
		b >>= 1;
	}
	return res % p;
}

int bsgs(int a, int b, int p) {
	unordered_map<int, int> hash;
	hash.clear();
	b %= p;
	int t = (int)sqrt(p) + 1;
	for (int j = 0; j < t; j++) {
		int val = b * power(a, j, p) % p;
		hash[val] = j;
	}
	a = power(a, t, p);
	if (a == 0) return b == 0 ? 1 : -1;
	for (int i = 0; i <= t; i++) {
		int val = power(a, i, p);
		int j = hash.find(val) == hash.end() ? -1 : hash[val];
		if (j >= 0 && i * t - j >= 0) return i * t - j;
	}
	return -1;
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	int p, b, n;
	while (cin >> p >> b >> n) {
		if (n == 1) {
			cout << "0\n";
			continue;
		}
		int res = bsgs(b, n, p);
		if (res == -1) cout << "no solution\n";
		else cout << res << '\n';
	}
	
	return 0;
}
```

---

## 作者：Mooncrying (赞：0)

# UVA 10225 Discrete Logging 题解

### [题目传送门](https://www.luogu.com.cn/problem/UVA10225)

这是一道求出形如 $a ^ x \equiv b \pmod p$，且 $a, p$ 互质的方程的模板题。

相比于[这道模板题](https://www.luogu.com.cn/problem/P3846)，本题属于数据加强版。

我们使用 BSGS 算法求解。

设 $t = \lfloor\sqrt{p}\rfloor$，$0 \le j \le t - 1$，$x = i \cdot t - j$，可得 $a ^ {i \cdot t - j} \equiv b \pmod p$，两边同乘 $a ^ j$，得到 $a ^ {t \cdot i} \equiv b \cdot a ^ j\pmod p$.

我们可以用一个 map 记录每一个 $b \cdot a ^ j\pmod p$，然后枚举每个 $i  \in [0,t]$，计算出每一个 $a ^ {t \cdot i} \pmod p$，判断该值在 map 中是否出现，这样就能求出对应的 $i,j$，又因为 $t$ 已知，这样就能求出对应的解 $x$ 的值。如果所有的 $a ^ {t \cdot i}\pmod p$ 在 map 中都未出现，说明该方程无解。


另外，如果 $a \equiv 0 \pmod p$ 且 $b \bmod p \ne 0$ 时方程无解，注意特判。

本算法时间复杂度为 $O (\sqrt{p} \log p)$ 级别。

本题多测，注意初始化。

下面是代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int p,a,b;
int qpow(int x,int y,int p)
{
	int ans = 1, res = x;
	while(y)
	{
		if(y & 1) ans = 1ll * ans * res % p;
		res = 1ll * res * res % p;
		y >>= 1;
	}
	return ans;
}
int BSGS(int a,int b,int p)
{
	map<int,int> hs;
	map<int,bool> vis;
	int t = sqrt(p); b %= p;
	int v = b;
	for(int i = 0; i <= t; ++ i)
	{
		hs[v] = i;
		vis[v] = 1;
		v = 1ll * v * a % p;//计算每一个 b * a ^ j 的值并插入 map 中
	}
	a = qpow(a,t,p);
	if(a == 0) return b == 0 ? 1 : -1;//特判
	for(int i = 0; i <= t; ++ i)
	{
		int v = qpow(a,i,p);
		if(vis[v])
		{
			int j = hs[v];
			if(t * i - j >= 0) return t * i - j;//返回 x 的值
		}
	}
	return -1;//无解，返回 -1 
}
int main ()
{
	while(scanf("%d%d%d",&p,&a,&b) != EOF)
	{
		int ans = BSGS(a,b,p);
		if(ans == -1) printf("no solution\n");
		else printf("%d\n",ans);
	}
	return 0;//完结撒花
}
```

---

## 作者：封禁用户 (赞：0)

## 分析：

本题的 $C$ 是素数，所以我们直接使用普通的 BSGS。

在寻找最小的 $x$ 的过程中，将 $x$ 设为 $i \times M + j$。从而原式变为 $A^{M^i} \times A^j \equiv{B}\pmod{C}$，那么 $D^i \times A^j \equiv{B}\pmod{C}$，我们预先将 $A^j$ 存入哈希表中，然后枚举 $i(0 \le i \le M-1)$，根据扩展欧几里得求出 $A^j$，再去哈希表中查找相应的 $j$，那么 $x = i\times M + j$。确定 $x$ 是否有解，就是在循环 $i$ 的时候判断 $A^j$ 是否有解，而且最小的解 $x$ 一定在 $(0∼C-1)$，因为 $\gcd(D^i,C) = 1$。如果 $(0∼C-1)$ 无解，那么一定无解。因为 $A^x \bmod C$ （ $C$ 是素数）有循环节，则 $A^x \bmod C = A^(x \bmod \varphi[c]) \bmod C$ 循环节的长度为 $\varphi(C)$，即 $C-1$， $x \ge C$ 以后开始新一轮的循环，因此$(0∼C-1)$ 无解的话，一定无解！

---

