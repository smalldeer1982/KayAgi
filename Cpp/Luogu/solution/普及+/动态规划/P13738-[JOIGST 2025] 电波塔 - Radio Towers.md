# [JOIGST 2025] 电波塔 / Radio Towers

## 题目描述

在 EGOI 国，有 $N$ 座电波塔沿东西方向排列，为国民提供互联网通信服务。电波塔从西向东依次编号为 $1$ 到 $N$。每座电波塔 $i$（$1 \leq i \leq N$）具有以下功能：

- 接收西向波长范围 $[A_i, A_i + L]$ 的电波；
- 向东发射固定波长 $B_i$ 的电波。

对于两座满足 $1 \leq i_1 < i_2 \leq N$ 的塔 $i_1, i_2$，当满足 $A_{i_2} \leq B_{i_1} \leq A_{i_2} + L$ 时，信息可从塔 $i_1$ 传输到塔 $i_2$。

EGOI 国政$ $府将通信稳定性定义为**满足顺序传输条件的非空子集数量**。具体来说，如果子集 $S = {i_1, i_2, \dots, i_k}$（$i_1 < i_2 < \cdots < i_k$）满足以下条件，则 $S$ 满足顺序传输条件：

- 对于任意相邻的两座塔 $(i_j, i_{j+1})$（$1 \leq j \leq k-1$），都满足 $A_{i_{j+1}} \leq B_{i_j} \leq A_{i_{j+1}} + L$。

给定电波塔参数，计算符合条件的子集数量模 $10^9 + 7$ 的结果。

## 说明/提示

#### 【样例解释 #1】

考虑选择电波塔 $1, 2, 3$ 的情况。

  - 由于不满足 $A_2 \leq B_1 \leq A_2 + L$，因此无法从电波塔 $1$ 向电波塔 $2$ 传输信息。
  - 由于满足 $A_3 \leq B_2 \leq A_3 + L$，因此可以从电波塔 $2$ 向电波塔 $3$ 传输信息。

所以，这种选择方式不满足条件。

考虑选择电波塔 $1, 3$ 的情况。

  - 由于满足 $A_3 \leq B_1 \leq A_3 + L$，因此可以从电波塔 $1$ 向电波塔 $3$ 传输信息。

所以，这种选择方式满足条件。

满足条件的塔的选择方式有 $\lbrace1\rbrace, \lbrace2\rbrace, \lbrace3\rbrace, \lbrace1, 3\rbrace, \lbrace2, 3\rbrace$ 这 $5$ 种。因此，输出 $5\bmod (10^9 + 7) = 5$。

此样例满足所有子任务的限制。

#### 【样例解释 #2】

该样例满足子任务 $1,2,4$ 的限制。

#### 【样例解释 #3】

该样例满足子任务 $1,2,4$ 的限制。

#### 【数据范围】

-   $2 \leq N \leq 300\,000$。
-   $0 \leq L \leq 300\,000$。
-   $1 \leq A_i \leq 300\,000$（$1\leq i \leq N$）。
-   $1 \leq B_i \leq 300\,000$（$1\leq i \leq N$）。
-   输入的所有值都是整数。

#### 【子任务】

1. （$20$ 分）$N \leq 16$。
2. （$20$ 分）$N \leq 5\,000$。
3. （$25$ 分）$L = 0$。
4. （$35$ 分）无附加限制。

## 样例 #1

### 输入

```
3 0
1 3
2 3
3 2```

### 输出

```
5```

## 样例 #2

### 输入

```
8 2
1 3
5 1
6 7
7 5
5 2
2 1
3 1
1 6```

### 输出

```
36```

## 样例 #3

### 输入

```
10 3
1 5
2 3
2 4
5 4
10 7
7 9
4 3
3 7
7 7
6 5```

### 输出

```
109```

# 题解

## 作者：Mindulle (赞：3)

很经典的树状数组题目。

考点：
- 树状数组
- DP

暴力枚举子集显然不能通过。故此题是一个 DP 问题。

先令 $dp_i$ 为以第 $i$ 座塔结尾的总方案数。

明显有状态转移方程：

$$dp_i=1+\sum_{j<i,a_i \le b_j \le a_i+L} dp_j$$

平方的 DP 显然会 TLE，考虑优化。

状态转移方程实际上是一个区间求和问题，所以我们可以使用树状数组或线段树来优化 DP，此时时间复杂度为 $O(n\log n)$，足以通过此题。而树状数组代码简短，所以在本题解里，我们选择树状数组。

参考代码：
```cpp
#include<bits/stdc++.h>
#define int long long
#define lowbit(x) x&(-x)
using namespace std;
const int mod=1e9+7;
const int N=3e5+5;
int n,l,a[N],b[N],dp[N],c[2*N],ans;
inline void add(int x,int k){
  while(x<2*N) c[x]+=k,x+=lowbit(x);
}
inline int getsum(int x){  
  int ans=0;
  while(x) ans=(ans+c[x])%mod,x-=lowbit(x);
  return ans%mod;
}
signed main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>n>>l;
    for(int i=1;i<=n;i++) cin>>a[i]>>b[i],dp[i]=1;
    add(b[1],dp[1]);
    for(int i=2;i<=n;i++){
        dp[i]=(dp[i]+(getsum(a[i]+l)-getsum(a[i]-1)+mod)%mod)%mod; //由于相减可能会出现负数，所以先 +mod 再模
        add(b[i],dp[i]);
    }
    for(int i=1;i<=n;i++) ans=(ans+dp[i])%mod;
    cout<<ans;
    return 0;
}
```

需要注意的地方：
- 开 `long long`。
- 树状数组下标要开到 $6\times10^5$。

---

## 作者：xAlec (赞：1)

赛时没做起我好菜111

感觉算是线段树 / 树状数组等区间上的数据结构优化 dp 的非常经典且常见的题目。

### Solution

你会发现对于可以选取的 $i$ 存在于跟 $a_i$ 有关的一个区间内，此时想到设 dp 并且用线段树等在区间取值转移就已经赢一半了。

在去重后的 $b$ 数组上建线段树。

记 $f_i$ 表示以 $i$ 结尾构成子集的方案数，那么有：

$$
f_i = 1 + \sum\limits_{j < i \land pos_{a_i} \leq j \leq pos_{a_i + L}}{f_j}
$$

每次查询 $a_i \sim a_i + L$ 对应 $b$ 中的下标的区间转移到 $f_i$ 即可，同时更新 $b_i$ 对应下标位置线段树上的值。

注意所有操作的下标均为排序去重后 $b$ 数组上的下标。

### Code

```cpp
#include <bits/stdc++.h>
#define FASTIO
#define int long long
#define lson (rt << 1)
#define rson (rt << 1 | 1)
using namespace std;
#ifdef FASTIO
	static int ostk[33];
	char buf[1 << 23], *p1, *p2;
#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 23, stdin), p1 == p2) ? EOF : *p1++)
	
	inline int read()
	{
		int res = 0, f = 1;
		char ch = getchar();
		while (!isdigit(ch))
			f = ch == '-' ? -1 : 1, ch = getchar();
		while (isdigit(ch))
			res = res * 10 + (ch ^ 48), ch = getchar();
		return res * f;
	}

	inline void write(int x)
	{
		int top = 0;
		if (x < 0)
		{
			x = -x;
			putchar('-');
		}
		do
		{
			ostk[top++] = x % 10;
			x /= 10;
		} while(x);
		while(top)
			putchar(ostk[--top] + '0');
	}

	inline void print(int x, char ch)
	{
		write(x);
		putchar(ch);
	}
#endif

constexpr int N = 6e5 + 100;
constexpr int mod = 1e9 + 7;
int n, L, a[N], b[N], cpy[N], f[N];

struct segmentree {
	int l, r;
	int val;
} T[N << 2];

inline void pushup(int rt)
{
	T[rt].val = (T[lson].val + T[rson].val) % mod;
}

void build(int rt, int l, int r)
{
	T[rt].l = l;
	T[rt].r = r;
	if (l == r)
		return;
	int mid = (l + r) / 2;
	build(lson, l, mid);
	build(rson, mid + 1, r);
	pushup(rt);
}

void update(int rt, int tar, int v)
{
	int l = T[rt].l;
	int r = T[rt].r;
	if (l == r)
	{
		T[rt].val = (T[rt].val + v) % mod;
		return;
	}
	int mid = (l + r) / 2;
	if (tar <= mid)
		update(lson, tar, v);
	else
		update(rson, tar, v);
	pushup(rt);
}

int query(int rt, int ql, int qr)
{
	int l = T[rt].l;
	int r = T[rt].r;
	if (ql <= l && qr >= r)
		return T[rt].val;
	int mid = (l + r) / 2, res = 0;
	if (ql <= mid)
		res = (res + query(lson, ql, qr)) % mod;
	if (qr > mid)
		res = (res + query(rson, ql, qr)) % mod;
	return res;
}

signed main()
{
	n = read();
	L = read();
	for (int i = 1; i <= n; i ++)
	{
		a[i] = read();
		b[i] = cpy[i] = read();
	}
	sort(cpy + 1, cpy + n + 1);
	int nn = unique(cpy + 1, cpy + n + 1) - (cpy + 1);
	
	build(1, 1, nn);
	for (int i = 1; i <= n; i ++)
	{
		int lpos = lower_bound(cpy + 1, cpy + nn + 1, a[i]) - cpy;
		int rpos = upper_bound(cpy + 1, cpy + nn + 1, a[i] + L) - cpy - 1;
		f[i] = (1 + query(1, lpos, rpos)) % mod;
		int pos = lower_bound(cpy + 1, cpy + nn + 1, b[i]) - cpy;
		update(1, pos, f[i]);
	}
	int ans = 0;
	for (int i = 1; i <= n; i ++)
		ans = (ans + f[i]) % mod;
	print(ans, '\n');
	return 0;
}
```

---

## 作者：MonKeySort_ZYczc (赞：1)

## 思路流程
首先暴力枚举可以拿到 20pts。  

考虑优化。  
设 $dp_i$ 为以 $i$ 结尾的子集的数量。  
有 
$$
dp_i=(\sum_{j=i+1}^{N}dp_j[a_j\le b_i\le a_j+L])+1
$$
（额外的 $1$ 是只有自己一个数的可能性）。  
然后 40pts 了。  

发现 $dp_i$ 只会影响 $b_i$ 在 $[a_i,a_i+L]$ 的数，于是打一个值域线段树，每次区间加和（$[a_i,a_i+L]$），单点查询（$b_i$）即可。  

注意取模以及 $a_i+L$ 最大可达 $6\times 10^5$，可以特殊处理或空间直接开到 $6\times 10^5$。  
## 代码实现
这里使用开大空间处理 $a_i+L$ 的方法。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ls k<<1
#define rs k<<1|1
const int N=6e5+10,mod=1e9+7;
int n,a[N],b[N],l,ans;
struct SGT
{
	int l,r,s,d;
	#define l(i) t[i].l
	#define r(i) t[i].r
	#define s(i) t[i].s
	#define d(i) t[i].d
}t[N<<2];
void build(int k,int l,int r)
{
	l(k)=l;r(k)=r;s(k)=d(k)=0;
	if(l==r) return;
	int mid=l+r>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
}
inline void pushdown(int k)
{
	d(ls)=(d(ls)+d(k))%mod;s(ls)=(s(ls)+d(k))%mod;
	d(rs)=(d(rs)+d(k))%mod;s(rs)=(s(rs)+d(k))%mod;
	d(k)=0;
}
void cg(int k,int x,int y,int v)
{
	int l=l(k),r=r(k);
	if(l>=x&&r<=y)
	{
		s(k)=(s(k)+v)%mod;d(k)=(d(k)+v)%mod;
		return;
	 } 
	pushdown(k);
	int mid=l+r>>1;
	if(x<=mid) cg(ls,x,y,v);
	if(mid<y) cg(rs,x,y,v);
	s(k)=s(ls)+s(rs);
}
int que(int k,int p)
{
	int l=l(k),r=r(k);
	if(l==p&&p==r) return s(k);
	pushdown(k);
	int mid=l+r>>1;
	if(p<=mid) return que(ls,p);
	else return que(rs,p);
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>l;
	for(int i=1;i<=n;i++) cin>>a[i]>>b[i];
	build(1,1,600000);
	for(int i=n;i>=1;i--) 
	{
		int dp=(que(1,b[i])+1)%mod;
		ans=(ans+dp)%mod;
		cg(1,a[i],a[i]+l,dp);
	}
	cout<<ans;
}

```

---

## 作者：XIAOWANGCHAI (赞：1)

### 正文
向左接受，向右发射，容易想到 $\texttt{dp}$。

定义 $dp_i$ 表示第 $i$ 座塔的答案，则 $dp_i=(\displaystyle \sum _{j=1}^{i-1} [B_j \in [A_i,A_i+l]] \times dp_j)+1$，直接暴力计算达到 $O(N^2)$ 的复杂度。

优化也很简单，考虑动态维护 $B_j$ 的 $dp$ 值的和 $X$，则直接 $dp_i=\displaystyle (\sum _{j=A_i}^{A_j+l} X_j)+1$。计算完之后将 $X_{B_i}$ 增加 $dp_i$ 即可。用线段树或者树状数组维护。

代码复杂度 $O(N \log N)$。

代码太丑就不贴了。

---

## 作者：Forge_Unique (赞：1)

## 思路

记一个数组 $dp_i$ 表是以第 $i$ 座电塔结尾的方案数。

则显然的 $dp_i = $ 所有的在第 $i$ 座电塔左边的可以被第 $i$ 座电塔接受到电波的电塔的 $dp$ 的和。

那么现在的难点就在如何求出所有的在第 $i$ 座电塔左边的可以被第 $i$ 座电塔接受到电波的所有电塔。

显然我们可以用树状数组维护，其余细节见代码。

## 代码

```
#include<cstring>
#include<iostream>
#define int long long
using namespace std;
const int N = 3e5 + 10;
const int mod = 1e9 + 7;
int n,m,a[N],b[N],tree[N * 2],dp[N];
int lowbit(int x){
	return x & -x;
}
void add(int x,int k){
	for(int i = x;i <= N * 2 - 1;i += lowbit(i)){
		tree[i] += k;
		tree[i] %= mod;
	}
}
int get_sum(int x){
	int ans = 0;
	for(int i = x;i >= 1;i -= lowbit(i)){
		ans += tree[i];
		ans %= mod;
	}
	return ans;
}
signed main(){
	cin >> n >> m;
	for(int i = 1;i <= n;i++){
		cin >> a[i] >> b[i];
		dp[i] = 1;//每座电塔本身也算一种方案 
	}
	add(b[1],dp[1]);
	for(int i = 2;i <= n;i++){
		dp[i] += get_sum(a[i] + m) - get_sum(a[i] - 1) + mod;//接受信号 
		dp[i] %= mod;
		add(b[i],dp[i]);//发出信号 
	}
	int ans = 0;
	for(int i = 1;i <= n;i++){
		ans += dp[i];
		ans %= mod;
	}
	cout << ans;
	return 0;
}
```

---

## 作者：__coderyc__ (赞：1)

## 思路
显然枚举子集会超时，考虑优化。

定义 $dp_i$ 表示以第 $i$ 座塔结尾的合法子集数量，等于这座塔本身以及满足条件的前驱塔 $dp$ 值之和，即：
$$dp_i = 1+\sum_{j<i,A_i\le B_j\le A_i+L} dp_j$$

时间复杂度为 $O(n^2)$，仍会超时，考虑用树状数组优化，进行快速的区间查询与单点更新。

这时时间复杂度为 $O(n \log n)$，可以通过此题。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int MOD=1e9+7;
const int MAXN=3e5+5;
int N,L;
int A[MAXN],B[MAXN];
ll dp[MAXN],ans=0;
struct BIT{
    ll t[MAXN];
    void add(int x,ll v){
        for(;x<MAXN;x+=x&-x) t[x]=(t[x]+v)%MOD;
    }
    ll sum(int x){
        ll res=0;
        for(;x>0;x-=x&-x) res=(res+t[x])%MOD;
        return res;
    }
    ll query(int l,int r){
        if(l>r) return 0;
        return (sum(r)-sum(l-1)+MOD)%MOD;
    }
}bit;
int main(){
    cin>>N>>L;
    for(int i=1;i<=N;++i) cin>>A[i]>>B[i];
    vector<int> vals(B+1,B+N+1);
    sort(vals.begin(),vals.end());
    vals.erase(unique(vals.begin(),vals.end()),vals.end());
    for(int i=1;i<=N;++i){
        int lb=lower_bound(vals.begin(),vals.end(),A[i])-vals.begin()+1;
        int ub=upper_bound(vals.begin(),vals.end(),A[i]+L)-vals.begin();
        dp[i]=(1+bit.query(lb,ub))%MOD;
        int pos=lower_bound(vals.begin(),vals.end(),B[i])-vals.begin()+1;
        bit.add(pos,dp[i]);
        ans=(ans+dp[i])%MOD;
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：_Weslie_ (赞：0)

## Solution P13738

### Idea

考虑直接 dp。

1. 状态设计：设 $dp_i$ 为传输到 $i$ 位置的方案数。
2. 状态转移：$dp_{i}=(\sum\limits_{a_i\le b_j\le a_i+l}dp_{j})+1$。原因是所有可以转移来的都可以加到方案数里面，并且不要忘记把自己独自成为合法序列的方案数算上。
3. 初值设计：对所有 $i\in [1,n]$，有 $dp_i=0$。
4. 答案：$\sum\limits_{i=1}^n dp_i$，原因显然（可以以任意位置结尾）。
5. 复杂度分析：如果直接转移就是 $\operatorname{O}(n^2)$ 的。因为转移要求符合一个区间，考虑使用树状数组优化，每次做时查询 $[a_i,a_i+l]$ 区间的 $dp$ 值之和，并且 $i$ 转移完之后给树状数组上 $b_i$ 的位置加上 $dp_i$ 保证正确性，可以做到 $\operatorname{O}(n\log V)$（$V$ 是值域）。

细节：$a_i$ 和 $l$ 都 $\le 3\times 10^5$，为防止爆炸建议把树状数组大小开到 $6\times 10^5$ 以上。

### Code

```
#include<bits/stdc++.h>
using namespace std;
const int N=300005,mod=1000000007;
#define ll long long
ll dp[N];
ll tr[N<<2];
int lowbit(int x){
	return x&(-x);
}
void add(int now,int x){
	while(now<N*3){
		tr[now]=(tr[now]+x)%mod;
		now+=lowbit(now);
	}
}
ll query(int now){
	ll res=0;
	while(now){
		res=(res+tr[now])%mod;
		now-=lowbit(now);
	}
	return res;
}
int n,a[N],b[N],l;
int main(){
	scanf("%d%d",&n,&l);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&a[i],&b[i]);
	}
	ll ans=0;
	for(int i=1;i<=n;i++){
		dp[i]+=(query(a[i]+l)-query(a[i]-1)+1+mod)%mod;
		add(b[i],dp[i]);
		ans=(ans+dp[i])%mod;
	}
	printf("%lld",ans);
	return 0;
}

```

---

## 作者：_xguagua_Firefly_ (赞：0)

### 分析

设 $dp _ {i}$ 表示以 $i$ 结尾的合法子序列的个数，则有转移：$dp _ {i} = 1 + \sum \limits _ {j \lt i \wedge A _ {i} \le B _ {j} \le A _ {i} + L} dp _ {j}$。

这个转移式是 $\Omicron(n ^ {2})$ 的，考虑优化，因为是从区间转移过来，所以可以考虑用树状数组或线段树优化。

具体的就是开棵线段树，每次算完 $dp$ 值之后给 $B _ {i}$ 位置加上 $dp _ {i}$，计算的时候查询 $[A _ {i},A _ {i} + L]$ 之和就能做到 $\Omicron(n \log n)$。

### Code

```cpp
#include <bits/extc++.h>
using namespace std;
#define int long long 

constexpr int MAXN = 3e5 + 5,V = 3e5,MOD = 1e9 + 7;
int n,l;
int a[MAXN],b[MAXN],dp[MAXN],tree[MAXN << 2];
inline void modify(int rt,int l,int r,int pos,int val)
{
    tree[rt] = (tree[rt] + val) % MOD;
    if(l == r)
        return ;
    int mid = (l + r) >> 1;
    if(pos <= mid)
        modify(rt << 1,l,mid,pos,val);
    else
        modify(rt << 1 | 1,mid + 1,r,pos,val);
}
inline int query(int rt,int l,int r,int L,int R)
{
    if(L <= l && R >= r)
        return tree[rt];
    int mid = (l + r) >> 1,res = 0;
    if(L <= mid)
        res = (res + query(rt << 1,l,mid,L,R)) % MOD;
    if(R > mid)
        res = (res + query(rt << 1 | 1,mid + 1,r,L,R)) % MOD;
    return res;
}
signed main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin >> n >> l;
    for(int i = 1;i <= n;i++)
    {
        cin >> a[i] >> b[i];
        dp[i] = 1;
    }
    int ans = 0;
    for(int i = 1;i <= n;i++)
    {
        dp[i] = (dp[i] + query(1,1,V,a[i],min(a[i] + l,V))) % MOD;
        modify(1,1,V,b[i],dp[i]);
        ans = (ans + dp[i]) % MOD;
    }
    cout << ans;
}
```

---

## 作者：szh_AK_all (赞：0)

典。

设 $f_i$ 表示以 $i$ 结尾的合法子集数量，转移为：$f_i = 1 + \sum_{j=1}^{i-1}[A_i\le B_j\le A_i+L]\times f_j$，最终答案为 $\sum_{i=1}^n f_i$。线段树优化即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 1e9 + 7;
int a[1000005], b[1000005], f[1000005];
int t[4000005];
void add(int d, int l, int r, int k, int z) {
    if (l == r) {
        t[d] += z, t[d] %= mod;
        return;
    }
    int mid = (l + r) / 2;
    if (k <= mid)
        add(d * 2, l, mid, k, z);
    else
        add(d * 2 + 1, mid + 1, r, k, z);
    t[d] = t[d * 2] + t[d * 2 + 1], t[d] %= mod;
}
int ask(int d, int l, int r, int ll, int rr) {
    if (ll > rr)
        return 0;
    if (ll <= l && r <= rr)
        return t[d];
    int mid = (l + r) / 2, ans = 0;
    if (ll <= mid)
        ans += ask(d * 2, l, mid, ll, rr), ans %= mod;
    if (rr > mid)
        ans += ask(d * 2 + 1, mid + 1, r, ll, rr), ans %= mod;
    return ans;
}
signed main() {
    int n, l;
    cin >> n >> l;
    for (int i = 1; i <= n; i++)    
        cin >> a[i] >> b[i];
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        f[i] = 1;
        f[i] += ask(1, 1, 3e5, a[i], a[i] + l), f[i] %= mod;
        add(1, 1, 3e5, b[i], f[i]);
        ans += f[i], ans %= mod;
    }
    cout << ans;
}
```

---

