# [AGC018E] Sightseeing Plan

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc018/tasks/agc018_e

joisinoお姉ちゃんは、高橋町を観光する計画を立てています。 高橋町は、正方形の区画が東西南北に敷き詰められた形をしており、 西から $ x $ 番目、北から $ y $ 番目の区画を区画 $ (x,y) $ と呼ぶことにします。

joisinoお姉ちゃんは、以下の条件を満たす観光計画を、よい観光計画だと思っています。

- 観光を始める区画を区画 $ (p,q) $ としたときに、$ X_1\ \leq\ p\ \leq\ X_2 $ , $ Y_1\ \leq\ q\ \leq\ Y_2 $ を満たしている。
- お昼ごはんを食べる区画を区画 $ (s,t) $ としたときに、$ X_3\ \leq\ s\ \leq\ X_4 $ , $ Y_3\ \leq\ t\ \leq\ Y_4 $ を満たしている。
- 観光を終了する区画を区画 $ (u,v) $ としたときに、$ X_5\ \leq\ u\ \leq\ X_6 $ , $ Y_5\ \leq\ v\ \leq\ Y_6 $ を満たしている。
- 観光の開始地点から終了地点まで、お昼ごはんを食べる区画を通りながら、隣接する(辺を共有する)区画への移動を繰り返して、最短距離で移動している。

ある二つの観光計画は、観光を開始する区画、お昼ご飯を食べる区画、観光を終了する区画、または途中で訪れる区画が異なる時、異なる観光計画とみなされます。 joisinoお姉ちゃんは、よい観光計画が何通りあるかを知りたくなりました。 よい観光計画が何通りあるかを求めてください。 なお、答えは非常に大きくなることがあるので、$ 10^9+7 $ で割った余りを求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ X_1\ \leq\ X_2 $
- $ 1\ \leq\ Y_1\ \leq\ Y_2 $

### Sample Explanation 1

観光を開始する区画は必ず区画 $ (1,1) $ に、お昼ご飯を食べる区画は必ず区画 $ (2,2) $ になります。 観光を終了する区画が区画 $ (3,3) $ のとき、移動する方法は $ 4 $ 通りあります。 観光を終了する区画が区画 $ (4,3) $ のとき、移動する方法は $ 6 $ 通りあります。 よって、この例の答えは $ 6+4=10 $ 通りになります。

## 样例 #1

### 输入

```
1 1 2 2 3 4
1 1 2 2 3 3```

### 输出

```
10```

## 样例 #2

### 输入

```
1 2 3 4 5 6
1 2 3 4 5 6```

### 输出

```
2346```

## 样例 #3

### 输入

```
77523 89555 420588 604360 845669 973451
2743 188053 544330 647651 709337 988194```

### 输出

```
137477680```

# 题解

## 作者：枫林晚 (赞：28)

[戳我](https://www.cnblogs.com/Miracevin/p/9877493.html)

鸣谢：[AGC 018E.Sightseeing Plan(组合 DP)](https://www.cnblogs.com/SovietPower/p/9756236.html)

（大家看代码就看这个题解的代码吧，我就讲思路。）

本蒟蒻认为，本题堪称网格路径问题观止。

因为涵盖了不少网格路径问题的处理方法和思路。

 
# 一句话题意：

给你三个矩形。

三个矩形从左下到右上排开。矩形顶点坐标范围是1e6

 

    1≤X1≤X2<X3≤X4<X5≤X6≤10^6
    1≤Y1≤Y2<Y3≤Y4<Y5≤Y6≤10^6

 

大概就是这样：
![](https://cdn.luogu.com.cn/upload/pic/40804.png )
 

对于所有的1中选择一个点P1，2中选择一个点P2，3中选择一个点P3。

求从P1到P2再到P3的最短路径条数之和。

 

 

从一个矩形再到另外一个矩形还要经过一个矩形太复杂。我们化简情况处理下。

反正本质就是所有三个点之间的路径。

 
## 一、一个点到一个点

你必须要知道的：

从(x1,y1)到(x2,y2)的最短路径，就是只能往上或者往右走。

最短路径条数就是：C(x2-x1+y2-y1,x2-x1)

~~所以我们可以O(1000000^6)枚举~~

 
## 二、一个点到一个矩形

$F(x,y)$表示，从$(0,0)$到$(x,y)$的路径条数。

这个可以直接算。

发现，

$F(x,y)=\sum_{j=0}^yF(x-1,j)$

可以理解为，从原点到所有的$(x-1,j)$然后向上走一步，然后直接向右到达$(x,y)$

肯定不重不漏。

那么，可以得到：

从$(0,0)$到一个矩阵路径，就是：

$F(x2+1,y2+1)-F(x2+1,y1)-F(x1,y2+1)+F(x1,y1)$

就是一个小容斥。

用上面的$F(x,y)=\sum_{j=0}^yF(x-1,j)$

把$F(x2+1,y2+1)$还有$F(x1,y2+1)$展开消一消，

每次保留$F(x2+1,j)$和$F(x1,j)$往下消。

画画图就看出来了。

 

所以，我们得到了从一个点到一个矩阵的路径条数。

 

只要计算那四个点即可。

 

 
## 三、一个矩形到一个矩形

 

列出式子：

$G$示路径条数

$M_1$代表第一个矩形，$M_2$代表第二个矩形。

$\sum_{x1} \sum_{y1} \sum_{x2} \sum_{y2}G((x1,y1),(x2,y2))$


可以提出两个sigma

变成枚举一个点，求到另外一个矩形的方案数

$\sum_{x1} \sum_{y1}G((x1,y1),M_2)$

其实就是：

$\sum_{x1} \sum_{y1}\sum_{xx}\sum_{yy}(G((x1,y1),(xx,yy))$

$xx,yy$代表那四个关键点。（省略了四个关键点正负号）

反过来，每个关键点都会被$M_1$所有的点统计一次。

所以，一个关键点的贡献，就是这个关键点到$M_1$的路径条数。

就是这个关键点到$M_1$的四个关键点路径条数。（当然，要有正负号）

所以，一个矩形到一个矩形的路径条数，

就是两个矩形四个关键点分别进行条数计算。处理好符号即可。

 

 
## 四、一个矩形经过一个矩形再到另一个矩形

 

可以把三的结论推广。

就是，第一个矩形四个关键点，到第三个矩形四个关键点，然后路径上经过第二个矩形的方案数。

所以，$4\times 4$枚举第一第三个矩形的关键点的话，

问题就变成了从一个点出发，经过一个矩形再到另外一个点的方案数。

直接枚举还是$O(n^2)$的。


发现，经过第二个矩形，
必然要么从$(x,y3)$（下边界）要么从$(x3,y)$（左边界）
进入。

所以，我们枚举进入点。

进入这个点，就一定进入了这个矩形。再到终点的任意一条路径，都是合法的。

再乘上从起点到这个进入点的方案数就是这个进入点的贡献。

必然不重不漏地枚举完了所有的合法路径。

所以我们成功的A掉了这个题。

 
## 五、然鹅并没有做完。。。

 

发现，不是要求经过第二个矩形的路径条数啊，我们要在第二个矩形中选择一个点。。。。

一个经过第二个矩形的长度为$len$的路径，就对应着$len$个方案。（每个位置都可以作为$P_2$）


我们经常转化研究对象，尝试分开统计贡献。

分开统计的前提是，贡献必须可以处理成互不相关的形式。

这个可以不可以呢？

但是凉凉，这个$len$还和离开点有关。。。

难道只能$O(n^2)$枚举进入点和离开点？

不！我们还有方法！



一个$len$怎么计算？

进入点$(x1,y1)$,离开点$(x2,y2)$

有$len=x2-x1+y2-y1$

诶！！

$x1,x2,y1,y2$貌似可以分离！！

那么，我们可以枚举进入点。

贡献是：$(-1)\times$刚才的两个组合数$\times(x+y)$

离开点：

贡献是：$(+1)\times$刚才的两个组合数$\times(x+y)$

（其实这个也是不重不漏枚举了所有路径）

相加的话，

发现，对于每个合法的路径，恰好被计算了两遍。（进入离开点各一次）

第一遍把$-x1-y1$算上，

第二遍把$x2+y2$算上。

所以，每个合法路径贡献就是$len$次。和题意符合。

完结撒花！！！~~~

## 六、一些代码实现细节：

1.len的长度是：$(x2-x1+y2-y1+1)$别忘了$+1$

2.注意，矩阵矩阵的之间的路径，

根据推导，是先转化成$M_2$中关键点到$M_1$矩阵的路径，所以，$M_1$的矩阵的四个关键点分别是$(x1-1,y1-1),(x2,y1-1),(x1-1,y2),(x2,y2)$

类比之前，这个是从上往下走的，所以要这样处理。

 
```cpp
#include<bits/stdc++.h>
#define ri register int
using namespace std;
typedef long long ll;
const int mod=1e9+7;
const int N=2e6+3;
ll ans=0;
ll jie[N],ni[N];
struct node{
	int x,y,fl;
	void init(int a,int b,int c){
		x=a,y=b,fl=c;
	}
}p[20];
int tot;
int x3,y3,x4,y4;
int xx[10],yy[10];
ll qm(ll x,ll y){
	ll ret=1;
	while(y){
		if(y&1) ret=ret*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return ret;
}
ll C(int n,int m){
	return jie[n]*ni[m]%mod*ni[n-m]%mod;
} 
ll G(int x1,int y1,int x2,int y2){
	ll A=abs(x2-x1),B=abs(y2-y1);
	return C(A+B,B);
}
ll sol(int x1,int y1,int x2,int y2,int f1,int f2){
	ll ret=0;
	for(ri x=x3;x<=x4;++x){
		ret=(ret+G(x1,y1,x,y4)*G(x,y4+1,x2,y2)%mod*(x+y4+1))%mod;//注意这里的x+y4+1的+1 
		ret=(ret-G(x1,y1,x,y3-1)*G(x,y3,x2,y2)%mod*(x+y3)%mod+mod)%mod;
	}
	for(ri y=y3;y<=y4;++y){
		ret=(ret+G(x1,y1,x4,y)*G(x4+1,y,x2,y2)%mod*(x4+y+1))%mod; 
		ret=(ret-G(x1,y1,x3-1,y)*G(x3,y,x2,y2)%mod*(x3+y)%mod+mod)%mod;
	} 
	ret=ret*(f1*f2);
	
	return ret;
}
int main(){
	int x,y;
	for(ri i=1;i<=6;++i)scanf("%d",&xx[i]);
	for(ri i=1;i<=6;++i)scanf("%d",&yy[i]);
	jie[0]=1;
	for(ri i=1;i<=N-2;++i) jie[i]=jie[i-1]*i%mod;
	ni[N-2]=qm(jie[N-2],mod-2);
	for(ri i=N-3;i>=0;--i) ni[i]=ni[i+1]*(i+1)%mod;
	
	x3=xx[3],y3=yy[3],x4=xx[4],y4=yy[4];
	p[1].init(xx[1]-1,yy[1]-1,1);p[2].init(xx[2],yy[1]-1,-1);//注意这里是这样的 
	p[3].init(xx[1]-1,yy[2],-1);p[4].init(xx[2],yy[2],1);
	
	p[5].init(xx[5],yy[5],1);p[6].init(xx[6]+1,yy[5],-1);
	p[7].init(xx[5],yy[6]+1,-1);p[8].init(xx[6]+1,yy[6]+1,1);
	
	for(int i=1;i<=4;++i){
		for(int j=5;j<=8;++j){
			ans=(ans+sol(p[i].x,p[i].y,p[j].x,p[j].y,p[i].fl,p[j].fl)+mod)%mod;
		}  
	}
	printf("%lld",ans);
	return 0;
}

```
## 七、总结

我们成功地把一个O(n^6)变成了O(n)

思路就是化简问题，然后从简单到困难，利用之前的结论考虑，不断转化简化问题。

最后的差分len也是异常精彩。

组合数和路径条数的问题，经常是考虑一个物品的贡献。

可以尝试往这方面想。

 

---

## 作者：myee (赞：11)

### 前言

组合意义天地灭，代数推导保平安。

### 思路

答案显然即

$$\sum_{X_1\le x_1\le X_2}\sum_{X_3\le x_2\le X_4}\sum_{X_5\le x_3\le X_6}\sum_{Y_1\le y_1\le Y_2}\sum_{Y_3\le y_2\le Y_4}\sum_{Y_5\le y_3\le Y_6}\binom{x_2+y_2-x_1-y_1}{x_2-x_1}\binom{x_3+y_3-x_2-y_2}{x_3-x_2}$$

我们的目标就是优化其计算。

我们先考虑**代数推导**。

我们把对 $x_2,y_2$ 的和式挪到最外层，那么里面就是两个分别关于 $(x_1,y_1)$ 和 $(x_3,y_3)$ 的和式。

考虑分开来计算出封闭形式。

对于 $(x_1,y_1)$ 的求和，我们有

$$
\begin{aligned}
&\quad\sum_{X_1\le x_1\le X_2}\sum_{Y_1\le y_1\le Y_2}\binom{x_2+y_2-x_1-y_1}{x_2-x_1}
\cr&=\sum_{X_1\le x_1\le X_2}\binom{x_2+y_2-x_1-Y_1+1}{x_2-x_1+1}-\binom{x_2+y_2-x_1-Y_2}{x_2-x_1+1}
\cr&=\binom{x_2+y_2-X_1-Y_1+2}{x_2-X_1+1}-\binom{x_2+y_2-X_2-Y_1+1}{x_2-X_2}
\cr&\quad-\binom{x_2+y_2-X_1-Y_2+1}{x_2-X_1+1}+\binom{x_2+y_2-X_2-Y_2}{x_2-X_2}
\end{aligned}
$$

同样，对于 $(x_3,y_3)$ 的求和，我们有

$$
\begin{aligned}
&\quad\sum_{X_5\le x_3\le X_6}\sum_{Y_5\le y_3\le Y_6}\binom{x_3+y_3-x_2-y_2}{x_3-x_2}
\cr&=\sum_{X_5\le x_3\le X_6}\binom{x_3+Y_6-x_2-y_2+1}{x_3-x_2+1}-\binom{x_3+Y_5-x_2-y_2}{x_3-x_2+1}
\cr&=\binom{X_6+Y_6-x_2-y_2+2}{X_6-x_2+1}-\binom{X_5+Y_6-x_2-y_2+1}{X_5-x_2}
\cr&\quad-\binom{X_6+Y_5-x_2-y_2+1}{X_6-x_2+1}+\binom{X_5+Y_5-x_2-y_2}{X_5-x_2}
\end{aligned}
$$

然后我们只用计算 $16$ 种

$$\sum_{X_3\le x\le X_4}\sum_{Y_3\le y\le Y_4}\binom{x+y-A-B}{x-A}\binom{C+D-x-y}{C-x}$$

这种形式即可。

现在这个东西不方便直接做，考虑如何快速算。

注意到把阶乘展开，这是一个关于 $x+y$ 的卷积式，可以使用 MTT 做；不过由于要做 $16$ 轮，以及数据范围 $10^6$，再加上 MTT 的大常数，肯定是过不了的。

因此，我们考虑使用**组合意义**。

这个和式可以理解为从 $(A,B)\rightarrow(C,D)$ 的各种走法上经过矩形 $(X_3,X_4,Y_3,Y_4)$ 的节点数之和。

容斥一步，转化为从 $(0,0)\rightarrow(A,B)$ 的各种走法上经过矩形 $(0,X,0,Y)$ 的节点数之和，询问 $4$ 次。（$64$ 倍常数警告）

我们发现，直接枚举从边界何处其第一次离开矩形，即可做到 $O(X+Y)$ 的复杂度。

总复杂度 $O(wV)$，其中 $w=64$，来自于容斥（显然此处带来的常数差异不可忽略，故记入复杂度记号）；$V$ 表示值域。

### Code

核心代码实现得好会很短。

```cpp
const ullt Mod=1e9+7;
typedef ConstMod::mod_ullt<Mod>modint;
typedef std::vector<modint>modvec;
modint P[5000005],Q[5000005];
modint solve(uint X,uint Y,uint A,uint B){
    if(A<=X&&B<=Y)return P[A+B+1]*Q[A]*Q[B];
    modint ans;
    for(uint i=0;i<=X&&i<=A&&Y<B;i++)
        ans+=P[Y+i+1]*Q[Y]*Q[i]*P[A+B-Y-i-1]*Q[B-Y-1]*Q[A-i];
    for(uint i=0;i<=Y&&i<=B&&X<A;i++)
        ans+=P[X+i+1]*Q[X]*Q[i]*P[A+B-X-i-1]*Q[A-X-1]*Q[B-i];
    return ans;
}
int main()
{
#ifdef MYEE
    freopen("QAQ.in","r",stdin);
    // freopen("QAQ.out","w",stdout);
#endif
    P[0]=1;for(uint i=1;i<=5000000;i++)P[i]=P[i-1]*i;
    Q[5000000]=P[5000000].inv();for(uint i=5000000;i;i--)Q[i-1]=Q[i]*i;
    uint X1,X2,X3,X4,X5,X6,Y1,Y2,Y3,Y4,Y5,Y6;
    scanf("%u%u%u%u%u%u%u%u%u%u%u%u",&X1,&X2,&X3,&X4,&X5,&X6,&Y1,&Y2,&Y3,&Y4,&Y5,&Y6);
    modint ans;
    X1--,Y1--,X3--,Y3--,X6++,Y6++;
    for(uint i=0;i<16;i++){
        modint w;
        uint A=i&1?X1:X2,B=i&2?Y1:Y2,C=i&4?X5:X6,D=i&8?Y5:Y6;
        w+=solve(X4-A,Y4-B,C-A,D-B);
        w-=solve(X4-A,Y3-B,C-A,D-B);
        w-=solve(X3-A,Y4-B,C-A,D-B);
        w+=solve(X3-A,Y3-B,C-A,D-B);
        (__builtin_popcount(i)&1)?ans-=w:ans+=w;
    }
    ans.println();
    return 0;
}
```


---

## 作者：小粉兔 (赞：7)

在博客园食用更佳：[https://www.cnblogs.com/PinkRabbit/p/AGC018.html](https://www.cnblogs.com/PinkRabbit/p/AGC018.html)。

如果固定中转点。那么方案数就是每个起点到中转点，和每个终点到中转点，的方案数的乘积。

那么一个矩形的起点，到一个点，的方案数。其实就是杨辉三角上一个菱形的和。

其实就是四个点到一个点的方案数（但是系数是两个 $+1$ 两个 $-1$）。

那么现在就转化成 $4 \times 4 = 16$ 种情况的，起点和终点都是唯一的，但是中转点是在一个区域内的情况。

此时就相当于：对每个起点到终点的每条路径，把经过那个区域的长度求和。

此时又是一个很重要的转换：经过那个区域的长度转化成，离开那个区域时的坐标，减去进入那个区域时的坐标（曼哈顿距离）。

那么我们就可以枚举离开那个区域时的位置，求出满足的路径数，乘以曼哈顿坐标贡献给答案。

进入那个区域的情况同理。

预处理组合数，时间复杂度就是坐标范围。

```cpp
#include <cstdio>
#include <algorithm>

typedef long long LL;
const int Mod = 1000000007;
const int MV = 2000005;

inline int qPow(int b, int e) {
	int a = 1;
	for (; e; e >>= 1, b = (LL)b * b % Mod)
		if (e & 1) a = (LL)a * b % Mod;
	return a;
}
inline int gInv(int b) { return qPow(b, Mod - 2); }

int Fac[MV], iFac[MV];
inline void Init(int N) {
	Fac[0] = 1;
	for (int i = 1; i <= N; ++i) Fac[i] = (LL)Fac[i - 1] * i % Mod;
	iFac[N] = gInv(Fac[N]);
	for (int i = N; i >= 1; --i) iFac[i - 1] = (LL)iFac[i] * i % Mod;
}
inline int Binom(int N, int M) {
	if (M < 0 || M > N) return 0;
	return (LL)Fac[N] * iFac[M] % Mod * iFac[N - M] % Mod;
}
inline int Calc(int N, int M) {
	return Binom(N + M, N);
}

int X1, X2, X3, X4, X5, X6;
int Y1, Y2, Y3, Y4, Y5, Y6;

int sx[4], sy[4], tx[4], ty[4];
int Ans;

int main() {
	Init(2000000);
	scanf("%d%d%d%d%d%d", &X1, &X2, &X3, &X4, &X5, &X6);
	scanf("%d%d%d%d%d%d", &Y1, &Y2, &Y3, &Y4, &Y5, &Y6);
	sx[0] = X1 - 1, sy[0] = Y1 - 1;
	sx[1] = X1 - 1, sy[1] = Y2;
	sx[2] = X2, sy[2] = Y2;
	sx[3] = X2, sy[3] = Y1 - 1;
	tx[0] = X6 + 1, ty[0] = Y6 + 1;
	tx[1] = X6 + 1, ty[1] = Y5;
	tx[2] = X5, ty[2] = Y5;
	tx[3] = X5, ty[3] = Y6 + 1;
	for (int sk = 0; sk < 4; ++sk) {
		for (int tk = 0; tk < 4; ++tk) {
			int spx = sx[sk], spy = sy[sk];
			int tpx = tx[tk], tpy = ty[tk];
			int coef = (sk ^ tk) & 1 ? -1 : 1;
			int Sum = 0;
			for (int i = X3; i <= X4; ++i) {
				Sum = (Sum + (LL)Calc(i - spx, Y3 - 1 - spy) * Calc(tpx - i, tpy - Y3) % Mod * -(i + Y3 - 1)) % Mod;
				Sum = (Sum + (LL)Calc(i - spx, Y4 - spy) * Calc(tpx - i, tpy - Y4 - 1) % Mod * (i + Y4)) % Mod;
			}
			for (int j = Y3; j <= Y4; ++j) {
				Sum = (Sum + (LL)Calc(X3 - 1 - spx, j - spy) * Calc(tpx - X3, tpy - j) % Mod * -(X3 - 1 + j)) % Mod;
				Sum = (Sum + (LL)Calc(X4 - spx, j - spy) * Calc(tpx - X4 - 1, tpy - j) % Mod * (X4 + j)) % Mod;
			}
			Ans = (Ans + coef * Sum) % Mod;
		}
	}
	printf("%d\n", (Ans + Mod) % Mod);
	return 0;
}
```

---

## 作者：Idtwtei (赞：3)

> 网格图上有三个矩形
> 
> $$
> A:(x_1,y_1)-(x_2,y_2),B:(x_3,y_3)-(x_4,y_4),C:(x_5,y_5)-(x_6,y_6)
> $$
> 
> 求 $a \to b \to c(a \in A,b \in B,c \in C)$ 的方案数。
> 
> 其中 $a \to b$ 表示 $a$ 向下向右走到 $b$ 的路径。两个方案不同当且仅当 $a,b,c$ 不同，或 $a \to b,b \to c$ 不同。
> 
> $1 \le x_1 \le x_2 < x_3 \le x_4 < x_5 \le x_6 \le 10^6,1 \le y_1 \le y_2 < y_3​ \le y_4 < y_5 \le y_6 \le 10^6$。

考虑枚举中间节点 $b$，需要计算的是一个点到一个矩形的方案数。将矩形差分，只需要计算点 $(0,0)$ 到矩形 $(0,0)-(x,y)$ 的方案数。


$$
\begin{aligned}
\sum_{i=0}^{x} \sum_{j=0}^{y} \binom{i+j}{i} &= \sum_{i=0}^{x} \binom{y+i+1}{i+1} \\
&= \sum_{i=-1}^{x} \binom{y+i+1}{y} - \binom{y}{y} \\
&= \binom{x+y+2}{y+1} - 1
\end{aligned}
$$

差分的四项求和之后 $-1$ 就被消去了，而 $\binom{x+y+2}{y+1}$ 恰为 $(0,0) \to (x+1,y+1)$ 的方案数。记 $a \to b$ 表示 $a$ 到 $b$ 路径的方案数，那么 $b$ 到 $A$ 的方案数为

$$
b \to (x_1-1,y_1-1) + b \to (x_2,y_2) - b \to (x_1-1,y_2) - b \to (x_2,y_1-1)
$$

$b$ 到 $C$ 的方案数类似，得到了 $O(n^2)$ 的做法。 

通过差分相当于将 $A,B$ 分别转化为 $4$ 个点，而枚举 $4 \times 4$ 个点对是可以接受的，考虑枚举起点 $a$ 和终点 $c$，此时对答案贡献的系数为两个点对应系数的乘积。

一条 $a \to c$ 的路径产生的方案数为路径与 $B$ 的交点个数（每个交点都可以充当 $b$）。可以枚举路径进入和离开 $B$ 的点计算方案数，但这样仍是 $O(n^2)$ 的。若矩形包含 $a$ 那就不用枚举进入的点了。继续差分，将 $B$ 差分为四个以 $a$ 为左上角的矩形。枚举路径离开矩形的点计算方案数即可。

时间复杂度 $O(n)$，带一个比较大的常数。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define ar(x) array<int,x>
#define pb push_back
const int N=2e6+100,MOD=1e9+7;
inline int qm(int x,int y=MOD-2){ int res=1; for(;y;y>>=1,x=1ll*x*x%MOD) if(y&1) res=1ll*res*x%MOD; return res; }
inline void mod(int &x){ if(x>=MOD) x-=MOD; if(x<0) x+=MOD; }
#define gc getchar()
#define rd read()
inline int read(){
    int x=0,f=0; char c=gc;
    for(;c<'0'||c>'9';c=gc) f|=(c=='-');
    for(;c>='0'&&c<='9';c=gc) x=(x<<1)+(x<<3)+(c^48);
    return f?-x:x;
}

int jc[N],fjc[N];
void init(int n){
    jc[0]=1; for(int i=1;i<=n;++i) jc[i]=1ll*jc[i-1]*i%MOD;
    fjc[n]=qm(jc[n]); for(int i=n-1;~i;--i) fjc[i]=1ll*fjc[i+1]*(i+1)%MOD;
}
inline int CM(int n,int m){ return n<0||m<0||m>n?0:1ll*jc[n]*fjc[m]%MOD*fjc[n-m]%MOD; }
inline int calc(int x_1,int y_1,int x_2,int y_2){ return CM(abs(x_2-x_1)+abs(y_2-y_1),abs(x_2-x_1)); }

int x[7],y[7],ans=0;
vector<ar(3)> A,B,C;

void sol(ar(3) a,ar(3) b,ar(3) c){
    int res=0;
    for(int i=a[1];i<=b[1];++i) mod(res+=1ll*calc(b[0],i,a[0],a[1])*calc(b[0]+1,i,c[0],c[1])%MOD*(b[0]-a[0]+i-a[1]+1)%MOD);
    for(int i=a[0];i<=b[0];++i) mod(res+=1ll*calc(i,b[1],a[0],a[1])*calc(i,b[1]+1,c[0],c[1])%MOD*(i-a[0]+b[1]-a[1]+1)%MOD);
    mod(ans+=a[2]*b[2]*c[2]*res);
}

int main(){

    init(N-1);

    for(int i=1;i<=6;++i) x[i]=rd;
    for(int i=1;i<=6;++i) y[i]=rd;

    A.pb({x[2],y[2],1}),A.pb({x[1]-1,y[1]-1,1}),A.pb({x[2],y[1]-1,-1}),A.pb({x[1]-1,y[2],-1});
    B.pb({x[4],y[4],1}),B.pb({x[3]-1,y[3]-1,1}),B.pb({x[4],y[3]-1,-1}),B.pb({x[3]-1,y[4],-1});
    C.pb({x[6]+1,y[6]+1,1}),C.pb({x[5],y[5],1}),C.pb({x[6]+1,y[5],-1}),C.pb({x[5],y[6]+1,-1});

    for(auto a:A) for(auto b:B) for(auto c:C) sol(a,b,c);

    printf("%d\n", ans);

    return 0;
}
```

---

## 作者：Argon_Cube (赞：2)

本题解会给最后一步提供一个不一样的组合意义。

通过简单的差分和组合意义推导，可以发现我们需要计算 $32$ 个如下的式子：

$$\sum_{i=l}^{r}f(n+i,a,b,i)$$

其中

$$f(n,a,b,i)=\sum_{j=0}^{n}\binom{j}{i}\binom{a-j}{b-i}$$

这是 Vandermonde 卷积的部分和，我们不能期望它有简单的封闭形式。使用莫队解决组合数前缀和的经验告诉我们可以考虑暴力计算 $f(l+i,a,b,l)$ 并尝试从 $f(n-1,a,b,i-1)$ 推出 $f(n,a,b,i)$，这样就可以线性的解决原问题。

考虑 $f(n,a,b,i)$ 的组合意义：在 $a+1$ 个方块中选择 $b+1$ 个方块，且第 $i+1$ 个被选中的方块必须在前 $n+1$ 个方块中。注意到 $f(n,a,b,i)$ 所计算的方案对于 $f(n,a,b,i-1)$ 也同样是合法的，而对 $f(n,a,b,i-1)$ 合法的方案对于 $f(n,a,b,i)$ 不合法当且仅当第 $i$ 个被选中的方块在前 $n+1$ 个方块中且第 $i+1$ 个被选中的方块不在其中。于是前 $n+1$ 个方块中恰好有 $i$ 个被选中了：

$$f(n,a,b,i)=f(n,a,b,i-1)-\binom{n+1}{i}\binom{a-n}{b+1-i}$$

从 $f(n-1,a,b,i)$ 推出 $f(n,a,b,i)$ 是显然的，这样我们就解决了原问题。

---

## 作者：critnos (赞：2)

考虑路径第一次和最后一次进入中间的那个矩形的在边界上的位置。记 $P(u,v)$ 表示从点 $u$ 走到点 $v$ 的方案数，那么比如我从左边进入了 $(a,b)$ 然后走到 $(c,d)$ 从上面出去，方案数就是 $P(S,(a-1,b))P((a,b),(c,d))P((c,d+1),T)(c-a+d-b+1)$，最后那个表示中间点的数量。

那么只需要求出边界旁边的点到另外两个矩形的方案数，即

$$\sum_{i=p_1}^{p_2}\sum_{j=q_1}^{q_2}C(i+j,i)$$

直接上指标求和就是

$$C(p_2+q_2+2,q_2+1)-C(p_1+q_2+1,q_2+1)-C(p_2+q_1+1,q_1)+C(p_1+q_1,q_1)$$

对边界旁边的每个点求之。

那中间的走法就是从左边进上面出/下右/下上/左右。把组合数拆掉，其中左上和下右是和卷积，下上和左右是差卷积，直接任意模数即可 $O(v\log v)$。

https://atcoder.jp/contests/agc018/submissions/48014040

---

## 作者：whiteqwq (赞：2)

[AT2674 [AGC018E] Sightseeing Plan](https://www.luogu.com.cn/problem/AT2674)解题报告：

[更好的阅读体验](https://zybuluo.com/xiaoziyao/note/1776382)

## 题意
- 给定$6$个点$(x_1,y_1)\cdots(x_6,y_6)$。
- 从矩形$(x_1,y_1)-(x_2,y_2)$中某个点出发，在矩形$(x_3,y_3)-(x_4,y_4)$中某个点休息，然后在矩形$(x_5,y_5)-(x_6,y_6)$中某个点结束，每一步行走都只能向上或向右。
- 求一共有多少不同的方案（只要经过的点集不同就算作不同方案），对$10^9+7$取模。
- 数据范围：$1\leqslant x_1\cdots x_6,y_1\cdots y_6\leqslant 10^6$。

## 分析
神仙题，下面分步进行说明：
### 点到点
点到点很简单，考虑两个点之间的横纵坐标之差$\Delta x,\Delta y$，发现一共有$\Delta x+\Delta y$步，可以选择$\Delta x$步向右，因此方案数为$\frac{(\Delta x+\Delta y)!}{\Delta x!\Delta y!}$。
```
inline int G(int a,int b,int c,int d){
	return 1ll*fac[abs(a-c)+abs(b-d)]*nfac[abs(a-c)]%mod*nfac[abs(b-d)]%mod;
}
```
下面设两个点$(a,b)$与$(c,d)$的距离为$G(a,b,c,d)$。

### 点到矩形/矩形到点
考虑点$(x,y)$到矩形$(a,b)-(c,d)$的方案数，但是直接算$\sum_{i=a}^b\sum_{j=c}^d G(x,y,i,j)$的复杂度太高了，考虑简单地容斥一下就会得到方案数为$G(x,y,c+1,d+1)-G(x,y,a,d+1)-G(x,y,c+1,b)+G(x,y,a,b)$。

矩形到点的方案数是一样的。

### 矩形到矩形

考虑先把一个矩形转化为四个点，然后再枚举那四个点把另一个矩形转化为四个点，然后照上面做就好了。（貌似和这道题没有关系）

### 本题要求

本题要求：从矩形$(x_1,y_1)-(x_2,y_2)$中某个点出发，在矩形$(x_3,y_3)-(x_4,y_4)$中某个点休息，然后在矩形$(x_5,y_5)-(x_6,y_6)$中某个点结束。

考虑枚举进入$(x_3,y_3)-(x_4,y_4)$的点$(i_1,j_1)$（也就是这个矩形左/下边缘上的点）与离开矩形的点$(i_2,j_2)$（也就是这个矩形右/上边缘的点），计算方案就枚举第一个矩形的四个关键点和第三个矩形的四个关键点，然后计算关键点与进入点，进入点与离开点，离开点与另一个关键点的方案，乘上进入点到离开点的路径长度（要在这条路径上选择一个点停留），再乘上容斥系数，这样的复杂度是$O(n^2)$的。

考虑分离进入点和离开点的贡献，不难发现关键点到进入点和进入点到离开点的方案数（或者进入点到离开点和离开点到关键点的方案数）是可以合并计算的，而进入点到离开点的路径长度为$(i_2-i_1+j_2-j_1+1)$，我们很显然可以分离这两个部分的贡献。

然后暴力枚举边缘上的点并进行统计就好了，时间复杂度：$O(n)$。

## 代码
细节很多，同时提供一个较短的代码：
```
#include<stdio.h>
const int maxn=2000005,mod=1000000007,maxx=2000000;
int X1,X2,X3,X4,X5,X6,Y1,Y2,Y3,Y4,Y5,Y6,ans;
int fac[maxn],nfac[maxn],inv[maxn],xx[9],yy[9],zz[9];
inline void set(int p,int x,int y,int z){
	xx[p]=x,yy[p]=y,zz[p]=z;
}
inline int abs(int x){
	return x<0? -x:x;
}
inline int G(int a,int b,int c,int d){//点到点
	return 1ll*fac[abs(a-c)+abs(b-d)]*nfac[abs(a-c)]%mod*nfac[abs(b-d)]%mod;
}
int calc(int sx,int sy,int x1,int y1,int x2,int y2,int tx,int ty,int f){//(s1,s2)->(x1,y1,x2,y2)->(tx,ty)
	int res=0;
	for(int i=x1;i<=x2;i++)//枚举矩形下边界/上边界
		res=(res-1ll*G(sx,sy,i,y1-1)*G(i,y1,tx,ty)%mod*(i+y1)%mod+1ll*G(sx,sy,i,y2)*G(i,y2+1,tx,ty)%mod*(i+y2+1)%mod)%mod;//减去的是下边界，加上的是上边界
	for(int i=y1;i<=y2;i++)//枚举矩形左边界/右边界
		res=(res-1ll*G(sx,sy,x1-1,i)*G(x1,i,tx,ty)%mod*(x1+i)%mod+1ll*G(sx,sy,x2,i)*G(x2+1,i,tx,ty)%mod*(x2+i+1)%mod)%mod;//减去的是左边界，加上的是右边界
	return (res*f+mod)%mod;//乘上容斥系数f
}
int main(){
	fac[0]=nfac[0]=1;
	for(int i=1;i<=maxx;i++){
		inv[i]=i==1? 1:(mod-1ll*(mod/i)*inv[mod%i]%mod);
		fac[i]=1ll*fac[i-1]*i%mod,nfac[i]=1ll*nfac[i-1]*inv[i]%mod;
	}
	scanf("%d%d%d%d%d%d%d%d%d%d%d%d",&X1,&X2,&X3,&X4,&X5,&X6,&Y1,&Y2,&Y3,&Y4,&Y5,&Y6);
	set(1,X1-1,Y1-1,1),set(2,X1-1,Y2,-1),set(3,X2,Y1-1,-1),set(4,X2,Y2,1);//设置第一个矩形关键点的位置
	set(5,X5,Y5,1),set(6,X5,Y6+1,-1),set(7,X6+1,Y5,-1),set(8,X6+1,Y6+1,1);//设置第三个矩形关键点的位置
	for(int i=1;i<=4;i++)
		for(int j=5;j<=8;j++)
			ans=(ans+calc(xx[i],yy[i],X3,Y3,X4,Y4,xx[j],yy[j],zz[i]*zz[j]))%mod;
	printf("%d\n",(ans+mod)%mod);
	return 0;
}
```

---

## 作者：0xyz (赞：1)

很明显，$P\to Q$ 一共 $\pi(P,Q)=C_{x_Q-x_P+y_Q-y_P}^{x_Q-x_P}$ 种走法。

假设 $v$ 是坐标范围，暴力算答案是 $O(v^6)$ 的，考虑优化。

我们枚举中间矩形的休息点 $P(x,y)$，那么我们考虑左下矩形中任意一个点 $S$，以及右上矩形中任意一个点 $T$，容易知道 $S$ 的贡献 $s(x,y)$ 与 $T$ 的贡献 $t(x,y)$ 无关，所以分开来考虑，然后相乘得到 $ans(x,y)$。

我们看一下左下矩形所有点对 $P$ 的贡献：

$$s(x,y)=\sum\limits_{i=x_1}\limits^{x_2}\sum\limits_{j=y_1}\limits^{y_2}C_{x-i+y-j}^{x-i}=\sum\limits_{i=x-x_2}\limits^{x-x_1}\sum\limits_{j=y-y_2}\limits^{y-y_1}C_{i+j}^{i}$$

不太好算，拆成四个，假设

$$\begin{aligned}S(u,v)&=\sum\limits_{i=0}\limits^{u}\sum\limits_{j=0}\limits^{v}C_{i+j}^{i}\\&=\sum\limits_{i=0}\limits^{u}\sum\limits_{j=0}\limits^{v}(C_{i+j+1}^{i+1}-C_{i+j}^{i+1})\\&=\sum\limits_{i=0}\limits^{u}C_{i+v+1}^{i+1}\\&=\sum\limits_{i=0}\limits^{u}(C_{i+v+2}^{i+2}-C_{i+v+1}^{i+2})\\&=C_{u+v+2}^{u+1}-1\end{aligned}$$

那么答案就变为

$$\begin{aligned}s(x,y)&=S(x-x_1,y-y_1)-S(x-x_2-1,y-y_1)-S(x-x_1,y-y_2-1)+S(x-x_2-1,y-y_2-1)\\&=C_{x-x_1+1+y-y_1+1}^{x-x_1+1}-C_{x-x_2+y-y_1+1}^{x-x_2}-C_{x-x_1+1+y-y_2}^{x-x_1+1}+C_{x-x_2+y-y_2}^{x-x_2}\end{aligned}$$

就相当于 $S_0(x_2,y_2),S_1(x_2,y_1-1),S_2(x_1-1,y_2),S_3(x_1-1,y_1-1)$ 这 $4$ 个点到 $P$ 的不同路径条数的带权和。

对于右上角矩阵的做法也同理，然后 $ans(x,y)=s(x,y)\times t(x,y)$。

这样的做法是 $O(v^2)$ 的，还是太慢了。

因为我们已经将左下、右上矩阵转各换成了 $4$ 个点，所以每个 $P$ 对应的答案会是 $16$ 个数的带权和。

固定 $p,q\in\{0,1,2,3\}$，我们尝试求出

$$cal(p,q)=\sum\limits_{i=x_3}\limits^{x_4}\sum\limits_{j=y_3}\limits^{y_4}\pi(S_p,(i,j))\times\pi((i,j),T_q)$$

我们知道 $S_p$ 出发的路径一定从中间矩形的左边或者下边进入，从右边或上边离开。枚举第一次进入中间矩形的位置 $O_S(a,b)$ 和离开的位置 $O_T(c,d)$，那么每一条这样的路径都经过中间矩形的 $c+d-a-b+1$ 个点。但是这样暴算还是不行，我们考虑拆成 $c+d+1$ 减去 $a+b$，统计对应代数式出现次数，也就是经过对应点的路径数。

$$\begin{aligned}cal(p,q)&=\sum\limits_{i=x_3}\limits^{x_4}\pi(S_p,(i,y_4))\times\pi((i,y_4+1),T_q)\times(i+y_4+1)\\&+\sum\limits_{i=y_3}\limits^{y_4}\pi(S_p,(x_4,i))\times\pi((x_4+1,i),T_q)\times(x_4+i+1)\\&-\sum\limits_{i=x_3}\limits^{x_4}\pi(S_p,(i,y_3-1))\times\pi((i,y_3),T_q)\times(i+y_3)\\&-\sum\limits_{i=y_3}\limits^{y_4}\pi(S_p,(x_3-1,i))\times\pi((x_3,i),T_q)\times(x_3+i)\end{aligned}$$

所以我们预处理出阶乘和阶乘的逆元，然后枚举 $p,q$，最后再用上面的式子算出 $cal(p,q)$，再加权计算和。总时间复杂度和空间复杂度都是 $O(v)$。

```cpp
#include<bits/stdc++.h>
#define R(i,x,y) for(ll i=x;i<=y;i++)
using namespace std;
typedef long long ll;
const ll M=1e9+7,z=2e6;
struct pt{ll x,y;}s[4],t[4];
ll p[z+1],q[z+1],x[7],y[7],ans;
inline ll P(pt s,pt t){
	return p[t.x+t.y-s.x-s.y]*q[t.x-s.x]%M*q[t.y-s.y]%M;
}
inline ll cal(pt s,pt t){
	ll rs=0;
	R(i,x[3],x[4])rs=(rs+P(s,{i,y[4]})*P({i,y[4]+1},t)%M*(i+y[4]+1))%M;
	R(i,x[3],x[4])rs=(rs+M-P(s,{i,y[3]-1})*P({i,y[3]},t)%M*(i+y[3])%M)%M;
	R(i,y[3],y[4])rs=(rs+P(s,{x[4],i})*P({x[4]+1,i},t)%M*(x[4]+i+1))%M;
	R(i,y[3],y[4])rs=(rs+M-P(s,{x[3]-1,i})*P({x[3],i},t)%M*(x[3]+i)%M)%M;
	return rs;
}
int main(){
	p[0]=q[z]=1;
	R(i,1,z)p[i]=p[i-1]*i%M;
	for(ll i=M-2,j=p[z];i;i>>=1,j=j*j%M)
		if(i&1)q[z]=q[z]*j%M;
	for(ll i=z;i;i--)q[i-1]=q[i]*i%M;
	R(i,1,6)cin>>x[i];
	R(i,1,6)cin>>y[i];
	R(i,0,3)s[i]={x[2-i/2]-i/2,y[2-i%2]-i%2};
	R(i,0,3)t[i]={x[5+i/2]+i/2,y[5+i%2]+i%2};
	R(i,0,3)R(j,0,3)ans=(ans+M+((!i||i>2)^(!j||j>2)?-1:1)*cal(s[i],t[j]))%M;
	cout<<ans<<'\n'; 
	return 0;
}
```

---

## 作者：Unnamed114514 (赞：0)

## 题意

给你三个矩形，前一个矩形在后一个矩形的左下方，现在让你从三个矩形中各取一个点，求第一个点经过第二个点到第三个点的方案数。（只能向右或向上走）

## 格点计数

显然我们可以平移坐标系把起点移到原点，所以我们只需要讨论起点是原点的情况。

- 点到点（$(0,0)\to (x,y)$）：

容易发现我们要向右走 $x$ 步，向上走 $y$ 步，那么我们一共走 $x+y$ 步，从这几步里面选 $x$ 步向右走即可，方案数即 ${x+y\choose x}$。

- 点到矩形（$(0,0)\to A[(x_1,y_1)\to(x_2,y_2)]$）：

考虑差分，那么我们就只需要求 $f(x,y)$ 表示 $(0,0)\to B[(0,0)\to(x,y)]$ 即可。

首先，考虑 $\sum\limits_{i=k}^n{i\choose k}={n+1\choose k+1}$。证明的话考虑归纳，显然 ${k\choose k}={k+1\choose k+1}$ 成立，当 $n\to n+1$ 时，有 $\sum\limits_{i=k}^{n+1}{i\choose k}=(\sum\limits_{i=k}^n{i\choose k})+{n+1\choose k}={n+1\choose k+1}+{n+1\choose k}={n+2\choose k+1}$，得证。

那么对于 $f$，我们大力推式子，有：

$f(x,y)=\sum\limits_{i=0}^{x}\sum\limits_{j=0}^y{i+j\choose i}=\sum\limits_{i=0}^x{i+y+1\choose i+1}=\sum\limits_{i=0}^x{i+y+1\choose y}=\sum\limits_{i=0}^{x+1}{i+y\choose y}-{y\choose y}={x+y+2\choose x+1}-1$

容易发现差分是两加两减，所以其实我们不妨令 $f(x,y)={x+y+2\choose x+1}$，那么我们就能得到它的组合意义是 $(0,0)\to (x+1,y+1)$ 了。

## 题解

根据上述推导，我们已经可以把 $A,C$ 转化成分别四个点（$a_1,a_2,a_3,a_4,c_1,c_2,c_3,c_4$，注意符号）来求解了，但是 $B$ 中的点不同我们也会算成不同的方案，所以我们会不可避免地枚举 $B$ 中的点，然后就得到 $O(n^2)$ 了。

转化一下问题，你会发现其实它等价于 $a_{\_},c_{\_}$ 的所有路径和 $B$ 的交集的点数和，因此我们只需要枚举进出 $B$ 的点即可，但是时间复杂度仍然是 $O(n^2)$。

手玩一下，可以发现对 $B$ 差分以后，一条路径的贡献不变，因此考虑把 $B$ 差分，这样的话，$a_{\_}$ 就到 $B$ 的内部去了，然后就不用枚举入点只需要枚举出点即可，时间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;
const int mod=1e9+7,N=2e6+5;
int x_1,x_2,x_3,x_4,x_5,x_6,y_1,y_2,y_3,y_4,y_5,y_6,fac[N],inv[N];
struct NODE{ int x,y,op; };
vector<NODE> a,c;
int qpow(int a,int b){
	int s=1;
	while(b){
		if(b&1) s=s*a%mod;
		a=a*a%mod,b>>=1;
	}
	return s;
}
int C(int n,int m){  return fac[n]*inv[m]%mod*inv[n-m]%mod; }
int f(int x,int y,int x_1,int y_1,int x_2,int y_2){
	x_1-=x,x_2-=x;
	y_1-=y,y_2-=y;
	x_1=abs(x_1),x_2=abs(x_2),y_1=abs(y_1),y_2=abs(y_2);
	return ((C(x_2+y_2+2,x_2+1)-C(x_2+y_1+1,x_2+1)-C(x_1+y_2+1,y_2+1)+C(x_1+y_1,x_1))%mod+mod)%mod;
}
int g(int x,int y,int x_1,int y_1,int x_2,int y_2){
	int ans=0;
	for(int i=x_1;i<=x;++i) ans=(ans+C((x_2-i)+(y_2-(y+1)),x_2-i)*C((i-x_1)+(y-y_1),i-x_1)%mod*((i-x_1)+(y-y_1)+1))%mod;
	for(int i=y_1;i<=y;++i) ans=(ans+C((x_2-(x+1))+(y_2-i),y_2-i)*C((x-x_1)+(i-y_1),x-x_1)%mod*((x-x_1)+(i-y_1)+1))%mod;
	return ans;
}
int solve(int sx,int sy,int tx,int ty){ return ((g(x_4,y_4,sx,sy,tx,ty)-g(x_4,y_3-1,sx,sy,tx,ty)-g(x_3-1,y_4,sx,sy,tx,ty)+g(x_3-1,y_3-1,sx,sy,tx,ty))%mod+mod)%mod; }
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>x_1>>x_2>>x_3>>x_4>>x_5>>x_6>>y_1>>y_2>>y_3>>y_4>>y_5>>y_6;
	a.emplace_back(NODE({x_1-1,y_1-1,1}));
	a.emplace_back(NODE({x_2,y_1-1,mod-1}));
	a.emplace_back(NODE({x_1-1,y_2,mod-1}));
	a.emplace_back(NODE({x_2,y_2,1}));
	c.emplace_back(NODE({x_5,y_5,1}));
	c.emplace_back(NODE({x_6+1,y_5,mod-1}));
	c.emplace_back(NODE({x_5,y_6+1,mod-1}));
	c.emplace_back(NODE({x_6+1,y_6+1,1}));
	fac[0]=1;
	for(int i=1;i<=2000000;++i) fac[i]=fac[i-1]*i%mod;
	inv[2000000]=qpow(fac[2000000],mod-2);
	for(int i=1999999;~i;--i) inv[i]=inv[i+1]*(i+1)%mod;
	int ans=0;
	for(auto s:a) for(auto t:c) ans=(ans+s.op*t.op%mod*solve(s.x,s.y,t.x,t.y))%mod;
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：lalaouye (赞：0)

计数好题。

要做出这道题首先考虑更简单的问题，只规定起点矩阵和终点矩阵怎么做？有点困难，没关系，我们可以先考虑求一个点到一个矩阵的路径数，不妨设起点为 $(0,0)$，矩阵显然是可以差分的，这样我们就只需要求 $f(x,y)=\sum_{i=0}^x\sum_{j=0}^y\binom{i+j}{i}$ 了。

有两种方法求，一种是考虑一个递推关系，这种东西一看就是有递推关系的对吧？那么我们考虑令 $g(x,y)$ 为到它的路径数，那么，$g(x,y)=\sum_{j=0}^yg(x-1,j)$。这是显然的，它有什么用呢？它可以代替前面一整列的贡献。那么对于 $f(x,y)$，我们发现 $g(x+1,y+1)$ 恰好可以将贡献一一对应的算出来，真是神奇！

还有一种更有一般性的方法，就是直接推组合数。考虑式子的形式，我们不妨将 $\binom{i+j}{i}$ 变为 $\binom {i+j} j$，于是 

$$\begin{align}f(x,y)&=\sum_{i=0}^x\sum_{j=0}^y\binom{i+j+1}{j+1}-\binom{i+j}{j+1}\\&=\sum_{j=0}^{y+1}\binom{x+j}{x}\\&=\sum_{j=0}^{y+1}\binom{x+j+1}{j+1}-\binom{x+j}{j+1}\\&=\binom{x+y+2}{x+1}\\&=g(x+1,y+1) \end{align}$$

主要利用了拆组合数抵消邻项的思想。

那么我们会了点到矩形之后，发现我们已经可以枚举中间矩形的轮廓，但是我们发现不同的 $P$ 会使得相同的路径多算，那么一条路径的权值相当于经过的点数，然而我们发现经过的点数等于进出的两个点的曼哈顿距离，这样就可以拆开算了。

代码：


```cpp
#include <bits/stdc++.h>
#define int long long
#define rep(i, l, r) for (int i (l); i <= r; ++ i)
#define rrp(i, l, r) for (int i (r); i >= l; -- i)
#define eb emplace_back
using namespace std;
#define pii pair <int, int>
#define inf 1000000000
constexpr int N = 2e6 + 5, M = 1e5, P = 1e9 + 7;
typedef long long ll;
typedef unsigned long long ull;
inline int rd () {
  int x = 0, f = 1;
  char ch = getchar ();
  while (! isdigit (ch)) {
    if (ch == '-') f = -1;
    ch = getchar ();
  }
  while (isdigit (ch)) {
    x = (x << 1) + (x << 3) + (ch ^ 48);
    ch = getchar ();
  }
  return x * f;
}
int qpow (int x, int y, int p = P) {
  int ret (1);
  for (; y; y >>= 1, x = x * x % p) if (y & 1) ret = ret * x % p;
  return ret;
}
int x[7], y[7];
int fac[N], ifac[N];
int C (int n, int m) {
  if (m > n) return 0;
  return fac[n] * ifac[m] % P * ifac[n - m] % P;
}
int calc (int X1, int Y1, int X2, int Y2) {
  return C (X2 - X1 + Y2 - Y1, X2 - X1);
}
int pre (int X, int Y) {
  return (calc (x[1] - 1, y[1] - 1, X, Y)
     - calc (x[2], y[1] - 1, X, Y)
     - calc (x[1] - 1, y[2], X, Y)
     + calc (x[2], y[2], X, Y) + P + P) % P;
}
int suf (int X, int Y) {
  return (calc (X, Y, x[6] + 1, y[6] + 1)
     - calc (X, Y, x[5], y[6] + 1)
     - calc (X, Y, x[6] + 1, y[5])
     + calc (X, Y, x[5], y[5]) + P + P) % P;
}
int32_t main () {
  // freopen ("1.in", "r", stdin);
  // freopen ("1.out", "w", stdout);
  fac[0] = 1;
  rep (i, 1, N - 1) fac[i] = fac[i - 1] * i % P;
  ifac[N - 1] = qpow (fac[N - 1], P - 2);
  rrp (i, 1, N - 1) ifac[i - 1] = ifac[i] * i % P;
  rep (i, 1, 6) x[i] = rd ();
  rep (i, 1, 6) y[i] = rd ();
  int ret (0);
  rep (i, x[3], x[4]) {
    ret += P - pre (i, y[3] - 1) * suf (i, y[3]) % P * (i + y[3]) % P;

    ret += pre (i, y[4]) * suf (i, y[4] + 1) % P * (i + y[4] + 1);

    ret %= P;
    // cout<<ret<<" "<<suf (i, y[3])<<" "<<pre (i, y[4]) * suf (i, y[4])<<endl;
  }
  rep (i, y[3], y[4]) {
    ret += P - pre (x[3] - 1, i) * suf (x[3], i) % P * (x[3] + i) % P;
    ret += pre (x[4], i) * suf (x[4] + 1, i) % P * (x[4] + i + 1);

    ret %= P;
  }
  cout << ret;
}
```

---

## 作者：Sky_Maths (赞：0)

## 提示
这是一篇专门解释如何计算 **从 $(x_s, y_s)$ 到 $(x_t, y_t)$，经过矩阵 $M_2$，并从矩阵中选出一个被路径覆盖的点** 的方案数 的题解。

## 思路
首先发现可以枚举中间的矩阵 $M_2$，必然是从左/下进入，从右/上离开，于是枚举进入和离开的 **方式（对于左下角和右上角有两种可能）**，时间复杂度为 $O(n^2)$。

对于一条 **已定** 的矩阵中的路径 $(x_1, y_1)\to(x_2, y_2)$，它需要乘上一个权值 $(x_2 - x_1 + y_2 - y_1 + 1)$，这是路径的长度，也即可选择的点数。

那么我们可以将其“分开”，分两次求，注意此时并没有成功优化，只是为了不那么抽象/感性。

先对于进入点考虑，乘上的权值变为 $(-x_1 - y_1)$，也可以发现对于每一条以 $(x_1, y_1)$ 为进入点的路径都要乘上这个权值，离开点类似。于是枚举进入/离开点，将这类路径乘上对应的权值即可。

有人可能会觉得还有其他的一些系数，但其实是没有的，因为这个求的方法在我看来有点“散”，分类方法并没有那么直观，但是非常高明。

## 总结
计数时可以将系数相同的分开，先不强求优化，使其更加清晰，再考虑优化。

## 参考资料
- [Sightseeing Plan by 枫林晚](https://www.luogu.com.cn/article/0x7wdt0h)

## 代码
[code](https://atcoder.jp/contests/agc018/submissions/51423503)

---

## 作者：Otomachi_Una_ (赞：0)

**[E - Sightseeing Plan](https://atcoder.jp/contests/agc018/tasks/agc018_e)（7）**

先考虑一个简单的问题，起点在 $(0,0)$，终点在 $([0,x],[0,y])$ 之间的路径有多少？

显然有：
$$
\begin{aligned}\text{Answer}&=\sum_{i=0}^x\sum_{j=0}^y\dbinom {i+j}{i}\\&=\sum_{i=0}^x\sum_{j=0}^y(\dbinom{i+j+1}{i+1}-\dbinom{i+j}{i+1})\\&=\sum_{i=0}^x\dbinom{i+y+1}{i+1}\\&=\sum_{i=0}^x(\dbinom{i+y+2}{i+1}-\dbinom{i+y+1}{i})\\&=\dbinom{x+y+2}{x+1}\end{aligned}
$$
这是从 $(0,0)\to(x+1,y+1)$ 的步数。

通过差分第 $1,3$ 个矩阵，我们能够把问题变成 $16$ 个固定起点终点的问题。

我们继续思考这样的问题：固定终点和起点，有一个矩阵，一条路径的价值是路径与矩阵交的点数。求所有路径的和。

我们继续把这个矩阵差分下来，变成了一个包括起点的矩阵。我们取枚举路径出去这个矩阵的位置 $pos$（$pos$ 只有 $\mathcal O(V)$ 种可能），那么只要加一下 $s\to pos\to out\to t$ 的方案数在乘上 $s\to pos$ 的整点个数即可。

时间复杂度 $\mathcal O(wn)$，其中 $w=2^6=64$。

[submission](https://atcoder.jp/contests/agc018/submissions/45302518) 

---

## 作者：DaiRuiChen007 (赞：0)

# AGC018E 题解

[Problem Link](https://www.luogu.com.cn/problem/AT_agc018_e)

**题目大意**

> 给三个矩形 $R_1=(x_1,y_1,x_2,y_2),R_2=(x_3.y_3,x_4,y_4),R_3=(x_5,y_5,x_6,y_6)$，保证三个矩形左下到右上排列，求有多少种路径 $u\to v\to w$ 满足 $u\in R_1,v\in R_2,w\in R_3$。
>
> 不同的 $u,v,w$ 或不同的路径均算作不同的方案。
>
> 数据范围：$x_1\le x_2<x_3\le x_4<x_5\le x_6,y_1\le y_2<y_3\le y_4<y_5\le y_6$，$n=\max\{x_i,y_i\}\le 10^6$。

**思路分析**

先考虑点 $(0,0)$ 到矩形 $(x_1,y_1,x_2,y_2)$ 的方案，显然前缀和转化成 $(0,0)$ 到 $(0,0,x,y)$ 的方案，容易得到：
$$
\begin{aligned}
\mathrm{Ans}
&=\sum_{i=0}^x\sum_{j=0}^y\binom{i+j}{i}\\
&=\sum_{i=0}^x\sum_{j=0}^y\binom{i+j+1}{i+1}-\binom{i+j}{i+1}\\
&=\sum_{i=0}^x\binom{i+y+1}{i+1}\\
&=\dfrac 1{y!}\sum_{i=0}^x (i+y+1)^{\underline y}\\
&=\dfrac 1{y!}\times\dfrac{1}{y+1} (x+y+2)^{\underline{y+1}}\\
&=\binom{x+y+2}{x+1}
\end{aligned}
$$
因此 $(0,0)$ 到 $(0,0,x,y)$ 的方案等价于 $(0,0,x+1,y+1)$ 的方案，那么原问题中 $R_1\to v\to R_3$ 也可以用类似的技巧转成 $16$ 组 $s\to v\to t$ 的方案数，其中 $s,t$ 是定点，$v\in R_2$。

考虑进入 $R_2$ 的的位置 $(ix,iy)$ 和离开 $R_2$ 的位置 $(ox,oy)$，容易发现 $(ix,iy)$  属于下边界上的点构成的点集 $D$ 或左边界上的点构成的点集 $L$；$(ox,oy)$ 属于上边界上的点构成的点集 $U$ 或右边界上的点构成的点集 $R$。

不妨假设 $(ix,iy)\in L,(ox,oy)\in R$，$F(u\to v) $ 表对应路径数，那么得到对应路径的贡献：$F(s\to (ix-1,iy))\times F((ix,iy)\to(ox,oy))\times F((ox+1,oy)\to t)\times (ox+oy-ix-iy+1)$。

考虑拆分贡献，分成 $-F(s\to (ix-1,iy))\times F((ix,iy)\to t)\times (ix+iy)$，$F(s\to (ix-1,iy))\times F((ix,iy)\to t)$，以及 $F(s\to (ox,oy))\times F((ox+1,oy)\to t)\times (ox+oy)$ 三部分，每部分只要 $\mathcal O(n)$ 枚举 $L/R/U/D$ 的其中一个即可。

时间复杂度 $\mathcal O(n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=2e6+5,MOD=1e9+7;
inline int ksm(int a,int b=MOD-2,int p=MOD) {
	int ret=1;
	while(b) ret=(b&1?ret*a%p:ret),a=a*a%p,b=b>>1;
	return ret;
}
int fac[MAXN],inv[MAXN];
inline int binom(int n,int m) {
	return fac[n]*inv[m]%MOD*inv[n-m]%MOD;
}
int x[10],y[10];
struct Point {
	int c,x,y;
};
int l,r,u,d;
inline int path(int sx,int sy,int tx,int ty) { return binom(tx+ty-sx-sy,tx-sx); }
inline int solve1(int sx,int sy,int tx,int ty) {
	int ans=0;
	for(int i=l;i<=r;++i) ans=(ans+path(sx,sy,u-1,i)*path(u,i,tx,ty))%MOD; //(u-1,i) -> (u,i)
	for(int i=u;i<=d;++i) ans=(ans+path(sx,sy,i,l-1)*path(i,l,tx,ty))%MOD; //(i,l-1) -> (i,l)
	return ans;
}
inline int solveS(int sx,int sy,int tx,int ty) {
	int ans=0;
	for(int i=l;i<=r;++i) ans=(ans+path(sx,sy,u-1,i)*path(u,i,tx,ty)%MOD*(u+i))%MOD; //(u-1,i) -> (u,i)
	for(int i=u;i<=d;++i) ans=(ans+path(sx,sy,i,l-1)*path(i,l,tx,ty)%MOD*(i+l))%MOD; //(i,l-1) -> (i,l)
	return ans;
}
inline int solveT(int sx,int sy,int tx,int ty) {
	int ans=0;
	for(int i=l;i<=r;++i) ans=(ans+path(sx,sy,d,i)*path(d+1,i,tx,ty)%MOD*(d+i))%MOD; //(d,i) -> (d+1,i)
	for(int i=u;i<=d;++i) ans=(ans+path(sx,sy,i,r)*path(i,r+1,tx,ty)%MOD*(i+r))%MOD; //(i,r) -> (i,r+1)
	return ans;
}
signed main() {
	for(int i=fac[0]=inv[0]=1;i<MAXN;++i) inv[i]=ksm(fac[i]=fac[i-1]*i%MOD);
	for(int i:{1,2,3,4,5,6}) scanf("%lld",&x[i]);
	for(int i:{1,2,3,4,5,6}) scanf("%lld",&y[i]);
	vector <Point> vs{ {1,x[1]-1,y[1]-1}, {-1,x[1]-1,y[2]}, {-1,x[2],y[1]-1}, {1,x[2],y[2]} };
	vector <Point> vt{ {1,x[6]+1,y[6]+1}, {-1,x[6]+1,y[5]}, {-1,x[5],y[6]+1}, {1,x[5],y[5]} };
	u=x[3],d=x[4],l=y[3],r=y[4];
	int ans=0;
	for(auto S:vs) for(auto T:vt) {
		int val=(solveT(S.x,S.y,T.x,T.y)-solveS(S.x,S.y,T.x,T.y)+solve1(S.x,S.y,T.x,T.y)+MOD)%MOD;
		ans=(ans+MOD+S.c*T.c*val)%MOD;
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：QcpyWcpyQ (赞：0)

首先对于路径 $(a,b)\to(c,d)$，令 $F(a,b,c,d)$ 为路径数量，有
$$
F(a,b,c,d)=\binom{c-a+d-b}{c-a}
$$
考虑计算点 $(x,y)$ 到矩形 $((a,b)-(c,d))$ 的路径数量。容斥得数量为
$$
G(x,y,a,b,c,d)=F(x,y,c+1,d+1)-F(x,y,a,d+1)-F(x,y,c+1,b)+F(x,y,a,b)
$$
考虑枚举进出第二个矩形 $((x_3,y_3)-(x_4,y_4))$ 的点 $s=(sx,sy)$ 和 $t=(tx,ty)$，那么 $(sx,sy)$ 必然在第二个矩形的靠左下角的边界上，$(tx,ty)$ 必然在第二个矩形的靠右上角的边界上。

此时计算答案转化为
$$
\sum_{sx}\sum_{sy}\sum_{tx}\sum_{ty}dis((sx,sy),(tx,ty))\times G(sx,sy,x_1,y_1,x_2,y_2)\times G(tx,ty,x_5,y_5,x_6,y_6)
$$
时间复杂度是 $\mathcal O\left(n^2\right)$ 的，不可通过。

考虑拆分贡献，分别计算进入点和离开点对答案的贡献。对于每一个从 $(sx,sy)$ 进入的路径，其答案都要乘上 $(-sx-sy)$ 的系数；对于每一个从 $(tx,ty)$ 离开的路径，其答案都要乘上 $(tx+ty)$ 的系数。所以可以直接枚举进入点和离开点，将路径乘上对应的权值。时间复杂度为 $\mathcal O\left(n\right)$。

感性理解，这个拆分贡献的方式类似于
$$
\sum_i\sum_jA(i)\times B(j)=\left(\sum_i A(i)\right)\times\left(\sum_j B(j)\right)
$$

---

