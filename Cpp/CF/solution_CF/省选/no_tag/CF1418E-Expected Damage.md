# Expected Damage

## 题目描述

You are playing a computer game. In this game, you have to fight $ n $ monsters.

To defend from monsters, you need a shield. Each shield has two parameters: its current durability $ a $ and its defence rating $ b $ . Each monster has only one parameter: its strength $ d $ .

When you fight a monster with strength $ d $ while having a shield with current durability $ a $ and defence $ b $ , there are three possible outcomes:

- if $ a = 0 $ , then you receive $ d $ damage;
- if $ a > 0 $ and $ d \ge b $ , you receive no damage, but the current durability of the shield decreases by $ 1 $ ;
- if $ a > 0 $ and $ d < b $ , nothing happens.

The $ i $ -th monster has strength $ d_i $ , and you will fight each of the monsters exactly once, in some random order (all $ n! $ orders are equiprobable). You have to consider $ m $ different shields, the $ i $ -th shield has initial durability $ a_i $ and defence rating $ b_i $ . For each shield, calculate the expected amount of damage you will receive if you take this shield and fight the given $ n $ monsters in random order.

## 样例 #1

### 输入

```
3 2
1 3 1
2 1
1 2```

### 输出

```
665496237
1```

## 样例 #2

### 输入

```
3 3
4 2 6
3 1
1 2
2 3```

### 输出

```
0
8
665496236```

# 题解

## 作者：youngk (赞：10)

对于每一个询问的$a$和$b$，我们可以先将序列$d[1...n]$进行排序，对于每个询问，通过二分找到有多少个数$\geq b$，不妨记为$cnt$。

首先考虑对于所有的$\geq b$的数，这部分中每个数被选中会受到伤害的概率为$\frac{cnt-a}{cnt}$。而对于$<b$的数，我们可以对于$cnt$个数包括最前和最后一共有$cnt+1$个空隙，而每个$<b$的数插入每个空隙的概率为$\frac{1}{cnt+1}$，其中前$a$个空隙是不受到伤害的，因此对于每个$<b$的数受到攻击的概率为$\frac{cnt+1-a}{cnt+1}$

提前做前缀和即可对于每个询问能够$O(logn)$回答

upd:在9月15号的重测中原代码被hack，因为输入的数值会高过模数，因此不能输入前缀和处理的时候值判断是否大于模数再减去模数

代码：

```cpp
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#define endl '\n'
#define ck(x) (x >= mod ? x - mod : x)
#define maxn 200010
const int mod = 998244353;

int qpow(int a, int b) {
    int ret = 1;
    while (b) {
        if (b & 1) {
            ret = 1LL * a * ret % mod;
        }
        a = 1LL * a * a % mod;
        b >>= 1;
    }
    return ret;
}

int n, d[maxn], sum[maxn], q, a, b;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> d[i];
    }
    sort(d + 1, d + n + 1);
    for (int i = 1; i <= n; i++) {
        sum[i] = (sum[i - 1] + d[i]) % mod;
        //sum[i] = ck(sum[i - 1] + d[i]);
    }
    while (q--) {
        cin >> a >> b;
        int p = lower_bound(d + 1, d + n + 1, b) - d - 1;
        int cnt = n - p;
        if (cnt < a) {
            cout << 0 << endl;
        } else {
            int ans = 1LL * (sum[n] - sum[p] + mod) % mod * (cnt - a) % mod * qpow(cnt, mod - 2) % mod;
            ans = ck(ans + 1LL * sum[p] * (cnt - a + 1) % mod * qpow(cnt + 1, mod - 2) % mod);
            cout << ans << endl;
        }
    }
    return 0;
}
```


---

## 作者：_lyx111 (赞：1)

# CF1418E Expected Damage

[link](https://codeforces.com/problemset/problem/1418/E)

## 分析

将题目中对于是否受伤害的的条件翻译一下：设第 $a$ 个满足 $b\le d$ 的怪物的编号为 $id$，则总伤害 $=\sum_{i=id+1}^nd_i$。

发现我们需要寻找满足 $b\le d$ 的怪物，可以考虑将 $d$ 从小到大排序，通过二分找到最后一个使得 $d<b$ 的怪兽的位置 $cnt$，即

- $i\le cnt$ 时，有 $d_i<b$

- $i>cnt$ 时，有 $b\le d_i$

则满足 $b\le d$ 的怪物的个数为 $n-cnt$。

1. 对于 $b\le d_i$ 的怪物伤害被记录的概率为 $\frac{n-cnt-a}{n-cnt}$，也就是在 $n-cnt$ 个中不在前 $a$ 个（ 在后 $n-cnt-a$ 个 ）的概率。

2. 对于 $b>d_i$ 的怪物伤害被记录的概率为 $\frac{n-cnt+1-a}{n-cnt+1}$。原因如下：那 $n-cnt$ 个怪兽共构成 $n-cnt+1$ 个空隙，每个 $b>d_i$ 个怪兽可以任意插入一个空隙，在前 $a$ 个空隙内伤害不会被记录，在后 $n-cnt+1-a$ 个空隙内伤害会被记录，所以满足 $b>d_i$ 的怪物伤害被记录的概率为 $\frac{n-cnt+1-a}{n-cnt+1}$。

设：$sum_1=\sum_{b\le d_i} d_i,\ sum_2=\sum_{b>d_i} d_i,\ k_1=\frac{n-cnt-a}{n-cnt},\ k_2=\frac{n-cnt+1-a}{n-cnt+1}$，那么答案就是 $sum_1\times k_1+sum_2\times k_2$，使用前缀和优化计算 $sum_1,sum_2$ 时间复杂度就可以降到 $O(m\log n)$。

其实这道题如果将 $d$ 从大到小排序写起来会更方便一些，但我懒得改了。

## 代码

~~~cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=2e5+10,mod=998244353;
int n,m;
int d[MAXN],pre[MAXN]; //pre 是 d 的前缀和 
int ksm(int u,int v) //快速计算 u^v 
{
	int res=1;
	while(v)
	{
		if(v&1) res=1ll*res*u%mod;
		u=1ll*u*u%mod; v>>=1;
	}
	return res;
}
int find(int b) //二分寻找最后一个使得 d<b 的怪兽的位置 cnt 
{
	int l=0,r=n;
	while(l+1<r)
	{
		int mid=(l+r)>>1;
		if(d[mid]<b) l=mid;
		else r=mid-1;
	}
	if(d[r]<b) return r;
	else return l;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&d[i]);
	sort(d+1,d+n+1); //将 d 从小到大排序 
	for(int i=1;i<=n;i++) pre[i]=(pre[i-1]+d[i])%mod; //前缀和 
	while(m--)
	{
		int a,b; scanf("%d%d",&a,&b);
		int cnt=find(b);
		if(n-cnt<a) { printf("0\n"); continue;}
		int sum1=(pre[n]-pre[cnt]+mod)%mod,k1=1ll*(n-cnt-a)*ksm(n-cnt,mod-2)%mod;
		int sum2=pre[cnt],k2=1ll*(n-cnt+1-a)*ksm(n-cnt+1,mod-2)%mod;
		//ksm(u,mod-2) 是在模 mod 的意义下 u 的逆元 
		int ans=(1ll*k1*sum1%mod+1ll*k2*sum2%mod)%mod;
		printf("%d\n",ans);
	}
	return 0;
}
~~~

[AC记录](https://codeforces.com/problemset/submission/1418/175101257)

## 写在最后

笔者水平有限，如果写的有不清楚或不对的地方望读者私信我指出，我会及时修正。

---

## 作者：ifffer_2137 (赞：0)

组合数做法。
### 题意
~~有点长就不贴了，自己看一下吧~~。
### 分析
有两种数，分类考虑每个数的贡献。

我们可以先放好攻击力大于防御力的怪物，再插入其他的，这样方便计算。假设我们求出这样攻击力较大的大怪物有 $x$ 个，至于怎么求，排序以后二分即可。

对于一个 $d_i\geq b$ 的怪物，他想要产生贡献，就需要在剩下的 $x-1$ 个当中选出 $a$ 个大怪物放在前面，其他的放在后面，然后把小怪物插到里面排一下。把 $n-x$ 个小怪物插到 $x+1$ 个空里，用可以为空的插板法，得到方案数 $\dbinom{n}{x}$。可以算出贡献：
$$d_i\dbinom{x-1}{a}\dbinom{n}{x}a!(x-a)!(n-x)!$$

然后是 $d_i<b$ 的怪物，也一样，先排好大怪物，在后面 $x-a$ 个当中选一个位置插进，然后剩下的 $n-x-1$ 个随意插进 $x+2$ 个空里，排一下，贡献就是：
$$d_i(x-a+1)\dbinom{n}{x+1}(n-x-1)!x!$$
全部贡献加起来最后除以 $n!$ 就是受伤值期望了。

因为已经排好序了，算的时候前缀和优化即可，线性预处理阶乘和逆元求组合数。这样最后时间复杂度 $\mathcal O(n\log_2n)$，瓶颈在排序和二分。
### 代码
```cpp
//From: ifffer_2137
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define inf 0x7fffffff
#define eb emplace_back
#define pii pair<int,int>
#define mkpr make_pair
#define fir first
#define sec second
inline int read(){
    char ch=getchar();int x=0,w=1;
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+ch-48,ch=getchar();return w==1?x:-x;
}
const int maxn=2e5+5;
const int mod=998244353;
int n,m;
int d[maxn],s[maxn];
struct node{int a,b;}p[maxn];
bool cmp(int x,int y){return x>y;}
int fac[maxn],inv[maxn];
int pw(int a,int x){
	int s=1;
	while(x){
		if(x&1) s=s*a%mod;
		a=a*a%mod;
		x>>=1;
	}
	return s%mod;
}
void init(){
	fac[0]=1;
	for(int i=1;i<maxn;i++){
		fac[i]=fac[i-1]*i%mod;
	}
	inv[maxn-1]=pw(fac[maxn-1],mod-2);
	for(int i=maxn-2;i>=0;i--){
		inv[i]=inv[i+1]*(i+1)%mod;
	}
}
int C(int n,int m){
	if(n<m) return 0;
	if(n<0||m<0) return 0;
	return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
signed main(){
	cin.tie(0),cout.tie(0);
	n=read(),m=read();
	for(int i=1;i<=n;i++) d[i]=read();
	for(int i=1;i<=m;i++) p[i].a=read(),p[i].b=read();
	sort(d+1,d+n+1,cmp);
	for(int i=1;i<=n;i++) s[i]=(s[i-1]+d[i])%mod;
	init();
	for(int i=1;i<=m;i++){
		int l=0,r=n,x=0;
		while(l<=r){
			int mid=(l+r)/2;
			if(d[mid]>=p[i].b){
				x=mid;
				l=mid+1;
			}else{
				r=mid-1;
			}
		}
		if(x<p[i].a){
			cout<<0<<endl;
			continue;
		}
		int ans=0;
		if(x==n){
			ans=s[x]*C(x-1,x-p[i].a-1)%mod*fac[p[i].a]%mod*fac[x-p[i].a]%mod*C(n,x)%mod*fac[n-x]%mod;
			ans=ans*inv[n]%mod;
			cout<<ans<<endl;
			continue;
		}
		ans=(s[x]*C(x-1,p[i].a)%mod*fac[p[i].a]%mod*fac[x-p[i].a]%mod*C(n,x)%mod*fac[n-x]%mod+(s[n]-s[x]+mod)%mod*C(n,x+1)%mod*fac[n-x-1]%mod*fac[x]%mod*(x-p[i].a+1)%mod)%mod;
		ans=ans*inv[n]%mod;
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：tribool4_in (赞：0)

考虑单次询问。由于盾牌的防御等级固定，考虑将怪物分成大怪（$d\ge b$ 即可以减少盾的耐久）和小怪（$d<b$），盾会在第 $a$ 个大怪攻击之后爆掉。

考虑从概率角度分析，求每个怪造成攻击的概率。设大怪有 $A$ 个，小怪有 $B$ 个。大怪造成伤害当且仅当其在大怪中的排名大于 $a$，因此概率为 $p_a=1-\dfrac{a}{A}$；小怪造成伤害当且仅当其在第 $a$ 名大怪之后，由于其在每个大怪空隙之间的概率均等，因此概率为 $p_b=1-\dfrac{a}{A+1}$。答案就是 $\sum{p_id_i}$。

多次询问的话，将式子中跟 $a,b$ 有关的提出来，只需要求各自 $d$ 的和即可。由于大小怪是由 $b$ 区分的，将询问离线下来关于 $b$ 排序，分别动态维护大小怪的 $d$ 之和，对于每组询问容易算出答案。当然也可以对于 $d$ 排序后做个前缀和，是类似的。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10, mod = 998244353;
int n, m, s, d[N], ans[N];
struct qry {
    int a, b, id;
} qr[N];
int qpow(int a, int b = mod - 2) {
    int res = 1;
    for (; b; a = 1ll * a * a % mod, b >>= 1)
        if (b & 1) res = 1ll * res * a % mod;
    return res;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> d[i], (s += d[i]) %= mod;
    for (int i = 1; i <= m; i++) {
        cin >> qr[i].a >> qr[i].b;
        qr[i].id = i;
    }
    sort(d + 1, d + n + 1);
    sort(qr + 1, qr + m + 1, [](const qry &x, const qry &y) { return x.b < y.b; });
    for (int i = 1, j = 1, bs = s, ss = 0, cnt = n; i <= m; i++) {
        while (j <= n && d[j] < qr[i].b) {
            (bs += mod - d[j]) %= mod, (ss += d[j]) %= mod, --cnt;
            ++j;
        }
        if (qr[i].a >= min(n, cnt + 1)) ans[qr[i].id] = 0;
        else ans[qr[i].id] = (s - 1ll * qr[i].a * bs % mod * qpow(cnt) % mod + mod - 1ll * qr[i].a * ss % mod * qpow(cnt + 1) % mod + mod) % mod;
    }
    for (int i = 1; i <= m; i++) cout << ans[i] << '\n';
    return 0;
}
```

---

## 作者：luogubot (赞：0)

题意略。

考虑对于一组 $a,b$ 怎么算答案，显然要去对于一个怪物 $d$ 求出它能在多少个排列中造成伤害，最后再除以 $n!$ 转为期望。假设目前有 $c$ 个怪物的力量不小于 $b$，我们称之为大怪物，那么：

- 如果它不是大怪物，需要在这个怪物前面放至少 $a$ 个大怪物，把 $c$ 个大怪物和它拉出来考虑，那就有 $\binom{n}{c+1}\frac{c+1-a}{c+1}(c+1)!(n-c-1)!$，先选出 $c+1$ 个位置，内部外部任意排列，特殊地，内部存在额外的限制：有一个特殊元素不能排在前 $a$ 个位置，乘上 $\frac{c+1-a}{c+1}$ 即可。
- 如果它是大怪物，需要在这个怪物前面另外放至少 $a$ 个大怪物，类似地，系数为 $\binom{n}{c}\frac{c-a}{c}c!(n-c)!$。

不难发现这两类系数是可以预处理后 $O(1)$ 计算的，我们只需要知道不小于 $b$ 的怪物的个数/力量之和，可以排序二分+前缀和或者是把询问离线双指针，时间复杂度 $O(n\log n)$。

---

## 作者：流水行船CCD (赞：0)

对于一次询问 $A,B$，我们将原怪物序列分成两种：一种会扣盾牌耐久，另一种不会扣盾牌耐久。

通过二分，可以快速求出第一类怪物的个数 $x$，那么第二类怪物的个数为 $n-x$。

枚举方案求贡献太慢了，正难则反，求考虑枚举贡献求方案，问题转化为询问每一个怪物对你造成伤害的概率 $p_i$。不难发现对于同一类的怪物，每一个怪物会对你造成伤害的概率是相等的，考虑捆绑在一起计算。

现在问题转化为有 $x$ 个关键点，$n - x$ 个非关键点，随机排列，在给定的一个非关键点前面有至少 $y$ 个关键点的概率 $g(x,y)$。那么第一类怪物对你造成伤害的概率是 $g(x-1,a_i)$，第二类怪物对你造成伤害的概率是 $g(x,a_i)$，其中 $a_i$ 是当前询问盾牌的耐久。

考虑求解 $g(x,y)$，将给定的那个非关键点视作关键点，就是视作有 $x+1$ 个关键点。那么在给定非关键点之前有 $y$ 个关键点的概率也就是给定非关键点在该长度为 $x+1$ 的关键点序列中第 $y$ 个元素后的概率 $\frac{x+1-y}{x+1}$。

至此，在 $\mathcal{O}(n \log n)$ 时间复杂度中解决了该问题。

[link](https://codeforces.com/problemset/submission/1418/319450596)。

---

