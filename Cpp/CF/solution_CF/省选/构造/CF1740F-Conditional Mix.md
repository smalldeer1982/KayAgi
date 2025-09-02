# Conditional Mix

## 题目描述

Pak Chanek is given an array $ a $ of $ n $ integers. For each $ i $ ( $ 1 \leq i \leq n $ ), Pak Chanek will write the one-element set $ \{a_i\} $ on a whiteboard.

After that, in one operation, Pak Chanek may do the following:

1. Choose two different sets $ S $ and $ T $ on the whiteboard such that $ S \cap T = \varnothing $ ( $ S $ and $ T $ do not have any common elements).
2. Erase $ S $ and $ T $ from the whiteboard and write $ S \cup T $ (the union of $ S $ and $ T $ ) onto the whiteboard.

After performing zero or more operations, Pak Chanek will construct a multiset $ M $ containing the sizes of all sets written on the whiteboard. In other words, each element in $ M $ corresponds to the size of a set after the operations.

How many distinct $ ^\dagger $ multisets $ M $ can be created by this process? Since the answer may be large, output it modulo $ 998\,244\,353 $ .

 $ ^\dagger $ Multisets $ B $ and $ C $ are different if and only if there exists a value $ k $ such that the number of elements with value $ k $ in $ B $ is different than the number of elements with value $ k $ in $ C $ .

## 说明/提示

In the first example, the possible multisets $ M $ are $ \{1,1,1,1,1,1\} $ , $ \{1,1,1,1,2\} $ , $ \{1,1,1,3\} $ , $ \{1,1,2,2\} $ , $ \{1,1,4\} $ , $ \{1,2,3\} $ , and $ \{2,2,2\} $ .

As an example, let's consider a possible sequence of operations.

1. In the beginning, the sets are $ \{1\} $ , $ \{1\} $ , $ \{2\} $ , $ \{1\} $ , $ \{4\} $ , and $ \{3\} $ .
2. Do an operation on sets $ \{1\} $ and $ \{3\} $ . Now, the sets are $ \{1\} $ , $ \{1\} $ , $ \{2\} $ , $ \{4\} $ , and $ \{1,3\} $ .
3. Do an operation on sets $ \{2\} $ and $ \{4\} $ . Now, the sets are $ \{1\} $ , $ \{1\} $ , $ \{1,3\} $ , and $ \{2,4\} $ .
4. Do an operation on sets $ \{1,3\} $ and $ \{2,4\} $ . Now, the sets are $ \{1\} $ , $ \{1\} $ , and $ \{1,2,3,4\} $ .
5. The multiset $ M $ that is constructed is $ \{1,1,4\} $ .

## 样例 #1

### 输入

```
6
1 1 2 1 4 3```

### 输出

```
7```

## 样例 #2

### 输入

```
7
3 5 4 3 7 4 5```

### 输出

```
11```

# 题解

## 作者：18Michael (赞：10)

首先若可重集内元素个数不满 $n$ 个，可以通过补 $0$ 补到 $n$ 个。同时我们发现，对于可重集内两个集合 $i,j$，若集合大小分别为 $M_i$ 和 $M_j$ 且 $M_i>M_j$，则 $i$ 中存在一个数可以取出放入 $j$ 中。也就是说对于两个可重集 $M,N$，如果对于 $\forall 1\le k\le n$ 都有 $\sum_{i=1}^k M_i\ge\sum_{i=1}^k N_i$，那么若 $M$ 能被表示出来则 $N$ 也可以被表示。

那么 $\sum_{i=1}^k M_i$ 的上界是多少呢？对于出现次数小于 $k$ 的数，肯定是可以都选的；对于出现次数大等于 $k$ 的数，至多只能选 $k$ 个。所以假设 $cnt_i$ 表示 $i$ 出现的次数，那么 $\sum_{i=1}^k M_i\le\sum_{i=1}^n \min(k,cnt_i)$，同时不难构造出一个可重集 $M$ 使得等号都成立，因此问题转化为求满足该条件的集合有多少个。

从大到小选数。设 $f_{i,j,k}$ 表示前 $i$ 个，和为 $j$，已选的最小的数为 $k$，转移可以用前缀和优化至 $O(1)$。同时注意到第一维可以滚动掉，且 $k\le\frac{n}{i}$，那么总时间复杂度就是 $O(n^2\ln n)$ 的，空间复杂度 $O(n^2)$。

## Code

```cpp
#include<bits/stdc++.h>
#define mod 998244353
using namespace std;
int n,i0=0,i1=1;
int a[2002],cnt[2002],sum[2002];
int f[2][2002][2002];
inline bool cmp(int x,int y)
{
	return x>y;
}
inline void upd(int &x,int y)
{
	if((x+=y)>=mod)x-=mod;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i)scanf("%d",&a[i]),++cnt[a[i]];
	sort(cnt+1,cnt+n+1,cmp);
	for(int i=0;i<=n;++i)for(int j=f[0][0][i]=1;j<=n;++j)sum[i]+=min(i,cnt[j]);
	for(int i=1,u;i<=n;++i,i0^=1,i1^=1)
	{
		u=n/i;
		for(int j=0;j<=sum[i];++j)f[i1][j][u+1]=0;
		for(int k=u;~k;--k)for(int j=0;j<=sum[i];++j)upd(f[i1][j][k]=(j>=k? f[i0][j-k][k]:0),f[i1][j][k+1]);
	}
	return 0&printf("%d",f[i0][n][0]);
}
```


---

## 作者：yanchengzhi (赞：5)

update on 2023.1.3：修改了一些不通顺的地方。

非常妙的转化。

对满足某种条件的可重集计数，可以先思考如何判定一个可重集满足条件。

设数字 $i$ 的出现次数为 $cnt_i$，可重集中的元素为 $M_i$，且强制让其大小为 $n$，不足的补 $0$。

首先，对于一个大小为 $k$ 的集合 $M$，它合法，有一个必要条件：$\sum_{i=1}^{k}M_i\leq \sum_{i=1}^{n}\min(k,cnt_i)$。

其次，如果两个可重集的大小相等，我们肯定希望其中的元素尽量大，因为这样才最有可能不满足条件。

也就是说，我们可以把 $M_i$ 从大到小排序，判断每个前缀 $1,2,3\cdots k$，是否满足 $\sum_{i=1}^{k}M_i\leq \sum_{i=1}^{n}\min(k,cnt_i)$ 即可。

知道了这步转化之后本题就很简单了，我们直接对这样的集合 $M$ DP。

设 $f(i,j,k)$ 表示从大到小考虑了集合 $M$ 的前 $i$ 个元素，元素和为 $j$，其中最小的数为 $k$ 的方案数。

注意到 $k\leq \lfloor\frac{n}{i}\rfloor$，那么使用前缀和优化可以做到 $\mathcal{O}(n^2\log n)$。

代码：

```c++
const int mod = 998244353;
const int maxn = 2005;
void amod(int &x, int y) {
	x = x + y >= mod ? x + y - mod : x + y;
}
int n, a[maxn], cnt[maxn], lim[maxn];
int f[2][maxn][maxn];
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
		cnt[a[i]]++;
	}
	for(int i = 0; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			lim[i] += min(i, cnt[j]);
		}
		f[0][0][i] = 1;
	}
	for(int i = 1, now = 0, cur = 1; i <= n; i++, now ^= 1, cur ^= 1) {
		int x = n / i;
		for(int j = 0; j <= lim[i]; j++) {
			f[cur][j][x + 1] = 0;
		}
		for(int k = x; k >= 0; k--) {
			for(int j = 0; j <= lim[i]; j++) {
				f[cur][j][k] = j >= k ? f[now][j - k][k] : 0;
				amod(f[cur][j][k], f[cur][j][k + 1]);
			}
		}
	}
	cout << f[n & 1][n][0] << '\n';
	return 0;
}

```

---

## 作者：Twig_K (赞：3)

[cnblogs](https://www.cnblogs.com/wanggk/p/-/CF1740F)

合并若干次后的状态是几个大集合，把每个集合堆成一堆，每个集合的大小就是这堆的高度 $H_i$。

不妨**设 $H$ 不增**，否则并不是本质不同的状态。

![](https://cdn.luogu.com.cn/upload/image_hosting/o0gspj18.png)

考虑如何检验上述状态是否合法，我们要求每一堆没有相同颜色，那么按照**出现次数**从大到小加入颜色，每次从左往右将能叠高的堆叠高一层。

如果高度序列可能被达到，那么该最终状态合法。

因为我们是贪心地向上叠（先消耗出现次数多的颜色，先消耗比较高的堆，最可能合法），所以我们发现，**对于一个合法局面，把前面堆的元素移到后面，一定是合法的。**

当然，移动完之后仍然需要保证**序列 $H$ 不增**，否则会重复统计。

![](https://cdn.luogu.com.cn/upload/image_hosting/obvsh710.png)

于是我们只需要找到**前面的堆最多**的状态，再统计不超过这个的局面数量就可以了。这个非常简单，只需要所有颜色都放一个前缀就可以了（最后面的堆可能为空）：

![](https://cdn.luogu.com.cn/upload/image_hosting/74vp1urh.png)

我们得到了尽可能最靠前放的序列，记其前缀和为 $Sum$（如图），合法序列 $H_n$ 一定满足：

- 单调不增。
- $\forall i \in [1,n],\sum_{j \leq i} \leq Sum_i$

找完性质之后 DP 就不难了，设 $f_{i,j,k}$ 表示到第 $i$ 项，目前前缀和为 $j$，最小值**大于等于** $k$ 的方案数。

$$f_{i,j,k}=f_{i-1,j,k+1}+f_{i-1,j-k,k}$$

前一项表示这一位填的数**大于** $k$，后一项表示这一位恰好填 $k$。

最后答案就是 $f_{n,n,0}$。

第一维可以滚动数组，另外由于 $k \leq \frac{j}{i}$，所以 $k$ 是 $\log$ 级别的，因此复杂度是对的。

[CF 提交记录](https://codeforces.com/contest/1740/submission/316898134)

```cpp
#include<bits/stdc++.h>
#define For(i,il,ir) for(int i=(il);i<=(ir);++i)
#define Rof(i,ir,il) for(int i=(ir);i>=(il);--i)
using namespace std;
typedef long long ll;
const int maxn=2005;
const ll mod=998244353;
void qadd(ll &x,ll y){ x=(x+y>=mod)?(x+y-mod):(x+y); }

int n,x;
int c[maxn],h[maxn],s[maxn];
ll f[2][maxn][maxn];

signed main()
{
	scanf("%d",&n);
	For(i,1,n) scanf("%d",&x),c[x]++;
	For(i,1,n) For(j,1,c[i]) h[j]++;
	For(i,1,n) s[i]=s[i-1]+h[i];
	
	For(k,0,n) f[0][0][k]=1ll;
	For(i,1,n){
		int nw=i&1,lt=(i&1)^1;
		For(j,0,s[i])
			Rof(k,j/i,0){
				f[nw][j][k]=0;
				if(k+1<=j/i) qadd(f[nw][j][k],f[nw][j][k+1]);
				if(i==1 || k<=(j-k)/(i-1)) qadd(f[nw][j][k],f[lt][j-k][k]);
			}
	}
	printf("%lld\n",f[n&1][n][0]);
	return 0;
}
```

---

## 作者：BreakPlus (赞：2)

+ 我们发现相等的数不能选两个及以上。将每个数的出现次数数出来，再并成一个可重集，并倒序排序。如 $\{1,1,1,2,3,4\}$ 变为 $\{3,1,1,1\}$，后者记作序列 $D$。 我们对 $M$ 也倒序排序考虑。

+ 考虑划分集合很困难，所以我们考虑判断一个 $M$ 是否可行。

+ $M$ 的总和为 $n$，而 $M$ 中较大的数越多，实现的可能性越小。

+ 联想到度序列的判定，我们不妨假设若有两个待定的答案 $M_1$ 和 $M_2$，若 $M_1$ 可行，$M_1$ 的每一个前缀和都大于等于 $M_2$ 的对应前缀和。序列长度不足可以补 $0$（不要学我不会补 $0$ 就把自己做法叉了）。

+ 考虑找出较大的数尽量多的方案，即为 $M$ 的“上限”，就是每次记录 $|D|$，将序列 $D$ 整体减 $1$，去掉 $D$ 中为 $0$ 的数。如 $\{3,1,1,1\}$ 会变成 $\{4,1,1\}$。

+ 现在我们证明刚才的结论，可以使用调整法。若一个可行的答案 $M_1$ 中有两个元素 $x,y$ 满足 $x>y$，那么 $x$ 对应的集合中必然有一个元素在 $y$ 对应的集合中没有，可以把这个元素从 $x$ 移到 $y$。可以理解为，序列的“重心”可以不断右移。

+ 接下来设计一个 DP 即可。$f_{i,j,k}$ 表示考虑到第 $i$ 个数，$M$ 中前 $i$ 个数和为 $j$，第 $i$ 个数为 $k$。由于倒序排序，$k \le \dfrac{j}{i}$。这个 DP 可以前缀和优化。时间复杂度 $\mathcal{O}(n^2\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
const ll mod = 998244353;
ll read(){
	ll x; scanf("%d",&x); return x;
}
ll n,a[2005],cnt[2005],qz[2005],hz[2005];
ll f[2][2005][2005], g[2][2005][2005];
map<ll,ll>M;
ll G(ll i,ll j,ll k){
    if(i==0) return g[0][j][k];
    if(k<=j/i) return g[i&1][j][k];
    else return g[i&1][j][j/i];
}// 由于前缀和优化只做到了 j/i，k>j/i 的查询需要特殊处理
int main(){
	n=read();
	for(ll i=1;i<=n;i++) a[i]=read(), M[a[i]]++;
	for(ll i=1;i<=n;i++)
		for(auto p: M)
			qz[i] += min(i, p.second);
	f[0][0][n] = 1; g[0][0][n] = 1;
	for(ll i=1,op=1;i<=n;i++,op^=1){
		for(ll j=0;j<=n;j++)
			for(ll k=0;k<=n/i;k++) f[op][j][k]=g[op][j][k]=0;
		for(ll j=0;j<=qz[i];j++){
			for(ll k=0;k<=j/i;k++){
				if(j-k>qz[i]) continue;
				f[op][j][k] = (G(i-1,j-k,n) - (k?G(i-1,j-k,k-1):0) + mod); 
                if(f[op][j][k]>=mod) f[op][j][k]-=mod; 
                if(k) {
                    g[op][j][k] = (g[op][j][k-1] + f[op][j][k]);
                    if(g[op][j][k] >= mod) g[op][j][k] -= mod;
                }
                else g[op][j][k] = f[op][j][k];
			}
		}
	} 
	printf("%d\n", (1+f[n&1][n][0])%mod);
	return 0;
}
```

---

## 作者：intel_core (赞：2)



考虑如何判定一组可重集的大小 $x_1,x_2\cdots,x_k$ 合法。

因为所有的集合都是从一元集合并形成的，所以在不重复的情况下可以随意挪动里面的元素。

这里不妨规定 $x_1\ge x_2\ge \cdots\ge x_k$，然后此时可以发现，若 $x_i>x_j$，那么一定可以将 $i$ 可重集里面的一个元素挪到 $j$ 里面。

然后此时考虑 $y_i=\sum_{j=1}^i x_j$，若进行上述操作，则 $y_i,y_{i+1},\cdots,y_{j-1}$ 都会减一。所以感性理解一下，$y_i$ 整体越大，就越不容易满足条件。

所以我们现在考虑 $y_k$ 的上界是多少；直接从集合的角度不好考虑，我们换成从元素的角度考虑。我们依次枚举 $i$，对于 $i$ 来说，在这 $k$ 个集合之中最多有 $k$ 个，且 $i$ 在原序列中只有 $cnt_i$ 个，所以 $y_k \le \sum_{i=1}^n \min\{cnt_i,k \}$。

此时 $\text{DP}$ 的思路就很清晰了，我们令 $f_{i,j,k}$ 表示当前已经钦定了 $x_1,x_2,\cdots,x_i$ 的值，$y_i=j,x_i=k$ 时的方案数。

暴力转移即为直接枚举 $x_{i+1}$ 的值，可以用前缀和优化，复杂度 $O(n
^3)$。

注意到 $x_1,\cdots,x_i \ge k$，所以 $i\times k\le n$，状态数直接下降到 $O(n^2 \ln n)$，可以通过。



---

## 作者：Alex_Wei (赞：2)

[CF1740F Conditional Mix](https://www.luogu.com.cn/problem/CF1740F)

对于任意将可重集 $a$ 划分为若干不可重集 $S_1, S_2, \cdots, S_c$ 的方案，我们总可以构造操作方案使得达到该局面。

考虑判定一个 $M$ 是否合法。将 $M$ 从大到小排序，设 $\sum_{j = 1} ^ i M_i$ 的最大值为 $T_i$，即 $\sum \min(i, c_j)$，其中 $c_j$ 表示 $j$ 的出现次数，因为每个 $j$ 至多贡献 $\min(i, c_j)$ 次，则 $\sum_{j = 1} ^ i M_i\leq T_i$ 为 $M$ 合法的充要条件。必要性显然，充分性考虑调整法，每次总可以将较大集合的元素移动至较小集合。

因此，设 $f_{i, j, k}$ 表示当前考虑到大小不小于 $i$ 的 $S$，数量为 $j$ 且 $\sum |S| = k$ 的方案数，则 $i + 1\to i$ 相当于对重量为 $i$ 的物品做完全背包，得到转移
$$
f_{i, j, k} = f_{i + 1, j, k} + f_{i, j - 1, k - i}
$$
因为 $ij\leq n$，所以复杂度为 $\mathcal{O}(n ^ 2\ln n)$。[代码](https://codeforces.com/contest/1740/submission/184053402)。

---

## 作者：TernaryTree (赞：1)

这种性质题真的是一点都不会做啊。。

我们考虑一个合法的 $S$，将其从大到小排序。找出其中字典序最大的那一个记作 $M$，我们有如下性质：

> 考虑任意一个可能的集合 $S'$，同样从大到小排序。那么，其合法的充要条件是它的前缀和每一项都不超过 $M$ 的前缀和对应项。
>
> 必要性：由于两个序列的字典序与其前缀和的字典序关系等价，所以 $M$ 同时是前缀和字典序最大的合法序列；那么此时，不可能存在一个元素，从后面的集合移到前面的集合，因为这样会使前缀和某一项变大。要从这个集合变换得到其他集合，只可能从前面的集合选元素移到后面集合。
>
> 充分性不难证明。

可以设计出 dp: $f_{i,j,k}$ 表示前 $i$ 个，前缀和为 $j$，最后一个为 $k$ 的方案数。前缀和可以优化到 $\Theta(n^3)$，注意到 $k$ 是 $\Theta\left(\dfrac ni\right)$ 量级，调和级数得到 $\Theta(n^2\log n)$ 做法，可以通过。

---

## 作者：daniEl_lElE (赞：1)

$\text{Difficulty: }\color{red}\text{2600}$。

令 $cnt_i$ 为 $i$ 在 $a$ 中出现次数。

令 $lim_i$ 为前 $i$ 大的集合大小总和的最大值，不难发现 $lim_i=\sum_{j=1}^n\min(cnt_j,i)$。$^{[1]}$

考虑 $dp_{i,j,k}$ 表示考虑到 $i$ 集合，集合包含元素最大值为 $j$，总和为 $k$ 的方案数。转移枚举下一个集合大小为 $d\leq j$，朴素转移 $O(n^4)$，通过前缀和优化可以做到 $O(n^3)$，发现 $j\leq\dfrac{n}{i}$，可以优化到 $O(n^2\log n)$，可以通过。

$^{[1]}$：证明：考虑总共只有 $i$ 个集合，每个集合每种元素只能出现一次，故总共只能出现 $\min(cnt_j,i)$ 次。$lim_i\leq\sum_{j=1}^n\min(cnt_j,i)$。因容易构造故 $lim_i$ 取最大值。

[提交记录](https://codeforces.com/contest/1740/submission/200883093)。

---

## 作者：xiezheyuan (赞：0)

## 简要题意

有 $n$ 个集合，第 $i$ 个集合为 $\{a_i\}$。

你可以进行任意次操作（可以不进行操作），每次选择两个无交的集合，将其合并成一个集合。

所有操作完成后，令所有集合的大小组成的多重集为 $S$，你需要计算有多少种可能的 $S$。答案对 $998,244,353$ 取模。

$1\leq a_i\leq n\leq 2\times 10^3$。

## 思路

欲解决计数问题，先要解决判定性问题。发现这个判定性问题也不显然，于是先考虑这个判定问题。同时这个原题意我们不是很熟悉，考虑将其转成常见的模型。

假如我们已经得到了 $S$，如何判定它是不是合法的多重集？考虑合并的过程，本质上相当于考虑将每个元素分配到某个集合中。同时由于集合的不可重性质，重复的元素需要特殊处理。我们自然想到将所有元素相同的点合并为一个，然后限制其分配的集合个数小于等于出现次数。

到这里我们似乎已经可以建立一个严谨的模型了。记 $B_i=\sum_k [a_k=i]$。则我们对于每一种 $a_i$，建立一个右部点，对于多重集的每一个元素，建立一个左部点。限制左部点 $a_i$ 的度数不大于 $B_{a_i}$，限制右部点 $i$ 的度数恰好为 $i$，我们需要判断是否存在这样的二分图（二分图的每一条边对应每一个元素，二分图不能有重边，即这个图是简单二分图）。

判断二分图相对困难，这里我们引入 [Gale-Ryser 定理](https://en.wikipedia.org/wiki/Gale%E2%80%93Ryser_theorem)。

> **Gale-Ryser 定理**：给定一个 $n$ 个左部点，$m$ 个右部点的二分图，第 $i$ 个左部点的度数限制为 $p_i$，第 $i$ 个右部点的度数限制为 $q_i$。钦定 $p_1\geq p_2\geq \cdots\geq p_n,q_1\geq q_2\geq \cdots\geq q_m$，存在满足所有限制的二分图，当且仅当对于任意的 $1\leq k\leq n$，使得 $\sum_{i=1}^{k} p_i\leq \sum_{i=1}^{m}\min(q_i,k)$。

证明可以参考 [JCY_std 的一篇博客](https://www.cnblogs.com/JCY-std/p/17642946.html)。

知道这个定理后，我们就可以直接根据这个定理来判断一个多重集是否合法了。

现在来考虑如何计数，我们提前计算出 $L_i=\sum_{k=1}^{i}\min(B_k, i)$。那么相当于求出有多少个单调不降的子序列，使得总和为 $n$ 且长度为 $i$ 的前缀的和不大于 $L_i$（因为我们可以适当分配右部点的度数来满足这个限制，而这个限制最大只能调整到 $L_i$）。

dp，设 $f(i,j,k)$ 表示考虑到长度为 $i$ 的前缀，和为 $j$，最后一个数为 $k$ 的方案数。注意到 $k\leq \frac{n}{i}$，所以可以将状态数优化到 $O(n^2\log n)$，转移的话可以用后缀和优化。

时间复杂度 $O(n^2\log n)$。

## 代码

```cpp
#include <bits/stdc++.h>
//#define int long long
using namespace std;

const int N = 2005;
int n, bd[N], b[N], f[N][N], suf[N][N];

constexpr int mod = 998244353;
int Add(int x, int y){ return (x + y) >= mod ? (x + y - mod) : (x + y); }
int Sub(int x, int y){ return (x - y) < 0 ? (x - y + mod) : (x - y); }
int Mul(int x, int y){ return 1ll * x * y % mod; }

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> n;
    for(int i=1;i<=n;i++){
        int a; cin >> a;
        b[a]++;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++) bd[i] += min(i, b[j]);
    }
    int ans = 0;
    for(int i=1;i<=bd[1];i++) f[i][i] = 1;
    if(bd[1] >= n) ans++;
    for(int i=2;i<=n;i++){
        for(int j=1;j<=bd[i - 1];j++){
            int upb = min(n / (i - 1), j);
            suf[j][upb + 1] = 0;
            for(int k=upb;k;k--) suf[j][k] = Add(suf[j][k + 1], f[j][k]);
        }
        for(int j=1;j<=bd[i];j++){
            for(int k=1;k<=min(n / (i - 1), j);k++){
                f[j][k] = suf[j - k][k];
                if(j == n) ans = Add(ans, f[j][k]);
            }
        }
    }
    cout << ans << '\n';
    return 0;
}

// Written by xiezheyuan
```

---

## 作者：_Cheems (赞：0)

首先，每次选择两个交集为空的集合合并，等价于最终将原集合恰好拆分为若干个集合，每个集合内部无重复元素。

不妨记这些集合为 $A=\{M_1\dots M_n\}$，假如不够就补 $0$ 即可，令 $|M_1|\ge |M_2|\dots \ge |M_n|$。然后记 $cnt_i$ 为原序列中元素 $i$ 的出现次数。

考虑判定 $A$ 是否合法，注意到非常重要的一点：假如存在 $M_i>M_j$，那么 $M_i$ 中必然存在 $M_j$ 中没有的元素，可以调整一元素，令 $M_i-1$ 而 $M_j+1$。

于是不难想到，若有 $S=\{N_1\dots N_n\}$，且满足“字典序”（即从 $i=1$ 开始比较集合大小）比 $A$ 大，那么就能将 $S$ 调整为 $A$，即 $S$ 合法，$A$ 一定合法。

于是考虑找到一个合法且“字典序”最大的集合 $P$，容易想到，贪心地从 $i=1$ 开始尽量填满即可。

不过比较“字典序”还是太麻烦了，其实可以这样比较，假如 $\forall i,\sum_{j=1}^i |N_j|\ge \sum_{j=1}^i |M_j|$，那么就有 $S>A$。

对于刚刚构造的 $P$ 集合，显然有 $\sum_{j=1}^i |P_j|=\sum_{j=1}^n \min(i, cnt_j)$。

我们记 $P,A$ 前缀和分别为 $Lim_i,pre_i$，那么只要满足 $\forall i,pre_i\le Lim_i$ 就有 $A$ 合法。

于是就容易了，不妨设 $f_{i,s,j}$ 为填了 $A_1\dots A_i$，且 $pre_i=s,|A_i|=j$ 时，合法方案总数，转移考虑枚举 $|A_{i-1}|=k\ge j$ 即可。

于是得到了 $O(n^4)$ 暴力，可以前缀和优化至 $O(n^3)$，然后滚动数组滚掉第一维。由于 $|A_i|$ 递减，所以有 $j\le \frac Si$，直接优化至 $O(n^2\ln n)$ 级别。
#### 代码
写的比较难看。


```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
#define ADD(a, b) a = (a + b) % mod
const int N = 2e3 + 5, mod = 998244353;
int n, a[N], cnt[N], Lim[N], ans, f[2][N][N], g[N][N], s[N];

signed main(){
	cin >> n;
	for(int i = 1; i <= n; ++i) scanf("%lld", &a[i]), ++cnt[a[i]];
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j)
			Lim[i] += min(i, cnt[j]);
	for(int S = 1; S <= Lim[1]; ++S) f[1][S][S] = 1;
	for(int i = 2; i <= n; ++i){
		int id = (i & 1), _id = (id ^ 1); 
		for(int S = 0; S <= Lim[i - 1]; ++S)
			for(int j = 0; j <= S / (i - 1); ++j)
				g[S][j] = (g[S][j - 1] + f[_id][S][j]) % mod, f[_id][S][j] = 0;
		for(int S = 0; S <= Lim[i]; ++S)
			for(int j = 0; j <= S / i; ++j)
				if(S - j <= Lim[i - 1] && j <= S - j)
					f[id][S][j] = (g[S - j][min(S - j, (S - j) / (i - 1))] - g[S - j][min(j - 1, (S - j) / (i - 1))] + mod) % mod;
	}
	for(int i = 0; i <= n; ++i) ADD(ans, f[n & 1][n][i]);
	cout << ans;
	return 0;
}
```

---

