# [NOI Online #3 入门组] 买表

## 题目描述

Jimmy 到 Symbol 的手表店买手表，Jimmy 只带了 $n$ 种钱币，第 $i$ 种钱币的面额为 $k_i$ 元，张数为 $a_i$ 张。Symbol 的店里一共有 $m$ 块手表，第 $i$ 块手表的价格为 $t_i$ 元。

Symbol 的手表店不能找零，所以 Jimmy 只能在凑出恰好的钱数时才能购买一块手表。现在对于店里的每块手表，Jimmy 想知道他能不能凑出恰好的钱数进行购买。


## 说明/提示

#### 样例 1 解释

- 第二块手表 $19=6 \times 3+1=6 \times 2+5+1 \times 2$，可以恰好凑出。
- 第四块手表 $1=1 \times 1$，可以恰好凑出。
- 第五块手表 $7=5+2\times 1=6 \times 1+1$，可以恰好凑出。

#### 数据规模与约定
- 对于 $50\%$ 的数据，保证 $n\leq 10$，$m \leq 60$，$a_i \leq 20$，$k_i \leq 5000$，$t_i \leq 250$。
- 对于 $100\%$ 的数据，保证 $1 \leq n \leq 200$，$1 \leq m \leq 10^5$，$1 \leq a_i \leq 1000$，$1 \leq k_i \leq 500000$，$0 \leq t_i \leq 500000$。

#### 说明

data provider：@皎月半洒花。

## 样例 #1

### 输入

```
3 5
1 2
5 1
6 3
3 19 21 1 7```

### 输出

```
No
Yes
No
Yes
Yes
```

# 题解

## 作者：critnos (赞：40)

考场上的错误：

1. 输出大小写

2. 二进制优化写挂/kk

这个题目就是变形的多重背包，那么不难想到，用一个 $5\times 10^5$ 的 bool 数组来 dp 每个数能否被选中。

但是这样极限数据是 $200 \times 1000\times 5\times 10^5$，直接爆炸，只能拿 $50\ \text{pts}$。

接下来就是套路性的优化多重背包了：**二进制优化**。

比如有 $a$ 个价值为 $b$ 的物品，那么他们能组合出的就是 $1\times b,2\times b,\dots a\times b$ 价值的物品。

那么能不能构造另一些物品，让这些物品同样能组合出 $1\times b,2\times b,\dots a\times b$ 价值的物品呢？

可以的。

我们需要构造的是价值为 $1\times b,2\times b,4\times b,\dots 2^n\times b$，其中这些物品价值的总和不超过 $a\times b$ 且 $n$ 尽量大。当然最后离 $a\times b$ 可能还有一些距离，所以要用一个价值为 $(a-\sum_{i=1}^n 2^n)\times b$ 来弥补。

用二进制的位值原理法可以得出这个是正确的。首先，除最后的一个物品可以组合出 价值 $1\times b\sim (2^{n+1}-1)\times b$ 价值的物品。然后再搭配最后一个物品就可以组合出全部物品了。

好处是物品数量由 $a$ 下降到了 $\log a$，但是 $200 \times 10\times 5\times 10^5$ 似乎还是过不了 ~~虽然在洛谷的脚造数据可以过~~

那么还有一个好东西：bitset

上面的 dp 看起来是这个样子的：

```cpp
for(j=5e5-l*k;j>=0;j--)
	if(dp[j])
		dp[j+l*k]=1;
```
欸，那不就是位运算吗？说清楚一些，如果把 dp 数组当作一个大 bool 类型，那么这个操作就等同于 `dp|=dp<<l*k`。

正好，万能的 STL 库中就有这个好东西 bitset，本质上是一个 bool 数组（内置是用 ull 压了位），但是仍然支持各种位运算。

这样定义：

```cpp
bitset<500005> dp;
```
操作也很简洁：

```cpp
dp|=dp<<l*k;
```
常数是一般的 bool 数组的 $\dfrac 1 w$，在一般的机子中 $w=64$。

然后凭借卡常技巧卡到了 rank 1/cy

```cpp
#include<bits/stdc++.h>
using namespace std;
bitset<500005> dp;
int main()
{
//	freopen("watch.in","r",stdin);
//	freopen("watch.out","w",stdout);
	int n,m,i,j,a,k,l;
	scanf("%d%d",&n,&m);
	dp[0]=1;
	for(i=0;i<n;i++)
	{
		scanf("%d%d",&k,&a);
		for(l=1;a>=l;l*=2)
		{
			dp|=dp<<l*k;
			a-=l;
		}
		if(a*k)
			dp|=dp<<a*k;	
	}
	while(m--)
	{
		scanf("%d",&k);
		puts(dp[k]?"Yes":"No");
	}
	return 0;
}
```


---

## 作者：翼德天尊 (赞：28)

**一道多重背包的 ~~板子(?)~~ 题**

## STEP 1 分析题意
### 题目条件

1. 有 $n$ 种货币，每种有 $a_i$ 张且价值 $k_i$ 元；

2. 有 $m$ 块手表，每块手表 $t_i$ 元；

3. 分别输出每块手表是否可以刚好买到。

### 答题思路

有经验的同学肯定而已看出来只是一道标准的**多重背包**问题（当然普通背包都不会的同学可以自行先去[这里](https://www.luogu.com.cn/problem/list?tag=139&page=1)的题目的题解里补课），每一个价钱是否可以恰好达到都可以**由该价钱减去未使用货币的面值**演变而来，转移方程易得：
$$dp_j=dp_{j-l\times k_i}|dp_j$$

当然，初始化时 $dp_0$ 一定为 $1$，因为它可以被无条件购买。

该部分代码如下：
```
for (int f=1;f<=m;f++){
	memset(dp,0,sizeof(dp);
	for (int i=1;i<=n;i++){
		for (int j=t[f];j>=0;j--){
			for (int l=0;l<=a[i]&&l*k[i]<=j;l++){
				dp[j]=dp[j-l*k[i]]|dp[j];
			}
		}
	}
	if (dp[f]==1) puts("Yes");
	else puts("No");         
}
```
但是这样就完了吗？？？四维啊！！！这个时间复杂度……我都懒得去计算了……

**所以，怎么优化呢？**

我们可以发现，对于每一种货币搭配，每一个价钱是否能够到达其实是固定不变的，也就是说，我们只要知道一个最大值，其实是可以**只循环一次的！**

代码如下：
```
for (int i=1;i<=n;i++){
	for (int j=maxn;j>=0;j--){//maxn为最大的钱数
		for (int l=0;l<=a[i]&&l*k[i]<=j;l++){
			if (dp[j]==1) break;
			if (dp[j-l*k[i]]==1) dp[j]=1;//小优化，只要它为1就可以直接跳出第三层循环；
		}
	}
}
for (int i=1;i<=m;i++){//m个询问依次处理
	if (dp[t[i]]==1) puts("Yes");
	else puts("No");
}
```
这是我考试的时候写的代码 ~~（90分）~~，~~（实际上数组开小了就50分~~）因为这是三维的，所以还是太慢了，我们要把它**压缩成二维**的！

**代码如下：**
```
for (int i=1;i<=n;i++){//can记录每个价钱是否可以凑到，dp记录每个物品在某个价钱已使用的次数
		memset(dp,0,sizeof(dp));
		for(int j=k[i];j<=maxn;j++){
			if(can[j]==0&&can[j-k[i]]==1&&dp[j-k[i]]<a[i]){//如果该价钱没有到过且该价钱的上一个状态到过并且还有使用次数
				can[j]=1,dp[j]=dp[j-k[i]]+1;//标记
			}
		}
	}
```

## STEP 2 AC code
```
#include<bits/stdc++.h>//万能头
using namespace std;
int n,m,k[201],a[201],t[100001],dp[500001],maxn,can[500001];//如题，注意dp和can要开大，开大！！！
int read(){
	int w=0,f=1;
	char c=getchar();
	while (c>'9'||c<'0'){
		c=getchar();
	}
	while (c<='9'&&c>='0'){
		w=(w<<3)+(w<<1)+(c^48);
		c=getchar();
	}
	return w;
}//快读
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);//优化
	freopen("watch.in","r",stdin);
	freopen("watch.out","w",stdout);//考试必备，洛谷爆0神器
	n=read();m=read();
	for (int i=1;i<=n;i++){
		k[i]=read();a[i]=read();
	}//读入
	for (int i=1;i<=m;i++){
		t[i]=read();
		maxn=max(maxn,t[i]);//取最大值
	}
	can[0]=1;//初始化
	for (int i=1;i<=n;i++){
		memset(dp,0,sizeof(dp));
		for(int j=k[i];j<=maxn;j++){
			if(can[j]==0&&can[j-k[i]]==1&&dp[j-k[i]]<a[i]){
				can[j]=1,dp[j]=dp[j-k[i]]+1;
			}
		}
	}//如上所述
	for (int i=1;i<=m;i++){
		if (can[t[i]]==1) puts("Yes");
		else puts("No");
	}//输出
	return 0;//好习惯++
}

```
**祝这次崩了的同学下次RP++，超常的同学下次RP依旧！**


---

## 作者：Mine_King (赞：10)

安利下[博客]()，若$\LaTeX$挂了请点击“在 Ta 的博客查看”。

先看$50\%$的数据：“对于 $50\%$ 的数据，保证$n \le 10,m \le 60,a_i \le 20,k_i \le 5000,t_i \le 250$。”

考虑朴素多重背包，时间复杂度$O(\sum\limits_{i=1}^n a_i \max\limits_{j=1}^m t_j)$。是可以过的。那么多重背包怎么做呢？设$dp_i$表示能否凑$i$元，那么$dp_0=true$，对于每个$dp_i$，若$\sum\limits_{j=1}^n dp_i-a_j$中的任意一个是$true$则为$true$,否则为$false$。

接下来看$100\%$的数据，想起这个多重背包还有个二进制优化，那么看看加二进制优化后可不可以过吧。

先讲讲二进制优化。普通的多重背包是把物品转换成多个一样的物品，然后做01背包。而这个二进制优化则把这个物品转化成$1,2,4,8,\cdots$个，注意是连续的$2$的次幂个，和倍增什么的不一样。而多余的又分一组。实现起来就是这个亚子：
```cpp
		int aa,vv;//aa表示题目中的ki,vv表示题目中的ai
		aa=read(),vv=read();//读入
		for(rg int j=1;vv-j>=0;j*=2)//从1开始枚举2的次幂，直到剩余的vv不满为止
		{
			a[++cnt]=j*aa;//记录答案
			vv-=j;//更新剩余的vv
		}
		if(vv>0) a[++cnt]=vv*aa;//若有剩余的，则自己分一组
```
之后，就按普通的多重背包做就行了。时间复杂度$O(\sum\limits_{i=1}^n log(a_i) \max\limits_{j=1}^n t_i)$，最多算$1e9$次，加一些常数优化应该是可以过的。

**code：**
```cpp
#include<cmath>
#include<cstdio>
#include<algorithm>
#define rg register
using namespace std;
int T,n,m,mx,cnt,tmp;
int a[2005],v[2005];
int t[500005];
bool dp[500005];
inline int read()//快读
{
    int x=0;int f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
    return x*f;
}
int main()
{
	freopen("watch.in","r",stdin);
	freopen("watch.out","w",stdout);
    //比赛时别忘了写freopen哦！
	n=read(),m=read();
	for(rg int i=1;i<=n;i++)
	{
		int aa,vv;
		aa=read(),vv=read();
		for(rg int j=1;vv-j>=0;j*=2)
		{
			a[++cnt]=j*aa;
			vv-=j;
		}
		if(vv>0) a[++cnt]=vv*aa;
        //读入并二进制拆分（二进制优化的另一种叫法？）
	}
	for(rg int i=1;i<=m;i++)
	{
		t[i]=read();
		if(t[i]>mx) mx=t[i];//记录最大的t，比到时候枚举到500000应该会快一点
	}
	dp[0]=true;//凑0元钱当然是可以的啦
	for(rg int i=1;i<=cnt;i++)
	{
		while(dp[tmp]&&tmp<=mx) tmp++;//tmp表示dp[0~tmp]都是true。
		if(tmp>=mx) break;//若到mx都为true就可以直接跳出了
		int nd=max(tmp,a[i]);//这里直接枚举到max(tmp,a[i])也会快一点
        //一个小优化
		for(rg int j=mx;j>=nd;j--)
			if(dp[j-a[i]]) dp[j]=true;
	}
	for(rg int i=1;i<=m;i++)
		if(dp[t[i]]) printf("Yes\n");
		else printf("No\n");
        //对于每个t[i]，若dp[t[i]]=true则输出Yes，否则输出No
	return 0;
}

```

---

## 作者：__Watcher (赞：6)

提供一种基于二进制拆分优化的多重背包做法。

每一种硬币，都看成是价值等于重量的物品，跑一边多重背包。再对于每一个询问，判断在该重量下能不能使价值等于重量，可以即为 `Yes`，否则为 `No`。

对于普通的多重背包复杂度为 $O(N\times W\times k)$，$W$ 即为该题中 $T_i$ 的最大值，$k$ 即为该题中的 $a_i$ 。$200\times 1000\times 50000 =10^{10}$ 显然不满足题目要求，考虑优化多重背包求法。

之前我们把多重背包拆成 $a_i$ 个 01 背包，我们要优化这种拆分方法。我们的目的是表示 $[1,a_i]$ 的所有数。逐个拆分显然可行，但二进制拆分更优。设 $2^p \le a_i \le 2^{p+1}$，那么我们只需要拆出 $2^0,2^1,2^2 \dots 2^p,a_i-2^p$ 这些数，也能表示 $[1,a_i]$ 的所有数。那么，之前枚举 $a_i$ 的循环现在只用枚举 $[1,p]$，p 是 $\log a_i$ 级别的。至此，总复杂度 $O(N\times W\times \log a_i)$，凭借背包优秀的常数，可以在不开 O2 的情况下通过本题。

附代码，仅供参考：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int M=500000;
int read() {
	int x=0, f=1; char ch=' ';
	while(!isdigit(ch)) {ch=getchar(); if(ch=='-') f=-1;}
	while(isdigit(ch)) x=(x<<3)+(x<<1)+(ch^48), ch=getchar();
	return x*f;
}
int n, m, dp[500005];
int main() {
	cin>>n>>m;
	for(int i=1;i<=n;i++) {
		int w=read(), k=read();
		for(int j=0;j<10;j++) {//拆分过程
			k-=(1<<j);
			if(k>=0) {
				int ww=w*(1<<j);//不再一个个拆了，只拆成 2 的指数幂个
				for(int j=M;j>=ww;j--) {
					dp[j]=max(dp[j], dp[j-ww]+ww);//01 背包代码
				}
			}
			else {
				k+=(1<<j);
				break;
			}
		}
		int ww=w*k;
		for(int j=M;j>=ww;j--) {
			dp[j]=max(dp[j], dp[j-ww]+ww);
		}//剩下的还要打个包
	}
	for(int i=1;i<=m;i++) {
		int x=read();
		if(dp[x]==x) printf("Yes\n");
		else printf("No\n");
	}
}

```


---

## 作者：lndjy (赞：5)

### 来提供一个乱搞做法，不用背包，复杂度是对的

首先，看见询问数多，且询问值域小，那么就可以想到预处理出所有数的答案，用布尔存储。

不过一眼得不出答案，那怎么办呢，先考虑每一种钱的数量都是无限的，那样的话dp做法显然：

`f[0]=1`,因为0一定可以表示。

`if(f[i-cost]) f[i]=1;` 因为如果现在金额减去这个钱可以表示，那么加上这个钱也就是现在的也可以表示。

然后加上个数的限制怎么做呢？可以把数组用int存，存的值是当前是钱用了几次。

转移显然：`f[i]=f[i-cost]+1;`,可以发现，当`f[i-cost]`大于次数时，就用光了，那么不可以转移。

由于对一共多少张没有限制，只对单个面额的有限制，所以每换一个面额就要把所有非零数变成1，用于下次计算。

代码：
```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;
int n,m;
int f[500005];
struct node
{
	int k,a;
}e[205];
bool cmp(node a,node b)
{
	return a.k>b.k;
}
int main()
{
//	freopen("watch.in","r",stdin);
	//freopen("watch.out","w",stdout);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	cin>>e[i].k>>e[i].a;
	sort(e+1,e+n+1,cmp);
	f[0]=1;
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<=500000;j++)
		{
			if(f[j]) f[j]=1;//清空
			if(j-e[i].k>=0) 
			if(f[j-e[i].k]&&f[j-e[i].k]<=e[i].a) f[j]=f[j-e[i].k]+1;//转移
		}
	}
	for(int i=1;i<=m;i++)
	{
		int x;
		cin>>x;
		if(f[x]) cout<<"Yes\n";
		else cout<<"No\n";
	}
	return 0;
}
```


---

## 作者：critnos (赞：3)

upd 2021.6.22

我们在 word-RAM model 中，认为 $w=\Theta(\log n)$（或 $w=\Omega(\log n)$），所以二进制优化的复杂度为 $O(\dfrac {nk\log a} w)=O(nk)$。

---

今天在李煜东的《算法竞赛进阶指南》上看到一种 $O(nk)$ 的方法。

众所周知这道题可以二进制优化达到 $O(nk\log a)$ 的复杂度。（对不起，上已修正）

但是这道题比较特殊，只用判定每个物品是否能被表示出来。

那么考虑一种贪心的思想：

对于放入第 $i$ 个物品，在表示 $j$ 时，有两种可能

1. 状态 $j$ 已经被前 $i-1$ 个物品表示出来，即 $dp_j=1$。

2. 状态 $j$ 没有被前 $i-1$ 个物品表示出来，但状态 $j-i$ 已经被不多于 $a-1$ 个物品表示出来，即 $dp_j=0 \ \text{and} \ dp_{i-j}=1 \ \text{and} \ t_{i-j}<a$。

显然对于情况 $1$ 要尽量选择，迫不得已才选择情况 $2$。

那么我们再设置一个 $t$ 数组用于存放状态被多少个物品表示出来。

```cpp
dp[0]=1;
	while(n--)
	{
		k=read(),a=read();
		memset(t,0,sizeof(t));
		for(i=k;i<=500000;i++)
			if(!dp[i]&&dp[i-k]&&t[i-k]<a)
				t[i]=t[i-k]+1,dp[i]=1;
	}
```
这样的话，虽然理论复杂度优于二进制优化，但是由于其常数大、无法用 `bitset` 优化的原因，速度却远慢于二进制优化了。

---

## 作者：Anita_Hailey (赞：2)



# 乱搞做法

考完tg心态爆炸，来虐pj了，**听说这次pj随便AK?**，orz wyh

实在是好水一个题，看到这个题，我就知道要 **dp**

咋搞，有人说用二进制优化的01背包？，~~没事咱想不到~~。那就试试完全背包

乱搞就完了，设 b[i] 表示为 i 的钱数能不能凑够。然后直接套完全背包，只是个数略有不一样的，就是说我们不能在顺序的dp了，那就正常倒着做呗，枚举用几个钱然后，就水过去了。

稍微的减小了常数。在代码中讲到

```c++
#include <bits/stdc++.h>

#define gc(  ) std::getchar(  )
#define pc( i ) std::putchar( i )

template < typename T >
inline
T read(  )
{
	register T x = 0;
	register char ch = gc(  );
	register bool f = 0;
	while( !std::isdigit( ch ) )
	{
		f = ( ch == '-' );
		ch = gc(  );
	}
	while( std::isdigit( ch ) )
	{
		x = x * 10 + ( ch - '0' );
		ch = gc(  );
	}
	return f ? -x : x;
}

template < typename T >
void
put( T x )
{
	if( x < 0 )
	{
		x = -x;
		pc( '-' );
	}
	if( x < 10 ) {
		pc( x + 48 );
		return;
	}
	put( x / 10 );
	pc( x % 10 + 48 );
	return ;
}

#define Rep( i, j, k ) for( int i = j; i >= k; --i )
#define rdi(  ) read < int > (  )
#define rdl(  ) read < long long > (  )
#define pti( i ) put < int > ( i ), putchar( ' ' )
#define ptl( i ) put < long long > ( i ), putchar( ' ' )
#define For( i, j, k ) for( int i = j; i <= k; ++i )

namespace
RSX
{

const int Maxn = 500001;

int n, m, t[ Maxn ], k[ Maxn ], num[ Maxn ], max;

bool b[ Maxn ];

void
fakemain(  )
{
	n = rdi(  );
	m = rdi(  );
	b[ 0 ] = 1;
	For( i, 1, n )
	{
		k[ i ] = rdi(  );
		num[ i ] = rdi(  );
	}
	For( i, 1, m ) max = std::max( max, t[ i ] = rdi(  ) );// 只做到最大的钱
	for( int i = 1, j = k[ 1 ]; i <= num[ 1 ] && j <= max ; ++i, j += k[ 1 ] ) b[ j ] = 1;
	Rep( i, n, 2 )//防止出题人卡，我们倒着做循环。
	{
		Rep( j , max, 1 )
		{
			if( b[ j ] ) continue;
			for(int tmp = j - k[ i ], kkk = 1; tmp >= 0 && kkk <= num[ i ] ; tmp -= k[i], ++kkk ) b[ j ] |= b[ tmp ];
		}
	}
	For( i, 1, m ) puts( b[ t[ i ] ] ? "Yes" : "No" );//puts输出好像比printf快，但是pc更快
	return;
}

}

int
main( int argc, char* argv[] )
{
	RSX::fakemain(  );
	return 0;
}
```





---

