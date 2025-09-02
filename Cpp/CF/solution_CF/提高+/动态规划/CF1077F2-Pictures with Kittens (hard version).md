# Pictures with Kittens (hard version)

## 题目描述

简单版和困难版的唯一区别在于约束条件。

Vova 喜欢带有小猫的图片。他所使用的社交网络的新闻推送可以表示为一个长度为 $n$ 的连续图片数组（当然，每张图片都有小猫）。Vova 喜欢所有这些图片，但有些图片比其他的更美丽：第 $i$ 张图片的美丽值为 $a_i$。

Vova 想要转发恰好 $x$ 张图片，要求满足：

- 新闻推送中每一段长度至少为 $k$ 的连续图片中，至少有一张被 Vova 转发；
- 被转发图片的美丽值之和尽可能大。

例如，如果 $k=1$，那么 Vova 必须转发新闻推送中的所有图片。如果 $k=2$，那么 Vova 可以跳过一些图片，但对于每一对相邻的图片，Vova 必须至少转发其中一张。

你的任务是计算在满足上述条件的情况下，Vova 能够转发的图片美丽值之和的最大值。如果无法满足所有条件，则输出无解。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5 2 3
5 1 3 10 1
```

### 输出

```
18
```

## 样例 #2

### 输入

```
6 1 5
10 30 30 70 10 10
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
4 3 1
1 100 1 1
```

### 输出

```
100
```

# 题解

## 作者：龙潜月十五 (赞：27)

## 一、前言

本题几乎是**单调队列优化 DP** 的裸题。这是一种很常见也很管用的优化方法。本篇题解将梳理**解题思路**与介绍**单调队列的实现**，希望能加深对这种方法的理解。

## 二、题意

有一个长度为 $n$ 的数列，你需选择 $m$ 个元素，使得连续的 $k$ 个元素中都**至少有一个被选中**。求所选出的数的和的**最大值**。

## 三、思路

首先我们为什么会想到 DP 求解呢？因为本题所求的是**最大值**。像此类**最优解问题**，方法大致有三：

1. **DFS**（像此题的数据范围，绝不可能使用）。

2. 发现某些**特殊性质**或**规律**，再用**数学方法**或**贪心**求解（本题似乎找不什么规律）。

3. 符合**最优子结构**和**无后效性**，用**动态规划**。

经过分析，可知我们要使用动态规划。

## 四、动态规划

### （1）状态

由于题目中会影响答案的有**已经选了几个元素**和**选了什么元素**，因此我们可以将其写进状态中。当然选了什么元素太宽泛，我们可以**加限制**，使状态更好表达。设 $f(i,j)$ 表示**已经选了 $j$ 个元素，且第 $j$ 个选的是第 $i$ 个元素时的最大和**。

### （2）转移

$$f(i,j)=\max_{t=i-k}^{i-1} \{ f(t,j-1) \}+a(i)$$

由于题目要求**连续的 $k$ 个元素至少有一个被选到**，因此我们转移到 $f(i,j)$ 需要保证前一个区间是合法的（有一个数被选到），因此 $t$ 的范围只能是 $i-k \leq t \leq i-1$。

### （3）答案

最后在在 $f(n-k+1,m) \sim f(n,m)$ 中取最大值。
## 五、单调队列

- 单调队列常用于一些**区间的信息查询**（如区间的**最大值**、**最小值**等），时间复杂度为 $O(n)$。


- 单调队列虽说可以用 STL 的双端队列 deque，但众所周知 STL 常数大，还是建议**手写**，用**数组**代替。

- 这里我会举本题代码为例，介绍单调队列的实现。

- 单调队列大致分三步：

1. 去除队首“过期”的元素（**~~它们可以退役了 ——by wcr~~**），使区间符合要求。

```cpp
while(he<=ta&&que[he]<i-k)//不符合要求
	he++;//去除队首元素
```

2. 加入新元素，去除队尾不符合要求的元素（**~~比你小还比你强，你就永远打不过它~~**）。

```cpp
while(he<=ta&&f[i][j-1]>=f[que[ta]][j-1])//去除队尾不合要求的答案
	ta--;
que[++ta]=i;//加入新元素
```

3. 更新答案（视题目要求而定）。

```cpp
if(he<=ta)//如果有元素
	f[i][j]=f[que[he]][j-1]+a[i];//进行转移
```

## 六、注意点

- 要判一下无解的情况

```cpp
if(n/k>m)//判断无解的情况 
	return printf("-1"),0;
```

- $f$ 数组的初始化

```cpp
for(int i=0;i<=n;i++)
	for(int j=0;j<=m;j++)
		f[i][j]=-INF;//INF 得是一个足够大的数（比如 1e18）
f[0][0]=0;
```
- 因为 $a\le 10^9$ 且有加法运算，所以不开 long long 见祖宗。


---

## 作者：wkjwkj (赞：13)

对于本题，显然用 $\mathtt{dp}$​​ 求解。

我们用 $\mathtt{f[i][j]}$​ 表示前 $i$​ 个数一共取 $j$​ 个且第 $i$​ 个一定取所得到的最大答案。

不难写出转移方程：

$$f[i][j]=max\{f[p][j-1]\}+a[i](i-k\le p<i)$$

若直接根据我们的转移方程进行，复杂度是 $O(n^3)$​，不能接受，我们需要进行优化。

注意到可以转移的区间长度是不变的，我们要求的即为区间 $[i-k,i-1]$​​ 内的最小值。

我们有两种选择，一种是采用 $\mathtt{ST}$ 算法，复杂度为 $O(n^2logn)$，可以通过本题。

自然也可以采用单调队列的方法。这就是裸的单调队列，直接用滑动窗口方法求解即可。

核心代码如下：

```cpp
for(int i=1;i<=n;i++)
{
	while(le<=ri&&q[le]+k<i)le++;
	f[i][j]=f[q[le]][j-1]+a[i];
	while(le<=ri&&f[i][j-1]>=f[q[ri]][j-1])ri--;
	q[++ri]=i;
}
```

本题还有一点需要注意，虽然我们通过单调队列，第一次更新即为最优答案，如果不进行初始化，但是本题可能会存在一种情况，即非法情况可能转移至合法情况，导致答案非法，说的清楚一点，即你的转移中可能会存在同一个数被加多次的情况，我们必须排除这种情况，即开始把 $\mathtt{f}$​ 数组赋为负无穷，否则得到的答案可能比正确答案大。

$\mathtt{AC}$ 代码如下：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,k,x;
ll f[5005][5005];
int q[5005];
int le=1,ri=0;
int a[5005];
int main()
{
	scanf("%d%d%d",&n,&k,&x);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	memset(f,0xcf,sizeof f);
	if(n/k>x){
		puts("-1");
		return 0;
	}
	f[0][0]=0;
	for(int j=1;j<=x;j++)
	{
		le=1,ri=0;
		q[++ri]=0;
		for(int i=1;i<=n;i++)
		{
			while(le<=ri&&q[le]+k<i)le++;
			f[i][j]=f[q[le]][j-1]+a[i];
			while(le<=ri&&f[i][j-1]>=f[q[ri]][j-1])ri--;
			q[++ri]=i;
		}
	}
	ll ans=0;
	for(int i=n-k+1;i<=n;i++)ans=max(ans,f[i][x]);
	printf("%lld\n",ans);
	return 0;
}
```



---

## 作者：jun头吉吉 (赞：10)

# CF1077F2 【Pictures with Kittens (hard version)】
[$\color{green}{\large{My\ Blog}}$](https://chen-jia-liang.gitee.io/blog/2020/10/18/%E9%A2%98%E8%A7%A3-CF1077F2-%E3%80%90Pictures-with-Kittens-hard-version-%E3%80%91/)
## 题意
给你一个数列$a$，你需要选择$x$个元素，使得连续的$k$个元素都至少有一个被选中。

请求出最大的选出来的所有数的和。

## 题解
假如我们用$f[i][j]$表示到第$i$个数，选择了$j$的最大和，那么：

$$f[i][j]=\max_{k=i-k+1}^{i-1}f[k][j-1]+a[i]$$

朴素的dp就是酱紫。但此时的复杂度为$\mathcal{O}(n^3)$，妥妥地$\texttt{TLE}$

考虑优化，算法的主要瓶颈在于求$max$，我们希望能更快地求出，这时候，$\text{单调队列}$就出现了。

对每一个$[j]$维护一个单调队列，辣么就可以维护并方便地求出那一个$\max$的值。具体操作就是普通的单调队列.
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read(){
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}
deque<int>q[6000];
int f[6000][6000];
int n,k,x;
//你需要选择x个元素，使得连续的k个元素都至少有一个被选中。
int a[6000];
signed main(){
    n=read();k=read();x=read();
    for(int i=1;i<=n;i++)a[i]=read();
    memset(f,-0x3f,sizeof f);
    f[0][0]=0;q[0].push_back(0);
    for(int i=1;i<=n;i++)
        for(int j=x;j>0;j--){
            //f[i][j]=max(f[k][j-1])+a[i]
            while(q[j-1].size()&&q[j-1].front()<i-k)q[j-1].pop_front();
            if(q[j-1].size()){
                f[i][j]=f[q[j-1].front()][j-1]+a[i];
                while(q[j].size()&&f[q[j].back()][j]<=f[i][j])q[j].pop_back();
                q[j].push_back(i);
            }
        }
    int ans=-0x3f3f3f3f;
    for(int i=n-k+1;i<=n;i++)ans=max(ans,f[i][x]);
    printf("%lld",ans>=0?ans:-1);
}
```

---

## 作者：BzhH (赞：5)

题解里好像没有和我做法一样的 ~~(指状态不一样)~~，那我就来发一篇，定义状态$f_{i,j}$表示当前选了$i$个数字,在第$j$个数字时的和的最大值


------------

那么很容易可以想出转移方程
$f_{i,j}=\max\limits_{0\le u<j}\limits^{1\le i \le x,0\le j\le n}f_{i-1,u}+a_j$

很显然直接$O(n^3)$转移是不行的,只能过24个点,别问我为什么知道,那么就可以考虑优化,去掉一维,仔细观察发现似乎可以用单调队列优化第三维,那么就可以用$O(n^2)$成功转移了
代码
```
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int N = 5005;
typedef long long ll;

ll f[N][N], a[N];
int q[N];

int main()
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            f[i][j] = -1e18;
    int n, k, m;
    scanf("%d%d%d", &n, &k, &m);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &a[i]);
    f[0][0] = 0;//初始状态
    for (int i = 1; i <= m; i++)
    {
        int front = 0, tail = -1;
        for (int j = 0; j <= n; j++)
        {
            if (front <= tail && q[front] < j - k)
                front++;
            if (front <= tail)
                f[i][j] = f[i - 1][q[front]] + a[j];
            while (front <= tail && f[i - 1][j] >= f[i - 1][q[tail]])
                tail--;
            q[++tail] = j;//单调队列优化
            //for (int u = 0; u < j; u++)
            //{
            //    if (j - u <= k)
            //        f[i][j] = max(f[i][j], f[i - 1][u] + a[j]);
            //}暴力转移的代码
        }
    }
    ll ans = -1;
    for (int i = n - k + 1; i <= n; i++)
        ans = max(ans, f[m][i]);
    printf("%lld", ans);
}
```
这里还可以有一个小优化,就是用滚动数组,实测加上滚动数组过后时间从$7.5s\to 2.97s$


---

## 作者：xixiup (赞：2)

## 思路分享

$n$ 个数中选 $m$ 个元素满足特定条件的问题，我们可以使用 $DP$。

考虑设 $dp_{i,j}$ 表示前 $i$ 个元素中选取了 $j$ 个元素且第 $i$ 个元素必须要选的情况，然后我们就可以得到状态转移方程：

$$
dp_{i,j}=\max\limits_{l=i-k}^{i-1}dp_{l,j-1}+a_i
$$

解释一下，就是选第 $i$ 个的情况需要从 $l \in \left[ i-k,i-1 \right]$ 转移过来，这样可以保证两个选取的元素之间的间隔至多为 $k-1$，即保证了答案符合要求。

但是这样朴素的转移是 $\Theta \left( n^3 \right)$ 的，会妥妥地 $TLE$ 飞，所以我们需要将每一个 $dp_{i,j}$ 转移的复杂度降到 $\Theta \left( 1 \right)$。

考虑在 $DP$ 从一个特定的区间取最大$/$最小值，我们可以考虑使用单调队列优化。

我们可以对于每一个 $j$ 开一个单调队列，维护区间 $l \in \left[ i-k,i-1 \right]$ 的 $dp_{l,j}$，就可以很好地处理这个问题了。

## 代码展示

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long//1e9*5e3会爆int
const int maxn=5010;
int n,m,k,a[maxn],dp[maxn][maxn];
deque<int>q[maxn];//单调队列
signed main(){
	cin>>n>>k>>m;//注意输入的顺序
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
	}
	memset(dp,0x80,sizeof(dp));//给dp赋初值
	dp[0][0]=0;//记得加上边界
	q[0].push_front(0);
	for(int i=1;i<=n;i++){
		for(int j=min(m,i);j>=1;j--){//这里要倒着跑，不然新加入的点会影响答案
			while(!q[j-1].empty()&&q[j-1].front()<i-k){//弹出超出范围的答案
				q[j-1].pop_front();
			}
			if(!q[j-1].empty()){//要有答案才能更新
				int l=q[j-1].front();
				dp[i][j]=dp[l][j-1]+a[i];
			}
			while(!q[j].empty()&&dp[q[j].back()][j]<=dp[i][j]){//加入新的元素
				q[j].pop_back();
			}
			q[j].push_back(i);
		}
	}
	int ans=-1;//ans直接赋为-1，等会方便输出
	for(int i=n-k+1;i<=n;i++){//最后一个要在[n-k+1,n]的范围内才满足题意要求
		ans=max(ans,dp[i][m]);
	}
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：Clouder (赞：2)

## Before the Beginning

本文同步发表于[笔者博客](https://www.codein.icu/cf1077f2/)

## 题意
给你一个数列 $a$，你需要选择 $m$ 个元素，使得连续的 $k$ 个元素都至少有一个被选中。  

需要你最大化选出来的所有数的和。  

## 解法

容易想到动态规划，定义 $f(i,j)$ 为前 $i$ 个元素选了 $j$ 个，且最后一个为 $i$ 时的最大和。   

连续 $k$ 个必须选一个，即限定转移范围为 $[i - k,i - 1]$，那么有转移方程：  

$$f(i,j) = \max \limits _{i - k \le p \le i - 1}f(p,j - 1) + a_i$$

朴素转移是 $O(n^3)$ 的，但看到连续区间取最大值，可以想到用单调队列优化。  

具体地，维护关于 $f(p,j - 1)$ 的 $[i - k,i - 1]$ 区间的最大值单调队列。最外层枚举选了的元素个数 $j$ 进行更新。  

最终复杂度 $O(n^2)$.  

空间上可以使用滚动数组稍微优化。  

判断无解的话，最后选的一个元素一定在 $[n - k + 1,n]$ 的区间内，设置初值为负无穷大，而 $f(0,0) = 0$ 进行合法转移即可。


```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <ctype.h>
using namespace std;
const int bufSize = 1e6;
inline char nc() { static char buf[bufSize], *p1 = buf, *p2 = buf; return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++; }
template<typename T> 
inline T read(T &r)
{
    static char c;
    r = 0;
    for (c = nc(); !isdigit(c); c = nc());
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r;
}
const int maxn = 5e3 + 100;
#define int long long
int n,k,x,a[maxn];
int cost[2][maxn],f[2][maxn],q[maxn],qt,qh;
signed main()
{
    read(n), read(k), read(x);
    for (int i = 1; i <= n; ++i) read(a[i]);
    int now = 0, last = 1;
    memset(f[last], ~0x3f, sizeof(f[last]));
    f[last][0] = 0;
    for (int j = 1; j <= x; ++j)  //choose j
    {
        qh = qt = 1, q[1] = 0;
        for (int i = 1; i <= n; ++i)
        {
            while (qt >= qh && i - q[qh] > k) ++qh;
            f[now][i] = f[last][q[qh]] + a[i];
            while (qt >= qh && f[last][q[qt]] <= f[last][i]) --qt;
            q[++qt] = i;
        }
        now ^= 1, last ^= 1;
    }
    int ans = -(1ll << 60);
    for (int i = n - k + 1; i <= n; ++i) ans = max(ans, f[last][i]);
    if (ans >= 0) printf("%lld\n", ans);
    else puts("-1");
    return 0;
}
```

---

## 作者：BlankAo (赞：0)

不难看出这是个DP，设 $f[i,j]$ 是前 $i$ 个数字，选了 $j$ 个数字，其中 $a[i]$ 必须选，不选相当于 $f[i-1,j-1]$ 。

初始状态为 $f[0,0]=0$ 其它的都为负无穷。我们很容易得出转移方程：

$$f[i,j]=\max(f[i-x,j-1])+a[i],x\in[1,k]$$

然后依次枚举 $i,j,x$ 就好啦~

但是，这样显然会TLE。我们用力思考，发现对于 $f[i-k,j-1],f[i-k+1,j-1],f[i-k+2,j-1]...f[i-1,j-1]$ 它们是单调不减的。

所以我们可以用**单调队列**去维护。我这里用了一个虽然开销大，但是也能过的方法：给每个 $j$ 维护一个单调队列，即 $que_j$ 存的是 $f[i-k,j] \sim f[i-1,j]$ 。设 $que_j$ 的**队头**为 $head_j$，如果 $head_j \le i-k-1$ ，那就表示距离上一个有效数字超过了限制，不能转移。否则，转移方程：

$$f[i,j]=f[head_{j-1},j-1]+a[i]$$

当 $f[i,1\sim m]$ 都转移完后，将它们推进队列中。注意，如果你转移完 $f[i,j]$ 后直接推进队列的话，待会 $f[i,j+1]$ 可能会由其而转移，导致出现错误。

答案就是 $\max\limits_{i=n-k+1}^{n}f[i,m]$

下面是代码（毒瘤码风）。个人习惯书写方便，我将题目中的 $k$ 由 $h$ 代替。

```c++
#include<bits/stdc++.h>
#define lon long long
using namespace std;
int n,m,h,a[5004];
lon ans,f[5004][5004];

struct MoquE{
	int qued[5004],head,tail;
	MoquE(){head=1,tail=0;}
	void updat(int id,int wei){
		while(head<=tail && qued[head]<=id-h)head++;
		while(head<=tail && f[ qued[tail] ][wei]<=f[id][wei])tail--;
		tail++,qued[tail]=id;
	}
	int query(int id){return qued[head];}
}que[5004];

int main(){
	scanf("%d%d%d",&n,&h,&m);
	if(n/h>m){printf("-1");return 0;}
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	
	memset(f,896,sizeof f);
	f[0][0]=0;
	
	que[0].updat(0,0);//f[0][0]=0
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m&&j<=i;j++){
			if(que[j-1].query(i)<=i-h-1)continue;
			f[i][j]=f[que[j-1].query(i)][j-1]+a[i];
		}
		for(int j=1;j<=m&&j<=i;j++)que[j].updat(i,j);
		if(i>=n-h+1)ans=max(ans,f[i][m]);
	}

	printf("%lld",ans);
	return 0;
}
```

---

## 作者：lgswdn_SA (赞：0)

题意：

>给你一个数列 $a$，你需要选 $m$ 个元素，使得连续的  $k$个元素都至少有一个被选中。  
需要你最大化选出来的所有数的和。

一道不难的 DP 题。

首先有一个 $O(nmk)$ 的 DP （[CF1077F1](https://www.luogu.com.cn/problem/CF1077F1)），$f(i,j)$ 表示为前 $i$ 个元素已经选了 $j$ 个元素的值。

$$
f(i,j)=\max _{p\in [i-k+1,i]} f(p-1,j-1)+a_p
$$

$p$ 代表 $a[p+1,i]$ 都不选然后选 $p$。

```cpp
namespace f1 {
	int f[209][209];
	void main() {
		memset(f,128,sizeof(f));
		rep(i,0,k-1) f[i][0]=0;
		rep(j,1,m) rep(i,1,n) {
			rep(p,max(1ll,i-k+1),i)
				f[i][j]=max(f[i][j],f[p-1][j-1]+a[p]);
		}
		printf("%lld\n",max(-1ll,f[n][m]));
	}
}
```

现在考虑优化。这个 $f(p-1,j-1)+a_p$ 是滑动窗口最大值且值与 $i$ 无关，可以用单调队列维护。所以对于每一个 $j$ 维护一个按照 $f(p-1,j-1)+a_p$ 排序的单调队列即可。

```cpp
namespace f2 {
	int f[N][N];
	struct monoque {
    	int q[N],size,l,r,g[N];
    	monoque(int x=0) {l=r=1;}
    	void maintain(int x) {
        	while(l<r&&x-q[l]>size) l++;
    	}
    	void clear() {l=r=1;}
    	void push(int x,int gg) {
    	    g[x]=gg;
     	    while(l<r&&g[x]>g[q[r-1]]) r--;
    	    q[r++]=x;
    	}
    	int max() {return g[q[l]];}
	}q;
	void main() {
		memset(f,128,sizeof(f));
		q.size=k-1;
		rep(i,0,k-1) f[i][0]=0;
		rep(j,1,m) {
			q.clear();
			q.push(0,f[0][j-1]);
			rep(i,1,n) {
				q.push(i,f[i-1][j-1]+a[i]);
				q.maintain(i);
				f[i][j]=q.max();
			}
		}
		printf("%lld\n",max(-1ll,f[n][m]));
	}
}
```

主函数：

```cpp
signed main() {
	scanf("%lld%lld%lld",&n,&k,&m);
	rep(i,1,n) scanf("%lld",&a[i]);
	if(n<=200) f1::main();
	else f2::main();
	return 0;
}
```

---

