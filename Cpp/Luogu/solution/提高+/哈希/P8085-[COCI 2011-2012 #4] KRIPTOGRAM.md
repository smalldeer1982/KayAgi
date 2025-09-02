# [COCI 2011/2012 #4] KRIPTOGRAM

## 题目描述

现有一段明文和一部分密文。明文和密文都由英文单词组成，且密文中的一个单词必然对应着明文中的一个单词。

求给出的密文在明文中可能出现的最早位置。

## 说明/提示

**【数据规模与约定】**

- 对于 $100\%$ 的数据，明文和密文所对应字符串的长度不超过 $10^6$，输入的单词均由小写字母组成。

**【提示与说明】**

**题目译自 [COCI 2011-2012](https://hsin.hr/coci/archive/2011_2012/) [CONTEST #4](https://hsin.hr/coci/archive/2011_2012/contest4_tasks.pdf) _Task 6 KRIPTOGRAM_。**

**本题分值按 COCI 原题设置，满分 $140$。**

## 样例 #1

### 输入

```
a a a b c d a b c $
x y $```

### 输出

```
3```

## 样例 #2

### 输入

```
xyz abc abc xyz $
abc abc $```

### 输出

```
2```

## 样例 #3

### 输入

```
a b c x c z z a b c $
prvi dr prvi tr tr x $```

### 输出

```
3```

# 题解

## 作者：离散小波变换° (赞：33)

## 题解

考虑使用哈希。

我们记明文中第 $i$ 个单词到上一个单词的距离是 $a_i$，密文中第 $i$ 个单词到上一个单词的距离是 $b_i$。特别地，如果前面没有出现过相同单词，则将距离记作 $-1$。例如，对于样例 $3$，明文和密文分别可以转化为如下形式：

- 明文转换前：$[\mathtt{a, b, c, x, c, z, z, a, b, c}]$；
- 明文转换后：$[-1,-1,\underline{-1,-1,2,-1,1,7},7,7]$；
- 密文转换前：$[\mathtt{prvi, dr, prvi, tr, tr, x}]$；
- 密文转换后：$[-1,-1,2,-1,1,-1]$。

如果明文当中某个子串等于密文，那么这个子串生成的序列应该是和密文序列相同的。不过我们不能直接对明文生成的序列进行区间哈希。因为明文当中某些单词的上一个单词的位置在区间之外，转换后有值，而密文里对应位置是 $-1$。

解决起来其实非常简单：只需要在滑动窗口的时候维护这个子串的哈希值即可。当窗口滑过某个单词，就把这个单词右侧第一次出现的与它相同的单词对应的元素变成 $-1$。仍然拿样例 $3$ 举例，

- 第一个子串：$[\underline{-1,-1,-1,-1,2,-1},1,7,7,7]$；
- 第二个子串：$[-1,\underline{-1,-1,-1,2,-1,1},\textcolor{red}{-1},7,7]$，第一个单词 $\verb!a!$ 已经移出窗口，于是将它右侧第一个 $\verb!a!$ 的位置换成 $-1$；
- 第三个子串：$[-1,-1,\underline{-1,-1,2,-1,1,-1},\textcolor{red}{-1},7]$；第二个单词 $\verb!b!$ 已经移出窗口，于是将它右侧第一个 $\verb!b!$ 的位置换成 $-1$；
- 第四个子串：$[-1,-1,-1,\underline{-1,\textcolor{red}{-1},-1,1,-1,-1},7]$；第三个单词 $\verb!b!$ 已经移出窗口，于是将它右侧第一个 $\verb!c!$ 的位置换成 $-1$；
- 第五个子串：$[-1,-1,-1,-1,\underline{-1,-1,1,-1,-1,7}]$。

维护的时候，如果需要变成 $-1$ 的那个元素的位置在当前子串所处的区间 $[l,r]$ 内，就将子串的哈希值 $h$ 减去原来这个元素的贡献值，再加上变成 $-1$ 后的贡献值。如果在 $[l,r]$ 外就不用管。别的维护和一般的区间哈希相似。

## 参考代码

```cpp
#include<bits/stdc++.h>
#define up(l, r, i) for(int i = l, END##i = r;i <= END##i;++ i)
#define dn(r, l, i) for(int i = r, END##i = l;i >= END##i;-- i)
using namespace std;
typedef long long i64;
const int INF = 2147483647;
const int MAXN= 1e6 + 3;
int L1[MAXN], R1[MAXN];
int L2[MAXN], R2[MAXN];
int A[MAXN], B[MAXN], n, m;
typedef unsigned int       u32;
typedef unsigned long long u64;
const u64 BAS = 13331;
u64 H[MAXN], P[MAXN];
map <string, int> M;
int main(){
    string t;
    while(cin >> t && t != "$"){
        R1[M[t]] = ++ n, L1[n] = M[t], M[t] = n;
    }
    M.clear();
    while(cin >> t && t != "$"){
        R2[M[t]] = ++ m, L2[m] = M[t], M[t] = m;
    }
    for(int i = 1;i <= n;++ i) if(!R1[i]) R1[i] = INF;
    for(int i = 1;i <= m;++ i) if(!R2[i]) R2[i] = INF;
    for(int i = 1;i <= n;++ i) A[i] = L1[i] ? i - L1[i] : -1;
    for(int i = 1;i <= m;++ i) B[i] = L2[i] ? i - L2[i] : -1;
    u64 h0 = 0, h = 0; P[0] = 1;
    for(int i = 1;i <= m;++ i) P[i] = P[i - 1] * BAS;
    for(int i = 1;i <= m;++ i)
        h0 = h0 * BAS + B[i], h  = h  * BAS + A[i];
    if(h == h0) printf("%d\n", 1), exit(0);
    for(int i = m + 1;i <= n;++ i){
        h = h * BAS + A[i], h = h - A[i - m] * P[m];
        if(R1[i - m] <= i){
            h = h - A[R1[i - m]] * P[i - R1[i - m]];
            A[R1[i - m]] = -1;
            h = h + A[R1[i - m]] * P[i - R1[i - m]];
        } else if(R1[i - m] <= n) A[R1[i - m]] = -1;
        if(h == h0) printf("%d\n", i - m + 1), exit(0);
    }
    return 0;
}
```

---

## 作者：orzws (赞：16)

看了题解的代码全都可以被讨论区的这组数据hack掉
```cpp
输入：
a a a b c d d e f $
x x y z $
```

```cpp
输出
2
```

被阴了好久，于是来写一篇题解(


------------

看到字符匹配可以想到kmp，但是本题中要求的与具体的单词无关，所以我们可以把原单词直接用map离散化，然后记录一下上一个出现的数字出现的位置。然后我们就会发现有两个问题要解决：

* 如何快速匹配（更改kmp数组的含义来满足本题的失配跳跃）
* 如何判断是否可以匹配

对于第一个问题，可以想到将原本的 $[1,L]$ 与 $[x-L+1,x]$ 字符相同的意义改为 $[1,L]$ 与 $[x-L+1,x]$ 在本题解密的意义下相同

对于第二个问题，我们记 $ls1[x]$ 为文本串为x在与上一个出现的距离， $ls2[x]$ 为模式串，若第一次出现则距离为inf，fl为单词离散化后的数组，我们可以分讨一下,

* 如果 $ls2[j]$ 为 $inf$，则 $ls1[i]$ 必须大于等于j才能满足条件
* 如果 $ls2[j]$ 不为 $inf$，则 $fl[i-ls2[j]]$ 要等于 $fl[i]$ 才能满足条件

然后我们按照将判断函数套用上方的分讨即可


------------

其他题解中会被hack的主要原因是因为在求kmp数组时直接用 $ls2$ 去匹配，但是这样其实是错的，我们在求kmp数组时要考虑清楚他的定义与匹配方式（上方的分讨），直接判断是否相等显然就没有考虑清楚匹配方式


------------

### 代码
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<map>

using namespace std;

#define ll long long

const int N = 1e6+7;
const int inf = 1e9;
string s;
int t1,t2,tp1,tp2,ls1[N],ls2[N],l[N],fl1[N],fl2[N],kmp[N];
map <string,int> mp;

void solve(int las[], int fl[], int &t) { 
	mp.clear(); for(int i = 1; i <= 1000000; i ++ ) l[i] = -inf;
	int tp = 0;
	for(int i = 1; cin >> s && s[0] != '$'; i ++ ) {
		t++;
		if(!mp[s]) mp[s] = ++tp; 
		int x = mp[s]; fl[i] = x;
		if(l[x] == -inf) las[i] = inf;
		else las[i] = i-l[x]; l[x] = i;
	}
}

bool check(int i, int j) {
	if(ls2[j+1] == inf && ls1[i] < j+1) return false;
	if(ls2[j+1] != inf && fl1[i] != fl1[i-ls2[j+1]]) return false;
	return true;
}

bool pd(int i, int j) {
	if(ls2[j+1] == inf && ls2[i] < j+1) return false;
	if(ls2[j+1] != inf && fl2[i] != fl2[i-ls2[j+1]]) return false;
	return true;
}

int main() {
	solve(ls1, fl1, t1);
	solve(ls2, fl2, t2);
	int j = 0;
	for(int i = 2; i <= t2; i ++ ) {
		while(!pd(i, j) && j) j = kmp[j];
		if(pd(i, j)) j++;
		kmp[i] = j;
	}
	j = 0;
	for(int i = 1; i <= t1; i ++ ) {
		while(j && !check(i, j)) j = kmp[j];
		if(check(i, j)) j++;
		if(j == t2) { cout << i-j+1; return 0; }
	}
}

```

---

## 作者：Autumn_Rain (赞：6)

方法一：

- 把字符串转成数字编号（可以用 Map 记录窗口内编号，出现过就用一样的编号，否则最大值加一）。
- 发现题目让我们从中找出形状和匹配串一样的最早一段的开头在哪里。
- 形状一样就是两两差值相同，差分数组后 KMP 即可。

方法二：

- 维护一个数组 $a$，记录此单词往前数几个就能遇到和它相同的单词，前面没有赋值为 $-1$。
- 维护一个滑动的窗口，长度同待匹配串，不断移动窗口并维护 $a$ 数组。
- 用区间 Hash 判断是否相同即可。

双倍经验：[CF471D](https://www.luogu.com.cn/problem/CF471D)。

---

## 作者：Yharimium (赞：5)

题目链接：[P8085](https://www.luogu.com.cn/problem/P8085)

## 题目理解

这里举若干例子解释「匹配」的概念：

- `a b c` 和 `d e f` 是匹配的
- `a a b`，`c c d` 和 `int int float` 是两两匹配的
- `a a b` 和 `a b c` 是不匹配的

「明文 $A$」和「密文 $B$」都由若干单词组成。问 $B$ 可以在 $A$ 中匹配的最早位置。

## 符号说明

-  $A_i$：段落 $A$ 的第 $i$ 个单词，$i$ 从 $1$ 开始计；
- $[\text{state}]$：命题 $\text{state}$ 的真值（成立为 $\text{true}$，不成立为 $\text{false}$）。

## 观察 0

单词间的关系只有「相等」和「不等」。

## 观察 1

若 $X$ 和 $Y$ 匹配，则 $X$ 中「任两个单词间的关系」和 $Y$ 中的相同。

$$\forall i,j,\quad [X_i=X_j]=[Y_i=Y_j]$$

## 观察 2

记 $\text{pre}X[i]$：$i$ 之前最近的「和 $X_i$ 相等的单词」的下标，没有则为 $0$。

若 $X$ 和 $Y$ 匹配，则

$$\forall i,\quad \text{pre}X[i]=\text{pre}Y[i]$$

## 观察 3

考虑最朴素的做法：将 $A$ 和 $B$ 的左端对齐。如不能匹配，就将 $B$ 右移一位，直到匹配成功。

假定当前 $A,B$ 的相对位置如下，此时要匹配 $A_i$ 和 $B_j$：

![](https://cdn.luogu.com.cn/upload/image_hosting/cm7a45zp.png)

容易观察出 $A_i$ 和 $B_j$ 匹配成功的条件：

1. 「$i$ 到 $\text{pre}A[i]$ 的距离」和「$j$ 到 $\text{pre}B[j]$ 的距离」相等；
2. $\text{pre}B[j]=0$ 且 $\text{pre}A[i]$ 在红色区域以外。

两个条件是「逻辑或」的关系，即

```
i - preA[i] == j - preB[j] || ! preB[j] && preA[i] <= i - j
```

## 解法

在传统的 `KMP` 算法中，我们直接比较字符之间是否相等。

针对此题的情况，只需要把 `A[i] == B[j]` 换成观察 3 中的布尔式即可。

## 代码

``` cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 1;

string A[N], B[N];
int lenA, lenB;
int sp_len[N], preA[N], preB[N];

void getPre(string str[], int pre[], int length) {
	unordered_map<string, int> last_pos;

	for (int i = 1; i <= length; i ++) {
		pre[i] = last_pos[str[i]];
		last_pos[str[i]] = i;
	}
}

void getSpLen() {
	int i = 2, j = 1;

	while (i <= lenB) {
		if (i - preB[i] == j - preB[j] || ! preB[j] && preB[i] <= i - j)
			sp_len[i ++] = j ++;
		else if (j > 1)
			j = sp_len[j - 1] + 1;
		else
			i ++;
	}
}

int kmp() {
	int i = 1, j = 1;
	
	while (i <= lenA) {
		if (i - preA[i] == j - preB[j] || ! preB[j] && preA[i] <= i - j)
			i ++, j ++;
		else if (j > 1)
			j = sp_len[j - 1] + 1;
		else
			i ++;

		if (j > lenB)
			return i - lenB;
	}
	
	return -1;
}

int main() {

	string x;

	while (cin >> x, x != "$")
		A[++ lenA] = x;

	while (cin >> x, x != "$")
		B[++ lenB] = x;

	getPre(A, preA, lenA);
	getPre(B, preB, lenB);

	getSpLen();

	cout << kmp() << endl;

	return 0;
}
```

---

## 作者：jiangxinyang2012 (赞：3)

读完题马上想到 kmp，但需要有一些变化。

容易发现两段单词可以匹配当且仅当它们出现的相对顺序相同，如 ```a a b a b c``` 和 ```x x y x y z```，因此可以想到将每个单词用它本次出现的位置与上次出现位置的差来记录它，若第一次出现则记为 inf，如 ```a a b a b c``` 可以改写成 ```inf 1 inf 2 2 inf```。

但是此时如果直接跑普通 kmp 会出现一个问题，如果文本串中这段单词中有一个在整段前出现过，而模式串中对应的单词第一次出现，就会判为不匹配，但有可能是匹配的，例如 ```c (a a b a b c) d``` 和 ```x x y x y z```，可以发现括号中的部分和模式串是匹配的。因此需要在 kmp 时判一下这种匹配的情况，即如果模式串中该单词第一次出现，且文本串中对应单词上次出现的位置在整段前，则也能匹配。

---

## 作者：2020luke (赞：3)

# [P8085 [COCI2011-2012#4] KRIPTOGRAM](https://www.luogu.com.cn/problem/solution/P8085) 题解

## 思路解析

这道题目的主要难点在于如何判断明文中形如 $\texttt{a b c b}$ 的子串可以和密文 $\texttt{b c a c}$ 匹配，因为如果单纯匹配字符的话将会无法匹配，所以我们需要找到一种新的储存一组明文和密文的方法。于是我们考虑存下上一个与当前字符串相同的字符串与当前字符串的距离，如果当前字符串在之前从来没出现过，就存下 $0$。这样下来我们就能正确的匹配明文和密文了。

接下来就要判断密文所对应的匹配数组是否在明文当中出现过，考虑使用滑动窗口做法。但由于删除子字符串会导致新的明文的匹配数组发生改变，所以我们需要同时存下来下一个与当前字符串相同的字符串的位置。原因是如果删掉一个明文的子字符串就会导致下一个与当前字符串相同的字符串的匹配数组的值变为 $0$。

最后我们就需要把已经求出来的两个匹配数组进行判断比较，但是如果对于每一个明文的子字符串都从头到尾比较一次的话时间复杂度就会达到 $O((10^6)^2)$，显然会 $\text{TLE}$，于是就要使用字符串哈希进行优化，如果没学过字符串哈希的可以去看这道题自学一下 [P3370 【模板】字符串哈希](https://www.luogu.com.cn/problem/P3370)。删除滑动窗口头部的元素相当于将哈希值减去元素的值 $\times$ 它对应数位的权值，将滑动窗口右移则相当于将哈希值 $\times BASE$，添加尾部的新元素则是将哈希值直接加上元素的值，而对于元素的修改就是减去原来的，然后加上修改后的值。最后修改完后就直接比较明文的哈希值和密文的哈希值即可。



## code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
const int N = 1e6 + 10;
const ull P = 13331;
string a[N], b[N];
ull p[N], l1[N], l2[N], t1[N];
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	string s1, s2;
	int n1 = 1, n2 = 1;
	cin >> s1;
	for(; s1 != "$"; n1++) {
		a[n1] = (s1);
		cin >> s1;
	}
	cin >> s2;
	for(; s2 != "$"; n2++) {
		b[n2] = (s2);
		cin >> s2;
	}
	n1--; n2--;
	p[0] = 1;
	for(int i = 1; i <= n1; i++) {
		p[i] = p[i - 1] * P;
	}
	map<string, int> mp1, mp2;
	ull h1 = 0, h2 = 0;
	for(int i = 1; i <= n2; i++) {
		if(mp1[a[i]] != 0) {
			l1[i] = i - mp1[a[i]];
			t1[mp1[a[i]]] = i;
		}
		else l1[i] = 0;
		mp1[a[i]] = i;
		h1 = h1 * P + l1[i];

		if(mp2[b[i]] != 0) {
			l2[i] = i - mp2[b[i]];
		}
		else l2[i] = 0;
		mp2[b[i]] = i;
		h2 = h2 * P + l2[i];
	}
	if(h1 == h2) {
		cout << 1;
		return 0;
	}
	for(int i = 2; i + n2 - 1 <= n1; i++) {
		int r = i + n2 - 1;
		h1 = (h1 - l1[i - 1] * p[n2 - 1]) * P;
		if(mp1[a[i - 1]] == i - 1) {
			mp1[a[i - 1]] = 0;
		}
		if(t1[i - 1] != 0) {
			h1 -= l1[t1[i - 1]] * p[r - t1[i - 1]];
			l1[t1[i - 1]] = 0;
		}
		if(mp1[a[r]] != 0) {
			l1[r] = r - mp1[a[r]];
			t1[mp1[a[r]]] = r;
		} 
		else l1[r] = 0;
		mp1[a[r]] = r;
		h1 += l1[r];
		if(h1 == h2) {
			cout << i;
			return 0;
		}
	}
	return 0;
}
```



---

## 作者：cjh20090318 (赞：2)

思路并不是很直接的一道哈希题，并不算特别难，但也不简单。

## 分析

看到题意后有字符串匹配，很容易想到哈希。

因为每一个明文对应着一个密文，可以记当前单词距离到上一个相同单词的距离（如果没有即为 $0$），可以观察到明文和密文的单词距离序列如果能相同，就说明可以对应上。

为了快速判断这样一个单词距离序列相同，可以用哈希。

滑动查询区间的时候，需要移除新区间中被移除单词第一个位置的哈希值，这个用队列存一下就行。

时间复杂度 $O(n)$，具体请看代码实现。

## 注意事项

因为使用了队列 `std::queue`，而默认的实现方式是 `std::queue<,std::deque<> >`，空间会爆炸，所以我们应该使用 `std::queue<,std::list<> >`。

## 代码

```cpp
//the code is from chenjh
#include<cstdio>
#include<cstring>
#include<iostream>
#include<list>
#include<queue>
#include<unordered_map>
#define MAXN 1000005
using namespace std;
typedef unsigned long long ULL;
const unsigned int p=131;
ULL pn[MAXN];
int n,m,t=0;
unordered_map<string,int> M;
int a[MAXN],b[MAXN],c[MAXN];//c[i] 表示第 i 个单词所造成的哈希贡献。
int ls[MAXN];//记录上一个单词出现的位置。
queue<int,list<int> > Q[MAXN];//存储每一个单词的位置队列信息。
int main(){
	for(string s;cin>>s&&s!="$";){
		if(M.find(s)==M.end()) M[s]=++t;
		a[++n]=M[s];
	}//将 a 的单词转化为数字，方便比较。
	pn[0]=1;
	for(int i=1;i<=n;i++) pn[i]=pn[i-1]*p;//预处理 p 的幂次方数组。
	M.clear(),t=0;//注意清空重新分配编号。
	for(string s;cin>>s&&s!="$";){
		if(M.find(s)==M.end()) M[s]=++t;
		b[++m]=M[s];
	}//将 b 的单词转化为数字，方便比较。
	ULL hsa=0,hsb=0;//a 的区间哈希值和 b 的哈希值。
	for(int i=1;i<=m;i++) hsb=hsb*p+(ls[b[i]]?i-ls[b[i]]:0),ls[b[i]]=i;//相减得到距离，找不到上一个则为 0.
	memset(ls,0,sizeof ls);
	for(int i=1;i<=m;i++){
		c[i]=ls[a[i]]?i-ls[a[i]]:0;
		hsa=hsa*p+c[i];
		Q[a[i]].push(ls[a[i]]=i);
	}
	if(hsa==hsb) return puts("1"),0;
	for(int i=m+1;i<=n;i++){
		Q[a[i-m]].pop();//弹出最前端单词。
		if(!Q[a[i-m]].empty()) hsa-=c[Q[a[i-m]].front()]*pn[i-Q[a[i-m]].front()-1];//删除新的队列中第一个被删除单词所贡献的哈希值，如果不存在则不需要删除。
		c[i]=(ls[a[i]]>i-m)?i-ls[a[i]]:0;
		hsa=hsa*p+c[i];//加入最新元素。
		Q[a[i]].push(ls[a[i]]=i);//加入新的单词。
		if(hsa==hsb) return printf("%d\n",i-m+1),0;
	}
	return 0;
}
```



---

## 作者：hzx360 (赞：2)

前言：感谢审核大大百忙中审核 MnZn 题解。


------------
### 正文

注意到答案和字符串是什么无关，只和不同种类字符串间的位置有关。

为什么能做到位置与文本唯一映射呢？

先看这个~~性感的图~~：

![](https://cdn.luogu.com.cn/upload/image_hosting/2qnjc53j.png)

将字符串向后继连边，若明文中出现该加密串则子串连边后的形式也必然是和这个一样的。那我们完全可以用两相同的相邻串的相对距离表示出这个边的权值。

于是可以考虑哈希，在明文中枚举一段长度和加密文一样的区间，求出区间哈希值，两者哈希值比较即可。

**值得注意的是：若边连向区间外则需要断开。**

具体怎么维护也很简单，这个类似滑动窗口，一边加上新加入点的贡献，一边减去左边要排出区间的贡献。

------------


细节见代码：
```
#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
const int N=3e6+100;
const ull base=131;
map<string,ull>mp1;
map<string,ull>mp2;
ull pre1[N],pre2[N],ne1[N],ne2[N],cnt1,cnt2;
ull goal=0;
void Hash(){for(ull k=1;k<=cnt2;k++) goal=(goal*base+(ull)(ne2[k]-k));}
void init(){
	 //求出两个文本中字符串的前驱后继，用map记录。 
	 string opt;
	 cin>>opt;
	 while(opt[0]!='$'){
	 	++cnt1;
	 	ne1[cnt1]=cnt1;
	 	if(!mp1[opt]) pre1[cnt1]=cnt1;
		else pre1[cnt1]=mp1[opt],ne1[mp1[opt]]=cnt1;
		mp1[opt]=cnt1; 
	 	cin>>opt;
	 }
	 cin>>opt;
	 while(opt[0]!='$'){
	 	++cnt2;
	 	ne2[cnt2]=cnt2;
	 	if(!mp2[opt]) pre2[cnt2]=cnt2;
		else pre2[cnt2]=mp2[opt],ne2[mp2[opt]]=cnt2;
		mp2[opt]=cnt2; 
	 	cin>>opt;
	 }
}
ull p[N];
ull work(){
	Hash();//先求出加密文的哈希值 
	ull l=1,r=cnt2;
	ull now=0;//now表示明文中[l,r]的哈希值 
	for(ull i=1;i<=r;i++) 
		if(ne1[i]<=r) now=(now*base+(ull)(ne1[i]-i));
		else now=now*base;
		
	p[0]=1;
	for(ull i=1;i<r;i++) p[i]=p[i-1]*base;//预处理出进制的系数 
	
	while(r<=cnt1){
		if(now==goal) return l;
		if(ne1[l]<=r) now=(now-p[cnt2-1]*(ull)(ne1[l]-l));
		//若 L 点连出去的边权对哈希值有贡献，因为 L 要被排出区间，所以要减去其贡献 
		now=now*base; 
		if(pre1[r+1]>=l+1) now=(now+(r+1-pre1[r+1])*p[r+1-pre1[r+1]]);
		//若区间内有点连向新加入的点则需要加上这个的贡献 
		l++,r++;
	}
}
signed main(){
	init();
	cout<<work();
	return 0;
}
```
温馨提示：~~能不用哈希做就不要用~~，哈希算出来的数大，不好调。

---

## 作者：Erica_N_Contina (赞：1)

**思路**

让我们先看懂样例的意思。

```C++
a b c x c z z a b c $
prvi dr prvi tr tr x $
```


我们把两个串中相同的子串按等价类来编号，就变成了：

```Plain Text
1 2 3 4 3 5 5 1 2 3
1 2 1 3 3 4
```


然后我们写成差分的形式：

```C++
(1) 1 1 1 -1 2 0 -4 1 1
(1) 1 -1 2 0 0 1
```


好像没什么发现——那我们手动找到明文中的对应密文的那一串单独拎出来呢？

```Plain Text
c x c z z a -> 1 2 1 3 3 4 -> 1 -1 2 0 0 1
prvi dr prvi tr tr x -> 1 2 1 3 3 4 -> 1 -1 2 0 0 1
```


我们惊奇的发现它们转化为等价类及其差分是相同的！这里我们就要想一想为什么之前我们没有发现（或者说为啥之前不相等）呢？

因为我们在明文中匹配密文相当于一个**滑动窗口**，窗口左端点之前的信息我们是不可以记录的！

对于字符串匹配，我们自然想得到字符串哈希。所以现在的问题就是我们如何动态维护窗口内的字符串的哈希，于是我们需要选择一个较好的方法来定义这个字符串哈希来使得我们可以比较方便地维护它。

所以我们记明文中第 $i$ 个单词到（窗口内）上一个相同单词的距离是 $a_i$​，密文中第 $i$ 个单词到上一个相同单词的距离是 $b_i$​。特别地，如果前面没有出现过相同单词，则将距离记作 $-1$。

那么对于一个单词 $v$，当它滑出窗口时，$v$ 后面的与它相同的单词的 $a$ 值就会发生改变。因此我们预处理对于每个单词 $i$（$i$ 为下标），它后面的和它相同的单词的位置 $nxt_i$。当我们的滑动窗口向后滑动时，对滑出窗口的那个字符串 $i$，找到 $nxt_i$，修改 $a_{nxt_i}$ 为 $-1$。

我们用窗口内的 $a_i$ 和 $b_i$ 的哈希值来判定窗口内的字符串和密文是否等价。因为我们的窗口是需要滑动的，故在窗口滑动过程中，$a_i$ 的值会发生改变，我们要快速维护窗口内的字符串的哈希值。

实际上就是区间哈希。

**Code**

```C++
/*
CB Ntsc
*/

#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define pii pair<int, int>
#define pf first
#define ps second

#define rd read()
inline int rd
{
	int xx=0,ff=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') ff=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') xx=xx*10+(ch-'0'),ch=getchar();
	return xx*ff;
}
inline void write(int out)
{
	if(out<0) putchar('-'),out=-out;
	if(out>9) write(out/10);
	putchar(out%10+'0');
}

const int N=5e5+5;
const int M=5e4+5;
const int INF=2e9+5;
const int MOD=2e9+7;
const int BASE=17737;
bool f1;
int n,m;
int prea[N], nxta[N], preb[N], nxtb[N];
int a[N], b[N];
string s;
ull has[N], hass[N];
map <string, int> mp,mp2;
bool f2;

void init(){
	while(cin >> s){
		if(s[0] == '$')break;
        nxta[mp[s]] = ++ n, prea[n] = mp[s], mp[s] = n;
    }
    while(cin >> s){
		if(s[0] == '$')break;
        nxtb[mp2[s]] = ++ m, preb[m] = mp2[s], mp2[s] = m;
    }

	for(int i = 1;i <= n;++ i) if(!nxta[i]) nxta[i] = INF;
    for(int i = 1;i <= m;++ i) if(!nxtb[i]) nxtb[i] = INF;

	for(int i=1;i<=n;i++)a[i]=b[i]=-1;
    for(int i=1;i<=n;i++)if(prea[i])a[i]=i-prea[i];
	for(int i=1;i<=m;i++)if(preb[i])b[i]=i-preb[i];

}
signed main(){

	init();
    
    ull h0 = 0, h = 0; 
	
	hass[0] = 1;
    for(int i = 1;i <= m;++ i) hass[i] = hass[i - 1] * BASE;


    for(int i = 1;i <= m;++ i)
        h0 = h0 * BASE + b[i], h  = h  * BASE + a[i];
    if(h == h0){//特判第一个位置
		cout<<1<<endl;
		return 0;
	}
    for(int i = m + 1;i <= n;++ i){
        h = h * BASE + a[i], h = h - a[i - m] * hass[m];

        if(nxta[i - m] <= i){
            h = h - a[nxta[i - m]] * hass[i - nxta[i - m]];
            a[nxta[i - m]] = -1;
            h = h + a[nxta[i - m]] * hass[i - nxta[i - m]];
        } else if(nxta[i - m] <= n) a[nxta[i - m]] = -1;

        if(h == h0){
			cout<<i - m + 1;
			return 0;
		}
    }
    return 0;
}

```




---

## 作者：Liyuqiao11 (赞：1)

这道题其实就是 [CF471D MUH and Cube Walls](https://www.luogu.com.cn/problem/CF471D) 的变形。CF471D 的思路是将两个数列分别进行差分形成新的数列，再将两个数列进行 KMP 匹配。在这一题中，我们注意到我们所需考虑的仅仅是两个不同位置的字符串是否相等。就拿样例 $3$ 来说，
```
a b c x c z z a b c $
prvi dr prvi tr tr x $
```

我们发现第二个字符串数组中第一个字符串和第三个字符串相同，第四个字符串和第五个字符串相同。第二个字符串和其他的字符串都不同。第六个字符串和其他的字符串也都不相同。

于是我们考虑为每一个字符串赋一个哈希值，如果这个字符串在这个字符串数组中没出现过，那就给它赋目前最大哈希值的值加上一，否则它的哈希值就是之前第一次出现时的哈希值。但是我们很容易发现它的问题，就是可能曾经出现过一个字符串，但是我们现在所匹配的这个范围不包含这个字符串，如果这个范围出现了和这个字符串相同的字符串，那我们按照刚才的思路，会沿用之前的哈希值。可是它的哈希值在这里太小了，在进行 KMP 匹配时会发生错误。

所以现在开始讲解正解，我们可以用 `map` 来维护一个字符串的出现次数。对于每一个位置，我们在它后面 $ n-1 $ 个位置时对它的 `map` 值减一（$n$ 是第二个字符串数组的长度），这个过程类似于滑动窗口。当我们发现一个字符串的 `map` 值为 $ 0 $ 时，给它赋一个新的哈希值，这个值是目前最大哈希值的值加上一。否则我们就给它赋成之前和它相同的字符串的哈希值。然后我们进行差分。差分完后就是一个普通的 KMP 匹配。

在这里我们还需要特判第二个字符串数组只有一个字符串时的情况，这时直接输出 $ 1 $ 就行了。

下面附上本人的代码，码风不是很好看，望诸位谅解。
```c
#include<bits/stdc++.h>
using namespace std;
const int N = 1e6+10;
#define int  long long
int n,m,fail[N],a[N],b[N],s[N],t[N],bz,cnt,tot;
map<string,int> mp;
map<string,int> dc;
map<string,int> mp_2;
string s1[N],s2;
signed main(){
    while(cin>>s2){
        if(s2=="$") break;
        n++;
        s1[n]=s2;
    }
    while(cin>>s2){
        if(s2=="$") break;
        m++;
        if(mp_2[s2]==0){
            tot++;
            mp_2[s2]=tot;
            b[m]=tot;
        }
        else b[m]=mp_2[s2];
        if(m!=1) t[m-1]=b[m]-b[m-1];
    }
    for(int i=1;i<=n;i++){
        if(mp[s1[i]]==0){
            cnt++;
            dc[s1[i]]=cnt;
            a[i]=cnt;
        }
        else a[i]=dc[s1[i]];
        mp[s1[i]]++;
        mp[s1[i-m+1]]--;
        if(i!=1) s[i-1]=a[i]-a[i-1];
    }
    if(m==1){
        cout<<1<<endl;
        exit(0);
    }
    fail[0]=0;
    fail[1]=0;
    int ind=0;
    for(int i=1;i<m-1;i++){
        while(ind&&t[i+1]!=t[ind+1]) ind=fail[ind];
        if(t[i+1]==t[ind+1]){
            ind++;
        }
        fail[i+1]=ind;
    }
    ind=0;
    for(int i=0;i<n-1;i++){
	while(ind&&s[i+1]!=t[ind+1]){
	    ind=fail[ind];
	}
	if(t[ind+1]==s[i+1]){
	    ind++;
	}
	if(ind==m-1){
	    bz=i-m+2;
            break;
	}
    }
    cout<<bz+1<<endl;
    return 0;
}
```



---

## 作者：aaron0919 (赞：0)

# [P8085 の题解](https://www.luogu.com.cn/problem/P8085)

## 新方法

介绍一种与众不同的哈希方法。简单易懂（主要是好想）。

### 核心思路

考虑加密前后的不变量：

原串：`a b a c c`

加密：`x y x z z`

我们发现串之间只有相同和不同的两种关系。

考虑将每个串替换为第一次出现的位置。

`a b a c c` -> `1 2 1 4 4`

就可以直接哈希了。

### 实现

但是我们需要在原串上用滑动窗口滚动，怎么办？

因为第一个串的编号恒为 $1$，整个窗口向后滚，那么每个数都会减少 $1$。

#### 生动形象的例子'

```text
原串: a b a c a b a
窗口: ^-------^
哈希: 1 2 1 4 1
滚动后
原串: a b a c a b a
窗口:   ^-------^
哈希: 1 2 1 4 1
减一: 0 1 0 3 0
再加: = 1 0 3 0 1
```

这时我们发现与原来第一个串相同的串都变为了 $1-1=0$，这样再加回去新的哈希值就可以了。

我们将每种串的出现的位置记录下来，这样可以直接维护新的哈希值。

```text
原串: a b a c a b a
---a: 1 0 1 0 1 0 1
---b: 0 1 0 0 0 1 0
---c: 0 0 0 1 0 0 0
```

我们将出现过的位置设为 $1$，乘上新的第一次出现的位置，就可以较快维护哈希值了。

#### 生动形象的例子''

```text
原串: a b a c a b a
窗口:   ^-------^
哈希: 1 2 1 4 1
减一: 0 1 0 3 0
再加: = 1 0 3 0 1
再加: + 0 2 0 2 0
可得: = 1 2 3 2 1
```

现在我们只用维护每种串出现的位置和对应的窗口间的哈希值，再动态维护当前窗口哈希值即可。

将每个位置的权值都减 $1$，哈希值就要减 $W^0+W^1+\cdots+W^m=\dfrac{W^{m+1}-1}{W-1}$，$W^i$ 是位权，我的代码中设为 $W=10$，方便调试时看。

我的代码中增加了调试，应该能给大家一些帮助。

#### 生动形象的例子'''

看完那个例子：

```text
原串: a b a c a b a
窗口: ^-------^
哈希: 1 2 1 4 1
滚动后
原串: a b a c a b a
窗口:   ^-------^
哈希: 1 2 1 4 1
减一: 0 1 0 3 0
再加: = 1 0 3 0 1
再加: + 0 2 0 2 0
可得: = 1 2 3 2 1
滚动后
原串: a b a c a b a
窗口:     ^-------^
哈希: - 1 2 3 2 1
减一: = 0 1 2 1 0
再加:   = 1 2 1 0 1
再加: b + 0 0 0 4 0
得到:   = 1 2 1 4 1
```

这是全过程，可以看我的代码的调试输出来帮助理解。

## Tips

- 存每种串的出现位置不用开 $10^6$ 个 `deque`，只需要记录在窗口中首次和末次出现的位置，再对于每种串记录后继 `nxt` 即可（学校 OJ 只开 64MB，卡空间调死我了）。
- 调哈希时建议将 $W$ 设为 $10$，方便调试，**可以知道每一位代表什么**，因为是几就对应第几位。

## code

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define int ll

#ifndef ONLINE_JUDGE
template <typename T>
inline void _debug(const T &t) { cerr << t << '\n'; }
template <typename T, typename... Args>
inline void _debug(const T &t, const Args &...rest)
{
    cerr << t << ' ';
    _debug(rest...);
}
#define debug(...) _debug(#__VA_ARGS__ " =", __VA_ARGS__)
#else
#define debug(...) 0
#endif

const int N = 1e6 + 10;
const int INF = 1e18;
const int MOD = 1e9 + 7;
const int W = 10;

ll qpow(ll a, ll b)
{
    ll res = 1;
    while (b)
    {
        if (b & 1)
        {
            res = res * a % MOD;
        }
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

int n, m, target, cur, pw[N]{1}, inv, nxt[N];
vector<string> s, t;
map<string, signed> tmp, hsh;
map<string, pair<signed, signed>> mp;

signed main()
{
    inv = qpow(W - 1, MOD - 2);
    for (int i = 1; i < N; i++)
    {
        pw[i] = pw[i - 1] * W % MOD;
    }
    cin.tie(0)->sync_with_stdio(false), cout.setf(ios::fixed), cout.precision(10);

    s.push_back("$");
    t.push_back("$");

    string str;
    while (cin >> str, str[0] != '$')
    {
        s.push_back(str), ++n;
    }
    while (cin >> str, str[0] != '$')
    {
        t.push_back(str), ++m;
    }
    for (int i = 1; i <= m; i++)
    {
        if (tmp.count(t[i]) == 0)
        {
            tmp[t[i]] = i;
        }
        target = (target * W + tmp[t[i]]) % MOD;
    }
    tmp.clear();
    for (int i = n; i >= 1; i--)
    {
        if (tmp.count(s[i]) == 0)
        {
            nxt[i] = n + 1;
        }
        else
        {
            nxt[i] = tmp[s[i]];
        }
        tmp[s[i]] = i;
    }
    for (int i = 1; i <= m; i++)
    {
        if (mp.count(s[i]))
        {
            hsh[s[i]] = (hsh[s[i]] * pw[i - mp[s[i]].second] + 1) % MOD;
            mp[s[i]].second = i;
        }
        else
        {
            hsh[s[i]] = 1;
            mp[s[i]].second = i;
            mp[s[i]].first = i;
        }
        cur = (cur * W + mp[s[i]].first) % MOD;
    }
    debug(target);
    for (int i = 1; i <= n; i++)
    {
        debug(cur);
        if (cur == target)
        {
            cout << i;
            return 0;
        }
        cur -= (pw[m] - 1) * inv % MOD - MOD;
        debug(cur);
        auto &q = mp[s[i]];
        int fr = q.first, bk = q.second;
        debug(fr, bk);
        hsh[s[i]] = (hsh[s[i]] - pw[bk - fr] + MOD) % MOD;
        debug(hsh[s[i]]);
        q.first = nxt[q.first];
        debug(q.first, q.second);
        if (q.first <= q.second)
        {
            int fi = q.first - i;
            (cur += fi * hsh[s[i]] % MOD * pw[i + m - bk - 1] % MOD) %= MOD;
        }
        else
        {
            mp.erase(s[i]);
            hsh.erase(s[i]);
        }
        debug(cur);
        if (mp.count(s[i + m]))
        {
            hsh[s[i + m]] = (hsh[s[i + m]] * pw[i + m - mp[s[i + m]].second] + 1) % MOD;
            mp[s[i + m]].second = i + m;
        }
        else
        {
            hsh[s[i + m]] = 1;
            mp[s[i + m]].first = i + m;
            mp[s[i + m]].second = i + m;
        }
        debug(mp[s[i + m]].first);
        cur = (cur * W + mp[s[i + m]].first - i) % MOD;
        debug(1);
    }

    return 0;
}
```

---

## 作者：oyoham (赞：0)

### Problem
定义字符串串为由字符串组成的串。  
定义 $S_p$ 为字符串串 $S$ 的第 $p$ 个字符串，下标从一开始。  
定义 $|S|$ 为字符串串 $S$ 的长度。

给你一串字符串串 $S$ 与字符串串 $O$，找到最小的 $x$ 满足：$\forall 1\le i,j\le |O|,[O_i=O_j]=[S_{x+i-1}=S_{x+j-1}]$。
### Solution
考虑算出每个元素上一次出现位置（没有则记为 $0$）不难发现，可以匹配的串由**元素上一次出现位置**组成的数组是相同的。  
如 `a a b a b` 与 `b b a b a` 均为 `0 1 0 2 3`。这样匹配就能 $\Theta(|O|)$ 解决，但是还是会 TLE。  
注意到相邻两次中有大量重复元素，所以考虑改变定义使其能够通过哈希解决，考虑改定义为**元素上一次出现位置与这个元素中的元素个数**。在匹配 $(x,x+|O|-1)$ 失败后，应将与 $S_x$ 相同的下一个元素的**元素上一次出现位置与这个元素中的元素个数**置为 $0$。此时注意到这个做法可以哈希处理，可以就做到 $\Theta(|S|+|O|)$ 了。  
写代码是建议将字符串转成整数方便存储与计算。
### Code 
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define int ll
#define aF(begin,end,step,name) for(int name=begin;name<=end;name+=step)
#define oF(B,E,N) aF(B,E,1,N)
#define af(B,E,S) aF(B,E,S,i)
#define of(B,E) af(B,E,1)
#define tF(E,N) oF(1,E,N)
#define tf(E) of(1,E)
#define nF(N) tf(n,N)
#define nf() tf(n)
inline ll read(){
	ll x=0;
	short f=1;
	char c=getchar();
	while(c>57||c<48){
		if(c==45) f=-1;
		c=getchar();
	}
	while(c<58&&c>47){
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}
inline void write(ll x){
	if(x<0ll) putchar(45),x=~x+1;
	if(x>9ll) write(x/10);
	putchar(x%10|48);
}
int L1=0,L0=0;
struct Map{
	#define T string
	#define vT int
	#define Mod 100003
	#define sz 1000000
	#define Basic 0
	int f(T x){
		return x.length()*x[0]*x[x.length()-1]%Mod;
	};
	int h[Mod+5],nxt[sz+5],idx;
	T id[sz+5];
	vT v[sz+5];
	vT& get(T x){
		int p=f(x);
		int _=h[p];
		while(_&&id[_]!=x){
			_=nxt[_];
		}
		if(!_){
			id[_=++idx]=x;
			nxt[_]=h[p];
			h[p]=_;
			v[_]=Basic;
		} 
		return v[_];
	}
	void change(T x,vT val){
		get(x)=val;
	}
	int getpl(T x){
		int p=f(x);
		int _=h[p];
		while(_&&id[_]!=x){
			_=nxt[_];
		}
		return _;
	}
	void clear(){
		idx=0;
		for(int i=0;i<Mod;i++) h[i]=0;
	}
	vT& operator[](T x){
		return get(x);
	}
	#undef T
	#undef vT
	#undef Mod
	#undef sz
	#undef Basic
}mp;
#define hashp 114514
#define hashm 1000000007
#define hash jntm
int hash(int *x){
	int hashv=0;
	of(0,L1-1){
		hashv=(hashv*hashp+x[i])%hashm;
	}
	return hashv;
}
int P[1000005]={1};
int hasht(int x,int p){
//	printf("?xp^k=%d\n",(x*P[p-1])%hashm);
	return (x*P[p-1])%hashm;
}
int a[1000006],b[1000006],nxt[1000006];
string s;
signed main(){
	mp["$"]=-1;
	while(1){
		cin>>s;
		int &_=mp[s];
		if(!~_) break;
		L0++;
		a[L0]=_?nxt[_]=L0,L0-_:0;
		_=L0; 
	}//处理S
	mp.clear();
	mp["$"]=-1;
	while(1){
		cin>>s;
		int &_=mp[s];
		if(!~_) break;
		L1++;
		b[L1]=_?L1-_:0;
		_=L1; 
	}//处理O
	tf(L1) P[i]=P[i-1]*hashp%hashm;
	int V=hash(b+1),N=hash(a+1);
	tf(L0){
		if(V==N) write(i),exit(0);
		N=(N-hasht(a[i],L1));//去掉首位元素
		if(nxt[i]-i<L1) N-=hasht(a[nxt[i]],L1+i-nxt[i]);//更新其后相同元素
		a[nxt[i]]=0;
		N*=hashp;//整体移动
		N+=a[i+L1];//加上后面的元素
		N=(N%hashm+hashm)%hashm;//记得取模！！！
	}
  return 0
}
```

---

