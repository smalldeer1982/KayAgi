# [ABC373F] Knapsack with Diminishing Values

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc373/tasks/abc373_f

$ N $ 種類の品物があり、 $ i $ 種類目の品物の重みは $ w_i $、価値は $ v_i $ です。どの種類の品物も $ 10^{10} $ 個ずつあります。

高橋君はこれから、品物をいくつか選んで、容量 $ W $ のバッグに入れます。高橋君は、選ぶ品物の価値を大きくしつつ、同じ種類の品物ばかりにならないようにしたいです。そこで高橋君は、$ i $ 種類目の品物を $ k_i $ 個選んだときの **うれしさ** を $ k_i\ v_i\ -\ k_i^2 $ と定義したとき、選んだ品物の重さの総和を $ W $ 以下にしつつ、各種類のうれしさの総和が最大になるように品物を選びます。高橋君が達成できる、うれしさの総和の最大値を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 3000 $
- $ 1\ \leq\ W\ \leq\ 3000 $
- $ 1\ \leq\ w_i\ \leq\ W $
- $ 1\ \leq\ v_i\ \leq\ 10^9 $
- 入力はすべて整数
 
### Sample Explanation 1

$ 1 $ 種類目の品物を $ 2 $ 個、$ 2 $ 種類目の品物を $ 1 $ 個選ぶと、うれしさの総和を $ 5 $ にすることができ、これが最適です。 $ 1 $ 種類目の品物についてのうれしさは $ 2\ \times\ 4\ -\ 2^2\ =\ 4 $、$ 2 $ 種類目の品物についてのうれしさは $ 1\ \times\ 2\ -\ 1^2\ =\ 1 $ です。 また、重さの総和は $ 9 $ であり、容量 $ 10 $ のバッグに入ります。

## 样例 #1

### 输入

```
2 10
3 4
3 2```

### 输出

```
5```

## 样例 #2

### 输入

```
3 6
1 4
2 3
2 7```

### 输出

```
14```

## 样例 #3

### 输入

```
1 10
1 7```

### 输出

```
12```

# 题解

## 作者：wangshulin (赞：11)

# 前言
有时候不要用 edge 的 GPT 侧边栏翻译，会把 $10^{10}$ 翻译成 $10$，害得我罚多了一发。
# 思路
提供一个很清奇的不用优先队列的解法。

首先，对于此题目的数据范围而言 $10^{10}$ 个物品就是 $+\infty$，这是因为 $W \le 3000,v \ge 1$，$\max\left\{\frac{w}{v}\right\}=3000 < 10^{10}$。

那么为什么不能跑完全背包呢？因为对于同种物品，$a$ 个该种物品的幸福值 $av_{i}-a^{2}$ 和 $b$ 个该种物品的幸福值 $bv_{i}-b^{2}$ 不能叠加成 $a+b$ 个该种物品的幸福值 $(a+b)v_{i}-(a+b)^{2}$！

遇事不决，先打暴力！

枚举要取多少个物品，枚举每个物品要取多少个，直接跑 $0/1$ 背包。

这是暴力 [code](https://atcoder.jp/contests/abc373/submissions/58226952)。

然后超时了，分析一下，发现是因为当 $w_{i}$ 都很小时，暴力的时间复杂度退化成 $O(NW^{2})$。让 $w_{i}$ 全部都变得很大肯定是不行的，我们退而求其次，如果 $w_{i}$ 全部不相同，因为当 $W$ 为整数，$O(\sum_{i=1}^{W} \frac{W}{i})=O(\ln W)$，所以时间复杂度就是 $O(NW \ln W)$，足以通过本题。

那么只需要预处理出 $h_{i,j}$——选 $j$ 个重量为 $i$ 的物品可以获得的最大幸福值，而 $h_{i,j}$ 可以通过一个很简单的贪心求得——“选 $j$ 个的最优方案”实际上一定是在“选 $j-1$ 个的最优方案”的基础上将某个物品的数量增加 $1$。~~我在赛时只是感知了一下它的正确性就打了~~，实际上根据开口向下的二次函数的导数递减的性质就能证明。
# 代码
赛时 [code](https://atcoder.jp/contests/abc373/submissions/58234498)。

---

## 作者：g1ove (赞：7)

容易发现这是一个完全背包问题，我们设状态 $f_{i,j}$ 表示前 $i$ 个物品使用了 $j$ 个容量的最大价值。

容易写出转移方程式：$f_{i,j}=\max\limits_{k=0}^{\lfloor\frac{j}{w}\rfloor} f_{i-1,j-kw}+kv-k^2$

直接 dp 是 $O(n^3)$。考虑对这个 dp 进行优化。

上面的方程容易写成滚动数组的形式。不妨设上一维状态为 $g$，这一维为 $f$。

## Solution 1
将后面的 $kv-k^2$ 记为 $T(k)$，则一段区间 $[l,r]$ 价值记为 $w(l,r)$，则 $w(l,r)=T(r-l+1)$。发现若对于决策点 $a,a+1,b,b+1$，始终满足 $w(a,b)+w(a+1,b+1)\ge w(a,b+1)+w(a+1,b)$。

将 $j$ 按对 $w$ 取模后的值分类后使用决策单调性优化即可。时间复杂度 $O(n^2\log n)$。

## Solution 2
同样对 $j$ 按对 $w$ 取模后的值分类。改写 dp 式子：$f_{i}=\max g_j+(i-j)v-(i-j)^2$。

对式子拆分：$f_{i}=g_j+iv-jv-i^2-j^2+2ij$

移项得 $g_j-jv-j^2=-2ij+i^2+fi-iv$

容易发现这是斜率优化的形式，且 $k=-2i$ 为单调的， $x=i$ 也是单调的，使用单调队列可以优化到 $O(n^2)$。

------
决策单调性：[code](https://atcoder.jp/contests/abc373/submissions/58217629)

斜率优化：[code](https://atcoder.jp/contests/abc373/submissions/58256160)

还是建议写决策单调性，码量小细节少。

---

## 作者：Hadtsti (赞：5)

### 题意简述

- $n$ 件物品容积为 $m$ 的完全背包，但每种物品选 $k$ 件的价值是 $kv_i-k^2$。

- $n,m\le 3000$。

### 题目分析

首先很容易转化一下条件，把第 $k$ 次选的那件 $i$ 物品价值改成 $v_i-2k+1$。然后一种物品就被拆成了一堆，直接做 01 背包会 T。

考虑 $n,m$ 不是很大，再看到 $3s$ 的时限，略大于 $O(nm)$ 的做法是可以被接受的。我们又发现当体积 $w$ 一定时，有用的物品最多有 $\frac mw$ 个，这是一个很好的性质，因为 $\sum\limits_{w=1}^m\frac mw=m\sum\limits_{w=1}^m\frac1w=m\ln m$。

那么我们直接对一定体积的物品二分出有用的物品最小价值，暴力做 01 背包就行了。时间复杂度 $O(m\log V+m^2\log m)$。

二分的时候一定要算对价值，否则会假并 T 得很惨。要开 `long long`！

### 代码实现


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,x,y;
long long f[3010];
vector<int>E[3010];
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&x,&y);
		E[x].push_back(y);
	}
	for(int i=1;i<=m;i++)
	{
		int tar=m/i,L=1,R=1000000000;
		while(L<R)
		{
			int mid=L+R+1>>1;
			long long cnt=0;
			for(int j:E[i])
				cnt+=max((j-mid+1)/2,0);
			if(cnt>=tar)
				L=mid;
			else
				R=mid-1;
		}
		for(int j:E[i])
			for(int k=1;k<=j-L;k+=2)
				for(int l=m;l>=i;l--)
					f[l]=max(f[l],f[l-i]+j-k);
	}
	printf("%lld",f[m]);
	return 0;
}
```

---

## 作者：_WRYYY_ (赞：5)

[ABC373 题解合订版（A~F）。](https://www.cnblogs.com/wryyy-233/p/18439686)

一眼 dp 题。

暴力转移是简单的，令 $f_{i,j}$ 表示算到第 $i$ 个人，使用容量为 $j$，$w_i,v_i$ 同原题，对于每个 $j$，$lim$ 表示最多可以放多少个 $i$，并且满足 $-k^2+kv_i>0$ 。

则 $f_{i,j}=\max_{k=1}^{lim} f_{i-1,j-kw_i}-k^2+kv_i$，并且还要和 $f_{i-1,j}$ 取 $\max$。

显然可以滚掉一维，写的时候注意以下枚举顺序就是了。

$f_j=\max_{k=1}^{lim} f_{j-kw_i}$。

然后呢？这个转移方程是暴力 $O(NW^2)$ 的。怎么优化它？

我发现它没有前途，做不到将其优化（可能是因为我菜）。

可以考虑将 $f_j$ 做前缀 $\max$，以求单调性方面的优化，可是以 $k\in[1,lim]$ 为 $x$ 轴时，$-k^2+kv_i$ 是单峰的并且可知峰顶横坐标，$f_j$ 却是单调不降的，结果二者相加不满足单调性，我们没法二分或是三分。

后面实质就是引导至官方做法了。

因为 $W$ 不大，可能会有相同的 $w_i$，难道我们每个都要给他遍历一遍吗？这样显然是不好的。

那么我们就想，对于 $w_i$ 相同的 $i$，我们可不可以求出使用 $k$ 个 $w_i$ 时取不同的 $v_i$ 的最大值是多少。当然可以。

但是暴力求解还是 $NW^2$ 的，不好。但是我们还有 $-K^2+Kv_i$ 这个式子可以入手，拆解后可以得到：

$-K^2+Kv_i=\sum_{k=1}^{K}v_i-2k+1$。

也就是说对于一个每多用一次 $i$，加上的权值都是之前的权值减二。

所以我们可以把所有的 $v_i-1$ 放入优先队列中，每取出一次就给这个值减二再放回去，这样取 $lim$ 次就知道所有的合法 $k$ 对应的最大值是多少。

这里的复杂度是 $O(N\log^2N)$，两只老鸽，一只来自优先队列，一只来自调和级数。（认为 $N,W$ 同阶，下同）

这样，我们对每个 $w(1\le w\le W)$ 就都只会遍历一遍，总时间复杂度就为 $O(N^2\log N)$。

## Code：


```cpp
#include <bits/stdc++.h>
#include <bits/extc++.h>
#define ll long long
#define ull unsigned long long
#define m_p make_pair
#define m_t make_tuple
#define N 3010
using namespace std;
using namespace __gnu_pbds;
ll dp[N], f[N];
vector<int> vec[N];
signed main()
{
	// auto ___IN___ = freopen("dc.in", "r", stdin);
	// auto ___OUT___ = freopen("test.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int n, W, w, val;
	cin >> n >> W;
	for (int i = 1; i <= n; i++)
	{
		cin >> w >> val;
		vec[w].push_back(val);
	}
	std::priority_queue<int> q;
	for (int i = 1; i <= W; i++)
	{
		while (!q.empty())
			q.pop();
		for (auto val : vec[i])
			q.push(val - 1);
		if (q.empty())
			continue;
		for (int j = 1; j * i <= W; j++)
		{
			f[j] = f[j - 1] + q.top();
			q.push(q.top() - 2);
			q.pop();
		}
		for (int j = W; j; j--)
			for (int k = 1; k * i <= j; k++)
				dp[j] = max(dp[j], dp[j - k * i] + f[k]);
	}
	cout << dp[W];
	return 0;
}
```

---

## 作者：DengDuck (赞：4)

挺好玩的题，场上差不多 30min 过了。

考虑到不太能背包，注意到价格的取值只有 $\mathcal O(M)$ 的级别，考虑按照价格对物品分类。

分类之后内部可以贪心，考虑每次选择一个可以让答案变得最大的物品。因此我们可以求出 $G(i,j)$ 表示价格为 $i$ 的物品中选择 $j$ 件可获得的最大价值。

然后我们就可以直接 DP 了，设 $F(i,j)$ 表示当前选了价格在 $[1,i]$ 的物品，选择的总价格为 $j$ 的最大价值。

直接枚举买的物品的质量，考虑优化一下枚举的范围之后时间复杂度大概是一个调和级数，也就是 $\mathcal O(nm\log m)$。

```cpp
#include<bits/stdc++.h>
#define LL long long
#define pb push_back
using namespace std;
const int N=3005;
int n,m;
LL Mx[N][N],Hav[N],W[N],K[N],F[N][N],Ans;
vector<int>V[N];
inline LL Cal(LL x,LL y){return K[x]*y-y*y;}
struct Node
{
	LL V,i,id;
	bool operator<(const Node&x)const{return V<x.V;}
};
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld%lld",&W[i],&K[i]);	
		V[W[i]].pb(i);
	}
	for(int i=1;i<=m;i++)
	{
		if(V[i].empty())continue;
		for(int j:V[i])Hav[j]=0;
		priority_queue<Node>Q;
		for(int j:V[i])Q.push({Cal(j,1),0,j});
		for(int k=1;k<=m/i;k++)
		{
			Node t=Q.top();Q.pop();
			Mx[i][k]=max(0ll,Mx[i][k-1]+t.V);
			t.i++;
			t.V=Cal(t.id,t.i+1)-Cal(t.id,t.i);
			Q.push(t);
		}
	}
	for(LL i=1;i<=m;i++)
	{
		for(LL j=0;j<=m/i;j++)
		for(LL k=0;k+i*j<=m;k++)
		{
			F[i][i*j+k]=max(F[i-1][k]+Mx[i][j],F[i][i*j+k]);
			Ans=max(F[i][i*j+k],Ans);
		}
	}
	printf("%lld\n",Ans);
}
```

---

## 作者：LHLeisus (赞：2)

[AtCoder](https://atcoder.jp/contests/abc373/tasks/abc373_f)|[Luogu](https://www.luogu.com.cn/problem/AT_abc373_f)|[cnblogs](https://www.cnblogs.com/LHLeisus/p/18438838)

比较遗憾，E 题用了太多时间了，没做出来。当时看到有平方感觉难道是斜率优化之类的？这下猜对了。
拜谢 WA90。
不过官解好像没用斜率优化？不会。

设 $f_{i,j}$ 表示前 $i$ 个物品一共用了 $j$ 的体积。直接暴力做是三次方的。

当加入一个体积为 $w$，价值为 $v$ 的物品时，就像单调队列优化多重背包一样，我们把 $j$ 按照模 $w$ 分组，只有组间会转移。设 $g_k=f_{i-1,j}(j=d+kw)$，同样地设一个 $h$ 对应新的 $f_i$，那么就有转移：

$$
h_i=\max_{j\le i}g_j+(i-j)v-(i-j)^2
$$

是我们喜欢的斜率优化。

$$
j^2+jv-g_j=2ij+iv-h_i
$$

把 $f$ 还原就做完了。时间复杂度 $\mathcal{O}(nW)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define FOR(i,a,b) for(int i=(a);i<=(b);++i)
#define ROF(i,a,b) for(int i=(a);i>=(b);--i)
#define mp(a,b) make_pair(a,b)
#define pll pair<long long,long long>
#define pii pair<int,int>
#define fi first
#define se second
#define eb emplace_back
#define ep emplace
#define pc __builtin_popcount
using namespace std;
typedef long long ll;
typedef double db;
const int N=3e3+5;
const int inf=0x3f3f3f3f;
const int INF=0x7f7f7f7f;
inline int read();
int n,m,k,W,w[N],v[N],f[N][N],g[N],q[N],l,r,I;
int X(int i){return i;}
int Y(int i){return i*i+i*v[I]-g[i];}
signed main()
{
	n=read(),W=read();
	FOR(i,1,n)w[i]=read(),v[i]=read();
	FOR(id,1,n){
		I=id;
		memset(g,0,sizeof g);
		FOR(d,0,w[id]-1){
			int tmp=d;int tot=-1;
			while(tmp<=W){
				g[++tot]=f[id-1][tmp];
				tmp+=w[id];
			}
			l=1,r=0;
			FOR(i,0,tot){
				while(l<r&&(Y(i)-Y(q[r]))*(X(q[r])-X(q[r-1]))<=(Y(q[r])-Y(q[r-1]))*(X(i)-X(q[r])))r--;
				q[++r]=i;
				while(l<r&&Y(q[l+1])-Y(q[l])<=2*i*(X(q[l+1])-X(q[l])))l++;
				if(l<=r)f[id][d+i*w[id]]=g[q[l]]+i*v[id]-q[l]*v[id]-i*i-q[l]*q[l]+2*i*q[l];
			}
		}
	}
	FOR(i,1,W)f[n][i]=max(f[n][i],f[n][i-1]);
	printf("%lld",f[n][W]);
	return 0;
	//あまりに短い夏だけで何を残していけるのかな？
}


inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return f*x;
}
```

---

## 作者：Gordon_Song (赞：2)

容易想到一种 $O(n^3)$ 的做法。设 $dp_{i,j}$ 表示前 $i$ 个数用了 $j$ 的容积的最大 happy 值。

注意到 $m < 3000$ 这一奇怪的条件，可以考虑使用调和级数相关的做法。

容易发现对于体积相同的物品，可以通过贪心正确地求出取若干个出来的最大 happy 值。所以将所有体积相同（设为 $i$）的归为一类，求出一个数组 $C$，其中 $C_{i,k}$ 表示在占用 $i \times k$ 的体积时，只用体积为 $i$ 的数最大能获得的 happy 值。然后就转化为了一个新的背包问题：有 $W$ 种数，其中第 $i$ 种的体积是 $i$。选 $j$ 个 $i$ 可以获得的 happy 值为 $C_{i,j}$，求体积不超过 $W$ 时的最大可收获的 happy 值。

使用 dp 暴力转移求这个问题的复杂度是正确的，为 $O(W \times (\sum_{i=1}^W \frac{W}{i}))$，也即 $O(W^2\log W)$

[代码](https://atcoder.jp/contests/abc373/submissions/58233770)

---

## 作者：—_—_—_ (赞：1)

写了一种比较玄学的做法：

首先，如果直接暴力跑背包的话，对于 $n$ 个物品，我们最多取 $w$ 个，背包的容量为 $w$，复杂度为$O(NW^2)$，显然会超时。但我们不妨把取的每个同一个物品都当做不同的物品来看。这样我们对于第 $j$ 次取第 $i$ 个物品，其价值为 $v_{i,j}=v_i+(j-1)^2-j^2$。只有当物品 $i$ 前 $j-1$ 次我们要取的时候我们才会考虑是否取第 $j$ 次物品。换句话说，我们用 $dp_x$ 表示当体积为 $x$ 时的最大价值，只有当 $v_{i,j-1}$ 更新了 dp 方程的最大值，我们才会考虑将 $v_{i,j}$ 参与转移。这样虽然看上去复杂度和原来没区别，但实际上每次能够更新 dp 状态的物品数量是有限的。如果我们用优先队列对需要检查的物品按价值从大到小排序，则每次会更新 dp 方程的物品数量会进一步减小。实测代码跑下来最慢的点也只用了 $19$ 毫秒。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=3e3+5;
#define ll long long
int n,W;
int w[maxn];
ll v[maxn],dp[maxn];
struct node
{
    ll w,v,num,prev;
    bool operator<(const node &b) const{
        if(v==b.v)
        {
            return w>b.w;
        }
        return v<b.v;
    }
};
int main()
{
    scanf("%d%d",&n,&W);
    priority_queue<node> pq;
    for(int i=1;i<=n;i++)
    {
    	scanf("%d%lld",&w[i],&v[i]);
        pq.push({w[i],v[i]-1,1,v[i]});
    }
    int cnt=0;
    while(!pq.empty())
    {
        node tp=pq.top();
        pq.pop();
        bool flag=false;
        for(int j=W;j>=tp.num*tp.w;j--)
        {
            if(dp[j]<dp[j-tp.w]+tp.v)
            {
            	dp[j]=dp[j-tp.w]+tp.v;
                flag=true;
            }
        }
        if(flag&&tp.prev+(tp.num)*(tp.num)-(tp.num+1)*(tp.num+1)>0)
        {
        	pq.push({tp.w,tp.prev+(tp.num)*(tp.num)-(tp.num+1)*(tp.num+1),tp.num+1,tp.prev});
        	
		}
    }
    //for(int i=1;i<W;i++) printf("%d ",dp[W]);
    printf("%lld\n",dp[W]);
}
```

---

## 作者：not_clever_syl (赞：1)

写一个能跑 $W$ 更大数据的做法，AT 官方给的题解是 $O(W^2\log W)$ 的，但是有 $O(nW\log W)$ 的做法。

考虑第 $i$ 个物品 $(w,v)$ 以及由前 $i-1$ 个物品组成的 dp 数组为 $f$，前 $i$ 个物品组成的 dp 数组为 $g$。

那么我们有：

$$
g_i=\max_{t=0}^{\lfloor \frac{i}{w} \rfloor}
\lbrace{f_{i-wt}+t(v-t)}\rbrace
$$

这个 dp 是 $O(nW^2)$ 的。

考虑怎么优化。

可以发现对于 $i \bmod w$ 相等的下标分成一类时，dp 过程不会访问别的类的下标。

所以我们枚举 $j=0 \sim w-1$，然后记 $f'_i=f_{j+iw},g'_i=g_{j+iw},m=\lfloor \frac{n-j}{w} \rfloor$。

于是我们有：$g'_i=\max\limits_{k=0}^i\lbrace {f_{i-k}+k(v-k)}\rbrace$。

观察这个柿子，可以令 $h_i(x)=f'_i+(x-i)(v-x+i)$。

然后就可以写成：$g'_i=\max\limits_{k=0}^i h_k(i)$。

把 $h_i(x)$ 柿子拆一下可以得到 $h_i(x)=-x^2+(2i+v)x+(i^2-iv+f_i)$。

于是设 $l_i(x)=(2i+v)x+(i^2-iv+f_i)$，那么 $h_i(x)=l_i(x)-x^2$，所以：

$$
\begin{aligned}
g'_i
&=\max\limits_{k=0}^i h_k(i)\\
&=\max\limits_{k=0}^i l_k(i)-i^2\\
&=-i^2+\max\limits_{k=0}^i l_k(i)\\
\end{aligned}
$$

所以我们只需要维护后面的那坨直线的 $\max$，动态维护一个凸包即可。

然后你注意到 $l_i(x)$ 的斜率大于 $l_{i-1}(x)$ 的斜率，所以直接单调栈上二分即可维护。

总时间复杂度 $O(nW\log W)$。

---

## 作者：Kreado (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc373_f)。

## 思路

不妨令 $c_{i,j}$ 表示权重为 $i$ 的物品选了 $j$ 个的最大价值，接下来我们只需对 $c_{i,j}$ 做分组背包即可做到 $\mathcal{O}(nW\log W)$。

对于每个权重 $i$，考虑从 $j-1$ 状态（即选了 $j-1$ 个物品的状态）贪心（即选择能使当前价值最大的一个）的转移过来，由于价值函数是一个二次函数，所以这样的贪心是显然正确的。


```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int Maxn=1e5+6;
int n,W;
int w[Maxn],v[Maxn];
vector<int>vp[Maxn];
int c[Maxn];
ll num[3002][3002];
ll f[3002];

int main(){
    cin>>n>>W;
    for(int i=1;i<=n;i++)
        cin>>w[i]>>v[i],
        vp[w[i]].emplace_back(i);
    for(int i=1;i<=W;i++){
        if(vp[i].empty()) continue;
        for(int j=1;j<=W;j++) c[j]=0;
        for(int j=1;j<=W;j++){
            ll ret=-1e9;int ps=0;
            for(auto k:vp[i]){
                ll res=1ll*(c[k]+1)*(v[k]-c[k]-1)-1ll*c[k]*(v[k]-c[k]);
                if(res>ret) ret=res,ps=k;
            }
            c[ps]++;
            num[i][j]=num[i][j-1]+ret;
        }
    }

    for(int i=1;i<=W;i++){
        for(int j=W;j;j--){
            for(int k=1;i*k<=W;k++){
                if(j>=i*k) f[j]=max(f[j],f[j-i*k]+num[i][k]);
            }
        }
    }

    ll ans=-1e9;
    for(int i=0;i<=W;i++) ans=max(ans,f[i]);
    printf("%lld\n",ans);

    system("pause");
    return 0;
}
```

---

## 作者：liujy_ (赞：0)

首先考虑写一个暴力的 DP 方程，设 $f_{i,j}$ 表示现在放到了第 $i$ 种物品，且用了 $j$ 的容量的最大快乐值。然后有 $f_{i,j}=\max_{k=0}^{m} f_{i-1,j-k\times w_i}+k\times v_i-k^2$。   
改写一下上面那个式子的形式，设 $x=\lfloor \frac{j}{w_i}\rfloor,y=\lfloor \frac{k}{w_i}\rfloor$。  
有下面的转移方程  
$$\begin{aligned}f_{i,j}&=\max_{k=0}^{m} f_{i-1,j-k\times w_i}+(x-y)\times v_i+(x+y)^2 \\&=\max_{k=0}^{m} f_{i-1,j-k\times w_i}+x\times v_i-y\times v_i-x^2-y^2+2xy\end{aligned} $$     
上面的式子可以分为只和 $j$ 有关的和只和 $k$ 有关的以及 $2xy$ 这一部分，我们考虑斜率优化，把 $j$ 除以 $w_i$ 余数相同的部分放在一起。$x,y$ 显然都是单调的，可以直接单调队列维护。时间复杂度 $O(n^2)$。   

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3005;
int n,m,w[N],v[N],q[N][N],l[N],r[N];
long long f[N][N],k[N],b[N];
bool check(int x,int y,int z){
	return ((k[z]-k[y])*(b[y]-b[x]))<=((k[y]-k[x])*(b[z]-b[y]));
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d%d",&w[i],&v[i]);
	for(int i=1;i<=n;i++){
		for(int j=0;j<=m;j++)l[j]=1,r[j]=0;
		for(int j=0;j<=m;j++){
			int x=j%w[i],y=j/w[i];
			k[j]=2*y,b[j]=f[i-1][j]-y*y-1ll*y*v[i];
			while(r[x]-l[x]>=1&&check(q[x][r[x]-1],q[x][r[x]],j))r[x]--;
			q[x][++r[x]]=j;
			while(r[x]-l[x]>=1&&(b[q[x][l[x]+1]]-b[q[x][l[x]]])>=-(k[q[x][l[x]+1]]-k[q[x][l[x]]])*y)l[x]++;
			f[i][j]=k[q[x][l[x]]]*y+b[q[x][l[x]]]+1ll*y*v[i]-y*y;
		}
		for(int j=0;j<=m;j++)f[i][j]=max(f[i][j],f[i][j-1]);
	}
	printf("%lld\n",f[n][m]);
	return 0;
}

```

---

## 作者：zrl123456 (赞：0)

[[ABC373F] Knapsack with Diminishing Values ](https://www.luogu.com.cn/problem/AT_abc373_f)  

题目考察：背包。  
题目简述：  
给你一个背包和 $n$ 个物品，第 $i$ 个物品代价为 $w_i$，价值为 $v_i$，数量为 $1145141919810$，出题人~~为了让这个题变难~~设你选择第 $i$ 个物品 $k$ 次，那么他会将你获得的价值变为 $kv_i-k^2$。在代价不大于 $w$ 的基础上，求你获得的最大价值。  
数据范围：
- $1\le n,w\le 3000$
- $\forall i\in[1,n],1\le w_i\le w,1\le v_i\le 10^9$
---
暴力的多重背包时间复杂度为 $\Theta(nw^2)$，显然不可行。  
我们发现，每多选一个第 $i$ 个物品（设以前选了 $k$ 个）就会增加 $v_i-1-2k$ 价值，我们将一个物品拆成 $v_i-1,v_i-3,\dots$ 这些新物品（当然了，价值为负的不能取）。由于代价相同的我们优先选价值高的，所以我们将代价（$w_k$）相同的放在一起，并降序排序，并取前 $\displaystyle\lfloor\frac{w}{w_k}\rfloor$ 个（因为只有这些有贡献）进行 dp。  
这样时间复杂度是调和级数，为 $\Theta(nw\log w)$。  

[代码](https://atcoder.jp/contests/abc373/submissions/58269526)

---

## 作者：freoepn (赞：0)

考虑背包，将选第 $j$ 次选的第 $i$ 个物品的价值定义为选 $j$ 个和选 $j-1$ 个时价值的差，发现这个价值一定随着 $j$ 变大而变小，则选到第 $j$ 个物品时前 $j-1$ 个一定选完，直接跑即可。

但这样物品数量太多，考虑如何优化，所有重量为 $x$ 的物品顶多选 $\lfloor\frac{w}{x} \rfloor$ 个，贪心选出重量为 $x$ 的物品中价值前 $\lfloor\frac{w}{x} \rfloor$ 个进行背包，这样物品数量是调和极数的，可以通过。


```cpp
#include <bits/stdc++.h>
using namespace std;
vector<long long> v[3005];
long long dp[3005];
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0),cout.tie(0);
  int n, w;
  cin >> n >> w;
  for (int i = 1; i <= n; i++) {
    long long x, y, sum = 0, e = 0;
    cin >> x >> y;
    for (long long j = 1; j * x <= w; j++) {
      e = (j * y - j * j);
      if (sum >= e) {
        break;
      }
    //  cout << x << " "<< e-sum << '\n';
      v[x].push_back(e - sum);
      sum = e;
    }
  }
  vector<pair<long long, long long> > a;
  for (int i = 1; i <= w; i++) {
    sort(v[i].begin(), v[i].end());
    reverse(v[i].begin(), v[i].end());
    for (int j = 0; j < v[i].size() && (j + 1) * i <= w; j++) {
      a.push_back(make_pair(i, v[i][j]));
    }
  }
  for(int i = 0;i < a.size();i++){
    for(int j = w-a[i].first;j >= 0;j--){
      dp[a[i].first + j] = max(dp[a[i].first+j],dp[j] + a[i].second);
    }
  }
  long long maxn = 0;
  for(int i = 0;i <= w;i++){
    maxn = max(maxn,dp[i]);
  }
  cout << maxn << '\n';
}
```

---

