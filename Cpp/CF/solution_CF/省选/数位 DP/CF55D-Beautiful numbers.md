# Beautiful numbers

## 题目描述

Volodya is an odd boy and his taste is strange as well. It seems to him that a positive integer number is beautiful if and only if it is divisible by each of its nonzero digits. We will not argue with this and just count the quantity of beautiful numbers in given ranges.

## 样例 #1

### 输入

```
1
1 9
```

### 输出

```
9
```

## 样例 #2

### 输入

```
1
12 15
```

### 输出

```
2
```

# 题解

## 作者：_agKc_ (赞：71)

# 蒟蒻操作一波终于A过了这道水题
**本蒟蒻前几天才学数位DP，个人感觉这道题与[P2657 windy数](https://www.luogu.org/problem/P2657)有异曲同工之妙（真的只是个人感觉）**      
**Warning：如果还不熟练数位DP康这道题可能会死大量脑细胞**

**与其他的黑题相比，这道题真的简单太多了（虽然我也是在题解dalao们的启发下做出来的），所以我打算写一篇通俗易懂点的题解，也算是对其他dalao们的补充**

## 进入正题
先说在前面，因为数据量极大，所以一个个的枚举是不行的！！！
所以我们可以将[l,r]的区间变成[1,r]-[1,l-1]，这就是所谓的差分。

为了解决这道题，我们还需要了解两点小学数学知识：  
1.一个数如果可以被几个数整除，那么这个数也可以被那几个数的最小公倍数整除；   
2."1,2,3,4,5,6,7,8,9"的最小公倍数为2520 ~~（废话）~~ 。

知道后我们就可以开始解题了。  
首先，因为是DP，所以我们需要一个DP数组来将宝贵中间的运算结果储存下来，之后可以直接使用（因为DP使用的是DFS，所以也可以看作记忆化剪枝）。  

接着，因为是数位DP，所以我们需要DP数组开一个维度来储存当前位数。  

其次，因为最后要检测这个数是否满足条件： _能被它自己的每一位数上的数整除_ （也就是被每一位上的数的最小公倍数整除），所以我们又需要开两个维度：一个存数的值，一个存这个数每一位上的数的最小公倍数。   

但我们不难发现，想存9*10（18）是不可能的，又因为题目最后是检测这个数能否被每一位上的数的最小公倍数整除，假设这个数为A，那么A与（A%2520）其实是等效的，所以我们可以不存A而存（A%2520），这样问题就解决了   
       
于是我们就开了一个数组：DP[20(因为总共就19位数)][2521][2521]（DP数组内的数据表示满足当前情况的 _Beautiful numbers_ 的个数），准备直接开始跑，然后就可以坐等~~AC~~内存超限了。  

所以问题又来了：数组开不下。于是我们思考怎么减小数组：第一二位已经到最小了，只能改第三维。我们通过计算发现，1~2520中，2520的因数只有48个，也就是满足条件的情况只有48种，所以第三维大小直接变为48（这到底是属于撞鸭还是离散化？蒟蒻傻傻分不清）

### 上代码（还有些细节部分会在代码中注释）

**！！！因为借鉴了题解dalao们的思路，所以代码会很相像！！！**

```cpp
#define Tokisaki return  //狂三我老婆！！！
#define Kurumi 0;      //狂三赛高！！！
#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

#define rint register int   //加速用的，直接用int也可以
typedef long long ll;

using namespace std;

const int MOD=2520;
int t,book[MOD+1];
vector <int> shu;
ll l,r,dp[25][MOD+1][50];   //特别注意：DP数组一定要开long long类型，不然会炸

inline int gcd (int x,int y) //gcd函数，虽然STL里面自带（为__gcd），但还是自己手写了一个
{
	if(x>y) swap(x,y);
	if(y%x==0) return x;
	return gcd(x,y%x);
}

inline int _lcm (int x,int y)  //lcm函数，求最小公约数
{
	return x*y/gcd(x,y);
}

inline void init()         //初始化用的函数
{
	memset(dp,-1,sizeof(dp));  //将DP数组初始化
	rint num=0;
	for(rint i=1;i<=MOD;i++)   //离散化，将2520的因数们从1开始标记
	{
		if(MOD%i==0)
		{
			num++;
			book[i]=num;
		}
	}
}

ll dfs(int pos,int he,int lcm,int sp)  //数位DP主要内容
//pos:当前处理到第几位；     
//he：pos位之前的数%2520；
//lcm：pos位之前的数的每一位数的最小公倍数；
//sp：特判当前是否为范围内的最大值
{
	if(pos==-1) return he%lcm==0;    //如果处理完了最后一位，数如果满足条件，返回1，否则返回0
	if(sp==0&&dp[pos][he][book[lcm]]!=-1) return dp[pos][he][book[lcm]];      //如果不是最大值的情况，并且当前情况以处理过，直接返回值
	ll ans=0;
	int MAX=sp==1?shu[pos]:9;  //如果前几位是最大值情况，那么当前位最大值为这一位的数，否则为9
	for(rint i=0;i<=MAX;i++)  //从0枚举
	{
		int next_he=(he*10+i)%MOD;  //计算包含当前位时数的值
		int next_lcm=lcm;  
		if(i)
		{
			next_lcm=_lcm(next_lcm,i);//计算包含当前位时所有位上的数的最小公倍数（当前位所选数不为0，如果为零就是原数）
		}
		ans+=dfs(pos-1,next_he,next_lcm,sp&&i==MAX); //向下搜索，如果前几位是最大值情况，并且当前位为最大值时，sp=1
	}
	if(sp==0)   //如果不是最大值情况，记录运算结果
	{
		dp[pos][he][book[lcm]]=ans;
	}
	return ans;
}

inline ll work (ll num)   //处理数据加求值函数
{
	
	shu.clear();     //一定要记得清空
	while(num)       //将数值按为存入
	{
		shu.push_back(num%10);
		num/=10;
	}
	return dfs(shu.size()-1,0,1,1); //从最高位开始搜索
}

int main ()
{
	init();  //初始化
	cin>>t;
	for(int i=1;i<=t;i++)
	{
		cin>>l>>r;
		cout<<work(r)-work(l-1)<<endl;
	}
	Tokisaki Kurumi   //狂三我老婆，不服憋着
}
```

那么这便是代码了（好像混入了什么奇怪的东西）

## 题目解决，恭喜你通过一道黑题！！！

---

## 作者：hsfzLZH1 (赞：34)

## G - Beautiful numbers

题目网址：https://vjudge.net/contest/243352#problem/G

题目来源：CF 55D http://codeforces.com/problemset/problem/55/D

time limit per test $4$ seconds

memory limit per test $256$ megabytes

Volodya is an odd boy and his taste is strange as well. It seems to him that a positive integer number is beautiful if and only if it is divisible by each of its nonzero digits. We will not argue with this and just count the quantity of beautiful numbers in given ranges.

#### Input

The first line of the input contains the number of cases $t$ ($1\le t\le 10$). Each of the next t lines contains two natural numbers $l_i$ and $r_i$ ($1\le l_i\le r_i\le 9\times 10^{18}$).

Please, do not use $\%lld$ specificator to read or write $64-bit$ integers in $C++$. It is preffered to use $cin$ (also you may use $\%I64d$).

#### Output

Output should contain $t$ numbers — answers to the queries, one number per line — quantities of beautiful numbers in given intervals (from $l_i$ to $r_i$, inclusively).
#### Examples
**Input**
```
1
1 9
```
**Output**
```
9
```
**Input**
```
1
12 15
```
**Output**
```
2
```

题目大意：对于一个正整数$n$，可以被其每一个数位上的数整除，即若$n$可以表示为$\sum_{i=0}^{m}a_i\times 10^i (0\le a_i\le 9)$，有$\forall a_i,a_i|n$，那么这个数被称为$Beautiful~Number$。现在，需要你求出区间里的$Beautiful~Number$的个数。

数位$DP$模板题。看到求区间内满足某种条件的个数的题目，首先想到的就是差分，将求区间$[l,r]$内满足条件的数的个数转化为求两个区间$[1,r],[1,l-1]$内满足条件的数的个数的差。

我们发现如果一个数能整除它的所有数位上的数，那么它一定能整除所有这些数位上的数的最小公倍数（性质$1$），而$1$到$9$的最小公倍数是$2520$，所有数可能形成的数位上所有数的最小公倍数一定是$2520$的因数。（性质$2$）以它的平方为时间复杂度可以接受。

我们定义$f[i][j][k]$表示剩下$i$位需要规划，这前$i$位模$2520$的余数是$j$，当前的前$i$位数的最小公倍数是$k$，满足这些条件的$Beautiful~Number$的个数。

由于性质$1$,如果最后的数能整除$k$，那么它一定能整除它各位数字的最小公倍数。由于性质$2$,所有可能出现的$k$都是$2520$的因数，借助这一性质，将$j$取模$2520$，若所得的结果整除$k$，那么原来的数也一定整除$k$。

由f的定义，我们可以写出状态转移方程

$f[i][j][k]=\sum f[i-1][(j\times10+x)~mod~2520][lcm(k,x)]~~~[1\le x\le maxx]$

在转移的过程中，需要注意前缀$0$的处理。

然而，我们发现$f$数组占用了$18\times 2520\times2520=114307200$的内存，很显然太大了。但是$1$到$9$中任取一些数作$lcm$，有很多值是根本取不到的，浪费了很多空间。我们预处理一下，最多只有$48$种可能，远远小于$2520$，建立映射的关系，将其中的一维压成$50$，大大减小了空间占用，使得空间变得可以接受。

代码：
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int maxn=20;
const int mod=2520;
int T,cur,a[mod+1];
ll l,r,f[20][mod+1][50];
vector<int>dim;
int gcd(int x,int y){return x%y?gcd(y,x%y):y;}
int lcm_(int x,int y){if(!y)return x;return x/gcd(x,y)*y;}
ll dfs(int x,int mode,int lcm,bool op)
{
    if(!x)return mode%lcm==0?1:0;
    if(!op&&f[x][mode][a[lcm]])return f[x][mode][a[lcm]];
    int maxx=op?dim[x]:9;ll ret=0;
    for(int i=0;i<=maxx;i++)ret+=dfs(x-1,(mode*10+i)%mod,lcm_(lcm,i),op&(i==maxx));
    if(!op)f[x][mode][a[lcm]]=ret;
    return ret;
}
ll solve(ll x)
{
    dim.clear();
    dim.push_back(-1);
    ll t=x;
    while(t)dim.push_back(t%10),t/=10;
    return dfs(dim.size()-1,0,1,1);
}
main()
{
    for(int i=1;i<=mod;i++)if(mod%i==0)a[i]=++cur;
    scanf("%d",&T);
    while(T--)scanf("%lld%lld",&l,&r),printf("%lld\n",solve(r)-solve(l-1));
    return 0;
}
```

---

## 作者：Owen_codeisking (赞：20)

前排$orz$ @加藤圣教_封仙 太强啦，每次我$AC$了以后都能看到你的题解%%%

这题做法比较套路，个人觉得省选/NOI-就够了，NOI/NOI+CTSC有点虚高

数位$dp$，发现它只跟当前数模$lcm(1,2,...,9)=2520$和数位上出现了$1..9$这些数字有关，那么记录$dp[len][pre][lcm]$表示当前第$len$位$pre\ mod \ 2520$和最后数位各个数字的$lcm$，那么可以进行记忆化搜索

核心代码：
```cpp
long long ret=0;int ed=limit?digit[len]:9;
for(int i=0;i<=ed;i++)
	ret+=dfs(len-1,(pre*10+i)%2520,i==0?lcm:lcm*i/gcd(lcm,i),limit&&i==ed);
```

$Code\ Below:$
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
int digit[20],mp[2521],cnt;
ll dp[20][2521][50];

int gcd(int a,int b){
    return b==0?a:gcd(b,a%b);
}

ll dfs(int len,int pre,int mod,int limit){
    if(!len) return pre%mod==0;
    if(!limit&&dp[len][pre][mp[mod]]!=-1) return dp[len][pre][mp[mod]];
    ll ret=0;int ed=limit?digit[len]:9;
    for(int i=0;i<=ed;i++)
        ret+=dfs(len-1,(pre*10+i)%2520,i==0?mod:mod*i/gcd(mod,i),limit&&i==ed);
    if(!limit) dp[len][pre][mp[mod]]=ret;
    return ret;
}

ll calc(ll n){
    int len=0;
    while(n){
        digit[++len]=n%10;
        n/=10;
    }
    return dfs(len,0,1,1);
}

int main()
{
	memset(dp,-1,sizeof(dp));
    for(int i=1;i<=2520;i++)
        if(2520%i==0) mp[i]=++cnt;
    int T;ll l,r;
    cin>>T;
    while(T--){
        cin>>l>>r;
        cout<<calc(r)-calc(l-1)<<endl;
    }
    return 0;
}
```
话说我把$memset(dp,-1,sizeof(dp))$放最前面就$AC$了，而且洛谷当前$rank\ 3$...我也不知道为什么，反正就是跑的飞快

---

## 作者：QwQcOrZ (赞：13)

首先有个结论，对于 $n$ 个数 $a_{1...n}$，设它们的 $LCM$ 为 $L$，那么对于每个 $i$ 和一个自然数 $x$，$x\ \operatorname{mod}\ a_i=x\ \operatorname{mod}\ L\ \operatorname{mod}\ a_i$

证明显然

也就是说对于每个数，我们只在意它 $\operatorname{mod\ lcm}\{1,2,3,...,9\}$ 的值，因为我们只需要知道它是否整除 $1$ 到 $9$ 中的某些数（$Tips$：$\operatorname{lcm}\{1,2,3,...,9\}=2520$）

还有一个结论：一个数 $x$ 要满足被 $y_1,y_2,y_3,...,y_n$ 这些数整除，充分必要条件为 $x$ 被 $\operatorname{lcm}\{y_1,y_2,y_3,...,y_n\}$ 整除

证明依然很显然

那么我们就可以数位 $dp$ 了！

设 $f_{i,j,k,0/1}$ 表示当前转移到了上界的前 $i$ 高位，满足模 $2520$ 后为 $j$，各位数位的 $\operatorname{lcm}$ 为 $k$，并且当前填的数是$/$否达到上界的数有多少个

然后简单转移即可

最后满足 $j\ \operatorname{mod}\ k=0$ 的所有 $f_{n,j,k,0/1}$ 的和即为答案

------------

然后你就发现 `TLE on test 11` 了

可以发现 $f_{i,j,k,0/1}$ 中有意义的 $k$ 值不多（$k$ 为 $1$ 到 $9$ 中某些数的 $\operatorname{lcm}$ 时才有意义）

那么可以预处理出所有合法的 $k$ 值，然后拿这些值去 $dp$ 即可

------------

然后你就发现你又 `TLE on test 11` 了

考虑 $dp$ 时所有数都小于 $2520$ 那么可以预处理出所有数对的 $\operatorname{lcm}$ 或者在求 $\operatorname{lcm}$ 时记忆化，即可将求 $\operatorname{lcm}$ 的过程优化到 $\mathcal{O(1)}$

------------

然后你就发现你还是 `TLE on test 11` 了

考虑继续优化，因为在 $f_{i,j,k,0/1}$ 中如果最后一维为 $1$，那么合法的情况只有一种，而每次都要转移会增大常数。然后最后一维为 $0$ 时其实也是有一部分是没有情况会满足的

那么可以使用刷表法，然后当当前枚举到的 $f$ 没有值时就不进行转移，可以使常数骤减

------------

然后你就发现你 `Accepted` 了！

$Code\ Below$

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
#define ll long long
using namespace std;
const int N=2525;
const int M=50;
const int p=2520;

ll read()
{
	ll s=0;
	char c=getchar(),lc='+';
	while (c<'0'||'9'<c) lc=c,c=getchar();
	while ('0'<=c&&c<='9') s=s*10+c-'0',c=getchar();
	return lc=='-'?-s:s;
}
void write(ll x)
{
	if (x<0)
	{
		putchar('-');
		x=-x;
	}
	if (x<10) putchar(x+'0');
	else
	{
		write(x/10);
		putchar(x%10+'0');
	}
}
void print(ll x=-1,char c='\n')
{
	write(x);
	putchar(c);
}
int MOD[114514];
int Mod(register int x)//优化取模，但其实并没什么用，当时卡常时写的
{
	if (~MOD[x]) return MOD[x];
	return MOD[x]=x%p;
}
ll gcd(register ll x,register ll y)
{
	return !y?x:gcd(y,x%y);
}
int LCM[N][N];
inline ll lcm(register ll x,register ll y)//记忆化求 lcm，注意特判与 0 取 lcm 的情况
{
	if (!x||!y) return x|y;
	if (LCM[x][y]) return LCM[x][y];
	return LCM[x][y]=x/gcd(x,y)*y;
}
int nd[N],d[M],cnt=0,a[21];
ll dp[21][N][M][2];
ll calc(register ll n)
{
	register ll tmp=n;
	register int m=0;
	while (tmp)
	{
		a[++m]=tmp%10;
		tmp/=10;
	}
	memset(dp,0,sizeof(dp));
	dp[m+1][0][1][1]=1;
	for (register int i=m;i>=1;i--)
	for (register int j=0;j<p;j++)
	for (register int k=1;k<=cnt;k++)
	{
		if (dp[i+1][j][k][0]) for (register int t=0;t<=9;t++) dp[i][Mod(j*10+t)][nd[lcm(d[k],t)]][0]+=dp[i+1][j][k][0];
		if (dp[i+1][j][k][1])
		{
			for (register int t=0;t<a[i];t++) dp[i][Mod(j*10+t)][nd[lcm(d[k],t)]][0]+=dp[i+1][j][k][1];
			dp[i][Mod(j*10+a[i])][nd[lcm(d[k],a[i])]][1]+=dp[i+1][j][k][1];
		}
	}
	ll ret=0;
	for (register int j=0;j<p;j++)
	for (register int k=1;k<=cnt;k++)
	if (j%d[k]==0)
	ret+=dp[1][j][k][0]+dp[1][j][k][1];
	return ret;
}

signed main(int Recall,char *_902_[])
{
	memset(MOD,-1,sizeof(MOD));
	for (int i=1;i<=p;i++)
	if (p%i==0)
	{
		d[++cnt]=i;
		nd[i]=cnt;
	}
	int T=read();
	while (T--)
	{
		ll l=read(),r=read();
		print(calc(r)-calc(l-1));
	}

	return 0;
}
```

---

## 作者：hzoi_liuchang (赞：10)

## 分析
一句话题意：有T组询问，每次询问区间[l, r]中的beautiful number有多少。beautiful number是指这个数可以被组成它的数字整除。例如15是beautiful number,因为15可以被1整除，也可以被5整除。25不是beautiful number, 25不能被2整除。

这道题数据范围达到了9e18，如果暴力枚举的话一定会T掉

所以我们要借助一个神奇的东西-——数位DP
## 0x00 前置知识：数位DP
引用自[StungYep](https://www.cnblogs.com/StungYep/p/12254173.html#2662535644)的博客
### 定义
数位dp(Digit Entry DP)是一种计数用的dp，一般就是要统计区间[l,r]内满足一些条件的数的个数。所谓数位dp，字面意思就是在数位上进行dp。数位的含义：一个数有个位、十位、百位、千位......数的每一位就是数位啦！

### 数位dp的思想
数位dp的实质就是换一种暴力枚举的方式，使得新的枚举方式满足dp的性质，然后记忆化就可以了。
### 模板
```cpp
typedef long long ll;
int a[20];
ll dp[20][state];   //不同题目状态不同
ll dfs(int pos,int state,bool lead,bool limit)       //变量，状态，前导0，数位上界；注意不是每题都要判断前导零
{
    if(pos==0) return 1;    //递归边界，一般一种递归到结束只能产生一种情况
    if(!limit && !lead && dp[pos][state]!=-1) return dp[pos][state];    //记忆化
    int up=limit?a[pos]:9;  //枚举上界
    ll ans=0;               //计数
    for(int i=0;i<=up;i++)  //枚举，然后把不同情况的个数加到ans就可以了
    {
        if() ...
        else if()...        //一下条件
        ans+=dfs(pos-1,/*状态转移*/,lead && i==0,limit && i==a[pos]) //最后两个变量传参都是这样写的
        //state状态转移要保证i的合法性，比如不能有62，那么当pre==6&&i==2就不合法，这里用state记录pre是否为6即可。
    }
    if(!limit && !lead) dp[pos][state]=ans;
    return ans;
}
ll solve(ll x)
{
    int tot=0;
    while(x)
    {
        a[++tot]=x%10;
        x/=10;
    }
    return dfs(tot/*从最高位开始枚举*/,/*一系列状态 */,true,true);//刚开始最高位都是有限制并且有前导零的，显然比最高位还要高的一位视为0嘛
}
int main()
{
    ll le,ri;
    while(~scanf("%lld%lld",&le,&ri))
    {
        //初始化dp数组为-1,这里还有更加优美的优化,后面讲
        printf("%lld\n",solve(ri)-solve(le-1));
    }
}
```
## 0x01 特征
对于一个正整数，什么情况下它才能被组成它的非零数字整除呢

这个应该比较好想，只有当这个正整数能被它所有数位的最小公倍数整除时，它才能被每一个数位整除

而且，我们还知道1，2，3，4，5，6，7，8，9的最小公倍数是2520（后面要用到）

## 0x02 数组定义
我们要进行DP的话，肯定要定义一个f 数组存储我们计算过的值

因为这道题和数位有关，所以第一位我们要定义当前遍历到了第几位

而且我们还要判断当前的数是否能被它所有数位的最小公倍数整除

所以我们还要开两维记录当前的数和它所有数位的最小公倍数

所以，最后的f数组就是f[当前枚举到了第几位][当前的数][当前数所有数位的最小公倍数]

题目中给出的最大的数就是9e18，所以最多有19位，那么第一维我们开20就可以了

第二维我们显然不能开到9e18，会超内存

因为我们最终统计的是这个数能否被它所有数位的最小公倍数整除，所以我们不必要记录原数的值

我们只需要记录原数对2520取模的结果就可以，因为2520是1到9的最小公倍数，所以取模之后不会有影响，x与x%2520是等效的

这时我们算一下内存20*2520*2520，还是会M掉

所以我们考虑减省一下第三维，由于第三维记录的是所有数位的最小公倍数，所以有很多数并不会出现

比如11、13、17、19……它们并不是1到9中任意几个数的最小公倍数

所以我们只需要记录2520的因数就可以了，这样的数有48个，所以我们开50就可以了

附48个数：

1 2 3 4 5 6 7 8 9 10 12 14 15 18 20 21 24 28 30 35 36 40 42 45 56 60 63 70 72 84 90 105 120 126 140 168 180 210 252 280 315 360 420 504 630 840 1260 2520 
## 0x03:主函数
先上代码
```cpp
int main(){
    int t;
    scanf("%d",&t);
    for(ll i=1,j=0;i<=2520;i++){
        if(2520%i==0){
            lcm[i]=j++;
        }
    }
    memset(f,-1,sizeof(f));
    while(t--){
        ll aa,bb;
        scanf("%lld%lld",&aa,&bb);
        ll ans=solve(bb)-solve(aa-1);
        printf("%lld\n",ans);
    }
    return 0;
}
```
前三行没有什么好说的，我们来看一下4到8行，这里就是建立了一种映射关系，把前面的48个数分别看成0到47

这其实和离散化差不多

第九行是初始化，我们这里把它写在询问的外面是因为之后的询问可能会用到前面的值，这样比较快一些

第13行的solve函数我们在下面会提到

这里的solve(bb)-solve(aa-1)实际上是用到了一种差分的思想


## 0x04:solve函数
```cpp
ll solve(ll x){
    ll cnt=0;
    memset(num,0,sizeof(num));
    while(x!=0){
        num[cnt++]=x%10;
        x/=10;
    }
    return asd(cnt-1,0,1,1);
}
```
这里的cnt是用来记录当前的数有多少位，num数组是用来记录这个数每一位上的数字的

这个函数的变量只有一个xx,返回值是0到xx之间beautiful number的个数

下面的一个asd函数是最重要的部分

ll asd(ll now,ll mod,ll gbs,ll jud){
它的四个参数分别为:当前处理到第now位； now位之前的数%2520； now位之前的数的每一位数的最小公倍数；jud特判前一位是否为范围内的最大值

前三个参数比较好理解，我们着重来讲一下第四个参数jud

我们来举一个例子

比如说我们要求的数为5456

我们把它的千位设为第3位，百位设为第2位，十位设为第1位，个位设为第0位

 当它的第三位为0、1、2、3、4时，它的第二位可以从0枚举到9

但是当它的第三位枚举到5时，第二位的数就只能枚举到4

所以我们用一个变量jud记录前一位能不能达到最大值，如果上一位达到了最大值，那么这一位就只能枚举到当前位上的数

如果上一位没有达到最大值，那么这一位就可以从0到9随便枚举

## 0x05:asd函数
```cpp
ll asd(ll now,ll mod,ll gbs,ll jud){
    if(now<0){
        if(mod%gbs==0) return 1;
        else return 0;
    }
    if(jud==0 && f[now][mod][lcm[gbs]]!=-1){
        return f[now][mod][lcm[gbs]];
    }
    ll mmax=9,mans=0;
    if(jud==1) mmax=num[now];
    for(ll i=0;i<=mmax;i++){
         mans+=asd(now-1,(mod*10+i)%2520,i!=0?i*gbs/gcd(i,gbs):gbs,jud&&i==mmax);
    }
    if(jud==0) f[now][mod][lcm[gbs]]=mans;
    return mans;
}
```
第一行的参数我们已经在上面讲过了

那么我们来看一下最开始传的参数 cnt-1,0,1,1

cnt是我们要求的那个数的位数，因为我是从0开始编号，所以要传cnt-1，就是该数的最高位

因为最高位前没有数，所以第二个参数我们传0

第三个数是前面所有位数的最小公倍数，那么我们可不可以传0呢

应该是不可以的，因为我们如果传0的话，有可能会出现RE（因为一个数不能对0取模）的情况

所以我们最好还是传一个1

为什么呢？因为1与其他位去求最小公倍数的话，不会影响最终的结果

最后一个参数是判断前一位是否为范围内的最大值，显然是，所以我们传1

2到5行是一个终止条件
```cpp
if(now<0){
        if(mod%gbs==0) return 1;
        else return 0;
    }
```
如果当前的位数小于0，说明这个数我已经处理完了，那我们只要判断mod（该数%2520）能否被gbs（最小公倍数）整除就可以了

如果能够整除返回1，否则返回0

6到8行是一个特殊判断，可以提升我们的效率
```cpp
if(jud==0 && f[now][mod][lcm[gbs]]!=-1){
        return f[now][mod][lcm[gbs]];
    }
```
如果当前的f值已经求出来过，并且没有数位限制，那我们就可以直接用

如果有数位限制，那我们就不能直接用，因为我们不知道这两次的数位限制是否相等
```cpp
ll mmax=9,mans=0;
    if(jud==1) mmax=num[now];
```
第9、10行则是判断该数位可以枚举到几

如果上一个数位没有达到最大值，那我们就把可以枚举到的最大数置为9

否则，可以枚举到的最大数就由当前这一位决定
```cpp
for(ll i=0;i<=mmax;i++){
         mans+=asd(now-1,(mod*10+i)%2520,i!=0?i*gbs/gcd(i,gbs):gbs,jud&&i==mmax);
    }
    if(jud==0) f[now][mod][lcm[gbs]]=mans;
    return mans;
```
最后几行则是普通情况，即没有达到边界

这是我们就要一位一位地去枚举下一位的状态

首先我们来看这句话
```cpp
mans+=asd(now-1,(mod*10+i)%2520,i!=0?i*gbs/gcd(i,gbs):gbs,jud&&i==mmax);
```
这句话其实就是向下传参数，递归解决问题

第一个参数位数肯定要减去1变成now-1

第二个参数则是之前的数位表示的数乘10再加上当前这一位的数，再对2520取模

为什么要乘10呢，这就要联系数字的实际意义

比如25，它的值是2*10+5

2345，它的值是2*1000+3*100+4*10+5

我们就拿2345来举例子，它一共有4位，要遍历5次

第一次它没有乘10，最后一次遍历时会在第二句话那里触发终止条件，也就是说

2会乘3次10，3会乘2次10，4会乘1次10，5一次也不会乘

把这个过程加起来正好是原数，在中间取一下模并不会影响结果

第三个参数比较长，我们把它展开就是
```cpp
if(当前位上的数字为0){
    最小公倍数不变
} else {
    和之前数位上的数字取最小公倍数
}
```
a和b的最小公倍数就是a*b/a和b的最大公因数

下面是求最大公因数的函数
```cpp
ll gcd(ll a,ll b){
    if(b==0) return a;
    return gcd(b,a%b);
}
```
最后一个参数是判断最高位

==的优先级要高于位运算，所以其实就是一个判断当前数字是否为该位上的最大数字的操作

如果上一位有限制并且当前枚举到的是该数位上合法的最大的数字，我们就传1，否则传0

比如2345

当我们的千位上枚举到1，百位上枚举到9时，虽然9是最大的数字。但是第一个条件jud==1并不满足，所以这时我们要传0

当我们的千位上枚举到2，百位上枚举到3时，这时两个条件都满足，所以这时我们要传1

最后不要忘了更新f的值

## 0x06:代码
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
ll lcm[3000],f[20][3000][55],num[55];
ll gcd(ll a,ll b){
    if(b==0) return a;
    return gcd(b,a%b);
}
ll asd(ll now,ll mod,ll gbs,ll jud){
    if(now<0){
        if(mod%gbs==0) return 1;
        else return 0;
    }
    if(jud==0 && f[now][mod][lcm[gbs]]!=-1){
        return f[now][mod][lcm[gbs]];
    }
    ll mmax=9,mans=0;
    if(jud==1) mmax=num[now];
    for(ll i=0;i<=mmax;i++){
         mans+=asd(now-1,(mod*10+i)%2520,i!=0?i*gbs/gcd(i,gbs):gbs,jud&&i==mmax);
    }
    if(jud==0) f[now][mod][lcm[gbs]]=mans;
    return mans;
}
ll solve(ll x){
    ll cnt=0;
    memset(num,0,sizeof(num));
    while(x!=0){
        num[cnt++]=x%10;
        x/=10;
    }
    return asd(cnt-1,0,1,1);
}
int main(){
    int t;
    scanf("%d",&t);
    for(ll i=1,j=0;i<=2520;i++){
        if(2520%i==0){
            lcm[i]=j++;
        }
    }
    memset(f,-1,sizeof(f));
    while(t--){
        ll aa,bb;
        scanf("%lld%lld",&aa,&bb);
        ll ans=solve(bb)-solve(aa-1);
        printf("%lld\n",ans);
    }
    return 0;
}
```


---

## 作者：Michmh (赞：6)

题解列表中只有记忆化搜索的写法，这里补充一下 for 循环的写法：

设状态 $d[i][j][k][l]$ 为满足题义条件数字的个数，其中 $i$ 表示当前枚举数位，$j$ 表示当前状态模 $\text{lcm}(1\sim 9) = 2520$ 的余数 ， $k$ 表示当前状态与上界的关系 ($1$ 代表等于，$0$ 代表小于) ， $l$ 通过 $\text {lcm}$ 压缩状态表示 $1\sim 9$ 在数位中出现的情况。 

注意 $\text {lcm}$ 需要预先处理， $2520$ 的因子也进行预处理并离散化，$l$ 用 $\text {lcm}$ 编号表示。

状态转移方程为：

$$
p=d[i+1][(j\times 10+x)\bmod 2520][k\ \text{and}\ x = top][id[\mathrm {lcm}(id[x], l)]]\\

p\gets p+d[i][j][k][l];
$$

其中 $x$ 为当前枚举的数位，$top$ 是当前位的上界，$id$ 是 $2520$ 因子的离散化数组。

```c++
#include<bits/stdc++.h>
#define ULL long long 
using namespace std;
const int mod = 2520;
int id[3000];
ULL d[30][3000][2][50], LCM[50][50];
ULL fac[50] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 14, 15, 18, 20, 21, 24, 28, 30, 35, 36, 40, 42, 45, 56, 60, 63, 70, 72, 84, 90, 105, 120, 126, 140, 168, 180, 210, 252, 280, 315, 360, 420, 504, 630, 840, 1260, 2520};
ULL gcd(ULL x, ULL y){
	if(!y) return x;
	return gcd(y, x % y);
}
ULL lcm(ULL x, ULL y){
	return x / gcd(x, y) * y;
}
ULL Getans(ULL num){
	if(!num) return 1ll;
	memset(d, 0, sizeof(d));
	int a[30], b[30];
	int cnt = 0;
	while(num){
		b[++cnt] = num % 10;
		num /= 10;
	}
	for(int i = 1; i <= cnt; i++) a[i] = b[cnt-i+1];
	ULL ans = 0;
	d[0][0][1][1] = 1;
	for(int i = 0; i < cnt; i++)
		for(int j = 0; j < mod; j++)
			for(int k = 0; k <= 1; k++)
				for(int l = 1; l <= 48; l++)
					if(d[i][j][k][l]){
						int top = k ? a[i+1] : 9;
						for(int x = 0; x <= top; x++){
							d[i+1][(j*10+x)%mod][k && x == top][x ? id[LCM[l][id[x]]] : l] += d[i][j][k][l];
						}
					}
	for(int j = 1; j <= 48; j++){
		for(int i = 0; i < mod; i+=fac[j]){
			if(!(i % fac[j]))
				ans += d[cnt][i][1][j] + d[cnt][i][0][j];
		}
	}
	return ans;
}
inline ULL read(void){
	ULL num = 0, f = 1;
	char ch;
	while(!isdigit(ch=getchar())) if(ch == '-') f = -1;
	while(isdigit(ch)) num = num*10 + ch-'0', ch = getchar();
	return num * f;
}
int main()
{
	for(int i = 1; i <= 48; i++) id[fac[i]] = i;
	for(int i = 1; i <= 48; i++)
		for(int j = 1; j <= 48; j++)
			LCM[j][i] = LCM[i][j] = lcm(fac[i], fac[j]);
	int T = read();
	while(T--){
		ULL l = read(), r = read();
		printf("%lld\n", Getans(r) - Getans(l-1));
	}
	return 0;
}
```



---

## 作者：foreverlasting (赞：5)

[题面](https://www.luogu.org/problemnew/show/CF55D)

数位DP+状压。

首先，按照数位$DP$的基本套路，每个个位数的最小公倍数为2520，所以只用考虑模2520的情况。考虑一个$DP$。$dp[i][j][k]$表示当前是第$i$位，2~9的数的集合为$j$，模2520为$k$的方案数。然后，就是数位$DP$的基本套路解决这道题。

code:
```
//2018.10.22 by ljz
#include<bits/stdc++.h>
using namespace std;
#define res register LL
#define LL long long
#define inf 0x3f3f3f3f
#define eps 1e-15
inline LL read(){
    res s=0;
    bool w=0;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')w=1;ch=getchar();}
    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=getchar();
    return w?-s:s;
}
inline void _swap(res &x,res &y){
    x^=y^=x^=y;
}
inline LL _abs(const res &x){
    return x>0?x:-x;
}
inline LL _max(const res &x,const res &y){
    return x>y?x:y;
}
inline LL _min(const res &x,const res &y){
    return x<y?x:y;
}
const int kcz=2520;
const int N=19+10;
namespace MAIN{
	LL Q;
	inline LL get(const res &i,const res &S){
		return i<2?S:S|(1<<(i-2));
	}
	LL dp[N][256+10][kcz+10],a[N];
	LL DP(const res &dep,const res &S,const res &sum,const bool &flag){
		if(dep==0){
			for(res i=2;i<=9;i++)if(S&(1<<(i-2))&&sum%i)return 0;
			return 1;
		}
		if(!flag&&dp[dep][S][sum]>=0)return dp[dep][S][sum];
		res pos=flag?a[dep]:9,ret=0;
		for(res i=0;i<=pos;i++)ret+=DP(dep-1,get(i,S),(sum*10+i)%kcz,flag&(i==pos));
		if(!flag)dp[dep][S][sum]=ret;
		return ret;
	}
	inline LL solve(res x){
		res len=0;
		while(x)a[++len]=x%10,x/=10;
		return DP(len,0,0,1);
	}
	inline void MAIN(){
		Q=read();
		memset(dp,-1,sizeof(dp));
		while(Q--){
			res l=read(),r=read();
			printf("%lld\n",solve(r)-solve(l-1));
		}
	} 
}
int main(){
    MAIN::MAIN();
    return 0;
}
```

---

## 作者：icefake (赞：2)

首先看到数据范围，$9e18$，再看题面，很明显的数位DP。

## 需要注意的地方：
$0$ 可以整除所有数。。。
答案可能会大于 $18$ 位，所以 $int$ 存不下！！！

## 分析

然后我们先确定 $dp$ 数组的下标，显然是一个三维的数组 —— $dp[pos][rar][sta]$。

> 我们用 $pos$ 表示当前位数，$rar$ 压缩一个状态，当先数位上有哪些数字，用 $sta$ 来表示原数。

但很显然，直接存 $sta$ 是存不下的，于是我们想到了 $mod$，那么我们将**模数**设为什么好呢？—— $1~9$ 的 $lcm$ 也就是 $2520$。

于是我定义了 $dp[20][1024][2521]$，经过计算后发现，只要开 $int$ 就不会炸空间，于是我就很高兴的开了 $int$ 。。。

> “于是它飞快地 WA 掉了”—— 某dalao

后来发现了答案可能很大。。。看到题解区都是将 $2520$ 进行离散化，但我 ~~实在太弱了。。。没想到~~ 发现对于 $0$ 和 $1$ 都是可以不计入状态中的，因为任意一个数（非 $0$ ）都可以被它们整除。所以我们就可以将第二位的上限改为 $512$，大小变成了原来的 $\frac{1}{2}$ 我们就可以开 $long long$ 啦。 ~~```#define int long long```~~

然后我们确定 $dfs$ 中的形参，很显然就是 $pos，rar，sta，limit$，$limit$ 表示是否到达上限。至于前导零的判断，本题并不需要。

那么我们就有两种转移，当 $i \leq 1$ 时：（ $up$ 表示上限）
```cpp
tem += dfs(pos - 1, rar, (sta * 10 + i) % MOD, (i == up) && limit);
```
而当 $2 \leq i$ 时：（ ~~不会打 $ ~~latex~~ $ 的大于等于 QAQ~~
```cpp
tem += dfs(pos - 1, rar | (1 << (i - 2)), (sta * 10 + i) % MOD, (i == up) && limit);
```

## 下面放上代码（实测 $AC$
```cpp
#include<bits/stdc++.h>
#define int long long
#define inc(i) (++ (i))
#define dec(i) (-- (i))
#define Rep(i, a, b) for(register int i = (a) , i##Limit = (b) ; i <= i##Limit ; inc(i))
#define Dep(i, a, b) for(register int i = (a) , i##Limit = (b) ; i >= i##Limit ; dec(i))

using namespace std;

const int MOD = 2520;
int a, b, T;
int res[21], dp[20][512][2521];

int dfs(int pos, int rar, int sta, bool limit) {
	if(!pos) {
		int num = 1;
		while(rar) {
			inc(num);
			if(rar & 1 && sta % num != 0) return 0;
			rar >>= 1;
		}
		return 1;
	}
	if(dp[pos][rar][sta] != -1 && !limit) return dp[pos][rar][sta];
	int up, tem = 0;
	if(limit) up = res[pos];
	else up = 9;
	Rep(i,0,up) {
		if(i <= 1) tem += dfs(pos - 1, rar, (sta * 10 + i) % MOD, (i == up) && limit);
		else tem += dfs(pos - 1, rar | (1 << (i - 2)), (sta * 10 + i) % MOD, (i == up) && limit);
	}
	if(!limit) dp[pos][rar][sta] = tem;
	return tem;
}

int solve(int x) {
	int pos = 0;
	while(x) {
		res[inc(pos)] = x % 10;
		x /= 10; 
	}
	return dfs(pos, 0, 0, 1);
}

signed main()
{
	cin>>T;
	memset(dp, -1, sizeof(dp));
	while(T --) {
		cin>>a>>b;
		printf("%lld\n", solve(b) - solve(a - 1));
	}
	return 0;
}
```

---

## 作者：EricWay1024 (赞：1)

这题做了半天。美丽的数的定义是“可以被自己的所有非零数位整除的数”。做数位DP，想的就是每个状态需要什么参量来表示。注意到这个定义的限制并不在选取每个数位的时候，而是在整个数字选完之后才能做一个整体判断。

很自然地，首先想到需要知道我们已经在$2, 3, \dots, 9$中选了哪些数字，这可以用一个$7$位二进制数来表示。这个想法虽然正确，但在本题中时间效率不够。能够观察到，假如我们选了$9$而没有选$3$，这种情况在最后需要的判断，和既选了$9$也选了$3$是等价的。这不免让我们意识到，可以拿我们已选的所有数位在$2, 3, 5, 7$的最高次幂分别作为一个状态参量，它一共有$4\times3\times2\times2=48$种可能取值，比一个$7$位二进制数来得小很多。这样做其实是可以的，但写起来稍微麻烦一点。我们依然可以更进一步：能够被我们的所有数位整除，就等价于能够被我们的所有数位的最小公倍数整除。虽然这个最小公倍数最大能达到$2520$，但根据刚才的论述，它只有$48$个可能的取值，对应的是$2520$的所有因数，简单离散化即可。

我们需要判断的是整个数能否被所有数位的最小公倍数整除。最理想的做法是记录状态参量包括“每一步选完后的数前缀”模“我们所选的所有数位的最小公倍数”的值。但这是不可能的，因为在选取的每一步，我们无法预知后面的步骤会选择什么，也就无法预知这个最小公倍数是几。但所幸其实只要是这个最小公倍数的倍数作为模数，我们都可以用余数来判断原数对最小公倍数的整除性。因此最后我们选取的模数相等于是“所有最小公倍数的最小公倍数”，不难发现这个虚张声势的说法等价于$2, 3, \dots, 9$的最小公倍数$2520$。

理论上这道题就做完了。但是我又被卡时间了。这时候我意识到数位DP未必非要走套路：先求小于等于$n$的“满足条件的数”，再拿区间两个端点求出的值减一下——其实可以搜索的时候同时卡两个端点，然后一遍就搜完了。做法就是不仅记录“已选择的所有数中是否均和右端点对应数位相等”，也记录“已选择的所有数中是否均和左端点对应数位相等”，这两个状态分别影响每一步能选择的数的上界和下界。这么做的好处在于，由此搜索的复杂度就只和区间长度有关，和左右端点数的大小本身无关了。换言之，对于原先左右端点都很大、但区间长度未必大的数据，这样做显然能缩短运行时间；对于其他数据，也不会明显劣于之前的算法（未严格证明）。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define rep(i,from,to) for(register int i=(int)from;i<=(int)to;++i)
#define For(i,to) for(register int i=0;i<(int)to;++i)
typedef long long ll;
inline ll read(){
    ll x=0; ll sign=1; char c=getchar();
    while(c>'9' || c<'0') {if (c=='-') sign=-1;c=getchar();}
    while(c>='0' && c<='9'){x=(x<<3)+(x<<1)+c-'0';c=getchar();}
    return x*sign;
}
const ll M = 2520;

ll l, r;
ll f[20][50][2521];
int fac[2521];
int dim_l[25]; int dim_l_size;
int dim_r[25]; int dim_r_size;

int gcd(int a, int b){ return b ? gcd(b, a % b) : a; }
inline int lcm(int a, int b) { return a / gcd(a, b) * b;}

ll dp(int x, int scm, int st, int opl, int opr) {
    if (x == -1) { return (st % scm) == 0; }
    ll &mem = f[x][fac[scm]][st];
    if (!opl && !opr && mem > -1) return mem;
    ll ret = 0;
    int maxx = opr ? dim_r[x] : 9;
    int minx = opl ? dim_l[x] : 0;
    rep(i, minx, maxx) {
        ret += dp(x - 1, (i == 0) ? scm : lcm(i, scm), ((st * 10 + i) % M), 
            (opl & (i == minx)), (opr & (i == maxx)));
    }
    if(!opl && !opr) mem = ret;
    return ret;
}

inline void cal_dim(ll n, int* dim, int &dim_size) {
    dim_size = 0;
    while(n) {
        dim[dim_size++] = n % 10; n /= 10;
    }
}

ll solve(ll l, ll r) {
    memset(dim_l, 0, sizeof(dim_l));
    memset(dim_r, 0, sizeof(dim_r));
    cal_dim(l, dim_l, dim_l_size);
    cal_dim(r, dim_r, dim_r_size);
    memset(f, -1, sizeof(f));
    return dp(dim_r_size-1, 1, 0, 1, 1);
}

int main() {
#ifdef D
    freopen("CF55D.in", "r", stdin);
    double TIMEA = clock();
#endif

    int cnt = 0;
    for(int i = 1; i <= M; ++i) {
        if (M % i == 0) fac[i] = ++cnt;
    }

    int T; T = read();
    while(T--) {
        l = read(); r = read();
        ll ans = solve(l, r);
        cout << ans << "\n";
    }

#ifdef D
    double TIMEB=clock();
    printf("\n# Time consumed: %.3fs.\n", (TIMEB-TIMEA)/1000);
#endif
    return 0;
}
```





---

## 作者：YuanZhizheng (赞：1)

兜兜转转总算过了这题。

先来看题，就是给你一个范围[l,r]，求这个范围中有多少个数字能满足这个数字能整除每个数位的数字。

比如12,12%2=0,12%1=0，所以12就是满足题目条件的。而13%1=0,13%3!=0，这就不符合。

求某个范围内的满足某些条件的数字一共有多少个，解决这类问题常用的解法就是数位dp。对于大部分数位dp题，套路也大多是这个。

下面，我就从数位dp的惯常套路入手。

```
ll Solve(ll x)//数位分解
{

    tot=0;
    while(x)
    {
        a[++tot]=x%10;
        x/=10;
    }
    return dfs(tot,1,1,0);
}
int main()//主函数
{
    memset(dp,-1,sizeof(dp));
    int t;
    cin>>t;
    lsh();
    while(t--)
    {
        ll l,r;
        cin>>l>>r;
        cout<<Solve(r)-Solve(l-1)<<'\n';
    }
    return 0;
}
```
先上一下主函数和Solve函数，数位分解和主函数这么写的都是必备的，有稍微学习过数位dp都能明白。

然后就是写dfs和开dp数组了，记忆化搜索就是数位dp的精髓，也可以说是优化的暴力。dp数组也就是记忆已经搜索过并且是“通用的状态”，保证不会重复搜索到，从而达到降低时间复杂度的做法。

我们再回头看看题目。

我们知道dp数组是保存状态的。初看题目，我们要什么呢？很显然是位置pos、数字x、还有其每一位数位上的数字。

首先数位有很多，我们不可能开太多维的数组，所以我们**只保存最小公倍数，如果这个数字可以除以每一数位的数字，那么一定能除以数位这些数字的最小公倍数**。

我们可以知道，1——9所有数字的最大的最小公倍数是2520。那么我们可以用x%2520，来保存数字x，所以保存数字的维度开2521左右即可。

这个时候，还差一个维度保存最小公倍数就完成了，但是这个数组维度不可能再开到2520以上了，因为dp[20][2521][2521]这样的数组一定会MLE的，这个时候我们就可以采用离散化，使得每一个最小公倍数对应1、2、3......n的编号。用in数组保存。

```
void lsh()//离散化，每一个最小公倍数对应一个编号
{
    ll i;
    tot=0;
    for(i=1; i<=2520; i++)
    {
        if(2520%i==0)
            in[i]=tot++;
    }
}
```

进行完函数之后，可以发现tot不过就48而已，也就是48个数字，那么离散化之后，第三维只用开50+即可。

当然，计算最小公倍数还需要一个**a*b/gcd(a,b)**这样的公式，这个是很容易的，就不多说了。

再重复一次，数位dp很多地方都是套路，这题只要能想到离散化就差不多能解决了！

下面是AC代码。

```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int in[2521];
ll dp[20][2521][49];
int a[20];
int tot;
void lsh()//离散化，每一个最小公倍数对应一个编号
{
    int i;
    tot=0;
    for(i=1; i<=2520; i++)
    {
        if(2520%i==0)
            in[i]=tot++;
    }
}
inline ll read()
{
    ll x=0,f=1;
    char c=getchar();
    for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
    for(;isdigit(c);c=getchar())x=x*10+c-'0';
    return x*f;
}
int gcd(int a,int b)//最小公因数
{
    return a%b==0?b:gcd(b,a%b);
}
ll dfs(int pos,bool f,int lcm,int x)
{
    if(pos==0)
        return !(x%lcm)?1:0;
    if(!f&&dp[pos][x][in[lcm]]!=-1)
        return dp[pos][x][in[lcm]];
    int up=f?a[pos]:9;
    ll ans=0;
    //以上都是套路
    for(int i=0; i<=up; i++)
    {
        if(i)
            ans+=dfs(pos-1,f&(i==up),i/gcd(lcm,i)*lcm,(x*10+i)%2520);//保存最小公倍数即可
        else
            ans+=dfs(pos-1,f&(i==up),lcm,(x*10+i)%2520);
    }
    if(f)
        return ans;
    else
        return dp[pos][x][in[lcm]]=ans;
}
ll Solve(ll x)
{
    tot=0;
    while(x)
    {
        a[++tot]=x%10;
        x/=10;
    }
    return dfs(tot,1,1,0);
}
int main()
{
    memset(dp,-1,sizeof(dp));
    int t;
    scanf("%d",&t);
    lsh();
    while(t--)
    {
        ll l,r;
        l=read();
        r=read();
        printf("%lld\n",Solve(r)-Solve(l-1));
    }
    return 0;
}

```
题目建议使用cin了（我不懂为什么），快读是可以的，这题数据也不是很多，直接莽cin、cout也行。这题cin、cout也不过是1s跑完，这题开的时间还是很够的，算法大致思路对了，很多细节没有优化依然可以轻松过。



---

## 作者：pomelo_nene (赞：0)

我们发现数位上只会有 $0,1,\cdots ,9$ 这些数字。这么小，有没有什么用呢？

而 $\operatorname{lcm}(1,2,\dots ,9)=2520$，也就是说所有可能要求一个数整除的数都是 $2520$ 的因子。于是我们就处理完 $2520$ 的因子，这又有什么用呢？

暂先抛开上面的思考。考虑数位 dp。定义 $dp_{i,j,k}$ 为当前填到第 $i$ 位，产生的数为 $j$，当前应该整除的数为 $k$。产生的数是 $9 \times 10^{18}$ 级别的，考虑一个方法去模掉它。

定理：若 $a \equiv 0(\bmod \ s),a\equiv 0(\bmod \ t)$，那么 $a \equiv 0(\bmod \ \operatorname{lcm}(s,t))$。

显然。

所以说我们将一般模数定成 $2520$，然后 $sum$ 向其取模即可。

空间复杂度 $O(20 \times 2520 \times 2520)$。。。炸了。

于是将因子离散化，只有 $50$ 多个，然后就能优化空间了。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
LL a[21],n,lsh[2521],dp[21][2521][51];
LL gcd(LL a,LL b){return !b?a:gcd(b,a%b);}
LL lcm(LL a,LL b){return a/gcd(a,b)*b;}
LL DP(LL pos,LL limit,LL sum,LL mod)
{
	if(!pos)	return sum%mod==0;
	if(!limit && ~dp[pos][sum][lsh[mod]])	return dp[pos][sum][lsh[mod]];
	LL up=limit?a[pos]:9,ans=0;
	for(LL i=0;i<=up;++i)	ans+=DP(pos-1,limit && i==up,(sum*10+i)%2520,i?lcm(i,mod):mod);
	if(!limit)	dp[pos][sum][lsh[mod]]=ans;
	return ans;
}
LL calc(LL up)
{
	n=0;
	while(up)	a[++n]=up%10,up/=10;
	return DP(n,1,0,1);
}
int main(){
	memset(dp,-1,sizeof dp);
	LL s=0;
	for(LL i=1;i<=2520;++i)	if(2520%i==0)	lsh[i]=++s;
	LL T;
	scanf("%lld",&T);
	while(T-->0)
	{
		LL l,r;
		scanf("%lld %lld",&l,&r);
		printf("%lld\n",calc(r)-calc(l-1));
	}
	return 0;
}
```

---

## 作者：Su_Zipei (赞：0)

## 分析
看到这道题的时候我想到的是状压DP，压一下0~9是否出现过，但发现之后就不好弄了，因为它不仅可能出现，而且还会出现很多次，看数据范围就知道暴力肯定不可能的，这数据大小就算跑一遍循环也能T掉，所以这里就要用到数位DP了。

状压DP是用一个十进制数来表示二进制的状态，本质上还是暴力，不过是优化了。**常用到位运算**

数位DP跟它也差不多，算是一种暴力，主要用来解决数位上计数的问题，比如本题。**主要是通过记忆化搜索来实现**

因为查询时查询一个区间很不方便，所以将他拆成两个区间相减的形式，这个地方应该不难看出来。

接下来就是数位DP的内容了，先考虑最原始的版本，因为我要一位一位的去考虑，所以位数占了一维，又因为要判断是否是这什么什么$Numbers$，所以位数所表示的十进制数也要存下来，那么怎么判断是不是这种数字呢？最坏的情况是含了0到9的所有数字，既然每个数字都能整除，那么必定可以整除它们的最小公倍数，所以公倍数也要占一维，于是定义$dp_{i,j,k}$为还剩下$i$位，并且前$i$位表示的数为$j$，这$i$位数字的最小公倍数为$k$时的
答案是多少，这里解释一下$i$这一维，比如123456，前三位分别是1，2，3，表示的数即为123，然后就能通过枚举得到$dp_{i,j,k}=\sum_{i=0}^{Max}dp_{i-1,j*10+i,lcm(k,i)}$,lcm表示的就是最小公倍数，这个应该也能看懂，他其实就是暴力的枚举了每
一位上的数字。

这个数组开了之后肯定会MLE，考虑一下优化，1~9的最小公倍数为$5*7*8*9==2520$，也就是说第三维的状态不可能比2520还要大，但开2520还是会MLE，继续思考，1到2520很多数字我们都是用不到的，我们用到的实际上只有2520的因数，所以可以提前预处理出来，然后把第三维的状态改成最小公倍数对应的数字为$k$，相当于一个离散化。

最棘手的东西还是中间这一维，直接记录的话会发现它最大$9*10^{18}$次方，那么有没有什么好的办法来压一下这个大小呢？先思考一下，我们最后判断的是什么，就是这个数$mod$它每个位数字上的最小公倍数是否==0，设这个数为$x$，最小公倍数为$lcm$，因为涉及到$mod$，所以从同余的角度来考虑。

引理:如果$a$是$b$的因子，那么$x$同余$x$%$b(mod$ $a)$

证明:因为$a$是$b$的因子，所以可以设$b=na,n$是正整数

不妨设$x=qb+r,r=0,1,2....b-1$

所以$x \equiv x-qna$               $(mod$ $a)$

即$x\equiv x-qb$                  $(mod$ $a)$

$x-qb$即为$r$又因为$r$是$x$%$b$       $(mod$ $a)$

所以$x \equiv x$%$b$ $(mod$ $a)$

有了这个引理，就好办多了，所有的lcm都一定是2520的因子，所以$x \equiv x$%$2520$ $(mod$ $lcm)$
也就是说，$x$与$x$%$2520$实际上是等价的，那为什么我们不把它%一下，于是第二维也就只需要开2520，空间问题就解决了，加上之前的一些分析，这个问题基本解决。

##细节

1.记忆化

反正都搜过了，不记白不记。但是记录的时候要注意，因为枚举每个位置的时候，不能超过这个数原本的值，超过了就会多记答案，所以当当前位是最大值的时候，不能记忆，同理返回值时也是。比如113，枚举百位时显然不能枚举到2，但当百位是0时，十位却能够到9，所以判断最大值时要保证每一位都是最大值。

2.longlong

这题不开longlong等着WA吧。

3.最大公约数和最小公倍数
最大公约数我用的辗转相除法，原理挺简单，就一直除，直到可以除尽为止。
最小公倍数就是两数的乘积除以最大公约数，这个就根据最小公倍数的定义自行理解吧
```
#include<iostream>
#define ll long long
using namespace std;
const int N=2525;
ll dp[20][N][50];
int p[N],hh,num[20],top;
int gcd(int a,int b){
    return a%b?gcd(b,a%b):b;
}
int Lcm(int a,int b){
    return b==0?a:a/gcd(a,b)*b;
}
ll dfs(int x,int sum,int lcm,bool ismx){
    if(x==0)return sum%lcm==0;
    if(!ismx&&dp[x][sum][p[lcm]])return dp[x][sum][p[lcm]];
    int Max=ismx==1?num[x]:9;
    ll ans=0;
    for(int i=0;i<=Max;i++)
        ans+=dfs(x-1,(sum*10+i)%2520,Lcm(lcm,i),ismx&&i==Max);
    if(!ismx)dp[x][sum][p[lcm]]=ans;
    return ans;
}
ll calc(ll x){
    top=0;
    while(x){
        num[++top]=x%10ll;
        x/=10ll;
    }
    return dfs(top,0,1,1);
}
int main(){
    for(int i=1;i<=2520;i++)
        if(2520%i==0)p[i]=++hh;
    int t;
    cin>>t;
    while(t--){
        ll l,r;
        cin>>l>>r;
        cout<<calc(r)-calc(l-1)<<'\n';
    }
}
```

---

## 作者：zhangyuxing (赞：0)

显然数位dp。

首先，整除每一位等同于整除lcm，所以我们考虑记录lcm。

数组显然会出大问题。

前置：$lcm(1,2,3,4,5,6,7,8,9)=2520$

所以我们考虑用%2520的余数来表示数字，这样不会改变数字整除性。

然后考虑优化lcm，我们发现很多情况其实是不可能为lcm（例如大于9的质数，$2^k(k>3)$)，然后就记录一下编号与数的对应关系(code中的map,remap)。

然后可过。
___
注意：本题可以不记录前导0，因为我们要排除0计算lcm，**0已经被排除了**.
___
code:
```cpp
#include<cstdio>
#include<cctype>
#include<cstring>
#define ll long long
using namespace std;
void read(ll &x)
{
	int flag=1;
	x=0;
	char c=getchar();
	while(!isdigit(c))
	{
		if(c=='-')flag=-1;
		c=getchar();
	}
	while(isdigit(c))
	{
		x=(x<<3)+(x<<1)+c-'0';
		c=getchar();
	}
	x*=flag;
}
int gcd(int a,int b){return !b?a:gcd(b,a%b);}
int lcm(int a,int b){return a/gcd(a,b)*b;}
int map[2521],remap[2521],cnt,num[25];
ll f[25][2521][55];
ll dfs(int now,int temp,int product,bool limits)
{
	if(!now)return temp%product==0;
	if(!limits&&~f[now][temp][remap[product]])return f[now][temp][remap[product]];
	ll ret=0;
	int maxn=limits?num[now]:9,i;
	for(i=0;i<=maxn;++i)ret+=dfs(now-1,(temp*10+i)%2520,i?lcm(i,product):product,limits&&i==maxn);
	return limits?ret:f[now][temp][remap[product]]=ret;
}
ll solve(ll x)
{
	int dig;
	for(dig=0;x;x/=10)num[++dig]=x%10;
	return dfs(dig,0,1,1);
}
void prepare()
{
	memset(f,-1,sizeof f);
	int i;
	for(i=1;i<=2520;++i)
	if(2520%i==0)
	{
		map[++cnt]=i;
		remap[i]=cnt;
	}
}
int main()
{
	prepare();
	ll t,l,r;
	read(t);
	while(t--)
	{
		read(l);read(r);
		printf("%lld\n",solve(r)-solve(l-1));
	}
	return 0;
}
```

---

