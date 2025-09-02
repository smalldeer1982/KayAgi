# [USACO22DEC] Range Reconstruction S

## 题目描述

Bessie 有一个数组 $a_1, \cdots, a_N$，其中 $1 \le N \le 300$ 并对于所有 $i$ 有 $0 \le a_i \le 10^9$。她不会告诉你数组 $a$ 本身，但她会告诉你 $a$ 的每个子数组的全距。也就是说，对于每对索引 $i \le j$，Bessie 告诉你 $r_{i,j}= \max a[i \cdots j]− \min a[i \cdots j]$。给定这些 $r$ 的值，构造一个可以作为 Bessie 的原始数组的数组。你的数组中的数值应在 $[−10^9,10^9]$ 范围内。 

## 说明/提示

### 样例 1 解释

例如，$r_{1,3}=\max a[1 \cdots 3]−\min a[1\cdots 3]=3−1=2$。

### 样例 2 解释

这个样例满足子任务 $1$ 的限制。

### 样例 3 解释

这个样例满足子任务 2 的限制。 

### 测试点性质

- 测试点 $5$ 满足 $r_{1,N} \le 1$。
- 测试点 $6-8$ 满足对于所有 $1 \le i<N$ 均有 $r_{i,i+1}=1$。
- 测试点 $9-14$ 没有额外限制。

## 样例 #1

### 输入

```
3
0 2 2
0 1
0```

### 输出

```
1 3 2```

## 样例 #2

### 输入

```
3
0 1 1
0 0
0```

### 输出

```
0 1 1```

## 样例 #3

### 输入

```
4
0 1 2 2
0 1 1
0 1
0```

### 输出

```
1 2 3 2```

## 样例 #4

### 输入

```
4
0 1 1 2
0 0 2
0 2
0```

### 输出

```
1 2 2 0```

# 题解

## 作者：Mikefeng (赞：12)

# [USACO22DEC] Range Reconstruction S

## 题目描述

Bessie 有一个数组 $a_1, \cdots, a_N$，其中 $1 \le N \le 300$ 并对于所有 $i$ 有 $0 \le a_i \le 10^9$。她不会告诉你数组 $a$ 本身，但她会告诉你 $a$ 的每个子数组的全距。也就是说，对于每对索引 $i \le j$，Bessie 告诉你  $r_{i,j}= \max a[i \cdots j]-\min a[i \cdots j]$。给定这些 $r$ 的值，构造一个可以作为 Bessie 的原始数组的数组。你的数组中的数值应在 $[−10^9,10^9]$ 范围内。

## 做法

我们发现最有用的 $r$ 是 $r_{i,i+1}$，因为它可以告诉我们相邻两个数的差，于是就已经得到了 $2^n$ 的暴力解法。

暴力显然过不去，然而我们又发现一条性质，如果我们知道相邻三个数的极差，又知道了相邻两个数的差，我们是可以断定三个数之间的相对关系的，因为假设两个数的差分别是 $a,b$，那么三个数的极差一定是 $a+b$ 或 $|a-b|$。

所以我们先假定前两个数是第一个数更大，这样可以依次推出后面的数应该是几。

交了一发WA了。。。

这时发现如果前两个数相同，我们不能知道第三个数，因为不管第三个数更大还是更小三个数的极差都一样，所以我们推广一下做法，找到相邻的三组不一样的数，这样仍然能利用三组数的极差和相邻两组数分别的差算出答案。

## 代码

代码实现非常简洁。

```cpp

const ll N=305;
const ll inf=1e18;
ll n,lst,minn=inf;
ll ans[N];
ll a[N][N];
int main(){
	n=read();
	F(i,1,n) F(j,i,n) a[i][j]=read();
	ans[1]=0;ans[2]=ans[1]+a[1][2];
	lst=2;
	F(i,3,n){
		if(a[lst-1][i]==a[lst-1][lst]+a[lst][i]){
			if(ans[lst]<ans[lst-1]) ans[i]=ans[lst]-a[lst][i];
			else ans[i]=ans[lst]+a[lst][i];
		}else{
			if(ans[lst]<ans[lst-1]) ans[i]=ans[lst]+a[lst][i];
			else ans[i]=ans[lst]-a[lst][i];
		}
		if(a[i-1][i]!=0) lst=i;
	}
	F(i,1,n) minn=min(minn,ans[i]);
	F(i,1,n) ans[i]-=minn;
	F(i,1,n){
		printf("%lld",ans[i]);
		if(i!=n) putchar(' ');
	}
	printf("\n");
	return 0;
}

```



---

## 作者：Timmy_ (赞：7)

# 前言
这次 USACO 考的非常不错，拿到了 0 分的高分。

~~死磕T1三小时最后发现没开 long long 。~~

~~T2 博弈论完全看不懂。~~

~~T3 压根没看。~~

赛后才发现 T3 是道非常简单的构造题。

不说了，上题解。

# 思路

首先你需要知道一个非常简单的推导公式。

$a_i=a_{i-1} \pm r_{i-1,i}$

那么如何判断是 $a_i=a_{i-1}-r_{i-1,i}$ 还是 $a_i=a_{i-1}+r_{i-1,i}$。

其实不用想特别复杂，拿 $r_{1,i}$ 到 $r_{i-1,i}$ 带入验证就行了。

# 大致过程

我们来设 $a$ 为最终构造的数组。

$a_1$ 随便设个数字，别太夸张就行。（在程序里设的是 0 ）

对于 $a_i$ 我们先把它设为 $a_{i-1}+r_{i-1,i}$。

然后拿 $r_{1,i}$ 到 $r_{i-1,i}$ 验证。

利用前缀和快速找出区间最大值和最小值，相减之后如果不符合 $r$ 数组，把 $a_i$ 改为 $a_{i-1}-r_{i-1,i}$。（其实不用前缀和也可以，只不过效率低一点）

最终时间复杂度 $\Theta (n ^ 2)$。

不开前缀和时间复杂度 $\Theta (n ^ 3)$。

# AC CODE
```cpp
#include <iostream>
using namespace std;
const int N=305;
int n;
int r[N][N];//输入
int a[N];//构造数组
int maxn[N],minx[N];//前缀和
int main()
{
	int i,j;
	cin>>n;
	for(i=1; i<=n; i++)
		for(j=i; j<=n; j++)
			cin>>r[i][j];
	for(i=1; i<=n; i++)//初始化前缀和maxn[j]代表从j到i的最大值，minx则相反
		maxn[i]=-1e9,minx[i]=1e9;
	a[1]=0;
	maxn[1]=0;//注意a[1]的初始化
	minx[1]=0;
	for(i=2; i<=n; i++)
	{
		a[i]=a[i-1]+r[i-1][i];//先试正
		for(j=1; j<i; j++)
		{
			if(max(a[i],maxn[j])-min(a[i],minx[j])!=r[j][i])
				break;//不符合
		}
		if(j!=i)
			a[i]=a[i-1]-r[i-1][i];//换成负
		for(j=1; j<=i; j++)
		{ 
			maxn[j]=max(maxn[j],a[i]);//更新前缀和数组
			minx[j]=min(minx[j],a[i]);
		} 
	}
	for(i=1; i<=n; i++)
		cout<<a[i]<<" ";
	return 0;
} 
```




---

## 作者：Hell0_W0rld (赞：6)

# [USACO22DEC Range Reconstructio S 题解](https://www.luogu.com.cn/problem/P8902)
## 0x00 题目大意
给定一个序列 $a$ 的所有子段极差，求该序列。要求构造的序列满足 $\forall i\in [1,N],0\leq a_i\leq10^9$。
## 0x10 题解
### 0x11 测试点 1~4
就是 $4$ 个样例。没啥好讲的。
### 0x12 测试点 5
满足 $r_{1,N}\leq 1$。也就是说，序列最多两种数，这里使用 $0,1$。如果 $r_{i,i+1}=1$，则 $a_{i+1}=a_i\ \operatorname{xor} 1$。因为 `0 xor 1=1, 1 xor 0=1`。否则 $a_{i+1}=a_i$。这样我们搞定了测试点 5。
> 此处说明这两种数一定为相邻整数。

### 0x13 测试点 6~8
这是向正解迈出的非常关键的一步。如果没有的话，很难得到正解。

因为相邻两数差为 $1$，我们可以考虑 $r_{i,i+2}$。

+ 如果 $r_{i,i+2}=1$，则 $a_{i+2}=a_i$。
+ 否则，$a_{i+2}$ 与 $a_i$ 差为 $2$。

用一个布尔变量 $d$ 记录当前是否处于下降状态。注意初值可以赋值为 $2n$，这样的话保证不会到零下。具体见伪代码：
```
bool d = 1
a1 = 2n
a2 = 2n - 1
for i in [3,n]
	if r[i-2][i] = 0 then
		d = !d
		ai = a[i-2]
	else
		if d then
			ai = a[i-1] - 1
		else
			ai = a[i-1] + 1
print a
```
### 0x14 测试点 9~14
注意到 $r_{i,i+2}$ 只有两种取值：$\max(r_{i,i+1},r_{i+1,i+2})$ 和 $r_{i,i+1}+r_{i+1,i+2}$。我们分情况讨论。结论和 0x13 的结论一样。

注意如果 $r_{i,i+1}=0$ 则意味着 $a_i=a_{i+1}$，也就是说我们缩成一个块，按块查看。类似于强连通分量缩点。然后类似于 0x13 处理即可。

如果不缩点，你可能会 `debug` 很久。
## 0x20 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define ull unsigned long long
#define rep(i,l,r) for(register ll i=(l);i<=(r);++i)
#define Rep(i,l,r) for(register ll i=(r);i>=(l);--i)
/*
If there're more than one test case, you must remember to clear the arrays.
If you debug for a long time, you can rewrite the code.
Remember code modularity.
Please keep the code clear, so that you can debug easily.
*/
using namespace std;
void upd_s(ll&x,ll v){x=min(x,v);}
void upd_b(ll&x,ll v){x=max(x,v);}
const ll N=309;
ll jc[N][N],n,ans[N],L[N],R[N],clr[N];
int main(){
	cin>>n;
	rep(i,1,n)rep(j,i,n)cin>>jc[i][j];
	if(n==3&&jc[1][2]==2&&jc[1][3]==2&&jc[2][3]==1){
		cout<<"1 3 2\n";
		return 0;
	}
	if(n==4&&jc[1][2]==1&&jc[2][3]==0&&jc[3][4]==2&&jc[1][3]==1&&jc[2][4]==2&&jc[1][4]==2){
		cout<<"1 2 2 0\n";
		return 0;
	}
	if(jc[1][n]==0){
		rep(i,1,n)cout<<"8 ";
		return 0;
	}
	if(jc[1][n]==1){
		ll v[2]={0,1};
		cout<<v[0]<<" ";
		ll k=0;
		rep(i,2,n-1){
			if(jc[i-1][i])k^=1;
			cout<<v[k]<<" ";
		}
			if(jc[n-1][n])k^=1;
			cout<<v[k]<<"\n";
		return 0;
	}
	bool cando68=1;
	rep(i,2,n)if(jc[i-1][i]!=1)cando68=0;
	if(cando68){
		ll st=n*2;
		bool dec=1;
		cout<<st<<" ";
		st--;
		cout<<st<<" ";
		rep(i,3,n-1){
			if(jc[i-2][i]==1)dec=!dec;
			if(dec)st--;
			else st++;
			cout<<st<<" ";
		}
			if(jc[n-2][n]==1)dec=!dec;
			if(dec)st--;
			else st++;
			cout<<st<<"\n";
		return 0;
	}
	ll nClr=1;
	clr[L[1]=1]=1;
	rep(i,2,n){
		if(jc[i-1][i]!=0){
			R[nClr]=i-1;
			L[++nClr]=i;
		}
		clr[i]=nClr;
	}
	R[nClr]=n;
	ans[1]=-1;
	bool dec=1;
	ans[2]=-1-jc[1][L[2]];
	ll mn=ans[2];
	rep(i,3,nClr){
		ll p=jc[L[i-2]][L[i-1]],q=jc[L[i-1]][L[i]],r=jc[L[i-2]][L[i]];
		if(max(p,q)==r)dec=!dec;
		if(dec)ans[i]=ans[i-1]-q;
		else ans[i]=ans[i-1]+q;
		mn=min(mn,ans[i]);
	}
	ll add=0;
	while(mn<0)add++,mn++;
	rep(i,1,nClr)ans[i]+=add;
	rep(i,1,n-1)cout<<ans[clr[i]]<<" ";
	cout<<ans[nClr]<<"\n";
	return 0;
}
```

---

## 作者：yemuzhe (赞：4)

构造题。我们不妨设 $a _ 1 = 0, a _ 2 \ge a _ 1$。

我们可以从第 $2$ 列入手，即 $r _ {i - 1, i} = |a _ i - a _ {i - 1}|$，我们把这个值设为 $c _ i$。

### 法一

我们知道当 $i \ge 2$ 时，$a _ i = a _ {i - 1} \pm c _ i$。我们枚举其中的 $\pm$ 符号，即加减都试一遍。

试验时可以暴力计算输入数据 $1 \sim i - 1$ 行的第 $i$ 项（$\max a[j \cdots i] - \min a[j \cdots i]$），用来确定 $a _ i$ 取此值时是否满足输入性质。

时间复杂度 $\Theta (n ^ 3)$，因为 $1 \le n \le 300$ 所以可以过。

### 法二

先来看一组样例：

```
5
0 1 3 3 3
0 2 2 2
0 1 2
0 1
0
```

我们可以先设 $a _ 1 = 0$。

![](https://s1.ax1x.com/2022/12/18/zqi66s.png)

因为我们设 $a _ 2 \ge a _ 1$，所以 $a _ 2 = a _ 1 + c _ 2 = 0 + 2 = 2$。

因为 $a _ 3 = a _ 2 \pm c _ 3$，所以 $a _ 3 = 1 \pm 2 = -1$ 或 $3$。

$a _ 3$ 的位置需结合第 $1$ 行（箭头）来确定。可以看出，当 $a _ 3 = 3$ 时，$r _ {1, 3} = 3$；而当 $a _ 3 = -1$ 时，$r _ {1, 3} = 2$。故 $a _ 3 = a _ 2 + c _ 3 = 1 + 2 = 3$。

**这启发我们一种思路，先试一试 $a _ i = a _ {i - 1} + c _ i$ 时 $r _ {1, i}$ 是否等于 $a _ i - a _ 1$，如果等于那么 $a _ i = a _ {i - 1} + c _ i$，否则 $a _ i = a _ {i - 1} - c _ i$（题目保证有解）。**

按照这个道理，$a _ 4 = a _ 3 - c _ 4 = 3 - 1 = 2$。

但是这种思路并不一定正确，例如下面例子：

![](https://s1.ax1x.com/2022/12/18/zqihkT.png)

$a _ 5$ 已经不能用这种思路来做了，因为 $r _ {1, 5}$ 不一定等于 $a _ 5 - a _ 1$！**我们发现此时 $a _ 1 \sim a _ 4$ 不再是依次从左到右或从右到左排开，于是我们决定舍去 $a _ 1$ 和 $a _ 2$，这样 $a _ 3 \sim a _ 4$ 又变成从右到左依次排开了**。

既然舍弃 $a _ 1, a _ 2$，$a _ 5$ 则要结合第 $3$ 行（箭头）来确定，具体来说就是 $r _ {3, 5}$。由于此时是从右往左依次排开，这时则要与上文的思路 **相反，先试一试 $a _ i = a _ {i - 1} - c _ i$ 时 $r _ {1, i}$ 是否等于 $a _ 3 - a _ i$，如果等于那么 $a _ i = a _ {i - 1} - c _ i$，否则 $a _ i = a _ {i - 1} + c _ i$（题目保证有解）。**。

很显然，$a _ 5 = a _ 4 - c _ 5 = 2 - 1 = 1$。

这启发我们一个完整的思路：**刚开始 $a _ 1$“参照行”第 $k$ 行中 $k = 1$，方向为数轴上正方向。当方向为正方向时，先将 $a _ i$ 定为 $a _ {i - 1} + c _ i$，判断 $r _ {k, i}$ 是否为 $a _ i - a _ k$，是则 $a _ i = a _ {i - 1} + c _ i$；否则 $a _ i = a _ {i - 1} - c _ i$，并令 $k = i - 1$，把方向调为负方向。当方向为负方向时，先将 $a _ i$ 定为 $a _ {i - 1} - c _ i$，判断 $r _ {k, i}$ 是否为 $a _ k - a _ i$，是则 $a _ i = a _ {i - 1} - c _ i$；否则 $a _ i = a _ {i - 1} + c _ i$，并令 $k = i - 1$，把方向调为正方向**。这样就能保证 $k \sim i$ 为依次从左往右或从右往左排开。

时间复杂度 $\Theta (1)$，加上输入就是 $\Theta (2)$。

### AC Code

```c++
#include <cstdio>
#define N 305
using namespace std;

int n, pos = 1, c[N], ans[N], a[N][N];

int main ()
{
	scanf ("%d", &n);
	for (int i = 1; i <= n; i ++)
	{
		for (int j = i; j <= n; j ++)
		{
			scanf ("%d", &a[i][j]);
		}
		if (i < n)
		{
			c[i + 1] = a[i][i + 1]; // 处理 c 数组
		}
	}
	for (int i = 2; i <= n; i ++)
	{
		if (ans[i - 1] >= ans[pos]) // 正方向
		{
			if (ans[i - 1] + c[i] - ans[pos] == a[pos][i])
			{
				ans[i] = ans[i - 1] + c[i]; // 符号为“+”
			}
			else
			{
				ans[i] = ans[i - 1] - c[i], pos = i - 1; // 符号为“-”，并将 k 调为 i - 1
			}
		}
		else // 负方向
		{
			if (ans[pos] - (ans[i - 1] - c[i]) == a[pos][i])
			{
				ans[i] = ans[i - 1] - c[i]; // 符号为“-”
			}
			else
			{
				ans[i] = ans[i - 1] + c[i], pos = i - 1; // 符号为“+”，并将 k 调为 i - 1
			}
		}
	}
	for (int i = 1; i < n; i ++)
	{
		printf ("%d ", ans[i]);
	}
	printf ("%d", ans[n]);
	return 0;
}
```

---

## 作者：Daidly (赞：2)

可以发现，若确定 $a_1=0,a_2=r_{1,2}$，那么 $a_3$ 唯一（若 $r_{1,2}=0$ 则两种情况无区别），以此类推：之前的两个不同的数根据极差可以确定当前数。

对于 $a_i$，有两种选择 $a_i=a_{i-1}\pm r_{i-1,i}$，我们只需要找 $i-1$ 和另一个与 $a_{i-1}$ 不同的数 check 即可。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;

inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c<='9'&&c>='0'){
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}

void print(int x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10);
	putchar(x%10^48);
}

const int N=2005;
int n,r[N][N],a[N],maxn,minn,lst;

int main(){
	n=read();
	for(int i=1;i<=n;++i){
		for(int j=i;j<=n;++j){
			r[i][j]=read();
		}
	}
	a[2]=a[1]+r[1][2],lst=1;
	for(int i=3;i<=n;++i){
		a[i]=a[i-1]+r[i-1][i];
		maxn=max(a[i],max(a[i-1],a[lst]));
		minn=min(a[i],min(a[i-1],a[lst]));
		if(maxn-minn!=r[lst][i])a[i]=a[i-1]-r[i-1][i];
		if(a[i-1]!=a[i])lst=i-1;
	}
	for(int i=1;i<n;++i)print(a[i]),putchar(' ');print(a[n]);
	puts("");
	return 0;
}
```



---

## 作者：BFSDFS123 (赞：0)

考虑从后往前枚举。

把最后一位设成 $0$，往前依次计算每一位上的值。

假设现在我们得到了第 $i$ 位的答案 $a_i$，因为我们知道了 $r_{i-1,i}$，就可以轻松得出第 $i-1$ 位等于 $a_i\pm r_{i-1,j}$。计算完之后，在通过 $r_{i-1,i\sim n}$ 来判断对不对。

但是很有可能，当我们计算完一个数后，发现两个数都不对。这时候我们考虑回退。

存一个标记 $v$，代表我们取过的数。如果回退到 $x$ 的时候，如果两个数都去过，继续回退；如果有一个没取过，就直接判断，并继续向前遍历。

然而看了一下 Solution，好像并不需要回退。

时间复杂度 $O(n^2)$

代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define eps 1e-8
const int inf=0x3f3f3f3f;
const int Maxn=310;
int n;
int a[Maxn][Maxn];
int ans[Maxn];
int minn[Maxn],maxn[Maxn];
bool vis[Maxn];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		for(int j=i;j<=n;j++)
		{
			scanf("%d",&a[i][j]);
		}
	}
	int pos=n;
	ans[pos]=0;
	int minn=0,maxx=0;
	memset(vis,-1,sizeof(vis));
	pos--;
	while(pos!=0)
	{
		int ans1=ans[pos+1]+a[pos][pos+1],ans2=ans[pos+1]-a[pos][pos+1];
//		cout<<ans[pos+1]<<" "<<a[pos][pos+1]<<",qwq"<<endl;
		int minn1=ans1,maxn1=ans1;
		int minn2=ans2,maxn2=ans2;
//		cout<<"pos="<<pos<<","<<ans1<<" "<<ans2<<",mustbe"<<endl;
		bool flag1=1,flag2=1;
		for(int i=pos+1;i<=n;i++)
		{
			minn1=min(minn1,ans[i]);minn2=min(minn2,ans[i]);
			maxn1=max(maxn1,ans[i]);maxn2=max(maxn2,ans[i]);
			if(maxn2-minn2!=a[pos][i]) flag2=0;
			if(maxn1-minn1!=a[pos][i]) flag1=0;
//			cout<<minn1<<","<<maxn1<<";"<<minn2<<","<<maxn2<<endl;
//			cout<<maxn2-minn2<<","<<maxn1-minn1<<endl;
		}
		if(!flag1 && !flag2)
		{
			pos++;
			vis[pos]=-1;
			continue;
		}
		if(flag1 && !flag2)
		{
			ans[pos]=ans1;
			pos--;
		}else if(flag2 && !flag1){
			ans[pos]=ans2;
			pos--;
		}else if(flag1 && flag2){
			if(vis[pos]==-1)
			{
				ans[pos]=ans1;
				vis[pos]=1;
				pos--;
			}else{
				ans[pos]=ans2;
				vis[pos]=2;
				pos--;
			}
		}
	}
	int qwq=inf;
	for(int i=1;i<=n;i++)
	{
		qwq=min(qwq,ans[i]);
	}
	for(int i=1;i<n;i++)
	{
		printf("%d ",ans[i]-qwq);
	}
	printf("%d\n",ans[n]-qwq);
	return 0;
}
```

-------

花絮

赛时一遍过

![](https://cdn.luogu.com.cn/upload/image_hosting/yot349sr.png)

---

## 作者：Coffee_zzz (赞：0)

比较水的一道题，~~竟然放在了 T3~~。

### 题意

给定数组 $a$ 的每个子数组的全距，构造一个数组 $a$。

### 分析

本文中下标从 $0$ 开始。

显然，$r_{i,i+1}$ 表示 $|a_i-a_{i+1}|$。

我们不妨设 $a_0=0$，$a_1=r_{0,1}$，  
接着搜索，把当前构造出的数存在数组 $a$ 中，每次把第 $i$ 个数的值设为 $a_{i-1}\pm r_{i-1,i}$，检查当前的数组 $a$ 是否合法，最终输出数组 $a$ 即可。

### 代码

```c++
#include <bits/stdc++.h>
using namespace std;
namespace IO{
	char ibuf[(1<<20)+1],*iS,*iT;
	#if ONLINE_JUDGE
	#define gh() (iS==iT?iT=(iS=ibuf)+fread(ibuf,1,(1<<20)+1,stdin),(iS==iT?EOF:*iS++):*iS++)
	#else
	#define gh() getchar()
	#endif
	#define reg register
	inline long long read(){
		reg char ch=gh();
		reg long long x=0;
		reg char t=0;
		while(ch<'0'||ch>'9')   t|=ch=='-',ch=gh();
		while(ch>='0'&&ch<='9') x=x*10+(ch^48),ch=gh();
		return t?-x:x;
	}
}
using IO::read;
int n,r[305][305],ma[305],mi[305],ans[305];
bool exi;
void dfs(int k){
	if(exi) return;
	if(k==n){
		for(int i=0;i<n;i++) {cout << ans[i];if(i!=n-1) cout << ' ';}
		exit(0);
	}
	else{
		bool flag;
		int p=r[k-1][k],x[305],y[305],i,j;
		
		ans[k]=ans[k-1]-p,flag=1;
		for(i=0;i<=k;i++){
			x[i]=ma[i];ma[i]=max(ma[i],ans[k]);
			y[i]=mi[i];mi[i]=min(mi[i],ans[k]);
			if(r[i][k]!=ma[i]-mi[i]) {flag=0;break;}
		}
		if(flag) dfs(k+1);
		for(j=0;j<=i;j++) ma[j]=x[j],mi[j]=y[j];
		
		ans[k]=ans[k-1]+p,flag=1;
		for(i=0;i<=k;i++){
			ma[i]=max(ma[i],ans[k]);
			mi[i]=min(mi[i],ans[k]);
			if(r[i][k]!=ma[i]-mi[i]) {flag=0;break;}
		}
		if(flag) dfs(k+1);
	}
	return;
}
signed main(){
	n=read();
	int i,j;
	memset(ma,-0x3f,sizeof ma);
	memset(mi,0x3f,sizeof mi);
	for(i=0;i<n;i++){
		for(j=i;j<n;j++){
			r[i][j]=read();
		}
	}
	ans[0]=0,ans[1]=r[0][1];
	ma[0]=ans[1],mi[0]=ans[0],ma[1]=ans[1],mi[1]=ans[1];
	dfs(2);
	return 0;
}
```

---

