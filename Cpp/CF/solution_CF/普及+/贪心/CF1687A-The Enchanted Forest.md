# The Enchanted Forest

## 题目描述

> 其实这里被称为魔法森林，基本上就是因为这些有幻觉效果的蘑菇。光是接近这些蘑菇，就好像被施了魔法而产生幻觉。——《东方求闻史纪》

魔理沙来到了魔法森林采摘蘑菇。    
魔法森林可以被抽象成一条有着 $n$ 个节点，从 $1$ 到 $n$ 标号的数轴。在魔理沙出发之前，她的好友帕秋莉运用魔法去侦测了每个节点上的蘑菇数量，分别为 $a_1,a_2,\dots,a_n$。    
在第 $0$ 分钟的时候，魔理沙可以从任意一个节点出发。在每一分钟的时候，她将会做以下事情：

- 她将从节点 $x$ 移动到节点 $y$（$|x-y| \leq 1$，即 $y$ 可能等于 $x$）
- 她将会收集节点 $y$ 上的所有蘑菇。
- 魔法森林中每个节点会再生长出一个蘑菇。

注意，她不能在第 $0$ 分钟的时候收集蘑菇。    
现在魔理沙希望知道她在前 $k$ 分钟的时候，最多能收集到多少个蘑菇。请你帮帮她。

## 样例 #1

### 输入

```
4
5 2
5 6 1 2 3
5 7
5 6 1 2 3
1 2
999999
5 70000
1000000000 1000000000 1000000000 1000000000 1000000000```

### 输出

```
12
37
1000000
5000349985```

# 题解

## 作者：SUNCHAOYI (赞：9)

一开始以为是一个 $\texttt{dp}$，仔细一看发现只是一个普通的贪心。

若 $k \le n$，则不能收集完或恰好收集完所有的蘑菇。如果一个地方的蘑菇被重复地收取，则会浪费之前到达该地所花的时间。我们的目标是使得时间之和最大，故一个地方重复遍历不可取。尝试模拟后可以发现，对于新长出来的蘑菇，收集的数目是确定的，为 $\sum_{i = 1}^{k - 1}$，运用高斯求和公式后得到 $\dfrac{k \times (k - 1)}{2}$。现在问题就转换为求原有蘑菇序列的长度为 $k$ 的区间和的最大值，因此只需要类似滑动窗口般的思想扫一遍求出最大值。

若 $k > n$，则可以收集完原有的所有的蘑菇（由于每次只长一个蘑菇，初始位置的蘑菇数量大于等于 $1$，所以收集原有的所有蘑菇至少不比不全收劣），对于如何求出新长出的蘑菇的最值的序列的问题，我的方法是逆向考虑。由于收集完原有的所有的蘑菇，所以每个节点至少到一次，令最后一次所到达的节点为 $n$，倒数第二个到达的点为 $n - 1$，以此类推……那么可以发现，$n$ 点最后生长的一个蘑菇没用能够采集，$n - 1$ 点有两个，一次类推……所以说，在 $k$ 秒后，共新长出了 $n \times k$ 个蘑菇，而节点 $n$ 至 $1$ 分别有 $1,2,\cdots,n$ 个蘑菇未采集，即总共采集到的新长出的蘑菇数量为 $n \times k - \sum_{i = 1}^{n} = n \times t - \frac{(n + 1) \times n}{2}$。

时间复杂度为 $O(n)$，可以通过本题。最后，**千千万万注意开$\texttt{long long}$**。代码如下：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#define init(x) memset (x,0,sizeof (x))
#define ll long long
#define ull unsigned long long
#define INF 0x3f3f3f3f
using namespace std;
const int MAX = 2e5 + 5;
const int MOD = 1e9 + 7;
inline int read ();
int t;
ll k,n,ans,a[MAX];
int main ()
{
	//freopen (".in","r",stdin);
	//freopen (".out","w",stdout);
	t = read ();
	while (t--)
	{
		ans = 0;
		n = read ();k = read (); 
		for (int i = 1;i <= n;++i) a[i] = read ();
		if (k <= n)
		{
			ll s = 0;
			for (int i = 1;i <= n;++i)
			{
				if (i <= k) s += a[i],ans = s;
				else ans = max (ans,s - a[i - k] + a[i]),s = s - a[i - k] + a[i];
			}
			ans += k * (k - 1) >> 1;
		}
		else
		{
			for (int i = 1;i <= n;++i) ans += a[i];
			ans += n * k;
			ans -= n * (n + 1) >> 1;
		}
		printf ("%lld\n",ans);
	}
	return 0;
}
inline int read ()
{
    int s = 0;int f = 1;
    char ch = getchar ();
    while ((ch < '0' || ch > '9') && ch != EOF)
	{
        if (ch == '-') f = -1;
        ch = getchar ();
    }
    while (ch >= '0' && ch <= '9')
	{
        s = s * 10 + ch - '0';
        ch = getchar ();
    }
    return s * f;
}
```

---

## 作者：12345678hzx (赞：6)

显然，如果 $k\le n$，我们要求的就是数组中长度为 $k$ 的子数组的最大价值。

如果 $k>n$，考虑贪心，我们可以采用前 $k-n+1$ 分钟都在一号点采蘑菇，剩下的时间遍历一遍，可以证明这样是最优的。

考虑证明，这样做一定可以把所有的初始蘑菇给吃掉，而增加的蘑菇这么做是可以吃掉大部分的蘑菇，所以总量是最优的。

对于求出区间价值，我们采用高斯等差数列求和公式即可。

---

## 作者：Tx_Lcy (赞：5)

这题好水，甚至比 $C$ 要水......
## 思路
首先看到这个题目，根据 CF 系列题目一贯的风格，肯定是个小贪心，我们继续仔细阅读题目，发现这个 $k$ 很大，$n$ 却较小，这表明我们要分两种情况讨论，一种是 $k≥n$，还有一种就是 $k<n$。

$\bullet \ \ k≥n$：我们**首先可以花费 $n$ 步把所有的蘑菇都取完**，然后的 $k-n$ 步我们开始**捡单位时间内长出来的蘑菇**。在 $k$ 的时间内每个格子我们可以捡到 $k$ 个长出来的蘑菇，但是由于我们需要从序列一段移动到另一端，我们无法捡拾的蘑菇总和就是 $n+(n-1)+...+1$，本来可以捡到的蘑菇总和是 $n \times k$，减一减我们发现可以捡到 $(k-1)+(k-2)+...+(k-n)$，**等差数列**求个和就是 $\frac{(k-1+k-n) \times n}{2}$，再加上最初的总蘑菇数量。

$\bullet \ \ k<n$：首先我们要明确，如果我们当前位置在 $x$，我们是从 $x-1$ 移动而来的。我们有**三个选择**，一种是捡**自己长出来的**，有一个，一种是拾取 **$x-1$ 长出来的**，有两个，一种是**拾取 $x+1$ 的**，总共有 $y+t$ 个，其中 $y$ 表示原有数量，$y≥1$，$t$ 表示已用步数，$t≥1$，所以 $y+t≥2$。**综上所述，我们选取的区间是一个连续的，且长度为 $k$ 的，所以只要前缀和一下就好了。**

关于为什么要经过尽可能多的蘑菇，因为加入你在位置 $a$，你是从位置 $a-1$ 过来的。第一种情况是你再回到 $a-1$，那么你得到的蘑菇数是 $1$，第二种情况是你往前走，你得到的蘑菇数一定 $≥1$，所以我们肯定选第二种。注意到第二种情况就是**不走回头路**，经过**尽可能多的蘑菇**。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long//要开 long long！
int const N=2e5+10; 
int s[N];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;cin>>t;
	while (t--){
		int n,k;cin>>n>>k;
		for (int i=1;i<=n;i++){
			int x;cin>>x;
			s[i]=s[i-1]+x;//求前缀和
		}
		if (k>n){cout<<((k-1+k-n)*n/2)+s[n]<<'\n';continue;}//分类讨论
	    int ans=0;
		for (int i=k;i<=n;i++)
		    ans=max(ans,s[i]-s[i-k]+((k-1)*k/2));
		cout<<ans<<'\n';
	} 
	return 0;
}
```


---

## 作者：Prophesy_One (赞：5)

#### 题意：

魔法森林可以被抽象成一条有着 $n$ 个节点，从 $1$ 到 $n$ 标号的数轴。在魔理沙出发之前，她的好友帕秋莉运用魔法去侦测了每个节点上的蘑菇数量，分别为 $a_1,a_2,\dots,a_n$。

在第 $0$ 分钟的时候，魔理沙可以从任意一个节点出发。在每一分钟的时候，她将会做以下事情：

$1.$ 她将从节点 $x$ 移动到节点 $y$。（$|x-y| \leq 1$，即 $y$ 可能等于 $x$。）

$2.$ 她将会收集节点 $y$ 上的所有蘑菇。

$3.$ 魔法森林中每个节点会再生长出一个蘑菇。

注意，她不能在第 $0$ 分钟的时候收集蘑菇。

现在魔理沙希望知道她在前 $k$ 分钟的时候，最多能收集到多少个蘑菇。

#### 分析：

挺好想的贪心题。

因为 $n$ 数据规模比 $k$ 小得多，故考虑分类讨论：

若 $k \leq n$，则选择序列内长度为 $k$ 的最大子段和，再加上 $k$ 分钟新生长的 $\sum_{i=1}^{k}i=\frac{k\times(k+1)}{2}$ 个蘑菇。

若 $k > n$，则先花 $k$ 分钟采摘完序列所有蘑菇，不断从序列一端走到另一端，考虑 $k$ 秒内，共生长 $nk$ 个蘑菇，而这样采点 $1$ 到 $n$ 分别剩有 $1,2,\dots,n$ 个蘑菇，则共摘 $nk-\sum_{i=1}^{n}i=nk-\frac{n\times(n+1)}{2}$ 个蘑菇。

```cpp

#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=2e5+5;
ll a[N],s[N];
ll read()
{
	ll res,f=1;
	char ch;
	while((ch=getchar())<'0'||ch>'9')
	if(ch=='-')
	f=-1;
	res=ch^48;
	while((ch=getchar())>='0'&&ch<='9')
	res=(res<<1)+(res<<3)+(ch^48);
	return res*f;
}
int main()
{
	ll T,n,k,i,ans;
	T=read();
	while(T--)
	{
		n=read();k=read();
		for(i=1;i<=n;i++)
		{
			a[i]=read();
			s[i]=s[i-1]+a[i];
		}
		if(n<k)
		{
			printf("%lld\n",s[n]+n*(k*2-n-1)/2);
			continue;
		}
		ans=0;
		for(i=k;i<=n;i++)
		ans=max(ans,s[i]-s[i-k]+(k-1)*k/2);
		printf("%lld\n",ans);
	}
	return 0;
}

```

---

## 作者：Cocoly1990 (赞：4)

官方题解。

We can solve the problem by deviding them into two cases:

1. $k<n$: We can easily found that we can't walk into a blocks more than one times,so just choose $k$ continuous blocks and eat them all,the final answer is the sum of these k blocks plus the additional mushrooms.We can calculated the additional mushrooms by using these equation $\frac{k\times\left(k - 1\right)}{2}$. the following picture shows the additional mushrooms clearly.
2. $k\geq n$: We can found that if we wanna make the number of additional mushrooms biggest,we have to pass by all the blocks in the last $n - 1$ seconds,so one way is to stay on the first blocks for $k - n + 1$ seconds and than goto the $n$ th blocks in $n-1$ seconds,by this way,we can eat all the mushrooms and make the number of additional mushrooms biggest.

别问，问就是这是第一版的蹩脚英文，ss 写的润色版本自己去 CF 上看。

翻译一下：

容易发现增量很本身的蘑菇可以分开考虑。

1. 当 $k<n$ 时，走重复的路必然是不优的（考虑反证），可以发现增量时固定的，为 $\frac{k\times\left(k - 1\right)}{2}$ ，因此找到连续的 $k$ 个格子使得其本身的值最大即可，用前缀和可以在 $\mathcal{O}\left(n\right)$ 内解决。

2. 当 $k\geq n$ 时。首先我们发现一个格子最后带来的增量贡献只和最后一次经过这个各自的时间有关，所以如果想让增量最大，必须在最后 $n$ 秒内把所有格子各走一次，可以构造形如 $1\rightarrow 1\rightarrow \cdots \rightarrow 2\rightarrow 3\rightarrow \cdots \rightarrow n$ 的走法，可以证明，这种走法一定能把每个格子初始的蘑菇都吃到，因此本量和增量都是最大的，那么总量也必然是最大的。



---

## 作者：legend_cn (赞：2)

# **解题思路：**
这道题考查的方法是贪心。

我们来分类讨论一下 $k$ 的范围：
+ 若 $k \le n $，也就是不能全部收集完原有的所有的蘑菇。
  - 首先我们的目标是让时间的和最大，所以不能收集之前收集过的蘑菇；
  - 其次，每次收集完新长的蘑菇，可以收集的数量是 $\sum_{i=1}^{k-1}i $，用求和公式表示就是 $\dfrac{k \times \left ( k - 1 \right ) }{2} $。
  - 这样问题就转换为求原有蘑菇序列的长度为 k的区间和的最大值，可以用单调队列的方法求最大值。

+ 若 $ k > n $，则可以收集完原有的所有的蘑菇。由于收集完原有的所有的蘑菇，所以每个节点至少需要到达一次。令倒数第一个到达的点为 $ n $，倒数第二个到达的点为 $n-1$，以此类推。那么可以发现，$ n $ 点最后生长有一个蘑菇没用能够采集，$n-1$ 点有两个蘑菇没用能够采集，以次类推。所以说，在 $k$ 秒后，共新长出了 $ n \times k $ 个蘑菇，还需要减去从节点 $1$ 至 $n$ 分别有 $ 1,2, \cdots ,n $ 个蘑菇未采集，即总共采集到的新长出的蘑菇数量为 $ n \times k - \sum_{i=1}^{n} i= n \times k - \frac{\left ( n+1 \right ) \times n}{2}  $。

最后提醒一句，此题必须开 long long。

# **AC 代码：**
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[200005];
signed main ()
{
	int T;
	cin>>T;
	while(T--)
	{
		int n,k;
		cin>>n>>k;
		int ans=0;
		for(int i=1;i<=n;i++)
			cin>>a[i];
		if(k<=n)
		{
			int sum=0;
			for(int i=1;i<=n;i++)
			{
				if(i<=k)
				{
					sum+=a[i];
					ans=sum;
				}
				else
				{
					ans=max(ans,sum-a[i-k]+a[i]);
					sum=sum-a[i-k]+a[i];
				}
			}
			ans+=k*(k-1)/2;
		}
		else
		{
			for(int i=1;i<=n;i++)
				ans+=a[i];
			ans+=n*k;
			ans-=n*(n+1)/2;
		}
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：Code_Select_You (赞：1)

## 思路
- 当 $k \le n$ 时，最优方案就是从某一点出发一直往右走。因为每个节点的蘑菇数都是大于等于 $1$ 的，如果往回走捡新长的蘑菇，不如捡后面原有的蘑菇加新长的蘑菇。所以枚举从哪个点出发，然后更新答案。

- 当 $k > n$ 时，最优方案就是一直在 $1$ 号点不动让蘑菇生长，等到只剩 $n$ 分钟的时候把每个节点的蘑菇都摘了。因为如果早走 $x$ 分钟（到头后往回走且 $x+n \le k$），新长的蘑菇为最优方案新长的蘑菇加上 $(\sum_{i=1}^{x}-\sum_{i=1}^{n}x)$，无论 $x$ 取多少，都不可能比最优方案更优。

## AC code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+1;
int T,a[N],n,k;
long long ans;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&k);
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		ans=0;
		if(k<=n){
			long long anss=0;
			for(int i=1;i<=k;i++) anss+=a[i]+i-1;
			ans=anss;
			for(int i=k+1;i<=n;i++) anss=anss-a[i-k]+a[i],ans=max(ans,anss);
			printf("%lld\n",ans);
		}
		else{
			int Q=k-n;
			for(int i=1;i<=n;i++) ans+=a[i]+Q+i-1;
			printf("%lld\n",ans);
		}
	}
	return 0;
}
```


---

## 作者：linyuhuai (赞：1)

[题目传送门](https://codeforces.com/problemset/problem/1687/A) & [前往 blog 获得更好的阅读体验](https://by505244.github.io/oi_blogs/2022/06/07/CF1687A题解)

将此问题拆分成 $2$ 小题来解答。

1. 求 $a$ 数组中长度为 $k$ 的和的最大值。（$k\ge n$ 时 不需考虑此问题）
2. 求在 $k$ 的时间里，找到一种方法，使得**所有位置被最后一次遍历到的时间之和最大**。

####  对于 $n< k$ 的情况

先考虑第二个小问。

如果一个地方被重复遍历，那么他就会浪费掉上次遍历完的时间，而我们的目标是使得时间之和最大，故一个地方重复遍历不可取。

故答案便是：

$$\max\limits_{1\le i\le n-k}(\sum\limits^{i+k}_{j=i}a_j)+\sum\limits_{i=0}^{k-1}i$$

#### 对于 $n\ge k$ 的情况：

由于 $n\ge k$，不需要再考虑第一小问，转而考虑第二小问。

为了满足时间之和最大，需要在最后 $n$ 秒内将所有数都遍历一遍。所以从**左到右或从右到左一定所遍历到的时间之和一定最大**。

由于可以原地走，不难证明在 $n\ge k$ 的情况下是可以构造的。

故答案便是：

$$(\sum\limits_{i=1}^{n}a_i)+\sum\limits_{i=k-n}^{k-1}i$$

前一段用前缀和处理，后一段可用高斯求和公式处理。

注意到题目数据范围较大，需要开 `long long` 处理。

~~最后感谢 cocoly 让我重写题解，sto cocoly orz~~

```cpp
#define int long long
ll a[200005];
void solve(){
    int n,k;
    scanf("%lld%lld",&n,&k);
    for(int i=1;i<=n;i++){
        scanf("%lld",&a[i]);
    }
    ll cnt=0,ans=0;
    for(int i=1;i<=n;i++)a[i]+=a[i-1];
    if(k<=n){
        for(int i=k;i<=n;i++){
            ans=max(ans,a[i]-a[i-k]);
        }
        printf("%lld\n",ans+(k*(k-1)/2));
        return;
    }
    if(n==1){
        printf("%lld\n",a[n]+k-1);
        return;
    }
    printf("%lld\n",((k-1)+(k-n))*(n)/2+ a[n]);
}

```

---

## 作者：dutianchen1 (赞：0)

# The Enchanted Forest

~~金发小女孩被红白压了一头（悲）。~~

### 题意翻译
魔理莎在一个长度为 $n$ 的数轴上执行 $k$ 次操作。操作按照一下顺序执行：

1. 魔理莎先移动至与当前位置相邻的另一个位置或原地不动。
2. 魔理莎获得她移动后她所在位置的价值。
3. 数轴上每个位置的价值值都加一。

问她在已知数轴上原本各位置的价值值下，能够获得的最大价值。

### 思路简析

由于魔理莎~~找不到扫把~~只能移动至相邻位置或不动，那么显然，我们想要获得权值的位置是数轴上**连续的一段**。于是我们考虑前缀和直接求

关于我们是否考虑回头，可以感性理解。由于原本各个位置的价值都不小于 $1$，那么我们取得原本价值一定比取得增长出来的价值更优。

那么，在 $k \le n$ 的情况下，显然，我们只需要利用前缀和算出区间最大价值加上增长的价值即可（不必考虑顺序，因为每个位置自然增长的价值都一样）。

考虑在 $k > n$，也就是在取完所有价值之后有多余时间的情况。取得原本价值不必再考虑，剩下的就是考虑如何能够获得最多增长的价值。

感性猜想一下：

首先，我们从两端开始，显然价值更大。

其次，我们呆在两端，等到其他位置自然增长的价值尽可能多之后再去采集能够获得的价值，比采集原价值后来回走取得增长价值更优秀（其实实际手模一下样例就能发现）。

贪心策略如上，代码见下：


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6+5;
const ll inf = 1e18+7; 
inline ll read()
{
	ll x=0,f=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
ll T,n,k;
ll maxx,ans;
ll num[N],sum[N];
int main()
{
	T=read();
	while(T--)
	{
		maxx=-inf;
		n=read();k=read();
		for(int i=1;i<=n;i++)
		{
			num[i]=read();
			sum[i]=sum[i-1]+num[i];//前缀和求区间最大和
			maxx=max(sum[i]-sum[max(0ll,i-k)],maxx);
		}
//		cout<<maxx<<'\n';
		if(k<n)
		{
			cout<<maxx+(k-1)*k/2<<'\n';
		}
		else
		{
			cout<<sum[n]+(2*k-n-1)*n/2<<'\n';
		}
	}
	return 0;
}
 
```

---

