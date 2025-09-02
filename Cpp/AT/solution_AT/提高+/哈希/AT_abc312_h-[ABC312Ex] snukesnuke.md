# [ABC312Ex] snukesnuke

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc312/tasks/abc312_h

高橋君は人 $ 1,\ldots,N $ の $ N $ 人のあだ名を決めることになりました。

人 $ i $ はあだ名を $ S_i $ にしてほしいと思っています。複数人に同じあだ名をつけるのを避けるため、高橋君は次の手順で $ N $ 人のあだ名を決めることにしました。

- $ i=1,\ldots,N $ の順に、以下の操作により人 $ i $ のあだ名を決める
  - 変数 $ k_i $ を $ 1 $ とする。
  - 「$ S_i $ を $ k_i $ 回繰り返した文字列」がすでに誰かのあだ名である間、$ k_i $ を $ 1 $ 増やすことを繰り返す。
  - 「$ S_i $ を $ k_i $ 回繰り返した文字列」を人 $ i $ のあだ名とする。
 
$ N $ 人のあだ名を決めた後の $ k_1,\ldots,k_N $ を求めてください。

## 说明/提示

### 制約

- $ N\ \geq\ 1 $
- $ S_i $ は英小文字のみからなる、長さ $ 1 $ 以上の文字列
- $ S_i $ の長さの総和は $ 2\times\ 10^5 $ 以下
 
### Sample Explanation 1

\- まず人 $ 1 $ のあだ名を決めます。 - $ k_1=1 $ とします。 - $ S_1 $ を $ k_1 $ 回繰り返した文字列 `snuke` は誰のあだ名でもないので、人 $ 1 $ のあだ名は `snuke` になります。 - 次に人 $ 2 $ のあだ名を決めます。 - $ k_2=1 $ とします。 - $ S_2 $ を $ k_2 $ 回繰り返した文字列 `snuke` はすでに人 $ 1 $ のあだ名なので、$ k_2 $ を $ 1 $ 増やして $ 2 $ とします。 - $ S_2 $ を $ k_2 $ 回繰り返した文字列 `snukesnuke` は誰のあだ名でもないので、人 $ 2 $ のあだ名は `snukesnuke` になります。 - 最後に人 $ 3 $ のあだ名を決めます。 - $ k_3=1 $ とします。 - $ S_3 $ を $ k_3 $ 回繰り返した文字列 `rng` は誰のあだ名でもないので、人 $ 3 $ のあだ名は `rng` になります。 以上により、$ k_1,k_2,k_3 $ はそれぞれ $ 1,2,1 $ となります。

### Sample Explanation 2

\- 人 $ 1 $ のあだ名は `aa` になります。 - 人 $ 2 $ のあだ名は `a` になります。 - 人 $ 3 $ のあだ名は、`a`, `aa` がすでに他の人のあだ名なので、`aaa` になります。 - 人 $ 4 $ のあだ名は、`aaa` がすでに他の人のあだ名なので、`aaaaaa` になります。

## 样例 #1

### 输入

```
3
snuke
snuke
rng```

### 输出

```
1 2 1```

## 样例 #2

### 输入

```
4
aa
a
a
aaa```

### 输出

```
1 1 3 2```

## 样例 #3

### 输入

```
5
x
x
x
x
x```

### 输出

```
1 2 3 4 5```

# 题解

## 作者：hzlqwq (赞：7)

因为具有相同循环节的字符串可能在分别翻倍多次后变成一样的，所以首先，我们需计算出每个字符串的最小循环节和循环次数，把循环节相同的字符串归到一类处理。

> 字符串的最小循环节可用 kmp 算法求得：若 $S$ 的前缀数组最后一项 $ne_{\lvert S\rvert}\ne 0$ 且 $(n-ne_{\lvert S\rvert})\mid n$ ，则最小循环节长度为 $n-ne_{\lvert S\rvert}$，否则为 $n$。

接下来，我们即可逐个计算 $k_i$：当遍历到第 $i$ 个字符串时，若第 $i$ 个字符串循环了 $sk_i$ 次自己的最小循环节，那么我们在*记录了这个循环节的每个循环次数是否出现过*的 map / set 中查询 $sk_i,2sk_i,3sk_i,4sk_i\cdots$，若 $xsk_i$ 为其中第一个没有在 map / set 中出现的数，则 $x$ 就是第 $i$ 个字符串的答案 $k_i$。

但是直接这样枚举显然会被卡飞，我们需要一些优化方法：虽然某个循环节出现过的循环次数不是连续的，但同一个 $sk_i$ 每次的查询是连续的（$1$ 倍，$2$ 倍，$3$ 倍 $\cdots$），于是我们可以记录每个循环节每个 $sk_i$ 的查询进行到了几倍，这样每次查询的倍数都是递增的，时间复杂度降为了 $O\left(\sum\limits_{i=1}^{n}\frac{n}{i}\right)=O(n\log n)$。

总时间复杂度 $O(\lvert S \rvert + n\log n)$。

```cpp
#include <iostream>
#include <unordered_map>
#include <unordered_set>

#define size(x) s[x].size()

using namespace std;

const int N = 2e5 + 10;

int n;
string s[N], cir[N];            // 原字符串，循环节
int ne[N], len[N], sk[N];       // kmp 前缀数组，循环节长度，循环次数
unordered_map<string, int> id;  // 循环节字符串映射到 mex 下标
int idx;                        // 不同的循环节个数
unordered_set<int> mex[N];      // 已出现过的循环节循环次数
unordered_map<int, int> jmp[N]; // 某个循环节每次跳某步当前已经枚举到的倍数

inline void speedup()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
}

inline void kmp(int x)
{
    for (int i = 1, j = 0; i < size(x); i++)
    {
        while (j && s[x][i] != s[x][j])
            j = ne[j - 1];
        if (s[x][i] == s[x][j])
            j++;
        ne[i] = j;
    }
    len[x] = size(x) % (size(x) - ne[size(x) - 1]) == 0 ? size(x) - ne[size(x) - 1] : size(x);
    sk[x] = size(x) / len[x];
    cir[x] = s[x].substr(0, len[x]);
}

inline void init()
{
    for (int i = 1; i <= n; i++)
        kmp(i);
    for (int i = 1; i <= n; i++)
        if (!id[cir[i]])
            id[cir[i]] = ++idx;
}

int main()
{
    speedup();
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> s[i];
    init();
    for (int i = 1; i <= n; i++)
    {
        int tmp = id[cir[i]];
        while (mex[tmp].count(++jmp[tmp][sk[i]] * sk[i]))
            ;
        cout << jmp[tmp][sk[i]] << "\n";
        mex[tmp].insert(jmp[tmp][sk[i]] * sk[i]);
    }
    return 0;
}
```


---

## 作者：Genius_Star (赞：0)

[**或许更好的阅读体验。**](https://www.cnblogs.com/rgw2010/p/18825266)

### 思路：

考虑求出每个字符串 $s_i$ 的严格最小正周期 $t_i$，那么若 $t_i \ne t_j$，则 $s_i$ 与 $s_j$ 无论叠加多少次都绝对不可能相等。

故我们只需要考虑 $t_i$ 相同的那些字符串。

设 $|t_i| = len$，对于最小正周期为 $t_i$ 的字符串，不难发现只需要用到这些字符串的长度，且由于这些长度都是 $len$ 的倍数，先考虑除以 $len$ 减小值域。

那么现在问题变为，支持集合动态加一个数，查询一个数最小的倍数使得不在集合中。

考虑动态对于每个长度 $x$，维护 $ans_x$ 表示最小的 $k$ 使得，$kx \notin S$；初始 $ans_x = 1$，然后考虑加入一个数 $n$ 后，只会对满足 $x \mid n$ 的 $ans_x$ 造成影响，暴力去更新即可。

由于 $\sum |s_i| \le 2 \times 10^5$，复杂度均摊下来是对的。

[**link**](https://atcoder.jp/contests/abc312/submissions/64960674)

### 完整代码：

```cpp
 #include<bits/stdc++.h>
#define lowbit(x) x & (-x)
#define ls(k) k << 1
#define rs(k) k << 1 | 1
#define fi first
#define se second
#define add(x, y) ((x + y >= mod) ? (x + y - mod) : (x + y))
#define dec(x, y) ((x - y < 0) ? (x - y + mod) : (x - y))
#define ctz(x) __builtin_ctz(x)
#define popcnt(x) __builtin_popcount(x)
#define open(s1, s2) freopen(s1, "r", stdin), freopen(s2, "w", stdout);
using namespace std;
typedef __int128 __;
typedef long double lb;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const int N = 2e5 + 10;
const int base = 127, mod = 1e9 + 7;
inline ll read(){
    ll x = 0, f = 1;
    char c = getchar();
    while(c < '0' || c > '9'){
        if(c == '-')
          f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9'){
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		x = -x;
	}
	if(x > 9)
	  write(x / 10);
	putchar(x % 10 + '0');
}
int n, m, t, now, cnt;
char s[N];
int poww[N], len[N], ans[N], h[N], a[N];
vector<pair<int, int>> V[N];
unordered_map<int, int> mp;
stack<int> T;
bool vis[N];
inline int get(int l, int r){
	return dec(a[r], 1ll * a[l - 1] * poww[r - l + 1] % mod);
}
inline void getn(int x, int v){
	if(x * h[x] != v)
	  return ;
	T.push(x);
	while(vis[x * h[x]])
	  ++h[x];
}
bool End;
int main(){
	poww[0] = 1;
	for(int i = 1; i < N; ++i){
		poww[i] = 1ll * base * poww[i - 1] % mod;
		h[i] = 1;
	}
	n = read();
	for(int id = 1; id <= n; ++id){
		scanf("%s", s + 1);
		m = strlen(s + 1);
		for(int i = 1; i <= m; ++i)
		  a[i] = add(s[i], 1ll * a[i - 1] * base % mod);
		for(int i = 1; i <= m; ++i){
			if(m % i == 0 && get(1, m - i) == get(i + 1, m)){
				t = i;
				now = a[i];
				break;
			}
		}
		if(!mp.count(now))
		  mp[now] = ++cnt;
		now = mp[now];
		V[now].push_back({m / t, id});
	}
	for(int now = 1; now <= cnt; ++now){
		stack<int> A;
		for(auto t : V[now]){
			ans[t.se] = h[t.fi];
			int x = h[t.fi] * t.fi;
			A.push(x), vis[x] = 1;
			for(int i = 1; i * i <= x; ++i){
				if(x % i == 0){
					getn(i, x);
					if(i * i != x)
					  getn(x / i, x);
				} 
			}
		}
		while(!A.empty()){
			int x = A.top();
			A.pop();
			vis[x] = 0;
		}
		while(!T.empty()){
			int x = T.top();
			T.pop();
			h[x] = 1;
		}
	}
	for(int i = 1; i <= n; ++i){
		write(ans[i]);
		putchar(' ');
	}
	cerr << '\n' << abs(&Begin - &End) / 1048576 << "MB";
	return 0;
}
```

---

## 作者：liangbowen (赞：0)

[blog](https://www.cnblogs.com/liangbowen/p/18380822)。这玩意有空心橙？？？？写篇题解祭一下速杀 *2400（

---

什么时候，两个串可能会冲突？答案是他们有公共最小循环节。于是[用 KMP 求出每个串的最小循环节](https://www.cnblogs.com/liangbowen/p/18381006)。

存在一个暴力：将所有最小循环节相同的串放到一起 query，对于一个循环节长度为 $r$ 的串，遍历 $r,2r,3r,\cdots,x\cdot r$ 直到 $x\cdot r$ 没有被使用过，答案即为 $x$。这样显然是平方的。

考虑**对原串完全相同的串记忆化**。即：若有 $S_1=S_2$ 且 $S_1$ 的答案为 $x$，处理 $S_2$ 时直接从 $(x+1)$ 开始枚举。

---

正确性显然，复杂度呢？下文记 $S=\sum|s_i|$。

注意到原问题维护了 $O(n)$ 个集合，显然它弱于 $1$ 个集合的问题：

> Problem：维护集合，每次 find 最小的、不在集合内的、能够整除 $r$ 的数，并把它 insert 进集合。

一个潜在条件是 $\sum r\le S$。并且容易证明，集合最大数不会超过 $\sum r$。

对相同的 $r$ 记忆化后，一个 $r$ 最多只会遍历 $O(\dfrac Sr)$ 次，于是总复杂度 $O(\sum\limits_{r=1}^S \dfrac Sr)=O(S\log S)$。

[code](https://atcoder.jp/contests/abc312/submissions/57145979)，时间复杂度 $O(S\log^2S)$。另一篇题解使用了 hash-table 做到了 $O(S\log S)$。

---

## 作者：__vector__ (赞：0)

纪念第一次赛时过 Ex && 做出 atc 2400+ 题目，虽然是个大水题。  
- 做法 $1$  
考虑暴力枚举 $k$，暴力判定。  
显然会寄掉。 

- 做法 $2$  
   显然同一个字符串出现两次，第二次的答案一定大于第一次。  
   其实一个字符串，只会对所有的循环节产生影响，而它本身的循环节种类显然是 $O(\sqrt{n})$ 量级的，可以参考因数数量，设本字符串长度为 $len$，那么最终造成的时间消耗是 $O(len \sqrt{len})$ 级别的。  
   复杂度瓶颈在于同一个字符串出现多次。  
   所以可以对字符串进行记忆化，对输入的字符串存储答案字符串，对最终形成的字符串（答案字符串）进行存在性标记。  
   但朴素实现复杂度不变，主要瓶颈在于存储最终的答案字符串。  
- 做法 $3$  
   考虑字典树，此时我们对于答案字符串的记忆化，不再直接存储字符串，转而使用字典树，而记忆方式则是同时记录 $k$ 和答案字符串对应的字典树坐标。  
   这样构造当前答案的时候，可以直接从原记录的字典树对应位置继续构造，而不用从头开始。  
   	复杂度 $O(len \sqrt{len})$。  
    [AC code](https://atcoder.jp/contests/abc312/submissions/44070102)  
    另外由于循环节数量实际上一般远远少于根号，所以运行时间应该是接近 log 的。  
    

---

