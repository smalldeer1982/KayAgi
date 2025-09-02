# Mortal Kombat Tower

## 题目描述

You and your friend are playing the game Mortal Kombat XI. You are trying to pass a challenge tower. There are $ n $ bosses in this tower, numbered from $ 1 $ to $ n $ . The type of the $ i $ -th boss is $ a_i $ . If the $ i $ -th boss is easy then its type is $ a_i = 0 $ , otherwise this boss is hard and its type is $ a_i = 1 $ .

During one session, either you or your friend can kill one or two bosses (neither you nor your friend can skip the session, so the minimum number of bosses killed during one session is at least one). After your friend session, your session begins, then again your friend session begins, your session begins, and so on. The first session is your friend's session.

Your friend needs to get good because he can't actually kill hard bosses. To kill them, he uses skip points. One skip point can be used to kill one hard boss.

Your task is to find the minimum number of skip points your friend needs to use so you and your friend kill all $ n $ bosses in the given order.

For example: suppose $ n = 8 $ , $ a = [1, 0, 1, 1, 0, 1, 1, 1] $ . Then the best course of action is the following:

- your friend kills two first bosses, using one skip point for the first boss;
- you kill the third and the fourth bosses;
- your friend kills the fifth boss;
- you kill the sixth and the seventh bosses;
- your friend kills the last boss, using one skip point, so the tower is completed using two skip points.

You have to answer $ t $ independent test cases.

## 样例 #1

### 输入

```
6
8
1 0 1 1 0 1 1 1
5
1 1 1 1 0
7
1 1 1 1 0 0 1
6
1 1 1 1 1 1
1
1
1
0```

### 输出

```
2
2
2
2
1
0```

# 题解

## 作者：TerryGong (赞：9)

## 0.放在前面

这一道题主流做法是 $\operatorname{DP}$，但是我太菜了 ~~，不会~~。老师上课给我们讲了~~一点也不~~复杂的 $\operatorname{DP}$ 作法，但是我发现了更神奇的东西。

假设这里输入的数组是 $w_i,i\in[1,n]$

## 1.$\operatorname{DP}$ 做法

### 1.0 状态设计

首先设计一下状态。显然第一维要记录目前打到第几个怪了，另一个不一样的是目前轮到你~~这个大佬~~还是你的~~菜鸡~~朋友，所以可以这样记：

> 令 $f[i][0/1]$ 表示怪物打完第 $i$ 个，轮到你打是 $0$（后手），轮到朋友打是 $1$（先手）时最优解。

### 1.1 可行性

前面打得怎么样，与后面没有关系。前后的答案可以简单相加，因此显然可以动态规划完成。

### 1.2 方程

- $f[i][0]=\min(f[i-1][1],f[i-2][1])$。

- 原因：对于你而言，无论是 $hard$ 还是 $easy$ 你都无代价消灭，又因为你可以打一个怪或者两个怪，因此可以直接找朋友打完的最小值。

- $f[i][1]=\min(f[i-1][0]+w[i],f[i-2][0]+w[i-1]+w[i])$。

- 原因：对于你的朋友而言，$\mathrm{ta}$ 打的怪都要考虑“跳关卡”`skip points`消耗，又因为朋友可以打一个怪或者两个怪，因此要找你打的最小值加上目前两个怪的代价。

可以将递推式简化：

$$f[i][j]=\min(f[i-1][!j]+j\times w[i],f[i-1][!j]+j\times(w[i-1]+w[i])),j\in \{0,1\},i\in [1,n]$$

接下来考虑数组越界的情况。

- 首先，由于这句话`The first session is your friend's session.`第二自然段最后一句话：你朋友~~虽然菜~~要先打。

- 对于 $i=0$ 的情况，不存在实际意义，但是由于你的朋友**先打**，所以**再往前一个回合**应该是**你**打才对。所以可以初始化 $f[0][0]=0$。观察方程式，在 $i=2$ 时只有 $f[0][0]$ 的访问，因此符合题意。

- 对于 $i=1$ 的情况，这个回合是你的朋友打的，只能 $f[1][1]=w[1]$。观察方程式，$f[2][0]$ 调用的是 $f[1][1]$，$f[2][1]$ 调用的是 $f[0][0]$ 和 $f[1][1]$，包括 $i=3$ 时没有涉及 $f[1][0]$ 的访问，**合理**。

初始化完成。`Initializing Accomplished.`（虽然我也不知道放在这有什么用）。

$$\colorbox{Aqua}{\color{red}{Code}}$$

```cpp
#include <cstdio>
#include <cstring>
using namespace std;
#define N 200010
int f[N][2],w[N];
inline bool isdigit(char x){return (x>='0'&&x<='9');}
inline int read(){
	int x=0,flag=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')flag=-1;c=getchar();}
	while(isdigit(c)){x=(x<<3)+(x<<1)+c-'0';c=getchar();}
	return flag*x;
}
inline int gmin(int x,int y){return x<y?x:y;}
int main(){
	int T;
	T=read();
	while(T--){
		memset(f,0x3f,sizeof f);int n=read();
		for(int i=1;i<=n;i++)w[i]=read();		
		f[0][0]=0;f[1][1]=w[1];
		for(int i=2;i<=n;i++)
        	for(int j=0;j<=1;j++)
        		f[i][j]=gmin(f[i-1][!j]+j*w[i],f[i-2][!j]+j*(w[i]+w[i-1]));
		printf("%d\n",gmin(f[n][1],f[n][0]));
	}
	return 0;
}
```

（码风奇怪，不喜勿喷）

### 2.Interesting Things

分析上面的动规式子（以及你的大胆猜想），有了这样的想法：能不能……？

我们考虑这样的情况：

- 为了让朋友尽量更少的花费`Skip point`，显然遇到 $1$ 我们要替他打了。那么我们想一下：
- - 如果遇到一个 $1$ ，那么我们一定能想办法让我们帮朋友扛一下。
- - 如果遇到这样的序列`0110`，那么我们打中间，朋友打两边，也就混过去了。
- - 如果遇到`111`那么只能给一点了。
- - 如果遇到遇到`1111`我们可以自己打 $2$ 个，给朋友 $1$ 个，我们再打 $1$ 个。
- - 如果遇到 $n$ 个，那么答案就是 $n\div 3$ 了，简单明了！
- - 显然第一个数字怎么也逃不掉，我们直接给它加进答案里好了。

于是就有了上面的代码。最后要加上 $cnt\div3$，因为有可能最后没有 $0$ 把 $1$ 卡出去。

结果是对的。成功 $\mathrm{A}$ 掉。

$$\colorbox{aqua}{\color{red}{Code}}$$


```cpp
#include <cstdio>
using namespace std;
int T,n,a,ans;
inline bool isdigit(char x){return (x>='0'&&x<='9');}
inline int read(){
	int x=0,flag=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')flag=-1;c=getchar();}
	while(isdigit(c)){x=(x<<3)+(x<<1)+c-'0';c=getchar();}
	return flag*x;
}
int main(){
	T=read();
	while(T--){
		n=read();ans=read();int cnt=0;
		for(int i=1;i<n;++i){
			a=read();
			if(a==1)++cnt;
			else{
				ans+=cnt/3;
				cnt=0;
			}
		}
		printf("%d\n",ans+cnt/3);
	}
	return 0;
}
```

---

## 作者：KSToki (赞：9)

# 题目大意
给定 $n$ 个数，你的朋友和你轮流操作，你的朋友先手，从头一次取出 $1$ 个或 $2$ 个数，求你的朋友取出 $1$ 的数量的最小值。
# 题目分析
贪心，让你取更多的 $1$。首先第一个数肯定是朋友取，之后每一段以 $1$ 开头的连续为 $1$ 的串，都能以你开头。所以我们只需统计除开头外所有连续的为 $1$ 串的长度，除以 $3$ 加入答案即可。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,a,ans;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		scanf("%d",&ans);
		int cnt=0;
		for(register int i=1;i<n;++i)
		{
			scanf("%d",&a);
			if(a==1)
				++cnt;
			else
			{
				ans+=cnt/3;
				cnt=0;
			}
		}
		printf("%d\n",ans+cnt/3);
	}
	return 0;
}
```


---

## 作者：Tenshi (赞：4)

## 分析
注意到这题要按照顺序来取 $1$ ，而且在取的过程中是没有**后效性**的，故考虑采取DP来解决。

$f[i][1]$ 表示取完前 $i$ 个数后，且**最后一次抽取者是先手**，先手所能取到 $1$ 最少的个数。

$f[i][0]$ 表示取完前 $i$ 个数后，且**最后一次抽取者是后手**，先手所能取到 $1$ 最少的个数。

从而得到状态转移方程：
$$f[i][1]=\min(f[i-1][0]+w[i],f[i-2][0]+w[i-1]+w[i])$$

$$f[i][0]=\min(f[i-1][1],f[i-2][1])$$

至此基本解决了问题，不过，这题的初始化值得注意。

当 $i=0$ 时，应当是**认定为轮到后手取**才符合题意，初始化为 $f[0][0]=0$ 。

当 $i=1$ 时，状态只能由 $f[1][1]$ 向后续情况转移，因而  $f[1][1]=w[1]$ 。

因为是求 $\min$ ，因此首先应该全部初始化为`INF`。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=2e5+5;
int f[N][2],w[N];

int main(){
	int T; cin>>T;
	while(T--){
		memset(f,0x3f,sizeof f); //初始化为INF
		int n; cin>>n;
		for(int i=1;i<=n;i++) cin>>w[i];
		
		f[0][0]=0; 
		f[1][1]=w[1];
		for(int i=2;i<=n;i++){
			f[i][1]=min(f[i-1][0]+w[i],f[i-2][0]+w[i-1]+w[i]);
			f[i][0]=min(f[i-1][1],f[i-2][1]);
		}
		
		cout<<min(f[n][1],f[n][0])<<endl;
	}
	return 0;
}
```

---

## 作者：I_am_AKed_by_NOI (赞：3)

## 题目大意

给定一个包含 $n$ 个数的数组，你的朋友和你轮流从开头一次取出 $1$ 或 $2$ 个数，你的朋友先手，最小化朋友拿到的 $1$ 的个数。

## 贪心解法

其实这题贪心即可解决，且代码极短。题解区的大佬都是用动态规划做的，是有讲贪心的，但可能并没有非常详细，我就来详细的写一篇贪心题解。

首先，假设你和朋友要取的是一段均为 $1$ 的数组，那么为了最小化朋友的拿到的 $1$ 的数量，应当你先手，且你必须每次都取走 $2$ 个数，而朋友每次取走 $1$ 个数，朋友最少会拿到 $\lfloor cnt \div 3 \rfloor$ 个 $1$。

数组中可以看做若干个都是 $1$ 的段和若干个都是 $0$ 的段，为了最小化朋友拿走 $1$ 的个数，你要保证每一个都是 $1$ 的段都是你先手。

其实，只要朋友开始游戏时拿走数组中第一个数，就可以保证每一个都是 $1$ 的段均为你先手。为什么，假设第 $i$ 个与第 $i+1$ 个都是 $1$ 的段中间有 $x$ 个元素，假如此时你要先手，如果 $x$ 是偶数，那么只要你和朋友每次都拿走一个数即可。如果 $x$ 为奇数，那么你先拿走 $2$ 个数，之后每一次你和朋友都拿走一个数即可。反之此时朋友要先手，原因是类似的。

所以，我们只需要找出每一个都为 $1$ 段，然后设它的长度为 $y$，将 $\lfloor y \div 3 \rfloor$ 累加即可。

## 代码

```
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int T,n,a[N],ans,cnt; //cnt 表示当前都是 1 的段的长度 
int main()
{
	scanf("%d",&T);
	for(int i=1;i<=T;i++)
	{
		scanf("%d",&n);
		scanf("%d",&a[1]); //朋友取走的第 1 个数 
		cnt=0,ans=0;
		for(int i=2;i<=n;i++)
		{
			scanf("%d",&a[i]);
			if(a[i]==1)
			{
				cnt++;  //如果是当前元素是1，长度就增加 
			}
			else //当前是 0 ，说明一个都是 1 的段已经结束了 
			{
				ans+=cnt/3; //累加答案 
				cnt=0;
			}
		}
		ans+=cnt/3;
		//为什么还要多一个 cnt/3，是因为可能数组的后缀是一些连续的 1，但是没有被计算到，到最后再加上 
		printf("%d\n",ans+a[1]); //ans+a[1] 是加上朋友第一次取得数  
	}
	return 0;
}
```




---

## 作者：pigstd (赞：3)

貌似没有和我$dp$方法一样的，那我就发一篇题解吧

设$dp_i$表示你的朋友取到$i$时最少取到$1$的个数

那么容易得到：

$dp_i=\min(a_i+\min(dp_{i-2},dp_{i-3}),a_i+a_{i-1}+\min(dp_{i-3},dp_{i-4}))$

推出这个方程之后，答案就是$\min(dp_i,dp_{i-1},dp_{i-2})$

有两个点需要注意：

1.因为第1次一定是你的朋友先开始，所以设初始值的时候，要把$dp_1-dp_4$都预处理好

2.$i-1$和$i-2$可能$\le 0$，所以要变为$\max(i-1,1)$和$\max (i-2,1)$

[code](https://www.luogu.com.cn/paste/zv93o8vh)

---

## 作者：ql12345 (赞：3)

## dp

定义：令f[i]为到i自己结束，g[i]为到i朋友结束

转移：最后一下是走1步还是走2步，都取min

到朋友结束：
	
   走1步：g[i-1]+a[i]
   
   走2步：g[i-2]+a[i]+a[i-1]
   
到自己结束：
	
   不需要算boss带来的代价

#### code：

```cpp
const int N=2e5+7,inf=0x3f3f3f3f;
int t,n,f[N],g[N],a[N];
signed main(){
	read(t); memset(f,0x3f,sizeof(f)); memset(g,0x3f,sizeof(g));
	while(t--){
		read(n); REP(i,1,n)read(a[i]);
		f[1]=a[1],f[2]=a[1]+a[2],g[1]=inf,g[2]=a[1];
		REP(i,3,n)
			f[i]=min(g[i-1]+a[i],g[i-2]+a[i]+a[i-1]),
			g[i]=min(f[i-1],f[i-2]);
		printf("%d\n",min(f[n],g[n]));
		REP(i,1,n)a[i]=0,f[i]=g[i]=inf;//多测要清空
	}
	return 0;
}
```

---

## 作者：littlejuruo (赞：2)

# DP

用$f_{i,0/1,0/1}$表示到$i$位置的最小答案

第二位是$0$时表示是我朋友的回合,$1$时表示是我的回合

第三位是$0$时表示上一回合是同一人,$1$时相反

易得转移方程为

$f_{i,0,0}=min(f_{i-1,1,0},f_{i-1,1,1})+a_{i}$

$f_{i,0,1}=f_{i-1,0,0}+a_{i}$

$f_{i,1,0}=min(f_{i-1,0,0},f_{i-1,0,1})$

$f_{i,1,1}=f_{i-1,1,0}$

$a_i$即输入数据

答案为$min(f_{n,0/1,0/1})$

## code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e5+10,INF=0x3f3f3f3f;
void file(string s){freopen((s+".in").c_str(),"r",stdin),freopen((s+".out").c_str(),"w",stdout);}
int read()
{
	int f=1,a=0;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')f=-f;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		a=a*10+ch-'0';
		ch=getchar();
	}
	return a*f;
}

int f[MAXN][3][3],a[MAXN];

signed main()
{
//  file("");
	int NT=read();
	while(NT--){
		int n=read();
		for(int i=1;i<=n;++i){
			a[i]=read();
		}
		f[1][0][0]=a[1],f[1][0][1]=f[1][1][1]=f[1][1][0]=INF;
		for(int i=2;i<=n;++i){
			f[i][0][0]=min(f[i-1][1][0],f[i-1][1][1])+a[i];
			f[i][0][1]=f[i-1][0][0]+a[i];
			f[i][1][0]=min(f[i-1][0][0],f[i-1][0][1]);
			f[i][1][1]=f[i-1][1][0];
		}
		int ans=min(min(f[n][0][1],f[n][0][0]),min(f[n][1][1],f[n][1][0]));
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：FiraCode (赞：0)

## 思路：
考虑贪心。
>	对于`11`这种请况，因为第一个是 $1$ 且第二个也是 $1$，又因为要让先手尽可能的小，所以先手只选一个 $1$，而后手选的话就选两个。\
>	对于`10`这种情况，第一个是 $1$ 第二个是 $0$，$0$选跟没选一样，这里先手选，后手不选，为什么后面再说。\
>	对于`0000...01`，我们发现只要 $0$ 的个数 $\ge 2$ 那么不管是先手先去还是后手先取都能让后手先取到 $1$，证明如下：
>> 当有两个的时候，此时，若后手取，就只取一个 $0$，然后再让先手取一个，那么就能让后手先取 $1$，而先手先取就直接把两个 $0$ 去掉就可以了。
>> 当有 $>2$ 个 $0$ 时，那么我们可以取掉一些转化为两个的（大不了就先手取一个，后手取一个，一直到 $2$）。

> 那么我们发现若`101`这种请况后手取了`10`那么先手就只能把最后一个 $1$ 给拿了，但其实它可以不拿，所以`10`这种情况就后手不取 $0$，先手取 $0$。

## Code:
```cpp
#include <bits/stdc++.h>
using namespace std;
int T;
int n;
int a[200010];
int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i)
			scanf("%d", &a[i]);
		int i = 1, ans = 0;
		bool is_ = false;
		while (i <= n) {
			if (a[i] == 0) {
				int cnt = 1;
				int j = i;
				while (j < n && a[j + 1] == 0) ++j, ++cnt;
				if (cnt >= 2) {
					i = j + 1;
					is_ = true;//一段长度>=2的0之后一定是后手先取，所以设成这轮先手不取
					continue;
				}
			}
			if (!is_) {//先手取
				if (a[i] == 1) {
					++ans;
					if (i < n && a[i + 1] == 0 && a[i + 2] == 1) i = i + 2;
					else ++i;
				} else {
					if (i < n && a[i + 1] == 0) i = i + 2;
					else ++i;
				}
			} else is_ = false;
			if (i > n) break;
			if (a[i] == 1) {//后手取
				if (i < n && a[i + 1] == 1) i = i + 2;
				else ++i;
			} else {
				if (i < n && a[i + 1] == 1) i = i + 2;
				else ++i;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
```

---

## 作者：Allanljx (赞：0)

## 题意
有 $n$ 个数，每个数要么是 $0$ 要么是 $1$ ，有两个人轮流取数，可以取一个数也可以取两个数，要让先手取得数的和尽量小，问和最小是多少。
## 思路
这是一道 `DP`。

 $dp[i][0]$ ，表示第 $i$ 个数该先手取时获得的最小和。

 $dp[i][1]$ ，表示第 $i$ 个数该后手取时获得的最小和。
 
 转移方程：
 $dp[i][0]=min(dp[i-1][1],dp[i-2][1]+a[i-1])+a[i]$ 
 $dp[i][1]=min(dp[i-1][0],dp[i-2][0])$ 

要注意初始化：
 $dp[0][1]=0,dp[1][0]=a[1]$ 
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200001],dp[200001][2];
int main()
{
	int t,n;
	cin>>t;
	while(t--)//多组数据 
	{
		memset(dp,0x3f,sizeof(dp));//因为后面要取min，所以要把初始值弄大 
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
		}
		dp[0][1]=0,dp[1][0]=a[1];//初始化 
		for(int i=2;i<=n;i++)
		{
			dp[i][0]=min(dp[i-1][1],dp[i-2][1]+a[i-1])+a[i];//转移方程 
			dp[i][1]=min(dp[i-1][0],dp[i-2][0]);
		}
		cout<<min(dp[n][0],dp[n][1])<<endl; //取最小值 
	}
	return 0;
}
```


---

## 作者：Fa1thful (赞：0)

### 题意：
给定一个 `bool` 数组，有两个人取数组里的数。先手取到 $1$ 要付出 $1$ 点代价，每个人可以取一个或取两个，从左取到右，问先手付出的最少代价是多少。
### 分析：
很显然如果枚举两个人取一个或取两个的情况，时间复杂度则是 $O(2^n)$，肯定会 `TLE`。那么我们就考虑用 `dp`。

因为有两个人，所以 `dp` 应有两维。$dp[i][1/0]$表示取到 `i` ，先手取或后手取 `i`，能够付出的最小代价。那么怎么转移呢？

我们可以根据取的个数分类讨论，那么有两种情况，第一种是前一个人去了两个，另一种是前一个人取了一个。这两种情况分别从 $dp_{i-1}$ 和 $dp_{i-2}$转移来，并且前一个人取的人不能和这次取的人一样，那么我们就有了一个转移方程：
```cpp
dp[i][0] = min(dp[i - 1][1] + a[i], dp[i - 2][1] + a[i] + a[i - 1]);
dp[i][1] = min(dp[i - 1][0], dp[i - 2][0]);
```
但是这个转移方程中有一个问题：如果算上他前面只有两个数怎么办？

很显然这种情况上一个取的人不能取两个。那么转移方程就出来了：

```cpp
if (i >= 3) dp[i][1] = min(dp[i - 1][0], dp[i - 2][0]);
if (i == 2) dp[i][1] = dp[i - 1][0];//这个地方我被卡了很久QWQ
dp[i][0] = min(dp[i - 1][1] + a[i], dp[i - 2][1] + a[i] + a[i - 1]);
```

接下来是初值的问题，很显然第一个数是不参与 `dp` 的，所以我们只需要附取第一数的值。
```cpp
dp[1][0] = 1;     //第一个人取第一个数
dp[1][1] = 999999999;//第二个人取第一个数，为了取min所以附无穷大
```
但是题目并没有说第一个数一定是 `1`，所以 $dp[1][0]=a_1$。
```cpp
dp[1][0] = a[1];    //这个地方卡了我一个多小时，还是同学帮我找出来的QWQ
dp[1][1] = 999999999;
```
### 代码：
```cpp
# include <bits/stdc++.h>
using namespace std;
int n;
int T;
int a[300000];
int dp[300000][2];
int main()
{
	scanf("%d",&T);
	while (T--)
	{
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
		{
			scanf("%d", &a[i]);
		}
		dp[1][0] = a[1];
		dp[1][1] = 999999999; //初值 
		for (int i = 2; i <= n; i++)
		{
			if (i >= 3) dp[i][1] = min(dp[i - 1][0], dp[i - 2][0]);
			if (i == 2) dp[i][1] = dp[i - 1][0];                                //转移 
			dp[i][0] = min(dp[i - 1][1] + a[i], dp[i - 2][1] + a[i] + a[i - 1]);
		}
		printf("%d\n", min(dp[n][1], dp[n][0]));       //最后一个可以是第一个人取也可以是第二个人取 
	}
}
```
谢谢观赏

---

## 作者：EDqwq (赞：0)

### 思路：

看到题目，首先想到简单的贪心：先手每次取 1 个 0 ，后手每次取 2 个 1。

显然我们可以构造一组数据，只有少量的 1 ，卡掉这种做法。

你又尝试了很多种贪心，发现都爆炸了。

于是我们转变思路，尝试dp。

状态：

定义 $dp[i][j = 0/1]$ 表示当前取到第 $i$ 张，现在是先 / 后手取，先手取到的最少张 1 的数量。

初始化：

整个数组赋 $inf$ 值，对于 $dp[0][0]$ ，显然为 0 ，对于 $dp[1][1]$ 显然取 $a[1]$ 。

方程：

$dp[i][0] = \min(dp[i-1][1],dp[i-2][1])$

显然当后手取的时候，先手没有任何影响，所以直接取 min 。

$dp[i][1] = \min(dp[i - 1][0] + a[i],dp[i - 2][0] + a[i - 1] + a[i])$

先手取的时候，对于取 1 张还是 2 张做一个判断即可。

最后答案就是 $\min(dp[n][0],dp[n][1])$ 了。

***

### 代码：

```cpp
#include<bits/stdc++.h>

#define int long long

using namespace std;

int read(){
   int s = 0,w = 1;
   char ch = getchar();
   while(ch < '0' || ch > '9'){if(ch == '-')w = -1;ch = getchar();}
   while(ch >= '0' && ch <= '9')s = s * 10 + ch - '0',ch = getchar();
   return s * w;
}

int t;
int n;
int a[200010];
int dp[200010][2];

signed main(){
	cin>>t;
	while(t --){
		n = read();
		for(int i = 1;i <= n;i ++)a[i] = read(),dp[i][0] = dp[i][1] = 2147483647;
		dp[0][1] = 2147483647;
		dp[0][0] = 0;
		dp[1][1] = a[1];
		for(int i = 2;i <= n;i ++){
			dp[i][1] = min(dp[i - 1][0] + a[i],dp[i - 2][0] + a[i - 1] + a[i]);
			dp[i][0] = min(dp[i - 1][1],dp[i - 2][1]);
		}
		printf("%lld\n",min(dp[n][0],dp[n][1]));
	}
	return 0;
}
```

---

## 作者：do_while_true (赞：0)

设 $f_i$ 为先手取到 $i$ 并且取 $a_i$ 时的最小代价，则 $f_i$ 可以从以下几种状态转移而来

先手取一个，后手在先手前面取了一个（也就是中间跳过一个数来取）: $f_{i-2}+a_i$

先手取一个，后手在先手前面取了两个: $f_{i-3}+a_i$

先手连续取两个的第二个: $\min(f_{i-3}, f_{i-4})+a_i+a_{i-1}$

$f_i$ 即为以上三种状态之一的最小值。

因为 $n$ 可能不取，所以状态转移到 $f_{n+1}$，$f_{n+1}$ 即为答案。（注意初始化 $a_{n+1}=0$）

因为最小是从 $f_{i-4}$ 开始转移，所以要初始化 $f_1,f_2,f_3,f_4$ 的值。

其中 $f_1=a_1$（只有取 $a_1$ 这个方案）

$f_2=a_1+a_2$（只有取 $a_1,a_2$ 这个方案）

$f_3=a_1+a_3$（只有取 $a_1,a_3$ 这个方案）

$f_4=a_1+a_4$（有取 $a_1,a_2,a_4$ 和 $a_1,a_4$ 两种方案，后者大于等于前者）

特判 $n\leq4$ 的各个情况:

当 $n\leq3$ 时，答案为 $a_1$ (必须取 $a_1$ 并且可以只取 $a_1$)

当 $n=4$ 时，答案为 $\min(f_2,f_3,f_4)$（后手可以在最后替先手取 $2,1,0$ 个的方案的最小值）

### $\mathcal{Code}$
```cpp
void solve() {
	n = read();
	for(int i = 1; i <= n; ++i)
		a[i] = read(), f[i] = 0x3f3f3f3f;
	a[n + 1] = 0;
	f[1] = a[1];
	f[2] = a[1] + a[2];
	f[3] = a[1] + a[3];
	f[4] = a[1] + a[4];
	f[n + 1] = 0x3f3f3f3f;
	for(int i = 5; i <= n + 1; ++i)
		f[i] = Min(Min(f[i - 2], a[i - 1] + Min(f[i - 3], f[i - 4])), f[i - 3]) + a[i];
	if(n <= 3) printf("%d\n", f[1]);
	else if(n == 4) printf("%d\n", Min(Min(f[2], f[3]), f[4]));
	else printf("%d\n", f[n + 1]);
}
````

---

