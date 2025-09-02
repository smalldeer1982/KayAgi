# Piglet's Birthday

## 题目描述

Piglet has got a birthday today. His friend Winnie the Pooh wants to make the best present for him — a honey pot. Of course Winnie realizes that he won't manage to get the full pot to Piglet. In fact, he is likely to eat all the honey from the pot. And as soon as Winnie planned a snack on is way, the pot should initially have as much honey as possible.

The day before Winnie the Pooh replenished his honey stocks. Winnie-the-Pooh has $ n $ shelves at home, each shelf contains some, perhaps zero number of honey pots. During the day Winnie came to the honey shelves $ q $ times; on the $ i $ -th time he came to some shelf $ u_{i} $ , took from it some pots $ k_{i} $ , tasted the honey from each pot and put all those pots on some shelf $ v_{i} $ . As Winnie chose the pots, he followed his intuition. And that means that among all sets of $ k_{i} $ pots on shelf $ u_{i} $ , he equiprobably chooses one.

Now Winnie remembers all actions he performed with the honey pots. He wants to take to the party the pot he didn't try the day before. For that he must know the mathematical expectation of the number $ m $ of shelves that don't have a single untasted pot. To evaluate his chances better, Winnie-the-Pooh wants to know the value $ m $ after each action he performs.

Your task is to write a program that will find those values for him.

## 样例 #1

### 输入

```
3
2 2 3
5
1 2 1
2 1 2
1 2 2
3 1 1
3 2 2
```

### 输出

```
0.000000000000
0.333333333333
1.000000000000
1.000000000000
2.000000000000
```

# 题解

## 作者：xtx1092515503 (赞：8)

写这篇题解是因为有一个小点我对当前两篇题解里的一个内容有异议。

首先先写做法。

我们可以设$f[i][j]$表示：

橱子$i$，剩了$j$个罐子**没吃过**的概率。

再设$num_i$表示橱子$i$初始罐数，$now_i$表示橱子$i$当前罐数。

则在$f[i][j]$中，必有$j\leq\min(num_i,now_i)$，因为如果从其它地方搬来了罐子，则这些罐子一定是已经被吃过的。

当我们有一次从$u$到$v$搬了$w$个罐子的操作时：

位置$v$的$f$值不会有任何影响——搬来的罐子吃过了。

位置$u$的罐子可以通过排列组合算出来：

$f[u][j]=\dfrac{\sum\limits_{k=j}^{\min(j+w,now_u)}f[u][k]*C_{k}^{k-j}*C_{now_u-k}^{w-(k-j)}}{C_{now_u}^{w}}$

其中，$C_{k}^{k-j}$表示从$k$个没吃过的罐子中选出$k-j$个罐子吃的方案数；$C_{now_u-k}^{w-(k-j)}$表示从$now_u-k$个吃过的罐子中选出$w-(k-j)$个罐子吃的方案数。

然后就是我有异议的地方了：

**似乎题面里也没有规定这个$now_u$最大能到多少吧？**

如果我们考虑极端情况，每次都从一个地方搬$5$个罐子过来，则$now_u$最大可以到$500100$！

而两篇题解里面预处理的$C$数组，都是$1000\times1000$的。

一个极端数据很容易就能卡掉。

我认为这个$C$数组应该预处理成$500100\times5$的，因为$k-j,w-(k-j),w$，这三者都是$\leq5$的。

虽然可能数据并没有卡错误的$C$范围，但是做题还是严谨一点好。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=500100;
int n,num[100100],q,now[100100];
double f[100100][110],C[500500][10],res;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&num[i]),now[i]=num[i],f[i][num[i]]=1,res+=f[i][0];
	for(int i=0;i<=MAXN;i++)C[i][0]=1;
	for(int i=1;i<=MAXN;i++)for(int j=1;j<=min(i,5);j++)C[i][j]=C[i-1][j-1]+C[i-1][j];
	scanf("%d",&q);
	for(int i=1,u,v,w;i<=q;i++){
		scanf("%d%d%d",&u,&v,&w);
		res-=f[u][0];
		for(int j=0;j<=num[u];j++){
			double ans=0;
			for(int k=j;k<=min(j+w,now[u]);k++)ans+=f[u][k]*C[k][k-j]*C[now[u]-k][w-(k-j)];
			f[u][j]=ans/C[now[u]][w];
		}
		res+=f[u][0],now[u]-=w,now[v]+=w;
		printf("%.9lf\n",res);
	}
	return 0;
}
```


---

## 作者：Alex_Wei (赞：3)

> *III. [CF248E Piglet's Birthday](https://www.luogu.com.cn/problem/CF248E)*

一道概率期望好题。

首先，我们发现被搬到 $v$ 货架上的蜜罐一定都是吃过的，与它之前的状态无关，因此对于 $v$ 可以直接看做多了 $k$ 个吃过的蜜罐。

注意到 $a_i$ 和 $k$ 均很小，这启发我们对每个货架 $i$，求出它有 $j$ 个的吃过的蜜罐的概率 $p_{i, j}$，转移直接枚举 $j$ 以及拿走的 $k$ 个蜜罐中有多少个是吃过的。显然系数是组合数的形式。但这样时间复杂度太大，因为一个货架上可能有很多吃过的蜜罐，而且对于 $v$ 而言它的 $f_v$ 还要向左平移 $k$，很麻烦。

考虑换一种状态设计。由于 **没有吃过** 的蜜罐随着操作的进行不会增加，因此不妨设 $j$ 表示有 $j$ 个没吃过蜜罐的概率，这样时间复杂度就被限制在 $\mathcal{O}(na_ik)$，可以通过。

转移方程：枚举拿走了多少个没有吃过的蜜罐 $q(0\leq q \leq k)$，那么对于每个 $j$，有
$$
f_{u, j} \times \dfrac{\binom j q \binom {a_u - j}{k - q}}{\binom{a_u} k}\to f'_{u, j - q}
$$
其中 $a_u$ 是当前货架上蜜罐个数。注意到 $a_u$ 可能很大，达到 $5\times 10 ^ 5$ 的级别，使得预处理组合数的值域过大导致丢失精度（虽然只有 $10 ^ {26}$ 左右）。保险起见，考虑每次都计算一遍组合数，并且一边除一边乘。这会给时间复杂度再乘一个 $k$，但是问题不大。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5, K = 100 + 5;
int n, q, a[N], fc[K];
double ans, f[N][K];
int main() {
	cin >> n;
	for(int i = fc[0] = 1; i <= 5; i++) fc[i] = fc[i - 1] * i;
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]), f[i][a[i]] = 1, ans += !a[i];
	cin >> q;
	for(int i = 1; i <= q; i++) {
		int u, v, k;
		scanf("%d %d %d", &u, &v, &k);
		static double g[K];
		memset(g, 0, sizeof(g)), ans -= f[u][0];
		for(int j = 0; j <= 100; j++) if(f[u][j])
			for(int p = 0; p <= k; p++) {
				if(j < p || a[u] - j < k - p) continue;
				double coef = 1;
				for(int q = 0; q < p; q++) coef = coef * (j - q) / (a[u] - q);
				for(int q = 0; q < k - p; q++) coef = coef * (a[u] - j - q) / (a[u] - p - q);
				g[j - p] += f[u][j] * coef * fc[k] / fc[k - p] / fc[p];
			}
		memcpy(f[u], g, sizeof(g));
		ans += f[u][0], a[u] -= k, a[v] += k;
		printf("%.9lf\n", ans);
	}
    return 0;
}
```

---

## 作者：_wsq_ (赞：0)

这道题打 duel 时被我秒了，然后因为没注意 $u=v$ 的特殊情况导致 WA 了然后没抢过对面。

首先注意到 $k$ 很小，因此可以将一次操作拆成 $k$ 次操作，每次操作只拿一罐。

然后考虑如何统计答案。注意到 $a_i$ 也很小，而每次操作后，这一罐一定是被吃过的，也就是说每个货架上没被吃过的罐子的数量一定是单调不升的，因此考虑直接维护每个货架上每种没被吃过的罐子的数量所对应的概率。对于每次操作，由于这一罐已经被吃过，因此对 $v$ 货架上的概率不会有任何影响；对于 $u$ 货架，只要我们再维护每个货架上罐子的个数，就可以对于每种没被吃过的罐子的数量算出取下被吃过的罐子的概率并进行转移。

具体的，设 $p_{u,i}$ 表示第 $u$ 个货架上没被吃过的罐子的数量为 $i$ 的概率，$num_u$ 表示第 $u$ 个货架上原来罐子的个数，则每次操作有

$$
p_{u,i}\gets\frac{p_{u,i}(num_u-i)+p_{u,i+1}(i+1)}{num_u}
$$

时间复杂度 $O(n+qka_i)$，空间复杂度 $O(na_i)$。

代码：

```cpp
#include<iostream>
#include<iomanip>
using namespace std;
#define maxn 100005
int n,q,a[maxn],num[maxn];
long double ans,p[maxn][105];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		num[i]=a[i];
		p[i][a[i]]=1;
		if(!a[i]){
			ans+=1.0;
		}
	}
	cin>>q;
	for(int i=1;i<=q;i++){
		int u,v,k,kk;
		cin>>u>>v>>k;
		kk=k;
		while(kk--){
			ans-=p[u][0];
			for(int j=1;j<=a[u];j++){
				p[u][j-1]+=p[u][j]*((long double)j/(long double)num[u]);
				p[u][j]-=p[u][j]*((long double)j/(long double)num[u]);
			}
			ans+=p[u][0];
			num[u]--;
		}
		num[v]+=k;
		cout<<fixed<<setprecision(12)<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：RockyYue (赞：0)

#### 248E

  $n$ 个集合，初始第 $i$ 个中有 $a_i$ 元素，每次操作 $(u,v,k)$ 表示从集合 $u$ 中任选 $k$ 个移动到集合 $v$，元素两两不同，每次操作后求满足其中所有元素都被选过的集合数量的期望，$n\le 10^5,0\le a_i\le 100$。

  #### Sol

  - 谨记：题面中任何一个数据范围都是有用的，其可能成为状态设计中的关键。
  - 对于集合 $i$，你知道的是在上一次从 $i$ 中选数的操作之前，移到 $i$ 的元素必然是选过的。在这之前移到 $i$ 的元素只要后续没被移走就是有效的。
  - 所以说确定一个每个集合中元素是否选的状态，只需要知道每次操作选了多少个之前选过的元素，这固然是难于枚举的，于是计算一些概率。
  - 需要记录每个集合中有多少个元素被选过，于是记 $f_{i,j}$ 为，集合 $i$ 中当前时刻有 $j$ 个元素被选过的概率，则答案为 $\sum_{i}f_{i,a_i}$，$a_i$ 随操作动态更新。
  - 对于一次操作 $(u,v,k)$，其影响 $f_u$ 和 $f_v$。
    - 对于 $f_{u,i}$，枚举这次转移走的选过点数量 $j$，则 $f_{u,i}\cdot \frac{\binom{i}{j}\binom{a_u-i}{k-j}}{\binom{a_u}{k}}\stackrel+\longrightarrow f'_{u,i-j}$。
    - 对于 $f_{v,i}$，$f_{v,i}\stackrel=\longrightarrow f'_{v,i+k}$。
  - 目前的问题在于，这样的状态设计可能会很大，第二维的范围并不明确。故改变状态设计，$j$ 表示这一集合中没选过的元素个数，可以将状态控制在 $O(nV)$，同时 $f_v$ 也不用更新。

---

## 作者：Graphcity (赞：0)

首先，根据期望的线性性质，答案等于每一个货架被清空的概率之和。注意到本题的数据范围，$0\le a_i\le 100$，且每次没有被吃掉的蜜罐数量单调不增，可以设 $p_{x,i}$ 表示 $x$ 货架内还剩下 $i$ 个蜜罐的概率。

对于一次操作 $(u,v,k)$，答案的变化仅和货架 $u$ 有关，因为 $v$ 货架内剩余蜜罐数量不变，不影响答案。枚举 $u$ 货架内有多少个新的蜜罐被吃掉了，则有：

$$
p_{x,i}=\sum_{j=i}^{i+k}p_{x,j}\times \frac{\binom{j}{j-i}\binom{sum_x-j}{k-(j-i)}}{\binom{sum_x}{k}}
$$

其中 $sum_x$ 为 $x$ 货架内总的蜜罐数量。注意到 $j-i,k-(j-i),k$ 均在 $[0,5]$ 范围内，而 $sum_x$ 高达 $5\times 10^5$，所以预处理 $\binom{0\dots 5\times 10^5}{0\cdots 5}$ 之内的组合数即可。

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=1e5,Maxk=5e5+120;

inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

int n,m,val[Maxn+5],sum[Maxn+5];
double p[Maxn+5][110],C[Maxk+5][6],ans;

inline void Off(int x,int k)
{
    ans-=p[x][0];
    For(i,0,min(sum[x],100))
    {
        double res=0;
        For(j,i,i+k) if(j<=sum[x])
            res+=p[x][j]*C[j][j-i]*C[sum[x]-j][k-(j-i)]/C[sum[x]][k];
        p[x][i]=res;
    }
    ans+=p[x][0];
}

int main()
{
    n=read(),C[0][0]=1;
    For(i,1,Maxk)
    {
        C[i][0]=1;
        For(j,1,min(i,5)) C[i][j]=C[i-1][j]+C[i-1][j-1];
    }
    For(i,1,n) p[i][val[i]=sum[i]=read()]=1.0;
    For(i,1,n) ans+=p[i][0];
    m=read();
    while(m--)
    {
        int x=read(),y=read(),k=read();
        Off(x,k),sum[x]-=k,sum[y]+=k,printf("%.12lf\n",ans);
    }
    return 0;
}
```

---

## 作者：shao0320 (赞：0)

题意翻译

给定$n$个货架，初始时每个上面有$a[i]$个蜜罐。
有$q$次操作，每次操作形如$u,v,k$，表示从货架$u$上任意选择$k$个蜜罐试吃（吃过的也还能吃），吃完后把这$k$个蜜罐放到$v$货架上去。
每次操作完之后回答所有蜜罐都被试吃过的货架数量的期望。

题解：

方便起见，这个题目可以抽象成：有$n$个位置，最开始第$i$个位置上有$a[i]$个白球，有$Q$次操作，每次从第$u$个位置拿出$k$个**球**染黑并放到$v$位置上。

注意到每个位置的白球不会增加，而且任意时刻每个位置上的球个数是固定的。由于$a[i]\leq100$,因此我们可以设$f[i][j]$表示当前时刻，第$i$个位置上出现$j$个白球的概率。并且维护每个位置上球的总数

对于每次操作，相当于在第$u$个位置上扔掉$k$个球，在往第$v$个位置上扔$k$个黑球。

加入操作好搞，这里重点说下删除操作。

注意到$k\leq5$,因此可以枚举，拿出来白球的数量和还剩下白球的数量。用组合数即可算出该种情况的概率。

最终答案就是每堆上有0个白球的概率之和。

代码
```
#include<iostream>
#include<cstdio>
#include<cstring>
#define N 100005
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
int n,a[N],q,siz[N],fac[N];
double f[N][303],ans,g[505];
double C(int n,int m)
{
	if(!n)return 1.0;
	if(!m)return 1.0;
	double res=1.0;
	for(int i=m;i>=m-n+1;i--)res*=i;
	return res/fac[n];
}
inline void del(int id,int x)
{
	ans-=f[id][0];
	for(int i=0;i<=x;i++)
	{
		for(int j=0;j<=a[id]&&j+x<=siz[id];j++)
		{
			double pro=C(i,i+j)*C(x-i,siz[id]-(j+i))/C(x,siz[id]);
			g[j]+=f[id][j+i]*pro;
		}
	}
	for(int i=0;i<=siz[id];i++)
	{
		f[id][i]=g[i];
		g[i]=0;
	}
	ans+=f[id][0];
	siz[id]-=x;
}
void add(int id,int x)
{
	siz[id]+=x;
}
signed main()
{
	n=read();
	for(int i=1;i<=n;i++)
	{
		siz[i]=a[i]=read();
		f[i][a[i]]=1.0;
	}
	fac[0]=1;
	for(int i=1;i<=10;i++)fac[i]=fac[i-1]*i;
	q=read();
	ans=0.0;
	for(int i=1;i<=n;i++)ans+=f[i][0];
	while(q--)
	{
		int x=read(),y=read(),z=read();
		del(x,z);add(y,z);
		printf("%.12lf\n",ans);
	}
	return 0;
}
/*
3
2 2 3
5
1 2 1
2 1 2
1 2 2
3 1 1
3 2 2
*/
```

---

## 作者：Lumos壹玖贰壹 (赞：0)

### 自古CF出概率DP好题
#### 题目
给定$n$个货架，初始时每个上面有$a[i]$个蜜罐。
有$q$次操作，每次操作形如$u,v,k$，表示从货架$u$上任意选择$k$个蜜罐试吃（吃过的也还能吃），吃完后把这$k$个蜜罐放到$v$货架上去。
每次操作完之后回答所有蜜罐都被试吃过的货架数量的期望。
#### 解析
因为答案只涉及**被试吃过的蜜罐**这一状态，我们不妨把这一状态设进dp状态\
设$f[i][j]$为当前时刻下第i个柜子有j个没被吃的概率，每次操作才会形成转移。\
每次u-->v转移k个。\
考虑更新f[u][j]\
设最开始u柜子有num[u]个蜂蜜，转移前u有now个罐子，p个没被品尝过,则    $f[u][j]$=${\sum_{p=j}^{min(num[u],j+k)}f[u][p]×C_{p}^{p-j}×C_{now-p}^{k-(p-j)}\over C_{now}^{p} }$

然后注意下细节就好了

Code
```
#include<bits/stdc++.h>
#define ri register int
using namespace std;
double f[100005][110],c[500105][10];
int n,now[100005],num[100005],q,u,v,k,t_n=0;
int main(){
	double res=0;
	scanf("%d",&n);
	for(ri i=1;i<=n;i++) scanf("%d",&now[i]),f[i][now[i]]=1,num[i]=now[i],res+=f[i][0];
	scanf("%d",&q);
	c[0][0]=c[1][0]=c[1][1]=1;
	for(ri i=2;i<=500100;i++){
		c[i][0]=1;
		for(ri j=1;j<=min(i,5);j++) c[i][j]=c[i-1][j-1]+c[i-1][j];
	}
	while(q--){
		scanf("%d%d%d",&u,&v,&k);
		res-=f[u][0];
		for(ri j=0;j<=num[u];j++){
			double ans=0;
			for(int p=j;p<=min(now[u],j+k);p++) ans+=f[u][p]*c[p][p-j]*c[now[u]-p][k-p+j];				   		  		          f[u][j]=ans/c[now[u]][k];
		}
		res+=f[u][0]; 
		printf("%.9lf\n",res);
		now[u]-=k; now[v]+=k;
	}
	return 0;
}
```

---

## 作者：__ykl (赞：0)

[题目链接](http://codeforces.com/problemset/problem/248/E)
 
# 分析：
令$f_{i,j}$表示第$i$个货架上有$j$个没有被试吃的期望，记$a_i$为第$i$个货架的初始数量，$ans$为当前都被试吃过的货架期望数量，显然有初始化：
$$f_{i,a_i} = 1\,(i = 1,2,\cdots,n),\quad ans = \sum_{i = 1}^n{f_{i,0}}$$

对于每个操作$i$，因为移动到$v_i$上的都是被试吃过的，所以货架$v_i$并不受影响，于是我们就只需要更新货架$u_i$。转移时枚举操作之前没被试吃过的数量，用组合数更新。用$d_i$表示货架$i$上的实际数量，有转移方程：
$$f_{u_i,j} = \frac{\sum_{k = j}^{min(k_i + j,d_{u_i})}(f_{u_i,k} \times C_k^{k - j} \times C_{d_{u_i} - k}^{k_i - (k - j)})}{C_{d_{u_i}}^{k _i}}\ (j = 0,1,\cdots,a_{u_i})$$
(即总概率 = 子事件期望数之和 / 事件总数)

注意每次操作我们还要维护答案$ans$与$d$数组，详见代码

# Code：
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int maxn = 1e5 + 50,maxm = 150;
int n,q,u,v,k,a[maxn],d[maxn];
double ans,f[maxn][maxm],c[10 * maxm][10 * maxm];
int read(){
    int x = 0;
    char c = getchar();
    while(c < '0' || c > '9') c = getchar();
    while(c >= '0' && c <= '9') x = x * 10 + (c ^ 48),c = getchar();
    return x;
}
int main(){
    for(int i = 0; i <= 1000; i ++){
        c[i][0] = 1;
        for(int j = 1; j <= i; j ++) c[i][j] = c[i - 1][j - 1] + c[i - 1][j];//预处理组合数
    }
    n = read();
    for(int i = 1; i <= n; i ++) a[i] = read(),d[i] = a[i],f[i][a[i]] = 1,ans += f[i][0];
    q = read();
    while(q --){
        u = read(),v = read(),k = read(),ans -= f[u][0];
        for(int i = 0; i <= a[u]; i ++){
            double s = 0;
            for(int j = i; j <= min(d[u],k + i); j ++) s += f[u][j] * c[j][j - i] * c[d[u] - j][k - (j - i)];
            f[u][i] = s / c[d[u]][k];
        }
        ans += f[u][0],d[u] -= k,d[v] += k;
        printf("%.9f\n",ans);
    }
    return 0;
}
```

---

## 作者：foreverlasting (赞：0)

[题面](https://www.luogu.org/problemnew/show/CF248E)

DP。

感觉这题好傻啊，没有题解，所以随便发一篇。

首先这个期望就是来吓唬人的，其实根本就是概率（这题哪来的结果啊）。然后神奇的是这道题居然没有取模！？？所以组合数直接预处理，$O(1)$调用就好了。设$dp[i][j]$表示第$i$个书架，有$j$个没被吃过的罐的期望。每一个的转移方程也很好写：$dp[u][i]=\sum_{j=0}^k (dp[u][i+j]*C(i+j,j)*C(b[u]-i-j,k-j)/C(b[u],k))$

$0<=i<=a[u],0<=j<=k,b[i]$表示当前货架上拥有的蜜罐。

然后就好了。

code:
```
//2018.10.17 by ljz
#include<bits/stdc++.h>
using namespace std;
#define res register LL
#define LL long long
#define inf 0x3f3f3f3f
#define eps 1e-15
inline LL read(){
    res s=0;
    bool w=0;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')w=1;ch=getchar();}
    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=getchar();
    return w?-s:s;
}
inline void _swap(res &x,res &y){
    x^=y^=x^=y;
}
inline LL _abs(const res &x){
    return x>0?x:-x;
}
inline LL _max(const res &x,const res &y){
    return x>y?x:y;
}
inline LL _min(const res &x,const res &y){
    return x<y?x:y;
}
const LL N=1e5+10;
const LL A=1e3+10;
namespace MAIN{
    LL n,m;
    LL a[N],b[N],C[A][A];
    inline void pre(){
        C[0][0]=1;
        for(res i=1;i<=A-10;i++){
            C[i][0]=1;
            for(res j=1;j<=i;j++)C[i][j]=C[i-1][j-1]+C[i-1][j];
        }
    }
    double dp[N][100+10],ans;
    inline void MAIN(){
        pre();
        n=read();
        for(res i=1;i<=n;i++)a[i]=b[i]=read(),dp[i][a[i]]=1,ans+=dp[i][0];
        m=read();
        while(m--){
            res u=read(),v=read(),k=read();
            ans-=dp[u][0];
            for(res i=0;i<=a[u];i++){
                double tmp=0,t=C[b[u]][k];
                for(res j=0;j<=k;j++)tmp+=dp[u][i+j]*C[i+j][j]*C[b[u]-i-j][k-j]/t;
                dp[u][i]=tmp;
            }
            b[u]-=k,b[v]+=k,ans+=dp[u][0];
            printf("%.10lf\n",ans);
        }
    }
}
int main(){
    MAIN::MAIN();
    return 0;
}
```

---

