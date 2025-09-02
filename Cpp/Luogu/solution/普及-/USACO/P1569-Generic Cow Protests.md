# Generic Cow Protests

## 题目描述

约翰家的 $n$ 头奶牛聚集在一起，排成一列，正在进行一项抗议活动。第 $i$ 头奶牛的理智度为 $a_i$。  
约翰希望奶牛在抗议时保持理性，为此，他打算将所有的奶牛隔离成若干个小组，每个小组内的奶牛的理智度总和都要不小于零。  
由于奶牛是按直线排列的，所以一个小组内的奶牛位置必须是连续的。请帮助约翰计算一下，最多分成几组。


## 说明/提示

【数据规模和约定】   
对于 $30\%$ 的数据，$1\le n \le 20$；   
对于 $100\%$ 的数据，$1\le n \le 1000$，$|a_i| \le 10^5$。  


## 样例 #1

### 输入

```
4
2
3
-3
1
```

### 输出

```
3```

# 题解

## 作者：xvhuanlin (赞：86)

本题类似于最长子序列的问题。

设add数组记录前i个数的和，dp数组记录分组到第i数时的最大分组。

当add[n]<0时，直接输出Impossible。

不然从1到n循环，当找到第i个数时，从0到i-1中找到第j个数，满足add[i]-add[j]>=0，即保证j到i为一组时，和是非负的，若dp[j]+1>dp[i]，则更新dp[i]。

需要注意的是，找到第i个数时，必须保证add[i]>=0，反之跳到下一位。因为若add[i]<0，则此时前i位之和为负，不可能有解。


---

## 作者：ShineEternal (赞：73)

经典动规题

------------

**设f[i]表示前i头牛最优分组**

**d[i]记录前i头牛理智度总和**
```
#include<cstdio>
#include<cmath>
using namespace std;
int d[1001],f[1001];
int main()
{
	int n;
	scanf("%d",&n);
	int x;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&x);
		d[i]=d[i-1]+x;
		if(d[i]>=0)f[i]=1;//保底有1组呀
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<i;j++)
		{
			if(f[j]>0&&d[i]-d[j]>=0)//前面已经可以分组&&这一段理智>=0
			f[i]=fmax(f[i],f[j]+1);//更新最大值
		}
	}
	if(f[n]==0)//一组分不了，即为不可能
	{
		printf("Impossible");
		return 0;//直接跳出
	}
	printf("%d",f[n]);
	return 0;
} 
```

大家都很厉害呀，认为这是入门难度，蒟蒻在这里班门弄斧了。

求过

---

## 作者：Lips (赞：34)

# $dp$ 简单问题。

先来看 `Impossible` 的情况，既然要求每组的理智度 $\ge0$，所以当且仅当所有的牛的理智度和 $<0$ 时，才是无解，毕竟最少分 $1$ 组都分不了，别提分多组了。

来定义状态，既然要求最大分组，那么设 $dp_i$ 为到第 $i$ 头牛为止，最多分成的组。

然后我们可以去枚举 $i$，也就是算截止到第 $i$ 头牛最大分组。与判断`Impossible` 的情况同理，如果到第 $i$ 个位置的所有牛的理智度 $\ge0$，那么这里就不能分成一组，于是跳过这种情况，毕竟您怎么分也不可能分成若干组都大于 $0$ 的情况。

之后我们可以枚举另一个端点 $j$，它是来假设上一个分组就在 $j$ 这个位置截止，从而推出 $dp_i$ 的最优解，首先要有一个特判，先看一下区间 $[j,i]$ 的和是否合法，也就是 $\ge0$，只有这样才可进行动态转移（牛的理智度必须大于 $0$）。

再考虑动态转移方程，第 $i$ 个位置必定从第 $j$ 个位置转移过来，那么第 $i$ 个位置就有两种选择：

- 不分组，$dp_i=dp_i$。

- 分组，需要将上一个分组的位置 $j$ 的最优解 $+1$，因为又分了一组，$dp_i=dp_j+1$。

在分组与不分组之间，取一个最大值，就是 $dp_i$ 的最优解：$dp_i=\max(dp_i,dp_j+1)$。

另外，本题需要多次计算某段区间的和，得用前缀和来解决。$sum_i$ 表示前 $i$ 个数的总和，区间 $[l,r]$ 的总和为：$sum_r-sum_{l-1}$。

$Code:$（高清方便某些人抄（伦敦雾（

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=1010;
int n,a[MAXN],sum[MAXN],dp[MAXN];
int main()
{
	scanf("%d",&n);
	for(register int i=1;i<=n;i++) scanf("%d",&a[i]),sum[i]=sum[i-1]+a[i];
	if(sum[n]<0) 
	{
		puts("Impossible");
		return 0;
	}
	for(register int i=1;i<=n;i++)
		if(sum[i]>=0) 
			for(register int j=0;j<i;j++) if(sum[i]-sum[j]>=0) dp[i]=max(dp[j]+1,dp[i]);
	printf("%d\n",dp[n]);
	return 0;
}
```


---

## 作者：zdx1031705564 (赞：12)

这么明显的前缀和，居然没有人搞一波前缀和？

我们来瞎搞一下

当i<j时 a[j]-a[i]>=0 那岂不是[i,j]可以作为一组

转移一下dp[j]=max(dp[j],dp[j]+1);

上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int inf=1000010;
int a[inf],dp[inf];
int main()
{
	int n,i,j,sumn=0;
	cin>>n;
	for(i=1;i<=n;i++)
	{	cin>>a[i];
		a[i]+=a[i-1];
		if(a[i]>=0) dp[i]=1;}
	for(i=1;i<=n;i++)
		for(j=1;j<i;j++)
			if(dp[j]>0&&a[i]-a[j]>=0) dp[i]=max(dp[i],dp[j]+1);//防伪标识
	if(dp[n]==0) cout<<"Impossible"<<endl;
	else cout<<dp[n]<<endl;
	return 0;
}
```
完美AC了

---

## 作者：OvOAuto (赞：6)

典型的一维 DP。

既然是连续的，那么 $sum_i$ 表示前 $i$ 个数的和，$dp_i$ 表示前 $i$ 个数的答案，也就是前 $i$ 头奶牛最多分成 $dp_i$ 组。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define OvO cout<<"OvO";

const int NR = 1e3 + 10;
int n,dp[NR],sum[NR];

int main()
{
	memset(dp,-999999,sizeof(dp));//预设成最小，这里-999999（我也忘了是bit还是Byte了）大概就接近int最小值
	cin>>n;
	for(int i = 1;i <= n;++i){
		cin>>sum[i];
		sum[i] += sum[i - 1];//这里要记录的是前i个数的和
	}
	dp[0] = 0;//第一个元素设为0，方便下面的j = 0处理
	for(int i = 1;i <= n;++i){
		for(int j = 0;j < i;++j)
			if(sum[i] - sum[j] >= 0)//如果这一段的理智度可以接受
				dp[i] = max(dp[j] + 1,dp[i]);//判断大小，决定状态
	}
	if(dp[n] < -1e9)
		cout<<"Impossible";//没有算出结果，也就是没有状态变动，无解
	else
		cout<<dp[n];//有解，输出答案
	return 0;
    OvO
}
```


---

## 作者：asuldb (赞：4)

比较基础的dp了

我们设$f[i]$表示前$i$只奶牛最多能分成多少组

于是我们的答案就是$f[n]$

于是我们的方程就是

$f[i]=max(f[j])+1$

其中$p[i]-p[j]>=0$

于是我们就有了一个时间复杂度为$O(n^2)$的动规了

但是作为一个追求时间与效率的人，这个复杂度我们显然是可以继续优化的

比如说优化到$O(nlog_{2}n)$

那我们就需要优化掉从前面找最优值的过程，我们期望一个$O(log_{2}n)$的过程

于是我们可以用线段树啊

我们先将前缀和离散化一遍，对于$p[i]-p[j]>=0$这个条件，不就是保证$p[i]>=p[j]$就好了，于是我们每次从比这个前缀和小的答案里找一个最大的就好了

于是就是代码了
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<map>
#include<set>
#define re register
#define maxn 1001
using namespace std;
int l[maxn<<2],r[maxn<<2],d[maxn<<2];
int a[maxn],p[maxn];
set<int> s;
map<int,int> ma;
int n,m,f[maxn];
int ans;
inline int read()
{
    char c=getchar();
    int x=0,r=1;
    while(c<'0'||c>'9')
    {
        if(c=='-') r=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9')
      x=(x<<3)+(x<<1)+c-48,c=getchar();
    return x*r;
}
void build(int x,int y,int i)//建树
{
    l[i]=x;
    r[i]=y;
    if(x==y) 
    {
    	d[i]=-999999;//我们先初始化一个最小值
    	return;
    }
    int mid=x+y>>1;
    build(x,mid,i<<1);
    build(mid+1,y,i<<1|1);
    d[i]=d[i<<1];
}
void change(int x,int v,int i)
{
    if(l[i]==r[i]&&l[i]==x)
    {
        if(v>d[i]) d[i]=v;//我们只有保证这个答案更大，才有更新的必要
        return;
    }
    int mid=l[i]+r[i]>>1;
    if(x<=mid) change(x,v,i<<1);
    else change(x,v,i<<1|1);
    d[i]=max(d[i<<1],d[i<<1|1]);
}
int query(int x,int y,int i)
{
    if(x<=l[i]&&y>=r[i]) return d[i];
    int mid=l[i]+r[i]>>1;
    if(y<=mid) return query(x,y,i<<1);
    if(x>mid) return query(x,y,i<<1|1);
    return max(query(x,y,i<<1),query(x,y,i<<1|1));
}
int main()
{
    n=read();
    for(re int i=1;i<=n;i++)
        a[i]=read();
    s.insert(0);
    for(re int i=1;i<=n;i++)
        p[i]=p[i-1]+a[i],s.insert(p[i]);//set用来离散化
    int tot=0;
    for(set<int>::iterator it=s.begin();it!=s.end();it++)
        ma[*it]=++tot;//map记录一下每个前缀和的值的新编号
    build(1,tot,1);
    for(re int i=1;i<=n+1;i++)
    if(p[i]>0) 
    {
    	ans=i;//对于那些刚上来就小于0的前缀和我们要直接滤过
    	break;
    }
    f[ans]=1;
    change(ma[p[ans]],1,1);
    for(re int i=ans+1;i<=n;i++)
    {
        f[i]=query(1,ma[p[i]],1)+1;//从前面找一个最优的答案
        change(ma[p[i]],f[i],1);//更新当前前缀和对应的答案
    }
    if(f[n]>0) cout<<f[n]<<endl;
    else puts("Impossible");
    return 0;
}
```

---

## 作者：ATZdhjeb (赞：3)

很简单的DP，发题解主要是为了展示一下我判断无解的思路。

设 $ans_i$ 表示前 $i$ 头牛最多可以分成多少组；同时，由于每组理智度是该组每头牛理智度之和，所以还需要用 $sum_i$ 来表示前 $i$ 头牛的理智度之和。状态转移方程就是简单的 $ans_i = max(ans_i,ans_j+1)$ （ $sum_i-sum_j \geq 0$ 时）。

但是，需要注意的是，本题要判断无解的情况。看见题解区好多大佬都直接用了前缀和来判断，但是本蒟蒻做题时~~脑子瓦特了~~并未想到这种做法，因此就在DP上动了一点手脚：

将 $ans$ 数组开始初始化为 $0$ ，接着用一个变量 $k$ 作为循环变量，找到第一个 $sum_k \geq 0$ ，然后将 $ans_k$ 赋为 $1$ ，再将 $ans_1$ 到  $ans_{k-1}$ 全部赋成 $-1$ （或者说标记为不合法的解）。

然后让 $i$ 从 $k+1$ 开始循环。每次循环都先开一个临时布尔变量 $f$ ，初值为 $true$ 。然后让 $j$ 从 $1$ 循环到 $i-1$ ，如果 $ans_j \neq -1$ 并且 $sum_i-sum_j \geq 0$（即 $ans_j$ 为合法解且从 $j$ 到 $i$ 的牛全部可以分在同一组），那么就状态转移，并将 $f$ 标记为 $false$ 。等 $j$ 循环完之后，如果 $f$ 还为 $true$ ，也就是没有发生状态转移，那么就将 $ans_i$ 赋为 $-1$ ，也就是标记为非法解。

最后，上~~无注释方便复制的~~代码。

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;
int main(){
	int n,k = 1;
	cin >> n;
	int x[n+5],ans[n+5],sum[n+5];
	sum[0] = 0;
	for(int i = 1;i<=n;++i){
		cin >> x[i];
		sum[i] = sum[i-1]+x[i];
	}
	memset(ans,0,sizeof(ans));
	while(sum[k++]<=0);
	--k;
	ans[k] = 1;
	for(int i = 1;i<k;++i) ans[i] = -1;
	for(int i = k+1;i<=n;++i){
		bool f = true;
		for(int j = 1;j<i;++j) 
			if(ans[j]!=-1 && sum[i]-sum[j]>=0) 
        	ans[i] = max(ans[i],ans[j]+1),f = false;
		if(f) ans[i] = -1;
	}
	if(ans[n]!=-1) cout << ans[n];
	else cout << "Impossible";
	return 0;
}
```

---

## 作者：Adove (赞：3)

这题复杂度优化不止有线段树一种方式啊QwQ

咱来分块乱搞一下吧。

思路和线段树那个是一样的。

空间比线段树小，复杂度比暴力更优

但常数很大。。？？？不知为啥每个点都3ms

复杂度$O(n\sqrt{n})$

```cpp
#include"cstdio"
#include"cstring"
#include"iostream"
#include"algorithm"
using namespace std;

const int MAXN=1005;

int n,siz;
int l[MAXN],r[MAXN],id[MAXN],val[45],f[MAXN];
struct rpg{
	int lis,id,ren;
}a[MAXN];

void build()
{
	for(int i=1;i<=n;++i){
		l[i]=l[i-1],r[i]=r[i-1],id[i]=id[i-1];
		if(i>r[i]){l[i]=r[i-1]+1;r[i]+=siz;id[i]=++val[0];}
	}return;
}

bool cmp1(rpg a,rpg b){return a.lis<b.lis;}
bool cmp2(rpg a,rpg b){return a.id<b.id;}

void init()
{
	scanf("%d",&n);for(int i=1;i*i<=n;++i) siz=i;
	for(int i=1;i<=n;++i) scanf("%d",&a[i].lis),a[i].lis+=a[i-1].lis,a[i].id=i;
	if(a[n].lis<0){puts("Impossible");exit(0);}build();
	sort(a+1,a+n+1,cmp1);a[1].ren=1;
	for(int i=2;i<=n;++i){a[i].ren=a[i-1].ren+(bool)(a[i].lis>a[i-1].lis);}
	sort(a+1,a+n+1,cmp2);return;
}

void solve()
{
	for(int i=1;i<=n;++i){
		int maxn=0;
		for(int j=a[i].ren;j>=l[a[i].ren];--j) maxn=max(maxn,f[j]);
		for(int j=id[a[i].ren]-1;j;--j) maxn=max(maxn,val[j]);
		if((!maxn&&a[i].lis>0)||maxn) f[a[i].ren]=maxn+1;
		val[id[a[i].ren]]=max(val[id[a[i].ren]],f[a[i].ren]);
	}printf("%d\n",f[a[n].ren]);
	return;
}

int main()
{
	init();
	solve();
	return 0;
}
```

---

## 作者：jijidawang (赞：2)

## 题意简述

> 将数列 $a$ 分成几组，每组数字和 $\ge 0$，求最大组数

## 算法分析

考虑 dp。

设 $sum_n=\sum\limits_{i=1}^na_i$，即前缀和。

然后设 $dp_i$ 记录 $1\sim i$ 区间的最优解。

将 $dp_i$ 遍历 $1\sim n$，当找到第 $i$ 个数时，从 $0\sim i-1$ 中找到第 $j$ 个数，满足 $add_i+add_j\ge0$，如果更优，就更新 $dp_i$。

注意 $dp_j$ 一定要是非负的，要不然不满足条件。

则：

对于任意 $i,j$ 若满足 $dp_j>0$ 且 $sum_i-sum_j>0$ 那么：

$$dp_i=\max\{dp_i,dp_j+1\}$$

清楚了之后，代码很好写。

---

## 作者：durex_com (赞：2)

### 一道简单的区间分组dp
（入门吗？这难度分组有点问题）

很显然
$f[i]=max(f[j])+1$
```cpp
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iostream>
using namespace std;
int dp[1001],sum[1001],x,i,j,k,l,o,p,m,n;
int main()
{
	scanf("%d",&n);
	for(i=1;i<=n;i++)
	{
		scanf("%d",&x);
		sum[i]=sum[i-1]+x;//先处理出sum。
		if (sum[i]>=0) dp[i]=1;
	}
	for(i=1;i<=n;i++)
	for(j=1;j<i;j++)
	{
		if (dp[j]>0&&sum[i]-sum[j]>=0) dp[i]=max(dp[i],dp[j]+1);
	}
	if (dp[n]==0) printf("Impossible");//注意I大写
	else printf("%d",dp[n]);
	return 0;
}
```

---

## 作者：huangwenlong (赞：1)

题目有坑，说的是大于0分一组，其实等于0也可以分一组

记录前i个奶牛的智商的和为sum[i]

容易证明，只有sum[i]>=0的时候，前i个奶牛才可以分组

那么就可以得到状转方程：

f(i)=max{f(k)+1} (1<=k<i, f(k)>0 && sum[i]-sum[j]>=0)

初始化dp数组的时候，sum[i]>=0的话dp[i]=1（至少分成一组），否则dp[i]=0（不可以分组）


来一发C++的代码

        
    
    
```cpp
#include <iostream>
#include <string>
#define maxn 1005
using namespace std;
int n;
int a[maxn];
int dp[maxn];
int sum[maxn]; //sum[i]即1~i的序列和
int main()
{
    cin>>n;
    for(int i=1;i<=n;++i)
    {
        cin>>a[i];
        sum[i]=sum[i-1]+a[i];
        if(sum[i]>=0) dp[i]=1; //至少可以分成1组
    }
    for(int i=1;i<=n;++i)
        for(int j=1;j<i;++j)
            if(dp[j]>0 && sum[i]-sum[j]>=0) dp[i]=max(dp[i],dp[j]+1);
    if(!dp[n]) cout<<"Impossible"<<endl;
    else cout<<dp[n]<<endl;
    return 0;
}
```

---

## 作者：心妍扎辫很美 (赞：0)

设f[i]表示前i头牛的最优分组                                   
sum是j到i的理智值                                                                  
递归式就是f[i]=max(f[j-1]+1)(j<=i,sum>=0)
```cpp
#include<cstdio>
#include<iostream>
using namespace std;
int n,a[1001],f[1001];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%d",&a[i]);
	for(int i=1;i<=n;++i)
	{
		int sum=0;
		for(int j=i;j>=1;--j)
		{
			sum+=a[j];
			if(sum>=0&&f[j-1]+1>f[i])
				if(j==1)f[i]=f[j-1]+1;
				else if(f[j-1]!=0)f[i]=f[j-1]+1;
		}
	}
	if(f[n]>0)printf("%d\n",f[n]);
	else printf("Impossible\n");
}
```


---

## 作者：pupuvovovovovo (赞：0)

一道区间分组dp。

最重要的问题是，题目描述方框中只能看前四行！剩下的要看输出格式。（望修改）

大意：给出一串数，求最多能分几组，使每组数字之和###******非负******（非负）。

f[i]代表前i头牛的最多分组数。

很明显，f[i]:=max{f[j]}+1

但是条件有坑。

**这题是怎么分到入门难度的？**

```cpp
var s:array [0..1000] of int64;
f,a:array [0..1000] of longint;//这儿不开0似乎没问题。
n,i,j:longint;
begin
  read(n);
  for i:=1 to n do
  begin
    read(a[i]);
    s[i]:=s[i-1]+a[i];
  end;
  for i:=1 to n do
  begin
    if s[i]>=0 then f[i]:=1;//如果直接做循环会有问题，万一直接自成一族呢。
    for j:=1 to i-1 do//本来这会有个0，上一行没有，但是发现这样的话会多算不可能的情况
      if (s[i]-s[j]>=0) and (f[j]+1>f[i]) and (f[j]>0) then//第三个条件用于滤不可能情况。YY
      f[i]:=f[j]+1;
  end;
  if f[n]=0 then write('Impossible') else write(f[n]);
  //是0的话意味着没有更新过，自然是不可能的。
end.
```

---

