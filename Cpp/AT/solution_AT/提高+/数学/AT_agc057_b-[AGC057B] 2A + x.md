# [AGC057B] 2A + x

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc057/tasks/agc057_b

正整数列 $ A\ =\ (A_1,\ A_2,\ \ldots,\ A_N) $ および正整数 $ X $ が与えられます。あなたはこの数列に対して、次の操作を何度でも行うことができます（$ 0 $ 回でもよい）：

- 添字 $ i $ （$ 1\leq\ i\leq\ N $）および、$ 0\leq\ x\leq\ X $ となる非負整数 $ x $ を選ぶ。$ A_i $ を $ 2A_i+x $ に変更する。

操作結果の $ \max\{A_1,A_2,\ldots,A_N\}-\min\{A_1,A_2,\ldots,A_N\} $ としてありうる最小値を求めてください。

## 说明/提示

### 制約

- $ 2\leq\ N\leq\ 10^5 $
- $ 1\leq\ X\leq\ 10^9 $
- $ 1\leq\ A_i\leq\ 10^9 $

### Sample Explanation 1

$ A_i $ を $ 2A_i+x $ に変更する操作を $ (i,\ x) $ と表すことにします。最適な操作列の一例は次の通りです。 - $ (1,0) $, $ (1,1) $, $ (2,2) $, $ (3,0) $ 操作結果は $ A\ =\ (21,\ 18,\ 24,\ 20) $ となり、$ \max\{A_1,A_2,A_3,A_4\}-\min\{A_1,A_2,A_3,A_4\}\ =\ 6 $ が達成できます。

### Sample Explanation 2

最適な操作列の一例は次の通りです。 - $ (1,5) $, $ (1,5) $, $ (2,5) $, $ (2,1) $, $ (3,2) $, $ (3,3) $, $ (4,0) $, $ (4,3) $ 操作結果は $ A\ =\ (111,111,111,111) $ となり、$ \max\{A_1,A_2,A_3,A_4\}-\min\{A_1,A_2,A_3,A_4\}\ =\ 0 $ が達成できます。

### Sample Explanation 3

一度も操作を行わないことにより、$ \max\{A_1,A_2,A_3,A_4\}-\min\{A_1,A_2,A_3,A_4\}\ =\ 3 $ が達成できます。

## 样例 #1

### 输入

```
4 2
5 8 12 20```

### 输出

```
6```

## 样例 #2

### 输入

```
4 5
24 25 26 27```

### 输出

```
0```

## 样例 #3

### 输入

```
4 1
24 25 26 27```

### 输出

```
3```

## 样例 #4

### 输入

```
10 5
39 23 3 7 16 19 40 16 33 6```

### 输出

```
13```

# 题解

## 作者：tis00 (赞：4)

怎么全是 $O(n\log n\log A)$ 的？只好由本蒟蒻献上一 $O(n(\log n+\log A))$ 的做法了。

首先，把 $A_i$ 操作 $k$ 次后，令 $L_i$ 为 $A_i$ 的最小可能值，$R_i$ 为 $A_i$ 的最大可能值，则一定有 $L_i=2^kA_i，R_i=L_i+(2^k-1)x$。

最终答案即为 $\max\{\max\{L_i\}-\min\{R_i\},0\}$。

令 $s=\max\{A_i\}-\min\{A_i\}$，则如果把每个 $A_i$ 都最优地操作了一次，那么 $s\leftarrow \max\{2s-v,0\}$。

如果 $s<v$，那么经过若干次操作后一定有 $s=0$。

如果 $s\ge v$，那么操作不优。

现在考虑至少一个 $A_k$ 不操作的情形。

容易发现，这个 $A_k$ 一定是 $\max\{A_i\}$。

于是先把其他 $A_i$ 向 $A_k$ 靠拢，即不断操作，直到 $2L_i>A_k$。

此时的 $\max\{\max\{L_i\}-\min\{R_i\},0\}<A_k$。

有一种贪心策略：把 $R_i$ 最小的取出，并做一次操作。

如果不操作它，那么 $\min\{R_i\}$ 一定不增，$\max\{L_i\}$ 也一定不降，故一定不优。

又因为操作满足交换律，故操作它是全局最优。

重复这种贪心策略 $n$ 次即可。

第 $n+1$ 次时，根据鸽巢原理，一定有数被操作两次及以上，而 $2L_i>A_k$，故 $4L_i-A_k>A_k>\max\{\max\{L_i\}-\min\{R_i\},0\}$，一定不优。

如果 $s<x$，那么输出 $0$，否则输出 $s$。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5;
const int INF=2e18;
int n,x,a[N]; 
struct Node{
	int l,r;
	Node(){}
	Node(int l,int r):l(l),r(r){}
	bool friend operator<(const Node A,const Node B){
		return A.r>B.r;
	}
} A[N];
priority_queue<Node> Q;
signed main(){
	scanf("%lld%lld",&n,&x);
	int mx=0,mn,ans;
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]),A[i]=Node(a[i],a[i]),mx=max(mx,a[i]);
	for(int i=1;i<=n;i++) while(A[i].l*2<=mx) A[i].l*=2,A[i].r=A[i].r*2+x;
	for(int i=1;i<=n;i++) Q.push(A[i]);
	mn=INF,mx=0;
	for(int i=1;i<=n;i++) mx=max(mx,A[i].l),mn=min(mn,A[i].r);
	ans=mx-mn;
	for(int i=1;i<=n;i++){
		Node t=Q.top();Q.pop();
		if(t.r>=INF) break;
		t.l*=2,t.r=t.r*2+x;Q.push(t);
		ans=min(ans,(mx=max(mx,t.l))-Q.top().r); 
	}
	printf("%lld",ans<x?0:ans);
	return 0;
}
```

运行时长仅 $26ms$。

---

## 作者：hj23308 (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/AT_agc057_b)

### $\mathcal{Description}$

给定一个长度为 $ n $ 的正整数序列 $ A $，你可以进行若干次操作，使得 $ \max \{ A_1, A_2, \ldots  A_n \} - \min \{ A_1, A_2, \ldots  A_n \} $ 最小。

每次操作选择两个整数 $ i $ 和 $ v \left( 0 \le v \le x \right) $，$ A_i \gets 2A_i + v $。

### $\mathcal{Solution}$

对于一个 $ A_i $，在其上进行 $ k $ 次操作后，结果一定在区间一个区间 $ \left[ L_i, R_i \right] $ 内，且可以取到区间内每一个整数。其中  $ L_i = 2^k A_i, R_i = L_i + \left( 2^k - 1 \right) x $。

我们可以对于每个 $ A_i $ 分配一定数量的操作（不关注每次操作具体的 $ v $），答案即为 $ \max(0, \max\{ L_i \} - \min\{ R_i \}) $。

不难发现，在一次操作后 $ \max\{ L_i \} $ 和 $ \min\{ R_i \} $ 不降。贪心的考虑，每次对 $ R_i $ 最小的 $ i $ 进行操作，这样一定可以增加 $ \min\{ R_i \} $，如果 $ \max\{ L_i \} $ 增加也是迟早的事，显然不比选其他 $ i $ 劣。

这个最小的 $ R_i $ 可以用堆来维护，并在每次操作前更新 $ \mathrm{ans} = \min( \mathrm{ans}, \max\{ L_i \} - \min\{ R_i \} )$，在爆 `int` 或 $ \mathrm{ans} \le 0 $ 之后跳出循环，输出 $ \mathrm{ans} $ 即可 AC 此题。

时间复杂度 $ O(n \log n) $，空间复杂度 $ O(n \log n) $。

### $ \mathcal{Code} $

```c++
#include<bits/stdc++.h>
using namespace std;

struct node {
	long long l, r;
	
	node(long long l, long long r) : l(l), r(r) {};
	
	bool operator <(const node& rhs) const { return r > rhs.r; }
};

int n;
long long x, l, ans = LLONG_MAX;
priority_queue<node> q;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	cin >> n >> x;
	for (int i = 0; i < n; i++) {
		long long v;
		cin >> v, l = max(l, v);
		q.push(node(v, v));
	}
	while (ans > 0) {
		auto v = q.top();
		if (v.r >= 1e18) break;
		ans = min(ans, l - v.r), l = max(l, v.l * 2);
		q.pop(), q.emplace(v.l * 2, v.r * 2 + x);
	}
	cout << max(ans, 0ll);
	
	return 0;
}
```

---

## 作者：喵仔牛奶 (赞：3)

题解好像没有怎么说明为什么操作到 $10^{18}$ 后终止是对的，那我来补充一下。

# Solution

# Part I

设 $a$ 操作 $k$ 次，则最终得到的 $a'$ 可以取 $[a_i\cdot 2^k,a_i\cdot 2^k+x(2^k-1)]$ 中的任意值。容易归纳证明。

这样可以干什么呢？这样之后，我们对 $a$ 的操作就可以从「操作了什么」变为简单的「操作了几次」。

# Part II

设最大值为 $t$，我们有以下性质：
- 若 $t$ 进行操作，则其他数必定操作至少一次。

证明是容易的。操作 $t$ 后，再操作其他数不会使最大值变大，所以进行操作不会是答案变劣。

所有数至少操作一次，那就可以拆出一次全局操作。我们考虑**全体操作一次**对答案的贡献，设原来答案为 $s$，全体操作一次后答案为 $(2s-x)$，证明显然。

观察发现仅当 $s<x$ 时全体操作使答案变优，而且操作若干次后答案变为 $0$。相反地，当 $s\geq x$ 时，我们肯定不会进行全体操作，**也就是不会操作** $\boldsymbol{t}$。

得出结论：设在不操作 $t$ 的情况下得出的答案为 $s$，最终的答案是 $\begin{cases}0&s<x\\s&s\geq k\end{cases}$。

也就是说，我们只需要计算出不操作 $t$ 的情况下的答案即可。

# Part III

设 $A_i$ 操作了 $k_i$ 次，设 $L_i=A_i\cdot 2^{k_i}$，$R_i=L_i+x(2^{k_i}-1)$，显然 $A_i$ 操作后的范围是 $[L_i,R_i]$。

答案为 $\max\{\max L_i-\min R_i,0\}$，证明显然。我们每次取 $R_i$ 最小的操作，这样是最优解，这也是显然的。

拿个堆维护，当堆定是原先的最大值时结束贪心。因为 $R_i$ 每次翻倍，所以这样只会贪心 $\mathcal{O}(n\log a)$ 次。

这样就得到了不操作 $t$ 的情况下的答案，判一下是不是 $<x$ 就可以了。

时间复杂度 $\mathcal{O}(n\log n\log a)$。

代码见下文。

# Part IV

回到开头，为啥操作到 $10^{18}$ 不判断 $<x$ 也时对的呢？考虑 $s$ 与 $x$ 的差值 $\Delta=x-s$，那么 $s\gets 2s-x$ 后 $\Delta\gets x-(2s-x)=2\Delta$。

$\Delta$ 每次翻倍，再额外操作 $\log$ 次即可省去判断。每次操作 $R_i$ 翻倍，正好要操作到 $A_i^2\approx10^{18}$。

# Code

```cpp
#include <bits/stdc++.h>
#define REP(i, l, r) for (int i = (l); i <= (r); ++ i)
#define DEP(i, r, l) for (int i = (r); i >= (l); -- i)
#define fi first
#define se second
#define pb emplace_back
#define mems(x, v) memset((x), (v), sizeof(x))
using namespace std;
namespace Milkcat {
	typedef long long LL;
	typedef pair<LL, LL> pii;
	const int N = 1e6 + 5;
	LL n, k, x, mx, L, rs; priority_queue<pii, vector<pii>, greater<pii>> q;
	int main() {
		cin >> n >> k, rs = 1e18;
		REP(i, 1, n)
			cin >> x, L = max(L, x), q.emplace(x, x);
		mx = L;
		while (rs > 0) {
			LL r = q.top().fi, l = q.top().se; q.pop();
			if (r > mx) break;
			rs = min(rs, L - r), L = max(L, l * 2);
			q.emplace(r * 2 + k, l * 2);
		}
		rs = max(rs, 0LL);
		cout << (rs < k ? 0 : rs) << '\n';
		return 0;
	}
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	int T = 1;
	while (T --) Milkcat::main();
	return 0;
}
```

---

## 作者：_edge_ (赞：3)

AGC 的好题！

~~当然我是不会做的。~~

题意就是让你不停操作，操作方式题面中给出了，然后要使得 $\max-\min$ 最小。

首先，我们观察知道，$a$ 数组的每个数至多操作 $\log$ 次。

在 $\log$ 之后就会炸掉，反正炸 long long 了。

可以证明在 long long 范围内肯定能找到一组最优解，这东西我不会证 (悲。

然后我们思考，操作了 $j$ 次之后，$a_i$ 能到达的下界是 $a_i \times 2^j$，上界是 $a_i \times 2^j+2^j \times x-1$，这里面的数肯定都能到达，这东西证明不难，相当于把他展开之后会得到 $2^0 \times v + 2^1 \times v + 2^2 \times v + \cdots +2^{j-1} \times v$ 。

读者可以感性理解上面两个证明。

好，那么也就是说我们目前知道的是 $a_i$ 操作之后能到达的是一段区间，那么怎么求答案呢？

我们思考这样一个子问题，对于每一个 $a_i$ 能取的数是 $[L_i,R_i]$，怎么取才能让答案最小呢？

肯定是 $\max{L_i}-\min{R_i}$，具体的，对于每一个大于 $\min{R_i}$ 的都往左移动肯定更优。

那么现在的问题在于，他能取到的区间是不固定的，是会动态变化的。

但是不难发现，这东西的 $R$ 肯定是单调递增的，为了使得上面那个柿子变优秀，我们每次取 $R$ 最小的来操作一次即可。

具体的流程就是先把几个数放到堆里面，初始区间长度为 $1$，然后对于一个 $R$ 小的就进行操作，这东西可以用堆来快速维护。

建议反复思考这题，挺好的一道思维题。

回顾这道题，首先要发现他所能到达的是一段区间，然后利用贪心原则把 $R$ 小的都拿出来搞，这样就好了，注意维护 $L$ 的最大值。

```cpp
#include <bits/stdc++.h>
#define int long long 
using namespace std;
const int INF=1e5+5;
struct _node_queue {
	int l,r,id;
	bool operator < (const _node_queue &x) const {
		return x.r<r;
	}
};
priority_queue <_node_queue> q;
int n,k,R,A,ans;
signed main()
{
	ios::sync_with_stdio(false);
	cin>>n>>k;ans=9e18;
	for (int i=1;i<=n;i++) {
		int x=0;cin>>x;
		q.push({x,x,i});
		A=max(A,x);
	}
	while ("If the world loves me") {
		auto it=q.top();q.pop();
		if (it.r>3e18) break;
		ans=min(ans,max(0ll,A-it.r));
		A=max(A,it.l*2);
		q.push({it.l*2,it.r*2+k,it.id});
	}
	cout<<ans<<"\n";
	return 0;
}
```


---

## 作者：SMTwy (赞：1)

某个值 $a$ 进行 $k$ 次操作后，可选的值域范围，下界是 $2$ 的 $k$ 次方乘 $a$。上界是下界加上 $2$ 的 $k$ 次方乘 $X$ 减一。

先将所有值调整到与初始最大值最近的位置，注意下界不要超过初始最大值。

如果此刻这个值的下界和上界可以包含初始最大值，那这个值在此后的所有操作中完全可以等价初始最大值。

因为此刻初始最大值没有进行任何操作，它是必须要考虑的，所以必然存在，那么可以与它相等的就直接令与它相等即可。所以可以直接把这个值扔掉。当然不扔也没有关系，这不会影响最后答案。

求最小差值自然是看最小的上界和最大的下界的差值，无论在什么时候这个差值小于 $X$，就代表答案可以是 $0$。

因为两个值同时乘 $2$ 之后差值也乘 $2$，可以将较小的那个加上 $X$ 来缩小差值直到为 $0$。

在数轴表现为最小的上界在不断乘 $2$ 中会不断逼近最大的下界。

其它的所有值随着它们的变动一起乘 $2$ 即可，无论怎么变动，如果都同时乘 $2$，最小和最大一直不会变。

如果不小于，就将按照顺序尝试将每个区间连带之前的区间一起乘 $2$ 去寻找新的最大下界和最小上界比较最小。

这个枚举每个断点 $O(n)$ 跑一遍即可，再继续乘下去，差距不会缩小的依旧不会缩小。注意倒序枚举断点，这样最小上界是 $O(1)$ 继承，最大下界就是断点的下界乘 $2$。

这个思路是同机房大佬sandom给我的，说实话我认为帅炸了，这种做法正确性肯定没问题。复杂度是稳定的排序复杂度，真正求答案时只需要 $O(n)$ 扫一遍即可。

目前在这仅有的几个人的提交里，就是三十毫秒和三秒的差距。


```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mx=1e5+1000;
const ll Inf=1e17;
int n,x,a[mx];
ll po[mx],ans=Inf;
int tot=0;
struct N{
    ll data;int cnt;
}s[mx];
bool cmp1(N a,N b){
    return a.data<b.data;
}
inline void prepare(){
    int cnt=0,pos=n;
    for(int i=1;i<=n-1;++i){
        cnt=0;
        if(a[i]*2<=a[n]){
            while(a[i]*2<=a[n]){a[i]*=2;cnt++;}
            ll uo=a[i]+(po[cnt]-1)*x;
            if(a[n]>=a[i] && a[n]<=uo)continue;
            s[++tot].data=a[i];s[tot].cnt=cnt;      
        }
        else{pos=i;break;}
    }
    for(int i=pos;i<=n;++i){s[++tot].data=a[i];s[tot].cnt=0;}
}
void MYH(){
    scanf("%d%d",&n,&x);
    for(int i=1;i<=n;++i)scanf("%d",&a[i]);
    sort(a+1,a+n+1);po[0]=1;po[1]=2;
    for(int i=2;i<=30;++i){po[i]=po[i-1]*2;}
    prepare();sort(s+1,s+tot+1,cmp1);
    ll maxl=s[tot].data;ll minr=Inf;
    for(int i=1;i<=tot;++i){minr=min(minr,s[i].data+(po[s[i].cnt]-1)*x);}
    if(maxl-minr<x){printf("0\n");return ;}
    ans=min(ans,maxl-minr);
    for(int i=1;i<=tot;++i)minr=min(minr,s[i].data+(po[s[i].cnt]-1)*x);
    if(maxl*2-minr<ans){printf("0\n");return ;}
    minr=s[tot].data+(po[s[tot].cnt]-1)*x;
    for(int i=tot-1;i>=1;--i){
        minr=min(minr,s[i+1].data+(po[s[i+1].cnt]-1)*x);
        maxl=s[i].data*2;
        if(maxl-minr<x){printf("0\n");return ;}
        ans=min(ans,maxl-minr);
    }
    printf("%lld\n",ans);

}
int main(){
    // freopen("2.in","r",stdin);
    // freopen("2.out","w",stdout);
    MYH();
    return 0;
}
```



---

## 作者：AC_love (赞：0)

首先对于某个数 $A_i$，如果它操作了 $p$ 次，那么它的最小值应该是 $A_i \times 2^p$，最大值应该是 $(A_i + x) \times 2^p - x$。

不难想到，在最大值和最小值之间所有的数都能取到。

对于每个 $A_i$，我们令其操作后的最小值为 $a_i$，最大值为 $b_i$，则我们最终的结果其实是 $\max a - \min b$。

我们把所有数都扔进优先队列里按照 $b$ 从小到大排序，每次找一个最小的 $b$，操作它，扔回优先队列中。如此反复，即可得到答案。

现在问题在于：一个数被操作 $\log$ 次之后就会溢出，我们能在溢出之前找到答案吗？

可以的。考虑如果我们把整个序列都操作一次，原先的答案是 $s$，操作一次后会变成 $2s - x$。显然当且仅当 $s < x$ 时我们会执行这样一次整体操作。再操作一次会变成 $4s - 3x$，以此类推。最后一定会变成一个 $x - 2^p(x - s)$ 的形式，其中 $p$ 是操作次数。本题中 $x \le 10^9$，因此 $p \le \log_210^9$，整体操作次数不会超过 $\log$ 级别，因此不会溢出。

[code](https://atcoder.jp/contests/agc057/submissions/59719702)

---

