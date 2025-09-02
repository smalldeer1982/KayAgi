# Inversion Composition

## 题目描述

[My Chemical Romance - Disenchanted](https://youtu.be/j_MlBCb9-m8)

ඞ



You are given a permutation $ p $ of size $ n $ , as well as a non-negative integer $ k $ . You need to construct a permutation $ q $ of size $ n $ such that $ \operatorname{inv}(q) + \operatorname{inv}(q \cdot p) = k {}^\dagger {}^\ddagger $ , or determine if it is impossible to do so.

 $ {}^\dagger $ For two permutations $ p $ and $ q $ of the same size $ n $ , the permutation $ w = q \cdot p $ is such that $ w_i = q_{p_i} $ for all $ 1 \le i \le n $ .

 $ {}^\ddagger $ For a permutation $ p $ of size $ n $ , the function $ \operatorname{inv}(p) $ returns the number of inversions of $ p $ , i.e. the number of pairs of indices $ 1 \le i < j \le n $ such that $ p_i > p_j $ .

## 说明/提示

In the first test case, we have $ q \cdot p = [2, 1, 3] $ , $ \operatorname{inv}(q) = 3 $ , and $ \operatorname{inv}(q \cdot p) = 1 $ .

In the fourth test case, we have $ q \cdot p = [9, 1, 8, 5, 7, 6, 4, 3, 2] $ , $ \operatorname{inv}(q) = 24 $ , and $ \operatorname{inv}(q \cdot p) = 27 $ .

## 样例 #1

### 输入

```
5
3 4
2 3 1
5 5
2 3 5 1 4
6 11
5 1 2 3 4 6
9 51
3 1 4 2 5 6 7 8 9
1 0
1```

### 输出

```
YES
3 2 1
NO
NO
YES
1 5 9 8 7 6 4 3 2
YES
1```

# 题解

## 作者：Liar_Dancer (赞：5)

设 $pos_i$ 表示排列 $p$ 中值为 $i$ 的**位置**。

若排列 $q$ 中有 $i<j,q_i<q_j$，且排列 $p$ 中有 $pos_j<pos_i$，因为 $p_{pos_i}=i$，故 $q_{p_{pos_j}}=q_j>q_i=q_{p_{pos_i}}$。

这里 $i,j$ 与 $pos_j,pos_i$ 构成**双射**，且其在排列 $q$ 与排列 $q \cdot p$ 中对应的值大小关系**不同**，于是可得，排列 $p$ 中的一个逆序对会使答案**恰好**增加 $1$。

同理可得，排列 $p$ 中的顺序对会使答案增加 $0$ 或 $2$。

于是，先求出 $p$ 中的逆序对数并将其从 $k$ 中减去，剩下 $k$ 的值若为奇数，小于 $0$，或大于顺序对数的两倍则无解，否则一定可以构造出一组解。

有解的情况，考虑贪心构造方案，对于 $q$ 中每个位置 $i$，预处理出 $p$ 中 $pos_i$ 的顺序对数，记为 $w_i$。

为方便叙述，之后的 $k$ 均为减去逆序对数后除以二的值。

从左向右贪心构造，设当前未使用数的最大值为 $Max$，若当前的 $i$ 满足 $w_i \leq k$，则使 $q_i=Max$；否则，使 $q_i=Max-(w_i-k)$，并找到 $p$ 中以 $pos_i$ 作开头的顺序对位置，倒序填上当前 $Max$。最后顺序将还没有值的位置填上当前最小值即可。

场上的代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 1000010
#define int long long
#define pii pair<int,int>
#define st first
#define ed second
#define mkp make_pair
#define pb push_back
#define eps 1e-12
#define mod 998244353
#define INF 0x3f3f3f3f
#define il inline
#define vi vector<int>
#define ins insert
#define umap unordered_map
#define uset unordered_set
il int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
int T=1,n,m,k;
int p[N],q[N],t[N];
il int lowbit(int x){
	return x&(-x);
}
il void upd(int x){
	for( ;x<=n;x+=lowbit(x))
		t[x]++;
}
il int query(int x){
	int ans=0;
	for( ;x>=1;x-=lowbit(x))
		ans+=t[x];
	return ans;
}
int w[N],vis[N];
il void solve(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++)
		t[i]=p[i]=q[i]=0;
	for(int i=1;i<=n;i++)
		scanf("%lld",&p[i]);
	int cnt=0;
	for(int i=n;i>=1;i--){
		cnt+=query(p[i]);
		w[p[i]]=n-i-query(p[i]);
		upd(p[i]);
	}
	m-=cnt;
	if(m<0||m%2==1||m>(n*(n-1)/2-cnt)*2){
		puts("NO");
		return ;
	}
	m>>=1;
	for(int i=1;i<=n;i++)
		vis[i]=0;
	int now=n;
	for(int i=1;i<=n;i++){
		if(m>=w[i]){
			q[i]=now;
			vis[now]=1;
			while(vis[now])now--;
			m-=w[i];
		}
		else{
			int pos=0;
			for(int j=1;j<=n;j++)
				if(p[j]==i){
					pos=j;
					break;
				}
			vector<int> v;
			for(int j=pos+1;j<=n;j++)
				if(p[j]>i)v.pb(p[j]);
			q[i]=now-(w[i]-m);
			while(vis[now])now--;
			vis[now-(w[i]-m)]=1;
			int len=v.size();
			for(int j=len-1;j>=0;j--){
				while(vis[now])now--;
				q[v[j]]=now;
				vis[now]=1;
			}
			for(int j=n;j>=1;j--){
				if(!q[j]){
					while(vis[now])now--;
					q[j]=now;
					vis[now]=1;
				}
			}
			break;
		}
	}
	puts("YES");
	for(int i=1;i<=n;i++)
		printf("%lld ",q[i]);
	puts("");
}
signed main(){
	scanf("%lld",&T);
	while(T--)solve();
	return 0;
}

```

---

## 作者：ReTF (赞：4)

一道好题。

题目给的条件难以直接刻画，考虑计算元素对 $(q_i,q_j)$ 对逆序对个数总和 $k$ 的贡献。

以下记 $d_i=i$，$p^I\cdot p=d$。

- 若 $p^I_i<p^I_j$ 且 $q_i<q_j$，则 $(q_i,q_j)$ 对 $k$ 有 $0$ 的贡献。
- 若 $p^I_i<p^I_j$ 且 $q_i>q_j$，则 $(q_i,q_j)$ 对 $k$ 有 $2$ 的贡献。
- 若 $p^I_i>p^I_j$ 且 $q_i<q_j$，则 $(q_i,q_j)$ 对 $k$ 有 $1$ 的贡献。
- 若 $p^I_i>p^I_j$ 且 $q_i>q_j$，则 $(q_i,q_j)$ 对 $k$ 有 $1$ 的贡献。

可见对于排列 $p^I$ 中的一对逆序对 $i<j,p^I_i>p^I_j$ 对 $k$ 一定有 $1$ 的贡献。将 $k$ 减去 $p^I$ 中的逆序对数量再除以 $2$，得到的就是满足  $p^I_i<p^I_j$ 且 $q_i>q_j$ 的 $(i,j)$ 对数 $r$。

考虑构造答案。对于每个 $i$ 求出 $s_i=\sum_{j=1}^{i-1}[p^I_j<p^I_i]$。从 $n$ 到 $1$ 遍历序列，将 $q_i$ 依次设置为 $1,2,3,\dots$。每次设置都对 $r$ 有 $s_i$ 的削减。重复此操作直到对于某个 $x$ 有 $r<s_x$。

然后，从 $x$ 到 $1$ 遍历序列，将 $q_i$ 依次设置为 $n,n-1,n-2,\dots$ 直到 $1$ 到 $x-1$ 中所有 $p^I_i$ 比 $p^I_x$ 小的 $i$ 中恰有 $r$ 个被遍历到。

最后再把剩下的权值从小到大从前到后填入 $q$ 即可构造出序列 $q$。

无解情况就是 $k$ 和 $p^I$ 中的逆序对数量模 $2$ 不同余，或者到最后了 $r$ 还没有分完。

时间复杂度 $O(n\log n)$，瓶颈在于求逆序对。

[代码](https://codeforces.com/contest/1951/submission/255475618)

---

## 作者：MaxBlazeResFire (赞：2)

记 $w_i=q_{p_i}$。考察 $(q_{p_i}=w_i=x,q_{p_j}=w_j=y)$ 这一对数；如果 $(i,j)$ 在 $p$ 中形成顺序对（$i<j$ 且 $p_i<p_j$），那么对答案贡献为 $0$ 或 $2$，取决于 $(x,y)$ 这对数在 $q,w$ 中的前后位置关系（在 $q,w$ 中是相同的）。如果在 $(i,j)$ 在 $p$ 中形成逆序对，那么 $(x,y)$ 这对数在 $q,w$ 中的位置关系一定不同，也即形成 $1$ 的贡献。

那么实际上，我们只需要构造一个排列 $w$，使得恰好有 $c$ 个 $p$ 中顺序对 $(i,j)$，在 $w$ 中满足 $w_i>w_j$。考虑一种构造，记 $f_i$ 表示 $p$ 中前 $i$ 个数的顺序对个数，我们找到一个最大的 $v$ 使得 $f_v\leq c$，那么我们从值域上拿出一个长度为 $v$ 的子序列，从大到小放在前 $v$ 个数；然后我们不妨可以让第 $v+1$ 个数与前 $v$ 个数形成 $c-f_v$ 个逆序对，也即我们实际上选取 $x=c-f_v$，然后找最开头的 $pos$ 个位置使得出现 $x$ 个与 $v+1$ 形成顺序对的数，然后把 $[v+1,v,v-1,\cdots,v-pos+2]$ 放在开头，然后放 $[v-pos,v-pos-1,\cdots,1]$，然后放 $v-pos+1$，然后 $[v+2,v+3,...,n]$ 放在后面可以不造成任何贡献，这样我们就构造出了 $w$。

复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
#define MAXN 300005

int n,k,p[MAXN],q[MAXN],w[MAXN],f[MAXN],g[MAXN],tr[MAXN + 5];

inline void add( int x , int k ){ for( ; x <= MAXN ; x += x & -x ) tr[x] += k; }
inline int sum( int x ){ int ret = 0; for( ; x ; x -= x & -x ) ret += tr[x]; return ret; }

inline void solve(){
	scanf("%lld%lld",&n,&k);
	for( int i = 1 ; i <= n ; i ++ ) scanf("%lld",&p[i]);
	for( int i = 1 ; i <= n ; i ++ ) f[i] = i - 1 - sum( p[i] ),g[i] = sum( p[i] - 1 ),add( p[i] , 1 );
	for( int i = 1 ; i <= n ; i ++ ) add( p[i] , -1 );
	for( int i = 1 ; i <= n ; i ++ ) f[i] += f[i - 1],g[i] += g[i - 1];
	k -= f[n]; if( k < 0 || k % 2 || k > ( n * ( n - 1 ) - 2 * f[n] ) ){ puts("NO"); return; } 
	k /= 2; int v = n;
	for( int i = 1 ; i < n ; i ++ ) if( g[i] <= k && g[i + 1] >= k ){ v = i; break; }
	int x = k - g[v];
	int cnt = 0,pos = 0;
	while( cnt < x ) pos ++,cnt += p[pos] < p[v + 1];
	x = pos;
	for( int i = 1 ; i <= x ; i ++ ) w[i] = v - i + 2;
	for( int i = x + 1 ; i <= v ; i ++ ) w[i] = v - i + 1;
	w[v + 1] = v - x + 1;
	for( int i = v + 2 ; i <= n ; i ++ ) w[i] = i;
	for( int i = 1 ; i <= n ; i ++ ) q[p[i]] = w[i];
	puts("YES");
	for( int i = 1 ; i <= n ; i ++ ) printf("%lld ",q[i]); puts("");
}

signed main(){
	int testcase; scanf("%lld",&testcase);
	while( testcase -- ) solve();
	return 0;
}
```

---

## 作者：HHH6666666666 (赞：2)

$q \cdot p$ 这个运算十分抽象，导致我们不好直接从整体上考虑变换后的排列。令排列 $r=q \cdot p$，不妨分别考虑 $q$ 中**每一对数**在 $r$ 中的贡献。

令 $pos_i$ 表示 $i$ 在 $p$ 中出现的位置，即 $p_{pos_i}=i$。则有 $r_{pos_i}=q_i$，进一步对于任意 $i \ne j$，$q_i$ 在 $r$ 中出现在 $q_j$ 前当且仅当 $pos_i < pos_j$。

那么对于所有数对 $(i,j), 1 \le i < j \le n$，观察 $(q_i,q_j)$ 及对应的 $(r_{pos_i},r_{pos_j})$，自然想到有以下四种情况：

1. 若 $q_i < q_j,pos_i<pos_j$，此时在 $q,r$ 中的两对数皆非逆序对，总体贡献为 $0$。

2. 若 $q_i<q_j,pos_i>pos_j$，此时 $(q_i,q_j)$ 非逆序对。然而由于 $r_{pos_i}=q_i<r_{pos_j}=q_j$ 且 $pos_i>pos_j$，$(r_{pos_i},r_{pos_j})$ 为逆序对，总体贡献为 $1$。

3. 若 $q_i>q_j,pos_i<pos_j$，此时 $q,r$ 中皆为逆序对，总体贡献为 $2$。

4. 若 $q_i>q_j,pos_i>pos_j$，此时 $q$ 中为逆序对而 $r$ 中非逆序对，总体贡献为 $1$。

总结：令 $i<j$。当 $pos_i<pos_j$ 时，$(q_i,q_j)$ 若为逆序对则总体贡献为 $2$，否则为 $0$。而当 $pos_i>pos_j$ 时无论 $q_i,q_j$ 大小关系如何其总体贡献均为 $1$。注意 $pos_i>pos_j$ 等价于 $i,j$ 两个值在 $p$ 中为逆序对。

到这里做法就很清晰了。

最终逆序对数 $tot$ 奇偶性一定与 $\operatorname{inv}(p)$ 相同且必有 $tot \ge \operatorname{inv}(p)$，否则无解。当然 $tot$ 太大也无解。

于是题目现在变为：构造 $q$ 使 $\sum\limits_{i<j}[(q_i>q_j)\bigwedge(pos_i<pos_j)]=k$，$k$ 为一定值（$\frac{tot-\operatorname{inv}(p)}{2}$）。

构造的细节有点多很容易挂。以下是本人赛时构造方法。

从左到右遍历 $p$，假设当前在 $i$，还需构造 $k$ 个逆序对。

若 $p$ 中在 $i$ 后方且小于 $p_i$ 的数有 $< k$ 个，则将 $q_{p_i}$ 赋为当前最大值（也就是维护一个变量 $t$ 初值为 $n$，每次 `q[p[i]] = t--`）。

若有 $\ge k$ 个则先把 $<p_i$ 且没放数的位置都从小到大（确保不会产生额外逆序对），然后再合理分配一下使得 $q_{p_i}$ 正好为后面位置中的 $k+1$ 大即可。有点难表述可以看代码。注意细节。

```cpp
#include<bits/stdc++.h>
#define ll long long

using namespace std;

const int MAXN = 3e5 + 10;

ll n, k;
struct Fwt {
    int a[MAXN];
    #define lowbit(x) ((x) & (-(x)))
    void add(int x, int k) {
        for (int i = x; i <= n; i += lowbit(i)) a[i] += k;
        return;
    }
    int query(int x) {
        int res = 0;
        for (int i = x; i; i -= lowbit(i)) res += a[i];
        return res;
    }
    void clear() {
        for (int i = 1; i <= n; ++i) a[i] = 0;
        return;
    }
    void set() {
        clear();
        for (int i = 1; i <= n; ++i) add(i, 1);
        return;
    }
} tr;
int p[MAXN];
int w[MAXN];

void solve() {
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) cin >> p[i];
    tr.set();
    ll raw = 0;
    for (int i = 1; i <= n; ++i) {
        tr.add(p[i], -1);
        raw += tr.query(p[i]);
    }
    ll delta = k - raw;
    if (raw > k || (delta & 1)) {
        cout << "NO" << endl;
        return;
    }
    delta /= 2;
    tr.set();
    for (int i = 1; i <= n; ++i) w[i] = 0;
    int now = n, l = 0;
    for (int i = 1; i <= n; ++i) {
        tr.add(p[i], -1);
        int cnt = tr.query(n) - tr.query(p[i]);
        if (cnt <= delta && delta) delta -= cnt, w[p[i]] = now--;
        else {
            // 注意这部分的构造
            for (int j = 1; j < p[i]; ++j)
                if (!w[j]) w[j] = ++l;
            for (int j = p[i] + 1; j <= n; ++j) {
                if (tr.query(j) - tr.query(j - 1)) {
                    // 若 j 在位置 i 后方出现
                    if (delta) --delta, w[j] = ++l;
                }
            }
            // 填完记得退出
            break;
        }
    }
    if (delta) {
        cout << "NO" << endl;
        return;
    }
    cout << "YES" << endl;
    for (int i = 1; i <= n; ++i)
        if (!w[i]) w[i] = ++l;
    for (int i = 1; i <= n; ++i) cout << w[i] << ' ';
    cout << endl;
    return;
}

signed main() {
    ios:: sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}

```

---

## 作者：OrezTsim (赞：1)

令 $w_i=q_{p_i}$。

令 $pos_i$ 表示 $i$ 在 $p$ 中出现的位置，即 $p_{pos_i}=i$，则 $w_{pos_i}=q_i$。

那么现在需要计算 $\operatorname{inv}(q)+\operatorname{inv}(w)$。

钦定 $1 \le i < j \le n$，计算每一对 $(i,j)$ 的可能贡献。

- $q_i<q_j$ 且 $pos_i<pos_j$，则对 $\operatorname{inv}(q)$ 贡献 $0$，对 $\operatorname{inv}(w)$ 贡献 $0$，总贡献 $0$。
- $q_i<q_j$ 且 $pos_i>pos_j$，则对 $\operatorname{inv}(q)$ 贡献 $0$，对 $\operatorname{inv}(w)$ 贡献 $1$，总贡献 $1$。
- $q_i>q_j$ 且 $pos_i<pos_j$，则对 $\operatorname{inv}(q)$ 贡献 $1$，对 $\operatorname{inv}(w)$ 贡献 $1$，总贡献 $2$。
- $q_i>q_j$ 且 $pos_i>pos_j$，则对 $\operatorname{inv}(q)$ 贡献 $1$，对 $\operatorname{inv}(w)$ 贡献 $0$，总贡献 $1$。

观察到 $pos_i>pos_j$ 时其贡献必定为 $1$，这部分贡献总和为 $\operatorname{inv}(p)$。

剩下的 $pos_i<pos_j$ 的情况造成的贡献一定是 $2$ 的倍数。

所以 $\operatorname{inv}(p)>k,k-\operatorname{inv}(p) \equiv 1(\bmod \space 2)$ 或 $\operatorname{inv}(p)+2(\dfrac{n(n-1)}{2}-\operatorname{inv}(p))<k$ 时一定无解。

不妨令 $k \leftarrow \dfrac{k-\operatorname{inv}(p)}{2}$。

因为只需要考虑 $pos_i<pos_j$ 的情况，所以现在可以枚举 $i \in [1,n]$，也即 $pos_{p_i} \in [1,n]$。

考虑初始维护一个值 $v=n$。如果当前枚举到一个 $p_i$ 并且操作后累加的答案不超过 $k$，那么就 $q_{p_i} \leftarrow v$，随后 $v$ 减去 $1$。

如果当前枚举到的 $p_i$ 赋上 $v$ 的值后累加的答案超过了 $k$，那么可以先按 $j$ **从小到大**消除 $\forall j<p_i$ 的 $q_j$ 的影响，即维护一个值 $v'=1$，那么 $q_j \leftarrow v'$，随后 $v'$ 加上 $1$。

接着，按 $j$ **从小到大**加上 $\forall j>p_i$ 的 $q_j$ 的影响，即 $q_j \leftarrow v'$，随后 $v'$ 加上 $1$，$k$ 减去 $1$，$k=0$ 时停止，最后 $q_{p_i}=v'$ 把贡献拿到，剩下的再从小到大赋值即可。

细节可以推一下，应该有其他构造方法，反正只要保证其他数不影响你构造的部分的贡献即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N=3e5+10;
int n,k,p[N],r[N],res[N];

namespace BIT {
    #define lb(x) (x&-x)
    int t[N]; void cl() { fill(t+1,t+1+n,0); }
    void upd(int x,int v) { for(;x<=n;x+=lb(x)) t[x]+=v; }
    auto qry(int x,int v=0) -> int { for(;x;x-=lb(x)) v+=t[x]; return v; }
}

using BIT::cl;
using BIT::upd;
using BIT::qry;

void solve() {
    cin>>n>>k; cl();
    for(int i=1;i<=n;++i) cin>>p[i];
    int inv=0;
    for(int i=1;i<=n;++i) inv+=i-1-qry(p[i]),upd(p[i],1);
    if(inv>k||(k-inv)&1) return cout<<"NO\n",void();
    int ver=n*(n-1)/2-inv;
    if(inv+ver*2<k) return cout<<"NO\n",void();
    k=(k-inv)>>1;
    int tmp=n,now=1,cur=1;
    for(int i=1;i<=n;++i) {
        upd(p[i],-1);
        int lst=n-i-qry(p[i]);
        if(lst<=k&&k) {
            k-=lst,res[p[i]]=tmp--;
            continue;
        }
        for(int j=1;j<p[i];++j)
            if(!res[j]) res[j]=now++;
        for(int j=p[i]+1;j<=n;++j)
            if(qry(j)-qry(j-1)&&k) --k,res[j]=now++;
        cur=p[i]; break;
    }
    if(k) return cout<<"NO\n",void();
    for(int i=cur;i<=n;++i)
        if(!res[i]) res[i]=now++;
    cout<<"YES\n";
    for(int i=1;i<=n;++i) cout<<res[i]<<' ';
    cout<<'\n';
    fill(res+1,res+1+n,0);
}

auto main() -> signed {
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int T; cin>>T;
    while(T--) solve();
    return 0;
}
```

---

## 作者：wosile (赞：1)

赛时 2:58/3:00 非常惊险的通过了这题，用时 45min，感觉完全没有 2F/1D 该有的难度。

对于一对 $q$ 中的元素 $(q_i,q_j)(i<j)$，它有两次对总逆序对数量造成贡献的机会：一次是在 $q$ 中，一次是在 $q\cdot p$ 中。

考虑一个 $p$ 中的逆序对 $p_i>p_j(i<j)$，在 $q$ 中 $q_{p_j}$ 在 $q_{p_i} $ 的前面，在 $q\cdot p$ 中 $q_{p_j}$ 在 $q_{p_i} $ 的后面，因此无论 $q_{p_i}$ 和 $q_{p_j}$ 的大小关系如何，$(q_{p_i},q_{p_j})$ 都一定会在 $q$ 和 $q \cdot p$ 中的恰好一个排列中成为逆序对。

假如是顺序对 $p_i<p_j$，两个排列中 $q_{p_i}$ 都在 $q_{p_j}$ 前面，因此如果 $q_{p_i}<q_{p_j}$，则不会成为逆序对，否则会在两个排列中都成为逆序对，造成 $2$ 的贡献。

形式化地，记 $\text{inv}_p(q)=\sum\limits_{i=1}^n\sum\limits_{j=i+1}^{n}[p_i<p_j\land q_{p_i}>q_{p_j}]$，那么实际上就有 $\text{inv}(q)+\text{inv}(q\cdot p)=\text{inv}(p)+2\text{inv}_p(q)=k$。也就是说，我们需要构造出排列 $q$ 使得 $\text{inv}_p(q)=\dfrac{k-\text{inv}(p)}{2}$。

可以发现，$p_i=i$ 时，$\text{inv}(q)=\text{inv}_p(q)$。

**以下只是一种可能的构造，构造合法的 $\text{inv}_p(q)=\dfrac{k-\text{inv}(p)}{2}$ 有很多种方式，这里使用这样的构造只是因为我自己是这么写的。**

先考虑怎么构造一个排列 $r$ 使得 $\text{inv}(r)=c$，考虑从前往后构造 $r$。注意到每次加入 $r_i$ 时，我们可以任意决定有多少个 $j<i$ 构成 $(r_j,r_i)$ 的逆序对，那么每一位尽可能让逆序对最多的构造就可以了。

例如 $c=12$，我们可以构造一个 $r=(6,5,3,2,1,4,7,8,9,10,11,\cdots)$。实现上，我们可以找到 $c$ 的逆序对额度被用完的位置（也就是这个 $r_6$），然后就很好构造了。

构造 $\text{inv}_{t}(r)=c$ 其实也是一样的，注意枚举的顺序是 $r_{t_1},r_{t_2},r_{t_3},\cdots$ 而不是 $r_1,r_2,r_3,\cdots$。仍然每一位让逆序对尽可能大，直到逆序对额度被用完为止，只不过我们需要用树状数组来维护 $t_i$ 有多少个顺序对 $t_j<t_i(j<i)$，因为只有在 $t$ 是顺序对的位置，$q_{t_i}$ 才有有效的逆序对。

然后这题就结束了，注意判断无解的情况。

时间复杂度 $O(\sum n \log n)$，代码非常好写，也很清晰。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int p[300005];
int c[300005];
int n;
ll k;
void upd(int x,int val){
    for(;x<=n;x+=(x&-x))c[x]+=val;
}
int query(int x){
    int ans=0;
    for(;x;x-=(x&-x))ans+=c[x];
    return ans;
}
int q[300005];
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d%lld",&n,&k);
        for(int i=1;i<=n;i++)scanf("%d",&p[i]);
        for(int i=1;i<=n;i++)c[i]=0;
        ll invp=0;
        for(int i=1;i<=n;i++){
            invp+=query(n)-query(p[i]);
            upd(p[i],1);
        }
        if((k-invp)%2==1 || k<invp){
            printf("NO\n");
            continue;
        }
        k=(k-invp)/2;
        for(int i=1;i<=n;i++)c[i]=0;
        int div=-1;
        int fl=0;
        for(int i=1;i<=n;i++){
            int x=query(p[i]);
            if(k>x)k-=x;
            else{
                fl=1;
                int pos=1;
                while(k>0){
                    k-=(p[pos]<p[i]);
                    ++pos;
                }
                for(int j=1;j<pos;j++)q[p[j]]=i-j+1;
                for(int j=pos;j<i;j++)q[p[j]]=i-j;
                q[p[i]]=i-pos+1;
                for(int j=i+1;j<=n;j++)q[p[j]]=j;
                break;
            }
            upd(p[i],1);
        }
        if(k){
            printf("NO\n");
            continue;
        }
        printf("YES\n");
        for(int i=1;i<=n;i++)printf("%d ",q[i]);
        printf("\n");
    }
    return 0;
	//quod erat demonstrandum
}
```

---

## 作者：Caiest_Oier (赞：0)

# [CF1951F](https://www.luogu.com.cn/problem/CF1951F)    

把式子写清楚，就是要你构造一个排列 $q$，满足 $\sum_{i=1}^{n}\sum_{j=i+1}^{n}[q_i>q_j]+[q_{p_i}>q_{p_j}]=k$。     

令 $invp_{p_i}=i$，即 $p$ 的逆排列。对于一对 $(i,j)$ 满足 $i<j$，如果 $invp_i>invp_j$，则其贡献固定为 $1$，否则如果 $q_i<q_j$，贡献为 $0$，$q_i>q_j$，贡献为 $2$。这里大概的思路就是把两种逆序对的求和方式做一个匹配，对于 $invp_i>invp_j$ 的对，则两边必定恰有一个满足，否则要么两个都不满足或都满足（可能有点抽象但是我也不知道该怎么表达了）。     

对于贡献固定为 $1$ 的对，可以通过计算逆序对的方式把这部分贡献减掉。如果剩下的 $k$ 不是偶数，则必定无解。否则从前往后构造，每次加入的 $q$ 都是最小的，贡献最多的逆序对。如果 $k$ 比这些逆序对少，则将当前元素适当升高，把 $k$ 减到 $0$，后面全部往大了加，不贡献逆序对即可。如果最后 $k>0$ 则还是无解，否则输出答案即可。    

代码：   

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,k,p[1000003],invp[1000003],q[1000003],lft,rgt;
int lowbit(int X){return (X&(-X));}
class BIT{
    public:
        int TreeAr[1000003];
        void modify(int wz,int val){
            wz++;
            for(int i=wz;i<=1000000;i+=lowbit(i))TreeAr[i]+=val;
            return;
        }
        int Query(int l,int r){
            l++;
            r++;
            int ret=0;
            for(int i=r;i;i-=lowbit(i))ret+=TreeAr[i];
            for(int i=l-1;i;i-=lowbit(i))ret-=TreeAr[i];
            return ret;
        }
}T;
int stk[500003],tot;
signed main(){
    ios::sync_with_stdio(false);
    cin>>t;
    while(t--){
        cin>>n>>k;
        for(int i=1;i<=n;i++){
            cin>>p[i];
            invp[p[i]]=i;
        }
        for(int i=0;i<=n+10;i++)T.TreeAr[i]=0;
        for(int i=1;i<=n;i++){
            k-=T.Query(invp[i]+1,n);
            T.modify(invp[i],1);
        }
        if(k<0||k%2!=0){
            cout<<"NO\n";
            continue;
        }
        k/=2;
        for(int i=0;i<=n+10;i++)T.TreeAr[i]=0;
        T.modify(invp[1],1);
        lft=rgt=0;
        q[1]=0;
        for(int i=2;i<=n;i++){
            if(T.Query(1,invp[i]-1)<=k){
                k-=T.Query(1,invp[i]-1);
                lft--;
                q[i]=lft;
            }
            else{
                if(k==0){
                    for(int j=i;j<=n;j++)q[j]=rgt+(j-i+1);
                    break;
                }
                tot=0;
                for(int j=1;j<i;j++){
                    if(invp[j]<invp[i])stk[++tot]=q[j];
                }
                sort(stk+1,stk+tot+1);
                q[i]=stk[tot-k]+1;
                for(int j=1;j<i;j++)if(q[j]>stk[tot-k])q[j]++;
                rgt++;
                k=0;
            }
            T.modify(invp[i],1);
        }
        if(k>0){
            cout<<"NO\n";
            continue;
        }
        cout<<"YES\n";
        for(int i=1;i<=n;i++)cout<<q[i]-lft+1<<" ";
        cout<<endl;
    }
    return 0;
}
```

---

