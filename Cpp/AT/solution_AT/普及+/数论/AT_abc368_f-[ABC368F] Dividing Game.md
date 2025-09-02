# [ABC368F] Dividing Game

## 题目描述

给定一个长度为 $ N $ 的正整数列 $ A = (A_1, A_2, \dots, A_N) $，其中每个元素都大于等于 $ 2 $。Anna 和 Bruno 将使用这些整数进行游戏。游戏由 Anna 先手，两人轮流进行以下操作：

- 随意选择一个整数 $ i $（$ 1 \leq i \leq N $）。选择 $ A_i $ 的一个正的除数 $ x $（$ x $ 不能是 $ A_i $ 本身），并将 $ A_i $ 替换为 $ x $。

当某一方无法进行操作时，该方输掉游戏，另一方获胜。双方都采取最优策略时，判断谁会获胜。

## 说明/提示

### 限制

- $ 1 \leq N \leq 10^5 $
- $ 2 \leq A_i \leq 10^5 $
- 所有输入都是整数

### 示例解释 #1

以下是一个可能的游戏过程，但请注意，这并不一定是双方都采取最优策略的情况。例如：

- Anna 将 $ A_3 $ 替换为 $ 2 $。
- Bruno 将 $ A_1 $ 替换为 $ 1 $。
- Anna 将 $ A_2 $ 替换为 $ 1 $。
- Bruno 将 $ A_3 $ 替换为 $ 1 $。
- Anna 无法进行操作，因此 Bruno 获胜。
  实际上，在这个示例中，如果 Anna 采取最优策略，她总是可以获胜。

## 样例 #1

### 输入

```
3
2 3 4```

### 输出

```
Anna```

## 样例 #2

### 输入

```
4
2 3 4 6```

### 输出

```
Bruno```

# 题解

## 作者：chenxi2009 (赞：7)

# 题目描述
给你一个长度为 $N$ 的正整数序列 $A=(A_1,A_2,\cdots,A_N)$，其中每个元素都不小于 $2$。 
Anna 和 Bruno 在用这些数玩游戏，从Anna开始轮流进行以下操作：

- 自由地选择一个整数 $i(1\le i\le N)$。然后选择 $A_i$ 的一个因子 $x$（$x$ 不得是$ A_i$ 本身），用 $x$ 替换 $A_i$。

当轮到一位玩家进行操作时，若他无法进行上述操作，则判他输，另外一名玩家赢。请你推测若 Anna 和 Bruno 都用最优策略进行游戏时（他们都想获胜），哪名玩家会获得胜利。  
# 输入格式
第一行一个整数 $N$。  
第二行 $N$ 个整数 $A_1,A_2,\cdots,A_N$。
# 输出格式
如果最终 Anna 获胜输出 `Anna`，Bruno 获胜则输出 `Bruno`。
# 数据范围与约定
对于所有数据，$1\le N\le 10^5,2\le A_i\le10^5(1\le i\le N)$，且 $A_i$ 为整数。
# 解题思路
典型的博弈论题目。单向双倍经验与前置模板：[Nim 游戏](https://www.luogu.com.cn/problem/P2197)  

这是一个 Nim 游戏。每次操作取一个 $A_i$ 并用一个不等于它本身的因子替换它，相当于“除去”了其中的一些因子。每次操作最少除去一个质因子，最多去除全部。我们将 $A_i$ 进行质因数分解，得到它的质因子个数（可重），就可以将其转化为模板化的 Nim 游戏了。  
通俗地说，设 $A_i$ 分解质因数后得到的质因子个数为 $p_i$，那么题意所述的博弈与以下博弈等价：  

有 $N$ 个数的正整数数列 $p_1,p_2,\cdots,p_N$，每次操作可以选取一个正整数 $p_i$，使其减去一个在 $[1,p_i]$ 中自由选取的数。双方轮流操作，无法操作者输。  

再套入 Nim 游戏的经典结论（参考前置模板题），得出若 $p_1\oplus p_2\oplus\cdots\oplus p_N$ 值为 $0$，则后手（Bruno）获胜；否则先手（Anna）获胜。其中 $\oplus$ 表示按位异或。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,s,cnt;
int main(){
	scanf("%d",&n);
	for(int i = 1;i <= n;i ++){
		scanf("%d",&a);
		cnt = 0;
		for(int j = 2;j * j <= a;j ++){
			while(a % j == 0){//质因数分解
				a = a / j;
				cnt ++;//统计质因数个数
			}
		}
		if(a != 1){
			cnt ++;
		}
		s = s ^ cnt;//取异或和
	}
	if(s){
		printf("Anna");
	}
	else{
		printf("Bruno");
	}
	return 0;
} 
```
~~闲话：赛时把“Bruno”打成“Bruco”喜提一次罚时~~

---

## 作者：KobeBeanBryantCox (赞：5)

# AT_abc368_f [ABC368F] Dividing Game 题解

[题目传送门](https://www.luogu.com.cn/problem/AT_abc368_f)。

[双倍经验](https://www.luogu.com.cn/problem/AT_ddcc2020_final_a)。

at 最板子的一集。

**本题解用三种方法过这个题，其中两份代码分别为最优解第四和第二（不算并列，也就是只看时间不看代码长度）。**

~~不看代码长度的原因是我写了快读之类的很多没用的东西，所以这个不算。~~

~~讲个乐子，这个题正好是我当天上午做的模拟赛的原题，改一改就能过的那种。~~

----------------------------

## 题意

给你一个由 $N$ 个正整数 $A = (A_1, A_2, \dots ,A_N)$ 组成的序列，其中每个元素至少是 $2$ 。安娜和布鲁诺用这些整数玩一个游戏。他们轮流执行以下操作，安娜先执行。

- 自由选择一个整数 $i \ (1 \leq i \leq N)$ 。然后，自由选择一个不是 $A_i$ 本身的因数 $x$ 将 $A_i$ 改为 $x$ 。

不能进行操作的一方输，另一方赢。假定两位棋手都以最佳方式下棋，谁会获胜？

------------------------

## 分析

### 前置知识：

[Nim 游戏](https://www.luogu.com.cn/problem/P2197)、[分解质因子](https://www.luogu.com.cn/problem/B3715)、简单博弈论。（不需要知道 SG 函数，不过知道了更好）

下面用 SG 和非 SG 两部分讲解，不会 SG 的跳过到证明部分。

--------------------

### SG 函数

暴力枚举因子，即可得到 SG 函数。

代码如下（写的有点丑）：

```cpp
for(int i=2;i<=1e5;i++)
{
    vector<int>a;
    for(int j=1;j*j<=i;j++)
    {
        if(i%j==0)
        {
            a.push_back(sg[j]);
            if(j!=1)a.push_back(sg[i/j]);
        }
    }
    sort(a.begin(),a.end()),a.push_back(1e18);
    if(a[0]!=0)sg[i]=0;
    else for(int j=1;j<a.size()&&!sg[i];j++)if(a[j]-a[j-1]>1)sg[i]=a[j-1]+1;
}
```

然后打表发现 SG 函数的值是一个数的质因子个数。

举个例子，$12=2\times 2\times 3$，所以 $sg(12)=3$。

SG 函数的值为什么是这样的呢，看下面证明部分。

-----------------------

### 证明（即非 SG 函数方法）

对于一个数 $a$，可以将其分解为唯一分解定理的形式，即 $a=p_1\times p_2\times p_3\times \dots\times p_k$，其中 $p$ 为质数，并且可重复。

考虑 $a$ 的因数的唯一分解定理的形式，即为原来的 $p$ 集合少一个或多个 $p$ 乘起来。

举个例子：$12=2\times 2\times 3$，$6=2\times 3$，少了一个 $2$，所以 $6$ 是 $12$ 的因子。

即 SG 值是质因子个数。

-----------------------------------

## 解法

原问题转化为：给定 $a$ 集合，令 $b_i$ 为 $a_i$ 的质因子个数，每次从任意第 $i$ 堆的 $b_i$ 中拿走一个或多个，不能操作的算输。

这不就是简单的 Nim 游戏了吗，把 $b$ 异或一下，等于 $0$ 后手胜，否则先手胜。

关于找质因子个数，暴力质因数分解即可，理论时间复杂度 $O(n\sqrt V)$，其中 $V$ 为值域。

这样已经能过了，当然还有 $O(V_1\log V_2)$ 和 $O(n\times V^{\frac{1}{4}})$ 的做法，适用于值域较大的时候，会在最后讲，不想看的跳过吧。

----------------------

## 本题 AC 代码

这里我采用了筛质数的方法做质因数分解，不过也可以直接做。

$11$ 毫秒，最优解第四，[记录详情](https://www.luogu.com.cn/record/174608878)。

```cpp
#include<bits/stdc++.h>
#define Code using
#define by namespace
#define wjb std
Code by wjb;
#define int long long
int in()
{
	int k=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')k=k*10+c-'0',c=getchar();
	return k*f;
}
void out(int x)
{
	if(x<0)putchar('-'),x=-x;
	if(x<10)putchar(x+'0');
	else out(x/10),putchar(x%10+'0');
}
const int N=1e5+10;
int prime[N];
bool isprime[N];
void pri(int n)
{
	memset(isprime,true,sizeof(isprime)),isprime[1]=false;
	for(int i=2;i<=n;i++)
	{
		if(isprime[i])prime[++prime[0]]=i;
		for(int j=1;j<=prime[0]&&i*prime[j]<=n;j++)
		{
			isprime[i*prime[j]]=false;
			if(i%prime[j]==0)break;
		}
	}
}
int sg(int x)
{
	if(x==1)return 0;
	if(isprime[x])return 1;
	int sum=0;
	for(int i=1;i<=prime[0]&&prime[i]*prime[i]<=x;i++)
		while(x%prime[i]==0)x/=prime[i],sum++;
	if(x>1)sum++;
	return sum;
}
signed main()
{
	pri(1e5+1);
	int n=in();
	int sum=0;
	for(int i=1;i<=n;i++)sum^=sg(in());
	if(sum==0)puts("Bruno");
	else puts("Anna");
	return 0;
}
```

----------------------

## 关于 $O(V_1\log V_2)$ 和 $O(n\times V^{\frac{1}{4}})$ 的做法

### 1. $O(V_1\log V_2)$ 的做法

其中 $V_1$ 为值域范围，$V_2$ 为最大值域。

预处理质数（线性筛），由于质因子个数是加性函数，我们可以对于每一个质数往上乘，乘到的数的质因子个数加一即可，用一个桶（值域范围相差不大，即 $r-l$ 不大但是 $r$ 很大的情况下）或者 map 记录即可。

关于时间复杂度，令值域范围为 $V$，$V$ 中的数总共要被扫 $\frac{V}{2}+\frac{V}{3}+\frac{V}{5}+\dots$，这个正是调和级数，所以时间复杂度约等于 $O(V_1\log V_2)$。

#### 本题第二个 AC 代码：

$8$ 毫秒，最优解第二，[记录详情](https://www.luogu.com.cn/record/174617047)。

```cpp
#include<bits/stdc++.h>
#define Code using
#define by namespace
#define wjb std
Code by wjb;
#define int long long
int in()
{
	int k=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')k=k*10+c-'0',c=getchar();
	return k*f;
}
void out(int x)
{
	if(x<0)putchar('-'),x=-x;
	if(x<10)putchar(x+'0');
	else out(x/10),putchar(x%10+'0');
}
const int N=1e5;
vector<int>prime;
bool vis[N+10];
void initprime(int n)
{
	memset(vis,0,sizeof(vis));
	for(int i=2;i<=n;i++)
	{
		if(!vis[i])prime.push_back(i);
		for(int j=0;j<prime.size()&&i*prime[j]<=n;j++)
		{
			vis[i*prime[j]]=1;
			if(i%prime[j]==0)break;
		}
	}
}
int cnt[N+10],val[N+10];
void init(int l,int r)
{
	memset(cnt,0,sizeof(cnt));
	int n=r-l+1;
	for(int i=0;i<n;i++)val[i]=l+i;
	for(int p:prime)
		for(int x=(l+p-1)/p*p;x<=r;x+=p)
		{
			int t=x-l;
			while(val[t]%p==0)val[t]/=p,cnt[t]++;
		}
	for(int i=0;i<n;i++)if(val[i]>1)cnt[i]++;
}
vector<int>a;
bool solve()
{
	initprime(1e5+1);
	init(1,1e5+1);
	int sum=0;
	for(int x:a)sum^=cnt[x-1];
	return sum==0;
}
signed main()
{
	int n=in();
	for(int i=1;i<=n;i++)a.push_back(in());
	if(solve())puts("Bruno");
    else puts("Anna");
	return 0;
}
```

### 2. $O(n\times V^{\frac{1}{4}})$ 的做法

思路基本与第一种一样，只不过求质因子个数不要用普通的，用 Pollard-Rho 来求质因子个数，复杂度期望 $O(n\times V^{\frac{1}{4}})$，但是由于 Miller-Rabin 的测试次数过多，所以比暴力还慢，不过还是能过。

关于 Pollard-Rho，看[这个](https://blog.csdn.net/qq_43449564/article/details/123979433?spm=1001.2101.3001.6650.2&utm_medium=distribute.pc_relevant.none-task-blog-2~default~BlogCommendFromBaidu~Rate-2-123979433-blog-87886418.235^v43^pc_blog_bottom_relevance_base1&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2~default~BlogCommendFromBaidu~Rate-2-123979433-blog-87886418.235^v43^pc_blog_bottom_relevance_base1&utm_relevant_index=3)和[这个](https://www.luogu.com.cn/problem/P4718)就行了。

#### 本题第三个 AC 代码：

445 毫秒，喜提最劣解，[记录详情](https://www.luogu.com.cn/record/174632381)。

这么慢的原因应该是 Miller-Rabin 的测试次数太多了。

不过改少了过不了，不知道为什么。

```cpp
#include<bits/stdc++.h>
#define Code using
#define by namespace
#define wjb std
Code by wjb;
#define int long long
int in()
{
	int k=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')k=k*10+c-'0',c=getchar();
	return k*f;
}
void out(int x)
{
	if(x<0)putchar('-'),x=-x;
	if(x<10)putchar(x+'0');
	else out(x/10),putchar(x%10+'0');
}
int multi(int a,int b,int p){return a*b%p;}
int qpow(int a,int b,int p)
{
	int ans=1;
	for(;b;b>>=1,a=multi(a,a,p))if(b&1)ans=multi(ans,a,p);
	return ans;
}
int gcd(int a,int b){return b?gcd(b,a%b):a;}
const int test_time=30; // 原本写的是 8 过不了，改到 30 就能过了，所以考场上还是别写随机化算法吧，太悬了（平衡树除外
bool miller_rabin(int n)
{
	if(n<3||n%2==0)return n==2;
	int b=n-1,k=0;
	while(b%2)b/=2,k++;
	for(int i=0;i<test_time;i++)
	{
		int a=qpow(rand()%(n-2)+2,b,n);
		if(a==1)continue;
		int j=0;
		for(;j<k;j++)
		{
			if(a!=n-1)break;
			a=multi(a,a,n);
		}
		if(j==k)return false;
	}
	return true;
}
int f(int x,int c,int p){return (multi(x,x,p)+c)%p;}
int pollard_rho(int n,int c)
{
	int i=rand()%(n-1)+1,j=f(i,c,n);
	while(i!=j)
	{
		int d=gcd(abs(i-j),n);
		if(d>1)return d;
		j=f(f(j,c,n),c,n),i=f(i,c,n);
	}
	return n;
}
int find(int n)
{
	if(miller_rabin(n))return 1;
	int c=rand()%(n-1)+1,d=n;
	while(d>=n)d=pollard_rho(n,c--);
	return find(n/d)+find(d);
}
vector<int>a;
bool solve()
{
	int sum=0;
	for(int x:a)sum^=find(x);
	return sum==0;
}
signed main()
{
	srand(time(0)+114514);
	int n=in();
	for(int i=1;i<=n;i++)a.push_back(in());
	if(solve())puts("Bruno");
    else puts("Anna");
	return 0;
}
```

--------------------------

## 后记

如果题解写得不对，欢迎提出改正；如果讲得不清楚，欢迎提问。

---

## 作者：Milthm (赞：3)

拿到题一看，博弈论？完啦！

先转化一下，我们发现这个把一个数变成一个非自己的因数，相当于删去它的若干个质因子，而没有质因子能删的人就输了。所以如果一个数有 $x$ 个质因子，我们就把它看成一堆共 $x$ 个的石子。

现在问题变成了，有 $n$ 堆石子，每次每人从其中选一堆拿走大于 $0$ 个石子，没有石子能拿的人就输了。

哎？这个题目怎么这么熟啊？哦，这原来是[【模板】Nim 游戏](https://www.luogu.com.cn/problem/P2197)，所以我们只要求出每个数的质因子个数，异或起来看一下是不是 $0$ 即可。

暴力分解质因数的话是 $O(n \sqrt V)$ 的，当然还可以优化，不过已经足够了。


```cpp
#include<bits/stdc++.h>
#define int long long
#define N 400005
using namespace std;
int n,a[N],ans;
signed main(){
	cin>>n;
	for(int i=1;i<=n;++i){
		int x,r=0;cin>>x;
		for(int j=2;j*j<=x;++j){
			while(x%j==0)++r,x/=j;
		}
		if(x!=1)++r;
		ans^=r;
	}
	if(ans)cout<<"Anna";
	else cout<<"Bruno";
	return 0;
}
```

---

## 作者：luqyou (赞：3)

# 思路

简单博弈题。

我们可以发现，每次我们将一个数变成它的一个因数，相当于拿走这个数的若干质因子。

所以我们可以将每一个质因子看作一颗石子，直接做 Nim 即可。

---

## 作者：doumingze (赞：3)

博弈论显然，关键是可以转化成什么问题。

发现一个 $a_i$ 不能再被换掉，当且仅当 $a_i = 1$，即 $a_i$ 没有任何质因子。

我们可以发现，如果 $a_i$ 被替换，本质上是去掉了 $a_i$ 的一些质因子。那么我们可以处理出一个 $a_i$ 的质因子数量，这个题就变成了一个经典的 Nim 游戏，去掉质因子就可以看成取走物品，每一堆总共可以取的物品数量就是这一堆的 $a_i$ 的质因子数量。

如果对 Nim 游戏不熟悉的同学，[移步这里看个结论/证明](https://oi-wiki.org/math/game-theory/impartial-game/#nim-%E5%92%8C)。

代码看看罢，只放关键部分防止抄袭，没啥好说的。

```cpp
int primes[N], cnt;
bool st[N];
int mdiv[N], cc[N];

void get_primes(int n)
{
  //略。
  //处理出所有的质数放入 primes 数组中，共有 cnt 个；并处理出每个数 i 的最小质因子 mdiv[i]。
  //primes内的下标为 0 ... cnt - 1。
}
void deco()
{
	cc[1] = 0;
	for(int i = 2, t = 0; i <= 100000; i ++)
	{
		t = i;
		while(mdiv[t] != t) t /= mdiv[t], cc[i] ++;
		cc[i] ++;
	}
}

int main()
{
	get_primes(100000);
	deco();
	int n;
	cin >> n;
	int x, ans = 0;
	for(int i = 1; i <= n; i ++)
	{
		scanf("%d", &x);
		ans ^= cc[x];
	}
	if(ans) puts("Anna");
	else puts("Bruno");
	return -1;
}
```

---

## 作者：huangrenheluogu (赞：2)

容易发现是 $n$ 个子游戏。

对于每一个游戏，可以看成有若干个质因子，一次取 $1$ 个或多个质因子。容易看出对于一个有 $x$ 个质因子的游戏，这个游戏的 SG 函数是 $SG(x)=x$。

然后求一下 Nim 和就可以了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5, maxn = 1e5;
int n, a[N], cnt[N], x, sg;
inline void init(){
	for(int i = 2; i <= maxn; i++){
		x = i;
		for(int j = 2; j * j <= i; j++){
			while(x % j == 0){
				cnt[i]++;
				x /= j;
			}
		}
			if(x > 1) cnt[i]++;
	}
}
int main(){
	init();
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%d", &x);
		sg ^= cnt[x];
	}
	puts(sg ? "Anna" : "Bruno");
	return 0;
}
```

---

## 作者：vorDeal (赞：1)

前置知识：Nim 博弈、质因数分解。

“每次操作可以把这个数替换为非它本身的约数”，我们把它抽象为减少它的质因数的个数，一次可以减少任意个，于是就把问题转化为了一个 Nim 博弈问题，以一个数的质因数个数为一堆石子的个数。

时间复杂度 $O(n\sqrt a)$，可以通过本题。

[**AC Code。**](https://atcoder.jp/contests/abc368/submissions/57108238)

---

## 作者：Walrus (赞：1)

F 是一道比较基础的 Nim 博弈。

题库中有一道它的弱化版，可以先参考那题的题解（无法通过本题）。

这里直接给出那题的链接就不概括题意了。

[link](https://www.luogu.com.cn/problem/AT_ddcc2020_final_a)

## 做法

先手分析必胜态和必败态。

- 必败态：如果剩下的数都是 1 则当前操作人必败，这个比较显然。
- 必胜态：如果剩下的数有且仅有 1 个数不是 1，则当前操作人必胜。

再从数的变换方式入手，一个人可以把一个非 1 数直接变 1，但这样对于 2 人肯定不是最优的，他们肯定都会通过“走闲”来设法取得胜利。

走闲的话，如果是当前数是**质数**就只能变 1，如果是**合数**就可以走闲。

但是其实只有某些合数可以被同一个 $x$ 替换成 1，这些合数才能被利用。可以根据第一个样例想想。

分析到这里，其实结论已经有了，接下来就是板子的事。

```cpp
#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++i)
#define pre(i, j, k) for(int i = j; i >= k; --i)
#define pb push_back
#define int long long
using namespace std;
const int N = 2e5 + 5;
int n, x, f;
int a[N];

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cin >> n;
	rep(i, 1, n) {
		cin >> x;
		rep(j, 2, sqrt(x)) {
			while(x % j == 0) 
				x /= j, ++a[i];
		}
		if(x != 1) ++a[i];
		f ^= a[i];
	}
	cout << (f ? "Anna" : "Bruno");
	return 0;
}
```

---

## 作者：liruixiong0101 (赞：1)

# F - Dividing Game
## 题意：
Anna 和 Bruno 在玩一个游戏。给定一个长度为 $n$ 的序列 $a_1,a_2,\cdots,a_n$，每次操作 Anna 或 Bruno 可以选择序列中的一个数，将其变成其因数（但不能不变），请问若 Anna 先手，双方都已最佳方式玩游戏，谁会取胜。（$1\le n\le 10^5,2\le a_i\le 10^5$）

## 思路：
先将每个 $a_i$ 分解质因数，发现操作就相当于在 $a_i$ 的质因数中去掉几个（但不能不去），质因数全去掉就不能继续对 $a_i$ 操作。设 $c_i$ 为 $a_i$ 的质因数个数（可以用筛法求出），那么题目就转化成了 Nim 游戏。

## 代码：
<https://atcoder.jp/contests/abc368/submissions/57065741>

---

## 作者：_xxxxx_ (赞：1)

纪念最水的 F 题。

### 题意

现在给你一个有 $n$ 个数的数列 $A$。每次操作可以将一个数变成她的一个因子（不含本身），不能操作算输，问最后先手是否有必胜策略。

### 分析

看起来挺板的。

每个数可以变成她的因子，从这里我们可以考虑对每一个 $A_i$ 进行质因数分解。这些就是她能够转移过来的地方。

每转移一次，都会减少还能转移的可能。每次只能拿一堆。这些条件引导我们想到 Nim 博弈。

进行质因数分解后，出来的质因数就是一堆石子，然后就变成了一个经典的 Nim 博弈了。

### 代码

可能看代码会更清晰一点。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 5e6 + 10;
int n, a[N];
int sg[N], ans;
// int b[N], le;
int cnt[N];//存下来这一堆石子的个数，即质因数数量
void calc()
{
    for(int i = 1; i <= n; i++)
    {
        for(int j = 2; j * j <= a[i]; j++)
        {
            while(a[i] % j == 0)
            {
                a[i] /= j;
                cnt[i]++;
            }
        }
        if(a[i] > 1) cnt[i]++;
    }
    //分解质因数
}
signed main()
{
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];
    calc();
    for(int i = 1; i <= n; i++) ans ^= cnt[i];//经典Nim
    if(ans == 0) cout << "Brnue\n";
    else cout << "Anna\n";
    return 0;
}
```

不抄代码，从我做起（有防抄）。

---

## 作者：xxseven (赞：1)

很好的博弈论入门题。  
前置知识：[P2197 【模板】Nim 游戏](https://www.luogu.com.cn/problem/P2197)

### 题意简述：

有 $n$ 个大于 $1$ 的正整数，先后手交替进行操作，每次操作可以选择一个数，将其变为它的不为自身的因数，无法操作的一方败。  
问最佳策略下哪一方获胜。

### 解题思路：

对于因子一类的问题，我们一般将一个数质因数分解后再考虑。我们可以发现每次操作的本质是选择任意多个原数的可重复的质因子，将其从原数中除去。

每次操作可以减去任意多个质因子，数为 $1$ 时即质因子个数为 $0$ 时不能再次操作，那么这个问题就被我们转化为了一个 Nim 游戏。

将每个数转化为它的可重复的质因子个数，然后根据 Nim 游戏的结论判断异或和是否为 $0$ 即可。

下面是加了注释的赛时代码：  
~~感觉我写的好蠢啊为什么要线性筛啊~~


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+6;
int n,p[N],a[N],ans,idx;
bitset<N> b; 
void init(int n){ //线性筛
	for(int i=2;i<=n;++i){
		if(!b.test(i)) p[++idx]=i;
		for(int j=1;j<=idx&&i*p[j]<=n;++j){
			b.set(i*p[j]); 
			if(i&p[j]==0) break;
		}
	}
}
int main(){
	cin>>n; init(400);
	for(int x,i=1;i<=n;++i){
		cin>>a[i]; x=0;
		for(int j=1;j<=idx;++j){
			while(a[i]%p[j]==0) a[i]/=p[j],x++; //每有一个质因子，权值+1
			if(a[i]==1) break;
		}
		if(a[i]!=1) x++;
		ans^=x;//根据异或和判定游戏结果
	} 
	cout<<(ans==0?"Bruno":"Anna");
	return 0;
}

```

希望这篇题解能够帮到你！

---

## 作者：coding_goat (赞：1)

注意到对于每一个数都可以拆分成 $\prod p_i^{k_i}$，故每一个数可被操作 $\sum k_i$ 次。于是此题等同于尼姆博弈，用素数筛筛出一个数可被操作的次数，再用尼姆博弈的公式计算即可。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define mem(a,b) memset((a),(b),sizeof(a))
#define lb(x) ((x)&-(x))
#define lc(x) ((x)<<1)
#define rc(x) (((x)<<1)|1)
#define pb(G,x) (G).push_back((x))
using namespace std;
inline int read()
{
	int xx=0;int f=1;
	char c = getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-') f = -1;
		c = getchar();
	}
	while(c>='0'&&c<='9')
	{
		xx = (xx<<1)+(xx<<3)+(c^48);
		c = getchar();
	}
	return xx*f;
}
#define maxn 200050
int n,a[maxn];
bool prime[maxn];
int cnt[maxn];
void pre_prime()
{
	for(int i=2;i<=100000;i++)
	{
		if(prime[i]) continue;
		for(int j=2;i*j<=100000;j++)
		{
			prime[i*j]=1;
			int x=i*j;
			while(x%i==0)
			{
				cnt[i*j]++;
				x/=i;
			}
		}
	}
}
signed main()
{
	n=read();
	pre_prime();
	for(int i=1;i<=n;i++)
	{
		a[i]=read();
	}
	int ans=1;
	int x=0;
	for(int i=1;i<=n;i++)
		if(prime[a[i]])
			x^=cnt[a[i]];
		else x^=1;//因为 A_i>1
	if(x==0) ans^=1;
	cout<<(ans&1?"Anna":"Bruno");
	return 0;
}
```

---

## 作者：gyyyyx (赞：1)

SG 函数基础题。

这显然是一个公平组合游戏，$SG(x)=mex_{y\mid x}\{SG(y)\}$。

直接埃氏筛枚举因数，时间复杂度是 $O(n\ln{V})$，其中 $V$ 为值域。

当然由于数据范围小，我们直接 $\sqrt{V}$ 暴力枚举因数也是可以的。

```cpp
#include<bits/stdc++.h>
#define N 100005
using namespace std;
int n,sg[N],ans;
int main(){
	for(int i(2);i<N;++i){
		if(!sg[i]) sg[i]=1;
		for(int j(i*2);j<N;j+=i) sg[j]=max(sg[j],sg[i]+1);
	}
	scanf("%d",&n);
	for(int i(1),a;i<=n;++i) scanf("%d",&a),ans^=sg[a];
	puts(ans?"Anna":"Bruno");
	return 0;
}
```

---

## 作者：EricWan (赞：0)

确保你记好这里的所有内容：[SG 定理](https://oiwiki.com/math/game-theory/impartial-game/)

一眼博弈论暴力题。

做博弈题第一步永远是手玩，我们发现 $SG$ 函数不会太大，因此直接暴力计算，对于每一个状态 $i$，枚举它的所有因数，开一个桶维护因数的 $SG$ 函数值，直接找 $\text{mex}$，然后清空桶子，直接过了。

$SG$ 定理相关内容看 Wiki。

---

## 作者：Red_river (赞：0)

### 题目大意
两个人在一起玩游戏，自由选择不是 $A_i$ 本身的正除数 $x$，并用 $x$ 替换 $A_i$。不能执行操作的玩家输了，另一个玩家赢了。确定谁赢，假设两个玩家都非常聪慧，[公平组合游戏](https://oi.wiki/math/game-theory/impartial-game/)。
### 题意分析
想到这种又是两个人玩游戏的东西，正常人肯定会想到 `Nim` 游戏。没错，但是还是得先分析一下为什么可以用它来做。

- 将每个人所选取的数看作为原版的石头数。
- 将不能拿取 $A_i$ 本身看作为当 $A_i$ 为零时，该石头堆取完。

于是我们容易发现，原版中拿取的**石头个数**正好是该游戏中的**因数**中的任意一个，于是就可以用 `Nim` 来做了。具体可以参考代码及注释理解。

```cpp
#include<bits/stdc++.h>
#define wk(x) write(x),putchar(' ')
#define wh(x) write(x),putchar('\n')
#define ll long long
#define mod 998244353
#define N 50005
#define NO printf("No\n")
#define YES printf("Yes\n")
using namespace std;
int n,m,k,jk,ans,sum,num,cnt,tot;
int dis[N],vis[N],wis[N],f[N];

inline void read(int &x)
{
	x=0;int ff=1;char ty;
	ty=getchar();
	while(!(ty>='0'&&ty<='9'))
	{
		if(ty=='-') ff=-1;
		ty=getchar();
	}
	while(ty>='0'&&ty<='9')
		x=(x<<3)+(x<<1)+ty-'0',ty=getchar();
	x*=ff;return;
}

inline void write(int x)
{
	if(x<0) x=-x,putchar('-');
	if(x>=10) write(x/10);
	putchar('0'+x%10);
	return;
}
//以上是快读快输。
signed main()
{
	read(n);int x=0;
	for(int i=1;i<=n;i++){
		read(x);sum=0;
		for(int j=2;j<=sqrt(x);j++){
			while(x%j==0) x/=j,sum++;//统计因数个数。
		}
		if(x>1) sum++;//还有因数没有算上。
		ans^=sum;//求异或和。
	}
	if(ans!=0) printf("Anna");//异或和不为零，先手胜。
	else printf("Bruno");//否则后手胜。
	return 0;
}
```

---

## 作者：Size_OIer (赞：0)

最板子的一集。  
题目中每个数需要转移到自己的一个正因子，那么考虑将一个数进行质因数分数分解。  
注意到我们所关心的只是下面能转移到的因子的个数，所以我们不需要考虑下面一个状态的大小，而只需要考虑下一个状态的质因子个数。  
因此，这个问题就能抽象为从质因子堆中取出任意个质因子，从而变成了一个取石子问题。  
## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=100000+5;
int n,a[maxn];
int h[maxn];

bool isprime[maxn];
vector<int> prime;
inline void pre(){
    for(int i=2;i<=1e5;i++){
        if(!isprime[i]) prime.push_back(i);
        for(auto j:prime){
            if(i*j>1e5) break;
            isprime[i*j]=1;
            if(i%j==0) break;
        }
    }
}
int main(){
    cin>>n;
    pre();
    for(int i=1;i<=n;i++){
        cin>>a[i];
        for(int j=2;j*j<=a[i];j++)
        if(a[i]%j==0&&isprime[j]==0) while(a[i]%j==0) a[i]/=j,h[i]++;
        if(a[i]>1) h[i]++;
    }
    int ans=h[1];
    for(int i=2;i<=n;i++) ans^=h[i];
    if(ans!=0) puts("Anna");
    else puts("Bruno");
    return 0;
}
```

---

