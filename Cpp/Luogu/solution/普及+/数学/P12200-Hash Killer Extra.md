# Hash Killer Extra

## 题目背景

本题为给定 base 和 mod 的情况下卡单哈希，参考了 [北航 2024 国庆思维训练特别赛](https://accoding.buaa.edu.cn/contest-ng/index.html#/1109)，向出题人表示感谢。

## 题目描述

请你找到任意两个字符串，使它们满足以下条件：
- 仅由小写字母 $\tt{a}\sim \tt{z}$ 组成；
- 两者长度相同，且长度 $n$ 满足：$1\leq n\leq 10^4$；
- 两者不完全相同，却在给定的 $b,p$ 下有着一致的哈希值；

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

- 对于 $40\%$ 的测试数据，$31\leq b<p\leq 10007$；
- 对于所有测试数据，$31\leq b<p\leq 10^9+7$；

测试数据保证 $p$ 一定是质数。

## 样例 #1

### 输入

```
37 131```

### 输出

```
bbbbbbbbbbbbbbbb
caabbbbbbcbbbbbb```

# 题解

## 作者：WorldMachine (赞：4)

相当于要找到满足 $\sum\limits_{i=1}^{n}(b^{n-i}\bmod p)a_i=0$ 的序列 $a$。考虑如下倍增过程：

- 初始时有 $n$ 个序列，第 $i$ 个序列第 $i$ 项为 $1$，其余项均为 $0$；
- 每次倍增，将每个序列按照权值从小到大排序，将相邻两个序列相减合并；
- 如果已经得到权为 $0$ 的序列则退出，否则重复上一步。

时间复杂度为 $\mathcal O(n\log^2 n)$，用 `unordered_map` 存，空间复杂度为 $\mathcal O(n)$。$n$ 取 $2^{13}$ 即可得到冲突。

```cpp
#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;
typedef long long ll;
const int N = 8192;
int b, p, pw[N], n = N;
struct vec { gp_hash_table<int, int> a; ll v; } a[N];
bool cmp(const vec &a, const vec &b) { return a.v < b.v; }
int solve() {
	sort(a, a + n, cmp);
	for (int i = 0; i < n >> 1; i++) {
		for (auto x : a[i << 1].a) a[i << 1 | 1].a[x.first] -= x.second;
		a[i << 1 | 1].v -= a[i << 1].v;
	}
	for (int i = 0; i < n >> 1; i++) {
		a[i] = a[i << 1 | 1];
		if (!a[i].v) return i;
	}
	return -1;
}
int main() {
	scanf("%d%d", &b, &p);
	pw[0] = 1;
	for (int i = 1; i < n; i++) pw[i] = (ll)pw[i - 1] * b % p;
	for (int i = 0; i < n; i++) a[i].a[i + 1] = 1, a[i].v = pw[n - i - 1];
	while (1) {
		int x = solve();
		if (x == -1) { n >>= 1; continue; }
		for (int i = 1; i <= N; i++) putchar('b'); puts("");
		for (int i = 1; i <= N; i++) putchar('b' + a[x].a[i]);
		return 0;
	}
}
```

---

## 作者：undefined_Ryan (赞：3)

啊？这题是数学构造？

$p\le10^9+7$，由生日悖论，直接随机即可。取 $n=20$，期望时间复杂度 $O(n\sqrt p)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
int b,p,k;
string rnd(int n) {
    string s;
    for (int i=1;i<=n;++i) s+=char(rand()%26+'a');
    return s;
}
int strhash(const string &s, int b, int p) {
    int val = 0;
    for (int i = 0; i < s.length(); i++)
        val = (1ll * val * b + s[i] - 'a' + 1) % p;
    return val;
}
string s;
unordered_map<int,string> mp;
int main() {
    cin>>b>>p;
    while (s=rnd(20),k=strhash(s,b,p)) {
        if (mp.count(k)&&mp[k]!=s) {
            cout<<mp[k]<<endl<<s<<endl;
            break;
        }
        else mp[k]=s;
    }
}
```

---

## 作者：lkjlkjlkj2012 (赞：0)

### 40pts
首先，看到这题，我们就想到暴力，不断随机 $2$ 个字符串，判断 hash 是否相同。

```cpp
#include <bits/stdc++.h>
using namespace std;
int b,p;
int strhash(const string &s, int b, int p) {
    int val = 0;
    for (int i = 0; i < s.length(); i++)
        val = (1ll * val * b + s[i] - 'a' + 1) % p;
    return val;
}
int main()
{
    cin>>b>>p;
    srand(time(0));
    while(true)
    {
        int len=rand()%1000+1;
        string s1,s2;
        for(int i=1;i<=len;i++)
            s1+='a'+rand()%26,s2+='a'+rand()%26;
        if(s1!=s2&&strhash(s1,b,p)==strhash(s2,b,p))
        {
            cout<<s1<<endl<<s2;
            break;
        }
    }
}
```
### 100pts
我们可以考虑生日悖论。每随机到一个字符串就在 map 中记录，发现 hash 相同但字符串不同直接输出。期望时间复杂度 $O(n\sqrt{p}\log{n})$。

至于为什么期望复杂度为 $O(\sqrt{p})$，这里先做一个感性理解：我们考虑 $n$ 个数时，他们两两之间一共有 $O(n^2)$ 对匹配，每对匹配都有 $\frac{1}{p}$ 的概率相同，所以期望匹配次数是 $O(n^2)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
int b,p;
int strhash(const string &s, int b, int p) {
    int val = 0;
    for (int i = 0; i < s.length(); i++)
        val = (1ll * val * b + s[i] - 'a' + 1) % p;
    return val;
}
string rdstr(int le)
{
    string r;
    for(int i=1;i<=le;i++)
        r+='a'+rand()%26;
    return r;
}
map<int,string> mp;
int main()
{
    int n=100;
    cin>>b>>p;
    srand(time(0));
    while(true)
    {
        string s=rdstr(n);
        int hash=strhash(s,b,p);
        if(mp[hash]!="")
        {
            cout<<mp[hash]<<endl<<s;
            break;
        }
        mp[hash]=s;
    }
}
```

---

## 作者：_H17_ (赞：0)

## 题目分析

哈希冲突的概率可以转化为生日悖论，相当于有 $p$ 天，同时有 $n$ 个人，求生日相同的概率。

根据生日悖论的结论：有 $n$ 天，其中有相同生日的人时，期望总人数是 $O(\sqrt{n})$ 的（具体证明见 [ OI-wiki](https://oi-wiki.org/math/number-theory/pollard-rho/#%E7%94%9F%E6%97%A5%E6%82%96%E8%AE%BA)）。

根据生日悖论，模数是 $p$ 的哈希期望上需要 $O(\sqrt{p})$ 次，所以随即多个字符串依次判断，期望时间复杂度 $O(l\times\sqrt{p}\log{p})$。

其中 $O(\log p)$ 是 `map` 的时间复杂度，可以用哈希优化。

这里 $l$ 别太小，有随机性即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int b,p;
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<char>randchar('a','z');
string randstring(int len=17){
    string s;
    for(int i=1;i<=len;i++)
        s+=randchar(rnd);
    return s;
}
int strhash(string s, int b, int p) {
    int val = 0;
    for (int i = 0; i < s.length(); i++)
        val = (1ll * val * b + s[i] - 'a' + 1) % p;
    return val;
}
map<int,string>hashval;
void check(string s){
    int hashv=strhash(s,b,p);
    if(hashval.count(hashv)){
        cout<<s<<'\n'<<hashval[hashv];
        exit(0);
    }
    hashval[hashv]=s;
    return;
}
int main(){
    cin>>b>>p;
    while(1)
        check(randstring());
    return 0;
}
```

---

