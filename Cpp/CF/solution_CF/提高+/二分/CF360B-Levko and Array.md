# Levko and Array

## 题目描述

Levko has an array that consists of integers: $ a_{1},a_{2},...\ ,a_{n} $ . But he doesn’t like this array at all.

Levko thinks that the beauty of the array $ a $ directly depends on value $ c(a) $ , which can be calculated by the formula:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF360B/bc46a8f9d72cc21bf5d1738220033f31da7db825.png) The less value $ c(a) $ is, the more beautiful the array is.It’s time to change the world and Levko is going to change his array for the better. To be exact, Levko wants to change the values of at most $ k $ array elements (it is allowed to replace the values by any integers). Of course, the changes should make the array as beautiful as possible.

Help Levko and calculate what minimum number $ c(a) $ he can reach.

## 说明/提示

In the first sample Levko can change the second and fourth elements and get array: $ 4 $ , $ 4 $ , $ 4 $ , $ 4 $ , $ 4 $ .

In the third sample he can get array: $ 1 $ , $ 2 $ , $ 3 $ , $ 4 $ , $ 5 $ , $ 6 $ .

## 样例 #1

### 输入

```
5 2
4 7 4 7 4
```

### 输出

```
0
```

## 样例 #2

### 输入

```
3 1
-100 0 100
```

### 输出

```
100
```

## 样例 #3

### 输入

```
6 3
1 2 3 7 8 9
```

### 输出

```
1
```

# 题解

## 作者：AC_CSP (赞：15)

# $\text{Part -1061109567 : 前言}$
[$\text{或许更好的阅读体验}$](https://www.luogu.com.cn/blog/zhaotianfang0515/cf360b-ti-jie)

前置知识：DP，二分。

本蒟蒻第一次写题解，有错误请大家指出。

# $\text{Part 0 : 题目大意}$
[$\text{题目传送门}$](https://www.luogu.com.cn/problem/CF360B)

给你一个长为 $n$ 的序列 $a$，你有至多 $k$ 次修改的机会，请你最小化 $\max\limits_{i=2}^{n}\left|a_i-a_{i-1}\right|$ 的值。

数据范围：$n\le2000$，$a_i\in[-10^9,10^9]$，$k\le n\text{。}$
# $\text{Part 1 : 题目分析}$
观察整个题干，我们发现，有三个未知量：修改的次数，修改的元素和修改后的值（视为一个变量），$\max\limits_{i=2}^{n}\left|a_i-a_{i-1}\right|$ 的值。

从最暴力的方法入手，我们应该枚举前两个变量，可这样的复杂度非常非常高，远不能通过此题。于是考虑之前算法最费时间的地方。

我们发现，由于我们不知道 $\max\limits_{i=2}^{n}\left|a_i-a_{i-1}\right|$ 的值，所以只能进行一个一个数的枚举。但是如果我们枚举  $\max\limits_{i=2}^{n}\left|a_i-a_{i-1}\right|$ 的值，在枚举前面两个变量时就能节省大量的时间。

于是，接下来的问题就变成了如何快速枚举 $\max\limits_{i=2}^{n}\left|a_i-a_{i-1}\right|$ 的值与快速处理前两个变量。
## $\text{Part 1.1 : 枚举？二分！}$

如果我们对 $\max\limits_{i=2}^{n}\left|a_i-a_{i-1}\right|$ 的值进行暴力枚举，需要枚举 $2\times10^9$ 次，考虑优化。

我们可以将 $\max\limits_{i=2}^{n}\left|a_i-a_{i-1}\right|$ 的值比作人的最大容忍值。这个值越大这个人的脾气越好。如果这个人现在的脾气无法容忍一件事（也就是说目前枚举的答案不合法），那么所有比她脾气坏的人可定也无法容忍这件事（也就是对于所有比这个值小的答案，一定都不合法）。这说明 $\max\limits_{i=2}^{n}\left|a_i-a_{i-1}\right|$ 的值具有**单调性**。

既然具有单调性，我们就可以对答案进行二分，使枚举的次数变为 $\log (2\times10^9)$，约 $31$ 次。

事实上，当看到“最小化最大值”或“最大化最小值”时，我们就应该考虑二分。

## $\text{Part 1.2 : 搜索？DP！}$

现在我们该处理前两个变量了。

最容易想到的是搜索，可这样复杂度既不稳定也不优秀。再次考虑，处理一个序列中的一些问题，我们应该想到    $\text{DP}$。

我们还要明确一个问题：是状态中有修改次数还是将修改次数作为答案？

显然是后者。因为如果是前者，复杂度是 $\Theta(nk\log 2\times10^9)$，显然无法通过此题。同时如果将修改次数作为状态的一部分答案就不好考虑了。后者的复杂度是  $\Theta(n\log2\times10^9)$，可以通过此题。

# $\text{Part 2 : DP}$
处理 $\text{DP}$，就要回归 $\text{DP}$ 的三要素：状态，初始化，转移方程。
## $\text{Part 2.1 : 状态}$
最容易想到的状态，是定义 $f[i][0/1]$ 为以第 $i$ 个元素结尾，不改变/改变 这个元素的值并使序列序列符合要求最少的修改次数。

但是，当第二维是 $1$ 时不好转移，所以我们设 $f_1[i]$ 为以第 $i$ 个元素结尾，不改变这个元素的值并使序列序列符合要求最少的修改次数。

同时给出另一种做法，设 $f_2[i]$ 为以第 $i$ 个元素结尾，不改变这个元素的值并使序列序列符合要求最**多**的**非**修改次数。
## $\text{Part 2.2 : 初始化}$
显然，$f_1[i]$ 应改初始化为 $i-1$，代表将之前的所有元素全部改变。

同理，$f_2[i]$ 应初始化为 $1$，代表只不修改当前元素。
## $\text{Part 2.3 : 转移方程}$
转移有两种方法：“人人为我”（用别人更新自己/填表法），“我为人人”（用自己更新别人/刷表法），这里采用前面一种。

由于我们之前确定了 $\max\limits_{i=2}^{n}\left|a_i-a_{i-1}\right|$，所以说对于 $1\le j<i\le n$，有：
$$\left|a_i-a_j\right|\le (\max\limits_{i=2}^{n}\left|a_i-a_{i-1}\right|)\times (i-j)\text{。}$$
所以得到了转移方程：

$$f_1[i]=\min\limits_{(1\le j<i\le n)\left|a_i-a_j\right|\le (\max\limits_{i=2}^{n}\left|a_i-a_{i-1}\right|)\times(i-j)}(f_1[j]+i-j-1)\text{；}$$
$$f_2[i]=\max\limits_{(1\le j<i\le n)\left|a_i-a_j\right|\le (\max\limits_{i=2}^{n}\left|a_i-a_{i-1}\right|)\times(i-j)}(f_2[j]+1)\text{。}$$
## $\text{Part 2.4 : 检验答案}$
对于 $1\le i\le n$，如果 $n-i+f_1[i]\le k(n-f_2[i]\le k)$，那么这个 $\max\limits_{i=2}^{n}\left|a_i-a_{i-1}\right|$ 的值就是合法的。

下面来解释一下。$n-i+f_1[i]$ 就是将 $i$ 后的所有元素都改变再加上前面改变数目的和，也就是总的操作次数。而 $n-f_2[i]\le k$ 就是除去没有改变的元素的数目后，剩余的元素个数，也是总的操作次数。

因为每个 $f_1[i](f_2[i])$ 后面的元素在计算时都被认为是改变的，所以每个状态是**互相独立**的。我们只要找到一个合法状态 $\max\limits_{i=2}^{n}\left|a_i-a_{i-1}\right|$ 的值就是合法的。
# $\text{Part 3 : Code}$
还有一些细节，写在代码里了。
```cpp
//这是一份0pt代码，因为同时写了f1与f2
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e3+7;
const int INF=2e9;
int n,a[N],k;
int f[N];
void first(){//初始化
	for(int i=1;i<=n;i++) f[i]=1;//f2
   for(int i=1;i<=n;i++) f[i]=i-1;//f1
}
void dp_to_dp(int m){//转移方程
	for(int i=1;i<=n;i++)
		for(int j=1;j<i;j++)
			if((i-j)*m>=abs(a[i]-a[j]))
				f[i]=max(f[i],f[j]+1)/*f2*/,f[i]=min(f[i],f[j]+i-j-1)/*f1*/;
}
bool check(){//检验答案
	for(int i=1;i<=n;i++)
		if(n-f[i]<=k/*f2*/,n-i+f[i]/*f1*/) return 1;
	return 0;
}
signed main(){//main必须为整形
	scanf("%lld%lld",&n,&k);
	for(int i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	int l=0,r=INF;//注意l=0，因为差可以等于0
	while(l<r){
		int m=l+r>>1;
		first();
		dp_to_dp(m);
		if(check()) r=m;//如果这个值是合法的，那么它可能是答案，所以是m而不是m-1
		else l=m+1;
		//printf("%lld %lld\n",l,r);
	}
	printf("%lld\n",r);
	return 0;
}//注意，这份代码同时写了两种做法，提交肯定会WA
```
# $\text{Part 1061109567 : 后记}$
制作不易，喜欢的话点个赞再走吧！

如果有什么问题，可以私信我或者发在评论区里，我会作出回答并记录在
[$\text{here}$](https://www.luogu.com.cn/paste/mbjpek1z)


---

## 作者：sLMxf (赞：4)

## Pro
求在至多修改 $k$ 次的情况下，$\max\limits^n_{i=2}|a_i-a_{i-1}|$ 的最小值。
## Sol
### 1. 二分答案
这题的二分挺明显的：因为如果能使 $ans$ 成立，$ans+1$ 一定成立；$ans$ 不成立，$ans-1$ 一定不成立。
### 2. 怎么 check
考虑外面套一个二分答案，考虑中间怎么 `check`。

`check` 的问题是：修改至多 $k$ 次，能否使 $\max\limits^n_{i=2}|a_i-a_{i-1}|$ 的答案等于 $mid$。
### 3. DP 状态
1.0: 定义 $dp_i$ 为前 $i$ 个数满足条件最少需要的修改次数。

但是这么写会很难受，因为我们没有一个定值，这个值不动，不方便我们 DP。

2.0: 定义 $dp_i$ 为前 $i$ 个数满足条件最少需要的修改次数，**其中 $\mathbf i$ 不修改**。

这样子我们可以通过 $a_i$ 来推断前面的 DP 状态了。
### 4. DP 方程
考虑 $dp_i$ 和 $dp_j$ 的关系。

先考虑 $dp_j$ 什么时候才能转到 $dp_i$。

这是一个植树问题。$a_j\sim a_i$ 中，有 $i-j+1$ 棵树，即 $i-j$ 个空格，空格长度不能超过 $ans$，即当且仅当 $a_i-a_j\le (i-j)\times ans$ 成立，$dp_j$ 才能转移到 $dp_i$。 

然而就这么简单一个四年级小盆友都会的植树问题，很多题解都没有写为什么，甚至还有写什么感性证明的。


方程：显然把 $j+1 \sim i$ 的数字全部改了就可以了。即

$$dp_{i}=\min \{dp_j+i-j-1\}$$

---
有人说：这肯定不是最优的啊。比如这个 hack：

```
1 2 3 4 4 4 4 4
      j       i
```

中间的三个 $4$ 根本没有必要去修改啊？

但是这只是在这个 $j$ 的情况，如果 $j$ 移动到 $i$ 前面一个时，阁下又该如何应对？

### 5. DP 初值
把所有数都改成 $a_i$ 就好了。即 $dp_i=i-1$。
### 6. 如何判断
显然，$dp_i$ 这玩意没有考虑到 $i+1\sim n$ 这 $n-i$ 个数，全改了就行。

所以 $dp_i$ 实际上修改的总次数为 $n-i+dp_i$。
### 7. 核心代码
```cpp
memset(dp,127,sizeof(dp)); // 不对啊你是来干什么的
for(int i=1;i<=n;i++) dp[i]=i-1;
for(int i=1;i<=n;i++)
  for(int j=1;j<i;j++)
  {
    int len=i-j+1; // 小学植树问题
    if(abs(a[i]-a[j])<=(len-1)*ans)
      dp[i]=min(dp[i],dp[j]+len-2);
  }
for(int i=1;i<=n;i++)
  if(n-i+dp[i]<=k) return 1;
return 0;
```
### 8. 时空复杂度分析
空间复杂度：$O(n)$。

时间复杂度：里面一个 $n^2$，外面一个 $\log A$，总时间复杂度 $O(n^2\log A)$，其中 $A$ 是 $a_i$ 的值域。

---

## 作者：Kelin (赞：4)

${\rm upd}:2020.7.1$

二分答案$x$，设$f_i$表示$a_i$不变时，前面的数最多有多少个数可以不变.可以得到转移方程
$$f_i=\max_{1\le j<i}\{f_j+1\ \big|\ |a_i-a_j|\le(i-j)x\}$$
即$|a_i-a_j|\le(i-j)x$时，$a_j$可以不变。

由于

$$|a_i-a_j|\le(i-j)x\Leftrightarrow a_i-a_j\le(i-j)x\land a_j-a_i\le(i-j)x$$

即$j\cdot x-a_j\le i\cdot x-a_i\land j\cdot x+a_j\le i\cdot x+a_i$
，故原题就转化为一个三维偏序的问题。

实际上后面的两个不等式蕴含了$j<i$的条件，故可以舍弃$j<i$的限制，从而变为关于$(i\cdot x-a_i,i\cdot x+a_i)$的二维偏序问题。


对第一维排序，第二维用树状数组维护或者二分求值，最后判断二维偏序答案$+k\ge n$即可。

时间复杂度$O(n\log n\log\max a)$

```c++
const int N=1e5+5;
typedef long long ll;
pair<ll,ll>s[N]
inline bool check(ll x){
    vector<ll>f;
    for(int i=1;i<=n;++i)
        s[i]=P(x*i-a[i],x*i+a[i]);
    sort(s+1,s+n+1);
    for(int i=1;i<=n;++i){
        int p=upper_bound(f.begin(),f.end(),s[i].second)-f.begin();
        if(p==(int)f.size())f.push_back(s[i].second);
        else f[p]=s[i].second;		
    }
    return (int)f.size()+k>=n;
}
```

---
$\text{原答案}:2018.1.29$

$f[i]$表示当$a[i]$不变时,最多有多少个$a[j](1\le j<i)$可以不用改变


考虑二分差值为$x$


相邻差值最大是$x\Rightarrow a[i]$跟$a[j]$之间最大的差值是$(i-j)\cdot x$


当相邻差值是$x$时,如果$|a[i]-a[j]|<=(i-j)\cdot x$,那$a[j]$就可以不用改变,

$f[i]=\max(f[i],f[j]+1)$，处理出所有的$f$，判断$\max f+k\ge n$就好了


成立说明$x$大了，否则就小了。


---

## 作者：chenxia25 (赞：4)

本题解是 [CF360B]( https://www.luogu.com.cn/problem/CF360B ) 的 $n\leq 2\times10^5$ 加强版。

一开始看到这题难度 2000，那完蛋了啊，我连 2000 的题都不会做了/ll。然后发现数据范围才 $2000$/xk。

---

答案 $x$ 显然有单调性，先二分起来。

考虑固定那些没有被改变的柱子。那么不难发现，一个没有被改变的柱子序列合法，当且仅当任意一个相邻对 $i,j$ 都满足 $|a_i-a_j|\leq (j-i)x$。然后考虑一个 DP，求出最少需要改变多少个柱子，即最多保留多少个柱子。

我们考虑 $dp_i$ 为考虑到 $i$，$i$ 保留，的最少的改变的柱子数。目标显然是 $\left[\max\limits_{i=1}^n\{dp_i+n-i\}\leq m\right]$。

考虑转移。显然有一个平方的转移，就是对于每个 $i$ 暴力枚举它前面的决策 $j$ 然后判一下比一下。这样总复杂度平方对数，原来的弱题就做完了。就这也配 2000？我 tm 直接秒切（（（（（

考虑优化。对于决策 $j$，合法条件是 $|a_i-a_j|\leq (i-j)x$，更新式是 $dp_j+i-j-1$。那显然可以把更新式拆成 $(dp_j-j)+(i-1)$，于是只要找到 $dp_j-j$ 最小的合法决策即可。然后合法条件里有个绝对值，比较讨厌，考虑将它拆成 $a_i\geq a_j,a_i-ix\leq a_j-jx$ 或 $a_i<a_j,a_i+ix\geq a_j+jx$。这样的话，考虑将「或」字两边的分别考虑，分别二维数点，这样总复杂度线性三次对数，会爆炸。我们需要一个线性二次对数或以下的算法。

注意到，如果最 primitive 的合法条件的 $\leq$ 改成 $\geq$，那么就很容易想到线性二次对数的算法：因为 $a_i\geq a_j$ 所对应的不等式和 $a_i<a_j$ 所对应的不等式，它要满足就显然只会满足真实的 $a_i,a_j$ 大小情况对应的那个。那就很好办，直接忽略 $a_i,a_j$ 的大小关系，把两个不等式对的并一下即可。但是该题是 $\leq$，如果并的话，那就每个决策都一定满足假的那个大小关系所对的不等式，那就每个决策都是合法的了……而如果把不符合的，也就是 $\geq$ 的给不算的话，那又无法撤销。事实上 $\leq$ 就是不能像 $\geq$ 那样顺利的。

我们考虑将「或」字改成「且」字，那就是可以像 $\geq$ 那样将 $a_i,a_j$ 大小关系去掉的。那就可以表示成 $[a_j-jx,a_j+jx]\subseteq[a_i-ix,a_i+ix]$（这直接做还是需要二维数点的）。不过注意到这里的一个特殊的性质：对于 $i<j$，$i$ 的区间大小一定比 $j$ 的区间大小小。这也就说明，我们原来是找那些 $j<i$ 的满足这个条件的 $j$，现在可以直接无视 $j<i$ 了，因为 $j>i$ 的话，$j$ 的区间就更大，就不可能包含于 $i$ 的区间了。于是可以调整一下 DP 顺序，将左端点排序，这样依然可以保证无后效性。这样一来，左端点这一维就不需要考虑了，于是变成一维数点了。就随便离散化 BIT 即可，小常数线性二次对数。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
const int inf=0x3f3f3f3f3f3f3f3f;
int lowbit(int x){return x&-x;}
void read(int &x){
	x=0;char c=getchar();bool ne=false;
	while(!isdigit(c))ne|=c=='-',c=getchar();
	while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();
	if(ne)x=-x;
}
const int N=200000;
int n,m;
int a[N+1];
int dp[N+1];
struct range{
	int l,r,id;
	range(int _l=0,int _r=0,int _id=0){l=_l,r=_r,id=_id;}
}rg[N+1];
bool cmp(range x,range y){
	if(x.l!=y.l)return x.l>y.l;
	return x.r<y.r;
}
vector<int> nums;
void discrete(){
	sort(nums.begin(),nums.end());
	nums.resize(unique(nums.begin(),nums.end())-nums.begin());
}
struct bitree{
	int mn[N+1];
	void init(){memset(mn,0x3f,sizeof(mn));}
	void chkmn(int x,int v){
		while(x<=n)mn[x]=min(mn[x],v),x+=lowbit(x);
	}
	int Mn(int x){
		int res=inf;
		while(x)res=min(res,mn[x]),x-=lowbit(x);
		return res;
	}
}bit;
bool chk(int x){
	nums.clear();
	for(int i=1;i<=n;i++)rg[i]=range(a[i]-i*x,a[i]+i*x,i),nums.pb(a[i]+i*x);
	discrete();
	sort(rg+1,rg+n+1,cmp);
	bit.init();
	for(int i=1;i<=n;i++){
		int fd=lower_bound(nums.begin(),nums.end(),rg[i].r)-nums.begin()+1;
		dp[rg[i].id]=min(rg[i].id-1,bit.Mn(fd)+rg[i].id-1);
		if(dp[rg[i].id]+n-rg[i].id<=m)return true;
		bit.chkmn(fd,dp[rg[i].id]-rg[i].id);
	}
	return false;
}
signed main(){
//	freopen("a.in","r",stdin);freopen("a.out","w",stdout); 
	read(n);read(m);
	for(int i=1;i<=n;i++)read(a[i]);
	int ans=1e10;
	for(int i=34;~i;i--)if(ans-(1ll<<i)>=0&&chk(ans-(1ll<<i)))ans-=1ll<<i;
	cout<<ans<<"\n";
	return 0;
}
```



---

## 作者：Stone_Xz (赞：3)

# [题目传送门](https://www.luogu.com.cn/problem/CF360B)

# 分析

答案具有单调性。如果无法在 $k$ 次修改内做到 $\max\limits^n_{i=2}\left|a_i-a_{i-1}\right| = ans$，那么肯定也无法在 $k$ 次修改内做到 $\max\limits^n_{i=2}\left|a_i-a_{i-1}\right| = ans - 1$。考虑二分答案。

如何判断当前答案 $x$ 是否可行？即判断是否能在 $k$ 次修改内使 $\max\limits^n_{i=2}\left|a_i-a_{i-1}\right| = x$。考虑 DP。

### 状态：

$dp_{i}$ 表示前 $i$ 个元素中，不修改 $i$ 这个元素的条件下，使数列符合要求的最小修改次数。

### 答案：
由于不确定保留哪个元素更优，所以枚举保留位置 $i$，取 $\min((n - i) + dp_{i})$。即取前 $i$ 个数的最优方案，然后将后面的数全部修改。

你可能想问：将后面所有数全改了肯定不优啊？

因为 $i$ 后面的数不归 $dp_i$ 管，等我们枚举到后面的 $dp$ 值，它会帮我们保留后面的数的。这样就可以知道后面的数如果不全部更改，是否更优了。还不懂的话可以拿样例三试一试。

### 状态转移：

首先枚举当前状态 $i$，我们考虑枚举最后修改的那一段位置（可以不修改）。所以枚举上一个决策 $j$（上一个保留的位置），$[j + 1, i - 1]$ 就是最后一段修改的位置。显然 $i$ 和 $j$ 都不能修改。但如果 $|a_i - a_j| > (i - j) \times x$ 的话，$i$ 和 $j$ 必须修改，所以我们要判断 $j$ 是否合法。

确定了 $i$ 和 $j$，还是一样的，前 $j$ 个数取最优方案，保留 $j$。然后将 $j + 1$ 到 $i - 1$ 这一段全部修改，最后保留 $i$。

$$
dp_{i} = \min(dp_{i}, dp_{j} + (i - j - 1))
$$

### 初始化：

把 $[1, i - 1]$ 这一段全修改了一定能达成目标。

如果对于一个 $i$，没有合法的 $j$，那么也只能这样。

初始化即 $dp_i = i - 1$。

# 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N = 2005;

int n, k, dp[N], a[N];

bool check(int x)
{
	for(int i = 1; i <= n; i++)
		dp[i] = i - 1;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j < i; j++)
		{
			if(abs(a[i] - a[j]) <= (i - j) * x)
				dp[i] = min(dp[i], dp[j] + i - j - 1);
		}
	for(int i = 1; i <= n; i++)
		if(n - i + dp[i] <= k) return true;
	return false;
}

signed main()
{
	cin.tie(0) -> sync_with_stdio(0);
	cin >> n >> k;
	for(int i = 1; i <= n; i++)
		cin >> a[i];
	int lt = -1, rt = 2e9 + 1;
	while(lt + 1 < rt)
	{
		int mid = lt + rt >> 1;
		if(check(mid)) rt = mid;
		else lt = mid;
	}
	cout << rt;
	return 0;
}
```

---

## 作者：lfxxx (赞：2)

二分答案 $x$，接下里问题变成最小化修改位置以满足条件。

由于修改很自由，所以考虑让不被修改的位置最多。

不妨设计状态 $dp_i$ 表示前 $i$ 个位置，最多可以保留多少位置不被修改，注意到相邻两个不被修改的位置 $i,j$ 可以通过修改中间的数做到的最小相邻差是 $\frac{|a_i-a_j|}{i-j} \leq x$，于是 $dp_j$ 可以转移到 $dp_i$ 的条件是 $|a_i - a_j| \leq (i-j) \times x$，暴力转移即可做到 $O(n^2 \log V)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
//#define lowbit(x) (x&(-x))
//#define bp push_back
//#define sz size
//#define cl clear
const int maxn = 2114;
int dp[maxn],a[maxn];
int n,k;
bool check(int x){
	for(int i=1;i<=n;i++){
		dp[i]=1;
		for(int j=1;j<i;j++){
			if(abs(a[i]-a[j])<=x*(i-j)) dp[i]=max(dp[i],dp[j]+1);				
		}
		if(dp[i]>=k) return true;
	}
	return false;
}
signed main(){
	cin>>n>>k;
	k=n-k;
	for(int i=1;i<=n;i++) cin>>a[i];
	int l=-1,r=2e9;
	while(l+1<r){
		int mid=(l+r)>>1;
		if(check(mid)==true) r=mid;
		else l=mid;
	}
	cout<<r<<'\n';
	return 0;
}

```

---

## 作者：觞羰涙 (赞：2)

# ~~毒瘤题~~ #
求相邻差值最大的最小值，考虑二分
---
* check用dp
* dp[i]表示第i个不改，前面符合条件的最小改动次数
* i~j区间都考虑更改到满足条件
* 正确性：如果i~j有的可以不改，那么j扫描到那里转移到i就会更优
```cpp
bool judge(ll MAX)
{
	for(int i=0;i<n;i++)dp[i]=i;
	for(int i=0;i<n;i++)
	for(int j=0;j<i;j++)
	if(abs(a[j]-a[i])<=MAX*(i-j))
	dp[i]=min(dp[i],dp[j]+i-j-1);
	for(int i=0;i<n;i++)
	if(dp[i]+n-i-1<=k)
	return true;
	return false;
}
```

---

## 作者：wind_whisper (赞：1)

## $\text{Description}$
给出一个序列 $a_{1...n}$，可以修改 $k$ 个值,最小化 $\max|a_i-a_{i+1}|(1\le i<n)$.  
$k\le n\le 2000$
## $\text{Solution}$
很巧妙的一道题.  
容易想到二分答案，关键就是如何判断合法.  
正难则反，改为保留至少 $n-k$ 个数不变.  
设计 $dp_i$ 表示 $[1,i]$ 区间中保留 $i$ 的前提下保留数的最多个数.  
转移则是：
$$dp_i=\max dp_j+1(j<i,|a_i-a_j|\le(j-i)\times d)$$
暴力 $n^2$ 转移即可通过.
## $\text{Code}$
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define debug(...) fprintf(stderr,__VA_ARGS__)
const int N=6005;
inline ll read(){
  ll x(0),f(1);char c=getchar();
  while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
  while(isdigit(c)){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
  return x*f;
}
int n,m;
ll a[N];
int dp[N];
bool check(ll x){
  for(int i=1;i<=n;i++){
    dp[i]=1;
    for(int j=1;j<i;j++){
      if(abs(a[i]-a[j])<=1ll*(i-j)*x) dp[i]=max(dp[i],dp[j]+1);
    }
    if(dp[i]+m>=n) return true;
  }
  return false;
}
int main(){
  #ifndef ONLINE_JUDGE
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
#endif
  n=read();m=read();
  for(int i=1;i<=n;i++) a[i]=read();
  ll st=0,ed=2e9;
  while(st<ed){
    ll mid=(st+ed)>>1;
    if(check(mid)) ed=mid;
    else st=mid+1;
  }
  printf("%lld\n",st);
  return 0;
}

```


---

## 作者：Claire0918 (赞：0)

注意到需要求最小的最大值，考虑二分。

对于一个确定的 $x$，我们需要求出最少需要多少次修改使得 $\max_{i = 2}^{n}\{|a_i - a_{i - 1}|\} \leq x$。因为式子中小于等于号的存在，这样的二分显然是具有单调性的。

考虑 dp。设 $f_i$ 表示 $[1, i]$ 子串中且 $i$ 不修改的答案。

转移枚举上一个不修改的点 $j$。首先，我们有必要的条件 $|a_i - a_j| \leq (i - j)x$，否则无论 $(j, i)$ 中如何修改，总不能满足原本的式子。在满足这条件后，我们默认 $(j, i)$ 中均修改，即修改 $i - j - 1$ 次，有转移 $f_i \gets f_j + i - j - 1$。

转移的正确性是可以用 dp 的意义证明的。

特别地，$i$ 可以成为第一个不修改的点，此时有 $f_i = i - 1$。

显然我们至少有一个点不修改是不劣的，从而我们可以枚举最后一个修改点 $i$，答案 $r \gets f_i + n - i$。

如果有 $r \leq k$，那么 $x$ 是可行的，否则不是可行的。

时间复杂度 $\mathcal{O}(n^2 \log a)$。

Code：
```cpp
#include<bits/stdc++.h>
#define mem(a, v) memset(a, v, sizeof(a));

using namespace std;

const int maxn = 2000 + 10;

int n, k;
int a[maxn], f[maxn];

inline bool check(long long x){
    for (int i = 1; i <= n; i++){
        f[i] = i - 1;
    }
    for (int i = 1; i <= n; i++){
        for (int j = 1; j < i; j++){
            if (abs(a[j] - a[i]) <= (i - j) * x){
                f[i] = min(f[i], f[j] + i - j - 1);
            }
        }
    }
    for (int i = 1; i <= n; i++){
        if (n - i + f[i] <= k){
            return true;
        }
    }
    return false;
}

signed main(){
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
    }
    long long l = 0, r = 2e9;
    while (l < r){
        const long long mid = l + r >> 1;
        if (check(mid)){
            r = mid;
        }else{
            l = mid + 1;
        }
    }
    printf("%lld", l);

return 0;
}
```

---

## 作者：qzmoot (赞：0)

# 题解：CF360B Levko and Array
最近开始恶补 dp，只因没有写对提高组的第三题
## 题目大意
给定一个数列 $a$，可以对其中的元素做至多 $k$ 次修改，每次修改可以将数列中的一个数改成另一个。问你最小的相邻两个数差的最大值。（可以去看看题面的公式表达）
## 题目分析
感觉看上去很可以二分答案，仔细想了想，对于一个答案不能成立，那说明必须得往大的找；如果对于一个答案成立，那么显然我们不需要往后了，后面全部都可以成立，要继续去往前找。

接着我们来想如何去检查。考虑 dp，我们设定状态 $f_i$ 为在第 $i$ 位前进行最少多少次操作才能满足要求。

初始值就比较好确定了，最多 $i-1$ 次，也就是把前面的数全部修改。

然后就是转移方程。我们发现，不一定是所以的 $j<i$ 都可以向 $i$ 转移。我们假设若可以转移，则之间的数最大才是 $mid$，对于 $i-j$ 个间隔，我们必须满足 $|a_i-a_j|\leq (i-j)\times mid$，否则我们无论怎么改变，他们中间总会有数的差大于 $mid$。

又因为我们都只考虑了前缀的修改，只维护了前缀，后缀的修改我们只能被迫配合前缀，否则就会产生后效，加上 $n-i$ 次就行了。

讲的都这么详细了，代码就不用放了。

---

## 作者：xixisuper (赞：0)

# CF360B Levko and Array 题解

出到学校模拟赛题里面了，来水篇题解。

## 思路

题目大意：

> 给定数列 $a$，最多改变 $k$ 个值，最小化 $|a_i-a_{i+1}|$ 的最大值。

注意到题目中有“**最小化最大值**”这么个东西，所以我们考虑二分答案。

我们二分一个 $d$ 表示当前情况下 $|a_i-a_{i+1}|$ 的最大值，并考虑如何进行 check。考虑 dp，设状态 $dp_i$ 表示 $[1,i]$ 这一段要想使得 $\max_{j=1}^{i-1}|a_j-a_{j+1}|\le d$ 最少要改变多少个数，并且钦定不改变第 $i$ 个数，分析一下怎样递推。

显然，我们可以把改变的数看成是连续的几段，于是我们可以去枚举改变哪些数能够使得 $\max_{j=1}^{i-1}|a_j-a_{j+1}|\le d$ 成立，并且改变最少的数，经过分析能够得到这样一个转移式：

$$
dp_i=\min_{t=1}^{i-1}\left\{dp_t+i-t-1\right\},  \left\lceil\frac{|a_i-a_t|}{i-t}\right\rceil\le d
$$

简单地说就是改变 $[t,i-1]$ 这一段的所有数，显然这一段内使得相邻的数差值的最大值最小就是 $|a_i-a_t|$ 的平均值，由于每个数都是整数，所以还得向上取整。

如果最终你发现要想使得这 $n$ 个数的答案满足条件的最小的值是小于等于 $d$，证明 $d$ 有可能更大，否则说明 $d$ 过大，于是我们便构造完成了我们的 check 函数，外层套一层二分即可。

归到时间复杂度分析，单次 check 的时间复杂度是 $O(n^2)$ 的，外面再套一层二分，得到的总时间复杂度为 $O(n^2\log V)$，其中 $V$ 是 $a$ 的值域，足以通过本题。

## 代码

```cpp
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
const ll N=2005;
const ll INF=2147483647;
ll n,k,H[N],dp[N];
bool chk(ll mx){
	dp[0]=0;
	for(ll i=1;i<=n;i++){
		dp[i]=INF;
		for(ll t=0;t<i;t++){
			if(!t){
				dp[i]=min(dp[i],i-1);
				continue;
			}
			ll pt=H[i]-H[t];
			if(pt<0) pt=-1*pt;
			if(pt<=mx*(i-t)) dp[i]=min(dp[i],dp[t]+i-t-1);
		}
	}
	ll ans=INF;
	for(ll i=n;i>=1;i--) ans=min(ans,n-i+dp[i]);
	return ans<=k;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>k;
	for(ll i=1;i<=n;i++) cin>>H[i];
	ll L=0,R=INF,mid;
	while(L<R){
		mid=(L+R)>>1;
		if(chk(mid)) R=mid;
		else L=mid+1;
	}
	cout<<L;
	return 0;
}
```

---

## 作者：makerlife (赞：0)

注意到答案具有单调性，二分答案 $x$。

考虑 `check()` 函数的写法，首先可以将题目中要求的最多 $k$ 次修改转化为至少保留 $n-k$ 个数。

不妨进行 DP，设 $f_i$ 表示前 $i$ 个数中在保留 $a_i$ 的情况下最多能保留的数量。两个数可以被保留，当且仅当 $\lvert a_j-a_i\rvert\leq (j-i)\times x$。这个比较好感性理解，两个位置 $(i,j)$ 之间有 $j-i+1$ 个数，也就意味着有 $j-i$ 个间隔，而这 $j-i$ 个间隔中每个间隔最大的符合条件的差是 $x$。

那么式子就很显然了：

$$
f_i=\max_{1\leq j<i}\{f_j+1 \big| \lvert a_j-a_i\rvert\leq (j-i)\times x\}
$$

### Core Code

```cpp
const int N = 2e3 + 10;
const int MAXN = 2e9;
int n, k;
int a[N];
int f[N];
bool check(int x) {
    for (int i = 1; i <= n; i++) f[i] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            if (abs(a[i] - a[j]) <= (i - j) * x) {
                f[i] = max(f[i], f[j] + 1);
            }
        }
        if (f[i] >= n - k) return 1;
    }
    return 0;
}
signed main() {
    n = read(); k = read();
    for (int i = 1; i <= n; i++) {
        a[i] = read();
    }
    int l = 0, r = MAXN;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (check(mid)) r = mid;
        else l = mid + 1;
    }
    cout << l << endl;
    return 0;
}
```

---

## 作者：Unnamed114514 (赞：0)

显然修改是一段一段的，修改后区间 $[l,r]$ 的贡献应该是 $\lceil\dfrac{|a_{r+1}-a_{l-1}|}{r-l+2}\rceil$，因为显然要做到平均，注意 $l=1$ 或 $r=n$ 的时候显然为 $0$。

直接搞会跟答案有关，考虑二分，转化为判定性问题。

定义 $f_i$ 表示 $i$ 不变时至少要变几个，考虑枚举前面可行的位置 $j$，有转移 $f_i\gets\min\limits_{\lceil\frac{|a_i-a_j|}{i-j}\rceil\le mid}\{f_j+i-j-1\}$。

注意最后一个不一定不变，所以需要枚举最后一个不变的位置，和 $k$ 比较的应该是 $\min\{f_i+n-i\}$。

---

## 作者：endswitch (赞：0)

技巧要点：

* 二分答案
* 转换性质（正难则反）

对于这一类形如**最大值最小**或**最小值最大**的问题通常都有一个二分答案的套路。

对于**至多做 $k$ 次修改**这个限制可以转换为**至少保留 $n - k$ 个数**。

那么我们的状态就呼之欲出了：$dp_i$ 表示 $[1, i]$ 中保留 $i$ 的最多保留数。那么转移限制为 $|a_i - a_j| \le x \times (j - i)$，可以感性理解为 $i$ 到 $j$ 中若全都为最大值的最劣情况。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
#define abs(x) ((x) < 0 ? -(x) : (x))
using namespace std;

const int N = 2e3 + 5;
int n, k, a[N], dp[N];

inline bool check(int x) {
	for(int i = 1 ; i <= n ; ++ i) {
		dp[i] = 1;
		for(int j = 1 ; j < i ; ++ j)
			if(abs(a[i] - a[j]) <= x * (i - j)) dp[i] = max(dp[i], dp[j] + 1);
		
		if(dp[i] + k >= n) return true;
	}
	
	return false;
}

signed main() {
	ios_base :: sync_with_stdio(NULL);
	cin.tie(nullptr);
	cout.tie(nullptr);
	
	cin >> n >> k;
	
	for(int i = 1 ; i <= n ; ++ i)
		cin >> a[i];
	
	int l = 0, r = 2e9, ans = 0;
	
	while(l <= r) {
		int mid = (l + r) >> 1;
		
		if(check(mid)) ans = mid, r = mid - 1;
		else l = mid + 1;
	}
	
	cout << ans;
	
	return 0;
}
```

---

