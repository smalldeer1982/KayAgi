# [AGC009C] Division into Two

## 题目描述

[problemUrl]: https://atcoder.jp/contests/jrex2017/tasks/agc009_c

相異なる整数 $ N $ 個からなる集合があります。この集合の $ i $ 番目に小さい要素は $ S_i $ です。この集合を $ X,Y $ の $ 2 $ つの集合に分割し、

- $ X $ に属するどの相異なる $ 2 $ つの要素も、その差の絶対値が $ A $ 以上
- $ Y $ に属するどの相異なる $ 2 $ つの要素も、その差の絶対値が $ B $ 以上

になるようにしたいです。このような分割としてありうるものの個数を $ 10^9\ +\ 7 $ で割ったあまりを求めてください。ただし、$ X,Y $ のうち一方が空となるような分割も数えます。

## 说明/提示

### 制約

- 入力はすべて整数である。
- $ 1\ ≦\ N\ ≦\ 10^5 $
- $ 1\ ≦\ A\ ,\ B\ ≦\ 10^{18} $
- $ 0\ ≦\ S_i\ ≦\ 10^{18}(1\ ≦\ i\ ≦\ N) $
- $ S_i\ <\ S_{i+1}(1\ ≦\ i\ ≦\ N\ -\ 1) $

### Sample Explanation 1

次の $ 5 $ 通りの分割方法があります。 - $ X= ${$ 1,6,9,12 $}, $ Y= ${$ 3 $} - $ X= ${$ 1,6,9 $}, $ Y= ${$ 3,12 $} - $ X= ${$ 3,6,9,12 $}, $ Y= ${$ 1 $} - $ X= ${$ 3,6,9 $}, $ Y= ${$ 1,12 $} - $ X= ${$ 3,6,12 $}, $ Y= ${$ 1,9 $}

## 样例 #1

### 输入

```
5 3 7
1
3
6
9
12```

### 输出

```
5```

## 样例 #2

### 输入

```
7 5 3
0
2
4
7
8
11
15```

### 输出

```
4```

## 样例 #3

### 输入

```
8 2 9
3
4
5
13
15
22
26
32```

### 输出

```
13```

## 样例 #4

### 输入

```
3 3 4
5
6
7```

### 输出

```
0```

# 题解

## 作者：zhylj (赞：9)

[欢迎关注我的博客](http://zhylj.cc/)

不妨设 $A\le B$。

若答案不为零，对于任意 $1\le i \le n - 2$，有 $s_{i+2} - s_i \ge A$。（相邻三个数必然有两个属于同一个集合）

设 $f(i)$ 代表前 $i$ 个数，第 $i$ 个数在 $Y$ 集合中的答案。（我们可以在数列第 $n + 1$ 个位置加上一个 $\inf$，这样答案就为 $f(n + 1)$）

有：

$$f(i) = \sum_{s_i - s_j \ge b \land (j,i)\text{这段区间可以被全部放在 X 集合中}} f(j)$$

可以用一个变量来维护 $f(j)$ 的和，若某一次 $s_i - s_{i-1} < a$，则把这个变量置零。

这样写似乎比前面的 julao 简洁一点。

```cpp
ll s[kN], f[kN];

int main() {
	int n; ll a, b, x = 0; rd(n, a, b);
	if(a > b) std::swap(a, b);
	for(int i = 1; i <= n; ++i) rd(s[i]);
	s[++n] = kInf;
	for(int i = 1; i < n - 1; ++i)
		if(s[i + 2] - s[i] < a) { printf("0\n"); return 0; }
	f[0] = 1; s[0] = -kInf;
	for(int i = 1, ptr = 0; i <= n; ++i) {
		for(; s[i] - s[ptr] >= b; ++ptr) x = (x + f[ptr]) % kMod;
		f[i] = x;
		if(s[i] - s[i - 1] < a) x = 0, ptr = i - 1;
	}
	printf("%lld", f[n]);
	return 0;
}
```



---

## 作者：chenxia25 (赞：5)

（hgs 风格小清新题解）

简单 DP 题。咋这种题都 2400 啊。。。

注意到最终 $A$ 和 $B$ 都各一定能表示成 $s$（有序）的若干个区间。

于是对这个区间 DP。

我们考虑 $dp_{i,0/1}$ 为考虑划分前 $i$ 个，第 $i$ 个分到 $A/B$ 的方案数。

然后转移的话，就 $0$ 转移到 $1$ $1$ 转移到 $0$，决策要满足两个限制：

1. 当前区间内部满足条件；
2. 区间两端要满足条件。 

然后随便推。发现 1 的决策集合是个 $[1,i]$ 的后缀，即有下界；2 是个前缀，即有上界。

综合起来就是一个区间？前缀和随便维护一下。

1 可以用分段 `for` 预处理，2 傻逼写 `lower_bound`，不傻逼发现单调性，two-pointers 随便维护。

然后做完了？

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=1000000007,inf=0x3f3f3f3f3f3f3f3f;
const int N=100000;
int n,a,b;
int s[N+1];
int Sum[N+1][2];
int dp[N+1][2];
int lft[N+1][2];
int sum(int l,int r,bool tp){
	if(l>r)return 0;
	return (Sum[r][tp]-Sum[l-1][tp])%mod;
}
signed main(){
	cin>>n>>a>>b;
	for(int i=1;i<=n;i++)scanf("%lld",s+i);
	for(int i=1,ie;i<=n;i=ie+1){
		ie=i;while(ie+1<=n&&s[ie+1]-s[ie]>=a)ie++;
		for(int j=i;j<=ie;j++)lft[j][0]=i;
	}
	for(int i=1,ie;i<=n;i=ie+1){
		ie=i;while(ie+1<=n&&s[ie+1]-s[ie]>=b)ie++;
		for(int j=i;j<=ie;j++)lft[j][1]=i;
	}
	dp[0][0]=dp[0][1]=Sum[0][0]=Sum[0][1]=1;
	int las0=0,las1=0;
	s[0]=-inf,s[n+1]=inf;
	for(int i=1;i<=n;i++){
		while(las0+1<i&&s[las0+1]<=s[i+1]-a)las0++;
		while(las1+1<i&&s[las1+1]<=s[i+1]-b)las1++;
		dp[i][0]=sum(lft[i][0]-1,las1,1);
		dp[i][1]=sum(lft[i][1]-1,las0,0);
		Sum[i][0]=(Sum[i-1][0]+dp[i][0])%mod;
		Sum[i][1]=(Sum[i-1][1]+dp[i][1])%mod;
	}
	cout<<(dp[n][0]+dp[n][1]+10*mod)%mod;
	return 0;
}
```



---

## 作者：小木虫 (赞：3)

### Preface
一道巧妙的优化 dp。  
### Problem  
给定 $n$ 个不同的整数，求将它们分成两个集合 $X,Y$，并且 $X$ 集合中任意两个数的差 $\geq A$，$Y$ 集合中任意两个数的差 $\geq B$ 的方案数。  
### Solution  
看到这题我们可以立刻胡出一个暴力的 $n^2$ dp。具体状态就是记录两个集合当前最后选择的数字是哪两个进行转移：  
```cpp
ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
cin>>n>>a>>b;for(int i=1;i<=n;i++)cin>>s[i];
dp[0][0]=1;
for(int i=0;i<=n;i++){
	for(int j=0;j<=n;j++){
		if(i<j){
			if(s[j+1]-s[j]>=b||j==0)dp[i][j+1]+=dp[i][j],dp[i][j+1]%=mod;
			if(s[j+1]-s[i]>=a||i==0)dp[j+1][j]+=dp[i][j],dp[j+1][j]%=mod;
		}else{
			if(s[i+1]-s[i]>=a||i==0)dp[i+1][j]+=dp[i][j],dp[i+1][j]%=mod;
			if(s[i+1]-s[j]>=b||j==0)dp[i][i+1]+=dp[i][j],dp[i+1][i]%=mod;
		}
	}
}
for(int i=0;i<=n;i++)ans+=dp[i][n]+dp[n][i],ans%=mod;
cout<<ans;
```
发现上面的代码实际上浪费了一些算力，因为我们只要选出一个集合另外一个集合就是其的补集，所以我们似乎可以尝试一下只选择一个集合的 dp。  

那么两个选择点之间的所有点就应该是另外一个集合的点，设我们选的集合为 $X$，补集为 $Y$。  
转移方程：  
$dp_i=\sum_{j=0}^{i-1}dp_j$  
那么 $[i+1,j-1]$ 内的任意两个数字 $x,y$ 应满足：  
$|x-y|\geq B$  
并且两个选择点 $i,j$ 应满足：  
$|s_i-s_j|\geq A$  
容易发现所有在 $i$ 上满足第一个条件的数字会形成一个 $[1,i-1]$ 的后缀，而满足第二个条件的会形成一个前缀。那么我们要转移的是它们的交。这是一个区间，我们可以边计算边搞出一个前缀和，解决 dp 数组区间加和的问题。  

搞了这么久，我们突然发现这里好像有一个 bug，如果一个 $X$ 的选择点的两边的两个属于 $Y$ 的数字的差的绝对值小于 $B$ 怎么办？这不是不合法吗？那我们的转移方程是不是错了？  
如果出现这样的情况，那么这个选择点与其两边的点两两之差全部小于 $B$，当 $B\leq A$ 时显然无解，因为无论在哪个集合它们都会发生冲突，但是要是 $A\leq B$ 怎么办？这两个集合是本质相同的啊，于是我们把大的那个叫做 $A$ 就是了。  
code：  
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e5+10;
const int mod=1e9+7;
ll dp[N];ll n,a,b,p;
ll s[N];ll sum[N];
int A[N];int B[N];ll ans;
int main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin>>n>>a>>b;for(int i=1;i<=n;i++)cin>>s[i];
	if(a<b)swap(a,b);dp[0]=1;sum[0]=1;
	for(int i=1;i<=n-2;i++)if(s[i+2]-s[i]<b){cout<<0;return 0;}
	p=0;for(int i=1;i<=n;i++){while(s[i]-s[p+1]>=a)p++;A[i]=p;}
	p=0;for(int i=1;i<=n;i++){if(i!=1&&s[i]-s[i-1]<b)p=i-1;B[i]=p;}
	for(int i=1;i<=n;i++){
		int r=A[i];int l=B[i-1];
		if(l<=r){
			if(l!=0)dp[i]+=(sum[r]-sum[l-1]+mod)%mod;
			else dp[i]+=sum[r];dp[i]%=mod;
		}
		sum[i]=sum[i-1]+dp[i];sum[i]%=mod;
	}
	for(int i=n;i>=0;i--){
		ans+=dp[i];ans%=mod;
		if(i!=n&&s[i+1]-s[i]<b)break;
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：吴思诚 (赞：2)

# [Division into Two](https://www.luogu.com.cn/problem/AT_agc009_c)

## 思路

一道 DP 好题。

我们假定 $A\ge B$（$A$ 对应 $X$ 集合，$B$ 对应 $Y$ 集合）。我们先判掉存在 $3$ 个数两两之差小于 $B$ 的情况（根据鸽巢原理，三数二集合，这三者必定有二者分在一起）。

DP 状态不难想到：令 $f_i$ 表示前 $i$ 个数都划分完成，其中第 $i$ 个数是分在 $X$ 的方案数。

首先我们需要枚举一个 $j$，那么 $[j+1,i-1]$ 这一段都放在 $Y$ 集合中。然后我们分析得到合法的 $j$ 需要满足的要求：

- $j<i$
- $s_i-s_j\ge A$（由于 $s_i$ 递增，所以满足条件的对会越来越多，所以满足此条件的 $j$ 是从**一开始的前缀**）
- 对于 $[j+1,i-1]$ 中的每一个数都满足两两之差 $\ge B$。（由于区间 $[j,i-1]$ 和 $[j+1,i-1]$，如果后者不合法则前者一定不合法，那么发现是一个 **$i-1$ 到开头的后缀**）。

那有的同学就会想，为什么新加入 $Y$ 的一段就一定合法呢？也可能不合法呀！

注意我们刚开始判断掉的情况，假设上次 $Y$ 集合中最后的数是 $a_k$，由于 $a_{j+1}-a_k<B$，又有 $a_k<a_j<a_{j+1}$，那么这三者两两作差一定 $<B$（因为最大的和最小的之差已经 $<B$，那么相邻的就一定更小），所以已经被我们判掉了，不需要担心正确性。

可转移的便是**二者的交集**。二者都可以用双指针一类的方式维护，然后作前缀和即可快速求得，复杂度为 $O(1)$。

对于代码而言：

1. 这道题对于后缀的处理还是很有讲究的。代码最后一个 `if` 语句：由于到下一轮循环才用到（$i$ 增加 $1$），所以等价于 $i$ 的时候知道了 $s[i-1]-s[i-2]<b$ 推出只能取到 $i-2$（因为以 $i-2$ 转移，那么 $i-1$ 还是可以到的，因为 $[i-1,i-1]$ 区间内只有一个数，一定满足要求） 。开头时无需判断的。
2. 最有统计答案时，需要累加多个 `f[i]`，遇到 $s_{i+1}-s_i<B$ 则停止。原因是这样**相当于后面的数都丢入 $B$ 集合中**，如果不统计答案是不全面的。而遇到前文的条件时，$i$ 还是可以累加的，理由和 1 中括号前半句话的道理是一样的。但是后面就不行了，其实总的说 1 点理解了这点其实更好理解些。
3. 代码中使用了边做边统计的方式，可以考虑分开处理的代码。

对于第 2 点，我认为比较难理解，在此特意点出。

## 代码

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
#define Ls(i,l,r) for(int i=l;i<r;++i)
#define Rs(i,l,r) for(int i=l;i>r;--i)
#define Le(i,l,r) for(int i=l;i<=r;++i)
#define Re(i,l,r) for(int i=l;i>=r;--i)
#define L(i,l) for(int i=0;i<l;++i)
#define E(i,l) for(int i=1;i<=l;++i)
#define W(t) while(t--)
const int N=100010,mod=1e9+7;
typedef long long ll;
int n;
ll a,b,s[N],sum[N];
int main(){
    #ifndef ONLINE_JUDGE
    freopen("1.in","r",stdin);
    // freopen("1.out","w",stdout);
    // ios::sync_with_stdio(0);
    // cin.tie(0);
    // cout.tie(0);
    #endif
    // Insert Code Here
    scanf("%d%lld%lld",&n,&a,&b);
    if(a<b)swap(a,b);
    E(i, n)scanf("%lld",s+i);
    E(i, n-2)if(s[i+2]-s[i]<b)return puts("0"),0;
    sum[0]=1;
    int r=0,l=0;
    E(i, n){
        while(r<i&&s[i]-s[r+1]>=a)++r;
        ll f=0;
        if(l<=r)f=(sum[r]-(r?sum[l-1]:0)+mod)%mod;
        sum[i]=(sum[i-1]+f)%mod;
        if(i>1&&s[i]-s[i-1]<b)l=i-1;
    }
    ll ans=0;
    Re(i, n, 0){
        (ans+=(sum[i]-sum[i-1]+mod)%mod)%=mod;
        if(i<n&&s[i+1]-s[i]<b)break;
    }
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：Sol1 (赞：2)

似乎是当年模拟赛搬的原题，我当时好像打了个奇怪复杂度的暴力 DP 跑路了（

考虑到如果将集合 $S$ 中的数从小到大写成一个序列，则可以将答案看作一段连续的元素进入 $X$，之后的一段进入 $Y$，再之后的一段进入 $X$，以此类推。考虑对这个序列进行 DP。

那么此时一个自然的想法就是设 $f_i$ 表示前 $i$ 个元素中，最后一段元素进入 $X$ 且最后一段恰好在 $i$ 结尾的方案数。类似的，$g_i$ 表示前 $i$ 个元素中，最后一段元素进入 $Y$ 且最后一段恰好在 $i$ 结尾的方案数。但是在转移时会卡住：虽然我们可以枚举最后一段的开头，但是我们无法得知倒数第二段的开头，因此无法得知最后一段开头与倒数第三段结尾的差是否在题目要求范围内。

但是我们可以发现这个状态的定义中暗含一个条件：对于 $f_i$ 要求 $i+1$ 进入 $Y$。因此我们没有必要考虑倒数第三段和最后一段，我们考虑倒数第二段和下一段。下一段的开头已经得知是 $i+1$，倒数第二段的结尾就是我们枚举的东西。因此这个是否合法是容易判定的。于是就可以转移了。

暴力转移的复杂度是 $O(n^2)$，但是容易发现这个转移是区间求和的形式同时区间还有单调性，因此写个双指针就直接 $O(n)$ 做完了。

注意在集合中加入一个 $-\infty$ 和 $+\infty$ 防止边界上爆炸，以及转移区间的确定上稍微有一些细节。这些细节相对 trivial，故不赘述。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1 << 21], *p1 = buf, *p2 = buf;

inline long long qread() {
	register char c = getchar();
	register long long x = 0, f = 1;
	while (c < '0' || c > '9') {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = (x << 3) + (x << 1) + c - 48;
		c = getchar();
	}
	return x * f;
}

const long long mod = 1000000007;
long long f[100005], g[100005];
long long n, a[100005], A, B;

inline void Read() {
	n = qread(); A = qread(); B = qread();
	for (int i = 1;i <= n;i++) a[i] = qread();
}

inline void Solve() {
	sort(a + 1, a + n + 1);
	a[n + 1] = 4e18;
	a[0] = -3e18;
	f[1] = g[1] = 1;
	f[0] = g[0] = 1;
	int lf = 0, rf = 0, lg = 0, rg = 0;
	long long sf = 0, sg = 0;
	for (int i = 2;i <= n;i++) {
		while (rf < i && a[i + 1] - a[rf] >= A) {
			sf = (sf + g[rf]) % mod;
			rf++;
		}
		if (a[i] - a[i - 1] < B) {
			while (lf != i - 1) {
				sf = (sf - g[lf] + mod) % mod;
				lf++;
			}
		}
		if (lf < rf) f[i] = sf;
		while (rg < i && a[i + 1] - a[rg] >= B) {
			sg = (sg + f[rg]) % mod;
			rg++;
		}
		if (a[i] - a[i - 1] < A) {
			while (lg != i - 1) {
				sg = (sg - f[lg] + mod) % mod;
				lg++;
			}
		}
		if (lg < rg) g[i] = sg;
	}
	printf("%lld", (f[n] + g[n]) % mod);
}

int main() {
	Read();
	Solve();
	return 0;
}
```

---

## 作者：圣嘉然 (赞：2)

提供一种慢一些，但也许仍有些参考价值的做法。

考虑暴力 dp 则设 $f(i, j, k)$ 表示划分完前 $i$ 个数，$X$ 的上一个数在 $j$，$Y$ 的上一个数在 $k$ 的方案数。

稍微思考后发现，$jk$ 中一定有一个是 $i$。

所以可以设 $f(i, j, 0/1)$ 表示划分完前 $i$ 个数，上一个数在 $j$ 且它是 $X/Y$ 集合的方案数。

考虑 $i + 1$ 的归属就有：
$$
f(i + 1, j, 0) \leftarrow f(i, j, 0) \\
f(i + 1, i, 1) \leftarrow f(i, j, 0) \\
f(i + 1, j, 1) \leftarrow f(i, j, 1) \\
f(i + 1, i, 0) \leftarrow f(i, j, 1)
$$
第一种转移可以发生当且仅当 $a(i + 1) - a(i) \ge B$，第二种转移可以发生当且仅当 $a(i + 1) - a(j) \ge A$，第三种转移可以发生当且仅当 $a(i + 1) - a(i) \ge A$，第四种转移可以发生当且仅当 $a(i + 1) - a(j) \ge B$。

考虑压掉第一维并用两棵线段树维护 $f$ 数组，即分别维护第三维，一三转移就是要么区间赋值要么直接继承，二四转移则需要二分位置后区间求和单点修改，那么本题就可以做了。

时间复杂度为 ${\mathcal O}(n \log n)$。

```cpp
// Never twist yourself just to please the world.
using ll = long long;
const int MD = 1e9 + 7, N = 1e5 + 5;
inline int plus(const int a, const int b) {
    return (a + b >= MD) ? (a + b - MD) : (a + b);
}
inline int sub(const int a, const int b) {
    return plus(a, MD - b);
}
inline int times(const int a, const int b) {
    return 1ll * a * b % MD;
}
 
int n; ll A, B;
ll a[N];
 
struct seg {
    seg() { std::memset(c, -1, sizeof c); }
    int f[N * 4], c[N * 4];
    inline void pc(int x, int len, int v) {
        f[x] = times(v, len);
        c[x] = v;
    }
    inline void pd(int x, int l, int r) {
        if (~c[x]) {
            int mid = (l + r) >> 1;
            pc(x << 1, mid - l + 1, c[x]), pc(x << 1 | 1, r - mid, c[x]);
            c[x] = -1;
        }
    }
    inline void pu(int x) {
        f[x] = plus(f[x << 1], f[x << 1 | 1]);
    }
    void set(int x, int l, int r, int ql, int qr, int v) {
        if (ql <= l && r <= qr) return pc(x, r - l + 1, v), void();
        pd(x, l, r);
        int mid = (l + r) >> 1;
        if (qr <= mid) set(x << 1, l, mid, ql, qr, v);
        else if (mid < ql) set(x << 1 | 1, mid + 1, r, ql, qr, v);
        else set(x << 1, l, mid, ql, qr, v), set(x << 1 | 1, mid + 1, r, ql, qr, v);
        pu(x);
    }
    int qry(int x, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return f[x];
        pd(x, l, r);
        int mid = (l + r) >> 1;
        if (qr <= mid) return qry(x << 1, l, mid, ql, qr);
        else if (mid < ql) return qry(x << 1 | 1, mid + 1, r, ql, qr);
        else return plus(qry(x << 1, l, mid, ql, qr), qry(x << 1 | 1, mid + 1, r, ql, qr));
    }
} f0, f1;
 
signed main() {
    n = read<int>();
    A = read<ll>(), B = read<ll>();
 
    for (int i = 1; i <= n; ++i) 
        a[i] = read<ll>();
 
    a[0] = -1e18;
    f0.set(1, 0, n, 0, 0, 1), f1.set(1, 0, n, 0, 0, 1);
    // f[1][0][0/1] = 1 
    for (int i = 1; i < n; ++i) {
        int p1 = std::upper_bound(a, a + n + 1, a[i + 1] - A) - a - 1, p2 = std::upper_bound(a, a + n + 1, a[i + 1] - B) - a - 1;
        int upd1 = f0.qry(1, 0, n, 0, p1), upd2 = f1.qry(1, 0, n, 0, p2);
        f1.set(1, 0, n, i, i, upd1);
        f0.set(1, 0, n, i, i, upd2);
 
        if (a[i + 1] - a[i] < B) {
            f0.set(1, 0, n, 0, i - 1, 0);
        }
        if (a[i + 1] - a[i] < A) {
            f1.set(1, 0, n, 0, i - 1, 0);
        }
    }
    int res = plus(f0.qry(1, 0, n, 0, n), f1.qry(1, 0, n, 0, n));
    write(res);
}
// St. JR bless you
```

---

## 作者：PosVII (赞：1)

**前言**

------------

好玩的好题，我这里给出 $O(n \log n)$ 的线段树做法。

**思路**

------------

首先有个超级暴力的 $O(n^3)$ 做法，我们设 $dp_{i,j,k}$ 为当你取完第 $i$ 个数后，$X$ 中最晚取到的数下标为 $j$，$Y$ 中最晚取到的数下标为 $k$，每次转移就判断当前集合中最晚加入的两个是否合法即可。

显然，一个合法的状态中，$j$ 和 $k$ 中一定有一个等于 $i$，那么我们将其优化为 $O(n^2)$ 的做法。即 $dp_{i,j,0/1}$ 表示为当你取完第 $i$ 个数后，我们将 $i$ 取到了 $X$ 或 $Y$ 集合，剩下的集合中最晚取到的数下标为 $j$。

因为它时空都是 $n^2$ 大小，首先考虑优化时间，因为第 $i$ 个数可以和哪些数取在一起是单调的，只要一个数可以和第 $i$ 个数一起取，它前面的数都可以和 $i$ 一起取，可以二分。这样我们的状态转移变成区间和查询加单点修改，可以使用线段树。

空间是 $n^2$，可以使用滚动线段树的方法，比较麻烦，容易写挂，看看就好。

**code**

------------

```
#include<bits/stdc++.h>
using namespace std;
template<typename G>inline void read(G&x) {x=0;G f=1;char ch=getchar();while((ch<'0'||ch>'9')&&ch!='-') ch=getchar();if(ch=='-') f=-1,ch=getchar();while(ch>='0'&&ch<='9') x=x*10+(ch^48),ch=getchar();x*=f;}
const int MAXN=1e5+5,mod=1e9+7;
long long d[MAXN*4][2],lazy[MAXN*4][2];
long long a,b,arr[MAXN];
void cover(int l,int r,int ql,int qr,int p,long long c,int z) {
	if(l>=ql&&r<=qr) {
		d[p][z]=(c*(r-l+1))%mod,lazy[p][z]=c;
		return;
	}
	int mid=(l+r)>>1;
	if(ql<=mid) cover(l,mid,ql,qr,p<<1,c,z);
	if(qr>mid) cover(mid+1,r,ql,qr,p<<1|1,c,z);
	d[p][z]=(d[p<<1][z]+d[p<<1|1][z])%mod;
}
long long query(int l,int r,int ql,int qr,int p,int z) {
	if(qr<ql) return 0;
	if(l>=ql&&r<=qr) return d[p][z];
	int mid=(l+r)>>1;long long res=0;
	if(~lazy[p][z]) {
		d[p<<1][z]=(lazy[p][z]*(mid-l+1))%mod,d[p<<1|1][z]=(lazy[p][z]*(r-mid))%mod;
		lazy[p<<1][z]=lazy[p<<1|1][z]=lazy[p][z];
		lazy[p][z]=-1;
	}
	if(ql<=mid) res+=query(l,mid,ql,qr,p<<1,z);
	if(qr>mid) res+=query(mid+1,r,ql,qr,p<<1|1,z);
	return res%mod;
}
int bs(int l,int r,long long x) {
	if(l==r) return l;
	if(l+1==r) {
		if(arr[r]<=x) return r;
		else return l;
	}
	int mid=(l+r)>>1;
	if(arr[mid]<=x) return bs(mid,r,x);
	else return bs(l,mid-1,x);
}
int n;
int main() {
	memset(lazy,-1,sizeof(lazy));
	read(n),read(a),read(b);
	arr[0]=-1e18;cover(0,n,0,0,1,1,0),cover(0,n,0,0,1,1,1);
	for(int i=1;i<=n;++i) {
		read(arr[i]);
		int c1=query(0,n,0,bs(0,i-1,arr[i]-a),1,1),c2=query(0,n,0,bs(0,i-1,arr[i]-b),1,0);
		cover(0,n,i-1,i-1,1,c1,0);
		cover(0,n,i-1,i-1,1,c2,1);
		if(arr[i]-arr[i-1]<a&&i>=2) cover(0,n,0,i-2,1,0,0);
		if(arr[i]-arr[i-1]<b&&i>=2) cover(0,n,0,i-2,1,0,1);
	} 
	printf("%lld",(query(0,n,0,n-1,1,0)+query(0,n,0,n-1,1,1))%mod);
	return 0;
} 
/*
dp[i][i-1][1]+=dp[i-1][j][0] (arr[i]-arr[j]>=b)
dp[i][i-1][0]+=dp[i-1][j][1] (arr[i]-arr[j]>=a)
dp[i][j][1]=dp[i-1][j][1] (arr[i]-arr[i-1]>=b)
dp[i][j][0]=dp[i-1][j][0] (arr[i]-arr[i-1]>=a)

dp[i][j][2]

3 7
1 3 6 9 12
*/ 
```

---

## 作者：Sasiyar (赞：0)

看到没有题解，补一下。

# Solution

考虑 $f_i$ 表示第 $i$ 个数放到 $B$ 的集合中 ($B>A$,否则交换) 。

每次状态转移有两个限制条件，一个限制左边界(相邻的数值的差必须为大于等于 $A$ 的)，一个限制右边界(右端点与当前的 $i$ 位置的差必须是大于等于 $B$ 的)，分别是 $A$ 集合的限制与 $B$ 集合的限制，若右端点在左端点的左边就没合法解，此时 $f_i$ 为 $0$ ，否则前缀和计算当前的 $f$ 值。

# Code

```cpp
#include <bits/stdc++.h>
#define ll long long
#define int ll
using namespace std;
struct _in {
	const _in operator , (int&a) const {
		a = 0; int f = 1; char k = getchar ();
		while (k > '9' || k < '0') { if (k == '-') f = -1; k = getchar (); }
		while (k >= '0' && k <= '9') { a = a * 10 + k - '0'; k = getchar (); }
		a *= f; return*this;
	}
}in;
const int N = 100000 + 5, mod = 1000000007;
int info[N], A, B, f[N], n, sumf[N];
inline void solve () {
	int curx = 0, cury = 0;
	sumf[0] = f[0] = 1;
	for (int i = 1; i <= n; ++i) {
		while (cury < i - 1 && info[i] - info[cury + 1] >= B) ++cury;
		if (cury >= curx) f[i] = (sumf[cury] - (curx == 0 ? 0 : sumf[curx - 1]) + mod) % mod;
		sumf[i] = (sumf[i - 1] + f[i]) % mod;
		if (i > 1 && info[i] - info[i - 1] < A) curx = i - 1;
	}
	int ans = 0;
	for (int i = n; i >= 0; --i) {
		ans = (ans + f[i]) % mod;	
		if (i < n && info[i + 1] - info[i] < A) break;
	}
	printf ("%lld\n", ans);
}
signed main () {
	in, n, A, B;
	if (n == 1) { printf ("2\n"); return 0; }
	if (A > B) swap (A, B);
	for (int i = 1; i <= n; ++i)
		in, info[i];
	sort (info + 1, info + n + 1);
	for (int i = 3; i <= n; ++i)
		if (info[i] - info[i - 2] < A) { printf ("0\n"); return 0; }
	solve ();
	return 0;
}
```

---

## 作者：bulijoijiodibuliduo (赞：0)

没事先排个序，然后开始dp。

[![vT0rpn.png](https://s1.ax1x.com/2022/09/05/vT0rpn.png)](https://imgse.com/i/vT0rpn)

我们只需要考虑上图中每个 $A$ 的位置的情况就可以了。

令 $dp_i$ 表示第 $i$ 个位置选则最后一个 $A$ 的种类数。

再令 $lst_i$ 表示以 $i$ 为结尾，最长连续的 $B$ 左端点在哪里。

为了方便表示，我们让 $pos$ 为最大的满足 $a_i-a_{pos} \ge A$ 的下标。

那么 $dp_i=\sum^{pos}_{lst_{i-1}-1}dp_i$。

若 $a_i-a_{i-1}\ge B$ ，$lst_i=lst_{i-1}$。

否则 $lst_i=i$。

$pos$ 可以二分计算。

最后统计答案就只要在序列后面加一个 $Inf$，答案就是 $dp_{n+1}$。

还要考虑无解的情况，就是存在 $x$，满足 $a_{x+2}-a_x \le min(A,B)$ ，此时输出 $0$ 即可。

代码如下：
```c++
/*
* @Author: wdssean
* @Last Modified time: 2022-09-05 10:19:56
*/
#include<bits/stdc++.h>
using namespace std;
#define qin cin
#define qout cout
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define fin(s) freopen(s,"r",stdin)
#define fout(s) freopen(s,"w",stdout)
#define fio(s) fin(s".in"),fout(s".out")
#define ll long long
#define ull uint64_t
#define lll __int128
#define ulll __uint128_t
#define db double
#define rep(i,a,b) for(auto i=(a);i<=(b);i++)
#define per(i,a,b) for(auto i=(a);i>=(b);i--)
#define pb push_back
#define fi first
#define se second
#define All(a) (a).begin(),(a).end()
#define Size(a) ((int)(a).size())
#define mem(a,b) memset(a,b,sizeof(a))
mt19937 rnd(random_device{}());
#define int long long
const int mod=1e9+7,N=1e5+10;
const ll inf=9e18;
int n,lst[N],sum[N],dp[N];
ll A,B,a[N];
signed main(){
  qin>>n>>A>>B;if(A<B)swap(A,B);
  rep(i,1,n)qin>>a[i];
  a[++n]=inf;
  sort(a+1,a+1+n);
  rep(i,1,n-2)if(a[i+2]-a[i]<B){qout<<"0\n";return 0;}
  lst[0]=lst[1]=1;rep(i,2,n)lst[i]=(a[i]-a[i-1]>=B?lst[i-1]:i);
  dp[0]=sum[0]=1;
  rep(i,1,n){
    int mx=upper_bound(a+1,a+1+n,a[i]-A)-a-1,mn=lst[i-1]-1;
    if(mn<=mx)dp[i]=(sum[mx]-(mn?sum[mn-1]:0)+mod)%mod;
    else dp[i]=0;
    sum[i]=(sum[i-1]+dp[i])%mod;
  }
  qout<<dp[n]<<'\n';
}
```

---

## 作者：SunsetSamsara (赞：0)

## 题意

给定 $n$ 个不同的整数，求将它们分成两个集合$X,Y$，并且 $X \small\textsf{中任意2个数的差} \ge A$，$Y \small\textsf{中任意2个数的差} \ge B$ 的方案数。

## 前置知识

动态规划

## 分析

首先，如果三个数两两之差同时大于 $A$ 或同时大于 $B$，则由抽屉原理，因为这三个数必定有 $2$ 个在同一个集合内，而三个数中每两个数都不能放在同一集合里，所以无解。

接下来为了少讨论一些情况，我们令 $A \ge B$

然后发现动态规划可以用一个数组存储划分的状态。我们可以记 $f_i$ 为 $X$ 中的最后一个数是 $i$ 的情况数。然后就可以考虑转移了。

我们开始考虑能够转移的位置。不难发现，能够转移的位置是一个区间，且满足 $a_i - a_j \ge A$。只需要使用前缀和优化一下就可以了。

## 代码

```cpp
#include <stdio.h>
#define lld long long
const int mod = 1e9 + 7;
const int N = 100010;
int n;
lld A, B, a[N];
int f[N], sum[N];
int main() {
	scanf("%d%lld%lld", &n, &A, &B);
	for (int i = 1; i <= n; ++ i) scanf("%lld", a + i);
	for (int i = 1; i + 2 <= n; ++ i)
		if (a[i + 2] - a[i] < A && a[i + 2] - a[i] < B) {
			puts("0"); // 特判
			return 0;
		}
	if (A < B) A ^= B ^= A ^= B;
	f[0] = sum[0] = 1;
	int l = 0, r = 0;
	for (int i = 1; i <= n; ++ i) {
		while (r < i && a[i] - a[r + 1] >= A) ++ r; // 向后拓展区间
		if (l <= r)
			f[i] = (f[i] + (sum[r] - (l ? sum[l - 1] : 0) + mod) % mod) % mod; // 前缀和
		sum[i] = (sum[i - 1] + f[i]) % mod;
		if (i > 1 && a[i] - a[i - 1] < B) l = i - 1;  // 向后收缩区间
	}
	int ans = 0;
	for (int i = n; i >= 0; -- i) {
		ans = (ans + f[i]) % mod;
		if (i < n && a[i + 1] - a[i] < B) break;
	}
	printf("%d\n", ans);
}
```

---

