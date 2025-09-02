# [BalticOI 2009] 甲虫 (Day1)

## 题目描述

**译自 [BalticOI 2009](http://www.csc.kth.se/contest/boi/tasks.php) Day1 T1「[Beetle](http://www.csc.kth.se/contest/boi/beetle.pdf)」**

有一只甲虫处于一根水平的树枝。因为他沉迷数学无法自拔，所以他觉得很像是在 $x$ 轴上。

在同一根树枝上，还有 $n$ 滴露水。每滴露水占用 $m$ 个单位的水分。相对于甲虫的位置，他们的坐标分别是 $x_1,x_2,\dots,x_n$。

显然，这一天将会骄阳似火。每过一个时间单位，就会有一个单位的水分从每一滴露水流失。这只甲虫受尽了烈阳的折磨，以至于每当它碰到一滴露水都能瞬间喝完。在每个时间单位中它能移动一个单位的距离。

所以你要写一个程序，根据露水的坐标，计算出甲虫**最多**能喝到的水。

## 说明/提示

$0 \le n \le 300,1 \le m \le 1,000,000,-10,000 \le x_1,x_2,\dots,x_n \le 10,000,$ 对于所有 $i \ne j,x_i \ne x_j$。

## 样例 #1

### 输入

```
3 15
6
-3
1```

### 输出

```
25```

# 题解

## 作者：wwlw (赞：17)

[[BalticOI 2009]甲虫](https://www.luogu.com.cn/problem/P4870)

![](https://img2020.cnblogs.com/blog/1604911/202012/1604911-20201201080431418-2033900091.png)

### Solution

比较套路的区间dp，先按坐标排序，再找出零点所在位置，记为 $pos$。设状态 $dp[i][j][0/1]$ 表示取完区间 $[i,j]$ 的所有水滴且最后位置在左边/右边的最大收益，但时间不好算，可以再开一个 $t[i][j][0/1]$ 来记录最优解转移到 $dp[i][j][0/1]$ 时的时间，那么转移就很显然了。

```cpp
#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
#define N 307
#define ll long long
 
ll dp[N][N][2],t[N][N][2],a[N];
int n,m;
int main(){
    freopen("data.in","r",stdin);
    freopen("user.out","w",stdout);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
    sort(a+1,a+1+n+1);
    int pos;
    for(int i=1;i<=n+1;i++)
        if(!a[i]){pos=i;break;}
    memset(dp,-63,sizeof(dp));
    dp[pos][pos][0]=dp[pos][pos][1]=0;
    t[pos][pos][0]=t[pos][pos][1]=m;
    ll ans=0;
    for(int l=2;l<=n+1;l++)
        for(int i=1,j=i+l-1;j<=n+1;i++,j++){
            if(dp[i+1][j][0]+t[i+1][j][0]-(a[i+1]-a[i])>dp[i][j][0]){
                dp[i][j][0]=dp[i+1][j][0]+t[i+1][j][0]-(a[i+1]-a[i]);
                t[i][j][0]=t[i+1][j][0]-(a[i+1]-a[i]);
            }
            if(dp[i+1][j][1]+t[i+1][j][1]-(a[j]-a[i])>dp[i][j][0]){
                dp[i][j][0]=dp[i+1][j][1]+t[i+1][j][1]-(a[j]-a[i]);
                t[i][j][0]=t[i+1][j][1]-(a[j]-a[i]);
            }
            if(dp[i][j-1][1]+t[i][j-1][1]-(a[j]-a[j-1])>dp[i][j][1]){
                dp[i][j][1]=dp[i][j-1][1]+t[i][j-1][1]-(a[j]-a[j-1]);
                t[i][j][1]=t[i][j-1][1]-(a[j]-a[j-1]);
            }
            if(dp[i][j-1][0]+t[i][j-1][0]-(a[j]-a[i])>dp[i][j][1]){
                dp[i][j][1]=dp[i][j-1][0]+t[i][j-1][0]-(a[j]-a[i]);
                t[i][j][1]=t[i][j-1][0]-(a[j]-a[i]);
            }
            ans=max(ans,max(dp[i][j][0],dp[i][j][1]));
        }
    printf("%lld",ans);
}
/*
3 15
6 -3 1
*/
```

然后你就可以得到 $76$ 分的高分。（这是我没有想到的）

上述做法的问题在于虽然 $dp[i][j][0/1]$ 在当前是最优的，但是 $t[i][j][0/1]$ 可能已经被减得很小了，甚至是负的，对后面的转移不利（所以这直接就是个假作法）。转换思路，考虑费用提前算，枚举当前必选的水滴的个数，然后考虑进行dp。状态 $dp[i][j][0/1]$ 变为在选完区间 $[i,j]$ 且最后位置在左边/右边，能使得到水滴丢失的最少水分是多少，这个状态的实质是让上文的 $t$ 尽量大，而对后面的状态产生正影响，那么这个算法的正确性就显然了。转移也很显然。那么对于不同的选取个数 $lim$ ，分别进行一次dp后，答案就是
$$lim\times m-\min \limits_{1\leq l\leq l+lim-1\leq n}\{dp[l][l+lim-1]\}$$
那么总的答案就是
$$\max \limits_{1\leq lim \leq n} \{lim\times m-\min \limits_{1\leq l\leq l+lim-1\leq n}\{dp[l][l+lim-1]\}\}$$

复杂度 $O(n^3)$
```cpp
#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
#define N 307
#define ll long long

int n,m,pos=0;
ll dp[N][N][2],a[N];

inline ll calc(int lim){
    memset(dp,127,sizeof(dp));
    dp[pos][pos][0]=dp[pos][pos][1]=0;
    for(int l=2;l<=lim;l++)
        for(int i=1,j=i+l-1;j<=n;i++,j++){
            dp[i][j][0]=min(dp[i][j][0],min(dp[i+1][j][0]+(a[i+1]-a[i])*(lim-l+1),dp[i+1][j][1]+(a[j]-a[i])*(lim-l+1)));
            dp[i][j][1]=min(dp[i][j][1],min(dp[i][j-1][1]+(a[j]-a[j-1])*(lim-l+1),dp[i][j-1][0]+(a[j]-a[i])*(lim-l+1)));
        }
    ll ret=(1LL<<60);
    for(int i=1,j=i+lim-1;j<=n;i++,j++)
        ret=min(ret,min(dp[i][j][0],dp[i][j][1]));
//    printf("%lld\n",ret);
    return ret;
}

int main(){
//    freopen("beetle.in","r",stdin);
//    freopen("beetle.out","w",stdout);
    scanf("%d%d",&n,&m);
    bool tag=0;
    for(int i=1;i<=n;i++)
        scanf("%lld",&a[i]),tag|=(!a[i]);
    if(!tag) n++;
    sort(a+1,a+1+n);
    for(int i=1;i<=n;i++)
        if(!a[i]){pos=i;break;}
    ll ans=-1;
    for(int i=1;i<=n;i++)
        ans=max(ans,i*m-calc(i)-(!tag? m:0));
    printf("%lld",ans);
}
/*
3 15
6 -3 1
*/
```

### Tips
原来的所有坐标中可能有 $0$，也可能没有。这会对答案产生影响，但简单讨论一下就可以了。

---

## 作者：FjswYuzu (赞：12)

不知道有没有人做过 Sue 的小球这道题没有。这道题是一样的。

考虑到这个露水会变成 $0$ 而不是 Sue 的小球里面的负数，所以说我们考虑吃的露水数量。注意到如果吃多了出现负数的水也不会比这个更优，而且我们也枚举到了，所以说我们暂先不管。

枚举露水的数量。因为露水是会一直减少的，你不可能越过一个不吃去吃另外一个，所以说满足区间 dp 的性质。知道枚举露水的数量，就可以枚举长度一定的区间进行 dp。关键在于如何 dp。你首先对露水排个序嘛。

因为我们已经知道了露水的总量，并且我们还知道，时间会对每一个还没有吃掉的露水造成负贡献。然而我们的区间 dp 在保存状态的时候，保存了这个区间的大小，也就可以推出有多少露水还没有被吃掉。

于是考虑费用提前计算，定义 $dp_{l,r,0 \operatorname{or} 1}$ 表示现在吃完了 $[l,r]$ 里面的所有露水，现在在 $l$ 或 $r$，的最多能喝到的水量。因为我们确实无法保存时间，于是我们就干脆在移动的过程中减去已经丢失的水量（相对的，因为我们已经在移动的过程中减去了丢失的水量，我们可以直接假设现在的露水大小就是 $m$，因为我们已经将时间的负贡献减去了）。令 $N-r+l$（当前枚举的露水总量 $N$ 转移的区间 $[l,r]$）为 $s$，可以列出方程：

$$
\begin{cases}
dp_{l,r,0}= \max (dp_{l+1,r,0}-(a_{l+1}-a_l) \times s,dp_{l+1,r,1}-(a_r-a_l)\times s)+m  \\
dp_{l,r,1} = \max(dp_{l,r-1,1}-(a_r-a_{r-1})\times s,dp_{l,r-1,0}-(a_r-a_l) \times s)+m
\end{cases}
$$

考虑解释这个方程，可以理解成为周围的露水都还在丢失，在这里减去贡献；相对认为当前这个露水没有损失水量，因为损失的水量我们已经丢去了。

dp 过程 $O(n^2)$，枚举大小 $O(n)$，总时间复杂度 $O(n^3)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int Abs(int x){return x>0?x:-x;}
int dp[305][305][2],n,m,a[305],ans;
int main(){
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;++i)	scanf("%d",&a[i]);
	sort(a+1,a+1+n);
	for(int N=1;N<=n;++N)
	{
		memset(dp,0,sizeof dp);
		for(int i=1;i<=n;++i)	dp[i][i][0]=dp[i][i][1]=m-Abs(a[i])*N,ans=max(ans,dp[i][i][0]);
		for(int dis=2;dis<=N;++dis)
		{
			for(int l=1,r=dis;r<=n;++l,++r)
			{
				dp[l][r][0]=max(dp[l+1][r][0]+m-Abs(a[l+1]-a[l])*(N-dis+1),dp[l+1][r][1]+m-Abs(a[r]-a[l])*(N-dis+1));
				dp[l][r][1]=max(dp[l][r-1][1]+m-Abs(a[r]-a[r-1])*(N-dis+1),dp[l][r-1][0]+m-Abs(a[r]-a[l])*(N-dis+1));
				ans=max(ans,max(dp[l][r][0],dp[l][r][1]));
			}
		}
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：all_for_god (赞：10)

## [P4870 [BalticOI 2009 Day1] 甲虫](https://www.luogu.com.cn/problem/P4870)

首先数据范围很小，而每个水珠的贡献一直在变化。

由于所有水珠的初始水量都相同，因此如果我们知道了经过的时间，那我们就可以统计每个水珠的贡献。

但是时间范围太大了，不好直接去放在状态里。那如何抛弃掉巨大的 $m$ 与 $x_i$ 让时间复杂度与 $n$ 挂钩呢？

于是我们倒过来想，由于时间复杂度可以支持到 $n^3$，因此我们直接去枚举到底要吃多少个水珠，去计算总共亏损了多少水量。

然后就是区间DP的套路了，设 $f_{l,r,0/1}$ 表示吃完了 $l$ 到 $r$ 之间的水珠之后站在左或者右端点的亏损的最小值。

而状态转移就如下（这个应该得会吧）：
```
f[l][r][0]=min({f[l][r][0],f[l+1][r][0]+(num-(r-l))*(loc[l+1]-loc[l]),f[l+1][r][1]+(num-(r-l))*(loc[r]-loc[l])});
f[l][r][1]=min({f[l][r][1],f[l][r-1][1]+(num-(r-l))*(loc[r]-loc[r-1]),f[l][r-1][0]+(num-(r-l))*(loc[r]-loc[l])});
```
表示的就是站在左边或者站在右边从左边或者右边走过来需要亏的水量。`num` 指枚举的要吃水珠的数量。

由于当前这个暂时还没有吃（中间的路还要赶），因此还剩下 $num-(r-l+1)+1$ 个水珠还没有吃，也就是还在晒着亏水量。

而答案就是

```
m*(r-l)-min(f[l][r][0],f[l][r][1])
```

取max。

注意这里假设水珠水量可以被晒成负数。能够这样处理的原因是如果水被晒成负数，那一定不优，因此不会选。

关于为何不是 $m*(r-l+1)$ 的问题，应该不是因为所谓的 “因为还没喝掉要喝的水，所以减一”，而是因为在开头：

```
for(int i=1;i<=n;i++) cin>>loc[i],z=(loc[i]==0)||z;
if(!z) loc[++n]=0;

```
这是避免没有水滴在 0 处不好 DP 的问题。因此我们直接强制在 0 处加上一个水滴，然后这里就需要考虑到不能多算一个水滴的答案，就要减一。

但是如果本来有水滴在 0 处，就要把多减的加回去：
```
cout<<ans+z*m<<'\n';
```

因此如果你愿意也可以写成这样：
```
m*(r-l+1)-min(f[l][r][0],f[l][r][1])

cout<<(ans==0?0:(ans-(z^1)*m))<<'\n';
```
但很可惜本题并没有 0 处有水滴的情况，建议加一下 hack。
时间复杂度 $O(n^3)$。
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=605;
const int inf=1e18;
int n,m,loc[N],ans=0,f[N][N][2],pos;bool z=0;
signed main()
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>loc[i],z=(loc[i]==0);
	if(!z) loc[++n]=0;
	sort(loc+1,loc+n+1);pos=lower_bound(loc+1,loc+n+1,0)-loc;
	for(int num=2;num<=n;num++) 
	{
		memset(f,0x3f,sizeof(f));
		f[pos][pos][0]=f[pos][pos][1]=0;
		for(int len=2;len<=num;len++) 
		for(int l=1;l+len-1<=n;l++)
		{
			int r=l+len-1;
			f[l][r][0]=min({f[l][r][0],f[l+1][r][0]+(num-(r-l))*(loc[l+1]-loc[l]),f[l+1][r][1]+(num-(r-l))*(loc[r]-loc[l])});
			f[l][r][1]=min({f[l][r][1],f[l][r-1][1]+(num-(r-l))*(loc[r]-loc[r-1]),f[l][r-1][0]+(num-(r-l))*(loc[r]-loc[l])});
			ans=max({ans,m*(r-l)-min(f[l][r][0],f[l][r][1])});
		}
	}
	cout<<ans+z*m<<'\n';return 0;
}
```

然后最近写了几道单调性，想可不可以优化，发现还真行。
>由于少喝水滴一定会劣，如果假定水滴可能减少为负数（就是本题的处理方法），再喝已经为负数的水滴也一定劣。
那么答案就一定会形成一个在吃的水滴数为x轴，最优答案为y轴的坐标系里的严格的**上凸壳**。

感觉已经够清楚了。然后就是找上凸壳的顶点，三分。
时间复杂度 $O(n^2\log n)$ ~~然后就被 $O(n^3)$ 吊打~~ 
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=605;
const int inf=1e18;
int n,m,loc[N],ans=0,f[N][N][2],pos;bool z=0;
int solve(int num)
{
	int res=0;
	memset(f,0x3f,sizeof(f));
	f[pos][pos][0]=f[pos][pos][1]=0;
	for(int len=2;len<=num;len++) 
	for(int l=1;l+len-1<=n;l++)
	{
		int r=l+len-1;
		f[l][r][0]=min({f[l][r][0],f[l+1][r][0]+(num-(r-l))*(loc[l+1]-loc[l]),f[l+1][r][1]+(num-(r-l))*(loc[r]-loc[l])});
		f[l][r][1]=min({f[l][r][1],f[l][r-1][1]+(num-(r-l))*(loc[r]-loc[r-1]),f[l][r-1][0]+(num-(r-l))*(loc[r]-loc[l])});
		res=max({res,m*(r-l)-min(f[l][r][0],f[l][r][1])});
	}ans=max(ans,res);
	return res;
}
signed main()
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>loc[i],z=(loc[i]==0)||z;
	if(!z) loc[++n]=0;
	sort(loc+1,loc+n+1);pos=lower_bound(loc+1,loc+n+1,0)-loc;
	int l=1,r=n;
	while(l<r-1)
	{
		int mid=(l+r)>>1,mmid=(mid+r)>>1,resm=solve(mid),resmm=solve(mmid);
		if(resm>resmm) r=mmid;else l=mid;
	}
	ans=max({ans,solve(l),solve(r)});
	cout<<ans+z*m<<'\n';return 0;
}
```
蒟蒻的第一篇题解，点个赞呗：）

---

## 作者：wasa855 (赞：8)

首先明显要将所有水滴排序。   
然后反着思考，看甲虫最少能避免多少水滴的蒸发。   
定义```f[i][j][0]```为喝光```i```到```j```的所有水滴并且留在左边的最少蒸发，```f[i][j][1]```为喝光```i```到```j```的所有水滴并且留在右边的最少蒸发。   
然后起始点一定是0，如果水滴中没有0的话，就手动加上一个水滴，最后减掉。   
注意每次dp要把数组清空。   
转移方程：
```
// k为i到j的水滴个数，l为总用时
f[i-1][j][0]=min(f[i-1][j][0],min(f[i][j][0]+(l-k)*(a[i]-a[i-1]),f[i][j][1]+(l-k)*(a[j]-a[i-1])));
f[i][j+1][1]=min(f[i][j+1][1],min(f[i][j][1]+(l-k)*(a[j+1]-a[j]),f[i][j][0]+(l-k)*(a[j+1]-a[i])));
```
最后枚举```l```，求出每个```l```对应的答案，求出最大值即可。  
#### 最后，祝大家NOIP2018 RP++   
附上AC的代码：   
``` cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int start=0;
ll n,m;
ll a[305];
ll f[305][305][2];//0 zuo ,1 you
#define INF 0x7fffffff
ll dp(int l)
{
    memset(f,0x7f,sizeof(f));
    f[start][start][0]=0;
    f[start][start][1]=0;
    for(int k=1;k<=l;k++)
    {
        for(int i=1;i<=n-k+1;i++)
        {
            int j=k+i-1;
            f[i-1][j][0]=min(f[i-1][j][0],min(f[i][j][0]+(l-k)*(a[i]-a[i-1]),f[i][j][1]+(l-k)*(a[j]-a[i-1])));
            f[i][j+1][1]=min(f[i][j+1][1],min(f[i][j][1]+(l-k)*(a[j+1]-a[j]),f[i][j][0]+(l-k)*(a[j+1]-a[i])));
        }
    }
    ll minn=INF;
    for(int i=1;i<=n-l+1;i++)
    {
        minn=min(minn,min(f[i][i+l-1][0],f[i][i+l-1][1])); 
    }
    return minn;
}
int main()
{
    cin>>n>>m;
    bool zero=false;
    for(int i=1;i<=n;i++)
    {
        scanf("%lld",&a[i]);
        if(a[i]==0)
        {
            zero=true;
        }
    }
    if(zero==false)
    {
        a[++n]=0;
    }
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++)
    {
        if(a[i]==0)
        {
            start=i;
        }
    }
    ll maxn=-1;
    for(int i=1;i<=n;i++)
    {
        maxn=max(maxn,m*i-dp(i));
    }
    if(zero==false)
    {
        maxn-=m;
    }
    cout<<maxn<<endl;
    return 0;
}
```

---

## 作者：LIUYC_C (赞：5)

 [题目链接。](https://www.luogu.com.cn/problem/P4870)
 
##  大体思路：
我习惯题解写出思考过程，而不是单独局限于一道题目，联系处理这种题目的思维我认为更重要。

首先拿到题目，啪的一下，很快啊，一眼这不是贪心吗，每次取离得更近的水，蒸发速率是一样的，因此~~正确性很显然~~。

然而当我写完提交，发现只有 44 分，很震惊。

进行了一个深度思考，哦，原来是从开头就错了，我只考虑到了两端距离不相等的情况，当距离相等的时候无法通过贪心选择是往左走还是往右走，也许可以再分别考虑两端，考虑两端局部最优解，很容易证明，这里的局部最优绝对代替不了整体最优解，所以贪心只能算是一个乱搞。

于是放上我的错误蒟蒻代码。

[Link。](https://www.luogu.com.cn/paste/jw1a7do1)

那么有没有一种方法可以很好的处理选择的问题呢，肯定就是 dp 啦。

具体来说，这是一道区间 dp，毕竟在一段数轴上，局部的贡献很容易转移，而且也可以覆盖整段区间。

我们设 $f_{l,r,0/1}$ 表示在 $[l,r]$ 区间内甲虫最后到左边 / 右边丢失的最小水分，这样就可以非常完美的解决贪心不知道往左还是往右走的问题（毕竟我都走了），那么怎么转移呢？

我们先对整个序列排序，保证 $x_{l+1} - x_{l}$ 可以表示数轴上两个相邻的位置的距离。

那么对于 $f_{l,r,0}$ 来说，它会等于：
	
  $$f_{l,r,0}=\min(f_{l+1,r,0}+(len-(r-l+1-1)\times(x_{l+1}-x_{l}))$$
  
$len$ 表示区间长度，$(r-l+1)$ 表示我这段区间内喝掉的水的长度。
  
  **这只是第一个转移，后面的肯定可以自行推出。**
 
 这个转移是什么意思呢，它表示我到 $[l+1,r]$ 区间的左边浪费了的最少的水，加上我从 $x_{l+1}$ 到 $x_{l}$ 的距离乘上我还没喝掉的水的大小（因为我每走一步就会浪费掉一些水，至于为什么减一，看注释），这两个值的和就是 $f_{l,r,0}$ 的大小。
  
  
其他的转移应该没什么难度了。

具体看代码理解。

## 代码实现：
  
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=302;

int ans=0;
int x[N];
int f[N][N][3];

int main(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        scanf("%d",&x[i]);
    }
    
    x[++n]=0; //一定是从零开始找，便于枚举，所以一定要有一个零的位置。
    sort(x+1,x+n+1);
    int pos=lower_bound(x+1,x+n+1,0)-x;//找到0的位置
    
    
    for(int len=1;len<=n;len++){
        memset(f,127,sizeof f);
        f[pos][pos][0]=0,f[pos][pos][1]=0;//初始化
        for(int siz=2;siz<=len;siz++){//区间dp一般套路
            for(int l=1;l+siz-1<=n;l++){
                int r=l+siz-1;
                f[l][r][0]=min(f[l+1][r][0]+(len-(r-l))*(x[l+1]-x[l]),f[l][r][0]);
                f[l][r][0]=min(f[l+1][r][1]+(len-(r-l))*(x[r]-x[l]),f[l][r][0]);
                f[l][r][1]=min(f[l][r-1][1]+(len-(r-l))*(x[r]-x[r-1]),f[l][r][1]);
                f[l][r][1]=min(f[l][r-1][0]+(len-(r-l))*(x[r]-x[l]),f[l][r][1]);
                ans=max(ans,m*(r-l+1-1)-f[l][r][0]);//因为还没喝掉要喝的水，所以减一,上面同理
                ans=max(ans,m*(r-l+1-1)-f[l][r][1]);
            }
        }
    }
    
    cout<<ans<<endl;
    return 0;
    
}
```
时间复杂度 $O(n^3)$。





---

## 作者：H_D_NULL (赞：5)

#### 本题解重点讲解整体思路，细节见代码

------------


### 确定做法

看到“数轴”和“最大价值”，自然而然地想到了区间DP，自己写了几个式子推了几种情况，发现不掉头或只掉一次头不一定最优，故排除贪心，大概确定做法为区间DP；观察数据范围，发现 $n$ 是 $O(n^3)$ 的范围，便想到可能要额外枚举某个条件后再跑一遍区间DP（~~伏笔~~）。



------------


### 确定状态

先思考用 $f$ 数组维护 $l$ 到 $r$ 区间可得的最大价值。本题中，每个水滴的价值（水分）随时都在变化，不同时间走到同一个点也可能会产生不同的价值，传统的区间DP状态 $f[l][r]$ 无法同时维护时间和直接价值，因为时间的上界过大且无法离散化，所以也无法增加一维状态。

~~但是~~经过观察我们发现，一个区间的价值等于区间初始价值（水滴数乘以 $m$）减去流失的价值，~~很显然~~。但是重要的是对于每一个区间，剩下水滴的数目可以确定，而水分流失的总速度也就确定，所以可以用 $f[l][r]$ 维护区间内已流失水分的最小值。

因为甲虫爬完区间后停在区间的哪一边（显然不可能是中间）不仅对本次的价值有影响，也影响下一次状态的转移，所以用 $f[l][r]$ 和 $f[r][l]$ 分别维护即可。


------------


### 处理答案

维护了流失水分的最小值，输出答案时就要用总的水滴值减去这个最小值，产生了如下问题：

- 水滴的水分不会减为负值，因为状态中没有一维表示时间，无法判断这个区间的答案是否包含了水滴为负值的情况；

所以，我们考虑枚举这个“时间”，由于时间过大，我们用可以喝到的水滴数来限制时间，及**枚举喝到的水滴数**（~~呼应~~），对于每一个水滴数，单独跑一遍区间DP，答案为这些价值的最大值。


------------

### ~~感性~~证明

从定义出发，甲虫喝到最多水的情况，必是已经喝过了所有的水滴或爬到下一个水滴时所有水滴已经蒸发完了。

如果枚举的水滴数大于了实际可以喝到的水滴数，则可以理解为甲虫在实际的最优情况下，又喝了一个价值为负的水滴，最后的价值必定小于最优价值，所以枚举一定能保证得到的最优价值是符合实际的。


------------

*Talk is cheap, show me the code*

```cpp
#include<bits/stdc++.h>
#define re register
using namespace std;

inline int read(){
	re int ret=0,f=1;
	re char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		ret=(ret<<1)+(ret<<3)+(c^48);
		c=getchar();
	} return ret*f;
}

int n,m,st,ans;
int loc[305];
int f[305][305];
//用f[i][j]和f[j][i]来代表停在哪一边 

bool IF; //判断是否有水滴在起始位置 

int main(){
	n=read(); m=read();
	for(re int i=1;i<=n;i++){
		loc[i]=read();
		if(!loc[i]) IF=1;
	} if(!IF) loc[++n]=0;
	//如没有水滴在起始位置，先添加一个，最后减去这个水滴的价值即可 
	sort(loc+1,loc+1+n);
	st=lower_bound(loc+1,loc+1+n,0)-loc;
	//0的位置 
	for(re int maxl=1;maxl<=n;maxl++){
		memset(f,63,sizeof(f)); f[st][st]=0;
		for(re int len=2;len<=maxl;len++){
			for(re int i=max(1,st-len+1),j;i<=st;i++){
				j=i+len-1; if(j>n) break;
				if(i<st){
					f[i][j]=f[j][i+1]+(loc[i+1]-loc[i])*(maxl-j+i)+(loc[j]-loc[i])*(maxl-j+i-1);
					f[j][i]=f[j][i+1]+(loc[i+1]-loc[i])*(maxl-j+i);
				}
				if(j>st){
					f[i][j]=min(f[i][j],f[i][j-1]+(loc[j]-loc[j-1])*(maxl-j+i));
					f[j][i]=min(f[j][i],f[i][j-1]+(loc[j]-loc[j-1])*(maxl-j+i)+(loc[j]-loc[i])*(maxl-j+i-1));
				}
				//状态转移要考虑从两边转移 
			}
		} //经典区间DP，不必多说 
		for(re int i=max(1,st-maxl+1),j,now;i<=st;i++){
			j=i+maxl-1; if(j>n) break;
			now=maxl*m-min(f[i][j],f[j][i])-(IF?0:m);
			ans=max(ans,now);
		}
	}
	printf("%d",ans);
	return 0;
}
```



---

## 作者：L_M_ (赞：4)

有道类似的题：奶牛吃草（好像不是洛谷上的）一样的意思

这种问题可以逆向思考：令f[i][j]表示位于区间[i,j]的最少损失量

由于在经过一段区间的时候，如果这段区间有水，那么一定要把它喝掉，也就是说，在一段区间[i,j]访问完毕后，这段区间上是没有水的

由此易知，甲虫要么位于左端，要么位于右端

因此，令f1[i][j]表示停在左端时，最小损失;f2[i][j]就是右端

有了这样的想法，转移方程不难得出：
```
f1[i][j] = min(f1[i + 1][j] + dis[i][i + 1] * (n - j + i),
f2[i][j - 1] + dis[j][j - 1] * (n - j + i));
```
f2同理

---

## 作者：漠寒 (赞：3)

## 分析

关于此题的 $dp$ 思路，其实可以先去做一做这道题[P1220 关路灯](https://www.luogu.com.cn/problem/P1220)。两道题的思路大体相同，不过这道题有一个细节，就是露水的水分不会降为负数，因此不能一次 $dp$ 完，因此我们考虑枚举喝到多少枚露水，以避免过程中出现某一滴露水过度消费的情况。

## 思路

用 $dp[i][j][0/1]$ 表示喝完 $i$ 到$j$ 所有露水后所消耗的最小水分，0表示喝完后位于最左端，1表示位于最右端，以此来确定下一次 $dp$ 甲虫所需走的时间，答案即为总水分减去消耗即可。

注意初始位置为0，若没有该点，需新加一个，特殊处理。

### 代码

```
#include<bits/stdc++.h>
using namespace std;
int n,m,qd,a[305],dp[305][305][2];

int jc(int mb){
	memset(dp,127,sizeof(dp));
	dp[qd][qd][0]=0;
	dp[qd][qd][1]=0;//初始化 
	for(int l=2;l<=mb;l++){
		for(int i=1,j=i+l-1;j<=n;j++,i++){
			dp[i][j][0]=min(dp[i][j][0],min(dp[i+1][j][0]+(a[i+1]-a[i])*(mb-l+1),dp[i+1][j][1]+(a[j]-a[i])*(mb-l+1)));
			dp[i][j][1]=min(dp[i][j][1],min(dp[i][j-1][1]+(a[j]-a[j-1])*(mb-l+1),dp[i][j-1][0]+(a[j]-a[i])*(mb-l+1)));
			//mb-l+1为喝这一滴露水前还有多少没喝，全部计入消耗 
		}
	}
	int mn=2e9;
	for(int i=1;(i+mb-1)<=n;i++){
		mn=min(mn,min(dp[i][i+mb-1][0],dp[i][i+mb-1][1]));
	}
	return mn;
}

int main()
{
	cin>>n>>m;
	int rt=0;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(!a[i])rt=1;//是否存在位置为0的露水 
	}
	if(!rt)n++;//若没有，新添一个 
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++){
		if(!a[i])qd=i;//确定起点 
	}
	int ans=-1;
	for(int i=1;i<=n;i++){//枚举喝水滴数 
		ans=max(ans,m*i-jc(i));
	}
	if(!rt)ans-=m;//特殊处理，加的一滴并无水分 
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：RockyYue (赞：2)

先将 $x$ 升序排列。

因为是一维坐标，任何时刻喝过的露水必然为一段区间，故考虑设 $f_{i,j}$ 为喝过且仅喝过 $x_{[i,j]}$ 上的露水所能获得的最大收益。为了方便转移，再添加一维 $f_{i,j,0/1}$ 表示结束时在 $i$ 还是 $j$，设 $t_{i,j,0/1}$ 为达到 $f_{i,j,0/1}$ 最优时喝完 $x_{i/j}$ 上的水的时刻。

但是这样转移是错误的。因为区间整体用时最优并不代表结束时间最优，下一次喝水的贡献也就是不确定的，这样转移出来的答案也是错误的。

考虑优化状态设计。上一种方法的错误无非是前面走的方式会影响后面的转移，我们只需要将一个 $x_i$ 的影响（包括喝这个露水的收益和对后面喝的露水流失的影响）在转移时一并计算即可。发现这一次的收益其实就是 $m$ 减之前 $x$ 的影响，故我们仅需要计算流失的部分。设 $f_{i,j,0/1}$ 为喝过 $x_{[i,j]}$，最后喝了 $x_{i/j}$，这些露水流失部分的最小和。转移部分：

```cpp
f[i][j][0] = min(f[i + 1][j][0] + (x[i + 1] - x[i]) * 后面走的个数, f[i + 1][j][1] + (x[j] - x[i]) * 后面走的个数);
f[i][j][1] = min(f[i][j - 1][0] + (x[j] - x[i]) * 后面走的个数, f[i][j - 1][1] + (x[j] - x[j - 1]) * 后面走的个数);
```

这里 ```后面选的个数``` 需要由选的总个数来确定，故枚举 $l$ 为总共喝的露水数，则 ```后面选的个数``` 为 $l-(j-i)$，当前已经选了 $j-i$ 个点，包括这次更新的 $i/j$ 和 $[i,j]$ 外的，一共会对这些点产生流失，则答案为 $m\cdot i$ 减去对应的 $f_{i,i+l-1,0/1}$ 中的最小值，复杂度 $O(n^3)$。

对于初始状态，由 $x_i=0$ 的 $f$ 向外延伸，故若没有位置为 $0$ 的点，就添加一个这样的点，最终答案减去 $m$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 305;
int n, x[N], f[N][N][2];
int minConsume(int Len) {
	for (int i = 1; i <= n; ++i) {
		if (x[i] == 0) f[i][i][0] = f[i][i][1] = 0;
		else f[i][i][0] = f[i][i][1] = 1e16;
	}
	for (int len = 2; len <= Len; ++len) {
		for (int l = 1, r = len; r <= n; ++l, ++r) {
			int t = Len - len + 1;
			f[l][r][0] = min(f[l + 1][r][0] + (x[l + 1] - x[l]) * t, f[l + 1][r][1] + (x[r] - x[l]) * t);
			f[l][r][1] = min(f[l][r - 1][0] + (x[r] - x[l]) * t, f[l][r - 1][1] + (x[r] - x[r - 1]) * t);
		}
	}
	int res = 1e18;
	for (int l = 1, r = Len; r <= n; ++l, ++r) res = min(res, min(f[l][r][0], f[l][r][1]));
	return res;
}
signed main() {
	ios :: sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	int m, res = 0; cin >> n >> m;
	bool flg0 = 0;
	for (int i = 1; i <= n; ++i) cin >> x[i], flg0 |= (x[i] == 0);
	if (!flg0) x[++n] = 0;
	sort(x + 1, x + n + 1);
	for (int i = 1; i <= n; ++i) res = max(res, m * i - minConsume(i));
	if (!flg0) res -= m;
	cout << res << '\n';
	return 0;
}
```

---

## 作者：Blancа (赞：2)

## 题意
甲虫在坐标轴0位置，左右移动使得喝到的水最多，同时一单位时间甲虫可以移动一个单位距离，一单位时间每滴水分蒸发1单位体积
## 思路  
~~考场上没有看懂题目，把水滴的体积和单位距离搞混了~~  
这道题是一道很好的$dp$题目，其关键在于怎么定义  
按照一般的定义，$dp_{[l][r][0/1]}$表示已经喝了$l$到$r$区间的水之后，在$l$或$r$位置，喝到的水的最大值，但是对于不同的值而言，经过的时间不一样，无法算出下一次转移时新水滴的贡献，换句话说，就是不同的值对应的经过的时间不同，值最大的不一定是最优的，如果维护了时间和喝的总水滴体积，把每种状态全部存下来，并不好处理，时间复杂度很差，考虑换种定义状态  
在枚举一个$len$（表示要喝$len$滴水）的前提下，定义$dp_{[l][r][0/1]}$表示已经喝了$l$到$r$区间内所有的水滴，所浪费的水体积最小值，所谓浪费的水体积也就是蒸发掉的水体积数，其中包括了还没有喝的$(len - (r - l + 1))$滴水和已经喝掉的$(r - l + 1)$滴水的总浪费。  
此时浪费的水滴数很好算，知道了还没有喝的水滴数和这次需要移动的长度（即话费的时间），这次转移多浪费的水滴体积就是$(len - (r - l + 1) - 1)$ $\times$ $\bigtriangleup x $  
**转移方程**：  
定义$len$表示这次要喝$len$滴水，$siz = (r - l + 1)$  
$dp_{[i][j][0]}$ = $min(dp_{[l + 1][r][0]} + (len - siz + 1) * (x[l + 1] - x[l]), dp_{[l + 1][r][1]} + (len - siz + 1) * (x[r] - x[l]))$  
$dp_{[i][j][1]}$ = $min(dp_{[l][r - 1][1]} + (len - siz + 1) * (x[r] - x[r - 1]), dp_{[l][r - 1][0]} + (len - siz + 1) * (x[r] - x[l]))$  
### $Code$
```c++
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
inline int read () {
	int x = 0, f = 1; char ch = getchar();
	for (;!isdigit(ch); ch = getchar()) if (ch == '-') f = -1;
	for (; isdigit(ch); ch = getchar()) x = x * 10 + ch - '0';
	return x * f;
}
const int maxn = 405;
int n, m;
long long dp[maxn][maxn][2];
long long ans;
int x[maxn];
int main () {
	freopen ("beetle.in", "r", stdin);
	freopen ("beetle.out", "w", stdout);
	n = read(), m = read();
	int flag = 0;
	for (register int i = 1; i <= n; i++) {
		x[i] = read();
	}
	x[++n] = 0;
	sort (x + 1, x + 1 + n);
	int pos = lower_bound(x + 1, x + 1 + n, 0) - x;
	int r;
	for (register int len = 1; len <= n; len++) {
		memset (dp, 0x7f, sizeof dp);
		dp[pos][pos][0] = 0, dp[pos][pos][1] = 0;
		for (register int siz = 2; siz <= len; siz++) {
			for (register int l = 1; l + siz - 1 <= n; l++) {
				r = l + siz - 1;
				dp[l][r][0] = min (dp[l + 1][r][0] + (len - siz + 1) * (x[l + 1] - x[l]), dp[l][r][0]);
				dp[l][r][0] = min (dp[l + 1][r][1] + (len - siz + 1) * (x[r] - x[l]), dp[l][r][0]);
				dp[l][r][1] = min (dp[l][r - 1][1] + (len - siz + 1) * (x[r] - x[r - 1]), dp[l][r][1]);
				dp[l][r][1] = min (dp[l][r - 1][0] + (len - siz + 1) * (x[r] - x[l]), dp[l][r][1]);
				ans = max (ans, m * (siz - 1) - dp[l][r][1]);
				ans = max (ans, m * (siz - 1) - dp[l][r][0]);
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Nuyoah_awa (赞：1)

### 题目大意

一个数轴上有 $n$ 滴水，每滴水最开始有 $m$ 的大小，每个单位时间内，所有水减小 $1$，你也可以移动一个单位长度，问最多能喝道多少水。

### 题目分析

与 [P2466 [SDOI2008] Sue 的小球 ](https://www.luogu.com.cn/problem/P2466) 有点像。~~（双倍经验）~~

在数轴上左右移动收集某些东西，很明显的区间 DP 特征。

常规状态 $f_{l, r, 0/1}$，表示收集完 $l\sim r$，最高分数，但是在收集一个水滴的时候，之前已经过去多长时间也会对这个点的贡献（即剩余水的大小）有影响，所以我们考虑如何边 dp，边算影响。由于 $v$ 不会变，可以一边 dp 一边将这一步用时对于还未收集的水滴的影响算上，直接加答案里。

转移方程为：
$$f_{l, r, 0} = \max\begin{cases}f_{l+1, r, 0} + (x_{l+1} - x_{l}) \times (n - r + l) + m \\ f_{l+1, r, 1} + (x_{r} - x_{l}) \times (n - r + l) + m \end{cases}$$

到这里就是上面那道题的大体思路了，但是这道题我们会发现有可能我们只选一部分是最优解，但是上面的转移我们已经预支了我们不取的那些水滴会减少的值。

但是我们发现上述算法是 $\mathcal O(n^2)$ 的，而这道题的数据范围很明显支持 $\mathcal O(n^3)$ 算法，于是我们不妨再枚举一下最终我们会选几个水滴，然后做 $n$ 次上述 DP。特别的，这次我们需要保证我们枚举的 $l, r$ 之差在限制范围内。

转移方程与上面差不多就不粘了。

### code
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#define int long long

using namespace std;

const int N = 1e3 + 5, INF = 2e18;
int n, m, st, f[N][N][2], x[N], ans = 0;

signed main()
{
    scanf("%lld %lld", &n, &m);
    for(int i = 1;i <= n;i++)  scanf("%lld", &x[i]);
    x[++n] = 0;
    sort(x + 1, x + n + 1);
    for(int i = 1;i <= n;i++)
    {
        if(x[i] == 0)
            st = i;
    }
    for(int k = 1;k <= n;k++)
    {
        for(int i = 1;i <= n;i++)
            for(int j = 1;j <= n;j++)
                f[i][j][1] = f[i][j][0] = -INF;
        f[st][st][1] = f[st][st][0] = 0;
        for(int l = st;l >= 1;l--)
        {
            for(int r = st;r <= n && r - l < k;r++)
            {
                if(l == st && r == st)  continue;
                f[l][r][0] = max(f[l][r][0], f[l+1][r][0] - (x[l+1] - x[l]) * (k - r + l) + m);
                f[l][r][0] = max(f[l][r][0], f[l+1][r][1] - (x[r] - x[l]) * (k - r + l) + m);

                f[l][r][1] = max(f[l][r][1], f[l][r-1][0] - (x[r] - x[l]) * (k - r + l) + m);
                f[l][r][1] = max(f[l][r][1], f[l][r-1][1] - (x[r] - x[r-1]) * (k - r + l) + m);
                ans = max(ans, f[l][r][0]);
                ans = max(ans, f[l][r][1]);
            }
        }
    }
    printf("%lld\n", ans);
    return 0;
}

```

---

## 作者：NBest (赞：0)

和 P2466 那题的 dp 思路有点相似，只不过这题因为 $m$ 有上限，我们不能保证自己喝掉每一滴露水，这导致如果我们假定喝了全部露水然后跑 dp 的话会导致一些露水的贡献是负数因此不优。发现这道题可以跑 $O(n^3)$，所以我们直接枚举喝的露水个数即可。
### $Code$
```cpp
const int N=303;
int n,m,loc[N],f[2][N][N],ans;
int main(){
    n=read(),m=read();
    for(int i=1;i<=n;i++)loc[i]=read();loc[++n]=0;
    sort(loc+1,loc+1+n);
    int st=lower_bound(loc+1,loc+1+n,0)-loc;
    for(int maxl=2;maxl<=n;maxl++){
        memset(f,0x3f,sizeof(f));
        f[0][st][st]=f[1][st][st]=0;
        for(int len=2;len<=maxl;len++)
            for(int i=1,j=len;j<=n;i++,j++)
                f[0][i][j]=min(f[0][i+1][j]+(maxl-len+1)*(loc[i+1]-loc[i]),f[1][i+1][j]+(maxl-len+1)*(loc[j]-loc[i])),
                f[1][i][j]=min(f[0][i][j-1]+(maxl-len+1)*(loc[j]-loc[i]),f[1][i][j-1]+(maxl-len+1)*(loc[j]-loc[j-1]));
        for(int i=1;i<=n;i++)
            ans=max(ans,m*(maxl-1)-min(f[0][i][i+maxl-1],f[1][i][i+maxl-1]));
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：_ZSR_ (赞：0)

### [P4870 [BalticOI 2009 Day1] 甲虫](https://www.luogu.com.cn/problem/P4870)

不同于关路灯那道题，露水不必全都喝。因此我们考虑枚举喝了几滴露水，然后也是求蒸发的最小值。

有个地方需要特殊处理一下，如果原本没有坐标为 $0$ 的露水，我们需要额外加一个进去，最后答案需要减去 $m$，因为加的那滴露水没有水分。

code 
```
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=310;
int n,m,s;
int x[N];
int dp[2][N][N];
inline int solve(int tot)
{
	memset(dp,0x3f,sizeof dp);
	dp[0][s][s]=dp[1][s][s]=0;
	for (int k=2;k<=tot;++k)
	{
		for (int l=1;l+k-1<=n;++l)
		{
			int r=l+k-1;
			dp[0][l][r]=min(dp[0][l+1][r]+(tot-k+1)*(x[l+1]-x[l]),dp[1][l+1][r]+(tot-k+1)*(x[r]-x[l]));
			dp[1][l][r]=min(dp[0][l][r-1]+(tot-k+1)*(x[r]-x[l]),dp[1][l][r-1]+(tot-k+1)*(x[r]-x[r-1]));
		}
	}
	int minn=1e18;
	for (int l=1;l+tot-1<=n;++l) minn=min({minn,dp[0][l][l+tot-1],dp[1][l][l+tot-1]});
	return minn;
}
signed main()
{
	scanf("%lld%lld",&n,&m);
	bool flag=false;
	for (int i=1;i<=n;++i) 
	{
		scanf("%lld",&x[i]);
		if (x[i]==0) flag=true;
	}
	if (!flag) x[++n]=0;
	sort(x+1,x+n+1);
	for (int i=1;i<=n;++i)
	{
		if (x[i]==0)
		{
			s=i;
			break;
		}
	}
	int ans=-1;
	for (int i=1;i<=n;++i) ans=max(ans,i*m-solve(i));
	if (!flag) ans-=m;
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：eastcloud (赞：0)

[更好的阅读体验](https://www.cnblogs.com/eastcloud/p/17101408.html)

### 简要题意

在一个数轴上有 $n$ 滴露水，每滴露水初始水量为 $m$，每秒会蒸发一滴水，一个甲虫初始在原点，速度为 1，水能瞬间喝完，问它最多能喝到几滴水。

### 题目分析

对于这种移动区间连续的题目，我们首先考虑区间 dp，记 $f_{l,r,0}$ 表示喝完区间 $[l,r]$ 的水且在左边表示的最小时间，第三维为 1 的时候在右边，据此设计转移。

但是我们发现本题中多了一维时间，强行增加维度时间复杂度会爆，我们考虑控制变量。

可以发现，上述转移最大的问题在于我们不知道转移之后每个水滴的剩余水量，而剩余水量和最多的水都可以通过已蒸发的水量和总共经过的水滴数求出，转换后复杂度降低，符合我们的要求。

于是我们把储存对象改为已蒸发水量，外层枚举一个总共经过的水滴数，定义喝完当前的水后还差 $k$ 滴水没喝，$val$ 为排序后的水滴横坐标，可以得到状态转移方程：

$f_{l,r,0}=\min(f_{l+1,r,1}+k \times |val_r-val_l|,f_{l+1,r,0}+k \times |val_{l+1}-val_l|)$

$f_{l,r,1}=\min(f_{l,r-1,1}+k \times |val_r-val_{r-1}|,f_{l,r-1,0}+k \times |val_{l}-val_{r}|)$

实现时还需要注意特判只喝一个水滴时的边界情况。

### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#define ll long long
using namespace std;
ll n,m;
ll val[1000001];
ll dp[301][301][2];
ll calc(int lim){
	ll ans=0x3f3f3f3f3f3f3f3f;
	for(int len=1;len<=lim;len++){
		for(int l=1;l+len-1<=n;l++){
			int r=l+len-1;
			if(len==1)dp[l][r][0]=dp[l][r][1]=lim*abs(val[l]);
			else{
				dp[l][r][0]=dp[l][r][1]=0x3f3f3f3f3f3f3f3f;
				dp[l][r][0]=min(dp[l][r][0],dp[l+1][r][0]+(lim-len+1)*abs(val[l+1]-val[l]));
				dp[l][r][0]=min(dp[l][r][0],dp[l+1][r][1]+(lim-len+1)*abs(val[r]-val[l]));
				dp[l][r][1]=min(dp[l][r][1],dp[l][r-1][1]+(lim-len+1)*abs(val[r]-val[r-1]));
				dp[l][r][1]=min(dp[l][r][1],dp[l][r-1][0]+(lim-len+1)*abs(val[l]-val[r]));
			}
			if(len==lim) ans=min(ans,min(dp[l][r][0],dp[l][r][1]));
		}
	}
	return ans;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>val[i];
	sort(val+1,val+n+1);
	ll ans=0;
	for(int i=1;i<=n;i++)ans=max(ans,i*m-calc(i));
	cout<<ans<<endl;
}
```


---

## 作者：Starlight_Glimmer (赞：0)

[题目链接](https://www.luogu.com.cn/problem/P4870)

#### 解析



类似于费用提前计算的题目：[SDOI2008 Sue的小球](https://www.cnblogs.com/lyttt/p/14019547.html)（好像就是因为这道题才去学这个的

定义$f[0/1][i][j]$表示吃掉$[i,j]$露水并且停留在最左端/最右端的最大水分。

转移：$f[0][i][j]=min(f[0][i+1][j]+(x[i+1]-x[i])*(i+n-j),f[1][i+1][j]+(x[j]-x[i])*(i+n-j))$

$f[1][i][j]=min(f[1][i][j-1]+(x[j]-x[j-1])*(i-1+n-(j-1)),f[0][i][j-1]+(x[j]-x[i])*(i-1+n-(j-1)))$

但是这道题有个问题就是，它符合物理常识，水分蒸发了就没有了，而不会变成负数，换句话说，就是没有上道题的$Sue$要求你捞全部的彩球，人家甲虫要活命的，只要求水分最大。

如果挨个计算每个水滴是不是负数，那么复杂度无疑会很大（而且优化也搞没了好嘛

所以可以枚举一下吃掉露水的数量，每个数量取最大值。可以发现这样做的话，负数的情况一定不优，所以可以规避掉。

------

#### ►Code View

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
#define N 305
#define INF 0x3f3f3f3f
#define LL long long
int rd()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1; c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	return f*x;
}
int n,m;
int x[N];
LL f[2][N][N],ans;
int Abs(int x)
{
	if(x>=0) return x;
	return -x;
}
int main()
{
	n=rd(),m=rd();
	for(int i=1;i<=n;i++)
		x[i]=rd();
	x[++n]=0;
	sort(x+1,x+n+1);
	int st; 
	for(int i=1;i<=n;i++)
		if(x[i]==0)
		{
			st=i;
			break;
		}
	for(int p=1;p<=n;p++)
	{
		memset(f,INF,sizeof(f));
		f[0][st][st]=f[1][st][st]=0;
		for(int len=1;len<=p;len++)
			for(int i=1;i+len<=n;i++)
			{
				int j=i+len;
				f[0][i][j]=min(f[0][i+1][j]+Abs(x[i+1]-x[i])*(i+p-j),f[1][i+1][j]+Abs(x[j]-x[i])*(i+p-j));
				f[1][i][j]=min(f[1][i][j-1]+Abs(x[j-1]-x[j])*(i-1+p-(j-1)),f[0][i][j-1]+Abs(x[i]-x[j])*(i-1+p-(j-1)));
				
			}
		for(int i=1;i+p-1<=n;i++)
			ans=max(ans,1ll*m*(p-1)-min(f[0][i][i+p-1],f[1][i][i+p-1]));
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

