# Red-Black Pepper

## 题目描述

Monocarp is going to host a party for his friends. He prepared $ n $ dishes and is about to serve them. First, he has to add some powdered pepper to each of them — otherwise, the dishes will be pretty tasteless.

The $ i $ -th dish has two values $ a_i $ and $ b_i $ — its tastiness with red pepper added or black pepper added, respectively. Monocarp won't add both peppers to any dish, won't add any pepper multiple times, and won't leave any dish without the pepper added.

Before adding the pepper, Monocarp should first purchase the said pepper in some shop. There are $ m $ shops in his local area. The $ j $ -th of them has packages of red pepper sufficient for $ x_j $ servings and packages of black pepper sufficient for $ y_j $ servings.

Monocarp goes to exactly one shop, purchases multiple (possibly, zero) packages of each pepper in such a way that each dish will get the pepper added once, and no pepper is left. More formally, if he purchases $ x $ red pepper packages and $ y $ black pepper packages, then $ x $ and $ y $ should be non-negative and $ x \cdot x_j + y \cdot y_j $ should be equal to $ n $ .

For each shop, determine the maximum total tastiness of the dishes after Monocarp buys pepper packages only in this shop and adds the pepper to the dishes. If it's impossible to purchase the packages in the said way, print -1.

## 说明/提示

Consider the first example.

In the first shop, Monocarp can only buy $ 0 $ red pepper packages and $ 1 $ black pepper package. Black pepper added to all dishes will sum up to $ 10 + 50 + 2 = 62 $ .

In the second shop, Monocarp can buy any number of red and black pepper packages: $ 0 $ and $ 3 $ , $ 1 $ and $ 2 $ , $ 2 $ and $ 1 $ or $ 3 $ and $ 0 $ . The optimal choice turns out to be either $ 1 $ and $ 2 $ or $ 2 $ and $ 1 $ . Monocarp can add black pepper to the first dish, red pepper to the second dish and any pepper to the third dish, the total is $ 10 + 100 + 2 = 112 $ .

In the third shop, Monocarp can only buy $ 1 $ red pepper package and $ 0 $ black pepper packages. Red pepper added to all dishes will sum up to $ 5 + 100 + 2 = 107 $ .

In the fourth shop, Monocarp can only buy an even total number of packages. Since $ n $ is odd, it's impossible to get exactly $ n $ packages. Thus, the answer is $ -1 $ .

## 样例 #1

### 输入

```
3
5 10
100 50
2 2
4
2 3
1 1
3 2
2 2```

### 输出

```
62
112
107
-1```

## 样例 #2

### 输入

```
10
3 1
2 3
1 1
2 1
6 3
1 4
4 3
1 3
5 3
5 4
10
8 10
9 3
1 4
2 5
8 3
3 5
1 6
7 2
6 7
3 1```

### 输出

```
26
-1
36
30
-1
26
34
26
-1
36```

# 题解

## 作者：_•́へ•́╬_ (赞：10)

缝

## 思路

### 第一部分

他给了 $a,b$，我要吧他转换成我能利用的形式。

我要计算：$f[i]$ 表示在 $n$ 对数中选 $i$ 个 $a$ 和 $n-j$ 个 $b$ 的最大美味度。

考虑贪心。

先吧所有的数都选 $b$，这就是 $f[0]$。

把所有的数按 $a-b$ 排序，每次我选择一个 $a-b$，就相当于吧一个 $b$ 的贡献减掉再加上 $a$，意义是吧某一组数由选 $b$ 改为选 $a$。

所以每次我贪心的选 $a-b$ 最大的，依次得到 $f[1\dots n]$。

### 第二部分

我们有了 $f$，考虑怎么应付询问。

询问长 $ux+vy=n$ 的样子。考虑 exgcd。

根据裴蜀定理判无解。

跑 exgcd 得到一组解 $(x_0,y_0)$，调整至 $x_0$ 为最小的可行的非负整数。

判 $y_0<0$ 无解。

通解长酱紫：$\begin{cases}x=x_0+\frac{v}{g}\times t\\y=y_0-\frac{u}{g}\times t\end{cases}$

回归问题：$ux+vy=n$。

$$\begin{cases}ux=ux_0+\frac{uv}{g}\times t\\vy=vy_0-\frac{uv}{g}\times t\end{cases}$$

$$\begin{cases}ux=ux_0+[u,v]\times t\\vy=vy_0-[u,v]\times t\end{cases}$$

方括号是 $\operatorname{lcm}$ 的意思都知道吧（

考虑根号分治：

- $[u,v]$ 较大：直接暴力。
- $[u,v]$ 较小：暴力，然后记忆化。记 $c[i][j]$ 表示 $i=[u,v],j=ux_0$ 的答案。（其实我的写法是预处理了，记忆化也是一样的）

## code

```cpp
#include<stdio.h>
#include<algorithm>
#define N 300001
#define B 9
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
int n,m,a[N],b[N],g,x,y,c[1<<B][1<<B];
inline void exgcd(const int&a,const int&b)
{
	if(!b){g=a;x=1;y=0;return;}
	exgcd(b,a%b);
	int tmp=x-a/b*y;x=y;y=tmp;
}//bx+(a-a/b*b)y=ay+b(x-a/b*y)
inline void max(int&x,const int&y){if(x<y)x=y;}
main()
{
	read(n);b[0]=0;
	for(int i=0,x,y;i<n;++i)
	{
		read(x);read(y);
		a[i]=x-y;
		b[0]+=y;
	}
	sort(a,a+n);
	for(int i=1;i<=n;++i)b[i]=b[i-1]+a[n-i];
	read(m);
	for(int i=1;i<=n&&!(i>>B);++i)for(int j=0;j<=n;++j)max(c[i][j%i],b[j]);
	for(int u,v;m--;)
	{
		read(u);read(v);exgcd(u,v);
		if(n%g){printf("-1\n");continue;}
		x*=n/g;y*=n/g;
		int t=x/(v/g);
		x-=v/g*t;y+=u/g*t;
		if(x>>63)x+=v/g,y-=u/g;
		if(y>>63){printf("-1\n");continue;}
		x*=u;v=u*v/g;
		int maxn=0;
		if((v>>B)||v>n)for(;x<=n;max(maxn,b[x]),x+=v);
		else maxn=c[v][x];
		printf("%lld\n",maxn);
	}
}
/*x:(x*(n/g)+v/g*t)*u
 *y:(y*(n/g)-u/g*t)*v
 */
 ```

---

## 作者：STUDENT00 (赞：4)

# Three Part:

# 前置芝士：

**CF** * **2300** 大水题。只需要掌握数论基础知识——扩展欧几里得即可求解，蒟蒻太弱太懒，故写了个整数三分简化推导，读者可自行推导，舍去三分求解。

# 解题思路：

首先，我们考虑，现有红辣椒 $x$ 份与黑辣椒 $y$ 份，所能产生的最大美味值是多少。

如果全选红辣椒，那么美味值为 $s_1=\sum\limits_{i=1}^{n} a_i$。

现需将其中 $y$ 份红辣椒替换为黑辣椒，每替换一份产生 $b_i-a_i$ 的贡献。欲使贡献最大化，需选择最大的 $y$ 份 $b_i-a_i$ 值，设其和为 $s_2$，最终答案即 $s_1+s_2$。

我们对于每组询问 $(p,q)$，求解二元一次方程 $px+qy=n$，并求出 $dx=\dfrac{q}{\gcd(p,q)},dy=\dfrac{p}{\gcd(p,q)}$。

欲得答案，需求一组自然数对 $(x,y)$，使得 $px+qy=n$，并且 $\max_{y}\left\{b_i-a_i\right\}$ 最大。这个最大值可以利用 $x,y,dx,dy$，并通过一些较为繁琐的处理求得，时间复杂度为 $O(1)$。还有一种三分法，由于函数 $f(x)=max_{x}\left\{b_i-a_i\right\}$ 呈单峰，故可使用整数三分求解，不需要太多的细节，代码实现较易，主要是不用动脑 (QWQ)。

# 代码实现：

十年 `OI` 一场空，不开 `long long` 见祖宗！

部分 `long long` 不保险，不如 `define int long long`！

```cpp
#include<bits/stdc++.h>
#define int long long
#define f(x) (mn+x*dy)*q
using namespace std;
const int N=300005;
const int INF=1e18;
int n,m,a[N],b[N],sum,c[N];
int exgcd(int a,int b,int &x,int &y){
	if(!b){x=1,y=0;return a;}
	int x1,y1;
	int d=exgcd(b,a%b,x1,y1);
	x=y1,y=x1-a/b*y1;
	return d;
}
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++) scanf("%lld%lld",&a[i],&b[i]),sum+=a[i],c[i]=b[i]-a[i];
	sort(c+1,c+n+1,greater<int>());
	for(int i=1;i<=n;i++) c[i]+=c[i-1]; //c[k]即前k大的b[i]-a[i]值之和
	scanf("%lld",&m);
	while(m--){
		int p,q;scanf("%lld%lld",&p,&q);
		int x,y;
		int d=exgcd(p,q,x,y);
		if(n%d){puts("-1");continue;} //裴蜀定理 
		x*=n/d,y*=n/d;
		int dx=q/d,dy=p/d;
		int mn,mx,l,r;
		mn=(y%dy+dy)%dy;
		x=(x%dx+dx)%dx;
		mx=(n-p*x)/q;
		if(mn>mx){puts("-1");continue;} //y无自然数解
		l=0,r=(mx-mn)/dy;
		while(r-l>2){
			int mid1=l+(r-l)/3,mid2=r-(r-l)/3;
			if(c[f(mid1)]<=c[f(mid2)]) l=mid1;
			else r=mid2;
		}
		int ans=-INF;
		for(int i=l;i<=r;i++) ans=max(ans,c[f(i)]); //整数三分
		printf("%lld\n",sum+ans);
	}
	return 0;
}
```

# The End


---

## 作者：Deft_t (赞：3)

## 思路
扩展欧几里德 $+$ 贪心  
设 $x_0$ 为最小选择辣椒的包数（注意是商店里的包装个数，实际辣椒份数需乘上 $x_j$ ）。   
令 $A = x_j,B = y_j$，$g$ 表示 $\gcd(x_j,y_j)$。  
可以根据题意列出一个二元一次方程：
$$A \times x + B \times y = n$$
如果方程无解，即 $n \bmod g \ne 0$，则输出 $-1$。  
先使用扩展欧几里德求出 $x$ 的**最小**非负整数解即为 $x_0$。
此时若 $A \times x_0 > n$ 则不存在 $x$ 和 $y$ 都不为负数的一组解，输出 $-1$。  
再根据通解公式 $ x = x_0+ \frac{B}{g} \times t$ 求出 $x$ 的**最大**非负整数解。因为辣椒份数不会超过 $n$，可以列出不等式 $A \times (x_0 + \frac{B}{g} \times t) \le n$。计算可得 $x$ 取到合法最大解时，$t$ 的合法最大值为 $\lfloor (n-x0 \times A) \div ( \frac{B}{g} \times A) \rfloor$。另外，显然 $t$ 的最小取值为 $0$。  
令 $[l,r]$ 表示上面求出的 $t$ 的合法取值范围，接下来把 $t$ 的范围代入通解公式后就可以求出辣椒**包数**的合法最小和最大值，即 $x_0+l \times  \frac{B}{g} $ 和 $x_0+r \times  \frac{B}{g} $。乘上 $A$ 即为辣椒**份数**的最小值 $L = A \times (x_0+l \times  \frac{B}{g})$ 和最大值 $R = A \times (x_0+r \times  \frac{B}{g} )$。  
接下来考虑什么时候能取到最优解，可以贪心，由题意可知当前选取了 $X$ 份辣椒的话，剩下的 $n-X$ 份就都是胡椒。把 $n$ 道菜按照 $d_i = a_i-b_i$ 从大到小排序，计算 $d_i$ 的前缀和 $p_i$。每一项 $p_i$ 加上所有 $b_i$ 的总和之后，就是取 $i$ 份辣椒时的最大美味度。此时枚举 $1$ 到 $n$ 可以找到 $i=mx$ 时取到最优解，但是 $mx$ 的取值不一定合法。
发现随着 $i$ 增大最大美味度在 $mx$ 时最大，接下来随着 $i$ 的增大最大美味度减小，由此可以发现这是一个单峰函数，此时可以考虑三分。但实际上只需要分类讨论求出离 $mx$ 最近的合法解即可。具体步骤见代码。  
注意：此题使用 cin 会超时。  
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll exgcd(ll a,ll b,ll &x,ll &y){
	if(b==0){
		x = 1;
		y = 0;
		return a; 
	}
	ll g = exgcd(b,a%b,x,y);
	ll t = x;
	x = y;
	y = t-a/b*y;
	return g;
}
ll a,b,d[3000005],p[300005];
int main(){
	int n,m;
	cin>>n;
	ll sumB = 0;
	for(int i = 1;i <= n;i++){
		scanf("%lld%lld",&a,&b);
		sumB += b;
		d[i] = a-b;
	}
	sort(d+1,d+n+1,greater<ll>());
	p[0] = sumB;
	int mx = 0;
	for(int i = 1;i <= n;i++){
		p[i] = p[i-1]+d[i];
		if(p[i]>p[mx]) mx = i;
	}
	cin>>m;
	ll A,B;
	while(m--){
		scanf("%lld%lld",&A,&B);
		ll x0,y0;
		ll g = exgcd(A,B,x0,y0);
		//x = x0+b/gcd * t 
		x0 *= n/g;
		ll kx = B/g;
		x0 = ((x0%kx)+kx)%kx;
		if(n%g!=0 || x0*A>n){
			puts("-1");
			continue;
		}
		ll l = 0,r = (n-x0*A)/(kx*A);//t的范围 
		ll L = A*(x0+l*kx),R = A*(x0+r*kx);
		ll ans;
		if(R <= mx) ans = p[R];
		else if(L >= mx) ans = p[L];
		else{
			// A*(x0+kx*t) <= mx 
			ll t1 = (mx-A*x0)/(kx*A);
			ll t2 = min(r,t1+1);
			ans = max(p[A*(x0+t1*kx)],p[A*(x0+t2*kx)]);	
		}
		cout<<ans<<endl;
	}
	
	return 0;
}
/*
a*x0 + b*y0 = gcd
a*x + b*y = gcd
a*(x-x0) = b*(y0-y);
a/gcd*(x-x0) = b/gcd*(y0-y)
x = x0+b/gcd * t
y = y0-a/gcd * t 
*/
```


---

## 作者：hcywoi (赞：1)

[Red-Black Pepper](https://www.luogu.com.cn/problem/CF1728E)。

先将该问题弱化，假设要选 $a$ 个红辣椒，$b$ 个黑辣椒那么最大美味值是多少？

假设我们将 $b$ 个黑辣椒搞成红辣椒，那么就为 $\sum\limits_{i=1}^{n}a_i$。

对于一个 $i$，如果将 $a_i\to b_i$，那么贡献值为 $b_i-a_i$。

令 $q\in\{b_i-a_i\}(1\le i\le n)$，假设 $q$ 以按从大到小排序。

则选 $a$ 个红辣椒，$b$ 个黑辣椒的最大美味值为 $\sum\limits_{i=1}^{n}a_i+\sum\limits_{i=1}^{k}q_i$。

---

然后考虑原问题。

最优解一定是在这两个位置：

我们令 $t$ 为第一个 $q_t < 0$ 的位置。

1. 在 $t$ 前面（不包括 $t$）的能取到的黑辣椒的最大位置。
2. 在 $t$ 后面（包括 $t$）的能取到的黑辣椒的最小位置。

实现：

就是先用 exgcd 求出 $ax_i+by_i=n$ 的一组解，然后根据通解公式求出上述的两个位置。

[代码](https://codeforces.com/contest/1728/submission/191212039)。

---

## 作者：DaiRuiChen007 (赞：1)

# CF1728E 题解



## 思路分析

首先可以用一个简单贪心预处理出恰好使用 $i$ 个红胡椒时的答案 $w_i$。

注意到 $w_i$ 是单峰的所以我们只需要找到最接近峰值的解。

首先显然可以通过 ExGcd 算出一组解 $(p,q)$ 使得 $px+qy=n$，那么所有的 $(px,qy)$ 都应该可以表示成 $(p+k\times\operatorname{lcm}(x,y),q-k\times\operatorname{lcm}(x,y))$，其中 $k\in\mathbb{Z}$。

那么我们设峰值为 $w_t$，那么立刻得到最优的 $k$ 应该为 $\dfrac{w-p}{\operatorname{lcm}(x,y)}$，又因为 $k\in\mathbb Z$，所以我们只需要用 $\left\lfloor k\right\rfloor$ 和 $\left\lceil k\right\rceil$ 带入计算即可，注意此时的 $p+k\times \operatorname{lcm}(x,y)$ 应该只在 $[0,n]$ 范围内。

时间复杂度 $\Theta(n\log n+m\log x)$。

## 代码呈现

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=3e5+1;
int a[MAXN],b[MAXN],w[MAXN];
inline int exgcd(int a,int b,int &x,int &y) {
	if(!b) {
		x=1,y=0;
		return a;
	}
	int gcd=exgcd(b,a%b,x,y),f=x;
	x=y,y=f-(a/b)*y;
	return gcd;
}
signed main() {
	int n,q,ch=0,sum=0;
	scanf("%lld",&n);
	for(int i=1;i<=n;++i) scanf("%lld%lld",&a[i],&b[i]);
	vector <int> d;
	for(int i=1;i<=n;++i) sum+=b[i],d.push_back(b[i]-a[i]);
	sort(d.begin(),d.end());
	w[0]=sum;
	for(int i=1;i<=n;++i) {
		sum-=d[i-1];
		w[i]=sum;
		if(w[i]>w[ch]) ch=i;
	}
	scanf("%lld",&q);
	while(q--) {
		int x,y,p,q,ret=-1;
		scanf("%lld%lld",&x,&y);
		int gcd=exgcd(x,y,p,q);
		if(n%gcd!=0) {
			puts("-1");
			continue;
		}
		p*=n/gcd,q*=n/gcd;
		int lcm=x*y/gcd;
		double k=(double)(ch-x*p)/lcm;
		int f1=x*p+floor(k)*lcm,f2=x*p+ceil(k)*lcm;
		if(0<=f1&&f1<=n) ret=max(ret,w[f1]);
		if(0<=f2&&f2<=n) ret=max(ret,w[f2]);
		printf("%lld\n",ret);
	}
} 
```



---

---

## 作者：youdu666 (赞：0)

思路：贪心

发现题解区大部分都是用扩展欧几里得算法做的，我提供一个纯贪心做法，可能有点卡常，虽然跑不满，但是复杂度是 $O(\operatorname d(n)\times n\log n)$（$\operatorname d(n)$ 表示 $1-n$ 中每个数因数个数的平均数）的。

发现红辣椒数量固定的情况下，获得的价值亦是固定的，可以先预处理求出。求法就是一开始钦定所有都选黑辣椒，然后把一道菜黑辣椒换成红辣椒的贡献就是这道菜红辣椒的价值减去黑辣椒的价值，把这个排个序依次替换即可。

把 $1 - n$ 中所有数字的因数计算出来，然后把所有询问中的 $x$ 拿出来，所有相同的 $x$ 放在一起枚举选几次红辣椒，这个东西叫调和级数，可以证明大约是 $O(n\log n)$ 的。枚举完了红辣椒就枚举剩余的黑辣椒的因数，来更新答案。

代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=3e5+5;
int n;
struct node{
	int x,y;
}a[N],s[N];
int b[N],ans[N];
int f[N],m;//有i个红辣椒时的答案
bool cmp(int a,int b){return a>b;}
int mp[N];
vector<int> v[N],pm[N];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		for(int j=1;j*j<=i;j++)if(i%j==0){
			pm[i].emplace_back(j);
			if(j*j!=i)pm[i].emplace_back(i/j);
		}
		pm[i].shrink_to_fit();
	}
	int sum=0;
	for(int i=1;i<=n;i++)cin>>a[i].x>>a[i].y,sum+=a[i].y,b[i]=a[i].x-a[i].y;
	sort(b+1,b+n+1,cmp);
	for(int i=0;i<=n;i++){
		if(i)sum+=b[i];
		f[i]=sum;
	}
	cin>>m;
	for(int i=1;i<=m;i++){
		cin>>s[i].x>>s[i].y;
		v[s[i].x].emplace_back(i);
	}
	for(int i=1;i<=n;i++){
		if(v[i].empty())continue;
		for(auto j:v[i])mp[s[j].y]=-1;
		int bs=-1;
		for(int j=0;j*i<=n;j++){
			int p=f[j*i],lst=n-j*i;
			if(not lst){
				bs=max(bs,p);
				continue;
			}
			for(auto u:pm[lst])mp[u]=max(mp[u],p);
		}
		for(auto j:v[i])ans[j]=max(mp[s[j].y],bs);
	}
	for(int i=1;i<=m;i++)cout<<ans[i]<<"\n";
}
```

---

## 作者：ifffer_2137 (赞：0)

小清新数论题。
### 题意
有 $n$ 道菜，第 $i$ 道菜加红辣椒美味度 $a_i$，加黑辣椒美味度 $b_i$。一道菜只能加一种辣椒，**必须加且只能加**一份。

现在询问 $m$ 次，每次给出 $x,y$ 表示一包红辣椒 $x$ 份，一包黑辣椒 $y$ 份，要求整包整包用，不允许浪费任何一份辣椒，求美味度最大和，或报告无解。
### 分析
本质相当于解 $px+qy=n$ 的不定方程，首先裴蜀定理判掉无解。

然后你考虑 exgcd 求出通解以后怎么算最大值，显然可以贪：钦定刚开始全选 $b_i$，把所有菜按照 $a_i-b_i$ 降序排序，这样选了 $x$ 份红辣椒就是这个序列的前缀 $x$ 项和。

然后容易发现这个前缀和是个单峰，所以直接算一下最接近 $\max$ 的那个位置两边的取值即可。时间复杂度 $O(n\log n)$。
### 代码

```cpp
//From: ifffer_2137
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define inf 1e18
#define eb emplace_back
#define pii pair<int,int>
#define mkpr make_pair
#define fir first
#define sec second
inline int read(){
	char ch=getchar();int x=0,w=1;
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+ch-48,ch=getchar();return w==1?x:-x;
}
const int maxn=3e5+5;
int n,m,S,M;
pii a[maxn];
int exgcd(int a,int b,int &X,int &Y){
	if(!b){X=1,Y=0;return a;}
	int g=exgcd(b,a%b,X,Y);
	int t=(X-(a/b)*Y);
	X=Y,Y=t;
	return g; 
}
signed main(){
	#ifndef ONLINE_JUDGE
		assert(freopen("data.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	cin.tie(0),cout.tie(0);
	n=read();
	for(int i=1;i<=n;i++){
		a[i].fir=read(),a[i].sec=read();
		S+=a[i].sec,a[i].fir-=a[i].sec;
	}
	sort(a+1,a+n+1,[&](pii x,pii y){return x.fir>y.fir;});
	M=n+1;for(int i=1;i<=n;i++) if(a[i].fir<0){M=i-1;break;}
	for(int i=1;i<=n;i++) a[i].fir+=a[i-1].fir;
	m=read();
	while(m--){
		int x=read(),y=read(),X,Y;
		int G=exgcd(x,y,X,Y),L=x/G*y;
		if(n%G){
			cout<<-1<<'\n';
			continue;
		}
		X*=n/G*x,Y*=n/G*y;
		if(X<0){
			int t=((-X+L-1)/L)*L;
			X+=t,Y-=t;
		}else{
			int t=(X/L)*L;
			X-=t,Y+=t;
		}
		if(X<0||X>n||Y<0||Y>n){
			cout<<-1<<'\n';
			continue;
		}
		if(M==n+1){
			cout<<S+a[X+((n-X)/L)*L].fir<<'\n';
			continue;
		}
		int ans=-inf;
		if(X<=M) ans=max(ans,a[X+((M-X)/L)*L].fir);
		else ans=max(ans,a[X].fir);
		if(X<=M&&X+((M+L-X)/L)*L<=n) ans=max(ans,a[X+((M+L-X)/L)*L].fir);
		cout<<ans+S<<'\n';
	}
	return 0;
}
```

---

