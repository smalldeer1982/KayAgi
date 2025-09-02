# PE Lesson

## 题目描述

Smart Beaver decided to be not only smart, but also a healthy beaver! And so he began to attend physical education classes at school X. In this school, physical education has a very creative teacher. One of his favorite warm-up exercises is throwing balls. Students line up. Each one gets a single ball in the beginning. The balls are numbered from $ 1 $ to $ n $ (by the demand of the inventory commission).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF316D3/dd5cf282ea1c98183da55e6989050cd8eabdb84c.png) Figure 1. The initial position for $ n=5 $ . After receiving the balls the students perform the warm-up exercise. The exercise takes place in a few throws. For each throw the teacher chooses any two arbitrary different students who will participate in it. The selected students throw their balls to each other. Thus, after each throw the students remain in their positions, and the two balls are swapped.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF316D3/6b5342e8a9f57fae45c7b1e47abe66718bc85450.png) Figure 2. The example of a throw. In this case there was a throw between the students, who were holding the $ 2 $ -nd and the $ 4 $ -th balls. Since the warm-up has many exercises, each of them can only continue for little time. Therefore, for each student we know the maximum number of throws he can participate in. For this lessons maximum number of throws will be $ 1 $ or $ 2 $ .

Note that after all phases of the considered exercise any ball can end up with any student. Smart Beaver decided to formalize it and introduced the concept of the "ball order". The ball order is a sequence of $ n $ numbers that correspond to the order of balls in the line. The first number will match the number of the ball of the first from the left student in the line, the second number will match the ball of the second student, and so on. For example, in figure $ 2 $ the order of the balls was ( $ 1 $ , $ 2 $ , $ 3 $ , $ 4 $ , $ 5 $ ), and after the throw it was ( $ 1 $ , $ 4 $ , $ 3 $ , $ 2 $ , $ 5 $ ). Smart beaver knows the number of students and for each student he knows the maximum number of throws in which he can participate. And now he is wondering: what is the number of distinct ways of ball orders by the end of the exercise.

## 样例 #1

### 输入

```
5
1 2 2 1 2
```

### 输出

```
120
```

## 样例 #2

### 输入

```
8
1 2 2 1 2 1 1 2
```

### 输出

```
16800
```

# 题解

## 作者：yuzhechuan (赞：10)

小清新思维题

---

### 题解：

首先很容易发现答案与顺序无关，只与"1","2"的数量有关，并记"1"的个数为$a$，"2"的个数为$b$

首先考虑$b=0$的情况

设$f[i]$表示剩余$i$个"1"时的排列数

很容易得到转移$f[i]=f[i-2]\times (i-1)+f[i-1]$，表示$(i-1)$种方法选1个互换，1种方法选自己保持不变

考虑扩展到$b\ne 0$的情况

我们把2次交换的限制看成一次主动交换和一次被动交换

那我们就可以让$b$个"2"都先使用一次主动交换

那么第一个"2"可以从$n$个中选一个

第二个"2"可以从$n-1$中选一个

第三个"2"可以从$n-2$中选一个

。。。以此类推

这样$b$次交换后会剩下正好$a$个"1"（可以用数学轻松证明）

于是答案$ans=f[a]\times \prod\limits_{i=1}^{b}(n-i+1)$

---

### 代码：

```cpp
#pragma GCC optimize(3,"Ofast","inline")
#pragma GCC target("avx,avx2")
#include <bits/stdc++.h>
using namespace std;
template<class t> inline t read(t &x){
    char c=getchar();bool f=0;x=0;
    while(!isdigit(c)) f|=c=='-',c=getchar();
    while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
    if(f) x=-x;return x;
}
template<class t> inline void write(t x){
    if(x<0) putchar('-'),write(-x);
    else{if(x>9) write(x/10);putchar('0'+x%10);}
}

#define int long long

const int mod=1e9+7,N=1e6+5;
int n,ans=1,cnt,f[N];

signed main(){
	read(n);
	for(int i=1,x;i<=n;i++){
		read(x);
		if(x==1) cnt++;
	}
	f[0]=f[1]=1;
	for(int i=2;i<=cnt;i++) f[i]=(f[i-2]*(i-1)+f[i-1])%mod;
	for(int i=n;i>cnt;i--) ans=ans*i%mod;
	write(ans*f[cnt]%mod);
}
```

---

## 作者：zzr8178541919 (赞：9)


感觉大佬们大多都没有讲得很清，这里提供一个较为严谨且好理解的方法。

首先阅读题面，发现是一个排列的交换问题。这是一种比较常见的题型了，看到这种题，一般都要想到：**环**！

**交换与环：** 假设当前有一个排列，排列为：$1,2,3...,n-1,n$。现在对这个环进行操作，每次选择两个数$(x,y)$，将它们交换，交换若干次后，会得到一个新的排列。对于$1$到$n$中的每个数$i$，假设最后$i$号点到达的位置是$p_i$，则从$i$到$p_i$连一条有向边。连完这些边发现，这形成了若干个环（包括自环）。

通过这些环，我们知道了，初始的点最终要到达哪个位置。

回到本题，发现本题加了一个限制，即：每个点的最多交换次数为$1$次或$2$次，还是从环入手，考虑每个点最多交换次数为$1$次或$2$次时，对于一个合法的交换操作，环需要满足的条件是什么？

为了方便讲述，这里将图中的$a_i=1$的点设为白点（球），$a_i=2$的点设为黑点（球），不交换的情况可以当成自己和自己交换，即：每个点的交换次数需使用完。

交换操作合法当且仅当**环需要满足的条件为：** 一个环中最多两个白点。

于是问题变成了：统计符合上述条件的方案数，这个方案数怎么求呢？我们还要寻找一些性质。

进一步推理可以发现：白球的交换是很受限制的，而黑球相对“自由得多”。如果一个白球$A$和一个白球$B$交换，白球$B$的最终位置就定了，不能再换到别的地方。而如果一个黑球被交换了一次，它还可以选择交换到其他的位置，再进一步，可以发现一个重要性质！

**性质：** 对于每一个黑球，最终都可以换到$n$个位置中的任意一个位置。

白球并不满足上述性质。

于是我们可以从黑球入手，先把它们最终到达的位置选完。选法方案数为：
$$
\frac{n!}{(n-cnt2)!}
$$

还记得要求什么吗？我们要求：满足一个环中最多两个白点的排列的操作方案数。

现在我们和环联系起来，黑点的去处是已知的，我们可以先把它们和它们的去处连好边，得到一个类似这样的图：

![](https://cdn.luogu.com.cn/upload/image_hosting/vbjb141w.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

得到的环无非是三种类型：

- 黑点成环
- 以白点结尾的链
- 单独的白点。

不管图长成什么样，可以确定的是：任意两个白点不在一个连通块中。我们现在要做什么呢？我们需要给每个白点分配一个去处（可以是自己，必须是含有白点的联通块），使其是一个合法的交换序列。

自己成环表示自己不与其它的点交换，两个连通块合并表示交换，对于两个给定的连通块，它们的合并有且只有一种方案，且合并后一定不会和第三个连通块合并（因为已经有两个白点了）。

这部分可以用$dp$解决。

$dp_i$表示给$i$个白点所在连通块分配去处的方案数，考虑第$i$个白点所在的连通块，有两种情况：

- 它自己成环，变成给$i-1$个白点所在连通块分配去处，$dp_i=dp_i+dp_{i-1}$
- 它找一个连通块成环，从$i-1$个含白点连通块中找一个与它匹配，再给$i-2$个白点所在连通块分配去处。$dp_i=dp_i+(i-1) \times dp_{i-2}$

这也就是其它题解中所说的那个线性递推，初始条件：$dp_0=1,dp_1=1$。

最终答案就是：$dp_{cnt1}\times \frac{n!}{(n-cnt2)!}$，问题得到完美解决！

```cpp

#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define reg register
#define x1 x11
#define x2 x22
#define y1 y11
#define y2 y22
#define z1 z11
#define z2 z22
const int mod=1e9+7;
const int INF=2e16;
const int maxn=1e6+5;
const double Pi=acos(-1.0);
double Exp=1e-6;
inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0' || ch>'9')
	{
	    if(ch=='-')
	        f=-1;
	    ch=getchar();
	}
	while(ch>='0' && ch<='9')
	{
	    x=x*10+ch-'0';
	    ch=getchar();
	}
	return x*f;
}
int n;
int a[maxn];
int cnt1=0,cnt2=0,ans=1;
int dp[maxn];
signed main()
{
	n=read();
	for(int i=1;i<=n;i++)
	{
		a[i]=read();
		if(a[i]==1)
			cnt1++;
		else
			cnt2++;
	}
	dp[0]=1;
	dp[1]=1,dp[2]=2;
	for(int i=3;i<=n;i++)
		dp[i]=(dp[i-1]+dp[i-2]*(i-1))%mod;
	for(int i=1;i<=cnt2;i++)
		ans=ans*(n-i+1)%mod;
	ans=ans*dp[cnt1]%mod;
	printf("%lld\n",ans);
	return 0;
}

/*
8
2 0 2 0 2 2 0 0
*/
```


---

## 作者：do_it_tomorrow (赞：4)

## 前言

发现这个[题解](https://www.luogu.com.cn/article/fggpebt5)的组合意义好像有问题，解释不了放弃的情况，~~但是对面作者好像是 $10$ 级钩大蛇~~。

似乎向上面的题解一样理解还需要考虑更多，反正我看不懂，那个题解也没说。

而且第 $i$ 个人有 $n-i+1$ 个位置就是错的。

为 $\text{uid}=114514$ 大佬的“严谨”的题解添加了一些证明并加入了一下自己的理解。

## 思路

发现换来换去的很麻烦，如果按照操作去考虑那么很难去重，直接从答案入手判断合法。

设第 $i$ 个点最后到达了 $p_i$，那么**把 $i$ 向 $p_i$ 连边**，需要注意是考虑结果而不是过程，所以即使 $t_i=1$ 也有可能 $i$ 的度为 $2$。

手玩发现一个性质，一些交换是合法的当且仅当一个环内最多存在 $2$ 个 $t_i=1$ 的点。

**下面考虑证明这个性质。**

考虑通过构造的思想证明。

因为交换的位置并没有限制，所以输入的顺序对答案没有影响，对答案影响的只有 $t_i=1$ 和 $t_i=2$ 的个数，我们假设分别有 $x,y$ 个。

不妨假设 $1$ 到 $x$ 都是 $t_i=2$ 的人，而 $x+1$ 到 $n$ 都是 $t_i=1$ 的人。

不妨先把 $1$ 和 $x+1$ 合并到一起，操作最少的显然就是让他们两人交换手中的球，经过操作 $1$ 就只能交换 $1$ 次了，而 $p_{x+1}=1$ 就已经确定了。

如果需要让这个环内添加更多的元素，那么显然需要操作 $1$ 号跟别人交换。

如果 $1$ 号与 $x+2$ 这样只能交换一次的人交换，那么显然 $p_1=x+2$ 和 $p_{x+2}=x+1$ 都已经确定了，所以最后形成的环就是 $1\to x+2\to x+1\to 1$，只含有 $2$ 个 $t_i=1$ 的节点。

如果 $1$ 号与 $2$ 号这样可以交换两次的人交换，那么 $p_1=2$ 就确定了，而 $2$ 号又只能操作一次，场面与 $1$ 号操作的情况就一样了，所以继续回到上面的情况讨论。

现在回到最开始，如果 $1,2$ 这样本来就可以还两次的点那么他们就相当于合并成为了一个 $t_i=2$ 的点，对上面的证明没有影响。

感性理解一下上面的操作显然可以通过“合并”操作搞出所有的操作，所以综上所述命题得证。

**形成的完整的图不可能有链，认为形成的链的两端分别是 $t_i=1$ 的思路是错误的！！！**

所以现在问题转化成为了满足上面要求的本质不同的基环树的计数问题。

因为上面的命题对 $t_i=2$ 的点并没有要求，那么那我们把全部 $y$ 个 $t_i=2$ 的点 $p$ 随便乱排显然都会有合法的答案。

**下面先只考虑 $t_i=2$ 的贡献。**

考虑分析一下原因，这样只操作 $t_i=2$ 的情况会形成一下的图：

- $t_i=2$ 的点自己成为一个大环。
- 一堆 $t_i=2$ 的点形成一条链最终连接一个 $t_i=1$ 的节点。
- 一堆没有边的 $t_i=1$ 的节点。

如果只关注有 $t_i=1$ 的点，那么上述的第 $2$ 种情况就可以缩为一个 $t_i=1$ 的节点。

接下来的操作就只与 $t_i=1$ 的点有关了，之前的操作都和后面的操作独立。

容易发现第一种操作的方案数为 $\large{A^y_n}$，根据乘法原理答案就是前后两个方案相乘。

**下面开始考虑 $t_i=1$ 的贡献。**

现在问题就转化成了将 $x$ 个不同的元素分成若干组，每一组的元素个数不大于 $2$ 的本质不同的分法。

设 $f_i$ 表示已经处理了 $i$ 个元素的方案数，那么有转移方程：

$$f_{i}=f_{i-1}+f_{i-2}\times (i-1)$$

- $f_{i-1}$ 表示自己单独成为一组，所以直接把前面的方案加进来就行了。
- $f_{i-2}\times (i-1)$ 表示在前面的 $i-1$ 个元素中选择 $1$ 个元素与 $i$ 放到一个组里，剩下 $i-2$ 个元素随便分组的方案数。

所以最终的答案就是 $\large{A_n^y}\normalsize \times f_{y}$。

## 代码

[Submission #289112469 - Codeforces](https://codeforces.com/contest/316/submission/289112469)

---

## 作者：Mr_Wu (赞：3)

我来当小丑了

----

### 题意

初始一个大小为 $n$ 的排列 $p_i=i$，并给定一个最大交换次数 $a_{1\cdots n}$。

每次可以选择 $u,v (u\not= v)$，将 $p_u,p_v$ 交换，并将 $a_u,a_v$ 都减 1。

在所有 $a_i$ 都非负的前提下，最后可能的 $p$ 的个数是？输出它模 $10^9+7$ 的值。

$n\le 10^6,a_i\in\{1,2\}$。

### 题解

我们考虑一个置换由若干个环组成，对于每个环，能交换过来当且仅当 $a_i=1$ 的个数不多于 2，这可以通过 ~~打表~~ 构造证明。

那么我们考虑我们要求的就是

$$
\begin{aligned}
& A!B![x^A][y^B] \exp \Big(\sum_{i\le 2,i+j>0} \frac{(i+j-1)!}{i!j!}x^iy^j \Big) \\
& = A!B![x^A][y^B] \exp \Big( \ln \frac{1}{1-y} + \frac{x}{1-y}+\frac{x^2}{2(1-y)^2} \Big) \\
&= A!B![x^A][y^B]\frac{1}{1-y}f(\frac{x}{1-y})
\end{aligned}
$$

其中 $f(x)=\exp (x+\frac{x^2}{2})$，两边求导可得 $f'(x)=(1+x)f$，所以

$$
if_i=f_{i-1}+f_{i-2},f_0=1
$$

所以我们最后要求的就是

$$
A!B!f_A[y^B](\frac{1}{1-y})^{A+1}=A!B!f_A\binom{A+B}{A}=f_An!
$$

时间复杂度 $O(n)$。

---

## 作者：sinestrea (赞：2)

既然所有人都能和任意人进行交换，那么就说明和 $1, 2$ 的顺序是无关，也就是说只和 $1, 2$ 的数量有关。

那么我们用 $cnt1$ 和 $cnt2$ 来表示 $1$ 和 $2$ 在输入中出现的次数。

我们用 $dp_i$ 来表示 $i$ 个 $1$ ,这 $cnt1$ 个人可以和自己玩，也可以和别人交换，那么我们可以得出动态转移方程 $dp_i = dp_{i - 2} \times (i - 1) + dp_{i - 1}$。

那么能交换两次的人选法为 $n^{\underline{cnt2}}$，即 $n \times (n - 1) \times \cdots \times (n - cnt2 + 1)$。

那么答案就是 $dp_{i} \times n^{\underline{cnt2}}$。

```cpp
#include <bits/stdc++.h>

const int MAX = 1111111, MOD = 1e9 + 7;

long long n{}, ans{}, num{}, dp[MAX] = {1, 1}, cnt[3]{};

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> num, cnt[num]++;
    for (int i = 2; i <= cnt[1]; i++) dp[i] = dp[i - 2] * (i - 1) + dp[i - 1], dp[i] %= MOD;
    ans = dp[cnt[1]];
    for (int i = n - cnt[2] + 1; i <= n; i++) ans *= i, ans %= MOD;
    std::cout << ans;
}
```

---

## 作者：Unnamed114514 (赞：1)

首先你这个方案数只跟 $1$ 和 $2$ 的数量有关，而跟具体的位置无关，所以求出 $1/2$ 的出现次数 $cnt_1/cnt_2$。

先求出 $f_i$ 表示只有 $i$ 个 $1$ 的方案，容易想到讨论第 $i$ 个人是否交换得到转移式 $f_i\gets f_{i-1}+(i-1)f_{i-2}$。

然后定义 $g_i$ 表示有 $i$ 个 $2$ 的方案数，容易想到 $g_0=f_{cnt_1}$。

考虑只有 $1$ 的时候的形式：对于每个 $1$，它只能是保持不变，或者是用它的初始值去覆盖了其它的值。

如果把不变理解成覆盖自己的话，那么这个时候就有一个关键的结论：**每个位置都会覆盖一个位置。**

然后你会发现 $2$ 比较特殊，因为它可以交换两次，也就是说，它可以在被修改初值后再去修改其它的初值。

那么对于 $g$ 的转移，相当于找一个 $2$，看它的初值会覆盖哪个的初值。。

首先就是它自己，然后就是那些没有被其它位置覆盖的位置，对于已经被覆盖的位置，它可以先被原来覆盖这个位置的值覆盖，然后再去覆盖这个位置。

也就是说，它可以覆盖现有的每个位置，即 $g_i\gets(cnt_1+i)g_{i-1}$。

答案就是 $g_{cnt_2}$，时间复杂度 $O(n)$。

---

## 作者：傅天宇 (赞：1)

[luogu's link](https://www.luogu.com.cn/problem/CF316D3)

[CF's link](https://codeforces.com/problemset/problem/316/D3)

#### 题意：

有 $n$ 个小朋友手里各有 $1$ 个球，其中每个人只能把手里的球和别人交换 $1$ 或 $2$ 次。输入每个人可交换的次数，求可能的交换方案数。

#### Solution：

先对 $1,2$ 分别做出统计。

1. $b=0$，设 $f_{i}$ 表示剩余 $i$ 个 $1$ 时排列数。易得 $f_i=f_{i-2}\times (i-1)+f_{i-1}$。
2. $b\neq0$，第一个 $2$ 可以从 $n$ 中选一个，第二个 $2$ 可以从 $n-1$ 中选一个，以此类推。

所以答案即为 $f_{sum1}\times \Pi_{i=1}^{b}{n-i+1}$。

#### Code：

```cpp
/*
 * @Author: FuTianyu 
 * @Date: 2020-12-03 14:34:54 
 * @Last Modified by: FuTianyu
 * @Last Modified time: 2020-12-03 14:48:53
 */
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define REP(i,a,b) for(int i=a;i>=b;i--)
/*
快读快输
*/
const int N=1e6+5;
const int mod=1e9+7;
int n,sum1,sum2,f[N];
signed main(){
	n=read();
	FOR(i,1,n){
		int x=read();
		if(x==1) sum1++;
		else sum2++;
	}
	f[0]=f[1]=1;
	FOR(i,2,sum1) f[i]=(f[i-1]+f[i-2]*(i-1)%mod)%mod;
	int sum=1;
	FOR(i,1,sum2) sum=sum*(n-i+1)%mod;
	write(sum*f[sum1]%mod);
	return 0;
}
```



---

## 作者：LCuter (赞：1)

## CF316D 题解

##### $\text{Description}$

给定一个序列 $\{t_n\},\forall i,t_i\in\{1,2\}$。问有多少个排列 $p$ 满足 $[1,2,\cdots,n]$ 可以通过有限制地交换任意两位置地数得到，其中第 $i$ 个位置至多只能被交换 $t_i$ 次。

$1\le n\le 10^6$

##### $\text{Solution}$

首先考虑怎样判定一个排列 $p$ 满足条件。

注意到任意两位置可以交换，考虑对于所有 $i$，连一条有向边 $i\rightarrow p_i$，则可以得到一张由若干不相交的简单环组成的有向图。

观察可知若一个排列满足条件，则其对应的图中，任意简单环中 $t$ 为 $1$ 的点不超过两个，可以通过简单构造证明。

问题转换为把这些数分成若干个圆排列，要求每个圆排列中至多有 $2$ 个 $t_i$ 为 $1$ 的点。

考虑先把 $t_i$ 为 $1$ 的点放好，设有 $a$ 个 $t_i$ 为 $1$ 的点，我们要将其分为 $b$ 个圆排列。

设有 $p$ 个圆排列有 $2$ 个这样的点，$q$ 个圆排列只有一个这样的点，解二元一次不等式可得 $p=a-b,q=2b-a$。

我们先把这 $p$ 个圆排列选好，然后剩下的点都是孤立点，由于圆排列间无序，故有：
$$
\frac{A^{2(a-b)}_{a}}{2^{a-b}(a-b)!}
$$
$2^{a-b}$ 消除圆排列内的顺序带来的影响，$(a-b)!$ 消除圆排列间的顺序带来的影响。

剩下 $t_i$ 为 $2$ 的点就可以按照求斯特林数的方式随意插入，故最终答案为：
$$
\frac{n!}{a!}\sum_{b=\lceil\frac{a}{2}\rceil}^a\frac{A^{2(a-b)}_{a}}{2^{a-b}(a-b)!}
$$

##### $\text{Code}$

```
#include<bits/stdc++.h>
#define REG register
using namespace std;
inline void read(int& x){
	static char c;
	while(!isdigit(c=getchar()));x=c^48;
	while(isdigit(c=getchar()))x=(x*10)+(c^48);
}

const int Mod=1000000007,N=5000005;

int T,n,tmp;

int Pow(int a,int b){
	int ans=1;
	while(b){
		if(b&1) ans=1ll*ans*a%Mod;
		a=1ll*a*a%Mod,b>>=1;
	}
	return ans;
}

int Fac[N],Iac[N],_2Pow[N];
inline void Init(){
	int Inv=Pow(2,Mod-2);
	Fac[0]=Iac[0]=_2Pow[0]=1;
	for(REG int i=1;i<=N-4;++i) Fac[i]=1ll*Fac[i-1]*i%Mod,_2Pow[i]=1ll*Inv*_2Pow[i-1]%Mod;
	Iac[N-4]=Pow(Fac[N-4],Mod-2);
	for(REG int i=N-5;i;--i) Iac[i]=1ll*Iac[i+1]*(i+1)%Mod;
}
inline int Binom(int n,int m){return 1ll*Fac[n]*Iac[m]%Mod*Iac[n-m]%Mod;}

int Ans,t;

inline void Work(){
//	freopen("throw.in","r",stdin);
//	freopen("throw.out","w",stdout);
	Init();
	T=1;
	while(T--){
		t=Ans=0;
		read(n);
		for(REG int i=1;i<=n;++i) read(tmp),t+=tmp==1;
		for(REG int i=(t-1)/2+1;i<=t;++i) Ans=(Ans+1ll*Fac[t]*Iac[2*i-t]%Mod*_2Pow[t-i]%Mod*Iac[t-i]%Mod)%Mod;
		if(!t) ++Ans;
		Ans=1ll*Ans*Fac[n]%Mod*Iac[t]%Mod;
		printf("%d\n",Ans);
	}
}

int main(){Work();}
```



---

## 作者：Grisses (赞：0)

[题面](https://www.luogu.com.cn/problem/CF316D3)

---

这题怎么可能只有 2400 啊？

---

容易发现答案只与 $a_i=1,a_i=2$ 的 $i$ 的数量有关，我们考虑分别将其记为 $a1,a2$。

考虑最终结果的排列满足什么性质，手玩一下可以发现这些排列中每一个环内最多只有两个数 $a_i=1$。

先考虑给所有 $a1$ 个 $a_i=1$ 的点的分组情况，每个点可以独自成一组，也可以和另一个在一个环里，即有 $f_i=f_{i-1}+(i-1)\times f_{i-2}$。表示第 $i$ 个点独立或是与前 $i-1$ 个点中的某一个在一起。

接下来考虑将剩的 $a2$ 个点插到环里去，结合第一类斯特林数的递推方法，对于第 $i$ 个点，有 $1+(a1+i-1)$ 种选择，代表自成一环或跟在前面某一个点后边。

所以总方案数为 $f_{a1}\times \prod\limits_{i=a1+1}^ni$

---

代码：
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int n,a1,a2,a[1000005],dp[1000005];
signed main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	for(int i=1;i<=n;i++)if(a[i]==1)a1++;else a2++;
	dp[0]=dp[1]=1;
	for(int i=1;i<=a1;i++)dp[i]=(dp[i-1]+(i-1)*dp[i-2])%mod;
	for(int i=n;i>=n-a2+1;i--)dp[a1]=dp[a1]*i%mod;
	printf("%lld",dp[a1]);
	return 0;
}
```

---

## 作者：__ycx2010__ (赞：0)

## Solution

假设第 $i$ 个球最终在 $p_i$ 位置上，则从 $i$ 向 $p_i$ 连边，于是我们得到了一个只存在环的有向图。

首先有结论每一个环内的白点个数不多于 $2$。

设 $f_i$ 表示 $i$ 个白点排列的数量，容易得到递推式 $f_i = f_{i-2} \cdot (i-1)+f_{i-1}$。

于是 $ans = f_{cnt1} \cdot A_n^{cnt2}$。

那么为什么呢？

由于是环的形式，所以段换成链，将白点放在最后面。

后面的 $A_{n}^{cnt2}$ 表示将所有黑点一个互不相同的 $h_i(1\leq h_i \leq n)$ 表示，$i$ 点的后继，若 $h_i=i$ 或者 $h_i$ 为白点，则表示一条链终止了，否则找到一个黑点作后继。

所以这样得出的方案与原图合法的只存在环的有向图一一对应。

## code

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 10, mod = 1e9 + 7;
int f[N];

int main() {
	int n, cnt1 = 0, cnt2 = 0;
	scanf("%d", &n);
	for (int i = 1; i <= n; i ++ ) {
		int x;
		scanf("%d", &x);
		if (x == 1) cnt1 ++ ;
		else cnt2 ++ ;
	}
	f[0] = 1, f[1] = 1;
	for (int i = 2; i <= cnt1; i ++ ) f[i] = (1ll * f[i - 2] * (i - 1) % mod + f[i - 1]) % mod;
	int ans = f[cnt1];
	for (int i = n; i >= n - cnt2 + 1; i -- ) ans = 1ll * ans * i % mod;
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：chufuzhe (赞：0)

可以分开讨论交换一次的人和交换两次的人。

因为只要交换的方案不同，最终的排列就不同，所以可以求不同的交换方案数。

对于交换一次的人，他可以和自己玩，也可以找一个人玩。

所以设 $f[i]$ 表示有 $i$ 个只能交换一次的人的交换方案数，

$f[i]=f[i-1]+(i-1)*f[i-2]$

对于能交换两次的人，他们可选择的交换方案共有 $a!$ ( $a$ 表示能交换两次的人的个数) 种。

最后的答案就是两种方案数的积。

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read() //输入量较大，要用快读
{
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int f[1000005]; //定义，f[i]表示i个只能交换一次的人的交换方案数
int main()
{
	int n = read(), cnt1 = 0; //cnt1表示只能交换一次的人的个数，不要和上文中的cnt混淆
	for(int i = 1; i <= n; i++) {
		cnt1 += !(read() - 1); //记录只能交换一次的人的个数
		//当read()=1时，read()-1=0，!(read()-1)为1，所以当read()为1时，cnt++
	}
	f[0] = f[1] = 1; f[2] = 2; //初始化
	for(int i = 3; i <= cnt1; i++) {
		f[i] = (f[i - 1] + f[i-2] * 1ll * (i - 1) % 1000000007) % 1000000007; //可以和自己玩，也可以找一个人玩
	}
	int s = 1; //s表示能交换两次的人的交换方案数
	for(int i = cnt1 + 1; i <= n; i++) { //除了cnt1个只能交换一次的人，其他都是能交换两次的人
		s = s * 1ll * i % 1000000007; //求阶乘
	}
	cout << s * f[cnt1] << endl; //最后的答案就是两种方案数的积
	return 0;
}
```


---

## 作者：fisheep (赞：0)

## 思路：
问题等价于由多少种排列按照抛球的方式能够还原成排列 $1,2,3, ⋯ ,n$ 。

由于本题是任意两个元素进行交换,我们可以发现，为了还原一个轮换，轮换中最多只能有两个位置的$t$值为 $1$，其它位置都要求$t$值为$2$（因为$t$值的上限不超过 $2$）。

而且对于任意的 $t = 1$ 的位置不超过两个的轮换，都可以进行还原，因此我们转化成计数问题——有多少个轮换符合上述条件。

设有 $a$ 个$ t = 1$ 的位置和 $b$ 个$ t = 2$ 的位置时，排列方案数为 $C(a, b)$。先考虑 $b = 0$ 的情况，则第 $a$ 个人可以选择自己组成一个轮换，也可以与前面某一个人组成一个轮换，因此有 $C(a, 0) = C(a − 1,0) + (a − 1) × C(a − 2,0)$。存在 $t = 2$ 的位置时，注意到这个位置可以插入轮换中任意一个数后面，也可以单独成为一个轮换，因此有 $C(a, b) = C(a, b − 1) × (a + b)$对每组数据，分别统计出 $t= 1,2$ 的人数即可。

## Code:
```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
#define int long long
inline int read(){
  int x=0,f=1;
  char ch=getchar();
  while(ch>'9'||ch<'0'){
    if(ch=='-') f=-1;
    ch=getchar();
  }
  while(ch>='0'&&ch<='9'){
    x=(x<<1)+(x<<3)+(ch^48);
    ch=getchar();
  }
  return x*f;
}

const int N=1010,mod=1e9+7;
int n,t[3]={};
long long ans=1,a,b,c;
signed main(){
	int T;
	// T=read();
	// while(T--){
		t[1]=t[2]=0;
		ans=1;
	n=read();
		for(int i=1,x=0;i<=n;++i){
			x=read();
			++t[x];
		}
		for(int i=t[1]+1;i<=t[1]+t[2];++i){
			ans=ans*i%mod;
    }
		a=1,b=1;
		for(int i=2;i<=t[1];++i){
			c=(b+(i-1)*a)%mod;
			a=b,b=c;
		}
	printf("%lld",ans*b%mod);
	// }
	return 0;
}

```

---

## 作者：DegChuZm (赞：0)

> 题意简述：有 $n$ 个同学，第 $i$ 个同学手里有一个编号为 $i$ 的球。每次可以交换两个同学手中的球。现给定每个同学与他人交换球的次数的上限（上限不大于 $2$ ），问若干次交换后球有多少种可能的排列。答案对 $10^9+7$ 取模。

这题是真好题。

### sol

发现这个东西换来换去好复杂，不如直接考虑结尾状态。

如果 $i$ 的球最终扔到了 $p_i$ 的位置，那么连一条 $i$ 连向 $p_i$ 的单向边。

然后不难发现每个点初始的位置其实没太大影响，设 $x$ 个人为 $2$，然后把前 $x$ 全放成 $2$ 后 $x+1$ 到 $n$ 全放成 $1$。

引理：每个环上最多存在 $2$ 个 $t_i=1$ 的人，$t_i$ 为交换次数。

怎么证明：

**如果**两个 $t_i$ 等于 $1$ 的互相交换，两个都确定了。

**如果**一个 $t_i=1$ 的和 $t_j=2$ 的交换，那么确定了一个 $t_i=1$ 的，$t_j=2$ 变成 $1$，然后这时如果跟 $t_k=1$ 的换就是第一种情况了，否则就只是环变长一点而已。

**如果**两个 $t_i=2$ 的交换，，，更简单，就是把两个 $t_i=2$ 的合成成了一个 $t_i=2$ 的。

然后就证完了。

于是考虑通过这个去算总方案数：

先考虑 $t_i=2$ 连成几个大环的情况： $A^y_n$，就是每个 $t_i=2$ 的点可以乱扔到任何一个位置上。

然后接下来带入 $t_i=1$。

如果完全不考虑 $t_i=2$ 时，$t_i=1$ 就只会出现自环和两个 $t_i=1$ 组成的小环。

然后发现在上面两种情况组成的环中怎么加 $t_i=2$ 的点**都不会有影响**，所以这两个问题就独立了！

于是来求只考虑 $t_i=1$ 的情况组成的环的方案数。

设 $f_i$ 表示有 $i$ 个 $t_i=1$ 的方案数：

转移即为 $f_i=f_{i-1} + f_{i-2}\times(i-1)$。

意思为：单独成立一个环 和 选择之前未选择的一个点跟它组成一个环。

答案就是 $t_i=1$ 和 $t_i=2$ 的相乘就好了。

### code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int n,m,f[1000001],x;

signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x;
		if(x==1) m++;
	}
	int ans=1;
	for(int i=n;i>m;i--){
		ans=ans*i%mod;
	}
	f[0]=f[1]=1;
	for(int i=2;i<=m;i++){
		f[i]=(f[i-1]+f[i-2]*(i-1)%mod)%mod;
	}
	cout<<f[m]*ans%mod;
	return 0;
}
```

---

