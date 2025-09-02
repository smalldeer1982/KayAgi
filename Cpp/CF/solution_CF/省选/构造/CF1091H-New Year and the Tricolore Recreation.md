# New Year and the Tricolore Recreation

## 题目描述

Alice 和 Bob 在一个有 $n$ 行、无限多列的网格上玩游戏。每一行上有三个棋子，分别是蓝色、白色和红色。在游戏开始前以及每次移动后，必须满足以下两个条件：

- 任意两个棋子不能在同一个格子里。
- 在每一行中，蓝色棋子必须在白色棋子的左侧，红色棋子必须在白色棋子的右侧。

首先，他们选择一个正整数 $f$，该值在整个游戏过程中都有效。然后，选择先手玩家并进行第一次操作。之后两人轮流操作。无法进行操作的一方判负。

每次操作时，玩家首先选择一个整数 $k$，$k$ 必须是质数或两个（可以相同）质数的乘积。也就是说，$k$ 的最小可能取值为 $2, 3, 4, 5, 6, 7, 9, 10, 11, 13, 14, 15, 17, 19, \dots$。此外，$k$ 不能等于之前选定的整数 $f$。每回合只能在某一行进行一次操作。

如果轮到 Alice，她可以选择一个蓝色棋子，将其向右移动 $k$ 格。或者，她也可以将同一行的蓝色和白色棋子都向右移动 $k$ 格。

如果轮到 Bob，他可以选择一个红色棋子，将其向左移动 $k$ 格。或者，他也可以将同一行的白色和红色棋子都向左移动 $k$ 格。

注意，Alice 不能移动红色棋子，Bob 不能移动蓝色棋子。每次操作后，棋子的相对位置必须始终满足上述两个条件。

两位玩家都采取最优策略。给定棋盘的初始状态，分别判断 Alice 先手和 Bob 先手时，谁能获胜。

## 说明/提示

第一个样例如下：

当 Alice 先手时，她可以将蓝色和白色棋子同时向右移动 $2$ 格，变为 $2~5~9$。无论 Bob 如何操作，Alice 都能多走一步，然后游戏结束。例如，Bob 可以将红色和白色棋子同时向左移动 $2$ 格，变为 $2~3~7$。Alice 再将蓝色和白色棋子同时向右移动 $2$ 格，变为 $4~5~7$，此时已无法再移动。

如果 Bob 先手，他可以获得足够的优势获胜。例如，他可以将红色棋子向左移动 $3$ 格，变为 $0~3~6$。Alice 可以选择将蓝色棋子向右移动 $2$ 格，但 Bob 可以用 $2$ 步反制，最后棋盘变为 $2~3~4$，游戏结束。

第二个样例中，禁止步长为 $2$，但这并不妨碍 Alice 获胜！她可以将蓝色和白色棋子同时向右移动 $4$ 格，变为 $4~7~9$。此时 Bob 无法移动，因为步长 $2$ 被禁止。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
1 6
0 3 9
```

### 输出

```
Alice
Bob
```

## 样例 #2

### 输入

```
1 2
0 3 9
```

### 输出

```
Alice
Bob
```

## 样例 #3

### 输入

```
10 133
-248 -193 -187
97 101 202
-72 67 91
23 89 215
-129 -108 232
-223 -59 236
-99 86 242
-137 -109 -45
-105 173 246
-44 228 243
```

### 输出

```
Bob
Alice
```

# 题解

## 作者：chenxia25 (赞：10)

>### [洛谷题目页面传送门](https://www.luogu.org/problemnew/show/CF1091H) & [CodeForces题目页面传送门](https://codeforces.com/contest/1091/problem/H)

>题意见洛谷里的翻译。

刚看题目，心想：完了，这题可执行操作与轮到的玩家有关，不是ICG，不能用SG函数了。

这么想就自闭了~~，题目就是想迷惑你~~。游戏结束的条件是无法移动，而整个棋盘是无限宽的，游戏永远无法因棋子碰到边界而结束，只能因为两棋子紧挨无法移动而结束。也就是说，棋子的具体坐标并不重要，相对距离才重要。那么将左（右）边$2$个棋子右（左）移和将右（左）边$1$个棋子左（右）移有什么区别呢？

经过一番转化，Alice和Bob的操作都变成了将左边$1$个棋子右移或将右边$1$个棋子左移。不难发现，中间棋子永远不动。那么一行的游戏可以拆分成两个子ICG：**每次操作可将左边的棋子与中间的棋子的距离缩小${d(d}\text{是质数或是2个质数的乘积}{,d\ne f)}$，距离为$1$时不能再缩小**和**……可将右边的棋子……**。拆分开后，左和右本质上就没差别了。

因为$2$个棋子之间的距离最多是$10^5-\left(-10^5\right)=2\times10^5$，所以我们只需要求出$\forall d\in[1,2\times10^5],\mathrm{SG}(\text{左（右）棋子与中间棋子相距}d\text{时的局面})$，然后再将$1$行$2$个，共$2n$个子ICG的SG函数值异或起来，如果为$0$先手必败，否则先手必胜。

那么SG函数怎么求呢？如果等到求第$i$个局面的时候再统计后继局面的SG函数值们，那么无疑ICG的DAG中的每一条有向边都要被访问一次，而那是$\left(2\times10^5\right)^2=4\times10^{10}$级的，肯定会TLE。于是我们可以换一种思路，在求出第$i$个局面时，就把所有它的前驱局面标记一下：“你们都有一个后继局面（就是我）的SG函数值为$\mathrm{SG}(\text{第}i\text{个局面})$了！”聪明的读者可能要问了，这不也要访问每条边吗？是的。不过这种方法可以用`bitset`卡掉$32$的常数。

设所有可移动的格子数存在一个`bitset`$ok$里（可移动为$1$，否则为$0$）；`bitset`数组$hav$表示若$hav_{i,j}$为$1$，则与中间棋子相距$j$的局面有一个后继的SG函数值为$i$，否则没有。通过打表可发现，任何情况下SG函数值都不会超过$100$，那么$hav$的大小开$101$就好。那么与中间棋子相距$i$的标记操作为`hav[sg[i]]|=ok<<i;`。利用这个$hav$也可以轻松求SG函数值。至于$ok$怎么求……先跑一遍Eratosthenes筛法，再把是质数或是$2$个质数的乘积的数`set`到$ok$里，再把$f$`reset`掉。

对了，这道~~毒瘤~~题要开O3优化才能~~勉强~~卡进$4\mathrm{s}$的时限。

下面是AC代码：
```cpp
#pragma GCC optimize(3)//毒瘤O3优化
#include<bits/stdc++.h>
using namespace std;
#define SG 100//SG函数值的上限
#define DIF 200000//2个棋子的距离的上限
#define pb push_back
int taboo/*题目中的f*/,sg[DIF+1]/*sg[i]表示与中间棋子相距i的局面的SG函数值*/;
vector<int> pr;//质数列表
bitset<DIF+1> npr/*是否为合数*/,ok/*能移动的格子数*/,hav[SG+1]/*hav[i][j]表示与中间棋子相距j的局面有没有一个后继的SG函数值为i*/;
void eratosthenes(){//Eratosthenes筛法
	for(int i=2;i<=DIF;i++){
		if(!npr[i])pr.pb(i);
		else continue;
		for(int j=i<<1;j<=DIF;j+=i)npr.set(j);
	}
}
void ok_prework(){//求出ok
	int i;
	for(i=0;i<pr.size();i++)ok.set(pr[i]);//所有质数
	for(i=0;i<pr.size();i++)for(int j=i;j<pr.size();j++){//所有两个质数的乘积
		if(1ll*pr[i]*pr[j]>1ll*DIF)break;
		ok.set(pr[i]*pr[j]);
	}
	ok.reset(taboo);//不能移动taboo格
}
void sg_prework(){//求出所有SG函数值
	for(int i=1;i<=DIF;i++){
		while(hav[sg[i]][i])sg[i]++;//mex运算
		hav[sg[i]]|=ok<<i;//对前驱局面的标记操作
	}
}
int main(){
	eratosthenes();
	int n,totsg=0/*将2n个子ICG的SG函数值异或起来的结果*/;scanf("%d%d",&n,&taboo);
	ok_prework();
	sg_prework();
	while(n--){
		int a,b,c;scanf("%d%d%d",&a,&b,&c);
		totsg^=sg[b-a/*左边棋子与中间棋子的距离*/]^sg[c-b/*右边棋子与中间棋子的距离*/];//异或
	}
	printf(totsg?"Alice\nBob":"Bob\nAlice");//非0先手必胜，否则先手必败
	return 0;
}
```

---

## 作者：LJC00118 (赞：8)

发现每组游戏都是独立的，所以分开考虑

对于一组游戏的 $ b, w, r $，将 $ b $ 和 $ w $ 同时加上 $ k $，是等价于将 $ r $ 减去 $ k $ 的，也就是说，我们能用两组个数分别为 $ w - b - 1 $ 和 $ r - w - 1 $ 的石子来描述它

发现这是一个简单博弈，只需要求出 $ 0 $ 到 $ 200000 $ 的 $ sg $ 函数值即可

这题有一个很棒的性质，在 $ 0 $ 到 $ 200000 $ 之间每个数的 $ sg $ 函数值都是 $ \le 100 $ 的，我们可以轻松的用 $ bitset $ 来维护它

我们先筛出素数，在将相乘后 $ \le 200000 $ 的放入 $ bitset $ 内，将 $ f $ 这一位设为 $ 0 $，然后从 $ 0 $ 的 $ sg $ 函数值推到 $ 200000 $ 即可

```cpp
#include <bits/stdc++.h>
#define Fast_cin ios::sync_with_stdio(false), cin.tie();
#define rep(i, a, b) for(register int i = a; i <= b; i++)
#define per(i, a, b) for(register int i = a; i >= b; i--)
#define DEBUG(x) cerr << "DEBUG" << x << " >>> " << endl;
using namespace std;

typedef unsigned long long ull;
typedef long long ll;

template <typename _T>
inline void read(_T &f) {
    f = 0; _T fu = 1; char c = getchar();
    while(c < '0' || c > '9') { if(c == '-') fu = -1; c = getchar(); }
    while(c >= '0' && c <= '9') { f = (f << 3) + (f << 1) + (c & 15); c = getchar(); }
    f *= fu;
}

template <typename T>
void print(T x) {
    if(x < 0) putchar('-'), x = -x;
    if(x < 10) putchar(x + 48);
    else print(x / 10), putchar(x % 10 + 48);
}

template <typename T>
void print(T x, char t) {
    print(x); putchar(t);
}

const int N = 2e5 + 5, Max = N - 5;

bitset <N> f[100], wxw;
int sg[N], pri[N], isp[N];
int n, ff, ans, len;

void init_pri() {
	for(register int i = 2; i <= Max; i++) {
		if(!isp[i]) pri[++len] = i;
		for(register int j = 1; j <= len && i * pri[j] <= Max; j++) {
			isp[i * pri[j]] = 1;
			if(i % pri[j] == 0) break;
		}
	}
}

int main() {
	read(n); read(ff); init_pri();
	for(register int i = 1; i <= len; i++) wxw[pri[i]] = 1;
	for(register int i = 1; i <= len; i++) {
		for(register int j = i; j <= len; j++) {
			if(1ll * pri[i] * pri[j] > Max) break;
			wxw[pri[i] * pri[j]] = 1;
		}
	}
	wxw[ff] = 0; f[0] = wxw;
	for(register int i = 1; i <= Max; i++) {
		while(f[sg[i]][i]) sg[i]++;
		f[sg[i]] |= (wxw << i);
	}
	for(register int i = 1; i <= n; i++) {
		int a, b, c;
		read(a); read(b); read(c);
		ans ^= sg[b - a - 1];
		ans ^= sg[c - b - 1];
	}
	if(ans != 0) printf("Alice\nBob\n");
	else printf("Bob\nAlice\n");
	return 0;
}
```

---

## 作者：xh39 (赞：2)

本题解用的是[yiyang2006](https://www.luogu.com.cn/user/149301)的思路和[此题解](https://www.luogu.com.cn/blog/Chenxiao-Yan/CodeForces-1091H)的bitset优化。将把bitset讲得详细些。

---

前置算法:博弈论之sg函数,线性筛质数,STL-bitset基本操作

由于每行**相互独立**,我们就可以研究每一行再异或。

本题描述的移动是以棋盘为参照物,所以会觉得是不公平游戏,但如果**把中间的棋子作为参照物**,你会发现:将左棋和中棋都右移$k$相当于右棋左移$k$,其余的运动也可以推一遍发现这是**公平游戏**。

根据上述结果,每人可以将左棋右移$k$或把右棋左移$k$,然后就是公平游戏了。然后发现**中棋左右两边都是相互独立的**,于是我们又可以**分开来处理**。

就转化成了经典的取石子游戏。

所以$ans=xor\{sg[c[i]-b[i]]\;xor\;sg[b[i]-a[i]]\}(0<=i<n)$

其中$sg[i]=mex\{sg[i-a[j]]\}(0<j<i\&\&j满足题面k的要求)$

直接求时间复杂度$(c-a)^{2}$,达到了$400亿$,显然会tle。

于是考虑bitset。不枚举每个$i$来获取状态。考虑枚举状态$i-a[j]$

下面用**连边**的方式表达转移,即**可以转移就连一条边**。

一开始我们可以想到将$bitset[i][j]$表示$sg[i]=i$的**后继**状态(后继为可以转移到的状态)。

每次算完$i$号点的$sg$值后统计$bitset[sg[i]]|=pr<<i(pr为题目中的所有符合条件的k的状态压缩),sg[i]=mex\{bitset[j][i]\}$

解释一下上面的语句,若$sg[0][i]至sg[j][i]都=1$,表示$mex=(0至j)$的$j$都与$i$有边,并且$mex=j+1$时与$i$无边,那么$i$的$mex$就等于$j+1$。

有可能会有人问:$sg$数组第一维($mex$)要开多大?不会$mle$吗?

通过打表发现,$sg$函数最大为$54$,所以开到$54$就够了(代码中多开到了$65$)。

思路已经知道了代码就很好写了。所以下面的代码注释不多。

注:下面的代码在本地运行需要$8.186s$,但是提交到codeforces可以过,最大测试点用时$1746ms$。
```cpp
#include<iostream>
#include<bitset>
using namespace std;
bool mark[1000005];
int prime[1000005],tot=0;
bitset<200011> pr,last[65]; //pr质数的集合,last后继。 
int f[1000005];
int main(){ 
	int i,j,ykb,n,sum=0,a,b,c;
	for(i=2;i<=200000;i++){ //线性筛质数,不做解释。
		if(!mark[i]){
			prime[tot++]=i;
		}
		for(j=0;j<=j<200000&&i*prime[j]<200000;j++){
			mark[i*prime[j]]=1;
			if(!(i%prime[j])){
				break;
			}
		}
	}
	for(i=0;i<tot;i++){
		pr.set(prime[i],1);
	}
	cin>>n>>a;
	for(i=0;i<tot;i++){ //处理出所有符合条件且在200000以内的k。
		ykb=200000/prime[i];
		for(j=i;j<tot&&prime[j]<=ykb;j++){ //prime[i]*prime[j]<=2000000,prime[j]<=200000/prime[i]
			pr.set(prime[i]*prime[j],1);
		}
	}
	pr.reset(a);
	for(i=1;i<200000;i++){
		for(j=0;last[j][i];j++){ //找到第一个没有连边的mex,即求i的mex。
		}
		f[i]=j;
		last[j]|=pr<<i;
	}
	for(i=0;i<n;i++){
		scanf("%d %d %d",&a,&b,&c);
		sum^=f[b-a]^f[c-b];
	}
	if(sum){
		cout<<"Alice"<<endl<<"Bob";
	}else{
		cout<<"Bob"<<endl<<"Alice";
	}
	return 0;
}
```

---

## 作者：WeLikeStudying (赞：1)

- 简单讲讲，了解一些概念即可，[借鉴](https://www.luogu.com.cn/blog/command-block/bo-yi-lun-xiao-ji)。
- 部分博弈问题已经丧失了博弈论题目考验思维的目的了，如果学习它们，会限制于模板的背诵而影响深入的思考，所以不论如何，这里最多只会讲 $\text{SG}$ 函数和最基础的 $\text{Nim}$ 取石子。
- 我觉得这真的很有趣。
- 一些前置的博弈技巧先放在这里，也可以在部分简单情况下判断胜负：
- 模仿对手的策略：指如果局面出现类似的情况，占优势的一方仅仅通过模仿对手的策略（或者更确切地，做出回应使得局面回到相似的情况）就可以将对手引入必败局面，那么胜负已分，比如 $\text{Nim}$ 的偶数堆相同石子，还有围棋中著名的“模仿棋”，基于类似的思路。
- 自由度分析：指某些游戏中明显出现了拥有决定必胜还是必败的自由的局面（相对的，这种游戏玩家受限制较多的情况），那么最先到达“有自由度”的局面是必胜的。

**一些定义**
- 公平组合游戏：两人参与，参与者共享所有信息，任意时刻参与者所能做的操作与当前状态有关，与决策者无关。
- $\text{SG}$ 游戏：一类公平组合游戏，无法操作者输。
- 游戏图：如果状态 $u$ 能够转移到 $v$，则向 $u,v$ 连一条有向边。
- 对于有向无环游戏图，定义 $\text{mex}(S)=\min\{x|x\in \mathbf{N},x\notin S\}$，定义 $\text{SG}(u)=\text{mex}\{\text{SG}(v)|(u,v)\}$。
- 根据该定义，必败态的 $\text{SG}$ 值为 $0$。
- 定义游戏的和：如果一个游戏能划分为若干个互不相关的游戏，每次操作某个游戏，不能操作任何一个游戏者输，那么这个游戏就是若干游戏的和。
- 容易（？）证明：游戏的和的 $\text{SG}$ 函数是划分的游戏的函数 $\text{SG}$ 函数的异或和，即 $\text{SG}(x+y)=\text{SG}(x)\text{ xor }\text{SG}(y)$。
- 下面我们来一起玩一些简单的游戏，虽然它们并没有不平等博弈（绝大部分棋类游戏）那么有趣，但它们的结论却十分优美。

**Nim 游戏**
- 若干堆石子，每堆石子的数量有限，转移是选取任意一堆石子并拿走若干颗，无法操作者输。
- 一堆石子的 $\text{SG}(x)=x$，所以先手必胜当且仅当所有石子异或和不为 $0$。
- 变式 $1$：拿走 $[p,q]$ 个 （$1\le p\le q$），暴力求 $\text{SG}$ 函数，对于 $[0,p-1]$ 显然必败，对于 $[p,p+q-1]$ 显然必胜，接下来我们证明答案模 $p+q$ 循环：占优势的一方总是可以找到对称的策略，对于 $\text{SG}$ 函数而言，容易证明（具体的做法是像刚才那样~~打表~~归纳）：
$$\text{SG}(x)=\bigg\lfloor\frac{x\bmod (p+q)}{p}\bigg\rfloor$$
- 变式 $2$：有 $n$ 个箱子，已知每个箱子有哪些石子，每次可以打开一些箱子和取某个箱子的一些石子，不能操作者输：先手想要必胜，需要开极大的异或值为 $0$ 的箱子，问题即变为线性基。
- 变式 $3$：有 $n$ 堆石子排成一排，每次可以从第 $x$ 堆中取出若干石子放到第 $x-1$ 堆，无法操作者输：我们假设偶数堆石子的异或和代表胜利，让我们看看被判定胜利的一方是如何维持胜利的：如果有人要把奇数堆石子放到偶数堆上，那个被判定胜利的一方就会将偶数堆上多出来的石子一步都推到更前的奇数堆上，而只考虑偶数堆的问题即归结于 $\text{Nim}$。

**例题 1**
- [题目](https://www.luogu.com.cn/problem/P3185)。
- 每个盒子里有一个豆子，可以将一个盒子内部的豆子取出，放入两个盒子内部。
- 容易发现每个豆子是独立的，状态数大幅度减少，所以问题就变成了状态数 $O(n)$ 转移数 $O(n^2)$ 的动态规划问题。
- 怎么判断第一步有哪些可行呢？暴力枚举转移算 $\text{SG}$ 函数。
- 顺带一提，由于异或的性质，问题模二也不影响，所以还有一个 $O(2^n)$ 的算法，在 07 年的机子上或许过不了，[代码实现](https://www.luogu.com.cn/paste/lsgc41ax)。

**例题 2**
- [题目](https://www.luogu.com.cn/problem/P3235)。
- 有 $n$ 堆石子，每次可以选择一堆数目不小于 $f$ 的石子，将石子“几乎平均”地分成几堆，无法操作者输。
- 瓶颈在预处理上，可以用整除分块搞，[代码实现](https://www.luogu.com.cn/paste/pczrix0a)。

**例题 3**
- [题目](https://www.luogu.com.cn/problem/CF1091H)。
- 根据运动是相对的，不仅可以判断两人是平等博弈，问题还可以被划分为经典的取石子模型，两堆石子分别代表的是那三个石头的间隔。
- 但是值域太大了，直接暴力的复杂度无法接受，这个时候当然是打表~~等等 f 就是不想让我们打表~~。
- [打表代码](https://www.luogu.com.cn/paste/2s15r0yg)，我们发现 $\text{SG}$ 函数值非常小，这是一个很好的提示——使用 $\text{bitset}$ 优化。
- 我们对 $\text{SG}$ 函数取到某个值单独开一个 $\text{bitset}$，即可利用它完成一些有趣的操作，详细见于代码。
- 复杂度 $O(n^2/w)$，[代码实现](https://www.luogu.com.cn/paste/q0rdx8v9)。

---

