# Maxim and Calculator

## 题目描述

Maxim has got a calculator. The calculator has two integer cells. Initially, the first cell contains number $ 1 $ , and the second cell contains number $ 0 $ . In one move you can perform one of the following operations:

1. Let's assume that at the current time the first cell contains number $ a $ , and the second cell contains number $ b $ . Write to the second cell number $ b+1 $ ;
2. Let's assume that at the current time the first cell contains number $ a $ , and the second cell contains number $ b $ . Write to the first cell number $ a·b $ .

Maxim is wondering, how many integers $ x $ $ (l<=x<=r) $ are there, such that we can write the number $ x $ to the first cell of the calculator, having performed at most $ p $ moves.

## 样例 #1

### 输入

```
2 10 3
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2 111 100
```

### 输出

```
106
```

## 样例 #3

### 输入

```
2 111 11
```

### 输出

```
47
```

# 题解

## 作者：ImmortalWatcher (赞：3)

**Description**

有两个数，$a=1$ 和 $b=0$。我们可以对它们进行两种操作。

1、把 $b$ 的值 $+1$。

2、把 $a$ 的值 $\times b$。

问 $a$ 在进行不超过 $p$ 次操作后，得到的数在 $l$~$r$ 这个区间的有多少个。

**Solution**

首先分析，由于进行了不超过 $p$ 次操作，而 $b$ 每次操作最多会 $+1$，所以最后 $b$ 的值一定不会大于 $p$，而 $a$ 的值是由多个 $b$ 的乘积组成的，所以 $a$ 不会有大于 $p$ 的约数，也就不会有大于 $p$ 的质因数。

所以我们可以把 $1$~$r$ 中能被不大于 $p$ 的质因数组合起来的数先爆搜出来，这样的数不超过 $3\times 10^6$ ，然后进行 $DP$。

设 $f[i][j]$ 表示当 $b$ 为 $i$ 时，$a$ 为 $j$ 时的操作 $2$ 的最小操作次数。

转移：$f[i][j]=min(f[i][j/i]+1,f[i-1][j])$。

但这样数组存不下，我们要解决两个问题。

1、$j$ 太大，数组开不下。

解决办法：

可以把 $j$ 用位置来表示，也就是 $f[i][j]$ 表示 $b$ 为 $i$，$a$ 为能被不大于 $p$ 的质因数组合起来的数中的第 $j$ 个，然后因为 $j$ 大了，$j/i$ 也会大，所以 $j/i$ 也可以用一个位置来存，跟着 $j$ 动即可。

2、两维数组开不下。

解决方法：

发现第一维 $i$ 只和 $i-1$ 和 $i$ 有关，可以滚动掉第一维。

这样我们就解决空间问题了。

但时间还是有点紧迫，我们不妨用一个玄学剪枝（也不知道能剪多少），设 $k=j/i$ 如果 $k\times i$ 大于能被不大于 $p$ 的质因数组合起来的数中最大的数，就可以直接退出了。

**Code**

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int l,r,p,ans,a[3000001],f[3000001],prime[101],tot,cnt;
bool bz[3000001],v[101];
void dfs(int x,int s)
{
	a[++cnt]=s;
	for (int i=x;i<=tot;i++)
		if (prime[i]*(long long)s<=r) dfs(i,prime[i]*s);
}
int main()
{
	scanf("%d%d%d",&l,&r,&p);
	for (int i=2;i<=p;i++)
	{
		if (!v[i]) prime[++tot]=i;
		for (int j=1;j<=tot;j++)
		{
			if (i*prime[j]>p) break;
			v[i*prime[j]]=true;
			if (i%prime[j]==0) break;
		}
	}
	dfs(1,1);
	for (int i=1;i<=cnt;i++) f[i]=0x3FFFFFFF;
	sort(a+1,a+cnt+1);
	f[1]=0;bz[1]=true;
	for (int i=2;i<=p;i++)
	{
		int j=i;
		for (int k=1;k<=cnt;k++)
		{
			while (j<=cnt&&a[j]!=a[k]*i) j++;
			if (j>cnt) break;
			if (f[k]+1<f[j]) f[j]=f[k]+1;
			if (a[j]<l||bz[j]) continue;
			if (f[j]+i<=p) bz[j]=true,ans++;
		}
	}
	printf("%d",ans);
	return 0;
}
```



---

## 作者：liangzihao (赞：3)

分析：
因为最多操作$p$步，所$b≤p$，所以$a$不会有大于$p$的约数，那一定不会有大于$p$的质因数。

我们把$[1,p]$范围内的所有小于等于$p$的质因数跑出来，然后dfs出$[1,r]$内可以被表示成小于等于$p$的质因数乘积的数跑出来，然后从小到大排序。

当$p=100,r=10^9$时，这样的数不超过$3*10^6$个，也就是只有这些数能被表示出来。

后面使用dp求步数，设$f[i][j]$表示表示二元组的第一维变为$j$，第二维变为$i$时，操作二的次数(乘操作)，显然有
$$f[i][j]=min(f[i][j/i]+1,f[i-1][j])$$
那么
$$step[j]=\min_{i=1}^{p}(f[i][j]+i)$$

我们发现第二维不能直接用$j$，因为$j$是$10^9$的，所以要把第二维设为是在答案数列中的第$j$位，这样的话，就不能直接用下标表示$j/i$了，但是我们发现，当我们$j$在不断增大的时候，$j/i$也是单调增的，所以我们可以开一个指针，当$j$右移时跟着就好了。

这样开$f$数组会爆空间，考虑滚动掉第二维，这样空间就是$10^6$级了。

时间复杂度是$O(p*n)$的，但是$n$最大可以达到$3*10^6$，还是跑不过。考虑玄学优化一下，我们发现可以改为枚举$k=j/i$，此时如果$k*i$已经大于数列中最大的数，那么就可以break掉了，应该是能过的。

代码：
```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>

const int maxn=3e6+7;

using namespace std;

int l,r,p,cnt,tot;
int not_prime[107],prime[107];
int a[maxn],f[maxn];
bool b[maxn];

void getprime(int n)
{
    for (int i=2;i<=n;i++)
    {
        if (!not_prime[i])
        {
            prime[++tot]=i;
        }
        for (int j=1;j<=tot;j++)
        {
            if (i*prime[j]>n) break;
            not_prime[i*prime[j]]=1;
            if (i%prime[j]==0) break;
        }
    }
}

void dfs(int x,int k)
{
    a[++cnt]=k;
    for (int i=x;i<=tot;i++)
    {
        if (prime[i]*(long long)k<=r) dfs(i,k*prime[i]);
    }
}

int main()
{
    scanf("%d%d%d",&l,&r,&p);
    getprime(p);    
    dfs(1,1);
    sort(a+1,a+cnt+1);      
    for (int i=1;i<=cnt;i++) f[i]=1156161;
    f[1]=0; b[1]=1; 
    int ans=0;
    for (int i=2;i<=p;i++)
    {       
        int j=i;            
        for (int k=1;k<=cnt;k++)
        {
            while ((j<=cnt) && (a[j]!=a[k]*i)) j++;
            if (j>cnt) break;
            if (f[k]+1<f[j]) f[j]=f[k]+1;
            if ((a[j]<l) || (b[j])) continue;
            if (f[j]+i<=p) b[j]=1,ans++;
        }       
    }   
    printf("%d",ans);
}
```


---

## 作者：灯芯糕 (赞：1)

### 题目大意：

有两个初始参数 $ a=1 $ ， $ b=0 $ ，你可以对它们进行两个操作： $ b~+=1 $ 或 $ a~\times =b $ ，最终的 $ a $ 才是你所得到的数 。 现在给你三个数 $ l,r,p $ ，让你求在区间 $ [l,r] $ 内可以用不超过 $ p $ 次操作得到的数的个数。数据范围： $ (2<=l<=r<=10^{9},1<=p<=100) $ 



------

------



## $ solution: $ 

很神仙的一道题，当时看了很久只能想到：每个我所得到的数，一定是若干个可能不同的 $ b $ 的乘积,。又因为 $ b $ 每次只能加1，所以我们如果要用最少的步数得到一个数 $ a $ ，**最终 $ b $ 的大小一定是 $ b $ 的最大质因子**！同理，**最大质因子大于 $ p $ 的数一定不可通过少于 $ p $ 的次数得到**！

当时的想法是线性筛最大质因子，然后暴力判断，复杂度 $ O(n) $ 显然超时。然后死活没想到可以筛 $ p $ 以下质数所构成的数（ $ 10^9 $ 里面不超过 $ 3\times 10^6 $ 个 ）！

好吧，回归正题。根据上面我们的分析，所有最大质因子大于 $ p $ 的数一定不可通过少于 $ p $ 的次数得到，所以我们可以找出所有最大质因子在 $ p $ 以内的数。怎么求？这其实等同于求 $ p $ 以内的所有质数可以构造的数（注意题目说 $ 2\leq r $ ，所以不考虑1）（然后我们现线性筛质数，再搜索一下即可）。然后我们发现这样的数不超过 $ 3\times 10^6 $ 个，我们用一个数组 $ a[] $ 存起来。于是我们考虑怎么判断 $ a[] $ 里面的数是否能在 $ p $ 次操作内得到。

首先我们要明白一个点：所有 $ a[] $ 里的数都可以通过 $ a[] $ 里比它小的数构造出来。证明：对于 $ a[] $ 里的数 $ i $  ，如果它的最大质因子为 $ k $ ，那么 $ i/k $ 一定在 $ a[] $ 中，因为 $ i/k $  的所有质因子都小于 $ p $ 。于是我们考虑 $ f[i][j] $ 表示 $ b $ 的大小为 $ i $ 时 $ j $ 的最小构造步数。我们从小到达枚举 $ b $ ，每个 $ b $ 可以选用很多次，这不就是一个完全背包吗？不过是 $ b $ 要被乘上去而已！注意我们的 $ a[] $ 数组是离散化的，我们先排一遍序，然后用单调队列找到 $ a[k]=a[j]*i $  即可做到 $ O(1) $ 转移！  

#### $ f[i][k]=f[i][j]+1 \quad (~a[j]\times i=a[k]~) $ 

复杂度： $ O(p\times 3 \times 10^6) $ ，很勉强



------

------



## $ code: $ 



```cpp
#include<iostream>
#include<cstdio>
#include<iomanip>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<vector>
#include<queue>
#include<map>
#include<set>

#define ll long long
#define db double
#define rg register int

using namespace std;

int l,r,p,n; // n表示a数组的大小
int ans,tt; // tt素数个数
int a[3000005]; //最大质因子小于p的数的集合
int f[3000005]; //构造a[i]这个数的最少步数
bool d[3000005]; //是否已经加入贡献
int pr[505]; //素数表
bool vis[505]; //筛素数

inline int qr(){
	register char ch; register bool sign=0; rg res=0;
	while(!isdigit(ch=getchar()))if(ch=='-')sign=1;
	while(isdigit(ch))res=res*10+(ch^48),ch=getchar();
	if(sign)return -res; else return res;
}

inline void prime(int x){ //线性筛素数
    for(rg i=2;i<=x;++i){
        if(!vis[i])pr[++tt]=i;
        for(rg j=1;j<=tt;++j){
            if(i*pr[j]>x)break;
			vis[i*pr[j]]=1;
            if(!(i%pr[j]))break;
        }
    }
}

//找到最大质因子小于p的数
//等效于我们构造小于p的质数所能构造的数
inline void dfs(int i,ll v){ //i是当前轮到的质数
	if(i>tt)return ; 
	dfs(i+1,v); //不用这个质数
	while(1){
		v*=pr[i]; //不断选用这个质数
		if(v>r)return ; //退出
		dfs(i+1,v);
		a[++n]=v; //记录这个数
	}
}

int main(){
	l=qr(); r=qr(); p=qr();
	prime(p); dfs(1,1); a[++n]=1; //预处理
	sort(a+1,a+n+1); f[1]=0;
	for(rg i=2;i<=n;++i) f[i]=101; //赋初值无穷大
	for(rg i=2;i<=p;++i){
		for(rg j=1,k=1;j<=n;++j){
			while(k<=n&&a[j]*i>a[k])++k; //因为a数组离散化，所以单调队列查找
			if(k>n)break; if(a[j]*i!=a[k])continue;
			f[k]=min(f[k],f[j]+1); //更新步数
			if(d[k]||f[k]+i>p||a[k]<l)continue; //注意第二个判断
			d[k]=1; ++ans; //步数在p范围内，计入答案
		}
	}
	printf("%d\n",ans);
	return 0;
}

```

---

## 作者：麻省理工学院 (赞：0)

我们发现$b ≤ p$，所以可以在a中出现的质因数一定不会超过p。搜索后可以发现$10^{9}$中只有不到300万个数满足要求。那么我们搜出所有≤R的数，接下来就可以DP了。
我们设$f[i][j]$表示b最少需要多少次$a = a * b$的操作使得$a=j$，那么转移方程也就十分显然了：

$f[i][j] = min(f[i-1][j], f[i][j / i])$

时间复杂度$O(pn)
$n是状态数

**Code**
```cpp
#include <cstdio>
#include <algorithm>
#define N 500010
#define ll long long
#define mem(x, a) memset(x, a, sizeof x)
#define mpy(x, y) memcpy(x, y, sizeof y)
#define fo(x, a, b) for (int x = (a); x <= (b); x++)
#define fd(x, a, b) for (int x = (a); x >= (b); x--)
#define go(x) for (int p = tail[x], v; p; p = e[p].fr)
using namespace std;
int L, R, p, pri[110], gs = 0, ans = 0;
int num[N * 6], tot = 0, f[N * 6];
bool tag[N * 6];

inline int read()
{
	int x = 0, f = 0; char c = getchar();
	while (c < '0' || c > '9') f = (c == '-') ? 1 : f, c = getchar();
	while (c >= '0' && c <= '9') x = (x << 1) + (x << 3) + (c ^ 48), c = getchar();
	return f ? -x : x;
}

void check(int x)
{
	for (int i = 2; i * i <= x; i++)
		if (x % i == 0) return;
	pri[++gs] = x;
}

void dfs(int x, int s, int fr)
{
	num[++tot] = s, f[tot] = p + 1;
	int yuan = tot;
	fo(i, x, gs)
		if ((ll)s * pri[i] <= R) dfs(i, s * pri[i], yuan);
}

int main()
{
	L = read(), R = read(), p = read();
	fo(i, 2, p) check(i);
	dfs(1, 1, 0), f[1] = 0;
	sort(num + 1, num + tot + 1);
	fo(i, 2, p)
	{
		int now = 1;
		fo(j, 1, tot)
		{
			if (f[j] > p) continue;
			while (now <= tot && num[now] != num[j] * i) now++;
			if (now > tot) break;
			f[now] = min(f[now], f[j] + 1);
			if (f[now] + i <= p && L <= num[now] && num[now] <= R && ! tag[now])
				tag[now] = 1, ans++;
		}
	}
	printf("%d\n", ans);
	return 0;
}
```



---

## 作者：傅思维666 (赞：0)


## 题解：

这是2019.10.16模拟赛的一道题。

一开始我发现，如果每次操作都加的话，那么操作数对应的答案都是可行的（这很显然）。但是这样肯定不会是答案，所以我们应该继续考虑一种情况：操作二，乘法运算。

然后我想到了整数的唯一分解定理：一个正整数可以被唯一分解成若干个质数的乘积。

这个思路紧紧地抓住了我的心//那么，对于一个数，我们肯定可以用算术基本定理把它分成若干个数的乘积，那么，如果这些数最大的那个和这些数的个数的和（最大的数+数的个数）比$p$小，那么这个数就是合法的。

证明是显然的：我们操作的过程是从1累加，每逢到了要作为$a$的质因子的数，就多用一次操作乘过去，这样，一直到了最后的质因子（也是最大的），就能乘出$a$。

这样就确定了我们的判定思路。但是如果暴力枚举的话，TLE是没跑的。

所以，我们进一步开始细细地琢磨怎么降低复杂度。

通过刚刚的讲解，我们发现，如果有一个数被唯一分解成若干个质数的乘积，并且其最大的质因子要比$p$还要大，那么这个数就根本不可能合法。

所以，我们发现，$b\le p$是必须的。所以，我们就可以通过线性筛选处理出$\le p$的所有质数，并且通过深搜来处理出所有能用这些质数表示出来（乘出来）的数。

这里简单说一下为什么要用深搜：根据算术基本定理，我们会有很多质数来乘成一个合数。而且，这些质数是可以重复的：也就是说，普通的循环遍历根本不会满足这样的要求，所以需要通过递归求解（即深搜）。

以上都是预处理部分，现在我们要检验这些数是否能在$\le p $的次数内出解。

~~（到这个地方本蒟蒻就不会了。模拟赛40分*￥%）~~

这个地方要用$DP$求解......

设$f[i] [j]$表示把第一元变成$i$，第二元变成$j$所用的操作二的最少次数。为什么这么设置呢？因为操作一作为加法，是可以直接计算出来的。而且，因为这样设置转移方程一定会导致爆空间，第二维（表示第二元）一定是要被滚动掉的。

所以，我们对深搜处理出的数列进行排序。外层枚举$2-p$，内层枚举$1-tot$（$tot$表示数列的长度），如果$i|a[j]$，则用单调队列指针寻找$i\times a[k]=a[j]$，这时就用$dp[k]$更新$dp[j]$，判断其加上数的个数（$i$）是否超过了$p$。



代码如下：（注意空间范围，不然会死得超级惨）

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#define ll long long
using namespace std;
const int maxp=3*1e6+1;
int l,r,p,ans;
bool v[maxp],vis[maxp];
int a[maxp],prime[maxp],dp[maxp],tot,cnt;
void euler(int n)
{
    cnt=0;
    for(int i=2;i<=n;i++)
    {
        if(!v[i])
            prime[++cnt]=i;
        for(int j=1;j<=cnt;j++)
        {
            if(i*prime[j]>=p)
                break;
            v[i*prime[j]]=1;
            if(i%prime[j]==0)
                break;
        }
    }
}
void scan(int x,int step)
{
    a[++tot]=x;
    for(int i=step;i<=cnt;i++)
    {
        if(prime[i]*(ll)x<=r)
            scan(prime[i]*x,i);
        else
            return;
    }
}
int main()
{
    scanf("%d%d%d",&l,&r,&p);
    euler(p-1);
    scan(1,1);
    sort(a+1,a+tot+1);
    memset(dp,0x3f,sizeof(dp)); 
    dp[1]=0;
    for(int i=2;i<=p;i++) 
    {
        int k=1;
        for(int j=1;j<=tot;j++) 
            if(a[j]%i==0)
            {
                while(a[k]*i<a[j]) 
                    k++;
                dp[j]=min(dp[j],dp[k]+1);
                if(dp[j]+i<=p) 
                    vis[j]=1;
            }
    }
    for(int i=1;i<=tot;i++) 
        if(vis[i] && a[i]>=l) 
            ans++;
    printf("%d",ans);
    return 0;
}
```

---

