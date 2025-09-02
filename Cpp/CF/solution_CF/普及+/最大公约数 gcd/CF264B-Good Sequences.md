# Good Sequences

## 题目描述

Squirrel Liss is interested in sequences. She also has preferences of integers. She thinks $ n $ integers $ a_{1},a_{2},...,a_{n} $ are good.

Now she is interested in good sequences. A sequence $ x_{1},x_{2},...,x_{k} $ is called good if it satisfies the following three conditions:

- The sequence is strictly increasing, i.e. $ x_{i}&lt;x_{i+1} $ for each $ i $ $ (1<=i<=k-1) $ .
- No two adjacent elements are coprime, i.e. $ gcd(x_{i},x_{i+1})&gt;1 $ for each $ i $ $ (1<=i<=k-1) $ (where $ gcd(p,q) $ denotes the greatest common divisor of the integers $ p $ and $ q $ ).
- All elements of the sequence are good integers.

Find the length of the longest good sequence.

## 说明/提示

In the first example, the following sequences are examples of good sequences: \[2; 4; 6; 9\], \[2; 4; 6\], \[3; 9\], \[6\]. The length of the longest good sequence is 4.

## 样例 #1

### 输入

```
5
2 3 4 6 9
```

### 输出

```
4
```

## 样例 #2

### 输入

```
9
1 2 3 5 6 7 8 9 10
```

### 输出

```
4
```

# 题解

## 作者：傅思维666 (赞：9)

## 题解：

一开始想了一个裸的DP：设$dp[i]$表示结尾位置为$i$的最长好序列。那么转移就是
$$
dp[i]=\max(dp[j])+1\quad(j\in(1,i-1),\gcd(a[i],a[j]>1))
$$
复杂度是$O(n^2\log n)$。

在21号点折戟。

代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=1e5+5;
int n,ans;
int a[maxn];
int dp[maxn];
//dp[i]表示以i结尾的最长好序列长度。
int gcd(int a,int b)
{
    return !b?a:gcd(b,a%b);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        dp[i]=1;
    }
    for(int i=2;i<=n;i++)
        for(int j=1;j<i;j++)
            if(gcd(a[i],a[j])>1)
                dp[i]=max(dp[i],dp[j]+1);
    for(int i=1;i<=n;i++)
        ans=max(ans,dp[i]);
    printf("%d\n",ans);
    return 0;
}
```

考虑如何优化转移：这个log大概率是省不掉的，只能优化两重枚举，我们可不可以找到一个唯一的转移过去的方式或者使转移时枚举数尽量少。我们考虑从GCD入手。

我们发现，我们只需要找到当前枚举到的状态前的最大合法dp值即可。而这个合法DP还应该和GCD有关（因为数列保证有序）。而GCD的一般处理方式是拆成因子——那就再设一个状态：$f[i]$表示含有因子$i$的$a[x]$中的最大$dp[x]$。这个转移也是无后效性的，所以可以在DP过程中同步更新。这样，每次转移就只需要枚举这个数的所有质因子。大大优化了枚举效率。

代码：

```cpp
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cmath>
using namespace std;
const int maxn=1e5+5;
int n,ans,maxx;
int a[maxn];
int dp[maxn];
//dp[i]表示以i结尾的最长好序列长度。
int f[maxn];
//f[i]表示所有含有因子i的a[x]的最大dp[x]
int prime[maxn],tot;
bool v[maxn];
vector<int> fac[maxn];
void init()
{
    for(int i=2;i<=maxx;i++)
	{
		if(!v[i])
			prime[++tot]=i;
		for(int j=1;j<=tot&&i*prime[j]<=maxx;j++)
		{
			v[i*prime[j]]=1;
			if(i%prime[j]==0)
				break;
		}
	}
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        dp[i]=1;
        maxx=max(maxx,a[i]);
    }
    init();
    for(int i=1;i<=tot;i++)
		for(int j=prime[i];j<=maxx;j+=prime[i])
			 fac[j].push_back(prime[i]);
    for(int i=1;i<=n;i++)
    {
        int tmp=0;
        for(int j=0;j<fac[a[i]].size();j++)
            tmp=max(tmp,f[fac[a[i]][j]]);
        dp[i]=max(dp[i],tmp+1);
        for(int j=0;j<fac[a[i]].size();j++)
            f[fac[a[i]][j]]=max(f[fac[a[i]][j]],dp[i]);
    }
    for(int i=1;i<=n;i++)
        ans=max(ans,dp[i]);
    printf("%d\n",ans);
    return 0;
}
```



---

## 作者：是个汉子 (赞：6)

### Solution

虽然每个题要求的最长序列的满足条件不一样，但是方法总是那一个——DP。

因为前后转移和 $\gcd$ 有关系，我们可以将 $\gcd$ 用因子的方式表示。

我们设 $dp_i$ 表示以 $a_i$ 结尾的最长序列， $f_i$ 为所有含有 $i$ 这个因子的 $a_x$ 中的 $\max\{dp_x\}$ 。当方程转移到 $x$ 位时，枚举 $a_x$ 的因子，更新 $dp_x=\max\limits_{d|a_x,d\not=1}\{f_d\}+1$ ，然后再将 $f_d$ 更新，最后搞一个 $ans$ 记录最大值就行了。

小细节：在更新 $f_d$ 的时候，可以只更新质因子的 $f$ ，因为在转移的时候，用非质因子更新答案，其实在枚举质因子的时候就已经更新过了，并且质因子的答案不会比非质因子差。而且 $dp$ 数组也不需要，当枚举到某一位时，这一位以前的最大值已经求出，所以可以直接和 $ans$ 更新。

### 代码

```c++
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
const int N=100010;
int ans,n,a[N],f[N];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
    while(isdigit(ch)){x=x*10+(ch^48);ch=getchar();}
    return x*f;
}

inline void solve(int x){
    int m=sqrt(x),sum=0;
    for(int i=2;i<=m;i++)
        if(x%i==0) sum=max(max(sum,f[i]),f[x/i]);
    sum=max(sum,f[x]);//记得x也算x的因数
    for(int i=2;i<=m;i++)
        if(x%i==0){
            f[i]=sum+1;
            while(x%i==0) x/=i;
        }
    f[x]=sum+1;
    ans=max(ans,sum+1);//不记录dp[] 直接更新
}

int main(){
    n=read();
    for(int i=1;i<=n;i++) a[i]=read();
    for(int i=1;i<=n;i++) solve(a[i]);
    printf("%d\n",ans);
    return 0;
}
```



---

## 作者：DYT_ (赞：4)

这题是一道DP好题。
如果数据量小的话，我们可以直接gcd+二维DP，复杂度是O(n^2*log(n))的。但是这题n达到了1e5的数据量，这样做肯定会Tle。
那么我们就要思考更好的方法了。
考虑gcd可以用因子来表示，即x和y有公共因子A。
我们定义f[i]表示以有i这个因子的数结尾的最长序列长度。
这样就可以DP了。
假设我们做到了a[i]这个数，我们枚举它的每一个因子k，此时f[k]表示有k这个因子的数结尾的最长序列长度，也就是前一个数的最长序列长度。那么我们可以对所有的f[k]取一个max，来修正f[a[i]]，并且因为这两个数有公共因子，所以可以用这个max来修正所有的f[k]。
代码比较简单:-）
代码如下：

```
#include<cstdio>
#include<string>
#include<cmath>
using namespace std;
const int maxn=100005;
int n,ans,a[maxn],f[maxn];
void doit(int x){
	int sq=sqrt(x),sum=0,y=x;
	for (int i=2;i<=sq;i++)
	if (x%i==0){
		sum=max(max(sum,f[i]),f[x/i]);
	}
	sum=max(sum,f[x]);
	x=y;
	for (int i=2;i<=sq;i++)
	if (x%i==0){
		f[i]=sum+1,f[x/i]=sum+1;
		while (x%i==0) x/=i;
	}
	f[x]=sum+1;
	ans=max(ans,sum+1);
}
int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&a[i]);
	for (int i=1;i<=n;i++) doit(a[i]);
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：2huk (赞：3)

## 题面描述

输入 $n$ 个数 $a_1, a_2, \dots, a_n$，保证严格递增。

如果一个序列 $x_1, x_2, \dots, x_k$ 能够满足条件，那就是一个好序列：

- $\forall i \in [1, k)$，有 $x_i < x_{i+1}$；
- $\forall i \in [1, k)$，有 $\gcd(x_i, x_{i+1}) > 1$；
- $\forall i \in [1, k]$，有 $x_i \in a$。

问序列最长是多少。

$1 \le n, a_i \le 10^5$

## 分析

考虑 `DP`。

一共有 $3$ 个条件，其中条件 $1, 3$ 提示了我们需要找一个 $a$ 中的上升子序列。由于 $a$ 本身就是严格递增的，所以题目可以简化成从 $a$ 中找出一个子序列，满足相邻两项不互质。

我们可以通过类似找最长上升子序列的方法，定义状态 $f_i$ 表示以 $i$ 结尾的满足条件的最长子序列，那么转移即：
$$
f_i = \max_{\gcd(a_i, a_j) > 1} (f_j + 1)
$$
总时间复杂度为 $\Theta(n^2\log n)$。

这样是不可行的。接下来考虑优化。

如果两个数不互质，那么它们必定有一个相同的**质因子**。在上面的转移中实际上就是在找与 $a_i$ 有相同质因子的 $a_j$ 的 $f_j + 1$，而这个值可以直接统计出来。

具体地，定义 $g_i$ 表示表示含有质因子 $i$ 的 $a_j$ 的 $f_j$ 的最大值，那么转移时只需要枚举 $a_i$ 的所有质因子 $j$，并找到最大的 $g_j + 1$ 即可。转移为：
$$
f_i = \max_{j \mid i, j\text{ is a prime}} (g_j + 1)
$$
同时，在更新完 $f_i$ 的答案后，还需要尝试更新 $i$ 的质因子 $j$ 的 $g_j$ 的值。然后统计最大的 $f_i$ 即可。

上述转移中寻找 $i$ 的质因子可以 $\Theta(\sqrt n)$ 的复杂度求解，因此整个算法的时间复杂度为 $\Theta(n\sqrt n)$。

[$\text{Code}$](https://www.luogu.com.cn/paste/yf4eflt8)

---

## 作者：Rayment (赞：3)

# Solution
发一篇另类题解。。

由于$a_i$是按大小给出的，所以直接设$f[i]$表示以$a_i$结尾的最长好序列，不难得出

$$f[i]=\max_{\gcd(a_i,a_j)\not=1}(f[j])+1$$

考虑枚举因数，然后就可以建图了，最后答案就是最长路。

但是我们会注意到如果把所有gcd不为1的都建边，空间复杂度很大，注意到是最长路，所以只需要相邻的建边即可，其他跳跃的肯定不会做为最长路。

时间复杂度$O(n\ln n)$。

# Code
```cpp
#include <algorithm>
#include <cstring>
#include <cstdio>
#define rg register
using namespace std;
typedef long long ll;
const int maxn=100010,maxm=2000010;
template <typename Tp> inline int getmin(Tp &x,Tp y){return y<x?x=y,1:0;}
template <typename Tp> inline int getmax(Tp &x,Tp y){return y>x?x=y,1:0;}
template <typename Tp> inline void read(Tp &x)
{
    x=0;int f=0;char ch=getchar();
    while(ch!='-'&&(ch<'0'||ch>'9')) ch=getchar();
    if(ch=='-') f=1,ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    if(f) x=-x;
}
struct data{int v,nxt;}edge[maxm];
int n,p,lst,ans,a[maxn],t[maxn],head[maxn],dis[maxn];
inline void insert(int u,int v){edge[++p]=(data){v,head[u]};head[u]=p;}
int dfs(int x)
{
	if(~dis[x]) return dis[x];
	dis[x]=1;
	for(int i=head[x];i;i=edge[i].nxt)
	  getmax(dis[x],dfs(edge[i].v)+1);
	return dis[x];
}
int main()
{
	read(n);
	for(rg int i=1;i<=n;i++)
	{
		read(a[i]);
		t[a[i]]=i;
	}
	for(rg int i=2;i<=100000;i++)
	{
		lst=0;
		for(rg int j=i;j<=100000;j+=i)
		  if(t[j])
		  {
		  	if(lst) insert(t[j],lst);
		  	lst=t[j];
		  }
	}
	memset(dis,0xff,sizeof(dis));
	for(rg int i=1;i<=n;i++) getmax(ans,dfs(i));
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：happybob (赞：2)

## 题意

给定一个单调上升序列 $a$，求最多在这个序列中选多个数（不要求相邻），满足相邻两个数不互质。

## 解法

显然有一个 $O(n^2 \log n)$ 的 DP，会超时。

考虑 $\gcd(x,y) > 1$ 这个式子，事实上就是 $x, y$ 有共同公因数，那么对于每一个 $i$，只需要把 $a_i$ 分解质因数，在所有质因数里找一个相对应 $dp$ 中最大的，$+1$ 即可。

代码：

```cpp
#pragma GCC optimize("-Ofast,inline")
#include <iostream>
#include <cmath>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

const int N = 1e5 + 5;

int a[N], n, dp[N], ans = 0;


inline vector<int> calc(register int x)
{
	vector<int> res;
    int rem = x;
	for (register int i = 2; i * i <= rem; ++i)
	{
		bool f = false;
		while (x % i == 0)
		{
			x /= i;
			f = true;
		}
		if (f) res.push_back(i);
	}
	if (x != 1)
	{
		res.push_back(x);
	}
	return res;
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= n; i++)
	{
		vector<int> x = calc(a[i]);
		int s = x.size() - 1, maxn = 0;
		for (int i = 0; i <= s; i++)
		{
			maxn = max(maxn, dp[x[i]]);
		}
		for (int i = 0; i <= s; i++)
		{
			dp[x[i]] = max(dp[x[i]], maxn + 1);
		}
		ans = max(ans, maxn + 1);
	}
	printf("%d\n", ans);
	return 0;
}
```


---

## 作者：叶枫 (赞：2)

### 题意
- 求出最长的相邻两数**不互质**的最长的严格上升数列的长度~~应该吧~~（wo 菜死了

这道题让我$get$到对于素数处理的几个新方法

具体看代码吧
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<string>
#include<queue>
#define re register
#define ll long long
#define maxn 100001
#define inf 2147483647
#define mod 998244353
using namespace std; //请忽略
inline int read(){
    int x=0,f=1; char ch=getchar();
    while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch)) {x=x*10+ch-48;ch=getchar();}
    return x*f;
}
int QAQ[maxn],dp[maxn];
int qwq;/也请忽略
int main()
{
    for(int i=2;i<maxn;i++)
    if(!QAQ[i])
    for(int j=i;j<maxn;j+=i) QAQ[j]=i; //可以用来储存每个因子(涨姿势了
	/*
	for(int i=2;i<=maxn;i++)
	if(!a[i]) 
	for(int j=i;j<=maxn;j+=i) a[j]=a[j/i]+1;//可以求每个数的所有因子个数(又涨姿势了 
	*/ 
    int n=read();
    for(int i=1;i<=n;i++)
    {
        int t=read();
        int x=0;
        for(int i=t;i>1;i/=QAQ[i]) x=max(x,dp[QAQ[i]]); // 求得当前以x为最后一位数的最长序列长度
        for(int i=t;i>1;i/=QAQ[i]) dp[QAQ[i]]=max(dp[QAQ[i]],x+1);//更新每一个因子i(dp[i]);
        qwq=max(x+1,qwq);
    }
    printf("%d",qwq);
    return 0;
}
```

```cpp
用vector 的，原理同上
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<string>
#include<vector>
#define re register
#define ll long long
#define maxn 200010
#define inf 2147483647
#define mod 998244353
using namespace std; 
inline int read(){
    int x=0,f=1; char ch=getchar();
    while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch)) {x=x*10+ch-48;ch=getchar();}
    return x*f;
}
vector<int>vc[maxn];
inline void init(){
	for(int i=2;i<=maxn;i++)
	for(int j=i;j<maxn;j+=i)
	   vc[j].push_back(i);
}
int a[maxn],dp[maxn],ans=1;
signed main(){
   init();
	int n=read();
	vector<int>::iterator it;
	for(int i=1;i<=n;i++) a[i]=read();
	sort(a+1,a+n+1); //为什么要排序？自己想。。。
	for(int i=1;i<=n;i++){
		int maxm=0;
		for(it=vc[a[i]].begin();it!=vc[a[i]].end();it++) maxm=max(maxm,dp[*it]);
		for(it=vc[a[i]].begin();it!=vc[a[i]].end();it++) dp[*it]=maxm+1;
	} 
	for(int i=0;i<maxn;i++) ans=max(ans,dp[i]);//一定要从0开始，我@@&…##
	printf("%d",ans);
	return 0;
}
 
```
[$\sout\text{无耻的求赞}$](https://yycdeboke.blog.luogu.org/solution-cf264b)

---

## 作者：decoqwq (赞：2)

水一道简单dp的题解(

考虑到转移中两个相邻的数不互质比较麻烦，我们将每个数字的所有质因子存起来，转移的时候，它可以从前面所有有公共质因子的数中答案最大值转移过来，所有每次转移只需遍历一遍每个质因子位上最大的答案，然后再将自己的答案更新这些质因子上的答案即可

因为$2*3*5*7*11*13*17 > 100000$ ，所以最多 $6$ 个质因子，考虑到枚举约数是 $O(\max\{a_i\}\mathbb{log} \max\{a_i\})$的，所以总时间复杂度 $(\max\{a_i\}\mathbb{log} \max\{a_i\}+n)$

```cpp
#include <bits/stdc++.h>
using namespace std;
int ans[100010],prime[100010],vis[100010],tot;
vector<int> vc[100010];
int n,a[100010],maxn,dp[100010];
void shai()
{
	for(int i=2;i<=maxn;i++)
	{
		if(!vis[i])
		{
			prime[++tot]=i;
		}
		for(int j=1;j<=tot&&i*prime[j]<=maxn;j++)
		{
			vis[i*prime[j]]=1;
			if(i%prime[j]==0)
			{
				break;
			}
		}
	}
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		maxn=max(maxn,a[i]);
		dp[i]=1;
	}
	shai(); 
	for(int i=1;i<=tot;i++)
	{
		for(int j=prime[i];j<=maxn;j+=prime[i])
		{
			 vc[j].push_back(prime[i]);//每个数的质因子
		}
	}
	int mxans=0;
	for(int i=1;i<=n;i++)
	{
		int rans=0;
		for(int j=0;j<vc[a[i]].size();j++)
		{
			rans=max(rans,ans[vc[a[i]][j]]);//有共同质因子的部分找最大的答案
		}
		dp[i]=max(dp[i],rans+1);
		for(int j=0;j<vc[a[i]].size();j++)
		{
			ans[vc[a[i]][j]]=max(ans[vc[a[i]][j]],dp[i]);
		}
		mxans=max(mxans,dp[i]);
	}
	cout<<mxans;
}		
```

---

## 作者：inexistent (赞：1)

**详见我的[博客](https://www.cnblogs.com/qixingzhi/p/9310133.html)**

思路分析：

　　这题DP太难了……

　　最终的解法是，令f[i]表示存在因子i的一个数作为子序列结尾的子序列的最大长度。（定义都好难懂啊……）

　　现在想一想怎么转移……首先先预处理出对于每一个数a[i]的所有因数（不含1）。既然相邻的两个数不能是互质的，我们只需要判断相邻两个数的最大公约数是否大于1就好了。

　　依次枚举a[i]，在这过程中枚举刚才处理好的a[i]的因数。为什么要枚举因数？ 为了看看我能够接到哪些数后面。因为所有因数如果在之前的数里出现过，那么当前的a[i]就可以接上去，因为因数大于1，所以肯定不会有互质的这种情况。由于我之前已经记录了这些因数所能够达到的最大长度，那么再加上我自己，长度就又可以+1了——这一点有点像LIS，但又有点不同：选择所有因数中f值最大的去接上去以后，所有因数的f值都可以更新成与其中最大值相同的。因为最后一个数本身就含有这些因数。

　　所以最后的答案究竟是什么？我认为是f[2]~f[a[n]中的最大值。然而这样会WA，改成f[1]~f[a[n]]就AC了。这一点一直想不通，是因为本身就会输入1吗？为什么输入1就会影响答案呢？而且我的AC代码对于数据1 1 1 1 1竟然输出了5，不应该是1吗？1和1是互质的！还请大神帮忙解答一下……

---

## 作者：谁是鸽王 (赞：1)

## 【题解】good序列

具有很明显的无后效性。

考虑$dp$。设$dp(i)$表示以第$i$号结尾，最长的序列长度。

考虑初始条件，显然是$dp(0)=0$

考虑转移，显然是$dp(t)=max(dp[k])+1$其中$gcd(data[t],data[k])>1$

这样的转移是$O(n^2)$的！显然超时。

发现值域$\le 100000$那么我们将数拆成它的质因数。

线性筛素数预处理$[1,100000]$的质数$O(n)$的代价。存下来。

然后转移的时候，先直接$O(\sqrt{n})$枚举质因数，直接从$vector$表里查询能够从谁那里转移。

根据$dp$的最优性质，可以知道只需要从$vector$的最后一个 $dp$值转移过来就好了，一定是最大的。

这样复杂度就是$O(n\sqrt{n})$了

```cpp
#include<bits/stdc++.h>

#define RP(t,a,b) for(register int (t)=(a),edd_=(b);t<=edd_;++t)
#define DRP(t,a,b) for(register int (t)=(a),edd_=(b);t>=edd_;--t)
#define ERP(t,a) for(int t=head[a];t;t=e[t].nx)
#define Min(a,b) ((a)<(b)?(a):(b))
#define pushup(x) seg[(x)]=seg[(x)<<1]+seg[(x)<<1|1]
#define midd register int mid=(l+r)>>1
#define chek if(R<l||r<L)return
#define TMP template<class ccf>
#define rgt L,R,mid,r,pos<<1|1
#define lef L,R,l,mid,pos<<1
#define all 1,n,1

using namespace std;typedef long long ll;
TMP inline ccf qr(ccf k){
    char c=getchar();
    ccf x=0;
    int q=1;
    while(c<48||c>57)q=c==45?-1:q,c=getchar();
    while(c>=48&&c<=57)x=x*10+c-48,c=getchar();
    return q==-1?-x:x;
}
const int maxn=100005;
const int maxl=maxn-5;
bool usd[maxn];
int data[maxn];
#define isp(x) (!usd[x])
vector < int > pr;
#define pb push_back
vector < int > p[100001];
int n;
int ans;
int dp[maxn];

inline void gen_pr(){
    usd[1]=1;
    usd[0]=1;
    RP(t,2,maxl){
	if(!usd[t])
	    pr.pb(t);
	RP(i,0,pr.size()-1){
	    if(t*pr[i]>maxn)
		break;
	    usd[t*pr[i]]=1;
	    if(!(t%pr[i]))
		break;
	}
    }
}

inline int Max(int x,int y){
    if(x>y)
	return x;
    return y;
}
int main(){
#ifndef ONLINE_JUDGE
    freopen("good.in","r",stdin);
    freopen("good.out","w",stdout);
#endif
    gen_pr();
    n=qr(1);
    RP(t,1,n)
	data[t]=qr(1);
    int siz=pr.size()-1;

    RP(t,1,n){register int sav=data[t];
	RP(i,0,siz){
	    register int now=pr[i];
	    register int nowcnt=p[now].size();
	    if(!(sav%now)){
		while(!(sav%now))
		    sav/=now;
		if(nowcnt)
		    dp[t]=Max(dp[t],dp[p[now][nowcnt-1]]+1);
		else
		    dp[t]=Max(dp[t],1);
		p[now].pb(t);
	    }
	    if(sav<now)
		break;
	}
    }
    
    ans=1;
    RP(t,1,n)
	ans=Max(ans,dp[t]);
    cout<<ans<<endl;
    return 0;
}
```



---

## 作者：xuantianhao (赞：0)

# [Good Sequences](https://www.luogu.com.cn/problem/CF264B)

状态很显然，设 $f[i]$ 表示位置 $i$ 的最长长度。

关键是转移，暴力转移是 $O(n^2)$ 的，我们必须找到一个更优秀的转移。

因为一个数的质因子数量是 $O(\log n)$ 的，而只有和这个数具有相同质因子的数是可以转移的；

因此我们可以对于每个质数 $p$，设一个 $mx_p$ 表示所有有 $p$ 作为质因子的 $x$ 的 $f_i$ 的最大值。

关于质因子应该怎么得出嘛，线性筛一下即可。

复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+100;
int n,res,t,x;
int p[N],pre[N],mx[N],f[N];
void prime(){
    for(int i=2;i<=N;i++){
        if(!p[i]){p[++p[0]]=i;pre[i]=p[0];}
        for(int j=1;j<=p[0]&&i*p[j]<=N;j++){
            p[i*p[j]]=true;
			pre[i*p[j]]=j;
            if(!(i%p[j])) break;
        }
    }
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
    cin>>n;
	prime();
    for(int i=1;i<=n;i++){
        cin>>x;
		f[i]=1;
        t=x;
        while(t!=1){
			f[i]=max(f[i],mx[pre[t]]+1);
			t/=p[pre[t]];
		}
        t=x;
        while(t!=1){
			mx[pre[t]]=f[i];
			t/=p[pre[t]];
		}
        res=max(res,f[i]);
    }
    printf("%d\n",res);
    return 0;
}
```


---

## 作者：Night_Bringer (赞：0)

# 前言
[博客园食用更佳](https://www.cnblogs.com/C202202chenkelin/p/14670868.html)
# 题意
给定一个数集 $A$ ，求一个严格上升的序列使得序列每个数都属于 $A$ ，且任意相邻的两个数不互质。求构造出的数列的最大长度。
# 思路
考虑 DP， 设 $dp[i]$ 以 $i$ 为质因数之一的数结尾的最大长度。

首先预处理分解质因数，对于 $A$ 中的数字从小到大排序并去重。

一次遍历 $A$ 中的数字，设当前遍历到的数为 $a$ 。

则再对于 $a$ 分解质因数，并使用 $set$ 进行维护。

将这些质因数的 $dp$ 值取 $max$ ，易得 $dp[i]=max+1$ （ $i$ 为 $a$ 的质因数）。

最后对 $dp[i](i\in[1,100000])$ 取 $max$ 即可。

总体时间复杂度为 $O(n\log n)$ ，因为一个数的能都分解成的质因数不可能超过 $\log n$ 个，当且仅当 $n$ 为 $2$ 的幂时取得到等号。还带上一个较小的常数，为 $n$ 对数的对数，因为使用了 set 进行维护，因为太小，此题中必不会超过 $5$ ，可看为常数。
# Code
```cpp
#include <set>
#include <cstdio>
#include <algorithm>
using namespace std;
namespace Quick_Function {
	template <typename Temp> void Read(Temp &x) {
		x = 0; char ch = getchar(); bool op = 0;
		while(ch < '0' || ch > '9') { if(ch == '-') op = 1; ch = getchar(); }
		while(ch >= '0' && ch <= '9') { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
		if(op) x = -x;
	}
	template <typename T, typename... Args> void Read(T &t, Args &... args) { Read(t); Read(args...); }
	template <typename Temp> Temp Max(Temp x, Temp y) { return x > y ? x : y; }
	template <typename Temp> Temp Min(Temp x, Temp y) { return x < y ? x : y; }
	template <typename Temp> Temp Abs(Temp x) { return x < 0 ? (-x) : x; }
	template <typename Temp> void Swap(Temp &x, Temp &y) { x ^= y ^= x ^= y; }
}
using namespace Quick_Function;
const int MAXN = 1e5 + 5;
int a[MAXN], n;
int pre[MAXN], p[MAXN];
bool vis[MAXN];
int cnt, ans = 1;
int dp[MAXN];
set<int> prime;
void Primes() {
	vis[1] = 1;
	for(int i = 2; i <= 100000; i++) {
		if(!vis[i]) { p[++cnt] = i, pre[i] = i; }
		for(int j = 1; j <= cnt && i * p[j] <= 100000; j++) {
			vis[i * p[j]] = 1; pre[i * p[j]] = p[j];
			if(i % p[j] == 0) break;
		}
	}
}
void Break_Down(int x) {
	if(x == 1) return;
	prime.insert(pre[x]);
	Break_Down(x / pre[x]);
}
int main() {
	Primes();
	Read(n);
	for(int i = 1; i <= n; i++) Read(a[i]);
	sort(a + 1, a + 1 + n);
	int m = unique(a + 1, a + 1 + n) - a - 1;
	for(int i = 1; i <= m; i++) {
		int maxn = 0;
		Break_Down(a[i]);
		for(set<int>::iterator it = prime.begin(); it != prime.end(); it++) maxn = Max(maxn, dp[*it] + 1);
		for(set<int>::iterator it = prime.begin(); it != prime.end(); it++) dp[*it] = maxn;
		prime.clear();
	}
	for(int i = 1; i <= 100000; i++) ans = Max(ans, dp[i]);
	printf("%d", ans);
	return 0;
}
```

---

## 作者：fangxk2003 (赞：0)

## Solution
DP

$dp[i]$表示以$i$结尾的Good Sequence

$d[i]$表示所有含有$i$这个质因子的$x$中$max(dp[x])$

每次转移完$dp[x]$之后，再更新一下所有的$d[i]$即可

## Code
```cpp
#include <cstdio>
#include <algorithm>
#define N 100010

using namespace std;

int a[N], dp[N], d[N];
int gcd(int x, int y) {
	if (y == 0) return x;
	else return(y, x % y);
}

int main() {
	int n;
	scanf("%d", &n);
	if (n == 1) {
		printf("%d\n", 1);
		return 0;
	}
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
	}
	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		int e = a[i];
		for (int j = 2; j * j <= a[i]; ++j) {
			if (e % j == 0) {
				dp[a[i]] = max(dp[a[i]], d[j]);
				while (e % j == 0) e /= j;
			}
		}
		if (e > 1) dp[a[i]] = max(dp[a[i]], d[e]);
		dp[a[i]]++;
		ans = max(ans, dp[a[i]]);
		e = a[i];
		for (int j = 2; j * j <= a[i]; ++j) {
			if (e % j == 0) {
				d[j] = dp[a[i]];
				while (e % j == 0) e /= j;
			}
		}
		if (e > 1) d[e] = dp[a[i]];
	}
	printf("%d\n", ans);
	return 0;
}
```

---

