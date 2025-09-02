# 「SFCOI-3」进行一个列的排

## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/8v9kbxjs.png)

（其实这题原来叫 I must say No，不过出于某些显然的原因就改题目名了 /kk）

You must say Yes.

（题目背景图片来自 Phigros 曲绘，如有侵权，请告知出题人。）

## 题目描述

小 R 有一个长度为 $n$ 的排列 $p_1\dots p_n$。换句话说，$p_1\dots p_n$ 包含 $0 \sim (n - 1)$ 之间的数，并且满足对于 $0 \sim (n - 1)$ 这 $n$ 个数，每个数在 $p$ 中出现且仅出现一次。

小 R 有 $n$ 个限制，其中第 $i(0 \leq i \leq n - 1)$ 个用一个![](cnm,shabierLeasier)**正整数** $L_i$ 描述，表示至少有一个长度为 $L_i$ 的区间 $[l, r]$（即 $r - l + 1 = L_i$）满足 $\operatorname{mex}_{k=l}^r p_k = i$。

小 R 丢失了排列 $p_1\dots p_n$，不过幸运的是她仍然记得这 $n$ 条限制。请你帮她求出总共有多少个初始的合法排列，答案对 $998244353$ 取模。

## 说明/提示

### 定义

+ 一个序列的 $\operatorname{mex}$ 是其中没有出现过的最小非负整数，如 $\operatorname{mex}\{1, 3, 4\} = 0$，$\operatorname{mex}\{0, 1, 1, 2, 5\} = 3$，$\operatorname{mex}\{3, 1, 0, 2\} = 4$。

### 数据规模与约定

+ Subtask 0（10 pts）：$n \leq 10$。
+ Subtask 1（30 pts）：$n \leq 18$。
+ Subtask 2（15 pts）：$n \leq 300$。
+ Subtask 3（45 pts）：无特殊限制。

对于所有数据，$1 \leq T \leq 10$，$1 \leq n \leq 5 \times 10^3$，$1 \leq L_i \leq n$。

## 样例 #1

### 输入

```
4
4
1 1 3 3
5
2 1 3 3 4
6
1 1 2 5 4 5
10
3 2 3 4 7 6 8 8 8 9```

### 输出

```
4
12
8
96```

# 题解

## 作者：vegetable_king (赞：18)

考虑一个 dp，设 $f_{k, i, j}$ 表示目前填了 $0 \sim k$，这些数最左的在 $i$，最右的在 $j$。发现每次新填入 $k + 1$，填的位置不可能在 $[i, j]$ 内，因为这样就不存在 $\operatorname{mex} = k + 1$ 的区间了。所以，$k + 1$ 只能填在 $i - 1, j + 1$ 其中之一位置，否则就留出了不能填的空隙，导致后填的数位置不足。

于是填下的位置一定是连续的一段，即 $k = j - i$，我们就可以省略 $k$，转移显然：

$$f_{i, i} = [i > L_0 \vee n - i \ge L_0]$$

$$f_{i, j} = [j > L_k]f_{i, j - 1} + [n - i \ge L_k]f_{i + 1, j} (i < j)$$

时间复杂度为 $O(n^2)$，代码略。

---

## 作者：irris (赞：13)

> Tag：dp / 计数 / **弱化条件**

我们先把 $L_i$ 的限制去掉，转化为分别 **至少存在一个**  $\operatorname{mex}$ 为 $0 \sim (n - 1)$ 的区间。

那么结论是：排列是下凸的。或者用一种更好的描述方法，就是 $\forall k \in [0, n - 1]$ 满足原排列中 $0 \sim k$ 形成一个连续段。

> 证明：不妨假设有一个最小的 $p$ 不满足 $0 \sim p$ 形成一个连续段，那么显然 $\operatorname{mex}$ 为 $0 \sim p$ 的区间都是存在的。如果我们要得到一个 $\operatorname{mex}$ 为 $p + 1$ 的区间（如果 $p + 1 \geq n$ 也就是说 $p = n - 1$ 显然并不成立，所以 $p \leq n - 1$，在题目的约束范围内）。
> 
> 我们不妨设最小包含 $0 \sim p$ 的连续段中，包含的不在 $[0, p]$ 范围内的数的集合为 $S$（由于 $0 \sim p$ 不是一个连续段，那么 $S$ 非空）。由于要得到一个「$\operatorname{mex}$ 为 $p + 1$ 的区间」，它应当包含 $0 \sim p$ 内的所有数但不包含 $p + 1$，所以 $(p + 1) \not\in S$（否则，这个区间的 $\operatorname{mex}$ 至少为 $p + 2$）；同理，使这个连续段延伸到加入 $p + 1$，那么 $(p + 2) \notin S$；一直往复，得到 $\gt p$ 的数都不在 $S$ 内。又由于定义，$\leq p$ 的数都不在 $S$ 内，因此 $S$ 是空集，因此与假设矛盾。

---

得到这个结论，你可以设计一些简单的 dp：比如从小到大，设 $f_{i,j}$ 表示 $[0, i]$ 之间的数填充区间 $[j, j + i]$ 的方案数；或者从大到小，设 $f_{i,j}$ 表示前 $i$ 个数填充了前缀 $[1,j]$ 后缀 $[n - i + j + 1, n]$ 的方案数。

std 采用上述方法中的前者。转移为：

+ 初始状态为 $f_{0,j} = [\max(j - 1, n - j) \geq L_0]$；
+ $f_{i,j}$ 显然可以由 $f_{i-1,j}$ 和 $f_{i-1,j+1}$ 转移而来，具体地，即 $f_{i,j} = [i + j - 1 \geq L_i]f_{i-1,j} + [n - j \geq L_i]f_{i-1,j+1}$。

艾弗森括号的意思是，如果可行的区间最大长度（即选择 $0 \sim ( i - 1)$ 的连续段并延伸到连续段两侧没有 $i$ 的一测的尽头）不低于 $L_i$，那么它就可行。

**边界条件**：如果 $L_i \lt i$，那么这样的区间不可能成立，应当输出 $0$（因为我们在转移时，仅约束了区间长度上界而没有约束下界）。

---

## 作者：xiaosi4081 (赞：7)

upd 2024.8.22：整篇文章重构。

仔细观察题面不难发现一个性质：$0 \sim n-1$ 这 $n$ 个数在符合条件的序列中都会成为一段区间的 $\operatorname{mex}$ 值。

一个值 $x$ 想要成为序列区间的 $\operatorname{mex}$ 值，必须要保证包含 $0 \sim x-1$ 的极小区间不包含 $x$。

![](https://cdn.luogu.com.cn/upload/image_hosting/pqd8yed8.png)

由于这个 $x$ 的取值区间是 $0\sim n-1$，所以我们得出一个显然的结论：这个序列是一个单峰序列，且下凸。

另外判断一下 $L_i<i$ 的情况，是无解的。

接下来就是一个单峰序列计数，已知区间 $[l,r]$ 包含 $0 \sim r-l$ 的数，我们直接在左右加入 $r-l+1$ 这个数即可。

在左右加数或者初始化的时候，判断一下有没有足够的地方放下 $\operatorname{mex}=r-l+1$ 的区间。  

upd：本来空间 $O(n^2)$ 的区间 dp 是能过的，然后空间限制改了。

可以发现开 $O(n^2)$ 的数组非常费空间，然后又发现转移是从上一层转移过来的，滚动数组一下即可。


```c++
#include<bits/stdc++.h>
#define mod 998244353
using namespace std;
int t,n,l[5005],f[2][5005];
signed main(){
	cin>>t;
	for(;t;t--){
		cin>>n;
		memset(f, 0, sizeof f);
		for(int i=0;i<n;i++){
			cin>>l[i];
		}
		bool flag=1;
		for(int i=0;i<n;i++){
			if(l[i]<i){
				cout<<0<<endl;
				flag=0;
				break;
			}
		}
		if(flag==0)continue;
		for(int i=1;i<=n;i++){
			f[1][i]=(i>l[0]||n-i>=l[0]);
		}
		for(int len=2;len<=n;len++){
			int now = len&1;
			memset(f[now], 0, sizeof f[now]); 
			for(int i=1;i+len-1<=n;i++){
				int j=i+len-1;
				f[now][i]=((n-i)>=l[len-1])*f[now^1][i+1]+(j>l[len-1])*f[now^1][i];
				f[now][i]%=mod;
			}	
		}
		cout<<f[n&1][1]<<endl;
	}
	
	return 0;
}
```

感谢 @A_small_WA 的提醒，要不然我都不知道改空限了

---

## 作者：Hisaishi_Kanade (赞：4)

原题的限制条件，相当于存在 $n-1$ 个区间使得其长度 $\ge L_i$，$\text{mex}=i$。如果一个区间其 $\text{mex}=i$ 会满足什么条件？

显然的，$\text{mex}=i$ 则区间出现了 $[0,i)$ 中所有的整数。所以其长度 $\ge i$。

那么首先判一下 $L_i<i$，这就无解了。

手玩样例可以发现一个很好的性质就是，结果不会存在 $i<j<k$ 但 $p_{j}>p_i$ 的同时 $p_j>p_k$。证明依然运用 $\text{mex}=i$ 则区间出现了 $[0,i)$ 中所有的整数的性质，会发现排列不会存在 $\text{mex}=p_j$ 的区间。

假设存在这样的区间，则其必须包括 $p_i,p_k$ 不包括 $p_j$，而因为 $i<j<k$，这样的区间不能存在。

那么也就是证明了，结果排列必然是下凸的。更进一步的，$[0,i]$ 的数排在 $[l,r]$ 后，$i+1$ 必然在 $l-1$ 或 $r+1$（如果可以）。

这就可以动态规划求解，放在 $l-1$ 必须保证 $[l,n]$ 的长度 $\ge L$；类似的，$r+1$ 必须保证 $[1,r]$ 的长度 $\ge L$。这其实还是“所以其长度 $\ge i$”的那个结论。

然后实现一下就好了，$f(l,r)$ 表示 $[0,r-l]$ 填入 $[l,r]$ 的方案数。转移时为了避免后效性以长度划分阶段。

```cpp
#include <bits/stdc++.h>
#define rep(i, l, r) for(i=l; i<=r; ++i)
using namespace std;
const int N=5e3+5, p=998244353;
int f[N][N], L[N];
int n, i, j, k, t;
int main()
{
	scanf("%d", &t);
	nxt:
	while(t--)
	{
		scanf("%d", &n);
		rep(i, 1, n) rep(j, 1, n) f[i][j]=0;
		rep(i, 0, n-1) scanf("%d", L+i);
		rep(i, 0, n-1) if(L[i]<i) {printf("0\n"); goto nxt;}
		rep(i, L[0]+1, n) f[i][i]=1;
		rep(i, 1, n-L[0]) f[i][i]=1;
		rep(k, 1, n-1)
			rep(i, 1, n-k)
			{
				j=i+k;
				if(j>L[k]) f[i][j]+=f[i][j-1];
				if(n-i>=L[k]) f[i][j]+=f[i+1][j];
				f[i][j]%=p;
			}
		printf("%d\n", f[1][n]);
	}
	return 0;
}
```

---

## 作者：TernaryTree (赞：3)

非常好的题，拜谢 irris 老师。

首先就是既然 $0\sim n-1$ 的 $\operatorname{mex}$ 都要出现，那么对于所有 $x$，排列中 $\le x$ 的数必然会构成一个连续的区间，也就是说这个序列以 $0$ 为分界点，左边单调下降，右边单调递增，可以证明~~或打表发现~~。

然后剩下的事情就很好办！设 $f_{i,j}$ 表示 $0\sim i$ 的数，填在 $j$ 开头的区间 $[j,j+i]$ 内的方案数。那么显然可以按当前最大值 $i$ 在最左端/最右端转移。最左端的转移即 $f_{i-1,j+1}$，此时要满足的条件是 $j+1$ 后面的位置要足够多，能组成一个长度为 $L_i$ 的区间，即 $n-j\ge L_i$；最右端的转移同理，$f_{i-1,j}$，条件是 $i+j-1\ge L_i$。

初始状态 $f_{0,j}$ 为 $[\max(j-1,n-j)\ge L_0]$，因为至少要有一个区间不包含 $0$，即 $\operatorname{mex}=0$。

滚动数组实现。

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int maxn = 5e3 + 10;
const int mod = 998244353;

int T, n;
int a[maxn];
int f[maxn];

signed main() {
	cin >> T;
	while (T--) {
		memset(f, 0, sizeof(f));
		bool fl = 1;
		cin >> n;
		for (int i = 0; i < n; i++) {
			cin >> a[i];
			if (a[i] < i) fl = 0;
		}
		if (!fl) {
			cout << 0 << endl;
			continue;
		}
		for (int j = 1; j <= n; j++) f[j] = max(j - 1, n - j) >= a[0];
		for (int i = 1; i < n; i++) {
			for (int j = 1; j <= n; j++) {
				f[j] *= (i + j - 1 >= a[i]);
				if (n - j >= a[i]) (f[j] += f[j + 1]) %= mod;
			}
		}
		cout << f[1] << endl;
	}
	return 0;
}

```

---

## 作者：sleepy66 (赞：2)

~~今天又是被区间动规薄纱的一天(bushi)~~。

考虑**动规**。我们可以按**从小到大**的顺序依次填数，并由此转移。设数组 $f_{i,j}$ 表示填完了区间 $[i,j]$，且所填的数为 $0$ 到 $j-i$ 的方案数。

考虑不可能的情况，如果长度为 $l_i$ 的区间的 $\operatorname{mex}$ 值为 $x$ ，则区间内肯定包含了 $0$ 到 $x-1$，那么如果 $l_i<i$，那么该区间最多只能包含 $0$ 到 $i-2$。显然，区间的 $\operatorname{mex}$ 值不可能为 $i$，此时直接判断无解即可。

接着考虑边界，如果一个位置 $i$ 左边或右边有区间能满足 $l_0$，那么该位置就有可能填 $0$，此时 $f_{i,i}=1$。

接下来是转移方程，显然一个数只能填在新区间的左端点或右端点，否则就会留出无法填的位置，导致无法满足后面要填的数 $x$ 的 $l_x$，会使得 $x$ 被比他小的数夹住。所以，假设要填入的数为 $x$，如果区间的一边在填入了 $x$ 后能满足 $l_x$，就考虑将数填入端点中。如果两边都可以填入，则方案数为 $f_{i+1,j}+f_{i,j-1}$，就是将两种方案的可能方案数累加。

最后答案记得取模即可。
 
```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=998244353;
int n,l[5000],f[5001][5001];
signed main(){
	int tmp;
	scanf("%d",&tmp);
	while(tmp--){
		memset(f,0,sizeof(f));
		scanf("%d",&n);
		bool flag=true;
		for(int i=0;i<n;i++){
			scanf("%d",&l[i]);
			if(l[i]<i)flag=false;//判断无解
		}
		if(!flag){
			printf("0\n");
			continue;
		}
		for(int i=1;i<=n;i++){
			if(i>l[0]||(n-i+1)>l[0])f[i][i]=1;//边界
		}
		for(int len=2;len<=n;len++){
			for(int i=1;i+len-1<=n;i++){
				int j=i+len-1;
				if(n-i>=l[len-1])f[i][j]+=f[i+1][j];//将数填入i的位置中
				if(j-1>=l[len-1])f[i][j]+=f[i][j-1];//将数填入j的位置中
				f[i][j]%=mod;
			}
		}
		printf("%d\n",f[1][n]);
	}	
}
```


---

## 作者：ZHR100102 (赞：1)

这么多 mex 的限制叠在一起显然不好考虑，我们先考虑一个可能性最少的限制如何满足，即 $i=n-1$ 的限制。首先因为 mex 是 $n-1$，所以这个区间必须至少包含 $n-1$ 个分别是 $0\sim n-2$ 的元素，那么这个区间就只剩下两种情况了：一个是 $[1,n-1]$，一个是 $[2,n]$。显然此时 $n-1$ 必须放在头或者尾部，并且当 $L=n$ 或者 $L<i$ 的时候是一定无解的。

于是 $i=n-1$ 的限制解决了以后，我们得到了区间 $[1,n-1]$ 或者 $[2,n]$。继续依次考虑 $i=n-2,n-3,\dots$ 的限制，不难发现这些限制和第一个限制一样，都是 $i$ 只能放头尾两个位置，给后面限制留下的区间长度逐层递减。再加上 $L$ 对答案的限制，可以推出区间 $[l,r]$ 所放元素能放左端点的条件是 $r-1\ge L$，能放右端点的条件是 $n-l\ge L$。原因都是上面那个 mex 的限制。

得到了这个区间的结论，设计区间 DP 是容易的，$dp_{i,j}$ 表示考虑完了 $j-i+1\sim n-1$ 的限制，并且缩到区间 $[i,j]$ 的方案数，分讨两个端点，按照上述条件，刷表法转移即可。初值是 $dp_{1,n}=1$，答案是 $\sum _{i=1}^n dp_{i,i}$。

时间复杂度 $O(n^2)$，注意到这题卡空间，可以利用滚动数组把 DP 阶段按照区间长度分层，空间就被优化到了 $O(n)$。同时注意特判无解，输出 $0$ 即可。

```cpp
#include <bits/stdc++.h>
#define fi first
#define se second
#define eb(x) emplace_back(x)
#define pb(x) push_back(x)
#define lc(x) (tr[x].ls)
#define rc(x) (tr[x].rs)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ldb;
using pi=pair<int,int>;
const int N=5005;
const ll mod=998244353;
int n,a[N];
ll dp[2][N],ans=0;
bool legal=1;
void solve()
{
    legal=1;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        if(a[i]==n||a[i]<i-1)legal=0;
    }
    if(n==1)legal=0;
    if(legal==0)
    {
        cout<<0<<'\n';
        return;
    }
    memset(dp,0,sizeof(dp));ans=0;
    dp[n&1][1]=1;
    for(int len=n;len>=2;len--)
    {
        int tlen=((len-1)&1);
        memset(dp[tlen],0,sizeof(dp[tlen]));
        for(int i=1;i+len-1<=n;i++)
        {
            int j=i+len-1;
            if(j-1>=a[len])dp[tlen][i]=(dp[tlen][i]+dp[len&1][i])%mod;
            if(n-i>=a[len])dp[tlen][i+1]=(dp[tlen][i+1]+dp[len&1][i])%mod;
        }
    }
    for(int i=1;i<=n;i++)ans=(ans+dp[1][i])%mod;
    cout<<ans<<'\n';
}
int main()
{
    //freopen("sample.in","r",stdin);
    //freopen("sample.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin>>t;
    while(t--)solve();
    return 0;
}
```

---

## 作者：DengDuck (赞：1)

一个 $\operatorname{mex}$ 为 $i$ 的区间必然满足包含 $[0,i-1]$，不包含 $i$，这题有 $1\leq L_i$，所以这个区间必然是得有的。

进一步地，我们得到这样的结论，$i$ 肯定不会夹在 $[0,i-1]$ 中间，由于这个的结论的存在我们知道 $x\in[i+1,n]$ 也不会出现在 $[0,i-1]$ 中间，因为这样它就在 $[0,x-1]$ 中间了。

所以我们发现合法的形状应该是从小到大把数字放在两边。

然后我们不难想到反过来，从两边放，这样可以方便处理 $L_i$ 的限制，我们设 $F_{i,j}$ 表示已经放了 $[i,n]$ 的数字，使得 $[1,j]$ 和 $[n-i+j+1,n]$ 的被填充的方案数。

转移考虑 $i$ 放在了哪里：

- 如果在左边 $F_{i,j}=F_{i+1,j-1}$，条件是 $n-j\geq L_i$。
- 如果在右边 $F_{i,j}=F_{i+1,j}$，条件是 $i+j-1\geq L_i$。

考虑滚动数组优化即可。

然后你会发现过不了样例，然后你想到最后一个 $1$ 既可以认为放在左边也可以认为放在右边，所以考虑特殊处理放 $1$。

还有就是上面给的条件实质上是给了个构造出的最长区间，实际上最短区间的长度应该是 $i-1$，所以需要特判 $L_i<i-1$。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int N=5005;
const int Mod=998244353;
int n,L[N];
LL F[2][N];
inline void Work()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&L[i]);
	for(int i=1;i<=n;i++)if(L[i]<i-1)return puts("0"),void();
	memset(F,0,sizeof(F));
	F[(n+1)&1][0]=1;
	for(int i=n;i>=2;i--)
	{
		int t=i&1;
		for(int j=0;j<=n-i+1;j++)
		{
			F[t][j]=0;
			if(i+j-1>=L[i])(F[t][j]+=F[t^1][j])%=Mod;
			if(n-j>=L[i]&&j)(F[t][j]+=F[t^1][j-1])%=Mod;
		}
	}
	LL Ans=0;
	for(int i=0;i<=n;i++)
	{
		if(i<L[1]&&n-1-i<L[1])break;
		(Ans+=F[0][i])%=Mod;
	}
	printf("%lld\n",Ans);
}
int main()
{
	int T;scanf("%d",&T);
	while(T--)Work();
}
```

---

