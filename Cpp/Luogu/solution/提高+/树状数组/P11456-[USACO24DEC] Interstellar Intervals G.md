# [USACO24DEC] Interstellar Intervals G

## 题目描述

现在是公元 $3000$ 年，Bessie 成为了第一头进入太空的奶牛！在她穿越星际的旅程中，她发现了一条有 $N$（$2 \leq N \leq 5 \cdot 10^5$）个点的数轴，点的编号从 $1$ 到 $N$。所有点初始时都是白色的。她可以执行任意次以下操作。

选择一个数轴上的位置 $i$ 和一个正整数 $x$。然后，将区间 $[i, i + x - 1]$ 中的所有点涂成红色，区间 $[i + x, i + 2x - 1]$ 中的所有点涂成蓝色。所有选择的区间必须是不交的（即区间 $[i, i + 2x - 1]$ 中的点不能已经被涂成红色或蓝色）。同时，整个区间必须落在数轴内（即 $1 \leq i \leq i + 2x - 1 \leq N$）。
Farmer John 给了 Bessie 一个长度为 $N$ 的字符串 $s$，由字符 $\tt R$，$\tt B$ 和 $\tt X$ 组成。该字符串表示了 Farmer John 对每个点的颜色偏好：$s_i=\texttt{R}$ 表示第 $i$ 个点必须被涂成红色，$s_i = \texttt{B}$ 表示第 $i$ 个点必须被涂成蓝色，$s_i = \texttt{X}$ 表示第 $i$ 个点的颜色没有限制。

帮助 Bessie 计算满足 Farmer John 偏好的不同的数轴涂色方案的数量。两个涂色方案是不同的，当且仅当至少一个对应点的颜色不同。由于答案可能很大，输出答案模 $10^9+7$ 的余数。

## 说明/提示

样例 1 解释：

Bessie 可以选择 $i=1,x=1$（即将点 $1$ 涂成红色，点 $2$  涂成蓝色）以及 $i=3,x=2$（即将点 $3,4$ 涂成红色，点 $5,6$ 涂成蓝色）来得到涂色方案 $\tt RBRRBB$。

其他涂色方案有 $\tt{RRBBRB}$，$\tt{RBWWRB}$，$\tt{RRRBBB}$ 和 $\tt{RBRBRB}$。

样例 2 解释：

六种涂色方案为 $\tt{WWRBWW}$，$\tt{WWRBRB}$，$\tt{WRRBBW}$，$\tt{RBRBWW}$，$\tt{RBRBRB}$ 和 $\tt{RRRBBB}$。

- 测试点 $4$：$N\leq 500$。
- 测试点 $5\sim 6$：$N\leq 10^4$。
- 测试点 $7\sim 13$：$s$ 中至多 $100$ 个字符不为 $\tt{X}$。
- 测试点 $14\sim 23$：没有额外限制。

## 样例 #1

### 输入

```
6
RXXXXB```

### 输出

```
5```

## 样例 #2

### 输入

```
6
XXRBXX```

### 输出

```
6```

## 样例 #3

### 输入

```
12
XBXXXXRXRBXX```

### 输出

```
18```

# 题解

## 作者：lalaouye (赞：19)

首先这道题肯定可以设 $f_i$ 表示前 $i$ 位的答案，转移就是枚举一段红加一段蓝，并 check 能否转移，这样可以简单做到 $\mathcal{O}(n^2)$。而对于转移怎么 check 呢？首先红色点对于无解的影响是好处理的，问题是蓝点怎么处理。我们考虑对于所有蓝点独立处理不能转移的段，那么不能转移的段即为所有蓝点不能处理的段的并。

我们注意到 $i$ 每往后一次，每个蓝点的影响就会往前扩展一位。那么这个东西显然可以均摊处理，我们维护所有不合法段的左端点，如果左端点到了已经不合法的点就删除这个左端点，因为它没有存在的必要。然后用树状数组维护所有 $f_j$ 的贡献，每扩展到一位就减去这一位的 dp 值即可。

时间复杂度 $\mathcal{O}(n\log n)$，$\log n$ 来自于树状数组，感觉 $n$ 开到 $5\times 10^6$ 不是问题！

代码：


```cpp
class BIT {
  public:
    int c[N];
    int lb (int x) {
      return x & -x;
    }
    void upd (int x, int y) {
      ++ x;
      for (; x <= n; x += lb (x)) c[x] += y;
    }
    int qry (int x) {
      int ret = 0; ++ x;
      for (; x; x -= lb (x)) ret += c[x];
      return ret;
    }
    int qry (int l, int r) { return qry (r) - qry (l - 1); }
} t[2];
void insert (int x) {
  nxt[pre[n + 1]] = x;
  pre[x] = pre[n + 1];
  pre[n + 1] = x;
  nxt[x] = n + 1;
}
void erase (int x) {
  pre[nxt[x]] = pre[x];
  nxt[pre[x]] = nxt[x];
}
int32_t main () {
  n = rd ();
  nxt[0] = n + 1, pre[n + 1] = 0;
  scanf ("%s", s + 1);
  int l1 = 0;
  f[0] = 1;
  t[0].upd (0, 1);
  rep (i, 1, n) {
    for (int x = nxt[0]; x <= n; x = nxt[x]) {
      del[now[x]] = 1;
      t[now[x] & 1].upd (now[x], - f[now[x] - 1]);
    }
    for (int x = nxt[0]; x <= n; x = nxt[x]) {
      if (del[-- now[x]] || now[x] < 1) erase (x);
    }
    if (s[i] == 'R') l1 = i;
    else if (s[i] == 'B' && ! del[i]) {
      insert (i), now[i] = i;
    }
    f[i] = t[i & 1 ^ 1].qry (max (1ll, l1 * 2 - i + 1), i) % P;
    if (s[i] == 'X') f[i] = (f[i] + f[i - 1]) % P;
    t[i & 1].upd (i, f[i - 1]);
  }
  cout << (f[n] + P) % P;
}
```

---

## 作者：EatBread (赞：12)

校内的模拟赛的题，赛时没切出来，看了题解才过，发现题解的大佬都没详细讲，于是来发一篇。

首先一个朴素的 dp，设 $f_i$ 表示前 $i$ 位的答案，然后可以枚举一个 $j$ 判断是否可以从 $j$ 转移过来，也就是说： $j+1$ 到 $i$ 的这一段可以通过**一次**染色**全部**染上颜色，如果可以，$f_i=f_i+f_{j-1}$。

这是显而易见可以 $O(n^2)$ 实现的，但过不去，所以我们考虑优化。

首先我们发现，如果一段区间是可以染色的（设这段区间左端点为 $l$，右端点为 $r$），仅当：
 - $len=r-l+1$ 是偶数。
 - 离 $l$ 最近的蓝点为 $x$，则 $r-x+1<len\div2$，因为蓝点最多只能占一半。
 - 离 $r$ 最近的红点为 $y$，则 $y-l+1<len\div2$，原因同上。
 
那么我们根据这几个条件，来依次筛选出一些不合法的踢出去，然后即可得出答案。

首先需要**两个**树状数组（分开统计，第一个条件），统计合法的答案。

然后，离 $r$ 最近的红点很好得出，判断的时候也很好算，不讲。

组后看离 $l$ 最近的蓝点，找到的原理很简单，不讲，程序长这样：`if(s[i]=='B')for(; bl<=i; bl++)`自己理解一下，此时 $i$ 是对于 $bl$ 来说最近的蓝点。

所以我们可以提前求出当某一个点作为 $l$ 的时候，它在哪一个 $r$ 点的情况下会失效（也就是 $r-x+1\ge  len\div2$）。

那很显然，如果对于一个 $l$ ，它在某一个 $r$ 时不合法，那么它在 $r+1$ 也肯定不合法，所以我们可以从 $r$ 起，永远的将它从树状数组中删除，那也就是说，现在第三个条件已经不存在了，所以我们直接算出符合第二个条件的值就行了。

复杂度 $O(n \log n)$，顺带提一嘴，这题跟[P2779](https://www.luogu.com.cn/problem/P2779)几乎一样。

放个程序，挺短的：

```
#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define lowbit(x) (x&(-x))
const int N=5e5+5,mod=1e9+7;
int f[N],rl,bl=1,be[N],n;
int q[N],h,t;
struct str{
	int s[N];
	void add(int x,int a){for(int i=x; i<=n; i+=lowbit(i))s[i]=(s[i]+a)%mod;}
	int ask(int x){int cnt=0;for(int i=x; i; i-=lowbit(i))cnt=(cnt+s[i])%mod;return cnt;}
}T[2];
char s[N];
vector<int>e[N*2];
signed main(){
	cin>>n,f[0]=1;
	scanf("%s",s+1);
	for(int i=1; i<=n; i++){
		if(s[i]=='X')f[i]=f[i-1];//这一位可以不填 
		if(s[i]=='R')rl=i;//离 r 最近的红点 
		if(s[i]=='B')for(; bl<=i; bl++)e[i+i-bl].push_back(bl);//算出这个 l 在哪个 r 时失效并添加 
		for(auto v:e[i])T[v&1].add(v,-f[v-1]);//删掉失效的点 
		int l=max(rl-(i-rl)+1,1ll);//符合第二个条件的 
		f[i]+=(T[(i+1)&1].ask(i)-T[(i+1)&1].ask(l-1)+mod)%mod;
		f[i]%=mod;
		T[i&1].add(i,f[i-1]);
	}
	cout<<f[n];
	return 0;
}
```

---

## 作者：Eddie08012025 (赞：10)

### 提供一种比较好想的做法
用 $dp_i$ 表示考虑前 $i$ 位的方案数。
1. $s_i$ 为 `R`，方案数为 $0$。
2. $s_i$ 为 `X`，这一位可以不染色，$dp_i=dp_i+dp_{i-1}$。
3. 一个区间 $[j,i](j\le i)$ 可以合法染色，$dp_i=dp_i+dp_{j-1}$。

对于一个区间 $[j,i]$，只有满足以下条件才可以合法染色：（借鉴了一下另外一篇题解）
1. $i-j+1$ 为偶数，即区间内数的个数为偶数，令 $len=i-j+1$。
2. 离 $j$ 最近的蓝点为 $x$，则 $i−x+1\le\frac{len}{2}$，因为蓝点最多只能占一半。
3. 离 $i$ 最近的红点为 $y$，则 $y−j+1\le\frac{len}{2}$，原因同上。

这样，显然可以 $O(n^2)$ 的去完成，对于离 $l$ 最近的蓝点与离 $r$ 最近的红点可以预处理。
```cpp
#include<bits/stdc++.h> 
using namespace std;
#define int long long
int n,dp[500005],lst[500005],nxt[500005],a[500005][5],mod=1e9+7;
string s;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>s;
    s=" "+s;
    dp[0]=1;
    int te=0;
    //处理离 j 最近的蓝点与离 i 最近的红点
    for(int i=1;i<=n;i++){
    	if(s[i]=='R')te=i;
		lst[i]=te;
	}te=n+1;
	for(int i=n;i>=1;i--){
		if(s[i]=='B')te=i;
		nxt[i]=te;
	}for(int i=1;i<=n;i++){
		if(s[i]=='R')dp[i]=0;
		else {
			if(s[i]=='X')dp[i]+=dp[i-1];
			for(int j=i-1;j>=1;j--){
				if((i-j+1)%2==1)continue;
				int a1=i-nxt[j]+1,b1=lst[i]-j+1,c1=(i-j+1)/2;
				if(a1<=c1&&b1<=c1)dp[i]+=dp[j-1],dp[i]%=mod;
			}
		}
	}cout<<dp[n];
    return 0;
}
```
尝试优化，对以上 $i−x+1\le\frac{len}{2}$ 与 $y−j+1\le\frac{len}{2}$ 变形得：（离 $j$ 最近的蓝点为 $x$，离 $i$ 最近的红点为 $y$）

$i+1\le 2\times x-j$ 与 $2\times y-i+1\le j$。

考虑用线段树维护第二个式子，在线段树上的 $[i,i]$ 上存储 $dp_{i-1}$，维护区间和。

需要两个线段树，一个来存储 $i$ 为奇数时，一个来存储 $i$ 为偶数时，在查询时若 $i$ 为奇数，则查询存储偶数的线段树，否则查询存储奇数的线段树，这是为了保证 $len$ 为偶数。

对于枚举到的每一个 $i$，
1. 将所有的不满足第一个式子的 $j$ 在线段树上删去，即赋值为 $0$，因为这个点对后面的答案产生不了贡献，找出这些 $j$ 可以用数组排序或数据结构解决。
2. $s_i$ 为 `R`，方案数为 $0$，直接跳到第五步。
3. $s_i$ 为 `X`，这一位可以不染色，$dp_i=dp_i+dp_{i-1}$。
4. 令 $a$ 为 $[\max(2\times y-i+1,1),i-1]$ 这个区间的区间和，则 $dp_i=dp_i+a$，注意查询正确的线段树。
5. 在正确的线段树上将 $[i,i]$ 赋值为 $dp_{i-1}$。
   
思路大致如此，代码：
```cpp
#include<bits/stdc++.h> 
#define mid (l+r)/2
using namespace std;
#define int long long
int n,dp[500005],lst[500005],nxt[500005],a[500005][5],sum[5000005],sum2[5000005],mod=1e9+7;
priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>q;
string s;
void up(int x){
	sum[x]=sum[x*2]+sum[x*2+1];
	sum[x]%=mod;
	sum2[x]=sum2[x*2]+sum2[x*2+1];
	sum2[x]%=mod;
}//p即为两个线段树的编号，维护奇数的为0，维护偶数的为1
void modify(int x,int l,int r,int l1,int r1,int k,int p){
	if(l>r1||r<l1)return ;
	if(l>=l1&&r<=r1){
		if(!p)sum[x]=k;
		else sum2[x]=k;
		return ;
	}modify(x*2,l,mid,l1,r1,k,p);
	modify(x*2+1,mid+1,r,l1,r1,k,p);
	up(x);
}int xun(int x,int l,int r,int l1,int r1,int p){
	if(l>r1||r<l1)return 0;
	if(l>=l1&&r<=r1)return p?sum2[x]:sum[x];
	return (xun(x*2,l,mid,l1,r1,p)+xun(x*2+1,mid+1,r,l1,r1,p))%mod;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>s;
    s=" "+s;
    dp[0]=1;
    int te=0,no=1;
    for(int i=1;i<=n;i++){
    	if(s[i]=='R')te=i;
		lst[i]=te;
	}te=n+1;
	for(int i=n;i>=1;i--){
		if(s[i]=='B')te=i;	
		nxt[i]=te;
	}for(int i=1;i<=n;i++){
		if(s[i]=='R'){
			dp[i]=0;
			if(i%2==1){
				modify(1,1,n,i,i,dp[i-1],0);
			}else {
				modify(1,1,n,i,i,dp[i-1],1);
			}
		}else {
			if(s[i]=='X')dp[i]+=dp[i-1];
			while(!q.empty()){//我用了优先队列来删除没有用的点，a存储的是式子中的2*x-j
				int a=q.top().first,b=q.top().second;
				if(i+1>a)modify(1,1,n,b,b,0,(b%2==1?0:1)),q.pop();
				else break; 
			}if(i%2==1){
				dp[i]+=xun(1,1,n,max(2*lst[i]-i+1,1ll),i-1,1);
				dp[i]%mod;
				modify(1,1,n,i,i,dp[i-1],0);
			}else {
				dp[i]+=xun(1,1,n,max(2*lst[i]-i+1,1ll),i-1,0);
				dp[i]%=mod;
				modify(1,1,n,i,i,dp[i-1],1);
			}
		}q.push({2*nxt[i]-i,i}); 
	}cout<<dp[n];
    return 0;
}
```

---

## 作者：Louis_lxy (赞：7)

**提供一种可以把本题变成绿题来做的单 $\log$ 做法。**

前置知识：树状数组区间加贡献。

首先，我们注意到对于一个位置 $i$，如果它要延伸出 $x$ 个位置为 `R`，那么我们需要保证这 $x$ 个位置上的字符不是 `B`，这 $x$ 个位置后面的 $x$ 个位置不是 `R`（感性理解一下吧，作者的语文真不好）。

然后我们发现如果填表 dp 好像不好处理限制条件（当然也好处理，只是因为本人最开始脑抽以为刷表每一个位置可以延伸的距离是一段区间然后就以为更好做），反正我们考虑刷表做。

注意到如果我们暴力刷表，我们会比较讨厌 `R`，例如 `RXXRXXXX` 这种情况，我们发现我们能涂 `RX`，但不能涂 `RXXR`这段区间，但是我们又能涂 `RXXRXXXX`这段区间，于是就会导致涂得长度不是一段区间，但是事实上，我们可能涂的区间数量是 $O(\log n)$ 的，于是我们可以在 $O(n\log n)$ 的时间复杂度下暴力解决这个问题。

下面给出每个位置可能涂的长度的区间数量是 $O(\log n)$ 的证明：注意到如果我们有一个字符串 `R...R...R` 这样的（`...` 代表的是一段 `X` 或 `R` 组成的字符串），且满足前两个 `R` 之间的距离是大于后两个 `R` 之间的距离减一的，那么我们直接走到前两个 `R` 之间距离的两倍的区间中最后一个 `R` 的位置上判断有没有贡献即可，中间的显然没有贡献。否则我们就直接计算完走到第二个 `R` 的右边一个 `R` 即可，这样我们保证每两次这样的操作就会增加至少一倍距离，于是总的操作次数自然是 $O(\log n)$ 的。

哦对了，`X` 可以当做 `R` 处理，但是如果一个位置是 `X` 的话，它的 dp 值应当是它到前一个不是 `X` 的字符上的 dp 值的和（包括它和前一个不是 `X` 的字符上的 dp 值）。

另外 `R...B...R` 这种情况也要考虑，注意到如果我们一旦遇到这种情况，可以立马退出处理 `R...R...R` 的情况的循环，因为之后一定没有贡献了，这种情况也比较好处理，读者不妨自己推导。

最后说一件事情，树状数组区间加是要分奇偶的。

然后就做完了，码量中等（但是相较于本题线性或者单 $\log$ 略大），因此给个示例。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 5e5 + 10, mod = 1e9 + 7;
int n, pr[N], pb[N], sr[N], sb[N], sum[N];
char c[N];

struct BIT {
	int f[N / 2];
	void add(int x, int k) {
		for (; x <= n / 2 + 1; x += x & -x) {
			f[x] += k;
			if (f[x] >= mod) f[x] -= mod; 
		}
	}
	int qry(int x) { int res = 0; for (; x; x -= x & -x) res += f[x]; return res % mod; }
} tr[2];

signed main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> c[i];
	for (int i = 0; i <= n; ++i) {
		if (c[i] == 'B') pb[i + 1] = i, pr[i + 1] = pr[i];
		else if (c[i] == 'R') pb[i + 1] = pb[i], pr[i + 1] = i;
		else pb[i + 1] = pb[i], pr[i + 1] = pr[i];
	}
	sr[n + 1] = sb[n + 1] = n + 1;
	for (int i = n + 1; i >= 1; --i) {
		if (c[i] == 'B') sb[i - 1] = i, sr[i - 1] = sr[i];
		else if (c[i] == 'R') sb[i - 1] = sb[i], sr[i - 1] = i;
		else sb[i - 1] = sb[i], sr[i - 1] = sr[i];
	}
	tr[0].add(1, 1), tr[0].add(2, -1);
	for (int i = 0; i < n; ++i) {
		int id = i / 2 + 1, x = tr[i & 1].qry(id);
		sum[i] = (sum[i - 1] + x) % mod;
		if (c[i] == 'X') {
			if (max(pr[i], pb[i]) - 1 < 0) x = sum[i];
			else x = (sum[i] - sum[max(pr[i], pb[i]) - 1] + mod) % mod;
		}
		if (c[i + 1] == 'B') continue;
		int p = i + 1, flag = 0;
		while (p < n) {
			int l = p - i, r = sr[p] - p - 1;
			if (p + l > n) break;
			if (l > r) { p = pr[p + l + 1]; continue; }
			if (p > sb[i]) break;
			if (sr[p] > sb[i]) { flag = 1; break; }
			r = (sr[p] - i - 1) / 2;
			tr[i & 1].add(id + l, x), tr[i & 1].add(id + r + 1, -x);
			p = sr[p];
		}
		if (flag) {
			int l = max(1ll, pr[sb[i]] - i), r = min(sb[i] - i - 1, (sr[sb[i]] - i - 1) / 2);
			if (l > r) continue;
			tr[i & 1].add(id + l, x), tr[i & 1].add(id + r + 1, -x);
		}
	}
	int res = tr[n & 1].qry(n / 2 + 1);
	if (c[n] == 'X') res = res + sum[n - 1] - sum[max(pr[n], pb[n]) - 1];
	cout << (res % mod + mod) % mod;
	return 0;
}
```

后记：应该不会有人跟作者一样脑抽写树状数组变成双 $\log$ 吧。事实上这题直接差分即可，可以做到单 $\log$。

贴一个单 $\log$ 的示例吧。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 5e5 + 10, mod = 1e9 + 7;
int n, pr[N], pb[N], sr[N], sb[N], sum[N], s[2][N / 2];
char c[N];

signed main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> c[i];
	for (int i = 0; i <= n; ++i) {
		if (c[i] == 'B') pb[i + 1] = i, pr[i + 1] = pr[i];
		else if (c[i] == 'R') pb[i + 1] = pb[i], pr[i + 1] = i;
		else pb[i + 1] = pb[i], pr[i + 1] = pr[i];
	}
	sr[n + 1] = sb[n + 1] = n + 1;
	for (int i = n + 1; i >= 1; --i) {
		if (c[i] == 'B') sb[i - 1] = i, sr[i - 1] = sr[i];
		else if (c[i] == 'R') sb[i - 1] = sb[i], sr[i - 1] = i;
		else sb[i - 1] = sb[i], sr[i - 1] = sr[i];
	}
	++s[0][1], --s[0][2];
	for (int i = 0; i < n; ++i) {
		int id = i / 2 + 1;
		s[i & 1][id] += s[i & 1][id - 1];
		int x = s[i & 1][id];
		sum[i] = (sum[i - 1] + x) % mod;
		if (c[i] == 'X') {
			if (max(pr[i], pb[i]) - 1 < 0) x = sum[i];
			else x = (sum[i] - sum[max(pr[i], pb[i]) - 1] + mod) % mod;
		}
		if (c[i + 1] == 'B') continue;
		int p = i + 1, flag = 0;
		while (p < n) {
			int l = p - i, r = sr[p] - p - 1;
			if (p + l > n) break;
			if (l > r) { p = pr[p + l + 1]; continue; }
			if (p > sb[i]) break;
			if (sr[p] > sb[i]) { flag = 1; break; }
			r = (sr[p] - i - 1) / 2;
			s[i & 1][id + l] += x, s[i & 1][id + r + 1] -= x;
			p = sr[p];
		}
		if (flag) {
			int l = max(1ll, pr[sb[i]] - i), r = min(sb[i] - i - 1, (sr[sb[i]] - i - 1) / 2);
			if (l > r) continue;
			s[i & 1][id + l] += x, s[i & 1][id + r + 1] -= x;
		}
	}
	s[n & 1][n / 2 + 1] += s[n & 1][n / 2];
	int res = s[n & 1][n / 2 + 1];
	if (c[n] == 'X') res = res + sum[n - 1] - sum[max(pr[n], pb[n]) - 1];
	cout << (res % mod + mod) % mod;
	return 0;
}
```

如果有想看填表的话可以看一下  Gold14526 的代码，他好像就是填表然后类似这样做。

---

## 作者：VainSylphid (赞：5)

线性做法。

设 $f_i$ 表示给前 $i$ 个位置染成符合条件的串的方案数，转移有两种：

* 枚举 $i$ 前面的 $j$，判断中间一段能不能染一次变成符合条件的串，$f_j\rightarrow f_i$。
* 当 $s_i$ 为 `x` 时，这一位可以不染，$f_i-1\rightarrow f_i$。

考虑刻画染色的条件：对于每个 $j$，它右侧都能染成红色的是一个连续段，对于每个 $i$，它左侧都能染成蓝色的也是一个连续段。那么我们维护每个 $j$ 消失的时刻，用树状数组查询能给每个 $i$ 贡献的 $f_j$，就能做到 $O(n\log n)$。

注意到我们查询的区间左右端点的移动总和是均摊 $O(n)$ 的，用类似莫队的方式即可做到 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll mod = 1000000007;
ll n,prer[500005],nxtb[500005],f[500005];
char s[500005];
vector<ll> e[500005];
ll d[2][500005],cl[2],cr[2],cv[2];
void update(ll p,ll x,ll op)
{
	(d[op][p] += x) %= mod;
	if(cl[op] <= p && p <= cr[op])
		(cv[op] += x) %= mod;
}
ll query(ll l,ll r,ll op)
{
	while(cl[op] > l)
		(cv[op] += d[op][--cl[op]]) %= mod;
	while(cr[op] < r)
		(cv[op] += d[op][++cr[op]]) %= mod;
	while(cl[op] < l)
		(cv[op] -= d[op][cl[op]++]) %= mod;
	while(cr[op] < r)
		(cv[op] -= d[op][cr[op]--]) %= mod;
	cv[op] = (cv[op] + mod) % mod;
	return cv[op];
}
int main()
{
	scanf("%lld",&n);
	scanf("%s",s + 1);
	for(ll i = 1;i <= n;i++)
	{
		prer[i] = prer[i - 1];
		if(s[i] == 'R')
			prer[i] = i;
	}
	nxtb[n + 1] = n + 1;
	for(ll i = n;i;i--)
	{
		nxtb[i] = nxtb[i + 1];
		if(s[i] == 'B')
			nxtb[i] = i;
	}
	f[0] = 1,cl[0] = cl[1] = 2,update(0,f[0],0);
	if(nxtb[1] == 1)
	{
		printf("0\n");
		return 0;
	}
	if(nxtb[1] * 2 <= n)
		e[nxtb[1] * 2].push_back(0);
	for(ll i = 1;i <= n;i++)
	{
		for(auto j : e[i])
			update(j,(mod - f[j]) % mod,j & 1);
		if(s[i] == 'X')
			f[i] += f[i - 1];
		(f[i] += query(max(prer[i] * 2 - i,0LL),i,i & 1)) %= mod;
		update(i,f[i],i & 1);
		if(nxtb[i + 1] * 2 - i <= n)
			e[nxtb[i + 1] * 2 - i].push_back(i);
	}
	printf("%lld\n",f[n]);
	return 0;
}
```

---

## 作者：RainWetPeopleStart (赞：4)

提供一种线段树优化 DP 做法。

首先，记 $f_i$ 表示序列以 $i$ 结尾的答案。

转移分两种情况。

情况1：填白色，如果 $s_i=\texttt{x}$ 则 $s_i$ 可以填白色，有转移 $f_i=f_i+f_{i-1}$。

情况2：填 RB 段，这个不能暴力枚举，考虑优化。

发现只有 R 或 B 是简单的。考虑将转移分步。

使用线段树维护 DP 值，若一个位置 $j$ 在只考虑 R 的情况下无法转移到 $i$。则它一定无法转移到 $i$ 以后的位置，把这个位置设为 0 即可。

这样就得出了只考虑 R 限制的合法位置，下面考虑 B，发现只考虑 B 时满足条件的点是一段后缀，直接求和即可。

复杂度 $O(n\log n)$。

代码：


```cpp
#include<bits/stdc++.h>
#define ll long long
#define fi first
#define se second
#define pii pair<int,int>
#define mk make_pair
#define Int __int128_t
using namespace std;
const int N=5e5+10,mod=1e9+7;
int f[N],n;
int prel[N],nxtr[N];
struct segtree{
	int T[N<<2];
	#define ls p*2
	#define rs p*2+1
	#define mid (l+r)/2
	void pu(int p){
		T[p]=(T[ls]+T[rs])%mod;
	}void upd(int p,int l,int r,int x,int v){
		if(l==r){
			T[p]=v;return ;
		}if(x<=mid) upd(ls,l,mid,x,v);
		else upd(rs,mid+1,r,x,v);pu(p);
	}int qry(int p,int l,int r,int pl,int pr){
		if(pl<=l&&r<=pr) return T[p];
		int res=0;
		if(pl<=mid) res+=qry(ls,l,mid,pl,pr);
		if(pr>mid) res+=qry(rs,mid+1,r,pl,pr);
		return res%mod;
	}
	#undef mid
	#undef ls
	#undef rs
}sgt[2];
vector<int> tag[N];
void ins(int id){
	int pr=nxtr[id+1];
	//cout<<pr<<' ';
	pr--;
	pr+=(pr-id);pr=min(n,pr);
	tag[pr+1].push_back(id);
	//cout<<id<<' '<<pr<<"ins"<<endl;
}
int sl[N],sr[N];
int chk(int l,int r){
	int len=r-l+1;
	int mid=l-1+len/2;
	int cnt=(sr[mid]-sr[l-1])+(sl[r]-sl[mid]);
	return (cnt==0);
}
void slv(){
	cin>>n;
	string s;cin>>s;
	if(n%2==1){
		cout<<0;return ;
	}int la=0;
	for(int i=1;i<=n;i++){
		if(s[i-1]=='R') la=i;
		prel[i]=la;
	}la=n+1;nxtr[n+1]=n+1;
	for(int i=n;i>=1;i--){
		if(s[i-1]=='B') la=i;
		nxtr[i]=la;
	}
	for(int i=1;i<=n;i++){
		sl[i]=sl[i-1],sr[i]=sr[i-1];
		if(s[i-1]=='R') sl[i]++;
		if(s[i-1]=='B') sr[i]++;
	}
	//0-e 1-o
	f[0]=1;f[1]=(s[0]=='X');
	ins(0);ins(1);
	sgt[0].upd(1,0,n,0,f[0]);sgt[1].upd(1,0,n,1,f[1]);
	for(int i=2;i<=n;i++){
		for(auto ed:tag[i]){
			sgt[0].upd(1,0,n,ed,0);
			sgt[1].upd(1,0,n,ed,0);
		}int op=i%2;
		if(s[i-1]=='X') f[i]=f[i-1];
		int lp=prel[i];
		lp=lp-(i-lp);lp=max(0,lp);
		//cout<<f[i]<<' ';
		f[i]+=sgt[op].qry(1,0,n,lp,i);f[i]%=mod;
		sgt[op].upd(1,0,n,i,f[i]);
		//cout<<f[i]<<endl;
		ins(i);
	}cout<<f[n]<<endl;
}
int main(){
	//freopen("2.in","r",stdin);
	//freopen("2.out","w",stdout);
    //int t;cin>>t;while(t--) 
	slv();
	return 0;
}
```

---

## 作者：P2441M (赞：2)

## 题意

有一条排列着 $n$ 个点的数轴，初始时所有点都是白色的。你可以进行若干次如下操作：

- 选择 $i,x$，满足 $1\leq i\leq i+2x-1\leq n$ 且 $[i,i+2x-1]$ 中的点都是白色，将 $[i,i+x-1]$ 中的点染成红色，再将 $[i+x,i+2x-1]$ 中的点染成蓝色。

给定一个长度为 $n$ 的、由 $\texttt{R},\texttt{B},\texttt{X}$ 构成的字符串 $s$，其中 $s_i=\texttt{R}$ 表示点 $i$ 必须被染成红色，$s_i=\texttt{B}$ 表示点 $i$ 必须被染成蓝色，$s_i=\texttt{X}$ 表示没有限制。求满足限制的染色方案数，答案对 $10^9+7$ 取模。$2\leq n\leq 5\times 10^5$。

## 题解

感觉有点神秘。

考虑 DP，令 $f_i$ 表示考虑前 $i$ 个点的染色方案数。对于转移：

- 若 $s_i=\texttt{R}$，则 $f_i=0$。
- 若 $s_i=\texttt{X}$，则令 $f_i\leftarrow f_i+f_{i-1}$。
- 令 $f_i\leftarrow f_i+\sum_{valid(j,i)}f_{j-1}$，其中 $valid(j,i)$ 表示是否能对 $[j,i]$ 中的所有点进行一次操作。

考虑刻画合法区间的判定条件：

- 首先显然需要有 $2\mid(i-j+1)$。
- 令 $nxt_j$ 表示点 $j$ 右边第一个要求被染成蓝色的点，则 $i-nxt_j+1\leq\frac{i-j+1}{2}\Leftrightarrow 2nxt_j-j-1\geq i$。
- 令 $prv_i$ 表示点 $i$ 左边第一个要求被染成红色的点，则 $prv_i-j+1\leq\frac{i-j+1}{2}\Leftrightarrow j\geq 2prv_i-i+1$。

$prv,nxt$ 随便扫一下就能预处理出来，这样就有了 $\mathcal{O}(n^2)$ 的暴力 DP。

考虑优化，对于条件 $1$，分奇偶考虑即可。我们开两个 BIT，然后把 $f_{i-1}$ 挂在对应 BIT 的 $2nxt_i-i-1$ 处，这样每次查询一个后缀和就可以满足第 $2$ 个条件。对于条件 $3$，直接搞一个指针，每次 $2prv_i-i+1$ 变化时，指针对应左移/右移，然后我们对应在 BIT 上增/删即可。

我们指出，指针的移动量是 $\mathcal{O}(n)$ 的。

**证明**：显然 $prv_i$ 是由若干连续同值段组成的，当 $i\leftarrow i+1$ 时：
- 若 $i,i+1$ 处于同段，则单次变化量就是 $1$，于是对于所有这样的变化，指针的总变化量就是 $\mathcal{O}(n)$。
- 若 $i,i+1$ 处于不同段，那么单次变化量是 $2prv_{i+1}-2prv_i-1$，显然指针的总变化量依然是 $\mathcal{O}(n)$ 的。

$\Box$

时间复杂度 $\mathcal{O}(n\log{n})$。

## 代码

```cpp
#include <iostream>

using namespace std;

#define lowbit(x) ((x) & -(x))
#define chk_min(x, v) (x) = min((x), (v))
#define chk_max(x, v) (x) = max((x), (v))
typedef long long ll;
typedef pair<int, int> pii;
const int N = 5e5 + 5, MOD = 1e9 + 7;

inline int add(int x, int y) { return x += y, x >= MOD ? x - MOD : x; }
inline int sub(int x, int y) { return x -= y, x < 0 ? x + MOD : x; }
inline void cadd(int &x, int y) { x += y, x < MOD || (x -= MOD); }
inline void csub(int &x, int y) { x -= y, x < 0 && (x += MOD); }

int n, ans, prv[N], nxt[N];
int f[N];
char s[N];

struct BIT {
	int c[N << 1];
	inline int query(int x) {
		ll res = 0;
		for (; x <= n << 1; x += lowbit(x)) res += c[x];
		return res % MOD;
	}
	inline int query(int l, int r) { return sub(query(r), query(l - 1)); }
	inline void add(int x, int v) { for (; x; x -= lowbit(x)) cadd(c[x], v); }
} ft0, ft1;

inline void proc(int i, int s) {
	int v = s == 1 ? f[i - 1] : sub(0, f[i - 1]);
	if (i & 1) ft1.add(nxt[i] * 2 - i - 1, v);
	else ft0.add(nxt[i] * 2 - i - 1, v);
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> n >> s + 1;
    for (int i = 1, j = 0; i <= n; ++i) {
    	if (s[i] == 'R') j = i;
    	prv[i] = j;
    }
    for (int i = n, j = n + 1; i; --i) {
    	if (s[i] == 'B') j = i;
    	nxt[i] = j;
    }
    f[0] = 1, proc(1, 1);
    for (int i = 1, l = 1; i <= n; ++i) {
    	if (s[i] == 'R') { f[i] = 0; continue; }
    	if (s[i] == 'X') f[i] = f[i - 1];
    	int p = max(prv[i] * 2 - i + 1, 1);
    	while (l < p) proc(l++, -1);
    	while (l > p) proc(--l, 1);
    	cadd(f[i], (i & 1) ? ft0.query(i) : ft1.query(i));
    	if (i < n) proc(i + 1, 1);
    }
    cout << f[n];
    return 0;
}
```

---

## 作者：_ANIG_ (赞：2)

[传送门](https://www.luogu.com.cn/problem/P11456)

无脑做法。

设 $f_i$ 为考虑前 $i$ 个位置，最后一个 RB 段的结尾为 $i$ 的方案数。

显然有 $f_i=f_{i-1}+\sum\limits_{ok(j,i)}f_{j-1}$，其中 $ok(j,i)$ 表示区间 $[j,i]$ 是合法的 RB 段。

这个限制比较奇怪，考虑 CDQ 分治优化。

类似括号匹配，记一下 $[l,mid]$ 中匹配完剩下 $k$ 个左括号的方案数之和，前缀和差分优化，总复杂度 $O(n\log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+5,mods=1e9+7;
int n,p[N],f[N],g1[N],g2[N],q1[N],q2[N],lst[N],nxt[N];
void add(int l,int r,int sm){
	if(l<0)l%=2;
	if(l<0)l+=2;
	if(l>r)return;
	g1[l]+=sm;
	g1[r+2]-=sm;
}
int gets(int l,int r){
	if(l>r)return 0;
	if(l<=1)return g2[r];
	return g2[r]-g2[l-2];
}
void solve(int l,int r){
	if(l==r){
		if(p[l]==2)f[l]+=f[l-1];
		f[l]%=mods;
		return;
	}
	int mid=l+r>>1;
	solve(l,mid);
	for(int i=0;i<=r-l+1;i++)g1[i]=g2[i]=0;
	lst[l-1]=l-1;nxt[mid+1]=mid+1;
	for(int i=l;i<=mid;i++){
		if(p[i]==0)lst[i]=i;
		else lst[i]=lst[i-1];
	}
	for(int i=mid;i>=l;i--){
		if(p[i]==1)nxt[i]=i;
		else nxt[i]=nxt[i+1];
	}
	for(int i=mid;i>=l;i--){
		if(nxt[i]==mid+1)g2[mid-i+1]+=f[i-1];
		add(2*max(lst[mid],i)-i+1-mid,2*(nxt[i]-1)-i+1-mid,f[i-1]);
	}
	for(int i=2;i<=r-l+1;i++)g1[i]+=g1[i-2],g1[i]%=mods;
	for(int i=2;i<=r-l+1;i++)(g2[i]+=g2[i-2])%=mods;
	lst[mid]=mid;nxt[r+1]=r+1;
	for(int i=mid+1;i<=r;i++){
		if(p[i]==0)lst[i]=i;
		else lst[i]=lst[i-1];
	}
	for(int i=r;i>mid;i--){
		if(p[i]==1)nxt[i]=i;
		else nxt[i]=nxt[i+1];
	}
	for(int i=mid+1;i<=r;i++){
		if(lst[i]==mid){
			f[i]+=g1[i-mid];
		}
		f[i]+=gets(i+mid-2*(min(nxt[mid+1],i)-1),i+mid-2*max(lst[i],mid+1));
		f[i]%=mods;
	}
	solve(mid+1,r);
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		char c;
		cin>>c;
		if(c=='R')p[i]=0;
		else if(c=='B')p[i]=1;
		else p[i]=2;
	}
	f[0]=1;
	solve(1,n);
	cout<<(f[n]%mods+mods)%mods<<endl;
}

```

---

## 作者：huhangqi (赞：1)

题目比较关键的点在于存在两种不同的点，因此而存在两种约束条件，对我们问题处理影响非常大。

这类计数题目使用动态规划的概率很大，那么先考虑动态规划。

我们设状态 $dp_i$ 表示在目前已经选择了前 $i$ 段的方案数，转移通过前缀和判断是否合法，暴力添加即可。

那么此时的时间复杂度是 $O(n^2)$ 的，考虑如何进行优化。

首先最显而易见的是区间长度一定是偶数，因此我们可能需要按照奇偶进行分类处理。

我们拆开红色的影响和蓝色的影响进行判断。

假设我们现在需要处理出 $dp_i$ 的值，我们想要得到对于红色合法的转移。

假设上一个红色的位置为 $la$，那么我们的左端点选择在 $[la-(i-la)+1,i]$，当然是保证奇偶相同的。

那么我们就需要将 $[la-(i-la),i-1]$ 的值转移过来。

但是我们还有蓝色的情况仍然存在影响，需要继续判断。

蓝色的并不像红色的可以直接判断，因为你选择覆盖的红色区间左右端点都在移动，所以这些可以选择进行转移的位置并不是一个区间。

那么我们反过来考虑，处理出每一个点可以被转移到的位置，做一个类似差分的修改操作，然后通过数据结构按照位置维护，通过修改值的大小满足蓝色的条件，通过查询的范围得到维护红色的条件，并且开两组数据结构分别维护即可。

那么我们很明显可以使用树状数组进行维护。

那么继续推出每个值在哪个范围内进行转移即可，只需要考虑下一个蓝色不会包含在红色内即可。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int n,la,lb,dp[500005];
char s[500005];
vector<int> e[500005];
struct BT{
	int c[500005];
	int lowbit(int x){
		return x&-x;
	}
	void add(int x,int y){
		x++;
		for(int i=x;i<=n+1;i+=lowbit(i))c[i]=(c[i]+y+mod)%mod;
	}
	int query(int x){
		x++;
		int ans=0;
		for(int i=x;i;i-=lowbit(i))ans=(ans+c[i])%mod;
		return ans;
	}
	int query(int l,int r){
		if(l>r)return 0;
		if(!l)return query(r);
		return (query(r)-query(l-1)+mod)%mod;
	}
}bit[2];
signed main(){
	cin>>n>>s+1;
	dp[0]=1;
	bit[0].add(0,dp[0]);
	for(int i=1;i<=n;i++){
		if(s[i]=='X')dp[i]=dp[i-1];
		if(s[i]=='R')la=i;
		if(s[i]=='B'){
			while(lb<i){
				if(i+(i-lb)<=n)e[i+(i-lb)].push_back(lb);
				lb++;
			}
		}
		for(int v:e[i])bit[v&1].add(v,-dp[v]);
		int l=max(la-(i-la),0ll);
		dp[i]=(dp[i]+bit[i&1].query(l,i-1))%mod;
		bit[i&1].add(i,dp[i]);
	}
	cout<<dp[n];
	return 0;
}

``````

---

## 作者：MoGuYun_12 (赞：1)

教练讲了本题的线性做法，自己写一篇题解加深理解。

对于求方案数的问题，一般有两种方法解决。一是组合数学，二是动态规划。像本题这种序列问题，可以考虑动态规划。

设 $f_i$ 表示前 $i$ 个位置中，合法序列的方案数。

如果当前位置没有限制，则可以顺承上一个位置的方案数，即 $f_i = f_{i-1}$。如果当前位置有限制，那么找到一段前面的合法连续子段，记其左端点为 $l$，右端点为 $r$，则转移方程为 $f_i = f_{i-1} + \sum_{j=l}^r f_j$，显然可以用前缀和优化后面的一坨求和。

接下来考虑如何求左端点和右端点。统一对右端点进行操作，先预处理每个位置之前最晚出现的两种颜色下标，记为 $prer$ 和 $preb$。在转移过程中假设当前下标为 $i$，能转移到 $i$ 的下标为 $j$，那么右端点为 $i - 2(i-j+1)$，左端点为 $preb_j$，因为如果再往右就会到上上一个合法序列。

代码实现需要注意细节和特殊限制。


```cpp
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int N = 5e5+5;
const int p = 1e9+7;
int n,l,prer[N],preb[N];
ll f[N],sum[N];
vector<int> v[N];
string s;

ll cal(int now,int l,int r){
	int L=now-2*r,R=now-2*l;
	if(L>R) return 0;
	if(L<2) return sum[R];
	return (sum[R]-sum[L-2]+p)%p;
}
int main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>n>>s; l=s.size(),s=" "+s;	 
    int lb=0,lr=0;
    for(int i=1;i<=n;i++){
    	prer[i]=lr,preb[i]=lb;
    	if(s[i]=='R') lr=i;
    	if(s[i]=='B') lb=i;
	}
    for(int i=1;i<=n;i++){
    	if(s[i]=='X') v[i].push_back(i);
    	if(s[i]=='B'){
    		for(int j=i;j<=min(n,i*2-preb[i]-2);j++) //预处理j能被哪些i转移 
    			v[j].push_back(i);
		}
	}
	sum[0]=f[0]=1;
	for(int i=1;i<=n;i++){
		if(s[i]!='R'){
			if(s[i]=='X') f[i]=f[i-1];
			int lim=i-prer[i]; //注意这里的限制 
			for(auto j:v[i]){
				int l=i-j+1;
				if(l>lim) continue;
				int r=min(lim,(i-preb[j])>>1);
				(f[i]+=cal(i,l,r))%=p;
			}
		}
		sum[i]=(i==1 ? f[1] : sum[i-2]+f[i])%p; //前缀和优化 
	}
	cout<<f[n];
	return 0;
}

```

---

## 作者：123456xwd (赞：1)

学习了 @[MoGuYun_12](https://www.luogu.com.cn/user/690320) 的线性做法，用自己的话记录一下，并且说明下复杂度。

设 $f_i$ 表示使得 $s_{1\sim i}$ 合法的方案数，考虑转移。

设 $preb,prer$ 表示每个点前面第一个 `B,R` 的下标。

若 $s_i$ 可以为白色，那么显然 $f_{i}\gets f_{i-1}$。

若 $s_i$ 可以为蓝色，那么考虑以 $i$ 为结尾的一个染色区间，设长度为 $2len$。

那么也就是说 $[i-len+1,i]$ 内不能有 `R`，$[i-2len+1,i-len]$ 内不能有 `B`。

第一个限制好搞，利用 $prer$ 即可，考虑第二个限制，即是要求 $preb_{i-len+1}<i-2len+1$。

设 $i-len+1=j$，则 $preb_{j}<2j-i-1\Rightarrow i\le 2j-preb_j-2$。

不妨从 $j$ 去推导可能合法的 $i$，但是呢，这样子时间复杂度是不对的。

事实上，我们就可以只在 $s_j$ 为 `B` 的位置去寻找 $i$，且钦定这个 `B` 是所选的 $[i-len+1,i]$ 中第一个 `B`。

那么，根据 $preb_j,prer_i$，我们可以求得 $len$ 的一段合法区间，前缀和优化转移即可。

这样子时间复杂度为 $\mathcal{O}(j-preb_j)$，总体上是 $\mathcal{O}(n)$ 的。

总时间为 $\mathcal{O}(n)$。

注意，若 $[i-len+1,i]$ 内没有 `B`，不妨假设 $s_i$ 就是 `B`。

```c++
#include<bits/stdc++.h>
#define ull unsigned long long
#define ll long long
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
const int N=5e5+5,mod=1e9+7;
void add(int &x,int y){
    x+=y;
    if(x>=mod) x-=mod;
}
int f[N],sum[N],n,preb[N],prer[N];
vector<int> vec[N];
char ch[N];
int calc(int i,int l,int r){
    int L=i-r*2,R=i-l*2;
    if(L<2) return sum[R];
    return (sum[R]-sum[L-2]+mod)%mod;
}
int main(){
    scanf("%d%s",&n,ch+1);
    int lb=0,lr=0;
    for(int i=1;i<=n;i++){
        preb[i]=lb,prer[i]=lr;
        if(ch[i]=='R') lr=i;
        if(ch[i]=='B') lb=i;
    }
    for(int i=1;i<=n;i++){
        if(ch[i]=='X') vec[i].p_b(i);
        if(ch[i]=='B'){
            for(int j=i;j<=min(n,2*i-preb[i]-2);j++) vec[j].p_b(i);
        }
    }
    f[0]=sum[0]=1;
    for(int i=1;i<=n;i++){
        if(ch[i]=='X') f[i]=f[i-1];
        if(ch[i]!='R'){
            int tmp=i-prer[i];
            for(auto j : vec[i]){
                int lenl=i-j+1,lenr=min(tmp,(i-preb[j])/2);
                if(lenl<=lenr) add(f[i],calc(i,lenl,lenr));
            }
        }
        if(i==1) sum[i]=f[i];
        else sum[i]=(f[i]+sum[i-2])%mod;
    }
    printf("%d\n",f[n]);
    return 0;
}
```

---

## 作者：CarroT1212 (赞：0)

比较神经的题。

DP，设 $dp_i$ 表示 $i$ 以前的限制全被满足的方案数，有

$$dp_i=dp_{i-1}[s_i=\texttt{X}]+dp_{l-1}[s_{[l,mid-1]}\neq \texttt{B}\wedge s_{[mid,i]}\neq\texttt{A}]$$

其中 $mid$ 表示枚举的以 $i$ 为右端点的合法段的第一个 `B` 的位置，$l=i-2(i-mid)-1$ 表示左端点。现在随便做一下就有 $O(n^2)$ 了。考虑优化。

观察一下后一种转移。假设从右往左枚举 $mid$，那么 $l$ 也是从右往左扩展的。如果 $l$ 在往左的过程中，$[l,mid-1]$ 突然新出现了一个 `B`，导致转移不合法，那我们就至少需要让 $mid\gets l+1$，才可能继续发生合法的转移，这直接导致序列长度翻了个倍。

这启示我们如果精细实现的话可能的转移点区间是 $O(\log)$ 级别的。如果这样就可以求出这些转移区间搞个奇偶前缀和优化过去了。

考虑这么一种求法：设目前处理 $dp_i$ 的转移，钦定 $s_i=\texttt{B}$，不是的话就当它是。我们维护 $i$ 及之前的 `B` 出现位置序列以及 `A` 的最后一次出现位置 $ma$，设它们是 $c_0=0,c_1,c_2,\cdots,c_k$。

我们从 $k$ 开始枚举一对 $(c_{j-1},c_j)$，每次假设 $mid$ 位于 $[\max(c_{j-1},ma)+1,c_j]$ 间，考虑由 $mid$ 求得的 $l$ 有哪些是合法的，容易知道对于 $l$ 此时它的限制只有 $l$ 的奇偶性与 $i$ 不同且 $l>c_{j-1}$，再结合上面对 $mid$ 的限制，容易知道 $l$ 的一个合法转移区间。

如果存在一个 $l$ 的合法转移区间，直接计算区间内合法的 $dp$ 和然后令 $j\gets j-1$ 继续做；否则令 $j$ 为 $mid=c_j$ 时 $l$ 及其右侧的第一个 `B` 对应的 $j$，继续做（跳过了一些不可能成为转移点的 $j$ 保证复杂度）。时刻注意 $mid$ 不可 $\le ma$。

实现起来有点繁琐。注意一些 $+1$ $-1$ 之类的问题差不多就可以了。$O(n\log^2 n)$ 带极小常数。

```cpp
const ll J=1e18,N=5e5+7,P=1e9+7;
ll n,dp[N],sum[N];
char str[N];
vector<ll> v[2];
ll cal(ll l,ll r,ll x) {
	if (l>r) return 0;
	ll o=x&1; l--,r--;
	return (sum[(r-o)/2*2+o]+P-(l-1-o>=0?sum[(l-1-o)/2*2+o]:0))%P;
}
void mian() {
	scanf("%lld%s",&n,str+1);
	v[1].pb(0),v[0].pb(0);
	dp[0]=sum[0]=1;
	for (ll i=1;i<=n;i++) {
		if (str[i]=='X') dp[i]=dp[i-1];
		if (str[i]=='R') v[0].pb(i);
		else {
			v[1].pb(i);
			ll p=(ll)v[1].size()-1;
			while (v[1][p]>v[0].back()) {
				ll zl=max(v[1][p-1],v[0].back())+1,zr=v[1][p];
				ll cr=i-(i-zr)*2-1;
				ll np=lower_bound(v[1].begin(),v[1].end(),cr)-v[1].begin();
				if (p==np) {
					ll cl=max(v[1][np-1]+1,i-(i-zl)*2-1);
					(dp[i]+=cal(cl,cr,i))%=P;
					p--;
				}
				else p=np;
			}
			if (str[i]=='X') v[1].pop_back();
		}
		sum[i]=((i==1?0:sum[i-2])+dp[i])%P;
	}
	cout<<dp[n];
}
```

---

## 作者：BYR_KKK (赞：0)

作者太笨了，赛时写了一个非常丑的线段树优化 dp。

首先发现答案只和选择哪些区间有关，于是我们钦定从左往右选择区间进行操作。令 $f_i$ 表示操作完所有右端点 $\le i$ 的区间后，强制最后一次是操作以 $i$ 为右端点的区间，使得 $1\sim i$ 满足条件的方案数。

枚举右端点考虑左端点的贡献不好做。考虑从左端点转移右端点。具体地，假设当前枚举的左端点为 $i$，我们为其找一个合法的右端点 $j$，将某个贡献 $v$ 转移到 $j$ 上。先考虑如果我们能求出 $v$ 后怎么快速转移 $j$。刻画一下 $j$ 需要满足的条件，下面将已经给出的为红色的点简称红色点，蓝色点同理。

考虑 $i$ 后所有红色点的位置 $r_1,r_2,\dots,r_m$，设 $x=\dfrac{j-i+1}{2}$，在 $i+x-1$ 中一定会包含 $r$ 的一段前缀（可以为空）。枚举这个前缀的最后一个点 $r_p$，设 $y=r_p-i+1$，那么显然有 $x\ge y$，即 $\dfrac{j-i+1}{2}\ge y$，稍微化一下得到 $j\ge 2y+i-1$。同时注意还存在一个条件就是 $j<r_{p+1}$，综合起来得到 $2y+i-1\le j<r_{p+1}$，放缩得到 $2y+i-1<r_{p+1}$，即 $2r_p-i+1<r_{p+1}$，看上去合法的 $p$ 并不会很多。实际上确实如此，移项得到 $r_p-i+1<r_{p+1}-r_p$。不妨令 $d_p=r_{p}-i+1$，即 $i,r_p$ 之间的距离。显然有 $d_{p+1}=d_p+r_{p+1}-r_p$。上面的不等式就可以表示成 $2d_p<d_{p+1}$，因此当一个 $p$ 合法就意味着存在 $2d_p<d_{p+1}$，由于 $d_p$ 递增，所以最多 $O(\log n)$ 个 $p$ 合法。

因此我们对于某一个 $j$,我们只转移合法的 $p$ 即可。但是这样还是不好做，考虑用合法的 $p$ 去转移 $j$，不难发现一个 $p$ 能转移到的 $j$ 是一段区间。因此可以用线段树维护这个过程。剩下的问题是：

1.如何找到能转移的 $p$。

2.如何找到 $p$ 能转移到的区间。

这里可能有问题就是已经知道了对于一个 $j$ 有 $O(\log n)$ 个 $p$ 能转移，但是怎么知道一共就 $O(\log n)$ 个 $p$ 能转移 $j$ 呢？

我们重新看上面的推导，没有利用 $j$ 的任何性质。换言之就是如果一个 $r_p$ 合法，也必须满足 $2d_p<d_{p+1}$。因此数量也是 $O(\log n)$。

先来看第一个问题。显然由上面的推导，$2d_p<d_{p+1}$ 是 $r_p$ 合法的充要条件，我们将 $d_p$ 变成 $r_p$ 的形式不难得到 $i>2r_p-r_{p+1}+1$，因此按照 $2r_p-r_{p+1}+1$ 放入堆里即可。

第二个问题，考虑选择的区间为 $[i,j]$，红色段的长度为 $x$。那么有 $i+x-1\ge r_p$，同时 $i+x-1<r_{p+1}$。注意还需要关注蓝色点的位置，即 $[i,i+x-1]$ 中不包含蓝色点。可以简单通过维护蓝色点的位置得到能转移到的区间的左右端点。线段树维护转移即可。

还有一个问题是一开始所说的要转移的贡献 $v$。看上去 $v=\sum\limits_{j=1}^{i-1}f_j$，不过注意如果 $[j+1,i-1]$ 中存在红色点或蓝色点，则这些点必须被染色，因此 $j$ 并不是从 $1$ 开始枚举的。

时间复杂度 $O(n\log^2 n)$。

---

## 作者：SnowTrace (赞：0)

提供一个我场上写的没脑子神秘做法。

首先注意到不同的染色结果显然最多对应一种染色的方式，所以可以 dp。

设 $dp_i$ 表示给 $[1,i]$ 这个区间染色并满足题目条件的方案数。

考虑转移，我们尝试枚举以 $r$ 结尾的染色段长度，也就是枚举题目中所说的那个 $\texttt {RRRBBB}$ 的长度。

设 $c_{l,r}$ 表示能否通过一次染色把 $[l,r]$ 全部覆盖且合法。

我们尝试分析固定一个染色位置的右端点 $r$，考虑合法的染色半径需要满足怎么样的条件。

我们知道我们染出来的东西是 $\texttt {RRRBBB}$ 这样的结构，所以 $\texttt{R,B}$ 都会对 $c_{l,r}$ 有影响。

首先考虑 $\texttt {R}$ 的限制，$\texttt {R}$ 的限制很容易，实际上说的是染色的长度不能超过某个值（只有距离当前点最近的那个 R 才会有影响）。

然后考虑 $\texttt {B}$ 的性质，设我们现在有 $s_i = \text {B}$，上面固定的右端点是 $r$，则一个 $\texttt {B}$ 实际上是规定了染色半径为 $[\lceil\dfrac{r-i+1}{2}\rceil，r-i]$ 的染色方案不合法。

我们声称：对于一个固定的 $r$，不合法的染色半径的连续区间个数是 $O(\log n)$ 的。

具体的，我们考虑上面 $\texttt {B}$ 字符对合法左端点形态的影响，设 $i$ 是最小的满足 $s_i = \text {B}$ 的位置，那么容易知道染色半径比 $>r-i$ 的都合法，然后再考虑染色半径 $\leq r-i$ 的方案，此时我们就能知道，**可能不合法的半径长度必须 $\leq r-i$**，而我们根据 $s_i = \text {B}$ 可以知道 $[\lceil\dfrac{r-i+1}{2}\rceil，r-i]$ 不合法，相当于你每出现一个 $s_i = \text {B}$ 的点就能让还没被确定是否合法的半径长度减半。

实际上 $s_i = \text {B}$ 构成的限制区间的集合是可能存在两个区间相交的，但是显然，区间相交只会使得连续段变少而不是变多。

我的实现非常神秘，不想展开讲了，但是应该也能类似的证明是 $O(n\log n)$ 的。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define double long double
#define lowbit(x) (x&(-x))
#define int long long
const int mod = 1000000007; 
int n;
char s[500005];
int nxt[500005],pre[500005];
int dp[500005];
int pre0[500005],pre1[500005];
int calc(int pos,int l,int r){
	//in pos,length [2l,2r]
	if(pos&1){
		return (pre1[pos-2*l]-((pos-2*r-2>=0)?pre1[pos-2*r-2]:0)+mod)%mod;
	}else{
		return (pre0[pos-2*l]-((pos-2*r-2>=0)?pre0[pos-2*r-2]:0)+mod)%mod;
	}
}
vector<pair<int,int> >seg;
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> n;for(int i = 1;i<=n;i++)cin >> s[i];
	for(int i = 0;i<=n+1;i++)pre[i] = 0,nxt[i] = n+1;
	for(int i = 1;i<=n;i++)if(s[i] == 'B')pre[i] = i,nxt[i] = i;
	for(int i = n;i>=1;i--)nxt[i] = min(nxt[i],nxt[i+1]);
	for(int i = 1;i<=n;i++)pre[i] = max(pre[i],pre[i-1]);
	dp[0] = pre0[0] = 1;
	int lst = 0;
	for(int i = 1;i<=n;i++){
		if(s[i] == 'R'){
			lst = i;
			if(i&1)pre1[i] = pre1[max(i-2,0ll)];
			else pre0[i] = pre0[i-2];
			continue;
		}
		if(s[i] == 'X')dp[i] = (dp[i-1]+dp[i])%mod;
		int l = 1,r = min(i-lst,i/2);
		int now = nxt[1];
		seg.clear();
		while(now<i){
			//range
			int L=n,R=0;
			while(1){
				int r = i-now,l = (i-now+2)/2;
				L = min(L,l),R = max(R,r);
				int to = pre[i-l];
				assert(i-l>=0);

				if(to == now){
					//cannot find other point
					break;
				}else{
					now = to;
				}
			}
			assert(L<=R);
			seg.push_back({L,R});
			now = nxt[now+1];
		}
		dp[i] = (dp[i]+calc(i,l,r))%mod;
		for(auto x:seg){
			int L = x.first,R = x.second;
			if(max(l,L)<=min(r,R))dp[i] = (dp[i]-calc(i,max(l,L),min(r,R))+mod)%mod;
		}
		if(i%2==0)pre0[i] = (pre0[max(i-2,0ll)]+dp[i])%mod;
		else pre1[i] = (pre1[max(i-2,0ll)]+dp[i])%mod;
	}
	cout << dp[n] << endl;
	return 0;
}
```

---

