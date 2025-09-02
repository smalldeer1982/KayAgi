# Johnny and Grandmaster

## 题目描述

Johnny has just found the new, great tutorial: "How to become a grandmaster?". The tutorial tells many strange and unexpected for Johnny things, such as you have to be patient or that very important is solving many harder and harder problems.

The boy has found an online judge with tasks divided by topics they cover. He has picked $ p^{k_i} $ problems from $ i $ -th category ( $ p $ is his favorite number). He wants to solve them in two weeks (the patience condition is too hard for Johnny, so for simplicity, he looks only at easy tasks, which can be solved in such a period). Now our future grandmaster has to decide which topics to cover first and which the second week. Help him assign topics in such a way, that workload is balanced.

Formally, given $ n $ numbers $ p^{k_i} $ , the boy wants to divide them into two disjoint sets, minimizing the absolute difference between sums of numbers in each set. Find the minimal absolute difference. Output the result modulo $ 10^{9}+7 $ .

## 说明/提示

You have to minimize the difference, not it's remainder. For example, if the minimum difference is equal to $ 2 $ , but there is also a distribution where the difference is $ 10^9 + 8 $ , then the answer is $ 2 $ , not $ 1 $ .

In the first test case of the example, there're the following numbers: $ 4 $ , $ 8 $ , $ 16 $ , $ 16 $ , and $ 8 $ . We can divide them into such two sets: $ {4, 8, 16} $ and $ {8, 16} $ . Then the difference between the sums of numbers in sets would be $ 4 $ .

## 样例 #1

### 输入

```
4
5 2
2 3 4 4 3
3 1
2 10 1000
4 5
0 1 1 100
1 8
89```

### 输出

```
4
1
146981438
747093407```

# 题解

## 作者：Alex_Wei (赞：12)

> [题面传送门](https://www.luogu.com.cn/problem/CF1361B)。

> 题意简述：将 $n$ 个数 $p^{k_1},p^{k_2},\cdots,p^{k_n}$ 分成两组，记 $a,b$ 分别为这两组数的和，请求出 $|a-b|$ 的最小值，对 $10^9+7$ 取模。

> 注意不是求 $|a-b| \bmod (10^9+7)$ 的最小值。

---

先特判掉 $p=1$ 的情况，显然输出 $n\bmod 2$。

接下来可能比较 tricky，有点难懂。不妨设 $a\geq b$，$df=\dfrac{a-b}{p^{k_i}}$。

将 $k_i$ 从大到小排序后遍历：

1. 当 $i>1$ 且 $df>0$ 时，算出 $c=k_{i-1}-k_i$。否则跳到步骤 $2$。

   接下来将 $df$ 不断乘上 $p$，直到乘了 $c$ 个 $p$ 为止。
   
   若在过程中任意时刻 $df\geq n-i+1$，则意味着 $b+\sum_{j=i}^n p^{k_j}\leq a$。此时就可以贪心并退出遍历。

2. 若 $df>0$，则 $b\gets b+p^{k_i},df\gets df-1$。

   否则 $df$ 一定为 $0$，则 $a\gets a+p^{k_i},df\gets 1$。

最后 $a-b$ 即为 $|a-b|$ 的最小值。

因为要使用快速幂，所以每次询问时间复杂度最坏情况下为 $O(n\log_2 k)$。

除去快速幂，每次询问步骤 $1$ 时间复杂度最坏情况下为 $O(n\log_p 10^6)$（其原因读者可自行思考）。

一些说明以帮助更好理解：

1. 可以将 $df$ 理解为 $b$ 在以 $p^{k_i}$ 为单位下欠 $a$ 的数的个数。因为 $p^{v+1}=p\times p^v$，所以每次缩小单位时 $df$ 都要乘上 $p$。

2. 为什么 $df\geq n-i+1$ 时，$b+\sum_{j=i}^n p^{k_j}\leq a$？

   解释：当 $df\geq n-i+1$ 时，由于 $k$ 是不增的，所以 $b$ 至少要还 $n-i+1$ 个数给 $a$，即此时无论如何 $b$ 都不会再大于 $a$（或者说，$a$ 不需要再添加数进入）。而如果不贪心，$df$ 不但会过大而导致无法存储，还会让单次询问时间复杂度退化成为 $O(10^6)$。

为更好的阅读体验，代码中的板子已省略。

```cpp
const int N=1e6+50;

int n,p,a,b,df,k[N];

void solve(){
	n=read(),p=read(),a=b=df=0; for(int i=1;i<=n;i++)k[i]=read();
	if(p==1){a=n&1; return;}
	sort(k+1,k+n+1),reverse(k+1,k+n+1);
	for(int i=1;i<=n;i++){
		if(i>1&&df) for(int j=k[i-1]-1;j>=k[i];j--)
			if((df*=p)>=(n-i+1)){while(i<=n)b=(b+ksm(p,k[i++]))%mod; return;}
		df?(b=(b+ksm(p,k[i]))%mod,df--):(a=(a+ksm(p,k[i]))%mod,df=1);
	}
}

int main(){
	int t=read();
	while(t--)solve(),cout<<(a-b+mod)%mod<<endl;
	return 0;
}
```

---

## 作者：dChengx (赞：11)

取模这个运算真的很妙

前置芝士：a%mod+b%mod=(a+b)%mod

（没错就是这么~~水~~

方法是跟楼下几位dalao一样，但具体实现有一些优化。

其实我们在发现k[i]但个数为奇数时，就要在<k[i]的值中找到值来补齐。但是这样简单的模拟，我写炸了，可能是因为我太菜了。于是取模就这样上场了。

首先我们肯定要排序k

现在我们假设这两个集合为A和B

（规定sumA表示集合A中所有元素的和

则我们保证sumA>=sumB恒成立就可以了

有了取模这个运算就不需要去一个一个找了，因为取模可以帮我们自动抵消。

假如我们现在有一个k[x]要去消，又正好在后面找到了k[x+i],k[x+i+1],k[x+i+2]...k[x+j]可以抵消（这些值可以相等，话说要是不相等怎么消k[x]），那在取模之中就可以自动抵消了。

若找不到抵消的，那就直接减不就好了。一样的道理。

最后经过pyx大佬的提醒，有可能正好是1e9+7的倍数，这就需要在加一个mod，来判断是不是真‘0’。然后pyx加了个1e9+9，被卡了……

AC代码：
```cpp
#include<bits/stdc++.h>
#define N 1000005
#define ll long long
using namespace std;
const ll mod1=1000000007,mod2=1621836843;
ll n,p,k[N];

ll qkm(ll x,ll y,ll mod){
	ll ans=1;
	for(;y;y>>=1,x=(x*x)%mod)
	    if(y&1)ans=(ans*x)%mod;
	return ans;
}

int main(){
	int T;scanf("%d",&T);
	while(T--){
		scanf("%lld%lld",&n,&p);
		for(ll i=1;i<=n;i++)scanf("%lld",&k[i]);
		if(p==1){
			printf("%lld\n",n&1);
			continue;
		}
		sort(k+1,k+n+1);
		ll sum1=0,sum2=0;
		for(ll i=n;i>=1;i--)
		    if(!sum1&&!sum2){
		    	sum1=qkm(p,k[i],mod1);
		    	sum2=qkm(p,k[i],mod2);
			}
			else{
				sum1=(sum1-qkm(p,k[i],mod1)+mod1)%mod1;
				sum2=(sum2-qkm(p,k[i],mod2)+mod2)%mod2;
			}
		printf("%lld\n",sum1);
	} 
	return 0;
}

```
考场时候就需要注意这些细节了%%%pyx

PS：别忘记开longlong

---

## 作者：Gordon_Song (赞：3)

# first step

首先，我们很容易想到这题的贪心策略：人手规定第一个集合恒大于等于第二个集合。先将 $a$ 从大到小排序，然后看当前两集合差是否为零，如果是就加入第一个集合，否则加入第二个集合。直接实现有点棘手，因为每个数都很大，可能需要一些神奇的东西来维护大小。

# second step

此时，我们必须注意模数。经过猜测和试验，我们发现：直接用一个变量记录差值模数，每次直接减去当前数，然后再模。特殊情况是当变量为**真零**的时候，进行加。

接下来，我将给出一个证明：

之所以我们在怀疑这样做的正确性，是因为有可能有 $\sum_{i=j+1 \dots k}{a_i} \leq p^{a_j} \leq \sum_{i=j+1 \dots k+1}{a_i}$。
如果把每个 $a$ 值都当作一个 $p$ 进制数，那么这些数都是形如 $(1000 \dots 0)_p$ 的形式。所以 $\sum_{i=j+1 \dots k}{a_i}$ 即是一个小于 $1000 \dots 0$ 的  $p$ 进制数。又因为 $\sum_{i=j+1 \dots k+1}{a_i}$ 大于 $p^{a_j}$ ，则易得 $a_{k+1}$ 这个位置必须要大于 $a_{k}$ ，矛盾。


# 注意

需要再用另一个模数来维护是否是真零。

# 代码

```cpp
int n,p;
int k[1000001];
const int mod1=1e9+7,mod2=1420101021;
ll qui(rll di,rll mi,rll mod){
	rll res=1;
	while(mi){
		if(mi&1){
			res*=di;
			res%=mod; 
		}
		di*=di;di%=mod;
		mi>>=1;
	}
	return res;
}
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&p);
		for(int i=1;i<=n;i++){
			scanf("%d",&k[i]); 
		}
		sort(k+1,k+1+n);
		long long sum1=0,sum2=0;
		for(int i=n;i>=1;i--){
			if(sum1==0&&sum2==0){
				sum1+=qui(p,k[i],mod1);
				sum2+=qui(p,k[i],mod2);
			}else{
				(sum1=sum1-qui(p,k[i],mod1)+mod1)%=mod1;
				(sum2=sum2-qui(p,k[i],mod2)+mod2)%=mod2;
			}
		}
		printf("%lld\n",sum1);
	}
}

```


---

## 作者：duyi (赞：3)



## CF1361B Johnny and Grandmaster

首先特判$p=1$的情况：$n$为奇数答案就是$1$，否则就是$0$。

当$p>2$时，每$p$个$p^{k-1}$可以换一个$p^{k}$。先记录下每个$k$值的出现次数。然后**从大到小**扫描$k$值。对于当前$k$值，记它在输入序列里的出现次数为$\text{cnt}$。假设在此之前，两个集合的和是相同的（显然初始时就是这样）。那么当前会三种情况：

1. $\text{cnt}$为偶数，那么我们给两个集合的和各加上$\frac{\text{cnt}}{2}\cdot p^k$。此时两个集合的和仍然是相同的，直接考虑下一个$k$。
2. $\text{cnt}$为奇数。先给一个集合加上$\lceil\frac{\text{cnt}}{2}\rceil\cdot p^k$（称为大集合），给另一个集合加上$\lfloor\frac{\text{cnt}}{2}\rfloor\cdot p^k$（称为小集合）。现在两个集合和相差了$p^k$。我们尝试从$<k$的值里拿一些上来，把这部分差值补齐。有一个非常重要的发现是：想要补齐这个差值，最多向下找$\log_pn$个值，所以可以暴力枚举$(k-1),(k-2),\dots (k-\log_pn)$的出现次数，看能不能补齐。如果能补齐，那么现在两个集合的和还是相同的，继续考虑下一个$k$。
3. 如果第2步中，我们无法补齐两个集合的差，那说明剩下所有数的和加起来都不到$p^k$，我们直接把剩下的所有数全部加入“小集合”里，然后输出答案（两集合之差）。

时间复杂度$O(n\log_2n+n\log_p n)$。

参考代码：

```cpp
//problem:B
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mk make_pair
#define lob lower_bound
#define upb upper_bound
#define fi first
#define se second
#define SZ(x) ((int)(x).size())

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;

const int MOD=1e9+7;
inline int mod1(int x){return x<MOD?x:x-MOD;}
inline int mod2(int x){return x<0?x+MOD:x;}
inline void add(int& x,int y){x=mod1(x+y);}
inline void sub(int& x,int y){x=mod2(x-y);}
inline int pow_mod(int x,int i){int y=1;while(i){if(i&1)y=(ll)y*x%MOD;x=(ll)x*x%MOD;i>>=1;}return y;}

const int MAXN=1e6;
int n,p,a[MAXN+5];

int main() {
	int T;cin>>T;while(T--){
		cin>>n>>p;
		map<int,int>mp;
		for(int i=1;i<=n;++i){
			cin>>a[i];
			mp[-a[i]]++;
		}
		if(p==1){
			cout<<(n&1)<<endl;
			continue;
		}
		int summx=0,summn=0;
		bool flag=0;
		for(map<int,int>::iterator it=mp.begin();it!=mp.end();++it){
			int k=-(it->fi);
			int cnt=(it->se);
			//cout<<k<<" "<<cnt<<endl;
			int v=pow_mod(p,k);
			if(flag){
				add(summn,(ll)v*cnt%MOD);
				continue;
			}
			if(cnt&1){
				ll need=1;
				for(int kk=k-1;kk>=0;--kk){
					need*=p;
					if(need>MAXN)break;
					if(!mp.count(-kk))continue;
					if(mp[-kk]>=need){
						need=0;
						break;
					}
					need-=mp[-kk];
				}
				if(!need){
					need=1;
					for(int kk=k-1;kk>=0;--kk){
						need*=p;
						if(need>MAXN)break;
						if(!mp.count(-kk))continue;
						if(mp[-kk]>=need){
							mp[-kk]-=need;
							need=0;
							break;
						}
						need-=mp[-kk];
						mp[-kk]=0;
					}
					add(summx,(ll)v*(cnt/2+1)%MOD);
					add(summn,(ll)v*(cnt/2+1)%MOD);
				}
				else{
					flag=1;
					add(summx,(ll)v*(cnt/2+1)%MOD);
					add(summn,(ll)v*(cnt/2)%MOD);
				}
			}
			else{
				add(summx,(ll)v*(cnt/2)%MOD);
				add(summn,(ll)v*(cnt/2)%MOD);
			}
		}
		cout<<mod2(summx-summn)<<endl;
	}
	return 0;
}
```

---

## 作者：bsdsdb (赞：1)

题意：给定 $p,\{k_n\}$，定义可重集 $A:=\{p^{k_i}\}$，要将 $A$ 分割成 $B$ 和 $C$，最小化 $\left|\sum B-\sum C\right|$。

~~提示：合成大西瓜~~

$p=1$ 答案就是 $n\bmod 2$，下文讨论 $p>1$。策略是先不停地用较小的数「合成」较大的数（如果有多种取法取用的数最大的，因为小的后面更自由），两边抵消，最后合成不出来了就最大数减其他数。具体到算法实现，可以把 $\sum A$ 写成一个 $p$ 进制数 $s$，然后每次取 $A$ 的最大值 $m$，如果 $s-m\ge m$（这一步可以用维护 $s$ 最高位实现）说明能合成，就每次取 $A\backslash\{m\}$ 的最大值去贡献。反之，如果不能合成，就直接用最大值减其他作为答案即可。复杂度 $\mathcal O(n(\log n+\log p+\log\max k))$，分析在代码注释。

```cpp
#include <bits/stdc++.h>
#pragma GCC optimize(1,2,3,"Ofast","inline")
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
typedef __int128 ll;
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
const vector<ll> millerrabin = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
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

const ll mod = 1000000007, MAXN = 1e6 + 5;

ll n, p, a;
prque<ll, vector<ll>, less<ll> > s;
map<ll, ll> cnt, sumdig;

ll wefoij = 0;

ll qpow(ll x, ll y) {
    ++wefoij;
	if (!y) {
		return 1;
	} else if (y & 1) {
		return x * qpow(x, y ^ 1) % mod;
	} else {
		return qpow(x * x % mod, y >> 1);
	}
}
ll lg(ll x, ll y) {
	if (y < x) {
		return 0;
	}
	return 1 + lg(y, x / y);
}

void init() {
    while (!s.empty()) {
        s.pop();
    }
    sumdig.clear();
	cnt.clear();
}
int mian() {
	read(n), read(p);
	for (ll i = 1; i <= n; ++i) {
		read(a);
		s.emp(a);
		++cnt[a];
	}
	if (p == 1) {
		write(n % 2), enter();
		return 0;
	}
    for (auto i : cnt) { // iterating: nlogn
        sumdig[i.first] += i.second;
        ll pos = i.first;
        while (sumdig[pos] >= p) { // add: logp(sumdig[pos]/=p every time), n(logn+logp) overall because sum of sumdig[i.first] is n
            sumdig[pos + 1] += sumdig[pos] / p;
            sumdig[pos] %= p;
            ++pos;
        }
    }
    auto msd = prev(sumdig.end());
    while (!s.empty()) {
        ll mx = s.top();
        s.pop();
        if (!s.empty() && s.top() == mx) {
            s.pop();
            sumdig[mx] -= 2;
            ll pos = mx;
            while (sumdig[pos] < 0) {
                sumdig[pos] += p;
                --sumdig[pos + 1];
                ++pos;
            }
            continue;
        }
        while (msd->second == 0) {
            msd = prev(msd);
        }
        if (msd->first == mx && msd->second == 1) {
            break;
        }
        sumdig[mx] -= 2;
        pll tg = mkp(mx, 1);
        while (!s.empty() && tg.second != 0) {
            ll h = s.top(); // nlogn
            s.pop();
            pll tgc = tg;
            tgc.second *= qpow(p, tg.first - h); // nlogk
            tgc.first = h;
            --tgc.second;
            tg = tgc;
        }
        ll pos = mx;
        while (sumdig[pos] < 0) { // at most n(logn+logp), same as above
            sumdig[pos] += p;
            --sumdig[pos + 1];
            ++pos;
        }
    }
    // overall time complexity: n(logn+logk+logp)
    auto msdd = prev(sumdig.end());
    while (msdd->second == 0 && msdd != sumdig.begin()) {
        msdd = prev(msdd);
    }
    ll ans = (msdd->second << 1) % mod * qpow(p, msdd->first) % mod;
    for (pll i : sumdig) {
        (ans -= i.second * qpow(p, i.first) % mod - mod) %= mod;
    }
    write(ans), enter();
    cerr << wefoij << endl;
	return 0;
}

int main() {
	ll T;
	read(T);
	while (T--) {
        // cerr << "----------------" << endl;
		init();
		mian();
	}
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
```

---

## 作者：liuli688 (赞：0)

### 思路
首先，先想一下这题暴力怎么做。

由于保证所有数是 $p$ 的倍数，所以可以想到贪心策略：从大到小排序后扫描整个数组，每次遇到一个数就往总和小的集合里放。这样有点麻烦，可以加上限制：规定第一个集合大于第二个集合，如果两个集合和一样则往第一个集合里加当前数，否则往第二个集合里加。

那么如何判断两个集合是否相等呢？可以用一个变量记录差值，每次取模。但是，如果变量的值是模数的倍数也会使变量值为 $0$。因此，可以用双模数降低出现假 $0$ 的概率。

同学 [ZMQ_Ink6556](https://www.luogu.com.cn/user/1125291) [告诉](https://www.luogu.com.cn/discuss/997875)我模数会被卡，亲测 $10 ^ 9 + 7$、$998244353$ 会被卡。因此换一个小众的模数就行了。
### 代码
```cpp
#include <cstdio>
#include <algorithm>
using ll = long long;

template <class _Tp = int>
_Tp read() {
    char c; _Tp x = 0; short f = 1;
    for (c = getchar(); c == ' ' or c == '\n'; c = getchar());
    for (c = (c == '-' ? f = -f, getchar() : c); c != ' ' and c != '\n'; c = getchar())
        x = (x << 1) + (x << 3) + c - 48;
    return x * f;
}

template <class _Tp>
_Tp qpow(_Tp a, _Tp b, _Tp p) {
	ll ans = 1, base = a;
    for (; b; b >>= 1) {
		if (b & 1)
			ans = (ans * base) % p;
		base = (base * base) % p;
	}
	return ans;
}

constexpr int N = 1e6 + 1, MOD1 = 1e9 + 7, MOD2 = 1e9 + 21;
int T, n, p, k[N + 1];
ll res1, res2;

signed main()
{
    for (T = read(); T--; )
    {
        n = read(); p = read();
       	for (int i = 1; i <= n; ++i)
            k[i] = read();
        std::sort(k + 1, k + n + 1);
        res1 = res2 = 0;
        for (int i = n; i; --i)
            if (res1 == 0 and res2 == 0)
            {
                res1 = (res1 + qpow(p, k[i], MOD1)) % MOD1;
                res2 = (res2 + qpow(p, k[i], MOD2)) % MOD2;
            }
            else
            {
                res1 = (res1 + MOD1 - qpow(p, k[i], MOD1)) % MOD1;
                res2 = (res2 + MOD2 - qpow(p, k[i], MOD2)) % MOD2;
            }
        printf("%d\n", res1);
    }
	return 0;
}
```

---

## 作者：Michael1234 (赞：0)

本题可以使用数学的思想：

我们将序列按倒序排序，用两个栈维护两堆数，第一堆的和恒大于等于第二堆。

对于每个数，如果当前第一堆中没有数，说明两堆里的数的和相等，我们把当前数扔进第一堆。

否则，第二堆数的和小于第一堆，那我们把当前数直接扔进第二堆。因为我们的序列是单调递减的，所以第二堆加上这个数后也不可能一下子超过第一堆的和。

每轮操作结束后，我们考虑把没对可以合成的后 $p$ 个数合成并且把两堆相同的部分消除。

最后加上第一堆的每个数，再减去第二堆的每个数。注意，在减去第二堆时，每次取模需先加上一个模数，避免出现负数，为了快速删除并能够访问每一位，最好手写人工栈。

## CODE
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5,mod=1e9+7;
int t,n,p,val,ans,k[N];
bool f;
inline int ksm(int a,int b)
{
	int res=1;
	for(;b;b>>=1)
	{
		if(b&1)
		{
			res*=a;
			res%=mod;
		}
		a*=a;
		a%=mod;
	}
	return res;
}
struct Stack
{
	int sz,a[N];
	inline void clear(){sz=0;return;}
	inline int size(){return sz;}
	inline void pb(int x){a[++sz]=x;return;}
	inline void pop(int p){sz-=p;return;}
	inline int& operator [](int x){return a[x];}
}x,y;
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	for(cin>>t;t;t--)
	{
		ans=0;
		x.clear();
		y.clear();
		cin>>n>>p;
		for(int i=1;i<=n;i++)
		{
			cin>>k[i];
		}
		if(p==1)
		{//特判
			cout<<(n&1)<<"\n";
			continue;
		}
		sort(k+1,k+n+1);
		for(int i=n;i>=1;i--)//倒序访问也是一样的
		{
			if(x.size())
			{
				y.pb(k[i]);
				while(y.size()>=p&&y[y.size()]==y[y.size()-p+1])
				{//合成p个数
					val=y[y.size()];
					y.pop(p);
					y.pb(val+1);
				}
				while(x.size()&&y.size()&&x[x.size()]==y[y.size()])
				{//消除相同
					x.pop(1);
					y.pop(1);
				}
			}
			else
			{
				x.pb(k[i]);
			}
		}
		while(x.size())
		{//加
			ans+=ksm(p,x[x.size()]);
			ans%=mod;
			x.pop(1);
		}
		while(y.size())
		{//减
			ans-=ksm(p,y[y.size()]);
			ans+=mod;
			ans%=mod;
			y.pop(1);
		}
		cout<<ans<<"\n";
	}
	exit(0); 
}
```

---

## 作者：氧少Kevin (赞：0)

# CF1361B - Johnny and Grandmaster
- https://www.luogu.com.cn/problem/CF1361B
- 幂运算的性质、贪心

## 题意
给出一个长度为 $n(n\leq 10^6)$ 的序列和一个正整数 $p(1\leq p\leq 10^6)$，序列 $a=[a_1,a_2,\dots a_n](0\leq a_i\leq 10^6)$ 实际意义是给出 $n$ 个数字 $[p^{a_1},p^{a_2},\dots p^{a_n}]$。

现要求将这 $n$ 个数字划分为两个集合，每个数字必须属于某一个集合。

现在需要最小化两个集合元素加和的差值，求差值对 $10^9+7$ 取模的结果。（注意：是最小化原来元素加和的差值，而不是最小化取模后的差值。）

## 思路

将所有元素降序排序。

第 $1$ 个元素是 $p^{a_1}$，将其放在 $A$ 集合。

接下来，需要向后寻找元素放在 $B$ 集合，用于减少差值。

寻找的过程有两种情况：
- 存在位置 $2\leq k\leq n$，满足 $p^{a_1}=\sum_{i=2}^{k} p^{a_i}$。
- 不存在位置 $2\leq k\leq n$，满足 $p^{a_1}=\sum_{i=2}^{k} p^{a_i}$，并且 $p^{a_1}<\sum_{i=2}^{n} p^{a_i}$。

>**为什么没有这种情况？**
>- 存在位置 $k$，满足 $p^{a_1}>\sum_{i=2}^{k} p^{a_i}$ 但 $p^{a_1}<\sum_{i=2}^{k+1} p^{a_i}$。
>
>假设当前在位置 $q$，两集合差值为 $d$，那么一定有 $d\geq p^{a_q}$ 且 $d \mod p^{a_q}=0$。
>
> 因此，将两集合差值减小 $p^{a_q}$ 后，一定有 $d\geq 0$。

分别维护 $A,B$ 两个集合的元素加和，降序排序后遍历所有元素。对于当前元素，哪个集合的加和较小，就将当前元素加到哪个集合中。

降序排序后，$A,B$ 两个集合的差值呈现如下变化特点：
- $A,B$ 的差值不断逼近 $0$。
- $A,B$ 的差值在等于 $0$ 后，突然增大，后又逼近 $0$。突增的增加量一次比一次小。

基于贪心的思想，$A,B$ 的差值在等于 $0$ 后，突然增大，接下来使用后面的元素弥补增加量。

#### 具体实现
假设 $A$ 的加和 $>$ $B$ 的加和，维护差值 $d$。

一开始将最大的 $p^{a_1}$ 放入集合 $A$（此时 $d=p^{a_1}$），再将第二个元素放入 $B$ 中（$d:=d-p^{a_2}$）。

当进行到某一个元素时发现 $d=0$ 时，将当前元素放入 $A$（$d:=p^{a_i}$）即可。


---

## 作者：快斗游鹿 (赞：0)

## 思路

考虑贪心。先将 $k$ 从大到小排个序。到第 $i$ 个数时，如果这时两个集合里的数和相等，就把这个数扔到其中一个集合里，我们称为第一个集合，以后的数都扔到另一个集合里，我们称为第二个集合，直到两个集合里的数和再次相等为止，重复上述操作。

为什么这样第一个集合中的数和一定会大于等于第二个集合中的数和呢？因为 $p^k=p\times p^{k-1}$，而 $k$ 又已经降序排序了，所以第二个集合中的数和一定不会大于第一个集合中的数和。

但是本题中 $p^k$ 会很大，需要取模。这样就会出现一个数是 $10^9+7$ 的倍数，导致被我们当做 $0$ 的情况。怎么解决呢？可以采用双模数的方式，这样可以大大降低出现假的 $0$ 的概率。

## 代码

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int moda=1e9+7;
const int modb=1e6+5;
const int N=1e6+5;
int T,n,p,a[N],suma,sumb;
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int qp(int x,int y,int mod){
	int ans=1;
	while(y){
		if(y&1)ans*=x,ans%=mod;
		x*=x;x%=mod;
		y>>=1;
	}
	return ans;
}
signed main(){
	T=read();
	while(T--){
		n=read();p=read();suma=0;sumb=0;
		for(int i=1;i<=n;i++)a[i]=read();
		sort(a+1,a+1+n);
		for(int i=n;i>=1;i--){
			if(!suma&&!sumb){
				suma=qp(p,a[i],moda);
				sumb=qp(p,a[i],modb);
			}
			else{
				suma-=qp(p,a[i],moda);suma=(suma%moda+moda)%moda;
				sumb-=qp(p,a[i],modb);sumb=(sumb%modb+modb)%modb;
			}
		}
		printf("%lld\n",suma);
	}
	return 0;
}

```


---

## 作者：Z1qqurat (赞：0)

difficulty: $4$，比较新颖。

1. Observation: 数都是 $p^k$ 的形式，那么如果 $k_i$ 互不相同，不可能用别的 $p^{k'}$ 把某个特定 $p^k$ 凑出来。就算有相同的 $k_i$ 也很难凑出来。
2. Induction: 自然地想到将相同的 $k$ 放到一起并且倒序处理（这样贪心地从大往小处理可以使得差距最小），原则上尽量均分，但是如果某个 $k$ 出现了奇数次，此时就会有两边（记为 $l,r$）相差 $p^k$ 的问题。
3. Observation*: 差的次数如果不能补全就往下推，$n\le 10^6$，如果某次两边差的次数已经大于 $10^6$，那之后怎么也补不齐了，这时候就可以放弃一碗水端平，后面的都补给小的那一边；否则能补齐就补齐，这样是 $\mathcal{O}(n\log n)$ 的，$\log n$ 来自快速幂。

这题的贪心思想看起来在于一开始的降序处理以及后来的补齐方式（均分）上面，可我认为这题优美的地方在于第二个 Observation 发现的“到了 $10^6$ 就补不齐，可以直接全给小的那一边了”，这是完美利用了数据范围和 $p^k$ 性质的，其中也用到了货币找零的那种贪心思想，这才是我认为这题有价值的点。对题目条件和性质完全的理解和利用才是优美做法该有的样子。

看到题解区也有一些利用取模性质的简单做法（？）但是没太看懂，不过不太重要吧。

[Submission.](https://codeforces.com/contest/1361/submission/267815907)

---

## 作者：Ryo_Yamada (赞：0)

目前最优解写法。

首先将 $k_i$ 降序排列，并将相同的 $k_i$ 合并。由于每个式子都是形如 $p^{k_i}$ 的形式，即底数相同，可以考虑变成 $p$ 进制，发现对于任意 $c_1,\, \ldots ,\, c_{i+1}$ 和 $a_0 < a_1 < a_2 \ldots < a_{i+1}$，满足 $c_{i+1} \times p^{a_{i+1}} \ge \sum\limits_{j=1}^i c_{j} \times p_{a_j}$ 时，$c_{i+1} \times p^{a_{i+1}} - \sum\limits_{j=1}^i c_{j} \times p_{a_j}$ 一定被 $p^{a_0}$ 整除。

我们可以考虑记录 $s1,\,s2$ 表示两堆的和，使任意时刻 $s1 < s2$。
考虑 $k_i$ 降序排序时贪心用较大的 $k$ 补足 $s2-s1$。$\text{now}$ 当前到 $i$，且 $p^{k_i} \times \text{now} = s2 - s1$。由于是降序排序，如果 $\text{now} > n$ 那么后面的 $k$ 都一定分配到 $s1$。否则先使 $s1=s2$，再用剩下的 $k_i$ 分配给 $s1,s2$，注意满足 $s1<s2$。

$\text{Code}$：

```cpp
def(N, int, 1e6 + 5)
def(p, int, 1e9 + 7)

int n, m;
int k[N];

int main() {
	int t; qread(t);
	W(t) {
		qread(n, m);
		rep(i, 1, n) qread(k[i]);
		sort(k + 1, k + n + 1, greater<int>());
		ll nw = 0;
		ll s1 = 0, s2 = 0;
		rep(i, 1, n) {
			if(nw && m != 1 && i != 1) {
				int nwm = k[i - 1] - k[i];
				rep(j, 1, nwm) {
					nw *= m;
					if(nw > n) {
						rep(l, i, n) s1 = (s1 + qpow(k[l], m, p)) % p;
						goto End;
					}
				}
			}
			int cn = 0, j = i;
			while(j <= n && k[i] == k[j]) ++j, ++cn;
			int ps = min(nw, (ll)cn); nw -= ps;
			if(cn > ps) {
				cn -= ps;
				int c1 = cn >> 1, c2 = cn - c1;
				if(c1 != c2) nw = 1;
				s1 = qpow(k[i], m, p) * c1 % p;
				s2 = qpow(k[i], m, p) * c2 % p;
			}
			else s1 = (s1 + qpow(k[i], m, p) * cn % p) % p;
			i = j - 1;
			// cout << s1 << ' ' << s2 << endl;
		}
		End:;
		printf("%lld\n", (s2 - s1 + p) % p);
	}
	return 0;
}
```


---

## 作者：wwldx (赞：0)

这题的大概意思就是t组数据，每组给你一个n和p，有n个数字，每个数字代表是p^k ,问把这些数字分成2组，第一组所有和为a,第二组和为b,求|a-b|最小值，这个值可能很大，对1000000007取余

首先看到这题，我就想起了前段时间某场div2的A，[传送门](https://www.luogu.com.cn/problem/CF1348A)，那题范围比这题小很多，相当于限制了t为1，p为2，并且不会超出int范围，n个数字也不会重复，但是基本思想是可以借鉴的

（具体可以结合代码）

假如这n个数字，有一个足够大的数字，就算他一个数字一组，其他所有n-1个数字加起来都没他大，那结果肯定是他减去其他所有的数字

那怎么判断这个数字是否足够大呢？我们都知道p^n相当于n
个p^(n-1)相乘，所以我们直接把这n个数字从大到小排序一次，取第一位为最大值，记录当前的阶数ans,然后判断第二位，第二位肯定是小于等于第一位的，所以分开判断，

假如小于ans，这个时候再分，第三位，第四位一直到第n位，肯定都是小于等于第二位的，所以后面的数字最大累加也就是(n-1)个p^(第二位),所以只要第一位换算成x * p^(n-1)的时候，x大于等于n-1即可，而换算就简单了，p^n变成p^(n-1)的时候，x乘以p就行。假如x小于n-1，就代表第一个值还不够大，那暂时还不能直接减去后面所有的，暂时先减掉第二大的。然后从第三位开始，这个时候第三位又是最大值了，重复进行上述操作

等于ans的话，直接减去第二位，因为第一位和第二位相等，消去了
```cpp
#include <bits/stdc++.h>
#define rep(i,a,n) for(int i=a;i<n;i++)
typedef long long ll;
using namespace std;
const int maxn = 1000005;
const ll mod = 1000000007;
int cmp(int a,int b)
{
	return a>b;
}
long long qpow(long long m,long long n,long long mod)
{//快速幂 
	long long temp;
	if (n==0) return 1;
	temp=qpow(m,n>>1,mod);
	if (n%2==0) return temp*temp%mod;
		else return m*temp%mod*temp%mod;
}
ll ans,sum,num,p,n;
int T;
ll a[maxn];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	//此题不要用cin和cout读入输出，会T 
	scanf("%d",&T);
	while(T--)
	{
		bool flag=false;
		scanf("%lld %lld",&n,&p);
		rep(i,1,n+1)
		{
			scanf("%lld",&a[i]);
		}
		if(p==1)
		{//假如p是1，1不管多少次幂都是1，所以n是奇数，sum就是1，n是偶数，sum就是0 
			printf("%lld\n",n&1);
			continue;
		}
		sort(a+1,a+n+1,cmp);//从大到小排序 
		sum=0,num=0;//sum总和，num表示当前存储了几个未处理的数字 
		rep(i,1,n+1)
		{
			if(!num)
			{//num为0了，之前的数字全部处理光了，相当于重新开始了 
				num++;
				ans=a[i];//ans存储当前待处理的数的幂次 
				(sum+=qpow(p,a[i],mod))%=mod;	
			}
			else
			{
				while(ans>a[i])//待处理的数字的幂次比后面的幂次大 
				{
					ans--;//幂次降低一 
					num*=p;//数量乘以p   p * (p ^ n-1) = p ^ n 
					if(num>=n-i+1)//num比剩余的加起来都多或者不小于 
					{//直接开减,把当前数字后面的全给减去 
						rep(j,i+1,n+1)
						{
							(sum-=qpow(p,a[j],mod)-mod)%=mod;
						}
						flag=true;//标记改为true,方便待会直接退出，防止冗余处理 
						break;
					}
				}//当待处理的数字的幂次等于后面的幂次了 
				num--;//因为幂次相同，消去一个 
				(sum-=qpow(p,a[i],mod)-mod)%=mod; 
			}
			if(flag)//退出 
			break;
		}
		printf("%lld\n",sum);
	}
	return 0;
}
```



---

