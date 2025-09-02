# [ABC380D] Strange Mirroring

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc380/tasks/abc380_d

英大小文字からなる文字列 $ S $ が与えられます。

$ S $ に以下の操作を $ 10^{100} $ 回繰り返します。

- まず、 $ S $ の大文字を小文字に、小文字を大文字に書き換えた文字列を $ T $ とする。
- その後、 $ S $ と $ T $ とをこの順に連結した文字列を新たな $ S $ とする。
 
$ Q $ 個の質問に答えて下さい。 そのうち $ i $ 個目は次の通りです。

- 全ての操作を終えた後の $ S $ の先頭から $ K_i $ 文字目を求めよ。

## 说明/提示

### 制約

- $ S $ は英大小文字からなる長さ $ 1 $ 以上 $ 2\ \times\ 10^5 $ 以下の文字列
- $ Q,K_i $ は整数
- $ 1\ \le\ Q\ \le\ 2\ \times\ 10^5 $
- $ 1\ \le\ K_i\ \le\ 10^{18} $
 
### Sample Explanation 1

操作前の $ S\ = $ `aB` です。 - `aB` に $ 1 $ 回操作を行うと `aBAb` となります。 - `aB` に $ 2 $ 回操作を行うと `aBAbAbaB` となります。 - $ \dots $ $ 10^{100} $ 回の操作を終えた後の $ S\ = $ `aBAbAbaBAbaBaBAb`... です。

## 样例 #1

### 输入

```
aB
16
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16```

### 输出

```
a B A b A b a B A b a B a B A b```

## 样例 #2

### 输入

```
qWeRtYuIoP
8
1 1 2 3 5 8 13 21```

### 输出

```
q q W e t I E Q```

## 样例 #3

### 输入

```
AnUoHrjhgfLMcDIpzxXmEWPwBZvbKqQuiJTtFSlkNGVReOYCdsay
5
1000000000000000000 123456789 1 987654321 999999999999999999```

### 输出

```
K a A Z L```

# 题解

## 作者：Moya_Rao (赞：12)

# 题目大意
给定一个长度不定的字符串 $S$，现在你要对 $S$ 执行 $10^{100}$ 次操作，每次操作分两个步骤：
- 首先新开一个字符串 $T$，并让 $T$ 等于 $S$ 中所有大小字母颠倒。
- 然后让 $S$ 在末尾连接上 $T$，形成新的字符串 $S$。

接下来有 $Q$ 次询问，第 $i$ 次询问要求输出进行了 $10^{100}$ 次操作后的字符串 $S$ 里，第 $K_i$ 个字符是什么。

# 思路
赛时想了大半年，不得不说还是菜。菜，就多练呀。欢迎各位大佬来踩爆这个蒟蒻。

废话不多说我们进入正题，这道题目该怎么做呢？

一看就知道，不能够真的进行 $10^{100}$ 次操作得到这个 $S$，时间空间都承受不了，只能找规律咯。

正着找，你试试看就会发现，根本没用，啥都找不出来。那咋办？反着倒退呗。

首先要获得一个 $q$，使得 $n \times 2^q \ge K > n \times 2^{q-1}$，我们让 $p=n \times 2^q$，因为 $q$ 其实是没什么用的，$p$ 最重要。$p$ 是什么呀？$p$ 是经过最少操作使得 $S$ 存在第 $K$ 个字符的情况下，$S$ 的长度。这可以通过一个简短的 `while` 循环实现，不会超时。

接下来我们折半来看，如果当前的 $K$ 处于这个长度的右边一半，那么它是会颠倒大小写的，我们便让记录大小写的 `bool` 变量 $flag$ 进行一次非运算来颠倒，并把 $K$ 重置为 $K - p \div 2$。否则，那么可以直接折半，$K$ 还是老样子，$flag$ 也不变。进行完一轮这个，把 $p$ 缩小，变成 $p \div 2$ 就行啦。

这样的操作要一直做到什么时候呢？一直做到这个 $K$ 呀，已经满足 $K \le |S|$ 啦，那么就一直折半变到了最开始那个 $S$ 的范围内啦。这个时候只要看看 $S_k$ 是什么，再根据 $flag$ 进行或不进行大小写颠倒，最后输出就行啦。

好啰嗦，思路也怪怪的，还是看代码吧，代码倒是简单。

# [赛时 AC](https://atcoder.jp/contests/abc380/submissions/59860616) 代码
你们就爱看这个，我清楚得很。没事，尽管看，就是能够 AC 滴！不过因为赛时调试了一下，导致记录里是有一些注释的，忽略就行，下面这个代码里的，被我删掉啦！

```cpp
#include<bits/stdc++.h>
using namespace std;
int Q,n;
string s;
int main(){
    cin>>s;n=s.size();s=" "+s;
    cin>>Q;
    while(Q--){
        long long k,p=n;cin>>k;
        while(k>p)p<<=1;
        bool flag=0;
        while(k>n){
            long long tmp=k;
            if(tmp>p/2)tmp-=p/2,flag=!flag;
            k=tmp;p/=2;
        }
        if(flag){
            if(s[k]>='A'&&s[k]<='Z')cout<<char(s[k]-'A'+'a')<<" ";
            else cout<<char(s[k]-'a'+'A')<<" ";
        }
        else cout<<s[k]<<" ";
    }
    return 0;
}
```

还是不太难吧？欢迎点赞，谢谢！

---

## 作者：hellolin (赞：3)

下文下标统一从 $0$ 开始。

> **定理**：如果 $\operatorname{bitcount}(i)$ 为奇数，那么第 $i$ 条字符串是反转字符串，否则是正常字符串。（反转指题目中的大小写互换）
>
> **证明**：对于 $i=0$，第 $0$ 条字符串是正常字符串。
>
> 对于 $i>0$，注意到每次操作的本质是将下标二进制向高位扩展了一位，操作后，前半部分这一位都是 $0$，后半部分这一位都是 $1$，下标的 $\operatorname{bitcount}$ 奇偶性恰好与其对应位置相反，而字符串是否反转也相反。
>
> ![](https://cdn.luogu.com.cn/upload/image_hosting/6kj2ski7.png)

算出查询的位置在哪条字符串的什么位置，再根据以上定理得出的反转性回答即可。

时间复杂度 $O(n)$。

---

## 作者：Clover_Lin (赞：2)

## 题目大意
给定一个字符串 $S$，执行 $10^{100}$ 次以下操作：
- 首先，令字符串 $T$ 为字符串 $S$ 中所有大写字母变为小写字母，小写字母变为大写字母的结果。
- 其次，将 $T$ 拼接在 $S$ 后面。

接下来，有一些询问：
- 请输出在所有操作执行完成之后 $S$ 的第 $K$ 个字母。
## 思路
乍一看，好大的数据范围！这题真难！

仔细思考一番发现，我们可以令原始的 $S$ 为一号串，刚开始$T$ 为二号串，然后每一次操作完的字符串就是一号串和二号串的组合。

于是，这题是……找规律？

以下内容为考场上研究的内容：
```text
1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64
1  2  2  1  2  1  1  2  2  1  1  2  1  2  2  1  2  1  1  2  1  2  2  1  1  2  2  1  2  1  1  2  2  1  1  2  1  2  2  1  1  2  2  1  2  1  1  2  1  2  2  1  2  1  1  2  2  1  1  2  1  2  2  1

1           2           3           4           5           6           7           8           9           10          11          12          13          14          15          16
1           2           2           1           2           1           1           2           2           1           1           2           1           2           2           1

1                                               2                                               3                                               4                                     
1                                               2                                               2                                               1                                     
```
解释一下，这堆东西每两行为一组，每组中第一行为位置，第二行为编号（一或二）。第一组是刚才说的一号二号串的组合，第二组就是把第一组中的 `1 2 2 1` 看作一号串，`2 1 1 2` 看作二号串，第三组同理。

规律的话嘛，就是可以发现每一层的规律都一样，最后一层就是 `1 2 2 1`。当然不能直接计算出来了，不过可以递归。单次查询的时间复杂度不高，递归调用的时间复杂度较为合理。$dfs(x)$ 的时间复杂度为线性级的，可以解决本题。
## 代码
[Submission #59860658](https://atcoder.jp/contests/abc380/submissions/59860658)

---

## 作者：__Allen_123__ (赞：2)

> 给定一个格式串 $S$，将按以下方式将其扩展无穷多次：
>
> - 在 $S$ 的后面插入 把 $S$ 的所有字母大小写反转后的字符串。
>
> 求最终的串中第 $k_i(1\le k_i\le 10^{18})$ 个字母是多少。有多组询问。

二进制拆位练手题。

设原来 $S$ 的长度为 $l$，不难想到在第 $i$ 次扩展后，$S$ 的长度为 $l\times 2^{i-1}$，可以通过枚举求出第 $k_i$ 个字符是第几次扩展后被确定的。

根据题意，如果是通过奇数次确定，则大小写将会反转；否则不会反转。并且在反复的减去 $2$ 的幂次以及拆位过程中，我们可以求出其源自原来 $S$ 的哪个字符，问题就求解完成了。

[AC 记录](https://atcoder.jp/contests/abc380/submissions/59851073)。

---

## 作者：qfy123 (赞：2)

# Solution
先找出要输出的字母，然后考虑要不要改变这个字母的大小写。

手模样例，下面用 $1$ 表示需要改变大小写，$0$ 表示不需要改变大小写，则对于第 $i$ 次重复（为了方便说明，重复次数整体向右移一次），有：


|重复次数|0|1|2|3|4|5|6|7|$\dots$|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|此次重复内每个字母是否要改变大小写|0|1|1|0|1|0|0|1|$\dots$|

将 $0,1,1,0,1,0,0,1,\dots$ 这个序列扔进 OEIS，发现这是 Thue-Morse 序列。而对于 Thue-Morse 序列，通项公式长成如下的样子：

$$a_0 = 0,\  a_n = \begin{cases}a_{\frac{n}{2}} & 2 \mid n \\ 1 - a_{n-1} & 2 \nmid n\end{cases}$$

于是对于每次询问，只要求出那个字母在第几次重复内，根据上述通项公式 $O(\log_2 V)$ 地判断要不要改变大小写即可。
# Code
```cpp
#include<bits/stdc++.h>
#define int long long 
#define ull unsigned long long
#define ri register int
#define rep(i,j,k) for(ri i=(j);i<=(k);++i) 
#define per(i,j,k) for(ri i=(j);i>=(k);--i)
#define repl(i,j,k,l) for(ri i=(j);(k);i=(l))
#define IOS ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
#define pc(x) putchar(x)
#define fir first
#define se second 
#define MP pair<int,int>
#define pii pair<int,int>
#define PB push_back
#define lson p << 1
#define rson p << 1 | 1
#define ls(p) tr[p].ch[0]
#define rs(p) tr[p].ch[1]
using namespace std;
char BUFFER[100000],*P1(0),*P2(0);
#define gtc() (P1 == P2 && (P2 = (P1 = BUFFER) + fread(BUFFER,1,100000,stdin), P1 == P2) ? EOF : *P1++)
inline int R(){
    int x;char c;bool f = 0;
	while((c = gtc()) < '0') if(c == '-') f = 1;
	x = c ^ '0';
	while((c = gtc()) >= '0') x = (x << 3) + (x << 1) + (c ^ '0');
	return f?(~x + 1):x;
}
inline string Rs(){
	string str = "";
	char ch = gtc();
	while(ch == ' ' || ch == '\n' || ch == '\r') ch = gtc();
	while(ch != ' ' && ch != '\n' && ch != '\r' && ch > '\0') str += ch, ch = gtc();
	return str;
}
inline int rS(char s[]){
	int tot = 0; char ch = gtc();
	while(ch == ' ' || ch == '\n' || ch == '\r') ch = gtc();
	while(ch != ' ' && ch != '\n' && ch != '\r' && ch > '\0') s[++tot] = ch, ch = gtc();
	return tot; 
}
inline void O(int x){
    if(x < 0) pc('-'),x = -x;
    if(x < 10) pc(x + '0');
    else O(x / 10),pc(x % 10 + '0');
}
inline void out(int x,int type){
	if(type == 1) O(x),pc(' ');
	if(type == 2) O(x),pc('\n');
	if(type == 3) O(x);
}
inline void Ps(string s, int type){
	int m = s.length();
	rep(i, 0, m - 1) pc(s[i]); 
	if(type == 1) pc(' ');
	if(type == 2) pc('\n');
}
inline void pS(char *s, int type){
	int m = strlen(s + 1);
	rep(i, 1, m) pc(s[i]);
	if(type == 1) pc(' ');
	if(type == 2) pc('\n');
}
inline void OI(){
	freopen(".in","r",stdin);
	freopen(".out","w",stdout);
}
const int N = 2e5 + 10;
char c[N];
int n, q, a;
char rev(char c){
	if(isupper(c)) return tolower(c);
	return toupper(c);
}
inline void solve(){
	n = rS(c);
	q = R();
	while(q--){
		int x = R();
		a = 0;
		int idx = x % n ? x % n : n;
		int p = x % n ? x / n : x / n - 1;
		while(p){
			if(p % 2 == 0) p /= 2;
			else a ^= 1, p--;
		}
		if(a) pc(rev(c[idx]));
		else pc(c[idx]);
		pc(' ');
	}
}
signed main(){
    // OI();
    int T = 1;
    // T = R();
	while(T--) solve();
	return 0;
}

```

---

## 作者：_JF_ (赞：1)

[[ABC380D] Strange Mirroring ](https://www.luogu.com.cn/problem/AT_abc380_d)

不算困难。

考虑倒推，思考当前位置 $x$ 是从哪个位置变化过来的，显然只用找到第一个 $2^k\ge x$，那么 $x$ 就是从 $x-2^k$ 变换过来的。

所以，我们只用让 $x$ 变换到 $<n$ 的某个位置就结束，观看变化次数，如果是奇数那就大小写互换，如果是偶数那就不变。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =1e6+10;
#define int long long
#define DEBUG cout<<"when can get npy"<<endl;
int n;
char s[N];
signed main(){
	scanf("%s",s+1); n=strlen(s+1);
	int t; cin>>t;
	while(t--){
		int x;
		cin>>x;
		if(x<=n)	{cout<<s[x]<<' '; continue;}
		int dus=0;
		while(x>n){
			for(int i=0;i<=60;i++){
				__int128 now=(1ll<<i)*(__int128)n;
				if(now>=x){
					int prelst=now/2+1;
					x=(x-prelst+1);
					dus++;
					break;
				}
			}
		}
		if(dus%2==0)	cout<<s[x]<<' '; 
		else{
			if(s[x]>='A'&&s[x]<='Z')	cout<<(char)(s[x]-'A'+'a')<<' ';
			else	cout<<(char)(s[x]-'a'+'A')<<' ';
		}
	}
	return 0;
}

```

---

## 作者：zjj2024 (赞：1)

### 思路
发现操作是一个倍增的过程。

考虑每次得到这个位置在上一次操作时的位置和大小写改变的状态。

每上一层大小写状态改变。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	string s;
	int T;
	cin>>s>>T;
	int n=s.size();
	s=' '+s;
	while(T--)
	{
		ll k;
		cin>>k;
		bool flag=0;
		ll c=1;
		while(c*n<k)c<<=1;//得到这一个位置在那一层
		c>>=1;
		while(k>n)
		{
			k-=c*n;
			flag^=1;
			while(c*n>=k&&c)c>>=1;//得到这一个位置在那一层
		}
		if(k==0)k=n;
		if(flag)
		{
			if(s[k]>='a')cout<<char(s[k]-32)<<' ';
			else cout<<char(s[k]+32)<<' ';
		}
		else cout<<s[k]<<' ';
		//cout<<flag<<"   ";
	}
	return 0;
}
```

---

## 作者：201012280925LSY (赞：0)

## 简要题意
你有一个字符串 $s$。接下来对这个字符串 $s$ 操作 $10^{100}$ 次。每次操作会对当前的字符串 $s$ 的大小写反转，即 $s_i$ 如果为大写字母，变成小写字母；如果 $s_i$ 如果为小写字母，变成大写字母。令 $s'$ 为 $s$ 大小写反转之后形成的字符串。然后把 $s'$ 拼接到 $s$ 后面。

然后有 $Q$ 次询问，每次询问给出一个数 $x$，请你输出在操作 $10^{100}$ 次之后的 $s_k$。

## 思路
预处理出操作 $10^{100}$ 次的字符串 $s$，显然不可能。

反过来思考。

令 $N$ 为初始的字符串 $s$ 的长度。

我们先对处理出是在第几个长为 $N$ 的字符串中，然后这个 $k$ 为这个值。

我们令 $0$ 为这个字符串没有大小写反转，$1$ 为这个字符串大小写反转的状态。然后可以得出一个 `01` 字符串。

则第 $1$ 次操作的 `01` 字符串为：`10`。

第 $2$ 次操作的 `01` 字符串为: `1001`。

第 $3$ 次操作的 `01` 字符串为 `10010110`。

但是预处理这个玩意，空间也不允许。

注意到这个玩意，每次都是上一次的两倍。

定义一个变量 $flag$，为 $0$ 表示这一段字符串和初始字符串一样，为 $1$ 表示这一段字符串是初始字符串大小写反转的，初始值为 $0$。

我们先处理出，第一个比 $k$ 大的 $2$ 的幂，并令这个 $2$ 的幂为 $p$。然后我们循环，在每次循环中，先对 $p \div 2$。如果当前的 $k>p$，则把 $k$ 变为 $k-p$，并且把 $flag \oplus 1$（因为反转 $2$ 次就相当于没反转）。如果 $k \le p$，则什么事也不做。

最后得出的 $flag$ 就是这一段字符串的状态。

对 $x \bmod N$，处理出是在这个长为 $N$ 的字符串的第几个位置。

最后输出对应位置的大小写状态即可。

由于笔者的水平较低，所以可能讲的比较抽象。可能在代码里会好一些。

具体见代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
string st;
long long n;
bool flag=0;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>st;
	cin>>n;
	while(n--)
	{
		long long x,k;
		cin>>x;
		k=(x-1)/st.size()+1;//第几段长度为 N 的字符串。 
		x=(x-1)%st.size()+1;//在这一段字符串中是第几个位置。 
		long long p=1;
		while(p<k)p<<=1;//第一个比它大的二的幂 
		flag=0;
		p>>=1;
		while(p)//循环 
		{ 
			if(k>p)//> 
			{
				k-=p;
				flag^=1; 
			}
			p>>=1;
		}
		if(flag==1)//反转的状态 
		{
			if(st[x-1]>=97)cout<<char(st[x-1]-32)<<" ";
			else cout<<char(st[x-1]+32)<<" "; 
		}
		else//没反转的状态 
		{
			cout<<st[x-1]<<" ";
		}
	}
	return 0;
}
```

---

## 作者：Binah_cyc (赞：0)

一道位运算找规律好题。

首先，当没有反转操作的时候，这道题将会变得十分简单：只需要将每一次的 $k$ 对 $n$ 取模，即可求出这个数在原字符串中对应的位置。

但是它引入了反转，这道题就变复杂了。考虑计算出该字符是否反转。

注意，该段的位置一词与上一段的含义不同，它表示某一个原串在最终的字符串中的位置。我们发现一个十分简单的结论：在每一次操作结束时，序列必定是由 $2$ 的整次幂个原串组成。同时，一个位置在反转之后所对应的位置就是在它原有的位置的基础上再加上序列长度。因此，一个位置反转，在二进制下就是在二进制高位添加一个 $1$，二的整次幂变化时为在末尾加 $0$。

![此处应有图片描述](https://cdn.luogu.com.cn/upload/image_hosting/692qjuex.png)

上图中，每一个方格表示一个原字符串，红色表示字符大小写不进行变化，黄色表示字符大小写较原串发生变化。

从这个图我们可以看出，第 $9$ 个位置是由第 $1$ 个位置经过变化来的。第 $7$ 个位置是由第 $3$ 个位置变化来的，就是由第 $1$ 个位置通过两步变化得来的。同时，$4$ 是由 $2$ 变化而来，也就是由 $1$ 通过两次变化得到。

随后，我们考虑如何从一个位置反推回它是由原串如何变化得到的。

由上面的结论，易得对于该位置，每一次都移除它最高位的 $1$，表示找它是由哪一个位置变化而来。在还剩最后一个 $1$ 的时候，我们取它二进制下后缀 $0$ 的个数表示它经过了多少次变化。

代码
```c
// LUOGU_RID: 189552560
// Problem: D - Strange Mirroring
// Contest: AtCoder - AtCoder Beginner Contest 380
// URL: https://atcoder.jp/contests/abc380/tasks/abc380_d
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
#define int long long
#define push_back emplace_back
int n,q;
string s;
signed main()
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>s,n=s.length(),s="$"+s;
	cin>>q;
	while(q--)
	{
		int x;
		cin>>x;
		int a=x%n,b=(x+n-1)/n;
		//a表示它在原串中对应了哪一个位置，b表示它作为一个字符串在最终字符串中的位置
		if(!a) a=n;
		int flag1=(__builtin_popcountll(b)-1)&1,flag2=__builtin_ctzll(b)&1;
		//flag1表示2进制下1的个数-1,代表需要经过多少次转化才能变成2的整次幂
		//flag2表示2进制下后缀0的个数,代表在转化为2的整数次幂之后还需要转化多少次
		//由于操作偶数次等同于没操作,我们只需要看操作次数的奇偶性即可
		if(flag1^flag2)//在操作之后大小写改变
		{
			if('a'<=s[a]&&s[a]<='z') cout<<(char)(s[a]-'a'+'A')<<' ';
			else cout<<(char)(s[a]-'A'+'a')<<' ';
		}
		else cout<<s[a]<<' ';
	}
	return 0;
}
```

---

## 作者：Genius_Star (赞：0)

### 思路：

设我们要找第 $x$ 个位置的字符；若 $x \le n$，则直接返回 $s_x$。

否则，找到一个最大的 $l$，使得 $n2^l < x$，那么求第 $x$ 个位置的字符相当于第 $x - n2^l$ 位置的值取反。

于是递归处理即可，时间复杂度为 $O(\log^2 W)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#define Add(x,y) (x+y>=mod)?(x+y-mod):(x+y)
#define lowbit(x) x&(-x)
#define pi pair<ll,ll>
#define pii pair<ll,pair<ll,ll>>
#define iip pair<pair<ll,ll>,ll>
#define ppii pair<pair<ll,ll>,pair<ll,ll>>
#define fi first
#define se second
#define full(l,r,x) for(auto it = l; it != r; ++it) (*it)=x
#define Full(a) memset(a, 0, sizeof(a))
#define open(s1,s2) freopen(s1, "r", stdin), freopen(s2, "w", stdout);
#define For(i,l,r) for(register int i = l; i <= r; ++i)
#define _For(i,l,r) for(register int i = r; i >= l; --i)
using namespace std;
using namespace __gnu_pbds;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const int N = 4e5 + 10;
inline ll read(){
    ll x = 0, f = 1;
    char c = getchar();
    while(c < '0' || c > '9'){
        if(c == '-')
          f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9'){
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		x = -x;
	}
	if(x > 9)
	  write(x / 10);
	putchar(x % 10 + '0');
}
ll n, q, x;
char s[N];
char query(ll x, bool f){
	if(x <= n){
		if(!f)
		  return s[x];
		else{
			if(s[x] >= 'A' && s[x] <= 'Z')
			  return s[x] - 'A' + 'a';
			else
			  return s[x] - 'a' + 'A';
		}
	}
	ll k = n;
	while(k * 2 < x)
	  k <<= 1;
	return query(x - k, f ^ 1);
}
bool End;
int main(){
	scanf("%s", s + 1);
	n = strlen(s + 1);
	q = read();
	while(q--){
		x = read();
		putchar(query(x, 0));
		putchar(' ');
	}
	cerr << '\n' << abs(&Begin - &End) / 1048576 << "MB";
	return 0;
}
```

---

## 作者：zengziqvan (赞：0)

考虑分治，设做了 $k$ 次操作后 $S$ 长度到达 $\max{K_i}$。则 $k$ 的量级一定是 $\log \frac{10^{18}}{n}$ 级别的，其中 $n$ 表示 $S$ 长度。

假设不考虑取反，则 $K_i$ 一定在某个被复制的最初的 $S$ 之内，记变量 $c$ 表示 $K_i$ 是否被改变大小写。

---

考虑将开始的大串分成两部分 $S'$ 与 $T'$，求出两部分的长度并考虑 $K_i$ 在哪一半：

- 在左半段，说明没有改变大小写，$c$ 不变，并继续考虑左半部分。

- 在右半段，说明改变过大小写，$c$ 异或 $1$，并继续考虑右半部分。

至于左半段、右半段怎么考虑，请重新从分界线开始往下读。

当分治到长度为 $1$ 的时候，已经确定了当前字母是否被改变大小写，只要求出不考虑取反后第 $K_i$ 个字母即可，这可以通过取模轻松得出。

复杂度 $O(Q\log V)$，其中 $V$ 是 $K_i$ 的值域。

```c++
int n,q;
char a[200010];
char change(char a) {
	if(a>='a'&a<='z') return a-32;
	else return a+32;
}
int st(int x) {
	return !x?n:x;
}
main() {
	scanf("%s",a+1);
	n=strlen(a+1);
	cin>>q;
	int op=log(1000000000000000000LL/n)/log(2)+1;
	while(q--) {
		LL k,num;cin>>k;
		int ps=0;
		ROF(j,op,1) {
			LL l1=1,r1=n*(1LL<<(j-1)),l2=r1+1,r2=n*(1LL<<j);
			if(k>=l1&&k<=r1) ;
			else ps^=1,k-=r1;
		}
		if(ps) cout<<change(a[st(k)])<<" ";
		else cout<<a[st(k)]<<" ";
	}
	puts("");
	return 0;
}
```

---

