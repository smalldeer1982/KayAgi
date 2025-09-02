# Road to Cinema

## 题目描述

Vasya is currently at a car rental service, and he wants to reach cinema. The film he has bought a ticket for starts in $ t $ minutes. There is a straight road of length $ s $ from the service to the cinema. Let's introduce a coordinate system so that the car rental service is at the point $ 0 $ , and the cinema is at the point $ s $ .

There are $ k $ gas stations along the road, and at each of them you can fill a car with any amount of fuel for free! Consider that this operation doesn't take any time, i.e. is carried out instantly.

There are $ n $ cars in the rental service, $ i $ -th of them is characterized with two integers $ c_{i} $ and $ v_{i} $ — the price of this car rent and the capacity of its fuel tank in liters. It's not allowed to fuel a car with more fuel than its tank capacity $ v_{i} $ . All cars are completely fueled at the car rental service.

Each of the cars can be driven in one of two speed modes: normal or accelerated. In the normal mode a car covers $ 1 $ kilometer in $ 2 $ minutes, and consumes $ 1 $ liter of fuel. In the accelerated mode a car covers $ 1 $ kilometer in $ 1 $ minutes, but consumes $ 2 $ liters of fuel. The driving mode can be changed at any moment and any number of times.

Your task is to choose a car with minimum price such that Vasya can reach the cinema before the show starts, i.e. not later than in $ t $ minutes. Assume that all cars are completely fueled initially.

## 说明/提示

In the first sample, Vasya can reach the cinema in time using the first or the third cars, but it would be cheaper to choose the first one. Its price is equal to $ 10 $ , and the capacity of its fuel tank is $ 8 $ . Then Vasya can drive to the first gas station in the accelerated mode in $ 3 $ minutes, spending $ 6 $ liters of fuel. After that he can full the tank and cover $ 2 $ kilometers in the normal mode in $ 4 $ minutes, spending $ 2 $ liters of fuel. Finally, he drives in the accelerated mode covering the remaining $ 3 $ kilometers in $ 3 $ minutes and spending $ 6 $ liters of fuel.

## 样例 #1

### 输入

```
3 1 8 10
10 8
5 7
11 9
3
```

### 输出

```
10
```

## 样例 #2

### 输入

```
2 2 10 18
10 4
20 6
5 3
```

### 输出

```
20
```

# 题解

## 作者：天泽龟 (赞：2)

### 一晚上就肝了一道题不写题解是不是有点亏？
其实是老师搞的二分练习题，挺有思维性的，故记之。

----

题意简单来说就是给你一堆车的油桶容量与价值的信息，问你在t时间内到达目的地的车中 价值最小那个是多少？

1. ### 假设我们已经选定了一辆车，怎么知道他满不满足条件呢？

题目中给了两种行动方法，以下简称快走与慢走。显然由于每次到达加油站可以更新容量，整段路程可以根据加油站分成若干个子路程，对于每段子路程分别求出最小的t，最后累加即为一共需要的t了。

对于每个子路程，显然可以利用贪心的思想：只要我有油我就快走，除非我走了一段路程后，我预判出要是在快走我就没油啦，我就改成慢走，直到把油全耗完（特殊情况我们以后讨论）。**那么应该怎么计算出这个路程长度呢？**

#### 我们设$x$为快走的路程，$y$为慢走路程，$V$为汽油总量，$s$为当前加油站与上一个加油站的距离，就可以得到以下的三个式子：
$$\begin{cases} 2x+y=V   \\ x+y=s  \\ x+2y=t\end{cases}$$

#### 我们解一下前两个式子，可以得出：
$$\begin{cases} x=V-s   \\ y=2*s-V  \end{cases}$$
将$x,y$代入即可求出对于这一子路程的$t$是多少了...
然后就可以毫无疑问的错了。

为啥会错？当然是$x,y$出现了**负数解**的情况啊！

### 我们进行简单的分类讨论：
- 如果$x<0$，你跑的比XG记者快还到不了，那你肯定就不可能到下一个点了，直接退了吧。。
- 如果$y<0$，说明你跑的太快，油桶没用完你就快走到了，那你此时的$t$加上$x$即可（对应花费的$x~min$）
- 除此之外均套用以上的式子算$t$

于是好像这一部分就没了？说着很复杂其实一想就出来了。。。

复杂度是$O(n)$的样子。

2. #### 我们怎么枚举车子，看他符不符合条件呢？

首先你$O(n)$一辆辆枚举肯定不行，超时。

其次的话看到最小值啥的想到二分应该是正常操作？然后你就又会发现给你的汽车价值根本就不存在单调性啥的，这二分啥啊。。

然后你就会自然的发现，这个价值是诈你的，真正决定能不能到达的是汽车的容量。所以你就直接二分容量，看最小满足条件的V是多少，搜一遍找一下满足$v[i]>V$且$min(w[i])$即可。

上我丑陋的代码，小细节都在代码里注释了：
```
#include <cstdio>
#include <algorithm>
#define MAXN 300000
using namespace std;

//1. 判断在t内最小V的油桶多少-->二分+贪心？

//2. 看满足 <V的最小C是多少。
int n,s,k,t;
int c[MAXN],v[MAXN],d[MAXN];

bool check(int v)
{
    long long sum=0;
    for (int i=1;i<=k;i++)
    {
        int dis=d[i]-d[i-1];
        long long x=v-dis,y=2*dis-v;
        if (x<0) return 0;
        if (y<0) sum+=dis;
        else sum+=x+2*y;
//		cout<<x<<" "<<y<<" "<<sum<<endl;
    }
    return (sum<=t);
}

int main()
{
    scanf("%d%d%d%d",&n,&k,&s,&t);
    for (int i=1;i<=n;i++) scanf("%d%d",&c[i],&v[i]);
    for (int i=1;i<=k;i++) scanf("%d",&d[i]); d[++k]=s; //十年OI一场空，cin超时见祖宗
    sort(d+1,d+k+1); //十年OI一场空，数组乱序见祖宗
    long long l=0,mid=0,r=3000000000,ans=3000000000,V=3000000000;
    while (l<r)   //STEP:1 
    {
        mid=(l+r)/2;
        if (check(mid)) r=V=mid;
        else l=mid+1;
    }
    for (int i=1;i<=n;i++) if (v[i]>=V) ans=min(ans,(long long)c[i]);
    //STEP:2
    if (ans==3000000000) printf("-1"); //十年OI一场空，忘记特判见祖宗
    else printf("%lld\n",ans);
}

```

---

## 作者：MspAInt (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF729C)

简单二分。

显然油箱越大越可能开到终点，因此二分油箱容量。

想想怎么 check。因为经过一个加油站就会加满油，考虑从一个加油站到下一个加油站。为了满足时间限制，贪心地优先选择加速行驶，直到油快不够时再换回慢速。这样一定不劣。

显然快速行驶得越久油越不够，所以还是二分快速行驶里程。这样计算两个加油站之间的耗时，如果超出时限了返回。一路开到底说明可行。

然后就能知道至少要多少的油箱容量，价格取最小值即可。

特别地，如果最大容量的车都开不到终点则无解。

复杂度 $\Theta(n \log^2 n)$。

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n,m,t,w[N],c[N],p[N],res,ans=1e9;
int loc(int l,int r,int d,int fl){
    if(l>=r)return l;
    int mid=l+r>>1;
    if(d+mid>fl)return loc(l,mid,d,fl);
    else return loc(mid+1,r,d,fl);
}
bool check(int lim){
    int now=0;
    for(int i=1;i<=m;i++){
        int dis=p[i]-p[i-1];
        int k=loc(0,dis+1,dis,lim)-1;
        if(k<0||dis+dis-k+now>t)return 0;
        else now+=dis+dis-k;
    }
    return 1;
}
int Search(int l,int r){
    if(l>=r)return l;
    int mid=l+r>>1;
    if(check(mid))return Search(l,mid);
    else return Search(mid+1,r);
}
signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    scanf("%d%d%d%d",&n,&m,&p[0],&t);
    for(int i=1;i<=n;i++)scanf("%d%d",&c[i],&w[i]),w[0]=max(w[0],w[i]);
    for(int i=1;i<=m;i++)scanf("%d",&p[i]);sort(p+1,p+m+1);p[++m]=p[0];p[0]=0;
    if(!check(w[0]))return puts("-1"),0;
    res=Search(1,w[0]);
    for(int i=1;i<=n;i++)if(w[i]>=res)ans=min(ans,c[i]);
    printf("%d\n",ans);
    //system("pause");
    return 0;
}
```

[record](https://www.luogu.com.cn/record/119376905)

---

## 作者：orecic (赞：1)

这里哦给出一个$\ O(k \log{k} + \sqrt{s}+n)$的算法。如果可以保证$\ g$的有序，复杂度将达到$\ O(k + \sqrt{s}+n)$。实际上用基数排序可以将复杂度也优化到$\ O(k + \sqrt{s}+n)$

首先我们设慢走路程为$\ x$，快走路程为$\ y$，邮箱容量为$\ V$，$\ s$为两加油站间路程,显然有：

$$
x=V-s
$$

$$
y=2s-V
$$

也就是说$\ V$在使$\ y > 0$的一段区间都会使时间减少。假若$\ s \in [1,1000000]$的话直接在数组上差分求二阶前缀和，然后从左往右遍历即可求出油量的最小值。

现在$\ s \in [1,1000000000]$则考虑分块。油量每增加$\ \sqrt{s}$减少的时间可以
$\ O(n + sqrt{n}) $预处理。然后遍历可以锁定在一个块里，之后块内直接搞即可。

```cpp
#include<bits/stdc++.h> 
using namespace std;
const int mm=500050;
int n,ss,tt,kk,m;
int c[1001001],v[1001001];
int g[1001001];
int xx[1001001],yy[1001001],minvv=0,initi=0;
long long sum[500500],ti[500500];
vector<int> num[500500];
inline void solve()
{
	int i=0;
	while(i<=m)
	{
		if(initi-ti[i]<=tt) break;
		initi-=ti[i];
		minvv+=mm;
		++i;
	}
	memset(xx,0,sizeof(xx));
	int j=0;
	while(j<num[i].size())
	{
		int vv=num[i][j];//cout<<vv<<endl;
		++xx[1];
		--xx[vv+1];
		++j;
	}
	int now=i;
	i=1;
	while(i<=mm)
	{
		xx[i]+=xx[i-1];
		++i;
	}
	i=1;
	while(i<=mm)
	{
		++minvv;
		if(initi-xx[i]-sum[now]<=tt) break;
		initi-=xx[i]+sum[now];
		++i;
	}
}
int main()
{
	scanf("%d%d%d%d",&n,&kk,&ss,&tt);
	int i=1;
	while(i<=n)
	{
		scanf("%d%d",&c[i],&v[i]);
		++i;
	}
	g[0]=0;
	i=1;
	while(i<=kk)
	{
		scanf("%d",&g[i]);
		++i;
	}
	g[kk+1]=ss;
	++kk;
	sort(g+1,g+kk+1);
	i=1;
	while(i<=kk)
	{
		minvv=max(minvv,g[i]-g[i-1]);
		++i;
	}
	i=1;
	while(i<=kk)
	{
		int x=minvv-(g[i]-g[i-1]),y=2*(g[i]-g[i-1])-minvv;
		if(y<=0)
		{
			initi+=g[i]-g[i-1];
		}
		else
		{
			initi+=x+2*y;
			num[y/mm].push_back(y%mm);
			ti[y/mm]+=y%mm;;
		}
		++i;
	}
	m=2000000000/mm;
	sum[m+1]=0;
	i=m;
	while(i>=0)
	{
		sum[i]=sum[i+1]+num[i+1].size();
		ti[i]+=1ll*sum[i]*mm;
		--i;
	}
	if(initi>tt) solve();
	int ans=2000000000;
	i=1;
	while(i<=n)
	{
		if(v[i]>=minvv) ans=min(ans,c[i]);
		++i;
	}
	if(ans==2000000000) ans=-1; 
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：只是路过这里 (赞：1)

我是天泽龟的同学，老师也给我布置了这道题，所以我也来水一波。

---
在开始之前，我们需要思考：我们该如何检验一定的油箱是否能符合条件。

首先，我们要有一种思想，能快则快，不然时间就来不及了。

如果能完全快速跑，我们就直接全程快速跑，~~不然你非要演示出自己充裕的时间干嘛呢，指不定就超了~~

反之，如果慢跑都跑不了的话，放弃吧，停止吧，结束吧。

对于两站之间的距离，我们可以列出如下表格（距离为$d$，油箱为$v$，设快跑距离为$x$)

|　|快速跑|慢速跑|总计|
|--|--|--|--|
|路|$x$|$dis-x$|$dis$|
|油|$2x$|$dis-x$|$value$ 或 $dis+x$|
|时|$x$|$2(dis-x)$|$2*dis-x$|

从上我们就已经知道了$x = value - dis$

显然我们只关心时间，$2 * dis - x = 2 * dis - value + dis = 3 * dis - value$

综上所述，可知一段路中

$$\left \{ \begin{array}{c}dis \ (value >= dis * 2) \\dis * 3 - value \ (dis <= value < dis * 2) \\None \ (value < dis)\end{array} \right.$$

注意开头和结尾，然后时间复杂度应为$O(n+1)$。

---
接下来二分枚举油箱的值，上界和下界可以根据车来决定。

得到最小油箱值后，在查找一边找到油箱大于它且花费最小的即可。

---
贴出源代码（C语言写的，不要介意）：

```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX(X,Y) ((X) >= (Y) ? (X) : (Y))
#define MIN(X,Y) ((X) <= (Y) ? (X) : (Y))
int ind();
#define MAXN 200010

int n, k, s, t;
struct car {
	int cost;
	int value;
} *cars;
int* stop;

int check(int value) {
	int time = 0;
	int i = 1;
	for(; i <= k + 1; ++i) {
		if(time > t) return time > t;
		int dis = stop[i] - stop[i - 1];
		if(value >= (dis << 1))
			time += dis;
		else if(value < dis)
			return 1;
		else 
			time += dis * 3 - value;
	}
	return time > t;
}

//这个comp写的有点丑
int comp(const void* a, const void* b) {
	return (*(const int*)a > *(const int*)b) - (*(const int*)a < *(const int*)b);
}

int main() {
	n = ind(); k = ind();
	s = ind(); t = ind();
	cars = (struct car*)calloc(n + 1, sizeof(struct car));
	stop = (int*)calloc(k + 3, sizeof(int));
	int l = 0, len = 0;
	int i = 1;
	while(i <= n) {
		cars[i].cost = ind();
		cars[i].value = ind();
		len = MAX(len, cars[i].value); // 确定上界
		++i;
	}
	len += 2;
	for(i = 1; i <= k; ++i)
		stop[i] = ind();
	stop[k + 1] = s; // 把末尾加进来，头已经被加了
	qsort(stop, (k + 2), sizeof(int), comp); // C语言的sort，总之升序即可
	while(len) {
		int half = len >> 1, mid = l + half;
		if(check(mid)) l = mid + 1, len -= half + 1;
		else len = half;
	}
	int ans = 0x7fffffff;
	for(i = 1; i <= n; ++i) {
		if(cars[i].value >= l)
			ans = MIN(ans, cars[i].cost);
	}
	printf("%d", (ans == 0x7fffffff) ? -1 : ans);
	free(cars);
	free(stop);
	return 0;
}

__inline int ind() {
	register int v = 0;
	register char ch;
	int sym = 0;
	while(!isdigit(ch = getchar()) && ch != '-');
	ch == '-' ? sym = 1 : (v = ch ^ 48);
	while(isdigit(ch = getchar())) v *= 10, v += ch ^ 48;
	return sym ? -v : v;
}
```

---

## 作者：Erica_N_Contina (赞：0)

## 思路

这里也许有一点困难就是本题实际上是一个二分。并且，我们不是二分最小花费，而是在 $0$ 到最大容量之间二分车的油箱容量。当我们二分出容量在r及以上的车可以 $t$ 分钟内到达终点后，就遍历所有 $v_i≥r$ 的车，取它们的 $c_i$ 最小值即可。

考虑二分后怎么 check。其实是一个贪心。我们考虑从第 $i$ 个加油站到 $i+1$ 个加油站之间的路程。我们可以使用一个很简单的贪心策略计算出怎么样才能最快到达或者判定无法到达。这里 $O(1)$ 就行（貌似看到题解里还用二分呢）。

假设从第 $i$ 个加油站到 $i+1$ 个加油站之间的路程为 $s$，那么我们为这 $s$ 路程分配 $s$ 汽油。对于多余的汽油，我们再分配一轮。那些被分配到两轮汽油的路程就是快速的路程。

---

```C++
#include<bits/stdc++.h>
#define rep(l,r,i) for(int i=l,END##i=r;i<=END##i;++i)
#define per(r,l,i) for(int i=r,END##i=l;i>=END##i;--i)
using namespace std;
#define int long long
#define pii pair<int,int>

#define lc(x) (x<<1)
#define rc(x) (x<<1|1)

#define rd read()
inline int read()
{
	int xx=0,ff=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') ff=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') xx=xx*10+(ch-'0'),ch=getchar();
	return xx*ff;
}
inline void write(int out)
{
	if(out<0) putchar('-'),out=-out;
	if(out>9) write(out/10);
	putchar(out%10+'0');
}

const int N=1e6+15;
const int INF=1e18+5;
const int MOD=998244353;

int b,x[N],ans[N];
int n,q;
int s,t,c[N],w[N],m,p[N];

bool check(int mid){
	int res=0;
	for(int i=1;i<=m;i++){
		int dis=p[i]-p[i-1];
		if(mid<dis)return 0;
		int ext=mid-dis;
		if(ext>dis)res+=dis;
		else res+=dis*2-ext;
	}
	return res<=t;
}
signed main(){
	n=rd,m=rd,s=rd,t=rd;
	for(int i=1;i<=n;i++){
		c[i]=rd,w[i]=rd;
		w[0]=max(w[0],w[i]);
	}
	for(int i=1;i<=m;i++)p[i]=rd;
	sort(p+1,p+m+1);
	p[++m]=s;

	int l=1,r=w[0]+1;
	while(l<r-1){
		int mid=l+r>>1;
		if(check(mid))r=mid;
		else l=mid;
	}
	int ans=INF;
	for(int i=1;i<=n;i++){
		if(w[i]>=r)ans=min(ans,c[i]);
	}
	if(ans==INF)ans=-1;
	cout<<ans<<endl;
}

```




---

