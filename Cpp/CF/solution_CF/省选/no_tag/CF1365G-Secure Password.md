# Secure Password

## 题目描述

This is an interactive problem.

Ayush devised yet another scheme to set the password of his lock. The lock has $ n $ slots where each slot can hold any non-negative integer. The password $ P $ is a sequence of $ n $ integers, $ i $ -th element of which goes into the $ i $ -th slot of the lock.

To set the password, Ayush comes up with an array $ A $ of $ n $ integers each in the range $ [0, 2^{63}-1] $ . He then sets the $ i $ -th element of $ P $ as the [bitwise OR](https://en.wikipedia.org/wiki/Bitwise_operation#OR) of all integers in the array except $ A_i $ .

You need to guess the password. To make a query, you can choose a non-empty subset of indices of the array and ask the bitwise OR all elements of the array with index in this subset. You can ask no more than 13 queries.

## 说明/提示

The array $ A $ in the example is $ \{{1, 2, 4\}} $ . The first element of the password is bitwise OR of $ A_2 $ and $ A_3 $ , the second element is bitwise OR of $ A_1 $ and $ A_3 $ and the third element is bitwise OR of $ A_1 $ and $ A_2 $ . Hence the password sequence is $ \{{6, 5, 3\}} $ .

## 样例 #1

### 输入

```
3

1

2

4```

### 输出

```
? 1 1

? 1 2

? 1 3

! 6 5 3```

# 题解

## 作者：duyi (赞：15)

# CF1365G Secure Password

[题目链接](https://codeforces.com/contest/1365/problem/G)

每次询问，可以查询出一个**集合**里所有数的按位或。考虑通过某种构造方法，使得**对每个位置** $i$（$1\leq i\leq n$），**都能选出若干（被询问过的）集合**，满足：**$i$ 不在这些集合里，除 $i$ 外的所有位置都被包含在至少一个集合里**。如果能构造出一组满足上述条件的集合（不超过 $13$ 个），那么本题就做完了。

考虑使用二进制编码。第一反应有一个较为简单的做法：

- 因为 $n\leq 1000$，那么每个位置 $i$ 都可以对应一个 $10$ 位二进制数（可以有前导零）。
- 对每个二进制位，我们把所有这位是 $0$ 的位置的按位或值问出来；所有这位是 $1$ 的位置的按位或值问出来。

- 查询位置 $i$ 的答案，对每个二进制位 $j$（$0\leq j < 10$），设 $i$ 的第 $j$ 位为 $t$，那么就把答案或上第 $j$ 位与 $t$ 相反的那个集合。
- 正确性：
  - 显然位置 $i$ 不会被选中的集合包含。因为是按每一位取反选的，所以所选集合里的数，至少有一位与 $i$ 不同。
  - 所有 $\neq i$ 的位置都会被包含在至少一个集合里。因为其他位置至少会有一位与 $i$ 不同。
- 上述做法所需的询问次数是 $20$ 次。无法通过本题，需要进一步优化。

上述做法所需的询问次数太多了。下面有一个更妙的做法：

- 把所有 $13$ 位的、**恰好有 $6$ 个 $1$**的二进制数拿过来，作为编码。因为 ${13\choose 6} > 1000\geq n$，因此一定可以使得：**每个位置 $i$ 唯一对应一个编码**。
- 对每个二进制位 $j$（$0\leq j < 13$），把编码的第 $j$ 位上是 $1$ 的位置拿出来，询问他们的按位或，记为 $w_j$。
- 查询位置 $i$ 的答案。对每个二进制位 $j$（$0\leq j < 13$），如果 $i$ 的编码的第 $j$ 位为 $0$，那么就令答案或上 $w_j$。
- 正确性：
  - 显然位置 $i$ 不会被包含。
  - 所有 $\neq i$ 的位置，至少存在某一位，使得它的编码这一位上是 $1$ 而 $i$ 的编码这一位上是 $0$。这是因为我们保证了所有编码里 $1$ 的个数相同。
- 需要 $13$ 次询问，可以通过本题。


```cpp
// problem:
#include <bits/stdc++.h>
using namespace std;

#define mk make_pair
#define fi first
#define se second
#define SZ(x) ((int)(x).size())

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;

template<typename T> inline void ckmax(T& x, T y) { x = (y > x ? y : x); }
template<typename T> inline void ckmin(T& x, T y) { x = (y < x ? y : x); }

const int MAXN = 1000;
int n;
int bitcnt[1 << 13];
int id[MAXN + 5], cnt;
ull res[13];

int main() {
	cin >> n;
	for (int i = 1; i < (1 << 13); ++i) {
		bitcnt[i] = bitcnt[i >> 1] + (i & 1);
		if (bitcnt[i] == 6) {
			id[++cnt] = i;
			// cerr << "id " << cnt << ": " << i << endl;
			if (cnt == n) {
				break;
			}
		}
	}
	for (int i = 0; i < 13; ++i) {
		vector<int> v;
		for (int j = 1; j <= n; ++j) {
			if ((id[j] >> i) & 1) {
				v.push_back(j);
			}
		}
		if (SZ(v)) {
			cout << "? " << SZ(v) << " ";
			for (int j = 0; j < SZ(v); ++j) {
				cout << v[j];
				if (j != SZ(v) - 1) cout << " ";
			}
			cout << endl;
			cin >> res[i];
		} else {
			res[i] = 0;
		}
	}
	cout << "! ";
	for (int i = 1; i <= n; ++i) {
		ull ans = 0;
		for (int j = 0; j < 13; ++j) {
			if (!((id[i] >> j) & 1)) {
				ans |= res[j];
			}
		}
		cout << ans;
		if (i != n) cout << " ";
	}
	cout << endl;
	return 0;
}
```



---

## 作者：lottle1212__ (赞：6)

# [Secure Password](https://www.luogu.com.cn/problem/CF1365G)

解决这题的过程中，我的思路有三个阶段。

## Part1

显而易见地分别去问 $n$ 个人。（但大佬们认为 Part2 才是显然的，我太菜了）

对于每一个位置，把其他位置全部或起来，就是答案。

## Part2

由于是或操作，则一个数被或上多次并不影响结果。

那么就考虑把数分成几个集合，最后答案通过并集得到。

把编号看做二进制数，对于每一位，是 $0$ 的所有数分别放到一起，是 $1$ 的所有数分别放到一起，分别询问。求答案时，对于编号的每一个二进制位，是 $1$，则或上这一位是 $0$ 的询问；是 $0$，则或上 $1$ 的询问。

总次数是 $2\times\log(n)$ 的，还差一点。

## Part3

上面这个例子是利用了二进制，然而有 $2$ 的常数。更优的解法是使用组合数。

对于每一个编号的数，只要与其他编号的数有一个出现的询问不一样即可。总共有 $13$ 个询问，每个编号的数放在 $p$ 个询问中，且保证每一个编号的数放的询问集合不同，就能求出答案。总共有 $C_{13}^p$ 种集合，取 $p=6$ 时，$C_{13}^p>1000$，可以通过。

[Code](https://codeforces.com/contest/1365/submission/279804782).

---

## 作者：Zcus (赞：4)

本题解同步于 [Myblog](https://oi.ender-zzm.pro/index.php/archives/94/)
### 题解

挺容易的一个题

首先显然有20次的二进制分组做法， 但是题目要求13次，还是多了

但是这个题目十分的奇怪， 经过几次实验可以发现$C(13, 6) > 1000$ 这就代表着我们对这1000个数用一个13位的有6个1的二进制标记， 每一个的二进制都是不同的， 而且绝对没有包含关系， 这样的话， 我们就可以去求出每一个位置上的权值



### 代码

```cpp
/*
Arthor: Ender_zzm
E-mail: ender-zzm@foxmail.com
Blog: oi.ender-zzm.pro
*/

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define int long long
//#define FILE
#define fi first
#define se second
#define vec vector
#define pb push_back
#define pii pair<int, int>
#define mp make_pair
#define ri read<int>
#define rl read<long long>
#define debug(x) cout << #x << " = " << x << endl
#define For(i, x, y) for (int i = x; i <= y; i++) 
#define Rep(i, x, y) for (int i = x; i >= y; i--) 
#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)
#define filein(FILE_NAME) freopen(FILE_NAME".in", "r", stdin);
#define fileout(FILE_NAME) freopen(FILE_NAME".out", "w", stdout);


const int LEN = 1 << 20 | 1;
static char buf[LEN], *_s, *_t;
static char obuf[LEN], *O = obuf;
struct ios {
	inline bool Isdigit(char c) {
		return (c >= '0' && c <= '9') ? 1 : 0;
	}
    inline char gc(){
#ifdef FILE
        return (_s==_t)&&(_t=(_s=buf)+fread(buf,1,LEN,stdin)),_s==_t?-1:*_s++;
#endif
#ifndef ZZM
        return (_s==_t)&&(_t=(_s=buf)+fread(buf,1,LEN,stdin)),_s==_t?-1:*_s++;
#endif
		return getchar();
    }
    template <class T> 	inline ios & operator >> (T &x) {
        static char ch, sgn; ch = gc(), sgn = 0;
        for (; !isdigit(ch); ch = gc()) {if(ch==-1)return *this; sgn|= ch=='-';}
        for (x = 0; isdigit(ch); ch = gc()) x = x * 10 + (ch ^ '0');
        sgn&&(x=-x); return *this;
    }
	inline void flush() {
		fwrite(obuf,1,O-obuf,stdout);
        O=obuf;
        fflush(stdout);
	}
	~ios() {flush();}
	inline void pr(const char c) {
#ifdef FILE
  		if(O - obuf > LEN-2) flush();
        *O++=c;		
		return;
#endif
#ifndef ZZM
  		if(O - obuf > LEN-2) flush();
        *O++=c;		
		return;
#endif
		return (void)putchar(c);
	}
	template <class T> inline ios & operator << (T x) {
		static char a[25] = {0}, *p = a;
		if (x < 0) pr('-'), x = -x;
		if (x == 0) pr('0');
		while (x) *(++p) = x % 10, x /= 10;
		while (p != a) pr(char(*(p--)) + '0');
		return *this;
	}
	inline ios & operator << (const char c) {pr(c);return *this;}
} io;


template<class T> inline bool Chkmax(T& x, const T& y) { return x < y ? x = y, true : false; }
template<class T> inline bool Chkmin(T& x, const T& y) { return x > y ? x = y, true : false; }


const int maxn = 1e5;
int n;
int Query(vec<int> q) {
	cout << "? " << q.size() << " ";
	for (int i = 0; i < q.size(); i++) {
		cout << q[i] << " ";
	}
	cout << endl; cout.flush();
	int x;
	cin >> x;
	return x;

}
vec<int> G[maxn];
int val[maxn];
int a[maxn][14], cnt;
int s[maxn];
void add() {
	int x = 1;
	++cnt;
	for (int i = 1; i <= 13; i++) {
		a[cnt][i] = s[i];
	}
}
void dfs(int x, int cnt) {
	if (::cnt == n + 1) return;
	if (x == 14) {
		if (cnt == 6) add();
		return;
	}
	if (cnt < 6) {
		s[x] = 1;
		dfs(x + 1, cnt + 1);
	}
	s[x] = 0;
	dfs(x + 1, cnt);
}
signed main() {
	cin >> n;
	dfs(1, 0);
	For (i, 1, 13) {
		For (j, 1, n) {
			if (a[j][i]) G[i].pb(j);
		}
		if (G[i].size()) val[i] = Query(G[i]);
//		debug(val[i]);
	}
	cout << "! ";
	For (i, 1, n) {
		int ans = 0;
		For (j, 1, 13) {
			if (a[i][j] == 0)  ans = ans | val[j];
		}
		cout << ans << " ";
	}
	cout << endl; cout.flush();
	return 0;
}

```





---

## 作者：Rainy_chen (赞：4)

## 题意
有一个固定的数组 $A$，同时通过数组 $A$ 构造出数组 $P$，具体来讲，$P_i$ 是 $A$ 中除 $A_i$ 外的所有元素的按位或。  

有最多 $13$ 次询问机会，每次询问可以指定一个 $A$ 的下标集合，之后会得到这几个位置的 $A_i$ 的按位或。  

## 题解
考虑对于任意两个 $i,j(i\neq j)$，必然满足其至少在二进制的某一位上不同，否则就有 $i=j$ 而不满足假设。  

于是对于 $i$，考虑其每一个二进制位 $k$，若已知所有在 $k$ 位上与 $i$ 不同的数的或，只需将每一个 $k$ 求出这样的或以后再或一次即可。  

但是这样做需要 $2logn$ 次询问，因为你需要询问第 $k$ 位为 $1$ 与不为 $1$ 的所有下标集合。  

考虑这样一个做法的本质，实际上我们为每一个 $i$ 分配了恰好一半的询问，也就是说有 $logn$ 个询问中包含了 $i$。那么我们确定 $P_i$ 的方法实际上是将剩下 $logn$ 次询问的结果做了一个按位或，由于不可能有两个不同的数二进制相同，所以也不可能在只询问剩下 $logn$ 个询问集合的时候遗漏了某个本应存在的 $A_j$。  

可以发现实际上这玩意只需要保证任意两个数对应到数次询问后，不存在 $i,j$ 满足所有包含了 $i$ 的询问都同时包含了 $j$，换句话说，一种类似于子集的关系。  

更具体地说就是我们使用 $i$ 的二进制来分配集合只是因为这样恰好满足了上面这个性质并且很好想，但是实际上这样来分配询问集合会导致有一些本来可用的询问组合被弃用。  

例如你绝不会在第 $k$ 位为 $0$ 的询问集合和不为 $0$ 的询问集合中同时包含一个数，但是这并不会违反上面所说的性质。  

我们可以考虑直接为每一个 $i$ 分配一个长度为 $q$ 的包含了 $k$ 个二进制位为 $1$ 的数，之后对于询问 $j$，若 $i$ 分配的这个数在第 $j$ 位上有 $1$ 就把 $i$ 塞到这次询问里，分配的这个数在官方题解里好像是叫做 bitmask 位掩码？不过这无所谓，谁会关心具体名字呢（）  

可以发现能够分配的不同的数的个数是 $\binom qk$，这玩意在 $k=\lfloor\frac q2\rfloor$ 取到最大值，而 $\binom {13}6=1716>10^3$。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long int_t;

struct Query {
    vector<int_t> indicies;
    int_t ans;

    bool inQuery(int_t ind) {
        for(int_t x : indicies) if(x == ind) return true;
        return false;
    }
} qs[14];

int_t bit_count(int_t x) {return x ? (x & 1) + bit_count(x / 2) : 0;}

int main() {
    int_t n; cin >> n;
    int_t used = 0;
    for(int_t i=1;i<(1<<13);i++) {
        if(bit_count(i) != 6) continue;
        ++used;
        for(int_t j=0;j<13;j++) if(i & (1 << j)) qs[j + 1].indicies.push_back(used);
        if(used == n) break;
    }
    for(int_t i=1;i<=13;i++) if(qs[i].indicies.size()) {
        cout << "? " << qs[i].indicies.size() << " ";
        for(int_t x : qs[i].indicies) cout << x << " ";
        cout << endl;
        cin >> qs[i].ans;
    }
    cout << "! ";
    for(int_t i=1;i<=n;i++) {
        int_t ans = 0;
        for(int_t j=1;j<=13;j++) if(!qs[j].inQuery(i)) ans |= qs[j].ans;
        cout << ans << " ";
    }
    cout << endl;
}
```

---

## 作者：Rubidium_Chloride (赞：2)

超爽的构造题！

考虑一个显然的 二进制分组做法，即将所有数对应成长度为 $10$ 的二进制，对于每个二进制位查询所有编号该位为 $1$ 或者 $0$ 的按位或值。

发现需要 $20$ 次问询。

如何优化？

二进制分组是没啥问题了，如何减少查询次数？

尝试规避每一位取 $0$ 和 $1$ 都要查询的情况，也就是要更换编码。

$13$ 是哪里来的呢，大概就是二进制编码位数。

$\dbinom{13}{6}>1000$，考虑每个数转换成 $13$ 位二进制数，且恰有 $6$ 位为 $1$。

每次查询每一位为 $1$ 的集合按位或的结果。

输出答案时考虑 $i$ 时，如果编码后 第 $j$ 位为 $0$，按位或上第 $j$ 位为 $1$ 的答案。

可以证明的是，除了 $i$ 的数都被不遗漏地按位或了一次。

代码：


```
#include<bits/stdc++.h>
#define N (1<<13)
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
typedef long long ll;
inline ll read() {
    ll x=0,f=1;int c=getchar();
    while(!isdigit(c)) {if(c=='-') f=-1;c=getchar();}
    while(isdigit(c)) {x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    return x*f;
}
ll n,cnt[N],tot[13],p[13][1009],id[1009],q,v[13],ans[1009];
int main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    n=read();
    for(int i=1;i<N;i++) cnt[i]=cnt[i>>1]+(i&1);
    for(int i=1;i<=n;i++){
        while(cnt[q]!=6) q++;
        id[i]=q,q++;
    }
    for(int i=0;i<13;i++)
        for(int j=1;j<=n;j++) if((id[j]>>i)&1) p[i][++tot[i]]=j;
    for(int i=0;i<13;i++) if(tot[i]!=0){
        printf("? %lld ",tot[i]);
        for(int j=1;j<=tot[i];j++) printf("%lld ",p[i][j]);
        printf("\n"),fflush(stdout);
        v[i]=read();
    }
    for(int i=1;i<=n;i++) for(int j=0;j<13;j++) if(((id[i]>>j)&1)==0) ans[i]|=v[j];
    printf("! ");
    for(int i=1;i<=n;i++) printf("%lld ",ans[i]);
    return 0;
}
```

---

## 作者：wmrqwq (赞：1)

场切了，写篇题解纪念一下。

# 题目链接

[CF1365G Secure Password](https://www.luogu.com.cn/problem/CF1365G)

# 解题思路

首先有个非常显然的次数为 $2 \times \log n$ 次的做法，就是我们根据二进制逐位考虑即可，那么为什么次数要乘上 $2$ 呢，因为你在求出答案时，需要通过 $0,1$ 两种不同的数位来确定答案。

那么这样，询问次数是 $2 \times \log n$ 级别的，不能通过本题。

我们考虑继续运用二进制来解决这个问题。

由于我们可以询问 $13$ 次，并且 $n \le 10^3$，因此我们可以很自然地想出通过给每个数字进行 $13$ 位的二进制编码来解决这个问题，那么怎么编码呢？由于 $\binom{13}{6} > 10^3$，因此我们就可以将每个数字编码为**不同的在二进制下含有 $6$ 个 $1$ 的数字**。询问形式为第 $j$ 依次询问 $n$ 个数中二进制编码下第 $j$ 位为 $1$ 的数字，查询也同理，第 $i$ 个位置的答案就是这个位置的编号所有 $0$ 的位置上询问出来的答案的按位或之和，容易证明这样必定可以或上除自己之外的所有数，因此这样做是对的。

若由于编码总共只有 $13$ 个二进制位，因此查询次数为 $13$ 次，可以通过本题。

# 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
//#define map unordered_map
#define re register
#define ll long long
#define forl(i,a,b) for(re ll i=a;i<=b;i++)
#define forr(i,a,b) for(re ll i=a;i>=b;i--)
#define forll(i,a,b,c) for(re ll i=a;i<=b;i+=c)
#define forrr(i,a,b,c) for(re ll i=a;i>=b;i-=c)
#define pii pair<ll,ll>
#define mid ((l+r)>>1)
#define lowbit(x) (x&-x)
#define pb push_back
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
//#define endl '\n'
#define QwQ return 0;
ll _t_;
void _clear(){}
ll n,id[2010];
ll a[15];
ll k;
vector<ll>G;
ll pw(ll x){
	return 1ll<<x;
}
ll f(ll x)
{
	ll sum=0;
	while(x)
		sum+=x%2,x/=2;
	return sum;
}
void init(){
	forl(i,0,pw(13)-1)
		if(f(i)==6)
			id[++k]=i;
}
ll ask(vector<ll>x)
{
	if(x.size()==0)
		return 0;
	cout<<"? ";
	cout<<x.size()<<' ';
	for(auto i:x)
		cout<<i<<' ';
	cout<<endl;
	ll y;
	cin>>y;
	return y;
}
void solve()
{
	_clear();
	cin>>n;
	forl(i,0,12)
	{
		G.clear();
		forl(j,1,n)
			if(id[j]&pw(i))
				G.pb(j);
		a[i]=ask(G);
	}
	cout<<"! ";
	forl(i,1,n)
	{
		ll ans=0;
		forl(j,0,12)
			if(!(id[i]&pw(j)))
				ans|=a[j];
		cout<<ans<<' ';
	}
	cout<<endl;
}
int main()
{
	init();
//	IOS;
	_t_=1;
 //	cin>>_t_;
	while(_t_--)
		solve();
	QwQ;
}
```

---

## 作者：Purslane (赞：1)

# Solution

首先，我们发现可以二进制分组。由于 $1$ 到 $n$ 中所有和 $i$ 不同的数 $j$ 都必然有一位上 $i$ 和 $j$ 不相等，所以我们每次找出下标二进制下第 $t$ 为 $0$ 的集合 $S$ 和为 $1$ 的集合 $T$，把 $\text{query} (S)$ 全部或到 $T$ 上，把 $\text{query} (T)$ 全部或到 $S$ 上。

但是这样需要 $20$ 次询问。

考虑如果任意两个下标 $i$ 和 $j$ 的二进制表示都有：必有一位 $i$ 是 $1$ 且 $j$ 是 $0$，而且必有一位 $i$ 是 $0$ 且 $j$ 是 $1$，我们一位只需要询问一个集合就可以了。

所以如果 $i$ 和 $j$ 的 $\text{popcount}$ 相等就好了。这说明我们得给他们人工附加下标。

然后你发现 $C_{13}^6 > 1000$，所以我们选取 $2^{13}-1$ 内所有 $\text{popcount}$ 为 $6$ 的数作为新的下标即可。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1e3+10;
int n,a[MAXN],id[MAXN],res[MAXN];
vector<int> S;
int pop_count(int n) {
	int ans=0;
	while(n) ans++,n-=n&-n;
	return ans;	
}
int query(vector<int> S) {
	if(S.size()==0) return 0;
	cout<<"? "; cout<<S.size()<<' ';
	for(auto id:S) cout<<id<<' ';
	cout<<endl;
	int ans; cin>>ans;
	return ans;
}
signed main() {
	cin>>n;
	ffor(i,0,(1<<13)-1) if(pop_count(i)==6) S.push_back(i);
	ffor(i,1,n) id[i]=S[i-1];
	ffor(i,0,12) {
		vector<int> T;
		ffor(j,1,n) if(!(id[j]&(1<<i))) T.push_back(j);
		int ans=query(T);
		ffor(j,1,n) if(id[j]&(1<<i)) res[j]|=ans;
	}
	cout<<"! ";
	ffor(i,1,n) cout<<res[i]<<' ';
	cout<<endl;
	return 0;
}
```

---

## 作者：songhongyi (赞：1)

Fixed: binom 打反了。

---

按位或是一个可重复贡献的东西。因此题目可以被认为是构造 $13$ 个集合 $S_i$，满足对任意一个 $i$，都存在若干个集合，其并恰为 $\{1,2,\cdots, n\}\setminus\{i\}$。

我们用 $T_i$ 表示 $i$ 所在的集合组成的族。不难发现满足此要求需要对于任意一对 $(i,j)$，都有一个集合 $S$ 满足 $S \not\in T_i$ 且 $S \in T_j$。这样我们在询问 $i$ 的时候，只需要取 $\{1,2,\cdots,n\}  \setminus  T_i$ 即可。

如果我们取 $T_i$ 为所有大小为 $6$ 的族，其方案数为 $\binom{13}{6}>1000$。同时显然两个不同的族一定存在满足上述条件的子集。

问题顺利解决。

---

## 作者：sunkuangzheng (赞：1)

看到题目第一个想到的就是二进制分组，即对于每个 $j(0 \le j \le 9)$，询问二进制下第 $j$ 位为 $0$ 和 $1$ 的下标集合，回答询问时，给答案或上第 $j$ 位与 $i$ 这一位值相反的集合。由于不存在两个不同的数字二进制编码相同，所以上面的方法可以遍历到每一个非 $i$ 元素。但是，它需要 $20$ 次询问。

观察询问过程，你发现我们的询问方式不太明智，询问过程中大量的信息被重复问到。想要在 $13$ 次询问内完成交互，我们需要设计一种新的编码方式。

二进制分组时，我们要对每一位是 $0$ 和 $1$ 分别问一次，因为可能会存在两个二进制编码，一个是另一个的子集。考虑这样一种编码：不存在两个不等数字，其编码一个是另一个的子集。有这样的编码，我们可以对于每一位只问一次吗？答案是肯定的。

考虑如果编码里不会出现 $i$ 是 $j$ 的子集，意味着一定存在两位 $p,q$，使得 $i$ 在第 $p$ 位上是 $0$，第 $q$ 位上是 $1$，而 $j$ 在这两位上的值正好相反。也就是说，对于所有不等于 $i$ 的数字 $j$，都至少存在一位 $k$ 满足第 $k$ 位上 $j$ 是 $1$ 而 $i$ 是 $0$。我们可以只询问每一位上是 $1$ 的下标集合。

如何构造这样的编码？根据询问次数，推断出编码长度应该是 $13$ 位。我们需要使编码互相不为子集，简单的办法是所有编码 $1$ 的数量相等。当然，我们需要编码至少能表示 $10^3$ 个数字，所以我们希望表示的数字尽可能多。显然 $\dbinom{13}{6} = \dbinom{13}{7}$ 是大于其他 $n = 13$ 的组合数的，那么我们选择 $6$ 个 $1$ 的 $13$ 位编码即可。计算得知，这样的编码大于 $1700$ 个，满足要求。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int unsigned long long
int t,n,k,a[15],p[2505],cnt;
signed main(){
    ios::sync_with_stdio(0),cin.tie(0);
    cin >> n;
    auto ask = [](vector<int> acc){
        if(!acc.size()) return 0ull;
        cout << "? " << acc.size() << " ";
        for(int i : acc) cout << i << " ";
        return cout << endl,cin >> k,k;
    };for(int i = 0;i < (1 << 13);i ++) if(__builtin_popcount(i) == 6) p[++cnt] = i;
    for(int j = 0;j <= 12;j ++){
        vector<int> acc,cjr;
        for(int i = 1;i <= n;i ++) if((p[i] >> j) & 1) acc.push_back(i);
        a[j] = ask(acc);
    }cout << "! ";
    for(int i = 1;i <= n;i ++){
        int ans = 0;
        for(int j = 0;j <= 12;j ++) if(!((p[i] >> j) & 1)) ans |= a[j];
        cout << ans << " ";
    }
}

---

## 作者：45dinо (赞：1)

非常巧妙的题。

先说一种方法，尽管和正解的思想一样，但实现方法略有不同。~~而且是错的~~

设 $f_{i,j}$ 表示所有 $a_x$ 的按位或的值。其中 x 的二进制位的第 i 位为 j。(个位是第一位）

比如 $f_{1,0}$ 就是 $a_2|a_4|a_6|\dots$ ，因为 2，4，6 的二进制位的第一位都是 0。

如果要求 $p_5$ 的值，其实就是求 $f_{3,0}|f_{2,1}|f_{1,0}$，因为 $(5)_{10}=(101)_{2}$，把第三位是 0 的数和第二位是 1 的数和第 1 位是 0 的数全部按位或即为所求，这三部分会有重复（没有关系）但不会遗漏除 5 以外的数（遗漏我直播吃电脑）

如果预处理 f，要交互 $2\times \log n$ 次，最多是 20 ，随便就会被卡掉，但学到了一个新思路——尝试利用 a 数组的下标进行分类。

然后就是正解：

尝试优化上述方法，**减少交互次数**，可以发现，只要规避每一位反别考虑 1 和 0 的情况就可以将交互次数减少一半，又发现**最多13次交互而不是10次**，所以可以考虑这样做：

将每一个 a 数组的下标都转换成一个 13 位的二进制编码，且恰好有 6 个 1。

e.g.
$$1\rightarrow 0000000111111$$
$$2\rightarrow 0000001011111$$
$$3\rightarrow 0000010011111$$
$$\cdots$$

最多可以存 $\dbinom{13}{6}=1716$ 个编码，对应 1000 个下标绰绰有余。

这里只需要存储 $w_i$ ,存的是上文 $f_{i,0}$ 相同的东西，只不过对应的是编码而不是下标。

如果要算 $p_3$，就算 $w_x$ 按位或的值，x 表示 $a_3$ 对应的编码中所有 1 的位置。

可以说明，这个答案即为所求，理由同上文。

所以为什么只用存储 0 而不用存储 1 呢？我认为因为在计算 $p_i$ 时，只考虑了 $a_i$ 的编码中 1 的位置，这也是正解的巧妙之处。

喜闻乐见的代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,cnt,w[14],ans[1001],num[1001];
vector<int> ask[14];
int query(vector<int> v)
{
	if(v.size()==0)
		return 0;
	cout<<"? "<<v.size();
	for(auto i:v)
		cout<<" "<<i;
	cout<<endl;
	int res;
	scanf("%lld",&res);
	return res;
}
signed main()
{
	scanf("%lld",&n);
	for(int i=1;i<(1<<13);i++)
		if(__builtin_popcount(i)==6)
		{
			num[++cnt]=i;
			for(int j=0;j<13;j++)
				if(!(i&(1<<j)))
					ask[j].push_back(cnt);
			if(cnt==n)
				break;
		}
	for(int i=0;i<13;i++)
		w[i]=query(ask[i]);
	cout<<"!";
	for(int i=1;i<=n;i++)
	{
		int ans=0;
		for(int j=0;j<13;j++)
			if(num[i]&(1<<j)) 
				ans|=w[j];
		cout<<" "<<ans;
	}
	return 0;
}
```

---

## 作者：DJRzjl (赞：1)


考虑二进制分组，$n\le1000<2^{10}$，所以可以将下标分为 $10$ 组，第 $i$ 组包含 $1$ 到 $n$ 中下标二进制第 $i$ 位为 $1$ 的位置。记 $w_i$ 表示询问第 $i$ 组的结果，$v_i$ 表示询问第 $i$ 组补集（即二进制位第 $i$ 位是 $0$​ 的下标集合，包括前导零）的结果。

对于求 $A_i$ 的值，枚举 $i$ 二进制下每一位，若第 $j$ 位为 $1$​，或上 $v_j$，否则或上 $w_j$。

相当于说，对于每个集合，若 $i$​ 在里面，或上该集合补集的询问结果，若不在，或上该集合本身的询问结果。

证明：首先我们或上的集合都不包含 $i$；其次不存在一个数 $j$ 不等于 $i$，但包括 $j$ 的集合与包括 $i$ 的集合相同，那么 $j$ 的值一定会在计算其与 $i$​ 二进制不一样的位置时被或进 $A_i$。综上，这样做可以使得 $A_i$ 满足题意。

但是这么做求 $w_i$ 和 $v_i$ 需要 $20$ 步操作，超出了要求，考虑优化。

注意到 $\binom{13}{6}=1716>1000$​，我们可以尝试用 $n$ 个 $13$ 位，并且恰好含有 $6$ 个 $1$ 的二进制数替换传统转换进制，来给这 $n$​ 个下标重新编码。然后我们与之前一样按照新的编码，将下标分为 $13$ 组。

这样做有什么好处？由于每个位置 $1$ 的数量相等，所以对于 $i,j(i\not=j)$​，一定既存在某一组 $i$ 在之中但 $j$ 不在，又存在一组 $j$ 在之中但 $i$​ 不在，这在之前的分组方式中则不能保证。

进一步的，我们就不需要询问每个 $v_i$ 了，对于每个 $A_i$，它就等于 $i$​ 对应新二进制编码为 $0$ 位所对应集合的 $w$ 或起来的值。总共 $13$ 次询问。

---

### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e3+10,Mx=1<<13;

int n,cnt,id[N];
ll w,ans[N];

int main(){
	scanf("%d",&n);
	for(int i=0;i<Mx&&cnt<n;i++) if(__builtin_popcount(i)==6) id[++cnt]=i;
	for(int i=0;i<13;i++){
		int now=1<<i,sum=0;
		for(int j=1;j<=n;j++) if(id[j]&now) sum++;
		if(sum){
			printf("? %d",sum);
			for(int j=1;j<=n;j++) if(id[j]&now) printf(" %d",j);
			putchar('\n'),fflush(stdout);
			scanf("%lld",&w);
			for(int j=1;j<=n;j++) if(!(id[j]&now)) ans[j]|=w;
		}
	}
	putchar('!');
	for(int i=1;i<=n;i++) printf(" %lld",ans[i]);
	return 0;
}
```


---

## 作者：奇米 (赞：1)

# 题解 - $\mathrm{CF1365G}$

## 题目意思

* [题目传送门](https://www.luogu.com.cn/problem/CF1365G)

## $\mathrm{Sol}$

* 很巧妙的一道思维题

我们首先考虑如果可以交互的次数较多怎么做？

我们可以设 $f_{i,j}$ 表示对于 $a_{k}$ 的或和，其中 $k$ 的第 $i$ 位为 $j$。那么统计答案时候比如 $P_6=f_{3,0}|f_{2,0}|f_{1,1}$，因为 $(6)_{2}=[1,1,0]$

这样的做法交互次数肯定大于 $13$ 次，我们考虑如何优化。一个方法就是把每个数的下标用二进制位表示，因为 $n\leq 10^3$，并且 $C_{13}^{6}>10^3$ 所以我们对于 $13$ 个二进制位以及 $6$ 个 $1$ 就足够表示所有下标了。

我们这次不再对下标进行dp，而是对其二进制编号我们用 $v_i$ 记录，其实 $v_i=f_{i,0}$。那么此时我们计算 $P_x=\sum v_i$ 其中 $i$ 为 $x$ 的二进制为 $1$ 的位置。

## $\mathrm{Code}$

```cpp

int n,m,A[2005],t[15];
vector<int> vec[15];

inline int query(int x)
{
	if(!vec[x].size()) return 0;
	cout<<"?"<<" "<<(int)vec[x].size()<<" ";
	For(i,0,(int)vec[x].size()-1) cout<<vec[x][i]<<" ";
	cout<<endl;
	cin>>m;
	return m;
}

signed main()
{
	io.read(n);
	int S=(1ll<<13)-1;
	For(i,0,S) if(__builtin_popcount(i)==6) 
	{
		A[++*A]=i;
		For(j,0,12) if(!(i&(1ll<<j))) vec[j].pb(*A);
		if((*A)==n) break;
	}
	For(i,0,12) t[i]=query(i);
	cout<<"!"<<" ";
	For(i,1,n) 
	{
		int sum=0,x=A[i];
		For(j,0,12) if((x>>j)&1ll) sum|=t[j];
		io.write(sum),putchar(' ');
	}
	return 0;
}
		

```


---

## 作者：xfrvq (赞：0)

恐怖。

数据范围略大于 $\lfloor\log n\rfloor$，$2\log$ 做法很多，容易把人引入死胡同。

考虑一个 $2\log$ 做法，对于 $\lfloor\log n\rfloor$ 每个二进制位，求出这一位为 $0,1$ 的数分别的或和，对于一个 $i$ 的所有二进制位的相反位，答案的或和。

正确性显然，每一个 $j\ne i$，$j$ 一定有至少一个二进制位与 $i$ 不同。

但我们压榨的还不够。继续考虑发现 $2\log$ 是这个算法或类似算法的下界，必须把 $2$ 去掉。

瓶颈在于必须同时维护 $0,1$ 的答案，是因为二进制位间存在包含关系，有一位 $i$ 为 $1$，$j$ 为 $0$ 或者 $i$ 为 $0$，$j$ 为 $1$ 才能说明 $i,j$ 不同。

考虑进行一轮重编号，此时任意 $i,j$ 不再具包含关系，有一位 $i$ 为 $1$，$j$ 为 $0$ 说明一定有另一位 $i$ 为 $0$，$j$ 为 $1$。我们只需要维护 $0$ 的答案。仅对每一位 $1$ 用该位 $0$ 的答案即可。

考虑 $C_{13,6}\ge10^3$，于是取所有编号为 $[0,2^{14})$ 中有 $6$ 个二进制位的数，此时需要对每个二进制位询问，共 $13$ 次。

```cpp
#include<bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 1e3 + 5;

int n,p[N];
ll f[N],a[N],S;

int main(){
	scanf("%d",&n);
	for(int i = 1;i <= n;++i)
		for(f[i] = f[i - 1] + 1;__builtin_popcount(f[i]) != 6;++f[i]);
	for(int j = 0,x;j < 13;++j){
		for(int i = 1;i <= n;++i) if(!(f[i] >> j & 1)) p[++p[0]] = i;
		if(p[0]){
			printf("? %d",p[0]);
			for(int i = 1;i <= p[0];++i) printf(" %d",p[i]);
			cout << endl,scanf("%lld",a + j),p[0] = 0;
		}
	}
	printf("! ");
	for(int i = 1;i <= n;printf("%lld ",S),++i)
		for(int j = S = 0;j < 13;++j) if(f[i] >> j & 1) S |= a[j];
	return 0;
}
```

---

## 作者：strcmp (赞：0)

挺人类智慧的题。

首先，$x \, \text{or} \, x = x$，且位或满足交换律。

然后你发现刨出一个位置其实不好按位或自己的性质考虑，你好像只能去考虑凑出一个大小为 $13$ 的位置集合的集合，使得它们都能有至少一种方案，组合起来，覆盖掉所有扣掉某一个位置的集合。

那你不妨将位置看成二进制，因为 $n \le 10^3,\,2^{10} - 1 = 1023 > n$，所以我们可以把每个位置映射成一个二进制数。比如 $1 \to 0000,\,2 \to 0001,\,6 \to 0101$。

然后可以想到，对于每个位置，我们取出它代表的二进制。

枚举位置 $i$，然后按位考虑 $i$ 映射到的二进制数，比如当前位是 $0$，那我们肯定是去位或上当前位是 $1$ 的其它所有位置。我们显然不能保证就能覆盖掉所有不等于 $i$ 的位置，但至少可以保证这些位置一定与 $i$ 不同。

那预处理 $w_{i,\,0/1}$ 代表满足从低到高第 $i$ 位是 $0/1$，其余位任选的所有位置的位与结果。

然后枚举到位置 $x$，就取出所有 $x$ 的二进制位，比如当前是 $0$，则去找这一位是 $1$ 的位或结果，否则找 $0$ 的位或结果。

这样覆盖了所有不是 $i$ 的位置，感性理解是很显然的，不等于 $i$ 的位置，映射到的二进制数一定至少有一位跟 $i$ 映射的二进制数不同。

但是这样要用到 $10 \times 2 = 20$ 次询问，做不了。

但有进步了，我们现在需要将每个位置映射成一堆二进制的集合，比如 $f(x)$ 代表 $x$ 映射的二进制数。

这题最牛的地方来了。

我们不妨去钦定 $1$ 的个数来去掉维护 $0$ 这个带给我们二倍询问常数的东西。

然后注意到 $\binom{12}{6} = 924 < 1000$，$14$ 又超过了询问次数。

又注意到 $\binom{13}{6} = 1716 > 1000$，那不妨将每个数映射到 $\text{popcnt} = 6$ 的 $13$ 位二进制数上。

然后对每个二进制数，把第 $i$ 位为 $1$ 的拿出来拉进 $w_i$ 上。

对于每个位置 $x$，取出 $f(x)$，枚举 $f(x)$ 的每一位 $k$，如果这一位是 $0$ 答案就位或 $w_k$ 的位或和，不妨令这些要位或的 $w_k$ 的并集为 $S$。

首先位置 $x$ 肯定不被包含，因为第 $k$ 位 $x$ 是 $0$ 而 $w_k$ 里的数这一位都是 $1$。

其次所有其它的位置都被包含进 $S$。因为任意 $f(y) \ne f(x)$ 一定至少有一个位是 $1$ 而 $x$ 这一位是 $0$，因为我们钦定了 $1$ 的个数是 $6$，自然这个结论是显然的。

于是只用 $13$ 个询问我们就做完了这道题。

```cpp
#include <bits/stdc++.h>
#define X first
#define Y second
#define rep(i, a, b) for(int i = a; i <= b; i++)
#define pb push_back
using namespace std;
using ld = double;
typedef long long int ll;
using pii = pair<int, int>;
constexpr int maxn = 2e5 + 10, mod = 1e9 + 7;
const ll inf = 1145141919810520L;
int n, p[maxn], b[maxn], a[maxn], tot = 0; ll w[15];
int main() {
	scanf("%d", &n);
	for (int i = 0; i < 1 << 13; i++) {
		b[i] = b[i >> 1] + (i & 1);
		if (b[i] == 6) {
			a[++tot] = i;
			if (tot == n) break;
		}
	}
	for (int i = 0; i < 13; i++) {
		int cnt = 0;
		for (int j = 1; j <= n; j++) if (a[j] >> i & 1) ++cnt;
		if (cnt) {
			printf("? %d ", cnt);
			for (int j = 1; j <= n; j++) if (a[j] >> i & 1) printf("%d ", j);
			puts(""); fflush(stdout);
			scanf("%lld", &w[i]);
		}
	}
	puts("! ");
	for (int x = 1; x <= n; x++) {
		ll ans = 0;
		for (int i = 0; i < 13; i++) if (a[x] >> i & 1 ^ 1) ans |= w[i];
		printf("%lld ", ans);
	}
	puts(""); fflush(stdout);
	return 0;
}
```

---

## 作者：Mirasycle (赞：0)

首先可以**转化一下题意**：每次可以询问一个集合，要求最后对于每一个 $i$ 需满足询问的集合中不含 $i$ 的集合的并集等于全集去掉 $i$。

其实就是一个集合划分问题，再进一步转化一个上面的条件也就是对任意 $(i,j)$ 满足 $j$ 出现在一个不含 $i$ 的集合中。于是我们可以通过元素特征来划分集合。$i$ 和 $j$ 不同当且仅当二者的二进制表示中有一位不同，这启发我们考虑二进制的每一位分别询问下标的当前位为 $0$ 和 $1$ 的元素的集合。但是这样操作次数是 $20$ 次。

如何减少操作次数呢，发现操作次数是等于集合总数的，于是我们可以通过减少集合总数来削减操作次数。在当前的划分方式下 $20$ 个集合确实是必要的，因为只有这样才能区分出那些只有一位不同的数，所以我们可以选择更具有特征性的划分方式。

我们发如果固定 $1$ 的个数这样不需要对于每一位正反查了，因为如果当前位 $i$ 为 $0$ 而 $j$ 为 $1$，那么必然存在另一位使得 $i$ 为 $1$ 而 $j$ 为 $0$，只需要在 $1$ 的位置统计就可以了，这样就不需要正反询问了。

为什么询问次数上限是 $13$ 呢，因为 $C_{12}^i \le C_{12}^6 <1000$，而 $13$ 恰好满足条件。

---

## 作者：Kevin090228 (赞：0)

考虑每个数在哪些询问里面出现了，设这些询问的集合为 $S_i$。

你能判断出来 $p_i$ 的值，其实就是不在 $S_i$ 里的询问覆盖了所有的其他位置。也即，不存在 $i,j$，使得 $i$ 没出现的询问 $j$ 都没出现，或者说 $S_i\sube S_j$。

注意到 $\binom{13}{6}>1.7\times 10^3$，所以 $S_i$ 取互异的大小为 $6$ 的集合即可。



---

