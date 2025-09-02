# Counting swaps

## 题目描述

给定一个排列 $p_1, \ldots, p_n$，它是数字 $1$ 到 $n$ 的一个排列。在每一步中，你可以选择两个数字 $x < y$ 并交换 $p_x$ 和 $p_y$。

设 $m$ 为将给定排列排序所需的最小交换次数。计算恰好用 $m$ 次交换来排序给定排列的不同序列的数量。由于这个数量可能很大，计算它对 $10^9 + 9$ 取模的结果。

## 说明/提示

在第一个测试用例中，我们可以通过两次交换来排序排列。我们可以任意进行第一次交换；对于每种情况，恰好有一种最佳的第二次交换。例如，三个最短解之一是“交换 $p_1$ 和 $p_2$，然后交换 $p_1$ 和 $p_3$”。

在第二个测试用例中，最佳解涉及交换 $p_1$ 和 $p_2$，以及交换 $p_3$ 和 $p_4$。我们可以以任意顺序进行这两次交换。

第三个序列已经排序。最佳交换次数为 $0$，因此唯一的最佳解是空的交换序列。

题目来源：[IPSC2016](https://ipsc.ksp.sk/2016/real/problems/c.html)

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
3

3
2 3 1

4
2 1 4 3

2
1 2```

### 输出

```
3
2
1```

# 题解

## 作者：基地A_I (赞：33)

[博客园阅读地址](https://www.cnblogs.com/BaseAI/p/12221703.html)

# **Problem**

[ACwing 题目地址](https://www.acwing.com/problem/content/214/)

[洛谷 题目地址](https://www.luogu.com.cn/problem/P4778)

经典题，好题。另外感谢 Rose_max 大佬的博客让我搞懂了这题。

---

# **Solution 1**

对于一个排列 $p_1,p_2,...,p_n$，每一个 $p_i$ 向 $i$ 连一条无向边，构成一张由若干个简单环组成的无向图。目标状态即 $n$ 个自环。

> 引理：将一个大小为 $k$ 的简单环变成 $k$ 个自环，至少需要 $k-1$ 次交换。

利用数学归纳法，证明很简单，这里省略证明。

由此我们可以得到一个推论：**假设图中有 $k$ 个环，那么最小交换步数是 $n-k$。**

---

下面我们来考虑计数。

设 $f[i]$ 表示一个大小为 $i$ 的环，在保证交换次数最少的情况下，**有多少种方法**将其变成目标状态。

**每一次交换可以把大小为 $i$ 的环拆成大小为 $x,y$ 的两个环，$x+y=n$**。设 $T(x,y)$ 表示**有多少种交换方法**可以将一个大小为 $i$ 的环拆成两个大小分别为 $x,y$ 的环。可以发现：当 $x=y$ 时，有一半的方法是重复的，$T(x,y)=x$；否则 $T(x,y)=x+y$。

将一个大小为 $i$ 的环拆成大小为 $x,y$ 的两个环后，$x$ 环需要 $x-1$ 次交换达到目标状态，将这 $x-1$ 次操作记为 $x-1$ 个 $0$，同理将 $y$ 环的 $y-1$ 次操作记为 $y-1$ 个 $1$。**由于 $x$ 环与 $y$ 环的操作互不干扰，两边的操作可以随意排列，因此这里就是一个多重集的全排列**。

综上所述，可以得到 $f[i]$ 的状态转移方程：

$$f[i]=\sum_{x+y=i} f[x]*f[y]*T(x,y)*\frac{(i-2)!}{(x-1)!(y-1)!}$$

（或许这个式子可以 $FFT$ 一下，如果你可以将其 $FFT$，记得告诉我一下做法qwq）

---

假设排列 $p_1,p_2,...,p_n$ 中有 $k$ 个大小分别为 $L_1,L_2,...,L_k$ 的环。**因为这 $k$ 个环的操作互不干扰**，可以记其中第 $i$ 个环的 $L_i-1$ 次操作为 $L_i-1$ 个 $i$，**总操作就是一个多重集的全排列**。答案是：

$$Ans=(\prod_{i=1}^k f[L_i])*(\frac{(n-k)!}{\prod_{i=1}^k (L_i-1)!})$$

在 $\mod 10^9+9$ 意义下，上述除法可以用费马小定理求得逆元解决。复杂度带一个 $\log$。

**时间复杂度：$O(n^2 \log n)$**

求 $f[\ ]$ 数组和阶乘部分代码（预处理）

```cpp
void Init() {
	fc[0] = 1;	//阶乘 factorial
	for(int i=1;i<=1000;++i) fc[i] = fc[i-1] * i % mod;
	f[1] = 1;
	for(int i=2;i<=1000;++i) {
		for(int j=1;j<=i/2;++j) {	// (x,y)和(y,x)只能算一次 
			int inv = Pow(fc[i-j-1]*fc[j-1]%mod, mod-2);
			f[i] = (f[i] + f[i-j]*f[j]%mod*T(i-j,j)%mod*fc[i-2]%mod*inv%mod) % mod;
		}
	}
	for(int i=1;i<=10;++i) printf("%lld\n",f[i]);
}
```

# **Solution 2**

注意到上述算法并不能通过此题（$n \leqslant 10^5$）。瓶颈在于求 $f[\ ]$ 数组这里。于是我们打表出 $f[\ ]$ 数组的前 $10$ 项：

``1 1 3 16 125 1296 16807 262144 4782969 100000000``

将其输入进 $OEIS$，或者是对乘方敏感的同学可以发现：$f[n]=n^{n-2}$。有了这个规律，我们便可以解决这个问题了。

**时间复杂度：$O(n \log n)$**

# **Code**

Talk is cheap.Show me the code.

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read() {
	int x=0,f=1; char ch=getchar();
	while(ch<'0' || ch>'9') { if(ch=='-') f=-1; ch=getchar(); }
	while(ch>='0'&&ch<='9') { x=(x<<3)+(x<<1)+(ch^48); ch=getchar(); }
	return x * f;
}
const int N = 1e5+7, mod = 1e9+9;
int n,cnt,ans;
int p[N],f[N],fc[N],L[N];
bool vis[N];
int Pow(int x,int y) {
	int res = 1, base = x;
	while(y) {
		if(y&1) res = res*base%mod; base = base*base%mod; y >>= 1;
	}
	return res;
}
void Init2() {
	fc[0] = 1;
	for(int i=1;i<N;++i) fc[i] = fc[i-1] * i % mod;
	f[1] = 1;
	for(int i=2;i<N;++i) f[i] = Pow(i,i-2);
}
int Dfs(int u) {
	vis[u] = 1;
	if(vis[p[u]]) return 1;
	return Dfs(p[u]) + 1;
}
void work() {
	cnt = 0;
	memset(vis, 0, sizeof(vis));
	n = read();
	for(int i=1;i<=n;++i) p[i] = read();
	for(int i=1;i<=n;++i)
		if(!vis[i]) L[++cnt] = Dfs(i);
	ans = fc[n-cnt] % mod;
	for(int i=1;i<=cnt;++i) {
		int inv = Pow(fc[L[i]-1], mod-2);
		ans = ans*f[L[i]]%mod*inv%mod;
	}
	printf("%lld\n",ans);
}
signed main()
{
	Init2();
	int T = read();
	while(T--) work();
	return 0;
}
```

# **Summary**

~~模数看错自闭一中午~~，所以大家在任何地方都要细心呀！！

这个题目让我学会两大经典模型：

- **将排列 $p_1,p_2,...,p_n$ 变成递增序列的最小交换次数。**

- **将排列 $p_1,p_2,...,p_n$ 变成递增序列，保证最小交换次数下的方案数**

另外让我学会一些计数题的 **技巧/思路/套路**。

---

## 作者：Mr_Wu (赞：20)

对每个 $i$ 向 $p_i$ 连边，表示初始在位置 $i$ 上的数想到位置 $p_i$ 上去。这样得到若干个环。明显环间交换不优，所以我们只需考虑一个环的最优交换次数，然后用组合数给所有环的操作序列分配标号。对于一个环，考虑对于它表示的序列交换两个数后，环会分裂成两个小环。因此可以得出大小为 $n$ 的环的最优交换次数 $f_n$ 的递推式（当两点距离为 $\frac{n}{2}$ 时选法是 $\frac{n}{2}$，其它都是 $n$。用 $\binom{n-2}{i-1}$ 分配两个环的操作的标号）
$$
f_1=1,f_n=\sum_{i=1}^{\lfloor \frac{n}{2}\rfloor} \binom{n-2}{i-1}f_if_{n-i}(2i==n?\frac{n}{2}:n)
$$
（这个递推式对结论的证明没有用处）

这个式子可以分治 FFT 求、也可以牛顿迭代，但这并不是重点，重点是大多数题解提出但没有证明的结论 $f_n=n^{n-2}$（这就是有标号无根树个数！）。为此我咨询了大佬 $\text{S}\color{red}\text{aInT7}$，得到了基于构造双射法的组合意义证明：

每次操作 $p_x,p_y$ 时，在一个图 $G$ 中加一条边 $(x,y)$，由上面的讨论知道这是一棵树。一个尝试是将每种操作与它对应的树建立双射，但这显然是错的，因为很容易举出例子发现相同的操作集合但不同的操作顺序得到了相同的树。但是我们注意到确定一棵树以及确定了 $n-1$ 条边的删除顺序后（这样的组合对象有 $n^{n-2}(n-1)!$ 种），我们可以倒序操作，倒着 swap，那么每次就是对于两个环在环间交换元素，容易发现这会使两个环合成一个大环，因此存在一个唯一的环使得这个操作是合法的。因此，我们对于每个环的所有合法操作，将其与边有顺序的有标号无根树建立了双射。而显然对于每个环合法操作都是相同的，所以对于单个环合法操作个数为 $\frac{n^{n-2}(n-1)!}{(n-1)!}=n^{n-2}$。

另外顺便提一下，这题的复杂度它应该是 $O(n)$ 的。只需不提前预处理 $f_n$，而是在每次用到的时候算。







---

## 作者：star_magic_young (赞：14)

~~计数套路题?但是我连套路都不会,,,~~

拿到这道题我一脸蒙彼,,,感谢 @poorpool 大佬的博客的指点

先将第$i$位上的数字$p_i$向$i$连无向边,然后构成了一个有若干环组成的无向图,可以知道某个点包含它的有且仅有一个环,因为所有点度数都为2(自环的点度数也是2吧qwq)

那么我们的最终目标就是把这个图转换成有$n$个自环的图,相当于把排列排好顺序

考虑对于一个$m$个点的环,把它变成$m$个自环至少需要$m-1$步(相当于排列$(2,3...m,1)$变成$(1,2,3...m)$,这至少需要$m-1$次交换)

设把一个$m$个点的环变成$m$个自环的方案数为$f_m$.因为一次操作可以把一个环拆成两个环,设拆出来两个环大小为$x,y$,那么拆环的方案数$g(x,y)$为$$g(x,y)=\begin{cases}x,\quad (x=y)\\x+y, \quad others\end{cases} $$

就是对于每一个点,有两个点使得这一个点和那两个点中的一个进行交换操作可以分出大小为$x,y$的环,因为点对会被计算2次,所以方案为$\frac{(x+y)*2}{2}=x+y$,如果$x=y$,那么那两个点是同一点,所以方案要除以2

每个环之间的操作是不会相互影响的,所以可以交错进行操作,两个环贡献答案给一个大环时,两个环的操作交错所构成的排列数就是可重集的排列数(总元素个数阶乘除以每一中元素个数阶乘).综上,我们可以知道$$f_m=\sum_{i=1}^{\lfloor\frac{m}{2}\rfloor} g(i,m-i)f_if_{m-i}\frac{(m-2)!}{(i-1)!(m-i-1)!}$$

我们可以找出$k$个大小为$a_1,a_2...a_k$的环

把所有环的答案合并,同样每个环之间的操作是不会相互影响的,所以方案数要乘上一个可重集的排列数,可以得到$$ans=\prod_{i=1}^{k}  f_{a_i}*\frac{(n-k)!}{\prod_{i=1}^{k}(a_i-1)!}$$

(注意边界,$f_1=f_2=1$)

然而求$f$要$O(n)$的时间,总复杂度为$O(nk)$

考虑优化此算法,通过~~打表找规律~~可以发现$f_i=i^{i-2}$

然后求$f$只要要$O(logn)$了,爽!

然后就可以偷税的写代码了

```cpp
// luogu-judger-enable-o2
#include<bits/stdc++.h>
#define LL long long
#define il inline
#define re register

using namespace std;
const LL mod=1000000009;
il LL rd()
{
    re LL x=0,w=1;re char ch;
    while(ch<'0'||ch>'9') {if(ch=='-') w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') {x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
    return x*w;
}
int to[200010],nt[200010],hd[100010],tot=1;
int vis[200010],a[100010],tt;
LL jc[100010],cj[100010];   //不要问我为什么把阶乘数组的逆元写成cj(逃
bool v[100010];
il void add(int x,int y)
{
  ++tot;to[tot]=y;nt[tot]=hd[x];hd[x]=tot;
  ++tot;to[tot]=x;nt[tot]=hd[y];hd[y]=tot;
}
il void dfs(int x,int o,int h)
{
  if(!v[x]) ++a[o];v[x]=true;
  for(int i=hd[x];i;i=nt[i])
    {
      if(vis[i]==h) continue;
      vis[i]=vis[i^1]=h;
      dfs(to[i],o,h);
    }
}
il LL ksm(LL a,LL b)
{
  if(b<=0) return 1;    //i=1时,i-2会为-1 qwq
  LL an=1;
  while(b)
    {
      if(b&1) an=(an*a)%mod;
      a=(a*a)%mod;
      b>>=1;
    }
  return an;
}

int main()
{
  jc[0]=cj[0]=1;
  for(int i=1;i<=100000;i++) jc[i]=(jc[i-1]*i)%mod,cj[i]=ksm(jc[i],mod-2);
  int T=rd();
  for(int h=1;h<=T;h++)
  {
    tot=1;tt=0;
    memset(a,0,sizeof(a));
    memset(v,0,sizeof(v));
    memset(hd,0,sizeof(hd));
    int n=rd();
    for(int i=1;i<=n;i++) add(i,rd());
    for(int i=1;i<=n;i++)
      if(!v[i]) dfs(i,++tt,h);
    LL ans=jc[n-tt];
    for(int i=1;i<=tt;i++) ans=((ans*ksm(a[i],a[i]-2))%mod*cj[a[i]-1])%mod;
    printf("%lld\n",ans);
  }
  return 0;
}

  

```

---

## 作者：良心WA题人 (赞：12)

# 原题链接
[洛谷 P4778](https://www.luogu.com.cn/problem/P4778)

[AcWing 212](https://www.acwing.com/problem/content/214/)
# 题目分析
虽然要求的是方案数，但是最好还是先把至少需要几步弄好了再说。题目中每一个点都要到另一个点，不妨给这两个点连一条边。现在我给出一下样例：
$$6:2　1　3　5　6　4$$
我们会得到如下图：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201129154534174.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NDA0MzY2OA==,size_16,color_FFFFFF,t_70#pic_center)

请注意，其中结点$3$是自环。不难发现，每一个连通块都一定是一个简单环，因为每个点都只有一个出度、一个入度。我们的目标就是通过改变一些边使得原图变成$n$个自环。所以原问题就是分裂这些环，设环大小为$a$，所以每个环至少需要$a-1$步分裂成自环。
# 尝试在图中操作
现在我们来看一看某一个环中交换两个点会发生什么：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201129155132753.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NDA0MzY2OA==,size_16,color_FFFFFF,t_70#pic_center)

上图对应序列$2　3　4　5　1$。接下来我们更换位置$2$和位置$3$（序列$2　4　3　5　1$）：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201129155411917.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NDA0MzY2OA==,size_16,color_FFFFFF,t_70#pic_center)

发现刚好把原图分成了两个环，让剩余的步数更少了。现在我们再看一看交换两个环上的点会发生什么：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201129155931770.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NDA0MzY2OA==,size_16,color_FFFFFF,t_70#pic_center)

原图对应序列$3　1　2　5　6　4$现在我们交换位置$1$和$4$（序列$5　1　2　3　6　4$）：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201129160315843.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NDA0MzY2OA==,size_16,color_FFFFFF,t_70#pic_center)

发现我们把两个环变成了一个环，让需要交换的步数更多了！
# 性质的证明
我们刚刚画了图思考了一下，发现好像只有交换环内的点更优。那是不是一定如此呢？不难发现任意的序列都唯一对应一个只含简单环且没有环外边的图，任意的只含简单环且没有环外边的图都唯一对应一个序列。所以我们现在来分析图的性质，图的性质就是序列的性质。
如果交换了两个点$a$和$b$，其数值分别为$c$和$d$，那么就断掉了$a\to b$和$c\to d$的边，然后连接$a\to d$和$b\to c$。如果原来$a$和$b$在一个环内，就会断掉两条环上的边，然后就会形成了两条链，接着连接了两条边，不难发现这两条边连接的都是两条链的起点和终点，所以一定会分裂。如果$a$和$b$是两个环上的点，那就会分别断掉两个环，新连接的两条边就会连接成一个环。所以选择环内的任意两点交换都是可以的。
# 初步的dp
现在我们来考虑如何算出来这个方案数。首先我们先针对单个环处理。设$f_i$表示大小为$i$的环，其中$f_1=1$。一个环可以分成两个环，所以我们可以枚举这两个环的大小。然后选择两个点来分割，不难看出可以找到$n$个分割的方案。但是请注意，如果分割的两部分大小一样就会出现重复，只有$\frac{n}{2}$个分割方案。设$T$表示分割的方案数，则有状态转移方程：
$$f_i=\displaystyle\sum_x^{\frac{n}{2}}f_x\times f_{n-x}\times T$$
但是请注意，这个状态转移方程并不对！我们分割出来的两个集合并没有先后顺序，所以可以两个集合的操作可以混乱得放在一起，只需要保证两个集合内部是有序的。因为一个集合处理至少需要$x-1$步，所以$01$串的长度为$n-2$。现在我们先假设吉和内部也可以随意摆放，所以方案数就是$(n-2)!$。然后单个集合内只能有序，$1$种方案，但是第一个集合内随意摆放产生了$(x-1)!$个方案，除法计算即可。另一个集合同理。得到最终的状态转移方程：
$$f_i=\displaystyle\sum_{x=1}^{\frac{n}{2}}f_x\times f_{n-x}\times T\times \frac{(n-2)!}{(x-1)!(n-x-1)!}$$
现在思考一下答案是什么。因为整体会有很多的环，所以每个环都要乘起来。因为答案中两个集合的顺序也可以打乱，设有$k$个环，每个环的大小为$l_i$，所以答案为：
$$ans=\displaystyle\prod_{i=1}^kf_{l_i}\times\frac{(n-k)!}{\displaystyle\prod_{j=1}^k[(l_j-1)!]}$$

# 超时的处理
但是以上的状态转移方程算$f$是$\Theta(n^2)$的，会超时。但是我们可以先看一看$f$数组算出来有什么特点：
$$1　1　3　16　125　1296　16807　262144　4782969　100000000...$$
发现了什么？你没发现？放到$OEIS$上看看：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201129182942523.png#pic_center)

$OEIS$告诉我们，这串数列是$n^{n-2}$。所以，$f$数组的处理直接变成了$\Theta(n\log n)$。
# 最后的问题：寻找环
因为本题只有简单环，直接$dfs$就能很快地找到，时间复杂度只有$\Theta(n)$。应该不会有人不会用$dfs$找环吧？不会的详见代码
# 题目代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int NN=1e5+4,P=1e9+9;
int f[NN],inv[NN],a[NN],l[NN];
bool vis[NN];
int qmi(int a,int b)
{
    int res=1;
    while(b)
    {
        if(b&1)
            res=1ll*res*a%P;
        a=1ll*a*a%P;
        b>>=1;
    }
    return res;
}
int dfs(int u)
{
    vis[u]=true;
    if(vis[a[u]])
        return 1;
    return dfs(a[u])+1;
}
int main()
{
    inv[0]=f[1]=1;
    for(int i=1;i<NN;i++)
        inv[i]=1ll*inv[i-1]*i%P;
    for(int i=2;i<NN;i++)
        f[i]=qmi(i,i-2);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        memset(vis,false,sizeof(vis));
        int n,cnt=0;
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        for(int i=1;i<=n;i++)
            if(!vis[i])
                l[++cnt]=dfs(i);
        int ans=inv[n-cnt];
        for(int i=1;i<=cnt;i++)
            ans=1ll*ans*f[l[i]]%P*qmi(max(1,inv[l[i]-1]),P-2)%P;
        printf("%d\n",ans);
    }
    return 0;
}
```

---

## 作者：Adove (赞：7)

我来说下这题的一个小技巧

我们知道一个数对应有且仅有一个位置，且一个位置有且仅有一个数

这就意味着整个图上每个点入度出度都为1

也就意味着图上的环都是简单环

于是DFS找环并统计长度可以用很简单的代码实现

```cpp
int dfs(int x)
{
	vis[x]=1;
	if(vis[a[x]]) return 1;
	return dfs(a[x])+1;
}
```

---

## 作者：Register_int (赞：4)

把数列中每个元素与他的位置连边。容易发现，目标状态就是让图中只有自环。  
考虑一次交换对环的影响。把交换映射到图上，我们可以发现他的过程是这样的：  
第一步：删边。  
![](https://cdn.luogu.com.cn/upload/image_hosting/zbrbrgtn.png)  
第二部：重连。  
![](https://cdn.luogu.com.cn/upload/image_hosting/m340sshc.png)  
由于每次最多删除两条边，所以只能将环上相邻的部分分割开。因此，每一步分裂一个环，设环长度为 $n$，则最少步数为 $n-1$。  
~~为了拒绝 OEIS，我决定手推结果~~  
把每次交换影响的两个点连起来。首先，很明显不能成环，不然不换肯定比换优。其次，总边数为 $n-1$。结合以上两条便可得出：这是一个树形结构。虽然在树中的任意两条边不能交叉，而且，因为操作顺序原因，也会多出来个别情况。比如以下两种：  
![](https://cdn.luogu.com.cn/upload/image_hosting/jerm45iu.png)![](https://cdn.luogu.com.cn/upload/image_hosting/00uxefct.png)  
但是，通过将交叉的边重连，我们可以发现，不可能的情况与重复的情况之间存在一一对应。方案抵消，我们就可以按照正常的情况统计方案数。  
那么答案就很明显了。根据 $\text{Cayley}$ 公式，总方案数就是 $n^{n-2}$。 
单个环的情况解决了。我们统计图上所有的环，逐个统计。设第 $i$ 个环的长度为 $l_i$，交换的方案数为 $f_i$，环的数量为 $k$，那么根据乘法原理与可重集的排列数，可以推出答案为：  
$$(n-k)!\prod^k_{i=1}f_i\frac1{(l_i-1)!}$$
复杂度 $O(n\log n)$，完结撒花。
# AC 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int mod = 1e9 + 9;
const int MAXN = 1e5 + 10;

inline 
ll qpow(ll b, ll p) {
	ll res = 1;
	while (p) {
		if (p & 1) res = res * b % mod;
		b = b * b % mod, p >>= 1;
	}
	return res;
}

ll frc[MAXN], ifrc[MAXN];

inline 
void init(int n) {
	frc[0] = 1;
	for (int i = 1; i <= n; i++) frc[i] = frc[i - 1] * i % mod;
	ifrc[n] = qpow(frc[n], mod - 2);
	for (int i = n - 1; ~i; i--) ifrc[i] = ifrc[i + 1] * (i + 1) % mod;
}

int n, a[MAXN];

bool vis[MAXN];

inline 
ll calc(int k) {
	int cnt = 1; vis[k] = 1;
	for (int i = a[k]; i != k; i = a[i]) cnt++, vis[i] = 1;
	return cnt == 1 ? 1 : qpow(cnt, cnt - 2) * ifrc[cnt - 1] % mod;
}

int t;

ll ans, k;

int main() {
	init(1e5);
	for (scanf("%d", &t); t--;) {
		memset(vis, 0, sizeof vis);
		scanf("%d", &n), ans = 1, k = 0;
		for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for (int i = 1; i <= n; i++) {
			if (!vis[i]) ans = ans * calc(i) % mod, k++;
		}
		printf("%lld\n", ans * frc[n - k] % mod);
	}
}
```

---

## 作者：灵华 (赞：4)

# P4778 Counting swaps

[**My blogs**](https://www.cnblogs.com/linghuabaobao/p/15516909.html)

[题目链接](https://www.luogu.com.cn/problem/P4778)

## 题意：
给出一个 $1\sim n$ 的排列，问将其变成 $1\sim n$ 的最少次数的方案数为多少。

## 解法：

首先对于一个排列，将这个位置和这个位置上数字应该在的位置连边，会形成若干个环，统计每个环上的点的个数，这个可以用并查集进行维护。

> 引理：对每个环，任意选取两个操作一次，一定会分成两个不相连的环

> 证明：对于每个环上的所有点，都有一个 $from_i$ 和 $to_i$ 分别表示哪个位置上的点应该到这里和这个位置上的点应该到哪里。其中 $from_i$ 和 $to_i$ 是两个对于 $1\sim n$ 的排列，且没有任意一个子序列的 $from_{i-j}$ 和 $to_{i-j}$ 的值域相等。而如果交换其中两个数，会交换这两个位置上的 $to_i$ 而不会交换 $from_i$。所以，交换一次就会使某子序列上的 $from$ 和 $to$ 的值域相等。

### 然后考虑每个环。

对于一个环，根据上面的理论，要使它上面所有的点都归位，那么至少需要 $n-1$ 次的操作。

### 考虑操作取法：

之后考虑对这 $n-1$ 次操作有几种取法。假设进行完这一次操作后，将这个环分成了 $x$ 和 $y$ 两部分，其中满足 $x + y = n$ ，对于每个点考虑这种分割操作，一共有两种：一种是和这个点 $i$ 的第 $x$ 级 $from$ 交换，可以分割成功；另一种是和这个点 $i$ 的第 $y$ 级 $from$ 交换，可以分割成功（其中这里面要注意的是：每个点的第 $a$ 级 $from$ 就是这个点的 $n-a$ 级 $to$）。

所以我们发现，对于每个点都有两种情况，每种操作的两个点对这次操作分别算一次，所以将一个环分为 $x$ 和 $y$ 两部分的次数 $T(x,y)$ 就为 $\frac{2\times n}{2}=n$。其中，当且仅当一个点的这两种操作交换的其实是同一个点，也就是 $x=y$ 时，才会产生重复的影响，所以此时 $T(x,y)$ 为 $\frac{n}{2}$。

### 考虑操作顺序：

当我们将一个环拆成两个大小为 $x$ 和 $y$ 的两个环后，对 $x$ 这个环还会有 $x-1$ 次操作，对 $y$ 同理，然后对 $x$ 和 $y$ 的操作，但是 $x$ 和 $y$ 互不干扰，所以就可以看成是对 $x-1$ 个 $0$ 和 $y-1$ 个 $1$ 求多重集排序数。

### 统计答案：

假设我们对于个数为 $n$ 的环操作种数有 $f_n$ 种，且分成了 $x$ 和 $y$ 两部分，并且根据乘法原理，分开之后的操作种数就是 $T(x,y)\times f_x\times f_y \times \frac{(n-2)!}{(x-1)!\times(y-1)!}$。

对于 $k$ 个环的题，设每个环上点的个数为 $siz_i$，因为 $k$ 个环之间操作相互不影响，所以可以看成是对于  $k$ 个 $siz_i$ 求多重集排序数，所以最终答案就是 
$$
f_{siz_1}\times f_{siz_2} \times \dots \times f_{siz_k} \times \frac{(n-k)!}{(siz_1-1)!\times(siz_2-1)!\times\dots\times(siz_k-1)! }
$$

对于计算，因为模数 $10^9+9$ 是质数，所以在答案范围内都有关于 $10^9+9$ 这个数的逆元，把除号改为使用逆元计算。复杂度 $O(n^2)$。考虑优化，算法瓶颈在于要枚举 $f_{siz_i}$，导致增加了一个 $n$，但是对于这个 $f_n$，前人告诉了我们 $f_n=n^{n-2}$~~（我也不知道咋来的\bushi）~~。然后就，嗯，$O(n\log n)$ 就可以解决了。


## Code

```cpp
#include <iostream>
#include <cstring>
using namespace std ;

const long long N = 1000005 , M = 1e9 + 9 ;
int cal[N] , n , clr[N] , siz[N] , msiz , a[N] , dt , res , ans ;
bool vis[N] ;

void init ( )
{
	memset ( clr , 0 , sizeof ( clr ) ) ;
	memset ( siz , 0 , sizeof ( siz ) ) ;
	memset ( a , 0 , sizeof ( a ) ) ;
	memset ( vis , 0 , sizeof ( vis ) ) ;
	dt = res = ans = 0 ;
}

int read ( )
{
	char ch = getchar ( ) ;
	int x = 0 ;
	while ( ch < '0' || ch > '9' )
		ch = getchar ( ) ;
	while ( ch >= '0' && ch <= '9' )
		x = x * 10 + ch - 48 , ch = getchar ( ) ;
	return x ;
}

int find ( int x )
{
	if ( x == clr [ x ] )
		return x ;
	return clr [ x ] = find ( clr [ x ] ) ;
}

int qpow ( int x , int y )
{
	if ( y < 1 )
		return 1 ;
	int res = 1 ;
	while ( y )
	{
		if ( y & 1 )
			res = res * 1ll * x % M ;
		x = x * 1ll * x % M ;
		y >>= 1 ;
	}
	return res ;
}

int main ( )
{
	cal [ 0 ] = cal [ msiz = 1 ] = 1 ;
	int T = read ( ) ;
	while ( T -- )
	{
		init ( ) ;
		n = read ( ) ;
		for ( int i = 1 ; i <= n ; ++ i )
			clr [ i ] = i , siz [ i ] = 1 , vis [ i ] = 0 ;
		int msz = 0 ;
		for ( int i = 1 ; i <= n ; ++ i )
		{
			int x = read ( ) ;
			int fi = find ( i ) , fx = find ( x ) ;
			if ( fi != fx )
			{
				clr [ fi ] = fx ;
				siz [ fx ] += siz [ fi ] ;
				msz = max ( msz , siz [ fx ] ) ;
				vis [ fi ] = 1 ;
			}
		}
		dt = 0 ;
		for ( int i = 1 ; i <= n ; ++ i )
			if ( ! vis [ i ] )
				a [ ++ dt ] = siz [ i ] ;
		msz = max ( msz , n - dt ) ;
		if ( msz > msiz )
		{
			for ( int i = msiz + 1 ; i <= msz ; ++ i )
				cal [ i ] = cal [ i - 1 ] * 1ll * i % M ;
			msiz = msz ;
		}
		res = ans = 1 ;
		for ( int i = 1 ; i <= dt ; ++ i )
			res = res * 1ll * cal [ a [ i ] - 1 ] % M , ans = ans * 1ll * qpow ( a [ i ] , a [ i ] - 2 ) % M ;
		ans = ans * 1ll * qpow ( res , M - 2 ) % M * cal [ n - dt ] % M ;
		ans = ( ans % M + M ) % M ;
		printf ( "%lld\n" , ans ) ;
	}
	return 0 ;
}
```

---

## 作者：accomplishment (赞：1)

一道练计数的题。

### 第一步 建图

将每个数和它的目标位置连一条边，形成一个 $n$ 个节点 $n$ 条边的有向图。

例如这组数据：

> 2 4 6 1 5 3

![](https://cdn.luogu.com.cn/upload/image_hosting/17xda8rj.png)

注：图源自@[泥土笨笨](https://www.luogu.com.cn/user/43206) 家的狗豆豆讲课时的课件。

目标就是经过很多次交换将这写环变成 $n$ 个自环。

### 第二步 自环

首先经过尝试，长度为 $1$ 的环不需要操作；长度为 $2$ 的环需要经过 $1$ 次操作；长度为 $3$ 的环需要经过 $2$ 次操作……

因此可以假设，长度为 $k$ 的环需要 $k-1$ 次操作。

那么我们可以用数学归纳法证明，现在考虑有 $k$ 个节点的环，在环上选择任意两点交换，会发现环会被分成两个具有 $x$ 个节点和 $k-x$ 个节点的环。

所以就需要操作 $(x-1)+(k-x-1)+1=k-1$ 次操作，假设成立。

![](https://cdn.luogu.com.cn/upload/image_hosting/tb9okbl2.png)

注：图源自@[泥土笨笨](https://www.luogu.com.cn/user/43206) 家的狗豆豆讲课时的课件。

### 第三步 还原

设 $f_k$ 表示把长度为 $k$ 的环变成 $k$ 个自环的方案数。设 $t(x,y)$ 表示一次交换之后，把长度为 $n$ 的环拆成长度分别为 $x$ 和 $y$ 的环的方案数。

首先若 $x=y$，$n$ 必须为偶数，选择任意一个点都可以选择对面的一个点，不考虑相反选择顺序的方案数有 $n$ 种，考虑重复的选择，共有 $\frac{n}{2}$ 种方案。

若 $x \neq y$，选择任意一个点都有两侧的两个点可以选择，不考虑相反选择顺序的方案数有 $2n$ 种，考虑重复的选择，共有 $n$ 种方案。

$$t(x.y)=\begin{cases}\frac{n}{2}&x = y\\n&x \neq y\end{cases}$$

那么长度为 $k$ 的环，分成 $x$ 和 $y$ 两部分后，拆成的方案数为 $t(x, y)$，各自需要的步骤分别为 $x-1$ 和 $y-1$，各自的方案数为 $f_x$ 和 $f_y$。那么总的方案就是 $x$ 的方案（相当于内部相同）和 $y$ 的方案（相当于内部相同），就是一个多重集的排列数 $\frac{(n-2)!}{(x-1)!(y-1)!}$，将这些分步的步骤乘起来就是 $f_k$，即：

$$f_k=\sum\limits_{x+y=k}^{}t(x,y)f_xf_y\frac{(k-2)!}{(x-1)!(y-1)!}$$

那么有了这个式子就可以用 $O(n^2)$ 的时间复杂度求出 $f_k$，但是一看数据范围 $n \leq 10^5$，明显过不了，那么我们可以打表打出来这个数组的前几项。

> 1 1 3 16 125 1296 16807 262144

求助 [OEIS](http://oeis.org/)，发现是 A000272：Number of trees on n labeled nodes: $f_n = n^{n-2}$。

那么我们就可以用快速幂在 $O(\log n)$ 的时间复杂度内求出 $f_k$。

### 第四步 计数

最终，如果原始排列由 $a$ 个环构成，长度分别为 $l_1, l_2, \cdots, l_a$，答案即为每个环的方案数乘上这些方案的多重集排列数，即：

$$\prod\limits_{i=1}^a f_{l_i} \times \frac{(n-a)!}{\prod\limits_{i=1}^a (l_i - 1)!}$$

就可以在 $O(n \log n)$ 的时间复杂度内求出答案。

### Code:

```cpp
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const int MAXN = 1e5 + 9;
const int mod = 1e9 + 9;

int _maxi = 0;
int _myArray[MAXN];
bool _visArray[MAXN];
int _circleArray[MAXN];
long long _facArray[MAXN];
long long _invArray[MAXN];
long long _res = 0;

long long QuickPow (long long base, long long index) {
	
	long long res = 1;
	
	while (index) {
		if (index & 1) {
			res = res * base % mod;
		}
		 
		base = base * base % mod;
		index >>= 1;
	}
	
	return res;
	
}

void Init () {
	
	_facArray[0] = 1;
	
	for (int i = 1; i < 1e5 + 1; i++) {
		_facArray[i] = _facArray[i - 1] * i % mod;
	}
	
	_invArray[100000] = QuickPow(_facArray[100000], mod - 2);
	
	for (int i = 1e5 - 1; i > -1; i--) {
		_invArray[i] = _invArray[i + 1] * (i + 1) % mod; 
	}
	
}

int Dfs (int cur) {
	
	_visArray[cur] = 1;
	
	if (_visArray[_myArray[cur]]) {
		return 1;
	}
	
	return Dfs(_myArray[cur]) + 1;
	
}

int main () {
	
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	
	int codeNum = 0;
	
	Init();
	
	cin >> codeNum;
	
	while (codeNum--) {
		memset(_myArray, 0, sizeof(_myArray));
		memset(_visArray, 0, sizeof(_visArray));
		memset(_circleArray, 0, sizeof(_circleArray));
		
		cin >> _maxi;
		
		for (int i = 1; i < _maxi + 1; i++) {
			cin >> _myArray[i];
		}
		
		int tot = 0;
	
		for (int i = 1; i < _maxi + 1; i++) {
			if (!_visArray[i]) {
				_circleArray[++tot] = Dfs(i);
			}
		} 
		
		_res = _facArray[_maxi - tot];
		
		for (int i = 1; i < tot + 1; i++) {
			if (_circleArray[i] > 1) {
				_res = _res * QuickPow(_circleArray[i], _circleArray[i] - 2) % mod;	
				_res = _res * _invArray[_circleArray[i] - 1] % mod;
			}
		}
		
		cout << _res << '\n';	
	}
	
	return 0;
	
} 
```

---

## 作者：Martian148 (赞：1)

# Link
[P4778 Counting swaps](https://www.luogu.com.cn/problem/P4778)

# Solve
对于一个排列$p_1,p_2,...,p_n$，如果从每个$i$向$p_i$建一条边，显然可以得到一张图，这张图包括若干个环组成（包括自环）。最后的目标序列为$1,2,...,n$，显然由$n$个自环组成。

这里我们有一个引理：

> 把一个长度为$n$的环变成$n$个自环，最少需要$n-1$次操作。

证明：

首先把长度为$2$的环变成$2$个自环，显然需要一种操作。

假设$∀k≤n-1$，把长度不超过$k$的环变成$k$个自环最少需要$k-1$次操作。当$k=n$时，设该环为$v_1→v_2→v_3→...→v_n→v_1$,任意交换$v_i,v_j(i<j)$的出边后，我们得到$v_{i+1}→v_{i+2}→v_{i+3}→...→v_j→v_{i+1}$和$v_{1}→v_{2}→v_{i}→...→v_{j+1}→v_{j+2}→...→v_n→v_1$两个环。

两者的长度分别是$j-i$和$n-(j-i)$。把两者分别拆分成自环的最小交换次数为$j-i-1$和$n-(j-i)-1$两者相加是$n-2$，加上刚才$v_i$和$v_j$的交换，总共需要$n-1$次交换。最后通过数学归纳法可知，原命题成立。

证毕

设$F_n$表示用最少步数把一个长度为$n$的环变成$n$个自环，总共有多少中操作方法。由上面的证明过程可知，把一个长度为$n$的环变成$n$个自环的过程中，可以把该环拆成长度为$x$和$y$的两个环，其中$x+y=n$,设$T(x,y)$表示有多少种交换方法可以把长度为$n$的环变成长度为$x$和$y$的两个环，易得：

$$T(x,y)=\begin{cases}
{n/2,x=y}\\{n,x≠y} \end{cases}$$

另外，两者各自变为自环的方法数为$F_x$和$F_y$，步数为$x-1$和$y-1$。

根据多重集的排列数·加法原理和乘法原理：

$$F_n=\sum_{x+y=n}T(x,y)\ast F_x \ast F_y \ast \dfrac{(n-2)!}{(x-1)!(y-1)!}$$

如果最初的排列$p_1,P-2,...,p_n$由长度为$l_1,l_2,...,l_k$的$k$个环组成，其中$l_1+l_2+...l_k=n$，那么最终答案就是

$$F_{l_1} \ast F_{l_2} \ast ... \ast F_{l_k} \ast \dfrac{(n-k)!}{(l_1-1)! \ast (l_2-1)! \ast ... \ast (l_k-1)!}$$

因为$10^9+9$是一个质数，所以就可以用乘法逆元算上面的除法，整个算法的时间复杂度是$O(n^2)$。事实上，我们可以递推出$F_n$的前几项找规律，数感好的同学应该可以找出规律，或者把前几项输入到$OEIS$网站中，我们都可以得到通项公式$F_n=n^{n-2}$，从而可以用快速幂优化到$O(nlogn)$。

代码不难，数学推理难。
# Code
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int TT=1000000009,maxn=100005;
int N,a[maxn],T,vis[maxn],cnt;
typedef long long LL;
LL ans,Fc[maxn],F[maxn],size[maxn];
int read(){
	int ret=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-f;ch=getchar();}
	while(ch>='0'&&ch<='9') ret=ret*10+ch-'0',ch=getchar();
	return ret*f; 
}
LL Pow(LL a,LL b){
	LL w=a,s=1;
	while(b){
		if(b&1)s=w*s%TT;
		w=w*w%TT;
		b>>=1;
	}
	return s;
}
int main(){
	freopen("P4778.in","r",stdin);
	freopen("P4778.out","w",stdout);
	T=read();
	Fc[0]=1;for(int i=1;i<maxn;i++)Fc[i]=Fc[i-1]*i%TT;
	F[1]=1;for(int i=2;i<maxn;i++)F[i]=Pow(i,i-2);
	while(T--){
		N=read();
		for(int i=1;i<=N;i++)a[i]=read();
		cnt=0;memset(vis,0,sizeof vis);
		int now_x;
		for(int i=1;i<=N;i++)if(!vis[i]){
			now_x=i;int num=0;
			while(!vis[now_x]){vis[now_x]=1;now_x=a[now_x];num++;};
			size[++cnt]=num;
		}
		ans=Fc[N-cnt];
		for(int i=1;i<=cnt;i++){
			LL inv=Pow(Fc[size[i]-1],TT-2);
			ans=ans*F[size[i]]%TT*inv%TT;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：chihik (赞：1)


对于每个位置 $i$ , 我们向 $p_i$ 连一条边。 结合题意可知，一个合法的排列，是一个由 $n$ 个自环组成的图。

但现在会形成多个环，不妨记环的数量为 $k$  ， 第 $i$ 个环的大小为 $s_i$（包括自环）。

我们现在要做的，就是将这 $k$ 个环拆成 $n$ 个自环。

显然，对于一个大小为 $s$ 的环，拆成自环至少需要 $s-1$次操作。

记 $w_n(x,y)$ , 表示将 $n$ 个点的环 ， 拆成 $x$ 个点的环 + $y$个点的环的方案数。

显然有 

$$
w_n(x,y)=
\begin{cases}

\frac{n}{2} & x=y\\

n & x \not= y
\end{cases}
(x+y=n)
$$

记 $f_n$ 表示大小为 $n$ 的环的拆分方案数（$f_1=1$） , 则根据多重集的排列公式得：

$$
f_n=\sum_{x+y=n}^{x \le\frac{n}{2}}w_n(x,y) \times f_x \times f_y \times \frac{ (n-2)! }{(x-1)! (y-1)!}
$$

这样递推的复杂度是 $\Theta(n^2)$ 的 ，给一份代码：

```cpp
f[ 1 ] = 1;
	for( int i = 2 ; i <= MAXN ; i ++ ) {
		for( int x = 1 ; x <= i / 2 ; x ++ ) {
			int y = i - x , t = x == y ? i / 2 : i;
			f[ i ] += t * f[ x ] * f[ y ] * ( Fac[ i - 2 ] / Fac[ x - 1 ] / Fac[ y - 1 ] );
		}
		printf("%d %d\n", i , f[ i ] );
	}
```
经过~~找规律~~，我们发现，$f_i=i^{i-2}$，现在就可以$\Theta(nlogn)$求出$f_i$了。

答案也是一个多重集，可以简单求出
$$
Ans=(\prod_{i=1}^k f[s_i]) \times (\frac{(n-k)!}{\prod_{i=1}^k(s_i-1)!})
$$

```cpp
#include <cstdio>
#include <cstring>
using namespace std;
#define Mod 1000000009

const int MAXN = 100000;
int t , n , p[ MAXN + 5 ] , s[ MAXN + 5 ] , k;
bool vis[ MAXN + 5 ];

int Quick_pow( int x , int po ) {
	int Ans = 1;
	while( po ) {
		if( po % 2 ) Ans = 1ll * Ans * x % Mod;
		x = 1ll * x * x % Mod;
		po /= 2;
	}
	return Ans;
}
int Inv( int x ) {
	return Quick_pow( x , Mod - 2 );
} 

int dfs( int u ) {
	if( vis[ u ] ) return 0;
	vis[ u ] = 1;
	return dfs( p[ u ] ) + 1;
}

int f[ MAXN + 5 ] , Fac[ MAXN + 5 ] , InvFac[ MAXN + 5 ];
void Init( ) {
	f[ 1 ] = 1;
	for( int i = 2 ; i <= MAXN ; i ++ )
		f[ i ] = Quick_pow( i , i - 2 );
	
	Fac[ 0 ] = 1; 
	for( int i = 1 ; i <= MAXN ; i ++ )
		Fac[ i ] = 1ll * Fac[ i - 1 ] * i % Mod;
		
	InvFac[ MAXN ] = Inv( Fac[ MAXN ] );
	for( int i = MAXN - 1 ; i >= 0 ; i -- )
		InvFac[ i ] = 1ll * InvFac[ i + 1 ] * ( i + 1 ) % Mod;
}
int main( ) {
	Init( ); 
	scanf("%d",&t);
	while( t -- ) {
		k = 0;
		memset( vis , 0 , sizeof( vis ) );
		memset( s , 0 , sizeof( s ) );
		
		scanf("%d",&n);
		for( int i = 1 ; i <= n ; i ++ )
			scanf("%d",&p[ i ]);
		for( int i = 1 ; i <= n ; i ++ )
			if( !vis[ i ] ) s[ ++ k ] = dfs( i );
		
		int p1 = 1 , p2 = 1 , p3 = Fac[ n - k ];
		for( int i = 1 ; i <= k ; i ++ ) {
			p1 = 1ll * p1 * f[ s[ i ] ] % Mod;
			p2 = 1ll * p2 * Fac[ s[ i ] - 1 ] % Mod;
		}
		printf("%d\n", 1ll * p1 * Inv( p2 ) % Mod * p3 % Mod );
	}
	return 0;
} 
```


---

## 作者：封禁用户 (赞：0)

一道经典好题。

首先把 $i$ 向 $a_i$ 连边，这就转化成了一个图，可以发现这个图是由若干个环（可能包括自环）组成的。

排序后的序列转化成的图是由 $n$ 个自环组成的，我们可以发现每次操作，如果两点在一个环内，就多一个环；否则，就少一个环。如果我们现在有 $k$ 个环，那至少操作 $n-k$ 次。

对于每个环单独考虑，我们可以把分裂环的操作倒过来地看成合并操作，这样就有了树的结构，仔细分析，我们要求的是有标号无根树的数量，就是 $len^{len-2}$。

然后考虑所有的环，进行集合排列，答案就是 $\prod {\frac{len^{len-2}}{(len-1)!}} \ \times (n-k)!$，其中 $len$ 是各个环的大小。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
template<typename T>inline void read(register T &x)
{
	register T p = 1,num = 0;
	char c = getchar();
	while(c < '0'||c > '9')
	{
		if(c == '-') p = -p;
		c = getchar();
	}
	while('0' <= c&&c <= '9')
	{
		num = (num<<3)+(num<<1)+(c^48);
		c = getchar();
	}
	x = p * num;
}
template<typename T>inline void write(register T x)
{
	if(x < 0) putchar('-'),x = -x;
	if(x > 9) write(x/10);
	putchar(x%10+48);
}
#define D(i,a,b) for(register int i=a;i>=b;--i)
#define F(i,a,b) for(register int i=a;i<=b;++i)
#define min(a,b) ((a<b)?a:b)
#define max(a,b) ((a>b)?a:b)
#define ll long long
#define N 100010
const int mod = 1e9 + 9;
ll fac[N],inv[N],pw[N];
int a[N],t,n;
bitset<N> vis;
inline ll qp(ll x,ll y)
{
	ll ret = 1;
	while(y)
	{
		if(y & 1) ret = ret * x % mod;
		x = x * x % mod;
		y >>= 1;	
	}
	return ret;
}
int main()
{
	fac[0] = fac[1] = inv[0] = inv[1] = 1ll;
	F(i,2,1e5) fac[i] = fac[i-1] * i % mod;
	F(i,2,1e5) inv[i] = 1ll * (mod - mod / i) * inv[mod % i] % mod;
	F(i,2,1e5) inv[i] = inv[i] * inv[i-1] % mod;
	pw[0] = pw[1] = pw[2] = 1ll;
	F(i,3,1e5) pw[i] = qp(i,i-2);
	read(t);
	while(t--)
	{
		ll ans = 1,k = 0;
		vis = 0;
		read(n);
		F(i,1,n) read(a[i]);
		F(i,1,n)
		{
			if(vis[i]) continue;
			int len = 0,p = i;
			while(!vis[p]) vis[p] = 1,p = a[p],++len;
			ans = ans * pw[len] % mod * inv[len-1] % mod;
			++k;
		}
		ans = ans * fac[n-k] % mod;
		write(ans);
		putchar('\n');
	}
	return 0;
}
```


---

