# [POI 2010] GRA-The Minima Game

## 题目描述

**译自 POI 2010 Stage 3. Day 1「[The Minima Game](https://szkopul.edu.pl/problemset/problem/3buviDQZWLE83AxVhvJJurgU/site/?key=statement)」**

Alice 和 Bob 玩一个游戏。Alice 先手，两人轮流进行操作，每轮一个玩家可以选择若干张牌（至少一张），并获得相当于这些牌上所写数字的最小值的分数，直到没有牌为止。两人都希望自己的分数与对方分数之差最大。若两个玩家都使用最佳策略，求游戏的最终结果。

## 说明/提示

$1\le n\le 10^6$，$1\le k_i\le 10^9$。

翻译来自于 [LibreOJ](https://loj.ac/p/2455)。

## 样例 #1

### 输入

```
3
1 3 1```

### 输出

```
2```

# 题解

## 作者：枫林晚 (赞：34)

### 题目大意：

给出N个正整数，AB两个人轮流取数，A先取。每次可以取任意多个数，直到N个数都被取走。每次获得的得分为取的数中的最小值，A和B的策略都是尽可能使得自己的得分减去对手的得分更大。在这样的情况下，最终A的得分减去B的得分为多少。

### 分析：

我们身临其境地考虑一下，先手肯定是要从大到小取数，并且一定取的是连续的一段。

证明：

从大到小取数显然，若不是连续取数，则留下的数更多，大的数更多，会给对方更多的机会。所以必然是连续取数。

所以我们倒着来考虑一下，将所有的数从小到大排列之后，f[i]表示两人取完前i个数，先手减去后手的最大值，（这里先手后手是相对的，因为我们是倒序的，和实际取法是完全相反的，它实际上是处理出了1~i个数的情况下的最优解，A先从i开始往左边取，所以说考虑先手减后手最大值）

这样的话，每到一个i，我们可以枚举一下A先手第一步从i取到哪里。而剩下的一段必然是换B当先手来操控。

f[i]=max(a[j]-f[j-1])(1<=j<=i)

j的意义是：A先手从i取到j，由于单调递减，所以他的得分就是a[j]，但是剩下的肯定由B来操控出f[j-1]，即1~j-1数的先手最大值，这样，A实际做出的超越，就是a[j]-f[j-1],保证先手使得差距最大，所以从所有的a[j]-f[j-1]中取一个max值。

这个max可以前缀最大值优化处理。

更简单的是：因为f[i-1]就是由这个max值转移过来的，所以f[i]=max(f[i-1],a[i]-f[i-1])

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1000000+10;
int n,a[N];
long long f[N];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)
	 f[i]=max(f[i-1],a[i]-f[i-1]);
	printf("%lld",f[n]);
	return 0;
}
```

---

## 作者：gary2005 (赞：10)

这是一题很好的dp题

首先我们需要明白几个事实

1. A和B的策略都是尽可能使得自己的得分减去对手的得分更大（也就是A 和 B都很聪明）换句话说在你来我往的取数间最大差值的对象是一直都在变化的。
2. 如果你要取走一个数，比它大的数一定是不能留下的，举个栗子：如果一个单调数列 1 2 3 5 7 9 你看中了5这个数那么取走7和9并不会影响你的得分（得分为最小数值），反而留下来还会给对手带来机会所以要一起取走。
3. 一定是从大向小取，我们假设你的对手从小向大取数，那么你从大向小取，你就赢定了。而题目中的A B都非常聪明，都会采用最佳策略。那么，由于A是先手，A留给B的肯定是比自己取的小的数（2 给予证明）。

接下来我们可以做题了

为了方便做题，我们将取的顺序反转，也就是从小到大取（结果并不影响）
```cpp
sort(a+1,a+n+1);
```
很快就会能写出第一个转移方程


```cpp
for(int i=1;i<=n;i++){
	   //枚举i就是A取到i的最大差值（A-B）
   	for(int j=0;j<i;j++){
       //这里枚举j就是A将取到j的机会让给了B,这里的dp[j]变为(B-A)的最大差值（1给予证明）。
//这时A取的是a[j+1]~a[i]，由于是单调数列，取得的就是最小值a[j+1].
    	dp[i]=max(dp[i],a[j+1]-dp[j]);
       }
}
```
但是O(n^2)会超时

所以需要优化。这是我们有了第二个转移方程
```cpp
for(int i=1;i<=n;i++){
    	dp[i]=max(dp[i-1],a[i]-dp[i-1]);
}
```
那这个怎么来理解。

由于取到第i个数只有两个可能1：单独就取i这个数，2：和前面的连在一起。

dp[i-1]就可以理解为和前面连在一起，由于单调数列，连在一起并不影响得分。

a[i]-dp[i-1]可以理解为单独取 所以dp[i-1]变为B-A的最大值（1证明）。

我们还可以继续优化，我们发现dp[i]只与dp[i-1]有关,所以我们可以省去数组。

好现在上CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1000000+10;
int n,a[MAXN],ans;
int main(){
	scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++){
    	ans=max(ans,a[i]-ans);
    }
    printf("%d\n",ans);
	return 0;
}
```


---

## 作者：Forever丶CIL (赞：5)

首先如果你想不到朴素的$O(n^2)$的做法，那建议你先刷点简单的动态规划题目再来做这个题。

先讲一下$O(n^2)$的算法：
-  首先，我们一拿一定是拿连续的一段数，不会拿几个大的，再拿几个小的，这个大家脑补一下就很清楚了。
- 那么我们先将这N个正整数从小到大排序。
- 令a[i]代表排好序后的第i个数，A[i]代表只拿前i个数的时候先手的最大得分。

那么转移也很好写：

$A[i]=max(A[i],a[j+1]-A[j]);\quad(j\in[0,i-1]) $

这个方程的意思是，我可以一次性把第j+1到第i个数(指排过序了的)全拿走，这样我的得分就是a[j+1]，而接下来，另一个人面对只剩下前j个数的局面的最大的分是A[j]，那么我们拿了a[j+1]后，与另一个人的分差就是a[j+1]-A[j]了。

这样就可以拿到60分。

但其实满分做法也不难，很显然我们每次更新A[i]都把前面所有的A[j]都枚举一遍是很浪费时间的，我们只需要知道最大的a[j+1]-A[j]是多少就可以了，而A[i]正是在不断的储存着i以前最大的a[j+1]-A[j]，所以方程就变成了：

$A[i]=max(A[i-1],a[i]-A[i-1]);$


------------


```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
const int Maxn=2000000;
int n;
int a[Maxn];
int A[Maxn];
inline int read()
{
    int fl=1,rt=0; char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-') fl=-1; ch=getchar();}
    while(ch>='0'&&ch<='9'){rt=rt*10+ch-'0'; ch=getchar();}
    return fl*rt;
}
void read_ini()
{
	n=read();
	for(int i=1;i<=n;i++) a[i]=read();
	sort(a+1,a+1+n);
	A[1]=a[1];
	for(int i=2;i<=n;i++) A[i]=max(A[i-1],a[i]-A[i-1]);
	printf("%d\n",A[n]);
}
int main()
{
	read_ini();
	return 0;
}
```


------------
$RP++$


---

## 作者：AubRain (赞：4)

刚看到这道题，发现跟今年九省联考的 D1T1 一双木棋挺像的。
~~后来发现真是一点也不一样~~

首先肯定要排序一下，~~显然~~。	**因为最优策略肯定是取最大的中连续的一段**

于是秒出解法：**记忆化搜索**

dp(i) 表示排完序从后往前剩 $i$ 的**先手-后手**最大得分。

然后枚举取到哪就行了

然后发现竟然是 $O(n^2)$ ，果断TLE

```cpp
#include<bits/stdc++.h>
#define N 1000005
using namespace std;
int n,a[N],f[N];
bool cmp(int a,int b){return a>b;}
int dp(int x)
{
    if(x==n) return 0;
    if(f[x]!=0xcfcfcfcf) return f[x];
    for(int i=x+1;i<=n;i++)
        f[x]=max(f[x],a[i]-dp(i));
    return f[x];
}

int main()
{
    scanf("%d",&n);memset(f,0xcf,sizeof f);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    sort(a+1,a+1+n,cmp);
    printf("%d",dp(0));
    
}

```

于是就不得不改进一下。

**记忆化搜索的本质就是dp，而dp不就是当重复访问子问题的时候记录一下吗？**

然后发现这其实是一个假的dp，因为计算 $dp(x)$ 和 $dp(x+1)$ 的时候还是会**重复枚举后面的值，造成无用的时间浪费**

于是就可以改进一下，**每次不枚举了，直接从 $dp(x+1)$转移**因为 $dp(x+1)$ 已经是最优解了，相当于枚举过了一遍。

**正确的代码：**

```cpp
#include<bits/stdc++.h>
#define N 1000005
using namespace std;
int n,a[N],f[N];
bool cmp(int a,int b){return a>b;}
int dp(int x)
{
	if(x==n) return 0;
	if(f[x]!=0xcfcfcfcf) return f[x];
	f[x]=max(dp(x+1),a[x+1]-dp(x+1));
	return f[x];
}

int main()
{
	scanf("%d",&n);memset(f,0xcf,sizeof f);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	sort(a+1,a+1+n,cmp);
	printf("%d",dp(0));
}

```
$dp$ 的复杂度是 $O(n)$ ,但瓶颈在于排序是 $O(nlogn)$ 的

当然其实还可以再优化，可以不用记忆化搜索，甚至不用开dp数组。直接倒序循环就行了。其实降序排序+倒序循环 相当于 直接排序+正序循环。

于是简短的代码就出来啦

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[1000005],ans;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    sort(a+1,a+1+n);
    for(int i=1;i<=n;i++) ans=max(ans,a[i]-ans);
    printf("%d",ans);
}

```

---

## 作者：lfxxx (赞：2)

首先假若在某一次取数中最小的数是 $x$，那实际上你就可以吧大于等于 $x$ 的数全部取走，反正得分没变而且使得对手可以取的方案变劣了，所以一定是不劣的。

也就是说所每次取完数剩下的一定是小于等于 $x$ 的所有数，不放先把所有数排序，然后设计状态 $dp_i$ 表示取后把前 $i$ 个数取完的最大答案，显然有转移 $dp_i = \max(a_{j+1} - dp_{j})$。直接记录 $\max(a_{i+1} - dp_i)$ 然后 $O(n)$ 转移即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 1e6+114;
int n,a[maxn],dp[maxn];
set<int> S;
signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        S.insert(a[i]);
    }
    int tot=0;
    for(int x:S) a[++tot]=x;
    //容易发现最优情况下每次都是选择一个数并且把比这个数大的数全部取掉
    //所以设计状态 dp[i] 表示取完除了前 i 大以外的数的答案
    //dp[i] = max(a[j+1]-dp[j])
    int mx=a[1],dp=0;
    for(int i=1;i<=tot;i++){
        dp=mx;
        mx=max(mx,a[i+1]-dp);
    }
    cout<<dp<<'\n';
    return 0;
}
```


---

## 作者：dbxxx (赞：2)



[P3507 [POI2010]GRA-The Minima Game - 洛谷 | 计算机科学教育新生态 (luogu.com.cn)](https://www.luogu.com.cn/problem/P3507)


给定一个长度为 $n$ 的正整数序列，A和B轮流取数，一次取任意多，一轮一方得分为取的数的最小值，双方策略均为最大化自己的得分减对手的得分，问最后A的得分减去B的得分。


- $1 \le n\le 10^6$
- $1 \le a_i \le 10^9$


考虑到题目中要求最小值，而排序不会影响答案，数据范围也支持我们排序。那就先排个序。

接下来说的 $a$ 都是排过序的了。

先考虑双方的博弈策略：一定拿从大到小连续的一段数，也就是一定拿的是 $a_i, a_{i +1}, \ldots, a_n$ 的一段数列。

为什么？

因为如果你连 $a_i$ 都取了，取比 $a_i$ 更大的数并不会影响到自己的得分（得分是选数最小值），但是不取会给对方留更多超越自己的机会。

考虑 dp。定义 $f_i$ 为前 $i$ 个数中，先手得分减去后手得分的最大值。一个很明显的方程：

$f_i = \max(a_j - f_{j - 1})$，$1 \le j \le i$

什么意思呢？$a_j - f_{j - 1}$ 其实描述的就是我从 $i$ 取到 $j$，我的分数减去你的分数。很好理解：A先从 $i$ 取到 $j$，我的得分是 $a_j$（因为 $a_j$ 到 $a_i$ 中最小的是 $a_j$），而B的最大得分自然是 $f_{j - 1}$（在 A 从 $i$ 取到 $j$ 后，剩下的从 $1$ 到 $j - 1$ 这一段相当于 B 为先手取数，得分 $f_{j - 1}$）。

这个做法 $n^2$，时间复杂度不是特别美丽。~~主要分数不美丽，不然暴力最美~~

方便叙述，把 $a_j - f_{j - 1}$ 说成式子 $F_j$.

观察到 $f_i$ 也就是 $j$ 从 $1$ 到 $i$ 的 $F_j$ 最大值，而 $j$ 从 $1$ 到 $i - 1$ 的 $F_j$ 最大值已经被 $f_{i - 1}$ 保存了。

$f_i$ 相对于 $f_{i - 1}$ 只是在 $j$ 的取值范围拓展到了可以取到 $i$ 了，那么我们只需要把 $f_{i - 1}$ 和新的 $F_i$ 比较一下最大值就可以了。也就是 $f_i = \max(f_{i - 1}, F_i)$.

到这里还能理解吗？不能理解就多看看吧！相信你可以看懂。

最后把 $F_j$ 还原成原来的样子，得到最终状态转移方程：

$$
f_i = \max(f_ {i - 1}, a_i - f_{i - 1})
$$



$\operatorname{O}(n \log n)$

因为排序。

状态转移是 $n$ 的复杂度的。


```cpp
/*
 * @Author: crab-in-the-northeast 
 * @Date: 2022-04-06 23:23:22 
 * @Last Modified by: crab-in-the-northeast
 * @Last Modified time: 2022-04-06 23:30:39
 */
#include <iostream>
#include <cstdio>
#include <algorithm>

inline int read() {
	int x = 0;
	bool flag = true;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-')
			flag = false;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		x = (x << 1) + (x << 3) + ch - '0';
		ch = getchar();
	}
	if (flag)
		return x;
	return ~(x - 1);
}

const int maxn = 1000005;
int a[maxn], f[maxn];

int main() {
	int n = read();
	for (int i = 1; i <= n; ++i)
		a[i] = read();
	std :: sort(a + 1, a + 1 + n);

	f[1] = a[1];
	for (int i = 2; i <= n; ++i)
		f[i] = std :: max(f[i - 1], a[i] - f[i - 1]);
	
	printf("%d\n", f[n]);
	return 0;
}
```

不错的dp！

---

## 作者：苏景曦 (赞：2)

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100010],dp[100010];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	//易证，所取数字大小上一定是连续的，不然对手会取到更大的数； 
	sort(a+1,a+1+n);
	//倒叙处理，因为前面的会用到后面的状态 
	for(int i=1;i<=n;i++){
		dp[i]=max(dp[i-1],a[i]-dp[i-1]);
		//对于每个数来说：是取当前数，让对手取之后的最优解好；
		//				  还是取到之后的那个最优解好；
		//				  以此DP； 
	}
	printf("%d",dp[n]);
	return 0;
}
```

---

## 作者：z7z_Eta (赞：1)

###POI2010

本题题解也不少了，我的状转方程不太一样，顺便说说自己思考此题的心路历程

此题其实很套路，设计状态是关键。（建议读者自己先思考，正解说不定就在不经意间得出

* 首先呢，把数字排好序，这样就形成了牌**堆**一样的结构，可以想堆顶是最大值，每次取牌时可以贪心的拿出第$X$张牌以上的所有牌，得分为$a_X$
* 发现拿牌的过程就是**转移**，自然的，设计这样的状态$f1_{i}$表示Alice的回合，剩余$i$张牌，$f2_{i}$表示Bob的回合，剩余$i$张牌。
* $O(n^2)$转移：$f1_x=max_{i=1}^{x-1}\ f2_i+a_{i+1}$ ，$f2$就是把max改成min
* 直接维护前缀max就$O(n)$啦

滚动数组就好了。

代码极短，作为蓝题还是很爽的

```cpp
// SeptEtavioxy
#include<cstdio>
#include<cctype>
#include<algorithm>
#define re register
#define ll long long
#define il inline
#define rep(i,s,t) for(re int i=(s);i<=(t);i++)
#define ptll(x) printf("%lld",x)
using namespace std;
// c_ints
il int ci(){
	re char ch;
	while(isspace(ch=getchar()));
	static int f; f= ch=='-'?-1:1 ;
	re int x= (ch=='-'?getchar():ch)^'0';
	while(isdigit(ch=getchar()))x=(x*10)+(ch^'0');
	return f*x;
}
enum{N=1000024};
int a[N];
int main(){
	int n= ci();
	rep(i,1,n) a[i]= ci();
	sort(a+1,a+n+1);
	n= unique(a+1,a+n+1)-a-1;//去重，其实不写也没关系的，和正确性无关
	ll mx1=0, mx2=0;
	rep(i,1,n){
		ll t= mx1; //锅点，注意
		mx1= max(mx1,mx2+a[i]);
		mx2= min(mx2,t-a[i]);
        //转移方程其实和其他题解实质一样，位置不同而已
	}
	ptll(mx1);
	return 0;
}
```
祝rp++；



---

## 作者：小塘空明 (赞：1)

看下n，1e6，基本可以确定是线性递推了。

从大到小选显然，同时很容易发现每次选必须选连续的一段，否则一段中留一个更大的数给对面显然不如自己选走优。

将a从小到大排序，设f[i]为当前人从当前数开始选所能得到的最大值。

可以发现f[i]与选的人是谁无关。

所以我们可以得到一个递推式f[i]=max(a[j]-f[j-1])(1<=j<=i)。

因为我们每次可以选连续的一段，所以f[i]=max(f[i],f[i-1]);

```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<string>
#include<cstring>
#include<cmath>
using namespace std;
typedef long long ll;
const ll size=1e6+10;
ll n,a[size],f[size];
inline ll read(){
	ll x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
	return x*f;
}
int main(){
	n=read();
	for(ll i=1;i<=n;i++) a[i]=read();
	sort(a+1,a+1+n);
	for(ll i=1;i<=n;i++){
		f[i]=max(f[i-1],a[i]-f[i-1]);
	}
	printf("%lld\n",f[n]);
	return 0;
}
```


---

## 作者：kczno1 (赞：1)

如果选了i，那么>=i的数都要选。

否则对方一定会更优。


证明:

假如选完>=i的数的状态为s1,没选完的为s2。

对方可以先选完>=i的数，那么他接下来面对的状态就是s1了。

所有在s2下，一切s1有的决策他都能选择。

同时他还多了一些决策。

所有s2下他一定比s1优。


所以我们先将n个数从小到大排序。

f[i]表示剩下了1..i这个前缀的max(先手-后手)。

枚举先手决策，f[i]=max(a[j]-f[j-1]),j=1..i

边界是f[0]=0。

a[j]-f[j-1]的前缀max是很好维护的。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define N 1000010
void chmax(int &x,int y) { if(x<y)x=y; }
int a[N];

int main()
{
    freopen("1.in","r",stdin);
    int n;scanf("%d",&n);
    int i;
    for (i=1;i<=n;++i) scanf("%d",a+i);
    sort(a+1,a+n+1);
    int ans=0;
    for (i=1;i<=n;++i) chmax(ans,a[i]-ans);
    printf("%d",ans);
}
```

---

## 作者：说好不哭 (赞：0)

```cpp
// 先把a数组从小到大排序，可以肯定的是， 每一次取，肯定要取从当前的最大值开始的连续一段
// f[i]表示从第一个数取到第i个数先手的最大分数，（也同时会成为后手的最大分数）
// 转移： 
//1.假设f[i-1]的价值是通过取  al,al+1,al+2...,ai-1得到的，那么这次的f[i]的价值，就是通过取 al,al+1,al+2...,ai得到的
//  那么f[i]=f[i-1] 
//  2. 这次只取一个a[i],那么后手就会取f[i-1]的价值，所以此刻的价值应为 :a[i]-f[i-1]
//  比如，有这个数据   1,100
// 方案就是这两种 1.先手就只取个100，那么后手会取1，这样价值为99 ,这个思路可以理解为："你好我好大家好“
// 因为先手会加一个值，后手也会加一个值，这时候，如果先手增加的值比后手增加的值多很多，就说明拉开差距了
// 方案2就是先手直接取掉1,100，那么后手没得取了，这样价值为1，这个思路可以理解为：“杀敌一千自损八百”
// 就是说， 我通过取掉一个比较小的数， 使得对方去取一个更小的数，或者直接没得取，那么这也是一种情况
//  所以，答案就是这两种情况里的 更优解
//   那么代码实现，就是把a数组从小到大排序完以后，1-n维护一遍最优解，因为f[i]是由f[i-1]转移过来的。 
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5;
int n;
int a[N],f[N];
signed main(){
	scanf("%lld",&n);
	for (register int i=1; i<=n; ++i) scanf("%lld",&a[i]);
	sort(a+1,a+n+1);
	for (register int i=1; i<=n; ++i) f[i]=max(f[i-1],a[i]-f[i-1]);
	printf("%lld\n",f[n]);
return 0;
}
```


---

## 作者：羽儇 (赞：0)

我觉得还可以这样理解

由于$A,B$都是聪明人，都会做出当前最有利于自己的方案

其本质上是让他们交叉先手，她们每次决策总会都会尽可能地拉大之间的分数差距

代码中也就这句需要注重解释：

$DP[i] = max(DP[i-1],a[i] - DP[i-1]);$

$DP[i-1]$假如取很长的子序列，其决定分数差距的只是其最小的那个数

即如果还继续取的最大差距

$a[i-1]-DP[i-1]$  :  $-DP[i-1]$是把差倒过来，譬如说，之前DP所表示的差值是$A-B$，辣么状态转换时，差值应为$B - A$,再加上此时他应该得到的值

呈上${AC}$代码
```cpp
#include <cstdio>
#include <algorithm>
#define int long long 
const int maxn = 1000010;
using namespace std;
int a[maxn],N,DP[maxn];
signed main()
{
	scanf("%lld",&N);
	for(int i = 1 ;i <= N ; i++)
	scanf("%lld",&a[i]);
	sort(a+1,a+1+N);
	for(int i = 1 ;i <= N ;i ++)
	DP[i] = max(DP[i-1],a[i] - DP[i-1]);
	printf("%lld",DP[N]);
	return 0;
 } 
```


---

## 作者：war1111 (赞：0)

[POI2010]GRA-The Minima Game

一道与博弈相关的dp，想了好长时间，才想明白。

A与B都是从大到小，取连续的一段，因为每次都是取当前拿走的元素的最小值。然后由小到大排序，f[i]表示两个人取完了，前i个元素，（先手-后手）的最大值，我一直卡在这里，我总是以为这里的先手就是A，后手就是B，正确的想法是先手与后手是相对的，在某次操作中，谁操作谁是先手，从这次操作转到下次状态，先后手会转换，f[i]=max(f[i-1],a[i]-f[i-1]);

答案就是f[n]。

标程在blog里

http://www.cnblogs.com/war1111/p/7677005.html


---

