# Funny Game

## 题目描述

Once upon a time Petya and Gena gathered after another programming competition and decided to play some game. As they consider most modern games to be boring, they always try to invent their own games. They have only stickers and markers, but that won't stop them.

The game they came up with has the following rules. Initially, there are $ n $ stickers on the wall arranged in a row. Each sticker has some number written on it. Now they alternate turn, Petya moves first.

One move happens as follows. Lets say there are $ m>=2 $ stickers on the wall. The player, who makes the current move, picks some integer $ k $ from $ 2 $ to $ m $ and takes $ k $ leftmost stickers (removes them from the wall). After that he makes the new sticker, puts it to the left end of the row, and writes on it the new integer, equal to the sum of all stickers he took on this move.

Game ends when there is only one sticker left on the wall. The score of the player is equal to the sum of integers written on all stickers he took during all his moves. The goal of each player is to maximize the difference between his score and the score of his opponent.

Given the integer $ n $ and the initial sequence of stickers on the wall, define the result of the game, i.e. the difference between the Petya's and Gena's score if both players play optimally.

## 说明/提示

In the first sample, the optimal move for Petya is to take all the stickers. As a result, his score will be equal to $ 14 $ and Gena's score will be equal to $ 0 $ .

In the second sample, the optimal sequence of moves is the following. On the first move Petya will take first three sticker and will put the new sticker with value $ -8 $ . On the second move Gena will take the remaining two stickers. The Petya's score is $ 1+(-7)+(-2)=-8 $ , Gena's score is $ (-8)+3=-5 $ , i.e. the score difference will be $ -3 $ .

## 样例 #1

### 输入

```
3
2 4 8
```

### 输出

```
14
```

## 样例 #2

### 输入

```
4
1 -7 -2 3
```

### 输出

```
-3
```

# 题解

## 作者：SqrtSecond (赞：6)

这里提供一种与其他题解不同的思路。

## 题目解析

我们可以发现，每次取完第 $i$ 个数时， $i$ 及其后面的前缀和都不变。

也就是说：

**本题相当于两人交替选择数组的前缀和！**

## 实现方法

根据前面的分析，我们先求出原数组的前缀和 $a_i$ 。

我们设 $dp_i$ 为某人先手时已经取完了前 $i$ 个数所取得的**最大差值**。

下面有两种情况：

### 1.不取到第 $i+1$ 个数

此时与从第 $i+1$ 个数开始取无异，所以 $dp_i=dp_{i+1}$

### 2.取到第 $i+1$ 个数

此时，先手取完得到 $a_{i+1}$ ，后手继续可以得到 $dp_{i+1}$ ，于是 $dp_i=a_{i+1}-dp_{i+1}$

综上所述，可得： $dp_i=\max(dp_{i+1},a_{i+1}-dp_{i+1})$

初始化：由于 $dp_n$ 无意义，我们就设 $dp_{n-1}=a_n$ 。

## ~~你们要的~~代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[1001000],dp[1001000];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i)scanf("%d",&a[i]),a[i]+=a[i-1];//求前缀和 
	dp[n-1]=a[n];
	for(int i=n-2;i>=1;--i)
	{
		dp[i]=max(dp[i+1],a[i+1]-dp[i+1]);
	}
	printf("%d\n",dp[1]);
	return 0;//养成好习惯 
}
```

---

## 作者：XL4453 (赞：3)

### 解题思路：

博弈 DP。

首先这是一个零和博弈，即一方的收益必然意味着另一方的损失。对于这样的问题，考虑用动态规划求解。

发现这个游戏是对称的，无论是谁先取，对于同样的一个情形双方做出的决策和最终的差值都是一样的。

设 $f_i$ 表示从 $i$ 开始到最后先手玩家和后手玩家所能拉开的最大得分差值（对于这道题，双方的具体分数显然是可以忽略的，只需要考虑双方分数差就可以了）。

然后考虑如何转移，对于每一个 $f_i$ 他都可以取任意量的数，从而从后面任意一个 $f_j$ 转移过来，若这样做最终得到的分数差值应当是 $\sum_{k=1}^{j}a_k-f_j$。

但如果单纯这样做，复杂度是 $O(n^2)$ 的，是不能通过的。

那就考虑一个小优化，由于每一次的转移只和自身有关（换言之，就是不和转移到那边去有关），那么就直接记录下当前最大的 $\sum_{k=1}^{j}a_k-f_j$ ，直接转移，再和新的可能的最大值，即 $\sum_{k=1}^{i}a_k-f_i$ 比较即可。

-------------
但其实这题并不需要真的弄一个 $f$ 数组，观察到，每一个的答案都不会比之前（数组意义上的之后）的答案更差，所以只需要一直记录下当前的最优答案就可以了。

-------------
### 代码：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
long long,n,a[200005],ans;
int main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		a[i]+=a[i-1];
	}
	ans=a[n];
	for(int i=n-1;i>=2;i--)
	ans=max(ans,a[i]-ans);
	printf("%lld",ans);
	return 0;
}
```



---

## 作者：Hoks (赞：2)

## 前言
简单手速题，略胜边哥一筹。

摘自 [杂题选做](https://www.luogu.com.cn/training/518105)。
## 思路分析
考察观察题面的能力。

其实不难发现我们就算把前缀和的一段数合并成一个数，后面的数的前缀和也是不变的。

因为你要选后面的数算前缀和也肯定要选上前面合并过的前缀和。

所以就是两人轮流选前缀和，问先后手最大分差。

考虑用 dp 有求这个东西，设 $f_i$ 表示 $i\sim n$ 选出来的最大前缀和。

因为正着跑会被后面影响，所以我们倒着设倒着跑。

那么不难得到转移方程式：
$$f_i=\max(f_{i+1},a_{i+1}-f_{i+1})$$

意义就是要么直接不选这个前缀和从直接按后面的先手走。

要么就是选上这个然后对面变为先手按照后面的最优策略走。

代码也就很好写了，$5$ 分钟码完了。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e6+10,INF=0x3f3f3f3f3f3f3f3f,mod=1e9+7;
int n,a[N],f[N];
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
inline void solve()
{
    n=read();for(int i=1;i<=n;i++) a[i]=a[i-1]+read();f[n-1]=a[n];
    for(int i=n-2;i>=1;i--) f[i]=max(f[i+1],a[i+1]-f[i+1]);print(f[1]);
}
signed main()
{
    int T=1;while(T--) solve();
    genshin:;flush();return 0;
}
```

---

## 作者：仗剑_天涯 (赞：2)

这是博弈论。

先计算出每个s[i](前缀和，a[1...i]）的值。

**比较这个数前缀和S[i]-最大值和最大值哪个大。**

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,mx,s[200010],f[200010];
int main()
{
    cin>>n; 
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&x);
	s[i]=s[i-1]+x;
    }
    mx=s[n];
    for(int i=n-1;i>=1;i--)
    {
        mx=max(mx,s[i]-mx);
    }
    cout<<mx;
    return 0;
}
```

然鹅！

![](https://cdn.luogu.com.cn/upload/image_hosting/xb0kuau9.png)

为什么？


```cpp
for(int i=n-1;i>=1;i--)
{
    mx=max(mx,s[i]-mx);
}
```
因为最后一次i变成了1，而题目要求每次的操作是选择一个**长度大于 1** 的前缀。

所以要将循环中的i>=1改成i>=2，就可以AC了。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,mx,s[200010],f[200010];
int main()
{
    cin>>n; 
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&x);
	s[i]=s[i-1]+x;//先计算出每个s[i](前缀和，a[1...i]）的值。
    }
    mx=s[n];//赋初值。
    for(int i=n-1;i>=2;i--)
    {
        mx=max(mx,s[i]-mx);//比较这个数前缀和S[i]-最大值和最大值哪个大。
    }
    cout<<mx;
    return 0;
}
```


---

## 作者：foreverlasting (赞：2)

博弈论。

双方的操作相当于交替选择该序列的前缀和。

所以跑个DP就好了。

code：
```
//2018.7.30 by ljz
#include<bits/stdc++.h>
using namespace std;
#define res register int
#define LL long long
#define inf 0x3f3f3f3f
#define eps 1e-15
inline int read(){
    res s=0;
    bool w=0;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')w=1;ch=getchar();}
    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=getchar();
    return w?-s:s;
}
inline int _max(res x,res y){
    return x>y?x:y;
}
inline int _min(res x,res y){
    return x<y?x:y;
}
const int N=2*1e5+10;
int n;
int a[N],dp[N];
int main(){
	n=read();
	for(res i=1;i<=n;i++)a[i]=a[i-1]+read();
	res ans=a[n];
	for(res i=n-1;i>=1;i--)dp[i]=ans,ans=_max(ans,a[i]-dp[i]);
    printf("%d\n",dp[1]);
	return 0;
}
```

---

## 作者：focus_aurora (赞：1)

## 思路

博弈论。

首先对这个序列求出前缀和。

因为双方均想最大化自己的得分。

对于每一步，都会考虑前缀和与最大值的差和最大值那个更大。

更大的就是我们的答案。

细节方面要注意求最大值变量 $maxn$ 的赋初值和遍历的下标。

更详细的见代码。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5;
int sum[N],a[N],n;
int maxn;
signed main(){
	scanf("%lld",&n);//输入 
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		sum[i]=sum[i-1]+a[i];//求前缀和 
	}
	maxn=sum[n];//赋初值！！！ 
	for(int i=n-1;i>=2;i--){//到2结束，大于1的前缀！ 
		maxn=max(maxn,sum[i]-maxn);//求答案 
	}
	printf("%lld",maxn);//输出 
	return 0;//好习惯 
} 
```

---

## 作者：王大神——A001 (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF731E)
### 思路
由于双方的操作后，操作后都是将操作数的和在放回去，所以可以用前缀和先处理了一下数组。

双方都想自己的分值比对方尽量大，所以第一个人一定拿的是最优。否则，对方拿了剩下的最优，再剩下的就一定不是最优的了。那么，我们可以第一次就使得利益最大化。

我们可以逆着遍历，不断的求计算的数和前缀和差的最大值（尽量使自己比对方的分值大）最后输出即可。

### 代码
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
const int o_o=200001;//注意数据范围 
int n,n_i,a_s,a_a[o_o];
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&n_i);//读入数列 
		a_a[i]=a_a[i-1]+n_i;//预处理，求前缀和 
    }
    a_s=a_a[n];//赋初值，要逆着遍历保证最优情况 
    for(int i=n-1;i>=2;i--)a_s=max(a_s,a_a[i]-a_s);//注意：最少选两个数注意边界 
    printf("%d",a_s);//输出结果 
    return 0;
}
```


---

## 作者：长明 (赞：1)

首先，我看到题目

(稍加思索)
写下

```cpp
#include<bits/stdc++.h>
using namespace std;
int n; 
int main()
{
	cin>>n;
	for(int i=1,n=0; i<=n; i++)
	{
		int x;
		cin>>x;
		n+=x;
	} 
	cout<<n;
	return 0;
}

```
结果

WA

emmmm


（挠头思索+~~百度~~）

状态转移方程为

------------
### $dp[i]=max(a[j]-dp[j])    i<j<=n$
###### （$dp[i]$表示前i个先手的最大值）
------------



面对同一个状态，最优决策都是不变的，所以不需要保存两个人，只需要保存最优决策。

显然我们想得到$dp[1]$，而$dp[n-1]$又是显然的，根据题目要求，这种情况下必须要选至少2个，而又只剩2个了。因此要用逆推。状态转移方程如上。


另外


在面对一个状态时，决策有$2$到$n-i$个，遍历找一个最大值（值为和减去最优解）

再优化一下，可以在dp时顺便记录a[i]-dp[i]的最大值。

即：

------------
#### $maxn=max(maxn,dp[i]-maxn)$
------------
同时，进一步优化，可以


```cpp
#include<bits/stdc++.h>
#include<cstdio>
using namespace std;
int n,dp[100005];
int main()
{
	cin>>n;
	for(int i=1; i<=n; i++)
	{
		int x;
		cin>>x;
		dp[i]=dp[i-1]+x;
	} 
	int mmax=dp[n];
	for(int i=n-1;i>=2;i--)
    		mmax=max(mmax,dp[i]-mmax);                                                                                                                 		           																																				莫抄题解
	cout<<mmax<<endl;
	return 0;
}

```

o（n）过



---

## 作者：endswitch (赞：0)

我们不关心谁先手谁后手，只要关注得分差。

设 $dp_i$ 为从后向前考虑到第 $i$ 位的最大得分差，则：

$$
dp_i = \max_{j \in [i + 1, n]} \left \{ pre_j - dp_j \right \}
$$

$\max$ 式子用 $dp$ 序列懒惰转移即可。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 2e5 + 5;
int n, maxx, a[N], dp[N], pre[N];

signed main() {
	ios_base :: sync_with_stdio(NULL);
	cin.tie(nullptr);
	cout.tie(nullptr);
	
	cin >> n;
	for(int i = 1 ; i <= n ; ++ i)
		cin >> a[i], pre[i] = pre[i - 1] + a[i];
	
	maxx = pre[n];
	
	for(int i = n - 1 ; i ; -- i) {
		dp[i] = maxx;
		
		maxx = max(maxx, pre[i] - dp[i]);
	}
	
	cout << dp[1];
	
	return 0;
}
```

---

## 作者：lfxxx (赞：0)

双方其实是对称的，别管哪方，关注得分差就行。

替换操作可以视为不替换但是每次选择的前缀都要比上一个选择的前缀靠后。

于是设计状态 $dp_i$ 表示考虑 $[i,n]$ 区间内的决策所能带来的最大得分差，显然有 $dp_i = \max(-dp_j + pre_j)$，于是从后往前 dp，记录一下 $\max$ 即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
//#define lowbit(x) (x&(-x))
//#define bp push_back
//#define sz size
//#define cl clear
const int maxn = 2e5+114;
int dp[maxn];
int mx,n;
int pre[maxn];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>pre[i],pre[i]+=pre[i-1];
	mx=-INT_MAX;
	dp[n]=0;
	mx=max(mx,-dp[n]+pre[n]);
	for(int i=n-1;i>=1;i--){
		dp[i]=mx;
		mx=max(mx,-dp[i]+pre[i]);
	}
	cout<<dp[1]<<'\n';
	return 0;
}

```

---

## 作者：TimSwn090306 (赞：0)

## [CF731E Funny Game 题目传送门](https://www.luogu.com.cn/problem/CF731E)

## 0.前话：

秒了一道 *2200 开心捏。


## 1.解题思路：

首先每个人每轮的得分一定是原序列中的一段前缀和的值，因为即使把这段前缀和缩成一个数字仍然不影响它们的和不变，所以某人在任意一轮，选择相同一个位置，的得分都是相同的，这是一个非常好性质，考虑 dp 。

设 $dp_i$ 表示还剩下区间 $[i,n]$ 中的数时（即剩下 $n-i+1$ 个数），所能得到的最大得分差（仍要考虑对手的最优策略）。

那么我们显然有一个 dp 转移式：

$$dp_i=\max_{j\in(i,n]}\{sum_j-dp_j\}$$

其中 $sum_j$ 表示原序列中 $j$ 下标的前缀和；由于 $dp_j$ 是对手的最优策略，因此还要减去其值。

诶，我们发现 $\max$ 里的式子和 $i$ 没有任何关系！！！所以我们可以维护一个值 $maxx$，它代表着 $(sum_j-dp_j)$ 的最大值，每次转移时直接将 $dp_i$ 设为 $maxx$ 并且更新 $maxx$ 的最大取值即可。

## 2.代码展示：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
int n,maxx,a[maxn],sum[maxn],dp[maxn];
int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&a[i]),sum[i]=sum[i-1]+a[i];
	maxx=sum[n],dp[n]=0;
	for (int i=n-1;i;i--){
		dp[i]=maxx;
		maxx=max(maxx,sum[i]-dp[i]);
	}
	printf("%d\n",dp[1]);
	return 0;
}
```



---

## 作者：hjqhs (赞：0)

$*$2200？$*$1200！  
简单博弈论。  
显然每次选前缀和，然后进行一个 dp。后手最好策略显然是与先手交替选，所以 $dp_i = \max({dp_{i+1},a_{i+1}-dp_{i+1}})$。然后发现可以把 dp 数组滚掉。
```cpp
// Problem: E. Funny Game
// Contest: Codeforces - Codeforces Round 376 (Div. 2)
// URL: https://codeforces.com/problemset/problem/731/E
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// Created Time: 2023-12-21 21:41:35
// Author: hjqhs
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;

// #define int long long
#define rep(i, a, b) for(int i = (a); i <= (b); ++ i)
#define per(i, a, b) for(int i = (a); i >= (b); -- i)
typedef long long ll;
typedef unsigned long long ull;

const int N = 200005;
const int INF = 0x3f3f3f3f;

int n, mx, a[N];

void solve() {
	cin >> n;
	rep(i, 1, n) {cin >> a[i]; a[i] += a[i - 1]; }
	
	mx = a[n];
	per(i, n - 1, 2) mx = max(mx, a[i] - mx);
	
	cout << mx;
	
	return;
}

signed main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	
	solve();
	
	return 0;
}
```

---

## 作者：QWQ_jyc (赞：0)

又是一题博弈论。

先交替选择该序列长度大于 $1$ 的前缀和，再枚举前缀和（自己分数）与最大值（对手分数）的差的最大值。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,s,m,a[11451419],f[11451419];
int main(){
	cin>>n; 
	for(int i=1;i<=n;i++){cin>>s;a[i]=a[i-1]+s;}//求前缀和
	m=a[n];//赋值
	for(int i=n-1;i>=2;i--)m=max(m,a[i]-m);//枚举，同时取绝对值
	cout<<m;
	return 0;
}
```


---

## 作者：fmdd_szx (赞：0)

[原题](https://www.luogu.com.cn/problem/CF731E)

# 题意

两人交替选择数组中长度大于 $1$ 的前缀，求自己分数 $-$ 对手分数的最大值。

# 思路

利用前缀和，枚举前缀 $a_i-$ 最大值的最大值。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,i,x,ma,a[1000001];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(i=1;i<=n;i++)
    	cin>>x,a[i]=a[i-1]+x;
    ma=a[n];
    for(i=n-1;i>=2;i--)
    	ma=max(ma,a[i]-ma);
    cout<<ma;
    return 0;
}
```
  

---

## 作者：Register_int (赞：0)

~~好水一 *2200~~  
容易发现每次选的就是前缀和。之后就是决策到底要选哪个的问题。  
考虑 $dp$。设 $dp_i$ 为取 $i\sim n$ 这段时可以获得的最优结果。如果取了 $a_i$，则后手的策略就是复制之前先手的操作。所以此时 $dp_{i-1}=a_i-dp_i$。不选则 $dp$ 值不变。  
数组可以滚掉。  
# AC 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2e5 + 10;

int n, a[MAXN];

int ans;

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]), a[i] += a[i - 1]; ans = a[n];
	for (int i = n - 1; i >= 2; i--) ans = max(ans, a[i] - ans);
	printf("%d", ans); 
}
```

---

