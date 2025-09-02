# Two Arrays

## 题目描述

You are given two arrays $ a_1, a_2, \dots , a_n $ and $ b_1, b_2, \dots , b_m $ . Array $ b $ is sorted in ascending order ( $ b_i < b_{i + 1} $ for each $ i $ from $ 1 $ to $ m - 1 $ ).

You have to divide the array $ a $ into $ m $ consecutive subarrays so that, for each $ i $ from $ 1 $ to $ m $ , the minimum on the $ i $ -th subarray is equal to $ b_i $ . Note that each element belongs to exactly one subarray, and they are formed in such a way: the first several elements of $ a $ compose the first subarray, the next several elements of $ a $ compose the second subarray, and so on.

For example, if $ a = [12, 10, 20, 20, 25, 30] $ and $ b = [10, 20, 30] $ then there are two good partitions of array $ a $ :

1. $ [12, 10, 20], [20, 25], [30] $ ;
2. $ [12, 10], [20, 20, 25], [30] $ .

You have to calculate the number of ways to divide the array $ a $ . Since the number can be pretty large print it modulo 998244353.

## 样例 #1

### 输入

```
6 3
12 10 20 20 25 30
10 20 30```

### 输出

```
2```

## 样例 #2

### 输入

```
4 2
1 3 3 7
3 7```

### 输出

```
0```

## 样例 #3

### 输入

```
8 2
1 2 2 2 2 2 2 2
1 2```

### 输出

```
7```

# 题解

## 作者：BMTXLRC (赞：7)

首先观察到 $b_i$ 单调递增，即，我们能不能用 $\mathcal{O}(n)$ 左右的时间解决这个问题，而不是选择 DP。

考虑到其实对于每个 $b_i$，它“控制”的范围是有限的。设 $\min\limits_{i\to n}\{a_i\}=suf_i$，$suf_i$ 被称作 $b_j$ 可选的数的最大范围。

假设我们现在有一个序列 $a=\{80,80,10,40,40,40,20,25,30\},b=\{10,20,30\}$。

不难得到 $suf=\{10,10,10,20,20,20,20,25,30\}$。

我们首先看 $b_1=10$ 对答案的贡献，很显然 $a_1\sim a_3$ 必须都分到第一组，这是因为 $a_3$ 必须分到第一组，$a_3$ 假如分到第二组则第二组最小值必定小于 $b_2$。

接下来可以看到 $a_4\sim a_6$ 分到第一组还是第二组都无所谓，但是这里必须切一刀，也就是说我有四种切法可以将这三个 $40$ 分到第一组或第二组。（注：假设最多有 $k$ 个 $suf_i=b_j$，则我至少要留下一个 $suf_i$ 给 $b_j$ 这一组，于是上一组与这一组可以被切开的方案数就是 $k-1+1=k$）

因为 $a_7=20$，所以 $a_7$ 必须分到第二组，此时可以发现 $a_8=25$ 必须分到第二组来，所以第二组的贡献是 $1$。

最后我们就得到答案为 $4$。

接下来对于结论 $ans=\prod\limits_{i=2}^m\operatorname{cnt}(b_i)$ 的推导，对于每一组的方案数，其最多可以扩张到下一组的最后一个最小值的前一位，不理解可以看刚刚的例子，这么多数的切割方案就是 $\operatorname{cnt}(b_{i+1})$。我们再举个例子：

$$
10,10,10,10,12,12,15,15,15,15,15
$$

对于上面的 $suf$ 序列，如果 $b=\{10,15\}$ 的话，首先可以得到那两个 $12$ 必须被分到前一组 $b_1=10$，因为他们被分到 $b_2=15$ 会拉低最小值。剩下的五个 $15$ 中，至少要留一个 $15$ 给第二组，故剩下四个 $15$ 可以切 $5$ 刀，即 $b_1$ 与 $b_2$ 共同能带来 $5$ 种方案。

所以就是说，相邻的两组答案为后一组 $suf_i=b_j$ 的 $suf_i$ 个数。

提醒：

1. 一定要开 `long long`
2. 第一组 $b_1$ 判的时候要看 $suf_1=b_1$，如果不符合马上答案为 $0$，你可以理解为，若小于，则我就是取再多数给第一组，最小值也不会是 $b_1$，若大于，则我无论取多少数都取不到 $b_1$。

查找 $suf_i=b_j$ 个数时，由于 $suf_i$ 的值域很广，可以用 `map` 做桶，总时间复杂度 $\mathcal{O}(n\log n)$。

代码如下：

```cpp
//CF1366-E
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
const int mod=998244353;
int a[N],b[N],n,m,suf[N],ans=1;
map<int,int> f;
signed main(){
    scanf("%lld %lld",&n,&m);
    for(register int i=1;i<=n;i++) scanf("%lld",&a[i]),suf[i]=2e9;
    suf[n+1]=2e9;
    for(register int i=n;i>=1;i--){
        suf[i]=min(a[i],suf[i+1]);//后缀最小
        f[suf[i]]++;
    }
    scanf("%lld",&b[1]);
    if(suf[1]!=b[1]){
        printf("0");
        return 0;
    }
    for(register int i=2;i<=m;i++){//乘法原理
        scanf("%lld",&b[i]);
        ans=(ans%mod*f[b[i]]%mod)%mod;
    }
    printf("%lld",ans);
}
```

---

## 作者：Caicz (赞：5)

本题的关键在于 `b严格单调递增` 这个条件，有了这个条件，很显然对于 $a[i]$ 数组当前位置 $i$ ，如果我们要分给 $b[j]$ ，我们必须满足 $i$ 这个位置的后缀最小值等于 $b[j]$ ，于是我们将 $a[i]$ 变为储存其后缀最小值的数组，题目就相当于在 $a[i]$ 上划 $m-1$ 刀，分为 $m$ 个区块，对于第 $j$ 刀，每刀的位置可以在任意 $a[i]=b[j+1]$ 前面，可以通过乘法原理统计答案

```cpp
#include<stdio.h>
#include<iostream>
#include<cstring>
#include<math.h>
#include<time.h>
#include<map>
#include<stdlib.h>
#include<algorithm>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int maxn=200005;
const int inf=0x3f3f3f3f;
const int p=998244353;
int n,m,a[maxn],tmp[maxn];
int cnt[maxn];
ll ans=1;
map<int,int>mp;
#define getchar() (_1==_2&&(_2=(_1=_3)+fread(_3,1,1<<21,stdin),_1==_2)?EOF:*_1++)
char _3[1<<21],*_1=_3,*_2=_3;
inline int read(void)
{
	int num,sign=1;char c;
	while(!isdigit(c=getchar()))if(c=='-')sign=0;num=c-'0';
	while(isdigit(c=getchar()))num=(num<<1)+(num<<3)+c-'0';
	return sign?num:-num;
}

signed main(void)
{
#ifndef ONLINE_JUDGE
	freopen("text.in","r",stdin);
#endif
	n=read(),m=read(),a[n+1]=inf;
	for(register int i=1;i<=n;++i)a[i]=read();
	for(register int i=n;i;--i)a[i]=min(a[i],a[i+1]),++mp[a[i]];
	n=read();
	if(a[1]!=n)puts("0"),exit(0);
	for(register int i=2;i<=m;++i)ans=ans*mp[read()]%p;
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：123zbk (赞：2)

## 解题思路
考虑在哪里切割 $a$。 

首先，对于每一个 $b_i$，我们必须在 $a$ 数组最后一个等于 $b_i$ 的数之后切割。

比如下面这组数据：

$a_i:12,10,20,10,25,20,25,25,30,35,30$

$b_i:10,20,30$

对于 $b_1=10$，我们只能在第二个 $10$ 出现之后切割。否则 $10$ 就会出现在下一次的分组中，而因为 $b_i$ 单调递增，所以 $10$ 一定会成为下一组的最小值，而不是 $20$。

其次，考虑 $b_i$ 最后能在哪里切。显然，在最后一个 $b_{i+1}$ 出现之前都可以。只要给下一组留一个 $b_{i+1}$ 当最小值就足够了。

还是看那组数据，对于 $b_2=20$，只要在最后一个 $30$ 之前的都可以。

综上所述，对于每一个 $b_i$，只要在 $a$ 数组中最后一个 $b_i$ 之后，最后一个 $b_{i+1}$ 出现之前切割都可以。

所以我们给 $a$ 数组维护一个后缀最小值，此时：

$a_i:10,10,10,10,20,20,25,25,30,30,30$

$b_i:10,20,30$

根据前面的分析，对于每一个 $b_i$，在现在的 $a$ 数组中每一个 $b_{i+1}$ 前切割都合法，有$num[b_{i+1}]$ 种情况。最后根据乘法原理将所有 $num$ 值乘起来即可。

注意特判一下，当后缀最小值的 $a_1$ 和 $b_1$ 不等时无解。

## code
```cpp
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const int maxn=2e5+5,mod=998244353;
int n,m,t,a[maxn];
ll ans=1;
map <int,int> mp;
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
    }
    a[n+1]=1e9+5;
    for(int i=n;i>=1;i--)
    {
        a[i]=min(a[i],a[i+1]);
        mp[a[i]]++;
    }
    cin>>t;
    if(a[1]!=t)
    {
        puts("0");
        exit(0);
    }
    for(int i=2;i<=m;i++)
    {
        int x;
        scanf("%d",&x);
        ans=ans*mp[x]%mod;
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：bsdsdb (赞：0)

题意：有多少种划分 $\{a_n\}$ 的方式使得第 $k$ 段的最小值等于 $b_k$，保证 $\{b_m\}$ 严格递增。

提示：

1. 考虑以下样例：
  ```text
  12 3
  1 2 1 3 2 4 3 4 5 6 5 6
  1 3 5
  ```
2. 对 $a$ 做后缀 min。

令 $c_i:=\min_{j=i}^na_i$，则对于 $c$ 中一段连续的 $i$，如果 $i\notin b$，那么他一定属于前面一段（即第「最大的 $j$ 使得 $b_j<i$」段），不对答案贡献；否则对答案贡献「这一段的长度」，因为前面一段可以要左边的 $[0,l-1]$ 个，相应地让后面一段拿 $[1,l]$ 个。双指针即可。特别的，如果 $\exist i:b_i\notin c$，那么答案为 $0$，因为在 $a$ 中即使有 $b_i$（如果没有直接得证）后面也一定有比他小的，又因为 $b$ 递增，所以选不出合法的划分。

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

const ll MAXN = 2e5 + 5, mod = 998244353;

ll n, m, a[MAXN], b[MAXN], sufm[MAXN];

int main() {
	read(n), read(m);
	for (ll i = 1; i <= n; ++i) {
		read(a[i]);
	}
	sufm[n + 1] = inf;
	for (ll i = n; i; --i) {
		sufm[i] = min(sufm[i + 1], a[i]);
	}
	for (ll i = 1; i <= m; ++i) {
		read(b[i]);
	}
	if (b[1] != sufm[1]) {
		write(0), enter();
		return 0;
	}
	ll cur1 = 1, cur2 = 1, ans = 1;
	while (cur2 <= m) {
		ll precur;
		while (sufm[cur1] < b[cur2]) {
			++cur1;
		}
		if (sufm[cur1] != b[cur2]) {
			write(0), enter();
			return 0;
		}
		precur = cur1;
		while (sufm[cur1 + 1] == b[cur2]) {
			++cur1;
		}
		if (cur2 > 1) {
			(ans *= cur1 - precur + 1) %= mod;
		}
		++cur1, ++cur2;
	}
	write(ans), enter();
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

## 作者：2huk (赞：0)

> - 给定一个长为 $n$ 的数组 $a$ 和一个长为 $m$ 的数组 $b$，你要把 $a$ 分割为连续的 $m$ 段使得第 $i$ 段中的最小值恰为 $b_i$ ，求总方案数。保证 $b$ 严格单调递增。
> - $m \le n \le 2 \times 10^5$，$a_i, b_i \le 10^9$。

首先特判掉 $\min a \ne b_1$ 无解。

思考如果 $a_j < b_i$，那么 $j$ 一定会被分到 $1 \sim i - 1$ 中的某个组。因此 $a_{j - 1}, a_{j - 2}, \dots$ 等之前的也一定会被分到 $[1, i - 1]$ 的组中。

这启发我们求出 $a$ 的后缀最小值 $c_i = \min_{j=i}^n a_j$。若 $c_{l_i - 1} \ne b_i = c_{l_i} = c_{l_{i+1}} = \dots = c_{r_i} \ne c_{r_i + 1}$，那么我们可以在 $l_i \sim r_i$ 中任意一个位置结束第 $i$ 段。令  $l_i \sim r_i$ 的长度为 $t_i$，即 $b_i$ 在 $c$ 中出现了 $t_i$ 次，那么答案为：
$$
\sum_{i=2}^n t_i
$$

![](https://cdn.luogu.com.cn/upload/image_hosting/r244rzpp.png)

```cpp
int n, m, a[N], b[N], suf[N];
map<int, int> cnt;

void Luogu_UID_748509() {
	fin >> n >> m;
	for (int i = 1; i <= n; ++ i ) fin >> a[i];
	for (int i = 1; i <= m; ++ i ) fin >> b[i];
	
	suf[n] = a[n], ++ cnt[a[n]];
	for (int i = n - 1; i; -- i ) {
		suf[i] = min(a[i], suf[i + 1]);
		++ cnt[suf[i]];
	}
	
	if (suf[1] != b[1]) puts("0");
	else {
		int res = 1;
		for (int i = 2; i <= m; ++ i ) res = (ll)res * cnt[b[i]] % P;
		fout << res;
	}
}
```

---

