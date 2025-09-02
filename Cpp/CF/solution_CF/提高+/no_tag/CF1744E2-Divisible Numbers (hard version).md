# Divisible Numbers (hard version)

## 题目描述

This is an hard version of the problem. The only difference between an easy and a hard version is the constraints on $ a $ , $ b $ , $ c $ and $ d $ .

You are given $ 4 $ positive integers $ a $ , $ b $ , $ c $ , $ d $ with $ a < c $ and $ b < d $ . Find any pair of numbers $ x $ and $ y $ that satisfies the following conditions:

- $ a < x \leq c $ , $ b < y \leq d $ ,
- $ x \cdot y $ is divisible by $ a \cdot b $ .

Note that required $ x $ and $ y $ may not exist.

## 样例 #1

### 输入

```
10
1 1 2 2
3 4 5 7
8 9 15 18
12 21 14 24
36 60 48 66
1024 729 373248 730
1024 729 373247 730
5040 40320 40319 1000000000
999999999 999999999 1000000000 1000000000
268435456 268435456 1000000000 1000000000```

### 输出

```
2 2
4 6
12 12
-1 -1
-1 -1
373248 730
-1 -1
15120 53760
-1 -1
536870912 536870912```

# 题解

## 作者：Moya_Rao (赞：21)

# 题目大意

给定四个正整数 $a,b,c,d$，满足 $a<c$ 且 $b<d$，现在要求你构造出一组整数对 $(x,y)$ 满足以下条件：
- $a < x \le c$；
- $b < y \le d$；
- $a \times b \mid x \times y$。

请求出这个整数对并输出，如果不存在请输出 `-1 -1`。注意本题有 $T$ 组数据。

$1 \le T \le 10$，$1 \le a,b,c,d \le 10^9$。

# 思路

乍一看好像挺难的，看着像个数学题，感觉还要推式子。哎，别怕，其实上很简单！这其实上根本不需要推什么式子，它根本算不上是个数学题！

既然枚举肯定是搞不定的，不如根据这个整数对的一些特性入手。

显然的，$x$ 是 $a$ 的某一个因子 $i$ 与 $b$ 的某一个因子 $j$ 的积的倍数。那么我们可以考虑枚举 $i$ 和 $j$。

但是如果我们直接枚举的话，时间复杂度为 $O(\sqrt{a \times b})$，额 $10^9$ 是接受不了的，那该咋办？

其实上不用直接枚举，完全可以一开始就将 $a$ 和 $b$ 的因子分解出来，放进一个数组里，再遍历。

这样的话，时间复杂度真的会变得更优吗？难道不会超时吗？确实，感觉是不行的，但是你上百度一搜，会发现一句话：

> $10^9$ 以内的所有数中，因子最多的数的因子有 $1536$ 个。

虽然不保证这个数值的精确性，但是我们可以得知，$a$ 或 $b$ 的因子个数不会超过 $2000$ 个。

那不就好办了吗？时间复杂度在这个规模下，肯定是没有问题的啦！

好了，时间复杂度的问题解决了，接下来呢？

现在我们已经知道了 $i$ 和 $j$，并且知道了 $x$ 肯定是 $i \times j$ 的倍数，反之可以推出 $y$ 肯定也是 $a \times b \div i \div j$ 的倍数。

我们令 $n$ 的值为 $i \times j$，$m$ 的值为 $a \times b \div i \div j$，于是可以根据 $n$ 和 $m$ 利用除法算出不超过 $c$ 与 $d$ 的最大的 $x$ 和 $y$。再判断一下它们是否分别大于 $a$ 和 $b$，如果是的就输出并结束，不是的就继续干就好啦。

无解的情况咋办？用一个变量 $flag$ 记录一下，如果全都遍历完了还是没有出来答案，就无解啦。

是不是很简单？那就不要看我的代码了，自己写吧！

# 代码

没事，想看代码也没关系，只是真的没必要，因为代码非常短，也非常简单。还给大家留下一个[提交记录](https://codeforces.com/contest/1744/submission/315245615)，这代码，保证对哟！只是希望大家不要抄袭，感谢。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2005 ;
bool flag;
long long T,a,b,c,d,cnt1,cnt2,p1[N],p2[N];
int main(){
    cin>>T;
    while(T--){
        cin>>a>>b>>c>>d;
        cnt1=0,cnt2=0,flag=0;
        for(long long i=1;i*i<=a;i++){
            if(a%i!=0)continue;
            p1[++cnt1]=i;
            if(a/i!=i)p1[++cnt1]=a/i;
        }
        for(long long i=1;i*i<=b;i++){
            if(b%i!=0)continue;
            p2[++cnt2]=i;
            if(b/i!=i)p2[++cnt2]=b/i;
        }
        for(int i=1;i<=cnt1&&!flag;i++){
            long long x=p1[i];
            for(int j=1;j<=cnt2&&!flag;j++){
                long long y=p2[j];
                long long n=x*y,m=a*b/x/y;
                long long ans1=c/n*n,ans2=d/m*m;
                if(ans1<=a||ans2<=b)continue;
                flag=1;cout<<ans1<<" "<<ans2<<"\n";
            }
        }
        if(!flag)cout<<"-1 -1\n";
    }
    return 0;
}
```

如果你觉得本篇题解对你有帮助的话，请点一个小小的赞，多谢多谢！

---

## 作者：EnofTaiPeople (赞：10)

### Part1 前言
有同学问这道题目，我居然分类讨论半天没做出来！今天早上还没出门就突然会了，交了才发现这是 Div3。

---
### Part2 题意简述
给定两个半开半闭区间 $(a,c],(b,d]$，求 $x\in(a,c],y\in(b,d]$，使得 $ab|xy$，注意 $1\le a,b,c,d\le10^9$，$a,b,c,d,x,y$ 均为正整数。

### Part3 如何枚举
容易发现，我们需要找到一组 $(x',y')$，使得 $x'y'=ab,x'|x,y'|y$，显然任何一组合法的 $(x,y)$，都与至少一组 $(x',y')$ 相对应。

发现 $n$ 的因数个数级别是 $\sqrt[3]{n}$，于是可以枚举 $x'$，这是最小的 $x>a$ 就是 $x=\lceil\dfrac{a}{x'}\rceil x'$，再得出 $y'=\dfrac{ab}{x'}$，$y=\lceil\dfrac{b}{y'}\rceil y'$，判断 $x\le c,y\le d$ 即可。

### Part4 实现

直接分解 $ab$ 需要 `Pollard-Rho` 算法，但实际上可以先暴力分解 $a,b$，再枚举两项乘起来得到 $x'$，这样空间复杂度为 $O(\sqrt[3]a+\sqrt[3]b)$，时间复杂度为 $O(\sqrt a+\sqrt b+\sqrt[3]{ab})$，大约是 $\sqrt[3]{10^{18}}=10^6$，可以通过，AC 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
using ll=long long;
ll T,A,B,C,D,F[N],ft,G[N],gt;
void solve(){
    cin>>A>>B>>C>>D;
    ll x,_a,_b,i,j,d;
    for(x=1,ft=gt=0;x*x<A;++x)
        if(!(A%x))F[++ft]=x,F[++ft]=A/x;
    if(x*x==A)F[++ft]=x;
    for(x=1;x*x<B;++x)
        if(!(B%x))G[++gt]=x,G[++gt]=B/x;
    if(x*x==B)G[++gt]=x;
    for(i=1;i<=ft;++i){
        for(j=1;j<=gt;++j){
            d=F[i]*G[j];
            _a=(A/d+1)*d;
            if(_a>C)continue;
            d=A*B/d;
            _b=(B/d+1)*d;
            if(_b>D)continue;
            printf("%lld %lld\n",_a,_b);
            return;
        }
    }puts("-1 -1");
}
int main(){
    ios::sync_with_stdio(false);
    cin>>T;
    while(T--)solve();
    return 0;
}
```
### Part5 后记
好像和其他题解不同，但这是 Div3，所以不用过多纠结。

---

## 作者：Allanljx (赞：8)

## 思路
E1：

枚举 $x$，那么 $y$ 必须是 $x\div\gcd(a\times b,x)$ 的倍数，然后可以利用除法的向下取整算出 $y$ 在不超过 $d$ 的情况下最大是多少，然后再判 $y$ 是否大于 $b$。

E2：

E1 复杂度的瓶颈是有许多无用的 $x$，因此考虑一些 $x$ 的性质。$x$ 一定是 $a$ 的一个因数与 $b$ 的一个因数的积的倍数，所以分别枚举 $a$ 和 $c$ 的某个因数，设为 $p,q$。所以 $x$ 就是最小的大于 $a$ 的并且是 $p\times q$ 的倍数的数；$y$ 是最小的大于 $c$ 的并且是 $(a\times b)\div(p\times q)$ 的倍数的数。

## 代码
E1:
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[200005],b[200005];
int t,y;
signed main()
{
    cin>>t;
    while(t--)
	{
		int a,b,c,d;
        cin>>a>>b>>c>>d;
        int f=0;
        int x=a*b;
        for(int i=a+1;i<=c;i++)
		{
            int y=x/__gcd(x,i);
            y=d/y*y;
            if(y>b)
			{
				cout<<i<<' '<<y<<endl;
                f=1;
                break;
            } 
        }
        if(!f) cout<<"-1 -1\n";
    }
}
```
E2:
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,a,b,c,d;
int a1[200005];
int a2[200005];
int tmp1,tmp2;
signed main()
{
	ios::sync_with_stdio(0);
	cin>>t;
	while(t--)
	{
		cin>>a>>b>>c>>d;
		tmp1=tmp2=0;
		for(int i=1;i*i<=a;i++)
		{
			if(a%i!=0) continue;
			a1[++tmp1]=i;
			if(i*i!=a) a1[++tmp1]=a/i;
		}
		for(int i=1;i*i<=b;i++)
		{
			if(b%i!=0) continue;
			a2[++tmp2]=i;
			if(i*i!=b) a2[++tmp2]=b/i;
		}
		int f=0;
		for(int i=1;i<=tmp1;i++)
		{
			if(f) break;
			for(int j=1;j<=tmp2;j++)
			{
				int x=a1[i]*a2[j];
				int y=a*b/x;
				if((a+x)/x*x<=c&&(b+y)/y*y<=d)
				{
					cout<<(a+x)/x*x<<' '<<(b+y)/y*y<<endl;
					f=1;
				}
				if(f) break;
			}
		}
		if(!f) cout<<"-1 -1\n"; 
	}
}
```

---

## 作者：_•́へ•́╬_ (赞：8)

## 思路

跟官方题解不一样。

吧 $a$ 和 $b$ 分解质因数，暴力枚举每个质因数分给 $x$ 还是 $y$。

最后 $x$ 和 $y$ 弄出来再乘一个东西调整到范围内。

显然这个复杂度是指数的。考虑剪枝。

如果有几个质因数是相等的，就强制前面几个给 $x$，后面的给 $y$，不准交叉的。

这一点如何实现？搜索的时候记一下每个质数给了谁。如果当前的质数和上一个质数相等，而上一个给了 $y$，那么这一个就必须依然给 $y$。

复杂度正确。

## code

```cpp
#include<stdio.h>
#include<algorithm>
#define int long long
using namespace std;
inline char nc()
{
	static char buf[99999],*l,*r;
	return l==r&&(r=(l=buf)+fread(buf,1,99999,stdin),l==r)?EOF:*l++;
}
inline void read(int&x)
{
	char c=nc();for(;c<'0'||'9'<c;c=nc());
	for(x=0;'0'<=c&&c<='9';x=(x<<3)+(x<<1)+(c^48),c=nc());
}
int t,a,b,c,d,e,f[66],sz,ans1,ans2;bool u[66];//u[i]==1表示给了x，==0表示给了y
struct __readt__{inline __readt__(){read(t);}}_readt___;
inline void dfs(const int&i,int x,int y)
{
	if(x>c||y>d)return;
	if(i==sz)
	{
		int i;
		for(i=a/x;i*x<=a;++i);x*=i;//这里我原来脑残没有用除法，一个个循环的，E2被大佬ltc叉了
		for(i=b/y;i*y<=b;++i);y*=i;
		if(x<=c&&y<=d)ans1=x,ans2=y;
		return;
	}
	if(!i||(f[i]^f[i-1])||u[i-1])//这里一堆或，其实是排除了f[i]==f[i-1]&&u[i-1]==0
	{
		u[i]=1;
		dfs(i+1,x*f[i],y);
	}
	if(~ans1)return;
	u[i]=0;
	dfs(i+1,x,y*f[i]);
}
main()
{
	read(a);read(b);read(c);read(d);
	e=a;sz=0;
	for(int i=2;i*i<=e;++i)for(;!(e%i);f[sz++]=i,e/=i);
	if(e>1)f[sz++]=e;//分解质因数
	e=b;
	for(int i=2;i*i<=e;++i)for(;!(e%i);f[sz++]=i,e/=i);
	if(e>1)f[sz++]=e;//分解质因数
	sort(f,f+sz);ans1=ans2=-1;
	dfs(0,1,1);
	printf("%lld %lld\n",ans1,ans2);
	if(--t)main();
}
```

![](https://cdn.luogu.com.cn/upload/image_hosting/l1vwtle7.png)

---

## 作者：苏联小渣 (赞：6)

题目要求一组合法的 $(x,y)$ 满足 $x \in (a,c],y \in (b,d]$ 且 $a \cdot b|x \cdot y$。

这是一道暴力题，没有结论，没有算法。先考虑 Easy Version 怎么做。

令 $t=a \cdot b$，设有一组 $p \cdot q=t$（就是 $p,q$ 为 $t$ 的两个约数且 $p \cdot q=t$）首先不难发现一定有 $x=up,y=vq$，其中 $u,v$ 为常数。也就是说，$x$ 是 $p$ 的倍数，$y$ 是 $q$ 的倍数。

这样 E1 就可以做了，暴力枚举 $t$ 的所有约数。假设现在枚举到的是 $p,q(p \cdot q=t)$，那么我们找到 $p$ 的倍数中第一个 $>a$ 的那个，和 $q$ 的倍数中第一个 $>b$ 的那个，判断两者是否分别 $\le c,\le d$ 即可。

时间复杂度 $O(\sqrt{ab})$，可以通过 E1。

接下来考虑 E2。上面的做法慢在哪里？**由于从 $1$ 枚举到 $\sqrt{t}$，所以有太多的无用状态**。考虑从减少无用状态的角度来优化，也就是从最简单的角度优化——优化枚举约数。考虑把 $t$ 分解质因数，比如说 $12=2 \times 2 \times 3,18=2 \times 3 \times 3$，那么 $p$ 一定就是选所有质因数组成的**可重集**其中的一部分（比如说，$12$ 的质因数组成的可重集就是 $\{2,2,3\}$），$q$ 可以看为 $\dfrac{t}{p}$。比如说对于 $12,p$ 就可以选 $\{1\},\{2\},\{2 \times 2\},\{2 \times 3\},\{2 \times 2 \times 3\}$。发现这就是枚举一个子集，可以用 dfs 实现。判断的方法还是如上，找到 $p$ 的倍数中第一个 $>a$ 的那个，和 $q$ 的倍数中第一个 $>b$ 的那个，判断两者是否分别 $\le c,\le d$。

那么这样为什么是对的呢？首先，分解 $t$ 的质因数肯定不能直接来，我们先把 $a,b$ 分别分解质因数然后对应指数相加，就能得到 $t$ 的质因数了。用 map 实现，这一部分复杂度为 $O(\sqrt{a} \log \sqrt{a}+\sqrt{b} \log \sqrt{b})$。dfs 的时间复杂度怎么分析？发现由于是枚举质因数的子集，那么 $t$ 的每个约数都会**恰好**被搜索一次，时间复杂度就是 $O(f(t)),f(t)$ 表示 $t$ 的约数个数。感性理解一下，这个时间复杂度肯定是合法的。

### Code：

```c++
#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, a, b, c, d, cnt, tot, flag;
int nxt(int x, int y){
	x ++;
	int yu = y - x % y;
	if (yu == y) yu = 0;
	return x + yu;
}
map <int, int> mpx, mpy;
map <int, int> :: iterator itx, ity;
struct node{
	int num, ci;
}yue[1000010];
void dfs(int x, int fir){
	if (flag) return ;
	int sec = tot / fir;
	int nx = nxt(a, fir), ny = nxt(b, sec);
	if (nx <= c && ny <= d){
		printf ("%lld %lld\n", nx, ny);
		flag = 1;
		return ;
	}
	nx = nxt(a, sec), ny = nxt(b, fir);
	if (nx <= c && ny <= d){
		printf ("%lld %lld\n", nx, ny);
		flag = 1;
		return ;
	}
	if (x > cnt) return ;
	int tmp = fir;
	for (int i=0; i<=yue[x].ci; i++){
		dfs(x+1, tmp);
		tmp *= yue[x].num;
	}
}
signed main(){
	scanf ("%lld", &t);
	while (t --){
		scanf ("%lld%lld%lld%lld", &a, &b, &c, &d);
		tot = a * b;
		mpx.clear(); mpy.clear(); cnt = 0;
		flag = 0;
		int na = a, nb = b;
		for (int i=2; i<=sqrt(a); i++){
			while (na % i == 0) na /= i, mpx[i] ++;
		}
		if (na > 1) mpx[na] ++;
		for (int i=2; i<=sqrt(b); i++){
			while (nb % i == 0) nb /= i, mpy[i] ++;
		}
		if (nb > 1) mpy[nb] ++;
		for (itx=mpx.begin(); itx!=mpx.end(); itx++){
			if (mpy.find(itx->first) != mpy.end()){
				mpx[itx->first] += mpy[itx->first];
				ity = mpy.find(itx->first);
				mpy.erase(ity);
			}
		}
		for (ity=mpy.begin(); ity!=mpy.end(); ity++){
			mpx[ity->first] += ity->second;
		}
		yue[++cnt].num = 1, yue[cnt].ci = 1;
		for (itx=mpx.begin(); itx!=mpx.end(); itx++){
			yue[++cnt].num = itx->first, yue[cnt].ci = itx->second;
		}
		dfs(1, 1);
		if (!flag) puts ("-1 -1");
	}
	return 0;
}

```

---

## 作者：SouthCity (赞：2)

### 题解：CF1744E2 Divisible Numbers (hard version)
处理出 $a$ 的因数和 $b$ 的因数，每一个小于 $\sqrt a$ 的因数 $x$ 都可以配对一个因数 $\frac{a}{x}$，时间 $O(\sqrt n)$。             
利用第一步，处理出所有 $x,y$ 使得 $x\times y=a\times b$，遍历 $a$ 的因数 $i$，和 $b$ 的因数 $j$，$x=\frac{a}{i}\times j,y=\frac{b}{j}\times i$ 满足要求。                  
找到两个数 $n,m$，使得 $a<n\times x\le c,b<m\times y\le d$，先找到一个 $n$，使得 $n\times x\le a$，这个 $n$ 加 $1$ 满足要求。             
输出答案 $n\times x$ 和 $m\times y$。             
如果没有找到答案就输出无解。          
代码实现。                    

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,a,b,c,d;
vector<int> s[2];
void C(int x,int n){
    s[n].clear();
    for(int i=1;i*i<=x;i++){
        if(x%i==0){
            s[n].push_back(i),s[n].push_back(x/i);
        }
    }
}
signed main(){
    for(cin>>t;t--;){
        cin>>a>>b>>c>>d;
        C(a,0),C(b,1);
        int xx=-1,yy=-1;
        for(int i:s[0]){
            for(int j:s[1]){
                int x=a/i*j,y=b/j*i;
                if(a/x*x+x<=c && b/y*y+y<=d){
                    xx=a/x*x+x,yy=b/y*y+y;
                }
            }
        }
        cout<<xx<<" "<<yy<<"\n";
    }
	return 0;
}
```

---

## 作者：20111019Yu (赞：2)

### 思路
#### part1

首先，枚举 $x$ 和 $y$ 的方法明显会超时到飞起，所以换个思路，根据小学数学我们可得知。

若存在 $x$ 和 $y$，则一定有 $ab=pq$ 且 $p\mid x$，$q\mid y$，这下只用枚举 $ab$ 的因数就可以了。

#### part2

当我们瞄一眼数据范围的时候，就能明显发现，枚举 $ab$ 也会飞起，这种方法只能过弱化版，所以继续优化。

根据小学奥数，可以得知，设 $a$ 的因数集合为 $A$，$b$ 的因数集合为 $B$，则 $ab$ 的因数集合为 $AB$，当然会有重复，但总数打死不会超过 $10^{7}$，这是显而易见的。

所以只需分别枚举 $a$ 和 $b$ 的因数，然后乘起来即可。

### code
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int t, a, b, c, d;
vector<int> vec1, vec2, vec3;

signed main(){
	cin >> t;
	while(t--){
		vec1.clear(), vec2.clear(), vec3.clear();
		cin >> a >> b >> c >> d;
		int lin = a * b;
		for( int i = 1; i * i <= a; i++ ){
			if(a % i == 0){
				vec1.push_back(i);
				if(i * i != a) vec1.push_back(a / i);
			}
		}
		for( int i = 1; i * i <= b; i++ ){
			if(b % i == 0){
				vec2.push_back(i);
				if(i * i != b) vec2.push_back(b / i);
			}
		}
		for( auto &i : vec1 ){
			for( auto &j : vec2 ){
				vec3.push_back(i * j);
			}
		}
		bool vis = 0;
		int len = vec3.size();
		for( int i = 0; i < len; i++ ){
			int lin1 = vec3[i];
			int lin2 = lin / vec3[i];
			if(c / lin1 * lin1 > a && d / lin2 * lin2 > b){
				cout << c / lin1 * lin1 << " " << d / lin2 * lin2 << endl;
				vis = 1;
				break;
			}
			if(c / lin2 * lin2 > a && d / lin1 * lin1 > b){
				cout << c / lin2 * lin2 << " " << d / lin1 * lin1 << endl;
				vis = 1;
				break;
			}
		}
		if(!vis) cout << -1 << " " << -1 << endl;
	}
	return 1;\\防抄袭
}
```

---

## 作者：loser_seele (赞：1)

题解区都提到了 Pollard-rho，但是都没写，于是来补一个。

考虑对于一个 $ x $，怎么找到一个 $ x $ 的倍数满足其在区间 $ [a+1,b] $ 内，这个在 E1 里就有提到过，为 $ \lfloor \frac{(a+x)}{x} \rfloor \times x $，然后判一下是否大于 $ b $ 即可。

不难发现题目中的 $ x $ 一定是 $ a \times b $ 的某些因子的倍数，否则显然无解。于是考虑直接 Pollard-rho 暴力分解 $ a \times b $，然后 dfs 枚举每个约数，具体实现是枚举每个质因子在约数中出现的次数，对于每个约数按上面的方法调整到范围内，然后按 E1 的方法算出 $ y $ 之后直接做就行。

由于 $ a,b \leq 10^9 $，于是 $ a \times b \leq 10^{18} $，在这个范围内约数的个数最多不会超过 $ 10^6 $，由唯一分解定理得到每个约数最多被枚举一次，足以通过。

时间复杂度 $ \mathcal{O}((a \times b)^\frac{1}{4}+d_0(a \times b)) $。由于实际上跑不满所以随便过。

代码：（模板部分过长丢云剪贴板）

[模板代码](https://www.luogu.com.cn/paste/cpc2see7)

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
/*模板部分*/
vector<pair<int,int> >p;
vector<uint64_t>tmp;
void dfs1(int step,int now) 
{
	if(step==p.size()) 
    {
		tmp.push_back(now);
		return;
	}
	for (int i=0;i<=p[step].second;i++)
	dfs1(step+1,now*pow(p[step].first,i));
}
main() 
{
	int T;
	cin>>T;
	while(T--) 
    {
		uint64_t a,b,c,d,res;
		cin>>a>>b>>c>>d;
		res=a*b;
		bool ans=0;
		auto map1=OY::Pollard_Rho::decomposite(res);
		p.clear();
		for (auto x:map1) 
        {
			pair<int,int> a= {x.prime,x.count};
			p.push_back(a);
		}
		tmp.clear();
		dfs1(0,1);
		for (auto x:tmp)
		if((a+x)/x*x<=c) 
        {
			x=(a+x)/x*x;
			int gcder=__gcd(a*b,x);
			int now=(a*b)/gcder;
			now=(now+b)/now*now;
			if(now<=d&&!ans)
			cout<<x<<' '<<now<<'\n',ans=1;
		}
		if(!ans)
		puts("-1 -1");
	}
}
```


---

## 作者：Rayman (赞：1)

## 题目大意
---
给出 $a,b,c,d$ 四个数字，要求输出两个数字 $x,y$ 满足 
- 条件 $1$:$x\times y$ 是 $a\times b$ 的倍数
- 条件 $2$:$a<x\le $ 且 $ b<y\le d$ 

---

首先的思路就是，找出一个 $a$ 的因数数 $i$ 和一个 $b$ 的因数 $j$，为了保证条件 $1$，使 $x=a\div i\times j$， $y=b\div j \times i$。然后我们要满足条件 $2$，这里先以 $i<j$ 来举例说明，此时 $x$ 一定满足 $x>a$ , 所以我们要乘上一个较小的数字，使 $y$ 为满足 $y>b$ 的最小值，所以需要将 $y$ 乘 $j\div i+1 $ ，最后判断是否满足 $x\le c$ 且 $y\le d$，满足则找到了一组答案，输出即可。

因为因数的数量有限，所以可以暴力枚举两个数字的因数组合，找出所有的因数的时间复杂度为$\sqrt{n}$，刚好能跑。

```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define ll long long
using namespace std;
typedef vector<ll> vint;


int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int times; cin>>times;	
	while(times--) {
	    ll a,b,c,d;
	    cin>>a>>b>>c>>d;
	    vint pra; vint prb;
	    function<void(vint&,ll)> find=[&] (vint& a,ll x) {
	        for(int i=1;i*i<=x;i++) {
	            if(x%i==0) {
	                if(i*i!=x) a.push_back(x/i);
	                a.push_back(i);
	            }
	        }
	    };
	    find(pra,a); find(prb,b);
	    ll ans1=-1,ans2=-1;
	    for(auto i:pra) {
	        for(auto j:prb) {
	            ll t1=(a/i*j);
	            ll t2=(b/j*i);
	            if(j<=i) t1*=((i+j)/j);
	            if(i<=j) t2*=((i+j)/i);
	            if(t1<=c&&t2<=d) {
	                ans1=t1;
	                ans2=t2;
	                goto end;
	            }
	        }
	    }
	    end: cout<<ans1<<' '<<ans2<<endl;
	}
	return 0;
}
```


---

