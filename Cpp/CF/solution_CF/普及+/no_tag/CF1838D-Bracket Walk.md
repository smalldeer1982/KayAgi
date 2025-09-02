# Bracket Walk

## 题目描述

There is a string $ s $ of length $ n $ consisting of the characters '(' and ')'. You are walking on this string. You start by standing on top of the first character of $ s $ , and you want to make a sequence of moves such that you end on the $ n $ -th character. In one step, you can move one space to the left (if you are not standing on the first character), or one space to the right (if you are not standing on the last character). You may not stay in the same place, however you may visit any character, including the first and last character, any number of times.

At each point in time, you write down the character you are currently standing on. We say the string is walkable if there exists some sequence of moves that take you from the first character to the last character, such that the string you write down is a regular bracket sequence.

A regular bracket sequence is a bracket sequence that can be transformed into a correct arithmetic expression by inserting characters '1' and '+' between the original characters of the sequence. For example, bracket sequences "()()", "(())" are regular (the resulting expressions are: "(1)+(1)", "((1+1)+1)"), and ")(" and "(" are not.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1838D/258127971c1944c307e76094dff5383eb1dfb8b7.png)One possible valid walk on $ s=\mathtt{(())()))} $ . The red dot indicates your current position, and the red string indicates the string you have written down. Note that the red string is a regular bracket sequence at the end of the process.You are given $ q $ queries. Each query flips the value of a character from '(' to ')' or vice versa. After each query, determine whether the string is walkable.

Queries are cumulative, so the effects of each query carry on to future queries.

## 说明/提示

In the first example:

- After the first query, the string is (())()()(). This string is a regular bracket sequence, so it is walkable by simply moving to the right.
- After the second query, the string is (())()))(). If you move right once, then left once, then walk right until you hit the end of the string, you produce the string (((())()))(), which is a regular bracket sequence.
- After the third query, the string is ()))()))(). We can show that this string is not walkable.

 In the second example, the strings after the queries are ()) and ()(, neither of which are walkable.

## 样例 #1

### 输入

```
10 9
(())()()))
9
7
2
6
3
6
7
4
8```

### 输出

```
YES
YES
NO
NO
YES
NO
YES
NO
NO```

## 样例 #2

### 输入

```
3 2
(()
2
3```

### 输出

```
NO
NO```

# 题解

## 作者：TLEWA (赞：8)

显然串长度为奇数的情况下怎么走括号都不可能匹配（数量不可能相等），我们只需要专心考虑偶数的情况。

思考我们什么时候需要往左走，如果我们往回走的位置是 `()`，那么走几次都不会对答案产生影响，对于 `)(` 同理，对于连续括号（`((` 和 `))`），我们可以一直走将括号数量不断叠加，由于非连续括号段不会对答案产生影响，我们考虑维护一个新括号序列用来记录连续括号。

新序列形如 `))(((())` 和 `(())(())))`，我们发现由于向左操作的存在，所以一个连续括号可以和任意多的连续括号匹配，我们只需要考虑连续括号的位置和是否存在即可，我们讨论几种情况：

1. 没有连续括号，合法
1. 只有一种连续括号，不合法
1. 有两种连续括号，如果第一个连续括号是 `((` 且最后一个连续括号为 `))`，合法，其余情况均不合法。

最后用 set 维护一下新括号序列，这道题就被我们解决了。

AC 代码：

```cpp
#include<bits/stdc++.h>

using namespace std;

int n,q,p;
string s;

set<int> L,R;

int main() {
	cin >> n >> q >> s;
	s=' '+s;
	for(int i=1;i!=n;++i) {
		if(s[i+1]==s[i]) {
			if(s[i]=='(') L.insert(i);
			else R.insert(i);
		}
	}
	
	while(q--) {
		cin >> p;
		if(n%2) {cout << "NO" << endl;continue;}
		if(p!=1 && s[p]==s[p-1]) {
			if(s[p]=='(') L.erase(p-1);
			else R.erase(p-1); 
		}
		if(p!=n && s[p]==s[p+1]) {
			if(s[p]=='(') L.erase(p);
			else R.erase(p); 
		}
		if(s[p]=='(') s[p]=')';
		else s[p]='(';
		if(p!=1 && s[p]==s[p-1]) {
			if(s[p]=='(') L.insert(p-1);
			else R.insert(p-1);
		}
		if(p!=n && s[p]==s[p+1]) {
			if(s[p]=='(') L.insert(p);
			else R.insert(p); 
		}
		if(s[1]==')' || s[n]=='(') cout << "NO" << endl;
		else if(L.empty() && R.empty()) cout << "YES" << endl;
		else if(L.empty() || R.empty()) cout << "NO" << endl;
		else if( (*L.begin()<*R.begin()) && (*L.rbegin()<*R.rbegin()) ){
			cout << "YES" << endl;
		}else cout << "NO" << endl;
	}
	return 0;
}

```

---

## 作者：World_Creater (赞：6)

玄学题。

首先判掉长度奇数的情况，这种情况无论怎么走走出来的串长都是奇数，不合法。

对于一个偶数的串，显然开头必须是左括号，结尾必须是右括号。

在满足以上条件中，不妨思考什么时候，我们会向左折返而不是向右走。

显然，我们只有在遇到连续两个相同括号时，才会向左走，不然不同的括号直接抵消了，而我们遇到连续括号时，我们可以反复横跳把这种括号叠满。

我们把所有连续的括号位置记下来，然后讨论几种情况：
1. 没有连续括号，显然合法。
2. 只有连续左括号或者连续右括号：寄了，某种括号太多了。
3. 都有：那么要求第一个连续括号是连续左括号且最后一个连续括号是连续右括号。

最后一种情况的条件是合法的，行走方案就是先把最左边的左括号叠满，然后走到最右边是再抵消掉，剩下的段一定左右括号交替，一定合法。

如果第一个连续括号是右括号，那么前面我们括号串是左右括号交替的，这时候你发现走到这里的时候左括号不够用了，并且也不存在连续的左括号给你补足左括号。

如果最后一个连续括号是左括号，那么走到这里左括号就过多了，而且你也不能前面“欠着”左括号再到这里补起来。

综上，维护所有连续的括号即可（只需要维护连续的两个就够用了）。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
set<int> s1,s2,s3,s4;
int n,q;
char s[200005];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>q>>s+1;
	for(int i=1;i<=n;i++)
	{
		if(s[i]=='(')
		{
			s1.insert(i);
			if(i!=1&&s[i-1]=='(') s3.insert(i);
		}
		if(s[i]==')')
		{
			s2.insert(i);
			if(i!=1&&s[i-1]==')') s4.insert(i);
		}
	}
	while(q--)
	{
		int x;
		cin>>x;
		if(n&1)
		{
			cout<<"NO\n";
			continue ;
		}
		if(s[x]=='(')
		{
			auto it=s1.upper_bound(x);
			s3.erase(x);
			if(it!=s1.end()&&*it-x==1) s3.erase(*it);
			s1.erase(x);
			it=s2.upper_bound(x);
			if(it!=s2.end()&&*it-x==1) s4.insert(*it);
			if(it!=s2.begin())
			{
				it--;
				if(x-*it==1) s4.insert(x);
			}
			s2.insert(x);
			s[x]=')';
		}
		else
		{
			auto it=s2.upper_bound(x);
			s4.erase(x);
			if(it!=s2.end()&&*it-x==1) s4.erase(*it);
			s2.erase(x);
			it=s1.upper_bound(x);
			if(it!=s1.end()&&*it-x==1) s3.insert(*it);
			if(it!=s1.begin())
			{
				it--;
				if(x-*it==1) s3.insert(x);
			}
			s1.insert(x);
			s[x]='(';
		}
		if(s[1]==')'||s[n]=='(') cout<<"NO\n";
		else if(s3.empty()&&s4.empty())
		{
			cout<<"YES\n";
		}
		else if(s3.empty()||s4.empty()) cout<<"NO\n";
		else 
		{
			int x=*s3.begin(),y=*s4.begin(),u=*s3.rbegin(),v=*s4.rbegin();
			cout<<(x<y&&u<v?"YES\n":"NO\n");
		}
	}
}
```


---

## 作者：_zqh_ (赞：3)

> 涉及知识点：字符串、STL、括号匹配。

~~赛时推出的结论有一点问题，代码也挂了。~~

首先，不难想到，如果一个字符串要重复走相同的位置其增加的长度一定是偶数。

其次，一个匹配的括号串一定是偶数长度。

那么，原长度为奇数的字符串一定不能通过重复走相同的位置而构成匹配的括号串。

直接全部输出 `NO` 即可。

显然，如果重复走的位置为 `()` 没有对答案产生任何贡献，`)(` 也同理，故不需要重复走这两种位置。

那么用两个 `set` 维护一下 `((` 和 `))` 的情况即可。

- 首先，考虑一种特殊情况，修改后第一个字符为 `)` 或最后一个字符为 `(`，显然不可能通过操作使其匹配，输出 `NO`。
- 接着，如果不存在 `((` 和 `))` 的情况，即两个 `set` 为空，该字符串一定形如 `()()()()`，一定可以匹配，输出 `YES`。
- 再者，如果第一组连续两个相同括号为 `((`，最后一组为 `))`，一定可以匹配，因为可以重复走 `((` 和 `))` 进行调整。
- 最后，以上条件都不满足，无法匹配，输出 `NO`。

丑陋的代码：

```cpp
#include <bits/stdc++.h>
// #pragma GCC optimize(2)
#define int long long
#define pii pair<int, int>
#define piiii pair<pii, pii>
#define il inline
#define p_q priority_queue
#define u_m unordered_map
#define bt bitset
#define rg register
#define rd Nothing::read
#define wt Nothing::write
#define endl '\n'

using namespace std;

namespace Nothing {
	il int read() {
		int f = 1, t = 0;
		char ch = getchar();
		while (ch < '0' || ch > '9') {
			if ( ch == '-' ) {
				f = -1;
			}
			ch = getchar();
		}
		while (ch >= '0' && ch <= '9') {
			t = t * 10 + ch - '0';
			ch = getchar();
		}
		return t * f;
	}

	il void write(int x, bool s) {
		if (x < 0) {
			putchar('-');
			write(-x, false);
			return ;
		}
		if (!s && x == 0)
			return ;
		if (s && x == 0) {
			putchar('0');
			return ;
		}
		write(x / 10, false);
		putchar(x % 10 + '0');
	}
}

const int N1 = 300005;
const int N2 = 1000006;
const int Mod = 998244353;

namespace COMB {
	int fac[N2] = {0};
	il void Cinit(int p) {
		fac[0] = 1;
		for (int i = 1; i < N2; i++) {
			fac[i] = fac[i - 1] * i % p;
		}
	}
	il int qpow(int a, int b, int p) {
		int ans = 1;
		while (b) {
			if (b & 1) {
				ans = ans * a % p;
			}
			a = a * a % p;
			b >>= 1;
		}
		return ans;
	}
	il int C(int n, int m, int p) {
		if (m > n || m < 0) {
			return 0;
		}
		return fac[n] * qpow(fac[m], p - 2, p) % p * qpow(fac[n - m], p - 2, p) % p;
	}
	il int Lucas(int n, int m, int p) {
		if (!m) return 1;
		return (C(n % p, m % p, p) * Lucas(n / p, m / p, p)) % p;
	}
	il int GCD(int n, int m, int p) {
		return __gcd(n, m) % p;
	}
	il int LCM(int n, int m, int p) {
		return n * m % p * qpow(GCD(n, m, p), p - 2, p) % p;
	}
}
using namespace COMB;
using namespace Nothing;

//#define debug 1
//#define multi_test 1
#define IOS 1

int T = 1;

set<int> lk, rk;//维护 '((' 和 '))'

int n, q;

string s;

void f(int x) {//反转括号
	s[x] = (s[x] == '(' ? ')' : '(');
}

void Init() {
	cin >> n >> q;
	cin >> s;
	for (int i = 1; i < s.size(); i++) {
		if (s[i - 1] == s[i]) {
			if (s[i] == '(') lk.insert(i - 1);
			else rk.insert(i - 1);
		}
	}
	return ;
}

void Solve() {
	if (n & 1) {
		while (q--) {
			cout << "NO\n";
		}
		return ;
	}
	while ( q-- ) {
		int x;
		cin >> x;
		x--;
		if (lk.find(x) != lk.end()) {//笔者把特判放这前面时不负众望地挂了
			lk.erase(x);
		}
		if (rk.find(x) != rk.end()) {
			rk.erase(x);
		}
		f(x);
		if (x && lk.find(x - 1) != lk.end()) {
			lk.erase(x - 1);
		}
		if (x && rk.find(x - 1) != rk.end()) {
			rk.erase(x - 1);
		}
		if (x && s[x] == s[x - 1]) {
			if (s[x] == '(') {
				lk.insert(x - 1);
			} else {
				rk.insert(x - 1);
			}
		}
		if (x < s.size() - 1 && s[x] == s[x + 1]) {
			if (s[x] == '(') {
				lk.insert(x);
			} else {
				rk.insert(x);
			}
		}
		if (s[0] == ')' || s[s.size() - 1] == '(') {
			cout << "NO\n";
			continue;
		}
		if (lk.empty() && rk.empty()) {
			cout << "YES\n";
			continue;
		}
		if (lk.empty() || rk.empty()) {
			cout << "NO\n";
			continue;
		}
		if (*(lk.begin()) < *(rk.begin()) && *(--lk.end()) < *(--rk.end())) {
			cout << "YES\n";
			continue;
		}
		cout << "NO\n";
	}
	return ;
}

signed main() {
#ifdef IOS
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
#endif
#ifdef debug
	freopen("zqh.in", "r", stdin);
	freopen("zqh.out", "w", stdout);
#endif
#ifdef multi_test
	cin >> T;
#endif
	while (T--) {
		Init();
		Solve();
	}
	return 0;
}
/*

*/
```

---

## 作者：xs_siqi (赞：3)

思维难度较低，代码长度稍长，调试需求低的小清新线段树+`set` 做法。

### 找结论

首先奇数肯定不合法，怎么走长度必然是奇数，不可能匹配。特判掉。

然后观察样例可以发现，向左走操作的唯一存在意义就是有两个相同且连续的（如果有多个相同且连续的，我们可以看做多组两个相同且连续的），然后去刷括号数量。

不难发现，你只要找到两个相同且连续的左括号，右边就不可能存在右括号大于左括号的情况。不管你右边是什么妖魔鬼怪，左边都能刷出很多括号来匹配你。因为是偶数，所以不可能括号因为奇偶性问题不匹配。

两个相同且连续的右括号也是同理的。左边就不可能存在左括号大于右括号的情况。

### 分类讨论

让我们梳理一下，还有什么没有考虑：

- 第一种：第一个两个连续左括号左边的右括号多于左括号（左括号多于右括号没关系，后面有两个连续的右括号，如果没有连续的，第二种情况能解决）

- 第二种：最后一个两个连续右括号的右边左括号多于右括号（同理）

### 维护

首先第一个问题是：如何维护第一个左括号，最后一个右括号？

动态加点删点，查找排名第一的操作，显然使用 `set` 维护。直接把下标放入 `set` 中即可。

第二个问题是：如何维护第一个左括号左边，最后一个右括号右边的情况？

这个问题可以转化为，第一个连续左括号左边，左括号的前缀和减去右括号的前缀和是否大于 $0$。右边同理。

要判断是否有元素大于 $0$，就是找序列最大值是否大于 $0$。

然后我们可以得到以下操作：动态区间，动态加权，动态求最大值。显然用线段树。

线段树维护前缀和差值以及后缀和差值，分别用于处理第一个连续左括号左边，最后一个连续右括号的右边的情况。

这样就把所有情况处理完了。

补充：tongzhenxuan 大神提出了：对于中间部分如果是奇数显然不合法。这件事情一开始的确没考虑到，但是这个程序也是对的。为什么呢？

我们发现：对于整个串是偶数的情况，第一个连续双左括号左边，和最后连续双右括号右边，显然只能是偶数，因此只有整个串是奇数，中间串才能是奇数。

为什么呢？考虑到，如果第一个连续双左括号左边是奇数，那么必定会有一种括号的数量更多。首先不可能是左括号更多。因为如果左括号更多，第一个连续双左括号的位置只会更左。也不可能是右括号，因为是右括号就无解了。右边同理。所以不需要判中间串是否是奇数。

```cpp
#include<bits/stdc++.h>
#define ls rt<<1
#define rs rt<<1|1
using namespace std;
const int maxn=2e5+5;
int x,q,n,t[maxn],sl[maxn],sr[maxn],le[maxn],ri[maxn],qz[maxn],hz[maxn];
char s[maxn];
set<int> l;
set<int> r;
struct tree{
	int Max[maxn*4],lz[maxn*4];
	inline void pushup(int rt){
		Max[rt]=max(Max[ls],Max[rs]);}
	inline void build(int a[],int rt,int l,int r){
		if(l==r){
			Max[rt]=a[l];
			return ;}
		int mid=(l+r)>>1;
		build(a,ls,l,mid),build(a,rs,mid+1,r);
		pushup(rt);}
	inline void pushdown(int rt){
		if(lz[rt]){
			Max[ls]+=lz[rt],Max[rs]+=lz[rt];
			lz[ls]+=lz[rt],lz[rs]+=lz[rt];}
		lz[rt]=0;}
	inline void modify(int rt,int l,int r,int ql,int qr,int p){
		if(ql<=l&&r<=qr){
			Max[rt]+=p;
			lz[rt]+=p;
			return ;}
		pushdown(rt);
		int mid=(l+r)>>1;
		if(ql<=mid)modify(ls,l,mid,ql,qr,p);
		if(mid<qr)modify(rs,mid+1,r,ql,qr,p);
		pushup(rt);}
	inline int query(int rt,int l,int r,int ql,int qr){
		if(ql<=l&&r<=qr)
			return Max[rt];
		pushdown(rt);
		int mid=(l+r)>>1,ans=-1e9;
		if(ql<=mid)ans=query(ls,l,mid,ql,qr);
		if(mid<qr)ans=max(ans,query(rs,mid+1,r,ql,qr));
		return ans;}
}tr1,tr2;
int main(){
	scanf("%d%d",&n,&q);
	if(n&1){
		while(q--)printf("NO\n");return 0;}
	scanf("%s",s+1);
	l.insert(n+1),r.insert(n+1);
	for(int i=1;i<=n;i++){
		t[i]=(s[i]=='(');
		le[i]=le[i-1]+t[i];
		ri[i]=ri[i-1]+(t[i]==0);
		qz[i]=ri[i]-le[i];}
	for(int i=n;i>=1;i--){
		le[i]=le[i+1]+t[i];
		ri[i]=ri[i+1]+(t[i]==0);
		hz[i]=le[i]-ri[i];}
	tr1.build(qz,1,1,n),tr2.build(hz,1,1,n);
	for(int i=2;i<=n;i++){
		if(t[i]&&t[i-1])sl[i-1]=1,l.insert(i-1);
		else if(!t[i]&&!t[i-1])sr[n-i+2]=1,r.insert(n-i+2);}
	while(q--){
		scanf("%d",&x);
		t[x]^=1;
		if(t[x])tr1.modify(1,1,n,x,n,-2),tr2.modify(1,1,n,1,x,2);
		else tr1.modify(1,1,n,x,n,2),tr2.modify(1,1,n,1,x,-2);
		if(x>1&&sl[x-1])l.erase(x-1),sl[x-1]=0;
		if(x>1&&sr[n-x+2])r.erase(n-x+2),sr[n-x+2]=0;
		if(sl[x])l.erase(x),sl[x]=0;
		if(sr[n-x+1])r.erase(n-x+1),sr[n-x+1]=0;
		if(t[x]&&t[x-1]&&x>1&&!sl[x-1])l.insert(x-1),sl[x-1]=1;
		if(t[x]&&t[x+1]&&x<n&&!sl[x])l.insert(x),sl[x]=1;
		if(!t[x]&&!t[x-1]&&x>1&&!sr[n-x+2])r.insert(n-x+2),sr[n-x+2]=1;
		if(!t[x]&&!t[x+1]&&x<n&&!sr[n-x+1])r.insert(n-x+1),sr[n-x+1]=1;
		int L=*l.begin(),R=n-(*r.begin())+1;
		if(L>1&&tr1.query(1,1,n,1,L-1)>0)printf("NO\n");
		else if(R<n&&tr2.query(1,1,n,R+1,n)>0)printf("NO\n");
		else printf("YES\n");}
	return 0;}
```


---

## 作者：Lyz09 (赞：2)

下文中 $sum_l$ 表示左括号数量之和，$sum_r$ 表示右括号数量之和。

一个行走所产生的括号序列是合法的，仅当

- $sum_l$ 等于 $sum_r$。

- 对于任意一个前缀，$sum_l \leq sum_r$。

对于一个原始的括号序列是合法的，仅当（此处仅给出大体判断条件）

- 当 $sum_l <sum_r$ 时，有连着的左括号且第一个连着的左括号之前的 $sum_l \geq sum_r$，注意有很多细节以及特判、边界。

- 当 $sum_r <sum_l$ 时，有连着的右括号且最后一个连着的右括号之后的 $sum_l \leq sum_r$。

- 当 $sum_l \equiv sum_r \pmod 2$ 时，判断方式和第一种类似，注意同样有很多细节以及特判、边界。

如何维护连着的括号的位置？

- 设 $f_i=(a_{i-1} = a_{i})$（括号内等号表示是否相等，括号外的为赋值）， 用 `set` 动态维护有哪些 $f_i=1$。其实 $f$ 装进 `set` 后就无需额外再用数组存储。

如何维护一段区间左/右括号的数量？

- 单点修改，区间查询。树状数组/线段树。

细节部分具体可以看代码。

```cpp
#include<iostream>
#include<set>
using namespace std;
#define N 200010
int n,q,w,a[N],f[N];
string s;
set<int> sl,sr;
class sgtree
{
	public:
		#define sN 800010
		int a[sN];
		void update(int o,int l,int r,int x,int k)
		{
			if(l>x||r<x)
			 return;
			if(l==r)
			{
				a[o]=k;
				return;
			}
			int mid=l+r>>1;
			update(o<<1,l,mid,x,k);
			update(o<<1|1,mid+1,r,x,k);
			a[o]=a[o<<1]+a[o<<1|1];
		}
		int query(int o,int l,int r,int x,int y)
		{
			if(l>y||r<x)
			 return 0;
			if(l>=x&&r<=y)
			{
				return a[o];
			}
			int mid=l+r>>1;
			int q1=query(o<<1,l,mid,x,y);
			int q2=query(o<<1|1,mid+1,r,x,y);
			return q1+q2; 
		}
}trl,trr;
int main()
{
	cin>>n>>q;
	cin>>s;
	for(int i=1;i<=n;i++)
	if(s[i-1]=='(')
	{
		a[i]=1;
		trl.update(1,1,n,i,1);
	}
	else
	{
		a[i]=2;
		trr.update(1,1,n,i,1);
	}
	for(int i=1;i<=n;i++)
	if(a[i]==a[i-1])
	{
		if(a[i]==1)
		 sl.insert(i);
		else
		 sr.insert(i);
	}
	for(int i=1;i<=q;i++)
	{
		cin>>w;
		sl.erase(w);
		sr.erase(w);
		sl.erase(w+1);
		sr.erase(w+1);
		if(a[w]==1)
		{
			trl.update(1,1,n,w,0);
			trr.update(1,1,n,w,1);
		}
		else
		{
			trr.update(1,1,n,w,0);
			trl.update(1,1,n,w,1);
		}
		if(a[w]==1)
		 a[w]=2;
		else
		 a[w]=1;
		if(a[w]==a[w-1])
		{
			if(a[w]==1)
			 sl.insert(w);
			else
			 sr.insert(w);
		}
		if(w<n)
		if(a[w]==a[w+1])
		{
			if(a[w]==1)
			 sl.insert(w+1);
			else
			 sr.insert(w+1);
		}
		if(trl.a[1]%2!=trr.a[1]%2||a[1]==2||a[n]==1)
		{
			puts("NO");
		}
		else
		{
			if(trl.a[1]<trr.a[1])
			{
				if(sl.empty())
				{
					puts("NO");
				}
				else
				{
					auto itr=sl.begin();
					int las=*itr;
					las-=2;
					int ql=trl.query(1,1,n,1,las);
					int qr=trr.query(1,1,n,1,las);
					if(ql<qr)
					{
						puts("NO");
					}
					else
					{
						if(sl.empty())
						{
							puts("YES"); 
						}
						else
						{
							auto itt=sl.end();
							itt--;
							int la=*itt;
							if(sr.empty())
							{
								puts("NO");
							}
							else
							{
								auto iit=sr.end();
								iit--;
								int laa=*iit;
								if(laa<la)
								 puts("NO");
								else
								 puts("YES");
							}
						}
					}
				}
			}
			else if(trl.a[1]==trr.a[1])
			{
				if(sl.empty())
				{
					if(a[1]==1&&sr.empty())
					 puts("YES");
					else
					 puts("NO");
				}
				else
				{
					auto itr=sl.begin();
					int las=*itr;
					las-=2;
					int ql=trl.query(1,1,n,1,las);
					int qr=trr.query(1,1,n,1,las);
					if(ql<qr)
					{
						puts("NO");
					}
					else
					{
						if(sl.empty())
						{
							puts("YES"); 
						}
						else
						{
							auto itt=sl.end();
							itt--;
							int la=*itt;
							if(sr.empty())
							{
								puts("NO");
							}
							else
							{
								auto iit=sr.end();
								iit--;
								int laa=*iit;
								if(laa<la)
								 puts("NO");
								else
								 puts("YES");
							}
						}
					}
				}
			}
			else
			{
				if(sr.empty())
				{
					puts("NO");
				}
				else
				{
					auto itr=sr.end();
					itr--;
					int las=*itr;
					las++;
					int ql=trl.query(1,1,n,las,n);
					int qr=trr.query(1,1,n,las,n);
					if(ql>qr)
					{
						puts("NO");
					}
					else
					{
						int fir=*sr.begin();
						if(sl.empty()||*sl.begin()>fir)
						{
							puts("NO");
						}
						else
						{
							puts("YES");
						}
					}
				}
			}
		}
	}
}
```



---

## 作者：zhlzt (赞：0)

### 题解

对于 $n\equiv 1\pmod 2$ 的情况显然无解。

考虑 $n\equiv 0\pmod 2$ 时括号序列是可行走的所需要满足的条件：

- 第一个括号为左括号，最后一个括号为右括号。

- 没有连续的相同括号，或者第一段连续的相同括号均为左括号且最后一段连续的相同括号均为右括号。

这是易得的，比如 `()()` 和 `()(()))())` 均是合法的。这里连续的相同括号可以反复行走来解决左右括号之间供不应求、供过于求的问题。

这里是括号序列合法的充要条件（辅助理解上文内容）：

- 括号序列中左右括号数量相等。

- 对于任意一个前缀，其中左括号数量大于等于右括号数量。

- 对于任意一个后缀，其中右括号数量大于等于左括号数量。

动态维护一个 `set` 用于保存所有满足 $s_i=s_{i+1}$ 的 $i$ 即可。

### 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
char str[maxn];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int n,q;cin>>n>>q>>str;
	set<int>same;
	for(int i=0;i<n-1;i++){
		if(str[i]==str[i+1]) same.insert(i);
	}
	if(n&1){
		while(q--) cout<<"NO\n";
		return 0;
	}
	for(int t=0;t<q;t++){
		int i;cin>>i; --i;
		str[i]=(str[i]=='('?')':'(');
		if(i>0){
			if(str[i]==str[i-1]) same.insert(i-1);
			else same.erase(same.find(i-1));
		}
		if(i<n-1){
			if(str[i]==str[i+1]) same.insert(i);
			else same.erase(same.find(i));
		}
		if(str[0]==')') cout<<"NO\n";
		else if(str[n-1]=='(') cout<<"NO\n";
		else if(same.empty()) cout<<"YES\n";
		else if(str[*same.begin()]==')') cout<<"NO\n";
		else if(str[*--same.end()]=='(') cout<<"NO\n";
		else cout<<"YES\n";
	}
	return 0;
}
```

---

## 作者：Little_Cabbage (赞：0)

> 涉及知识点：字符串，`set`。

# 解题思路

首先，如果序列的长度为奇数，是一定不能做到的，所以 $q$ 个询问直接输出 `NO`。

如果 $i$ 为奇数且 $s_i$ 为 $)$，则将 $i$ 插入数据结构中。

同理，如果 $i$ 为偶数且 $s_i$ 为 $($，则将 $i$ 也插入数据结构中。

对于每一次询问操作，令输入的数为 $idx$，如果 $idx$ 在数据结构里，就把 $idx$ 删除，否则把 $idx$ 插入数据结构。

然后判断如果数据结构的长度不等于 $0$ 且最小值为奇数或最大值为偶数，则输出 `NO`，否则输出 `YES`。

由于需要查询元素是否存在，最大值，最小值，插入以及删除，所以可以使用 `set` 来维护。

# 代码


```cpp
#include <bits/stdc++.h>
#define int long long
#define ll __int128
#define db double
#define ldb long double
#define vo void
#define endl '\n'
#define il inline
#define re register
#define ve vector
#define p_q priority_queue
#define PII pair<int, int>
#define u_m unordered_map
#define bt bitset

using namespace std;

//#define O2 1
#ifdef O2
	#pragma GCC optimize(1)
	#pragma GCC optimize(2)
	#pragma GCC optimize(3, "Ofast", "inline")
#endif

struct IO {
#define MAXSIZE (1 << 20)
#define isdigit(x) (x >= '0' && x <= '9')
	char buf[MAXSIZE], *p1, *p2;
	char pbuf[MAXSIZE], *pp;
	IO() : p1(buf), p2(buf), pp(pbuf) {}

	~IO() {
		fwrite(pbuf, 1, pp - pbuf, stdout);
	}
	char gc() {
		if (p1 == p2) p2 = (p1 = buf) + fread(buf, 1, MAXSIZE, stdin);
		return p1 == p2 ? ' ' : *p1++;
	}

	bool blank(char ch) {
		return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
	}

	template <class T>
	void read(T &x) {
		double tmp = 1;
		bool sign = 0;
		x = 0;
		char ch = gc();
		while (!isdigit(ch)) {
			if (ch == '-') sign = 1;
			ch = gc();
		}
		while (isdigit(ch)) {
			x = x * 10 + (ch - '0');
			ch = gc();
		}
		if (ch == '.') {
			ch = gc();
			while (isdigit(ch)) {
				tmp /= 10.0, x += tmp * (ch - '0');
				ch = gc();
			}
		}
		if (sign) x = -x;
	}

	void read(char *s) {
		char ch = gc();
		for (; blank(ch); ch = gc());
		for (; !blank(ch); ch = gc()) * s++ = ch;
		*s = 0;
	}

	void read(char &c) {
		for (c = gc(); blank(c); c = gc());
	}

	void push(const char &c) {
		if (pp - pbuf == MAXSIZE) fwrite(pbuf, 1, MAXSIZE, stdout), pp = pbuf;
		*pp++ = c;
	}

	template <class T>
	void write(T x) {
		if (x < 0) x = -x, push('-');
		static T sta[35];
		T top = 0;
		do {
			sta[top++] = x % 10, x /= 10;
		} while (x);
		while (top) push(sta[--top] + '0');
	}

	template <class T>
	void write(T x, char lastChar) {
		write(x), push(lastChar);
	}
} io;

namespace Template {
	int fact[200000];
	int Triangle[1010][1010];
	int Prime[2000000], Prime_vis[2000000];
	int Prime_len;
	void Fact(int n, int mod) {
		fact[0] = 1;
		for (int i = 1; i <= n; i ++ ) fact[i] = ((fact[i - 1]) % mod * (i % mod)) % mod;
	}
	void Pascal_s_triangle(int n, int mod) {
		for (int i = 0; i <= n; i ++ ) Triangle[i][0] = 1;
		for (int i = 1; i <= n; i ++ )
			for (int j = 1; j <= i; j ++ )
				Triangle[i][j] = (Triangle[i - 1][j] + Triangle[i - 1][j - 1]) % mod;
	}
	void Get_prime(int n) {
		for (int i = 2; i <= n; i ++ ) {
			if (!Prime_vis[i]) Prime[++Prime_len] = i;
			for (int j = 1; Prime[j] * i <= n; j ++ ) {
				Prime_vis[Prime[j] * i] = 1;
				if (i % Prime[j] == 0) break;
			}
		}
	}
	int pw(int x, int y, int mod) {
		int res = 1;
		while (y) {
			if (y & 1) res = ((res % mod) * (x % mod)) % mod;
			x = (x % mod) * (x % mod) % mod;
			y >>= 1;
		}
		return res;
	}
	int pw(int x, int y) {
		int res = 1;
		while (y) {
			if (y & 1) res *= x;
			x *= x;
			y >>= 1;
		}
		return res;
	}
	int GCD(int x, int y, int mod) {
		return __gcd(x, y) % mod;
	}
	int LCM(int x, int y, int mod) {
		return (((x % mod) * (y % mod)) % mod / (GCD(x, y, mod) % mod)) % mod;
	}
	int C(int n, int m, int mod) {
		if (m > n || m < 0) return 0;
		return fact[n] * pw(fact[m], mod - 2, mod) % mod * pw(fact[n - m], mod - 2, mod) % mod;
	}
	int Ask_triangle(int x, int y) {
		return Triangle[x][y];
	}
}
using namespace Template;

//#define fre 1
#define IOS 1
//#define multitest 1

const int N = 4e6 + 10;
const int M = 4e5 + 10;
const int inf = 1e12;
const int Mod = 1e9 + 9;

namespace zla {
	int n, q;
	string str;
	set<int> s;

	il void Init() {
		cin >> n >> q;
		cin >> str;
	}

	il void Solve() {
		if (n % 2) {
			while (q -- ) cout << "NO\n";
			return ;
		}
		str = " " + str;
		for (int i = 1; i <= n; i ++ ) {
			if (i % 2 && str[i] == ')') s.insert(i);
			else if ((!(i % 2)) && str[i] == '(') s.insert(i);
		}
		while (q -- ) {
			int idx;
			cin >> idx;
			if (s.count(idx)) s.erase(idx);
			else s.insert(idx);
			if (!s.empty() && ((*s.begin() % 2) || (!(*s.rbegin() % 2)))) cout << "NO\n";
			else cout << "YES\n";
		}
	}

	il void main() {
		Init();
		Solve();
	}
}

signed main() {
	int T;
#ifdef IOS
	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
#endif
#ifdef fre
	freopen(".in", "r", stdin);
	freopen(".out", "w", stdout);
#endif
#ifdef multitest
	cin >> T;
#else
	T = 1;
#endif
	while (T--) zla::main();
	return 0;
}
```

---

## 作者：Zimo_666 (赞：0)

# Bracket Walk

题看了好久才看懂，题解区都是一些 `DS` 做法，这里给出官方题解做法。

想看英文可以去：[Link](https://codeforces.com/blog/entry/116995)。

## Statement

给你一个长度为 $n$ 的括号序列，你可以在上面走，起点是第一个括号，终点是最后一个括号，在此期间，你可以随意的往左右走，当你处在第一个括号的时候，你仅能往右走，当你处在最后一个括号的时候，你可以选择不走了，也可以选择继续往左走。需要注意的是，经过任何一个位置的次数和总的步数都是**不被限制的**。每次走过一个括号都会记录下你来你当前所在的括号，这些括号组成一个括号序列。

题目中给出你 $q$ 次询问，询问都是**互相影响的**，这也就意味着，前面的修改对后面的询问依然有效。询问每次给出一个 $i$，意思是改变位置为 $i$ 的括号方向，这以后请你给出能否在这个括号上走出一个合法括号序列，如果可以走出，请输出 `YES`，否则请输出 `NO`。

## Solution

我们考虑维护一个这样的 `set`。

如果当前 $i$ 是奇数并且 $s_i= \ )$，或者当前 $i$ 是偶数并且 $s_i=\ ($，那么我们就把它丢进 `set` 中。

对于每个询问如果 $i$ 在 `set` 中就擦掉，否则丢进去。

- 如果 $n$ 是奇数，那么无论如何都没办法构成合法的括号序列。

- 如果当前 `set` 的 `size` 是 0，也就意味着括号序列形如 `()()()()()`，那么肯定合法。
- 如果当前 `set` 的 `size` 大于 0，那么分下面三种情况。
  - $\min  $ 是奇数，也就意味着括号序列形如 $()()())$，这种情况下我们是没办法走出合法的括号序列的，换句话说不管怎么走，我们没办法弥补掉最后一个右括号带来的影响。
  - $\max$ 是偶数，也就意味着括号序列形如 $(()()()$，同上，没办法弥补左括号带来的影响。
  - 剩下的情况都是合法的，形如 $()()(((...)))()()$，也就意味着，我可以用左括号弥补掉右括号的影响，用右括号弥补掉左括号的影响。也就意味着，时时刻刻我们可以计算好，然后通过多走点右括号或者多走点左括号圆满走到 $()()$ 这样的地方最后结束。

代码还是比较好实现的，主要是真的不好想。

[Code](https://codeforces.com/contest/1838/submission/230306945)

---

## 作者：wth2026 (赞：0)

# 题目思路
使用数据结构维护，本人建议使用 set。

如果 $x$ 是奇数且 $s_x=)$，就将 $x$ 插入数据结构。

同理，如果 $x$ 是偶数且 $s_x=($，就将 $x$ 插入数据结构。

每一次求的时候，对于修改，如果当前询问的数 $Qry$ 在数据结构里，就将其移除，否则插入。

随后判断数据结构的元素个数、最小值与最大值，看是否满足元素个数为 $0$，或最大值为奇数且最小值为偶数，如果是，说明可行。否则不可行。

# AC Code
```cpp
#include <set>
#include <cstring>
#include <iostream>
#include <algorithm>

#define endl '\n'
#define int long long
#define inf 0x3f3f3f3f
#define lnf 0x3f3f3f3f3f3f3f3f

const bool Debug = false;

//#define Debug true

using namespace std;

const int N = 2e5;

void init ();

int n, m;
string s;
set <int> _St;
int x;

signed main () {
	init ();
	cin >> n >> m;
	cin >> s;
	s = " " + s;
	
	if (Debug) {
		cout << s << endl;
	}
	
	for (register int i = 1; i <= n; ++ i) {
		if (i % 2) {
			if (s[i] == ')') {
				_St.insert (i);
			}
		} else {
			if (s[i] == '(') {
				_St.insert (i);
			}
		}
	}
	
	if (Debug) {
		for (auto it : _St) {
			cout << it << ' ';
		}
		
		cout << endl;
	}
	
	while (m --) {
		cin >> x;
		
		if (_St.count (x)) {
			_St.erase (x);
		} else {
			_St.insert (x);
		}
		
		if (n % 2) {
			cout << "No" << endl;
		} else {
			if (_St.size () && ((*_St.begin () % 2) || (!(*_St.rbegin () % 2)))) {
				cout << "No" << endl;
			} else {
				cout << "Yes" << endl;
			}
		}
	}
	
	return 0;
}

void init () {
	ios::sync_with_stdio (Debug);
	cin.tie (0);
	cout.tie (0);
}
```

---

## 作者：lutaoquan2012 (赞：0)

## 思路：
显然如果长度是奇数那么这个括号序列一定不会匹配成功。

我们不难发现，如果想让这个括号序列中的那些无法匹配的括号通过走动而匹配成功，那么这些无法匹配的括号左右两边一定有 ```((``` 和 ```))```，也就是如果有一个序列 ```((.......))``` 那么一定可以匹配成功，不管中间是什么括号。

这样我们就只要用三个 set 分别去记录 ```((,)),()```，最后判断可不可以匹配。

判断不可以匹配的几个点：

- 单独有 ```((``` 却没有 ```))``` 或者单独有 ```))``` 却没有 ```((``` 无法匹配。
- 只有  ```)(``` 却没有 ```((``` 和 ```))``` 去重复左右括号那么无法匹配，比如说：```()())(()()```。
- 有任意一个 ```((``` 在任意一个 ```))``` 的右边那么无法匹配。
- 不符合：要有 ```((``` 必须在所有的 ```)(``` 左边，要有 ```))``` 必须在所有的 ```)(``` 右边，也就任何一个 ```)(``` 都必须被 ```((``` 和 ```))``` 包含，那么无法匹配。

## 代码：
```cpp
//
// Created by 55062 on 2024/7/12.
//
#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
ll n, q, x;
string s;
set<ll> st[4];

int main() {
    cin >> n >> q >> s;
    for (int i = 0; i < n; i += 2) {
        if (s[i] == '(' && s[i + 1] == '(') st[1].insert(i);//两个连续的左括号
        if (s[i] == ')' && s[i + 1] == ')') st[2].insert(i);//两个联系的右括号
        if (s[i] == ')' && s[i + 1] == '(') st[3].insert(i);//需要用两边连续的两个左括号和连续的两个右括号让序列是“可行走的”
    }
    while (q--) {
        cin >> x;
        x--;
        if (n % 2 != 0) {//长度为奇数显然无法是“可行走的”
            cout << "NO\n";
            continue;
        }
        ll i = x - (x % 2 != 0);//对括号序列经行修改
        for (int j = 1; j <= 3; j++) st[j].erase(i);
        if (s[x] == '(') s[x] = ')';
        else s[x] = '(';
        if (s[i] == '(' && s[i + 1] == '(') st[1].insert(i);
        if (s[i] == ')' && s[i + 1] == ')') st[2].insert(i);
        if (s[i] == ')' && s[i + 1] == '(') st[3].insert(i);
        bool flag = false;
        if (st[1].empty() != st[2].empty()) flag = true;//如果单独有 (( 却没有 )) 或者单独有 )) 却没有 (( 都无法匹配
        else if (st[1].empty() && st[2].empty() && !st[3].empty())
            flag = true;//如果只有匹配不了的 )( 却没有 (( 和 )) 去重复左右括号那么无法匹配，比如说：( ) ( ) ) ( ( ) ( )
        else if (!st[1].empty() && !st[2].empty()) {//有 ((、))、)(
            if (*st[2].begin() < *st[1].begin() || *st[1].rbegin() > *st[2].rbegin())
                flag = true;//所有的 (( 必须在 所有的 )) 左边，否则无法匹配
            else if (!st[3].empty() && (*st[3].begin() < *st[1].begin() || *st[3].rbegin() > *st[2].rbegin()))
                flag = true;//要有 (( 必须在所有的 )( 左边，要有 )) 必须在所有的 )( 右边，也就任何一个 )( 都必须被 (( 和 )) 包含
        }
        if (flag == false) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}
```

---

## 作者：Anamnesis (赞：0)

一种思维难度较低的线段树上二分做法。

首先有几个观察：

- 左右括号的数量差为奇数时，一定无解。这是因为我们可能可以通过反复走来弥补数量差，但每次一定会增加偶数个某种括号。
- 类似地，$n$ 为奇数时，一定无解。
- 某处的前缀左括号数小于右括号数，此处需要补充左括号；后缀右括号数小于左括号数，此处需要补充右括号。
- 如果需要补充右括号，左括号只要补充在它左边即可，具体位置没有要求。反之亦然。


由此可知，有解需满足：
- 下标最小的连续左括号位置 $i$、下标最小的前缀左括号数小于右括号数的位置 $x$ 满足 $i<x$。
- 下标最大的连续右括号位置 $j$，下标最大的后缀右括号数小于左括号数的位置 $y$ 满足 $j>y$。

考虑怎么维护 $x$。

构造一个序列，左括号为 $-1$，右括号为 $1$，对其求前缀和，满足 $pref_x>0$ 的最小的 $x$ 即为所求。  
翻转括号的修改操作就是对前缀和做区间加。  
前缀和不满足单调性，但可以用线段树维护区间最大值。这样在线段树上二分就可以找到 $x$ 了。

$y$ 同理，使用后缀和并维护区间最小值即可。

然后考虑怎么维护 $i$、$j$。发现这个也可以线段树上二分。构造序列，将每个连续括号的位置设为 $1$，其余为 $0$，再求前缀和 / 后缀和即可。每次修改还是在区间加。这个是单调的，因此可以直接在一棵区间求和线段树上二分（需要 `long long`），当然仍然维护区间最大值也可以。

除此之外，$i$、$j$ 也可以用 `std::set` 简单维护。

修改操作的细节可以参考代码，应该还是比较可读的（

---

主函数：
```cpp
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  string s;
  cin >> s;
  if (n % 2 == 1) {
    while (q--) {
      int meow;
      cin >> meow;
      cout << "NO\n";
    }
    return 0;
  }

  vector<int> pre(n), suf(n), lb(n), rb(n);
  for (int i = 0; i < n; ++i) {
    if (s[i] == ')') {
      pre[i] = 1;
    } else {
      pre[i] = -1;
    }
    if (i) {
      pre[i] += pre[i - 1];
      lb[i] += lb[i - 1];
      if (s[i] == '(' && s[i - 1] == '(') {
        ++lb[i];
      }
    }
  }
  for (int i = n - 1; i >= 0; --i) {
     if (s[i] == ')') {
      suf[i] = 1;
    } else {
      suf[i] = -1;
    }
    if (i < n - 1) {
      suf[i] += suf[i + 1];
      rb[i] += rb[i + 1];
      if (s[i] == ')' && s[i + 1] == ')') {
        ++rb[i];
      }
    }
  }
  Segmax<int> t(pre);
  Segmin<int> p(suf);
  Segmax<int> l(lb), r(rb);
  while (q--) {
    int x;
    cin >> x;
    --x;

    if (s[x] == '(') {
      s[x] = ')';
      t.upd(x, n - 1, {2});
      p.upd(0, x, {2});
      if (x < n - 1) {
        if (s[x + 1] == '(') {
          l.upd(x + 1, n - 1, {-1});
        } else {
          r.upd(0, x, {1});
        }
      }
      if (x > 0) {
        if (s[x - 1] == '(') {
          l.upd(x, n - 1, {-1});
        } else {
          r.upd(0, x - 1, {1});
        }
      }
    } else {
      s[x] = '(';
      t.upd(x, n - 1, {-2});
      p.upd(0, x, {-2});
      if (x < n - 1) {
        if (s[x + 1] == ')') {
          r.upd(0, x, {-1});
        } else {
          l.upd(x + 1, n - 1, {1});
        }
      }
      if (x > 0) {
        if (s[x - 1] == ')') {
          r.upd(0, x - 1, {-1});
        } else {
          l.upd(x, n - 1, {1});
        }
      }
    }

    int dt = t.get(n - 1).v;
    if (dt % 2 == 1) {
      cout << "NO\n";
      continue;
    }

    int first_need_left = t.find_first(0, n - 1, [](const Segmax<int>::Node &v) { return v.v > 0; });
    int first_give_left = l.find_first(0, n - 1, [](const Segmax<int>::Node &v) { return v.v > 0; });
    int last_need_right = p.find_last(0, n - 1, [](const Segmin<int>::Node &v) { return v.v < 0; });
    int last_give_right = r.find_last(0, n - 1, [](const Segmax<int>::Node &v) { return v.v > 0; });

    if ((first_need_left == -1 || (first_need_left > first_give_left && first_give_left != -1)) && (last_need_right == -1 || (last_need_right < last_give_right && last_give_right != -1))) {
      cout << "YES\n";
    } else {
      cout << "NO\n";
    }
  }
  return 0;
}
```

使用的线段树模板：
```cpp
template<typename T>
class Segmax {
 public:
  struct Node {
    T v = 0, add = 0;
    Node operator+(const Node &rhs) {
      Node res{};
      res.v = max(v, rhs.v);
      return res;
    }
    void apply(int _l, int _r, const Node &todo) {
      v += todo.v;
      add += todo.v;
    }
  };
  vector<Node> t;
  vector<T> src;
  int n;

  Segmax(const vector<T> &arr) : src(arr) {
    n = src.size();
    assert(n > 0);
    t.resize(n << 2);
    build(0, 0, n - 1);
  }

  inline void push(int o, int l, int r) {
    if (!t[o].add) return;
    int p = (l + r) >> 1;
    int q = o + ((p - l + 1) << 1);
    t[o + 1].apply(l, p, {t[o].add});
    t[q].apply(p + 1, r, {t[o].add});
    t[o].add = 0;
  }
  void upd(int o, int l, int r, int ll, int rr, const Node &v) {
    if (ll <= l && r <= rr) {
      t[o].apply(l, r, v);
      return;
    }
    push(o, l, r);
    int p = (l + r) >> 1;
    int q = o + ((p - l + 1) << 1);
    if (ll <= p) 
      upd(o + 1, l, p, ll, rr, v);
    if (rr > p) 
      upd(q, p + 1, r, ll, rr, v);
    t[o] = t[o + 1] + t[q];
  }
  Node get(int o, int l, int r, int ll, int rr) {
    if (ll <= l && r <= rr)
      return t[o];
    push(o, l, r);
    int p = (l + r) >> 1;
    int q = o + ((p - l + 1) << 1);
    Node res{};
    if (rr <= p)
      res = get(o + 1, l, p, ll, rr);
    else if (ll > p)
      res = get(q, p + 1, r, ll, rr);
    else
      res = get(o + 1, l, p, ll, rr) + get(q, p + 1, r, ll, rr);
    return res;
  }
  int find_first_knowingly(int o, int l, int r, const function<bool(const Node&)> &f) {
    if (l == r)
      return l;
    push(o, l, r);
    int p = (l + r) >> 1;
    int q = o + ((p - l + 1) << 1);
    int res;
    if (f(t[o + 1]))
      res = find_first_knowingly(o + 1, l, p, f);
    else
      res = find_first_knowingly(q, p + 1, r, f);
    t[o] = t[o + 1] + t[q];
    return res;
  }
 
  int find_first(int o, int l, int r, int ll, int rr, const function<bool(const Node&)> &f) {
    if (ll <= l && r <= rr) {
      if (!f(t[o]))
        return -1;
      return find_first_knowingly(o, l, r, f);
    }
    push(o, l, r);
    int p = (l + r) >> 1;
    int q = o + ((p - l + 1) << 1);
    int res = -1;
    if (ll <= p)
      res = find_first(o + 1, l, p, ll, rr, f);
    if (rr > p && res == -1)
      res = find_first(q, p + 1, r, ll, rr, f);
    t[o] = t[o + 1] + t[q];
    return res;
  }
 
  int find_last_knowingly(int o, int l, int r, const function<bool(const Node&)> &f) {
    if (l == r)
      return l;
    push(o, l, r);
    int p = (l + r) >> 1;
    int q = o + ((p - l + 1) << 1);
    int res;
    if (f(t[q]))
      res = find_last_knowingly(q, p + 1, r, f);
    else
      res = find_last_knowingly(o + 1, l, p, f);
    t[o] = t[o + 1] + t[q];
    return res;
  }
 
  int find_last(int o, int l, int r, int ll, int rr, const function<bool(const Node&)> &f) {
    if (ll <= l && r <= rr) {
      if (!f(t[o]))
        return -1;
      return find_last_knowingly(o, l, r, f);
    }
    push(o, l, r);
    int p = (l + r) >> 1;
    int q = o + ((p - l + 1) << 1);
    int res = -1;
    if (rr > p)
      res = find_last(q, p + 1, r, ll, rr, f);
    if (ll <= p && res == -1)
      res = find_last(o + 1, l, p, ll, rr, f);
    t[o] = t[o + 1] + t[q];
    return res;
  }
  void upd(int x, const Node &v) {
    assert(0 <= x && x <= n - 1);
    upd(0, 0, n - 1, x, x, v);
  }
  void upd(int ll, int rr, const Node &v) {
    assert(0 <= ll && ll <= rr && rr <= n - 1);
    upd(0, 0, n - 1, ll, rr, v);
  }
  Node get(int ll, int rr) {
    assert(0 <= ll && ll <= rr && rr <= n - 1);
    return get(0, 0, n - 1, ll, rr);
  }
  Node get(int x) {
    assert(0 <= x && x <= n - 1);
    return get(0, 0, n - 1, x, x);
  }
  int find_first(int ll, int rr, const function<bool(const Node &)> &f) {
    assert(0 <= ll && ll <= rr && rr <= n - 1);
    return find_first(0, 0, n - 1, ll, rr, f);
  }
  int find_last(int ll, int rr, const function<bool(const Node &)> &f) {
    assert(0 <= ll && ll <= rr && rr <= n - 1);
    return find_last(0, 0, n - 1, ll, rr, f);
  }

 private:
  void build(int o, int l, int r) {
    if (l == r) {
      t[o].apply(l, r, {src[l]});
      return;
    }
    int p = (l + r) >> 1;
    int q = o + ((p - l + 1) << 1);
    build(o + 1, l, p);
    build(q, p + 1, r);
    t[o] = t[o + 1] + t[q];  // pull
  }
};
```

---

