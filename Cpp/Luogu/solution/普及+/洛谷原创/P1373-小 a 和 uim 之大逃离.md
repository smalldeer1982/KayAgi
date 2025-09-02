# 小 a 和 uim 之大逃离

## 题目背景

小 a 和 uim 来到雨林中探险。突然一阵北风吹来，一片乌云从北部天边急涌过来，还伴着一道道闪电，一阵阵雷声。刹那间，狂风大作，乌云布满了天空，紧接着豆大的雨点从天空中打落下来，只见前方出现了一个披头散发、青面獠牙的怪物，低沉着声音说：“呵呵，既然你们来到这，只能活下来一个！”。小 a 和他的小伙伴都惊呆了！


## 题目描述

瞬间，地面上出现了一个 $n\times m$ 的巨幅矩阵，矩阵的每个格子上有一坨 $0\sim k$ 不等量的魔液。

怪物各给了小 a 和 uim 一个魔瓶，说道，你们可以从矩阵的任一个格子开始，每次向右或向下走一步，从任一个格子结束。开始时小 a 用魔瓶吸收地面上的魔液，下一步由 uim 吸收，如此交替下去，并且要求最后一步必须由 uim 吸收。魔瓶只有 $k$ 的容量，也就是说，如果装了 $k+1$ 那么魔瓶会被清空成零，如果装了 $k+2$ 就只剩下 $1$，依次类推。

怪物还说道，最后谁的魔瓶装的魔液多，谁就能活下来。小 a 和 uim 感情深厚，情同手足，怎能忍心让小伙伴离自己而去呢？沉默片刻，小 a 灵机一动，如果他俩的魔瓶中魔液一样多，不就都能活下来了吗？小 a 和他的小伙伴都笑呆了！

现在他想知道他们都能活下来有多少种方法。

## 说明/提示

【题目来源】

lzn 改编

【样例解释】

样例解释：四种方案是：$(1,1)\to (1,2)$，$(1,1)\to (2,1)$，$(1,2)\to (2,2)$，$(2,1)\to (2,2)$。

【数据范围】

对于 $20\%$ 的数据，$n,m\leq 10$，$k\leq2$；

对于 $50\%$ 的数据，$n,m\leq 100$，$k\leq5$；

对于 $100\%$ 的数据，$1 \leq n,m\leq 800$，$1\leq k\leq 15$。


## 样例 #1

### 输入

```
2 2 3
1 1
1 1
```

### 输出

```
4
```

# 题解

## 作者：kkksc03 (赞：205)

By lzn
动态规划或者说是递推常规题。

f[i][j][p][q]表示他们走到(i,j)，且两人魔瓶内魔液量的差为p时的方法数。q=0表示最后一步是小a走的，q=1表示最后一步是uim走的。题目中说魔瓶的容量为k，实际上就是动归时p需要对k+1取余数，即p只有0~k，k+1种可能。答案为所有f[i][j][0][1]的和。

动归方程如下：（为了方便已经令k=k+1）

f[i][j][p][0]+=f[i-1][j][(p-mapp[i][j]+k)%k][1]   (i-1>=1)

f[i][j][p][0]+=f[i][j-1][(p-mapp[i][j]+k)%k][1]   (j-1>=1)

f[i][j][p][1]+=f[i-1][j][(p+mapp[i][j])%k][0]   (i-1>=1)

f[i][j][p][1]+=f[i][j-1][(p+mapp[i][j])%k][0]   (j-1>=1)

还有每个格子都有可能作为小a的起始格子，所以初始时对于所有i、j，f[i][j][mapp[i][j]][0]=1。

算法复杂度o(n\*m\*k)。


---

## 作者：SkyRainWind (赞：86)

这道题是真坑啊，先说一下思路：
```
// dp[i][j][h][l] 表示在点 (i,j)，差值为h，小A还是uim取液体的方案数(0-->小A 1-->uim) 
// dp[i][j][h][1]+=(dp[i-1][j][(h-a[i][j]+k)%k][0])	// uim取，差值就变小了
// dp[i][j][h][1]+=(dp[i][j-1][(h-a[i][j]+k)%k][0]
// dp[i][j][h][0]+=(dp[i-1][j][(h+a[i][j])%k][1]) // 小A取
// dp[i][j][h][0]+=(dp[i][j-1][(h+a[i][j])%k][1]) 
// 初始化：dp[i][j][a[i][j]][0]=1;		// 一开始小A可以从任意点开始 
```

然后就转化成一个简单dp就可以了，有几个坑点：
卡内存！例如，我的dp数组开的是
```dp[805][805][25][2]```，4个点MLE，换成
```dp[805][805][20][2]```就过了。

还有就是这道题不用开longlong，最后记录答案开个longlong就行了（我全没开longlong还过了），否则数组开个longlong，内存直接变两倍，呵呵。。。

代码：
```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <map> // STL
#include <string> 
#include <vector>
#include <queue>
#include <stack>
#define mpr make_pair
#define debug() puts("okkkkkkkk")

using namespace std;

typedef long long LL;

const int inf = 1 << 26;

// dp[i][j][h][l] 表示在点 (i,j)，差值为h，小A还是uim取液体的方案数(0-->小A 1-->uim) 
// dp[i][j][h][1]+=(dp[i-1][j][(h-a[i][j]+k)%k][0])	// uim取，差值就变小了
// dp[i][j][h][1]+=(dp[i][j-1][(h-a[i][j]+k)%k][0]
// dp[i][j][h][0]+=(dp[i-1][j][(h+a[i][j])%k][1])
// dp[i][j][h][0]+=(dp[i][j-1][(h+a[i][j])%k][1]) 
// 初始化：dp[i][j][a[i][j]][0]=1;		// 一开始小A可以从任意点开始 
int dp[805][805][20][2];
int n,m,k;
int a[805][805];
const int mod=(int)1e9+7;

int main(){
//	freopen("Luogu1373.in","r",stdin);
	scanf("%d%d%d",&n,&m,&k);++k;	// k+1会变成0，k不变 
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			scanf("%d",&a[i][j]);
			dp[i][j][a[i][j]%k][0]=1; 
		} 
	int ans=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			for(int h=0;h<=k;h++){
				dp[i][j][h][0]=(dp[i][j][h][0]+dp[i-1][j][(h-a[i][j]+k)%k][1])%mod;
				dp[i][j][h][0]=(dp[i][j][h][0]+dp[i][j-1][(h-a[i][j]+k)%k][1])%mod;
				dp[i][j][h][1]=(dp[i][j][h][1]+dp[i-1][j][(h+a[i][j])%k][0])%mod;
				dp[i][j][h][1]=(dp[i][j][h][1]+dp[i][j-1][(h+a[i][j])%k][0])%mod;
			}
		}
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)ans=(ans+dp[i][j][0][1])%mod;
	printf("%d\n",ans);

	return 0;
}
```

---

## 作者：桑梓暖阳 (赞：54)

确实是好题，下面几位说的不是太细，我来补充一下。（个人理解不一定精确，勿喷）

首先最直接想到的思路是用f[i][j][k][l][0/1] k和l分别表示走到i，j点时两个人的分数。0、1表示谁吸魔液。

但是这样需要枚举起点，4维再加两维，伤不起。。。。

于是乎微调思路，题目只求方案数，而答案只和差值有关，把分数记下来管什么用。。？而且同一个差值对应着多种情况转移而来，枚举所有差值解就是完全的了，起点枚举也免了！直接降为O（n\*m\*k），可以过了。

具体细节上，转移时差值可以是负的，这个问题让我头疼了很久（弱），平移数组？可是要模k的，不行。

最后想到，只要在正的差值中找到和它等价的，也就是模完后加上k就好了。

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn 810
#define mod 1000000007
using namespace std;
int n,m,K,ans,a[maxn][maxn];
int f[maxn][maxn][16][2];
int main(){
    scanf("%d%d%d",&n,&m,&K);K++;
    memset(f,0,sizeof(f));
    for(int i=1;i<=n;i++)
      for(int j=1;j<=m;j++){
          scanf("%d",&a[i][j]);
          f[i][j][a[i][j]%K][0]=1;
        }
    for(int i=1;i<=n;i++)
      for(int j=1;j<=m;j++)
        for(int h=0;h<K;h++){
            if(i+1<=n){
                f[i+1][j][(h+a[i+1][j])%K][0]=(f[i+1][j][(h+a[i+1][j])%K][0]+f[i][j][h][1])%mod;
                f[i+1][j][(h-a[i+1][j]+K)%K][1]=(f[i+1][j][(h-a[i+1][j]+K)%K][1]+f[i][j][h][0])%mod;
              }
            if(j+1<=m){
                f[i][j+1][(h+a[i][j+1])%K][0]=(f[i][j+1][(h+a[i][j+1])%K][0]+f[i][j][h][1])%mod;
                f[i][j+1][(h-a[i][j+1]+K)%K][1]=(f[i][j+1][(h-a[i][j+1]+K)%K][1]+f[i][j][h][0])%mod;
              }
            if(h==0)ans=(ans+f[i][j][h][1])%mod;
          }
    printf("%d\n",ans);
    return 0;
}

```

---

## 作者：torque (赞：18)

# P1373

### 传送门

题目$\rightarrow$[戳我](https://www.luogu.org/problem/P1373)

blog$\rightarrow$[戳我](https://www.luogu.org/blog/oneJURUO/p1373-xiao-a-hu-uim-zhi-tai-tao-li-ti-xie)
***
### 题意

背景挺长的，这里简述一下题意:

```
在n*m的矩阵中有若干个数，求出满足以下条件的路径数：
1.从起点到终点只能向右或向下走
2.从起点开始，第奇数个碰到的数字的和与第偶数个碰到的数
  字之和在模一个数的意义下相等
```
***
### 算法

#### 算法1：

考虑直接求解，枚举起点n*m，枚举终点n*m，枚举路径$2^{\frac{m+n}{2}}$，最终统计有多少条路径满足题意

而利用DP，可以优化路径

其中奇数个碰到的数加入集合1``即sum1+=x``

偶数个碰到的数加入集合2``即sum2+=x``

最终统计在 **模(k+1)** 的意义下同余

**注意是k+1，不清楚的同学可以再看看题意**

记dp[i][j][x][y][sum1][sum2][sta]为以(i,j)为起点，走到(x,y)处时差值为t，状态为sta的方案数(其中sta=0表示最后一步是奇数步，不能作为答案；sta=1表示是偶数步，可以作为答案)

${\forall}i,j,x,y,k,sum1,sum2,sta$，有``dp[i][j][x][y][(sum1?d[x][y])%t][(sum2??d[x][y])%t][sta]=dp[i][j][x-1][y][k][sta^1]+dp[i][j][x][y-1][k][sta^1]``，而``dp[i][j][x][y][d[i][i]][0][0]``初始化为1，其中t指的是题目中的k+1，``d[i][j]``代表第i行第j列的数字的值

当sta=0时，``?``处为‘+’,``??``处不加

当sta=1时，``??``处为‘-’，``?``处不加

这时候不要忘了取模以及对负数的处理

时间复杂度$O(n^2*m^2*k^2)$，预计得分20

#### 算法2：

考虑优化算法1

由于题目中说可以从任意处开始，而我们关注的只是终点时的状态，所以可以省去起点一维

用``dp[x][y][sum1][sum2][sta]``来进行转移

除了省去了i、j，转移方程同上

时间复杂度$O(n*m*k^2)$，预计得分95

#### 算法3：

顺着2的思路，我们注意到，题目只关心sum1与sum2的差值

在统计时，记``cha=sum1-sum2``(别忘了取模，由于同余性质，是可以随便取模的！)

当sum1中加入元素x，cha+=x

当sum2中加入元素x，cha-=x

上面两个加减应该是可以互换位置的，这么做就优化掉了一维k~~尽管它很小~~

在最后我们重新整理一下DP转移方程:

```cpp
dp[x][y][(k+d[x][y])%t][0]+=dp[x-1][y][k][1]
dp[x][y][(k+d[x][y])%t][0]+=dp[x][y-1][k][1]
dp[x][y][(k-d[x][y])%t][1]+=dp[x-1][y][k][0]
dp[x][y][(k-d[x][y])%t][1]+=dp[x][y-1][k][0]
```

至于负数怎么处理，方程中没有给出，读者不妨思考一下
~~读者自证不难~~

所有``dp[x][y][d[x][y]%t][0]``初始化为1，答案为$\sum_{x=1}^n{\sum_{y=1}^m{dp[x][y][0][1]}}$

时间复杂度$O(n*m*k)$,预计得分100
***
### 代码
```cpp
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#define N 801
#define MOD 1000000007
#define rnt register int
using namespace std;
int n,m,t,x,ans,f[N][N][16][2];
signed main(){
	scanf("%d%d%d",&n,&m,&t);t=-~t;
	for(rnt i=1;i<=n;i=-~i) for(rnt j=1;j<=m;j=-~j){
		scanf("%d",&x);
		f[i][j][x%t][0]=1;
		for(rnt k=0;k<t;k=-~k){
			if(i!=1){
				f[i][j][((k-x)%t+t)%t][1]+=f[i-1][j][k][0];
				f[i][j][((k-x)%t+t)%t][1]%=MOD;
				f[i][j][((k+x)%t+t)%t][0]+=f[i-1][j][k][1];
				f[i][j][((k+x)%t+t)%t][0]%=MOD;
			}
			if(j!=1){
				f[i][j][((k-x)%t+t)%t][1]+=f[i][j-1][k][0];
				f[i][j][((k-x)%t+t)%t][1]%=MOD;
				f[i][j][((k+x)%t+t)%t][0]+=f[i][j-1][k][1];
				f[i][j][((k+x)%t+t)%t][0]%=MOD;
			}
		}
		ans=(ans+f[i][j][0][1])%MOD;
	}
	return printf("%d",ans),0;
}
```

### 写在后面

你以为这就完了？

当我终于调出了正确代码时，自信提交

80分

为神马？

在这里友情提醒各位，这道题卡常，容易MLE以及TLE（为甚我会T？？？）

改正方法

1.数组开小：dp[801][801][16][2]

2.**别开long long！！！**
***
### 看完可以留个赞证明你来过

---

## 作者：马必辰 (赞：14)

这道题是一个DP，具体的DP方法底下已经说了，这里不多说，主要讲几个题目的坑点。

1.用int就足够了，用long long有可能爆空间（当然你可以用循环数组）。

2.因为k+1时才会被清空成零，所以模数为k+1。

3.魔液量大于k+1无意义，一开始直接去模（有20分包含这种情况）。

下面是代码，看不懂可以私信我。

```cpp
#include<cstdio>
int a,b,c,d,e,f,i,m,n,x[850][850]={0},w[850][850][20][2]={0},y=1000000007; 
int main()
{
scanf("%d%d%d",&a,&b,&c);
c++;
for(i=1;i<=a;i++)
{
    for(m=1;m<=b;m++)
    {
        scanf("%d",&x[i][m]);
        x[i][m]%=c;
        w[i][m][x[i][m]][1]++;
    }
}
d=0;
for(i=a;i>=1;i--)
{
    for(m=b;m>=1;m--)
    {
        for(n=0;n<c;n++)
        {
            e=(n-x[i][m]+c)%c;
            w[i][m][n][1]+=w[i+1][m][e][0];
            w[i][m][n][1]%=y;
            w[i][m][n][1]+=w[i][m+1][e][0];
            w[i][m][n][1]%=y;
            e=(n+x[i][m])%c;
            w[i][m][n][0]+=w[i+1][m][e][1];
            w[i][m][n][0]%=y;
            w[i][m][n][0]+=w[i][m+1][e][1];
            w[i][m][n][0]%=y;
        }
        d+=w[i][m][0][0];
        d%=y;
    }
}
printf("%d\n",d);
}
```

---

## 作者：我要考北大 (赞：5)

这篇题解重点讨论差值为负数的情况
----

我把所有2019.11.4之前的题解都看了一边


一
---
最后想到，只要在正的差值中找到和它等价的，也就是模完后加上k就好了。

作者: 桑梓暖阳    https://www.luogu.org/blog/user22461/solution-p1373





二
---

 读者自证不难
 
 作者: 六道仙人  https://www.luogu.org/blog/oneJURUO/p1373-xiao-a-hu-uim-zhi-tai-tao-li-ti-xie
 
 
 三
 ----
 需要考虑差值小于0的情况，这时将插值替代为模k + 1意义下的等价元就行了。 
 
 作者: Minagami_Yuki   
 
 https://www.luogu.org/blog/Minagami-Yuki/ti-xie-p1373-xiao-a-hu-uim-zhi-tai-tao-li   
 
 他的博客挂了
 
 
 四
 ---
 
 
觉得需要引入负下标，于是用了一个小技巧，弄了一个有负下标的数组。虽然在本题中很蠢



```cpp

long long a[2][805][31], map[805][805], b[2][805][31];
long long *d[2][805], *bak[2][805], sum;
int N, M, K;

void prepare()
{
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 805; j++)
        {
            d[i][j] = a[i][j] + 15;
            bak[i][j] = b[i][j] + 15;
        }
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));
}
```


作者: 杜岱玮 更 https://www.luogu.org/blog/davidblog/solution-p1373


五
---

关于差值问题：


有人说差值可正可负，我当时也考虑了一段时间，后来发现在%k意义下对答案没有任何影响，即 k = 3时，（k + 1等于4时）a比b少2和a比b多2其实是等效的，即a拿2个后两人均相同  

作者: Leowner

https://www.luogu.org/blog/user11829/solution-p1373




个人认为
----

一直接给结论

二太高估读者

三跟一一样

四的想法不错

五的假设，数据范围太小


思考
---

我认为f[i][j][0/1][h] 代表0比1多h

假设瓶子k=12


目前差值是5

下一个让1捡

那么差值会变小

mark
------

假设1捡6

差值变成-1

下一次让0捡2

差值变成 1




但是负数要处理，像四大佬的想法很好

处理
------
从mark开始停住

让差值加上（k+1）

差值变成11

下一次让0减2

差值变成1


所以，把负数加上k+1
---

和负数本身所作用效果一样
---









 

---

## 作者：Martian148 (赞：3)

这道题显然就是动态规划，主要是怎么定义，我们发现定义每个人的拿的魔液坑定会爆内存，但我们每次关注差值，就那差值定义就好了。

定义F[i][j][k][0/1]表示收集了第(i,j)这个格子的魔液小a和uim的差值，0表示这一下是小a取的，1表示这一下是uim取的

我们要减去这个格子的魔液就能得到上一次的差值（当然可能减的是负的就是加了）

于是转移方程就出来了
F[i][j][k][0]=(F[i][j][k][0]+F[i-1][j][(k-a[i][j]+K)%K][1])%TT;
F[i][j][k][0]=(F[i][j][k][0]+F[i][j-1][(k-a[i][j]+K)%K][1])%TT;
F[i][j][k][1]=(F[i][j][k][1]+F[i-1][j][(k+a[i][j])%K][0])%TT;
F[i][j][k][1]=(F[i][j][k][1]+F[i][j-1][(k+a[i][j])%K][0])%TT;

初始就是第一次是小a取的差值就是当前格子的魔液值:
F[i][j][a[i][j]][0]=1;

答案就是将每个差值为0而最后一下是uim取的累计上
ans=(ans+F[i][j][0][1])%TT;

### code
```cpp
#include<bits/stdc++.h>
using namespace std;
int N,M,F[805][805][20][2],a[805][805],K,ans;
const int TT=1000000007;
inline int read(){
	int ret=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();}
	while(ch<='9'&&ch>='0')ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}

int main(){
	N=read();M=read();K=read()+1;
	for(int i=1;i<=N;i++)
	for(int j=1;j<=M;j++)a[i][j]=read()%K,F[i][j][a[i][j]][0]=1;
	for(int i=1;i<=N;i++)
	for(int j=1;j<=M;j++)
	for(int k=0;k<K;k++){
		F[i][j][k][0]=(F[i][j][k][0]+F[i-1][j][(k-a[i][j]+K)%K][1])%TT;
		F[i][j][k][0]=(F[i][j][k][0]+F[i][j-1][(k-a[i][j]+K)%K][1])%TT;
		F[i][j][k][1]=(F[i][j][k][1]+F[i-1][j][(k+a[i][j])%K][0])%TT;
		F[i][j][k][1]=(F[i][j][k][1]+F[i][j-1][(k+a[i][j])%K][0])%TT;
	}
	for(int i=1;i<=N;i++)
	for(int j=1;j<=M;j++)
		ans=(ans+F[i][j][0][1])%TT;
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：huiwang17 (赞：2)

听说这题卡空间？

机智的我开了动态数组~~~

做法都差不多，就是令$f[i][j][k][q]$ 表示走到点$(i, j)$时两人的差是k，最后一步是q（表示小A或者UIM）走的时的方案数。那么差为负数的情况怎么办呢？注意到这个瓶子是一个自动清零的瓶子，所以负数直接加上$k + 1$就可以了。

转移方程比较简单啦，就是可以从左边或者上面更新过来嘛~~
$$f[i][j][dif][0] += f[i-1][j][x][1] + f[i][j-1][x][1] $$
$$f[i][j][dif][1] += f[i-1][j][y][0] + f[i][j-1][y][0] $$

注意每一步都要取模哦~~

初始情况想了比较久，因为这题是可以从任意点出发，任意点结束，所以得把第一步初始化好，也就是令$f[i][j][a[i][j]][0] = 1$, 代表第一步小A走完造成$a[i][j]$的差值。

```cpp
#include <iostream>
#include <cstdio>

using namespace std;
#define ll long long
const int MAXN = 5e5 + 7;
const int INF = 2.1e9;
const int mod = 1e9 + 7;

int n, m, k;
int a[805][805];

int main(){
    cin >> n >> m >> k;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            cin >> a[i][j];
    int f[n+5][m+5][k+1][2]; //first a, then uim
    memset(f, 0, sizeof(f)); //在main函数里面开数组记得清零哦
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            f[i][j][a[i][j]][0] = 1;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            for(int dif = 0; dif < k + 1; dif++){
                int x = dif - a[i][j];
                if(x < 0)
                    x += k + 1;
                f[i][j][dif][0] += ((f[i-1][j][x][1] % mod) + (f[i][j-1][x][1] % mod)) % mod ;
                int y = dif + a[i][j];
                if(y > k)
                    y -= k + 1;
                f[i][j][dif][1] += ((f[i-1][j][y][0] % mod) + (f[i][j-1][y][0] % mod)) % mod;
                //printf("### f[%d][%d][%d][%d] = %d\n", i, j, dif, 0, f[i][j][dif][0]);
                //printf("### f[%d][%d][%d][%d] = %d\n", i, j, dif, 1, f[i][j][dif][1]);
            }
    ll ans = 0;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            ans += f[i][j][0][1], ans %= mod;
    cout << ans << endl;

}

```


---

## 作者：Leowner (赞：2)

#良心题解：


本地写的github式的markdown，不清楚luogu上的显示如何，，


# 洛谷 1373 dp

这题还不算太难，，当初看的时候不是很理解题意，以为他们会选择两条不同的路径，导致整体思路混乱


***

[传送门](https://www.luogu.org/problem/show?pid=1373)


***

其实理解题意和思路之后还是敲了不短的时间，一部分身体原因再加上中午休息不太好，整个人思路较乱，靠本能打了一遍代码毫无头绪。恢复了一下状态重新开打，才算是A掉


###题解


设dp[i][j][l][p]为当前走到第(i, j)位，当前(a - b) % k 为l，本次是第p个人取得药，p = 0为a，p = 1 为b，

此时的方案数


> 则  dp[i][j][l][1] += dp[i-1][j][((l + a[i][j]) % k + k) % k][0] + dp[i][j-1][((l + a[i][j]) % k + k) % k][0]

> dp[i][j][l][0] += dp[i-1][j][((l - a[i][j]) % k + k) % k][1] + dp[i][j-1][((l - a[i][j]) % k + k) % k][1]

####举个栗子：


假设本次在(3, 2)，该1(uim)走，则该状态的上一个状态应为 ``` 当前在(3,1)，该0(小a)走，当时的差为l + a[i][j] ``` 另一个状态同理。

####解释一下差加减的原理：
我们的dp方程的第三维定义的是a(小a) - b(uim)的差，那么按照上面的栗子来看，本步由uim来走，那么它们状态的差应减少，减少值为a[i][j]，所以上一状态为l + a[i][j]，

####扯一点关于初始化的东西

由于题目中规定可以从每个点开始，同时必须小a先吸收，所以

> 对于读入的每一个a[i][j]，设dp[i][j][a[i][j] % k][0] = 1

> 其余点均为0

####关于k

~~实在有些不理解出题人的脑洞，，(lzn别打我= =)，~~，只有k的容量，到了k+1就会清零，，，默默地k++吧

####关于复杂度

记录两个人的当前值肯定会T，使用long long会M，据说常数太大会卡两个，暂时没发现

####关于差值问题：

有人说差值可正可负，我当时也考虑了一段时间，后来发现在%k意义下对答案没有任何影响，即 k = 3时，**（k + 1等于4时）**a比b少2和a比b多2其实是等效的，即a拿2个后两人均相同

代码如下：
``` cpp




```cpp
[安利一下我的博客](http://www.cnblogs.com/CtsNevermore/)
```
#include <cstdio>
#include <cstring>
#include <algorithm>
const int maxn = 800 + 1;
const int mod = 1000000007;
int dp[maxn][maxn][16][2];
int a[maxn][maxn];
int n, m, k;
int main () {
    scanf("%d %d %d", &n, &m, &k);
    k++;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &a[i][j]);
            dp[i][j][(a[i][j]) % k][0] = 1;
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            for (int l = 0; l < k; l++) {
                dp[i][j][l][1] = (dp[i][j][l][1] + dp[i-1][j][((l + a[i][j]) % k + k) % k][0] + dp[i][j-1][((l + a[i][j]) % k + k) % k][0]) % mod;
                dp[i][j][l][0] = (dp[i][j][l][0] + dp[i-1][j][((l - a[i][j]) % k + k) % k][1] + dp[i][j-1][((l - a[i][j]) % k + k) % k][1]) % mod;
            }
        }
    }
    long long ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            ans = (ans + dp[i][j][0][1]) % mod;
        }
    printf("%lld", ans);
    return 0;
}

```cpp

---

## 作者：ShuKuang (赞：1)

计数DP

**状态表示:** 


f[i][j][k][2] -> 坐标为 i,j 的点 0，1分别表示2个人

k表示两个人的差

因为最终计数的答案数量是两个人和相等的时候，那么可以压

所掉一位，那么可以设k为两个人的差，最后输出差为0的即可

**状态表示到i,j这个点时，两个人差为k的方案总数**

**状态转移:**

```
inline int mod(int x){
	return (x + k) % k;//k如题意
}

f[i][j][x][0] += (f[i-1][j][mod(x-a[i][j])][1] + f[i][j-1][mod(x+a[i][j])[1]) % MOD;

```
f[j][j][x][1] 道理是一样的.

转移的时候因为这两个人是交替着走的，所以当前这个状态

转移的时候是上一个位置转移过来的，所以0和1转移时加上

的时反的。

另外x这一位在计算的时候默认时1号-2号，所以有的是x-a[i][j],此时就是1号加上了那么多，差相当于1号没有走到这里时的那个量，可以好好体会一下。

```
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>

using namespace std;
const int MOD = 1e9+7;
const int N = 803;

int n,m,k,ans;
int a[N][N];
int f[N][N][20][2];

int mod(int x){
    return (x + k) % k;
}

int main(){
	cin >> n >> m >> k;
    k++; 
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= m;j++){
			cin >> a[i][j];
            a[i][j] %= k;
            f[i][j][a[i][j]][0] = 1;
		}
	}	
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= m;j++){
            for(int x = 0;x < k;x++){
            f[i][j][x][0] = (f[i][j][x][0] + f[i-1][j][mod(x-a[i][j])][1] + f[i][j-1][mod(x-a[i][j])][1]) % MOD;
            f[i][j][x][1] = (f[i][j][x][1] + f[i-1][j][mod(x+a[i][j])][0] + f[i][j-1][mod(x+a[i][j])][0]) % MOD;
            }
		}	
	}
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= m;j++){
			(ans += f[i][j][0][1] ) %= MOD;
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```






---

## 作者：crashed (赞：1)

# 分析：
该题也就是在设计状态上面需要懂点脑筋。  
简单来看，这道题就是一个基础DP的背景上面加点东西。  
所以我们就可以第一种定义状态:  
$ DP( i, j, a, b, 0/1 )$ ： 一行人走到$( i, j )$格子上后，小$a$拥有$a$的魔液，$uim$拥有$b$的魔液，并该格子上的魔液被小$a$/$uim$吸走($0\rightarrow $小$a$；$1\rightarrow uim$)  
状态转移很简单，可以参考过河卒：  
（其中$liq( i, j )$表示$( i, j )$格子上面的魔液量）   
$ DP( i, j, a, b, 0 ) = DP( i - 1, j, a - liq( i, j ), b, 1 ) + DP( i, j - 1, a - liq( i, j ), b, 1 )  $
$ DP( i, j, a, b, 1 ) = DP( i - 1, j, a, b - liq( i, j ), 0 ) + DP( i, j - 1, a, b - liq( i, j ), 0 )$  
答案的计算：  
$ans = \sum_{i=1}^N{\sum_{j=1}^M {\sum_{k=0}^K DP( i, j, k, k, 1 ) } } $
# 优化：
But，这样暴力地计算，时间和空间上都不好看，破亿了。   
而转移方程又没有什么明显的性质可以用于优化，所以我们得从状态入手。  
经过重新审题我们发现，该题主要考虑的是魔液量的差，而两者手中分别拿着多少魔液，我们并不在意。  
所以重新定义状态：  
$DP( i, j, a, 0/1 )$ ：一行人走到$( i, j )$格子上后，小$a$和$uim$手中魔液量的差为$a$（向$k+1$取过模），并该格子上的魔液被小$a$/$uim$吸走( $0\rightarrow$小$a$；$1\rightarrow uim$ )  
状态转移稍微改改：  
$DP( i, j, a, 0 ) = DP( i - 1, j, a - liq( i, j ), 1 ) + DP( i, j - 1, a - liq( i, j ), 1 )$  
$DP( i, j, a, 1 ) = DP( i - 1, j, a + liq( i, j ), 0 ) + DP( i, j - 1, a + liq( i, j ), 0 )  $
（注意a的取模）  
答案：  
$ans = \sum_{i=1}^N{\sum_{j=1}^M DP( i, j, 0, 1 ) }$  
时间复杂度：$O( N * M * K )$   
空间复杂度：$O( N * M * K )$  
# 代码:
```cpp
#include <cstdio>

const int MAXN = 805, MAXM = 805, MAXK = 20, mod = 1000000007;

template<typename _T>
void read( _T &x )
{
	x = 0;char s = getchar();int f = 1;
	while( s > '9' || s < '0' ){if( s == '-' ) f = -1; s = getchar();}
	while( s >= '0' && s <= '9' ){x = ( x << 3 ) + ( x << 1 ) + ( s - '0' ), s = getchar();}
	x *= f;
}

template<typename _T>
void write( _T x )
{
	if( x < 0 ){ putchar( '-' ); x = ( ~ x ) + 1; }
	if( 9 < x ){ write( x / 10 ); }
	putchar( x % 10 + '0' );
}

int DP[MAXN][MAXM][MAXK][2];
int liq[MAXN][MAXM];
//存储魔液量 
int N, M, K;

int fix( const int a )
{
	return ( a % ( K + 1 ) + K + 1 ) % ( K + 1 );
}

int main()
{
	read( N ), read( M ), read( K );
	for( int i = 1 ; i <= N ; i ++ )
	{
		for( int j = 1 ; j <= M ; j ++ )
		{
			read( liq[i][j] );
			DP[i][j][liq[i][j]][0] = 1;
		}
	}
	for( int i = 1 ; i <= N ; i ++ )
	{
		for( int j = 1 ; j <= M ; j ++ )
		{
			for( int a = 0 ; a <= K ; a ++ )
			{
				DP[i][j][a][0] = ( DP[i][j][a][0] + ( DP[i - 1][j][fix( a - liq[i][j] )][1] + DP[i][j - 1][fix( a - liq[i][j] )][1] ) % mod ) % mod;
				DP[i][j][a][1] = ( DP[i][j][a][1] + ( DP[i - 1][j][fix( a + liq[i][j] )][0] + DP[i][j - 1][fix( a + liq[i][j] )][0] ) % mod ) % mod;
				//注意不要把当前格子上的可能步数清掉了，是累加 
			}
		}
	}
	int res = 0;
	for( int i = 1 ; i <= N ; i ++ )
	{
		for( int j = 1 ; j <= M ; j ++ )
		{
			res = ( res + DP[i][j][0][1] ) % mod;
		} 
	}
	write( res ), putchar( '\n' );
	return 0;
}
```

---

## 作者：Minakami_Yuki (赞：1)

[更好的阅读体验](https://zgjjj.github.io/2019/06/11/Luogu-P1373-%E5%B0%8Fa%E5%92%8Cuim%E4%B9%8B%E5%A4%A7%E9%80%83%E7%A6%BB-%E8%A7%A3%E9%A2%98%E6%8A%A5%E5%91%8A/)

# 题目链接

[**P1373** 小a和uim之大逃离](https://www.luogu.org/problemnew/show/P1373)

# 题意简述

~~感觉题目描述挺清楚的~~

给定矩阵，两个人以任意点为起点，每次可以向下走或向右走，同时两人的得分**交替**加上当前格的值并对$k + 1$取模，可以在任意点由**后者**结束。求两人得分一致的方法数。

<!--more-->

# 解题思想

题目中的方案数与两人的**具体得分**无关，故我们考虑将每一步**两人的差值**作为状态。剩下的状态显而易见：当前位置和取数人。即$dp[x][y][\Delta][op]$表示在坐标为$(x, y)$的方格上由$op$取数，**取完后**两人的差值为$\Delta$

因为由后者结束，所以我们只统计$op = 0$时的答案，并累加。再加上题目中给出的移动方式，我们不难得出状态转移方程：

$$dp[x][y][\Delta][0] = dp[x - 1][y][\Delta - a[x][y]][1] + dp[x][y - 1][\Delta - a[x][y]][1]$$

$$dp[x][y][\Delta][1] = dp[x - 1][y][\Delta + a[x][y]][0] + dp[x][y - 1][\Delta + a[x][y]][0]$$

需要考虑差值小于0的情况，这时将插值替代为模$k + 1$意义下的等价元就行了。

# 参考代码

```cpp
#include <cstdio>

const int N = 801;
const int MOD = 1000000007;

int n, m, k, ans;
int a[N][N];
int dp[N][N][17][2];

int main() {
    scanf("%d%d%d", &n, &m, &k);
    k++;
    for(register int i = 1; i <= n; i++) {
        for(register int j = 1; j <= m; j++) {
            scanf("%d", &a[i][j]);
            dp[i][j][a[i][j] % k][0] = 1;
        }
    }
    for(register int i = 1; i <= n; i++) {
        for(register int j = 1; j <= m; j++) {
            for(register int del = 0; del <= k; del++) {
                dp[i][j][del][0] = (dp[i][j][del][0] + dp[i - 1][j][(del - a[i][j] + k) % k][1]) % MOD;
                dp[i][j][del][0] = (dp[i][j][del][0] + dp[i][j - 1][(del - a[i][j] + k) % k][1]) % MOD;
                dp[i][j][del][1] = (dp[i][j][del][1] + dp[i - 1][j][(del + a[i][j] + k) % k][0]) % MOD;
                dp[i][j][del][1] = (dp[i][j][del][1] + dp[i][j - 1][(del + a[i][j] + k) % k][0]) % MOD;
            }
        }
    }
    for(register int i = 1; i <= n; i++) {
        for(register int j = 1; j <= m; j++) {
            ans = (ans + dp[i][j][0][1]) % MOD;
        }
    }
    printf("%d", ans);
    return 0;
}
```



---

## 作者：李寻欢 (赞：1)

这是一道DP题,大家应该都可以看出来。这题是与地图有关的，所以我的f数组首先带上坐标。

再看k是<=15,所以我的第一个f数组是五维的f[i][j][k][l][1/0],代表在第(i,j)的位置第一个人有k个，第二个人有l个,0是第一个人选，1是第二个人选；的方案数，但是显然时空复杂度都不能接受。

我们再看题目，最终是否是我们的答案只与相对大小有关，所以我们把第三维和第四维合并为两人相差了多少，第一个人捡就加，第二个人捡就减，然后从前往后转移即可。

最后贴上代码:~~~


```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 805
#define K 16
#define mod 1000000007
using namespace std;
int n,m,k,f[N][N][K][2],ans,Map[N][N];
int read()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
int main()
{
	n=read();m=read();k=read();
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			Map[i][j]=read(),f[i][j][Map[i][j]][0]=1;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			for(int l=0;l<=k;++l)
			{
				f[i][j][l][0]=(ll)(f[i][j][l][0]+f[i][j-1][(l-Map[i][j]+k+1)%(k+1)][1])%mod;
				f[i][j][l][0]=(ll)(f[i][j][l][0]+f[i-1][j][(l-Map[i][j]+k+1)%(k+1)][1])%mod;
				f[i][j][l][1]=(ll)(f[i][j][l][1]+f[i][j-1][(l+Map[i][j])%(k+1)][0])%mod;
				f[i][j][l][1]=(ll)(f[i][j][l][1]+f[i-1][j][(l+Map[i][j])%(k+1)][0])%mod;
			}
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			ans=(ans+f[i][j][0][1])%mod;
	printf("%d\n",ans);
	return 0;
}
```
我代码丑，各位老爷将就着看吧~~~



---

## 作者：I_AM_HelloWord (赞：1)

洛谷是不是时限给的有点问题，感觉评测器可能是只有0.5s就T。

随手加了个memset就T了一个点，然后删掉那个0.4s就跑过去了，管理员能解释一下么。

好吧，说正事，讲讲这个题吧。

楼下说的对，这题跟多米诺骨牌那题思想是一样的。

我们考虑一个简单的二维dp[i][j][0]表示第一个人走到i，j和第二个人最小的差值的方案数，dp[i][j][1]同理，

那么很显然，这个差值由于了绝对值和模k意义而存在了后效性，即当前的选择的最优性会受到后面选择的影响。

所以这个dp是行不通的。

我们在dp中有个很著名的恒等变换（手动滑稽），就是 求最值=判断最值的可行性

我们可以考虑给这个dp加一维，表示走到当前位置是他们的差值，那么此时dp就是没有后效性的了，而我们求结果就可以直接输出差值为0的方案数就好了，如果是求最小差值的方案数，顺序枚举一下差值看看是否有方案数即可。

考虑一下具体的dp过程吧。

dp[i][j][h][0]+=dp[i-1][j][(h-a[i][j]+k)%k][1]+dp[i][j-1][(h-a[i][j]+k)%k][1];

dp[i][j][h][1]+=dp[i-1][j][h+a[i][j]%k][0]+dp[i][j-1][h+a[i][j]%k][1];

再mod一个10^9+7就好了。

注意一个小点，题目说的是到k+1的时候才变为0，所以读入k后要k++

方法和楼下dalao大同小异，仅供参考。

参考代码：

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int Mod=1000000007;
template<class T>inline void Inc(T &a,int b){(a+=b)%=Mod;}
const int N=810;
int n,m,k;
int a[N][N],dp[N][N][20][2];
int main(){
    scanf("%d%d%d",&n,&m,&k);k++;
    for (int i=1;i<=n;i++)
        for (int j=1;j<=m;j++){
            scanf("%d",&a[i][j]);
            dp[i][j][a[i][j]%k][0]=1;
        }
    for (int i=1;i<=n;i++)
        for (int j=1;j<=m;j++)
            for (int h=0;h<=k;h++){
                Inc(dp[i][j][h][0],dp[i-1][j][(h-a[i][j]+k)%k][1]+dp[i][j-1][(h-a[i][j]+k)%k][1]);
                Inc(dp[i][j][h][1],dp[i-1][j][(h+a[i][j])%k][0]+dp[i][j-1][(h+a[i][j])%k][0]);
            }
    long long ans=0;
    for (int i=1;i<=n;i++)
        for (int j=1;j<=m;j++)
            Inc(ans,dp[i][j][0][1]);
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：loceaner (赞：1)

## 思路

### 怎么做

一道$DP$~~不~~好题.

我们用$f[i][j][q][p]$来表示：走到第$i$行第$j$列魔液差距值为$q$且当前为$p$走的方案数（$p\in \{0, 1\} p=0$表示目前为小$a$走，$p=1$表示目前为$uim$走)

初始条件：$f[i][j][a[i][j]][0]=1$表示小$a$从每个点开始取，差距值为$a[i][j]$的方案数为$1$

那么我们可以想出转移方程：

$$f[i][j][p][0]+=f[i-1][j][p-a[i][j]][1]+f[i][j-1][p-a[i][j]][1]$$

这个式子表示目前在第$i$行第$j$列，差距值为$p$，当前小$a$走的方案数，因为只能往右走或往下走，且上一步一定是$uim$走的，所以可以从第$i-1$行第$j$列、第$i$行第$j-1$列转移过来，差距值增大

$$f[i][j][p][1]+=f[i-1][j][p+a[i][j]][0]+f[i][j-1][p-a[i][j]][0]$$

同理，这个式子表示目前在第$i$行第$j$列，差距值为$p$，当前$uim$走的方案数，上一步一定是小$a$走的，所以可以从第$i-1$行第$j$列、第$i$行第$j-1$列转移过来，差距值减小

我们~~容易~~想出，最后的答案就是$\sum_{i = 1}^{n}\sum_{j = 1}^{m}f[i][j][0][1]$最后一维是$1$是因为最后一步只能由$uim$走

**空间复杂度$n*m*k*2$刚好可以，时间复杂度$O(n*m*k)$可以过**

### 注意！

1. 因为魔液值到达$k+1$之后就会清$0$，所以在过程中要随时对$k+1$取模
2. 空间开好！！不要开太大！因为最后一维只用$0、1$，所以开$2$的数组就好了就行了，开$3$会$MLE$
3. 码风丑陋，谨慎阅读$qwq$

## 代码

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int B = 20;
const int A = 800 + 7;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

inline int read() {
	char c = getchar(); int x = 0, f = 1;
	for( ; !isdigit(c); c = getchar()) if(c == '-') f = -1;
	for( ; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
	return x * f;
}

int n, m, k, a[A][A], f[A][A][B][2];

int main() {
	n = read(), m = read(), k = read() + 1;
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) a[i][j] = read(), f[i][j][a[i][j] % k][0] = 1;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			for(int p = 0; p <= k; p++) {
				f[i][j][p][0] = (f[i][j][p][0] + f[i - 1][j][(p - a[i][j] + k) % k][1] + f[i][j - 1][(p - a[i][j] + k) % k][1]) % mod;
				f[i][j][p][1] = (f[i][j][p][1] + f[i - 1][j][(p + a[i][j] + k) % k][0] + f[i][j - 1][(p + a[i][j] + k) % k][0]) % mod;
			}
	int ans = 0;
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) ans += f[i][j][0][1], ans %= mod;
	cout << ans << '\n';
	return 0;
}
```

---

## 作者：荀令君 (赞：1)

本蒟蒻的第一篇题解

------------
上来看到这个题，自然的想到一个四维做法，但状态的设置方面有些巧妙
##  状态： 
### 设dp[i][j][h][0]表示差值为h小a走到(i,j)时的方案数                                                                                     dp[i][j][h][1]表示差值为 h Uim走到(i,j)时的方案数
## 转移：
        dp[i][j][h][0]=(dp[i][j][h][0]+dp[i-1][j][(h-a[i][j]+k)%k][1])%mod;
	  	dp[i][j][h][0]=(dp[i][j][h][0]+dp[i][j-1][(h-a[i][j]+k)%k][1])%mod;
	  	dp[i][j][h][1]=(dp[i][j][h][1]+dp[i-1][j][(h+a[i][j])%k][0])%mod;
	  	dp[i][j][h][1]=(dp[i][j][h][1]+dp[i][j-1][(h+a[i][j])%k][0])%mod;
 
## 结果:
 ### 结果要注意结束点可能在任意一格，所以任意差值为0的方案都是独立的，需要相加。
 
程序见bloghttps://www.luogu.org/blog/sfloyd666/post-1353-post

---

## 作者：Adove (赞：1)

这里我来介绍一种常用的滚动数组优化方式，相对于楼下的滚动数组，这种方式只需要对数组赋一次值就够了，空间开销相当小，跑得算比较快的（但还是不如dsq快%%%%%

这里用到了位运算，针对行数的奇偶性进行滚动

上代码↓

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int MAXN=805,MOD=1e9+7;

int n,m,mod,ans,x;
int f[2][MAXN][16][2];

inline int read(){
	int x=0;char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return x;
}

int main(){
	scanf("%d%d%d",&n,&m,&mod);++mod;
	for(register int i=1;i<=n;++i){
		for(register int j=1;j<=m;++j){
			x=read();
			for(register int k=0;k<mod;++k) f[i&1][j][k][1]=f[i&1][j][k][0]=0;
			f[i&1][j][x][1]=1;
			for(register int k=0;k<mod;++k){
				int tmp1=(k-x+mod)%mod,tmp2=(k+x)%mod;
				int cmp1=f[i&1^1][j][k][1]+f[i&1][j-1][k][1],cmp2=f[i&1^1][j][k][0]+f[i&1][j-1][k][0];
				if(cmp1>=MOD) cmp1-=MOD;
				if(cmp2>=MOD) cmp2-=MOD;
				f[i&1][j][tmp1][0]+=cmp1;
				f[i&1][j][tmp2][1]+=cmp2;
				if(f[i&1][j][tmp1][0]>=MOD) f[i&1][j][tmp1][0]-=MOD;
				if(f[i&1][j][tmp2][1]>=MOD) f[i&1][j][tmp2][1]-=MOD;
			}ans+=f[i&1][j][0][0];
			if(ans>=MOD) ans-=MOD;
		}
	}printf("%d\n",ans);
	return 0;
} 
```

---

## 作者：junyaoren (赞：0)

一开始用典型的4维dp，dp[n+1][m+1][k+1][2]; dp[r][c][i] 表示以 （r, c）为终点，最后diff(a - umi) = i 的方案数；其中：
dp[r][c][i][0]: 以a为最后一次采集； dp[r][c][i][1]为umi为最后一次采集

可能因为java与C++性能不一致，会出现MLE和TLE，导致只有60分；需要一系列优化：
1. 滚动数组
2. 在统计结果时候用long，最后取模
3. 输入时就取模（k + 1）
4. 计算中不要用 % mod，而是 if(x>=mod) x-=mod
5. 要用FastReader

```java
import java.util.*;
import java.io.*;
import java.math.BigInteger;

 
public class Main implements Runnable {
  // static Scanner in;
  static FastReader in;
  static PrintWriter out;
  static int[][] dirs8 = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {-1, -1}, {-1, 1}, {1, -1}};
  static int[][] dirs = {{0, -1}, {1, 0}, {0, +1}, {-1, 0}};
 
  static int[][] E;
  // static List<int[]>[] adj;
  static List<Integer>[] adj;
  static int[] vis;
 
  static long INFL = (long) 1e15 + 7;
  static int INF = (int) 1e7 + 9;
 
  static int T, n, m, k, count;
  static boolean flag;
  static int[] a, b;
  static int[][] mx;

  static int[][][][] dp;

  static int mod = (int) 1e9 + 7;
 
  static void solve() throws Exception {
    n = in.nextInt();
    m = in.nextInt();
    k = in.nextInt();

    mx = new int[n + 1][m + 1];
    for (int r = 1; r <= n; r++) {
      for (int c = 1; c <= m; c++) {
        mx[r][c] = in.nextInt() % (k + 1);
      }
    }
    dp = new int[2][m + 1][k + 1][2];
    // a - b - a - b
    // dp[r][c][i]: # of ways to end at (r, c), with diff(a - b) = i
    // 0: finish with a collecting
    // 1: finish with b collecting
    long res = 0;
    int cur = 0;
    for (int r = 1; r <= n; r++) {
      // dp[cur] = new int[m + 1][k + 1][2];
      for (int c = 1; c <= m; c++) {
        // dp[cur][c][mx[r][c] % (k + 1)][0] = 1;
        for (int i = 0; i <= k; i++) {
          dp[cur][c][i][1] = 0;
          dp[cur][c][i][0] = 0;

          if (i == mx[r][c]) {dp[cur][c][i][0]++;}
          dp[cur][c][i][1] += dp[1 ^ cur][c][(i + mx[r][c]) % (k + 1)][0];
          if (dp[cur][c][i][1] >= mod) dp[cur][c][i][1] -= mod;
          dp[cur][c][i][1] += dp[cur][c - 1][(i + mx[r][c]) % (k + 1)][0];
          if (dp[cur][c][i][1] >= mod) dp[cur][c][i][1] -= mod;

          dp[cur][c][i][0] += dp[1 ^ cur][c][(i - mx[r][c] + (k + 1)) % (k + 1)][1];
          if (dp[cur][c][i][0] >= mod) dp[cur][c][i][0] -= mod;
          dp[cur][c][i][0] += dp[cur][c - 1][(i - mx[r][c] + (k + 1)) % (k + 1)][1];
          if (dp[cur][c][i][0] >= mod) dp[cur][c][i][0] -= mod;
          
        }
        res += dp[cur][c][0][1];
      }
      cur = 1 ^ cur;
    }


    
    // for (int r = 1; r <= n; r++) {
    //   for (int c = 1; c <= m; c++) {
    //     res += dp[r][c][0][1];
    //   }
    // }

    out.println(res % mod);
    // Jren.p(dp[0][0][1]);
  }

 

 

  

  public static void main(String[] args) throws Exception {
 
    // in = new Scanner(new BufferedReader(new InputStreamReader(System.in)));
    in = new FastReader();
    out = new PrintWriter(System.out);
 
    // int T = in.nextInt();
    // for (int tt = 1; tt <= T; tt++) {
    //   // Thread t = new Thread(null, new Main(), "Main", 1 << 28);
    //   // t.start();
    //   // t.join();
    //   solve();
    // }
 
    // // Thread t = new Thread(null, new Main(), "Main", 1 << 28);
    // // t.start();
    // // t.join();
    solve();
 
    out.flush();
    out.close();
  }
 
  @Override
  public void run() {
    try {
      solve();
    } catch (Exception e) {
      e.printStackTrace(); 
    }
  }
 
  static class FastReader {
    public BufferedReader br; 
    StringTokenizer st; 
    public FastReader() {br = new BufferedReader(new InputStreamReader(System.in));} 
    String next() { 
      while (st == null || !st.hasMoreElements()) { 
          try {st = new StringTokenizer(br.readLine());} 
          catch (IOException e) {e.printStackTrace();} 
      } 
      return st.nextToken(); 
    } 
    int nextInt() {return Integer.parseInt(next());} 
    long nextLong() {return Long.parseLong(next());} 
    double nextDouble() {return Double.parseDouble(next());} 
    String nextLine() {
      String str = ""; 
        try {str = br.readLine();} 
        catch (IOException e) {e.printStackTrace();} 
        return str; 
    }
  }

  static void as(boolean result) throws Exception {
    if (!result) {
      throw new Exception();
    }
  }


  static int modInverse(int a, int m) { 
    int m0 = m; 
    int y = 0, x = 1; 
    if (m == 1) {return 0;} 
    while (a > 1) { 
      // q is quotient 
      int q = a / m; 
      int t = m; 
      // m is remainder now, process 
      // same as Euclid's algo 
      m = a % m; 
      a = t; 
      t = y; 
      // Update x and y 
      y = x - q * y; 
      x = t; 
    } 
    // Make x positive 
    if (x < 0) 
      x += m0; 
    return x; 
  } 
} 
```



---

## 作者：jins3599 (赞：0)

作为一个只会图论的蒟蒻，这道题还是想了蛮久的。

从题目可以肯定的看出来这是要用$dp$做的了。

先上来想一下有哪些状态？

当前点的坐标 $i,j$ ,小$a$的魔液值$q$ , $uim$的魔液值$p$，当前结点是小$a$走还是$uim$走。

$i,j,q,p,step......$五个状态..算了算大概空间，上限为:
$$800*800*15*15*2=288,000,000$$

还要四个维度进行枚举，$O(288000000)$的时间。

~~显然，我们可以拿这50分跑路了~~

我们考虑消去一维，我们不会用到$p,q$的具体值为多少，我们只关心$p$是否与$q$相等，即$p-q$的值。

因此我们只用四个维度就可以，即:
$$i,j,p-q,step=800*800*15*2=192,000,00$$

当然，转移复杂度也是$O(19200000)$，那么就可以通过本题了。

等等，还有dp的初始化呢？这不才是最重要的嘛！

题目中说："小$a$可以从任意点出发"

那么我们可以就在输入的时候，把所有代表小$a$要走的点赋值为1就行了。

再不理解的话代码中有注释

$Code:$
```cpp
#include <bits/stdc++.h>

using namespace std;

const int mod = 1e9 + 7;
const int maxn = 805;

int n , m , k , a[maxn][maxn];

int f[maxn][maxn][2][20];
// f[i][j][k][l] 代表 在点(i,j)的时候,若k=0,则为小a走，否则为uim,此时 : l = uim-小a 的魔液为k时的方案数。

/*
转移： f[i][j][0][l] += f[i - 1][j][1][(l - a[i][j] + k) % k]
      f[i][j][0][l] += f[i][j - 1][1][(l - a[i][j] + k) % k]
      f[i][j][1][l] += f[i - 1][j][0][(l + a[i][j]) % k]
      f[i][j][1][l] += f[i][j - 1][0][(l + a[i][j]) % k]
*/

int main () {
    scanf("%d%d%d" , &n , &m , &k); k ++;
    for(int i = 1 ; i <= n ; ++ i)
        for(int j = 1 ; j <= m ; ++ j) scanf("%d" ,&a[i][j]) , a[i][j] %= k , f[i][j][0][a[i][j] % k] = 1;;

    for(int i = 1 ; i <= n ; ++ i)  
        for(int j = 1 ; j <= m ; ++ j) 
            for(int l = 0 ; l < k ; ++ l){
            f[i][j][0][l] = (f[i][j][0][l] % mod + f[i - 1][j][1][(l - a[i][j] + k) % k] % mod) % mod;
            f[i][j][1][l] = (f[i][j][1][l] % mod + f[i - 1][j][0][(l + a[i][j]) % k] % mod) % mod;
            f[i][j][0][l] = (f[i][j][0][l] % mod + f[i][j - 1][1][(l - a[i][j] + k) % k] % mod) % mod;
            f[i][j][1][l] = (f[i][j][1][l] % mod + f[i][j - 1][0][(l + a[i][j]) % k] % mod) % mod;
        }
    int ans = 0;
    for(int i = 1 ; i <= n ; ++ i)
        for(int j = 1 ; j <= m ; ++ j) 
            ans = (ans % mod + f[i][j][1][0] % mod) % mod;
    printf("%d\n" , ans);
    return 0;
}
```

---

## 作者：Dolphin_ (赞：0)

看数据范围知dp

不需要知道两个人准确的值，只需要知道两个人是否相等，那么在状态中维护一下两个人的差即可

设dp[i][j][k][q]为当矩阵取到i,j个数时，两个人值的差为k，当前为q选

最终答案为所有k=0，q=1的方案数和（因为题目保证1号同学结束q=1，两个人的值相等 即差为0 k=0）

PS数组不要开太大了 会TLE int能存下不要用long long

见代码
```cpp
/*
 * @Author: Dolphin_ 
 * @Date: 2019-08-13 20:49:20 
 * @Last Modified by: Dolphin_
 * @Last Modified time: 2019-08-13 21:19:56
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define _FOR(i, a, b) for (int i = a; i >= b; --i)
#define INF 0x7fffffff
const int MOD=1000000007;
int n,m,k,a[802][802];
int f[802][802][16][2],ans;
inline void read(int &x)
{
    int f=1;x=0;char s=getchar();
    while(s>'9'||s<'0'){if(s=='-')f=-1;s=getchar();}
    while(s<='9'&&s>='0'){x=x*10+s-'0';s=getchar();}
    x*=f;
}
//羞耻的debug
void DEBUG()
{
	FOR(i,0,n)
		FOR(j,0,m)
			FOR(p,0,k)
				printf("%d %d %d:%d %d\n",i,j,p,f[i][j][p][0],f[i][j][p][1]);
}
int main()
{
    freopen("a.in","r",stdin);
    read(n);read(m);read(k);
    FOR(i,1,n)
        FOR(j,1,m)
            read(a[i][j]);
    FOR(i,1,n)
    	FOR(j,1,m)
    		f[i][j][a[i][j]%(k+1)][0]=1;
    FOR(i,1,n)
    {
        FOR(j,1,m)
        {
            FOR(p,0,k)
            {
            	if(i+1<=n)
            	{
            		f[i+1][j][(p+a[i+1][j])%(k+1)][0]=(f[i+1][j][(p+a[i+1][j])%(k+1)][0]+f[i][j][p][1])%MOD;
            		f[i+1][j][(p-a[i+1][j]+k+1)%(k+1)][1]=(f[i+1][j][(p-a[i+1][j]+k+1)%(k+1)][1]+f[i][j][p][0])%MOD;
				}
				if(j+1<=m)
				{
					f[i][j+1][(p+a[i][j+1])%(k+1)][0]=(f[i][j+1][(p+a[i][j+1])%(k+1)][0]+f[i][j][p][1])%MOD;	
					f[i][j+1][(p-a[i][j+1]+k+1)%(k+1)][1]=(f[i][j+1][(p-a[i][j+1]+k+1)%(k+1)][1]+f[i][j][p][0])%MOD;
				}
            }
        }
    }
    //DEBUG();
    ans=0;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			ans=(ans+f[i][j][0][1])%MOD;
    printf("%d\n",ans);
    return 0;
}

---

## 作者：shejian0702 (赞：0)


据说这是一道好题，注意到移动方向固定，每个格子只能有自己上方或左方的格子到达  
不妨设 `dp[i][j][n][0/1]` 表示在格子`[i.j]`小a/小uim取药水，小a的药水比小uim多n的方法种数。边界条件：

$dp[0][0][a[i][j]][0]=1,dp[0][0][n(n!=v[0][0])]=0$;状态转移方程为，
$$dp[i][j][n][0] = dp[i-1][j][n-k][1] +dp[i][j-1][n-k][1]+ dp[i][j][l][0];$$
$$dp[i][j][n][1] = dp[i-1][j][n+k][0] +dp[i][j-1][n+k][0];$$
但是有一个尴尬的问题：会爆药水瓶，我是这样解决的：有 `a%k - b%k = (a - b + n*k)%k(n 为正整数且使得a-b+k >= 0)`
于是转移方程变为
```cpp
dp[i][j][l][0] = dp[i-1][j][(l-t+k)%k][1]%mod + dp[i][j-1][(l-t+k)%k][1]%mod + dp[i][j][l][0];
dp[i][j][l][1] = dp[i-1][j][(l+t)%k][0]%mod +dp[i][j-1][(l+t)%k][0]%mod;
```
最后答案为$$\sum^{n-1}_{i = 0}\sum^{m-1}_{j = 0} dp[i][j][0][1]$$ ;~~我是从0开始计数的~~  
代码：  

```cpp
#include<cstdio>
#define rep(i,n) for(register int i = 1;i<=n;i++) 
#define repk for(register int l = 0;l<=k;l++) 


const long long  mod = 1000000007;
const int maxn = 805;

void read(int& k){
int f = 1,x = 0;char ch = getchar();
while('9'<ch || ch < '0') {if(ch == '-') f = -1;ch = getchar();}
while(ch >= '0' && ch <= '9') {x = (x<<3) + (x<<1) + (ch ^ 48);ch = getchar();}
k = f*x;
}

int n,m,k,a[maxn][maxn],dp[maxn][maxn][18][2]; 
long long ans;

int main(){
	read(n);read(m);read(k);++k;
	//printf("%d %d %d ",n,m,k);
	rep(i,n) rep(j,m) {read(a[i][j]);a[i][j] %= k;dp[i][j][a[i][j]][0] = 1;}//printf("a[%d][%d]:%d\n",i,j,a[i][j]);}
	rep(i,n) rep(j,m) repk{
		int &t = a[i][j];
		dp[i][j][l][0] = dp[i-1][j][(l-t+k)%k][1]%mod + dp[i][j-1][(l-t+k)%k][1]%mod + dp[i][j][l][0];
		dp[i][j][l][1] = dp[i-1][j][(l+t)%k][0]%mod +dp[i][j-1][(l+t)%k][0]%mod;
	}
	rep(i,n) rep(j,m) ans = (ans+dp[i][j][0][1])%mod;
	printf("%lld",ans);
}	

```


---

## 作者：ddwqwq (赞：0)

不知道楼下是怎么过的，为什么没有炸内存，反正我第一次记忆化搜索内存炸了，只好放弃了递归的习惯，改用递推加滚动数组优化，写了人生第一个滚动数组。发现还没有这个优化，就发一个。

我的基本思路与楼下一样，但计算差时脑子没转过弯来，觉得需要引入负下标，于是用了一个小技巧，弄了一个有负下标的数组。虽然在本题中很蠢，但也可以借鉴一下。这是初始化，应该很好理解，就是用指针代替原本的数组头。

```cpp
long long a[2][805][31], map[805][805], b[2][805][31];
long long *d[2][805], *bak[2][805], sum;
int N, M, K;

void prepare()
{
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 805; j++)
        {
            d[i][j] = a[i][j] + 15;
            bak[i][j] = b[i][j] + 15;
        }
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));
}
```
然后就是滚动数组。思路：填表时只留下正在使用的两行，分别放在d数组和bak数组里，然后随时记录方案数。参照楼下题解，看看代码，应当也容易理解。输入输出略。

```cpp
void dp()
{
    for (int k = N; k >= 1; k--)
    {
        memcpy(b, a, sizeof(a));//更新bak。
        for (int j = M; j >= 1; j--)
        {
            for (int l = -K; l <= K; l++)
                for (int i = 1; i >= 0; i--)
                {
                    int m;//m是更新两人差值
                    if (i == 1)
                        m = (l + map[k][j]) % (K + 1);
                    else
                        m = (l - map[k][j]) % (K + 1);
//注意，更新时向下用bak数组，向右用d数组。
                    d[i][j][l] = (bak[1 - i][j][m] + d[1 - i][j + 1][m]) % MAX;
                    if (i == 0 && m == 0)
                        d[i][j][l]++;
                }
        }
        
        for (int i = 1; i <= M; i++)
            sum = (sum + d[1][i][0]) % MAX;
    }
}
```
最后放一个炸掉的记忆化搜索，作为反面教材

```cpp
#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <math.h>
#include <cstring>
#include <time.h>

#define MAX 1000000007

int a[2][801][801][31], map[801][801];
int *d[2][801][801];
int N, M, K;

void prepare()
{
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 801; j++)
            for (int k = 0; k < 801; k++)
                d[i][j][k] = a[i][j][k] + 15;
    memset(a, -1, sizeof(a));
}

int dfs(int a, int x, int y, int dif)
{
    if (x > N || y > M)
        return 0;
    if (d[a][x][y][dif] != -1)
        return d[a][x][y][dif];
    
    int m = dif;
    if (a == 1)
        m = (m + map[x][y]) % (K + 1);
    else
        m = (m - map[x][y]) % (K + 1);
    
    if (m == 0 && a == 0)
        return d[a][x][y][dif] = (dfs(1 - a, x + 1, y, m) +
            dfs(1 - a, x, y + 1, m) + 1) % MAX;
    else
        return d[a][x][y][dif] = (dfs(1 - a, x + 1, y, m) +
            dfs(1 - a, x, y + 1, m)) % MAX;
}

int main()
{
    prepare();
    int i, j, sum = 0;

    scanf("%d %d %d", &N, &M, &K);

    for (i = 1; i <= N; i++)
        for (j = 1; j <= M; j++)
            scanf("%d", &map[i][j]);

    for (i = 1; i <= N; i++)
        for (j = 1; j <= M; j++)
            sum += dfs(1, i, j, 0);

    printf("%d", sum);

//    system("pause");
    return 0;
}
```

---

## 作者：panda_2134 (赞：0)

路径行走dp+背包

### 审题

两个人绑在一起走，但是每次吸收的人交换，可以向右向下走，求二者魔瓶内体积相等的方案数目。

注意开始和结束都在矩阵内。

### 思路分析

不知道大家有没有写过一道叫做多米诺骨牌的题目。[Luogu P1282](https://www.luogu.org/problem/show?pid=1282)

那个题目里面明显地说明了"让差最小"，于是我们把差加入状态；在这个题目里面，体积相等可以转化为差为0。

因为吸取魔液实际上是建立了不同液体量，也就是不同体积之间的联系，所以同样可以用背包的方法：定义状态$f(i,j,p,q)$为处在坐标$(i,j)$，二者体积的差值（模k+1意义下）为p，q=0表示这个格子由小a吸收，反之表示由uim吸收。统计向右和向下走的方案总数目即可。

状态转移方程：

 ![](https://cdn.luogu.com.cn/upload/pic/6996.png) 

代码：注意常数，多维数组每一位都尽量不要是2的n次方，否则会不断cache miss降低效率；MOD运算很慢，减少进行的次数

```cpp
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cctype>
using namespace std;
const int MAXN = 800, MAXM = 800, MAXK = 15, MOD=1e9+7;
int N,M,K,n1,n2,Ans,W[MAXN+2][MAXM+2],opt[MAXN+2][MAXM+2][MAXK+2][2];//85MB
inline int readint() {
    int f=1,r=0;char c=getchar();
    while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
    while(isdigit(c)){r=r*10+c-'0';c=getchar();}
    return f*r;
} 
int main(){
    N=readint();M=readint();K=readint();
    for(int i=1;i<=N;i++)
        for(int j=1;j<=M;j++)
            W[i][j]=readint();
    for(int i=N;i>=1;i--)
        for(int j=M;j>=1;j--)
            for(int p=0;p<=K;p++) {
                n1=(p+W[i][j])%(K+1);n2=(p-W[i][j]%(K+1)+((K+1)<<1))%(K+1);
                //q=0
                opt[i][j][p][0] = (opt[i][j][p][0]%MOD 
                + opt[i+1][j][n1][1]%MOD) %MOD;
                opt[i][j][p][0] = (opt[i][j][p][0]%MOD 
                + opt[i][j+1][n1][1]%MOD) %MOD;
                //q=1
                opt[i][j][p][1]= (opt[i][j][p][1]%MOD
                + opt[i+1][j][n2][0]%MOD) %MOD;
                opt[i][j][p][1] = (opt[i][j][p][1]%MOD 
                + opt[i][j+1][n2][0]%MOD) %MOD;
                //Stop here
                if(n2==0) opt[i][j][p][1]++;
            } 
    for(int i=1;i<=N;i++)
        for(int j=1;j<=M;j++)
            Ans=(Ans%MOD+opt[i][j][0][0]%MOD)%MOD;
    printf("%d",Ans);
    return 0;
}

```

---

