# [POI 2012] ODL-Distance

## 题目描述

**译自 POI 2012 Stage 1. 「[Distance](https://szkopul.edu.pl/problemset/problem/Phel_x2Ny30OUh7z1RhCtzEG/site/?key=statement)」**

定义一次「操作」为将一个正整数除以或乘以一个质数。定义函数 $d(a,b)$ 表示将 $a$ 进行若干次“操作”变成 $b$ 所需要的最小操作次数。例如，$d(69,42)=3$.

$d$ 显然是一个距离函数，满足以下性质：
* $d(a,a) = 0$
* $d(a,b) = d(b,a)$
* $d(a,b) + d(b,c) \ge d(a,c)$

给定 $n$ 个正整数 $a_1, a_2, \ldots, a_n$，对每个 $a_i (1 \le i \le n)$，求 $j$ 使得 $j \neq i$ 且 $d(a_i,a_j)$ 最小。如果有多个满足条件的 $j$，应输出最小的那个。

## 说明/提示

对于 $30\%$ 的数据有 $n \le 1000$.

对于所有数据有 $2 \le n \le 10^5,1 \le a_i \le 10^6$.

翻译来自于 [LibreOJ](https://loj.ac/p/2690)。

## 样例 #1

### 输入

```
6
1
2
3
4
5
6```

### 输出

```
2
1
1
2
1
2```

# 题解

## 作者：kczno1 (赞：11)

dis(a,b)=a\*b/(gcd(a,b)^2)的质因数个数

预处理每个数的质因数个数num。

考虑枚举gcd。

也就是枚举x,对于x，枚举所有x的倍数a。

那么dis(a,b)=num(a)+num(b)-2\*num(x)

那么对于每个a,选择的b就应该是最小的那一个。

我们求出num最小的，对于非最小用它更新答案，同时更新最小答案。

这样虽然不能保证x是a,b的gcd，但是a,b的gcd一定会被枚举到，所以答案一定会被更新成最优的。

```cpp
#include<bits/stdc++.h>
using std::swap; 

#define U 1000000
#define N 100100
int num[U+5],t[U+5];
void init_num()
{
    static int p[N],top;
    for (int i=2;i<=U;++i)
    {
      if (!num[i])
      {
           p[++top]=i;
           num[i]=1;
      }
      int x;
      for (int j=1;(x=p[j])*i<=U;++j)
      {
            num[x*i]=num[i]+1;
          if (!(i%x)) break;     
      }
    }
}

int a[N],next[N];
int ansj[N],ans[N];
int q[N],top;

int main()
{
    freopen("1.in","r",stdin);
    init_num();
    int n,i;
    scanf("%d",&n); 
    for (i=1;i<=n;++i) 
    {scanf("%d",a+i);ans[i]=U;
     next[i]=t[a[i]];t[a[i]]=i;
    }
    int x,j;
    for (x=1;x<=U;++x)
    {
        top=0;
        for (i=1;i<=U/x;++i)
         for (j=t[x*i];j;j=next[j]) q[++top]=j;
        int b=q[1];
        for (i=2;i<=top;++i)
        if (num[a[q[i]]]<num[a[b]]||num[a[q[i]]]==num[a[b]]&&q[i]<b) swap(b,q[i]);
        for (i=2;i<=top;++i)
        {
            int A=q[i],now=num[a[A]]+num[a[b]]-(num[x]<<1);
            if (now<ans[A]||now==ans[A]&&b<ansj[A]) 
            {
                ans[A]=now;ansj[A]=b;
            }
            if (now<ans[b]||now==ans[b]&&A<ansj[b]) 
            {
                ans[b]=now;ansj[b]=A;
            }
        }
    }
    for (i=1;i<=n;++i) printf("%d\n",ansj[i]);
} 
```

---

## 作者：lhm_ (赞：5)

设 $cnt(x)$ 为 $x$ 质因数分解后质因数的指数和，即将 $x$ 不断除其一个约数来使其变为 $1$ 所需的次数，其可以通过线性筛来预处理。

不难发现：
$$
\large d(a_i,a_j)=cnt(a_i)+cnt(a_j)-2cnt(\gcd(a_i,a_j))
$$
考虑对于每个 $a_i$，可以枚举其约数，即枚举与另一个数 $a_j$ 的 $\gcd$。这样的话，$cnt(a_i)$ 和 $cnt(\gcd(a_i,a_j))$ 就都确定下来了。要使 $d(a_i,a_j)$ 最小，只需 $cnt(a_j)$ 最小，于是可以处理出每个数的所有倍数中 $cnt$ 最小的数，且该数在序列 $\{ a_i \}$ 中。因为要求 $i \not = j$，因此还需处理出次小值。

然后就可以统计每个约数的最优贡献了，这样枚举到的约数不一定恰好为 $\gcd(a_i,a_j)$，但当枚举到 $\gcd(a_i,a_j)$ 一定会更优，所以最终的答案一定为 $\gcd(a_i,a_j)$。

```cpp
#include<bits/stdc++.h>
#define maxn 1000010
#define all 1000000
#define inf 1000000000
using namespace std;
template<typename T> inline void read(T &x)
{
    x=0;char c=getchar();bool flag=false;
    while(!isdigit(c)){if(c=='-')flag=true;c=getchar();}
    while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    if(flag)x=-x;
}
int n,tot,ans,val;
int a[maxn],p[maxn],cnt[maxn],mn1[maxn],mn2[maxn];
bool tag[maxn];
void init()
{
    for(int i=2;i<=all;++i)
    {
        if(!tag[i]) p[++tot]=i,cnt[i]=1;
        for(int j=1;j<=tot;++j)
        {
            int k=i*p[j];
            if(k>all) break;
            tag[k]=true,cnt[k]=cnt[i]+1;
            if(i%p[j]==0) break;
        }
    }
}
void update(int d,int x)
{
    if(cnt[a[x]]<cnt[a[mn1[d]]]) mn2[d]=mn1[d],mn1[d]=x;
    else if(cnt[a[x]]<cnt[a[mn2[d]]]&&x!=mn1[d]) mn2[d]=x;
}
void work(int d,int x)
{
    int y=mn1[d]==x?mn2[d]:mn1[d],v=cnt[a[x]]+cnt[a[y]]-2*cnt[d];
    if(v<val||(v==val&&y<ans)) val=v,ans=y;
}
int main()
{
    init(),read(n),cnt[0]=inf;
    for(int i=1;i<=n;++i) read(a[i]);
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j*j<=a[i];++j)
        {
            if(a[i]%j) continue;
            update(j,i),update(a[i]/j,i);
        }
    }
    for(int i=1;i<=n;++i)
    {
        val=inf;
        for(int j=1;j*j<=a[i];++j)
        {
            if(a[i]%j) continue;
            work(j,i),work(a[i]/j,i);
        }
        printf("%d\n",ans);
    }
    return 0;
}
```

---

## 作者：傅思维666 (赞：3)

## 题解：

其实这道题的性质啥的还是比较好推导的，我觉得难点只在于如何简洁、正确地实现代码。

先考虑：对于任意的两个数$A,B$，如何用最少的乘除质数的操作完成转换？

肯定秒想质因子分解啊。

现在我们有A的质因子，B的质因子，A,B的公共质因子。明显地，最少步数就是**相同的质因子保留，不同的质因子乘除**，设$f(x)$为$x$的质因子个数（质因子指数和）。那么最少步骤就是：$f(A)+f(B)-2f(\gcd(A,B))$。

这个式子还是很好推导的。

然后显而易见的暴力思路就是对于每个位置$i$，从头到尾枚举$j$，一旦符合条件就跳出。$O(n^2)$做法。

肯定是不行，我们思考优化。对于这种三元问题，定一元，枚举另一元，不行的话就枚举下一元好了。既然枚举$j$要T，我们尝试枚举$\gcd(a[i],a[j])=g$。

那么对于$g$，我们需要在它的所有倍数中找到存在于序列中的且下标尽可能小的位置。这个步骤不能用正向思维，比如用set维护。要逆向想：在枚举一个数$x$的所有因子$g$的过程中，$x$就是$g$的一个倍数，我们直接用$x$来更新就好了。

需要注意的是，有可能存在最小下标就是这个数本身的情况，于是我们还需要维护一个次小值。

最后查询的时候直接$O(1)$就好。

代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=1e6+5;
const int maxw=1e6+6;
const int INF=1e9;
int n,tot,ans,val,maxx;
int a[maxn],prime[maxn],cnt[maxn],mn1[maxn],mn2[maxn];
//mn1,mn2表示一个数的所有倍数中最小、次小值的位置
bool v[maxn];
void init(int x)
{
    for(int i=2;i<=x;i++)
    {
        if(!v[i]) 
			prime[++tot]=i,cnt[i]=1;
        for(int j=1;j<=tot && i*prime[j]<=x;j++)
        {
            v[i*prime[j]]=1;
			cnt[i*prime[j]]=cnt[i]+1;
            if(i%prime[j]==0) 
				break;
        }
    }
}
void update(int d,int x)
{
    if(cnt[a[x]]<cnt[a[mn1[d]]]) 
		mn2[d]=mn1[d],mn1[d]=x;
    else if(cnt[a[x]]<cnt[a[mn2[d]]]&&x!=mn1[d]) 
		mn2[d]=x;
}
void getans(int d,int x)
{
    int pos=mn1[d]==x?mn2[d]:mn1[d];
	int v=cnt[a[x]]+cnt[a[pos]]-2*cnt[d];
    if(v<val||(v==val&&pos<ans)) 
		val=v,ans=pos;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		maxx=max(maxx,a[i]);
	}
    init(maxx);
	cnt[0]=INF;
    for(int i=1;i<=n;i++)
        for(int j=1;j*j<=a[i];++j)
        {
            if(a[i]%j) 
				continue;
            update(j,i);
			update(a[i]/j,i);
        }
    for(int i=1;i<=n;++i)
    {
        val=INF;
        for(int j=1;j*j<=a[i];++j)
        {
            if(a[i]%j) 
				continue;
            getans(j,i);
			getans(a[i]/j,i);
        }
        printf("%d\n",ans);
    }
    return 0;
}
```



---

## 作者：This_Rrhar (赞：2)

**Lemma：$|a-b|=a+b-2\min(a,b)$**。

>证明：
>
>减去一个 $\min(a,b)$ 会消去一个 $a$ 或 $b$，剩下 $\max(a,b)$，所以再减去一个 $\min(a,b)$ 就变成 $|a-b|$。

用 $\Omega(n)$ 表示 $n$ 所有质因数的次数和，即：若 $\displaystyle n=\prod p_k^{t_k}$，则 $\displaystyle\Omega(n)=\sum t_k$。

考虑两个数 $\displaystyle a_i=\prod p_k^{x_k},a_j=\prod p_k^{y_k}$，显然有 $\displaystyle d(i,j)=\sum|x_k-y_k|=\sum(x_k+y_k-2\min(x_k,y_k))$。

注意到 $\displaystyle\prod p_k^{\min(x_k,y_k)}=\gcd(a_i,a_j)$，所以 $d(i,j)=\Omega(a_i)+\Omega(a_j)-2\Omega(\gcd(a_i,a_j))$。

容易在 $O(V)$ 时间内筛出所有 $\Omega(n)$，因此计算 $d(i,j)$ 是 $O(\log n)$ 的，瓶颈在求 $\gcd$。

直接枚举 $a_i$ 和 $a_j$ 是 $O(n^2\log n)$ 的，不能通过。

故考虑枚举 $a_i$ 和 $\gcd(a_i,a_j)$，此时需满足 $i\ne j,\gcd(a_i,a_j)\mid a_j$，而我们要求 $\Omega(a_j)$ 最小，考虑预处理出对于 $\forall1\le k\le V$，当 $k$ 为 $\gcd$ 时，选取哪个 $j$ 可以使 $\Omega(a_j)$ 最小。

又因为预处理的方式会使得 $a_i$ 是最优的，因此我们需要记录次小值。

按这种方式，枚举的 $\gcd$ 可能会比实际的 $\gcd$ 要小，但由于 $-2\Omega(\gcd(a_i,a_j))$ 这一项，枚举到的答案必然不优于实际答案。又因为实际的 $\gcd$ 必定能枚举到，所以这个算法是正确的。

最终的时间复杂度是 $O(n\sqrt V+V\log V)$，代码稍后再补。

---

## 作者：__ycx2010__ (赞：2)

设 $g(x)$ 表示 $x$ 的质因子个数，对于两个数 $x$ 和 $y$，$d(x,y)=g(x)+g(y)-2g(\gcd(x,y))=\min_{k|x,k|y}(g(x)+g(y)-2g(k))$。

于是我们枚举 $x,k$，设 $f(k)$ 表示质因数个数最小的满足为 $k$ 的倍数的在序列 $a$ 中的数，则更新答案 $dis(x,f(k))$。

枚举 $x,k$ 的复杂度为 $O(n\sqrt{m})$，由于 $f(k)$ 可能等于 $x$，所以从前往后扫一遍，再从后往前扫一遍。

## code

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 100010, M = 1000010;
int d[M], vis[M], prime[M], tot;
int ans[N], pos[N], a[N], Mn[M], id[M];

void init() {
	d[1] = 0;
	for (int i = 2; i < M; i ++ ) {
		if (!vis[i]) {
			prime[++ tot] = i;
			d[i] = 1;
		}
		for (int j = 1; prime[j] * i < M; j ++ ) {
			d[i * prime[j]] = d[i] + 1;
			vis[i * prime[j]] = true;
			if (i % prime[j] == 0) break;
		}
	}
}

void update(int x, int y, int val) {
	if (ans[x] > val) {
		ans[x] = val, pos[x] = y;
	} else if (ans[x] == val) {
		pos[x] = min(pos[x], y);
	}
}

int main() {
	memset(ans, 0x3f, sizeof ans);
	init();
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i ++ )
		scanf("%d", &a[i]);
	memset(Mn, 0x3f, sizeof Mn);
	for (int i = 1; i <= n; i ++ ) {
		for (int j = 1; j * j <= a[i]; j ++ ) {
			if (a[i] % j == 0) {
				update(i, id[j], d[a[i]] - 2 * d[j] + Mn[j]);
				update(i, id[a[i] / j], d[a[i]] - 2 * d[a[i] / j] + Mn[a[i] / j]);
			}
		}
		for (int j = 1; j * j <= a[i]; j ++ ) {
			if (a[i] % j == 0) {
				if (d[a[i]] < Mn[j]) {
					Mn[j] = d[a[i]], id[j] = i;
				}
				if (d[a[i]] < Mn[a[i] / j]) {
					Mn[a[i] / j] = d[a[i]], id[a[i] / j] = i;
				}
			}
		}
	}
	memset(Mn, 0x3f, sizeof Mn);
	for (int i = n; i >= 1; i -- ) {
		for (int j = 1; j * j <= a[i]; j ++ ) {
			if (a[i] % j == 0) {
				update(i, id[j], d[a[i]] - 2 * d[j] + Mn[j]);
				update(i, id[a[i] / j], d[a[i]] - 2 * d[a[i] / j] + Mn[a[i] / j]);
			}
		}
		for (int j = 1; j * j <= a[i]; j ++ ) {
			if (a[i] % j == 0) {
				if (d[a[i]] < Mn[j]) {
					Mn[j] = d[a[i]], id[j] = i;
				} else if (d[a[i]] == Mn[j]) {
					id[j] = i;
				}
				if (d[a[i]] < Mn[a[i] / j]) {
					Mn[a[i] / j] = d[a[i]], id[a[i] / j] = i;
				} else if (d[a[i]] == Mn[a[i] / j]) {
					id[a[i] / j] = i;
				}
			}
		}		
	}
	for (int i = 1; i <= n; i ++ ) printf("%d\n", pos[i]);
	return 0;
}
```

---

## 作者：Alex_Wei (赞：2)

> *[P3532 [POI2012]ODL-Distance](https://www.luogu.com.cn/problem/P3532)
>
> [POI 合集](https://www.cnblogs.com/alex-wei/p/POI.html)。

考虑在 $i$ 和 $p\times i\ (p\in \mathbb{P})$ 之间连边，题目相当于在这张图上撒 $n$ 个关键点，求距离每个关键点最近且非本身的关键点的最小编号。对每个点记录距离该点最近和第二近的关键点距离与编号，一遍 `BFS` 即可，但是常数太大，不开 O2 难以通过。

设 $\omega(i)$ 表示 $i$ 的质因子个数，则 $\mathrm{dis}(i,j)=\omega(i)+\omega(j)-2\omega(\gcd(i,j))$。考虑枚举 $d=\gcd(i,j)$，那么减号后面的部分就确定了，对于一个固定的 $i$，我们显然要让 $(\omega(j),buc_j)$ 这一二元组最小，其中 $buc_j$ 表示 $a$ 值为 $j$ 的最小位置。

考虑枚举 $d$ 的倍数 $kd$，求出 $\min_{k\geq 1,kd\leq r}(\omega(kd),buc_{kd})$，设为 $(x,y)$ 以及取到最小值的位置为 $td$。 那么对于所有 $k\neq t$，我们用 $td$ 和 $kd$ 互相更新。$kd$ 就相当于上面的 $i$，而 $td$ 充当了使得 $(\omega(j),buc_j)$ 最小的 $j$。

每个 $\gcd$ 都会被枚举到，因此算法正确。时间复杂度是调和级数的线性对数。由于小常数，成功拿到了最优解（2021.12.19）。

```cpp
const int N = 1e6 + 5;
int n, mx, a[N], buc[N], ans[N], fc[N]; pii dis[N];
int cnt, vis[N], pr[N], mpr[N], chk[N];
void sieve() {
	dis[1] = {N, 0};
	for(int i = 2; i <= mx; i++) {
		dis[i] = {N, 0};
		if(!vis[i]) pr[++cnt] = i, mpr[i] = i;
		for(int j = 1; j <= cnt && i * pr[j] <= mx; j++) {
			vis[i * pr[j]] = 1, mpr[i * pr[j]] = pr[j];
			if(i % pr[j] == 0) break;
		} chk[i] = chk[i / mpr[i]] + 1;
	}
} 
int main() {
	cin >> n;
	for(int i = 1; i <= n; i++) {
		a[i] = read(), cmax(mx, a[i]);
		if(buc[a[i]]) {
			ans[i] = buc[a[i]];
			if(!ans[buc[a[i]]]) ans[buc[a[i]]] = i;
		} else buc[a[i]] = i;
	} sieve();
	for(int i = 1; i <= mx; i++) {
		pii best = {N, 0};
		for(int j = i, dv = 1; j <= mx; j += i, dv++)
			if(buc[j]) cmin(best, (pii){chk[dv], buc[j]});
		for(int j = i, dv = 1; j <= mx; j += i, dv++) if(buc[j] != best.se && buc[j])
			cmin(dis[j], (pii){best.fi + chk[dv], best.se}),
			cmin(dis[a[best.se]], (pii){best.fi + chk[dv], buc[j]});
		if(buc[i] && !ans[buc[i]]) ans[buc[i]] = dis[i].se;
	} for(int i = 1; i <= n; i++) print(ans[i]), pc('\n');
	return flush(), 0;
}
```

---

## 作者：ThinkofBlank (赞：2)

​	首先，我们来分析题意：给出一个序列a[1]...a[n]，对于每个i，找到一个j使得i$\neq$j且j为最小使得使得a[i]到a[j]的距离最小的数。

####	距离定义为:定义一个数乘或除以一个质数为一步，一个数与另一个数的距离为一个数变为另一个数所需的最小步骤。

​	我们首先来推式子：我们要把一个数x变为y，我们需要改动哪些？我们设f(x)=dis(1,x)=把x分解质因数后所有质数的指数之和(**这个可以用线型筛O(n)预处理**)。

​	设d=gcd(x,y),那么可以发现,要把x变为y，我们无需改动乘积为d的部分，只需改动剩下部分即可，也即是说**dis(x,y)=f($\frac{x}{d}$)+f($\frac{y}{d}$)=f(x)+f(y)-2f(d)**

​	有了这个式子后，我们只需要对于每一个枚举的x找到一个合适的y即可。

​	注意到，dis(x,y)由x,y,d三部分共同组成,而x为定值,不用管。枚举y的话明显会T，所以我们考虑枚举d。我们知道，枚举d只需要$\sqrt{x}$次即可枚举完x的所有d。

​	现在d是一个定值了，于是，题目转化为:

#### ​	给定x,d求一个数y使得y是d的倍数且f(y)最小，且y对应的下标最小。

​	而且，我们当前已经花了n$\sqrt{n}$的时间枚举了，所以我们必须尽快求出答案。

​	那么我们考虑**预处理**。

​	首先，我们设g(x)表示,对于所有序列中是x的倍数的数y，最小的f(y)的值，t(x)则表示g(x)所对应的下标(满足最小)。所以，我们就可以O(1)回答上面的问题了！而且这是可以O(n$\sqrt{n}$)预处理出的！

​	但是，如果您打好代码，直接交一发，那么很遗憾，您会wa。

​	为什么呢？因为我们没有考虑到i$\neq$j这个条件！

​	当i=j时dis(i,j)=0，就会使得答案错误，那么我们改怎么解决呢？

​	我的方法是：**在维护最小值的基础上再维护一个次小值**

​	这样，因为最小值下标$ \neq$次小值下标,所以对于每个x一定能找到一个最小的满足条件的y

​	代码如下：

```c
//#pragma GCC optimize()//手动Ox优化
#include<bits/stdc++.h>
//维护最小值与次小值即可避免相同数的情况 
using namespace std;
const int N=1e5+1,M=1e6+1;
int a[N];
int f[M],zhi[M>>1],e;
int ti[M][2],id[M][2];//ti为x,y的约数为i时最小,次小的f的值,id为对应的下标 
inline void sai(int maxe){//个数筛
	for(int i=2;i<=maxe;++i){
		if(!f[i]){
			f[i]=1;
			zhi[++e]=i;
		}
		for(int j=1;j<=e;++j){
			if(i*zhi[j]>maxe){
				break;
			}
			f[i*zhi[j]]=f[i]+1;
			if(i%zhi[j]==0){
				break;
			}
		}
	}
}
int main(){
	memset(ti,0x3f3f,sizeof(ti));//记得初始化极大值 
	sai(M-1);//线性筛筛f函数
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%d",&a[i]);
		int now=a[i];
		for(int j=sqrt(now);j;--j){//预处理 
			if(now%j==0){
				if(ti[j][0]>f[a[i]]||(ti[j][0]==f[a[i]]&&i<id[j][0])){//更新最小值 
					ti[j][1]=ti[j][0];
					id[j][1]=id[j][0];//先让次小值继承最小值(其实相当于推表)
					ti[j][0]=f[a[i]];
					id[j][0]=i;
				}else if(ti[j][1]>f[a[i]]||(ti[j][1]==f[a[i]]&&i<id[j][1])){//更新次小值 
					ti[j][1]=f[a[i]];
					id[j][1]=i;
				}
				if(j*j!=now){//枚举另一个约数 
					int k=now/j;
					if(ti[k][0]>f[a[i]]||(ti[k][0]==f[a[i]]&&id[k][0]>i)){
						ti[k][1]=ti[k][0];
						id[k][1]=id[k][0];
						ti[k][0]=f[a[i]];
						id[k][0]=i;
					}else if(ti[k][1]>f[a[i]]||(ti[k][1]==f[a[i]]&&id[k][1]>i)){
						ti[k][1]=f[a[i]];
						id[k][1]=i;
					}
				}
			}
		}
	}
	for(int i=1;i<=n;++i){
		int now=a[i];
		int ans=2e9,ji;
		for(int j=sqrt(now);j;--j){//枚举d 
			if(now%j==0){
				int ant=ti[j][0]-2*f[j],anp=ti[j][1]-2*f[j];//计算距离，由于f[a[i]]是定值，所以可以忽略 
				if((ans>ant&&id[j][0]!=i)||(ans==ant&&id[j][0]!=i&&id[j][0]<ji)){
					ans=ant,ji=id[j][0];
				}else if(ans>anp||(ans==anp&&id[j][1]<ji)){
					ans=anp,ji=id[j][1];
				}
				if(j*j!=now){//枚举另一个约数 
					int k=now/j;
					ant=ti[k][0]-2*f[k],anp=ti[k][1]-2*f[k];
					if((ans>ant&&id[k][0]!=i)||(ans==ant&&id[k][0]!=i&&id[k][0]<ji)){
						ans=ant,ji=id[k][0];
					}else if(ans>anp||(ans==anp&&id[k][1]<ji)){
						ans=anp,ji=id[k][1];
					}
				}
			}
		}
		printf("%d\n",ji);
	}
	return 0;
}
```

---

## 作者：YLWang (赞：1)

好题。

首先我们只能考虑基于值域处理。

然后因为计算 $f(i,\ j)$ 的时候 $i$ 和 $j$ 是相互影响的我们无法直接操作他。

于是推得 $f(i,\ j) = \dfrac{d(i) \cdot d(j)}{d(\gcd(i,\ j)^2)}$。其中定义 $d(i)$ 为 $i$ 和 $1$ 的距离。容易预处理出来 $d$。

然后考虑枚举 $\gcd$。再枚举 $\gcd$ 的倍数计算。

我们再处理出每一个数的倍数中，出现在数列中的数的 $d$ 的最小值及其位置。就可以非常方便地计算了。

注意到一个细节就是倍数不一定符合 $\gcd$ 的条件。

但其实这里不影响，因为如果不符合 $\gcd$ 的话就一定是 $\gcd$ 的因数。只会使答案更小而不会影响。

如果有人会这题最小改为最大的做法可以私信教我一下 /kk。

---

## 作者：Cells (赞：1)

#### 写在前面

看不懂其他题解和代码请看这。

感谢 [傅思维 666](https://www.luogu.com.cn/user/175131) 大佬的思路。

#### 暴力

根据题意在模拟一下能够很轻松地得出一个式子：

$$
d_{x, y} = cnt_{\frac{x}{\gcd(x, y)}} + cnt_{\frac{y}{\gcd(x, y)}}
$$

其中 $cnt_x$ 数组为 $x$ 的质因数个数，注意**不是不同**的质因数，相同的多个质因数也要算，也就是那个质因数指数和。

为什么呢？

因为相同的质因数部分我们不需要动，只需要在不同的质因数部分改动，这就是取最大公约数的原因。

质因数个数在线性筛的时候就可以预处理了。

然后能写出 40 pts 的 $O(n^2)$ 暴力。

#### 优化

我们在细看一下上面的式子，发现它可以写成这个：

$$
d_{x, y} = cnt_x + cnt_y - 2 \times cnt_{\gcd(x, y)}
$$

因为原式减少了 $2$ 个 $cnt_{\gcd(x, y)}$，所以可以这样写。

这里我莫名想到了三维偏序的 CDQ 分治做法，回想一下，不就是把一维排序掉，剩下的再用树状数组拍掉一维，最后统计吗？三元问题一般就是这样，枚举一个不行，就尝试优化或者变枚举的东西。那对于每一个 $x$，我们尝试枚举 $\gcd(x, y)$。

对于序列 $a$，枚举每个 $a_i$ 的因数，尝试将其作为 $\gcd$，此时两个数都已确定，那找一个 $\gcd \mid a_j$，并且 $cnt_{a_j}$ 最小。另外要求 $i \not = j$，所以还需要次小值。

对于每个 $a_i$ 我们枚举因数，把上述式子的值计算出来即可。

#### Code

```c++
# include <bits/stdc++.h>
# define eb emplace_back
# define rep(i, a, b) for(int i = (a); i <= (b); ++ i)
using namespace std;

using LL = long long;

const int N = 1e5 + 10, P = 8e4 + 10, AI = 1e6 + 10, INF = 0x3f3f3f3f;

int n, ans, tot, minn, maxx;
int a[N], cnt[AI], min1[AI], min2[AI], prime[P];//min1 最小值的下标，min2 次小值的下标 

vector<int> fct[N];//储存因数，就不用再次 sqrt(n) 枚举了 

void get_prime(int n){//线性筛 
	rep(i, 2, n){
		if(!cnt[i]) cnt[i] = 1, prime[++ tot] = i;
		for(int j = 1; prime[j] * i <= n; j ++){
			cnt[i * prime[j]] = cnt[i] + 1;//多了 prime[j] 这个质数 
			if(i % prime[j] == 0) break;
		}
	}
}

void update(int i, int gcd){//更新 
	if(cnt[a[i]] < cnt[a[min1[gcd]]]) min2[gcd] = min1[gcd], min1[gcd] = i;//记得更新 min2 
	else if(cnt[a[i]] < cnt[a[min2[gcd]]]) min2[gcd] = i;
}

void query(int i, int gcd){//查询 
	int j = min1[gcd] == i ? min2[gcd] : min1[gcd];
	int val = cnt[a[i]] + cnt[a[j]] - 2 * cnt[gcd];
	if(val < minn || (val == minn && j < ans)) minn = val, ans = j;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	
	cnt[0] = INF;
	
	cin >> n;
	rep(i, 1, n){
		cin >> a[i];
		maxx = max(maxx, a[i]);
	}
	
	get_prime(maxx);
	
	rep(i, 1, n){
		for(int j = 1; j * j <= a[i]; j ++){
			if(a[i] % j) continue;
			fct[i].eb(j);
			update(i, j);
			if(j * j == a[i]) continue;//刚好相等可能会把次小值也变成最小值 
			update(i, a[i] / j);
		}
	}
	
	rep(i, 1, n){
		minn = INF;
		
		for(int x : fct[i]){
			query(i, x);
			if(x * x == a[i]) continue;
			query(i, a[i] / x);
		}
		
		cout << ans << "\n";
	}
	
	return 0;
}
```

如有错误欢迎指出。

**感谢观看！！！**

---

