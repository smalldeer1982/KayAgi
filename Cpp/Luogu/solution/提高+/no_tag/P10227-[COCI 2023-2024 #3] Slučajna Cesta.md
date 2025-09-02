# [COCI 2023/2024 #3] Slučajna Cesta

## 题目背景

**译自 [COCI 2023/2024 Contest #3](https://hsin.hr/coci/archive/2023_2024) T5「[Slučajna Cesta](https://hsin.hr/coci/archive/2023_2024/contest3_tasks.pdf)」**

## 题目描述

Vito 住在一个有 $n$ 个公园的城市，这些公园编号为 $1$ 到 $n$。这些公园被 $n-1$ 条道路相连，满足任意两公园之间都存在一条路径。每个公园均有一个美丽值，第 $i$ 个公园的美丽值为 $v_i$。

昨晚 Vito 决定在城市中走走，在他游览完一个公园后，他会等概率随机选择一条路，并游览这条路通往的公园。但在出发前，他透过摩天大楼的窗户看到，每条路上都有一条蓝蛇或红蛇。蓝蛇会攻击所有从编号较小的公园前往编号较大的公园的人，红蛇会攻击所有从编号较大的公园前往编号较小的公园的人。由于 Vito 不想被蛇攻击，他决定改变计划，在随机选择道路时只考虑不会被蛇攻击的道路。因为他喜欢长距离行走，所以在至少有一条路他可以安全通过之前，他不会停下脚步。

当 Vito 下楼时，他完全忘记了哪条路上有红蛇或蓝蛇，于是他想知道：「如果每条路上有蓝蛇或红蛇的概率相同，那么我从第 $i$ 个公园开始的路线的美感的期望是多少？」

一条路线的美感是在这条路线上经过的公园的美丽值的和。路线美感的期望定义为对于所有可能的路线，路线的美感乘以 Vito 按这条路线走的概率的乘积之和。

## 说明/提示

### 样例解释 1

从第一个公园开始的路线的美感的期望是 $2.5\pmod{10^9+7}=\frac{5}{2}\pmod{10^9+7}=5\cdot 2^{-1}\pmod{10^9+7}=5\cdot 500000004\pmod{10^9+7}=500000006\pmod{10^9+7}$，从第二个公园开始的路线的美感的期望是 $2$。

### 样例解释 2

两条蛇都是红蛇的概率是 $\frac{1}{4}$，这种情况下如果 Vito 从第一个公园出发，他会随机选择走哪条路。

### 子任务

| 子任务编号 |              附加限制              | 分值 |
| :--------: | :--------------------------------: | :--: |
|    $1$     |             $n\le 10$              | $9$  |
|    $2$     |           $n\le 1\ 000$            | $27$ |
|    $3$     | 序列 $p_i$ 中没有值出现超过 $2$ 次 | $27$ |
|    $4$     |             无附加限制             | $37$ |

## 样例 #1

### 输入

```
2
1
2 1
```

### 输出

```
500000006
2
```

## 样例 #2

### 输入

```
3
1 1
8 8 8
```

### 输出

```
14
14
14```

## 样例 #3

### 输入

```
11
1 1 1 2 3 4 1 2 6 2
1 1000 5 3 18 200 8 9 0 2 2
```

### 输出

```
968750272
610352580
450521029
536458466
199219275
662760680
190972315
90277951
824219264
941840425
532552597
```

# 题解

## 作者：iyka (赞：10)

### [题目传送门](https://www.luogu.com.cn/problem/P10227)

题目要求我们求出路线的美感的期望，这可以通过 `dfs` 来实现，主要是期望怎么求。在题目中，影响期望值的是蓝蛇和红蛇，而蓝蛇和红蛇的出现概率是一样的，转化一下就是每条路都可以选择走与不走，而且各占 $\frac{1}{2}$ 的概率。

接下来就是计算总的概率了，这里要用到组合数：$\tbinom{n}{r}=\frac{A_m^n}{m!}=\frac{n!}{m!(n-m)!}$。

因为输出要求是 $ab^{-1}\pmod{10^{9}+7}$（期望值形如 $\frac{c}{d}$ 的小数形式，$a=c$ 且 $b=d$）。还要求求出 $b$ 的逆元，所以我们可以用线性逆元预处理出逆元数组，优化时间复杂度。

最终时间复杂度为 $O(N\sqrt{N})$，在洛谷大数据点中不吸氧也最多跑到2.58秒，还是可以接受的。

注：为了防止不必要的麻烦，建议开 `long long` 或者使用 $1ll$ 转换类型，后者空间会小很多。

代码部分：
```cpp
#include<bits/stdc++.h>
using namespace std;
// #define int long long
const int N=1e6+10,mod=1e9+7,invd=5e8+4;
int n,a[N];
int fa[N],son[N],fac[N],ifac[N],f[N],g[N];
int inv[N],ipw[N];
vector<int> way[N];
int qpow(int x,int y)//快速幂
{
	int res=1;
	while(y) 
	{
		if(y&1) 
			res=1ll*res*x%mod;
		x=1ll*x*x%mod, y>>=1;
	}
	return res;
}
void init()//预处理
{
	ipw[0]=fac[0]=inv[1]=1;
	for(int i=1;i<=n;++i)
		ipw[i]=1ll*ipw[i-1]*invd%mod, fac[i]=1ll*fac[i-1]*i%mod;
	ifac[n]=qpow(fac[n],mod-2);
	for(int i=n-1;i>=0;--i)
		ifac[i]=1ll*ifac[i+1]*(i+1)%mod;
	for(int i=2;i<=n;++i)
        inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
}
void add_edge(int x,int y)//加边
{
	way[x].push_back(y);
}
void compare(int &x,int y)
{
	if((x+=y)>=mod)
		x-=mod;
}
int combination(int x,int y)// 组合数
{
	return 1ll*fac[x]*ifac[y]%mod*ifac[x-y]%mod;
}
void dfs(int u)
{
	f[u]=a[u];
	if(!son[u])
		return;
	int tmp=0;
	for(int i=0;i<son[u];++i)
		compare(tmp,1ll*combination(son[u]-1,i)*inv[i+1]%mod);
	tmp=1ll*tmp*ipw[son[u]]%mod;
	for(int v:way[u])
		dfs(v), compare(f[u],1ll*f[v]*tmp%mod);
}
void _dfs(int u)
{
	if(!son[u])
		return;
	int tmp=0,sum=g[u];
	for(int i=0;i<=son[u]-1-(u==1);++i)
		compare(tmp,1ll*combination(son[u]-1-(u==1),i)*inv[i+1]%mod);
	tmp=1ll*tmp*ipw[son[u]-(u==1)]%mod;
	for(int v:way[u])
		compare(sum,f[v]);
	for(int v:way[u])
		g[v]=(1ll*tmp*(sum+mod-f[v])+a[u])%mod, _dfs(v);
}
signed main()
{
	cin>>n;
	init();
	for(int i=2;i<=n;++i)
		cin>>fa[i], add_edge(fa[i],i), son[fa[i]]++;
	for(int i=1;i<=n;++i)
		cin>>a[i];
	dfs(1); _dfs(1);  //遍历路径
	for(int i=1;i<=n;++i)
	{
		if(i==1)
		{
			cout<<f[1]<<endl; 
			continue;
		}
		int ans=a[i],tmp=0;
		for(int j=0;j<=son[i];++j)
			compare(tmp,1ll*combination(son[i],j)*inv[j+1]%mod);
		tmp=1ll*tmp*ipw[son[i]+1]%mod;
		compare(ans,1ll*g[i]*tmp%mod);
		for(int v:way[i])
			compare(ans,1ll*f[v]*tmp%mod);
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：FFTotoro (赞：6)

考虑如何 $O(n)$ 求出结点 $1$ 的答案，然后再使用换根。

现在 Vito 从结点 $1$ 出发（即令根结点为 $1$）。显然同一条边不会被走过两次，因为如果这条边上是红蛇，那么前一个点的编号必然比后一个点小，走回去必然会被攻击，反之依然

对于一个结点 $u$，令 $C_u$ 表示其儿子集合，同时设 $k=|C_u|$，如果从它开始往下走，有 $\dfrac{1}{2^k}$ 的概率所有路都不能走，剩下的 $\dfrac{2^k-1}{2^k}$ 的概率中往每个子结点走的概率相等，即 $\dfrac{2^k-1}{k2^k}$。于是令 $f_u$ 表示从结点 $u$ 往下走的路线美感度的期望（不包括自身的贡献，即 $v_u$），可以得出转移方程：

$$f_u=\sum\limits_{i\in C_u}\frac{2^k-1}{k2^k}(f_i+v_i)$$

前文提到对于每个结点，往所有出边走的概率相等，可以借助这一点进行换根。即对于每个结点**按比例**加入从父亲下传的贡献即可。具体实现可以参考代码。

时间复杂度 $O(n\log P)$，其中 $P=10^9+7$，那个 $\log$ 是求逆元的。

放代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int p=1e9+7;
int qpow(int a,int b){
  int r=1;
  while(b){
    if(b&1)(r*=a)%=p;
    (a*=a)%=p,b>>=1;
  }
  return r;
}
int inv(int x){
  return qpow(x,p-2);
}
int sp(int x){
  return (1-qpow(inv(2),x)+p)*inv(x)%p;
} // 有 x 个儿子时走到单个儿子的概率
main(){
  ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  int n; cin>>n;
  vector<vector<int> > g(n);
  for(int i=1;i<n;i++){
    int f; cin>>f;
    g[f-1].emplace_back(i);
  }
  vector<int> w(n),f1(n),f2(n),r(n);
  for(auto &i:w)cin>>i;
  function<void(int)> dfs1=[&](int u){
    int x=sp(g[u].size());
    for(int i:g[u])
      dfs1(i),(f1[u]+=(f1[i]+w[i])*x%p)%=p;
  }; // 处理出根结点答案
  function<void(int,int)> dfs2=[&](int u,int f){
    int x1=sp(g[u].size()),x2=sp(g[u].size()+1);
    if(u){
      int x3=sp(g[f].size());
      if(f)f2[u]=((f2[f]-f1[u]-w[u]+(p<<1))*x3%p+f1[f]+w[f])%p; // 父亲不是根
      else{
        int x4=sp(g[f].size()-1);
        f2[u]=((f1[f]-(f1[u]+w[u])*x3%p+p)*x4%p*inv(x3)%p+w[f])%p;
      } // 父亲是根
      r[u]=(f2[u]*x2%p+f1[u]*x2%p*inv(x1)%p+w[u])%p;
    }
    else r[u]=(f1[u]+w[u])%p; // 根结点
    for(int i:g[u])dfs2(i,u);
  };
  dfs1(0),dfs2(0,0);
  for(int i:r)cout<<i<<'\n';
  return 0;
}
```

---

## 作者：Add_Catalyst (赞：3)

# P10227 [COCI 2023/2024 #3] Slučajna Cesta 题解

---

## 知识点

期望 DP，树形（换根）DP，组合数学。

---

## 题意分析

一棵树，每个点都有点权，每一条边的方向分布都是等概率的，问从每个点出发，有路走就一直走的情况下，所途径的点的权值总和的期望值。

---

## 思路分析

这明显是一个树形 DP，且需要变成换根 DP 才能过得了这题。

先考虑最基础的树形 DP 暴力：那么设 $f_u$ 表示从点 $u$ 开始往子节点走，满足有路走就一直走的情况下，所途径的点的权值总和的期望值。

设一个点 $u$ 有 $d_u$ 个子节点，那么我们就可以分情况讨论：

对于通向子节点的边能不能走，共有 $2^{d_u}$ 种情况。

再根据期望的线性性质，计算每个子节点的 DP 值 $f_v$ 对 $f_u$ 的贡献，就是下面这个式子：
$$
f_v \cdot \frac{\sum_{i=0}^{d_u-1}\frac{\begin{pmatrix}d_u-1\\i\end{pmatrix}}{i+1}}{2^{d_u}}
$$
解释一下：$\frac{\sum_{i=0}^{d_u-1}\frac{\begin{pmatrix}d_u-1\\i\end{pmatrix}}{i+1}}{2^{d_u}}$ 表示从 $u$ 走到 $v$ 的概率。其中作为分母的 $\frac{1}{2^{d_u}}$ 表示总情况数，上面每次枚举的 $i$ 表示在 $u$ 能够通向 $v$ 时，还能通向几个子节点，那么单次去到 $v$ 的概率就是 $\frac{1}{i+1}$，这种情况的数量就是 $\begin{pmatrix}d_u-1\\i\end{pmatrix}$，乘起来就是概率。

那么 $f_u$ 的值就是：
$$
v_u + \frac{\sum_{i=0}^{d_u-1}\frac{\begin{pmatrix}d_u-1\\i\end{pmatrix}}{i+1}}{2^{d_u}} \cdot \sum_{(u,v) \in G} f_v
$$
那么我们已经可以拿到 Subtask 1 的分了 ~~（卡一卡 Subtask 2 也是轻轻松松）~~。

但这明显不够，我们力求完美。这个一看就可以化简 ~~（二项式定理随便搞搞）~~，我们这里讲两种方法。

两种方法都得先化到一定程度：发现概率中有一个会变的分母 $i+1$，尝试把它转成一个常量（只化简能化的概率部分）。
$$
\begin{aligned}
&  \frac{\sum_{i=0}^{d_u-1}\frac{\begin{pmatrix}d_u-1\\i\end{pmatrix}}{i+1}}{2^{d_u}} \\
& = \frac{\sum_{i=0}^{d_u-1}\frac{(d_u-1)!}{(i+1) \cdot i! \cdot (d_u - i - 1)}}{2^{d_u}} \\
& = \frac{\sum_{i=0}^{d_u-1}\frac{(d_u-1)!}{(i+1)! \cdot (d_u - i - 1)}}{2^{d_u}} \\
& = \frac{\sum_{i=1}^{d_u}\begin{pmatrix}d_u\\i\end{pmatrix}}{d_u \cdot 2^{d_u}} \\
\end{aligned}
$$

1. 二项式定理：

   好了，到这里，一般数学好的同学已经发现上面的 $\sum_{i=1}^{d_u}\begin{pmatrix}d_u\\i\end{pmatrix}$ 可以用二项式定理了，那我们就先推一下他：
   $$
   \begin{aligned}
   & \prod_{i=1}^n (1+a_ix) \\
   & = 1 + (\sum_{i=1}^n a_i) \cdot x + (\sum_{i=1}^n \sum_{j=i+1}^n a_i a_j) x^2 + \cdots + (\prod_{i=1}^n a_i) x^n \\
   \end{aligned}
   $$
   在这里只用在题目里的话，设 $a_i = 1,\forall i\in[1,n]$，式子变为：
   $$
   \begin{aligned}
   \prod_{i=1}^n (1+a_ix) & = 1 + (\sum_{i=1}^n a_i) \cdot x + (\sum_{i=1}^n \sum_{j=i+1}^n a_i a_j) x^2 + \cdots + (\prod_{i=1}^n a_i) x^n \\
   (1+x)^n & = 1 + \begin{pmatrix} n \\ 1 \end{pmatrix} x + \begin{pmatrix} n \\ 2 \end{pmatrix} x^2 + \cdots +\begin{pmatrix} n \\ n \end{pmatrix} x^n \\
   (1+x)^n & = \sum_{i=0}^n \begin{pmatrix} n \\ i \end{pmatrix} x^i
   \end{aligned}
   $$
   这个时候，再设 $x=1$，式子就变成了我们想要的样子：
   $$
   \begin{aligned}
   (1+x)^n & = \sum_{i=0}^n \begin{pmatrix} n \\ i \end{pmatrix} x^i \\
   (1+1)^n & = \sum_{i=0}^n \begin{pmatrix} n \\ i \end{pmatrix} 1^i \\
   2^n & = \sum_{i=0}^n \begin{pmatrix} n \\ i \end{pmatrix} \\
   \end{aligned}
   $$
   于是，我们上面的概率就变成了：
   $$
   \begin{aligned}
   & \frac{\sum_{i=1}^{d_u}\begin{pmatrix}d_u\\i\end{pmatrix}}{d_u \cdot 2^{d_u}} \\
   & = \frac{2^{d_u}-1}{d_u \cdot 2^{d_u}} \\
   \end{aligned}
   $$

2. 手推递推式：

   想不到上面这种方法的同学也不要气馁，车到山前必有路，我们再想想。如果实在想不出来，可以试试先做一下[这题](https://www.luogu.com.cn/problem/U430605)，我就是受这题莫队方法的启发（不会莫队的同学不必慌张，跟这题没关系）。

   设 $f_{x,y} = \sum_{i=1}^{x}\begin{pmatrix} y \\ i \end{pmatrix}$。但是它少一个 $\begin{pmatrix} y \\ 0 \end{pmatrix}$，不好处理，那么我们把它加上：设 $g_{x,y} = \sum_{i=0}^{x}\begin{pmatrix} y \\ i \end{pmatrix}$，那么显而易见：$f_{x,y} = g_{x,y} - 1$。

   我们发现，从 $g_{x,y}$ 其实可以推出 $g_{x,y+1}$ 与 $g_{x+1,y}$：

   1. $g_{x,y} \to g_{x,y+1}$：
      $$
      \begin{aligned}
      g_{x,y+1} & = \sum_{i=0}^{x}\begin{pmatrix} y+1 \\ i \end{pmatrix} \\
      g_{x,y+1} & = \sum_{i=0}^{x}[\begin{pmatrix} y \\ i \end{pmatrix}+\begin{pmatrix} y \\ i-1 \end{pmatrix}] \\
      g_{x,y+1} & = \sum_{i=0}^{x}\begin{pmatrix} y \\ i \end{pmatrix}+ \sum_{i=0}^{x-1} \begin{pmatrix} y \\ i \end{pmatrix} \\
      g_{x,y+1} & = 2 g_{x,y} - \begin{pmatrix} y \\ x \end{pmatrix} \\
      \end{aligned}
      $$

   2. $g_{x,y} \to g_{x+1,y}$：
      $$
      \begin{aligned}
      g_{x+1,y} & = \sum_{i=0}^{x+1}\begin{pmatrix} y \\ i \end{pmatrix} \\
      g_{x+1,y} & = \sum_{i=0}^{x}\begin{pmatrix} y \\ i \end{pmatrix} + \begin{pmatrix} y \\ x+1 \end{pmatrix}\\
      g_{x+1,y} & = g_{x,y} + \begin{pmatrix} y \\ x+1 \end{pmatrix}\\
      \end{aligned}
      $$

   那么从 $g_{x,x}$ 就可以推到 $g_{x+1,x+1}$：
   $$
   \begin{aligned}
   g_{x,x+1} & = 2 g_{x,x} - \begin{pmatrix} x \\ x \end{pmatrix} \\
   g_{x+1,x+1} & = g_{x,x+1} + \begin{pmatrix} x+1 \\ x+1 \end{pmatrix} \\
   g_{x+1,x+1} & = 2 g_{x,x}\\
   \end{aligned}
   $$
   那么 $g_{x,x} = 2^x \cdot g_{0,0},g_{0,0}=1$，即 $g_{x,x}=2^x,f_{x,x}=2^x-1$。

   同样也能得出概率为：
   $$
   \begin{aligned}
   & \frac{\sum_{i=1}^{d_u}\begin{pmatrix}d_u\\i\end{pmatrix}}{d_u \cdot 2^{d_u}} \\
   & = \frac{2^{d_u}-1}{d_u \cdot 2^{d_u}} \\
   \end{aligned}
   $$

总结一下上面的推导过程，得到结论：
$$
\begin{aligned}
f_u & = v_u + \frac{\sum_{i=0}^{d_u-1}\frac{\begin{pmatrix}d_u-1\\i\end{pmatrix}}{i+1}}{2^{d_u}} \cdot \sum_{(u,v) \in G} f_v \\
f_u & = v_u + \frac{2^{d_u}-1}{d_u \cdot 2^{d_u}} \cdot \sum_{(u,v) \in G} f_v \\
\end{aligned}
$$
然后在树形 DP 的基础上再推出换根 DP 就可以拿到满分了！（ヾ(@^▽^@)ノ欢呼）

时间复杂度在不预处理的情况下是 $O(n\log_2{P})$ 的，其中 $P = 10^9 + 7$，$\log_2{P}$ 是处理逆元的时间复杂度，但是发现我们所有的逆元都可以 $O(n)$ 预处理，然后一些其他地方转化一下，就可以去掉这个 $\log_2{P}$ 了！

---

## CODE

```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
#define ll long long
#define max(a,b) ((a)<(b)?(b):(a))
#define min(a,b) ((a)>(b)?(b):(a))
#define tomax(a,b) ((a)=max((a),(b)))
#define tomin(a,b) ((a)=min((a),(b)))
#define RCL(a,b,c,d) memset((a),(b),sizeof(c)*(d))
#define FOR(i,a,b) for(register int i=(a);i<=(b);++i)
#define DOR(i,a,b) for(register int i=(a);i>=(b);--i)
#define EDGE(g,i,u,x) for(register int (i)=(g).h[(u)],(x)=(g).v[(i)];(i);(i)=(g).nxt[(i)],(x)=(g).v[(i)])
#define main Main();signed main(){ios::sync_with_stdio(0);cin.tie(0);return Main();}signed Main
using namespace std;
constexpr int N=1e6+10;
namespace Modular_Arithmetic{
	#define MOD 1000000007
	#define toadd(a,b) ((a)=add((a),(b)))
	#define tomul(a,b) ((a)=mul((a),(b)))
	int pw[N],pinv[N],Inv[N],val[N];
	template<typename T1,typename T2>constexpr auto add(T1 a,T2 b){
		return a+b>=MOD?a+b-MOD:a+b<0?a+b+MOD:a+b;
	}
	template<typename T1,typename T2>constexpr auto mul(T1 a,T2 b){
		return (long long)a*b%MOD;
	}
	template<typename T,typename...Types>constexpr auto add(T a,Types... b){
		return add(a,add(b...));
	}
	template<typename T,typename...Types>constexpr auto mul(T a,Types... b){
		return mul(a,mul(b...));
	}
	int Pow(int a,int b){
		int res=1;
		for(a%=MOD;b;b>>=1,tomul(a,a))if(b&1)tomul(res,a);
		return res;
	}
	void Init(int n){
		pw[0]=1;
		FOR(i,1,n)pw[i]=mul(pw[i-1],2);
		pinv[n]=Pow(pw[n],MOD-2);
		DOR(i,n,1)pinv[i-1]=mul(pinv[i],2);
		Inv[0]=Inv[1]=1;
	    FOR(i,2,n)Inv[i]=1ll*(MOD-MOD/i)*Inv[MOD%i]%MOD;
	    FOR(i,0,n)val[i]=mul(add(pw[i],-1),Inv[i],pinv[i]);
	}
}using namespace Modular_Arithmetic;
int n;
int a[N],d[N],f[N],h[N];
struct CFS{
	int tot,h[N],v[N<<1],nxt[N<<1];
	void att(int U,int V){
		v[++tot]=V,nxt[tot]=h[U],h[U]=tot;
	}
	void con(int U,int V){
		att(U,V),att(V,U);
	}
}g;
void dfs0(int u,int fa){
	d[u]=0,f[u]=0,h[u]=0;
	EDGE(g,i,u,v)if(v^fa)++d[u],dfs0(v,u),toadd(h[u],f[v]);
	f[u]=add(a[u],mul(h[u],val[d[u]]));
}
void dfs1(int u,int fa){
	if(u>1)++d[u];
	f[u]=add(a[u],mul(h[u],val[d[u]]));
	EDGE(g,i,u,v)if(v^fa)toadd(h[v],add(a[u],mul(add(h[u],-f[v]),val[d[u]-1]))),dfs1(v,u);
}
signed main(){
	rd(n),Init(n);
	FOR(i,2,n){
		int x;
		rd(x),g.con(x,i);
	}
	FOR(i,1,n)rd(a[i]);
	dfs0(1,0),dfs1(1,0);
	FOR(i,1,n)wr(f[i]);
	return 0;
}
```

提示：把取模运算封装一下会方便很多哦。

---

---

## 作者：LinkCatTree (赞：1)

观察数据范围，$n \leq 10^6$，大概就可以判断出这是一道换根 DP。我们先考虑如何计算某个点的答案，再考虑如何进行“换根”。

首先，根据题目描述，显然**一条边最多只会被经过一次**，这说明如果以树上的根结点为起点，走到的点的深度只会越来越大。这样就可以通过 dfs，自底向上最终计算出根节点的答案。

我们考虑如何设计 dp 转移方程。假设 $f_i$ 表示在当前这棵树中，从 $i$ 开始往子树走的期望美感。我们可以发现：一个点往其每个子节点走的概率是相同的。假设 $son_i$ 表示 $i$ 的子节点，那么有 $\dfrac1{2^{|son_i|}}$ 的概率没法走到任何一个子节点，剩下的每个子节点有 $\dfrac1{|son_i|} \times (1-\dfrac1{2^{|son_i|}})$ 的概率走到。于是我们可以写出转移方程：

$$f_i=v_i+\sum\limits_{j \in son_i} f_j \times \dfrac1{|son_i|} \times (1-\dfrac1{2^{|son_i|}})$$

不妨用 $sum_i$ 表示 $\sum\limits_{j \in son_i} f_j$，得到：

$$f_i=v_i+\dfrac1{|son_i|}\times(1-\dfrac1{2^{|son_i|}})sum_i$$

接下来我们考虑如何换根 dp。假设当前的根是 $i$，我们考虑怎么求以 $i$ 的子节点 $j$ 为根时的答案：

![](https://cdn.luogu.com.cn/upload/image_hosting/5worlgrv.png)

我们不妨考虑以 $j$ 为根时，$sum_{i/j},f_{i/j},son_{i/j}$ 都有哪些变化。（显然除了 $i$ 和 $j$，其他点都没有变化）

显然，$son_i$ 中少了一个 $j$ 而 $son_j$ 中多了一个 $i$；这意味着 $|son_i|$ 少了一且 $|son_j|$ 多了一。$sum_i$ 少了 $f_j$（这里的 $f_j$ 是以 $i$ 为根时的 $f_j$），而 $sum_j$ 多了 $f_i$（这里的 $f_i$ 是以 $j$ 为根时的 $f_i$）。那么我们根据以上变化，也不难用更新后的值来计算出更新后的 $f_i,f_j$。

两遍 dfs 都是 $\mathcal{O}(n)$ 的，但是预处理 $\dfrac1{|son_i|}\times(1-\dfrac1{2^{|son_i|}})$ 需要 $\mathcal{O}(n \log n)$ 的时间（求逆元）。总时间复杂度为 $\mathcal{O}(n \log n)$。

```cpp
typedef long long ll;
const int N=1e6+5;
const ll mod=1e9+7,inv2=5e8+4;
int n;
vector<int> son[N];
ll val[N],sum[N],f[N];
ll ans[N],tp[N];

inline ll qpow(ll x,ll p) {
	ll tmp=1;
	for(;p;p>>=1) {
		if(p&1) tmp=tmp*x%mod;
		x=x*x%mod;
	}
	return tmp;
}
void dfs0(int u) {
	for(auto v:son[u]) dfs0(v),(sum[u]+=f[v])%=mod;
	f[u]=(tp[son[u].size()]*sum[u]+val[u])%mod;
	return ;
}
void dfs1(int u) {
	ans[u]=f[u];
	for(auto v:son[u]) {
		ll sumu=sum[u],sumv=sum[v],fu=f[u],fv=f[v];
		sum[u]=(sum[u]-f[v]+mod)%mod,f[u]=(tp[son[u].size()-(u==1)]*sum[u]+val[u])%mod;
		sum[v]=(sum[v]+f[u])%mod,f[v]=(tp[son[v].size()+1]*sum[v]+val[v])%mod;
		dfs1(v);
		sum[u]=sumu,sum[v]=sumv;
		f[u]=fu,f[v]=fv;
	}
	return ;
}

int main() {
	n=read();
	for(int i=1;i<=n;i++) tp[i]=(mod+1-qpow(inv2,i))*qpow(i,mod-2)%mod;
	for(int i=2;i<=n;i++) son[read()].push_back(i);
	for(int i=1;i<=n;i++) val[i]=read();
	dfs0(1),dfs1(1);
	for(int i=1;i<=n;i++) printf("%lld\n",ans[i]);
	return 0;
}
```

---

## 作者：_qhbd_ (赞：0)

# 题意
给定一颗 $n$ 个节点的树，点有点权，每条边有 $\frac{1}{2}$ 的概率可单向通行。你在树上游走，每次在可行边中随机择一条边游走，直到无路可走时停止。求当点 $i(1\le i\le n)$ 为起点时，行走路径上点权和期望。
# 思路
树上期望换根 dp。

不妨令树根和起点为 $u$ 且其有子节点 $a$，那么我们的问题转化为求 $u$ 向其子树内游走路径上点权和期望。假设 $u$ 有 $w$ 的概率走向 $a$，如果知道 $a$ 为起点向其子树内游走路径上点权和期望为 $V$，便能求得子节点 $a$ 对 $u$ 的贡献为 $Vw$。

显然这就是树上期望 dp，我们用 dp 数组存储每个点以自身为起点向子树内游走路径点权和期望，加之用其父节点走向它概率作转移来求得答案。然后作换根即可。

令 $g_u$ 表示 $u$ 非根时向自己子树内游走路径点权和期望，$f_u$ 则表示 $u$ 为根时向游走路径点权和期望。

这里之所以分是根非根，是因为两种情况的儿子数量是不一样的，如果非根时有个爹，如果变成根爹就成儿子，儿子数量增一。

令点 $u$ 有 $s$ 个儿子，那么它有 $\frac{1}{2^s}$ 的概率无路可走，同时就有 $\frac{2^s-1}{2^s}$ 的概率有路可走，因为随机所以每个儿子被选择的概率为 $\frac{2^s-1}{2^s\times s}$，这里 $s\in[1,n-1]$，可以预处理。

转移显然：

$$
g_u=\sum\limits_{v\in son_u}g_v\times \frac{2^{|son_u|}-1}{2^{|son_u|}\times|son_u|}
$$

$$
f_u=\sum\limits_{v\in son_u}g_v\times \frac{2^{|son_u|}-1}{2^{|son_u|}\times|son_u|}
$$

换根怎么做呢？假设当前根 $u$，准备换根到其儿子 $v$ 身上，那么我们要先从 $g_u$ 上减掉 $g_v$ 的贡献然后 $f_v,g_v$ 计入 $g_u$ 的贡献即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
const int P=1e9+7;
int n;
long long vl[N],f[N],g[N],E[N];
vector<int>e[N];
inline long long qkpow(long long base,long long x,long long res=1){
	while(x){
		if(x&1)res=res*base%P;
		base=base*base%P;
		x>>=1;
	}
	return res;
}
inline void dfs(int u,int fa){
	f[u]=g[u]=vl[u];
	for(auto v:e[u])
		if(v^fa){
			dfs(v,u);
			f[u]=(f[u]+g[v]*E[e[u].size()]%P)%P;
			g[u]=(g[u]+g[v]*E[e[u].size()-1]%P)%P;
		}
}
inline void DFS(int u,int fa){
	for(auto v:e[u])
		if(v^fa){
			g[u]=(g[u]-g[v]*E[e[u].size()-1]%P+P)%P;
			g[v]=(g[v]+g[u]*E[e[v].size()-1]%P)%P;
			f[v]=(f[v]+g[u]*E[e[v].size()]%P)%P;
			DFS(v,u);
			g[v]=(g[v]-g[u]*E[e[v].size()-1]%P+P)%P;
			g[u]=(g[u]+g[v]*E[e[u].size()-1]%P)%P;
		}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)E[i]=(1-qkpow(qkpow(2,i),P-2)+P)%P*qkpow(i,P-2)%P;
	for(int u=2,v;u<=n;u++){
		scanf("%d",&v);
		e[u].emplace_back(v);
		e[v].emplace_back(u);
	}
	for(int i=1;i<=n;i++)scanf("%lld",&vl[i]);
	dfs(1,0);
	DFS(1,0);
	for(int i=1;i<=n;i++)printf("%lld\n",f[i]);
	return 0;
}
```

---

## 作者：XuYueming (赞：0)

## 前言

期望套期望，很有意思。来一发考场首 A，近 $\Theta(n)$ 的算法。

洛谷题解太窄了，所以[更好的体验](https://www.cnblogs.com/XuYueming/p/18187874)。

## 题意简述

一棵树，每条边随机设有方向。对于所有 $i$，从 $i$ 开始随机游走，直到不能移动，所行走的距离的期望的期望。

前一个期望是局面确定时，随机游走的期望距离；后一个期望是所有局面下的期望距离。

## 题目分析

看到有 $n \leq 1000$ 的部分分，很容易猜到这是换根 DP，这一档部分分是用来每个点跑一边 DFS 的。那么先来看看部分分。

### 枚举根

不妨先来考虑求以 $yzh$ 为根时，从 $yzh$ 开始随机游走的距离的期望的期望。

考虑设 $f_i$ 表示以点 $i$ 为根的答案。因为若从 $\operatorname{fa}[i]$ 走到了 $i$，那么 $i$ 不可能返回到 $\operatorname{fa}[i]$，所以这是一个形式相同，规模更小的子问题。注意到，这前提是以 $yzh$ 为根的情况。

根据期望的定义式 $\operatorname{E} = \sum \limits _ {S \subseteq \Omega} \operatorname{val}[S] \cdot \operatorname{P}[S]$。本题中，$\Omega$ 是 $\operatorname{son}[i]$，$\operatorname{val}[S]$ 指这样一个局面，若 $j \in S$，$i$ 和 $j$ 之间的边的方向为 $i \rightarrow j$，否则是 $i \leftarrow j$。从 $i$ 开始随机游走，就是等概率从 $S$ 中选出 $j$，然后向 $j$ 走。易知所有局面出现概率相等，即 $\operatorname {P}[S] = \cfrac{1}{2 ^ {|\operatorname{son}[i]|}}$，故 $f_i = \cfrac{1}{2 ^ {|\operatorname{son}[i]|}} \sum \limits _ {S \subseteq \operatorname{son}[i]} \operatorname{val}[S]$。又有 $\operatorname{val}[S] = \cfrac{1}{|S|} \sum \limits _ {j \in S} f_j + \operatorname{value}[i]$。所以有

$$
f_i = \operatorname{value}[i] + \cfrac{1}{2 ^ {|\operatorname{son}[i]|}} \sum \limits _ {S \subseteq \operatorname{son}[i]} \cfrac{1}{|S|} \sum \limits _ {j \in S} f_j
$$

值得注意的是，当 $S = \varnothing$ 时，$\cfrac{1}{|S|}$ 没意义，但是这种情况不会对答案产生贡献，所以只用考虑 $S \neq \varnothing$ 的情况。

套路化地拆贡献，分别考虑每个 $j \in \operatorname{son}[i]$ 的贡献。那么 $j$ 产生的贡献就是包含 $j$ 的所有情况的 $\cfrac{1}{|S|}$ 之和 $\operatorname{sum}$，与 $f_j$ 的乘积。发现对于所有 $j$ 来说，前者是一样的，都是 $\large \operatorname{sum} = \sum \limits _ {i = 1} ^ {|\operatorname{son}[i]|} \cfrac{C_{|\operatorname{son}[i]| - 1} ^ {i - 1}}{i}$，其中 $i$ 表示包含 $j$ 的集合 $S$ 的大小，组合数表示包含 $j$，且大小为 $i$ 的 $S$ 的情况数。所以有

$$
\Large f_i = \operatorname{value}[i] + \cfrac{1}{2 ^ {|\operatorname{son}[i]|}} \left (\sum \limits _ {i = 1} ^ {|\operatorname{son}[i]|} \cfrac{C_{|\operatorname{son}[i]| - 1} ^ {i - 1}}{i} \right) \left( \sum \limits _ {j \in \operatorname{son}[i]} f_j \right)
$$

到此为止，已经可以拿到这部分分了。注意到 $\sum |\operatorname{son}[i]| = n - 1$，所以配合线性推逆元等奇技淫巧，一次 dfs 的时间复杂度是 $\Theta(n)$ 的，总体时间复杂度 $\Theta(n^2)$ 的。

### 换根 DP

换根 DP 的第一遍 dfs 和部分分相同，考虑第二遍 dfs。

在第二遍 dfs 时，考虑根从 $yzh \rightarrow xym$，那么首先要把 $f_{yzh}$ 中来自 $xym$ 的贡献去掉，再累加到 $f_{xym}$ 的求和里，同时注意维护换根时对 $\operatorname{son}$ 的影响。推式子也很好推，考虑记 $\operatorname{cal}(n) = \sum \limits _ {i = 1} ^ {n} \cfrac{C_{n - 1} ^ {i - 1}}{i}$，用 $f'$ 表示第一遍 dfs 求出的 $f$，$F$ 表示以 $xym$ 为根时的 $f$。

$$

\tiny F_{yzh} = \operatorname{val}[yzh] + \cfrac{1}{2^{|\operatorname{son}[yzh]| - [yzh = 1]}} \cdot \operatorname{cal}(|\operatorname{son}[yzh]| - [yzh = 1]) \cdot \left(\cfrac{2 ^ {|\operatorname{son}[yzh]| + [yzh \neq 1]}(f_{yzh} - \operatorname{val}[yzh])}{\operatorname{cal}(|\operatorname{son}[yzh]| + [yzh \neq 1])} - f'_{xym} \right)

$$

$$

\tiny f_{xym} = \operatorname{val}[xym] + \cfrac{1}{2^{|\operatorname{son}[xym]| + 1}} \cdot \operatorname{cal}(|\operatorname{son}[xym]| + 1) \cdot\left(2 ^ {|\operatorname{son}[xym]|} \cdot \operatorname{cal}(|\operatorname{son}[xym]|) \cdot (f'_{xym} - \operatorname{val}[xym]) + F_{yzh} \right)

$$

然后就可以啦～

## 时间复杂度分析

yzh 问为什么时间复杂度是**近** $\Theta(n)$ 的，那么接下来回答下她的问题。

发现本来时间复杂度是 $\Theta(n)$ 的，但是有求 $\operatorname{cal}$ 函数的逆元，会多一个 $\log P$。但是，加上记忆化后，时间复杂度是 $\Theta(n + \sqrt{n}\log P)$ 的，考虑证明一棵树本质不同的儿子数是 $\Theta(\sqrt{n})$ 的。

> 证明：
> 
> 反证。假设一棵树有 $k \gt \sqrt{2n}$ 个本质不同的孩子数，分别为 $s_1, s_2, \cdots, s_k$。那么有 $n = \sum \limits _ {i = 1} ^ {k} s_i \geq \sum \limits _ {i = 1} ^ {k} i = \cfrac{(1 + k)k}{2} \gt n$，矛盾，所以一棵树本质不同的儿子数是 $\Theta(\sqrt{n})$ 的。

在本题的数据范围下，可以**近似**看做线性算法。

## 代码

略去了快读快写，实现也很容易。

```cpp
// #pragma GCC optimize(3)
// #pragma GCC optimize("Ofast", "inline", "-ffast-math")
#pragma GCC target("avx", "sse2", "sse3", "sse4", "mmx")
#include <iostream>
#include <cstdio>
#define debug(a) cerr << "Line: " << __LINE__ << " " << #a << endl
#define print(a) cerr << #a << "=" << (a) << endl
#define file(a) freopen(#a".in", "r", stdin), freopen(#a".out", "w", stdout)
#define main Main(); signed main(){ return ios::sync_with_stdio(0), cin.tie(0), Main(); } signed Main
using namespace std;

char ST;

constexpr const int mod = 1e9 + 7;

constexpr inline int pow(const int a, const int p, const int mod = mod){
	int res = 1, base = a % mod, b = p;
	while (b){
		if (b & 1) res = 1ll * res * base % mod;
		base = 1ll * base * base % mod, b >>= 1;
	}
	return res;
}

constexpr inline int inv(const int a, const int mod = mod){
	return pow(a, mod - 2, mod);
}

constexpr const int inv2 = inv(2, mod);

inline int add(int a, int b){
	return a + b >= mod ? a + b - mod : a + b;
}

inline int mul(int a, int b){
	return 1ll * a * b % mod;
}

int n, val[1000010], frac[1000010], ans[1000010];
int Inv[1000010], ifrac[1000010], pw2[1000010], ipw2[1000010];
int f[1000010];

inline int C(int n, int m){
	return mul(frac[n], mul(ifrac[m], ifrac[n - m]));
}

struct Graph{
	struct node{
		int to, nxt;
	} edge[1000010];
	int eid, head[1000010];
	inline void add(int u, int v){
		edge[++eid] = {v, head[u]};
		head[u] = eid;
	}
	inline node & operator [] (const int x){
		return edge[x];
	}
} xym;

int g[1000010], ig[1000010];
int calsum(int son){
	if (g[son] != -1) return g[son];
	int sum = 0;
	for (int i = 1; i <= son; ++i)
		sum = add(sum, mul(Inv[i], C(son - 1, i - 1)));
	return g[son] = sum;
}
int icalsum(int son){
	if (ig[son] != -1) return ig[son];
	return ig[son] = inv(calsum(son));
}

int soncnt[1000010];

void dfs(int now, int fa){
	// 这一遍维护子树信息
	for (int i = xym.head[now], to; to = xym[i].to, i; i = xym[i].nxt){
		if (to == fa) continue;
		++soncnt[now], dfs(to, now), f[now] = add(f[now], f[to]);
	}
	f[now] = mul(f[now], calsum(soncnt[now]));
	f[now] = mul(f[now], ipw2[soncnt[now]]);
	f[now] = add(f[now], val[now]);
}

void redfs(int now, int fa){
	// 这一次搞一搞父亲方向的子树
	ans[now] = f[now];
	for (int i = xym.head[now], to; to = xym[i].to, i; i = xym[i].nxt){
		if (to == fa) continue;
		f[to] = add(
					mul(
						mul(
							add(
								mul(
									mul(
										pw2[soncnt[to]],
										add(
											f[to],
											mod - val[to]
										)
									),
									icalsum(soncnt[to])
								),
								add(
									mul(
										mul(
											add(
												mul(
													mul(
														pw2[soncnt[now] + (now != 1)],
														add(
															f[now],
															mod - val[now]
														)
													),
													icalsum(soncnt[now] + (now != 1))
												),
												mod - f[to]
											),
											calsum(soncnt[now] - (now == 1))
										),
										ipw2[soncnt[now] - (now == 1)]
									),
									val[now]
								)
							),
							calsum(soncnt[to] + 1)
						),
						ipw2[soncnt[to] + 1]
					),
					val[to]
				);
		redfs(to, now);
	}
}

char ED;

signed main(){
	#if XuYueming
	fprintf(stderr, "Memory: %2.lfMb\n", (&ED - &ST) / 1024.0 / 1024.0);
	#endif
	
	read(n);
	for (int i = 2, fa; i <= n; ++i) read(fa), xym.add(fa, i);
	ifrac[0] = frac[0] = 1, ig[0] = g[0] = -1, pw2[0] = ipw2[0] = 1;
	for (int i = 1; i <= n; ++i)
		read(val[i]),
		frac[i] = mul(frac[i - 1], i),
		pw2[i] = mul(pw2[i - 1], 2), ipw2[i] = mul(ipw2[i - 1], inv2),
		Inv[i] = i == 1 ? 1 : mod - mul(mod / i, Inv[mod % i]),
		ifrac[i] = mul(ifrac[i - 1], Inv[i]), g[i] = ig[i] = -1;
	dfs(1, 0), redfs(1, 0);
	for (int i = 1; i <= n; ++i) write(ans[i], '\n');
	return 0;
}
```

## 后记

考后认真思考一番，发现瓶颈在算 $\operatorname{cal}$ 的逆元，而我们目的仅是去掉某一贡献，故可以额外记 $g$ 表示 $f$ 在算 $\operatorname{cal}$ 之前的值。并且 $\operatorname{cal}$ 其实是可以继续用数学的方式 $\Theta(1)$ 计算的，由于本题解方法不侧重这里，所以简略地推一推，其实也很简单：

$$
\begin{aligned}

\operatorname{cal}(n) & = \sum \limits _ {i = 1} ^ {n} \cfrac{C_{n - 1} ^ {i - 1}}{i} \\
&= \sum \limits _ {i = 1} ^ {n} \cfrac{(n - 1)!}{i \cdot (i - 1)! \cdot (n - i)!} \\
&= \sum \limits _ {i = 1} ^ {n} \cfrac{n \cdot (n - 1)!}{i! \cdot n \cdot (n - i)!} \\
&= \sum \limits _ {i = 1} ^ {n} \cfrac{C_n^i}{n} \\
&= \cfrac{\sum \limits _ {i = 0} ^ {n} C_n^i - C_n^0}{n} \\
&= \cfrac{2^n - 1}{n}

\end{aligned}
$$

配合上题目输入已经拓扑排序，dfs 换成循环，能跑到 [Rank1](https://www.luogu.com.cn/record/158879705)，代码也很短，注意到实现中 `cal` 数组含义是 $\cfrac{\operatorname{cal}(n)}{2^n}=\cfrac{1}{n}-\cfrac{1}{n\cdot2^n}$。

```cpp
#pragma GCC target("avx", "sse2", "sse3", "sse4", "mmx")
#include <cstdio>

constexpr const int MAX = 1 << 24, yzh_i_love_you = 1314520736;

char buf[MAX], *p1 = buf, *p2 = buf, obuf[MAX], *o = obuf;
#ifndef XuYueming
#define getchar() ((p1 == p2) && (p2 = (p1 = buf) + fread(buf, 1, MAX, stdin), p1 == p2) ? EOF : *p1++)
#endif

constexpr inline bool isdigit(const char c) { return c >= '0' && c <= '9'; }
template <typename T> inline void read(T &x) { x = 0; char c = 0; for (;!isdigit(c); c = getchar()); for (; isdigit(c); c = getchar()) x = (x << 3) + (x << 1) + (c ^ 48); }
template <typename T> inline void write(T &x){ static short Stack[50], top = 0; do Stack[++top] = x % 10, x /= 10; while (x); while (top) *o++ = Stack[top--] | 48; }

constexpr const int mod = 1e9 + 7;
constexpr const int inv2 = 500000004;
constexpr inline int add(int a, int b){ return a + b >= mod ? a + b - mod : a + b; }
constexpr inline int mul(int a, int b){ return 1ll * a * b % mod; }

int n, fa[1000001], soncnt[1000001], val[1000001], cal[1000001], Inv[1000001], ipw2[1000001], f[1000001], g[1000001];

signed main(){
	read(n);
	for (register int i = 2; i <= n; ++i) read(fa[i]), ++soncnt[fa[i]];
	Inv[0] = ipw2[0] = 1;
	for (register int i = 1; i <= n; ++i) read(val[i]), ipw2[i] = mul(ipw2[i - 1], inv2), Inv[i] = i == 1 ? 1 : mod - mul(mod / i, Inv[mod % i]), cal[i] = add(Inv[i], mod - mul(Inv[i], ipw2[i]));
	for (register int i = n; i >= 1; --i) f[i] = add(val[i], mul(g[i], cal[soncnt[i]])), g[fa[i]] = add(g[fa[i]], f[i]);
	for (register int i = 2; i <= n; ++i) g[i] = add(g[i], add(val[fa[i]], mul(add(g[fa[i]], mod - f[i]), cal[soncnt[fa[i]] - 1]))), f[i] = add(val[i], mul(g[i], cal[++soncnt[i]]));
	for (register int i = 1; i <= n; ++i) write(f[i]), *o++ = '\n';
	return fwrite(obuf, 1, o - obuf, stdout), 0;
}
```

---

