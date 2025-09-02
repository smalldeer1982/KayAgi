# 『STA - R3』Aulvwc

## 题目背景

统计学是一门古老而迷人的学科。

传说早在若干年前，一位名为惠普的神灵来到地球，发现了人类——另一种有智慧的物种……

**已加入 Hack 数据，位于 Subtask 5，不计分。**

## 题目描述

定义一个序列 $\{a_n\}$ 是分部平均的，当且仅当存在一个 $\{1,2,\cdots,n\}$ 的划分 $S_1,S_2,\cdots,S_k$（其中 $k>1$），满足对于每个整数 $1\le i\le k$，序列 $\{a\}$ 中以 $S_i$ 为下标的元素之平均数都是相等的**整数**。

现在，给定序列 $\{a_n\}$，问它是否是分部平均的。

如果你对于一些定义不很清楚，可以查阅最后的「提示」部分。



## 说明/提示

### 提示
一个集合 $S$ 的划分定义为一组集合 $U_1,U_2,\cdots,U_k$，满足：
- 对于所有 $i\neq j$，有 $U_i\cap U_j=\varnothing$。
- $U_1\cup U_2\cup\cdots\cup U_k=S$。

一个序列 $\{x_n\}$ 的平均数定义为：
$$\bar x=\dfrac{x_1+x_2+\cdots+x_n}{n}=\dfrac 1n\sum_{i=1}^nx_i$$
### 样例解释
第一组数据的一种划分方案：$\{1\},\{2\},\{3\},\{4\},\{5\}$。

第二组数据的一种划分方案：$\{1,5\},\{2,4\},\{3\}$。

注意：划分方案所提供的集合是下标集合。

### 数据范围

**本题采用捆绑测试及子任务依赖。**
$$
\newcommand{\arraystretch}{1.5}
\begin{array}{c|c|c|c|c}\hline\hline
\textbf{Subtask} & \bm{n}\le & \textbf{分值} & \textbf{特殊性质}&\textbf{依赖子任务}\\\hline
\textsf{1} & 10 & 5 & \\\hline
\textsf{2} & 10^3 & 20 & \sum a_i=0 \\\hline
\textsf{3} & 100 & 25 & & \sf1\\\hline
\textsf{4} & 10^3 & 50 & & \sf1\texttt{,}\ 3\\\hline
\end{array}
$$

对于全部数据，$1\le q\le 10$，$2\le n\le 10^3$，$|a_i|\le 5\times10^3$。

## 样例 #1

### 输入

```
4
5
1 1 1 1 1
5
1 2 3 4 5
5
1 1 1 1 6
5
-1 0 1 0 1```

### 输出

```
Yes
Yes
No
No```

# 题解

## 作者：ty_mxzhn (赞：21)

对于每两个平均数相同的划分方案里的子集 $S,T$，可以合并成一个子集。

那我们只需要把数分成两个子集即可。根据此，可知题目所知的相等的平均数即为整个数列的平均数。

显然可以将每个数减去这个平均数。此时问题转化为，$\texttt{Yes}$ 即找到转化后的一个非全选，非全不选的和为 $0$ 的子序列。

这里显然列出 dp：$f_{i,j}$ 为前 $i$ 个数中和为 $j$ 的方案。$f_{i,j}=f_{i-1,j}+f_{i-1,j-a_i}$。答案即为 $[f_{n,0}\geq 3]$

发现肯定过不了，但我们有同余科技，如果把和为 $j$ 改为和 $\bmod p=j$，就很轻松了，于是多判几次即可。

```cpp
#include <cstdio>
#include <cstring>
using namespace std;

int t,n,a[1007];
short f1[7][1007][2007],g1[7][1007][2007];
int s,p[]={0,1799,1857,1927,1924,1981,1999};//判断的模数
signed main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);s=0;
		for(int i=1;i<=n;i++) scanf("%d",&a[i]),s=s+a[i];
		if(s%n!=0){
			printf("No\n");//没有平均数
			continue;
		}
		s=s/n;
		memset(f1,0,sizeof f1);
		memset(g1,0,sizeof g1);
		for(int i=1;i<=n;i++) a[i]=a[i]-s;//问题转化
		for(int k=1;k<=6;k++){
			g1[k][0][0]=f1[k][0][0]=1;
			for(int i=1;i<=n;i++){
				for(int j=0;j<p[k];j++){
					f1[k][i][j]=g1[k][i-1][(j-a[i]+p[k]+p[k]+p[k])%p[k]];
					g1[k][i][j]=g1[k][i-1][j]+f1[k][i][j];
					if(g1[k][i][j]>10000) g1[k][i][j]=10000;//这里显然可以剪去情况
				}
			}
		}
		int ans=1;
		for(int k=1;k<=6;k++){
			ans=ans&&(g1[k][n][0]>=3);//所有模数都要过
		}
		if(ans) printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}
```


---

## 作者：Lyz09 (赞：19)

这题就是让我们求出一个子集使得这个子集的平均数为 $w$。（$w$ 是整个序列的平均数）

但是直接这样做特别麻烦，要求出是否存在固定大小子集的中的元素和为某个数。具体的，是否有集合 $U\in a_n$ 满足 $\frac{1}{|U|}\sum\limits_{x\in U}=w$。~~我在赛时想了半小时也没有想出来。~~

如果你注意到了 $\sum {a_i}=0$ 的部分分，就可以注意到这一档的部分分十分好写。因为 $w=0$，所以符合条件的子集的和只能是 $0$，与集合的大小无关，这样就变成了一个经典的动态规划的问题。发现其他的数据也可以转化成这样，因为这个序列的平均数为 $w$，要想要 $w$ 变为 $0$，将序列中每个元素都减去 $w$ 即可。

但是我们发现朴素的动态规划的时间复杂度是 $O(n^2k)$。（其中 $k$ 是值域，本题赛后中为 $10^4$）这无法通过此题。我们考虑使用科技优化，也就是 `bitset`。（如果你不会 `bitset`  请自行百度）众所周知 `bitset` 的常数为 $\frac {1}{\omega}$，一般 $\omega$ 取 $64$。所以这时时间复杂度变为了 $O(\frac {n^2k}{\omega})$，循环次数约为 $1.5\times 10^8$ 次，仍然超时。

发现数据的极限情况是类似于一个尖的形状，如果有解则最坏情况下也会在正负值域一半的地方往 $0$ 折返。也就是说，我们实际上用到的值域只有原值域的一半。现在循环次数只有约 $0.8\times 10^7$ 次，足以通过此题。

个人的实现是处理后的序列正负分开处理，如果两个 `bitset` 有 $m$ 个相同位置为 $1$，则表明有 $m$ 个子集的和为 $0$。因为 $f_0=0$（这里的 $f$ 指 `bitset`），所以 $a_i=0$ 要特判。当 $m>2$ 时则代表有解，因为要除去空集和整个集合。

还有些细节在代码中。

```cpp
#include<iostream>
#include<bitset>
using namespace std;
#define N 2500010
int t,n,a[N],f[2][N];
bitset<N> s,b,c;
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n;
		int sum=0;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			sum+=a[i];
		}
		a[n+1]=0;
		if(sum%n==0)//平均数必须为整数
		{
			int p=sum/n;
			s.reset();
			b.reset();
			b.set(0);
			s.set(0);
			for(int i=1;i<=n;i++)
			{
				a[i]-=p;
				if(a[i]==0)
				{
					puts("Yes");
					goto loop;//跳转到loop的位置，等价于写solve函数的return
				}
				if(a[i]>0)
				{
					b|=b<<a[i];//bitset的好用操作，等价于f[i][j]|=f[i-1][i-a[i]]
				}
				else
				{
					s|=s<<(-a[i]);
				}
			}
			c=s&b;
			if(c.count()>2)//判断
			 puts("Yes");
			else
			 puts("No");
		}
		else
		 puts("No");
		loop:
			;
	}
}
```



---

## 作者：jijidawang (赞：16)

后面 $v$ 是值域 .

首先注意到如果两个序列 $\{a_n\},\{b_m\}$ 的平均数都是 $e$，则它们两个拼起来的平均数也是 $e$ .

具体地，令 $\{a\},\{b\}$ 的和分别为 $s_{\sf a},s_{\sf b}$，则 $\dfrac{s_{\sf a}}n=\dfrac{s_{\sf b}}m=e$ .

从而 $\dfrac{s_{\sf a}+s_{\sf b}}{n+m}=\dfrac{en+em}{n+m}=e$，这也就证明了命题的正确性 .

从而不难发现划分的每个段的平均数必然都等于全局的平均数，因为要求每个段的平均数都是整数，所以只有全局平均数是整数才可能有解 . 特判这种情况之后则默认全局平均数为整数 $\bar x$ .

注意到，对于每个数全部减去 $\bar x$ 后，只需要找出一个集合的和为 $0$，则可以将整体划分为两个不交集合，由根据开头的性质，如果不能划分为两个，则必然多个也是不行的 .

于是问题变成了在给定序列中找出一个和为 $0$ 的子集，这是经典的 01 背包问题 . 这样时间复杂度是 $O(n|w|)$ 的，所以只需要考虑 $|w|$ 的上界是多少 .

如果直接处理，可以简单构造出使 $|w|=O(nv)$ 的数据，则时间复杂度为 $O(n^2v)$，无法通过所有数据 .

但是，因为整个序列的和为 $0$，所以考虑在处理之前随机打乱整个序列，根据经典结论，可以证明 $|w|=O(v\sqrt n)$，于是时间复杂度为 $O(n^{1.5}v)$，可以通过 .

不随机化动态调整上下界，用一些奇怪的做法比如随机打乱后绝对值大于 $2v_0$ 的状态直接丢掉也是可以过的 .

---

## 作者：Huangjy88 (赞：6)

# P9509题解

## Part 0 前言
赛时只想到了引理部分，写了个暴搜+剪枝，拿了 $5$ 分（~~想写动规但发现有负数~~）。
## Part 1 题意
给定序列 $\{a_n\}$，判断能否将其划分成 $k(k\ge2)$ 个子序列，使每个子序列的平均数都为**相等的整数**。
## Part 2 解析

### 2.1 转化

**引理**：若存在一种划分方法符合题意，则一定存在一种划分方法使原序列被化为两个子序列，且平均数都为原序列的平均数。

**证明**：

设划分的子序列的下标集合分别为 $S_{1},S_{2} \dots S_{k}$，元素之和分别为 $sum_{1},sum_{2} \dots sum_{k}$，则有 $\frac{sum_{1}}{\left| S_{1} \right|}=\frac{sum_{2}}{\left| S_{2} \right|}=\cdots=\frac{sum_{k}}{\left| S_{k} \right|}$。设 $S_{0}=S_{2}\cup S_{3}\cup \cdots \cup S_{k}$，则 $sum_{0}=\sum_{i=2}^{k} sum_{i}$。
由合比定理知 $\frac{sum_{2}}{\left| S_{2} \right|}=\cdots=\frac{sum_{k}}{\left| S_{k} \right|}=\frac{\sum_{i=2}^{k}sum_{i}}{\sum_{i=2}^{k}\left| S_{i} \right|}=\frac{sum_{0}}{\left| S_{0} \right|}$，故 $\frac{sum_{0}}{\left| S_{0} \right|}=\frac{sum_{k}}{\left| S_{k} \right|}=\frac{sum_{1}}{\left| S_{1} \right|}$，即下标集合 $S_{0},S_{1}$ 对应的子序列也是符合条件的一种划分，且由合比定理知 $\frac{sum_{0}}{\left| S_{0} \right|}=\frac{sum_{1}}{\left| S_{1} \right|}=\frac{sum_{0}+sum_{1}}{\left| S_{0} \right|+\left| S_{1} \right|}=\frac{sum}{n}$，即为原序列平均数，证毕。

根据引理，原题可转化为求原序列的一个子序列，使其平均数等于原序列的平均数。

### 2.2 实现
先判断原序列的平均数是否为整数，因为要求子序列的平均数为**整数**。

接下来，先考虑用动规实现，但是要求平均数一定，即和与子序列长度相干，不好处理。可以让原序列每个数都减去原平均数，那么新序列的平均数为 $0$，只需找一个和为 $0$ 的子序列。动规？还是不好处理（~~因为我太蒟了~~），因为可能出现和为负数的情况，数组下标放不了 。

考虑其他实现方法。~~一点开标签“随机化”~~，我们可以将原序列随机打乱，然后判断是否有和为 $0$ 的区间，只要打乱足够多次，判断就是正确的。

具体的，打乱序列后，记录前缀和，发现为 $0$ 或有相等的说明有区间和为 $0$，但是得判断该区间是否为整个序列。我这里选择用 `stl::set` 记录和判重前缀和。更多细节在代码里，不在此赘述。

## Part 3 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e3+5;
int n;
int a[N];
int w;
set<int>s;//记录前缀和
bool check(){
    int k=1000;//自行调整
    while(k--){
	int res=0;//前缀和
	random_shuffle(a+1,a+n+1)；//随机排列
	s.clear();//清空
	for(int i=1;i<=n;i++){
	    res+=a[i];
	    if((res==0&&i!=n) || s.count(res)){//找到和为0的区间
		return 1;
	    }
	    s.insert(res);//记录
	}
    }	
    return 0;
}
int main(){
    srand(time(0));
    int t;cin>>t;
    while(t--){
	cin>>n;
	int sum=0;
	for(int i=1;i<=n;i++){
	    cin>>a[i];
	    sum+=a[i];
	}
	if(sum%n){//判断平均数为整
	    puts("No");
	    continue;
	}
	w=sum/n;
	for(int i=1;i<=n;i++) a[i]-=w;//减平均数
	check()?puts("Yes"):puts("No");
    } 
    return 0;
}
```
有疑惑或发现题解中存在问题的欢迎私信我！

---

## 作者：zqiaor (赞：6)

### [题目传送门](https://www.luogu.com.cn/problem/P9509)

# 题意
能否把一个集合分成数个子集合，使每个子集合的平均数均相等且为整数。

# 分析
首先可以发现平均数一定是全集的平均数 $\overline{x}$，因此当全集的平均数不为整数时必不满足条件，且将所有数减去 $\overline{x}$ **不改变答案**。~~（这样就成功通过了 subtask $3$ and $4$）~~

此时所有数的总和为 $0$，那么子集合内数的总和也为 $0$ 即可满足条件，于是只需要有一个子集合的总和为 $0$，于是该集合的补集的总和也为 $0$，从而满足条件。

考虑将数分为正数和负数，注意到 $|a_i|\le5\times10^{3}$，故所有正数的和小于 $2.5\times10^{6}$，所有负数的和大于 $-2.5\times10^{6}$，用 $2$ 个 bitset 储存所有正数的和与所有负数的和的可能值，判断是否交集即可，复杂度为 $O(\frac{{n}^{2}S}\omega)$。（S 为所有数减去 $\overline{x}$ 后所有正数的和）

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[1001],tot,dx;
bitset<2500001>b1,b2,d;//b1为正数,b2为负数，d为b1&b2
bool f;
void solve(){
	cin>>n,tot=0,f=0,b1=b2=0;//初始化
	for(int i=1;i<=n;i++)cin>>a[i],tot+=a[i];
	if(tot%n){puts("No");return;}//平均数不为整数
	dx=tot/n;
	for(int i=1;i<=n;i++)a[i]-=dx;
	b1[0]=b2[0]=1;
	for(int i=1;i<=n;i++){
		if(a[i]>0)b1|=(b1<<a[i]);
		else if(a[i]<0)b2|=(b2<<(-a[i]));
		else {puts("Yes"),f=1;break;}//当a[i]=0时以{a[i]}为一个集合即可
	}
	if(!f){
		d=b1&b2;
		if(d.count()<=2)puts("No");//0和最大最小值不能取
		else puts("Yes");
	}
}
int main(){
	int T;
	cin>>T;
	while(T--)solve();
}
```


---

## 作者：lizhous (赞：4)

首先有一个显然的结论：划分出来的子序列平均数必然是整个序列的平均数。每个划分平均数是相等的，所有划分的平均数的平均数就是全局平均数，所以结论得证。

为了去除数字数量的影响，进行一步转化：将所有数减去平均数 $avg$。这样平均数就为 $0$。整个序列和为 $0$，只要有非全集子区间和为 $0$，就可以把序列分成两个集合使其合法。

经典的，考虑 `bitset` 维护。

因为要求了不是全集，我们就钦定任意一个数不选，对剩下的数判断。这样是对的，因为至少有两个集合和为 $0$，而不选的那一个数最多破坏一个集合。

一个 `bitset` 记录当前可组合出的数，称其为 $b$；一个 `bitset` 记录加入一个数后新增可以被表示的数，称其为 $c$。强制钦定选新增的数 $a_i$，所以 $c$ 根据 $b$ 左右移 $a_i$ 位更新，当前可以表示的数为 $b$ 和 $c$ 的按位或，只需要判断 $c$ 是否包含 $0$ 即可。复杂度 $O(\frac{n^2\times|a|}{\omega})$。

本题的细节：会出现负数，所以维护 `bitset` 时把所有数加 $1.25\times 10^6$。为什么是 $1.25\times 10^6$，因为最多只能加到一半值域，不然减法就无法减回 $0$。所以 `bitset` 只需开到 $2.5\times 10^6$，数据加强后 $5\times 10^6$ 会超时。

关键代码：
```cpp
bool check()
{
	b.reset();
	b[1250000]=1;
	for(int i=1;i<n;i++)
	{
		if(a[i]<0) 
		{
			c=(b>>(-a[i]));
			b=b|c;
		}
		else
		{
			c=(b<<a[i]);
			b=b|c;
		}
		if(c[1250000]==true) return true; 
	}
	return false;
}
```
强烈谴责赛时假做法过的人，真的很不公平。

---

## 作者：Argon_Cube (赞：3)

首先注意到如果有解一定存在一种解将原数列分成两部分（即 $k=2$）。

考虑若两组数平均值相等，那么将两组数并为一组后，平均值不变。也就是说我们可以通过合并其它的集合，构造出只有两个集合的解。

同时这也说明了，最后构造出的集合的平均数就是所有数的平均数，因此，我们将所有数减去平均数，转化为找到和为 $0$ 的非空真子集。直接可行性背包就好了。

但是注意到，直接做背包会导致将不选数和全选认为是一种合法方案。我们在做背包时，事先不将 $f_0$ 设为可达，而是在转移后将 $f_{a_i}$ 设为可达，这样可以强制至少选一个；我们强制令 $a_1$ 不在我们选的集合，这样可以避免全选。

然后我们的复杂度是 $\mathrm O(tn^2v)$ 的，算一下是 $10^{10}$，直接 `bitset` 就过了。

---

## 作者：Cx114514 (赞：2)

不难发现，每一个划分内的平均数一定等于序列里的 $n$ 个平均数。

不难发现，在两个划分平均数相等时，我们把两个划分合并，得到的新划分内平均数依然相等。

所以问题等价于能否把整个序列拆成两个平均数相等的划分。

我们采取一个处理平均数的经典手段：把序列中每个数的权值减去整个序列的平均数。这样，若干个和为 $0$ 的数一定是一种合法的划分。此时我们可以判断序列中是否包含元素个数不为 $0$ 或 $n$ 的和为 $0$ 的若干个数。此时我们可以想到用背包做。

可这样就会遇到一个新问题：如果正常做背包的话，运算量最大能达到 $5\times 10^{9} $，我们显然要对其进行一些优化。

我们可以发现，在进行背包的过程中，如果前 $i$ 个数中没有和为 $x$ 的若干个数，在加上第 $i+1$ 个数后不可能出现和为 $x+a_{i+1}$ 的情况，这种情况下我们就不需要进行转移，运算量大幅度减小。

下面贴上代码：
```cpp
#include <bits/stdc++.h>
using namespace std;

int read()
{
	int f = 1;
	char c = getchar();
	while (!isdigit(c))
	{
	    if (c == '-') f = -1;
	    c = getchar();
    }
	int x = 0;
	while (isdigit(c))
	{
		x = x * 10 + c - '0';
		c = getchar();
	}
	return x * f;
}

int buf[15];

void write(int x)
{
	int p = 0;
	if (x < 0)
	{
	    putchar('-');
	    x = -x;
	}
	if (x == 0) putchar('0');
	else
	{
		while (x)
		{
			buf[++p] = x % 10;
			x /= 10;
		}
		for (int i = p; i >= 1; i--)
			putchar('0' + buf[i]);
	}
}

int q, a[1005];

int vis[200005];

struct node
{
	int num, val;
};

vector < node > v;

int main()
{
	q = read();
	while (q--)
	{
		int n, sum = 0;
		n = read();
		for (int i = 1; i <= n; i++)
			a[i] = read();
		for (int i = 1; i <= n; i++)
			sum += a[i];
		int aa = sum / n;
		if (aa * n != sum)
		{
			printf("No\n");
			continue;
		}
		for (int i = 1; i <= n; i++)
			a[i] -= aa;
		memset(vis, -1, sizeof(vis));
		vis[100000] = 0;
		v.clear();
		v.push_back({100000, 0});
		for (int i = 1; i <= n; i++)
		{
			int len = v.size();
			for (int j = 0; j < len; j++)
			{
				node t = v[j];
				if (t.num + a[i] >= 0 && t.num + a[i] <= 200000)
				{
					if (vis[t.num + a[i]] == -1 || vis[t.num + a[i]] == 0) 
					{
						vis[t.num + a[i]] = t.val + 1;
						v.push_back({t.num + a[i], vis[t.num + a[i]]});
					}
					else vis[t.num + a[i]] = min(vis[t.num + a[i]], t.val + 1);
				}
			}	
		}
		if (vis[100000] && vis[100000] != n) printf("Yes\n");
		else printf("No\n");
	}
    return 0;
}
```


---

## 作者：louisliang (赞：2)

[传送门](/problem/P9509)

## 题意
能否把一个集合 $S$ 的划分成一组集合 $U_1,U_2,\cdots,U_k$ 使 $U_i(1 \le i \le k)$ 的平均数相等。

## 分析
设 $U_i$ 的元素个数为 $n_i$，元素和为 $SU_i$，由题意，$\frac{SU_1}{n_1}=\frac{SU_2}{n_2}=\cdots=\frac{SU_k}{n_k}=\bar x$，所以 $\frac{SU_1+SU_2+\cdots+SU_k}{n_1+n_2+\cdots+n_k}=\bar x$，所以每个子集的平均数等于整个集合的平均数。

先判断 $\bar x$ 是否为整数，再让所有 $a_i$ 减 $\bar x$，若答案存在，一定有子集和为 $0$，随机打乱足够多次后一定有子段和为 $0$，此时用 ```set``` 判断一下前缀和有没有重复的即可。

## 代码
``` cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
#include<ctime>
#include<set>
using namespace std;
int n, t, a[1005], s[1005];
bool f[10000005][2];
set <int> m;
bool check(){
	int k = 1000;
	while(k--){
		random_shuffle(a + 1, a + n + 1);
		m.clear();
		m.insert(0); //注意0
		for(int i = 1; i < n; i++){ //注意不能遍历到n
			s[i] = a[i] + s[i - 1];
			if(m.count(s[i]))
				return 1;
			 m.insert(s[i]); 
		}
	}
	return 0;
}
int main(){
	srand(time(0));
	cin >> t;
	while(t--){
		cin >> n;
		int sum = 0;
		for(int i = 1; i <= n; i++){
			cin >> a[i];
			sum += a[i];
		}
		if(sum % n != 0){
			cout << "No" << endl;
			continue; 
		}
		sum /= n;
		for(int i = 1; i <= n; i++)
			a[i] -= sum; 
		if(check())
			cout << "Yes" << endl;
		else
			cout << "No" << endl;
	}
	return 0;
}
```
概率很高的，我 $3$ 次有 $2$ 次 AC。

---

## 作者：m1kusama (赞：1)

## 题目大意
给定长度为 $n$ 的序列，将其分成至少两份，你要保证每份的元素之平均都与总平均相等。

## 解题思路

先求出总平均 $x$ （因为题目说会用到），此时发现若总平均不是整数，则违背题意，直接特判输出 `No`。

然后将序列每个元素全部减去 $x$，放进正负两个桶里（负数取绝对值），遍历一遍序列，对于每个桶，**从后向前遍历**，若此位置非空，更新能由此桶中组成的数，将其放入桶里。

至于为什么要从后往前遍历：举个例子，若正数桶中有 $3$ 个元素 $0$，$3$，$4$，处理完的序列为：$1$，$-2$，$3$，$4$，$-1$，则使用 $1$ 更新 $0$，$3$ 更新 $0$，$4$ 更新 $0$，桶中变成 $0$，$1$，$3$，$4$，再遍历桶中的 $1$，再用序列中的 $1$ 去更新它，桶中出现了错误元素 $2$。若从后往前遍历，就会避免这种问题，因为更新后加入的元素一定严格不小于当前元素，下标就严格不小于此元素，而每次循环变量变小 $1$，新更新的元素就不会出现在下一次循环里。

结束后，遍历正负两个桶，若非最大元素相同，则跳出循环，输出 `Yes`，否则输出 `No`。

至于此方法的正确性，设共有 $n$ 个元素，将正负桶里组成此相同元素的值放入一个集合，集合大小为 $n_1$，此集合的平均值就是 $x$，而剩下的元素之平均数为 $\frac {n \times x-n_1 \times x}{n-n_1}=x$，剩下的数分为另一个集合，则两个集合平均都为 $x$，满足条件。

再考虑相同元素为最大值的情况，则剩下的数集为空，不能组成一个满足要求的集合，故错误。

## 赛时代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
bool t1[1000005],t2[1000005];//正负两个桶
int n,cnt=0,a[1005];
void solve(){
	memset(t1,false,sizeof t1);//多测记得清空
	memset(t2,false,sizeof t2);
	cnt=0;
	int flag=0,ma=0;//最大值
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		cnt+=a[i];
	}
	if(cnt%n!=0){
		cout<<"No\n";
		return;
	}
	cnt/=n;
	for(int i=1;i<=n;i++){
		a[i]-=cnt;
		if(a[i]==0) flag=1;
		if(a[i] > 0){
			ma += a[i];
		}
	}
	t1[0]=true;
	t2[0]=true;
	for(int j = 1;j <= n;j++){
		if(a[j]>0){
			for(int i=ma;i>=0;i--){
				if(t1[i]){
					t1[i+a[j]]=true;
				}
			}
		}
		if(a[j]<0){
			for(int i=ma;i>=0;i--){
				if(t2[i]){
					t2[i-a[j]]=true;
				}
			}
		}
	}
	for(int i=1;i<=ma;i++){
		if(t1[i]==t2[i] and t1[i]==true and !flag and i!=ma){
			flag=1;
		}
	}
	if(!flag) cout<<"No\n";
	else cout<<"Yes\n";
}

int main(){
	cin>>t;
	while(t--){
		solve();
	}
}
```


---

## 作者：ncwzdlsd (赞：0)

一个性质：若一个序列是平均的，它一定可以被拆分成两个序列 $\{a_k\},\{b_{n-k}\}$，这两个序列的平均数与原序列的平均数相等。

> 证明：假设这两个子序列的平均数为 $A$，即 $\dfrac{s_a}{k}=\dfrac{s_b}{n-k}=A$，根据合比定理有 $\dfrac{s_a+s_b}{n}=A_a=A$。

于是只要得到一个平均数与序列平均数相等的子序列，该序列就是平均的。考虑多次随机打乱子序列，记录前缀和暴力枚举子序列，可以通过所有子任务但无法通过 Hack 数据。

注意到暴力枚举子序列的操作是 $O(n^2)$ 的，用一个技巧进行优化。把序列中的每一项都减掉平均数，这样序列的平均数变为 $0$，消除了对子序列长度的考虑，只需要找到一个和为 $0$ 的子序列，或者找到两个大小相等的前缀和即可。查询重复出现的前缀和可以用 `set` 实现 $O(\log n)$ 级别的查询。


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

const int maxn=1005;
int a[maxn];
set<int> s;

void solve()
{
    int n;cin>>n;
    int sum=0;
    for(int i=1;i<=n;i++) cin>>a[i],sum+=a[i];
    if(sum%n) return cout<<"No\n",void();
    int T=1000;sum/=n;
    for(int i=1;i<=n;i++) a[i]-=sum;
    while(T--)
    {
        random_shuffle(a+1,a+n+1);
        // for(int i=1;i<=n;i++) s[i]=s[i-1]+a[i];
        int res=0;s.clear();
        for(int i=1;i<n;i++)
        {
        	res+=a[i];
        	if(!res||s.count(res)) return cout<<"Yes\n",void();
        	s.insert(res);
        }
    }
    cout<<"No\n";
}

signed main()
{
    int q;cin>>q;
    while(q--) solve();
    return 0;
}
```

---

## 作者：史蒂夫的憨憨 (赞：0)

思路：首先求出序列和，并判断其平均数 $\bar x$ 是否为整数，不是整数则无解。之后，我们开两个数组分别存储 $\bar x$ 与小于其元素的差与大于其元素与之的差，并用类背包的方法分别求出两个数组元素可以组成的所有数，然后比对是否有相同的，有则输出 ```Yes```，否则输出 ```No```。

注意：多测要清空。

代码如下：
```cpp
#include<vector>
#include<cstring>
#include<iostream>
using namespace std;
const int N=1e3+5,M=1e7+5;
int T,n,m,sum,p,l1,l2,f1,f2,p1,p2;
int a[N],t1[N],t2[N];
int dp1[M],dp2[M];
bool fl1[M],fl2[M];
int main(){
	cin>>T;
	while(T--){
		memset(fl1,0,sizeof(fl1));
		memset(fl2,0,sizeof(fl2));
		p1=p2=p=l1=l2=sum=0;
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			sum+=a[i];
		}
		if(sum%n!=0){
			cout<<"No\n";
			continue;
		}
		sum/=n;
		for(int i=1;i<=n;i++){
			if(a[i]-sum>0){
				t1[++l1]=a[i]-sum; 
				p+=a[i]-sum;
			}else{
				t2[++l2]=sum-a[i];
			}
		}
		if(p==0){//特判，说明所有数一样 
			cout<<"Yes\n";
			continue;
		}
		for(int i=1;i<=l1;i++){//用类背包思想求所有可能的数 
			int l=p1;
			for(int j=1;j<=l;j++){
				int x=t1[i]+dp1[j];
				if(fl1[x]) continue;
				dp1[++p1]=x;
				fl1[x]=true;
			}
			if(fl1[t1[i]]) continue;
			dp1[++p1]=t1[i];
			fl1[t1[i]]=true;
		}
		for(int i=1;i<=l2;i++){
			int l=p2;
			for(int j=1;j<=l;j++){
				int x=t2[i]+dp2[j];
				if(fl2[x]) continue;
				dp2[++p2]=x;
				fl2[x]=true;
			}
			if(fl2[t2[i]]) continue;
			dp2[++p2]=t2[i];
			fl2[t2[i]]=true;
		}
		f1=f2=1;
		bool flag=false;
		for(int i=1;i<p;i++){//检查是否有相同的组合 
			if(fl1[i]&&fl2[i]){
				flag=true;
				break;
			}
		}
		if(flag) cout<<"Yes\n";
		else cout<<"No\n";
	}
	return 0;
}
```


---

