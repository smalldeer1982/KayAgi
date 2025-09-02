# Gosha is hunting

## 题目描述

Gosha is hunting. His goal is to catch as many Pokemons as possible. Gosha has $ a $ Poke Balls and $ b $ Ultra Balls. There are $ n $ Pokemons. They are numbered $ 1 $ through $ n $ . Gosha knows that if he throws a Poke Ball at the $ i $ -th Pokemon he catches it with probability $ p_{i} $ . If he throws an Ultra Ball at the $ i $ -th Pokemon he catches it with probability $ u_{i} $ . He can throw at most one Ball of each type at any Pokemon.

The hunting proceeds as follows: at first, Gosha chooses no more than $ a $ Pokemons at which he will throw Poke Balls and no more than $ b $ Pokemons at which he will throw Ultra Balls. After that, he throws the chosen Balls at the chosen Pokemons. If he throws both Ultra Ball and Poke Ball at some Pokemon, he is caught if and only if he is caught by any of these Balls. The outcome of a throw doesn't depend on the other throws.

Gosha would like to know what is the expected number of the Pokemons he catches if he acts in an optimal way. In other words, he would like to know the maximum possible expected number of Pokemons can catch.

## 样例 #1

### 输入

```
3 2 2
1.000 0.000 0.500
0.000 1.000 0.500
```

### 输出

```
2.75
```

## 样例 #2

### 输入

```
4 1 3
0.100 0.500 0.500 0.600
0.100 0.500 0.900 0.400
```

### 输出

```
2.16
```

## 样例 #3

### 输入

```
3 2 0
0.412 0.198 0.599
0.612 0.987 0.443
```

### 输出

```
1.011```

# 题解

## 作者：panyf (赞：50)

首先有一个 $O(n^2\log n)$ 的做法，就是二分斜率 $k$，然后每用一个 A 类球答案就减 $k$，dp 求出 B 类球取 $b$ 个的答案。正确性和实现可以参考其他题解。

考虑每个位置的四种选择：

1. 用 A 和 B，答案加 $p+u-pu-k$

1. 用 B，答案加 $u-k$

1. 用 A，答案加 $p$

1. 都不用，答案加 $0$。

考虑一个位置从不用 B 变成用 B，答案的增加量就是 $x=\max(p+u-pu-k,p)-\max(u-k,0)$，对 $x$ 从大到小排序，取前 $b$ 个即可。

可以分四种情况归并省掉排序，优化到 $O(n\log n)$。

$O(n\log ^2 n)$ 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
enum{N=2009};
double ans,p[N],u[N];
int n,a,b;
struct T{
	double x;
	int a0,a1;
}t[N];
bool chk(double k){
	int i,c=0;
	ans=0;
	for(i=1;i<=n;++i){
		if(p[i]>p[i]+u[i]-p[i]*u[i]-k)t[i].a1=0,t[i].x=p[i];
		else t[i].a1=1,t[i].x=p[i]+u[i]-p[i]*u[i]-k;
		if(0>u[i]-k)t[i].a0=0;
		else t[i].a0=1,t[i].x-=u[i]-k,ans+=u[i]-k;
	}
	sort(t+1,t+n+1,[](T a,T b){return a.x>b.x;});
	for(i=1;i<=a;++i)c+=t[i].a1,ans+=t[i].x;
	for(;i<=n;++i)c+=t[i].a0;
	return c<b;
}
int main(){ios::sync_with_stdio(0);cin.tie(0);
	double l=0,r=1,m;
	int i;
	cin>>n>>a>>b;
	for(i=1;i<=n;++i)cin>>p[i];
	for(i=1;i<=n;++i)cin>>u[i];
	for(i=1;i<77;++i){
		m=(l+r)/2;
		if(chk(m))r=m;else l=m;
	}
	cout<<fixed<<setprecision(9)<<ans+b*m;
}
```
暂时能过讨论区所有 hack 数据。

---

## 作者：Tyher (赞：34)

#### 最大费用最大流。
匹配问题，考虑费用流。
 
先考虑一下每个神奇宝贝球的贡献：

不用，贡献为$0$

只用一个$A$球，贡献为$P_a$

只用一个$B$球，贡献为$P_b$

都用，贡献为$1-(1-P_a)*(1-P_b)$

也就是用总期望减去都失败的期望。

然后考虑怎么连边。

新建$A$,$B$两个点限制球的个数。

连$S$到$A$，流量$a$，费用$0$，连$S$到$B$，流量$b$，费用$0$

连$A$到$i$，流量$1$，费用$P_a$，连$B$到$i$，流量$1$，费用$P_b$。

连$i$到$t$，流量$1$，费用$0$。

现在考虑怎么减去都用多出来的贡献，化减一下。

原式子$$P=1-(1-P_a)*(1-P_b)$$
 $$=1-1+P_a+P_b-P_a*P_b=P_a+P_b-P_a*P_b$$

注意到$P_a,P_b$的贡献已经算进去了，所以连$i$到$t$，流量$1$，费用$-P_a*P_b$。

做最大费用最大流即可，剩下的都是套模板了。

注意精度问题，~~调了好久~~，我设的$eps$为$1e-10$

 ~~贪心题单里面混进来了一道费用流流~~
 
 代码就不贴了，都是板子

---

## 作者：2018ljw (赞：14)

$O(n\log n)$ 的做法！

首先有一个非常 naive 的 $O(n^3)$ 的动态规划，但由于转移式子很没有前途，所以我们直接忽略。

考虑费用流做法。源点向两种球连边，流量 $1$ 费用 $0$，两种球向每个单位连边，流量 $1$ 费用 $p_i$ 或 $q_i$。每个单位向汇点连边，流量 $1$ 费用 $0$ 和流量 $1$ 费用 $-p_iq_i$ 各一条。

这种做法下，最大流为 $O(n)$ 级别，边数与 $n$ 同阶，总复杂度 $O(n^3)$ 无法通过。

但关注到模型比较单纯，所以可以考虑模拟费用流，每次求增广路就等价于找出图中的一条最长路。

由于存在退流操作，问题可能看起来比较复杂。但仔细考察下增广路的基本性质与形态，可以将问题化简。同时，由于源点到两种球的费用均为 $0$，可以转化为暴力枚举增广路的起点。

以下记 $a,b$ 为两种球在网络流建模中对应的点，$t$ 为汇点。

考察图和增广路的性质：

1. 不考虑汇点时，图是一个二分图，其中左半只有两个点。
2. 增广路是从二分图左半出发，到 $t$ 结束的**简单路径**。

所以不难发现，在一条增广路中，**退流操作至多会进行一次**。如此一来，情况数便少了很多。

对于一个点，若其已经被增广一次，那么第二次增广时，其通往汇点的边权会改变。所以，我们将所有点分为四大类：

1. 未被增广过，用 $00$ 表示。
2. 只被 $a$ 增广过，用 $01$ 表示。
3. 只被 $b$ 增广过，用 $10$ 表示。
4. 被 $a,b$ 增广过，用 $11$ 表示。

同时我们记录 $e_{i,1}=p_i,e_{i,2}=q_i,e_{i,3}=p_i\times q_i$。

接下来就是暴力大分讨了。

1. $a\to x\to T$。

当 $x$ 为 $00$ 类点时，增广路长度为 $e_{x,1}$。

当 $x$ 为 $10$ 类点时，增广路长度为 $e_{x,1}-e_{x,3}$。

2. $b\to x\to T$。

当 $x$ 为 $00$ 类点时，增广路长度为 $e_{x,2}$。

当 $x$ 为 $01$ 类点时，增广路长度为 $e_{x,2}-e_{x,3}$。

3. $a\to x\to b\to y\to T$。

此时 $x$ 必须为 $10$ 类点。

对 $x$ 的退流操作的边权和为 $e_{x,1}-e_{x,2}$。

当 $y$ 为 $00$ 类点时，增广路长度为 $e_{x,1}-e_{x,2}+e_{y,2}$。

当 $y$ 为 $01$ 类点时，增广路长度为 $e_{x,1}-e_{x,2}+e_{y,2}-e_{y,3}$。

4. $b\to x\to a\to y\to T$。

此时 $x$ 必须为 $01$ 类点。

对 $x$ 的退流操作的边权和为 $e_{x,2}-e_{x,1}$。

当 $y$ 为 $00$ 类点时，增广路长度为 $e_{x,2}-e_{x,1}+e_{y,1}$。

当 $y$ 为 $10$ 类点时，增广路长度为 $e_{x,2}-e_{x,1}+e_{y,1}-e_{y,3}$。

然后考虑这 $8$ 种情况分别需要维护什么。

1. $00$ 类点的 $e_{x,1}$ 和 $e_{x,2}$ 的 $\max$。
2. $01$ 类点的 $e_{x,2}-e_{x,1}$ 和 $e_{x,2}-e_{x,3}$ 的 $\max$。
3. $10$ 类点的 $e_{x,1}-e_{x,2}$ 和 $e_{x,1}-e_{x,3}$ 的 $\max$。

开六个堆维护这六项，每次增广前弹掉堆顶类型不合法的元素即可。

至多增广 $2n$ 次，复杂度 $O(n\log n)$。

总代码如下，其中为了状压表示方便，代码中的 $01$ 和 $10$ 两类点和文字部分是反过来的。

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define mp make_pair
#define fs(x) x.top().first
#define sd(x) x.top().second
const int inf=1e9;
using namespace std;
int n,m,k,tp[2001];
double p[2001],q[2001];
double e1[2001],e2[2001],e3[2001];
priority_queue<pair<double,int> >w[3];
// 00 e1max 01 e1-e3max 10 e2-e3max
priority_queue<pair<double,int> >ww[3];
// 00 e2max 01 e1-e2max 10 e2-e1max
void upd(){
	int i;
	for(i=0;i<=2;i++){
		while(w[i].size()){
			int x=sd(w[i]);
			if(tp[x]!=i)w[i].pop();
			else break;
		}
		while(ww[i].size()){
			int x=sd(ww[i]);
			if(tp[x]!=i)ww[i].pop();
			else break;
		}
	}
}
void ins(int x){
	if(tp[x]==0){
		w[0].push(mp(e1[x],x));
		ww[0].push(mp(e2[x],x));
	}
	if(tp[x]==1){
		w[1].push(mp(e1[x]-e3[x],x));
		ww[1].push(mp(e1[x]-e2[x],x));
	}
	if(tp[x]==2){
		w[2].push(mp(e2[x]-e3[x],x));
		ww[2].push(mp(e2[x]-e1[x],x));
	}
}
int main(){
	int i;
	double res=0;
	scanf("%d%d%d",&n,&m,&k);
	for(i=1;i<=n;i++)scanf("%lf",&p[i]);
	for(i=1;i<=n;i++)scanf("%lf",&q[i]);
	for(i=1;i<=n;i++){
		e1[i]=p[i];
		e2[i]=q[i];
		e3[i]=p[i]*q[i];
		ins(i);
	}
	while(m||k){
		double dx=-inf;
		int x,y,s;
		upd();
		if(m){
			if(w[0].size()){
				int g=sd(w[0]);
				if(e1[g]>dx)dx=e1[g],x=g,y=-1,s=0;
			}
			if(w[1].size()){
				int g=sd(w[1]);
				if(e1[g]-e3[g]>dx)dx=e1[g]-e3[g],x=g,y=-1,s=0;
				g=sd(ww[1]);
				double ss=e1[g]-e2[g];
				if(w[0].size()){
					int r=sd(ww[0]);
					if(ss+e2[r]>dx)dx=ss+e2[r],x=g,y=r,s=0;
				}
				if(w[2].size()){
					int r=sd(w[2]);
					if(ss+e2[r]-e3[r]>dx)dx=ss+e2[r]-e3[r],x=g,y=r,s=0;
				}
			}
		}
		if(k){
			if(w[0].size()){
				int g=sd(ww[0]);
				if(e2[g]>dx)dx=e2[g],x=g,y=-1,s=1;
			}
			if(w[2].size()){
				int g=sd(w[2]);
				if(e2[g]-e3[g]>dx)dx=e2[g]-e3[g],x=g,y=-1,s=1;
				g=sd(ww[2]);
				double ss=e2[g]-e1[g];
				if(w[0].size()){
					int r=sd(w[0]);
					if(ss+e1[r]>dx)dx=ss+e1[r],x=g,y=r,s=1;
				}
				if(w[1].size()){
					int r=sd(w[1]);
					if(ss+e1[r]-e3[r]>dx)dx=ss+e1[r]-e3[r],x=g,y=r,s=1;
				}
			}
		}
		if(dx<0)break;
		res+=dx;
		if(!s){
			if(!~y){
				tp[x]+=2;
				ins(x);
			}
			else{
				tp[x]=2;
				tp[y]+=1;
				ins(x);ins(y);
			}
			m--;
		}
		else{
			if(!~y){
				tp[x]+=1;
				ins(x);
			}
			else{
				tp[x]=1;
				tp[y]+=2;
				ins(x);ins(y);
			}
			k--;
		}
	}
	printf("%.10f",res);
}
```

---

## 作者：蒟蒻丁 (赞：14)

~~由于刚学带权二分，所以考虑带权二分~~  
对于dp优化型题目，首先写出普通dp方程，$f_{i,a,b}$表示前i个宝可梦用a个精灵球和b个超级球期望能抓住几只
$$f_{i,a,b}=max(f_{i-1,a-1,b}+p_{i},f_{i-1,a,b-1}+q_{i},f_{i-1,a-1,b-1}+q_{i} * p_{i}-q_{i}*p_{i})$$
我们发现一只宝可梦用一只球会比两只球有性价比(毕竟还要减$p[i]*q[i]$ (注意两只球若都抓住只贡献一次)）)

所以当$i,a$固定时，关于$b$的函数$f_{i,a,b}$是上凸的，于是我们脑中就有了一个最优解图像：
![](https://s3.ax1x.com/2021/01/18/scNsW6.png)
然而这只是脑中的，我们要想办法根据他的性质把他还原出来  
这里就有一个针对凸函数的办法：引一条直线使该直线与函数相切，这个函数也是由一小节一小节线段构成的(毕竟大家都是整数)，当相切时实际上引的直线就是那一条线段比如：
![](https://s3.ax1x.com/2021/01/18/scUSf0.png)  
而我们想要得到的是在正确函数上当$x=b$时的取值，所以我们不断调整斜率，因为该函数是凸函数，当截距最大时，我们得到的就是最优函数图像最右端的部分，我们~~口胡~~设一个函数
$$f'(x)=f(x)+kx$$
这就是我们拿来还原图像的直线($f'(x)$为最优$f_{n,a,x}$)，变形一下
$$f(x)=f'(x)-kx$$
这下我们表示出了截距，我们要想办法让截距最大  
发现$kx$很像一个权值，所以我们让超级球的收益变为$q[i]-k$，然后贪心做就好，细节可以看代码(作死用了提前声明请见谅)
```
#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
#define ld double
#define mid ((l+r)/2)
using namespace std;
ll n,a,b;
ld p[10001],q[10001],f[2010][2010],cnt[2101][2101];

bool check_dp(ld sam);

int main(){
	scanf("%lld%lld%lld",&n,&a,&b);
	for(ll i=1;i<=n;i++)scanf("%lf",&p[i]);
	for(ll i=1;i<=n;i++)scanf("%lf",&q[i]);
	ld l=0,r=1,ans=1;
	for(ll o=1;o<=60;o++){
		if(check_dp(mid))ans=mid,r=mid-1;
		else l=mid+1;
	}
	ans=f[n][a]+ans*b;
	printf("%.5lf\n",ans);
}

bool check_dp(ld sam){
	memset(f,0,sizeof f);
	memset(cnt,0,sizeof cnt);
	ll i,j;
	for(i=1;i<=n;i++){
		for(j=0;j<=a;j++){
			cnt[i][j]=cnt[i-1][j];
			f[i][j]=f[i-1][j];
			if(j!=0&&f[i-1][j-1]+p[i]>f[i][j]){
				cnt[i][j]=cnt[i-1][j-1];
				f[i][j]=p[i]+f[i-1][j-1];
			}
			if(f[i-1][j]+q[i]-sam>f[i][j]){
				cnt[i][j]=cnt[i-1][j]+1;
				f[i][j]=f[i-1][j]+q[i]-sam;
			}
			if(j!=0&&f[i-1][j-1]+p[i]+q[i]-q[i]*p[i]-sam>f[i][j]){
				cnt[i][j]=cnt[i-1][j-1]+1;
				f[i][j]=f[i-1][j-1]+p[i]+q[i]-q[i]*p[i]-sam;
			}
		}
	}
	return cnt[n][a]<=b;
}
```

---

## 作者：0x3F (赞：9)

这是一种我口胡的 wqs 二分的新的实现方法。

假设我们要最小化答案（虽然这道题不是），wqs 二分，就是你要求一个下凸包上 $x=x_0$ 位置的值，但是你不能直接求，你唯一可以做的事是求凸包与斜率为 $k$ 的直线的切点。

一般的 wqs 二分的思路是：根据这个切点的 $x$ 坐标是大了还是小了，来调整 $k$ 的值。这样有一个问题：如果凸包上有三点共线，那么切点的位置不是唯一的。一维的情况下，可以只选取 $x$ 坐标最小/最大的切点，而二维的情况下，重合的可能是一个平面，所以不能这么做。

那么怎么办呢？

考虑这条切线和直线 $x=x_0$ 的交点，这个交点显然是唯一的。它的 $y$ 坐标只可能小于或等于答案，而绝不会大于答案，取等号当且仅当切线恰好经过要求的点。同时，这个交点的 $y$ 坐标关于 $k$ 的函数 $y(k)$ 是上凸的。

见图。

![](https://s11.ax1x.com/2024/01/22/pFZnrY4.png)

三分 $k$ 求其最大值即可。~~不如叫 wqs 三分~~

如果要最大化答案，或者高维的情况，是类似地，就不再赘述了。

这是这道题的代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int _ = 2e3 + 10;
const long double eps = 1e-10L;
int n, a, b;
long double p[_], q[_];
inline long double calcxy(long double x, long double y) {
	long double sum = a * x + b * y;
	for (int i = 1; i <= n; i++) {
		sum += max({0.0L, p[i] - x, q[i] - y, p[i] + q[i] - p[i] * q[i] - x - y});
	}
	return sum;
}
inline long double calcx(long double x) {
	long double l = -1e4L;
	long double r = 1e4L;
	while (r - l > eps) {
		long double m1 = (l * 2 + r) / 3;
		long double m2 = (l + r * 2) / 3;
		if (calcxy(x, m1) > calcxy(x, m2)) {
			l = m1;
		} else {
			r = m2;
		}
	}
	return calcxy(x, (l + r) / 2);
}
inline long double calc(void) {
	long double l = -1e4L;
	long double r = 1e4L;
	while (r - l > eps) {
		long double m1 = (l * 2 + r) / 3;
		long double m2 = (l + r * 2) / 3;
		if (calcx(m1) > calcx(m2)) {
			l = m1;
		} else {
			r = m2;
		}
	}
	return calcx((l + r) / 2);
}
int main() {
	cin >> n >> a >> b;
	for (int i = 1; i <= n; i++) {
		cin >> p[i];
	}
	for (int i = 1; i <= n; i++) {
		cin >> q[i];
	}
	cout << fixed << setprecision(20) << calc() << endl;
	return 0;
}
```

---

## 作者：wrpwrp (赞：7)

[题目链接](https://www.luogu.com.cn/problem/CF739E)  
[一刀999](https://www.cnblogs.com/HN-wrp/p/13086688.html)  
首先一个很显然的想法就是直接$DP$

设$f[i][j][k]$表示抓前$i$个神奇宝贝用了$j$个宝贝球和$k$个超级球，有：

$$f[i][j][k] = max (f[i - 1][j - 1][k] + p[i], f[i - 1][j][k - 1] + u[i], f[i - 1][j  - 1][k - 1] + p[i] + u[i] -p[i] * u[i])$$

这样直接转移是$O(n^3)$的。

```c++
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define R register
#define LL long long
const int inf = 0x3f3f3f3f;
const int N = 200 + 5;

inline int read() {
	char a = getchar(); int x = 0,f = 1;
	for(;a > '9' || a < '0';a = getchar()) if(a == '-') f = -1;
	for(;a >= '0' && a <= '9'; a = getchar()) x = x * 10 + a - '0';
	return x * f;
}

int n, a, b;
double p[N], u[N];
double f[N][N][N];

int main() {
	freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	n = read(); a = read(); b = read();
	for(R int i = 1; i <= n; i ++) scanf("%lf", & p[i]);
	for(R int i = 1; i <= n; i ++) scanf("%lf", & u[i]);
	for(R int i = 1; i <= n; i ++) {
		for(R int j = 0; j <= a; j ++)
			for(R int k = 0; k <= b; k ++) {
				f[i][j][k] = f[i - 1][j][k];
				if(j != 0) f[i][j][k] = max(f[i][j][k], f[i - 1][j - 1][k] + p[i]);
				if(k != 0) f[i][j][k] = max(f[i][j][k], f[i - 1][j][k - 1] + u[i]);
				if(j != 0 && k != 0) f[i][j][k] = max(f[i][j][k], f[i - 1][j - 1][k - 1] + p[i] + u[i] - p[i] * u[i]);
			}
	}
	printf("%lf\n", f[n][a][b]);
	return 0;	
}

```

　

考虑优化，打表或者脑补可以发现，当$n, b$固定的时候$f[n][a][i]$是一个下凸的函数，而且最低点是$f[n][a][0]$，其实脑补一下也就知道用的球越多，这个期望肯定越大，所以就有这么个性质。考虑用wqs二分进行优化。对于每一个超级球都带上一个费用，通过二分这个费用来控制宝贝球的使用个数，可以做到$n^2log_2n$ (~~大概的，实际二分多少次看过了就行~~)。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define R register
#define LL long long
const int inf = 0x3f3f3f3f;
const int N = 2000 + 5;

inline int read() {
	char a = getchar(); int x = 0,f = 1;
	for(;a > '9' || a < '0';a = getchar()) if(a == '-') f = -1;
	for(;a >= '0' && a <= '9'; a = getchar()) x = x * 10 + a - '0';
	return x * f;
}

int n, a, b;
double p[N], u[N];
double f[N][N];
int cnt[N][N];

inline bool check(double mid) {
	memset(f, 0, sizeof(f));
	memset(cnt, 0, sizeof(cnt));
	for(R int i = 1; i <= n; i ++) {
		for(R int j = 0; j <= a; j ++) {
			cnt[i][j] = cnt[i - 1][j];
			f[i][j] = f[i - 1][j];
			if(j != 0 && f[i - 1][j - 1] + p[i] >= f[i][j]) {
				f[i][j] = f[i - 1][j - 1] + p[i];
				cnt[i][j] = cnt[i - 1][j - 1];
			}
			if(j != 0 && f[i - 1][j - 1] + u[i] + p[i] - u[i] * p[i] - mid >= f[i][j]) {
				f[i][j] = f[i - 1][j - 1] + u[i] + p[i] - u[i] * p[i] - mid;
				cnt[i][j] = cnt[i - 1][j - 1] + 1;
			}
			if(f[i - 1][j] + u[i] - mid >= f[i][j]) {
				f[i][j] = f[i - 1][j] + u[i] - mid;
				cnt[i][j] = cnt[i - 1][j] + 1;
			}
		}
	}
	return cnt[n][a] <= b;
}


int main() {
	freopen("a.in","r",stdin);
	freopen("b.out","w",stdout);
	n = read(); a = read(); b = read();
	for(R int i = 1; i <= n; i ++) scanf("%lf", & p[i]);
	for(R int i = 1; i <= n; i ++) scanf("%lf", & u[i]);
	double l = 0, r = 1;
	for(R int i = 1; i <= 60; i ++) {
		double mid = (l + r) / 2;
		if(check(mid)) r = mid;
		else l = mid;
	}
	printf("%.5lf\n", f[n][a] + l * b);
	return 0;	
}

```

但是实际上发现，不仅仅对于$b$，$a$也有这个性质，所以可以再套一个$wqs$,二分一个宝贝球的费用，可以做到$nlog_2n^2$（~~这个也是假的~~）

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define R register
#define LL long long
const int inf = 0x3f3f3f3f;
const int N = 2000 + 5;
const double eps = 1e-9;

inline int read() {
	char a = getchar(); int x = 0,f = 1;
	for(;a > '9' || a < '0';a = getchar()) if(a == '-') f = -1;
	for(;a >= '0' && a <= '9'; a = getchar()) x = x * 10 + a - '0';
	return x * f; 
}

int n, a, b;
double p[N], u[N];
double f[N];
int cnt1[N], cnt2[N];

inline bool Check(double v1,double v2) {
	memset(f, 0, sizeof(f));
	memset(cnt1, 0, sizeof(cnt1));
	memset(cnt2, 0, sizeof(cnt2));
	for(R int i = 1;i <= n; i ++) {
		f[i] = f[i - 1];
		cnt1[i] = cnt1[i - 1];
		cnt2[i] = cnt2[i - 1];
		if(f[i - 1] + p[i] - v1 - eps > f[i]) {
			f[i] = f[i - 1] + p[i] - v1;
			cnt1[i] = cnt1[i - 1] + 1;
			cnt2[i] = cnt2[i - 1];
		}
		if(f[i - 1] + u[i] - v2 - eps > f[i]) {
			f[i] = f[i - 1] + u[i] - v2;
			cnt1[i] = cnt1[i - 1];
			cnt2[i] = cnt2[i - 1] + 1;
		}
		if(f[i - 1] + p[i] + u[i] - p[i] * u[i] - v1 - v2 - eps > f[i]) {
			f[i] = f[i - 1] + p[i] + u[i] - p[i] * u[i] - v1 - v2;
			cnt1[i] = cnt1[i - 1] + 1;
			cnt2[i] = cnt2[i - 1] + 1;
		}
	}
	return cnt2[n] <= b;
}

double tl;

inline bool check(double md) {
	double l = 0, r = 1;
	for(R int i = 1; i <= 50; i ++) {
		double mid = (l + r) / 2;
		if(Check(md, mid)) r = mid;
		else l = mid;
	}
	tl = l;
	return cnt1[n] <= a;
}


int main() {
	//freopen("a.in","r",stdin);
	//freopen("b.out","w",stdout);
	n = read(); a = read(); b = read();
	for(R int i = 1; i <= n; i ++) scanf("%lf", & p[i]);
	for(R int i = 1; i <= n; i ++) scanf("%lf", & u[i]);
	double l = 0, r = 1;
	for(R int i = 1; i <= 50; i ++) {
		double mid = (l + r) / 2;
		if(check(mid)) r = mid;
		else l = mid;
	}
	//printf("%d %d\n", cnt1[n], cnt2[n]);
	printf("%.5lf\n", f[n] + l * a + tl * b);
	return 0;	
}
```

但是这个写法有一个巨大的坑点就是会被卡精度，一定要在代码中减去$eps$，这是因为我们要在判断的时候尽量少使用球，这样才可以碰到最优解。要是用了和没有用没有区别的话，不用显然会更加优秀，也是题目所要求的。

---

