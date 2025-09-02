# Maximum Sine

## 题目描述

给定整数 $a$、$b$、$p$ 和 $q$。定义 $f(x) = \text{abs}(\sin(\frac{p}{q} \pi x))$。

请在 $a \le x \le b$ 的范围内，找到使 $f(x)$ 最大的最小整数 $x$。

## 说明/提示

在第一个测试点中，$f(0) = 0$，$f(1) = f(2) \approx 0.866$，$f(3) = 0$。

在第二个测试点中，$f(55) \approx 0.999969$，这是所有可能值中的最大值。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2
0 3 1 3
17 86 389 995
```

### 输出

```
1
55
```

# 题解

## 作者：litble (赞：9)

学过三角函数的同学都知道，$|\sin x|$的周期为$\pi$，每个周期$[k \pi, (k+1) pi]$（$k$为整数）内的最大值在$k \pi+\frac{1}{2}$处取到。

也就是说，$\frac{px}{q}=\frac{2px}{2q}$的小数部分要尽可能地接近$\frac{1}{2}=\frac{q}{2q}$。

也就是说，$2px \bmod 2q$要尽可能接近$q$。

利用一种类似BSGS的，一边走大步一边走小步的思路，将$[l,r]$区间分成$\sqrt{r-l+1}$块（最后一块比其他块小，暴力处理它）。先将每个块的第一个元素$x$的$2px \bmod 2q$记录下来，排序。

接着，将记录下来的元素一次一次地集体变为$2p(x+1) \bmod 2q$。

由于每一次改变，相当于将所有记录下来的元素都加上$2p$这个定值，所以相当于是将原来排好序的序列旋转一下，于是可以不用真的将这些元素都加上定值，而是将这个定值记录下来，利用二分找到所有元素加上这个定值后，最接近$q$的元素。

复杂度$O(\sqrt{n}\log \sqrt{n})$

~~全靠CF评测机快续命~~

```cpp
#include<bits/stdc++.h>
using namespace std;
#define RI register int
inline int read() {
	int q=0;char ch=' ';
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') q=q*10+ch-'0',ch=getchar();
	return q;
}
const int N=100005;
typedef long long LL;
int T;LL l,r,p,q;
struct node{LL v,id;}a[N];
bool operator < (node A,node B) {return A.v==B.v?A.id<B.id:A.v<B.v;}

int main()
{
	scanf("%d",&T);
	while(T--) {
		scanf("%lld%lld%lld%lld",&l,&r,&p,&q);
		int sqn=sqrt(r-l+1),kjs=0,js;
		LL ans1=LLONG_MAX,ans2=-1;
		for(LL i=l;i<=r;i+=sqn) {
			if(i+sqn-1<=r) a[++kjs]=(node){i*(p+p)%(q+q),i};
			else {
				for(RI j=i;j<=r;++j) {
					LL val=abs(j*(p+p)%(q+q)-q);
					if(val<ans1||(val==ans1&&j<ans2)) ans1=val,ans2=j;
				}
			}
		}
		sort(a+1,a+1+kjs);
		js=1;for(RI i=2;i<=kjs;++i) if(a[i].v!=a[js].v) a[++js]=a[i];
		for(LL i=0,now=0;i<sqn;++i,now=(now+(p+p))%(q+q)) {
			LL pos=(q-now+q+q)%(q+q);
			int k=lower_bound(a+1,a+1+js,(node){pos,-1})-a;
			if(k<=js) {
				if(a[k].v-pos<ans1||(a[k].v-pos==ans1&&a[k].id+i<ans2))
					ans1=a[k].v-pos,ans2=a[k].id+i;
			}
			else {
				if(q+q-(pos-a[1].v)<ans1||(q+q-(pos-a[1].v)==ans1&&a[1].id+i<ans2))
					ans1=q+q-(pos-a[1].v),ans2=a[1].id+i;
			}
			--k;
			if(k>=1) {
				if(pos-a[k].v<ans1||(pos-a[k].v==ans1&&a[k].id+i<ans2))
					ans1=pos-a[k].v,ans2=a[k].id+i;
			}
			else {
				if(q+q-(a[js].v-pos)<ans1||(q+q-(a[js].v-pos)==ans1&&a[js].id+i<ans2))
					ans1=q+q-(a[js].v-pos),ans2=a[js].id+i;
			}
		}
		printf("%lld\n",ans2);
	}
	return 0;
}
```

---

## 作者：pythoner713 (赞：7)

$$\text{求 } [a,b] \text{ 中使得 } f(x)=\left|\sin\left(\frac{p}{q}x\pi\right)\right| \text{最大的整数 }x$$

---

$\sin(x)$ 的**最值**在 $\left(k+\dfrac{1}{2}\right)\pi, k\in\mathbb{Z}$ 处取到。

既然如此，我们便要让 $px/q$ 最接近于一个整数加上二分之一。不严谨地说，我们需要让：

$$
\begin{aligned}
\frac{px}{q} &\approx k+\frac{1}{2} \\
&\Downarrow \\
\frac{2px}{q} &\approx 2k+1 \\
&\Downarrow \\
\frac{2px+q}{q} &\approx 2k \\
&\Downarrow \\
\frac{2px+q}{2q} &\approx k \\
\end{aligned}
$$

另外，如果分数 $\dfrac{p}{q}$ 越接近一个整数，则 $p  \bmod q$ 的值则越接近于 $0$ 或 $q$。

因此，我们所求便是使：

$$g(x)=(2px+q)\bmod 2q\quad (x\in[a,b])$$

最小/最大的 $x$ 值。

---

我们不妨先思考一个更一般的问题。求：

$$\min\{(Ax+B)\bmod C\}\quad x\in[l,r]$$

可以利用分块（或BSGS）的思想，步骤如下：

1. 先将区间 $[l,r]$ 分为长度为 $T=\sqrt{r-l+1}$ 的若干块。

2. 预处理出当 $x\in[0,T)$ 时，所有 $Ax\bmod C$ 的值（并排序），这些相当于我们的 baby step。

3. 接着开始以 $T$ 为步长，开始迈大步。形式化地，既然每个 $x$ 都可以表示成 $mT+n\;(n\in[0,T))$ 的形式，可以 $l,l+T,l+2T,\cdots,r-T$ 的顺序枚举 $x$ 的大块部分。设当前枚举到的值为 $i$，则原问题变为求 $(Ai+An+B)\bmod C\;(n\in[0,T))$ 最小的 $n$。

4. 将上述问题移项，即是求使得 $An\bmod C$ 恰好大于 $C-((Ai+B)\bmod C)$ 的最小的 $n$。由于我们第一步已经预处理出了所有 $An \bmod C$ 并排好了序，只需要二分出 $n$ 的位置并更新答案即可。

求 $\max$ 的做法是一样的，顺带着更新一下即可。

---

好了，既然我们已经求得使

$$g(x)=(2px+q)\bmod 2q\quad (x\in[a,b])$$

最小的整数 $x_1$ 和使它最大的整数 $x_2$ 了，那么该选择哪个输出呢？我们只需要比较 $g(x_1)$ 与 $2q-g(x_2)$ 的大小，哪个更小，说明哪个 $x$ 值让 $\dfrac{2px+q}{2q}$ 更接近整数，于是就输出哪个 $x$ 值。两者相同便输出较小的 $x$。

>最后提一个小细节，$f(x)$ 肯定是会循环的，循环节是 $d=\dfrac{\text{lcm}(2p,2q)}{2p}=\dfrac{q}{\gcd(p,q)}$。于是，当我们发现求出的 $x-l\ge d$ 时，说明我们跳过了至少一个循环节，前面还有 $x$ 更小的解。
令 $x=l+(x-l)\bmod d$ 即可。

---

```cpp
#include<bits/stdc++.h>
#define update {\
    now = (bbs[idx].mod + i * A + B) % C;\
    if(now < minn) minn = now, ans1 = i + bbs[idx].x;\
    if(now > maxx) maxx = now, ans2 = i + bbs[idx].x;\
}
#define int long long
using namespace std;
 
int _, a, b, p, q;
struct babystep{
    int x, mod;
    bool operator < (const babystep &tmp) const{
        return mod < tmp.mod || (mod == tmp.mod && x < tmp.x);
    }
}bbs[50000];

int solve(int A, int B, int C, int l, int r){
    int t = sqrt(r - l + 1), ans1, ans2, minn = 2e15, maxx = -1;
    for(int i = 0; i < t; i++) bbs[i] = (babystep){i, i * A % C};
    sort(bbs, bbs + t);
    for(int i = l; i <= r - t; i += t){
        int idx = lower_bound(bbs, bbs + t, (babystep){0, C - (i * A + B) % C}) - bbs, now;
        if(idx >= t) idx--; update
        if(idx) idx--;      update
        idx = (idx + 2) % t;update // 二分到附近的值都试一下
    }
    int idx = 49999, now, tmp = q / __gcd(p, q);
    for(int i = r; i >= max(l, r - t * 2); i--) update  // 最后两个块暴力更新
    ans1 = l + (ans1 - l) % tmp, ans2 = l + (ans2 - l) % tmp;
    return ((minn < C - maxx || (minn == C - maxx && ans1 < ans2)) ? ans1 : ans2);
}
 
signed main(){
    for(cin >> _; _; _--){
        // min/max{(2px + q) mod 2q}    (a <= x <= b)
        cin >> a >> b >> p >> q;
        cout << solve(2 * p, q, 2 * q, a, b) << endl;
    }
    return 0;
}
```









---

## 作者：w33z8kqrqk8zzzx33 (赞：7)

根据 $\sin$ 的性质，题目等价于求最小的 $x$ 来最小化 $|2(px\bmod q)-q|$。  
考虑乱搞，如何乱搞？

 - 首先，当 $b-a\le10^6$ 的时候暴力。
 - 另外，当 $[a,b]$ 最多在一个 $\sin$ 半周期里时并且 $q$ 太大，直接二分/三分出来最大值在哪里。
 - 最后，$q$ 很大 $p$ 也很大，所以可以看做 $px\bmod q$ 当一个随机函数。可以枚举答案然后用 exgcd 求出来逆元之后判断这个答案在 $[a,b]$ 里面可能不可能出现。这个可以用维护一个 $l$ 一个 $r$ 来做；初始 $l=\lfloor q/2\rfloor,r=\lceil q/2\rceil$，然后一个一个的往外滚动。

~~承认面向数据。~~  
过了之后发现可以直接被 $p=q-1$ 叉掉，很少见到一个 CF 数据水的题目。

时间复杂度:~~O(玄学)~~
 - 第一个是 $O(b-a)$
 - 第二个是 $O(\log(b-a))$，只能在特殊情况下用
 - 第三个是期望 $O(\frac{q}{b-a})$

贼长的代码：

```cpp
// writer: w33z8kqrqk8zzzx33
#include <bits/stdc++.h>
using namespace std;

// begin fast read template by CYJian (source: https://www.luogu.com.cn/paste/i11c3ppx)

namespace io {
	const int __SIZE = (1 << 21) + 1;
	char ibuf[__SIZE], *iS, *iT, obuf[__SIZE], *oS = obuf, *oT = oS + __SIZE - 1, __c, qu[55]; int __f, qr, _eof;
	#define Gc() (iS == iT ? (iT = (iS = ibuf) + fread (ibuf, 1, __SIZE, stdin), (iS == iT ? EOF : *iS ++)) : *iS ++)
	inline void flush () { fwrite (obuf, 1, oS - obuf, stdout), oS = obuf; }
	inline void gc (char &x) { x = Gc(); }
	inline void pc (char x) { *oS ++ = x; if (oS == oT) flush (); }
	inline void pstr (const char *s) { int __len = strlen(s); for (__f = 0; __f < __len; ++__f) pc (s[__f]); }
	inline void gstr (char *s) { for(__c = Gc(); __c < 32 || __c > 126 || __c == ' ';)  __c = Gc();
		for(; __c > 31 && __c < 127 && __c != ' '; ++s, __c = Gc()) *s = __c; *s = 0; }
	template <class I> inline bool gi (I &x) { _eof = 0;
		for (__f = 1, __c = Gc(); (__c < '0' || __c > '9') && !_eof; __c = Gc()) { if (__c == '-') __f = -1; _eof |= __c == EOF; }
		for (x = 0; __c <= '9' && __c >= '0' && !_eof; __c = Gc()) x = x * 10 + (__c & 15), _eof |= __c == EOF; x *= __f; return !_eof; }
	template <class I> inline void print (I x) { if (!x) pc ('0'); if (x < 0) pc ('-'), x = -x;
		while (x) qu[++ qr] = x % 10 + '0',  x /= 10; while (qr) pc (qu[qr --]); }
	struct Flusher_ {~Flusher_(){flush();}}io_flusher_;
} using io::pc; using io::gc; using io::pstr; using io::gstr; using io::gi; using io::print;

// end fast read template by CYJian

#define iter(i, a, b) for(int i=(a); i<(b); i++)
#define rep(i, a) iter(i, 0, a)
#define rep1(i, a) iter(i, 1, (a)+1)
#define log(a) cerr<<"\033[32m[DEBUG] "<<#a<<'='<<(a)<<" @ line "<<__LINE__<<"\033[0m"<<endl
#define all(a) a.begin(), a.end()
#define fi first
#define se second
#define pb push_back
#define mp make_pair
 
using ll=long long;
using pii=pair<int, int>;
//#define int ll
const int MOD = 1000000007;

ll bruteforce(ll a, ll b, ll p, ll q) {
	p %= q;
	ll best = 0x3f3f3f3f3f3f3f3f, bestp = 0, cur = p*a % q;
	iter(i, a, b+1) {
		if(abs(2*cur-q) < best) {
			best = abs(2*cur-q);
			bestp = i;
		}
		cur += p; cur -= (cur >= q ? q : 0);
	}
	return bestp;
}
constexpr ll infty = 1e18;
void exgcd(ll a, ll b, ll&x, ll&y) {
	if(!b) x=1,y=0;
	else exgcd(b, a%b, y, x), y-=a/b*x;
}
ll sv(ll p, ll q) { ll x,y; exgcd(p,q,x,y); return (x%q+q)%q; }
ll solution(ll p, ll q, ll g, ll tg, ll v, ll l, ll r) {
	if(!(0 <= tg && tg < q)) return infty;
	if(tg % g) return infty;
	ll tmp = v * (tg/g) % q;
	if(tmp < l) {
		ll k = (l - tmp + q - 1) / q;
		tmp += k * q;
	} else {
		ll k = (tmp - l) / q;
		tmp -= k * q;
	}
	assert(l <= tmp);
	assert(tmp-q < l);
	if(r < tmp) return infty;
	return tmp;
}
ll bruteforce2(ll a, ll b, ll p, ll q) {
	ll g = 1;
	ll low, high;
	ll v = sv(p, q);
	if(q % 2 == 0) {
		ll t = solution(p, q, g, q/2, v, a, b);
		if(t != infty) return t;
		low = q/2 - 1, high = q/2+1;
	} else low = q/2, high = q/2+1;
	while(1) {
		//if(low % 1000000 == 0) cout << low << ' ' << high << endl;
		if(low <= -1 && high >= q) return -1;
		ll t1 = solution(p, q, g, low, v, a, b);
		ll t2 = solution(p, q, g, high, v, a, b);
		t2 = min(t1, t2);
		if(t2 != infty) return t2;
		low--; high++;
	}
	return -1;
}
ll check1(ll a, ll b, ll p, ll q) {
	auto eval = [&](ll x){return abs(2*(p*x%q)-q);};
	ll low = a, high = b;
	pair<ll, ll> ans = {infty,0};
	ans = min(ans, {eval(a), a});
	ans = min(ans, {eval(b), b});
	if(eval(a)<eval(a+1)) {
		while(low <= high) {
			ll mid = (low+high)/2;
			ans = min(ans, {eval(mid), mid});
			ans = min(ans, {eval(mid+1), mid+1});
			if(eval(mid)<eval(mid+1)) low = mid + 1;
			else high = mid - 1;
		}
	}
	return ans.se;
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
	while(t--) {
		ll a, b, p, q; cin >> a >> b >> p >> q;
		ll g = __gcd(p, q);
		p /= g;
		q /= g;
		if(b-a+1 <= 1000000) cout << bruteforce(a, b, p, q) << endl;
		else if(2 * p * (b-a+1) < q && q > 1000000) cout << check1(a, b, p, q) << endl;
		else cout << bruteforce2(a, b, p, q) << endl;
	}
}

```

---

## 作者：lgvc (赞：4)

问题容易归约到最小化，最大化 $(2px+q) \bmod 2q$，其中 $a \le x \le b$。给一个辗转相除的 $O(\log q)$ 算法。

直接解决最小化 $ax+by+c$ 的问题，要求 $ax+by+c \ge 0$ 且 $l \le x \le y$。这显然就是最小化 $ax+c \bmod b$。不妨设 $a<b$。

两种情况：

1. $\lfloor\frac{a*l+c}{b}\rfloor=\lfloor\frac{a*r+c}{b}\rfloor$

此时 $l,r$ 总有一个是最优解之一，直接求出答案。

2. 其余情况

注意到此时要求的最小值  $< a$ 。使用 $0 \le ax+by+c < a$ 求出 $b$ 的可能范围。注意满足 $b$ 的范围， $a$ 的范围一定可以满足，因为对所有 $b$，$a$ 只有最多一个解。

于是可以递归求出答案： $a=b \bmod a$ ，$b=a$，$c$ 不变，$l,r$ 为求出的 $b$ 的范围。这样是对的，本题中可以构造出解。

然后还要求一个最小的解，不停减去 $\frac{q}{\gcd(p,q)}$ ，保证在范围内就可以。

代码，实现时直接求了 $|ax+by+c|$ 的最小值，方法类似。

```cpp
#include <bits/stdc++.h>
#define int long long
int T,A,B,P,Q;
struct n_t{
	int a,b;
};
int cl(int x,int y);
int fl(int x,int y) {
	if(y<0) x=-x,y=-y;
	if(x<0) return -cl(-x,y);
	return x/y;
}
int cl(int x,int y) {
	if(y<0) x=-x,y=-y;
	if(x<0) return -fl(-x,y);
	return (x+y-1)/y;
}
n_t fd(int p,int q,int c,int l,int r) {
	int tz=-c/q;
	c%=q;
	int a1=fl(p*l+c,q);
	int a2=fl(p*r+c,q);
	//printf("%lld %lld %lld %lld %lld\n",p,q,c,l,r);
	if(a1==a2) {
		if((p*l+c)-q*a1<q-(p*r+c)+q*a2) {
			return (n_t){l,-a1+tz};
		} 
		return (n_t){r,-1-a2+tz};
	}
	int lx=-(p/2)-p*r-c,rx=(p-1)/2-p*l-c;
	rx=fl(rx,q);
	lx=cl(lx,q);
	n_t tp=fd(q%p,p,c,lx,rx);
	return (n_t){tp.b-tp.a*(q/p),tp.a+tz};
}
signed main(void) {
	scanf("%lld",&T);
	while(T--) {
		scanf("%lld %lld %lld %lld",&A,&B,&P,&Q);
		P%=Q;
		int tz=std::__gcd(P,Q);P/=tz;Q/=tz;
		int tp=fd(2*P,2*Q,Q,A,B).a,tp1,tp2;
		tp2=(Q-tp%Q+A/Q*Q+Q);
		tp2=tp2-(tp2-A)/Q*Q;
		tp1=tp-(tp-A)/Q*Q;
		printf("%lld\n",std::min(tp1,tp2));
	}
}
```

---

## 作者：critnos (赞：0)

发现就是求 $(ax+b)\bmod c$ 的最值，写成 $(ax+b)-\lfloor (ax+b)/c\rfloor \times c$，然后万能欧几里得秒了。

[提交记录](https://codeforces.com/problemset/submission/1182/262702462)

---

