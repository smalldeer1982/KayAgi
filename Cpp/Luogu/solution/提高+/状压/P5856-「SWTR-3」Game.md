# 「SWTR-3」Game

## 题目背景

小 E 在玩一个数字游戏。

## 题目描述

小 E 有 $n$ 个正整数 $a_1,a_2,\dots,a_n$。他可以进行以下操作任意次：

选择一个数 $q$，和一个集合 $S=\{d_1,d_2,\dots,d_m\}$，使得 $a_{d_1},a_{d_2},\dots,a_{d_m}$ 能被 $q$ 整除，并将 $a_{d_1},a_{d_2},\dots,a_{d_m}$ 除以 $q$。

- $q$ 要满足可以写成 $p^z$ 的形式，其中 $p$ 为质数，$z$ 为正整数。

求最少需要进行多少次操作才能将这些数变为相等的数。

## 说明/提示

#### 「样例 1 说明」

一开始的序列为 12 30 48 36 18。  
选择 $S=\{4,5\},p=3$，操作后变为 12 30 48 12 6。  
选择 $S=\{1,3,4\},p=2$，操作后变为 6 30 24 6 6。  
选择 $S=\{2\},p=5$，操作后变为 6 6 24 6 6。  
选择 $S=\{3\},p=2^2=4$，操作后变为 6 6 6 6 6。  
共 4 次操作，方法不唯一。

#### 「数据范围与约定」

**本题使用捆绑测试。**

Subtask 编号 | $n\leq$ | $a_i\leq$ | 特殊性质 | 得分
:-: | :-: | :-: | :-: | :-:
$1$ | $8$ | $50$ | $a_i$ 中有一个数为 $1$ | $13$
$2$ | $10$ | $100$ | 无 | $17$
$3$ | $10^3$ | $10^4$ | 无 | $29$
$4$ | $10^5$ | $10^6$ | 无 | $41$

对于 $100\%$ 的数据，有 $1\leq n\leq 10^5$，$1\leq a_i\leq 10^6$。

对于所有测试点，时间限制 1s，空间限制 128MB。

#### 「来源」

[Sweet Round 03 B](https://www.luogu.com.cn/contest/24755)。  
idea & solution：ET2006 & Alex_Wei。

## 样例 #1

### 输入

```
5
12 30 48 36 18
```

### 输出

```
4```

## 样例 #2

### 输入

```
10
72 81 27 90 45 45 27 99 45 18
```

### 输出

```
6```

## 样例 #3

### 输入

```
4
1 2 4 8```

### 输出

```
2```

# 题解

## 作者：Infiltrator (赞：5)

[$\Large\color{#FFBBFF}\textit{Tian-Xing's blog}$](https://Tian-Xing.github.io)

------------

# Description

[传送门](https://www.luogu.com.cn/problem/P5856)

------------

# Solution

读完题面之后我们首先可以想到要进行质因数分解。  

因为每次只能除以$prime^z$也就是说每次我们只能消除某一个质因子多出来的部分，所以对于每个质因子可以分开考虑。     

消去某个质因子多出来的部分只需要把这个质因子所有出现过的在每个数中的次数都记录下来，然后将一些数除以$prime^z$就相当于是从这些数中任意选取一些统一减去$z$。  

那么这些数减到什么时候合法呢？因为最后所有这$n$个数都必须相等，所以每个质因子在每个数中的次数最多是所有这$n$个数的$gcd$中该质因子出现的次数。

所以现在问题发生了转换，变成有一些数开始时从大到小递增，这些数只能是$[1,20]$中的数，要进行尽可能少的操作将所有数变成一样的且次数小于该质因子在$gcd$中出现的次数。    

接着可以发现，对于不同的质因子减数的效果是一样的，所以我们可以预处理出不同次数的最少次数，即用$dp[s]$表示状态为$s$时最少操作次数。  

因为不一定要消到所有的质因子次数都为$0$，所以预处理$gcd$中每个质因子出现的次数,这样只需要枚举最后每个质因数最后的次数的可行范围，即将$s$右移即可求出答案。

------------

# Code

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int n,a[724000][21],p[1000050],cnt,prime[1000050],ans,maxx,x[100050],anstmp,dp[2000050],gcdd,t[724000];
int gcd(int a,int b){return b==0?a:gcd(b,a%b);}
void xxs()
{
	p[0]=p[1]=1;
	for(int i=2;i<=1000000;i++)
	{
		if(!p[i])prime[++cnt]=i;
		for(int j=1;j<=cnt && prime[j]*i<=1000000;j++)
		{
			p[prime[j]*i]=1;
			if(i%prime[j]==0)break;
		}
	}
}
void make(int x)
{
	for(int i=1;i<=cnt && prime[i]<=x;i++)
	{
		int tmp=0;
		while(x%prime[i]==0)x/=prime[i],tmp++;
		if(tmp>0)a[i][tmp]=1;
	}
}
void print(int x)
{
	for(int i=20;i>=1;i--)
		if((1<<(i-1)&x)==1<<(i-1))cout<<1;
		else cout<<0;
	cout<<endl;
}
int main()
{
	xxs();
	scanf("%d",&n);
	scanf("%d",&x[1]);
	maxx=gcdd=x[1];
	for(int i=2;i<=n;i++)scanf("%d",&x[i]),maxx=max(maxx,x[i]),gcdd=gcd(gcdd,x[i]);
	for(int i=1;i<=cnt && prime[i]<=gcdd;i++)
	{
		int tmp=0;
		while(gcdd%prime[i]==0)gcdd/=prime[i],tmp++;
		if(tmp>0)t[i]=tmp;
	}
	for(int i=1;i<=n;i++)make(x[i]);
	for(int i=1;i<=1000500;i++)dp[i]=0x7f7f7f7f;
	dp[0]=0;
	for(int zt=1;zt<(1LL<<20);zt++)
	{
		int maxx;
		for(int i=20;i>=1;i--)if((zt>>i-1)&1==1){maxx=i;break;}
		for(int q=1;q<=maxx;q++)dp[zt]=min(dp[zt],dp[(zt&((1<<q-1)-1))|(zt>>q)]+1);
	}
	for(int i=1;i<=cnt && prime[i]<=maxx;i++)
	{
		int begin=0,minn,minnn;
		for(int j=1;j<=20;j++)if(a[i][j])begin|=(1<<(j-1));
		minnn=dp[begin];
		for(int j=1;j<=t[i];j++)minnn=min(minnn,dp[begin>>j]);
		ans+=minnn;
	} 
	printf("%d",ans);
	return 0;
}
```

---

## 作者：nofind (赞：4)

## [题意](https://www.luogu.com.cn/problem/P5856)

我自闭了，连蓝题都不会了，还得看题解。

以下是我理解的官方做法，献给给广大没看懂官方题解的神仙们。作者蒟蒻，如果有什么不对的地方请指出。

观察题目的限制，发现$q$是一个$p^z$的形式，因此我们可以考虑每个质数$p$。

对于每个质数$p$，我们求出一个$0-1$串$state_i$，其中第$i$位为$1$则表示存在一个数，它分解后$p$这个质因子的次幂为$i$。特殊地，如果一个数不含$p$这个质因子，那么第$0$位为$1$。$p$的次幂的上界很小，$p=2$时最大，才$\log_2$级别，因此是开得下的。

现在我们考虑通过题中的操作使得$a_{1...n}$相同的过程：  
对于每个质数$p$，显然只有所有$a_i$分解后的$p$的次幂相同才会满足条件。

#### 先假设我们要将所有的$a_i$中$p$的次幂都消成$0$。  
此时，我们要对$p$的状态求出一个最小的集合，满足将这个集合内的数任意相加可以拼出$p$的状态中所有的位置。

就拿官方题解里的例子吧：  
对于$1000111010$，在$1,3,4,5,9$位上是$1$（注意我们是从右向左从零开始数的），于是$f_{(1000111010)_2}=3$，因为我们可以通过$\{1,3,5\}$拼出所有的数。（$1=1$，$3=3$，$4=1+3$，$5=5$，$9=1+3+5$）

此时我们在$q=p^1$时操作分解后$p$的次幂为$1,4,9$的位置，在$q=p^3$时操作分解后$p$的次幂为$3,4,9$的位置，在$q=p^5$时操作分解后$p$的次幂为$5,9$的位置，那么所有的数中$p$的次幂都为$0$。

那么我们就设$f_s$表示状态$s$的答案，我们可以$dfs$求出。

但是包含$s$的状态$t$（即$s$是$t$的子集）的答案$f_t$也可以更新$f_s$（能拼出$t$就能拼出$s$），我们再枚举每个状态，更新它的子集即可。

#### 现在考虑我们不把所有的$a_i$中的$p$的次幂消成$0$的情况。

这时候需要满足该状态最低位（即第$0$位）不为$0$，因为为$0$的话就说明有一个数根本就没有$p$这个质因子，那肯定要全消完。

那么我们保留$p^k$就相当于$s_p>>k$这个状态的答案，还是拿之前的那个举例：  
$1000111010$，在$1,3,4,5,9$位上是$1$。
我们现在保留$p^1$，也就是我们要找最小的集合，使其能拼成$0,2,3,4,8$，那么对应的状态就是$s_p>>1$。

由衷地感叹：这题的确是道思维好题。

code（真·抄的官方题解）：
```
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+10;
const int maxm=20;
int n,ans;
int a[maxn],f[1<<maxm],state[1<<maxm],cnt[1<<maxm];
bool vis[maxn];
vector<int>prime;
inline void pre_work()
{
	vis[1]=1;
	for(int i=2;i<=1000000;i++)
	{
		if(!vis[i])prime.push_back(i);
		for(unsigned int j=0;j<prime.size()&&i*prime[j]<=1000000;j++)
		{
			vis[i*prime[j]]=1;
			if(i%prime[j]==0)break;
		}
	}
}
void dfs(int dep,int now,int s)
{
	f[s]=min(f[s],dep-1);
	if(dep>5)return;
	for(int i=now;i<=20;i++)dfs(dep+1,i,(s|(s<<i))&((1<<20)-1));
}
int main()
{
	pre_work();
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	memset(f,0x3f,sizeof(f));
	dfs(1,1,1);
	for(int s=(1<<20)-1;s;s--)
		for(int j=1;j<=20;j++)
			if(!((s>>(j-1))&1))f[s]=min(f[s],f[s|(1<<(j-1))]);
	for(int s=1;s<(1<<20);s++)if(!(s&1))f[s]=min(f[s],f[s>>1]);
	for(int i=1;i<=n;i++)
	{
		int tmp=a[i];
		for(unsigned int j=0;j<prime.size()&&prime[j]*prime[j]<=tmp;j++)
		{
			if(tmp%prime[j])continue;
			int k=0;
			while(tmp%prime[j]==0)k++,tmp/=prime[j];
			state[prime[j]]|=1<<k;cnt[prime[j]]++;
		}
		if(tmp>1)cnt[tmp]++,state[tmp]|=2;
	}
	for(int i=2;i<=1000000;i++)
	{
		if(cnt[i]!=n)state[i]|=1;
		ans+=f[state[i]];
	}
	printf("%d",ans);
	return 0;
}
```


---

## 作者：Alex_Wei (赞：3)

$\color{#00bfff}\mathrm{This\ is\ Sweet\ Round\ 03.}$

[$\color{#00bfff}\mathrm{Link:T2\ Game}$](https://www.luogu.com.cn/problem/P5856)

其实如果这题不出锅，质量还是挺高的（？

---

首先，设 $i$ 的二进制串为 $b_i$。

设 $f_i$ 表示通过 $01$ 背包后包含状态 $b_i$ 的集合的大小最小值。

例如 $f_{1000111010(570)}=3$，用集合 $\{1,3,5\}$ 就可以凑出。 

我们可以通过深搜预处理出背包状态**恰好为** $i$ 时的集合大小最小值。

然后根据 “如果一个状态能被组合出来，那么它的子集也能被组合出来” 更新 $f$ 数组。

接着根据 “如果一个状态末尾是 $0$，那么将它右移一位后的状态和它等效” 更新 $f$ 数组。

对于每个质数 $p$：我们得到一个长度为二进制串 $s$，第 $i$ 位表示 $a_1,a_2,\dots,a_n$ 中是否有一个数恰好被 $p^i$ 整除且不被 $p^{i+1}$ 整除。

答案加上 $f_s$ 即可。注意细节。

---

感谢 @LJC00118 提供的 $\mathrm{std}$。

$\mathrm{std:}$

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5,base=20;
int f[1<<base],state[1<<base],cnt[1<<base],a[N];
int n,ans;
void dfs(int u,int now,int state){
    f[state]=min(f[state],u-1);
	if(u>5)return;//因为{1+2+4+8+16}能表示出所有不大于31的数，而2^31>10^6,所以f[i]不会超过5
    for(int i=now;i<=20;i++)dfs(u+1,i,(state|(state<<i))&((1<<20)-1));
}
int main(){
    memset(f,0x7f,sizeof(f));
    dfs(1,1,1);
    for(int mid=1;mid<(1<<base);mid<<=1)
        for(int i=0;i<(1<<base);i+=(mid<<1))
            for(int j=0;j<mid;j++)
                f[i+j]=min(f[i+j],f[i+j+mid]);
    for(int i=1;i<(1<<base);i++)if(!(i&1))f[i]=min(f[i],f[i>>1]);
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
    	scanf("%d",&a[i]);
        for(int j=2;j*j<=a[i];j++){
            if(a[i]%j==0){
                int c=0;
                while(a[i]%j==0)++c,a[i]/=j;
                state[j]|=(1<<c);
                ++cnt[j];
            }
        }
        if(a[i]>1)++cnt[a[i]],state[a[i]]|=2;
    }
    for(int i=2;i<=1000000;i++){
        if(cnt[i]!=n)state[i]|=1;
        ans+=f[state[i]];
    }
    printf("%d",ans);
    return 0;
}
```

---

