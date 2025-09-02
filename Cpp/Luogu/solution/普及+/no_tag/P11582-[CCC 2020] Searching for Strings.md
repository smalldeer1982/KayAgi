# [CCC 2020] Searching for Strings

## 题目背景

本题译自 [Canadian Computing Competition](https://cemc.uwaterloo.ca/resources/past-contests?contest_category=29) [2020 Senior](https://cemc.uwaterloo.ca/sites/default/files/documents/2020/2020CCCSrProblemSet.html) T3 Searching for Strings。

## 题目描述

计算字符串 $n$ 的不同排列中，作为 $h$ 的子字符串的数量。

## 说明/提示

**本题采用捆绑测试**。
#### 【样例解析】
仅有排列 `aba` 和 `baa` 作为子字符串出现在了 $h$ 中。
#### 【数据范围】
设 $n$ 长度为 $x$，$h$ 长度为 $y$。
| Subtask | 特殊性质 | 分值 |
| :----------: | :----------: | :----------: |
| 1 | $x\le 8,y\le 200$ | 20 |
| 2 | $x\le 200,y\le 200$ | 14 |
| 3 | $x\le 2000,y\le 2000$ | 14 |
| 4 | 无 | 52 |

注：原题满分为 15 分，其中 Sub1 有 $3$ 分，Sub2 和 Sub3 有 $2$ 分，而 Sub4 有 $8$ 分。本题分数为取近似后得到的结果。

## 样例 #1

### 输入

```
aab
abacabaa```

### 输出

```
2```

# 题解

## 作者：穼柗° (赞：4)

#### 温馨提示：在[专栏](https://www.luogu.com/article/y0yohyii)食用效果更佳。
### 前置知识：[子串的概念](https://baidu.physton.com/?q=%22%E5%AD%90%E4%B8%B2%E6%98%AF%E4%BB%80%E4%B9%88%22)、[字符串哈希](https://www.luogu.com.cn/problem/P3370)。

可以这样：枚举字符串 $h$ 中每个长度为 $|n|$ 的子串，判断是否为字符串 $n$ 的排列，如果是，就把它放到一个 `set` 里面，最后输出 `set` 的大小，因为 `set` 会去重，所以 `set` 的大小就是满足条件的不同子串数，也就是我们要求的答案。但是如果用 `set<string>` 会 [MLE](https://www.luogu.com.cn/record/200029289)，所以可以字符串哈希，用一个整数代替 `string`。
### Code
```cpp
#include <iostream>
#include <set>
using namespace std;
string a,b;
set<unsigned long long> st;
unsigned long long h[200001],pw[200001];
void Hash(const string &s) { // 哈希
	const int len=s.size();
	for(int i=0;i<len;i++)
		h[i+1]=h[i]*131+s[i];
}
unsigned long long sub_Hash(int l,int r) { // 求区间 [l,r] 的哈希值
	return h[r]-h[l-1]*pw[r-l+1];
}
void init() { // 初始化数组 pw[]，pw[i] 表示 131^i mod 2^64
	for(register int i=*pw=1;i<=200000;i++)
		pw[i]=pw[i-1]*131;
}
int anum[128],bnum[128];
int main() {
	cin.tie(nullptr)->sync_with_stdio(false),
	cout.tie(nullptr);
	cin>>a>>b; // 这里的 a,b 分别为题目中的 n,h
	init();
	Hash(b);
	const int len=a.size();
	for(int i=0;i<len;i++)
		anum[a[i]]++; // anum[c] 表示字符串 a 中字符 c 出现次数
	for(int j,i=0;i<b.size();i++) {
		bnum[b[i]]++; // bnum[c] 表示当前枚举的 b 的子串中字符 c 出现次数
		if(i>=len) bnum[b[i-len]]--;
		if(i>=len-1) {
			for(j=0;j<128;j++)
				if(anum[j]!=bnum[j])
					break; // 此时枚举的子串不是字符串 a 的排列
			if(j==128) st.insert(sub_Hash(i-len+2,i+1));
			// 上面的循环一直没执行到 break j 才会等于 128，
			// 说明此时枚举的子串是字符串 a 的排列，所以将哈希值放到 set 中
		}
	}
	cout<<st.size(); // 集合的大小就是最终的答案
	return 0;
}
```

---

## 作者：jojo222 (赞：4)

很多人会被 `TLE` 或 `MLE` 所困扰，今天我来将一个既不会 `TLE` 也不会 `MLE` 的方法。
### 人家的思路
暴力，暴力，暴力！  
用 `string` 存下枚举每一个长度为 $|n|$ 的子串，比较，统计！  
### 优化 1
这是用来解决 `TLE` 一部分的。先把 $h$ 的前 $|n|$ 个字符放入字符串中，接下来的每一部分只需要去掉开头的字符，再加入后面的字符就行了。  

优化后的代码（第一遍提交的代码）：
```cpp
#include <bits/stdc++.h>
using namespace std;
int ans, ln, lh;
int vn[128], vh[128];
string n, h, x;
vector<string> a;
int check()
{
	for(int i = 0; i < 128; i++)
		if(vn[i] != vh[i]) return 0;
	if(find(a.begin(), a.end(), x) == a.end())
	{
		a.push_back(x);
		return 1;
	}
	return 0;
}
int main()
{
	cin >> n >> h;
	ln = n.size(), lh = h.size();
	for(char c : n)
		vn[c]++;
	for(int i = 0; i < ln; i++)
		x += h[i], vh[h[i]]++;
	ans += check();
	for(int i = ln; i < lh; i++)
	{
		x = x.erase(0, 1), x += h[i];
		vh[h[i - ln]]--, vh[h[i]]++;
		ans += check();
	}
	cout << ans;
	return 0;
}
```
### 优化 2
这个优化有点难，大家坐稳扶好！  
`MLE` 想必困扰了大家一个下午。接下来我们要用~~完美暴力~~一个整数存下一整个字符串。  
$$s=c_0128^{|n|}+c_1128^{|n|-1}+\cdots+c_{|n|-1}$$
这……这好像会爆 `int` 甚至 `long long`，$128$ 也是 $2$ 的幂，乘着乘着就会变成 $0$ 呀！  
别急，我们要给它模一个质数 $10^9+7$，这样字符串不一样但整数一样发生的概率非常小（其它质数因为过于~~幸运~~倒霉而 `WA`）。  
这样，只需要统计这个压缩后的整数就可以了！ 

最终代码：
```cpp
#include <bits/stdc++.h>
#define mod 1000000007ll
using namespace std;
int mh, pw = 1;
int vn[128], vh[128];
string n, h;
set<int> s;
void check()
{
	for(int i = 0; i < 128; i++)
		if(vn[i] != vh[i]) return;
	s.insert(mh);
}
int main()
{
	cin >> n >> h;
	int ln = n.size(), lh = h.size();
	for(int i = 1; i < ln; i++)
		pw = 128ll * pw % mod;
	for(int i = 0; i < ln; i++)
	{
		vn[n[i]]++, vh[h[i]]++;
		mh = (128ll * mh + h[i]) % mod;
	}
	check();
	for(int i = ln; i < lh; i++)
	{
		vh[h[i - ln]]--, vh[h[i]]++;
		mh = (128ll * mod + mh - 1ll * h[i - ln] * pw) % mod;
		mh = (128ll * mh + h[i]) % mod;
		check();
	}
	cout << s.size();
	return 0;
}
```

---

## 作者：jiangxinyang2012 (赞：3)

当字符串 $m$ 中所有字母出现的次数都和 $n$ 一致时，$m$ 一定是 $n$ 的一个排列。

所以，我们可以根据字符串 $n$ 中每个字母出现的数量来构造一个哈希函数：

$$h(x)=c_a \cdot base^{0}+c_b \cdot base^{1}+c_c \cdot base^{2}+\cdots+c_z \cdot base^{25}$$

其中，$c_x$ 表示字母 `x` 出现的次数。

这样，我们就可以枚举排列的最后一个位置，每次 $O(1)$ 更新子串哈希值，并和 $n$ 的哈希值对比，如果一样，再把排列的子串哈希值丢进 set 里。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll mod = 1e9 + 7;
const int N = 200005;
const int INF = 0x3f3f3f3f;
using ull = unsigned long long;
const ull base = 131;
char a[N], b[N];
ull pw[N], d[N];
ll f(int l, int r) {
    return d[r] - d[l - 1] * pw[r - l + 1];
}
int main() {
    scanf("%s%s", a + 1, b + 1);
    int n = strlen(a + 1), m = strlen(b + 1);
    pw[0] = 1;
    for (int i = 1; i <= m; i++) {
        pw[i] = pw[i - 1] * base;
    }
    for (int i = 1; i <= m; i++) {
        d[i] = d[i - 1] * base + b[i] - 'a';
    }
    ll h = 0;
    for (int i = 1; i <= n; i++) {
        h += pw[a[i] - 'a'];
    }
    ll h2 = 0;
    set<ll> se;
    int tot = 0;
    for (int i = 1; i <= m; i++) {
        h2 += pw[b[i] - 'a'];
        if (i > n) h2 = h2 - pw[b[i - n] - 'a'];
        if (i >= n && h2 == h) {
            se.insert(f(i - n + 1, i));
        }
    }
    printf("%d\n", (int)se.size());
    return 0;
}

```

---

## 作者：szh_AK_all (赞：3)

比较清新的一道题。

## 分析
我们要求的合法字符串要满足如下几点要求：

- 是 $h$ 的子串且长度为 $x$（即 $n$ 的长度）；

- 是 $n$ 的一个排列。

要求一告诉我们可以线性的枚举 $h$ 的每个长度为 $x$ 的子串，再判断其是否符合要求二；而要求二等价于让当前字符串中与 $n$ 中相同字符出现的次数相同，由于字符集很小，所以可以暴力 check 当前子串是否合法。

由于记录的这些合法子串可能有些是相同的，所以用 map 来记录每个合法子串，起到记录不同合法子串个数的效果；而在记录时如果将整个字符串都存进去会超时，于是考虑使用哈希。

注：取模哈希可能会被卡，用自然溢出即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int base = 13331;
int now[200005], mu[200005];
unordered_map<int, int>q;

int ch() {
	for (int i = 1; i <= 26; i++)
		if (now[i] != mu[i])
			return 0;
	return 1;
}
int ha[200005], jie[200005];

int has(int l, int r) {
	int ans = ha[r] - ha[l - 1] * jie[r - l + 1];
	return ans;
}

signed main() {
	string n, h;
	cin >> n >> h;
	int x = n.size(), y = h.size();
	n = " " + n, h = " " + h;
	if (x > y) {
		cout << 0;
		return 0;
	}
	jie[0] = 1;
	for (int i = 1; i <= y; i++) {
		ha[i] = ha[i - 1] * base + h[i] - 'a' + 1;
		jie[i] = jie[i - 1] * base;
	}
	for (int i = 1; i <= x; i++)
		mu[n[i] - 'a' + 1]++, now[h[i] - 'a' + 1]++;
	if (ch())
		q[has(1, x)] = 1;
	for (int i = x + 1; i <= y; i++) {
		now[h[i - x] - 'a' + 1]--, now[h[i] - 'a' + 1]++;
		if (ch())
			q[has(i - x + 1, i)] = 1;
	}
	cout << q.size();
}
```

---

## 作者：lzt415 (赞：1)

## 思路分析
### 第一步
首先分析题意。得知我们需要暴力枚举字符串 $h$ 的每个与字符串 $n$ 长度相同的子字符串，并判断是否是 $n$ 的一种排列。  

问题来了，如何判断这个子字符串是字符串 $n$ 的一种排列呢？   

其实很简单，只需判断这个子字符串每种相同字符出现的个数与 $n$ 相同即可。而想要快速完成此操作，只需从左到右遍历 $h$ 的这个子字符串，设一个统计 $26$ 个字母的数组统计各个字母出现的个数即可。而每得到下一个 $h$ 的子字符串，只需向右移动一个，也就是只有一个字符被删除，一个被添加，这一部分的代码实施并不复杂。
### 第二步
重点来了！

接下来是本题唯一的关键。由于可能会有重复的排列，所以我们需判重。所以我们就很容易联想到用 ```map```。用来记录每个合法子串，起到记录不同合法子串个数的效果。而在记录时如果将整个子字符串塞进去显然会超时，所以我们考虑使用到哈希。

---

## 作者：xuzb (赞：1)

# 思路
设 $S$ 是字符串 $H$ 的一个子串，长度为 $| N|$。要检查 $S$ 是否是 $N$ 的排列，统计字母表中 $26$ 个字母各自的出现次数。如果 $S$ 和 $N$ 中各字母的统计次数都一致，那么它们就是彼此的排列。为快速完成此操作，从左到右遍历 $S$。如此一来，每次向右移动时，最多只有两个字符被添加或移除。这样我们就能知晓哪些子串能满足 “排列” 要求。

现在我们要找出满足条件的不同子串 $S$ 的数量。设  $T$ 为所有这样的 $S$ 构成的集合。为去除重复项，我们需要一种快速比较 $T$ 中元素的方法。这可以通过使用滚动哈希（采用以 31 为基数的双重哈希）来快速实现。我们将有效的 $hash (S)$ 值插入到集合 $T$ 中。最后，答案就是集合 $T$ 的元素个数。

时间复杂度：$O (|H|)$ 

# AC代码

```cpp
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
#include <utility>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
ll hsh[200010], pw[200010], base = 31;
int fs[26], ft[26];
unordered_set<ll> st;
bool isubstring(){
    for (int i = 0; i < 26; i++){
        if (fs[i] != ft[i]) return false;
    }
    return true;
}
ll mySubHash(int l, int r){
    return hsh[r] - hsh[l-1]*pw[r-l+1];
}
int main() {
    string s, t;
    cin >> s >> t;
    int n = s.length(), m = t.length();
    for (int i = 1; i <= n; i++){
        fs[s[i-1]-'a']++;
    }
    pw[0] = 1;
    for (int i = 1; i <= m; i++){
        hsh[i] = hsh[i-1]*base + t[i-1];
        pw[i] = pw[i-1]*base;
    }
 
    for (int i = 1; i <= m; i++){
        // Sliding window
        ft[t[i-1]-'a']++;
        if (i < n)
        	continue;
        if (i > n)
        	ft[t[i-n-1]-'a']--;
        // Rolling hash
        if (isubstring()){
        	st.insert(mySubHash(i-n+1, i));
        }
    }
    cout << st.size() << endl;
}

```
最后希望管理员大大能过！

---

## 作者：lzx111218 (赞：0)

# P11582 [CCC 2020] Searching for Strings
[题目传送门](https://www.luogu.com.cn/problem/P11582)
## 思路
字符串 $n$ 的所有排列实际上是由字符频率决定的。排列问题转化为字符频率匹配的问题。因此，我们需要计算字符串 $n$ 中每个字符的频率，并且在 $h$ 中寻找所有长度为 $|n|$ 的子串，它们的字符频率与 $n$ 的字符频率一致。

~~为了不会 TLE~~ 我们使用 滑动窗口 技术。具体来说，我们将 $h$ 中的每个长度为 $|n|$ 的子串视作一个窗口，通过滑动这个窗口来更新子串的字符频率。每滑动一次，就更新一下窗口内的字符频率，判断是否与 $n$ 的字符频率相同即可。

**时间复杂度为** $O(y)$。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

int base = 13331;
int now[200005], mu[200005];
map<int, int> q;  

int ch() {
    for (int i = 1; i <= 26; i++)
        if (now[i] != mu[i])
            return 0;
    return 1;
}

int ha[200005], jie[200005];

int has(int l, int r) {
    int ans = ha[r] - ha[l - 1] * jie[r - l + 1];
    return ans;
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
    string n, h;
    cin >> n >> h;
    int x = n.size(), y = h.size();
    n = " " + n, h = " " + h;
    if (x > y) {
        cout << 0;
        return 0;
    }
    
    jie[0] = 1;
    for (int i = 1; i <= y; i++) {
        ha[i] = ha[i - 1] * base + h[i] - 'a' + 1;
        jie[i] = jie[i - 1] * base;
    }
    for (int i = 1; i <= x; i++) {
        mu[n[i] - 'a' + 1]++;
        now[h[i] - 'a' + 1]++;
    }
    if (ch()) 
        q[has(1, x)] = 1;
    for (int i = x + 1; i <= y; i++) {
        now[h[i - x] - 'a' + 1]--;
        now[h[i] - 'a' + 1]++;
        if (ch())
            q[has(i - x + 1, i)] = 1;
    }
    cout << q.size();
    return 0;
}

```

---

