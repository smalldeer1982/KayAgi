# [SEERC 2020] Modulo Permutations

## 题目描述

求长度为 $n$ 的 $1 \sim n$ 的所有排列总数，其中满足 $p_i \bmod p_{i+1} \leq 2$ 的（此处 $p_{n+1} = p_1$），对 $10^9 + 7$ 取模后的值。

## 样例 #1

### 输入

```
1```

### 输出

```
1```

## 样例 #2

### 输入

```
2```

### 输出

```
2```

## 样例 #3

### 输入

```
3```

### 输出

```
6```

## 样例 #4

### 输入

```
4```

### 输出

```
16```

## 样例 #5

### 输入

```
5```

### 输出

```
40```

## 样例 #6

### 输入

```
1000000```

### 输出

```
581177467```

# 题解

## 作者：OtterZ (赞：3)

# 题目

求有多少个全排列，使 $p_i\bmod p_{i \bmod n + 1} \le 2$。

要求长度为 $n(1 \le n \le 10 ^ 6)$。

# 引理

引理：每一个排列从一个位置开始环形遍历，可得到结尾分别为 $1,2$ 的单调下降序列拼合得到的全排列。

证：对于 $p_i < p_{i \bmod n + 1},p_i > 2$，有 $p_i \mod p_{i \bmod n + 1} = p_i > 2$，故而 $p_i > 2$ 时总有 $p_i > p_{i \bmod n + 1}$，而 $p_i < p_{i \bmod n + 1},p_i \le 2$，有 $p_i \bmod p_{i \bmod n + 1} = p_i \le 2$，由此可得，每一个排列从一个位置开始环形遍历，可得到结尾分别为 $1,2$ 的单调下降序列拼合得到的全排列，证毕。

# 动规

对于其中一个下降子序列，每个数前可接：

1. $i\times j$；
2. $i \times j + 1$；
3. $i \times j + 2$。

我们设 $dp_{i,j}$ 为两序列结尾较小值为 $i$，较大值为 $j$ 的对应排列数，根据 $\max\{i,j\} + 1$ 的插入情况可得到转移方程。

# 优化

## 再来一个引理

引理：设 $s_i = \{x|j \in N^+,x \bmod i \le 2 \text{且} x > i + 1\}$，有 $dp_{i,i + 1} = 1 + \sum_{k \in s_i}dp_{k - 1,k}$。

证：对于一个序列结尾为 $i$，另一个序列结尾为 $i + 1,i$ 前为 $k$ 时，$i + 2,i + 3,...,k - 1$ 此时在另一个序列上，即 $i + 1$ 前，此时得到一个合法结果，还有一个情况，即将所有 $x > i$ 放在另一个序列中也会得到一个合法解。

![](https://cdn.luogu.com.cn/upload/image_hosting/x4iukomo.png)

证毕。

## 基于引理的快速动规

我们要的答案为 $dp_{1,2} \times n$，根据引理得到的公式可 $\operatorname{O}(n\ln n)$ 得出，这样就解决了问题。

注意 $n = 1$ 的特殊情况和转移方程的范围判断与去重。

# 代码

```cpp
#include<cstdio>
using namespace std;
int n,m,dp[1000009];
int ans;
#define mod 1000000007
int main(){
	scanf("%d",&n);
	if(n == 1){
		puts("1");
		return 0;
	}
	dp[n - 1] = 1;
	ans = 1;
	for(int i = n - 2; i > 0; i --){
		dp[i] = 1;
		for(int j = 1; j * i <= n; j ++){
			if(j * i > i + 1){ //(i,i + 1) -> (j * i - 1,j * i) 
				dp[i] = (dp[i] + dp[i * j - 1]) % mod;
			}
			if(j * i > i && j * i + 1 <= n && i > 1){//(i,i + 1) -> (j * i,j * i + 1)
				dp[i] = (dp[i] + dp[i * j]) % mod;
			}
			if(j * i + 1 > i && j * i + 2 <= n && i > 2){//(i,i + 1) -> (j * i + 1,j * i + 2)
				dp[i] = (dp[i] + dp[i * j + 1]) % mod;
			}
		}
	//	printf("%d\n",dp[i]);
	}
	printf("%d\n",1ll * dp[1] * n % mod);
}
```

---

## 作者：bsdsdb (赞：3)

我们考虑从 $1$ 到 $n$ 一个一个加入数。

显然，每一个 $1$ 不在 1 号位置的解都能对应到一个 $1$ 在 1 号位置的解。所以我们只考虑 $1$ 在 1 号位置的解，答案最后乘以 $n$.

剩下的数就不用管 $1$ 了，因为 $\forall 2\le i\le n:1\bmod i\le 2, i\bmod 1\le 2$. 现在这个环变成了一个链。

继续考虑加入 $2$，同样有 $\forall 3\le i\le n:2\bmod i\le 2, i\bmod 2\le 2$. 所以其他数也不用管 $2$ 怎么放。$2$ 的位置可以唯一对应到一对【$1$ 后面的数和 $2$ 后面的数的数量】，也可以根据这个数量来确定 $1,2$ 的位置。

所以换个角度考虑问题，就是我们现在要往 $1,2$ 两个桶里依次加入 $3\cdots n$. 令这个桶里上次加入的数是 $x$，这次加入的数是 $y$，则需要保证 $y\bmod x\le 2$. 不用考虑 $x\bmod y$ 是因为有 $x\ge 3$ 和 $x<y$，所以 $x\bmod y=x\ge 3$. 为什么不可能先加大的再加小的？因为 $\forall j>i\ge 3:i\bmod j=i>2$.

考虑 dp. 令 $\mathrm{dp}_{i,j_1,j_2}$ 表示现在加到了 $i$，$1$ 号桶的顶端是 $j_1$，$2$ 号是 $j_2$. 容易发现必有 $j_1=i\lor j_2=i$，所以状态可以优化成 $\mathrm{dp}_{i,1/2,j}$ 表示 $1/2$ 号桶顶端是 $i$，另一个是 $j$. 初始情况是 $\mathrm{dp}_{2,1,1}=1$. 我们将加数的过程分为两种情况：加入顶端是 $i-1$ 的那个桶，以及不是 $i-1$ 的。

对于第一种情况，$\mathrm{dp}_{i,k,j}$ 的前置状态是 $\mathrm{dp}_{i-1,k,j}$. 不论任何情况，这么加都是合法的，因为 $\forall i:i\bmod (i-1)=1\le 2$. 所以我们有 $\mathrm{dp}_{i,k,j}\leftarrow\mathrm{dp}_{i-1,k,j}$，其中 $x\leftarrow y$ 表示 $y$ 的值对 $x$ 做了贡献。

对于第二种情况，设加入前桶顶是 $j'$，要求 $i\bmod j'\le 2$. 加入之前，$j'$ 在 $k$ 号桶，则 $i-1$ 在 $3-k$ 号桶。加入之后，一个桶的桶顶是 $i$，另一个必是 $i-1$。所以有 $\mathrm{dp}_{i,k,i-1}\leftarrow\mathrm{dp}_{i-1,3-k,j'}$.

至此，我们得到了 $O(n^2)$ 的 dp，接下来考虑优化。

对于第二种情况，有贡献的就只有 $i,i-1,i-2$ 的因数，$i,i-1$ 本身除外，因为由 $\mathrm{dp}$ 的定义有 $\mathrm{dp}_{i-1,k,i-1}=\mathrm{dp}_{i-1,k,i}=0$. 对此，我们可以先 $O(n\log n)$ 预处理每个数的因数（简单来说就是 `for all i satisfies <=n: for all j satisfies j|i: add i to factor[j]`）。然后需要算 $\mathrm{dp}$ 的时候去 $\mathrm{factor}$ 中循环即可。注意去重。

对于第一种情况，其实就是把 $\mathrm{dp}_{i-1}$ 复制到 $\mathrm{dp}_i$ 来。要是把第一维去掉，就不用复制，直接留在那里就行了。因此我们把第一维去掉。由于第二种情况更新 $\mathrm{dp}_{k,i-1}$ 的时候不会用到同时更新的 $\mathrm{dp}_{3-k,i-1}$，所以去掉第一维不影响答案。

最后答案就是 $n\sum_{i=1}^{n-1}\sum_{k=1}^{2}\mathrm{dp}_{k,i}$，时间 / 空间复杂度 $\mathcal O(n\log n)$. 注意特判 $n=1$.

```cpp
// 不能AC，会被卡常(っ °Д °;)っ
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
#include <ext/pb_ds/exception.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#include <ext/pb_ds/list_update_policy.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/trie_policy.hpp>
// using namespace __gnu_pbds;
// tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update>T;
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
typedef long double ldb;
//#define umap unordered_map
#define umap __gnu_pbds::cc_hash_table
#define mkp make_pair
#define prque priority_queue
#define emp emplace
#define empb emplace_back
#define empf emplace_front
random_device rndv;
mt19937 rd(rndv());
const ll inf = 0x3f3f3f3f3f3f3f3fll;
const double eps = 1e-8;
inline void enter(){putchar('\n');}
inline void space(){putchar(' ');}
inline ll readll(){ll ret=0,k=1;char c;do{c=getchar();if(c=='-'){k=-1;}}while(('0'>c)|('9'<c));do{ret=(ret<<3)+(ret<<1)+c-48;c=getchar();}while(('0'<=c)&(c<='9'));return ret*k;}
inline void read(ll&x){x=readll();}
inline char readchar(){char ret;do{ret=getchar();}while(ret<=32);return ret;}
inline void read(char&x){x=readchar();}
inline string readstr(){string ret;char c;do{c=getchar();}while(c<=32);do{ret+=c;c=getchar();}while((c>32)&(c!=EOF));return ret;}
inline void read(string&x){x=readstr();}
inline void write(ll x){if(!x){putchar('0');return;}if(x<0){putchar('-');x*=-1;}char op[20]={};ll cur=0;while(x){op[++cur]=x%10+48;x/=10;}while(cur){putchar(op[cur--]);}}
inline ostream& operator<<(ostream& out, __int128 x){if(!x){out<<"0";return out;}if(x<0){out<<"-";x*=-1;}char op[40]={};ll cur=0;while(x){op[++cur]=x%10+48;x/=10;}while(cur){out<<op[cur--];}return out;}
// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

const ll MAXN = 1e6 + 5, mod = 1e9 + 7;

ll n, dp[2][MAXN];
vector<ll> ys[MAXN];
vector<ll> yinshu;

vector<ll> gb(vector<ll>& x, vector<ll>& y) {
	vector<ll> ret;
	ll cur1 = 0, cur2 = 0;
	while (cur1 < x.size() || cur2 < y.size()) {
		if (cur1 >= x.size()) {
			ret.empb(y[cur2++]);
		} else if (cur2 >= y.size()) {
			ret.empb(x[cur1++]);
		} else if (x[cur1] < y[cur2]) {
			ret.empb(x[cur1++]);
		} else if (y[cur2] < x[cur1]) {
			ret.empb(y[cur2++]);
		} else {
			ret.empb(x[cur1]);
			++cur1, ++cur2;
		}
	}
	return ret;
}

int main() {
//	freopen("crlf.txt", "r", stdin);
	read(n);
	if (n == 1) {
		write(1), enter();
		return 0;
	}
	if (n == 2) {
		write(2), enter();
		return 0;
	}
	for (ll i = 1; i <= n; ++i) {
		for (ll j = i; j <= n; j += i) {
			ys[j].empb(i);
		}
	}
	memset(dp, 0, sizeof dp);
	dp[1][1] = n;
	for (ll i = 3; i <= n; ++i) {
		yinshu.clear();
		vector<ll> tmp = gb(ys[i - 1], ys[i - 2]);
		yinshu = gb(ys[i], tmp);
		for (auto _j = yinshu.begin(); _j != yinshu.end(); ++_j) {
			ll j = *_j;
			if (j == i - 1) {
				continue;
			}
			(dp[0][i - 1] += dp[1][j]) %= mod;
			(dp[1][i - 1] += dp[0][j]) %= mod;
		}
	}
	ll ans = 0;
	for (ll i = 1; i <= n; ++i) {
		(ans += dp[0][i] + dp[1][i]) %= mod;
	}
	write(ans % mod), enter();
	return 0;
}

;             ;;;;;;;;;;;         ;
;                      ;         ; ;
;                    ;          ;   ;
;                   ;          ;     ;
;                 ;           ;;;;;;;;;
;               ;            ;         ;
;              ;            ;           ;
;;;;;;;;;;;   ;;;;;;;;;;   ;             ;

   ;                        ;
  ;                          ;
 ;                            ;
;                              ;
;                              ;
;                              ;
 ;                            ;
  ;         ;;          ;;   ;
   ;        ;;          ;;  ;

  ;  ;  ;;; ;;;  ;   ;   ;  ;;  ;;  ;;; 
; ; ; ;  ;  ; ; ; ; ; ; ; ; ;;  ; ; ; ;  ;   ;
;;; ; ;  ;  ; ;   ; ; ;   ; ;;  ; ; ; ;  ;   ;
;;; ; ;  ;  ;;   ;  ; ;  ;  ;;  ;;  ;;  ;;; ;;;
;;; ; ;  ;  ;   ;   ; ; ;   ;;; ;;  ;    ;   ;
; ; ; ;  ;  ;   ; ; ; ; ; ;  ;  ; ; ;    ;   ;
;    ;  ;;; ;   ;;;  ;  ;;;  ;  ; ; ;
```

---

## 作者：elbissoPtImaerD (赞：3)

### Algorithm 1
我们发现对于一个约束，当 $p_i < p_{i+1}$ 时仅当 $p_i \le 2$ 方成立。由于是一个排列，所以 $p_i < p_{i+1}$ 的位置只有 $2$ 个，分别是 $1$ 和 $2$ 的位置。

注意到若钦定 $p_1=1$，$p_q=2$，则 $[1,q)$ 和 $(q,n]$ 分别递减。考虑对这两段 DP，具体地，设 $f(i,j)$ 表示已经填入 $1\sim i$，与 $i$ 不在同一段的数的最大值是 $j$ 的方案数，转移直接考虑 $i+1$ 是否与 $i$ 同一段，有转移：$f(i,j) \to f(i+1,j)$ 和 $f(i,j)[(i+1) \bmod j \le 2] \to f(i+1,i)$。暴力 DP 是 $O(n^2)$ 的。

### Algorithm 2
考虑优化 Algorithm 1 中从 $i$ 到 $i+1$ 的转移，$f(i,j) \to f(i+1,j)$ 就是数组复制，$f(i,j)[(i+1) \bmod j \le 2] \to f(i+1,i)$ 只需要枚举 $(i+1) \bmod j \le 2$ 的 $j$ 做转移，复杂度是调和级数的 $O(n\ln n)$。

### Algorithm 3
重新设计 Algorithm 1 中对两段的 DP。考虑另一种生成方式：每次在两段的末尾加入一段极长连续段。

直接记录断点，$f(i)$ 表示已经填入 $1\sim i$ 钦定 $i$ 和 $i+1$ 在不同段的方案数。

转移直接枚举 $j$ 表示在 $j$ 不在的段上拼上 $[i,j)$，有 $f(j)[(i+1)\bmod j \le 2] \to f(i)$，注意限制 $i+1$ 可以接在 $j$ 上。

暴力转移 $O(n^2)$。
### Algorithm 4
考虑优化 Algorithm 3 的转移部分，观察到 $(i+1) \bmod j \le 2$ 等价于 $j\mid (i-1)$ 或 $j \mid i$ 或 $j \mid (i+1)$，所以枚举 $j$ 以及 $j$ 的倍数做刷表即可做到调和级数复杂度，即 $O(n \ln n)$。

Algorithm 4 的一种实现：
```cpp

void Solve() {
  int n; cin>>n;
  if(n<=2) {
    cout<<n<<'\n';
    return;
  }
  // Algorithm 3: 
  // ve<Mi>f(n);
  // f[1]=n;
  // for(int i=2;i<n;++i) {
  //   for(int j=1;j<i;++j) {
  //     if((i+1)%j<=2) f[i]+=f[j];
  //   }
  // }
  ve<Mi>f(n,n*2);
  f[0]=0,f[1]=n,f[2]=n;
  for(int j=3;j<n;++j) {
    for(int k=j;k<=n;k+=j) {
      if(j<k-1) f[k-1]+=f[j];
      if(j<k&&k<n) f[k]+=f[j];
      if(k+1<n) f[k+1]+=f[j];
    }
  }
  cout<<accumulate(all(f),Mi(0))<<'\n';
  return;
}
```

---

## 作者：xiezheyuan (赞：3)

## 思路

首先我们发现下面几条关键性质：

- $1,2$ 前面可以填任意数（其实 $3$ 也可以）。
- 用 $1,2$ 分割排列，每一部分单调递减。

第一个性质是平凡的，第二个性质可以用反证法。假如存在 $p_i<p_{i+1}$，则 $p_i\bmod p_{i+1}=p_i$，又因为 $p_i>2$，所以 $p_i\bmod p_{i+1} > 2$，不合法，故每一部分单调递减。

于是我们可以对类似 `xx...xx1yy...yy2` 的排列计数。我们称 $x$ 部分为第一部分，$y$ 部分为第二部分。

然后可以 dp，枚举第一部分的最前面的元素 $i$，然后尝试添加比它大的元素 $j$ 到前面去。根据题目的约束，需要满足 $j\bmod i\leq 2$，这样的 $(i,j)$ 总数数量类似调和级数，为 $O(n\log n)$ 级别。

然后考虑 $j-1\sim i$ 这一部分是一个递减，只能放到第二部分去。那么这个时候发现第一部分的第一个元素为 $j$，第二部分的第一个元素为 $j-1$，并且这种情况出现频繁。

考虑我们就设 $f(i)$ 表示第一部分第一个元素是 $i$，第二部分第一个元素是 $i-1$，可以按照前面的思路枚举 $j$ 去刷表。

然后考虑如何求出答案，对于每一个方法，我们都有一种决策就是将 $i\sim n$ 的元素都放到第一部分去。所以我们需要求：

$$
\sum_{k}f(k)
$$

然后我们注意，可以对排列轮换，会得到另一个合法的排列，并且在之前的计算中没有出现（注意 $2$ 的位置）。所以最后还需要乘上 $n$。

注意一下转移的细节。时间复杂度 $O(n\log n)$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5, mod = 1e9 + 7;
int n, f[N], ans;
unordered_map<int, int> vis;
int Add(int x, int y){ return (x + y) > mod ? (x + y - mod) : (x + y); }

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> n;
    if(n <= 2){
        cout << n;
        return 0;
    }
    f[2] = 1;
    for(int i=2;i<=n;i++){
        if(i <= 5) vis.clear();
        for(int j=i-1;j<=n;j+=i-1){
            for(int k=0;k<=2&&j+k<=(n + 1);k++){// x % i <= 2
                if(j + k <= i) continue;
                if(i <= 5 && vis[j + k]) continue;
                f[j + k] = Add(f[j + k], f[i]);
                if(i <= 5) vis[j + k] = 1;
            }
        }
    }
    for(int i=1;i<=n;i++) ans = Add(ans, f[i]);
    cout << (1ll * ans * n % mod);
    return 0;
}

// Written by xiezheyuan
```

---

## 作者：ChrysanthBlossom (赞：3)

由于限制是环状的，考虑直接对最大值在首位的排列进行计数，最后再乘上 $n$ 即可。

观察合法的排列可以发现他们都由一段或两段极长单调下降序列拼接而成，且若存在两个则这两个末尾不能有大于 $2$ 的数。这个可以用反证法证：假如有三段，则必然有一段末尾为 $3$，在 $3$ 之后的数必然比 $3$ 大（否则则不是极长的），设 $3$ 所在位置为 $x$，则 $p_x \bmod p_{x+1}=3$，不合法，故最多有两段；假如存在大于 $2$ 的数作末尾，用上述方法同样可证，此处略去。

对于一段的情况，我们可以将其划为 $1$ 和 $[2,n]$，这样它也可被认为是两段。于是我们仅需统计有多少种从 $1$ 到 $n$ 中抽出一个子序列的方法使得抽出的子序列与剩下的子序列相邻的都满足条件。

考虑连续段 dp。设 $f_i$ 表示当前考虑到的最后一个连续段末尾为 $i$，且 **保证 $i+1$ 与最后一个连续段开头的前一个元素满足条件（若不存在此元素（即当前仅一条连续段），我们认为 $i+1$ 满足）** 的方案数。

由于我们规定了一条连续段时是满足的，故 $f_1=1$。转移式显然为 $\forall j \bmod i \le 2, f_i \to f_{j-1}$。对于答案，我们考虑最后一段的起始点，故为 $\sum\limits_{i=1}^{n-1}f_i$。

转移时可从前往后贡献，时间复杂度 $O(n \log n)$。

---

## 作者：Rem_CandleFire (赞：0)

很奇妙的题目。参考了其它题解。

首先考虑条件 $p_i\bmod p_{i+1}\le 2$，这告诉我们当 $p_i\le p_{i+1}$ 时有 $p_i\le 2$。若令 $p_x=1,p_y=2$ 则有区间 $[1,x],[y,n]$ 单调递减。考虑对这两段 DP，枚举第一段的第一个元素 $i$，将 $j$ 放入 $i$ 的前一个位置，为了满足条件，必须有 $j=ik+d(k,d\in\mathbb{N},d\le2,k>0)$。为了保证段落的单调性，数 $[j-1,i+1]$ 这一段都要整个放入第二部分 $[y,n]$ 中。

此时我们发现，第一部分的第一个数为 $j$，第二部分第一个数为 $j-1$。于是钦定 $f_i$ 表示将 $i$ 与 $i-1$ 分成两个部分的方案数。对于一个 $i$，直接跳 $i-1$ 的倍数，枚举 $d=0,1,2$ 分别刷表即可。为什么是跳 $i-1$ 的倍数呢，因为另一段的开头是 $i-1$，枚举 $j$ 转移后 $i-1$ 的前面一个数可能是 $i+1$，这是正确的。如果跳 $i$ 的倍数，可能会出现某种类似于 $6,5,3,2,7,4,1$ 的不合法答案被当做合法计入了。可以枚举一些情况或者看看别的题解思考一下。

初始化是 $f_2=n$，因为有 $n$ 个位置可以放。对于任意 $f_i,f_j$，二者的方案之间一定是不同的（毕竟两段的最高位置不一样），所以答案是 $\sum f_i$。

枚举 $j$ 是调和级数，时间复杂度为 $O(n\log n)$。

需要注意的是，手模一下 $n=3$ 的情况我们发现可能会多次计算，用个数组打标记避免重复就好了，当然也可以把 $i\le3$ 的情况单独处理。

---

