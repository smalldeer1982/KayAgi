# [ARC148E] ≥ K

## 题目描述

给定长度为 $n$ 的数列 $\{a_i\}$ 和一个自然数 $K$, 可以将 $\{a_i\}$ 打乱顺序重排，问多少种结果序列满足 $\forall i \in [1,n), a'_i + a'_{i+1} \ge K$。 答案对 $998244353$ 取模。

## 说明/提示

$ 2 \le n \le 2 \times 10^5$  
$ 0 \le a_i, K \le 10^9$

## 样例 #1

### 输入

```
4 5
1 2 3 4```

### 输出

```
4```

## 样例 #2

### 输入

```
4 3
1 2 3 3```

### 输出

```
12```

## 样例 #3

### 输入

```
10 7
3 1 4 1 5 9 2 6 5 3```

### 输出

```
108```

# 题解

## 作者：int_R (赞：16)

[更好的阅读体验](https://www.cnblogs.com/int-R/p/18330162/AT_arc148_e)

一种很新的思路。

考虑使得你放一个数的时候，要不然就是之后所有数都可以放在它旁边，要不然就是都不可以。

于是先排序，对于一个 $<\dfrac{k}{2}$ 的数 $a_i$，挂在第一个 $\geq k-a_i$ 的位置上（本质或许是双指针，但我并不想这么说）。

然后从大到小放所有 $\geq\dfrac{k}{2}$ 的数，放完一个数就把挂在它上面的数也放了，发现这样所有 $\geq\dfrac{k}{2}$ 的数和 $<\dfrac{k}{2}$ 的数分别满足最开始说的两种情况。

这样两种数放完以后会分别使得能放数的位置加一或减一，直接乘起来就完了。

最后除以每种数出现次数的阶乘来消去相同数的重复排列。

```cpp
#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<vector>
#define ll long long
using namespace std;
const int MAXN=2e5+10,mod=998244353;
int n,k,a[MAXN],cnt[MAXN];ll ans=1,T=1,P=1;
inline int ksm(ll a,int b=mod-2)
{
    ll ans=1;
    for(;b;b>>=1,a=a*a%mod)
        if(b&1) ans=ans*a%mod;
    return ans;
}
int main()
{
    // freopen("in.in","r",stdin);
    // freopen("out.out","w",stdout);
    cin.tie(0),cout.tie(0);
    ios::sync_with_stdio(0);
    cin>>n>>k;
    for(int i=1;i<=n;++i) cin>>a[i];
    sort(a+1,a+1+n);
    for(int i=1;i<=n&&a[i]<=(k-1)/2;++i)
    {
        if(a[n]+a[i]<k) cout<<"0\n",exit(0);
        ++cnt[lower_bound(a+1,a+n+1,k-a[i])-a];
    }
    for(int i=n;i&&a[i]>(k-1)/2;--i)
    {
        ans=ans*T%mod,++T;
        for(int j=1;j<=cnt[i];++j)
            ans=ans*T%mod,--T;
    }
    for(int i=1,j=1;i<=n;i=j)
    {
        while(a[j]==a[i]) ++j;
        for(int k=1;k<=j-i;++k)
            P=P*k%mod;
    }
    cout<<ans*ksm(P)%mod<<'\n';return 0;
}
```

---

## 作者：APJifengc (赞：15)

好题，全程没看题解做出来一道计数题感觉非常开心x（虽然爆了好几发 好几个 corner cases 没有判）

有一点想提的，就是这种题你可以先去观察答案，发现答案看起来就像是若干个数乘起来而不是加起来的，所以你就可以考虑答案应该是若干个组合数之类的乘积。这也算是一种技巧吧）

# 思路

题目要求相邻两个数之和大于等于 $k$，那么首先我们可以把所有的数分成两类，一类是 $\ge \frac{k}{2}$ 的数，一类是 $< \frac{k}{2}$ 的数、

这样分类后，我们可以发现 $\ge \frac{k}{2}$ 的数可以随便放，因为无论如何放两个数之和都 $\ge k$，而所有 $< \frac{k}{2}$ 的数就都不能相邻着放。

那么我们考虑 $\ge \frac{k}{2}$ 的数与 $< \frac{k}{2}$ 的数之间要怎么放。不难发现，如果放了一个 $< \frac{k}{2}$ 的数 $a$，那么与之相邻的数必须 $\ge k - a$。

我们可以考虑一种放数的顺序：从小到大考虑 $< \frac{k}{2}$ 的数 $a$。首先先把所有 $\ge k - a$ 的数全放进去，然后再往里面插 $a$。

假如说我们现在要放一个更大的数 $b$，那么此时 $\ge k - b$ 且 $< k - a$ 的数必定不可以和 $a$ 放在一起。那么也就是说，一旦这个数 $a$ 放下了，之后无论什么数都不可以与 $a$ 相邻了。

那么我可以考虑随时记录一下当前还有哪些空位还可以放数。当放所有 $\ge k - a$ 的数时，我们相当于把若干个数放到若干个空位中（因为 $\ge \frac{k}{2}$ 可以挨着放），而我们每放一个数，都会多出一个新的空位（因为我们占了一个空位，而这个数左右两边又分别多出一个空位）；当放所有 $a$ 时，我们相当于在若干个空位中选出几个空位放数（因为 $< \frac{k}{2}$ 的数不能挨着放），而我们每放一个数，都会减少一个空位。然后把每次选数的方案数乘起来就是答案。

式子其实不难，建议自己写。

# 具体式子

设 $a$ 出现的次数为 $cnt_a$，当前空位为 $s$。

假如我们现在要放一个 $\ge \frac{k}{2}$ 的数 $a$，那么答案乘以 $\displaystyle \binom{cnt_a+s-1}{s-1}$，并且 $s \gets s + cnt_a$。

假如我们现在要放一个 $< \frac{k}{2}$ 的数 $a$，那么答案乘以 $\displaystyle \binom{s}{cnt_a}$，并且 $s \gets s - cnt_a$。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 400005, P = 998244353;
int qpow(int a, int b) {
    int ans = 1;
    while (b) {
        if (b & 1) ans = 1ll * ans * a % P;
        a = 1ll * a * a % P;
        b >>= 1;
    }
    return ans;
}
int n, k, a[MAXN];
int fac[MAXN], inv[MAXN];
int C(int n, int m) {
    if (n < m) return 0;
    return 1ll * fac[n] * inv[m] % P * inv[n - m] % P;
}
vector<pair<int, int>> w;
int main() {
    scanf("%d%d", &n, &k);
    fac[0] = 1;
    for (int i = 1; i <= n; i++) 
        fac[i] = 1ll * fac[i - 1] * i % P;
    inv[n] = qpow(fac[n], P - 2);
    for (int i = n; i >= 1; i--)
        inv[i - 1] = 1ll * inv[i] * i % P;
    assert(inv[0] == 1);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    sort(a + 1, a + 1 + n);
    pair<int, int> q = {-1, -1};
    a[0] = -1;
    for (int i = 1; i <= n; i++) { // 处理相同的数字
        if (a[i] != a[i - 1]) {
            if (q.first != -1) {
                w.push_back(q);
            }
            q.first = a[i], q.second = 1;
        } else {
            q.second++;
        }
    }
    w.push_back(q);
    int r = w.size() - 1;
    int mid = -1;
    while (mid + 1 < w.size() && w[mid + 1].first * 2 < k) mid++;
    int space = 1;
    int ans = 1;
    for (int l = 0; l <= mid; l++) { // 从小到大考虑 < k/2 的数
        while (r > mid && w[l].first + w[r].first >= k) { // 加入所有 >= k/2 的数
            ans = 1ll * ans * C(w[r].second + space - 1, space - 1) % P;
            if (!ans) {
                printf("0\n");
                return 0;
            }
            space += w[r].second;
            r--;
        }
        ans = 1ll * ans * C(space, w[l].second) % P;
        if (!ans) {
            printf("0\n");
            return 0;
        }
        space -= w[l].second;
    }
    while (r > mid) { // 把剩下的 >= k/2 的数加进去
        ans = 1ll * ans * C(w[r].second + space - 1, space - 1) % P;
        if (!ans) {
            printf("0\n");
            return 0;
        }
        space += w[r].second;
        r--;
    }
    printf("%d\n", ans);
    return 0;
}
// owo
```

---

## 作者：EuphoricStar (赞：8)

是一道不错的计数。

考察合法序列的形态，容易发现：

1. 不能出现两个 $< \frac{k}{2}$ 的数相邻；
2. 如果 $x < \frac{k}{2}, y \ge \frac{k}{2}$，那么 $|y - \frac{k}{2}| \ge |x - \frac{k}{2}|$。

考虑不直接排列，而是按照一定的顺序插入。考虑按照 $|x - \frac{k}{2}|$ 从大到小插入，并且如果 $|x - \frac{k}{2}|$ 相同，那么就让 $\ge \frac{k}{2}$ 的数先插入，这样能保证不会出现第二种不合法情况。因为题目不区分相同的数，于是把所有相同的数放一起考虑。

于是只用限制第一个不合法情况。维护一个可用位置数 $s$，然后：

- 遇到 $x < \frac{k}{2}$，出现次数为 $y$，那我们有 $\binom{s}{y}$ 种方案插入，并且可用位置数减去 $y$（之后不能在它们两侧放数了）；
- 遇到 $x \ge \frac{k}{2}$，出现次数为 $y$，这个插入的方案数相当于，把这 $y$ 个数划分成 $s$ 段，允许有空段，把这 $s$ 段依次插入。这个用插板法可得方案数为 $\binom{s + y - 1}{s - 1}$，并且可用位置数加上 $y$。

最后由乘法原理把每一步的方案数乘起来就是最终答案。

时间复杂度 $O(n \log n)$，瓶颈在排序。

[code](https://atcoder.jp/contests/arc148/submissions/41838169)

---

## 作者：luobotianle (赞：5)

求合法序列数量，考虑将所有数一个个插入；

由于需要维护可放的位置，所以我们要尽可能的让一个数被插入时，要么之后的数都能放在它的左右两边，要么都不能；

具体地，先对 $a$ 数组排序，随后我们使用两个指针 $l$，$r$，先固定 $l$，不断令 $r \gets r-1$ 并插入 $a_r$ 直到 $a_l+a_r<k$，随后插入 $a_l$ 并令 $l \gets l+1
$，重复此操作直到 $l=r$；

我们发现，当 $a_r$ 被插入序列中时，它的左右两边**一定可以放数**；

- 因为当 $a_r$ 被插入时 $a_l+a_r \ge k$，而接下来的 $a_l$ 会变大，所以之后要插入的数都可以放在 $a_r$ 两侧。

而当 $a_l$ 被插入时，它的左右两边**一定不能放数**；

- 当 $a_l$ 被插入时 $a_l+a_r<k$，而接下来 $a_r$ 会变小，所以之后要插入的数都不能放在 $a_l$ 两侧。

所以，每插入一个 $a_r$，会使可用位置增加 $1$；而每插入一个 $a_l$，会使可用位置减少 $1$，开一个 $tot$ 维护，每插入一个数时把当前的 $tot$ 乘到答案里即可。

注意此时我们将相同元素当成了不同元素计算，所以最后要除以每种数的个数的阶乘以消除影响。

```cpp
#include<bits/stdc++.h>
#define int ll
using namespace std;
typedef long long ll;
const int N=2e5+5;
const int mod=998244353;
int n,k,a[N];
int fac[N],inv[N];
int qp(ll a,int b,int mod=mod){
	ll ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;
		b>>=1;
		a=a*a%mod;
	}
	return ans;
}
map<int,int> cnt;
int ans=1;
int tot=1;
main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>k;
	fac[0]=inv[0]=1;
	for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
	inv[n]=qp(fac[n],mod-2);
	for(int i=n-1;i>=1;i--)inv[i]=inv[i+1]*(i+1)%mod;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		cnt[a[i]]++;
	}
	sort(a+1,a+1+n);
	int l=1,r=n;
	while(l<=r){
		ans=ans*tot%mod;
		if(a[l]+a[r]>=k)r--,tot++;
		else l++,tot--;
	}
	int tot=unique(a+1,a+1+n)-(a+1);
	for(int i=1;i<=tot;i++){
		int tt=cnt[a[i]];
		ans=ans*inv[tt]%mod;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：XKJie (赞：4)

一道计数题。

对于这种对相邻两个元素都有影响的问题，可以考虑将元素按一定顺序一个个加入序列，考虑其对整个方案数的贡献。

1.先将元素从小到大排序。

2.考虑两个维护左右区间的指针 $l,r$，令 $a_r$ 为 $a_l+a_r\geq k$ 的最小编号，其中 $[1,l-1]$ 以及 $[r+1,n]$ 这两段中的元素都已经加入序列。

这样就可以知道一共加入了 $n-r+l-1$ 个元素，有 $n-r+l$ 个空位可供下一个元素放置。

- 放入 $a_r$ 

  此时一共有 $l-1$ 个元素无法满足将 $a_r$ 放入其左边或者右边时无法满足 $ \geq k$的要求（之所以是 $l-1$ 是因为既然 $r$并没有在 $l$ 之前的元素遍历到时就放入，那么自然前面的元素也是不满足条件的）;

  那么此时就有 $(n-r+l)-2 \times (l-1)$ 个空位可选。 

- 放入 $a_l$ 

  $[1,l-1]$ 中的元素和 $a_l$ 也不能满足条件；

  不会有 $a_l+a_{l-1} \geq k$ ,因为如果这样的话 $a_l$就会在遍历到 $l$ 还是 $l-1$ 是就被当作 $a_r$ 放入；

  同理，有 $(n-r+l)-2\times(l-1)$ 个空位可选。  

- 注意，因为有相同元素，因此要在最后除以相同元素的排列数以消除影响。  

```cpp
#include <bits/stdc++.h>
#define N 200010
#define P 998244353
using namespace std;
int n,k,a[N],fac[N],inv[N];
inline int read()
{
    int x=0;char ch=getchar();
    while ((ch<'0') || (ch>'9')) ch=getchar();
    while ((ch>='0') && (ch<='9')) x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
    return x;
}
void mul(int &x,int y)
{x=(1ll*x*y)%P;}
void add(int &x,int y)
{x=(x+y)%P;}
int qpow(int x,int p)
{
    int ans=1;
    while (p)
    {
        if (p&1) mul(ans,x);
        mul(x,x);
        p>>=1;
    }
    return ans;
}
int main()
{
    // read
    n=read();k=read();
    for (int i=1;i<=n;i++) a[i]=read();
    sort(a+1,a+n+1);

    //fac
    fac[0]=1;
    inv[0]=1;
    for (int i=1;i<=n;i++)
    {
        fac[i]=1ll*fac[i-1]*i%P;
        inv[i]=qpow(fac[i],P-2);
    }

    //main
    int l=1,r=n,ans=1;
    while (l<=r)
    {
        while ((r>l) && (a[r]+a[l]>=k))
        {
            mul(ans,n-r-l+2);
            r--;
        }
        mul(ans,n-r-l+2);
        l++;
    }

    //same
    int cnt=1;
    a[n+1]=1000000001;
    for (int i=2;i<=n+1;i++)
    {
        if (a[i]==a[i-1]) cnt++;
        else
        {
            mul(ans,qpow(fac[cnt],P-2));
            cnt=1;
        }
    }
    printf("%d",ans);
    return 0;
}
```

---

## 作者：喵仔牛奶 (赞：2)

## Solution

观察到样例的答案看起来像是很多数相乘的结果，我们猜测可以将数按某种顺序插入，并且存在某种简单的方式维护每次可以插的位置数。

试着让排列插入过程中一直合法。尝试一下从小到大插入，但是插入前，难以计算可以插入的位置，于是在插入 $x$ 前将剩下满足 $x+y\ge k$ 的 $y$ 全部插入。很幸运，这样插入是对的。

设当前可以插入的位置数是 $c$，假定这个对插入 $x,y$ 都有效：
- 若插入了 $y$：插入后，因为之后的 $x'$ 更大，故 $y'\ge x'\ge x\ge k-y$，所以插入的 $y$ 旁边放啥都行。有效位置 $c\gets c+1$，并且仍然对插入 $x',y'$ 都有效。
- 若插入了 $x$：插入后，可以发现之后的 $y'<k-x$，不然插入 $x$ 前已经插入，故 $x'\le y'<k-x$，所以插入的 $x$ 旁边放啥都不行。有效位置 $c\gets c-1$，并且仍然对插入 $x',y'$ 都有效。

非常好，我们归纳得出了这样始终对入 $x,y$ 都有效，把 $c$ 全部乘起来就好了。

不过可以发现有重复的数，我们不应区分它们，记 $b_i$ 是 $i$ 的出现次数，答案要除以 $\prod b_i!$。

## Code

```cpp
#include <bits/stdc++.h>
#define REP(i, l, r) for (int i = (l); i <= (r); ++ i)
#define DEP(i, r, l) for (int i = (r); i >= (l); -- i)
#define fi first
#define se second
#define pb emplace_back
#define mems(x, v) memset((x), (v), sizeof(x))
#define SZ(x) (int)(x).size()
#define ALL(x) (x).begin(), (x).end()
using namespace std;
namespace math { ... }
namespace Milkcat {
	using namespace math;
	typedef long long LL;
	typedef pair<LL, LL> pii;
	const int N = 1e6 + 5, mod = 998244353;
	typedef mint<mod> MI;
	int n, k, a[N]; MI rs, fac[N];
	int main() {
		cin >> n >> k, rs = fac[0] = 1;
		REP(i, 1, n) fac[i] = fac[i - 1] * i;
		REP(i, 1, n) cin >> a[i];
		sort(a + 1, a + 1 + n);
		int r = n, ct = 1;
		REP(i, 1, n) {
			while (i < r && a[i] + a[r] >= k)
				rs *= ct, ct ++, r --;
			if (i > r) break;
			rs *= ct, ct --;
		}
		ct = 0;
		REP(i, 1, n + 1) {
			if (a[i] != a[i - 1]) rs /= fac[ct], ct = 1;
			else ct ++;
		}
		cout << rs << '\n';
		return 0;
	}
}
```

---

## 作者：_abcd_ (赞：0)

[[ARC148E] ≥ K](https://atcoder.jp/contests/arc148/tasks/arc148_e)

对于这种排列计数类问题，首先可以想到按照某种顺序将每个数字插入序列中，但是这道题如果从小到大插入，会有一个问题：如果当前存在两个相邻的数的和 $< k$，但是之后可能这两个数中间插入了一个更大的数，使得序列合法。同样，如果从大到小插入，会发现我们无法很好的记录不能插入的位置，因为如果在插入 $a_i$ 时，存在两个数 $x$ 和 $y$ 满足 $a_i + x < k, a_i + y < k$，存在 $x$ 和 $y$ 相邻以及 $x$ 和 $y$ 不相邻两种情况，第一种情况有 $4$ 个不能放的位置，而第二种情况有 $3$ 个。

那么，不妨考虑从两端插入，即有两个指针 $l$ 和 $r$，一开始有 $l=1, r=n$，如果有 $a_l + a_r \ge k$，那么就插入 $a_r$，否则插入 $a_l$。那么显然插入 $x$ 时，有且仅有 $a_1 \sim a_{l-1}$ 都不合法。这样有两点好处：

$1.$ 不存在原先不合法，之后变得合法的情况，因为如果插入的是 $x$，那么和他相邻的不合法的数属于 $a_1 \sim a_{l-1}$，那么之后的数插入到他们中间都不会使序列变得合法。

$2.$ 由于 $a_1 \sim a_{l-1}$ 之间不存在相邻的情况，那么不能插的位置总有 $2(l-1)$ 个。

因此插入第 $i$ 个数时乘上 $i - 2(l-1)$ 就行了。

---

### Code:
```cpp
#include<bits/stdc++.h>
#define ll long long
#define pn putchar('\n')
#define mclear(a) memset(a,0,sizeof a)
#define fls() fflush(stdout)
#define maxn 200005
#define int ll
#define mod 998244353
using namespace std;
int re()
{
    int x=0,t=1;char ch=getchar();
    while(ch>'9'||ch<'0'){if(ch=='-')t=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return x*t;
}
int n,m,ans=1;
int a[maxn],iv[maxn];
signed main()
{
    #ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
    #endif
    n=re(),m=re();
    for(int i=1;i<=n;i++)
        a[i]=re();
    sort(a+1,a+1+n);
    for(int i=1,l=1,r=n;i<=n;i++)
    {
        ans=ans*(i-2*(l-1))%mod;
        if(a[l]+a[r]>=m)
            r--;
        else
            l++;
    }
    iv[0]=iv[1]=1;
    for(int i=2;i<=n;i++)
        iv[i]=(mod-mod/i)*iv[mod%i]%mod;
    a[0]=a[n+1]=-1;
    for(int i=1,inv=1,cnt=1;i<=n+1;i++)
    {
        if(a[i]!=a[i-1])
        {
            ans=ans*inv%mod;
            inv=cnt=1;
        }
        else
        {
            cnt++;
            inv=inv*iv[cnt]%mod;
        }
    }
    printf("%lld",ans);
    return 0;
}
```

---

