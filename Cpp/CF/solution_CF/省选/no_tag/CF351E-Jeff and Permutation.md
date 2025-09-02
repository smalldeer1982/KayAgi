# Jeff and Permutation

## 题目描述

Jeff's friends know full well that the boy likes to get sequences and arrays for his birthday. Thus, Jeff got sequence $ p_{1},p_{2},...,p_{n} $ for his birthday.

Jeff hates inversions in sequences. An inversion in sequence $ a_{1},a_{2},...,a_{n} $ is a pair of indexes $ i,j $ $ (1<=i<j<=n) $ , such that an inequality $ a_{i}>a_{j} $ holds.

Jeff can multiply some numbers of the sequence $ p $ by -1. At that, he wants the number of inversions in the sequence to be minimum. Help Jeff and find the minimum number of inversions he manages to get.

## 样例 #1

### 输入

```
2
2 1
```

### 输出

```
0
```

## 样例 #2

### 输入

```
9
-2 0 -1 0 -1 2 1 0 -1
```

### 输出

```
6
```

# 题解

## 作者：LlLlCc (赞：15)

首先，不难想到，答案和读进来的数的正负性是无关的，所以我们可以在写快读时不判负数

要求出逆序对的最小个数，我们得先了解什么是逆序对

逆序对：$a_i>a_j\;(i<j)$

有就是说前面的数比后面的大就是逆序对，可以看出逆序对是和由数的大小决定的

贪心的想法就是前面的尽量为负，后面的尽量为正。但这样一个数取正负和前面后面的值都有关系，也就是有后效性，不太好处理

我们换一种方向思考

对于序列$a$，我们找到最大的$a_i$

对于$a_i$来说，他取正取负和其他数没有关系

为什么呢？其实非常显然

- 取正：由于这个数是最大的，所以前面的所有数取正或取负都不会大于这个数，也就是说对于前面的数不会产生逆序对。同时，因为这个数是最大的，所以后面的数不管怎么取，都一定比这个数小，对于后面的数就一定会产生$n-i$对逆序对

- 取负：由于这个数是最大的，所以前面的所有数取正或取负都不会小于这个数，也就是说对于前面的数一定会产生$i-1$逆序对。同时，因为这个数是最大的，所以后面的数不管怎么取，都一定比这个数大，对于后面的数就一定不会产生逆序对

可以看出，$a_i$无论取正取负都与其他数的取法没有任何关系，所以$a_i$的贡献就等于$\min(i-1,n-i)$

所以最大的数我们处理完了，那么接下来怎么处理第$2$大、第$3$大、第$4$大$\cdots$呢？

刚刚我们已经知道了最大的数的取法和其他数的取法都没有关系，所以说其他数的取法和最大的数的取法也没有关系

因为第$kth$大的数对最大数的贡献（是否产生逆序对），已经在处理最大的数时处理掉了，所以最大的数已经没有任何用了，可以删掉了

这时，就有了如下$O(n^2)$代码：
```
#include<bits/stdc++.h>
#define maxn 1000005
#define ll long long
using namespace std;
int a[2[maxn],n,N,c[2][maxn],L[maxn],R[maxn];
bool vis[maxn];
ll Ans;
inline int read(){
	int ret=0;char ch=getchar();
	while (ch<'0'||ch>'9') ch=getchar();
	while (ch<='9'&&ch>='0') ret=ret*10+ch-'0',ch=getchar();
	return ret;
}
int main(){
	n=N=read();  
	for (int i=1;i<=n;i++) a[1[i]=read();
	for (int i=1;i<=n;i++){
		int Mx=-1,k=0,tot=0,l=0,r=0;
		for (int j=1;j<=N;j++) if (a[i&1][j]>Mx) Mx=a[i&1][j],k=j;
		for (int j=1;j<k;j++) if (a[i&1][j]==Mx) l++;
		for (int j=k+1;j<=N;j++) if (a[i&1][j]==Mx) r++;
		Ans+=min(k-1-l,N-k-r);
		for (int j=1;j<=N;j++) if (j!=k) a[1-i&1][++tot]=a[i&1][j];
		N=tot;
	}
	   printf("%lld",Ans);
	return 0;
}
```

但显然数据一大就萎了，我们考虑优化

我们再来模拟一遍暴力的流程

- 找到最小值$\rightarrow \min(i-1,n-i)\rightarrow $删除最小值$\rightarrow$ 重构数组$\rightarrow$找到最小值 $\cdots$

多看几遍就发现直接的暴力很多操作都显得多余

可以发现，找到最大值后，左边有$i-1$个比他小的右边有$n-i$个。但因为我们之前删的都是比这个数大的，所以左右边有多少个比他小的数，是一直不变的，也就是可以预处了

问题就转化成求：

$$\Large \sum\limits_{i=1}^n \min(\sum\limits_{j=1}^{i-1} [a_j<a_i]+\sum\limits_{k=i+1}^{n} [a_k<a_i])$$

这个问题就非常好求了，权值线段树就能$O(nlogn)$完美处理

## code
```
#include<bits/stdc++.h>
#define maxn 1000005
#define ll long long
using namespace std;
int a[maxn],n,L[maxn],R[maxn],N;
bool vis[maxn];
ll Ans;
struct lc{
	int L,R,x;
}tree[maxn];
inline int read(){
	int ret=0;char ch=getchar();
	while (ch<'0'||ch>'9') ch=getchar();
	while (ch<='9'&&ch>='0') ret=ret*10+ch-'0',ch=getchar();
	return ret;
}
inline void build(int k,int L,int R){
	tree[k].L=L,tree[k].R=R;
	if (L==R){tree[k].x=0;return;}
	int mid=L+R>>1;
	build(k<<1,L,mid);build(k<<1|1,mid+1,R);
    tree[k].x=0;
}
inline int Get(int k,int L,int R){
	if (R<L) return 0;
	if (tree[k].L>=L&&tree[k].R<=R) return tree[k].x;
	int mid=tree[k].L+tree[k].R>>1,sum=0;
	if (L<=mid) sum+=Get(k<<1,L,R);
	if (R>mid) sum+=Get(k<<1|1,L,R);
	return sum;
}
inline void change(int k,int x){
	if (tree[k].L==tree[k].R&&tree[k].L==x){tree[k].x++;return;}
	int mid=tree[k].L+tree[k].R>>1;
	if (x<=mid) change(k<<1,x);
	else change(k<<1|1,x);
	tree[k].x=tree[k<<1].x+tree[k<<1|1].x;
}
int main(){
	n=read(); 
	for (int i=1;i<=n;i++) a[i]=read(),N=max(N,a[i]);
	build(1,0,N);
	for (int i=1;i<=n;i++) L[i]=Get(1,0,a[i]-1),change(1,a[i]);
	build(1,0,N);
	for (int i=n;i;i--) R[i]=Get(1,0,a[i]-1),change(1,a[i]);
	for (int i=1;i<=n;i++) Ans+=min(R[i],L[i]);
	printf("%lld",Ans);
	return 0;
}
```







---

## 作者：Little_x_starTYJ (赞：14)

### 解题思路
首先我们可以得到读入时 $a_i$ 的正负不影响答案，因为我们可以进行一次操作将它们变成它们的相反数，从而使其变成原数，因此，我们可以将 $a_i$ 取绝对值。

我们使 $1\le i < j \le n$，那么会有两种情况：

- $a_i > a_j$，如果想要制造出逆序对，要么 $a_i,a_j$ 都不变成相反数，要么只有 $a_j$ 变成相反数。

- $a_i < a_j$，如果想要制造出逆序对，要么 $a_i,a_j$ 都变成相反数，要么只有 $a_j$ 变成相反数。

- $a_i = a_j$，如果想要制造出逆序对，只能够 $a_j$ 变成相反数。

因此，我们只需要取它变成相反数时与没变成相反数时的最小答案即可。

感谢 @奇米 的题解给作者提供了思路。

CODE:
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, a[2010];
signed main() {
	ios::sync_with_stdio(false);
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n;
	int ans = 0;
	for (int i = 1; i <= n; i++)
		cin >> a[i], a[i] = abs(a[i]);
	for (register int i = n; i >= 1; i--) {
		int cnt = 0, res = 0;
		for (register int j = 1; j < i; j++)
			if (a[j] < a[i])
				cnt++;
		for (register int j = i + 1; j <= n; j++)
			if (a[j] < a[i])
				res++;
		ans += min(res, cnt);
	}
	cout << ans;
	return 0;
}
```

---

## 作者：奇米 (赞：13)

# $\mathrm{CF351E\ Jeff \ and \ Permutation}$

### 题目意思

* [题目传送门](https://www.luogu.com.cn/problem/CF351E)

* 题目很小清新：就是对每个数可以进行取反操作。问经过任意次操作后序列逆序对最少数目。

* $n\leq 2000$

### $\mathrm{Sol}$

* 正如$\mathrm{xlh}$说，这是道考智商的题目。

* 我们首先对序列中的每个$a_i$变成$|a_i|$。这操作并不会影响结果（你可以把它在变回去）。以下出现的$a_i$都是$|a_i|$

* 然后我们考虑对于一组$(i,j),i<j$ 会产生逆序对的情况：

	* $\mathrm{Case1\ a_i<a_j}$
    	
 	  那么要产生逆序对只能：$(1)$让$a_j$取反，$a_i$不变，$(2)$让$a_i,a_j$都取反
        
	* $\mathrm{Case2\ a_i>a_j}$
  	  	
  	  那么要产生逆序对只能： $(1)$让$a_i,a_j$都不取反，$(2)a_i$不取反，$a_j$取反
        
        
* 那么综上两种情况：如果$a_i$不选择取反，那么就是第二种情况（后面的数比他小），否则$a_i$取反那么就是前面比他小的数都会产生贡献。然后就对左右两边统计比$a_i$小的个数取$min$，计数器加加就可以了。

* 时间复杂度：$\mathrm{O(n^2)/O(n\log n)}$ 

### $\mathrm{Code}$

```cpp
#include <bits/stdc++.h>
#define pb push_back
using namespace std;

inline int read()
{
	int sum=0,ff=1; char ch=getchar();
	while(!isdigit(ch))
	{
		if(ch=='-') ff=-1;
		ch=getchar();
	}
	while(isdigit(ch))
		sum=sum*10+(ch^48),ch=getchar();
	return sum*ff;
}

const int N=2005;

int n,m,a[N];
long long ans;

int main()
{
	n=read();
	for ( int i=1;i<=n;i++ ) 
	{
		a[i]=read();
		a[i]=abs(a[i]);
	}
	for ( int i=1;i<=n;i++ ) 
	{
		int L=0,R=0;
		for ( int j=1;j<i;j++ ) if(a[j]<a[i]) L++;
		for ( int j=i+1;j<=n;j++ ) if(a[j]<a[i]) R++;
		ans+=min(L,R);
	}
	printf("%lld\n",ans);
	return 0;
}
```



---

## 作者：LroseC (赞：10)

关于这道题，貌似所有题解都漏掉了对于 `abs(a[i]) == abs(a[j])` 这种情况的讨论，我决定写一篇题解进行补充。

#### 题意简述
给定你一个长度为 $n$ 的序列 $a$，你可以将序列中任意个元素变成它的相反数，问得到的新序列逆序对最小为多少。

#### 解题思路

这题解题关键在于发现一个很牛逼的性质：
> 对于 $|a_i|< |a_j|$ 这种情况，如果 $a_j < 0$ 则必有 $a_j < a_i$。
>
> 同理如果 $a_j > 0$ 则必有 $a_j > a_i$。

换言之，如果 $a_i < a_j$，这个逆序对能否能形成只取决于 $a_j$ 的符号，与 $a_i$ 的符号无关。

有了这个性质我们就随便做了，我们直接按绝对值从大到小考虑每个数，计算这个数和比它小的数最少能产生多少逆序对。贪心选择即可，如果当前数符号为负就会和左边所有绝对值小于当前数的数构成逆序对，否则就会与右边所有绝对值小于当前数的数构成逆序对，取较小那个即可。

然后就做完了？并不，虽然这样可以 AC，但是你有没有想过对于一对 $(i, j)$ 满足 $|a_i| = |a_j|$，它们之间的贡献如何讨论？

一个最直接的做法是把刚刚的贪心做法改成 DP，从大到小考虑每个数，把它出现的位置都拿出来然后 DP。

事实上并不需要那么麻烦，你可以发现另一个性质，如果按照之前的贪心做法做，对于 $|a_i| = |a_j|$ 的情况，一定是左边一些符号为负，右边一些符号为正，这样它们之间显然是不会产生逆序对的。

因此，我们就可以说贪心就是此题正解（~~当然你要写 DP 也没问题~~）

#### 参考代码
```cpp
#include <cctype>
#include <cstdio>
#include <algorithm>

struct FSI
{
	template<typename T>
	FSI& operator>>(T &res)
	{
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
		res = res * f; return *this;
	}
} read;

using i64 = long long;
const int N = 1e6 + 10;
inline int lowbit(int x) { return x & -x; }

template<int SIZE>
struct BIT
{
	int tr[SIZE];

	void add(int x, int val)
	{
		x += 2;
		for (int i = x; i < SIZE; i += lowbit(i))
			tr[i] += val;
	}
	int query(int x)
	{
		x += 2;
		int res = 0;
		for (int i = x; i; i -= lowbit(i))
			res += tr[i];
		return res;
	}
};
BIT<(int)1e5 + 10> bit1, bit2;
int n, val[N], ans[N];

int main(void)
{
	read >> n;
	for (int i = 1; i <= n; ++i) {
		read >> val[i];
		val[i] = std::abs(val[i]);
	}
	for (int i = 1; i <= n; ++i) {
		ans[i] = bit1.query(val[i] - 1);
		bit1.add(val[i], 1);
	}
	i64 res = 0;
	for (int i = n; i >= 1; --i) {
		res += std::min(ans[i], bit2.query(val[i] - 1));
		bit2.add(val[i], 1);
	}
	printf("%lld\n", res);
	return 0;
}
```

---

## 作者：badFlamesへ (赞：5)

提供一个另类的解法。（虽然有复杂度更优的解法但是还是提供一个思路吧）
# CF351E $\textsf{Jeff and permutation}$
拿到这题的你，在贪心和 dp 之间徘徊许久，发现一个都不会！怎么办？

然后你的思绪开始漫无目的地飘荡，直到你突然注意到**对于一个数来说，只有正和负两种选择**！

$n = 2000$？

嘶—— 网络流？最小割？

交了一发，神奇地过了。

我们尝试给他套上集合划分的板子。首先考虑 $n$ 个点代表 $n$ 个元素，然后将每个点分别向源点和汇点连权为 $0$ 的边表示决策（和源点连通表示取正，和汇点连通表示取负，当然容量为 $0$ 的边在最大流中实际上没有意义）考虑**两个元素** $a_i$ 和 $a_j$ 的决策（$i < j$），分三种情况讨论：
- $|a_i| > |a_j|$：如果 $a_i$ 取正（源点到 $i$ 的边不割），那么无论如何都会产生 $(i, j)$ 的逆序对，对应将点 $i$ 到汇点连一条权为 $1$ 的边。
- $|a_i| < |a_j|$：如果 $a_j$ 取负（ $j$ 到汇点的边不割），那么无论如何都会产生 $(i, j)$ 的逆序对，对应将点 $j$ 到源点连一条权为 $1$ 的边。
- $|a_i| = |a_j|$：如果 $a_i$ 取正并且 $a_j$ 取负，那么就会产生 $(i, j)$ 的逆序对，对应的在图中连一条 $i\to j$ 权为 $1$ 的边。

建完图直接最小割就完事了。

复杂度就不分析了，反正对于 $n = 2000$ 能过（理论上最劣还是 $\mathcal O(n^2)$ 条边，感觉能被卡掉/kk）。

代码难度很低。
```cpp
#include <bits/stdc++.h>
#define File(x, y) freopen(#x, "r", stdin), freopen(#y, "w", stdout)
#define ffile(x) File(x##.in, x##.out)
#define emp emplace_back
#define fi first
#define se second
#define wllyyds
using namespace std;
using LL = long long;

wllyyds
wllyyds
wllyyds
wllyyds
wllyyds
wllyyds
wllyyds
wllyyds
wllyyds
wllyyds

mt19937 gen(chrono::system_clock::now().time_since_epoch().count());

template <typename T = int> inline T read() {
    T x = T(); int w = 0, ch = getchar();
    for(; !isdigit(ch); ch = getchar()) w |= ch == 45;
    for(; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
    return w ? -x : x;
}
inline void fin() {}
template <typename T, typename ...A> inline void fin(T &x, A &...k) { x = read<T>(), fin(k...); }

template <ostream &C> class DEBUG {
    public: inline void write() {}
    template <typename T> inline void writeln(T x) { C << x << endl; }
    template <typename T, typename ...A> inline void write(T x, A ...k) { C << x, write(k...); }
    template <typename T, typename ...A> inline void writeln(T x, A ...k) { C << x << ' ', writeln(k...); }
    template <typename T> inline void debug(const T *arr, int l, int r) { 
        for(int i = l; i <= r; ++i) C << arr[i] << ' ';
        C << endl;
    }
};

const int N = 2e3 + 5, M = 4.2e6 + 5, inf = 1e9;

namespace FLOW { // This is the template of MaxFlow
    int head[N], to[M], nxt[M], dep[N], tot = 1;
    int val[M];
    int s, t;
    inline void _adde(int x, int y, int w) {
        to[++tot] = y, val[tot] = w, nxt[tot] = head[x], head[x] = tot;
    }
    inline void adde(int x, int y, int w) {
        _adde(x, y, w), _adde(y, x, 0);
    }
    inline bool bfs() {
        memset(dep, 0, sizeof dep);
        queue <int> Q; Q.push(s), dep[s] = 1;
        while(Q.size()) {
            int x = Q.front(); Q.pop();
            for(int i = head[x], v = to[i]; i; v = to[i = nxt[i]]) 
                if(!dep[v] && val[i]) dep[v] = dep[x] + 1, Q.push(v);
        }
        return dep[t] != 0;
    }
    int dfs(int u, int in) {
        if(u == t) return in;
        int out = 0;
        for(int i = head[u], v = to[i]; i && in; v = to[i = nxt[i]]) {
            if(dep[v] == dep[u] + 1 && val[i]) {
                LL res = dfs(v, min(in, val[i]));
                val[i] -= res, val[i ^ 1] += res;
                in -= res, out += res;
            }
        }
        if(!out) dep[u] = 0;
        return out;
    }
    inline int Dinic() {
        int res = 0;
        while(bfs()) res += dfs(s, +inf);
        return res;
    }
} using namespace FLOW;

int n, a[N];
int c1[N], c2[N];

signed main() {
#ifndef ONLINE_JUDGE
    File(in.txt, Ans.txt);
#endif
    n = read();
    for(int i = 1; i <= n; ++i) a[i] = abs(read());
    s = 0, t = n + 1;
    for(int i = 1; i <= n; ++i) 
        for(int j = i + 1; j <= n; ++j) {
        // 按照上述的建法肯定会产生一堆重边，所以可以用c1, c2就是记录每个点到源点、汇点建了几条边。
        // 这样这一部分建的边就是 O(n) 的。
            if(a[i] > a[j]) ++c2[i];
            if(a[i] < a[j]) ++c1[j];
            if(a[i] == a[j]) adde(i, j, 1);
        }
    for(int i = 1; i <= n; ++i) adde(s, i, c1[i]), adde(i, t, c2[i]);
    return cout << Dinic(), 0; // Dinic 好像没写当前弧优化，不要学我。
}
/*
ALL MY LIFE I'VE BEEN CHASING DOWN A DREAM
BUT ALL THE MOMENTS IN BETWEEN THAT IS ALL I NEED
*/
```


---

## 作者：ViXpop (赞：3)

### 这题其实就是一个贪心题

其实刚开始本蒟蒻是没什么思路的，只是在想如果一个数后面有一个比它小的数字且它本身是个正数，那么可以把这个数改变正负达到减少逆序对的目的

但是对于负数显然这样是无法进行改变的

听了学长的解释，本蒟蒻貌似懂了一点

### 我们首先考虑如果改变一个数的正负性，逆序对个数会怎样变化

我们默认ｉ>ｊ

如果abs(a[i])<=abs(a[j])时，改变a[i]的正负性对答案没有任何影响

但是如果反之，即abs(a[i])>abs(a[j])，如果a[i]是正数，那么a[i]恒大于a[j]，反之则恒小于a[j]

所以我们要对于每一个a[i]求出前后有多少个数字满足修改的条件

所以就选择暴力做法了，也可以用树状数组将复杂度降到O(nlogn)

但是蒟蒻太垃圾了，就只会用暴力做一下了

## 下面就是本蒟蒻丑陋的代码

```
#include <bits/stdc++.h>

using namespace std;

const int N=5555555;
int read(){
    int res=0,kkk=1;char ch=' ';
    while(ch<'0'||ch>'9'){
        ch=getchar();
        if(ch=='-')kkk=-1;
    }
    while(ch>='0'&&ch<='9'){
        res=res*10+ch-'0';
        ch=getchar();
    }
    return res*kkk;
}
int n,a[N],ans,l,r;
int main()
{
    n=read();
    for(register int i=1;i<=n;i++)
        a[i]=read();
    for(register int i=1;i<=n;i++){
        l=0,r=0;
        for(register int j=1;j<=n;j++)
        {
            if(j==i)continue;
            if(abs(a[j])<abs(a[i]))
            {
                if(j<i)l++;
                else if(j>i)r++;
            }
        }
        ans+=min(l,r);
    }
    printf("%d\n",ans);
    return 0;
}

```
大概就是这样了

---

## 作者：yanwh1 (赞：2)

# 题目大意：
~~看不懂题目题意翻译的可以左转去学一下语文。~~
# 大致思路：
我们枚举两个数 $i,j(1\le i<j\le n)$，可以发现，当 $|a_i| < |a_j|$ 时，当 $a_j$ 为负数时两数则必有一个逆序对，当 $a_j$ 为正数时两数则无逆序对。相反，当 $|a_i| > |a_j|$ 时，当 $a_i$ 为正数时两数则必有一个逆序对，当 $a_i$ 为负数时两数则无逆序对。当 $a_i = a_j$ 时，因为我们要求逆序对最小个数，并且我们只要使两数同号便不会有逆序对。于是相等情况下对答案贡献为零。

我们就能发现：现在可以贪心了！我们可以 $O(n^2)$ 处理上述的判断，然后 $O(n)$ 贪心，便做完了！
# 代码实现：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define rint register int
inline int read(){
    int f=0,t=0;
    char c=getchar();
    while(!isdigit(c)) t|=(c=='-'),c=getchar();
    while(isdigit(c)) f=(f<<3)+(f<<1)+c-48,c=getchar();
    return t?-f:f;
}
inline void write(int x) {
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar('0'+x%10);
}const int N=1e6+5;
int s[N],f[N][2];
signed main(){
	int n=read();
	for(rint i=1;i<=n;i++)s[i]=abs(read());
	for(rint i=1;i<n;i++){
		for(rint j=i+1;j<=n;j++){
			if(s[i]>s[j])f[i][1]++;
			if(s[i]<s[j]) f[j][0]++;
		}
	}int ans=0;
	for(rint i=1;i<=n;i++)ans+=min(f[i][0],f[i][1]);
	write(ans);
	return 0;
}
```
# 优化思路
上面的 $O(n^2)$ 判断其实可以用树状数组做到 $O(n\log n)$。具体详解看代码吧！
# 优化代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define rint register int
inline int read(){
    int f=0,t=0;
    char c=getchar();
    while(!isdigit(c)) t|=(c=='-'),c=getchar();
    while(isdigit(c)) f=(f<<3)+(f<<1)+c-48,c=getchar();
    return t?-f:f;
}
inline void write(int x) {
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar('0'+x%10);
}
//快读快写 
int s[2005],f[2005][2],tr[2005],n;
// f[n][0/1]用来记录当前位置为正或负所带来的贡献，tr[n]是树状数组 
inline void update(int p){for(;p<=n;p+=p&-p)tr[p]++;}
inline int query(int p){
	int sm=0;
	for(;p;p-=p&-p)sm+=tr[p];
	return sm;
}
//树状数组板子 
signed main(){
	n=read();
	for(rint i=1;i<=n;i++)s[i]=abs(read())+1;
	for(rint i=1;i<=n;i++){
		update(s[i]);
		f[i][0]+=query(s[i]-1);
		//这里是第一种判断 ，如果s[i]>s[j](i>j)则当s[i]<0时会产生贡献
	}memset(tr,0,sizeof(tr));
	for(rint i=n;i>=1;i--){
		update(s[i]);
		f[i][1]+=query(s[i]-1);
		//这里是第二种判断 ，如果s[i]>s[j](i<j)则当s[i]>0时会产生贡献
	}int ans=0;
	for(rint i=1;i<=n;i++)ans+=min(f[i][0],f[i][1]);
	//贪心统计答案 
	write(ans);
	return 0;
}
```

---

## 作者：封禁用户 (赞：2)

### 题面
给出数组 $a$，你可以改变每个数的正负，求逆序对数最少是多少。

### 思路
因为我们不关心改变正负的次数，于是无视他最开始的正负情况。

发现每个数的贡献可以拆开，记录 $f_{i,0/1}$ 表示 $i$ 正或负的前面有多少个比他大的数。为什么贡献不随前面正负情况改变，是因为若他前面有一个数 $j$，$|a_j|<|a_i|$ 我们把 $j$ 变为负数，则 $-|a_j|<|a_i|$ 不变，不对后面的数造成影响。然后又考虑我们把 $i$ 变为负数则有 $|a_j|>-|a_i|$，这样 $f_{i,0}$ 实际上大了 1，$f_{j,1}$ 小了 1，总和还是不变。

然后正负没有对后续的影响就可以直接贪心，每个数取正和负的最小值，用树状数组维护一下逆序对（话说 $n$ 咋这么小，$O(n^2)$ 都可以过了），再用了个可有可无的离散化（其实 $|a_i|$ 还可以再大一点），时间复杂度 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
#define Maxn 1000006 
using namespace std;
int tr[Maxn],n,m;
void add(int x,int value) {for(;x<=m;x+=x&-x)tr[x] += value;}
int ask(int x) {int ans = 0;for(;x>0;x-=x&-x)ans += tr[x];return ans;}
int s[Maxn],a[Maxn],f[Maxn][2];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++) {
		cin>>a[i]; a[i] = abs(a[i])+1;
		s[i] = a[i];
	} sort(s+1,s+1+n);
	m = 0; s[0] = -1;
	for(int i=1;i<=n;i++)
		if(s[i] != s[i-1])
			s[++m] = s[i];
	for(int i=1;i<=n;i++)a[i] = lower_bound(s+1,s+1+m,a[i])-s;
	for(int i=1;i<=n;i++)
		f[i][0] += ask(a[i]-1),add(a[i],1);
	memset(tr,0,sizeof(tr));
	for(int i=n;i>0;i--)
		f[i][1] += ask(a[i]-1),add(a[i],1);
	int ans = 0;
	for(int i=1;i<=n;i++)ans += min(f[i][0],f[i][1]);
	cout<<ans;
	return 0;
}
```

---

## 作者：Register_int (赞：1)

非常妙的一道题。

首先考虑一个数 $a_i$ 取正负时会对逆序对造成什么贡献。相等的情况只要同正负就可以避免贡献，其余分前后考虑：

- - -

- $1\le j<i$

这个时候，当 $|a_j|<|a_i|$ 时，只要 $a_i$ 取负就一定会出现逆序对，取正就一定不会出现逆序对，原因显然。当 $|a_j|\ge |a_i|$ 时情况会被 $a_j$ 统计，具体见下一条。

 - $i<j\le n$
 
当 $|a_j|<|a_i|$ 时，一样逆序对是否产生贡献由 $a_i$ 的正负决定。而 $|a_j|\ge|a_i|$ 的情况会被上一条统计。

- - -

这个时候可以发现一个神奇的性质：前后贡献只跟 $a_i$ 正负有关。换句话说：可以直接贪心！统计个数取最小值即可，复杂度 $O(n\log n)$。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 2e3 + 10;
const int MAXM = 1e5 + 10;

int c[MAXM];

inline 
int lowbit(int k) {
	return k & -k;
}

inline 
void add(int k) {
	for (int i = k; i < MAXM; i += lowbit(i)) c[i]++;
}

inline 
void del(int k) {
	for (int i = k; i < MAXM; i += lowbit(i)) c[i]--;
}

inline 
int query(int k) {
	int res = 0;
	for (int i = k; i; i -= lowbit(i)) res += c[i];
	return res;
}

int n, a[MAXN], x[MAXN];

ll ans;

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]), a[i] = abs(a[i]);
	for (int i = 1; i <= n; i++) x[i] = query(a[i]), add(a[i] + 1);
	for (int i = 1; i <= n; i++) del(a[i] + 1);
	for (int i = n; i; i--) ans += min(x[i], query(a[i])), add(a[i] + 1);
	printf("%lld", ans);
}
```

---

## 作者：Piwry (赞：1)

## 解析

（话说这里的逆序对是严格大于...~~好像都是严格大于？~~）

首先考虑单个元素的正负性（假设其他元素都是最优）对答案的影响：

可以发现，它只能决定所有**绝对值小于它**的元素之间的贡献，且**完全**无法决定**绝对值大于它**的元素之间的贡献。

可以先设想只有两个不相同元素的情况。设 $a,b$, 并保证 $|a|>|b|$，$a$ 在 $b$ 左侧。

1. 若设 $a$ 为正，$b$ 为正，此时有逆序对
2. 若设 $a$ 为正，$b$ 为负，此时有逆序对
3. 若设 $a$ 为负，$b$ 为正，此时无逆序对
4. 若设 $a$ 为负，$b$ 为负，此时无逆序对

![0](https://cdn.luogu.com.cn/upload/image_hosting/139wky7e.png)

于是，对于每个元素，我们只需求出它左右绝对值比它小的元素个数：如果该元素取正，它会和右边那些元素形成逆序对；否则它会和左边那些元素形成逆序对。

具体地，只需将求和每个元素的 $\text{min(左边绝对值比该元素小的元素数, 右边绝对值比该元素小的元素数)}$ 即可。

---

另外，至于如何查询某元素左右绝对值小于它的元素数，我们可以**从绝对值大到小**枚举元素，每次查询完前从区间中**删去**这个元素。

注意对于绝对值相同的元素，要先将它们全部删去，然后再一个个按**元素位置**查询。

## CODE

（线段树存的是区间有多少个元素（和值没啥关系））

~~（怎么感觉上面那句是废话...）~~

```cpp
#include <cstdio>
#include <algorithm>
using std::sort;
using std::min;

const int MAXN =1e6+50;

int sum[MAXN<<1], N =1;
struct in{
	int val, id;
}a[MAXN];

int cmp(in x, in y){
	if(x.val == y.val) return x.id < y.id;
	return x.val > y.val;
}

inline void pushup(int s){ sum[s] =sum[s<<1]+sum[(s<<1)|1]; }

void modify(int x, int s =1, int nl =1, int nr =N){/*删去某个元素*/
	if(nl == nr) return (void)--sum[s];
	int mid =(nl+nr)>>1;
	if(x <= mid) modify(x, s<<1, nl, mid);
	else modify(x, (s<<1)|1, mid+1, nr);
	pushup(s);
}

int query(int l, int r, int s =1, int nl =1, int nr =N){
	if(r < l) return 0;
	if(l == nl && r == nr) return sum[s];
	int mid =(nl+nr)>>1;
	if(r <= mid) return query(l, r, s<<1, nl, mid);
	else if(l > mid) return query(l, r, (s<<1)|1, mid+1, nr);
	else return query(l, mid, s<<1, nl, mid)+query(mid+1, r, (s<<1)|1, mid+1, nr);
}

inline int read(){/*反正是取绝对值判断，可以取反符号，就干脆不管原来符号了*/
	int x =0; char c =getchar();
	while(c < '0' || c > '9') c =getchar();
	while(c >= '0' && c <= '9') x =(x<<1)+(x<<3)+(c^48), c =getchar();
	return x;
}

in stk[MAXN];
int tot;

int main(){
	int n =read();
	while(N < n) N <<=1;
	for(int i =1; i <= n; ++i) a[i].val =read(), a[i].id =i;
	for(int i =N-1+n; i >= N; --i) sum[i] =1;
	for(int i =N-1; i > 0; --i) sum[i] =sum[i<<1]+sum[(i<<1)|1];
	sort(a+1, a+1+n, cmp);
	long long ans =0;
	for(int i =1; i <= n; ++i){
		tot =0;
		while(a[i+1].val == a[i].val && i < n) modify(a[i].id), stk[tot++] =a[i], ++i;/*压入栈*/
		modify(a[i].id), stk[tot++] =a[i];
		while(tot){
			in na =stk[--tot];
			int l =query(1, na.id), r =query(na.id+1, n);
			ans +=min(l, r);
		}
	}
	printf("%lld", ans);
}
```


---

## 作者：Zechariah (赞：1)

一个可以过$n\le10^6$的题解（大概）  
考虑每个位置，改变其符号会产生怎样的影响  
不难发现，只有当$|a_j|<|a_i|$，$a_i$符号改变才会使逆序对数量变化，于是我们可以用树状数组求出$a_i$的两边分别有多少数的绝对值小于$|a_i|$，两个值中取$min$，加起来就是答案
```cpp
#include <bits/stdc++.h>
#define lowbit(x) (x&-x)
#define jh(x, y) x^=y^=x^=y
#define rg register
#define inl inline
typedef long long ll;
const int N = 1e5 + 5, mod = 1e9 + 7, INF = 0x3f3f3f3f;
using namespace std;
namespace fast_IO {
	inl ll read() {
		rg char c;
		rg ll x = 0;
		rg bool flag = false;
		while ((c = getchar()) == ' ' || c == '\n' || c == '\r');
		if (c == EOF)return c; if (c == '-')flag = true; else x = c ^ 48;
		while ((c = getchar()) != ' ' && c != '\n' && c != '\r'&&~c)
			x = (x << 1) + (x << 3) + (c ^ 48);
		if (flag)return -x; return x;
	}
	inl ll max(rg ll a, rg ll b) { if (a > b)return a; return b; }
	inl ll min(rg ll a, rg ll b) { if (a < b)return a; return b; }
	void write(rg ll x) { if (x < 0)putchar('-'), x = -x; if (x >= 10)write(x / 10); putchar(x % 10 ^ 48); }
}
int a[N], Hash[N], c[N], sum1[N], sum2[N];
inl void update(rg int x, rg int data) { for (; x<=*Hash; x += lowbit(x))c[x] += data; }
inl int query(rg int x) { rg int ans = 0; for (; x; x -= lowbit(x))ans += c[x]; return ans; }

int main(void)
{
	rg int n = fast_IO::read();
	for (rg int i = 1; i <= n; ++i)a[i] = Hash[i] = abs(fast_IO::read());
	sort(Hash + 1, Hash + n + 1);
	*Hash = unique(Hash + 1, Hash + n + 1) - Hash - 1;
	for (rg int i = 1; i <= n; ++i)a[i] = lower_bound(Hash + 1, Hash + *Hash + 1, a[i]) - Hash;
	for (rg int i = 1; i <= n; ++i)sum1[i] = query(a[i] - 1), update(a[i], 1);
	memset(c, 0, sizeof(c));
	for (rg int i = n; i; --i)sum2[i] = query(a[i] - 1), update(a[i], 1);
	rg int ans = 0;
	for (rg int i = 1; i <= n; ++i)ans += fast_IO::min(sum1[i], sum2[i]);
	fast_IO::write(ans);
	return 0;
}
```


---

## 作者：AFO_Lzx (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF351E)

### $\texttt{Description}$

给定一个数组 $a$，对于数组 $a$ 中每一个 $a_i$ 可以为 $a_i$ 或者是 $-a_i$，求最少的逆序对数量。

### $\texttt{Solution}$

#### 前置知识：逆序对的定义

假设有一个数组 $a=\{2,1,3\}$，那么 $\{2,1\}$ 就是一个逆序对，因为它们在数组中的顺序与它们本身的大小关系不同。

#### 题目分析

算法标签：贪心、模拟。

首先我们知道，每一个 $a_i$ 的正负是不影响答案的，因为我们可以把 $a_i$ 进行操作，变为 $-a_i$ 也就是原数字。所以，我们可以让每一个 $a_i=\vert a_i \vert$。

我们有两个下标 $i,j$，满足 $1 \le i < j \le n$，也就是 $i$ 在 $j$ 的左侧。那么我们需要分类讨论：

- 若 $a_i>a_j$，那么只有 $a_i=a_i,a_j=-a_j$ 或者 $a_i=a_i,a_j=a_j$ 才能够制造出逆序对。
- 若 $a_i<a_j$，就只能 $a_i=-a_i,a_j=-a_j$ 或者 $a_i=-a_i,a_j=-a_j$ 才能够制造出逆序对。
- 最后就是 $a_i=a_j$，那么就只有 $a_j=-a_j$ 才行。

所以我们只需要循环 $n$ 次，每次把答案加上区间 $[1,i-1]$ 内满足 $a_j<a_i$ 的个数和区间 $[i+1,n]$ 内满足 $a_j<a_i$ 的个数的最小值即可。

 时间复杂度为 $O(n^2)$，由于 $n \le 2 \times 10^3$，所以轻松能过。

### $\texttt{Code}$

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N = 2e3 + 5;
int n, a[N], ans;

signed main() {
	cin >> n;
	
	for (int i = 1; i <= n; i++) {
		int x; cin >> x;
		a[i] = abs(x); // 存入绝对值
	}
	
	for (int i = 1; i <= n; i++) {
		int cnt1 = 0, cnt2 = 0;
		for (int j = 1; j < i; j++) cnt1 += (a[j] < a[i]); // 前面的区间
		for (int j = i + 1; j <= n; j++) cnt2 += (a[j] < a[i]); // 后面的区间
		ans += min(cnt1, cnt2); // 取最小值加进答案
	}
	
	cout << ans << endl;
	return 0;
}
```

---

## 作者：Lavaloon (赞：0)

## $\text{Analysis}$

首先观察到 $a_i$ 的正负性并不影响最终的答案，因此将序列的每个元素取绝对值，令 $a_i:=|a_i|$，即**下文的所有 $a_i$ 即为 $|a_i|$。**

对于所有下标点对 $i<j$，我们考察 $(i,j)$ 对答案造成贡献的充分必要条件：

- $a_i>a_j$，造成贡献的充分必要条件为 **$a_i$ 不取相反数**
- $a_i<a_j$，造成贡献的充分必要条件为 **$a_j$ 取相反数**
- $a_i=a_j$，造成贡献的充分必要条件为 **$a_i$ 不取相反数，且 $a_j$ 取相反数**

---

实际上前两种情况的 $i,j$ 具有**高度的独立性**，因为其**只依赖 $i,j$ 一边**。

**那不妨考虑一个子问题：不存在两数相等的情况。**

在此情况下，假如每个数取不取相反数已经被确定，那么可以设计如下算法来统计这一组方案的逆序对数（称之为总贡献）：

- 在每个下标 $i$ 处，统计其**后面**所有下标 $j$，满足 $a_j<a_i$ 的点对的总贡献——这只与 $a_i$ 是否取相反数有关：若**取**相反数，则贡献为 $0$，**否则**为 $a_i$ 后面比它小的数的个数。
- 在每个下标 $i$ 处，统计其**前面**所有下标 $j$，满足 $a_j<a_i$ 的点对的总贡献——这只与 $a_i$ 是否取相反数有关：若**不取**相反数，则贡献为 $0$，**否则**为 $a_i$ 前面比它小的数的个数。

总贡献是每一个下标的贡献之和，**而每一个下标是独立造成贡献的。**

因此可以**对每个下标取不取相反数进行讨论**，取贡献较小的那一种情况加入答案。

这可以以 $\mathcal{O}(n^2)$ 或 $\mathcal{O}(n \log n)$ 的复杂度进行求解。

---

**接下来考虑原问题：存在两数相等的情况。**

若存在点对 $(i,j)$ 且 $a_i=a_j$ 造成了贡献，那么 $a_i$ 不取相反数，且 $a_j$ 取相反数。

**假如直接套用之前的算法**，那这给出：

-  $a_i$ 后面比它小的数的个数 $\color{red}{<}$ $a_i$ 前面比它小的数的个数
- $a_j$ 后面比它小的数的个数 $\ge$ $a_j$ 前面比它小的数的个数

然而因为 $i<j$，所以有：

- $a_i$ 后面比它小的数的个数 $\ge$ $a_j$ 后面比它小的数的个数
- $a_i$ 前面比它小的数的个数 $\le$ $a_j$ 前面比它小的数的个数

**不等式组无解**。

**故在套用之前的算法的情况下，其构造出的那种方案中，点对 $(i,j)$ 必不满足造成贡献的要求，不可能造成贡献。**

当然，**这也是我们所期望的最优情况**，因为答案的下界就是“不存在两数相等的情况”时统计出的答案。

因此我们之前的算法对原问题也是成立的，使用原先算法求解即可。

## $\text{Code}$

这份代码的时间复杂度为 $\mathcal{O}(n^2)$，足以通过此题。

当然，读者可以使用树状数组优化为 $\mathcal{O}(n \log n)$。

```cpp
#include<iostream>
using namespace std;
#define int long long
const int Mx=500005,p=998244353;
int read(){
	char ch=getchar();
	int Alice=0,Aya=1;
	while(ch<'0'||ch>'9'){
		if(ch=='-') Aya=-Aya;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
		Alice=(Alice<<3)+(Alice<<1)+(ch^48),ch=getchar();
	return (Aya==1?Alice:-Alice);
}
int n,a[Mx];
signed main(){
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		if(a[i]<0) a[i]=-a[i];
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		int cnt=0,tnc=0;
		for(int j=1;j<i;j++) cnt+=(a[j]<a[i]);
		for(int j=i+1;j<=n;j++) tnc+=(a[j]<a[i]);
		ans+=min(cnt,tnc);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：xiao7_Mr_10_ (赞：0)

## 前言

题意：给定一个序列，可以做若干次操作，其中一次操作可以把一个数变成它的相反数。求修改后序列的逆序对数最少有多少个。

我考场上并没有认真看这题。

## Step1 思考

转化问题，注意到如果我们强制把序列处理为**正**是可以的，毕竟后面是可以修改的，所以把所有数取绝对值对答案并没有影响。接下来的讨论都默认已经取了绝对值。

然后考虑一个数能够产生的贡献是什么。这样做有点麻烦了，因为很难考虑后面的和前面的修改带来的影响。

换一种方向思考，先假设 $a_{i}$ 为目前序列的最大值，然后考虑其修改为正或负数的贡献。


- 当 $a_{i} > 0 $ 时，其贡献为它后面比它小的总数，因为逆序对是**严格大于**的，所以后面和他相等的数不能计入答案。

- 当 $a_{i} \le 0$ 时，其贡献为它前面比他大的总数，同理可得。

所以对于 $a_{i}$，它的贡献**不受其他数的正负的影响**。


## Step 2 做法

那么我们找到对应的最大值然后计入答案即可。但是考虑到第二小或第 $n$ 小的数的贡献，我们的做法可以有丢掉这个这个最大值然后再计算。这样时间复杂度是 $O(n^2)$ 的，可以通过原题。

显然还有更优秀的做法，考虑分解问题。

注意到每次就相当于求前缀和后缀，也就是统计 $1$ 到 $i-1$ 中比 $a_{i}$ 小的，在 $i+1$ 到 $n$ 中有多少比 $a_{i}$ 小的。

实际上这个问题就是一个简单的**求逆序对问题**的拓展，不过就是还需要反着做一遍而已。

预处理即可，设 $1$ 到 $i-1$ 中比 $a_{i}$ 小的数的个数为 $l_{i}$，$i+1$ 到 $n$ 中比 $a_{i}$ 小的数为 $r_{i}$。

那么答案就是 $\sum _{i=1} ^ n \min(l_{i},r_{i})$。

## Step 3 代码

实现时可以离散化一下，然后挂个树状数组即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+5;
int l[N],c[N*2],n,a[N],b[N*2],ans,len,cnt,r[N];
void insert(int x,int y){
	for(;x<=cnt;x+=x&(-x))c[x]+=y;
} 
int query(int x){
	int ans=0;
	for(;x;x-=x&(-x))ans+=c[x];
	return ans;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for(int i = 1;i <= n;i++){
		cin >> a[i];
		a[i]=abs(a[i]);
		b[++len]=a[i];
	}
	sort(b+1,b+1+len);
	cnt=unique(b+1,b+1+len)-b-1;
	for(int i = 1;i <= n;i++)a[i]=lower_bound(b+1,b+1+cnt,a[i])-b;
	for(int i = 1;i <= n;i++){
		l[i]=query(a[i]-1);
		insert(a[i],1);
	}
	memset(c,0,sizeof(c));
	for(int i = n;i >= 1;i--){
		r[i]=query(a[i]-1);
		insert(a[i],1);
	}
	for(int i = 1;i <= n;i++)ans+=min(l[i],r[i]);
	cout << ans;
	return 0;
} 
```

---

