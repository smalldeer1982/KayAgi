# Perform Operations to Maximize Score

## 题目描述

I see satyam343. I'm shaking. Please more median problems this time. I love those. Please satyam343 we believe in you.

— satyam343's biggest fan



You are given an array $ a $ of length $ n $ and an integer $ k $ . You are also given a binary array $ b $ of length $ n $ .

You can perform the following operation at most $ k $ times:

- Select an index $ i $ ( $ 1 \leq i \leq n $ ) such that $ b_i = 1 $ . Set $ a_i = a_i + 1 $ (i.e., increase $ a_i $ by $ 1 $ ).

Your score is defined to be $ \max\limits_{i = 1}^{n} \left( a_i + \operatorname{median}(c_i) \right) $ , where $ c_i $ denotes the array of length $ n-1 $ that you get by deleting $ a_i $ from $ a $ . In other words, your score is the maximum value of $ a_i + \operatorname{median}(c_i) $ over all $ i $ from $ 1 $ to $ n $ .

Find the maximum score that you can achieve if you perform the operations optimally.

For an arbitrary array $ p $ , $ \operatorname{median}(p) $ is defined as the $ \left\lfloor \frac{|p|+1}{2} \right\rfloor $ -th smallest element of $ p $ . For example, $ \operatorname{median} \left( [3,2,1,3] \right) = 2 $ and $ \operatorname{median} \left( [6,2,4,5,1] \right) = 4 $ .

## 说明/提示

For the first test case, it is optimal to perform $ 5 $ operations on both elements so $ a = [8,8] $ . So, the maximum score we can achieve is $ \max(8 + \operatorname{median}[8], 8 + \operatorname{median}[8]) = 16 $ , as $ c_1 = [a_2] = [8] $ . It can be proven that you cannot get a better score.

For the second test case, you are not able to perform operations on any elements, so $ a $ remains $ [3,3,3] $ . So, the maximum score we can achieve is $ 3 + \operatorname{median}[3, 3] = 6 $ , as $ c_1 = [a_2, a_3] = [3, 3] $ . It can be proven that you cannot get a better score.

## 样例 #1

### 输入

```
8
2 10
3 3
1 1
3 10
3 3 3
0 0 0
4 4
2 1 5 1
0 1 0 1
5 4
7 5 2 5 4
0 0 1 0 1
5 1
5 15 15 2 11
1 0 0 1 1
5 2
10 11 4 10 15
1 1 0 1 0
4 4
1 1 2 5
1 1 0 0
2 1000000000
1000000000 1000000000
1 1```

### 输出

```
16
6
8
13
21
26
8
3000000000```

# 题解

## 作者：BrotherCall (赞：3)

第一步化繁为简。

设题目中的 $a_i + \text{median}(c_i)$ 为 $f_i$。

考虑若所有 $b_i$ 均为 $0$ 或 $1$ 的情况。

若所有 $b_i$ 均为 $0$，由于不考虑增加的数量 $k$，当 $a_i$ 最大时答案取最大为 $f_i$。

若所有 $b_i$ 均为 $1$，当 $a_i$ 最大时答案取最大为 $f_i+k$。

> 证明：
>
> 先考虑当 $b_i$ 均为 $0$ 的情况，默认 $a_i$ 已按递增排序。
>
> 令删除最大的数后的中位数为 $mid$。
>
> 若 $a_i > mid$，则 $i$ 的坐标 $>\displaystyle \lfloor \frac{n}{2}\rfloor$，中位数坐标为 $\displaystyle \lfloor \frac{n}{2}\rfloor$。
>
> 若 $a_i \le mid$，则 $i$ 的坐标 $\le\displaystyle \lfloor \frac{n}{2}\rfloor$，中位数坐标为 $\displaystyle \lfloor \frac{n}{2}\rfloor + 1$。
>
> 第一种情况最优为 $a_n + a_{\lfloor \frac{n}{2}\rfloor}$，第二种情况最优为 $a_{\lfloor \frac{n}{2}\rfloor + 1} + a_{\lfloor \frac{n}{2}\rfloor}$。
>
> 显然前者大于等于后者，所以最优策略即为删一个最大的 $a_i$。
>
> 第一条结论得证。
>
> 第二条结论就简单了，如果把 $k$ 个贡献加到 $a_i$ 上的话可以获得实打实的 $k$ 个贡献，而加到其他数上，首先一定不会超过 $k$ 的贡献，其次由于中位数的变动，贡献很可能小于 $k$。
>
> 第二条结论得证。

---

现在考虑既有 $0$ 也有 $1$ 的情况。

不难发现当最大的 $a_i$ 对应的 $b_i$ 为 $1$ 时，答案即为 $f_i + k$。

如果最大的 $a_i$ 对应的 $b_i$ 为 $0$ 咋办呢。

首先一种情况是选定 $a_i$，并用 $k$ 次操作最大化剩下部分的中位数，这个二分答案然后按 $a_i$ 从大往小判断 $k$ 次操作内，是否存在至少 $\displaystyle \lfloor\frac{n + 1}{2}\rfloor$ 个数 $\ge mid$。

另一种情况是找到 $b_j = 1$ 时最大的 $a_j$，这种情况的最优答案为 $f_j + k$。

两种情况取个 $\max$ 即可。

---

时间复杂度：二分内排序的话即为 $O(n\log n\log V)$，二分外排序的话 $O(n\log V)$。

我写的是前者，[提交记录](https://codeforces.com/contest/1998/submission/282679395)。

---

## 作者：bsdsdb (赞：0)

题意：给定序列 $\{a_n\}$，指定一些数可以进行操作，一次操作可以把一个数自增 1，共操作 $k$ 次，最大化 $\max_{i=1}^na_i+\operatorname{median}(a\backslash a_i)$.

下文默认 $\{a\}$ 已经排好序，所有除法全部下取整。

首先考虑 $k=0$ 的情况。删完后的中位数在原序列中只有两种可能：$a_\frac{n}{2}$ 和 $a_{\frac{n}{2}+1}$. 如果是前者，那么取出来的数应该尽可能大，也就是 $a_n+a_\frac{n}{2}$. 后面那种情况的话答案是 $a_{\frac{n}{2}+1}+a_\frac{n}{2}$，显然前者更好。因此现在有个结论：如果 $k=0$，那么选 $i\gets n$.

对于 $k\neq 0$ 的情况，可以把 $k$ 用在两个地方：加最大值，加中位数。加最大值的话找最大的能加的数就行，加中位数的话二分答案即可。容易注意到加中位数的时候最大值是不用变的，因为如果新中位数大于原最大值，那么这样子搞出来的答案一定不如直接加最大值（如果可以这么操作，那么把往 $\frac{n}{2}$ 个数上加的东西全往一个数上加显然答案更大，见图）。

![](https://www.luogu.com.cn/fe/api/problem/downloadAttachment/f04v21uc)

重新分配之后，中位数小了 1 个柱子，最大值加了 3 个柱子。

```
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
 
const ll MAXN = 2e5 + 5;
 
ll n, k;
pll a[MAXN], aa[MAXN];
 
bool chk(ll tg) {
	// cerr << "chk " << tg << endl;
	ll kk = k;;
	for (ll i = 1; i <= n; ++i) {
		aa[i] = a[i];
	}
	for (ll i = n; i; --i) {
		if (a[i].first < tg && a[i].second) {
			ll f = min(kk, tg - aa[i].first);
			aa[i].first += f;
			kk -= f;
		}
	}
	sort(aa + 1, aa + n + 1);
	return aa[n >> 1].first >= tg;
}
 
void init() {
	for (ll i = 1; i <= n; ++i) {
		a[i] = aa[i] = pll();
	}
}
int mian() {
	read(n), read(k);
	for (ll i = 1; i <= n; ++i) {
		read(a[i].first);
	}
	for (ll i = 1; i <= n; ++i) {
		read(a[i].second);
	}
	sort(a + 1, a + n + 1);
	// +max
	ll ans = 0;
	for (ll i = 1; i <= n; ++i) {
		aa[i] = a[i];
	}
	for (ll i = n; i; --i) {
		if (aa[i].second) {
			cerr << i << endl;
			ans = max(aa[n].first, aa[i].first + k) + aa[(n >> 1) + (aa[i].first + k >= aa[n].first && i <= (n >> 1))].first;
			break;
		}
	}
//	cerr << ans << endl;
	// +med
	ll l = 0, r = a[n].first, mid;
	while (l < r) {
		mid = (l + r + 1) >> 1;
		if (chk(mid)) {
			l = mid;
		} else {
			r = mid - 1;
		}
	}
	write(max(ans, l + a[n].first)), enter();
	return 0;
}
 
int main() {
	ll T;
	read(T);
	while (T--) {
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
 
  ;  ;  ;;; ;;;  ;   ;   ;  ;;  ;;  ;;; 
; ; ; ;  ;  ; ; ; ; ; ; ; ; ;;  ; ; ; ;  ;   ;
;;; ; ;  ;  ; ;   ; ; ;   ; ;;  ; ; ; ;  ;   ;
;;; ; ;  ;  ;;   ;  ; ;  ;  ;;  ;;  ;;  ;;; ;;;
;;; ; ;  ;  ;   ;   ; ; ;   ;;; ;;  ;    ;   ;
; ; ; ;  ;  ;   ; ; ; ; ; ;  ;  ; ; ;    ;   ;
;    ;  ;;; ;   ;;;  ;  ;;;  ;  ; ; ; 
```

---

## 作者：liugh_ (赞：0)

## [Perform Operations to Maximize Score](https://codeforces.com/contest/1998/problem/C)

> 每次操作任选 $i$ 满足 $b_i=1$ 并令 $a_i\gets a_i+1$，求 $m$ 次操作后 $\max_{i=1}^{n} a_i+f(i)$，其中 $f(i)$ 为删去 $a_i$ 后 $a$ 的中位数。
>
> $n\le 5\cdot 10^6$。

先升序排序。考虑 $m=0$，有一个关键的结论：答案必为 $a_n+f(n)$。证明略，对中位数的位置分讨四种情况即可。

考虑 $m\ne 0$，一种情况是使 $f(n)$ 尽量大，可以通过二分中位数解决；另一种情况是若 $b_n=1$ 则答案对 $a_n+m+f(n)$ 取 $\max$，否则找到最大的 $a_p$ 满足 $b_p=1$ 并令答案对 $a_p+m+f(p)$ 取 $\max$。时间复杂度 $O(n\log n)$。

```cpp
#define int ll
int n,m;cin>>n>>m;
vector<pii> a(n+5);
for(int i=1;i<=n;i++)cin>>a[i].fi;
for(int i=1;i<=n;i++)cin>>a[i].se;
sort(&a[1],&a[n]+1);
auto chk=[&](int mid)->bool {
    vector<int> t;
    int lst=(n-1)/2+1; // mid 能成为中位数当且仅当不少于 (n-1)/2+1 个数不小于 mid
    for(int i=1;i<=n-1;i++){
        if(a[i].fi>=mid){
            lst--;
        }else if(a[i].se){
            t.pb(a[i].fi);
        }
    }
    for(int res=0;;){
        if(lst<=0)return res<=m;
        if(!t.size())return 0;
        res+=mid-t.back();
        t.pop_back();
        lst--;
    }
    return 0;
};
int l=1,r=2e9,res=-1;
while(l<=r){
    int mid=(l+r)>>1;
    if(chk(mid))res=mid,l=mid+1;else r=mid-1;
}
res+=a[n].fi;
for(int i=n;i>=1;i--)if(a[i].se){
    int p=(n+1)>>1;
    if(n&1){
        if(i>=p)p--;
    }else{
        if(i<=p)p++;
    }
    tomax(res,a[i].fi+m+a[p].fi);
    break;
}
cout<<res<<'\n';
```

---

## 作者：RaymondOccam (赞：0)

### 题目传送门
[link](https://codeforces.com/problemset/problem/1998/C)

### 题意
假设有数组 $x$，定义 $\operatorname{f}(x)$ 表示数组 $x$ 中的第 $\lfloor \frac{|x|+1}{2}\rfloor$ 小的元素（$|a|$ 表示数组 $a$ 的长度）。

之后有一个长度为 $n$ 的数组 $a$、一个整数 $k$ 和一个二进制数组 $b$。

有如下最多 $k$ 次操作：
- 选择一个索引 $i$，必须满足 $b_i=1$ 且 $1\le i\le n$。在满足上述条件时，将 $a_i$ 变为 $a_i+1$。

求在 $k$ 次操作内使得得分 $\max\limits_{i=1}^{n}\left(a_i+\operatorname{f}(c_i)\right)$ 尽可能的大的值，$c_i$ 表示从 $a$ 中删除 $a_i$ 后的数组。

### 思路
就是二分和贪心。

如果将 $a$ 数组按照升序排列，$\operatorname{f}(x)$ 就为 $x_{\lfloor \frac{n}{2}\rfloor}$ 或者 $x_{\lfloor \frac{n+2}{2}\rfloor}$，其得分就为 $a_n+\operatorname{f}(c_n)$。

考虑两种情况：
- $\operatorname{f}(c_i)=a_{\lfloor\frac{n}{2}\rfloor}$，在这种情况下，得分为 $a_n+a_{\lfloor\frac{n}{2}\rfloor}$。因为要想最大化 $a_i$，$i$ 的最佳值便为 $n$，使得得分最大化。
- $\operatorname{f}(c_i)=a_{\lfloor\frac{n+2}{2}\rfloor}$，在这种情况下，得分为 $a_{\lfloor\frac{n}{2}\rfloor}+a_{\lfloor\frac{n+2}{2}\rfloor}$。因为最优情况下，$i$ 需要等于 $\lfloor\frac{n}{2}\rfloor$，使得得分最大化。
 
得出结论，$\operatorname{f}(c_i)=a_{\lfloor\frac{n}{2}\rfloor}$ 的情况是最优的。

可以二分，使 $a_n$ 为最大值的情况下，得到其他 $n-1$ 个元素的最大中值。

### 代码
只给出核心部分。

```cpp
sort(vec.begin(), vec.end());
ans = 0;
for (ll i = 0; i < n; i++)
    if (vec[i].second == 1)
    {
        if (i < n / 2)
			vc = vec[n / 2].first;
        else
            vc = vec[(n - 2) / 2].first;

		ans = max(ans, vec[i].first + k + vc);
    }

l = 0, r = 0x7fffffff;

while (l != r)
{
    ll mid = (1 + l + r) / 2;
    z = 0;
    vector<ll> tin;
    for (ll i = 0; i < n - 1; i++)
        if (vec[i].first >= mid)
            z++;
        else if (vec[i].second == 1)
            tin.push_back(mid - vec[i].first);
            
        reverse(tin.begin(), tin.end());
        rk = k;

        for (auto x : tin)
            if (rk >= x)
                rk -= x,
                z++;

        if (z >= (n + 1) / 2)
            l = mid;
        else
            r = mid - 1;
}
ans = max(ans, vec[n - 1].first + l);
```

---

## 作者：yshpdyt (赞：0)

## 题意

一个正整数序列 $a_i$，一个 `01` 序列 $b_i$，你可以进行 $k$ 次操作：
选择一个 $b_i=1$ 的位置，让 $a_i$ 加一。

最大化 $res=\max\{{a_i}+f(a_i)\}$，$f(a_i)$ 含义为去掉 $a_i$ 后的 $n-1$ 个位置的第 $\left\lceil\frac{n-1}{2}\right\rceil$ 大的数（以下简称中位数）。

## Sol
喵喵贪心题。

首先可以将数组排序，以方便确定中位数，记 $p=\left\lfloor\frac{n}{2}\right\rfloor$。
### Part 1 考虑如果没有 $k$ 次操作的情况

- 当 $i\le p$ 时
  - 当 $2 \mid n$ 时，左边剩下 $p-1$ 个，右边剩下 $p$ 个，最终中位数是原序列第 $p+1$ 个元素。   
  - 当 $2\nmid n$ 时，左边剩下 $p-1$ 个，右边剩下 $p+1$ 个，最终中位数是原序列第 $p+1$ 个元素。
  
由于 $a_i$ 升序，此时最大的 $res_1=a_p+a_{p+1}$。
- 当 $i> p$ 时
  - 当 $2 \mid n$ 时，左边剩下 $p$ 个，右边剩下 $p-1$ 个，最终中位数是原序列第 $p$ 个元素。   
  - 当 $2\nmid n$ 时，左边剩下 $p$ 个，右边剩下 $p-1$ 个，最终中位数是原序列第 $p$ 个元素。

由于 $a_i$ 升序，此时最大的 $res_2=a_n+a_{p}>res_1$。



### Part 2 考虑有 $k$ 次操作且只能加在删除元素上
由于最终答案只与删除元素和中位数有关，加在其它数上 $x$ 次不一定能使答案增大 $x$，但是加在删除元素上一定可以使答案增大 $x$，所以把 $k$ 次操作全部加入 $a_i$：

$$res_3=\max_{i=1}^p\{a_i+a_{p+1}+k\},b_i=1$$

$$res_4=\max_{i=p+1}^n\{a_i+a_{p}+k\},b_i=1$$


### Part 3 考虑有 $k$ 次操作且只能加在其它元素上

这种情况对应要考虑 $b_i=0$ 的 $i$，相当于钦定 $i=n$ ，如果 $b_n=1$，那么删掉 $a_n$ 并给其加最优，如果 $b_n=b_i=0$ ，都是给中位数加相同的值，那么取删除元素为 $b_n$ 最优。

这种情况可以二分中位数为 $x$，然后在 $k$ 次操作内，从大到小使每个 $<x$ 的位置加到 $x$，判断最后是否有 $\left\lfloor\frac{n+1}{2}\right\rfloor$ 个元素$\ge x$ 即可。

$$res_5=a_n+x$$

所以最后的答案是 $\max_{i=1}^5 res_i$。

时间复杂度 $O(\log n)$，重点在于看出取 $i=n$ 最优。
##  Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 200005
#define endl "\n" 
#define fi first
#define se second
using namespace std;
const ll mod=1e9+7;
const ll inf=1e18;
const double eps=1e-6;


ll n,m,p,ans,res,now;
pair<ll,ll>a[N];
ll h[N],sum[N],hp[N],b[N];

bool check(ll x){
    ll cost=0;
    ll cnt=0;
    for(int i=n-1;i>=1;i--){
        b[i]=a[i].fi;
        if(a[i].fi<x&&a[i].se){
            if(cost+x-a[i].fi<=m)cost+=x-a[i].fi,b[i]=x;
        }
        if(b[i]>=x)cnt++;
    }
    return cnt>(n-1)/2;
}
void sol(){
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>a[i].fi;
    for(int i=1;i<=n;i++)cin>>a[i].se;
    sort(a+1,a+n+1);
    p=n/2;
    res=0;
    for(int i=1;i<=p;i++)if(a[i].se)res=max(a[i].fi+m+a[p+1].fi,res);
    for(int i=p+1;i<=n;i++)if(a[i].se)res=max(a[i].fi+m+a[p].fi,res);
    ll l=a[p].fi,r=a[p].fi+m;
    while(l<r){
        ll mid=(l+r+1)>>1;
        if(check(mid))l=mid;
        else r=mid-1;
    }
    cout<<max(res,a[n].fi+l)<<endl;
}
int main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    ll ttt;
    cin>>ttt;
    while(ttt--)sol();
    return 0;
}
```

---

## 作者：__Floze3__ (赞：0)

## 思路简介

~~做过的最难的Div2 C~~

显而易见的，如果我们选择出的那个数可以被增加，那么增加那个数一定更优。这启示我们分两种情况考虑：一种是选出能被增加的数中的最大的数，并且一直增加那个数；另一种是选出不能被增加的数中的最大的数，并且增大中位数。第一种情况是好处理的，如何处理第二种情况？我们考虑要是中位数为某个特定的值所需的最少操作次数具有单调性，我们不妨考虑二分中位数，可以做到 $O(n)$ check。单组数据的时间复杂度为 $O(n \log n + n \log V)$。

## 代码

[赛时提交链接](https://codeforces.com/contest/1998/submission/275592870)

---

## 作者：__Louis__ (赞：0)

## CF1998C Perform Operations to Maximize Score 题解

### 题目翻译

两个数组 $A,B$，大小为 $n$，你可以一共 $k$ 次操作，选择一个 $i\in [1,n]$，满足 $B_i$ 为 $1$，然后让 $A_i$  加一。

执行完所有操作后，你可以选择一个数和剩下 $n-1$ 个数中第  $ \left\lfloor \frac{|n|+1}{2} \right\rfloor $ 小的数作为你的得分，求得分的最大值。

### 分析

由贪心得知，最终只可能以两种方法取得最大的得分。

- 取最大的 $0$，然后剩下的取最大的。
- 取最大的 $1$，然后计算。

第二种可以 sort 直接做完，但是第一种比较困难。

考虑二分答案，贪心判断是否能满足有 $ \left\lfloor \frac{|n|+1}{2} \right\rfloor $ 个数比答案大即可。

时间复杂度 $O(n\log n)$。

### code


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define inf 0x3f3f3f3f3f3f3f3f
const int maxn=2e5+10;
struct node{
	int da,b;
}arr[maxn];
bool cmp(node a,node b){
	if(a.b==b.b){
		return a.da>b.da;
	}else{
		return a.b<b.b;
	}
}
bool vis[maxn];
int mx0,i0,mx1,i1; 
int cnt;
int n,k;
bool check(int x){
	int sum=0;
	for(int i=1;i<=cnt;i++){
		if(vis[i]) continue;
		if(arr[i].da>=x) sum++;
	}
	int q=k;
	for(int i=cnt+1;i<=n;i++){
		if(vis[i]) continue;
		if(arr[i].da>=x){
			sum++;
		}else if(x-arr[i].da<=q){
			q-=(x-arr[i].da);
			sum++;
		}
	}
	return sum>((n-1)/2);
}
bool cmp1(node a,node b){
	return a.da<b.da;
}
signed main(){
	int T;
	scanf("%lld",&T);
	while(T--){
		cnt=0;
		scanf("%lld%lld",&n,&k);
		for(int i=1;i<=n;i++){
			scanf("%lld",&arr[i].da);
		}
		for(int i=1;i<=n;i++){
			scanf("%lld",&arr[i].b);
			if(!arr[i].b) cnt++;
		}
		sort(arr+1,arr+1+n,cmp);
		int ans=0,l=0,r=inf;
		if(cnt){
			vis[1]=true;
			
			while(l<r){
				int mid=(l+r)>>1;
				if(check(mid))  l=mid+1;
				else r=mid;
			} 
			ans=max(arr[1].da+l-1,ans);
			vis[1]=false;
			
		}
		if(cnt!=n){
			swap(arr[cnt+1],arr[n]);
			sort(arr+1,arr+n,cmp1);
			ans=max(arr[n].da+k+arr[n/2].da,ans);
		}
		
		printf("%lld\n",ans);
	}
	return 0;
}

```

---

