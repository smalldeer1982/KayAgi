# STAMMER - Stammering Aliens

## 题目描述

Dr. Ellie Arroway has established contact with an extraterrestrial civilization. However, all efforts to decode their messages have failed so far because, as luck would have it, they have stumbled upon a race of stuttering aliens! Her team has found out that, in every long enough message, the most important words appear repeated a certain number of times as a sequence of consecutive characters, even in the middle of other words. Furthermore, sometimes they use contractions in an obscure manner. For example, if they need to say _bab_ twice, they might just send the message _babab_, which has been abbreviated because the second _b_ of the first word can be reused as the first _b_ of the second one.

Thus, the message contains possibly overlapping repetitions of the same words over and over again. As a result, Ellie turns to you, S.R. Hadden, for help in identifying the gist of the message.

Given an integer _m_, and a string _s_, representing the message, your task is to find the longest substring of _s_ that appears at least _m_ times. For example, in the message _baaaababababbababbab_, the length-5 word _babab_ is contained 3 times, namely at positions 5, 7 and 12 (where indices start at zero). No substring appearing 3 or more times is longer (see the first example from the sample input). On the other hand, no substring appears 11 times or more (see example 2).

In case there are several solutions, the substring with the rightmost occurrence is preferred (see example 3).

  
  
**Input**

The input contains several test cases. Each test case consists of a line with an integer _m_ (_m_ >= 1), the minimum number of repetitions, followed by a line containing a string _s_ of length between _m_ and 40 000, inclusive. All characters in _s_ are lowercase characters from “a” to “z”. The last test case is denoted by _m_ = 0 and must not be processed.

  
  
**Output**

Print one line of output for each test case. If there is no solution, output none; otherwise, print two integers in a line, separated by a space. The first integer denotes the maximum length of a substring appearing at least _m_ times; the second integer gives the rightmost possible starting position of such a substring.

  
  
**Sample Input**

 ```
<pre class="verbatim">3
baaaababababbababbab
11
baaaababababbababbab
3
cccccc
0
```

# 题解

## 作者：5k_sync_closer (赞：3)

二分这个最大长度，设当前二分中点为 $k$。

把所有长度为 $k$ 的子串算出来，扔进哈希表里。

然后如果某哈希值的出现次数 $\ge m$，则 $k$ 合法。

复杂度 $O(n\log n)$，可以过掉。
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <ext/pb_ds/hash_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
#define M 1000000093
using namespace std;
int n, m, l, r, k, f, q;char s[40050];long long p[40050], h[40050];
bool C(int k, int &q)
{
	__gnu_pbds::gp_hash_table<int, int> c, d;
	q = -1;for(int i = k, g;i <= n;++i)
		++c[g = (h[i] + M - h[i - k] * p[k] % M) % M], d[g] = i - k + 1;
	for(auto i : c) if(i.second >= m) q = max(q, d[i.first]);return ~q;
}
int main()
{
	for(int i = p[0] = 1;i <= 40000;++i)
		p[i] = p[i - 1] * 233 % M;
	while(~scanf("%d", &m) && m)
	{
		scanf("%s", s + 1);
		l = 0;r = n = strlen(s + 1);
		for(int i = 1;i <= n;++i)
			h[i] = (h[i - 1] * 233 + s[i]) % M;
		while(l <= r) if(C(k = l + r >> 1, f))
			l = k + 1, q = f;else r = k - 1;
		if(r) printf("%d %d\n", r, q - 1);
		else puts("none");
	}
	return 0;
}
```


---

## 作者：cyc001 (赞：2)

[UVA12206](https://www.luogu.com.cn/problem/UVA12206)双倍得分

### 题意
[题目传送门](https://www.luogu.com.cn/problem/SP10079)

给定一个字符串 $s$ 和整数 $n$ , 求 $s$ 中出现至少 $n$ 次的字符串的最长长度及这个长度的满足要求的字符串最后一次出现时这个字符串的起始位置
### 分析
1.此题答案存在单调性，若字符串 $s$ 满足要求，则 $s$ 去掉首 / 尾后的字符串 $s_1$ 仍然满足

2.所以可以考虑二分答案求解

3.先预处理 $s$ 的 $hash$ ，对于每个 $mid$ ，求解时 $O(1)$ 获得每个字串的 $hash$ ，当有某个特定字串的 $hash$ 出现数量 $\ge n$ 时，记录一次最后出现位置的答案

4.最终二分结束之后 $mid$ 及 $ck(mid)$ 即为答案

### Code

```cpp
#include<bits/stdc++.h>
#include<unordered_map>
using namespace std;
typedef unsigned long long ull;
vector<ull> wq;
void t() {
	wq.push_back(1);
	for (int i = 0; i < 40005; ++i) wq.push_back(((*(wq.end() - 1)) * 127));
}
bool ck(string& s, vector<ull>& H, int& last, int mid, int n) {
	unordered_map<ull, int> a_max; int t_max = -1;
	for (int i = 1; i <= s.length() - mid + 1; ++i) {
		int m = (++a_max[((H[i + mid - 1] - H[i - 1] * wq[mid]))]);
		if (n <= m) { t_max = m; last = i - 1; }
	}
	return t_max >= n;
}
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	string s; int n; t();
	while (cin >> n && n) {
		cin >> s; int l = 1, r = s.length();
		string bs; vector<ull> vu; ull th = 0;
		vu.push_back(0);
		for (int i = 1; i <= s.length(); ++i) {
			vu.push_back((th * 127 + s[i - 1] - 96));
			th = vu.back();
		}
		int r_ans = 1e9, r_last = -1, il;
		while (l <= r) {
			int mid = (l + r) / 2;
			ck(s, vu, il, mid, n) ? r_ans = mid, r_last = il,
				l = mid + 1 : r = mid - 1;
		}
		if (r_ans == 1e9) cout << "none" << endl;
		else cout << r_ans << ' ' << r_last << endl;
	}
	return 0;
}
```

---

## 作者：Ein_Niemand (赞：2)

## 题目大意：
- 给定一个整数 $m$ 和一个表示消息的字符串 $s$ ，找到至少出现 $m$ 次的 $s$ 的最长子字符串。

- 如果存在多个解决方案，则优选最右边出现的子串（即样例 $3$ ）。

- 由多组数据，当 $m=0$ 时输入结束。其中 $m>=1$  、 $m <= s.length <= 40000$ 。

- 如果没有解决方案，则输出 $none$；否则，输出两个整数，用**空格**分隔，第一个整数表示出现至少 $m$ 次的子串的最大长度; 第二个整数给出了这种子串最可能的起始位置（同时要注意**题目中字串从 $0$ 开始**）。

# ------------------------------------------------

## 分析：
- 啊，本**蒟蒻**不会后缀数组咋办啊……可不要忘了我们还有 $hash$ +二分这种好东西！！

- 既然我们**使得**至少出现 $m$ 次的子串的长度**尽量大**，所以我们可以二分出一个 $mid$ 。若对其 $check$ 结果为 $true$ ，则用 $ans$ 记录。

- 关于 $check$ 函数，我们可以每次找长度为 $mid$ 的字串，即 $s[i]->s[i+mid-1],i+mid-1<=len$。用 $map$ 存储每个子串出现的次数，若某一个子串出现数 $>m$，则返回 $true$ ；否则返回 $false$ 。

- 找到 $ans$ 后，再计算一下它出现的位置即可。（方法与 $check$ 差不多）

# ------------------------------------------------

## Code（~~高清无码~~）
```cpp
#include<cstdio>
#include<cstring>
#include<map>
using namespace std;
#define rg register int
#define I inline int
#define V inline void
#define ll long long
#define db double
#define B inline bool
#define F1(i,a,b) for(rg i=a;i<=b;++i)
#define ed putchar('\n')
#define bl putchar(' ')
const int N=40005;
const int mod=13331;
template<typename TP>V read(TP &x)
{
	TP f=1;x=0;register char c=getchar();
	for(;c<'0'||c>'9';c=getchar()) if(c=='-') f=-1;
	for(;c>='0'&&c<='9';c=getchar()) x=(x<<3)+(x<<1)+(c^'0');
	x*=f;
}
template<typename TP>V print(TP x)
{
	if(x<0) x=-x,putchar('-');
	if(x>9) print(x/10);
	putchar(x%10+'0');
}
int t,len,ans;
char s[N];
unsigned ll p[N],H[N];
template<typename TP>B check(TP x)
{
	map<int,int>m;
	for(rg i=1;i+x-1<=len;++i)
	{
		rg h=H[i+x-1]-H[i-1]*p[x];++m[h];
		if(m[h]>=t) return true;
	}
	return false;
}
template<typename TP>I calc(TP x)
{
	map<int,int>m;
	rg pos;
	for(rg i=1;i+x-1<=len;++i)
	{
		rg h=H[i+x-1]-H[i-1]*p[x];++m[h];
		if(m[h]>=t) pos=i;
	}
	return pos-1;//题目中从0开始 
}
int main()
{
	while(~scanf("%d",&t)&&t)
	{
		scanf("%s",s+1);
		p[0]=1,H[0]=ans=0,len=strlen(s+1);
		F1(i,1,len)
		{
			p[i]=p[i-1]*mod;
			H[i]=H[i-1]*mod+(s[i]-'a'+1);
		}
		rg l=1,r=len;
		while(l<=r)
		{
			rg mid=(l+r)>>1;
			if(check(mid)) l=mid+1,ans=mid;
			else r=mid-1;
		}
		if(!ans) puts("none");
		else print(ans),bl,print(calc(ans)),ed;
	}
	return 0;
}
```


---

## 作者：szh_AK_all (赞：1)

[摘自本文](https://www.luogu.com.cn/article/7d7bk882)。

### SP10079 STAMMER - Stammering Aliens

先对 height 数组建出笛卡尔树，题目要求出现次数不低于 $m$ 且长度最长最靠右的子串，那么对于出现次数这个条件，我们仍然考虑枚举每个节点，只有它所代表的左右子树的 LCP 才可能是答案，而这个 LCP 的出现次数即为当前节点的影响区间，那么我们可以以此来更新答案。

当然我们还需要求每个节点所代表的左右子树的 LCP 最后出现的位置，也就是该节点及其子树所涵盖的起始位置最大的后缀，这个可以用 $maxn$ 来记录。对于一个节点 $x$，在遍历完他的左右子树 $l,r$ 后，便可以用 $maxn_l,maxn_r$ 来更新 $maxn_x$。而 $maxn_x$ 的初始值是 $\max(sa_x,sa_{x+1})$（这个地方很容易错！）。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 40005;
int a[N], b[N], sa[N], h[N], rk[N], t[N], q[N];
string s;
int n, m;

void getsa() {
	memset(t, 0, sizeof(t));
	memset(sa, 0, sizeof(sa));
	for (int i = 1; i <= n; i++) {
		a[i] = s[i];
		++t[a[i]];
	}
	for (int i = 2; i <= 128; i++)
		t[i] += t[i - 1];
	for (int i = n; i >= 1; i--)
		sa[t[a[i]]--] = i;
	int now = 128;
	for (int k = 1; k <= n; k *= 2) {
		int cnt = 0;
		for (int i = n - k + 1; i <= n; i++)
			b[++cnt] = i;
		for (int i = 1; i <= n; i++)
			if (sa[i] > k)
				b[++cnt] = sa[i] - k;
		memset(t, 0, sizeof(t));
		for (int i = 1; i <= n; i++)
			t[a[i]]++;
		for (int i = 2; i <= now; i++)
			t[i] += t[i - 1];
		for (int i = n; i >= 1; i--)
			sa[t[a[b[i]]]--] = b[i], b[i] = 0;
		swap(a, b);
		int tot = 1;
		a[sa[1]] = 1;
		for (int i = 2; i <= n; i++) {
			if (b[sa[i]] == b[sa[i - 1]] && b[sa[i] + k] == b[sa[i - 1] + k])
				a[sa[i]] = tot;
			else
				a[sa[i]] = ++tot;
		}
		if (tot == n)
			break;
		now = tot;
	}
}

void gethi() {
	memset(rk, 0, sizeof(rk));
	memset(h, 0, sizeof(h));
	for (int i = 1; i <= n; i++)
		rk[sa[i]] = i;
	int now = 0;
	for (int i = 1; i <= n; i++) {
		if (rk[i] == 1)
			continue;
		if (now)
			now--;
		int j = sa[rk[i] - 1];
		while (i + now <= n && j + now <= n && s[i + now] == s[j + now])
			now++;
		h[rk[i]] = now;
	}
	for (int i = 1; i <= n; i++)
		h[i] = h[i + 1];
}

struct node {
	int l, r, hi;
	int ql, qr;
} p[N];

void bu(int d, int l, int r) {
	if (!d)
		return;
	p[d].ql = l, p[d].qr = r;
	bu(p[d].l, l, d);
	bu(p[d].r, d + 1, r);
}
int qq[N];

void dikaer() {
	int top = 0;
	h[n] = -1;
	for (int i = 1; i <= n; i++) {
		int now = 0;
		while (top && h[i] <= h[qq[top]]) {
			p[qq[top]].r = now;
			now = qq[top];
			top--;
		}
		p[i].l = now;
		qq[++top] = i;
	}
}
int ans, wei = -1, maxn[N];

void dfs(int x) {
	maxn[x] = max(sa[x], sa[x + 1]);
	if (p[x].l)
		dfs(p[x].l);
	if (p[x].r)
		dfs(p[x].r);
	maxn[x] = max(maxn[x], max(maxn[p[x].l], maxn[p[x].r]));
	if (p[x].qr - p[x].ql + 1 >= m && h[x] != 0) {
		if (h[x] > ans || (h[x] == ans && maxn[x] > wei)) {
			ans = h[x];
			wei = maxn[x];
		}
	}
}

signed main() {
	while (1) {
		cin >> m;
		if (!m)
			return 0;
		cin >> s;
		n = s.size();
		s = " " + s;
		if (m == 1) {
			cout << n << " " << 0 << "\n";
			continue;
		}
		getsa();
		gethi();
		dikaer();
		bu(p[n].l, 1, n);
		dfs(p[n].l);
		if (wei == -1)
			cout << "none\n";
		else
			cout << ans << " " << wei - 1 << "\n";
		ans = 0;
		wei = -1;
		memset(p, 0, sizeof(p));
		memset(maxn, 0, sizeof(maxn));
		memset(qq, 0, sizeof(qq));
	}
}
```

---

## 作者：L_zaa_L (赞：1)

## 前置知识
因为本文使用的算法是 SAM。

所以如果想要轻松的看懂这篇题解，可以看看我的文章[SAM学习笔记](https://zhuanlan.zhihu.com/p/665086302)或者左转[模板题](https://www.luogu.com.cn/problem/P3804)。

## 分析

### 求子串出现次数

对于每一个子串的出现次数，我们可以利用 parent 树进行计算。

对于每一次插入，一个类出现次数增加，当且仅当这是当前的后缀，也就是把这个点的 parent 链都加一。

之间将每个节点按照字符串最长的字符串的长度进行排序（一个等价类中，出现的次数一定相同，可以不算小的，节约时间）。

从下往上更新即可每个后缀出现的次数即可，很明显最开始的赋值只需要原串的后缀赋值即可，不能附多了。

```cpp

void query(){
	for(int i=1;i<=tot;i++) tag[len[i]]++;
	for(int i=1;i<=tot;i++) tag[i]+=tag[i-1];
	for(int i=1;i<=tot;i++) a[tag[len[i]]--]=i;//将树按照子树大小进行排序，方便从下往上更新（越往下子串长度越大）
        //这里运用的是基数排序
	for(int i=tot;i>=1;i--) siz[lnk[a[i]]]+=siz[a[i]];//从下往上进行更新。
	return;
}
```


这样我们既可以得到每个子串出现次数了，然后考虑如何找到最右边的。

## 求这个子串最右边的可能
我们需要引入一个新的定义 $lstappear_i$ 记录每个等价类出现的最右边的位置。

我们最开始新建点的时候，肯定出现了新的等价类，所以新增加的这个点的 $lstapper_{cur}$ 肯定是当前加入字符的位置 $loc$。

我们顺着 parent 树往上更新的时候，有时候需要新建个点 $copy$（将 $q$ 拆为两个部分），那么新建部分的 $lstappear_{copy}$ 就为原来的那个点的最右边出现的位置。

但这些还不是真正的最右边出现的，我们还得像上面出现次数 $siz$ 一样更新一遍，因为如果这个串出现过，那么他的 $lnk_x$ 也应该在这个位置出现过。

```cpp
#include<bits/stdc++.h>
#define int long long
#define For(i,a,b) for(int i=a,i##end=b;i<=i##end;i++)
#define Rof(i,a,b) for(int i=a,i##end=b;i>=i##end;i--)
#define rep(i,  b) for(int i=1,i##end=b;i<=i##end;i++)
using namespace std;
const int N=2e5+5;
//char buf[(1<<21)+5],*p1,*p2;
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
void chmx(int &x,int y){(x<y)&&(x=y);}
void chmn(int &x,int y){(x>y)&&(x=y);}
inline int read(){
	int f=0,x=0;
	char ch=getchar();
	while(!isdigit(ch)){f|=(ch=='-');ch=getchar();}
	while(isdigit(ch)){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return f?-x:x;
}
int lnk[2000005];
map<int,int>ch[2000005];
int len[2000005],last,tot;
int siz[2000005],lstappear[2000005];
inline void insert(int c,int loc){//后缀自动机板子
	int p=last,cur=++tot;
	last=cur;
	len[cur]=len[p]+1;
	lstappear[cur]=loc;//赋值
	for(;p&&!ch[p].count(c);p=lnk[p]) ch[p][c]=cur;
	if(!p) lnk[cur]=1;
	else{
		int q=ch[p][c];
		if(len[p]+1==len[q]) lnk[cur]=q;
 		else{
 			int copy=++tot;
 			lstappear[copy]=lstappear[q];//新的等价类的出现位置。
 			len[copy]=len[p]+1;lnk[copy]=lnk[q];
 			ch[copy]=ch[q];
 			lnk[q]=lnk[cur]=copy;
 			for (;ch[p].count(c)&&p;p=lnk[p]){
 				if(ch[p][c]==q)ch[p][c]=copy;
 				else break;
 			}
 		}	
	}
	siz[cur]=1;
}
int tag[2000005],a[2000005];
inline void query(){
	for(int i=1;i<=tot;++i) tag[len[i]]++;
	for(int i=1;i<=tot;++i) tag[i]+=tag[i-1];
	for(int i=1;i<=tot;++i) a[tag[len[i]]--]=i;//按长度排，基数排序
	for(int i=tot;i>=1;--i){
		siz[lnk[a[i]]]+=siz[a[i]];
		lstappear[lnk[a[i]]]=max(lstappear[lnk[a[i]]],lstappear[a[i]]);//更新出现次数和最右边的位置
	}
}
int m;
signed main(){
	//freopen("SP10079.in","r",stdin);
	//freopen("zaa.out","w",stdout);
	int T=1e9;
	while(T--){
		for(int i=0;i<=tot+1;i++){
			lstappear[i]=a[i]=siz[i]=tag[i]=len[i]=lnk[i]=0;
			ch[i].clear();
		}
		last=tot=1;
		string s;
		m=read();
		if(m==0) break;
		cin>>s;
		for(int i=0;i<s.size();++i){
			insert(s[i]-'a',i+1);
		}
		query();
		int maxlen=-1,p=0;
		for(int i=tot;i>=1;i--){
			if(siz[a[i]]>=m){
				if(maxlen<len[a[i]]){//求长度最大且出现最右边的串
					maxlen=len[a[i]];
					p=lstappear[a[i]]-len[a[i]];
				}
				else if(maxlen==len[a[i]]){
					p=max(p,lstappear[a[i]]-len[a[i]]);
				}
			}
		}
		if(maxlen)printf("%lld %lld\n",maxlen,p);//判断无解
		else puts("none");
	}
	return 0;
}

```




---

## 作者：凤年 (赞：0)

求出至少出现 $m$ 次的最长字符串并输出其长度以及起始位置最大值。

给 SAM 定义一个 $firstpos_v$ 记录当前状态出现的末端位置。

维护方式：

- 当加入新字符创建节点 $now$ 时令：
$$\text{firstpos}(now) = \text{len}(p) - 1$$
- 当复制节点创建一个 $tmp$ 令：
$$\text{firstpos}(tmp) = \text{firstpos}(q)$$

（因为如果该值选 $\text{firstpos}(now)$ 就太大了。）

求长度不用说相信都会。
求串 $S$ 位置则是求
$$\text{firstpos}(t_0) - |S| - 1$$

其中 $t_0$ 表示 $S$ 在 SAM 中的状态。

再维护一个 $siz_v$ 表示状态 $v$ 的等价类大小，如果有 $siz_v \geq m$ 则让

```cpp
len = sam[now].len;
pos = max(pos, sam[now].firstpos - sam[now].len + 1);
```

于是这个题就可以快乐的 AC 了 ~~（SAM 的题好像好多都挺水的）。~~

```cpp
#include <bits/stdc++.h>
#define LL long long
#define N 40010
using namespace std;

int m;
char s[N];
LL ans, siz[N << 1];
int cnt[N], order[N << 1];


int tot = 1, last = 1;
struct SAM {
    int firstpos, fa, len, nex[26];
}sam[N << 1];

void clear() {
    tot = last = 1;
    memset(siz, 0, sizeof(siz));
    memset(cnt, 0, sizeof(cnt));
    memset(sam, 0, sizeof(sam));
    memset(order, 0, sizeof(order));
}

void add(int x, int i) {
    int now = ++tot, p = last;
    siz[now] = 1;
    sam[now].firstpos = i;
    sam[now].len = sam[p].len + 1;
    for(;p&&!sam[p].nex[x];p = sam[p].fa) sam[p].nex[x] = now;
    if(!p) sam[now].fa = 1;
    else {
        int q = sam[p].nex[x];
        if(sam[q].len == sam[p].len + 1) sam[now].fa = q;
        else {
            int tmp = ++tot;
            sam[tmp] = sam[q];
            sam[q].fa = sam[now].fa = tmp;
            sam[tmp].len = sam[p].len + 1;
            for(;p&&sam[p].nex[x] == q; p = sam[p].fa) sam[p].nex[x] = tmp;
        }
    }
    last = now;
}
void work() {
    int n = strlen(s), len = 0, pos = -1;
    for(int i = 0;i < n; ++i) add(s[i] - 'a', i);
    for(int i = 1;i <= tot; ++i) ++cnt[sam[i].len];
    for(int i = 1;i <= n; ++i) cnt[i] += cnt[i - 1];
    for(int i = 1;i <= tot; ++i) order[cnt[sam[i].len]--] = i;
    for(int i = tot, now, fa;i >= 1; --i) {
        now = order[i];
        fa = sam[now].fa;
        if(siz[now] >= m) {
            if(sam[now].len >= len) {
                len = sam[now].len;
                pos = max(pos, sam[now].firstpos - sam[now].len + 1);
            }
        }
        siz[fa] += siz[now];
        sam[fa].firstpos = max(sam[fa].firstpos, sam[now].firstpos);
    }
    if(len) printf("%d %d\n", len, pos);
    else printf("none\n");
}

int main() {
    while(scanf("%d", &m) == 1) {
        if(!m) return 0;
        clear();
        scanf("%s", s);
        work();
    }
    return 0;
}
```


---

## 作者：Acerkaio (赞：0)

### 题外话：

双倍经验：[https://www.luogu.com.cn/problem/UVA12206](https://www.luogu.com.cn/problem/UVA12206)

### 题目简述：

在字符串 $s$ 中找出出现次数至少为 $n$ 的最长连续子串（不包括空串），并且输出最右边的起始位置，如果不存在输出 `none`。

### 算法：

字符串 hash 加二分。

### 思路：

我们先 hash 一下字符串，这样方便我们后面求出 $s$ 中每段的 hash 值，不会[字符串哈希？](https://www.luogu.com.cn/problem/P3370)

二分长度，对于每次 check ，我们开一个桶，用于储存每个哈希值的出现次数，然后从在字符串中枚举每一段，每一段 $O(1)$ 求出这一段的哈希值，然后在桶里的出现次数就加一，发现出现次数多余 $n$ 了，就更新最右边的起始位置，如果次数没有多余 $n$ 那么肯定是查询的长度过长了。所以往长度更小二分。

Q：此题为什么满足单调性（以下所说的连续子串排除本身与空串）？

A： $s$ 中，如果出现了它的连续子串 `abc` 三次，假如为如下：

```
...abc...abc...abc...
```
那么 `ab` 也一定出现了，因为 `ab` 是 `abc` 的连续子串，即为：

```
...ab(c)...ab(c)...ab(c)...
```
同理，则 `bc` 也同样出现了三次。

但如果是这样的：

```
...abc...abc...abc...bc...
```
那么 `bc` 出现了 4 次。

易得：当一个字符串的连续子串出现了 $x$ 次时，那么这个字符串的连续子串的连续子串也是这个字符串的连续子串且至少出现了 $x$ 次。

Q：为什么如果次数没有多余 $n$ 那么肯定是查询的长度过长了？

A：同上面的结论，当一个字符串的连续子串出现了 $x$ 次时，那么这个字符串的连续子串的连续子串也是这个字符串的连续子串且至少出现了 $x$ 次。

所以这个字符串的连续子串的连续子串可能多余 $x$ 次，所以往长度小来二分就有可能查找到大于 $n$ 次的次数。

### CDOE

```cpp
#include <bits/stdc++.h>
#define ull unsigned long long
using namespace std;
int P = 131;
ull p[100001];
long long last, n;
inline bool check(vector<ull> vu, string s, int len) {
	map <ull, int> num;
	bool flag = 0;
	for (int i = 1; i <= s.size() - len + 1; i++) {
		int c = (++num[vu[i + len - 1] - vu[i - 1] * p[len]]);
		if (c >= n) {
			flag = 1;
			last = i - 1;
		}
	}
	return flag;
}
signed main() {
	string s;
	p[0] = 1;
	for (int i = 1; i < 40005; i++) {
		p[i] = p[i - 1] * P;
	}
	while (cin >> n && n) {
		cin >> s;
		int lens = s.size();
		ull temp = 0;
		vector <ull> ve;
		ve.push_back(0);
		for (int i = 0; i < s.size(); i++) {
			ve.push_back((temp * P + (s[i] - 'a' + 1)));
			temp = ve.back();
		}
		int l = 1, r = lens;
		int answer = 114514, anslast = -1;
		while (l <= r) {
			long long  mid = l + r >> 1;
			if (check(ve, s, mid) == 1) {
				l = mid + 1;
				answer = mid;
				anslast = last;
			} else {
				r = mid - 1;
			}
		}
		if (answer == 114514) {
			cout << "none\n";
		} else {
			cout << answer << ' ' << anslast << '\n';
		}
	}
	return 0;
}
```


---

## 作者：Usada_Pekora (赞：0)

首先不难想到一个 $O(n^3\log n)$ 的做法：枚举长度，枚举起点，然后用 `std::map` 维护一个串的出现次数。由于答案存在单调性，即若一个子串 $s^{'}$ 可行，则 $s^{'}$ 的子串也是可行的，所以长度的枚举考虑使用二分解决，复杂度降到了 $O(n^2\log^2n)$。

现在的瓶颈在于：如何快速的将子串取出并比较。

可以采用字符串哈希，将整个字符串转化成一个 $p$ 进制数，维护一个前缀哈希值序列 $h$，那么子串 $[l,r]$ 的哈希值是 $h_r-h_{l-1}\times p^{r-l+1}$（将缺少的位补齐）。这样就能 $O(n\log^2 n)$ 求解了。

采用纯哈希做法可以做到期望 $O(n\log n)$，常数比较小，拿下了最优解，甚至可以超过线性的 SAM 做法。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 4e4 + 5, P = 131, mod = 998244353, Mod = 69317;
typedef long long ll;
int n, k, ans1, ans2;
ll p[N], hsh[N];
char s[N];
pair<int, int> f[N];
int fir[Mod], nxt[N], fi[N], se[N], idx;
inline int hshv(int x) {
	return 37u * x % Mod;
}
inline void ins(int x, int _fi, int _se) {
	fi[++idx] = _fi;
	se[idx] = _se;
	nxt[idx] = fir[x];
	fir[x] = idx;
}
inline int findv(int x) {
	int pos = hshv(x);
	for (int i = fir[pos]; i; i = nxt[i]) {
		if (fi[i] == x) {
			se[i]++;
			return i;
		}
	}
	ins(pos, x, 1);
	return idx;
}
inline int hshval(int l, int r) {
	return (hsh[r] - hsh[l - 1] * p[r - l + 1] % mod + mod) % mod;
}
inline int check(int x) {
	int cnt = 0;
	f[0].first = -1;
	for (int i = x; i <= n; i++) {
		f[++cnt] = make_pair(hshval(i - x + 1, i), i - x + 1);
	}
	idx = 0;
	memset(fir, 0, sizeof fir);
	int res = 0;
	for (int i = 1; i <= cnt; i++) {
		int it = findv(f[i].first);
		if (se[it] >= k) res = f[i].second;
	}
	return res;
}
signed main() {
	p[0] = 1;
	for (int i = 1; i < N; i++) p[i] = p[i - 1] * P % mod;
	while (scanf("%d", &k) != EOF && k) {
		scanf("%s", s + 1);
		n = strlen(s + 1);
		for (int i = 1; i <= n; i++) hsh[i] = (hsh[i - 1] * P + s[i]) % mod;
		int l = 1, r = n, nos = 0;
		while (l <= r) {
			int mid = (l + r) >> 1, t;
			if ((t = check(mid)) > 0) nos = 1, ans1 = mid, ans2 = t, l = mid + 1;
			else r = mid - 1;
		}
		if (!nos) puts("none");
		else printf("%d %d\n", ans1, ans2 - 1);
	}
	return 0;
}
```


---

## 作者：__stick (赞：0)

# 题意
## 题意
给定一个字符串 $s$ 和整数 $m$ , 求 $s$ 中出现至少 $m$ 次的字符串的最长长度及这个长度的满足要求的字符串最后一次出现时这个字符串的起始位置。
## 思路
不难想到使用后缀数组解决，首先跑出来 sa，height 数组。

首先有一个简单的转化，就是出现次数等价于在所有后缀的前缀中的出现次数，所以想要出现 $m$ 次就最少要在 $m$ 个后缀中出现，然后也就等价于至少有 $m$ 个后缀的 lcp 等于这个字符串，所以我们就要找出这有哪些后缀的 lcp 可以被满足，这里有一个常用技巧，就是找出每个 height 作为最小值出现的区间（排序后），然后这个区间的 lcp 就是这个最小值，原因显然，所以就可以使用单调栈跑出来每个 height 的区间，枚举每个 height 看看对应的区间大小是否满足条件，如果满足就将答案和这个区间的 height 取 max。

这个题最恶心的是要输出下标，这个我没想到好办法，用了一个 ST 表维护排序后后缀在原串下标的区间最大值，每次取到这个区间的时候就暴力查询一下就行了，比较麻烦。

后来看了题解才知道可以用单调队列，不过我觉得我这种方法有一定可拓展性（~~真是自恋~~）。
## 代码
警钟长撅，某男子因为 ST 表
```cpp
for(int j=1;(1<<j)<=n;j++)
		for(int i=1;i+(1<<j)-1<=n;i++)
		{
			F[i][j]=max(F[i][j-1],F[i+(1<<j-1)][j-1]);
		}
```
第一个循环没带等于号 debug 一下午，不带等在 $n$ 等于 $2$ 的幂的时候会出错（也就是说我一直写的是错误的 ST 表?！）。
```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<vector>
#include<set>
#include<map>
#include<queue>
#include<bits/stdc++.h>
using namespace std;
template<typename T>
inline bool cmax(T& a,const T& b){return a<b?a=b,1:0;}
template<typename T>
inline bool cmin(T& a,const T& b){return b<a?a=b,1:0;}
typedef long long ll;
typedef pair<int,int> pii;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef vector<int> vi;
typedef vector<vector<int> > vii;
#define X first
#define Y second
#define mp make_pair
const int mod=1e9+7;
const int MAXN=1e6+10;
char a[MAXN];
int cnt[MAXN],x[MAXN],y[MAXN];
int sa[MAXN];

void get_sa(int n,int m)
{
	for(int i=0;i<=m;i++)cnt[i]=0;
	for(int i=1;i<=n;i++)cnt[x[i]=a[i]]++;
	for(int i=1;i<=m;i++)cnt[i]+=cnt[i-1];
	for(int i=n;i>=1;i--)sa[cnt[x[i]]--]=i;
	for(int k=1;k<=n;k<<=1)
	{
		int num=0;
		for(int i=n-k+1;i<=n;i++)y[++num]=i;
		for(int i=1;i<=n;i++)if(sa[i]>k)y[++num]=sa[i]-k;
		for(int i=0;i<=m;i++)cnt[i]=0;
		for(int i=1;i<=n;i++)cnt[x[i]]++;
		for(int i=1;i<=m;i++)cnt[i]+=cnt[i-1];
		for(int i=n;i>=1;i--)sa[cnt[x[y[i]]]--]=y[i],y[i]=0;
		swap(x,y);
		x[sa[1]]=1;num=1;
		for(int i=2;i<=n;i++)
		x[sa[i]]=((y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k])?num:++num);
		if(num==n)break;m=num;
	}
} 
int rk[MAXN];
int hi[MAXN];
void get_hi(int n)
{
	for(int i=1;i<=n;i++)rk[sa[i]]=i;
	int k=0;
	for(int i=1;i<=n;i++)
	{
		if(rk[i]==1)continue;
		if(k)k--;int j=sa[rk[i]-1];
		while(i+k<=n&&j+k<=n&&a[i+k]==a[j+k])k++;
		hi[rk[i]]=k;
	}
}
int main()
{
	ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0);cout<<fixed<<setprecision(20);
	int m;
	while(1)
	{
		cin>>m;
		if(!m)break;
		cin>>a+1;
		int n=strlen(a+1);
		if(m==1)
		{
			cout<<n<<' '<<0<<'\n';
			continue;
		}
		get_sa(n,5000),get_hi(n);
		vi s(n+1);int top=0;
		vi l(n+1),r(n+1);
		for(int i=1;i<=n;i++)
		{
			while(top&&hi[s[top]]>=hi[i])top--;			
			l[i]=s[top]+1;
			s[++top]=i;
		}
		top=0;
		s[0]=n+1;
		for(int i=n;i>=1;i--)
		{
			while(top&&hi[s[top]]>=hi[i])top--;		
			r[i]=s[top]-1;
			s[++top]=i;
		}
		int ans=0,id=0;
		vii F(n+1,vi(20));
		for(int i=1;i<=n;i++)F[i][0]=sa[i];
		for(int j=1;(1<<j)<=n;j++)
			for(int i=1;i+(1<<j)-1<=n;i++)
			{
				F[i][j]=max(F[i][j-1],F[i+(1<<j-1)][j-1]);
			}
		auto ask=[&](int l,int r)
		{
			int k=log2(r-l+1);
			return max(F[l][k],F[r-(1<<k)+1][k]);
		};
		for(int i=1;i<=n;i++)
		{
			if(!hi[i])continue;
			if(r[i]-l[i]+2>=m)
			{
				if(hi[i]>=ans)
				{
					if(hi[i]==ans)cmax(id,ask(l[i]-1,r[i]));
					else id=ask(l[i]-1,r[i]);
					ans=hi[i];
					
				}
			}
		}
		if(!ans)
		{
			cout<<"none\n";
			continue;
		}
		cout<<ans<<' '<<id-1<<'\n';
	}
	return 0;
}
```


---

## 作者：望月Asta (赞：0)

### 题意

给出一个字符串与一个正整数 $m$，求出现 **不少于** $m$ 次的子串中最长的。

同时求出这个子串在原串中最大的左端点位置，且这里认为字符串下标从 $0$ 开始。

如果有多解选择最靠右的。

双倍经验 [UVA12206](https://www.luogu.com.cn/problem/UVA12206)

### 解法

求子串问题还有对出现次数的限制,考虑使用 SAM.

求出现次数参考 [SAM 模板](https://www.luogu.com.cn/problem/P3804) 在 parent 树上树形 DP 即可。

求最右侧位置也可以使用类似的方式，从子节点中取 $\max$ 。

其中 parent 树可以不建立出来而是直接用拓扑序代替。

本题有多测，使用 SAM 求解一定要注意清空数组。

建立 SAM 复杂度为线性，基数排序求拓扑序为线性，树形 DP 更新答案为线性，总体复杂度 $\mathcal{O} (n)$。

即使 SAM 常数较大，这道题上速度还是远超二分 + 哈希。

### 代码

删除读写优化以及替换了一些宏定义.

```cpp
struct SuffixAutomaton {
	int tot,lst;
	struct Node {
		int len,link;
		int ch[26];
	}st[N << 1];
	
	int buc[N];
	int id[N << 1],siz[N << 1];
	int rpos[N << 1];
	
	SuffixAutomaton() : tot(1),lst(1) {}
	
	inline void extend(int ch) {
		int cur = ++tot,p = lst;lst = tot;
		siz[cur] = 1,rpos[cur] = st[cur].len = st[p].len + 1;
        	// 更新 len 时同时也更新最右侧出现位置
		for(;p && !st[p].ch[ch];p = st[p].link)
			st[p].ch[ch] = cur;
		if(!p) st[cur].link = 1;
		else {
			int q = st[p].ch[ch];
			if(st[q].len == st[p].len + 1)
				st[cur].link = q;
			else {
				int pp = ++tot;st[pp] = st[q];
				st[pp].len = st[p].len + 1;
				st[q].link = st[cur].link = pp;
				for(;p && st[p].ch[ch] == q;p = st[p].link)
					st[p].ch[ch] = pp;
			}
		}
	}
	
	inline void init() {
		tot = lst = 1;
		memset(st,0,sizeof(st));
		memset(id,0,sizeof(id));
		memset(buc,0,sizeof(id));
		memset(siz,0,sizeof(siz));
		memset(rpos,0,sizeof(rpos));
	}
	
	inline void solve(int n,int k) {
    		// 基排求拓扑序
		for(int i = 1;i <= tot;++i) ++buc[st[i].len];
		for(int i = 1;i <= n;++i) buc[i] += buc[i - 1];
		for(int i = tot;i;--i) id[buc[st[i].len]--] = i;
		int ans = 0,pos = 0;
		for(int i = tot;i;--i) {
			int p = id[i],fa = st[p].link;
			siz[fa] += siz[p];
			rpos[fa] = std::max(rpos[fa],rpos[p]);// 从子节点继承信息
			if(siz[p] >= k && i != 1) {
				if(st[p].len > ans) ans = st[p].len,pos = rpos[p] - st[p].len;
				else if(st[p].len == ans) pos = std::max(pos,rpos[p] - st[p].len);
			}
		}
		if(ans) {
			write(ans),space,write(pos);
			enter;
		}
		else {
			putC('n'),putC('o'),putC('n'),putC('e');
			enter;
		}
	}
}SAM;

char s[N];

int main() {
	init_IO();
	int k = read();
	while(k) {
		SAM.init();
		int n = getStr(s + 1);
		for(int i = 1;i <= n;++i)
			SAM.extend(s[i] - 'a');
		SAM.solve(n,k);
		k = read();
	}
	end_IO();
	return 0;
}
```


---

## 作者：Mars_Dingdang (赞：0)

后缀数组练习题之一，双倍经验 UVA12206。

## 题目大意
给定一个长度为 $n$ 的字符串，以及一个常数 $k$，求出现次数至少为 $k$ 次的可重叠的子串的最长长度，以及该子串最大的可能起始位置。

多组数据，$k\le n\le 40000$。

## 大体思路
本题所求的长度与 [P2852](https://www.luogu.com.cn/problem/P2852) 相同，只需要二分长度，转换为判断是否存在长度为 $len$ 的子串满足要求。此时可以通过对 $\text{LCP}\ge len$ 的后缀进行分组，即如果存在连续的 $height_i\ge len$ 的数量 $\ge k$，则说明满足条件。

此外，本题还要求出最大的可能起始位置，可以在二分的 $\text{check}$ 函数中进行判断，令 $t$ 表示某一组后缀中 $sa$ 的最大值，则如果这一组合法（即大小 $\ge k$），则 $ans\leftarrow \max(ans, t)$。

除此以外，还有两个小细节：

1. 如果 $k=1$，按照这种方式进行判断会出错，所以特判 $k=1$ 时答案为 `n 0`。

2. 本题的下标从 $0$ 开始，因此如果代码习惯下标从 $1$ 开始，输出位置时要 $-1$。

## 完整代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define rep(ii,aa,bb) for(re int ii = aa; ii <= bb; ii++)
#define Rep(ii,aa,bb) for(re int ii = aa; ii >= bb; ii--)
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef pair<int, int> PII;
const int maxn = 1e5 + 5;
namespace IO_ReadWrite {
	#define re register
	#define gg (p1 == p2 && (p2 = (p1 = _buf) + fread(_buf, 1, 1<<21, stdin), p1 == p2) ? EOF :*p1++)
	char _buf[1<<21], *p1 = _buf, *p2 = _buf;
	template <typename T>
	inline void read(T &x){
		x = 0; re T f=1; re char c = gg;
		while(c > 57 || c < 48){if(c == '-') f = -1;c = gg;}
		while(c >= 48 &&c <= 57){x = (x<<1) + (x<<3) + (c^48);c = gg;}
		x *= f;return;
	}
	inline void ReadChar(char &c){
		c = gg;
		while(!isalpha(c)) c = gg;
	}
	template <typename T>
	inline void write(T x){
		if(x < 0) putchar('-'), x = -x;
		if(x > 9) write(x/10);
		putchar('0' + x % 10);
	}
	template <typename T>
	inline void writeln(T x){write(x); putchar('\n');}
}
using namespace IO_ReadWrite;
int n, k, m;
char s[maxn];
int x[maxn], y[maxn], cnt[maxn], sa[maxn], height[maxn], rk[maxn];
inline void getSA() {
	rep(i, 1, n) cnt[x[i] = s[i]] ++;
	rep(i, 2, m) cnt[i] += cnt[i - 1];
	Rep(i, n, 1) sa[cnt[x[i]] --] = i;
	for(int k = 1; k <= n; k <<= 1) {
		int tot = 0;
		rep(i, n - k + 1, n) y[++tot] = i;
		rep(i, 1, n)
			if(sa[i] > k) y[++tot] = sa[i] - k;
		rep(i, 1, m) cnt[i] = 0;
		rep(i, 1, n) cnt[x[i]] ++;
		rep(i, 2, m) cnt[i] += cnt[i - 1];
		Rep(i, n, 1) sa[cnt[x[y[i]]] --] = y[i], y[i] = 0;
		swap(x, y);
		x[sa[1]] = 1, tot = 1;
		rep(i, 2, n)
			x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k]) ? tot : ++tot;
		if(tot >= n) break;
		m = tot;
	}
}
inline void getH() {
	rep(i, 1, n) rk[sa[i]] = i;
	for(int i = 1, k = 0; i <= n; i ++) {
		if(rk[i] == 1) continue;
		if(k) k --;
		int j = sa[rk[i] - 1];
		while(i + k <= n && j + k <= n && s[i + k] == s[j + k]) k ++;
		height[rk[i]] = k;
	}
}
inline int check(int len) {
	int cnt = 0, mx = -1, tmp = 0;
	rep(i, 1, n) {
		if(height[i] < len) {
			cnt = 1;
			tmp = sa[i];
		} else {
			cnt ++;
			tmp = max(tmp, sa[i]);
		}
		if(cnt >= k) mx = max(mx, tmp);
	}
	return mx;
}
int ans, pos;
inline void Binary(int L, int R) {
	while(L <= R) {
		int mid = (L + R) >> 1;
		int t = check(mid);
		if(t == -1) R = mid - 1;
		else {
			ans = mid;
			pos = t;
			L = mid + 1;
		}
	}
}
int main () {
	while(1) {
		scanf("%d", &k);
		if(k == 0) return 0;
		scanf("%s", s + 1);
		n = strlen(s + 1), m = 128;
		if(k == 1) {
			write(n), putchar(' '), writeln(0);
			continue;
		}
		memset(cnt, 0, sizeof cnt);
		memset(sa, 0, sizeof sa);
		memset(height, 0, sizeof height);
		ans = pos = 0;
		getSA();
		getH();
		Binary(1, n);
		if(!ans) puts("none");
		else write(ans), putchar(' '), writeln(pos - 1);		
	}
	
	return 0;
}
```

---

