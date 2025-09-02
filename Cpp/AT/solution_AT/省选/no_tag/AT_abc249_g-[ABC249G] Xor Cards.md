# [ABC249G] Xor Cards

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc249/tasks/abc249_g

$ N $ 枚のカードがあり、$ 1,\ \dots,\ N $ の番号が付けられています。カード $ i\ \,\ (1\ \leq\ i\ \leq\ N) $ の表には整数 $ A_i $、裏には整数 $ B_i $ が書かれています。

選んだカードの表に書かれた整数の排他的論理和が $ K $ 以下となるように $ 1 $ 枚以上の好きな枚数のカードを選ぶとき、選んだカードの裏に書かれた整数の排他的論理和としてあり得る最大値を求めてください。

 排他的論理和とは 整数 $ a,\ b $ の排他的論理和 $ a\ \oplus\ b $ は、以下のように定義されます。 - $ a\ \oplus\ b $ を二進表記した際の $ 2^k\ \,\ (k\ \geq\ 0) $ の位の数は、$ a,\ b $ を二進表記した際の $ 2^k $ の位の数のうち一方のみが $ 1 $ であれば $ 1 $、そうでなければ $ 0 $ である。

 例えば、$ 3\ \oplus\ 5\ =\ 6 $ となります（二進表記すると $ 011\ \oplus\ 101\ =\ 110 $）。  
 一般に $ k $ 個の整数 $ p_1,\ \dots,\ p_k $ の排他的論理和は $ (\cdots\ ((p_1\ \oplus\ p_2)\ \oplus\ p_3)\ \oplus\ \cdots\ \oplus\ p_k) $ と定義され、これは $ p_1,\ \dots,\ p_k $ の順番によらないことが証明できます。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 1000 $
- $ 0\ \leq\ K\ \lt\ 2^{30} $
- $ 0\ \leq\ A_i,\ B_i\ \lt\ 2^{30}\ \,\ (1\ \leq\ i\ \leq\ N) $
- 入力は全て整数

### Sample Explanation 1

カード $ 1,\ 2 $ を選ぶことで、表に書かれた整数の排他的論理和は $ 2 $、裏に書かれた整数の排他的論理和は $ 3 $ となり、これが最大です。

### Sample Explanation 2

条件を満たすようにカードを選ぶことはできません。

## 样例 #1

### 输入

```
4 2
1 1
3 2
2 2
0 1```

### 输出

```
3```

## 样例 #2

### 输入

```
1 2
3 4```

### 输出

```
-1```

## 样例 #3

### 输入

```
10 326872757
487274679 568989827
267359104 968688210
669234369 189421955
1044049637 253386228
202278801 233212012
436646715 769734012
478066962 376960084
491389944 1033137442
214977048 1051768288
803550682 1053605300```

### 输出

```
1064164329```

# 题解

## 作者：N_z_ (赞：10)

能不能再给力一点。

考虑那个 $O(n\log V+\log^3V)$ 做法，我们首先来处理后面这个 $O(\log^3V)$，注意到每次都是做一个后缀的线性基，倒着预处理出来查询，即可得到 $O(\log^2V)$。

<https://atcoder.jp/contests/abc249/submissions/57799636>。

接下来的部分只有口胡没有实现，说不定假了。

考虑前面那个 $O(n\log V)$，我们每次 $\log V$ 似乎有一些浪费。考虑 $k$ 位分成一块，处理出对于这些二进制位完成这块之后原数会异或上多少，对于没有插入的情况下，我们以 $O(\frac{\log V}k)$ 的复杂度完成一次，对于插入，发生 $\log V$ 次，每次我们以 $O(2^k)$ 的复杂度完成（我不知道能不能做到更优）。

分析一下这部分复杂度：$O(\frac{n\log V}k+\log V\times2^k)$，平衡点在 $k\times2^k=n$，得到 $O(\frac{n\log V}{\log n})$。

---

## 作者：Reunite (赞：7)

好题，参考了 zlt 的题解。

### 一
---

还是一样地枚举 $lcp$，设 $\oplus a_i$ 在第 $x$ 位第一次小于 $k$，则后面的位可以随意选，设 $k'=(\lfloor \frac{k}{2^x}\rfloor\oplus 1)2^x,a_i'=\lfloor \frac{a_i}{2^x}\rfloor 2^x$，则问题转化为选择若干 $(a'_i,b_i)$，满足 $\bigoplus a_i'=k'$，最大化 $\bigoplus b_i$。

线性基可以实现这几个东西：查询某个值是否可以被异或表示，查询一些值能异或出来的最大值。但这两个不是割裂的，我们可以把朴素 $\log V$ 求最大值的做法劣化为 $\log^2 V$ 的做法，即从高位往低位贪心，设前 $j-1$ 位最大值为 $tmp$，查询 $tmp|2^j$ 能否被表示。

这启示了我们这题的做法，我们可以把 $(a_i',b_i)$ 拼成一个 $60$ 位二进制数（$2^{30}a_i'|b_i$），然后从高位往低位贪心，查询 $2^{30}k'|tmp|2^j$ 能否被表示。非常巧妙的是，这样同时满足了上面条件和目标。

zlt 题解里所说的检查是因为初值肯定是 $0$，但不一定有解，可能有 $-1$ 的情况，所以要判断。

---
### 二

复杂度 $O(n\log^3 V)$，可以做到 $n=5\times 10^4$。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#define int long long
using namespace std;

int n,x;
int a[1005];
int b[1005];

struct Bin{
	int b[65],if0;
	inline void init(){if0=0;memset(b,0,sizeof(b));}
	inline void ins(int x){
		if(x==0){if0=1;return ;}
		for(int i=60;i>=0;i--)
			if((x>>i)&1){
				if(b[i]) x^=b[i];
				else{b[i]=x;return ;}
			}
		return ;
	}
	inline bool find(int x){
		if(!x) return if0;
		for(int i=60;i>=0;i--)
			if((x>>i)&1) x^=b[i];
		return (x==0);
	}
};

signed main(){
	scanf("%lld%lld",&n,&x);
	for(int i=1;i<=n;i++) scanf("%lld%lld",&a[i],&b[i]);
	int ans=-1;
	for(int i=29;i>=-1;i--){
		if(i>=0&&(!((x>>i)&1))) continue;
		int K=(i>=0)?(((x>>i)^1)<<i):x,tmp=0;
		int ii=max(i,0ll);
		for(int j=29;j>=0;j--){
			Bin B;
			B.init();
			for(int k=1;k<=n;k++){
				int X=(((a[k]>>ii)<<ii)<<30)|((b[k]>>j)<<j);
				B.ins(X);
			}
			if(B.find((K<<30)|(tmp|(1<<j)))) tmp|=(1<<j);
		}
		Bin B;
		B.init();
		for(int k=1;k<=n;k++) B.ins((((a[k]>>ii)<<ii)<<30)|b[k]);
		if(B.find((K<<30)|tmp)) ans=max(ans,tmp);
	}
	printf("%lld\n",ans);

	return 0;
}
```

---

## 作者：EuphoricStar (赞：4)

好题。

套路地，考虑枚举最优解的 $a$ 异或和二进制下与 $k$ 的 $\text{LCP}$，设在第 $i$ 位不同。这样的好处是 $i$ 之后的位可以随便选。

之后按位贪心确定最优解 $b$ 的异或和。考虑之前的答案是 $res$，当前在确定第 $j$ 位，如何判断 $res + 2^j$ 可行。

考虑将 $2^i \left\lfloor\frac{a}{2^i}\right\rfloor$ 和 $2^j \left\lfloor\frac{b}{2^j}\right\rfloor$ 拼成一个 $60$ 位的二进制数，把它插入线性基内，判断 $res + 2^j$ 能否被这些数凑出来即可。

注意最后要检查 $res$ 是否能被 $b_i$ 凑出来。

[code](https://atcoder.jp/contests/abc249/submissions/42268312)

---

## 作者：youdu666 (赞：2)

来点不一样的小清新的不魔改线性基的 $O(N\log_2{V}+\log^2{V})$ 做法。

在一开始的时候把每个二元组变成 $x\times2^{30}+y$ 插入到线性基中，考虑倒着枚举异或出来的 $x$ 和 $k$ 前缀有几位相等。不难发现取出来的二元组需要满足高位异或起来是一个固定值，中间部分位置随意，后面部分需要最大。高位相等比较好做，直接把相等的数按位取反，直接用这个值去线性基里搞最大值就行了。对于中间可以随意选择的位，考虑倒着枚举时是逐步增多的，可以向线性基中插入只有对应位置为 $1$ 的值，不难发现这样可以在不影响其他点的情况下让这一位一定能取到。

发现很难分辨无解和答案为 $0$，不妨直接算一下所有 $x$ 异或起来的最小值是否小于 $k$。

---

## 作者：喵仔牛奶 (赞：2)

# Solution

将 $(x_i,y_i)$ 作为 $y_i\times2^{30}+x_i$ 插入线性基，线性基里的 $\mathcal{O}(\log V)$ 个数可以表示出原序列任意的数，只保留这些数答案不变（如果异或出了 $0$ 也要保留）。将这些数还原回 $(x_i,y_i)$，得到了新的序列。

于是我们花费了 $\mathcal{O}(n\log V)$ 的时间，将 $n$ 缩小到了 $\mathcal{O}(\log V)$。

可以发现，$y_i$ 最高位互不相同。将 $(x_i,y_i)$ 按 $y_i$ 从大到小排序，每次贪心判断能否取。具体地，维护当前 $x_i,y_i$ 的异或和 $sm,rs$，处理出 $[i+1,n]$ 的线性基 $B$：
- $sm$ 在 $B$ 中异或最终不可以 $\le k$，那么取；
- 如果 $rs\oplus y_i>rs$ 且 $sm\oplus x_i$ 在 $B$ 中异或最终可以 $\le k$，那么取；
- 否则不取。

注意判无解：强制取一个数 $i$，然后判断它在 $[i+1,n]$ 的线性基 $B$ 中最终是否可以 $\le k$。如果存在这样的 $i$，那么有解。

处理出后缀线性基，复杂度 $\mathcal{O}(n\log V+\log^2V)$。

# Code

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
namespace Milkcat {
	typedef long long LL;
	typedef pair<LL, LL> pii;
	const int N = 1e6 + 5, P = 60;
	struct LBase {
		LL b[P + 3]; Linear() { mems(b, 0); }
		int ins(LL x) { DEP(i, P, 0) if (x >> i & 1) if (b[i]) x ^= b[i]; else return b[i] = x, i; return 0; }
		LL askmx(LL x) { DEP(i, P, 0) x = max(x, x ^ b[i]); return x; }
		LL askmn(LL x) { DEP(i, P, 0) x = min(x, x ^ b[i]); return x; }
	} C, B[P + 5];
	LL n, m, k, x, ck, a[N], b[N];
	vector<pii> s;
	bool chk(int t, LL v) { return (B[t].askmn(v) <= k); }
	int main() {
		cin >> n >> k;
		REP(i, 1, n) {
			cin >> a[i] >> b[i];
			int x = C.ins(b[i] << 30 | a[i]);
			if (!x && !SZ(s)) s.pb(0, 0);
		}
		REP(i, 0, P) {
			LL x = C.b[i];
			if (x > 0) s.pb(x >> 30, x & ((1 << 30) - 1));
		}
		sort(ALL(s), greater<pii>()), m = SZ(s) - 1;
		DEP(i, m, 0) B[i] = B[i + 1], B[i].ins(s[i].se);
		REP(i, 0, m) ck |= chk(i + 1, s[i].se);
		if (!ck) { cout << "-1\n"; return 0; }
		LL rs = 0, sm = 0;
		REP(i, 0, m) {
			auto [x, y] = s[i];
			int c1 = chk(i + 1, sm ^ y), c2 = chk(i + 1, sm);
			if ((c1 && (rs ^ x) > rs) || !c2) rs ^= x, sm ^= y;
		}
		cout << rs << '\n';
		return 0;
	}
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	int T = 1;
	while (T --) Milkcat::main();
	return 0;
}
```

---

## 作者：JWRuixi (赞：2)

## [ABC249G] Xor Cards

### 题意

给定 $n$ 个二元组 $(x_i, y_i)$，对于所有集合 $S$，满足 $\bigoplus\limits_{i \in S} x_i \le k$，求 $\max(\bigoplus\limits_{i \in S} y_i)$。

$n \le 1000, x_i, y_i, k < 2^{30}$。

bonus：$n \le 10^6$。

### 分析

由于涉及到一个集合异或和的最大值，不得不考虑线性基，有几种方向：对 $y$ 做；对 $x$ 做；对 $(x, y)$ 这个整体做。我们考虑第二种思路。

考虑找到线性基后，不在基中的元素的 $x$ 一定可以被消为 $0$，也就是说它们的选取不存在限制，我们只需要将他们插入到一个线性基中，然后枚举一个基的子集满足异或和不超过 $k$，从高位到低位贪心即可。

由于插入式线性基性质不太优秀，我们不妨换用**高斯消元**求解线性基。这样能满足一个性质：一定能找到一组基，满足对于任意元素 $v_i$，考虑其最高位 $j$，那么 $\forall k \neq i, j \not \in v_k$。

这样就能有一个推论：对于任意一个集合 $S$，若 $x \not \in S$，则 $\bigoplus\limits_{i \in S} x_i < \bigoplus\limits_{i \in S \cup \{x\}} x_i$。

基于这个推论，我们可以应用到条件上：记线性基为 $B$，若存在集合 $S \subseteq B$，满足 $\bigoplus\limits_{i \in S} x_i \le k$，则 $\forall T \subseteq S, \bigoplus\limits_{i \in T} x_i \le k$，证明考虑 $S$ 一定是异或和最大的组合。

于是我们知道所有的 $(S, \bigoplus\limits_{i \in S} x_i)$ 满足一定的**偏序关系**，相对于找多所有异或和不超过 $k$ 的集合，我们可以找到极大的那些集合，在用线性基来描述它的子集，这样可以大大较少枚举量。

而有多少不同的极大集合呢？我们发现实质上可以认为是枚举了一个和 $k$ 的 LCP，所以极大集合的数量就是 $\mathcal O(\log V)$ 的了，具体实现可以考虑钦定一个点不出现，然后对与剩下的部分贪心选取（在异或和不超过 $k$ 的前提下能选就选）。

这样总复杂度就是 $\mathcal O(n \log V + \log^3 V)$ 的了。

### Code

提交记录：<https://atcoder.jp/contests/abc249/submissions/56897049>。

---

## 作者：tobie (赞：2)

提供一个复杂度更优秀的做法，可以加强到 $n\le 5\times 10^5$。

考虑将 $y_i\times 2^{31}+x_i$ 塞到一个线性基里，所以事实上不管 $n$ 有多大，我们只在乎线性基中的 $O(\log V)$ 个元素。

现在把这 $O(\log V)$ 个元素还原为二元组，那么我们发现，根据异或线性基的特点，所有 $y_i$ 的最高位是互不相同的。

这样我们就可以考虑使用贪心：从高到低考虑二元组，如果加入这个二元组能让答案更大就直接加入。

那么如何判断一个数 $y_i$ 能否被插入呢？因为后面的数已经不会影响这个最高位，所以只要将 $i$ 后面的所有 $x_j$ 插入线性基，看看能不能把当前的异或和 $t$ 消到比 $k$ 小即可。

时间复杂度 $O(n^2 \log V)$，但是因为 $n$ 最终是 $O(\log V)$ 级别的，所以总复杂度是 $O(n\log V+\log^3 V)$。

[submission](https://atcoder.jp/contests/abc249/submissions/56896541)

---

## 作者：ppllxx_9G (赞：2)

## 二元组线性基

基本操作即：对于二元组 $(x,y)$，将 $(x<<31)|y$ 插入线性基中。

这样得到的线性基可以表出原二元数组异或得到的所有组合。

## [ABC249G](https://www.luogu.com.cn/problem/AT_abc249_g)

基本问题。二元数组 $(x_i,y_i)$，选出集合 $\mathbb{T}$，令 $\bigoplus_{i \in \mathbb{T}} x_i \le k$ 的前提下 $\bigoplus_{i \in \mathbb{T}} y_i$ 最大。

转化问题，对于异或和小于等于一个数，想到从高到低枚举二进制下公共前缀，钦定第一位小于后，后面的数就可以任选了。

我们枚举这个前缀，令 $i$ 为第一个不同的位置，前 $i$ 位确定的值为 $x$，问题变成在 $x$ 能被 $x_i$ 的前 $i$ 位通过异或表出的前提下，$\bigoplus_{i \in \mathbb{T}} y_i$ 最大。

一个数是否能被表出显然可做，并且只和前 $i$ 位有关，然后将前 $i$ 位消掉后的值在 [1,30] 位上找最大异或和，即为所求。

具体实现时枚举 $i$，每次将 $x$ 前 $i$ 或 $y$ 插进线性基，复杂度 $O(n\log^2 V)$。

能不能再给力一点？

发现每次暴力插很劣，考虑维护的二元组线性基本身就已经可以表示出 $(x,y)$ 的所有信息，不如直接将 $(x<<31)|y$ 得到的线性基代替 $(x_i,y_i)$。

复杂度 $O(n\log V+ \log^3V)$。

[AC record](https://www.luogu.com.cn/record/196126608)

---

## 作者：123456xwd (赞：0)

我们考虑枚举一下二进制下 $\oplus a_i,k$ 中第一位不同的地方 $i$（$k$ 中这一位为 1），这样子我们相当于只用考虑 $i$ 前面的位数异或起来相等的情况，后面不管（注意等于的情况）

我们令： $k\to (\frac{k}{2^i}+1)2^i,a_j\to \frac{a_j}{2^i}$，相当于我们要取得若干个 $a_j$，使得他们异或起来和 $k$ 等。

并且我们想要最大化 $\oplus b_i$。

这两步单独放入线性基，其实都是好处理的，但烦就烦在他们被拼凑在了一起。

考虑一下，我们把 $a_i,b_i$ 拼接为一个二进制数，一个为前 $30$ 位，一个为后 $30$ 位，我们还是先在线性基中正常处理，使得其前 $30$ 位异或起来为 $k$，然后我们贪心的满足后 $30$ 位最大即可。

这样子时间为 $\mathcal{O}(NV^2)$，其中 $V=30$，但还有一个 $2$ 的常数，这样子可以过到 $n=10^5$ 级别的。

至于判断无解，我们有两种情况，在最开始的时候我们把初始的 $a_i$ 加入线性基，若每次的返回值都 $>k$，那么必定无解，直接不管后面了。

至于后面再枚举第一位不同的时候，若最后 $a$ 部分不能把 $k$ 消完，那么也是无解。

```c++
#include<bits/stdc++.h>
#define ull unsigned long long
#define ll long long
#define p_b push_back
#define m_p make_pair
#define pii pair<int,int>
#define fi first
#define se second
#define ls k<<1
#define rs k<<1|1
#define mid ((l+r)>>1)
#define gcd __gcd
#define lowbit(x) (x&(-x))
using namespace std;
int rd(){
    int x=0,f=1; char ch=getchar();
    for(;ch<'0'||ch>'9';ch=getchar())if (ch=='-') f=-1;
    for(;ch>='0'&&ch<='9';ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
    return x*f;
}
void write(int x){
    if(x>9) write(x/10);
    putchar('0'+x%10);
}
const int N=1e5+5,V=30,INF=0x3f3f3f3f;

int n,k,a[N],b[N],ans=-1;
ll K,c[N];

struct node{
    ll d[61];
    void clear(){
        for(int i=60;i>=0;i--) d[i]=0;
    }
    int insert(ll x){
        for(int i=60;i>=0;i--){
            if((x>>i)&1){
                if(d[i]) x^=d[i];
                else{
                    d[i]=x;
                    return x;
                }
            }
        }
        return x;
    }
    int query(ll x){
        for(int i=60;i>=30;i--){
            if(((x>>i)&1)){
                if(!d[i]) return -1;
                x^=d[i];
            }
        }
        for(int i=29;i>=0;i--){
            if(d[i]&&!((x>>i)&1)) x^=d[i];
        }
        if(x>=(1ll<<30))return -1; 
        return (int)x;
    }
}A;

int main(){
    n=rd(),k=rd();
    for(int i=1;i<=n;i++) a[i]=rd(),b[i]=rd();
    bool flag=0;
    for(int i=1;i<=n;i++) if(A.insert(a[i])<=k) flag=1;
    if(!flag){puts("-1");return 0;}
    for(int i=29;i>=-1;i--){
        if(i!=-1&&!((k>>i)&1))continue;
        K=k;
        if(i!=-1)K=((K>>i)^1)<<i;
        K<<=30ll;
        for(int j=1;j<=n;j++){
            if(i!=-1)c[j]=(a[j]>>i)<<i;
            else c[j]=a[j];
            c[j]=(c[j]<<30ll)^b[j];
        } 
        A.clear();
        for(int j=1;j<=n;j++) A.insert(c[j]);
        ans=max(ans,A.query(K));
    }
    printf("%d\n",ans);
    return 0;
}
```

---

