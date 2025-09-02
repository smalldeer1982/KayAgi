# [ABC313E] Duplicate

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc313/tasks/abc313_e

`1` から `9` までの数字からなる文字列 $ S $ に対して、 $ f(S) $ を次の手順によって得られる文字列 $ T $ とします。($ S_i $ は $ S $ の $ i $ 番目の文字を意味します)

- 文字列 $ T $ がある。はじめ、$ T $ は空文字列である。
- $ i=1,\ 2,\ \dots,\ |S|\ -\ 1 $ の順に次の操作を行う。 
  - $ S_{i+1} $ を整数として解釈したときの値を $ n $ とする。$ T $ の末尾に $ S_i $ を $ n $ 個追加する。

例えば $ S\ = $ `313` のとき、以下の手順によって $ f(S)\ = $ `3111` に決まります。

- はじめ $ T $ は空文字列である。
- $ i=1 $ のとき $ n\ =\ 1 $ である。$ T $ に `3` を $ 1 $ 個追加する。$ T $ は `3` になる。
- $ i=2 $ のとき $ n\ =\ 3 $ である。$ T $ に `1` を $ 3 $ 個追加する。$ T $ は `3111` になる。
- 操作を終了する。$ T $ として `3111` を得る。

`1` から `9` までの数字からなる長さ $ N $ の文字列 $ S $ が与えられます。  
あなたは「$ S $ を $ f(S) $ に置き換える」という操作を $ S $ の長さが $ 1 $ になるまで繰り返します。  
操作が終了するまでに行う操作を行う回数を $ 998244353 $ で割った余りを求めてください。ただし、操作が無限に続く場合は `-1` を出力してください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 10^6 $
- $ S $ は `1`, `2`, `3`, `4`, `5`, `6`, `7`, `8`, `9` からなる長さ $ N $ の文字列

### Sample Explanation 1

$ S\ = $ `313` の場合、操作を $ 4 $ 回行うと $ S $ の長さが $ 1 $ になります。 
- $ f(S)\ = $ `3111` である。$ S $ を `3111` に置き換える。 
- $ f(S)\ = $ `311` である。$ S $ を `311` に置き換える。 
- $ f(S)\ = $ `31` である。$ S $ を `31` に置き換える。 
- $ f(S)\ = $ `3` である。$ S $ を `3` に置き換える。 
- $ S $ の長さが $ 1 $ になったので操作を終了する。

### Sample Explanation 2

$ S\ = $ `123456789` の場合、操作が無限に続きます。この場合は `-1` を出力してください。

## 样例 #1

### 输入

```
3
313```

### 输出

```
4```

## 样例 #2

### 输入

```
9
123456789```

### 输出

```
-1```

## 样例 #3

### 输入

```
2
11```

### 输出

```
1```

# 题解

## 作者：FFTotoro (赞：10)

考虑什么时候无解。显然如果有两个相邻字符都不等于 $1$ 一定无解。举最简单的例子 $22$，这个串不管怎么删长度都不会减少；可以看出如果比它数字更大的串的长度会不减可能还反增。

那么其他情况是否都是有解的？答案是肯定的。考虑这样的字符串有什么性质：它必然是由单个大于 $1$ 的数字和数字 $1$ 的极长连续段构成。每次删掉最后一个大于 $1$ 的数后（如果是），最后一个 $1$ 连续段的长度就不会变了，一个一个删掉即可；而且因为每个大于 $1$ 的数字后面的数都是 $1$，所以它不会变多只会在接下来的操作内被删掉。如此往复一个串必然可以被删完。

至于计数，考虑一次操作会对每个 $1$ 连续段造成什么影响。显然的如果一个 $1$ 连续段后面的数字是 $d$（如果有），一次操作内它的长度就会增加 $d-1$（相当于把最后 $1$ 个 $1$ 替换成 $d$ 个 $1$），设当前已经进行了 $c$ 次操作那么它的长度就增加了 $c(d-1)$。用一个指针从右往左扫，扫到一个大于 $1$ 的数就考虑前面的极长 $1$ 连续段长度增加了多少。

注意特判最后一段 $1$ 的连续段后没有大于 $1$ 的数字的情况。因为长度删到 $1$ 就结束，所以指针只要扫到 $S_1$ 就不用统计答案了。

放代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
main(){
  ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  int n,c=0; string s; cin>>n>>s;
  for(int i=1;i<n;i++)
    if(min(s[i],s[i-1])>49)
      cout<<"-1\n",exit(0); // 判断无解
  int r=n-1;
  while(r>0){
    if(r>0&&s[r]>49){
      (++c)%=mod; // 加上删除它本身一位的贡献
      int x=0,d=s[r]-48; r--;
      while(r>0&&s[r]==49)r--,x++; // 找极长 1 连续段
      (c+=c*(d-1)%mod+x%mod)%=mod; // 算贡献
    }
    else while(r>0&&s[r]==49)r--,(++c)%=mod; // 特判
  }
  cout<<c<<endl;
  return 0;
}
```

---

## 作者：_liuyi_ (赞：10)

# 题意
给定一个长度为 $n$ 的字符串 $S$，你可以对它进行操作 $f(S)$，定义 $f(S)$ 为对字符串 $S$ 的第 $i$ 位 $(1 \leq i\leq n) $，将 $S_{i+1}$ 个 $S_i$ 加入一个空串 $T$ 的末尾。最后将 $S$ 与 $T$ 互换，$T$ 清空，问至少进行多少次操作时 $\left |  S\right |=1$。答案对 $998244353$ 取模，无解输出 $-1$。
# 思路
我们先考虑无解的情况，对于第 $i$ 位，出现 $S_i>1,S_{i+1}>1$，这种情况一定无解，因为显然会无限的进行下去。

对于一般的情况，我们考虑递推，$ans$ 为当前的操作步数，每一位对答案的贡献，显然只与它后面的数有关，所以我们倒着推，对于第 $i$ 位对前面答案的贡献，我们可以想到，它与后面进行的操作和 $S_i$ 有关，我们观察样例可以发现，每次操作不考虑添加的数，长度一定会减少 $1$，那么这一位就会贡献 $(ans+1) \times S_i-1$ 个一，那么可以得到递推式 $ans=(ans+1) \times S_i(2 \leq i\leq n)$，时间复杂度 $O(n)$。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for(int i=a;i<=n;i++)
#define per(i,a,n) for(int i=n;i>=a;i--)
#define mem(a, x) memset(a, x, sizeof(a)) 
#define pb push_back
#define SZ(x) ((int)(x).size())
#define debug(x) cout<<#x<<":"<<x<<endl;
#define all(a) a.begin(),a.end()
typedef long long ll;
typedef pair<int,int> PII;
typedef unsigned long long ull;
typedef double db;
typedef vector<int> VI;
const int N=1e6+10;
const int mod=998244353;
ll n,ans;
char s[N];
int main(){
	scanf("%lld%s",&n,s+1);
	rep(i,1,n-1){
		if(s[i]!='1'&&s[i+1]!='1'){
			puts("-1");
			return 0;
		}
	}
	per(i,2,n) ans=(ans+1)%mod*((int)s[i]-'0')%mod;
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：Crazyouth (赞：3)

**翻译**

对于一个字符串 $S$，假如一个字符串 $T$ 是按以下方法形成的，记 $f(S)=T$：

- 初始时，$T$ 为空串。
- 接下来，对于所有 $1\le i< |S|$，将 $S_{i+1}$ 个字符 $S_i$ 加入 $T$ 的末尾。

你需要求出，需要进行多少次如下操作，才能使 $|S|=1$：

- 将 $S$ 替换为 $f(S)$。

**分析**

先考虑什么时候无解，我们把样例 $2$ 缩短一些：$S=1234$，接下来模拟操作：$S\leftarrow f(S)=112223333,S\leftarrow f(S)=1112222222333333333,\dots$，会发现就是在一开始的时候，出现了两个相邻的大于 $1$ 的数，结果两者无限复制，就无解了。证明：若 $S_i>1,S_{i+1}>1$，则 $S_i\ge2,S_{i+1}\ge2$，所以 $S_i$ 的复制至少有 $2$ 个，因此又会产生两个相邻且大于 $1$ 的数。

接下来考虑有解时怎么算。首先发现，假如末尾是 $1$，则一次可删掉其末尾。进而，若要删掉末尾，则需要先删掉自己，再删掉因前几次操作而多出来的 $1$，不难得到前面会产生 $ans\times (s_{|s|}-1)$ 个 $1$，所以就做完了。

**AC Code**
```cpp
#include <bits/stdc++.h>
using namespace std;
const int mod=998244353;
int check(string s)//是否有解
{
	for(int i=1;i<s.size();i++) if(s[i]>'1'&&s[i-1]>'1') return 0;
	return 1;
}
int main()
{
	int n;
	cin>>n;
	string s;
	cin>>s;
	if(!check(s)) 
	{
		cout<<-1;
		return 0;
	}
	long long ans=0;
	for(int i=s.size()-1;i>0;i--)
	{
		ans++;//删自己
		ans+=ans*(s[i]-'1');//删多出来的1
		ans%=mod; //取模
	}
	cout<<ans;
	return 0;
}

---

## 作者：SegTree (赞：1)

### 题意

一个数字串串 $S$，一次操作为创建一个空串 $T$，对于 $i\in[1,|S|-1]$，在 $T$ 中将 $S_i$ 重复 $S_{i+1}$ 次，然后 $S\gets T$。求将该串字符串长度变为 $1$ 所需最小次数对 $998244353$ 取模的结果，若无法达到字符串长度为 $1$，输出 `-1`。

$2\le|S|\le 10^6$。

### 题解
+ 判断无解：以样例 $2$ 为例，$23\to 222\to 2222\to\cdots$，你会发现每个字符都会出现更多次，字符串长度只会减 $1$，也就是字符串长度不降，这样一来就肯定无法让字符串长度变为 $1$，无解。

+ 操作次数：以 $121$ 为例。$121\to 112\to 111\to 11\to 1$，对于 $i$，它一次会让前面的字符多出现 $s_i-1$ 遍，若记 $c$ 为清空后面的操作次数，它会造成前面的字符复制 $c\times(s_i-1)$ 遍，再加上需要 $1$ 次来删除这个字符本身。


[赛时代码。](https://atcoder.jp/contests/abc313/submissions/44302711)

---

## 作者：joe_zxq (赞：1)

# 一、什么情况无解？
让我们看这样一个例子：

$$34 \to 3333 \to 333333 \dots \to \dots$$

会陷入死循环。

若在 $3$ 和 $4$ 之间加入一个 $1$，那么：

$$314 \to 31111 \to 3111 \to 311 \to 31 \to 3$$

就不会陷入死循环。

由此可见，**如果两个大于 $1$ 的数相邻就直接输出 `-1`**。

# 二、有解时怎么计算？
删除每一位，我们显然是**从后往前**，最后一位不需要删除。

在 $314 \to 31111 \to 3111 \to 311 \to 31 \to 3$ 的例子中，删除 $4$ 这个数时，我们进行了 $4$ 次操作（$314 \to 31111 \to 3111 \to 311 \to 31$）。

再举些例子，总结发现，根据乘法原理，删除 $x$ 需要 $ans \times (x-1)+1$ 次。（这里，$ans$ 指当前的答案）

为啥要 $+1$？因为要把自己加上。

# 三、代码实现
附上完整代码，注意要模 $998244353$ 哦。

```cpp
#include<bits/stdc++.h>
using namespace std;
void solve(){
    long long n; cin>>n;
    string s; cin>>s;
    for(long long i=0;i<(long long)s.size()-1;i++){
    	if(s[i]!='1'&&s[i+1]!='1'){
    		cout<<-1;
    		return;
		}
	}
	long long ans=0;
	for(long long i=(long long)s.size()-1;i>0;i--){
		ans++;
		ans+=ans*(s[i]-'1');
		ans%=998244353;
	}
	cout<<ans;
}
int main(){
    long long tc=1; //cin>>tc;
    while(tc--){
    	solve();
    }
    return 0;
}
```

---

## 作者：梦应归于何处 (赞：1)

## 题目大意

对于一个仅包含字符 $1,2,3,4,5,6,7,8,9$ 的字符串  $S$ 而言，规定 $f(S)$ 是按如下方式构造的字符串 $T$：
- 最初 $T$ 是空串；
- 枚举 $i = 1, 2, \dots |S| - 1$，往 $T$ 的尾部添加 $S_{i+1}$ 个 $S_i$ 字符

给定字符串 $S$，反复将 $S$ 替换为 $f(S)$ 直至 $S$ 串长度为 $1$。问需要的操作步数。答案对 $998244353$ 取模。


## 如何判断无解

我们可以发现如果两个大于一的数相邻，那么就会出现无限循环变长。

举个例子：

- $23$
- $222$
- $2222$
- $222222$

	⋮
    
我们就可以判断了，如果两个大于一的数相邻就直接输出 `-1`。

## 暴力思路

怎么暴力，这个很好想吧。

就是按照题目的要求模拟。

## 正确思路

考虑倒推。

我们设 $res$ 变量为需要变多少次，$x$ 为当前是多少，$y$ 为 $x$ 的后面一个是多少。

首先我们考虑 当 $x$ 等于一的时候，他是不是会增加 $y-1$ 个 $x$。所以，这里我们 给 $res$ 加上 $(y-1) \times res+1$，为什么要加一呢？因为我们要把它自己给加上。

如果 $x$ 不为一，那么就 $res+1$ 应为它后面一定是一。

时间复杂度：$O(N)$。

### 代码


~~~cpp

#include <bits/stdc++.h>
#define TNTMAX INT_MAX
#define db double
#define ll long long
#define ex exit(0);
using namespace std;
ll mod = 998244353;
int main() {
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ll n;
	cin >> n;
	string s;
	cin >> s;
	ll res = 0;
	for (int i = n - 1; i > 0; i--) {
		if (s[i] != '1' && s[i - 1] != '1') {
			cout << "-1";
			return 0;
		}
		ll x = s[i] - '0', y = 0;
		if (i != n + 1) {
			y = s[i + 1] - '0';
		}
		if (x == 1) {
			if (i != n - 1) {
				res = (res + (y - 1) * res % mod + 1) % mod;
			} else {
				res++;
			}
		} else {
			res++;
		}
		res %= mod;
	}
	res += (s[1] - '0' - 1) * res % mod;
	res %= mod;
	res = (res + mod) % mod;
	cout << res;
	return 0;
}



~~~

[AT的AC记录](https://atcoder.jp/contests/abc313/submissions/44340098)

---

## 作者：nahidaa (赞：0)

## [传送门](https://www.luogu.com.cn/problem/AT_abc313_e)
## 题解：

观察发现，当且仅当存在相邻两个数均不为 1 时，无解。

其中具体的思考过程，先是发现当存在相邻两个数均不为 1 时，无解；而后进一步得到"当且仅当"。

那么，接下来，我们就可以通过数学进行计算。

最后，$\color{red}\text{不要忘记取模！}$

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,ans,MOD=998244353;//取模别忘了
string a,b;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>b;
	a=" "+b;
	for(int g=2;g<=n;++g){
		if(a[g]!='1'&&a[g-1]!='1'){//当且仅当存在相邻两个数均不为1时，无解
			cout<<"-1\n";return 0;
		}
	}//判断无解
	ans=1;
	for(int g=n-1;g>=1;--g){
		if(a[g]=='1')ans+=1+(a[g+1]-'1')*ans,ans%=MOD;//a[g+1]位不为'1',数学计算
		else ++ans;//a[g+1]位为'1',则 ++
	}
	cout<<ans-1<<"\n";//别忘了最后应该剩下一个
	return 0;
}
```

---

## 作者：Ferm_Tawn (赞：0)

首先，如果 $S$ 相邻的数字大于等于 $2$ ，那么答案是 $-1$ 。

我们考虑其他情况。例如，设 $S=$ $1121131$
。$S$ 的转换操作如下:

- $1121131$

- $111211113$
- $11112111111$
- $11111211111$
- $111111211111$

我们可以从序列中观察到以下性质:

由相同数字组成的后缀(如上面的 $3$ 和 $111111$ )被一个接一个地缩短，最终消失。

出现在 $2$ 到 $9$ 之间的不属于该后缀的数字不会减少。

如果连续出现的 $1$ 不在该后缀中，则每一步增加 $x - 1$ ，其中 $x$ 是前一位数字。例如，前导 $11$ 的出现次数每一步增加 $2 - 1 = 1$ 。

此规则的要点是，只有当相同数字是后缀时，连续出现的数字才会减少其长度。因此，可以通过将 $S$ 存储在运行长度编码中，并在弹出运行长度压缩序列尾部时模拟 $S$ 的长度和操作次数来找到答案。

时间复杂度：$O(N)$ 。

代码来喽：

```cpp
//借用 atcoder 的函数，本地无法运行。
#include <bits/stdc++.h>
#include "atcoder/modint.hpp"
using namespace std;
using mint = atcoder::modint998244353;
vector<pair<char, int>> RunLengthEncoding(string& S) {
  if (S.empty()) return {};
  vector<pair<char, int>> ret;
  char c = S[0];
  int n = 1;
  for (int i = 1; i < (int)S.size(); i++) {
    if (S[i] == c)
      n++;
    else {
      ret.emplace_back(c, n);
      c = S[i], n = 1;
    }
  }
  ret.emplace_back(c, n);
  return ret;
}

int main() {
  int N;
  string S;
  cin >> N >> S;
  for (int i = 0; i + 1 < N; i++) {
    if (S[i] >= '2' and S[i + 1] >= '2') {
      cout << "-1\n";
      exit(0);
    }
  }
  auto rle = RunLengthEncoding(S);
  mint t = 0;
  char last = '1';
  while (!rle.empty()) {
    char c;
    mint n;
    tie(c, n) = rle.back();
    rle.pop_back();
    if (c == '1') {
      n += t * (last - '1');
      t += n;
    } else {
      t += 1;
    }
    last = c;
  }
  cout << (t - 1).val() << "\n";
}

```


---

## 作者：robertuu (赞：0)

[洛谷题目传送门](https://www.luogu.com.cn/problem/AT_abc313_e)

[AT 原题传送门](https://atcoder.jp/contests/abc313/tasks/abc313_e)

### 分析：

显然可以发现，只有 $1$ 才能通过在最后一位被消除减短串的长度，如果出现了连续 $2$ 个或多个大于 $1$ 的数字，穿的长度只可能永远不变（比如 `22` 的串，长度永远不变，比 $2$ 大的数长度会增加）。

因此可以向把整个串扫一遍，判断是否出现连续多位不是 $1$ 的现象，如果出现了直接输出 `-1`。

对于一串连续的 $1$，最后一个 $1$ 会因为与后面的一个非 $1$ 数相邻而增加长度，如果前面的数是 $x$，这组相邻一直保持了 $y$ 次操作，连续 $1$ 串的长度将增加 $y(x-1)$（每一轮把最后一个 $1$ 多复制 $x-1$ 遍，少的那一次相当于把原来这个 $1$ 的位置补上）。可以把一个连续 $1$ 串和它后面的数字 $x$ 作为一个整体，如果这个整体要被消除，对答案的贡献是 $now(x-1)+len$，$now$ 表示这一组被消掉前已经操作了几轮（需要用计算出的贡献进行更新），$len$ 表示这一组 $1$ 的长度。不断重复就可以搞定了！

复杂度分析：由于一开始就要枚举数组，后面的部分最差也会有 $\frac{n}{2}$ 组，因此复杂度是 $O(n)$，可以通过。

### 细节：
- 第一个数是不是 `1` 需要用来帮助后面每一位判定是否是“必 $1$ 位”，需要单独判断（有的写法似乎不用，但是后面需要现场找块）。

- 如果第一位是 $1$ 第二位不是 $1$ 需要“豁免”第二位，其他情况不用，从第二位开始判

- 第一位是 $1$ 的时候做后一个块可以省下一个，输出时需要减掉。不是 $1$ 不用减。

- 最后一位时 $1$ 时需要把这些 $1$ 也放入块中（那个后面的数组就随便了，反正处理的时候 $now$ 是 $0$）。

AC code：
```
#include<iostream>
using namespace std;
char s[1000001];
struct node
{
	int sum,p;
} a[1000001];
int main()
{
	int n;
	scanf("%d",&n);
	scanf("%s",s);
	int summ = 0,sz = 0;
	s[n] = '0';
	if(s[0] == '1' && s[1] != '1') a[++sz] = (node){1,s[1]-'0'}; // 单独算第一位是1，第二位不是，循环跳过第二位（只用这种情况第一位是1才会被计算！！）
	for(int i = 1+sz;i < n;i++)
	{
		if(s[i] != '1') // “必1位”不是1
		{
			printf("-1");
			return 0;
		}
		summ = 0;
		while(i < n && s[i] == '1') {summ++; i++;} // 全是这个块
		a[++sz] = (node){summ,s[i]-'0'}; // 把新块加入
	}
	long long ans = 0;
	for(int i = sz;i >= 1;i--) ans = (ans + a[i].sum + 1ll*ans*(a[i].p-1) + a[i].p) % 998244353; // 一定要去模！
	printf("%lld",(ans-(s[0]=='1'&&s[1]!='1')) % 998244353); // 第一个1如果被计算了需要-1（s[1]=='1'没被计算，不用减）
	return 0;
}
```


---

