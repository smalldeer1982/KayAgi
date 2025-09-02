# Fun Game

## 题目描述

### 题目大意

Vanya 有一个 01 串 $s=s_1s_2\dots s_n$。他可以对 $s$ 进行一系列变换。每次变换中，Vanya 会取两个整数 $l,r\left(1\le l\le r\le n\right)$，然后对所有 $i\in\left[l,r\right]$，将 $s_i$ **同时**替换为 $s_i\oplus s_{i-L+1}$，其中 $\oplus$ 表示按位异或。

Vanya 想知道 $s$ 能否经过一系列变换，得到另一个长度与 $s$ 相同的 01 串 $t$。

## 样例 #1

### 输入

```
6
1
0
1
7
0110100
0110100
9
100101010
101111110
4
0011
1011
4
0100
0001
8
10110111
01100000```

### 输出

```
NO
YES
YES
NO
YES
YES```

# 题解

## 作者：Little_Cabbage (赞：1)

> 涉及知识点：异或，字符串处理。

# 解题思路

> ‌异或是一种二进制运算，用于比较两个数字的差异。 当两个输入不同时，异或运算的结果为1；当两个输入相同时，结果为0。

现在就可以切掉本题了。

设两个字符串分别为 $a$，$b$。

1. 如果 $a$ 和 $b$ 完全相同，输出 `Yes`。
2. 如果 $a$ 中没有 $1$ 且 $b$ 中没有 $1$，输出 `Yes`。
3. 如果 $a$ 中没有 $1$ 且 $b$ 中有 $1$，输出 `No`。
4. 如果 $a$ 中出现 $1$ 的第 $1$ 个位置比 $b$ 中出现 $1$ 的位置靠前，输出 `No`。
5. 其他情况输出 `Yes`。

# 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define ll __int128
#define db double
#define ldb long double
#define vo void
#define endl '\n'
#define il inline
#define re register
#define ve vector
#define p_q priority_queue
using namespace std;

//#define O2 1
#ifdef O2
#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3, "Ofast", "inline")
#endif

namespace OI {
	template <typename T>
	il T read() {
		T x = 0, f = 1;
		int ch = getchar();
		while (!isdigit(ch)) {
			if (ch == '-') f = -1;
			ch = getchar();
		}
		while (isdigit(ch)) {
			x = (x << 3) + (x << 1) + (ch ^ 48);
			ch = getchar();
		}
		return x * f;
	}
	template <typename TE>
	il void write(TE x) {
		if (x < 0) {
			x = -x;
			putchar('-');
		}
		TE sta[35];
		int top = 0;
		do {
			sta[top++] = x % 10, x /= 10;
		} while (x);
		while (top) putchar(sta[--top] + '0');
	}
	il string read_with_string() {
		string s = "";
		char ch = getchar();
		while ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9')) {
			s += ch;
			ch = getchar();
		}
		return s;
	}
	il void write_with_string(string s) {
		for (int i = 0; i < s.size(); i ++ ) putchar(s[i]);
	}
}
namespace COMB {
	int fact[200000];
	int Triangle[1010][1010];
	void Fact(int n, int mod) {
		fact[0] = 1;
		for (int i = 1; i <= n; i ++ ) fact[i] = ((fact[i - 1]) % mod * (i % mod)) % mod;
	}
	void Pascal_s_triangle(int n, int mod) {
		for (int i = 0; i <= n; i ++ ) Triangle[i][0] = 1;
		for (int i = 1; i <= n; i ++ )
			for (int j = 1; j <= i; j ++ )
				Triangle[i][j] = (Triangle[i - 1][j] + Triangle[i - 1][j - 1]) % mod;
	}
	int pw(int x, int y, int mod) {
		int res = 1;
		while (y) {
			if (y & 1) res = ((res % mod) * (x % mod)) % mod;
			x = (x % mod) * (x % mod) % mod;
			y >>= 1;
		}
		return res;
	}
	int pw(int x, int y) {
		int res = 1;
		while (y) {
			if (y & 1) res *= x;
			x *= x;
			y >>= 1;
		}
	}
	int GCD(int x, int y, int mod) {
		return __gcd(x, y) % mod;
	}
	int LCM(int x, int y, int mod) {
		return (((x % mod) * (y % mod)) % mod / (GCD(x, y, mod) % mod)) % mod;
	}
	int C(int n, int m, int mod) {
		if (m > n || m < 0) return 0;
		return fact[n] * pw(fact[m], mod - 2, mod) % mod * pw(fact[n - m], mod - 2, mod) % mod;
	}
	int Ask_triangle(int x, int y) {
		return Triangle[x][y];
	}
}
using namespace OI;
using namespace COMB;

//#define fre 1
#define IOS 1
#define multitest 1

const int N = 2e5 + 10;
const int M = 4e5 + 10;
const int inf = 1e12;

string a, b;
int n;


il void Init() {
	cin >> n;
	cin >> a >> b;
}

il void Solve() {
	if (a == b) {
		cout << "Yes\n";
		return ;
	}
	int x = a.find("1");
	int y = b.find("1");
	if (x == -1 && y == -1) {
		cout << "Yes\n";
		return ;
	} else if (x == -1) {
		cout << "No\n";
		return ;
	} else {
		int cnt = 0;
		for (int i = 0; i < n; i ++ ) {
			if (a[i] == '1') cnt++;
			if (b[i] == '1' && !cnt) {
				cout << "No\n";
				return ;
			}
		}
		cout << "Yes\n";
	}
}
signed main() {
	int T;
#ifdef IOS
	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
#endif
#ifdef fre
	freopen(".in", "r", stdin);
	freopen(".out", "w", stdout);
#endif
#ifdef multitest
	cin >> T;
#else
	T = 1;
#endif
	while (T--) {
		Init();
		Solve();
	}
	return 0;
}
/*

*/
```

---

## 作者：a_girl (赞：1)

[CF1994B Fun Game](https://www.luogu.com.cn/problem/CF1994B)

## 思路
首先我们先看异或是什么，异或是两个数转为二进制，两个值每个位判断，如果两个值不相同，则异或结果为 $1$。如果两个值相同，异或结果为 $0$。

我们看题目，因为可以操作无数次，所以我们只要一个一个考虑每个字符就可以了。

如果 $s2_i$ 是 $0$，那么就要变成 $1$，那么 $s1$ 前面就一定有一个 $1$，因为 $0$ 异或 $1$ 是 $1$，如果 $s2_i$ 是 $1$，那么就要变成 $0$，那么 $s1$ 前面就一定有一个 $1$，因为 $1$ 异或 $1$ 是 $0$，所以我们只要看这个数之前有没有 $1$ 就行了。

## 代码
```cpp
#include<bits/stdc++.h>万能头 
using namespace std;
int t;
int main()
{
	cin>>t;
	while(t--)//多组数据 
	{
		int n;
		string s1,s2;
		cin>>n>>s1>>s2;//输入 
		int sum=0,flag=1;
		for(int i=0;i<s1.size();i++)//每个字符去找 
		{
			if(s1[i]=='1') sum=1;
			if(s2[i]=='1'&&sum==0)
			{
				flag=0;
				cout<<"No\n";//不满足要求，输出错误 
				break;
			}
		}
		if(flag) cout<<"Yes\n";//满足要求，输出正确 
	}
	return 0;谢谢观看 
}
```

---

## 作者：d909RCA (赞：0)

### 0x00 前言

赛时没调出来。~~经过@[oier03](/user/730195)指点后秒切。~~

---
### 0x01 前置芝士

- 字符串遍历

---
### 0x02 思路

首先找到字符串 $s$ 中第一次出现 $1$ 的下标 $k$。然后判断在 $[0,k)$ 的区间里是否有 $1$ 就行了，因为若无任何 $1$ 那么可以证明对于 $[k,\text{size}]$ 总是合法。

---
### 0x03 Code

```
#include <bits/stdc++.h>
using namespace std;
signed main()
{
	int n;
	cin>>n;
	while(n--)
	{
		string s,t;
		int flag=0,k=-1,sz;
		cin>>sz;
		cin>>s>>t;
		for(int i=0;s[i]=='0';i++)
		{
			k=i;
		}
		for(int i=0;i<=k;i++)
		{
			if(t[i]=='1')
			{
				cout<<"No\n";
				flag=1;
				break ;
			}
		}
		if(!flag) cout<<"Yes\n";
	}
	return 0;
}
```

---

---

## 作者：yangduan_ (赞：0)

## 思路
先标记出字符串 $s$ 第一次出现 $1$ 的位置 $x$，再找出 $s$ 和 $t$ 两个字符串中第一次出现不同时的位置 $y$，最后判断字符串 $s$ 中 $y$ 位置之前是否出现 $1$ 即可。
# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define N 200010
int t,l,x[N],y[N],cnt[N];
char a[N],b[N];
int main(){
	int i,j;
	cin>>t;
	while(t--){
		cin>>l;
		cin>>(a+1)>>(b+1);
		for(i=1;i<=l;i++){
			x[i]=a[i]-'0';
			y[i]=b[i]-'0';
			cnt[i]=cnt[i-1];
			if(x[i]==1){
				cnt[i]=1;
			}
		}
		for(i=1;i<=l;i++){
			if(x[i]!=y[i]){
				if(!cnt[i]){
					cout<<"NO"<<endl;
					goto yd;
				}
			}
		}
		cout<<"YES"<<endl;
		yd:;
	}
	return 0;
}
```

---

## 作者：YuYuanPQ (赞：0)

题目问能不能通过任意次操作，把序列 $s$ 变成 $t$。

我们找一下 [XOR]((https://en.wikipedia.org/wiki/Bitwise_operation#XOR))（$\oplus$） 运算的规律，总结起来就是：

> $2$ 个数相同为 $0$，不同为 $1$。

对于每个 $i$ 来说，只有前面 $s_1 \sim s_{i-1}$ 的值与它有关。

考虑一下分类讨论（这里只考虑 $2$ 个序列中不同的情况）：

- $s$ 中为 $0$，要想变成 $1$，需要 $1$。

- $s$ 中为 $1$，要想变成 $0$，还是需要 $1$。

因此可以得出结论：对于每个 $i$ 来说，当 $s_1 \sim s_{i-1}$ 中有 $1$ 时，即为“有趣的”，否则为“无趣的”。
## Code

[Link](https://codeforces.com/contest/1994/submission/271247426)

---

## 作者：zxy1919810 (赞：0)

# CF1994B Fun Game 题解
## 思路
发现：

1. 若二进制字符串 $s$ 中的第 $i$ 个字符是 $1$，则可以将第 $i+1$ 个字符和它之后的字符都随意更改。
2. 若字符串 $s$ 的第 $i$ 个字符前面没有字符 $1$，则它无法被更改。

所以只需要先找到字符串 $s$ 中第一个 $1$ 的位置，再在字符串 $t$ 中寻找这个位置之前有没有 $1$。如果有，那么 $s$ 就不能变成 $t$。
## code
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t,n,m;
	string s1,s2;
	cin>>t;
	while(t--){
		cin>>n>>s1>>s2;
		bool flag=0;
		n=s1.find("1");  //找1
		m=s2.find("1");  //找1
		if(n==-1&&n==m)cout<<"YES";  //两个字符串全是0，输出yes
		else if(n==-1)cout<<"NO";   //s没有1，但是t有，输出no
		else{
			for(int i=0;i<n;i++)if(s2[i]=='1'){flag=1;cout<<"NO";break;}  //若字符串t在 字符串s的第一个1以前的位置 有1，则输出no
			if(flag==0)cout<<"YES";  //否则输出yes
		}
		cout<<endl;
	}
    return 0;
}
```

---

## 作者：__DayLight__ (赞：0)

## 前言

[原题机翻。](https://www.luogu.com.cn/article/e1ybyywp)

## 思路

先来问度娘什么是**异或**：
>如果 $a$、$b$ 两个值不相同，则异或结果为 $1$。如果 $a$、$b$ 两个值相同，异或结果为 $0$。

通俗易懂，接下来回到题目。

由于不限制操作次数，所以不需要考虑一整段子串，只需考虑单独的 $s_i$ 即可，而能参与操作的只有 $s_1$ $\sim$ $s_i$。

运用到题目中则有：

1. 若 $s_i$ 为 $0$，要变成 $1$，那么 $s_1$ $\sim$ $s_i$ 中肯定要有 $1$，因为 $0 \oplus 1 =1$。

1. 若 $s_i$ 为 $1$，要变成 $0$，那么 $s_1$ $\sim$ $s_i$ 中**也必须**有 $1$，因为 $1 \oplus 1 =0$，显然，$s_i$ 本身就为 $1$，所以该情况不需要判断。

综上所述，只许判断第 $1$ 种情况即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n;
string s,t;
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--)
	{
		cin>>n>>s>>t;
		s=" "+s,t=" "+t;
		int ct=0;//ct 记录 1 的数量。 
		bool f=1;
		for(int i=1; i<=n; i++)
		{
			if(s[i]=='1')ct++;
			if(t[i]=='1'&&!ct)
			{
				f=0;
				break;
			}
		}
		if(f)cout<<"Yes\n";
		else cout<<"No\n";
	}
	return 0;
}
```

---

## 作者：xcms (赞：0)

# CF1994B 题解

这道题肯定不能暴力求解，所以可以找找规律。

假设 $s$ 的第一位就是 $1$，可以发现，所有的 $s_i$ 都可以实现 $0$ 和 $1$ 的互相转变，比如下面的数据。

```
4
1000
1111
```

上面这个数据中，第一次可以选择 $l=2$ 和 $r=2$，$1$ 和 $0$ 进行异或运算后得到 $1$。第二次可以选择 $l=3$ 和 $r=3$，$1$ 和 $0$ 进行异或运算后还是得到 $1$。第三次可以选择 $l=4$ 和 $r=4$，$1$ 和 $0$ 进行异或运算后仍然得到 $1$。按照以上操作之后，就可以得到 $t$。

假设 $s$ 的第一位变成 $0$，第二位变成 $1$，可以通过模拟发现：除了第一位，剩下的 $s_i$ 都可以实现 $0$ 和 $1$ 的互相转变，像下面的数据。

```
4
0100
0111
```

第三位可以通过选择 $l=2$ 和 $r=3$ 来变成 $1$，第四位可以通过选择 $l=3$ 和 $r=4$ 来变成 $1$。然而，不管 $l$ 和 $r$ 等于几，第一位是永远无法变成 $1$，但是 $s$ 和 $t$ 本身第一位就相等，所以 $s$ 还是可以变成 $t$。

按照上面的方式类推下去，就可以总结出下面的规律：所有在 $s$ 从左到右的第一个 $1$ 之后的数字，都可以实现 $0$ 和 $1$ 的互相转变。

有了上面的规律，写起代码就容易多了。

首先判断如果 $s$ 和 $t$ 相等，就可以实现目标。

然后找到 $s$ 的第一个 $1$ 出现的位置。用 $x$ 存下来。

接着判断如果 $s$ 中没有 $1$，就看看 $t$ 中有没有 $1$。如果有则不可以实现目标，否则就可以。

最后枚举 $0$ 到 $x-1$，如果 $t_i$ 是 $1$，则不能实现目标，否则就可以实现。

AC 代码如下。

```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
	int q;
	cin>>q;
	while(q--){
		int n;
		string s,t;
		cin>>n>>s>>t;
		if(s==t){
			cout<<"YES\n";
			continue;
		}
		int x=s.find('1');
		if(x==-1){
			int y=t.find('1');
			if(y==-1)cout<<"YES\n";
			else cout<<"NO\n";
			continue;
		}
		bool k=0;
		for(int i=0;i<x;i++){
			if(t[i]=='1'){
				cout<<"NO\n";
				k=1;
				break;
			}
		}
		if(!k)cout<<"YES\n";
	}
	return 0;
}
```

---

## 作者：MrJC_Pandingding (赞：0)

# 解题思路
设 $s_x$ 是 $s$ 中的第一个 `1`，则此前的字符无法更改。设 $s_y(y>x)$ 需要更改，则让 $s_{y-x+1}\sim s_y$ 与 $s_1\sim s_x$ 异或。如果 $s_x$ 自己需要更改，那么在其他需要更改的字符改完后，让 $s_1\sim s_x$ 与 $s_1\sim s_x$ 异或。

因此，对于每组数据，逐位比较 $s$ 和 $t$ 中的字符，遍历到第一个不相同的位置时，如果 $s$ 中的字符为 `0`，$t$ 中的字符为 `1`，且此前 $s$ 中无 `1`，则输出 `No`，否则输出 `Yes`。
# 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5;
int n,q;
bool f,g;
char s[maxn+10],t[maxn+10];
int main()
{
	int i;
	scanf("%d",&q);
	while(q--)
	{
		scanf("%d%s%s",&n,s,t);
		f=false;
		g=true;
		for(i=0;i<=n-1;++i)
		{
			if(s[i]=='1')
				f=true;
			if(!f&&s[i]=='0'&&t[i]=='1')
				g=false;
		}
		if(g)
			puts("Yes");
		else puts("No");
	}
	return 0;
}
```

---

## 作者：zyn0309 (赞：0)

# CF1994B Fun Game
[题目传送门](https://www.luogu.com.cn/problem/CF1994B)
## 思路
因为 $0 \oplus 1 =1$，$1 \oplus 1 =0$，所以遇到 $s_i \ne t_i$ 时只能将 $s_i \oplus 1$ 才能满足题目条件。只需要从头开始查找，若 $s_i \ne t_i$，则判断当前是否已经出现过 $1$。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int q,n;
string s,t;
int main(){
	cin>>q;
	while(q--){
	  cin>>n>>s>>t;
	  bool f=0,f2=0;
	  for(int i=0;i<n;++i){
	  	if(s[i]=='1')f=1;
	  	if(s[i]!=t[i]&&!f){
	  	  f2=1;
	  	  break;
		}
	  }
	  if(!f2)cout<<"YES"<<endl;
	  else cout<<"NO"<<endl;
	}
	return 0;
}

---

## 作者：Bad_Luck_No_Fun (赞：0)

### 题面描述

给定长度为 $n$ 的 $0/1$ 序列 $A, B$。定义一次操作为选择 $l,r$ 且 $l \le r$ 并将 $s_i$ 替换为 $s_i⊕s_{i−l+1}$ ，判断 $A$ 能否通过有限次操作变为 $b$。

### 思路

这道题的操作略显别扭和奇怪，于是我考虑了一些极端一点的情况。就比如 $l=r$ 的时候，$s_i$ 被赋值为 $s_i⊕s_1$。
如果 $s_1 = 1$，那么我们可以做到单点修改所有的数，答案肯定是 yes。

基于这点的启发，我们开始寻找 $A$ 序列里第一个 $1$ ,记其位置为 $x$。

此时我们构造操作 $(i-x+1,i)$，发现 $s_{i-x+1,i-x+2,...,i}$ 分别异或上了 $s_{1, 2,...x}$。因为 $x$ 是 $A$ 中第一个 $1$ ，所以我们发现了只改一个数的理想操作！

然后我们就把所有可改位置及 $A_{x,x+1,...,n}$ 标注出来，然后判断即可。

### $Code$

```cpp
# include <bits/stdc++.h>
# define int long long
using namespace std;
const int N = 2e5 + 5;
int T, n, m;
char a[N];
char b[N];
bool flag[N];

void solve() {
	cin >> n;
	cin >> a + 1 >> b + 1;
	for (int i = 1; i <= n; i++) {
		flag[i] = 0;
	}
	for (int i = 1; i <= n; i++) {
		if (flag[i - 1])
			flag[i] = 1;
		if (a[i] == '1')
			flag[i] = 1;
	}
	for (int i = 1; i <= n; i++) {
		if (a[i] != b[i] && flag[i] == 0) {
			cout << "No" << endl;
			return;
		}
	}
	cout << "Yes" << endl;
}

signed main() {
	cin >> T;
	while (T--) {
		solve();
	}
	return 0;
}

```

---

## 作者：Special_Tony (赞：0)

# 思路
我们设 $x$ 为第 $1$ 个 $1$ 的位置，则可以使用 $a_1\sim a_x$ 异或 $a_{r-x+1}\sim a_r$ 把 $a_r$ 取反，所以 $a_x\sim a_n$ 都是可以随意改变的，但 $a_1\sim a_{x-1}$ 不行。所以我们只要判断 $b_1\sim b_{x-1}$ 是否全 $0$ 就行。
# 代码
```cpp
# include <bits/stdc++.h>
# define I return
# define AK 0
# define IOI ;
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
int t, n;
string a, b;
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> t;
	while (t --) {
		cin >> n >> a >> b;
		for (int i = 0; i < n; ++ i) {
			if (a[i] == '1')
				break ;
			if (a[i] != b[i])
				goto no;
		}
		cout << "Yes\n";
		continue ;
no:
		cout << "No\n";
	}
	I AK IOI
}
```

---

## 作者：littlebug (赞：0)

## Solution

考虑对于第 $i$ 个位置，只有在 $i$ 之前的位置可以影响 $i$ 的值。又因为异或运算有性质：

- $0 \oplus 0 = 0$
- $0 \oplus 1 = 1$
- $1 \oplus 0 = 1$
- $1 \oplus 1 = 0$

所以 $0$ 即是使位于 $i$ 前面，也无法影响 $i$ 的取值，只有 $1$ 可以。所以我们可以考虑从前往后遍历，如果在 $[1,i)$ 中，$s_1 \sim s_{i-1}$ 都为 $0$，但是 $t_{i}$ 为 $1$，那么 $s_{i}$ 无法变为 $0$，所以无解。否则（即 $s_1 \sim s_{i-1}$ 中有 $1$），可以将操作区间的起点设为 $i$，长度可以使 $i$ 正好可以同 $i$ 之前的那个 $1$ 操作即可。

不过题目只要求我们输出有没有解，所以操作的步骤可以直接省略。

## Code

```cpp
#include<iostream>
#include<cstdio>
#include<bitset>
#define il inline
using namespace std;
const int MAXN=2e5+5;
int n;
bitset <MAXN> s,t;
il void solve()
{
	cin>>n;
	string ss,tt;
	cin>>ss>>tt;
	for(int i=0;i<n;++i) s[i+1]=(ss[i]=='1'),t[i+1]=(tt[i]=='1');
	for(int i=1;i<=n;++i)
	{
		if(s[i]) break;
		if(t[i])
		{
			cout<<"NO\n";
			return;
		}
	}
	cout<<"YES\n";
	return;
}
int main()
{
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--)
		solve();
	return 0;
}
```

---

## 作者：Redshift_Shine (赞：0)

## 2. Fun Game / 橙

给两个 $01$ 序列 $a$ 和 $b$，可以进行无限次操作使 $a_l$ 到 $a_r$ **同时**异或 $a_1$ 到 $a_{r-l+1}$。问将 $a$ 通过操作转换为 $b$ 的可行性。

我看到题目后想，这啥？第二题就上强度啊？

然后我想起了赛前刷的绝区零视频。我突然意识到，可以将 $a$ 和 $b$ 内的前缀零看成“空洞”，因为根据题目的要求，前缀零无论进行多少次操作，长度都不会减小。

而在初始空洞后的所有元素，可以依靠空洞后的第一个 $1$ 修改成任意的样子。

于是问题解决。核心代码一行。时间复杂度 $O(n)$。

```c++
#include <iostream>
#include <string>
using namespace std;
const int N = 1e5 + 10;
int n;
string s, t;
void run()
{
    cin >> n >> s >> t;
    puts(s.find('1') <= t.find('1') ? "YES" : "NO");
}
int main()
{
    int T = 1;
    scanf("%d", &T);
    while (T--)
        run();
}
```

---

## 作者：QingDeng_Star (赞：0)

## 思路
首先我们要知道异或是怎么一回事。

‌异或是一种二进制运算。当 $a$ 和 $b$ 不同时，异或运算的结果为 $1$；当 $a$ 和 $b$ 相同时，结果为 $0$。

这道题可以用分情况讨论的方法来 A 掉它。

$1.$ 如果两个字符串相同，就可以做到。

$2.$ 如果两个字符串中都没有 $1$，也可以做到。

$3.$ 如果其中一个字符串有 $1$，另一个没有，就无法做到。

$4.$ 其余情况都可以做到。

## 上代码

```cpp
#include<bits/stdc++.h>//万能头 
using namespace std;
int main()
{
    ios::sync_with_stdio(0); 
    cin.tie(0); cout.tie(0); 
	int t;
	cin>>t;
	while(t--)
	{
		int n,flag1=0,flag2=1;//两个指标，一个是记录 s1 是否有1，另一个是用来判断的。 
		string s1,s2;
		cin>>n>>s1>>s2;
		for(int i=0;i<s1.size();i++)
		{
			if(s1[i]=='1') 
				flag1=1;//判断s1里是否有1 
			if(s2[i]=='1'&&flag1==0)
			{
				flag2=0;
				cout<<"NO"<<endl;
				break;
			}
		}
		if(flag2==1) 
			cout<<"YES"<<endl;
	}
	return 0;//完结散花！ 
}
```

---

