# Game with Binary String

## 题目描述

考虑以下游戏。两个玩家拥有一个二进制字符串（一个由字符 0 和/或 1 组成的字符串）。玩家轮流行动，由第一位玩家先手。在玩家的回合中，必须选择字符串中恰好两个相邻元素并移除它们（首元素和末元素也被视为相邻）。此外，根据当前行动玩家的不同存在额外约束：

- 如果是第一位玩家的回合，所选的两个字符必须都是 0；
- 如果是第二位玩家的回合，所选的两个字符中至少有一个必须是 1。

无法进行有效移动的玩家输掉游戏。这也意味着如果当前字符串长度小于 2，当前玩家输掉游戏。

给定一个长度为 $n$ 的二进制字符串 $s$。你需要计算其满足以下条件的子串数量：若在该子串上进行游戏且双方都采取最优决策，第一位玩家将获胜。换句话说，计算满足 $1 \le l \le r \le n$ 的有序对 $(l, r)$ 的数量，使得在字符串 $s_l s_{l+1} \dots s_r$ 上第一位玩家拥有必胜策略。

## 说明/提示

第一个示例中，以下子串是第一位玩家的必胜子串（$s[l:r]$ 表示 $s_l s_{l+1} \dots s_r$）：

- $s[1:2]$；
- $s[1:3]$；
- $s[1:7]$；
- $s[2:4]$；
- $s[2:8]$；
- $s[3:5]$；
- $s[4:5]$；
- $s[4:6]$；
- $s[5:7]$；
- $s[6:8]$；
- $s[7:8]$；
- $s[7:9]$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
10
0010010011```

### 输出

```
12```

# 题解

## 作者：2huk (赞：2)

考察一个序列先手必胜的条件。

对于后手，如果有相邻的 $0,1$ 是一定要操作它们的，因为这样能减少 $0$ 的数量。

注意到序列是环形，那么存在相邻的 $0,1$ 等价于序列不全相同。显然序列全相同时胜负能定。所以后手只能操作 $0,1$ 而不是 $1,1$。

令序列中 $0,1$ 的个数分别为 $c_0,c_1$。注意到一轮操作后 $0$ 会少三个，$1$ 会少一个，也就是最多能操作 $\min(c_0/3,c_1)$ 轮。于是考虑 $c_0,c_1$ 的关系对先手是否必胜的影响。

- $c_0 - 3c_1 \ge 2$：操作完 $c_1$ 轮后全是 $0$，先手胜。
- $c_0-3c_1=1$：操作完 $c_1$ 轮后只剩一个 $0$，后手胜。
- $c_0-3c_1=0$：操作完 $c_1$ 轮后全删完了，后手胜。
- $c_0-3c_1=-1$：操作完 $c_1-1$ 轮后，还剩两个 $0$ 和一个 $1$，先手胜。
- $c_0 - 3c_1=-2$：操作完 $c_1-1$ 轮后，还剩一个 $0$ 和一个 $1$，后手胜。
- $c_0-3c_1\le -3$：操作完 $\lfloor c_0/3 \rfloor$ 轮后全是 $0$，先手胜。

也就是说先手胜等价于 $c_0 - 3c_1 \ge 2$ 或 $c_0-3c_1=-1$。

那很好了，我们视作 $0$ 的权值为 $1$，$1$ 的权值为 $-3$，然后做这个权值的前缀和，那么 $[l, r]$ 合法等价于 $s_r-s_{l-1} \ge 2$ 或 $s_r-s_{l-1} = -1$。随便搞一下就好了。

---

## 作者：CQ_Bab (赞：2)

# 前言
不用线段树，我赛时磕 ~~尼玛的 F~~。
# 思路
首先我们可以发现对于一个串是否合法只与其中的 $0$ 和 $1$ 个数量有关，因为我们第一个人每次要减少的是一定的，而第二个人又因为最多所以取的一定是一个 $0$ 一个 $1$，这时有人会说比不一定有 $01$ 的情况存在，但是你发现对于一个串 $s$ 是一个环形结构如果没有 $01$ 相邻当且仅当一种数字没了。

有了上述结论就是煞笔题了，你发现我们可以先将所有的 $0$ 移到 $1$ 的前面，那么每一轮都会将 $0$ 的个数减 $3$ 将 $1$ 的个数减 $1$，然后我们在据此来分讨。

- 如果最后第一个人拿完之后已经没剩 $1$ 了，那么第一个人肯定赢了，就等于要满足 $cnt0-cnt1\times 3\geq 2$。
- 如果最后一个人拿完之后还剩了一个 $1$ 但没有 $0$ 了，也可以赢，等价于 $cnt0-cnt1\times 3=-1$。

可以发现只有这两种情况第一个人能赢，那么就能打出暴力了。
```cpp
rep(i,1,n) {
		rep(j,i+1,n) {
			int c0=cnt[j][0]-cnt[i-1][0];
			int c1=cnt[j][1]-cnt[i-1][1];
			if(c0-c1*3>=2) {
				res++;
			}else {
				if(c0-((c1-1)*3)==2) res++;
			}
  }
}
```

而优化也很好优化，直接分治就行了，就不讲了。
# 代码
```cpp
#include <bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include <ext/rope>
using namespace __gnu_pbds;
using namespace std;
#define pb push_back
#define rep(i,x,y) for(register int i=x;i<=y;i++)
#define rep1(i,x,y) for(register int i=x;i>=y;--i)
#define int long long
#define fire signed
#define il inline
template<class T> il void print(T x) {
	if(x<0) printf("-"),x=-x;
	if (x > 9) print(x / 10);
	putchar(x % 10 + '0');
}
template<class T> il void in(T &x) {
    x = 0; char ch = getchar();
    int f = 1;
    while (ch < '0' || ch > '9') {if(ch=='-') f = -1; ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = (x << 3) + (x << 1) + (ch ^ 48); ch = getchar(); }
    x *= f;
}
int T=1;
string s;
const int N=3e5+10;
int cnt[N][2],n;
int lowbit(int x) {
	return x&-x;
}
int tr[N*7];
void add(int x,int k) {
	x+=n*4;
	for(;x<=n*7;x+=lowbit(x)) tr[x]+=k;
}
int Ans(int x) {
	x+=n*4;
	int res=0;
	for(;x;x-=lowbit(x)) res+=tr[x];
	return res;
}
int res;
void get(int l,int r) {
	if(l==r) return;
	int ss=0;
	int mid=l+r>>1;
	get(l,mid);
	get(mid+1,r);
	vector<int>vv;
	rep(i,mid+1,r) {
		if(s[i]=='0') ss++;
		else ss-=3;
		add(ss,1);
		vv.pb(ss);
	}
	ss=0;
	rep1(i,mid,l) {
		if(s[i]=='0') ss++;
		else ss-=3;
		res+=(r-(mid+1)+1)-Ans(2-ss-1);
		res+=(Ans(-1-ss)-Ans(-2-ss));
	}
	for(auto to:vv) add(to,-1);
}
void solve() {
	in(n);
	cin>>s;
	s=" "+s;
	rep(i,1,n) {
		rep(j,0,1) cnt[i][j]=cnt[i-1][j];
		cnt[i][s[i]-'0']++;
	}
	get(1,n);
	cout<<res;
}
fire main() {
	while(T--) {
		solve();
	}
	return false;
}
```

---

## 作者：AxB_Thomas (赞：1)

## 题意：
题目描述较为繁琐，vjudge 上有翻译版：[点这里](https://vjudge.net/problem/CodeForces-2070E#author=GPT_zh)
## 思路：
首先可以确定的是，如果玩家 $2$ 的策略是最优策略，那么其一定会选形如 $01/10$ 这样的串。因为玩家 $2$ 必须要选至少一个 $1$ ，那么一定我们希望每次尽量少用 $1$ 并且多消耗玩家1需要的 $0$，这样才可以使得可以撑更多的回合，更优。

又发现，我们如果想让玩家 $1$ 获胜，那么必然其比玩家 $2$ 多玩了 $1$ 轮。考虑玩家 $2$ 输了最后会出现怎样的局面：

显然有两种情况。第一种是所有 $1$ 都被拿完了，并且局面还能保证玩家 $1$ 至少还能玩 $1$ 轮，第二种是最后还剩一个 $1$ ，但是没有其他任何元素了，那么此时玩家 $2$ 也无法胜利。

所以我们考虑记 $cnt_{0/1}$ 表示序列中 $0/1$ 的个数，先考虑上述第一种情况，此时玩家 $2$ 拿完了所有 $1$ ，并且按照最优策略。那么玩家 $2$ 就拿了 $cnt_1$ 个 $1$ 和 $0$，此时若要满足玩家 $1$ 能至少比玩家 $2$ 多玩一轮，则一定，其拿了 $2\times(cnt_1 + 1)$ 个 $0$。也就等价说明了，要满足玩家 $1$ 必胜，一定要满足：
$$cnt_0\geq3\times cnt_1+2$$
什么，你说怎么保证每一次玩家 $1$ 都可以行动？很简单，我们换一个视角思考这个问题，考虑我们现在已经有了 $cnt_1$ 个 $1$，我们将所有的 $0$ 分配到任意的两个 $1$ 之间，因为至少有 $3\times cnt_1+2$ 个 $0$ 则所有的分配情况下都一定会存在至少有 $3$ 个连续(相邻)的 $0$ $(cnt_1>0)$ 的方案，所以不用担心不够用，并且每一轮玩家 $1$ 和玩家 $2$ 都进行了游戏后，这个不等式是依然成立的，所以每一次都可以保证玩家 $1$ 可以行动。

又很显然的，当上述不等式取等时，我们的必胜策略已经到极限了，再让 $cnt_0$ 变小就无法保证玩家 $1$ 必胜了，所以上述不等式是充要的。

用同样的分析方法，可以得出如果要产生第二种必胜结局，则一定：
$$cnt_0=3\times cnt_1-1$$
证明思路同上，略。

现在考虑统计答案，我们试着枚举区间左端点 $r$，那么我们现在需要知道的就是有多少个 $l$ 是合法的。显然一个合法的 $l$ 需要满足的充要条件（情况1）是：
$$(cntr_0-cntl_0)\geq3\times(cntr_1-cntl_1) + 2$$
我们试着对式子进行变换：
$$(cntr_0-3\times cntr_1)-2\geq cntl_0 - 3\times cntl_1$$
你发不等式现左边括号中的内容与不等式右边是同构的。所以我们定义函数 $f(i)=cnti_0-3\times cnti_1$ ，所以不等式变为：
$$f(r) - 2\geq f(l)$$
那么我们现在只需要找出这样的 $l$ ，如果我们暴力枚举的话，复杂度是 $O(n^2)$ 的，显然无法通过本题，但你发现这是一个求区间 $[1,r-1]$ 中的合法下标的问题，既然是区间问题，我们可以考虑建立一颗树状数组来解决这个问题，以减少对前面区间的重复遍历。但是这不是一般的树状数组。事实上，我们应当建立一颗值域树状数组，也就是下标为 $f(x)$ 中存的东西。并且每次遍历完 $r$ 后，都需要将树状数组中 $f(r)$ 的部分加$1$，即遍历到了多一个值为 $f(r)$ 的下标 $r$ ，方便给后面的数计算。

对于情况二是同理的，只是需要注意的是，情况二是等号，所以需要减去小于 $f(r) + 1$ 的部分的贡献（这么说有点抽象，直接看代码可能更好理解）。

## Code:
注意上述分析中 $f(x)$ 可能为负数，所以需要加一个偏移量来保证树状数组下标的非负。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define LL long long 
inline int read(){
	char c=getchar();bool f=0;int x=0;
	while(c > '9' || c < '0') f|=c=='-',c=getchar();
	while(c >= '0'&&c <= '9') x=(x<<1)+(x<<3)+(c^48),c=getchar();
	if(f) x=-x;return x;
}

const int M = 4e6 + 10,N = 3e5 + 10;
char s[N];
int n,tree[M],pre[N],up_limit;
int lowbit(int x){return x & (-x);}
 
void add(int x, int k){
    for(;x <= up_limit;x += lowbit(x)) 
		tree[x] += k;
}

LL query(int x){
    LL res = 0;
    for(;x;x -= lowbit(x)) 
		res += tree[x];
    return res;
}

int main()
{
	n = read(); 
	scanf("%s",s + 1);
	LL ans = 0;
	up_limit = 3e6 + 10;
	for(int i = 1;i <= n;++i) 
	{
		pre[i] = pre[i - 1] + (s[i] == '0' ? 1 : -3); 
	}
	for(int i = 0;i <= n;++i) pre[i] += 3 * n + 5;
	
	add(pre[0],1);
	for(int i = 1;i <= n;++i)
	{
		ans += query(pre[i] - 2) + (query(pre[i] + 1) - query(pre[i]));
		add(pre[i],1);
	}
	
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：冷却心 (赞：1)

upd 250304：修改了若干笔误。

锐评一下官解有没有素质啊，四颗线段树根据余数分讨诗人握持。

来一个并非小清新做法。

首先考虑什么样的字符串会 Alice 必胜。观察到 Alice 没什么策略可言，Bob 一定会取一个  $0$ 和 $1$，因为当前序列必有一个 $0$，否则显然 Bob 获胜。这样会发现每一轮序列会减少三个 $0$ 一个 $1$。记 $c_0$ 表示 $0$ 的个数，$c_1$ 表示 $1$ 的个数。轻微分讨一下：

- 当 $c_0-3c_1\geq 2$ 时，显然做完若干轮之后会只剩下一堆 $0$，Alice 必胜。
- 当 $c_0-3c_1=1$ 或 $c_0-3c_1=0$ 时，会发现是做完若干轮之后剩下 $\leq 1$ 个 $0$，这时候 Alice 无法操作，Bob 必胜。
- 当 $c_0-3c_1=-1$ 时，这时是做完若干轮之后 Alice 又能操作一次，然后剩下恰好一个 $1$，Bob 无法继续，Alice 必胜。
- 当 $c_0-3c_1=-2$ 时，此时做完若干轮之后会剩下一个 $1$ 一个 $0$，Alice 动不了，Bob 必胜。
- 当 $c_0-3c_1\leq-3$ 是，做完若干轮会剩下一车 $1$，Bob 必胜。

总结一下，当 $c_0-3c_1\leq 2$ 或 $c_0-3c_1=-1$ 的时候 Alice 必胜。很清新的结论。

感觉 $c_0-3c_1$ 这个东西不太好维护啊，代换一下，设区间长度为 $l$，则 $c_0-3c_1=c_0-3(l-c_0)=4c_0-3l$，所以记 $c_i$ 表示前缀 $i$ 包含 $0$ 的个数，$b_i=4c_i-3i$，然后维护一个 ds 用来求单点加区间查询，把 $i$ 从 $1$ 到 $n$ 扫一遍，每次计算以 $i$ 为右端点的区间的贡献，寻找合法的左端点 $p$，这里是左开右闭区间 $(p,i]$，只有满足 $b_p\leq b_i-2$ 或 $b_p=b_i+1$ 的 $p$ 是合法的，然后把 $b_i$ 加入这个数据结构。这里我赛时没多想直接上了动态开点线段树，因为懒得搞清楚 $b_i$ 的值域了，事实上 bit 应该也可以。


```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int N = 3e5 + 10;
int n, cnt[N], A[N]; char S[N];

int lim = 5e8;
int tot, ls[N * 30], rt, rs[N * 30]; LL tr[N * 30];
void update(int &p, int l, int r, int x, LL k) {
	if (x > r || x < l) return ;
	if (!p) p = ++ tot;
	if (l == r) { tr[p] += k; return ; }
	int mid = (l + r) >> 1; update(ls[p], l, mid, x, k); update(rs[p], mid + 1, r, x, k);
	tr[p] = tr[ls[p]] + tr[rs[p]];
}
LL query(int p, int l, int r, int x, int y) {
	if (!p || x > r || y < l) return 0;
	if (x <= l && y >= r) return tr[p];
	int mid = (l + r) >> 1; return query(ls[p], l, mid, x, y) + query(rs[p], mid + 1, r, x, y);
} 

int main() {
	freopen(".in", "r", stdin); freopen(".out", "w", stdout);
	ios :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> n >> (S + 1);
	for (int i = 1; i <= n; i ++) 
		cnt[i] = cnt[i - 1] + (S[i] == '0'), A[i] = 4 * cnt[i] - 3 * i;
	update(rt, -lim, lim, A[0], 1);
	LL Ans = 0;
	for (int i = 1; i <= n; i ++) {
		Ans += query(rt, -lim, lim, -lim, A[i] - 2) + query(rt, -lim, lim, A[i] + 1, A[i] + 1);
		update(rt, -lim, lim, A[i], 1);
	} cout << Ans;
	return 0;
}
```

---

## 作者：__staring__ (赞：1)

前言：来点并非小清新的做法，ys（余数），启动！

看到博弈论打个表先，找出 $len\le10$ 的先手必胜串，观察 $len=10$ 的部分：

```cpp
0000000000 0000000001 0000000010 0000000011
0000000100 0000000101 0000000110 0000001000
0000001001 0000001010 0000001100 0000010000
0000010001 0000010010 0000010100 0000011000
0000100000 0000100001 0000100010 0000100100
0000101000 0000110000 0001000000 0001000001
0001000010 0001000100 0001001000 0001010000
0001100000 0010000000 0010000001 0010000010
0010000100 0010001000 0010010000 0010100000
0011000000 0100000000 0100000001 0100000010
0100000100 0100001000 0100010000 0100100000
0101000000 0110000000 1000000000 1000000001
1000000010 1000000100 1000001000 1000010000
1000100000 1001000000 1010000000 1100000000
```

很有规律，似乎所有 $len=10,popcount\le2$ 的串都出现了。

再找出 $len\in(10,20]$ 的先手必胜串，也存在这样的规律，于是猜测：

存在数列 $win$，使得对于长为 $len$ 的串 $str$，先手必胜当且仅当 $popcount(str)\le win_{len}$。

再打表一下，找到 $win_{2,\dots,20}$（$win$ 数列下标从 $2$ 开始）：

```cpp
0,1,0,0,  1,2,1,1,  2,3,2,2,  3,4,3,3,  4,5,4
```

发现 $win_i=\lfloor \frac{i-2}{4} \rfloor + [i\bmod4=3]$。

简要地用归纳证一下：

假设上述规律对于 $len\le n-4$ 的串均成立，那么考虑 $len=n$ 的某一串 $str$，Alice 和 Bob 均操作一次后，$len\leftarrow n-4$，此时规律成立，$str'$ 先手必胜当且仅当 $popcount'\le win_{n-4}$，由于 $popcount$ 只被 Bob 影响，因此 Bob 一定只拿走一个 $1$，故原串 $str$ 先手必胜当且仅当 $popcount\le win_{n-4}+1$，得 $win_n=win_{n-4}+1$，根据打表结果知初态 $win_{2,3,4,5}={0,1,0,0}$。

综上，对于长为 $len$ 的串 $str$，先手必胜当且仅当 $popcount(str)\le win_{len}$，其中 $win_i=\lfloor \frac{i-2}{4} \rfloor + [i\bmod4=3]$。

接下来就好办了，记 $pre_i$ 表示 $str$ 的前缀和，合法子串满足 $pre_r-pre_{l-1}\le win_{r-l+1}$，令 $l'=l-1$，将 $win$ 拆开，得到 $pre_r-pre_{l'}\le \lfloor \frac{r-l'-2}{4} \rfloor + [(r-l'-2)\bmod4=3]$。

$/4$ 这一项直接做难以处理，但是考虑记 $r=4k_1+r_1,l'=4k_2+r_2$，那么 $\lfloor \frac{r-l'}{4} \rfloor=k_1-k_2-[r_1<r_2]$，带上 $-2$ 这一项，结果为 $k_1-k_2-\lfloor \frac{r_1-r_2-2}{4} \rfloor$，由于 $r_1,r_2\in[0,3]$，直接分讨即可。

此时条件为 $pre_r-pre_{l'}\le k_1-k_2+O(1)$，简单移项得到 $k_2-pre_{l'}\le k_1-pre_r+O(1)$，考虑对 $r$ 扫描线，用四棵树状数组 $bit_{0,1,2,3}$ 维护 $pre_{l'}-k_2$，后面的 $O(1)$ 直接根据余数分讨即可得知具体值。

注意由于 $win$ 下标从 $2$ 开始，扫到 $i$ 时才能放入 $i-2$ 的信息。

赛时代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
namespace staring
{
    typedef long long LL;
    typedef vector<int> VEC;
    typedef pair<int,int> PII;
    typedef pair<LL,LL> PLL;
    #define fir first
    #define sec second

    #define FOR(i,a,b) for(int i=(a),i##E=(b);i<=i##E;i++)
    #define ROF(i,a,b) for(int i=(a),i##E=(b);i>=i##E;i--)

    template<typename TYPE>
    TYPE gmax(TYPE &x,const TYPE y){return x<y?x=y:x;}
    template<typename TYPE>
    TYPE gmin(TYPE &x,const TYPE y){return y<x?x=y:x;}

    static constexpr int SIZE=1<<20;
    static char buffin[SIZE]{},*pin1{},*pin2{};
    static char buffout[SIZE]{},*pout{buffout};
    #define GETC() (pin1==pin2&&(pin2=(pin1=buffin)+fread(buffin,1,SIZE,stdin),pin1==pin2)?EOF:*pin1++)
    #define PUTC(c) (pout-buffout==SIZE&&(fwrite(buffout,1,SIZE,stdout),pout=buffout),*pout++=c)
    template<typename TYPE>
    void read(TYPE &x)
    {
        static int signf{0},chin{0};
        x=signf=0,chin=GETC();
        while(chin<'0'||chin>'9')signf|=chin=='-',chin=GETC();
        while(chin>='0'&&chin<='9')x=(x<<3)+(x<<1)+(chin^48),chin=GETC();
        if(signf)x=-x;
    }
    template<typename TYPE>
    void write(TYPE x,char ch=' ')
    {
        static char stack[64]{},top{0};
        !x&&PUTC('0'),x<0&&(x=-x,PUTC('-'));
        while(x)stack[top++]=x%10|48,x/=10;
        while(top)PUTC(stack[--top]);
        if(ch)PUTC(ch);
    }

}using namespace staring;

constexpr int N=3e5+5;

int n;
char str[N];
int c[4][N<<1];
int pre[N];

void add(int u,int k)
{
    k+=n+1;
    while(k<=(n<<1|1))++c[u][k],k+=-k&k;
}

int ask(int u,int k)
{
    int r=0;k+=n+1;
    while(k>=1)r+=c[u][k],k-=-k&k;
    return r;
}

int main()
{
    scanf("%d%s",&n,str+1);

    LL res=0;
    FOR(i,1,n)
    {
        int r=i&3,v;
        pre[i]=pre[i-1]+(str[i]=='1');

        int tmp=res;
        if(i-2>=0)add((i-2)&3,(i-2)/4-pre[i-2]);
        FOR(l,0,3)
        {
            if(r-l-2>=0)v=0;
            else if(r-l-2>=-4)v=-1;
            else v=-2;
            if(((r-l+4)&3)==3)++v;
            res+=ask(l,i/4-pre[i]+v);
        }
    }
    write(res);

    fwrite(buffout,1,pout-buffout,stdout);
    return 0;
}
```

---

## 作者：paper_ (赞：1)

## 主要思路

很显然 Bob 每次就一定会尽可能取 $01$，这样就发现每一轮都会消掉一个 $1$ 三个 $0$。

令序列中 $0$ 的个数为 $c_0$，$1$ 的个数为 $c_1$。

分类讨论：

- 若 $c_0-3\times c_1 \ge 2$，最终一定会剩下不少于两个的 $0$，Alice 胜。
- 若 $c_0 -3 \times c_1 = 0/1$，最终剩下 $0/1$ 个 $0$，Alice 无法操作，Bob 胜。
- 若 $c_0 - 3 \times c_1 = -1$，Alice 操作后只剩下一个 $1$，Bob 无法操作，Alice 胜。
- 若 $c_0 - 3 \times c_1 \le -2$，最终会剩下若干个 $1$，Bob 胜。

当然，每轮 Alice 能操作的前提是有相邻的两个 $0$，所以要满足：$c_0-c_1 \ge 1$ 才能保证，发现与 Alice 获胜的条件并不冲突，很多用这个方法的题解根本没有考虑这个点。

综上，只需要考虑满足 $c_0-3\times c_1 \ge 2$ 或 $c_0-3\times c_1 = -1$ 的区间个数就行了。

令 $num_i=c_{0,i} - 3 \times c_{1,i}$，$c_{0/1,i}$ 表示 $1 \sim i$ 中 $0/1$ 的个数。

原式就变为 $num_r - num_{l-1} \ge 2$ 或 $num_r - num_{l-1} = -1$ 。

接下来就是动态开点板子了。

### code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 300010;
char s[N];
int rt = 1, idx = 1;
struct TREE {
	int l, r, sum;
}tr[N * 20];
void insert(int &k, int l, int r, int p) {
	if (!k) k = ++ idx;
	if (l == r) {
		tr[k].sum ++;
		return;
	}
	int mid = l + r >> 1;
	if (p <= mid) insert(tr[k].l, l, mid, p);
	else insert(tr[k].r, mid + 1, r, p);
	tr[k].sum = tr[tr[k].l].sum + tr[tr[k].r].sum;
}
int query(int k, int l, int r, int ql, int qr) {
	if (!k) return 0;
	if (l >= ql && r <= qr) return tr[k].sum;
	int mid = l + r >> 1, re = 0;
	if (ql <= mid) re = query(tr[k].l, l, mid, ql, qr);
	if (qr > mid) re += query(tr[k].r, mid + 1, r, ql, qr);
	return re;
}
signed main() {
	int n;cin >> n;
	cin >> s + 1;
	int c0 = 0, c1 = 0, ans = 0;
	insert(rt, -1e6, 1e6, 0);
	for (int i = 1; i <= n; i ++ ) {
		if (s[i] == '0') c0 ++;
		else c1 ++;
		int num = c0 - c1 * 3;
		ans += query(1, -1e6, 1e6, -1e6, num - 2) + query(1, -1e6, 1e6, num + 1, num + 1);
		insert(rt, -1e6, 1e6, num);
	}
	cout << ans;
	return 0;
}
```

---

## 作者：Silvestorm (赞：0)

### 题目大意

[题目链接](https://www.luogu.com.cn/problem/CF2070E)

一个首尾相连的 $01$ 字符串，操作是取相邻的两个字符删去，先手只能取 $00$，后手至少有一个 $1$。谁不能操作谁就输了。

现在给出一个字符串，对于这个字符串的所有子串，统计先手必赢的数量。

### 题目类型

博弈论，贪心，线段树。

### 解题思路

先手只能取 $00$，后手至少有一个 $1$，但是为了让自己的赢面最大，后手肯定是有 $0$ 选 $0$。考虑后手输的情况：没有 $1$ 给他选，或者只剩下一个字母。

那么一轮操作中，先手取 $00$，后手取 $01$，消耗的 $01$ 比为 $3:1$。再考虑先手赢的情况：若干轮操作后，还剩下至少两个 $0$，或者剩下两个 $0$ 一个 $1$（这样取完，后手就取不了了。

量化一下，先手赢的条件是：假设最初 $1$ 的数量是 $x$，$0$ 的数量是 $y$，那么 $0$ 的数量范围就是 $y=3\times x-1$ 或 $3\times x+2\le y$。

现在考虑如何统计 $0,1$ 的数目。不妨设 $1$ 的权值为 $-3$，$0$ 的权值为 $1$，问题就转化成了统计区间和等于 $-1$ 或大于 $1$ 的区间数量。

区间和可以使用前缀和做差得到，统计答案可以使用权值线段树。由于前缀和的值可能是负数，需要特殊处理。

时间复杂度为 $O(n\log{n})$。

### code


```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll n, m, x, k, root, cnt, ans, mod = 998244353;
ll num[500100];
string s;
const ll L = -1e8, R = 1e8;
struct Tree
{
    ll w, w1, l, r;
} tree[10000100];

void update(ll nx, ll l, ll r, ll &p)
{
    if (!p)
        p = ++cnt;
    tree[p].w++;
    if (l == r)
        return;
    ll mid = (l + r) >> 1;
    if (nx <= mid)
        update(nx, l, mid, tree[p].l);
    else
        update(nx, mid + 1, r, tree[p].r);
}
ll query(ll nl, ll nr, ll l, ll r, ll p)
{
    if (!p || (nl <= l && r <= nr))
        return tree[p].w;
    ll mid = (l + r) >> 1;
    ll res = 0;
    if (nl <= mid)
        res += query(nl, nr, l, mid, tree[p].l);
    if (nr > mid)
        res += query(nl, nr, mid + 1, r, tree[p].r);
    return res;
}
void solve()
{
    cin >> n;
    cin >> s;
    ll u = 0;
    for (int i = 1; i <= n; i++)
    {
        if (s[i - 1] == '0')
            num[i] = 1, u++;
        else
            num[i] = -3;
        num[i] += num[i - 1];
        if (i > 1)
            update(num[i - 2], L, R, root);
        ans += query(L, num[i] - 2, L, R, root);
        ans += query(num[i] + 1, num[i] + 1, L, R, root);
    }
    cout << ans << '\n';
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    // cin >> t;
    while (t--)
        solve();
    return 0;
}

```

---

