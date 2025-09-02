# Binary Literature

## 题目描述

A bitstring is a string that contains only the characters 0 and 1.

Koyomi Kanou is working hard towards her dream of becoming a writer. To practice, she decided to participate in the Binary Novel Writing Contest. The writing prompt for the contest consists of three bitstrings of length $ 2n $ . A valid novel for the contest is a bitstring of length at most $ 3n $ that contains at least two of the three given strings as subsequences.

Koyomi has just received the three prompt strings from the contest organizers. Help her write a valid novel for the contest.

A string $ a $ is a subsequence of a string $ b $ if $ a $ can be obtained from $ b $ by deletion of several (possibly, zero) characters.

## 说明/提示

In the first test case, the bitstrings 00 and 01 are subsequences of the output string: 010 and 010. Note that 11 is not a subsequence of the output string, but this is not required.

In the second test case all three input strings are subsequences of the output string: 011001010, 011001010 and 011001010.

## 样例 #1

### 输入

```
2
1
00
11
01
3
011001
111010
010001```

### 输出

```
010
011001010```

# 题解

## 作者：syksykCCC (赞：8)

考虑着重关注两个 $0/1$ 字符串 $s_1, s_2$，构造一个 $S$ 同时含有 $s_1, s_2$ 作为子序列，那么 $|S|$ 至少应该是多少呢？

答案显然是 $|s_1| + |s_2| - |\operatorname{LCS}(s_1, s_2)|$。

但是通常求 $\operatorname{LCS}$ 是 $O(n^2)$ 的 DP，这里显然行不通，但考虑到这里是 $0/1$ 字符串，而且并不是一定要最小化长度，只要满足一定限制即可，所以有没有改进方法呢？

> 对于任意长度为 $2n$ 的 $0/1$ 字符串 $s$，其中必然有至少 $n$ 个 $0$ 或者至少 $n$ 个 $1$。

这个结论的正确性是非常显然的，它的另一种表述形式是，每个 $s_i$ 要么含有 $t_1 = \footnotesize\begin{matrix} n \\ \overbrace{00\cdots 0}\end{matrix}$ 要么含有 $t_2 = \footnotesize\begin{matrix} n \\ \overbrace{11\cdots 1}\end{matrix}$。

而本题中又给定了 $3$ 个字符串，所以必然有两个字符串所含的 $t$ 是相同的。

于是必然可以构造出一种 $2n+2n - n = 3n$ 的合法方案。

构造过程中，只要把 $s_1, s_2$ 中对应的字符插到 $t$ 的对应位置中即可。

---

## 作者：Light_snow (赞：3)

提供一个更为简洁的做法。

我们考虑三位上必定有两位是相同的。

那么我们逐位确定 $S$ 的每一位。

我们设 $la,lb,lc$ 为当前 $S$ 能和 $a,b,c$ 匹配上的最长的子序列长度。

那么我们每次扩展 $S$ 时将其多加一位 $to$，使 $to$ 满足在 $a[la + 1],b[lb + 1],c[lc + 1]$ 中至少出现两次，并将出现的位置对应字符串的指针向右移。

直到出现了一个字符串已经完全成为了 $S$ 的子序列。

那么我们在剩下的两个字符串中选取已经匹配位数最多的并输出其剩下的项，
下证明为什么这样构造的 $len(S) \leq 3\times n$。

考虑到我们每次多加入一位，一定有两个以上的指针向右移动一位。

那么我们考虑显然只有 $n$ 个操作对这个成为子序列的字符串的指针有影响。

而他每次的操作都会对剩下两个串至少一个造成向右的影响，那么 $(\frac{2\times n}{2} = n) + m \leq \max(lb,lc)$（这里假设 $a$ 成为子序列,$m$ 为同时操作 $b,c$ 的次数）。

那么最后的 $S$ 的长度为 $2\times n + m + 2\times n - \max(lb,lc) \leq 3 \times n$。

```
#include<iostream>
#include<cstdio>
#define ll long long 
#define N 300005

char a[N],b[N],c[N];
int la,lb,lc;
int n;
int T;

int main(){
	scanf("%d",&T);
	while(T -- ){
		scanf("%d",&n);
		scanf("%s",a + 1);
		scanf("%s",b + 1);
		scanf("%s",c + 1);
		la = lb = lc = 1;
		while(la <= 2 * n && lb <= 2 * n && lc <= 2 * n){
			int to = (a[la] - '0' + b[lb] - '0' + c[lc] - '0');
			to = (to >= 2) ? 1 : 0;
			std::cout<<to;
			if(a[la] == '0' + to)
			la ++ ;
			if(b[lb] == '0' + to)
			lb ++ ;
			if(c[lc] == '0' + to)
			lc ++ ;
		} 
		if(la == 2 * n + 1){
			if(lb > lc)
			for(int i = lb;i <= 2 * n;++i)
			std::cout<<b[i];	
			else
			for(int i = lc;i <= 2 * n;++i)
			std::cout<<c[i];	
		}
		if(lb == 2 * n + 1){
			if(la > lc)
			for(int i = la;i <= 2 * n;++i)
			std::cout<<a[i];	
			else
			for(int i = lc;i <= 2 * n;++i)
			std::cout<<c[i];
		}
		if(lc == 2 * n + 1){
			if(lb > la)
			for(int i = lb;i <= 2 * n;++i)
			std::cout<<b[i];	
			else
			for(int i = la;i <= 2 * n;++i)
			std::cout<<a[i];
		}				
		puts("");
	}
}
```

---

## 作者：RedreamMer (赞：2)

[$\huge\texttt{CF1508A}$](https://www.luogu.com.cn/problem/CF1508A)

update 2021/04/19：修改了链接，和重新提交（交错了题目/fad）

标签：构造

## 题意

给定三个长为 $2n$ 的 $01$ 串，要求构造一个最多长为 $3n$ 的 $01$ 串，要求至少有两个给定的 $01$ 串是你构造的串的子序列。

## 思路

考虑为什么题目给了三个串，以及为什么长度上限是 $3n$。

因为你暴力构造两个串的最短母串显然是 $4n$ 的，考虑消去了 $n$ 个哪些东西使长度变成了 $3n$，正好发现 $n$ 是 $2n$ 的一半。

随即就有了一个构造方法，对于一个长为 $2n$ 的 $01$ 串必有 $0$ 或 $1$ 的数码个数不小于 $n$，而三个串必有两个串不小于 $n$ 的数码相同，因此，找到这两个串，把它们相同的数码直接合并一起，长度至少少了 $n$，剩下的暴力合并都没关系，长度必然小于 $3n$。

## 代码

省去了冗杂的码头。

```cpp
int t, a;
vector<int> vis[2];
char s[3][N];

inline void calc(int n, int m, char ch) {
    int i = 1, j = 1;
    while (1) {
        if (s[n][i] == s[m][j]) printf("%c", s[n][i]);
        else if (s[n][i] == ch) {
            while (j <= 2 * a && s[m][j] != ch) printf("%c", s[m][j]), j++;
            printf("%c", ch);
        }
        else {
            while (i <= 2 * a && s[n][i] != ch) printf("%c", s[n][i]), i++;
            printf("%c", ch);
        }
        i++;
        j++;
        if (i > 2 * a || j > 2 * a) break;
    }
    while (i <= 2 * a) printf("%c", s[n][i]), i++;
    while (j <= 2 * a) printf("%c", s[m][j]), j++;
    puts("");
}

signed main() {
    // freopen("in1.in", "r", stdin);
    t = read();
    while (t--) {
        vis[0].clear();
        vis[1].clear();
        a = read();
        rep(i, 0, 2) scanf("%s", s[i] + 1);
        rep(i, 0, 2) {
            int sum = 0;
            rep(j, 1, 2 * a) sum += (s[i][j] == '1');
            vis[sum >= a].PB(i);
        }
        if (siz(vis[0]) >= 2) calc(vis[0][0], vis[0][1], '0');
        else calc(vis[1][0], vis[1][1], '1');
    }
    return 0;
}
```

---

## 作者：封禁用户 (赞：1)

[更好的阅读体验](https://www.doittomorrow.xyz/post/cf1508a-binary-literature-de-ti-jie/)

我们定义 $1$ 的数量**大于等于** $n$ 的字符串为 $1$ 串，反之为 $0$ 串。

那么显然有性质每一个字符串肯定都至少是这两种串中的一种，那么根据鸽巢原理在题目给定的 $3$ 个串中，注定有 $2$ 个串的类别是一样的。

不妨设这两个字符串分别是 $a,b$，他们都是 $1$ 串，那么通过以下方式进行构造就一定可以构造出一个合法的方案：

1. 维护两个指针 $p1,p2$，分别指向 $a,b$ 两个数组中 $1$ 的位置。

2. 如果 $a_{p1}=b_{p2}$，那么输出 $a_{p1}$ 接着将 $p1,p2$ 分别加 $1$。

4. 如果 $a_{p1}\ne b_{p1}\wedge a_{p1}=1$，那么输出 $b_{p2}$ 并将 $p2$ 加 $1$。

5. 如果 $a_{p1}\ne b_{p2}\wedge b_{p2}=1$，那么输出 $a_{p1}$ 并将 $p1$ 加 $1$。

6. 如果 $p1=n$ 或者 $p2=n$，那么将不为 $n$ 的指针之后的所有对应的字符输出。

容易理解 $s1$ 和 $s2$ 都是上面构造出的字符出的字串，接下来考虑证明使用上面的方法构造的字符串长度是否在 $3n$ 之内。

容易得到除 $1$ 之外的操作都不会使输出的字符串比直接将两个字符串直接拼接起来段，所以真正的长度就是 $4n-\text{the number of action 1}$。

因为在 $2,3,4$ 中都不会有 $1$ 输出，所以 $1$ 的输出只在操作 $1,5$ 中。因为 $s1,s2$ 两串中至少有 $n$ 个 $1$，所以因为 $s1_{p1}=s2_{p2}=1$ 而执行的 $1$ 的操作至少有 $n$ 次，那么长度就一定小于 $3n$。

另外提供一个很短的代码实现：

```c++
#include<iostream>
using namespace std;
const int N=2e5+5;
int n,a0,a1,b0,b1,c0,c1,f;
char a[N],b[N],c[N];
void sswap(char a[],char b[]){
    for(int i=1;i<=n*2;i++) swap(a[i],b[i]);
}
void solve(){
	cin>>n,f=0;
	cin>>a+1>>b+1>>c+1;
    a0=a1=b0=b1=c0=c1=0;
	for(int i=1;i<=n*2;i++){
		a0+=a[i]=='0',a1+=a[i]=='1';
		b0+=b[i]=='0',b1+=b[i]=='1';
		c0+=c[i]=='0',c1+=c[i]=='1';
		a[i]-=48,b[i]-=48,c[i]-=48;
	}
    if(a0!=n&&b0!=n){
        if(c0==n) sswap(a,c),swap(a0,c0),swap(a1,c1);
        else if(!((a0>=n)^(c0>=n))) sswap(b,c),swap(b0,c0),swap(b1,c1);
        else if(!((b0>=n)^(c0>=n))) sswap(a,c),swap(a0,c0),swap(a1,c1);
    }
	if(a0<n||b0<n) f=1;
    n<<=1;
    int l=1,r=1;
	while(l<=n&&r<=n){
		if(a[l]==b[r]) cout<<(int)a[l++],r++;
        else if(a[l]!=f) cout<<(int)a[l++];
        else cout<<(int)b[r++];
	}
    for(int i=l;i<=n;i++) cout<<(int)a[i];
    for(int i=r;i<=n;i++) cout<<(int)b[i];
	cout<<'\n';
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;cin>>T;
	while(T--) solve();
	return 0;
}
```

---

## 作者：Cutest_Junior (赞：1)

## 题解 CF1508A 【Binary Literature】

### 题意

+ 给出 $3$ 个长度为 $2\times n$ 的 01 模式串，构造一个长度不超过 $3\times n$ 的 01 串，要求是至少两个模式串是它的子序列，保证有解；
+ $n\le10^5$。

### 做法

先考虑两个长度为 $n$ 的 01 串 $a,b$，最长公共子序列的长度为 $k$，即有两个长度为 $k$ 的 **已知的** 数组 $c,d$，满足$\{a_{c_1},a_{c_2},\dots,a_{c_k}\}=\{b_{d_1},b_{d_2},\dots,b_{d_k}\}$，如何构造最短的 01 串使 $a,b$ 均为其子序列。

可以想到对于任意满足 $0\le i\le k$ 的 $i$，把 $\{b_{d_i+1},b_{d_i+2},\dots,b_{d_{i+1}-1}\}$ 插入到 $a_{c_i}$ 和 $a_{c_{i+1}}$ 之间，这里假设 $c_0=d_0=0,c_{k+1}=c_{k+1}=n+1$。新的 $a$ 即是我们要构造的 01 串，长度为 $n+n-k$。可以证明这是最短的。

但我们一开始并不知道数组 $c,d$，是需要求的。

若两序列最大公共子序列长度为 $k$，新的序列长度为 $4\times n-k$，前面已经证明过。

因为要求答案长度小于 $3\times n$，即 $4\times n-k\le3\times n$，解得 $k\ge n$。

因为保证有答案，我们可以两两求最大公共子序列，当两个序列最大公共子序列的长度大于等于 $n$ 时，就可以构造出答案了。

现在只剩下一个问题，如何求最大公共子序列。

显然可以 dp，但复杂度为 $O(n^2)$。

考场上我想了半个小时，~~所以请读者先想半个小时再往下看。~~

我们发现序列都是 01 串，而且保证有答案。可以猜到至少有两个串各有不少于 $n$ 个的 0 或 1。

反证法：假设任意两个串都不各有不少于 $n$ 个的 0 或 1。若第一个串有 $k_1(k_1\ge n)$ 个 0，那第二个串就有 $k_2(k_2<n)$ 个 0，那么无论第三个串有多少个 0，都和前两个串中的一个各有不少于 $n$ 个的 0 或 1（若 $k_3\ge n$，则和第一个串各有不少于 $n$ 个的 0，若 $k_3<n$，则和第二个串各有不少于 $n$ 个的 1。）。与假设不符。

知道这个结论，做法就不难了。

### 代码

```cpp
#include <cstdio>
#include <cstring>

using namespace std;

const int N = 5e5 + 5;

char s[3][N];

int cnt[3];

int n;

bool flag[2][N];

void run(int a, int b, bool x) {
//	printf("%d %d %d\n", a, b, x);
	int c = 0;
	for (int i = 0; i < n + n; ++i) {
		if (c < n && s[a][i] - '0' == x) {
			flag[0][i] = 1;
			++c;
		}
		else {
			flag[0][i] = 0;
		}
//		printf("%d ", flag[0][i]);
	}
	c = 0;
	for (int i = 0; i < n + n; ++i) {
		if (c < n && s[b][i] - '0' == x) {
			flag[1][i] = 1;
			++c;
		}
		else {
			flag[1][i] = 0;
		}
//		printf("%d ", flag[1][i]);
	}
	int i = 0, j = 0;
	while (i < n + n || j < n + n) {
		while (i < n + n && !flag[0][i]) {
			printf("%d", s[a][i] - '0');
			++i;
		}
		while (j < n + n && !flag[1][j]) {
			printf("%d", s[b][j] - '0');
			++j;
		}
		if (j < n + n || i < n + n)
		printf("%d", x);
		++i;
		++j;
	}
	printf("\n");
}

void solve() {
	memset(cnt, 0, sizeof cnt);
	scanf("%d", &n);
	int c = 0;
	for (int i = 0; i < 3; ++i) {
		scanf("%s", s[i]);
		for (int j = 0; j < n + n; ++j) {
			cnt[i] += s[i][j] - '0';
		}
		if (cnt[i] >= n) {
			++c;
		}
	}
	if (c >= 2) {
		if (cnt[0] >= n) {
			if (cnt[1] >= n) {
				run(0, 1, 1);
			}
			else {
				run(0, 2, 1);
			}
		}
		else {
			run(1, 2, 1);
		}
	}
	else {
		if (cnt[0] <= n) {
			if (cnt[1] <= n) {
				run(0, 1, 0);
			}
			else {
				run(0, 2, 0);
			}
		}
		else {
			run(1, 2, 0);
		}
	}
}

int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		solve();
	}
}
```

---

## 作者：氧少Kevin (赞：0)

# CF1509D - Binary Literature
- https://www.luogu.com.cn/problem/CF1508A
- 鸽巢原理、构造

## 题意
给出整数 $n(1\leq n\leq 10^5)$ 和三个长度均为 $2\cdot n$ 的 01 串，

需要构造出一个长度不超过 $3\cdot n$ 的 01 串，

满足：给出的三个 01 串中的至少两个是构造的 01 串的子序列。

## 思路

观察到，构造的 01 串长度不超过 $3\cdot n$，$3\cdot n = 2\cdot n+n$。

考虑在某个给出的 01 串插入不超过 $n$ 个字符，来构造答案。

对于一个 01 串而言，观察到：

- 如果 $0$ 的数量 $\geq$ $1$ 的数量，那么 $0$ 的数量 $\geq n$，$1$ 的数量 $\leq n$；
- 如果 $1$ 的数量 $\geq$ $0$ 的数量，那么 $1$ 的数量 $\geq n$，$0$ 的数量 $\leq n$。

那么，我们可以这么做：
- 找到两个 $0$ 数量较多的 01 串，将其中一个 01 串的 $1$ 穿插到另一个 01 串即可；
- 找到两个 $1$ 数量较多的 01 串，将其中一个 01 串的 $0$ 穿插到另一个 01 串即可。

不难发现，由鸽巢原理，上述两个做法至少有一个能做到。

---

## 作者：Little09 (赞：0)

这里把大于等于一半称为过半。

每个串 $0$ 或 $1$ 的个数过半。鸽巢原理（抽屉原理）可知，在三个串中，一定能找到两个串的 $0$ 的个数过半或 $1$ 的个数过半。

假设它们的 $0$ 的个数过半。我们只要把这两个串拼在一起就可以了。把 $0$ 保留下来，把两个串的 $1$ 插到空里去，显然长度是小于等于 $3n$ 的。注意代码细节。

代码片段给的是拼接的过程。写得比较丑。

```cpp
void print(int x,int y,int t)
{
	if (num[x][t]<num[y][t]) swap(x,y);
	char tt=t+'0';
	int j=0;
	for (int i=1;i<=2*n;i++)
	{
		if (a[x][i]==tt)
		{
			while (j<2*n) 
			{
				++j;
				if (a[y][j]!=tt) cout << a[y][j];
				else break;
			}
			cout << tt;
		}
		else cout << a[x][i];
	}
	while (j<2*n) 
	{
		++j;
		cout << a[y][j];
	}
} 

// x,y是要拼接的两个串，t是0或1表示保留的数字
```


---

## 作者：PPL_ (赞：0)

# 前言

练习赛的时候降智写了一车面包锅，赛后一写就过。

# 题目

[洛谷](https://www.luogu.com.cn/problem/CF1508A)

[CF](http://codeforces.com/problemset/problem/1508/A)

题目大意：

给定一个正整数 $n$，接着输入三个长度为 $2n$ 的01字符串，要求构造一个长度不超过 $3n$ 的字符串使得至少给定的两个串为你构造的串的**子序列**。

多组数据，$\sum n\le 10^5$。

# 讲解

其实这道题还是比较好想的。

我们发现如果其中两个串的最长公共子序列能够达到 $n$，那么我们将剩下的都按对应的位置插入进去，就可以构造出合法解。

根据**鸽巢原理**可知一个长度为 $2n$ 的01字符串，一定会使得0或1达到半数。

而题目给了三个串，那么一定会有两个串使得0或1都达到半数，随便写写就好。

注意数组不要开小了。

# 代码

~~又丑又长。~~

```cpp
bool check(int x,int y)
{
	int cnt1 = 0,cnt2 = 0;
	for(int i = 1;i <= 2*n;++ i) 
	{
		if(a[x][i] == '0') cnt1++;
		if(a[y][i] == '0') cnt2++;
	}
	if(cnt1 >= n && cnt2 >= n)
	{
		int MIN = Min(cnt1,cnt2),now1 = 1,now2 = 1;
		for(int i = 1;i <= MIN;++ i)
		{
			while(a[x][now1] != '0') putchar(a[x][now1]),now1++;
			while(a[y][now2] != '0') putchar(a[y][now2]),now2++;
			putchar('0');
			now1++;
			now2++;
		}
		for(int i = now1;i <= 2*n;++ i) putchar(a[x][i]);
		for(int i = now2;i <= 2*n;++ i) putchar(a[y][i]);
		putchar('\n');
		return 1;
	}
	cnt1 = 2*n - cnt1; cnt2 = 2*n - cnt2;//1的个数
	if(cnt1 >= n && cnt2 >= n) 
	{
		int MIN = Min(cnt1,cnt2),now1 = 1,now2 = 1;;
		for(int i = 1;i <= MIN;++ i)
		{
			while(a[x][now1] != '1') putchar(a[x][now1]),now1++;
			while(a[y][now2] != '1') putchar(a[y][now2]),now2++;
			putchar('1');
			now1++;
			now2++;
		}
		for(int i = now1;i <= 2*n;++ i) putchar(a[x][i]);
		for(int i = now2;i <= 2*n;++ i) putchar(a[y][i]);
		putchar('\n');
		return 1;
	}
	return 0;
}

int main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	for(int T = Read(); T ;-- T)
	{
		n = Read();
		for(int i = 0;i < 3;++ i) scanf("%s",a[i]+1);
		bool f = 1;
		for(int i = 0;i < 3 && f;++ i)//其实不需要这么多次
			for(int j = 0;j < 3 && f;++ j)
				if(i != j && check(i,j))
					f = 0;
	}
	return 0;
}
```

---

