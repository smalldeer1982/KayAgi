# Prefixes and Suffixes

## 题目描述

You have two strings $ s_1 $ and $ s_2 $ of length $ n $ , consisting of lowercase English letters. You can perform the following operation any (possibly zero) number of times:

- Choose a positive integer $ 1 \leq k \leq n $ .
- Swap the prefix of the string $ s_1 $ and the suffix of the string $ s_2 $ of length $ k $ .

Is it possible to make these two strings equal by doing described operations?

## 说明/提示

In the first test case:

- Initially $ s_1 = \mathtt{cbc} $ , $ s_2 = \mathtt{aba} $ .
- Operation with $ k = 1 $ , after the operation $ s_1 = \mathtt{abc} $ , $ s_2 = \mathtt{abc} $ .

In the second test case:

- Initially $ s_1 = \mathtt{abcaa} $ , $ s_2 = \mathtt{cbabb} $ .
- Operation with $ k = 2 $ , after the operation $ s_1 = \mathtt{bbcaa} $ , $ s_2 = \mathtt{cbaab} $ .
- Operation with $ k = 3 $ , after the operation $ s_1 = \mathtt{aabaa} $ , $ s_2 = \mathtt{cbbbc} $ .
- Operation with $ k = 1 $ , after the operation $ s_1 = \mathtt{cabaa} $ , $ s_2 = \mathtt{cbbba} $ .
- Operation with $ k = 2 $ , after the operation $ s_1 = \mathtt{babaa} $ , $ s_2 = \mathtt{cbbca} $ .
- Operation with $ k = 1 $ , after the operation $ s_1 = \mathtt{aabaa} $ , $ s_2 = \mathtt{cbbcb} $ .
- Operation with $ k = 2 $ , after the operation $ s_1 = \mathtt{cbbaa} $ , $ s_2 = \mathtt{cbbaa} $ .

In the third test case, it's impossible to make strings equal.

## 样例 #1

### 输入

```
7
3
cbc
aba
5
abcaa
cbabb
5
abcaa
cbabz
1
a
a
1
a
b
6
abadaa
adaaba
8
abcabdaa
adabcaba```

### 输出

```
YES
YES
NO
YES
NO
NO
YES```

# 题解

## 作者：hzlqwq (赞：9)

模拟样例我们会发现，操作实际上并没有那么简单，我们需要细细剖析它的性质：

直接考虑前缀和后缀比较困难，考虑将 $s_2$ 翻转，操作变为选择 $s_1$ 和 $s_2$ 相同长度的一段前缀，交换并翻转；因此可以发现，同一对 $s_{1,i},s_{2,i}$ 的相对位置是不会变的，就像一个长条形的“盒子”，上下绑定了，只能翻转“盒子”（上下交换）或左右移动。

此时有一个重要的结论：**任意的这些盒子的排列都是可以得到的**。证明如下：

假如将 $\{s_{1,i},s_{2,i}\}$ 称为 $i$ 号盒子，盒子 $i$ 的目标位置是 $p_i$，从后往前满足位置（过程类似选择排序），当前要将 $p_i=j$ 的盒子移到 $j$，$j+1\sim n$ 位置上的盒子已经满足并固定，$i$ 号盒子现在在 $x$ 位置，则可以：

- 执行 $k=x$，将第 $x$ 个盒子调到第 $1$ 个；

- 执行 $k=j$，将第 $1$ 个盒子调到第 $j$ 个。

于是，执行最多 $2n$ 次操作，任意的盒子排列都能被组合出来。

同时，**任意一个盒子的上下两个元素也是可以交换的**，假设目前要交换第 $i$ 个盒子的上下两个元素，操作如下：

- 执行 $k=i$，将第 $i$ 个盒子调到第 $1$ 个，此时上下元素颠倒；

- 执行 $k=1$，交换第 $1$ 个盒子的上下元素，此时未颠倒；

- 执行 $k=i$，将第 $1$ 个盒子放回位置 $i$，其他盒子执行了两次操作，抵消了，没有发生任何变化，当前盒子颠倒，目标达成。

因此，每个盒子可以看成一个无序对，我们只要**令第 $i$ 个和第 $n-i+1$ 个无序列相等**即可，于是统计不同的无序对数量和它们分别的出现次数（哈希），除了 $n$ 为奇数且最多有一个两个元素相等的无序对只出现了一次（放在正中间，$i=n-i+1$）的情况，所有无序对出现的次数都需要为偶数，否则无解。

时间复杂度 $O(n)$。

参考代码：

```cpp
#include <iostream>
#include <unordered_map> 

#define hsh(x,y) 26*(min(x,y)-'a')+max(x,y)-'a'

using namespace std;

const int N=1e5+10;

int t,n;
char s1[N],s2[N];
unordered_map<int,int> buc;

inline void speedup(){
	ios::sync_with_stdio(0);
	cin.tie(0);
} 

int main(){
	speedup();
	cin>>t;
	while (t--){
		cin>>n>>s1+1>>s2+1;
		buc.clear();
		for (int i=1;i<=n;i++) buc[hsh(s1[i],s2[n-i+1])]++;
		int ans=1,cnt=0;
		for (auto [i,j]:buc) ans&=j%2==0||n%2&&++cnt<=1&&i%26==i/26;
		cout<<(ans?"YES\n":"NO\n");
	}
	return 0;
}
```

---

## 作者：Jasper08 (赞：4)

直接考虑 $T$ 的后缀有点困难，考虑先将 $T$ 翻转一下，记为 $T'$。则对于题目中的一次操作，相当于我们先将 $S[1\sim k],T'[1\sim k]$ 翻转，然后再交换 $S[1\sim k],T'[1\sim k]$。那么可以发现，$S_i$ 和 $T'_i$ 的相对位置是不会改变的。那么我们可以用 $P_i=(S_i,T_i')$ 表示 $S,T'$ 中第 $i$ 个位置上的字符对。

接下来，我们需要证明 $2$ 个重要结论：

- $(S_i,T_i')$ 是可以任意排列的。

证明：

令当前序列为 $(S_1,T'_1),(S_2,T'_2),\cdots(S_n,T_n')$。

假设我们已经排列好了第 $j$ 位之后所有的元素，对于 $1\le i\le j$，可以通过 $2$ 次操作将 $(S_i,T_i')$ 移动至第 $j$ 位 。

1. $k=i$：将 $(S_i,T_i')$ 移动至第 $1$ 位，并交换为 $(T_i',S_i)$；
2. $k=j$：将 $(S_i,T_i')$ 移动至第 $j$ 位，并交换为 $(S_i,T_i')$。

这样我们就成功将 $(S_i,T_i')$ 移动至第 $j$ 位 。

- $(S_i,T_i')$ 可以交换为 $(T_i',S_i)$ 。

证明：

1. $k=i$：将 $(S_i,T_i')$ 移动至第 $1$ 位，并交换为 $(T_i',S_i)$；
2. $k=1$：将 $(S_i,T_i')$ 移动至第 $1$ 位，并交换为 $(S_i,T_i')$；
3. $k=i$ ：将 $(S_i,T_i')$ 移动至第 $i$ 位，并交换为 $(T_i',S_i)$。

这样我们就成功让 $(S_i,T_i')$ 交换为 $(T_i',S_i)$。

到这一步就比较简单了。可以发现，对于最终的序列，一定有 $S_i=T'_{n-i+1},T'_i=S_{n-i+1}$。也就是说，如果我们不考虑一个对中的顺序，一定有 $P_i=P_{n-i+1}$。由此可以得到结论：

- $n$ 为偶数时，每种对都需要出现偶数次。
- $n$ 为奇数时，只有一种对 $(x,x)$ 可以出现奇数次，其余种类的对都需要出现偶数次。

通过哈希和桶实现，时间复杂度 $O(T|\Sigma|^2)$（$|\Sigma|$ 为字符集大小）。


```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

typedef pair<int, int> pii;
#define Yes cout << "YES\n"
#define No cout << "NO\n" 

const int N = 1e5+10; 

int t, n, num[1000];
char S[N], T[N];

int h(int a, int b) {
	if (a > b) swap(a, b);
	return a*26 + b;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	
	cin >> t;
	while (t -- ) {
		memset(num, 0, sizeof num);
		cin >> n >> S+1 >> T+1;
		reverse(T+1, T+n+1);
		for (int i = 1; i <= n; ++i) num[h(S[i]-'a', T[i]-'a')] ++;
		int mid = -1;
		for (int i = 0; i < 700; ++i) {
			if (num[i] % 2) {
				if (mid != -1) {mid = 1000; break;}
				mid = i;
			} 
		}
		if (mid == 1000) No;
		else if (n % 2) (mid/26 == mid%26) ? Yes : No;
		else (mid != -1) ? No : Yes;  
	} 
	return 0;
}
```


---

## 作者：mountain_climber (赞：3)

纪念第一道自己切的2200*，来发一篇题解。

~~说实话这道题能切主要还是因为它基本不用算法和数据结构。~~

温馨提示：请你先沉下心来自己思考，实在不会了再来看这篇题解。

~~如果你要好好看这篇题解好的话，那么请你真正的好好看。~~

首先我们来分析题目给出的操作：

- “交换 $s$ 的前缀和 $t$ 的后缀”

这个操作看起来让人不舒服，因为我们希望操作更加的优美和简单（注意这个思想，当你看到一个操作的时候，你希望它变成一个你喜欢的样子）。

所以我们让这个操作等价为：

- “将 $t$ 翻转，记为 $t^{1}$”
- “交换 $s$ 与 $t^{1}$ 的长度为 $k$ 的前缀”
- “翻转 $s$ 与 $t^{1}$ 的长度为 $k$ 的前缀”

好的，你现在可能会骂我了：“你这也没让操作变得更简单啊，你这不是把原本的一个操作分裂成了三个操作吗？！”

听我解释，如果你交换两个字符串的不同部分，这是十分难以考虑的 ~~（巨佬除外，巨佬不用听，巨佬直接切）~~，所以我们让它变成交换两个字符串的相同部分，再来考虑。

先举个例子解释一下为什么等价：

当 $s=\text{"abcde"}，t=\text{"fghij"}$ 时，我们先翻转 $t$，得到 $t^{1}=\text{"jihgf"}$。

我们对原串执行操作 $k=2$，就等价于先交换 $s$ 与 $t^{1}$ 的长度为 $2$ 的前缀，得到 $s=\text{"fgcde"}，t^{1}=\text{"abhij"}$。

然后我们再翻转 $s$ 与 $t^{1}$ 的长度为 $2$ 的前缀，得到 $s=\text{"gfcde"}，t^{1}=\text{"bahij"}$，最后我们将 $t^{1}$ 还原成 $t$，得到交换后的 $t=\text{"jihab"}$，就等价于题目操作。

没看懂的先理解一下哈。

然后我们对新的操作进行考虑，容易得到非常好的性质（关键性质）：

**在我们对 $s$ 与 $t^{1}$ 的前缀做操作的时候（交换和翻转操作），我们并不会改变同一个位置上两个字符的相对位置。**

解释一下：

当 $s=\text{"axxxx"}，t^{1}=\text{"bxxxx"}$ 时，不管你怎么操作，其中字符‘a’与字符‘b’的相对位置不会改变，或者说 $pos_{\text{a}}=pos_{\text{b}}$ 恒成立。

但是注意这两个字符的上下位置可以改变。

所以我们约定一个无序对集合 $\phi$，其中存储所有由 $s$ 与 $t^{1}$ 的某一位上下组成的无序字符对。

$s=\text{"abcde"}，t^{1}=\text{"fghij"}$ 时，$\phi=[('a','f'),('b','g'),('c','h'),('d','i'),('e','j')]$，注意字符对是**无序**对（因为可以上下交换）。

下面我们大胆猜想，我们可以从 $\phi$ 中按任意顺序取出一些数对组成任意的两个可以组成的字符串，实质是通过有限次操作得到任意我们想要的顺序，举个例子：

$s=\text{"abcde"}，t^{1}=\text{"fghij"}$ 时，可以通过一些操作得到：

- $s=\text{"cdeab"}，t^{1}=\text{"hijfg"}$
- $s=\text{"ebhda"}，t^{1}=\text{"jgcif"}$
- $s=\text{"adegc"}，t^{1}=\text{"fijbh"}$

等等等。。。

就是在不改变同一位置字符相对位置的情况下可以任意交换一个字符的上下位置，以及一个字符对的下标，从而得到任意 $\phi$ 的排列。

下面我们来证明这个事情（没看懂请先看证明）：

命题一：可以任意改变字符对的排列。

假设我们想得到 $\phi^{1}$，我们已经使 $\phi^{1}[k + 1,n] = \phi[k+1,n]$ 了，我们现在要将 $i$ 移动到 $k$，我们只需要先执行操作 $i$，将 $i$ 换到开头，再执行操作 $k$，把开头的 $i$ 移动到 $j$ 就可以了，所以我们用归纳法证明了这个命题。（注意此处我们并没有改变字符对的上下位置关系），我累了，所以请读者自己举例理解。

命题二：可以改变任意位置字符的上下位置关系。

就是说可以将 $s=\text{"abcde"}，t^{1}=\text{"fghij"}$ 变为 $s=\text{"abhde"}，t^{1}=\text{"fgcij"}$。

假设我们交换第 $k$ 位，我们其实直接交换就行了，因为有命题一的帮助，我们可以直接恢复被改变的位置。

所以就证明了，一样的，请读者自己举例子来看看是怎么回事。

呼，终于做完“准备工作”了，这看似很繁琐其实它只是解释起来比较繁琐，或是我写的太细了。。。

所以说呢，我们终于可以开始判断题目的问题了：

当字符串长度是偶数的时候，我们只要保证所有相等的无序字符对的数量都是偶数就行了。

例子：

字符对集为 $[('a','b'),('a','b'),('a','b'),('a','b'),('a','c'),('a','c')]$ 时，将相同的字符对左放一个右放一个就行了，即 $s=\text{"aacabb"}，t^{1}=\text{"bbacaa"}$，显然可以。

当字符串长度是奇数的时候，其实就是偶数情况可以在中间加上一个两个字符相等的字符对。

例子：

字符对集为 $[('a','b'),('a','b'),('a','b'),('a','b'),('a',c'),('a','c'),('z','z')]$ 时，将相同的字符对左放一个右放一个，把单独的放在中间就行了，即 $s=\text{"aaczabb"}，t^{1}=\text{"bbazcaa"}$，显然可以。

所以说最后得出的结论是：

- 当长度为偶数时，相同字符对出现字数必须是偶数。

- 当长度是奇数时，相同字符对出现字数须是偶数，单独剩下的字符对必须内部两个字符相等。

代码：

```
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
typedef pair<char, char> pii;
int t, n;
char s1[N], s2[N];
map<pii, int> m;
int main()
{
	scanf("%d", &t);
	while (t -- )
	{
		m.clear();
		scanf("%d", &n);
		scanf("%s", s1 + 1);
		scanf("%s", s2 + 1);
		for (int i = 1, j = n; i <= n, j >= 1; i ++, j -- )
		{
			char maxn = max(s1[i], s2[j]), minn = min(s1[i], s2[j]);
			pii p = make_pair(maxn, minn);
			m[p] ++ ;
		}
		int cnt = 0;
		bool flg = false;
		for (map<pii,int>::iterator it = m.begin(); it != m.end(); it ++ )
		{
			if (it->second % 2 == 0) continue;
			if (it->first.first == it->first.second && cnt == 0) cnt ++ ;
			else
			{
				printf("No\n");
				flg = true;
				break;
			}
		}
		if (flg) continue;
		else if (cnt == 0 && n % 2 == 0) printf("Yes\n");
		else if (cnt == 1 && n % 2 == 1) printf("Yes\n");
		else printf("No\n");
	}
	return 0;	
} 
```

[AC记录](https://codeforces.com/contest/1730/submission/269693899)

完结散花~

---

## 作者：_liuyi_ (赞：2)

好厉害的题啊，想了好久。

交换前后缀有点复杂，考虑构造出交换两个点的形式，这样进行多次可以等价于交换前后缀。

假设要交换的前后缀形如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/xkxtzq1a.png)

我们可以先交换两个前后缀，然后交换 $C,B$，最后交换前后缀。

![](https://cdn.luogu.com.cn/upload/image_hosting/g4u0wclo.png)

这样就只交换了 $B,C$。更形式化的，每次可以只交换 $s1_i$ 和 $s2_{n-i+1}$。

还有一个重要的观察，每次交换前后缀 $s1_i$ 仍然和 $s2_{n-i+1}$ 匹配。

现在不妨转换一下问题，可以将 $s2$ 翻转然后和 $s1$ 拼在一起为 $S$，还有 $n$ 个无序点对，每对可以填在 $S_i$ 和 $S_{i+n}$，问 $S$ 是否可以为一个回文串。

转化后的问题就比较简单了，可以根据是否存在出现次数为奇数的点对和 $n$ 的奇偶性分讨即可。

[code](https://codeforces.com/contest/1730/submission/293512817)

---

## 作者：DaiRuiChen007 (赞：1)

# CF1730D 题解



## 思路分析

先对 $T$ 进行翻转，每次操作会变成：翻转 $S[1\sim k],T[1\sim k]$，然后交换 $S[1\sim k],T[1\sim k]$。

根据上面的转化，有一个显然的观察：一对同位置的 $(S_i,T_i)$ 在经过若干次操作后依然会在同一个位置上。

根据上面的观察得到：只要确定 $S$，$T$ 也随之确定。

因此对于最终的状态 $(S^\star,T^\star)$ 我们可以用一个长度为 $n$ 的排列 $\{p_i\}$ 和一个长度为 $n$ 的 01 串 $\{b_i\}$ 表示，具体规则如下：

> 对于 $(S^\star_i,T^\star_i)$：
>
> - 如果 $b_i=0$，那么 $(S^\star_i,T^\star_i)=(S_{p_i},T_{p_i})$。
> - 如果 $b_i\ne 0$，那么 $(S^\star_i,T^\star_i)=(T_{p_i},S_{p_i})$。

注意到有如下观察：

> 观察：
>
> 对于任意的一个状态表示 $(\{p_i\},\{b_i\})$，都存在一种合法的操作序列使我们能够得到一个合法的终态 $(S^\star,T^\star)$ 恰好能够用 $(\{p_i\},\{b_i\})$ 表示。
>
> 对于每一次操作，我们会使 $\{p_i\}$ 的前 $k$ 位翻转，$\{b_i\}$ 的前 $k$ 位逐位取反后翻转。
>
> 事实上，我们只需要证明存在一种操作使得我们能从任意一个状态 $(\{p'_i\},\{b'_i\})$ 开始，经过若干次操作使得 $p'_n=p_n$ 和 $b'_n=b_n$，剩下的步骤由数学归纳法即可得到。
>
> 不妨假设在 $\{p'_i\}$ 中 $p_n$ 对应 $p'_k$，那么通过操作 $[1,k]$ 和 $[1,n]$ 就可以把 $p'_k$ 移动到 $p'_n$ 上，此时 $b'_n$ 会变成 $b'_k\oplus 1$，如果我们需要保证 $b'_k$ 不变，那么在操作 $[1,n]$ 之前先操作一次 $[1,1]$ 就可以使得 $b'_k$ 移动到 $b'_n$ 并且保持值不变。

因此，我们得到了原题的操作等价于任意重排 $(S_i,T_i)$ 并且任意交换 $(S_i,T_i)$。

由于我们翻转了原序列，那么我们等价于让 $S+T$ 变成一个回文串。

考虑一组相对下标 $(i,n-i+1)$，我们需要使 $S_i=T_{n-i+1},T_i=S_{n-i+1}$，因此对于两个相等的无序对 $\{S_x,T_x\}$ 和 $\{S_y,T_y\}$，我们可以把他们分别放到位置 $i$ 和位置 $n-i+1$ 上，使他们满足条件，可以证明这是使 $S+T$ 回文的充要条件。

因此我们维护每个无序字符对 $\{\alpha,\beta\}$ 出现的次数，如果所有的 $\{\alpha,\beta\}$ 出现的次数都是偶数那么满足条件。

不过对于 $n$ 为奇数的情况，我们需要恰好一对 $\{\alpha,\alpha\}$ 是出现过奇数次，因此我们可以采用 `map` 来统计。

时间复杂度 $\Theta(n+k^2\log k)$，$k$ 为字符集大小。

## 代码呈现

```cpp
#include<bits/stdc++.h>
#define pcc pair<char,char>
using namespace std;
const int MAXN=1e5+1;
char s[MAXN],t[MAXN];
inline void solve() {
	int n;
	scanf("%d%s%s",&n,s+1,t+1);
	map <pcc,int> cnt;
	for(int i=1,j=n;i<=n;++i,--j) ++cnt[make_pair(min(s[i],t[j]),max(s[i],t[j]))];
	bool eq=false;
	for(auto u:cnt) {
		if(u.second%2==0) continue;
		if(u.first.first==u.first.second&&!eq) eq=true;
		else {
			puts("NO");
			return ;
		}
	}
	puts((eq&&n%2!=0)||(!eq&&n%2==0)?"YES":"NO");
}
signed main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```



---

## 作者：incra (赞：0)

### Sol
假设两个串分别为 $a,b$，考虑操作长度为 $k$ 的前缀和后缀，那么可以得到：

- $a'\gets b_{n-k+1}b_{n-k+2}\dots b_n,a_{k+1}a_{k+2}\dots a_n$。

- $b'\gets b_1b_2\dots b_{n-k}a_{1}a_{2}\dots a_k$。

如果你仔细观察 $a'$ 和 $b'$，其实可以得到 $a'_i=b'_{n-i+1}$，记 $cnt_{i,j}=\displaystyle\sum_{k=1}^n[a_k=i\land b_{n-k+1}=j]$，如果 $n$ 是偶数，那么对于任意 $i,j$ 都需要满足 $cnt_{i,j}\equiv0\pmod 2$，如果 $n$ 是奇数，那么允许有且仅有一对 $i,j$ 满足 $cnt_{i,j}\equiv1\pmod 2$ 且 $i=j$，并且其他的 $i,j$ 仍然需要满足 $cnt_{i,j}\equiv2\pmod 2$。

注意上文中 $a_i,b_{n-i+1}$ 并无顺序关系，如果你操作 $k$ 然后操作 $k-1$，那么就可以交换 $a_k$ 和 $b_{n-k+1}$。
### Code
[Link](https://codeforces.com/contest/1730/submission/319732893)。

---

## 作者：SFlyer (赞：0)

这也太难了。

首先发现这个操作很让人难受，因为还要考虑比如说重叠的情况，也没有什么性质，就考虑转换一下。

常用的方法有两个串拼在一起，或者变成反串。这里我们 $t\gets \textsf{rev}(t)$，这样操作就变成了：

- 选定 $k$。

- 把长度为 $k$ 的前缀交换。

- 把长度为 $k$ 的前缀翻转。

发现看起来好看许多，原因是操作的位置是一样的。进一步发现，$s,t$ 的置换是一摸一样的，即原来在一个位置的现在还在一个位置，也就是说，有无法改变位置顺序的 $n$ 个“对”$s_i$ 和 $t_i$。

现在猜测结论：任何排列都可行，$s_i,t_i$ 可以随意交换。

先证明第一点。可以看成一个 $1\sim n$ 的排列，每一次可以翻转前缀，问可不可以生成所有排列。

设要生成 $p$。那么我们将 $p_n$ 的位置先填上，就变成了一个长度为 $n-1$ 的子问题，一直归纳下去即可。

再证明第二点。如果你现在要反转第 $x$ 位，进行操作：选 $k=x$，选 $k=1$，选 $k=x$ 即可。

因此现在问题就简单了。贪心匹配即可。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 1e5+5;

int n;
string s,t;

void solve(){
	cin>>n>>s>>t;
	reverse(t.begin(),t.end());
	s=" "+s;
	t=" "+t;
	map<pair<int,int>,int> mp;
	for (int i=1; i<=n; i++){
		int x=s[i]-'a',y=t[i]-'a';
		if (x>y) swap(x,y);
		mp[{x,y}]++;
	} 
	int f=0;
	for (auto u : mp){
		if (u.second&1){
			if (u.first.first!=u.first.second){
				cout<<"NO\n";
				return;
			}
			f++;
			if (f>n%2){
				cout<<"NO\n";
				return;
			}
		}
	}
	cout<<"YES\n";
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	int t;
	cin>>t;
	while (t--){
		solve();
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

### ~~这仿佛也许似乎就是个模拟吧~~——   

感觉这个操作很不好搞，需要有很多东西，直觉告诉我们可以转化一下这个操作再依靠新的操作去处理。      

我们手模一下可以发现 $S_{i}$ 和 $T_{n-i+1}$ 的对应关系是永远不变的，且存在一种方式等于直接交换，其实就是把两个变成第一个，换就行了。        

然后我们发现仅仅用这种操作还原并不是冲要的，再思考一波...      

发现就只是顺序维护不了，我考虑发掘一下顺序上的性质。然后对于顺序上，每次可以把一个数移到对应数列的开头，显然，通过这样的方法，可以得到序列的任意一个序列，然后我们看到这两个条件与先前等价。     

因此我们用这种操作处理问题，显然对于一堆字母，他与之相对应的有且仅有一个对，那么这样每两个对一组的东西相互独立。     

那么只要这四个字母可以两两对应就行，然后特判一下 $n$ 为奇数时，首尾相等的可以独立一次就行。

```cpp
#include<bits/stdc++.h>
using namespace std;
int ttt,n,p[30][30]; char s[200005],t[200005];
int main(){
	scanf("%d",&ttt);
	while (ttt--){
		memset(p,0,sizeof(p));
		scanf("%d%s%s",&n,s+1,t+1);
	    for (register int i=1;i<=n;i++){
	        int a=s[i]-'a',b=t[n+1-i]-'a';
	        if (a>b) swap(a,b);
	        p[a][b]++;
	    } bool f=true;
	    for (register int i=0;i<26;i++)
	        for (register int j=i+1;j<26;j++)
	            if (p[i][j]&1)
					f=false;
	    int ans=0;
	    for (int i=0;i<26;i++)
			ans+=p[i][i]%2;
	    if (!f||ans>n%2)
			puts("NO");
	    else puts("YES");
	}
	return 0;
}
```

---

## 作者：zuytong (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1730D)



------------
## 题解

肉眼瞪性质：

- 1. 对于 $s_1$ 中 $i$ 上的字母，它与 $s_2$ 中 $n+1-i$ 上的字母的相对位置不会变（也就是说，当 $s_1$ 的 $i$ 移到 $j$ 位置时，$s_2$ 的 $n+1-i$ 也会相应移到 $n+1-j$）。

我们称这样为一个字母对。

- 2. 对于一个字母对，它们可以移动到任意一个地方。

（不太会证明，可以自己动手试一下）

因此，我们将所有字母对都记录下来。

对于一种字母对 $(i,j)$ （$i,j$ 表示两个**不同**的字母），它的个数必须为偶数；

对于相同字母的字母对 $(i,i)$，当 $n$ 为奇数时，我们允许有且仅有一种 $(i,i)$ 的个数为奇数（就是将一对 $(i,i)$ 放在中间）；当 $n$ 为偶数时，那就还是必须个数都为偶数。


------------
## 代码

```cpp
#include<bits/stdc++.h>
#define LL long long
#define FOR(i, x, y) for(int i = (x); i <= (y); i++)
#define ROF(i, x, y) for(int i = (x); i >= (y); i--)
using namespace std;
inline int rd()
{
	int sign = 1, re = 0; char c = getchar();
	while(!isdigit(c)) {if(c == '-') sign = -1; c = getchar();}
	while(isdigit(c)) {re = re * 10 + (c - '0'); c = getchar();}
	return sign * re;
}
int T, n;
char s1[100005], s2[100005];
int c1[30][30];
bool ans, ji;
signed main()
{
	T = rd();
	while(T--)
	{
		ans = 1; ji = 0;
		memset(c1, 0, sizeof(c1));
		n = rd();
		scanf("%s%s", s1 + 1, s2 + 1);
		for(int i = 1, j = n; i <= n; i++, j--) c1[s1[i] - 'a'][s2[j] - 'a']++;
		FOR(i, 0, 25)
		{
			if(n & 1)
			{
				if(c1[i][i] & 1)
				{
					if(ji)
					{
						ans = 0;
						break;
					}
					ji = 1;
				}
			}
			else if(c1[i][i] & 1)
			{
				ans = 0;
				break;
			}
			FOR(j, i + 1, 25)
			{
				if((c1[i][j] & 1) != (c1[j][i] & 1))
				{
					ans = 0;
					break;
				}
			}
			if(!ans) break;
		}
		if(ans) puts("YES");
		else puts("NO");
	}
	return 0;
}
```


---

