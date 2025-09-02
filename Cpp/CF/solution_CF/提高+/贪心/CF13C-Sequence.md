# Sequence

## 题目描述

Little Petya likes to play very much. And most of all he likes to play the following game:

He is given a sequence of $ N $ integer numbers. At each step it is allowed to increase the value of any number by $ 1 $ or to decrease it by $ 1 $ . The goal of the game is to make the sequence non-decreasing with the smallest number of steps. Petya is not good at math, so he asks for your help.

The sequence $ a $ is called non-decreasing if $ a_{1}<=a_{2}<=...<=a_{N} $ holds, where $ N $ is the length of the sequence.

## 样例 #1

### 输入

```
5
3 2 -1 2 11
```

### 输出

```
4
```

## 样例 #2

### 输入

```
5
2 1 1 1 1
```

### 输出

```
1
```

# 题解

## 作者：FCB_Yiyang2006✈ (赞：50)

## 1.做这道题前需要掌握
> ##### (1) 递推基本思路
> ##### (2) $DP$ 算法基本知识（主要思想）

## 2.进入正题
### (1). 思路
大概的题意就是每次可以对一个数加一或者减一，然后用最 小的代价使得原序列变成不下降的序列。(考虑DP)
### (2). 关于 $DP$
一般用三步来确定线性 $DP$: 定义边界，定义状态，状态转移方程
#### STEP1: $DP$边界 
因为是最小的代价，所以到最后的序列中的每个数字肯定在原先的序列中出现过。（各位巨佬可以想一下到底是为什么，或者简单举几个例子验证一下）
我们用一个字符数组拷贝原先的数组，然后进行从小到大排序。

### STEP2: 定义$DP$
设 $dp[i][j]$ 表示前 $i 个已经符合要求，而且最大数不大于原序列第 $j$ 个元素最小需要的代价。

### STEP3: 状态转移方程
那么我们可以得出转移方程
```cpp
dp[i][j]=min(dp[i][j−1],dp[i−1][j]+abs(a[i]−c[j])
```


## 上代码（c++）
```cpp
#include<bits/stdc++.h>
using namespace std;
const long long maxn=100000000000000005;
long long n;
long long ans=maxn;
long long a[50005],c[50005],dp[2][50005];
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++) 
	{
		cin>>a[i];
	}
    memcpy(c,a,sizeof(a));
    sort(c+1,c+n+1);
    memset(dp,maxn,sizeof(dp));
    for(int i=1;i<=n;i++)
	{
		dp[0][i]=0;	
	}
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
        	dp[1][j]=min(dp[1][j-1],dp[0][j]+abs(a[i]-c[j]));
		}
        swap(dp[1],dp[0]);
    }
    for(int i=1;i<=n;i++)
	{
		ans=min(ans,dp[0][i]);
	}
    cout<<ans<<endl;
    return 0;
}
```
（蒟蒻心地善良，珂以直接 $AC$）

## 3.最后

#### 感谢CF题库供题，洛谷管理员维护,翻译者的翻译和所有点赞用户。

因为我比较弱，有些讲得不清楚的地方敬请谅解，可以在评论区提出。

祝各位早日 $AC$ 本题！

---

## 作者：Yaha (赞：16)

### DP

这题和[P2893](https://www.luogu.com.cn/problem/P2893)差不多，只是这题的数据范围更大些，而空间限制小些。

[我P2893的题解](https://www.luogu.com.cn/blog/Yaha/solution-p2893)

---

（下面这一段是我那篇题解复制过来的，因为两道题思路是一模一样的）

首先看数据范围，$n^2$可以过。

单调不降，我们很容易想到DP。

我们想要花费最小，说明尽可能让每个数动的幅度小一点。能不动就不动，如果必须要动的话，变成上一个位置上的数就可以了。这里假设上一个位置的数已经确定。

所以一个数要么是自己，要么是上一个位置上的数。而上一个数怎么来的呢？很明显，也是这样，要么不动，要么是上上个位置的数。可以一直推下去。这就~~口胡~~得出了众题解中的结论了:

#### 存在一种最优方案，每个位置上的数，是原序列中的数。


我们设$f[i][j]$表示第i个位置放j时的方案数，显然，前一个位置放的数必须比j小。

为了转移方便，我们处理一个b数组，为a数组排序后的数，$f[i][j]$表示第i个位置放b[j]时方案数，前一个位置为b[1]~b[j]，这就满足了前一个位置比这个位置小的要求。

于是得出转移方程：

$f[i][j]=(f[i-1][k]+|a[i]-b[j]|)_{min}$，其中k为1~j中的数。

所以我们定义一个$Min[i][j]$表示f[i][1]~f[i][j]中的最小值。

则新的转移方程为：

### $f[i][j]=Min[i-1][j]+|a[i]-b[j]|$

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int amou=2101,Inf=0x3f3f3f3f;
int a[amou],b[amou],n;
int f[amou][amou],Min[amou][amou];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		b[i]=a[i];
	}
	sort(b+1,b+n+1);
	for(int i=1;i<=n;i++)
	{
		Min[i][0]=Inf;
		for(int j=1;j<=n;j++)
		{
			f[i][j]=Min[i-1][j]+abs(a[i]-b[j]);
			Min[i][j]=min(Min[i][j-1],f[i][j]);
		}
	}
	printf("%d",Min[n][n]);
	return 0;
}
```
----

### 然后是这题不一样的地方，需要特殊处理：

上面的代码交上去你会得到一个大大的MLE，所以我们考虑怎样节省空间。

因为f其实是没用过的，所以直接把f数组舍弃。

Min数组因为只需要用到i-1，所以可以直接省去第一维，但是因为我们要在求值的同时记录，所以用$Min[0][j]$表示上$Min[i-1][j]$，$Min[1][j]$表示$Min[i][j]$；

除此之外，因为CF数据太猛，我们还需要用long long存储。

见代码：

```cpp
#include<bits/stdc++.h>
#define in long long
using namespace std;
const int amou=5e5+90;
const in Inf=0x3f3f3f3f3f3f3f3f;
int a[amou],b[amou],n;
in Min[2][amou];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		b[i]=a[i];
	}
	sort(b+1,b+n+1);
	for(int i=1;i<=n;i++)
	{
		Min[1][0]=Inf;
		for(int j=1;j<=n;j++)
		{
			in f=Min[0][j]+abs(a[i]-b[j]);
			Min[1][j]=min(Min[1][j-1],f);
		}
		for(int j=1;j<=n;j++) Min[0][j]=Min[1][j];
	}
	printf("%lld",Min[1][n]);
	return 0;
}
```


---

## 作者：liuyifan (赞：13)

## 本题可以用堆优化
为了让序列符合题意,y必须>=之前的ymax.因为整个序列最大为y，如果它之前的最大值y1<=x，那么将y减小到x依然可以让序列合法。否则y1<y,就导致
在x-y内的花费是y-x,新答案就能确定正确了

所以这个时候我们就可以开个大根堆优化此过程了

code:~~看起来好短啊~~
```cpp
// luogu-judger-enable-o2
#include<bits/stdc++.h>
#define reg register
#define ll long long
#define inf 0x3f3f3f3f
#define null liuyifan_null
#define y1 liuyifan_y1
#define next liuyifan_next
#define data liuyifan_data
using namespace std;
priority_queue<ll>q;//默认为大根堆
ll n,x,ans;
int main()
{
    scanf("%lld",&n);
    for(reg int i=1;i<=n;i++)
	{
        scanf("%lld",&x);
        q.push(x);//插入堆
        if(q.top()>x)
		{
            ans+=q.top()-x;//top:堆顶的值
            q.pop();//弹出堆顶
            q.push(x);
        }
    }
    printf("%lld",ans);
    return 0;
}
```
## 堆优化后的LUOGU官方例题:[P4597](https://www.luogu.org/problemnew/show/P4597)
本题解的部分严格证明:[题解 P4597 by chen_zhe ](https://www.luogu.org/blog/chen-zhe/solution-p4597)
部分内容参考[题解 P4597 by  bztMinamoto ](https://minamoto.blog.luogu.org/solution-p4597)Orz!Orz!Orz!

---

## 作者：Xie_BR (赞：9)

# 蒟蒻想法，大佬指教！

首先，如果我们需要把调整的总值放到最小，那么其实我们可以想到，最终调整完的数组中的每个数都是原来数组里的数，所以我们需要一个叫做cnt的数组去作为调整数组，就像
```
cnt[i] = a[i];
sort(cnt+1,cnt+n+1);
```
这样一来，每个数的更换值会是最小的。

dp方程：

```
dp[j] = abs(a[i]-a[j]);
dp[j] = min(dp[j],dp[j-1]);
```
所以AC代码如下：
```
#include<iostream>
#include<cmath>
#include<cstring>
#include<cstdio>
#include<algorithm>
#define int long long
#define MK 5010
using namespace std;
int n,a[MK];
int cnt[MK];
int dp[MK];

signed main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		cnt[i] = a[i];
	}
	sort(cnt+1,cnt+n+1);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			dp[j]+=abs(a[i]-cnt[j]);
			if(j>1)
			{
				dp[j] = min(dp[j],dp[j-1]);
			}
		}
	}
	printf("%lld",dp[n]);
	return 0;
}
```


---

## 作者：SpXace (赞：6)

	变化后的每一个值肯定是等于原来序列的某个值，因为只需要变为非递减的，所以对于某个数要么不变，要么变成左右附件的某个值。这样我们就可以根据前述条件得出DP方程了：



**	dp[i][j]=min(dp[i][j-1],dp[i-1][j]+|a[i]-b[j]|)**
    
    
    (a为原序列，b为排序后的序列)，方程的意思是，把序列前i个数变为非递减序列并且以不超过b[j]的值结尾的最小花费，那么它要么是以不超过b[j-1]结尾的最小花费，或者是刚好以b[j]结尾的最小花费
```

/*
/*
日期：2018年10月4日23点33分
地点：诸城
类型：DP
作者：飞马の幻想
题目来源：https://www.luogu.org/problemnew/show/CF13C
input：
5
3 2 -1 2 11

outpu：
4

*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
typedef long long LL;
#define rep(i, a, b) for(int i = a; i <= b; ++i)
#define per(i, a, b) for(int i = a; i >= b; --i)
#define vec(i) for (int i = 0; i < len; ++i)
#define clr(a,b)  memset((a),b,sizeof(a))
using namespace std;
inline int Read(){
	LL s = 0, w = 1; char ch = getchar();
	while(ch < '0' || ch > '9')   { if(ch == '-') w = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') { s = (s << 3) + (s << 1) + (ch ^ 48); ch = getchar(); }
	return s * w;
}
const int MX = 100010;
LL dp[MX],a[MX], b[MX], N;
void init() {
	N = Read();
	rep(i, 1, N) a[i] = Read(), b[i] = a[i];
}
void solve() {
	sort(b + 1, b + 1 + N);
	rep(i, 1, N) 
		rep(j, 1, N){
			if(j == 1) dp[j] += abs(a[i] - b[j]);
			else dp[j] = min(dp[j - 1], dp[j] + abs(a[i] - b[j]));
		}
	printf("%lld\n", dp[N]);
}
int main() {
	init();
	solve();
	return 0;
}
```

---

## 作者：奇米 (赞：5)

# 题解 - $\mathrm{CF13C}$

## 题目意思

[题目传送门](https://www.luogu.com.cn/problem/CF13C)

## $\mathrm{Sol}$

* 简单$DP$

我们设 $f_{i,j}$ 表示构造的序列到第 $i$ 位对应原序列（已排序） 的第 $j$ 位的最小值。

$f_{i,j}=\min_{k=1}^{j}(f_{i-1,k}+|a_i-b_j|)$

然而我们发现 $f_{i-1,k}$ 可以前缀 $\min$ 优化，设 $g_{i,j}$ 表示 $i-1$ 位选 $1\to j$ 位的最小值

$f_{i,j}= g_{i-1,j}+|a_i-b_j|$

注意空间问题，只要滚存一下就好了，时间复杂度 $O(n^2)$

## $\mathrm{Code}$

```cpp
#include <bits/stdc++.h>
#define For(i,a,b) for ( int i=(a);i<=(b);i++ )
#define Dow(i,b,a) for ( int i=(b);i>=(a);i-- )
#define GO(i,x) for ( int i=head[x];i;i=e[i].nex )
#define mem(x,s) memset(x,s,sizeof(x))
#define cpy(x,s) memcpy(x,s,sizeof(x))
#define YES return puts("YES"),0
#define NO return puts("NO"),0
#define GG return puts("-1"),0
#define pb push_back
#define int long long 
using namespace std;

struct IO
{
	#define MAXSIZE (1 << 20)
	#define isdigit(x) (x >= '0' && x <= '9')
  	char buf[MAXSIZE],*p1,*p2;
  	char pbuf[MAXSIZE],*pp;
  	IO():p1(buf),p2(buf),pp(pbuf){}
  	inline char gc() {
    	return getchar();
    	if (p1==p2) p2=(p1=buf)+fread(buf,1,MAXSIZE,stdin);
    	return p1==p2?' ':*p1++;
  	}
	inline bool blank(char ch) {return ch==' '||ch =='\n'||ch == '\r'||ch == '\t';}
  	template <class T>
  	inline void read(T &x)
	{
	    register double tmp=1;register bool sign=0; x=0;
	    register char ch=gc();
	    for (;!isdigit(ch);ch=gc()) if(ch=='-') sign=1;
	    for (;isdigit(ch);ch=gc()) x=x*10+(ch-'0');
	    if (ch=='.') for (ch=gc();isdigit(ch);ch=gc()) tmp/=10.0,x+=tmp*(ch-'0');
	    if (sign) x=-x;
  	}
  	inline void read(char *s)
	{
    	register char ch=gc();
		for (;blank(ch);ch=gc());
		for (;!blank(ch);ch=gc()) *s++=ch;
    	*s=0;
  	}
  	inline void read(char &c) {for(c=gc();blank(c);c=gc());}
  	template<class t> inline void write(t x){
		if(x<0) putchar('-'),write(-x);
		else{if(x>9) write(x/10);putchar('0'+x%10);}
	}
} io;

const int mod=1e9+7;
const int mo=998244353;
const int N=5005;

int n,m,a[N],b[N],f[2][N],g[2][N],ans;

signed main()
{
	io.read(n);
	For(i,1,n) io.read(b[i]),a[i]=b[i];
	sort(b+1,b+n+1);
	For(i,1,n) f[0][i]=0,g[0][i]=0;
	For(i,1,n) 
	{
		mem(f[i&1],88);
		mem(g[i&1],88);
		For(j,1,n) 
			f[i&1][j]=min(f[i&1][j],g[(i-1)&1][j]+abs(a[i]-b[j]));
		For(j,1,n) g[i&1][j]=min(g[i&1][j-1],f[i&1][j]);
	}
	ans=1e14;
	For(i,1,n) ans=min(ans,f[n&1][i]);
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：Star_Cried (赞：4)

## CF13C Sequence

### 题意

给定一个序列，每次操作可以把某个数+1或-1。要求把序列变成非降数列。而且要求修改后的数列只能出现修改前的数。

### 思路

绝妙的思路！

从前往后计算，考虑对于当前值和前面的最大值，若当前值不小于前面的最大值，不操作；否则**将最大值修改为最小值**（不太准确，下面有解释），并统计答案。注意这里将最大值修改为最小值的含义。因为对于一个前面的最大值和后面的较小值，将他们改为不降序列并且将两个数改为两个数之间的数的代价是固定的（之所以要改为两个数之间的数是因为，往大改不优，而且后面会考虑往小改的情况），所以我们可以直接加上两个数间的差值。

也就是说，如果我们用优先队列维护的话，每次插入的值，即将最大值修改后插入的值其实是**它最低能到的位置**。不用考虑修改后可能更前面的变大的情况，因为会发现代价是相同的，所以我们统计的答案无论如何是正确的。

然后会发现是符合所有数修改为修改前出现的数的条件的，~~并且发现这样好像是最优的~~

### 实现

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cctype>
#include<cstring>
#include<cmath>
#include<queue>
using namespace std;
inline int read(){
	int w=0,x=0;char c=getchar();
	while(!isdigit(c))w|=c=='-',c=getchar();
	while(isdigit(c))x=x*10+(c^48),c=getchar();
	return w?-x:x;
}
namespace star
{
	const int maxn=5e5+10;
	int n;
	long long ans;
	priority_queue<int> q;
	inline void work(){
		n=read();
		while(n--){
			int x=read();
			q.push(x);
			if(q.top()>x) ans+=q.top()-x,q.pop(),q.push(x);
		}
		printf("%lld\n",ans);
	}
}
signed main(){
	star::work();
	return 0;
}
```

### 附

四倍经验：

* [P4597](https://www.luogu.com.cn/problem/P4597)
* [CF713C](https://www.luogu.com.cn/problem/CF713C)
* [P2893](https://www.luogu.com.cn/problem/P2893)

---

## 作者：Bezime (赞：3)

题目要求很明确。

先给个样例。

单调处理前：
```
7
1 4 4 7 9 7 15
```
单调处理后：
```
7
1 3 2 4 5 3 9
```
我们按递推顺序想想，

下标为 $1$ 时，符合条件，不做处理。序列为：$\{1\}$。

下标为 $2$ 时，符合条件，不做处理。序列为：$\{1,3\}$。

下标为 $3$ 时，不符合，将前面的 $3$ 改为 $2$。序列为：$\{1,2,2\}$。

下标为 $4$ 时，符合条件，不做处理。序列为：$\{1,2,2,4\}$。

下标为 $5$ 时，符合条件，不做处理。序列为：$\{1,2,2,4,5\}$。

下标为 $6$ 时，不符合，将前面的 $5$ 改为 $3$。序列为：$\{1,2,2,4,3,3\}$。

下标为 $7$ 时，符合条件，不做处理。序列为：$\{1,2,2,4,3,3,9\}$。

为什么第六步可行呢？我们在做处理时肯定是将前面最大数变为这个数（即最适配情况）（$5,3$ 变 $3,3$），而这个的操作数，与将前面最大数与这个数折中变化的操作数相同（$5,3$ 变 $4,4$），所以这里的 $\{3,3\}$ 等效于  $\{4,4\}$， $\{5,5\}$。

而我们每次只找前面最大值，把我们更改的数值当作动态平衡（可小可大），这种动态平衡与单调不减是等效的（这里要好好理解），因为这并不影响我们找到的前面最大值与操作数。

当当前的数小于前面最大值，且这个最大值原本处于动态平衡，则这个数的值就定下来了，每次将前面最大数变为这个数。

当当前的数大于或等于前面最大值，符合条件，不更改值。

所以我们只需维护前面的更改数值后的值的最大值就行了。

附上代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define mxm 200002
#define mxn 100002
using namespace std;
ll n,mx;
priority_queue<ll>qmx;
inline void rd(ll &x){x=0;short f=1;char c=getchar();while((c<'0'||c>'9')&&c!='-') c=getchar();if(c=='-') f=-1,c=getchar();while(c>='0'&&c<='9') x=x*10+c-'0',c=getchar();x*=f;}
inline void pt(ll x){if(x<0) putchar('-'),x=-x;if(x>9) pt(x/10);putchar(x%10+'0');}
int main(){
	rd(n);
	for(ll i=1,x;i<=n;i++){
		rd(x);
		qmx.push(x);//将x放入优先队列
		mx+=qmx.top()-x;//记录操作次数
		qmx.pop();//将最大值弹出
		qmx.push(x);//改为x
	}//想想当x大于或等于时，是否没改值
	pt(mx);//输出操作次数
}
```

---

## 作者：叶枫 (赞：1)

$\texttt{离散化+滚动数组}$

### $Idea$
$dp[i][j]$表示前i个数以$a[j]$为结尾的满足要求的最少的操作，可是题目给的最大数是$10^9$，二维数组的$j$元素不可能开这么大，所以需要离散化一下，改成前i个数以第$j$个数为结尾的满足要求的最少的操作。

$dp[i][j]=min(dp[i][j],\text{第i-1个位置前j个数的最小操作}+abs(b[j]-a[i]))$ $b$数组是原来输入的$a$数组排好序且离散化之后的数组

因为$b$数组是从小到大排好序的，所以在第$i$个位置时第$j$个数肯定比$i-1$个位置的前j个数要大。

最后$dp[5000][5000]$也不能存下，那么这个二维数组就要滚一下了。

### $Code$
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<string>
#include<queue>
#define ll long long
#define maxn 100001
#define mod 998244353
#define eps 1e-6
#define pi acos(-1.0)
#define de(x) ((x)*(x))
using namespace std; 
inline int read(){
    int x=0,f=1; char ch=getchar();
    while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch)) {x=x*10+ch-48;ch=getchar();}
    return x*f;
}
const ll inf=1ll<<62;
ll dp[2][5007],a[5007],b[5007];
int main(){
	ll n=read();
    for(ll i=1;i<=n;i++){
    	a[i]=read();
        b[i]=a[i];
    }
    sort(b+1,b+n+1);
    ll tot=unique(b+1,b+n+1)-b-1;//离散化
    dp[1][1]=inf;
    for(ll i=1;i<=tot;i++){
        dp[1&1][i]=fabs(b[i]-a[1]);
        dp[2&1][i]=inf;
    }
    for(ll i=2;i<=n;i++){
    	ll minn=inf;
        for(ll j=1;j<=tot;j++){
            minn=min(minn,dp[(i-1)&1][j]);//取上一个位置中前j颗不同高度的树中花费最小
            dp[i&1][j]=min(dp[i&1][j],minn+abs(b[j]-a[i]));//当前位置等于上一个位置中前j颗树花费最小+这个位置是第j颗树的花费
        }
    	for(ll j=1;j<=tot;j++) dp[(i+1)&1][j]=inf;
    }
	ll ans=inf;
    for(ll i=1;i<=tot;i++) ans=min(ans,dp[n&1][i]);//取最后一个位置是第j颗树是花费最小
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：一只书虫仔 (赞：0)

#### Description

> 给定一个长为 $n$ 的序列 $a_i$，把一个数从 $p$ 修改为 $q$ 需要用 $|p-q|$ 的代价，求将其修改为一个不下降=序列的最小代价。

#### Solution

比如说对于这三个数：$3\ 2\ 5$，将其修改为满足要求的序列，很明显要改变 $2$ 的值，然而要求变动最小，所以要让其改变为 $3$，即等于前面那一个数。如果中间的数是 $6$，将其改变为 $5$，即等于后面那一个数。不难发现，改为原序列中的一个数代价会最小。

因此，先将序列进行离散化，假设离散化后有 $w$ 个数 $c_i$。

考虑 dp，定义 $dp_{i,j}$ 为将序列的第 $i$ 个数改为 $c_j$ 使得 $a_{[1,i]}$ 为满足要求的序列需要的最少代价，很显然，对于所有 $k \in [1,j]$，对 $dp_{i-1,k}$ 取个 $\min$ 并加上 $|a_i-c_j|$ 即可，答案即为 $\min\limits_{i=1}^n dp_{i,j}$，形式化的转移方程：

$$dp_{i,j}=\min\limits_{k=1}^j dp_{i-1,k}+|a_i-c_j|$$

直接枚举 $k$ 是 $\mathcal O(n^3)$ 的，我们对于区间 $\min$，可以使用单调队列！！！（大雾）不知道是不是可以使用单调队列，但是太麻烦了，既然这个 $\min$ 与 $i$ 及以后的都没有关系，不如直接在算 $i-1$ 的时候就将其预处理。

问题是这题空间有丶卡，所以需要滚动数组。

---

## 作者：_Clown_ (赞：0)

# C.Sequence
这道题目我们可以考虑直接上 STL。

我们一个数一个数地放进一个大根堆(优先队列)，

其实就是算到当前数时，

取前面最大的数出来。

假如现在这个数比前面最大数大或相等就没事，

反之我们则需要考虑如何改为不降。

我们肯定是将大的往小移，将小的往大移，

那么花费一定是 $|a-b|$。

为了不影响先前的答案，

当然都是移到同一基准，

即是先前的最大数。

代码不难写出。
```cpp
#include<bits/stdc++.h>
#define BetterIO ios::sync_with_stdio(false)
using namespace std;
long long Total;
priority_queue< long long >Queue;
int main(void)
{
	BetterIO;
	register long long i;cin>>Total;
	register long long Ans(0);
	for(i=1;i<=Total;i++)
	{
		register long long Now;cin>>Now;
		Queue.push(Now);
		if(Queue.top()>Now)
		{
			Ans+=Queue.top()-Now;
			Queue.pop();
			Queue.push(Now);
		}
	}
	cout<<Ans<<endl;
	return 0;
}
```

---

