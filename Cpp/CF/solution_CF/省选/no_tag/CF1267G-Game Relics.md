# Game Relics

## 题目描述

Esports is a form of competitive sports using video games. Dota 2 is one of the most popular competitive video games in Esports. Recently, a new video game Dota 3 was released. In Dota 3 a player can buy some relics for their hero. Relics are counters that track hero's actions and statistics in a game.

Gloria likes to play Dota 3, so she wants to buy all $ n $ available relics for her favorite hero.

Relics can be bought using an in-game currency called shards. Each relic has its own price — $ c_i $ shards for the $ i $ -th relic. A player can buy a relic using one of the following options:

- Pay $ c_i $ shards to buy the $ i $ -th relic;
- Pay $ x $ shards and randomly get one of all $ n $ relics. The probability of getting a relic is the same for all $ n $ relics. If a duplicate relic is received, then the relic is recycled and $ \frac{x}{2} $ shards are given back to the player.

Gloria wants to buy all $ n $ relics. Help her minimize the expected number of shards she spends to buy all the relics.

## 说明/提示

In the first example, the optimal strategy is to randomly get one of the two relics paying $ 20 $ shards. Then there are two scenarios.

The first one happens if Gloria receives the first relic. Then she keeps getting random relics until she obtains the second relic. The expected number of shards to spend in this scenario is $ 20 + 30 = 50 $ .

In the second scenario, Gloria initially gets the second relic. Then it is better to buy the first relic for $ 25 $ shards, so the expected number of shards to spend in this scenario is $ 20 + 25 = 45 $ .

Thus, the expected number of shards to spend is $ \frac{50 + 45}{2} = 47.5 $ .

## 样例 #1

### 输入

```
2 20
25 100
```

### 输出

```
47.50000000000000000
```

## 样例 #2

### 输入

```
4 30
60 50 60 80
```

### 输出

```
171.25000000000000000
```

# 题解

## 作者：Yizhixiaoyun (赞：25)

想了想还是写吧，毕竟是一道比较神的期望 $\text{dp}$。

------------

首先是一个简单的贪心思路：**能抽卡的先抽卡，然后再去买**。

原因显然，如果先买了卡，那么接下来抽卡就很有可能会抽到重复的卡，因此先抽卡再买卡。

如果我们已经有了 $i$ 张卡，易得抽一张新卡概率为 $\dfrac{n-i}{n}$，则需要抽 $\dfrac{n}{n-i}$ 次。

除了最后一次之外，其他的次数都可以让我们获得 $\dfrac{x}{2}$ 的回馈，最后一次消耗 $x$ 获得新卡，则期望消耗为：

$$(\frac{n}{n-i}-1) \times \frac{x}{2} + x$$

接着寻找抽卡与买的分界线。考虑**把所有直接购买的花费均摊到每次之中**。令已有的卡价值为 $w_{have}$，总价值为 $w$，则单次消耗为 $\dfrac{w-w_{have}}{n-i}$，转换策略判断条件为：

$$\frac{w-w_{have}}{n-i} < (\frac{n}{n-i}-1) \times \frac{x}{2} + x$$

接着假设 $a_{i,j}$ 为选择了 $i$ 张牌，已有价值为 $j$ 的事件，$dp_{i,j}$ 为其组合数量，则 $a_{i,j}$ 发生的概率是：

$$\frac{dp_{i,j}}{c_{n}^{i}}$$

其中组合数可以预处理，$dp_{i,j}$ 也可以通过背包预处理求出。

愉快结束。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=102;
const int maxm=10002; 
int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=x*10+c-48;
		c=getchar();
	}
	return x*f;
}
int n,x;
double sum,ans;
int a[maxn];
double C[maxn][maxn],dp[maxn][maxm];
inline void init(){
	n=read();x=read();
	for(register int i=1;i<=n;++i) a[i]=read();
	C[0][0]=1;dp[0][0]=1;
	for(register int i=1;i<=n;++i){
		C[i][0]=1;
		for(register int j=1;j<=i;++j) C[i][j]=C[i-1][j]+C[i-1][j-1];
	}
	for(register int i=1;i<=n;++i){
		for(register int j=i-1;j>=0;--j){
			for(register int k=sum;k>=0;--k) dp[j+1][k+a[i]]+=dp[j][k];
		}
		sum+=a[i];
	}
}
int main(){
	init();
	for(register int i=0;i<=n-1;++i){
		for(register int j=0;j<=sum;++j) ans+=min((sum-j)/(n-i),x*(1.0*n/(n-i)+1)/2)*dp[i][j]/C[n][i];
	}
	printf("%.8lf",ans);
}
```

---

## 作者：Soulist (赞：15)

很有意思的题。

给定 $n$ 张卡，第 $i$ 张的价格为 $c_i$

你有两种方式获得卡牌：

- 随机抽一张卡，花费为 $x$，如果得到了一个已经有的卡，那么返还 $\frac{x}{2}$
- 直接购买一张卡，花费为 $c_i$

求期望花多少集齐所有卡。

精度要求 $10^{-9}$

$n\le 100,\sum c_i\le 10^4$

----

### Solution



注意到决策一定是先抽卡，然后再全买。

那么我们可以改变决策的方式，变成选择一种方式获得卡：

- 按照规则随机抽卡。
- 随机抽一张没有的卡并获得，花费为这张卡的花费。

我们发现这种情况下的最优解和原问题等价。

同时，由于每次抽卡均为随机抽卡，所以假设我们抽了 $i$ 张不同的卡出来，那么这 $i$ 张卡也将是随机的卡，换而言之原集中每种大小为 $i$ 的子集被抽出的概率均相同！

现在考虑我们有 $i$ 张卡，期望花费多少得到 $i+1$ 张卡，不难发现期望花费为：$(\frac{n}{n-i}+1)\times \frac{x}{2}$，前面表示期望抽的次数，$+1$ 表示最后一次抽会额外附带 $\frac{x}{2}$ 的贡献。

修改规则后，我们发生如果剩余的权值和为 $c$，当前剩余 $k$ 个元素，那么问题等价于期望以 $\frac{c}{k}$ 的贡献得到一个元素，否则以 $(\frac{n}{k}+1)\times \frac{x}{2}$ 的贡献得到一个元素。

于是我们只需要比对这两者的大小，如果 $\frac{c}{k}$ 更大，那么以其期望产生贡献，否则以 $(\frac{n}{k}+1)\times \frac{x}{2}$ 产生贡献。

将每一种情况发生的概率乘以贡献求和即为答案。

注意到所有子集的等价性，保留 $k$ 个数使得权值和为 $c$ 的概率是可以算出来的，于是这个题就做完了，复杂度 $\mathcal O(n^2\sum c)$

- 其实就是为了保证精度，边算边除以 $\frac{1}{\binom{n}{k}}$，$\binom{n}{k}\leftarrow \binom{n}{k-1}\times \frac{n-k+1}{k}$

$Code:$

```cpp
#include<bits/stdc++.h>
using namespace std ;
#define rep( i, s, t ) for( register int i = (s); i <= (t); ++ i )
#define drep( i, s, t ) for( register int i = (t); i >= (s); -- i )
#define D long double
int gi() {
	char cc = getchar() ; int cn = 0, flus = 1 ;
	while( cc < '0' || cc > '9' ) {  if( cc == '-' ) flus = - flus ; cc = getchar() ; }
	while( cc >= '0' && cc <= '9' )  cn = cn * 10 + cc - '0', cc = getchar() ;
	return cn * flus ;
}
const int N = 100 + 5 ; 
int n, c[N], m ;
D ans, t, f[N][10005] ; 
D Min(D x, D y) { return min(x, y) ; }
signed main()
{
	n = gi(), t = gi(), t /= 2.0 ; 
	rep( i, 1, n ) c[i] = gi(), m += c[i] ; f[0][0] = 1 ; 
	rep( i, 1, n ) drep( k, 1, i ) rep( j, c[i], m ) 
	f[k][j] = (f[k][j] + f[k - 1][j - c[i]] * k / (1.0 * (n - k + 1)) ) ;
	rep( k, 1, n ) rep( j, 0, m ) 
		ans = (ans + f[k][j] * Min( ((D)n / (D)k + 1) * t, (D)j / ((D)k)) ) ; 
	printf("%.10Lf\n", ans ) ; 
	return 0 ;
}
```

---

## 作者：FjswYuzu (赞：9)

最近成功成为 Motivation 魔怔人……随便写点。

有一个可能太简单导致不好发现的结论，当前状态如果选择了随机抽，那么会随机抽直到抽到一个。

根据 WC2022 讲的 canonicalize（决策规范化），我们考虑将两个操作分开执行（可以用同样出处的 exchange argument 证明，交替执行的策略不会更优）。那么在先执行随机抽和先买中显然先随机抽更优秀（毕竟一开始抽中的概率会大一些，这是个直观的东西）。

然后是，我们要找到一个时间点，使得在之前我们选择随机抽，在之后直接买。定义 $f_i$ 为选择了 $i$ 个东西之后，再买一个随机的东西的期望花费。抽中没抽到的东西的概率是 $\dfrac{n-i}{n}$，那么期望抽 $\dfrac{n}{n-i}$ 次。那么 $f_i = \dfrac{x}{2}\left( \dfrac{n}{n-i} -1 \right) + x$。

注意到随机抽去买这个动作得到的东西我根本不知道，也无法操控。将随机抽归纳到直接买是不可行的。

Motivation: 将直接买这个操作，通过先随机抽再直接买这个性质，变成跟随机抽一个性质。

记没买的东西的总价值为 $c$，还有 $p$ 个没选。注意到在两个操作都是通过固定花费随机购买一个东西，那么每种购买顺序概率相同，当前如果直接买相当于期望花费 $\dfrac{c}{p}$ 买一个随机的还没有的东西。

那么在确定了 $c,p$ 的情况下，我们的最优决策固定，花费为 $\min\left(f_{n-p},\dfrac{c}{p}\right)$。

观察数据范围，猜测需要 $O(n^2 \sum c_i)$ 的算法。因此我们可以求出选了 $p$ 个东西总价格为 $c$ 的方案数。

因为每种购买顺序概率已经相同了，可以求出 $dp_{p,c}$ 表示选了 $p$ 个东西总价格为 $c$ 的概率，相当于方案数再除以 $\dbinom{n}{p}$。

那么最优的答案是 $\displaystyle \sum_{i=0}^{n-1} C(i)$，其中 $C(i)$ 表示在选择了 $i$ 个东西之后再选择一个东西的最优期望花费。

显然 $C(i)$ 也是个求和的形式。令 $s = \sum c_i$，枚举剩下的东西的总价格 $c$，那么 $\displaystyle C(i) = \sum dp_{i,c} \cdot \min\left(f_i,\dfrac{s-c}{n-i}\right)$。

```cpp
/*
他决定要“格”院子里的竹子。于是他搬了一条凳子坐在院子里，面对着竹子硬想了七天，结果因为头痛而宣告失败。
DONT NEVER AROUND . //
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef long double DB;
DB fac[105];
DB C(int n,int m){return (n<m || m<0)?0:fac[n]/fac[m]/fac[n-m];}
int n,x,a[10005],sum;
DB f[10005],dp[105][10005];
DB getMin(int c,int p){return min(DB(sum-c)/DB(n-p),f[p]);}
int main(){
	scanf("%d %d",&n,&x);
	for(int i=1;i<=n;++i)	scanf("%d",&a[i]),sum+=a[i];
	for(int i=0;i<n;++i)	f[i]=DB(x)/DB(2)*(DB(n)/DB(n-i)+1);
	fac[0]=1;
	for(int i=1;i<=n;++i)	fac[i]=fac[i-1]*DB(i);
	dp[0][0]=1;
	for(int i=1;i<=n;++i)	for(int j=i;j;--j)	for(int k=sum;k>=a[i];--k)	dp[j][k]+=dp[j-1][k-a[i]];
	for(int i=0;i<=n;++i)	for(int j=0;j<=sum;++j)	dp[i][j]/=C(n,i);
	DB ans=0;
	for(int i=0;i<n;++i)	for(int j=0;j<=sum;++j)	ans+=dp[i][j]*getMin(j,i);
	printf("%.10Lf",ans);
	return 0;
}
```

---

## 作者：Mr_Wu (赞：7)

1. 对于一次抽奖，如果没有抽中，一定会继续抽

如果没有抽到状态是不会变的，也就是说如果没抽到那么下一步执行的定是当前状态的最优策略，也就是说如果最优策略是抽奖那么没抽到一定继续抽。

2. 一次抽奖等效为用 $(\frac{n}{k}+1)\frac{x}{2}$ 的代价随机从没购买的商品中抽一个（$k$ 是没购买的商品个数）。注意随着 $k$ 递减（即购买的越多）此代价递增。
3. 在选择购买商品之后便不会进行抽奖操作

这是由 $c_i\ge x$ 保证的。如果不保证很容易有反例如 $x=1,c=[0,0,0,5]$，最优策略是购买三个价值为 $0$ 的商品后进行抽奖。

假设没买的商品是 $a_1\le a_2\le \cdots\le a_k$ 时，购买了 $a_i$，然后进行抽奖。现在考虑一个策略：先抽奖，如果没抽到 $a_i$ 那么下一步就购买 $a_i$，否则继续抽奖。我们可以对这两个策略的比对做出预测：两个策略的行为几乎一致，如果没抽到 $a_i$ 就会继续随机，这个随机与先随机再买 $a_i$ 是差不多的。由于现在随机比下一步随机代价少，因此某种程度上后者会更优。

令 $S=\{1,2,\cdots,k\}$，$f(S)$ 为没买的商品集合为 $S$ 时的答案，则前者的期望花费是
$$
a_i+(\frac{n}{k-1}+1)\frac{x}{2}+\sum_{j\not= i} \frac{f(S-\{i\}-\{j\})}{k-1}
$$
后者的期望花费是
$$
(\frac{n}{k}+1)\frac{x}{2}+\sum_{j\not= i} \frac{a_i+f(S-\{i\}-\{j\})}{k}+\frac{1}{k}((\frac{n}{k-1}+1)\frac{x}{2}+\sum_{j\not= i} \frac{f(S-\{i\}-\{j\})}{k-1})
$$
经过比对，后者的求和式的系数是 $\frac{1}{k}+\frac{1}{k}\frac{1}{k-1}=\frac{1}{k-1}$ 与上式抵消。因此我们要证明的是
$$
a_i+(\frac{n}{k-1}+1)\frac{x}{2}\ge (\frac{n}{k}+1)\frac{x}{2}+\frac{k-1}{k}a_i+\frac{1}{k}((\frac{n}{k-1}+1))\frac{x}{2}
$$
经过相同的比对，所有与 $x$ 有关的项化简成 $\frac{1}{k}\frac{x}{2}$，所以这个式子就化为 $a_i\ge \frac{x}{2}$ 了。在 $a_i\ge x$ 的前提下这显然是正确的。



所以我们的最优策略一定是先一直抽奖，到某个时刻忽然选择正常购买，然后以任意顺序把剩下的物品都买了。

根据 $\sum c_i\le 10000$ 我们容易想到正解复杂度与 $\sum c_i$ 有关，所以我们容易想到将 $S$ 变成某种只与 $S$ 内部 $c_i$ 的和有关的东西。可是此题可以花费 $c_i$ 在除 $S$ 内所有物品中购买，不好刻画。我们不妨做一个大胆的转化，将第一个操作 ”花费 $c_i$ 碎片购买第 $i$ 种圣物“ 变成 “随机选择一个没购买的商品，以 $c_i$ 的代价购买”！

由于我们的主动权降低了，因此新问题的最优答案一定大于等于原题的最优答案。但是如果我们得到了原题的一个策略，我们可以在新问题中一直仿照，在原问题决定从抽奖变成购买后在新问题中也从抽奖变成随机购买。所以**新问题的最优答案等于原问题的最优答案。**

由于两者都是从没购买的物品中随机，因此当我们在一个状态 $S$ 时我们只需比较 $(\frac{n}{k}+1)\frac{x}{2}$ 与 $\frac{\sum c_i}{k}$ 的大小即可确定是抽奖还是随机购买。怎么计算答案也比较简单，考虑期望线性性，由于每一步都是在没有的物品中随机，因此拥有的物品的概率分布与策略是没有任何关系的。对于一个 $S$ 它被经过的概率是 $1/\binom{n}{|S|}$，而它对答案的贡献只与 $\sum c_i$ 有关，因此对于相同的 $|S|,\sum c_i$ 可以一起计算答案。做一个 $O(n^2|S|)$ 的暴力背包即可将答案算出。由于此题是在 double 下做运算，所以 dp 数组需要带着 $\binom{n}{|S|}$ 的因子，具体来说可以写成 $f_{i,siz,sum}=f_{i-1,siz,sum}+f_{i-1,siz-1,sum-c_i}\frac{siz}{n-siz+1}$

---

## 作者：shao0320 (赞：6)

#### CF1267G Game Relics

好玩的期望$dp$题目。

考虑这个抽卡的过程，实际上是花费$\frac{x}{2}$的代价抽一些次，然后再用$x$的代价抽一次。

那么考虑抽卡的次数，如果我们现在手中有$i$张卡，单纯靠抽卡获得第$i+1$张卡的的期望花费是肾么呢，显然是$(\frac{n}{n-i}+1)\times\frac{x}{2}$。加一是因为最后一次不返还$\frac{x}{2}$的代价。

那么这就有一个比较好玩的性质，注意到随着手头有的牌数$i$逐渐增加，爆率是在逐渐下降的，也就是说我们要抽到一张新牌用的次数就增加了，期望也就增加了。

那么最优策略必然是我们先爆抽很多次，然后最后买掉剩下的卡。

那考虑直接$dp$，由于期望=概率$\times$值，而这道题中对于某个场面转移到下一个场面的值容易计算，因此考虑直接对于概率$dp$。

设$f(i,j)$表示抽/买了共$i$张卡，总价值为$j$的概率。

注意到这个$dp$类似于背包，可以直接$0/1$背包转移。

但我们发现这个概率并不好算，而方案数是很好算的，概率又等于方案数/情况数。

统计答案的时候是如果抽卡的期望低于买卡，那么就抽卡。否则就买卡，这个地方为了方便处理可以只算当前场面转移到下一步（也就多抽出一张卡来的）的期望花费，由于一定是先抽再买，那么算买的期望的时候可以算他的平均值。

（~~这就像我们打王者荣耀，新赛季先赢几把，要是发现赢不了了的时候赶紧去打匹配，因为胜率越来越低，策划极差~~）

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define N 10005
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
int n,sum,x,c[N];
double f[105][N],fac[N];
double C(int x,int y)
{
	return fac[x]/(fac[y]*fac[x-y]);
}
int main()
{
	n=read();x=read();
	fac[0]=1;
	for(int i=1;i<=n;i++)c[i]=read(),sum+=c[i],fac[i]=fac[i-1]*i*1.0;
	f[0][0]=1;
	for(int i=1;i<=n;i++)
	{
		for(int j=n;j>=1;j--)
		{
			for(int k=sum;k>=c[i];k--)
			{
				f[j][k]=f[j][k]+f[j-1][k-c[i]];
				//这里的F算的是方案数 
			}
		}
	}
	double ans=0;
	for(int i=0;i<=n-1;i++)
	{
		for(int j=0;j<=sum;j++)
		{
			//cout<<"!!!!!!!!"<<i<<" "<<j<<" "<<f[i][j]<<endl;
			//cout<<n<<" "<<i<<" "<<C(n,i)<<endl;;
			ans+=f[i][j]/C(n,i)*min((sum-j)*1.0/(n-i),(n*1.0/(n-i)+1)*x/2);
			//方案数/总次数=概率 
		}
	}
	printf("%.10lf\n",ans);
	return 0;
}
```



---

## 作者：HaneDaniko (赞：4)

太神了这题，膜拜出题人 orz。

### 思考一

首先是大家都提到的一点，先抽卡再买。这里来做个数学分析。

假设我们还剩 $k$ 种没有买，其实我们是有式子来算出它的花费期望的。WIKI 上提到，假设一个事件的概率为 $p$，则遇到它的期望为 $\frac{1}{p}$，因此，对于这个题，抽到一个新物品的概率显然为 $\frac{k}{n}$，那么期望次数就为 $\frac{n}{k}$，这里面除了最后一次之外，其余的次数的花费都为 $x-\frac{x}{2}=\frac{x}{2}$，而最后一次的花费恰好为 $x$，因此可以得出**有 $k$ 种没买的情况下，抽到新物品的期望花费公式：**

$$E(k)=\frac{x}{2}\times (\frac{n}{k}-1)+x$$

可以看出这个式子是关于 $k$ 单调递增的，也就是说，**越晚抽卡，花费的代价越大**，因此才有了上述的结论：先抽卡再买。

### 思考二

既然我们能直接算出期望了，那我们直接**比较一下抽卡和买哪个更赚**不就行了吗。现在抽卡的期望我们有了，还需要一个买东西的期望。其实，因为每个东西的价值都是固定的，所以这个期望实际上就是**平均数**，那么我们算出这个平均数，每次都和当前的抽卡期望比较，选个最小的执行不就行了，搞定！紫题也不过如此。

但是不对，有点小问题。因为每个物品的价值都是不一样的，我们抽到不同的物品，最后计算出来的平均数也不一样。难道要枚举一遍全部的可能情况，再算一个平均数的平均数？又或者还要分情况讨论？那不就变成搜了吗，晕。

### 思考三

不对，除了搜还能写 DP，但是就是不知道状态怎么设计。

想想看，我们现在需要的东西有什么。需要计算抽卡期望，那么我们需要的东西就是当前剩余的物品个数，还有一个是平均数，那我们直接用剩余价值除以剩余个数不就行了吗！开一个两个维度的 DP：剩余个数，剩余价值。发现它变成了一个**背包 DP**。

现在来想状态转移。其实到这一步就和常规背包 DP 差不多了。定义初始状态 $f_{n,sum}=sum$，即不抽卡的期望花费为总价值，然后从剩余容量由大到小开始枚举所有物品，然后尝试转移就行了。

### 思考四

本来以为都快过了，但是写一半卡住了。

具体是卡在状态转移的时候，突然发现这个转移根本就没法实现。因为我们每次转移可能的来源有两个：一个是购买，一个是抽卡。买还好说，但是抽卡不行，因为不是整数，而我们没办法访问一个小数下标。

那么怎么办呢，感觉又到了瓶颈了。

首先这个思路是绝对正确的，我们整理一下现在都有什么了。我们可以求出在某个状态下的最优代价，那么，假如我们再维护一个出现概率的话，就能根据期望的定义，直接用**概率乘代价**去算了。那么我们不妨把我们设计的 DP 数组改一下，不维护期望了，改成**维护当前状态的概率**，再求一下抽卡期望和平均值的最小值，二者一乘就是答案。又因为这个题的总方案数是一定的（可以用组合数求），那么我们不妨再转换一下思路，改成**求当前状态的总方案数**，和总方案数一比就是答案。

### 思考五

我们在思路整理的时候忽略了一些小细节，比如，**如果当前的最优策略是抽卡，则若没抽中，下次的最优策略还是抽卡，直到抽到一个新的**。简单证明一下，假如你抽卡没抽中，那么除了钱少了点，此外什么都没变，因此 $E(k)$ 和平均数完全不会有任何变化。知道了这点，我们才能用 $E(k)$ 这样一条路走到黑的模型来计算答案。

还有一点，打完提交的时候莫名其妙 RE 了，后来发现是阶乘乘炸了（$100!$ 确实还挺大的），然后把阶乘函数改成 Double 就过了，会丢精度，但是不影响答案。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define div *1.0/
int n,x;
int c[101];
double f[101][10001];
long double fac[101];
inline void prework(){
	fac[0]=1;
	for(int i=1;i<=100;++i){
		fac[i]=fac[i-1]*i;
	}
}
inline double E(int k){
	return (n div k -1)*(x div 2)+x;
}
inline double C(int x,int y){
	return fac[x] div (fac[y]*fac[x-y]);
}
int main(){
	int sum=0;
	cin>>n>>x;
	prework();
	for(int i=1;i<=n;++i){
		cin>>c[i];
		sum+=c[i];
	}
	f[n][sum]=1;
	for(int i=1;i<=n;++i){
		for(int j=0;j<=n-1;++j){
			for(int k=0;k<=sum-c[i];++k){
				f[j][k]+=f[j+1][k+c[i]];
			}
		}
	}
	long double ans=0;
	for(int i=1;i<=n;++i){
		for(int j=0;j<=sum;++j){
			ans+=(f[i][j] div C(n,n-i)) * min(j div i,E(i));
		}
	}
	printf("%.20Lf",ans);
}
```

---

## 作者：Purslane (赞：3)

# Solution

我一上来就猜到了结论，但是没看到题目限制证不出来就倒闭了。这道 `*3000` 的题真的没黑吗？ /dk

首先，如果已经有了 $k$ 张卡，再选择**抽卡**，那么就**一定会一直用到抽到一张新的卡**。则相当于用了 $\dfrac{x}{2}(\dfrac{n}{n-k}+1)$ 的代价买了一张新的卡，随机。

显然如果选择买卡，一定会买代价最低的卡——这样可以让之后的抽卡显得更加划算。

如果有相邻的两次操作，**先买了一张卡 $i$**，**然后选择进行一次抽卡（假设抽到了 $j$）**。假设这两次操作前一共有了 $k$ 张卡。

我们不妨交换一次操作，先抽卡，再买卡。如果先抽卡，代价是 $c_1 = \dfrac{x}{2}(\dfrac{n}{n-k}+1)$，$c_2 = \dfrac{x}{2} (\dfrac{n}{n-k-1}+1)$。

如果第一次抽到的不是 $i$，那么我们显然可以第二次再买 $i$——这样总花费减少了 $c_2-c_1$；

如果第一次抽到的是 $i$：

- 如果 $c_1 \le a_i$，那么这样做稳赚不赔；
- 否则，我们多花了 $c_1-a_i$。

考虑后者，我们期望节省了 $\dfrac{n-k-1}{n-k}(c_2-c_1) - \dfrac{1}{n-k}(c_1-a_i)$，我们惊奇的发现，当 $a_i \ge x$ 的时候，它 $\ge 0$！！！

因此，我们的决策就大大简化：不断抽卡，等到当前卡牌集合满足某一特征的时候停止抽卡直接购买。

非常喜欢 Mr_Wu 的做法：由于购买只发生在最后，我们认为**购买也是随机的，而不是受人控制**。这样对答案没有影响。

假设我们已经付了 $\sum a_i$ 的钱，那么我们有两种操作：

1. 随机选取一个数，将其删掉。
2. 随机选取一个数，花 $\dfrac{x}{2} \times (\dfrac{n}{n-k}+1)-a_c$ 的代价。

我们可以计算出后者代价的期望值，假设为 $E_c$。

这一步我们花的代价为 $\min\{0,E_c\}$。但是有人（就是我）会产生一个问题——你怎么证明你这么做没有后效性？？

这是容易回答的——这个过程是独立的。也就是说，无论我们选哪个决策，下一步还有哪些遗物没收集都是独立的。因此我们选好每一步就行了，局部最优就是整体最优。

这样我们就知道之前“随机化”那一步的妙处——消除了问题的后效性，每一步独立，可以算贡献。

剩下的就好办了——发现 $E_c$ 之和已经选出的集合的权值和有关，而已经保证了 $\sum a$ 比较小，可以直接做背包。要用一些手段规避精度误差。

```cpp
#include<bits/stdc++.h>
#define ld long double 
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=100+10,MAXM=10000+10;
int n,c[MAXN],m;
ld x,dp[2][MAXM][MAXN];
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>x;
	ffor(i,1,n) cin>>c[i],m+=c[i];
	dp[0][0][0]=1;
	ffor(i,1,n) {
		int st=i&1,lst=st^1;
		ffor(j,0,n) ffor(t,0,m) dp[st][t][j]=0;
		ffor(j,0,n-1) ffor(t,0,m-c[i]) dp[st][t][j]+=dp[lst][t][j],dp[st][t+c[i]][j+1]+=dp[lst][t][j]/(n-j)*(j+1);	
	}
	ld ans=m;
	ffor(i,0,n-1) ffor(t,0,m) {
		ld cost=min((ld)0.0,x/2.0*(1.0*n/(n-i)+1)-1.0*(m-t)/(n-i));
		ans+=cost*dp[n&1][t][i];
	}
	cout<<fixed<<setprecision(10)<<ans;
	return 0;
}
```

---

## 作者：出言不逊王子 (赞：3)

题目中给出了两个操作，一个是**一定能得到**，一个是**不一定能得到**，且**没有的越多，则得到的概率越大**。

所以最优策略就出来了：**先抽卡，最后统一买卡**。

原因很显然：买卡随时都能买，先买卡意味着手动把没有的数量给减下去了，得不偿失。

既然最后是统一买了，那么顺序就无所谓了。

所以我们就钦定操作一是在**剩余**的物品里面随便买一个，并且有相应的花费。

为什么要这样呢？因为这样的话，捞到每个东西都是随机的了。

这样有一个好处，就是选到一个物品集合 $S$ 的概率一定是 $\dfrac 1{C_n^{|S|}}$。

然后我们就没思路了。

观察到统一买卡的集合，我们可以先算出最后购买物品的集合有几种。

但是这就涉及顺序了怎么办？

因为总代价不变，所以我们可以增加一个总代价的限制。

那么我们记 $f_{i,j}$ 为最后买了 $i$ 个物品，总代价是 $j$ 的方案数。

因为只能通过购买得来，所以我们记 $f_{i,j}=\sum f_{i-1,j-c_k}$，其中 $k$ 是每一个物品。

具体转移时，从上往下开始加入，反正和最终顺序无关。

那么有了这个，我们怎么得到接下来该干啥呢？

根据期望的线性性，我们可以把每个点搞到的期望加起来，就是最终的答案。

考虑对于一个状态 $f_{i,j}$，我们现在要再抽出一个物品。

在转换了条件的情况下，这个决策是纯随机的。

- 如果我们选择用方案一，那么期望就是 $\dfrac{s-j}{n-i}$，其中 $s$ 是 $\sum c_i$。

- 如果我们选用方案二，假设期望是 $e$，那么这由两部分构成：成了还是寄了
1. 如果成了，那么代价是 $x$，概率是 $\frac{n-i}n$，期望就是 $\frac{n-i}n\times x$。
2. 如果寄了，那么概率是 $\frac in$，代价是 $e+\frac x2$，期望就是 $\frac in \times (e+\frac x2)$。

解这个方程可以得到 $e=\frac {2n-i}{2n-2i}\times x$。

那么这俩的最小值就是这个物品的代价。这个局面出现的概率就是 $\dfrac{f_{i,j}}{C_n^i}$。

然后问题出来了：那我们哪知道这会搞到哪去呢？

你不需要知道啊，你需要知道的只是：这是操作序列上第 $i+1$ 个可能的物品的一种情况下的期望。

把每个“第 $i+1$ 个可能的物品的一种情况下的期望”加起来，就是最终的答案。

因为我们算的是每个“第 $i+1$ 个可能物品的期望”，所以 $i$ 从 $0$ 开始枚举。

注意代码实现细节：

- 求 $f$ 数组时要倒序求，因为这东西的本质是个背包。
- 在计算贡献时要多乘上几个 $1.0$，否则可能会有精度问题。

代码：

```cpp
#include<bits/stdc++.h>
#define fs(i,x,y,z) for(int i=x;i<=y;i+=z)
#define ft(i,x,y,z) for(int i=x;i>=y;i+=z)
#define ll long long
#define ull unsigned long long
#define db double
#define ms(a,b) memset(a,b,sizeof(a))
#define sz(a) sizeof(a)
using namespace std;
const int rw[]={-1,0,1,0,-1,1,-1,1},cl[]={0,1,0,-1,-1,1,1,-1};
const int N=10001,inf=0x3f3f3f3f;
inline int read(){
	int date=0,w=1;char c=0;
	while(c<'0'||c>'9'){if(c=='-')w=-1;c=getchar();}
	while(c>='0'&&c<='9'){date=date*10+c-'0';c=getchar();}
	return date*w;
}
int ksm(int a,int b){
	int ans=1;while(b){if(b&1)ans=ans*a%inf;a=a*a%inf;b=b>>1;}
	return ans;
}
int v[N],n,x,sig;
db res,fac[N+1],f[101][N];
db c(int d,int u){return fac[d]/(fac[u]*fac[d-u]);}
int main(){
	fac[0]=1.0;
	fs(i,1,N,1) fac[i]=fac[i-1]*i*1.0;
	n=read(),x=read();
	fs(i,1,n,1) v[i]=read(),sig+=v[i]; 
	f[0][0]=1.0;//初始是0
	fs(i,1,n,1){//现在放入哪个物品 
		ft(j,n,1,-1){//目前一共放了几个物品 
			ft(k,sig,v[i],-1){//当前物品花了几个钱 
				f[j][k]=f[j][k]+f[j-1][k-v[i]]; 
			}
		}
	}
	fs(i,0,n-1,1){//当前合法的有几个 
		fs(j,0,sig,1){
			db gl=f[i][j]*1.0/c(n,i);
			db buy=(sig-j)*1.0/(n-i),chouka=(((2*n-i)*1.0/((n-i)*1.0))*x/2.0);
			//如果不是全部这样的决策的话，那有其他状态替我们考虑到了 
			res+=min(buy,chouka)*gl;//有多少概率走到这一步，如果有的话，氪多少 
		}
	}
	cout<<fixed<<setprecision(8)<<res; 
	return 0;
}
//最优策略：先抽卡再统一购买，则你的任务就是抽好以后然后丢上去，抽到一个集合的概率就是1/C(n,|S|) 
//fij表示凹了i个物品，物品花了j个钱的所有可能的方案数 
//那么总概率就是fij/C(n,i)
//那么考虑要氪多少金 
//最多就是sig 
//他这个的意思是“抽到第i+1”个的期望 
//具体是哪个呢，我们也不知道，但是一定有一个 
//那么管他是哪一个呢，最后是一定的
//因为AABBCBBDBDBCBD和AABBBBBBBCCDDD是一样的 
```

---

## 作者：FutaRimeWoawaSete (赞：2)

讲的时候连题目都没看完就被寄掉了（               

考虑到一个比较 NB 的性质：一定是先搞二操作再搞一操作。           

一个不是完全严谨的证明：假设现在已经有 $s$ 张牌被你抽了，那么我们知道想要获得第 $(s + 1)$ 张牌的期望是 $(\frac{n}{n - s} + 1) \times \frac{x}{2}$，我们不难发现随着 $s$ 的增大那么该期望值一定会变大。      

也就是说存在一个临界点，使得之前获得所有卡牌的方式都是回旋心跳水立方抽卡，之后的所有方式都是直接买。               

那么你可以用一个很 trick ~~但是我没见过~~的套路将原题这么转化：     

有两种得卡方式，分别为：             

- 直接开抽；

- 在心中随机一张牌然后买它，并且购买任意一张牌的值会剩下的所有卡牌的价值和除上剩下卡牌的数量；

求使用以上两种方法可以获得的期望最小值。    

我们发现总的牌数很小，总的卡牌价值和很小，那么不妨定义状态 $dp_{i,j}$ 表示此时抽到 $i$ 张牌并且用了 $j$ 花费的概率。

由于现在两种操作都是概率操作，所以 $dp_{i,j}$ 可以用总方案数除上所有情况得出。

我们如果设计期望 DP 的话难度太大，所以我们不妨累加所有的 $dp_{i,j}$ 向下一个状态转移时的最小期望值以获得全局最小期望值。（这里的状态转移不是指概率 DP 的转移，可以理解成假设你有一个期望 DP 时你要从这步状态转移到下步状态时的状态转移，可以感性理解下）

之所以要转化题意是为了判断临界点。把这个转化的题意模拟一下就会发现，临界点的判断只需要在两种方法中取 $\min$ 以达到间接判断的作用（一旦选择操作 $2$ 后面也会一直选择操作 $2$，期望值形同虚设只是为了辅助正确的判断），而如果按照原题的方式直接 DP 就无法判断临界点，导致爆炸。                 

然后基本上就做完了，如果还对于 DP 转移式或如何求 $dp_{i,j}$ 比较迷惑的同学可以参考代码或者直接看一下旁边的题解，因为这一部分比较简单所以不再赘述。              

个人认为难度在于第一步转化题意（~~虽然很多人都觉得很 trick~~）以及累加转移的最小期望值以获得全局期望最小值的计算方法，别的都还是很良心的！

```cpp
#include "bits/stdc++.h"
using namespace std;
const int N = 105 , M = 10005;
int n,m,a[N],sum;
double f[N][M],fac[M],x,ans;
double C(int nn,int mm){return fac[nn] /(fac[mm] * fac[nn - mm]);}
int main()
{
	scanf("%d %lf",&n,&x);x = x / 2;fac[0] = 1;
	for(int i = 1 ; i <= n ; i ++) 
	{
		scanf("%d",&a[i]);
		sum += a[i];
		fac[i] = 1.0 * fac[i - 1] * i;
	}
	f[0][0] = 1;
	for(int i = 1 ; i <= n ; i ++)
		for(int j = n ; j >= 1 ; j --) 
			for(int k = sum ; k >= a[i] ; k --) f[j][k] += f[j - 1][k - a[i]];
	for(int i = 0 ; i < n ; i ++)
		for(int j = 0 ; j <= sum ; j ++) ans += 1.0 * f[i][j] / C(n , i) * min(1.0 * (sum - j) / (n - i) , (1.0 * n / (n - i) + 1.0) * x);
	printf("%.10lf\n",ans);
	return 0;
}
```

---

## 作者：lupengheyyds (赞：1)

这是一个根据随机状态动态调整决策的问题，应该先 **canonicalize（决策规范化）**，考虑一个决策的过程是怎样的。

分析发现，最优决策一定是先抽再买。

因为“买”操作的花费仅与剩余价格和有关（一旦开始买，就不再抽，费用就是剩下的物品价格和），“抽”操作的花费仅与获得物品数量有关，那么就关注这两个状态。

假设还剩 $a$ 个物品没拥有，剩余总价格和为 $w$，考虑应该“抽”还是“买”。

- 如果“买”，花费就是 $w$。

- 如果"抽"，由于随机，期望花费 $(\frac{n}a-1)\frac x2+x$，抽到一个新的物品，但是具体获得那个未知。如果暴力枚举每一种可能+用 dp 转移会 TLE。

于是要使用**费用均摊**，既然一开始"买"后就不再“抽”了，费用就是确定的，那我可以均摊到每次进行计算，取平均数 $\frac wa$ 与 $(\frac{n}a-1)\frac x2+x$ 的较小值，相当于抽到什么就买什么。于是就可以计算了。

但还有一个问题——由于“抽”是不确定的，所转移到的状态就是不确定的，没法直接使用 dp 转移计算。

于是可以利用期望的线性，设 $f(i)$ 表示选了 $i$ 个物品后再选一个物品的最小期望花费。

那么答案就是 $\sum f(i)$。

考虑求 $f(i)$，假设还剩 $w$ 的总价格，那最小费用就是 $\min\{\frac w{n-a},(\frac{n}{n-a}-1)\frac x2+x\}$，由于我们“抽到什么就买什么”，这样不论“抽“还是“买”，都是随机的，那么直接乘上随机选 $i$ 个物品价值和为 $j$ 的概率 $p_{i,j}$。这可以用背包轻松求解。

复杂度 $\mathcal O(n\sum w)$。

---

## 作者：do_it_tomorrow (赞：1)

[更好的阅读体验](https://www.doittomorrow.xyz/post/cf1267g-game-relics/)

容易发现对于这样抽卡或者转转盘的题目，都是先使劲随机达到一个临界值在进行定点操作。

对于这个题目，显然应该**先抽卡再去买卡**，因为如果抽到了已经买过的卡就会直接损失 $\dfrac{x}{2}$ 的碎片。

设 $E_i$ 表示抽了 $i$ 张不同的卡的期望操作次数，考虑分情况讨论随机抽一张新卡的操作次数：

- 抽到了已有的卡，概率为 $\dfrac{i}{n}$，还需要继续抽。
- 抽到了新的卡，概率为 $\dfrac{n-i}{n}$，操作就结束了。

那么显然有：

$$E_i=\dfrac{i}{n}\times (E_i+\dfrac{x}{2})+\dfrac{n-i}{n}\times (E_{i-1}+x)$$
化简之后有：

$$E_{i}-E_{i-1}=(\dfrac{n}{n-i}+1)\times\dfrac{x}{2}$$
所以我们就得到了已有 $i$ 张后抽出一张的卡的操作的代价为 $(\dfrac{n}{n-i}+1)\times\dfrac{x}{2}$。

如果要新买一张卡，那么肯定后面所有的卡都要全部买，那么假设后面还有价值为 $sum$ 的卡没有买，那么新获得一张卡的期望就是 $\dfrac{sum}{n-i}$。

因为 $\sum\limits_{i=1}^n c_i\le 10^4$ 所以，考虑直接设 $f_{i,j}$ 表示抽出了 $i$ 张卡已有的价值为 $j$ 时候的方案数。

那么显然有转移方程：

$$f_{j+1,k+a_i}\gets f_{j+1,k+a_i}+f_{j,k}$$
这样转移是为了避免重复的选择一个碎片。

显然，出现一个情况 $(i,j)$ 的概率为 $\dfrac{f_{i,j}}{i\choose n}$。

根据期望等于概率乘以权值，答案显然为：

$$\sum\limits_{i=0}^{n-1}\sum\limits_{j=0}^{s}\min(\dfrac{s-j}{n-i},(\dfrac{n}{n-i}+1)\times\dfrac{x}{2})\times \dfrac{f_{i,j}}{i\choose n}$$

[Submission #286064731 - Codeforces](https://codeforces.com/problemset/submission/1267/286064731)

---

## 作者：Needna (赞：0)

题解用了 [Yizhixiaoyun](https://www.luogu.com.cn/user/590864) 的式子和 [wangzihan_](https://www.luogu.com.cn/user/196975) 的部分证明，感谢两位神犇！


## 题意：

有 $n$ 种圣物，每个的价值为 $c_{i}$，现在有两种操作，一种是直接买，还有一种是抽卡，花费 $x$ 代价随机抽出一张，如果是已经有的，那么就返还 $\dfrac{x}{2} $ 代价，否者抽出新的，问最优策略下的获得所有圣物期望代价。

## 题解：

先确定最优策略是什么，思考一下很明显是先抽后买，感性理解就是越到后面越难抽出新东西出来，但也让我们来理性证明一下。

证明：首先购买一定是买当前价值最小的圣物。考虑相邻两次操作，如果先购买再抽奖，注意到本题的随机规则和决策是无关的，那么我们可以当成，在游戏开始之前，每次抽的结果就已经确定了，那么分情况讨论：


1. 如果下一次抽奖抽到的就是，最小值，则如果先买再抽，我们就白买了。

2. 如果下一次抽奖抽到的不是，最小值，则交换两次操作不影响结果。

那发现就是有关价值的决策，考虑决策代价：

因为 $Q=\sum w_{i}\times p_{i}$  所以分开计算。


设 $f_{i,j}$ 为抽了 $i$ 次，抽出的代价为 $j$ 的次数，那么 $f$ 数组明显可以用背包来做，可以求出次数，那么除以总可能那么概率就是 $\dfrac{f_{i,j}}{C_{n}^{i}}$ 了。

因为有抽和买两种代价，思考获得下一个圣物的期望代价。如果我们已经有了 $i$ 张卡，易得抽一张新卡概率为 $\dfrac{n-i}{n}$，则需要抽 $\dfrac{n}{n-i}$ 次。

除了最后一次之外，其他的次数都可以让我们获得 $\dfrac{x}{2}$ 的回馈，最后一次消耗 $x$ 获得新卡，则期望消耗为：

$$(\frac{n}{n-i}+1) \times \frac{x}{2}$$

接着寻找抽卡与买的分界线。考虑**把所有直接购买的花费均摊到每次之中**。令已有的卡价值为 $w_{have}$，总价值为 $sum$，则单次消耗为 $\dfrac{sum-w_{have}}{n-i}$，转换策略判断条件为：

$$\frac{sum-w_{have}}{n-i} < (\frac{n}{n-i}+1) \times \frac{x}{2}$$


代码里直接概率乘上两个的最小值即可，所有可能性加起来自动就是答案，很巧妙。

ac code：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e2+10,M=1e4+10;
int n,x,a[N];
double c[N][N],f[N][M],ans;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>x;
	for(int i=1;i<=n;i++) cin>>a[i];
	c[0][0]=f[0][0]=1;
	for(int i=1;i<=n;i++){c[i][0]=1;
		for(int j=1;j<=n;j++){
			c[i][j]=c[i-1][j-1]+c[i-1][j];
		}
	}int sum=0;
	for(int i=1;i<=n;i++){
		for(int j=i-1;j>=0;j--){
			for(int k=sum;k>=0;k--){
				f[j+1][k+a[i]]+=f[j][k];
			}
		}
		sum+=a[i];
	}
	for(int i=0;i<=n-1;i++){
		for(int j=0;j<=sum;j++){
			ans+=min(1.0*(sum-j)/(n-i),x*(1.0*n/(n-i)+1)/2)*f[i][j]/c[n][i]; 
		}
	}
	cout<<fixed<<setprecision(8)<<ans;
	return 0;
}

```

---

