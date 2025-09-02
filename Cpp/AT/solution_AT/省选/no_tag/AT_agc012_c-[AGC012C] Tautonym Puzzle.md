# [AGC012C] Tautonym Puzzle

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc012/tasks/agc012_c

文字列 $ x $ が以下の条件を満たすとき、$ x $ を *良い文字列* と呼びます。

- 条件：$ x $ はある長さ $ 1 $ 以上の文字列 $ y $ を $ 2 $ 回繰り返した文字列 $ yy $ で表すことができる。

例えば `aa`,`bubobubo` などは良い文字列ですが、空文字列、`a`,`abcabcabc`,`abba` などは良い文字列ではありません。

ワシとフクロウが良い文字列に関するパズルを作りました。 以下の条件を満たす文字列 $ s $ をどれか $ 1 $ つ求めてください。この問題の制約下で、そのような文字列が必ず存在することが証明できます。

- $ 1\ ≦\ |s|\ ≦\ 200 $
- $ s $ は $ 1 $ から $ 100 $ までの整数で表される $ 100 $ 種類の文字のみからなる。
- $ s $ の $ 2^{|s|} $ 個ある部分列のうち、良い文字列であるようなものは $ N $ 個ある。

## 说明/提示

### 制約

- $ 1\ ≦\ N\ ≦\ 10^{12} $

### Sample Explanation 1

$ s $ の部分列であって良い文字列となるようなものは (1,1) と (1,1,1,1) の $ 2 $ 種類があります。(1,1) であるような部分列は $ 6 $ 個、(1,1,1,1) であるような部分列は $ 1 $ 個あるため、合計 $ 7 $ 個です。

## 样例 #1

### 输入

```
7```

### 输出

```
4
1 1 1 1```

## 样例 #2

### 输入

```
299```

### 输出

```
23
32 11 11 73 45 8 11 83 83 8 45 32 32 10 100 73 32 83 45 73 32 11 10```

# 题解

## 作者：louhao088 (赞：13)

一道好的构造题。


------------

由于是子序列相同，只要顺序相同出现两次就可以。

由于最长 200，我们先放前 $100$ 个为 $1 \to 100$。


------------


这样题目就变为，怎样满足 一个序列有 $N$ 个严格上升子序列。

这个很容易构造，我们倒着先摆所有偶数（只要隔两个摆就可以，倒着是为了防止多算）。

结合二进制，如果第 $x$ 位是 $1$ ，那只要放 $x \times 2+1$ 前面必然有 $x$ 个比他小，方案数增加 $2^x$ 次。这样构造必然可以。（这个要从高位到低位）

（至今也没有想通，此题的 spj 是怎么写的）。



------------
```cpp
#include<bits/stdc++.h>
using namespace std;
//static char buf[1000000],*p1=buf,*p2=buf;
//#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
#define re register
#define int long long
const int maxn=1e5+5,M=34005;
inline int read()
{
	char ch=getchar();bool f=0;int x=0;
	for(;!isdigit(ch);ch=getchar())if(ch=='-')f=1;
	for(;isdigit(ch);ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
	if(f==1)x=-x;return x;
}
inline void print(int x)
{
    static int a[55];int top=0;
    if(x<0) putchar('-'),x=-x;
    do{a[top++]=x%10,x/=10;}while(x);
    while(top) putchar(a[--top]+48);
}
int n,m,a[maxn],t=0,b[maxn],ans;
signed main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	n=read();int x=n;
	for(int i=1;i<=100;i++)b[++ans]=i;t=0;
	while(x>=pow(2,t+1)-1ll)t++;
	for(int i=1;i<=t;i++)b[++ans]=i*2;n=n-pow(2,t)+1ll;
	for(int i=t;i>=1;i--)if(n&(1ll<<(i-1)))b[++ans]=i*2-1;
	cout<<ans<<endl;
	for(int i=1;i<=ans;i++)printf("%d ",b[i]);
 	return 0;
}

```


---

## 作者：Kinandra (赞：10)

标签: 构造.

直奔主题, 正解做法: 构造出来的字符串分为前后两部分, 后半部分为 `1 2 ... 99 100` , 前半部分为 $1$  至 $x(x\leqslant 100)$ 的一个排列, 那么好子序列的个数即为前半部分上升子序列个数(后半部分必有一个相同的子序列).

考虑从小到大一个一个增加字符, 放最前面方案数 $+1$, 放最后面方案数 $\times 2$, 发现是一个二进制拆分的过程, 递归一下就好了.

时间复杂度 $O(\log n)$, 代码实现很简单.

```cpp
#include <bits/stdc++.h>
using namespace std;
 
int p[202], q[202], cnt;
long long n;
     
void solve(long long n){
	if (!n) return;
   	if (~n & 1) 
		q[++q[0]] = cnt++, solve(n - 1);
   	else
   		p[++p[0]] = cnt++, solve(n >> 1);
}
    
int main(){
  	scanf("%lld", &n), solve(n), printf("%d\n", cnt + 100);
  	for (int i = 1; i <= q[0]; ++i) printf("%d ", cnt - q[i]);
  	for (int i = p[0]; i; --i) printf("%d ", cnt - p[i]);
   	for (int i = 1; i <= 100; ++i) printf("%d ", i);
 	return 0;
}

```



---

## 作者：10circle (赞：7)

以下内容中“字符串”和“序列”含义相同，“答案”和“子序列个数”含义相同。

### 题意

给定 $n$，构造字符串 $s$，使 $s$ 中能表示为某个串复制两份的子序列恰有 $n$ 个。$1\le n \le 10^{12}, 1\le |s| \le 200$。解必然存在。

### 思路

看到构造题，数据范围又这么神秘，直觉告诉我这和其它一些乱搞题（如 [UR #6 智商锁](https://uoj.ac/problem/75)）类似，都是先处理出什么东西再构造。于是尝试处理些东西。

然后发现，当左侧与右侧互相之间没有相同字符时，符合条件的子序列个数就是左侧的加上右侧的。于是考虑预处理一些串和它们的子序列个数，并将 $n$ 分解为这些数的和。

### Part 1 计算某个串合法子序列个数

这个还是有些必要讲的。~~听说有人不会写这题 spj？~~

考虑枚举复制后右侧的第一个字符的位置，然后设 dp 状态 $dp_{i,j}$ 表示左侧最后一个字符在 $i$ 处，右侧最后一个字符在 $j$ 处的方案数，显然可以四次方做一遍，算上枚举就是五次方。不过可以使用前缀和优化，这样做一遍就是平方的，总复杂度是串长的三次方。

注意如果方案数很大（大于 $n$ 的上界）就可以直接返回不可行。

代码（注意代码中是枚举的右侧第一个字符的左侧一位）：

```cpp
typedef long long ll;
const int N=205;
const ll INF = 1e12;
ll dp[N][N];

ll calc(const vector<int> &a) {
	ll ans = 0; 
	int n = a.size();
	for (int i = 0; i + 1 < n; i++) {
		for (int j = 0; j <= i; j++) memset(dp[j], 0, n * 8);
		for (int j = 0; j <= i; j++) if (a[i + 1] == a[j]) dp[j][i + 1] = 1;
		for (int l = 0; l <= i; l++) {
			for (int r = i + 1; r < n; r++) {
				if (a[l] == a[r] && l) {
					dp[l][r] += dp[l - 1][r - 1];
				}
				dp[l][r] += dp[l][r - 1];
				if (l) dp[l][r] += dp[l - 1][r] - dp[l - 1][r - 1];
				if (dp[l][r] > INF) return -1;
			}
		}
		ans += dp[i][n - 1];
		if (ans > INF) return -1;
	}
	return ans;
}
```

### Part 2 处理哪些序列

这个应该有很多种做法，我就稍微讲一下我的。

首先发现，全部相同的序列无法在限制内构造出 $n$。分析原因，发现是每次使 $n$ 减小时减小的不够多。因此考虑多处理些序列，让答案分布的比较近。

之后实际测试得到，仅有两种字符的串就已经很均匀了，也能发现在串长为 $53$ 左右时答案就在 $10^{12}$ 左右。因此从小到大枚举串长，每个串长随机大约 $800$ 个串并计算答案，如果答案没出现过就扔进 map 里。这样可以在 1s 左右跑完预处理。

代码：

```cpp
mt19937 rnd(20220921);
for (int n = 2; n <= 53; ++n) {
	vector <int> a(n, 0);
	int lim = 800;
	for (int r = 0; r < lim; r++) {
		for (int i = 0; i < n; i++) a[i] = rnd() & 1;
		ll k = calc(a);
		if (k == -1) continue;
		if (mp.find(k) == mp.end()) {
			mp[k]=a;
		}
	}
}
```

### Part 3 构造序列

之后对于某个 $n$，找到答案离它最近且小于它的某个序列，并加入到最终序列中。实际测试中我没有发现构造序列长于 $170$ 的 $n$，然后这题就做完了。

代码就不放了，很简单。

### 题外话

还是太菜，只会实际测试，根本不会分析错误概率。但这题既然范围这么宽，乱搞解法也是好的（）

官方题解怎么构造序列长 $80$ 就够。完了真的被吊打了。


---

## 作者：Creeper_l (赞：4)

原题链接：[Tautonym Puzzle](https://www.luogu.com.cn/problem/AT_agc012_c)

##  前言

这道题是一道很有趣的构造题。我认为这道题的重点在于对题目要求的转化与转化过程中细节的处理。（有些细节问题也困惑了我很久）。

## 题意

构造一个字符串 $S$ ，使 $S$ 的所有子序列中，恰好有 $N$ 个好串。

- 好串：一个字符串能分成两个相同的字符串。

## 思路

我们可以构造一个形如 $X$ 的字符串，满足：

- 前一半为 $1$ 到 $num$ 的一种排列

- 后一半为 $1$ 到 $num$ 的**升序或降序**排列

显然，题目要求前一半的**上升/下降**子序列的数量为 $N$。

如何构造？我们拿后半段为升序排列来举例。

假设我们从小到大枚举字符，那么可以发现：

- 当前字符如果放最前面，那么总方案数会 $+1$。

- 放最后面，**方案数 $×2$ 或方案数 $×2+1$**。

为什么有两种呢？这就是本题的重点了。

其实两种写法的区别在于对**空串**的计算。

第一种是先把空串加上，后面每次就不用计算空串的情况了。

第二种是先不加上空串，后面每次都考虑空串。

只要理解到这一点，本题思路就很清晰了。

## 总结

因为这道题可以升序或降序，先加空串或后加空串，所以共有四种写法。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 1e3 + 10;	
int n, cnt1, cnt2, a[MAXN], b[MAXN], num = 101; 
signed main()
{
	cin >> n; n++;
	while (n > 1) {
		if (n & 1) a[++cnt1] = --num, n = n - 1;
		else b[++cnt2] = --num, n = n / 2;
	}
	cout << (100 - num + 1) * 2 << endl;
	for (int i = 1; i <= cnt1; i++) cout << a[i] << " ";
	for (int i = cnt2; i >= 1; i--) cout << b[i] << " ";
	for (int i = num ;i <= 100; i++) cout << i << " ";
    return 0;
}
```

	
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e3 + 10;	
int n, cnt1, cnt2, a[MAXN], b[MAXN], num = 101; 
signed main()
{
	cin >> n; 
	while (n >= 1) {
		if (n & 1) a[++cnt1] = --num, n = (n - 1) / 2;
		else b[++cnt2] = --num, n = n - 1;
	}
	cout << (100 - num + 1) * 2 << endl;
	for (int i = 1; i <= cnt2; i++) cout << b[i] << " ";
	for (int i = cnt1; i >= 1; i--) cout << a[i] << " ";
	for (int i = num ;i <= 100; i++) cout << i << " ";
    return 0;
}
```

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 1e3 + 10;	
int n, cnt1, cnt2, a[MAXN], b[MAXN], num = 0; 
signed main()
{
	cin >> n; n++;
	while (n > 1) {
		if (n & 1) a[++cnt1] = ++num, n = n - 1;
		else b[++cnt2] = ++num, n = n / 2;
	}
	cout << num * 2 << endl;
	for (int i = 1; i <= cnt1; i++) cout << a[i] << " ";
	for (int i = cnt2; i >= 1; i--) cout << b[i] << " ";
	for (int i = num ;i >= 1; i--) cout << i << " ";
    return 0;
}
```

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 1e3 + 10;	
int n, cnt1, cnt2, a[MAXN], b[MAXN], num = 0; 
signed main()
{
	cin >> n; 
	while (n >= 1) {
		if (n & 1) a[++cnt1] = ++num, n = (n - 1) / 2;
		else b[++cnt2] = ++num, n = n - 1;
	}
	cout << num * 2 << endl;
	for (int i = 1; i <= cnt2; i++) cout << b[i] << " ";
	for (int i = cnt1; i >= 1; i--) cout << a[i] << " ";
	for (int i = num ;i >= 1; i--) cout << i << " ";
    return 0;
}
```


---

## 作者：spider_oyster (赞：3)

空间复杂度优秀做法。

受大神 Caiest_oier 启发。

最简单的情况莫过于 $n \leq 100$，直接填 $1 \sim n$ 再 $n \sim 1$。

思考后发现可以保留前面的 $1 \sim 100$，然后后面就构造上升子序列。

前面包括值域 $[1,100]$ 所有上升子序列，故后面上升子序列个数就是好的序列的个数。

我的构造方法：
 
- 先修个地基，就是直接填 $1 \sim x$，可以发现第 $i$ 个数贡献是 $2^{i-1}$，直到 $\sum\limits_{i=1}^{x+1} 2^{i-1}>n$。
- 修完地基你会发现，在第 $i$ 个数前插入一个比后面所有数大的数贡献也是 $2^{i-1}$。
- 令 $n$ 减去修地基的贡献后二进制拆分就可以了。

时间复杂度 $O(\log_2 n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

main()
{
    int n;cin>>n;
    int mx,now,cnt=0,top=100;
    for(mx=1,now=0;now+(1ll<<mx-1)<=n;now+=(1ll<<mx-1),mx++);//修地基
    mx-=1,n-=now;
    vector<int> c(41);
    for(int i=40;~i;i--) if(n>=1ll<<i) n-=1ll<<i,cnt++,c[i]=1;//二进制拆分
    cout<<100+mx+cnt<<'\n';
    for(int i=1;i<=100;i++) cout<<i<<' ';
    for(int i=1;i<=n;i++) cout<<i<<' ';
    for(int i=1;i<=mx;i++)
    {
        if(c[i-1]) cout<<top--<<' ';
        cout<<i<<' ';
    }
}
```

---

## 作者：Hyscere (赞：2)

## 题目大意

我们称一个字符串$x$是好的当且仅当它满足一下条件：

- $x$可以被表示为另外一个串$y$复制一遍得到，即$x=\overline {yy}$。

举个例子：`'aa'`和`'bubobubo'`是好的，`'a'`,`'abcabcabc'`和`'abba'`不是。

现在要求一个串$s$满足下列条件，可以证明这个串存在：

- $|s|\leqslant 200$

- 字符集大小为$100$，即每个字符用$[1,100]​$的整数表示。

- 在$s$的所有的$2^{|s|}$个子序列中，恰好有$N$个串是好的，其中$N​$是给出的。

## Solution

构造题...窝太菜了想不出来...

一开始想搞一个二进制拆分，一段一段的分，每段字符相同，但是这样串长是$O(\log ^2 n)$的，$\rm WA$了近一半的点...

正解很简洁，也很巧妙：

注意到$\rm good \, string$的性质，我们可以在串的右半段构造一个严格上升的串，在左边构造一个右边串的排列，那么方案数就是左边串的上升子序列个数。

我们从小到大往左边加字符，设空串也是一种情况，那么当前字符可以放最前面或最后面：

- 当前字符放最前面，那么我们的方案数会$+1$。
- 放最后面，方案数$\times 2$。

那么我们可以构造$n+1$的每个二进制位，串长为$O(2\log n)$，复杂度也是这个$O(\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long 

void read(int &x) {
    x=0;int f=1;char ch=getchar();
    for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-f;
    for(;isdigit(ch);ch=getchar()) x=x*10+ch-'0';x*=f;
}

void print(int x) {
    if(x<0) putchar('-'),x=-x;
    if(!x) return ;print(x/10),putchar(x%10+48);
}
void write(int x) {if(!x) putchar('0');else print(x);putchar('\n');}

#define lf double
#define ll long long 
#define pb push_back

const int maxn = 1e5+10;
const int inf = 1e9;
const lf eps = 1e-8;

int n;

vector<int > s,t;

signed main() {
    read(n);int p=101;n++;
    while(n>1) {if(n&1) t.pb(--p),n--;else s.pb(--p),n>>=1;}
    int m=s.size()+t.size();printf("%lld\n",m<<1);
    for(int i=0;i<(int)t.size();i++) printf("%lld ",t[i]);
    for(int i=s.size()-1;~i;i--) printf("%lld ",s[i]);
    for(int i=100-m+1;i<=100;i++) printf("%lld ",i);
    return 0;
}
```

---

## 作者：cwfxlh (赞：1)

# [AT_agc012_c](https://www.luogu.com.cn/problem/AT_agc012_c)   

第一次 $15$ 分钟想出 $2700$ 的题。     

首先我们考虑 $n\le100$ 的情况，可以构造如下序列：   

$$1,2,3,...n-1,n,n,n-1,...3,2,1$$   

这样的序列很明显只有 $n$ 个好的子序列，原因在于，我们可以将其分为前后两段，两段字符集相同而且每一段都没有重复字符。那对于 $n$ 更大的情况，我们或许也可以这样构造。先构造前半部分 $1,2,3,...n$，接下来，后半部分我们令它是一个 $1$ 到 $n$ 的排列，则发现，好的子序列个数就是后半部分的上升子序列个数。于是问题转化成构造一个排列使得其上升子序列个数为 $n$。    

令 $dp_i$ 表示以位置 $i$ 为结尾的上升子序列个数，我们考虑从小到大加入元素，则新加入元素的 $dp$ 值就是 $dp$ 的前缀和加一。而对于 $1,2,3,...k$，第 $i$ 个元素的 $dp$ 值为 $2^{i-1}$，前缀和加一是一个二的幂次。于是我们先根据 $n$ 在二进制下的位数构造一个 $1,2,3,...k$ 形式的数列，然后按照二进制表示的情况一位一位插入就可以了。这里因为是从后往前插入，并且值越来越大，所以不会产生额外贡献。   

代码：  

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[500003],tot;
void insert(int X,int Y){
	tot++;
	for(int i=tot;i>X+1;i--)a[i]=a[i-1];
	a[X+1]=Y;
	return;
}
int fsp[68],stk[5003][2],tots,v;
signed main(){
	fsp[0]=1;
	for(int i=1;i<=60;i++)fsp[i]=fsp[i-1]*2ll;
	scanf("%lld",&n);
	if(n==0){
		puts("1");
		puts("1");
		return 0;
	}
	if(n<=100){
		cout<<n*2<<endl;
		for(int i=1;i<=n;i++)cout<<i<<" ";
		for(int i=n;i;i--)cout<<i<<" ";
		return 0;
	}
	for(int i=1;i<=100;i++)a[++tot]=i;
	for(int i=1,j=2;j-1<=n;i++,j*=2ll){
		a[++tot]=i;
		if(j*2ll-1>n)n-=(j-1);
	}
	v=a[tot];
	for(int i=tot-1;n;i--){
		if(fsp[a[i]]<=n){
			n-=fsp[a[i]];
			stk[++tots][0]=i;
			v++;
			stk[tots][1]=v;
		}
	}
	for(int i=1;i<=tots;i++)insert(stk[i][0],stk[i][1]);
	printf("%lld\n",tot);
	for(int i=1;i<=tot;i++)printf("%lld ",a[i]);
	return 0;
}
```


---

