# Iva & Pav

## 题目描述

Iva and Pav are a famous Serbian competitive programming couple. In Serbia, they call Pav "papuca" and that's why he will make all of Iva's wishes come true.

Iva gave Pav an array $ a $ of $ n $ elements.

Let's define $ f(l, r) = a_l \ \& \ a_{l+1} \ \& \dots \& \ a_r $ (here $ \& $ denotes the [bitwise AND operation](http://tiny.cc/bitwise_and)).

Note that $ f(l, r) $ is not defined when $ l>r $ .

Iva also gave Pav $ q $ queries.

Each query consists of 2 numbers, $ k $ and $ l $ , and she wants Pav to find the largest index $ r $ ( $ l \le r \le n $ ), such that $ f(l, r) \ge k $ .

Pav wants to solve this problem fast because he doesn't want to upset Iva. He needs your help.

## 说明/提示

In the first test case $ n=5 $ , and the array $ a = [15, 14, 17, 42, 34] $

The first query asks for the biggest index $ r $ such that the $ f(1, r) \ge 7 $ .

 $ f(1,1) = 15, \ f(1, 2) = 14, \ f(1,3)=0 \ f(1, 4)=0 \ f(1, 5)=0 $ , so $ r=2 $ is the answer.

The second query asks for $ f(2, r) \ge 15 $ . Since such $ r $ doesn't exist, the answer is $ -1 $ .

The third query asks for $ f(4, r) \ge 5 $ . $ f(4, 4) = 42, \ f(4, 5) = 34 $ , so $ r=5 $ is the answer.

In the second test case $ n=5 $ , and the array $ a= [7, 5, 3, 1, 7] $ .

For the first query, $ f(1, r) \ge 7 $ .

 $ f(1, 1)=7, \ f(1, 2)=5, \ f(1, 3) = 1, \ f(1,4) = 1, \ f(1, 5)=1 $ , so the answer to this query is $ 1 $ .

For the second query, $ f(5, r) \ge 7 $ .

 $ f(5, 5) = 7 $ , so the answer is $ 5 $ .

For the third query, $ f(2, r) \ge 3 $ .

 $ f(2, 2) = 5, \ f(2, 3) = 1, \ f(2, 4) = 1, \ f(2, 5) = 1 $ , so the answer is $ 2 $ .

## 样例 #1

### 输入

```
3
5
15 14 17 42 34
3
1 7
2 15
4 5
5
7 5 3 1 7
4
1 7
5 7
2 3
2 2
7
19 20 15 12 21 7 11
4
1 15
4 4
7 12
5 7```

### 输出

```
2 -1 5 
1 5 2 2 
2 6 -1 5```

# 题解

## 作者：Register_int (赞：10)

> 在倍增结构上二分你玩原神玩多了？——cjld

考虑倍增。预处理出所有 $[l,l+2^k)$ 区间的按位与，查询时从高到低考虑长度的每一位来拓展右端点即可。

容易发现这玩意就是 ST 表，所以 ST 表不需要二分。

最优解 rk3。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 2e5 + 10;

int st[18][MAXN], lg[MAXN];

inline 
void init(int n, int *a) {
	for (int i = 1; i <= n; i++) st[0][i] = a[i];
	for (int i = 1; i <= lg[n]; i++) {
		for (int j = 1; j + (1 << i) - 1 <= n; j++) {
			st[i][j] = st[i - 1][j] & st[i - 1][j + (1 << i - 1)];
		}
	}
}

int t, n, m, a[MAXN];

int main() {
    for (int i = 2; i <= 2e5; i++) lg[i] = lg[i >> 1] + 1;
    for (scanf("%d", &t); t--;) {
    	scanf("%d", &n);
    	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    	init(n, a), scanf("%d", &m);
    	for (int l, k, r, x; m--;) {
    		scanf("%d%d", &l, &k);
    		if (a[l] < k) { puts("-1"); continue; }
    		r = l, x = INT_MAX;
    		for (int i = lg[n]; ~i; i--) {
    			if (r + (1 << i) - 1 <= n && (x & st[i][r]) >= k) x &= st[i][r], r += 1 << i;
			}
    		printf("%d\n", r - 1);
		}
	}
}
```

---

## 作者：WaterSun (赞：6)

~~CF 是没题考了吧，每场都出二进制拆位。~~

# 思路

首先我们可以二分 $r$，因为 $r$ 越大，按位与一定只会小于等于 $r$ 小的情况。

那么，我们可以用 $num_{i,j}$ 记录 $a_j$ 第 $i$ 位的二进制情况。

如果我们对 $num_{i,j}$ 做一个前缀和，如果 $num_{i,r} - num_{i,l - 1} = r - l + 1$，说明 $[l,r]$ 中第 $i$ 位都是 $1$，那么它对按位与的贡献就有 $2^i$。

# code

```cpp
#include <bits/stdc++.h>
#define re register
#define int long long

using namespace std;

const int N = 2e5 + 10,M = 34;
int T,n,q;
int arr[N];
int num[M][N];

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

inline bool check(int l,int r,int k){
	int sum = 0;
	for (re int bit = 0;bit <= 30;bit++){
		int cnt = num[bit][r] - num[bit][l - 1];
		if (cnt == r - l + 1) sum += (1ll << bit);
	}
	return (sum >= k);
}

signed main(){
	T = read();
	while (T--){
		n = read();
		for (re int i = 0;i <= 30;i++){
			for (re int j = 1;j <= n;j++) num[i][j] = 0;
		}
		for (re int i = 1;i <= n;i++){
			arr[i] = read();
			for (re int bit = 0;bit <= 30;bit++){
				if (arr[i] >> bit & 1) num[bit][i] = 1;
				num[bit][i] += num[bit][i - 1];
			}
		}
		q = read();
		while (q--){
			int l,L,r = n,x;
			L = l = read();
			x = read();
			while (l < r){
				int mid = l + r + 1 >> 1;
				if (check(L,mid,x)) l = mid;
				else r = mid - 1;
			}
			if (check(L,l,x)) printf("%lld ",l);
			else printf("-1 ");
		}
		puts("");
	}
	return 0;
}
```

---

## 作者：luqyou (赞：5)

# 题意

给出一个序列 $a$，有 $q$ 次询问，每次询问给出两个数 $l,k$，要求回答最大的 $r \le n$ 使得 $a_l \& a_{l+1} \& \dots \& a_r \ge k$。

首先我们注意到 $\&$ 运算是有单调性的，所以考虑二分。

然后考虑快速维护 $\&$ 运算。不难发现，区间按位与是一个可重复贡献问题（也就是说你将一个区间按位与起来的值再与上区间里的任何数答案都不变），所以可以使用 ST 表维护。

# code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
int n,m,x[maxn],st[maxn][20];
int query(int l,int r){
	int k=log2(r-l+1);
	return (st[l][k]&st[r-(1<<k)+1][k]);
}
void solve(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x[i];
		st[i][0]=x[i];
	}
	for(int i=1;(1<<i)<=n;i++){
		for(int j=1;j<=n;j++){
			if(j+(1<<i)-1<=n){
				st[j][i]=(st[j][i-1]&st[j+(1<<(i-1))][i-1]);
			}
		}
	}
	cin>>m;
	while(m--){
		int l,k;
		cin>>l>>k;
		if(x[l]<k){
			cout<<-1<<" ";
			continue;
		}
		int L=l,R=n+1;
		while(L<R){
			int mid=L+R>>1;
			if(query(l,mid)<k){
				R=mid;
			}
			else{
				L=mid+1;
			}
		}
		cout<<L-1<<" ";
	}
	cout<<endl;
}
int main(){
 	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int t;
	cin>>t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：_299817_ (赞：2)

## Part 0: 前言
赛时 D 题用 rope 被卡了很久，这道题明明能做出来的结果并没有。

## Part 1：主要思路
首先，我们要明确按位与运算的一个性质，就是说：$a_1\ \& \ a_2 \ \& \dots \& \ a_n \le a_1 \ \& \ a_2 \  \& \dots \& \ a_n \ \& \ a_{n+1}$，其中，对于任意的 $i$，$a_i$ 可以是任意正整数。

那么，我们就不难发现，对于固定的 $l$，当 $r$ 越大，$f(l, r)$ 就越小，满足单调不增的性质，于是我们就考虑二分查找。

那么，我们还需要解决一个问题：就是求区间的所有数的按位与运算的值，我们可以用线段树解决。

## Part 2：完整代码
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstdlib>
#include<cmath>
#include<iomanip>
#include<cstring>
#include<unordered_map>
#include<map>
#include<queue>
#include<stack>
#include <climits>
#define sort stable_sort
#define map unordered_map
using namespace std;
typedef long long ll;

struct node{ // 线段树的节点
    int l, r; // 左端点和右端点
    int val; // 值
};

int T; // 数据组数
int n;
int a[200010];
node tree[800010]; // 线段树记得开四倍空间

void build(int l, int r, int now){ // 建树
    tree[now].l = l, tree[now].r = r;
    if(l == r){
        tree[now].val = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, now * 2);
    build(mid + 1, r, now * 2 + 1);
    tree[now].val = tree[now * 2].val & tree[now * 2 + 1].val;
}

int query(int l, int r, int now){ // 查询
    if(l <= tree[now].l && tree[now].r <= r){
        return tree[now].val;
    }
    int ans = INT_MAX;
    int mid = (tree[now].l + tree[now].r) >> 1;
    if(l <= mid){
        ans &= query(l, r, now * 2);
    }
    if(r > mid){
        ans &= query(l, r, now * 2 + 1);
    }
    return ans;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> T;
    while(T--){
        cin >> n;
        for(int i = 1; i <= n; i++){
            cin >> a[i];
        }
        build(1, n, 1);
        int q;
        cin >> q;
        while(q--){
            int l, k;
            cin >> l >> k;
            int left = l;
            int right = n;
            int mid;
            int ans = -1; // 记录答案
            while(left <= right){ // 二分查找
                mid = (left + right) >> 1;
                if(k <= query(l, mid, 1)){ // 题目条件
                    left = mid + 1;
                    ans = max(ans, mid);
                }else{
                    right = mid - 1;
                }
            }
            // 记得特判无解的情况
            if(query(l, ans, 1) < k){ // 如果还不满足
                cout << -1 << " "; // 输出 -1
                continue;
            }
            cout << ans << " "; // 输出答案
        }
        cout << endl;
    }
    return 0;
}
```


---

## 作者：AlicX (赞：2)

## Sulotion

为什么题解区全是线段树之类的？

首先我们统计出 $cnt_{i,j}$ 表示 $1 \sim i$ 中第 $j$ 位（二进制下）的个数。

然后我们发现对于一个区间 $(l,r)$，发现如果 $a_l \And a_{l+1} \And \dots \And a_{r+1} \geq k$，所以 $a_l \And a_{l+1} \And \dots \And a_r \geq k$，所以答案具有单调性，考虑二分。

对于 $mid$，它成立的条件是 $cnt_{mid,j}-cnt_{l-1,j}=mid-j+1$，因为如果要成立，每一位都应该是 $1$。

```cpp
#include<bits/stdc++.h> 
#define int long long 
#define x first
#define y second
#define il inline 
#define debug() puts("-------")
using namespace std;
typedef pair<int,int> pii;
const int N=2e5+10,M=31; 
int n,m; 
int a[N]; 
pii q[N]; 
int cnt[N][M];  
il bool check(int mid,int l,int k){
	int sum=0; 
	for(int j=0;j<=30;j++) if((cnt[mid][j]-cnt[l-1][j])==mid-l+1) sum+=(1ll<<j);
	return (sum>=k); 
}
il void work(){	
	scanf("%lld",&n);  
	for(int i=1;i<=n;i++) for(int j=0;j<=30;j++) cnt[i][j]=0;
	for(int i=1,x;i<=n;i++){ 
		scanf("%lld",&x); 
		for(int j=0;j<=30;j++){
			if((x>>j)&1) cnt[i][j]=1; 
			cnt[i][j]+=cnt[i-1][j]; 	
		}  
	} scanf("%lld",&m); 
	while(m--){ 
		int x,k; 
		scanf("%lld%lld",&x,&k); 
		int l=x,r=n; 
		while(l<r){ 
			int mid=l+r+1>>1;    
			if(check(mid,x,k)) l=mid; 
			else r=mid-1; 
		} if(check(l,x,k)) printf("%lld\n",l); else puts("-1"); 
	} 
} 
signed main(){ 
	int T; cin>>T; 
	while(T--) work(); 
	return 0;
} /* */
```


---

## 作者：LCat90 (赞：1)

**性质 1**： $a$ 和 $b$ 的按位与值小于等于 $a,b$。

**性质 2**： 当且仅当 $a_l$ 到 $a_r$ 的第 $k$ 为均为 $1$，从 $a_l$ 到 $a_r$ 的按位与和的第 $k$ 位为 $1$。

性质 1 告诉我们单调性，即可以二分；而性质 2 则直接告诉我们 ``check`` 怎么写，即拆位维护前缀和，一个为 $x$ 为 $1$ 当且仅当 $1$ 的个数等于区间长度。

时间复杂度为 $O(n\log^2 n)$。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 4e5 + 5;
int t, n, a[N], q, pre[N][40];
int check(int l, int r) {
	int sum = 0;
	for(int i = 0;i <= 31; ++i) sum += (1 << i) * (pre[r][i] - pre[l - 1][i] == r - l + 1);
	return sum;
} int read();
signed main() {
	cin >> t;
	while(t--) { 
		cin >> n;
		for(int i = 1;i <= n; ++i) {
			a[i] = read();
			for(int j = 0;j <= 31; ++j) {
				bool bit = (1 & (a[i] >> j));
				pre[i][j] = pre[i - 1][j] + bit;
			} 
		}
		cin >> q;
		for(int i = 1, k, x;i <= q; ++i) {
			cin >> k >> x;
			int l = k, r = n;
			while(l < r) {
				int mid = l + r + 1 >> 1;
				if(check(k, mid) >= x) l = mid;
				else r = mid - 1; 
			}
			if(check(k, l) < x) cout << "-1 ";
			else cout << l << " "; 
		}
	}  
	return 0;
}

/*
按位计算 
*/

int read() {
	char c; int sum = 0; while(c < '0' or c > '9') c = getchar();
	while(c >= '0' and c <= '9') sum = (sum << 3) + (sum << 1) + (c ^ 48), c = getchar();
	return sum;	
}
```

---

## 作者：COsm0s (赞：1)

更好的体验：[$\texttt{cnblogs}$](https://www.cnblogs.com/cornulsyhj/p/17740433.html)。

## $Solution$

比较典的题。

我们知道与运算的一个性质：对于任意自然数 $x, y$ 都有 $x\&y\leq\max(x,y)$，读者可以自行证明，过程并不繁琐。

那么对于一段区间 $[l,r]$，当 $l$ 固定，$r$ 不断变大时，$f(l,r)$ 会呈单调不上升的趋势。

这就满足了二分的单调性。此时整个算法的复杂度在 $\Theta(Tq\log n)$ 级别，而最后的步骤就是求 $f(l,r)$。

所以我们的问题变成了如何在 $\Theta(\log n)$ 时间范围内求 $f(l,r)$，这是时限内能满足的最大时间。

这是典型的区间问题，很自然的想到 ST 表或是线段树。

那么问题得解。最终时间复杂度 $\Theta(Tq\log^2 n)$。

## $Code$
```cpp
#define int long long
const int N = 1e6 + 5;
namespace Jelly {
	int n, q;
	int tree[N << 2], a[N];
	void Build(int x, int l, int r) {
		if(l == r) {
			tree[x] = a[l];
			return ;
		}
		int mid = l + r >> 1;
		Build(x << 1, l, mid);
		Build(x << 1 | 1, mid + 1, r);
		tree[x] = tree[x << 1] & tree[x << 1 | 1];
	}
	int Query(int l, int r, int x, int L, int R) {
		if(r < L || l > R) return INT_MAX;
		if(L <= l && r <= R) return tree[x];
		int mid = l + r >> 1;
		return Query(l, mid, x << 1, L, R) & Query(mid + 1, r, x << 1 | 1, L, R);
	}
	int main() {
		Read(n);
		for(int i = 1; i <= n; i ++) Read(a[i]);
		Build(1, 1, n);
		Read(q);
		while(q --) {
			int lft, k;
			Read(lft, k);
			int l = lft, r = n;
			if(a[lft] < k) {
				Write(-1, ' ');
				continue;
			}
			while(l < r) {
				int mid = l + r + 1 >> 1;
				if(Query(1, n, 1, lft, mid) >= k) l = mid;
				else r = mid - 1;
			}
			Write(l, ' ');
		}
		Writeln();
		return 0;
	}
}
signed main() {
	int T = 1;
	Read(T);
	while(T --) Jelly::main();
	return 0;
}
```

---

## 作者：iiiiiyang (赞：1)

[逆天的阅读体验](https://www.cnblogs.com/LittleTwoawa/p/17731979.html)

[题目链接](https://www.luogu.com.cn/problem/CF1878E)

如果一个区间的按位与和在第 $k$ 位上是 $1$，说明这个区间内所有的数在这一位上都是 $1$。拆位，对于每一位预处理出每个位置向后连续 $1$ 段最长到什么位置。对于每次询问将 $k$ 拆位，如果当前位 $k$ 为 $0$，且更高位不存在 $1$，那么如果一个区间按位与和在这一位上为 $1$ 就可以大于 $k$，所以对于这些位置和记录的最长后缀连续长度取最大值即可。找到 $k$ 二进制位下最高的 $1$，从这一位开始，如果 $k$ 在当前考虑到的位上是 $1$，那么区间按位与和也必须是 $1$；如果 $k$ 在这一位是 $0$，那么按位与和在这一位选 $1$ 就赢了。维护一个指针表示为了和 $k$ 保持相等取到的右端点，如果找到 $k$ 这一位为 $0$，答案就和**当前指针和这一位取 $1$ 的记录的右端点中的较小值**再取个最大值即可。

这样可以做到 $\mathcal O((n + q) \log V)$，多测清空要多清一点，这种找后继的清少了可能会继承掉上组的答案。

```cpp
#include<bits/stdc++.h>
#define ld long double
#define ui unsigned int
#define ull unsigned long long
#define int long long
#define eb emplace_back
#define pb pop_back
#define ins insert
#define mp make_pair
#define pii pair<int,int>
#define fi first
#define se second
#define power(x) ((x)*(x))
using namespace std;
 
namespace FastIO
{
    template<typename T=int> inline T read()
    {
        T s=0,w=1; char c=getchar();
        while(!isdigit(c)) {if(c=='-') w=-1; c=getchar();}
        while(isdigit(c)) s=(s*10)+(c^48),c=getchar();
        return s*w;
    }
    template<typename T> inline void read(T &s)
    {
        s=0; int w=1; char c=getchar();
        while(!isdigit(c)) {if(c=='-') w=-1; c=getchar();}
        while(isdigit(c)) s=(s*10)+(c^48),c=getchar();
        s=s*w;
    }
    template<typename T,typename... Args> inline void read(T &x,Args &...args)
    {
        read(x),read(args...);
    }
    template<typename T> inline void write(T x,char ch)
    {
        if(x<0) x=-x,putchar('-');
        static char stk[25]; int top=0;
        do {stk[top++]=x%10+'0',x/=10;} while(x);
        while(top) putchar(stk[--top]);
        if(ch!='~') putchar(ch);
        return;
    }
}
using namespace FastIO;
 
namespace MTool
{   
    #define TA template<typename T,typename... Args>
    #define TT template<typename T>
    static const int Mod=998244353;
    TT inline void Swp(T &a,T &b) {T t=a;a=b;b=t;}
    TT inline void cmax(T &a,T b) {a=max(a,b);}
    TT inline void cmin(T &a,T b) {a=min(a,b);}
    TA inline void cmax(T &a,T b,Args... args) {a=max({a,b,args...});}
    TA inline void cmin(T &a,T b,Args... args) {a=min({a,b,args...});}
    TT inline void Madd(T &a,T b) {a=a+b>=Mod?a+b-Mod:a+b;}
    TT inline void Mdel(T &a,T b) {a=a-b<0?a-b+Mod:a-b;}
    TT inline void Mmul(T &a,T b) {a=a*b%Mod;}
    TT inline void Mmod(T &a) {a=(a%Mod+Mod)%Mod;}
    TT inline T Cadd(T a,T b) {return a+b>=Mod?a+b-Mod:a+b;}
    TT inline T Cdel(T a,T b) {return a-b<0?a-b+Mod:a-b;}
    TT inline T Cmul(T a,T b) {return a*b%Mod;}
    TT inline T Cmod(T a) {return (a%Mod+Mod)%Mod;}
    TA inline void Madd(T &a,T b,Args... args) {Madd(a,Cadd(b,args...));}
    TA inline void Mdel(T &a,T b,Args... args) {Mdel(a,Cadd(b,args...));}
    TA inline void Mmul(T &a,T b,Args... args) {Mmul(a,Cmul(b,args...));}
    TA inline T Cadd(T a,T b,Args... args) {return Cadd(Cadd(a,b),args...);}
    TA inline T Cdel(T a,T b,Args... args) {return Cdel(Cdel(a,b),args...);}
    TA inline T Cmul(T a,T b,Args... args) {return Cmul(Cmul(a,b),args...);}
    TT inline T qpow(T a,T b) {int res=1; while(b) {if(b&1) Mmul(res,a); Mmul(a,a); b>>=1;} return res;}
    TT inline T qmul(T a,T b) {int res=0; while(b) {if(b&1) Madd(res,a); Madd(a,a); b>>=1;} return res;}
    TT inline T spow(T a,T b) {int res=1; while(b) {if(b&1) res=qmul(res,a); a=qmul(a,a); b>>=1;} return res;}
    TT inline void exgcd(T A,T B,T &X,T &Y) {if(!B) return X=1,Y=0,void(); exgcd(B,A%B,Y,X),Y-=X*(A/B);}
    TT inline T Ginv(T x) {T A=0,B=0; exgcd(x,Mod,A,B); return Cmod(A);}
    #undef TT
    #undef TA
}
using namespace MTool;
 
inline void file()
{
    freopen(".in","r",stdin);
    freopen(".out","w",stdout);
    return;
}
 
bool Mbe;
 
namespace LgxTpre
{
    static const int MAX=300010;
    static const int inf=2147483647;
    static const int INF=4557430888798830399;
    
    int T,n,m,a[MAX],l,r,k;
    int mix,suf[35][MAX];
 
    inline void lmy_forever()
    {
    	read(T);
    	while(T--)
    	{
    		read(n),mix=0,a[n+1]=0;
    		for(int i=1;i<=n;++i) read(a[i]),cmax(mix,a[i]);
    		for(int k=0;k<=30;++k) for(int i=1;i<=n+10;++i) suf[k][i]=-1;
    		for(int k=0;k<=__lg(mix);++k) for(int i=n;i;--i) if(a[i]>>k&1) {if(a[i+1]>>k&1) suf[k][i]=suf[k][i+1]; else suf[k][i]=i;} else suf[k][i]=-1;
			read(m);
			for(int i=1;i<=m;++i)
			{
				read(l,k),r=-1;
				for(int j=__lg(mix);j>__lg(k);--j) cmax(r,suf[j][l]);
				int nr=suf[__lg(k)][l];
				for(int j=__lg(k)-1;~j&&~nr;--j) if(k>>j&1) cmin(nr,suf[j][l]); else cmax(r,min(suf[j][l],nr));
				cmax(r,nr),write(r,' ');
			}
			puts("");
		}
    }
}
 
bool Med;
 
signed main()
{
//  file();
    fprintf(stderr,"%.3lf MB\n",abs(&Med-&Mbe)/1048576.0);
    int Tbe=clock();
    LgxTpre::lmy_forever();
    int Ted=clock();
    cerr<<1e3*(Ted-Tbe)/CLOCKS_PER_SEC<<" ms\n";
    return (0-0);
}
```

---

## 作者：tbdsh (赞：1)

# 题意简述
[洛谷原题传送门](https://www.luogu.com.cn/problem/CF1878E)

[CodeForces 原题传送门](http://codeforces.com/problemset/problem/1878/E)

有 $t$ 组数据。每组数据给定长度为 $n$ 的数组 $a$ 和 $q$ 次询问。

我们定义 $\operatorname{f}(l,r)(1\le l\le r\le n)$ 表示 $a_l\And a_{l+1}\& \dots\& a_{r-1}\&a_r$ 的结果。其中，$\&$ 表示位与运算。

对于每次询问，将给定 $l,k$。请你找到最大的 $r$ 使得 $\operatorname{f}(l,r)\ge k$。如果无解，输出 `-1`。

# 分析
结束前一分钟想到。

首先我们可以注意到，$a_i\And a_{i+1} \ge a_i\And a_{i+1} \And a_{i+2}$ 一定成立。

那么我们就可以二分答案。

但是如何快速求出区间位与的和呢？我们考虑使用线段树。

那么本题就可以在 $O(\log^2 n)$ 的时间复杂度中处理出一次询问。

# Code
```cpp
#include<bits/stdc++.h>
#define int long long

using namespace std;
const int MAXN = 2e5 + 5;
int n, q, a[MAXN], tr[4 * MAXN];
void js(int id, int l, int r){
  if (l == r){
    tr[id] = a[l];
    return ;
  }
  int mid = (l + r) >> 1;
  js(id * 2, l, mid);
  js(id * 2 + 1, mid + 1, r);
  tr[id] = (tr[id * 2] & tr[id * 2 + 1]);
}
int find(int id, int l, int r, int ql, int qr){
  if (l > qr || r < ql){
    return (1ll << 30) - 1;
  }else if (ql <= l && r <= qr){
    return tr[id];
  }
  int mid = (l + r) >> 1;
  return find(id * 2, l, mid, ql, qr) & find(id * 2 + 1, mid + 1, r, ql, qr);
}
void Solve(){
  cin >> n;
  for (int i = 1; i <= n; i++){
    cin >> a[i];
  }
  js(1, 1, n);
  cin >> q;
  while (q--){
    int l, r = n, k;
    cin >> l >> k;
    int tmp = l;
    while (l < r){
      int mid = (l + r + 1) >> 1;
      if (find(1, 1, n, tmp, mid) >= k){
        l = mid;
      }else {
        r = mid - 1;
      }
    }
    cout << (find(1, 1, n, tmp, r) < k ? -1 : r) << ' ';
  }
  cout << '\n';
}
signed main(){
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int t;
  cin >> t;
  while (t--){
    Solve();
  }
  return 0;
}
```

---

## 作者：Xiphi (赞：0)

主体做法：二分+st 表。

综合评价：上位黄，但是很板。

首先，一个很典的性质就是 $f(l,r)$ 递减，呈单调性，所以可以二分。 $f(l,r)$ 考虑 st 表或者线段树维护。

代码细节不多，故不写注释：

```cpp
#include<bits/stdc++.h>
using namespace std;
int st[200005][20],n,q;
void build(){
	for(int j=1;j<=19;++j){
	for(int i=1;(i+(1<<j)-1)<=n;++i){
		st[i][j]=st[i][j-1]&st[i+(1<<(j-1))][j-1];
	}
	}
}
int query(int l,int r){
	int len=log2(r-l+1);
	return st[l][len]&st[r-(1<<(len))+1][len];
}
void solve(){
	cin>>n;
	for(int i=1;i<=n;++i) cin>>st[i][0];
	build();
	cin>>q;
	while(q--){
		int t,l,k;
		cin>>l>>k;
		t=l;
		int r=n,ans=-1;
		while(l<=r){
			int mid=l+r>>1;
			if(query(t,mid)>=k){
				ans=mid,l=mid+1;
			}else r=mid-1;
		}
		cout<<ans<<' ';
	}
	cout<<'\n';
}
int main(){
//	freopen("test.in","r",stdin);
//	freopen("test.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
	int T;
	cin>>T;
	while(T--){
		solve();
	}
	return 0;
}




```

---

## 作者：One_JuRuo (赞：0)

## 思路

要求从一个点开始最远可以选择那个点使得两点之间的数字的与大于等于 $k$，最开始想到的是提前预处理出每个点往后若干位的与，因为与只可能变小不可能变大，所以可以二分找到最远的位置，但是这样无论时间还是空间都会爆掉，所以我们考虑优化一下这个办法。

既然不能把每个点的后面的位置的与全部算出来，那么我们可以只算一部分，所以想到了 ST 表。

至于无解，如果当前位置的数本身就比 $k$ 小就一定无解，否则就一定有解。

想到了 ST 表和二分，这道题应该就不难了。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,a[200005],q,l,k,st[200005][35],lo[200005],L,R,mid,ans,le;
int main()
{
	for(int i=2;i<=200000;++i) lo[i]=lo[i/2]+1;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;++i) scanf("%d",&a[i]),st[i][0]=a[i];
		for(int i=1;i<=30;++i) for(int j=1;j+(1<<i)-1<=n;++j) st[j][i]=st[j][i-1]&st[j+(1<<(i-1))][i-1];//ST表预处理
		scanf("%d",&q);
		while(q--)
		{
			scanf("%d%d",&l,&k);
			if(a[l]<k){printf("-1 ");continue;}//判无解
			L=l,R=n;
			while(L<=R)//二分找最远位置
			{
				mid=L+R>>1,le=lo[mid-l+1];
				if((st[l][le]&st[mid-(1<<le)+1][le])>=k) ans=mid,L=mid+1;//与重复一个数不会造成影响，所以这里ST表范围重复不影响
				else R=mid-1;
			}
			printf("%d ",ans);
		}
		puts("");
	}
	return 0;
}
```

---

## 作者：hikariyo_ (赞：0)

## 按位与计算性质

对于常数 $k$，$\forall a,a\&k\le a$ 总是成立的，所以当 $L$ 固定时，$f(L,R)$ 对 $R$ 是非严格单调递减的，因此我们可以通过在区间 $[L,N]$ 二分出一个最大的 $R$。

拓展：相似地，按位或运算是非严格单调递增的。

## 线段树

快速求出来一个区间的具有结合律的运算，很容易想到线段树，这样二分的复杂度是 $O(\log n)$，线段树求区间与的复杂度是 $O(\log n)$，综合起来是 $O(n\log n+q\log^2 n)$ 的复杂度。

```cpp
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int N = 200010;
int a[N], n;
struct Node {
	int l, r, v;
} tr[N<<2];

void pushup(int u) {
	tr[u].v = tr[u<<1].v & tr[u<<1|1].v;
}

void build(int u, int l, int r) {
	tr[u].l = l, tr[u].r = r;
	if (l == r) return tr[u].v = a[l], void();
	int mid = l+r >> 1;
	build(u<<1, l, mid), build(u<<1|1, mid+1, r);
	pushup(u);
}

int query(int u, int l, int r) {
	if (l <= tr[u].l && tr[u].r <= r) return tr[u].v;
	
	int mid = tr[u].l + tr[u].r >> 1;
	if (r < mid+1) return query(u<<1, l, r);
	if (l > mid) return query(u<<1|1, l, r);
	
	return query(u<<1, l, r) & query(u<<1|1, l, r);
}

void solve() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	build(1, 1, n);
	int q, start, k;
	cin >> q;
	while (q--) {
		cin >> start >> k;
		int l = start, r = n;
		while (l < r) {
			int mid = l+r+1 >> 1;
			int now = query(1, start, mid);
//			printf("NOW IS %d\n", now);
			if (now >= k) l=mid;
			else r=mid-1;
		}
		if (r == start && a[start] < k) cout << -1 << ' ';
		else cout << r << ' ';
	}
	cout << '\n';
}

int main() {
	int T; cin >> T;
	while (T--) solve();
	return 0;
}

```

## 拆位前缀和

对于二进制位 $i$，当且仅当 $S_{i,r}-S_{i,l-1}=r-l+1$ 即整个区间的这个位都是 $1$ 时是有贡献的，其余区间都无贡献。

$a$ 最大为 $10^9$，所以这里开 $30$ 个足够用。

初始化：

```cpp
for (int i = 0; i < 30; i++)
    for (int j = 1; j <= n; j++)
        s[i][j] = s[i][j-1] + (a[j] >> i & 1);
````


查询：

```cpp
int query(int l, int r) {
    int res = 0;
    for (int i = 0; i < 30; i++)
        if (s[i][r] - s[i][l-1] == r-l+1)
            res += 1 << i;
    return res;
}
```

这样看下来复杂度是 $O(n\log a+q\log n\log a)$，和线段树相差不大，但是更好写。



---

