# [KSN2021] Self Permutation

## 题目描述

给定一个长度为 $N$ 的排列 $a_i$，你可以执行若干次操作：

* 选择两个相邻的数，删除它们中较大的那个。

问最后可能得到序列的数量，答案对 $10^9+7$ 取模。

注意如果两个数中间所有的数被删除了，它们会变成相邻的。

## 说明/提示

**【样例解释】**

对于第一组样例，以下为所有可能得到的序列：

- $[2,3,1]$
- $[\bold2,\bold3,1]\to[2,1]$
- $[\bold2,\bold3,1]→[\bold2,\bold1]→[1]$

对于第二组样例，以下为所有可能得到的序列：

- $[2,1,4,3]$
- $[\bold2,\bold1, 4, 3]\to[1, 4, 3]$
- $[\bold2,\bold1, 4, 3]\to[1,\bold4,\bold3]\to[1, 3]$
- $[\bold2,\bold1, 4, 3]\to[1,\bold4,\bold3]\to[\bold1,\bold3]\to[1]$
- $[2, 1,\bold4,\bold3]\to[2, 1, 3]$
- $[2, 1,\bold4,\bold3]\to[2,\bold1,\bold3]\to[2, 1]$

**【数据范围】**

**本题采用捆绑测试。**

- Subtask 1（8 points）：只存在一组数据，满足 $N=6$，$A=[2,5,1,3,4,6]$。
- Subtask 2（20 points）：$N\leq 200$。
- Subtask 3（13 points）：$N\leq 2000$，$A_i=i$。
- Subtask 4（9 points）：$A_i=i$。
- Subtask 5（23 points）：$N\leq 2000$。
- Subtask 6（27 points）：无特殊限制。

对于所有数据，$N\leq 3\times 10^5$，保证输入的 $a_i$ 能构成一个排列。

## 样例 #1

### 输入

```
3
2 3 1```

### 输出

```
3```

## 样例 #2

### 输入

```
4
2 1 4 3```

### 输出

```
6```

# 题解

## 作者：Elma_ (赞：14)

一个显然的结论：对于原序列中的两个位置 $i,j(i < j)$，如果存在某一个最终得到的序列使得 $i,j$ 相邻，那么一定有 $\min\{a_{i+1},\cdots,a_{j-1}\} > \min\{a_i,a_j\}$，否则没有办法删过去。

据此我们可以设计 dp，设 $f_i$ 为以 $i$ 为结尾的最后可能得到的序列的总数，枚举上一个位置 $j$ 进行转移即可，其中 $j$ 需要满足上面给的那个条件，最后对所有可能作为结尾的位置统计答案。然而这样是 $O(n^2)$ 的，考虑进行优化。

对于一个位置 $i$，我们可以利用单调栈 $O(n)$ 求出用它左右两边最远可以删到哪里（实际上就是求左右两边第一个小于 $a_i$ 的数的位置），这样每个数就对应了一个区间 $[l_i,r_i]$。于是我们会发现上面那个条件就变成了区间 $[l_i,r_i]$ 和 $[l_j,r_j]$ 有交（因为每个数要么被 $i$ 删掉，要么被 $j$ 删掉）。

树状数组优化 dp 即可。时间复杂度 $O(n\log n)$，常数极小。

```cpp
const int MN = 3e5 + 5, Inf = 1e9, Mod = 1e9 + 7;

int N, A[MN], f[MN], L[MN], R[MN], Ans, st[MN], tp;

struct BIT {
    int tr[MN];
    inline int lowbit(int x) {
        return x & (-x);
    }
    inline void Modify(int x, int k) {
        for (int i = x; i <= N; i += lowbit(i)) {
            tr[i] = (tr[i] + k) % Mod;
        }
    } 
    inline int Query(int x) {
        int res = 0;
        for (int i = x; i; i -= lowbit(i)) {
            res = (res + tr[i]) % Mod;
        }
        return res;
    }
} T;

signed main(void) {
    N = read();
    for (int i = 1; i <= N; i++) A[i] = read();
    for (int i = 1; i <= N + 1; i++) {
        while (tp && A[st[tp]] > A[i]) R[st[tp--]] = i - 1;
        st[++tp] = i;
    }
    for (int i = N; i >= 0; i--) {
        while (tp && A[st[tp]] > A[i]) L[st[tp--]] = i + 1;
        st[++tp] = i;
    }
    T.Modify(1, 1);
    for (int i = 1; i <= N; i++) {
        f[i] = (T.Query(N) - T.Query(L[i] - 1) % Mod + Mod) % Mod;
        T.Modify(R[i], f[i]);
    }
    int mn = Inf;
    for (int i = N; i >= 1; i--) {
        mn = min(mn, A[i]), Ans = (Ans + (mn == A[i] ? 1 : 0) * f[i]) % Mod;
    }
    printf("%lld\n", Ans);
    return 0;
}
```


---

## 作者：rui_er (赞：9)

怎么其他两篇题解都是 $O(n\log n)$ 的，来发一个 $O(n)$ 做法，当考前复习了。

对原序列建出小根笛卡尔树，节点编号与原序列中的下标相同。记 $T_u$ 表示以 $u$ 为根的子树，$lc(u),rc(u)$ 分别表示 $u$ 的左儿子和右儿子。

设 $f_u$ 表示删除若干 $T_u$ 中的点（可以不删），但不能删空的方案数。

假设节点 $u$ 没有删除，此时左右子树可以删空也可以不删空，有转移：

$$
f_u\gets(f_{lc(u)}+1)(f_{rc(u)}+1)
$$

节点 $u$ 可以被删除，当且仅当其左侧存在比它小的数且它们中间所有数都被删了，或者其右侧存在比它小的数且它们中间所有数都被删了。根据笛卡尔树性质，假设 $T_u$ 的下标范围是 $[l_u,r_u]$，则 $l_u-1,r_u+1$ 两个下标的数如果存在，必定比 $u$ 下标的数要小。根据这一点，有转移：

$$
\begin{cases}
f_u\gets f_{rc(u)}&\textrm{if }l_u > 1\\
f_u\gets f_{lc(u)}&\textrm{if }r_u > 1\\
\end{cases}
$$

时间复杂度 $O(n)$。

```cpp
//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x, y, z) for(int x = (y); x <= (z); ++x)
#define per(x, y, z) for(int x = (y); x >= (z); --x)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do {freopen(s".in", "r", stdin); freopen(s".out", "w", stdout);} while(false)
#define endl '\n'
using namespace std;
typedef long long ll;

mt19937 rnd(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
int randint(int L, int R) {
    uniform_int_distribution<int> dist(L, R);
    return dist(rnd);
}

template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}

template<int mod>
inline unsigned int down(unsigned int x) {
    return x < mod ? x : x - mod;
}

template<int mod>
struct Modint {
    unsigned int x;
    Modint() = default;
    Modint(int x) : x(x) {}
    friend istream& operator>>(istream& in, Modint& a) {return in >> a.x;}
    friend ostream& operator<<(ostream& out, Modint a) {return out << a.x;}
    friend Modint operator+(Modint a, Modint b) {return down<mod>(a.x + b.x);}
    friend Modint operator-(Modint a, Modint b) {return down<mod>(a.x - b.x + mod);}
    friend Modint operator*(Modint a, Modint b) {return 1ULL * a.x * b.x % mod;}
    friend Modint operator^(Modint a, int k) {Modint ans = 1; for(; k; k >>= 1, a *= a) if(k & 1) ans *= a; return ans;}
    friend Modint operator~(Modint a) {return a ^ (mod - 2);}
    friend Modint operator/(Modint a, Modint b) {return a * ~b;}
    friend Modint& operator+=(Modint& a, Modint b) {return a = a + b;}
    friend Modint& operator-=(Modint& a, Modint b) {return a = a - b;}
    friend Modint& operator*=(Modint& a, Modint b) {return a = a * b;}
    friend Modint& operator^=(Modint& a, int k) {return a = a ^ k;}
    friend Modint& operator/=(Modint& a, Modint b) {return a = a / b;}
    friend Modint& operator++(Modint& a) {return a += 1;}
    friend Modint operator++(Modint& a, int) {Modint b = a; ++a; return b;}
    friend Modint& operator--(Modint& a) {return a -= 1;}
    friend Modint operator--(Modint& a, int) {Modint b = a; --a; return b;}
    friend Modint operator-(Modint a) {return a.x == 0 ? 0 : mod - a.x;}
    friend bool operator==(Modint a, Modint b) {return a.x == b.x;}
    friend bool operator!=(Modint a, Modint b) {return !(a == b);}
};

typedef Modint<1000000007> mint;

const int N = 3e5 + 5;

int n, a[N], lc[N], rc[N], stk[N], top;
mint dp[N];

void dfs(int u, int l, int r) {
    if(lc[u]) dfs(lc[u], l, u - 1);
    if(rc[u]) dfs(rc[u], u + 1, r);
    dp[u] += (dp[lc[u]] + 1) * (dp[rc[u]] + 1);
    if(l > 1) dp[u] += dp[rc[u]];
    if(r < n) dp[u] += dp[lc[u]];
} 

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n;
    rep(i, 1, n) cin >> a[i];
    stk[++top] = 1;
    rep(i, 2, n) {
        while(top && a[stk[top]] > a[i]) --top;
        if(!top) lc[i] = stk[1];
        else {
            lc[i] = rc[stk[top]];
            rc[stk[top]] = i;
        }
        stk[++top] = i;
    }
    int rt = min_element(a + 1, a + 1 + n) - a;
    dfs(rt, 1, n);
    cout << dp[rt] << endl;
    return 0;
}
```

---

## 作者：Priestess_SLG (赞：2)

模拟赛 T3，场切~~但是被卡常了.jpg~~

考虑设 $f_i$ 表示以 $i$ 结尾的子排列有多少种不同的序列，那么显然有初始条件 $f_1=1$，若 $j$ 可以转移到 $i$ 则必须满足存在一组合并方案使得 $i$ 和 $j$ 相邻，即 $\min\limits_{k=j+1}^{i-1} a_k>\min(a_i,a_j)$。使用 ST 表维护区间 $\min$ 就可以 $O(n^2)$ 暴力 dp。代码：

```cpp
lg[0]=-1;
	F(i,1,N-1)lg[i]=lg[i>>1]+1;
	st(n);
	a[0]=1e18;
	f[1]=f[0]=1;
	F(i,2,n){
		f[i]=f[i-1];
		F(j,0,i-2){
			if(chk(j,i))
				f[i]=(f[i]+f[j])%mod;
		}
	}
	// cout<<"qwq "<<f[1]<<' '<<f[2]<<' '<<f[3]<<' '<<f[4]<<'\n';
	int mi=1e18,res=0;
	G(i,n,1){
		if(a[i]<mi)res=(res+f[i])%mod;
		mi=min(mi,a[i]);
	}
```

发现一个元素可能合并到的范围 $[L_i,R_i]$ 可以使用单调栈 $O(n)$ 计算出，两个元素 $i$，$j$ 可以相邻当且仅当其所对应的区间 $[L_i,R_i]$ 和 $[L_j,R_j]$ 中存在元素相邻。因此此时变为 2-D 数点问题，使用树状数组 ds 就可以在 $O(n\log n)$ 的时间复杂度内求解。赛时[代码](https://www.luogu.com.cn/record/177427377)。

---

## 作者：zhouyuhang (赞：2)

感觉现有那篇题解做繁了。

观察到性质：$(l,r)$ 能被删空意味着 $[l,r]$ 最小值等于 $\min(a_l,a_r)$。

令 $f_i$ 表示以位置 $i$ 为结尾的序列个数。根据上述性质容易写出转移并优化。具体地，用数据结构（比如 ``set``）对于所有 $i$ 维护出 $p<i$ 满足 $a_p<\min(a_{p+1},…,a_i)$ 的 $p$ 所构成集合 ${\rm S}_i$，那么根据所得性质 $f_i=\sum_{j=\max \text{S}_i+1}^{i-1}f_j+\sum_{j\in \text{S}_i}f_j$。可能有人疑惑怎么维护，只需注意 dp 顺序是从后往前扫，因此每次只会在删除比当前数大的元素并加入当前数。
复杂度 ${\mathcal O}(n\log n)$。

代码很短：

```cpp
#include <bits/stdc++.h>

using namespace std;
using ii = pair<int, int>;

const int N = 3e5 + 10;
const int mod = 1e9 + 7;

int n, a[N];
int dp[N], sum[N]; // sum 是前缀和

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	
	set<ii> s;
	sum[0] = 1;
	for (int i = 1, res = 0; i <= n; ++i) { // res 维护的是当前 set 内 dp 值之和
		ii u;
		while (!s.empty()) {
			u = (*s.rbegin());
			if (u.first > a[i]) {
				res = (res - dp[u.second] + mod) % mod;
				s.erase(u);
			} else break;
		}
		if (s.empty()) dp[i] = sum[i - 1];
		else dp[i] = (res + sum[i - 1] - sum[u.second]) % mod;
		if (dp[i] < 0) dp[i] += mod;
		sum[i] = (sum[i - 1] + dp[i]) % mod;
		s.insert({a[i], i});
		res = (res + dp[i]) % mod;
	}
	
	int ans = 0;
	for (ii u: s) ans = (ans + dp[u.second]) % mod;
	
	cout << ans << endl;
	
	return 0;
}
```

---

## 作者：SunburstFan (赞：0)

### P7972 [KSN2021] Self Permutation

#### 题目大意

给定一个长度为 $N$ 的排列 $a_i$，每次操作选择两个相邻的数，删除它们中较大的那个。

问最后可能得到序列的数量，答案对 $10^9+7$ 取模。

#### 解题思路

通过理解题目、手模大样例，可以得出以下重要性质：

- 如果 $a_l$ 与 $a_r$ 能够被删除至相邻，那么 $\min _{i=l}^{r} a_i = \min(a_l,a_r)$

考虑 dp，设 $f_i$ 表示前 $i$ 个数能够构成的最后的序列的个数。

然后就有一个很显然的时间复杂度为 $O(N^2)$ 的转移，枚举上一个位置 $j$，但这样会超时。

考虑用单调栈，对于每个 $i$ 求它左边和右边第一个小于 $a_i$ 的位置，记为 $l_i$ 和 $r_i$。

如果两个位置 $i$ 和 $j$ 可以相邻，当且仅当 $[l_i,r_i]$ 与 $[l_j,r_j]$ 相交。

就可以用树状数组优化 dp 解决，时间复杂度 $O(N \times \log N)$。

```cpp

#include<bits/stdc++.h>
using namespace std;

const int N=3e5+5;
const int mod=1e9+7;

int n,a[N],f[N];
int l[N],r[N];

struct BIT{
    int c[N];

    int lowbit(int x){
        return x&-x;
    }
    void update(int x,int k=1){
        for(;x<=n;x+=lowbit(x)) 
            (c[x]+=k)%=mod;
    }
    int query(int x){
        int res=0;
        for(;x;x-=lowbit(x))
            (res+=c[x])%=mod;
        return res;
    }
}Tr;

struct my_stack{
    int idx;
    vector<int> vec;
    
    int size(){
        return idx;
    }
    bool empty(){
        return idx==0;
    }
    void init(int x){
        vec.reserve(x);
    }
    int top(){
        return vec[idx];
    }
    void push(int x){
        vec[++idx]=x;
        return;
    }
    void pop(){
        idx--;
    }
    void pop_k(int k){
        idx-=k;
    }

}stk;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);

    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }

    stk.init(n+5);
    for(int i=1;i<=n+1;i++){
        while(stk.size()&&a[stk.top()]>a[i]){
            r[stk.top()]=i-1;
            stk.pop();
        }
        stk.push(i);
    }

    for(int i=n;i>=0;i--){
        while(stk.size()&&a[stk.top()]>a[i]){
            l[stk.top()]=i+1;
            stk.pop();
        }
        stk.push(i);
    }

    Tr.update(1);
    for(int i=1;i<=n;i++){
        f[i]=((Tr.query(n)-Tr.query(l[i]-1))%mod+mod)%mod;
        Tr.update(r[i],f[i]);
    }

    int minn=1<<30,ans=0;
    for(int i=n;i>=1;i--)
        if(minn>=a[i]){
            minn=a[i];
            (ans+=f[i])%=mod;
        }

    cout<<ans<<"\n";
    return 0;
}

```

---

