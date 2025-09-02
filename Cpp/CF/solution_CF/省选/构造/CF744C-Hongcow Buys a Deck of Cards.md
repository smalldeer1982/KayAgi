# Hongcow Buys a Deck of Cards

## 题目描述

One day, Hongcow goes to the store and sees a brand new deck of $ n $ special cards. Each individual card is either red or blue. He decides he wants to buy them immediately. To do this, he needs to play a game with the owner of the store.

This game takes some number of turns to complete. On a turn, Hongcow may do one of two things:

- Collect tokens. Hongcow collects $ 1 $ red token and $ 1 $ blue token by choosing this option (thus, $ 2 $ tokens in total per one operation).
- Buy a card. Hongcow chooses some card and spends tokens to purchase it as specified below.

The $ i $ -th card requires $ r_{i} $ red resources and $ b_{i} $ blue resources. Suppose Hongcow currently has $ A $ red cards and $ B $ blue cards. Then, the $ i $ -th card will require Hongcow to spend $ max(r_{i}-A,0) $ red tokens, and $ max(b_{i}-B,0) $ blue tokens. Note, only tokens disappear, but the cards stay with Hongcow forever. Each card can be bought only once.

Given a description of the cards and their costs determine the minimum number of turns Hongcow needs to purchase all cards.

## 说明/提示

For the first sample, Hongcow's four moves are as follows:

1. Collect tokens
2. Buy card $ 1 $
3. Buy card $ 2 $
4. Buy card $ 3 $

 Note, at the fourth step, Hongcow is able to buy card $ 3 $ because Hongcow already has one red and one blue card, so we don't need to collect tokens.For the second sample, one optimal strategy is as follows:

1. Collect tokens
2. Collect tokens
3. Buy card $ 2 $
4. Collect tokens
5. Buy card $ 3 $
6. Buy card $ 1 $

 At the fifth step, even though Hongcow has a red token, Hongcow doesn't actually need to spend it, since Hongcow has a red card already.

## 样例 #1

### 输入

```
3
R 0 1
B 1 0
R 1 1
```

### 输出

```
4
```

## 样例 #2

### 输入

```
3
R 3 0
R 2 0
R 1 0
```

### 输出

```
6
```

# 题解

## 作者：Rainbow_qwq (赞：9)

[CF744C Hongcow Buys a Deck of Cards](https://www.luogu.org/problem/CF744C)

# 思路

看到$1\leq n\leq 16$，一定是状态压缩$dp$。

$dp$状态设计极为巧妙：  

设$f[S][j]$为买了$S$这个集合的卡， **省下了$j$颗红宝石时**，能够 **省下最多蓝宝石的数量**

设$ca[S]$表示$S$这个集合的红卡数量，$cb[S]$表示$S$这个集合的蓝卡数量。$ca$与$cb$可以预处理。

若$S$集合时，第$i$卡还没买。若买了$i$这张卡，能省下$\min(a[i],ca[S])$颗红宝石，$\min(b[i],cb[S])$颗蓝宝石。

那就可以转移了，当成一个背包，$\min(a[i],ca[S])$为重量，$\min(b[i],cb[S])$为价值。

状态转移方程：
```cpp
int T=S|(1<<i);//转移状态
int ma=min(a[i],ca[S]),mb=min(b[i],cb[S]);
f[T][j+ma]=max(f[T][j+ma],f[S][j]+mb);//转出
```
# 答案

题目中说 **“获得一颗红宝石和一颗蓝宝石”** 也就是买红宝石和蓝宝石的个数是一样的。

那就可以一开始把宝石都买够，再全部买卡。

最终答案为$\mathrm{max(suma-i,sumb-f[2^n-1][i])+n}$  
suma与sumb为买所有卡红宝石和蓝宝石的总量。

先买$\mathrm{max(suma-i,sumb-f[2^n-1][i])}$次宝石，最后$n$次买卡。

边界条件：先将$f$数组初始化为$-1$,$f[0][0]=0$,若dp结束$f[S][i]$为$-1$，这种状态就达不到。

# 代码

代码中`S>>i&1`表示判断`S`集合中是否包含`i`。
```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(register int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(register int i=(a);i>=(b);--i)
using namespace std;
inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}
int n,suma,sumb,a[17],b[17];
int ca[1<<16],cb[1<<16],f[1<<16][126];
int main()
{
	n=read();
	int maxst=(1<<n)-1;
	For(i,0,n-1){
		char ch;while(!isupper(ch=getchar()));
		a[i]=read(),b[i]=read();
		suma+=a[i],sumb+=b[i];
		For(j,0,maxst)//预处理ca[],cb[],
			if(j>>i&1){
				if(ch=='R')ca[j]++;
				else cb[j]++;
			}
	}
   //dp
	memset(f,-1,sizeof f);f[0][0]=0;
	For(S,0,maxst)
		For(j,0,122){//j是乱设的122，应当足够
			if(f[S][j]==-1)continue;
			For(i,0,n-1){
				if(S>>i&1)continue;
				int T=S|(1<<i);
				int ma=min(a[i],ca[S]),mb=min(b[i],cb[S]);
				f[T][j+ma]=max(f[T][j+ma],f[S][j]+mb);
			}
		}
	int res=0x3f3f3f3f;
	For(i,0,122)
		if(~f[maxst][i])
			res=min(res,max(suma-i,sumb-f[maxst][i]));
	cout<<res+n;//加上n
    return 0;
}
```

---

## 作者：EastPorridge (赞：6)

大家好啊，我非常喜欢模拟退火，所以我用模拟退火把这道状压 dp 过了，而且跑的飞快，目前是最优解，比写状压 dp 的快几十秒。

### 题目分析：

我们用乱搞的心态去思考这道题，当我们随机出一个序列的时候，我们可以用 $O(n)$ 的复杂度去针对当前序列统计出答案，且这个 $n$ 非常小，最大只有 $16$。

考虑怎么退火，如果每一次只随机交换的两个值，效率会很低，且在 $16!$ 的序列中出现正解的概率也非常小，自己随机造了点数据，发现在 $13!$ 左右就不是很跑的出来了。

所以我们按照退火的思想，在温度高的时候多次交换序列中任意两个值，在温度低的时候趋于稳定，少交换值，我们设定每次交换的次数为 $\frac{n \times T}{T'}+1 $ 次，$n$ 是序列长度，$T$ 是当前温度，$T'$ 为初始温度，这样保证交换次数会随着温度逐渐下降，$+1$ 保证每次至少进行了一次交换。

交一发，发现在一百多个点的时候会 WA ，且相差的值很小，我的是相差只有 $1$，考虑精度不够，所以调高了乘法步长的精度，多跑了 $5$ 次，然后就差不多了。

需要注意的问题：这个题我认为很依赖模拟退火可以概率接受差解来跳出区域最优解的特性，所以注意不要写假了接受差解的部分；`mt19937` 比 `rand` 快，我推荐使用 `mt19937` 来进行随机取值；拿 `vector` 存下序列，每次直接交换按理说会比 `memcpy` 赋值数组快，如果被卡了可以试试 `vector`。

### Code.

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=18; mt19937 rnd(time(NULL));
struct node {int op,x,y;} a[N],b[N];
int n,res=0x3f3f3f3f; char ch[3];
int calc()
{
	int s1=0,s2=0,r=0,b=0,sum=0;
	for(int i=1;i<=n;i++)
	{
		int tmp=max(max(0,a[i].x-r-s1),max(0,a[i].y-b-s2));
		s1+=tmp-max(a[i].x-r,0); s2+=tmp-max(a[i].y-b,0); sum+=tmp;
		if(a[i].op == 2) r++; else b++;
	}
	return sum+n;
}
void SA()
{
	for(double T=1000.0;T>1e-3;T*=0.9999)
	{
		int tmp=calc(),pl=n*T/1000.0+1; memcpy(b,a,sizeof b); 
		while(pl --) swap(a[rnd()%n+1],a[rnd()%n+1]);
		int nw=calc(),del=tmp-nw; res=min(res,min(tmp,nw));
		if(del > 0 || rnd()%RAND_MAX+1  < exp(1.0*del/T)*RAND_MAX) continue ;
		memcpy(a,b,sizeof a);
	}
}
int main()
{
	scanf("%d",&n); for(int i=1;i<=n;i++) {scanf("%s%d%d",ch,&a[n-i+1].x,&a[n-i+1].y); a[n-i+1].op=(ch[0]=='R')+1;}
	for(int i=1;i<=5;i++) SA();
	printf("%d",res);
	return 0;
}
```
------------
一点闲话：写到这里，离 CSP2022 只剩整整一周了，作为高二的我，还是面临退役的其他人，这都是我们的 final chance，想到这里也是感慨万分，希望选择 OI 的你不会后悔，从今往后，无论是 OI 还是 whk，都能收获像现在坐在机房的你，为了目标而奋斗的喜悦，绕远的路，总有风景。

![](https://cdn.luogu.com.cn/upload/image_hosting/ukf2177x.png)

---

## 作者：RainFestival (赞：1)

考虑状压即可。

记 $A_s$ 为 $\sum\limits_{i\in s} a_i$，$B$ 为 $\sum\limits_{i\in s} b_i$。

记录 $dp_{s,i}$ 为收集了 $s$ 集合的卡片，用了 $i$ 颗红宝石，最少用多少颗蓝宝石。

这样时间复杂度是 $\mathcal{O(2^n\times A_n)}$。

然后发现对于一个合法的 $s,i$，$i$ 和 $A_s$ 相差不会很大。

然后把 $i$ 替换成 $A_s-i$ 即可。

大概是 $O(n^32^n)$ 左右。

代码：

```cpp
#include<cstdio>
#include<cstdlib>
#include<utility>
#include<algorithm>
#define base 152
#define maxd 150
struct card
{
	int col,r,b;
};
int n;
card f[20];
std::pair<int,int> w[80005];
int dp[80005][320],ans;
int getopt()
{
	char ch=getchar();
	if (ch=='R'||ch=='B') return ch=='R'?1:-1;
	return getopt();
}
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) f[i].col=getopt(),scanf("%d%d",&f[i].r,&f[i].b);
//	for (int i=1;i<=n;i++) printf("%d %d %d\n",f[i].col,f[i].r,f[i].b);
	for (int i=0;i<(1<<n);i++)
	    for (int k=1;k<=n;k++)
	        if (i&(1<<(k-1))) f[k].col==1?++w[i].first:++w[i].second;
	for (int i=0;i<(1<<n);i++) for (int j=-maxd;j<=maxd;j++) dp[i][j+base]=1000000000;
	dp[0][0+base]=0;
	for (int i=1;i<(1<<n);i++)
		for (int k=1;k<=n;k++)
		{
			if (!(i&(1<<(k-1)))) continue;
			int lst=i-(1<<(k-1)),wr=w[lst].first,wb=w[lst].second,nr=std::max(f[k].r-wr,0),nb=std::max(f[k].b-wb,0);
//			printf("To sta = %d, From status = %d, red = %d, blue = %d(purchase %d)\n",i,lst,nr,nb,k);
			for (int x=-maxd;x<=maxd;x++)
			{
				int ur,ub,t;
				if (x>0) ur=dp[lst][x+base]+nr,ub=dp[lst][x+base]-x+nb,t=ur-ub;
				else ur=dp[lst][x+base]-x+nr,ub=dp[lst][x+base]+nb,t=ur-ub;
				if (t>maxd) t=maxd;if (t<-maxd) t=-maxd;
				if (t>0) dp[i][t+base]=std::min(dp[i][t+base],ur);
				else dp[i][t+base]=std::min(dp[i][t+base],ub);
//				printf("(%d %d) to (%d %d), purchase %d, cost %d(red = %d, blue = %d)\n",lst,x,i,t,k,std::max(ur,ub),ur,ub);
//				printf("dp value = %d\n",dp[i][t+base]);
			}
		}
//	for (int i=0;i<(1<<n);i++)
//    {
//    	for (int x=-10;x<=10;x++) printf("%d ",dp[i][x+base]);
//    	puts("");
//	}
	ans=1000000000;
	for (int x=-maxd;x<=maxd;x++) ans=std::min(ans,dp[(1<<n)-1][x+base]);
	printf("%d\n",ans+n);
	return 0;
}
```

---

## 作者：ainivolAGEM (赞：0)

**前情提要：**[更好的阅读体验。](https://www.luogu.com.cn/article/hvvjfc7i)

## 题目大意

[题目](https://www.luogu.com.cn/problem/CF744C)较为简洁，没看过的可先去看。

## 题目分析

一看 $n$ 的范围，而且有关操作队列，一看就是状压了。

但是很明显，$n$ 的范围不止可供状压过，那么~~由于我想整活~~出于实践精神，我们尝试使用**模拟退火**通过这道题。

显然，当每次随机出一个序列时，我们就可以用 $O ( N )$ 的时间复杂度判断完序列的答案。问题在于怎么随机序列，如果每次只随机交换两个数据的值，对于 $n \leq 12$ 的情况还可以，但是从 $n = 13$ 开始就跑不动了。

考虑退火，当在“温度高”时多次交换任意值，使其“温度降下去”，而“温度稳定”时则少交换。（最佳转换方式来源于网上及微调）

注意：由于 `mt19937` 比 `rand` 快，所以还是使用 `mt19937`，同时为了加大正确率，我们在不 TLE 的情况下跑五遍程序。

那么交上去，这是[第一次结果](https://www.luogu.com.cn/record/157650040)，可以发现第 $33$ 个点 WA 了，是~~阳寿问题~~正常现象。[第二次交](https://www.luogu.com.cn/record/157650156)就可以了。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=22;
const int T=3;
const int inf=0x3f3f3f3f;
ll n,ans=inf;
char ch;
mt19937 rnd(time(NULL));
struct node{
	ll op,r,b;
}a[N],b[N];
ll work(){
	ll t1,t2,r,b,sum;
	t1=t2=r=b=sum=0;
	for(int i=1;i<=n;i++){
		ll t=max(max(0ll,a[i].r-r-t1),max(0ll,a[i].b-b-t2));
		t1+=t-max(a[i].r-r,0ll);
		t2+=t-max(a[i].b-b,0ll);
		sum+=t;
		if(a[i].op==2){
			r++;
		}else{
			b++;
		}
	}
	return sum+n;
}
void SA(){
	for(double T=1000.0;T>1e-3;T*=0.9999){
		ll t1=work();
		ll accuracy=n*T/1000.0+1;
		memcpy(b,a,sizeof(b));
		while(accuracy--){
			swap(a[rnd()%n+1],a[rnd()%n+1]);
		}
		ll t2=work();
		ll dif=t1-t2;
		ans=min(ans,min(t1,t2));
		if(dif>0||rnd()%RAND_MAX+1<exp(1.0*dif/T)*RAND_MAX){
			continue;
		}
		memcpy(a,b,sizeof(a));
	}
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>ch>>a[n-i+1].r>>a[n-i+1].b;
		if(ch=='R'){
			a[n-i+1].op=2;
		}else{
			a[n-i+1].op=1;
		}
	}
	for(int i=1;i<=5;i++){
		SA();
	}
	cout<<ans;
}
```

部分最优参考数据来源于网上。

---

## 作者：demon_yao (赞：0)

### 思路
- 求最少回合就能完成任务，~~显然~~是$DP$。又因为$DP$涉及到当前买的卡的数量，所以我们会想到状压$DP$。

- 考虑如何设计状态，这个应该蛮简单的，我们设$S$为当前买的卡的集合，$cnta[S]$为当前状态为$S$时所含$a$类型卡的数量，$cntb[S]$同理，于是我们就很容易得到预处理部分的$code$。
```cpp
	for(int i=0;i<n;i++){
		scanf(" %c",&ch);a[i]=read();b[i]=read();
		suma+=a[i];sumb+=b[i];
		for(int j=0;j<=maxn;j++){
			if(j>>i&1){
				if(ch=='R') cnta[j]++;
				else cntb[j]++;
			}
		}
	}
```

- 接下来就是状态与转移方程了，由于省的红蓝宝石越多，步骤就会越少，于是我们便想到了用$f[S][j]$来表示当买了卡的集合为$S$时,能剩下红宝石最大数为$j$时，能省下的蓝宝石最大数。至于如何转移，我们考虑买第$i$张卡时，能省下的最大红宝石数为$min(a[i],cnta[S])$,能省下的最大蓝宝石数为$min(b[i],cntb[S])$。把他们看成正常的$01$背包就可以啦。

```cpp
	for(int S=0;S<=maxn;++S){
		for(int j=0;j<=150;j++){
			if(f[S][j]==-1)continue;
			for(int i=0;i<n;i++){
				if(S>>i&1)continue;
				int T=S|(1<<i);
				int ma=min(a[i],cnta[S]),mb=min(b[i],cntb[S]);
				f[T][j+ma]=max(f[T][j+ma],f[S][j]+mb);
			}	
		}
	}
```

- 最后的最后，我们只需遍历一遍数组就可以找出答案了(注意输出别忘了加上$n$次买卡的回合$qwq$)。

```cpp
	for(int i=0;i<=150;i++)
		if(~f[maxn][i]) res=min(res,max(suma-i,sumb-f[maxn][i]));
	cout<<res+n;
```

$PS$:

1. 对于整个过程，我们可以看作一次性先把宝石买够，之后再买卡，这样会方便很多。
2. 注意答案的初值设大点，我设了$214111111$,之前设太小$wa$了$2$次$QAQ$。

---

