# Prime Divisors Selection

## 题目描述

Suppose you have a sequence of $ k $ integers $ A = [a_1, a_2, \dots , a_k] $ where each $ a_i \geq 2 $ . A sequence of prime integers $ P = [p_1, p_2, \dots, p_k] $ is called suitable for the sequence $ A $ if $ a_1 $ is divisible by $ p_1 $ , $ a_2 $ is divisible by $ p_2 $ and so on.

A sequence of prime integers $ P $ is called friendly if there are no unique integers in this sequence.

A sequence $ A $ is called ideal, if each sequence $ P $ that is suitable for $ A $ is friendly as well (i. e. there is no sequence $ P $ that is suitable for $ A $ , but not friendly). For example, the sequence $ [2, 4, 16] $ is ideal, while the sequence $ [2, 4, 6] $ is not ideal (there exists a sequence $ P = [2, 2, 3] $ which is suitable for $ A $ , but not friendly).

You are given $ n $ different integers $ x_1 $ , $ x_2 $ , ..., $ x_n $ . You have to choose exactly $ k $ of them in such a way that they form an ideal sequence, or report that it is impossible. Note that no integer can be chosen more than once.

## 样例 #1

### 输入

```
3 3
2 4 6```

### 输出

```
0```

## 样例 #2

### 输入

```
3 3
2 4 16```

### 输出

```
2 4 16```

## 样例 #3

### 输入

```
4 3
2 4 6 16```

### 输出

```
2 4 16```

# 题解

## 作者：Union_of_Britain (赞：2)

史中史题目。

考虑一个序列合法的条件？容易发现 $\forall p\in \mathcal P,\exists i,p\mid a_i\Rightarrow \exists j\neq k,a_j=p^a,a_k=p^b$ 是充要的。

然后拿出每个 $p^a$ 的数，这样的数给 `map` 中 $p$ 位置 $+1$。最后得到 `map` 里值为 $2$ 的有 $c_1$ 个，$>2$ 的有 $c_2$ 个，不为 $1$ 的数和为 $S$。

定义可表示的数为质因子数量 $>1$ 且这些质因子在 `map` 的值都 $\ge2$ 的数，合法的数为质数且 `map` 的值 $>1$。一个合法质数 $p$ 的位置是那些 $a_i=p^k$ 的位置。尽量做一个操作是直到答案被填满。

分类讨论：

- $c_2=0,2\nmid k,k\le S$。找出最小的可表示的数的质因子个数 $a$。若 $2a+1>k$，无解；否则先取这些质因子和这个数，再随便找一些合法质数塞进答案。

- $c_2=0,2\mid k,k\le S$。选若干合法质数即可。

- $c_2=0.k>S$。把所有合法质数选上然后尽量选可表示数。

- $c2\neq 0,k\le S,2\mid k$。先把尽量把每个合法质数从大到小选偶数个位置（即是奇数就留最后一个位置不选），再从大到小把那些有奇数个位置的合法质数尽量选最后一个位置。

- $c_2\neq 0,k\le S,2\nmid k$。若 $k=S$，选择所有合法质数；否则把 `map` 值最大的合法质数 $p$ 的出现位置砍成奇数（如果是偶数就取出一个位置）。先尽量选 $p$ 的位置，这个时候 $k$ 被砍成偶数；再套用上一个的做法。

- $c_2\neq 0,k>S$。先把每个合法质数选上再尽量选可表示数。

需要 Pollard-rho 来快速分解（可以避开）。因为是贺的 pollard-rho，代码中就略去这部分了（见 `fac` 函数）（

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int INF=1e9;
set<int> st;
inline void fac(ll x){for(all the factor of x)st.insert(x);}
map<int,int> mp,rev,MP;
const int maxn=1e3+5;
int a[maxn],n,k,R[maxn];
set<int> c[maxn],cur;
bool cmp(int a,int b){return rev[a]<rev[b];}
bool cmp2(vector<int> A,vector<int> B){return A.size()>B.size();}
vector<int> e[maxn];
signed main()
{
	cin>>n>>k;
	if(k==1){cout<<0<<endl;return 0;}
	for(int i=1;i<=n;i++)
		cin>>a[i],rev[a[i]]=i;
	for(int i=1;i<=n;i++){
		st.clear();
		fac(a[i]);c[i]=st;
		if(st.size()==1)mp[*st.begin()]++;
	}
	int c2=0,c3=0,S=0,t=0;
	for(auto [a,b]:mp){
		if(b==2)c2++;
		else if(b>2)c3++;
		if(b>=2)S+=b,cur.insert(a);
		t+=b;
	}
	t=n-t;
	if(c3==0){
		if((k&1)&&k<=S){
			int mn=INF,pos;
			for(int i=1;i<=n;i++){
				if(c[i].size()>1){
					bool flg=1;
					for(auto u:c[i])if(!cur.count(u)){flg=0;break;}
					if(flg){
						mn=min(mn,(int)c[i].size()*2+1);
						pos=i;
					}
				}
			}
			if(mn<=k){
				set<int> res;vector<int> ans;ans.push_back(a[pos]);
				for(auto u:c[pos])res.insert(u);
				int ct=mn;
				for(int i=1;i<=n;i++){
					if(ct>=k)break;
					if(c[i].size()==1){
						if(res.count(*c[i].begin()))continue;
						else res.insert(*c[i].begin()),ct+=2;
					}
				}
				for(int i=1;i<=n;i++){
					if(c[i].size()==1){
						if(res.count(*c[i].begin()))ans.push_back(a[i]);
					}
				}
				sort(ans.begin(),ans.end(),cmp);
				for(auto u:ans)cout<<u<<" ";cout<<endl;
			}else{
				cout<<0<<endl;
			}
		}else if(k<=S){
			set<int> res;vector<int> ans;
			int ct=0;
			for(int i=1;i<=n;i++){
				if(ct>=k)break;
				if(c[i].size()==1){
					if(mp[*c[i].begin()]==1)continue;
					if(res.count(*c[i].begin()))continue;
					else res.insert(*c[i].begin()),ct+=2;
				}
			}
			for(int i=1;i<=n;i++){
				if(c[i].size()==1){
					if(res.count(*c[i].begin()))ans.push_back(a[i]);
				}
			}
			sort(ans.begin(),ans.end(),cmp);
			for(auto u:ans)cout<<u<<" ";cout<<endl;
		}else{
			set<int> res;vector<int> ans;
			int ct=0;
			for(int i=1;i<=n;i++){
				if(c[i].size()==1){
					if(mp[*c[i].begin()]==1)continue;
					res.insert(*c[i].begin()),ct++;
					ans.push_back(a[i]);
				}
			}
			for(int i=1;i<=n;i++){
				if(ct>=k)break;
				if(c[i].size()>1){
					bool flg=1;
					for(auto u:c[i])if(!res.count(u)){flg=0;break;}
					if(flg)ans.push_back(a[i]),++ct;
				}
			}
			if(ct<k)cout<<0<<endl;
			else{
				sort(ans.begin(),ans.end(),cmp);
				for(auto u:ans)cout<<u<<" ";cout<<endl;
			}
		}
	}else{
		int tot=0;
		for(int i=1;i<=n;i++){
			if(c[i].size()==1){
				int x=*c[i].begin();
				if(mp[x]==1)continue;
				if(!MP[x])MP[x]=++tot,R[tot]=x;
				e[MP[x]].push_back(i);
			}
		}
		if(S>=k){
			sort(e+1,e+tot+1,cmp2);
			vector<int> ans;int ct=0;
			if(k&1){
				if(k==S){
					for(int i=1;i<=tot;i++){
						for(auto u:e[i])ans.push_back(a[u]);
					}
				}else{
					if(e[1].size()%2==0)e[1].pop_back();
					for(int i=1;i<=min((int)e[1].size(),k);i++)ans.push_back(a[e[1][i-1]]);
					k-=min((int)e[1].size(),k);
					for(int i=2;i<=tot;i++){
						for(int j=0;j<e[i].size();j+=2){
							if(ct>=k)break;
							ans.push_back(a[e[i][j]]);
							ans.push_back(a[e[i][j+1]]);
							ct+=2;
						}
					}
					for(int i=2;i<=tot;i++){
						if(ct>=k)break;
						if(e[i].size()&1)ct++,ans.push_back(a[e[i][e[i].size()-1]]);
					}
				}
			}else{
				for(int i=1;i<=tot;i++){
					for(int j=0;j+1<e[i].size();j+=2){
						if(ct>=k)break;
						ans.push_back(a[e[i][j]]);
						ans.push_back(a[e[i][j+1]]);
						ct+=2;
					}
				}
				for(int i=1;i<=tot;i++){
					if(ct>=k)break;
					if(e[i].size()&1)ct++,ans.push_back(a[e[i][e[i].size()-1]]);
				}
			}
			sort(ans.begin(),ans.end(),cmp);
			for(auto u:ans)cout<<u<<" ";cout<<endl;
		}else{
			vector<int> ans;int ct=0;
			for(int i=1;i<=tot;i++){
				for(auto u:e[i])ans.push_back(a[u]),++ct;
			}
			for(int i=1;i<=n;i++){
				if(ct>=k)break;
				if(c[i].size()>1){
					bool flg=1;
					for(auto u:c[i])if(!cur.count(u)){flg=0;break;}
					if(flg)ans.push_back(a[i]),++ct;
				}
			}
			if(ct<k)cout<<0<<endl;
			else{
				sort(ans.begin(),ans.end(),cmp);
				for(auto u:ans)cout<<u<<" ";cout<<endl;
			}
		}
	}
    return 0;
}
```

---

## 作者：tzc_wk (赞：2)

> 摘自我的 [杂题选做Ⅴ](https://www.cnblogs.com/ET2006/p/greedy-construction-dp5.html) 中的第 $105$ 题。

我们先考虑将每个数写成 $p^a$ 的形式，我们定义一个质因子 $p$ 的“出现次数”为，满足 $a_i=p^x$ 的 $i$ 的个数（$x\in\mathbb{Z}$）。显然如果一个质因子出现次数 $\le 1$，那么包含这些质因子的数都不能被选择，我们就干脆把这些质因子全部踢出去，这样我们剩下的就只有那些由出现次数 $\ge 2$ 的质因子构成的数。

显然如果 $k=1$ 或者 $k$ 超过了剩余的数的个数那肯定无解了，直接输出 $0$。但是如果 $k$ 在 $2$ 与剩余的数的个数之间那也有可能出现无解的情况，特例：$a=[4,8,9,27],k=3$，因此考虑进一步分情况讨论：

- 记 $cnt$ 表示出现次数 $\ge 2$ 的质因子个数，如果 $k\ge 2cnt$ 那好办，直接在这 $cnt$ 个质因子中先随便选 $2$ 个数，然后再随便选 $k-2cnt$ 个数即可。
- 否则如果 $k$​ 是偶数那也好办，随机选 $\dfrac{k}{2}$ 个质因子，然后这些质因子中随便选 $2$ 个对应的数即可。
- 否则继续分情况讨论，如果存在一个质因子 $p$​ 出现次数 $\ge 3$​ 那么我们就选 $3$​ 个满足可以写成 $p^x$​ 的数，然后再随机选另外 $\dfrac{k-3}{2}$​ 个质因子，对于选中的质因子 $p’$，随便选两个数形如 $(p’)^x$ 的数即可。
- 否则说明所有质因子的出现次数都等于 $2$，那么我们考虑所有不可以写成 $p^x$ 且没有被我们踢掉的数，我们记这些数中质因子个数的最小值为 $M$，那么如果 $k<2M-1$ 就无解了。否则我们j，再选假设没有被踢掉的数中质因子个数最小的数为 $v$，$v$ 的 $M$ 个质因子为 $p_1,p_2,\cdots,p_M$，那么我们对于 $i\in[1,M]$，选出两个形如 $p_i^x$ 的数，然后选上 $v$ 这个数，然后再随便选 $\dfrac{k-2M-1}{2}$ 个剩余的质因子 $p$，每个质因子选两个形如 $p^x$ 的数即可。

注意到每个数互不相同，所以只有 $<10^9$ 的质数是有用的，其他质数的出现次数至多为 $1$。而如果我们考虑对 $1\sim 10^6$ 里的质数暴力分解，这样我们可以对所有 $\le 10^6$ 的质数 $p$，找出序列中所有可以表示成 $p^x$ 的数。而如果 $a_i\le 10^9$，并且 $a_i$ 没有 $\le 10^6$​ 的质因子，那么就说明 $a_i$ 是质数，我们只需检验 $a_i^2$ 是否是一个质数，如果是则说明 $a_i$ 的出现次数为二，否则我们直接踢掉这个质数即可。

时间复杂度 $n\pi(10^6)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fill0(a) memset(a, 0, sizeof(a))
#define fill1(a) memset(a, -1, sizeof(a))
#define fillbig(a) memset(a, 63, sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
#define mt make_tuple
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
template <typename T1, typename T2> void chkmin(T1 &x, T2 y){
	if (x > y) x = y;
}
template <typename T1, typename T2> void chkmax(T1 &x, T2 y){
	if (x < y) x = y;
}
typedef pair<int, int> pii;
typedef long long ll;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef long double ld;
namespace fastio {
	#define FILE_SIZE 1 << 23
	char rbuf[FILE_SIZE], *p1 = rbuf, *p2 = rbuf, wbuf[FILE_SIZE], *p3 = wbuf;
	inline char getc() {
		return p1 == p2 && (p2 = (p1 = rbuf) + fread(rbuf, 1, FILE_SIZE, stdin), p1 == p2) ? -1: *p1++;
	}
	inline void putc(char x) {(*p3++ = x);}
	template <typename T> void read(T &x) {
		x = 0; char c = getc(); T neg = 0;
		while (!isdigit(c)) neg |= !(c ^ '-'), c = getc();
		while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = getc();
		if (neg) x = (~x) + 1;
	}
	template <typename T> void recursive_print(T x) {
		if (!x) return;
		recursive_print (x / 10);
		putc (x % 10 ^ 48);
	}
	template <typename T> void print(T x) {
		if (!x) putc('0');
		if (x<0) putc('-'), x = -x;
		recursive_print(x);
	}
	template <typename T> void print(T x,char c) {print(x); putc(c);}
	void readstr(char *s) {
		char c = getc();
		while (c <= 32 || c >= 127) c = getc();
		while (c > 32 && c < 127) s[0] = c, s++, c = getc();
		(*s) = 0;
	}
	void printstr(string s) {
		for (int i = 0; i < s.size(); i++) putc(s[i]);
	}
	void printstr(char *s) {
		int len = strlen(s);
		for (int i = 0; i < len; i++) putc(s[i]);
	}
	void print_final() {fwrite(wbuf, 1, p3-wbuf, stdout);}
}
const int MAXN = 1000;
const int MAXV = 1e6;
int n, k; ll x[MAXN + 5], pp[MAXN + 5];
bool ok[MAXN + 5]; map<ll, int> cnt;
int prcnt, pr[MAXV / 6 + 5], vis[MAXV + 5];
void sieve(int n) {
	for (int i = 2; i <= n; i++) {
		if (!vis[i]) pr[++prcnt] = i;
		for (int j = 1; j <= prcnt && pr[j] * i <= n; j++) {
			vis[pr[j] * i] = 1;
		}
	}
}
vector<int> fac[MAXN + 5];
bool book[MAXN + 5];
int main() {
	scanf("%d%d", &n, &k); sieve(MAXV);
	map<ll, vector<int> > pos;
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &x[i]);
		bool flg = 1; ll tmp = x[i];
		for (int j = 1; j <= prcnt; j++) {
			if (x[i] % pr[j] == 0) {
				while (tmp % pr[j] == 0) tmp /= pr[j];
				if (tmp == 1) pp[i] = pr[j];
				else pp[i] = -1;
				break;
			}
		}
		pos[x[i]].pb(i);
	}
	for (int i = 1; i <= n; i++) if (!pp[i]) {
		if (x[i] <= 1e9 && !pos[x[i] * x[i]].empty()) {
			for (int j : pos[x[i] * x[i]]) pp[j] = x[i];
			pp[i] = x[i];
		}
		else pp[i] = -1;
	}
	int num = 0;
//	for (int i = 1; i <= n; i++) printf("%lld%c", pp[i], " \n"[i == n]);
	for (int i = 1; i <= n; i++) if (~pp[i]) cnt[pp[i]]++;
	vector<ll> seq; ll mpos = -1;
	for (auto p : cnt) if (p.se >= 2) {
		seq.pb(p.fi);
		if (p.se >= 3) mpos = p.fi;
	}
//	printf("%d\n", seq.size());
	for (int i = 1; i <= n; i++) {
		if (!~pp[i]) {
			ll tmp = x[i]; vector<int> fc;
			for (int j : seq) if (tmp % j == 0) {
				fc.pb(j);
				while (tmp % j == 0) tmp /= j;
			}
			if (tmp == 1) fac[i] = fc, num++, ok[i] = 1;
		}
		else if (cnt[pp[i]] == 1) pp[i] = -1;
		else num++;
	}
	if (num < k || k == 1) return puts("0"), 0;
	if (~mpos) {
//		puts("-1");
		if (k <= seq.size() * 2) {
			for (int j = 1, lft = 2 + (k & 1); j <= n; j++)
				if (pp[j] == mpos && lft) {
					book[j] = 1; lft--; k--;
				}
			for (int i = 0; i < seq.size(); i++) if (mpos != seq[i]) {
				for (int j = 1, lft = 2; j <= n; j++)
					if (pp[j] == seq[i] && lft && k) {
						book[j] = 1; lft--; k--;
					}
			}
		} else {
			for (int i = 0; i < seq.size(); i++)
				for (int j = 1, lft = 2 + (seq[i] == mpos); j <= n; j++)
					if (pp[j] == seq[i] && lft) {
						book[j] = 1; lft--; k--;
					}
			for (int i = 1; i <= n; i++) if (!book[i] && (ok[i] || pp[i] != -1) && k)
				book[i] = 1, k--;
		}
	} else {
		pii mn = mp(seq.size(), 0);
		for (int i = 1; i <= n; i++) if (ok[i]) chkmin(mn, mp((int)fac[i].size(), i));
		if (k <= 2 * mn.fi && (k & 1)) return puts("0"), 0;
		if (k <= 2 * seq.size()) {
			if (k % 2 == 0) {
				for (int i = 0; i < seq.size(); i++)
					for (int j = 1; j <= n; j++)
						if (pp[j] == seq[i] && k) {
							book[j] = 1; k--;
						}
			} else {
				book[mn.se] = 1; k--;
				for (int f : fac[mn.se]) {
					for (int j = 1; j <= n; j++) if (pp[j] == f)
						book[j] = 1, k--;
				}
				for (int i = 0; i < seq.size(); i++)
					for (int j = 1; j <= n; j++)
						if (pp[j] == seq[i] && !book[j] && k) {
							book[j] = 1; k--;
						}
			}
		} else {
			for (int i = 1; i <= n; i++) if (~pp[i]) book[i] = 1, k--;
			for (int i = 1; i <= n; i++) if (ok[i] && k) book[i] = 1, k--;
		}
	}
	for (int i = 1; i <= n; i++) if (book[i])
		printf("%lld ", x[i]);
	return 0;
}
/*
5 3
2 4 9 27 6

7 5
2 4 9 27 5 25 10

7 6
2 4 9 27 5 25 10
*/
```

---

## 作者：SegTree (赞：1)

## 前言 / Preface
这也是题？
## 题意 / Statement
定义一个序列 $a$ 是合法的，当且仅当任意满足 $P_i|a_i$ 质数序列 $P$ 中不存在只出现一次的数。

给定长度为 $n$ 的序列 $a$，求其中任意一个长度为 $k$ 的合法子序列。

$1\le k\le n\le 1000,1\le a_i\le 10^{18}$。
## 题解 / Solution
$k=1$ 显然无解。

先考虑对一个序列的合法性进行判定：

显然如果序列中能表示成 $p_i^{k_i}$ 中的某个 $p_i$ 只出现一次显然不合法。判掉这种情况以后，任意不能被表示成 $p_i^{k_i}$ 的数的所有质因子必须在 $p_i^{k_i}$ 中全部出现。

换言之，$\forall P|a_i,\exists a_j=P^x,a_k=P^y,j\ne k$。

先用 Pollard-Rho 分解质因子，把 $p^k$ 中对应 $p$ 只出现一次的数删掉，记此时 $p^k$ 总个数为 $tot$。

+ 如果 $k\ge tot$，先把这 $tot$ 那么只需要考虑余下的哪些满足上面提到的性质，如果这样的数不够 $k-tot$ 就无解，否则可以任意取 $k-tot$ 个。
+ 如果 $k$ 是偶数，问题是简单的。因为不能有单个出现的 $p^k$，所以可以按照奇数-偶数的顺序贪心选择，每次对于偶数选满对于奇数保留一个选满。此时不够的时候就接着去取之前没有取干净的奇数。
+ 如果 $k$ 是奇数：若存在出现 $3$ 次即以上的，取出 $3$ 个即变成了 $k$ 是偶数的问题；反之，此时只能从不是 $p^k$ 的合法数中凑 $1$ 个，考虑这种合法数必须选择的质因子个数最小值 $mn$，则在 $2mn+1\le k$ 时即可把它的质因子对应的两个插进去、把自己插进去，在剩下的里面任选即可；否则显然无解。

时间复杂度 $O(nV^{1/4})$。

---

## 作者：Leasier (赞：1)

首先特判 $k = 1$，此时显然无解。

考虑如何判断一个序列 $a$ 是不是 ideal 的。下面“出现”表示其作为 $a$ 的某项的质因数。

注意到：

- 如果存在一个只出现一次的质数 $p$，则它不是 ideal 的。

此时 $p$ 只能出现至多一次。

- 如果存在一个其幂次只出现 $\leq 1$ 的质数 $p$，则它不是 ideal 的。

若其幂次未出现，则我们从含质因数 $p$ 的其他项中选恰好一项选 $p$、其余不选 $p$。

若其幂次出现恰好一次，则我们让含质因数 $p$ 的其他项中不选 $p$。

------------

综上，我们只关心所以幂次出现 $\geq 2$ 次的质数，不妨设只含这些质因数的数的个数为 $u$，则 $k > u$ 时显然无解。

否则，设这些质数的个数为 $v$，则 $k \geq 2v$ 时我们可以先把这些质数的幂次每个选 $2$ 个，然后在剩下的数中随便选。

然后，$k$ 为偶数时我们可以类似地选 $\frac{k}{2}$ 对幂次。

最后，我们还有 $k < 2v$ 且 $k$ 为奇数的情况需要解决。

一个简明的想法是找一个幂次出现 $\geq 3$ 次的质数 $p$ 并选 $3$ 个它的幂次、剩下的部分同 $k$ 为偶数的情况，但此时可能不存在这样的 $p$。

经过一些思考我们发现这样的情况是可能有解的。设质数 $p \neq q$，令 $x = [p, p^2, q, q^2, pq], k = 5$，此时我们直接选择整个 $x$ 是合法的。

考虑对上面的解决方案进行推广：从 $x$ 的可选部分抓出一个 $x_i$，$x_i$ 的质因数必选，此时剩下待选的个数为偶数，于是又回到了 $k$ 为偶数的情况。 

贪心地，我们选择质因数个数最少的 $x_i$ 即可。如果最少者也不合法则无解。

最后的问题是分解质因数。注意到我们事实上并不关心 $> 10^9$ 的质因数——因为它们的幂次只会出现 $\leq 1$ 次，于是我们筛出 $\leq N = 10^6$ 范围内的质数，对每个 $x_i$ 挨个试除，特判最后剩下的 $p^2$ 状物即可。

时间复杂度为 $O(\frac{nN}{\ln N})$。

------------

代码：
```cpp
#include <stdio.h>
#include <math.h>

typedef long long ll;

const int N = 1e6, M = 1e3 + 7;
int prime[N + 7], bucket[N + 7], good[M], chosen[N + 7];
ll x[M];
bool mark[M], p[N + 7], vis[N + 7], sel[N + 7];

inline int init(){
	int cnt = 0;
	p[0] = p[1] = true;
	for (register int i = 2; i <= N; i++){
		if (!p[i]) prime[++cnt] = i;
		for (register int j = 1; j <= cnt && i * prime[j] <= N; j++){
			p[i * prime[j]] = true;
			if (i % prime[j] == 0) break;
		}
	}
	return cnt;
}

int main(){
	int n, k;
	scanf("%d %d", &n, &k);
	if (k == 1){
		printf("0");
		return 0;
	}
	int cnt1 = init(), cnt2 = 0, rem = 0, pair;
	for (register int i = 1; i <= n; i++){
		int p;
		ll t;
		scanf("%lld", &x[i]);
		t = x[i];
		for (register int j = 1; j <= cnt1; j++){
			if (x[i] % prime[j] == 0){
				while (t % prime[j] == 0){
					t /= prime[j];
				}
			}
		}
		if (t > 1){
			p = (int)sqrt(t);
			if ((ll)p * p == t){
				prime[++cnt1] = p;
			} else if (t <= 1e9){
				prime[++cnt1] = (int)t;
			} else {
				mark[i] = true;
			}
		}
		for (register int j = 1; j <= cnt1; j++){
			if (x[i] % prime[j] == 0){
				ll t = x[i];
				while (t % prime[j] == 0){
					t /= prime[j];
				}
				if (t == 1){
					good[i] = j;
					bucket[j]++;
					break;
				}
			}
		}
	}
	for (register int i = 1; i <= cnt1; i++){
		if (bucket[i] <= 1){
			vis[i] = true;
		} else {
			cnt2++;
		}
	}
	for (register int i = 1; i <= n; i++){
		if (mark[i]){
			mark[i] = false;
			continue;
		}
		mark[i] = true;
		for (register int j = 1; j <= cnt1; j++){
			if (x[i] % prime[j] == 0 && vis[j]){
				mark[i] = false;
				break;
			}
		}
		if (mark[i]) rem++;
	}
	pair = cnt2 * 2;
	if (k > rem){
		printf("0");
	} else if (k >= pair){
		k -= pair;
		for (register int i = 1; i <= n; i++){
			if (good[i] != 0 && bucket[good[i]] >= 2 && chosen[good[i]] < 2){
				chosen[good[i]]++;
				pair--;
				printf("%lld ", x[i], good[i]);
			} else if (mark[i] && k >= 1){
				k--;
				printf("%lld ", x[i]);
			}
		}
	} else if (k % 2 == 0){
		for (register int i = 1; i <= cnt1 && k >= 1; i++){
			if (bucket[i] >= 2){
				sel[i] = true;
				k -= 2;
			}
		}
		for (register int i = 1; i <= n; i++){
			if (sel[good[i]] && chosen[good[i]] < 2){
				chosen[good[i]]++;
				printf("%lld ", x[i], good[i]);
			}
		}
	} else {
		int pos = -1;
		for (register int i = 1; i <= cnt1; i++){
			if (bucket[i] >= 3){
				pos = i;
				break;
			}
		}
		if (pos != -1){
			sel[pos] = true;
			k -= 3;
			for (register int i = 1; i <= cnt1 && k >= 1; i++){
				if (i != pos && bucket[i] >= 2){
					sel[i] = true;
					k -= 2;
				}
			}
			for (register int i = 1; i <= n; i++){
				if (sel[good[i]] && chosen[good[i]] < (good[i] == pos ? 1 : 0) + 2){
					chosen[good[i]]++;
					printf("%lld ", x[i], good[i]);
				}
			}
		} else {
			int min_val = 1e9, min_pos = 0, first;
			for (register int i = 1; i <= n; i++){
				if (!mark[i] || good[i]) continue;
				int inside = 0;
				for (register int j = 1; j <= cnt1; j++){
					if (x[i] % prime[j] == 0) inside++;
				}
				if (min_val > inside){
					min_val = inside;
					min_pos = i;
				}
			}
			first = min_val * 2 + 1;
			if (k < first){
				printf("0");
			} else {
				k -= first;
				printf("%lld ", x[min_pos]);
				for (register int i = 1; i <= cnt1; i++){
					if (x[min_pos] % prime[i] == 0){
						for (register int j = 1; j <= n && chosen[i] < 2; j++){
							if (good[j] == i){
								chosen[i]++;
								printf("%lld ", x[j]);
							}
						}
					}
				}
				for (register int i = 1; i <= cnt1 && k >= 1; i++){
					if (bucket[i] >= 2 && chosen[i] == 0){
						sel[i] = true;
						k -= 2;
					}
				}
				for (register int i = 1; i <= n; i++){
					if (sel[good[i]] && chosen[good[i]] < 2){
						chosen[good[i]]++;
						printf("%lld ", x[i]);
					}
				}
			}
		}
	}
	return 0;
}
```

---

