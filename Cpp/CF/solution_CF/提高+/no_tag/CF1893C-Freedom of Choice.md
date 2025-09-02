# Freedom of Choice

## 题目描述

Let's define the anti-beauty of a multiset $ \{b_1, b_2, \ldots, b_{len}\} $ as the number of occurrences of the number $ len $ in the multiset.

You are given $ m $ multisets, where the $ i $ -th multiset contains $ n_i $ distinct elements, specifically: $ c_{i, 1} $ copies of the number $ a_{i,1} $ , $ c_{i, 2} $ copies of the number $ a_{i,2}, \ldots, c_{i, n_i} $ copies of the number $ a_{i, n_i} $ . It is guaranteed that $ a_{i, 1} < a_{i, 2} < \ldots < a_{i, n_i} $ . You are also given numbers $ l_1, l_2, \ldots, l_m $ and $ r_1, r_2, \ldots, r_m $ such that $ 1 \le l_i \le r_i \le c_{i, 1} + \ldots + c_{i, n_i} $ .

Let's create a multiset $ X $ , initially empty. Then, for each $ i $ from $ 1 $ to $ m $ , you must perform the following action exactly once:

1. Choose some $ v_i $ such that $ l_i \le v_i \le r_i $
2. Choose any $ v_i $ numbers from the $ i $ -th multiset and add them to the multiset $ X $ .

You need to choose $ v_1, \ldots, v_m $ and the added numbers in such a way that the resulting multiset $ X $ has the minimum possible anti-beauty.

## 说明/提示

In the first test case, the multisets have the following form:

1. $ \{10, 10, 10, 11, 11, 11, 12\} $ . From this multiset, you need to select between $ 5 $ and $ 6 $ numbers.
2. $ \{12, 12, 12, 12\} $ . From this multiset, you need to select between $ 1 $ and $ 3 $ numbers.
3. $ \{12, 13, 13, 13, 13, 13\} $ . From this multiset, you need to select $ 4 $ numbers.

You can select the elements $ \{10, 11, 11, 11, 12\} $ from the first multiset, $ \{12\} $ from the second multiset, and $ \{13, 13, 13, 13\} $ from the third multiset. Thus, $ X = \{10, 11, 11, 11, 12, 12, 13, 13, 13, 13\} $ . The size of $ X $ is $ 10 $ , the number $ 10 $ appears exactly $ 1 $ time in $ X $ , so the anti-beauty of $ X $ is $ 1 $ . It can be shown that it is not possible to achieve an anti-beauty less than $ 1 $ .

## 样例 #1

### 输入

```
7
3
3 5 6
10 11 12
3 3 1
1 1 3
12
4
2 4 4
12 13
1 5
1
7 1000 1006
1000 1001 1002 1003 1004 1005 1006
147 145 143 143 143 143 142
1
2 48 50
48 50
25 25
2
1 1 1
1
1
1 1 1
2
1
1
1 1 1
1
2
2
1 1 1
1
1
2 1 1
1 2
1 1
2
4 8 10
11 12 13 14
3 3 3 3
2 3 4
11 12
2 2```

### 输出

```
1
139
0
1
1
0
0```

# 题解

## 作者：Alex_Wei (赞：14)

### [CF1893C Freedom of Choice](https://www.luogu.com.cn/problem/CF1893C)

首先算出 $|X|$ 的上下界 $[L, R]$，由于不同的 $a_{i, j}$ 的种类只有 $N = \sum n$ 种，于是若 $R - L + 1 > N$，根据抽屉原理，总能找到 $|X| \in [L, R]$ 使得 $|X|$ 不等于任何 $a_{i, j}$，答案为 $0$。

于是 $R - L + 1 \leq N$，可以直接枚举 $x = |X|$。对第 $i$ 个可重集，我们把不等于 $x$ 的 $a_{i, j}$ 全部选上，设总数为 $s_i$。如果 $s_i < l_i$，说明无论如何都要补充 $l_i - s_i$ 个 $x$ 加入 $X$，然后令 $s_i \gets l_i$。如果 $s_i > r_i$ 则需要令 $s_i\gets r_i$。将 $s_i$ 求和得到 $S$。

如果 $S \geq x$，说明可以丢掉若干个元素（但不能丢掉 $x$，因为这些 $x$ 必须要加）使得 $S = x$。

如果 $S < x$，说明还要加入 $x - S$ 个 $x$：如果还有不等于 $x$ 的 $a_{i, j}$ 没被选，那一定是因为 $s_i > r_i$ 导致的，所以只有等于 $x$ 的 $a_{i, j}$ 能选，且就是因为没选 $a_{i, j} = x$ 导致了 $S < x$。

这样可以算出 $x = |X|$ 时 $X$ 最少有多少个 $x$，将所有 $x\in [L, R]$ 的答案取最小值即可。

为了避免复杂度退化为 $\mathcal{O}(mN)$，枚举 $x$ 时需要快速知道有哪些 $i$ 存在 $j$ 使得 $a_{i, j} = x$，用 `map<long long, vector<int>>` 维护；以及对每个 $i$ 和值 $a_{i, j}$，在 $j$ 未知的情况下求出对应的 $c_{i, j}$，用 `map<pair<int, long long>, long long>` 维护。

时间复杂度线性对数。

```cpp
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using pdi = pair<double, int>;
using pdd = pair<double, double>;
using ull = unsigned long long;

#define ppc(x) __builtin_popcount(x)
#define clz(x) __builtin_clz(x)

bool Mbe;
// mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
mt19937_64 rnd(1064);
int rd(int l, int r) {return rnd() % (r - l + 1) + l;}

constexpr int mod = 998244353;
void addt(int &x, int y) {x += y, x >= mod && (x -= mod);}
int add(int x, int y) {return x += y, x >= mod && (x -= mod), x;}
int ksm(int a, int b) {
  int s = 1;
  while(b) {
    if(b & 1) s = 1ll * s * a % mod;
    a = 1ll * a * a % mod, b >>= 1;
  }
  return s;
}

constexpr int Z = 1e6 + 5;
int fc[Z], ifc[Z];
int bin(int n, int m) {
  if(n < m) return 0;
  return 1ll * fc[n] * ifc[m] % mod * ifc[n - m] % mod;
}
void init_fac(int Z) {
  for(int i = fc[0] = 1; i < Z; i++) fc[i] = 1ll * fc[i - 1] * i % mod;
  ifc[Z - 1] = ksm(fc[Z - 1], mod - 2);
  for(int i = Z - 2; ~i; i--) ifc[i] = 1ll * ifc[i + 1] * (i + 1) % mod;
}

// ---------- templates above ----------

constexpr int N = 1e5 + 5;

ll m, n[N], l[N], r[N], sc[N];
vector<ll> c[N], a[N];
void mian() {
  cin >> m;
  ll suml = 0, sumr = 0, sumn = 0;
  map<ll, vector<int>> mp;
  map<pair<int, ll>, ll> mp2;
  for(int i = 1; i <= m; i++) {
    vector<ll> ().swap(c[i]);
    vector<ll> ().swap(a[i]);
    cin >> n[i] >> l[i] >> r[i], sc[i] = 0;
    sumn += n[i], suml += l[i], sumr += r[i];
    c[i].resize(n[i]);
    a[i].resize(n[i]);
    for(int j = 0; j < n[i]; j++) cin >> a[i][j], mp[a[i][j]].push_back(i);
    for(int j = 0; j < n[i]; j++) cin >> c[i][j], sc[i] += c[i][j];
    for(int j = 0; j < n[i]; j++) mp2[{i, a[i][j]}] = c[i][j];
  }
  if(sumn < sumr - suml + 1) {
    cout << 0 << "\n";
    return;
  }
  ll ans = LONG_LONG_MAX;
  for(ll cnt = suml; cnt <= sumr; cnt++) {
    ll tot = sumr, res = 0;
    vector<int> index = mp[cnt];
    for(int i : index) {
      tot -= r[i];
      ll ctr = sc[i] - mp2[{i, cnt}];
      if(ctr < l[i]) res += l[i] - ctr, ctr = l[i];
      tot += min(ctr, r[i]);
    }
    ans = min(ans, res + max(0ll, cnt - tot));
  }
  cout << ans << "\n";
}


bool Med;
int main() {
  fprintf(stderr, "%.3lf MB\n", (&Mbe - &Med) / 1048576.0);
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int T = 1;
  cin >> T;
  while(T--) mian();
  cerr << 1e3 * clock() / CLOCKS_PER_SEC << " ms\n";
  return 0;
}
```

---

## 作者：未来姚班zyl (赞：5)

#### 前记（没必要看）

我本想多 VP 几场 div3 来磨练一下基本功的，结果同学老是嘲讽我，拉着我来 VP div2 了，~~结果我早早 AK 了，他 D 都没做完~~，趁他还在冲 D 来把这篇题解写了。

## 题目大意

定义一个可重集的冲突值为这个集合的大小在这个集合中出现的次数。

给你 $m$ 个可重集。每个集合有 $n_i$ 种互不相同的元素，第 $j$ 种元素为 $a_{i,j}$，有 $c_{i,j}$ 个，你要从第 $i$ 个集合中选择 $l_i$ 至 $r_i$ 个元素，组成一个新的可重集 $S$。最小化 $S$ 的冲突值。

## 题目分析

诈骗题。一看完这道题可能想了很多方向都没有什么头绪，只能傻傻地先把 $S$ 的大小范围求出来，为 $[\sum l_i,\sum r_i]$。结果居然发现这个范围的大小是不能超过 $\sum n_i$ 的，否则肯定能找到一个大小使得没有这个大小的值出现，直接输出 $0$。

这就引导我们按照这个范围来求解了。

我们考虑枚举 $S$ 的大小，则只需要考虑值为 $|S|$ 的出现次数最少是多少。为此，我们先假设选满，然后想办法把值为 $|S|$ 的数尽量删除。

设第 $i$ 个可重集的大小为 $siz_i$，值为 $|S|$ 的个数为 $C$。则我们至少可以先删 $\min(C,siz_i-r_i)$ 个，并使得 $C=\max(0,C-(siz_i-r_i))$。然后我们还有删 $\min(C,r_i-l_i)$ 个的空间，这两种贡献我们都可以分别用 map 或者直接开数组（所有值减去 $\sum l_i$ 就能用数组存了）记录到对应的值上。

对于枚举的 $|S|$，我们可以在第一种贡献的基础上再最多按第二种贡献删 $\sum r_i-|S|$ 个数，直接计算并对每种 $|S|$ 取最小值即为答案。

复杂度 $O(\sum n_i)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define int ll
#define L x<<1
#define R L|1
#define mid (l+r>>1)
#define lc L,l,mid
#define rc R,mid+1,r
#define OK Ll<=l&&r<=Rr
#define Root 1,1,n
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define pb push_back
#define ull unsigned ll
#define e(x) for(int i=h[x],y=to[i];i;i=nxt[i],y=to[i])
#define E(x) for(auto y:p[x])
#define Pi pair<int,int>
#define ui unsigned ll
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(ll x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
const int N =2e5+5,M=5e6+5,inf=(1LL<<31)-1;
const ll llf=2e18,mod=1e9+7;
using namespace std;
int T=read(),m[N],l[N],r[N],sc[N],n,sm,slen,sl,sr;
struct node{
	int w,k;
};
vector<node>p[N];
unordered_map<int,int>P;
unordered_map<int,int>Q;
signed main(){
	while(T--){
		n=read();
		sm=slen=sl=sr=0;
		rep(i,1,n){
			p[i].clear();
			m[i]=read(),l[i]=read(),r[i]=read(),sc[i]=0;
			sm+=m[i],slen+=r[i]-l[i],sl+=l[i],sr+=r[i];
			rep(j,1,m[i])p[i].pb({read(),0});
			rep(j,0,m[i]-1)p[i][j].k=read(),sc[i]+=p[i][j].k;
		}
		if(slen>=sm){
			cout <<"0\n";
			continue;
		}
		P.clear(),Q.clear();
		rep(i,1,n)E(i){
			if(y.w<sl||y.w>sr)continue;
			int w=max(0LL,y.k-(sc[i]-r[i]));
			P[y.w]+=w;
			w=min(r[i]-l[i],w);
			Q[y.w]+=w;
		}
		int ans=llf; 
		rep(i,sl,sr){
			 ans=min(ans,P[i]-min(Q[i],sr-i));
		}
		cout <<ans<<'\n';
	} 
	return 0;
}
```




---

## 作者：Xy_top (赞：2)

Div2 赛场里只有不到 60 人做出了这题，但这场没打，赛后补题时独立想了出来，太可惜了。

先来考虑最终 ``multiset`` 长度 $len$ 的范围，显然下界就是所有 $l$ 相加，上界就是所有 $r$ 相加。

那么可选的长度个数就是 $r-l+1$ 个，如果这个个数大于了 $\sum n_i$，答案显然为 $0$，因为一定能够找到一个符合要求的长度 $len$ 使得给定的数字中没有一个是 $len$。

问题转化成了 $r-l+1\leq 2\times 10^5$ 的情况，这时便可以枚举 $len$ 来求解。

枚举 $len$ 之后就有一个显然成立的贪心，对于每个不含 $len$ 的 ``multiset``，尽量多选一点，选 $r$ 个，对于每个含 $len$ 的 ``multiset``，尽量不选 $len$，如果选了所有不是 $len$ 仍然无法达到 $l_i$，那么剩下的只能选 $len$。

最后算一下选出的所有元素个数和是否 $\geq len$，如果没有，那么剩下的全选 $len$ 来填满，如果 $>len$ 显然可以随便退掉一点选的就行。

这个时候有人可能就会问了，那你这个不会超时吗？是的，但是对于每个 $len$，只考虑包含 $len$ 的 ``multiset`` 就够了，剩下的可以 $O(1)$，然后在一个含 $len$ 的 ``multiset`` 中找 $len$ 我使用了二分。（主要是太懒不想写预处理了）

具体实现看代码：

```cpp
#include <bits/stdc++.h>
#define For(i, a, b) for (int i = (a); i <= (b); i ++)
#define foR(i, a, b) for (int i = (a); i >= (b); i --)
#define int long long
using namespace std;
int m, cnt, sum, sum1, sum2;
int n[100005], l[100005], r[100005], sz[100005];
int pre[17];
vector <int> x[100005], y[100005];
vector <int> occ[100005];
map <int, int> row;
void clear () {
	For (i, 1, cnt) occ[i].clear ();
	row.clear ();
	cnt = sum = sum1 = sum2 = 0;
	For (i, 1, m) {
		x[i].clear ();
		y[i].clear ();
		x[i].push_back (0);
		y[i].push_back (0);
		n[i] = 0;
		l[i] = 0;
		r[i] = 0;
		sz[i] = 0;
	}
}
int find (vector <int> v, int x) {
	int ret = 1;
	return ret;
}
void solve () {
	cin >> m;
	clear ();
	For (i, 1, m) {
		cin >> n[i] >> l[i] >> r[i];
		sum += n[i];
		sum1 += l[i];
		sum2 += r[i];
		int a;
		For (j, 1, n[i]) {
			cin >> a;
			x[i].push_back (a);
			if (!row[a]) row[a] = ++ cnt;
			occ[row[a] ].push_back (i);
		}
		For (j, 1, n[i]) {
			cin >> a;
			y[i].push_back (a);
			sz[i] += a;
		}
	}
	if (sum < sum2 - sum1 + 1) {
		cout << 0;
		return;
	}
	int ans = 1000000000000000000;
	For (i, sum1, sum2) {
		//sz = i，且不出现 i 这个元素
		if (!row[i]) {
			cout << 0;
			return;
		}
		int x_ = row[i], sum_ = 0, res = 0;
		int extra = 0;
		for (int j : occ[x_]) {
			sum_ += r[j];
			int loc = 1;
			foR (k, 16, 0) if (loc + pre[k] < x[j].size () && x[j][loc + pre[k] ] <= i) loc += pre[k];
			if (sz[j] - y[j][loc] < l[j]) {
				extra += l[j] - sz[j] + y[j][loc];
				res += l[j];
				
			} else res += min (sz[j] - y[j][loc], r[j]);
		}
		res += sum2 - sum_;
		if (res >= i) ans = min (ans, extra);
		else ans = min (ans, i - res + extra);
	}
	cout << ans;
}
signed main () {
	foR (i, 16, 0) pre[i] = 1 << i;
	ios::sync_with_stdio (0);
	int _ = 1;
	cin >> _;
	while (_ --) {
		solve ();
		cout << '\n';
	}
	return 0;
}
```


---

## 作者：Ghosty_Neutrino (赞：0)

## 题意
新定义了一个漂亮集，集有一个值，值的大小等于集的大小在本集合内出现的次数。

输入：有 $m$ 个可重集，每个集合有 $n$ 个不同的元素，每个元素值为 $a_{i,j}$ 有 $c_{i,j}$ 个。每个集合可以选择 $l_i$ 到 $r_i$ 个元素组成一个新集，最小化集的值。

输出：组成的新集集的最小值。
## 分析
设最后组成的新集为 $A$，那么由于 $A$ 会从每一个多重集中取出 $l_i$ 到 $r_i$ 个元素，当 $\sum_{r_i}-\sum{l_i}+1>\sum_{n_i}$ 时，可以选出足够多的数，此时答案为 $0$ 直接输出。

然后从集合 $A$ 的大小入手，设所有的 $l$ 总和为 $suml$，所有的 $r$ 总和为 $sumr$。$suml \le A_size \le sumr$ 枚举 $A$ 集合可以删去的数的多少，则 $A$ 可以删去 $0$ 至 $sumr-suml+1$ 个数，对于删去 $x$ 个数，肯定是优先删去值为 $A_size-x$ 的数，看最后剩的下几个。

注：这里有可能 $x$ 比值为 $A_size-x$ 的数多，所以要判断一下删到 $0$ 就不可以删了。
## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define inf 1e18
using namespace std;
const int M=1000005;
inline int max(int x,int y){return x>y?x:y;}
inline int min(int x,int y){return x>y?y:x;}
int T,n,m;;
int a[M],c[M],lx[M],rx[M];
int sum[M],p[M],rr[M],pos[M];
int st[M];
inline void work(){
    cin>>m;
    int suml=0,sumr=0;
    for(int i=1;i<=m;i++) sum[i]=0;
    for(int i=1;i<=m;i++){
        cin>>n>>lx[i]>>rx[i];
        suml+=lx[i],sumr+=rx[i];
        for(int j=1+pos[i-1];j<=n+pos[i-1];j++)cin>>a[j];
        for(int j=pos[i-1]+1;j<=pos[i-1]+n;j++){
            cin>>c[j];
            sum[i]+=c[j];
        }
        pos[i]=pos[i-1]+n;
    }
    if(sumr-suml+1>pos[m]){
        cout<<0<<"\n";
        return ;
    }
    else{
        int cnt=0;
        for(int i=1;i<=m;i++){
            for(int j=pos[i-1]+1;j<=pos[i];j++){
                if(a[j]>=suml&&a[j]<=sumr&&st[a[j]-suml+1]==0){
                    ++cnt;
                    st[a[j]-suml+1]=1;
                }
            }
        }
        for(int i=1;i<=sumr-suml+1;i++) st[i]=p[i]=rr[i]=0;
        if(sumr-suml+1>cnt){
            cout<<"0"<<"\n";
            return ;
        }
        for(int i=1;i<=m;i++){
            for(int j=pos[i-1]+1;j<=pos[i];j++){
                if(a[j]>=suml&&a[j]<=sumr){
                    int x=sum[i]-c[j];
                    p[a[j]-suml+1]+=max(0,lx[i]-x);
                    rr[a[j]-suml+1]+=rx[i]-min(rx[i],max(x,lx[i]));
                }
            }
        }
        int minn=inf;
        for(int i=1;i<=sumr-suml+1;i++){
            minn=min(minn,p[i]+max(0,i+suml-sumr-1+rr[i]));
        }
        cout<<minn<<"\n";
        return ;
    }
}
signed main(){
    cin>>T;
    while(T--) work();
    return 0;
}
```

---

## 作者：chatoudp (赞：0)

先计算出总的 multiset 大小的上下界：$L,R$，以及数的总种类数：$sum$。

若 $R-L+1>sum$ 则答案为 $0$，因为你只需选一个在所有 multiset 中均未出现过的数作为长度，在满足题目要求的情况下随便选，即可使答案为 $0$。

但若 $R-L+1\le sum$，则我们考虑枚举长度。先把所有数都选上，在删数，尽可能多删为长度的数。先每个 multiset 中选上的数删到 $r_i$ 个数，其中能删几个为长度的数，就删几个。而所有的 $r_i$ 的总和是不一定等于长度的，所以还要进行第二轮删数。也是尽可能删为长度的数。

我们可以先预处理经过各种长度在第一轮删数后为长度的数长度剩余几个，以及第二轮删数可以再删掉几个为长度的数，这样答案就很好算了。

AC 代码：


```cpp

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#include <ext/pb_ds/priority_queue.hpp>
#define I return
#define AK 0
#define IOI ;
#define itn int
#define Please int
#define AC main(){
#define pritnf printf
using namespace std;
typedef long long ll;
int T,m;
ll n[100005],l[100005],r[100005],suml,sumr,sumn;
ll N[100005];
map<ll,ll> a[100005],c[100005]; 
map<ll,ll> s,ks;//s表示第一轮删后剩几个为长度的数，ks表示第二轮还能删几个
Please AC//'_' T_T ^_^
	scanf("%d",&T);
	while(T--){
		scanf("%d",&m);
		suml=sumr=sumn=0;
		for(int i=1;i<=m;i++){
			scanf("%lld%lld%lld",&n[i],&l[i],&r[i]);
			ll x;
			N[i]=0;
			for(int j=1;j<=n[i];j++) scanf("%lld",&x),a[i][j]=x;
			for(int j=1;j<=n[i];j++) scanf("%lld",&x),c[i][j]=x,N[i]+=c[i][j];
			sumn+=n[i]; suml+=l[i]; sumr+=r[i];
		}
		if(sumr-suml+1>sumn){
			printf("0\n");
			continue;
		}
		for(ll i=1;i<=m;i++)
			for(int j=1;j<=n[i];j++) s[a[i][j]]+=c[i][j]-min(N[i]-r[i],(ll)c[i][j]),ks[a[i][j]]+=min(r[i]-l[i],c[i][j]-min(N[i]-r[i],(ll)c[i][j]));
		ll minn=0x7f7f7f7f7f7f7f7f;
		for(ll i=suml;i<=sumr;i++)
			minn=min(minn,s[i]-min(sumr-i,(ll)ks[i]));
		printf("%lld\n",minn);
		s.clear(); ks.clear();
	}
	I AK IOI
}

```

---

## 作者：Gmt丶FFF (赞：0)

首先有一个很暴力的想法：我们枚举每一个数字 $x$，让最终选的数字数量等同于 $x$，使 $x$ 选的尽量少。

这个问题我们只需要每次对所有多重集选除 $x$ 外的所有数，如果选的数仍然小于 $l$ 那再选 $x$，选完所有多重集后，如果选的数仍然数量小于 $x$，那么剩下的数我们明显都只能选 $x$ 了，如果大于等于了 $x$，那么答案就是我们已经选了的 $x$ 的个数。

当然，当 $\sum l_i\le x\le \sum r_i$ 时以上结论才成立，否则这个数不可能作为答案出现。

现在问题在于，如果一个集合没有 $x$，我们还要将强制选上 $r$ 个，这样时间复杂度会退化到  $O(nm)$。

这个问题也很好解决，我们不记录我们总共选了多少个，而是记录我们会少选多少个数字，因为只有当 $x$ 出现在一个集合时才会出现我不选 $r$ 个的可能性。

那么我们就用 map 来记录我们选了多少个 $x$ 和在尽量少选 $x$ 的可能下最少少选了几个数，最后枚举 $\sum l_i$ 到 $\sum r_i$ 的所有数字的贡献即可，如果一个数在这区间没有出现，明显答案就为 $0$，此时可以跳出枚举，这样保证枚举数量为 $O(n)$。

时间复杂度：$O((n+m)\log n)$。

vp 时脑子抽了，没想到特判 $\sum r_i>10^{17}$ 答案就为 $0$，害的打了 __int128，又懒得写哈希函数，就用了 map，如果加了特判改成 long long 还可以用 unordered_map，复杂度可以提到 $O(n+m)$。

```cpp
#include<iostream>
#include<cstdio>
#include<map>
#define int __int128
#define pii pair<int,int> 
using namespace std;
int cnwr,wr[40];
inline int read()
{
	char ch=getchar();
	int sum=0;
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9')sum=(sum<<1)+(sum<<3)+(ch^48),ch=getchar();
	return sum;
}
inline void write(int x)
{
	if(x==0)putchar('0');
	while(x)wr[++cnwr]=x%10,x/=10;
	while(cnwr)putchar(wr[cnwr--]^48);
}
map<int,int>f1,f2,f3;
const int N=1e5+5;
int m,len[N],ll[N],rr[N],a[N],c[N];
signed main()
{
	int T;
	T=read();
	while(T--)
	{
		f1.clear();
		f2.clear();
		f3.clear();
		m=read();
		int tot=0,tot2=0;
//		bool flag=1;
		for(int i=1;i<=m;i++)
		{
			len[i]=read(),ll[i]=read(),rr[i]=read();
			int sum=0;
			for(int j=1;j<=len[i];j++)a[j]=read(),f3[a[j]]=1;
			for(int j=1;j<=len[i];j++)c[j]=read(),sum+=c[j];
			for(int j=1;j<=len[i];j++)
			{
				int num=max((__int128)0,(ll[i]-(sum-c[j])));
				f1[a[j]]+=num;
				f2[a[j]]-=rr[i]-min(rr[i],max(ll[i],sum-c[j]));
			}
			tot+=rr[i];
			tot2+=ll[i];
//			if(rr[i]>1e17)
//			{
//				flag=0;
//				break;
//			}
		}
//		if(!flag)
//		{
//			putchar('0');
//			putchar('\n');
//			continue;
//		}
		int ans=1e18;
		for(int i=tot2;i<=tot;i++)
		{
			if(!f3[i])
			{
				ans=0;
				break;
			}
			int x=i,y=f1[i];
			int num=-f2[x];
			if(tot-num>=x)ans=min(ans,y);
			else ans=min(ans,y+x-(tot-num));
		}
		write(ans);
		putchar('\n');
	}
	return 0;
}
```


---

