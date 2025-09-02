# バームクーヘン (Baumkuchen)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joi2014ho/tasks/joi2014ho3

JOI 君は妹の JOI 子ちゃんと JOI 美ちゃんと一緒におやつを食べようとしている．今日のおやつは $ 3 $ 人の大好物のバームクーヘンだ．

バームクーヘンは下図のような円筒形のお菓子である．$ 3 $ 人に分けるために，JOI 君は半径向に刃を $ 3 $ 回入れて，これを $ 3 $ つのピースに切り分けなければならない．ただしこのバームクーヘンは本物の木材のように固いので，刃を入れるのは簡単ではない．そのためこのバームクーヘンにはあらかじめ $ N $ 個の切れ込みが入っており，JOI 君は切れ込みのある位置でのみ切ることができる．切れ込みに $ 1 $ から $ N $ まで時計回りに番号をふったとき，$ 1\ \leqq\ i\ \leqq\ N\ -\ 1 $ に対し，$ i $ 番目の切れ込みと $ i\ +\ 1 $ 番目の切れ込みの間の部分の大きさは $ A_i $ である．また $ N $ 番目の切れ込みと $ 1 $ 番目の切れ込みの間の部分の大きさは $ A_N $ である．

![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_joi2014ho3/5c087c509e50fd3943f3a436bd121047a3ea6c93.png)図 1: バームクーヘンの例 $ N\ =\ 6 $，$ A_1\ =\ 1 $，$ A_2\ =\ 5 $，$ A_3\ =\ 4 $，$ A_4\ =\ 5 $，$ A_5\ =\ 2 $，$ A_6\ =\ 4 $



妹思いの JOI 君は，バームクーヘンを $ 3 $ つのピースに切り分けたあと，自分は最も小さいピースを選び，残りの $ 2 $ つのピースを $ 2 $ 人の妹にあげることにした．一方で，JOI 君はバームクーヘンが大好物なので，できるだけたくさん食べたいと思っている．最も小さいピースの大きさが最大になるように切ったとき，JOI 君が食べることになるピースの大きさはいくらになるだろうか．

## 说明/提示

### 課題

切れ込みの個数 $ N $ と，各部分の大きさを表す整数 $ A_1,\ \ldots,\ A_N $ が与えられる．バームクーヘンを $ 3 $ つに切り分けたときの，最も小さいピースの大きさの最大値を出力するプログラムを作成せよ．

- - - - - -

### 制限

すべての入力データは以下の条件を満たす．

- $ 3\ \leqq\ N\ \leqq\ 100\,000 $．
- $ 1\ \leqq\ Ai\ \leqq\ 1\,000\,000\,000 $ ($ 1\ \leqq\ i\ \leqq\ N $)．

### 小課題

#### 小課題 1 \[5 点\]

$ N\ \leqq\ 100 $ を満たす．

#### 小課題 2 \[15 点\]

$ N\ \leqq\ 400 $ を満たす．

#### 小課題 3 \[30 点\]

$ N\ \leqq\ 8\,000 $ を満たす．

#### 小課題 4 \[50 点\]

追加の制限はない．

- - - - - -

### Sample Explanation 1

!\[\](https://img.atcoder.jp/joi2014ho/2014-ho-t3-fig02.png)図 2: $ 1 $ 番目の切れ込みと $ 3 $ 番目の切れ込みと $ 5 $ 番目の切れ込みで切るのが最善である． - - - - - -

## 样例 #1

### 输入

```
6
1
5
4
5
2
4```

### 输出

```
6```

## 样例 #2

### 输入

```
30
1
34
44
13
30
1
9
3
7
7
20
12
2
44
6
9
44
31
17
20
33
18
48
23
19
31
24
50
43
15```

### 输出

```
213```

# 题解

## 作者：Karieciation (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/AT_joi2014ho3)

这里给出一种巧妙~~偷鸡~~的方法。

## 题目分析

我们观察题目，知道：**把蛋糕切成 3 份分给 3 人；蛋糕是“环”，且每块蛋糕是正整数；哥哥一定拿的最少**。

**寥寥 3 个条件，却成为解题关键！**

## 如何分类

当该蛋糕为环时，只有 2 种情况：**“妹哥妹”，“妹妹哥”**

这样分类有个好处：



||第一组|第二组|
|:-:|:-:|:-:|
|1|妹|哥妹|
|2|妹|妹哥|

通过观察，我们发现，我们完全可以通过二分（因为正整数前缀和具有单调递增性）设置断点分成三块（两个断点），分成两组，并只在第二组里分类讨论。

为了方便使用环，我们需要**破环成双倍的链**。

## 设置断点

接下来就是我们应如何设置这两个断点。

我们用 $\operatorname{lower\_bound}()$ 找断点。

我们就顺次枚举区间 $[i,i+n-1](1\le i\le n) $。

我们设蛋糕总体积是 $all$，第一个妹妹拿 $num_1$ 体积的蛋糕，第二个妹妹拿 $num_2$ 体积的蛋糕。

我们知道哥哥一定拿的最少，也就是说哥哥最多拿 $\lfloor\dfrac{all}{3}\rfloor$。

由此我们得出：至少有一个妹妹拿了大于等于 $\lceil\dfrac{all}{3}\rceil$ 的蛋糕体积。

我们此时就可求出第一个断点 $x$：

$$x=\operatorname{lower\_bound}(sum+i,sum+i+n,sum[i-1]+num_1)$$

此时，剩余蛋糕为 $all-(sum[x]-sum[i-1])$，另一个妹妹拿了大于等于 $\lceil\dfrac{all-(sum[x]-sum[i-1])}{2}\rceil$ 的蛋糕体积。

然后可确定第二个断点：

$$y=\operatorname{lower\_bound}(sum+x+1,sum+i+n,sum[x]+num_2)$$

~~(二分光荣地滚蛋了)~~。

## 细节处理（分类讨论）

**重重重点来了！！！**

我们发现，此时我们仅仅维护了“妹妹哥”这种情况，如何维护“妹哥妹”呢？

由于我们的蛋糕是正整数，所以我们知道 $sum[y-1]-sum[x]<sum[i+n-1]-sum[y-1]$ 这是一定成立的，所以“妹哥妹”也维护好啦！！！

由此，我们得出：

$$ans=\max_{i=1}^n(sum[i+n-1]-sum[y],sum[y-1]-sum[x])$$

## $Code$
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+5;
template<typename T>void read(T& x)
{
	x=0;char ch=getchar();ll f=1;while(ch<48||ch>57){if(ch==45)f=-1;ch=getchar();}
	while(ch>47&&ch<58)x=(x<<3)+(x<<1)+(ch&15),ch=getchar();x*=f;
}
template<typename T>void write(T x)
{
	if(x<0){putchar(45);x=-x;}
	if(x>9)write(x/10);
	putchar(x%10|48);
}
int n;
ll a[N];
ll sum[N];//记录前缀和
ll num;//记录第一个妹妹至少拿到多少蛋糕
ll all;// 记录蛋糕体积
ll ans;
int main()
{
	read(n);
	for(int i=1;i<=n;i++)
	{
		read(a[i]);
		sum[i]=sum[i-1]+a[i];
	}
	for(int i=n+1;i<(n<<1);i++)
		sum[i]=sum[i-1]+a[i-n];
	all=sum[n],num=all/3+(bool)(all%3);
	for(int i=1;i<=n;i++)
	{
		int x=lower_bound(sum+i,sum+i+n,num+sum[i-1])-sum;//第一个断点
		if(x==i+n-1)
			continue;
		ll num2=(all+(sum[x]-sum[i-1])>>1)+(all+(sum[x]-sum[i-1])&1);//记录第一个妹妹至少拿到多少蛋糕
		int y=lower_bound(sum+x+1,sum+i+n,num2+sum[x])-sum;//第二个断点
		ans=max(ans,max(sum[i+n-1]-sum[y],sum[y-1]-sum[x]));
	}
	write(ans);putchar('\n');
	return 0;
}
```

## 结语

感谢大家的观看，学到了记得留赞哦。 

***

---

## 作者：Sincerin (赞：3)

[题目传送门！](https://www.luogu.com.cn/problem/AT_joi2014ho3)

[更好的阅读体验？](https://www.luogu.com.cn/blog/sincerin520/solution-at-joi2014ho3)


**前言**：模拟赛出了这题原题，但是当时的我沉迷于推导前一题组合数的柿子并在上面花费了两个半小时然后成功爆蛋了![](//图.tk/1)。赛场上没来得及读这题，结果考完一看发现他喵的这题比上一题简单多了。心态有点炸裂，于是我就决定了要写这篇题解。



## 题意

雪豹排了很长很长时间的队才买到了传说中雪市最美味的年轮蛋糕。但是这种蛋糕太硬了，所以雪豹在切蛋糕时只能按照老板娘切好的 $n$ 个切口把蛋糕切成 $n$ 块（因为蛋糕是环形的，所以 $n$ 个切口可以分成成 $n$ 块）。蛋糕的形状是均匀的，第 $i$ 块与 第 $i+1$ 块之间有一块体积为 $a_i$ 的蛋糕。这时，同住雪市的食雪汉和東雪莲来蹭饭了。出于我中华传统文化的待客之道，雪豹想用三刀将蛋糕切成三块，自己吃最小的那块。但是他又想吃的尽可能多，那你能帮帮他吗？

- $3 \leq n \leq 10^5$ 
- $1 \leq a_i \leq 10^9(i \in [1,n])$ 


## 解析

首先题目明确说了要求三块中的最小值尽可能的大，也就是最小值最大化一类的题目，一眼二分。我们可以二分雪豹分到的蛋糕的体积，即最小值的大小，然后判断这个值是否合法（是否可以由其中连续的一段蛋糕“拼”出来）。

首先就是预处理部分，我们可以在输入时求出 $a$ 的前缀和数组 $sum$，即  $sum_i=\sum_{j=1}^i a_j$，同时 $\sum_{i=l}^r a_i=sum_r-sum_{l-1}$。处理出前缀和数组对于每一段体积和的计算和码长的减少都有很大帮助。

还有一个问题就是这个蛋糕是个环。对环的处理方式一般分为两种，第一个就是在变量循环到 $n$ 时特判一下，再次回到开头。还有一种方法就是“破环为链”，也就是把原序列复制一份放到末尾，使得原序列变为长度为 $2n$ 的序列，造成伪环。在这里我采用了方法二来处理。

前戏差不多了，那么二分判断函数 `check(mid)` 该怎么写呢？

首先大家肯定都能想到两层循环来枚举前两刀的位置，这样第二三块的长度也可以确定了(只要让第二块蛋糕的体积大于等于 `mid`，判断第三块即可)。时间复杂度为 $\Theta(n^2)$。算上最外层的二分，总时间复杂度在 $\Theta(n^2 \log_2 \sum_{i=1}^n a_i)$ 级别，只能过掉前两个总共 $20$ 分的子任务。

既然内层枚举过不了，我们可以思考一下，由于每一块蛋糕的体积都是正整数，加上一块蛋糕只会让整段蛋糕的总体积变大，所以符合单调递增函数的单调递增性，我们可以考虑在后两刀的选择时进行二分，时间复杂度降为 $\Theta (n  \log_2 n )$，总时间复杂度为 $\Theta(n \log_2 n \log_2 \sum_{i=1}^n a_i)$，已经足够通过本题了。

但是这还没完，如果有同学比较熟悉双指针，那么他一定能发现，当我们最外层 $\Theta(n)$ 枚举第一刀的时候，每次都会确定后两刀的位置。但其实第一次确定第一刀位置时，我们就可以确定第一对合法的后两刀，使得切出的前两块蛋糕的体积均大于等于 `mid`。随着第一刀的后移，第一块的体积会减小。我们要确保第一块和第二块蛋糕的体积均大于等于 `mid`，则第二刀和第三刀都是要么原地不动，要么后移，不可能往前移。这样一来，后两刀的位置也不需要每次都从头枚举，其实就相当于两个指针在外层的 $\Theta(n)$ 循环中各移动 $n$ 次，时间复杂度还是 $\Theta(n)$。总时间复杂度为 $\Theta(n \log_2 \sum_{i=1}^n a_i)$。


## AC Code

```cpp

//C++14(GCC 9)  1.05KB  43ms  5.76MB 
#include<iostream>
#include<cstdio> 
using namespace std;
#define ri register int
#define _ 0
const int N=100005;
long long n,m,l,r,a[N];//开long long! 
long long sum[N<<1],ans;
inline bool check(long long x)
{
	long long  k1=1,k2=1;
	for(ri i=1;i<=n;++i)
	{
		ri lt=i,rt=i+n;//注意a[i]表示第i~i+1个切口之间的距离,sum[i+n]-sum[i]表示第i+1~i+n+1个切口之间的距离
		while(sum[k1]-sum[lt]<x&&k1<rt) ++k1;//加上"k1<rt",防止数据极小，一直累加导致越界RE 
		while(sum[k2]-sum[k1]<x&&k1<rt) ++k2;
		if(sum[rt]-sum[k2]>=x) return true;//剩下的还够mid，可以继续增加mid
	} 
	return false;
} 
signed main(void)
{
	std::ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL); //cin,cout优化 
	cin>>n;
	for(ri i=1;i<=n;++i) 
	{
		cin>>a[i];
		sum[i]=sum[i-1]+a[i];//前缀和 
	}
	for(ri i=n+1;i<=(n<<1);++i) sum[i]=sum[i-1]+a[i-n];//破环为链
	l=0,r=sum[n]/3;//由于最短的一段不可能超过sum[n]/3,故上界r=sum[n]/3 
	while(l<=r)//二分最短段的长度 
	{
		long long  mid=(l+r)>>1; //(l+r)>>1相当于(l+r)/2向零舍入 
		if(check(mid)) 
		{
			l=mid+1;
			ans=mid;
		}
		else r=mid-1;
	}
	cout<<ans<<"\n";//AT好像必须换行？ 
	return ~~(0^_^0);//完结撒花！ 
}
```

[AC Record](https://www.luogu.com.cn/record/116675408)




---

## 作者：BqtMtsZDnlpsT (赞：3)

~~二分查找胜利~~，获得 Um_nik 的保佑。

$\large\text{Solution:}$

首先看到了 “最短的一段长度尽可能的长”，就想到了二分答案。

考虑二分最短一段的值。当前最短一段的值为 $x$ 的时候我们先枚举一个断点，贪心地找出前两段（使这两段的和分别大于 $x$，且最小，这样能在满足条件的情况下使第三段最大），再比较第三段（由于前两段值确定，第三段随之确定）是否大于 $x$。

考虑如何找从一点开始 $>x$ 的最小的段：由于从一个点开始的数之和有单调性，可以二分。

这样一来，复杂度为 $O(n\log \sum{A_i}\log n)$，由于 $n\le10^5$ 可以通过。

代码：
```cpp
//记得开long long
int n,a[100005],s[100005];
int Gem(int l,int r){
	if(l<=r)return (l+r)>>1;
	int pp=(l+r+n)>>1;
	if(pp<=n)return pp;
	return pp%n;
}
int Q(int l,int r){//计算环上一段区间和
	if(l<=r)return s[r]-s[l-1];
	return s[n]-s[l-1]+s[r]; 
}
int D(int x){
	if(x==1)return n;
	return x-1;
}
bool check(int x){
	for(int i=1;i<=n;i++){
		int l=i,r=D(i);//D(i)求出比 i 小1的位置（由于是个环，需要特判一下）
		while(l!=r){//二分下一个断点
			int mid=Gem(l,r);//在环上找二分中点
			if(Q(i,mid)>=x)r=mid;//如果当前一段区间和满足条件，右端点缩进
			else l=mid%n+1;
		}
		int ll=l%n+1,rr=D(i);
		while(ll!=rr){//同理找下一个断点
			int mid=Gem(ll,rr);
			if(Q(l%n+1,mid)>=x)rr=mid;
			else ll=mid%n+1;
		}
		if(Q(i,l)<x)continue;
		if(Q(l%n+1,ll)<x)continue;//如果有任意一个找出来的答案不满足条件（无法找到），则失败，找下一个断点
		if(ll%n+1==i)continue;//如果第 3 段长度为 0，失败
		int u=Q(ll%n+1,D(i));
		if(u>=x)return 1;//如果第 3 段长度符合条件，则成功。
	}
	return 0;
}
signed main(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read(),s[i]=s[i-1]+a[i];//前缀和方便计算区间和
	int l=0,r=s[n],ans=0;
	while(l<=r){//二分最短一段的长度
		int mid=(l+r)>>1;
		if(check(mid))l=mid+1,ans=mid;
		else r=mid-1;
	}
	cout<<ans<<'\n';
}

```

---

## 作者：_HCl_ (赞：2)

二分好题，但建议评绿。

# JOI2014HO3 题解

**题意简述**

一个圆环由 $n$ 段组成，每段长度是 $A-i$，现在希望切成 $3$ 段，使得最短的一段最长。

**思路引导**

由于是一条环，又要求换上一段的长度，容易想到开环为链，然后求前缀和处理。

我们先暴力枚举最小的一段的起始点 $cut_1$，然后二分枚举最小的一段的长度 $len$。

接下来考虑怎么检验 $len$ 是否能满足。还是使用二分法处理。我们从第二个切割点 $cut_2$ 开始，二分枚举出第一个点 $p$，满足 $cut_2 \sim p$ 的长度 $\geq len$，作为 $cut_3$。

最后在检测 $(cut_3+1)\sim (cut1-1)$ 的长度是否 $\geq len$ 即可。

注意开 `long long`，注意输出后要换行。

**代码**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,ANS;
int a[2000001],s[2000001];
int calc(int bg,int len){
	int l=bg,r=n+bg-1,ans;
	while(l<=r){
		int mid=(l+r)>>1;
		if(s[mid]-s[bg-1]>=len)ans=mid,r=mid-1;
		else l=mid+1;
	}
	return ans;
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;++i)scanf("%lld",a+i),a[n+i]=a[i];
	for(int i=1;i<=2*n;++i)s[i]=s[i-1]+a[i];
	for(int i=1;i<=n;++i){
		int l=0,r=s[n],ans;
		while(l<=r){
			int mid=(l+r)>>1;
			int cut2=calc(i,mid);
			int len=s[cut2]-s[i-1];
			int cut3=calc(cut2+1,len);
			if(s[n+i-1]-s[cut3]>=len)ans=mid,l=mid+1;
			else r=mid-1;
		}
		ANS=max(ANS,ans);
	} 
	cout<<ANS<<"\n";
	 
}
```

---

## 作者：Wei_Han (赞：1)

首先我们发现答案是具有单调性的，假如能够获取 $x$ 大小的蛋糕，那么肯定能够获得至少 $y$ 大小的蛋糕，此处 $y<x$，我们考虑直接二分答案，然后断环为链，枚举第一刀的位置，由于我们已经知道了我们第一次要切的长度，可以直接记录前缀和进行二分，这样也就找到了我们第二刀至少需要切到哪里，由于剩下的两块都不能小于第一块的大小，我们以上次二分结果的下一个作为起始点，再次二分找到第一个大于等于第一块大小的位置，这就是第三刀的位置，再判断剩下的最后一块是否也大于第一块即可。注意断环为链要多复制几遍序列。

时间复杂度 $O(n\log^2 n)$。

```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
#define pr putchar('\n')
#define pp putchar(' ')
#define pii pair<ll,ll>
#define pdi pair<ll,ll>
#define mem(aa,bb) memset(aa,bb,sizeof(aa))
#define fo(a,i,b) for(register ll i = a ; i <= b ; ++ i )
#define Fo(a,i,b) for(register ll i = a ; i >= b ; -- i )
#define fi first
#define se second
//#pragma GCC optimize(2)
using namespace std;
typedef long long ll;
typedef double db;
const int N=5e5+10,M=1e7+5;
inline void read(ll &opp){ll x=0,t=1;char ch;ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-'){t=-1;}ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}opp=x*t;return; }
inline void wr(ll x){if(x<0){putchar('-');x=-x;}if(x>9){wr(x/10);}putchar(x%10+'0');}

ll n,a[N],pre[N],ans;

inline bool check(ll midd){
	ll flag=0;
	fo(1,i,n){
		ll l=i,r=n*2;
		while(l<r){
			ll mid=l+r>>1;
			if(pre[mid]-pre[i-1]>=midd) r=mid;
			else l=mid+1; 
		}
		ll now=l,sum=pre[l]-pre[i-1];
		if(pre[l]-pre[i-1]<midd) continue;
		l=now+1,r=n*4;
		while(l<r){
			ll mid=l+r>>1;
			if(pre[mid]-pre[now]>=sum) r=mid;
			else l=mid+1;
		}
		if(pre[l]-pre[now]<sum) continue;
		if(ans-sum-pre[l]+pre[now]<sum) continue;
		return 1;
	}
	return 0;
}

signed main(){
	read(n);fo(1,i,n) read(a[i]),a[i+n]=a[i+2*n]=a[i+3*n]=a[i],ans+=a[i];
	fo(1,i,n*4) pre[i]=pre[i-1]+a[i];
	ll l=1,r=1e15;
	while(l<r){
		ll mid=l+r+1>>1;
		if(check(mid)) l=mid;
		else r=mid-1;
	} 
	wr(r);pr;
	return 0; 
}	
``````

---

## 作者：TruchyR (赞：1)

## Part 1 思路
发现这东西满足单调性，可以二分。  
可以先枚举第一刀的位置，然后二分最终答案。  
判断函数内可以二分找到第二刀和第三刀的位置，判断是否合法即可。  
时间复杂度 $O(n\log{n}\sum_{i=1}^{n}A_i)$。  
部分思路见代码注释。  
## Part 2 代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define MX 200005
//由于是还所以开两倍方便一些
#define CKE if(CHECK)
using namespace std;
const int CHECK=0;
int s,e,n,sm,res,a[MX];
int fd(int st,int r,int yq){
	int l=st;//以st开头，找一个最小的r使得a[st~r]>=yq
	while(l<r){
		int mid=(l+r)>>1;
		if(a[mid]-a[st-1]>=yq) r=mid;
		else l=mid+1;
	}return r;
}
bool ck(int t){
	int mt=fd(s,e,t);//第二刀
	CKE cout<<mt<<' ';
	if(a[mt]-a[s-1]<t) return false;//一二刀间判断
	int mf=fd(mt+1,e,t);//第三刀
	CKE cout<<mf<<' ';
	if(a[mf]-a[mt]<t) return false;//二三刀间判断
	CKE cout<<e<<' ';
	if(a[e]-a[mf]<t) return false;//一三刀间判断
	CKE cout<<'T';
	return true;
}
signed main(){
	//带CKE的输出是测试输出
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];sm+=a[i];
		a[i+n]=a[i];//环
	}
	for(int i=1;i<=n*2;i++)
		a[i]+=a[i-1];//前缀和
	for(s=1;s<=n;s++){//枚举起始点
		e=s+n-1;//在数组内的终点
		int L=res,R=sm;//sm是A[i]的和
		CKE cout<<s<<' '<<e<<":\n";
		while(L<R){
			int Mid=(L+R+1ll)>>1ll;
			CKE cout<<"- "<<Mid<<'\n';
			if(ck(Mid)) L=Mid;
			else R=Mid-1ll;
			CKE cout<<'\n';
		}CKE cout<<'\n';
		res=max(res,L);
	}cout<<res<<'\n';//记得换行！
	return 0;
}

```


---

## 作者：wwh177 (赞：0)

# AT_joi2014ho3 题解

## 这是一个半自动题解自测程序
由于题解审核没过很多次，就写了这个玩意并水了一贴。链接：[基于题解审核的半自动题解自测程序](https://www.luogu.com.cn/discuss/727540)。

## 这里提供一份题面翻译
JOI 正在和 JOI 子、JOI 美一起吃点心。今天的点心是三人喜欢的年轮蛋糕。

年轮蛋糕是像下图一样的圆桶状点心。由于要分给三人，JOI 要沿着半径方向切三刀，将蛋糕分成三块。但是这个年轮蛋糕像木头一样坚硬，想切下去并不容易。因此这个年轮蛋糕预留了 $N$ 个切口。JOI 可以从这些位置切下去。切口从 $1$ 到 $N$ 顺时针编号，对于 $ 1 \le i \le N - 1 $，第 $i$ 个切口和第 $i+1$ 个切口中间部分大小为 $A_i$，第 $N$ 个切口和第 $1$ 个切口中间部分大小为 $A_N$。

图 $1$：年轮蛋糕的例子。$N=6,A_1=1,A_2=5,A_3=4,A_4=5,A_5=2,A_6=4$

顾及妹妹们的 JOI 将年轮蛋糕分成 $3$ 块，自己选了最小的一块，剩下两块分给两个妹妹。与此同时，JOI 很喜欢年轮蛋糕，希望能够多吃一点。求最小部分最大时，JOI 能吃的蛋糕最大为多少。

输入格式：从标准输入中读入以下数据：  
第一行一个整数 $N$，表示年轮蛋糕有 $N$ 个切口。  
接下来 $N$ 行中，第 $i$ 行（$1 \le i \le N$）输入整数 $A_i$，表示第 $i$ 个与第 $i+1$ 个切口中间部分的大小（$i=N$ 时表示第 $N$ 个与第 $1$ 个切口之间部分的大小）。

输出格式：  
从标准输出中输出一个整数，表示年轮蛋糕切成 $3$ 块时，最小部分最大值。

[图 2](https://img.atcoder.jp/joi2014ho/2014-ho-t3-fig02.png)：从第 $1/3/5$ 切口切入时得到最优解。


------------
## 题意
需要将这个圆环从切口处分成三段，要求其中一段的长度严格小于另外两段。求：最短的一段的最大长度。

## 思路
数据范围给到了 $10^5$，所以 $ O(n^2)$ 会炸。所以考虑 $O(n\log{n})$  级别的。注意到题目要求求最值，而这个蛋糕每个块的大小都为正整数，具有单调性，所以可以考虑到二分求解。  
所以：
### Act 0 处理环
这个可以直接拆环成链，才 $10^5$，空间管够。
### Act 1 枚举起点
用一个 $O(n)$ 的复杂度枚举最小那块蛋糕的起始位置。  
Q：为什么要枚举起点？  
A：对于每个起点来说，最后得到的答案有可能不同（因为起点其实也是切的三刀之一）。
### Act 2 二分答案
一个朴素的二分，枚举最小部分的大小。  
其中，$l=0$（其实严格来说应该是 $A_1$ 至 $A_i$ 的和，但直接赋 $0$ 也对），$r$ 表示整块蛋糕大小。
### Act 3 二分查找第二刀位置
这里需要满足后两块蛋糕的大小都大于第一块（即二分枚举的那个数值）。

---

然后呢，这题就完了。
## 代码（带注释）
```cpp
//你觉得直接抄能过吗？(^_^)
//没错，直接抄能过（你谷：不应在代码中加入防抄袭内容。）
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[200005];
int sum[200005],l,r,m,L,R,M,p,q,v,ans;
int Sol(int s,int ms)//处理从 s 开始，总大小大于等于 ms 的最早位置
{
	L=s;
	R=s+n;
	while(R>L+1)//二分查找位置
	{
		M=(L+R)/2;
		if(sum[M]-sum[s-1]>=ms)
		{
			R=M;
		}
		else
		{
			L=M;
		}
	}
	return (sum[L]-sum[s-1]>=ms)?L:R;
}
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		a[i+n]=a[i];
	}
	for(int i=1;i<=n*2;i++)//前缀和的处理
	{
		sum[i]=a[i]+sum[i-1];
	}	
	for(int i=1;i<=n;i++)
	{
		l=0;
		r=sum[n];
		while(r>l+1)//二分枚举答案
		{
			m=(l+r)/2;
			p=sol(i,m);
			v=sum[p]-sum[i-1];
			q=sol(p+1,v);
			if(sum[i+n-1]-sum[q]>=v&&m*3<sum[n])
			{
				l=m;
			}
			else
			{
				r=m;
			}
		}
		ans=max(ans,l);
	}
	cout<<ans<<endl;
}
```


---

## 作者：ningago (赞：0)

坏了，根本不会贪心。

二分套三分大法好耶！

由于要最大化最小值，所以二分最小长度 $mid$。

然后判断另外两段的长度是否可以都 $\geq mid$ 即可。

问题就变成了：给定一段区间，求把区间劈成两半后，长度小的那一段的最大长度。

不难发现这是个凸函数。

三分即可。

总体复杂度 $O(\log\sum A\cdot n\cdot \log n)$。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>

#define N 200010
#define int long long

int n,m;
int a[N];
int pre[N];

int checkcheck(int L,int R)
{
	int l = L,r = R - 1,res = 0;
	while(l <= r)
	{
		int mid1 = l + (r - l) / 3;
		int mid2 = r - (r - l) / 3;
		int t1 = std::min(pre[mid1] - pre[L - 1],pre[R] - pre[mid1]);
		int t2 = std::min(pre[mid2] - pre[L - 1],pre[R] - pre[mid2]);
		if(t1 <= t2)
		{
			res = std::max(res,t2);
			l = mid1 + 1;
		}
		else
		{
			res = std::max(res,t1);
			r = mid2 - 1;
		}
	}
	return res;
}

bool check(int mid)
{
//	printf("mid = %lld\n",mid);
	int r = 0,now = 0;
	for(int i = 1;i <= n;i++)
	{
		while(r < m && now < mid)
			now += a[++r];
		if(now >= mid && i + n - 1 - r >= 2)
		{
			if(checkcheck(r + 1,i + n - 1) >= mid)
				return 1;
		}
		now -= a[i];
	}
	return 0;
}

signed main()
{
	scanf("%lld",&n);
	m = n << 1;
	for(int i = 1;i <= n;i++)
	{
		scanf("%lld",&a[i]);
		a[i + n] = a[i];
	}
	for(int i = 1;i <= m;i++)
		pre[i] = pre[i - 1] + a[i];
	int l = 0,r = 1e14,ans = 0;
	while(l <= r)
	{
		int mid = (l + r) >> 1;
		if(check(mid))
		{
			ans = mid;
			l = mid + 1;
		}
		else
			r = mid - 1;
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：WAAutoMaton (赞：0)

[先宣传一波博客（逃](https://waautomaton.tk/2018/08/12/loj-2758-%E9%A2%98%E8%A7%A3/)

#### 题解

&emsp;&emsp;套路题，首先先二分答案，然后枚举第一刀切口，贪心找出第二刀和第三刀的位置，判是否合法即可，由于后两刀位置是单调变化的所以单次check复杂度$O(n)$，总复杂度$O(n \log n)$

#### 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

template <size_t _I_Buffer_Size = 1 << 23, size_t _O_Buffer_Size = 1 << 23>
struct IO_Tp
{
    //这是读入优化板子，为了阅读体验此部分内容省略。
};
 IO_Tp<> IO;
const int maxn=3*100000;
int a[maxn+10];
LL sum[maxn+10];
	int n;
LL calc(int l,int r)
{
	if (l<=r) return sum[r]-sum[l];
	else return 0;
}
bool check(LL mid)
{
	int p1=0,p2=0,p3=0;
	for(p1=0; p1<2*n; ++p1) {
		while(p2<=3*n && calc(p1,p2)<mid) ++p2;
		while(p3<=3*n && calc(p2,p3)<mid) ++p3;
		if (p3>3*n) return false;
		if (calc(p3,p1+n)>=mid) return true;
	}
	return false;
}
int main()
{
	iopen();
	IO>>n;
	for(int i=1; i<=n; ++i) {
		IO>>a[i];
		sum[i]=sum[i-1]+a[i];
	}
	for(int i=1; i<=n; ++i) {
		a[n+i]=a[i];
		sum[n+i]=sum[n+i-1]+a[n+i];
	}
	for(int i=n+1; i<=2*n; ++i) {
		a[n+i]=a[i];
		sum[n+i]=sum[n+i-1]+a[n+i];
	}
	LL l=0,r=sum[n];
	while(l<r) {
		LL mid=(l+r+1)/2;
		if (check(mid)) l=mid;
		else r=mid-1;
	}
	IO<<r<<'\n';
    return 0;
}




```



---

