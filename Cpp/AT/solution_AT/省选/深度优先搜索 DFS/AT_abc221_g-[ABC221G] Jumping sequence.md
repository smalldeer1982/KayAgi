# [ABC221G] Jumping sequence

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc221/tasks/abc221_g

無限に広がる $ 2 $ 次元の座標平面を考えます。 高橋君は最初 $ (0,0) $ に立っており、今から上下左右いずれかの方向を選んでジャンプすることを $ N $ 回行います。 それぞれのジャンプで移動する距離は定まっており、具体的には $ i $ 回目のジャンプでは距離 $ D_i $ を移動します。 $ N $ 回のジャンプの後で、ちょうど位置 $ (A,B) $ にいるようにすることは可能か判定し、 可能ならばそのような移動方法を $ 1 $ つ示してください。

ただし、現在の位置が $ (X,Y) $ のときに、それぞれの方向を選んで距離 $ D $ のジャンプをしたときの着地地点はそれぞれ以下の通りです。

- 上方向 : $ (X,Y)\ \to\ (X,Y+D) $
- 下方向 : $ (X,Y)\ \to\ (X,Y-D) $
- 左方向 : $ (X,Y)\ \to\ (X-D,Y) $
- 右方向 : $ (X,Y)\ \to\ (X+D,Y) $

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2000 $
- $ \lvert\ A\rvert,\ \lvert\ B\rvert\ \leq\ 3.6\times\ 10^6 $
- $ 1\ \leq\ D_i\ \leq\ 1800 $
- 入力は全て整数である。

### Sample Explanation 1

$ 1 $ 回目のジャンプで左方向に、$ 2 $ 回目のジャンプで下方向に、$ 3 $ 回目のジャンプで右方向にジャンプすると、 $ (0,0)\to(-1,0)\to(-1,-2)\to(2,-2) $ と高橋君は動き、 最終的に $ (2,-2) $ に到達しているためこれは条件をみたしています。

### Sample Explanation 2

$ 2 $ 回のジャンプの後でちょうど $ (1,0) $ にいるようにすることはできません。

## 样例 #1

### 输入

```
3 2 -2
1 2 3```

### 输出

```
Yes
LDR```

## 样例 #2

### 输入

```
2 1 0
1 6```

### 输出

```
No```

## 样例 #3

### 输入

```
5 6 7
1 3 5 7 9```

### 输出

```
Yes
LRLUR```

# 题解

## 作者：AFewSuns (赞：45)

很好奇怎么没有题解提到复杂度更优的做法。

### 题目大意

有一个无限大的平面直角坐标系，初始时你在 $(0,0)$ 处。你要走 $n$ 步，每次需要向上/下/左/右走 $d_i$ 的距离，不能不走，最终要走到 $(A,B)$。问是否有解，有解则给出方案。

$1 \leq n \leq 2000,1 \leq d_i \leq 1800$。

### 题目分析

首先两维背包看起来不太好做，需要稍微转化一下。

不妨设最终走 $x$ 轴的集合为 $S$，走 $y$ 轴的集合为 $T$，那么题目变成给两个集合的 $d_i$ 赋上 $1$ 或 $-1$ 的权，要求两个集合的和分别为 $A$ 和 $B$，变成了一维的背包。

当然不能枚举 $S$ 和 $T$。考虑把两个集合的方案拼在一起，由于集合无交且互补，那么就得到了一个所有数和为 $A+B$ 的方案。同理，把 $T$ 集合的方案取反再拼起来，就得到了一个所有数和为 $A-B$ 的方案。

之后做法就很明了了：考虑倒过来，用背包求出一个所有数和为 $A+B$ 及 $A-B$ 的方案，把两个方案中符号相同的归到 $S$ 集合，不同的归到 $T$ 集合，这就是原问题的一个解。这其实与其他题解中所说的旋转坐标轴本质相同。

那么现在问题就变成了：给所有数赋上 $1$ 或 $-1$ 的权，构造一个和为 $C$ 的方案。假设所有数的初始权值为 $-1$，即让 $C$ 初始时加上 $\sum d_i$，操作就变成选一些数 $+2d_i$。再让 $C$ 除以二，就变成了一个 01 背包问题。

记 $D=\max d_i$。朴素的 01 背包做法时间复杂度为 $\mathcal O(n^2D)$，使用 bitset 优化即可做到 $\mathcal O(\frac{n^2D}{\omega})$。但是这还不够，我们需要更快的算法。

---

接下来我将介绍如何将 01 背包问题做到 $\mathcal O(nD)$ 的复杂度。

首先从前往后贪心地选取物品，即找到最大的 $pos$ 使得 $sum=\sum\limits_{i=1}^{pos}{d_i} \leq C$。若 $pos=n$ 则直接判断 $sum$ 是否等于 $C$，否则将序列分为 $\leq pos$ 和 $> pos$ 两部分。

假设已经知道了最终的解，那么最终的解一定是在目前的基础上丢掉左边的一些物品，再选上右边的一些物品。定义一次操作为丢掉左边物品或选取右边物品，接下来我将说明一定存在某种操作顺序使得目前解到答案的过程中，选取的物品和 $sum$ 始终在 $(C-D,C+D]$ 范围内。

这其实很容易说明。首先一开始的 $sum$ 肯定在范围内，如果当前的 $sum \leq C$，则选取右边的物品；否则丢掉左边的物品。由于 $d_i \leq D$，所以不会超出范围。并且最终的和为 $C$，所以不会出现选完/丢完的情况。

为了方便，不妨假设是从中间断点 $pos$ 往两边操作的，于是就可以 dp 了。设 $f_{l,r,w}$ 表示目前只考虑操作 $[l,r]$ 内的位置，是否能构造出权值和为 $w$ 的方案。$w$ 的范围由上面可知是 $\mathcal O(D)$ 的。初始时 $f_{pos+1,pos,sum}=1$，答案即为 $f_{1,n,C}$。转移时只需要枚举上一步操作是从 $f_{l+1,r}$ 还是 $f_{l,r-1}$ 转移过来，以及 $l$ 和 $r$ 有没有操作。具体转移如下：

- $f_{l,r,w} \leftarrow f_{l,r-1,w}$

- $f_{l,r,w} \leftarrow f_{l+1,r,w}$

- $f_{l,r,w+a_r} \leftarrow f_{l,r-1,w}(w \leq C)$

- $f_{l,r,w-a_l} \leftarrow f_{l+1,r,w}(w > C)$

但是时间复杂度相比普通背包并没有优化。考虑重新设计 dp，设 $g_{r,w}$ 表示**要使得 $f_{l,r,w}=1$，$l$ 最大是多少**，没有则记为 $0$。

转移时还是考虑上一步从哪边转移，以及 $l,r$ 要不要操作。具体转移如下：

- $g_{r,w} \leftarrow g_{r-1,w}$，即从 $r-1$ 转移过来且不操作 $r$；

- $g_{r,w+a_r} \leftarrow g_{r-1,w}(w \leq C)$，即从 $r-1$ 转移过来且操作 $r$；

- $g_{r,w-a_l} \leftarrow l(w > C,l < g_{r,w})$，即从左边转移过来且操作 $l$。

从左边转移但不操作 $l$ 的情况不需要考虑，因为 $g$ 取的是 $\max$。

状态数变少了，但复杂度没变，其瓶颈在于第 $3$ 步。注意到当 $l<g_{r-1,w}$ 时，其会在 $r-1$ 时就被转移，然后从第 $1$ 步转移回来。所以只需要转移 $l \geq g_{r-1,w}$ 即可。对于单个 $w$，转移的复杂度为 $\mathcal O(\sum{g_{r,w}-g_{r-1,w}})=\mathcal O(n)$，于是总时间复杂度为 $\mathcal O(nD)$。

初值为 $g_{pos,sum}=pos+1$，答案即为 $[g_{n,C}>0]$。求方案只需要记录上一步转移即可。

同理，这个做法还可以求背包最大体积。

### 代码

[目前最优解](https://www.luogu.com.cn/record/124754310) 85ms。

```cpp
#include<bits/stdc++.h>
using namespace std;
using namespace my_std;
ll n,A,B,lim=1800,d[2020],f[2020][4040],ans0[2020],ans[2020];
pair<ll,ll> lst[2020][4040];
il void upd(ll x,ll y,ll xx,ll yy,ll v){
	if(f[x][y]<v){
		f[x][y]=v;
		lst[x][y]=MP(xx,yy);
	}
}
il bl solve(ll C){
	ll pos=0,sum=0;
	fr(i,1,n){
		if((sum+d[i])<=C){
			sum+=d[i];
			pos++;
		}
		else break;
	}
	if(pos==n&&sum<C) return 0;
	fr(i,pos,n) fr(j,1,2*lim) f[i][j]=0;
	f[pos][sum-C+lim]=pos+1;
	fr(i,pos+1,n){
		fr(j,1,2*lim) upd(i,j,i-1,j,f[i-1][j]);
		fr(j,1,lim) upd(i,j+d[i],i-1,j,f[i-1][j]);
		pfr(j,2*lim,lim+1) fr(k,f[i-1][j],f[i][j]-1) upd(i,j-d[k],i,j,k);
	}
	if(!f[n][lim]) return 0;
	fr(i,1,pos) ans[i]=1;
	fr(i,pos+1,n) ans[i]=0;
	ll x=n,y=lim;
	while(x>pos){
		ll xx=lst[x][y].fir,yy=lst[x][y].sec;
		if(xx==(x-1)&&yy==(y-d[x])) ans[x]=1;
		else if(x==xx) ans[f[x][y]]=0;
		x=xx;
		y=yy;
	}
	return 1;
}
int main(){
	n=read();
	A=read();
	B=read();
	fr(i,1,n) d[i]=read();
	A+=B;
	B=A-2*B;
	fr(i,1,n) A+=d[i];
	fr(i,1,n) B+=d[i];
	if(A<0||B<0||(A%2==1)||(B%2==1)){
		pf("No");
		return 0;
	}
	A/=2;
	B/=2;
	if(!solve(A)){
		pf("No");
		return 0;
	}
	fr(i,1,n) ans0[i]=ans[i];
	if(!solve(B)){
		pf("No");
		return 0;
	}
	pf("Yes\n");
	fr(i,1,n){
		if(ans0[i]==ans[i]){
			if(!ans0[i]) pc('L');
			else pc('R');
		}
		else{
			if(!ans0[i]) pc('D');
			else pc('U');
		}
	}
}
```

---

## 作者：o51gHaboTei1 (赞：10)

**sol of ABC221G**

我们考虑直接将二维平面转 $45$ 度。

这样终点的坐标为 $(x-y,x+y)$，其它的所有操作都会变化：

- $L(-d,0) \rightarrow L'(-d,-d)$

- $R(d,0) \rightarrow R'(d,d)$

- $U(0,d) \rightarrow U'(-d,d)$

- $D(0,-d) \rightarrow D'(d,-d)$

你发现一个强大的转化题意：对于 $x$ 维和 $y$ 维我们分开确定 $d$ 前面的符号后进行累和，看能否从 $(0,0) \rightarrow (x-y,x+y)$。

我们发现这个问题有点类似 dp 的存在性问题，但是还不能完全转化，于是：

- 显然写成这种形式：$d_1 \pm d_2 \pm \dots d_n = C$

- 等式两边同加 $\sum d_i$，则前面的系数变成了 $0,2$，然后将 $2$ 除过去，将 $C$ 带成 $x-y,x+y$，问题即可变成一个选择/不选的存在性背包问题。

使用 bitset 优化然后输出答案即可。

时空复杂度 $O(\frac{n ^ 2d}{w})$。

```cpp
/*
先将二维坐标轴旋转 45 度，问题变成了能否只在中间添加 +- 凑出两个数 a,b。 
*/
#include "bits/stdc++.h" 
using namespace std;
const int Len = 2e3 + 5 , M = 3.6e6 + 1;
int n,m,a,b,x,y,sm,d[Len],pst[Len];
bitset<M> dp[Len];
inline int Iabs(int x){return x < 0 ? -x : x;}
int main()
{
	scanf("%d %d %d",&n,&x,&y);
	a = x - y , b = x + y;
	for(int i = 1 ; i <= n ; i ++)
	{
		scanf("%d",&d[i]);
		sm += d[i];
	}
	if(Iabs(a) > sm || Iabs(b) > sm) return puts("No") & 0;
	if((a + sm) % 2 == 1 || (b + sm) % 2 == 1) return puts("No") & 0;
	a = (a + sm) / 2 , b = (b + sm) / 2;
	dp[1][0] = 1;
	for(int i = 1 ; i <= n ; i ++) dp[i + 1] = dp[i] | (dp[i] << d[i]);
	if(dp[n + 1][a] == 0 || dp[n + 1][b] == 0) return puts("No") & 0;
	for(int i = n ; i >= 1 ; i --)
	{
		int w = 0;
		if(!dp[i][a]){a -= d[i];w += (1 << 0);}
		if(!dp[i][b]){b -= d[i];w += (1 << 1);}
		pst[i] = w;
	}
	puts("Yes");
	for(int i = 1 ; i <= n ; i ++) 
	{
		if(pst[i] == 0) putchar('L');
		if(pst[i] == 1) putchar('D');
		if(pst[i] == 2) putchar('U');
		if(pst[i] == 3) putchar('R');
	}
	return 0;
}
```

---

## 作者：liangbowen (赞：9)

2024.6.7 update：修改了符号。

[blog](https://www.cnblogs.com/liangbowen/p/18145579)。很典的 trick！记录一下。

关键技巧：走相邻点很难处理，通过改变坐标轴意义，将维度分开考虑。

---

两维混在一起，每一步决策需要考虑两维，非常麻烦。

考虑将 $(x,y)$ 转为 $(x+y,x-y)$，那么每一步操作有如下变化。

+ 上：$(x,y+d_i)\to(x+d_i,y-d_i)$。
+ 下：$(x,y-d_i)\to(x-d_i,y+d_i)$。
+ 右：$(x+d_i,y)\to(x+d_i,y+d_i)$。
+ 左：$(x-d_i,y)\to(x-d_i,y-d_i)$。

发现两维被拆开了，等价于，解决两次下面的问题。

> 钦定 $o_i\in\{-1,1\}$，使得 $\sum\limits_{i=1}^no_i\times d_i=T$。

令 $o^\prime_i\in\{0,2\}$，则 $\sum\limits_{i=1}^no_i\times d_i=\sum\limits_{i=1}^n(o^\prime_i-1)\times d_i$。将常数提出去并进行移项，等价于解决：

> 钦定 $o_i\in\{0,1\}$，使得 $\sum\limits_{i=1}^no_i\times d_i=\dfrac{T+\sum d_i}2$。

即 01 背包问题，直接做即可。时空都有点小爆，bitset 优化即可通过。

[code](https://atcoder.jp/contests/abc221/submissions/52500236)，时间复杂度 $O(\dfrac{n\times\sum |d_i|}\omega)$。

练习：ABC240G。

---

## 作者：Expert_Dream (赞：5)

这是我第一道正经的黑题，鼓掌！

这道题精妙在于将整个图旋转 $45$ 度，虽然可能要画图，但我感觉不用画图也是可以理解的了。

为什么要旋转 $45$ 度呢？

我们先把所有种类的操作的偏移量列出来。

- $L(-d_i,0)$

- $R(d_i,0)$

- $U(0,d_i$

- $D(0,-d_i)$

发现有三种可能的值，有点难搞，怎么办？如果将图旋转了一下，会发生什么呢？

- $L(-d_i,-d_i)$

- $R(d_i,d_i)$

- $U(-d_i,d_i)$

- $D(d_i,-d_i)$

这样，只有了 $d_i$ 和 $-d_i$。

依然不太好搞。然后，我们可以将最终答案的横纵坐标减去 $\sum_{i=1}^n d_i$。这样，每一次的操作就变成了：

也就是说，每一次的操作横纵坐标都加上 $d_i$。

- $L(0,0)$

- $R(2\times d_i,2\times d_i)$

- $U(0,2 \times d_i)$

- $D(2\times d_i,0)$

这样，我们发现了横纵坐标是不会互相依赖的，都是独立的，我们可以对他们进行单独计算，最后拼起来即可。

如何计算能否拼成功呢？那么我们就用到可行性背包问题。

到最后，我们从后往前记录路径就可以了。

[link](https://atcoder.jp/contests/abc221/submissions/51451629)。

---

## 作者：Miraik (赞：4)

纯纯的套路题。

将坐标轴旋转 $45 \degree$，$(A,B)$ 变化为 $(A-B,A+B)$。然后操作就相当于从 $(x,y)$ 走到 $(x\pm d_i,y\pm d_i)$，这样两维就独立了。

对于每一维我们可以用 bitset 背包解决，但是要输出方案，需要开 $n$ 个值域在 $-3.6 \times 10^6 \sim 3.6 \times 10^6$ 的 bitset，然后你发现它开不下。再改一下，发现第二维不开两倍就不会爆，有点难受。

那咋办呢？我们注意到在随机生成的数据下，我们的第二位在背包过程中不会访问到比较大的负下标（就是当值减到比较小的时候，我们直接不管它了）。但是如果数据精心构造一下，让合法方案的减法全部堆到前面，你这样就出事了。

于是我把序列 shuffle 一下，这下你该卡不掉我了吧（

还有就是一个比较有趣的细节：在随机数据下，解可能会很多，因此你在输出方案时不能一直往一个方向跑，不然有可能会 RE（

时间复杂度 $O(\frac{n|A|}{w})$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2005;
const int V=3650001;
const char ch[5]={'L','D','U','R'};
inline int read(){
    int x=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    return x*f;
}
int n,rA,rB,A,B,ans[N];
struct Opt{ int x,y; }d[N];
bitset<V>f[N]; mt19937 rnd(10086001);
inline void solve(int X,int op){
    int flag=0; if(X<0) X=-X,flag=op;
    if(X>=V){ puts("No"); exit(0); }
    f[0].reset(); f[0][50000]=1;
    for(int i=1;i<=n;i++)
        f[i] = (f[i-1]<<d[i].x) | (f[i-1]>>d[i].x);
    if(!f[n][50000+X]){ puts("No"); exit(0); }
    for(int i=n;i;i--){
        if(X<0){
            if(f[i-1][50000+X+d[i].x]) X+=d[i].x,ans[d[i].y]|=flag;
            else X-=d[i].x,ans[d[i].y]|=flag^op;
        }
        else{
            if(f[i-1][50000+X-d[i].x]) X-=d[i].x,ans[d[i].y]|=flag^op;
            else X+=d[i].x,ans[d[i].y]|=flag;
        }
    }
}
int main(){
    n=read(),rA=read(),rB=read(); A=rA-rB,B=rA+rB;
    for(int i=1;i<=n;i++) d[i].x=read(),d[i].y=i; shuffle(d+1,d+n+1,rnd);
    solve(A,1); solve(B,2);
    puts("Yes");
    for(int i=1;i<=n;i++) putchar(ch[ans[i]]);
    putchar('\n');
    return 0;
}
```


---

## 作者：DengDuck (赞：4)

记录一个很巧妙的 Trick。

首先问题看起来很像一个背包问题，对吧。

但是问题来了，我们对于物品既要选择方向（水平还是竖直），又要选择加减符号，这俩分开我们都会做，但是咋在一起了呢？真遗憾。

然后我们可以运用旋转 $45$ 度，在放大 $\sqrt 2$ 的方法，这样如果原来是 $(x,y)$ 的话，现在就是 $(x-y,x+y)$。

其实这个跟曼哈顿距离转切比雪夫距离的原理是一样的，但是这里显然没有距离的出现对吧，所以最好看作一个独立的套路。

那这里这么做有啥好处呢？显然我们把 $x$ 和 $y$ 联系在了一起，因为 $x$ 和 $y$ 中恰好有一个必然会被 $A_i$ 做贡献，所以对于 $x-y$ 和 $x+y$ 来说，每个 $A_i$ 都是有贡献的。

开心！现在我们只需要考虑正负符号就行啦！

这个很简单吧，加上一个 $A$ 的和就变成了朴素的 01 背包问题，`bitset` 秒了。 

那么我们就把这玩意看作两个 01 背包去做，再输出方案即可。

时间复杂度为 $\mathcal O(\dfrac{nW}{\omega})$，其中 $W$ 表示背包的值域，$\omega$ 表示 `bitset` 的常数。

```cpp
#include<bits/stdc++.h>
#define LL long long
#define LF long double
#define pLL pair<LL,LL>
#define pb push_back
#define LowBound lower_bound
#define UpBound upper_bound
//#define Fi first
//#define Se second
//#define Ls(x) (x<<1)
//#define Rs(x) (x<<1|1)
//#define Ls(x) t[x].Lson
//#define Rs(x) t[x].Rson
using namespace std;
//const LL Inf;
const LL N=2e3+5;
const LL M=4e6+5;
//const LL Mod;
//const LF eps;
//const LL P;
LL n,X,Y,x,y,S,A[N],Ans[N];
bitset<M>F[N];
int main()
{
	scanf("%lld%lld%lld",&n,&x,&y);
	X=x-y,Y=x+y;
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&A[i]);
		S+=A[i];
	}
	if(abs(X)>S||abs(Y)>S||(X+S)%2==1||(Y+S)%2==1)
	{
		puts("No");
		return 0;
	}
	X=(X+S)/2,Y=(Y+S)/2;
	F[0][0]=1;
	for(int i=1;i<=n;i++)F[i]=F[i-1]|(F[i-1]<<A[i]);
	if(F[n][X]==0||F[n][Y]==0)
	{
		puts("No");
		return 0;
	}
	for(int i=n-1;i>=0;i--)
	{
		LL op=0;
		if(!F[i][X]){X-=A[i+1],op+=1;}
		if(!F[i][Y]){Y-=A[i+1],op+=2;}
		Ans[i]=op;
	}
	puts("Yes");
	for(int i=0;i<n;i++)
	{
		if(Ans[i]==0)putchar('L');
		if(Ans[i]==1)putchar('D');
		if(Ans[i]==2)putchar('U');
		if(Ans[i]==3)putchar('R');
	}
	return 0;
}
//RP++
```

---

## 作者：Empty_Dream (赞：4)

## 题意

有一个无限大的平面直角坐标系，初始时你在 $(0,0)$ 处。你要走 $n$ 步，每次向上/下/左/右走 $d_i$ 的距离，不能不走，最终要走到 $(x,y)$。

## 分析

有个套路？那就是把坐标系顺时针旋转 $45 \degree$，那就要更新一下旋转后的终点坐标和操作。

操作看起来比较容易，画一张坐标系可以发现，新坐标系上的单位长度是旧坐标系上的 $\sqrt 2$ 倍，而且对应操作也变成了在横坐标和纵坐标上一起移动的形式。我们为了方便操作（解释）就把这个单位长度除以 $\sqrt 2$。终点坐标的变换见下图：

![image-20240320190409386](https://cdn.luogu.com.cn/upload/image_hosting/68dbtpoe.png)

这里需要注意到一点，每次操作横坐标和纵坐标的值更改时相同的，也就是说我们只需要处理一遍 dp 就能处理出来他们俩的可行性。

到了这一步我们的问题就转换成了能否通过 $\sum_{i=1}^{n}d_i \times a$ 这些移动使得最终坐标为 $(x-y,x+y)$， 其中 $a \in \{ -1,1\}$。有点像背包 dp，但是 $x$ 不是选和不选的关系，那我们得进一步转换一下：我们先看横坐标（以下都只考虑横坐标，纵坐标类似），将左右两边同时加上 $\sum d$，这样左边就成为了 $\sum_{i=1}^{n}d_i \times (a+1)$，这里 $a+1 \in\{0, 2\}$，右边变成了 $x-y +\sum d$。这就有点类似了，但是可以进一步转换一下，左右两边同时除以 $2$，这样 $a+1$ 的值就变成了 $0$ 或 $1$，就转化成可行性 dp 了。

对于 dp，先将 $x$ 转化成要 dp 的答案，即 $\frac{x-y+\sum d}{2}$，设 $dp_{i,j}$ 表示取前 $i$ 个状态，能否取到 $j$ 这个坐标，basecase 为 $dp_{0,0}=1$，ans 为 $dp_{n,x}$。转移就是 $dp_{i,j}=dp_{i-1,j}|dp_{i-1,j-d_i}$。但是这里开数组时间有点炸，需要用 bitset 进行优化，转移方程大致相同，只不过省去了枚举 $j$ 的循环，直接整体按位或。

判断完不可达之后就是回溯路径的时候了。我们看一下什么时候要取 $d_i$，只有当这一位到不了最终答案地时候才肯定要取它，也就是 $dp_{i,x}=0$ 时就要取。那怎么判断方向呢，我们回到上面提到的在新坐标系中的操作方式（以下横纵坐标都只新坐标系中的），`U` 和 `R` 都是有纵坐标的变化的，`L` 都是 `D` 有横坐标变化的，那我们就要构造一种记录方式，考虑三进制——每一个数都有唯一的三进制值，仿照这个，设横坐标取的时候权值加 $1$，纵坐标加 $2$，模拟一下发现每一个方向都有一个唯一的值，这样就可以确定了。

至此完结撒花！！！

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, a, b, x, y, sum;
int d[2005], pos[2005];
bitset<3600005> dp[2005];//数据范围是3.6e6……

int main(){
    cin >> n >> a >> b;
    x = a - b, y = a + b;//更新旋转后终点位置
    for (int i = 1; i <= n; i++) cin >> d[i], sum += d[i];
    if (abs(x) > sum || abs(y) > sum) return cout << "No", 0;//特判
    if ((x + sum) & 1 || (y + sum) & 1) return cout << "No", 0;
    x = (x + sum) / 2, y = (y + sum) / 2;//直接转化成我们dp要去做的东西
    dp[1][0] = 1;//basecase 这里为了之后找路径方便计算（美观）把basecase第一维加了1，后面同理
    for (int i = 1; i <= n; i++) dp[i + 1] = dp[i] | (dp[i] << d[i]);//转移
    if (dp[n + 1][x] == 0 || dp[n + 1][y] == 0) return cout << "No", 0;//特判不可能到达
    for (int i = n; i >= 1; i--){
        int tmp = 0;
        if (!dp[i][x]) x -= d[i], tmp++;//统计方法
        if (!dp[i][y]) y -= d[i], tmp += 2;
        pos[i] = tmp;
    }
    cout << "Yes\n";
    for (int i = 1; i <= n; i++){
        if (pos[i] == 0) cout << "L";//按统计方法输出
        if (pos[i] == 1) cout << "D";
        if (pos[i] == 2) cout << "U";
        if (pos[i] == 3) cout << "R";
    }
    return 0;
}
```

---

## 作者：WrongAnswer_90 (赞：2)

# [My Blogs](https://www.cnblogs.com/WrongAnswer90/p/18399404)

### [[ABC221G] Jumping sequence](https://www.luogu.com.cn/problem/AT_abc221_g)

做法有点深刻，优化方式非常深刻。

首先是曼哈顿距离和切比雪夫距离的转化：把坐标系旋转四十五度，变成每次向左上，右上，左下，右下走 $\sqrt 2 a_i$ 的距离，要求最后走到 $(A+B,A-B)$。然后这样可以对于横纵坐标分开做了（非常神奇）。

问题转化成了询问是否存在序列 $x$ 满足 $\forall i,x_i\in\{-1,1\},A=\sum x_ia_i$。先钦定全都是 $+1$ 或者 $-1$ 之后可以变形为，询问是否能从 $a$ 中选择若干个数使得和为 $A$。可以直接 `bitset` 做到 $\mathcal O(\frac{nV^2}{w})$，但是存在更优秀的做法。

首先从前向后找到最大的 $mid$ 满足 $\sum_{j\leq mid}a_j\leq A$。然后如果存在解，则一定是前面删掉若干个元素然后后面再加进来若干个元素。可以设 $f_{l,r,i}$ 表示从 $[l,mid]$ 中选择一些负数，$[mid+1,r]$ 中选择一些正数，能否凑出来 $i$。

一个关键性质是 $i$ 只需要保留 $[-V,V]$ 的部分，其中 $V$ 是题目中数列的值域。证明比较简单，对于一种方案，假设选取的左侧负数是 $x_1\dots x_k$，右侧选取的正数是 $y_1\dots y_s$，如果当前 $i$ 是正的就在左边加负数，否则在右边加正数。如果有一个序列取空了剩下的就直接全取了。因为 $A-\sum_{j\leq mid}a_j\leq V$，所以上面这样值域不会超过 $[-V,V]$。

但是 $f$ 的状态就是 $\mathcal O(nV^2)$ 的。注意到如果固定了 $i,r$，合法的 $l$ 是一段前缀。可以记录 $g_{i,j}$ 表示当前右端点是 $i$，值是 $j$，合法的最大左端点是 $g_{i,j}$。转移：

$$
\begin{aligned}
g_{i+1,j}&\leftarrow g_{i,j}\\
g_{i+1,j+a_i}&\leftarrow g_{i,j}\\
g_{i+1,j-a_k}&\leftarrow k\;\;\;\;\;\;\;\;\;\;\;\;\;\;k\leq g_{i+1,j}
\end{aligned}
$$

现在复杂度瓶颈在于第三种转移。但是可以发现许多第三种转移都是没用的：如果 $k\leq g_{i,j}$，则可以在 $i-1$ 的时候就转移掉这个 $k$。所以每次只需要转移新添进候选值的 $k$，即 $k\in(g_{i,j},g_{i+1,j}]$。因为 $g$ 单调不降，对于一个 $j$，$k$ 的枚举次数即为 $(\sum_{i}g_{i,j}-g_{i-1,j})\leq n$，所以这样总复杂度是 $\mathcal O(nV)$。输出方案也比较平凡，只需要记录从哪个状态转移过来的即可。

```cpp
int n,A,B,a[2010],f[2010][4010];
pii from[2010][4010];
bitset<2010> v1,v2;
void solve(int X)
{
    if(X<0)puts("No"),exit(0);
    int v=0,I=0;memset(f,0,sizeof(f));
    while(I<n&&v+a[I+1]<=X)v+=a[++I];
    if(I==n&&v<X)puts("No"),exit(0);
    v=X-v,f[I][2000]=I+1,v1.reset();
    for(int i=I+1;i<=n;++i)
    {
        for(int j=4000;j>=0;--j)
        {
            if(Mmax(f[i][j],f[i-1][j]))from[i][j]=mp(i-1,j);
            if(j>a[i])if(Mmax(f[i][j],f[i-1][j-a[i]]))
            from[i][j]=mp(i-1,j-a[i]);
            for(int k=f[i-1][j];k<f[i][j];++k)if(j>=a[k])
            if(Mmax(f[i][j-a[k]],k))from[i][j-a[k]]=mp(i,j);
        }
    }
    if(!f[n][2000+v])puts("No"),exit(0);
    for(int i=1;i<=I;++i)v1[i]=1;
    int i=n,j=2000+v,x,y;
    while(i!=I||j!=2000)
    {
        x=from[i][j].fi,y=from[i][j].se;
        if(x==i)v1[f[i][j]]=0;
        else if(y!=j)v1[i]=1;
        i=x,j=y;
    }
}
inline void mian()
{
    read(n,A,B),A=A+B,B=A-B-B;
    for(int i=1;i<=n;++i)read(a[i]),A+=a[i],B+=a[i];
    if((A&1)||(B&1))return puts("No"),void();
    solve(A>>1),v2=v1,solve(B>>1),puts("Yes");
    for(int i=1;i<=n;++i)
    {
        if(v1[i]==v2[i]){if(v1[i])putchar('R');else putchar('L');}
        else{if(v2[i])putchar('U');else putchar('D');}
    }
}
```

---

## 作者：xuanxuan001 (赞：2)

不是很理解为什么题解全是砍一半然后靠 shuffle 过的。

前面的坐标转换是个板，将 $(x,y)$ 对应到 $(x+y,x-y)$，那么题目中的移动就行当于是将横纵坐标分别加减 $a$，这样就把横纵坐标分离开了，这是个 DP，但数据范围看起来不是那么可做。

后面那个 DP 直接用 bitset 卡是我没想到的，不过这么经典的问题确实很难有本质的突破还不被人熟知。

这题的主要问题就是 bitset 开满会 MLE，需要砍掉一半。但是真的有必要通过砍值域来吗？可以参考 CF 的[这道题](https://www.luogu.com.cn/problem/CF101E)，将序列分为两半，先将前一半滚动并求出后一半的决策，再将前一半重新跑一遍来求出前一半的决策。就行当于是用了大概两倍的常数去缩小一半的空间。

我写的最大运行时间才 2.5s，时间是很充裕的。

代码

```
#include<cstdio>
#include<bitset>
#define TY int
#define MAXN 2002
#define MAXM 7200001
#define debug if( 1 &&putchar('>'))
#define FOR(i,a,b) for(TY i=(a);i<=(b);i=-~i)
#define fOR(i,a,b) for(TY i=(a);i<(b);i=-~i)
#define ROF(i,a,b) for(TY i=(a);i>=(b);i=~-i)
#define rOF(i,a,b) for(TY i=(a);i>(b);i=~-i)
using namespace std;
typedef long long ll;
const TY M=998244353,N=3600000;
typedef unsigned long long ull;
TY _abs(TY a){return a<0?-a:a;}
TY maxn(TY a,TY b){return a>b?a:b;}
TY minn(TY a,TY b){return a<b?a:b;}
void add(TY &x,TY y){if((x+=y)>=M)x-=M;}
TY gcd(TY a,TY b){return b?gcd(b,a%b):a;}
TY qp(TY a,TY b){TY ans=1;do{if(1&b)ans=ans*a%M;a=a*a%M;}while(b>>=1);return ans;}
char getc(){char ch=getchar();while(ch==' '||ch=='\n'||ch=='\r')ch=getchar();return ch;}
TY qr(){
	char ch=getchar();TY s=0,x=1;
	for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')x=-1;
	for(;ch>='0'&&ch<='9';ch=getchar())s=s*10+ch-'0';return x*s;
}void qw1(TY a){if(a>9)qw1(a/10);putchar(a%10+'0');}
void qw(TY a,char ch){
	if(a<0){a=-a;putchar('-');}
	if(a>9)qw1(a/10);putchar(a%10+'0');
	if(ch)putchar(ch);
}bitset<MAXM>dp[MAXN>>1];TY n,m,x,y,a[MAXN],vl;char s[5]="RUDL",ans[MAXN];
int main(){
	m=(n=qr())>>1;x=qr();y=qr();
	x+=y;y=x-(y<<1);x+=N;y+=N;
	if(x<0||x>=MAXM||y<0||y>=MAXM){printf("No");return 0;}
	dp[0][N]=1;FOR(i,1,n)a[i]=qr();
	FOR(i,1,m){
		dp[i]=dp[i-1]<<a[i];
		dp[i]|=(dp[i-1]>>a[i]);
	}dp[0]=dp[m];
	FOR(i,m+1,n){
		dp[i-m]=dp[i-m-1]<<a[i];
		dp[i-m]|=(dp[i-m-1]>>a[i]);
	}if(!dp[n-m][x]||!dp[n-m][y]){printf("No");return 0;}//跑一整遍，覆盖掉前一半的值
	rOF(i,n,m){vl=0;
		if(x>=a[i]&&dp[i-m-1][x-a[i]])x-=a[i];
		else{vl|=2;x+=a[i];}//从后往前遍历，记录决策，保持可行即可
		if(y>=a[i]&&dp[i-m-1][y-a[i]])y-=a[i];
		else{vl|=1;y+=a[i];}ans[i]=s[vl];
	}fOR(i,0,MAXM)dp[0][i]=0;dp[0][N]=1;//初始化后再跑出前一半的 dp
	FOR(i,1,m){
		dp[i]=dp[i-1]<<a[i];
		dp[i]|=(dp[i-1]>>a[i]);
	}ROF(i,m,1){vl=0;
		if(x>=a[i]&&dp[i-1][x-a[i]])x-=a[i];
		else{vl|=2;x+=a[i];}//同上，记录决策
		if(y>=a[i]&&dp[i-1][y-a[i]])y-=a[i];
		else{vl|=1;y+=a[i];}ans[i]=s[vl];
	}printf("Yes\n%s",ans+1);return 0;
}
```

---

## 作者：541forever (赞：1)

首先将两条坐标轴顺时针旋转 $45^\circ$，再将坐标轴缩短至原长度的 $1 \over \sqrt{2}$，则终点坐标变为 $(x-y,x+y)$，原本的向右变为 $(d,d)$，向上变为 $(-d,d)$，向左变为 $(-d,-d)$，向下变为 $(d,-d)$。

那么此时，我们可以发现，操作已经变成了可以对横纵坐标任意地 $\pm d$，这就意味着横纵坐标在这种操作下是独立的。此时问题就变成了一个简单的 01 背包问题：你每次可以给一个最初是 $0$ 的数加上或减去 $d_i$，问最后能否凑成一个数。本来直接 bitset 优化即可，但出题人神必地卡了一手空间，让你不能开 $n$ 个大小为 $2000 \times 1800 \times 2=7200000$，但开成大小是 $2000\times 1800=3600000$ 是可以的。我们接着又可以发现，设所有的 $d_i$ 和为 $s$，其实原问题还等价于每次选择加不加 $d_i$，最后能不能凑出 ${x+s}\over 2$，原因是设你如果能凑出，设你选出的要加的 $d_i$ 的和为 $s1$，则 $s1={x+s}\over 2$，则 $x=2s1-s$，而你实际选出（按有加有减算）的和为 $s1-(s-s1)=2s1-s$，实际上仍是等于 $x$ 的，这样就将空间缩小至原本的 $1 \over 2$ 了，可以通过本题。

[Code](https://atcoder.jp/contests/abc221/submissions/43023909)

---

## 作者：ghx0052 (赞：0)

# 思路

直接做显然不好做。

考虑转化：把坐标系顺时针旋转 $45$ 度，目标点坐标变为 $(\frac{X+Y}{2},\frac{Y-X}{2})$。

发现现在横纵坐标可以分别考虑，也就是说问题变为给你一个序列 $D_i$，求序列 $x_i\in \{1,-1\}$，使得：

$$\sum D_i\times x_i=w(w=\frac{X+Y}{2}{\div} \frac{Y-X}{2})$$

可以分开讨论。

再进行一个转化：设 $\sum D_i=S$，求出序列 $x_i$ 等价于在 $D_i$ 中选取若干个数，使得 $\sum x_i=\frac{S-w}{2}$。

这是一个经典的背包问题。

`bitset` 优化即可。

总结：解题需要精巧的思路，试错的胆量。

# 代码
```cpp
#include<bits/stdc++.h>
#define N (2001)
using namespace std;
int n,A,B,S,d[N],x[N],y[N];
bitset<3600010>f[N];
inline int read(){
	int w=0;
	char ch=getchar();
	while(ch>'9'||ch<'0') ch=getchar();
	while(ch>='0'&&ch<='9'){
		w=(w<<3)+(w<<1)+(ch^48);
		ch=getchar();
	}
	return w;
}
int main(){
	n=read();
	cin>>A>>B;
	f[0][0]=1;
	for(int i=1;i<=n;i++) S+=d[i]=read(),f[i]=((f[i-1]<<d[i])|f[i-1]);
	int S1=S-(A-B),S2=S-(A+B);
	if(S1<0||S2<0||(S1&1)||(S2)&1){puts("No");return 0;}
	if(S1>7200000||S2>7200000){puts("No");return 0;}
	if(!f[n][S1/2]||!f[n][S2/2]){puts("No");return 0;}
	S1>>=1,S2>>=1;
	for(int i=n;i>=1;i--){
		if(S1>=d[i]&&f[i-1][S1-d[i]]) S1-=d[i],x[i]=0;
		else x[i]=1;
		if(S2>=d[i]&&f[i-1][S2-d[i]]) S2-=d[i],y[i]=0;
		else y[i]=1;
	}
	puts("Yes");
	for(int i=1;i<=n;i++){
        //最后记得转回来
		if(x[i]&&y[i]) putchar('R');
		if(x[i]&&!y[i]) putchar('D');
		if(!x[i]&&y[i]) putchar('U');
		if(!x[i]&&!y[i]) putchar('L');
	}
	puts("");
	return 0;
}

```


---

