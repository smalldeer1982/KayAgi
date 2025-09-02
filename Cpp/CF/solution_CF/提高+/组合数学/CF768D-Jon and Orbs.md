# Jon and Orbs

## 题目描述

Jon Snow is on the lookout for some orbs required to defeat the white walkers. There are $ k $ different types of orbs and he needs at least one of each. One orb spawns daily at the base of a Weirwood tree north of the wall. The probability of this orb being of any kind is equal. As the north of wall is full of dangers, he wants to know the minimum number of days he should wait before sending a ranger to collect the orbs such that the probability of him getting at least one of each kind of orb is at least ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF768D/084e5b8c9ee986cd51e443adb59a2f8594ceba38.png), where $ ε&lt;10^{-7} $ .

To better prepare himself, he wants to know the answer for $ q $ different values of $ p_{i} $ . Since he is busy designing the battle strategy with Sam, he asks you for your help.

## 样例 #1

### 输入

```
1 1
1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2 2
1
2
```

### 输出

```
2
2
```

# 题解

## 作者：Evitagen (赞：14)

### 题意：

$K$ 种物品，求一次取一件把所有种类取遍的概率不小于 $p/2000$ 的最小天数。

$p$ 有 $Q$ 次询问。

### 分析：

概率 $dp$ ，而且选择的顺序没关系，因此二维就可以了

设 $dp[i][j]$ 表示第 $i$ 天，之前已经选择了 $j$ 种物品的概率。

有两种情况：

1. 第 $i$ 天选择在第 $i-1$ 天前已经选过了的物品的概率
   此时，概率为 $\frac{j}{n}$
```cpp
dp[i][j]+=dp[i-1][j]*j/n;
```

2. 第 $i$ 天选择了没有选过的物品
   
   概率则是 $\frac{n-j+1}{n}$ ，表示之前选过 $j-1$ 个物品，就剩余 $n-j+1$ 个物品没选择。

```cpp
dp[i][j]+=dp[i-1][j-1]*(n-j+1)/n;
```

那么，怎么枚举天数呢？

最极限的情况是：$1000$ 个物品，需要天数对应的概率不小于二分之一

我们设转移中最高天数为 $m$。

通过枚举 $m$ (输出 $dp[m][1000]$)，发现在这种条件下，需要的天数至少是 $m=7500$ 天左右，而且转移的时间复杂度符合题意。

因此，我们设 $m=10000$, 像上面一样进行转移。

最后，我们顺序查找：

当 $dp[j][n] \geq p[i]/2000$ ，输出 $j$ 即可。


### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e4+5,M=1e3+5;
double dp[N][M];
int K,Q;
int p[N],n,m=10000;
int main(){
    cin>>n>>Q;
    for(int i=1;i<=Q;i++){
        scanf("%d",&p[i]);
    }
    dp[0][0]=1;
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++)
            dp[i][j]=dp[i-1][j]*(double)j/n+dp[i-1][j-1]*(double)(n-j+1)/(n);
    for(int i=1;i<=Q;i++){
        int t=1;
        for(int j=1;j<=m;j++) if(dp[j][n]<p[i]*0.0005) t++;
        printf("%d\n",t);
    }
    // cout<<dp[m][n]<<endl;
    system("pause");
    return 0;
}
```

---

## 作者：quest_2 (赞：7)


推一下蒟蒻 [$\large\color{limegreen}{\texttt {博客}}$](https://www.luogu.com.cn/blog/quest233/#) ～

------------

看到楼上下的大佬都开的是二维数组，实则不需，蒟蒻在这里给出一种反复利用一个一维数组的解法 $QwQ$ 。

------------

$\large\color{salmon}{\texttt {先设置状态～}}$

按着期望 $DP$ 的套路走，设置 $dp_{\ i}$ 表示：**取到 $i$ 件不同的物品，所期望取的天数。**

这一设置状态的思路甚至可以延用到 [ [SHOI2002]百事世界杯之旅](https://www.luogu.com.cn/problem/P1291) 和 [收集邮票](https://www.luogu.com.cn/problem/P4550) 两道蓝题里。~~（说实话，我觉得这道黄题比那两道蓝题不知道高到哪里去了。）~~


------------

$\large\color{violet}{\texttt {再考虑转移～}}$

我们提到：$dp_{\ i}$ 代表的状态是 **取到了 $i$ 件不同的物品** 。

考虑什么情况下会造就这种状态。无非两种：

- 原来有 $i-1$ 个物品，一发出货，从 $dp_{\ i-1}$ 转移过来，这样的概率是 $\dfrac{K-(i-1)}{K}=\dfrac{K-i+1}{K}$ 

_注：即卡池（误）里有 $K$ 个物品，自己已经有了 $i-1$ 个，那还有 $K-i+1$ 个是自己没有的，抽这些即能使自己多获得一种物品_

- 早就有 $i$ 个物品了，抽一发沉了 ~~（是我没错了）~~ ，从  $dp[i]$ 转移过来，这样的概率是 $\dfrac{i}{K}$ 

_注：含义同上_ 

那么我们就可以列出一个方程辣：

$$dp[i]=dp[i-1]*\dfrac{K-i+1}{K}+dp[i]*\dfrac{i}{K}$$

为了防止爆精写成这样更为稳妥：

$$dp[i]=\dfrac{dp[i-1]*(K-i+1)+dp[i]*i}{K}$$

随着时间的推移， **每一天** 都会面临一次这样的转移，因为每一天的抽卡都存在有出货与不出货的概率。~~（赌狗一无所有）~~


------------

$\large\color{blueviolet}{\texttt {最后计划转移方式～}}$

这个式子对于每一天的状态 **独立成立** ，说人话就是：

**当天** 的 $dp_{i-1}$ 不能影响 **当天**  $dp_i$ 的转移，用来转移 $dp_i$ 的 $dp_{i-1}$ 是 **上一天** 的 $dp_{i-1}$ 。

存在一种感性理解就是：我今天抽卡的卡池，实则用的是我 **昨天** 抽完以后的卡池。

那么，为了防止 $dp_{i-1}$ 的更新影响 $dp_{i}$ 的更新，我们选择 **倒序跑 $for$ 。**

记录第 $d$ 天抽满 $K$ 个物品的概率，即当时的 $dp_{\ K}$ 。存这个值于 $ans_{\ d}$

最后对于每一个询问，扫一遍 $ans$ ，找到最小的 $d$ 满足条件，输出即可。


------------

$\large\color{royalblue}{\texttt {代码如下：}}$

```
#include <bits/stdc++.h>
using namespace std;
const long double EPS = 1e-8;
const int MAX = 1e3 + 7;
long double dp[MAX];
long double ans[MAX << 3];
//楼上大佬已经证过，最大的期望天数跑不出 1000*ln(1000) 
//这里用*8 代替 *ln(1000)
int main()
{
	int K, M;
	cin >> K >> M;
	dp[0] = 1.0;
	for (int i = 1; i <= 8000; i++)
	{
		for (int j = K; j > 0; j--)//倒序扫
		{
			dp[j] = (dp[j - 1] * (K - j + 1) + dp[j] * j) / (K * 1.0);
            //转移
		}
		ans[i] = dp[K];//记录 dp[k]
		dp[0] = 0;
	}
	while (M--)
	{
		int p;
		cin >> p;
		for (int i = 1; i <= 8000; i++)
		{
			if (ans[i] * 2000 >= p - EPS)//防炸精写法
			{
				cout << i << "\n";
				break;
			}
		}
	}
}
```


---

## 作者：皎月半洒花 (赞：5)

首先 $dp$ 不难想，感觉这个 dp 十分 naive 不知道为什么 CF 的评分会很高，奇了怪了。

然后需要知道的是，为什么天数大部分人开的都是 $1e4$？这个可以算一波。由于概率 $p$ 发生的事件期望 $\dfrac{1}{p}$ 次实验会发生，那么不难知道凑齐所有的期望天数就是。

$$
\sum_{i=1}^{n}\frac{n}{n-i+1}
$$

那么也就是调和级数 $n\cdot H(n)$，是 $O(n\ln n)$ 级别的，所以开 $1000\cdot \ln 1000$ 就好了。

---

## 作者：fanypcd (赞：2)

$f_{i,j}$ 表示 $i$ 天选出 $j$ 种互不相同的数的概率。

如果第 $i$ 天选的是没选过的，概率 $\frac{n - j + 1}{n}$，这样从 $f_{i-1,j-1}$ 转移过来，如果第 $i$ 天选的是选过的，概率 $\frac{j - 1}{n}$，从 $f_{i-1,j}$ 转移过来。

转移方程：

$$f_{i,j}=f_{i-1,j-1}\times \frac{n - j + 1}{n} + f_{i-1,j} \times \frac{j - 1}{n}$$

数组范围看着不超时开就好。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
inline void read(int &x)
{
	x = 0;
	int f = 0;
	char ch = getchar();
	while(ch < '0' || ch > '9')
	{
		f |= ch == '-';
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9')
	{
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	x = f ? -x : x;
	return;
}
#define N 1005
int n, q;
double f[N << 5][N];
signed main()
{
	read(n), read(q);
	f[0][0] = 1;
	for(int i = 1; i <= n << 5; i++)
	{
		f[i][0] = 1;
		for(int j = 1; j <= min(i, n); j++)
		{
			f[i][j] = f[i - 1][j - 1] * (double)(n - j + 1) / n + f[i - 1][j] * (double)(j - 1) / n;
		}
	}
	int p;
	while(q--)
	{
		read(p);
		for(int i = 0; i <= n << 5; i++)
		{
			if(f[i][n] >= ((double)p / 2000))
			{
				printf("%d\n", i);
				break;
			}
		}
	}
	return 0;
}
```

---

## 作者：lytqwq (赞：1)

设 $f_{i,j}$ 表示已经取了 $i$ 件物品，再取 $j$ 次恰好取完的概率

边界：

$f_{k,i}=1$ $(0 \le i)$

$f_{i,0}=0$ $(0\le i< k)$

有状态转移方程：

$$
f_{i,j}= \frac{k-i}{k} \times f_{i+1,j-1} + \frac{i}{k} \times f_{i,j-1}
$$

因为 $p_i\le1000$ ，我们询问的最大概率为 $\frac{1}{2}$

我们猜测这个 $j$ 不会很大，打表发现确实，这个 $j$ 最大是 $7274$ 

然后我们就二分答案就完了

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1010;
int k,q,p[N],vis[N][N*10];
long double f[N][N*10];
long double F(int x,int y){
	if(x==k)return 1;
	if(y==0)return 0;
	if(vis[x][y])return f[x][y];
	vis[x][y]=1;
	f[x][y]=(k-x)*1.0/k*F(x+1,y-1)+x*1.0/k*F(x,y-1);
	return f[x][y];
}
int main(){
	scanf("%d%d",&k,&q);
	for(int i=1;i<=q;i++){
		scanf("%d",&p[i]);
		int l=0,r=8000,mid;
		while(l<r){
			mid=(l+r)>>1;
			if(F(0,mid)>=p[i]*1.0/2000){
				r=mid;
			}
			else{
				l=mid+1;
			}
		}
		printf("%d\n",l);
	}
	return 0;
}
/*
1000 100

*/
```





---

## 作者：123hh2 (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF768D)

---

### 前言

说实话这个翻译我确实没怎么看懂，大概 10 分钟 + 上了个厕所之后才知道这道题要干什么，应该是我太蒻辣/kk

---

### 题目大意

给定一个物品数 $k(1 \le k \le 1000)$，每个物品都是无限个，每天你可以随机获得到一个物品，每种物品获得的概率都是 $\frac{1}{k}$。给定 $q(1 \le q \le 1000)$ 组询问，每个询问给定一个值 $p(1 \le p \le 1000)$，问最少在多少天时集齐这 $k$ 个物品的概率大于 $\frac{p}{2000}$。

---

### 分析

概率dp

我们设 $dp[i][j]$ 表示第 $i$ 天，取到了 $j$ 件不重复的物品的概率

一般的概率dp 都是顺推的，这个也不例外，考虑如何递推

发现 $dp[i][j]$ 的状态可以从 $dp[i-1][j]$ 和 $dp[i-1][j-1]$ 转移过来

- 从 $dp[i-1][j]$ 转移过来

这表示在 $dp[i-1][j]$ 这个状态时，拿到了一个重复的物品从而转移到了 $dp[i][j]$

那么在 $dp[i-1][j]$ 这个状态时拿到重复物品的概率为 $\frac{j}{n}$

所以有转移方程 $dp[i][j] = dp[i-1][j] \times \frac{j}{n}$

- 从 $dp[i-1][j-1]$ 转移过来

这表示在 $dp[i-1][j-1]$ 这个状态时，拿到了一个没有重复的物品从而转移到了 $dp[i][j]$

那么在 $dp[i-1][j-1]$ 这个状态时拿到了一个没有重复的物品的概率为 $\frac{n-j+1}{n}$

所以有转移方程 $dp[i][j] = dp[i-1][j-1] \times \frac{n-j+1}{n}$

显然边界为 $dp[0][0] = 1$

这时候我们发现一个问题，我们不确定 dp 的第一维，也就是天数的上界是多少

那么我们可以考虑对极限数据进行测试，当 $k = 1000$，$p = 1000$ 时，测出来是 7274

所以第一维开 1e4 就行了

最后的答案就是遍历一遍 dp 数组然后找第一个比所需概率大的值所对应的天数就好了

其实也可以二分查找，因为这个概率必然是单调递增的，不过对于这道题的数据范围来说意义不大，为了防止二分出锅，个人建议还是遍历一遍数组为好

---

### 代码

遍历数组版


```cpp
//you have no way to return
#include<bits/stdc++.h>
#define ri register
#define in inline
// #include<Windows.h>
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();while(ch>'9'||ch<'0') {if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') {x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}return x*f;
}
void write(int x) {if(x<0) x=-x,putchar('-');if(x>9) write(x/10);putchar(x%10+'0');}
//设 dp[i][j] 表示第 i 天，取到了 j 件不重复的物品的概率
int k,q;double dp[10001][1001];
signed main()
{
	k=read(),q=read();dp[0][0]=1;
	for(ri int i=1;i<=10000;i++)
	{
		for(ri int j=1;j<=k;j++)
		{
			dp[i][j]+=dp[i-1][j-1]*double(k-j+1)/double(k);
			dp[i][j]+=dp[i-1][j]*double(j)/double(k);
		}
	}
	while(q --> 0)
	{
		double p=read();double now=p/2000.0;
		// cout<<now<<endl;
		for(ri int i=1;i<=10000;i++)
		{
			// cout<<dp[i][k]<<" ";
			if(dp[i][k]>=now) {write(i),puts("");break;}
		}
	}
	return 0;
}
```

二分查找版，实测好像并不是很快

```cpp
//you have no way to return
#include<bits/stdc++.h>
#define ri register
#define in inline
// #include<Windows.h>
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();while(ch>'9'||ch<'0') {if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') {x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}return x*f;
}
void write(int x) {if(x<0) x=-x,putchar('-');if(x>9) write(x/10);putchar(x%10+'0');}
//设 dp[i][j] 表示第 i 天，取到了 j 件不重复的物品的概率
int k,q;double dp[10001][1001];
signed main()
{
	k=read(),q=read();dp[0][0]=1;
	for(ri int i=1;i<=10000;i++)
	{
		for(ri int j=1;j<=k;j++)
		{
			dp[i][j]+=dp[i-1][j-1]*double(k-j+1)/double(k);
			dp[i][j]+=dp[i-1][j]*double(j)/double(k);
		}
	}
	while(q --> 0)
	{
		double p=read();double now=p/2000.0;
		int l=k,r=10000,ans=0;
		while(l<=r)
		{
			int mid=(l+r)>>1;
			if(dp[mid][k]>=now) ans=mid,r=mid-1;
			else l=mid+1;
		}
		write(ans),puts("");
	}
	return 0;
}
```

---

## 作者：pokefunc (赞：0)

### 题目描述

有 $n$ 种物品，每天等概率的取 $n$ 种物品中的一个物品，问多少天后拿到所有物品的概率 $\ge {p \over 2000}$。

### 题解

~~（考前复习概率DP，顺便水个题解）~~

定义 $f(i,j)$ 为在前 $i$ 天取出了 $j$ 种物品的概率。

边界：$f(0,0)=1,f(0,i)=0\quad \forall i \in [1..n]$（最开始什么也没有）

转移：
$$
f(i,j)=f(i-1,j-1)\times {n-j+1 \over n}+f(i-1,j)\times {j \over n}
$$
转移方程中，第一部分是在这一天取到没取过的物品，第二部分是这一天取到取到过的物品。

答案：

这部分比较麻烦，但是观察数据范围 $n,p \le 1000$，取 $n,p=1000$ 得 $ans=7274$，因此开 $7500$ 以上就好了。

又有 $q=1000$，所以答案的统计从前往后暴力统计就好了。

时间复杂度：$O (np+q \times {\rm maxans})$，其中 $\rm{maxans}$ 为答案的最大值。

### Code

```cpp
#include<cstdio>
inline int read(){int x(0),op(0);char ch=getchar();while(ch<'0'||ch>'9')op|=(ch==45),ch=getchar();while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch^48),ch=getchar();return op?-x:x;}
double f[10001][1001];
int n,q;
int main(){
	n=read();q=read();
	f[0][0]=1.0;
    for(int i=1;i<=n;++i)f[0][i]=0;
	for(int i=1;i<=10000;++i)
		for(int j=1;j<=n;++j)
			f[i][j]=f[i-1][j-1]*((n-j+1)*1.0/n)+f[i-1][j]*(j*1.0/n);
	while(q--){
		int x=read();
		for(int i=1;i<=10000;++i)if(f[i][n]>(x*1.0/2000)){
			printf("%d\n",i);
			break;
		}
	}
	return 0;
}
```



---

## 作者：5k_sync_closer (赞：0)

题意：有 $N$ 种物品，每天随机取一件，取到每种物品的概率相同。

存在天数 $k$，使得 $k$ 天内取过 $N$ 种物品的概率不小于 $\dfrac p{2000}$。

多组询问，每组询问给定 $p$，求 $k$ 的最小值。
# 思路
考虑概率 DP。设 $f_{i,j}$ 为 $i$ 天内取过 $j$ 种物品的概率。

分类讨论 $i$ 天内取过 $j$ 种物品的前提下，第 $i$ 天取的物品 $i-1$ 天内是否取过。

若第 $i$ 天取的物品 $i-1$ 天内取过，则 $i$ 天内取过 $j$ 种物品的概率为 $f_{i-1,j}\times\dfrac jn$。

若第 $i$ 天取的物品 $i-1$ 天内没取过，则 $i$ 天内取过 $j$ 种物品的概率为 $f_{i-1,j-1}\times\dfrac{n-j+1}n$。

综上所述，$f_{i,j}=f_{i-1,j}\times\dfrac jn+f_{i-1,j-1}\times\dfrac{n-j+1}n$。

预处理到 $f_{10000,n}$，每组询问暴力找 $k$ 即可。
# 代码
```cpp
#include <cstdio>
int n, i, q;double p, f[10050][1050];
int main()
{
    scanf("%d%d", &n, &q);f[0][0] = 1;for(int i = 1;i <= 10000;++i) for(int j = 1;j <= n;
    ++j) f[i][j] = f[i - 1][j] * j / n + f[i - 1][j - 1] * (n - j + 1) / n;while(q--)
    {scanf("%lf", &p);p /= 2000;for(i = 1;f[i][n] < p;++i);printf("%d\n", i);}return 0;
}
```


---

## 作者：ssss41 (赞：0)

一个比较套路的概率 dp。

首先根据题意设计状态，设 $f_{i,j}$ 表示在 $i$ 天里选过了 $j$ 种物品的概率，因此得出边界条件 $f_{0,0}=1$

考虑转移，发现会有两种状况，即可能摸到的是 $j$ 种里面的物品，也可能是一个新的物品，需分情况讨论。

- 摸到的是 $j$ 种里面的物品

因为摸到的种类并没有增加，所以此时要从 $f_{i-1,j}$ 中转移过来，而摸到 $j$ 种之一的概率为 $\dfrac{j}{n}$，因此此时的转移方程为：

$$f_{i,j}=f_{i-1,j} \times \dfrac{j}{n}$$

- 摸到的是新的物品

增加了一个种类，从 $f_{i-1,j-1}$ 中转移过来，以前已经摸到了 $j-1$ 种物品，所以摸到新物品的概率是 $\dfrac{n-j+1}{n}$，此时方程为：

$$f_{i,j}=f_{i-1,j-1} \times \dfrac{n-j+1}{n}$$

算总方案数只需要把两个相加起来。

对于每一个询问把数组扫一遍统计答案就好。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, q; double f[10005][1005], p;//数组范围可以跑极限数据测一下
int main () {
	scanf ("%d%d", &n, &q);
	f[0][0] = 1;
	for (int i = 1; i <= 10000; ++ i) 
		for (int j = 1; j <= n; ++ j) {
			f[i][j] += (double)j / n * f[i - 1][j];
			f[i][j] += (double) (n - j + 1) / n * f[i - 1][j - 1];
		}
	while (q --> 0) {
		scanf ("%lf", &p); p /= 2000;
		for (int i = 1; i <= 10000; ++ i) 
			if (f[i][n] >= p) {printf ("%d\n", i); break;}
	}
}
```

---

## 作者：first_fan (赞：0)

`概率dp的模板题。`

题意非常简洁，就是要求一次取一件把所有种类取遍的概率不小于给定值的最小天数。

令$\sf f[i][j]$表示前$i$次取出了$j$种的概率，则发现可以递推：

* 前$i$次取出了$j$种的概率可以由**前$i-1$次取出$j$种的概率**与**再次选中这j种物品的概率**$\frac{j}{n}$转移得来;

* 前$i$次取出了$j$种的概率可以由**前$i-1$次取出$j-1$种的概率**与**选中其他种类的概率**$\frac{n-j+1}{n}$转移得来;

$$\sf\large f[i][j]=f[i-1][j]*\frac{j}{n}+f[i-1][j-1]*\frac{n-j+1}{n}$$

根据这个式子，先处理出$f[10^4][n]$，再$O(1)$回答就好了。

```cpp
#include <bits/stdc++.h>
#define ri int
#define ll long long
#define db double
using namespace std;

int read()
{
	int num=0;
	int flg=1;
	char c=getchar();
	while(!isdigit(c))
	{
		if(c=='-')
		{
			flg=-1;
		}
		c=getchar();
	}
	while(isdigit(c))
	{
		num=(num<<1)+(num<<3)+(c^48);
		c=getchar();
	}
	return num*flg;
}

const int maxn=11250;
db f[maxn][2019];

int main()
{
	int n=read();
	int q=read();
	f[0][0]=1.0;
	for(ri i=1; i<=11000; i++)
	{
		for(ri j=1; j<=n; j++)
		{
			f[i][j]+=f[i-1][j]*j/n;
			f[i][j]+=f[i-1][j-1]*(n-(j-1))/n;
		}
	}
	while(q--)
	{
		db p=read()/2000.0;
		for(ri i=1;i<=11000;i++)
		{
			if(f[i][n]>p)
			{
				printf("%d\n",i);
				break;
			}
		}
	}
}
```

---

