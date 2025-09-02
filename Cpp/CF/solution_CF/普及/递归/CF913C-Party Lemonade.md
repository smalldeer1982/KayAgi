# Party Lemonade

## 题目描述

题意

没有柠檬水的新年派对不是新年派对。像往常一样，你期待着客人，而柠檬水已经成为一种令人愉快的必需品。
你最喜欢的商店卖 n 种不同价格的装在不同瓶子里的柠檬水。一瓶第 i 种柠檬水，体积为2^{i-1}，价格为c_{i}卢布。商店里的每种柠檬水可以被认为有无限瓶。
你想要买至少 L 升的柠檬水，你需要花费多少卢布？

## 样例 #1

### 输入

```
4 12
20 30 70 90
```

### 输出

```
150
```

## 样例 #2

### 输入

```
4 3
10000 1000 100 10
```

### 输出

```
10
```

## 样例 #3

### 输入

```
4 3
10 100 1000 10000
```

### 输出

```
30
```

## 样例 #4

### 输入

```
5 787787787
123456789 234567890 345678901 456789012 987654321
```

### 输出

```
44981600785557577
```

# 题解

## 作者：Eric_jx (赞：6)

## 思路分析
由于 $L$ 的数值比较大（$1≤L≤10^9$），所以不能用多重背包来解，通过观察题目发现正解很可能与二进制位有关。分析题目可以得到 $c_i$ 与 $c_{i+1}$ 有以下几种关系：

- $2\times c_i=c_{i+1}$ 此时选择 $c_i$ 还是 $c_{i+1}$ 都对答案没有影响。

- $2\times c_i<c_{i+1}$ 此时应购买两个 $c_i$ 而不是一个 $c_{i+1}$。

- $2\times c_i>c_{i+1}$ 此时应选用 $c_{i+1}$ 而不是两个 $c_i$。

因此，我们可以得到购买 $2^k$ 件商品的最优解。

当可以购买大于等于 $L$ 件商品的时候的最优解：假设购买了 $M$ 件商品为最优解（$M≥L$）。此时从高位到低位，$M$ 与 $L$ 的二进制第一次出现不同的位置 $i$ 所对应的 $c_i$ 小于 $L$ 比 $i$ 小的所有位 $c_i$ 的和。从这个角度出发可得最优解。

注意：不开 long long 见祖宗

## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long c[1005],num[1005];
int main(){
	long long n,l,ans=0,cnt=0;
	cin>>n>>l;
	while(l!=0){
		num[cnt++]=l%2,l/=2;
	}
	cin>>c[0];
	for(int i=1;i<n;i++){
		cin>>c[i];
		c[i]=min(c[i],c[i-1]*2);
	}
	for(int i=n;i<cnt;i++){
		c[i]=c[i-1]*2;
	}
	for(int i=0;i<max(n,cnt);i++){
		ans=min(ans,c[i]);
		if(num[i]==1) ans+=c[i];
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：囧仙 (赞：4)

## 题目大意

$n$种柠檬汁，每种体积为$2^{i-1}$，价格为$W_i$。询问购买总体积不小于$L$的柠檬汁，最少要花多少钱。

## 题解

很显然，如果$2\times W_i<W_{i+1}$，那么我们就可以用两瓶$i$种柠檬汁来替代一瓶$i+1$种柠檬汁。这样可以保证，一次购买的体积越大，平均花费的钱越少。

让我们从一个简单的问题入手：假如你有$m$元，你**最多**能够购买到多少柠檬汁呢？

根据上述的贪心方法，我们能够发现，**尽可能购买体积更大的柠檬汁能省更多钱**。他的正确性比较容易说明。很显然，如果我们需要购买两次$i$种柠檬汁，就不如购买一次$i+1$种柠檬汁，因此每种果汁**最多购买一瓶**。如果我们放弃购买第$i$种柠檬汁，即使我们将剩下的种类都买了一遍，也达不到它的体积，甚至还要花费更多的钱。

因此，这样一个二分的算法就出来了。每次判断$x$元能否购买到$L$体积的柠檬汁，进行二分操作即可。

## 参考代码

```cpp
#include<bits/stdc++.h>
#define up(l,r,i) for(int i=l;i<=r;i++)
#define dn(l,r,i) for(int i=l;i>=r;i--)
using namespace std;

typedef long long LL;
const int INF =2147483647;
LL qread(){
    LL w=1,c,ret;
    while((c=getchar())> '9'||c< '0')
    w=(c=='-'?-1:1); ret=c-'0';
    while((c=getchar())>='0'&&c<='9')
    ret=ret*10+c-'0';
    return ret*w;
}
LL n,l,W[31],ans,p,k;
bool chk(LL x){
    LL ret=0;
    dn(30,0,i) if(x>=W[i]) ret+=(1<<i),x-=W[i];
    return ret>=l;
}
int main(){
    n=qread(),l=qread(); W[0]=qread();
    up(1,n-1,i){
        W[i]=qread(); if(W[i]>W[i-1]<<1) W[i]=W[i-1]<<1;
    }
    up(n,30,i) W[i]=W[i-1]<<1;
    p=0,k=1; while(k){
        if(!chk(p+k)) p+=k,k<<=1; else k>>=1;
    }
    printf("%lld\n",p+1);
    return 0;
}
```

---

## 作者：Overstars (赞：4)

一道非常巧妙的贪心题。

先来尝试处理$l$的每一位，可以发现这一位有三种处理方式。

- 当高位量多价廉时，多买了高位就没必要再买任何低位了，包括当前这一位

- 只按这一位$i$对应的$2^i$个$c[i]$元购买

- 由低位凑出来更实惠

~~感觉爆搜可以做，~~我们可以用$dp$处理出购买$2^i$个（即第i位的代价）所需的最小花费，这样就不必考虑第三种情况。
```cpp
dp[0]=c[0];
	for(int i=1;i<n;i++)//购买2^i最小代价
		dp[i]=min(c[i],dp[i-1]*2);
```

从$l$的高位向低位扫一遍，依次累加消除$l$的每一位的代价，并在每一位都试一下是否在这一位多买一份能得到更优解，答案即为其中的最小值，复杂度$O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
//#define int ll
const int maxn=210,inf=0x3f3f3f3f,mod=1000000007;
ll c[maxn],dp[maxn];
signed main()
{
	ll n,l,x,y;
	cin>>n>>l;
	for(int i=0;i<n;i++)
		cin>>c[i];
	dp[0]=c[0];
	for(int i=1;i<n;i++)//购买2^i最小代价
		dp[i]=min(c[i],dp[i-1]*2);
	ll ans=LLONG_MAX,sum=0;
	for(ll i=n-1;i>=0;i--)
	{//高位到低位
		ll des=l/(1ll<<i);
		sum+=des*dp[i];//累计代价
		l&=(1<<i)-1;//保留低位
		ans=min(ans,sum+(l>0)*dp[i]);
	}
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：CheerJustice (赞：3)

### [点我传送](https://www.luogu.com.cn/problem/CF913C)

## solution

首先题目里有一个条件是突破口：第 $ i $ 种柠檬水 有 $ 2^{i-1} $ 升。所以我们直接给 $ L $ 做个二进制分解，设 $ L $ 二进制下第 $ i $ 位为 $ a_{i} $。若 $ a_{i}=1 $，就得买 $2^{i-1}$ 水，这样 $ L $ 就好凑了。怎么凑是最优的？我来举个栗子。

你去小店买可乐，有 $ 3 $ 元一瓶的，还有 $ 40 $ 元 $ 12 $ 瓶一箱的，很显然这个小店的老板数学是体育老师教的。作为数学课代表，你高兴的买了 $ 12 $ 瓶单瓶可乐狠赚了老板 $ 4 $ 块钱。

很幸运，本题的老板数学也不好。不难发现，买 $ 1 $ 瓶第 $ i $ 种柠檬水就等同于买 $ 2 $ 瓶第 $ i-1 $ 中柠檬水，当然了，$ i>1 $。这时候如果后者更便宜，直接取代前者。实现起来很简单，我们在读入时预处理出买 $ 2^{i} $ 的柠檬水的最少价值 $ c_{i} $，然后直接把对应 $ a_{i}=1 $ 的 $ c_{i} $ 给加上就行了。

但是还有一种情况，我们不一定刚好要买 $ L $ 升，大于也是满足题意的，所以特判一下即可。

## code
```c++
#include <bits/stdc++.h>
#define ll long long
using namespace std;
inline int in(){
	char c=getchar();int f=1;int x;
	while((c<'0'||c>'9')&&c!='-') c=getchar();
	if(c=='-')f=-1,c=getchar();
	for(x=0;c>='0'&&c<='9';c=getchar())
		x=(x<<3)+(x<<1)+(c^48);
	return x*f;
}
template <typename T>
inline void in(T &x){
	char c=getchar();int f=1;
	while((c<'0'||c>'9')&&c!='-') c=getchar();
	if(c=='-')f=-1,c=getchar();
	for(x=0;c>='0'&&c<='9';c=getchar())
		x=(x<<3)+(x<<1)+(c^48);
	x*=f;
}
// 以上快读，请允许我略~
int n,l,len;
bool num[35];
ll c[35],ans;// long long必须开
int main(){
	in(n),in(l); 
	while(l) num[len++]=l&1,l>>=1; // 转二进制
	for(int i=0;i<n;++i){
		in(c[i]);
		if(i)c[i]=min(c[i],c[i-1]<<1);//处理c[i]，注意下标从0开始
	}
	for(int i=n;i<len;++i)c[i]=c[i-1]<<1;
	for(int i=0;i<max(n,len);++i){
		ans=min(ans,c[i]);// 如上文所说，特判
		if(num[i])ans+=c[i];
	}
	printf("%lld\n",ans);
	return 0;
}



---

## 作者：elijahqi (赞：3)

http://www.elijahqi.win/2018/01/09/codeforces-913c-party-lemonade/ ‎


 http://blog.csdn.net/elijahqi/article/details/79008889

C. Party Lemonade

time limit per test

1 second

memory limit per test

256 megabytes

input
standard input

output
standard output


A New Year party is not a New Year party without lemonade! As usual, you are expecting a lot of guests, and buying lemonade has already become a pleasant necessity.


Your favorite store sells lemonade in bottles of n different volumes at different costs. A single bottle of type i has volume 2i - 1 liters and costs ci roubles. The number of bottles of each type in the store can be considered infinite.


You want to buy at least L liters of lemonade. How many roubles do you have to spend?

Input

The first line contains two integers n and L (1 ≤ n ≤ 30; 1 ≤ L ≤ 109) — the number of types of bottles in the store and the required amount of lemonade in liters, respectively.


The second line contains n integers c1, c2, ..., cn (1 ≤ ci ≤ 109) — the costs of bottles of different types.

Output

Output a single integer — the smallest number of roubles you have to pay in order to buy at least L liters of lemonade.

Examples

Input

4 12
20 30 70 90


Output

150

Input

4 3
10000 1000 100 10


Output

10

Input

4 3
10 100 1000 10000


Output

30

Input

5 787787787

123456789 234567890 345678901 456789012 987654321


Output

44981600785557577


Note

In the first example you should buy one 8-liter bottle for 90 roubles and two 2-liter bottles for 30 roubles each. In total you'll get 12 liters of lemonade for just 150 roubles.


In the second example, even though you need only 3 liters, it's cheaper to buy a single 8-liter bottle for 10 roubles.


In the third example it's best to buy three 1-liter bottles for 10 roubles each, getting three liters for 30 roubles.


还是icefox巨佬强啊orz  %%我好菜啊 细节太多我还是fail system test了


题意：给定2^0~2^n-1L的汽水 的花费 最后至少L的汽水的最小花费是多少


那么首先我们把他给的数都读进来  然后倒着dp一下 设dp[i]表示买2^i的最小花费是多少


然后得到每个正确的花费 然后针对每一位贪心考虑即可 为什么这题可以贪心考虑 因为这个都是2的次幂 所以我 确信我如果小的次幂多选了 一定不会影响我大的次幂


所以可以这么来搞 我把L转换成二进制 单独考虑每一个二进制位上的数怎么去搞


假设我这个二进制是1010110001 那么 首先有1的位置我可以认为一定买2^i最优 比如处理其中一个子问题110001的时候 在处理最高位1的时候 我有可能选两个这个一位置上的数 有可能就是按部就班的选一个 然后比我最高位小的地方我再递归下去去搞 这里得注意一些细节 就是比如我选了最后一个1010110001的最后一个1  但是我发现 它到上一个1的位置中的某个0的位置我选了反而会更好 那么我就需要去选一下这个位置的0  然后后面原本算出来的代价直接被替换就好


还有个小细节 我这样算出来 比如8的费用是1000 但是我发现我买1000的费用只需要10即可 我最后还需要扫一遍 把这种情况做掉即可

```cpp
#include<cmath>
#include<cstdio>
#include<algorithm>
#define ll long long
using namespace std;
int n,L;long long cost[33];
inline ll dfs(int v){
    double len=log2(v);int len1=len;
    if(len==len1) return cost[len1];
    ll left=v-(1<<len1);ll tmp=dfs(left);int len2=log2(left);
    for (int i=len2+1;i<=len1;++i) tmp=min(tmp,cost[i]);
    return cost[len1]*2<cost[len1]+tmp?cost[len1]*2:cost[len1]+tmp;
}
int main(){
    freopen("cf.in","r",stdin);
    scanf("%d%d",&n,&L);
    for (int i=1;i<=32;++i) cost[i]=1LL<<62; 
    for (int i=0;i<n;++i) scanf("%lld",&cost[i]);
    for (int i=1;i<=32;++i) cost[i]=min(cost[i],cost[i-1]*2);
    //for (int i=0;i<30;++i) printf("%lld ",cost[i]);puts("");
    int len=log2(L);ll ans=dfs(L);
    for (int i=len+1;i<=32;++i) ans=min(ans,cost[i]);
    printf("%I64d",ans);
    return 0;
}
```


---

## 作者：llzzxx712 (赞：1)

# CF913C

## 题目分析
本题按顺序给出 1L、2L、4L …… 柠檬汁的价钱。显然如果 2L 柠檬汁比 2 * 1L 的价钱要贵的话，我们可以用 2杯1L 柠檬汁来代替2L柠檬汁。也就是我们读入的时候可以进行一个小处理，读取 $c_i$ 后，使 $c_i=min( c_i ,c_{i-1}* 2)$，这样就可以保证我们可以以最便宜的价格买到 $2^i$ L 柠檬汁了。

至此，我们就获得了第一个贪心思路:将要买的果汁数 L 看成一个多位二进制数（我们把首位叫做第 0 位），从高（n-1）位到低位考虑，如果第 $i$ 位是 1 ，那么就将答案累加上 $c_i$ 。

但是到了 样例2 就发现不对了。答案是20，我们却输出 11000 。**为什么呢？** 再次看题，**购买不小于 L 升柠檬汁**。也就是说我们可以买超过 L 升。在 样例2 中，买 2L 柠檬汁花 ￥1000，但买 8L 柠檬汁只要 ￥10 ！~~（真是奇妙）~~ 这也就是说我们在考虑第 $i$ 位的时候，如果第 i 位是 1，我们可以花 $c_i$ 选择买 $2^i$ 升柠檬汁，再考虑更低位，也可以干脆直接花 $2* c_i$ 的价格买 $2* 2^i$ 杯柠檬汁。就不去管更低位了。

我们可以通过递归来进行解决，用 $dfs(x)$ 来处理第 $i$ 位及以下要花的钱，我们可以先 $dfs(x-1)$ 看看下面几位要花多少钱，再决定是花下面要花的钱，还是直接多买一杯 $2^i$ 量的柠檬汁。边界是 x=0 时，如果 L 的第 0 位是 1 的话就返回 $c_0$ ，否则返回 0。

递归部分代码：
```cpp
#define ull unsigned long long 
ull dfs(ull x){
	if(x==0){//边界了
		if(L&1) return c[0];//买1升
		else return 0;//不用买这 1 升（L是偶数）
	}
	ull anss=dfs(x-1);//先处理低位
	if((L>>x)&1) return min(c[x]<<1,c[x]+anss);//如果这位本来就要买
	return min(c[x],anss);//如果这位本来不用买，但也可以通过买这一位让后面几位不用买
}
```

但是这样会发现还是过不了第四个样例，再一看题我们发现题目没保证 $L<2^n* 2-1$ (用一个n 位的二进制数不一定能表示 L）。因为上面说了，买高位一定最优。所以我们可以一直买 $c_{n-1}$(最高位）,直到 $L<2^n* 2-1$ 。

## 详细注释代码

```cpp
#include<bits/stdc++.h>
#define ull unsigned long long 
using namespace std;
void read(ull &x){
	int f=1;x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') {x=x*10+ch-'0';ch=getchar();}
	x*=f;
}
#define N 40
ull n,L;
ull ans;
ull c[N];
ull dfs(ull x){
	if(x==0){//边界了
		if(L&1) return c[0];//买1升
		else return 0;//不用买这 1 升（L是偶数）
	}
	ull anss=dfs(x-1);//先处理低位
	if((L>>x)&1) return min(c[x]<<1,c[x]+anss);//如果这位本来就要买
	return min(c[x],anss);//如果这位本来不用买，但也可以通过买这一位让后面几位不用买
}
int main(){
	read(n),read(L),read(c[0]);//先专门读入第 0 位 
	for(int i=1;i<n;i++){
		read(c[i]);
		c[i]=min(c[i],c[i-1]<<1);//保证最优惠 
	}
	while(L>=(1<<n)){//一直将 L 减小，直到可以用 n 位 2进制数表示 
		L-=1<<(n-1);
		ans+=c[n-1];
	}
	cout<<ans+dfs(n-1);
	return 0;
}

```


---

## 作者：Meickol (赞：0)

DP 预处理：$w_i$ 记录体积为 $2^i$ 的柠檬水最少需要的卢布。

贪心：对于购买体积为 $2^i$ 的柠檬水，我们有两种选择，要么购买两瓶体积为 $2^{i-1}$ 的柠檬水，要么购买一瓶体积为 $2^i$ 的柠檬水，我们只需要在这两种选择中选一种最小的代价即可。

注意，因为要求买至少 $L$ 升柠檬水的最小花费，因此我们还要考虑是否存在购买大于 $L$ 升柠檬水代价更小的情况。

一方面，相较于前面枚举的位而言，当前枚举到的位是高位，我们考虑当前这个高位单放一个 $1$ 低位全不放时需要的代价 与 前面考虑的符合要求的低位放置的最小代价打擂台取一个最小值。

另一方面，枚举二进制位的位数时需要取最大位数。因为如果 $L$ 大于 $n$，那么显然必须要把所有的 $L$ 在二进制下表示的位数都枚举计算了才能保证答案的正确性；而如果 $L$ 小于 $n$，因为可能存在花费大于 $L$ 升柠檬水但代价更小的情况。

```cpp
#define rep(x,y,z) for(int x=y;x<=z;x++)
typedef long long LL;
const int N=31;
int n,L;
int cnt,num[N]; //num_i 表示 L 在二进制表示下各位的值。
LL w[N],ans;
void solve(){
	cin>>n>>L;
	cin>>w[0];
	rep(i,1,n-1){
		cin>>w[i];
		w[i]=min(w[i],w[i-1]*2);
	}
	while(L){
		num[cnt++]=(L&1);
		L>>=1;
	}
	rep(i,n,cnt-1) w[i]=w[i-1]*2;
	rep(i,0,max(n-1,cnt-1)){
		ans=min(w[i],ans);
		if(num[i]&1) ans+=w[i];
	}
	cout<<ans;
}
```

---

## 作者：JimmyLee (赞：0)

#  分析

因为容量为 $2^{i-1}$，所以对于任意的 $i<j$，第 $j$ 种瓶子一定可以通过选择 $2^{j-i}$ 个 $i$ 种瓶子来实现。

定义一个瓶子的性价比为 $\dfrac{\textrm{容量}}{\textrm{价格}}$，即 $\dfrac{2^{i-1}}{c_i}$。

我们可以按照每个瓶子的性价比从高到低排序，依次选择。

选择时分两种情况：

- 直接选择 $\left\lceil\dfrac{L}{2^{i-1}}\right\rceil$ 个当前瓶子。

- 选择 $\left\lfloor\dfrac{L}{2^{i-1}}\right\rfloor$ 个当前瓶子，用后面的瓶子再去算剩下的 $L-2^{i-1}\cdot\left\lfloor\dfrac{L}{2^{i-1}}\right\rfloor$ 容量。

两种情况取 $\min$ 即可。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;

struct bot
{
    int V, w;
    bot(int v, int W): V(v), w(W) {}
    auto operator<=>(bot &b) {return 1ll*b.V*w<=>1ll*V*b.w;}
};

vector<bot> con, bts;

int64_t calc(int n, vector<bot>::iterator it)
{
    int64_t ret=ceil(1.00*n/it->V)*it->w;
    if(n%it->V==0||next(it)==bts.end()) return ret;
    else return min(ret, 1ll*(n/it->V)*it->w+calc(n%it->V, next(it)));
}

int main()
{
    int n, l;
    cin>>n>>l;
    for(int i=0, t;i<n;i++)
        cin>>t, con.emplace_back(1<<i, t);
    sort(con.begin(), con.end());
    for(auto v:con)
        if(bts.empty()||v.V<bts.back().V) 
            bts.emplace_back(v);
    cout<<calc(l, bts.begin());
}
```

---

