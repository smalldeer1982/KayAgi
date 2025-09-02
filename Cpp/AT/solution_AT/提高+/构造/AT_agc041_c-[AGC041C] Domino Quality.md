# [AGC041C] Domino Quality

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc041/tasks/agc041_c

$ N $ 行 $ N $ 列のマスからなる盤面を考えます。あなたはこの上にドミノ牌を何枚か置こうとしています。 各牌は一辺を共有する $ 2 $ マスの上に置き、各マスに乗せられる牌は $ 1 $ 枚までです。

盤面の各行について、その行の $ 1 $ マス以上を占める牌の数をその行のクオリティと定義します。 各列のクオリティも同様に定義します。

$ 1 $ 枚以上の牌の盤面への置き方であって、どの行のクオリティもどの列のクオリティとも等しくなるものを求めてください。あるいは、そのような置き方が存在しないことを検出してください。

## 说明/提示

### 制約

- $ 2\ \le\ N\ \le\ 1000 $

### Sample Explanation 1

どの行のクオリティも、どの列のクオリティも $ 2 $ です。

## 样例 #1

### 输入

```
6```

### 输出

```
aabb..
b..zz.
ba....
.a..aa
..a..b
..a..b```

## 样例 #2

### 输入

```
2```

### 输出

```
-1```

# 题解

## 作者：CYJian (赞：7)

这题妙啊

---

首先不难发现，$n<3$ 是无解的。

$n=3$ 可以非常方便地构造：

```plain
e..
e..
.ee
```

然后考虑更大的怎么办。

我们考虑构造多米诺数量为 $3$ 的矩阵：

$n=4$：

```plain
orzz
oree
eero
zzro
```

$n=5$：

```plain
orrzz
oe..e
ae..e
a.eez
oorrz
```

$n=6$：

```plain
oorrzz
.e.e.e
.e.e.e
e.e.e.
e.e.e.
oorrzz
```

$n=7$：

```plain
.oorrzz
oaee...
oa.a...
reea...
r...eaa
z...e.e
z...aae
```

打完这些表后，聪明的观众可能就会说：我会做了！

对于 $n \ge 8$ 的那些表格，我们只需要用上面四个凑就行了。将这些东西放在对角线上就可以了。

比如，对于 $n=9$，我们可以用一个 $n=4$ 和一个 $n=5$ 来凑：

```plain
orzz.....
oree.....
eero.....
zzro.....
....orrzz
....oe..e
....ae..e
....a.eez
....oorrz
```

更大的也用类似的方法凑就行了。大概就先将 $n \bmod 4$ 算出最后凑上哪一个，然后再一直凑 $4$ 直到凑到 $n$ 就行了。

$\rm Code$：

```cpp
const string S4[4] = {"abcc", "abdd", "ccab", "ddab"};
const string S5[5] = {"abbcc", "ad..a", "bd..a", "b.eez", "oorrz"};
const string S6[6] = {"oorrzz", ".a.b.c", ".a.b.c", "d.e.f.", "d.e.f.", "oorrzz"};
const string S7[7] = {".oorrzz", "oabb...", "oa.c...", "rddc...", "r...abb", "z...a.c", "z...ddc"};

char s[1010][1010];

inline void solve(int&n, int x) {
	if(x == 4)
		for(int i = 0; i < x; i++)
			for(int j = 0; j < x; j++)
				s[n + i][n + j] = S4[i][j];
	if(x == 5)
		for(int i = 0; i < x; i++)
			for(int j = 0; j < x; j++)
				s[n + i][n + j] = S5[i][j];
	if(x == 6)
		for(int i = 0; i < x; i++)
			for(int j = 0; j < x; j++)
				s[n + i][n + j] = S6[i][j];
	if(x == 7)
		for(int i = 0; i < x; i++)
			for(int j = 0; j < x; j++)
				s[n + i][n + j] = S7[i][j];
	n += x;
}

int main() {
	int n = ri;
	if(n <= 2) return puts("-1"), 0;
	if(n == 3) {
		puts("a..");
		puts("a..");
		puts(".bb");
		return 0;
	}
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			s[i][j] = '.';
	int x = n % 4, N = 1;
	if(x == 0) solve(N, 4);
	if(x == 1) solve(N, 5);
	if(x == 2) solve(N, 6);
	if(x == 3) solve(N, 7);
	while(N <= n) solve(N, 4);
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++)
			putchar(s[i][j]);
		puts("");
	}
	return 0;
}
```

---

## 作者：xxgirlxx (赞：2)

其实这题的思路挺好想的，就是把**大问题转化成小问题，再把小问题解决掉**，用这种思路的还有这两道题：

[这道是黄。](https://www.luogu.com.cn/problem/CF1352G)

[这道是黑。](https://www.luogu.com.cn/problem/P6892)

我们先来考虑怎么把大问题转化为小问题。

可以注意到，我们只将大的正方形的对角线分成几个小正方形的对角线，再让小正方形满足要求就行了。

可是该怎么分呢？

先打几个小样例吧！

$n=2$ 无解。

$n=3$ 解法如下：

```cpp
aab
b.b
baa
```

每行每列的骨牌数量为 $2$。

$n=4$ 解法如下：

```cpp
aabd
ccbd
dbcc
dbaa
```

每行每列的骨牌数量为 $3$。

$n=5$ 解法如下：

```cpp
aabba
b.cca
bc..b
ac..b
abbaa
```

每行每列的骨牌数量为 $3$。

$n=6$ 解法如下：

```cpp
aabcc.
b.b..c
baa..c
c..aab
c..b.b
.ccbaa
```

每行每列的骨牌数量为 $3$。

$n=7$ 解法如下：

```cpp
aab...c
b.b...c
baa...a
...aaba
...b.bc
...baac
ccaacc.
```

每行每列的骨牌数量为 $3$。

打住！先别急着去打 $n=8$ 的表，注意到 $4$ 到 $7$ 的骨牌数量都是 $3$，所以我们可以考虑把大问题化成若干个 $4$ 的问题 $+$ 另一个小问题，可有人就要问了：“可是除 $4$ 的余数是 $0,1,2,3$ 怎么办？”这就是这类题目很妙的一个地方了。

因为 $1,2$ 无解，$3$ 的骨牌数量不匹配，所以我们考虑将它们加上一个除数 $4$，这样余数就变成了 $4,5,6,7$。不仅都有解，骨牌数量还都匹配，就可以进行拆分了。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans[1010][1010],m;
int main(){
	cin>>n,m=n;
	if(n==2){
		cout<<"-1";
		return 0;
	}
	if(n==3){
		cout<<"aab\nb.b\nbaa";
		return 0;
	}
	for(int i=1;n;){
		if(n==4){
			ans[i][i]=ans[i][i+1]=ans[i+3][i+2]=ans[i+3][i+3]=1;
			ans[i][i+3]=ans[i+1][i+3]=ans[i+2][i]=ans[i+3][i]=2;
			ans[i][i+2]=ans[i+1][i+2]=ans[i+2][i+1]=ans[i+3][i+1]=3;
			ans[i+1][i]=ans[i+1][i+1]=ans[i+2][i+2]=ans[i+2][i+3]=4;
			break;
		}
		if(n==5){
			ans[i][i]=ans[i][i+1]=ans[i][i+4]=ans[i+1][i+4]=ans[i+3][i]=ans[i+4][i]=ans[i+4][i+3]=ans[i+4][i+4]=1;
			ans[i][i+2]=ans[i][i+3]=ans[i+1][i]=ans[i+2][i]=ans[i+2][i+4]=ans[i+3][i+4]=ans[i+4][i+1]=ans[i+4][i+2]=2;
			ans[i+1][i+2]=ans[i+1][i+3]=ans[i+2][i+1]=ans[i+3][i+1]=3;
			break;
		}
		if(n==6){
			ans[i][i]=ans[i][i+1]=ans[i+2][i+1]=ans[i+2][i+2]=ans[i+3][i+3]=ans[i+3][i+4]=ans[i+5][i+4]=ans[i+5][i+5]=1;
			ans[i][i+2]=ans[i+1][i]=ans[i+1][i+2]=ans[i+2][i]=ans[i+3][i+5]=ans[i+4][i+3]=ans[i+4][i+5]=ans[i+5][i+3]=2;
			ans[i][i+3]=ans[i][i+4]=ans[i+1][i+5]=ans[i+2][i+5]=ans[i+3][i]=ans[i+4][i]=ans[i+5][i+1]=ans[i+5][i+2]=3;
			break;
		}
		if(n==7){
			ans[i][i]=ans[i][i+1]=ans[i+2][i+1]=ans[i+2][i+2]=ans[i+3][i+3]=ans[i+3][i+4]=ans[i+5][i+4]=ans[i+5][i+5]=ans[i+2][i+6]=ans[i+3][i+6]=ans[i+6][i+2]=ans[i+6][i+3]=1;
			ans[i][i+2]=ans[i+1][i]=ans[i+1][i+2]=ans[i+2][i]=ans[i+3][i+5]=ans[i+4][i+3]=ans[i+4][i+5]=ans[i+5][i+3]=2;
			ans[i][i+6]=ans[i+1][i+6]=ans[i+4][i+6]=ans[i+5][i+6]=ans[i+6][i]=ans[i+6][i+1]=ans[i+6][i+4]=ans[i+6][i+5]=3;
			break;
		}
		ans[i][i]=ans[i][i+1]=ans[i+3][i+2]=ans[i+3][i+3]=1;
		ans[i][i+3]=ans[i+1][i+3]=ans[i+2][i]=ans[i+3][i]=2;
		ans[i][i+2]=ans[i+1][i+2]=ans[i+2][i+1]=ans[i+3][i+1]=3;
		ans[i+1][i]=ans[i+1][i+1]=ans[i+2][i+2]=ans[i+2][i+3]=4;
		n-=4,i+=4;
	}
	for(int i=1;i<=m;i++){
		for(int j=1;j<=m;j++){
			if(ans[i][j]==0)cout<<".";
			else{
				char b=ans[i][j]+'a'-1;
				cout<<b;
			}
		}
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：StayAlone (赞：1)

## 思路

另一篇题解写得非常清楚，补充一下就是 $n\geq 4$ 时一定可以通过一些 $4$ 拼起来，最后剩下一个，所以需要再处理 $5\sim 7$ 的情况。

但是那篇题解的写法我不好评价，这里提供一种更简洁的实现。

目前是最优解（虽然好像差别很小）。

[AC record](https://www.luogu.com.cn/record/102193868)
```cpp
int n; char ans[1010][1010];
vector <int> spl;

char mp[10][10][10] = {
	{}, {}, {}, {},
	{"orzz", "oree", "eero", "zzro"},
	{"orrzz", "oe..e", "ae..e", "a.eez", "oorrz"},
	{"oorrzz", ".e.e.e", ".e.e.e", "e.e.e.", "e.e.e.", "oorrzz"},
	{".oorrzz", "oaee...", "oa.a...", "reea...", "r...eaa", "z...e.e", "z...aae"},
};

il void upd(int x, int y, int p) {
	rep1(i, x, x + p - 1) rep1(j, y, y + p - 1) ans[i][j] = mp[p][i - x][j - y];
}

int main() {
	read(n);
	if (n < 3) return puts("-1"), 0;
	if (n == 3) return puts("e..\ne..\n.ee"), 0;
	rep1(i, 1, n) rep1(j, 1, n) ans[i][j] = '.';
	int m = n;
	while (m) {
		if (m >= 4) spl.eb(4), m -= 4;
		else spl[spl.size() - 1] += m, m = 0;
	}
	int nx = 1, ny = 1;
	for (auto v : spl) upd(nx, ny, v), nx += v, ny += v;
	rep1(i, 1, n) puts(ans[i] + 1);
	rout;
}

```

---

## 作者：bsdsdb (赞：0)

题意：在 $n\times n$ 的棋盘上摆多米诺骨牌，使得每行每列的牌数相等。

用 $P(n,c)$ 表示 $n\times n$，每行每列 $c$ 个是否有解。注意到 $P(a,c)\land P(b,c)\Rightarrow P(a+b,c)$，证：左上角摆 $a\times a$ 的，右下角摆 $b\times b$ 的。

又注意到我们可以如下构造出一些解：

```text
(3, 1):
1..
1..
.22

(4, 3):
1233
1244
5567
8867

(5, 3):
123..
123..
45566
4.788
997AA

(6, 3):
112233
445566
7.8.9.
7.8.9.
.A.B.C
.A.B.C

(7, 3):
1..2..3
1..2..3
.44.556
7..8..6
7..8..9
.AA.BB9
CCDDEE.
```

然后这道题就做完了。因为如果 $n\ge 8$，那我们可以在左上角构造一个 $(4,3)$ 的，然后在右下角构造 $(n-4,3)$ 的。注意对 $n=1,2,3$ 特判。

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
 
const ll MAXN = 1e3 + 5;

string a[10][10] = {
	{}, {}, {}, {
		string(),
		"a..",
		"a..",
		".aa"
	}, {
		string(),
		"0abcc",
		"0abdd",
		"0ccab",
		"0ddab"
	}, {
		string(),
		"0abc..",
		"0abc..",
		"0baabb",
		"0b.baa",
		"0aabcc"
	}, {
		string(),
		"0aabbaa",
		"0bbaabb",
		"0a.b.a.",
		"0a.b.a.",
		"0.a.a.a",
		"0.a.a.a"
	}, {
		string(),
		"0a..a..a",
		"0a..a..a",
		"0.aa.aab",
		"0a..a..b",
		"0a..a..c",
		"0.aa.aac",
		"0bbccdd."
	}
};

ll n;
char ans[MAXN][MAXN];

void fil(ll x, ll l) {
	for (ll i = 1; i <= l; ++i) {
		for (ll j = 1; j <= l; ++j) {
			ans[x + i - 1][x + j - 1] = a[l][i][j];
		}
	}
}

int main() {
	read(n);
	if (n <= 2) {
		puts("-1");
		return 0;
	}
	if (n == 3) {
		for (ll i = 1; i <= 3; ++i) {
			cout << a[3][i] << endl;
		}
		return 0;
	}
	fill(ans[0], ans[0] + sizeof ans, '.');
	for (ll i = 1; n - i + 1 >= 8; i += 4) {
		fil(i, 4);
	}
	fil(n - 4 - (n % 4) + 1, n % 4 + 4);
	for (ll i = 1; i <= n; ++i) {
		for (ll j = 1; j <= n; ++j) {
			putchar(ans[i][j]);
		}
		enter();
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

