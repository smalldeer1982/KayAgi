# No Palindromes

## 题目描述

[Christopher Tin ft. Soweto Gospel Choir - Baba Yetu](https://youtu.be/d4iOF4yoNQw)

ඞ



You are given a string $ s $ consisting of lowercase Latin characters. You need to partition $ ^\dagger $ this string into some substrings, such that each substring is not a palindrome $ ^\ddagger $ .

 $ ^\dagger $ A partition of a string $ s $ is an ordered sequence of some $ k $ strings $ t_1, t_2, \ldots, t_k $ , such that $ t_1 + t_2 + \ldots + t_k = s $ , where $ + $ here represents the concatenation operation.

 $ ^\ddagger $ A string $ s $ is considered a palindrome if it reads the same backwards as forwards. For example, $ \mathtt{racecar} $ , $ \mathtt{abccba} $ , and $ \mathtt{a} $ are palindromes, but $ \mathtt{ab} $ , $ \mathtt{dokibird} $ , and $ \mathtt{kurosanji} $ are not.

## 说明/提示

In the first test case, since $ \mathtt{sinktheyacht} $ is already non-palindrome, the partition $ [\mathtt{sinktheyacht}] $ is valid.

In the second test case, as any substring of the string $ s $ is palindrome, there are no valid partitions.

In the third test case, another valid partition is $ [\mathtt{uw},\mathtt{uo}, \mathtt{wou}, \mathtt{wu}] $ .

## 样例 #1

### 输入

```
3
sinktheyacht
lllllllll
uwuowouwu```

### 输出

```
YES
1
sinktheyacht
NO
YES
3
uw uow ouwu```

# 题解

## 作者：Eraine (赞：9)

编号：CF1951E

tag：贪心，字符串

难度：*2040（$\texttt{Clist}$ 数据）

~~我们 OP 是这样的！！！~~

注意两种特殊情况，一种是整串都为同一个字符则输出 $\texttt{NO}$，一种是原串不是回文串则输出 $\texttt{YES}$。

剩下的情况只能是回文串，且不是 **整串都为同一个字符**。

令 $s_1=\texttt{a}$，则 $s_n=\texttt{a}$。不失一般性。

> Lemma 1 $s[2\dots n]$ 为非回文串。

证明：

假设其为回文串，则 $s_2=s_n=\texttt{a}$。

由于 $s$ 为回文串，所以 $s_{n-1}=s_2=\texttt{a}$。

依此类推，$\forall i\in [1,n],s_i=\texttt{a}$，不满足条件，得证。

拓展到 $i$，我们可以得到：

> Lemma 2 若 $\forall j\in[1,i]$ 有 $s[1,j]$ 为回文串，则 $s[j+1,n]$ 为非回文串。

证明方法与 $\text{Lemma 1}$ 类似，就不细讲了。

显然有：

> Lemma 3 不存在一个 $i$ 使得 $\forall j\in[1,i]$ 有 $s[1,j]$ 为回文串且 $i\gt\lfloor\frac{n}{2}\rfloor$。

证明显然。若存在则序列变为 **整串都为同一个字符**。

当 $n$ 为奇数时，若 $i=\frac{n-1}{2}$ 满足而 $s_{\frac{n+1}{2}}=\texttt{b}$ 时显然无解。

剩余情况为 $i\le \frac{n-2}{2}$。显然 $i+1$ 不可能作为 $s[1,n]$ 的中点或中点的右部分。

假设 $\forall j\in[1,i]$ 有 $s[1,j]$ 为回文串，$s[1,i+1]$ 为非回文串。

若 $s[i+2,n]$ 为非回文串，则直接输出断点 $(i+1,i+2)$ 即可。

若 $s[i+2,n]$ 为回文串，设 $s_{i+1}=\texttt{b}$。

分两种情况讨论。当 $i=1$ 时，显然序列为 $s=\texttt{aba\dots aba}$。很容易发现这种情况无解。当 $i\gt 1$ 时，显然序列为 $k$ 组 $i$ 个 $\texttt{a}$ 和 $k-1$ 组 $\texttt{b}$ 交替拼接。由于 $i+1$ 只能是字符串区间 $[1,n]$ 的左部分位置，则 $k\ge 3$。显然可以构造 $s[1\dots i+2],s[i+3\dots n]$。且保证有解。

以上将所有情况讨论完毕，发现若有解绝对存在一种解使得分割段数 $\le 2$。

对于段数为 $1$ 的情况暴力判断是否为回文串。对于段数为 $2$ 的情况需要处理出 $s[1\dots i]$ 和 $s[i\dots n]$ 是否为回文串。这里实现用 Manacher。

$\Theta(\sum n)$。

[submission](https://codeforces.com/contest/1951/submission/255349843)

若有误请指出。虚心接受您的意见。

---

## 作者：yzc358230151 (赞：4)

# CF1951E

- - -

## 题意简述

划分给定字符串，使每一段均不回文或报告无解，多组数据。

## 分析

### 猜结论

非回文串的答案显然。

对于回文串，显然至少划分为 $2$ 段。

通过自行举例等方式可以猜想若有解存在一种解使得原串划分为 $2$ 段。

### 证明

**假设法**。

假设存在某个回文串 $S$（下标由 $1$ 开始，长度为 $n$），它有解但至少要划分为 $k$ 段 $(k \ge 3)$。

分类讨论：

1. 假设 $k=3$，一种解中 $S$ 被划分为 $S[1..x],S[x+1\dots y],S[y+1\dots n]$。

那么：

- 划分出的串都不回文，即 $S[1..x],S[x+1\dots y],S[y+1\dots n]$ 不回文。

> 这可以表示为以下三个式子：
> 
> $$\exist 0\le i\le x-1,S[1+i]\neq S[x-i]$$
> 
> $$\exist 0\le i\le y-x-1,S[x+1+i]\neq S[y-i]\space (1)$$
> 
> $$\exist 0\le i\le n-y-1,S[y+i+1]\neq S[n-i]$$

- 合并任意两个串，得到的串一定回文，即 $S[1\dots y],S[x+1\dots n]$ 不回文。

> 否则合并后得到划分为 $2$ 段的方案，与假设矛盾。
> 
> 该性质同样可以表示为以下两个式子：
> 
> $$\forall 0\le i\le y-1,S[1+i]=S[y-i]\space (2)$$
> 
> $$\forall 0\le i\le n-x-1,S[x+1+i]=S[n-i]\space (3)$$

- 已经假设 $S$ 为回文串。

> 式子表示：
> 
> $$\forall 0\le i\le n-1,S[1+i]=S[n-i]\space (4)$$

若我们合并上述的 $(2)(3)(4)$ 式，可得：

$$\forall 0\le i\le \min(y-1,n-x-1,n-1),S[1+i]=S[y-i]=S[x+1+i]=S[n-i]$$

而分析上述字符串长度或分析 $x,y,n$ 大小可知，

$$y-x\le \min(y,n-x,n)$$

所以

$$y-x-1\le \min(y-1,n-x-1,n-1)$$

所以

$$\forall 0\le i\le y-x-1,S[1+i]=S[y-i]=S[x+1+i]=S[n-i]$$

我们发现，该式与前述 $(1)$ 式矛盾，故假设不成立，$k\neq 3$。

2. 假设 $k>3$，一种解中划分开头的 $3$ 段为 $S[1\dots x],S[x+1\dots y],S[y+1\dots z]\space(z<n)$，对 $S[1\dots z]$ 作类似的分析也可得假设不成立，$k \le 3$。

综上所述，原假设不成立，一定存在一种解使得回文串 $S$ 被划分为 $2$ 段。

### 代码实现

知道了这一点后，利用 Manacher 判断回文，枚举断点即可以 $O(\sum n)$ 通过本题。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define gc getchar
#define pc putchar
#define mkp make_pair
#define pb push_back
//typedef long long ll;
char str[1000010],str2[2000020];
int n,n2,r[2000020];
void huiwen(){
	r[1]=1;
	int box=1;
	for(int i=2;i<=n2;++i){
		int rr=i-box+1;
		if(rr<=r[box]){
			r[i]=min(r[box-rr+1],r[box]-rr+1);
		}else
			r[i]=1;
		while(i-r[i]>=1&&i+r[i]<=n2&&str2[i+r[i]]==str2[i-r[i]])
			++r[i];
		if(i+r[i]-1>box+r[box]-1)
			box=i;
	}
}
bool chk(int L,int R){
	int LL=(L<<1)-1,RR=(R<<1)-1;
	int mid=(LL+RR)>>1;
//	printf("checking %d->%d,on str2:%d->%d\n",L,R,LL,RR),
//	printf("mid=%d,dis=%d,radius=%d\n",mid,RR-mid+1,r[mid]);
	return RR-mid+1>r[mid];
}
void doit(){
	scanf("%s",str+1),
	n=strlen(str+1),
	n2=(n<<1)-1;
	for(int i=1;i<=n2;++i)
	if(i&1)
		str2[i]=str[(i+1)>>1];
	else
		str2[i]='#';
	huiwen();
	if(chk(1,n)){
		fputs("YES\n1\n",stdout),
		fputs(str+1,stdout),
		fputs("\n",stdout);
		return;
	}else for(int i=2;i<=n;++i)
	if(chk(1,i-1)&&chk(i,n)){
		fputs("YES\n2\n",stdout);
		char tmpch='\0';
		swap(str[i],tmpch),
		fputs(str+1,stdout),
		fputs(" ",stdout),
		swap(str[i],tmpch),
		fputs(str+i,stdout),
		fputs("\n",stdout);
		return;
	}
	fputs("NO\n",stdout);
}
signed main(){
	int T;
	for(scanf("%d",&T);T;--T)
		doit();
	return 0;
}
```

## 后记

~~CF的题真的很容易被搬啊。~~

考试做到该题，听讲评和看题解发现思路大有不同，遂写题解。

---

## 作者：bsdsdb (赞：2)

题意：给定字符串 $s$，如果可能，将字符串划分成若干个不回文的子串。

下文使用 `A` 来表示 `aa...a`，定义字符串 $A$「形如」$B$ 为：$|A|=|B|\land\forall 1\le i,j\le |A|,[A_i=A_j]=[B_i=B_j]$.

如果原串不回文，直接输出原串。如果原串形如 `A`，肯定不可能。否则，令 $c:=\min\{x\mid s_x\neq   s_1\}$，那么如果 $s_{[c+1,|s|]}$ 不回文，输出 $s_{[1,c]},s_{[c+1,|s|]}$ 即可。

否则，$s$ 一定形如 `AbAbA...AbA`，证：

![](https://www.luogu.com.cn/fe/api/problem/downloadAttachment/21n28mqn)

分三种情况：

- `A` 长度为 $1$：即 $s$ 形如 `aba...ba`，证明无合法划分：`a` 和 `aba` 显然不行；如果 $s$ 长度为 $x$，且一切长度小于 $x$ 长度的 `aba...ba` 都不行，那么假如 $s$ 可以被划分，最左边一段长度为 $y$，则有 $y\equiv 0\pmod 2$，那么说明长度为 $x-y$ 的有合法划分，矛盾。
- $s$ 形如 `AbA`：无合法划分。如果能划分，必有一段形如 `A`，矛盾。
- 否则，$s_{[1,c+1]}$ 和 $s_{[c+2,|s|]}$ 都不是回文串。

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

string s;

bool ispal(ll l, ll r) {
	for (ll i = l; i <= r; ++i) {
		if (s[i] != s[l + r - i]) {
			return 0;
		}
	}
	return 1;
}

void init() {}
int mian() {
	read(s);
	set<char> cc;
	for (char c : s) {
		cc.emp(c);
	}
	if (cc.size() == 1) {
		puts("NO");
		return 0;
	}
	if (!ispal(0, s.size() - 1)) {
		puts("YES"), puts("1"), puts(s.c_str());
		return 0;
	}
	ll cur = 0;
	for (; cur < s.size(); ++cur) {
		if (s[cur] != s[0]) {
			break;
		}
	}
	if (!ispal(cur + 1, s.size() - 1)) {
		puts("YES"), puts("2");
		for (ll i = 0; i <= cur; ++i) {
			putchar(s[i]);
		}
		space();
		for (ll i = cur + 1; i < s.size(); ++i) {
			putchar(s[i]);
		}
		enter();
		return 0;
	}
	if (cur * 2 + 1 == s.size() || cur == 1) {
		puts("NO");
		return 0;
	}
	puts("YES"), puts("2");
	for (ll i = 0; i <= cur + 1; ++i) {
		putchar(s[i]);
	}
	space();
	for (ll i = cur + 2; i < s.size(); ++i) {
		putchar(s[i]);
	}
	enter();
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
```

---

## 作者：fish_love_cat (赞：2)

省流：屎山。

![](https://cdn.luogu.com.cn/upload/image_hosting/ncxq72am.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/t1cxa5mk.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/37e5gvgn.png)

调死了，开心。

---

注：本文下标均从 $1$ 开始，下文可能不会特地声明。

---

我们把字符串转化成一个一个由相同字母组成的块，记录块长，存进一个 `vector` 里，我们把第 $i$ 块的块长称作 $x_i$。

注意到相邻块代表的字母一定不同，所以把两个块接在一起肯定不是回文串。那么我们可以得出当块数为偶数时一定可解，将两个块接在一起即可。

那么剩下的情况块数均为奇数，我们考虑如何转化为偶数。

我们有如下四条结论可以帮助转化。

---

**结论一**：如果存在 $x_i \ne x_{i+2}$ 或者这两者代表的字母不同，那么把 $x_i,x_{i+1},x_{i+2}$ 所代表的块连接起来一定不是回文串。

---

证明：

设 $x_i,x_{i+1},x_{i+2}$ 所代表的块连接起来是回文串 $s$，且下标从 $1$ 开始。

同时我们设 $x_i,x_{i+1},x_{i+2}$ 所代表的块分别由若干 $a$，若干 $b$，若干 $c$ 所组成，且在 $s$ 中的位置分别是 $s_1$ 到 $s_{x_i}$，$s_{x_i+1}$ 到 $s_{x_i+x_{(i+1)}}$，$s_{x_i+x_{(i+1)}+1}$ 到 $s_{x_i+x_{(i+1)}+x_{(i+2)}}$，且 $a\ne b,b\ne c$。

显然当 $a \ne c$ 时结论成立。

接下来处理 $a=c$ 的情况。这些情况满足 $x_i\ne x_{i+2}$。

依据上面我们有 $|s|=x_i+x_{i+1}+x_{i+2}$。

当 $x_i<x_{i+2}$ 时：

那么 $s_{x_i+1} = s_{|s|-x_i} = s_{x_{(i+1)}+x_{(i+2)}}$。

因为 $x_i<x_{i+2}$。

所以 $s_{x_{(i+1)}+x_{(i+2)}}=c$。

因为 $s_{x_i+1}=b,b\ne c$。

所以 $s_{x_i+1}\ne s_{x_{(i+1)}+x_{(i+2)}}$。

自相矛盾，所以 $s$ 不是回文串。

当 $x_i>x_{i+2}$ 时：

因为 $s$ 是回文串，所以设 $c$ 是反转后的 $s$。

此时有 $c=s$。

那么对于 $c$ 满足 $x_i<x_{i+2}$。

所以 $c$ 不是回文串。

由此可知 $s$ 也不是回文串。

综上，结论成立。

~~怎么这段这么长……~~

---

**结论二**：如果存在 $x_i \ne x_{i+2}$ 或者这两者代表的字母不同，那么把 $x_{i-1},x_i,x_{i+1},x_{i+2},x_{i+3}$ 所代表的块连接起来的 $s$ 一定不是回文串。

---

证明：

设 $s$ 是回文串，五个块的成分分别是若干个 $a$，若干个 $b$，若干个 $c$，若干个 $d$，若干个 $e$。

如果 $b \ne d$ 结论显然成立。

那么设 $a=e$。

首先由结论一可以知道，$s_{x_{(i-1)}+1}$ 到 $s_{x_{(i-1)}+x_i+x_{(i+1)}+x_{(i+2)}}$ 不是回文串。

因为 $e \ne d,a\ne b$。

所以 $e\ne b,a\ne d$。

那么显然没法补齐中间不是回文串的部分。

所以 $s$ 不是回文串。

综上，结论成立。

---

对于一个不存在 $x_i \ne x_{i+2}$ 或者这两者代表的字母不同的字符串 $s$，也就是说这个字符串形如 `AB...A`，其中 $A,B$ 各代表一类块。

**结论三**：在满足上述条件且 $B>1$ 时，我们可以把第二个 $B$ 的中间作为分割，这样割出来的两个串均不回文。

**结论四**：在满足上述条件且 $A>1$，块数大于 $1$ 时，我们可以把第三个 $A$ 的中间作为分割，这样割出来的两个串均不回文。

---

证明：

结论三的割法使两个串头尾字符不一，显然不回文。

结论四的割法使两个串头尾长度不一，根据结论一的证明，同理可得结论四也是正确的。

---

那我们应该怎么构造呢？

首先找出一个满足 $x_i \ne x_{i+2}$ 或者这两者代表的字母不同的 $i$。

如果不存在这么一个 $i$，检查是否满足结论三结论四的条件，满足的照做即可。不满足的显然不可做，返回无解。

剩下的情况把 $i$ 按照情况一来做，其余部分是偶数，按照初始情况两两一组即可。

但是这不对。~~废话那我要情况二干嘛？~~

当 $i$ 是偶数时，你会发现左右都是奇数，假了。

所以此时按照结论二做即可，因为是五合一，所以刚刚好。

然后你就可以开始调屎山了。

---

调试之你可能会犯的错误：

越界，如忘记判队列 `ans.empty()`。这是 UB 的重要原因，CF 不会返回 RE 返回 WA on #2 就很神奇。

多测注意清空，不然见祖宗。

变量不重名。~~不过这好像没什么关系。~~

**还有就是虽然本文下标从 $1$ 开始但是注意 `string` 下标从 $0$ 开始！！！！**

上述问题不要问我怎么知道的，问就是第一张图。

---

[AC 代码](https://www.luogu.com.cn/paste/4ozje9em)。

---

拜谢 @[tanglb](https://www.luogu.com.cn/user/976073) 帮我调题！

---

## 作者：Priestess_SLG (赞：1)

被 $2400$ 击败了，写点水题提提信心（

考虑什么时候是不合法的。显然，此时 $S$ 串必须为回文串，且必须满足下面三个条件之一：

+ $S$ 串内所有元素均相同。
+ $S$ 串内只有两个不同的字符，$2\nmid |S|$ 且所有奇数位，偶数位的字符分别相同。
+ $S$ 串内只有两个不同的字符，$2\nmid |S|$ 且除 $S$ 的第 $\frac{|S|+1}2$ 位以外所有字符均相同。

可以证明，上述情况均不存在合法的划分。

证明：

+ 对于情况 $1$，显然无论怎么划出其任意子串，该子串所有字符均相同，必为回文串。因此无法划分。
+ 对于情况 $2$，显然若要划出一个前缀，则该前缀的长度必须为偶数才能满足条件，此时剩余部分仍为一个前缀，因此可以划分的部分的长度一定为偶数。而串的总长度为奇数，因此无法划分。
+ 对于情况 $3$，显然若要划出一个前缀，必包含 $S$ 串的第 $\frac{|S|+1}2$ 位字符，而剩下的部分为情况 $1$，因此无法划分。

对于剩下的情况，若串本身不为回文串，则答案可以为 $1$，即整串。

还剩下若干种情况，容易发现，此时同时不满足上面所有情况的串，必然存在 $2\le t\le n$ 使得 $S_{[1,t-1]}$ 和 $S_{[t,n]}$ 都为非回文串。因此做完了，判断串是否回文可以用正反哈希维护。

```cpp
#pragma GCC optimize(3, "Ofast", "inline") 
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1000010;
const int ba1 = 131, ba2 = 13331, m1 = 998244353, m2 = 1e9 + 9;
char s[N];
int h1[N], h2[N], h3[N], h4[N], b1[N], b2[N], pre[N][26], n;
int get(int *h, int *b, int m, int l, int r) {
    return (h[r] - h[l - 1] * b[r - l + 1] % m + m) % m;
}
int chk(int l, int r) {
    return get(h1, b1, m1, l, r) == get(h3, b1, m1, n - r + 1, n - l + 1) &&
           get(h2, b2, m2, l, r) == get(h4, b2, m2, n - r + 1, n - l + 1);
}
signed main() {
    int T;
    cin >> T;
    b1[0] = b2[0] = 1;
    for (int i = 1; i < N; ++i) {
        b1[i] = b1[i - 1] * ba1 % m1;
        b2[i] = b2[i - 1] * ba2 % m2;
    }
    while (T--) {
        scanf("%s", s + 1);
        n = strlen(s + 1);
        for (int i = 1; i <= n; ++i) {
            h1[i] = (h1[i - 1] * ba1 + s[i]) % m1;
            h2[i] = (h2[i - 1] * ba2 + s[i]) % m2;
            h3[i] = (h3[i - 1] * ba1 + s[n - i + 1]) % m1;
            h4[i] = (h4[i - 1] * ba2 + s[n - i + 1]) % m2;
        }
        if (!chk(1, n)) {
            cout << "YES\n1\n";
            puts(s + 1);
        }
        else {
            for (int i = 1; i <= n; ++i) {
                for (int j = 0; j < 26; ++j) pre[i][j] = pre[i - 1][j];
                ++pre[i][s[i] - 'a'];
            }
            int mx = 0;
            for (int i = 1; i <= 26; ++i)
                mx = max(mx, pre[n][i - 1]);
            if (mx == n) cout << "NO\n";
            else {
                int cnt = 0;
                for (int i = 1; i <= 26; ++i)
                    if (pre[n][i - 1]) ++cnt;
                if (cnt == 2) {
                    int ok = 1;
                    for (int i = 1; i <= n; ++i) {
                        int o = 2 - (i & 1);
                        if (s[o] != s[i]) {
                            ok = 0;
                            break;
                        }
                    }
                    if (ok) cout << "NO\n";
                    else {
                        if (n & 1) {
                            int mid = n / 2 + 1;
                            if (pre[n][s[mid] - 'a'] == 1) {
                                cout << "NO\n";
                                continue;
                            }
                        }
                        cout << "YES\n";
                        for (int i = 2; i <= n; ++i)
                            if (!chk(1, i - 1) && !chk(i, n)) {
                                cout << "2\n";
                                for (int j = 1; j < i; ++j) cout << s[j];
                                cout << ' ';
                                for (int j = i; j <= n; ++j) cout << s[j];
                                cout << '\n';
                                break;
                            }
                    }
                } else {
                    cout << "YES\n";
                    for (int i = 2; i <= n; ++i)
                        if (!chk(1, i - 1) && !chk(i, n)) {
                            cout << "2\n";
                            for (int j = 1; j < i; ++j) cout << s[j];
                            cout << ' ';
                            for (int j = i; j <= n; ++j) cout << s[j];
                            cout << '\n';
                            break;
                        }
                }
            }
        }
    }
}
```

---

## 作者：破壁人罗辑 (赞：1)

题目传送门：[洛谷](https://www.luogu.com.cn/problem/CF1951E)/[Codeforces](https://codeforces.com/contest/1951/problem/E)

## 题意简述

将一个字符串分割成若干个非空连续子串，使得每一个子串都不是回文字符串。

## 解题思路

把字符串视为“字符+连续相同字符数量”的组合的形式，例如 `lluoggu` 在此规则下被视为 `l2u1o1g2u1`，`aaabbcccdd` 在此规则下被视为 `a3b2c3d2`。

如果一个字符串正好含有偶数个“字符+连续相同字符数量”组合，那么这个字符串一定不是回文字符串，那么直接输出本身即可。

如果一个字符串只有一个“字符+连续相同字符数量”组合，那么它的任一子串均为回文字符串，输出 `NO`。

如果一个字符串含有除 $1$ 以外的奇数个“字符+连续相同字符数量”组合，那么分两大类讨论：

- 如果存在一个“字符+连续相同字符数量”组合与一个和它相隔一个组合的“字符+连续相同字符数量”组合不同，假设是第 $x$ 个和第 $x+2$ 个组合不同，我们分两小类讨论：

- - 如果 $x$ 是奇数，那么我们把 $x$ 之前的和 $x+2$ 之后的组合全部两两配对输出，把第 $x,x+1,x+2$ 个组合结合输出。例如 `acbcacaca`，$x=3$，我们就输出 `ac`,`bca`,`ca` 和 `ca` 四个字符串。

- - 如果 $x$ 是偶数，那么我们把 $x-1$ 之前的和 $x+3$ 之后的组合全部两两配对输出，把第 $x-1,x,x+1,x+2,x+3$ 个组合结合输出。例如 `xyxyxzxyxyx`，$x=4$，我们就输出 `xy`,`xyxzx`,`yx` 和 `yx` 四个字符串。

- 如果不存在“字符+连续相同字符数量”组合与一个和它相隔一个组合的“字符+连续相同字符数量”组合不同，那么字符串一定是 `aNbMaNbM...aNbMaN` 形式，其中 `ab` 表示任意两个字母，$N,M$ 表示任意两个整数。我们分三小类讨论：

- - 如果 $N=M=1$，那么字符串一定形如 `ababab...ababa`，可以证明拆分后至少有一个连续子串为回文字符串，输出 `NO`。

- - 如果 $M>1$，那么我们就输出 `aNb1` 和 `b(M-1)aNbM...aNbMaN` 两个字符串，易知这两个字符串都不为回文字符串。例如 `xyyyxyyyxyyyx`，我们输出 `xy` 和 `yyxyyyxyyyx` 两个字符串。

- - 如果 $M=1,N>1$，若只有三个“字符+连续相同字符数量”组合，那么可以证明拆分后一定至少有一个连续子串是回文字符串，输出 `NO`；否则输出 `aNbMa1` 和 `a(N-1)bMaNbM...aNbMaN` 两个字符串，易知这两个字符串都不为回文字符串。例如 `iiijiiijiiijiii`，我们输出 `iiiji` 和 `iijiiijiii` 两个字符串。

以上讨论包含了所有可能作为输入的字符串。

## AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
char c[1000002],dif[1000001];int num[1000001];
int main(){
	int T;scanf("%d",&T);
	while(T--){
		int tot=-1;scanf("%s",c+1);
		for(int i=1;c[i];i++){
			if(c[i]!=c[i-1]){
				dif[++tot]=c[i];num[tot]=1;
			}
			else num[tot]++;
		}
		if(tot&1){
			puts("YES\n1");puts(c+1);
		}
		else if(tot==0)puts("NO");
		else{
			bool ok=1;int h=0;
			for(int i=2;i<=tot;i++){
				if(dif[i]!=dif[i-2]||num[i]!=num[i-2]){h=i-2;ok=0;break;}
			}
			if(ok){
				if(num[0]==1&&num[1]==1)puts("NO");
				else if(num[1]>1){
					puts("YES\n2");
					while(num[0]--)putchar(dif[0]);
					putchar(dif[1]);num[1]--;putchar(' ');
					for(int i=1;i<=tot;i++)while(num[i]--)putchar(dif[i]);
					putchar('\n');
				}
				else{
					if(tot==2)puts("NO");
					else{
						puts("YES\n2");
						for(int i=0;i<=1;i++)while(num[i]--)putchar(dif[i]);
						putchar(dif[2]);num[2]--;putchar(' ');
						for(int i=2;i<=tot;i++)while(num[i]--)putchar(dif[i]);
						putchar('\n');
					}
				}
			}
			else if(h&1){
				printf("YES\n%d\n",(tot>>1)-1);
				for(int i=0;i<tot;i+=2){
					while(num[i]--)putchar(dif[i]);
					while(num[i+1]--)putchar(dif[i+1]);
					if(h-1==i){
						i+=2;
						while(num[i]--)putchar(dif[i]);
						while(num[i+1]--)putchar(dif[i+1]);
						i++;while(num[i+1]--)putchar(dif[i+1]);
					}
					putchar(' ');
				}
				putchar('\n');
			}
			else{
				printf("YES\n%d\n",tot>>1);
				for(int i=0;i<tot;i+=2){
					while(num[i]--)putchar(dif[i]);
					while(num[i+1]--)putchar(dif[i+1]);
					if(h==i){
						i++;
                        while(num[i+1]--)putchar(dif[i+1]);
					}
					putchar(' ');
				}
				putchar('\n');
			}
		}
	}
	return 0;
}
```

---

## 作者：liugh_ (赞：0)

定义问题 $A_k$ 为是否存在方案将原串分为 $k$ 个非回文子串 $\{s_i\}_{i=1}^{k}$。对于 $k>2$，若 $A_k$ 有解，则必不存在 $1<i<k$ 使 $s_{i-1}+s_i$ 和 $s_i+s_{i+1}$ 均为回文串，否则 $s_i$ 是回文串，矛盾，考虑将 $s_{i-1}$ 与 $s_i$ 或 $s_i$ 与 $s_{i+1}$ 合并，于是 $A_{k-1}$ 有解。故原问题有解当且仅当 $A_1$ 或 $A_2$ 有解。

---

## 作者：UncleSam_Died (赞：0)

### 题目大意

给出一个字符串 $s$，要求将 $s$ 分为若干个非回文子串，输出一组可行解或输出 $-1$ 报告无解。

### 解题思路

我们考虑将连续的相同字符分为一段，然后将没两段或三段合并，得到答案。设划分后有 $m$ 段，具体情况如下：

1. $s$ 本身为非回文串，那么直接输出 $s$ 就可以了，此时字串数为 $1$；
2. 划分后共有偶数段，这种情况直接相邻两段合并即可，子串数为 $\frac{m}{2}$；
3. 划分后有奇数段，那么这时我们需要将某些段三个合并，情况如下：
   1. 存在一个段使得它的长度大于 $1$ 且编号为偶数，这个时候我们将这个段从中间任意一处分为两段，新得到的两段分别与前后两段合并，这时子串数量为 $\lceil \frac{m}{2} \rceil$；
   2. 存在一个段使得长度大于 $1$ 且编号为奇数，不妨设它为 $a_i$，这个时候我们同样把它从中间某一处断开，使得 $a_{i-2}\not= a_i \vee a_{i+2}\not= a_i$，我们将分开后的两个段分别与前后三个段合并，这时子串个数为 $\lfloor \frac{m}{2} \rfloor$；
4. 其他情况无解，输出 $-1$；

### AC 代码

```cp
#pragma GCC optimize(3)
#pragma GCC target("avx")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#include<stdio.h>
#include<string.h>
#define N 1000005
int n,m; char s[N];
struct STR{int len;
char ch;}a[N],b[N];
inline bool hw(){ for(int i=1;i<=n;++i)
        if(s[i]!=s[n-i+1]) return false;
    return true;
}inline void work(){
    scanf("%s",s+1); m=0;n=strlen(s+1);
    for(int i=1;i<=n;++i) if(s[i]!=s[i-1]) 
    a[++m].ch=s[i],a[m].len=1; else ++a[m].len;
    if(!hw()){ printf("YES\n1\n"); printf("%s",s+1);
    putchar('\n');return;}if(m==1){puts("NO");return;}
    else if(m&1){ bool is=false; for(int i=2;i<m;++i)
        if(a[i].len>1&&(i%2==0)){is=true;break;}
        if(is){ puts("YES"); printf("%d\n",(m+1)/2);
            bool flag=false;for(int i=1;i<=m;++i){ if(i==1||i==m){
                for(int j=1;j<=a[i].len;++j) putchar(a[i].ch);
                continue;} if(!flag&&a[i].len>1&&(i%2==0)){
                putchar(a[i].ch);putchar(' ');
                for(int j=1;j<a[i].len;++j) putchar(a[i].ch);
                flag=true; continue;
                } for(int j=1;j<=a[i].len;++j) putchar(a[i].ch);
                if(!flag&&(i%2==0)) putchar(' ');
                else if(flag&&(i&1)) putchar(' ');
            } putchar('\n');
        }else{ is=false;
            for(int i=1;i<=m-2;i+=2){ if(i==m) continue;
                if(a[i].len!=a[i+2].len){ is=true;break;}
                if(a[i].ch!=a[i+2].ch){ is=true;break; }
            } if(!is){ int ce=0; for(int i=3;i<=m-2;++i)
                if(i&1&&(a[i].len>1)){ is=true;break; }
                if(!is){puts("NO");return;}
                int pos=0,flag=0; for(int i=1;i<=m;++i)
                if((!flag)&&(i&1)&&a[i].len>1&&i!=1&&i!=m){
                    int l=0,r=a[i].len;
                    if(r==a[i+2].len) ++l,--r;
                    if(l==a[i-2].len) ++l,--r;
                    b[++ce].ch=a[i].ch,b[ce].len=l;
                    b[++ce].ch=a[i].ch,b[ce].len=r;
                    pos=ce-1; flag=true;
                }else b[++ce]=a[i];
                printf("YES\n%d\n",(ce-2)/2);
                for(int i=1;i<=ce;i+=2)
                if(i+2!=pos){ for(int j=1;j<=b[i].len;++j) putchar(b[i].ch);
                    for(int j=1;j<=b[i+1].len;++j) putchar(b[i+1].ch);
                    putchar(' ');
                }else{ for(int j=1;j<=b[i].len;++j) putchar(b[i].ch);
                    for(int j=1;j<=b[i+1].len;++j) putchar(b[i+1].ch);
                    for(int j=1;j<=b[i+2].len;++j) putchar(b[i+2].ch);
                    putchar(' '); i+=3;
                    for(int j=1;j<=b[i].len;++j) putchar(b[i].ch);
                    for(int j=1;j<=b[i+1].len;++j) putchar(b[i+1].ch);
                    for(int j=1;j<=b[i+2].len;++j) putchar(b[i+2].ch);
                    putchar(' '); i+=1;
                } putchar('\n'); return;
            }
            puts("YES");
            printf("%d\n",(m-1)/2);
            bool flag=false;
            for(int i=1;i<=m;i+=2){  if(!flag)
                if(a[i].len!=a[i+2].len||a[i].ch!=a[i+2].ch){
                    for(int j=1;j<=a[i].len;++j) putchar(a[i].ch);
                    for(int j=1;j<=a[i+1].len;++j) putchar(a[i+1].ch);
                    for(int j=1;j<=a[i+2].len;++j) putchar(a[i+2].ch);
                    putchar(' '); ++i; flag=true;continue;
                } for(int j=1;j<=a[i].len;++j) putchar(a[i].ch);
                for(int j=1;j<=a[i+1].len;++j) putchar(a[i+1].ch);
                putchar(' ');
            } putchar('\n');
        }
    }else{ printf("YES\n%d\n",m/2);
        for(int i=1;i<=m;i+=2){
        for(int j=1;j<=a[i].len;++j) putchar(a[i].ch);
        for(int j=1;j<=a[i+1].len;++j) putchar(a[i+1].ch);
        putchar(' '); } putchar('\n');
    }
} signed main(){
    int T;scanf("%d",&T);
    while(T--) work();
}
```

---

