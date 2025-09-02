# [USACO08NOV] Mixed Up Cows G

## 题目描述

Each of Farmer John's N (4 <= N <= 16) cows has a unique serial number S\_i (1 <= S\_i <= 25,000). The cows are so proud of it that each one now wears her number in a gangsta manner engraved in large letters on a gold plate hung around her ample bovine neck.

Gangsta cows are rebellious and line up to be milked in an order called 'Mixed Up'. A cow order is 'Mixed Up' if the sequence of serial numbers formed by their milking line is such that the serial numbers of every pair of consecutive cows in line differs by more than K (1 <= K <= 3400). For example, if N = 6 and K = 1 then 1, 3, 5, 2, 6, 4 is a 'Mixed Up' lineup but 1, 3, 6, 5, 2, 4 is not (since the consecutive numbers 5 and 6 differ by 1).

How many different ways can N cows be Mixed Up?

For your first 10 submissions, you will be provided with the results of running your program on a part of the actual test data.

POINTS: 200

约翰家有N头奶牛，第i头奶牛的编号是Si，每头奶牛的编号都是唯一的。这些奶牛最近 在闹脾气，为表达不满的情绪，她们在挤奶的时候一定要排成混乱的队伍。在一只混乱的队 伍中，相邻奶牛的编号之差均超过K。比如当K = 1时，1, 3, 5, 2, 6, 4就是一支混乱的队伍， 而1, 3, 6, 5, 2, 4不是，因为6和5只差1。请数一数，有多少种队形是混乱的呢？


## 说明/提示

The 2 possible Mixed Up arrangements are:

3 1 4 2

2 4 1 3


## 样例 #1

### 输入

```
4 1 
3 
4 
2 
1 
```

### 输出

```
2 
```

# 题解

## 作者：asuldb (赞：49)

首先我们能够一眼看到4 <= N <= 16，那么就是它了，我们要压缩的状态就是它了

那么之后能我们用这个状态表示什么呢，我们要表示的显然是每只奶牛是否在队伍中
比如说10吧，转成二进制后就是1010，这就代表了第一只和第三只奶牛已经在队伍中，而第二只和第四只还没有在队伍中

那么就有一些状态可以初始化了，对于那些只有一只奶牛在队伍中，即某个状态转为二进制后只有一个1的状态我们就可以初始化为1

但是我们要判断的是这个队伍是否“混乱”，混乱的定义是：相邻奶牛的编号之差均超过K，于是我们在由一个状态得到一个新状态时一定要去判断这个原状态加上那个我们新添加到队伍末尾的那只奶牛后是否还是混乱的
那么我们要怎么做呢
显然我们的dp数组里存的不止是状态了，还应该存一个能帮助我们判断的东西
那就想想我们一旦新在队伍末尾加入一个奶牛后是怎么判断的呢

很显然只要新加入的这只奶牛和原本队尾那只奶牛的编号差大于k就可以使队伍继续混乱下去了，因为我们必须保证那个原来的状态是合法的，也就是说原来的那个队伍是混乱的

于是我们的dp数组就呼之欲出了

我们设 f[i][j]表示以第i只奶牛为结尾的状态为j的队伍混乱的方案数是多少

而我们怎么转移状态呢，我们知道对于每一个状态都有很多结尾，于是我们用两个循环，一个枚举状态，一个枚举结尾的奶牛

当然我们还需要判断这个情况是否存在，比如说f[2][10]吧，它表示10这个状态也就是1010，以第二只奶牛为结尾的方案数，这种情况显然是不存在的，因为在1010这个状态中第二只奶牛根本没有被选择，根本不可能成为结尾，所以对于这种情况我们需要进行判断

在最后我们统计答案的时候要把枚举各种奶牛作为结尾且所有奶牛均被选择的情况

于是就很简单了

之后就是代码了
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#define re register
#define int long long
#define maxn 17
using namespace std;
int k;
int n,a[maxn],f[maxn][1<<maxn];
inline int read()
{
	char c=getchar();
	int x=0;
	while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9')
	  x=(x<<3)+(x<<1)+c-48,c=getchar();
	return x;
}
signed main()
{
	n=read();
	k=read();
	for(re int i=1;i<=n;i++)
		a[i]=read();
	for(re int i=1;i<=n;i++)
		f[i][1<<(n-i)]=1;
	for(re int i=1;i<(1<<n);i++)//枚举状态 
	for(re int j=1;j<=n;j++)//枚举结尾奶牛 
	{
		if(f[j][i]) continue;
		if(!(i&(1<<(n-j)))) continue;
		//判断这种情况是否存在 
		int m=i^(1<<(n-j));
		//得到一个没有选择当前结尾奶牛j的状态 
		for(re int g=1;g<=n;g++)
		//枚举这个状态m的结尾 
		{
			if(g==j) continue;
			if(a[j]-a[g]>k||a[g]-a[j]>k) f[j][i]+=f[g][m];
			//符合混乱的条件，进行转移 
		}
	}
	int ans=0;
	for(re int i=1;i<=n;i++)
	ans+=f[i][(1<<n)-1];
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：pzc2004 (赞：22)

[题目传送门](https://www.luogu.org/problem/P2915)

这题用状压DP做，用$f_{i,j}$表示当前最后一头牛为i，当前状态为j时队列时混乱的的方案数。因为只有一头奶牛时的方案数为一，所以要将所有$f_{i,2^{i-1}}$都初始化为1.然后就是状态转移方程了。

对于当前的状态j，我们枚举末尾可能的奶牛i，如果j当中不包含i就continue,如果包含就枚举下一个可能放的奶牛k，如果j当中不包含k就判断一下$abs(a_i-a_j)$是否超过题目给定的K，如果超过就将$f_{k,j+2^{k-1}}$加上$f_{i,j}$。

最后只需要输出$\sum\limits_{i=1}^nf_{i,2^n-1}$即可。

细节：要开long long！！！要开long long！！！要开long long！！！（别问我是怎么知道的）

代码：
```
#include<bits/stdc++.h>
using namespace std;
long long n,sb,a[17],f[17][65536],ans;//为了图方便我把所有int都改成long long了
int main()
{
	scanf("%lld%lld",&n,&sb);
	for(long long i=1;i<=n;i++)scanf("%lld",&a[i]);
	for(long long i=1;i<=n;i++)f[i][1<<(i-1)]=1;//初始化
	for(long long j=1;j<=(1<<n)-1;j++)//枚举每个状态
	{
		for(long long i=1;i<=n;i++)//枚举末尾可能的奶牛
		{
			if(!(j&(1<<i-1)))continue;//如果i没在j中出现就continue
			for(long long k=1;k<=n;k++)//枚举接下来要放的奶牛
			{
				if(j&(1<<(k-1)))continue;//如果k在j中出现了就continue
				if(abs(a[k]-a[i])>sb)f[k][(1<<(k-1))|j]+=f[i][j];//状态转移
			}
		}
	}
	for(long long i=1;i<=n;i++)ans+=f[i][(1<<n)-1];//统计答案
	printf("%lld",ans);//输出
}
```
![](https://www.luogu.org/images/congratulation.png)

---

## 作者：chenzijie (赞：20)

N (4 <= N <= 16),定义状态值state（范围：0-216-1），表示当前含哪几头牛，如表：


牛    16    15    14    13    12    11    10    9    8    7    6    5    4    3    2    1

位序    15    14    13    12    11    10    9    8    7    6    5    4    3    2    1    0

取值    0/1    0/1    0/1    0/1    0/1    0/1    0/1    0/1    0/1    0/1    0/1    0/1    0/1    0/1    0/1    0/1

含义    第i位取值为1/0,表示含/不含第(i+1)头牛

举例    49=0000 0000 0001 1001，表示含第1、4、5头牛


N头牛的身上的编号 s[1],s[2],…,s[N]


dp[last][state]表示最后一头牛为last，当前含牛的状态为state，共有多少组符合条件的队伍。

dp[2][2],2=00…0010(二进制仅表示第2头牛的第1位为1) 该状态表示仅含第2头牛，

所以：dp[2][2]表示最后一头牛是2，仅含第2头牛，混乱队伍数量

dp[2][5],5=00…001001(二进制仅表示含第1、4头牛)，这种情况不存在，dp[2][5]=0


初始情况，仅含1头牛，那么这头牛就是结尾

假设共含8头牛，下标列出各种初始情况

哪头牛

（last）    状态值

(二进制)    状态值

(十进制)    表示方法    参数含义    dp(last,state)

1    0000 0001    1    20   1<<0     若仅含第last头牛，则其状态state为1左移last-1位，或2的last-1次方    1

表示在仅有1头牛的情况下，属混乱状态。

```cpp
2    0000 0010    2    21   1<<0           
3    0000 0100    4    22   1<<0        
4    0000 1000    8    23   1<<0        
5    0001 1000    16    24   1<<0        
6    0010 0000    32    25   1<<0        
7    0100 0000    64    26   1<<0        
8    1000 0000    128    27   1<<0        
```
故，初始化程序：
```cpp
for(last = 1; last <= n; last++)
{
state=1<<(last-1);// 仅含第last头牛，则其状态state为1左移last-1位
f[last][state] = 1;//有效状态进行初始化
}
```
然后按状态、依次加入每头牛，进行迭代
for(state=1;state<=2n-1;state++)  //或等价写法 for(state=1;state<=1<<n-1;state++)



```cpp
  //对每一种状态进行处理
  //状态初值二进制00…01，十进制1:前n-1位为0，最后1位为1，仅含第1头牛
//状态最大值11…11，十进制2n-1，1<<n-1: n位均为1，表示含全部第1-n头牛
 {
      for(last=1;last<=n;last++) //依次对每种状态下、队伍尾牛为last的情况进行处理 
        { //首先要判断第last头牛是否已经在state状态中
//如果不在，则dp[last][state]为不可能,无需处理
           //这里要用到&二进制按位与运算
           if(state & 1<<(last-1)==0)continue;// state & 1<<(last-1)=0表示last不在state状态
           //若牛last在state中，为合法情况，需进一步进行处理
//即依次加入1头不在state中的牛，进行处理
            for(newcow=1;newcow<=n;newcow++)
              //从第1头到第n头依次处理
{ if(state & 1<<(newcow-1)==1)continue;// state & 1<<(newcow-1)=1表示
// newcow在state状态
//不能重复加入该点，不处理
              //再判断加入newcow到队伍尾部后，队伍是否混乱
              if(abs(s[last]-s[newcow])<k) )continue;  //不混乱，也不需要处理
             //若依然混乱，则需进行数据更新
             //此时需更新的是以newcow为队尾，加上newcow以后状态的dp值
             newstate=state | (1<<(newcow-1));//或newstate=state + (1<<(newcow-1))
             dp[newcow][nowstate]+=dp[last][state];
}
           }
   }
state=2n-1;//等价于：state<=1<<n-1 ，最后的有效状态是包含所有牛
ans=0;//统计符合要求的方案数，初值为0
for(last = 1; last <= n; last++)
   ans+=dp[last][state];//包含所有牛的状态下，队尾为1、2、3…、n
                    //累加即为所求结果
    #include <cstdio>
    #include <cstdlib>
    using namespace std;
    int a[17],n,k1;
    long long dp[16][1<<16],ans=0;
    int main()
    {
        scanf("%d%d",&n,&k1);
        for(int i=0;i<n;i++)
            scanf("%d",&a[i]);
        for(int i=0;i<n;i++)
            dp[i][1<<i]=1;
        for(int i=0;i<(1<<n);i++)
            for(int j=0;j<n;j++)
                if(i&(1<<j))
                    for (int k=0;k<n;k++)
                        if(!(i&(1<<k))&&abs(a[j]-a[k])>k1)
                            dp[k][i|(1<<k)]=dp[k][i|(1<<k)]+dp[j][i];
        for(int i=0;i<n;i++)
            ans=ans+dp[i][(1<<n)-1];
        printf("%lld",ans);
        return 0;
    }

```

---

## 作者：Swing__逗比的我 (赞：13)

就是要和别人不同，更新一篇记忆化搜索的题解。

~~个人认为记忆化搜索通俗易懂，便于理解~~

正文开始

这个题是当时考试的题看了看数据范围，觉得可以打爆搜

~~然后莫名其妙水了70分~~

当时的代码，应该都比较通俗易懂，就不解释了。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<queue>
#include<map>
#include<algorithm>
#include<cmath>
#include<vector>
#define ll long long
using namespace std;
ll read()
{
    char ch; ll x=0,f=1;
    while(!isdigit(ch=getchar()))(ch=='-')&&(f=-f);
    while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
    return x*f;
}
ll a[20],n,k,ans;

bool vis[20];
int  dis[20];

void dfs(int x,int y)//第几个点，放的第几棵树
{
    if(x == n) 
    {
        ans ++;
        return ;
    }
    for(int i = 1;i <= n;i ++)
    {
        if(!vis[i] and abs(a[i] - a[y]) > k)
        {
            vis[i] = 1;//放了树就打标记，标记的是树
            dfs(x + 1,i);
            vis[i] = 0;//回溯
        }
    }
    return ;
}
int main()
{
    n = read(),k = read();
    for(int i = 1;i <= n;i ++)
        a[i] = read();
    for(int i = 1;i <= n;i ++)//每一个起点都遍历一遍
    {
        
        vis[i] = 1;
        dfs(1,i);
        memset(vis,0,sizeof vis);//每搜完一个起点开始的每一种情况就回溯至初始
    }
    cout<<ans;
    return 0;
}

```

显然70分不是我们追求的目标

这个题可以用记忆化搜索来做

~~注释都写在代码里，不多BB上代码~~

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,k,dp[17][1<<17],a[17];//DP为记录数组//VIS为判断数组 
bool vis[17][1<<17];
ll dfs(ll step,ll last,ll used)
{
    if(step>=n)
        return 1;
    if(vis[last][used])
        return dp[last][used];//如果被更新过了直接输出值，省下很多操作，这就是记忆化搜索的好处 
    ll ans=0;
    for(int i = 1;i<=n;++i)
    {
        int mask=1<<i; //拆成当前状态 
        if(!(used & mask)) //两种状态不一样 如果一样的话 & 就为 0 
        {
            if(step==0||abs(a[last]-a[i])>k)// 第一步，或者绝对值大于0，可以随便放，这个不用多说了吧 
                ans+=dfs(step+1,i,used ^ mask);//异或是为了求一个完全不一样的状态，相同的地方不变，不同的地方取反 
        }
    } 
    dp[last][used]=ans;//记录ans 
    vis[last][used]=1;//标记为1，不是说不能搜这个地方，而是这个地方已经有值了，可以直接调用 
    return ans;
}
int main()
{
    cin>>n>>k;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    cout<<dfs(0,0,0);
}
```

这一代码借鉴一位巨佬的代码，在此鸣谢@||huayucaiji

题解结束

10K多的题解量，你看我这么认真给个赞呗，qaq

---

## 作者：览遍千秋 (赞：12)

## 状压DP

观察奶牛的数据范围：$4≤N≤16$。

很明显，这是一道状压DP。

所以如果你不会位运算的话，可以右转出门了。

---

## 状态压缩

使用一个正整数$t$来描述奶牛的选取情况，当$t$的第$r$位为$1$时，代表选取了该奶牛，反之亦然。

---

## 对整数$t$的操作

假设我们要判断第$r$头奶牛是否被选取，则当``t&(1<<(r-1))``为``True``时，表示选取了，反之亦然。

---

## 状态的表示

设$opt_{a,b}$代表在题目条件下，当前选取的奶牛序列的整数$t=a$时，且最后选取的奶牛为$b$时的方案总数。

---

## 边界

$opt_{1<<(e-1),e}=1$

$1≤e≤N$

---

## 状态转移

枚举奶牛序列$t=i$，$1≤i≤(1<<n)-1$

枚举当前序列的最后一只奶牛$j$

**当满足``i&(1<<(j-1))``为``True``时**

枚举奶牛$q$，当满足$i|(1<<(q-1))≠i$且$|S_j-S_q|>k$时，$$opt_{q,(i|(1<<(q-1)))}=opt_{q,(i|(1<<(q-1)))}+opt_{j,i}$$

---

代码：
```cpp
#include<iostream>
#include<cstdio>

using namespace std;
#define maxn 16
long long int n,K,opt[maxn+1][(1<<maxn)],s[maxn+1],ok,ans;
long long int cows[maxn+1];
void read(long long int &x)
{
	x=0;
	int fh;
	char ch='a';
	while(ch!='-'&&(ch<'0'||ch>'9')) ch=getchar();
	if(ch=='-'){
		fh=1;
		ch=getchar();
	}
	else fh=1;
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	x*=fh;
}
int abs(int a)
{
	return a>0?-a:a;
}
int mian()
{
	read(n);
	read(K);
	for(register int i=1;i<=n;i++)
	{
		read(s[i]);
		cows[i]=(1<<i-1);
		opt[i][cows[i]]=1;
	}
	ok=(1<<n)-1;
	for(register int i=1;i<=ok;i++)
	{
		for(register int j=1;j<=n;j++)
		{
			if(i&cows[j])
			{
				for(register int k=1;k<=n;k++)
				{
					if((i|cows[k])!=i&&abs(s[j]-s[k])>K)
						opt[k][(i|cows[k])]+=opt[j][i];
				}
			}
		}
	}
	for(register int i=1;i<=n;i++)
		ans+=opt[i][ok];
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：wjyyy (赞：8)

[欢迎在博客食用](http://www.wjyyy.top/691.html)

## 解法：

   首先我们看到数据范围N≤16，就可以想到状态压缩，接着看就会看到方案数的选择，那么就可以尝试DP。



   首先我想的是，用三维数组$f[i][j][k]$表示当前已经选了i头牛，上一个选的是j，当前状态压缩为k。我们主要关注的是第二维，因为方案合不合法就看与自己前面的**那一个**的编号差距。因此有了方案：枚举当前要放的牛m，再枚举之前放过的牛c，这样枚举1到65535，找出有c且没有m的状态。为了避免**冲突**，我们还要在最外面枚举当前选了多少头牛。



   因此这个时间复杂度是$O(N^3\times 2^n)$的，乘出来有2亿~~我为什么要乘出来~~。



   所以这种做法是不可行的，不过bzoj时限比较宽，可以过，luogu开O2再加玄学剪枝就可以![](http://www.wjyyy.top/wp-content/uploads/2018/07/201807021718.png)了，emmm。。。代码贴在最后。



## 正解：

   学过集合/了解二进制的同学应该知道，我们如果用二进制枚举子集，在合法条件下，后枚举的一定包含某些先枚举的，例如**111011**会在**110011**后枚举到。因为数值越来越大，1也会趋向越多。那么我们就可以使大体趋势跟随1~65535枚举来更新我们的DP状态。首先我们定义DP数组$f[i][j]$，表示当前最后一头牛是i时状态压缩为j的方案数。那么我们在二进制枚举下，枚举数对**(j,k)**，找到合法数对，使得在当前二进制状态下，j被放进去过，且为最后一头，同时k没有被放进去过，找到后更新状态。因为1存的是已经放过的奶牛，所以在奶牛增加的情况下，通过刷表法更新之后状态下的奶牛，就不会出现紊乱/冲突了。
   
## Code：100pts
```cpp
#include<cstdio>
#include<cstring>
int abs(int x)
{
    return x>0?x:-x;
}
long long f[18][66666];//当前放到i号牛时压位为j
int num[18];

int main()
{
    memset(f,0,sizeof(f));
    int n,K;
    scanf("%d%d",&n,&K);
    for(int i=1;i<=n;i++)
        scanf("%d",&num[i]);
    for(int i=1;i<=n;i++)
        f[i][1<<(i-1)]=1;
    //正在枚举的状态一定包含已经枚举过的状态
    for(int i=1;i<(1<<n);i++)
        for(int j=1;j<=n;j++)//j是来自
            for(int k=1;k<=n;k++)//k是当前
                if(abs(num[j]-num[k])>K&&((1<<(j-1))&i)&&(((1<<(k-1))&i)==0))
                    f[k][((1<<(k-1))|i)]+=f[j][i];//刷表
    long long sum=0;
    for(int i=1;i<=n;i++)//统计答案
        sum+=f[i][(1<<n)-1];
    printf("%lld\n",sum);
    return 0;
}
```

## Code：80~100pts（O2）  4维枚举
```cpp
#include<cstdio>
#include<cstring>
int abs(int x)
{
    return x>0?x:-x;
}
long long f[2][18][66666];//当前放到i号牛时压位为j
int num[18];
int lowbit(int x)
{
    return x&(-x);
}
int cnt(int x)//二进制数里有多少个1
{
    int sum=0;
    while(x)
    {
        sum++;
        x-=lowbit(x);
    }
    return sum;
}

int main()
{
    memset(f,0,sizeof(f));
    int n,k,tmp;
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)
        scanf("%d",&num[i]);
    for(int i=1;i<=n;i++)
        f[1][i][1<<(i-1)]=1;
    for(int i=2;i<=n;i++)//放第i头牛
        //可行状态
        for(int j=1;j<=n;j++)
            for(int t=1;t<=n;t++)
            {
                if(abs(num[j]-num[t])>k)
                {
                    if(t==1)//这是什么玄学剪枝
                        tmp=2;
                    else
                        tmp=1;
                    for(int k=1;k<1<<n;k+=tmp)
                        if(cnt(k)==i-1)
                        {
                            if(!((1<<(j-1))&k)&&((1<<(t-1))&k))//j没有被用过且t被用过
                                f[i&1][j][k|(1<<(j-1))]+=f[i&1^1][t][k];
                        }
                }
            }
    long long sum=0;
    for(int i=1;i<=n;i++)//统计方案
        sum+=f[n&1][i][(1<<n)-1];
    printf("%lld\n",sum);
    return 0;
}
```

---

## 作者：Sweetness (赞：3)

### Luogu P2915 [USACO08NOV]奶牛混合起来

题外话：

~~是非常颓废的博主~~

~~写题解也不在于能不能通过啦，主要是缓解颓废~~

首先看到这个题，肯定是可以暴力搜索的：

不得不说这道题还是很善良的，一波大暴力dfs，居然有70pts：

```cpp
#include<bits/stdc++.h>

using namespace std;

inline int read() {
	int ans=0;
	char last=' ',ch=getchar();
	while(ch>'9'||ch<'0') last=ch,ch=getchar();
	while(ch>='0'&&ch<='9') ans=(ans<<1)+(ans<<3)+ch-'0',ch=getchar();
	if(last=='-') ans=-ans;
	return ans;
}

int n,k;
int s[20];
long long ans;
bool vis[20];
void dfs(int cnt,int nxt) {
	if(cnt==n) {
		ans++;
		return;
	}
	for(int i=1;i<=n;i++) {
		if(vis[i]) continue;
		if(abs(s[i]-nxt)>k) {
			vis[i]=1;
			dfs(cnt+1,s[i]);
			vis[i]=0;
		}
	}
	
}

int main() {
	n=read();
	k=read();
	for(int i=1;i<=n;i++) 
		s[i]=read();
	dfs(0,-k-1);
	printf("%lld",ans);
	return 0;
}
```

  
  

想改记忆化，然后~~我发现我不会~~

~~滚~~回来重新考虑dp：

将奶牛状压到一个二进制数中，第i位表示这头奶牛是否在队伍中；~~（突兀~~

我们设$dp[i][j]$表示当前状态为i，最后一个加入队伍的奶牛是j的方案数；

考虑如何转移：

设现在的状态为 $dp[i][j]$

考虑枚举下一个加入队伍的奶牛g是哪一只，那么首先肯定要满足的，就是这只奶牛不能已经加入队伍了 ~~（奶牛：我有分身术~~ 也就是i&(1<<(g-1))==0

1.如果已经在队伍里，显然要continue；~~（废话~~

2.如果不在队伍里，那么判断第g头奶牛和第j头奶牛之间的编号之差是否>k,同样的不是就continue掉 ~~（同样的废话~~

如果上面两个条件都满足，那么就可以将g加入队伍，对应的状态$dp[i|(1<<(g-1))][g]+=dp[i][j];$

考虑初始化：

对于只有一头奶牛的情况，显然只有一种方案，因此$dp[1<<(i-1)][i]=1;$

#### 然后因为上面讲的~~非常非常之乱~~，咱们来理一理思路：

首先显然是初始化，将只有一头奶牛的方案的值初始化为1

- 接下来枚举每一种状态

- 第二维枚举当前状态下，最后一个加入队伍的奶牛j是哪一只（可以直接从1~n枚举，用i&(1<<(j-1))!=0来判断合法与否

- 然后枚举下一头加入队伍的奶牛是哪一头，判断是否符合上面的两个条件，相应的进行修改

最后显然是输出答案啦:显然最后的答案应该是所有奶牛都加入了队伍，每一头奶牛最后进入队伍的方案数相加，也就是$\sum\limits_{i=1}^n dp[(1<<n)-1][i]$

然后，大概应该可能就可以愉快的AC了？~~（是码风清奇的奇女子，将就着看吧~~

```cpp
#include<bits/stdc++.h>

using namespace std;

inline int read() {
	int ans=0;
	char last=' ',ch=getchar();
	while(ch>'9'||ch<'0') last=ch,ch=getchar();
	while(ch>='0'&&ch<='9') ans=(ans<<1)+(ans<<3)+ch-'0',ch=getchar();
	if(last=='-') ans=-ans;
	return ans;
}

int n,k;
int s[20];
long long ans;
long long dp[70000][18];

int main() {
	n=read();
	k=read();
	for(int i=1;i<=n;i++) 
		s[i]=read();
	for(int i=1;i<=n;i++)
        dp[1<<(i-1)][i]=1;
	for(int a=1;a<(1<<n);a++) {
		for(int j=1;j<=n;j++) {
			if(!(a&(1<<(j-1)))) 
                continue;
			for(int g=1;g<=n;g++) {
				if((a&(1<<(g-1)))) 
                    continue;
				if(abs(s[j]-s[g])<=k) 
                    continue;
				dp[a|(1<<(g-1))][g]+=dp[a][j]; 
			}
		}
	}
	for(int i=1;i<=n;i++) 
        ans+=dp[(1<<n)-1][i];
	printf("%lld\n",ans);
	return 0;
}
```

~~//一堆括号看的我眼疼~~



---

## 作者：功在不舍 (赞：2)

1.一上来看见4<=N<=16估计是个搜索或者装压DP，发现搜索N!过不了，考虑装压DP。

2.装压DP考虑如何定义状态。设S为已经选中的点的集合，其中选中的为1，没选的为0。
(1).直接令DP[s]表示选中S集合的方案数，发现没法进行转移，因为从~S中选取一个没有用过的点放在最后面时，发现它的转移和已经选中序列的最后一位有关系，没法转移。(2).由于要求一个序列中至少有两个相邻位置差大于K，所以我们加上一维，令DP[s][i]表示选中S集合，且最后一位为i的方案数。

3.状态转移：三重循环，i枚举所有状态，j枚举i状态是以谁结尾，k枚举新加入的点,则有转移条件abs(s[j]-s[k])>K(K在我的程序里是t)
DP[i|(1<<k)][k]+=DP[i][j];

4.预处理和输出：开始把所有DP[1<<i][i]=1;
最后的答案就是DP[(1<<n)-1][i]求和；
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
long long ans,n,t,s[100],dp[1<<16][16];
int main()
{
	cin>>n>>t;
	for(int i=0;i<=n-1;i++)cin>>s[i];
	for(int i=0;i<=n-1;i++)dp[1<<i][i]=1;
	for(int i=1;i<=(1<<n)-1;i++)
	{
		for(int j=0;j<=n-1;j++)
		{
		    if((1<<j)&i)//j得在i状态中出现
		    {
		    	for(int k=0;k<=n-1;k++)
		    	{
		    		if((1<<k)&i)continue;//k不能在i状态中出现
		    		if(abs(s[j]-s[k])>t)
		    		   dp[i|(1<<k)][k]+=dp[i][j];
		    	}
		    }
		}
	}
	for(int i=0;i<=n-1;i++)ans=ans+dp[(1<<n)-1][i]; 
	cout<<ans<<endl; 
	return 0;
}
 
```

---

## 作者：Yuyuanqi (赞：1)

# 题解 P2915 [USACO08NOV]奶牛混合起来Mixed Up Cows

[题目链接](https://www.luogu.org/problem/P2915)

~~数据规模16-20的都是状压~~

如果要每一位都压序号的话空间肯定是不够的，所以每一位只能是0或1。1表示有这头牛，0表示没有这头牛。显然每个位置的选择和他两边的牛有关，所以我们就可以定义这样的状态：

f[i][j]表示使用集合i的牛，其中最后一头牛的序号为j时的总方案数。答案从f[(1 << n) - 1][n]累加即可。

转移也比较好想，从i中枚举选出倒数第二头牛，作为子状态的最后一头牛，注意边界情况。

下面看代码吧，也不是很难：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define N 17
using namespace std;
inline int read()
{
	int x = 0, f = 1;
	char c = getchar();
	while (c < '0' || c > '9') { if (c == '-') f = -1; c = getchar(); }
	while (c >= '0' && c <= '9') { x = x * 10 + c - '0'; c = getchar(); }
	return x * f;
}
int abs(int x) { return x > 0 ? x : -x; }
ll f[(1 << 16) + 5][18], ans;
int n, k, a[N], cnt[(1 << 16) + 5];
void init()
{
	for (int i = 1; i <= (1 << n); i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i & (1 << j)) cnt[i]++;
		}
	}
}//初始化每种集合的奶牛头数
int main()
{
	n = read(), k = read();
	for (int i = 1; i <= n; i++)
		a[i] = read();
	init();
	for (int i = 1; i < (1 << n); i++)
		for (int j = 1; j <= n; j++) //枚举这个集合的最后一头牛
			if (i & (1 << (j - 1)))
			{
				if (cnt[i] == 1) f[i][j] = 1; //边界情况
				else
					for (int p = 1; p <= n; p++) //枚举倒数第二头牛
						if (p != j && (i & (1 << (p - 1))) && abs(a[p] - a[j]) > k)
							f[i][j] += f[i - (1 << (j - 1))][p];
			}
	for (int i = 1; i <= n; i++)
		ans += f[(1 << n) - 1][i];
	cout << ans;
	return 0;
}
```


---

## 作者：keydu (赞：1)

最关键的就是这一句话
> N (4 <= N <= 16)

我想呀，这个也太明显了。。。zz先发个代码，按机房大佬的说法代码最直接了。。。
----------------------
```````javascript
#include<bits/stdc++.h>
#define REP(i,a,b) for(int i(a);i<=(b);++i)
using namespace std;
void read(long long  &x){
	x=0; char c=getchar(); int f=1;
	for (;!isdigit(c);c=getchar()) if (c=='-') f=-f;
	for (;isdigit(c);c=getchar()) x=x*10+c-'0';x*=f;}
long long n,k,amap[30],dp[1<<20][20],cow[30];
int main(){
	read(n); read(k); 
	REP(i,1,n) {read(amap[i]); cow[i]=1<<(i-1); dp[1<<(i-1)][i]=1;}
	int limi=(1<<(n))-1;
	REP(i,1,limi) {  REP(j,1,n) {
			if (cow[j]&i)  REP(kk,1,n) {
					if ((cow[kk]|i)!=i) {
						if (abs(amap[j]-amap[kk])>k) {
							dp[(i|(cow[kk]))][kk]+=dp[i][j];}}}}}
	long long ans=0;
	REP(i,1,n) ans+=dp[limi][i]; cout<<ans<<endl;
} 
```````
要注释一波；
先是最基本的快读。。
				蒟蒻不会打封装的读入|><| 我实在是太弱了
amap[]数组的意思是第i只牛的编号。。。
cow[]表示的是第i只牛，加入队列时的要 | 的位置
怎么说呢，比如 10000010 这样一个01串我们表示的就是第二只牛和第，，懒得数了只牛已经放好了的状态，当我们把这个01串与000010000， 相  |  后，几可以得出1---1--1中间的0自动神略（手动滑稽）的状态
dp表示的是 dp[ ][ ]第一个是枚举到的状态，，第二个是这个状态是第几只牛刚发进去，，，为什么要真么dp呢
------------
---------
 1. 首先啊，这是状压而且是n属于1--16的状压，既然给了你那么明显的数据提示那么，dp里面一般就会带有状态表示（我说的是一般，一般，一般！）
 2. 一般这类题型是不会让你直接就一维dp就可以刷爆的。好吧有特例（[你以为我会告诉你？](https://www.luogu.org/problemnew/show/P3052)）但这题也得要一点辅助的，，，
 3. 那么根据题意，看关键限制条件（要大于K），那么如果我们已经把前面的几头牛塞进状态中了，就不会对现在的dp转移有影响有影响的只能是刚放进去的，因为他的编号直接决定了你能否进入这个大家庭，，（we are family!!）
 -------
下面就是常用的提高加 状压dp模板呵呵
```
REP（1,0/1,limi(状态的最后表示形式））
REP（枚举的位置（要变换的编号）<这题中就是第几头牛的>）
		加大判定 IF (这头牛没有放进去（呸呸，这个位置上没有被站位）)  
        继续往下
REP （dp[ ][ ]两个格子中后面的一维中代表的数）再加个大判定
```
然后状态转移 然后输出答案

---

## 作者：Vin_1999 (赞：1)

状压的入门题吧，因为前面选择的数没有后效性所以可以用动规，dp[i][j]表示当前的选择状态为j，而最后一个选的数为i;

死于不会打ll的indef;orz








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
#define rep(i,s,n) for(int (i)=(s);(i)<=(n);(i)++)
#ifdef unix
#define ll "%lld"
#else
#define ll "%I64d"
#endif
using namespace std;
const int maxn=16;
static int a[maxn],n,lim;
static long long dp[maxn][1<<maxn],ans,cnt;
char s[maxn];
inline void init()
{
    scanf("%d%d",&n,&lim);
    rep(i,0,n-1) scanf("%d",&a[i]);
    rep(i,0,n-1) dp[i][1<<i]=1;
    cnt=1<<n;
}
int main()
{
     init();
     rep(i,0,cnt-1) rep(j,0,n-1) if(i&(1<<j))
     rep(k,0,n-1) if(!(i&(1<<k) )&&abs(a[j]-a[k])>lim  )
    dp[k][(1<<k)|i]+=dp[j][i];
    rep(i,0,n-1) ans+=dp[i][cnt-1];
    cout<<ans;
    return 0;  
}//by lyyz-ljy
```

---

## 作者：xfydemx (赞：1)

搞不懂了 这题应该是算我见过最水的一类状压了呀

唯一难一点的就是状态表示： 

考虑    ```
f[i][s]```  表示最后一位是i头牛，已经用过的二进制集合是s

然后就最简单的经典转移： 找一个选过的 i, 找一个没选过的 j,

```
f[j][s | (1 << j-1)] += f[i][s];
```

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cctype>
#include<cmath>
#include<bitset>
#define ll long long
using namespace std;
const int N = 1000005;
const ll INF = 0x3f3f3f3f;
inline int read() {
    int s = 1, w= 0; char c = getchar();
    for(; !isdigit(c); c=getchar()) if(c=='-') s = -1;
    for(; isdigit(c); c=getchar()) w = 10*w+c-'0';
    return s*w;
}
ll f[17][1<<17+1],dis[17][17],c[17],ans,n,k;
int main() {
	n = read(); k = read();
	for(int i = 1; i <= n; i++) c[i] = read();
	for(int i = 1; i <= n; i++) {
		f[i][1 << i-1] = 1;
	}
	int full = (1 << n) - 1;
	for(int s = 1; s <= full; s++) {
		for(int i = 1; i <= n; i++) {
			if(!(s & (1 << i-1))) continue;			
			for(int j = 1; j <= n; j++){
				if(s & (1 << j-1)) continue;
				if(abs(c[i] - c[j]) > k) f[j][s | (1 << j-1)] += f[i][s];
			}
		}
	}
	for(int i = 1; i <= n; i++) {
		ans += f[i][full];
	}
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：陈新月 (赞：1)

可以在我博客中看：  http://www.cnblogs.com/bingdada/p/7697887.html


思路：


看到n的范围这么小就能猜到是状态压缩的动态规划。


设f[i][j]为j在二进制表示的那些牛中以第i只牛为尾合法的队形总数，则我们就可以得到动态转移方程f[i][j | (1 << p-1)]  += f[i][j] ，其中f[i][j | (1 << p-1)] 为状态j加上（1 << p-1）这只牛后的状态。其中 1 <= p <= n。

该动态转移方程必须符合以下条件：


状态j中没有包括第p只牛，且abs(s[p]-s[i]) > k。


所以，我们枚举每一个状态，并且在每一个状态中枚举第每一只牛，看这只牛是否在该状态中，如果在，我们则在此情况下进一步枚举，看那一只牛不在当前状态里，找到不在当前状态中的牛之后就进行累加，即为:


f[没在当前状态中的牛的输入顺序编号][当前状态加上不在状态中的牛后的新状态]  += f[当前状态的结尾牛输入顺序编号][当前状态]；


初始化应该为f[i][1 << i] = 1, 因为，当队列中只有一只牛时最后一只牛的标号就是它本身且此情况上的子问题答案是1。


 

另外，这题因为答案大，所以要使用longlong，这里用到了条件编译，使得该程序将不受longlon影响。


下面贴代码，有问题留言。





```cpp
#include<cstdio>
#define N 1 << 17
#define S 20
using namespace std;
long long  f[S][N];
int s[20];
#ifdef WIN32　　　　　　　　　　　　//条件编译，省去longlong给程序带来的影响
#define LL "%I64d\n"
#else
#define LL "%lld\n"
#endif
int main(){
    int n,k;
    scanf("%d%d",&n,&k);
    for(int i = 1; i <= n; i++)scanf("%d",&s[i]);
    int mxx = (1 << n)-1;
    for(int i = 1; i <= n; i++)f[i][1 << (i-1)] = 1;
    for(int i = 0; i <= mxx+1;i++){　　　　　　　　　　　　　　　　//枚举每一个状态
        for(int j = 1; j <= n; j++){
            if(i & (1 << j-1)){　　　　　　　　　　　　　　　　//第j只牛是否在状态i中
                for(int p = 1; p <= n; p++)　　　　　　　　　　//进一步枚举没有在状态i中的牛
                  if(!(i & (1 << p-1)) && (s[j]-s[p] > k || s[p]-s[j] > k)){   //如果k不在队列中且差值大于k 
                        f[p][i | (1 << p-1)] += f[j][i];
                  }
            }
        }
    }
    long long  ans = 0;
    for(int i = 1; i <= n; i++)ans += f[i][mxx];
    printf(LL,ans);
    return 0;
}
```

---

## 作者：Feliks (赞：0)

# 状压dp

~~十年oi一场空，不用long long见祖宗~~

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
long long f[20][70020];//表示以i号牛为结尾，状态j的混乱方案数，70020>2**16
int a[20];
int main(){
	scanf("%d%d",&n,&k);
	int ns=(1<<n)-1;//总方案数
	for(int i=0;i<n;i++){
		scanf("%d",&a[i]);
	}
	for(int i=0;i<n;i++){
		f[i][1<<i]=1;//初始化，因为k>=1，所以只有一头牛时一定是混乱的
	}
	for(int i=0;i<=ns;i++){//枚举状态
		for(int j=0;j<n;j++){//枚举结尾的牛
			if(!(i&(1<<j))){
            //这里是状态i的第j位不是1，即j号牛不在状态i中时，continue
				continue;
			}
			if(f[j][i]){//这里是个优化，如果更新过这个状态就没必要更新了
				continue;
			}
			int m=i^(1<<j);//状态m是把状态中的j号牛去掉
			for(int g=0;g<n;g++){
				if(g==j){//如果j号牛已经在m的结尾里出现过，就不可能再在i的结尾出现
					continue;
				}
				if(abs(a[g]-a[j])>k){//满足混乱的条件
					f[j][i]+=f[g][m];
				}
			}
		}
	}
	long long ans=0;
	for(int i=0;i<n;i++){
		ans+=f[i][ns];//放满牛时结尾的牛不同的所有方案数之和
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：水無月嘉祥 (赞：0)

这道题，很明显是一道状压的题，但是在此之前，我要向大家介绍一个好东西——next_permutation()

## 这是什么？
这个函数是STL库里的，用于求全排列，但是它求的全排列是求一个数组里所有数的全排列（或者说字典序）。它是求升序的，它还有个兄弟——prev_permutation()，这个是求降序的
## 它怎么用？
函数括号内的打法同sort，数组名+左闭右开区间，一般它的用法是这样的：
```cpp
do
{
//在这里写你对于全排列的处理
}while(num+1,num+1+n)//num是数组名，区间是左闭右开
```

------------
有了以上知识就可以愉快的**骗分**了
### 但是请注意！全排列暴力找只能过50分（吸了O2是60分）本地实验发现不开优化时n=10是此法的极限
全排列代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;

int n,k;
int num[20];
long long ans;

int main()
{
	scanf("%d %d",&n,&k);
	for(int i=1;i<=n;i++)
		scanf("%d",&num[i]);
	sort(num+1,num+1+n);
	do
	{
		for(int i=2;i<=n;i++)
		{
			if(abs(num[i]-num[i-1])>k)
				continue;
			else
				goto jump;
		}
		ans++;
		jump:;
	}while(next_permutation(num+1,num+1+n));
	printf("%lld",ans);
	return 0;
}
```
------------
### 以下为正解（思路请看上面的大佬）
用状态压缩来进行求解（之前的大佬已经清晰解释过了，作为提供骗分思路的我就不再赘述，这里是按照上面某位大佬的代码打的）
```cpp
#include<bits/stdc++.h>
using namespace std;

int n,k;
int num[20];
long long f[20][70000];//最后放入的牛和此时状态 
long long ans;

int main()
{
	scanf("%d %d",&n,&k);
	for(int i=1;i<=n;i++)
		scanf("%d",&num[i]);
	for(int i=1;i<=n;i++)
		f[i][1<<(i-1)]=1;//初始化 
	for(int i=1;i<(1<<n);i++)//枚举状态 
		for(int j=1;j<=n;j++)//枚举最后放下的牛
			for(int l=1;l<=n;l++)//枚举现在放下的牛
			if(abs(num[j]-num[l])>k&&((1<<(j-1))&i)&&(((1<<(l-1))&i)==0))
				f[l][(1<<(l-1))|i]+=f[j][i];//f[l][放下牛后新状态]+=转移过来的f 
	for(int i=1;i<=n;i++)
		ans+=f[i][(1<<n)-1];
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：我惠美如画 (赞：0)

1.看到范围  _ **4<=n<=16**_ ,我们不难发现这是一道状压DP题

2.**The answer is guaranteed to fit in a 64 bit integer.**不知道有没有可怜的小伙伴没有看到这句话呢。这句话就提示我们答案要开** _long long_ ** 呀。

--------------------------


## 那么 ，进入正题。
### 位运算
说到状压dp，我们不能不提位运算。
位运算可以帮助我们理解程序运行中的种种表现，提高程序运行的时空效率的同时还可以降低编程复杂度。

C++中的位运算符有6种：

      &       与运算        同1得1
      |       或运算        有1得1
      ^       异或运算      不同得1
      ~       非运算        取反
      >>      右移运算
      <<      左移运算
      
这里要特别说一下左移和右移

左移：在二进制下把数字同时向左移动，低位补充0，高位舍弃。

右移在二进制补码表示下把数字同时向右移动，低位舍弃，高位以符号位填充。

利用二进制位运算 我们可以将每种状态表示出来

-------------------
## 状压DP，即通过二进制位运算将状态压缩（用整数表示集合）作为动态规划的状态来解决问题的办法

分析题意，2^n最大只有65536.我们可以开一个数组
f[(1 <<16) + 10][20]利用这个数组我们可以轻松快速地遍历所有状态。
### 如何遍历呢？
##### 我们只需知道每头牛是否已经被选和最后一牛的是第几只，
##### 所以设f[state][last]表示牛的排列状态为state,最后一头牛为
##### last时的合法队列数分别遍历上一头牛和这头牛
### 边界条件是dp[i][1<<i];
										
### 答案就是answer=∑（0~n）dp[(1<<n)−1][i]

## 转移方程 f[k][(1<<(k-1))|j]+=f[i][j];
代码如下：
```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
typedef long long ll;
inline ll read()
{
 	ll res=0,bo=1;
 	char ch=getchar();
 	while(ch<'0'||ch>'9'){if(ch=='-')bo=-1;ch=getchar();}
 	while(ch>='0'&&ch<='9'){res=(res<<1)+(res<<3)+ch-'0';ch=getchar();}
 	return bo*res;
}
ll dp[(1 <<16) + 10][20], n, a[20];
int main()
{
    n = read(); int p = read();
    for(int i = 0; i < n; ++i){
        a[i] = read(); 
    }
    for(int i = 0; i < n; ++i)
        dp[1 << i][i] = 1; //初始化
    for(int i = 1; i < 1 << n; ++i){//枚举状态
        for(int j = 0; j < n; ++j)
            if((1 << j) & i){//枚举最后一头牛
                for(int k = 0; k < n; ++k){
                    if(k != j && ((1 << k) & i) && abs(a[j] - a[k]) > p)
                        dp[i][j] += dp[i ^ (1 << j)][k]; //累计答案
                }
            } 
    }
    ll ans = 0;
    for(int i = 0; i < n; ++i){
        ans += dp[(1 << n) - 1][i]；统计答案
    }
    printf("%lld",ans);
    return 0;
}

```
 

---

## 作者：maomao (赞：0)

[P2915 [USACO08NOV]奶牛混合起来Mixed Up Cows](https://www.luogu.org/problemnew/show/P2915)

### 做此题前必须知道的一些事
设a,b,c为三个**十进制数**,a[i]表示**二进制下**数a的第i位,b[i]和c[i]同上.
1. 位运算符“|”(或):a|b表示a、b两数在二进制位下,对于任何a[i]与b[i]中只要有一个为1,c[i]的值就为1,否则为0.最后得到的c就是a|b

2. 位运算符“&”(与):a&b表示a、b两数在二进制位下,对于任何a[i]与b[i]都为1,c[i]的值就为1,否则为0.最后得到的c就是a&b

3. 位运算符“<<”(左移):a<<b表示a在二进制位下在末尾添加b个0,其在十进制数值上相当于a*(2^b)

### e.g.

a=01010010=2+16+64=82
b=10100010=2+32+128=162

a|b=11110010=2+16+32+64+128
a&b=00000010=2
a<<1=10100100=82*2=4+64+128=164

### 回到本题
关于本题,暴力的算法十分好想:枚举每一头牛,在满足条件(编号之差大于k)的情况下向下搜索,时间复杂度为O(n!),在n<=16时显然超时.

关于动态规划:
如果按照动态规划的一般做法,对于每一种会影响最后结果的状态都应被写成维度,就本题而言,每一头牛的位置都会对最后的结果产生影响
如果真的定义一个16维的数组,代码的复杂度会空前巨大,不可行.

观察每一个状态,容易看出每一头牛只有在或不在已排列的队伍中的两种状态(对于每一头牛,我们只需记录当它在队尾时的状态,因为它此时会影响新入队牛的合法性.没必要去关注每一头牛在队列中的位置),因此可以用一段长度为n的01序列来表示2^n种状态,对于第i头牛的状态,可以用01序列的第i位的值来表示它.这样的~~骚~~操作就叫**状态转移**.

### 具体实现
由于n<=16,2^n只有65536,所以我们可以轻松遍历所有状态.

定义f[i][s]为当状态为s,队尾的牛是第i头时,可以取到的最大方案数.此时,遍历n头牛,找出第j头牛满足**i和j的编号差大于k**,和**j之前没有被选过**(即j不在状态s中)两个条件,此时选中j,用f[i][s]更新f[j][包含j的新状态s]就可以得到此DP的状态转移方程,问题就可以用O(n^2*2^n)的复杂度解决了.


此时,如何判断j在s中及如何表示包含j的新状态s?由上文,我们知道,对于状态s,它在二进制下第i位的值就可以表达第i头牛是否在状态中,那么,1<<(i-1)就可以表示一个第i位为1的二进制数,用这个结果和状态s取"&"运算,整个式子的值为0时则说明状态s中没有i.(或者你可以取"|"运算,整个式子的值为s时则说明状态s中没有i)

那么,转移方程就愉快地写出来了:
### f[j][s|(1<<(i-1))]+=f[i][s];

## 代码:
```cpp
#include<bits/stdc++.h>
#define N 20
#define M 70010
#define R register int
#define C const int

using namespace std;

int n,k;
int a[N];
long long f[N][M]={0};

int main()
{
    //FRE;
    int n;
    scanf("%d%d",&n,&k);
    for(R i=1;i<=n;++i)scanf("%d",&a[i]);
    C l=(1<<n)-1;
    for(int i=1,j;i<=n;++i)
    {
        j=1<<(i-1);
      	f[i][j]=1;
    }
    for(R s=1;s<=l;++s)
    {
    	for(R i=1;i<=n;++i)
    	{
    		//if(s|(1<<(i-1))!=s)continue;
    		for(R j=1,now;j<=n;++j)
    		{
    			now=s|(1<<(j-1));
    			if(abs(a[i]-a[j])>k&&now!=s)f[j][now]+=f[i][s];
      		}
      	}
    }
    long long ans=0;
    for(int i=1;i<=n;++i)ans+=f[i][l];
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：aiyougege (赞：0)

### P2915 [USACO08NOV]奶牛混合起来Mixed Up Cows
#### Solution
　　做法是比较显然的.

　　用$f(i,j)$表示当前集合为$i$且队中最后一头牛是$j$的方案数.然后就可以列出转移方程了, 即
$$f(i,j)=\sum_{k\in \bar{j}}[|s_j-s_k|>k]f(\bar{j},k)$$

其中$\bar{j}$表示$i$中去掉$j$剩下的牛的集合.初始化所有只有一头牛的情况方案数为1,然后可以用**记忆化搜索**直接求解.复杂度$O(n2^n)$.
#### Code
还是需要用long long, 不注意会被坑去20分.
```c++
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#define N 20
#define M 600005
#define int long long
using namespace std;

int n,k;
int s[N];
int f[M][N];

int find(int a,int b){
	if(f[a][b])return f[a][b];
	int c=a-(1<<(b-1));
	for(int i=1;i<=n;++i)
		if(c&(1<<(i-1))&&abs(s[i]-s[b])>k)
			f[a][b]+=find(c,i);
	return f[a][b];
}

main(){
	scanf("%lld%lld",&n,&k);
	for(int i=1;i<=n;++i)scanf("%lld",&s[i]);
	int p=0,ans=0;
	for(int i=0;i<n;++i)f[1<<i][i+1]=1;
	for(int i=0;i<n;++i)p|=(1<<i);
	for(int i=1;i<=n;++i)ans+=find(p,i);
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：xxxxxxx__ (赞：0)

#### 一道稍微有一点难度的状压dp题！

#### 看到这题的数据范围n<=16就知道应该是个状压了 但是具体怎么操作呢？怎样来表示状态才是可做的？然后想一想就会发现其实每一次加入一个新的数字时 其实只和当前最后一个数字有关

#### 所以就搞出了我们的状态转移方程！

#### f[i][j]表示选择的状态为i时 最后一个数的下标是j （选择的状态就是选了的位置是1 还没选的是0）

#### 然后我们只要看一看它怎么能再加一个数字就行了 条件就是新的数字当前还没选 并且和j不冲突

#### 最后i=1~n 输出所有的f[(1<<n)-1][i]之和即可 （相当于是看一看每一个数作为结尾的情况）

#### 小提示：f数组和ans一定要开long long 不然会WA的（别问我怎么知道的…）


---

## 作者：Tweetuzki (赞：0)

类似于n皇后的思想，只要把dfs表示放置情况的数字压缩成一个整数，就能实现记忆化搜索了。

一些有关集合的操作：

{i}在集合S内：S&(1<<i)==1；

将{i}加入集合S：S=S|(1<<i)；

集合S内包含了{0,1,2,...,n-2,n-1}：S==(1<<n)-1；

```cpp
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;

typedef long long llt;
const int maxn=16;
int n,k;
//每只奶牛的高度 
int a[maxn];
//记忆化数组 
llt dp[maxn][1<<maxn];

void init() {
    scanf("%d%d",&n,&k);
    for (int i=0;i<n;i++)
        scanf("%d",a+i);
    //因为可能搜索完答案是0，所以说要初始化成-1 
    memset(dp,-1,sizeof(dp));
}

//搜索以x号奶牛为队尾，状态为S时可以有多少种情况 
llt dfs(int x, int S) {
    //如果全部奶牛都能放进来，且构成了一个混乱队形，则有一种情况 
    if (S==(1<<n)-1) return 1;
    //记忆化 
    if (dp[x][S]!=-1) return dp[x][S];
    llt res=0;
    for (int i=0;i<n;i++) {
        //判断是否符合情况 
        if (S&(1<<i)) continue;
        if (abs(a[x]-a[i])<=k) continue;
        //继续搜索 
        res+=dfs(i,S|(1<<i));
    }
    return dp[x][S]=res;
}

int main() {
    init();
    llt ans=0;
    //每种奶牛都当一次队头 
    for (int i=0;i<n;i++)
        ans+=dfs(i,1<<i);
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：远航之曲 (赞：0)

首先观察N的范围，非常小。

这样我们就可以联想一下，用一个二进制数表示队伍中有哪些奶牛。

用dp[i, j]表示 j状态下，队伍末尾奶牛编号为i的方案数

然后就可以枚举来寻找一个能往队伍末尾塞的奶牛编号

这个限制就是相邻的奶牛的编号相差超过K，并且这个奶牛不存在于队伍中

然后注意就是初值不能是f[i][0]=1，因为所有牛本来都可以第一个被选中，然而这样一定初值有些牛可能就无法被第一个选出了，因此应该是f[i][1<<i]=1。


代码

```cpp
#include <cstdio>
#include <cstdlib>
using namespace std;
int a[17];
int n,k1;
long long dp[16][1<<16];
main()
{
    scanf("%d%d",&n,&k1);
    for (int i=0;i<n;i++)
        scanf("%d",&a[i]);
    for (int i=0;i<n;i++)
        dp[i][1<<i]=1;
    for (int i=0;i<(1<<n);i++)
        for (int j=0;j<n;j++)
            if (i & (1<<j))
                for (int k=0;k<n;k++)
                    if(!(i&(1<<k)) && abs(a[j]-a[k])>k1)
                        dp[k][i|(1<<k)]+=dp[j][i];
    long long ans=0;
    for (int i=0;i<n;i++)
        ans+=dp[i][(1<<n)-1];
    printf("%lld",ans);
}

```

---

