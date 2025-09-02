# Hash Killer Phantasm

## 题目背景

本题为给定 base 和 mod 的情况下卡双哈希，参考了 [北航 2024 国庆思维训练特别赛](https://accoding.buaa.edu.cn/contest-ng/index.html#/1109)，向出题人表示感谢。

## 题目描述

请你找到任意两个字符串，使它们满足以下条件：
- 仅由小写字母 $\tt{a}\sim \tt{z}$ 组成；
- 两者长度相同，且长度 $n$ 满足：$1\leq n\leq 10^4$；
- 两者不完全相同，却在给定的 $(b_1,p_1)$ 和 $(b_2,p_2)$ 下有着一致的哈希值；

本题中参考的 hash 代码为：

```cpp
int strhash(const string &s, int b, int p) {
    int val = 0;
    for (int i = 0; i < s.length(); i++)
        val = (1ll * val * b + s[i] - 'a' + 1) % p;
    return val;
}
```

## 说明/提示

### 数据范围

- 对于 $40\%$ 的测试数据，$31\leq b_1,b_2<p_1,p_2\leq 10007$；
- 对于所有测试数据，$31\leq b_1,b_2<p_1,p_2\leq 10^9+7$；

测试数据保证 $p$ 一定是质数。

## 样例 #1

### 输入

```
31 131
37 233```

### 输出

```
ylnylnaylaylylnylnaylylnaylyln
ylnaylaylylnylnaylylnaylylnyln```

# 题解

## 作者：bcdmwSjy (赞：11)

这个题非常简单，只需要暴力就行了，根本用不着构造。

根据生日悖论，只需要随 $\sqrt{p}$ 个字符串就会出现哈希相同的字符串。所以先随出一组在 $(b_1,p_1)$ 下冲突的字符串，再以它们两个为字符集，随机生成新的字符串。不难发现，生成的所有字符串在 $(b_1,p_1)$ 下都是冲突的，因为它们的组成部分的哈希都是一样的，接着随出在 $(b_2,p_2)$ 下冲突的字符串就行了。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

mt19937 rnd(random_device{}());

string str_rand(int n){
	string ans;
	for (int i=0;i<n;i++) ans.push_back(rnd()%26+'a');
	return ans;
}

string str_rand2(int n,const string &s1,const string &s2){
	string ans;
	for (int i=0;i<n;i++) ans+=(rnd()&1?s1:s2);
	return ans;
}

int strhash(const string &s,int b,int p){
    int val=0;
    for (int i=0;i<int(s.length());i++) val=(1ll*val*b+s[i]-'a'+1)%p;
    return val;
}

unordered_map<int,string> mp;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int b1,p1,b2,p2;
	cin>>b1>>p1;
	string s1,s2;
	while (true){
		string s=str_rand(7);
		int h=strhash(s,b1,p1);
		auto it=mp.find(h);
		if (it!=mp.end() and it->second!=s){
			s1=it->second;
			s2=s;
			break;
		}else{
			mp[h]=s;
		}
	}
	mp.clear();
	cin>>b2>>p2;
	while (true){
		string s=str_rand2(32,s1,s2);
		int h=strhash(s,b2,p2);
		auto it=mp.find(h);
		if (it!=mp.end() and it->second!=s){
			cout<<it->second<<"\n"<<s;
			// cout<<"\n";
			// cout<<strhash(it->second,b1,p1)<<" "<<strhash(s,b1,p1)<<"\n";
			// cout<<strhash(it->second,b2,p2)<<" "<<strhash(s,b2,p2)<<"\n";
			break;
		}else{
			mp[h]=s;
		}
	}
	return 0;
}
```

~~后记：题目中计算字符串哈希的代码会爆警告，建议改一下。~~

---

## 作者：WorldMachine (赞：4)

相当于要找到同时满足 $\sum\limits_{i=1}^{n}(b_1^{n-i}\bmod p_1)a_i=0$ 和 $\sum\limits_{i=1}^{n}(b_2^{n-i}\bmod p_2)a_i=0$ 的序列 $a$。使用 CRT，问题转化为求解 $\sum\limits_{i=1}^{n}(b'_{n-i}\bmod p_1p_2)a_i=0$，其中 $b'_i\equiv b_1^i\pmod{p_1}$，$b'_i\equiv b_2^i\pmod{p_2}$，用 Hash Killer Extra 的做法即可。

但让 $p_1=p_2$ 且 $b_1\not=b_2$ 不就炸了吗。

换一种方式，先求出 $(b_1,p_1)$ 的一组碰撞 $s_1,s_2$，设其长度为 $l$，则以字符集为 $\{s_1,s_2\}$，求出 $(b_2^l\bmod p_2,p_2)$ 的一组碰撞即可。

这样长度为平方级别的，然后就爆炸了。

细究其原因，是因为之前的构造方法只用到了 $\{\texttt{a},\texttt{b},\texttt{c}\}$ 这三个字母，如果能把字符集扩得更大就好了。

其实可以直接随机 $\mathcal O(\sqrt p)$ 个字符串，根据生日悖论，这样有冲突的概率很大。当然不需要真的随机 $\mathcal O(\sqrt p)$ 个，随机一个长度为 $\mathcal O(n+\sqrt p)$ 的字符串，把每个长度为 $n$ 的子串拿出来即可。

第一次随机，字符集大小为 $26$，长度开到 $16$ 就够了，而第二次大小为 $2$，长度需要开得更大，开到 $256$ 就行。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 3e5 + 5, l1 = 16, l2 = 256;
int b1, p1, b2, p2, pw[N], h[N], B = 1, H[2];
char str[N], s[2][20], S[260];
unordered_map<int, int> mp;
int Hash(int l, int r, int p) { return (h[r] - (ll)h[l - 1] * pw[r - l + 1] % p + p) % p; }
bool chk(int x, int y, int l) {
	bool flg = 0;
	for (int i = 0; i < l; i++) if (s[x - i] != s[y - i]) { flg = 1; break; }
	return flg;
}
void hack1() {
	for (int i = 1; i < N; i++) str[i] = 'a' + rand() % 26;
	pw[0] = 1;
	for (int i = 1; i < N; i++) pw[i] = (ll)pw[i - 1] * b1 % p1, h[i] = ((ll)h[i - 1] * b1 + str[i] - 'a' + 1) % p1;
	for (int i = l1; i < N; i++) {
		int h = Hash(i - l1 + 1, i, p1), x = mp[h];
		if (!x) mp[h] = i;
		else if (chk(x, i, l1)) {
			for (int j = 1; j <= l1; j++) s[0][j] = str[x - l1 + j], s[1][j] = str[i - l1 + j];
			return;
		}
	}
}
void hack2() {
	for (int i = 1; i <= l1; i++) B = (ll)B * b2 % p2, H[0] = ((ll)H[0] * b2 + s[0][i] - 'a' + 1) % p2, H[1] = ((ll)H[1] * b2 + s[1][i] - 'a' + 1) % p2;
	for (int i = 1; i < N; i++) str[i] = rand() & 1;
	pw[0] = 1;
	for (int i = 1; i < N; i++) pw[i] = (ll)pw[i - 1] * B % p2, h[i] = ((ll)h[i - 1] * B + H[str[i]]) % p2;
	mp.clear();
	for (int i = l2; i < N; i++) {
		int h = Hash(i - l2 + 1, i, p2), x = mp[h];
		if (!x) mp[h] = i;
		else if (chk(x, i, l2)) {
			for (int j = x - l2 + 1; j <= x; j++) printf("%s", s[str[j]] + 1);
			puts("");
			for (int j = i - l2 + 1; j <= i; j++) printf("%s", s[str[j]] + 1);
			return;
		}
	}
}
int main() {
	srand(time(0));
	scanf("%d%d%d%d", &b1, &p1, &b2, &p2);
	hack1(), hack2();
}
```

---

## 作者：xrz114514 (赞：1)

# P12201 题解

个人以为没有蓝题的难度，最多也就绿。

## 题面

没啥好说的，就是给你一个双哈希的模数和底数，让你 hack 掉它。

## 思路

根据生日悖论~~和我们写单哈希的经验~~表明，随便造一组有 $10^5$ 个字符串，每个字符串长度为 $10$ 是有大概率能卡掉模数在 `int` 范围内的单哈希，我们可以先将第一个模数和底数用随机的方式卡掉，并且找出冲突的两个，设其为 $a$，$b$。

可以发现，假设 $x$ 和 $y$ 哈希冲突了，那 $x + x + \cdots + x$ 和 $y + y + \cdots y$ 也哈希冲突，其中 $+$ 运算符表示将两字符串进行拼接操作。原理很简单，由于 $\operatorname{hash}(x) \equiv \operatorname{hash}(y) \pmod p$，所以 $\operatorname{hash}(x) \cdot (b^{\lvert x \rvert} + 1) \equiv \operatorname{hash}(y) \cdot (b^{\lvert y \rvert} + 1) \pmod p$，就是 $\operatorname{hash}(x + x) \equiv \operatorname{hash}(y + y) \pmod p$。

有了以上条件，就容易了。又根据生日悖论，我们可以进行随机数，如果为奇数，就插个 $a$，否则插 $b$，最后看有没有两个随机出的字符串在第二个模数和底数冲突。如果有，则根据上面所述，它们在第一个模数和底数冲突且在第二个模数和底数冲突，即为答案。

## 代码

```cpp
#pragma G++ optimize("Ofast")
#pragma G++ optimize("unroll-loops")
#pragma G++ optimize("inline")
#pragma G++ optimize("-ffast-math")
#pragma G++ optimize("-fstrict-aliasing")
#pragma G++ optimize("-funsafe-loop-optimizations")
#include <bits/stdc++.h>
#include <bits/extc++.h>
//#include <windows.h>
#define pque priority_queue
#define fi first
#define se second
#define un unsigned
#define si signed
//#define int long long

using namespace std;
using namespace __gnu_pbds;
using ll = long long;
using LL = unsigned long long;
using Int = unsigned int;
using ld = double;
using Ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

const int N = 1e5 + 1;

int m1, b1, m2, b2;
string a, b, x, y, u, v, s[N], t[N];

int strhash(const string &s, int b, int p) {
    int val = 0;
    for (int i = 0; i < s.length(); i++)
        val = (1ll * val * b + s[i] - 'a' + 1) % p;
    return val;
}

int main(){
	//freopen("","r", stdin);
	//freopen("", "w", stdout);
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> b1 >> m1 >> b2 >> m2;
	srand(time(0));
	mt19937 gen(rand());//这是一种随机数
	while(1){
		map<int, int> mp;
		int flag = 0;
		for(int i = 1; i <= (int)1e5; ++i){
			int has = 0;
			for(int j = 1; j <= 10; ++j){
				ll x = gen();
				s[i].push_back('a' + x % 26);
			}
            has = strhash(s[i], b1, m1);
			if(mp.count(has) && s[mp[has]] != s[i]){
				a = s[mp[has]], b = s[i], flag = 1;
				break;
			}
			mp[has] = i;
		}
		if(flag){
			break;
		}
	}
	while(1){
		map<int, int> mp;
		int flag = 0;
		for(int i = 1; i <= (int)1e5; ++i){
			int has = 0;
			for(int j = 1; j <= 10; ++j){
				ll x = gen();
				t[i] += (x % 2 == 0 ? a : b);
			}
			has = strhash(t[i], b2, m2);
			if(mp.count(has) && t[mp[has]] != t[i]){
				x = t[mp[has]], y = t[i], flag = 1;
				break;
			}
			mp[has] = i;
		}
		if(flag){
			break;
		}
	}
	cout << x << '\n' << y;
	return 0;
}
```

~~然后的然后，这道水蓝色的题就这么水淋淋的过去了。~~

---

## 作者：_H17_ (赞：1)

## 题目分析

哈希冲突的概率可以转化为生日悖论，相当于有 $p$ 天，同时有 $n$ 个人，求生日相同的概率。

根据生日悖论的结论：有 $n$ 天，其中有相同生日的人时，期望总人数是 $O(\sqrt{n})$ 的（具体证明见 [ OI-wiki](https://oi-wiki.org/math/number-theory/pollard-rho/#%E7%94%9F%E6%97%A5%E6%82%96%E8%AE%BA)）。

根据生日悖论，模数是 $p$ 的哈希期望上需要 $O(\sqrt{p})$ 次，所以随即多个字符串依次判断，期望时间复杂度 $O(l\times\sqrt{p}\log{p})$。

其中 $O(\log p)$ 是 `map` 的时间复杂度，可以用哈希优化。

这里 $l$ 别太小，有随机性即可（注意下文由于是类似 $\texttt{01}$ 串的东西，所以 $l$ 应该取大一点）。

但是我们需要卡双哈希，很显而易见的是：对于两个卡掉 $b_1,p_1$ 的字符串 $x,y$，把它们当作两个字符（显然这两个串是在 $b_2,p_2$ 哈希意义下不同的，但是一直可以卡 $b_1,p_1$，所以可以当字符）。

然后我们使用同样的方法把 $x,y$ 当作字符进行随机，搞出一个也满足 $b_2,p_2$ 的即可。

时间复杂度 $O(l\times \sqrt{n}\log n)$。

其中 $O(\log n)$ 是 `map` 的时间复杂度，可以用哈希优化。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int b1,p1,b2,p2;
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<char>randchar('a','z'),randindex(0,1);
int strhash(string s, int b, int p) {
    int val = 0;
    for (int i = 0; i < s.length(); i++)
        val = (1ll * val * b + s[i] - 'a' + 1) % p;
    return val;
}
map<int,string>hashval1,hashval2;
string x,y;
string randstring1(int len=7){//生成字符串
    string s;
    for(int i=1;i<=len;i++)
        s+=randchar(rnd);
    return s;
}
bool check1(string s,string&x,string&y){//检查第一个哈希
    int hashv=strhash(s,b1,p1);
    if(hashval1.count(hashv)){
        x=s,y=hashval1[hashv];
        if(x==y){
            x=y="";
            return 1;
        }
        return 0;
    }
    hashval1[hashv]=s;
    return 1;
}
string randstring2(int len=37){//对“字符”生成字符串
    string s;
    for(int i=1;i<=len;i++)
        s+=(randindex(rnd)?x:y);
    return s;
}
void check2(string s){//检查第二个哈希
    int hashv=strhash(s,b2,p2);
    string x,y;
    if(hashval2.count(hashv)){
        x=s,y=hashval2[hashv];
        if(x==y)
            return;
        cout<<x<<'\n'<<y;
        exit(0);
        return;
    }
    hashval2[hashv]=s;
    return;
}
int main(){
    cin>>b1>>p1>>b2>>p2;
    while(check1(randstring1(),x,y));//找“字符”
    while(1)
        check2(randstring2());
    return 0;
}
```

---

## 作者：ELECTRODE_kaf (赞：1)

只要随机生成 $\sqrt p$ 个字符串就会出现哈希值相同的字符串（这里涉及一个数学概率论中一个有趣的悖论：[birthday paradox](https://baike.baidu.com/item/%E7%94%9F%E6%97%A5%E6%82%96%E8%AE%BA/2715290)），所以随机生成字符串并检验，数量级可以接受。先考虑其中一组哈希，随机拼接字母 `a` 到 `z` 生成字符串并用一个 `map` 维护是否存在此前生成的字符串与新生成的字符串哈希值相同，并随时记录每个哈希值所对应的字符串，直到获得一组配对，再每次随机选择这对字符串中的一个拼接出一个新的字符串，这样可以保证第一组哈希值保持相同，得到第二组配对。尝试不同的参数作为两次生成的字符串的长度，实测很多都能通过（比如我用的 `11` 和 `45`）。使用 `mt19937 rnd(random_device{}())` 实现。

---

## 作者：lkjlkjlkj2012 (赞：0)

### 前置知识
[P12200](https://www.luogu.com.cn/problem/P12200)
### 思路
首先我们观察样例，可以发现两个字符串都是由 `yln` 和 `ayl` 组成的，而 `yln` 和 `ayl` 在 $(b_1,p_1)$ 下哈希是相等的。那么我们的思路就是找到长度相同 $s_1,s_2$ 在 $(b_1,p_1)$ 下哈希相等，再用 $s_1,s_2$ 随机组成长度相同的字符串，使得两个字符串 $ans_1,ans_2$ 在 $(b_2,p_2)$ 下哈希相等，由于组成部分在 $(b_1,p_1)$ 下哈希都相等，所以 $ans_1,ans_2$ 在 $(b_1,p_1)$ 下哈希相等。
### 代码
```cpp
// Problem: P12201 Hash Killer Phantasm
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P12201
// Memory Limit: 512 MB
// Time Limit: 1000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;
int b1, p1, b2, p2;
int strhash(const string &s, int b, int p) {
  int val = 0;
  for (int i = 0; i < s.length(); i++)
    val = (1ll * val * b + s[i] - 'a' + 1) % p;
  return val;
}
string rdstr(int le, vector<string> v) {
  string r;
  for (int i = 1; i <= le; i++) r += v[rand() % v.size()];
  return r;
}
map<int, string> mp, mp2;
int main() {
  vector<string> abc, s1s2;
  for (int i = 0; i < 26; i++) {
    string s;
    s += (char)('a' + i);
    abc.push_back(s);
  };
  int n1 = 10, n2 = 100;
  cin >> b1 >> p1 >> b2 >> p2;
  srand(time(0));
  while (true) {
    string s = rdstr(n1, abc);
    int p = strhash(s, b1, p1);
    if (mp[p] != "") {
      s1s2.push_back(mp[p]);
      s1s2.push_back(s);
      break;
    }
    mp[p] = s;
  }
  // cout << s1s2[0] << " " << s1s2[1] << endl;
  while (true) {
    string s = rdstr(n2, s1s2);
    int p = strhash(s, b2, p2);
    if (mp2[p] != "") {
      cout << mp2[p] << endl << s;
      break;
    }
    mp2[p] = s;
  }
}
```

---

