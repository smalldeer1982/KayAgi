# [USACO09MAR] Cow Frisbee Team S

## 题目描述

老唐最近迷上了飞盘，约翰想和他一起玩，于是打算从他家的 $N$ 头奶牛中选出一支队伍。

每只奶牛的能力为整数，第 $i$ 头奶牛的能力为 $R_i$。飞盘队的队员数量不能少于 $1$、大于 $N$。一支队伍的总能力就是所有队员能力的总和。

约翰比较迷信，他的幸运数字是 $F$，所以他要求队伍的总能力必须是 $F$ 的倍数。请帮他算一下，符合这个要求的队伍组合有多少？由于这个数字很大，只要输出答案对 $10^8$ 取模的值。

## 说明/提示

对于 $100\%$ 的数据，$1 \le N \le 2000$，$1 \le F \le 1000$，$1 \le R_i \le 10^5$。

## 样例 #1

### 输入

```
4 5 
1 
2 
8 
2 
```

### 输出

```
3 
```

# 题解

## 作者：CCF_zkskyer (赞：288)

## 一、看题
  很明显，这是一道~~USACO~~的原题，所以我们得先看题面，小心被坑（本蒟蒻就被坑了！！！）
  
 广大群众都看出来这是一道完完全全的01背包，但还是有些不一样，这里不是求能力最大，而是求能整除幸运数F的总能力有几种
 
## 二、构思
大部分朋友听到这里后就不会做了，这恰好就中了出题人的下怀，其实啊，我们不妨直接按题目中的条件去试试，没准就过了呢（AC的魔力）

所以，根据题面所说的，可以看出状态转移方程，其实这道题蛮单纯的

**状态转移方程**如下：


$$f (i,j) = ( ( f (i,j) + f(i-1,j)) \% mod + f (i-1,(j - cow[ i ] + F ) \% F ] ) \% mod$$


即分奶牛参与或不参与两种情况进行讨论

## 三、AC代码呈现

```cpp
#include <bits/stdc++.h>

using namespace std;

const int mod=100000000;//这里定义去模的数，尽量用常数 

long long cow[2005],f[2005][2005];//cow[i]指第i头奶牛的能力，f[i][j]是存前i件物品且余数正好为j时的最大值 

int main()
{
        int N,F;
        
	scanf("%d%d",&N,&F);//输入奶牛数量和幸运数 
    
	for (register int i=1;i<=N;i++) //适当的卡 
	{
		scanf("%d",&cow[i]);//输入奶牛能力 
		cow[i]%=F;//这里可以提前取模，减少时间 
	} 
    
	for (register int i=1;i<=N;i++) f[i][cow[i]]=1;//初始化 
	
        for (register int i=1;i<=N;i++)//列举前i件物品 
        {
    	     for (register int j=0;j<=F-1;j++)//列举余数 
             {
        	  f[i][j]=((f[i][j]+f[i-1][j])%mod+f[i-1][(j-cow[i]+F)%F])%mod;//状态转移方程应用 
             }
	}
    
	printf("%d",f[N][0]);//注意这里是到前n件物品且余数正好为0时的最大值 
    
	return 0;
}

```

## 四、请求
本人是中学生，第一次发题解，请大家多多支持，留下你们宝贵的赞，顶我！！！


---

## 作者：Cxs3 (赞：55)

题目链接：https://www.luogu.org/problem/P2946

---

## 题目分析
这就是一个类似于$01$背包的问题。对于每头牛都有取和不取两种选择。

用$h[i][j]$表示在前$i$头牛中选择，所选数之和$mod \ F$结果为$j$的方案数。（以下用“和为$j$”表示“和$mod \ F$结果为$j$”。）

- 若不取$i$，则应在前$i-1$头牛中取来若干和为$j$的数，方案数即为$h[i-1][j]$。  
- 若取$i$，则应在前$i-1$头牛中取来若干和为$j-r[i]$的数，这样加上$r[i]$后，和才能等于$j$，即$h[i-1][j-r[i]]$。  

所以$h[i][j]=h[i][j]+h[i-1][j]+h[i-1][j-r[i]]$。

这里还有一个关于取模的问题要解决。我们要用到的只是$r[i] \ mod \ F$的余数，所以输入时就先将$r[i]$对$F$取模。  
还有就是$j-r[i]$可能为负数，这时就得写成`(j-r[i]+F)%F`，就为正了。

初始化$h[i][r[i]]$为$1$。  

---

## 代码实现
```cpp
#include<bits/stdc++.h>
const int p=1e8;//定义常数
const int N=2000+10;
const int F=1000+10;
using namespace std;

int n,f,r[N],s[N][F];
long long h[N][F];

int main()
{
	int i,j;
	cin>>n>>f;
	for(i=1;i<=n;i++)
	{
	  cin>>r[i];
	  r[i]%=f;//提前取模
	}
	for(i=1;i<=n;i++) h[i][r[i]]=1;//初始化
	for(i=1;i<=n;i++)
	  for(j=0;j<f;j++)//余数范围：0到f-1
	    h[i][j]=((h[i][j]+h[i-1][j])%p+h[i-1][(j-r[i]+f)%f])%p;//每加一次就%p
	cout<<h[n][0]<<endl;
	return 0;
}
```

---

## 作者：lawsonabs (赞：25)

---
## 0.总结
这是一道好题 **（我太菜了）**，这是一道好题（我太菜了），这是一道好题（我太菜了）！重要的话说三遍。

`Get to the key point firstly, the article comes from [LawsonAbs](https://lawson-t.blog.csdn.net/article/details/104876230)LawsonAbs!`

坑点如下：
- 数据范围过大，导致无法开出2000*100000的数组，即朴素的0/1背包无法解决问题
- 在把能力对F取模处理之后，利用一维的滚动数组会造成问题的错误解
- 答案要对 10^8 取模

下面正式进入主题

---


## 1.题意
给出两个整数n，f。接下来输入n个数，要求从这 n 个数中选出若干个数，它们组成的和能够整除f，求这种选择的个数。又因为解的数过大，要求对10^8取模。


## 2.主要思路
一眼望去，满屏都是 “0/1背包”的身影。思路如下：

01.令 `dp[i]` 表示到达能力`i`的选择种类数。初始时`dp[0] = 1`。 

02.双重`for`循环后，依次放入第`1-n`个物品 【其下标对应分别是`0 — n-1`】，倒序更新j的值，然后依次得到到达能力j的选择种类。

03.最后再用一个for循环判断每个能力值是否可以整除f。如果是累计答案，同时将答案取模。

04.输出结果 `res`.

 兴奋的10min编码，但是却只能得到 **80分**，【另外两个分别是 RE,TLE】。于是找问题。

结合题目的数据范围，可以看到
>N(1≤N≤2000);Ri(1≤Ri≤100000);F(1≤F≤1000)

那么能力值的范围就是 `2000 * 100000`。毫无疑问，开这么大的数组肯定会MLE。那接下就要想该怎么优化了。

题目要求能力值能整除f时，才作为结果的一部分。根据加法模运算的规则【`(a+b)%F = a%F + b%F`】那么就可以考虑  

### 是否不用把所有的能力加起来之后对F取模，而是在相加的同时就对F取模。

这样最后只需要输出 `dp[0] - 1`【F!=1时】 或者`dp[0]`【F=1时】 即可。举例来说：
```
2 5
1 
10
```
可以到达的能力是
```
dp[0]=1; dp[1]=1; dp[10]=1; dp[11] = 1;
```
其中符合输出条件的只有10一个。而如果我们在对求出的能力值对F取余再写入数组时，就得到如下的结果
```
dp[0]=1; dp[1]=2; dp[10]=1;
```
`dp[1]`由之前的1变成了2。但是结果并不会发生变化【不会发生变化的原因就是 加法模运算这个规则造成的】。所以现在可以确定的是：
- 利用模运算，将能力值范围从 `0- N*Ri` 缩小到 `0-F`

但是像上面说的这样硬性取模真的可以解决问题吗？再看一组测试用例：
```
6 5
1
3
10
2
8
2
```
输入时对数据同时进行取余操作，得到的样例就变成：
```
6 5
1
3
0
2
3
2
```
dp的过程是：用上一轮的`dp[j]`与 `dp[j-arr[i]]` 求和作为本轮的`dp[j]`，其中必有 **j>arr[i]** ，但是因为我们对和进行了取模操作，就无法保证**j>arr[i]** 恒成立。
比如10对5取模成了0，2对5取模成了2。0<2，但是10>2。
所以直接用式子 `dp[j] += dp[j-arr[i]]` 求，就相当于是 `dp[0] += dp[-2]` 显然是不合理的。所以需将操作变成 `dp[j] += dp[(j-arr[i]+f)%f]` 但这样依然无法解决问题。因为`((j-arr[i]+f)%f)`这个操作会**改变j与arr[i]之间的大小关系**。原本j大于arr[i], 可能在操作之后， arr[i]大于j，就导致之前做的倒序枚举失效，从而无法得到正确的结果，所以在此基础上，应该使用2维dp，将上一次的结果值放在一个数组里，而避免出现错误。

## 3.AC代码

```
#include<iostream>
using namespace std;
const int maxN = 2005;
const int maxV = 1005; 
int n,f;
int arr[maxN],dp[2][maxV];

int main(){	
	cin >> n >>f;	
	for(int i = 0 ;i< n;i++){
		cin >>arr[i];
		arr[i] %= f; 
	}
		
	fill(dp[0],dp[0]+2*maxV,0);
	
	//1.初始化，放第1个物品【即arr[0]达到的情况】 
	dp[0][0] = 1;
	dp[0][arr[0]] = 1;
	
	//2.开始依次将第2-(n-1)个物品放入 
	for(int i = 1;i< n;i++){		
		for(int j = f-1;j >= 0;j--){											
			dp[i&1][j] = dp[(i-1)&1][(j-arr[i]+f)%f] + dp[(i-1)&1][j];
			dp[i&1][j] %= 100000000;						
		}
	}
	int ei = (n-1)&1;
	int res = dp[ei][0];
	if(f == 1)
		cout << res<<"\n";
	else
		cout << res - 1<<"\n";
	return 0;
}
```

## 5.废话
- 如有错误，希望各位大佬不吝指正
- 本题的中文翻译真的是太low了
- 洛谷的Markdown太难用了吧
- 请各位大佬不要灌水评论

---

## 作者：Karl_Aurora (赞：22)

$ 更新于2021.1.17——修复了博客链接 $

#### [~~无耻地推销个人博客qwq~~](https://www.luogu.com.cn/blog/ling-XAIqwq/solution-p2946)

#### [题目传送门](https://www.luogu.com.cn/problem/P2946)



------------


## ~~USACO出品，必属精品~~

众所周知的是，这玩意大家一眼就能看出是个01背包，但如果再仔细看一下，你就会发现这玩意儿不对劲儿——

**_这玩意的结果不仅要求的是结果总数，还要求是结果是幸运数F的倍数啊喂！_**

~~\*\*\*~~

~~稍加思考.jpg~~

不过如果顺着题目条件推一推，经过一番思索，我们便能得到如下dp递推柿子：

$f(i,j) = f(f(i,j) + f(i-1,j)) \% mod + f(i - 1,(j - R_i + F) \% F) \% mod  $

于是乎，这道题就出来了qwq

现在又到了你们最爱的代码时间\~\~\~

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod = 1e8;
int N, F, x;
int dp[2010][1010], R[2010];
int main()
{
    cin>>N>>F;
    for (int i = 1; i <= N; ++i) 
    {
        cin>>x;
        R[i] = x%F; 
        dp[i][R[i]] = 1;
    }
    for (int i = 1; i <= N; ++i)
        for (int j = 0; j < F; ++j)
            dp[i][j] = ((dp[i][j] + dp[i-1][j]) % mod +dp[i-1][(j-R[i]+F)%F])%mod;
    cout<<dp[N][0]<<endl;
    return 0;
}
```

![](https://cdn.luogu.com.cn/upload/image_hosting/a5r33wq6.png)

经测试，在未吸氧的情况下，跑了63ms，6.40MB，全部AC

#### ~~最后求点赞啦qwq~~

---

## 作者：namespace_std (赞：22)

为增加明天考试RP和活跃值发一波题解...

这题是动归经典题目。

FZOJ传送门：http://218.62.22.209:8080/problem.php?cid=1759&pid=3

BZOJ传送门：http://www.lydsy.com/JudgeOnline/problem.php?id=3400

用一个数组dp[2][1000]来递推操作。因为每次递推只需要上一层的数据，所以dp开2层即可，不需要1000×2000的高开销。

状态转移方程：
```cpp
	dp[i][j]=dp[i-1][j]+dp[i-1][(f+j-Ri)%f];
```
或者更~~草率~~直接的：
```cpp
	for(j=0;j<f;j++)
	{
		(dp[i][(j+ri)%f]+=dp[i-1][j])%=INF;
		(dp[i][j]+=dp[i-1][j])%=INF;
		dp[i][j]=0;
	}
```

然后把i和i-1替换成了i%2和(i+1)%2...

~~就差不多了~~然后别忘了求余

下面是代码：
```cpp
//FZOJ-Contest C1759-NOIPB层模拟10<ACM>-题目D
#include<cstdio>
#define INF 100000000
int dp[2][1001];
int n,f;
int main()
{
    int i,ii,ri;//请不要吐槽，本人用ii表示2层循环习惯了
	scanf("%d%d",&n,&f);
	dp[0][0]=1;
	for(i=1;i<=n;i++)
	{
		scanf("%d",&ri);
		int l=i%2,r=(i+1)%2;
		for(ii=0;ii<f;ii++)
		{
			(dp[l][(ii+ri)%f]+=dp[r][ii])%=INF;
			(dp[l][ii]+=dp[r][ii])%=INF;
			dp[r][ii]=0;
		}
	}
	printf("%d\n",dp[n%2][0]-1);
}
```

---

## 作者：fy0123 (赞：20)

01背包直接上！

f[i][j]表示选到前i件物品，%m的余数为j的方案数。初始条件f[i][a[i]]=1。

转移：f[i][j] += f[i-1][j]+f[i-1][((j-a[i])%m+m)%m];（分这头牛选或不选两种情况）

代码：

```cpp
#include<cstdio>
#include<cstring>
#include<cctype>
using namespace std;

const int N = 2010, M = 1010;
const int MOD = 1e8;
int n, m;
int f[N][M], a[N];

inline int read()
{
    char ch = getchar(); int x = 0, flag = 0;
    while (!isdigit(ch)){ if (ch == '-') flag = 1; ch = getchar(); }
    while (isdigit(ch)){ x = x * 10 + ch - '0'; ch = getchar(); }
    return flag ? -x : x;
}

int main()
{
    n = read(), m = read();
    for (int i = 1; i <= n; i ++) f[i][a[i] = read()%m] = 1;
    for (int i = 1; i <= n; i ++)
        for (int j = 0; j < m; j ++)
            f[i][j] = (f[i][j]+f[i-1][j]+f[i-1][((j-a[i])%m+m)%m])%MOD;
    printf("%d\n", f[n][0]);
    return 0;
}
```

---

## 作者：nafna (赞：11)

# P2946 [Cow Frisbee Team] DP/滚动数组优化/在线求解

## 思路
- 看做是 **0-1背包求方案数**
- 求背包中物品的价值恰好是 ```F``` 的倍数, 即 价值 % F == 0 的方案数
- 滚动数组优化
- 在线求解

转移方程
$$f[i][j] = f[i - 1][j] + f[i - 1][j - w]$$
分别对应装与不装物品的方案数

## 完整代码
```cpp
#include <iostream>
using namespace std;

const int Q = 1e8;

int n, F;        // 物品数,
int f[2][1005];  // 滚动数组, 前 i 件物品, 价值总和 % F = j 的方案数

int main(){
    ios::sync_with_stdio(false);
    cin >> n >> F;

    // 初始化
    int p = 0, w;      // 滚动数组游标, 当前物品价值
    f[p][0] = 1;      // 即 f[0][0] = 1

    for (int i = 1; i <= n; i ++){
        cin >> w;
        w %= F;

        p = 1 - p;
        for (int j = 0; j < F; j ++)        // 1-p 是上一行, 即 i-1 行; p 是当前行, 即 i 行
            f[p][j] = ( f[1-p][j] + f[1-p][(j - w + F) % F] ) % Q;
    }

    cout << f[p][0] - 1 << endl;  // 减去 f[0][0] 的 1
    return 0;
}
```


---

## 作者：huxulin (赞：4)

水一发题解,我们设f[i][j]表示前i个物品组成模F余数为j的方案数,那么考虑第i个物品选或不选,那么就有f[i][j]+=f[i-1][j],或f[i][j]+=f[i-1][(j+r[i])%F],记得初始化f[0][0]=1.


```cpp
#include <cstdio>
#include <algorithm>
using namespace std;

static const int maxm=2e3+10;
static const int MOD=1e8;

int f[maxm][maxm],r[maxm];
int n,F;

int main(){
    scanf("%d%d",&n,&F);
    for(int i=1;i<=n;i++)scanf("%d",&r[i]);

    f[0][0]=1;
    
    for(int i=1;i<=n;i++){
        for(int v=0;v<=F;v++){
            f[i][v]=(f[i][v]+f[i-1][v])%MOD;
            f[i][v]=(f[i][v]+f[i-1][(v+r[i])%F])%MOD;
        }
    }

    printf("%d\n",f[n][F]);   //如果是f[n][0]则要减一
    
    return 0;
}
```

---

## 作者：L7_56 (赞：3)

### 01背包问题
---
将能力值对 $F$ 的取模作为背包容量

对于每头牛有取和不取两种方案，分别找出方案数再相加就可以了

由于余数最后形成的是一个环，没有办法压掉一维

但还是可以用滚动数组压(这道题不需要我就没用)

### 代码
---
```cpp
#include<bits/stdc++.h>
#define Nmx 2010
#define Fmx 1010
using namespace std;

const int mod=1e8;
int n,f;
int dp[Nmx][Fmx],r[Nmx];

int main(){
	scanf("%d%d", &n, &f);
	for(int i=1;i<=n;++i){
		scanf("%d", &r[i]);
		r[i]%=f;dp[i][r[i]]=1;
		for(int j=0;j<f;++j)
		 dp[i][j]=(dp[i][j]+dp[i-1][j]+dp[i-1][(j-r[i]+f)%f])%mod;
	}
	printf("%d",dp[n][0]);
	return 0;
}
```

---

## 作者：DDOSvoid (赞：1)

在这里给大家提供一种01背包的思想。虽然我的代码只能得80分(一个点RE，一个点TLE)

由于每种物品只有选或不选两种情况，所以可以转换成01背包。直接套用01背包的方案数。f[j]表示组成j的方案数。

```cpp
#include<iostream>
#include<cstdio>
#define maxn 2001
#define ll long long 
using namespace std;
int n,m,a[maxn],sum,ans;
int f[maxn*10000+10];//死就死在数组没法开2000000000上 
const int mod=100000000;
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        sum+=a[i];
    }
    f[0]=1;
    for(int i=1;i<=n;i++)
        for(int j=sum;j>=a[i];j--){
            f[j]+=f[j-a[i]];
            f[j]%=mod;
        }
    for(int i=m;i<=sum;i+=m)//只需要加上组成m的倍数的方案数 
        ans=(ans+f[i])%mod;
    cout<<ans;
    return 0;
}
```
如果题解在思想上跟正解类似（就是正解思想一样反而更优）请及时联系


---

