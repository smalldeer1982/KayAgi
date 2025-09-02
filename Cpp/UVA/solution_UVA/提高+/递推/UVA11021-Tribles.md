# Tribles

## 题目描述

# Tribles

## 题面翻译

### 题目大意

一开始有 $k$ 只生物，这种生物只能活一天，死的时候有 $p_i$ 的概率生成 $i$ 只这种生物（也只能活一天），询问 $m$ 天内所有生物都死的概率（包括 $m$ 天前死亡的情况）


[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=22&page=show_problem&problem=1962

[PDF](https://uva.onlinejudge.org/external/110/p11021.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11021/dc00578efa81b6aad117bc54386f7e892627c921.png)

## 样例 #1

### 输入

```
4
3 1 1
0.33
0.34
0.33
3 1 2
0.33
0.34
0.33
3 1 2
0.5
0.0
0.5
4 2 2
0.5
0.0
0.0
0.5```

### 输出

```
Case #1: 0.3300000
Case #2: 0.4781370
Case #3: 0.6250000
Case #4: 0.3164062```

# 题解

## 作者：花园Serena (赞：27)

一道很经典的概率 DP 题

#### 提示 ：文中提到的死去指题目中的所有麻球全部死去

首先对于有 k 只麻球的问题，我们能够很快的想到，如果最开始有一只麻球在 m 天前死的概率为 $f_m$ ，那么 k 只麻球在 m 天前死去的概率为 ${f_m}^k$ ，于是我们就把 k 只麻球的问题转化成了一只麻球的问题。

如果只有一只麻球，我们该如何进行 DP 呢？

首先如上文设状态为 $f_i$ 表示最开始有一只麻球，在第 $i$ 天所有麻球会死，那么


$$f_i =  \sum_{j = 0} ^ {n - 1} {p_j * {f_{i - 1}} ^ j} $$

来解释一下这个式子，首先对于第 1 只麻球，要在 第 $i$ 天或之前死，那么他在第一天生出的小麻球显然就需要在 $i - 1$ 天前死，而对于每一只小麻球他们都是互不干扰的，所以对于每一只小麻球都可以重新看作最开始的第一只麻球，那么一只麻球在第 $i$ 天所有后代都死去的概率为他生出后代的概率乘以他的所有后代在 $i - 1$ 天全部都会死去的概率也就是上式。

最终答案为 ${f_m} ^ k$

下为代码，如有疑问或是有错误欢迎评论与私信指出

```cpp
#include <bits/stdc++.h>
using namespace std;
double f[1000 + 10], p[1000 + 10];
int main ()  {
	int T; scanf("%d", &T);
	for(register int flag = 1; flag <= T; flag ++) {
		int n, k, m;
		memset(f, 0, sizeof(f));
		memset(p, 0, sizeof(p));
		scanf("%d%d%d", &n, &k, &m);
		for(register int i = 0; i < n; i ++) 
			scanf("%lf", &p[i]);
		for(register int i = 1; i <= m; i ++) {
			for(register int j = 0; j <= n; j ++) {
				f[i] += p[j] * pow(f[i - 1],j);
			}
		}
		printf("Case #%d: %.7lf\n",flag, pow(f[m], k));
	}
	return 0;
}
```
~~看在我差点把麻球全部打成玛奇玛的份上点个赞叭（哭）~~

---

## 作者：Plus_Ultra (赞：9)

一. 题目翻译:

- 有k只麻球(应该是一种小鸟)，每只活一天就会死亡.

- 每只麻球临死前会生出新的麻球，生i只麻球的概率为Pi
求m天以后所有麻球都死亡的概率.

二. 题目解法:

- 首先我们要知道一件事:
  在马路上,如果一个人被撞的概率是P,那么两个人一起被撞的概率就是:P^2(滑稽).
  
- 以此类推:一只麻球在i天后死亡的概率是f(i),那么两只麻球在i天死亡的概率为f(i)^2.

- 考虑一只麻球，i天后全部死亡的概率为:

![图片1.png](https://i.loli.net/2020/01/24/dVreY2AGN5PIRbn.png)

- 答案: f(m)^k. k只麻球在m天后同时死亡.

三. 代码:

```
#include<iostream>
#include<cmath>
#include<cstdio>

using namespace std;

int k,n,m,T;
double p[1005],f[1005];

int main()
{
	scanf("%d",&T);
	
	for(int t=1;t<=T;t++)
	{
		scanf("%d%d%d",&n,&k,&m);
		for(int i=0;i<n;i++)  scanf("%lf",&p[i]);
		
		f[1]=p[0];
		f[0]=0;
		for(int i=2;i<=m;i++)
		{
			f[i]=0;
			for(int j=0;j<n;j++)
			{
				f[i]+=p[j]*pow(f[i-1],j);	
			}	
		}
		
		printf("Case #%d: %.7lf\n",t,pow(f[m],k));	
	}
	
	return 0;
}
```

### [_Plus_Ultra!_](hiahiahia)




---

## 作者：小元勋 (赞：4)


- 由于每只麻球独立存活，所以我们只需要求出一开始只有$1$只麻球，$m$天后全部死亡的概率$f_{m}$。由全概率公式，我们有：

$$f_{i}=p_{0}+p_{1}f_{i-1}+p_{2}{(f_{i-1})}^{2}+p_{3}(f_{i-1})^{3}+...+p_{n-1}(f_{i-1})^{n-1}$$

- 其中$p_{j}(f_{i-1})^{j}$的意思是，又生了$j$个麻球，这些麻球在$i-1$天后死亡。

- 由于一开始有$k$只麻球，且各麻球死亡是独立的，所以答案为${(f_{m}})^{k}$

```cpp
#include <bits/stdc++.h>
using namespace std;
#define maxn 1050

int T,n,m,k;
double p[maxn],f[maxn];

inline int read_() {
	int x_=0,f_=1;char c_=getchar();
	while(c_<'0'||c_>'9') {if(c_=='-') f_=-1;c_=getchar();}
	while(c_>='0'&&c_<='9') {x_=(x_<<1)+(x_<<3)+c_-'0';c_=getchar();}
	return x_*f_;
}

void readda_() {
    T = read_();
    int CA = 0;
	while(T--) {
		n = read_();k = read_();m = read_();
		for(int i=0;i<n;++i) scanf("%lf",&p[i]);
		f[0] = 0;f[1] = p[0];
		for(int i=2;i<=m;++i) {
			f[i] = 0;
			for(int j=0;j<n;++j) {
				f[i] += p[j] * pow(f[i-1],j);
			}
		}
		printf("Case #%d: %.7lf\n",++CA,pow(f[m],k));
	}
}

int main() {
	//freopen("a.txt","r",stdin);
   //freopen("ac.txt","w",stdout);
	readda_();
	return 0;
}
```


---

## 作者：Acc_Robin (赞：2)

# UVA11021 Tribles 题解

更好的阅读体验[On Blog](https://accrobin.github.io/_posts/2021-03-12-%E6%A6%82%E7%8E%87%E4%B8%8E%E6%9C%9F%E6%9C%9B-UVA11021Tribles/)

## 题意

一开始有$k$只生物，这种生物只能活$1$天，死的时候有$p_i$的概率产生$i$只这种生物（也只能活一天），询问$m$天内所有生物都死的概率（包括$m$天前死亡的情况）。

## 思路

使用**全概率公式**

**全概率公式**


$$
P(A)=\sum_{1 \le i \le n}P(A|B_i)\times P(B_i)
$$

其中，$P(U\mid V)$表示在$V$的条件下发生$U$的概率。

其中，事件$B_1,B_2,...,B_n$构成一组**完备**的事件且都有正概率，即诸多事件$B$是样本空间的划分，满足

$$
\forall ~i \ne j~,~B_i \cap B_j=\varnothing\\
\forall ~i~,~P(B_i) \ge 0\\
\sum_{1\le i \le n}B_i=1
$$

对于本题，我们令$f(i)$表示

>一开始有$1$只生物，在$i$天后全部死亡的概率。

那么，对于一开始有$k$只生物，因为每只生物都是互相独立的，可以使用乘法原理，则

>一开始有$k$只生物，在$i$天后全部死亡的概率为$f(i)^k$。

那么本题所求即为$f(m)^k$。对于指数，因为每只生物都是互相独立的，所以可以使用乘法原理。

套用全概率公式，我们有

$$
f(i)=\sum_{0\le j \le n-1}f(i-1)^j \times P(j)
$$

解释一下，和式的一项意义就是

一只生物在第$i$天，会生出$j$只生物；且**在生出$j$只生物的情况下**，$j$只生物在$i-1$天中全都死亡的概率。

明显地套用全概率公式。

$~$

需要提前处理$f(0)$和$f(1)$的值：

$f(0)$显然为$0$，因为在$0$天时生物是不可能死亡的。

$f(1)$为$P(0)$，两种思考方式：

1.在$1$天时生物死亡的概率就是不生孩子的概率。

2.直接套用之前推出的公式，$f(1)=P_0+0+0+...+0=P_0$

上代码：
```cpp
//UVA11021 Tribles
//2021-3-11
#include<cstdio>
#include<cstring>
#include<cmath>
namespace Acc{
	const int N = 1e3+10;

	int n,k,m,T,cnt;

	double p[N],f[N];
	
	int work(){
		scanf("%d",&T);
		while(T--){
			scanf("%d%d%d",&n,&k,&m);
			memset(f,0,sizeof(f));
			for(int i=0;i<n;i++) scanf("%lf",&p[i]);
			f[1]=p[0];
            f[0]=0;
			for(int i=2;i<=m;i++){
				for(int j=0;j<=n-1;j++){
					f[i]+=p[j]*pow(f[i-1],j);
				}
			}
			printf("Case #%d: %.7lf\n",++cnt,pow(f[m],k));
		}
		return 0;
	}
}
int main(){
	return Acc::work();
}
```

引用

1.[OI-wiki](https://oi-wiki.org/math/expectation/#_10)

2.刘汝佳 算法竞赛入门经典训练指南

---

## 作者：marTixx (赞：2)

[myblog](https://www.cnblogs.com/martixx/p/13986246.html)

我们一开始有$k$只生物，这是很难搞的，所以可以先考虑一开始只有1只生物，

设$p[i]$表示一开始有$1$只生物，第$i$天所有生物死光光的概率，

求出$p[m]$后，$ans = p[m]^{k}$，

为什么呢，就是乘法公式哦，也可以感性理解下，把一开始的$k$生物一只一只分开，它们和它们的子孙后代就是一个个互不干涉的家族，总共有$k$个家族，在第$m$天所有的$k$个家族都灭门的概率不就是$p[m]^k$吗？~~滑稽(~~

所以现在我们只要求$p[m]$,先给出式子：
$$
s[i] = \sum_{j=0}^{n-1}p[j]*s[i-1]^j
$$
来理解下，假如昨天存活的生物生了$j$个后代（这$j$个后代是独立的，互不干涉），每个后代在今天肯定会，死的概率就是它昨天出生的概率$s[i-1]$，所以$j$个全死的概率就是$s[i-1]^j$，枚举$j$相加就好

```cpp
#include <cstdio>
#include <cstring>
typedef double db;

const int N = 1e3 + 30;

int T, n, m, k, cnt;
db p[N], s[N];

db POW(db t, int num)
{
    db ans = 1;
    while (num)
    {
        if (num & 1) ans *= t;
        t *= t, num >>= 1;
    }
    return ans;
}

int main()
{
    scanf ("%d", &T);
    while (T--)
    {
        scanf ("%d%d%d", &n, &k, &m);
        for (int i = 0; i < n; ++i) scanf ("%lf", &p[i]);
        s[1] = p[0];
        for (int i = 2; i <= m; ++i)
        {
            s[i] = 0;
            for (int j = 0; j < n; ++j) s[i] += p[j] * POW(s[i - 1], j);
        }
        printf ("Case #%d: %.7lf\n", ++cnt, POW(s[m], k));
    }
    return 0;
}
```



---

## 作者：andyli (赞：2)

由于每只麻球的后代独立存活，只需求出一开始只有$1$只麻球，$m$天后全部死亡的概率$f(m)$。由全概率公式，有：
$$f(i)=P_0+P_1f(i-1)+P_2f(i-2)^2+P_3f(i-3)^3+...+P_{n-1}f(i-1)^{n-1}$$  
其中$P_jf(i-1)^j$的含义是这个麻球生了$j$个后代，它们在$i-1$天后全部死亡。注意这$j$个后代的死亡是独立的，而每个死亡的概率都是$f(i-1)$，因此根据乘法公式，$j$个后代全部死亡的概率为$f(i-1)^j$。同理，由于一开始共有$k$只麻球，且各只麻球的死亡是独立的，由乘法公式，最终答案是$f(m)^k$。代码如下（注意$m=0$的情况）：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1005;

double P[maxn], f[maxn];
int main()
{
    int T;
    scanf("%d", &T);
    for (int kase = 1; kase <= T; kase++)
    {
        int n, k, m;
        scanf("%d%d%d", &n, &k, &m);
        for (int i = 0; i < n; i++)
            scanf("%lf", &P[i]);
        f[0] = 0, f[1] = P[0];
        for (int i = 2; i <= m; i++)
        {
            f[i] = 0;
            for (int j = 0; j < n; j++)
                f[i] += P[j] * pow(f[i - 1], j);
        }
        printf("Case #%d: %.7lf\n", kase, pow(f[m], k));
    }
    return 0;
}
```

---

## 作者：Ezio_0420 (赞：2)

只要知道全概率公式，这就是一道水题。因为麻球的各种活动都互不影响，所以现在只考虑一只麻球，我们假设f[i]是第i天全部都死亡的概率，那么

f[i] = p0 + p1*f[i-1] + p2*f[i-1]^2 + ...pn-1*f[i - 1]^(n-1)
    
也就是用前一天的全部死亡概率来代替今天的每一只死亡的概率，又因为今天的每只的生死概率什么的都是独立的，所以p2*f[i-1]^2可以理解成剩下2只，然后两只都死了，这样最后在第m天死光的概率就是f[m]，但是这个只是一只麻球的，所有麻球都死光是f[m]^k。
```cpp
#include<cstdio>
#include<cmath>
const int maxn = 1000 + 10;
const int maxm = 1000 + 10;
int n, k, m;
double P[maxn], f[maxm];
int main() {
  int T;
  scanf("%d", &T);
  for(int kase = 1; kase <= T; kase++) {
    scanf("%d%d%d", &n, &k, &m);
    for(int i = 0; i < n; i++) scanf("%lf", &P[i]);
    f[0] = 0; f[1] = P[0];
    for(int i = 2; i <= m; i++) {
      f[i] = 0;
      for(int j = 0; j < n; j++) f[i] += P[j] * pow(f[i-1], j);
    }
    printf("Case #%d: %.7lf\n", kase, pow(f[m], k));
  }
  return 0;
}
```

---

## 作者：zhaomingrui (赞：2)

题目描述：

有k只麻球，每只活一天就会死亡，临死前可能会生下一些新的小麻球，具体来说，省i个麻球的概率为Pi。给定m，求m天后所有麻球均死亡的概率。

如果直接处理会非常麻烦！！所以我们用一个函数f(x),代表开始有一只麻球，m天后所有麻球死亡的概率。
所以可以列出递推式》f(i)=P0+P1*f(i-1)+.....+Pn-1*f(i-1)^(n-1);

解释;

f(i)+=Pj*f(i-1)^j;因为共j只麻球，它们死亡概率就是f(i-1)^j;至于他们加起来，是因为全概率公式。

那么很显然，接下来要做的就是递推运算！！
最后再算出f(m)^k;

代码如下：
```
#include<bits/stdc++.h>
using namespace std;
int n,k,m,T;
double f[1005],p[1005];
int main()
{
	scanf("%d",&T);
	for(int h=1;h<=T;++h)
	{
		scanf("%d%d%d",&n,&k,&m);
		for(int i=0;i<n;++i)
		 scanf("%lf",&p[i]);
       f[1]=p[0];
       for(int i=2;i<=m;++i)
       {
       	f[i]=0;
       	for(int j=0;j<n;++j)
       	 f[i]+=p[j]*pow(f[i-1],j);
       }
        printf("Case #%d: %.7lf\n",h,pow(f[m],k));
	}
	return 0;
} 
```

---

## 作者：Randyhoads (赞：2)

概率DP水题
如果不会概率与期望的可以到我的博客[my blog](https://www.cnblogs.com/wlzs1432/p/9373284.html)中查看。

显然对于每个生物m天全挂掉的概率一样，于是我们就只用考虑其中一只，另`dp[i]`为一只生物在i天后死掉的概率。

由全概率公式dp[i]=$\sum_{j=0}^{n-1}p[j]*dp[i-1]^j$

代码如下
```cpp
#include<bits/stdc++.h>

using namespace std;

const int MAXN  = 1000+10;

inline int read()
{
	int f=1,x=0;
	char ch;
	do
	{
		ch=getchar();
		if(ch=='-') f=-1;
	}while(ch<'0'||ch>'9');
	do
	{
		x=(x<<3)+(x<<1)+ch-'0';
		ch=getchar();
	}while(ch>='0'&&ch<='9');
	return f*x;
}

int t;
int n,m,k;
double dp[MAXN];
double p[MAXN];
int num=0;

int main()
{
	t=read();
	while(t--)
	{
		n=read();k=read();m=read();
		for(int i=0;i<n;i++) scanf("%lf",&p[i]);
		dp[0]=0;dp[1]=p[0];
		double sum;
		for(int i=2;i<=m;i++) 
		{
			sum=1;
			dp[i]=0;
			for(int j=0;j<n;j++)
			{
				dp[i]+=p[j]*sum;
				sum*=dp[i-1];	
			}
		}
		++num;
		printf("Case #%d: %.7f\n",num,pow(dp[m],k));
	}
} 
```

---

## 作者：xixiup (赞：1)

### 题目大意

有 $k$ 头神奇的生物，这些生物过 $1$ 天就会死掉，但是在死掉后就会分裂出一些和原来一毛一样的生物，分裂出的头数在 $\left[0,n-1\right]$ 中，其中分裂出 $i$ 头的概率为 $p_i$。

求在 $m$ 天内（包括 $m$ 天）这些生物全部死亡的概率。

### 思路分享

不妨先从一头生物说起：设 $con_i$ 为 $k=1$ 时，在第 $i$ 天内全部死亡的概率。

那么拓展到 $k\not=1$ 的情况，可以发现：若 $1$ 头生物在某天前死亡的概率为 $x$，那么可以发现：$2$ 头生物在这天内的死亡概率为 $x^2$，$n$ 头生物在这天内的死亡概率为 $x^n$。

所以可以推出如下公式：

$$
\boxed{con_i=p_0+{con_{i-1}}^1*p_1+{con_{i-1}}^2*p_2...+{con_{i-1}}^{n-1}*p_{n-1}}
$$

然后，我们就可以根据这个式子推出 $con_m$，最后由于开始有 $k$ 头生物，所以就可以求出答案为 ${con_m}^k$。

然后考虑如何赋边界值。

对于在 $0$ 天内全部死亡的概率，因为开始的 $1$ 头生物都能活过一天，所以 $con_0=0$，而如果 $1$ 头生物一天内死亡的情况，则仅有这头生物直接死亡后消失才可以，所以 $con_1=p_0$。

### 代码展示

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1010;
int n,m,k;
double p[maxn],con[maxn];
//p、con与前文中的含义相同
double ksm(double x,int y){//快速幂
	double ans=1;
	while(y){
		if(y&1==1){
			ans*=x;
		}
		x*=x;
		y/=2;
	}
	return ans;
}
int main(){
	int T;
	cin>>T;
	for(int t=1;t<=T;t++){
		cin>>n>>k>>m;
		for(int i=0;i<n;i++){
			scanf("%lf",&p[i]);
		}
		con[0]=0;
		con[1]=p[0];//赋初始值
		for(int i=2;i<=m;i++){
			con[i]=p[0];
			for(int j=1;j<n;j++){
				con[i]+=p[j]*ksm(dp[i-1],j);
			}//计算con[i]
		}
		printf("Case #%d: %.6lf\n",t,ksm(dp[m],k));
	}
	return 0;
}
```


---

## 作者：hyjdouSHEN (赞：0)

[原题传送门](https://www.luogu.com.cn/problem/UVA11021)

## 题目分析

我们分析题目可知，由于每个生物的后代是**独立存活**的，只要求出一开始只有 $1$ 只生物，$m$ 天后全部死亡的概率 $f(m)$ 就可以了。

所以由全概率公式我们就可以求得

$f\left ( i \right )=P_0+P_1\cdot f(i-1)^2 + P_2\cdot f(i-1)^3 + … + P_{n-1}\cdot f(i-1)^{n-1}$

其中，$P_j\cdot f(i-1)^j$ 的含义是这只生物生了 $j$ 只后代，它们在 $i-1$ 天后全部死亡。要注意的是这 $j$ 只后代的死亡是**独立**的，而每只死亡的概率都是 $f(i-1)$，因此根据乘法公式，把死亡的概率乘起来，得到 $j$ 只后代全部死亡的概率为 $f(i-1)^j$。同理，由于一开始共有 $k$ 只生物，各只生物的死亡也是**独立**的，由乘法公式，我们可以得到最终的答案是 $f(m)^k$。

代码如下。 

## 代码部分

```cpp
//要注意m=0的情况
#include<bits/stdc++.h>
using namespace std;
const int maxn=1010;
int n,k,m;
double P[maxn],f[maxn];
int main()
{
	int T;
	scanf("%d",&T);
	for(int kase=1;kase<=T;kase++){
		scanf("%d%d%d",&n,&k,&m);
		for(int i=0;i<n;i++){
			scanf("%lf",&P[i]);
		}
		f[0]=0;f[1]=P[0];
		for(int i=2;i<=m;i++){
			f[i]=0;
			for(int j=0;j<n;j++) f[i]+=P[j]*pow(f[i-1],j);
		}
		printf("Case #%d: %.7lf\n",kase,pow(f[m],k));
	}
	return 0;
}
```

希望这篇题解对你有帮助~

[AC记录](https://www.luogu.com.cn/record/120128749)

---

## 作者：Coros_Trusds (赞：0)

# 题目大意

一开始有 $n$ 种生物，这种生物只能活 $1$ 天，死的时候有 $p[i]$ 的概率产生 $i$ 只这种生物（也只能活一天），问 $m$ 天内所有生物都死的概率（包括 $m$ 天前死亡的情况）。

# 题目分析

令 $dp[i]$ 表示最开始有一只生物，第 $i$ 天时所有生物都已经死了的概率。

所以状态转移方程为 $dp[i]=p[0]+p[1]\times dp[i-1]+p[2]\times(dp[i-1])^2+\cdots+p[n-1]\times(dp[i-1])^{n-1}$。

解释一下：$p[j]\times(dp[i-1])^j$ 的意思是：又生了 $j$ 只且这些新生儿全部在 $i-1$ 天及第 $i-1$ 天之前死。因为每只生物都独立，所以每一只新生儿都可以看做“单独的一只生物”。

# 代码

```cpp
//2022/5/17
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <climits>//need "INT_MAX","INT_MIN"
#include <cstring>//need "memset"
#include <numeric>
#include <algorithm>
#include <cmath>
#define enter putchar(10)
#define debug(c,que) std::cerr << #c << " = " << c << que
#define cek(c) puts(c)
#define blow(arr,st,ed,w) for(register int i = (st);i <= (ed); ++ i) std::cout << arr[i] << w;
#define speed_up() std::ios::sync_with_stdio(false),std::cin.tie(0),std::cout.tie(0)
#define mst(a,k) memset(a,k,sizeof(a))
#define Abs(x) ((x) > 0 ? (x) : -(x))
#define stop return(0)
const int mod = 1e9 + 7;
inline int MOD(int x) {
	if(x < 0) x += mod;
	return x % mod;
}
namespace Newstd {
	char buf[1 << 21],*p1 = buf,*p2 = buf;
	inline int getc() {
		return p1 == p2 && (p2 = (p1 = buf) + fread(buf,1,1 << 21,stdin),p1 == p2) ? EOF : *p1 ++;
	}
	inline int read() {
		int ret = 0,f = 0;char ch = getc();
		while (!isdigit(ch)) {
			if(ch == '-') f = 1;
			ch = getc();
		}
		while (isdigit(ch)) {
			ret = (ret << 3) + (ret << 1) + ch - 48;
			ch = getc();
		}
		return f ? -ret : ret;
	}
	inline void write(int x) {
		if(x < 0) {
			putchar('-');
			x = -x;
		}
		if(x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
}
using namespace Newstd;

const int N = 1005;
double p[N],dp[N];
int T,n,k,m,cases;
inline void init() {
	mst(dp,0),mst(p,0);
}
inline void solve() {
	scanf("%d%d%d",&n,&k,&m);
	for (register int i = 0;i < n; ++ i) {
		scanf("%lf",&p[i]);
	}
	dp[1] = p[0];
	for (register int i = 2;i <= m; ++ i) {
		for (register int j = 0;j < n; ++ j) {
			dp[i] += p[j] * pow(dp[i - 1],j);
		}
	}
	printf("Case #%d: %.7lf\n",++ cases,pow(dp[m],k));
}
int main(void) {
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	scanf("%d",&T);
	while (T --) {
		init();
		solve();
	}

	return 0;
}
```

---

## 作者：serverkiller (赞：0)

## 题意

$k$只虫子,每只虫子死后有$p_i$的概率产生$i$只虫子$(0\leq i < n)$,问在$m$天后,虫子死光的概率

## solution

~~精心设计状态~~

我们发现每只虫子的生存问题都是独立的,那么可以把问题转换成1只虫子在$m$天后死掉的概率

设$dp_i$表示1只虫子在$i$天后死亡的概率,那么显然有:
$$
dp_i=\displaystyle\sum\limits_{j=0}^{n-1}p_jdp_{i-1}^j
$$
最终的结果就是$dp_m^k$啦

```cpp
#include <bits/stdc++.h>
#define int long long
#define N 100005
using namespace std;
    
template <typename T>
     
void read(T &a)
{
    T x = 0,f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    a = x * f;
}
     
template <typename T,typename... Args> void read(T &t,Args &... args) {read(t); read(args...); }

int n,k,m;
double dp[1005],p[1005];

double ksm(double a,int b)
{
	double res = 1;
	while (b)
	{
		if (b & 1) res = res * a;
		a = a * a;
		b >>= 1;
	}
	return res;
}

signed main()
{
	int t;
	read(t);
	for (int T = 1; T <= t; T++)
	{
		read(n,k,m);
		for (int i = 0; i < n; i++)
			scanf("%lf",&p[i]);
		for (int i = 1; i <= m; i++)
		{
			dp[i] = 0;
			double tmp = 1;
			for (int j = 0; j < n; j++)
			{
				dp[i] += p[j] * tmp;
				tmp *= dp[i - 1];
			}
		}
		printf("Case #%lld: %.6lf\n",T,ksm(dp[m],k));
	}
	return 0;
}
```

~~说句闲话,UVA的题面好难提交啊~~

---

