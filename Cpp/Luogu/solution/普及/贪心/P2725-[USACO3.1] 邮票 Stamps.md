# [USACO3.1] 邮票 Stamps

## 题目描述

给一组 $n$ 枚邮票的面值集合和一个上限 $k$ —— 表示信封上能够贴 $k$ 张邮票。请求出最大的正整数 $m$，满足 $1$ 到 $m$ 的面值都可以用不超过 $k$ 张邮票表示出来。



## 说明/提示

#### 样例输入输出 1 解释

有 $1$ 分和 $3$ 分的邮票；你最多可以贴 $5$ 张邮票。很容易贴出 $1$ 到 $5$ 分的邮资（用 $1$ 分邮票贴就行了），接下来的邮资也不难：


- $6 = 3 + 3$。
- $7 = 3 + 3 + 1$。
- $8 = 3 + 3 + 1 + 1 $。
- $9 = 3 + 3 + 3 $。
- $10 = 3 + 3 + 3 + 1 $。
- $11 = 3 + 3 + 3 + 1 + 1 $。
- $12 = 3 + 3 + 3 + 3 $。
- $13 = 3 + 3 + 3 + 3 + 1$。


然而，使用 $5$ 枚 $1$ 分或者 $3$ 分的邮票根本不可能贴出 $14$ 分的邮资。因此，答案为 $13$。

#### 数据规模与约定

对于 $100\%$ 的数据，保证 $1 \leq k \leq 200$，$1 \leq n \leq 50$，$1 \leq a_i \leq 10^4$。

#### 说明

题目翻译来自 NOCOW。

## 样例 #1

### 输入

```
5 2
1 3```

### 输出

```
13```

# 题解

## 作者：「QQ红包」 (赞：55)

完全背包，然后从头搜就可以了，

具体见代码

```cpp
/*
ID: redbag
PROG: stamps 
LANG: C++     
*/
#include<set>  
#include<map>  
#include<list>  
#include<queue>  
#include<stack>  
#include<string>  
#include<math.h>  
#include<time.h>  
#include<vector>  
#include<bitset>  
#include<memory>  
#include<utility>  
#include<stdio.h>  
#include<sstream>  
#include<iostream>  
#include<stdlib.h>  
#include<string.h>  
#include<algorithm> 
#define LL unsigned long long   
using namespace std;
int k,n,i,j,s,a;//k:总共消耗的邮票数 
int f[2000000];//f[i]表示构成面值为i至少需要的邮票数 
int main() 
{
    scanf("%d%d",&k,&n);
    for (i=1;i<=2000000;i++) f[i]=2333;//标记
    f[0]=0;//赋初值 ，用0张邮票可以构成0
    for (i=1;i<=n;i++)
    {
        scanf("%d",&a);//读入 
        for (j=a;j<=2000000;j++)
        if (f[j-a]+1<=k)//用的邮票数目在范围内 
            f[j]=min(f[j],f[j-a]+1);//取较小的 
    } 
    s=0;
    for (i=1;i<=2000000;i++)//找从1开始 连续 的能取的集合的最后一个。 
        if (f[i]==2333)//凑不出了 
        {
            s=i-1;//记录 
            break;//退出 
        }
    printf("%d\n",s);//输出 
    return 0;
}
```

---

## 作者：ysner (赞：25)

此题应该是一道较为简单的DP题，只要认真观察、找规律，推出状态转移方程，就会发现，用程序实现此题很简单。

1.数据分析：每个信封最多贴K(K<=200)张邮票，每张邮票的面值不超过10000，能贴出最大的邮资不超过2000000，可用一个数组来表示能够表示贴出每种邮资。

2.算法分析：

(1)搜索：每种邮票最多贴200张，总共50种，朴素的深搜规模将达到50^200。

(2)动态规划：

<1>阶段：能够构成每个面值为阶段。比如能构成的面值为1到V，那么总共为V个阶段。

<2>状态：dp[i]表示构成面值i所需要的最少邮票数.

<3>决策：对于样例数据1和3两种面值的邮票：

构成邮资0：所需要邮票张数为0张，dp[0]=0;

构成邮资1：只能用1分的邮票，所需要邮票张数1张，dp[1]=1;

构成邮资2：只能用1分的邮票，所需要邮票张数2张，dp[2]=1;

构成邮资3：

\*1.若选择使用一张1分的邮票，dp[3]=dp[2]+1=3………dp[3-1]+1

\*2.若选择使用一张3分的邮票，dp[3]=dp[0]+1=1………dp[3-3]+1

dp[3]=min{dp[2]+1,dp[0]+1}=1;

构成邮资4：

\*1.若选择使用一张1分的邮票，dp[4]=dp[3]+1=2………dp[3-1]+1

\*2.若选择使用一张3分的邮票，dp[4]=dp[1]+1=1………dp[3-3]+1

dp[4]=min{dp[3]+1,dp[1]+1}=2;

<4>状态转移方程：dp[i]=min{dp[i-a[j]]+1}    i>=a[j]  1<=j<=n    f[i]<=k;

样例代码：

```cpp
#include<iostream>
#include<cmath> 
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int main()
{
    int a[51]={},dp[2000001]={};;
    int i,j,k,n,m;
    while(scanf("%d%d",&k,&n)!=EOF)
    {
        for(i=0;i<n;i++)
            scanf("%d",&a[i]);
        sort(a,a+n);
        dp[0]=0;
        i=0;
        while(dp[i]<=k)
        {
            i++;
            dp[i]=999999;
            for(j=0;j<n&&a[j]<=i;j++)
              if(dp[i-a[j]]+1<dp[i])
                dp[i]=dp[i-a[j]]+1;
        }
        printf("%d\n",i-1);
    }
    return 0;
}
实质就是背包问题：当前邮资i可以看作背包容量，每种邮票可以看作是一个物品，邮票的面值就是物品的体积，k可以看作是对物品数量的一个限制。
```

---

## 作者：光明正大 (赞：17)

## 一翻题解发现dalao用的都是动规，蒟弱表示不会，所以写了一篇BFS

开一个结构体记录能组成的数和需用邮票数

不说了，上代码，详细注释见代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int m,n,ans0,ans,maxn,a[55],f[2000020];
struct stamp{int x,k;};
//x表示能组成的面额,k表示需用邮票数 
queue<stamp> q;//用的STL 
int main()
{
	cin>>m>>n;
	//找出最大的面额 
	for(int i=1;i<=n;i++) cin>>a[i],maxn=max(a[i],maxn);
	q.push((stamp){0,0});
	while(!q.empty())
	{
		stamp u=q.front();q.pop();
		//枚每一个面额 
		for(int i=1;i<=n;i++)
		{
			//不能超过邮票总数 
			if(u.k>=m) continue;
			//如果能表示就不再表示 
			if(f[u.x+a[i]]) continue;//非常重要，否则会MLE 
			u.k++;u.x+=a[i];
			//记录，入队 
			f[u.x]=1;q.push(u);
			u.k--;u.x-=a[i];
		}
	}
	//找最长连续面额
	//ans0表示当前连续面额，ans为最终答案 
	for(int i=1;i<=maxn*m;i++)
		if(!f[i]) ans=max(ans,ans0),ans0=0;
		else ans0++;
	//不要忘了再比一下 
	cout<<max(ans,ans0);
	return 0;
}
```
### 罕见的一篇BFS，望管理员通过

### 如果有问题可私信问我

### 望dalao勿喷

---

## 作者：Priori_Incantatem (赞：13)

比较水的一道完全背包，很类似硬币问题 ~~听rxz讲了贼多遍~~

设$f[i]$为用给出的硬币凑出面值为$i$的钱最少需要多少枚硬币

转移方程：$f[i]=min(f[i],f[i-a[j]]+1)$（$f[i]$初始时为$inf$）

从$1$开始求凑出每一个面值的$f$值，计数器累加，直到有一种面值凑不出来或者$f$值超过$K$

```cpp
#include<cstdio>
#include<iostream>
using namespace std;
const int Maxn=60,inf=0x3f3f3f3f,Maxm=200*10000+10;//Maxm为用所有货币可能凑出的最大值
int f[Maxm+100],a[Maxn];
int n,m,ans;//这里的m是题目中的K
int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0' && ch<='9')s=s*10+ch-'0',ch=getchar();
	return s*w;
}
int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	m=read(),n=read();
	for(int i=1;i<=n;++i)
	a[i]=read();
	for(int i=1;i<=Maxm;++i)
	{
		f[i]=inf;
		for(int j=1;j<=n;++j)
		if(i-a[j]>=0)f[i]=min(f[i],f[i-a[j]]+1);//注意要特判，不然会出错
		if(f[i]==inf || f[i]>m)break;
		ans++;
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Weierstras (赞：10)

一个经典背包题，f[i]记录面值为i时最少需要的邮票数

状态转移方程：f[i]=min(f[i],f[i-value]+1)

这里i只能取[value,value\*k]，可以大大缩短时间，看了下面dalao的题解好像没人求背包的上界233

本蒟蒻第一次写题解 写得不好见谅

```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#define min(a,b) ((a)<(b)? (a):(b))
#define maxv 2000005
#define inf 0x3f3f3f3f
using namespace std;
int n,k,ans,mx,c[55];
int vis[maxv];
int main(){
    cin>>k>>n;
    memset(vis,inf,sizeof(vis));
    vis[0]=0;
    for(int i=1;i<=n;i++) cin>>c[i];
    sort(c+1,c+n+1); //把邮票面值从小到大排序
    for(int i=1;i<=n;i++){
        mx=c[i]*k; //最大可能出现的面值
        for(int j=c[i];j<=mx;j++){
            if(vis[j-c[i]]<min(k,vis[j]-1)){
                vis[j]=vis[j-c[i]]+1; //DP
            }
        }
    }
    for(int i=1;i<maxv;i++){
        if(vis[i]!=inf) ans++;
        else break;
    }
    cout<<ans;
    return 0;
}

```

---

## 作者：Magi_karp (赞：3)

#递推？广搜？

背包例题题解里面的一股泥石流……

非常好理解的！

代码有注释

```cpp
#include<cstdio>
#include<iostream>
using namespace std;
int n,m,w,ma;
int v[60],use[2500005];//虽然你只用到2000000但是访问到2000000之外了的（当然进队时判断也行）
bool f[2500005]={1};//可恶某评测机在我写2000000时爆栈却说是tle…坑…
int main()
{
    scanf("%d%d",&m,&n);
    for (int i=1;i<=n;i++)
        scanf("%d",&v[i]);
    for (int i=1;i<=2000000;i++) use[i]=m+1;//初始化用的邮票超了方便后面取min
    int k=0;
    while (f[k]&&use[k]<=m)//如果当前合法则一定进行k++操作
    {
               //如果use[k]==m则合法但不可扩展，但这时（2）处就一定不会更新
        for (int i=1;i<=n;i++)
            if (use[k+v[i]]>use[k]+1)//(2)处（也就是初始化的时候use[i]是m+1而不是极大值的原因）
                f[k+v[i]]=1,use[k+v[i]]=use[k]+1;
        k++;
    }
    printf("%d\n",k-1);
}
老题新思路就很好玩啊不觉得嘛？
```

---

## 作者：_soul_ (赞：3)

首先看这道题目，如果没有只能贴K张邮票这个限制，那么这题就是一题很水的背包，只要将用a[i]个物品能组成的值

的全部求出来，然后一遍for求出连续最长的可以到达的数字的长度即可。附转移方程{f[j]:=f[j] or f[j-a[i]]  f为bool数组 初始化 f[0]=true}

然而这题并不是如此。

但是我们其实只需要添加一个状态即可。

因为每次取邮票都必须在k范围内，所以我们只需要维护一个达到i花费的最小邮票数就行了。如果达到j-a[i]时的邮票数已经等于了k就说明a[i]这张邮票已经不可取不然就超过了k。但是这里还有一个小细节，因为你要维护的是达到i花费的最小邮票数，是最小！！！所以如果当j这个值已经可以达到时但是并不一定达到他的邮票数是最小的，所以如果f[j-a[i]]+1的邮票数小于f[j]本身的邮票数就要将F[J]的最小邮票数更新。

具体见代码了！！！

带一次写题解各位写的不好各位见谅了，以后一定会更加努力的！！！

```cpp
uses math;
var i,j,n,k,l,m,ma,ans1,ans:longint;
a:array[0..1000] of longint;   {存物品}
f:array[0..10000000,1..2] of longint;  {f[i,1] 代表i能否到达   f[i,2]代表到达i花费的最小邮票数}
begin
  read(m,n);
  for i:=1 to n do
  begin
    read(a[i]);
    if a[i]>ma then ma:=a[i];
    f[a[i],1]:=1;
    f[a[i],2]:=1;
  end;
  f[0,1]:=1;
  for i:=1 to n do
   for j:=a[i] to ma*m do
   if f[j-a[i],2]+1<=m then
   begin
     if (f[j,1]=0)and(f[j-a[i],1]=1) then
     begin f[j,1]:=1; f[j,2]:=f[j-a[i],2]+1; end;
     if (f[j,1]=1)and(f[j-a[i],1]=1) then
     f[j,2]:=min(f[j,2],f[j-a[i],2]+1) else
   end;
  for i:=1 to ma*m do
  begin
    if f[i,1]=1 then inc(ans) else
    begin
      ans1:=max(ans1,ans);
      ans:=0;
    end;
  end;
  writeln(ans1);
end.
```

---

## 作者：Celebrate (赞：3)

这一题我想不出什么高级算法，也就打了一个暴力

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[51];
int f[2100000];//f[i]表示达到面值为i至少需要多少张邮票 
int main()
{
	int i,j;
	scanf("%d%d",&m,&n);
	for(i=1;i<=n;i++) scanf("%d",&a[i]);
	memset(f,127,sizeof(f));f[0]=0;//f初始化无限大，面值为0就不用邮票 
	for(i=1;i<=n;i++)//枚举n张邮票 
	{
		for(j=a[i];j<=2000000;j++)//因为是可以自己叠加自己的，所以就顺着来 
		{
			if(f[j-a[i]]!=2139062143 && f[j-a[i]]+1<=m)//如果上一个可以求出，并且小于等于m张邮票 
			{
				f[j]=min(f[j],f[j-a[i]]+1);//更新最优值 
			}
		}
	}
	int t=0;//从0开始找 
	while(f[t+1]!=2139062143) t++;
	printf("%d\n",t);//输出 
	return 0;
}
```

---

## 作者：LikC1606 (赞：2)

### 题意
判断从1开始的能凑出的连续的邮票价值（1~n）,会给出两个数K和N,K是可用的邮票总数。N是邮票面值的数量。接下去的N行是每种邮票的价值
#### 注意：每种邮票是可以多次使用
###  做法
完全背包模型，用一维即可，如果用二维会内存超限,记录的是凑足i的价值至少要多少邮票，如果大于K，输出i-1,跳出循换，如果没有跳出，输出最大可能性K*n(n是价值最大的邮票)，详见代码
### 代码
```cpp
/*
ID: liuzhen26
TASK: inflate
LANG: C++                 
*/
#include<bits/stdc++.h>
using namespace std;
int k,n;
int a[55];
int f[2000005];//记录至少多少邮票凑足 
int main() 
{
	//freopen("inflate.in","r",stdin);
	//freopen("inflate.out","w",stdout);
    scanf("%d%d",&k,&n);
    int maxx=0;
    for(int i=1;i<=n;++i)
       scanf("%d",&a[i]),maxx=max(maxx,a[i]);//记录邮票中的最大值 
    f[0]=0;
    int l=maxx*k;//循换次数 
    for(int i=1;i<=l;++i)
	{
		for(int j=1;j<=n;++j)
			if(i>=a[j])//边界处理 
				f[i]=min(f[i]?f[i]:200000000,f[i-a[j]]+1);//比较前提是f[i]！=0 
        if(f[i]>k)//超出K的值要跳出 
        {
        	cout<<i-1<<endl;
        	return 0;
		}
	}   
	cout<<l<<endl;//没被return所以输出 
	return 0;
}
```


---

## 作者：PauGasol (赞：2)

看到下面dalao们的代码，本蒟蒻来发一个复杂度高一些的。

（但是好像评测机跑得快所以能过)

dp[i]表示凑成i块钱**最少**需要多少张邮票

然后就这样搞：dp[i]=min(dp[i],dp[i-value[i]]);循环到2000000；

最后统计答案的时候扫一遍dp数组，找最长的dp值不超过k的一段区间，这就是答案了。

···cpp

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int k,n;
int w[51];
int ans=-1,b;
int dp[2000001];
int main()
{
    memset(dp,0x7f7f7f7f,sizeof(dp));
    scanf("%d%d",&k,&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&w[i]);
    }
    dp[0]=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=w[i];j<=2000000;j++)
        {
            dp[j]=min(dp[j],dp[j-w[i]]+1);
        }
    }
    b=0;
    for(int i=1;i<=2000000;i++)
    {
        if(dp[i]!=2139062143&&dp[i]<=k){
            b++;
        }
        else b=0;
        ans=max(ans,b);
    }
    cout<<ans;
    return 0;
}
···
```

---

## 作者：xzyxzy (赞：1)

首先，有1分的邮票，所以可以从一分开始凑

接下来，用变量i表示当前要凑到的面值，r[i]表示凑到i要用的邮票数量

为使得张数最少，则在凑i时，将i依次减去各个种类的邮票面值m[j]，得到的剩余面值a

这样凑i需要的张数r[i]，就是凑a需要的张数r[a]+1，然后依次枚举邮票面值相减取得a，取r[a]最小时，再计算r[i]，可使得r[i]最小，再重复此过程，直到r[i]=0或者r[i]大于了限定张数为止

最后输出i-1

这样即可保证凑到每个面额中所用的张数是最少的

可以看下我的代码（其实思路明确了完全可以按照自己风格写）


```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;
int n,k;//n种面值,k张邮票 
int m[51];//m存放面值
int r[2000001];//c[i]存放达到总额i需要的最少邮票张数 
int read()
{
    char ch=getchar();
    while(ch<'0'||ch>'9') ch=getchar();
    int h=0;
    while(ch<='9'&&ch>='0')
    {
        h=h*10+ch-48;
        ch=getchar();
    }
    return h;
}
int main()
{
    k=read();
    n=read();
    for(int i=1;i<=n;i++) m[i]=read(); 
    sort(m+1,m+n+1);
    r[1]=1;
    int i=1;
    while(1)
    {
        i++;//要凑到i的面值 
        int mini=201;
        for(int w=1;w<=n;w++)
        {
            if(i-m[w]>=0) mini=(r[i-m[w]]+1)<mini?(r[i-m[w]]+1):mini;
        }
        r[i]=mini;
        if(mini==0||mini>k)
        {
            cout<<i-1;
            return 0;
        }
    } 
}

```

---

## 作者：Jason_Yvan (赞：1)

首先我们定义dp[n]：表示的n价值时，所用最小的邮票数；

注意要把数组开大一点，防止RE

然后我们从 输入的邮票面值数开始不断判断，使得在n价值时用最小的邮票数

代码如下：

/*************************************************************************

    > Author: wzw-cnyali
    > Created Time: 2017/3/25 21:49:43
************************************************************************/












```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long LL;
#define REP(i, a, b) for(register int i = (a), i##_end_ = (b); i <= i##_end_; ++ i)
#define DREP(i, a, b) for(register int i = (a), i##_end_ = (b); i >= i##_end_; -- i)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define mem(a, b) memset((a), b, sizeof(a))
template<typename T> inline bool chkmin(T &a, const T &b) { return a > b ? a = b, 1 : 0; }
template<typename T> inline bool chkmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }
int read()
{
    int sum = 0, fg = 1; char c = getchar();
    while(c < '0' || c > '9') { if (c == '-') fg = -1; c = getchar(); }
    while(c >= '0' && c <= '9') { sum = sum * 10 + c - '0'; c = getchar(); }
    return sum * fg;
}
const int Size = 4000000;
const int inf = 0x3f3f3f3f;
int dp[Size];
int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);
#endif
    int M = read(), N = read();
    REP(i, 1, N)
    {
        int stamp = read();
        dp[stamp] = 1;
        REP(j, stamp + 1, 2000000)
        {
            if(dp[j - stamp] && dp[j - stamp] < M && ( !dp[j] || dp[j] > dp[j - stamp] + 1))
            dp[j] = dp[j - stamp] + 1;
        }
    }
    int ans = 0;
    REP(i, 1, 2000000)
    {
        if(dp[i]) ans = i;
        else break;
    }
    printf("%d\n", ans);
    return 0;
}

```

---

## 作者：functionendless (赞：1)

f[j][0]表示当总和为i时可不可行：1为可行，0为不可行，f[j][1]表示总和为j时最少需要多少邮票

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
short f[100000001][2];
int a[55];
long long sum=0;
int main()
{
    int i,j,k,s,n;
    scanf("%d %d",&s,&n);
    for(i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        if(a[i]>sum)
            sum=a[i];
    }
    f[0][0]=1;f[0][1]=0;
    sum*=s;
    for(i=1;i<=sum;i++)//初始化f[i][1]
        f[i][1]=9999;
    for(i=1;i<=n;i++)
        for(j=1;j<=sum;j++)
            if(f[j-a[i]][0]==1&&f[j-a[i]][1]+1<f[j][1])
            {
                f[j][0]=1;
                f[j][1]=f[j-a[i]][1]+1;
            }
    //for(i=1;i<=sum;i++)
    //    printf("%d %d\n",f[i][0],f[i][1]);
    for(i=1;i<=sum+1;i++)
        if(f[i][0]==0||f[i][1]>s)
        {
            printf("%d",i-1);
            return 0;
        }
    return 0;
}
```
/\*3 10
29 50 36 43 1 2 4 8 15 22\*/


---

## 作者：Vin_1999 (赞：1)

/\*就是简单的dp+贪心（？）。

若集到该邮资的邮票数能更少就更有可能集到下一邮资啦

dp[i]为集至该邮资的邮票数最小值，value[j]为每张邮票面值。

dp[i]=min(dp[i-value[j]],dp[i])。dp[0]=0;dp[i>0]=INT\_MAX;

其实楼下已经说清楚了呢······

重点是要把面值快排一遍，然后加个判断，不然第11个点会wa掉\*/




    
    
```cpp
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<string>
#include<cstdio>
#include<queue>
#include<stack>
#include<set>
#include<map>
#include<vector>
#include<climits>
using namespace std;
static int n,k,a[210],dp[2000003];
int main()
{
     freopen("e:/in.txt","r",stdin);
     scanf("%d%d",&k,&n);
     for(int i=1;i<=n;i++)
     {
         scanf("%d",&a[i]);    
    }
    sort(a+1,a+1+n);
    int i=0;
    memset(dp,127,sizeof(dp));
    dp[0]=0;
    do
    {
        i++;
        for(int j=1;j<=n;j++)
            if(i-a[j]<0) break;
        else dp[i]=min(dp[i-a[j]]+1,dp[i]);
    }while(dp[i]<=k&&dp[i]!=dp[2000003]);
    printf("%d",i-1);
    return 0;
}
```

---

## 作者：水库中的水库 (赞：1)

很明显是一个裸的完全背包

```cpp
/***************************************************************
	File name: P2725.cpp
	Author: ljfcnyali
	Create time: 2019年05月07日 星期二 14时39分48秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0x3f, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 2000010;

int dp[maxn], n, k, a;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &k, &n);
	mem(dp);
	dp[0] = 0;
	REP(i, 1, n)
	{
		scanf("%d", &a);
		REP(j, a, maxn - 1) 
		{
			if ( dp[j - a] + 1 <= k ) dp[j] = min(dp[j], dp[j - a] + 1);
		}
	}
	REP(i, 1, maxn - 1) if ( dp[i] > k ) { printf("%d\n", i - 1); return 0; }
    return 0;
}
```

---

## 作者：封禁用户 (赞：0)

一道经典的dp题
------------
设dp[i]表示i元最少用几张票可以抽出来
------------
dp[i+a[j]]=min(dp[i+a[j]],dp[i]+1)
------------
初始化dp[a[i]]=1;
------------
cpp代码
------------

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100],dp[2000000];//dp[i]表示表示出钱i至少需要多少张邮票;
int main() {
    int k,n;
    cin>>k>>n;
    memset(dp,0x3f3f3f3f,sizeof(dp));
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        dp[a[i]]=1;
    }
    for(int i=1;i<=2000000;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(i+a[j]<=2000000)
                dp[i+a[j]]=min(dp[i+a[j]],dp[i]+1);
        }
    }
    int t=0,maxx=0;
    for(int i=1;i<=2000000;i++)
    {
        if(dp[i]<=k)
        {
            t++;
        }
        else
        {
            maxx=max(maxx,t);
            t=0;
        }
        
    }
    cout<<maxx<< endl;
    return 0;
}
```


---

## 作者：封禁用户 (赞：0)

这题看着是一个比较典型的完全背包，然后我想出了以下状态转移方程：

（用f[]记录该面额能否组成（布尔型数组）,num[]记录组成该面额最少需要的邮票数，value[]记录每张邮票的价值,j表示面额，i表示第几张邮票）

f[j] = ( f[j-value[i]] ) or ( f[j] )  {num[j-value[i]]<k}

同时，如果f[j]=true 那么

if num[j-value[i]]+1<num[j] then num[j]=num[j-value[i]]+1

初始化时f[0]=true;num[]全部初始化为maxint

 
```cpp
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
using namespace std;
ifstream fin("stamps.in");
ofstream fout("stamps.out");
const int maxn=2100001;
int k,n;
int f[maxn];
int a[100];
void init(){
  fin >> k >> n;
  for (int i=1;i<=n;i++)
    fin >> a[i];
  f[0]=0;
}
void solve(){
  for (int w=0;;w++){
    if ((f[w] || w==0) && f[w]<=k){
      for (int i=1;i<=n;i++)
      if (f[w+a[i]])
        f[w+a[i]]=min(f[w+a[i]],f[w]+1);
      else
        f[w+a[i]]=f[w]+1;
    }
    else{
      fout << w-1 << endl;
      exit(0);
    }
  }
}
int main(){
  init();
  solve();
}

```

---

