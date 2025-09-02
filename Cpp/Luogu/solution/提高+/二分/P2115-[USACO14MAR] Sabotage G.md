# [USACO14MAR] Sabotage G

## 题目描述

Farmer John's arch-nemesis, Farmer Paul, has decided to sabotage Farmer John's milking equipment!

The milking equipment consists of a row of N (3 <= N <= 100,000) milking machines, where the ith machine produces M\_i units of milk (1 <= M\_i <= 10,000).  Farmer Paul plans to disconnect a contiguous block of these machines -- from the ith machine up to the jth machine (2 <= i <= j <= N-1); note that Farmer Paul does not want to disconnect either the first or the last machine, since this will make his plot too easy to discover.  Farmer Paul's goal is to minimize the average milk production of the remaining machines.  Farmer Paul plans to remove at least 1 cow, even if it would be better for him to avoid sabotage entirely.

Fortunately, Farmer John has learned of Farmer Paul's evil plot, and he is wondering how bad his milk production will suffer if the plot succeeds.  Please help Farmer John figure out the minimum average milk production of the remaining machines if Farmer Paul does succeed.

农夫约翰的头号敌人保罗决定破坏农民约翰的挤奶设备。挤奶设备排成一行，共N（3<= N <=100000）台挤奶机，其中第i个台挤奶机生产M\_i单位（1 <= M\_i<=10,000）的牛奶。


保罗计划切断一段连续的挤奶机，从第i台挤奶机到第j台挤奶机（2<= i<= j<= N-1）。注意，他不希望断开第一台或最后一台挤奶机，因为这将会使他的计划太容易被发现。保罗的目标是让其余机器的平均产奶量最小。保罗计划除去至少1台挤奶机。

请计算剩余机器的最小平均产奶量。


## 说明/提示

【样例说明】

移去 7 和 8，剩下 5, 1, 2，平均值为 8/3。

【数据规模和约定】

对于 30%的数据，N <= 1,000。

对于 50%的数据，N <= 10,000。

对于 100%的数据，3 <= N <= 100,000，1 <= M\_i <= 10,000。

【时空限制】

0.2s/128M


## 样例 #1

### 输入

```
5
5
1
7
8
2```

### 输出

```
2.667```

# 题解

## 作者：XY_ATOE (赞：43)

这个题是二分。假设s[i]表示m[i]的前缀和数组。假设去掉[i,j](i<=j)这一部分机器则其余机器的平均产奶量可以表示为(s[n]-s[j]+s[i-1])/(n-j+i-1)。假设最小值为k，则有(s[n]-s[j]+s[i-1])/(n-j+i-1)>=k，显然可以二分，可得s[n]-s[j]+s[i-1]>=k\*n-k\*j+k\*(i-1)，即(s[n]-k\*n)-(s[j]-k\*j)+(s[i-1]-i+1)>=0。令c[i]=s[i]-k\*i。原式可化为c[n]-c[j]+c[i-1]>=0，即c[n]>=c[j]-c[i-1]。


所以每二分答案得到一个k，就可以得到一组c[i]。所以只要找到一组令c[j]-c[i-1]最大的i和j即可。如果最大的c[j]-c[i-1]>c[n]。然后注意一下第一个和第n个不能去（因为这个wa了好多次qaq）。这样就可以了。

最大的c[j]-c[i-1]用n^2枚举判断当然是不行的啊，所以可以处理c[i]的前缀最小值和后缀最大值，这样就可以o(n)check了。



```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<queue>
using namespace std;
int read()
{
    int f=1,p=0;
    char c=getchar();
    while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){p=p*10+c-'0';c=getchar();}
    return f*p;
}
double l,r,m;
int n,s[100100];
double hmax[100100],qmin[100100],c[100100];
bool check()
{
    for(int i=0;i<=n;i++)c[i]=s[i]-m*i;
    qmin[1]=c[1];for(int i=2;i<=n;i++)qmin[i]=min(qmin[i-1],c[i]);
    hmax[n-1]=c[n-1];for(int i=n-2;i>=1;i--)hmax[i]=max(hmax[i+1],c[i]);
    for(int i=2;i<n;i++)
        if(hmax[i]-qmin[i-1]>c[n])return 0;
    return 1;
}
int main()
{
    n=read();
    for(int i=1;i<=n;i++)s[i]=s[i-1]+read();
    l=0,r=1e4+100;
    for(int i=1;i<=60;i++)
    {
        m=(l+r)/2;
        if(check())l=m;
        else r=m;
    }
    printf("%.3lf",l);
    return 0;
}
```

---

## 作者：communist (赞：18)

还是二分答案，发现我的$check$函数不太一样，来水一发题解

列一下式子

$$\frac{sum-sum[l,r]}{n-(r-l+1)}<=ans$$

乘过去

$$sum-sum[l,r]<=ans*(n-r+l-1)$$

即

$$\sum_{i=1}^{l-1}+\sum_{i=r+1}^{n}<=ans*(n-r+l-1)$$

$$\sum{(a_i-ans)}<=0$$

所以我们在$check$函数中，可以处理出$a_i-ans$数组

然后求个前缀和，后缀和，前缀最小值，后缀最小值，对于每个位置考虑这个位置的前缀最小和这个位置之后（因为不能一个不删）的后缀最小是否非负即可

```
#include<iostream>
#include<cstdio>
using namespace std;
const int maxn=1e5+10;
const double eps=1e-6;
int n,m[maxn];
double ans,sum1[maxn],sum2[maxn],mn1[maxn],mn2[maxn],a[maxn];
bool check(double x)
{
    for(int i=0;i<=n+1;i++)
        mn1[i]=mn2[i]=1e9;
    for(int i=1;i<=n;i++)
        a[i]=m[i]-x;
    for(int i=1;i<=n;i++)
        sum1[i]=sum1[i-1]+a[i],mn1[i]=min(sum1[i],mn1[i-1]);
    for(int i=n;i;i--)
        sum2[i]=sum2[i+1]+a[i],mn2[i]=min(sum2[i],mn2[i+1]);
    for(int i=1;i<n-1;i++)
        if(mn1[i]+mn2[i+2]<=0)
            return 1;
    return 0;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&m[i]);
    double l=1,r=10000;
    while(r-l>eps)
    {
        double mid=(l+r)/2;
        if(check(mid))
            r=mid-eps,ans=mid;
        else
            l=mid+eps;
    }
    printf("%.3lf\n",ans);
    return 0;
}
```

---

## 作者：amstar (赞：16)

居然没有c++题解，来一发c++题解


/\*首先一看就是二分答案吗，怎么二分呢。


可以二分枚举平均值x，先维护一个前缀和，按题意要去掉一个区间，是平均值最小，设去掉[i,j]区间，去掉的和就是sum[j]-sum[i-1]，剩下的和就是sum[n]-(sum[j]-sum[i-1])，去括号，sum[n]-sum[j]+sum[i-1]（也就是[j,n]的和加上[1,i-1]的和）；剩下的和除以剩下的个数就是平均值，剩下的个数n-(j-i+1)。


那么 (sum[n]-sum[j]+sum[i-1])/(n-j+i-1)<=x。






```cpp
sum[n]-sum[j]+sum[i-1]<=xn-xj-x(i-1)；
(sum[n]-xn)-(sum[j]-xj)+(sum[i-1]-x(i-1))<=0； */
#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN = 100100;
int sum[MAXN]; 
int n;
bool check(double x)
{
    double minv = sum[1]-x*1; 
    for (int i=2; i<n; ++i)
    {
        if (sum[n]-x*n-(sum[i]-x*i)+minv<=0) return true ;
        minv = min(minv,sum[i]-x*i);   
    }
    return false ;
}
int main()
{
    scanf("%d",&n);
    for (int a,i=1; i<=n; ++i)
    {
        scanf("%d",&a);
        sum[i] = sum[i-1]+a;
    }
    double l = 0, r = 10000;
    while (r-l>1e-5)   
    {
        double mid = (l+r)/2.0;
        if (check(mid)) r = mid;    
        else l = mid;
    }
    printf("%.3lf",r);
    return 0;
}

```

---

## 作者：关怀他人 (赞：11)

## 二分答案 + 最大子段和
设当前二分的答案为$x$,总和为$tot$,当前这个答案可行当且仅当
$$
\frac{tot-sum[l,r]}{n - (r - l + 1)}\leq x
$$
也就是有一段连续区间满足它的平均数小于等于$x$

将上式化简一下得：
$$
tot - sum[l,r]\leq nx - (r - l + 1)x
$$
$$
sum[l,r] - (r - l + 1)x\geq tot - nx
$$
$$
\sum_{i=l}^{r}{(a[i] - x)} \geq tot - nx
$$
$b[i]=a[i]-x$的值可以在$check$函数里预处理，若要使上式成立，左边应取最大值，于是问题就变为求左边的式子的最大值，由于是一段连续的区间，很容易想到最大子段和，于是直接求出$b$数组的最大子段和然后和$tot-nx$比下大小即可。

**tips**：实数二分时为了避免精度误差，可以强行循环$50$次，这样便能保证精度了。

```cpp
/*
Problem : luogu P2115
Algorithm : binary search
Status : AC
*/
#include <bits/stdc++.h>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;

const int INF = 0x3f3f3f3f;
const int MAXN = 1e5 + 5;
const double eps = 1e-8;

int n;
double tot;
double a[MAXN];

bool check(double x){
	//printf("%.5lf\n",x);
	double Max = -INF,sum = 0;
	for(int i = 2;i < n;i++){
		if(sum - eps < 0)
			sum = 0;
		sum += a[i] - x;
		//printf("%.5lf ",sum);
		Max = max(Max,sum);
	}
	//printf("%.5lf\n",Max);
	return Max - (tot - n * x) >= eps;
}

int main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
	scanf("%d",&n);
	for(int i = 1;i <= n;i++){
		scanf("%lf",&a[i]);
		tot += a[i];
	}
	double l = 0,r = INF,ans = 0;
	for(int i  = 1;i <= 50;i++){
		double mid = (l + r) / 2.0;
		if(check(mid)){
			ans = mid;
			r = mid;
		}else
			l = mid;
	}
	printf("%.3lf",(double)round(ans * 1000) / 1000.0);
	return 0;
}

```


---

## 作者：Shallowy (赞：9)

蒟蒻的**贪心**就这样挂了...
###### 没错就7分...
后来才发现：![于是默默地删掉了sort()...](http://r.photo.store.qq.com/psb?/V10Cnxsq4Tf3Ww/C3K78Cr1IIIHv2RjFQPMd.Y6*6rejuuXeIC5W5SkL8E!/r/dGEBAAAAAAAA)

------------
于是看到求最小值，莫名在脑海里闪过**二分答案**~~还是小数...~~

这个时候我们应该试试设一下、推一下看看了~

那么我们**假设当前切断了i——j这一段的 _挤奶机_** ，再来个前缀和sum[i],

则**剩下的总量为$sum[n]-(sum[j]-sum[i-1])=sum[n]-sum[j]+sum[i-1]$,**

**总个数为$n-(j-i+1)=n-j+(i-1)$,**

**平均值为$(sum[n]-sum[j]+sum[i-1])/(n-j+(i-1))$.**

我们二分一个期望平均值x 即答案.

那么问题来了，怎么对一个确定的x进行判断呢？继续推。

很明显，如果当前的x是满足的，那么所有可能的平均值应该>=x,即

$(sum[n]-sum[j]+sum[i-1])/(n-j+(i-1))>=x$

—> $sum[n]-sum[j]+sum[i-1]>=nx-jx+(i-1)x$

—> $(sum[n]-nx)-(sun[j]-jx)+(sum[i-1]-(i-1)x)>=0$

### 然后？

清楚一点：再**设$p[i]=sum[i]-ix$**.

则$p[n]-p[j]+p[i-1]>=0$ —> $p[j]-p[i-1]<=p[n].$

对于上面说的一个“确定的x”，**p[n]是不变的**，所以**只要找到一组i , j使得p[j]-p[i-1]>p[n]，这个x就不能满足**，那我们肯定是要**让p[j]最大，p[i-1]最小，弄一个前缀最小值和后缀最大值就行。**

这样时间复杂度就能达到 **O(n log m)** 了。(实际应该要更快)

c++代码
```cpp
#include <iostream>
#include <cstdio>
#include <cctype>
#define rep(x) for(int i=1;i<=x;++i)
#define db double  //偷懒~
using namespace std;
const int mn=1e5+8,maxint=0x7fffffff; 
int rd(){char c;
    while(!isdigit(c=getchar())); int x=c^48;
    while(isdigit(c=getchar())) x=(x<<3)+(x<<1)+(c^48);
    return x;
}
int n=rd(),sum[mn]; //sum[i]为前缀和
db l,r,mid,p[mn],minn[mn]={maxint},maxx[mn]; //表示minn[0]=∞
db max(db x,db y){return x>y?x:y;}
db min(db x,db y){return x<y?x:y;} //手码似乎更好？
bool check(db x){
    rep(n) p[i]=sum[i]-x*i;
    rep(n-2) minn[i]=min(minn[i-1],p[i]);
    for(int i=n-1;i>=2;--i) maxx[i]=max(maxx[i+1],p[i]);
    for(int i=2;i<n;++i) if(maxx[i]-minn[i-1]>p[n]) return 0; //只要2——n-1
    return 1;
}
int main(){
    rep(n) sum[i]=sum[i-1]+rd();
    r=(sum[1]+sum[n]-sum[n-1])/2.0,maxx[n]=-maxint; //r:把2——n-1的都切断是一种方案；maxx[n]:坑了我半天，取max时它的值可能为负！⊙﹏⊙∥∣°
    while(r-l>1e-4) check(mid=(l+r)/2.0)?l=mid:r=mid; //实数二分还是这样写吧...注意满足条件应l=mid，往大找。(答案是原序列中某几个确定数的值，不能有多小就多小！)
    printf("%.3lf",l); //l是最近的解
    return 0;
}
```

Upd on 2018.10.15:
    
　　关于**为什么满足条件要l=mid往大找**，我再作个解释QAQ.
  
  　首先对于某个数据，最小值是固定的(~~全文比较~~),此时我们设答案为ans,由前面"$(sum[n]-sum[j]+sum[i-1])/(n-j+(i-1))>=x$"可以知道**对于ans和小于ans的数，check之后返回值都是满足的**，也就是说，如果往小找会找到0...ioi。又因为**当前check的数一定<=ans**，而我们只要ans这一个值，所以要往大找.

---

## 作者：lwhllw (赞：3)

看完题目，直观的感受是二分。

```cpp
  while right-left>0.0001 do
  begin
      mid:=(left+right)/2;
      if ok(mid) then right:=mid
      else left:=mid;
  end;
```
那么怎么判断可行就成了问题。
贪心思路一：对于大于mid的节点去除，不成线段则不可行(X)

这个思路显然是错的，但是却提供了一种想法，是否可以维护一个当前线段对答案的贡献呢？

贪心思路二：维护剩余剩余节点数，剩余和sum，计算mid\*剩余线段与sum关系判断

我们定义mid-a[i]为一个节点对答案的贡献，如果条线段对答案贡献为负，一定不会删去该条线段，那么找到对答案贡献最大的就行了，而实际上只需要在for循环内部每次取节点时判断可行性就行，也免去了求最大的过程。

当然还要注意一些细节问题，比如说一定要去掉一个节点......

```cpp
  for i:=2 to n-1 do
    begin
      if (hav) and (a[i]>mid) then
      begin
        cont:=(a[i]-mid);
        lev:=lev-a[i];
        levnum:=n-1;
        hav:=false;cl:=false;
        if(lev<=levnum*mid)then exit(true);
        continue;
      end;
      if not hav then
      begin
        inc(cont,a[i]-mid);
        dec(levnum);
        inc(lev,-a[i]);
        if(lev<=levnum*mid)then exit(true);
        if(cont<0)then
        begin
          cont:=0;
          hav:=true;
          levnum:=n;
          lev:=tot;
          continue;
        end;
      end;
    end;
    exit(false);
这样下来 我们就在时间复杂度O(nlogm)内解决了问题
```

---

## 作者：hanzhongtlx (赞：3)

显然想到的是一段子区间，预处理前缀和可以 $\mathcal O(1)$ 查询。  

这个复杂度确实不错，给我们乱搞留下了充足的时间。  

容易想到相关参量只有 $l,r$ ，所以考虑**模拟退火**。  

注意不要把初温设的太大，更不要把末温设的太小，这样都是白费时间。  

然后你发现还是过不了(，把接受概率调小一些就可以了。 

好像我 rp 不太行，跑 $0.9 \;s$ 都会错，所以改成 $0.95$ 秒就可以过了！  

```
#include"algorithm"
#include"iostream"
#include"cstdio"
#include"ctime"
#include"cmath"
using namespace std;

#define MAXN 100005
#define read(x) scanf("%d",&x)

int n,a[MAXN];
int x,y,L,R;
int l=2,r;
int s[MAXN];
double ans=1000000000000.00;
double t;

inline double check(int l,int r)
{
	return (double)(s[n]-s[r]+s[l-1])/(n-r+l-1);
}

inline void SA()
{
	double T=2*n,delta=0.994,T0=0.05;
	while(T>=T0)
	{
		L=x+((1.0*rand()/RAND_MAX*2)-1)*T;
		R=y+((1.0*rand()/RAND_MAX*2)-1)*T;
		L=min(L,r),L=max(l,L),R=max(L,R),R=min(R,r);
		double op=check(L,R);
		if(op<ans) x=L,y=R,ans=op;
		else if(rand()<=exp((ans-op)/T*100000000)*RAND_MAX) x=L,y=R;
		T*=delta;
	}
}

inline void work(){while((clock()-t)/CLOCKS_PER_SEC<0.95) SA();}

int main()
{
	t=clock();
	srand((int)time(0)),srand(19260817),srand((int)time(0));
	read(n),r=n-1;
	for(register int i=1;i<=n;i++) read(a[i]),s[i]=s[i-1]+a[i];
	work();
	printf("%.3lf\n",ans);
	return 0;
}
```

---

## 作者：wurzang (赞：2)

二分答案好题。

我们枚举一个答案 $x$，然后我们看下这个答案 $x$ 是否可以。

 
$$
\max\limits_{l \not = 1,r \not =n}\{ \frac{s_n-(s_r-s_{l-1})}{n-(r-(l-1))} \} \leq x
$$

假如这个式子成立的话，那么答案肯定是可以小于等于 $x$ 的。

然后发现这个式子是不变的，于是直接二分答案 $x$。

设 $check$ 函数 $check(x)=[\max\limits_{l \not = 1,r \not =n}\{ \frac{s_n-(s_r-s_{l-1})}{n-(r-(l-1))} \} \leq x]$，假如 $check(mid)=1$，$r=mid$，否则 $l=mid$。

那么问题来了这个 $check$ 函数如何 $\mathcal{O}(n)$ 去做。

然后开始推式子...

$$\max\limits_{l \not = 1,r \not =n}\{ \frac{s_n-(s_r-s_{l-1})}{n-(r-(l-1))} \} \leq x$$

把这个 $\max$ 丢掉，就有

$$\frac{s_n-(s_r-s_{l-1})}{n-(r-(l-1))} \leq x$$

$$s_n-(s_r-s_{l-1}) \leq x \times (n-(r-(l-1)))$$

$$s_n-x \times n \leq s_r-s_{l-1} -x \times (r-(l-1))$$

$$s_n-x \times n \leq s_r-x \times r-(s_{l-1}-x \times (l-1))$$


然后发现这样搞就相当于每个数字减去 $x$ 之后的前缀和。

于是问题就转化为每个数字减去 $x$ 之后的和是否小于等于每个数字减去 $x$ 之后的最大子段和。

最大子段和可以 $\mathcal{O}(n)$ 去做。

以下是代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const double eps=1e-4;
const int N=100000+5;
double a[N];int n;
double pre[N],nxt[N],sum[N];
bool check(double x){
	double sum=0,ans=-1e9;
	for(int i=2;i<n;++i){
		if(sum<0) sum=0;
		sum+=a[i]-x;
		ans=max(ans,sum);
	}
	sum=0;
	for(int i=1;i<=n;++i)
		sum+=a[i]-x;
	return ans<sum;
}
int main(){
	cin>>n;
	double l=0,r=1e9,ans=0;
	for(int i=1;i<=n;++i)
		cin>>a[i];
	for(int i=1;i<=50;++i){
		double mid=(l+r)/2.0;
		if(check(mid)) l=mid;
		else ans=mid,r=mid;
		//cout<<l<<" "<<r<<endl;
	}
	printf("%.3lf",ans);
	return 0;
}
```


---

## 作者：大菜鸡fks (赞：1)

这题一开始的时候并没有想到正解。脑子一片空白（虽然后面也没想到）忍不住就看了一发题解。下面进入正题。
看到平均值可以很自然的联想到二分判定性问题，对于原数列的每个值，我们都减去平均数进行判定。
那么我们考虑什么时候成立。
这里我把序列分成三部分。L，mid，R ，mid是要破坏的机器。
而L和R是完好的机器（分别位于mid的左右）
设x为二分出的平均值，n为序列长度，sum为原数列的和
L+R+mid+n*x=sum
L+R=sum-n*x-mid
我们要使答案成立，必须使L+R尽量小，sum和n*x均为常量。那么问题就转为对于sum的求解最大值。这是一个裸的最大子段问题。我们可以在o（n）时间内解决。
总复杂度o（n log n）
```cpp

#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=100005;
const double eps=1e-6;
int n,a[maxn],sum;
inline void init(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		sum+=a[i];
	}
}
const int inf=1e9;
inline bool check(double mid){
	double res=sum-mid*n,mx=-inf,s=0;
	for (int i=2;i<n;i++){
		s+=a[i]-mid; mx=max(mx,s); 
		if (s<0.0) s=0; 
	}
	return res-mx<=0;
}
inline void solve(){
	double l=0,r=10000;
	while (l+eps<r){
		double mid=(l+r)/2;
		if (check(mid)) r=mid;
			else l=mid;
	}
	printf("%.3lf\n",l);
}
int main(){
	init();
	solve(); 
	return 0;
} 
```

---

## 作者：MILLOPE (赞：0)

## 题目
[题目传送门]()
>农夫约翰的头号敌人保罗决定破坏农民约翰的挤奶设备。挤奶设备排成一行，共$N（3<= N <=100000）$台挤奶机，其中第i个台挤奶机生产$M_i$单位$（1 <= M_i<=10,000）$的牛奶。
保罗计划切断一段连续的挤奶机，从第i台挤奶机到第j台挤奶机$（2<= i<= j<= N-1）$。注意，他不希望断开第一台或最后一台挤奶机，因为这将会使他的计划太容易被发现。保罗的目标是让其余机器的平均产奶量最小。保罗计划除去至少$1$台挤奶机。
请计算剩余机器的最小平均产奶量。

## 题解
- 设$sum[\ \ ]$为前缀和数组，若去掉$[i,j]$区间内的机器，那么剩下的平均数为$$\frac{sum[n]-(sum[j]-sum[i-1])}{(n-(j-i+1))}$$
- 假设当前答案为$ans$，则$$ans \leq \frac{sum[n]-(sum[j]-sum[i-1])}{(n-(j-i+1))}$$
$$ans*(n-j+i-1) \leq sum[n]-sum[j]+sum[i-1]$$
$$sum[n]-n*ans-(sum[j]-j*ans)+sum[i - 1]-(i-1)*ans+ans\geq 0$$
- 令$p[i] =sum[i]-i*ans$，则上式可以变为
$$p[n]-p[j]+p[i-1]\geq 0$$
$$p[n]\geq p[j]-p[i-1]$$
- 显然，我们现在可以二分$i,j$来使上式取得最大值，但是我们不能$n^2$枚举$i,j$，我们可以$O(n)$预处理出$p[\ \ ]$的前缀最小值与后缀最大值，即可得到答案。

## $code$
```cpp
#include <bits/stcd++.h>
using namespace std; 
#define maxn 101000
const double eps = 1e-6; 
typedef long long LL; 

template <typename T> 
inline void read(T &s) {
	s = 0; 
	T w = 1, ch = getchar(); 
	while (!isdigit(ch)) { if (ch == '-') w = -1; ch = getchar(); }
	while (isdigit(ch)) { s = (s << 1) + (s << 3) + (ch ^ 48); ch = getchar(); }
	s *= w; 
}

int n; 
int a[maxn], sum[maxn]; 
double l, r; 
double p[maxn], mn[maxn], mx[maxn]; 

template <class T> inline T cmin(T a, T b) { return a < b ? a : b; }
template <class T> inline T cmax(T a, T b) { return a > b ? a : b; }

bool check(double mid) {
	for (int i = 0; i <= n; ++i) 
		p[i] = sum[i] - i * mid; 

	mn[1] = p[1]; 
	for (int i = 2; i <= n; ++i) 
		mn[i] = cmin(mn[i - 1], p[i]); 
	mx[n - 1] = p[n - 1]; 
	for (int i = n - 2; i >= 1; --i) 
		mx[i] = cmax(mx[i + 1], p[i]); 

	for (int i = 2; i < n; ++i) // 注意题目要求1,n不能选
		if (mx[i] - mn[i - 1] > p[n]) return false; 
	return true; 
}

int main() {
	read(n); 
	for (int i = 1; i <= n; ++i) {
		read(a[i]); 
		sum[i] = sum[i - 1] + a[i]; 
		r = cmax(r, (double)a[i]); 
	}

	l = 0;
	while (l + eps < r) {
		double mid = (l + r) / 2; 
		if (check(mid)) l = mid; 
		else r = mid; 
		// cout << check(mid) << endl; 
		// printf("%.2lf %.2lf\n", l, r); 
		// cout << "111111" << endl; 
	}
	printf("%.3lf", l); 
	return 0; 
}


```

---

