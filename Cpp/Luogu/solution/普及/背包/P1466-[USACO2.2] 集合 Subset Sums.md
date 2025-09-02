# [USACO2.2] 集合 Subset Sums

## 题目描述

对于从 $1\sim n$ 的连续整数集合，能划分成两个子集合，且保证每个集合的数字和是相等的。举个例子，如果 $n=3$，对于 $\{1,2,3\}$ 能划分成两个子集合，每个子集合的所有数字和是相等的：

$\{3\}$ 和 $\{1,2\}$ 是唯一一种分法（交换集合位置被认为是同一种划分方案，因此不会增加划分方案总数）  
如果 $n=7$，有四种方法能划分集合 $\{1,2,3,4,5,6,7 \}$，每一种分法的子集合各数字和是相等的:

$\{1,6,7\}$ 和 $\{2,3,4,5\}$  
$\{2,5,7\}$ 和 $\{1,3,4,6\}$  
$\{3,4,7\}$ 和 $\{1,2,5,6\}$  
$\{1,2,4,7\}$ 和 $\{3,5,6\}$  

给出 $n$，你的程序应该输出划分方案总数。

## 说明/提示

【数据范围】  
对于 $100\%$ 的数据，$1\le n \le 39$。

翻译来自NOCOW

USACO 2.2


## 样例 #1

### 输入

```
7
```

### 输出

```
4
```

# 题解

## 作者：Makasukaka (赞：48)

# Meet-in-the-middle
看到大家都在写dp，可我看到n<=39的数据范围想到的是meet-in-the-middle 这个小技巧。

大家都知道，爆搜子集排列是O(2^N)的，而O(2^N)的时间复杂度在OI中一般跑N=20是没有问题的。

我们先把无解的情况判了，只要找到合为sum/2的种类数即可，另外一种都是一一对应的。

我们不妨把40个数分成左右两边，考虑到选取若干个数时最后一定是左右两边各取若干。那我们可以对左右两边分别枚举子集，用一个数组把其中一边的组合值存起来，记作b[M]。那么我们只需要在另外一边枚举的时候，ans+=b[sum/2-cur]即可(cur指的是另外一边枚举的当前和)。

时间复杂度O(2^(N/2))

附上代码
```cpp
#include<cstdio>
typedef long long LL;
const int M=1e3+5;
LL b[M];
int n;
LL ans;
int main(){
    scanf("%d",&n);
    if(((1+n)*n/2)&1)puts("0");
    else{
        for(int i=0;i<(1<<(n/2));++i){
            int cur=0;
            for(int j=0;(i>>j)>0;++j)if((i>>j)&1)cur+=(j+1);
            b[cur]++;
        }
        for(int i=0;i<(1<<(n-n/2));++i){
            int cur=0;
            for(int j=0;(i>>j)>0;++j)if((i>>j)&1)cur+=j+n/2+1;
            if((1+n)*n/4>=cur)
            ans+=b[(1+n)*n/4-cur];
        }
        printf("%lld\n",ans/2);
    }
    return 0;
}

```

---

## 作者：Qutam (赞：39)

这题是一个背包板子。

对于只选前$i$项的数，它们的和正好是$j$的方案总数，我们可以这样想，先考虑第$i$个数选不选。所以方案总数就应该是选的方案和不选的方案之和。

状态转移方程为：
$$
dp[i][j]=dp[i-1][j]+dp[i-1][j-a[i]]
$$

需要注意，有解的前提必须是数字之和是偶数。
## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[40],dp[45][2010];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		a[i]=i;
	dp[0][0]=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n*(n+1)/2;j++){
			dp[i][j]=dp[i-1][j];
			if(j>=a[i])dp[i][j]+=dp[i-1][j-a[i]];
		}
	if(n*(n+1)%4==0)cout<<dp[n][n*(n+1)/4]<<endl;
	else cout<<0<<endl;
	return 0;
}
```

---

## 作者：「QQ红包」 (赞：35)

题解by:redbag

原题解地址：http://redbag.duapp.com/?p=1197

n个数的总和为sum:=n\*(n+1)shr 1,当且仅当sum为偶数的时候才有解，sum为奇数时直接输出0并且退出程序；然后每个数只有2种情况，放在第一个集合和不放在第一个集合。于是就是简单的01背包问题了。简单的分析见图

[图](http://redbag.duapp.com/wp-content/uploads/3.bmp)）

代码：

```cpp
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
int sum/*1~n的和*/,n;
int f[40][800];
int i,j;
int main() 
{
    freopen("subset.in","r",stdin);
    freopen("subset.out","w",stdout); 
    scanf("%d",&n);
    sum=(n*(n+1))/2;//算出1~n的和。
    if (sum%2==1)//仅当sum为偶数的时候才有解 
    {
        printf("0\n");//因为分成的2份和要相等 
        return 0;
    } 
    f[1][1]=1;//1中取任意个数的数使和为1的情况
    f[1][0]=1;//1中取任意个数的数使和为0的情况 
    for (i=2;i<=n;i++)//1的情况已经算完了，所以从2开始 
    {
        for (j=0;j<=sum;j++)
        {
            if (j>i)//有取这个数和不取两种情况 
                f[i][j]=f[i-1][j]+f[i-1][j-i];
                else f[i][j]=f[i-1][j];//只能不取了
        }
    }
    printf("%d\n",f[n][sum/2]); 
    return 0;
}

```

---

## 作者：courage (赞：31)

01背包


先判断s=1+2+3+……+n的奇偶性，为奇数直接输出0,。然后就是01背包判断凑成s/2的方案数了，注意输出时要除以2。


f[i][j]表示前i个数凑成j的方案数，边界f[0][0]=1，状态转移方程f[i][j]=f[i-1][j]+f[i-1][j-i]。另外可以压缩成一维数组，不过循环顺序就必须是倒序了


还有n=39时方案数大于maxlongint（除以2之后小于maxlongint）


```cpp

#include<cstdio>
int n,s;
long long f[400]={0};
int main(){
    scanf("%d",&n);
    s=n*(n+1)/2;
    if (s&1){
        printf("0");
        return 0;
    }
    s/=2;
    f[0]=1;
    for (int i=1;i<=n;i++)
        for (int j=s;j>=i;j--)
            f[j]+=f[j-i];
    printf("%d\n",(long long)f[s]/2);
}

```

---

## 作者：CalcMaster (赞：12)

~~为了彻底弄懂这道题,还是来水一发题解~~

题意：从 1->n 中选任意个数,使得其和为这列数总和的$1/2$.（稍稍加以变通）

**令$m=n*(n+1)/2;$**

**$m/=2;$**

那么 m 即为要求的答案


背包+dp.

### 特判：
由于是分成总和的 $1/2$ ,如果总和的  $1/2$ 不是偶数的话,那么就肯定分不出来.直接输出0.

### 设计状态：
dp[i][j]表示已经处理了1到i,其总和为j的情况总数.那么有状态转移方程：dp[i][j] += dp[i-1][j-i];

### 优化状态：
由于dp[i][j]的答案只与dp[i-1][j-i]有关,而且在循环的时候我们可以直接从小到大循环.求完 dp[i-1][...] 后就求 dp[i][...] .所以可以把第一维去掉.那么 dp[j] 就表示从1-n这些数中任取一些数使其和为 j 的方案数。

我们从小到大循环，这样确保求 dp[j] 时 dp[j-i] 是有答案的.




```cpp
for(int i=1;i<=n;i++)
    {
        for(int j=m;j>=i;j--)
        {
            dp[j]+=dp[j-i];
        }
    }
```

### dp循环详解：
第一层从 1->n 的循环：枚举第i个数 (其值正好就是i) 加入集合.
第二层从 m->i 的循环：如果第i个数加入集合，那么和最小为 i ,最大（在题意范围内）为 m .那么要使和为 j ，答案即为 dp[j-i] 的答案 +1 .


```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
ll n,m;
ll dp[10009];//dp[i]表示在n个数中去任意个数使其和为i的方案总数
int main()
{
    scanf("%lld",&n);
    m=(n+1)*n/2;
    if(m%2==1)
    {
        printf("0\n");
        return 0;
    }
    m/=2;
    dp[0]=1;
    for(int i=1;i<=n;i++)
    {
        for(int j=m;j>=i;j--)
        {
            dp[j]+=dp[j-i];
        }
    }
    printf("%lld\n",dp[m]/2);
    return 0;
}
```



---

## 作者：万弘 (赞：9)

貌似是叫一个什么**恰好背包**，也许也是背包的一种吧

设$f[x][v]$为在决断第x件物品时体积剩余v的方案数  
$a[x]$为第x件物品的体积

边界：$f[x][0]=1(1<=x<=n),f[x][v]=0(x>n||v<0)$

转移方程： 
$$f[x][v]=f[x+1][v]+f[x+1][v-a[x]]$$

我用记搜实现：空间和时间都是$O(nv)=O(n^3)$
```cpp
ll dfs(ll x,ll v)
{
	if(v==0)return f[x][v]=1;
	if(x>n||v<0)return f[x][v]=0;
	if(f[x][v])return f[x][v];
	
	ll res=dfs(x+1,v);
	if(v>=x)res+=dfs(x+1,v-x);//本题的特殊性，不需要a[x]
	return f[x][v]=res;
}
```
还有，要先求一下sum，如果是奇数，一定没有方法
```cpp
sum=((n+1)*n)>>1;//暴力加也可
if(sum&1)printf("0");
else
{
	printf("%lld",dfs(1,sum>>1)>>1);
}
```

---

## 作者：江山_远方 (赞：9)

一道裸的背包方案数问题

需要注意两个点

1.需要特判:如果1~n之和为奇数，那么方案数即为0

2.要开long long:本蒟蒻不开long long 错过一个点 调了半天没出来（汗）

上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
long long f[100];
int main()
{
	cin>>n;
	f[0]=1;
	if(((1+n)*n/2)%2==1)
	{
		cout<<0;
		return 0;
	}//特判
	for(int i=1;i<=n;i++)
	  for(int j=(1+n)*n/2/2;j>=i;j--)f[j]+=f[j-i];//背包方案数
	cout<<f[(1+n)*n/2/2]/2;//最后输出要/2,否则会因顺序原因重复计算
	return 0;
}
```


---

## 作者：Mr_QwQ (赞：6)

本题正解dp。但是这里我用暴力解决了问题。

楼下的神犇说直接枚举不行。确实不行，$2^39$的复杂度太太太太太太大了。

所以我们需要一些“奇技淫巧”来枚举。

很显然，必须有1+2+3+...+n mod 4=0才能平分。

首先我们把集合分成1,2,3...n/2与n/2+1,n/2+2...n的两块。

然后我们就要在这两块之中分别挖出一块，使得这两块的和是(1+2+3+...+n)/4。

又因为这个值的范围很小，我们可以先在前一块中枚举所有的集合，并存下来前一块得出每一种和的方案数，然后枚举后一块所有集合并在前一块查找对应的值，最后相加就没了。就没了。

总而言之就是道双搜的模板题。再看看复杂度，时间复杂度$O(2^20)$，恩，好了很多哦，可以过了。

代码：

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
int s,n;
long long p[1600];
void dfs(int cur,int imax,int isum)
{
    if(cur>imax){
        ++p[isum];
        return;
    }
    dfs(cur+1,imax,isum);
    dfs(cur+1,imax,isum+cur);
}
long long dfs2(int cur,int imax,int isum)
{
    if(cur>imax)
    {
        if(s>=isum)return p[s-isum];
        return 0;
    }
    return dfs2(cur+1,imax,isum)+dfs2(cur+1,imax,isum+cur);
}
int main()
{
    scanf("%d",&n);
    if((n*(n+1)/2)&1){
        printf("0");
        return 0;
    }
    s=n*(n+1)/4;
    dfs(1,n/2,0);
    cout<<dfs2(n/2+1,n,0)/2;
    return 0;
}
```

---

## 作者：Lolierl (赞：4)

看见这题的第一感觉是深搜递归。dfs(i,j,step)表示当看前step个数时，第一个和为i，第二个和为j时的方案。

```cpp
#include<iostream>
#include<cmath>
using namespace std;

int n,s;
inline int dfs(int s1,int s2,int step)//意思如上。 
{
    if(step==0)//我用的是step从n到0可以多a一个点 
    {
        if(s1==s2)//当深搜到结束时判断，如果两数相等就返回1否则返回0。 
            return 1;
        else 
            return 0;
    }
    if(s1>s/2||s2>s/2)return 0;//剪枝，如果当前已经不符合要求就直接返回 
    return dfs(s1+step,s2,step-1)+dfs(s1,s2+step,step-1);//深搜扩展，当前数（step）尝试放进第一个集合和第二个集合，同时step-1看到下一个数，并返回结果。 
}
int main()
{
    ios::sync_with_stdio(false);
    cin>>n;
    s=n*(n+1)>>1;//1+2+···+n的和，每个集合的和便应该是s/2 
    if(s%2==1)//如果是奇数明显不可行，输出0。 
        cout<<0;
    else
        cout<<(dfs(0,0,n)>>1);//从n看起，输出方案数，注意每个方案被颠倒算了2遍，要除以2。 
    return 0;
}
```
这段代码无论怎么优化都是80分。那么，怎么全过呢？

我们知道递归之所以慢是因为调用了系统栈。那么，我们来试一试递归变递推。

用a[i][j]表示第一个集合和为i、第二个集合和为j的情况。先在外面一层循环枚举1-n（模拟系统栈），再对每一个数枚举i和j，通过递推迭代可以用o(n\*s/2\*s/2)=o(n^5)的复杂度解决问题。

然而我们发现，对于每一个i和j，都有i+j=s，不然这就是一个无用状态，可以舍去。于是我们可以消去一维，只枚举一维即可。

以下为全A代码:

```cpp
#include<iostream>
#include<cstring>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int n;
    cin>>n;
    int s=(n*(n+1))>>1;
    if(s%2==1){cout<<0;return 0;}//和之前完全一样，就不解释了 
    
    long long a[s/2+1];//枚举i，注意要开ll 
    memset(a,0,sizeof(a));
    a[0]=1;//这里一定要写，不然全是0 
    for(int i=1;i<=n;i++)
        for(int j=s/2;j>=i;j--)
            a[j]+=a[j-i];//对于每个数，都对每一个状态产生了影响。在第一个集合和为j的方案数中，要加上和为j-i的方案数。由于i是有序并且j是倒序的，所以不会重复。 
    cout<<(a[s/2]>>1);//输出（注意还是要除以2） 
    return 0;
} 
//类似01背包的代码，不过我是用递归变递推的思想AC本题的。 
```

---

## 作者：傅思维666 (赞：3)

动归。

最终可以转化成背包问题。为什么呢？

因为题目中让你把集合中元素分成两个权值相等的部分，也就是说元素和相加除以2就是背包容量，我们的状态f[i][j]就设置为第i个元素装满容量为j的背包的方案数目。

好了，现在这个题目就变成了01背包问题。

只不过是求方案罢了。

我看到大家有很多写数组压缩的，但是我~~不会~~（逃

先上代码，再强调一下细节。
```cpp
#include<cstdio>
using namespace std;
int n,t,f[40][1000];
int main()
{
    scanf("%d",&n);
    t=(n+1)*n/2;
    if(t%2)
    {
        printf("0");
        return 0;
    }
    else 
        t/=2;
    f[1][1]=1;
    for(int i=2;i<=n;i++)
        for(int j=0;j<=t;j++)
        {
            if(j>i)
                f[i][j]=f[i-1][j]+f[i-1][j-i];
            else
                f[i][j]=f[i-1][j];
        }
    printf("%d",f[n][t]);
    return 0;
}
```
首先要判断当前集合的元素和能否被2整除，不能的话还玩个头。

然后要设定初值，f[1][1]=1，我想不用多说。

PS;有人也把f[1][0]设置为0了，我本人不是很理解，事实证明删去也毫无问题。

然后开始DP，注意t要除以2。

我们在每次状态转移之前要先加判断，如果可用空间比当前元素要大的话才可以把选和不选两种可能加到一起，否则就只能不选。

选和不选的问题或者这段代码看不懂的请自行补习01背包。

然后这道题就可以AC 了。

---

## 作者：ylsoi (赞：2)

我已开始用搜索求全组合，然后就炸了，看了一下标签才发现这是DP的题目，突然就想的了背包，我们可以把每一个集合里数字的和定义为背包的体积，然后我们就可以求背包问题的方案总数，也就是在空间为v的状态下填满的方案总数，状态转移方程为f[j]=f[j]+f[j-i](滚动数组，详情见背包问题，其中j为枚举的空间，i为在前i个数中选择)，边界f[0]=1，因为一个都不选但是要选满背包的话只有0体积的时候是符合要求的。

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
using namespace std;
const int maxn=10000;//这里最好开大一点，虽然也不要这么大，但是开39是绝对不够的；
int n,t;
long long f[maxn];//一定要开longlong
int main()
{
    scanf("%d",&n);
    t=(n+1)*n/2;
    if(t%2)
    {
        printf("%d\n",0);
        return 0;
    }
    else t/=2;
    f[0]=1;
    for(int i=1;i<=n;i++)
        for(int j=t;j>=i;j--)
            f[j]=f[j]+f[j-i];
    printf("%lld\n",f[t]/2);
    return 0;
}
```

---

## 作者：Shan＿Xian (赞：1)

 
 
 
```cpp
#include<iostream>
#include<fstream>
#include<memory.h>
using namespace std;
long long c1[395],c2[395];
int c3[2];
int main()
{
    freopen("subset.in","r",stdin);
    freopen("subset.out","w",stdout);
    int n;
    cin >>n;
    int Sum = (n*(n+1))/2;
    if(Sum%2){ //和为奇数即不可能分成相等的两堆
        cout <<'0' <<endl;
        return 0;
    }
    int HalfSum = Sum/2;
    memset(c1,0,sizeof(c1));
    c1[0] = c1[1] = 1; //第一个表达式（1+x）
    for(int i = 2;i <= n;i++){// n个表达式中的第i个表达式
        c3[0] = 0; c3[1] = i;  //初始化第i个表达式
        memset(c2,0,sizeof(c2));  //中间数组必须置0
        for(int l = 0;l <= HalfSum;l++){//c[l]代表前i-1个表达式的结果的指数部分为l的系数
            for(int r = 0;r <=1 && c3[r]+l <= HalfSum;r++){//第i个表达式，只有两项
                //cout <<'(' <<c3[r] <<',' <<l <<')' <<endl;
                c2[c3[r]+l] += c1[l];
            }
        }
        for(int k = 0;k <= HalfSum;k++)
            c1[k] = c2[k];
    }
    cout <<c1[HalfSum]/2 <<endl;
    fclose(stdin);
    fclose(stdout);
    return 0;
}
```

---

## 作者：Thaumaturge (赞：1)

居然能过，简直怀疑自己的智商
```cpp
#include <bits/stdc++.h>

using namespace std;

long int i,j,k,m,a[3000],sum;

int main(){
	cin>>m;
	sum=(m+1)*m/2;//求总和
	if(sum%2==1) {cout<<0; return 0;}//和为奇数就直接跳出来
	else sum=sum/2;
	
	a[0]=1;//设置初始状态

	for(j=1;j<=m;j++)//先枚举数字
	{
		for(i=sum;i>=1;i--)//只能这么转移，防止变成完全背包
		{
			if(i>=j) a[i]+=a[i-j];//整合方案
		}
	}

	cout<<a[sum]/2;//这么转移，会导致一组数据变为两组，直接除以2
	return 0;
}
```


---

## 作者：Celebrate (赞：1)

这是一道简单的递推，f[i]表示i的方案数*2

代码如下：

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
long long f[1100];//int会爆 
int main()
{
	int i,j,t,n=0;scanf("%d",&t);//输入 
	for(i=1;i<=t;i++) n+=i;//求和 
	if(n%2==1){printf("0\n");return 0;}//如果是奇数，就满足不了条件 
	n/=2;//因为两份相等所以要/2 
	f[0]=1;//0是一种方案，什么都不用管就是这个方案 
	for(i=1;i<=t;i++)//t个数 
		for(j=n;j>=i;j--)//从n开始往下，自己无法叠加自己 
			f[j]+=f[j-i];//递推 
	printf("%lld",f[n]/2);//记得/2，因为两个为一种方案 
	return 0;
}
```

---

