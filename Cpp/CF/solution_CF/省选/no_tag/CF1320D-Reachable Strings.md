# Reachable Strings

## 题目描述

In this problem, we will deal with binary strings. Each character of a binary string is either a 0 or a 1. We will also deal with substrings; recall that a substring is a contiguous subsequence of a string. We denote the substring of string $ s $ starting from the $ l $ -th character and ending with the $ r $ -th character as $ s[l \dots r] $ . The characters of each string are numbered from $ 1 $ .

We can perform several operations on the strings we consider. Each operation is to choose a substring of our string and replace it with another string. There are two possible types of operations: replace 011 with 110, or replace 110 with 011. For example, if we apply exactly one operation to the string 110011110, it can be transformed into 011011110, 110110110, or 110011011.

Binary string $ a $ is considered reachable from binary string $ b $ if there exists a sequence $ s_1 $ , $ s_2 $ , ..., $ s_k $ such that $ s_1 = a $ , $ s_k = b $ , and for every $ i \in [1, k - 1] $ , $ s_i $ can be transformed into $ s_{i + 1} $ using exactly one operation. Note that $ k $ can be equal to $ 1 $ , i. e., every string is reachable from itself.

You are given a string $ t $ and $ q $ queries to it. Each query consists of three integers $ l_1 $ , $ l_2 $ and $ len $ . To answer each query, you have to determine whether $ t[l_1 \dots l_1 + len - 1] $ is reachable from $ t[l_2 \dots l_2 + len - 1] $ .

## 样例 #1

### 输入

```
5
11011
3
1 3 3
1 4 2
1 2 3```

### 输出

```
Yes
Yes
No```

# 题解

## 作者：George1123 (赞：24)

# 题解-Reachable Strings

[$\texttt{Read it in my cnblogs.}$](https://www.cnblogs.com/Wendigo/p/12539363.html)

**前置知识：**

> $\texttt{Hash}$

---

> [Reachable Strings](https://www.luogu.com.cn/problem/CF1320D)

> 给一个长度为 $n$ 的 $\texttt{01}$ 串 $s$，可以让 $s$ 中的 $\texttt{110}$ 和 $\texttt{011}$ 互相转换。$q$ 次询问，每次给定两个 $s$ 的子串 $s_{l_1\sim l_1+len-1}$ 和 $s_{l_2\sim l_2+len-1}$，问两个串是否可以互相变换得到。

> 数据范围：$1\le n,q\le 10^5$。

---
哈希萌新觉得这是哈希好题。

---

很容易注意到 $\texttt{11}\color{#9c3}\texttt{0}\color{black}\leftrightarrow\color{#9c3}\texttt{0}\color{black}\texttt{11}$ 就是 **$\texttt{0}$ 左右移动两个位置**。

但是**不可以** $\texttt{10}\color{#9c3}\texttt{0}\color{black}\leftrightarrow\color{#9c3}\texttt{0}\color{black}\texttt{01}$ 或 $\texttt{01}\color{#9c3}\texttt{0}\color{black}\leftrightarrow\color{#9c3}\texttt{0}\color{black}\texttt{10}$，说明 **$\texttt{0}$ 移动时不能跨越别的 $\texttt{0}$**。

综上，所有 $\texttt{0}$ 的**位置（从左往右第几个 $\texttt{0}$）** 不会发生改变，并且下标的奇偶性不会变。

所以可以把所有 $\texttt{0}$ 按序记录下标奇偶性生成序列，然后**判断 两个子序列 是否可以互相变换得到 可以用序列哈希对比 看是否相等**。

重点是**因为每个子序列的起点奇偶性不都相同，所以每个 $0$ 有两种奇偶性可能，所以用两个哈希数组。**

---

具体实现哈希时可以用一个**质数进制数**来表示一个序列。

如果从高到低第 $i$ 位为 $1$，就表示原字符串从左到右第 $i$ 个 $\texttt{0}$ 的下标为**奇数**；如果为 $2$，就表示原字符串从左到右第 $i$ 个 $\texttt{0}$ 的下标为**偶数**。

然后开前缀 $\texttt{0}$ 序列数组 $h$，$h_n$ 表示原字符串前 $n$ 个 $\texttt{0}$ 哈希得的质数进制数。

因为子序列的**起点奇偶性不同**，所以有两个 $h$，分别表示以起点为**奇数和偶数**为标准时哈希得的前缀 $\texttt{0}$ 序列数组。

子串可以由前缀 $\texttt{0}$ 序列数组推得，看是否可以互相变换得到只需直接比较子串。

但是有个问题：**$0$ 那么多，形成的质数进制数太大怎么办（远爆 $\texttt{long long}$）？**

**解决方法是模某个大质数（如 $998244353$）。** 虽然这样可能会把两个不同的序列哈希得一样，但这正是哈希的精髓。没有绝对正确的哈希，能解决问题的就是好哈希。

---

## $\texttt{Code}$

```cpp
#include <bits/stdc++.h>
using namespace std;

//&Start
#define inf 0x3f3f3f3f
#define re register
#define il inline
#define hash unorded_map
typedef long long lng;
typedef unsigned long long ulng;
typedef vector<int> veci;
#define fo(i,st,xb,y) for(re int i=st;i xb;i y)

//&Data
#define N 200000
#define mod 998244353 //模数为998244353
#define base 5119 //5119进制
char s[N+10];
int n,m,h[N+10][2],bs[N+10]={1},ze[N+10];
//两个h，进制前缀积，零数量前缀和

//&Main
il int Hash(re int l,re int r,re int o){return (-1ll*h[l-1][o]*bs[ze[r]-ze[l-1]]%mod+h[r][o]+mod)%mod;} //子序列哈希值
int main(){
	scanf("%d%s",&n,s+1);  
	fo(i,1,<=n,++)
		if(s[i]=='1') h[i][0]=h[i-1][0],h[i][1]=h[i-1][1],ze[i]=ze[i-1];
		else h[i][0]=(1ll*h[i-1][0]*base%mod+1+(i&1))%mod,
			h[i][1]=(1ll*h[i-1][1]*base%mod+1+((i&1)^1))%mod,ze[i]=ze[i-1]+1;
	fo(i,1,<=n,++) bs[i]=1ll*bs[i-1]*base%mod;
	scanf("%d",&m); fo(i,1,<=m,++){
		re int l1,l2,len; scanf("%d%d%d",&l1,&l2,&len);
		(Hash(l1,l1+len-1,l1&1)==Hash(l2,l2+len-1,l2&1)?puts("Yes"):puts("No"));
	}
	return 0;
}
```

---
**祝大家学习愉快！**


---

## 作者：xht (赞：6)

`011` 和 `110` 可以相互转化，相当于每次可以将每个 `0` 向左右移动两个单位，因此每个 `0` 的位置下标的奇偶性不会变。

但是当出现 `00` 时，左边的 `0` 无法移到右边，右边的 `0` 无法移到左边，也就是**无法跨越奇偶性不同的 `0`**。

换句话说，两个字符串可以相互转化，当且仅当**每个 `0` 所在的位置下标的奇偶性一一对应**。

比如一个字符串中有 $6$ 个 `0`，位置分别在 $1,2,3,4,6,7$，则它一定可以转化为 `0` 的位置分别在 $1,10,101,102,1000,10101$ 的字符串。

那么，每次询问相当于求出一个区间内每个 `0` 在**以这个区间开头为奇下标**时的奇偶性。

我们对这个奇偶性进行 hash，就能快速比较两个区间内的信息是否一致了。

```cpp
#define Hash pair<modint, modint>
const Hash B = mp(131, 13331);
inline Hash operator + (Hash a, Hash b) { return mp(a.fi + b.fi, a.se + b.se); }
inline Hash operator - (Hash a, Hash b) { return mp(a.fi - b.fi, a.se - b.se); }
inline Hash operator * (Hash a, Hash b) { return mp(a.fi * b.fi, a.se * b.se); }
inline Hash operator + (Hash a, int b) { return mp(a.fi + b, a.se + b); }

const int N = 2e5 + 7;
int n, q, c[N];
char s[N];
Hash h[N][2], p[N];

inline Hash H(int l, int r, int o) {
	return h[r][o] - h[l-1][o] * p[c[r]-c[l-1]];
}

int main() {
	rd(n), rds(s, n), rd(q);
	p[0] = mp((modint)1, (modint)1);
	for (int i = 1; i <= n; i++) {
		if (s[i] != '0') h[i][0] = h[i-1][0], h[i][1] = h[i-1][1], c[i] = c[i-1];
		else h[i][0] = h[i-1][0] * B + ('0' + (i & 1)), h[i][1] = h[i-1][1] * B + ('0' + ((i & 1) ^ 1)), c[i] = c[i-1] + 1;
		p[i] = p[i-1] * B;
	}
	while (q--) {
		int l1, l2, len;
		rd(l1), rd(l2), rd(len);
		int r1 = l1 + len - 1, r2 = l2 + len - 1;
		prints(H(l1, r1, l1 & 1) == H(l2, r2, l2 & 1) ? "Yes" : "No");
	}
	return 0;
}
```

---

## 作者：Owen_codeisking (赞：4)

提供一个差不多的解法。

注意到操作是可逆的，所以我们只要找到一个等价类让两者相等，两者就一定相等。

所以我们就可以找到等价类中字典序最小的串进行比较，那么只需要执行 $110\rightarrow 011$ 这个操作。

可以发现，$11$ 这种串一定可以移到串的末尾，而且移到末尾可以视为删除 $11$。

接下来就可以用线段树维护左右边界的数，目前的长度，哈希的值，在上传的时候把 $11$ 删掉。

时间 $\mathcal{O}(n\log n)$。

代码使用了双哈希，所以比较慢。

[code](https://codeforces.com/contest/1320/submission/92760906)

---

## 作者：1kri (赞：3)

~~真有意思~~的哈希

---
思路：

无修改，子串查询，容易想到哈希。

考虑每种操作的实质：将每个 **0** 向前移动两位（需保证前两位都是 **1** ）。

于是我们只管 **0** 的位置，忽视 **1** 。

考虑一种构造情况：将所有 **0** 尽可能前移。这样可以保证正确（不会遗漏）。

分析样例可知：两个 **0** 的最终相对位置（位置差，中间隔的 **1** 的个数）只可能是 0 或 1 。（如果大于 1 ，则可继续向前移动 2 位）

分析可知：两个 **0** 的最终相对位置是它们的初始位置差模 2 。于是记下所有 **0** 的最终相对位置并哈希。

现在确定了所有 **0** 的最终相对位置，只需确定第一个 **0** 的位置即可确定整个最终序列并判断。

第一个 **0** 的位置判定如前，只需将初始位置模 2 即可。

这样还有一个问题，就是最终序列有较大概率发生哈希冲突。记下区间 **0** 的个数并比较即可解决。

---

代码实现：

将所有 **0** 的位置放进数组，计算最终相对位置并哈希。

每次查询时二分即可。

具体代码：

```cpp
#include <iostream>
#include <cstdio>
#define int long long
#define mod 998244353
using namespace std;
int n,q,x,y,t,len,pos[200005],ch[200005],fac[200005],num[200005],sum[200005];
char s[200005];
inline int getmod(int x){
    return (x%mod+mod)%mod;
}
inline int getsum(int l,int r){//获取相对位置哈希值
    if (l>r)return 0;
    return getmod(sum[r]-sum[l-1]*fac[r-(l-1)]);
}
inline int getnum(int l,int r){//防止hack，记录区间0的个数
    return num[r]-num[l-1];
}
inline int lowwer(int x){
    int l=1,r=len,ans=-1;
    while(l<=r){
        int mid=(l+r)/2;
        if (pos[mid]<=x)ans=mid,l=mid+1;
        else r=mid-1;
    }
    return ans;
}
inline int larger(int x){
    int l=1,r=len,ans=-1;
    while(l<=r){
        int mid=(l+r)/2;
        if (pos[mid]>=x)ans=mid,r=mid-1;
        else l=mid+1;
    }
    return ans;
}
inline int getval(int nowl,int nowr){ //获取最终序列哈希值
    int l=larger(nowl),r=lowwer(nowr);
    if (l==-1||r==-1)return -1;
    if (pos[l]>nowr||pos[r]<nowl||l>r)return -1;//以上两行特判全是1的情况
    return getmod(getsum(l+1,r)*2+(pos[l]-nowl)%2);
}
signed main(){
    cin>>n;
    scanf("%s",s+1);
    for (int i=1;i<=n;i++){
        num[i]=num[i-1];
        if (s[i]=='0')pos[++len]=i,num[i]++;
    }//储存0的位置
    fac[0]=1;
    for (int i=1;i<=n;i++)fac[i]=getmod(fac[i-1]*2);
    for (int i=2;i<=len;i++)ch[i]=(pos[i]-pos[i-1])%2;//相对位置
    for (int i=2;i<=len;i++)sum[i]=getmod(sum[i-1]*2+ch[i]);//相对位置哈希
    cin>>q;
    while(q--){
        scanf("%lld%lld%lld",&x,&y,&t);
        if (getval(x,x+t-1)==getval(y,y+t-1)&&getnum(x,x+t-1)==getnum(y,y+t-1))puts("Yes");//查询判断
        else puts("No");
    }
    return 0;
}
```


---

## 作者：legend_life (赞：2)

# [CF1320D Reachable Strings](http://codeforces.com/contest/1320/problem/D)

**挺好的思维题，码量也不大**

首先，需要看出一件事情————一次变换相当于让一个 $0$ 向前跳两位或向后跳两位，但 $00$ 这种子串两个 $0$ 都互相跳不过去

虽然很显然，但不容易向这方面思考（可能是我太菜了）

假设 $t$ 是原字符串，  $t_{l_{1}, l_{1} + 1, ... , l_{1} + len - 1}$ 中 $0$ 的奇偶性依次是 $k1_{1}, k1_{2}, ..., k1_{cnt_{1}}$，$t_{l_{2}, l_{2} + 1, ... , l_{2} + len - 1}$ 中 $0$ 的奇偶性依次是 $k2_{1}, k2_{2}, ..., k2_{cnt_{2}}$

那么可以由 $t_{l_{1}, l_{1} + 1, ... , l_{1} + len - 1}$ 变成 $t_{l_{2}, l_{2} + 1, ..., l_{2} + len - 1}$ 的充分必要条件是：

$\begin{cases}cnt_1 = cnt_2 \\ k1_{i} = k2_{i} (1 \le i \le cnt_1) \end{cases}$

接下来就简单了————  
对字符串简单哈希一下就可以了

详情见我代码：


```cpp
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define mp make_pair
#define pb push_back
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;

ll read()
{
	char c = getchar(); ll flag = 1, ans = 0;
	while (c < '0' || c > '9') {if (c == '-') flag = -flag; c = getchar();}
	while (c >= '0' && c <= '9') {ans = ans * 10 + c - '0'; c = getchar();}
	return ans * flag;
}

const ll INF = 1e16;
const int MAXN = 200020;
const ll MOD = 1e9 + 9, bas = 23;
ll has[2][MAXN], pw[MAXN], cnt[MAXN];
char c[MAXN];
int n, q;

ll query (int l, int r, int op)
{
	return ((has[op][r] - has[op][l - 1] * pw[cnt[r] - cnt[l - 1]]) % MOD + MOD) % MOD;
}

int main()
{
	scanf ("%d", &n);
	scanf ("%s", c + 1);
	for (int i = 1; i <= n; ++ i)
	{
		has[0][i] = has[0][i - 1], has[1][i] = has[1][i - 1], cnt[i] = cnt[i - 1];
		if (c[i] == '0')
		{
			has[0][i] = (has[0][i - 1] * bas + 1 + (i & 1)) % MOD;
			has[1][i] = (has[1][i - 1] * bas + 1 + ((i & 1) ^ 1)) % MOD;
			++ cnt[i];
		}
	}
	pw[0] = 1;
	for (ll i = 1; i <= n; ++ i)
		pw[i] = pw[i - 1] * bas % MOD;
	scanf ("%d", &q);
	for (int i = 1; i <= q; ++ i)
	{
		ll l1, l2, len;
		scanf ("%lld%lld%lld", &l1, &l2, &len);
		if (query (l1, l1 + len - 1, l1 & 1) == query (l2, l2 + len - 1, l2 & 1))
			printf ("Yes\n");
		else
			printf ("No\n");
	}
	return 0;
}
```

---

## 作者：灵梦 (赞：2)

比赛时并没有搞出来qwq

题目中的两种变换可以当作是字符 $1$ 或 $0$ 的一次运动。我们尝试寻找 $0$ 的运动规律。

观察到 $011\to 110$ 可以看作 $0$ 在右边有连续两个 $1$ 时右移 $2$ 位，而 $110\to 011$ 可以看作 $0$ 在左边有连续两个 $1$ 时左移 $2$ 位。考虑整个字符串的变换，发现两个 $0$ 是不可以相互跨越的，并且每个 $0$ 的下标的奇偶性在变换中保持不变。那么对于两个等长的子串，若它们满足以下两个条件，则可以互相通过变换达到：

- $0$ 的个数相等；
- 两个子串中的第 $i$ 个 $0$ 的下标的奇偶性对应相同。

于是我们只需要对 $0$ 哈希它的下标奇偶性就可以了。这里下标是相对左端点的，所以求子串哈希时还要讨论左端点的奇偶性。

代码：

```cpp
#include <cstdio>
#include <algorithm>
#include <chrono>
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const int MAXN=220000;
const int BASE=rng()%19260817+3;
const int MOD=1004535809;
char a[MAXN];
int powb[MAXN];
int cnt[MAXN], h1[MAXN], h2[MAXN];
inline int query(int l, int r)
{
	if (l&1) return (h1[r]-1ll*h1[l-1]*powb[cnt[r]-cnt[l-1]]%MOD+MOD)%MOD;
	else return (h2[r]-1ll*h2[l-1]*powb[cnt[r]-cnt[l-1]]%MOD+MOD)%MOD;
}
int main()
{
//	freopen("D.in", "r", stdin);
//	freopen("D.out", "w", stdout);
	int n, q;
	scanf("%d%s", &n, a+1);
	powb[0]=1;
	for (int i=1; i<=n; i++)
	{
		powb[i]=1ll*powb[i-1]*BASE%MOD;
		cnt[i]=cnt[i-1]+(a[i]=='0');
		if (a[i]=='0')
		{
			h1[i]=(1ll*h1[i-1]*BASE+(i&1)+1)%MOD;
			h2[i]=(1ll*h2[i-1]*BASE+(i&1^1)+1)%MOD;
		}
		else h1[i]=h1[i-1], h2[i]=h2[i-1];
	}
	scanf("%d", &q);
	while (q--)
	{
		int l, r, len;
		scanf("%d%d%d", &l, &r, &len);
		if (query(l, l+len-1)==query(r, r+len-1)) puts("Yes");
		else puts("No");
	}
	return 0;
}
```



---

## 作者：vectorwyx (赞：1)

相当不错的思维题。

注意到 $110→011$ 和 $011→110$ 相当于把 $0$ 左移或右移两位，且移动的过程中**不能跨越某个 $0$**。（**关键点 $1$**）

这意味着 $0$ 的相对方位不会发生改变（**关键点** $2$），两个子串 $s1$ 和 $s2$ 如果相互可达，那么 $s1$ 里的 $0$ 与 $s2$ 里的 $0$ 的对应关系一定是唯一确定的——$s1$ 的第一个 $0$ 与 $s2$ 的第一个 $0$ 对应，$s1$ 的第二个 $0$ 与 $s2$ 的第二个 $0$ 对应……所以 $s1$ 与 $s2$ 是否相互可达也就只与它们所含的 $0$ 的**数量**和 $0$ 的**下标的奇偶性**有关（**关键点** $3$）。

首先，如果 $0$ 的数量不一致，那么答案肯定为`no`。其次，如果 $s1$ 和 $s2$ 中所对应的 $0$ 的下标的奇偶性不同，那么答案肯定也为`no`，因为每个 $0$ 的下标的变化量只能为偶数（**关键点** $4$）。故而，我们可以将给定的字符串 $s$ 所含的所有 $0$ 的下标都放到一个单独的字符串 $a$ 里，把奇数赋为 $1$，偶数赋为 $0$。那么问题就变成了判断 $a$ 中的两个子串是否相等，这个过程可以用哈希来实现（**关键点** $5$）。

注意，由于得到的 $a$ 数组中存储的01值是由相对于原字符串 $s$ 而言的“绝对下标”得到的，而我们实际上要判断的是相对于所询问子串的“相对下标”，因此询问时的某段子串的01值可能会与 $a$ 中的01值截然相反，处理一下就好了（**关键点** $6$）。


------------
代码如下qwq：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#define mod1 998244353
#define mod2 1000000007
#define base1 3
#define base2 101
#define ll long long
#define fo(i,x,y) for(int i=x;i<=y;++i)
#define go(i,x,y) for(int i=x;i>=y;--i)
using namespace std;
inline int read(){ int x=0,fh=1; char ch=getchar(); while(!isdigit(ch)){ if(ch=='-') fh=-1; ch=getchar(); } while(isdigit(ch)){ x=(x<<1)+(x<<3)+ch-'0'; ch=getchar(); } return x*fh; }

const int N=2e5+5;
char s[N];
int n,pw1[N],pw2[N],hx1[N],hx2[N],a[N],top,_hx1[N],_hx2[N];

void hash_(){
	pw1[0]=pw2[0]=1;
	fo(i,1,top) pw1[i]=1ll*pw1[i-1]*base1%mod1,pw2[i]=1ll*pw2[i-1]*base2%mod2;
	fo(i,1,top){
		hx1[i]=hx1[i-1];hx2[i]=hx2[i-1];_hx1[i]=_hx1[i-1];_hx2[i]=_hx2[i-1];
		if(a[i]&1) hx1[i]=(hx1[i]+pw1[i-1])%mod1,hx2[i]=(hx2[i]+pw2[i-1])%mod2;
		else _hx1[i]=(_hx1[i-1]+pw1[i-1])%mod1,_hx2[i]=(_hx2[i]+pw2[i-1])%mod2;
	}
}

bool check(){
	int l1=read(),l2=read(),len=read();
	bool flag=(l1&1)^(l2&1);
	if(l1>l2) swap(l1,l2);
	int r1=l1+len-1,r2=l2+len-1;
	int L1=lower_bound(a+1,a+1+top,l1)-a,R1=upper_bound(a+1,a+1+top,r1)-a-1;
	int L2=lower_bound(a+1,a+1+top,l2)-a,R2=upper_bound(a+1,a+1+top,r2)-a-1;
	if(R1-L1!=R2-L2) return 0;
	if(R1-L1==-1) return 1;
	int v1,v2;
	if(flag) v1=(0ll+_hx1[R1]+mod1-_hx1[L1-1])*pw1[L2-L1]%mod1;
	else v1=(0ll+hx1[R1]+mod1-hx1[L1-1])*pw1[L2-L1]%mod1;
	v2=(0ll+hx1[R2]+mod1-hx1[L2-1])%mod1;
	if(v1!=v2) return 0;
	if(flag) v1=(0ll+_hx2[R1]+mod2-_hx2[L1-1])*pw2[L2-L1]%mod2;
	else v1=(0ll+hx2[R1]+mod2-hx2[L1-1])*pw2[L2-L1]%mod2;
	v2=(0ll+hx2[R2]+mod2-hx2[L2-1])%mod2;
	return v1==v2;
}

int main(){
	n=read();
	scanf("%s",s+1);
	fo(i,1,n) if(s[i]=='0') a[++top]=i;
	hash_();
	int q=read();
	while(q--) puts(check()?"Yes":"No");
	return 0;
}
```

点个赞再走呗/kel

---

## 作者：chenxia25 (赞：1)

>### [洛谷题目页面传送门](https://www.luogu.org/problem/CF1320D) & [CodeForces题目页面传送门](https://codeforces.com/contest/1320/problem/D)

>有一个01串$a,|a|=n$。$q$次询问，每次给出$l1,l2,len$，问$a_{l1\sim l1+len-1},a_{l2\sim l2+len-1}$这$2$个01串是否能通过若干次操作变得相等，其中一次操作指的是将任意一个01串的任意一个等于$\texttt{110}$的子串变成$\texttt{011}$或将$\texttt{011}$变成$\texttt{110}$。

>$n,q\in\left[1,2\times10^5\right]$。

考虑分析能通过若干次操作变得相等的充要条件。

不难发现，每次操作都不可能改变01串中$\texttt0$和$\texttt1$分别的数量，所以$2$个01串中$\texttt0$和$\texttt1$的数量分别相等是能通过若干次操作变得相等的必要条件，但充分性还远远不够。

又发现，$\texttt{110}\leftrightarrow\texttt{011}$这个操作比较有意思，它相当于将这个唯一的$\texttt{0}$向左/右推了$2$位。由于这是个01串，非$\texttt0$即$\texttt1$，于是我们将所有$\texttt0$的位置揪出来，其他位置自然是$\texttt1$。

不难发现，01串中所有$\texttt0$对的相对位置都不会改变。证明：若$2$个$\texttt0$想要交换位置，那么交换前最后一刻的状态一定是距离差$\leq2$，此时左边的$\texttt0$不能通过$\texttt{011}\to\texttt{110}$往右再移$2$格，因为它右边$1\sim2$格是右边的$\texttt0$，以它开头的长度为$3$的子串一定不为$\texttt{011}$。类似地，右边的$\texttt0$也不能往左移$2$格。得证。

于是考虑将$2$个01串中的所有$\texttt0$按出现次序一一对应。显然，第$1$个01串中的某个$\texttt0$能够与第$2$个01串中的某个$\texttt0$到同一位置上当且仅当它们在所在串中的位置之差为偶数，即奇偶性相等。所以我们猜测：$2$个01串中的所有$\texttt0$按出现次序一一对应后，每对$\texttt0$在所在串中的位置奇偶性相等，是这$2$个01串能通过若干次操作变得相等的充要条件。证明：

1. 充分性证明：数学归纳法。
   1. 当$2$个串都不存在$\texttt0$时，充分性显然；
   1. 假设当$2$个串都存在$x-1(x\geq1)$个$\texttt0$时，满足充分性。此时若要将$2$个存在$x$个$\texttt0$的01串的所有$\texttt0$对一一对齐，可以将左数第$1$对$\texttt0$中较右的那个$\texttt0$通过若干次操作与较左的对齐，问题转化为将剩下$x-1$对$\texttt0$一一对齐，根据假设，存在方案。所以若当$2$个串都存在$x-1$个$\texttt0$时，满足充分性，那么当$2$个串都存在$x$个$\texttt0$时，满足充分性。
   
   综上，充分性得证；
1. 必要性显然。

综上，得证。

接下来问题就变成了比较裸的序列哈希：每次给定$2$个子串，问这$2$个子串中$\texttt0$的位置奇偶性组成的序列是否相等。注意：这里的位置奇偶性指的是相对于$l1/l2$的位置奇偶性，而不是相对于$1$，所以要记录$2$个每项对应相反的$\texttt0$的位置奇偶性序列。子串中包含的$\texttt0$的位置奇偶性序列的子序列可以二分查找找到。

下面是AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define mp make_pair
#define pb push_back
const int N=200000;
int n/*01串长度*/,qu/*询问次数*/;
char a[N+5];//01串 
vector<int> pos;//'0'的位置序列 
const int hbase1=131,hmod1=998244353,hbase2=13331,hmod2=1000000007;//哈希参数 
int Hsh1[N+1],Rhsh1[N+1],hpw1[N+1],Hsh2[N+1],Rhsh2[N+1],hpw2[N+1];//Hsh：相对于1的'0'的位置奇偶性序列的前缀哈希，Rhsh：相对于2的…… 
void hsh_init(){//哈希预处理 
	hpw1[0]=hpw2[0]=1;
	for(int i=1;i<=pos.size();i++)//为了前缀运算方便，哈希数组们1-indexed 
		Hsh1[i]=(1ll*Hsh1[i-1]*hbase1+pos[i-1]%2+1)%hmod1,
		Rhsh1[i]=(1ll*Rhsh1[i-1]*hbase1+!(pos[i-1]%2)+1)%hmod1,
		hpw1[i]=1ll*hpw1[i-1]*hbase1%hmod1,
		Hsh2[i]=(1ll*Hsh2[i-1]*hbase2+pos[i-1]%2+1)%hmod2,
		Rhsh2[i]=(1ll*Rhsh2[i-1]*hbase2+!(pos[i-1]%2)+1)%hmod2,
		hpw2[i]=1ll*hpw2[i-1]*hbase2%hmod2;
}
pair<int,int> hsh(int l,int r){//pos[l-1~r-1]相对于1的奇偶性序列的哈希值 
	return mp(((Hsh1[r]-1ll*Hsh1[l-1]*hpw1[r-l+1]%hmod1)+hmod1)%hmod1,
			  ((Hsh2[r]-1ll*Hsh2[l-1]*hpw2[r-l+1]%hmod2)+hmod2)%hmod2);
}
pair<int,int> rhsh(int l,int r){//pos[l-1~r-1]相对于2的奇偶性序列的哈希值
	return mp(((Rhsh1[r]-1ll*Rhsh1[l-1]*hpw1[r-l+1]%hmod1)+hmod1)%hmod1,
			  ((Rhsh2[r]-1ll*Rhsh2[l-1]*hpw2[r-l+1]%hmod2)+hmod2)%hmod2);
}
int main(){
	cin>>n>>a+1>>qu;
	for(int i=1;i<=n;i++)if(a[i]=='0')pos.pb(i);//预处理pos 
	hsh_init();//预处理哈希 
	while(qu--){
		int l1,l2,len;
		scanf("%d%d%d",&l1,&l2,&len);
		int l1_0=lower_bound(pos.begin(),pos.end(),l1)-pos.begin()+1,//a[l1~l1+len-1]包含的'0'的位置奇偶性序列的左端点 
			r1_0=lower_bound(pos.begin(),pos.end(),l1+len)-pos.begin(),//a[l1~l1+len-1]包含的'0'的位置奇偶性序列的右端点
			l2_0=lower_bound(pos.begin(),pos.end(),l2)-pos.begin()+1,//a[l2~l2+len-1]包含的'0'的位置奇偶性序列的左端点
			r2_0=lower_bound(pos.begin(),pos.end(),l2+len)-pos.begin();//a[l2~l2+len-1]包含的'0'的位置奇偶性序列的右端点
		pair<int,int> hsh1=l1%2?hsh(l1_0,r1_0):rhsh(l1_0,r1_0),hsh2=l2%2?hsh(l2_0,r2_0):rhsh(l2_0,r2_0);//计算哈希值 
		puts(hsh1==hsh2?"Yes":"No");//判断相等 
	}
	return 0;
}
```

---

## 作者：xcyle (赞：0)

其它题解貌似都是看0的操作规律，我来提供一篇1的

操作的含义就是每次将偶数个1向左边移动一格。我们先找找性质，看起来偶数段是可以随意游走的，而奇数段需要留下一个

考虑到操作的可逆性，我们希望找到一种操作的“模式”使得两个子串经过这种“模式”后相同

因此我们让两个子串都将所有偶数个1移到子串最左端，不难证明这样操作后两子串是否相等的判断与原问题等价

哈希即可。

（此方法细节较多不建议使用）

```cpp#include <iostream>
#include <cstdio>
#define maxn 200005
#define uint unsigned long long 
using namespace std;
int n, q, l1, l2, len;
int sum[maxn], cnt[maxn];
int pre[maxn], suf[maxn];
char s[maxn];
uint hash1[maxn], hash2[maxn], pow1[maxn], pow2[maxn], bas1 = 998244353, bas2 = 1e9 + 7;
void init()
{
	pow1[0] = pow2[0] = 1;
	for (int i = 1; i <= n; i++) 
	{
		pow1[i] = pow1[i - 1] * bas1;
		pow2[i] = pow2[i - 1] * bas2;
	}
	for (int i = 1; i <= n; i++)
	{
		sum[i] = sum[i - 1];
		if(s[i] == '1') sum[i]++;
	}
	pre[0] = 0;
	for (int i = 1; i <= n; i++)
	{
		if(s[i] == '0') pre[i] = i;
		else pre[i] = pre[i - 1];
	}
	suf[n + 1] = n + 1;
	for (int i = n; i >= 1; i--)
	{
		if(s[i] == '0') suf[i] = i;
		else suf[i] = suf[i + 1];
	}
}
void work()
{
	int p = 0;
	for (int i = 1; i <= n; i++)
	{
		if(s[i] == '0') 
		{
			cnt[i] = cnt[i - 1] + 1;
			hash1[i] = hash1[i - 1] * bas1;
			hash2[i] = hash2[i - 1] * bas2;
		}
		else
		{
			int last = pre[i];
			cnt[i] = cnt[last];
			if((i - last) & 1) 
			{
				hash1[i] = hash1[last] * bas1 + 1;
				hash2[i] = hash2[last] * bas2 + 1;
				cnt[i]++;
			}
			else 
			{
				hash1[i] = hash1[last];
				hash2[i] = hash2[last];
			} 
		}
	}
}
int check(int l, int r)
{
	int tl = suf[l];
	if(tl > r)
	{
		return (r - l + 1) & 1;
	}
	return cnt[r] - cnt[tl - 1] + ((tl - l) & 1);
}
uint calc1(int l, int r)
{
	int tl = suf[l];
	if(tl > r)
	{
		if((r - l + 1) & 1) return bas1;
		else return 0;
	}
	uint res = hash1[r] - hash1[tl - 1] * pow1[cnt[r] - cnt[tl - 1]];
	if((tl - l) & 1) res += pow1[cnt[r] - cnt[tl - 1]];
	return res;
}
uint calc2(int l, int r)
{
	int tl = suf[l];
	if(tl > r)
	{
		if((r - l + 1) & 1) return bas2;
		else return 0;
	}
	uint res = hash2[r] - hash2[tl - 1] * pow2[cnt[r] - cnt[tl - 1]];
	if((tl - l) & 1) res += pow2[cnt[r] - cnt[tl - 1]];
	return res;
}
int main()
{
	scanf("%d%s%d", &n, s + 1, &q);
	init();
	work();
	for (int i = 1; i <= q; i++)
	{
		scanf("%d%d%d", &l1, &l2, &len);
		if(calc1(l1, l1 + len - 1) != calc1(l2, l2 + len - 1) || calc2(l1, l1 + len - 1) != calc2(l2, l2 + len - 1) || check(l1, l1 + len - 1) != check(l2, l2 + len - 1) || sum[l1 + len - 1] - sum[l1 - 1] != sum[l2 + len - 1] - sum[l2 - 1])
		{
			printf("No\n");
		}
		else printf("Yes\n");
	}
	return 0;
}
```

---

## 作者：Nylch (赞：0)

一道挺好的题，刚刚开始的时候没什么思路，后来认真考虑了一些性质就会做了。

题意是给出一个 01 串 $s$，$|s| \leq 2 \times 10^5$，每次可将任意子串 $011$ 变成 $110$ 或者将 $110$ 变成 $011$。有 $q$ 次询问，每次询问两个等长的子串，询问是否可以从一个子串经过变换变成另一个子串。

首先我们可以发现每次变换相当于把 $0$ 向左或向右移动两位，移动前后相邻两个 $0$ 之间 $1$ 的个数奇偶不变，那么我们将这两个串中的 $0$ 都尽量往某方向移动，如果移动之后两串长得一样，则这两原串间可相互变换。所以我们将每个 $0$ 的权值设为与前一个 $0$ 之间 $1$ 个数的奇偶（也就是设成  ```digit % 2```，其中 ```digit``` 表示前面所说的 $1$ 的个数，然后用哈希判断是否相同即可。

代码：

```cpp
#include <bits/stdc++.h>
#define reg register
#define ll long long
#define ull unsigned long long
#define db double
#define pi pair<int, int>
#define pl pair<ll, ll>
#define vi vector<int>
#define vl vector<ll>
#define vpi vector<pi>
#define vpl vector<pl>
#define pb push_back
#define er erase
#define SZ(x) (int) x.size()
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define mkp make_pair
using namespace std;
char ch, B[1 << 20], *S = B, *T = B;
#define getc() (S == T && (T = (S = B) + fread(B, 1, 1 << 20, stdin), S == T) ? 0 : *S++)
#define isd(c) (c >= '0' && c <= '9')
int aa, bb;
int rd() {
  while(ch = getc(), !isd(ch) && ch != '-');
  ch == '-' ? aa = bb = 0 : (aa = ch - '0', bb = 1);
  while(ch = getc(), isd(ch))
    aa = aa * 10 + ch - '0';
  return bb ? aa : -aa;
}
const int MAXN = 2e5 + 10;
const int BASE = 233;
char s[MAXN];
int n, a[MAXN], tot, flag[MAXN], cnt[MAXN];
ull power[MAXN], Hash[MAXN];
ull get(int l, int r) {
  int len = r - l + 1;
  return 1ll * Hash[r] - Hash[l - 1] * power[len];
}
ull check(int l, int r) {
  int L = lower_bound(a + 1, a + tot + 1, l) - a;
  int R = upper_bound(a + 1, a + tot + 1, r) - a - 1;
  if(L <= R) {
    ull x = (a[L] - l) & 1, v = x * power[R - L];
    if(L < R)
      v += get(L + 1, R);
    return v;
  }
  return 0;
}
inline void work() {
  power[0] = 1;
  for(reg int i = 1; i < MAXN; ++i)
    power[i] = power[i - 1] * BASE;
  scanf("%d%s", &n, s + 1);
  int digit = 0;
  for(reg int i = 1; i <= n; ++i) {
    cnt[i] = cnt[i - 1];
    if(s[i] == '1')
      digit++;
    else {
      flag[++tot] = digit & 1;
      digit = 0;
      a[tot] = i;
      ++cnt[i];
    }
  }
  for(reg int i = 1; i <= tot; ++i)
    Hash[i] = Hash[i - 1] * BASE + flag[i];
  int q;
  scanf("%d", &q);
  while(q--) {
    int l1, l2, len, r1, r2;
    scanf("%d%d%d", &l1, &l2, &len);
    r1 = l1 + len - 1;
    r2 = l2 + len - 1;
    if(cnt[r1] - cnt[l1 - 1] == cnt[r2] - cnt[l2 - 1] && check(l1, r1) == check(l2, r2))
      printf("Yes\n");
    else
      printf("No\n");
  }
}
int main() {
 	// freopen("input.txt", "r", stdin);
  work();
  return 0;
}
```

---

