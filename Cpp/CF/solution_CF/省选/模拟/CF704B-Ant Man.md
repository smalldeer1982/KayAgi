# Ant Man

## 题目描述

Scott Lang is at war with Darren Cross. There are $ n $ chairs in a hall where they are, numbered with $ 1,2,...,n $ from left to right. The $ i $ -th chair is located at coordinate $ x_{i} $ . Scott is on chair number $ s $ and Cross is on chair number $ e $ . Scott can jump to all other chairs (not only neighboring chairs). He wants to start at his position (chair number $ s $ ), visit each chair exactly once and end up on chair number $ e $ with Cross.

As we all know, Scott can shrink or grow big (grow big only to his normal size), so at any moment of time he can be either small or large (normal). The thing is, he can only shrink or grow big while being on a chair (not in the air while jumping to another chair). Jumping takes time, but shrinking and growing big takes no time. Jumping from chair number $ i $ to chair number $ j $ takes $ |x_{i}-x_{j}| $ seconds. Also, jumping off a chair and landing on a chair takes extra amount of time.

If Scott wants to jump to a chair on his left, he can only be small, and if he wants to jump to a chair on his right he should be large.

Jumping off the $ i $ -th chair takes:

- $ c_{i} $ extra seconds if he's small.
- $ d_{i} $ extra seconds otherwise (he's large).

Also, landing on $ i $ -th chair takes:

- $ b_{i} $ extra seconds if he's small.
- $ a_{i} $ extra seconds otherwise (he's large).

In simpler words, jumping from $ i $ -th chair to $ j $ -th chair takes exactly:

- $ |x_{i}-x_{j}|+c_{i}+b_{j} $ seconds if $ j&lt;i $ .
- $ |x_{i}-x_{j}|+d_{i}+a_{j} $ seconds otherwise ( $ j&gt;i $ ).

Given values of $ x $ , $ a $ , $ b $ , $ c $ , $ d $ find the minimum time Scott can get to Cross, assuming he wants to visit each chair exactly once.

## 说明/提示

In the sample testcase, an optimal solution would be ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF704B/4c6f96e15c54bfd937ff89197525b5068744a884.png). Spent time would be $ 17+24+23+20+33+22=139 $ .

## 样例 #1

### 输入

```
7 4 3
8 11 12 16 17 18 20
17 16 20 2 20 5 13
17 8 8 16 12 15 13
12 4 16 4 15 7 6
8 14 2 11 17 12 8
```

### 输出

```
139
```

# 题解

## 作者：xht (赞：27)

> [CF704B Ant Man](https://codeforces.com/contest/704/problem/B)

## 题意

- 有 $n$ 个元素，第 $i$ 个元素有五个参数 $x_i,a_i,b_i,c_i,d_i$。
- 你需要求出一个 $1 \sim n$ 的排列 $p$，满足 $p_1 = s, p_n = e$，同时最小化这个排列的权值。
- 一个排列的权值为 $\sum_{i=1}^{n-1} f(p_i, p_{i+1})$，其中 $f(i,j)$ 的值有两种情况：
  - 若 $i > j$，则 $f(i,j) = x_i - x_j + c_i + b_j$。
  - 若 $i < j$，则 $f(i,j) = x_j - x_i + d_i + a_j$。
- $n \le 5 \times 10^3$，$s \ne e$，$1 \le x_1 < x_2 < \cdots < x_n \le 10^9$，$1 \le a_i,b_i,c_i,d_i \le 10^9$。

## 题解

考虑贪心，对 $s \to e$ 建立一个链表。

从小到大考虑 $1 \sim n$ 中每个不是 $s,e$ 的元素，枚举它往链表中插入的位置，从最优的位置插入即可。

为什么是对的呢？

注意到，元素的贡献只和左右两个元素的相对大小有关。

先不考虑 $s,e$ 的情况，显然元素是从小到大插入的。

讨论每次插入一个元素时贡献的变化情况，设此时 $x$ 要插入 $y \to z$ 的位置，不妨设 $x > y > z$。

原本的贡献有：

- $y$ 往小
- 大往 $z$

插入 $x$ 后的贡献由：

- $y$ 往大
- 大往 $z$
- 小往 $x$
- $x$ 往小

其中「大往 $z$」的贡献不变，直接消掉；「小往 $x$」和「$x$ 往小」的贡献是固定的，不管从哪儿插入这个贡献都一定存在，因此可以忽略。

即每次会把一个「$y$ 往小」的贡献变成「$y$ 往大」的贡献。

同理，若 $x > z > y$，则每次会把一个「小往 $z$」的贡献变成「大往 $z$」的贡献。

换句话说，对于与「大」相关的贡献，将永远无法被去掉；对于与「小」相关的贡献，在每一次插入操作时，会把原有的一个与「小」相关的贡献变成与「大」相关的贡献，然后加入两个新的与「小」相关的贡献。

这就相当于，有一个集合存储着所有「小」$\to$「大」的贡献，每次在集合中选择一个数去掉，然后加入两个数，要使最后去掉的数之和最小。

显然每次贪心的取最小值即可。

现在要考虑 $s,e$，我们将元素分成 $[1, \min(s,e) - 1],[\min(s,e) + 1, \max(s,e) - 1],[\max(s,e) + 1, n]$ 三个部分分别讨论，可以发现过程和上面的类似。

因此这样贪心是正确的。

由于本题 $n$ 较小，可以直接 $\mathcal O(n^2)$ 解决，但根据上述讨论，我们显然可以优化至 $\mathcal O(n \log n)$。

## 代码

```cpp
const int N = 5e3 + 7;
int n, s, e, t[N];
ll x[N], a[N], b[N], c[N], d[N], ans;

inline ll S(int i, int j) {
	return i < j ? x[j] - x[i] + d[i] + a[j] : x[i] - x[j] + c[i] + b[j];
}

int main() {
	rd(n), rd(s), rd(e);
	rda(x, n), rda(a, n), rda(b, n), rda(c, n), rda(d, n);
	ans = S(s, e), t[s] = e;
	for (int i = 1; i <= n; i++)
		if (i != s && i != e) {
			pair<ll, int> o = mp((ll)1e18, 0);
			for (int j = s; j != e; j = t[j])
				o = min(o, mp(S(j, i) + S(i, t[j]) - S(j, t[j]), j));
			t[i] = t[o.se], t[o.se] = i, ans += o.fi;
		}
	print(ans);
	return 0;
}
```

---

## 作者：_HCl_ (赞：14)

反复读错题，重构了三次。急了，写篇题解。

# CF704B 题解

**题意简述**

求出一个 $1\sim n$ 的排列 $p$，满足 $p_1=s$，$p_n=e$，且 $\sum\limits_{i=1}^{n-1}F(p_i,p_{i+1})$ 最小。

其中 $F_{i,j}=\begin{cases}x_i-x_j+c_i+b_j&i>j\\x_j-x_i+d_i+a_j&i<j \end{cases}$。

**思路引导**

容易观察到，这个 $f_{i,j}$ 可以拆成 $i$ 有关的部分和 $j$ 有关的部分，也就说，相邻的两个数对答案的贡献是独立的，那我们就可以分开计算每个数对答案的贡献。

很自然地想到，使用“插入型 DP”来解决这个问题。关于插入型 DP 可以去观察[这题](https://www.luogu.com.cn/problem/P5999)。我们可以考虑将 $1\sim n$ 按顺序逐一插入序列中，并计算贡献。

我们设 $f_{i,j}$ 表示插入 $i$ 个数，分成 $j$ 段，这 $i$ 个数对答案的贡献。然后按照插入型 DP 的套路去考虑它的转移方程。先考虑一般化的情况，也就是没有 $s$ 和 $e$ 的限制。

---

- 段新增

新增一个段，一开始只有要插入的数 $i$，左右都没有数。但是到了后面，左右都要插入数，并且插入的数都要比 $i$ 大。

因此其贡献就是 $F_{i,j}$ 第一条中的 $j$ 加上第二条中的 $i$。

$$f_{i,j}=f_{i-1,j-1}-2x_i+b_i+d_i$$

- 段扩张

选择一个段，将 $i$ 添加到该段的左侧或右侧。

以添加到左侧为例，$i$ 比其右侧的数大，其贡献是 $F_{i,j}$ 中第一条中的 $i$。但是 $i$ 的左侧还会继续添加比它大的数，此时的贡献是 $F_{i,j}$ 中第一条中的 $j$。两个贡献加起来就是 $i$ 的贡献。

添加在右侧也是同理。

$$f_{i,j}=f_{i-1,j}+b_i+c_i$$
$$f_{i,j}=f_{i-1,j}+a_i+d_i$$

- 段合并

选择两个段，将 $i$ 添加在两个段的中间，把两个段合并起来。

此时 $i$ 比左右两个数都要大，因此其贡献就是 $F_{i,j}$ 中第一条的 $i$ 加上第二条的 $j$。

$$f_{i,j}=f_{i-1,j+1}+2x_i+a_i+c_i$$

---

然后考虑一下 $i=s$ 和 $i=e$ 的情况。

以 $i=s$ 为例，由于它只会被添加在最左侧，在段新增时，只用考虑它对右侧的贡献；段扩张时，只用考虑被添加在左侧的可能；并且不用考虑段合并的情况。

$i=e$ 也是同理。

但是还有一个东西我们要考虑，即使是一般的情况，段新增和段扩张是要考虑条件的。

段新增时，需要满足 `j>(i>s)+(i>e)` 的条件。由于段新增的状态是由 $f_{i,j-1}$ 转移过来的，当 $j=2$ 时，$f_{i,j-1}$ 的状态中只有一段，而且这唯一的一段还包含了 $s$ 和 $e$，那就不可能再加入新的点了。

段扩张时，对于添加到左侧，需要满足 `j>1||i<s` 的条件。因为当只有一段时，并且 $s$ 还没被访问到，你需要把唯一一段的左侧留给 $s$。对于添加到右侧也是同理。

那这样这道题就做好了。最后的答案也就是 $f_{n,1}$。

**代码**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5001;
int n,s,e;
int f[N][N],a[N],b[N],c[N],d[N],x[N];
int _min(int x,int y){
	return x>y?y:x;
}
signed main(){
	cin>>n>>s>>e;
	for(int i=1;i<=n;++i)scanf("%lld",x+i);
	for(int i=1;i<=n;++i)scanf("%lld",a+i);
	for(int i=1;i<=n;++i)scanf("%lld",b+i);
	for(int i=1;i<=n;++i)scanf("%lld",c+i);
	for(int i=1;i<=n;++i)scanf("%lld",d+i);
	memset(f,0x3f,sizeof(f));
	f[0][0]=0;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=i;++j){
			if(i==s){
				f[i][j]=_min(f[i][j],f[i-1][j-1]-x[i]+d[i]);
				f[i][j]=_min(f[i][j],f[i-1][j]+x[i]+c[i]);
			}
			else if(i==e){
				f[i][j]=_min(f[i][j],f[i-1][j-1]-x[i]+b[i]);
				f[i][j]=_min(f[i][j],f[i-1][j]+x[i]+a[i]);
			}
			else{
				if(j>(i>s)+(i>e))f[i][j]=_min(f[i][j],f[i-1][j-1]-2*x[i]+b[i]+d[i]);
				if(j>1||i<s)f[i][j]=_min(f[i][j],f[i-1][j]+b[i]+c[i]);
				if(j>1||i<e)f[i][j]=_min(f[i][j],f[i-1][j]+a[i]+d[i]);
				f[i][j]=_min(f[i][j],f[i-1][j+1]+2*x[i]+a[i]+c[i]); 
			}
		}
	}
	cout<<f[n][1]; 
} 
```

---

## 作者：GreenDay (赞：11)

### CF704B Ant Man 题解

大佬的题解都是$O(n^2)$的，蒟蒻来补充一篇$O(n \log n)$的题解。

参考了xht37的题解和TA201314的题解.

[题面](https://www.luogu.com.cn/problem/CF704B)

---
我们分开考虑某个数$i$有哪些4类贡献

- A 小->i $A_i=x_i+a_i$
- B 大->i $B_i=-x_i+b_i$
- C i->小 $C_i=x_i+c_i$
- D i->大 $D_i=-x_i+d_i$

---

天马行空的想，我们不管$s,e$作为开头和结尾的限制(或者说$s=1,e=2$)，只是**从小到大的**插入这$n$个数(这显然对答案没有影响)，考虑增量构造。

一次插入的$i$永远是当前编号最大的那个，因此答案一定会增加$A_i+C_i$的贡献（这是肯定的）。

然后我们考虑两种情况，若$i$插入了$x\rightarrow y$的空隙中。

- $x>y$ 此时$x$的贡献由$C_x$变为$D_x$,可以认为答案$+(D_x-C_x)$。在此之后，$x$的后继一定大于$x$,所以$x$与$x$的后继产生的贡献不再变化。

- $x<y$ 此时$y$的贡献由$A_y$变为了$B_y$,可以认为答案$+(B_y-A_y)$。在此之后，$y$的前驱一定大于$y$,所以$y$与$y$的前驱产生的贡献不再变化。

我们如果把所有对答案的贡献(也就是上文提到的$+(D_x-C_x)$,$+(B_y-A_y)$)用数据结构维护，我们发现每次操作可以被理解为如下三个步骤：

**(1)** 给答案加上一个$A_i+C_i$。

**(2)** 从数据结构取一个值加到答案上，然后把这个值删掉(这个值不可能再被使用了)。

**(3)** 向数据结构中添加两个新的值$B_i-A_i,D_i-C_i$，表示新建出两个空隙可能增加的贡献。

我们希望答案最小，所以(2)中取出当前的最小值。显然这种数据结构**小根堆**。

---

考虑$s,e$的限制。我们根据增量构造法，令$ans=calc(s,e)$，初始序列为$s,e$。

注意到我们并不能保证i是当前的最大值，也就是操作 **(1)** 不一定合法。我们有如下巧妙的做法：

- 当$i<s$时，我们把插入$B_i-A_i$提前在 **(2)** 操作之前。这样我们虽然不能保证$A_i$是合法的，但是如果我们从堆里取出了$B_i-A_i$,相当于我们选了$B_i$作为初始答案，即$i$左侧可能连的是$s$(右侧是合法的，所以没有新增贡献产生)

- 当$i<e$时，我们把插入$D_i-C_i$提前在 **(2)** 操作之前。这样我们虽然不能保证$C_i$是合法的，但是如果我们从堆里取出了$D_i-C_i$,相当于我们选了$D_i$作为初始答案，即$i$右侧可能连的是$e$.(左侧是合法的，所以没有新增贡献产生)

- 当$i=1\&s\ne1\&e \ne 1$,左右侧都有可能不合法，比较麻烦，所以我们提前强制插入1。

当然$i=s\|i=e$是，我们不必要执行所有操作（因为已经算过了），我们只需要分别向小根堆中添加$D_s-C_s$和$B_e-A_e$,表示：在计算s的时候,我们默认是s->小，现在提供一种可能让s->小变为s->大。（e同理）

最后输出答案即可.~~所以这道题可以被加强到$N\le10^6$的(duliu)~~

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long int64;
const int N = 5005;

int n , s , e;
int64 x[N] , a[N] , b[N] , c[N] , d[N];
int64 calc(int i , int j) {
    if(i < j) return x[j] - x[i] + d[i] + a[j];
    else return x[i] - x[j] + c[i] + b[j];
}
template<typename _T>
inline void read(_T &x) {
    x = 0 ; char c = getchar(); bool f = 0;
    while(c < '0' || c > '9') f |= (c=='-') , c = getchar();
    while(c >= '0' && c <= '9') x = x * 10 + (c^48) , c = getchar();
    if(f) x = -x;
}
void input(int64* t) { for(int i = 1 ; i <= n ; ++i) read(t[i]); }

priority_queue<int64 , vector<int64> , greater<int64> > heap;
int64 ans = 0;
void init() {
    read(n) , read(s) , read(e);
    input(x) , input(a) , input(b) , input(c) , input(d);
    if(s == 1 || e == 1) ans = calc(s , e);
    else ans = calc(s , 1) + calc(1 , e);
    //注意特判1,因为1的左右两端(一端)都是比他小的数，所以得特判
}

int main() {
    init();
    for(int64 i = 2 ; i <= n ; ++i) {
        int64 A = x[i] + a[i] , B = -x[i] + b[i] , C = x[i] + c[i] , D = -x[i] + d[i];
        //A:小->i B:大->i C:i->小 D:i->大
        if(i == s) //在计算s的时候,我们默认是s->小，现在提供一种可能让s->小变为s->大
            heap.push(D-C);
        else if(i == e)//跟上面那个分析差不多
            heap.push(B-A);
        else {
            ans += A+C;//我们先默认它左右两边都是比他小的数
            if(i < s) heap.push(B-A);
            if(i < e) heap.push(D-C);
            ans += heap.top() , heap.pop();
            if(i > s) heap.push(B-A);
            if(i > e) heap.push(D-C);            
        }
    }
    cout << ans << endl;
}
```

---

## 作者：yijan (赞：8)

[我的博客](https://www.yijan.co/cf704b-ant-man/)

考虑对于一个位置，如果它不是 $s,e$ ，那么这个位置必然有一个入度一个出度。也就是说一个位置的方案有从右边进入，从左边进入，向左边出去，向右边出去。

我们考虑当前已经填完了前 $i$ 个位置，到现在为止还剩 $j$ 个向左的边和 $k$ 个向右的边。不难发现，如果这个点不是 $s,e$ 的一种，那么对于任何一种填这个点边的方案，要么使向左的、向右的边的个数同时 $+1,-1$ 要么使向左、向右的边的个数不变，分别对应：

![](https://yijan.oss-cn-chengdu.aliyuncs.com/img/DB76CAAB-723F-48C4-AAAC-6816BE086872.png)

然后如果新增的点是 $s$ ，那么只能是

![](https://yijan.oss-cn-chengdu.aliyuncs.com/img/BC5745CF-8E85-464D-9559-D5BC8E01F523.png)

如果新增的点是 $t$ ，那么只能是反过来的。

于是我们考虑一个 $dp$ ，设 $dp[i][j]$ 表示当前在 $i$ 这个位置，然后：

- 如果当前 $i < s,i < e$ ，那么还剩 $j$ 个向右，$j$ 个向左的边。
- 如果当前 $s < i < e$ ，那么还剩 $j$ 个向右，$j - 1$ 个向左的边。
- 如果当前 $e < i < s$，那么还剩 $j - 1$ 个向右，$j$ 个向左的边。
- 如果当前 $i > s,i > e$ ，那么还剩 $j - 1$ 个向右，$j - 1$ 个向左的边。

考虑什么状态、转移不合法：

- 如果 $j \le 0 , i \neq 0$ ，显然这个状态必然不合法。
- 如果当前有 $i > s,i > e,i \neq n$ 那么对于 $j \le 1$ 都不合法。 因为如果这个位置在 $s,e$ 之后了，那么前面必须得有接口可以接入 $s-e$ 这条链。不然的话我们就会转移出 $s-t$ 一条链加上很多环的情况（不出意外应该会 WA 7）。
- 如果当前有 $i > s,j = 1$ 不能走最前面说的第四种转移，虽然是从 $(i,j) \to (i,j)$ 但是这个位置前面并没有向左的边存在，所以不能这么接进去。
- 同理的，如果当前有 $i > e,j = 1$ 不能走最前面说的第三种转移。（如果没有考虑后面两种情况不出意外会直接 WA 5）

代码写着还是蛮爽的，只是开始没考虑到不合法的转移（好在特殊情况 $n=4$ 都能拍出来 QwQ）。

还是 Orz 上面的贪心。

```cpp
#include "iostream"
#include "algorithm"
#include "cstring"
#include "cstdio"
#include "cmath"
#include "vector"
#include "map"
#include "set"
#include "queue"
using namespace std;
#define MAXN 5006
//#define int long long
#define rep(i, a, b) for (int i = (a), i##end = (b); i <= i##end; ++i)
#define per(i, a, b) for (int i = (a), i##end = (b); i >= i##end; --i)
#define pii pair<int,int>
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define vi vector<int>
#define all(x) (x).begin() , (x).end()
#define mem( a ) memset( a , 0 , sizeof a )
typedef long long ll;
int n , s , e;
ll dp[MAXN][MAXN];
int A[MAXN] , B[MAXN] , C[MAXN] , D[MAXN] , x[MAXN];

void solve() {
	cin >> n >> s >> e;
	rep( i , 1 , n ) scanf("%d",x + i);
	rep( i , 1 , n ) scanf("%d",A + i);
	rep( i , 1 , n ) scanf("%d",B + i);
	rep( i , 1 , n ) scanf("%d",C + i);
	rep( i , 1 , n ) scanf("%d",D + i);
	memset( dp , 0x3f , sizeof dp );
	dp[1][1] = ( s != 1 ? B[1] - x[1] : 0 ) + ( e != 1 ? D[1] - x[1] : 0 );
	rep( i , 2 , n - 1 ) {
		if( i != s && i != e ) {
			rep( j , ( i > s && i > e ? 2 : 1 ) , i ) {
				if( i <= s || j != 1 ) dp[i][j] = min( dp[i][j] , dp[i - 1][j] + B[i] + C[i] );
				if( i <= e || j != 1 ) dp[i][j] = min( dp[i][j] , dp[i - 1][j] + A[i] + D[i] );
				dp[i][j + 1] = min( dp[i][j + 1] , dp[i - 1][j] + B[i] - x[i] + D[i] - x[i] );
				if( j != 1 ) dp[i][j - 1] = min( dp[i][j - 1] , dp[i - 1][j] + A[i] + x[i] + C[i] + x[i] );
			}
		} else if( i == s ) {
			rep( j , 1 , i ) {
				dp[i][j] = min( dp[i][j] , dp[i - 1][j] + C[i] + x[i] );
				dp[i][j + 1] = min( dp[i][j + 1] , dp[i - 1][j] + D[i] - x[i] );
			}
		} else if( i == e ) {
			rep( j , 1 , i ) {
				dp[i][j + 1] = min( dp[i][j + 1] , dp[i - 1][j] + B[i] - x[i] );
				dp[i][j] = min( dp[i][j] , dp[i - 1][j] + A[i] + x[i] );
			}
		}
	}
//	cout << dp[2][1] << endl;
//	cout << dp[2][1] << endl;
	ll res = 0;
//	cout << dp[3][1] << endl;
//	cout << C[n] + x[n] << endl;
	res = dp[n - 1][1 + ( s != n && e != n )] + ( s != n ? A[n] + x[n] : 0 ) + ( e != n ? C[n] + x[n] : 0 );
	cout << res << endl;
}

signed main() {
//	freopen("input","r",stdin);
//    int T;cin >> T;while( T-- ) solve();
	solve();
}
```



---

## 作者：绝顶我为峰 (赞：7)

集训队作业居然有 *2500 的题。![qq_emoji: jy](https://xn--9zr.tk/jy)![qq_emoji: jy](https://xn--9zr.tk/jy)![qq_emoji: jy](https://xn--9zr.tk/jy)

把贡献拆一下，$f(i,j)$ 中 $i,j$ 的贡献是独立的，很方便我们分别考虑计算。

具体来说贡献有四类：

- 左边比 $i$ 大：$-x_i+b_i$；
- 左边比 $i$ 小：$x_i+c_i$；
- 右边比 $i$ 大：$-x_i+d_i$；
- 右边比 $i$ 小： $x_i+a_i$。

然后按照 [JOI 摩天大楼](https://loj.ac/p/2743) 那个题的套路来做，$dp_{i,j}$ 表示填了前 $i$ 个数，当前有 $j$ 个连续段的最小值。

从小到大加入数字，转移分三类讨论：

- 当前点是 $s$，分成新开一段（右边比他大）和接在一段边上（右边比他小）两种；
- 当前点是 $e$，分成新开一段（左边比他大）和接在一段边上（左边比他小）两种；
- 当前点是普通点，分成新开一段（左右都比他大），合并两段（左右都比他小），接在一段左边（左边比他大，右边比他小），接在一段右边（左边比他小，右边比他大）四种。

这里有一个坑点是有些状态是不合法的，具体来说有下面五种，要特判掉：

- 数组越界了的；
- 合并成 $0$ 段的；
- $s,e$ 都已经填了，当前点不是 $n$ 却已经缩成了一段的；
- 只填了 $s$，只有一段却接在了这段左边的；
- 只填了 $e$，只有一段却接在了这段右边的。

时间复杂度 $O(n^2)$。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
#define int long long
int n,s,t,cnt,x[5001],a[5001],b[5001],c[5001],d[5001],dp[5001][5001];
signed main()
{
    cin>>n>>s>>t;
    for(int i=1;i<=n;++i)
        cin>>x[i];
    for(int i=1;i<=n;++i)
        cin>>a[i];
    for(int i=1;i<=n;++i)
        cin>>b[i];
    for(int i=1;i<=n;++i)
        cin>>c[i];
    for(int i=1;i<=n;++i)
        cin>>d[i];
    for(int i=0;i<=n;++i)
        for(int j=0;j<=n;++j)
            dp[i][j]=1e18;
    dp[0][0]=0;
    for(int i=0;i<n;++i)
    {
        for(int j=0;j<=n;++j)
        {
            if(j==1&&cnt==2)
                dp[i][j]=1e18;
            if(dp[i][j]<1e18)
            {
                if(s==i+1)
                {
                    if(j<n)
                        dp[i+1][j+1]=min(dp[i+1][j+1],dp[i][j]-x[i+1]+d[i+1]);
                    if(j)
                        dp[i+1][j]=min(dp[i+1][j],dp[i][j]+x[i+1]+c[i+1]);
                }
                else if(t==i+1)
                {
                    if(j<n)
                        dp[i+1][j+1]=min(dp[i+1][j+1],dp[i][j]-x[i+1]+b[i+1]);
                    if(j)
                        dp[i+1][j]=min(dp[i+1][j],dp[i][j]+x[i+1]+a[i+1]);
                }
                else
                {
                    if(j<n)
                        dp[i+1][j+1]=min(dp[i+1][j+1],dp[i][j]-x[i+1]+b[i+1]-x[i+1]+d[i+1]);
                    if(j>1)
                        dp[i+1][j-1]=min(dp[i+1][j-1],dp[i][j]+x[i+1]+a[i+1]+x[i+1]+c[i+1]);
                    if(j)
                    {
                        if(t>i+1||j>1)
                            dp[i+1][j]=min(dp[i+1][j],dp[i][j]+d[i+1]+a[i+1]);
                        if(s>i+1||j>1)
                            dp[i+1][j]=min(dp[i+1][j],dp[i][j]+c[i+1]+b[i+1]);
                    }
                }
            }
        }
        cnt+=s==i+1||t==i+1;
    }
    cout<<dp[n][1]<<'\n';
    return 0;
}
```

---

## 作者：xishanmeigao (赞：2)

（[题目传送门](https://www.luogu.com.cn/problem/CF704B)）

一道很好的排列 $\rm dp$（连续段 $\rm dp$）的题目。

我们考虑从小到大插入这 $n$ 个数，设 $f[i][j]$ 表示现在考虑到第 $i$ 个数，有 $j$ 个连续段的最小权值，初始化为正无穷。

那么我们在插入一个数 $i$ 时，要将 $i$ 可能会产生的贡献提前计算。注意到如果 $i=s$ 或 $i=e$ 时贡献会有所不同，所以我们要分情况讨论：

- $i=s$：
  - 将 $i$ 插入到第一个连续段的最前面：
  
    $f[i-1][j]+x_i+c_i\rightarrow f[i][j]$
  - 将 $i$ 放在最前面自成一段，注意此时若 $e$ 已经插入，则要求 $j\geq 1$：
    
    $f[i-1][j]-x_i+d_i\rightarrow f[i][j+1]$
- $i=e$：
  - 将 $i$ 插入到最后一个连续段的最后面：
    
    $f[i-1][j]+x_i+a_i\rightarrow f[i][j]$
  - 将 $i$ 放到最后面自成一段，注意此时若 $s$ 已经插入，则要求 $j\geq 1$：
    
    $f[i-1][j]-x_i+b_i\rightarrow f[i][j+1]$
    
- $i\ne s$ 且 $i\ne e$

  - 将 $i$ 插入到左边，注意若 $s$ 已经插入，则要求 $j>1$：
    
    $f[i-1][j]+b_i+c_i\rightarrow f[i][j]$
    
  - 将 $i$ 插入到右边，注意若 $e$ 已经插入，则要求 $j>1$：
    
    $f[i-1][j]+a_i+d_i\rightarrow f[i][j]$
  - 用 $i$ 合并两个连续段，此时要求 $j\geq 2$：
     
    $f[i-1][j]+x_i+x_i+a_i+c_i\rightarrow f[i][j-1]$
  - $i$ 自成一段，注意若 $s$ 或 $e$ 若已经插入则对 $j$ 有要求：
    $f[i-1][j]-x_i-x_i+b_i+d_i\rightarrow f[i][j+1]$
    
    
最后输出 $f[n][1]$，那这道题就愉快地结束了！
    
```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;

const int N=5010;

int n,s,e;
LL f[N][N];
int x[N],a[N],b[N],c[N],d[N];

int main()
{
	memset(f,0x3f,sizeof(f));
	
	scanf("%d%d%d",&n,&s,&e);
	for(int i=1; i<=n; i++)
		scanf("%d",&x[i]);
	for(int i=1; i<=n; i++)
		scanf("%d",&a[i]);
	for(int i=1; i<=n; i++)
		scanf("%d",&b[i]);
	for(int i=1; i<=n; i++)
		scanf("%d",&c[i]);
	for(int i=1; i<=n; i++)
		scanf("%d",&d[i]);
		
	f[0][0]=0;
	for(int i=1; i<=n; i++)
	{
		for(int j=0; j<i; j++)
		{
			if(i==s)
			{
				f[i][j]=min(f[i][j],f[i-1][j]+x[i]+c[i]);
				if(j>=(i>e))
					f[i][j+1]=min(f[i][j+1],f[i-1][j]-x[i]+d[i]);
			}
			else if(i==e)
			{
				f[i][j]=min(f[i][j],f[i-1][j]+x[i]+a[i]);
				if(j>=(i>s))
					f[i][j+1]=min(f[i][j+1],f[i-1][j]-x[i]+b[i]);
			}
			else
			{
				if(j>1 || (i<s && j>0))
					f[i][j]=min(f[i][j],f[i-1][j]+b[i]+c[i]);
				if(j>1 || (i<e && j>0))
					f[i][j]=min(f[i][j],f[i-1][j]+a[i]+d[i]);
				if(j>=2)
					f[i][j-1]=min(f[i][j-1],f[i-1][j]+x[i]+x[i]+a[i]+c[i]);
				if(j>=((i>s)+(i>e)))
					f[i][j+1]=min(f[i][j+1],f[i-1][j]-x[i]-x[i]+b[i]+d[i]);
			}
		}
	}
	
	printf("%lld",f[n][1]);
	
	return 0;
}
```


---

## 作者：lfxxx (赞：1)

$p_i \to p_{i+1}$ 转换为图论模型，$e \to s$ 整个图变为一个环，我们要做的实际上是给每个点的入边和出边确定是向前连还是向后连。

考虑以前缀来拆解问题，好处是你可以很方便的处理 $x_i$ 带来的贡献，当你考虑一个前缀 $[1,i]$ 时，你在乎的是这个前缀中有多少个点的出边和入边还没有定下来，看似要设计两维状态，但是注意到前缀中入边出边总和相等，且前缀内的匹配一定是一条入边消去一条出边，所以剩下的出边入边数量也会相等，所以设计状态 $dp_{i,j}$ 表示考虑前缀 $[1,i]$ 剩下了 $j$ 条出边，$j$ 条入边的最小花费。转移就是枚举新加入的点出边入边方向和前面去匹配。

注意到并非确定了每个点有一条出边一条入边就是环了，图还要联通，如何在 dp 过程中考虑这个事情？

首先，假若在 $i \not = 1$ 时从 $dp_{i-1,0}$ 转移过来，一定不联通，因为这样使得 $[1,i-1]$ 与 $[i,n]$ 两个点集之间不存在边。

否则就一定存在联通方案吗？

可以证明，一定。

不妨归纳证明 $dp_{i,j}$ 可以对应一个只考虑 $[1,i]$ 内的点，形成了 $j$ 个连通块的方案，这是因为转移形如新增一个连通块，合并（当然也可以不合并，但是合并是不劣的）两个连通块，和往一个连通块的出边或者入边上挂点。

还有一个小细节，由于钦定了边 $e \to s$，所以这两个点之间的转移在 $j=1$ 时会禁用一种挂点的转移，也就是不能往 $e \to s$ 的边上挂点，同时钦定了 $e,s$ 的一条出边或者入边的方向，在 dp 过程中特判一下即可。

时间复杂度 $O(n^2)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 5e3+114;
const int inf = 1e18;
int x[maxn],a[maxn],b[maxn],c[maxn],d[maxn];
int dp[maxn];//In = Out = i 
int g[maxn];
int s,e;
int n;
signed main(){
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>s>>e;
    for(int i=1;i<=n;i++){
        cin>>x[i];
    }
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=n;i++){
        cin>>b[i];
    }
    for(int i=1;i<=n;i++){
        cin>>c[i];
    }
    for(int i=1;i<=n;i++){
        cin>>d[i];
    }
    for(int j=0;j<=n;j++) dp[j]=inf;
    dp[0]=0;
    bool flag=(s<e);
    //flag=1 S in 必须为 -> E out 必须为 <-
    //flag=0 S in 必须为 <- E out 必须为 ->
    for(int i=1;i<=n;i++){
        for(int j=0;j<=n;j++) g[j]=inf;
        if(i>1) dp[0]=inf;
        for(int j=0;j<=n;j++){
            if(i!=s&&i!=e){
                //In Out
                //<- <-
                if(j>=1&&dp[j]<inf) g[j-1]=min(g[j-1],dp[j]+2*x[i]+a[i]+c[i]);
                //<- ->
                if(j>=1&&dp[j]<inf&&(i<min(s,e)||i>max(s,e)||j>=2||flag==1)) g[j]=min(g[j],dp[j]+a[i]+d[i]);
                //-> <-
                if(j>=1&&dp[j]<inf&&(i<min(s,e)||i>max(s,e)||j>=2||flag==0)) g[j]=min(g[j],dp[j]+b[i]+c[i]);
                //-> ->
                if(j<n&&dp[j]<inf) g[j+1]=min(g[j+1],dp[j]-2*x[i]+b[i]+d[i]);       
            }else{
                if(i==s){
                    if(flag==1){
                        //-> <-
                        if(j>=1&&dp[j]<inf) g[j]=min(g[j],dp[j]+b[i]+c[i]);
                        //-> ->
                        if(j<n&&dp[j]<inf) g[j+1]=min(g[j+1],dp[j]-2*x[i]+b[i]+d[i]);
                    }else{
                        //<- <-
                        if(j>=1&&dp[j]<inf) g[j-1]=min(g[j-1],dp[j]+2*x[i]+a[i]+c[i]);
                        //<- ->
                        if(j>=1&&dp[j]<inf) g[j]=min(g[j],dp[j]+a[i]+d[i]);
                    }
                }else{
                    if(flag==1){
                        if(j>=1&&dp[j]<inf) g[j-1]=min(g[j-1],dp[j]+2*x[i]+a[i]+c[i]);
                        if(j>=1&&dp[j]<inf) g[j]=min(g[j],dp[j]+b[i]+c[i]);
                    }else{
                        if(j>=1&&dp[j]<inf) g[j]=min(g[j],dp[j]+a[i]+d[i]);
                        if(j<n&&dp[j]<inf) g[j+1]=min(g[j+1],dp[j]-2*x[i]+b[i]+d[i]);
                    }
                }
            }
        }
        for(int j=0;j<=n;j++) dp[j]=g[j];
    }
    cout<<dp[0]-(flag==1?(x[e]-x[s]+c[e]+b[s]):(x[s]-x[e]+d[e]+a[s]))<<'\n';
    return 0;
}
/*
7 1 7
8 11 12 16 17 18 20
0 0 0 0 0 0 0
0 0 0 0 0 0 0
0 0 0 0 0 0 0
0 0 0 0 0 0 0
*/
```

---

## 作者：MYLHF (赞：1)

先 orz 一下贪心大佬们。

我们设 $f_{i,j}$ 表示前 $i$ 个，有 $j$ 个没封闭的段的最小代价。

考虑当前插入元素 $i$，然后分一下几种情况转移：

若 $i=s$，则他可以新开一块，或者插在当前最左边的一段的左边。

若 $i=t$，则他可以新开一块，或者插在当前最右边的一段的右边。

否则：

- 新开一段，后面插入的都比他大。

  需要注意的是在 $i\not = n$ 时，$s$ 所在的块不能与 $e$ 所在的块合并。即当前的块数是要大于 $(i>s)+(i>e)$ 的。

- 接在某一段后面

  不能接在 $e$ 的后面。

- 接在某一段前面

  不能接在 $s$ 的前面。

- 合并某两段

放个代码：

```cpp
#include<vector>
#include<bits/stdc++.h>
#define int long long
#define de(x) cout<<#x<<": "<<x<<endl
#define rep(i,a,b) for(int i(a);i<=(b);++i)
#define REP(i,a,b) for(int i(a);i>=(b);--i)
using namespace std;

const int N=5000 +7,M=998244353;
int n,s,e,x[N],a[N],b[N],c[N],d[N],f[N][N];

signed main()
{
	cin>>n>>s>>e;
	rep(i,1,n) cin>>x[i];
	rep(i,1,n) cin>>a[i];
	rep(i,1,n) cin>>b[i];
	rep(i,1,n) cin>>c[i];
	rep(i,1,n) cin>>d[i];

	// f[i][j]表示前i个,有j个没封闭的段
	memset(f,127,sizeof f);
	f[0][0]=0;
	rep(i,1,n)
	{
		rep(j,1,i)
		{
			if(i==s ||i==e)
			{
				if(i==s) f[i][j]=min(f[i-1][j-1]-x[i]+d[i],f[i-1][j]+x[i]+c[i]);
				if(i==e) f[i][j]=min(f[i-1][j-1]-x[i]+b[i],f[i-1][j]+x[i]+a[i]);
			}
			else
			{
				// 新开一段，前后都比他大
				if(j>(i>s)+(i>e)) f[i][j]=min(f[i][j],f[i-1][j-1]-x[i]+b[i]-x[i]+d[i]);
				// 接在某一段后面
				if(j>1 || i<e) f[i][j]=min(f[i][j],f[i-1][j]+x[i]+a[i]-x[i]+d[i]);
				// 接在某一段前面
				if(j>1 || i<s) f[i][j]=min(f[i][j],f[i-1][j]+x[i]+c[i]-x[i]+b[i]);
				//合并某两段
				if(j!=i) f[i][j]=min(f[i][j],f[i-1][j+1]+x[i]+c[i]+x[i]+a[i]);
			}
		}
	}

	cout<<f[n][1]<<endl;

	return 0;
}
```

---

## 作者：Take_A_Single_6 (赞：1)

很好的一道连续段dp，求排列权值而不是常规的方案计数。  
考虑**将依赖邻项的贡献拆成单点贡献**，可以得到以下四种情况：  

- $i>j$
  - $i$ 的贡献为 $x_i+c_i$
  - $j$ 的贡献为 $-x_j+b_j$
- $i<j$
  - $i$ 的贡献为 $-x_i+d_i$
  - $j$ 的贡献为 $x_j+a_j$

然后按照连续段dp的状态设计，有新建连续段，插入连续段，合并连续段三种操作。题目给定了 $p_1=s$ 和 $p_n=e$，那么对于头尾我们要分类讨论。  
- $i=s$
  - 作为第一段单独成段，注意加过 $e$ 就至少有两段：
  $$dp_{i-1,j}-x_i+d_i \to dp_{i,j+1}$$
  - 插入连续段只能插入第一段的左端：
  $$dp_{i-1,j}+x_i+c_i \to dp_{i,j}$$
  - 无法用于合并连续段。
- $i=e$
  - 作为最后一段单独成段，注意加过 $s$ 至少有两段：
  $$dp_{i-1,j}-x_i+b_i \to dp_{i,j+1}$$
  - 插入连续段只能插入最后一段的右端：
  $$dp_{i-1,j}+x_i+a_i \to dp_{i,j}$$
  - 无法用于合并连续段。
- $\text{else}$
  - 新建连续段，注意是否加过 $s$ 和 $e$：
  $$dp_{i-1,j}-x_i+d_i-x_i+b_i \to dp_{i,j+1}$$
  - 插入某个连续段的左端，这里要保证不能插在 $s$ 前且已经有连续段存在：
  $$dp_{i-1,j}-x_i+b_i+x_i+c_i \to dp_{i,j}$$
  - 插入某个连续段的右端，这里要保证不能插在 $e$ 后且已经有连续段存在：
  $$dp_{i-1,j}-x_i+d_i+x_i+a_i \to dp_{i,j}$$
  - 用于合并连续段，注意至少有两个连续段才能合并：
  $$dp_{i-1,j}+x_i+c_i+x_i+a_i \to dp_{i,j-1}$$

为什么可以这样做？我们发现，新建连续段时左右一定会有更大的数来合并或者插入，插入连续段时肯定会比一端大而另一端将会有更大的数插入或合并，合并连续段时左右一定会小，这样就恰好覆盖了四种贡献情况。  
代码很好写，本题难点在于分讨。
```cpp
#include<bits/stdc++.h>
#define int long long
#define db double
#define maxn 1000005
#define mod 998244353
#define fir first
#define sec second
#define pr pair<int,int>
#define mk make_pair
#define inf 10000000000000000
using namespace std;
inline int read()
{
    int SS=0,WW=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
	{
        if(ch=='-')WW=-1;
        ch = getchar();
    }
    while(ch>='0'&&ch<='9')
	{
        SS=(SS<<1)+(SS<<3)+(ch^48);
        ch=getchar();
    }
    return SS*WW;
}
inline void write(int XX)
{
    if(XX<0)putchar('-'),XX=-XX;
    if(XX>9)write(XX/10);
    putchar(XX% 10 + '0');
}
int n,T,s,e,x[maxn],a[maxn],b[maxn],c[maxn],d[maxn],dp[5005][5005];
signed main()
{
	memset(dp,63,sizeof dp);
	n=read(),s=read(),e=read();
	for(int i=1;i<=n;i++)x[i]=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=read();
	for(int i=1;i<=n;i++)c[i]=read();
	for(int i=1;i<=n;i++)d[i]=read();
	dp[0][0]=0;
	for(int i=1;i<=n;i++)
		for(int j=0;j<i;j++)
		{
			if(i==s)
			{
				if(j>=(i>e))dp[i][j+1]=min(dp[i][j+1],dp[i-1][j]-x[i]+d[i]);
				dp[i][j]=min(dp[i][j],dp[i-1][j]+x[i]+c[i]);
			}
			else if(i==e)
			{
				if(j>=(i>s))dp[i][j+1]=min(dp[i][j+1],dp[i-1][j]-x[i]+b[i]);
				dp[i][j]=min(dp[i][j],dp[i-1][j]+x[i]+a[i]);
			}
			else
			{
				if(j>=(i>s)+(i>e))dp[i][j+1]=min(dp[i][j+1],dp[i-1][j]-2*x[i]+d[i]+b[i]);
				if((i<s&&j)||j>1)dp[i][j]=min(dp[i][j],dp[i-1][j]+b[i]+c[i]);
				if((i<e&&j)||j>1)dp[i][j]=min(dp[i][j],dp[i-1][j]+a[i]+d[i]);
				if(j>1)dp[i][j-1]=min(dp[i][j-1],dp[i-1][j]+2*x[i]+a[i]+c[i]);
			}
		}
	write(dp[n][1]);
	return 0;
}
```
由于我们的转移方程是**刷表法**，复杂度为 $O(n^2)$，通常难以优化。所以让我们膜拜写出 $\log$ 做法的神犇！

---

## 作者：ccxswl (赞：1)

从[这](https://www.luogu.com.cn/problem/P5999)来的，套路都一样，预设型 DP。

把那个式子拆开，看每个数单独的贡献。
 - 一个数比它左边的数小，它的贡献就是：$-x_i + b_i$
 - 比它左边的数大，它的贡献就是：$x_i + a_i$
 - 比它右边的数小，它的贡献就是：$-x_i + d_i$
 - 比它右边的数大，它的贡献就是：$x_i + c_i$

即：
```cpp
int Gl(int i) { // > 左边
    return x[i] + a[i];
}
int Gr(int i) { // > 右边
    return x[i] + c[i];
}
int Ll(int i) { // < 左边
    return -x[i] + b[i];
}
int Lr(int i) { // < 右边
    return -x[i] + d[i];
}
```

令 $f_{i,j}$ 表示已经插入 $i$ 个数，这些数构成了 $j$ 个连续段。

新插入的数比后插入的数小，所以一个数插进去的时候可以直接根据前后有没有数来计算贡献。

分类讨论即可，我分的情况比较细致，其实有几个情况有重合，但胜在好理解。

如果 $i=S$：
 - 插入到最左边，形成单独的块：
   - $f_{i,j} = f_{i-1,j-1}+Lr(i)$
 - 插入到最左边块的左边。如果 $E$ 已经插入，并且 $j=1$，这种情况就不成立了：
   - $f_{i,j} = f_{i-1,j}+Gr(i)$

如果 $i=E$：
 - 插入到最右边，形成单独的块：
   - $f_{i,j} = f_{i-1,j-1}+Ll(i)$
 - 插入到最右边块的右边。如果 $S$ 已经插入，并且 $j=1$，这种情况不成立：
   - $f_{i,j} = f_{i-1,j}+Gl(i)$

接下来看平常的情况：
 - 插入到所有数最左边，构成一个新块。如果 $S$ 已经插入则不成立：
   - $f_{i,j} = f_{i-1,j-1}+Ll(i)+Lr(i)$
 - 插入到最左边块的左边。如果 $S$ 已经插入则不成立：
   - $f_{i,j} = f_{i-1,j}+Ll(i)+Gr(i)$
 - 插入到所有数最右边，构成一个新块。如果 $E$ 已经插入则不成立：
   - $f_{i,j} = f_{i-1,j-1}+Ll(i)+Lr(i)$
 - 插入到最右边块的右边。如果 $E$ 已经插入则不成立：
   - $f_{i,j} = f_{i-1,j}+Gl(i)+Lr(i)$
 - 插到中间某块的左边。注意一定要有中间块，所以要满足 $j>1$：
   - $f_{i,j} = f_{i-1,j}+Ll(i)+Gr(i)$
 - 插到中间某块的右边。注意一定要有中间块，所以要满足 $j>1$：
    - $f_{i,j} = f_{i-1,j}+Gl(i)+Lr(i)$
 - 插到中间单独成块。两边一定要有块，所以要满足 $j > 2$：
   - $f_{i,j} = f_{i-1,j-1}+Ll(i)+Lr(i)$
 - 插到中间链接两个块：
   - $f_{i,j} = f_{i-1,j+1}+Gl(i)+Gr(i)$
     
对于 DP 边界详细见代码。

代码用一些技巧合并了重复的情况。

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

const int maxN = 5007;

int n, f[maxN][maxN];
int S, T;

int x[maxN], a[maxN], b[maxN], c[maxN], d[maxN];
int Gl(int i) {
    return x[i] + a[i];
}
int Gr(int i) {
    return x[i] + c[i];
}
int Ll(int i) {
    return -x[i] + b[i];
}
int Lr(int i) {
    return -x[i] + d[i];
}

int chkmin(int &x, int y) {
    return x = x > y ? y : x;
}

signed main() {
    cin >> n >> S >> T;
    for (int i = 1; i <= n; i++) cin >> x[i];
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];
    for (int i = 1; i <= n; i++) cin >> c[i];
    for (int i = 1; i <= n; i++) cin >> d[i];

    memset(f, 0x3f, sizeof(f));
    if (S == 1)
        f[1][1] = Lr(1);
    else if (T == 1)
        f[1][1] = Ll(1);
    else
        f[1][1] = Ll(1) + Lr(1);
    for (int i = 2; i < n; i++) {
        for (int j = 1; j <= i; j++) {
            if (i == S || i == T) {
                if (i == S) {
                    chkmin(f[i][j], f[i - 1][j - 1] + Lr(i));
                    if (j > (i > T))
                        chkmin(f[i][j], f[i - 1][j] + Gr(i));
                }
                else {
                    chkmin(f[i][j], f[i - 1][j - 1] + Ll(i));
                    if (j > (i > S))
                        chkmin(f[i][j], f[i - 1][j] + Gl(i));
                }
                continue;
            }
            if (i > S && i > T && j == 1) continue;

            if (j > (i > T) + (i > S))
                chkmin(f[i][j], f[i - 1][j - 1] + Ll(i) + Lr(i));
            chkmin(f[i][j], f[i - 1][j + 1] + Gl(i) + Gr(i));
            if (i < S || j != 1)
                chkmin(f[i][j], f[i - 1][j] + Ll(i) + Gr(i));
            if (i < T || j != 1)
                chkmin(f[i][j], f[i - 1][j] + Gl(i) + Lr(i));
        }
    }
    if (T == n)
        f[n][1] = f[n - 1][1] + Gl(n);
    else if (S == n)
        f[n][1] = f[n - 1][1] + Gr(n);
    else
        f[n][1] = f[n - 1][2] + Gl(n) + Gr(n);

    cout << f[n][1] << '\n';
}
```

---

## 作者：Claire0918 (赞：0)

问题实际上是将 $1$ 到 $n$ 重排使得权值最小，考虑连续段 DP。设 $f_{i, j}$ 表示已经加入了 $[1, i]$，恰形成了 $j$ 个连续段时某种权值的最小值。我们希望恰当的定义某种权值，使得转移过程简单。

我们发现无论 $i < j$ 还是 $i > j$，$f(i, j)$ 的项要么只与 $i$ 相关，要么只与 $j$ 相关，而没有同时与两者相关的项。因此，对于确定的 $i$ 和未知的 $j$，如果我们能够确定是 $i < j$ 还是 $i > j$，那么 $f(i, j)$ 和 $f(j, i)$ 中与 $i$ 相关的项就完全确定了。与 $j$ 相关的项我们留待考虑 $j$ 时再计算贡献。

综上，我们设 $f_{i, j}$ 表示已经加入了 $[1, i]$，恰形成了 $j$ 个连续段时 $x \in [1, i]$ 的贡献之和最小值。我们有平凡的下述转移：

+ $i$ 新建一段。此时 $i$ 左右两侧的 $j_1$ 和 $j_2$ 都比 $i$ 大，所以 $i$ 的贡献是 $(b_i - x_i) + (d_i - x_i) = b_i + d_i - 2x_i$，转移 $f_{i, j + 1} \gets f_{i - 1, j} + b_i + d_i - 2x_i$。
+ $i$ 加入到某一段的左侧。此时 $i$ 左侧的 $j_1 > i$，右侧的 $j_2 < i$，所以 $i$ 的贡献是 $(b_i - x_i) + (c_i + x_i) = b_i + c_i$，转移 $f_{i, j} \gets f_{i - 1, j} + b_i + c_i$。
+ $i$ 加入到某一段的右侧。此时 $i$ 左侧的 $j_1 < i$，右侧的 $j_2 > i$，所以 $i$ 的贡献是 $(a_i + x_i) + (d_i - x_i) = a_i + d_i$，转移 $f_{i, j} \gets f_{i - 1, j} + a_i + d_i$。
+ 加入 $i$ 将两段连接成一段。此时 $i$ 左右两侧的 $j_1$ 和 $j_2$ 都比 $i$ 大，所以 $i$ 的贡献是 $(c_i + x_i) + (a_i + x_i) = c_i + a_i + 2x_i$，转移 $f_{i, j - 1} \gets f_{i - 1. j} + c_i + a_i + 2x_i$。

当然，$i = s$ 或 $i = e$ 时有部分转移是不合法的，同时 $s$ 左侧没有贡献，$e$ 右侧没有贡献，特判并修改转移即可。

这样之后，我们仍然面临一个问题：如果我们加入了 $s$，然后在 $s$ 所在连续段的左侧在加入了某个 $i$，那么最后的结果中 $s$ 将不位于左侧，并不合法。为了处理类似问题，我们要求：

+ $i \geq s, i \geq e, i < n$ 且 $j = 1$ 的 $f_{i, j}$ 不合法。
+ $i > s, j = 1$ 时不能将 $i$ 加入到某一段的左侧。
+ $i > e, j = 1$ 时不能将 $i$ 加入到某一段的右侧。

容易发现，在上述限制后，每一种转移都一定存在合法的构造方案，所以问题完整地解决了，答案即为 $f_{n, 1}$。

时间复杂度 $\mathcal{O}(n^2)$。

Code：
```cpp
#include<bits/stdc++.h>
#define mem(a, v) memset(a, v, sizeof(a))

using namespace std;

const int maxn = 5e3 + 10;

int n, s, e;
long long x[maxn], a[maxn], b[maxn], c[maxn], d[maxn], f[2][maxn];

int main(){
    scanf("%d %d %d", &n, &s, &e);
    const vector<long long*> ord = {x, a, b, c, d};
    for (auto arr: ord){
        for (int i = 1; i <= n; i++){
            scanf("%lld", arr + i);
        }
    }
    mem(f[0], 0x3f), f[0][0] = 0;
    for (int i = 1; i <= n; i++){
        mem(f[i & 1], 0x3f);
        for (int j = 0; j < i; j++){
            if (s < i && e < i && j == 1){
                continue;
            }
            if (i == s){
                f[i & 1][j + 1] = min(f[i & 1][j + 1], f[i & 1 ^ 1][j] + d[i] - x[i]);
                j && (f[i & 1][j] = min(f[i & 1][j], f[i & 1 ^ 1][j] + x[i] + c[i]));
            }else if (i == e){
                f[i & 1][j + 1] = min(f[i & 1][j + 1], f[i & 1 ^ 1][j] + b[i] - x[i]);
                j && (f[i & 1][j] = min(f[i & 1][j], f[i & 1 ^ 1][j] + x[i] + a[i]));
            }else{
                f[i & 1][j + 1] = min(f[i & 1][j + 1], f[i & 1 ^ 1][j] + b[i] + d[i] - (x[i] << 1));
                if (j){
                    s < i && j == 1 || (f[i & 1][j] = min(f[i & 1][j], f[i & 1 ^ 1][j] + c[i] + b[i]));
                    e < i && j == 1 || (f[i & 1][j] = min(f[i & 1][j], f[i & 1 ^ 1][j] + d[i] + a[i]));
                }
                j >= 2 && (f[i & 1][j - 1] = min(f[i & 1][j - 1], f[i & 1 ^ 1][j] + c[i] + a[i] + (x[i] << 1)));
            }
        }
    }
    printf("%lld", f[n & 1][1]);

return 0;
}
```

---

## 作者：forest114514 (赞：0)

题意：给定 $n$ 个元素组 $x_i,a_i,b_i,c_i,d_i$，求一个排列，满足 $p_1=s,p_n=e$ 的同时最小化 $\sum\limits_{i=1}^{n-1}f(p_{i},p_{i+1})$，$f(i,j)=\begin{cases}x_i-x_j+c_i+b_j&i>j\\x_j-x_i+d_i+a_j&i<j\end{cases}$。

----

最近正好在练连续段 DP，于是乎详细地写一下。

考虑拆贡献，$i$ 左侧的数下标小于自己的时候贡献为 $x_i+d_i$，否则为 $-x_i+b_i$，右侧的数小于自己的时候贡献为 $x_i+c_i$ 否则为 $-x_i+a_i$。发现每个数的贡献只和周围的数的大小关系有关，这不就是明示了做法：按顺序加入做 DP。特殊的因为算贡献是小于的时候相当于之前钦定了一些位置大于自己，所以 $\leq i$ 的数构成了若干段，段外的 数满足 $>i$，每次就考虑加入的数左右的大小关系，可以连续段 DP。

给定开头结尾就特判即可，设 $f_{i,j}$ 为放了 $1\sim i$，当前有 $j$ 个连续段的最大权值和，转移有：

1. 接在某个连续段左侧而且不是作为开头：$f_{i,j}+b_i+c_i\to f_{i+1,j}$
2. 接在某个连续段右侧而且不是作为结尾：$f_{i,j}+d_i+a_i\to f_{i+1,j}$
3. 新开一个连续段：$f_{i,j}-2x_i+a_i+b_i\to f_{i+1,j+1}$
4. 合并一个连续段：$f_{i,j}+2x_i+c_i+d_i\to f_{i+1,j-1}$
5. 作为开头，不新开一段：$f_{i,j}+x_i+c_i\to f_{i,j}$
6. 作为开头，新开一段：$f_{i,j}-x_i+a_i\to f_{i,j+1}$
7. 作为结尾，不新开一段：$f_{i,j}+x_i+d_i\to f_{i,j}$
8. 作为结尾，新开一段：$f_{i,j}-x_i+c_i\to f_{i,j+1}$

特判一下当前不能接在某段左边或右边的情况和没法合并和不合法的情况，时间复杂度 $O(n^2)$。

---

## 作者：hzoi_Shadow (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF704B)

# 前置知识

预设性 DP

# 解法

考虑统计每个数单独的贡献，然后进行预设性 DP。

设 $f_{i,j}$ 表示当前填了 $[1,i]$ 时有 $j$ 个连续段的最小权值，边界为 $f_{0,0}=0$。

对 $i(i \ne s,i \ne e)$ 填入的位置进行分讨。
  - 新开一段
    - 后面填入的数都比 $i$ 大（如果存在后面填入的数的话，即 $j>[i>s]+[i>t]$），故 $f_{i,j}=\min(f_{i,j},f_{i-1,j-1}-2x_{i}+b_{i}+d_{i})$。
  - 连接到某个连续段的前后
    - 连接到某个连续段的前面（如果可以在前面的话，即 $j>[i>s]$）时，后面填入的数（在 $i$ 左面）比 $i$ 大，而 $i$ 右面的数比 $i$ 小，故 $f_{i,j}=\min(f_{i,j},f_{i-1,j}+b_{i}+c_{i})$。
    - 连接到某个连续段的后面（如果可以在后面的话，即 $j>[i>t]$）时，后面填入的数（在 $i$ 右面）比 $i$ 大，而 $i$ 左面的数比 $i$ 小，故 $f_{i,j}=\min(f_{i,j},f_{i-1,j}+a_{i}+d_{i})$。
  - 连接两个连续段
    - $i$ 比旁边的两个数都要大，故 $f_{i,j}=\min(f_{i,j},f_{i-1,j+1}+2x_{i}+a_{i}+c_{i})$。

当 $i=s$ 时只可能放到首端，可行的转移操作只有新开一段和连接到某个连续段的前面且前面不会再有数填，故 $f_{i,j}=\min(f_{i-1,j-1}-x_{i}+d_{i},f_{i-1,j}+x_{i}+c_{i})$；当 $i=e$ 时只可能放到末端，可行的转移操作只有新开一段和连接到某个连续段的后面且后面不会再有数填，故 $f_{i,j}=\min(f_{i-1,j-1}-x_{i}+b_{i},f_{i-1,j}+x_{i}+a_{i})$。

最终有 $f_{n,1}$ 即为所求。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define ull unsigned long long
#define sort stable_sort 
#define endl '\n'
ll f[5010][5010],x[5010],a[5010],b[5010],c[5010],d[5010];
int main()
{
	ll n,s,e,i,j;
	cin>>n>>s>>e;
	for(i=1;i<=n;i++)
	{
		cin>>x[i];
	}
	for(i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	for(i=1;i<=n;i++)
	{
		cin>>b[i];
	}
	for(i=1;i<=n;i++)
	{
		cin>>c[i];
	}
	for(i=1;i<=n;i++)
	{
		cin>>d[i];
	}
	memset(f,0x3f,sizeof(f));
	f[0][0]=0;
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=i;j++)
		{
			if(i==s)
			{
				f[i][j]=min(f[i][j],f[i-1][j-1]-x[i]+d[i]);
				f[i][j]=min(f[i][j],f[i-1][j]+x[i]+c[i]);
			}
			else
			{
				if(i==e)
				{
					f[i][j]=min(f[i][j],f[i-1][j-1]-x[i]+b[i]);
					f[i][j]=min(f[i][j],f[i-1][j]+x[i]+a[i]);
				}
				else
				{
					if(j>(i>s)+(i>e))
					{
						f[i][j]=min(f[i][j],f[i-1][j-1]-2*x[i]+b[i]+d[i]);
					}
					if(j>(i>s))
					{
						f[i][j]=min(f[i][j],f[i-1][j]+b[i]+c[i]);
					}
					if(j>(i>e))
					{
						f[i][j]=min(f[i][j],f[i-1][j]+a[i]+d[i]);
					}
					f[i][j]=min(f[i][j],f[i-1][j+1]+2*x[i]+a[i]+c[i]);
				}
			}
		}
	}
	cout<<f[n][1]<<endl;
	return 0;
}
```

---

## 作者：Forg1weN (赞：0)

## 题面
- 有 $n$ 个元素，第 $i$ 个元素有五个参数 $x_i,a_i,b_i,c_i,d_i$。
- 你需要求出一个 $1 \sim n$ 的排列 $p$，满足 $p_1 = s, p_n = t$，同时最小化这个排列的权值。
- 一个排列的权值为 $\sum_{i=1}^{n-1} f(p_i, p_{i+1})$，其中 $f(i,j)$ 的值有两种情况：
  - 若 $i > j$，则 $f(i,j) = x_i - x_j + c_i + b_j$。
  - 若 $i < j$，则 $f(i,j) = x_j - x_i + d_i + a_j$。
- $n \le 5 \times 10^3$，$s \ne e$，$1 \le x_1 < x_2 < \cdots < x_n \le 10^9$，$1 \le a_i,b_i,c_i,d_i \le 10^9$。

## Solution
老样子，如果关注其排列的顺序具体是什么则无法解决这道题，考虑插入 DP。

记 $f_{i,j}$ 表示填入 $i$ 个数构成了 $j$ 个联通块的最小权值。令 $ls,lb,rs,rb$ 为下示。

```cpp
int ls(int i){return  x[i]+a[i];}//左边的数比我小 
int lb(int i){return -x[i]+b[i];}//左边的数比我大 
int rs(int i){return  x[i]+c[i];}//右边的数比我小 
int rb(int i){return -x[i]+d[i];}//右边的数比我大 
```

首先要固定一个块内的顺序，否则无法转移，令插入只能插入块的两端。

本题的关键不在于处理如此庞多的数据，而在于在处理 $i$ 插入的时候把与  $i$ 有关的数值全部处理，这样保证了转移没有后效性。

首先考虑当 $i=s$ 或 $i=t$ 的特殊限制。

若 $i=s$，则只能插入首块的首端： 

$f_{i,j}=f_{i-1,j}+rs_i$。

或自成一块： 

$f_{i,j}=f_{i-1,j-1}+rb_i$。

若 $i=t$，则只能插入尾块的尾端： 

$f_{i,j}=f_{i-1,j}+ls_i$。

或自成一块： 

$f_{i,j}=f_{i-1,j-1}+lb_i$。

接着考虑剩余情况。

若插入一个块的左端，前提是不能插入已插入过 $s$ 的首块中： 

$f_{i,j}=f_{i-1,j}+rs_i+lb_i$。

若插入一个块的右端，前提是不能插入已插入过 $t$ 的尾块中： 

$f_{i,j}=f_{i-1,j}+rb_i+ls_i$

若合并两个块，则： 

$f_{i,j}=f_{i-1,j+1}+ls_i+rs_i$。

若自成一块，则： 

$f_{i,j}=f_{i-1,j-1}+lb_i+rb_i$。

注意，转移的方程不同，考虑的边界情况不一样。

## code 
自写不难，略去。

---

