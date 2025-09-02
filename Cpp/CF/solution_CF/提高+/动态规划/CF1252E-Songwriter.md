# Songwriter

## 题目描述

安迪是数学家，计算机科学家和作曲家。潜心创作很长时间后，他终于写出了一首他认为是他最好的作品。但是，每位歌手有一个独特的音域，因此可能需要调整。

旋律被定义为$N$个音符的序列（保证$N$为整数）。$A$是安迪创作的原旋律。现在需要把$A$调整成一个新的旋律B，这样对于每个小于$N$的$i$：

- 若$A_i<A_{i+1}$，那么$B_i<B_{i+1}$；
- 若$A_i=A_{i+1}$，那么$B_i=B_{i+1}$；
- 若$A_i>A_{i+1}$，那么$B_i>B_{i+1}$；
- $|B_i-B_{i+1}|\le K$，即两个连续音符之间的差不大于$K$。

此外，歌手还要求所有的音符都在她的音域范围内，即对于所有$i$都要求$L\le B_i\le R$。请你帮助安迪找出符合条件的字典序最小的$B$。若存在$j$（$1\le j\le N$）使得所有小于$j$的$i$ $X_i=Y_i$且$X_j<Y_j$，则称旋律$X<$ 旋律$Y$。

## 说明/提示

样例1：  
定义$A=\{1,3,5,6,7,8,9,10,3,7,8,9,11,12,12\}$，如下图所示。指向右上方的箭头表示$A_i<A_{i+1}$，指向右侧的箭头表示$A_i=A_{i+1}$，指向右下角的箭头表示$A_i>A_{i+1}$。根据$L=1,R=8,K=6$，我们可以得出符合条件且字典序最小的$B=\{1,2,3,4,5,6,7,8,2,3,4,5,6,7,8,8\}$，如图所示。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1252E/e498d7b4f78632de9fe4f587d3c868951b8bb1a9.png)

## 样例 #1

### 输入

```
16 1 8 6
1 3 5 6 7 8 9 10 3 7 8 9 10 11 12 12
```

### 输出

```
1 2 3 4 5 6 7 8 2 3 4 5 6 7 8 8
```

## 样例 #2

### 输入

```
16 1 8 6
1 3 5 6 7 8 9 10 3 7 8 9 10 11 12 13
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
16 1 10 10
1 3 5 6 7 8 9 10 3 7 8 9 1 11 12 13
```

### 输出

```
1 2 3 4 5 6 7 8 1 2 3 4 1 2 3 4
```

# 题解

## 作者：bsdsdb (赞：1)

题意：给 $\{a_n\}$，要求给出字典序最小的满足下述条件的序列 $\{b_n\}$，或报告不存在：

- 值域为 $[L,R]\cup\mathbb N$；
- $\forall i:\operatorname{sgn}(a_i-a_{i-1})=\operatorname{sgn}(b_i-b_{i-1})$；
- $\forall i:b_i\in[b_{i-1}-k,b_{i-1}+k]$。

考虑从「判断前面合法且 $b_i$ 的值为 $v$ 时是否有解」的角度推出「只考虑后面时，$b_i$ 的值域」。如果 $b_i$ 太低，以至于后面的数只做 $+k / +0 / -1$ 的变化也不能使得 $\forall j:b_i\ge L$，那么这么取是不合法的。也就是说，如果 $v$ 加上「后面的数尽可能往大变时产生的 $b_{\textcolor{red}(i,n]}$ 的最小前缀和」小于 $L$，那么他不合法。这个前缀和可以后往前递推 $\Omicron(n)$ 求出。具体来说，设 $f_i$ 为$b_{\textcolor{red}[i,n]}$ 的答案，那么 $f_i=\min(u,u+f_{i+1})$，其中 $u$ 是 $+k/+0/-1$。然后我们就给 $b_i$ 加了一条限制：$b_i+f_{i+1}\ge L$。如果 $b_i$ 太高使得定有 $b_j>R$ 的情况同理。然后在把这些值域交上 $[L,R]$ 和 $[b_{i-1}-k,b_{i-1}+k]$ 还有 $A_i$（由 $\operatorname{sgn}(a_i-a_{i-1})$ 给出的限制）之后按最小的输出就行了。有空集就无解。至于为什么无解之后不调整 $b_{i-1}$，因为如果无解是因为这个的话那么 $b_{i-1}$ 应该提前预知并自行调整。

```cpp
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
#define invarg invalid_argument
#define cus_throw(msg) throw invarg(string(msg) + " at " + __FILE__ + ":" + to_string(__LINE__))
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

namespace modint {
    const ll MOD = 1;
    struct modint {
        ll val, mod;
        void setmod(ll x) {
            mod = x;
        }
        explicit operator ll() {
            return val;
        }
        modint() {
            val = 0, mod = MOD;
        }
        modint(ll v, ll m = MOD) {
            if (m == 1) {
                cus_throw("init modint without mod");
            }
            v %= m;
            if (v < 0) {
                v += m;
            }
            val = v;
            mod = m;
        }
    };
    #define chkmod(x, y) if (x.mod != y.mod) cus_throw("mod isn't the same")
    modint operator+(modint x, modint y) {
        chkmod(x, y);
        return modint(x.val + y.val, x.mod);
    }
    modint operator-(modint x, modint y) {
        chkmod(x, y);
        return modint(x.val - y.val, x.mod);
    }
    modint operator*(modint x, modint y) {
        chkmod(x, y);
        return modint(__int128(1) * x.val * y.val, x.mod);
    }
    modint qpow(modint x, ll y) {
        if (!y) {
            return modint(1, x.mod);
        } else if (y & 1) {
            return x * qpow(x, y ^ 1);
        } else {
            return qpow(x * x, y >> 1);
        }
    }
    modint inv(modint x) {
        return qpow(x, x.mod - 2);
    }
    modint operator/(modint x, modint y) {
        chkmod(x, y);
        if (ll(y) == 0) {
            cus_throw("modint divide by 0");
        }
        return x * inv(y);
    }
    modint operator+=(modint& x, modint y) {
        return x = x + y;
    }
    modint operator-=(modint& x, modint y) {
        return x = x - y;
    }
    modint operator*=(modint& x, modint y) {
        return x = x * y;
    }
    modint operator/=(modint& x, modint y) {
        return x = x / y;
    }
    bool operator==(modint x, modint y) {
        chkmod(x, y);
        return x.val == y.val;
    }
}

const ll MAXN = 1e5 + 5;
ll n, L, R, k, a[MAXN], b[MAXN], zxzd[MAXN], zdzx[MAXN];

int main() {
	read(n), read(L), read(R), read(k);
	for (ll i = 1; i <= n; ++i) read(a[i]);
	for (ll i = n; i > 1; --i) {
		if (a[i] > a[i - 1]) {
			a[i] = 1;
		} else if (a[i] < a[i - 1]) {
			a[i] = -1;
		} else {
			a[i] = 0;
		}
	}
	a[1] = 0;
	for (ll i = n; i; --i) {
		//zxzd
		ll v = 0;
		if (a[i] == -1) {
			v = -k;
		} else if (a[i]) {
			v = 1;
		}
		zxzd[i] = max(v, v + zxzd[i + 1]);
		// zdzx
		v = 0;
		if (a[i] == -1) {
			v = -1;
		} else if (a[i]) {
			v = k;
		}
		zdzx[i] = min(v, v + zdzx[i + 1]);
	}
//	for (ll i = 1; i <= n; ++i) cerr << i << ' ' << a[i] << ' ' << zxzd[i] << ' ' << zdzx[i] << endl;
	for (ll i = 1; i <= n; ++i) {
		// b[i] + zxzd[i + 1] <= R
		// b[i] + zdzx[i + 1] >= L
		// b[i] <= R - zxzd[i + 1]
		// b[i] >= L - zdzx[i + 1]
//		cerr << i << endl;
		if (i == 1) {
			b[i] = max(L, L - zdzx[i + 1]);
			if (b[i] > R - zxzd[i + 1]) {
				goto wj;
			}
		} else if (a[i] == -1) {
			b[i] = max({L, b[i - 1] - k, L - zdzx[i + 1]});
			if (b[i] >= b[i - 1] || b[i] > R - zxzd[i + 1]) {
				goto wj;
			}
		} else if (a[i] == 1) {
			b[i] = max({L, b[i - 1] + 1, L - zdzx[i + 1]});
//			cerr << L - zdzx[i + 1] << endl;
			if (b[i] > b[i - 1] + k || b[i] > R - zxzd[i + 1]) {
				goto wj;
			}
		} else {
			b[i] = b[i - 1];
		}
		if (b[i] > R) {
			goto wj;
		}
	}
	for (ll i = 1; i <= n; ++i) write(b[i]), space();
	enter();
	return 0;
	wj:;
	puts("-1");
//	for (ll i = 1; i <= n; ++i) cerr << b[i] << ' ';
	return 0;
}

/*
k=2
++---++
1 4 3 2 1 2 3
*/

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

## 作者：PeterBei (赞：1)

考虑先从后向前反推，令最后一位可能的取值区间为 $L$ 到 $R$，则样例一中所有位的可能取值区间为：

![](https://cdn.luogu.com.cn/upload/image_hosting/tqc5obrx.png)

样例比较特殊，第一位只有一种可能的取值。若是有多种可能取值的话，则贪心的从最小的可能值开始取，即可满足字典序最小的要求。

有且仅有在反推的时候出现某一位不可以取任何音符的情况时，输出无解。

```
int main(){
	long long n = read(), l = read(), r = read(), k = read();
	for(long long i = 1; i <= n; i++){
		a[i] = read();
	}
	qj[n].l = l, qj[n].r = r;
	for(long long i = n - 1; i >= 1; i--){
		if(a[i] == a[i + 1]){
			qj[i].l = qj[i + 1].l, qj[i].r = qj[i + 1].r;
		} else if(a[i] < a[i + 1]){
			qj[i].l = max(qj[i + 1].l - k, l), qj[i].r = qj[i + 1].r - 1;
		} else{
			qj[i].l = qj[i + 1].l + 1, qj[i].r = min(qj[i + 1].r + k, r);
		} if(qj[i].r < qj[i].l || qj[i].l < l || qj[i].r > r){
			cout << -1; return 0;
		}
	}
	cout << qj[1].l << ' '; long long last = qj[1].l;
	for(long long i = 2; i <= n; i++){
		if(a[i] > a[i - 1]) last = max(last + 1, qj[i].l);
		if(a[i] < a[i - 1]) last = max(last - k, qj[i].l);
		cout << last << ' ';
	}
	return 0;
}
```

---

