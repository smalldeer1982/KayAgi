# Three Blocks Palindrome (hard version)

## 题目描述

The only difference between easy and hard versions is constraints.

You are given a sequence $ a $ consisting of $ n $ positive integers.

Let's define a three blocks palindrome as the sequence, consisting of at most two distinct elements (let these elements are $ a $ and $ b $ , $ a $ can be equal $ b $ ) and is as follows: $ [\underbrace{a, a, \dots, a}_{x}, \underbrace{b, b, \dots, b}_{y}, \underbrace{a, a, \dots, a}_{x}] $ . There $ x, y $ are integers greater than or equal to $ 0 $ . For example, sequences $ [] $ , $ [2] $ , $ [1, 1] $ , $ [1, 2, 1] $ , $ [1, 2, 2, 1] $ and $ [1, 1, 2, 1, 1] $ are three block palindromes but $ [1, 2, 3, 2, 1] $ , $ [1, 2, 1, 2, 1] $ and $ [1, 2] $ are not.

Your task is to choose the maximum by length subsequence of $ a $ that is a three blocks palindrome.

You have to answer $ t $ independent test cases.

Recall that the sequence $ t $ is a a subsequence of the sequence $ s $ if $ t $ can be derived from $ s $ by removing zero or more elements without changing the order of the remaining elements. For example, if $ s=[1, 2, 1, 3, 1, 2, 1] $ , then possible subsequences are: $ [1, 1, 1, 1] $ , $ [3] $ and $ [1, 2, 1, 3, 1, 2, 1] $ , but not $ [3, 2, 3] $ and $ [1, 1, 1, 1, 2] $ .

## 样例 #1

### 输入

```
6
8
1 1 2 2 3 2 1 1
3
1 3 3
4
1 10 10 1
1
26
2
2 1
3
1 1 1```

### 输出

```
7
2
4
1
1
3```

# 题解

## 作者：_byta (赞：6)

看到 n 非常大，而 $a(i)$ 的值域很小，我们可以从值域入手，考虑用桶来做。

由此我们开一个 vector 记录 $a(i)$ 到 i 为止出现的次数，再开一个二维数组 $b$ 记录到 i 为止 $a(i)$ 出现的次数。

那么在统计答案时，我们只需要对于原数组每个数，记录一下以他为中心断开时能取到的最大值，最后取一个最大即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int z=200;
int n,m,a[200001],b[200001][201];
vector<int>v[201];// v 存某一个数 ai 到 i 出现的次数以及出现到这个次数的位置 
void solve()
{
	cin >> n;
	for(int i=1; i<=z ;i++)v[i].clear();
	int ans=0;
	for(int i=1; i<=n ;i++)
	{
		cin >> a[i];
		v[a[i]].push_back(i);
		for(int j=1; j<=z ;j++)
		{
			b[i][j]=b[i-1][j];
		}
		b[i][a[i]]++;
		ans=max(ans,b[i][a[i]]);
	}
	for(int i=1; i<=n ;i++)
	{
		int f=b[i][a[i]];
		int l=i;
		int r=v[a[i]][v[a[i]].size()-f];
		if(r<=l) continue;
		for(int j=1; j<=z ;j++)
		{
			ans=max(ans,b[r-1][j]-b[l][j]+f*2);
		}
	}
	cout << ans << endl;
}
int main()
{
	ios::sync_with_stdio(0);
	int t;
	cin >> t;
	while(t--)
	{
		solve();
	}
}
```





---

## 作者：Eibon (赞：5)

发现 $a_{i} \le 200$，考虑对每个位置 $i$，算出截止当前位置，数字 $a_j$ 出现的次数 $num_{i,j}$，找到后缀次数同样为 $num_{i,j}$ 的 $k$。判断 $k$ 是否大于 $i$，确保合法。然后枚举每个数字在这两段区间的出现次数。最后与 $ans$ 取 $\max$ 即可。

$ans$ 要先初始化成序列中出现次数最多的 $a_i$，对于数字 $a_i$ 第几次出现的位置，可以用 vector 维护。

```cpp
#include <bits/stdc++.h>
using namespace std;
//#define int long long
const int maxn=2e5+5;
int T,n,ans;
int a[maxn],num[maxn][205];
vector<int>v[205];
signed main()
{
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		ans=1;
		for(int i=1;i<=200;i++){
			v[i].clear();
		}
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			v[a[i]].push_back(i);
			for(int j=1;j<=200;j++){
				if(a[i]==j){
					num[i][j]=num[i-1][j]+1;
				}
				else{
					num[i][j]=num[i-1][j];
				}
				ans=max(ans,num[i][j]);
			}
		}
		for(int i=1;i<=n;i++){
			int m=num[i][a[i]];
			int k=v[a[i]][v[a[i]].size()-m];
			if(k<=i){
				continue;
			}
			for(int j=1;j<=200;j++){
				ans=max(ans,num[k-1][j]-num[i][j]+m*2);
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
//dyyyyds
```

---

## 作者：奇米 (赞：5)

## $\mathrm{E1,E2.\ Three \ Blocks\ Palindrome }$

[$$\huge\color{blue}\boxed{\color{Violet}\mathfrak{There\ is \ my \ blog}}$$](https://www.luogu.com.cn/blog/wyy2020/)

####  **题目意思**
*  [CF1335E1 ](https://www.luogu.com.cn/problem/CF1335E1)
*  [CF1335E2 ](https://www.luogu.com.cn/problem/CF1335E2)

####   $\mathrm{Sol}$
* 比较简单的模拟题
* 首先我们记录某一个数$a_i$到$i$出现的次数以及出现到这个次数的位置。前缀后缀个各做一遍。
* 然后我们枚举第一个颜色$x$以及它第一段的长度$l$。然后得出$p_1,p_2$分别表示前缀$x$颜色到达$l$个的位置，以及后缀到达$l$个的位置。然后在枚举第二种颜色$y$，那么$ans=\max(ans,l\times 2+\max_{colsum}(p_2-p_1))$,$\max_{colsum}(p_2-p_1)$为到$[p1,p2]$这段区间里面出现次数最多的颜色数量。

####   $\mathrm{Sol}$
* 写法$1$

```cpp
#include <bits/stdc++.h>
#define pb push_back
using namespace std;

inline int read()
{
	int sum=0,ff=1; char ch=getchar();
	while(!isdigit(ch))
	{
		if(ch=='-') ff=-1;
		ch=getchar();
	}
	while(isdigit(ch))
		sum=sum*10+(ch^48),ch=getchar();
	return sum*ff;
}

const int N=2e5+5;

int n,m,f[N][205],g[N][205],a[N],pre[205][N],suf[205][N],ans;

int main()
{
	int Q=read();
	for (;Q--;)
	{
		n=read();
		for ( int i=1;i<=n;i++ )
		{
			a[i]=read();
			for ( int j=1;j<=200;j++ ) f[i][j]=f[i-1][j];
			f[i][a[i]]++;
			pre[a[i]][f[i][a[i]]]=i;
		}
		for ( int i=n;i>=1;i-- ) 
		{
			for ( int j=1;j<=200;j++ ) g[i][j]=g[i+1][j];
			g[i][a[i]]++;
			suf[a[i]][g[i][a[i]]]=i;
		}
		for ( int i=1;i<=200;i++ ) 
		{
			for ( int j=1;j<=f[n][i]/2;j++ ) 
			{
				int pos1=pre[i][j];
				int pos2=suf[i][j];	
				if(pos1>pos2) continue;
				for ( int k=1;k<=200;k++ ) 
				{
					if(k==i) continue;
					ans=max(ans,j*2+f[pos2][k]-f[pos1][k]);
				}
//				if(ans==4) cout<<i<<" "<<j<<" "<<pos1<<" "<<pos2<<endl;
			}
			ans=max(ans,f[n][i]);
		}
		printf("%d\n",ans);
		ans=0;
		for ( int i=1;i<=n;i++ ) 
			for ( int j=1;j<=200;j++ ) 
			{
				f[i][j]=g[i][j]=0;
				pre[j][i]=suf[j][i]=0;
			}
	}
	return 0;
}
```
* 写法$2$（**建图优化内存**）

```cpp
#include <bits/stdc++.h>
#define pb push_back
using namespace std;

inline int read()
{
	int sum=0,ff=1; char ch=getchar();
	while(!isdigit(ch))
	{
		if(ch=='-') ff=-1;
		ch=getchar();
	}
	while(isdigit(ch))
		sum=sum*10+(ch^48),ch=getchar();
	return sum*ff;
}

const int N=2e5+5;
int n,m,ans,f[N][205],TT,a[N],l[N],head[N];


struct nood
{
	int nex,to;
};
nood e[N];

inline void jia(int u,int v)
{
	e[++TT].nex=head[u];
	head[u]=TT;
	e[TT].to=v;
}

int main()
{
	int Q=read();
	for (;Q--;)
	{
		n=read();
		for ( int i=1;i<=200;i++ ) head[i]=0;
		TT=0;
		for ( int i=1;i<=n;i++ )
		{
			a[i]=read();
			jia(a[i],i);
			for ( int j=1;j<=200;j++ ) 
				f[i][j]=f[i-1][j];
			f[i][a[i]]++;
		}
		int ans=1;
		for ( int k=1;k<=200;k++ ) 
		{
			int cnt=0;
			for ( int p=head[k];p;p=e[p].nex )
			{
				int v=e[p].to;
				l[++cnt]=v;
			}
			int p=cnt/2;
			for ( int i=1;i<=p;i++ )
			{
				int mx=0;
				for ( int j=1;j<=200;j++ )
					mx=max(mx,f[l[i]-1][j]-f[l[cnt-i+1]][j]);
				ans=max(ans,mx+i*2);
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：Limit (赞：5)

# 题目大意

给出一个序列,找到一个最长的**子序列**,使得子序列满足 $\begin{matrix}[\underbrace{a,a,\dots,a}\\x\end{matrix}\begin{matrix}\underbrace{b,b,\dots,b}\\y\end{matrix}\begin{matrix}\underbrace{a,a,\dots,a}]\\x\end{matrix}$.

即开始和结束为 $x$ 个 $a$, 中间  $y$ 个 $b$,($0\leq x\leq\lfloor\frac{n-1}{2}\rfloor$,$1\leq y\leq n$).

(本题有两个part)

# Part1

可以发现 $n$ 很小,那么枚举两个点,计算两个点到边界中每种数出现的次数,左右取 $\min$ 之后再取 $\max$,中间同样取出 $\max$ 然后计算和,取 $\max$,就是答案,前缀和搞一下就是 $\mathcal{O}(n^2a)$ 了(具体我也没写过).

# Part2

同样考虑前缀和,每个数出现次数,然后考虑将原序列拆成若干条链(每条链上的数相等),然后考虑枚举 $a$,枚举 $x$,再枚举 $b$,时间复杂度看似是 $\mathcal{O}(na^2)$ 的,但是用了链表优化之后在枚举 $x$ 的时候 $1\sim n$ 都只会出现一次,所以时间复杂度就是 $\mathcal{O}(na)$ 了.

# 代码

```cpp
#include<bits/stdc++.h>
#define REP(i,first,last) for(int i=first;i<=last;++i)
#define DOW(i,first,last) for(int i=first;i>=last;--i)
using namespace std;
const int MAXN=2e5+5;
int n,m;
int T;
struct Edge//用链式前向星来代替链表
{
	int to,next;
}edge[MAXN];
int edge_head[MAXN];
int edge_cnt=0;
#define FOR(now) for(int edge_i=edge_head[now];edge_i;edge_i=edge[edge_i].next)
#define TO edge[edge_i].to
void AddEdge(int form,int to)
{
	edge[++edge_cnt].to=to;
	edge[edge_cnt].next=edge_head[form];
	edge_head[form]=edge_cnt;
}
int sum[MAXN][201];//前缀和
int l[MAXN];
int arr[MAXN];
void work()
{
	REP(i,1,200)//初始化
	{
		edge_head[i]=0;
	}
	edge_cnt=0;
	scanf("%d",&n);
	REP(i,1,n)
	{
		scanf("%d",&arr[i]);
		AddEdge(arr[i],i);//在这个数中加上这个位置
		REP(j,1,200)//前缀和
		{
			sum[i][j]=sum[i-1][j];
		}
		sum[i][arr[i]]++;
	}
	int answer=1;//初值为1
	REP(k,1,200)//枚举a的值
	{
		int cnt=0;
		FOR(k)//先将位置离线出来,用链式前向星的话是从大到小的
		{
			l[++cnt]=TO;
		}
		int p=cnt/2;//枚举上限
		REP(i,1,p)//枚举x的大小
		{
			int max_num=0;
			REP(j,1,200)//在中间找出现最多的数,可以直接用前缀和相减得到
			{
				max_num=max(max_num,sum[l[i]-1][j]-sum[l[cnt-i+1]][j]);
			}
			answer=max(answer,max_num+i*2);//和答案取max
		}
	}
	printf("%d\n",answer);//输出答案
}
int main()
{
	scanf("%d",&T);
	REP(i,1,T)
	{
		work();
	}
	return 0;
}
```



---

## 作者：HoshizoraZ (赞：2)

因为 E1,E2 的区别只在数据范围上体现，所以我在此就写下优化代码的过程吧。

------------

首先，发现 E1 的数据范围很小，我们可以考虑这样一个算法：

- 从前往后枚举第一个位置 $i$，从后往前枚举第二个位置 $j$，同时保证 $0 \le i<j \le n+1$。
- 枚举取值 $k=1 \sim 26$，对于每个 $k$ 分别找到区间 $[1,i],\ [j,n]$ 中 $k$ 的出现次数，将二者取**较小值**得到 $ans_1$。
- 中间的部分，找到区间 $[i+1,j-1]$ 中出现次数最多的数，并将其出现次数即为 $ans_2$，最终答案即为 $2 \times ans_1+ans_2$。

当然直接暴力是过不去的，我们可以将数字 $1 \sim 26$ 在序列每一个位置的出现次数都记录一个**前缀和**，这样在查询某个字符在**某个区间**的出现次数时可以直接 $O(1)$ 计算得到。

该算法的时间复杂度为 $O(n^2 \times a_i)$，3s 内肯定能过。

----------

接下来考虑如何优化这个算法。

**优化一**

我们发现，在枚举 $i$ 的过程中，当 $j$ 一定时，相比于 $i-1$ 只有 $a_i$ 的前缀出现次数发生了改变。

所以不必枚举取值，每次枚举 $i,j$ 时直接令 $k=a_i$ 即可，时间复杂度降为 $O(n^2)$。

**优化二**

根据优化一，对于枚举的的每一个 $i$，都最多只有一个位置 $j$ 同时满足以下两个条件：
- $a_i=a_j$
- $\sum_{x=1}^{i-1}[a_x=a_i]=\sum_{x=j+1}^n[a_x=a_i]$

因此可以针对不同的取值 $k$，可以记录序列中第 $1,2,...$ 个数值等于 $k$ 的位置。

在每次枚举 $i$ 的时候，合适的 $j$ 就可以直接通过记录被找到。

然后中间的部分只需要枚举取值 $k$，通过前缀和找到 $[i+1,j-1]$ 中出现次数最多的 $k$。

该算法的时间复杂度就降为了 $O(n \times \max\{a_i\})$，此时已经可以通过本题。

----------

**节省空间的解法**

前文提到的前缀和数组，理论上开 $4e7$ 的 int 是可以满足空间限制的。

但是我在做题的时候把空间算错了，就以为上述算法无法通过，于是又想了一个节省空间，但效率稍低的算法。

既然没法记前缀和了，我们可以用一些其它的方式求区间和。

我们开 200 个 `vector`（下文定义变量名为 `v`），第 $i$ 个 `vector` **按从前到后的顺序**记录原序列中数值等于 $i$ 的**位置**。

- 按 $n\rightarrow1$ 逐个枚举 $i$，这样做是为了方便之后的查找数列**单调不降**，方便之后使用 `STL` 的二分（当然手写二分也行）。
- 记录 $a_i=k$，二分找 $k$ 是**整个序列**中第几个等于 $k$ 的数，那么就知道 $[i,n]$ 有不同的 $k$ 的数量，在此记为 $num$。
- 同理，可以找到一个满足 $\sum_{x=1}^{j}[a_x=a_i]=\sum_{x=j}^n[a_x=a_i]$ 的 $j$，这可以查找 `v[a[i]][num - 1]` 得到。
- 接下来查找中间的部分 $[j+1,i-1]$。
	- 枚举在 $1\sim200$ 内的取值 $k$。
    - 找到所有等于 $k$ 的数中第一个**大于** $i-1$ 的数在 `vector` 中的下标 $pos_1$。
    - 找到所有等于 $k$ 的数中第一个**大于等于** $j+1$ 的数在 `vector` 中的下标 $pos_2$。
    - $pos_1-pos_2$ 就是区间 $[j+1,i-1]$ 中等于 $k$ 的数字数量。
- 对于相同的 $i,j$ 找到最大的一个 $pos_1-pos_2$ 加上 $2num$ 即为答案。

由于两百个 `vector` 一共就存 $n$ 个数，该算法空间复杂度降为 $O(n)$。

当然，该算法对时间作出了一定牺牲。瓶颈在于查找 $pos_1,pos_2$ 相比原算法多了一个二分，但两百次 `vector` 二分的长度**之和**等于 $n$，所以算法的时间复杂度为 $O(n \times \max\{a_i\} \times k)$，$k$ 最大约等于 $10$（不含 `vector` 自身常数）。

该做法不经过任何常数优化也可以通过，详情见代码。

**代码（最慢点 1.67s，空间最大 3.35MB）：**
```cpp
int t, n, a[200010], q[210], ans;
vector <int> v[210];

inline int max(int a, int b){
	return a > b ? a : b;
}

int main(){

	scanf("%d", &t);
	while(t--){
		scanf("%d", &n);
		for(int i = 1; i <= n; i++)
			scanf("%d", &a[i]);
		for(int i = 1; i <= 200; i++)	// 初始化
			q[i] = 0, v[i].clear();
		ans = 0;
		for(int i = 1; i <= n; i++)		// 向 vector 填充数据
			v[a[i]].push_back(i), q[a[i]]++, ans = max(ans, q[a[i]]);
		for(int i = n, pos, now, poss; i >= 1; i--){
			poss = lower_bound(v[a[i]].begin(), v[a[i]].end(), i) - v[a[i]].begin();	// 找排行
			poss = v[a[i]].size() - poss;	// 改为上文提到的 num
			pos = v[a[i]][poss - 1];	// 上文的 j
			if(pos >= i) continue;		// 注意 pos 一定要小于 i
			now = 0;
			for(int j = 1, pos1, pos2; j <= 200; j++){
				pos1 = lower_bound(v[j].begin(), v[j].end(), i) - v[j].begin();
				pos2 = upper_bound(v[j].begin(), v[j].end(), pos) - v[j].begin();
				now = max(now, pos1 - pos2);
			}
			ans = max(ans, poss * 2 + now);
		}
		printf("%d\n", ans);
	}

	return 0;
}
```

---

## 作者：suxxsfe (赞：1)

[在我的blog中查看](https://www.cnblogs.com/suxxsfe/p/12696998.html)  

就是我这个菜鸡，赛时写出了 E2 的做法，但是算错复杂度，导致以为自己的做法只能AC E1，就没交到 E2 上，然后赛后秒A.....  

## 题意

定义一种字串为形如：$[\underbrace{a, a, \dots, a}_{x}, \underbrace{b, b, \dots, b}_{y}, \underbrace{a, a, \dots, a}_{x}]$  

问你在给定的字串中，符合这种要求的最大子序列（可以不连续）的长度  
给出数列长度 $n\le 2\cdot 10^5$，数列中每个数 $a_i\le 200$  

-----------  

考虑暴力枚举 $a$，然后对于每一个 $a$，枚举 $x$，也就是两边的 $a$ 的 个数  
用两个 `vector`，分别记录从前和从后数，第 $x$ 个 $a$ 的位置  
然后一直枚举到第 $\lfloor\dfrac{\text{a出现的次数}}{2}\rfloor$ 个  
此时，再暴力枚举 $b$，记录一个前缀和 $sum_{b,i}$，表示 $b$ 这个数，在前 $i$ 位中出现的次数  
假设在 `vector` 中记录的整数第 $x$ 个 $a$ 的位置是 $pos1$，倒数第 $x$ 个位置是 $pos2$，那么中间 $b$ 的个数就是 $sum_{b,pos2}-sum_{b,pos1-1}$  
然后给所有枚举到的 $b$ 取一个 $\max$ 就行  

注意在 $pos1,pos2$ 中，要分别先 `push_back` 一个 $0$ 和 $n+1$，意思是正数倒数第 $0$ 第出现的位置，同时方便后面的枚举  

每枚举一个 $a$，设它出现的次数为 $num_a$，则它的复杂度为 $200\times num_a$  
那么总复杂度是 $\sum_{i=1}^{200}num_a\times 200=200\times n$  

~~赛时没想到这点导致并没有交 E2 qaq~~  

```cpp  
#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cmath>
#include<map>
#include<iomanip>
#include<vector>
#include<cstring>
#define reg register
#define EN std::puts("")
#define LL long long
inline int read(){
	register int x=0;register int y=1;
	register char c=std::getchar();
	while(c<'0'||c>'9'){if(c=='-') y=0;c=std::getchar();}
	while(c>='0'&&c<='9'){x=x*10+(c^48);c=std::getchar();}
	return y?x:-x;
}
int sum[206][200006];
std::vector<int>pos1[206],pos2[206];
int num[206];
int a[200006];
int main(){int T=read();while(T--){
//		std::printf("%lld",sizeof sum+sizeof pos1+sizeof pos2+sizeof a);
	int n=read();
	for(reg int i=1;i<=200;i++){
		pos1[i].clear();pos2[i].clear();
		pos1[i].push_back(0);pos2[i].push_back(n+1);
	}
	for(reg int x,i=1;i<=n;i++){
		for(x=1;x<=200;x++) sum[x][i]=sum[x][i-1];
		a[i]=read();sum[a[i]][i]++;
		num[a[i]]++;pos1[a[i]].push_back(i);
	}
	for(reg int i=n;i;i--) pos2[a[i]].push_back(i);
	reg int ans=0;
	for(reg int a=1;a<=200;a++){
		for(reg int x=0;x<=num[a]>>1;x++){
			for(reg int b=1;b<=200;b++)
				ans=std::max(ans,(x<<1)+sum[b][pos2[a][x]-1]-sum[b][pos1[a][x]]);
		}
	}
	std::printf("%d\n",ans);
	std::memset(num,0,sizeof num);
	for(reg int x,i=1;i<=n;i++){
		for(x=1;x<=200;x++) sum[x][i]=0;
	}
}
	return 0;
}
```

---

## 作者：ctq1999 (赞：1)

$Div3$ 的 $E$  $\text{Three Blocks Palindrome}$。

## 题解

注意到 $a_i$ 是只有 $1 \leq a_i \leq 200$ ，所以可以通过枚举两个不同颜色的方式来算出答案。

定义 $sum[i][j]$ 表示在 $[1,j]$ 的范围内 $i$ 的个数。
定义 $at[i][j]$ 表示第 $j$ 个 $i$ 在数组上位置。

先 $i$ 枚举外面两个区间的颜色。再 $j$ 枚举外面两个区间的长度。得到外面区间与内区间在原数组的断点。

```cpp
int from = at[i][j - 1];
int to = at[i][sum[i][n] - j];
```

即 $[1,from]$ 和 $[to,n]$ 是两个外区间，$[from+1, to-1]$ 是内区间。

再 $k$ 枚举里面区间的长度。

```cpp
ans = max(ans, sum[i][from] + sum[k][to - 1] - sum[k][from] + sum[i][n] - sum[i][to - 1]);
```

不用 $vector$ 好像会 $\text{MLE}$，好像出题人卡空间了。

## 代码

```cpp
#include <bits/stdc++.h>

#define ll long long

using namespace std;

const int MAXN = 200010;
const int MAXM = 210;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;

int n, m, k;
int ans, tot;

int a[MAXN];

int main(){
	int t;
	cin >> t;
	while (t--) {
		ans = 0;
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) {
			scanf("%d", &a[i]);
		}
		m = 200;
		vector<vector<int> > at(m + 1);
		vector<vector<int> > sum(m + 1, vector<int>(n + 1));
		for (int i = 1; i <= m; i++) {
			for (int j = 1; j <= n; j++) {
				sum[i][j] = sum[i][j - 1] + (a[j] == i);
				if (a[j] == i) {
					at[i].push_back(j);
				}
			}
		}
		for (int i = 1; i <= m; i++) {
			ans = max(ans, sum[i][n]);
			for (int j = 1; 2 * j <= sum[i][n]; j++) {
				int from = at[i][j - 1];
				int to = at[i][sum[i][n] - j];
				for (int k = 1; k <= m; k++) {
					ans = max(ans, sum[i][from] + sum[k][to - 1] - sum[k][from] + sum[i][n] - sum[i][to - 1]);
				}
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}

```




---

## 作者：_JF_ (赞：0)

[Link](https://www.luogu.com.cn/problem/CF1335E2)

这居然有 $^*1800$。。

肯定是从值域入手，然后呢？

一开始考虑从中间的 $y$ 着手考虑，发现至少要枚举末位置和长度才能确定 $x$，不好搞，也考虑过 dp，感觉也不太会/yun

于是我开始考虑从 $x$ 着手。

考虑到一个很显然的贪心，考虑 $x$ 固定，那么对于 $a$ 而言肯定是越靠近两边越好，这样留给 $b$ 的位置就尽可能的多。

具体的，用一个 `vec` 维护每个数出现的位置。根据这个贪心，我们只要从两端向中间取就一定最优。

然后计算这个 $b$ 预处理前缀和扫一下值域就没了。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define DEBUG cout<<"when can get npy"<<endl;
const int N =3e5+10;
int a[N],s[206][N],n,ans;
vector<int> g[206];
int Slove(int l,int r,int dus,int op){
	int sum=0;
	for(int i=1;i<=200;i++){
		if(op==i)	continue;
		int now=s[i][r-1]-s[i][l];
		sum=max(sum,now);
	}
	return sum;
}
signed main(){
	int t;
	cin>>t;
	while(t--){
		ans=0;
		for(int i=1;i<=200;i++)	g[i].clear();
		cin>>n;
		for(int i=1;i<=n;i++)	for(int j=1;j<=200;j++)	s[j][i]=0;
		for(int i=1;i<=n;i++){
			cin>>a[i],g[a[i]].push_back(i),ans=max(ans,(int)g[a[i]].size());
			for(int j=1;j<=200;j++){
				if(j==a[i])	s[j][i]=s[j][i-1]+1;
				else	s[j][i]=s[j][i-1];
			}
		}
		for(int i=1;i<=200;i++){
			if(g[i].size()==0)	continue;
			int l=0,r=(int)(g[i].size())-1,len=1;
			
			while(l<=r){
//				if(i==3)	cout<<g[i][l]<<" "<<g[i][r]<<endl;
				int now=Slove(g[i][l],g[i][r],len,i);
				if(g[i][l]==g[i][r])	ans=max(ans,1);
				else ans=max(ans,len*2+now);
				l++,r--,len++;
			}
		}
		cout<<ans<<endl;
	}
	
	return 0;
}
// 22:00 begin 
```

---

## 作者：chlchl (赞：0)

## Solution
思维题。

显然如果我们确定了 $a$ 是多少，那么我们一定选的是最外面的 $x$ 个 $a$，否则答案一定不会更优（中间可供选择的位置变少了，答案不会优的）。

又注意到其实值域并不大，枚举 $a$ 的值和其出现的次数 $k$，我们可以直接得到前 $k$ 个 $a$ 的结束位置 $l$ 和最后 $k$ 个 $a$ 的开始位置 $r$，$(l,r)$ 就是可供选择 $b$ 的位置。

我们用前缀和记录前 $i$ 个位置出现了多少个值为 $j$ 的数，那么 $sum_{r-1,x}-sum_{l,x}$ 就是 $x$ 在这个区间的出现次数。

直接枚举 $x$，对这些 $x$ 取最大值即可。

这个复杂度足以通过本题，为什么？

看似时间复杂度是 $O(n\times \max\{a_i\}^2)$ 的，但实际上是 $O(n\times \max\{a_i\})$ 的。

因为枚举 $k$ 的时候，不需要枚举到 $n$，只需要枚举到 $a$ 出现次数 $\div 2$ 向下取整次即可。

这样显然可以保证，这两重循环最后加起来不会超过 $n$（把枚举 $k$ 理解成枚举到第 $k$ 个 $a$，那么最后每一个数会且仅会被枚举到一次，所以时间复杂度是 $O(n)$ 的）。

ps：如果空间放大一些，利用主席树可以进一步优化这个取最大值的步骤，时间复杂度还能进一步降低。

最后为了防止没有答案，跟 $1$ 要比个大小。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10; 
int T, n, a[N], sum[N][205];
vector<int> pos[N];

void solve(){
	for(int i=1;i<=n;i++)
		for(int j=1;j<=200;j++)
			sum[i][j] = 0;
	for(int i=1;i<=200;i++)
		pos[i].clear();
	scanf("%d", &n);
	for(int i=1;i<=n;i++){
		scanf("%d", &a[i]);
		sum[i][a[i]] = 1;
		pos[a[i]].push_back(i);
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=200;j++)
			sum[i][j] += sum[i - 1][j];
	int ans = 0;
	for(int c=1;c<=200;c++){
		int len = pos[c].size();
		for(int x=1;x<=len/2;x++){
			int l = pos[c][x - 1] + 1, r = pos[c][len - x] - 1, mx = 0;
			for(int d=1;d<=200;d++)
				mx = max(mx, sum[r][d] - sum[l - 1][d]);
			ans = max(ans, x * 2 + mx);
		}
	}
	printf("%d\n", max(1, ans));
}

int main(){
	scanf("%d", &T);
	while(T--)
		solve();
	return 0;
} 
```


---

