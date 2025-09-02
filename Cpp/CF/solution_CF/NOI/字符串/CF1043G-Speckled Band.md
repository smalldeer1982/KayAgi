# Speckled Band

## 题目描述

Ildar 拿了一条带子（一条细长的布条）并给它染上了颜色。形式上，这条带子有 $n$ 个格子，每个格子被染成 $26$ 种颜色中的一种，因此我们可以用小写英文字母来表示每种颜色。

Ildar 决定从带子上选取他喜欢的某一段区间 $[l, r]$（$1 \le l \le r \le n$），并将其剪下来。这样他就得到了一个新的带子，可以表示为字符串 $t = s_l s_{l+1} \ldots s_r$。

之后，Ildar 会玩如下的游戏：他将带子 $t$ 剪成若干新带子，并统计其中不同带子的数量。形式上，Ildar 选择 $1 \le k \le |t|$ 个下标 $1 \le i_1 < i_2 < \ldots < i_k = |t|$，将 $t$ 剪成 $k$ 个带子字符串 $t_1 t_2 \ldots t_{i_1}, t_{i_1 + 1} \ldots t_{i_2}, \ldots, t_{i_{k-1} + 1} \ldots t_{i_k}$，然后统计这些带子中不同带子的数量。他想知道，在至少有一个带子出现至少两次的前提下，他能得到的不同带子的最小数量。游戏的结果就是这个数量。如果无法将 $t$ 剪成满足条件的带子，则游戏结果为 $-1$。

不幸的是，Ildar 还没有决定他喜欢哪一段区间，但他有 $q$ 个候选区间 $[l_1, r_1]$，$[l_2, r_2]$，……，$[l_q, r_q]$。你的任务是计算每个区间的游戏结果。

## 说明/提示

考虑第一个样例。

如果 Ildar 选择区间 $[1, 6]$，他剪下的字符串 $t = abcabc$。如果他将 $t$ 剪成两个带子 $abc$ 和 $abc$，带子 $abc$ 出现了两次，不同带子的数量为 $1$。所以，这个游戏的结果是 $1$。

如果 Ildar 选择区间 $[4, 7]$，他剪下的字符串 $t = abcd$。无法将这个带子剪成至少有一个带子出现两次的情况，所以结果为 $-1$。

如果 Ildar 选择区间 $[3, 6]$，他剪下的字符串 $t = cabc$。如果他将 $t$ 剪成三个带子 $c$、$ab$ 和 $c$，带子 $c$ 出现了两次，不同带子的数量为 $2$。所以，这个游戏的结果是 $2$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
9
abcabcdce
7
1 6
4 7
5 9
6 9
1 9
3 6
4 4
```

### 输出

```
1
-1
4
3
2
2
-1
```

# 题解

## 作者：IkunTeddy (赞：9)

# 题目分析
我们阅读题目后能够很容易的得出答案有解时最大为 $4$。因为答案种类数较少时我们可以考虑直接分类讨论。

1. 答案为 $-1$

那么区间内的字母都只出现一次，所以我们开个字母出现次数的前缀和判断即可。

时间复杂度 $O(\Sigma)$。

2. 答案为 $1$

因为只能出现一种子串，例如 $\textrm{AAA}$。所以我们判断一下这个区间是否有循环节即可，根据循环节的定义我们只需判断区间长度的因子是否为循环节即可。可以使用 Hash，也可以用 SA。

查询时间复杂度为因子个数，SA 预处理时间复杂度 $O(n\log{n})$，暴力预处理因子时间复杂度 $O(n \sqrt{n})$。

3. 答案为 $2$

答案为 $2$ 只有三种情况 $\textrm{AAB}$，$\textrm{BAA}$，$\textrm{ABA}$。前两种我们只需像[优秀的拆分](https://www.luogu.com.cn/problem/P1117)一样统计一下 $pre[i]$ 和 $suf[i]$ 分别表示以 $i$ 开头的最短 $\textrm{AA}$ 长度，以 $i$ 结尾的最短 $\textrm{AA}$ 长度。然后枚举关键点统计即可，随便用什么数据结构维护一下就行。

查询时间复杂度 $O(1)$，根据调和级数得出预处理时间复杂度 $O(n\ln{n})$。

再考虑第三种情况，其实就是判断子串是否有 border。最长 border 比较难求，但是最短 border 就比较简单了。

引理：若串 S 的最小 border 长度超过 $\sqrt{|S|}$ 则该 border 在串中的出现次数不超过 $\sqrt{|S|}$ 次。

所以我们可以考虑平衡规划，对于判断长度小于 $\sqrt{|S|}$ 的 border，我们直接枚举长度用 SA 或 Hash 判断即可。对于判断长度大于 $\sqrt{|S|}$ 的 border 我们可以枚举在后缀排名中与 $rnk[l]$ 相邻的 $\sqrt{|S|}$ 个后缀判断 border。

我们还要注意一个点，若有一个长度大于 $\frac{|S|}{2}$ 的 border，那么相交处还会存在一个更小的 border。所以我们求出的 border 长度小于 $\frac{|S|}{2}$ 的 border 才是合法的。

查询时间复杂度 $O(\sqrt{n})$。

4. 答案为 $3$

答案为 $3$ 也只有三种情况 $\textrm{ABAC}$，$\textrm{BACA}$，$\textrm{BAAC}$。

前两种只需判断 $s[l]$ 和 $s[r]$ 在 $s[l+1\sim r-1]$ 中是否出现过即可。用前面需处理的前缀和判断。

第三种情况，我们可以用前面已知的 $pre$ 帮助判断，我们就是判断是否存在一个 $i$ 满足 $\forall i \in \{l+1,\cdots,r-1\}$ 且 $i+pre[i]<r$。这个式子可以贪心，$i+pre[i]$ 越小越优秀，我们预处理 ST 表即可查询。

查询时间复杂度 $O(1)$，预处理时间复杂度 $O(n\log{n})$。

5. 答案为 $4$

以上都不是直接输出 $4$ 即可。

# Code
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=2e5+10;
const int inf=LONG_LONG_MAX;
int n,q,m,p,flg;
char s[maxn];
int cnt[maxn][200];
vector<int>g[maxn];
struct SA{
	int s[maxn];
	int m,p;
	int x[maxn],y[maxn],last[maxn],dbf[maxn],t[maxn];
	int sa[maxn],rnk[maxn],height[maxn],st[maxn][30];
	int cmp(int x,int y,int k){
		return last[x]==last[y]&&last[x+k]==last[y+k];
	}
	void init(){
		m=200;
		p=0;
		memset(t,0,sizeof(t));
		memset(height,0,sizeof(height)); 
		memset(x,0,sizeof(x));
		for(int i=1;i<=n;i++)t[x[i]=s[i]]++;
		for(int i=1;i<=m;i++)t[i]+=t[i-1];
		for(int i=n;i>=1;i--)dbf[t[x[i]]--]=i;
		for(int k=1;k<=n;k<<=1,m=p){
			p=0;
			for(int i=n-k+1;i<=n;i++)y[++p]=i;
			for(int i=1;i<=n;i++){
				if(dbf[i]>k)y[++p]=dbf[i]-k;
			}
			memset(t,0,sizeof(t));
			for(int i=1;i<=n;i++)t[x[y[i]]]++;
			for(int i=1;i<=m;i++)t[i]+=t[i-1];
			for(int i=n;i>=1;i--)dbf[t[x[y[i]]]--]=y[i];
			memcpy(last,x,sizeof(x));
			p=0;
			for(int i=1;i<=n;i++){
				x[dbf[i]]=cmp(dbf[i],dbf[i-1],k)?p:++p;
			}
			if(p==n)break;
		}
		for(int i=1;i<=n;i++){
			sa[i]=dbf[i];
			rnk[i]=x[i];
		}
		p=0;
		for(int i=1;i<=n;i++){
			if(p)p--;
			int j=sa[rnk[i]-1];
			while(i+p<=n&&j+p<=n&&s[i+p]==s[j+p])p++;
			height[rnk[i]]=p;
			st[rnk[i]][0]=height[rnk[i]];
		}
		for(int j=1;j<=25;j++){
			for(int i=1;i+(1<<j)-1<=n;i++){
				st[i][j]=min(st[i][j-1],st[i+(1<<j-1)][j-1]);
			}
		}
	}
	int get(int l,int r){
		l=rnk[l],r=rnk[r];
		if(l>r)swap(l,r);
		if(l==r)return n-sa[l]+1;
		l++;
		int k=__lg(r-l+1);
		return min(st[l][k],st[r-(1<<k)+1][k]); 
	}
}A,B;
struct DSU{
	int fa[maxn],val[maxn];
	void init(){
		for(int i=1;i<=n+1;i++){
			fa[i]=i;
			val[i]=0x3f3f3f3f;
		}
	}
	int find(int x){
		if(x==fa[x])return x;
		return fa[x]=find(fa[x]);
	}
	void update(int l,int r,int k){
		if(l>r)return ;
		int p=find(l);
		while(p<=r){
			val[p]=k;
			fa[p]=p+1;
			p=find(p);
		}
	}
}pre,suf;
int st[maxn][25];
void init(){
	for(int i=1;i<=n;i++){
		A.s[i]=s[i];
		B.s[i]=s[n-i+1];
	}
	A.init();
	B.init();
	pre.init();
	suf.init();
	for(int i=1;i<=n;i++){
		cnt[i][s[i]]++;
	}
	for(int i=1;i<=n;i++){
		for(int j='a';j<='z';j++){
			cnt[i][j]+=cnt[i-1][j];
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j*j<=i;j++){
			if(i%j==0){
				if(j!=i)g[i].push_back(j);
				if(i/j!=i&&i/j!=j)g[i].push_back(i/j);
			}
		}
	}
	for(int len=1;len*2<=n;len++){
		for(int i=len,j=len*2;j<=n;i+=len,j+=len){
			int lcp=A.get(i,j);
			int lcs=B.get(n-i+1,n-j+1);
			int l=i-lcs+1,r=j+lcp-1;
			pre.update(l,r-2*len+1,2*len);
			suf.update(l+2*len-1,r,2*len);
		}
	}
	for(int i=1;i<=n;i++)st[i][0]=i+pre.val[i]-1;
	for(int j=1;j<=20;j++){
		for(int i=1;i+(1<<j)-1<=n;i++){
			st[i][j]=min(st[i][j-1],st[i+(1<<j-1)][j-1]);
		}
	}
}
int solve1(int l,int r){
	flg=1;
	for(int i='a';i<='z';i++){
		if(cnt[r][i]-cnt[l-1][i]>1)flg=0;
	}
	return flg;
}
int solve2(int l,int r){
	flg=0;
	for(int i=0;i<g[r-l+1].size();i++){
		if(A.get(l,l+g[r-l+1][i])>=r-l+1-g[r-l+1][i]){
			flg=1;
			break;
		}
	}
	return flg;
}
int solve3(int l,int r){
	if(pre.val[l]<=r-l+1||suf.val[r]<=r-l+1){
		return 1;
	}
	int sq=sqrt(n);
	for(int i=1;i<=sq&&i<r-l+1;i++){
		if(A.get(l,r-i+1)>=i&&2*i<=r-l+1)return 1;
	}
	int res=0x3f3f3f3f;
	for(int i=max(1ll,A.rnk[l]-sq+1);i<=min(n,A.rnk[l]+sq-1);i++){
		int p=A.sa[i];
		if(p>l&&p<=r&&A.get(l,p)>=r-p+1)res=min(res,r-p+1);
	}
	if(res*2<=r-l+1)return 1;
	return 0;
}
int get(int l,int r){
	if(l>r)return 0x3f3f3f3f;
	int k=__lg(r-l+1);
	return min(st[l][k],st[r-(1<<k)+1][k]);
}
int solve4(int l,int r){
	if((cnt[r-1][s[l]]-cnt[l][s[l]])||(cnt[r-1][s[r]]-cnt[l][s[r]]))return 1;
	if(get(l+1,r-1)<r)return 1;
	return 0;
}
signed main(){
	scanf("%lld",&n);
	scanf("%s",s+1);
	init();
	scanf("%lld",&q);
	while(q--){
		int l,r;
		scanf("%lld%lld",&l,&r);
		if(solve1(l,r))puts("-1");
		else if(solve2(l,r))puts("1");
		else if(solve3(l,r))puts("2");
		else if(solve4(l,r))puts("3");
		else puts("4");
	}

	return 0;
}
```

---

## 作者：Alex_Wei (赞：7)

- Upd on 2022.8.28：修改表述。

> [CF1043G Speckled Band](https://www.luogu.com.cn/problem/CF1043G)

易知答案不超过 $4$，因为若出现两个相等的字符，可以用 $bacad$ 的方式分割字符串。因此我们尝试对每种情况分别讨论一下，令 $t = s_{l\sim r}$。

显然，答案为 $-1$ 当且仅当 $t$ 不包含相同字符。

若答案为 $1$，则 $t$ 有整除它长度的周期，等价于 $t$ 有长为 $|t| - d$ 的 border。枚举因数判一下即可，用哈希或各种后缀字符串结构均可。

若答案是 $2$，则 $t$ 必然形如 $aba$，$aab$ 或 $abb$：若 $t$ 存在 border 则存在不相交 border，直接把 border 割来即可；当 $t$ 不存在 border 时，它的两端不同，形如 $a * b$。若形如 $ab * ab$ 则存在 border，矛盾，因此形如 $aa * b$ 或 $a * bb$，可转化成 $aab$ 或 $abb$。

$aba$ 这种情况有些棘手，我们放在最后讨论。$aab$ 和 $baa$ 本质上是一样的，可以通过 “优秀的拆分” 枚举长度 + 设置关键点的套路求出所有形如 $aa$ 的字符串的出现位置，形成共 $n\ln n$ 个区间。维护 $lft_i$ 表示从 $i$ 开始最短的形如 $aa$ 的字符串长度，$rt_i$ 则表示以 $i$ 结尾的。每个区间相当于为 $lft$ 和 $rt$ 区间 $\rm checkmin$。从小到大枚举长度，并查集维护。

若答案为 $3$，首先两端必然不等，形如 $a * b$。若 $*$ 中出现 $a$ 或 $b$，那么直接 $abcb$ 或者 $acab$ 即可。只需判 $s_l$ 和 $s_r$ 是否在 $s_{l + 1\sim r - 1}$ 当中出现过。否则根据出现次数 $\geq 2$ 的限制，只能为 $ac \cdots cb$，简化为 $accb$。因为维护了 $lft$ 这个信息，直接判断是否有 $\min\limits_{i = l} ^ r (i + lft_i - 1) \leq r$ 即可。

若上述条件均不符合，则答案为 $4$。

最后解决一个遗留问题：求一个子串是否存在 border。当然这可以通过 “border 的四种求法” 的 border 论或 SAM + 树剖解决，但因为只需判断 border 的存在性，所以存在一个优美且巧妙的根号做法。

若 border 相交，则必然形成长度更短的 border。因此我们不妨 **钦定 border 不交**，得到根号分治做法：若 border 长度小于 $\sqrt n$，直接枚举。若 border 长度不小于 $\sqrt n$，那么它在整个字符串中的出现次数不超过 $\sqrt n$，可在后缀数组上枚举 $l$ 后缀的排名的半径为 $\sqrt n$ 的排名邻域判断。

时间复杂度 $\mathcal{O}(n\log n + q\sqrt n)$，但是很优美。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define fi first
#define se second
#define TIME 1e3 * clock() / CLOCKS_PER_SEC
bool Mbe;
constexpr int K = 18;
constexpr int N = 2e5 + 5;
char s[N];
int n, q, lg[N], nxt[N], pre[N], pos[128], st[K][N];
struct SA {
  int sa[N], rk[N], ork[N], buc[N], id[N], mi[K][N];
  bool cmp(int a, int b, int w) {return ork[a] == ork[b] && ork[a + w] == ork[b + w];}
  void build(char *s) {
    int m = 1 << 7, p = 0;
    for(int i = 1; i <= n; i++) buc[rk[i] = s[i]]++;
    for(int i = 1; i <= m; i++) buc[i] += buc[i - 1];
    for(int i = n; i; i--) sa[buc[rk[i]]--] = i;
    for(int w = 1; ; w <<= 1, m = p, p = 0) {
      for(int i = n - w + 1; i <= n; i++) id[++p] = i;
      for(int i = 1; i <= n; i++) if(sa[i] > w) id[++p] = sa[i] - w;
      memset(buc, 0, sizeof(buc));
      memcpy(ork, rk, sizeof(rk));
      p = 0;
      for(int i = 1; i <= n; i++) buc[rk[i]]++;
      for(int i = 1; i <= m; i++) buc[i] += buc[i - 1];
      for(int i = n; i; i--) sa[buc[rk[id[i]]]--] = id[i];
      for(int i = 1; i <= n; i++) rk[sa[i]] = cmp(sa[i - 1], sa[i], w) ? p : ++p;
      if(p == n) break;
    }
    for(int i = 1, k = 0; i <= n; i++) {
      if(k) k--;
      while(s[i + k] == s[sa[rk[i] - 1] + k]) k++;
      mi[0][rk[i]] = k;
    }
    for(int i = 1; i <= lg[n]; i++)
      for(int j = 1; j + (1 << i) - 1 <= n; j++)
        mi[i][j] = min(mi[i - 1][j], mi[i - 1][j + (1 << i - 1)]);
  }
  int lcp(int a, int b) {
    assert(a != b);
    if((a = rk[a]) > (b = rk[b])) swap(a, b);
    int d = lg[b - a++];
    return min(mi[d][a], mi[d][b - (1 << d) + 1]);
  }
} sa, rev;
struct dsu {
  int fa[N], val[N];
  void init() {
    for(int i = 1; i <= n + 1; i++) fa[i] = i; // n -> n + 1
    memset(val, 0x3f, sizeof(val)); // add this line
  }
  int find(int x) {return fa[x] == x ? x : fa[x] = find(fa[x]);}
  void modify(int l, int r, int v) {
    if(l > r) return; // add this line
    while(1) {
      int p = find(l);
      if(p > r) break;
      val[p] = v, fa[p] = p + 1;
    }
  }
} lft, rt;
bool Med;
int main() {
  fprintf(stderr, "%.3lf MB\n", (&Mbe - &Med) / 1048576.0);
  #ifdef ALEX_WEI
    FILE* IN = freopen("1.in", "r", stdin);
    FILE* OUT = freopen("1.out", "w", stdout);
  #endif
  ios::sync_with_stdio(0);
  cin >> n >> s + 1;
  for(int i = 2; i <= n; i++) lg[i] = lg[i >> 1] + 1;
  for(int i = 1; i <= n; i++) pre[i] = pos[s[i]], pos[s[i]] = i;
  memset(pos, 0x3f, sizeof(pos)); // 0 -> 0x3f
  for(int i = n; i; i--) nxt[i] = pos[s[i]], pos[s[i]] = i;
  sa.build(s);
  reverse(s + 1, s + n + 1);
  rev.build(s);
  lft.init(), rt.init();
  for(int i = 1; i * 2 <= n; i++)
    for(int p = i, q = i + i; q <= n; p += i, q += i) {
      int L = rev.lcp(n - p + 1, n - q + 1), R = sa.lcp(p, q);
      int l = p - L + 1, r = q + R - 1;
      lft.modify(l, r - 2 * i + 1, i * 2);
      rt.modify(l + 2 * i - 1, r, i * 2);
    }
  for(int i = 1; i <= n; i++) st[0][i] = i + lft.val[i] - 1;
  for(int i = 1; i <= lg[n]; i++)
    for(int j = 1; j + (1 << i) - 1 <= n; j++)
      st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << i - 1)]);
  int B = 300;
  cin >> q;
  for(int i = 1; i <= q; i++) {
    int l, r, L;
    cin >> l >> r, L = r - l + 1;
    bool found = 0;
    for(int j = l; j < r && !found; j++) found |= nxt[j] <= r;
    if(!found) {cout << "-1\n"; continue;}
    found = 0;
    for(int d = 1; d * d <= L; d++)
      if(L % d == 0) {
        found |= sa.lcp(l, l + d) >= L - d;
        if(d != 1) found |= sa.lcp(l, l + L / d) >= L - L / d;
      }
    if(found) {cout << "1\n"; continue;}
    if(l + lft.val[l] - 1 <= r || r - rt.val[r] + 1 >= l) {cout << "2\n"; continue;}
    int lim = min(L - 1, B);
    for(int i = 1; i <= lim; i++) found |= sa.lcp(l, r - i + 1) >= i;
    if(found) {cout << "2\n"; continue;}
    int lcp = N;
    for(int i = sa.rk[l] - 1; i && !found; i--) {
      if(sa.mi[0][i + 1] < B) break;
      int q = sa.sa[i];
      lcp = min(lcp, sa.mi[0][i + 1]);
      found |= q > l && q <= r && q + lcp - 1 >= r;
    }
    lcp = N;
    for(int i = sa.rk[l] + 1; i <= n && !found; i++) {
      if(sa.mi[0][i] < B) break;
      int q = sa.sa[i];
      lcp = min(lcp, sa.mi[0][i]);
      found |= q > l && q <= r && q + lcp - 1 >= r;
    }
    if(found) {cout << "2\n"; continue;}
    if(nxt[l] <= r || pre[r] >= l) {cout << "3\n"; continue;}
    int d = lg[L];
    if(min(st[d][l], st[d][r - (1 << d) + 1]) <= r) cout << "3\n";
    else cout << "4\n";
  }
  cerr << TIME << " ms\n";
  return 0;
}
/*
2022/8/28
author: Alex_Wei
start coding: 6:44
finish debugging: 7:40
*/
```

---

## 作者：Acee (赞：4)

首先，比较显然，答案最多为 4，因为更多不会最优，最多形如 $\text{AbCbD}$。

然后考虑每一种情况:

1. 无解

那么字母一定互不相同，对于每个字母开个前缀和统计一下。

2. 答案为 1

那么这个子串一定是循环节。

根据 WPL 周期引理，只需枚举素因子，然后等比数列求 hash 和来判断即可。

时间复杂度：$O(\log n)$。

3. 答案为 2

又分为两种

- 形如 $\text{AAB}$ 与 $\text{BAA}$。

就是前后缀形如 $\text{AA}$。

记 $f_i$ 为以 $i$ 开头的最短的形如 $\text{AA}$ 的长度。

显然扫描线，枚举 $A$ 的长度，然后找出关键点。

显然这是 $O(n \ln n)$ 的，随便拿一个线段树之类的数据结构更新。

- 形如 $\text{ABA}$

问题转为求解子串最小 border。

考虑平衡规划。

记 $\text{A}$ 长度为 $n$。

- $n \leq \sqrt {|S|}$

暴力枚举，hash 判断即可。

- $n \ge \sqrt {|S|}$

出现次数不超过 $\sqrt {|S|}$ 次。

枚举 SA 中 $l$ 后缀附近的 $\sqrt {|S|}$ 个后缀，用 hash 值判定。

3. 答案为 3

也有两种情况

- 形如 $\text{ABAC}$ 与 $\text{BACA}$

二分与前缀和判定即可。

- 形如 $\text{BAAC}$

像第 2 种情况一样判定是否为 $\text{AA}$ 即可。

4. 答案为 4

前面都不是，那么答案为 4。

---

## 作者：yinianxingkong (赞：3)

# [CF1043G](https://www.luogu.com.cn/problem/CF1043G)

## 前言

拖了几天才做完……太蒻了……

字符串实在是太难了 qwq。

这题可以说是后缀数组的综合运用了，做完后对后缀数组的理解会加深很多。

~~作者自信地认为这篇题解十分详细。~~

注意，本文中大写字母表示字符串或某段子串，小写字母表示某个字符。

## 解法分析

- ps：解法分析只会讲解大框架，并不会仔细讲解某些技巧的实现，可以到实现部分查看。

题意很清楚了，划分子串使不同段尽量少，输出最少段数，没有相同则输出 $-1$。

我们令 $l$、$r$ 表示子串的左右端点。

发现完全不会……

划分子串想到贪心，考虑先合法再最优。然后想一下哪种情况是有解的：

$$aa$$

是的，有两个字符就有解。那么，在有解的情况下：

$$AaBaC$$

也就是说，只要有解，就会有 $ans \le 4$。

这不是诈骗吗 QnQ。

然后就可以分类讨论：

$ans = -1$，直接判子串是否含有相同字符。

$ans = 1$，即判断子串是否含有循环节。

$ans = 2$，这又分为两种情况。

一种是在前后缀分别重复出现两次，即：

$$AAB/BAA$$

令 $f_i$ 表示以 $i$ 开始的 $AA$ 串最近的结尾，$g_i$ 表示以 $i$ 结尾的 $AA$ 串最近的开始，即判 $f_l \le r \vee g_r \ge l$。

另一种是在前后缀各出现两次，即：

$$ABA$$

判断是否存在 `border` 即可。

$ans = 3$，分两种情况。

一种是分别隔开两个不同的子串，即：

$$ABAC/BACA$$

我明确地告诉你，直接判我不会……

但是我们刚刚已经判过 $ans = 2$ 的情况了，不用看它“进化”的情况了。

也就是说，完全不用担心 $A$ 的长度，只要能分割开不同子串就可以了。直接判 $ch_l$ 和 $ch_r$ 是否在串内还出现过就行了。

而另一种就是内部隔开，即：

$$BAAC$$

这种结合 $f$ 数组直接判就好了。

还有一种就是：

$$AABC/ABCA/BCAA$$

~~欸？不是两种吗？~~

其实不用判断这种情况，因为把 $BC$ 拼一起就“进化”成 $ans = 2$ 的情况了……

最后就是 $ans = 4$ 的情况……

傻了吗？不会 else？

~~怎么 3 和 4 还简单一点 qwq。~~

## 实现

如果你看完思路就高兴地开始敲代码，你会发现根本无从下手……

首先是解决判断子串内是否存在两个相同字符的问题，记一个 $cnt_{i,j}$ 表示前 $i$ 位有多少个字符 $j$ 即可。

然后是判断子串是否有循环节，即判断是否有周期整除子串长度。可以枚举约数，然后判断前缀是否是周期。具体来说，令循环节枚举到长度 $len$，判 $LCP(S[l...r],S[l+len...r])=r-l+1-len$ 即可。综上，时间复杂度就是 $O(\sqrt {n}) + O(1) = O(\sqrt {n})$。当然，如果你想继续优化，可以根据 WPL（即弱周期引理）得出枚举质因子即可，复杂度 $O(\log {n})$，注意特判一的情况。~~但我比较懒就直接枚举因子了\kk~~

对 $f$ 数组的处理是经典的，可以参见[这道题](https://www.luogu.com.cn/problem/P1117)。

特化一下，枚举关键点，求完 $LCP$ 和 $LCS$ 后，求出最近的 $AA$ 即可。

话是这么说，实际处理起来还是有点难搞。回顾一下上面那道题是怎么处理的，其实是一个关键点的影响转成了两端区间加，只是我们发现因为只有一次查询所以用差分优化。而本题亦是如此，可以转化为区间 `chkmin` 操作用摊还线段树维护。再仔细观察，我们若从小到大枚举关键点，就会特化为更加经典的区间推平，可以用并查集做到均摊 $O(1)$。

对于判断是否有 `border`，可以特化为判断是否存在最小/大的 `border`。在这道题里，判断是否有最小 `border` 相对容易一点。具体来说，因为 `border` 的 `border` 还是 `border`，这就导致 `border` 太多就会产生长度更小的 `border`。

容易看出，最小 `border` 的长度与出现次数呈反比，可以平衡规划。再具体一点，设 `border` 长度为 $len$，出现次数为 $count$。

当 $len \le \sqrt n$ 时，我们暴力枚举这个范围内的 `border` 再用 `SA` 就可以 $O(1)$ 判。

当 $len \ge \sqrt n$ 时，$count \le \sqrt n$。显然，子串的子串还是子串，并且 `border` 还是前缀。所以，以 `border` 开头的后缀的排名一定与我们要查询的子串所在后缀的排名差不远。事实上，因为 $count \le \sqrt n$，我们只需要查这个子串所在后缀排名 $\sqrt n$ 左右的后缀就可以了。

~~感觉就是缝合怪。~~

## 代码

真挺难打的……

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace TYX_YNXK{
    #define il inline
    #define bl bool
    #define ll long long
    #define vd void
    #define M 200005
    #define INF 0x3f3f3f3f3f3f3f3f
    #define DEBUG cout<<"You are right,but you are wrong"<<'\n'
    #define END cout<<"You are right,but you are right now"<<'\n'
    #define MN(l,r) (((l)>(r))?(0x3f3f3f3f):(min(mn[l][__lg(r-(l)+1)],mn[r-(1<<(__lg(r-(l)+1)))+1][__lg(r-(l)+1)])))
	int n,f[M],g[M],cnt[M][26],mn[M][21],q,lim;
	char ch[M];
    struct SA{
		int m,sa[M],rk[M],id[M],key[M],cnt[M],pre[M],height[M],st[M][21];
		#define cmp(x,y,w) pre[x]==pre[y]&&pre[x+w]==pre[y+w]
	//	#define idx(c) (c<58?c-47:c<91?c-54:c-60)
		#define idx(c) (c-96)
		il vd init(){
//			m=62;
			m=26;
			for(int i=1;i<=n;++i) ++cnt[rk[i]=idx(ch[i])];
			for(int i=1;i<m;++i) cnt[i+1]+=cnt[i];
			for(int i=n;i;--i) sa[cnt[rk[i]]--]=i;
			for(int w=1,p=0;;w<<=1,m=p,p=0){
				for(int i=n;i>n-w;--i) id[++p]=i;
				for(int i=1;i<=n;++i) if(sa[i]>w) id[++p]=sa[i]-w;
				for(int i=1;i<=m;++i) cnt[i]=0;
				for(int i=1;i<=n;++i) ++cnt[key[i]=rk[id[i]]];
				for(int i=1;i<m;++i) cnt[i+1]+=cnt[i];
				for(int i=n;i;--i) sa[cnt[key[i]]--]=id[i];
				memcpy(pre+1,rk+1,n*sizeof(int));p=0;
				for(int i=1;i<=n;++i) rk[sa[i]]=cmp(sa[i],sa[i-1],w)?p:++p;
				if(p==n) break;
			}
			for(int i=1,k=0;i<=n;++i){
				if(!rk[i]) continue;
				if(k) --k;
				while(ch[i+k]==ch[sa[rk[i]-1]+k]) ++k;
				height[rk[i]]=k;
			}
			for(int i=1;i<=n;i++) st[i][0]=height[i];
			for(int j=1;(1<<j)<=n;j++){
				for(int i=1;i+(1<<j)-1<=n;i++){
					st[i][j]=min(st[i][j-1],st[i+(1<<j-1)][j-1]);
				}
			}
		}
		il int RMQ(int l,int r){// new meaning: s[l...n] to s[r...n]
			if(l==r) return n-l+1;
			l=rk[l],r=rk[r];
			if(l>r) swap(l,r);
			int k=__lg(r-l++);
			return min(st[l][k],st[r-(1<<k)+1][k]);
		}
	}A,B;
	struct DSU{
		int fa[M],val[M];
		int find(int x){
			if(fa[x]==fa[fa[x]]) return fa[x];
			return fa[x]=find(fa[x]);
		}
		il vd update(int l,int r,int v){
			if(l>r) return;
			int k=find(l);
			while(k<=r){
				val[k]=v,fa[k]=k+1;
				k=find(l);
			}
		}
	}lt,rt;
	il bl solve1(int l,int r){
		for(int i=0;i<26;i++) if(cnt[r][i]-cnt[l-1][i]>1) return 0;
		return 1;
	}
	il bl solve2(int l,int r){
		int len=r-l+1;
		if(cnt[r][ch[l]-'a']-cnt[l-1][ch[l]-'a']==len) return 1;
		for(int i=2;i*i<=len;i++){
			if(len%i==0){
				if(A.RMQ(l,l+i)>=len-i) return 1;
				if(A.RMQ(l,l+len/i)>=len-len/i) return 1;
			}
		}
		return 0;
	}
	il bl solve3(int l,int r){
		if(f[l]<=r||g[r]>=l) return 1;
		for(int i=1;i<=min(lim,r-l);i++) if(A.RMQ(l,r-i+1)>=i) return 1;
		int lcp=n;
		for(int i=max(1,A.rk[l]-lim+1);i<=min(n,A.rk[l]+lim-1);i++){
			int &tmp=A.sa[i];
			if(tmp>l&&tmp<=r&&A.RMQ(l,tmp)>=r-tmp+1) lcp=min(lcp,r-tmp+1);
		}
		return lcp*2<=r-l+1;
	}
	il bl solve4(int l,int r){
		if(cnt[r][ch[l]-'a']-cnt[l][ch[l]-'a']||cnt[r-1][ch[r]-'a']-cnt[l-1][ch[r]-'a']) return 1;
		return MN(l+1,r-1)<r;
	}
	signed main(){
		scanf("%d%s%d",&n,ch+1,&q);A.init();lim=ceil(sqrt(n));
		for(int i=1;i<=n;i++) memcpy(cnt[i],cnt[i-1],sizeof cnt[i]),++cnt[i][ch[i]-'a'];
		for(int i=1,j=n;i<j;i++,j--) swap(ch[i],ch[j]);B.init();
		for(int i=1,j=n;i<j;i++,j--) swap(ch[i],ch[j]);
		for(int i=1;i<=n+1;i++) lt.fa[i]=rt.fa[i]=i;
		memset(lt.val,0x3f,sizeof lt.val);
		memset(rt.val,0x3f,sizeof rt.val);
		for(int len=1;(len<<1)<=n;len++){
			for(int i=len;i<=n-len;i+=len){
				int LCS=B.RMQ(n-i+1,n-i-len+1),LCP=A.RMQ(i,i+len);
				lt.update(i-LCS+1,i+LCP-len,len<<1);
				rt.update(i-LCS+(len<<1),i+len+LCP-1,len<<1);
			}
		}
		for(int i=1;i<=n;i++) mn[i][0]=f[i]=i+lt.val[i]-1,g[i]=i-rt.val[i]+1;
		for(int j=1;(1<<j)<=n;j++){
			for(int i=1;i+(1<<j)-1<=n;i++){
				mn[i][j]=min(mn[i][j-1],mn[i+(1<<j-1)][j-1]);
			}
		}
		while(q--){
			int l,r;scanf("%d%d",&l,&r);
			if(solve1(l,r)) puts("-1");
			else if(solve2(l,r)) puts("1");
			else if(solve3(l,r)) puts("2");
			else if(solve4(l,r)) puts("3");
			else puts("4");
		}
        return 0;
    }
}
signed main(){
    TYX_YNXK::main();
    return 0;
}
```

## 后记

欢迎 `hack`！

---

## 作者：kkksx (赞：3)

如果子串中没有字母出现超过一次，那肯定是无解的，否则选择这两个相同字母，答案只可能是在1~4中的一个，下面分情况讨论

注：下面大写字母表示一个字符串，$l_i$表示最大的位置满足$[l_i,i]$是一个AA串，$r_i$类似（就是尽量短的重复两次的串）

令$len = R - L + 1$

1. ans=1：即AAAA...，枚举len的所有质因子然后check是否存在这个长度的周期

2. ans=2：即AAB、BAA、ABA，前两者可以用$l,r$数组判断；后者需要求出该子串的最短border

3. ans=3：即ABAC、BACA、BAAC，前两者可以发现A是单个字母时比其他情况更好，所以变成判断首尾字母是否在中间出现，前缀和即可；后者即中间某个位置的$r_i < R$，可以用ST表维护的$r_i$的最小值

4. ans=4：前面的都不是那就是4了

**求$l,r$**：用 [NOI2016]优秀的拆分 的做法即可求出所有AA串，然后随便乱搞一下就可以弄出$l,r$数组

**求border**：

有一个结论：先判断有没有长度为$1$~$\sqrt{len}$的border，如果没有，那么最短的border与原串的后缀排名小于$\sqrt{len}$

证明自己画图比较好理解：如果它们的距离超过了$\sqrt{len}$，那么他们中间就夹了$\sqrt{len}$个串，且这些串的前缀都是border，一定会有重叠，两个相同的border重叠之后一定可以得到一个更短的border，说明这个border不是最短的，与我们要求的矛盾

#### Code

```cpp
#include<bits/stdc++.h>
#define N 200005
using namespace std;
typedef unsigned long long ull;
const ull base = 1000000007;
int n,q,lg[N];
int ar[N],al[N],mn[N][20];
int sum[N][26];
char a[N];

template <class T> inline T Max(T a,T b) { return a > b ? a : b; }
template <class T> inline T Min(T a,T b) { return a < b ? a : b; }
struct SA
{
	int rk[N],sa[N],tp[N],h[N],tot[N];
	int mn[N][20];
	void radixsort()
	{
		for(int i=0;i<=n;++i) tot[i] = 0;
		for(int i=1;i<=n;++i) tot[rk[i]]++;
		for(int i=1;i<=n;++i) tot[i] += tot[i - 1];
		for(int i=n;i>=1;--i) sa[tot[rk[tp[i]]]--] = tp[i];
	}
	void getsa()
	{
		for(int i=1;i<=n;++i) rk[i] = a[i] - 'a' + 1,tp[i] = i;
		radixsort();
		for(int t=1;t<n;t<<=1)
		{
			int p = 0;
			for(int i=1;i<=t;++i) tp[++p] = n - t + i;
			for(int i=1;i<=n;++i) if(sa[i] > t) tp[++p] = sa[i] - t;
			radixsort(); for(int i=1;i<=n;++i) swap(rk[i],tp[i]);
			rk[sa[1]] = p = 1;
			for(int i=2;i<=n;++i) 
			  rk[sa[i]] = (tp[sa[i - 1]] == tp[sa[i]] && tp[sa[i - 1] + t] == tp[sa[i] + t]) ? p : ++p;
			if(n == p) break;
		}
	}
	void geth()
	{
		int ht = 0;
		for(int i=1;i<=n;++i) rk[sa[i]] = i;
		for(int i=1;i<=n;++i)
		{
			int p = sa[rk[i] - 1];
			while(a[i + ht] == a[p + ht]) ++ht;
			h[rk[i]] = ht;
			ht = Max(0,ht - 1);
		}
	}
	int lcp(int l,int r)
	{
		if(l == r) return n - l + 1;
		l = rk[l]; r = rk[r];
		if(l > r) swap(l,r); ++l;
		int len = lg[r - l + 1];
		return Min(mn[l][len] , mn[r - (1 << len) + 1][len]);
	}
	void init()
	{
		getsa(); geth();
		for(int i=1;i<=n;++i) mn[i][0] = h[i];
		for(int t=1;t<20;++t)
		  for(int i=1;i+(1<<(t-1))<=n;++i)
			mn[i][t] = Min(mn[i][t - 1],mn[i + (1<<(t-1))][t - 1]);
	}
}sa;

int pre[N],suf[N];
int sig1[N << 2],sig2[N << 2];
ull qp[N],hah[N];
void modify(int *sig,int rt,int l,int r,int x,int y,int v)
{
	if(x < 1) x = 1; if(y > n) y = n;
	if(x <= l && r <= y) return (void)(sig[rt] = Min(sig[rt],v));
	int mid = (l + r) >> 1;
	if(x <= mid) modify(sig,rt<<1,l,mid,x,y,v);
	if(y > mid) modify(sig,rt<<1|1,mid + 1,r,x,y,v);
}
void dfs1(int rt,int l,int r,int mn)
{
	mn = Min(mn,sig1[rt]);
	if(l == r) return (void)(ar[l] = l + mn * 2 - 1);
	int mid = (l + r) >> 1;
	dfs1(rt<<1,l,mid,mn);
	dfs1(rt<<1|1,mid + 1,r,mn);
}
void dfs2(int rt,int l,int r,int mn)
{
	mn = Min(mn,sig2[rt]);
	if(l == r) return (void)(al[l] = l - mn * 2 + 1);
	int mid = (l + r) >> 1;
	dfs2(rt<<1,l,mid,mn);
	dfs2(rt<<1|1,mid + 1,r,mn);
}
ull hsh(int l,int r) { return (l < 1 || r > n) ? (ull)rand() * rand() : hah[r] - hah[l - 1] * qp[r - l + 1]; }
void getr()
{
	srand((unsigned)time(NULL));
	qp[0] = 1; for(int i=1;i<N;++i) qp[i] = qp[i - 1] * base;
	memset(pre,0,sizeof(pre));
	memset(suf,0,sizeof(suf));
	memset(sig1,50,sizeof(sig1));
	memset(sig2,50,sizeof(sig2));
	for(int i=1;i<=n;++i) hah[i] = hah[i - 1] * base + a[i];

	for(int k=1;k<=n;++k)
	{
		for(int i=1;i+k<=n;i+=k)
		{
			int now = i,nxt = i + k;
			int l,r,pr = 0,sf = 0;
			l = 1; r = k;
			while(l <= r)
			{
				int mid = (l + r) >> 1;
				if(hsh(now - mid + 1,now) == hsh(nxt - mid + 1,nxt)) l = mid + 1,pr = mid;
				else r = mid - 1;
			}
			l = 1; r = k;
			while(l <= r)
			{
				int mid = (l + r) >> 1;
				if(hsh(now,now + mid - 1) == hsh(nxt,nxt + mid - 1)) l = mid + 1,sf = mid;
				else r = mid - 1;
			}
			int len = sf + pr - (k + 1) + 1;
			if(len <= 0) continue;
			//++pre[nxt - pr + 1 - k]; --pre[now + sf - k + 1];
			//++suf[nxt - pr + 1 + k - 1]; --suf[now + sf + k];
			modify(sig1,1,1,n,nxt - pr + 1 - k,now + sf - k,k);
			modify(sig2,1,1,n,nxt - pr + 1 + k - 1,now + sf + k - 1,k);
		}
	}
	dfs1(1,1,n,N); dfs2(1,1,n,N);
}

void init()
{
	lg[0] = -1; for(int i=1;i<N;++i) lg[i] = lg[i >> 1] + 1;
	sa.init();
	for(int i=1;i<=n;++i)
	{
		for(int j=0;j<26;++j) sum[i][j] = sum[i - 1][j];
		++sum[i][a[i] - 'a'];
	}
	getr();
	for(int i=1;i<=n;++i) mn[i][0] = ar[i];
	for(int t=1;t<20;++t)
	  for(int i=1;i+(1<<(t-1))<=n;++i)
		mn[i][t] = Min(mn[i][t - 1],mn[i + (1<<(t-1))][t - 1]);
}
int query(int l,int r)
{
	int len = lg[r - l + 1];
	return Min(mn[l][len] , mn[r - (1 << len) + 1][len]);
}
int border(int l,int r)
{
	int len = r - l + 1,sqr = sqrt(n);
	for(int i=1;i<=sqr&&i<len;++i) if(sa.lcp(l,r - i + 1) >= i) return i;
	int ret = N;
	for(int i=Max(1,sa.rk[l]-sqr+1);i<=Min(n,sa.rk[l]+sqr-1);++i)
	{
		int loc = sa.sa[i];
		if(loc <= l || loc > r) continue;
		if(sa.lcp(l,loc) >= r - loc + 1) ret = Min(ret,r - loc + 1);
	}
	return ret;
}
int solve0(int l,int r)
{
	int t[26] = {0};
	for(int i=l;i<=min(r,l + 27);++i) ++t[a[i] - 'a'];
	for(int i=0;i<26;++i) if(t[i] > 1) return 0;
	return 1;
}
int solve1(int l,int r)
{
	int len = r - l + 1;
	for(int i=2;i*i<=len;++i)
	{
		if(len % i == 0)
		{
			while(len % i == 0) len /= i;
			if(sa.lcp(l,l + (r-l+1) / i) >= r - l + 1 - (r-l+1) / i) return 1;
		}
	}
	if(len != 1) if(sa.lcp(l,l + (r-l+1) / len) >= r - l + 1 - (r-l+1) / len) return 1;
	return 0;
}
int solve2(int l,int r)
{
	if(ar[l] <= r) return 1;
	if(al[r] >= l) return 1;
	return (border(l,r) * 2 <= (r - l + 1));
}
int solve3(int l,int r)
{
	if(sum[r][a[l] - 'a'] - sum[l][a[l] - 'a'] > 0) return 1;
	if(sum[r - 1][a[r] - 'a'] - sum[l - 1][a[r] - 'a'] > 0) return 1;
	return (query(l + 1,r - 1) < r);
}
int main()
{
	scanf("%d%s%d",&n,a + 1,&q);
	init();
	while(q--)
	{
		int l,r;
		scanf("%d%d",&l,&r);
		if(solve0(l,r)) puts("-1");
		else if(solve1(l,r)) puts("1");
		else if(solve2(l,r)) puts("2");
		else if(solve3(l,r)) puts("3");
		else puts("4");
	}
	return 0;
}

```








---

## 作者：critnos (赞：2)

考虑到 kkksx 大致方向讲的很清楚，我只简述一下本题的 polylog 解法。

### 判断区间是否存在循环节（非本身）

显然，若一个长度不行，那么其因数也不行。

那么枚举 $p$ 为区间长度 $len$ 的质因子，我们只需要判断 $\dfrac {len} p$ 是否可行即可。

即 $[s[l,r-\dfrac {len} p]=[l+\dfrac {len} p,r]]$。

hash 或 SA 之类均可。$O(\log n)$ 单次。

### 判断区间是否存在不重叠的相等前后缀

即判断区间是否存在起点 $\in [\lceil \dfrac {l+r+1} 2\rceil,r] $ 的 border。

可以套用区间 border 的做法。

设 border 的起点为 $i$，那么 $r-i+1\le lcp(l,i)$。

建出反串的 SAM，设点 $i$ 在 SAM 上的位置为 $rk_i$，显然 $r-i+1\le len_{lca(rk_l,rk_i)}$。

扫描线，扫到 $\lceil \dfrac {l+r+1} 2\rceil$ 时加入询问，扫到 $r+1$ 时删除该询问。

那么对于每个 $i$，我们取出所有的满足这个 $i$ 是询问区间 border 的询问即可。

对 parent tree 轻重链剖分，一条到根的路径就被拆成了 $O(\log n)$ 条重链的前缀。

从 $rk_i$ 向上跳重链（优化枚举祖先），假设现在跳到了点 $u$，链顶为 $top_u$，父亲为 $fa_u$，考虑该重链前缀的贡献。

1. $lca(rk_l,rk_i)=u$

显然这类 $rk_l$ 几乎在点 $u$ 的子树内。

断言这个“几乎”是没有影响的，因为这类点之前算过了。这个显然没有影响。

现在 $i,lca$ 是确定的，那么移项得 $r\le len_{lca(rk_l,rk_i)}+i-1$。

那么每次取出子树中的最小值判断即可。

2. $lca(rk_l,rk_i)=v$，$v$ 为 $fa_u \to top_u$ 上的点。

这类 $rk_l$ 在 $v$ 的轻子树内或 $rk_l=v$。

因为 $rk_l$ 显然不在 $v$ 的重子树内，否则之前就算过了。

那么有 $r-len_{lca(rk_l,rk_i)}+1\le i$。

在插入询问的时候枚举包含其的轻子树，显然是 $O(\log n)$ 个。

同理，每次取出链中的最小值判断即可。

那么上面的两类引导我们设计这样一个数据结构，维护序列（上面的用 dfn 拍平），支持在一个位置插入（相当于每个位置是个可重集？），求区间最小元组，删除一个位置的最小值。

小孩都会，每个位置维护个堆，用线段树维护区间最小值即可。

这个的时间复杂度为 $O(n\log^2 n)$。

[CF 评测记录](https://codeforces.com/contest/1043/submission/149364916)

---

## 作者：L_zaa_L (赞：0)

## 分析
首先我们发现答案应该不会超过 $4$，因为再不济也可以将它弄成 $\texttt{bacad}$，除非没用相同的字符，这个是直接输出 $-1$ 就可以了。

答案为 $1$ 的，我们发现应该是一个循环串。判断一个字符串是否有长度为 $i$ 的循环节，只需要判断 $S[1,n-i+1]=S[i,n]$，所以这部分可以直接进行 hash 或者其他各种算法都能过。

答案为 $2$ 的，我们枚举一下情况，就只有形似 $\texttt{aba,aab,baa}$，发现可能需要判平方串，我们考虑使用[优秀的拆分](https://www.luogu.com.cn/problem/P1117)中的找关键点之后判断最长公共后缀和前缀，能得到每个位置开头和结尾最短的平方串，长度大的一定不优，随便用个数据结构就可以得到最小值。

然后剩下一个 $aba$ 这种情况，有点难我们需要考虑找到这个字符串 border，然后我们考虑找到最短的 border，考虑根号分治，小于 $\sqrt{n}$ 的，直接枚举就可以了，然后对于大于等于 $\sqrt{n}$，我们发现，如果两个相等同的 border 相交，如 $\texttt{abc}$（$\texttt{ab}=\texttt{bc}$），那么肯定会有一个长度为 $|b|$，所以并不是最小的，所以相等的 border 最多只会有 $\sqrt{n}$ 级别的个数，然后枚举后缀排序后排名在其周围 $\sqrt{n}$ 级别的位置，肯定包含这个 border。

答案为 $3$ 的，情况有 $\texttt{abac},\texttt{baca},\texttt{baac}$，对于 $\texttt{abac},\texttt{baca}$ 的情况，我们可以让 $a$ 的长度为 $1$，因为如果有长度更大的一定有长度为 $1$ 的方案，所以之间判断 $[l+1,r-1]$ 中有没有跟 $s_l,s_r$ 相等的字符，然后对于 $\texttt{baac}$ 的情况，由于我们前面求出了每个位置开头的最小平方串，所以用个 ST 表求一下区间最小值就可以了。

时间复杂度：$O(n\sqrt{n})$。

## Code

```cpp
#include<bits/stdc++.h>
//#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
//#pragma GCC optimize(2)
//#pragma GCC optimize(3)
//#pragma GCC optimize("Ofast,unroll-loops")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")
//#include <immintrin.h>
//#include <emmintrin.h>
#define ls(x) ((x)*2)
#define rs(x) ((x)*2+1)
#define pii pair<int,int>
#define fi first
#define se second
#define Debug(...) fprintf(stderr, __VA_ARGS__)
#define For(i,a,b) for(int i=a,i##end=b;i<=i##end;i++)
#define Rof(i,a,b) for(int i=a,i##end=b;i>=i##end;i--)
#define rep(i,  b) for(int i=1,i##end=b;i<=i##end;i++)
using namespace std;
const int N=2e5+5,base=999983,Mod=998244353;
//char buf[(1<<21)+5],*p1,*p2;
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
inline void chmx(int &x,int y){(x<y)&&(x=y);}
inline void chmn(int &x,int y){(x>y)&&(x=y);}
inline void Add(int &x,int y){(x=x+y+Mod)%=Mod;}
inline int read(){
	int f=0,x=0;
	char ch=getchar();
	while(!isdigit(ch)){f|=(ch=='-');ch=getchar();}
	while(isdigit(ch)){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return f?-x:x;
}
void print(int n){
    if(n<0){
        putchar('-');
        n*=-1;
    }
    if(n>9) print(n/10);
    putchar(n%10+'0');
}bool SSS;
int n,m,Q,lg[N];
struct SuffixArray {
	char s[N];
	int rak[N],tp[N],tag[N],sa[N];
	int height[N];
	int st[N][18];
	inline void SA(){
		m=250;
	    For(i,0,m) tag[i]=0;
		For(i,1,n) rak[i]=(int)s[i];
		int p=0;
		For(i,1,n)++tag[rak[i]];
		For(i,1,m) tag[i]+=tag[i-1];
		Rof(i,n,1) sa[tag[rak[i]]--]=i;
		for(int k=1;k<=n;k<<=1){
			p=0;
	        For(i,0,m) tag[i]=tp[i]=0;
			For(i,n-k+1,n) tp[++p]=i;
			For(i,1,n)
				if(sa[i]>k)tp[++p]=sa[i]-k;
			For(i,1,m)tag[i]=0;
			For(i,1,n)tag[rak[i]]++;
			For(i,1,m) tag[i]+=tag[i-1];
			Rof(i,n,1) sa[tag[rak[tp[i]]]--]=tp[i],tp[i]=0;
			swap(rak,tp);
			rak[sa[1]]=1;
			p=1;
			For(i,2,n) rak[sa[i]]=(tp[sa[i-1]]==tp[sa[i]]&&tp[sa[i-1]+k]==tp[sa[i]+k])?p:++p;
			m=p;
		}
	}
	inline void GetHeight(){
		int k=0;
		For(i,1,n){
	        if(k) k--;
	        while(s[i+k]==s[sa[rak[i]-1]+k]) ++k;
	        height[rak[i]]=k;
	    }
	}
	inline void RMQ(){ 
		For(i,1,n) st[i][0]=height[i]; 
		For(j,1,17)
			For(i,1,n){
				if(i+(1<<j)-1>n) break;
	            st[i][j]=min(st[i][j-1], st[i+(1<<(j-1))][j-1]);
			}
	}
    inline int rmq(int l,int r){
        int x=rak[l],y=rak[r];
		if(x>y) swap(x,y);x++;
		int k=lg[y-x+1];
		return min(st[x][k],st[y-(1<<k)+1][k]);
    }    
}A,B;
char s[N];
vector<pii>q[N];
int pmn[N],smn[N],mmn[N];
struct STbiao{
	int st[N][18];
	inline void init(){ 
		For(i,1,n) st[i][0]=mmn[i]; 
		For(j,1,17)For(i,1,n){
			if(i+(1<<j)-1>n) break;
            st[i][j]=min(st[i][j-1], st[i+(1<<(j-1))][j-1]);
		}
	}
    inline int rmq(int l,int r){
		int k=lg[r-l+1];
		return min(st[l][k],st[r-(1<<k)+1][k]);
    }
}ST;
struct DSU{
	int fa[N];
	inline void init(){For(i,1,n+1) fa[i]=i;}
	int find(int x){return (fa[x]==x?x:fa[x]=find(fa[x]));}
}Lf,Rf;
inline void solve(){
	For(i,1,n){
		for(int j=i;j+i<=n;j+=i){
			int lcp=A.rmq(j,j+i),lcs=B.rmq(n-j+1,n-j-i+1);
			lcs=min(lcs,i);lcp=min(lcp,i); 
			int len=lcp+lcs-i;
			if(lcp+lcs-1>=i){
				int L=j-lcs+1,R=j-lcs+len;
				if(!q[i].empty()&&(q[i].back()).se>=L-1){
					pii x=q[i].back();q[i].pop_back();
					q[i].push_back({x.fi,R});
				}else q[i].push_back({L,R});
			}
		}
	}Lf.init(),Rf.init();
	For(i,1,n)pmn[i]=smn[i]=n+1;
	For(i,1,n){
		for(auto v:q[i]){
			int L=v.fi,R=v.se;
			int p=Lf.find(L);
			while(p<=R){
				pmn[p]=i;
				Lf.fa[p]=Lf.find(p+1);
				p=Lf.find(p+1);
			}L=v.fi+2*i-1,R=v.se+2*i-1,p=Rf.find(L);
			while(p<=R){
				smn[p]=i;
				Rf.fa[p]=Rf.find(p+1);
				p=Rf.find(p+1);
			}
		}
	}For(i,1,n) mmn[i]=i+2*pmn[i]-1;
	ST.init();
}vector<int>oo[N];
int pre[26][N];
bool TTT;
signed main(){
//	cerr<<(&SSS-&TTT)/1024/1024<<"Mib"<<endl;
	//_base=(_base<<64)/Mod;
	// ios::sync_with_stdio(false);
	// cin.tie(0); cout.tie(0);
//	n=read(),Q=read();
lg[0]=-1;
For(i,1,N-5) lg[i]=lg[i/2]+1;
	n=read();const int BB=(int)sqrt(n);
	scanf("%s",s+1);
	For(i,1,n) A.s[i]=s[i];
	For(i,1,n) B.s[n-i+1]=s[i];
	A.SA();A.GetHeight();A.RMQ();
	B.SA();B.GetHeight();B.RMQ();
	solve();int Q=read();
	For(i,1,n)For(j,2,n/i) oo[i*j].push_back(i);
	For(i,1,n)For(j,0,25)pre[j][i]=pre[j][i-1]+(s[i]==j+'a');
//	For(i,1,n) cout<<pmn[i]<<" ";puts("");
//	For(i,1,n) cout<<smn[i]<<" ";puts("");
	while(Q--){
		int l=read(),r=read();
		bool flag=0;
		For(i,0,25) if(pre[i][r]-pre[i][l-1]>1)flag=1;
		if(!flag){
			puts("-1");
			continue;
		}flag=0;
		for(auto v:oo[r-l+1]){
			if(A.rmq(l,l+v)>=r-l+1-v){flag=1;break;}
		}
		if(flag){puts("1");continue;}
		if(pmn[l]*2<=r-l+1||smn[r]*2<=r-l+1){puts("2");continue;}
		flag=0;
		For(i,1,min((r-l+1)/2,BB)){
			if(A.rmq(l,r-i+1)>=i)flag=1;
		}if(flag){puts("2");continue;}
		For(i,max(1,A.rak[l]-BB+1),min(n,A.rak[l]+BB-1))if(A.sa[i]>l&&A.sa[i]<=r&&(r-A.sa[i]+1)*2<=r-l+1){
			if(A.rmq(l,A.sa[i])>=r-A.sa[i]+1){
				flag=1;break;
			}
		}if(flag){puts("2");continue;}
		if(pre[s[l]-'a'][r-1]-pre[s[l]-'a'][l]||pre[s[r]-'a'][r-1]-pre[s[r]-'a'][l]||ST.rmq(l+1,r-1)<r){puts("3");continue;}
		puts("4");
	}
	
#ifdef LOCAL
    Debug("\nMy Time: %.3lfms\n", (double)clock() / CLOCKS_PER_SEC);
#endif
	return 0;
}
```

---

