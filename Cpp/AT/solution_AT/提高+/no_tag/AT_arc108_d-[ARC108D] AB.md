# [ARC108D] AB

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc108/tasks/arc108_d

整数 $ N $ と $ 4 $ つの文字 $ c_{\mathrm{AA}},c_{\mathrm{AB}},c_{\mathrm{BA}},c_{\mathrm{BB}} $ が与えられます。 ここで、与えられる $ 4 $ つの文字はいずれも `A` か `B` であることが保証されます。

すぬけ君は文字列 $ s $ を持っています。 $ s $ ははじめ `AB` です。

$ s $ の長さを $ |s| $ と書くことにします。 すぬけ君は以下の $ 4 $ 種類の操作を任意の順序で $ 0 $ 回以上行うことができます。

1. $ 1\ \leq\ i\ <\ |s|,\ s_{i} $ = `A`, $ s_{i+1} $ = `A` なる $ i $ を選んで、$ s $ の $ i $ 文字目と $ i+1 $ 文字目の間に $ c_{\mathrm{AA}} $ を挿入する。
2. $ 1\ \leq\ i\ <\ |s|,s_{i} $ = `A`, $ s_{i+1} $ = `B` なる $ i $ を選んで、$ s $ の $ i $ 文字目と $ i+1 $ 文字目の間に $ c_{\mathrm{AB}} $ を挿入する。
3. $ 1\ \leq\ i\ <\ |s|,s_{i} $ = `B`, $ s_{i+1} $ = `A` なる $ i $ を選んで、$ s $ の $ i $ 文字目と $ i+1 $ 文字目の間に $ c_{\mathrm{BA}} $ を挿入する。
4. $ 1\ \leq\ i\ <\ |s|,s_{i} $ = `B`, $ s_{i+1} $ = `B` なる $ i $ を選んで、$ s $ の $ i $ 文字目と $ i+1 $ 文字目の間に $ c_{\mathrm{BB}} $ を挿入する。

$ s $ の長さが $ N $ になるまで操作を行ったあとの $ s $ としてありうる文字列の個数を $ 10^9+7 $ で割ったあまりを求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 1000 $
- $ c_{\mathrm{AA}},c_{\mathrm{AB}},c_{\mathrm{BA}},c_{\mathrm{BB}} $ は `A` か `B`

### Sample Explanation 1

\- $ s $ としてありうる文字列は `ABAB` と `ABBB` の $ 2 $ 通りです。

### Sample Explanation 2

\- $ s $ としてありうる文字列は $ 1 $ 通りです。

## 样例 #1

### 输入

```
4
A
B
B
A```

### 输出

```
2```

## 样例 #2

### 输入

```
1000
B
B
B
B```

### 输出

```
1```

# 题解

## 作者：henrytb (赞：7)

分类讨论题。

先假设 $c_\texttt{AB} = \texttt{B}$，如果是 $\texttt{A}$ 则同理。

假如 $c_\texttt{BB} = \texttt{B}$，那么最终的串只有可能有一种，即为 $\texttt{ABB}\ldots\texttt{B}$。

否则 $c_\texttt{BB} = \texttt{A}$，此时，若 $c_\texttt{BA} = \texttt{A}$，那么所有以 $\texttt{AB}$ 起始、$\texttt{B}$ 结尾的串都可以被取到，答案为 $2^{n - 3}$；若 $c_\texttt{BA} = \texttt{B}$，那么所有以 $\texttt{AB}$ 起始、$\texttt{B}$ 结尾的满足 $\texttt{A}$ 不连续的串都可以被取到，答案即为 $\texttt{Fib}_{n - 2}$。

其中 $\texttt{Fib}_i$ 表示斐波那契数列的第 $i$ 项，$\texttt{Fib}_0 = 1, \texttt{Fib}_1 = 1$。

---

## 作者：SmileMask (赞：2)

不妨分类讨论，考虑 $cAB=A$ 的情况，对于 $cAB=B$ 同理。

- 若 $cAA=A$ 的情况，显然只有一种串为：$AAAAAA\dots B$。
- 若 $cAA=B$ 的情况，那么考虑最后的串一定为 $A \dots AB$ 这种类型，中间的串不妨将其考虑成每次在尾部加入一个字符有多少种不同的情况，此时若中间串末尾为 $A$，可以任意添加 $A,B$。
  - 若 $cBA=B$，则中间串末尾为 $B$ 时，还是可以任意添加 $A,B$，则总方案数为 $2^{n-3}$。
  - 若 $cBA=A$，则中间串末尾为 $B$ 时，只能添加 $A$，转化对为长度为 $n-3$，$B$ 不相邻的串计数，不妨记 $f_{i}$ 为长度为 $i$ 且 $i$ 为 $B$ 的方案数，答案为 $\sum_{i=0}^{n-3} f_i$，转移有：$f_{i}=\sum_{k=0}^{i-2} f_i$，可以做到 $O(\log n)$，但是笔者懒得写矩阵快速幂写了 $O(n)$ 递推。
```cpp
void Main(){
	n=rd;
	cin>>cAA>>cAB>>cBA>>cBB;
	if(n<=3) return puts("1"),void();
	int ans=qmi(2,n-3),all=2;
	f[0]=f[1]=1;
	for(int i=2;i<=n-3;i++)
		f[i]=(all-f[i-1]+mod)%mod,all=(all+f[i])%mod;
	if(cAB=='A'){
		if(cAA=='A') ans=1;
		else if(cBA=='A') ans=all;
	}
	else{
		if(cBB=='B') ans=1;
		else if(cBA=='B') ans=all;
	}
	cout<<ans<<endl;
}

```

---

## 作者：2huk (赞：2)

可能写的有点烦琐。想省事的直接看后面的总结吧。

---

我们称在某两个相邻 $\texttt {AA}$ 间添加 $S_{\texttt{AB}}$ 为“$S_\texttt{AA}$ 操作”。其余类似。

首先第一步一定是 $S_{\texttt {AB}}$ 操作。即 $s = \texttt A + S_{\texttt {AB}} +\texttt B$。不妨对 $S_{\texttt {AB}}$ 分类讨论。

到最后你会发现 $S_{\texttt{AB}}$ 是 $\texttt A$ 是 $\texttt B$ 都是类似的。我们以 $S_{\texttt {AB}} = \texttt A$ 为例。

第一步后 $s = \texttt {AAB}$。第二步我们还可以继续进行 $S_{\texttt {AB}}$ 操作，得到 $s = \texttt{AAAB}$。以此类推。也就是我们可以凑出任意的 $s = \texttt{AAA}\dots\texttt{AB}$。

总长度需要是 $n$。不妨枚举上面的过程经过了**最多**几次。即 $s = \underbrace{\texttt{AAA}\dots\texttt A}_k\texttt B$（$k < n$）。

（**最多**的含义是，以后我们不再在最后这个空里进行 $S_{\texttt{AB}}$ 操作。）

那么下一步一定在某两个 $\texttt {AA}$ 之间添加 $S_{\texttt {AA}}$。二级分类讨论。

- $S_{\texttt {AA}} = \texttt A$。那么一定有 $s = \underbrace{\texttt{AAA}\dots\texttt A}_{k+1}\texttt B$。这和最开始的过程执行 $k+1$ 次无异。不讨论。

  换言之，最终字符串一定形如 $s = \underbrace{\texttt{AAA}\dots\texttt A}_{n-1}\texttt B$。也就是说答案为 $1$。

- $S_{\texttt{AA}} = \texttt B$。那么进行若干步这样的操作后，整个字符串一定形如 $s = \texttt{AA}\dots\texttt {A}\texttt B\texttt{AA}\dots\texttt {A}\texttt B\texttt{AA}\dots\texttt {AB}$，即一个连续连续 $\texttt A$ 段后一定紧跟恰好 $1$ 个 $\texttt B$。

  此时如果再进行 $S_\texttt{AB}$ 操作（别忘了 $S_\texttt {AB}=\texttt A$）得到的字符串的形式和这个是一样的。

  所以下一步操作一定是 $S_{\texttt {BA}}$ 操作。

  三级分类讨论。

  - $S_{\texttt{BA}} = \texttt A$。下一步得到的字符串形式还是 $s = \texttt{AA}\dots\texttt {A}\texttt B\texttt{AA}\dots\texttt {A}\texttt B\texttt{AA}\dots\texttt {AB}$。即每个连续 $\texttt B$ 段的长度必为 $1$。做个 DP 即可。
  - $S_{\texttt{AB}} = \texttt B$。连续若干次 $S_\texttt{AB}$ 操作后 $s$ 将变得没有规律。每个连续 $\texttt B$ 段的长度也不固定了。也就是说，除了开头的 $\texttt A$，结尾的 $\texttt B$ 和倒数第二个 $\texttt A$ 固定不变，中间共有 $2^{n-3}$ 种方案。

---

总结一下。当 $S_{\texttt {AB}} = \texttt A$ 时：

- $S_\texttt{AA}=\texttt A$：答案为 $1$。
- $S_{\texttt{AA}} = \texttt B$：
  - $S_{\texttt{BA}} = \texttt A$：考虑 DP。设 $f(i,0/1)$ 表示考虑前 $i$ 个位置，且最后一个位置是 $\texttt A / \texttt B$，且每个连续 $\texttt B$ 段的长度必为 $1$ 的方案数。转移 $f(i,0) +f(i,1) \to f(i+1,0),f(i,1)\to f(i+1,0)$。
  - $S_{\texttt{AB}} = \texttt B$：答案为 $2^{n-3}$。

$S_{\texttt {AB}} = \texttt B$ 几乎一模一样。请读者自行完成。

---

注意需要特判一下 $n = 2$。

代码：<https://atcoder.jp/contests/arc108/submissions/59509364>

---

## 作者：shinkuu (赞：2)

挺有意思的题。

一开始看到 $n\le 1000$ 想的是一个类似区间 dp 的东西，但是没写完就发现这样完全不能去重。

于是考虑推一些性质。一开始序列是 `AB`，不妨设 $c_{AB}=A$，另一种情况大概是对称的。则序列会变成 `AAB`。此时发现，右半边仍然是 `AB`，怎么做都只能再增加一个 `A`。所以只用考虑左半边的 `AA`。

同时注意到这要求最终的 $s_{n-1}=A$。

- 如果 $c_{AA}=A$，那么最终序列就只有 `AAA...AB` 这一种情况。

- 否则若 $c_{BA}=B$，则可以发现，任何一个 $s_1=A,s_{n-1}=A,s_n=B$ 的序列都可以构造出来，方法是先不管开头的 `A` 和结尾的 `B` ，每次找到最后一个连续段，先把这个连续段的第一个位置填上，再往后填。故方案数为 $2^{n-3}$。

- 否则还是类似上面的，但是此时不能有两个连续的 `B`，因为 $c_{AB}=c_{BA}=A$。这是一个经典计数问题，设 $f_n$ 为长为 $n$ 的序列的方案数，则 $f$ 为 $f_0=1,f_1=2$ 的斐波那契数列。方案数为 $f_{n-3}$。

$c_{AB}=B$ 的答案是类似的，对称地推一下即可。

code：

```cpp
int n,m,a[4],f[N];
il int Mod(int x,int y){
	return x+y>=mod?x+y-mod:x+y;
}
il int qpow(int x,int y){
	int ret=1;
	while(y){
		if(y&1){
			ret=1ll*ret*x%mod;
		}
		x=1ll*x*x%mod,y>>=1;
	}
	return ret;
}
void Yorushika(){
	read(n);
	if(n==2){
		puts("1");
		return;
	}
	rep(i,0,3){
		char s[7];scanf("%s",s);
		a[i]=s[0]-'A';
	}
	f[0]=1,f[1]=2;
	rep(i,2,n){
		f[i]=Mod(f[i-1],f[i-2]);
	}
	if(a[1]==0){
		if(a[0]==0){
			puts("1");
		}else{
			if(a[2]==1){
				printf("%d\n",qpow(2,n-3));
			}else{
				printf("%d\n",f[n-3]);
			}
		}
	}else{
		if(a[3]==1){
			puts("1");
		}else{
			if(a[2]==0){
				printf("%d\n",qpow(2,n-3));
			}else{
				printf("%d\n",f[n-3]);
			}
		}
	}
}
signed main(){
	int t=1;
	//read(t);
	while(t--){
		Yorushika();
	}
}
```

---

## 作者：SoyTony (赞：2)

人类智慧分类讨论题。

首先考虑 $c_{\text{AB}}$ 的值，这一定是第一次插入的字符。

我们在 $c_{\text{AB}}=\texttt{A}$ 的基础上讨论，这说明我们开始得到 $\texttt{AAB}$ 且可以得到任意 $\texttt{A}\dots\texttt{AB}$。

在此基础上讨论 $c_{\text{AA}}$ 的值，如果是 $\texttt{A}$ 那么能且只能得到 $\texttt{A}\dots\texttt{AB}$，答案为 $1$。否则 $c_{\text{AA}}=\texttt{B}$，也就是我们可以在相邻 $\texttt{A}$ 之间插入一个 $\texttt{B}$。现在再讨论能不能存在相邻的两个 $\texttt{B}$，由于 $c_{\text{AB}}=\texttt{A}$ 已经确定，可以讨论的只有 $c_{\text{BA}}$。

- $c_{\text{BA}}=\texttt{B}$，那么 $\texttt{B}$ 可以相邻，也就是除了第一个字符和最后一个字符确定，且倒数第二个字符一定是 $\texttt{A}$ 以外，其余位置任意，答案 $2^{n-3}$。

- $c_{\text{BA}}=\texttt{A}$，那么 $\texttt{B}$ 不能相邻，长度依旧是 $n-3$，可以 DP 出来。

$c_{\text{AB}}=\texttt{B}$ 的情况本质相同。

上面的 DP 设 $f_{i,0/1}$ 为长度为 $i$，结尾为可以/不可以相邻的元素的方案数，递推式：

$$\begin{cases}
f_{i,0}=f_{i-1,0}+f_{i-1,1}\\
f_{i,1}=f_{i-1,0}
\end{cases}$$  

答案就是 $f_{n-3,0}+f_{n-3,1}$。

所以 $2\le n\le 1000$ 是什么意思。

---

## 作者：AstaVenti_ (赞：1)

# $\mathbf{0x00}$ 启

蒟蒻的第 $\color{red}\mathbf{41}$ 篇题解。

# $\mathbf{0x01}$ 承

对于字符串 $s$，初始为 $\text{AB}$，每次在两个字母中间根据左右两个字母的种类插入新的字母，求使它达到 $n$ 长度时的方案数。 

# $\mathbf{0x02}$ 转

其实就是个找规律。由于初始字符串是 $\text{AB}$，我们就以 $c_{\text{AB}}$ 的不同情况来分类讨论。

- 若 $c_{\text{AB}}=\text{A}$，我们第一次生成的字符串就是 $\text{AAB}$，之后依次在 $\text{AB}$ 之间插入 $\text{A}$，我们就能得到 $\text{A}\cdots\text{AB}$。进而当 $c_\text{AA}=\text{A}$ 时，我们只能得到 $\text{A}\cdots\text{AB}$ 一种情况；当 $c_\text{AA}=\text{B}$ 时，则可以有一段 $\cdots\text{ABA}\cdots$，继续讨论 $c_\text{BA}$ 的情况：当$c_\text{BA}=\text{A}$ 时，则一定会出现形如 $\cdots\text{ABA}\cdots$ 的子串，$\text{B}$ 也不会相邻（因为 $c_\text{BA}$ 和 $c_\text{AB}$ 都是 $\text{A}$），则 $\text{A}\cdots\text{AB}$ 中还有 $n-3$ 位不确定，又因为 $\text{B}$ 不能相邻，简单推算可以算出结果就是斐波那契数列的第 $n-1$ 项。反之 $c_\text{BA}=\text{B}$ 时就没有规定了，结果是 $2^{n-3}$。

- $c_{\text{AB}}=\text{B}$ 的情况同理，但是要注意当且仅当 $c_{\text{BB}}=\text{B}$ 时结果为 $1$。

此外在计算 $2^{n-3}$ 时最好不要用递归的快速幂，直接 $\Theta(n)$ 循环即可，毕竟 $1\leq n\leq 1000$。

# $\mathbf{0x03}$ 合

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod=998244353;
ll n,k,tmp,x=0,y=0,a[100005];
ll ksm(ll b,ll e=mod-2) {
	ll a=1;
	while(e) {
		if(e%2)(a*=b)%=mod;
		(b*=b)%=mod,e/=2;
	}
	return a;
}
ll C(ll n,ll m) {
	if(m>n/2)m=n-m;
	if(n<m)return 0;
	ll r1=1,r2=1;
	for(ll i=0; i<m; i++)(r1*=(n-i))%=mod,(r2*=(i+1))%=mod;
	return r1*ksm(r2,mod-2)%mod;
}
int main() {
	cin>>n>>k;	
	for(ll i=1;i<=n;i++){
		if(i==1)cin>>a[i];
		if(i>=2){
			cin>>a[i];
			y+=a[i];
		}
	}
	if(a[1]<y+k) {
		cout<<0;
		return 0;
	}
	a[1]-=(y+k);
	//put x balls into k boxes
	ll ans=1;
	for(ll i=1; i<=n; i++) {
		ans=ans*(C(a[i]+k-1,k-1)%mod)%mod;
	}
	cout<<(ans%mod+mod)%mod;
}
```

---

## 作者：TLEWA (赞：1)

清新可爱小分讨。

从 $AB$ 开始转移一次有两种情况：$ABB$ 和 $AAB$。考虑将转移后产生的 $AB$ 子串标记，视为“原串”，两种情况分别是 $A[AB]$，$[AB]B$。容易发现两种转移本质相同，仅为字母相反和方向不同。这里我只讨论从 $c_{AB}=B$ 的情况往后转移。

假设 $c_{BB}=B$ 那么显然最终取值为 $ABBB...$，只有一种。

如果 $c_{BB}=A$，那么一定可以向右构造出无数原串。根据 $c_{BA}$ 取值不同，可以在原串之间构造不同的东西：

如果 $c_{BA}=B$，那么最终串形如 $[AB]BB...[AB]B...$

如果 $c_{BA}=A$，那么最终串形如 $[AB]BB...AA...[AB]B...$

对于每种情况，分别讨论，根据实现不同复杂度差异极大，好在本题的 $n$ 较小，正常实现均可通过。

## AC 代码


```cpp
#include<bits/stdc++.h>
#define int long long

/*
考虑初始字符串为 AB，可能出现的第二中转移无非两个

[AB]B
A[AB] 

我们考虑 BB 和 AA 的情况

BB == 'A'
[AB]xB[AB]

BB == 'B'
[AB]BB

A 的情况同理 

AB -> [AB]B

BB -> 'A' AB -> 'B' BA -> 'A'

[AB]x*b x*A[AB]

*/

using namespace std;

const int N=1005,mod=1000000007;

int n;

int dp[N],dp2[N];
char C[2][2]; 

signed main() {
	cin >> n;
	for(int i=0;i<=1;++i)
		for(int j=0;j<=1;++j)
			cin >> C[i][j];
	
	dp[2]=1;
	for(int i=3;i<=n;++i) dp[i]=(dp[i-1]+dp[i-2])%mod;
	
	dp2[2]=1;
	for(int i=3;i<=n;++i) {
		for(int j=2;j<=i-2;++j) {
			dp2[i]=(dp2[i]+((i-2)-j+1)*dp2[j])%mod;
		}
	}
	int ans=0;
	
	if(C[0][1]=='A') { // A[AB]
		if(C[0][0]=='A') {cout << 1;return 0;}
		if(C[1][0]=='A') cout << dp[n];
		else {
			for(int i=2;i<=n;++i) ans=(ans+dp2[i])%mod;
			cout << ans;
		}
	}else {
		if(C[1][1]=='B') {cout << 1;return 0;}
		if(C[1][0]=='B') cout << dp[n];
		else {
			for(int i=2;i<=n;++i) ans=(ans+dp2[i])%mod;
			cout << ans;
		}
	}
	
	return 0;
}

```

---

