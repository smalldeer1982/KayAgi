# Array Collapse

## 题目描述

You are given an array $ [p_1, p_2, \dots, p_n] $ , where all elements are distinct.

You can perform several (possibly zero) operations with it. In one operation, you can choose a contiguous subsegment of $ p $ and remove all elements from that subsegment, except for the minimum element on that subsegment. For example, if $ p = [3, 1, 4, 7, 5, 2, 6] $ and you choose the subsegment from the $ 3 $ -rd element to the $ 6 $ -th element, the resulting array is $ [3, 1, 2, 6] $ .

An array $ a $ is called reachable if it can be obtained from $ p $ using several (maybe zero) aforementioned operations. Calculate the number of reachable arrays, and print it modulo $ 998244353 $ .

## 样例 #1

### 输入

```
3
2
2 1
4
2 4 1 3
5
10 2 6 3 4```

### 输出

```
2
6
12```

# 题解

## 作者：sunkuangzheng (赞：31)

组合数学不太好做，考虑 dp。设 $f_i,g_i$ 表示考虑序列前 $i$ 个元素，且最后一个元素是否被删除的方案数。令 $p$ 表示 $i$ 前面第一个小于 $a_i$ 的数字，有转移：

$$\begin{cases}f_i = f_p + g_p\\g_i = f_p + \sum\limits_{j=p}^{i-1} g_j\end{cases}$$

答案是 $f_n + g_n$。

第一个转移式子的含义是，如果第 $i$ 个元素要被删除，那么它一定不是区间最小值，所以这个区间一定要包含小于它的数字，此时可以选择保留 $p$，也可以让 $p$ 被前面更小的数字删除。第二个转移式子的含义是，第 $i$ 个元素要保留，这个区间里它一定是最小值。上一个区间端点在 $p \sim i-1$ 之间显然满足题意，如果 $p$ 被删除，上一个区间端点在最后一个没有被删除的位置也合法，所以加上 $f_p$。

直接做是 $\mathcal O(n^2)$ 的，对于寻找 $p$ 显然可以单调栈，$g_i$ 的转移有区间和， 可以简单前缀和优化。最终复杂度 $\mathcal O(n)$。

赛时代码，注意 $f$ 和 $g$ 的含义和上面相反。



```cpp
/**
 *    author: sunkuangzheng
 *    created: 18.12.2023 23:06:42
**/
#include<bits/stdc++.h>
using ll = long long;
#define int long long
const int N = 5e5+5,mod = 998244353;
using namespace std;
int T,n,a[N],st[N],tp,sm[N],f[N],g[N];
void los(){
    cin >> n;tp = 0;
    for(int i = 1;i <= n;i ++) cin >> a[i];
    f[0] = sm[0] = 1;
    for(int i = 1;i <= n;i ++){
        while(tp && a[st[tp]] > a[i]) tp --;
        int j = st[tp];if(j) g[i] = (f[j] + g[j]) % mod; else g[i] = 0;
        f[i] = (sm[i-1] - (j == 0 ? 0 : sm[j-1]) + g[j] + mod) % mod,
        sm[i] = (sm[i-1] + f[i]) % mod,st[++tp] = i;
    }cout << (f[n] + g[n]) % mod << "\n";
}signed main(){
    ios::sync_with_stdio(0),cin.tie(0);
    for(cin >> T;T --;) los();
}
```



---

## 作者：Boboge (赞：12)

考虑在笛卡尔树，容易发现根节点是无法被删除的。接下来考虑什么情况下可以删除某个节点 $u$ 并保留其子节点 $v$。

假设 $v$ 在 $u$ 的左子树中，若存在一个结点 $anc$ 是 $u$ 的祖先，且在原数组中 $anc$ 在 $u$ 的右边，那么就可以通过删除 $[u, anc]$ 区间来删除 $u$ 并且保留 $v$，那么对于每个节点，我们只需要分别记录它有没有位于左/右的祖先即可。

设 $dp_{u}$ 为以 $u$ 为根节点的子树的方案数(包含空树)，则：

1. 保留 $u$ 的情况：$dp_{u} \gets dp_{u} + dp_{lson} \times dp_{rson}$。
2. 不保留 $u$ 的情况：
   1. 如果 $u$ 有位于右边的祖先，可以保留左子树，右子树一定会被清空：$dp_{u} \gets dp_{u} + dp_{lson}$。
   2. 如果 $u$ 有位于左边的祖先，同理：$dp_{u} \gets dp_{u} + dp_{rson}$。
   3. 注意删去重复统计的空树。

核心代码：

```cpp
void run(int tCase) {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    auto [rt, ls, rs] = CartesianTree(a);
    std::vector<Z> dp(n);
    auto dfs = [&](auto &dfs, int u, int f) {
        if (u == -1) return;
        dfs(dfs, ls[u], f | 1);
        dfs(dfs, rs[u], f | 2);
        Z L = 1, R = 1;
        if (~ls[u]) L = dp[ls[u]];
        if (~rs[u]) R = dp[rs[u]];
        //keep root;
        dp[u] += L * R;
        //no keep root
        if (f & 1) {
            dp[u] += L;
        }
        if (f & 2) {
            dp[u] += R;
        }
        if (f == 3) dp[u] -= 1;
    };
    dfs(dfs, ls[rt], 1);
    dfs(dfs, rs[rt], 2);
    Z L = 1, R = 1;
    if (~ls[rt]) L = dp[ls[rt]];
    if (~rs[rt]) R = dp[rs[rt]];
    Z ans = L * R;
    std::cout << ans << '\n';
}
```

时间复杂度：$O(n)$ ，因为笛卡尔树可以线性建（板子）。

---

## 作者：Lu_xZ (赞：10)

### [D. Array Collapse](https://codeforces.com/problemset/problem/1913/D)

考虑分治。

设 $f[l, r]$，为区间 $[l, r]$ 能够通过操作得到的子序列数。

设 $[l, r]$ 内最小元素的下标为 $p$。

如果只考虑 $[l, r]$ 内部的所有情况，因为无论怎么操作 $a[p]$ 都无法被删除，所以有 $f[l][r] = f[l][p - 1] \cdot f[p + 1][r]$。

考虑外部元素对 $f[l][r]$ 的贡献。

显然，任意一个比 $a[p]$ 大的数都不能使 $[l,r]$ 内有新的子序列出现。

如果 $\exists i < l$，$a[i] < a[p]$，那么我们可以把 $[l,p]$ 删掉，剩下 $[p + 1, r]$，新贡献为 $f[p + 1][r]$。

如果 $\exists j > r$，$a[j] < a[p]$，那么我们可以把 $[p,r]$ 删掉，剩下 $[l, p - 1]$，新贡献为 $f[l][p - 1]$。

如果上述 $i,j$ 都存在，我们发现两者重复计算了 $[l,r]$ 全部删掉的方案，则 $f[l][r]$ 减一。

考虑递归边界。

如果 $l > r$，只存在空集这一种方案。

如果 $l = r$ 且左右两边至少有一个小于 $a[l]$ 的元素，则有 $\phi$ 和 $a[l]$ 两种，否则只有 $a[l]$ 一种。

#### code

其中 $f[i][j]$ 存的是 $[i, i + 2^j - 1]$ 内最小元素的位置。

$L\_less$ 表示左边是否存在比区间最小值小的元素，$R\_less$ 表示右边是否存在比区间最小值小的元素。

```c++
void init() {
	for(int i = 1; i <= n; ++ i) f[i][0] = i;
	for(int j = 1; j < 20; ++ j) {
		for(int i = 1; i + (1 << j) - 1 <= n; ++ i) {
			if(a[f[i][j - 1]] < a[f[i + (1 << j - 1)][j - 1]]) f[i][j] = f[i][j - 1];
			else f[i][j] = f[i + (1 << j - 1)][j - 1];
		}
	}
}

int get_pos(int l, int r) {
	int len = log2l(r - l + 1);
	if(a[f[l][len]] < a[f[r - (1 << len) + 1][len]]) return f[l][len];
	else return f[r - (1 << len) + 1][len];
}

ll get_val(int l, int r, bool L_less, bool R_less) {
	if(l > r) return 1;
	if(l == r && (L_less || R_less)) return 2;
	if(l == r) return 1;
	
	int p = get_pos(l, r);
	ll left = get_val(l, p - 1, L_less, true);
	ll right = get_val(p + 1, r, true, R_less);
	
	ll ret = left * right % P;
	if(L_less) ret += right;
	if(R_less) ret += left;
	if(L_less && R_less) -- ret;
	return (ret % P + P) % P;
}

void solve() {
	cin >> n;
	for(int i = 1; i <= n; ++ i) cin >> a[i];
	init();
	cout << get_val(1, n, 0, 0) << '\n';
}
```



---

## 作者：Erica_N_Contina (赞：6)

## 思路

考虑如果一个数字被保留了，那么要么这个数字是全局最小值，要么还存在比它更小的数字。换一个说法，就是最后的序列 $[q_1,\dots,q_k]$，若 $q_i,q_{i+1}$ 之间原来有数 $d_1,\dots,d_l$ ，那么这些数字一定比 $q_i$ 或者 $q_{i+1}$ 大。这是很显然的，否则要么 $q_i$ 或者 $q_{i+1}$ 会被删掉，要么 $d_1,\dots,d_l$ 中会有至少一个数字没有被删。

那么我们定义 $f_i$ 为考虑到第 $i$ 个数，且 $p_i$ 必须被保留时的方案数。

- 若 $p_i$ 是前缀最小值，即它前面的数都比它大，那么可以最后只剩下它一个数字，这里有一种方案。

- 考虑更加普适的情况是 $p_i$ 是前面一些被删除的数字的右边的那个没有被删的数字。这是我们要满足那些被删的数字的两旁没有被删除的数字（即上面所说的 $q_i$ 或者 $q_{i+1}$）有一个比它小。

首先考虑一定可以转移过来的地方。记 $p_i$ 左边第一个比它小的数的下标为 $l_i$，那么一定可以从 $l_i+1\sim i-1$ 转移过来。因为 $p_{l_i+1\sim i-1}$ 这些数都大于 $p_i$，满足上面的条件。这里有一个误区就是假设我们从 $j,j\in [l_i+1,i-1]$ 转移过来，那么有效的消息是 $p_{j+1\sim i-1}$ 都大于 $p_i$，因为此时 $p_j$ 也是被保留的。

那么 $l_i$ 之前呢？若 $j<l_i$，很显然就说明 $p_{j+1\sim i-1}$ 不都大于 $p_i$ 了，那么只能把希望寄托在 $p_j$ 身上。换一种说法就是必须保证 $p_j=\min p_{j\sim i-1}$。考虑到我们之前就求出了 $l_i$，我们可以找到符合要求的 $j$ 就是 $l_i,l_{l_i},\dots$。

为了转移方便，可以记录 $g_i=f_{l_i}+f_{l_{l_i}}+\dots$，这个在递推时维护即可，即 $g_i=f_{l_i}+g_{l_i}$。

对于求 $l_i$，我们单调栈即可。

$f_i$ 就是把那些可以转移过来的 $f_j$ 都加在一起。注意取模。

​答案就是把合法的 $f_i$ 相加，合法的定义是 $p_i$ 是后缀最小值。即用单调栈求出的 $r_i=0$。

---

```C++
#include<bits/stdc++.h>
#define rep(l,r,i) for(int i=l,END##i=r;i<=END##i;++i)
#define per(r,l,i) for(int i=r,END##i=l;i>=END##i;--i)
using namespace std;
#define int long long
#define pii pair<int,int>

#define lc(x) (x<<1)
#define rc(x) (x<<1|1)

#define rd read()
inline int read()
{
	int xx=0,ff=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') ff=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') xx=xx*10+(ch-'0'),ch=getchar();
	return xx*ff;
}
inline void write(int out)
{
	if(out<0) putchar('-'),out=-out;
	if(out>9) write(out/10);
	putchar(out%10+'0');
}

const int N=1e6+15;
const int INF=1e18+5;
const int MOD=998244353;
int n,top,stk[N],l[N],a[N],p[N];
int ans,f[N],g[N],qz[N],r[N];
signed main(){
	int t=rd;
	while(t--){
		n=rd;
		for(int i=1;i<=n;i++)p[i]=rd;
		for(int i = 1;i <= n;i ++){
			while(top && p[stk[top]] > p[i]) top --;
			l[i]=stk[top];
			stk[++top] = i;
		}
		top=0;
		for(int i = n;i ;i --){
			while(top && p[stk[top]] > p[i]) top --;
			r[i]=stk[top];
			stk[++top] = i;
		}
		top=0;
		// for(int i=1;i<=n;i++)cerr<<l[i]<<' ';
		// cerr<<endl;
		// for(int i=1;i<=n;i++)cerr<<r[i]<<' ';
		for(int i=0;i<=n;i++)f[i]=0,g[i]=0,qz[i]=0;
		for(int i=1;i<=n;i++){
			if(!l[i])f[i]++;
			f[i]+=qz[i-1]-qz[l[i]];
			g[i]=f[l[i]]+g[l[i]];
			f[i]+=g[i];
			qz[i]=qz[i-1]+f[i];//前缀和
			f[i]%=MOD;
			g[i]%=MOD;
			qz[i]%=MOD;
		}
		for(int i=1;i<=n;i++){
			if(!r[i])ans+=f[i],ans%=MOD;
		}
		cout<<(ans%MOD+MOD)%MOD<<endl;
		ans=0;

	}
}
```




---

## 作者：蒟蒻君HJT (赞：4)

观察合法的最后剩下的数字集合的形态：假设下标为 $i_1,i_2\cdots i_k(k\geq 1)$，则 $\displaystyle\min_{i\in[1,i_1]}a_i=a_{i_1},\displaystyle\min_{i\in[i_k,n]}a_i=a_{i_k},\forall j\in[1,k-1],\displaystyle\min_{i\in[i_j,i_{j+1}]}a_i=\min(a_{i_j},a_{i_{j+1}})$，说人话就是被删掉的数必须比与它相邻的 $1/2$ 个剩下的数中的至少一个大。若不然，当它被删掉时，这些剩下的数因为比它大并且被包括了进去，也会被删掉。

因此考虑 dp。设 $f_i$ 表示考虑前 $i$ 个数，第 $i$ 个数必须保留的方案数。考虑两种转移：

1. 只留下 $a_i$ 一个，此时 $a_i$ 必须是前缀最小值才可行，$f_i\gets f_i+1$；

2. 枚举上一个留下的 $a_j(1\leq j<i)$。为了方便记 $l_i$ 表示 $a_i$ 左边第一个比它小的 $a_k$ 的下标 $k$，不存在记作 $0$；$r_i$ 表示 $a_i$ 右边第一个比它小的 $a_k$ 的下标 $k$，不存在记作 $n+1$。可以单调栈线性求出。第一种情况，$a_j>a_i$，即对于 $j\in[l_i+1,i-1]$，$f_j$ 一定可以转移过来，即 $f_i\gets f_i+\displaystyle\sum_{j=l_i+1}^{i-1}f_j$，这里需要用前缀和优化；第二种情况，$a_j<a_i$，即对于 $j<l_i$，则需要满足 $\displaystyle \min_{k\in [j,i]}a_k=a_j$，因此 $j$ 可以取 $l_i,l_{l_i},l_{l_{l_i}}\cdots$ 一直到不大于 $0$ 为止。因此再记录 $g_k=f_k+f_{l_k}+f_{l_{l_k}}+\cdots$ 就可以转移了。

注意保留的最后一个元素必须是后缀最小值，求出对应 $f$ 之和就是答案了。

时间复杂度线性。

---

## 作者：快斗游鹿 (赞：3)

## 思路

考虑分治，设 $f_{l,r}$ 表示 $[l,r]$ 中的数能产生多少种可能的序列。观察到区间的最小值一定不会被删掉，所以以最小值位置 $pos$ 为分界点分治。一种显然的想法是 $f_{l,r}=f_{l,pos-1}\times f_{pos+1,r}$。但发现跑出来答案小了，手玩样例后发现，当原数列为 $[10,2,6,3,4]$ 时，$3$ 被删掉的情况没有被统计。因为在处理 $f_{3,5}$ 时，我们默认 $3$ 会被保留，因此在处理分界点为 $2$ 时，右区间所有情况都是 $3$ 被保留的。这很好解决，只要一个区间左侧存在数小于该区间最小值，则这个最小值可以被删掉，该区间答案加上 $f_{pos+1,r}$，其含义是 $[l,pos]$ 全被更小的数删掉的方案数，右侧同理。

## 代码

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+5;
const int mod=998244353;
int T,n,a[N],f[N][22];
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return x*f;
}
void ST(){
	for(int j=1;j<=20;j++){
		for(int i=1;i+(1<<j)<=n+1;i++){
			if(a[f[i][j-1]]<a[f[i+(1<<(j-1))][j-1]]){
				f[i][j]=f[i][j-1];
			}
			else f[i][j]=f[i+(1<<(j-1))][j-1];
			//cout<<i<<" "<<j<<" "<<f[i][j]<<endl;
		}
	}
}
int ask(int l,int r){
	int k=log2(r-l+1);
	if(a[f[l][k]]<a[f[r-(1<<k)+1][k]])return f[l][k];
	return f[r-(1<<k)+1][k];
}
int solve(int l,int r){
	if(l>r)return 1;
	if(l==r){
		if(a[l]!=a[ask(1,n)])return 2;
		else return 1;
	}
	int pos=ask(l,r),lans,rans,ans=0;
	//cout<<pos<<endl;
	lans=solve(l,pos-1);
	rans=solve(pos+1,r);
	//cout<<pos<<endl;
	ans+=lans*rans;ans%=mod;
	bool lflag=0,rflag=0;
	if(l!=1&&a[ask(1,l-1)]<=a[pos])ans+=rans,lflag=1;
	if(r!=n&&a[ask(r+1,n)]<=a[pos])ans+=lans,rflag=1;
	if(lflag&&rflag)ans--;
	return (ans%mod+mod)%mod;
}
signed main(){
	//freopen("std.in","r",stdin);
	T=read();
	while(T--){
		n=read();
		for(int i=1;i<=n;i++)a[i]=read(),f[i][0]=i;
		ST();
		printf("%lld\n",solve(1,n));
	}
	return 0;
}

```


---

## 作者：impuk (赞：3)

题意：给定一个数组，每次你可以挑选两个相邻值并且删除更小的那个，问有多少可能的数组是你可能能达到的。

考虑一下如果我们想删除一个数，有什么前置条件？要么这个数旁边就有一个小的，可以直接把它删掉，要么在很远的地方有一个小的，它要跋山涉水把中间的大的全删掉，它才能被删掉。

所以解法就很自然了。从大到小枚举数，比如说是 $i$，然后维护由大于 $i$ 的数构成的区间的可能数组数量，然后分几种情况讨论一下。

1. 左边小，右边大：那么右边的区间方法数直接乘 $2$，因为我想删就删不删也没事。
2. 右边小，左边大：同上。
3. 左边小，右边小：那么 $[i,i]$ 这个区间方法数就是 $2$。
4. 左边大，右边大：
   - 讨论一下。假设左边和右边可能数分别为 $a$ 和 $b$，假设 $i$ 我删掉了，那么 $a$ 和 $b$ 必须得死一个，然后减去一个左右全删的重复值，是 $a+b-1$。
   - 假设 $i$ 我不删，那么答案就是朴素的 $a\times b$。

需要注意第四种情况左右两边并不总是有更小的值能删，因此还要特判一下。此外边界也需要特判，区间和值的关联可以用珂朵莉树维护。

然后我们就得到了一个和所有人不一样，长得很丑还不好写的代码。

```
#include "bits/stdc++.h"
using namespace std;
#pragma GCC optimize("Ofast","inline","-ffast-math")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")
 
#define int long long
#define MOD 998244353
int a[300002],inv[300002],n;
void Delta() {
   cin >> n;
   for(int i=1;i<=n;++i) cin >> a[i];
   a[0]=a[n+1]=n+1;
   {
      vector<int> Q;
      for(int i=1;i<=n;++i) Q.push_back(a[i]);
      sort(Q.begin(),Q.end());
      for(int i=1;i<=n;++i) {a[i]=lower_bound(Q.begin(),Q.end(),a[i])-Q.begin()+1;inv[a[i]]=i;}
   }
   set<array<int,3>> Q;
   for(int d=n;d>=2;--d) {
      int i=inv[d];
      if(i==1) {
         if(a[2]>a[1]) {
            array<int,3> t=*Q.begin();
            Q.erase(t);
            Q.insert({t[0]-1,t[1],t[2]+1});
         } else
            Q.insert({1,1,2});
      } else {
         if(i==n) {
            if(a[n-1]>a[n]) {
               array<int,3> t=*prev(Q.end());
               Q.erase(t);
               Q.insert({t[0],t[1]+1,t[2]+1});
            } else
               Q.insert({n,n,2});
         } else {
            if(a[i+1]>a[i]&&a[i-1]<a[i]) {
               array<int,3> t=*Q.lower_bound({i,0,0});
               Q.erase(t);
               Q.insert({t[0]-1,t[1],t[2]*2%MOD});
            } else
            if(a[i+1]<a[i]&&a[i-1]>a[i]) {
               array<int,3> t=*prev(Q.lower_bound({i,0,0}));
               Q.erase(t);
               Q.insert({t[0],t[1]+1,t[2]*2%MOD});
            } else
            if(a[i+1]<a[i]&&a[i-1]<a[i])
               Q.insert({i,i,2});
            else {
               array<int,3> l=*prev(Q.lower_bound({i,0,0})),r=*Q.lower_bound({i,0,0});
               Q.erase(l);Q.erase(r);
               if(r[1]==n)
                  Q.insert({l[0],r[1],(l[2]*r[2]+r[2])%MOD});
               else if(l[0]==1)
                  Q.insert({l[0],r[1],(l[2]*r[2]+l[2])%MOD});
               else
                  Q.insert({l[0],r[1],(l[2]*r[2]+l[2]+r[2]+MOD-1)%MOD});
            }
         }
      }
   }
   int val=1;
   for(array<int,3> i:Q)
      val*=i[2];
   cout << val%MOD << endl;
}
signed main() {
   ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
   int T=1; cin >> T;
   while(T--) Delta();
}
```

---

## 作者：Struct_Sec (赞：2)

考虑暴力 dp。

设 $dp_{i}$ 表示将 $i$ 前面选完后最后一个是 $i$ 的不同的序列个数。

首先我们来考虑暴力 $dp$，每次能从 $j$ 转移过来，当且仅当 $p_{j}\sim p_{i}$ 中的数能被分成 $p_{j}\sim p_{k}$ 和 $p_{k+1}\sim p_{i}$ 使得 $p_{j}\sim p_{k}$ 均大于等于 $p_{j}$，$p_{k+1}\sim p_{i}$ 均大于等于 $p_{i}$。

我们考虑转换一下条件，设 $l_{i}$ 表示 $i$ 左边第一个小于 $p_{i}$ 的数的位置 $+1$（若没有，则是 1），$r_{i}$ 同理。此时我们发现 $j$ 能转移到 $i$ 的条件变为 $r_{j}\ge l_{i}-1$。

显然这个东西我们可以用线段树/树状数组维护，每次查询 $l_{i}-1$ 以后的值，再在 $r_{i}$ 加上本次的答案。

需要注意的是，若 $l_{i}=1$，即左边没有比当前点值小的点，则这个点的初始答案为 $1$，若 $r_{i}=n$，则总答案可以加上这个点的答案。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5,mod=998244353;
int t;
int n,a[N];
int tr[N<<2],lz[N<<2],sz[N<<2];
void build(int l,int r,int x){
	sz[x]=r-l+1;
	tr[x]=lz[x]=0;
	if(l==r) return;
	int mid=l+r>>1;
	build(l,mid,x<<1),build(mid+1,r,x<<1|1);
}
void pushdown(int x){
	if(lz[x]){
		tr[x<<1]+=sz[x<<1]*lz[x];
		tr[x<<1|1]+=sz[x<<1|1]*lz[x];
		lz[x<<1]+=lz[x];
		lz[x<<1|1]+=lz[x];
		tr[x<<1]%=mod,lz[x<<1]%=mod;
		tr[x<<1|1]%=mod,lz[x<<1|1]%=mod;
		lz[x]=0;
	}
}
void upt(int l,int r,int fl,int fr,int k,int x){
	if(fl<=l && r<=fr){
		tr[x]+=sz[x]*k%mod;
		lz[x]+=k;
		tr[x]%=mod,lz[x]%=mod;
		return;
	}
	int mid=l+r>>1;
	pushdown(x);
	if(fl<=mid) upt(l,mid,fl,fr,k,x<<1);
	if(fr>mid) upt(mid+1,r,fl,fr,k,x<<1|1);
	tr[x]=tr[x<<1]+tr[x<<1|1];
	tr[x]%=mod;
}
int query(int l,int r,int fl,int fr,int x){
	if(fl>fr) return 0;
	if(fl<=l && r<=fr){
		return tr[x];
	}
	int mid=l+r>>1,sum=0;
	pushdown(x);
	if(fl<=mid) sum+=query(l,mid,fl,fr,x<<1);
	if(fr>mid) sum+=query(mid+1,r,fl,fr,x<<1|1);
	return sum%mod;
}
int st[N][25],lg[N];
int l[N],r[N];
signed main(){
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++) for(int j=0;j<=20;j++) st[i][j]=0;
		for(int i=1;i<=n;i++) cin>>a[i],st[i][0]=a[i];
		for(int i=1;i<=20;i++){
			for(int j=1;j<=n-(1<<i)+1;j++){
				st[j][i]=min(st[j][i-1],st[j+(1<<(i-1))][i-1]);
			}
		}
		for(int i=2;i<=n;i++) lg[i]=lg[i>>1]+1;
		for(int i=1;i<=n;i++){
			int lf=1,rg=i,pos=1;
			while(lf<=rg){
				int mid=lf+rg>>1;
				int x=lg[i-mid+1];
				if(min(st[mid][x],st[i-(1<<x)+1][x])>=a[i]) pos=mid,rg=mid-1;
				else lf=mid+1;
			}
			l[i]=pos;
			lf=i,rg=n,pos=n;
			while(lf<=rg){
				int mid=lf+rg>>1;
				int x=lg[mid-i+1];
				if(min(st[i][x],st[mid-(1<<x)+1][x])>=a[i]) pos=mid,lf=mid+1;
				else rg=mid-1;
			}
			r[i]=pos;
		}
		build(1,n,1);
		int ans=0;
		int lt=0;
		for(int i=1;i<=n;i++){
			int x=query(1,n,max(l[i]-1,1ll),n,1);
			if(l[i]==1) x++;
			if(r[i]==n) ans+=x,ans%=mod;
			upt(1,n,r[i],r[i],x,1);
		}
		cout<<ans<<endl;
	}
	return 0;
}

```


---

## 作者：spider_oyster (赞：2)

设 $f_i$ 表示以 $a_i$ 结尾的子序列个数。

假设我们要从 $f_j$ 转移到 $f_i$，考虑需要满足什么条件。

如果 $\min\{a_i,a_j\}=\min\limits_{i\leq k \leq j}\{a_k\}$，那么可以接上。

考虑分两种情况，$a_i$ 为区间最小值，用单调栈维护从 $i$ 往左边第一个位置 $l_i$，满足 $a_{l_i}<a_i$，那么区间左端点为 $[l_i+1,i]$ 的区间都满足这个条件。

对于 $a_j$ 为区间最小值，满足条件的 $j$ 就是当前单调栈里的剩余所有元素。设当前单调栈元素 $f$ 之和为 $sum$，那么有：

$f_i=\sum\limits_{j=l_i+1}^{i-1} f_j+sum$

注意，当当前单调栈为空的时候， $a_i$ 可以作为一个子序列的开头。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N=3e5+5,p=998244353;
int n,m,top,a[N],f[N],s[N],stk[N];

inline int rd()
{
    int x=0;char c=getchar();
    for(;!isdigit(c);c=getchar());
    for(; isdigit(c);c=getchar()) x=(x<<3)+(x<<1)+(c^48);
    return x;
}

void solve()
{
    n=rd();
    for(int i=1;i<=n;i++) a[i]=rd();
    int sum=0;top=0;
    for(int i=1;i<=n;i++)
    {
        while(top&&a[stk[top]]>a[i]) sum=(sum-f[stk[top]]+p)%p,top--;
        f[i]=(sum+s[i-1]-s[stk[top]]+(top==0)+p)%p;
        s[i]=(s[i-1]+f[i])%p;
        stk[++top]=i,sum=(sum+f[i])%p;
    }
    cout<<sum<<'\n';
}

signed main()
{
    int t=rd();
    while(t--) solve();
}
```

---

## 作者：wosile (赞：2)

题目已经几乎摆明了告诉你要 dp，那就试试 dp 吧。

套路地设 $f_i$ 表示考虑前 $i$ 个数，留下第 $i$ 个数时有多少种可能的序列。

对于每个可以转移到 $f_i$ 的 $f_j(j<i)$，$(j,i)$ 中的所有数都需要能被 $p_i$ 和 $p_j$ 删掉，即对于每一个 $j<k<i$，都有 $p_k>p_i$ 或 $p_k>p_j$，或者说 $\{p_j,p_{j+1},\cdots,p_i\}$ 的最小值要么是 $p_i$ 要么是 $p_j$。

第一种情况，最小值是 $p_i$，那么在 $i$ 左边找到最靠右的比 $p_i$ 小的数 $p_l$，只要 $j>l$ 的话 $p_i$ 就是最小值。这部分可以用单调栈和前缀和处理。

第二种情况，最小值是 $p_j$，意味着 $j$ 往右所有数都比 $p_j$ 大，这样的所有 $j$ 可以用单调栈维护他们 $f_j$ 的和。

还有一种情况就是只留下单独 $p_i$ 一个数，判断 $p_i$ 是否是前缀最小即可。

更新答案时，显然所有后缀最小值所在的位置可以被统计到答案里，因为这些位置的数可以删掉他们往后的所有数从而满足 $f_i$ 的定义。

时间复杂度 $O(n)$，好题。

```cpp
#include<bits/stdc++.h>
using namespace std;
int f[300005],a[300005];
#define mod 998244353
int st[300005],top=0;
int pre[300005];
void solve(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	f[0]=1;
	pre[1]=1;
	int sum=0;
	a[0]=0x3f3f3f3f;
	top=0;
	for(int i=1;i<=n;i++){
		while(top>0 && a[st[top]]>a[i])sum=(sum-f[st[top--]]+mod)%mod;
		f[i]=(pre[i-1]-pre[st[top]]+mod)%mod;//情况1
		if(top==0)f[i]=(f[i]+1)%mod;//单独一个数
		f[i]=(f[i]+sum)%mod;//情况2
		sum=(sum+f[i])%mod;
		st[++top]=i;
		pre[i]=(pre[i-1]+f[i])%mod;//前缀和
	}
	int mn=inf,ans=0;
	for(int i=n;i>=1;i--){
		if(a[i]<mn)ans=(ans+f[i])%mod;//后缀最小可以被计入答案
		mn=min(mn,a[i]);
	}
	printf("%d\n",ans);
}
int main(){
	int T;
	scanf("%d",&T);
	while(T--)solve();
	return 0;
}
//quod erat demonstrandum
```

---

## 作者：qscisQJing (赞：1)

# 前置知识
dp，单调栈优化

# 题目分析
看到这个形式首先考虑 dp。设 $ f_i $ 表示对 $ 1 $ 到 $ i $ 的序列，由 $ i $ 这个位置结尾的数量。

暴力 $ O(n^2) $ 去维护它是很简单的，只要 $ j $ 满足 $ 1\le j \le i-1 $ 且 $ \min_{j+1 \le k \le i-1}{p_k} $ 不比 $ \min(p_j,p_i) $ 要小，我们就可以让 $ f_i $ 加上 $ f_j $。用 st 表维护一下最值就可以做到 $ O(1) $ 一次转移。

现在考虑优化这个转移的过程。把 $ i $ 从 $ 1 $ 到 $ n $ 扫一遍这个过程较难优化，我们考虑优化求 $ f_i $ 的这个过程。

不难发现，如果用单调栈分别求出每个 $ i $ 的 $ l_i $ 和 $ r_i $，$ l_i $ 到 $ i-1 $ 的这一段是一定满足转移的限制条件的，可以直接用前缀和 $ O(1) $ 加上。

接着是由 $ 1 $ 到 $ l_i-1 $ 这一段。这时可以重新考虑一下那个最值条件。因为 $ p_{l_i}<p_i $，所以只需要 $ j<\min_{j+1\le k \le l_i-1} $ 就可以转移了。记录一下**不可转移**的值的和，然后每次更新 $ f_i $ 的时候顺便更新这个东西的值就可以了。

具体来讲，我们用 $ sum_i $ 表示 $ 1 $ 到 $ i $ 的**不能转移**的 $ f $ 的和，然后令 $ sum_i=sum_{l_i}+pre_{i-1}-pre_{l_i} $。前缀和 $ pre $ 需要在每次求完 $ f_i $ 后加一下。而在求 $ f_i $ 时，把 $ 1 $ 到 $ l_i $ 这一段减去即可。

现在我们已经可以 $ O(n) $ 求出整个 $ f $ 数组了。统计答案时，只能在 $ r_i=n+1 $ 时加上相应的 $ f_i $，此时右端点 $ i $ 才可以覆盖右边 $ i $ 到 $ n $ 的整个序列，作为操作后的真正的右端点。

最后注意一下初值和取模就可以过了这道题了。

# AC代码
```
#include<bits/stdc++.h>
using namespace std;
const int MAXN=3e5+5,MOD=998244353;
#define ll long long
int l[MAXN],r[MAXN],p[MAXN];
ll f[MAXN],sum[MAXN],pre[MAXN];
int stk[MAXN],top;
int main()
{
	int T;cin>>T;
	while(T--)
	{
		int n;cin>>n;
		for(int i=1;i<=n;i++)
			scanf("%d",p+i),pre[i]=f[i]=sum[i]=0;
		top=0;
		for(int i=1;i<=n;i++)
		{
			while(top&&p[stk[top]]>p[i])r[stk[top]]=i,top--;
			l[i]=stk[top];stk[++top]=i;
		}
		while(top)r[stk[top--]]=n+1;
		pre[0]=0;
		f[0]=1;
		for(int i=1;i<=n;i++)
		{
			f[i]=pre[i-1]-sum[l[i]];if(l[i]==0)f[i]++;
			pre[i]=pre[i-1]+f[i];
			sum[i]=sum[l[i]]+pre[i-1]-pre[l[i]];
			f[i]%=MOD,pre[i]%=MOD,sum[i]%=MOD;
		}
		ll ans=0;
		for(int i=1;i<=n;i++)
			if(r[i]==n+1)ans+=f[i];
		cout<<(ans+1ll*MOD*MOD)%MOD<<endl;
	}
	return 0;
}
```


---

## 作者：masonpop (赞：1)

怎么题解全是神仙做法，写一发自己赛时的数据结构优化 DP。自认为更好想？

考虑如果要判定留下的位置是 $p_1,p_2,\cdots,p_k$ 怎么做。注意到，对于相邻两个位置 $p_i,p_{i+1}$，其中间的数能被全部删掉的充要条件是 $\min\limits_{j=p_i+1}^{p_{i+1}-1}a_j>\min(p_i,p_{i+1})$。首尾可能需要特判一下。

那么就有一个很显然的 DP：设 $f_i$ 表示以 $i$ 结尾的剩余序列有多少个合法。转移就枚举上一个满足上述条件的位置 $j$，直接 $f_i\leftarrow f_j+1$ 即可。

这样做是 $O(n^2)$ 的，考虑优化。我们设当前位置为 $i$，然后对于上一个位置 $j$ 分类：

① $a_i<a_j$。此时有对任意 $t\in[j,i-1]$，$a_i<a_t$。因此可以用二分结合 ST 表 $O(\log n)$ 处理每个数之前极长的比它大的段，再结合前缀和优化就能快速转移了。

② $a_i>a_j$。此时有对任意 $t\in [j+1,i]$，$a_t>a_j$。同样可以处理出这样的 $j$ 后面的极长的比它大的段，树状数组统计贡献即可。

有一些小细节，比如首尾能否全部消去等，可以看代码。

综上时间复杂度 $O(n\log n)$。[代码](https://codeforces.com/contest/1913/submission/237799405)。

---

