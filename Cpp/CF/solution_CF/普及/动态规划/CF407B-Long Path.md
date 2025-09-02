# Long Path

## 题目描述

One day, little Vasya found himself in a maze consisting of $ (n+1) $ rooms, numbered from $ 1 $ to $ (n+1) $ . Initially, Vasya is at the first room and to get out of the maze, he needs to get to the $ (n+1) $ -th one.

The maze is organized as follows. Each room of the maze has two one-way portals. Let's consider room number $ i $ $ (1<=i<=n) $ , someone can use the first portal to move from it to room number $ (i+1) $ , also someone can use the second portal to move from it to room number $ p_{i} $ , where $ 1<=p_{i}<=i $ .

In order not to get lost, Vasya decided to act as follows.

- Each time Vasya enters some room, he paints a cross on its ceiling. Initially, Vasya paints a cross at the ceiling of room $ 1 $ .
- Let's assume that Vasya is in room $ i $ and has already painted a cross on its ceiling. Then, if the ceiling now contains an odd number of crosses, Vasya uses the second portal (it leads to room $ p_{i} $ ), otherwise Vasya uses the first portal.

Help Vasya determine the number of times he needs to use portals to get to room $ (n+1) $ in the end.

## 样例 #1

### 输入

```
2
1 2
```

### 输出

```
4
```

## 样例 #2

### 输入

```
4
1 1 2 3
```

### 输出

```
20
```

## 样例 #3

### 输入

```
5
1 1 1 1 1
```

### 输出

```
62
```

# 题解

## 作者：ygsldr (赞：4)

以为奇数可以到处走卡住了...

由于奇数只会往前走，往后走只能走1格，我们可以定义dp[p]表示在p点向后走1格所需步数，我们需要证明一个条件保证无后效性：

>走下一步的时候，所有门下次都是奇数次访问

证明：

因为往后走只能通过偶数次，所以下一次一定是奇数次

所以我们的状态可以说是，在p点，所有门下一次都是奇数次访问，向后走1步所需步数

那么转移方程就比较好得到了：

dp[p] = pre[p - 1] - pre[P[p] - 1] + 2

其中,pre为dp的前缀和

解释一下：

你走回P[p],需要1步，从P[p]走回p需要pre[p-1] - pre[P[p] - 1]步，走到下一格需要1步，还是很清晰的

放下代码
```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
const int mod = 1000000007;
int dp[1123456];
int pre[1123456];
int p[1123456];
int main()
{
	int n;
	scanf("%d",&n);
	for(int i(1);i <= n;++i)
	{
		scanf("%d",&p[i]);
	}
	dp[1] = pre[1] = 2;
	for(int i(2);i <= n;++i)
	{
		dp[i] = pre[i - 1] - pre[p[i] - 1] + 2;
		if(dp[i] < 0)dp[i] += mod;
		pre[i] = pre[i - 1] + dp[i];
		pre[i] %= mod;
	}
	printf("%d\n",pre[n]);
	return 0;
}
```


---

## 作者：_Fontainebleau_ (赞：3)

### [CF407B Long Path](https://www.luogu.com.cn/problem/CF407B)

#### 题意

见[题面](https://www.luogu.com.cn/problem/CF407B)

#### 分析

**dp** 


不妨先说转移方程，再解释。我们令 $f_i$ 表示第一次从 $1$ 号房间到 $i$ 号房间需要经过的门的数量，则有 $f_i=f_{i-1}+f_{i-1}-f_{p_{i-1}}+2$。

首先第一二次到达第 $i(i \not= 1)$ 号房间，都是由 $i-1$ 号房间进入的。

那么你第一次走到 $i$ 号房间，首先要第一次到 $i-1$ 号房,花费 $f_{i-1}$。 然后返回 $p_{i-1}$ 号房间,花费 $1$。从 $p_{i-1}$ 号房间走到 $i-1$ 号房间，花费 $f_{i-1}-f_{p_{i-1}}$ （可以用 **前缀和** 的思想去理解）。从 $i-1$ 号房间走到 $i$ 号房间，花费 $1$ 。

因而有：$f_i=f_{i-1}+1+f_{i-1}-f_{p_{i-1}}+1=f_{i-1}+f_{i-1}-f_{p_{i-1}}+2$。

应该还算清爽

#### code below ↓

```cpp
#include<bits/stdc++.h>
#define FOR(i,j,k)  for(int i=(j);i<=(k);i++)
#define mod 1000000007
using namespace std;
int n;
long long f[1003];
int p[1003];
inline int read()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-f;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f;
}
int main()
{
	n=read(); 
	for(int i=1;i<=n;i++)	p[i]=read();
	for(int i=2;i<=n+1;i++)
		f[i]=(f[i-1]+f[i-1]-f[p[i-1]]+2+mod)%mod;//trick:模 mod 之前加上 mod 避免出现负数
	printf("%lld\n",f[n+1]);
	return 0;
}

```


---

## 作者：Disjoint_cat (赞：2)

# [CF407B](https://www.luogu.com.cn/problem/CF407B) [Long Path](http://codeforces.com/problemset/problem/407/B)

随机跳题跳到的。又一道诈骗题。

## 题意

一个长为 $n+1$ 的迷宫，初始时在房间 $1$。

对于一个房间 $x$，如果这是第奇数次到达此房间（包括现在一次），则走到房间 $p_x$，否则走到 $i+1$。

问走到房间 $n+1$ 所需走的步数。

$n\le10^3,\bm{1\le p_i\le i}$。

## 题解

注意到一个房间奇数次经过时只能跳到其前面的房间。

引理：

> 当第一次走到某个房间 $r$ 时，其前面的所有房间都走过偶数次（也就是说下次会跳到 $p$）。

证明：

> 一个房间只有经过偶数次时，才能跳到下一个房间。
> 
> 也就是说，房间 $r-1$ 被经过偶数次。
> 
> 但要走到 $r-1$，$r-2$ 也必须被经过偶数次。
> 
> 以此类推，可得之前所有房间都经过偶数次。

假设我们已经分别求出了跳到 $1\sim r$ 的步数 $f_{1\sim r}$。

接下来，我们考虑跳到 $r+1$ 的过程：

- 从 $1$ 首次跳到 $r$；
- 从 $r$ 跳回 $p_r$；
- 从 $p_r$ 再跳回 $r$；
- 从 $r$ 跳到 $r+1$。

显然，第一步要花费 $f_r$ 步，第二、四步只要 $1$ 步，所以关键点在于第三步。

我们可以把“从 $r$ 跳回 $p_r$”看成“从 $r$ 跳回 $1$，然后再从 $1$ 跳回 $p_r$”。

为什么可以这样做？根据引理，从 $1$ 跳到 $r$ 后 $1\sim r-1$ 全部是偶数次，“跳回 $1$ 再跳回 $p_r$”后，因为没有跳出 $r$，所以也不会变成奇数次，所以这样做是成立的。

如果我们要从 $1$ 跳到 $p_r$ 再跳回 $r$，显然需要 $f_r$ 步。但是实际上我们并没有“从 $1$ 跳到 $p_r$”，所以减去 $f_{p_r}$ 即可。

综上，可得 $f_{r+1}=f_r+1+(f_r-f_{p_r})+1=2f_r-f_{p_r}+2$。

答案不用说了吧，就是 $f_{n+1}$。

时间复杂度 $\Theta(n)$。所以为什么只有 $10^3$。

## 代码实现

```cpp
//struct MI{}; 取模 1e9+7。
const int N=1005;
int n;
MI dp[N];
void Solve()
{
	cin>>n;
	dp[1]=0;
	for(int i=1;i<=n;i++)
	{
		int x;
		cin>>x;
		dp[i+1]=2*dp[i]-dp[x]+2;
	}
	cout<<dp[n+1];
}
```

---

## 作者：T_Q_X (赞：2)

本文同步发布于[我naive的博客中](https://www.cnblogs.com/tqxboomzero/p/13904681.html)
### description
[codeforces传送门](http://codeforces.com/problemset/problem/407/B)
### solution
令$dp[i]$表示从第一位跳到第$i$位，并且此时第$i$位有偶数个甜甜圈需要的最小步数，我们假设这个状态是第$i$位的目标状态，显然有$dp[i]+1$就是从第一位跳到第$i+1$为需要的步数。

于是当$p[i]=i$时，从$i-1$位跳到第$i$位后原地跳一次即可到达目标状态，于是
$$
dp[i]=dp[i-1]+2
$$

否则，从$i-1$位跳到第$i$位后会跳回$p[i]$处，此时，$p[i]$处甜甜圈数量是奇数，而$[p[i]+1,i-1]$中的所有位置因为之前曾从这里跳到下一位，故甜甜圈数量都是偶数，此时的状态正好与从$p[i]-1$跳到$p[i]$时的状态相同，于是再次从$p[i]$跳到$i$需要的步数就是$dp[i-1]-(dp[p[i]-1]+1)+1$
加上一开始跳的2步，故
$$
dp[i]=dp[i-1]-dp[p[i]-1]+2
$$

于是这道题目就做完了。。。
### code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
const int N=1e6+10;
int n,p[N],f[N];
inline int add(int x,int y){return (x+y>=mod)?x+y-mod:x+y;}
inline int dec(int x,int y){return (x-y<0)?x-y+mod:x-y;}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%d",&p[i]);
	for(int i=1;i<=n;++i){
		if(p[i]==i) f[i]=add(f[i-1],2);
		else f[i]=add(add(f[i-1],dec(f[i-1],f[p[i]-1])),2);
	}
	printf("%d\n",f[n]);
	return 0;
}

```

---

## 作者：是个妹子啦 (赞：2)

### 简化题意：

$n+1$个房间，从$1$开始每进入一次房间打一次标记，标记有偶数个时可以往下一个房间，奇数时跳到$p[i]$，求最少经过房间次数

### 思路：

由题意显然要设计状态，因为$f$可以从后面也可以从前面转移过去，但为了简便以及成立，令$f[i]$表示从起点第一次走到第$i$个格子需要跳的次数，考虑$f$的递推，往后走只能是偶数标记，下一次一定是奇数来。又因为题目中$1\le p[i]\le i$，所以可以转移

**转移：** 如果直接从前一个点转移，方程为$f[i]=f[i-1]+1$，但因为我们设的是第一次来这个点，还要从$i-1$号点绕回别的点再回来
$$
\large f[i]=f[i]+f[i-1]+1-f[p[i-1]]
$$
$$
\large f[i]=2*f[i-1]+2-f[p[i-1]]
$$
走回$p[i-1]$需要$1$步，从$p[i-1]$走回$i-1$需$f[i-1]-f[p[i-1]]$步，再走一步，即可得到方程 

```cpp
#include<cstdio>
#include<cctype>
#define maxn 1000005
#define mod 1000000007
#define re register
using namespace std;
int n,p[maxn],f[maxn];
//f从起点第一次走到第i个格子需要跳的次数
inline int read(){
	int x = 0;char c = getchar();
	while(!isdigit(c)) c = std::getchar();
	while(isdigit(c))x = (x << 1) + (x << 3) + (c ^ 48), c = std::getchar();
	return x;
}
int main(){
	n = read();
	for(re int i = 1;i <= n;i++) p[i] = read();
	for(int i = 1;i <= n;i++){
		f[i+1] = (f[i] + f[i] - f[p[i]] + 2) % mod;
		if(f[i+1] < 0) f[i+1] += mod;//比取模稍微快
		//套路，有减时需要考虑负数 
	}
	printf("%d",f[n+1]);
}
```



---

## 作者：月雩·薇嫭 (赞：1)

# CF407B 「Long Path」
------------


**星影落九天，鱼雁舞千弦。但为君沉吟，落日天涯圆。**

------------
[[题目传送门]](https://www.luogu.com.cn/problem/CF407B)

[安利一波博客~](https://pray-yueyu.github.io)

---

### 题目描述

有个人进入一个迷宫，这个迷宫共有$n+1$个房间，编号从$1$~$n+1$，ta现在在第1个房间，需要到达第$n+1$个房间以出去。房间$i$有两个前进的门（来时的门不算），第一扇门通向第$i+1$个房间，第二扇门通向第
$p_i(1<=p_i<=i)$房间，为了不迷路，这个人每到达一个房间，就会给这个房间画一个标记，画完后如果这个房间的标记数为偶数个，ta就会选择这个房间第一扇门前进，否则选择第二扇门前进。 求这个人需要通过多少道门到达终点（即第$n+1$个房间），答案对$1000000007$取模）



------------


##### **思路：**

注意到从$i$走到$i+1$的过程，应该是$i\to p_i\to i\to i+1$

那么我们用$dp_{i+1}$表示从第一个房间第一次到第$i+1$个房间所穿过的门的数量

根据上面的流程图，~~显然有~~：$dp_{i+1}=dp_i+1+dp_i-dp_{p_i}+1$

**解释递推式：**

$dp_i+1$:第一次到第$i$个房间再到第$p_i$个房间所经过门的数量

$dp_i-dp_{p_i}+1$:从第$p_i$房间又跳回$i$并且走到(第一次)$i+1$房间所经过的门的数量

这样就可以得到上面的递推式啦~

##### **为各位大佬献上我丑陋的代码~**

```cpp
#include<bits/stdc++.h>
#define prf printf
#define scf scanf
#define ll long long
using namespace std;
const ll N=1000000+100,M=1000000007;
ll n,a[N],num[N],F[N];
ll read()
{	
	ll x=0,f=1;char ch=getchar();	
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}	
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}	
	return x*f;
}
int main()
{
	n=read();	
	for(int i=1;i<=n;i++)a[i]=read();	
	for(int i=1;i<=n;i++)	
		F[i+1]=(F[i]*2)%M-F[a[i]]+2,F[i+1]=(F[i+1]+M)%M;//记得这里一定要先加上模数再模一次，因为算出来的值可能为负数		
	printf("%lld\n",F[n+1]);	
	return 0;	
	
} 
```

------------


---

## 作者：STDquantum (赞：1)

这是一个递归做法。

如果想要到达 $n+1$，那么必定是从 $n$ 过来的，$n$ 处必然是偶数。

而且每次在推进的时候，只能一格一格往前走，所以在 $n$ 被跳到第二次的时候，就一定能到 $n+1$。

所以现在问题转化到了经过 $n$ 两次需要跳的路程。

我们还可以发现，无论你现在跳到什么地方，之前已经过去的必定是偶数，其实也就可以当做 $0$ 看待，否则无法一直向前推进。

所以从 $n$ 第一次出来的时候，从跳回到的那个点 $p_n$ 开始到 $n$ 的路径，其实和没跳到过 $n$ 时从它开始走过的路径是完全一样的，所以用一个容斥原理，到过 $n$ 两次就转化为了到过 $n-1$ 两次的路径长度二倍减去到 $p_n -1$两次的路径长度。

这就是一个递归的过程了，递归终点当然就是在 $1$ 这个格子，因为 $1$ 是奇数的话只能跳到自己，所以要走两次。

到一个地方（如 $i$）两次以后，还要加上 $1$ 才能跳到下一个地方（如 $i+1$），所以跳到 $i+1$ 两次的那个递归转化要加上 $2$。

递归容易爆栈啊（虽然栈空间足够）。为了防止复杂度太大，可以考虑记忆化一下。为了防止爆栈可以隔一段预处理一下。

因为有记忆化，$[1,n]$ 每个点都只可能访问一次，一共加起来是 $O(n)$ 的。

AC代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

namespace STDquantum {

template <typename T> inline void read(T &x) {  // 快读板子
  char ch;
  int f = 1;
  while (ch = getchar(), !isdigit(ch)) {
    if (ch == '-') f = -1;
  }
  x = (ch ^ 48);
  while (ch = getchar(), isdigit(ch)) { x = x * 10 + (ch ^ 48); }
  x *= f;
}

typedef long long ll;
const int N = 2e6 + 10, mod = 1e9 + 7;
ll n, a[N], ans[N] = {0, 2}; // ans[1]要初始化或者特判
ll solve(ll x) {
  if (x < 1) return 0;
  if (ans[x]) return ans[x]; // 记忆化
  ans[x] = (solve(x - 1) * 2 % mod - solve(a[x] - 1) + 2 + mod) % mod;
  return ans[x];
}
inline void main() { // 就相当于主函数部分
  read(n);
  for (int i = 1; i <= n; ++i) { read(a[i]); }
  // for (int i = 32000; i <= n; i += 32000) solve(i); // 还可以这样做防止爆栈qwq
  printf("%lld", solve(n));
}

}  // namespace STDquantum

int main() {
  STDquantum::main();
  return 0;
}
```

---

## 作者：Mickey_snow (赞：1)

[CF407B](http://codeforces.com/contest/407/problem/B) _Long Path_ :区间动态规划

首先，我们可以发现一个很有用的信息，就是到达一个房间 $i$ 之后如果不能够直接走向 $i + 1$ (奇数次到达 $i$ ) ，那么之后我们只能够去一个拥有比 $i$ 小的 序号的房间，这为我们提供了动态规划的思路。

我们先开一个二维数组 $Dp$ , $Dp_{i,j}$ 代表从 $i$ 号房间走到 $j$ 号房间需要经过的门的数量，$Dp$ 仅当 $i \leq j$ 时才有意义。如果房间从 1 开始编号，那么答案就是 $Dp_{1,n + 1} - 1$ ，边界条件为 $Dp_{i,i} = 1$.

到这里可能有人会有疑问：这两个1是怎么来的。 事实上，$Dp_{i,i} = 1$ 代表从 $i$ 号房间走到 $i$ 号房间，而并不是呆在原地不动，这也是为什么后面的答案算出来也需要减去1的原因。

#### 第一次到达 $i | i > 1$ 之前，一定到达了 $i - 1$ 号房间正好 2 次。

证明：第一次到达 $i$ 号房间之前，一定没有到达过$ i + 1 $。 当第一个达到 $i$ 的时候，走向一个房间 $j$ ,而且 $j \leq i$ ,我们再经过一连串的房间，它们都小于 $i + 1$ ,直到第二次到达 $i$ ，才可以径直走向 $i + 1$.

按照这个逻辑，转移方程如下：

​	$$ Dp_{fr,to} = Dp_{fr,to - 1} + Dp_{next_{to - 1}, to-1} + 1 $$ 

  有了转移方程，但是~~由于我太垃圾了~~看不出来计算顺序，所以我们可以使用记忆化搜索，$Dp_{fr,to}$ 通过以下的函数得到。

```c#
static Int64 Solve(int fr,int to) {
	if(fr == to) return Global.Dp[fr, to] = 1;
	if(Global.vis[fr, to]) return Global.Dp[fr, to];
	else { Global.vis[fr, to] = true;Global.Dp[fr, to] = 0; }

	return (Global.Dp[fr, to] = (Solve(fr, to - 1) + Solve(Global.nxt[to - 1], to - 1) + 1) % 1000000007);
}
```

 在这份代码中 Global 是全局函数类名， $vis_{i,j}$ 代表有没有计算过，当然也可以用 $Dp_{i,j} = -1$ 达到相同的效果。

时空复杂度为 $O(N^2)$  ，但是由于有些状态收不到，所以应该实际上比这个小一些？

完整的代码如下：

```c#
using System;

namespace CF407B
{
    class Program
    {
		public class Global {
			public static Int64[,] Dp;
			public static int[] nxt;
			public static bool[,] vis;
		}

        static void Main(string[] args)
        {
			int totRooms = Convert.ToInt32(Console.ReadLine());
			string[] div = Console.ReadLine().Split(' ');

			Global.nxt = new int[totRooms];
			for(int i = 0; i < totRooms; i++) Global.nxt[i] = Convert.ToInt32(div[i]) - 1;

			Global.Dp = new Int64[totRooms + 1, totRooms + 1];
			Global.vis = new bool[totRooms + 1, totRooms + 1];
			for(int i = 0; i <= totRooms; i++) for(int j = 0; j <= totRooms; j++) Global.vis[i, j] = false;

			Console.WriteLine((Solve(0, totRooms) - 1).ToString());
        }

		static Int64 Solve(int fr,int to) {
			if(fr == to) return Global.Dp[fr, to] = 1;
			if(Global.vis[fr, to]) return Global.Dp[fr, to];
			else { Global.vis[fr, to] = true;Global.Dp[fr, to] = 0; }

			return (Global.Dp[fr, to] = (Solve(fr, to - 1) + Solve(Global.nxt[to - 1], to - 1) + 1) % 1000000007);
		}
    }
}
```



---

## 作者：hhhqx (赞：0)

# Long Path 题解
###### ~~这是一道水蓝~~
## 题意
一个人从一号房间出发,他每到大一个地方，会**先**标记一下,当前标记数为奇数时，他的下一个到达的房间时$p_i$,否则下一个到达的房间为$i + 1$,就求他从 $1$ 到 $n + 1$ 要移动几次。（初始，所有房间标记数为0）

## 化简后的题目,思路
### 无脑暴力思路：

模拟一遍。

### 有脑暴力思路：

- 每个房间的标记数只有奇偶两种状态。
- 第一次到达某个房间时要到达的下一个房间一定是$p_i$。
- 设当前在 $i$ 号房间，那么 $1,2 ...... i - 1$ 号房间的标记数一定为偶数。

对每个房间求这个房间的标记数从奇数变成偶数要移动几次。

输出 $n + 1$ 号房间要移动的次数。

### AC思路

前缀和，记忆化。

记得取模！！！

### 时间复杂度
$O(n^2)$。

## 丑陋代码
```cpp
#include <iostream>
#include <algorithm>

using namespace std;

const long long mod = 1e9 + 7;

int n, a[1010];
int l[1010], sum = 0, uuu;
long long ans[1010];

long long F(int x){
    if(sum != 0 && x == uuu + 1){
        return 0;
    }
    sum = 1;
    if(ans[x] >= 0){
        return (ans[x] + F(x + 1) + mod) % mod;
    }
    l[x]++, sum = 1;
    if(l[x] % 2 == 0){
        return (F(x + 1) + 1 + mod) % mod;
    }else{
        return (F(a[x]) + 1 + mod) % mod;
    }
}

int main(){
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        ans[i] = -1;
    }
    ans[n + 1] = -1;
    for(int i = 1; i <= n + 1; i++){
        fill(l + 1, l + 2 + n, 0), uuu = i, sum = 0;
        ans[i] = F(i);
    }
    long long sum = 0;
    for(int i = 1; i <= n; i++){
        sum = (sum + ans[i] + mod) % mod;
    }
    cout << sum % mod;
    return 0;
}
```

---

## 作者：Phartial (赞：0)

定义一个房间“稳定”表示打上标记后此房间标记数为偶数。

手玩一下可以发现我们到了第 $i$ 个点时第 $1$ 个房间到第 $i-1$ 个房间肯定都是稳定的。

口胡证明：到达第 $i$ 个点肯定要使得第 $i-1$ 个点稳定，然后就可以归纳。

因此设 $f_{i,j}$ 表示从第 $i$ 个房间走到第 $j$ 个房间，且使得房间 $k$（$1\le k\le j$）都稳定的最小步数，初始所有房间都稳定。

若 $i=j$，那么分类讨论：

1. $p_i=i$：此时只需要走 $2$ 步，因此 $f_{i,j}=2$。
2. $p_i<i$：此时第一步会走到 $p_i$，那么我们需要从 $p_i$ 走到 $i-1$，下一步才能走到 $i$。因此 $f_{i,j}=1+f_{p_i,i-1}+1=f_{p_i,i-1}+2$。

若 $i<j$，此时我们需要先从 $i$ 走到 $j-1$，下一步 $j-1$ 走到 $j$，但是 $j$ 会走到 $p_j$，所以分类讨论：

1. $p_j=j$：此时再走 $1$ 步即可稳定。
2. $p_j<j$：此时需要先从 $p_j$ 走到 $j-1$，再从 $j-1$ 走到 $j$，需要走 $f_{p_j,j-1}+1$ 步。

为了实现方便，不妨设 $f_{i,i-1}=0$，那么有转移方程：

$$
f_{i,j}=f_{i,j-1}+f_{p_j,j-1}+2
$$

可以使用记忆化搜索实现，时间复杂度 $O(n^2)$。

```cpp
#include <iostream>

using namespace std;

const int kN = 1001;
const int kM = 1e9 + 7;

int n, p[kN], f[kN][kN];

int S(int i, int j) {
  if (f[i][j]) {
    return f[i][j];
  }
  if (i > j) {
    return 0;
  }
  return f[i][j] = (S(i, j - 1) + S(p[j], j - 1) + 2) % kM;
}

int main() {
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> p[i];
  }
  cout << S(1, n);
  return 0;
}
```

---

## 作者：yellow_bored (赞：0)

## 我来一篇不一样的解法

## 我们先考虑第二扇门走向自己的情况   

那么显然第$n$个点需要经过$2$次才能走到终点，第$n-1$个点则需要走$4$次   

#### 即$f[i]=f[i+1] \times2$

## 然后我们继续考虑所有的情况    

第i个点还会从$p[j]==i$的点走过来，所以在只考虑第一扇门的基础上，转移时还需减少$f[p[j]==i]$      

代码中$f$数组用来统计答案   

$dp$数组用来统计每个点额外减去的值   

### 超短代码如下 ~~（自认为码风不毒）~~
```cpp
#include<bits/stdc++.h>
#define re register
#define LL long long
#define il inline
using namespace std;
template<typename T>il void read(T &ff){
  T rr=1;ff=0;re char ch=getchar();
  while(!isdigit(ch)){if(ch=='-')rr=-1;ch=getchar();}
  while(isdigit(ch)){ff=(ff<<1)+(ff<<3)+(ch^48);ch=getchar();}
  ff*=rr;
}
const int P=1e9+7;
LL f[1000005],dp[1000005],ans;
int p[1000005],n;
signed main(){
   read(n);
   for(int i=1;i<=n;++i)read(p[i]);
	ans+=f[n]=2,dp[p[n]]+=2;
	for(int i=n-1;i>=1;i--){
              f[i]=(-dp[i+1]+f[i+1]*2+P)%P;
	      dp[p[i]]=(f[i]+dp[p[i]])%P;
	      ans=(f[i]+ans)%P;
	}	
   printf("%lld",ans); 
}
```


---

## 作者：无意识躺枪人 (赞：0)

很简单的递推

设$ans[i]$为`第一次到i节点的时间`

很显然，如果直接从前一个点走过来，有递推关系：

$$ans[i]+=ans[i-1]+1$$

但由于我们设的是第一次到达这个点的时间，所以还要算出从$i-1$号节点绕一大圈又回到$i-1$号点的时间：

$$ans[i]+=ans[i-1]+1-ans[fa[i-1]]$$

这个关系很好理解，就是从$i-1$绕一大圈到$fa[i-1]$又回到这个点的时间

而题目又有限制条件：$1\leq fa[i]\leq i$，每一项只与前面的某些项有关

所以我们$\Theta(n)$递推一遍即可

代码：
```cpp
#include<bits/stdc++.h>
#define mod 1000000007
#define N 1000005
using namespace std;

int n,a[N];
long long ans[N];

template<class T>inline void read(T &res)
{
	char c;T flag=1;
	while((c=getchar())<'0'||c>'9')if(c=='-')flag=-1;res=c-'0';
	while((c=getchar())>='0'&&c<='9')res=res*10+c-'0';res*=flag;
}

int main()
{
	read(n);
	for(register int i=1;i<=n;++i) read(a[i]);
	for(register int i=2;i<=n+1;++i)
		ans[i]=((ans[i-1]+1)+(ans[i-1]+1)-ans[a[i-1]])%mod;
	printf("%lld\n",(ans[n+1]+mod)%mod);
	return 0;
}
```

---

