# [ABC272F] Two Strings

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc272/tasks/abc272_f

長さ $ N $ の英小文字からなる文字列 $ S,T $ が与えられます。

文字列 $ X $ と整数 $ i $ に対し、$ f(X,i) $ を $ X $ に対して以下の操作を $ i $ 回行い得られる文字列とします。

- $ X $ の先頭の文字を削除し、同じ文字を $ X $ の末尾に挿入する。

$ 0\ \le\ i,j\ \le\ N-1 $ を満たす非負整数の組 $ (i,j) $ のうち、辞書順で $ f(S,i) $ が $ f(T,j) $ より小さいか同じであるものの個数を求めてください。

 辞書順とは？ 辞書順とは簡単に説明すると「単語が辞書に載っている順番」を意味します。より厳密な説明として、英小文字からなる相異なる文字列 $ S,\ T $ の大小を判定するアルゴリズムを以下に説明します。

以下では「 $ S $ の $ i $ 文字目の文字」を $ S_i $ のように表します。また、 $ S $ が $ T $ より辞書順で小さい場合は $ S\ \lt\ T $ 、大きい場合は $ S\ \gt\ T $ と表します。

1. $ S,\ T $ のうち長さが大きくない方の文字列の長さを $ L $ とします。$ i=1,2,\dots,L $ に対して $ S_i $ と $ T_i $ が一致するか調べます。
2. $ S_i\ \neq\ T_i $ である $ i $ が存在する場合、そのような $ i $ のうち最小のものを $ j $ とします。そして、$ S_j $ と $ T_j $ を比較して、$ S_j $ が $ T_j $ よりアルファベット順で小さい場合は $ S\ \lt\ T $ 、そうでない場合は $ S\ \gt\ T $ と決定して、アルゴリズムを終了します。
3. $ S_i\ \neq\ T_i $ である $ i $ が存在しない場合、$ S $ と $ T $ の長さを比較して、$ S $ が $ T $ より短い場合は $ S\ \lt\ T $ 、長い場合は $ S\ \gt\ T $ と決定して、アルゴリズムを終了します。

## 说明/提示

### 制約

- $ 1\ \le\ N\ \le\ 2\ \times\ 10^5 $
- $ S,T $ は英小文字からなる長さ $ N $ の文字列
- $ N $ は整数

### Sample Explanation 1

条件を満たす $ (i,j) $ の組は $ (0,0),(0,2),(2,0),(2,2) $ の $ 4 $ 個があります。 $ (i,j)=(1,2) $ は、$ f(S,i)= $`dba`$ ,f(T,j)= $`bca` であるため条件を満たしません。

## 样例 #1

### 输入

```
3
adb
cab```

### 输出

```
4```

## 样例 #2

### 输入

```
10
wsiuhwijsl
pwqoketvun```

### 输出

```
56```

# 题解

## 作者：Rnfmabj (赞：3)

## ABC272F

*2238

观前提示：由于笔者太弱小了没有力量，所以这是一篇使用哈希+二分以 $O(n \log^2n)$ 的复杂度求解 SA 数组的题解。

### 题意

给出两个仅含小写字母的长度为 $N$ 的字符串 $S,T$。

对于一个字符串 $X$ 和一个整数 $i$，定义 $f(X,i)$ 为执行以下操作 $i$ 遍后的结果：

- 移除字符串 $X$ 的首个字符并将其加到字符串最后。

找出符合以下条件的数对 $(i,j)$ 的数量：

- $1\le i,j\le N-1$。
- $f(S,i)$ 的字典序小于等于 $f(T,j)$ 的字典序。

### 题解

题中给出的操作相当于构成了一个 “字符环”，那么为了便于计算当然要先破环为链。具体地，我们将 $S,T$ 串各将自身复制一份然后直接拼接在自己后面，这样一来对于任意的 $1\le i\le N$ ，$S_i,S_{i+1},\dots,S_{i+N-1}$ 即为 $f(S,i-1)$ 的结果。

然后一个 $i$ 的贡献即为字符串排名在 $i$ 之后的 $j$ ，如果我们可以对所有的长为 $N$ 的字符串排序，然后得到这样做的下标顺序，也就是求出两个串合并之后的 SA 数组就好了（实际上并没有长度均为 $N$ 的限制，但在本题中二者起到的作用等价）。

那么怎么比较呢？排序本身是 $O(n\log n)$ 的，比较长度为 $N$ 的字符串字典序是 $O(n)$ 的，这样做最坏是 $O(n^2\log n)$ 的，不能接受。

可以使用哈希+二分来优化字符串比较。哈希可以检查两个字符串是否相等，那么在比较两个字符串时，可以二分出两个字符串最长的相同前缀，然后比较相同前缀的后一位，也就是第一个不同位的大小即可。

这样就能以 $O(n\log^2n)$ 的时间复杂度完成排序，最后 $O(n)$ 从后往前扫排序后的下标，维护一个 $cnt$ ，如果该下标是 $T$ 的那么 $cnt←cnt+1$ ，反之 $ans←ans+cnt$，即可完成统计答案。

### 代码

为了便于排序与统计将 $T$ 串拼在了 $S$ 串后。

```cpp
typedef unsigned long long ll;
const ll maxn=2e5+5,seed=29;
ll n;
char c[maxn<<2];
ll h[maxn<<2],fac[maxn];
ll calc(ll l,ll r){
	return (h[r]-(h[l-1]*fac[r-l+1]));
}
bool cmp(ll x,ll y){
	ll l=1,r=n,ans=0;
	while(l<=r){
		ll mid=(l+r)>>1;
		if(calc(x,x+mid-1)==calc(y,y+mid-1)){
			ans=mid;
			l=mid+1;
		}
		else r=mid-1;
	}
	return c[x+ans]==c[y+ans]?x<y:c[x+ans]<c[y+ans];//如果两个字符串相等那么优先将编号靠前的放在前面
	//因为题目要求的是统计小于等于的 f(T,j)，意味着相等的 T 也要被记入答案
	//前面我们把 T 拼在 S 后，所以 T 串的任意一个下标一定都比 S 的任意一个大
}
ll sa[maxn<<1];
void solve(){
	cin>>n;
	cin>>(c+1);
	fac[0]=1;
	for(ll i=1;i<=n;i++){
		fac[i]=fac[i-1]*seed;
		c[i+n]=c[i];
		sa[i]=i;
	}
	cin>>(c+2*n+1);
	for(ll i=1;i<=n;i++){
		c[i+3*n]=c[i+2*n];
		sa[n+i]=2*n+i;
	}
	for(ll i=1;i<=n*4;i++)h[i]=h[i-1]*seed+c[i]-'a'+1;
	sort(sa+1,sa+1+n*2,cmp);
	ll ans=0,cnt=0;
	for(ll i=n*2;i>=1;i--){
		if(sa[i]>n)cnt++;
		else ans+=cnt;
	}
	cout<<ans<<endl;
	return ;
}
```



---

## 作者：WaterSun (赞：2)

# 思路

实际上对于一个字符串 $S$ 进行一个 $f(S,x)$ 的操作本质上就是在 $S + S$ 中截取一段长度为 $n$ 的子串。

于是你不难想到把 $A,B$ 拼起来，形成一个字符串 $S = A + A + B + B$，然后比较后缀。你发现这是对的，因为两个串的字典序大小从前往后比较的，因此你尽管是比较的后缀，本质上还是比较的两个子串。

比较后缀大小，直接 SA 得出 $rk$ 数组。再次回到题目中，要求 $f(A,i) \leq f(B,j)$ 的数量，你发现这个条件等效于比较两个后缀 $rk$ 的大小。

但是直接枚举 $i,j$ 是不现实的，但是你可以先将 $f(A,i)$ 的 $rk$ 值丢到一个桶里面，然后对于所有的 $f(B,j)$ 对答案的贡献就是在桶中 $rk$ 小于等于它本身 $rk$ 的值的数量。因此对桶做一次前缀和即可。

但是本题中有一个坑点在与字符串应当在 $A,B$ 字符串交界处插入一个极小的字符，在最后插入一个极大的字符。

中间插入极小字符是因为当 $A = B$ 时，$B_1$ 就会影响两个后缀的大小关系；最后插入极大字符的原因是，本题求的是小于等于的情况，因此当两个子串相同时也应该记录答案，但是在 SA 中，$rk$ 的大小就会乱飘，为了使我们可以通过上述方法求答案我们应该保证当 $f(A,i) = f(B,j)$ 时，后者排在后面。

# Code

```cpp
#include <bits/stdc++.h>
#define re register
#define int long long

using namespace std;

const int N = 1e6 + 10;
int len,n,m = 250,ans;
int sum[N];
int sa[N],rk[N],prk[N],tmp[N],cnt[N];
char a[N],b[N],s[N];

inline int read(){
    int r = 0,w = 1;
    char c = getchar();
    while (c < '0' || c > '9'){
        if (c == '-') w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9'){
        r = (r << 3) + (r << 1) + (c ^ 48);
        c = getchar();
    }
    return r * w;
}

signed main(){
    len = read();
    scanf("%s%s",a + 1,b + 1);
    for (re int i = 1;i <= len;i++) s[++n] = a[i];
    for (re int i = 1;i <= len;i++) s[++n] = a[i];
    s[++n] = '&';
    for (re int i = 1;i <= len;i++) s[++n] = b[i];
    for (re int i = 1;i <= len;i++) s[++n] = b[i];
    s[++n] = '|';
    for (re int i = 1;i <= n;i++){
        rk[i] = s[i];
        cnt[rk[i]]++;
    }
    for (re int i = 1;i <= m;i++) cnt[i] += cnt[i - 1];
    for (re int i = n;i;i--) sa[cnt[rk[i]]--] = i;
    for (re int w = 1;w < n;w <<= 1){
        int num = 0,p = 0;
        for (re int i = n - w + 1;i <= n;i++) tmp[++num] = i;
        for (re int i = 1;i <= n;i++){
            if (sa[i] > w) tmp[++num] = sa[i] - w;
        }
        for (re int i = 1;i <= m;i++) cnt[i] = 0;
        for (re int i = 1;i <= n;i++) cnt[rk[i]]++;
        for (re int i = 1;i <= m;i++) cnt[i] += cnt[i - 1];
        for (re int i = n;i;i--) sa[cnt[rk[tmp[i]]]--] = tmp[i];
        for (re int i = 1;i <= n;i++) prk[i] = rk[i];
        for (re int i = 1;i <= n;i++){
            if (prk[sa[i]] == prk[sa[i - 1]] && prk[sa[i] + w] == prk[sa[i - 1] + w]) rk[sa[i]] = p;
            else rk[sa[i]] = ++p;
        }
        if (p == n) break;
        m = p;
    }
    for (re int i = 1;i <= len;i++) sum[rk[i]]++;
    for (re int i = 1;i <= 1e6;i++) sum[i] += sum[i - 1];
    for (re int i = 2 * len + 2;i <= 3 * len + 1;i++) ans += sum[rk[i]];
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：L_zaa_L (赞：1)

## 分析
考虑使用后缀数组（不会的可以看下[我的博客](https://www.cnblogs.com/pdpdzaa/p/17436993.html)）。

对于 $f(S,i)$，我们知道他是一个和 $S$ 循环同构的字符串，而且又要比大小，那么我们就可以用后缀数组来处理各个子串的大小。

因为要处理循环同构，所以可以将它拼成类似：$S+S+T+T$。

但是由于对于两串之间的大小不好分别，那么我们可以采用像马拉车的思想，在中间插上一些字符即可。

排完序之后呢？

我们已经知道 $S$ 各个循环同构子串与 $T$ 循环同构子串的大小。

我们就可以利用数组 $sa$ 直接记录每个排名有多少个 $T$ 的循环同构子串（$T$ 的范围应该要注意一下）比他小。

```
#include<bits/stdc++.h>
#define int long long 
using namespace std;
inline int read(){
	int x=0,f=1;
	char ch;
	ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-f;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=x*10+(ch-'0');
		ch=getchar();
	}
	return x*f;
}
const int N=5145140;
char s[2*N];
int n,m=500;
int rak[N],tp[N],tag[N],sa[N];
int height[N]; 
int za[N];
inline void SA(){//后缀数组
    for(int i=0;i<=m;++i) tag[i]=0;
	for(int i=1;i<=n;++i) rak[i]=s[i];
	int p=0;
	for(int i=1;i<=n;++i)++tag[rak[i]];
	for(int i=1;i<=m;++i) tag[i]+=tag[i-1];
	for(int i=n;i>=1;--i) sa[tag[rak[i]]--]=i;
	//Radix_sort();
	for(int k=1;k<=n;k<<=1){
		p=0;
		for(int i=n-k+1;i<=n;++i) tp[++p]=i;
		for(int i=1;i<=n;++i)
			if(sa[i]>k)
				tp[++p]=sa[i]-k;
		for(int i=0;i<=m;++i) tag[i]=0;
		for(int i=1;i<=n;++i)tag[rak[i]]++;
		for(int i=1;i<=m;++i) tag[i]+=tag[i-1];
		for(int i=n;i>=1;--i){sa[tag[rak[tp[i]]]--]=tp[i];tp[i]=0;}
		swap(rak,tp);
		rak[sa[1]]=1;
 		p=1;
		for(int i=2;i<=n;++i)
			rak[sa[i]]=(tp[sa[i-1]]==tp[sa[i]]&&tp[sa[i-1]+k]==tp[sa[i]+k])?p:++p;
		if(p==n) break;
		m=p;
	}
}
void GetHeight(){
	int k=0;
    for(int i=1;i<=n;++i){
		if(rak[i]==1) continue;
        if(k) k--;
        while(i + k <= n &&sa[rak[i]-1]+k<= n &&s[i+k]==s[sa[rak[i]-1]+k]) k++;
        height[rak[i]]=k;
    }
} 
char t[N];
int id[N],ans[N];
signed main(){
	n=read();
	scanf("%s",s+1);
	n=strlen(s+1);
	for(int i=1;i<=n;++i) s[i+n]=s[i];
  	s[n*2+1]='#';
	scanf("%s",s+2*n+2);
	for(int i=n*2+2;i<=n*3+1;++i) s[i+n]=s[i];
	n*=4;
	n+=2;
	s[n]='|';//把串拼起来。
	SA();
	n/=4;
	for(int i=1;i<=n*4;++i)
		if(sa[i]>n*2+1&&sa[i]<=n*2+1+n)
			++za[i];
	int ans=0;
	for(int i=n*4;i>=1;--i)
		za[i]+=za[i+1];
	for(int i=1;i<=n*4;++i)
		if(sa[i]<=n)
			ans+=za[i];
	cout<<ans;
	return 0;
}

```

---

## 作者：Tsawke (赞：0)

#  [[ABC272F] Two Strings](https://www.luogu.com.cn/problem/AT_abc272_f) Solution

[TOC]

## [更好的阅读体验戳此进入](http://blog.tsawke.com?t=ABC272F)

## 题面

给定两字符串 $ S, T $，求两字符串及其分别循环同构的所有字符串按字典序排序后顺序对个数，定义顺序对为 $ S $ 循环同构的字符串小于等于 $ T $ 循环同构的字符串的对数。

## Solution

~~二分哈希~~，~~SA~~，SAM。

首先经典套路，对于循环同构直接断环然后倍长，以此其长度为 $ n $ 的子串可以表示所有循环同构的串，于是想到对于本题，倍长 $ S, T $，按照 `S + S + T + T` 的顺序排一下，此时对于其中起始点为 $ [1, n] \cup [2n + 1, 3n] $，长度为 $ n $ 的所有子串进行字典序排序然后求顺序对即可。

上述排序过程显然可以哈希之后，二分判断，复杂度大概是 $ O(n \log^2 n) $，但是这样不够优秀，显然也可以用 SA 求解，但是我不想写 SA，于是我们考虑强行使用 SAM 解决。

这个做法常数较大且细节较多，需要对 SAM 有一定的理解，建议先尝试用 SAM 写一下后缀排序后再考虑这道题。

再次思考一下我们的问题，显然可以转换为对原串的所有定长（即长度为 $ n $）子串之间可重复地排序。

不考虑可重复，不考虑复杂度，一个显而易见的思路就是我们顺序插入建出 SAM，显然在 SAM 中每走一步就会使长度 $ +1 $，且 SAM 可以表示出原串的任意子串，于是我们在 SAM（具体来说就是 SAM 的 DAG）上 dfs，然后贪心地优先走字典序较小的 `trans`，这样当深度（或者说步数）达到 $ n $ 的时候，我们直接将这个点对应的插入的位置 $ idx $ 存下来，这个存储的顺序就是对应终止于 $ idx $ 长度为 $ n $ 的字符串之间的字典序顺序关系。

现在让我们依次解决这些问题。

首先对于重复的问题，终止节点，或者说就是 $ endpos $ 不同的相同串，我们应该均保留，而上述过程中显然我们对于一个 $ endpos $ 的等价类中只保留了一个，而这个也很好处理，我们只需要对于找到的节点，遍历其在 Parent Tree 上的整个子树保留整棵子树上的所有 $ idx $ 即可。

然后考虑复杂度，一般来讲树上的搜索是可控的，而 DAG 上的搜索则不同，甚至是指数级的，于是我们想到尝试将这个过程从 SAM 上搜索转为从 Parent Tree 上搜索，这一部分的思路与 SAM 求 SA 较为相似，首先思考 SAM 与 Parent Tree 的区别，SAM 中的边是在尾部追加字符，而 Parent Tree 则是在前面插入字符。我们考虑将原串倒序插入 SAM，这样在 Parent Tree 中向更深走的时候意义就会变为追加后缀，而每个等价类中又代表着连续长度的子串，那么当我们在 Parent Tree 搜索时若 $ len \ge n $，则说明当前所在的 $ endpos $ 等价类中子串长度刚好会包括 $ n $，于是再次搜索这个点的子树并保留即可。

接下来不难发现这样是不存在贪心的，也就是说此过程是无序的，而 `link` 并不像 `trans` 一样本身带有字符，而对于这里的处理又要考虑到 SAM 中 Parent Tree 的本质，即在 SAM 中进行压缩，换句话说就是对于一个 $ v \rightarrow u $ 的 `link`，Parent Tree 中 $ u $ 为 $ v $ 的子节点，那么应该满足 $ u $ 追加若干长度后达到 $ v $，而此时我们的贪心就需要考虑到从 $ u $ 到 $ v $ 的过程中的 $ u $ 之后的第一个字符的字典序关系，这个是显然的，且若第一个字符相同那么一定不会被分裂成两个点，所以我们依次为依据，想到 $ u $ 是 $ v $ 的前缀，那么从 $ v $ 的初始位置（注意这里反向插入原串后 $ endpos $ 或者说代码中的 $ idx $ 的意义改为子串初始位置）位移 $ u $ 的长度后以原串中的对应位置的字符为关键字进行偏序地贪心即可。具体来说，Parent Tree 每条边的边权应为 `p->idx + p->link->len`。

下一个细节，对于建 SAM 时分裂出来的点，从意义上来讲其 $ idx $ 应该为对应次插入时的 $ idx $，且我们在记录答案时对于分裂出的点应该忽略。

再一个细节就是我们在搜索子树的时候不能直接返回一个 `basic_string` 等容器，否则会因递归多次导致复杂度退化。

而最终统计答案时，我们只需要保留所有范围在 $ [1, n] \cup [2n + 1, 3n] $ 的答案并记录即可。

## Code

```cpp
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

#define PI M_PI
#define E M_E
#define npt nullptr
#define SON i->to
#define OPNEW void* operator new(size_t)
#define ROPNEW void* Edge::operator new(size_t){static Edge* P = ed; return P++;}
#define ROPNEW_NODE void* Node::operator new(size_t){static Node* P = nd; return P++;}

using namespace std;

mt19937 rnd(random_device{}());
int rndd(int l, int r){return rnd() % (r - l + 1) + l;}
bool rnddd(int x){return rndd(1, 100) <= x;}

typedef unsigned int uint;
typedef unsigned long long unll;
typedef long long ll;
typedef long double ld;

#define d(c) (c - 'a')

template < typename T = int >
inline T read(void);

struct Edge;
struct Node{
    unordered_map < int, Node* > trans;
    Node* link;
    int len;
    int idx;
    bool flag;
    Edge* head;
    int val;
    OPNEW;
}nd[2100000];
ROPNEW_NODE;
Node* root;

struct Edge{
    Edge* nxt;
    Node* to;
    int val;
    OPNEW;
}ed[4100000];
ROPNEW;

int N;
string S, T;
string base;
basic_string < bool > sorted;
basic_string < int > ret;

void Insert(int c, int idx){
    static Node* lst = root;
    Node* p = lst; Node* cp = lst = new Node; cp->idx = idx; cp->flag = true;
    cp->len = p->len + 1;
    while(p && !p->trans[c])p->trans[c] = cp, p = p->link;
    if(!p)cp->link = root;
    else if(p->trans[c]->len == p->len + 1)cp->link = p->trans[c];
    else{
        auto q = p->trans[c], sq = new Node(*q); sq->idx = idx; sq->flag = false;
        sq->len = p->len + 1;
        cp->link = q->link = sq;
        while(p && p->trans[c] == q)p->trans[c] = sq, p = p->link;
    }
}
void Link(void){
    auto endp = new Node();
    for(auto p = nd; p != endp;++p)
        if(p->link)
            p->link->head = new Edge{p->link->head, p, base.at(p->idx + p->link->len)};
}
void dfs_subt(Node* p){
    if(p->flag && ((1 <= p->idx && p->idx <= N) || (N * 2 + 1 <= p->idx && p->idx <= N * 3)))ret += p->idx;
    for(auto i = p->head; i; i = i->nxt)dfs_subt(SON);
}
void dfs(Node* p = root){
    if(N <= p->len){
        ret.clear();
        dfs_subt(p);
        int cnt1(0);
        for(auto pos : ret)
            if(N * 2 + 1 <= pos && pos <= N * 3)++cnt1;
            else if(1 <= pos && pos <= N)sorted += false;
        while(cnt1--)sorted += true;
        return;
    }
    basic_string < Edge* > sons;
    for(auto i = p->head; i; i = i->nxt)sons += i;
    sort(sons.begin(), sons.end(), [](Edge* a, Edge* b)->bool{return a->val < b->val;});
    for(auto son : sons)dfs(son->to);
}

int main(){
    // freopen("in.txt", "r", stdin);
    root = new Node(); root->idx = -1; root->len = 0;
    N = read();
    cin >> S >> T;
    base = '#' + S + S + T + T;
    for(int i = N * 4; i >= 1; --i)Insert(d(base.at(i)), i);
    Link(), dfs();
    ll ans(0), sumS(0);
    for(auto v : sorted)if(v)ans += sumS; else ++sumS;
    printf("%lld\n", ans);
    fprintf(stderr, "Time: %.6lf\n", (double)clock() / CLOCKS_PER_SEC);
    return 0;
}

template < typename T >
inline T read(void){
    T ret(0);
    int idx(1);
    char c = getchar();
    while(c != '-' && !isdigit(c))c = getchar();
    if(c == '-')idx = -1, c = getchar();
    while(isdigit(c)){
        ret *= 10;
        ret += int(c - '0');
        c = getchar();
    }
    ret *= idx;
    return ret;
}
```

## UPD

update-2023_02_15 初稿

---

