# Au Pont Rouge

## 题目描述

VK just opened its second HQ in St. Petersburg! Side of its office building has a huge string $ s $ written on its side. This part of the office is supposed to be split into $ m $ meeting rooms in such way that meeting room walls are strictly between letters on the building. Obviously, meeting rooms should not be of size 0, but can be as small as one letter wide. Each meeting room will be named after the substring of $ s $ written on its side.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1310C/3f4208069ef8a30005bed865124fbaec7ac1508a.png)For each possible arrangement of $ m $ meeting rooms we ordered a test meeting room label for the meeting room with lexicographically minimal name. When delivered, those labels got sorted backward lexicographically.

What is printed on $ k $ th label of the delivery?

## 说明/提示

In the first example, delivery consists of the labels "aba", "ab", "a".

In the second example, delivery consists of $ 3060 $ labels. The first label is "aupontrougevkof" and the last one is "a".

## 样例 #1

### 输入

```
4 2 1
abac```

### 输出

```
aba```

## 样例 #2

### 输入

```
19 5 1821
aupontrougevkoffice```

### 输出

```
au```

# 题解

## 作者：王鲲鹏 (赞：15)

$n \leq 1000$，可以考虑 $O(n^2)$ 做法（~~我也不会低于 $n^2$ 的~~ 

先把所有的子串排序，只需要考虑如何快速比较两个串：
* 定义 $lcp[i][j]$ 为 $s[i,n]$ 和 $s[j,n]$ 的最长公共前缀。可以 $n^2$ 递推出来。
* 比较两串 $s[l_1,r_1]$，$s[l_2,r_2]$ 时，判断lcp的长度是否大于串长，是则比较串长；否则比较lcp后一位。比较就是 $O(1)$ 的了。

于是我们得到了一个子串构成的数组 $A$，其中的串大小是（非严格）递增的。满足了单调性，考虑二分是哪个串。若当前二分到串 $S$，求划分后所有串都大于 $S$ 的划分方案数，判断是否大于等于 $k$ 。最后得到一个串 $S$，它是最大的串满足方案数大于等于 $k$，则方案是恰比 $S$ 大的那个子串。（请思考为什么不是 $S$ ？）

这题主要妙在dp上。

很自然地考虑设状态 $dp[i][j]$ 表示将 $s[1,i]$ 划分为 $j$ 段，每一段都大于 $S$ 的方案数。
显然有
$$
dp[i][j]=\sum_{(t \leq i)\wedge(s[t,i]>S)}dp[t-1][j-1]
$$
发现这是 $O(n^3)$ 的，无法接受。不好优化转移，所有优化状态。

我们思考问题的瓶颈在于字符串的大小更多被靠前的字符影响，而我们移动的是字符串的开头，这就导致我们必须每次都判断字符串大小。

所以重设状态 $dp[i][j]$ 表示 $s[i,n]$ 分为 $j$ 段的方案数：
$$
dp[i][j] = \sum_{(i\le t)\wedge(s[i,t]>S)}dp[t+1][j-1]
$$
固定了字符串开头为 $i$，移动结尾。

可以发现如果对于一个 $t$，满足 $s[i,t]>S$，那 $t+1$ 也一定大于。反之如果小于，那后面无论怎么加字符，还是会小于。
所以转化成一段后缀的形式，维护一下后缀和就好了。

第一个满足的 $t$ 可以通过 lcp数组求。还要判断是不是大于了 $|S|$。
于是转移变成 $O(1)$ 的。

细节看代码

```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long ll;
int const maxn = 1003;
int n = 0, m = 0;
ll k = 0;
char s[maxn];
int lcp[maxn][maxn];
struct Substring { int l, r; };
inline bool operator<(Substring const &lhs, Substring const &rhs) {
	int L = lcp[lhs.l][rhs.l];
	if (L >= lhs.r - lhs.l + 1 || L >= rhs.r - rhs.l + 1)
		return lhs.r - lhs.l + 1 < rhs.r - rhs.l + 1;
	return s[lhs.l + L] < s[rhs.l + L];
}
Substring a[maxn * maxn];
int cnt = 0;
ll dp[maxn][maxn], d[maxn][maxn]; // d 是dp的后缀和
bool check(int p) {
	memset(dp, 0, sizeof dp); memset(d, 0, sizeof d);
	d[n + 1][0] = 1;
	int stdLen = a[p].r - a[p].l + 1;
	for (int i = n; i >= 1; --i) {
		int t = std::min(stdLen, lcp[a[p].l][i]);
		if (t == stdLen || s[i + t] > s[a[p].l + t])
			for (int j = 1; j <= m; ++j)
				dp[i][j] = d[i + t + 1][j - 1];
		for (int j = 0; j <= m; ++j)
			d[i][j] = std::min(d[i + 1][j] + dp[i][j], k); // 爆 long long
	}
	return dp[1][m] >= k;
}
int main() {
	scanf("%d %d %lld", &n, &m, &k);
	scanf("%s", s + 1);
	for (int i = n; i >= 1; --i)
		for (int j = n; j >= 1; --j)
			lcp[i][j] = (s[i] == s[j] ? lcp[i + 1][j + 1] + 1 : 0);
	for (int i = 1; i <= n; ++i)
		for (int j = i; j <= n; ++j)
			a[++cnt] = Substring{i, j};
	sort(a + 1, a + cnt + 1);
	int l = 1, r = cnt;
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (check(mid)) l = mid + 1;
		else r = mid - 1;
	}
	for (int i = a[l].l; i <= a[l].r; ++i)
		putchar(s[i]);
	printf("\n");
	return 0;
}
```


---

## 作者：沉石鱼惊旋 (赞：6)

# 题目翻译

给定长度为 $n$ 的字符串 $s$，将其分成 $m$ 个非空子串。定义一种划分方式的『代表』，是这 $m$ 个子串种，字典序最小的那个子串。

求所有分割方式中，所有『代表』按字典序**从大到小**排的第 $k$ 个『代表』。

$1\leq n,m\leq 1000$，$1\leq k\leq 10^{18}$。

# 题目思路

首先可以套路性地二分答案。但是二分字符串不太好做，考虑先把所有子串给找出来排序。

直接截取 substr 显然复杂度是假的，子串个数无法缩减了，考虑在存储和比较字符串上做文章。

一个字符串可以用一个区间表示，比较大小就是找到第一个不同的问题。可以通过倒着 DP，$\mathcal O(n^2)$ 预处理 $\operatorname{lcp}$ 做。

之后这些子串只要存左右端点，排序复杂度 $\mathcal O(n^2 \log n)$。

考虑二分答案的 check 怎么实现。

一个显然的 DP 做法是设 $f_{i,j}$ 表示前 $i$ 个数分了 $j$ 段并且每一段的字典序都比二分的 $mid$ 大的方案数。

直接转移，枚举前一个分割位置。但是这样复杂度是 $\mathcal O(n^2 m)$ 的。具体实现可以看 [CF submission 281117038](https://codeforces.com/problemset/submission/1310/281117038)。

这样子看上去三个枚举都不好优化掉。

考虑不是『别人更新自己』，而是『自己更新别人』的转移方式。

枚举下一个分割位置，且满足目前位置到这个分割位置，组成的字符串，比二分的 $mid$ 大。

这时候我们发现这样有效的下一个分割位置，是一个后缀。

因为我们注意到字典序比较方式，如果 $s_i$ 是 $s_j$ 的前缀，必然存在 $s_i\leq s_j$。

也就是若 $s_{i+1\sim j}\geq mid$，则一定有 $s_{i+1\sim k}\geq mid(k\geq j)$。所以说有效的下一个分割位置，是一个后缀。

那么直接在第一个满足 $s_{i+1\sim j}\geq mid$ 的 $j$ 的位置打一个标记即可。

对标记做前缀和就是这一轮最新的 DP 值。

由于方案数很大会爆 long long。所以对于 $\geq 2\times 10^{18}$ 的 DP 值不妨都当成 $2\times 10^{18}$ 考虑。对最后答案是没有影响的。

# 完整代码

难度好像打错了，2800 感觉是乱评的，800 吧。

[CF submission 281119576](https://codeforces.com/contest/1310/submission/281119576)

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll inf = 2e18;
int n, m;
ll K;
string s;
int lcp[1020][1020];
struct substr
{
    int l, r;
    int len() { return r - l + 1; }
    string ss() { return s.substr(l, r - l + 1); }
} sub[1000020];
bool operator<(substr a, substr b)
{
    if (a.l == b.l)
        return a.r < b.r;
    int l = lcp[a.l][b.l];
    if (l >= a.len() || l >= b.len())
        return a.len() < b.len();
    return s[a.l + l] < s[b.l + l];
};
bool operator==(substr a, substr b) { return a.len() == b.len() && lcp[a.l][b.l] >= a.len(); };
bool operator<=(substr a, substr b) { return a < b || a == b; }
int tot;
ll f[1020][1020];
ll g[1020][1020];
void add(ll &x, ll y) { x = min(x + y, inf); }
bool check(substr mid)
{
    memset(f, 0, sizeof(f));
    memset(g, 0, sizeof(g));
    g[0][0] = 1;
    for (int i = 0; i <= n; i++)
    {
        if (i)
        {
            for (int j = 1; j <= m; j++)
                add(g[i][j], g[i - 1][j]);
        }
        for (int j = 0; j <= m; j++)
            f[i][j] = g[i][j];
        for (int k = i + 1; k <= n; k++)
        {
            if (mid <= (substr){i + 1, k})
            {
                for (int j = 1; j <= m; j++)
                    // add(f[k][j], f[i][j - 1]);
                    add(g[k][j], f[i][j - 1]);
                break;
            }
        }
    }
    // cout << mid.l << " " << mid.r << " " << mid.ss() << endl;
    // cout << f[n][m] << endl;
    return f[n][m] >= K;
}
int main()
{
    cin >> n >> m >> K >> s;
    s = ' ' + s;
    for (int i = n; i >= 1; i--)
    {
        for (int j = n; j >= 1; j--)
        {
            if (s[i] == s[j])
                lcp[i][j] = lcp[i + 1][j + 1] + 1;
        }
    }
    for (int l = 1; l <= n; l++)
    {
        for (int r = l; r <= n; r++)
            sub[++tot] = {l, r};
    }
    sort(sub + 1, sub + tot + 1);
    // for (int i = 1; i <= tot; i++)
    //     cout << sub[i].l << " " << sub[i].r << " " << sub[i].ss() << endl;
    // cout << endl;
    int L = 1, R = tot, ans = 0;
    while (L <= R)
    {
        int mid = L + R >> 1;
        if (check(sub[mid]))
            L = (ans = mid) + 1;
        else
            R = mid - 1;
    }
    cout << sub[ans].ss() << endl;
    return 0;
}
```

---

## 作者：David_Mercury (赞：3)

注：此题解仅为一个对 DP 优化方式的补充。所使用到的 DP 方程及一些变量的含义同其它题解。

其他题解都用到了“转化 DP 更新顺序”这一方法来优化 DP。如果我就是想不到该倒序 DP 怎么办？

接下来，让我们称 $s[t+1 \sim i] \ge S$ 的 $t$ 为 $i$ 的一个**决策**。称所有合法决策所在的集合为**决策集合**。

本质上，这个方法依旧使用了字典序的这一条性质：“**往一个字符串后添加字符，其字典序只增不减。**”那么，如果某个决策 $t$ 对于 $i$ 合法，那么它对于所有 $i+1 \sim n$ 也都是合法决策。也就是说，我们的**决策集合只增不减**。

于是不难构建如下代码：

1. 循环枚举 $i$。

2. 由于决策集合只增不减，任意 $i,j$ 都满足 $dp_{i,j} \ge dp_{i-1,j}$，故可以先令 $dp_{i,j} \leftarrow dp_{i-1,j}$。

3. 枚举 $1 \sim i-1$ 中**新增的合法决策**。也就是说，如果该决策在之前的 DP 过程中已经合法，或者说它现在还没有合法，我们都忽略它。然后再用 $O(m)$ 的复杂度暴力做一次 DP 转移即可。

复杂度分析：看上去有三重循环，但容易发现每个点 $t$ **最多加入一次决策集合**，故 $O(m)$ 的转移循环最多执行 $n$ 次，复杂度 $O(nm)$。总复杂度 $O(nm \log k)$。

代码：

```cpp
inline ll Check(int mid){
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)	f[i][j] = 0;
	for(int i = 0; i <= n; i++)	vst[i] = false;
	f[0][0] = 1;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++)	f[i][j] = f[i-1][j];
		for(int j = 0; j < i; j++){
			if(vst[j] or rk[j+1][i] < mid)	continue;
			vst[j] = true;
			for(int x = 1; x <= m; x++)	f[i][x] = min(k, f[i][x]+f[j][x-1]);
		}
	}
	return f[n][m];
}

```

---

## 作者：lupengheyyds (赞：2)

## 题面

给出一个长度为 $n$ 的字符串 $S$ 以及整数 $m,k$。

对于一个把 $S$ 分割成非空的 $m$ 段的一个方案，我们用这个方案中分割出的字典序最小的一个串代表这个分割方案。

现在把**所有分割方案对应的代表该方案的串**按字典序**从大到小**排序，求排序后的第 $k$ 个串。

$1\le m\le n\le 1000,1\le k\le 10^{18}$

## 题解

直接求代表元素不好求，可以考虑转化为判定，先将所有子串排序，二分判定大于串 $S$ 的划分方式有几个。

#### 首先是如何快速比较子串

令 $lcp_{x,y}=\operatorname{lcp}(s[x\sim n],s[y\sim n])$，有

$$
lcp_{x,y}=
\left\{\begin{aligned}
&lcp_{x+1,y+1}+1&&s_x=s_y\\
&0&&s_x\not=s_y
\end{aligned}\right.
$$

可以 $\mathcal O(n^2)$ 求出。

比较两个子串 $s[l_1\sim r_1]$ 与 $s[l_2\sim r_2]$。

- 若 $lcp_{l_1,l_2}\ge \min(r_1-l_1+1,r_2-l_2+1)$，直接比较子串长度。

- 否则比较 $s[l_1+lcp_{l_1,r_1}]$ 与 $s[l_2+lcp_{l_1,l_2}]$

代码如下：

```cpp
bool cmp(pa a,pa b){
    int lena=a.r-a.l+1,lenb=b.r-b.l+1,LCP=lcp[a.l][b.l];
    if(LCP>=lena||LCP>=lenb)return lena<lenb;
    return s[a.l+LCP]<s[b.l+LCP];
}
```

于是我们可以 $\mathcal O(1)$ 比较。

排序复杂度 $\mathcal O(n^2\log n)$

#### 接着如何求解划分个数

令 $dp_{i,j}$ 表示将 $s[1\sim i]$ 划分为 $j$ 段且每一段的字典序都大于 $S$ 的方案数，有：

$$
dp_{i,j}=\sum_{(t \leq i)\land(s[t\sim i]>S)}dp_{t-1,j-1}
$$

在每次转移的时候都需要枚举 $t$，复杂度 $\mathcal O(n^3)$。

我们知道字典序是从前往后比较的，但这个方程中却在不断移动左端点，使得我们不得不重新得到大小信息，于是可以考虑从后往前转移。

令 $dp_{i,j}$ 表示将 $s[i\sim n]$ 划分为 $j$ 段且每一段的字典序都大于 $S$ 的方案数，有：

$$
dp_{i,j}= \sum_{(t\ge i)\land(s[i\sim t]>S)}dp_{t+1,j-1}
$$

根据我们对于子串比较的分析，

$$
\exist w,s[i\sim w]>S\implies\forall t\in[w,n],s[w\sim n]>S
$$

这样就可以$\mathcal O(n^2)$ 转移了，加上二分，复杂度$\mathcal O(n^2\log n)$

总复杂度 $\mathcal O(n^2\log n)$

## 方法

- 预处理快速比较子串

- 更改枚举顺序——字典序尽量保证左端点定而右端点动

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pa;
const int NN=1005;
int n,m,lcp[NN][NN];
ll k,dp[NN][NN],hz[NN][NN];
char s[NN];
vector<pa> v;
#define l first
#define r second
bool cmp(pa a,pa b){
	int lena=a.r-a.l+1,lenb=b.r-b.l+1,LCP=lcp[a.l][b.l];
	if(LCP>=lena||LCP>=lenb)return lena<lenb;
	return s[a.l+LCP]<s[b.l+LCP];
}
bool Check(pa cv){
	memset(dp,0,sizeof dp);
	memset(hz,0,sizeof dp);
	hz[n+1][0]=dp[n+1][0]=1;
	int lent=cv.r-cv.l+1;
	for(int i=n;i>=1;i--){
		int len=min(lcp[i][cv.l],lent);
		if(len==lent||s[i+len]>s[cv.l+len])
			for(int j=1;j<=m;j++)dp[i][j]=hz[i+len+1][j-1];
		for(int j=0;j<=m;j++)hz[i][j]=min(dp[i][j]+hz[i+1][j],k);//爆longlong 
	}
	return dp[1][m]>=k;
}
int main(){
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++)cin>>s[i];
	for(int i=n;i>=1;i--)
		for(int j=n;j>=1;j--){
			if(s[i]==s[j])lcp[i][j]=lcp[i+1][j+1]+1;//else lcp[i][j]=0;
			if(i<=j)v.push_back({i,j});
		}
	sort(v.begin(),v.end(),cmp);
	int l=0,r=v.size()-1;
	while(l<r){
		int mid=l+r>>1;
		if(Check(v[mid]))l=mid+1;
		else r=mid;
	}
	for(int i=v[l].l;i<=v[l].r;i++)cout<<s[i];
	return 0;
}
```

---

## 作者：RainWetPeopleStart (赞：0)

vp 时降智不会做。

首先，发现答案必然是原串的一个子串，而且有可二分性，考虑二分答案。

首先，我们需要求子串的排名，考虑把所有子串扔到 Trie 树里，可以分析出 Trie 树的点数是 $O(n^2)$ 级别的，因此这一部分是 $O(n^2\Sigma)$ 的，下记 $rk_{i,j}$ 为 $s_{[i,j]}$ 的排名。

下面考虑 check 排名为 $r$ 的子串，即方案数和 $k$ 的大小关系，记 $f_{i,j}$ 表示前 $i$ 个字符划分为 $j$ 个子串的方案数，转移是 $f_{i,j}=\sum\limits_{k<i}f_{k,j-1}[rk_{k+1,i}\ge r]$，时间为 $O(n^3)$ 无法通过。

考虑优化，发现 $rk_{i,j}<rk_{i,j+1}$，所以在固定 $k+1$ 的情况下从小到大考虑 $i$，有 $[rk_{k+1,i}\ge r]$ 的变化次数是 $O(1)$ 的，所以右边的判定条件的总更新次数是 $O(n)$ 级别的，考虑动态维护 $sum_j=\sum\limits_{k<i}f_{k,j-1}[rk_{k+1,i}\ge r]$，对于判定条件的变化直接暴力更新所有的 $sum$，这样 DP 部分就可以 $O(n^2)$ 了。

方案数为 $f_{n,m}$，注意初值 $f_{0,0}=1$。

总复杂度 $O(n^2\Sigma+n^2\log n)$。

代码：


```cpp
#include<bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define se second
#define mk make_pair
#define ll long long
#define ull unsigned long long
#define uint unsigned int
#define bi __int128_t
#define lb(x) ((x)&(-(x)))
#define gp(i,j) (((i)>>(j-1))&1)
#define ppc __builtin_popcount
#define ctz __builtin_ctz
#define db long double
using namespace std;
const int N=1010,mod=1e9+7,iv2=(mod+1)/2;
const ll inf=2e18+10;
const db eps=1e-8;
bool Mbg;
void Add(int &a,int b){a+=b;if(a>=mod) a-=mod;}
void Sub(int &a,int b){a-=b;if(a<0) a+=mod;}
void Mul(int &a,int b){a=1ll*a*b%mod;}
int qp(int a,int b){
    int x=1;
    while(b){
        if(b&1) Mul(x,a);
        Mul(a,a);b>>=1;
    }return x;
}
ll f[N][N];
int n,m;ll k;
int rk[N][N];
bool tag[N];
bi sum[N];
struct Trie{
    int T[N*N][27],tot=1;
    vector<pii> vec[N*N];
    void ins(string s,int pl){
        int now=1,pr=pl;
        for(auto ch:s){
            if(!T[now][ch-'a'+1]) T[now][ch-'a'+1]=++tot;
            now=T[now][ch-'a'+1];
            vec[now].push_back(mk(pl,pr++));
        }
    }
    int rkc=0;
    void dfs(int id){
        for(auto ed:vec[id]){
            rk[ed.fi][ed.se]=++rkc;
        }
        for(int i=1;i<=26;i++){
            if(T[id][i]) dfs(T[id][i]);
        }
    }
}T;

void upd(int id,int op){
    for(int i=1;i<=m;i++){
        sum[i]+=op*f[id][i-1];
    }
}
ll dp(int nk){
    for(int i=0;i<=n;i++){
        for(int j=0;j<=m;j++){
            sum[j]=0;tag[i]=0;
            f[i][j]=0;
        }
    }f[0][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=i;j++){
            if(rk[j][i]<nk&&tag[j]){
                upd(j-1,-1);tag[j]=0;
            }else if(rk[j][i]>=nk&&!tag[j]){
                upd(j-1,1);tag[j]=1;
            }
        }
        for(int j=1;j<=m;j++){
            f[i][j]=min(sum[j],(bi)inf);
        }
    }return f[n][m];
}
string s;
void slv(){
    cin>>n>>m>>k;
    cin>>s;
    s=' '+s+' ';
    for(int i=1;i<=n;i++){
        string st="";
        for(int j=i;j<=n;j++) st+=s[j];
        T.ins(st,i);
    }T.dfs(1);
    int l=1,r=n*(n+1)/2;
    while(l<r){
        int mid=(l+r+1)/2;
        if(dp(mid)<k){
            r=mid-1;
        }else{
            l=mid;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++){
            if(rk[i][j]==l){
                for(int p=i;p<=j;p++) cout<<s[p];cout<<endl;
                return ;
            }
        }
    }
}
bool Med;
int main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int t=1;//cin>>t;
    while(t--) slv();
    cout.flush();
    cerr<<clock()*1.0/CLOCKS_PER_SEC<<' '<<(&Mbg-&Med)/1024.0/1024.0<<endl;
    return 0;
}
```

---

## 作者：一只绝帆 (赞：0)

跟 @mikefeng duel 到这题，写一发题解。

这个题我一开始思路直接拐到自动机上贪心了，似。

由于 $n\le 1000$，考虑把所有子串排序（可以 $\rm dfs$ 字典树来实现），然后二分一个子串 $[l,r]$，判断所有代表串字典序 $\ge s[l,r]$ 的串的个数是否 $\ge k$。

由于代表串是一个划分中最小的那个串，最小的串都 $\ge s[l,r]$ 说明所有串都 $\ge s[l,r]$，相当于求只能用到 $\ge s[l,r]$ 的串问能否划分整个串为 $m$ 个非空段。

发现性质：一个 $\ge s[l,r]$ 的串往后面任意添加字符仍然 $\ge s[l,r]$，所以我们从后往前 $\rm dp$，设 $f_{i,j}$ 表示已经划分了 $i$ 段，$j$ 是最左边那一段的左端点的方案数，则转移是从一个后缀转移而来。

每个 $i$ 作为左端点对应的最靠左的合法右端点 $s_i$ 可以对每个 $i$ 暴力挪动指针求出，然后使用后缀和优化：

$$f_{i,j}\gets \sum_{k>s_j}f_{i,k}$$

注意方案可能有特别多种，而我们只需要判断与 $k$ 的关系，所以我们可以使用 `long double` 或者做一次就与 $10^{18}$ 取 $\min$，这两种都要求我们不使用减法，所以上文中用后缀和而不是前缀和优化。

注意不要使用哈希，我们要用到所有的子串，极有可能发生生日悖论的哈希碰撞，我的随机模数双模哈希都死的很惨。

[代码](https://codeforces.com/contest/1310/submission/266207277)。

---

## 作者：Hypercube (赞：0)

中规中矩的一道 dp 题。

首先看到字典序，我们不难想到一个经典套路。我们可以尝试逐位确定字符串，然后进行判断。确定的时候可以进行二分，也可以按字典序从大到小枚举要填的字符。具体的判断方式就是在后面加上足够多的 `z`，计算比当前串字典序大的划分有多少个。若当前字母是字典序最小的且满足字典序比它大的划分不小于 $k$ 即合法。

然后考虑怎么计算字典序比当前串大的划分的个数。这个其实是容易 dp 解决的。直接做就有一个状态为 $O(n^2)$，转移为 $O(n)$ 的 dp。但容易发现字典序其实是有单调性的（即在当前串后面加一个字符字典序一定增加），所以转移其实是后缀加的形式，简单维护即可做到 $O(n^2)$。

这样做总复杂度大概是 $O(n^3)$ 的，而且带一个 $\log26$ 的常数，难以接受。

于是我们发现其实没有必要逐位确定答案，因为题目中答案的集合并不大，只有可能是原串的子串。于是可以直接排序之后二分。当然了，排序的部分利用 SA 那一套可以做到 $O(n^2 \log n)$，但写个二分加哈希也是可以的，虽然的确带两只 $\log$，但把串去重一下常数会小很多，可以通过。

有一个实现细节是 dp 的时候可能会出现 dp 值巨大的情况，这部分我的实现是将超过 $k$ 的 dp 值钦定为 -1，特判一下转移即可。

总时间复杂度 $O(n^2 \log^2 n)$。

代码很好写，但不怎么漂亮。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
inline ll read() {
	ll f=1,x=0;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-') f=-1;ch=getchar();}
	while(isdigit(ch)) {x=x*10+ch-48;ch=getchar();}
	return x*f;
}
const ll N=1003,p=998244353,inv27=480636170;
ll n,m,k,cnt,hsh[N],pw[N],ex[N],f[N][N],g[N][N];
string s;
struct SUB {
	int l,r;
}sub[N*N];
void init() {
	ll base=1;
	for(int i=1;i<=n;i++) hsh[i]=(hsh[i-1]+(s[i]-'a'+1)*base%p)%p,(base*=27ll)%=p;
    pw[0]=1;
	for(int i=1;i<=n;i++) pw[i]=pw[i-1]*inv27%p;
}
ll hs(int l,int r) {
	return (hsh[r]-hsh[l-1]+p)%p*pw[l-1]%p;
}
bool operator < (SUB a,SUB b) {
	int la=a.r-a.l+1,lb=b.r-b.l+1;
	if(la<=lb&&hs(a.l,a.r)==hs(b.l,b.l+la-1)) return 1;
    if(la>lb&&hs(a.l,a.l+lb-1)==hs(b.l,b.r)) return 0;
    if(s[a.l]!=s[b.l]) return s[a.l]<s[b.l];
    int l=1,r=min(la,lb),ans=-1;
    while(l<=r) {
    	int mid=(l+r)>>1;
    	if(hs(a.l,a.l+mid-1)==hs(b.l,b.l+mid-1)) ans=mid,l=mid+1;
    	else r=mid-1;
	}
	return s[a.l+ans]<s[b.l+ans];
}
bool operator == (SUB a,SUB b) {
    return hs(a.l,a.r)==hs(b.l,b.r);
}
unordered_map <ll,bool> mp;
int main() {
	n=read(),m=read(),k=read();
	cin>>s;
	s=" "+s;
	init();
	for(int i=1;i<=n;i++) 
		for(int j=i;j<=n;j++) {
			if(mp[hs(i,j)]) continue;
			sub[++cnt]=(SUB){i,j};
			mp[hs(i,j)]=true;
		}
	stable_sort(sub+1,sub+cnt+1);
	int l=1,r=cnt,ans=-1;
	while(l<=r) {
		int mid=(l+r)>>1;
		for(int i=1;i<=n;i++) {
			ex[i]=-1;
			for(int j=i;j<=n;j++) {
				if(sub[mid]<(SUB){i,j}||sub[mid]==(SUB){i,j}) {
					ex[i]=j;
					break;
				}
			}
		}
		for(int i=0;i<=n;i++) {
			for(int j=0;j<=i;j++) {
				f[i][j]=g[i][j]=0;
			}
		}
		f[0][0]=1;
		if(f[0][0]>=k) f[0][0]=-1;
		for(int i=0;i<=n;i++) {
			for(int j=0;j<=min(i,int(m));j++) {
				if(i) {
					if(g[i-1][j]==-1) g[i][j]=-1;
			    	else if(g[i][j]!=-1) {
			    		g[i][j]+=g[i-1][j];
			    		if(g[i][j]>=k) g[i][j]=-1;
			    	}
				}
				if(g[i][j]==-1) f[i][j]=-1;
				else if(f[i][j]!=-1) {
					f[i][j]+=g[i][j];
					if(f[i][j]>=k) f[i][j]=-1;
				}
				if(!f[i][j]||ex[i+1]==-1) continue;
				if(f[i][j]==-1) g[ex[i+1]][j+1]=-1;
				else {
					if(g[ex[i+1]][j+1]!=-1) {
						g[ex[i+1]][j+1]+=f[i][j];
						if(g[ex[i+1]][j+1]>=k) g[ex[i+1]][j+1]=-1;
					}
				}
			}
		}
		if(f[n][m]==-1) ans=mid,l=mid+1;
		else r=mid-1;
	}
	for(int i=sub[ans].l;i<=sub[ans].r;i++) cout<<s[i];
	cout<<'\n';
	return 0;
}

```


---

