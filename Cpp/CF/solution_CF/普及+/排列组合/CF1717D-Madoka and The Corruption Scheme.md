# Madoka and The Corruption Scheme

## 题目描述

Madoka decided to entrust the organization of a major computer game tournament "OSU"!

In this tournament, matches are held according to the "Olympic system". In other words, there are $ 2^n $ participants in the tournament, numbered with integers from $ 1 $ to $ 2^n $ . There are $ n $ rounds in total in the tournament. In the $ i $ -th round there are $ 2^{n - i} $ matches between two players (one of whom is right, the other is left), after which the winners go further along the tournament grid, and the losing participants are eliminated from the tournament. Herewith, the relative order in the next round does not change. And the winner of the tournament — is the last remaining participant.

But the smaller the participant's number, the more he will pay Madoka if he wins, so Madoka wants the participant with the lowest number to win. To do this, she can arrange the participants in the first round as she likes, and also determine for each match who will win — the participant on the left or right.

But Madoka knows that tournament sponsors can change the winner in matches no more than $ k $ times. (That is, if the participant on the left won before the change, then the participant on the right will win after the change, and if the participant on the right won, then the participant on the left will win after the change).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1717D/f3b4c42531ac8b0aab0fa40e7e46069a137caf77.png)So, the first image shows the tournament grid that Madoka made, where the red lines denote who should win the match. And the second one shows the tournament grid, after one change in the outcome of the match by sponsors (a match between $ 1 $ and $ 3 $ players).Print the minimum possible number of the winner in the tournament, which Madoka can get regardless of changes in sponsors. But since the answer can be very large, output it modulo $ 10^9 + 7 $ . Note that we need to minimize the answer, and only then take it modulo.

## 说明/提示

In the first example, there is only one match between players $ 1 $ and $ 2 $ , so the sponsors can always make player $ 2 $ wins.

The tournament grid from the second example is shown in the picture in the statement.

## 样例 #1

### 输入

```
1 1```

### 输出

```
2```

## 样例 #2

### 输入

```
2 1```

### 输出

```
3```

## 样例 #3

### 输入

```
3 2```

### 输出

```
7```

# 题解

## 作者：Hedgehog_210508 (赞：11)

**题目传送门**：[here](https://www.luogu.com.cn/problem/CF1717D)

**思路**：这题目乍一看就很奇怪。

所以我们不妨**把原题中的比赛看做一棵树，倒过来从上往下走**。

下面举一个 $n=3$ 且 $k=1$ 例子:

![](https://cdn.luogu.com.cn/upload/image_hosting/7g8dhyul.png)

不妨设原先都是左边获胜，从根往下走时都选择左边，那么根据题意，现在主办方可以选择至多 $k$ 步向右走，能达到的地方打了红勾（见上图）。

显然，答案是所有能走到的地方的最大值，所以她从 $1$ 开始依次安排。

接下来问题就转换为了 _在这样的树上最多向右走 $k$ 步能够走到的位置个数。_ 通过简单地计数知识，可得答案为 $\sum_{i=0}^k(C_n^i)$。通过快速幂和逆元即可正确计算组合数（显然当 $k \ge n$ 时就没必要傻傻地做了，改变 $k$ 次必定有所有之中的最大值）。

**代码**：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define M 1000000007
ll n,k,p[200009];
ll t; //114514
ll qp(ll a,ll b){
	if(b==1) return a;
	if(b==0) return 1;
	ll ans=1;
	if(b%2) b--,ans*=a;
	ll tmp=qp(a,b/2);
	ans*=tmp%M*tmp%M;
	return ans%M;
}
ll c(ll a,ll b){
	return p[a]%M*qp(p[b],M-2)%M*qp(p[a-b],M-2)%M; 
}
int main(){
	std::ios::sync_with_stdio(false);
	cin>>n>>k;
	if(k>=n){
		cout<<qp(2,n);
		return 0;
	}
	p[0]=1;
	for(ll i=1;i<=n;i++) p[i]=p[i-1]*i%M;
	ll tmp=0;
	for(ll i=0;i<=k;i++) tmp+=c(n,i),tmp%=M;
	cout<<tmp;
	return 0;
}
```


---

## 作者：whhsteven (赞：6)

题目所问是：指定一个局面，使得在最坏情况下，赞助商做完调整后，获得冠军的人编号尽可能小。

考虑在最坏情况下，则面对一个我们指定的局面时，赞助商一定会将一个编号尽可能大的人送上去成为冠军。

易见，为了送一个人上去成为冠军，赞助商花费最少调整次数的方法，是只调整锦标赛树上从这个人到根的路径上，所有原本胜出者不是这个人的场次。

对于每一个人，锦标赛树上从其到根的每一场次，胜出者为子树内包含其的这一方则记为 $1$，否则记为 $0$，将这样的每一场次的情况按顺序连成一个二进制数，作为这个人的属性值。

可以看出，这个属性值有如下性质：

- 每一个人的属性值都是唯一的，所有人的属性值遍历 $[0,2^n) \cap \mathbb{Z}$；

- 赞助商想要送一个人上去成为冠军，最少需要的调整次数是这个人属性值二进制表示中 $0$ 的个数。

从而，所有属性值二进制表示中 $0$ 的个数小于等于 $k$ 的人，都可以成为冠军。赞助商一定会从这些人中选出编号最大的送上去成为冠军，我们要让成为冠军的人编号尽可能小，即求最小可能的最大编号，即为属性值二进制表示中 $0$ 的个数小于等于 $k$ 的人数。

这个人数，即

$$\sum_{i=0}^{\min(n,k)}\binom{n}{i}$$

容易做到 $O(\min(n,k))$ 的时间复杂度。

---

## 作者：zsseg (赞：3)

### Solution:

考虑对每个点进行编号，其二进制第 $i$ 位代表其 $i-1$ 级祖先是否获胜，获胜为 $0$ ，否则为 $1$，如下所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/lsjpb354.png)

显然，我们可以看出，编号为 $j$ 的节点要想成为胜利者，需要改变 $\text{popcount(j)}$ 次结果，那么，第 $k$ 次修改能获得的贡献就是 $\sum\limits_{i=0}^{2^n-1}[\text{popcount}(i)=k]$。

考虑到，一个 $n$ 位二进制数若有 $k$ 个 $1$，则其有 $C_n^k$ 种取值。所以，贡献可以转化为 $C_n^k$。 根据贪心，改变所需次数少的要分配更小的节点，所以 改变 $k$ 条边所需节点数就为 $\sum\limits_{i=0}^kC_n^i$，这也就是答案。

所以，我们只要从 $C_n^0$ 到 $C_n^k$ 递推，再累加结果就可以了，复杂度线性。

注意当 $k>n$ 时答案是 $2^n$，需要进行特判。

### Code(仅核心代码):

```cpp
const ll mod=1e9+7;
ll Tra[1000010];
ll ans;
inline ll qmod(ll x,ll y){
	ll A=1;
	while(y){
		if(y&1)A*=x,A%=mod;
		x=x*x%mod;
		y>>=1;
	}
	return A;
}
inline ll ylsqm(ll a,ll b){
	return (a*qmod(b,mod-2))%mod;//费马小定理求逆元
}
int main(){
	Tra[0]=1;
	if(k>n)k=n;//特判
	f(i,1,n)Tra[i]=ylsqm(Tra[i-1]*(n-i+1)%mod,i);//线性求组合数
	f(i,0,k)ans=(ans+Tra[i])%mod;
	write(ans);
	return 0;
}
```


---

## 作者：fast_photon (赞：2)

**0. 前言**  
重在思路，不在代码。   
前置知识：逆元

**1. 分析**  
赞助商修改的 $k$ 次比赛结果可以是任意的，但是问的是最坏情况，也就是尽可能让编号大的获胜。如果想让一个人获胜，只需要把他所有的比赛全都调成赢即可。
>注意，打败他的人在打败他之后进行的场次赢的计入他的胜利中，就比如下图：6 号位被 5 号位打败，然后 5 号位打败 7 号位，接着 1 号位打败 5 号位，那么就是 6 号位算是赢了一场（5 打败 1）。因为如果让 6 打败 5 的话，因为预先设定的是 5 6 之间的胜者打败了 7 8 之间的胜者，所以如果能打败一个人就能抢走他这场比赛后应有的全部的胜利场次。

如果他输了 $x<k$ 场，那么赞助商就可以让他胜出。  
![](https://cdn.luogu.com.cn/upload/image_hosting/aql66hsj.png)  
蓝色=赢，黑色=输，数字仅表示位置不表示编号  

如果赞助商想让 1 号位的人赢，就需要 $k\ge 0$。而 2,3,5 号位需要 $k\ge 1$。  
如果 $k=1$，那么有四个人永远都不会最终胜出，就可以把编号最大的 5 6 7 8 排入其中，所以最终结果是 4。而可能胜出的人分别赢了 $0,1,\dots,k$ 场，相当于在每个人的 $n$ 场里面选择**不超过** $k$ 场作为赢的，总的方案数就是答案。如果恰好选择 $i$ 场，那么这部分的结果将是 $C_n^i$。  
而根据公式，$C_n^i=C_n^{i+1}\times(i+1)\div(n-i)$，可以通过预处理逆元 $O(n)$ 预处理组合数。最终时间复杂度 $O(n)$。
```cpp
#include<iostream>
#include<cstdio>
#define maxn 100005
#define mod 1000000007

using namespace std;

long long n, k, inv[maxn], C[maxn], ans;

long long qpow(int p, int q) {
	if(q == 0) return 1ll;
	if(q == 1) return p;
	long long kkk = qpow(p, q >> 1);
	return kkk * kkk % mod * ((q & 1) ? p : 1ll) % mod;
} //就是用来计算2的幂的，也可以用每次左移1取模的方式

int main() {
	scanf("%lld %lld", &n, &k);
	inv[1] = 1;
	for(int i = 2; i <= n; i++) {
		inv[i] = (mod - mod / i) * inv[mod % i] % mod;
	}
	C[n] = 1;
	for(int i = n - 1; i >= 0; i--) {
		C[i] = C[i + 1] * (i + 1) % mod * inv[n - i] % mod;//预处理组合数
	}
	for(int i = n; i > k; i--) {//这里是因为之前有过多次组合数带取模正向枚举结果k>n的然后炸飞的经历，已经养成这样的习惯了
		ans += C[i];
		ans %= mod;
	}
	cout << (qpow(2, n) - ans + mod) % mod << endl;//减完之后可能是负的，所以要加一个mod再取模
}
```

---

## 作者：hank0402 (赞：1)

注意到有 $C_n^x$ 个人会输 $x$ 场，而第二个人可以改到第一名的人输掉的场次一定小于等于 $k$，所以第二个人会选 $S=\sum_{x\leq k} C_n^x$ 个人中编号最大的作为答案。为了使这个最大的编号最小，我们把 $1\sim S$ 填入这 $S$ 个位置中，所以答案就是 $S$。

注意特判 $k\ge n$ 的情况。

```cpp
#include <bits/stdc++.h>
using namespace std;
template <typename T> inline void rd(T &x){
    x = 0; bool f = true; char ch = getchar();
    while(ch < '0' || ch > '9'){ if(ch == '-') f = false; ch = getchar();}
    while(ch >= '0' && ch <= '9'){ x = (x << 1) + (x << 3) + (ch ^ '0'); ch = getchar();}
    if(!f) x = -x;
}
template <typename T, typename ...Args> inline void rd(T &x, Args &...args){ rd(x); rd(args...);}
#define int long long
const int N = 1e5 + 10, mod = 1e9 + 7;
int n, k, fac[N], inv[N];
int qpow(int a, int b = mod - 2)
{
    int res = 1;
    while (b)
    {
        if (b & 1)
            res = res * a % mod;
        a = a * a % mod, b >>= 1;
    }
    return res;
}
int choose(int n, int m)
{
    return fac[n] * inv[m] % mod * inv[n - m];
}
signed main() {
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    fac[0] = 1;
    for (int i = 1; i <= 100000; ++i)
        fac[i] = fac[i - 1] * i % mod;
    inv[100000] = qpow(fac[100000]);
    for (int i = 99999; i >= 0; --i)
        inv[i] = inv[i + 1] * (i + 1) % mod;
    rd(n, k);
    int ans = 0;
    for (int i = 0; i <= min(n, k); ++i)
        ans = (ans + choose(n, i)) % mod;
    cout << ans;
    return 0;
}
/*
注意到：n取x 输 x场
所以把一个数提到最后需要输<=k场，第二个人肯定把能提上来的最大值提上来，所以ans=输0场+输1场+...+输k场
*/
```

---

## 作者：氧少Kevin (赞：0)

# CF1717D - Madoka and The Corruption Scheme - 组合计数,思维转化

## 题意
给出一棵完全二叉树的层数 $n(1\leq n\leq 10^5)$，这棵二叉树有 $2^n$ 个叶子结点，代表初始时有 $2^n$ 个选手进行 $n$ 次比赛，胜出者进入下一轮，最终有 $1$ 个选手（根结点）获得最终胜利。

你可以随意确定二叉树的每个叶子节点的顺序，也可以随意确定每轮比赛谁赢谁输。

在你确定了这些以后，另一个人可以改变每轮比赛的输赢情况，最多改变 $k(1\leq k\leq \min(2^n,10^9))$ 轮比赛的输赢情况。

问：你能确保获得最终胜利的人的编号的最小值，答案对 $10^9+7$ 取模。

## 思路

不妨假设，**每次比赛均选择靠左侧的选手赢**，然后我们根据有机会的选手

假设 $n=5$
若改变最多 $0$ 场比赛的输赢情况，那么有 $1$ 个结点有机会走到最后

若改变最多 $1$ 场比赛的输赢情况，那么有 $1+5$ 个结点有机会走到最后

若改变最多 $2$ 场比赛的输赢情况，那么有 $1+5+1+2+3+4+5$ 个结点有机会走到最后。

可以发现：
- 只要更改的那场比赛直通根结点，那么就能让一个新的叶子结点成为有机会胜利的结点。
- 我们从上到下依次修改，能发现可以修改的比赛是唯一的。
- 有多少种不同的、合法的修改方案（不修改也算一种方案），那么就有多少个不同的叶子结点有机会胜利。

我们得出：从上到下修改比赛结果，恰好修改 $k$ 次，那么有 $\complement_n^k$ 种方案，每一种方案都会造成一个结点有机会成为胜利的结点，因此有恰好 $\complement_n^k$ 个叶子结点有机会胜利。

答案就是 $\sum_{i=0}^{\min(n,k)}\complement_n^i$。

---

## 作者：Plozia (赞：0)

宣传博客 $\to$ [link](https://www.cnblogs.com/Plozia/p/16659665.html)

首先注意到我们同一层不可能会修改多次比赛结果，因为 Sponsors 一定会定准一个目标然后修改结果，据此 $k>n$ 可以视作 $k=n$。

因此某个叶子如果被选为冠军，那么根节点到叶子节点这条路上的边一定都被选中了，而如果某个叶子节点到根的路径上有小于等于 $k$ 条边没有被选中，那么这个点可能会被 Sponsors 选为冠军，因此我们要让这些点编号都小，设答案为 $ans$ 那么这些点的编号应为 $[1,ans]$。

考虑会有多少点有小于等于 $k$ 条边没被选中？枚举 $i$ 表示某叶子节点到根节点路径上有 $i$ 条边没有被选中，那么这类叶子节点个数就是 $C_{n}^{i}$，但是至多只能修改 $k$ 次结果，因此最终答案就是 $\sum_{i=1}^{\min(n,k)}C_{n}^{i}$。

GitHub：[CodeBase-of-Plozia](https://github.com/Plozia/CodeBase-of-Plozia/blob/main/%E6%9D%82%E9%A1%B9/%E6%80%9D%E7%BB%B4%2B%E6%9E%84%E9%80%A0%2B%E4%BA%A4%E4%BA%92/CF1717D%20Madoka%20and%20The%20Corruption%20Scheme.cpp)

Code：

```cpp
/*
========= Plozia =========
	Author:Plozia
	Problem:CF1717D Madoka and The Corruption Scheme
	Date:2022/9/5
========= Plozia =========
*/

#include <bits/stdc++.h>
typedef long long LL;

const int MAXN = 1e5 + 5;
const LL P = 1e9 + 7;
int n, k;
LL fact[MAXN], inv[MAXN];

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return sum * fh;
}

LL ksm(LL a, LL b = P - 2, LL p = P)
{
	LL s = 1 % p;
	for (; b; b >>= 1, a = a * a % p)
		if (b & 1) s = s * a % p;
	return s;
}

int main()
{
	n = Read(), k = Read(); k = std::min(n, k);
	fact[0] = 1; for (int i = 1; i <= n; ++i) fact[i] = i * fact[i - 1] % P;
	for (int i = 0; i <= n; ++i) inv[i] = ksm(fact[i]);
	LL ans = 0;
	for (int i = 0; i <= k; ++i) ans = (ans + fact[n] * inv[i] % P * inv[n - i] % P) % P;
	printf("%lld\n", ans); return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：0)

# CF1717D 题解



## 思路分析

考虑对于每个人到根节点的路径，将每条边的胜负分别对应 $1/0$，得到一个长度为 $n$ 的二进制数，可以证明这样的 $2^n$ 个二进制数和树上 $2^n$ 个叶节点一一对应，不妨设 $f(x)$ 表示叶节点 $x$ 对应的二进制数。

我们考虑判断某个节点 $u$ 是否可以通过不超过 $k$ 调整使得 $u$ 最终获胜，即每次在 $f(u)$ 中修改一位的值，最终能否使 $f(u)$ 全部为一，不难发现这个问题等价于使得 $f(u)$ 中的 $0$ 的个数不超过 $k$，显然，最终状态就是所有这样的 $u$ 的最大值，注意到所有 $f$ 值中有 $x$ 个 $0$ 的有 $\dbinom nx$，即：
$$
\text{Answer}=\sum_{i=0}^{\min(n,k)} \dbinom ni
$$
时间复杂度 $\Theta(n)$。

## 代码呈现

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=2e5+1,MOD=1e9+7;
int fac[MAXN],inv[MAXN];
inline int ksm(int a,int b=MOD-2,int m=MOD) {
	int res=1;
	while(b) {
		if(b&1) res=res*a%m;
		a=a*a%m;
		b=b>>1;
	}
	return res;
}
inline int C(int n,int m) {
	if(m<0||m>n) return 0;
	if(m==0||m==n) return 1;
	return fac[n]*inv[m]%MOD*inv[n-m]%MOD;
} 
signed main() {
	fac[0]=inv[0]=1;
	for(int i=1;i<MAXN;++i) fac[i]=fac[i-1]*i%MOD,inv[i]=ksm(fac[i]);
	int n,k,res=0;
	scanf("%lld%lld",&n,&k);
	for(int i=0;i<=min(n,k);++i) res=(res+C(n,i))%MOD;
	printf("%lld\n",res);
	return 0;
}
```



---

## 作者：luogu_gza (赞：0)

绝世好题，一定要再做亿遍。

我们令只能操作 $k$ 次的人为 $B$，另外一人称为 $A$。

我们考虑把过程倒着来，看做是先 $B$ 操作 $k$ 次，然后 $A$ 任意操作。

$B$ 想让结果尽可能大，$A$ 则想让结果更小。

那么，一定是 $B$ 往右走 $k$ 步，$A$ 再一直往左走。

可以发现，这样走到的数就是

$$\sum_{i=0}^{k}C_{n}^{i}$$

显然的，当 $k \geq n$ 的时候，答案是 $2^n-1$。

这里借鉴了 [piaoyun](https://codeforces.com/contest/1717/submission/211703234) 的写法，使得连续组合数的计算更加方便。

[piaoyun写法](https://codeforces.com/contest/1717/submission/211777048)

[普通写法（我有点压行）](https://codeforces.com/contest/1717/submission/211777573)



---

