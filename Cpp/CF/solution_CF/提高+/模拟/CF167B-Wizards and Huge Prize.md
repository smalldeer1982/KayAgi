# Wizards and Huge Prize

## 题目描述

One must train much to do well on wizardry contests. So, there are numerous wizardry schools and magic fees.

One of such magic schools consists of $ n $ tours. A winner of each tour gets a huge prize. The school is organised quite far away, so one will have to take all the prizes home in one go. And the bags that you've brought with you have space for no more than $ k $ huge prizes.

Besides the fact that you want to take all the prizes home, you also want to perform well. You will consider your performance good if you win at least $ l $ tours.

In fact, years of organizing contests proved to the organizers that transporting huge prizes is an issue for the participants. Alas, no one has ever invented a spell that would shrink the prizes... So, here's the solution: for some tours the winner gets a bag instead of a huge prize. Each bag is characterized by number $ a_{i} $ — the number of huge prizes that will fit into it.

You already know the subject of all tours, so you can estimate the probability $ p_{i} $ of winning the $ i $ -th tour. You cannot skip the tour under any circumstances.

Find the probability that you will perform well on the contest and will be able to take all won prizes home (that is, that you will be able to fit all the huge prizes that you won into the bags that you either won or brought from home).

## 说明/提示

In the first sample we need either win no tour or win the third one. If we win nothing we wouldn't perform well. So, we must to win the third tour. Other conditions will be satisfied in this case. Probability of wining the third tour is 0.3.

In the second sample we win the only tour with probability 1.0, and go back home with bag for it.

## 样例 #1

### 输入

```
3 1 0
10 20 30
-1 -1 2
```

### 输出

```
0.300000000000
```

## 样例 #2

### 输入

```
1 1 1
100
123
```

### 输出

```
1.000000000000
```

# 题解

## 作者：Inui_Sana (赞：6)

[题目传送门](https://www.luogu.com.cn/problem/CF167B)

## 解题思路：dp

很经典且标准的一道概率 `dp`。

看到题目里说什么的容量，联想到背包，所以可以定义一个状态：$dp_{i,j,k}$ 表示前 $i$ 场比赛赢了 $j$ 局，当前背包容量为 $k$ 的概率。列出状态转移方程：$dp_{i,j,k}=dp_{i-1,j-1,k-a_i}\times p_i\times 0.01+dp_{i-1,j,k}\times(1-p_i)\times 0.01$。

但这么做会时时间复杂度来到 $1.6\times 10^9$ 的级别。考虑如何优化。

可以发现，比赛再多，获得的物品总体积都不会超过 $n$。所以将 $k\ge n$ 的状态归入 $k=n$ 的状态。这样我们就得到了一个时空复杂度 $O(n^3)$ 的做法。

但是现在再用上面那条状转方程就会比较麻烦，于是改成 $dp_{i,j+1,\min(k+a_i,n)}+=dp_{i-1,j,k}\times p_i\times 0.01,dp_{i,j,k}+=dp_{i-1,j,k}\times p_i\times 0.01$。

初始值为 $dp_{0,0,min(n,k)}=1$。最后答案即为 $\sum\limits_{i=l}^n\sum\limits_{j=0}^n dp_{n,i,j}$。

最后还可以用滚动数组将空间复杂度优化到 $O(n^2)$。

code：

```cpp
int n,m,k;
double dp[2][N][N];
struct node{
	int p,val;
	bool operator<(const node &tmp)const{return val>tmp.val;}
}e[N];
void solve(){
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++)scanf("%d",&e[i].p);
	for(int i=1;i<=n;i++)scanf("%d",&e[i].val);
	std::sort(e+1,e+n+1);
	int cur=0;
	dp[0][0][min(n,k)]=1;
	for(int i=1;i<=n;i++){
		cur^=1;
		for(int j=0;j<=i;j++){
			for(int p=0;p<=n;p++)dp[cur][j][p]=0;//别忘了每次循环要初始化（因为用的是+=）
		}
		for(int j=0;j<i;j++){
			for(int p=0;p<=n;p++){
				if(~e[i].val)dp[cur][j+1][min(p+e[i].val,n)]+=dp[cur^1][j][p]*e[i].p*0.01;
				else if(p)dp[cur][j+1][p-1]+=dp[cur^1][j][p]*e[i].p*0.01;
				dp[cur][j][p]+=dp[cur^1][j][p]*(100.0-e[i].p)*0.01;
			}
		}
	}
	double ans=0;
	for(int i=m;i<=n;i++){
		for(int j=0;j<=n;j++)ans+=dp[cur][i][j];
	}
	printf("%.6lf\n",ans);
}
signed main(){
	int t=1;
//	scanf("%d",&t);
	while(t--)solve();
}
```

---

## 作者：_FL_ (赞：4)

## $ \texttt{CF167B} $  

---

### 题意：  

$ n $ 个事件，每个事件有成功和失败两种结果，其概率分别为 $ p_i*0.01 $ 和 $ (1-p_i*0.01) $，若成功则会获得 $ a_i $ 的分数  

初始分数为 $ k $，问任意时刻分数均非负且总成功次数不小于 $ l $ 的概率  

---

### 思路：  

题目有要求成功 $ l $ 次且分数非负，可以考虑对应地设置 $ dp $ 数组，$ dp[i][j][k] $ 表示前 $ i $ 个事件，成功了 $ j $ 次，且获得的分数为 $ k $ 的概率  

接着是转移，首先当下一事件失败了一定是可行的（因为分数不会减少），所以有：  

$ dp[i+1][j][k]+=dp[i][j][k]*(1-p_{i+1}*0.01) $  

当然，若当前分数加上 $ a_{i+1} $ 仍然非负时，下一事件可以成功，即有：  

$ dp[i+1][j+1][min(k+a_i,n)]+=dp[i][j][k]*(p_{i+1}*0.01) $  

这里之所以要和 $ n $ 取 $ min $，是因为 $ a_i\ge -1 $，所以既然有 $ n $ 的分数，你怎么减都减不到负数了  

转移完毕后将符合要求的情况概率相加即可，即：  

$ ans=\sum\limits_{i=l}^n\sum\limits_{j=0}^n dp[n][i][j] $  

---

### 代码：  

```cpp
#include<bits/stdc++.h>
#define Hu_Tao namespace std
using Hu_Tao;
const int N = 201;
struct HT {
	int Val;
	double Pi;
} s1[N];
int n, l, k;
double dp[N][N][N], ans;
bool cmp1(HT x, HT y);
int main() {
	scanf("%d%d%d", &n, &l, &k);
	for (int i = 1; i <= n; i++) {
		scanf("%lf", &s1[i].Pi);
		s1[i].Pi *= 0.01;//转换为真实概率
	}
	for (int i = 1; i <= n; i++) {
		scanf("%d", &s1[i].Val);
	}
	sort(s1 + 1, s1 + n + 1, cmp1);//先走大的肯定最优
	dp[0][0][min(n, k)] = 1.0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= i; j++) {
			for (int g = 0; g <= n; g++) {
				dp[i + 1][j][g] += dp[i][j][g] * (1 - s1[i + 1].Pi);
				if (g + s1[i + 1].Val >= 0) {
					dp[i + 1][j + 1][min(g + s1[i + 1].Val, n)] += dp[i][j][g] * s1[i + 1].Pi;
				}
				//转移
			}
		}
	}
	for (int i = l; i <= n; i++) {
		for (int j = 0; j <= n; j++) {
			ans += dp[n][i][j];//统计答案
		}
	}
	printf("%0.10lf", ans);
	return 0;
}
bool cmp1(HT x, HT y) {
	return x.Val > y.Val;
}
```


---

## 作者：Acc_Robin (赞：4)

说实话，不是很明白其他题解为什么要`sort`一遍，于是我就写了一个不需要`sort`的题解。

我们可以假设，$a[i]=-1$ 就是一个容积为$-1$的物品。

显然DP，令 $dp[i][j][k]$ 表示前 $i$ 局，赢了 $j$ 局，且背包容积为 $k$ 时的概率。

显然有 DP 转移状态（刷表法）：

$$
dp[i+1][j][k]+=(1-p[i+1])dp[i][j][k]

\\

dp[i+1][j+1][k+a[i+1]]+=p[i+1]\times dp[i][j][k]
$$

分别对应着第 $i+1$ 局赢和输两种情况。

为何要刷表？是因为我们发现，当 $k+a[i]>200$ 时，就只能够取 $200$。而填表法不能很好地从 $200$ 这个状态转移回去。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
namespace Acc{
	const int N = 2e2+10;
#define db double
	db dp[N][N][N*2],p[N],ans;
	int a[N],n,l,k,m;
	void work(){
		cin>>n>>l>>m;
		for(int i=1;i<=n;i++)cin>>p[i],p[i]/=100;
		for(int i=1;i<=n;i++)cin>>a[i];
		dp[0][0][m+200]=1;
		for(int i=0;i<n;i++){
			for(int j=0;j<=i;j++){
				for(int k=0;k<=400;k++){
					int t=min(400,k+a[i+1]);
					dp[i+1][j][k]+=dp[i][j][k]*(1-p[i+1]);
					if(t>=0)dp[i+1][j+1][t]+=dp[i][j][k]*p[i+1];
				}
			}
		}
		for(int i=l;i<=n;i++)for(int j=200;j<=400;j++)ans+=dp[n][i][j];
		cout<<fixed<<setprecision(10)<<ans;
	}
#undef db
}
int main(){
	return Acc::work(),0;
}
```

---

## 作者：lmy_2011 (赞：2)

这题求概率，不求中间过程，是一道概率动态规划。
### 基本思路
不难想到，既然求概率，所以 $dp_{i,j,k}$ 表示前 $i$ 天赢了 $j$ 场，剩余容量为 $k$ 的概率，状态转移方程就是：
$$dp_{i,j,k}=dp_{i-1,j,k}\times(1-p_i)+dp_{i-1,j-1,k-a_i}\times p$$

我们可以优化，$k$ 看起来很大，但他与状态转移方程的系数无关，所以最后答案相当于可以求 $\sum_{i=l}^n\cdot \sum_{j=l}^{200}\cdot dp_{n,i,j}$。

时间复杂度 $\mathrm{O(n^3)}$。
### 优化
既然时间复杂度这么高，那么我们可以一下优化：
- 获得后面的容积，再得到物品。
- 将容积增大 $200$，增至 $[0,400]$。
- 取 $dp_{i,j,k}$ 的值可取精确，只取变大后的后 $200$ 个，也就是 $[200,400]$。

---

## 作者：king_xbz (赞：2)



不错的一道期望DP，校内模拟赛考到了，发现这里竟然还没有题解，就赶来发一下。

我们设状态：$dp[i][j][k]$表示$i$轮游戏，赢了$j$次，背包容积为$k$

那么当背包容积加上属性值不超限制时，我们可赢可输，否则，我们不能赢只能输。

由此可以得到状态转移方程式：

$dp[i+1][j+1][k]+=dp[i][j][k]*p$($win$)

$dp[i+1][j][k+val]+=dp[i][j][k]*(1-p)$($lose$)

注意$k+val>n$时我们最多只能得到$n$个物品奖励。

最后我们枚举求$dp[n][l\to n][0\to n]$的加和即可。

代码：

```cpp
#include<bits/stdc++.h>
#define fint register int
#define H 205
#define N 30001
#define AK cout<<"LYFX and ZGW AK IOI"<<endl
using namespace std;
struct node
{
	double p;
	int val;
}
a[N];
double dp[H][H][H];//i轮游戏，赢了j次，背包容积为k 
inline int read();
inline bool cmp(node aa,node bb);
int main()
{
	int n,L,k;
	n=read(),L=read(),k=read();
	for(fint i=1;i<=n;i++)
	a[i].p=read(),a[i].p/=(double)100;
	for(fint i=1;i<=n;i++)
	a[i].val=read();
	dp[0][0][min(k,n)]=1;
	sort(a+1,a+n+1,cmp);
	for(fint i=0;i<n;i++)
	for(fint j=0;j<=i;j++)
	for(fint l=0;l<=n;l++)
	{
		if(l+a[i+1].val>=0)
		dp[i+1][j+1][l+a[i+1].val>n?n:l+a[i+1].val]+=dp[i][j][l]*a[i+1].p;
		dp[i+1][j][l]+=dp[i][j][l]*(1-a[i+1].p);
	}
	double ans=0;
	for(fint i=L;i<=n;i++)//至少成功l次 
	for(fint j=0;j<=n;j++)
	ans+=dp[n][i][j];
	printf("%.8lf",ans);
	return 0;
}

inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
		f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}

inline void print(int x)
{
	if(x<0)
	putchar('-'),x=-x;
	if(x>9)
	print(x/10);
	putchar(x%10+'0');
	return ;
}

inline bool cmp(node aa,node bb)
{
	return aa.val>bb.val;
}
```



---

## 作者：OE_AiHAn (赞：0)

## [CF167B](https://codeforces.com/problemset/problem/167/B)

### 题意
给定初始背包容量 $k$, 要进行 $n$ 场比赛，每场比赛有 $p_i\%$ 的概率能够胜利，赢的一场比赛能获得一个奖励——当 $a_i = -1$ 时获得一个体积为 $1$ 的奖品，或者当 $a_i > 0$ 时给背包增加 $a_i$ 容量，求所有比赛结束后至少赢得 $l$ 场且背包能装下所有奖品的概率。
$(1 \le n \le 200, 0 \le l, k, a_i \le 200, 0 \le p_i \le 100)$ 

### 解析
大部分题解都把奖品和增加背包容量放在一起进行转移，其实两者可以分开，我们将能增加背包容量的比赛（以下简称 a 类比赛）设为 $a_i$，其它的比赛（以下简称 b 类比赛）设为 $b_i$。对于背包容量的转移，设 $i$ 为当前进行了几场 a 类比赛（此处转移方程均针对 a 类比赛），$j$ 为已赢下几场比赛，$k$ 为背包容量，有转移方程如下：
$$dp^1_{i, j, k} = dp^1_{i - 1, j, k} \times \frac{100 - p_i}{100} + dp^1_{i - 1, j - 1, k - a_i} \times \frac{p_i}{100}$$
初始化为 $dp^1_{1,0,k} = 1$。但此时复杂度为 $O(n^2\sum{a_i})$，约 $1.6 \times 10^9$，肯定系 T 飞了的。

观察到背包容量其实最多只需要到 $n$，更多的容量没有作用，因此可以将第三维（$k$ 的那一维）的范围从 $\sum{a_i}$ 压缩到 $n$，大概 $200$，这样时间复杂度就能过了；另外，对于 $dp^1$ 数组的第一维（$i$ 的一维），可以滚动数组优化掉，使空间复杂度从 $O(n^3)$ 压到 $O(n^2)$，不至于空间超限。

而对于 b 类比赛的转移，由于奖品体积固定为 $1$，设 $i$ 为第几场 b 类比赛，$j$ 为已赢下 b 类比赛的数量，有转移方程：
$$dp^2_{i, j} = dp^2_{i - 1, j} \times \frac{100 - p_i}{100} + dp^2_{i - 1, j - 1} \times \frac{p_i}{100}$$
同样的，$dp^2$ 数组的第一维也是可以滚动数组优化掉的。

最后，先对 $dp^1$ 数组进行前缀和处理，即可求出答案 $ans$，设共有 $m$ 场 b 类比赛，答案为
$$ans = \sum{dp^2_{m, j} \times (dp^1_{n - m, n - m, \sum{a_i}} - dp^1_{n - m, l - j - 1, \sum{a_i}} - dp^1_{n - m, n - m, j - 1} + dp^1_{n - m, l - j - 1, j - 1})}$$
其中，$dp^1_{n - m, l - j - 1, \sum{a_i}}$ 在前缀和后变成赢得不超过 $l - j - 1$ 场 a 类比赛的概率，由于 $dp^1$ 数组第三维的计算在大概 200 停止，$dp^1_{n - m, j, \sum{a_i}}$ 可以用类似于求 $dp^2$ 的方法求出。则有
$$ans = \sum{dp^2_{m, j} \times (1 - dp^1_{n - m, l - j - 1, \sum{a_i}} - dp^1_{n - m, n - m, j - 1} + dp^1_{n - m, l - j - 1, j - 1})}$$
需要注意的是，在计算 dp 数组和答案 $ans$ 的时候，都要注意判定防止数组下标越界（出现负数下标）；另外，由于此题对精度的要求仅为 $10^{-6}$，dp 时可以用 long long 数组存储而不是 long double，防止丢精度（亲测，被 long double 玩了 QwQ）。

### 代码
```c++
#include <bits/stdc++.h>
#define LL long long
#define double long double
#define pii pair<int, int>

using namespace std;

int ps[205];
vector<int> p;
vector<pii> a;
vector<LL> pon(205, 0.0), powi(205, 0.0); //使用long long防止丢精度
vector<vector<LL> > dp(205, vector<LL>(405, 0)); //dp数组均被滚动优化掉一维

int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);

    p.push_back(0);
    a.push_back({ 0, 0 });

    int n, l, k, c;
    cin >> n >> l >> k;
    for (int i = 1; i <= n; i++)
        cin >> ps[i];
    for (int i = 1; i <= n; i++)
    {
        cin >> c;
        if (c < 0)
            p.push_back(ps[i]);
        else
            a.push_back({ c, ps[i] });
    }

    //计算dp1数组
    dp[0][k] = 1e12;
    for (int i = 1; i < a.size(); i++)
        for (int j = i; j >= 0; j--)
            for (int m = 400; m >= 0; m--)
                dp[j][m] = dp[j][m] * (100 - a[i].second) / 100 + (m >= a[i].first && j ? dp[j - 1][m - a[i].first] * a[i].second / 100 : 0); //三元运算符用于特判防止下标越界，以下同
    for (int i = 1; i <= 400; i++) //前缀和
        dp[0][i] += dp[0][i - 1];
    for (int i = 1; i < a.size(); i++)
    {
        dp[i][0] += dp[i - 1][0];
        for (int j = 1; j <= 400; j++)
            dp[i][j] += dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1];
    }
    
    //同为dp1数组
    powi[0] = 1e12;
    for (int i = 1; i < a.size(); i++)
        for (int j = i; j >= 0; j--)
            powi[j] = powi[j] * (100 - a[i].second) / 100 + (j ? powi[j - 1] * a[i].second / 100 : 0);
    for (int i = 1; i < a.size(); i++) //前缀和
        powi[i] += powi[i - 1];
        
    //计算dp2数组
    pon[0] = 1e12;
    for (int i = 1; i < p.size(); i++)
        for (int j = i; j >= 0; j--)
            pon[j] = pon[j] * (100 - p[i]) / 100 + (j ? pon[j - 1] * p[i] / 100 : 0);

    //计算答案
    double ans = 0.0;
    for (int i = max(l - (int)a.size() + 1, 0); i < p.size(); i++)
        ans += (double)pon[i] / 1e12 * ((double)((LL)1e12 - (l - i > 0 ? powi[l - i - 1] : 0) - (i ? dp[a.size() - 1][i - 1] : 0) + (l - i > 0 && i ? dp[l - i - 1][i - 1] : 0)) / 1e12);
    printf("%.12LF\n", ans);
}
```

最后祝各位顺利AC。  >w<

---

## 作者：qianxinyu (赞：0)

# [Wizards and Huge Prize(CF167B)](https://www.luogu.com.cn/problem/CF167B)
## 题目大意:
$n$ 个比赛，每个比赛有 $0.01 \times p_i$ 的概率获胜，可以得到 $a_i \in\{-1\}\cup(0,200]$ 的分数。最后求得到 $0$ 分以上且至少赢 $l$ 局的概率。
## 思路：
想暴力时可以想到在两种不同的情况中，有的区别可能是：
 - 第几场
 - 已经赢了几场
 - 有多少分

那么我们就先把这三维设成状态，求出对应概率，容易想到转移方程：
 - $f_{i,j+jl_i,t}+=f_{i-1,j,t-1}\times gl_i\times0.01$
 - $f_{i,j,t}+=f_{i-1,j,t}\times(1.0-0.01\times gl_i)$

第一个转移赢的情况，第二个转移没赢的情况。

时空复杂度 $O(n^3)$。
## 处理：
1. 第一个问题在于你如果把程序跑到分数的上限，那么复杂度会变成 $O(n^2 \times \sum gl_i)$。但考虑到每次最多只可能让分数减一，所以分数超过 $n$ 就可以保证分数不可能被减到负数，我们可以一旦 $j+jl_i \ge n+2$ 就把  $j+jl_i$ 设成 $n+2$，这样就不会炸了。

2. double 数组开到 $200^3$ 让我很慌，又发现这题每次转移只设及 $i$ 和 $i-1$。所以果断开滚存。其实还有一种方法，就是把所有概率乘 $10^8$ 用 int 存，因为题目只要求 $10^{-6}$ 的精度，且每个概率不超过 $1$。（方法 $2$ 有概率被卡，可以开 long long 防止被卡）~~我真是空间管理大师。~~

3. $j$ 可能是负数，那就在每一一个涉及 $j$ 的地方加上一个数。
## 代码：
```cpp
#include"cstdio"
inline int min(int x,int y){return x<y?x:y;}
int n,l,k;
double f[3][410][210],ans;
int gl[210];
int jl[210];
int main()
{
	scanf("%d%d%d",&n,&l,&k);
	for(int i=1;i<=n;i++)scanf("%d",&gl[i]);
	for(int i=1;i<=n;i++)scanf("%d",&jl[i]);
	if(k>n+2)k=n+2;//防止k大于n而被忽略 #wa on 83
	f[0][k+205][0]=1.0;
	for(int i=1;i<=n;i++)
	{
		//转移
		for(int j=-i;j<=n+2;j++)
		{
			f[1][j+205][0]+=f[0][j+205][0]*(1.0-0.01*gl[i]);
			for(int t=1;t<=i;t++)
			{
				f[1][min(j+jl[i],n+2)+205][t]+=f[0][j+205][t-1]*gl[i]*0.01;
				f[1][j+205][t]+=f[0][j+205][t]*(1.0-0.01*gl[i]);
			}
		}
		//滚存
		for(int j=-i;j<=n+2;j++)
		{
			for(int t=0;t<=i;t++)
			{
				f[0][j+205][t]=f[1][j+205][t];
				f[1][j+205][t]=0.0;
			}
		}
	}
	for(int j=0;j<=n+2;j++)
	{
		for(int t=l;t<=n;t++)
		{
			ans+=f[0][j+205][t];//统计答案
		}
	}
	printf("%.10lf",ans);
	return 0;
}
```

---

## 作者：傅思维666 (赞：0)

## 题解：

期望DP好题。

题目大意他概括的不清晰，我重新说一下：

最开始你有k的容积，有n轮比赛，**每轮比赛的胜率为pi**，比赛分为两种(具体种类由输入给出，**给出ai>=1是第一种，给出-1为第二种**)，第一种的奖品是增加ai容积，另一种增加一个物品，**体积为1**，只有到最后的容积装得下所有赢得的物品才算合法的方案，问赢得的比赛总场数>=l的合法方案的概率。

那么设置状态为：$dp[i][j][k]$表示当前$i$轮游戏，赢了$j$次，背包容积为$k$时的合法概率。

那么答案就是
$$
\sum_{i=l}^{n}\sum_{j=0}^{n}dp[n][i][j]
$$
转移的时候也比较好想：背包容积加上这个值之后，如果不超过限制，那么输赢无所谓，否则，就必须要输，否则就和合法的状态相悖。

那么代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxh=210;
const int maxn=3e4+4;
struct node
{
	double p;
	int val;
}a[maxn];
int n,L,k;
double dp[maxh][maxh][maxh];//i轮游戏，赢了j次，背包容积为k 
bool cmp(node a,node b)
{
	return a.val>b.val;
}
int main()
{
	scanf("%d%d%d",&n,&L,&k);
	for(int i=1;i<=n;i++)
    {
	    scanf("%lf",&a[i].p);
        a[i].p/=1.0*100;
    }
	for(int i=1;i<=n;i++)
	    scanf("%d",&a[i].val);
	dp[0][0][min(k,n)]=1;
	sort(a+1,a+n+1,cmp);
	for(int i=0;i<n;i++)
	    for(int j=0;j<=i;j++)
	        for(int l=0;l<=n;l++)
	        {
		        if(l+a[i+1].val>=0)
		            dp[i+1][j+1][l+a[i+1].val>n?n:l+a[i+1].val]+=dp[i][j][l]*a[i+1].p;
		        dp[i+1][j][l]+=dp[i][j][l]*(1-a[i+1].p);
	        }
	double ans=0;
	for(int i=L;i<=n;i++)
	    for(int j=0;j<=n;j++)
	        ans+=dp[n][i][j];
	printf("%.8lf",ans);
	return 0;
}
```



---

