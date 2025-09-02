# Substrings in a String

## 题目描述

Given a string $ s $ , process $ q $ queries, each having one of the following forms:

- $ 1ic $ — Change the $ i $ -th character in the string to $ c $ .
- $ 2lry $ — Consider the substring of $ s $ starting at position $ l $ and ending at position $ r $ . Output the number of times $ y $ occurs as a substring in it.

## 说明/提示

Consider the first sample case. Initially, the string aba occurs $ 3 $ times in the range $ [1,7] $ . Note that two occurrences may overlap.

After the update, the string becomes ababcbaba and now aba occurs only once in the range $ [1,7] $ .

## 样例 #1

### 输入

```
ababababa
3
2 1 7 aba
1 5 c
2 1 7 aba
```

### 输出

```
3
1
```

## 样例 #2

### 输入

```
abcdcbc
5
2 1 7 bc
1 4 b
2 4 7 bc
1 2 a
2 1 4 aa
```

### 输出

```
2
2
1
```

# 题解

## 作者：老莽莽穿一切 (赞：20)

[更好的阅读体验](https://www.cnblogs.com/LaoMang-no-blog/p/16305374.html)

---

[**你谷 link**](https://www.luogu.com.cn/problem/CF914F)

[**CF link**](https://codeforces.com/problemset/problem/914/F)

3000 分的题，正解似乎是什么分块套后缀自动机之类的，根本不会，但是我们有别的解法。

看到标签里有个 bitmask，于是恍然大悟，字符串题有位运算提示就很明显了，就是直接 `bitset` 乱搞字符串匹配。

当字符集大小可以接受时字符串匹配的一种乱搞做法，给每个字符集开一个 `bitset`，如果一个位置上是这个字符，就给对应的 `bitset` 对应位置标上 $1$，匹配的时候就每个字符所有位置一起匹配，匹配的结果与起来就是答案，如果是区间查询可以利用 `bitset` 右移差分。

注意坑点是右移差分的时候因为询问存在查询区间长度低于字符串长度的，所以要特判。

与正解不同，[代码](https://codeforces.com/contest/914/submission/158268050)实现非常简单。

---

## 作者：唐一文 (赞：20)

~~讲一下这题的不正经做法。~~

以下假设 $n,q,\sum\left|y\right|$ 同阶。

首先是暴力，每次 $O(1)$ 修改，$O(n^2)$ 查询，总时间最坏 $O(n^3)$。

然后优化这个暴力，发现用 kmp 可以优化到每次 $O(n)$ 查询，总时间最坏 $O(n^2)$。

我们想一想为什么这个最坏是 $O(n^2)$：假设 $\left|y\right|=len$，那么最多有 $\dfrac{n}{len}$ 次查询，每次查询 $[1,n]$，时间复杂度为 $O(\dfrac{n^2}{len})$，当 $len=1$ 的时候最坏 $O(n^2)$。

可以发现，当 $len$ 较大的时候，kmp 是可以直接跑过去的，所以可以设一个阈值 $L$，当 $L\leq len$ 的时候直接跑 kmp。

那么当 $len<L$ 时怎么做呢？

统计一个字符串在另一个串里的出现次数，不难想到用哈希~~也可能是我才疏学浅只想得到哈希~~。

记 $hs_{i,j}$ 表示 $[i,i+j-1]$ 的哈希值。

查询操作：

相当于统计 $i\in[l,r-len+1]$ 与询问串哈希值相同的 $hs_{i,len}$ 数量，可以分块，设块大小为 $B$，那么可以做到每次 $O(\dfrac{n}{B})$ 查询。（树状数组不知道行不行，但是我的树状数组过不去）

修改操作：

修改位置 $i$ 时，只需要修改包含位置 $i$ 的长度小于 $L$ 的子串的哈希值，因为最多会有 $L^2$ 个子串被修改，所以每次修改 $O(L^2)$。

对每个块开 $L$ 个桶，第 $j$ 个桶记录块内每个位置 $i$ 的 $hs_{i,j}$ 的出现次数，可以用哈希表实现。

然后是我的悲惨经历：兴致勃勃地写完代码，交上去发现 MLE on test 4 了，调了一下午 $L,B$ 都没用。

最后发现是哈希表中修改后会出现一些数量为 $0$ 的哈希值，需要将它们及时扔出去减少占用的内存。

时间复杂度 $O(\dfrac{n^2}{B}+nL^2+\dfrac{n^2}{L})$，空间复杂度不太会算（

这题感觉空间比较卡，如果 MLE 了试着调一下 $L$ 和 $B$ 的大小。

随便测了下我的代码是 $L=25,B=700/1000$ 和 $L=20,B=320/500$ 可过。

[Code](https://www.luogu.com.cn/paste/w9dq4x2e)

---

## 作者：Rainbow_qwq (赞：14)

- [CF914F Substrings in a String](https://www.luogu.com.cn/problem/CF914F)

---


看见有修改操作就感觉不太可做，肯定要用什么数据结构维护。

考虑对字符串 $s$ 分块，设块长为 $B$ ，每块建一个 SAM ，修改直接暴力 $O(B)$ 重构。

查询时也进行根号分治，设一个阈值 $T(T\le B)$ 。

设查询串 $y$ 长度为 $len$ ，$len>T$ 时最多有 $\frac{100000}{T}$ 个这样的询问，暴力建出 $s[l:r]$ 的 SAM 然后查询。

$len\le T$ 时，此时 $len\le T\le B$，只可能 $y$ 出现在某块内 、 $y$ 跨越两个块。

$y$ 出现在某块内：每个块的 SAM 上查询，边角 2 个块暴力建出 SAM 再查询，$O(\sum len \times \frac{n}{B}) $ 。

$y$ 跨越两个块：在两个块的交界处，向左右各取 $len-1$ 的区间长度建出 SAM，$O(\sum len \times B) $ 。

取 $B=\sqrt n$ 可以得到 $O(n\sqrt n)$ 大常数做法，T 掉了，被 bitset 做法吊打（

卡常：

- 数组不要全部 memset，只 memset 一部分。
- ~~加一堆 pragmas 头文件。~~
- 修改时不要直接 rebuild ，对块打上 tag，查询时要用到这个块再 rebuild 。一开始也不用 build ，直接打 tag。
- 玄学调块长，我代码取了 $B=350$ 。

~~虽然 AC 了，但仍然被 bitset 做法吊打。~~

[Code](https://www.luogu.com.cn/paste/8puy29l6)

---

## 作者：EternalAlexander (赞：12)

讲一下这题的正经做法。  
对整个串分块，令块大小为$k$。对于每个块内的长度为$k$的字符串暴力建后缀自动机或者类似的东西。  
遇到修改操作时，找到对应的块$O(k)$暴力重建数据结构即可。  
考虑查询操作。对于询问串的长度$|y|$，如果$|y|>k$，那么$O(n)$暴力匹配。显然这样的串不会超过$\sum|y|/k$个,总复杂度$O(n\sum|y|/k$)。  
如果$|y|<k$，在每个块内的数据结构中暴力查询。然后考虑跨越两个块的字符串。显然对于每两个块的分界线，需要考虑的字符串长度不超过$2|y|$。直接对所有需要考虑的字符串暴力查询即可。总复杂度$O(\sum |y|n/k+\sum |y|k)$。
因为$\sum |y|$和$n$同级，取$k=\sqrt n$可以得到一个$n\sqrt n$的做法。   

但是6s当然可以bitset踩标算。  

---

## 作者：spider_oyster (赞：9)

线下模拟赛居然考到了，发现这题还是阉割版。

直接开科技用 bitset。

先用 bitset 存每一个字母出现的位置。

考虑如何计算一个字符串 $t$ 在字符串 $s$ 的 $l-r$ 中出现的次数：

先开一个全为 1 的 bitset：ans；

对于 $t$ 的每一个字符，我们都用 ans& 上这个字符的 bitset 右移 i 位（i 为这个字符在 $t$ 中的下标）。

这样，如果 ans 中有一位为 1，则说明 $t$ 出现了一次（在经历重重与运算后，这个位置还为 1，说明 $t$ 里的字符都按顺序出现了）。我们统计在合法范围内 ans 里 1 的个数即可。

此外，如果 $r-l+1<|t|$，需要特判一下，不然会越界。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=1e5+5;
int n,m;
string s,t;
bitset<N> a[26],ans;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>s>>m;
	for(int i=0;i<s.size();i++) a[s[i]-'a'].flip(i);
	while(m--)
	{
		int op,l,r;char c;
		cin>>op>>l;--l;
		if(op==1) cin>>c,a[s[l]-'a'].flip(l),s[l]=c,a[s[l]-'a'].flip(l);
		else
		{
			cin>>r>>t;--r;
			int n=t.size();
			if(n>r-l+1) {cout<<"0\n";continue;}
			ans.set();
			for(int i=0;i<t.size();i++) ans&=a[t[i]-'a']>>i;
			cout<<(ans>>l).count()-(ans>>(r-n+2)).count()<<'\n';
		}
	}
}
```


---

## 作者：_WAlkingDead (赞：4)

诈骗题。

如果你想用一些字符串科技，那你就成功地被骗了。

bitset

我们定义 ```bitset<N> res,b ``` 其中 res 为答案， b 为初始字符串。


我们用 res 存下所有可能的左端点，当处理第 i 个字符时，``` res&=(b[c[i]]>>(i-1)) ``` 即可，其中 c 为待匹配字符串。

最终的 res 就是匹配的所有左端点。

然后我们求出合法区间内 res 中 1 的个数即可。

修改就直接 $O(1)$ 做就好了。

时间复杂度 $O(\frac{n(n+1)}{w}+y)$

## code

```cpp
#include<iostream>
#include<cstdio>
#include<bitset>
#include<cstring>
using namespace std;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
const int N=1e5+5;
bitset<N> b[256],res;
char s[N],c[N];
int q,len;
int main(){
	scanf("%s",s+1);
	for(int i=1;i<=strlen(s+1);i++) b[s[i]][i]=1;
	q=read();
	while(q--){
		int opt=read();
		if(opt==1){
			int i=read();
			scanf("%s",c+1);
			b[s[i]][i]=0;
			b[c[1]][i]=1;
			s[i]=c[1];
		}
		if(opt==2){
			int l=read(),r=read();
			scanf("%s",c+1);
			res.set();
			for(int i=1;i<=strlen(c+1);i++) res&=(b[c[i]]>>(i-1));
			int lans=(res>>l).count(),rans=(res>>(r-strlen(c+1)+2)).count();
			printf("%d\n",max(0,lans-rans));
		}
	}
	return 0;
}
```


---

## 作者：Illusory_dimes (赞：4)

复盘 fsy 讲的题，写篇题解来~~报复社会~~

## Description

维护一个支持单点修改的，能查询区间 $[l,\ r]$ 内指定文本串 $t$ 出现次数的模式串 $s$ 。

$|s| \leq 10 ^ 5,\ \ q\leq 10 ^ 5,\ \ \sum |t| \leq 10 ^ 5$

## Solution

这玩意似乎并不好维护，询问很 SAM ，但似乎单点修改又需要重构，所以看起来只维护全局 SAM 并不能很好地解决这个问题。

再看数据，发现这很 CF 根号，我们可以考虑在重构上下点狠心，但是我们又不能直接重构，这样是一个 $O(q \cdot n)$ 的恶心算法，考虑怎么把时间降下来。

发现有个 $\sum$ 的条件，所以说我们应该用这玩意限制一下，比如说根号分治。

令阈值为 $B$。

1. 当 $|t| > B$ 时，我们直接重构整个 SAM，根据条件，这种字符串数量不超过 $\frac{\sum}{B}$ 个，总时间是 $O(n \cdot \frac{\sum |t|}{B})$。

2. 当 $|t| \leq B$ 时，我们考虑分块，对于询问区间遍及的每个块内进行重构，总时间是 $O(\sum |t| \cdot \frac{n}{B})$。

这样就完了吗？？没有！！

- 因为 $|t| \leq B$，所以有可能答案在两个且至多两个区间内产生，说还要对于每相邻两个块间的答案再次统计（长度一定要是左区间 $|t| - 1$ + 右区间 $|t| - 1$ ），总时间是 $O(\sum |t| \cdot B)$。

总的来看将 $B$ 定为 $\sqrt{n}$ 就能得到一个正常的根号做法。

然而被 bitset 爆踩。。

## Code

```cpp
/*

*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10, B = 322;
int n, m, q, k, blo[N], l[N], r[N], lzy[N];
char s[N], p[N];
inline int read() {
	char ch = getchar();
	int s = 0, w = 1;
	while (!isdigit(ch)) {if (ch == '-') w = -1; ch = getchar();}
	while (isdigit(ch)) {s = (s << 3) + (s << 1) + (ch ^ 48); ch = getchar();}
	return s * w;
}
template <int M>
struct SAM {
	int n, cnt, las, len[M], link[M], ch[M][26];
	int tong[M], rk[M], mx[M], siz[M];
	inline void init() {
		cnt = las = 1;
		memset(ch[1], 0, sizeof(ch[1]));
	}
	inline void SAM_stru(int c) {
		int cur = ++cnt, p = las;
		memset(ch[cur], 0, sizeof(ch[cur]));
		las = cur;
		len[cur] = len[p] + 1; siz[cur] = 1;
		while (p && !ch[p][c]) ch[p][c] = cur, p = link[p];
		if (!p) {link[cur] = 1; return ;}
		int q = ch[p][c];
		if (len[p] + 1 == len[q]) {link[cur] = q; return ;}
		int clo = ++cnt; siz[clo] = 0;
		link[clo] = link[q]; len[clo] = len[p] + 1;
		link[q] = link[cur] = clo;
		memcpy(ch[clo], ch[q], sizeof(ch[clo]));
		while (p && ch[p][c] == q) ch[p][c] = clo, p = link[p];
	}
	inline void Tong_sort() {
		memset(tong, 0, sizeof(int) * (cnt + 1));
		for (int i = 1; i <= cnt; ++i) ++tong[len[i]];
		for (int i = 1; i <= cnt; ++i) tong[i] += tong[i - 1];
		for (int i = 1; i <= cnt; ++i) rk[tong[len[i]]--] = i;
		for (int i = cnt; i > 1; --i) siz[link[rk[i]]] += siz[rk[i]];
	}
	inline void rebuild(int l, int r) {
		init();
		for (int i = l; i <= r; ++i) SAM_stru(s[i] - 'a');
		Tong_sort();
	}
	inline int calc(char *t, int m) {
		int p = 1;
		for (int i = 1; i <= m; ++i) {
			p = ch[p][t[i] - 'a'];
			if (!p) return 0;
		}
		return siz[p];
	}
};
SAM<N << 1> t;
SAM<B << 2> b[B << 1];
inline int solve() {
	int lt = read(), rt = read(), bl = blo[lt], br = blo[rt], res = 0;
	scanf("%s", p + 1); m = strlen(p + 1);
	if (m > B || bl == br) return t.rebuild(lt, rt), t.calc(p, m);
	t.rebuild(lt, r[bl]); res += t.calc(p, m); 
	t.rebuild(l[br], rt); res += t.calc(p, m);
	for (int i = bl + 1; i < br; ++i) {
		if (lzy[i]) lzy[i] = 0, b[i].rebuild(l[i], r[i]);
		res += b[i].calc(p, m);
	}
	for (int i = bl + 1; i <= br; ++i) {
		t.rebuild(max(lt, r[i - 1] - m + 2), min(rt, l[i] + m - 2));
		res += t.calc(p, m); 
	}
	return res;
}
int main() {
	scanf("%s", s + 1); n = strlen(s + 1);
	k = (n - 1) / B + 1;
	for (int i = 1; i <= k; ++i) {
		l[i] = r[i - 1] + 1; r[i] = r[i - 1] + B;
		for (int j = l[i]; j <= r[i]; ++j) blo[j] = i;
		lzy[i] = 1;
	}
	r[k] = n;
	q = read();
	for (int i = 1, op, x; i <= q; ++i) {
		op = read();
		if (op == 1) {
			x = read(); char c = getchar();
			s[x] = c; lzy[blo[x]] = 1;
		}
		else printf("%d\n", solve());
	}
	return 0;
}
```

---

## 作者：fjy666 (赞：2)

给定一个字符串，支持单点修改和子串询问出现次数。

****

把整个串按照块长 $b$ 分块，然后维护这么些东西：  
- 单个块的 SAM
- 相邻两个块的 SAM

先不管散块，考虑整块查询（设左右两块为 $bl, br$）。

显然出现次数为相邻两块 SAM 种出现次数之和与单块 SAM 出现次数之和的差。（容斥）

然后考虑散块。直接 KMP 即可。

但是这样会出现一个问题，当查询的串的长度 $\ge b$ 会炸。
 
 
但是 $\sum|s_i|\le 10^5$，所以我们只需要暴力搞就行了。 

***
[submission](https://codeforces.com/problemset/submission/914/213449632)

坑点：当 $br - bl\le 1$ 时特判。  
统计：这个题我提交了 $43$ 发。另外这题是我在旁边拿枪逼 EDqwq 做的，效果很好，有无读者愿意试试。

---

## 作者：CodingShark (赞：2)

~~大蒟蒻过的第一道黑题，写篇题解纪念一下。~~

作为一个连后缀自动机都不会的蒟，只能用 bitset 进行玄学了。

可以先对每一个字符开一个长度为 $|s|$ 的 bitset（比如叫 `idx`），把这个字符出现的位置都标为 1。

对于样例 `ababababa`，我们可以的愉快地到两个 bitset：

`a:101010101`

`b:010101010`

于是我们

### update

这个操作比较简单，只需要修改 bitset 里对应的值即可，不过多赘述。

### query

对于每次询问，可以再处理出一个 bitset（比如叫 `ans`），

如果 `ans[i]` 的值为 1，那么代表 $s[i, i + |t| - 1]$ 这段与 $t$ 匹配。 

显而易见，如果某一个 `ans[i]` 想变成 1，那么 $s[i]$ 这项的值必然等于 $t[1]$。

在只考虑 $t[1]$ 的情况下，`ans` 就恰好是 `idx[t[0]]`。

接着考虑 $t[2]$，可以发现，只要让 $t[1]$ 后面一项为 $t[2]$ ，反映到 bitset 上就是 `ans &= idx[t[2]] >> 1` 。

以此类推，对于每个 $t[i]$，让 `ans &= idx[t[i]] >> (i - 1)` 即可。

最后查询一个区间 $[l, r]$，只需要对 `ans` 进行一个差分计算即可。

时间复杂度 $O(\frac{nq}{w})$，最慢的点 2.20s。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
char s[100005], t[100005];
bitset<100005> idx[26], ans;

int main()
{
    scanf("%s", s + 1);
    int len = strlen(s + 1);
    for (int i = 1; i <= len; i++)
        idx[s[i] - 'a'][i] = 1; // 预处理idx
    int q, opt, l, r;
    scanf("%d", &q);
    while (q--)
    {
        scanf("%d", &opt);
        if (opt & 1)
        {
            scanf("%d %s", &l, t);
            idx[s[l] - 'a'][l] = 0;
            idx[t[0] - 'a'][l] = 1;
            s[l] = t[0]; // 别忘了在s里更新
        }
        else
        {
            scanf("%d %d %s", &l, &r, t + 1);
            len = strlen(t + 1), ans.set();
            for (int i = 1; i <= len; i++)
                ans &= (idx[t[i] - 'a'] >> i - 1);
            int lans = (ans >> l).count(), rans = (ans >> r - len + 2).count(); // 做差分
            printf("%d\n", max(lans - rans, 0)); // 记得与0取max
        }
    }
    return 0;
}
```

---

## 作者：lory1608 (赞：2)

本题第一反应是字符串算法，但是是动态的匹配就很难办。

看到时间是$6s$，想到可以用暴力的$bitset$来维护。

匹配时可以用$bitset$暴力把26个字符的可行性都检测一遍。

```cpp
ans.set();///多的差分减掉了 
int len=strlen(now+1);
for(int i=1;i<=len;++i)
{
	ans&=(se[now[i]-'a']>>(i-1));///从几开始的ok 
}///suffix
int lans=(ans>>x).count();///[x,n]
int rans=(ans>>(y-len+2)).count();///[y-len+2,n]
printf("%d\n",(lans-rans<0)?0:lans-rans);

```
这一段就是将所有的可行的开头都存到$bitset$中。

由于$bitset$右移溢出很不好写，所以用**后缀差分**，同样也可以解决此题。

```cpp
ans>>x;///提取[x,n]开头的答案
ans>>(y-len+2);///提取[y-len+2,n]开头的答案
```
**注意:当结尾为$(r+1)$是不合法，此时开头是$(y-len+2)$**。

数据中有$l>r$的情况所以还要特判一下。

总复杂度为$\Theta(\frac{qn}{\omega})$可以通过此题。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<queue>
#include<bitset>
using namespace std;
const int maxn=1e5+5;
int n,q,x,y,opt;
bitset<maxn>se[26],ans;///a-z
char s[maxn],now[maxn],v[2];
int main()
{
	scanf("%s",s+1);
	n=strlen(s+1);
	for(int i=1;i<=n;++i)
	{
		se[s[i]-'a'].set(i,1);
	}
	scanf("%d",&q);
	for(int i=1;i<=q;++i)
	{
		scanf("%d",&opt);
		if(opt==1)
		{
			scanf("%d%s",&x,v);
			se[s[x]-'a'].set(x,0);
			se[v[0]-'a'].set(x,1);
			s[x]=v[0];
		}
		else
		{
			scanf("%d%d%s",&x,&y,now+1);
			ans.set();///多的差分减掉了 
			int len=strlen(now+1);
			for(int i=1;i<=len;++i)
			{
				ans&=(se[now[i]-'a']>>(i-1));///从几开始的ok 
			}///suffix
			int lans=(ans>>x).count();///[x,n]
			int rans=(ans>>(y-len+2)).count();///[y-len+2,n]
			printf("%d\n",(lans-rans<0)?0:lans-rans);
		}
	}
	return 0;
}

```

---

## 作者：ademik (赞：1)

#### 分析 :

神秘 bitset 科技 。

![](https://cdn.luogu.com.cn/upload/image_hosting/f1ndfcmy.png)

对于修改操作，我们只需要修改对应 bitset 的 01 值即可。


#### Code ：

```cpp
# include <bits/stdc++.h>
# define TIME 1e3 * clock() / CLOCKS_PER_SEC
using namespace std;
typedef long long i64;
const int N = 1e5 + 50;
int n;
bitset < N > ans;
bitset < N > ch[26];
char s[N], t[N]; 
int main()
{
    ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >>(s + 1); n = strlen(s + 1); 
    for(int i = 1; i <= n; i ++) ch[s[i] - 'a'].set(i);
    int q; cin >>q;
    while(q --) {
        int op; cin >>op;
        if(op == 1) {
            int x; char y;
            cin >>x >>y;
            ch[s[x] - 'a'].reset(x);
            s[x] = y;
            ch[s[x] - 'a'].set(x);
        } else {
            int x, y; string t;
            cin >>x >>y >>t;
            if(t.size() > y - x + 1) {
                cout <<"0" <<endl;
                continue;
            }
            ans.set();
            for(int i = 0; i < t.size(); i ++) ans &= (ch[t[i] - 'a'] >> i);
            cout <<((ans >> x).count() - (ans >> (y - t.size() + 2)).count()) <<endl;
        }
    }
    return 0;
} 
```

---

## 作者：FutaRimeWoawaSete (赞：1)

**CF914F sol。**

考虑一个好想点的做法：由于存在单点修改，若使用字符串型数据结构需要推平。

所以优先考虑构造是线性时间复杂度的结构——SAM。

先进行一次根号分治，对于 $|y| > \sqrt {\sum|y|}$ 的字符串暴力进行 kmp，时间复杂度是 $O(\sqrt {\sum|y|} |s|)$ 的。

对于 $|y| <= \sqrt {\sum|y|}$ 的我们直接按此为块长分块，显然串至多跨越两个块，维护相邻块的 SAM 即可维护整块答案，这部分时间复杂度为 $O(\sqrt {|s|} (\sum |y|))$ 的。

对于散块我们也暴力连利两端的整块进行一次 kmp，这部分时间复杂度也是 $O(\sqrt {|s|} (\sum |y|))$ 的。注意一些细节即可通过此题。

考虑不那么好想，至少我没想到的是直接开 $26$ 个维护字符集位置的 bitset，即 $bs_{c,i}$ 表示第 $i$ 个位置是否有字符 $c$ 出现。

修改是简单的。

对于查询，我们考虑维护每个开头是否是可行的，这个可以用上述维护的 bitset 数组加速判断。

接着筛选合法区间内的合法左端点即可，时间复杂度 $O(\frac{\sum|y| \times |s|}{w})$。



---

## 作者：Ray662 (赞：0)

[洛谷 传送门](https://www.luogu.com.cn/problem/CF914F) | [CodeForces 传送门](https://codeforces.com/problemset/problem/914/F)

[更好的阅读体验](https://www.luogu.com.cn/blog/sunrize/solution-cf914f)

题目大意：

- 有两种操作：

1. 修改一个字符串；

2. 求一个字符串 $y$ 在 $[l, r]$ 区间内的出现次数。

- $|s|, q, \sum |y| \le 10^5$。

---

### 分析

考虑用 bitset 来维护。

bitset 用法详见[这里](https://www.cnblogs.com/fswly/p/16164109.html)。

- 初始化

首先把每个 $s_i$ 存入 bitset 中。

```cpp
_for (i, 1, strlen(s + 1))  bs[s[i] - 'a'].set(i, 1);  // 把第 i 位设为 1
```

- 操作 1

修改操作，把原来的 $s_i$ 设为 $0$，同时把新的存入 bitset（**最后记得把 $s_i$ 更新**）。

```cpp
bs[s[l] - 'a'].set(l, 0), bs[c[0] - 'a'].set(l, 1), s[l] = c[0]
```

- 操作 2

把能有的前缀都存进 $t$ 中，然后求值即可（**注意 $t$ 的清空**）。

```cpp
t.set();
_for (i, 1, strlen(y + 1))  t &= bs[y[i] - 'a'] >> (i - 1);
cout << max(0, (int)(t >> l).count() - (int)(t >> (r - strlen(y + 1) + 2)).count()) << endl;
```

---

完整代码：

```cpp
#include <bits/stdc++.h>
#define ll long long
#define _for(i, a, b)  for (int i = (a); i <= (b); i ++ )
#define _all(i, a, b)  for (int i = (a); i >= (b); i -- )
using namespace std;
const int N = 1e5 + 5;
int q;
char s[N], y[N], c[1];
bitset<N> bs[30], t;
int main() {
	scanf("%s", s + 1);
	_for (i, 1, strlen(s + 1))  bs[s[i] - 'a'].set(i, 1);
	scanf("%d", & q);
	while (q -- ) {
		int opt, l, r;
		scanf("%d", & opt);
		if (opt == 1)  scanf("%d%s", & l, c), bs[s[l] - 'a'].set(l, 0), bs[c[0] - 'a'].set(l, 1), s[l] = c[0];
		else {
			scanf("%d%d%s", & l, & r, y + 1), t.set();
			_for (i, 1, strlen(y + 1))  t &= bs[y[i] - 'a'] >> (i - 1);
			cout << max(0, (int)(t >> l).count() - (int)(t >> (r - strlen(y + 1) + 2)).count()) << endl;
		}
	}
	return 0;
}
```

---

