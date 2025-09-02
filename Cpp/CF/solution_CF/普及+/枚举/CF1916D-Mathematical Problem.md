# Mathematical Problem

## 题目描述

The mathematicians of the 31st lyceum were given the following task:

You are given an odd number $ n $ , and you need to find $ n $ different numbers that are squares of integers. But it's not that simple. Each number should have a length of $ n $ (and should not have leading zeros), and the multiset of digits of all the numbers should be the same. For example, for $ \mathtt{234} $ and $ \mathtt{432} $ , and $ \mathtt{11223} $ and $ \mathtt{32211} $ , the multisets of digits are the same, but for $ \mathtt{123} $ and $ \mathtt{112233} $ , they are not.

The mathematicians couldn't solve this problem. Can you?

## 说明/提示

Below are the squares of the numbers that are the answers for the second test case:

 $ \mathtt{169} $ = $ \mathtt{13}^2 $

 $ \mathtt{196} $ = $ \mathtt{14}^2 $

 $ \mathtt{961} $ = $ \mathtt{31}^2 $

Below are the squares of the numbers that are the answers for the third test case:

 $ \mathtt{16384} $ = $ \mathtt{128}^2 $

 $ \mathtt{31684} $ = $ \mathtt{178}^2 $

 $ \mathtt{36481} $ = $ \mathtt{191}^2 $

 $ \mathtt{38416} $ = $ \mathtt{196}^2 $

 $ \mathtt{43681} $ = $ \mathtt{209}^2 $

## 样例 #1

### 输入

```
3
1
3
5```

### 输出

```
1
169
196
961
16384
31684
36481
38416
43681```

# 题解

## 作者：One_JuRuo (赞：18)

## 思路

很不错的人类智慧题。

拿到以后，完全没有思路，看到数据范围，感觉是什么 $n^2\log n$ 的逆天做法，但是又完全没思路，看后面的题感觉没希望，就在这道题死磕。

先打了个暴力程序，发现平方数太多，没什么规律，就拿了个 map 统计一下那些出现数字方案拥有的平方数比较多

程序如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
multiset<int>s;
map<multiset<int>,int>mp;
int main()
{
	for(int i=1;i<=200000;++i)
	{
		long long k=1ll*i*i;
		if(k<100000000) continue;//此程序是九位数的情况，想试其他情况的就改这里的值即可
		if(k>999999999) break;
		while(k) s.insert(k%10),k/=10;
		++mp[s],s.clear();
	}
	for(auto i:mp)
	{
		if(i.second>=9)//这里也要改
		{
			for(auto j:i.first)
			{
				cout<<j<<" ";
			}
			puts("");
		}
	}
	return 0;
}
```

先试一试五位数的情况，发现下面的数字组合都可以存在五个以上的平方数，除了样例给的还有一组。

- 0 0 1 6 9
- 1 3 4 6 8

再试一试七位数的情况，发现符合条件的数字组合更多了。

- 0 0 0 0 1 6 9
- 0 0 1 3 4 6 8
- 0 1 2 4 5 6 9
- 0 1 4 5 6 7 8
- 1 2 3 4 4 5 6
- 1 2 3 4 4 8 9

一看，发现了一个很重要的规律，都有 $0~ \cdots ~0 ~1 ~6 ~9$。

所以猜测所有情况都可以由若干个 $0$ 和 $1~6~9$ 构成。

再试一试九位数，发现也是如此。

于是，改了改暴力程序，让程序输出符合条件的平方数，如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
multiset<int>s;
map<multiset<int>,int>mp;
int main()
{
	multiset<int>tmp;
	tmp.insert(0),tmp.insert(0),tmp.insert(0),tmp.insert(0),tmp.insert(0),tmp.insert(0),tmp.insert(1),tmp.insert(6),tmp.insert(9);//同样是九位数的程序，其他情况注意更改参数
	for(int i=1;i<=200000;++i)
	{
		long long k=1ll*i*i;
		if(k<100000000) continue;
		if(k>999999999) break;
		while(k) s.insert(k%10),k/=10;
		if(s==tmp) printf("%lld\n",1ll*i*i);
		s.clear();
	}
	return 0;
}
```

先试一试五位数的，发现程序给的是：

```
10609
16900
19600
61009
90601
96100
```

研究了一下，发现首先又 $1690\cdots$、$1960\cdots$ 和 $9610\cdots$，这三个很显然，都是 $169$、$196$ 和 $961$ 乘以了 $10^k$，其中 $k$ 为偶数，所以一定是平方数。

剩下的就是 $10\cdots60\cdots90\cdots$，也就是 $169$ 的 $1$ 与 $6$ 之间和 $6$ 与 $9$ 之间插入相同数量的零，再在后面放若干个零构成的，首先因为插入的零是偶数，并且总数字个数是奇数，再加上有 $169$ 三个数字，所以后面的零一定是偶数个，所以后面加的一定正确，只需要验证 $10\cdots60\cdots9$ 是否一定正确即可，发现就是 $10\cdots3$ 的平方，所以一定正确。

那么同理 $961$ 的 $1$ 与 $6$ 之间和 $6$ 与 $9$ 之间插入相同数量的零，再在后面放若干个零构成的数也一定是平方数，也是正确的。

使用暴力程序在七位数和九位数验证，发现是正确的。

再计算一下我们发现了多少个平方数了，在其中插入的零可以是 $[0,\frac{n-1}2-1]$ 个，一共有 $\frac{n-1}2$ 个，$169$ 和 $961$都可以，一共有 $n-1$ 个，再加上 $1960\cdots$ 的一个，刚好 $n$ 个。

其实发现还有形如 $61009$ 之类的数也满足条件，但是我们已经不需要了。

根据上面发现的构造方案可以很轻松的写出程序。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
long long T,n,a,sum,num;
int main()
{
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld",&n);
		if(n==1){puts("1");continue;}//注意特判n=1
		printf("169");
		for(int i=4;i<=n;++i) printf("0");
		puts("");
		printf("961");
		for(int i=4;i<=n;++i) printf("0");
		puts("");
		printf("196");
		for(int i=4;i<=n;++i) printf("0");
		puts("");
		for(int i=1;i<n/2;++i)
		{
			printf("1");
			for(int j=1;j<=i;++j) printf("0");
			printf("6");
			for(int j=1;j<=i;++j) printf("0");
			printf("9");
			for(int j=3+2*i;j<n;++j) printf("0");
			puts("");
			printf("9");
			for(int j=1;j<=i;++j) printf("0");
			printf("6");
			for(int j=1;j<=i;++j) printf("0");
			printf("1");
			for(int j=3+2*i;j<n;++j) printf("0");
			puts("");
		}
	}
	return 0;
}
```

---

## 作者：No_Rest (赞：10)

# 思路

这道题我们可以递推先预处理 $n \le 99$ 的所有答案。

当 $n=1$ 时，答案为 $1$ (当然 $4,9$ 也行)，$n=3$ 时，答案为 $169,196,961$。

接下来考虑当 $n \ge 5$ 时的情况。显然，前 $n-2$ 个答案都可以通过将长度为 $n-2$ 的所有答案末尾都添加两个 $0$ 得到。

设 $x = \displaystyle \frac{n-1}{2}$。则又因为 $(10^x + 3)^2 = 10^{2x} + 6 \times 10^x + 9$，$(3 \times 10^x + 1)^2 = 9 \times 10^{2x} + 6 \times 10^x + 1$，所以 $10 \cdots 060 \cdots 09$ 和 $90 \cdots 060 \cdots 01$（每段共 $x-1$ 个 $0$）都为完全平方数。

这样我们就凑齐了 $n$ 个平方数，每个平方数都由 $1$ 个 $1$，$1$ 个 $6$，$1$ 个 $9$，$n-3$ 个 $0$ 组成。

时间复杂度：$\mathcal O(n^2 + Tn)$。

# 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll maxn = 1e2 + 5;
ll read(){
	char ch;
	ll f = 0, r = 0;
	ch = getchar();
	while(ch > '9' || ch < '0') f |= ch == '-', ch = getchar();
	while(ch <= '9' && ch >= '0') r = (r << 3) + (r << 1) + (ch ^ 48), ch = getchar();
	return f ? -r : r;
}
ll t = read(), n;
string s[maxn][maxn];
void solve(){
	n = read();
	for(int i = 1; i <= n; ++i) cout << s[n][i] << endl;
}
int main(){
	s[1][1] = "1", s[3][1] = "169", s[3][2] = "196", s[3][3] = "961";//初始化
	for(int i = 5; i <= 99; i += 2){
		for(int j = 1; j <= i - 2; ++j) s[i][j] = s[i - 2][j] + "00";//前 i - 2 个可以由前面的接上两个零得到
		s[i][i - 1] = "1";//10···060···09
		for(int j = 1; j <= i / 2 - 1; ++j) s[i][i - 1] = s[i][i - 1] + "0";
		s[i][i - 1] = s[i][i - 1] + "6";
		for(int j = 1; j <= i / 2 - 1; ++j) s[i][i - 1] = s[i][i - 1] + "0";
		s[i][i - 1] = s[i][i - 1] + "9";
		s[i][i] = "9";//90···060···01
		for(int j = 1; j <= i / 2 - 1; ++j) s[i][i] = s[i][i] + "0";
		s[i][i] = s[i][i] + "6";
		for(int j = 1; j <= i / 2 - 1; ++j) s[i][i] = s[i][i] + "0";
		s[i][i] = s[i][i] + "1";
	}
	for(; t; --t) solve();
    return 0;
}
```

---

## 作者：IceKylin (赞：4)

# CF1916D Mathematical Problem 题解

诈骗题，但场上被卡了很久，差评。

考虑 

$$(10^\frac{n-1}{2}+3)^2=10^{n-1}+6\times10^\frac{n-1}{2}+9$$

以及 

$$(3\times10^\frac{n-1}{2}+1)^2=9\times 10^{n-1}+6\times 10^\frac{n-1}{2}+1$$

这两个数在十进制下各包含 $1$ 个数码 $1$，$1$ 个数码 $6$，$1$ 个数码 $9$ 和 $(n-3)$ 个数码 $0$。

再考虑将完全平方数 $x$ 变为 $100x$，显然也是完全平方数，且唯一区别是十进制下末尾多了 $2$ 个数码 $0$。

所以可以想到如下构造方式：

设答案为 $a_{n,1},a_{n,2},a_{n,3},\cdots,a_{n,n}$ 这一序列。

当 $n=1$ 时，存在一组答案为 $1$。

当 $n=3$ 时，存在一组答案为 $169,196,961$。

当 $n>3$ 时，对于 $1\le i\le n-2$，令 $a_{n,i}=100\times a_{n-2,i}$，再令 $a_{n,n-1}=(10^\frac{n-1}{2}+3)^2, a_{n,n}=(3\times 10^\frac{n-1}{2}+1)^2$，易证该构造符合题意。

代码详见 [link](https://codeforces.com/contest/1916/submission/239693786)。

---

## 作者：Phartial (赞：3)

# CF1916D Mathematical Problem 题解

首先不难注意到这样一件事：如果 $x$ 是一个平方数，则 $100x$ 也是一个平方数，这给了我们一种在方案后面加两个 $0$ 的操作。

我们有 $10^{n-1}+6\times 10^{\frac{n-1}{2}}+9=(10^{\frac{n-1}{2}}+3)^2$，$9\times10^{n-1}+6\times 10^{\frac{n-1}{2}}+1=(3\times10^{\frac{n-1}{2}}+1)^2$。于是这两个数是数位构成为 $\{1,6,9\}$ 的数位为 $n$ 的完全平方数。

$n=3$ 时我们额外构造一个 $196=14^2$，之后的 $n$ 的方案都可以通过将 $n-2$ 的方案后加两个 $0$ 并加上 $10^{n-1}+6\times 10^{\frac{n-1}{2}}+9$ 和 $9\times10^{n-1}+6\times 10^{\frac{n-1}{2}}+1$ 两组数得到。

需要特判 $n=1$。

```cpp
#include <iostream>

using namespace std;

int n;

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int tt = 1;
  cin >> tt;
  for (; tt--; ) {
    cin >> n;
    if (n == 1) {
      cout << "1\n";
      continue;
    }
    for (int i = 0; i < n / 2; ++i) {
      cout << '1' << string(i, '0') << '6' << string(i, '0') << '9' << string(n - 3 - i * 2, '0') << '\n';
    }
    for (int i = 0; i < n / 2; ++i) {
      cout << '9' << string(i, '0') << '6' << string(i, '0') << '1' << string(n - 3 - i * 2, '0') << '\n';
    }
    cout << "196" << string(n - 3, '0') << '\n';
  }
  return 0;
}
```


---

## 作者：__3E24AC7002AD9292__ (赞：3)

找规律。

发现 $n=3$ 时，$A_3=\{169,196,961\}$ 是一个解，那么 $n=5$ 时 $A_5=\{16900,19600,96100,y,z\}$ 也是一个解，$y,z$ 暂时未知，因为 $f(x)=x\times 10^2=(10x)^2$ 是 $A_3$ 对 $A_5$ 的单射。

发现 $16900=130^2$，而 $10609=103^2$，$96100=310^2$，而 $90601=301^2$，找规律发现在 $169$ 和 $196$ 中间插入 $0$ 也是可以做的。

对于一个奇数 $n$，$A_n$，$A_{n+2}=A'\cup\{1\times10^{n-1}+6\times10^{\frac{n-1}{2}}+9,9\times10^{n-1}+6\times10^{\frac{n-1}{2}}+1\}$，$A'$ 表示 $A_n$ 通过一一映射 $f$ 形成的集合。

---

## 作者：Pt_crN (赞：3)

看到题想一会儿发现 $99$ 位的数 int128 都存不下。所以钦定这是思维结论题。

考虑从 $n$ 小的情况看起。看到 $n=3$ 时有 $169,196,961$，所以 $n=5$ 自然有 $16900,96100,19600$。

然后呢？发现 $16900=130\times 130$，如果把 $0$ 放到 $1,3$ 中间会怎么样？发现 $103\times 103=10609$。然后发现 $301$ 也可以，$n>3$ 以此类推。做完了。

所以结论就是 $1000\cdots 06000\cdots 09000\cdots$ 或是将 $1,9$ 位置互换的数可以。加上 $196000\cdots$ 刚好 $n$ 个。

很有意思啊！幸好做的不慢。

code：

```cpp
int n,m;
void Yorushika(){
	scanf("%d",&n);
	if(n==1)return puts("1"),void();
	rep(i,0,(n-3)/2){
		pc('1');
		rep(j,1,i)pc('0');
		pc('6');
		rep(j,1,i)pc('0');
		pc('9');
		rep(j,1,n-3-2*i)pc('0');
		puts("");
	}
	rep(i,0,(n-3)/2){
		pc('9');
		rep(j,1,i)pc('0');
		pc('6');
		rep(j,1,i)pc('0');
		pc('1');
		rep(j,1,n-3-2*i)pc('0');
		puts("");
	}
	printf("196");
	rep(i,1,n-3)pc('0');
	puts("");
}
signed main(){
	int t=1;
		scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

## 作者：E_firework (赞：2)

神秘构造题。

样例告诉我们，当 $n=3$ 时有一组解为 $169=13^2,196=14^2,961=31^2$，我们考虑在这一组解的基础上扩展得到答案。因为 $13$ 乘 $13$ 与 $31$ 乘 $31$ 并不涉及进位，当 $n>3$ 时，我们可以尝试在这两个数字中间和末尾插入若干个 $0$。得到的数字的数位的集合是一样的，都包含 $1,6,9$ 各一个加上 $n-3$ 个 $0$。而 $14$ 乘 $14$ 涉及了进位，只能 $14$ 的末尾添上若干个 $0$，得到的数字数位的集合也一样。然后我们正好得到了 $n$ 个不同的数字。

举例：当 $n=7$ 时，一组答案为：

$$
1690000=1300^2\\
1060900=1030^2\\
1006009=1003^2\\
9610000=3100^2\\
9060100=3010^2\\
9006001=3001^2\\
1960000=1400^2
$$

然后求答案时没必要做大整数乘法，直接根据答案的规律输出就行了。

需要特判 $n=1$ 的情况。

code:

```cpp
#include<bits/stdc++.h>
#define LL long long
#define mes(s, x) memset(s, x, sizeof s)
using namespace std;
inline LL read(){char c;c = getchar();while(!(('0' <= c && c <= '9') || c == '-')) c = getchar();bool flag = 0;if(c == '-'){flag = 1;c = getchar();}LL tot = 0;while('0' <= c && c <= '9'){tot = 10 * tot + c - '0';c = getchar();}return flag ? -tot : tot;}
char s[105];
int main(){
	int T = read(), n;
	while(T--){
		n = read();
		if(n == 1){
			puts("1");
			continue;
		}
		mes(s, '0');
		s[n] = '\0';
		s[0] = '1', s[1] = '9', s[2] = '6';
		puts(s);
		s[0] = s[1] = s[2] = '0';
		for(int x = 1; x <= n / 2; x++){
			s[0] = '1', s[x] = '6', s[x << 1] = '9';
			puts(s);
			s[0] =  s[x] = s[x << 1] = '0';
		}
		for(int x = 1; x <= n / 2; x++){
			s[0] = '9', s[x] = '6', s[x << 1] = '1';
			puts(s);
			s[0] =  s[x] = s[x << 1] = '0';
		}
	}
	return 0;
}
```

---

## 作者：User_Unauthorized (赞：2)

首先我们可以发现，若 $x$ 为 $k$ 位的完全平方数，那么 $100 \cdot x$ 一定是 $k + 2$ 位的完全平方数。

这启示我们寻找当 $n$ 较小时是否存在某个合法完全平方数集合不小于 $99$，而通过对平方数的枚举我们可以发现，当 $n = 13$ 时存在一些平方数集合大小超过 $99$。因此可以使用这一集合处理所有 $n \ge 13$ 的询问。

对于 $n < 13$ 的询问可以通过枚举所有满足平方后的长度不超过 $11$ 的数，其个数为 $\sqrt{10^{11}}$ 级别。预处理出答案即可。

[Submission](https://codeforces.com/contest/1916/submission/239697493)。

---

## 作者：Drind (赞：1)

### 题目解析

给定一个 $n$，求输出 $n$ 个位数为 $n$ 的数字满足既是平方数，又拥有同样多个同种数字，$n$ 为奇数。

首先可以想出一个 $O(10^{\frac{n}{2}})$ 的做法就是枚举平方数，然后随便设置一个条件（这里可以随便选一个平方数，然后把他的数字全部打到表里再爆搜），但是 $n\le 99$，完全跑不了一点儿。

我们发现，当 $n=13$ 的时候，随便打就已经会有几百个平方数符合要求了，并且一个平方数末尾加上两个 0 还是平方数（注意 $n$ 为奇数），所以我们在处理 $13\le n\le 99$ 的情况时就可以打表解决。

剩下的爆搜即可，为了防止超时也可以打一个表。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;

int re[10]={1,3,2,2,1,1,1,0,1,1};//数字表，re[i] 代表数字 i 要出现 re[i] 次，这个表随便填都可以，建议随便找个平方数然后把他的各位数字整进去
int re11[10]={0,2,2,1,0,2,2,0,0,2};
int re9[10]={1,0,1,0,1,1,2,0,1,2};
int re7[10]={1,1,0,0,1,1,1,1,1,0};//这里使用了 1024*1024 ，或许其他数字符合条件的较少？
int vis[10];


bool check(int x){//暴力检查
	if(x<1e12) return false;
	for(int i=0;i<=9;i++) vis[i]=0;
	for(int i=1;i<=13;i++){
		vis[x%10]++; x/=10;
	}
	for(int i=0;i<=9;i++){
		if(vis[i]!=re[i]) return false;
	}
	return true;
}

bool check11(int x){
	if(x<1e10) return false;
	for(int i=0;i<=9;i++) vis[i]=0;
	for(int i=1;i<=11;i++){
		vis[x%10]++; x/=10;
	}
	for(int i=0;i<=9;i++){
		if(vis[i]!=re11[i]) return false;
	}
	return true;
}

bool check9(int x){
	if(x<1e8) return false;
	for(int i=0;i<=9;i++) vis[i]=0;
	for(int i=1;i<=9;i++){
		vis[x%10]++; x/=10;
	}
	for(int i=0;i<=9;i++){
		if(vis[i]!=re9[i]) return false;
	}
	return true;
}

bool check7(int x){
	if(x<1e6) return false;
	for(int i=0;i<=9;i++) vis[i]=0;
	for(int i=1;i<=7;i++){
		vis[x%10]++; x/=10;
	}
	for(int i=0;i<=9;i++){
		if(vis[i]!=re7[i]) return false;
	}
	return true;
}

int blank[100]={0};
int blank11[100]={0};
int blank9[100]={0};这里填的是打出来的表，但是影响观感我就不写了

inline void fake_main(){
	int n; cin>>n;
	int ans=0;
	if(n>=13){
		for(int i=0;i<n;i++){
			cout<<blank[i]*blank[i];//所以记得输出平方，赛时因为这个吃了一发
			for(int j=14;j<=n;j++) cout<<0; cout<<"\n";//剩下的全输出 0
		}
	}else if(n==11){
		for(int i=0;i<11;i++){
			cout<<blank11[i]*blank11[i]<<"\n";
		}
	}else if(n==9){
		for(int i=0;i<9;i++){
			cout<<blank9[i]*blank9[i]<<"\n";
		}
	}else if(n==7){
		for(int i=1;i*i<1e7;i++){//爆搜枚举所有七位平方数
			if(ans>=n) return;
			if(check7(i*i)){
				ans++;
				cout<<i*i<<"\n";
			}	
		}
	}else if(n==5){//样例里就有，照样输出即可
		cout<<"16384\n";
		cout<<"31684\n";
		cout<<"36481\n";
		cout<<"38416\n";
		cout<<"43681\n";
	}else if(n==3){
		cout<<"169\n";
		cout<<"196\n";
		cout<<"961\n";
	}else if(n==1){
		cout<<"1\n";
	}
}

signed main(){
	ios::sync_with_stdio(false);
	int t; cin>>t;
	while(t--) fake_main();
}
```

---

## 作者：1234567890sjx (赞：1)

很人类智慧的一题！

首先构造 $n-1$ 个长度为 $n$ 的平方数是很平凡的。容易发现：所有由一个 $1$，一个 $3$，$\lfloor\frac{n}{2}\rfloor-1$ 个 $0$ 组成的没有前导零的数的平方恰好全部符合条件。

然而这样还少一个这样的数。

发现 $(13\times 10^{\lfloor\frac{n}{2}\rfloor+1})^2$ 和 $(14\times 10^{\lfloor\frac{n}{2}\rfloor+1})^2$ 这两组数是符合条件的。所以只需要构造完上面的 $n-1$ 组数，然后在最后加上 $(14\times 10^{\lfloor\frac{n}{2}\rfloor+1})^2$ 即可。

时间复杂度 $O(\sum n^2)$。

```python
T = int(input())
while (T > 0):
    n = int(input())
    if (n == 1):
        print(1)
    else:
        for i in range(0, n // 2):
            s = 1
            for j in range(0, n // 2):
                if (i == j):
                    s = s * 10 + 3
                else:
                    s = s * 10
            print(s * s)
            s = 3
            for j in range(0, n // 2):
                if (i == j):
                    s = s * 10 + 1
                else:
                    s = s * 10
            print(s * s)
        s = 14
        for i in range(1, n // 2):
            s = s * 10
        print(s * s)
    T = T - 1
```



---

## 作者：Xiphi (赞：0)

考虑找规律。首先发现 $3$ 位数的情况如下：


1. $169(13^3)$
1. $196(14^2)$
1. $961(31^2)$

接着找规律，猜想 $5$ 位数可能也跟 $1,6,9$ 这三个数有关（这一步非常人类智慧），我打了个 $10000-99999$ 的平方数的表，暴力用眼睛搜出了这样一组：

1. $16900(130^2)$
1. $96100(310^2)$
1. $10609(103^2)$
1. $90601(301^2)$
1. $19600(140^2)$

考虑后边的平方数，和上一个尝试做联系，发现都是 $1...0...3...0...$，$3...0...1...0$，$14...0...$ 的形式的数的平方（当然，可能有某些段不存在 $0$）。

然后对于第一种以及第二种的形式，会有 $\lfloor n/2\rfloor$ 个（因为共有 $\lfloor n/2\rfloor$ 个 $0$）。

对于第三种形式，只有一个。

然后就很简单了，枚举每个可能的形式，输出其平方即可，本人用高精度实现的。

代码见[此](https://codeforces.com/contest/1916/submission/239702016)。

---

## 作者：sto_5k_orz (赞：0)

找规律神题，没有场切，我太菜了。

显然 $x$ 是平方数时，$100x$ 也是平方数。

然后呢？

考虑 $10^{2x}+60^{x}+9$ 一定是平方数，因为 $10^{2x}+60^{x}+9=(10^x+3)^2$。

同理可得 $90^{2x}+60^{x}+1$ 也是平方数，因为 $90^{2x}+60^{x}+1=(30^x+1)^2$。

然后在后面补 $0$ 即可，这样每个数都是由 $1$ 个 $1$，$1$ 个 $6$，$1$ 个 $9$，$n-3$ 个 $0$ 构成的。

但是这样只有 $2\lfloor\dfrac{n}{2}\rfloor=n-1$ 个平方数啊，还有一个咋整？

不难发现 $196$ 是个平方数，所以再写一个 $196\times 10^{n-3}$ 即可。

注意特判 $n=1$。

```cpp
#include<bits/stdc++.h> 
using namespace std;
int main() {
	ios::sync_with_stdio(0);
	int t; cin >> t;
	while(t--) {
		int n; cin >> n;
		if(n == 1) {
			cout << "1\n";
			continue;
		}
		for(int i = 0; i < n / 2; i++) {
			cout << "1" << string(i, '0') << '6' << string(i, '0') << '9' << string(n - 3 - i * 2, '0') << '\n';
		}
		for(int i = 0; i < n / 2; i++) {
			cout << "9" << string(i, '0') << '6' << string(i, '0') << '1' << string(n - 3 - i * 2, '0') << '\n';
		}
		cout << "196" << string(n - 3, '0') << '\n';
	}
	return 0;
}
```

---

