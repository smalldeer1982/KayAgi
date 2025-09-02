# LCM Sum (hard version)

## 题目描述

我们之和，因我们众多。

一些数字

本题与前一版本的区别仅在于 $ t $ 的约束条件。只有当两个版本的问题都被解决时，才能进行 hack。

给定两个正整数 $ l $ 和 $ r $。

请计算有多少个不同的整数三元组 $ (i, j, k) $ 满足 $ l \le i < j < k \le r $ 且 $ \operatorname{lcm}(i,j,k) \ge i + j + k $。

这里 $ \operatorname{lcm}(i, j, k) $ 表示整数 $ i $、$ j $、$ k $ 的最小公倍数。

## 说明/提示

在第一个测试用例中，有 $ 3 $ 个满足条件的三元组：

- $ (1,2,3) $，
- $ (1,3,4) $，
- $ (2,3,4) $。

在第二个测试用例中，有 $ 1 $ 个满足条件的三元组：

- $ (3,4,5) $。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5
1 4
3 5
8 86
68 86
6 86868```

### 输出

```
3
1
78975
969
109229059713337```

# 题解

## 作者：xuanxuan001 (赞：15)

做法不太一样，发篇题解。

赛时居然切了 E1 没切 E2，可能大半夜脑子有点昏。

考虑计算出 $\operatorname{lcm}(i,j,k) < i + j + k$ 的三元组数量，然后答案就是 $C_{r-l+1}^3$ 减去这个数。

设 $x = \operatorname{lcm}(i,j,k),i = \dfrac{x}{a},j = \dfrac{x}{b},k = \dfrac{x}{c}$，那么有 $a > b > c$，而上面那个 $\operatorname{lcm}$ 的条件就相当于$\dfrac{1}{a} + \dfrac{1}{b} + \dfrac{1}{c} > 1$。

要满足这个条件，可以分为 $c=1$ 和 $c \ne 1$ 两类。先讨论 $c \ne 1$ 这一类。

如果 $c \ge 3$，那么 $\dfrac{1}{a} < \dfrac{1}{b} < \dfrac{1}{c} \le \dfrac{1}{3}$，所以有 $\dfrac{1}{a} + \dfrac{1}{b} + \dfrac{1}{c} < \dfrac{1}{3} + \dfrac{1}{3} + \dfrac{1}{3} = 1$，不符合条件，所以 $c=2$。

如果 $b \ge 4$，那么 $\dfrac{1}{a} < \dfrac{1}{b} \le \dfrac{1}{4}$，所以有 $\dfrac{1}{a} + \dfrac{1}{b} + \dfrac{1}{c} < \dfrac{1}{4} + \dfrac{1}{4} + \dfrac{1}{2} = 1$，不符合条件，所以 $b=3$。

最后经尝试(?)，$a \le 5$。

所以刚才经过一大波初(xiao)中(xue)数(ao)学(shu)式的推导后，得出满足条件的 $a,b,c$ 只有两组：(4,3,2) 和 (5,3,2)。对应到 $i,j,k$ 的比例就是 3:4:6 和 6:10:15。

得出了这个比例后我们就可以很容易的求出有多少组满足的了。以第一个比例 3:4:6 为例，设 $i = 3 \lambda,j = 4\lambda,k = 6\lambda$。那么为了让 $i,j,k$ 满足大小的限制，$\lambda$ 的取值必须在 $[\lceil \dfrac{l}{3} \rceil,\lfloor \dfrac{r}{6} \rfloor]$ 之间，而每一种取值都对应一组 $i,j,k$，所以直接 $\max(0,\lfloor \dfrac{r}{6} \rfloor - \lceil \dfrac{l}{3} \rceil + 1)$ 即可。

同理，第二个比例算出来的公式是 $\max(0,\lfloor \dfrac{r}{15} \rfloor - \lceil \dfrac{l}{6} \rceil + 1)$。

重点是 $c=1$ 这一类。这一类就相当于是 $i,j$ 都是 $k$ 的约数，那么设 $cnt_i$ 表示在 $[l,r]$ 中 $i$ 的约数的数量（不包括 $i$），这一部分的答案就是 $\sum\limits_{i=l}^rC_{cnt_i}^2$。

可以反过来考虑，对于每个 $i \in [l,r]$ ，将所有除 $i$ 外的 $i$ 的倍数的 $cnt$ 值都加 1。

对于 E1，可以直接处理 $cnt$，然后就可以在 $O(\sum r-l+1)$ 的时间解决。

对于 E2，我赛时完全没有想法，考虑了一下主席树，然后空间过大，弃了。

第二天白天准备补一下，在我就要点开 CF 官方题解的那一刻，我突然有了思路：这个直接离线不就行了！

然后推了一小会，通了。

还是前面那个做法，但是正着枚举 $i$ 显得很棘手，所以考虑从 $\max r$ 开始倒着枚举 $i$，同时更新对应位置的 $cnt$ 值和 $C_{cnt}^2$ 值。

发现一个 $i$ 只会更新下标大于它的位置。所以对于一次询问 $[l,r]$，只需要在 $l$ 更新完后查询区间 $[l,r]$ 的 $C_{cnt_i}^2$ 和即可，因为大于 $r$ 的 $i$ 的更新不会影响这个区间的值。

单点加区间求和是一个裸的树状数组，维护即可。

发现会更新 $O(n \log n)$ 次，因为这是个调和级数。

最终复杂度 $O(n \log^2 n)$。

代码：

```
#include<cstdio>
#include<vector>
#define TY ll
#define MAXN 200002
#define MAXM 100002
#define debug if(1==1)
#define FOR(i,a,b) for(TY i=(a);i<=(b);++i)
#define fOR(i,a,b) for(TY i=(a);i<(b);++i)
#define ROF(i,a,b) for(TY i=(a);i>=(b);--i)
#define rOF(i,a,b) for(TY i=(a);i>(b);--i)
using namespace std;
typedef double db;
typedef long long ll;
const TY M=998244353;
typedef unsigned long long ull;
TY _abs(TY a){return a<0?-a:a;}
TY maxn(TY a,TY b){return a>b?a:b;}
TY minn(TY a,TY b){return a<b?a:b;}
TY gcd(TY a,TY b){return b?gcd(b,a%b):a;}
TY qp(TY a,TY b){TY ans=1;do{if(b&1)ans=ans*a%M;a=a*a%M;}while(b>>=1);return ans;}
char getc(){char ch=getchar();while(ch==' '||ch=='\n')ch=getchar();return ch;}
void prtcan(bool x,bool big){
	if(x){
		if(big)printf("YES\n");
		else printf("Yes\n");
	}else{
		if(big)printf("NO\n");
		else printf("No\n");
	}
}TY qr(){
	char ch=getchar();TY s=0,x=1;
	for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')x=-1;
	for(;ch>='0'&&ch<='9';ch=getchar())s=s*10+ch-'0';return x*s;
}void qw(TY a,char ch){
	if(a<0){a=-a;putchar('-');}
	if(a>9)qw(a/10,0);putchar(a%10+'0');
	if(ch)putchar(ch);
}TY T=qr(),l,r,cnt[MAXN],tre[MAXN],ans[MAXM];vector<TY>id[MAXN],v[MAXN];
TY js(TY a){return a*(a-1)*(a-2)/6;}
TY len(TY l,TY r){return l<=r?r-l+1:0;}
inline void add(TY x,TY d){for(;x<MAXN;x+=x&-x)tre[x]+=d;}
TY ask(TY x){TY s=0;for(;x;x^=x&-x)s+=tre[x];return s;}
int main(){
	FOR(i,1,T){
		l=qr();r=qr();ans[i]=js(r-l+1);
		ans[i]-=len((l+2)/3,r/6);
		ans[i]-=len((l+5)/6,r/15);//c不等于1的情况
		id[l].push_back(i);v[l].push_back(r);
	}ROF(i,MAXN-1,1){
		for(TY j=i<<1;j<MAXN;j+=i)add(j,cnt[j]++);//tre维护C(cnt,2)的树状数组
		fOR(j,0,id[i].size())ans[id[i][j]]-=ask(v[i][j])-ask(i-1);//c=1的情况考虑
	}FOR(i,1,T)qw(ans[i],'\n');
	return 0;
}
```

---

## 作者：巨型蚊子精 (赞：9)

# CF1712E2 LCM Sum(hard version)

## 题意：
给定正整数 $l,r$，求满足 $\operatorname{lcm}(i,j,k) \ge i+j+k$ 且 $l \le i < j < k \le r$ 的三元组 $(i,j,k)$ 的数量。

## 思路：

由于满足该条件的三元组数量很多，难以直接统计，符合我们考虑不满足条件的“坏”三元组，即计数满足 $\operatorname{lcm} (i,j,k) < i + j + k$ 的三元组。那么最终的答案就是 $\dbinom {3}{r - l + 1} = \dfrac{(r - l + 1)(r - l)(r - l - 1)}{6}$ （即三元组总数）减去坏三元组的数量。

由于三元组有序，即有 $i < j < k$，一个三元组是坏的当且仅当 $\operatorname{lcm}(i, j, k) = k$ 或 $\operatorname{lcm}(i, j, k) = 2\cdot k  \land i + j > k$。此时，$i$ 和 $j$ 必须是 $k$ 或 $2k$ 的约数。

-  证明：

	1. 坏三元组 $\iff  lcm(i, j, k) < 3k$:
    	
        反设 $\operatorname{lcm}(i,j,k) \ge 3k$，因为 $i < j < k$，故 $i + j + k < 3k$ ，结合反证假设得到 $\operatorname{lcm}(i, j, k) > i + j + k$，不满足计数条件，矛盾。故原命题得证。

	2. $\operatorname{lcm}(i, j, k) = 2k$ 时需满足 $i + j > k$:

    	代入计数条件得 $2k < i + j + k$，两边消去一个 $k$ 即得证。

- Tips：
    通过刚刚得出的条件手算可以得出，满足 $\operatorname{lcm}(i, j, k) = 2k$ 的坏三元组只有 $(3, 4, 6)$ 和 $(6, 10, 15)$ 及其若干正整数倍。
    故我们可以先处理掉这两种情况以简化计算。具体处理方法见代码注释。


我们发现，一个三元组 $(i,j,k)$ 能否对最终答案做出贡献仅取决于 $i$ 和 $k$ 的范围。故我们可以将所有 $i,k$ 相同的三元组合并在一起计数。我们将其记作一个二元组 $(i,k)$。对于每一个二元组 $(i,k)$ (其中 $i$ 是 $k$ 的约数)，我们计数所有满足 $i < j < k$ 且使得 $(i,j,k)$ 为坏三元组的 $j$ 的数量，将其称作这个二元组的权值。

在具体处理时，根据本题的时空限制，我们可以暴力枚举所有的三元组 $(i,j,k)$，其中 $1\le i < j < k$ 且 $i,j$ 为 $k$ 的约数。对于每一个这样的三元组，我们检查它是否是“坏的”。如果是，就把二元组 $(i,k)$ 的权值加一。其复杂度是 $O(n\sqrt{n})$ 的。为了得到最终答案，我们只需要统计区间 $[l,r]$ 中所有二元组 $(i,k)$ 的权值之和。

如果直接暴力枚举所有在 $[l,r]$ 区间内的二元组，可以通过本题的 `easy version`。但由于本题的数据组数可达 $T = 10^5$，这样做显然会超时，故我们考虑用数据结构优化。

注意到我们计数的是带权二元组 $(i,k)$，且二元组要满足 $l\le i \land k \le r$ 的限制，很容易看出这是一个二位数点问题。又因为题目并未要求强制在线，故我们可以将操作离线后用线段树或树状数组解决。

具体实现细节见代码。

## Code：

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
const int N = 2e5;
typedef long long ll;
vector < int > fac[N + 5];
struct stu{
    ll l, r, ans, id;
}q[N + 5];
struct stu1{
    ll x, y, cnt;
}tpl[N * 50];
//这里数组大小需要注意。应当根据理论点对个数来开数组，大小为 n sqrt(n) = 89442719，所以大概要50 * 2 * 10^5。
ll bit[N + 5], ans[N + 5];
int sz[N + 5];
int n, t;
bool cmp(stu a, stu b){
    return a.r == b.r ? a.l < b.l : a.r < b.r;
}
void init(){//预处理1～200000所有数的约数
    for(int i = 3; i <= N; ++i)
        for(int j = 1; j * j <= i; ++j)
            if(!(i % j)){
                fac[i].push_back(j);
                //fac[i]记录第i个数的约数
                sz[i] ++;
                //sz[i]记录第i个数约数的个数
                if(j * j != i && j != 1){
                    fac[i].push_back(i / j);
                    sz[i] ++;
                }
            }
    for(int i = 3; i <= N; ++i)
        sort(fac[i].begin(), fac[i].end());
        //将约数从小到大排序
    //此处我们没有考虑i本身是素数的情况。
    //因为当i为素数时，其不能构成需要计数的三元组，对答案没有贡献。
    return ;
}
void pre_work(){//预处理所有的二元组的权值
    for(int i = 2; i <= N; ++i)
        for(int j = 0; j < sz[i] - 1; ++j){
            tpl[++ t].x = fac[i][j];
            tpl[t].y = i;
            //记录该二元组的左右端点
            tpl[t].cnt = sz[i] - j - 1;
            //计算该二元组的权值
            //由于在此我们只考虑lcm(i,j,k) = k 的情况，每个对于特定的k，每个i都可以和大于它的k的约数形成一个坏三元组
            //故二元组权值可如此计算
        }
    //在数点时我们需要将二元组按照右端点排序，但在此处预处理时已经有序，故不再次排序
}
ll lowbit(ll x){return x & (-x);}
void add(ll pos, ll val){
    while(pos <= N){
        bit[pos] += val;
        pos += lowbit(pos);
    }
    return ;
}
ll query(ll pos){
    ll cur = 0;
    while(pos){
        cur += bit[pos];
        pos -= lowbit(pos);
    }
    return cur;
}
//用树状数组处理二位数点
int main(){
    int T = 0;
    scanf("%d", &T);
    init();
    for(int i = 1; i <= T; ++i){
    	//将询问离线并预处理lcm(i,j,k) = 2k的三元组
        scanf("%lld%lld", &q[i].l, &q[i].r);
        q[i].ans = (q[i].r - q[i].l + 1) * (q[i].r - q[i].l) / 2 * (q[i].r - q[i].l - 1) / 3;
        //初始化最终答案为该区间总共的三元组数量
        q[i].ans -= max((ll)0, q[i].r / 6 - (q[i].l - 1) / 3);
        //减去形如(3, 4, 6)及其倍数的三元组数量
        //此处应用前缀和思想
        //q[i].r/6 表示在 [1, r] 区间内 6 及 6 的倍数的数量，(q[i].l - 1)/3 表示在 [1,l - 1] 区间内 3 及 3 的倍数的数量
        //相减即得到[l,r]区间内形如(3x,6x)的二元组的数量
        //由于每一对形如(3x,6x)的数都可以形成一个坏三元组，故先将这一部分从最终答案中减去
        q[i].ans -= max((ll)0, q[i].r / 15 - (q[i].l - 1) / 6);
        //减去形如(6, 10, 15)及其倍数的三元组数量，原理同上
        q[i].id = i;
      	//记录原编号
    }
    pre_work();
    sort(q + 1, q + T + 1, cmp);//将所有查询区间按照右端点排序
    int tmp = 1;
    memset(bit, 0, sizeof(bit));
    for(int i = 1; i <= T; ++i){
        //按区间右端点从小到大顺序考虑所有的询问
        while(tmp <= t && tpl[tmp].y <= q[i].r){
        	//将所有右端点不超过当前询问区间右端点的二元组加入树状数组
            add(tpl[tmp].x, tpl[tmp].cnt);
            tmp ++;
        }
        q[i].ans -= query(q[i].r) - query(q[i].l - 1);
        //查询答案，前缀和思想
    }
    for(int i = 1; i <= T; ++i)
    	ans[q[i].id] = q[i].ans;
    for(int i = 1; i <= T; ++i)
    	printf("%lld\n", ans[i]);
    //按原顺序输出
    return 0;
}

```

---

## 作者：苏联小渣 (赞：4)

纪念一下第一道独立做出的 *2500。

如果我们随便选三个数 $a<b<c$，我们发现很容易使得 $\text{lcm}(a,b,c) \ge a+b+c$，所以正难则反，考虑什么时候不满足该条件。而在 $r-l+1$ 个数里面选 $3$ 个方案为 $r-l+1 \choose 3$，所以用总数减去不符合的就是答案了。

直觉告诉我们应该会有什么倍数关系。可以发现，如果 $\text{lcm}(a,b,c)=c$，那么就有 $\text{lcm}(a,b,c)=c<a+b+c$。

那么这个是否为 $\text{lcm}(a,b,c)<a+b+c$ 的充要条件呢？先不管那么多，考虑怎样把这部分的答案算出来。发现本质上就是枚举一个 $c$，然后 $a,b$ 为 $c$ 在 $[l,c)$ 范围内的两个不同的因子。对于 E1，枚举 $c \in [l,r]$，然后用根号复杂度求出 $c$ 在 $[l,c)$ 范围内的因子个数 $d_c$，然后这部分的答案就是 $\sum_{c=l}^r \dfrac{d_c \times (d_c-1)}{2}$（也就是 $d_c \choose 2$）。

然后我就写了一发，发现样例过不去。于是就打了个表，发现还真不是充要条件，然后打出了两个反例：$(3,4,6),(6,10,15)$。

发现这两个反例看起来没什么规律，然后我就继续打……等等，怎么上界是 $1000$ 的时候也只有这两个？

于是我们可以大胆猜想，只有满足以下两种情况才有 $\text{lcm}(a,b,c)<a+b+c$。

- 情况 $1$：$(3k,4k,6k)$ 和 $(6k,10k,15k)$，感性理解一下，在 $a,b,c$ 极大的时候还有一组，看起来是不可能的。

- 情况 $2$：所有满足 $a|c,b|c,a<b<c$ 的 $(a,b,c)$，

对于处理情况 $1$，我们只需要把 $k$ 的范围求出来即可。以 $(3k,4k,6k)$ 为例，有 $\lceil \dfrac{l}{3}\rceil \le k \le \lfloor\dfrac{r}{6}\rfloor$，判掉无交即可。单次 $O(1)$。

对于处理情况 $2$，用上述方法即可。对于 E1，单次 $O((r-l+1)\sqrt{r})$。至此可以通过 E1。

考虑 E2，$T$ 很大，那么我们需要优化对于情况 $2$ 的处理方式。而 E1 是对于每个 $c \in [l,r]$ **单独**求答案，这启示我们用类似前缀和的方式统计答案。我们发现，一个数 $c$ 的答案只和 $c$ 本身和 $l$ 有关。所以，这启示我们可以通过离线扫描线的方式计算答案。

对于所有询问 $[l,r]$，我们按照 $l$ 从小到大排序。初始时，算出 $l=1$ 时，所有 $c \in [1,V]$ 的**除去本身**的约数个数，记作 $d_c$，其中 $V$ 为值域上界。那么此时，$c$ 的贡献就是 $f_c={d_c \choose 2}$。我们企图算出，当 $l$ 取遍 $[1,V]$ 时，每个 $c \in [l,V]$ 的贡献 $f_c$，然后用前缀和回答询问。

**考虑转移**：当 $l' \gets l+1$ 时，我们考虑对哪些数，它的 $f$ 值会发生变化。发现 $f$ 本身只与约数个数有关，也就是说，当 $l' \gets l+1$ 时，哪些数 $\ge l'$ 的约数个数会和 $\ge l$ 的约数个数不同。显然，只有 $l$ 的倍数，其 $\ge l'$ 的约数个数会在原有基础上减一。而这些数是可以枚举的，因为其总数就是调和级数级别的，那么其 $d,f$ 值就很好维护了。但是我们要求前缀和，而这些数是离散的，所以必须上能支持单点修改的数据结构，树状数组就可以满足需求。于是最后转化成单点修改、查询区间和的问题了。时间复杂度是 2log 级别的。

对于情况 $1$，其处理方式和 E1 是相同的。总复杂度 $O(t \log^2V)$。

### Code：

```c++
#include <bits/stdc++.h>
using namespace std;
#define N 200000
#define ll long long
int t, lst, l, r, kl, kr, len, d[200010];
ll f[200010], g[200010], ans[200010];
struct node{
	int l, r, id;
	bool operator < (const node &A) const{
		if (l == A.l) return r < A.r;
		return l < A.l;
	}
}a[100010];
void add(int p, ll x){
	for (; p<=N; p+=p&-p) g[p] += x;
}
ll query(int p){
	ll ret = 0;
	for (; p; p-=p&-p) ret += g[p];
	return ret;
}
int main(){
	scanf ("%d", &t);
	for (int i=1; i<=t; i++){
		scanf ("%d%d", &a[i].l, &a[i].r);
		a[i].id = i;
	}
	sort (a+1, a+t+1);
	lst = 1;
	for (int i=1; i<=N; i++){
		int cnt = 0;
		for (int j=1; j<=sqrt(i); j++){
			if (i % j == 0){
				if (j != i) cnt ++;
				if (i / j != i && j != i / j) cnt ++;
			}
		}
		d[i] = cnt;
		f[i] = 1LL * cnt * (cnt - 1) / 2;
		add(i, f[i]);
	}
	for (int i=1; i<=t; i++){
		if (lst != a[i].l){
			for (int j=lst; j<a[i].l; j++){
				for (int k=2; j*k<=N; k++){
					d[j*k] --;
					add(j*k, -f[j*k]);
					f[j*k] = 1LL * d[j*k] * (d[j*k] - 1) / 2;
					add(j*k, f[j*k]);
				}
			}
		}
		lst = a[i].l;
		l = a[i].l, r = a[i].r;
		len = r - l + 1;
		ans[a[i].id] = 1LL*len*(len-1)*(len-2)/6;
		ans[a[i].id] -= query(r) - query(l-1);
		kl = l / 3, kr = r / 6;
		if (l % 3) kl ++;
		if (kl <= kr) ans[a[i].id] -= (kr - kl + 1);
		kl = l / 6, kr = r / 15;
		if (l % 6) kl ++;
		if (kl <= kr) ans[a[i].id] -= (kr - kl + 1);
	}
	for (int i=1; i<=t; i++){
		printf ("%lld\n", ans[i]);
	}
	return 0;
}
```

---

## 作者：youyou2007 (赞：4)


## Description

给定 $l$、$r$，求 $l$ 到 $r$ 之间有多少三元组 $(i,j,k)$，满足 $\operatorname{lcm}(i,j,k) \ge i+j+k$ 且 $i \lt j\lt k$。

**Easy version**

共有 $T (1 \le T \le 5)$ 组询问， $ 1 \le l \le r \le 2 \times 10^5 $。

**Hard version**

共有 $T (1 \le T \le 2 \times 10^{5})$ 组询问， $ 1 \le l \le r \le 2 \times 10^5 $。

## Solution

观察样例，发现合法的状态太多，不好统计，但**正难则反** ，我们考虑统计不合法的三元组，再用总数减去不合法的个数即可。

问题转化为统计  $\operatorname{lcm}(i,j,k) \lt i+j+k$ 的三元组个数。

由于 $i \lt j\lt k$，所以 $i + j + k \le 3k$ ，从而得出 $\operatorname{lcm}(i,j,k) \lt 3 \times k$。

根据最小公倍数的性质可知，$k$ 必然是 $lcm(i,j,k)$ 的约数 ，那么只有两种可能：$\operatorname{lcm}(i,j,k) = k$ 或 $\operatorname{lcm}(i,j,k) = 2 \times k$ 。

先看 $\operatorname{lcm}(i,j,k) = 2 \times k$  的情况，通过打小数据暴力的表发现，只有 $(3,4,6)$ 与 $(6,10,15)$ 和它们的**整数倍**的情况能够满足。

再看另一种情况，  $i$、$j$、$k$ 的最小公倍数为 $k$，说明 $i$ 和 $j$ 都是 $k$ 的约数，这是一个较强的性质。

#### Easy version:

在 **easy version** 下，发现 $T$ 很小，几乎可以忽略成常数对待，而区间值域也不大，可以从 $l+2$ 到 $r$ 枚举 $k$，对于每个 $k$ 计算不合法三元组个数：

+ 对于  $\operatorname{lcm}(i,j,k) = k$  的贡献，枚举 $k$ 在 $[l,r]$ 中有多少个约数，设区间内有 $fac$ 个约数，则贡献为 $C(fac, 2)$ 种。

+ 对于 $\operatorname{lcm}(i,j,k) = 2 \times k$  的贡献，我们直接求是不是上述两种的整数倍即可。

整个区间所有三元组的总数为 $C(r-l+1,3)$ 个，最后答案即为 $C(r-l+1,3) - $ 所有不合法方案总数。

不要忘记开 **long long**，以及注计算组合数时不要一下全乘起来，保证不炸 long long。


#### Hard version:

在 **hard version** 下，$T$ 很大，不能直接暴力，考虑优化。

区间三元组总数可以用组合数学轻松求出，对于 $\operatorname{lcm}(i,j,k) = 2 \times k$  的贡献也能直接求出（在代码中有注释），

我们主要处理  $\operatorname{lcm}(i,j,k) = k$ 的情况 。

既然 $i$ 和 $j$ 都是 $k$ 的约数，而且值域不大，所以可以先把 $1 \sim 200000$ 中每个数除本身的约数处理出来。

为了使约数有序从而方便计算，这里求约数运用了这种方法：

建立一个 vector，外层枚举每个数 $i$，内层枚举它的整数倍，即 $2 \times i$，$3 \times i$，...，一直到超出值域为止，这些数它们都有共同的约数 $i$，插入它们的约数数组中即可，不难发现现在每个数的约数组内也是有序的。

 枚举 $1 \sim 200000$ 中所有数，把每一个数都视作 $k$，此时对应的 $i$ 就是 $k$ 的约数，  $i \sim k$ 中所有 $k$ 的约数个数 $j$ 就是这一个二元组 $(i,k)$ 对答案的贡献。

具体的，若我们现在正在计算 $x$ 这个数的约数的贡献，设处理到了第 $i$ 个约数，$x$ 共有 $siz_{x}$ 个约数，则这个约数的贡献就是 $siz_{x} - i - 1$。

现在该问题转化成了：处理多次询问，每次询问当 $k \le r$ 时计算 $[l,r]$ 区间的答案。这是一个标准的二维数点问题。

可以把所有询问离线下来，按照右端点 $r$ 排序，外层从 $1 \sim 200000$ 枚举，建立一棵树状数组，把所有约数的贡献插入树状数组中， 若碰到一个询问的右端点就计算答案，最后按照**原询问顺序**输出即可。

由于询问也已经有序，我们用一个类似双指针的思想维护现在处理到哪个询问，不断向后移动即可。

设 $N$ 为最大的 $r$，时间复杂度约为 $O(N\sqrt{N} + T \log N)$。
```c++
// by youyou2007 in 2022.
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <queue>
#include <stack>
#include <map>
#define REP(i, x, y) for(int i = x; i < y; i++)
#define rep(i, x, y) for(int i = x; i <= y; i++)
#define PER(i, x, y) for(int i = x; i > y; i--)
#define per(i, x, y) for(int i = x; i >= y; i--)
#define lc (k << 1)
#define rc (k << 1 | 1)
using namespace std;
const int N = 200005;
int T;
struct node{
    long long l, r, id;
}q[N];
long long ans[N], cnt;
long long tree[N];
vector <int> fac[N];
bool cmp(node x, node y)
{
    if(x.r == y.r) return x.l < y.l;
    else return x.r < y.r;
}
int lowbit(int x)
{
    return x & (-x);
}
void add(int x, long long y)
{
    while(x <= 200000)//注意值域应到 200000
    {
        tree[x] += y;
        x += lowbit(x);
    }
}
long long query(int x)
{
    long long res = 0;
    while(x > 0)
    {
        res += tree[x];
        x -= lowbit(x); 
    }
    return res;
}
int main()
{
    scanf("%d", &T);
    for(int i = 1; i <= T; i++)
    {
        scanf("%lld%lld", &q[i].l, &q[i].r);
        ans[i] = (q[i].r - q[i].l + 1) * (q[i].r - q[i].l) / 2 * (q[i].r - q[i].l - 1) / 3;//计算总的三元组数
        ans[i] -= max((long long)0, q[i].r / 6 - (q[i].l - 1) / 3);//处理 (3, 4, 6) 以及它们的整数倍情况，先看[1, r] 区间有多少个 6 的倍数，再看 [1, l - 1] 区间有多少个 3 的倍数，两者一减则就是 [l, r] 中满足 (3x, 6x) 这样的数，但可能这个区间小到没有这样的数，所以要和 0 取 max
        ans[i] -= max((long long)0, q[i].r / 15 - (q[i].l - 1) / 6);//处理 (6, 10, 12) 以及它们的整数倍情况，道理同上，注意是 l - 1
        q[i].id = i;//记录下询问的编号
    }
    for(int i = 1; i <= 200000; i++)
    {
        for(int j = i * 2; j <= 200000; j += i)//从 i * 2 开始
        {
            fac[j].push_back(i);//计算出每个数除自己之外的约数，正好 vector 也能一并记下约数个数
        }
    }
    sort(q + 1, q + T + 1, cmp);//按照右端点按照询问排序
    int now = 1;
    for(int i = 1; i <= 200000; i++)
    {
        for(int j = 0; j < fac[i].size(); j++)
        {
            add(fac[i][j], fac[i].size() - 1 - j);//把 i 的所有约数插入树状数组中，原因已解释
        }
        while(now <= T && q[now].r <= i)//类似双指针扫描，对于每个询问我们计算答案
        {
            ans[q[now].id] -= query(q[now].r) - query(q[now].l - 1);
            now++;
        }
    }
    for(int i = 1; i <= T; i++)
    {
        printf("%lld\n", ans[i]);
    }
	return 0;

}
```



---

## 作者：diqiuyi (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1712E2)。

**思路**

正难则反，考虑 $\operatorname{lcm}(i,j,k) < i+j+k$ 且 $l \le i<j<k \le r$ 的三元组数量。

显然三元组总数量为 $C_{r-l+1}^3$。

显然有 $\operatorname{lcm}(i,j,k) < i+j+k <3k$，故 $\operatorname{lcm}(i,j,k)=k$ 或 $\operatorname{lcm}(i,j,k)=2k$。

首先考虑 $\operatorname{lcm}(i,j,k)=2k$，此时 $2k<i+j+k$，$k<i+j$。

设 $i=\dfrac{2k}{a}$，$j=\dfrac{2k}{b}$，显然 $2<b<a$。

于是 $\dfrac{2k}{a}+\dfrac{2k}{b}>k$，$\dfrac{2}{a}+\dfrac{2}{b}>1$。

$\because \dfrac{2}{b}>\dfrac{2}{a}$，$\therefore \dfrac{2}{b}>\dfrac{1}{2}$，$b=3$。

代入得 $\dfrac{2}{a}+\dfrac{2}{3}>1$，$a=4$ 或 $a=5$。

即 $i:j:k=3:4:6$ 或 $i:j:k=6:10:15$。

这两种情况均要满足 $l\le i\And k \le r$，故询问 $(l,r)$ 中这一部分的贡献为 $(\left\lfloor\dfrac{r}{6}\right\rfloor-\left\lceil\dfrac{l}{3}\right\rceil+1)+(\left\lfloor\dfrac{r}{15}\right\rfloor-\left\lceil\dfrac{l}{6}\right\rceil+1)$，显然如果某部分贡献 $<0$ 则不计算该部分贡献。

接下来考虑 $\operatorname{lcm}(i,j,k)=k$，即 $i,j$ 都是 $k$ 的约数。

不妨考虑把每个数的因数都先用一个动态数组存下来，可以枚举每个数，然后将其放入其倍数中，这部分的时间复杂度是 $O(\sum{\dfrac{n}{i}}=n \ln n)$，参考代码如下：
```cpp
for(int i=1;i<=n;i++)
	for(int j=(i<<1);j<=n;j+=i)
		g[j].push_back(i);
```
不难发现我们可以把每个成倍数关系的 $(i,k)$ 单独看作一个带权的点，其权值为此时可选择的 $j$ 的个数，不难发现 $(i,k)$ 的个数大约是 $n \ln n$。

现在问题转化为有若干个点 $(i,k)$，求满足 $l \le i \And k \le r$ 的点的权值和。我们不妨把所有询问离线下来，将右端点从小到大排序，再将 $(i,k)$ 按 $i$ 从小到大排序，处理到一个新的询问就将所有可能会对该询问及后面的询问产生贡献的点加入树状数组，最后用树状数组查询即可。

**CODE**
```cpp
#include <bits/stdc++.h>
#define int long long
#define n 200000
using namespace std;
int t,cnt,now=1;
vector<int> g[200005];
long long ans[100005],a[200005];
struct qu{
	int l,r,id;
	bool operator <(qu x) const{
		return r^x.r?r<x.r:l<x.l;
	}
}q[100005];
struct pt{
	int lt,rt,val;
}p[5000005];
void upd(int x,int y){
	for(;x<=n;x+=(x&(-x)))
		a[x]+=y;
}
long long sum(int x){
	long long res=0;
	for(;x;x-=(x&(-x)))
		res+=a[x];
	return res;
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>t;
	for(int i=1;i<=n;i++)
		for(int j=(i<<1);j<=n;j+=i)
			g[j].push_back(i);//预处理因数
	for(int i=1;i<=n;i++)
		for(int j=0;j<(int)g[i].size()-1;j++)
			p[++cnt].lt=g[i][j],p[cnt].rt=i,p[cnt].val=g[i].size()-j-1;
            	//预处理点对 (i,k)，即此处的 (lt,rt)，j 的个数即满足大于 i 且小于 k 的 k 的因数个数
	for(int i=1;i<=t;i++)
		cin>>q[i].l>>q[i].r,q[i].id=i;
	sort(q+1,q+t+1); 	 
	for(int i=1;i<=t;i++){
		while(now<=cnt&&p[now].rt<=q[i].r) 
			upd(p[now].lt,p[now].val),now++;//将点加入
		ans[q[i].id]=1ll*(q[i].r-q[i].l+1)*(q[i].r-q[i].l)*(q[i].r-q[i].l-1)/6-
		max(0ll,q[i].r/6-(q[i].l-1)/3)-max(0ll,q[i].r/15-(q[i].l-1)/6)-sum(q[i].r)+sum(q[i].l-1);
        	//分别计算贡献
	}
	for(int i=1;i<=t;i++)
		cout<<ans[i]<<'\n';
	return 0;
}
```

---

## 作者：liyixin0514 (赞：1)

# LCM Sum (hard version)

> 计数题。不断缩小答案范围。

反过来求 $\text{lcm}(i,j,k) < i+j+k$ 的数量。因为 $i+j+k < 3k$，所以 $\text{lcm}(i,j,k) = k$ or $2k$。

1. $\text{lcm} = k$。

$i,j$ 是 $k$ 的因子且 $i,j\ge l$。

可以枚举 $k$ 和 $i$，求 $j>i \land j\mid k$。容易直接计算出所有合法 $j$ 的个数。

枚举 $i$ 而不是 $j$ 的好处是对于每组询问，只要 $i,k$ 合法，所有 $j$ 也不会超出区间 $[l,r]$。

把 $(i,k)$ 看作二维平面上的点，点有点权，每次询问数满足 $l \le i < k \le r$ 的点的点权之和。

时间复杂度 $O(n \log^2 n)$。

2. $\text{lcm} = 2k$。

$2k<i+j+k \Rightarrow i+j>k$。

所以 $j > \frac{k}{2}$。$j$ 不是 $k$ 的因子。所以 $j$ 分解质因数一定比 $k$ 多一个 $2$。

$\frac{j}{2}$ 是 $k$ 的因子，所以 $j$ 不超过 $k$ 的因子个数个。

发现满足要求的 $\frac{j}{2}$ 只能是 $\frac{k}{3}$。

所以 $j = \frac{2}{3}k$。

$i$ 必须是 $2k$ 的因子。而且 $i> \frac{1}{3} \cdot \frac{1}{2}\cdot 2k \land i < \frac{2}{3} \cdot \frac{1}{2} \cdot 2k$。

所以 $i = \frac{1}{4} \cdot 2k$ or $\frac{1}{5} \cdot 2k$。

所以 $(i,j,k)$ 是 $(3d,4d,6d)$ 或 $ (6d,10d,15d)$ 的形式。

根据 $l \le i,j,k \le r$ 解不等式即可。

## code

```cpp
#include<bits/stdc++.h>
#define sf scanf
#define pf printf
#define rep(x,y,z) for(int x=y;x<=z;x++)
#define per(x,y,z) for(int x=y;x>=z;x--)
using namespace std;
typedef long long ll;
namespace wing_heart {
	constexpr int Max=2e5,T=1e5+7;
	vector<int> son[Max+5];
	typedef pair<int,int> pii;
	#define fi first 
	#define se second 
	vector<pii> vec[Max+5];
	struct qpii {
		int id,l,r;
	}q[T];
	int t,l,r;
	void init() {
		rep(i,1,Max) {
			rep(j,2,Max/i) {
				son[i*j].push_back(i);
			}
		}
		rep(i,1,Max) {
			rep(j,0,(int)son[i].size()-2) {
				vec[son[i][j]].push_back({i,son[i].size()-j-1});
			}
		}
	}
	bool cmp(qpii a, qpii b) { return a.l > b.l; }
	int tr[Max+5];
	void add(int x,int val) {
		for(;x<=Max;x+=x&-x) tr[x]+=val;
	}
	int query(int x) {
		int sum=0;
		for(;x;x-=x&-x) sum+=tr[x];
		return sum;
	}
	ll ans[T];
    void main() { 
		sf("%d",&t);
		init();
		rep(i,1,t) {
			sf("%d%d",&l,&r);
			q[i]={i,l,r};
			ans[i]=1ll*(r-l+1)*(r-l)*(r-l-1)/6;
			ans[i]-=max(0,(r/6)-((l+2)/3)+1)+max(0,(r/15)-((l+5)/6)+1);
		}
		sort(q+1,q+t+1,cmp);
		int it=1;
		per(i,Max,1) {
			for(auto p : vec[i]) {
				add(p.fi,p.se);
			}
			while(it<=t && q[it].l==i) {
				ans[q[it].id]-=query(q[it].r);
				++it;
			}
		}
		rep(i,1,t) pf("%lld\n",ans[i]);
    }
}
int main() {
    #ifdef LOCAL
    freopen("in.txt","r",stdin);
    freopen("my.out","w",stdout);
    #endif
    wing_heart :: main();
}
```

---

## 作者：bryce (赞：1)

## [LCM Sum (hard version)](https://www.luogu.com.cn/problem/CF1712E2)
### 思路
正着做不好做，考虑用总数减去不好的三元组的数量，即 $\operatorname{lcm}(i, j, k)\lt i + j + k$ 的数量。

由于 $i\lt j\lt k$，所以 $\operatorname{lcm}(i, j, k)\lt 3k$ 才有可能成为不好的三元组，那么 $\operatorname{lcm}(i, j, k) = k$ 或 $\operatorname{lcm}(i, j, k) = 2k$ 但在等于 $2k$ 时要满足 $i + j \lt k$。

如何统计答案？首先总的三元组的数量为 $\binom{r - l + 1}{3}$，手玩一下发现当 $\operatorname{lcm}(i, j, k) = 2k$ 且不好的三元组只有可能是 $(3x, 4x, 6x)$ 或 $(6x, 10x, 15x)$，由于 $l\le 3x\lt 6x\le r$，所以第一种情况的数量为 $\frac{r}{6} - \frac{l - 1}{3}$，第二种情况的数量同理就为 $\frac{r}{15} - \frac{l - 1}{6}$，将答案减去这些即可完成等于 $2k$ 的讨论。

接下来考虑如何统计等于 $k$ 的三元组数量，那么 $i$ 和 $j$ 都为 $k$ 的约数，我们发现一个这样的三元组与 $j$ 无关，只与一个二元组 $(i, k)有关$，我们只需要知道 $i$ 和 $k$ 值，统计有多少个 $j$ 满足条件即为一个二元组 $(i, k)$ 的权值，这部分可以预处理得到，于是只需枚举二元组将每个二元组的权值加起来即为等于 $k$ 的三元组的数量。

考虑暴力枚举二元组不优秀，因为 $T\le 10^5$，但由于没有强制在线，可以用二维数点将其离线下来去做，将一个二元组 $(i, k)$ 看成平面上的点 $(x, y)$，每个点有权重，那么询问区间等于 $k$ 的三元组数量即为右上角为 $(r, r)$，左下角为 $(l, l)$ 的矩形中的点的权重之和。
### 代码
```cpp
#include<iostream>
#include<vector>
#include<algorithm>
#define int long long

using namespace std;

inline int read(){register int x = 0, f = 1;register char c = getchar();while (c < '0' || c > '9'){if (c == '-') f = -1;c = getchar();}while (c >= '0' && c <= '9'){x = (x << 1) + (x << 3) + (c ^ 48);c = getchar();}return x * f;}

const int N = 2e5 + 10, M = 1e7 + 10, K = 2e5;
int T;
vector<int> g[N];
void init(){
    for (int i = 2; i <= K; i++){
        for (int j = 1; j * j <= i; j++){
            if (i % j == 0){
                g[i].emplace_back(j);
                if (j * j != i && j != 1) g[i].emplace_back(i / j);
            }
        }
    }
    for (int i = 2; i <= K; i++) sort(g[i].begin(), g[i].end());
}
struct node{
    int l, r, id, res;
}q[N];
struct Query{
    int x, y, cnt, id, opt;
    bool operator < (const Query &b) const{
        return (x == b.x ? opt < b.opt : x < b.x);
    }
}p[M];
int cnt;
void get(){
    for (int i = 2; i <= K; i++){
        int h = g[i].size();
        for (int j = 0; j < h; j++){
            p[++cnt] = (Query){g[i][j], i, h - j - 1, 0, 0};
        }
    }
}
int t[N];
int lowbit(int x){return x & -x;}
void add(int x, int k){
    for (int i = x; i <= K; i += lowbit(i)) t[i] += k;
}
int query(int x){
    int res = 0;
    for (int i = x; i; i -= lowbit(i)) res += t[i];
    return res;
}

signed main(){
    T = read();
    init();
    for (int i = 1; i <= T; i++){
        int l = read(), r = read();
        q[i].l = l, q[i].r = r, q[i].id = i;
        q[i].res = (r - l + 1) * (r - l) * (r - l - 1) / 6;
        q[i].res -= max(r / 6 - (l - 1) / 3, 0ll);
        q[i].res -= max(r / 15 - (l - 1) / 6, 0ll);
    }
    get();
    for (int i = 1; i <= T; i++){
        p[++cnt] = (Query){q[i].r, q[i].r, 0, q[i].id, 1};
        p[++cnt] = (Query){q[i].r, q[i].l - 1, 0, q[i].id, 2};
        p[++cnt] = (Query){q[i].l - 1, q[i].r, 0, q[i].id, 2};
        p[++cnt] = (Query){q[i].l - 1, q[i].l - 1, 0, q[i].id, 1};
    }
    sort(p + 1, p + cnt + 1);
    for (int i = 1; i <= cnt; i++){
        if (p[i].opt == 0) add(p[i].y, p[i].cnt);
        else if (p[i].opt == 1) q[p[i].id].res -= query(p[i].y);
        else q[p[i].id].res += query(p[i].y);
    }
    for (int i = 1; i <= T; i++) cout << q[i].res << '\n';
    return 0;
}
```

---

## 作者：happy_dengziyue (赞：1)

### 1 视频题解

![](bilibili:BV1DS4y1s7yL)

### 2 思路

本题解按照困难难度撰写。

满足条件的三元组个数有点不好求，那么我们就求不满足条件的三元组。

题目告诉我们，$i<j<k$。那么如果 $\operatorname{lcm}(i,j,k)<i+j+k$，必须满足两个条件之一：

$i\mid k\operatorname{and}j\mid k$

$i\mid k\times2\operatorname{and}j\mid k\times2\operatorname{and}i+j>k$

可以发现，若 $i\mid k$，那么必定有 $i\mid k\times2$。$j$ 同理。

我们可以**依次**枚举 $k$，然后列出所有的 $k\times2$ 的因数。在此基础上枚举 $i$ 和 $j$。

我们可以一边枚举一边记录答案。

将所有的询问按照 $r$ 升序排序。然后，每当我们完成上述枚举（但是还没有开始枚举下一个 $k$ 的时候），我们要解决所有的满足 $r=k$ 的问题。

因为此时，所有的被枚举出来的三元组的所有数字都不会大于 $k$。此时解决问题才正确。

例如，当枚举到 $k=4$ 时，只有 $(1,2,4)$ 一个三元组满足 $\operatorname{lcm}(i,j,k)=4<i+j+k=7$，那么我们就可以解决诸如 $[1,4]$ 之类的问题。

我们可以发现，每当找到一个三元组，我们就要记录有多少个三元组满足左端点是 $i$。我们可以用线段树储存。

解决问题的时候直接找有多少个三元组左端点在  $l$ 和 $k$ 之间即可。反正此时被找到的三元组右端点也都不会超过 $k$。

我们可以发现，总的三元组个数是 $(r-l+1)\times(r-l)\times(r-l-1)\div6$。用总数减去不符题意的数即为符合题意的数。

输出答案即可。

### 3 代码与记录

```cpp
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<vector>
using namespace std;
#define max_n 200000
int p[202];
int pi;
struct V{
	int x,cnt;
	long long sum;
};
int q;
struct Q{
	int id,l,r;
	long long ans;
}a[max_n+2];
struct TR{
	int l,r;
	long long sum;
}tr[max_n<<2];
bool cmpr(Q a,Q b){
	return a.r<b.r;
}
bool check(int i,int j,int k){
	return (!(k%i)&&!(k%j))||i+j>k;
}
void pu(int o){
	tr[o].sum=tr[o<<1].sum+tr[o<<1|1].sum;
}
void build(int o,int l,int r){
	tr[o]=(TR){l,r,0};
	if(l>=r)return;
	int mid=(l+r)>>1;
	build(o<<1,l,mid);
	build(o<<1|1,mid+1,r);
}
void upd(int o,int x,int w){
	int l=tr[o].l,r=tr[o].r;
	if(l>=r){
		tr[o].sum+=w;
		return;
	}
	int mid=(l+r)>>1;
	if(x<=mid)upd(o<<1,x,w);
	else upd(o<<1|1,x,w);
	pu(o);
}
long long query(int o,int ql,int qr){
	int l=tr[o].l,r=tr[o].r;
	if(ql<=l&&r<=qr)return tr[o].sum;
	int mid=(l+r)>>1;
	long long res=0;
	if(ql<=mid)res+=query(o<<1,ql,qr);
	if(qr>mid)res+=query(o<<1|1,ql,qr);
	return res;
}
bool cmpid(Q a,Q b){
	return a.id<b.id;
}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1712E2_1.in","r",stdin);
	freopen("CF1712E2_1.out","w",stdout);
	#endif
	scanf("%d",&q);
	for(int i=1;i<=q;++i){
		a[i].id=i;
		scanf("%d%d",&a[i].l,&a[i].r);
	}
	sort(a+1,a+q+1,cmpr);
	build(1,1,max_n);
	for(int k=1,ai=1;k<=max_n;++k){
		pi=0;
		for(int i=1,len=sqrt(k<<1);i<=len;++i){
			if((k<<1)%i==0){
				p[++pi]=i;
				p[++pi]=(k<<1)/i;
			}
		}
		sort(p+1,p+pi+1);
		pi=unique(p+1,p+pi+1)-p-1;
		for(int i=1,cnt;i<=pi&&p[i]<k;++i){
			cnt=0;
			for(int j=i+1;j<=pi&&p[j]<k;++j){
				if(check(p[i],p[j],k))++cnt;
			}
			if(!cnt)continue;
			upd(1,p[i],cnt);
		}
		while(a[ai].r==k){
			long long len=(a[ai].r-a[ai].l+1);
			a[ai].ans=len*(len-1)*(len-2)/6-query(1,a[ai].l,k);
			++ai;
		}
	}
	sort(a+1,a+q+1,cmpid);
	for(int i=1;i<=q;++i)printf("%lld\n",a[i].ans);
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/83727195)

By **dengziyue**

---

## 作者：zyn0309 (赞：1)

# CF1712E2 LCM Sum (hard version)
[题目传送门](https://codeforces.com/problemset/problem/1712/E2)
## 思路
将 $\operatorname{lcm}(i,j,k) \ge i+j+k $ 的数量比较大，不太好处理，因此转化为总数量减去 $\operatorname{lcm}(i,j,k) < i+j+k $ 的数量。

对于长度为 $n$ 的区间，总数为三元组 $(i,j,k)$ 的数量，即 $\binom{n}{3}$。

三元组满足 $i<j<k$，则满足条件的三元组的 $\operatorname{lcm}(i,j,k)$ 最大为 $2k$。因为 $i+j+k$ 显然小于 $3k$。

分开讨论 $\operatorname{lcm}(i,j,k)$ 为 $k$ 和 $2k$ 的情况：

当 $\operatorname{lcm}(i,j,k)$ 等于 $k$，所以 $i$ 和 $j$ 都为 $k$ 的因数。我们可以枚举所有可能的 $k$，再枚举所有 $k$ 的因数。在处理答案时，只要 $i \ge l$ 且 $k \le r$ 就可以对当前询问产生贡献。因此只要确定二元组 $(i,k)$ 就可以统计答案，该二元组的贡献就是 $i$ 和 $j$ 之间 $k$ 因数的个数，然后将该二元组和贡献插入一个结构体数组中。

当 $\operatorname{lcm}(i,j,k)$ 等于 $2k$，$i$ 和 $j$ 都为 $k$ 的因数或 $k$ 的因数的两倍，且 $\operatorname{lcm}(i,k)$ 或 $\operatorname{lcm}(j,k)$ 等于 $2k$。所以可以把所有满足 $\operatorname{lcm}(j,k)$ 等于 $2k$ 的 $j$ 插入树状数组，然后枚举所有 $k$ 的因数以及二倍作为 $i$，去树状数组上大于 $\max(j,k-j)$ 的区间检查有没有值，并将找到的二元组和贡献插入一个结构体数组中。

以上两部分代码：
```cpp
for(int i=1;i<=2e5;++i){
  l=0;
  for(int j=1;j*j<=i;++j){
  	if(i%j)continue;
  	f[++l]=j;
  	if(j*j!=i&&j!=1)f[++l]=i/j;
  }
  sort(f+1,f+1+l);
  for(int j=1;j<l;++j){
	++len;
	q[len].l=f[j];
	q[len].r=i;
	q[len].cnt=l-j;
  }
  int l2=l;
  for(int j=1;j<=l;++j){
	if(2*f[j]<i&&2*f[j]/__gcd(2*f[j],i)==2)
	  f[++l2]=2*f[j],add(2*f[j],1);
  }
  for(int j=1;j<=l2;++j){
  	int siz=sum(i)-sum(max(i-f[j],f[j]));
  	if(!siz)continue;
	++len;
	q[len].l=f[j];
	q[len].r=i;
	q[len].cnt=siz;
  }
  for(int j=1;j<=l;++j){
	if(2*f[j]<i&&2*f[j]/__gcd(2*f[j],i)==2)
	  add(2*f[j],-1);
  }
}
```

此时，我们已经成功将该问题转换为了二维偏序问题，做法比较多。

提供一种使用树状数组的做法。把所有询问和可能造成贡献的二元组存到一个结构体数组中并按照右端点排序，然后依次按照左端点插入树状数组。查询时，直接查询树状数组上大于等于 $l$ 的区间的和即为答案。

## Code
```cpp
#include<bits/stdc++.h>
#define ll long long
namespace fast_IO {
#define IOSIZE 1000000
	char ibuf[IOSIZE], obuf[IOSIZE], *p1 = ibuf, *p2 = ibuf, *p3 = obuf;
#define getchar() ((p1==p2)and(p2=(p1=ibuf)+fread(ibuf,1,IOSIZE,stdin),p1==p2)?(EOF):(*p1++))
#define putchar(x) ((p3==obuf+IOSIZE)&&(fwrite(obuf,p3-obuf,1,stdout),p3=obuf),*p3++=x)
#define isdigit(ch) (ch>47&&ch<58)
#define isspace(ch) (ch<33)
	template<typename T> inline T read() { T s = 0; int w = 1; char ch; while (ch = getchar(), !isdigit(ch) and (ch != EOF)) if (ch == '-') w = -1; if (ch == EOF) return false; while (isdigit(ch)) s = s * 10 + ch - 48, ch = getchar(); return s * w; }
	template<typename T> inline bool read(T &s) { s = 0; int w = 1; char ch; while (ch = getchar(), !isdigit(ch) and (ch != EOF)) if (ch == '-') w = -1; if (ch == EOF) return false; while (isdigit(ch)) s = s * 10 + ch - 48, ch = getchar(); return s *= w, true; }
	template<typename T> inline void print(T x) { if (x < 0) putchar('-'), x = -x; if (x > 9) print(x / 10); putchar(x % 10 + 48); }
	inline bool read(char &s) { while (s = getchar(), isspace(s)); return true; }
	inline bool read(char *s) { char ch; while (ch = getchar(), isspace(ch)); if (ch == EOF) return false; while (!isspace(ch)) *s++ = ch, ch = getchar(); *s = '\000'; return true; }
	inline void print(char x) { putchar(x); }
	inline void print(char *x) { while (*x) putchar(*x++); }
	inline void print(const char *x) { for (int i = 0; x[i]; i++) putchar(x[i]); }
	inline bool read(std::string& s) { s = ""; char ch; while (ch = getchar(), isspace(ch)); if (ch == EOF) return false; while (!isspace(ch)) s += ch, ch = getchar(); return true; }
	inline void print(std::string x) { for (int i = 0, n = x.size(); i < n; i++) putchar(x[i]); }
	inline bool read(bool &b) { char ch; while(ch=getchar(), isspace(ch)); b=ch^48; return true; }
	inline void print(bool b) { putchar(b+48); }
	template<typename T, typename... T1> inline int read(T& a, T1&... other) { return read(a) + read(other...); }
	template<typename T, typename... T1> inline void print(T a, T1... other) { print(a), print(other...); }
	struct Fast_IO { ~Fast_IO() { fwrite(obuf, p3 - obuf, 1, stdout); } } io;
	template<typename T> Fast_IO& operator >> (Fast_IO &io, T &b) { return read(b), io; }
	template<typename T> Fast_IO& operator << (Fast_IO &io, T b) { return print(b), io; }
#define cout io
#define cin io
#define endl '\n'
} using namespace fast_IO;
using namespace std;
const int N=2e5+10;
int n,m,len,f[N],l;
struct query{
	int l,r,cnt,id;
}q[N*20];
ll ans[N],t[N];
inline bool cmp(query a,query b){
	if(a.r!=b.r)return a.r<b.r;
	else return a.cnt>b.cnt;
}
#define lowbit(x) (x&(-x))
inline void add(int x,int val){
	for(int i=x;i<=2e5;i+=lowbit(i))
	  t[i]+=val;
}
inline ll sum(int x){
	ll res=0;
	while(x>0){
	  res+=t[x];
	  x-=lowbit(x);
	}
	return res;
}
signed main(){
	for(int i=1;i<=2e5;++i){
	  l=0;
	  for(int j=1;j*j<=i;++j){
	  	if(i%j)continue;
	  	f[++l]=j;
	  	if(j*j!=i&&j!=1)f[++l]=i/j;
	  }
	  sort(f+1,f+1+l);
	  for(int j=1;j<l;++j){
		++len;
		q[len].l=f[j];
		q[len].r=i;
		q[len].cnt=l-j;
	  }
	  int l2=l;
	  for(int j=1;j<=l;++j){
		if(2*f[j]<i&&2*f[j]/__gcd(2*f[j],i)==2)
		  f[++l2]=2*f[j],add(2*f[j],1);
	  }
	  for(int j=1;j<=l2;++j){
	  	int siz=sum(i)-sum(max(i-f[j],f[j]));
	  	if(!siz)continue;
		++len;
		q[len].l=f[j];
		q[len].r=i;
		q[len].cnt=siz;
	  }
	  for(int j=1;j<=l;++j){
		if(2*f[j]<i&&2*f[j]/__gcd(2*f[j],i)==2)
		  add(2*f[j],-1);
	  }
	}
	cin>>m;
	for(int i=1;i<=m;++i){
	  ++len;
	  cin>>q[len].l>>q[len].r;
	  q[len].cnt=-1;
	  q[len].id=i;
	}
	sort(q+1,q+1+len,cmp);
	for(int i=1;i<=len;++i){
	  if(q[i].cnt==-1)ans[q[i].id]=1ll*(q[i].r-q[i].l+1)*(q[i].r-q[i].l)*(q[i].r-q[i].l-1)/6-(sum(2e5)-sum(q[i].l-1));
	  else add(q[i].l,q[i].cnt);
	}
	for(int i=1;i<=m;++i)cout<<ans[i]<<"\n";
	return 0;
}
```

---

## 作者：xiezheyuan (赞：0)

## 简要题意

$T$ 组询问，每组询问给出 $[l,r]$，你需要求出有多少个有序对 $(i,j,k)$，满足：

- $l\leq i\lt j\lt k\leq r$。
- $\mathrm{lcm}(i,j,k)\geq i+j+k$。

$1\leq T,l,r\leq 2\times 10^5$。

## 思路

观察样例可得，对于区间 $[6,86868]$，有 $109229059713337$ 个好的有序对，而根据简单的组合数学知识（后面会谈到），区间内只有 $109229066961511$ 个有序对，相当于区间内只有 $7248174$ 个不好的有序对，这引导我们正难则反，改为统计区间中有多少个不好的有序对。

考察不好的有序对的条件 $\mathrm{lcm}(i,j,k)<i+j+k$，由于 $i<j<k$，所以有 $i+j+k<3k$。进而可得 $\mathrm{lcm}(i,j,k)<3k$。

根据 LCM 的基本性质，可以得到 $k\mid \mathrm{lcm}(i,j,k)$，也就是说 $\mathrm{lcm}(i,j,k)$ 只能为 $k$ 或 $2k$。

先考虑 $\mathrm{lcm}(i,j,k)=k$ 的情况，那么需要满足 $k\mid i,k\mid j$，可以预先求出每一个 $k$ 的所有因子，然后将所有询问离线下来按照 $r$ 做扫描线，每次我们枚举 $k$ 和最小的因子 $i$，不难计算出 $j$ 的数量，这一部分可以用树状数组简单维护。

然后考虑 $\mathrm{lcm}(i,j,k)=2k$ 的情况，我想出了几种做法，然后发现不是算重了就是算漏了，非常麻烦。

不过我们发现这种情况非常少（对于区间 $[6,86868]$ 只有 $20268$ 个），可以考虑打表出来观察性质。

然后你可以发现一个非常神奇的结论：

> 不好的有序对 $(i,j,k)$，若满足 $\mathrm{lcm}(i,j,k)=2k$，则存在一个整数 $t$，使得 $3t=i,4t=j,6t=k$ 或 $6t=i,10t=j,15t=k$。

这种情况可以在扫描线中一起维护。

时间复杂度 $O(n\log^2 n+T\log n)$。

## 代码

代码感觉写的比较清真，应该不难读懂。

```cpp
#include <bits/stdc++.h>
#define int long long
#define lowbit(x) ((x) & (-(x)))
using namespace std;

const int N = 2e5 + 5;
int n, q, ans[N], t[N];
vector<int> bs[N];
vector<pair<int,int> > qry[N];

void update(int p, int v){
    while(p <= n) t[p] += v, p += lowbit(p);
}

int query(int p){
    int ret = 0;
    while(p) ret += t[p], p -= lowbit(p);
    return ret;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> q;
    for(int i=1;i<=q;i++){
        int l, r; cin >> l >> r;
        n = max(n, r); qry[r].emplace_back(l, i);
    }
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j+=i) bs[j].emplace_back(i);
    }
    for(int i=1;i<=n;i++){
        for(size_t j=0;j<bs[i].size()-1;j++) update(bs[i][j], bs[i].size() - j - 2);
        if(!(i % 6)) update(i >> 1, 1);
        if(!(i % 15)) update(i / 15 * 6, 1);
        for(auto [l, id] : qry[i]){
            int all = (i - l + 1);
            all = all * (all - 1) / 2 * (all - 2) / 3;
            ans[id] = all - (query(i) - query(l - 1));
        }
    }
    for(int i=1;i<=q;i++) cout << ans[i] << '\n';
    return 0;
}

// Written by xiezheyuan
```

---

## 作者：strcmp (赞：0)

对于题目给的条件很奇怪，然后要我们去计数，一种想法是满足/不满足这种条件的数是不是（相对全集）很少，然后我们就可以考虑上二维数点之类的东西直接做。

$\text{lcm}(i,\,j,\,k) \ge i + j + k$，第一眼看过去，我们发现满足条件的数实在太多了。绝大部分情况下 $\text{lcm}(i,\,j,\,k)$ 都是一个 $\mathcal O(n^3)$ 级别的数，而 $i + j + k$ 只是 $\mathcal O(n)$ 级别的数。

正难则反，考虑用 $\frac{(r - l + 1)(r - l)(r - l - 1)}{6}$ 也就是三元组总数，减去不合法的三元组数量。也就是 $\text{lcm}(i,\,j,\,k) < i + j + k$ 的数量。

根据定义，$\text{lcm}(i,\,j,\,k)$ 一定是 $k$ 的倍数，那么它可能等于 $k,\,2k,\,3k,\,\dots$。

不合法的三元组，$\text{lcm}(i,\,j,\,k)$ 一定要么是 $k$，要么是 $2k$。不然 $3k > i + j + k$。

问题就变成了计数 $\text{lcm}(i,\,j,\,k) = k$ 和 $\text{lcm}(i,\,j,\,k) = 2k$ 的数量。

那不妨枚举 $i,\,k$，因为枚举了这两个我们可以顺道规避掉 $[l,\,r]$ 的限制，用二维数点即可。

如果 $\text{lcm}(i,\,j,\,k) = k$，那 $k$ 一定只能是 $i$ 的倍数，枚举 $i$ 再枚举 $k$。$j$ 是 $[i + 1,\,k - 1]$ 之间是 $k$ 的因数的数的数量，这东西提前预处理一下即可。

如果 $\text{lcm}(i,\,j,\,k) = 2k$，我们发现并不好放在一起处理（同学说直接二次离线下来扫一遍也是可以的，不太会）。

考虑一些智慧方法，经过打表我们发现满足这种情况的，不合法的点对只有 $3k,\,4k,\,6k$ 和 $6k,\,10k,\,15k$，其中 $k$ 是正整数。证明可以代换 $i \leftarrow \frac{2k}{x},\,j \leftarrow \frac{2k}{y}$ 解方程严格证明，也可以感性理解，这样的点对极其特殊在值域大的时候基本不可能出现。于是这些点对在读入的时候直接容斥掉就可以了。

求出不合法的 $(i,\,k)$ 对，问题整个变成了带权二维数点，扫描线用个树状数组维护即可。

时间复杂度 $\Theta(T \log^2 n)$，可以通过。

```cpp
#include <bits/stdc++.h>
#define X first
#define Y second
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define per(i, a, b) for (int i = a; i >= b; i--)
#define pb push_back
#define mp make_pair
using namespace std;
typedef long long int ll;
using pii = pair<int, int>;
constexpr int maxn = 2e5 + 10, V = 2e5, mod = 998244353;
ll c[maxn], ans[maxn]; int T, n, f[maxn]; vector<pii> g[maxn], q[maxn];	
inline void add(int x, ll d) { while (x) c[x] += d, x -= x & -x; }
inline ll qry(int x) { ll s = 0; while (x <= V) s += c[x], x += x & -x; return s; }
int main() {
	scanf("%d", &T); 
	rep(i, 1, V) for (int j = i + i; j <= V; j += i) ++f[j];
	rep(i, 1, V) for (int j = i + i; j <= V; j += i) if (f[j] - 1) g[j].pb(mp(i, --f[j]));
	rep(i, 1, T) {
		int l, r; scanf("%d%d", &l, &r);
		if (r - l + 1 < 3) continue;
		ans[i] += (ll)(r - l - 1) * (r - l) * (r - l + 1) / 6;
		ans[i] -= max(r / 6 - (l - 1) / 3, 0), ans[i] -= max(r / 15 - (l - 1) / 6, 0);
		q[r].pb({ l, i });
	}
	rep(i, 1, V) {
		for (pii x : g[i]) add(x.X, x.Y);
		for (pii x : q[i]) ans[x.Y] -= qry(x.X);
	}
	rep(i, 1, T) printf("%lld\n", ans[i]);
	return 0;
}
```

---

## 作者：happybob (赞：0)

考虑反面。$\operatorname{lcm}(i,j,k) < i+j+k$ 的情况是比较少的。具体来说，如果这个情况成立，由于 $3k > i+j+k$，有 $\operatorname{lcm}(i,j,k) \leq 2k$。

考虑分类讨论，若 $\operatorname{lcm}(i,j,k)=k$，那么 $i \mid k$ 且 $j \mid k$。这部分的贡献通过扫描线枚举 $l$ 后枚举倍数，维护区间加单点查询即可。根据调和级数分析，复杂度 $O(n \log^2 n)$。

另一部分，若 $\operatorname{lcm}(i,j,k)=2k$。此时限制比较多，需要满足 $i \mid 2k$，$j \mid 2k$，$i+j>k$，$i \nmid k$ 或 $j \nmid k$。限制很多，比较难办。考虑容斥。先去掉后面两个限制，然后减去 $i \mid k$ 且 $j \mid k$ 的贡献。扫描线的时候也可以维护这部分的贡献。所以总复杂度 $O(n \log^2 n)$。

代码：


```cpp
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 4e5 + 5;

int n;
array<ll, N> ans;
struct Query
{
	int r, id;
	Query() = default;
	Query(int r, int id): r(r), id(id){}
};

array<vector<Query>, N> qry;
array<vector<int>, N> s1;

class Fenwick_Tree
{
public:
	array<ll, N> tr;
	void update(int x, ll v)
	{
		while (x < N)
		{
			tr[x] += v, x += x & -x;
		}
	}
	ll query(int x)
	{
		ll res = 0ll;
		while (x)
		{
			res += tr[x];
			x -= x & -x;
		}
		return res;
	}
	void update_range(int l, int r, ll v)
	{
		update(l, v);
		update(r + 1, -v);
	}
}bt;

inline int query2(int x, int l, int r)
{
	if (l > r) return 0;
	return upper_bound(s1[x].begin(), s1[x].end(), r) - lower_bound(s1[x].begin(), s1[x].end(), l);	
} 

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		int l, r;
		cin >> l >> r;
		int len = r - l + 1;
		qry[l].emplace_back(r, i);
		ans[i] = 1ll * len * (len - 1) * (len - 2) / 6;
	}
	for (int i = 1; i < N; i++)
	{
		for (int j = i + i; j < N; j += i)
		{
			s1[j].emplace_back(i);
		}
	}
	const int MAXN = (int)4e5;
	for (int i = MAXN; i >= 1; i--)
	{
		for (int j = 3 * i; j <= MAXN; j += i)
		{
			bt.update_range(j, MAXN, query2(j, i + 1, j - 1)); 
		}
		for (int k = i * 2; k <= MAXN; k += i)
		{
			if (k % 2) continue;
			int nk = k / 2;
			bt.update_range(nk, MAXN, query2(k, max(i + 1, nk - i + 1), nk - 1));
		}
		for (int k = i * 2; k <= MAXN; k += i)
		{
			if (k % 2) continue;
			int nk = k / 2;
			bt.update_range(nk, MAXN, -query2(nk, max(i + 1, nk - i + 1), nk - 1));
		}
		for (auto &x : qry[i])
		{
			ans[x.id] -= bt.query(x.r);
		}
	}
	for (int i = 1; i <= n; i++) cout << ans[i] << "\n";
	return 0;
}
```

---

## 作者：Argon_Cube (赞：0)

非常牛的一题，我们先假设 $l=1$。

考虑两个数的情况，即 $i<j,\operatorname{lcm}(i,j)\geq i+j$。我们考虑算不合法的方案数，即 $\operatorname{lcm}(i,j)<i+j$，可以发现若 $\operatorname{lcm}(i,j)\geq 2j$ 时一定合法，那么自然算 $\operatorname{lcm}(i,j)=i+j\iff i\mid j$。此时若加上 $l$ 的限制可以二维数点做到 $\mathrm O(q+n\log n)$。

推广到三个数，同样考虑容斥，当 $\operatorname{lcm}(i,j,k)\geq 3k$ 时显然合法。那么分两类讨论：$\operatorname{lcm}(i,j,k)=k$、$\operatorname{lcm}(i,j,k)=2k$ 且 $k< i+j$。第一种情况显然就是 $\binom{d(k)-1}{2}$。

对于第二种情况可以发现当 $i<j<k,\operatorname{lcm}(i,j,k)=k$ 时必定 $i,j\leq \frac k2$ 从而 $i+j\leq k$，于是若 $i+j>k$ 则必定有 $\operatorname{lcm}(i,j,k)=2k$，这样我们就不需要考虑 $i,j$ 里面一定要多一个 $2$ 的限制。那么我们发现 $0.5k<j<k$ 并且 $j\mid 2k$，发现存在合法的 $j$ 当且仅当 $3\mid k$，此时 $j=\frac23k$。

现在 $j,k$ 都确定了，自然 $i$ 也很好确定：$i\mid 2k$ 且 $i<j$。注意到此时 $2k$ 的前 $3$ 大因子分别为 $2k,k,\frac23k=j$，也就是说 $i$ 可以取除了这三个因子外的所有 $2k$ 的因子；但是 $i+j>k$ 因此 $i>\frac k3$。也就是说，$i$ 只有最多 $2$ 种取值：$\frac 12k,\frac 25k$。因此，对于一个 $k$ 最多有两对符合 $\operatorname{lcm}(i,j,k)\leq 2k$ 且 $k<i+j$，即 $(\frac12k,\frac23k,k)$ 与 $(\frac 25k,\frac 23k,k)$。

综上，对于一个 $k$ 若 $l=1$ 时它的答案为 $\binom{k-1}{2}-\binom{d(k)-1}{2}-[6\mid k]-[15\mid k]$。

然而事实是，我们不得不面对 $l$ 的限制。显然我们并不想做一个三维的容斥（而且似乎并不可做），那么我们考虑直接硬上。对于一个 $k$，总方案数变为 $\binom{k-l}2$。对于第二种不合法情况显然可以简单变成 $-[6\mid k][k\geq 2l]-[15\mid k][2k\geq5l]$。而第一种不合法情况就很麻烦，我们需要计算 $k$ 大于等于 $l$ 的因子个数（我们记为 $d_{\geq l}(k)$）。

这样答案就是

$$\begin{aligned}
&\sum_{k=l}^r\left(\binom{k-l}{2}-\binom{d_{\geq l}(k)-1}{2}-[6\mid k][k\geq 2l]-[15\mid k][2k\geq5l]\right)\\
=&\binom{r-l+1}{3}-\sum_{k=\color{red}0}^r\binom{d_{\geq l}(k)-1}{2}-\max\left(0,\left\lfloor\frac{r}{6}\right\rfloor-\left\lfloor\frac{2l-1}{6}\right\rfloor\right)-\max\left(0,\left\lfloor\frac{r}{15}\right\rfloor-\left\lfloor\frac{5l-2}{30}\right\rfloor\right)
\end{aligned}$$

预处理出每个数的所有因子即可做到 $\mathrm O(v\log v+Tv\log d(v))=\mathrm O(v(\log v+T\log\log v))$ 的时间复杂度与 $\mathrm O(v\log v)$ 的空间复杂度并通过 Easy Version。第二项加上二维数点优化第二项的求和即可达到 $\mathrm O(v\log^2v+T\log v)$ 的时间复杂度与线性空间并通过 Hard Version，并且我们并不需要将一个询问拆成四个，因为询问等价于做一次原点为 $(0,v)$ 的二维前缀和。

---

