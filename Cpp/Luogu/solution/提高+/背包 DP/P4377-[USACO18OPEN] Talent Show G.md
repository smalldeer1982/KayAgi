# [USACO18OPEN] Talent Show G

## 题目描述

Farmer John 要带着他的 $n$ 头奶牛，方便起见编号为 $1\ldots n$，到农业展览会上去，参加每年的达牛秀！他的第 $i$ 头奶牛重量为 $w_i$，才艺水平为 $t_i$，两者都是整数。

在到达时，Farmer John 就被今年达牛秀的新规则吓到了：

（一）参加比赛的一组奶牛必须总重量至少为 $W$（这是为了确保是强大的队伍在比赛，而不仅是强大的某头奶牛），并且。

（二）总才艺值与总重量的比值最大的一组获得胜利。

FJ 注意到他的所有奶牛的总重量不小于 $W$，所以他能够派出符合规则（一）的队伍。帮助他确定这样的队伍中能够达到的最佳的才艺与重量的比值。

## 说明/提示

#### 样例解释

在这个例子中，总体来看最佳的才艺与重量的比值应该是仅用一头才艺值为 $11$、重量为 $10$ 的奶牛，但是由于我们需要至少 $15$ 单位的重量，最优解最终为使用这头奶牛加上才艺值为 $21$、重量为 $20$ 的奶牛。这样的话才艺与重量的比值为 $\frac{11+21}{10+20}=\frac{32}{30} = 1.0666\dots$，乘以 $1000$ 向下取整之后得到 $1066$。

#### 数据规模与约定

对于全部的测试点，保证 $1 \leq n \leq 250$，$1 \leq W \leq 1000$，$1 \leq w_i \leq 10^6$，$1 \leq t_i \leq 10^3$。

## 样例 #1

### 输入

```
3 15
20 21
10 11
30 31```

### 输出

```
1066
```

# 题解

## 作者：瞬闪影 (赞：59)

### 这道题所需要的知识点是：01分数规划 背包dp

 首先01分数规划更像是一种数据的转化，相信不少童鞋都试着贪心来着，然额几经波折的你最后也许会发现贪心是彻底错误的，归结到底还是因为这个式子有个“/”号╰（‵□′）╯
 
而01分数规划就是将这样的数据处理需求“可贪心化”，下面看看她是怎么做到的

首先定义一个数组x，x[i]表示的是这一头牛拿不拿，如果拿赋值成1，不拿就是0

那么则有答案R=sigma(t[i]\*x[i])/sigma(w[i]\*x[i])我们需要R最大，现在我们假设有一个没那么优的答案Z满足Z<=R，那么就会有如下的式子：
	sigma(t[i]\*x[i])>=sigma(w[i]\*x[i])\*Z
    
也就是sigma((t[i]-w[i])\*x[i]\*Z)>=0
    
我天！每头牛的贡献竟然变成了(t[i]-w[i])\*x[i]\*Z，与其他牛无关了有木有！这下不久可以贪心了吗！只要在最优选取的状态下可以使总和非负，就说明这个Z是可行的，答案还可以进一步变大！

所以，与二分配合，进行01分数规划就是这题的第一步。

然而在验证的时候也有些小问题，这里要求奶牛们的总质量必须不小于W，这就很难愉快的贪心了啊。。。不过我们还有应对办法，用背包啊！

设f[i]为当前选择的奶牛总质量为i时sigma((t[i]-w[i])\*x[i]\*Z)最大是多少，因为这有可能是负数，所以初值最好弄成负无穷

接下来以零一背包的模式dp就好了，不过要注意，要把所有总质量大于等于W的更新全算在f[W]上。这里如果有点蒙可以详见代码

总之希望这篇题解对你有帮助！d=====(￣▽￣*)b
```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
int n,W;
int w[300],t[300];
long long f[10000];
bool check(int z){
	memset(f,128,sizeof(f));f[0]=0;
	long long tmp=f[W];
	for(int i=1;i<=n;i++){
		for(int j=W;j>=0;j--)if(f[j]!=tmp){
			int jj=j+w[i];jj=min(jj,W);
			f[jj]=max(f[jj],f[j]+t[i]-(long long)w[i]*z);
		}
	}
	return f[W]>=0;
}
int erfen(){
	int l=0,r=1000000;
	while(l<=r){
		int mid=l+r>>1;
		if(check(mid))l=mid+1;
		else r=mid-1;
	}
	return l-1;
}
int main(){
	scanf("%d%d",&n,&W);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&w[i],&t[i]);
		t[i]*=1000;
	}
	printf("%d",erfen());
	return 0;
}
```

---

## 作者：zhmshitiancai (赞：18)

[门](https://www.luogu.org/problem/P4377)

### 解：
1. 分数规划

二分答案
$$ \frac{\sum ti}{\sum wi} \geq  mid $$ 
即

$$\sum ti-mid \times \sum wi \geq 0$$

即
$$\sum (ti-mid \times wi) \geq 0$$
为了方便令$ti-mid \times wi=ci$ 

2.  01背包

做一个大小为$W$ 的背包，重量大于等于$W$的，都记在$dp[w]$上。
最后只要看$dp[W]$ 是否大于0。
就可以解决重量至少为$W$ 的限制。

### Tips:
1.我连背包都不会了。。。

**Code:**
``` cpp

//love yjl forever
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
const int INF=0x3f3f3f3f,MAX=250+5,MAXm=1000+5;
const double eps=1e-5;
int n,W;
int t[MAX],w[MAX];
double c[MAX],dp[MAXm];
bool ok(double mid)
{
	int i,j;
	for(i=1;i<=n;i++)
		c[i]=(double)t[i]-mid*w[i];
	
	for(i=1;i<=W;i++)
		dp[i]=-INF;
/*	for(i=1;i<=n;i++)
		cout<<c[i]<<" ";
	cout<<endl;*/
	for(i=1;i<=n;i++)
		for(j=W;j>=0;j--)
		{
			if(j+w[i]>=W)	
				dp[W]=max(dp[W],dp[j]+c[i]);
			else
				dp[j+w[i]]=max(dp[j+w[i]],dp[j]+c[i]); 
		}
	return dp[W]>=0;
}
int main()
{
/*	freopen("","r",stdin);
	freopen("","w",stdout);*/
	int i;
	cin>>n>>W;
	
	double l=0,r=0;
	for(i=1;i<=n;i++)
	{
		cin>>w[i]>>t[i];
		r+=t[i];
	}
	
	while(l+eps<=r)
	{
		double mid=(l+r)/2;
		if(ok(mid))
		{
			l=mid;	
		}
		else 
			r=mid;
	}
	cout<<(int)(l*1000)<<endl;
	return 0;
}
```

---

## 作者：Parabola (赞：17)

### Part0.题外话

妈的搞什么国际玩笑

2018OPEN银比金难

![](https://cdn.luogu.com.cn/upload/pic/57766.png)

### Part1.题外话2

这是一道一眼题（只要你学过01分数规划？）

然后题解还有罪恶的贪心？

于是我想写一篇题解讲讲这个01分数规划

### Part3.总算进入正题了

什么是01分数规划。就是有$n$个物品，每个物品有两个属性$(x,y)$，现在你要选出一些物品使得选出的物品的$x$属性的和与$y$属性的和比值最大。

我就知道自然语言的无力，肯定有人没看懂，给你们看看数学语言如何描述

三个序列$x$ , $y$，$b$，长度为$n$

而$b$满足$∀i ∈ [1 , n] , b_i ∈(1,0)$

要求给$b$安排一种合法的取值，最大化$\dfrac {\sum_{i = 1}^n{x_i} * b_i} {\sum_{i = 1}^n{y_i} * b_i}$，其中$x,y$已知

这种问题的解法就是二分法

假设窝们现在猜测的答案是$L$，则要检验$L$是否可行

若$L$可行，则必然最终的答案大于等于L

否则小于L

而此刻$L$是我们猜的答案，也就是说他要满足存在一组$b$使得$\sum_{i = 1}^n{x_i} * b_i = \sum_{i = 1}^n{y_i} * b_i * L$

即$\sum_{i = 1}^n{(x_i - y_i * L)} * b_i >=0$

那就变成了给你一个数组$A$，$A_i = x_i-y_i* L$，从$A$中选取一些数使得它们的和能取到最大值。

那不就取所有正数嘛？

然后判断是否>=0不就好了。

这就是基本01分数规划的解法，还有一种Dinkelbach迭代法，这个没什么用（个人观点），比二分块不到哪去。

### Part3.这题

这题不就是个板子，只不过多了限制。并不是所有正数都能取，还有个范围上限。

那不就成了个背包喵

### Part4.Code
```cpp
#include<bits/stdc++.h>
using namespace std; 
#define rep(i , a , b) for(int i = (a) ; i <= (b) ; ++i)
#define irep(i , a , b) for(int i = (b) ; i >= (a) ; --i)
#define IO ios::sync_with_stdio(false) 
#define ms(A) memset(A , 0 , sizeof A)
#define msinf(A) memset(A , 0x3f , sizeof A)
typedef long long ll;
typedef pair <int , int> pii;  

const int inf = 0x3f3f3f3f;
const ll infLL = 0x3f3f3f3f3f3f3f3fLL;

const int MAXN = 250 + 5;
const int MAXW = 1000 + 5;
const double eps = 1e-6;

int n , wei , sumt , w[MAXN] , t[MAXN];

double p[MAXN] , dp[MAXW];

double Get() { 
	rep(j , 1 , wei) dp[j] = -inf;
	rep(i , 0 , n) {
		irep(j , 0 , wei) {
			if(j + w[i] >= wei) dp[wei] = max(dp[wei] , dp[j] + p[i]);
			else dp[j + w[i]] = max(dp[j + w[i]] , dp[j] + p[i]); 
		}
	}
	return dp[wei];
}

int main() {
	scanf("%d %d" , &n , &wei);
	rep(i , 1 , n) scanf("%d %d" , w + i , t + i) , sumt += t[i];
	double l = 0 , r = sumt;
	while(r - l > eps) {
		double mid = (l + r) / 2;
		rep(i , 1 , n) p[i] = t[i] - mid * w[i];
		double res = Get();
		if(res >= eps) l = mid;
		else r = mid - eps;
	}
	cout << (int)(l * 1000);
}
```
### Part5.最后再说一句话

如果你过不了，不要急着骂我

记得卡卡精度，这题按理四位就够了，但是我卡到6位才过...

---

## 作者：任梦华 (赞：17)

本蒟蒻发现这个题目基本都是01分数规划或者背包做法之类的，又发现数据也不是很强于是给大家展示一下我的暴力贪心卡时做法（自认为qwq）

主要思路非常简单，只做部分性价比高的牛，其他的牛先扔在一旁，有时间就管一下，没时间就不管（别怪我贪心我只是不会正解qwq）

然后再用简陋的一匹的暴力做法直接去推答案（非常暴力的做法，捂脸）

然后是最重要的一步，卡时，少了他，“你就可以获得30分的好成绩”（出自某个H2大佬）

蒟蒻码字不容易，求别打回谢谢qwq

然后上代码了qwq
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,w,js,ans;
struct EE{
    int w,t;
}e[300];
void ss(int wz,int h,int s)//
{
    js++;
    if(js>10000000)
        return;//卡时：当我们的时间不够了咋办，就见好就收了吧，咱们已经有一些贪心出来的解，运气好就能拿到很多分，运气不好也至少应该不会暴零了qwq，如果还是没分只能说数据太强了。
    if(s>=w)//粗糙的算法（逃
    {
        h=1000*h;
        ans=max(ans,h/s);
        return;
    }
    for(int i=wz+1;i<=n;i++)//找下一个吧
        ss(i,h+e[i].t,s+e[i].w);
}
bool cmp(EE a,EE b)
{
    return a.t*b.w>b.t*a.w;
}//a.t/a.w>b.t/b.w转化为a.t*b.w>b.t*a.w，这样可以不用算浮点数了
int main()
{
    scanf("%d%d",&n,&w);
    for(int i=1;i<=n;i++)
        scanf("%d%d",&e[i].w,&e[i].t);
    sort(e+1,e+1+n,cmp);//贪心一下找性价比高的
    for(int i=1;i<=n;i++)//因为性价比最高的不一定我们要的里面，所以从几个高的里挑一挑（呢？）
        ss(i,e[i].t,e[i].w);//大佬别喷，这个暴力的确很难看qwq
    printf("%d",ans);
}

```


---

## 作者：DengDuck (赞：10)

听说这题是分数规划的板子题，所以我用神犇 Konjac_HZX 的裸背包做法过了，时间复杂度十分优秀。

一种比较暴力的思想：我们直接做背包，$f_{i,j}$ 表示前 $i$ 个奶牛总重量为 $j$ 下最大的才艺值，然后统计统计就可以了。

时间复杂度瓶颈是什么？我们发现总重量和可能很大，所以背包很慢。

有一个定理，俗话叫糖水定理，就是 $\max(\dfrac a b,\dfrac c d)\geq \dfrac{a+c}{b+d}$，这个东西的证明比较简单，用分数基本性质算一算就行了。

这给了我们什么启发呢？加上奶牛只会让比变小，当然你加上一个这个分数值比你目前方案的分数值大的奶牛（神仙牛）除外，但是这种情况我已经选择的奶牛为啥不选一些干掉换成这个神仙牛呢？你的身价是抬高了，但是神仙牛却自降身价了。这样在全局上是不优的，会被选择了神仙牛的方案比下去。

所以说我们在处理背包时，加到满足重量限制条件的时候就停止结算。

比如，当前重量为 $x$ 的奶牛尝试用 $f_{i-1,j}$ 更新 $f_{i,j+x}$ 时发现 $j+x\geq W$，那么我们就直接结算这种可能，更新答案。

注意我们需要排序把比较轻的奶牛放在前面，不然大奶牛结算了，我们会没考虑到一些小奶牛填充空间，大奶牛加入结算的可能。

时间复杂度为 $\mathcal O(nm)$。


```cpp
#include<bits/stdc++.h>
#define LL long long 
using namespace std;
const LL N=255;
const LL M=1005;
LL n,m,f[N][M],ans;
struct node
{
	LL a,b;
}a[N];
bool cmp(node x,node y)
{
	return x.a<y.a;
}
int main()
{
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld%lld",&a[i].a,&a[i].b);
	}
	memset(f,-127,sizeof(f));
	f[0][0]=0;
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<=m;j++)
		{
			f[i][j]=f[i-1][j];
			if(j-a[i].a>=0)f[i][j]=max(f[i][j],f[i-1][j-a[i].a]+a[i].b);
			if(j+a[i].a>=m)ans=max(ans,(f[i-1][j]+a[i].b)*1000/(j+a[i].a));
		}
	}
	printf("%lld",ans);
}
```

---

## 作者：AThousandSuns (赞：10)

emmm……看到题面“总才艺值与总体重的比值最大”，那么这个就是01分数规划问题了。

现在详细讲一讲如何解决这类问题。

---
先看简单一点的题：

有 $n$ 个物品，有属性值 $a_i,b_i$。要求选出至多 $k$ 个物品，使得 $\frac{\sum a_i}{\sum b_i}$ 尽可能大。

我们要首先二分答案 $x$。若 $\frac{\sum a_i}{\sum b_i}\ge x$ 则说明答案可以更大。

稍微变形一下：$\sum a_i\ge \sum b_ix$

继续：$\sum(a_i-b_ix)\ge 0$。

我们发现 $i$ 对答案的贡献是个常数 $a_i-b_ix$ 了！

由于至多选 $k$ 个物品，我们可以贪心，将 $a_i-b_ix$ 从大到小排序，然后选出前 $k$ 个前缀和的最大值。如果是非负数那么答案就可以变得更大。

---
回到原题：

每头牛的贡献值应该还是 $t_i-w_ix$，但是这里要求 $\sum w_i\ge W$，就不能简单的贪心了。

那就背包！至于背包的细节看[这篇题解](https://www.luogu.org/blog/SSY/solution-p4377)，我也说不清楚……

---
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=100010;
inline int read(){
	char ch=getchar();int x=0,f=0;
	while(ch<'0' || ch>'9') f|=ch=='-',ch=getchar();
	while(ch>='0' && ch<='9') x=x*10+ch-'0',ch=getchar();
	return f?-x:x;
}
int n,m,w[256],t[256];
ll dp[1111];
bool check(int x){
	memset(dp,~0x3f,sizeof(dp));dp[0]=0;	//初始化（要memset成负数的原因有两个：1.v[i]可以是负的，2.可以不像平常写的01背包一样dp[i]表示至多装了i体积的物体，具体自己想一想）
	for(int i=1;i<=n;i++)
		for(int j=m;~j;j--) dp[min(j+w[i],m)]=max(dp[min(j+w[i],m)],dp[j]+t[i]-1ll*w[i]*x);	//大于m的算在m头上
	return dp[m]>=0;	//答案可以增大
}
int main(){
	n=read();m=read();
	for(int i=1;i<=n;i++) w[i]=read(),t[i]=read()*1000;	//t[i]*=1000正好满足题目说的*1000的要求，也可以避免小数
	int l=0,r=2.5e8;	//右边界是sigma(t[i])的最大值
	while(l<r){
		int mid=(l+r+1)>>1;
		if(check(mid)) l=mid;	//二分判断
		else r=mid-1;
	}
	printf("%d\n",l);
}
```

---

## 作者：_louhc (赞：6)

# [P4377 [USACO18OPEN]Talent Show](https://www.luogu.org/problemnew/show/P4377)

# 思路I

很简单的0/1分数规划与背包DP结合。。。

0/1分数规划老套路（安利[机房巨佬zzq博客](https://www.luogu.org/blog/yestoday/post-01-fen-shuo-gui-hua-yang-xie)_还上了洛谷日报$QAQ$_）——>二分答案，条件$\sum (ti \times Ans - wi) \ge 0$

但是，我们注意到$\sum wi$可能会很大，所以我们不能直接弄动态规划。

我们引入一些贪心的思想。

1. 若$t\times Ans-w\ge 0$直接选来。因为这样只会更优化答案。
2. 若1不满足，若$w\ge W$，只有$t\times Ans - w$最大的有可能成为答案。
3. 若2再不满足，背包DP即可。只要把容量设为$2\times W$即可。（请自行思考

然后就是代码啦

# 代码I

```cpp
#include<bits/stdc++.h>
using namespace std;
#define Re register
#define MAXN 255
#define LD long double

int N, W, WW;
int w[MAXN], T[MAXN];
LD f[2005], v;

bool check( LD t ){
	int c(0); LD r(0), tmp(-1e12);
	for ( int i = 1; i <= WW; ++i ) f[i] = -1e12;
	
	for ( int i = 1; i <= N; ++i ){
		v = T[i] - w[i] * t;
		if ( v >= 0 ) c += w[i], r += v;
		else{
			if ( w[i] >= W ){ tmp = max( tmp, v ); continue; }
			for ( int j = WW; j >= w[i]; --j ) f[j] = max( f[j], f[j - w[i]] + v );
		}
	}
	if ( c >= W || r + tmp >= 0 ) return 1;
	for ( int i = W - c; i <= WW; ++i ) if ( f[i] + r >= 0 ) return 1;
	return 0;
}

int main(){
	scanf( "%d%d", &N, &W ); WW = W << 1;
	for ( int i = 1; i <= N; ++i ) scanf( "%d%d", &w[i], &T[i] );
	LD l(0), r(1000000), mid;
	for ( int i = 1; i <= 40; ++i ){
		mid = ( l + r ) / 2;
		if ( check( mid ) ) l = mid;
		else r = mid;
	}
	printf( "%d\n", (int)floor(l * 1000) );
	return 0;
}

```

# 思路II

实际上，好像另一种写法更简洁？容量设为W空间还要更小？（我太弱了QAQ

把状态转移方程式写成+的形式，而不是上面那种-的形式。

只要大于等于W的，都缩成一种状态。这样写好简单呀$QAQ$

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define Re register
#define MAXN 255
#define LD long double

int N, W;
int w[MAXN], T[MAXN];
LD f[1005], v;

bool check( LD t ){
	for ( int i = 1; i <= W; ++i ) f[i] = -1e12;	
	for ( int i = 1; i <= N; ++i ){
		for ( int j = W; j >= 0; --j ){
			int k( min( j + w[i], W ) );
			f[k] = max( f[k], f[j] + T[i] - w[i] * t );
		}
	}
	return f[W] >= 0;
}

int main(){
	scanf( "%d%d", &N, &W );
	for ( int i = 1; i <= N; ++i ) scanf( "%d%d", &w[i], &T[i] );
	LD l(0), r(1000000), mid;
	for ( int i = 1; i <= 40; ++i ){
		mid = ( l + r ) / 2;
		if ( check( mid ) ) l = mid;
		else r = mid;
	}
	printf( "%d\n", (int)floor(l * 1000) );
	return 0;
}

```

---

## 作者：a2600254 (赞：5)

01分数规划裸题

我们需要求得$\frac{\sum_{}^{}{t[i]}}{\sum_{}^{}{w[i]}}$的最大值

设答案为$x$，化简可得$\sum_{}^{}{(t[i]-w[i]*x)}$

首先二分$x$，然后代入做01背包即可

注意二分方式，可能被卡精度

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<cstdlib>
#include<cmath>
using namespace std;
#define max(a,b) ((a>b)?(a):(b))
#define min(a,b) ((a<b)?(a):(b))
#define rd(a) scanf("%d",&a)
#define rd2(a,b) scanf("%d%d",&a,&b)
#define rd3(a,b,c) scanf("%d%d%d",&a,&b,&c)
#define wt(a) printf("%d",a)
#define wtb putchar(' ')
#define wtl putchar(10)
#define F1N FUP(i,1,n)
#define FUP(a,b,c) for(int a=b;a<=c;++a)
#define FDN(a,b,c) for(int a=b;a>=c;--a)
#define maxn 300
int n,W,mid,l,r=1000000,w[maxn],t[maxn],dp[1000000];
bool check(int x)
{
	memset(dp,0x80,sizeof(dp));
	dp[0]=0;
	int temp=dp[W];
	F1N
		for(int j=W;j>=0;--j)
			if(dp[j]!=temp)
				dp[min(W,j+w[i])]=max(dp[min(W,j+w[i])],dp[j]+t[i]-(long long)w[i]*x);
	return dp[W]>=0;
}
int main()
{
	rd2(n,W);
	F1N
		rd2(w[i],t[i]),t[i]*=1000;
	while(l<=r)
	{
		mid=(l+r)>>1;
		if(check(mid))
			l=mid+1;
		else
			r=mid-1;
	}
	wt(l-1);
	rd2(n,W);
}
```

---

## 作者：AlexZhang (赞：4)

## **emmm这题说起来欲哭无泪

今日我们多校联训入营测试的最后一题

感觉自己能AC来着结果只有20分

好了，言归正传，我们讲讲这题做法
**

暴力先不说了，直接上正解

这类价值类比值问题多数为01分数规划，什么是01分数规划呢，就这题来说，sigma（t）/sigma（w）=r  (sigma为求和符号Σ)（r为最终答案），根据性质sigma（t）=sigema（w）*r;再根据减法性质sigma（t）－ｓｉｇｍａ(ｗ)＊ｒ＝０。此时基本上就形成了一个函数关系，ｆ（ｘ）＝sigma（t）－ｓｉｇｍａ(ｗ)＊ｒ，用ｆ（ｘ）与０比较，如果大于０，那证明ｒ的值小了，小于０就是ｒ的值大了（数学知识）。等于零正好。这还等什么，二分啊。把每个数０１规划后的值依次预处理好放在一个新数组里保存，（０１规划的值就是ｔｉ－ｗｉ＊ｒ）

以上，本人考场想的明明白白的，但是有个制约条件，选出几人的重量和必须大于等于Ｗ，本人在考场上选择贪心算法了，按照没个数经过０１规划后的值进行了排序，从大到小选，后来才回过神来，这应该是个背包啊，下面放一下错误代码
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
int n,w;
double ans;
struct edge{
    int w,t,num;
    double js;
}e[251];
bool cmp(edge x,edge y){
    if(x.js==y.js) return x.w>y.w;
    return x.js>y.js;
}
bool solve(double x){
    double tot1=0,tot2=0;
    for(int i=1;i<=n;i++){
        e[i].js=e[i].t-e[i].w*x;
    //  printf("%f ",e[i].js);
    }
    //printf("\n");
    sort(e+1,e+1+n,cmp);
    for(int i=1;i<=n;i++){
        tot1+=e[i].js;tot2+=e[i].w;
        if(tot2>=w) break;
    }
//  printf("%f\n",tot1);
    return tot1>=0;
}
int main(){
    scanf("%d%d",&n,&w);
    double l=0,r=0;
    for(int i=1;i<=n;i++){
        scanf("%d%d",&e[i].w,&e[i].t);
        r+=e[i].t;
    }
    while(r-l>=0.0001){
        double mid=(l+r)/2;
        //printf("%f\n",mid);
        if(solve(mid)){ l=mid+0.0001;ans=l;}
        else{ r=mid-0.0001;}
    }
    ans=(ans*1000);
    printf("%d",(int)ans);
    return 0;
}
```

下面按照背包的做法放出正确代码

```cpp
#include <cstdio>
#include <algorithm>
#define inf 2147483647
using namespace std;
int n,w;
double ans,f[1005];
struct edge{
    int w,t,num;
    double js;
}e[251];
bool cmp(edge x,edge y){
   // if(x.js==y.js) return x.w>y.w;
    return x.js>y.js;
}
bool solve(double x){
	 for(int i=1;i<=w;i++) f[i]=-inf;
    double tot1=0,tot2=0;
    for(int i=1;i<=n;i++){
        e[i].js=e[i].t-e[i].w*x;
    //  printf("%f ",e[i].js);
    }
    //printf("\n");
    //sort(e+1,e+1+n,cmp);
    for(int i=1;i<=n;i++)
    	for(int j=w;j>=0;j--)
    		f[min(e[i].w+j,w)]=max(f[min(e[i].w+j,w)],f[j]+e[i].js);
//  printf("%f\n",tot1);
    //	printf("%f",f[w]);
    return f[w]>=0;
}
int main(){
    scanf("%d%d",&n,&w);
    double l=0,r=0;
    for(int i=1;i<=n;i++){
        scanf("%d%d",&e[i].w,&e[i].t);
        r+=e[i].t;
    }
    while(r-l>=0.00001){
        double mid=(l+r)/2;
        //printf("%f\n",mid);
        if(solve(mid)){ l=mid;ans=l;}
        else{ r=mid;}
    }
    ans=(ans*1000);
    printf("%d",(int)ans);
    return 0;
}

```
ｏｋ大功告成！求管理给过，毕竟我是第一篇题解吖

---

## 作者：LOOOSER (赞：3)

这道题我们设 $f[i][j]$ 表示考虑了第 $i$ 头牛，当前的总重量为 $j$ 的比值的最大值，转移方程为：

1. 不选择第 $i+1$ 头奶牛：$f[i+1][j]=max(f[i+1][j],\;f[i][j])$
2. 选择第 $i+1$ 头奶牛：$f[i+1][j+w[i]]=max(f[i+1][j+w[i],\;x)$

其中 $i\in[1,\;n-1]$，$j\in[0,\;W]$

这个 $x$ 就是选择第 $i+1$ 头奶牛后，新的总才艺值和总重量的比值，由于 $x$ 不能直接由 $f[i][j]$ 得到，需要新设 $s[i][j]$ 表示 $f[i][j]$ 对应的总才艺值， $p[i][j]$ 表示 $f[i][j]$ 对应的总重量，于是：

$f[i+1][j+w[i]]=max(f[i+1][j+w[i]],\;(s[i][j]+t[i+1])\div(p[i][j]+w[i+1])$

$s[i][j]$ 和 $p[i][j]$ 在 $f[i][j]$ 发生变化的时候一起更新，但是注意到 $f[i][j]$ 里面 $j$ 是表示重量的，而对应的 $p[i][j]$ 也是表示重量的，看起来是重复表示了重量，实际上是因为避免 MLE，转移方程的 $j$ 只开到了 $W$(1000) ,而题目中奶牛的重量和可能远大于这个值，在 $j>W$ 时可以把它累积到 $j=W$ 也就是 $f[i][W]$ 来转移，但是要对应真实的重量和，所以新设的 $p[i][j]$ 是用来表示 $f[i][j]$ 对应的实际重量和

边界为 $f[1][w[1]]=t[1]\div w[1]$，最后的答案在 $f[1\to n][W]$ 里面取最大值

**代码：**

```cpp
#include <cstdio>
#include <cstring>
#include <queue>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#define maxn 251
#define maxs 1001
#define v(x) (x>maxw?maxw:x)
using namespace std;
template<typename t>inline void fcin(t &x){
	int sign=1; x=0; char op=getchar();
	while(op<'0'||op>'9'){if(op=='-') sign=-1;op=getchar();}
	while(op>='0'&&op<='9'){x=x*10+(op-48);op=getchar();}
	x*=sign;
}
int n,maxw;
int t[maxn],w[maxn];
int s[maxn][maxs],p[maxn][maxs];
double f[maxn][maxs];
inline void dp(){
	f[1][v(w[1])]=(double)t[1]/(double)w[1];
	s[1][v(w[1])]=t[1];p[1][v(w[1])]=w[1];
	for(int i=1;i<=n-1;i++)
	for(int j=0;j<=maxw;j++){
		if(f[i][j]>f[i+1][j]){
			f[i+1][j]=f[i][j];
			s[i+1][j]=s[i][j];
			p[i+1][j]=p[i][j];
		}
		if((double)(s[i][j]+t[i+1])/(double)(p[i][j]+w[i+1])>f[i+1][v(p[i][j]+w[i+1])]){
			f[i+1][v(p[i][j]+w[i+1])]=(double)(s[i][j]+t[i+1])/(double)(p[i][j]+w[i+1]);
			s[i+1][v(p[i][j]+w[i+1])]=s[i][j]+t[i+1];
			p[i+1][v(p[i][j]+w[i+1])]=p[i][j]+w[i+1];
		}
	}
	double ans=0.0;
	for(int i=1;i<=n;i++) ans=max(ans,f[i][maxw]);
	ans*=1000.0;
	printf("%lld",(long long)ans); 
}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("show.in","r",stdin);
	freopen("show.out","w",stdout);
	#endif
	fcin(n);fcin(maxw);
	for(int i=1;i<=n;i++)
		fcin(w[i]),fcin(t[i]);
	dp();
	return 0;
}

```

---

## 作者：Rec° (赞：1)

这道题题解上来就说了转移       
完全看不懂啊       
虽然像我这么菜的虽然不多但肯定也有哇
所以我觉的应该顺带提一下大家觉得很简单但我却不会的01分数规划
## 推荐访问[juruo博客](https://rec.ac.cn/?p=324)观看（格式问题）
[luogup4377](https://www.luogu.org/problemnew/show/P4377 "luogup4377")      
这道题比较模板     
转移方程不难推出   
$\sum (T_i - min W_i) \ge 0$    
就是加了一个w的限制条件     
只需要用01背包来转移就好了
代码看官方题解吧（懒     
然后想一想
这样会的可能比较扎实   
[usaco](http://www.usaco.org/current/data/sol_talent_gold_open18.html "usaco")

---

