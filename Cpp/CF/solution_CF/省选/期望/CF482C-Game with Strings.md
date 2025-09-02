# Game with Strings

## 题目描述

你和你的朋友玩一个游戏，游戏规则如下。

你的朋友创造出了 $n$ 个长度均为 $m$ 的不相同的字符串，然后他随机地选择其中一个。他选择这些字符串的概率是相等的，也就是说，他选择 $n$ 个字符串中的每一个的概率是 $\frac{1}{n}$。你想猜猜你的朋友选择了哪个字符串。

为了猜到你的朋友选择了哪个字符串，你可以问他问题，形式如下：字符串中第 $pos$ 个字符是什么？当这些问题的答案能够唯一确定一个字符串时，我们认为这个字符串被猜到了。在字符串被猜到后，你将停止提问。

你没有特殊的策略，所以你每次可能会等概率的问任何一个你从没猜过的位置。求猜到你的朋友选的字符串所需次数的期望。

## 样例 #1

### 输入

```
2
aab
aac
```

### 输出

```
2.000000000000000
```

## 样例 #2

### 输入

```
3
aaA
aBa
Caa
```

### 输出

```
1.666666666666667
```

## 样例 #3

### 输入

```
3
aca
vac
wqq
```

### 输出

```
1.000000000000000
```

# 题解

## 作者：Almus (赞：14)

 [洛谷传送门](https://www.luogu.com.cn/problem/CF482C) [CF传送门](https://codeforces.com/problemset/problem/482/C)  
 
#  Solution
看了看其他人的题解，感觉很高妙且看不懂，自己想了一个明快的做法/qd。

由于 $m≤20$，想到了状压当前询问了哪些位置，我们有一个最开始的想法：枚举每一个串，算出选了它的答案是多少再除以 $n$ 就得到了总的答案。

具体来说，设 $f_i$ 表示当前以及询问了 $i$ 这个状态，期望再问多少次能够确定这个串（当前枚举的这个串）。

转移就考虑这个状态下又问了哪个位置，可得：

$$f_i={\sum\limits_{!((1<<j)\&i)}} \dfrac{f_{i|(1<<j)}}{tot}+1$$

$tot$ 指的是 $i$ 里面 $0$ 的数量即还没有被问过的位置，答案显然是  $f_0$，值得注意的是，如果状态 $i$ 已经能够区分出这个字符串，那么 $f_i=0$，不再进行转移。

这样做法的复杂度是 $O(n\times m\times2^{m})$ 会寄。

考虑如何去优化，我们做的过程是对于每一个串去分别 $dp$ 求答案,再求一个总和，考虑能否一遍 $dp$ 求完所有字符串答案的总和。

 于是改变 $f_i$ 的定义为：当前已经询问了 $i$ 这个状态的位置，对于每一个串，它们**各自被唯一确定所需要的期望步数的总和。**
 
 换言之，新的定义下的 $f_i$ 即为旧的定义下每个串的 $f_i$ 的总和 。
 
 在从 $f_{i|(1<<j)}$ 转移过来时，原来额外会多 $1$ 的贡献，而现在，由于只有那些还未确定的串才要再继续问，会多未确定串的个数的贡献。**设  $num_i$ 为状态为 $i$ 时，还没有确定的串的个数**，则有如下转移：
 
 
 $$f_i={\sum\limits_{!((1<<j)\&i)}} \dfrac{f_{i|(1<<j)}}{tot}+num_i$$
 
接下来求解 $num$。设 $g_i$ 记录的是只问这个位置集合，不能被区分的那些串（状压）。

$O(n^2m)$ 暴力枚举两个串并且匹配，求出两个串的极大的相同的位置集合作为 $g_i$ 的初值。从大向小做，使 $g_i$ 或上其超集即可。

具体见代码:

```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define mkp make_pair
using namespace std;
const int inf=2147483647,N=55,M=1<<22;
inline int rd(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int n,m,g[M],num[M];;
double f[M];
char a[N][N];
signed main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	n=rd();
	for(int i=1;i<=n;i++) scanf("%s",a[i]+1); 
	m=strlen(a[1]+1);
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			int now=0;
			for(int k=1;k<=m;k++){
				if(a[i][k]==a[j][k]) now|=(1<<(m-k));
				g[now]|=(1ll<<i-1)|(1ll<<j-1);
			}
		}
	}
	for(int i=(1<<m)-1;i>=0;i--){
		for(int j=0;j<m;j++){
			if(!((i>>j)&1)) g[i]|=g[i^(1<<j)];
		}
	}
	for(int i=0;i<(1<<m);i++) {
		for(int j=0;j<n;j++){
			if((g[i]>>j)&1) num[i]++;
		}
	}
	for(int i=(1<<m)-1;i>=0;i--){
		if(!num[i]) continue;
		int cnt=0;
		for(int j=0;j<m;j++){
			if(!((i>>j)&1)) {
				cnt++;
				f[i]+=f[i|(1<<j)];
			}
		}
		f[i]=f[i]/cnt; f[i]+=1.0*num[i];
	}
	
	f[0]/=n;
	printf("%.9lf",f[0]);	
    return 0;
}
```

---

## 作者：是个汉子 (赞：7)

[洛谷传送门](https://www.luogu.com.cn/problem/CF482C)	[CF传送门](http://codeforces.com/problemset/problem/482/C)

### Solution

观察发现 $m\leq 20$ ，那么我们可以想到状压DP。

将位置压起来，设 $f_i$ 表示此时状态为 $i$ ，距离确定一个字符串所需要的期望，那么可得：
$$
f_i=\sum_{!(i\And(1<<j)}\frac {f_{i|(1<<j)}}{tot}+1
$$
其中 $tot$ 表示状态 $i$ 中还有几个位置没问（也就是还有几个 $0$ ），那因为询问剩余位置的概率相同，所以此方程是对的。

但是每次询问不一定就能唯一一个字符串，可能是好几个，所以需要处理出来对于每一个状态能确定几个字符串。

那么设 $num_i$ 表示符合 $i$ 这个状态的字符串的**数量**，可得：
$$
f_i=\sum_{!(i\And(1<<j)}\frac {f_{i|(1<<j)}}{tot}\times \frac {num_{i|(1<<j)}}{num_i}+1
$$
详细解释一下 $\dfrac {num_{i|(1<<j)}}{num_i}$ ：首先设 $k=i|(1<<j)$ ，那么 $num_k\leq num_i$ ，因为 $k$ 多了一位确定的。而 $i$ 有 $num_k$ 种可能变成 $k$ ，剩下的 $num_i-num_k$ 是直接得到唯一确定字符串的，所以继续转移的可能就是 $\dfrac  {num_{i|(1<<j)}}{num_i}$ 。

好，转移方程得到了，怎么求得 $num$ 数组呢？

这个时候，就要再来一个辅助的东西——设 $unf_i$ 表示状态为 $i$ 的情况下，哪些字符串是符合的，或者说是不能直接确定的（这里是拿**二进制状态**存串是否满足条件），因为在 $i$ 这个状态下，某几个串表达的东西可能一样。

对于 $unf$ 数组，直接 $O(n^2)$ 暴力匹配即可，然后从大到小更新。

那么 $num_i$ 就是 $unf_i$ 中 $1$ 的数量了。

注意：代码中状压时枚举要往后错一位。

### Code

```c++
#include<bits/stdc++.h>
#define int long long

using namespace std;
const int N=(1ll<<20)+10,M=55;
int m,n,unf[N],num[N];
char s[M][M];
double f[N];

signed main(){
    scanf("%lld",&n);
    for(int i=1;i<=n;i++) scanf("%s",s[i]+1);
    m=strlen(s[1]+1);
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++){
            int tmp=0;
            for(int k=1;k<=m;k++)
                if(s[i][k]==s[j][k]) tmp|=(1ll<<(k-1));
            unf[tmp]|=(1ll<<(i-1)); unf[tmp]|=(1ll<<(j-1));
        }
    for(int i=(1ll<<m)-1;i>=1;i--)
        for(int j=1;j<=m;j++)
            if(i&(1ll<<(j-1))) unf[i^(1ll<<(j-1))]|=unf[i];
    for(int i=0;i<(1ll<<m);i++)
        for(int j=1;j<=n;j++)
            if(unf[i]&(1ll<<(j-1))) num[i]++;
    for(int i=(1ll<<m)-2;i>=0;i--){
        if(!num[i]) continue;
        int tot=m;
        for(int j=1;j<=m;j++)
            if(i&(1ll<<(j-1))) --tot;
        for(int j=1;j<=m;j++){
            if(i&(1ll<<(j-1))) continue;
            f[i]+=
            f[i|(1ll<<(j-1))]/(double)tot*((double)num[i|(1ll<<(j-1))]/(double)num[i]);
        }
        f[i]+=1.0;
    }
    printf("%.10lf\n",f[0]);
    return 0;
}
```



---

## 作者：CDFLS_mao_zx (赞：4)

##  CF432C

### 废话：

1. 这是一道好题。
2. 这道题我自闭了一下午，最后看 $\text{Tourist}$ 代码才写过。
3. 所以要来水一篇~~清楚~~的题解。

### 题意：

给定 $n$ 个字符串，长度为 $m$ ，随机选一个出来，每次随机获取一个还没有被获取的位置（得知这个位置上的字符），问期望多少次可以获取到这个字符串。所有随机均是等概率随机。

$m\leq 20,n\leq 50$

### 思路：

首先看到期望，考虑从后向前推。~~至于为什么我只能说题做多了就知道了。~~

然后看到 $m\leq 20$ ，并且注意到题目中只关心哪些位置还没有被获取，所以状压。

$dp[mask]$ 表示现在获取的状态为 $mask$ ，获取到这个字符串期望**还需要多少步**。显然有边界 $dp[(1<<m)-1]=0$ 。每次考虑填好 $dp[mask]$ ，那么枚举 $mask$ 上哪些位置还是 $0$ ，需要在这些位置中随机选一个来转移。

期望 $dp$ ，不，所有 $dp$ 的一个重要步骤都是考虑到下一步需要的代价。这道题的这个代价有那么~~一点点~~特殊。我们发现，其实获取到了某个状态 $mask$ ，其实有一部分字符串已经被我们确定出来了，不需要继续填了，然而，我们并不知道我们选到的字符串是不是已经被确定了，所以考虑枚举选到的字符串，看看它是否在 $mask$ 状态下能被确定好就可以了。

转移方程  :
$$
dp[mask]=\min_{i \in mask}(p[mask]+dp[mask|(1<<i)])
$$


$p[mask]$ 表示选到枚举的这个字符串的情况下，它在 $mask$ 能否被确定，能则 $p[mask]=0$

所以我们得到了一个 $O(2^n * n * m)$ 的做法。~~得到了 TLE 13 的好成绩~~。

认真观察这个柿子，再联想一下枚举选的字符串的过程，我们发现转移的时候关心的只是目前状态 $mask$ 下有多少个字符串还没确定。

那么就不枚举选择的字符串了，直接转移。

假设我们在 $mask$ 这里能还不能确定出来的字符串的个数为 $num_i$ ，那么我们转移的代价就是 $\dfrac{num_i}{n}$ ，为什么是这个？因为只有 $\dfrac{num_i}{n}$ 的可能会继续选下去。

所以剩下的问题就变成了统计 $mask$ 状态下哪些还不能确定。

我们发现其实 $m$ 也不大，所以枚举每一对字符串，看它们相同位置的集合。（一个字符串如果不能被确定，那么至少有一个字符串在这个状态下和它相同），状压这个集合即可。

具体实现见代码和其它大神的题解。

### 参考代码：

```cpp
#include<bits/stdc++.h>
#define y1 y3647
#define next nxt
#define earse erase
#define INF 1000000000
#define LL long long
#define low(x) (x)&(-x)
using namespace std;
inline void read(int &x)
{
	x=0;int f=1;
	char ch=getchar();
	while(ch!=45&&(ch>'9'||ch<'0'))ch=getchar();
	if(ch==45){f=-1,ch=getchar();}
	while(ch<='9'&&ch>='0'){x=x*10+ch-48;ch=getchar();}
	x*=f;
}
const int N=20,M=55;
int i,j,k,n,s,t,m;
int cnt[1<<N];
LL p[1<<N];
char ch[M][N+10];
double dp[1<<N];
double ans;
signed main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	//freopen(".ans","w",sdtout);
	read(m);
	for(i=1;i<=m;i++)
	scanf("%s",ch[i]+1);
	
	n=strlen(ch[1]+1);
	
	for(i=1;i<=m;i++)
	for(j=i+1;j<=m;j++)
	{
		int mask=0;
		for(k=1;k<=n;k++)
		if(ch[i][k]==ch[j][k])
		mask|=1<<k-1;
		
		p[mask]|=1ll<<j-1,p[mask]|=1ll<<i-1;
	}
	for(i=1;i<1<<n;i++)
	cnt[i]=__builtin_popcount(i);
	
	p[(1<<n)-2]|=p[(1<<n)-1];
	for(int mask=(1<<n)-2;mask>=0;mask--)
	{
		for(i=1;i<=n;i++)
		if(((1<<i-1)&mask)==0)
		{
			p[mask]|=p[mask^(1<<i-1)];
			dp[mask]+=1.0/(n-cnt[mask])*dp[mask^(1<<i-1)];
		}
		dp[mask]+=1.0*__builtin_popcountll(p[mask])/m;
	}
	printf("%0.9lf",dp[0]);
	return 0;
}


```



---

## 作者：FarmerJohn (赞：4)

我觉得没有必要考虑DP 有一种更加简单的思路

因为状态数非常少 我们枚举被选中的串 再枚举一个询问的状态（无序）

这是因为每次对位置的询问互相独立 

考虑一个状态需要的期望步数 $\sum_{i=1}^{m} i/(i+n-m)$ 其中n是字符串长度 m是选中状态中1的个数

面向一个已知询问串 每次询问一个位置可以区分一个集合的串 手打bit优化或者强行上Bitset都是不错的选择 

正确性显然 

---

## 作者：leozhang (赞：3)

noip2016考了一道状压dp，一道期望dp

然而这题是状压期望dp...

所以难度是什么，省选noi吗...

怎么办...

题目大意：

给定n个字符串，甲从中任选出一个串（即选出每个串的概率相同为1/n）,乙要通过询问甲选出的字符串pos位置上的字符是什么来确定这个串。然而由于有些字符串的一些位置上字符相同，所以可能不能通过一次询问达成目标。现在乙没有任何策略地进行随机询问，问乙能够确定答案的询问次数期望是多少？

其中n<=50，每个字符串长度相等且长度<=20

题解：

首先状压是比较好想的，但是和期望结合起来了，我们怎么办呢？

那么我们先尝试对询问进行状压，这也是最显然的一个思路：记1表示该位置已被询问过，0表示该位置未被询问过。

那么我们考虑转移：设状态为dp[i],字符串长度为l，那么dp[i]+=dp[i|(1<<j)]*1/tot

看懵了？

首先我们要知道，这是个期望dp，状态表示的是已经问了i状态的问题，距离得到想要的字符串的期望距离是多少

于是显然我们从后向前更新。

接下来，我们设j是i状态中没问过的一个问题，那么dp[i]就可以由dp[i|(1<<j)]转移过来

而设i状态中没问过的问题数为tot，那么问出问题j的概率就是1/tot

但...你有没有觉得缺点什么？

是啊，这样根本忽略掉了字符串，变成了无论你读入什么串结果都一样，因为转移中根本没体现出字符串的存在！！！

所以这个转移显然是并不完全的。

那么我们要考虑一下完善它

我们维护另一个数组num,用num[i]表示问i状态的问题有多少字符串是彼此区分不开的

然后在转移dp时，我们使用这个方程：dp[i]=（∑dp[i|(1<<j)]1/totnum[i|(1<<j)]/num[i]）+1

这样就比较完善了。

至于证明：前半部分不说了，我们就说一下后面除法的部分：

其实这个方程可玄学了，网上其他方程都和这个不一样，但这是最简洁的一个...

稍微证明一下，就是说当状态为i时，待确定的串有num[i]个，而当状态为(1<<j)|i时，待确定的状态有num[(1<<j)|i]个

这样一来，无法确定所求串的概率就是num[(1<<j)|i]/num[i]，只有这一部分会对期望产生贡献，所以乘上这个概率就好了。

至于num数组如何维护，首先我们记录某一状态i下有哪些串不能确定，那么如果询问为i的子集这些串显然也不能确定，那么我们再把所有的子集查出来维护一下就好了。


```cpp
#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>
#define ll long long
using namespace std;
int num[(1<<20)+5];
double dp[(1<<20)+5];
ll unusage[(1<<20)+5];
int n,l;
char ch[55][25];
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        scanf("%s",ch[i]);
    }
    if(n==1)
    {
        printf("0.000000000\n");
        return 0;
    }
    l=strlen(ch[1]);
    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            ll sit=0;
            for(int k=0;k<l;k++)
            {
                if(ch[i][k]==ch[j][k])
                {
                    sit|=(1ll<<k);
                }
            }
            unusage[sit]|=(1ll<<i);
            unusage[sit]|=(1ll<<j);
        }
    }
    for(int i=(1<<l)-1;i>=1;i--)
    {
        for(int j=0;j<l;j++)
        {
            if(i&(1<<j))
            {
                unusage[i^(1<<j)]|=unusage[i];
            }
        }
    }
    for(int i=0;i<(1<<l);i++)
    {
        for(int j=0;j<n;j++)
        {
            if(unusage[i]&(1ll<<j))
            {
                num[i]++;
            }
        }
    }
    dp[(1<<l)-1]=0;
    for(int i=(1<<l)-2;i>=0;i--)
    {
        if(!num[i])
        {
            dp[i]=0;
            continue;
        }else
        {
            int tot=l;
            for(int j=0;j<l;j++)
            {
                if((1<<j)&i)
                {
                    tot--;
                }
            }
            for(int j=0;j<l;j++)
            {
                if((1<<j)&i)
                {
                    continue;
                }
                dp[i]+=dp[i|(1<<j)]*1.0/(double)(tot)*(double)(num[i|(1<<j)])/(double)(num[i]);
            }
            dp[i]+=1.0;
        }
    }
    printf("%.9lf\n",dp[0]);
    return 0;
}
```

---

## 作者：YellowBean_Elsa (赞：3)

 我做过状压dp

 我做过期望dp

### 但状压期望dp我还是第一次见！

~~（黑题题解我也是第一次写）~~

看小数据能想到状压（但注意有很多东西要状压）

```cpp
#include<bits/stdc++.h>
#define ll long long
#define re register
using namespace std;
const int N=55;
const int L=21;
int n;
char s[N][L];
double ans;
ll unable[1<<L];//问了mask状态的位置时不能被确定的string的集合的状态
double pos[1<<L];//问了mask的possibility
int zero;//How many "zero"s in the mask of pos;
int one;//How many "one"s in the unable[mask];
inline int read(){
	int x=0;char ch=getchar();
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
	return x;
}
int main(){
	n=read();
	for(re int i=1;i<=n;i++)
		scanf("%s",&s[i]);
	int len=strlen(s[1]),same;
	//get unable strings
	for(re int i=1;i<=n;i++)
		for(re int j=i+1;j<=n;j++){//枚举两个字符串 
			same=0;//两个字符串那些位相同，状压进same 
			for(re int k=0;k<len;k++)if(s[i][k]==s[j][k])
				same|=(1<<k);
			unable[same]|=(((ll)1<<(i-1))|((ll)1<<(j-1)));//"|=" == "+="		
			//即把在某几位相同的字符串加入unable只问其same位的状态中
		}
	for(re int mask=(1<<len)-1;mask>=0;mask--)//从大往小，把包含自己的集合中的内容加进自己 
		for(re int i=1;i<=len;i++)if(mask&(1<<(i-1)))
			unable[mask^(1<<(i-1))]|=unable[mask];//"^=" == "-="
			//mask不行的话其子集当然不行 
	pos[0]=1;
	for(re int mask=0;mask<(1<<len);mask++){//问了的位数的状压 
		zero=one=0;
		for(re int i=0;i<len;i++)if(!(mask&(1<<i)))zero++;//统计zero 
		for(re int i=0;i<n;i++)if(unable[mask]&((ll)1<<i))one++;//统计one 
		for(re int i=0;i<len;i++)if(!(mask&(1<<i)))
			pos[(mask|(1<<i))]+=pos[mask]/(double)zero;//递推possibility
		ans+=pos[mask]*(double)one;//还需要one步才能搞定unable[mask]中的字符串 
	}
	printf("%.12f\n",(ans/(double)n));//由于之前算ans是按每个字符串都要判出来做的，
									//现在要/n来get到一个字符串的期望 
	return 0;
}
```


---

## 作者：cwfxlh (赞：1)

# [CF482C](https://www.luogu.com.cn/problem/CF482C)         

?突然抽风，不会高维前缀和了，想了一个稍微有点不同的做法。        

考虑对期望次数的贡献做拆分，接下来需要求的就是求出猜测位置集合为 $S$ 时，是否能区分出字符串 $s_x$。直接暴力求的话复杂度是 $O(n^2m2^m)$ 的，无法通过。这一步可以高维前缀和做，但我采用的是另一种做法。          

将字符串拆成前后两半，对于两边分别求出猜测集合为 $T$ 时，不能与 $s_x$ 区分的字符串有哪些，容易发现这样的话只用处理 $n2^{\frac{m}{2}}$ 种状态，随便处理一下就过了，然后查询的时候把 $S$ 拆成两半，左右两边与起来就可以得到答案了。因为询问数量没有降低，所以复杂度是 $O(n^2m2^{\frac{m}{2}}+n2^m)$ 的。         

代码：      

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,f[53][(1<<10)],g[53][(1<<10)],fsp[63],B,k1,k2,k3,k4,k5,k6,C[503][503];
double ans,v[503];
string s[5003];
signed main(){
    ios::sync_with_stdio(false);
    fsp[0]=1;
    for(int i=1;i<=60;i++)fsp[i]=fsp[i-1]*2ll;
    for(int i=0;i<=20;i++)C[i][0]=1;
    for(int i=1;i<=20;i++){
        for(int j=1;j<=i;j++)C[i][j]=C[i-1][j]+C[i-1][j-1];
    }
    cin>>n;
    for(int i=1;i<=n;i++)cin>>s[i];
    m=s[1].length();
    B=(m/2);
    for(int i=0;i<=m;i++)v[i]=(1.0/((double)(n*C[m][i])));
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++){
            k1=k2=0;
            for(int u=1;u<=B;u++)if(s[i][u-1]==s[j][u-1])k1+=(1<<(u-1));
            for(int u=B+1;u<=m;u++)if(s[i][u-1]==s[j][u-1])k2+=(1<<(u-B-1));
            for(int u=0;u<(1<<B);u++){
                if((u&k1)==u){
                    f[i][u]|=fsp[j-1];
                    f[j][u]|=fsp[i-1];
                }
            }
            for(int u=0;u<(1<<(m-B));u++){
                if((u&k2)==u){
                    g[i][u]|=fsp[j-1];
                    g[j][u]|=fsp[i-1];
                }
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<(1<<B);j++){
            for(int u=0;u<(1<<(m-B));u++){
                if((f[i][j]&g[i][u])!=fsp[i-1])ans+=v[__builtin_popcount(j+(u<<B))];
            }
        }
    }
    cout<<fixed<<setprecision(10)<<ans;
    return 0;
}
```

---

## 作者：2huk (赞：0)

> - 小 A 有 $n$ 个长度均为 $m$ 的不相同的字符串，然后小 A 随机地选择其中一个，小 B 要猜这个字符串。小 B 可以问小 A：字符串中第 $pos$ 个字符是什么？求小 B 期望问几次能唯一确定这个字符串。
> - $n \le 50, m \le 20$。

不妨枚举小 A 选择的字符串为 $s_i$。

状压 DP。设 $f(S)$ 表示当前已经询问的下标集合为 $S$ 时，期望**再问几次**可以唯一确定 $s$。那么答案为 $f(\varnothing)$。

如果 $S$ 已经能够确定这个字符串那么 $f(S) = 0$。否则：
$$
f(S) = \sum_{v \notin S} \dfrac{f(S \cup \{v\}) + 1}{m - |S|} = 1  + \sum_{v \notin S} \dfrac{f(S \cup \{v\})}{m - |S|}
$$
复杂度过不去。思考能否省去最开始的枚举。

重新设 $f(S)$ 表示当前状态为 $S$ 时，每个 $s_i$ 期望的次数**之和**。也即，此时的 $f(S)$ 是上面每个字符串的 $f(S)$ 之和。

类似的有转移：
$$
f(S) = g(S)  + \sum_{v \notin S} \dfrac{f(S \cup \{v\})}{m - |S|}
$$
其中 $g(S)$ 有多少个字符串不能通过 $S$ 唯一确定。

考虑 $g(S)$ 的求解。我们可以枚举两个字符串 $s_i, s_j$。对于某个 $k$ 而言，如果 ${s_i}_k = {s_j}_k$ 那么就不能通过一次询问唯一确定 $s_i$ 或 $s_j$。令 $A$ 为所有这样的 $k$（${s_i}_k = {s_j}_k$）组成的集合。那么每个 $A$ 的子集都不能唯一确定 $s_i$ 或 $s_j$。高维前缀和秒了。

```cpp
#include <bits/stdc++.h>

typedef long long ll;
#define int ll

const int N = 51, M = 22;

int n, m;
int a[N][M];
double f[1ll << M], res;
ll g[1ll << M];

signed main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0), std::cout.tie(0);
	std::cin >> n;
	
	if (n == 1) {
		std::cout << 0 << '\n';
		return 0;
	}
	
	for (int i = 1; i <= n; ++ i ) {
		std::string s;
		std::cin >> s;
		m = s.size();
		for (int j = 0; j < m; ++ j )
			a[i][j] = s[j] >= 'a' ? s[j] - 'a' : s[j] - 'A' + 26;
	}
	
	g[0] = (1ll << n) - 1;
	for (int i = 1; i < n; ++ i )
		for (int j = i + 1; j <= n; ++ j ) {
			int S = 0;
			for (int k = 0; k < m; ++ k )
				if (a[i][k] == a[j][k]) S |= 1 << k;
			g[S] |= (1ll << i - 1) | (1ll << j - 1);
		}
	
	for (int i = 0; i < m; ++ i )
		for (int j = (1 << m) - 1; ~j; -- j )
			if (!(j >> i & 1)) g[j] |= g[j | (1ll << i)];
	
	for (int i = (1 << m) - 1; ~i; -- i ) {
		if (!g[i]) continue;
		for (int j = 0; j < m; ++ j )
			if (!(i >> j & 1)) f[i] += f[i | (1ll << j)];
		f[i] /= (m - __builtin_popcountll(i));
		f[i] += __builtin_popcountll(g[i]);
	}
	
	std::cout << std::fixed << std::setprecision(10) << f[0] / n << '\n';
	
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：0)

考虑对于每个串，如果问到的一个字符位置集 $S$ 满足存在另一个串与该串在这个字符位置集中所有位置上的字符相等，那么显然需要至少再问一次。贡献的期望就是这个字符位置集被达到的概率，即 $\frac{|S|!(m-|S|)!}{m!}$。

考虑如何对于每个串计算每个字符位置集是否贡献到期望中，先预处理出每个其他的字符串与他的哪些位置相同，再做一遍高维前缀和即可。复杂度 $O(n^2m+nm2^m)$，无法通过。

考虑优化，注意到对于每个串，每个字符位置集是否符合要求是一个 `bool` 类，故可以把所有串压到一起跑一遍高维前缀和，第 $i$ 个串占第 $i$ 个二进制位。总复杂度 $O(n^2m+m2^m)$，可以通过。

```cpp
#include <bits/stdc++.h>
#define int long long
#define add(i,j) ((i+j>=mod)?i+j-mod:i+j)
using namespace std;
int cnt[1048576],f[1048576];
string s[55];
signed main(){
	int n; cin>>n;
	for(int i=1;i<=n;i++) cin>>s[i];
	int m=s[1].size();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i==j) continue;
			int tmp=0;
			for(int k=0;k<m;k++){
				if(s[i][k]==s[j][k]) tmp|=(1<<k);
			}
			f[tmp]|=(1ll<<(i-1));
		}
	}
	for(int j=0;j<m;j++){
		for(int i=0;i<(1<<m);i++){
			if((i>>j)&1){
				f[i^(1<<j)]|=f[i];
			}
		}
	}
	double ans=0;
	for(int j=0;j<(1<<m);j++){
		for(int k=0;k<n;k++) if((f[j]>>k)&1) cnt[j]++;
		double pre=1;
		int bp=__builtin_popcount(j);
		for(int k=m-bp+1;k<=m;k++) pre/=k;
		for(int k=1;k<=bp;k++) pre*=k;
		ans+=cnt[j]*1.0/n*pre;
	}
	cout<<fixed<<setprecision(10)<<ans;
	return 0;
}
```

---

## 作者：SFlyer (赞：0)

首先求出来 $ind_{msk}$，代表知道了集合 $msk$ 中的元素，那么还是不能区别的字符串是那些。这个很好求。具体来说，先对于每两个字符串 $i,j$，求 $sm$ 表示 $i,j$ 相同的部分，再 $ind_{sm}|=2^i$。然后 $ind_{msk}|=ind_{msk|(2^i)}$，其中 $i$ 不在 $msk$ 中。

求这个有什么用？我们尝试用它表示答案。首先，我们要求的期望次数其实就是所有 $msk$ 被访问的期望次数之和。我们把每一个 $msk$ 被访问到的期望次数加起来就可以了。（$msk$ 是你已经问了的位置集合）对于 $msk$ 的答案是，$\frac{\texttt{popcnt}(ind_{msk})}{n\times \binom{len}{\texttt{popcnt}(msk)}}$，其中 $len$ 是每一个字符串的长度。

为什么呢？因为要访问到 $msk$，你必须：

- 不能问道 $msk$ 的子集就已经知道答案。

- 不能问不在 $msk$ 中的元素。

满足第一个，要只能答案是 $ind_{msk}$ 里的元素，即有 $\frac{\texttt{popcnt}(ind_{msk})}{n}$。满足第二个，在选 $\texttt{popcnt}(msk)$ 个地方问的情况里只有一种是可以的，因此要乘上一个 $\frac{1}{\binom{len}{\texttt{popcnt}(msk)}}$。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;

int n;
string s[55];
ll ind[1<<20];
ld dp[1<<20],C[21][21];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin>>n;
	for (int i=0; i<=20; i++){
		C[i][0]=1;
		for (int j=1; j<=i; j++){
			C[i][j]=C[i-1][j-1]+C[i-1][j];
		}
	}
	for (int i=0; i<n; i++){
		cin>>s[i];
	}
	int m=s[0].size();
	for (int i=0; i<n; i++){
		for (int j=0; j<n; j++){
			if (i!=j){
				int sm=0;
				for (int k=0; k<m; k++){
					if (s[i][k]==s[j][k]){
						sm|=(1<<k);
					}
				}
				ind[sm]|=(1ll<<i);
			}
		}
	}
	ld ans=0;
	for (int msk=(1<<m)-1; msk>=0; msk--){
		for (int i=0; i<m; i++){
			if (!(msk>>i&1)){
				ind[msk]|=ind[msk|(1<<i)];
			}
		}
		if (ind[msk]){
			int pop1=__builtin_popcountll(ind[msk]);
			int pop2=__builtin_popcountll(msk);
			ans+=1.*pop1/n/C[m][pop2];		
		}
	}
	cout<<fixed<<setprecision(10)<<ans<<"\n";
	return 0;
}
```

---

## 作者：N_Position (赞：0)

# CF482C

## 题目翻译

$n$ 个长度为 $m$ 的字符串 $s_i$，等概率随机选择其中一个字符串（记作 $x$）。

接下来，每次等概率随机询问该字符串的某一个位置是什么字符（不会询问已经问过的位置）。

问确定下选择的字符串是哪一个所需要次数的期望是多少。

$1\leq n\leq50,1\leq m\leq 20$。

## 分析

### 暴力求解

发现 $n$ 和 $m$ 很小，容易想到 $O(nm2^m)$ 的做法，即选择枚举每一个字符串的每一种状态，求解即可。

### 步骤 1

设 $d_i$ 表示询问状态为 $i$ 时，哪几个字符串不能不确定下来。

设 $num_i$ 表示询问状态为 $i$ 时，有几个字符串不能被确定下来。

以样例 $2$ 为例。

例如 $d_1=3$ 表示当询问状态为 $1$ 时（即只问了第一个字符是什么时），$s_1$ 和 $s_2$ 不能被确定下来，$s_3$ 可以被确定下来是或不是 $x$。

因此，此时 $num_1=2$（有 $s_1$ 和 $s_2$ 没有被确定下来）。

对于求解 $d$ 数组，可以在 $O(n^2m)$ 的复杂度内求解。

显然，若状态 $i$ 下某个字符串不能被判断出来，则状态为 $i$ 的子集下更不能被判断出来。

过程如下：

- $O(n^2)$ 枚举两个字符串 $s_i$ 和 $s_j$。
- $O(m)$ 枚举字符串的位置，得到 $s_i$ 和 $s_j$ 重合的位置 $t$。
- 那么，在 $t$ 状态下，一定不能判断出 $s_i$ 和 $s_j$。
- 在 $t$ 的子集下更不可以了。

### 步骤 2

设 $dp_i$ 表示询问状态为 $i$ 时，期望还需要询问的次数。

显然 $dp_{2^m-1}=0$，即所有位置都询问了之后，期望还需要询问 $0$ 次，才能确定下来 $x$ 是哪个字符串。

有转移方程：$dp_i=\sum \frac{dp_j}{tot}+num_i$，其中 $tot$ 表示 $i$ 中二进制表示下 $1$ 的个数，$j$ 为 $i$ 的子集，且 $i-j=2^k,k\in N$，即 $j$ 在二进制表示下仅仅是 $i$ 在某一位上把 $1$ 替换为了 $0$。

转移即可。

## 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 55;
const int M = 21;
typedef long long ll;
string s[N];
ll d[1<<M];
int num[1<<M];
double dp[1<<M];
int main(){
	int n,m;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		cin>>s[i];
	}
	m = s[1].length();
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			ll t = 0;
			for(int k=0;k<m;k++){
				if(s[i][k] == s[j][k]){
					t |= (1<<k);
				}
			}
			d[t] |= (1ll<<(i-1));
			d[t] |= (1ll<<(j-1));
		}
	}
	for(int i=(1<<m)-1;i>=0;i--){
		for(int j=0;j<m;j++){
			if(i&(1<<j))
			d[i^(1<<j)] |= d[i];
		}
	}
	for(int i=0;i<=(1<<m)-1;i++){
		while(d[i]){
			num[i] ++;
			d[i] -= (d[i]&(-d[i]));
		}
	}
//	puts("!");
	for(int i=(1<<m)-2;i>=0;i--){
		int cnt = 0;
		for(int j=0;j<m;j++){
			if(!(i&(1<<j))){//i 的 j 位为 0； 
				cnt ++;
				dp[i] += dp[i|(1<<j)];
			}
		}
		dp[i] = 1.0*dp[i]/cnt+num[i];
	}
//	cout<<dp[0];
	printf("%.15lf",dp[0]/n);
}
```

---

## 作者：spdarkle (赞：0)

一晚上切了这一道题，悲伤。

考虑设 $s_i$ 为选出位置状态为 $i$ 时，所有可以确定的字符串的集合。

注意到两个字符串 $a,b$ 在选出 $T$ 的情况下不同，当且仅当 $\exist k\in T,a_k\neq b_k$。

那么再考虑设 $g_{i,j}$ 表示选出点 $j$ 时，与 $i$ 不同的点的集合。

```cpp
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++)for(int k=0;k<n;k++)g[j][i]|=(1ll<<k)*(a[j][i]!=a[k][i]);
    }
```

然后我们利用 $g$，可以递推出 $f_{i,j}$ 为选出状态为 $j$ 时，与 $i$ 不同的点的集合。

当 $j\cup \lbrace i\rbrace=U$ 时，说明 $i$ 与众不同，可以唯一确定。

```cpp
    for(int i=0;i<n;i++){
        for(int j=1;j<(1<<m);j++){
            f[j]=f[j^(j&-j)]|g[i][lg[j&-j]];
            if(f[j]==(((1ll<<n)-1ll)^(1ll<<i)))s[j]|=1ll<<i;
        }
    }
```

由此我们可以 $O(n2^m+n^2m)$ 的求出 $s$。

然后考虑计算答案。

首先我们计算概率系数 $p_i$，表示选出集合 $i$ 的概率，这是非常容易的。

```cpp
    pi[0]=1;
    for(int i=0;i<(1<<m);i++){
        int c=0;
        for(int j=0;j<m;j++)c+=(i>>j)&1;
        for(int j=0;j<m;j++)if((i>>j)&1){
            pi[i]+=pi[i^(1<<j)]/(m-c+1);
        }
    }
```

$O(n2^m)$ 地可以求得概率。

然后我们考虑答案的计算。

$s_{T}\to s_{T\cup \lbrace i\rbrace}$ 这一步转移中，有 $|s_{T\cup \lbrace i\rbrace}-s_{T}|$ 个位置在这一步中确定。同时我们一共用了 $|T|+1$ 步。

所以贡献就是 $|s_{T\cup \lbrace i\rbrace}-s_{T}||T|\frac{p_{T}}{(n-|T|)n}$。

```cpp
    for(int i=0;i<(1<<m);i++){
        if(!s[i])continue;
        int c=0;
        for(int j=0;j<m;j++)c+=(i>>j)&1;
        for(int j=0;j<m;j++)if((i>>j)&1){
            ll t=s[i]^s[i^(1<<j)];
            res+=1.0*__builtin_popcountll(t)*pi[i^(1<<j)]*c/(m-c+1);
            // cout<<"Res: "<<res<<"\n";
            // cout<<i<<" "<<((i^(1<<j)))<<" "<<1.0*__builtin_popcountll(t)*pi[i^(1<<j)]*c/(m-c+1)<<" "<<pi[i^(1<<j)]<<" "<<c<<" "<<__builtin_popcountll(t)<<"\n"; 
        }
    }res/=n;
```

复杂度 $O(n2^m+n^2m)$。

---

## 作者：BotYoung (赞：0)

前置知识：**状压 DP**
## 分析：
看到 $n,m$ 都是两个比较小的数，提示我们可能用到状态压缩。

看到数学期望，提示我们需要用到 DP。根据一般期望 DP 的共性，我们可以定义 $f_{S,i}$，表示已知位置构成的集合为 $S$，通过若干次询问确定答案为第 $i$ 个字符串的期望次数。

考虑边界情况：一个字符串已经能够确认，当且仅当已知位置上的字符构成的子序列在所有字符串对应位置上的子序列中是独一无二的。

比较朴素的想法是，通过枚举位置集合，对每个字符串预处理出它的 $2^m-1$ 个子序列，并用一个桶进行统计，就可以对每个字符串找出所有满足边界条件的子集。

记满足边界条件的子集为 $S_0$，$m$ 为字符串长度有：
$$f_{S_0,i}=0$$

$$f_{S,i}=\dfrac{\sum\limits_{x\notin S}f_{S\cup \{x\},i}+1}{m-\operatorname{popcount(S)}}$$

(P.S：$\operatorname{popcount}$ 表示一个数二进制中 $1$ 的个数)

则最终答案 $Ans$ 为：

$$Ans=\sum\limits_{i=1}^n f_{\varnothing,i}$$

但这毕竟是一道 `*2600` 的黑题，简单计算后发现 $O(nm2^m)$ 的做法显然不可过。

## 优化：
E_firework：不考虑答案具体是谁，直接计算每个子集的贡献

~~(果然神就是神，一眼就把下位黑给切了)~~

回顾刚才的过程，唯一的复杂度瓶颈在于**判断一个子集是否满足边界条件**。

考虑直接对集合 $S$ 计算它的总贡献，定义新的 $f'_S=\sum_{i=1}^nf_{S,i}$。

### Q1：如何计算转移时的贡献
考虑当前集合为 $S$，朴素算法中，$(S,i)$ 能够对集合 $(S',i)$ 产生贡献，$(S',i)$ 一定尚未满足边界条件。

则发生转移 $S\rightarrow S'$ 的次数，一定是对于 $S'$ 而言不满足边界条件的 $i$ 的个数，我们可以记这个值为 $cnt_{S'}$。

那么可以得到新的转移方程：

$$f'_S=\dfrac{\sum\limits_{x\notin S}f'_{S\cup \{x\}}+cnt_S}{m-\operatorname{popcount}(S)}$$

### Q2：如何快速求解 $cnt_S$

我们小小的运用一下逆向思维，对于已选定的位置集合 $S$，我们如何得知哪些字符串在这些位置上对应的子序列相同？

- **再打一个状压！**

我们直接枚举两个字符串 $i,j$，对于它们的每个极大相同子序列，将元素 $i,j$ 一起加入这个子序列对应的位置集合。

令处理后位置集合 $S$ 中无法区分的字符串集合为 $g_S$，对 $g_S$ 做一个超集并，即 $g_S=\bigcup\limits_{S\subseteq S'}g_{S'}$，那么我们要求的 $cnt_S$ 即为 $\operatorname{popcount}(g_S)$。

注意细节 $g$ 开 `long long` （$n\leq50$）

那么这道题到这里就做完了。下面是喜闻乐见的代码部分：
```cpp
#include <bits/stdc++.h>
#define reg register
#define rep(i, l, r) for (reg int i = l; i <= r; i++)
#define per(i, r, l) for (reg int i = r; i >= l; i--)
using namespace std;
typedef long long ll;
typedef unsigned long long llu;
namespace io {
inline ll read(){
    reg ll s = 0, f = 1;
    reg char ch = getchar();
    while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
    while (ch >= '0' && ch <= '9') { s = (s << 1) + (s << 3) + (ch ^ '0'); ch = getchar(); }
    return s * f;
}
inline void write(reg ll x){
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x / 10); putchar(x % 10 ^ '0');
}
inline void write(reg ll x, reg char c){
    write(x), putchar(c);
}
}//namespace io
using namespace io;
const int N = 1 << 20;
int n, m, cnt[N];
ll g[N];
char s[55][25];
double f[N];
int main(){
    n = read();
    rep(i, 0, n - 1) scanf("\n%s", s[i]);
    m = strlen(s[0]);
    rep(i, 0, n - 1) rep(j, i + 1, n - 1){
        int res = 0;
        rep(k, 0, m - 1) {
            if (s[i][k] == s[j][k]) res |= 1 << m - 1 - k;
            g[res] |= (1ll << i) | (1ll << j);
        }
    }
    per(i, (1 << m) - 1, 0) rep(j, 0, m - 1) if (!(i >> j & 1)) g[i] |= g[i ^ (1 << j)];
    rep(i, 0, (1 << m) - 1) rep(j, 0, n - 1) cnt[i] += (g[i] >> j & 1);
    per(i, (1 << m) - 1, 0) {
        if (!cnt[i]) continue;
        int siz = 0;
        rep(j, 0, m - 1) if (!(i >> j & 1)) f[i] += f[i ^ (1 << j)], ++siz;
        f[i] = f[i] / siz + cnt[i];
    }
    printf("%.10lf", f[0] / n);
    return 0;
}
```

---

