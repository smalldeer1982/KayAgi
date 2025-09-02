# Jellyfish and Mex

## 题目描述

You are given an array of $ n $ nonnegative integers $ a_1, a_2, \dots, a_n $ .

Let $ m $ be a variable that is initialized to $ 0 $ , Jellyfish will perform the following operation $ n $ times:

- select an index $ i $ ( $ 1 \leq i \leq |a| $ ) and delete $ a_i $ from $ a $ .
- add $ \operatorname{MEX}(a)^{\dagger} $ to $ m $ .

Now Jellyfish wants to know the minimum possible final value of $ m $ if he performs all the operations optimally.

 $ ^{\dagger} $ The MEX (minimum excluded) of an array is the smallest non-negative integer that does not belong to the array. For instance:

- The MEX of $ [2,2,1] $ is $ 0 $ , because $ 0 $ does not belong to the array.
- The MEX of $ [3,1,0,1] $ is $ 2 $ , because $ 0 $ and $ 1 $ belong to the array, but $ 2 $ does not.
- The MEX of $ [0,3,1,2] $ is $ 4 $ because $ 0 $ , $ 1 $ , $ 2 $ , and $ 3 $ belong to the array, but $ 4 $ does not.

## 说明/提示

In the first test case, we delete elements from $ a $ in the following order: $ [5,2,\color{red}{1},0,3,0,4,0] \to [5,2,0,3,\color{red}{0},4,0] \to [5,2,\color{red}{0},3,4,0] \to [5,2,3,4,\color{red}{0}] \to [5,2,\color{red}{3},4] \to [\color{red}{5},2,4] \to [\color{red}{2},4] \to [\color{red}{4}] \to [~] $ . The value of $ m $ will be $ 1+1+1+0+0+0+0+0=3 $ .

## 样例 #1

### 输入

```
4
8
5 2 1 0 3 0 4 0
2
1 2
5
1 0 2 114514 0
8
0 1 2 0 1 2 0 3```

### 输出

```
3
0
2
7```

# 题解

## 作者：weitianyi (赞：12)

#### 题目大意
给定一个序列 $a$，每次从序列中删除一个数 $a_i$，将删除这个数后的 $\operatorname{MEX}(a)^{\dagger}$ 加入答案 $m$。求出 $m$ 的最小值。$\operatorname{MEX}(a)^{\dagger}$ 指最小的在 $a$ 中没有出现过的自然数。
#### 题目思路
首先，我们可以发现，如果将 $a$ 序列的 $0$ 全部删除，那么之后的所有 $\operatorname{MEX}(a)^{\dagger}$ 全部是 $0$，不会对答案有影响。

那么我们就可以考虑在删除 $0$ 之前应该删除哪些数。

显而易见，如果 $a_i > \operatorname{MEX}(a)^{\dagger}$，那么 $a_i$ 一定不用删除。

考虑小于 $\operatorname{MEX}(a)^{\dagger}$ 的数，可以进行动态规划，可以发现在 $0$ 之前如果要删数 $x$ 那么必须一次性将所有 $x$ 全部删除。设 $dp_i$ 表示删完所有 $i$ 耗费的最小代价，先从从大到小枚举 $i$，然后枚举 $j$，用 $dp_i$ 来更新 $dp_j$，状态转移方程：
$$\forall j < i, dp_j \leftarrow dp_i + i \times (cnt_j - 1) + j$$
这里的 $cnt_j$ 表示 $j$ 出现的次数，删去 $cnt_j$ 次 $j$，前 $cnt_j - 1$ 次每次代价是 $i$，最后一次的代价是 $j$。
#### 实现代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T, n;
map<int,int> cnt;
int dp[5005];
signed main() {
	ios :: sync_with_stdio(false); 
	cin >> T;
	while (T--) {
		cin >> n;
		cnt.clear();
		memset(dp, 0x3f, sizeof(dp));
		for (int i = 1, tmp; i <= n; i++) {
			cin >> tmp;
			cnt[tmp]++;
		}
		int mex = 0;
		while (cnt[mex]) mex++;
		dp[mex] = 0;
		for (int i = mex; i >= 1; i--) {
			for (int j = 0; j < i; j++) {
				dp[j] = min(dp[j], dp[i] + (cnt[j] - 1) * i + j);
			}
		}
		cout << dp[0] << endl;
		
	}
	return 0;
} 
```

---

## 作者：MarSer020 (赞：11)

$\Large\text{Solution}$

首先有一个很 naive 的想法，就是把所有 $0$ 依次删掉，再删其他数，但是这显然是假的。

手玩样例可以发现最优解一定是每次将相同值的所有元素依次删掉，而且每次删掉的元素值是单调递减的。

于是就能得到一个 $\text{dp}$：设 $f_i$ 表示删除若干个元素使得当前序列的 $\text{mex}$ 值为 $i$ 的最小代价，转移式为 $f_i=\min\{f_j+j\times (cnt_i-1)+i\}$，$cnt_i$ 表示满足 $a_j=i$ 的 $j$ 的个数。

设 $k$ 为原序列的 $\text{mex}$ 值，发现当 $a_i>k$ 时显然不会有贡献，将这一部分删除即可，时间复杂度 $\Theta(nk)$。

到这里已经可以通过本题，但是考虑进行优化：

我们考虑什么样的点才会有贡献。

我们发现 $f$ 数组里有很多无用状态，例如当 $cnt_i\le cnt_j,i<j$ 时，删掉 $i$ 显然比删掉 $j$ 更优，此时 $f_j$ 这一状态显然不需要维护。

考虑如何处理出这一类位置，可以用栈维护。将 $0$ 到 $k$ 依次试着加入栈，若此时的 $i$ 满足 $cnt_i<cnt_{top}$ 则入栈，容易发现栈内元素个数是 $O(\sqrt{n})$ 级别的，在栈上跑上述 $\text{dp}$ 即可，时空复杂度 $\Theta(n)$。

对于 $n\le 3\times 10^7$ 的数据范围，在极限数据下下面的代码可以跑进 $\text{0.5s}$。

当 $n\le 3\times 10^7$ 时注意要开 `long long`。

$\Large\text{Code}$

```cpp
#include<bits/stdc++.h>
#define int long long
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?EOF:*p1++)
using namespace std;
static char buf[1<<20],*p1=buf,*p2=buf;
int n,t,cnt[30000005],dp[30000005],mex,a[30000005],top;
int read(){
    int x=0;
    char ch=getchar();
    while(!isdigit(ch))
        ch=getchar();
    while(isdigit(ch))
        x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return x;
}
void solve(){
    n=read(),mex=top=0;
    for(int i=0;i<=n+1;i++)
    	dp[i]=1e18,cnt[i]=0;
    for(int i=1,x;i<=n;i++){
    	x=read();
    	if(x<=n)
    		cnt[x]++;
    }
    for(int i=0;i<=n+1;i++)
    	if(!cnt[i]){
    		mex=i;
    		break;
    	}
    a[++top]=0;
    for(int i=1;i<=mex;i++)
    	if(cnt[i]<cnt[a[top]])
    		a[++top]=i;
    n=top,dp[n]=0;
    for(int i=n-1;i>=1;i--)
    	for(int j=i+1;j<=n;j++)
    		dp[i]=min(dp[i],dp[j]+(cnt[a[i]]-1)*a[j]+a[i]);
    cout<<dp[1]<<'\n';
}
signed main(){
    t=read();
    while(t--)
        solve();
    return 0;
}
```

---

## 作者：Lucky_Cloud (赞：7)

很简单的题。~~虽然没在考场上做出来~~

## 分析

我们经过思考，容易得出以下结论：

1. 如果当前 $mex = x$，则下一个删的数一定小于 $x$。
1. 如果 $mex = 0$，那么我们就可以不往下算了，因为它们对答案的贡献为 $0$。

我们设 $f[i]$ 表示当 $mex = i$ 时，$m$ 的值。

则有：

$$f[i] = \min(f[j] + (c[i] - 1) \times j + i, f[i])$$

其中 $j > i$，$c[i]$ 表示 $i$ 在 $a$ 中的个数。

因为，我们要使 $mex = i$，就必须将 $i$ 这个数删去，并且 $0 \sim i-1$ 都还存在于 $a$ 中。我们会删 $c[i]$ 次，但 $c[i] - 1$ 次，$m$ 会加上上一个 $mex$ 的值。 第 $c[i]$ 次则会加上 $i$，也就是新的 $mex$。

设没删任何数的 $mex = first$。

根据定义，初始化 $f[first] = 0$。

根据上述结论，与定义，答案即为 $f[0]$。

## Code

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned ll 
using namespace std;

const int N = 5e3 + 5;
int t, x, p;
ll c[N], f[N];
ll pre, now, n;
 
int main() {
    ios::sync_with_stdio(0);
    cin >> t;
    while (t--) {
        cin >> n;
        ll mx = 0;
        memset(c, 0, sizeof c);
        memset(f, 0x3f, sizeof f);
        for (int i = 1; i <= n; i++) {
            ll x;
            cin >> x;
            if (x <= 5001) c[x]++, mx = max(mx, x);//因为至多 5000 个数，但数可能大于 5000。
        }
        for (int i = 0; i <= mx + 1; i++) {//找到没删任何数时的 mex。
            if (!c[i]) {
                p = i;
                break;
            }
        }
        f[p] = 0;
        for (int i = p; i >= 0; i--) {
            for (int j = i - 1; j >= 0; j--) {
                f[j] = min(f[i] + (c[j] - 1) * i + j, f[j]);
            }
        }
        cout << f[0] << '\n';
    }
    return 0;
} 
```

---

## 作者：rui_er (赞：6)

显然，除非 $\operatorname{mex}a=0$，否则不会删除 $>\operatorname{mex}a$ 的数。而 $\operatorname{mex}a=0$ 时不对答案产生贡献，因此任意时刻我们都可以忽略 $a$ 中 $>\operatorname{mex}a$ 的数。

又显然，一旦我们开始删一个数，就会先把所有与之相等的数删光。否则，设最先删光的数为 $x$，把所有删除 $x$ 的操作提到最前面一定更优。

至此，我们自然地设 $f_i$ 表示假设只保留所有 $<i$ 的数，此时删光的最小代价。注意到，我们忽略了 $>\operatorname{mex}a$ 的数，此时 $i$ 的取值范围是 $[0,\operatorname{mex}a]$，由 $\operatorname{mex}$ 的定义可知此时 $\operatorname{mex}a=i$。

考察首先要删光哪个数，不妨设为 $j$（$j < i$）。设 $j$ 出现次数为 $cnt(j)$。显然，前 $cnt(j)-1$ 次删除时 $j$ 还未被删光，此时对答案贡献为 $i$；最后一次删除时 $j$ 已被删光，此时对答案贡献为 $j$。删除结束后，剩余的数列满足保留了所有 $<j$ 的数，且 $\operatorname{mex}a=j$。此时，所有 $[j+1,i-1]$ 的数都可以被忽略，问题转化为 $f_j$。因此，得到转移方程：

$$
f_i=
\begin{cases}
0,&i=0\\
\min\limits_{j<i}\{f_j+(cnt(j)-1)\times i+j\},&i>0
\end{cases}
$$

时间复杂度 $O(n^2)$。

```cpp
// Problem: D. Jellyfish and Mex
// Contest: Codeforces - Codeforces Round 901 (Div. 2)
// URL: https://codeforces.com/problemset/problem/1875/D
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x, y, z) for(ll x = (y); x <= (z); ++x)
#define per(x, y, z) for(ll x = (y); x >= (z); --x)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do {freopen(s".in", "r", stdin); freopen(s".out", "w", stdout);} while(false)
#define endl '\n'
using namespace std;
typedef long long ll;

mt19937 rnd(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
ll randint(ll L, ll R) {
    uniform_int_distribution<ll> dist(L, R);
    return dist(rnd);
}

template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}

const ll N = 5e3 + 5, inf = 0x1f1f1f1f1f1f1f1fll;

ll T, n, a[N], cnt[N], dp[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    for(cin >> T; T; T--) {
        cin >> n;
        rep(i, 1, n) {
            cin >> a[i];
            if(a[i] <= n) ++cnt[a[i]];
        }
        ll mex = 0;
        while(cnt[mex]) ++mex;
        rep(i, 1, mex) dp[i] = inf;
        rep(i, 1, mex) rep(j, 0, i - 1) chkmin(dp[i], dp[j] + (cnt[j] - 1) * i + j);
        cout << dp[mex] << endl;
        rep(i, 0, n) cnt[i] = 0;
    }
    return 0;
}
```

---

## 作者：__K2FeO4 (赞：2)

本蒟蒻不太会 dp， 列出式子直接转图论搞 Dijkstra 了。

好久不写 Dijkstra 了，考场上来不及……不要有 3 个小时就掉以轻心。

------------

首先，我们目的是把所有 $0$ 删光。这样就会有 $\operatorname{mex}a=0$，使后续所有操作贡献为 $0$。

其次，不删 $0$ 是为了减小 $\operatorname{mex}a$，而大于  $\operatorname{mex}a$ 的数被删去不会对 $\operatorname{mex}a$ 产生任何影响。因此在 $\operatorname{mex}a=0$ 之前，只删小于等于 $\operatorname{mex}a$ 的数。

还有，要删一个数就要把它全删光。否则，要么可以不删比它大的数，要么直接选择比它小的数。

设 $cnt_i$ 为数字 $i$ 出现的次数。记录时记到 $\operatorname{mex}a$ 即可。则 $\operatorname{mex}a=m$ 删 $i$ 的代价为 $m\times(cnt_i-1)+i$。

又设 $d_j$ 为在 $0$ 之前**倒数**第 $j$ 个删掉的数。则总代价为：
$$
\begin{aligned}
ans&=d_1\times(cnt_{0}-1)+0+d_2\times(cnt_{d_1}-1)+d_1+\dots+d_k\times(cnt_{d_{k-1}}-1)+d_{k-1}+\operatorname{mex}a\times(cnt_{d_k}-1)+d_k\\
&=d_1\times cnt_{0}+d_2\times cnt_{d_1}+\dots+d_k\times cnt_{d_{k-1}}+\operatorname{mex}a\times cnt_{k}-\operatorname{mex}a
\end{aligned}
$$
因此我们可以建一张结点为 $0\sim \operatorname{mex}a$ 完全图（但不标准，因为有向）。若对于结点 $i,j$ 满足 $i<j$ 则连一条权值为 $j\times cnt_i$ 的边，跑 $0$ 到 $\operatorname{mex}a$ 的最短路即可。别忘记**最后要减 $\operatorname{mex}a$！**

完全图用堆优化会变慢，所以用正常 $O(n^2)$ 就行了。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=5004;
int n,m,t,a[N],c[N],dis[N];
bool v[N];
//74-year-old PRC!
//Chinese dream soars to the 9th heaven!
signed main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		scanf("%d",a+i);
		sort(a+1,a+n+1);
		if(a[1]){
			puts("0");
			continue;
		}
		m=1,c[0]=1;
		while(m<n&&a[m]+1>=a[m+1])m++,c[a[m]]++;//mex=a[m]+1
		//n=m,m=a[m]+1;
		//for(int i=0;i<=m;i++)
		for(int j=1;j<=a[m]+1;j++)
		dis[j]=c[0]*j;
		dis[0]=0;
		int cur=0;
		while(!v[cur]){
			v[cur]=true;
			for(int j=cur+1;j<=a[m]+1;j++){
				if(!v[j]&&dis[j]>dis[cur]+c[cur]*j){
					dis[j]=dis[cur]+c[cur]*j;
				}
			}
			int minn=0x3f3f3f3f;
			for(int j=0;j<=a[m]+1;j++){
				if(!v[j]&&minn>dis[j]){
					minn=dis[j];
					cur=j;
				}
			}
		}
		
		printf("%d\n",dis[a[m]+1]-a[m]-1);
		for(int i=0;i<=m+1;i++)a[i]=c[i]=dis[i]=0,v[i]=false;
		
	}
	return 0;
}
*/
```


---

## 作者：sunkuangzheng (赞：1)

好题遇到阴间场，惋惜。

**【题目大意】**

你有一个数列 $a$ 和初始为 $0$ 的变量 $x$，每次操作删除 $a$ 中一个整数，并使 $x \gets x + \operatorname{mex}(a)$（先删除再增加），问若可以任意确定删除顺序，删掉所有元素后 $x$ 的最小值。

$1 \le n \le 5000,0 \le a_i \le 10^9$。

**【题目分析】**

先考虑贪心。

有个很单纯的思路：删掉所有 $0$，这样删别的数字代价都是 $0$。但显然这是错的，比如 $0,0,0,1$，最优方案是删除 $1$ 后再删除 $0$，代价为 $5$。

但是我们还是可以沿用上面的思想：每次尝试让 $\ge m$ 的所有数字删除代价为 $0$，我们需要找到若干个决策点 $m$，并删除所有 $a_i = m$ 的 $a_i$。当你这样删除到 $0$ 后，之后的所有数字代价都是 $0$。容易证明这样的策略一定不劣。

接下来考虑如何选择决策点 $m$，看到数据范围允许 $n^2$，考虑 dp。设 $f_i$ 表示**只考虑 $0 \sim i$ 的数字的情况下，删除了小于等于 $i$** 的所有数字的最小花费。转移方程是 $f_i = \min\limits_{j=1}^i\{f_{j-1}+(num_j-1)(i+1)+j\}$，其中 $num_j$ 表示数字 $j$ 的出现次数。

考虑式子的含义，枚举上一个转移点 $j$，删除所有 $j$，其中前 $num_{j}-1$ 个的代价是现在的 $\operatorname{mex}$，即 $i+1$，而最后一个则是删完了所有 $j$ 的 $\operatorname{mex}$。由于前 $j-1$ 个数字已经删除，所以 $j+1 \sim i$ 的代价都是 $0$。

我们在开始 dp 前，找到第一个 $a_i$ 不连续的地方断开，显然上面一部分没有意义，对下面一部分 dp 即可，时间复杂度 $\mathcal O(n^2)$。

注意 dp 的边界 $i = 0$。

**【赛时代码】**

```cpp
/**
 *    author: sunkuangzheng
 *    created: 30.09.2023 23:44:27
**/
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,n,a[500005],b[500005],f[500005];
signed main(){
    ios::sync_with_stdio(0),cin.tie(0);
    cin >> t;
    while(t --){
        cin >> n;int ans = 0;
        for(int i = 1;i <= n;i ++) f[i] = 1e18,b[i] = 0;b[0] = 0;
        for(int i = 1;i <= n;i ++) {
            cin >> a[i];if(a[i] <= n) b[a[i]] ++;
        }a[n+1] = 1e18;
        sort(a+1,a+n+1);if(a[1]){cout << "0\n";continue;}
        int p = 0,mx = -1;f[0] = b[0] - 1;
        for(int i = 1;i <= n;i ++) if(a[i] + 1 < a[i+1]) {p = i,mx = a[i];break;}
        for(int i = 1;i <= mx;i ++){
            f[i] = (b[0] - 1) * (i + 1);
            for(int j = 1;j <= i;j ++) f[i] = min(f[i],f[j-1] + (b[j]-1) * (i + 1) + j);
        }cout << f[mx] << "\n";
    }
}
```


---

## 作者：Didncan_yu (赞：0)

[cf 传送门](https://codeforces.com/problemset/problem/1875/D)  
[原题传送门](https://www.luogu.com.cn/problem/CF1875D)

### 题目大意

每次删去 $a$ 数组中的一个数，$m$ 加上删去一个数后最小的未在 $a$ 数组中出现的自然数（即为 $\operatorname{mex} a$），直至 $a$ 数组所有数被删除。

求 $m$ 的最小值。

### 思路分析

观察第三个样例：
```
5
1 0 2 114514 0
```
我们先将其排序：
```
5
0 0 1 2 114514
```
可以发现此时 $\operatorname{mex} a = 3$。那么此时删去 $114514$ 后不会有任何改变，而删去 $ < 3$ 的数会使 $\operatorname{mex} a$ 更小，从而使 $m$ 更小。所以我们应优先删除 $ < \operatorname{mex} a$ 的数。

同时在删除全部 $ < \operatorname{mex} a$ 的数后，$ \operatorname{mex} a = 0$，删除上例中类似 $114514$ 的数也没有影响。 

所以可以得到第一个结论：**可以忽略 $ > \operatorname{mex} a$ 的数。**

同时考虑到第二个结论：**如果选择删除 $a_i$，那么就应该删除所有 $ = a_i$ 的数。**

回到上面的样例：
```
5
0 0 1 2 114514
```
如果你选择删除一个 $0$ 后删除 $1$，那么肯定是不如删除两个 $0$ 的。

### 具体操作

定义 $k_i$ 为 $a$ 数组中 $i$ 的个数，$dp_i$ 为 $ \operatorname{mex} a = i$ 时 $m$ 的最小值。

而考虑如何转移 $dp_i$：删完 $j (j<i) $ 后，由第一个结论得：此时 $dp_i$ 即为 $dp_j$ 和本次删除的代价。此时前 $k_j - 1$ 次操作代价总共为 $(k_j-1) \times i$，最后一次代价为 $j$。

推出转移方程：
$$dp_i = \min_{j<i}(dp_j + (k_j-1) \times i + j)$$
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read();
inline void write(long long n);
int t,n;
long long dp[5501],a[5501],k[5501];
void slove(){
	n=read();
	int b=n;
	a[0]=-1;
	for(int i=1;i<=n;i++)
		a[i]=read();
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++){
		if(a[i]-a[i-1]>1){
			b=a[i-1]+1;
			break;
		}
		k[a[i]]++;
		b=a[i]+1;
	}
	dp[0]=0;
	for(int i=1;i<=b;i++){
		for(int j=0;j<i;j++){
			dp[i]=min(dp[i],dp[j]+(k[j]-1)*i+j);
		}
	}
	write(dp[b]);
	putchar('\n');
}
int main(){
	t=read();
	while(t--){
		memset(a,0,sizeof(a));
		memset(dp,127,sizeof(dp));
		memset(k,0,sizeof(k));
		slove();
	}
	return 0;
}
inline int read(){
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
	return s*w;
}
inline void write(long long n){
	if(n<0){putchar('-');n=-n;}
	if(n>9){write(n/10);}
	putchar(n%10+'0');
}
```


---

## 作者：One_JuRuo (赞：0)

## 思路

看到 $n$ 的范围只有 $5000$，并且 $\sum n$ 的范围也是 $5000$，所以可以考虑 $n^2$ 的做法。

每次操作肯定都是一次性删完某个数字，如果删除某个数字删一半又去删别的数字，答案肯定会变大。

所以我们可以考虑统计所有数字的数量，记为 $num_i$，来计算删完某个数字的最小答案，记为 $ans_i$。

那么我们可以考虑用大于 $i$ 的 $j$ 来更新 $ans_i$，$j$ 代表上一次删除的是 $j$，所以当前的 $\operatorname{mex}$ 应该就是 $j$，那么删除 $i$ 得到的值应该是 $(num_i-1)\times j+i$，因为删除的前 $(num_i-1)$ 次的 $\operatorname{mex}$ 是 $j$，最后一次是 $i$。

所以我们只需要倒着求 $ans_i$ 即可，最后的答案是 $ans_0$。

另外，统计 $\operatorname{mex}$ 以内的数即可，大于 $\operatorname{mex}$ 的数都是无用的。并且，在这个方法没有删除的数字就最后挨个删除就好，反正 $\operatorname{mex}$ 都是 $0$ 没有影响。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
long long T,n,a[5005],now,num[5005],dp[5005][5005],ans[5005];
int main()
{
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld",&n),now=num[0]=0;
		for(int i=1;i<=n;++i) scanf("%lld",&a[i]);
		sort(a+1,a+n+1);//排序
		for(int i=1;i<=n;++i)
		{
			if(a[i]==now) ++num[now];//统计num，now最后就是mex
			else if(a[i]==now+1&&num[now]) num[++now]=1;
			else break;
		}
		if(!num[0]){printf("0\n");continue;}//mex最开始就是0
		ans[now+1]=0;//预处理
		for(int i=now;i>=0;--i)
		{
			ans[i]=0x3f3f3f3f;//赋初值
			for(int j=i+1;j<=now+1;++j) ans[i]=min(ans[i],ans[j]+(num[i]-1)*j+i);//更新答案
		}
		printf("%lld\n",ans[0]);
	}
	return 0;
}
```

---

## 作者：Coffee_zzz (赞：0)

考虑 dp。

定义 $dp_i$ 表示使 $\operatorname{MEX}(a)$ 变为 $i$ 的最小花费。

我们令 $cnt_i$ 表示 $a$ 中 $i$ 出现的次数。这里我们只需要记录小于 $\operatorname{MEX}(a)$ 的 $i$ 的数量即可，因为再大就用不到了。

显然，如果我们想让 $\operatorname{MEX}(a)$ 变为 $i$，就需要删掉 $a$ 中所有为 $i$ 的元素，即删除 $cnt_i$ 次。

我们令 $\operatorname{MEX}(a)=k$，依次对 $k-1$ 到 $0$ 的每一个 $i$ 进行转移。

我们可以一上来直接把 $cnt_i$ 个 $i$ 全删了，那么会花费 $(cnt_i-1)\times k$。

或者我们可以在 $\operatorname{MEX}(a)=j$ 的基础上去删，那么花费为 $dp_j+cnt_i\times j$。

所以可以得到转移方程为：

$$dp_i=\min((cnt_i-1)\times k,\min\limits_{j=i+1}^{k-1}(dp_j+cnt_i\times j))$$

其中当 $i+1\gt k-1$ 时，$\min\limits_{j=i+1}^{k-1}(dp_j+cnt_i\times j))=\infty$。

那么答案显然就是 $dp_0$。

不需要初始化，把 $cnt$ 和 $k$ 预处理出来就行。

记得开 `long long`。

```c++
#define int long long
const int N=5005;
int a[N],dp[N],cnt[N];
void solve(){
	int n,las=-1;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=0;i<=n;i++) cnt[i]=0;
	sort(a+1,a+1+n);
	for(int i=1;i<=n;i++){
		if(a[i]==las+1) las++,cnt[a[i]]++;
		else if(a[i]==las) cnt[a[i]]++; 
		else break;
	}
	las++;
	for(int i=las-1;i>=0;i--){
		dp[i]=las*(cnt[i]-1);
		for(int j=i+1;j<=las;j++){
			dp[i]=min(dp[i],dp[j]+j*cnt[i]);
		}
	}
	cout<<dp[0]<<endl;
}
```

---

## 作者：accgj_ (赞：0)

[题目链接](https://www.luogu.com.cn/problem/CF1875D)



------------
题目大意：给出一个长度为 $n$ 的序列，每次从中删除一个数直到删完，求每次**删数之后**的序列的 mex 的和的最小值。



------------
显然有一个贪心：若当前的 mex 是 $i$，那么先删比 $i$ 小的数，因为比 $i$ 大的数已经对 mex 没有贡献了，后删就更优。

那么就有了一个状态，$f_i$ 表示 mex 为 $i$ 时的代价（即删数之后的序列的 mex 的和的最小值）。

而对于每一个 $f_i$，都能从 $f_j (j>i)$ 转移过来。

令 $num_i$ 为 $i$ 的个数，列出式子：$f_i=\min{f_j+j \times(num_i-1)+i} (j>i)$。

即把 $i$ 变成新的 mex，前 $num_i-1$ 次删完后的 mex 还是 $j$，最后一次删完的 mex 就是 $i$。

那么最后的答案就是 $f_0$，此时 mex 为 0，所以剩下的还没删的数就都没有贡献了。



------------
代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int n;
long long a[100001];
long long num[5005];
long long f[5005];
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>t;
	while(t--)
	{
		cin>>n;
		for(int i=1;i<=n;i++)cin>>a[i];
		sort(a+1,a+1+n);
		memset(num,0,sizeof(num));
		long long x=0;
		for(int i=1;i<=n;i++)
		{
			if(a[i]==x)
			{
				num[x]++;continue;
			}
			if(a[i]==x+1 and num[x]!=0)
			{
				x++;num[x]++;continue;
			}
			if(num[x]!=0)x++;break;
		}
		memset(f,0x3f,sizeof(f));
		if(x==a[n])x++;
		f[x]=0;
		for(long long i=x;i>0;i--)
		{
			for(long long j=i-1;j>=0;j--)
			{
				f[j]=min(f[j],f[i]+i*(num[j]-1)+j);
			}
		}
		cout<<f[0]<<"\n";
	}
	return 0;
}

```


---

## 作者：OIerBoy (赞：0)

# 大意
每次删去 $a$ 数组中的一个数，$m$ 加上删去一个数后最小的未在 $a$ 数组中出现的自然数（即为 $\operatorname{mex}a$），直至 $a$ 数组所有数被删除。
# Sol
这道题一眼 dp。

我们需要考虑的是对于函数 $\operatorname{mex}$ 的性质，假设当前 $a$ 数组存在 $0\sim x$，则 $\operatorname{mex}a=x+1$。再记每一个数出现过 $s_0,s_1,\cdots s_n$，如果当前我将数字 $i$ 全部取出，代价就为 $s_i\times (x+1)$，而之后的 $\operatorname{mex}a=i$。

那么一个很明显的贪心，我们需要先用最小的代价将 $\operatorname{mex}a$ 变为 $0$，再去删除剩余的就不需要有任何代价了。

我们记 $f_{i}$ 表示将 $\operatorname{mex}a$ 变为 $i$ 的最小代价。转移就是：

$$f_i=\begin{cases}\min\limits_{j=i+1}^{tot}\{f_j+s_i\times j\} & (j\not=tot)\\ \min\{f_j+(s_i-1)\times j\} & (j=tot)\end{cases}$$

这里的 $tot$ 表示为初始数组 $a$ 的 $\operatorname{mex}$。

时间复杂度为 $O(n^2)$。

# Code
```cpp
#include<bits/stdc++.h>
#define db doub
#define inf LONG_LONG_MAX
#define fir first
#define sec second
#define ls (x<<1)
#define rs (x<<1|1)
#define mid ((l+r)>>1)
#define Pr(i,j) pair<i,j>
#define PB(i) push_back(i)
#define MP(i,j) make_pair(i,j)
#define Fo(i,j) for(auto i:j)
#define mem(i,j) memset(i,j,sizeof(i))
#define FO(i,j,k) for(int i=j;i;i=k)
#define FFF(i,j,k) for(auto i=j;i!=k;++i)
#define For(i,j,k) for(int i=j;i<=k;++i)
#define FoR(i,j,k) for(int i=j;i^k;++i)
#define FOR(i,j,k) for(int i=j;i>=k;--i)
using namespace std;
template <typename _Tp>void read(_Tp& first) {
    _Tp x = 0, f = 1; char c = getchar();
    while (!isdigit(c)) {if (c == '-') f = -1; c = getchar();}
    while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ '0'), c = getchar();
    first = x * f;
}
#define N 50005
#define Mod 1000000007
#define int long long
int n,T,tot;
int a[N],f[N];
int k[N];
signed main(){
    read(T);
    while(T--){
        tot=0;
        mem(k,0);
        mem(f,0x7f);
        read(n);
        For(i,1,n)read(a[i]);
        sort(a+1,a+1+n);
        For(i,1,n){
            if(tot==a[i])k[tot++]=1;
            else if(tot>a[i])k[a[i]]++;
            else break;
        }
        f[tot]=0;
        FOR(i,tot,0){
            For(j,0,i-1){
                f[j]=min(f[j],f[i]+i*(k[j]-(tot==i)));
            }
        }
        cout<<f[0]<<endl;
    }
    return 0;
}
```

---

