# Parametric MST

## 题目描述

You are given $ n $ integers $ a_1, a_2, \ldots, a_n $ . For any real number $ t $ , consider the complete weighted graph on $ n $ vertices $ K_n(t) $ with weight of the edge between vertices $ i $ and $ j $ equal to $ w_{ij}(t) = a_i \cdot a_j + t \cdot (a_i + a_j) $ .

Let $ f(t) $ be the cost of the [minimum spanning tree](https://en.wikipedia.org/wiki/Minimum_spanning_tree) of $ K_n(t) $ . Determine whether $ f(t) $ is bounded above and, if so, output the maximum value it attains.

## 样例 #1

### 输入

```
5
2
1 0
2
-1 1
3
1 -1 -2
3
3 -1 -2
4
1 2 3 -4```

### 输出

```
INF
-1
INF
-6
-18```

# 题解

## 作者：FFTotoro (赞：14)

为了便于解题，先对 $a$ 数组从小到大进行排序。

首先，根据定义可以得出总价值的表达式：

$$
\begin{aligned}
W&=\sum\limits_{(u,v)\in E}[a_ua_v+t(a_u+a_v)]\\
  &=\sum\limits_{(u,v)\in E}a_ua_v+t\sum\limits_{(u,v)\in E}(a_u+a_v)
\end{aligned}
$$

接着，我们需要发现一个比较重要的性质：

- $w_{i,j}(t)=a_ia_j+t(a_i+a_j)=(a_i+t)(a_j+t)-t^2$

也就是说，如果固定一个 $t$，那么 $t^2$ 就是定值，可以暂不考虑；$\forall 1\le i\le n$，如果 $a_i+t$ 是正数，就向结点 $1$ 连边以最小化该点的贡献；如果 $a_i+t$ 是负数，就向结点 $n$ 连边（如果 $a_i+t=0$ 那么向哪个点连边都一样）。最后去掉 $1$ 与 $n$ 之间的重边以及若干自环，即可构造出正好有 $n-1$ 条边的最小生成树。

现在来考虑一下无解的情况：

- 如果 $\forall 1\le i\le n,a_i+t>0$，那么除了 $1$ 以外的所有结点向 $1$ 连边，有

  $$
  \begin{aligned}
  W&=\sum\limits_{(u,v)\in E}a_ua_v+t\sum\limits_{(u,v)\in E}(a_u+a_v)\\
  &=a_1\sum\limits_{i=2}^na_i+t\left[(n-1)a_1+\sum\limits_{i=2}^na_i\right]\\
  \end{aligned}
  $$
  
  可以发现，$W$ 是关于 $t$ 的一次函数。由于满足 $\forall 1\le i\le n,a_i+t>0$，所以如果一次项系数 $(n-1)a_1+\sum\limits_{i=2}^na_i>0$，那么当 $t\rightarrow+\infty$ 时 $W\rightarrow+\infty$，该函数不存在最大值。
  
- 如果 $\forall 1\le i\le n,a_i+t<0$，同理有：

  $$
  \begin{aligned}
  W&=a_n\sum\limits_{i=1}^{n-1}a_i+t\left[(n-1)a_n+\sum\limits_{i=1}^{n-1}a_i\right]\\
  \end{aligned}
  $$
  
  类似的，如果 $(n-1)a_n+\sum\limits_{i=1}^{n-1}a_i<0$，当 $t\rightarrow-\infty$ 时，$W\rightarrow+\infty$，不存在最大值。
  
综上，如果 $(n-1)a_1+\sum\limits_{i=2}^na_i>0$ 或 $(n-1)a_n+\sum\limits_{i=1}^{n-1}a_i<0$，边权和不存在最大值，直接输出 `INF` 即可。

现在来考虑有解时如何寻找解。这时我们就需要引入一个新的性质：

- 如果 $W$ 能取到最大值，$-t$ 的值一定是 $a$ 数组中的其中一个元素的值。

  证明：
  
  容易得知当 $W$ 取到最值时，$a_1\le -t\le a_n$（否则函数不收敛）。
  
  当 $-t\in[a_i,a_{i+1}](1\le i<n)$ 时，最优的连边方式之一是将所有的 $1\le j\le i$ 向结点 $n$ 连边（因为这些 $j$ 满足 $a_j+t\le 0$），其他结点向 $1$ 连边。所以我们可以得到 $W$ 的表达式：
  
  $$
  \begin{aligned}
  W&=a_n\sum\limits_{j=2}^ia_j+t\left[(i-1)a_n+\sum\limits_{j=2}^ia_j\right]+a_1\sum\limits_{j=i+1}^na_j+t\left[(n-i)a_1+\sum_{j=i+1}^na_j\right]
  \end{aligned}
  $$
  
  （注意到这里 $1$ 和 $n$ 之间的边仅仅被连了一次，所以最终不用考虑重边的影响。）
  
  在这里因为 $i$ 确定，所以 $W$ 还是关于 $t$ 的一次函数，最值必然在 $-t=a_i$ 或 $-t=a_{i+1}$ 时取到。命题得证。
  
接下来只用枚举 $i=1,2,\ldots,n$，然后令 $t=-a_i$，将 $t$ 带入证明中的那个表达式算出 $W$ 的值。在所有的 $W$ 中找到 $W_{\max}$ 并输出即可。

中间那一些求和的式子可以使用前缀和维护。

放代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
main(){
  ios::sync_with_stdio(false);
  int t; cin>>t;
  while(t--){
    int n,c=LLONG_MIN; cin>>n;
    vector<int> a(n),s;
    for(auto &i:a)cin>>i;
    sort(a.begin(),a.end()); // 排序
    partial_sum(a.begin(),a.end(),back_inserter(s)); // 做前缀和
    if(a[0]*(n-2)+s[n-1]>0||a[n-1]*(n-2)+s[n-1]<0)cout<<"INF\n"; // 无解情况
    else{
      for(int i=0;i<n;i++)
        c=max(c,a[0]*(s[n-1]-s[i])-a[i]*(a[0]*(n-i-1)+s[n-1]-s[i])+a[n-1]*(s[i]-s[0])-a[i]*(a[n-1]*i+s[i]-s[0]));
        // 带入表达式计算
      cout<<c<<endl;
    }
  }
  return 0;
}
```

---

## 作者：Phanstom_Peng (赞：9)

~~场上差那么一点点就 15Ton 了~~

一个瓶颈在排序的线性做法。  

记 $d_i$ 表示点 $i$ 的度数。  

判断 $\text{INF}$ 是简单的，只需要看能不能凑出 $\sum a_i\times d_i$ 分别为正和负或者 $0$ 就行，如果凑不出来，令 $t$ 为正无穷或者负无穷，然后它就不收敛了。

现在已知有解。

考虑固定一个 $t$ 后怎么快速求 $\text{MST}$。做个恒等变形，权值为 $(a_i+t)\times (a_j+t)-t^2$，把 $t^2$ 给扔掉。

结论是排序后按正负性断开，$a_1$  向所有 $a_i$ 大于 $0$ 的连边， $a_n$ 向所有 $a_i$ 小于 $0$ 的连边，$0$ 无所谓。

证明可以考虑 `Prime` 算法的过程，最开始一定是 $a_1$ 到 $a_n$。然后后面不会取到正负性相同的，并且一个点一定是连向 $a_1$ 或者 $a_n$。

如果处理一个前缀和，知道正负交界的位置之后可以快速算，从小到大枚举 $t$，然后双指针维护交界处。

可以证明 $t$ 一定取到每个 $-a_i$。如果夹在两坨中间，那么由于具体选哪些边是固定的，根据 $\sum a_i\times d_i$ 正负性调整即可。

不会取到 $[a_1,a_n]$ 外面去，因为我们已经判了无解，所以取到边界外面时 $\sum a_i\times d_i$  的正负性会导致向里面调整更优。


代码：

```
#include<bits/stdc++.h>
#define INF 1000000000
#define int long long
#define pii pair<int,int>
using namespace std;
template<typename _type>
inline void read(_type &x){
	x=0;int f=1;char ch=getchar();
	while(ch!=45&&(ch>'9'||ch<'0'))ch=getchar();
	if(ch==45){f=-1,ch=getchar();}
	while(ch<='9'&&ch>='0'){x=x*10+ch-48;ch=getchar();}x*=f;
}
template<typename _type>void cmin(_type &a,_type b){a=min(a,b);}
template<typename _type>void cmax(_type &a,_type b){a=max(a,b);}
const int N=1e6+10;
int i,j,k,n,s,t,m,ans,pos;
int a[N],sum[N];
int calc(int pos,int val){
	return -(n-1)*val*val+(a[n]+val)*(sum[pos]+pos*val)+(a[1]+val)*((sum[n-1]-sum[pos])+(n-1-pos)*val);
}
signed main()
{
 	//freopen("string.in","r",stdin);
	//freopen("string.out","w",stdout);
	read(t);
	while(t--){
		read(n);	
		for(i=1;i<=n;i++)read(a[i]);
		sort(a+1,a+n+1);
		for(i=1;i<=n;i++)sum[i]=a[i]+sum[i-1];
		int flag=0;
		if(a[1]*(n-2)+sum[n]>0||a[n]*(n-2)+sum[n]<0)flag=1;
		if(flag){
			puts("INF");
			continue;
		}
		ans=-4e18,pos=1;
		for(i=1;i<n;i++){
			cmax(ans,calc(i,-a[i]));
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：jiangchenyangsong (赞：6)


给定一张 $n$ 个点的无向完全图 $\operatorname{K_n}(t)$，点 $i$ 和点  $j$ 之间的边的边权 $\operatorname{w_{i,j}}(t)$ 为 $a_i\times a_j+t \times (a_i+a_j)$，其中 $t$ 为任意实数。

定义 $\operatorname{f}(t)$ 为 $\operatorname{K_n}(t)$ 的最小生成树的边权和。输出  $\operatorname{f}(t)$ 的最大值，无最大值则输出 `INF` 。
## 分析

 首先将 $a$ 从小到大排序，设 $s$ 为 $a$ 的前缀和
，确定 $i$ 时，$a_ia_j+t(a_i+a_j)=(t+a_i)a_j+ta_i$ 。

因为 $ta_i$ 是个定值，所以只需考虑 $t+a_i$ 的正负，若 $t+a_i$ 为正则肯定贪心选择最小的 $a_j$，否则选择最大的 $a_j$ 。所以，对于 $t$ 非常大，若 $(a_1 \times (n-1)+s_n-s_1)>0$ 则输出 `INF`，同理若 $t$ 是非常小的负数，若 $(a_n\times(n-1)+s_n-s_1)<0$ 则输出 `INF`。

 其它情况我们观察一下式子 $\operatorname{w_{i,j}}(t)=a_ia_j+t(a_i+a_j)=(a_i+t)(a_j+t)-t^2$，令$b_i=a_i+t$，则权值为 $\operatorname{w_{i,j}}(t)=b_ib_j-t^2$，令   $\operatorname{w_{i,j}}=b_ib_j$ 则 $\operatorname{f}(t)=mst-(n-1)t^2$ （ $mst$ 为最小生成树权值和），对于所有的对于任意一个 $t$，一定满足 $ [1,i]\ b_i<0$，$[i+1,n]\ b_i>0$，对于 $ b_i<0$ 我们将其和 $\max(b_i)$) 相连，对于 $ b_i>0$ 我们将其和 $\min(b_i)$ 相连，这样求出来的就是最小值，通过枚举 $t$ 求解即可。
 
发现 t 在 $[-a_{i+1},-a_i]$ 可以把这个范围内的 $\operatorname{f}(t)$ 表示成一个关于 $t$ 的一次函数。这怎么理解呢？比如说，$t$ 在 $[-a_{i+1},-a_i]$ 范围内，每次 $+1$，最小生成树选择的边是不会变的，则答案就会变化 $\sum{a_i+a_j}-2\times t\times (n-1)$，( $(i,j)$ 为选择的边)，显然 $\sum{a_i+a_j}$ 的值不会变，所以为一次函数。所以，最大值肯定取在端点处，所以依次只要枚举 $t=-a_i$ 的权值，再取个最大值就行了。

$code$
```
#include<bits/stdc++.h>
#define N 200005
#define int long long
using namespace std;
int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}
int T,n;
int a[N],s[N];
signed main(){
	T=read();
	while(T--){
		n=read();
		for(int i=1;i<=n;++i) a[i]=read();
		sort(a+1,a+1+n);
		for(int i=1;i<=n;++i) s[i]=s[i-1]+a[i];
		if(s[n]-s[1]+a[1]*(n-1)>0||s[n-1]+a[n]*(n-1)<0){printf("INF\n");continue;}
		int ans=-1e18;
		for(int i=1;i<=n;++i){
			int t=-a[i];
			int maxn=a[n]+t,minn=a[1]+t;
			int ls=s[i]+i*t,rs=s[n]-s[i]+(n-i)*t;
			ans=max(ans,ls*maxn+rs*minn-minn*maxn-(n-1)*t*t);
		}
		printf("%lld\n",ans);
	}
	return 0;
} 
```


---

## 作者：elbissoPtImaerD (赞：3)

肯定是先考虑 $t$ 给定怎么做。

**调整地**，我们可以让每个点 $u$ 和使 $w_{u,v}(t)$ 最小的 $v\neq u$ 相连。

尝试给 $a$ 定序：升序排列好了。

那么这个 $v$ 就很好刻画了：关注到 $w_{u,v}(t)=(a_u+t)(a_v+t)-t^2$，若 $a_u+t$ 为正，则 $v=n$，否则 $v=0$。

这个贡献容易用前缀和快速统计。

如何判 `INF` 也就呼之欲出了：让 $t \to \pm \inf$，看函数取值（事实上写出来是一个一次函数）。

[$\color{green}{\checkmark}$](https://codeforces.com/contest/1656/submission/255832385)

---

## 作者：Schi2oid (赞：3)


考虑一个不用动脑子的 $O(n\log V)$ 做法。

考虑每一棵可能的生成树，其边权和随 $t$ 变化形成一条直线。根据定义，对于所有这样的直线对位取 $\min$ 得到的函数就是 $f(t)$。而直线取 $\min$ 得到的函数显然具有凸性。只需要判断斜率最小的直线和斜率最大的直线的斜率是否同号，若是则输出 `INF`，否则在凸包上二分斜率即可找到最大值。

对于某个特定的 $t$，计算 $f(t)$ 的值，可以将边权拆贡献，转化为 $(a_i+t)(a_j+t)-t^2$，根据 `prim` 算法每次选取未定点中 $a_i+t$ 最大、最小，和已定点中最大、最小尝试连边，取产生边权最小的边即可。

---

## 作者：SamHJD (赞：2)

## [CF1656F Parametric MST](https://www.luogu.com.cn/problem/CF1656F)

### 题意

给出 $n$ 个点的一个无向完全图，对于 $t\in \mathbb R$，$i,j$ 的边权 $w_{i,j}$ 为 $a_i\times a_j+t\times(a_i+a_j)$，整张图的最小生成树边圈和为 $f(t)$，求 $f$ 的最大值，或输出 `INF`。

### 解法

将 $a$ 从小到大排序。

将边权的式子变形，得：

$$w_{i,j}=(a_i+t)\times(a_j+t)-t^2$$

------

若所有 $a_i+t>0$。最小生成树的方案显然是将所有的点连向 $1$，于是答案为：

$$\sum\limits_{i=2}^{n} (a_1\times a_i)+t\times \sum\limits_{i=2}^{n}(a_1+ a_i)$$

两处求和都是定值，根据限制，一种情况是 $a_i$ 为正，一种是 $t>0$。如果一次系数为正，那么不存在最大值，否则 $t$ 一定为正，存在最大值。

若所有的 $a_i+t<0$，同理，最小生成树的方案为将所有点连向 $n$，答案为：

$$\sum\limits_{i=1}^{n-1} (a_n\times a_i)+t\times \sum\limits_{i=1}^{n-1}(a_n+ a_i)$$

同样的，根据限制，一种情况是所有 $a_i$ 为负，一种是 $t$ 为负。如果一次系数为负，那么不存在最大值，否则 $t$ 一定为负，存在最大值。

------

将所有 $a_i$ 加上 $t$（全为正或全为负的情况按上面构造，这里不考虑），整个点权序列变为负、非负两部分，我们思考如何构造最小生成树。

设 $a_x$ 为最小的非负点权，那么 $a_x \dots a_n$ 可以全部连向 $a_1$；$a_2\dots a_{x-1}$ 全部连向 $a_n$，容易证明这是最优的方案。于是答案为：

$$\sum\limits_{i=x}^{n}(a_1\times a_i)+t\times\sum\limits(a_1+a_i)+\sum\limits_{i=2}^{x-1}(a_n\times a_i)+t\times\sum\limits_{i=2}^{x-1}(a_n+a_i)$$

注意当 $a_l \le t \le a_r$ 时，$x$ 是不变的。于是我们只用每次将 $t$ 设为某一 $a_i$ 的倒数计算答案即可。

求和部分可以用前缀和优化，注意下标等细节。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10,INF=1e18;
int T,n,a[N],q[N],ans;
//判断无解
bool inf(){
    int sum1=0,sum2=0;
    for(int i=2;i<=n;++i) sum1+=a[1]+a[i];
    for(int i=1;i<n;++i)  sum2+=a[n]+a[i];
    return (sum1>0||sum2<0);
}
//计算最小生成树边权和
int calc(int x){
    int res=0,t=a[x];
    res+=a[1]*(q[n]-q[x])+a[n]*(q[x]-q[1]);
    res-=t*((n-x)*a[1]+q[n]-q[x])+t*((x-1)*a[n]+q[x]-q[1]);
    return res;
}
signed main(){
    scanf("%lld",&T);
    while(T--){
        scanf("%lld",&n);
        q[0]=0;
        for(int i=1;i<=n;++i) scanf("%lld",&a[i]);
        sort(a+1,a+n+1);
        //前缀和
        for(int i=1;i<=n;++i) q[i]=q[i-1]+a[i];
        if(inf()){
            printf("INF\n");
            continue;
        }
        ans=-INF;
        for(int i=1;i<=n;++i) ans=max(ans,calc(i));
        printf("%lld\n",ans);
    }
    return 0;
}
```

---

## 作者：daniEl_lElE (赞：1)

$a_i\times a_j+t\times(a_i+a_j)=(a_i+t)\times(a_j+t)-t^2$。

于是问题等价于 $b_i=a_i+t$，$w_{i,j}=b_i\times b_j$ 的最小生成树。

容易发现这玩意可以贪心。如果 $b_i$ 同号，那么答案显然为所有都跟绝对值最小的连。否则不论正负，都跟相反符号中绝对值最大的连。

此时我们发现有且仅有连边方式会影响答案（否则是关于 $t$ 的一次函数，两个端点均算出来即可），且连边方式只会跟 $t$ 在 $-a_i\sim-a_{i+1}$ 的区间有关。

于是，我们只需要枚举 $t=-\inf,-a_1,-a_2,\dots,-a_n,+\inf$ 即可。其中 $a_i$ 为排序好的原数组。$-\inf,+\inf$ 是用来判断答案是否为 INF 的。

这样是 $O(n^2)$ 的，然而我们可以将最小生成树的式子写出来，容易理解 $t=-a_x$ 时，$i<x$ 的 $a_i$ 与 $i>x$ 的 $a_i$ 对答案的贡献权值相等，即可前缀和优化。总复杂度 $O(n\log n)$，瓶颈在于排序。具体式子留给读者自行思考。

---

## 作者：Purslane (赞：0)

# Solution

首先判掉无解的情况。（其实后面一起判也可以）

当 $|t| \to + \infty$ 时，$\sum_{(u,v) \in E} a_ua_v$ 显然不值一提。

考虑 $\sum_{(u,v) \in E} a_u+a_v$ 的最大值 $\rm mx$ 和最小值 $\rm mn$。如果 $\rm mn >0$ 或者 $\rm mx < 0$，我们显然可以让 $t$ 趋近于正无穷或者负无穷，此时 $f$ 最大值发散。

考虑到实际上边权是 $(a_u + t)(a_v+t)-t^2$，即总代价是 $\sum_{(u,v) \in E} (a_u+t)(a_v+t) - (n-1)t^2$。

当 $a_u + t > 0$ 的时候，显然他会趋向于 $a_v+ t$ 最小的 $v$ 连边；当 $a_u + a_t < 0$ 的时候，他会趋向于和 $a_v + t$ 最大的 $v$ 连边。

因此不妨将 $a$ 从到达排序。对于每个 $t$，都对应整数 $1 \le k \le n$ 使得 $a_{1,2,3,\dots,k}$ 和 $a_n$ 连边，$a_{k+1,k+2,\dots,n}$ 和 $a_1$ 连边。容易发现这是一棵树。

当 $k$ 固定时，答案是关于 $t$ 的一次函数，而 $t$ 实际上也有固定端点。使用前缀和计算即可。

我不小心打错了一个变量结果过了，看来还有一些我没发现的性质，不过摆烂了。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2e5+10;
int T,n,a[MAXN],pre[MAXN];
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--) {
		cin>>n;
		ffor(i,1,n) cin>>a[i];
		sort(a+1,a+n+1);
		int mn=0,mx=0;
		ffor(i,1,n) {
			pre[i]=pre[i-1]+a[i];
			if(i!=1) mn+=a[1]+a[i];
			if(i!=n) mx+=a[n]+a[i];
		}
		if(mn>0||mx<0) {cout<<"INF\n";continue ;}
		int ans=-LONG_LONG_MAX;
		ffor(i,1,n-1) {
			int l=-a[i+1],r=-a[i];
			int k=pre[n]+a[1]*(n-i-1)+a[n]*(i-1);
			ans=max(ans,l*k+a[n]*(pre[i]-a[1])+a[1]*(pre[n]-pre[i]));	
			ans=max(ans,r*k+a[n]*(pre[i]-a[1])+a[1]*(pre[n]-pre[i]));	
		}
		cout<<ans<<'\n'; 
	}
	return 0;
}
```

---

## 作者：SnowTrace (赞：0)

简单推性质题。

先考虑没有最大值的情况。

我们任意取一颗生成树都可以表达成 $kt+b$ 的形式，后面的 $b$ 显然和有没有解没关系，不需要考虑。

观察可以发现，只要 $t$ 不全为正或全为负，那么就不可能没有最大值。

也就是说我们只需要求出这个 $t$ 的最大值和最小值然后判断一下即可。

考虑这个生成树的限制，如果一个点度数为 $d$ 那么会给 $k$（上文中 $t$ 的系数） 带来 $d \times a_i$ 的贡献，而每个点度数应该大于等于 $1$，所以最小的情况是最小值的点为中心的一个菊花图，最大的情况是最大值的点为中心的菊花图。

现在我们判断完了是否有解，考虑如何算出答案。

算答案的话就需要把 $b$ 考虑进去了。

先考虑一个简单的问题，如果 $t=0$ 答案是什么？

容易发现，$t = 0$ 时， $a_i>0$ 的所有点应该都连向最小值，$a_i<0$ 的所有点应该连向最大值，证明显然。

我们考虑 $t$ 不为 $0$ 时能否继续有这个优秀的性质。

拆式子：$a_ia_j+t(a_i+a_j) = (t+a_j)a_i+ta_j$

$t$ 足够小时，所有点都连向最大值，考虑由此进行调整。

随着 $t$ 的增大，当 $t+a_j$ 的正负性改变时，把 $j$ 从原本连向最大值改成连向最小值，归纳可以发现这样一定是最优的，从而我们对于每一个 $t$ 都可以知道树的形态并且快速计算出答案。

那么也就是说我们已经知道了 $f(t)$ 这样的一个分段函数在各个时候连出的生成树的形态。而且根据一开始的结论，容易发现每一段应该都是关于 $t$ 的一次函数。那么这个东西就有单调性，最大值肯定会取在函数分界处，也就是只需要考虑 $\exist i,a_i+t = 0$ 的所有情况就可以。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n;int a[200005],pre[200005];
void solve(){
	cin >> n;for(int i = 1;i<=n;i++)cin >> a[i];
	sort(a+1,a+1+n);
	int mx = 0,mn = 0,sum = 0;
	for(int i = 1;i<=n;i++)mx+=a[i],mn+=a[i],sum+=a[i],pre[i] = pre[i-1]+a[i];
	mx+=(n-2)*a[n],mn+=(n-2)*a[1];
	if(mx>0 and mn>0){
		cout << "INF" << endl;return;
	}
	if(mx<0 and mn<0){
		cout << "INF" <<  endl;return;
	}
	int ans = -1000000000000000000;
	for(int i = 2;i<=n;i++){
		int t = -a[i];
		int tot = t*(pre[n-1]-pre[1])+a[1]*a[n]+t*(a[1]+a[n]);
		tot+=a[1]*(pre[n-1]-pre[i-1]+(n-i)*t)+a[n]*(pre[i-1]-pre[1]+(i-2)*t);
		ans=max(ans,tot);
	}
	cout << ans << endl;
}
signed main(){
	int t;cin >> t;
	while(t--){
		solve();
	}
}/*
如果我爱上你的笑容
要怎么收藏 要怎么拥有
如果你快乐不是为我
会不会放手其实才是拥有
*/
```

---

