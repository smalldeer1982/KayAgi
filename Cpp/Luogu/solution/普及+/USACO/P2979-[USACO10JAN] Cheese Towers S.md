# [USACO10JAN] Cheese Towers S

## 题目描述

FJ 要建一个奶酪塔，高度最大为 $T\ (1 \le T \le 10^3)$ 。他有 $N\ (1 \le N \le 10^2)$ 种奶酪。第 $i$ 种奶酪的高度为 $H_i\ (5\le H_i \le T\text{ 且 }5 \mid H_i)$ ，价值为 $V_i\ (1 \le V_i \le 10^6)$ 。一块高度 $H_i\ge K\ (1 \le K \le T)$ 的奶酪被称为大奶酪，如果一个奶酪上方有大奶酪（如果有多块就只算一次），这个奶酪的高度 $H_i$ 就会变成原来的 $\frac{4}{5}$。FJ 想让他的奶酪塔价值和最大。请你求出这个最大值。

例如，考虑一种奶酪塔，其最大高度可以是 $53$，可以用三种类型的奶酪块建造。大块是大于或等于 $25$ 的块。下面是他堆叠的各种奶酪块的值和高度的图表：

|类型|价值|高度|
| :----------: | :----------: | :----------: |
|1|100|25|
|2|20|5|
|3|40|10|

FJ建造了以下奶酪塔：

|类型|价值|高度|
| :----------: | :----------: | :----------: |
|1|100|25|
|2|20|4|
|3|40|8|
|3|40|8|
|3|40|8|

总高度是 $25 + 4 + 8 + 8 + 8 = 53$，除塔顶奶酪外，其余高度均被压低。总价值是 $100 + 20 + 40 + 40 + 40 = 240$。

## 样例 #1

### 输入

```
3 53 25 
100 25 
20 5 
40 10 
```

### 输出

```
240 
```

# 题解

## 作者：reek (赞：74)

如果没有大奶酪，这道题就是一道裸的完全背包。

稍微思考能够发现，最有解只有两种情况：要么整个奶酪塔上都没有大奶酪，要么奶酪塔的最上面一块是大奶酪。因为如果在奶酪塔的中间位置有一个大奶酪，那么显然把这块大奶酪提到奶酪塔的最顶端不会使答案变劣。

对于第一种情况，直接做完全背包即可。

对于第二种情况，我们可以枚举最上面的那块大奶酪i，用v[i]+f[(T-h[i])\*5/4]更新ans。

最后两种情况取max即可。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n,T,k,ans,f[2000],v[1000],h[1000];
int main() {
    scanf("%d%d%d",&n,&T,&k);
    for (int i=1;i<=n;i++) {
        scanf("%d%d",&v[i],&h[i]);
        for (int j=h[i];j<=T*5/4;j++)
        f[j]=max(f[j],f[j-h[i]]+v[i]);
    }
    ans=f[T];
    for (int i=1;i<=n;i++)
    if (h[i]>=k) ans=max(ans,f[(T-h[i])*5/4]+v[i]);
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：Cxs3 (赞：13)

题目链接：https://www.luogu.org/problem/P2979

## 题目分析
这道题的代码是简单的，就是思考过程有难度。

很容易就可以看出，这是个完全背包。那么怎么解决大奶酪的问题呢？  
运用贪心的思想去思考，可以发现，最优解只有两种情况：  
- 塔里没有一块是大奶酪。
- 塔上最顶端那一块是大奶酪。这样就可以让下面所有奶酪的高度都变为原来的$\frac{4}{5}$。

对于第一种情况，直接完全背包即可，将答案记录在$f[ \ ]$中。  
对于第二种情况，我们可以枚举每一块大奶酪，求当它在顶端时的答案。假设它是$i$，那么答案即为：$v[i]$加上某个$f[x]$。  
那么$x$等于几呢？  
不考虑大奶酪的话，$x=T-h[i]$。但有了大奶酪之后，$\frac{4}{5}x=T-h[i]$，即$x=(T-h[i])\times \frac{5}{4}$。此时答案即为$v[i]+f[(T-h[i])\times \frac{5}{4}]$，再与第一种情况取$max$即可。

这里还要提醒一下，求完全背包时，$j$要从$h[i]$循环到$T\times \frac{5}{4}$而不是$T$。因为求第二种情况时可能会用到。

## 代码实现
```cpp
#include<bits/stdc++.h>
const int N=100+10;
const int T=5000;
using namespace std;

int n,t,k,ans;
int v[N],h[N],f[T];

int main()
{
	int i,j,now;
	cin>>n>>t>>k;
	for(i=1;i<=n;i++) cin>>v[i]>>h[i];
	for(i=1;i<=n;i++)
	  for(j=h[i];j<=t*5/4;j++) f[j]=max(f[j],f[j-h[i]]+v[i]);//完全背包 
	ans=f[t];//ans初始化为f[t] 
	for(i=1;i<=n;i++)
	{
	  if(h[i]<k) continue;//不是大奶酪就不做 
	  now=v[i]+f[(t-h[i])*5/4];//用now求当前答案 
	  ans=max(ans,now);//更新 
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：WDAGLVE (赞：8)

题意：在n块奶酪中选取若干块总高度不超过t的奶酪，使其价值最大。其中，高度在k以上的奶酪可以挤压它下面的奶酪，使他们的高度只有原来的4/5.


分析：首先，从题目中就可以看出这是一道完全背包的题目，但是由于高度大于k的奶酪会使它下面的奶酪高度变小，所以需要把状态拆分。所以我们可以在完全背包的基础上在加一层，用f[i][0]表示高度为i且存在大奶酪的最优解，用f[i][1]表示高度为i且不存在大奶酪的最优解。


对于没有大奶酪的情况我们可以直接用完全背包的状态转移方程搞定，但是在有大奶酪的情况下我们还需要考虑到大奶酪的位置，用贪心思想不难得出大奶酪一定要放在最上面才是最优解（可以挤压更多的奶酪），若是有两个以上的大奶酪，则要把高度最小的大奶酪放到最上面（都放在上面大奶酪不会被挤压到，高度不变，所以要把这个位置留给高度最小的大$奶酪）。


所以我们要把所有的大奶酪从小到大排列，先选大奶酪。一开始，所有的f[j][1]都要定义成无解，当第i个是大奶酪时，它的值就等于f[(j−a[i].w)∗4/5][0]+a[i].v（选取第i个奶酪，这样就有大奶酪了）。所以会有：


f[j][0]=max(f[j][0],f[j−a[i].w][0]+a[i].v); 

当f[j−a[i].w∗4/5][1]存在解时：f[j][1]=max(f[j][1],f[j−a[i].w∗4/5][1]+a[i].v);

当第i个是大奶酪时：f[j][1]=max(f[j][1],f[(j−a[i].w)∗4/5][0]+a[i].v);

最后的答案就是 max(f[m][0],f[m][1])

参考代码：






```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std ;
const int maxn=110,maxm=1010 ;
struct t{int v,w;}a[maxn] ;
bool cmp1(t a,t b)
{
    return a.w>b.w ;
}
bool cmp2(t a,t b)
{
    return a.w<b.w ;
}
int n,m,k,temp,f[maxm][2] ;
int main()
{
    freopen("chess.in","r",stdin) ;
    freopen("chess.out","w",stdout) ;
    scanf("%d%d%d",&n,&m,&k) ;
    for (int i=1;i<=n;i++)
        scanf("%d%d",&a[i].v,&a[i].w) ;
    for (int i=1;i<=m;i++) f[i][1]=-1 ;
    sort(a+1,a+1+n,cmp1) ;
    for (;a[temp+1].w>=k;temp++) ;
    sort(a+1,a+1+temp,cmp2) ;
    for (int i=1;i<=n;i++)
        for (int j=a[i].w;j<=m;j++)
        {
            f[j][0]=max(f[j][0],f[j-a[i].w][0]+a[i].v) ;
            if (f[j-a[i].w*4/5][1]!=-1) f[j][1]=max(f[j][1],f[j-a[i].w*4/5][1]+a[i].v) ;
            if (a[i].w>=k) f[j][1]=max(f[j][1],f[(j-a[i].w)*4/5][0]+a[i].v) ;
        }
    printf("%d",max(f[m][0],f[m][1])) ;
    return 0 ;
}
```

---

## 作者：Awdrgysxc (赞：7)

## 【分析】

题目说高度为T,每个奶酪有价值也有体积，要你算最大价值；这不是一个背包吗，但是题目还说：一块高度Hi>=K的奶酪被称为大奶酪，一个奶酪如果在它上方有大奶酪（如果有多块就只算一次），它的高度Hi就会变成原来的4/5；我们可以用贪心，把大奶酪放到最顶上，这样就也许就能装下更多东西了，BUT

#### 前面完全背包怎么处理
按常规处理？也许可以，但比较麻烦；我们可以把背包容量扩大为原来的 $5/4$（一定是5/4） ；因为每个奶酪都被缩小了4/5，所以要算到5/4,这样后面打的放上来就很方便了；（详见代码）

## 【Code】
```cpp
#include <cstdio>
#include <cstring>
#define re register
#define max(x,y)(x>y?x:y)
#define min(x,y)(x<y?x:y)

inline int read() {
    re int ret=0;re bool flag=0;re char c=getchar();
    while((c<'0')|(c>'9'))flag^=!(c^'-'),c=getchar();
    while((c>='0')&(c<='9'))ret=(ret<<3)+(ret<<1)+(c^'0'),c=getchar();
    return flag?-ret:ret;
}

void Put(int x)
{
    if(x < 0) {putchar('-'),x = -x;}
    if(x > 9) Put(x / 10);
    putchar(x % 10 + '0');
}
const int M = 2018;

int n,dp[M],w[M],v[M],T,K;
int Ans;

inline void inp()
{
    n = read(),T = read(),K = read();
    for(re int i = 1;i <= n; i++)
        w[i] = read(),v[i] = read();
}

inline void solve()
{
    for(re int i = 1;i <= n; i++)
        for(re int j = v[i];j <= T * 5 / 4; j++)
            dp[j] = max(dp[j],dp[j - v[i]] + w[i]); 
        
        //先做一遍完全背包，把体积扩大为T * 5 / 4
    Ans = dp[T]; //Ans一定是dp[T]因为考虑最顶放大奶酪可能使答案更优
    //但也不一定，所以这里要赋值为dp[T]
    
    for(re int i = 1;i <= n; i++)
        if(v[i] >= K) Ans = max(Ans,dp[(T - v[i]) * 5 / 4] + w[i]);
        
        //因为背包容量被我们扩大了5/4，所以这里也要乘回去
}

inline void output()
{
    Put(Ans);
}

int main(void)
{
    inp();
    
    solve();
    
    output();
    return 0;
}
```

---

## 作者：ez_lcw (赞：4)

一种思路奇特的做法。

看到题目容易联想到背包dp，~~因为看上去很像~~。

但是我们并不知道上面有没有大奶酪。

**所以我们不妨倒过来看，从上往下加奶酪。**

设 $dp(i,1/0)$ 表示当前从上往下的累加高度为 $i$，这之中有/无大奶酪。

显然，当我们考虑新加一个奶酪时，有：

$$\begin{cases}
dp(i,0)=\max(dp(i-h_j,0)+v_j)\ \ (h_j<K)\\
dp(i,1)=\max(dp(i-h_j,0)+v_j)\ \ (h_j\geq K)
\end{cases}$$

然后对于 $dp(i,1)$，还有：

$$dp(i,1)=\max(dp(i-\frac{4}{5}h_j,1)+v_j)$$

总的时间复杂度 $O(nt)$，听说 $O(n^2t)$ 也能过……

```cpp
#include<bits/stdc++.h>

#define N 110
#define T 1010

using namespace std;

int n,t,k,ans;
int v[N],h[N];
int dp[T][2];

int main()
{
	scanf("%d%d%d",&n,&t,&k);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&v[i],&h[i]);
	memset(dp,128,sizeof(dp));
	dp[0][0]=0;
	for(int i=0;i<=t;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(i-h[j]>=0)
			{
				if(h[j]<k) dp[i][0]=max(dp[i][0],dp[i-h[j]][0]+v[j]);
				else dp[i][1]=max(dp[i][1],dp[i-h[j]][0]+v[j]);
			}
		}
		for(int j=1;j<=n;j++)
			if(i-h[j]*4/5>=0)
				dp[i][1]=max(dp[i][1],dp[i-h[j]*4/5][1]+v[j]);
		ans=max(ans,max(dp[i][0],dp[i][1]));
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：linyinuo2008 (赞：3)

[原题链接](https://www.luogu.com.cn/problem/P2979)

这是一道非常不错的完全背包题，我们一起来看一看。

# 1、题意理解

先说几个小点：

- 输入时先输入奶酪的价值，再输入高度。

- 有一种奶酪叫做大奶酪，高度比$k$大。

- 大奶酪下边的所有奶酪的高度都变为原来的$\dfrac{4}{5}$。

这题一个很重要的点就是有大奶酪，这种奶酪能够压缩下边的奶酪，我们该怎样处理呢？


# 2、算法实现
这道题如果没有大奶酪的话，就是一道[完全背包](https://www.cnblogs.com/mfrank/p/10803417.html)的模板题，我们把$v_i$看成每个奶酪的价值，把$h_i$看成每个奶酪的花费，并且每个奶酪都有无限块可取。代码如下：

```cpp
void complete_pack(int n,int t)//n为奶酪个数，t为最大高度
{
	for(int i=1;i<=n;i++)//最外层枚举物品个数 
	{
		for(int j=h[i];j<=t;j++)//完全背包正序枚举容量 
		{
			f[j]=max(f[j],f[j-h[i]]+v[i]);//转移 
		}
	}
} 
```
但是我们现在有大奶酪，该怎么求出最优解呢？

经过仔细分析，**我们可以发现最优解只能出现在两种情况（敲黑板）：**

**1、一块大奶酪都没有，直接上完全背包的板子。**

**2、最顶上的那块是大奶酪，因为如果大奶酪不在最顶上，把他一到最顶上一定可以使解更优，因为能够使更多的奶酪高度减小。**

所以我们分别做两次背包转移：第一次是先来一次完全背包，第二次是考虑最顶上为大奶酪的情况。

我们设$f_i$表示当奶酪塔总高度为$i$时的最大价值，于是当我们枚举最顶上的大奶酪时我们可以考虑一下转移方程为：$ans=min($ $ans,$ $f_{(t-h_i) \times \frac{5}{4}}+v_i)$。这个转移方程的意思就是我们可以把这块大奶酪放在最顶上，那么这里奶酪塔的总价值就是原来高度为最大高度减去这块大奶酪的高度再乘以$\dfrac{5}{4}$，因为它下面的所有奶酪的高度都变为了原高度的$\dfrac{4}{5}$。
因此，在第一次进行完全背包的时候，要把物品容量枚举到$T$的$\dfrac{5}{4}$倍，才能进行之后的转移。

所以我们的大体步骤就确定下来了，后面的就是代码实现了：

1. 先上一遍完全背包的板子，但是要把容量枚举到$\dfrac{5}{4}T$。

2. 把$ans$先设为$f_t$。

3. 枚举每个奶酪，如果这块奶酪是大奶酪，那就试一试它在顶上的情况。

4. 输出$ans$。

# 3、代码

代码中有注释欧。

```cpp
#include <iostream>
using namespace std;

const int NR=105;
const int MR=1400;//最大容量必须开到5/4倍
int n,t,k;
int v[NR],h[NR],ans;
int f[MR];

int max(int a,int b)//手写max更快
{
	return a>b?a:b;
}

int main()
{
	f[0]=0;
	cin>>n>>t>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>v[i]>>h[i];
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=h[i];j<=t*5/4;j++)//枚举到容量的5/4倍
		{
			f[j]=max(f[j],f[j-h[i]]+v[i]);//上一边完全背包
		}
	}
	ans=f[t];//先把ans设为f[t]
	for(int i=1;i<=n;i++)
	{
		if(h[i]>=k)//如果它是块大奶酪
			ans=max(ans,f[(t-h[i])*5/4]+v[i]);//那么尝试把它放在最顶上
	}
	cout<<ans;//输出
	return 0;
}
```
**若有错误，欢迎指出！**

---

## 作者：Kirisame_Marisa_ (赞：3)

[传送门](https://www.luogu.org/problemnew/show/P2979)

dp.  
参考第一篇题解，先跑一次完全背包。

（帮第一篇题解的）补充说明：(?  
 1. 为什么完全背包的时候不要判大奶酪  
 2. 为什么完全背包的循环是从$h_i$到$\frac{5}{4}T$  
 3. 为什么只要枚举一个大奶酪
 
### 1. 为什么完全背包的时候不要判大奶酪  &&
### 3. 为什么只要枚举一个大奶酪

就算之前的奶酪被我们枚举的奶酪压扁了，  
那么我们在最后的循环中枚举的时候，之前放置的所有奶酪都会被压扁。  
这时候已经将之前没有做的事（压扁）一起做完了。


### 2. 为什么完全背包的循环是从$h_i$到$\frac{5}{4}T$  

记得我们的完全背包吗？  
一维的背包`dp[i]`就是指`当前背包里的总重量为i时的最优答案`。  
如果我们在最后枚举的时候，除去当前的大奶酪，我们剩下奶酪的总体积不就是$T-h_i$吗？  
# 很遗憾这是错误的
因为此时的$T-h_i$应当是目前剩下的奶酪**被压缩之后**的总体积。它们的**原始体积**应当乘以$\frac{5}{4}$（因为你压缩的时候乘了$\frac{4}{5}$）。最坏情况下，乘法的结果会接近$\frac{5}{4}T$（$h_i=1$时），如果你只处理到了$T$，那么恭喜`63pts`:^)。

---

## 作者：SCUT_HYX (赞：2)

**更好的阅读体验：[黄毛猫_HYX的博客](https://www.luogu.org/blog/jerriehmm/solution-p1983)**

**~~推销下我的空间~~：[蒟蒻](https://www.luogu.org/blog/jerriehmm/)**

# 解题关键：完全背包类DP

## 1.初始

### 1.1 审题

①大奶酪：高度$h[i]≥ K$的奶酪

②大奶酪作用：使得下面的奶酪体积变为原来的$\frac{4}{5}$

③一种奶酪可以放多个

### 1.2 思路

如果没有大奶酪的特殊效果，这道题应该是完全背包秒切。加上之后是只要稍加思考，其实再加入一个贪心思想即可。

再审题，我们看到，大奶酪只能使得压在它下面的奶酪体积变小，但**奶酪的放置位置是不会影响价值的**，于是我们得出主要策略：**如果要放大奶酪，就要放在最上面**。

## 2.状态转移方程

### 2.1 第一次方程

~~如果不会完全背包的建议先去做些模板题，这里不赘述了~~

第一次先正常跑一次完全背包：

$f[j]=f[j-h[i]]+v[i],i=1...n,j=h[i]...m\times \frac{5}{4}(m$为总最高高度$)$

此处m$\times\frac{5}{4}$是因为要考虑到第二次方程考虑最顶上放/不放大奶酪时，可能会有一开始体积超过$\frac{5}{4}$的，一压再加上大奶酪体积小于$m$的情况

### 2.2 第二次方程

第二次枚举放大奶酪的情况：

$ans=max(f[(m-h[i])\times\frac{5}{4}]+v[i]),h[i]\ge K$

## 3.注意

①建议开long long

②第一次第二次DP均需和$\frac{5}{4}$有关，读者自行注意

## 4.完整AC代码
```cpp
#include<cstdio>
#include<iostream>
using namespace std;
long long n,m,k;
long long h[1013],v[1013],f[1013];			//v->价值，h->高度，f->dp数组 
int main()						
{
    scanf("%lld%lld%lld",&n,&m,&k);
    for(int i=1;i<=n;++i) scanf("%lld%lld",&v[i],&h[i]);
    for(int i=1;i<=n;++i)
        for(int j=h[i];j<=m*5/4;++j)
             f[j]=max(f[j],f[j-h[i]]+v[i]);	//dp方程 
    long long ans1=f[m],ans2=0;				//ans1->不加任何大奶酪
											//ans2->加大奶酪在最顶上 
    for(int i=1;i<=n;++i)
        if(h[i]>=k)
            ans2=max(ans2,f[(m-h[i])*5/4]+v[i]);
    ans1=max(ans1,ans2);
    printf("%lld",ans1);					//输出较大的 
    return 0;
}
```
## 萌新第五篇题解，有建议请评论或小窗私聊

---

## 作者：MilkyCoffee (赞：2)

这是一道完全背包板子题，应该有手就能20min内打出来，当然**点睛之笔没有想到的另当别论**

本篇的点睛之笔：**分有大奶酪和无大奶酪来看，如果无大奶酪就是一道完全背包板子题了**

### 思路区

1. 没有大奶酪

	很明显，奶酪有无限种，相信这里没什么好说的，就是一个完全背包板子。
    
    核心代码实现：
    
    ```
    int n, t, k;
    int v[1005], h[1005];
    //  价值       高度
    int dp[1005];
	
	cin >> n >> t >> k;
	for (int i = 1; i <= n; i++) {
		cin >> v[i] >> h[i];
	}
	for (int i = 1; i <= n; i++) {
		if (h[i] > k) continue;
		// 如果是大奶酪就跳过，这里算的是不是大奶酪的
		for (int j = h[i]; j <= t; j++) {
			dp[j] = max(dp[j], dp[j-h[i]] + v[i]);
		}
	}
    int ans = dp[t];
    cout << ans << endl;
    ```
    
2. 有大奶酪

	如果有大奶酪的话，而且要放到奶酪塔上去，当然，是放在最上方最划算。于是我们只需要枚举每一个大奶酪（用来计算把大奶酪 $x$ 放在最上方的 $dp$ ，最后求出答案的最大值）

	核心代码实现：

    ```
    int n, t, k;
    int v[1005], h[1005];
    //  价值       高度
    int dp[1005];
    
	cin >> n >> t >> k;
	for (int i = 1; i <= n; i++) {
		cin >> v[i] >> h[i];
	}
	int ans;
	for (int x = 1; x <= n; x++) { // 枚举放在最上面的大奶酪
		if (h[x] < k) continue; // 如果是小奶酪，不考虑
		if (h[x] > t) continue; // 如果大奶酪比最大高度大，不考虑
		memset(dp, 0, sizeof(dp));
		for (int i = 1; i <= n; i++) {
			for (int j = h[i] / 5 * 4; j <= t - h[x]; j++) {
				// 我们已经选了h[x]号大奶酪放在最上面，只需要对剩下的做一次完全背包
				dp[j] = max(dp[j], dp[j-h[i]/5*4] + v[i]);
			}
		}
		// 现在的dp是以大奶酪(x)放在奶酪塔最上面的情况
		ans = max(ans, dp[t-h[x]] + v[x]);
		// 换一个放在最上面的大奶酪重新dp
	}
	cout << ans << endl;
    ```

### 你绝对会掉进去的坑...

1. 计算完无大奶酪之后要**保存答案！**
2. 不要忘了有大奶酪的情况是**dp[j-h[i]/5\*4 + v[i]！不要忘了乘五分之四！**
3. 最后有大奶酪的答案是**算出来的答案是要减去大奶酪的高度再加上大奶酪的价值的！不是直接的dp[t]！**

### 代码实现

```
#include <bits/stdc++.h>
using namespace std;

int n, t, k;
int v[1005], h[1005];
int dp[1005];

int main() {
	cin >> n >> t >> k;
	for (int i = 1; i <= n; i++) {
	    cin >> v[i] >> h[i];
	}
	
	for (int i = 1; i <= n; i++) {
	    if (h[i] > k) continue;
	    for (int j = h[i]; j <= t; j++) {
	        dp[j] = max(dp[j], dp[j-h[i]] + v[i]);
	    }
	}
	
	int ans = dp[t];
    
	for (int x = 1; x <= n; x++) { 
	    if (h[x] < k) continue; 
	    if (h[x] > t) continue; 
	    memset(dp, 0, sizeof(dp));
	    for (int i = 1; i <= n; i++) {
	        for (int j = h[i] / 5 * 4; j <= t - h[x]; j++) {
	            dp[j] = max(dp[j], dp[j-h[i]/5*4] + v[i]);
	        }
	    }
	    
	    ans = max(ans, dp[t-h[x]] + v[x]);
	}
	cout << ans << endl;
    return 0;
}
```

### 祈祷区

管理员求过，路过人求赞！希望能对你的OI之路献出一点点的帮助呢！

---

## 作者：syfufo (赞：2)

//这题实际上可以转化为一个完全背包来求解。

//只需要考虑在j高度放第i块之后会不会再放上巨无霸砖即可

//具体请研究代码，dp数组第3维中，0表示之后不再放巨无霸砖，1表示之后还要放。

```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
#define MAXN 1000+2
struct Node{
    int Vi;
    int Hi;
};
int dp[102][MAXN][2];
int T,n,k;
Node jl[MAXN];
bool cmp(Node a,Node b){
    return a.Hi<b.Hi;
}
bool cmp2(Node a,Node b){
    return a.Hi>b.Hi;
}
void input(){
    cin>>n>>T>>k;
    for(int i=1;i<=n;++i){
        cin>>jl[i].Vi>>jl[i].Hi;
    }
    sort(jl+1,jl+n+1,cmp);
    int jll=-1;
    for(int i=1;i<=n;++i){
        if(jl[i].Hi>=k) {
            jll=i;
            break;
        }
    }
    if(jll!=-1) sort(jl+jll,jl+n+1,cmp2);
}
void syf(){
    for(int i=1;i<=n;++i){
        for(int j=0;j<=T;++j){
            dp[i][j][0]=max(dp[i][j][0],dp[i-1][j][0]);
            dp[i][j][1]=max(dp[i][j][1],dp[i-1][j][1]);
            if(jl[i].Hi<k){
                for(int k=1;k*jl[i].Hi<=j;++k){
                    dp[i][j][0]=max(dp[i][j][0],dp[i-1][j-k*jl[i].Hi][0]+k*jl[i].Vi);
                }
                for(int k=1;(k*jl[i].Hi*4/5)<=j;++k){
                    dp[i][j][1]=max(dp[i][j][1],dp[i-1][j-(k*jl[i].Hi*4/5)][1]+k*jl[i].Vi);
                }
            }
            else{
                for(int k=1;(k*jl[i].Hi*4/5)+jl[i].Hi/5<=j;++k){
                    dp[i][j][0]=max(dp[i][j][0],dp[i-1][j-((k*jl[i].Hi*4/5)+jl[i].Hi/5)][1]+k*jl[i].Vi);
                }
                for(int k=1;(k*jl[i].Hi*4/5)<=j;++k){
                    dp[i][j][1]=max(dp[i][j][1],dp[i-1][j-(k*jl[i].Hi*4/5)][1]+k*jl[i].Vi);
                }
            }
        }
    }
    cout<<dp[n][T][0]<<endl;
}
int main(){
    input();
    syf();
    return 0;
}
```

---

## 作者：zplqwq (赞：1)



给同学讲完全背包时找到的一个好题。

**题目分析**

我们首先知道，如果这个题没有大奶酪，那么就是一个裸的完全背包，代码可以参考[这题](https://www.luogu.com.cn/problem/P1616)。

这题难就难在如果我们加上大奶酪之后要怎么处理。

首先，我们知道最优解只有可能是一下两种情况：

1. 塔内没有大奶酪，也就是完全背包的板子。
2. 我们选择把大奶酪放到最顶端，因为如果在这个奶酪塔里有大奶酪，那么把它放到最顶端肯定不会使答案变差。

答案是两者取最大值。

对于第二种情况的处理，我们可以尝试去枚举最顶端的那个大奶酪，然后用	$v_i+f_{(t-c[i])\times5/4}$ 来取最大值，从而可以求出第二种的答案。

其实这道题的核心就是第二种情况的处理，因此这里给出第二种情况的代码。

```cpp
	for(int i=1;i<=n;i++)
	{
		if(c[i]>=k)//如果是大奶酪
		{
			int tmp1=v[i]+f[(t-c[i])*5/4];//求出要被用来更新这个值
			tmp=max(tmp1,tmp);//更新值
		}
	}
```

---

## 作者：minxu (赞：1)

[题目](https://www.luogu.com.cn/problem/P2979)
给出一种直接dp求解代码比较简单的做法

f[j][0/1]表示前j高度i个奶酪有没有大奶酪的最大值

转移的话f[j][0]只能从小的转移
f[j][1]可以从f[j-a[i]/5*4][1]或当前作为大奶酪转移

注意完全背包空间要在外层循环
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2200;
int f[N][2],v[N],h[N];
int n,m,t,k;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
struct node{
    int h,v;
}a[N];
long long ans=0;
signed main()
{
    n=read();t=read(),k=read();
    for(int i=1;i<=n;++i)
    a[i].v=read(),a[i].h=read();
    for(int j=0;j<=t;++j)
    for(int i=1;i<=n;++i)
    {
        if(j>=a[i].h&&a[i].h<k)f[j][0]=max(f[j][0],f[j-a[i].h][0]+a[i].v);
         f[j][1]=f[j][1];
        if(a[i].h>=k)
        {
        if(j>=a[i].h)f[j][1]=max(f[j][1],f[j-a[i].h][0]+a[i].v);
        }
        if(j>=(a[i].h/5*4)&&f[j-(a[i].h/5*4)][1])f[j][1]=max(f[j][1],f[j-(a[i].h/5*4)][1]+a[i].v);
        ans=max(ans,max(f[j][1],f[j][0]));       
    }

    cout<<ans<<endl;
    return 0;
}
```


---

## 作者：Zenith_Yeh (赞：1)

这题共有两种情况：没有一块大奶酪 或 大奶酪在最顶端。（Because 如果大奶酪在中间，那么放在顶端一定更优。）

### first:

没有一块大奶酪，直接上完全背包。

### second:

我们可以枚举最上面的那块大奶酪$i$，用$v_i+f_{t-h_i}* \frac{5}{4}$更新$ans$

#### 上菜

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t,k,f[1305],v[1005],h[1005];
int main()
{	cin>>n>>t>>k;	
	for(int i=1;i<=n;i++)
	{	cin>>v[i]>>h[i];
		for(int j=h[i];j<=t*5/4;j++)
			f[j]=max(f[j],f[j-h[i]]+v[i]);
	}
	int ans=f[t];
	for(int i=1;i<=n;i++)
		if(h[i]>=k)ans=max(ans,f[(t-h[i])*5/4]+v[i]);
	cout<<ans;
	return 0;
}
```


---

## 作者：呆瓜yy (赞：1)

### ~~这是一篇很水的题解~~

我们知道，只有最上面的奶酪体积不变，其余的奶酪的体积都变为原来的4/5

也就是说，这题可以看作去掉最上面的奶酪、所有奶酪体积均为原来的4/5的背包问题

但出现一个问题，万一所有奶酪都达不到大奶酪的标准，就没有所谓的体积变小

所以，保险起见，还是算两次吧（虽然数据应该没有这么坑）

### 具体思路

（1）用数组f记录体积未被压缩时的最大价值

（2）用数组ff记录体积被压缩后的最大价值

（3）for循环枚举去掉最上面奶酪体积的最大价值ff[j]加上最上面的奶酪价值v[i]

（4）比较压缩前后的最大价值（如果不存在大奶酪，则ff数组均为0，输出压缩前最大价值；反之，压缩后最大价值必然大于等于压缩前最大价值）

### 贴代码
```cpp
// luogu-judger-enable-o2
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int vv,n,f[5005],t,ff[5005],fff[5005],ans,h1[5005],h2[5005],v[5005];
int main()
{
	cin>>n>>t>>vv;
	for(int i=1;i<=n;i++)
	  cin>>v[i]>>h1[i];
	for(int i=1;i<=n;i++)
	  h2[i]=h1[i]*4/5;
	  
	for(int i=1;i<=n;i++)
	  for(int j=0;j<=t-h1[i];j++)
	    f[j+h1[i]]=max(f[j+h1[i]],f[j]+v[i]);
	    
	for(int i=1;i<=n;i++)
	  for(int j=0;j<=t-h2[i];j++)
	    ff[j+h2[i]]=max(ff[j+h2[i]],ff[j]+v[i]);
	    
	for(int i=1;i<=n;i++)
	  if(h1[i]>=vv)
	    for(int j=t;j>h1[i];j--)
	      ans=max(ans,ff[j-h1[i]]+v[i]);
	  
	    
	cout<<max(ans,f[t]);
	return 0;
} 
```

---

## 作者：Celebrate (赞：1)

[我的博客](https://blog.csdn.net/zsyzClb/article/details/84422937)

我比较菜，就用了一个比较复杂的dp

这一题不难看出是背包问题，因为dp在这一道题无后效性！

而且N和T的值很小，背包的时间是O(NT），完全承受的了的

可是如果直接从底往上搜，就会很难判断出上面是否有大奶酪，那我们怎么办呢？
既然直接模拟不行，那我们换个方向总行吧！

所以我们直接从上往下找

//dp[i][0]表示第i高度，没有大奶酪的最大值
//dp[i][0]表示第i高度，有大奶酪的最大值
就可以推出动态方程了

首先是头文件和定义的数组：

```
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<queue>
#include<stack>
#include<map>
#include<cmath>
#include<string>
#include<set>
#include<ctime>
using namespace std;
inline int read(){
	int x=0,f=0;char s=getchar();
	while(!isdigit(s))f|=s=='-',s=getchar();
	while( isdigit(s))x=(x<<1)+(x<<3)+s-48,s=getchar();
	return !f?x:-x;
}
inline void print(int x){
     if(x<0)putchar('-'),x=-x;
     if(x>9)print(x/10);
     putchar(x%10+'0');
}
const int N=2e2+20;
const int T=2e3+20;
int n,t,k;
struct node{
	int v,h;
}a[N];
int dp[T][2];
//dp[i][0]表示第i高度，没有大奶酪的最大值
//dp[i][0]表示第i高度，有大奶酪的最大值

```
然后是输入和初始化

dp一开始全部为0，表示不可用，边界dp[0][0]=0

```
n=read();t=read();k=read();
	for(int i=1;i<=n;i++)a[i].v=read(),a[i].h=read();
	memset(dp,-1,sizeof(dp));dp[0][0]=0;


```

然后是核心的dp

我们可以分3种不同的情况进行讨论

1：

当前已经有大奶酪了，就推出dp[ki+a[i].h/5*4][1]

2:

当前无大奶酪，推出dp[ki+a[i].h][0]

3:

当前无大奶酪并且这个就是大奶酪，利用dp[ki][0]推出dp[ki+a[i].h][1]

代码：

```
for(int ki=0;ki<=t;ki++){
	for(int i=1;i<=n;i++){
		if(ki+a[i].h/5*4<=t&&dp[ki][1]!=-1)
			dp[ki+a[i].h/5*4][1]=max(dp[ki+a[i].h/5*4][1],dp[ki][1]+a[i].v);
		if(ki+a[i].h    <=t&&dp[ki][0]!=-1)
			dp[ki+a[i].h    ][0]=max(dp[ki+a[i].h    ][0],dp[ki][0]+a[i].v);
		if(a[i].h>=k	   &&dp[ki][0]!=-1)
			dp[ki+a[i].h    ][1]=max(dp[ki+a[i].h    ][1],dp[ki][0]+a[i].v);
	}
}

```
以及最后的输出

```
int maxx=-1;
for(int i=0;i<=t;i++)maxx=max(maxx,max(dp[i][0],dp[i][1]));
print(maxx);


```



---

## 作者：K0stlin (赞：1)

很容易看出这是一个完全背包。

主要难点是处理大奶酪。

我在代码中开的背包数组是这样定义的：

 _f[x][0/1]（x代表当前高度，[0/1]表示是否有大奶酪，0没有，1有）_
 
 ```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,m,k,x,y,f[1005][5],ans=1<<31;
int main(){
	//freopen("a.in","r",stdin);
	scanf("%d%d%d",&n,&m,&k);
	for(int i=0;i<=m;++i)//一开始没有大奶酪，故不能在下文1处使用
		f[i][1]=1<<31;
	f[0][0]=0;
	for(int i=1;i<=n;++i){
		scanf("%d%d",&x,&y);//x价值，y高度
		if(y>=k){//要想选此大奶酪，必定是在有大奶酪的情况之中，不处理[0]情况
			for(int j=y/5*4;j<y;++j)//2处 独自处理必定只能有大奶酪的部分
				f[j][1]=max(f[j][1],f[j-y/5*4][1]+x);
			for(int j=y;j<=m;++j)//前面是否有大奶酪
				f[j][1]=max(f[j][1],max(f[j-y][0],f[j-y/5*4][1])+x);//1处 前者为之前没有大奶酪，后者反之
		}
		else{//不是大奶酪
			for(int j=y/5*4;j<y;++j)//同上文2处
				f[j][1]=max(f[j][1],f[j-y/5*4][1]+x);
			for(int j=y;j<=m;++j){
				f[j][0]=max(f[j][0],f[j-y][0]+x);//目前没有大奶酪
				f[j][1]=max(f[j][1],f[j-y/5*4][1]+x);//有大奶酪
			}
		}
	}
	for(int i=0;i<=m;++i)//取最大价值
		ans=max(ans,max(f[i][0],f[i][1]));
	printf("%d\n",ans);
	return 0;
}

```
有错误欢迎指出。

---

## 作者：nihanchu (赞：1)

不用大奶酪的部分，我们直接用一个完全背包就可以解决，所以接下来我们只考虑奶酪塔中有大奶酪的情况。


方法一：我们枚举用第i块大奶酪放在最上面（很明显，如果有用大奶酪的话，放在最上面肯定是最优的），然后将t变成t-h[i]，再用所有奶酪4/5的高度,去做一次完全背包，比较好想，复杂度是O(n^2T)，我没有写过这种方法所以不贴代码了。


方法二：我们把奶酪分成大于等于k和不大于k的两部分，用g[j]来表示奶酪塔中有大奶酪的时候在j的高度下我们能获得的最大价值。重点就在于我们如何赋g的初值。


h[i]代表的是第i块大奶酪（必须是大奶酪）g[h[i]]=max(g[h[i]],v[i])，剩余的g[j]都赋为-INF。然后直接用所有奶酪4/5的高度去套完全背包即



g[j]=max(g[j],g[j-h[i]\*4/5]+v[i]);复杂度是O(nT)

这样做的理由在于如果我们要能把g[j]更新到一个正数，那么g[j-h[i]]必须不是-INF,即代表j-h[i]的最优价值所代表的奶酪，至少有一块是未被压缩，用完整高度的来更新它的（即那块垫底的大奶酪），否则，如果都是4/5的高度的话，因为初始-INF的存在，根本就达不到正数。开始的初始化就和方法一中枚举最上面的是哪块大奶酪的作用很像。

方法三（其实不算。。）：其实也可以不要这样初始化，贪心思想，利用了最终在一个奶酪塔中如果有两块即以上的大奶酪的话，放在最上面的那一块一定是高度更小的那一块，那么我们只要按照每块大奶酪的高度从小到大排序，然后，完全不要初始化，按照方法二的动归做就可以了。复杂度O(nlogn+nT);


然后我用f数组套了一遍完全背包，来考虑奶酪塔中没有大奶酪的情况。


下面是我用方法二的程序（我只是为了自己看的懂所以用了两个数组把它们分开，其实没什么必要。。）：


```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
struct ding{long long v,h;}a[110],b[110];
int n,m,k,cnt1,cnt2;
long long f[1010],g[1010],x,y,ans;
int main()
{
  scanf("%d%d%d",&n,&m,&k);
  for (int i=1;i<=n;i++) 
  {
      scanf("%lld%lld",&x,&y);
      if (y>=k) {a[++cnt1].h=y;a[cnt1].v=x;}
      else {b[++cnt2].h=y;b[cnt2].v=x;}
  }
  for (int i=0;i<=m;i++) f[i]=g[i]=-2100000000;
  for (int i=1;i<=cnt1;i++) g[a[i].h]=max(g[a[i].h],a[i].v);
  for (int i=1;i<=cnt1;i++)
  {
      int temp=(a[i].h/5)*4;
      for (int j=temp;j<=m;j++) g[j]=max(g[j-temp]+a[i].v,g[j]);
  }
  f[0]=0;
  for (int i=1;i<=cnt2;i++) 
  {
   int temp=b[i].h/5*4;
   for (int j=b[i].h;j<=m;j++) f[j]=max(f[j],f[j-b[i].h]+b[i].v);
   for (int j=temp;j<=m;j++) g[j]=max(g[j-temp]+b[i].v,g[j]);
  }
  for (int i=0;i<=m;i++) ans=max(max(ans,g[i]),f[i]);
  printf("%lld\n",ans);
  return 0;
}
```
还有方法三的（少了初始化，多了一个排序）：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
struct ding{long long v,h;}a[110],b[110];
int n,m,k,cnt1,cnt2;
long long f[1010],g[1010],x,y,ans;
bool cmp(const ding&c,const ding&d){return (c.h==d.h?c.v<d.v:c.h<d.h);}
int main()
{
  scanf("%d%d%d",&n,&m,&k);
  for (int i=1;i<=n;i++) 
  {
      scanf("%lld%lld",&x,&y);
      if (y>=k) {a[++cnt1].h=y;a[cnt1].v=x;}
      else {b[++cnt2].h=y;b[cnt2].v=x;}
  }
  for (int i=0;i<=m;i++) f[i]=g[i]=-2100000000;
  sort(a+1,a+1+cnt1,cmp); sort(b+1,b+1+cnt2,cmp);
  for (int i=1;i<=cnt1;i++)
  {
      int temp=(a[i].h/5)*4;
      g[a[i].h]=max(g[a[i].h],a[i].v);
      for (int j=temp;j<=m;j++) g[j]=max(g[j-temp]+a[i].v,g[j]);
  }
  f[0]=0;
  for (int i=1;i<=cnt2;i++) 
  {
   int temp=b[i].h/5*4;
   for (int j=b[i].h;j<=m;j++) f[j]=max(f[j],f[j-b[i].h]+b[i].v);
   for (int j=temp;j<=m;j++) g[j]=max(g[j-temp]+b[i].v,g[j]);
  }
  for (int i=0;i<=m;i++) ans=max(max(ans,g[i]),f[i]);
  printf("%lld\n",ans);
  return 0;
}

```

---

## 作者：2333tech (赞：0)

**本题看起来是01背包，~~实际上也是~~**  
在忽略“大奶酪”后，就相当于没有难度。  
关键问题在于如何处理题目中所述：奶酪在大奶酪下面，高度**缩小到原来的 4/5** 。  
与此相关，我们不但要处理**大奶酪的位置**，还要处理下方奶酪的**高度缩减**。  
这里可以利用贪心思维思考一下，大奶酪放在最上面时，总高度最小。  
同时将背包的“高度”扩大到原来的 5/4 即可很方便的处理高度缩减。
（详见代码）
```
#include<bits/stdc++.h>
using namespace std;
int n, t, k;
int v[1010], h[1010];
long long f[2000];
int main()
{
    scanf("%d%d%d", &n, &t, &k);
    for (int i = 1; i <= n;i++) {
        scanf("%d%d", &v[i], &h[i]);
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = h[i]; j <= t * 5 / 4; j++)
        //背包扩大为 5/4 ，相当于将奶酪缩小为 4/5
        //j 从 0 到 t 段是没有大奶酪的普通背包
        {
            f[j] = max(f[j], f[j - h[i]] + v[i]);//初步计算时，忽略大奶酪
        }
    }
    long long ans = f[t];//无大奶酪时
    for (int i = 1; i <= n;i++) {
        if(h[i] >= k) {
            ans = max(ans, v[i] + f[(t - h[i]) * 5 / 4]);
            //t 和 h[i] 都要放大，因为此处的大奶酪位于塔顶，体积没有缩小
        }   //此处是计算包含大奶酪后的最大答案
    }
    printf("%lld\n", ans);
    return 0;
}
```


---

