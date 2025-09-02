# Fake News (medium)

## 题目描述

Thanks to your help, Heidi is confident that no one can fool her. She has now decided to post some fake news on the HC $ ^{2} $ Facebook page. However, she wants to be able to communicate to the HC $ ^{2} $ committee that the post is fake, using some secret phrase hidden in the post as a subsequence. To make this method foolproof, she wants the phrase to appear $ n $ times in the post. She is asking you to design a post (string) $ s $ and a hidden phrase $ p $ such that $ p $ appears in $ s $ as a subsequence exactly $ n $ times.

## 说明/提示

An occurrence of $ p $ as a subsequence in $ s $ should be thought of as a set of positions in $ s $ such that the letters at these positions, in order, form $ p $ . The number of occurences is thus the number of such sets. For example, ab appears 6 times as a subsequence in aaabb, for the following sets of positions: $ {1,4},{1,5},{2,4},{2,5},{3,4},{3,5} $ (that is, we should choose one of the a's and one of the b's).

## 样例 #1

### 输入

```
2
```

### 输出

```
hHheidi Hei```

## 样例 #2

### 输入

```
4
```

### 输出

```
bbbba ba```

## 样例 #3

### 输入

```
6
```

### 输出

```
aaabb ab```

# 题解

## 作者：DPair (赞：4)

构造好题。

## 【前言】
今天乱找找到的一道题，瞎搞了半个多小时不会做，打开题解一看发现一点说明都没有，网上题解也都只提供了构造方法，这里给出详细思路和正确性说明。

## 【思路】
首先看到数据范围是 $1e5$ ，并且发现他只给了我们 $52$ 个可用字符，到这里应该容易想到要用 $log$ 级别的构造方法。

考虑递归分治。

首先不难发现对于两个字符串 $A$ 和 $B$ ，若 $B$ 在 $A$ 中作为子序列出现过的次数为 $x$ ，那么字符串 $B+c$ 在 $A+c+c$ 中出现过的次数一定恰好为 $2x$ （其中 $c$ 为未在 $A$ 、 $B$ 中出现过的字符）。

这个结论其实挺显然的，对于原 $A$ 中的每一个子序列 $B$ ，都有恰好出现了两个 $c$ 使得子序列变为 $B+c$ ，因此子序列数一定是 $\times 2$ 的。

于是我们大概有了一个把算法变为 $log_2$ 级别的大体思路，并且基本可以解决 $n=2^k(k\in Z)$ 的问题了。

然后我们发现，我们解决不了的是 $n$ 为奇数的所有子问题。

由于奇数可以表示为 $2k+1(k\in Z)$ 的形式，考虑怎么给他加上一个 $1$ 。

~~然后我就想了好久再然后就he题解去了~~

最初的的想法是这样的：

对于 $A,B,c$ （具体定义见上文）：

考虑这样构造使得原先的 $x$ 变为 $2x+1$：

$$
B->B+c,A->B+A+c+c
$$

很显然这个构造是错的，比如构造
$$
ABB ~~~~ AB ~~~~ C ~~~~~~~~~ x=2
$$
时，会出现这样的字符串（这里举出反例是为了下面的说明）：
$$
ABCABBCC~ABC
$$
（这里 $x=11$ ，是不是有些什么意思了？）

但给了一个很好的思路：在 $A$ 前面加上一个 $B$。

发现这个构造错误的原因在于前面加上的这个 $B$ 与后面的 $c$ 产生了关联，因此我们考虑如何消除这种关联。

我们发现上面的构造中 $A$ 这个**字符**出现了两次，并且每一次都造成了 $BBCC$ 权值为 $4$ 的贡献，然后 $B$ 也多出现了一次，导致最终的 $x$ 变为了 $4 + 4 +1+2$ 。

接下来我们只需要想出如何消除这种影响就 $AC$ 此题了。

我们知道，这种影响是新增的 $A$ 、 $B$ 造成了重复的贡献造成的，考虑消除这种重复贡献，由于新增的 $1$ 必不可少，考虑从源头上消除，即删去**后面的** $AB$ ，变为：

$$
ABCBCC~ABC
$$

发现正好是 $x=5$，岂不美哉？

因此考虑这么构造，先按原方法构造，只改变边界状态（发现此时边界为 $x=1$ 或 $x=2$ ），然后在 $A$ 前加上一个 $B$ 即可完成统一加 $1$ 的操作。

但是，我们又发现这时偶数出现了问题，因为我们统一加上了 $1$ ，但是此时我们只需再 $+1$ 即可，而且经过我们对于构造方法的改造，这次 $+1$ 简单许多，即这样变化：

$$
A=c+A+c+c~(A~mod~2=0)
$$

$$
A=A+c+c~(A~mod~2=1)
$$

最终答案为：
$$
A=B+A
$$

由于我们的边界条件删去了最初的 $A$ **字符** ，也就是说，全场只有一个 $A$ **字符**对后面产生贡献，那么每一次 $A$ **串**前的新字符恰好产生 $1$，的贡献。串后的新字符产生$2x$的贡献。

总结下来，就是在分治的大思路下，对于奇数的子问题， $2x$ 由经典的**加两个**$c$，产生贡献，剩下的 $1$ 由最后在 $A$ 串前加的 $B$ 串产生贡献（每个数都会受到贡献哦，具体的不好说明，留给读者自行思考）；然后对于偶数的子问题，在奇数的基础上再 $+1$ 即可。

## 【正确性】
首先这个算法是 $log$ 级的，最终用到的字符个数也是 $log$ 级的，甚至用不上小写字母。

对于另一个限制条件 $200$ ，根据我们的构造方法，每一次最多增加3个字符，增加 $log$ 级次，最后连 $100$ 个字符也不会超过（实测 $n=1e5$ 时 $A$ 字符串长度为 $53$ ）。

所以这个方法是可行的。

## 【代码】
```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
string a, b;
char c;
void work(int x){
    if(x == 1){
        c = 'A';a = "";b = c;
        return ;
    }
    if(x == 2){
        c = 'B';a = "B";b = "AB";
        return ;
    }
    if(x & 1){
        work(x >> 1);
        c ++;
        a = a + c + c;
        b = b + c;
    }
    else{
        work((x >> 1) - 1);
        c ++;
        a = c + a + c + c;
        b = b + c;
    }
}

int main(){
    scanf("%d", &n);
    work(n);
    cout << b + a << ' ' << b;
    return 0;
}
```

---

## 作者：Imakf (赞：3)

## Legend

[Link](codeforces.com/problemset/problem/802/H) $\textrm{to Codeforces}$。

给定 $n$，求两个字符串 $s,t$，使得 $t$ 在 $s$ 中作为子序列出现了恰好 $n$ 次。

$1 \le n \le 10^6$，$|s|,|t| \le 200$。

## Editorial

我想起有一道题，它是构造 $1447$ 作为子序列的个数。也是 cf 的。

我就想啊，能不能用三个字符也做这道题呢？

那道 $1447$ 的题限制字符串长度比较宽松，所以做法就是：

$14444444444\cdots444$

然后把一堆的 $7$ 贪心从右往左插入，如果左边有 $k$ 个 $4$，那么就贡献了 $\binom{k}{2}$。

受到这个做法的启发，我们来看这个题。

它没有限制组合数的下面一定是 $2$，也就是 $\binom{k}{2} \to \binom{k}{x}$，而我们可以任意选取这个 $x$！

经过一番打表……（打表代码放在最后）

```plain
x = i
cnt 为估计最坏情况次数
mxneed 表示连续 '4' 段的长度最长是多少

i = 3 cnt = 366 mxneed = 182
i = 4 cnt = 145 mxneed = 71
i = 5 cnt = 91 mxneed = 43
i = 6 cnt = 70 mxneed = 32
i = 7 cnt = 63 mxneed = 27
i = 8 cnt = 58 mxneed = 24
i = 9 cnt = 59 mxneed = 23
i = 10 cnt = 59 mxneed = 22
i = 11 cnt = 62 mxneed = 22
i = 12 cnt = 62 mxneed = 22
i = 13 cnt = 65 mxneed = 22
i = 14 cnt = 67 mxneed = 23
```

我们可以发现大约 $x$ 取 $x=8$ 的时候是相当优秀的，可以通过这个题。

复杂度不会算，但是显然可以过。

## Code

代码非常好写，只需要预处理组合数即可。

```cpp
#include <bits/stdc++.h>

int C[1000][1000];

void init(){
	for(int i = 0 ; i < 1000 ; ++i) C[i][0] = 1;
	for(int i = 1 ; i < 1000 ; ++i){
		for(int j = 1 ; j < 1000 ; ++j){
			C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
		}
	}
	int cnt = 0 ,mxneed;
	for(int i = 3 ; i <= 100 ; ++i){
		cnt = 0 ,mxneed = 0;
		for(int j = 1 ; C[j][i] <= 1e6 ; ++j){
			mxneed = j;
			if(C[j - 1][i]) cnt += ((C[j][i] - 1 - C[j - 1][i]) / C[j - 1][i]) + 1;
			
		}
		// printf("i = %d cnt = %d mxneed = %d\n" ,i ,cnt + 2 + mxneed ,mxneed);
	}
}

int pos[1000];

int main(){
	init();
	putchar('a');
	int n; std::cin >> n;
	for(int i = 24 ; n ; --i){
		int cnt = n / C[i][8];
		pos[i] = cnt;
		n -= cnt * C[i][8];
	}
	for(int i = 1 ; i <= 24 ; ++i){
		putchar('b');
		while(pos[i]--) putchar('c');
	}
	puts(" abbbbbbbbc");
}
```

---

## 作者：米奇奇米 (赞：3)

```
#include<bits/stdc++.h>
using namespace std;
int n;
char now;
string s,t;
void solve(int len)
{
    if(len==1) 
    {
        s="";
        t="a";
        now='a';
        return;
    }
    if(len==2)
    {
        s="b";
        t="ab";
        now='b';
        return;
    }
    if(len%2==0)
    {
        solve(len/2-1);
        now++;
        s=now+s+now+now;
        t=t+now;
        return;
    }
    if(len%2==1)
    {
        solve(len/2);
        now++;
        s=s+now+now;
        t=t+now;
        return;
    }
}
int main()
{
    scanf("%d",&n);
    solve(n);
    cout<<t<<s<<" "<<t;
    return 0;
}
```

---

## 作者：CSP_Sept (赞：2)

节选自我的 [**杂题选做 [S-C1]**](https://www.luogu.com.cn/blog/supervise/s-c-1) _07_。

## 题意

构造字符串 $s,p$，使字符串 $s$ 的为 $p$ 的子序列恰有 $n\ (1\le n\le 10^6)$ 个。

## 解法

萌萌 \*2200！一种新的做法，感觉思路比较牛逼。

我首先想到了 [CF1368B Codeforces Subsequences](https://codeforces.com/contest/1368/problem/B)，不同的是，这道题是**至少** $n$ 个。

一个朴素的想法是，对于恰好有 $k$ 个子序列的情况 $(s,p)$，我们可以实现 $k\to 2 k$。

具体地，任取一个**新字符** $c$，令 $s'=scc$，$p'=pc$ 即可（这里直接用字符串拼接表示了）。

但是我们不能实现 $k\to k+1$。这是很困难的。否则我们可以直接二进制拆分 $n$ 解决。

考虑另一个思路，假设对于恰好有 $k$ 个子序列的情况 $(s,p)$，$s$ 可以被表示为 $pu$（$u$ 也是一个字符串），任取一个新字符 $c$，那么我们可以实现

- $k\to 2 k+1$：令 $s'=pcucc$，$p'=pc$ 即可；
- $k\to 2 k+2$：令 $s'=pccucc$，$p'=pc$ 即可。

这之后我们均直接可以更新 $u'$。

于是我们递归地解决这个问题即可。考虑每次处理 $x$ 时，先解决 $\left\lfloor\frac{x-1}2\right\rfloor$ 时的情况，再回溯解决。容易发现这是合理的。

边界是 $x=1,2$。这个也是平凡的，只需要使 $p=\texttt a$ 即可。

这个是很对的，不考虑 string 类的复杂度是 $O(\log n)$。由于 $2^{26}>10^6$，我们可以仅用小写字母解决本题。

## 代码

```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>

#define N 105
#define ll long long

using namespace std;

inline ll rd() {
	char c;
	bool flag = 0;
	while ((c = getchar()) < '0' || c > '9')
		if (c == '-')
			flag = 1;
	ll res = c - '0';
	while ((c = getchar()) >= '0' && c <= '9')
		res = (res << 3) + (res << 1) + c - '0';
	return flag ? -res : res;
}

int n;
string s, p, u;
char cnt = 'a';

void dfs(int x){
	if(x == 1){
		s = p = "a";
		u = "";
		return;
	}
	else if(x == 2){
		s = "aa";
		p = u = "a";
		return;
	}
	dfs((x - 1) / 2);
	cnt++;
	if(x & 1){
		s = p + cnt + u + cnt + cnt;
		u = u + cnt + cnt;
		p = p + cnt;
	}
	else{
		s = p + cnt + cnt + u + cnt + cnt;
		u = cnt + u + cnt + cnt;
		p = p + cnt;
	}
}

int main() {
	n = rd();
	dfs(n);
	cout << s << ' ' << p << endl;
	return 0;
}
```

- **UPD20230901** 改了些 typo。

---

## 作者：lfxxx (赞：1)

考虑来点乱搞。

首先记 $c^i$ 表示 $i$ 个字符 $c$ 拼接形成的字符串，字符串加法代表拼接。

下文用数字代替字符。

考虑构造 $1^{s_1} + 2^{s_2} + 3^{s_3} + ... + l^{s_l} + 1 + 2 + 3 + ... + l$ 作为字符串 $s$，构造 $1 + 2 + 3 + ... + l$ 作为字符串 $p$，于是可以发现出现次数为 $1+s_1 \times (1+s_2 \times (... \times (1+s_l)))$。

那么考虑对于 $n$ 判断其是否是 $2$ 或者 $3$ 的倍数，如果是，那么除以 $2$ 或 $3$ 后减去 $1$ 否则直接减去 $1$，也就是对应了 $s = 2,3,1$ 的情况，直到用完 $30$ 个字符后，此时一定进行了 $O(\log n)$ 次除以 $2$ 或 $3$ 的操作，所以当前的 $n$ 一定很小，直接令 $s$ 等于其减 $1$ 即可，由于 $O(1)$ 次操作后一定会至少折半，所以总操作次数也是 $O(\log n)$ 的，总操作次数就是可以通过的。


```cpp
#include<bits/stdc++.h>
using namespace std;
//#define int long long
//#define lowbit(x) (x&(-x))
//#define bp push_back
//#define sz size
//#define cl clear
vector<int> S;
char v(int u){
	if(u<=26) return 'a'+u-1;
	else return 'A'+u-27;
}
void solve(int u,int h){
	if(h==30||u<=5){
		S.push_back(u-1);
		return ;
	}
	if((u-1)%2==0){
		S.push_back(2);
		solve((u-1)/2,h+1);
	}else if((u-1)%3==0){
		S.push_back(3);
		solve((u-1)/3,h+1);
	}else{
		S.push_back(1);
		solve(u-1,h+1);
	}
}
int main(){
	int n;
	cin>>n;
	solve(n,1);
	for(int i=1;i<=(int)S.size();i++){
		int x=S[i-1];
		for(int j=1;j<=x;j++) cout<<v(i);
	}
	for(int i=1;i<=(int)S.size();i++) cout<<v(i);
	cout<<'\n';
	for(int i=1;i<=(int)S.size();i++) cout<<v(i);
	return 0;
}
```

---

## 作者：zyh_helen (赞：1)

这个题应该有好多种做法，这是一种和洛谷题解区不同的做法。

---
---

考虑构造一个形如这样的 $s$ 序列：

$\texttt{abc\dots aaa\dots aa bbb\dots bb ccc\dots cc\dots}$

即开头一段字符，每种字符在后面依次又出现了若干次。

我们设第 $i$ 个字符出现了 $b_i$ 次，共有 $c$ 个字符。

那么 $t$ 序列应为：

$\texttt{abc\dots}$

即 $s$ 序列开头的那段字符。

---

那么 $t$ 序列在 $s$ 中出现了 $\sum_{i=0}^{c}\Pi_{j=i+1}^c b_j$ 次。

为什么呢，这样考虑：

- 若不使用开头的那段字符，显然 $t$ 序列将会出现 $\Pi_{i=1}^c b_i$ 次；

- 若仅使用开头那段字符的第一个，那么便不再会使用后面 $b_1$ 个字符中的任何一个了，$t$ 序列将会出现 $\Pi_{i=2}^c b_i$ 次；

- 若要使用开头那段字符的第二个，必将使用第一个，所以不再会使用后面 $b_1$ 个字符和 $b_2$ 个字符中的任何一个了，$t$ 序列将会出现 $\Pi_{i=3}^c b_i$ 次了；

- 依此类推，若要使用开头那段字符的前 $i$ 个，$t$ 序列将会出现 $\Pi_{j=i}^c b_j$ 次。

---

既然有了这个式子，很自然的能联想到进制，又因为没有系数，所以就使用二进制，可以通过控制 $b_i$ 的大小来控制系数为 0 或 1。

我们令所有 $b_i=2$，那么 $t$ 出现总次数为 $\sum_{i=0}^c 2^i$ 次，即二进制表示下所有位数都是 1。

考虑如何将二进制下某位改为 0。

- 若要将第 $i$ 位改成 0，可以先把 $b_i$ 缩小至原来 $\frac{1}{2}$，这样该位的值由 $2^{i+1}$ 变为 $2^i$，又因为第 $i+1$ 个字符的值为 $2^i$，所以这两位相加的值由 $2^{i+1}+2^i$ 变为了 $2^{i+1}$；

- 但是这样该位前面所有位都将缩小至 $\frac{1}{2}$ 所以我们将第 $b_{i-1}$ 扩大至原来 2 倍，这样便完成了二进制下某位改为 0。

---
---

考虑计算总长度，容易看出的是总长度一定小于 $5\times \log n$（每一位最多扩大至 2 倍，加上开头的那段字符）。

但事实上最长总长度远比这个小，原因是改为 0 同样需要将此位缩小至 $\frac{1}{2}$，所以最长的字符串应在 $n$ 的二进制表示为这种情况下出现：

$\text{1010101010\dots}$

易算出总长度最长为 $\frac{7\times\log n}{2}$，即 70 左右。

---

总字符个数则更为简单，肯定就是 $n$ 的二进制表示位数了，即使用 $\log n$ 个字符，20 个左右。

---
---

代码相当简洁。

```cpp
#include<bits/stdc++.h>
#define int long long
//#define double long double
#define y1 yyyyyyyyyyyyyyyy1
using namespace std;
const int N = 2e6 + 10, M = 8000, mod = 998244353;
const double eps = 1e-7, pi = 3.1415926, inf = 1.6e11;
/*
		    	           _      _        _          
			       ____  _| |_   | |_  ___| |___ _ _  
			      |_ / || | ' \  | ' \/ -_) / -_) ' \ 
			      /__|\_, |_||_|_|_||_\___|_\___|_||_|
			          |__/    |___|                              
				       
*/

//int head[N], tot = 1;
//struct edge{
//	int t, f;
//	char c;
//	int next;
//}e[N << 1];
//void edge_add(int u, int v, char c){
//	e[++tot].next = head[u];
//	e[tot].t = v;
//	e[tot].f = u;
//	e[tot].c = c;
//	head[u] = tot;
//}
//int qmr(int x, int a){
//	x %= mod;
//	int ret = 1, p = x;
//	while(a){
//		if(a & 1)ret = ret * p % mod;
//		p = p * p % mod;
//		a >>= 1;
//	}
//	return ret;
//}


int n, m, a[30];
string s;
signed main(){
	cin >> n;
	if(n == 1){
		cout << "a a";
		return 0;
	}
	int m = 0;
	for(int i = 0;i <= 21;i++){
		if(n & (1 << i))m = i;
		a[i] = 2;
	}
	for(int i = 0;i < m;i++){
		if(!(n & (1 << i)))a[i] /= 2, a[i + 1] *= 2;
		while(a[i]--)s = (char)('a' + m - 1 - i) + s;
	}
	for(int i = 0;i < m;i++)putchar('a' + i);
	cout << s << " ";
	for(int i = 0;i < m;i++)putchar('a' + i);
	return 0;
}

---

## 作者：Redshift_Shine (赞：0)

推荐大家都去 [duel](https://algorithm-duels.online/)，可以有效激发自己的潜力。

我和队友组队打 3v3，看到队友都有 A 题后绞尽脑汁思考这一题，然后就过了，看到洛谷评分为紫而且还能写题解感到惊诧，于是赶紧写一发。

注意到

$$
f(\overline{c_1c_1c_2c_2c_3c_3\dots c_nc_nc_1c_2c_3\dots c_n},\overline{c_1c_2c_3\dots c_n})=2^{n+1}-1
$$

考虑在中间的 $c_n$ 和 $c_1$ 中间插点东西。然后我们发现，只需要在中间插入 $c_x$，答案就会增加 $2^{x-1}$。只要按照 $x$ 倒序插入就不会产生重复贡献。

然后，这道题就做完了。

时间复杂度 $O(\log n)$。

```c++
// #define Redshift_Debug
#ifdef Redshift_Debug
#define debug(...) fprintf(stderr, __VA_ARGS__)
#include <chrono>
#else
#define debug(...)
#endif
#include <cstdio>
#include <iostream>
#include <string>
using namespace std;
const int N = 1e6 + 10;
string s, t;
/*
 */
char ch;
int n, tn, ts;
void run()
{
	ch = 'a';
	scanf("%d", &n);
	/*
	aabbccddabcd abcd
	0 0 0 0
	1 0 0 0
	2 0 0 0
	2 2 0 0
	2 4 0 0
	2 4 4 0
	2 4 8 0
	2 4 8 8
	2 4 8 16
	3 4 8 16
	3 7 8 16
	3 7 15 16
	3 7 15 31
	aabaab ab
	*/
	if (n == 1)
	{
		puts("a a");
		return;
	}
	if (n == (n & -n))
	{
		while (n != 1)
			s += ch, s += ch, t += ch, ch++, n >>= 1;
		cout << s << ' ' << t << '\n';
		return;
	}
	ts = 3;
	while (ts <= n)
	{
		s += ch, s += ch, t += ch, ch++;
		ts = (ts << 1 | 1);
	}
	ts >>= 1;
	n -= ts;
	ts = (ts >> 1) + 1;
	while (ts)
	{
		if (n & ts)
		{
			s += ch;
			if (ch > t.back())
				t += ch;
		}
		ch--;
		ts >>= 1;
	}
	s += t;
	cout << s << ' ' << t << '\n';
}
int main()
{
#ifdef Redshift_Debug
	auto st = chrono::high_resolution_clock::now();
#endif
	run();
#ifdef Redshift_Debug
	auto ed = chrono::high_resolution_clock::now();
	fprintf(stderr, "%.9lf\n", (ed - st).count() / 1e9);
#endif
}
```

---

## 作者：_ZHONGZIJIE0608_ (赞：0)

首先考虑分解质因数后按照质数因子来排字母。但是这样会导致字数过多。

发现应该是一个类似于 $\log$ 或者高次根号的长度。你考虑从一个较为简单的串，如 `CCCP` 入手。（想想为什么用这个串）

如果 `P` 前面有 $c(c \ge 4)$ 个 `C`，那么显而易见，`CCCP` 在这个串里的出现次数是 $\binom{k}{3}$。

拓展之后，`CCCCPCCCCCCP` 这个串中，左起第一个 `P` 前面有 $4$ 个 `C`，第二个前面有 $10$ 个 `C`，所以总的出现次数为 $\binom{10}{3}+\binom{4}{3}$。

但是打表发现 $3$ 个 `C` 在 $200$ 的长度范围内不够用，考虑把 `C` 扩展到 $6$ 个，方案数更多。

于是对于 $n$，我们把它按照类似于进制拆分的方法拆成若干个 $\binom{k}{6}$ 的和。

然后从小到大，不断增加 `C` 的个数，如果到了一个需使用的数就加一个 `P`。

那么构造的匹配串就是 `CCCCCCP`。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
int C[1010][1010];
signed main(){
    ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
    cin>>n;int cnt=0;
    for(int i=0;i<=1000;++i)C[i][0]=C[i][i]=1;
    for(int i=1;i<=1000;++i){
        for(int j=1;j<i;++j){
            C[i][j]=C[i-1][j]+C[i-1][j-1];
        }
    }
    vector<int>ans;
    for(int i=75;i>=6;--i){
        while(C[i][6]<=n){
            n-=C[i][6];
            ans.push_back(i);
        }
    }
    sort(ans.begin(),ans.end());
    for(int i=1;cnt<(int)ans.size();++i){
        cout<<"C";
        while(i==ans[cnt]){
            cout<<"P";
            ++cnt;
        }
    }
    cout<<" CCCCCCP";
    return 0;
}
```

---

## 作者：_Wind_Leaves_ShaDow_ (赞：0)

纪念一下第一次独立切掉紫构造。

因为过多的字符会让序列不好构造，我们尝试用数量更少的字符通过此题。

因为要用到 $n$，所以令输入为 $x$，$n$ 是序列长度，$m$ 是子序列长度。

如果只有一种字符，那么答案固定为 $\binom{n}{m}$，，显然不可能满足所有输入情况。

考虑用两种字符构造。通过一种字符的做法我们发现答案应该跟组合数有关。考虑最后得到的子序列是 `ab`。那么每个 `a` 都能跟后面的 $k$ 个 `b` 组合，造成 `k` 的贡献。就是说我们构造的每个 `a` 对答案的贡献是后面 `b` 的数量。显然在 $n\le200$ 的情况下无法满足所有 $x\le10^6$。

如果最后得到的是 `abb`，每个 `a` 对答案造成的贡献是 $\binom{k}{2}$，$k$ 是它后面的 `b` 的个数。经过手算可以发现这个东西也无法满足所有 $x\le10^6$，但是个数明显较 `ab` 有很大增长。

尝试 `abbb`，每个 `a` 对答案的贡献是 $\binom{k}{3}$，经过估算发现是可以满足所有 $x\le10^6$ 的数据的。

因为 $\binom{3}{3}=1$，我们不需要考虑最后 $x$ 减不完的情况，每次挑选最大的可以减去的 $\binom{k}{3}$，然后把此次要求记下来。

输出答案时从后往前记录已经输出的 `b` 的个数，如果达到某个 `a` 的需求就输出一个 `a`。

```cpp
#include <bits/stdc++.h>
#define lint __int128
//#define int long long
#define Il inline
#define Rg register
#define Ri Rg int
#define fi first
#define se second
#define vec vector
#define pb push_back
#define IT ::iterator
#define p_que priority_queue
 
using namespace std;
//typedef long long ll;
typedef double db;
typedef pair<int,int> pii;
typedef unsigned int ui;
const int N=200;
const db eps=1e-9,pi=acos(-1.0);

int n,sc=0,jc[N+5];
stack<int>ans,st;

Il int solve(int x){
	int l=3,r=147;//右端点随便取的，能过就行
	while(l<=r){
		int mid=(l+r)>>1;
		if(jc[mid]<=n)l=mid+1;
		else r=mid-1;
	}
	return l-1;
}

signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	jc[3]=1,jc[4]=4;for(Ri i=5;i<=147;i++)jc[i]=i*(i-1)*(i-2)/6;
	cin>>n;while(n){int s=solve(n);st.push(s);n-=jc[s];}
	while(!st.empty()){
		if(sc==st.top())ans.push('a'),st.pop();
		else ans.push('b'),sc++;
	}
	for(;!ans.empty();ans.pop())cout<<char(ans.top());cout<<" abbb";
	return 0;
}
```

---

## 作者：Purslane (赞：0)

# Solution

事实证明，只要是构造题，就算 `*2200`，我也要做很久。

下面教大家怎么用两种字符通过这个题。

-------

我们让问题简单化，设子序列就是 `aaaaab` 的形态（笑点解析：最后我就选了它），其中 `b` 前面有 $c$ 个 `a`。

假设母串每个 `b` 前面有 $k$ 个 `a`，那么总的子序列个数就是：

$$
\sum \dbinom{k_i}{c}
$$

我们将所有的 $k$ 排序，则最终需要的字符个数是：

$$
\max k +\sum [k_j = k_{j-1}]
$$

随便取 $c=5$，就过了。

感性理解这个东西会是 $O(n^{0.2})$ 级别的，最多只需要 $57$ 个字符。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1000000+10;
int n,k=5,dp[MAXN],C[MAXN];
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	ffor(i,5,50) {
		int mul=1;
		ffor(j,i-4,i) mul*=j;
		mul/=120;
		C[i]=mul;	
	}
	vector<int> vc;
	cin>>n;
	while(n) {
		int v=upper_bound(C+1,C+51+1,n)-C-1;
		while(n>=C[v]) vc.push_back(v),n-=C[v];
	}
	sort(vc.begin(),vc.end());
	int a_cnt=0;
	for(auto id:vc) {
		while(a_cnt<id) cout<<"a",a_cnt++;
		cout<<"b";	
	}
	cout<<" aaaaab";
	return 0;
}
```

UPD：又试了一下，$c=6$ 可以做到 $50$ 个字符。

---

