# Max Sum Array

## 题目描述

You are given an array $ c = [c_1, c_2, \dots, c_m] $ . An array $ a = [a_1, a_2, \dots, a_n] $ is constructed in such a way that it consists of integers $ 1, 2, \dots, m $ , and for each $ i \in [1,m] $ , there are exactly $ c_i $ occurrences of integer $ i $ in $ a $ . So, the number of elements in $ a $ is exactly $ \sum\limits_{i=1}^{m} c_i $ .

Let's define for such array $ a $ the value $ f(a) $ as $ $$$f(a) = \sum_{\substack{1 \le i < j \le n\\ a_i = a_j}}{j - i}. $ $ </p><p>In other words,  $ f(a) $  is the total sum of distances between all pairs of equal elements.</p><p>Your task is to calculate the maximum possible value of  $ f(a) $  and the number of arrays yielding the maximum possible value of  $ f(a)$$$. Two arrays are considered different, if elements at some position differ.

## 说明/提示

In the first example, all possible arrays $ a $ are permutations of $ [1, 2, 3, 4, 5, 6] $ . Since each array $ a $ will have $ f(a) = 0 $ , so maximum value is $ f(a) = 0 $ and there are $ 6! = 720 $ such arrays.

In the second example, the only possible array consists of $ 10^6 $ ones and its $ f(a) = \sum\limits_{1 \le i < j \le 10^6}{j - i} = 166\,666\,666\,666\,500\,000 $ and $ 166\,666\,666\,666\,500\,000 \bmod{10^9 + 7} = 499\,833\,345 $ .

## 样例 #1

### 输入

```
6
1 1 1 1 1 1```

### 输出

```
0 720```

## 样例 #2

### 输入

```
1
1000000```

### 输出

```
499833345 1```

## 样例 #3

### 输入

```
7
123 451 234 512 345 123 451```

### 输出

```
339854850 882811119```

# 题解

## 作者：Tyyyyyy (赞：12)

## CF1612G
[原题链接](https://codeforces.com/contest/1612/problem/G)
### 题意简述
- 给定一个长为 $m$ 的序列 $c_1,c_2,\dots,c_m$。
- 序列 $A$ 满足：对于所有 $1 \leq i \leq m$，$i$ 在 $A$ 中出现了 $c_i$ 次。
- 定义一个序列 $A$ 的值如下：
$$f(A)=\sum_{1 \leq i<j \leq n,a_i=a_j}j-i$$
- 求满足条件的 $f(A)$ 的最大值，及在取最大值时有多少种序列 $A$。
- $1 \leq m \leq 5 \times 10^5,1 \leq c_i \leq 10^6$。

### 分析
我们先来考虑如何计算一个确定的序列 $A$ 的 $f(A)$。

考虑对于一个元素 $k$，它在 $A$ 中出现的位置排序后为 $\{p_1,\dots,p_x\}$。

具体地，我们可以举一个实例：设该元素出现的位置是 $\{2,3,5,8,9\}$。

于是该元素对 $f(A)$ 的贡献是 $(3-2)+(5-2)+(8-2)+(9-2)+(5-3)+(8-3)+(9-3)+(8-5)+(9-5)+(9-8)$。

化简可以得到，$2$ 被减了 $4$ 次，$3$ 被减了 $2$ 次，$5$ 被抵消，$8$ 被加了 $2$ 次，$9$ 被加了 $4$ 次。

更进一步推广，我们可以得到该元素对 $f(A)$ 的贡献就是 $p_1(1-x)+p_2(3-x)+\dots+p_x(x-1)$。

即系数序列 $B=\{1-x,3-x,\dots,x-3,x-1\}$。

于是我们考虑如何使 $f(A)$ 最大化。

考虑生成一个系数序列。对于每个 $c_i$，我们将 $1-c_i,3-c_i,\dots,c_i-1$ 加入到序列中。

此时对于该系数序列 $P$，有 $f(A)=\sum_{i=1}^n i \times p_i$。

现在，我们的问题就是要重排这个系数序列 $P=\{p_1,p_2,\dots,p_n\}$，让 $\sum_{i=1}^ni \times p_i$ 最大。其中 $n=\sum c_i$。

显然有结论：当 $P$ 升序排列时，答案最大。

这可以通过微扰证明：假设在升序排列的 $P$ 中交换任意两项 $p_i,p_j$（假设 $i<j$，即 $p_i\leq p_j$），则前后的 $f(A)$ 的变化值为 $D=i\times p_i+j\times p_j-j\times p_i-i\times p_j=p_i(i-j)+p_j(j-i)$。因为 $p_i \leq p_j$，所以显然有 $D \leq 0$。所以邻项交换不会使答案更优。

如何实现这个操作呢？我们可以发现，时间主要花费在了将 $1-c_i,3-c_i,\dots,c_i-1$ 加入序列这一步。

事实上，我们并不需要把这个序列生成出来。我们可以使用一个差分数组，存储每个元素在序列中出现的次数。形式化地讲，对于每个 $c_i$，在差分数组中对应的操作可以转化为 $d_{1-c_i} \gets d_{1-c_i}+1,d_{c_i-1} \gets d_{c_i-1}-1$。
因为 $1-c_i$ 可能为负，我们可以把整个差分数组在数轴上向正方向平移。

接下来我们从小到大遍历差分数组。因为系数序列的特殊性，我们可以得到在差分数组中计算前缀的递推式 $d_i=d_{i-2}+d_i$。

于是对于每个系数数组中出现 $cnt$ 次的元素 $p$，我们把 $p$ 作为我们尚未分配的 $cnt$ 个最小的 $a_i$ 的系数。它对答案的贡献就是 $p \times sum$，其中 $sum$ 是所选 $a_i$ 的和。

因为在 $A$ 中的不同元素中，有 $cnt$ 个元素为系数数组贡献了 $p$，所以可行的方案数就是这 $cnt$ 个元素的排列数 $cnt!$。根据乘法原理，总方案数就是 $cnt_1!cnt_2!\dots cnt_k!$。

理论时间复杂度为 $O(m+\max\{c_i\})$。代码中为了方便直接把上限设为了 $2\times 10^6$。

Code：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll mod=1e9+7;
const int N=1e6+10;
int m,x;
ll fact[N],d[N<<1],ans,cnt=1,now;
ll ask(ll l,ll r){return ((r-l+1)*(l+r)/2)%mod;}
int main() 
{
    fact[0]=1;
    for (int i=1;i<N;i++)fact[i]=fact[i-1]*i%mod;
    scanf("%d",&m);
    for(int i=1;i<=m;i++){scanf("%d",&x);d[1000002-x]++,d[1000002+x]--;}
    for(int i=2;i<N<<1;i++) 
	{
        d[i]+=d[i-2];
        ans=(ans+ask(now+1,now+d[i])*(i-1000001))%mod;
        now+=d[i],cnt=(cnt*fact[d[i]])%mod;
    }
    printf("%lld %lld",ans,cnt);
}
```

---

## 作者：pengyule (赞：5)

**本题可以积累一个较常见的套路。**

对于每一个 $c_i$，考虑这 $c_i$ 个数产生的贡献。如果设其在 $a$ 中的下标为 $x_j(j=1,2,...,c_i;x_j<x_{j+1})$，则它们产生总贡献是
$$
\sum_{1\le j<k\le c_i}(x_k-x_j)
$$
化简得
$$
\sum_{j=1}^{c_i}(2j-c_i-1)x_j
$$
单个元素产生的贡献是 $(2j-c_i-1)x_j$，可以把括号中的看成权值。

由此，这所有 $\sum c_i$ 个数的贡献从大到小排序，依次给予下标 $n,n-1,...,1$，既可以实现“大乘大”的贪心策略。
同时，对于第二问（方案数），权值相同的 $l$ 个数可以全排列，产生 $\times l!$ 的方案。

但这样的复杂度为 $O(\sum c_i)$ 的。
考虑到**实际有用的是权值的大小**，可以建一个权值桶。对于每个 $c_i$，第 $1-c_i,3-c_i,...,c_i-3,c_i-1$ 个桶都需要加 1。
从大到小枚举权值，照旧给桶里的数分配下标。

对于实现方面，统一加可以用差分（稍加改动）。
$O(n)$。
代码细节：权值会有负数，但绝对值不超过 $10^6$，可以先统一加上 $10^6$ 便于数组标记。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e6+5,mod=1e9+7;
typedef long long ll;
ll n,m,val,ans=1,c[N],b[2][N],jc[N];
signed main(){
	cin>>m;
	for(int i=1;i<=m;i++)cin>>c[i],n+=c[i];
	for(int i=1;i<=m;i++){
		ll x=1e6+1-c[i],y=1e6+c[i]-1;
		b[x&1][x]++,b[x&1][y+1]--;
	}
	jc[0]=1;
	for(int i=1;i<=2e6;i++)b[0][i]+=b[0][i-1],b[1][i]+=b[1][i-1],jc[i]=jc[i-1]*i%mod;
	for(int i=2e6;i;i--){
		val=(val+(n+n+1-b[i&1][i])*b[i&1][i]/2%mod*((i-1000000)%mod+mod)%mod)%mod;
		ans=ans*jc[b[i&1][i]]%mod;
		n-=b[i&1][i];
	}
	cout<<val<<' '<<ans;
}

```

*文首所指的套路指的是从第一公式到第二公式的化简。*

---

## 作者：bsdsdb (赞：2)

题意：给定序列 $\{c_n\}$，序列 $\{a_{\sum c}\}$ 合法当且仅当 $i$ 恰好在 $\{a\}$ 中出现了 $c_i$ 次，定义 $f(a):=\sum_{i<j,a_i=a_j}j-i$，最大化该值，并回答多少个 $\{a\}$ 能使 $f(a)$ 最大化。

提示：写个能输出所有使 $f(a)$ 最大化的 $a$ 的暴力，并观察：

1. 输入 $\{c_n\}$，再输入一个 $\{c_n\}$ 的乱序排列，这两个输出有什么规律？如何证明？
2. 输入 $n$ 和 $n$ 个 `1`，输出有什么规律？如何证明？
3. 输入 `3\n4 4 4`，输出的 $a$ 的前三个数和后三个数有什么规律？如何证明？
4. 输入 $\{c_n\}$ 以及 $\{c'_n\}:c'_i=\begin{cases}c_i,c_i<\max c\\c_i-2,c_i=\max c\end{cases}$，二者的输出有何关系？如何证明？

（提示 1 解答）如果存在一个 $1$ 到 $n$ 的排列 $\{p\}$ 满足 $c_i=c'_{p_i}$，那么对于 $c'$ 的答案做了贡献的 $a'$，构造 $a_i=p_{a'_i}$ 即可对 $c$ 的答案做贡献，反之亦然，所以一个序列的两种排列答案相同。又有一个定理：定义「序列 $c$ 的 $b$」为一个序列 $\{b_n\}$，满足 $b_i$ 是 $i$ 在 $c$ 中的出现次数，那么一个 $b$ 对应着一个 $c$ 的全排列（证：$c'$ 是 $c$ 的重排，当且仅当他们拥有相同的 $b$），所以我们可以使用 $b$ 来计算答案。下文定义 $m:=\max\{x\mid b_x>0\}$。（提示 2 解答）如果 $m=1$，那么 $\max f(a)=0$，因为没有 $i<j$ 使得 $a_i=a_j$。方案数显然为 $b_m!$。

（提示 3 解答）否则，$a$ 的前后 $b_m$ 个数分别为使得 $c_i=m$ 的 $i$ 各一个（称这些 $i$ 为「目标数」）。证：定义 $l_i$ 为 $i$ 在 $a$ 中最左边的出现的位置，$r_i$ 同理，那么 $l_i,r_i$ 对 $f(a)$ 的贡献为 $(r_i-l_i)(c_i-1)$。如果 $\exist i:l_i\le b_m\lor r_i>\sum c-b_m$（即 $i$ 占用了目标数的位置），$j:c_j=m,l_j> b_m\lor r_j\le\sum c-b_m$（即 $j$ 是被占用的目标数），那么考虑更换 $i$ 和 $j$ 的位置使得 $l'_j<l'_i\le r'_i<r'_j$，那么：

$$
\begin{aligned}
\Delta f(a)=&(r'_j-l'_j)(c'_j-1)+(r'_i-l'_i)(c'_i-1)\\
&-(r_j-l_j)(c_j-1)-(r_i-l_i)(c_i-1)\\
\xlongequal{c_j=c'_j,c_i=c'_i}&(r'_j-l'_j-(r_j-l_j))(c_j-1)\\
&-(r'_i-l'_i-(r_i-l_i))(c_i-1)\\
>&0
\end{aligned}
$$

更换后更优。（提示 4 解答）所以将出现最多的数放在两边之后，对 $f(a)$ 贡献 $(\sum_{i=\sum c-b_m+1}^{\sum c}i-\sum_{i=1}^{b_m}i)(m-1)$，方案数贡献 $(b_m!)^2$ 后，剩下的数递归解决即可，记得对 $\{b\}$ 和 $\{c\}$ 做更改。

```cpp
#include <bits/stdc++.h>
#pragma GCC optimize(1, 2, 3, "inline", "Ofast")
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
const ldb eps = 1e-8;
const vector<ll> millerrabin = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
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

const ll MAXN = 5e5 + 5, mod = 1e9 + 7;

ll n, a[MAXN], cnt = 1, facc[MAXN << 2], app[MAXN << 2];

ll fac(ll x) {
	return facc[x];
}

ll cal(ll l, ll mx) {
	while (mx >= 2 && !app[mx]) {
		--mx;
	}
	if (mx <= 1) {
		(cnt *= fac(app[1])) %= mod;
		return 0;
	}
	ll tmp = app[mx];
	app[mx - 2] += tmp, app[mx] = 0;
	(cnt *= fac(tmp) * fac(tmp) % mod) %= mod;
	return ((mx - 1) * (l - tmp) % mod * tmp % mod + cal(l - tmp * 2, mx)) % mod;
}

int main() {
	facc[0] = 1;
	for (ll i = 1; i <= 2e6; ++i) {
		facc[i] = facc[i - 1] * i % mod;
	}
	read(n);
	ll s = 0;
	for (ll i = 1; i <= n; ++i) {
		read(a[i]);
		s += a[i];
		++app[a[i]];
	}
	write(cal(s, 1e6 + 1)), space(), write(cnt), enter();
	return 0;
}

;             ;;;;;;;;          ;
;                   ;          ; ;
;                  ;          ;   ;
;                 ;          ;     ;
;                ;          ;;;;;;;;;
;               ;          ;         ;
;              ;          ;           ;
;;;;;;;;;;;   ;;;;;;;;   ;             ;

   ;                        ;
  ;                          ;
 ;                            ;
;                              ;
;                              ;
;                              ;
 ;                            ;
  ;         ;;          ;;   ;
   ;        ;;          ;;  ;

```

---

## 作者：yshpdyt (赞：1)

## 题意
给定一个颜色序列 $c_i$，记 $A$ 为满足颜色 $x$ 恰好出现过 $c_x$ 次所形成的序列，令：
$$f(A)=\sum\limits_{i<j,a_i=a_j}j-i$$ 

求最大的 $f(A)$ 以及取得最大值的序列数量。

## Sol
令 $n$ 为 $A$ 的序列长度。

考虑对于一个确定的 $A$ 如何快速求贡献，不同颜色贡献独立，一个位置的贡献，只和其所处位置，左右颜色相同的位置数量有关，记在 $i$ 位置填 $x$，$[1,i-1]$ 中有 $l_i$ 个 $x$ 颜色位置，$[i+1,n]$ 有 $r_i$ 个 $x$ 颜色位置，于是我们的贡献拆成了：

$$f(A)=\sum\limits_{i=1}^n (l_i-r_i)i$$

现在考虑如何构造 $A$，将每种颜色独立出来，从左到右排开，前面的系数依次为：$\{-c_x+1,-c_x+3,\cdots,c_x-3,c_x-1\}$。

贪心地考虑，肯定是给尽可能大的系数分配靠右的位置，将每种颜色的系数序列求出来，合并到一起从小到大从前往后分配位置即可求得最大 $f(A)$。

至于方案数，不同的颜色系数序列可能重叠，相同颜色不存在两个相同系数，于是对于系数相同的颜色位置可以任意交换，对每种系数乘相同颜色数量的阶乘即可。

这样复杂度是 $O(mV)$ 的，瓶颈在于求系数序列。

注意到这其实是个公差为二的等差数列，于是我们根据 $c_i$ 的奇偶性分别用差分数组实现区间加，同样可以求得每种系数的相同颜色数量，时间复杂度 $O(m+V)$。
## Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 2000005
#define endl "\n" 
#define fi first
#define se second
using namespace std;
const ll mod=1e9+7;
const ll inf=1e18;
const double eps=1e-6;
ll n,m,a[N],fac[N];
ll getsum(ll l,ll r){
    __int128 p=(__int128)(r+l)*(r-l+1)/2%mod;
    return (p%mod);
}

ll odd[N],even[N],f[N];
int main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    cin>>n;
    fac[0]=1;
    ll tot=0;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        tot+=a[i];
        m=max(m,a[i]);
        fac[i]=fac[i-1]*i%mod;
    }
    for(int i=1;i<=n;i++){
        if(a[i]&1)even[m-a[i]+1]++,even[m+a[i]]--;
        else odd[m-a[i]+1]++,odd[m+a[i]]--;
    }
    for(int i=-m+1;i<=m-1;i++){
        odd[m+i]=odd[m+i-1]+odd[m+i];
        even[m+i]=even[m+i-1]+even[m+i];
        if(i%2)f[m+i]=odd[m+i];
        else f[m+i]=even[m+i];
    }
    ll res=1,sum=0,cnt=0;
    ll l=tot,r=tot;
    for(int i=m-1;i>=-m+1;i--){
        l=r-f[i+m]+1;
        sum=(sum+getsum(l,r)*i%mod+mod)%mod;
        res=(res*fac[f[i+m]]%mod)%mod;
        r=l-1;
    }
    cout<<sum<<" "<<res<<endl;
    return 0;
}
```

---

## 作者：allenchoi (赞：1)

### 科技：
差分
### 思路：
容易想到拆分贡献。  
设 $n=\sum_{i=1}^{m}c_i$，$a_i$ 表示第 $i$ 个数的种类，$t_i$ 表示这个数列中有多少个 $a_i$，$p_i$ 表示第 $i$ 个数是从左向右数第几个 $a_i$（$1\le i \le n$）。  
那么，容易想到 $f(A) = \sum_{i=1}^{n}i(p_i-1)-i(t_i-p_i)=\sum_{i=1}^{n}i(2p_i-t_i-1)$。  
设 $k_i=2p_i-t_i-1$ ，那么最大化 $\sum_{i=1}^{n}k_ii$ 就是尽量使 $k_i$ 单调递增（因为 $i$ 是由小到大的，我们想贪心让大乘大，小乘小）。  
$k_i$ 单调递增是肯定能实现的。每一种元素所产生的 $k_i$ 都是：$1-c_i,3-c_i,5-c_i...c_i-1$。  
互不相同且单调递增，无需调整（当然也不能调整）。而不同元素的先后顺序对于 $k_i$ 是影响的，所以可以任意调整以实现单调递增。  
那么，最大值就是将所有 $k_i$ 排序后乘上对应的 $i$。  
我们发现，$k_i\in [-10^6,10^6]$，逐一枚举是可接受的。  
那么，如何确定每种 $k_i$ 的数量（设为 $r_i$）？  
再回头看一下每种元素产生的 $k_i$：$1-c_i,3-c_i,5-c_i...c_i-1$。  
一个公差为 $2$ 的等差数列。
那我们不妨设 $q_i=r_i-r_{i-2}$。  
那么，每增加一种元素，就是让 $q_{1-c_i}+1,q_{c_i-1+2}-1$。  
接着，从小到大枚举 $k_i$，用一个变量 $cnt$ 表示已经到了数列中的第几个数。$r_i$ 由 $r_{i-2}+q_i$ 得到，最大值加上 $i\sum_{j=cnt+1}^{cnt+r_i}j$，$cnt$ 加上 $r_i$。  
然后，方案数又怎么求呢？  
考虑到相等的 $k_i$ 之间的顺序是随意的，于是方案数等于 $\Pi (r_i!)$。   
注意，$q_i$ 的下标可能是负数，所以我们要将整个数组向右移（下标统一加上一个数）。
### 代码：
~~~cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e6 + 10,mod = 1e9 + 7,s = 1e6 + 1,inv = 500000004;
int n,cnt,maxn,num = 1,q[N],fac[N];
int sum(int x,int y)
{
	x %= mod,y %= mod;
	return 1LL * (x + y) * (y - x + 1) % mod * inv % mod;
}
int main()
{
	fac[0] = 1;
	for(int i = 1;i <= 1000000;i++) fac[i] = 1LL * fac[i - 1] * i % mod;
	scanf("%d",&n);
	for(int i = 1,x;i <= n;i++)
	{
		scanf("%d",&x);
		q[1 - x + s]++;
		q[x + 1 + s]--;
	}
	for(int i = 2;i < N;i++)
	{
		q[i] += q[i - 2];
		maxn = (maxn + 1LL * ((i - s + mod) % mod) * sum(cnt + 1,cnt + q[i]) % mod) % mod;
		cnt = (cnt + q[i]) % mod;
		num = 1LL * num * fac[q[i]] % mod;
	}
	printf("%d %d\n",maxn,num);
	return 0;
}
~~~

---

## 作者：Loser_Syx (赞：0)

还是比较典的。

首先，对于某个数组 $A$，他的答案可以被表示为 $\sum^{len}_{i=1} i \times (a_i - b_i)$，其中 $a_i$ 是在它前面的同颜色个数，$b_i$ 是在它后面的个数。

对于同种颜色，我们把它贡献拆开，那么就是分别是 $1-c_i,3-c_i,\ldots,c_i-3,c_i-1$ 个 $i$。

自然地，我们想到对于每一个权值，给大的赋尽可能大的，给小的赋尽可能小的，这时候就需要实现一个排序。

由于 $\sum c_i$ 很大，这时候观察到每个数的贡献都差 $2$，考虑差分计算。同种权值的顺序先后无关，所以才有的方案数。

于是复杂度 $O(n)$。

[code](https://codeforces.com/contest/1612/submission/292627077)。

---

## 作者：Hanx16Kira (赞：0)

# Max Sum Array

[Luogu CF1612G](https://www.luogu.com.cn/problem/CF1612G)

## Solution

分开讨论每一种颜色。

假设一个颜色出现的位置为 $p_1,p_2,p_3,\dots,p_n$。拆一下贡献的式子，发现对于一个位置 $p_i$，它最后会对答案造成 $(2i-n-1)p_i$ 的贡献。由于每个颜色出现的次数固定，因此所有的系数也是固定的，所以只需要找到一种 $p$ 的分配方案使得答案最小即可。不难发现 $p$ 只需要按照系数的大小关系分配，系数大的 $p$ 也分配大的位置即可。

对于方案的求法，当两个位置的系数相等的时候，这两个位置一定可以交换且不影响答案。所以记 $\operatorname{cnt}_i$ 表示系数为 $i$ 的位置个数，那么最后的方案数应当为 $\displaystyle\sum\operatorname{cnt}_i!$。

如果直接按照上面的做法做，时间复杂度是 $\mathcal O(m^2)$ 的。发现每一个颜色对系数桶的贡献其实相当于是一个步长为 $2$ 的区间加，那么直接使用差分快速维护系数桶即可。

时间复杂度 $\mathcal O(m)$。

```cpp
int N, cnt[_N];
mint fac[_N];
void init(int n) {
    fac[0] = 1; For(i, 1, n) fac[i] = fac[i-1] * i;
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N; init(M);
    For(i, 1, N) {
        int x; cin >> x;
        ++cnt[M-x], --cnt[M+x];
    }
    i64 sum = 0;
    mint ans = 0, tot = 1;
    auto calc = [](i64 l, i64 r)->mint {
        return (l + r) * (r - l + 1) / 2 % mod;
    };
    For(i, 2, M << 1) {
        cnt[i] += cnt[i-2];
        ans += calc(sum + 1, sum + cnt[i]) * (mint(i) - M + 1);
        tot *= fac[cnt[i]];
        sum += cnt[i];
    }
    cout << ans << ' ' << tot << '\n';
}
```

---

