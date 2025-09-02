# Dog Walking

## 题目描述

You are walking with your dog, and now you are at the promenade. The promenade can be represented as an infinite line. Initially, you are in the point $ 0 $ with your dog.

You decided to give some freedom to your dog, so you untied her and let her run for a while. Also, you watched what your dog is doing, so you have some writings about how she ran. During the $ i $ -th minute, the dog position changed from her previous position by the value $ a_i $ (it means, that the dog ran for $ a_i $ meters during the $ i $ -th minute). If $ a_i $ is positive, the dog ran $ a_i $ meters to the right, otherwise (if $ a_i $ is negative) she ran $ a_i $ meters to the left.

During some minutes, you were chatting with your friend, so you don't have writings about your dog movement during these minutes. These values $ a_i $ equal zero.

You want your dog to return to you after the end of the walk, so the destination point of the dog after $ n $ minutes should be $ 0 $ .

Now you are wondering: what is the maximum possible number of different integer points of the line your dog could visit on her way, if you replace every $ 0 $ with some integer from $ -k $ to $ k $ (and your dog should return to $ 0 $ after the walk)? The dog visits an integer point if she runs through that point or reaches in it at the end of any minute. Point $ 0 $ is always visited by the dog, since she is initially there.

If the dog cannot return to the point $ 0 $ after $ n $ minutes regardless of the integers you place, print -1.

## 样例 #1

### 输入

```
3 2
5 0 -4```

### 输出

```
6```

## 样例 #2

### 输入

```
6 4
1 -2 0 3 -4 5```

### 输出

```
7```

## 样例 #3

### 输入

```
3 1000000000
0 0 0```

### 输出

```
1000000001```

## 样例 #4

### 输入

```
5 9
-7 -3 8 12 0```

### 输出

```
-1```

## 样例 #5

### 输入

```
5 3
-1 0 3 3 0```

### 输出

```
7```

## 样例 #6

### 输入

```
5 4
0 2 0 3 0```

### 输出

```
9```

# 题解

## 作者：CGDGAD (赞：14)

## CF1680D Dog Walking

### 算法

题面太长不看。稍微简化一下题意：将数列中的 $0$ 都替换成 $[-k,k]$ 中的一个数后，令前缀和数组为 $s$，最大化 $\max\{s\}-\min\{s\}$ 且要求 $s_n=0$（很容易判断，当 $\mid s_n\mid$ 大于 0 的个数乘以 $k$ 的时候，必然无解）。

由这个式子不难想到最大子段和的前缀和解法，可以差不多地理解一下，这个 $\max\{s\}-\min\{s\}$ 代表的是原数列中的**一段区间和（的绝对值）**。然后注意到 $1 \le n \le 3000$ 的良心范围，考虑直接枚举这个区间的左、右端点。如果没有 $s_n=0$ 的限制，最优化的方案必然是要么 0 全替换为 $k$，要么全替换为 $-k$。

但要求 $s_n=0$，怎么处理这个条件也是难点之一。关键点在于看被选择的区间内、外的和能否达到平衡，即「归零」：

- 当区间内的和为一个正数 $p$，区间外的和的最小值为 $p'_{\min}$，题目要求 $p+p'_{\min}$ 必须等于 $0$，因此答案取 $\min\{p, \mid p'_{\min} \mid\}$；
- 同理，当区间内的和为一个负数 $-p$，区间外的和的最大值为 $p'_{\max}$，答案取 $\min\{\mid p \mid, p'_{\max}\}$。


### 实现

```cpp
int n, k, a[3001];
int p[3001], d[3001];

signed main() {
    n = read(), k = read();
    for (int i = 1; i <= n; i++) {
        a[i] = read();
        d[i] = d[i - 1] + (a[i] == 0);
        p[i] = p[i - 1] + a[i];
    }
    if (abs(p[n]) > k * d[n]) return puts("-1"), 0;
    int max = -1;
    for (int l = 1; l <= n; l++) {
        for (int r = l; r <= n; r++) {
            int sum = p[r] - p[l - 1], cnt = d[r] - d[l - 1];
            int lSum = p[n] - sum, lCnt = d[n] - cnt;
            max = std::max(max, std::min(abs(sum + cnt * k), abs(lSum - lCnt * k)));
            max = std::max(max, std::min(abs(sum - cnt * k), abs(lSum + lCnt * k)));
        }
    }
    printf("%lld\n", max + 1);
    return 0;
}
```

---

## 作者：I_am_Accepted (赞：9)

### Analysis

先分别将不确定的位移设为 $-k$ 和 $+k$，计算狗最终的坐标，判断 $0$ 坐标是否在区间内——若不在则无解。

显然的是，最终狗走到的地方是一段包含坐标 $0$ 的区间，我们只要最大化极差即可。

设不确定的位移数量为 $cnt$，先将所有不确定的位移固定为 $-k$，预处理每个时间狗的坐标。

设这样狗最终的坐标为 $-d$ ——即我们还要在不确定的位移中总共向正方向增加 $d$ 格。

相当于在 $cnt$ 容量为 $2k$ 的盒子里放恰好 $d$ 个球。

我们 $O(n^2)$ 枚举两个时间——钦定的最大和最小坐标取到的时间，然后每一对 $O(1)$ 算答案，最后取最大值即可。

设枚举到 $x$ 时间坐标最小，$y$ 时间坐标最大。不失一般性，设 $x<y$。

我们的目标是让 $x,y$ 时间坐标的差值最大，即在 $[x,y]$ 时间段内的不确定的位移因尽可能大（接近 $+k$）。

也就是说，让这段区间内的盒子尽可能多放球，设这段共 $z$ 个盒子，则最多放 $\min\{2kz,d\}$ 个球，这样极差就能快速求出。

值得一提，$x>y$ 的情况希望 $[y,x]$ 间盒子少放球，可知最少放 $\max\{0,d-2k(cnt-z)\}$。

总时间复杂度 $O(n^2)$。

### Code

```cpp
//Said no more counting dollars. We'll be counting stars.
#pragma GCC optimize("Ofast")
//#pragma GCC optimize("unroll-loops")//DONT use rashly,I have suffered
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")//DONT use rashly,I have suffered
#include<bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define fir first
#define sec second
#define mkp make_pair
#define pb emplace_back
#define mem(x,y) memset(x,y,sizeof(x))
#define For(i,j,k) for(int i=j;i<=k;i++)
#define Rof(i,j,k) for(int i=j;i>=k;i--)
#define Fe(x,y) for(int x=head[y];x;x=e[x].nxt)
#define ckmx(a,b) a=max(a,b)
#define ckmn(a,b) a=min(a,b)
#define fin(s) freopen(s,"r",stdin)
#define fout(s) freopen(s,"w",stdout)
#define file(s) fin(s".in");fout(s".out")
#define cerr cerr<<'_'
#define debug cerr<<"Passed line #"<<__LINE__<<endl
template<typename T>T ov(T x){cerr<<"Value: "<<x<<endl;return x;}
#define ll long long
const ll mod=1000000007;
inline ll pw(ll x,ll y){ll r=1;while(y){if(y&1)r=r*x%mod;x=x*x%mod;y>>=1;}return r;}
inline void mad(ll &a,ll b){a=(a+b)%mod;while(a<0)a+=mod;}
inline void mmu(ll &a,ll b){a=a*b%mod;while(a<0)a+=mod;}
#define inv(a) pw(a,mod-2)
#define int long long
#define N 3010

int n,k,a[N],b[N],c[N],cnt=0,ned,L=0,R=0;
signed main(){IOS;
	cin>>n>>k;
	For(i,1,n) cin>>a[i];
	For(i,1,n) if(a[i]) L+=a[i]; else L-=k;
	For(i,1,n) if(a[i]) R+=a[i]; else R+=k;
	if(!(L<=0 && R>=0)){
		cout<<-1<<endl;
		return 0;
	}
	For(i,1,n) if(!a[i]) cnt++;
	For(i,1,n) if(a[i]) b[i]=b[i-1]+a[i]; else b[i]=b[i-1]-k;
	For(i,1,n) if(a[i]) c[i]=c[i-1]; else c[i]=c[i-1]+1;
	k<<=1;
	ned=-b[n];
	int ans=0,tmp;
	For(i,0,n){//min
		For(j,0,n){//max
			if(i<j){
				tmp=b[j]-b[i]+min((c[j]-c[i])*k,ned);
			}else if(i>j){
				tmp=b[j]-b[i]-max(ned-(cnt-(c[i]-c[j]))*k,0ll);
			}else continue;
			ckmx(ans,tmp);
		}
	}
	cout<<ans+1<<endl;
return 0;}
```



---

## 作者：daniEl_lElE (赞：4)

赛时过的，个人认为难度没有 2k4。

## 思路

首先，我们很容易得知一个很基本的贪心策略：尽可能往左或右边走，然后在回来。原因也很清晰，我们想要让走过的点尽可能多，就要尽可能往左或往右。

观察到数据范围是 $3000$，这提示我们使用 $\Theta(n^2)$ 的解法。

我们考虑将序列分成三段，第一段保持向左或右，第二段和第一段相反，第三段再和第二段相反，易发现，我们会得到两个端点，这两个端点一定是我们所“希望”的左右“极”点。那么，我们可以考虑枚举这两个端点，然后再计算。

那么，现在难点就是如何计算最左或最右能到达哪里。

对于每一段，我们先预处理出来 $lmax_i,rmax_i$，意思就是前缀向左和向右**最多**能走几步。那么每次我们在计算最多走多远时，只需要计算第一、三段一个方向最远距离和第二段另一个方向最远距离，取较小值即可。复杂度 $\Theta(n^2)$，即可通过此题。

上一段描述的细节均在代码中会有解释

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
	int n,k;
	cin>>n>>k;
	int a[n+1],tot=0,cnt=0;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		tot+=a[i];//计算不看0的答案
		cnt+=(a[i]==0);//计算0的数量
	}
	if(llabs(tot)>cnt*k){//特判一波，如果永远走不到输出-1
		cout<<-1;
		return 0;
	}
	int maxv=0;//不要赋值成1，不要赋值成1，不要赋值成1！
	int mind[n+2],maxu[n+2];
	mind[0]=0,maxu[0]=0;
	for(int i=1;i<=n;i++){//预处理向左向右最多几步
		if(a[i]==0){//如果不知道了，取k步
			mind[i]=mind[i-1]-k;
			maxu[i]=maxu[i-1]+k;
		}
		else{//如果知道直接加
			mind[i]=mind[i-1]+a[i];
			maxu[i]=maxu[i-1]+a[i];
		} 
	}
	for(int i=0;i<=n;i++){
		for(int j=i;j<=n;j++){
			int d,u;
			d=-(mind[i]+(mind[n]-mind[j]));//向左
			u=(maxu[j]-maxu[i]);//向右
			maxv=max(maxv,min(d,u));//取最小
			d=(maxu[i]+(maxu[n]-maxu[j]));//向左
			u=-(mind[j]-mind[i]);//向右
			maxv=max(maxv,min(d,u));//取最小
		}
	}
	cout<<maxv+1;//加上0位置的
}
```

## 彩蛋

![](https://cdn.luogu.com.cn/upload/image_hosting/20gevemj.png)

顺便解释一下易错点：

* `maxv=1`,`cout<<maxv+1;`。
* `maxv=0`,`cout<<maxv;`。
* `maxv=-1`,`cout<<maxv` 或 `cout<<maxv+1` 且 `for(int i=1;i<=n;i++) for(int j=i+1;j<=n;j++`。

Hack 数据：

```
1 1
0
```

---

## 作者：Hoks (赞：3)

## 前言
[题目链接](https://www.luogu.com.cn/problem/CF1680D)，[个人博客](https://www.luogu.com.cn/blog/Hok/solution-cf1680d)内食用更佳。

~~duel 到的 +1。~~
## 思路分析
首先注意题面所写的意思，**不是** 每一次移动完后到的点的种类数，**而是** 到过的点中的坐标的 **极差**。（刚开始看题的时候半天没看懂悲悲。）

一看 $n$ 的范围果断来个 $n^2$ 枚举最大值的位置和最小值的位置。那怎么 $\operatorname{O}(1)$ 处理极差呢？

首先考虑给所有 $0$ 的位置放上 $-k$，这个时候得出的数列和的相反数便是可以把前面的 $0$ 的位置从 $-k$ 放大的值的最大值。

不难发现影响极差的只有 $\min$ 和 $\max$ 中间的一段 $0$，考虑这段能变大的最大值即为 $2\times k\times cnt,cnt$ 表示其中的 $0$ 的数量。这里只需要和能变的最大值取个最小即可。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k,sum1,sum2,cnt,ans,xy;
int a[3010],b[3010],c[3010];
int read()
{
    char c=getchar();int x=0,f=1;
    while(!isdigit(c)){if(c=='-') f=-1;c=getchar();}
    while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return x*f;
}
signed main()
{
    n=read(),k=read();
    for(int i=1;i<=n;i++) 
        a[i]=read(),cnt+=(a[i]==0),c[i]=cnt,
        b[i]=(a[i]==0)*(-k)+(a[i]!=0)*a[i]+b[i-1],
        sum2+=(a[i]==0)*(k)+(a[i]!=0)*a[i];
    sum1=b[n],xy=-b[n];
    if(sum1>0||sum2<0){puts("-1");goto yuanshen;}
    for(int i=0;i<=n;i++)
        for(int j=0;j<=n;j++)
            if(i<j) ans=max(ans,b[j]-b[i]+min((c[j]-c[i])*2*k,xy)+1);
            else if(i>j) ans=max(ans,b[j]-b[i]-max(xy-(cnt-(c[i]-c[j]))*2*k,0ll)+1);
            else continue;
    cout<<ans;
    yuanshen:;
    return 0;
}
```


---

## 作者：Yasuraoka_Hanabi (赞：3)

D题评了 2400* 而 F 题也才 2600*。这题真的这么难吗... 我 vp 的思考时间甚至比公认傻逼的 E 还短...

------------

首先，设路程中走到的最大的点是 $maxv$，最小的点是 $minv$，则 $ans=maxv-minv+1$。

然后，观察到，当移动量 $a$ 确定后，第 $i$ 步后所处的位置 $s_i$ 实际上是 $a_i$ 的前缀和。换言之，我们需要确定未定的 $a_i$，然后让前缀和的最大值与最小值的差最大。

设一段 $a$ 内有 $cnt$ 个未定位置。显然，这一段的和可以取到 $[sum-cnt\times k,sum+cnt\times k]$ 的任意一个值，其中 $sum$ 是这一段的已定位置的 $a$ 的和。可取值是一段区间，这是一个很有用的性质。另外，我们发现，可以利用它，来判断最后的 $a$ 的所有的和是否可能为 $0$。（正因为要先思考无解情况，那么就应该很容易发现这条性质）。

既然允许 $n^2$，那么就应该思考暴力一点的想法。所以不难想到，我们设 $minpos$ 是前缀和取到最小值的位置，$maxpos$ 是前缀和取到最大值的位置。不妨设 $minpos\lt maxpos$，那么，$maxv-minv$，实际上是 $a_{minpos+1}+...+a_{mapoxs}$，这是显然的。

让我们把 $a_{1\sim minpos}$ 的和记为 $A$，类似地，把 $a_{minpos+1\sim maxpos},a_{maxpos\sim n}$ 的和分别记为 $B,C$。则问题转化为：

$A,B,C$ 的可取值都是一段区间。需要在满足 $A+B+C=0$ 的情况下，让 $B$ 的值最大。

容易发现 $D=A+C$ 的可取值也是一段区间，那么变成了 $D=-B$。且 $B$ 要尽可能大。

如果 $B=B_{max}$ 的时候对应的 $D$ 也合法，那么毫无疑问就是最优秀的了。否则，我们会尝试把 $B$ 不断减一，直到对应的 $D$ 合法。注意到 $B$ 变化 $1$ 的时候，对应的 $D$ 也会变化 $1$。因此，$B$ 第一次合法的时候，$D$ 要么为 $D_{min}$ 要么为 $D_{max}$。而你知道了 $D$ 就能反推出 $B$ 了，此时判断 $B$ 是否合法即可。注意到这里的操作都是 $O(1)$ 的。

不难发现 $minpos\gt maxpos$ 的时候同理，为了方便，其实可以把 $a$ 全部取 $\min$ 再做一遍 $minpos\lt maxpos$ 的情况的......

显然，时间复杂度为 $O(n^2)$。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
#define op(x) ((x&1)?x+1:x-1)
#define odd(x) (x&1)
#define even(x) (!odd(x))
#define lc(x) (x<<1)
#define rc(x) (lc(x)|1)
#define lowbit(x) (x&-x)
#define mp(x,y) make_pair(x,y)
#define int ll
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
using namespace std;
const int MAXN=3010;
ll n,k,a[MAXN],sum1[MAXN],sum2[MAXN];
ll ans=1;
array<ll,2> calc(int x,int y){
    if(x>y)return {0,0};
    ll S=sum1[y]-sum1[x-1],cnt=sum2[y]-sum2[x-1];
    return {S-cnt*k,S+cnt*k};
}
int check(ll pos,array<ll,2>inv){return pos>=inv[0]&&pos<=inv[1];}
void solve(){
    if(calc(1,n)[0]>0 | calc(1,n)[1]<0)return (void)(ans=-1);
    //1. minpos<maxpos
    rep(minpos,0,n-1)rep(maxpos,minpos+1,n){
        array<ll,2>inv1={calc(1,minpos)[0]+calc(maxpos+1,n)[0],calc(1,minpos)[1]+calc(maxpos+1,n)[1]};
        array<ll,2>inv2=calc(minpos+1,maxpos);
        if(inv2[1]<=0)continue;
        if(inv1[0]>=0)continue;
        if(check(-inv2[1],inv1))ans=max(ans,inv2[1]+1);
        if(check(-inv1[0],inv2))ans=max(ans,-inv1[0]+1);
        if(check(-inv1[1],inv2))ans=max(ans,-inv1[1]+1);
    }
    //2. maxpos<minpos
    rep(maxpos,0,n-1)rep(minpos,maxpos+1,n){
        array<ll,2>inv1={calc(1,maxpos)[0]+calc(minpos+1,n)[0],calc(1,maxpos)[1]+calc(minpos+1,n)[1]};
        array<ll,2>inv2=calc(maxpos+1,minpos);
        if(inv2[0]>=0)continue;
        if(inv1[1]<=0)continue;
        if(check(-inv2[0],inv1))ans=max(ans,-inv2[0]+1);
        if(check(-inv1[0],inv2))ans=max(ans,inv1[0]+1);
        if(check(-inv1[1],inv2))ans=max(ans,inv1[1]+1);
    }
}
signed main(){
    cin>>n>>k;
    rep(i,1,n)cin>>a[i];
    rep(i,1,n){
        sum1[i]=sum1[i-1];sum2[i]=sum2[i-1];
        if(a[i])sum1[i]+=a[i];
        else sum2[i]++;
    }
    solve();
    cout<<ans;
    return 0;
}
```

---

## 作者：yyz1005 (赞：0)

属于是被翻译给绕晕了。

注意到要求的实际上就是 $\{a_n\}$ 前缀和数组的极差。

注意到极差一定是原数组某一段区间的和的绝对值。

例如极差 $S=|sum_x-sum_y|$，那么极差就是 $sum_x$，$sum_y$ 之间的数。

然后 $n \le 3000$，考虑枚举原数组上的这个区间。

对于一个区间，设区间内被固定的数和为 $s_1$，区间外的为 $s_2$，区间内外分别有 $c_1$，$c_2$ 个需要构造的位置。

注意到合法的构造需要最终和为 $0$。

注意到一个显然的做法是考虑区间外能构成的最大最小值。

那么只需要考虑

$$\text{区间内最大/小值}+\text{区间外最小/大值}$$

是否可以构造。

也就是 $\min\{\text{区间内最大值,区间外最小值}\}$ 与 $\min\{\text{区间内最小值,区间外最大值}\}$。

另外注意这个东西结果要 $+1$，因为问的是能到的点不是点之间的距离。

[Code](https://codeforces.com/contest/1680/submission/248877876)

---

## 作者：Lates (赞：0)

钦定两个点 $i,j$，分别表示取到最大值和最小值位置。

假设所有非零操作结束后为 $d$，那么填入数的和为 $-d$

- $i\le j$

假设前 $i$ 次操作后已经到了 $p$，那 $\max = p,\min = p + \Delta+\delta$

$\delta$ 表示 $i+1 \to j$ 的增量。$\Delta$ 表示已知的非零增量之和。

$ans = \max-\min+1=-\delta+1$，问题转化为最小化 $\delta$。

有两个限制，设 $i\to j$ 中有 $t$ 个空位，所有操作一共有 $c$ 个空位，那么 $\delta \ge t\times (-k)$。

同时，$\delta \ge -d-(c-t)\times k$ (考虑除 $i+1\to j$ 空位的限制)

取max即可。

- $i>j$

同上，转化为求 $\delta$ 的最大值。

---

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define int long long 
inline int read(){
	int x=0,v=1,ch=getchar();
	while(ch<'0' || ch>'9'){
		if(ch=='-')v=0;
		ch=getchar();
	}while(ch>='0' && ch<='9'){
		x=(x*10) + (ch^'0');
		ch=getchar();
	}return v?x:-x;
}
const int MAX=3005;
int n,k,a[MAX],p[MAX],c[MAX];
signed main(){
	n=read(),k=read();
	for(register int i=1;i<=n;++i){
		a[i] = read();
		p[i] = p[i-1] + a[i];
		c[i] = c[i-1] + (a[i] == 0);
	}
	if(! (p[n] - c[n] * k <= 0 && 0 <= p[n] + c[n] * k) )
		return puts("-1"),0;
	int ans = 0 , d = -p[n];
	for(register int i=1;i<=n;++i){
		for(register int j=1;j<=n;++j){
			// i -> max , j -> min ,{ max - min } max
			int ret ,t;
			if(i<=j){
//				printf("%lld %lld\n",i,j); 
				t = c[j] - c[i];
				ret = p[j] - p[i] + max(t * (-k),d+(c[n]-t) * (-k)) ;
				ans = max(ans,-ret);
			}else {
				t = c[i] - c[j];
				ret = p[i] - p[j] + min(t*k,d+(c[n]-t)*k);
				ans=max(ans,ret);
			}
		}
	}
	cout << ans+1;
	return 0;
}
```


---

