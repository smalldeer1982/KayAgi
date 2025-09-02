# [JOIST 2023] 合唱 / Chorus

## 题目描述

在舞台上，有 $2N$ 只海狸排成一列。它们是合唱团的成员。每只海狸唱着高音部或低音部。这些信息由一个字符串 $S$ 给出。具体地，如果 $S$ 的第 $i$ 个字符是 $A$，编号为 $i$ 的海狸（从右边看台来看）唱高音。如果 $S$ 的第 $i$ 个字符是 $B$，编号为 $i$ 的海狸唱低音。有 $N$ 只海狸唱高音，有 $N$ 只海狸唱低音。

从现在起，这些海狸将要演唱 $K$ 首歌。然而，因为所有歌曲非常复杂，每只海狸只唱一首歌曲，不会唱其他歌曲。此外，为了使歌声更加美妙，每首歌曲必须满足以下条件：

+ 至少有一只海狸唱这首歌。

+ 唱这首歌的唱高音和唱低音的海狸数量应当相等。

+ 如果只考虑唱这首歌的海狸，所有唱高音的海狸都在唱低音的海狸的右边。

指挥家 Bitaro 想找到一种方案，给出哪些海狸唱哪首歌，满足以上所有条件。由于 Bitaro 特别聪明，他注意到这可能无法实现。为了应对这个问题，Bitaro 将交换相邻两只海狸的位置多次，以便有一种方式可以调配海狸，从而满足上述条件。

由于 Bitaro 认为效率很重要，所以他想最小化要执行的操作数。然而，这是一个非常困难的问题。由于您是一位出色的程序员，Bitaro 请求您解决此问题。

编写一份程序，在给出合唱与演唱歌曲数量 $K$ 的信息时，计算 Bitaro 需要执行的最小操作数。请注意，在本任务的限制下，可以执行操作多次，以便有一种方式可以在海狸之间分配歌曲，满足上述条件。

## 说明/提示

**【样例解释 #1】**

在该样例输入中，例如 Bitaro 可以进行如下操作。下划线表示被交换的两个海狸的位置。

1. 交换从舞台右侧数第 3 个和第 4 个海狸。  
   操作后，表示海狸部件分布的字符串变为 $\text{`\texttt{AA\underline{AB}BABBAB}'}$。
2. 交换从舞台右侧数第 8 个和第 9 个海狸。  
   操作后，字符串变为 $\text{`\texttt{AAABBAB\underline{AB}B}'}$。

操作完成后，Bitaro 可以按如下方式分配歌曲：
- 从舞台右侧数第 1, 2, 3, 4, 5, 7 个海狸演唱第一首歌
- 从舞台右侧数第 6, 8, 9, 10 个海狸演唱第二首歌

这种分配方式满足条件。若操作次数少于 2 次，则不存在满足条件的分配方式。因此输出 2。

该样例满足所有子任务的限制。

**【样例解释 #2】**

不进行任何操作时，Bitaro 可以按如下方式分配歌曲：
- 从舞台右侧数第 1, 2, 3, 5 个海狸演唱第一首歌
- 从舞台右侧数第 4, 6, 7, 8 个海狸演唱第二首歌  
- 从舞台右侧数第 9, 10 个海狸演唱第三首歌

这种分配方式满足条件。因此输出 0。

该样例满足所有子任务的限制。

**【样例解释 #3】**

该样例满足所有子任务的限制。

**【样例解释 #4】**

该样例满足所有子任务的限制。

**【数据范围】**

对于所有测试数据，满足 $1 \le N \le 10^6$，$1 \le K \le N$，$S$ 是长度为 $2N$ 的字符串，且其中字符 $\verb!A!$ 和 $\verb!B!$ 各出现 $N$ 次。保证 $N,K$ 均为整数。

| 子任务编号 | 分值 | 限制 |
| :----------: | :----------: | :----------: |
| $1$ | $16$ | $N \le 10$ |
| $2$ | $24$ | $N \le 500$ |
| $3$ | $21$ | $N \le 5000$ |
| $4$ | $26$ | $N \le 10^5$ |
| $5$ | $13$ | 无 |

提示说明部分，翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
5 2
AABABABBAB```

### 输出

```
2
```

## 样例 #2

### 输入

```
5 3
AABABABBAB```

### 输出

```
0```

## 样例 #3

### 输入

```
3 1
BBBAAA```

### 输出

```
9```

## 样例 #4

### 输入

```
10 3
ABABBBBABBABABABAAAA```

### 输出

```
37```

# 题解

## 作者：Elma_ (赞：16)

感觉完全做不来这种题/ll.

首先发现 $=k$ 和 $\leq k$ 其实是等价的，先考虑对于一个确定的串，怎样划分能够使得子序列的数量尽量少。这比较简单，只需要每次贪心的往后取就行了。然后我们考虑一下大概会怎么交换，好像每次是给一个区间做排序状物，但似乎没有什么好的刻画方法，于是突然就做不下去了。

考虑一个神秘观察：把 $S$ 看成在 $n \times n$ 的网格中的一个路径，其中 ```A``` 表示向右一步，```B``` 表示向上一步，显然一次操作只会是把一个上右改成右上。当然有解的一个必要条件是它必须在对角线下方，我们把在对角线上方的部分改到对角线下方，代价提前计算掉，现在只考虑路径在对角线之下的情况。

考虑在路径上做上面那个贪心，相当于每次沿着路径往右走，碰到一个向上就一直向上直到碰到对角线再向右，两次拐弯衔接的地方可能会平移一部分路径，但这个是合法的。

于是要求 $k$ 个子序列，相当于是拐弯了 $k$ 次，每个拐弯对应一个区间。现在假设已经确定了最后的这 $k$ 个拐弯长成什么样，我们发现达到这个状态的代价恰好就是夹在钦定的路径上方，原路径下方的格子数量。具体可以看下面这个从官方题解偷来的图。

![](https://cdn.luogu.com.cn/upload/image_hosting/es788j99.png)

设 $w(l,r)$ 为区间 $[l,r]$ 对应拐弯，即从 $(l,l)$ 走到 $(r,r)$ 的代价，假设原点坐标是 $(1,1)$。那么现在问题相当于是要划分成 $k$ 个区间，最小化代价和。老套路了，容易验证它满足四边形不等式，所以整个问题是凸的。考虑 WQS 二分，之后用利用决策单调性分治 / SMAWK / LARSCH 等等优化转移技巧可以做到 $\mathcal{O}(n \log^3 n)$ 到 $\mathcal{O}(n \log n)$ 不等的时间复杂度。但它们要么复杂度太高，要么代码太难写，都不是我们想要的。

让我们暂时忘掉决策单调性。考虑给 $w(l,r)$ 一个更好的表征：设 $t_i$ 表示第 $i$ 向上前向右的次数，$pre_i$ 表示 $t_i$ 的前缀和，$cnt_i$ 和 $sum_i$ 分别表示满足 $t_j \leq  i$ 的 $j$ 的个数和 $t_j$ 的和，这些都容易 $\mathcal{O}(n)$ 预处理。那么 $w(l,r) = (cnt_{r-1} - l + 1) \times (r - 1) - sum_{r-1} + pre_{l-1}$。拆开用斜率优化即可。

总时间复杂度 $\mathcal{O}(n)$。有时候知道得太多也不一定是一件好事。


```cpp
#include <bits/stdc++.h>
using namespace std;
typedef pair <int, int> pi;
typedef long long LL;
constexpr int N = 2e6 + 5;
constexpr LL inf = 1e18;
int n, k, t[N], g[N]; LL cnt[N], sum[N], pre[N], f[N], ans, ns;
int q[N], hd, tl;
LL X(int i) { return i; }
LL Y(int i) {
	return f[i] + pre[i - 1] + i;
}
bool chk(LL m) {
	fill(f + 1, f + n + 2, inf);
	fill(g + 1, g + n + 2, k + 1);
	f[1] = g[1] = 0;
	q[hd = tl = 1] = 1;
	for (int i = 2; i <= n + 1; i++) {
		while (hd < tl && i * (X(q[hd + 1]) - X(q[hd])) > (Y(q[hd + 1]) - Y(q[hd]))) hd++;
		LL val = -X(q[hd]) * i + Y(q[hd]);
		f[i] = val + (cnt[i - 1] + 1) * (i - 1) - sum[i - 1] - m, g[i] = g[q[hd]] + 1;
		while (hd < tl && (Y(i) - Y(q[tl])) * (X(q[tl]) - X(q[tl - 1])) < (Y(q[tl]) - Y(q[tl - 1])) * (X(i) - X(q[tl]))) tl--;
		q[++tl] = i;
	} 
	ans = f[n + 1];
	return g[n + 1] <= k;
}
signed main() {
	ios :: sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> k;
	string str;
	cin >> str;
	str = ' ' + str;
	int cA = 0, cB = 0;
	for (int i = 1; i <= 2 * n; i++) {
		if (str[i] == 'A') ++cA;
		else ++cB, t[cB] = cA;
	}
	for (int i = 1; i <= n; i++) if (t[i] < i) ns += i - t[i], t[i] = i;
	for (int i = 1; i <= n; i++) pre[i] = pre[i - 1] + t[i];
	for (int i = 1; i <= n; i++) ++cnt[t[i]], sum[t[i]] += t[i];
	for (int i = 1; i <= n; i++) cnt[i] += cnt[i - 1], sum[i] += sum[i - 1];
	LL l = -5e11, r = 0, p = 0;
	while (l <= r) {
		LL m = (l + r) >> 1;
		if (chk(m)) p = m, l = m + 1;
		else r = m - 1;
	}
	chk(p);
	cout << ns + ans + 1LL * p * k << "\n";
  	return 0;
}
```

---

## 作者：yllcm (赞：13)

闲扯：大概两个月前我做了这道题，今天突然又看到这道题，想起我做法比较有意思然后准备写篇题解，然后对着我两个月前的简要题解看了半个小时才想起来做法，所以 DP 可能会有点奇怪的感觉，因为我也不知道我当时的精神状态也懒得重新写一遍了（

先转化一下题意：你需要进行若干次交换相邻的 $\texttt{A}$ 和 $\texttt{B}$ 的操作，使得存在一种将序列划分成恰好 $K$ 个集合的方案，使得：

* 集合内 $\texttt{A,B}$ 的数量相等。
* 集合内所有 $\texttt{B}$ 都在 $\texttt{A}$ 的右侧。

注意到一个集合可以裂开成多个集合，所以如果我们找到了一种 $\leq K$ 的方案，就一定能构造出 $=K$ 的方案。不妨先考虑这样一个问题：如何求出对于一个序列，按照上面的方式，最少分割成多少个集合？

显然有一个贪心做法：从前往后做，找到前缀一段连续的 $\texttt{A}$，然后匹配后面相同数量的 $\texttt{B}$ 并把它删掉。但是这样做比较麻烦，无法拓展到原问题。考虑一个更清晰的刻画：对于第一个条件，我们看做是 $\texttt{A}$ 和 $\texttt{B}$ 从前往后依次匹配，显然第 $i$ 个字符 $\texttt{A}$ 在最终方案中会与第 $i$ 个字符 $\texttt{B}$ 匹配。对于这样的匹配，我们不妨将它看做以 $\texttt{A}$ 的位置为左端点，$\texttt{B}$ 的位置为右端点的区间，这样每个集合中的所有匹配构成的区间两两有交。如果我们把一个区间完全在另一个区间右侧看做一个偏序关系，那么题目相当于让我们求一个**最小反链覆盖**，而它与最长链的长度相等。所以问题转化成求在所有区间中选最多的区间，使得区间两两不交，这有显然的贪心做法。

发现它非常有前途。回到原题，我们需要约束最长链的长度不超过 $K$，那么考虑一个 DP：设 $f_{i,l}$ 表示最长链方案中最小的能用的左端点为第 $i+1$ 个字符 $\texttt{A}$，最长链的长度为 $l$，使用的最小交换次数。转移是枚举第 $i+1$ 个 $\texttt{A}$ 和第 $i+1$ 个 $\texttt{B}$ 构成的区间能覆盖到的最远的字符 $\texttt{A}$ 是第 $j$ 个，那么我们需要让 $(i,j]$ 中的所有 $\texttt{A}$ 都移动到第 $i+1$ 个 $\texttt{B}$ 前面，设 $b_i$ 表示第 $i$ 个 $\texttt{A}$ 之前有多少个 $\texttt{B}$，转移是 $f_{j,l+1}\gets f_{i,l}+\sum_{k=i+1}^j \max(b_k-i,0)$。

发现这里的贡献 $w(i,j)=\sum\max(0,b_k-i)$ 满足四边形不等式，所以 DP 具有凸性，于是 WQS 二分可以省去 $l$ 这一维，复杂度优化至 $\mathcal{O}(n^2\log n)$。我们需要优化一维 DP：$f_{i}=\min_{j} (f_{j}+\sum_{k=j+1}^{i} \max(0,b_k-j))-\text{mid}$。

发现 $\max$ 比较烦，不过我们可以发现如果 $b_i<j$，我们完全可以多覆盖一位，这样最长链会变短，且代价不变。所以 $b_i\geq j$，设 $\text{nxt}_j$ 表示最小的 $k$ 满足 $b_k\geq j$，那么转移是 $f_i=\min_{nxt_j\leq i} (f_j+\sum_{k=nxt_j}^i (b_k-j))$。后面用前缀和拆开就可以发现是斜率优化的形式了。时间复杂度 $\mathcal{O}(n\log n)$。[code](https://loj.ac/s/1864083) ~~内含三方和平方代码~~



---

## 作者：Drind (赞：11)

这种题究竟是什么人在切。

先不考虑修改，容易发现只要构造段数小于 $k$ 的方案，一定有段数为 $k$ 的方案。所以可以把问题转化为求段数最小。并且，第 $i$ 个 A 和第 $i$ 个 B 一定要匹配在一起，证明显然。

现在加上修改，我们考虑 dp。我们设 $w(l,r)$ 为把第 $[l,r]$ 个 A 和 B 匹配在一起，所需要的最小权值。因为要让第 $l$ 到 第 $r$ 个 A 中间不能有任何一个编号大于 $l$ 的 B，所以 $w(l,r)=\sum_{i=l}^r\max(c_i-l+1,0)$，其中 $c_i$ 为第 $i$ 个 A 前面有多少个 B。

这个式子满足四边形不等式吧！所以外层 wqs 二分，内层决策单调性分治！复杂度 $O(n\log^2 n)$！这个做法难写，跑得慢，我们先弃了。

我们回到刚才的式子，我们发现 $l$ 取得很小没有什么意义，因为再小的 $c_i$ 最后和 $0$ 取 $\max$ 还是 $0$。我们预处理 $p_i$ 代表最小的 $k$ 使得 $c_k-i$ 不为 $0$，所以转移可以写成 $f_i=\min(f_j+\sum_{k=p_j-1}^j(c_k-i+1))$，拆成前缀和，发现可以斜率优化，所以用单调队列维护即可。复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
int _abs(int x){if(x<0) return -x; return x;}

int ta[N],res,cnt,n;
int sum[N],f[N],d[N],p[N];

//fi=fj+sumi-sum[pj-1]-j(i-pj+1)
//fi=fj-sum[pj-1]+j(pj-1) +sumi  -ij 

//fi-sumi = -ij + b(j) 
//max -ij + b(j) 
// y = kx(i)+b

int y(int x){
	return f[x]-sum[p[x]-1]+x*(p[x]-1);
}

int q[N];
pair<int,int>check(int k){
	int hd=0,tl=0;
	for(int i=1;i<=n;i++){
		while(hd<tl&&(y(q[hd+1])-y(q[hd]))<(q[hd+1]-q[hd])*i) hd++;
		int j=q[hd]; f[i]=f[j]+sum[i]-sum[p[j]-1]-j*(i-p[j]+1)+k; d[i]=d[j]+1;
		while(hd<tl&&(y(q[tl])-y(q[tl-1]))*(i-q[tl])>(y(i)-y(q[tl]))*(q[tl]-q[tl-1])) tl--;
		q[++tl]=i;
	}
	return {d[n],f[n]};
}

inline void fake_main(){
	int k; cin>>n>>k; string s; cin>>s;
	for(int i=0;i<n*2;i++){
		if(s[i]=='A'){
			ta[++res]=cnt;
			sum[res]=sum[res-1]+ta[res];
		}else cnt++;
	}
	for(int i=1;i<=n;i++){
		p[i]=lower_bound(ta+1,ta+res+1,i)-ta;
		p[i]=max(p[i],i+1);
	}
	int l=0,r=1e12,ans=1e12;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid).first<=k) ans=mid,r=mid-1;
		else l=mid+1;
	}
	cout<<check(ans).second-k*ans<<"\n";
}

signed main(){
	ios::sync_with_stdio(false);
	int t; t=1;
	while(t--) fake_main();
}

```

---

## 作者：Mirasycle (赞：10)

解读一下 sjy 老师上课讲的图象法。

转化为折线图，$A$ 向右上走，$B$ 向右下走。最严格条件是 $k$ 个连续单峰函数，每个峰端点高度均为 $0$，也就是底座在坐标轴上。

由于不是连续选择元素，而是可以选择子序列，所以只要当前折线画出来之后轮廓包含住了上述最严格折线必然合法，这个条件是充要的。如图 $k=5$ 的时候，黑色曲线就是其中一个最严格折线，而红色折线这个时候包含住了黑色折线，因为它也是合法的。

![](https://cdn.luogu.com.cn/upload/image_hosting/5ex0x3yg.png)

考虑何时能够包含住最严格曲线，对于当前序列的曲线画出来之后，我们能在当前曲线下方任意行走。由于我们可以 ABAB 这样子快速上下来构造峰，所以峰的个数很容易多，只要我们能走出 $\le k$ 个峰就一定能走出 $k$ 个峰（总长一定的情况下，把大峰拆成若干小峰就可以增加个数），所以贪心地尽可能走出尽量少的峰。

可以现在我们在目前折线下不一定能走出 $\le k$ 个峰，所以需要将原折线进行翻折使得其去包含住一些峰。

交换相邻 $A,B$ 其实就是把一个谷低/峰进行翻折（本题翻折峰没有意义）。翻折一大段的代价就是其面积，翻折面积的意义为逆序对数量。据此进行 dp。借用一张 Rainbow_qwq 博客园里面的图，黑色的是原折线，红色的是最严格折线。我之前试过很多对于黑色折线 dp 的方式，但是都失败了，因为黑色折线波动的规律其实是不多的，我找到了一些但是都不充要，所以我们考虑**对于红色折线进行 dp**，然后让黑色折线去满足红色折线的要求，这样子就不需要对于黑色折线的形态去刻画充要条件了。

![](https://cdn.luogu.com.cn/upload/image_hosting/pyf2kav7.png)

设 $f_{i,j}$ 表示对于前 $i$ 个位置划分出 $j$ 个最严格峰的最小代价，其中 $i$ 表示第 $j$ 个峰结束的位置，就是最后一个峰下降到的最低点。


一个转移 $f_{k,j-1}\to f_{i,j}$，会有一个贡献函数 $\rm cost(l,r)$ 来表示这个代价。就是把 $[l,r]$ 的黑色折线翻折到红色折线的上方的代价。其中这个红色折线已经固定了，就是一个以 $(l,0)$ 和 $(r,0)$ 为两个底部顶点的等腰直角三角形。

上文说过翻折一大段的代价就是其面积，所以黄色部分就是其代价。观察一下图形面积，一段向右下的线段能贡献面积需要一段在 $x$ 轴下方的向右上的线段。考虑如何计算这个面积，在坐标轴中根据直线方程分成两段就是 $\sum \max(x-l-s_x,0)+\sum \max(r-x-s_x,0)$，暴力转移是 $O(n^3)$ 的。

![](https://cdn.luogu.com.cn/upload/image_hosting/v4wmen22.png)

观察到 $f$ 的第二维关于 $k$ 是凸的，可以 wqs 二分处理掉。

同时 $\rm cost(l,r)$ 满足四边形不等式，我们可以用二分队列转移，这个时候时间复杂度为 $O(n\log^2 V)$。可惜 $2\log$ 过不去。

$\rm cost(l,r)$ 函数其实是可以改写成一个去掉 $\max$ 的形式的，因为单次 $s_x$ 最多变化 $1$，所以 $x-l-s_x$ 是单调递增的，能使其 $\ge 0$ 的位置是一段后缀。对于 $r-x-s_x$ 同理。我们提前处理出来这两个转折点，就可以拆掉 $\max$ 写成斜率优化的形式了。

写成斜率优化的形式之后就可以丢掉一个 $\log$ 了。时间复杂度 $O(n\log V)$。

其实上述又带 $l$ 又带 $r$ 的式子很复杂，把坐标轴旋转 $45°$ 之后再计算这个贡献会变成很简单！这启发我们在求解这种 $01$ 序列的时候，观察性质用走斜线画图，计算贡献用旋转 $45°$ 之后的方格图来算。以下代码是按照旋转 $45°$ 之后的贡献方式来算的。

化简贡献方式之后的方程如下，

$$f_{i,j}=\min\{f_{k,j}+w(k+1,i)\}$$

设 $w(l,r)$ 表示区间 $[l,r]$ 的调整代价，不难发现设第 $i$ 个 $A$ 前面有 $c_i$ 个 $B$，那么有$$w(l,r)=\sum\max(c_i-l+1,0)$$。

代码在斜率优化的地方需要维护两个队列，一个是正常的斜率优化，还有一个是在 $\max$ 式子取 $0$ 的时候需要单独开一个单调队列维护。

```cpp
#include<bits/stdc++.h>
#define pb emplace_back
#define fi first
#define se second
#define mp make_pair
using namespace std;
typedef long long ll;
const int maxn=2e6+10;
void cmax(int &x,int y){ x=x>y?x:y; }
void cmin(int &x,int y){ x=x<y?x:y; }
int c[maxn],p[maxn],q[maxn],g[maxn],n,K;
vector<int> vec[maxn],del[maxn]; 
ll s[maxn],dp[maxn]; char ch[maxn];
deque<int> Q;
ll Y(int x){ return dp[x]-s[p[x+1]-1]+1ll*(p[x+1]-1)*x; }
int cmp(int x,int y,int z){
	if((Y(z)-Y(y))*(y-x)<(Y(y)-Y(x))*(z-y)) return 1;
	if((Y(z)-Y(y))*(y-x)==(Y(y)-Y(x))*(z-y)&&g[y]>=g[z]) return 1;
	return 0;
}
int chk(int k,int x,int y){
	if(1ll*k*(y-x)>Y(y)-Y(x)) return 1;
	if(1ll*k*(y-x)==Y(y)-Y(x)&&g[y]<=g[x]) return 1;
	return 0;
}
ll w(int l,int r){
	if(p[l]>r) return 0; 
	return s[r]-s[p[l]-1]+1ll*(r-p[l]+1)*(1-l);
}
int calc(ll x){
	while(Q.size()) Q.pop_front(); 
	memset(dp,0x3f,sizeof(dp));
	for(int i=1;i<=n;i++) g[i]=n+1; 
	int l=1,r=0; Q.push_back(0); dp[0]=g[0]=0;
	for(int i=1;i<=n;i++){
		for(auto z:vec[i]){
			if(Q.size()&&Q.front()==z) Q.pop_front();
			while(l<r&&cmp(q[r-1],q[r],z)) r--;
			q[++r]=z;
		}
		while(l<r&&chk(i,q[l],q[l+1])) l++;
		if(l<=r){
			dp[i]=dp[q[l]]+w(q[l]+1,i)-x;
			g[i]=g[q[l]]+1;
		}
		if(Q.size()){
			int j=Q.front();
			if(dp[j]-x<dp[i]||(dp[j]==dp[i]&&g[j]+1<g[i])){
				dp[i]=dp[j]-x; g[i]=g[j]+1;
			}
		}
		while(Q.size()&&dp[Q.back()]>=dp[i]) Q.pop_back();
		Q.push_back(i);
	}
	return g[n];
}
int main(){
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin>>n>>K>>(ch+1); int cnt=1;
	for(int i=1;i<=2*n;i++)
		if(ch[i]=='A'){
			++cnt;
			c[cnt]=c[cnt-1];
		}else c[cnt]++;
	for(int i=1;i<=n;i++){
		int j=max(p[i-1],i);
		while(c[j]-i+1<0&&j<=n) j++;
		p[i]=j;
	}
	for(int i=0;i<n;i++) vec[p[i+1]].pb(i);
	for(int i=1;i<=n;i++) s[i]=s[i-1]+c[i];
	ll l=-1ll*n*n,r=1ll*n*n;
	while(l<r){//下凸函数,最小化
		ll mid=(l+r+1)>>1;
		if(calc(mid)<=K) l=mid;
		else r=mid-1;
	}
	calc(l); cout<<dp[n]+K*l;
	return 0;
}
```

---

## 作者：Richard_Whr (赞：8)

神仙题目。

将 $A$ 看成左括号，$B$ 看成右括号，对于括号序列逆序对，有一种很形象的刻画方式，就是将括号序列的图像画出来，然后交换一组逆序对就是翻折一个谷：

![](https://cdn.luogu.com.cn/upload/image_hosting/kngir6ys.png)

一段变为有序的逆序对数量就是围成的面积：

![](https://cdn.luogu.com.cn/upload/image_hosting/1pbef78u.png)

随便选一种划分方案，然后将其排好后也画成图像，长成若干段底在坐标轴上的山峰。

如上图蓝色的线。

考虑原始的图像能否选子序列后选成这个图象。

考虑凸出来的部分，发现这部分不受影响，可以选，因为多余的下降部分已经被前面的选走。

凹下去的不行，因为选了一段下降的就不能回来选上升的了。

比如先选了 $EF$ 就不能回来选 $PE$。

因此需要把凹下去的部分翻上去，根据上面的结论，逆序对数量就是差的面积，也就是红色部分。

考虑斜着的不好算，旋转 45°变成正的。

![](https://cdn.luogu.com.cn/upload/image_hosting/pzt1qixn.png)

考虑刻画红色部分的面积。

容易发现这是 $\sum\limits_{i \in [l,r]}\max(0,r-b_i)$，$b_i$ 是每个右括号前面左括号数量，对应到图里就是一条横边的高度。

我们只需要求出来 $cnt_i = \sum\limits_{i}[b_i \le i],sum_i= \sum\limits_{i}[b_i \le i]b_i,s_i=\sum\limits_{j\le i}b_i$，就能表示出来。

然后 $w(l,r)=(cnt_r-(l-1)) \times r-(sum_r-s_{l-1})$

剩下的 dp 优化部分就比较套路了，不再赘述。wqs+斜率优化即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10,Inf=1e12;
char str[N*2];
int s[N]; 
int cnt[N],sum[N],p[N];
int f[N],g[N],q[N];
int n,m;
int ans;

inline int Y(int i){return f[i]+p[i];}

inline int X(int i){return i;}

int Dp(int x)
{
	int hh=0,tt=-1;
	q[++tt]=0;
	for(int i=1;i<=n;i++)
	{
		while(hh<tt && Y(q[hh+1])-Y(q[hh])<=i*(X(q[hh+1])-X(q[hh]))) hh++;
		int j=q[hh];
		f[i]=f[j]+(cnt[i]-j)*i-sum[i]+p[j]-x,g[i]=g[j]+1;
		while(hh<tt && (Y(i)-Y(q[tt]))*(X(q[tt])-X(q[tt-1]))<=(Y(q[tt])-Y(q[tt-1]))*(X(i)-X(q[tt]))) tt--;
		q[++tt]=i; 
	}
	return g[n]; 
}

signed main()
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	
	cin>>n>>m;
	cin>>(str+1);
	int ss=0;
	for(int i=1,j=0;i<=n*2;i++)
	{
		if(str[i]=='A') ss++;
		else s[++j]=ss;
	}
	
	for(int i=1;i<=n;i++)
	{
		if(s[i]<i) ans+=i-s[i],s[i]=i;
		p[i]=p[i-1]+s[i];
	}
	
	for(int i=1;i<=n;i++) cnt[s[i]]++,sum[s[i]]+=s[i];
	for(int i=1;i<=n;i++) cnt[i]+=cnt[i-1],sum[i]+=sum[i-1];
	
	int l=-Inf,r=0,res=0;
	while(l<=r)
	{
		int mid=l+r>>1;
		if(Dp(mid)>=m) res=mid,r=mid-1;
		else l=mid+1;
	}
	
	Dp(res);
	cout<<ans+f[n]+m*res<<"\n";
	
	return 0;
}
```

---

## 作者：123456xwd (赞：6)

容易发现，一个字符串可能合法当且仅当第 $i$ 个 `A` 在第 $i$ 个 `B` 前面。并且，在最优操作下，`A` 或者 `B` 之间的相对顺序一定是不变的，那么一定是第 $[l,r]$ 个 `A` 去匹配第 $[l,r]$ 个 `B`。

设 $w(l,r)$ 表示将第 $[l+1,r]$ 个 `A` 和 `B` 去匹配的代价，设 $b_k$ 表示出现在第 $k$ 个 `A` 之前的 `B` 的数量。则 $w(l,r)=\sum_{k=l+1}^r\max(0,b_k-l)$，相当于去统计会和每个 `A` 交换的 `B` 的数量。

会不会有 `B` 跨越了第 $\le l$ 个 `A` 呢？那么这会在之前就进行计算。

设一个 $f_{i,l}$ 表示当前划分出来了 $l$ 个子序列，下一个子序列开头为第 $i+1$ 个 `A` 所需的最小代价，则：$f_{j,l+1}\gets f_{i,l}+w(i,j)$。

显然 $w(i,j)$ 满足四边形不等式，那么 $f_{n,i=1,2,\cdots}$ 是满足凸性的，且是一个下凸包。（[具体证明](https://www.cnblogs.com/Itst/p/12805678.html)，把他的 $s,r,t$ 看做 $x-1,x,x+1$ 即可）

使用 wqs 二分进行优化，$dp$ 式子变为：$f_j\gets f_i+w(i,j)-mid$。

而考虑设 $p_i$ 表示第一个满足 $b_k\ge i$ 的 $k$，且 $p_i=\max(p_i,i+1)$，则 $w(l,r)=\sum_{i=p_{l}}^r b_i-l$，设 $b_i$ 的前缀和为 $s_i$，则 $w(l,r)=s_r-s_{p_l-1}-l\times(r-p_{l}+1)$。

可以使用斜率优化，时间为 $\mathcal{O}(n\log V)$。

```c++
#include<bits/stdc++.h>
#define ull unsigned long long
#define int long long
#define p_b push_back
#define m_p make_pair
#define pii pair<int,int>
#define fi first
#define se second
#define ls k<<1
#define rs k<<1|1
#define mid ((l+r)>>1)
#define gcd __gcd
#define lowbit(x) (x&(-x))
using namespace std;
int rd(){
    int x=0,f=1; char ch=getchar();
    for(;ch<'0'||ch>'9';ch=getchar())if (ch=='-') f=-1;
    for(;ch>='0'&&ch<='9';ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
    return x*f;
}
void write(int x){
    if(x>9) write(x/10);
    putchar('0'+x%10);
}
const int N=1e6+5,INF=1e12;

int f[N],g[N],q[N];
int b[N],bt,n,K,s[N],p[N];
int X(int i){return i;}
int Y(int i){return f[i]-s[p[i]-1]+p[i]*i-i;}
//维护下凸包
void check(int k){
    int h=0,t=0;
    for(int i=1;i<=n;i++){
        while(h<t&&(Y(q[h+1])-Y(q[h]))<(X(q[h+1])-X(q[h]))*i) h++;
        int j=q[h];
        f[i]=f[j]+s[i]-s[p[j]-1]-j*(i-p[j]+1)+k,g[i]=g[j]+1;
        while(h<t&&(Y(q[t])-Y(q[t-1]))*((X(i)-X(q[t])))>=((Y(i)-Y(q[t])))*(X(q[t])-X(q[t-1])))t--;
        q[++t]=i;    
    }
}

signed main(){
    n=rd(),K=rd();
    for(int i=1,sum=0;i<=2*n;i++){
        char ch=getchar();while(ch!='A'&&ch!='B') ch=getchar();
        if(ch=='A') b[++bt]=sum;
        else sum++;
    }
    for(int i=1;i<=n;i++) s[i]=s[i-1]+b[i];
    for(int i=0;i<=n;i++) p[i]=lower_bound(b+1,b+1+n,i)-b,p[i]=max(p[i],i+1);
    int l=0,r=INF,ans=0;
    while(l<=r){
        check(mid);
        if(g[n]<=K) ans=mid,r=mid-1;
        else l=mid+1;
    }
    check(ans);printf("%lld\n",f[n]-ans*K);
    return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：4)

# P9338 题解

**题目大意**

> 给定一个 $n$ 个 $\texttt{A}$ 和 $n$ 个 $\texttt B$ 组成的字符串 $S$，交换最少对元素使得：
>
> 存在一种方式，把 $S$ 划分为 $k$ 个子序列，每个子序列 $\texttt{A},\texttt B$ 数量相等且所有 $\texttt A$ 在所有 $\texttt B$ 左边。
>
> 数据范围：$n\le 10^6$。

**思路分析**

注意到所有 $\texttt A,\texttt B$ 内部的相对顺序不会变，因此考虑划分 dp，不妨设 $w(l,r)$ 表示把第 $l\sim r$ 个 $\texttt A$ 和 $\texttt B$ 匹配起来的最小代价。

不妨设第 $i$ 个 $\texttt A$ 前面有 $c_i$ 个 $\texttt B$，那么 $w(l,r)=\sum_{k=i}^r\max(0,c_i-l+1)$。

容易验证 $w(l,r)$ 有四边形不等式，且答案关于划分的子序列数是凸的，因此外层 wqs 二分，内层单调队列维护转移即可  $\mathcal O(n\log ^2n)$。

考虑进一步化简 $w(l,r)$：设 $p_i$ 为第一个 $b_k\ge i$ 的 $k$，那么 $w(l,r)=\sum_{k=p_{l-1}}^r c_i-l+1$，设 $c_i$ 前缀和为 $s_i$，那么 $w(l,r)=s_r-s_{p_{l-1}-1}-(l-1)\times (r-p_{l-1}+1)$。

设 wqs 二分的斜率为 $d$，那么转移为 $dp_{i}=\min_{j}\{dp_j+s_i-s_{p_j-1}-j\times(i-p_j+1)\}$，斜率优化即可。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=1e6+5;
const ll  inf=5e11;
int n,k,p[MAXN],c[MAXN],q[MAXN],f[MAXN];
ll s[MAXN],dp[MAXN];
char str[MAXN<<1];
inline ll y(int i) { return dp[i]-s[p[i]-1]+1ll*i*(p[i]-1); }
inline array<ll,2> check(ll x) {
	int hd=0,tl=0;
	for(int i=1;i<=n;++i) {
		while(hd<tl&&y(q[hd+1])-y(q[hd])<1ll*(q[hd+1]-q[hd])*i) ++hd;
		int j=q[hd]; dp[i]=dp[j]+s[i]-s[p[j]-1]-1ll*j*(i-p[j]+1)+x,f[i]=f[j]+1;
		while(hd<tl&&(y(q[tl])-y(q[tl-1]))*(i-q[tl])>(y(i)-y(q[tl]))*(q[tl]-q[tl-1])) --tl;
		q[++tl]=i;
	}
	return {f[n],dp[n]};
}
signed main() {
	scanf("%d%d%s",&n,&k,str+1);
	for(int i=1,id=0,cnt=0;i<=2*n;++i) {
		if(str[i]=='A') c[++id]=cnt,s[id]=c[id]+s[id-1];
		else ++cnt;
	}
	for(int i=1;i<=n;++i) p[i]=lower_bound(c+1,c+n+1,i)-c,p[i]=max(p[i],i+1);
	ll l=0,r=inf,res=inf;
	while(l<=r) {
		ll mid=(l+r)>>1;
		if(check(mid)[0]<=k) res=mid,r=mid-1;
		else l=mid+1;
	}
	printf("%lld\n",check(res)[1]-k*res);
	return 0;
}
```

---

## 作者：Graphcity (赞：3)

非常好题目，使我的 Bitaro 合唱。

我们先不管 $k$ 的限制，只考虑怎么样才能让所有的河狸们能唱起来。

这里给一个结论：**字符串合法当且仅当将男河狸 $A$ 的位置视为 $1$，女河狸 $B$ 的位置视为 $-1$ 后所有的前缀和大于等于 $0$**。这个结论跟 **对于 $i\in [1,n]$，从左往右第 $i$ 个 $A$ 在第 $i$ 个 $B$ 前面** 是等价的。

必要性考虑前 $i$ 个 $B$ 前面至少得有 $i$ 个 $A$；充分性则是考虑直接将第 $i$ 个 $A$ 跟第 $i$ 个 $B$ 进行合唱是一组合法的构造。

显然每次交换都只会将一个 $A$ 换到前面去。通过一些比较快的模拟可以 $O(n)$ 求出交换次数最少的，满足限制的字符串。

然后通过观察，发现最优的匹配方式一定形如前面第 $l\sim r$ 个 $A$ 跟前面第 $l\sim r$ 个 $B$ 进行合唱。证明考虑调整法。

设 $siz_i$ 表示第 $i$ 个 $A$ 前面的 $B$ 个数，$sum$ 为 $siz$ 的前缀和序列。$pre_i$ 表示第 $i$ 个 $B$ 前面的第一个 $A$，$nxt_i$ 表示第 $i$ 个 $A$ 后面的第一个 $B$。

考虑如何求出区间 $[j,i]$ 表示的合唱花费的代价。分类讨论：

- $nxt_i\ge j$：那此时就是合法情况，根本不需要交换。

- 否则，第 $pre_j+1\sim i$ 个 $A$ 都需要交换到第 $j$ 个 $B$ 前面，交换次数为 $sum_i-sum_{pre_j}-(i-pre_j)\times (j-1)$。

现在加入 $k$ 的限制。那我们设 $f_{i,k}$ 表示考虑到位置 $i$，合唱了 $k$ 次的最小交换次数。根据之前的式子可以直接写出转移。这样做是 $O(n^3)$ 的。

通过打表，猜测或 ~~看到数据范围就知道应该优化掉这一维~~ 可以发现转移式子满足四边形不等式，$f$ 具有凸性。那可以通过 WQS 二分直接优化掉第二维。

但这样还是 $O(n^2\log V)$ 的，必须得优化掉枚举前驱这一过程。

发现 $nxt_i$ 具有单调性，前半部分的式子可以使用斜率优化，后半部分的式子相当于 $f$ 最小值的滑动窗口，分别用两个单调队列就可以做到 $O(n)$ 求出所有 $f$。

时间复杂度 $O(n\log V)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=2e6;
const ll inf=4e12;

int n,m; char s[Maxn+5]; ll ans,all;
ll f[Maxn+5],sum[Maxn+5],siz[Maxn+5],Y[Maxn+5];
int pr[Maxn+5],nx[Maxn+5],h[Maxn+5],q[Maxn+5],hd,tl;

inline void Init()
{
    char t[Maxn+5]; int id=0,sum=0,cnt=0,tot=0;
    scanf("%d%d%s",&n,&m,s+1);
    For(i,1,n*2)
    {
        if(s[i]=='A')
        {
            if(cnt) {ans+=id,cnt--; continue;}
            sum++,t[++tot]='A';
        }
        else
        {
            if(!sum) {cnt++,ans-=id,id++,t[++tot]='A',t[++tot]='B'; continue;}
            sum--,id++,t[++tot]='B';
        }
    }
    For(i,1,n*2) s[i]=t[i];
}
inline ll sqr(ll x) {return x*x;}
inline void Build()
{
    static int val[Maxn+5][2],id[Maxn+5][2],R[Maxn+5]; int cur=0;
    For(i,1,n*2) if(s[i]=='A') id[++cur][0]=i,val[i][0]++; cur=0;
    For(i,1,n*2) if(s[i]=='B') id[++cur][1]=i,val[i][1]++; cur=0;
    For(i,1,n*2) For(j,0,1) val[i][j]+=val[i-1][j];
    For(i,1,n) {int k=id[i][0]; siz[i]=val[k][1],sum[i]=sum[i-1]+siz[i];}
    for(int i=1,it=1;i<=n;++i) {while(it<=n && id[it][0]<id[i][1]) it++; pr[i]=it-1;}
    for(int i=n,it=n;i>=1;--i) {while(it>=1 && id[it][1]>id[i][0]) it--; nx[i]=it+1;}
}
inline ll Trans(int i,int j)
{return sum[i]-sum[pr[j+1]]-1ll*(i-pr[j+1])*j;}
inline double Slope(int a,int b) {return 1.0*(Y[b]-Y[a])/(b-a);}
inline auto Check(ll mid)
{
    deque<int> qr; int it=0; hd=1,tl=0;
    auto Update=[&](int x)
    {
        Y[x]=f[x]+1ll*x*pr[x+1]-sum[pr[x+1]];
        while(!qr.empty() && f[x]<=f[qr.back()]) qr.pop_back();
        qr.push_back(x);
    };
    auto Insert=[&](int x)
    {
        while(hd<tl && Slope(q[tl],x)<=Slope(q[tl-1],q[tl])) tl--;
        q[++tl]=x;
    };
    For(i,0,n) f[i]=inf,h[i]=0; f[0]=0,Update(0);
    For(i,1,n)
    {
        while(!qr.empty() && qr.front()<nx[i]-1) qr.pop_front();
        if(!qr.empty())
        {
            int j=qr.front(); ll res=f[j]+mid;
            if(res<f[i]) f[i]=res,h[i]=h[j]+1;
        }
        while(it<nx[i]-1) Insert(it++);
        while(hd<tl && Slope(q[hd],q[hd+1])<=i) hd++;
        if(hd<=tl)
        {
            int j=q[hd]; ll res=f[j]+Trans(i,j)+mid;
            if(res<f[i]) f[i]=res,h[i]=h[j]+1;
        } Update(i);
    }
    return make_pair(f[n],h[n]);
}

int main()
{
    Init(),Build();
    ll l=0,r=inf; all=-inf;
    while(l<r)
    {
        ll mid=(l+r)/2;
        if(Check(mid).second<=m) r=mid; else l=mid+1;
    }
    for(ll i=max(l-2,0ll);i<=min(l+2,inf);++i)
    {
        auto res=Check(i);
        all=max(all,res.first-1ll*i*m);
    }
    cout<<ans+all<<endl;
    return 0;
}
```

---

## 作者：SoyTony (赞：1)

首先通过调整，使得第 $i$ 个 $\texttt{A}$ 在第 $i$ 个 $\texttt{B}$ 之前，容易发现对于所有方案，这样的调整都是要进行的。

之后大致考虑一个 DP，$f_{k,i}$ 表示当前把前 $i$ 个 $\texttt{A}$ 和 $\texttt{B}$ 划分成 $k$ 段的最小操作次数。

转移需要考虑贡献函数 $w(j,i)$ 表示将第 $[j+1,i]$ 的 $\texttt{A}$ 和 $\texttt{B}$ 调整成所有 $\texttt{A}$ 都在 $\texttt{B}$ 前的最小操作次数。由于现在保证第 $i$ 个 $\texttt{A}$ 一定在第 $\texttt{B}$ 前，那么将第 $j+1$ 个 $\texttt{A}$ 到第 $i$ 个 $\texttt{B}$ 的部分拿出来，发现可以分成五部分：一些排名在 $[j+1,i]$ 内的 $\texttt{A}$、一些排名 $\le j$ 的 $\texttt{B}$、一些 $\texttt{A}$ 和 $\texttt{B}$、一些排名 $>i$ 的 $\texttt{A}$ 以及一些排名在 $[j+1,i]$ 内的 $\texttt{B}$。发现实际上操作只在第三部分进行，那么每个 $\texttt{A}$ 需要被操作的次数等于前面 $\texttt{B}$ 的个数。

设 $pre_i$ 表示第 $i$ 个 $\texttt{A}$ 前面 $\texttt{B}$ 的个数，那么得到贡献函数 $w(j,i)=\sum_{p=j+1}^i \max(pre_p-j,0)$，容易证明 $w(j,i)$ 满足四边形不等式，可以 wqs 二分优化。

考虑如何优化内层 DP，首先是去掉取 $\max$，设 $pos_i$ 表示第一个 $pre\ge i$ 的 $\texttt{A}$，得到 $w(j,i)=\sum_{p=pos_j}^i pre_p-j$。记 $pre_i$ 的前缀和 $sum_i$，就化简成了 $w(j,i)=sum_i-sum_{pos_j-1}+(i-pos_j+1)\times j$，可以斜率优化。

同样存在 $pos_j>i$ 的情况不能拆成前缀和，这时贡献函数为 $0$，而由于 $pos_j$ 单调，在斜率优化时可以等到 $\ge pos_j$ 的 $i$ 出现再把 $j$ 加入凸包，同时还要维护没有加入的 $j$ 中 $f_j$ 的最小值，可以单调队列。这样内层 DP 就做到线性。

提交记录：[Submission - AtCoder](https://atcoder.jp/contests/joisp2023/submissions/48207160)

---

