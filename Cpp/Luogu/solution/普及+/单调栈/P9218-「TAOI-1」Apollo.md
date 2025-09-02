# 「TAOI-1」Apollo

## 题目背景

Execution.

这题原来叫 `std::cout << std::fixed << std::setprecision(1) << 6.5 << '\n';`。

[被当事人删掉的图片.jpg]

**【Upd 2023/04/15 21:42】添加了一组 Hack 数据位于 Subtask 2，#13。现在所有赛时的 $\bm{50}$ 分提交理论上均只能获得 $\bm{30}$ 分。**

## 题目描述

给出 $n$ 个十进制小数 $a_1 \dots a_n$。

对于一个 **数** $a$，定义其精度 $f(a)$ 表示最小的非负整数 $k$ 使得 $10^k\times a$ 为整数；对于整数 $a$，定义 $f(a) = 0$。对于两个十进制小数 $a, b$，定义 $g(a, b)$ 为对于所有 **数** $c \in [\min(a,b), \max(a,b)]$ 的 $f(c)$ 的最小值。

对于所有 $1 \leq i \leq n$，你需要求出 $\sum\limits_{j=1}^ng(a_i, a_j)$ 的值并输出。

定义十进制小数是一个含有整数部分和小数部分的数，其小数部分不为 $0$。之所以描述得这么愚蠢是因为保证输入的每个数都有小数点，但是好像无论什么写法都会有人提出不满，真是抱歉了。~~所以还是得看看被当事人删掉的图片。所以我在这里写闲话有人看得到吗。~~

## 说明/提示

### 数据范围

**本题采用捆绑测试。**

令 $\sum\limits_{i=1}^n f(a_i) = t$。

- Subtask 1（15 points）：$a_i \leq 10$，$n \leq 5$，$t \leq 10$。
- Subtask 2（15 points）：$a_i \leq 10$，$n \leq 100$，$t \leq 1000$。
- Subtask 3（20 points）：$n \leq 1722$。
- Subtask 4（15 points）：$a_i \leq 1$。
- Subtask 5（35 points）：无特殊限制。

对于所有数据，$0 \lt a_i \lt 10^9$，$1 \leq n \leq 10^5$，$1 \leq t \leq 3 \times 10^6$，**保证 $\bm{a_i}$ 没有后导 [$\color{black}\bm 0$](https://cdn.luogu.com.cn/upload/image_hosting/pg66fm1z.png)，不保证 $\bm{a_i}$ 互不相同**。

### 样例解释

以 $i = 1$ 为例：

+ $j = 1$：取 $c = 11.4514$，$f(c) = 4$；
+ $j = 2$：取 $c = 11.46$，$f(c) = 2$；
+ $j = 3$：取 $c = 11.2$，$f(c) = 1$；
+ $j = 4$：取 $c = 11.3$，$f(c) = 1$；
+ $j = 5$：取 $c = 11.47$，$f(c) = 2$。

故 $\sum\limits_{j=1}^n g(a_1, a_j) = 4 + 2 + 1 + 1 + 2 = 10$。对于同一个 $j$，上文给出的所有 $c$，都可能有其它的不同的 $c$ 满足 $f(c)$ 同样最小。

## 样例 #1

### 输入

```
5
11.4514
11.4778
11.1338
11.1236
11.4789```

### 输出

```
10
11
9
9
11```

## 样例 #2

### 输入

```
8
1.1145
1.114
1.1145
1.514
1.19198
1.1154
1.114
1.1145```

### 输出

```
24
21
24
10
18
22
21
24```

# 题解

## 作者：wloving (赞：12)

## 题目分析

仔细阅读题目，可知题目要求的是对于每个 $a_i$ 的 $\sum\limits_{j=1}^ng(a_i,a_j)$ 。再结合 $g(a,b)$ 的定义，可知，对于 $a_i$ 来说，我们需要计算 $a_i$ 与 $a_1\sim a_n$ 构成的 $n$ 组数对的 $g(a_i,a_j)$ 的总和。对于 $g(a,b)$ 的值，则是 $[\min(a,b),\max(a,b)]$ 中的最小 $f(c)$ 的值，当前 $c\in [\min(a,b),\max(a,b)]$。对于 $f(c)$ 的作用则是返回将小数 $c$ 变成整数的乘 $10$ 的次数，即 $c$ 的小数部分的位数。题目描述的比较绕，需要耐心将公式之间的关系捋清楚。

接下来思考如何计算 $g(a,b)$。我们分情况进行讨论，为方便描述我们设 $a\le b$。

1. 两个数的整数部分不同。

当整数部分不相同时，在 $[a,b]$ 中一定可以存在一个整数 $c$ ，当 $c$ 为整数时，$f(c)=0$。所以整数部分不相同，$g(a,b)=0$。

2. 两个数的整数部分相同。当整数部分相同时，考虑小数部分。可以分成三种情况：

   1. 小数部分完全不一样。

      如 $11.123$ 和 $11.231$ 对应的 $c=11.2$，$f(c)=1$。也就是较小的数值保留1位小数再加 $0.1$ 就好，这样乘 $10^1$ 就能成为整数。

   2. 部分前缀相同。

      如 $11.12345$ 和 $11.12388$ 对应的 $c=11.1235$，$f(c)=4$。也就是先找 $a$ 和 $b$ 的最大公共前缀，再往后一位，找一个在两者范围内的数字即可，若小数点后最大公共前缀长度为 $k$ 则乘 $10^{k+1}$ 就能成为整数。

   3. 较小的数字是较大数字的前缀。

      如 $11.123$ 和 $11.123456$ 对应的 $c=11.123$，$f(c)=3$。也就是较小的那个数字的小数位数，若较小数字的小数位置为 $k$ 则乘 $10^k$ 就能成为整数。

此时我们可以发现，问题是围绕着公共前缀展开的。对于小数的公共前缀，我们可以将小数视为字符串进行存储与使用，就将问题转换了字符串的公共前缀问题，这类问题使我们联想到字典树，可以考虑使用字典树解决它。

以样例2为例，讲解字典树解法思路。

```
8
1.1145
1.114
1.1145
1.514
1.19198
1.1154
1.114
1.1145
```



下图为建立好的字典树。

![1715103837347.png](https://picstore-1308257740.cos.ap-nanjing.myqcloud.com/2024/05/08/663a685e93fd3.png)

查找数值 $1.1145$ 的答案过程。

![1715102902356.png](https://picstore-1308257740.cos.ap-nanjing.myqcloud.com/2024/05/08/663a64b7efb5e.png)

查找数值 $1.114$ 的答案过程。

![1715103185147.png](https://picstore-1308257740.cos.ap-nanjing.myqcloud.com/2024/05/08/663a65d2bd337.png)



查找数值 $1.514$ 的答案过程。![1715103398110.png](https://picstore-1308257740.cos.ap-nanjing.myqcloud.com/2024/05/08/663a66a75ed07.png)

模拟过程中可发现，在遍历字典树的过程中，我们计算新增的不同前缀的元素个数与当前结尾的元素个数，它们成为整数的答案为当前小数位数。另外，在遍历结束后需要考虑和计算以当前数字为前缀且又比它长的数字个数，详细可查看寻找数值 $1.114$ 的过程。

## 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
const int N = 1e5 + 5;
const int M = 3e6 + 5;
int n, tot, zs;
string str[N];
struct node {
  int son[11];
  // 前缀相同的字符串个数、以该节点结尾的字符串个数、小数部分的位数
  int num, end, dep;
} trie[M];
int toNum[256];
void init() {
  for (int i = 0; i < 10; i++) {
    toNum[i + '0'] = i;
  }
  toNum['.'] = 10;
}
void insert(string s) {  // 字典树插入
  int len = s.size();
  int u = 0;
  int dot = -1;   // 小数点位置
  trie[u].num++;  // 记录字符串总数
  for (int i = 0; i < len; i++) {
    int ch = toNum[s[i]];
    if (!trie[u].son[ch]) trie[u].son[ch] = ++tot;
    u = trie[u].son[ch];
    trie[u].num++;
    if (ch == 10) dot = i;                 // 记录小数点的位置
    if (dot != -1) trie[u].dep = i - dot;  // 更新小数部分对应的位数
  }
  trie[u].end++;//记录该处结尾的数字个数
}
int findStr(string s) {
  // 整数部分不一样，f(c)为0
  // 整数部分相同时考虑小数部分的最大公共前缀
  int len = s.size();
  int sum = 0, re = trie[0].num;  // re-剩余前缀相同的字符串数量
  int u = 0;
  for (int i = 0; i < len; i++) {
    int ch = toNum[s[i]];
    u = trie[u].son[ch];
    //   num=新增的前缀不同的字符串数量 + 以该节点结尾的字符串数量
    int num = re - trie[u].num + trie[u].end;
    sum += num * trie[u].dep;  // 更新总和
    re -= num;
  }
  // 处理前缀与s相同，但又比s长的字符串
  sum += (trie[u].num - trie[u].end) * trie[u].dep;
  return sum;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  init();
  string s;
  char c;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> str[i];
    insert(str[i]);
  }
  for (int i = 1; i <= n; i++) {
    cout << findStr(str[i]) << '\n';
  }
  return 0;
}
```

---

## 作者：irris (赞：3)

### 前言

这题个人差挺大的，不知道为啥。/ng

### 观察

我们发现 $g(x, y) = k$ 相当于 $k$ 是最小满足 $\lfloor x \times 10^k \rfloor \neq \lfloor y \times 10^k \rfloor$ 的自然数。特殊地，若 $x = y$，则 $g(x, y) = f(x) = f(y)$。

简单证明：前 $k - 1$ 位必须保持一样（因为被 $x, y$ 夹在中间了），第 $k$ 位开始有选择空间，就意味着可以在这一位结束。

我们下面假设 $g(x, y) \gt 0$，也就是说对整数部分不同的数分别处理。

### 算法一

进行暴力枚举每一对 $i, j$，可以做到最劣 $\mathcal O(n^2 + t\sqrt{t})$ 的匹配复杂度（如果还可以接着卡匹配的话，麻烦私信指教我）！期望得分 $30$ 分。

### 算法二

考虑如何快速计算 $g(a_i, a_j)$，我们可以通过哈希加二分的方式做到 $\mathcal O(n^2\log t)$，期望得分 $50$ 分。

### 算法三

将 $a_{1\dots n}$ 排序后，我们考虑让 $m_i = g(a_i, a_{i+1})$，那么枚举取值范围，有 $g(a_i,a_j) = \min_{k=i}^{j-1} m_k$。维护一个单调栈，我们可以 $\mathcal O(n)$ 对 $j = 1 \sim n$ 计算所有 $i \lt j$ 的 $i$ 对 $j$ 的贡献，把这个过程再反过来并且加上自身即可，时间复杂度 $\mathcal O(\text{SORT} + n + t)$。

通过字典树可以保证排序的严格复杂度，做到 $\mathcal O(n + t)$，期望得分 $100$ 分。

### 算法四

我们都用字典树了，你还不能想把单调栈丢掉吗？

发现 $i, j$ 彼此之间的贡献就是 $i, j$ 在字典树上 lca 的深度，那么一个点 $u$ 对其内所有表示原数的节点的贡献就是 $sz_u$，不要忘了一些实现细节。期望得分 $100$ 分，明显好写于算法三。

xyf 的代码比我更短更简洁，但是我觉得应该放我的代码/hsh：

```cpp
#include <bits/stdc++.h>

int st = 1, root = 1;
#define MAXV 4000001
struct Trie {
	/* 0123456789Trie */
	int node[10], sz, ed;
	Trie () : sz(0), ed(0) {}
	inline int getNxt(int val) {
		return node[val] ? node[val] : node[val] = ++st;
	}
} f[MAXV];

void insert(const std::string& x) {
	++f[root].sz;
	for (int p = root, i = 0; i < x.size(); ++i) {
		++f[p = f[p].getNxt(x[i] - '0')].sz;
		if (i == x.size() - 1) ++f[p].ed;
	}
}
void del(const std::string& x) {
	--f[root].sz;
	for (int p = root, i = 0; i < x.size(); ++i) {
		--f[p = f[p].getNxt(x[i] - '0')].sz;
		if (i == x.size() - 1) --f[p].ed;
	}
}
int calc(const std::string& x) {
	int ans = 0;
	for (int p = root, i = 0; i < x.size(); ++i) 
		ans += f[p].sz - f[p].ed, p = f[p].getNxt(x[i] - '0');
	return ans;
}

#define MAXN 100001
std::string Q[MAXN];
int ans[MAXN];
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr), std::cout.tie(nullptr);
	int N; std::string S, T; std::cin >> N;
	std::vector<std::pair<int, int>> floor;
	for (int i = 1, idx = 0, p = 0; i <= N; idx = p = 0, ++i) {
		std::cin >> S;
		while (p < S.size() && S[p] != '.')
			 idx = idx * 10 + S[p++] - '0';
		floor.push_back({idx, i});
		if (p == S.size()) S += ".0";
		for (++p; p < S.size(); ++p) Q[i].push_back(S[p]);
	}
	std::sort(floor.begin(), floor.end());
	for (int l = 0, r = 0; l < N; l = ++r) {
		while (r < N - 1 && floor[r + 1].first == floor[l].first) ++r;
		// solve [l, r]
		for (int i = l; i <= r; ++i) insert(Q[floor[i].second]);
		for (int i = l; i <= r; ++i) 
			ans[floor[i].second] = calc(Q[floor[i].second]);
		for (int i = l; i <= r; ++i) del(Q[floor[i].second]);
	}
	for (int i = 1; i <= N; ++i) std::cout << ans[i] << '\n';
	return 0;
}
```

---

## 作者：Lysea (赞：2)

### P9218 字典树（Trie）做法

奔着 TRIE 的标签来的，竟然第一次提交就 AC 了，必须写篇题解纪念一下！

### 分析

对于两个十进制小数 $a$ 和 $b$：

- 如果 $\lfloor a \rfloor = \lfloor b \rfloor$，容易得到 $g(a,b)$ 就是 $a$ 与 $b$ 小数部分**最长公共前缀的长度**。

- 否则 $g(a,b)=0$。

如果我们将这些小数看成字符串，这就变成了一道寻找字符串间最大公共前缀的题目，妥妥的 Trie 模板题啊！

### 思路

统计 $a$ 和 $b$ 在字典树上第 $i$ 位小数的的经过次数 $\mathit{cnt}_{i}$，它的深度 $\mathit{d}_{i}$，以及它的父节点 $p$。

当 $f(a) \leq f(b)$ 且 $g(a,b) \neq f(a)$ 时，$a$ 与 $b$ 不在字典树的同一条链上，二者的 $i$ 点对答案的贡献为 $\mathit{d}_{i} \times (\mathit{cnt}_{p} - \mathit{cnt}_{i})$，其中 $\mathit{cnt}_{p} - \mathit{cnt}_{i}$ 表示以 $p$ 为父节点的除去 $i$ 号点的儿子个数，$\mathit{d}_{i}$ 等价于字符串中的最大公共前缀。

当 $f(a) \leq f(b)$ 且 $g(a,b)=f(a)$ 时，$a$ 与 $b$ 在字典树的同一条链上，需要特殊处理：

统计树上 $i$ 号点被作为终点的次数 $\mathit{e}_{i}$，可以得到贡献为 $\mathit{d}_{i} \times (\mathit{cnt}_{p} - \mathit{cnt}_{i} - \mathit{e}_{p} + \mathit{e}_{i})$，并且如果这个点是 $a$ 点，还要加上 $a$ 终点的儿子节点的 $cnt$ 之和。

最后别忘了处理数字的整数部分，因为还存在 $g(a,b)=0$ 的情况。

### 代码
```
#include<bits/stdc++.h>
#define int long long
#define N 3000005
using namespace std;
int n,t[N][10],p,c,a,b,tot,cnt[N],ans,dep,u,en[N];
//cnt数组记录经过次数，en数组记录作为终点的次数 
string s[100005];
void Insert(string x){
	a=p=0,u=1;
	for(b=0;x[b]!='.';b++) a=a*10+(x[b]-'0');
	for(int i=1;i<=9;i++) u*=10;
	for(;u;u/=10){
		c=a/u%10;
		if(!t[p][c]) t[p][c]=++tot;
		p=t[p][c];
		cnt[p]++;
	}//处理整数部分 
	for(int i=b+1;i<x.size();i++){
		c=x[i]-'0';
		if(!t[p][c]) t[p][c]=++tot;
		p=t[p][c];
		cnt[p]++;
	}//处理小数部分 
	en[p]++;
}
void Find(string x){
	ans=p=dep=a=0,u=1;
	for(b=0;x[b]!='.';b++) a=a*10+(x[b]-'0');
	for(int i=1;i<=9;i++) u*=10;
	for(;u;u/=10){
		c=a/u%10;
		p=t[p][c];
	}//处理整数部分 
	for(int i=b+1;i<x.size();i++){
		c=x[i]-'0',dep++;
		ans+=dep*(cnt[p]-cnt[t[p][c]]-en[p]+en[t[p][c]]);
		//特殊情况下的计算是通用的 
		p=t[p][c];
	}//处理小数部分 
	for(int i=0;i<=9;i++){
		if(t[p][i]) ans+=dep*cnt[t[p][i]];
	}//特殊情况下的累加 
	cout<<ans<<endl;
}
signed main(){
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>s[i],Insert(s[i]);
	for(int i=1;i<=n;i++) Find(s[i]);
    return 0;
}


```

---

## 作者：gyyyyx (赞：2)

[题面](https://www.luogu.com.cn/problem/P9218)

观察一下会发现对于两个小数，若其**整数部分不相同**，那**必定**能找到一个满足条件的**整数**。

如以下两组 $a,b$，均能找到一个满足条件的整数 $c$：

```
a=10.72839465781875
b=11.3312573461624
c=11

a=35.589712
b=34.872
c=35
```

此时的 $g(a,b)=0$。

那如果**整数部分相同**，则要算**小数部分**的**最长公共前缀**的长度。

如以下两组 $a,b$ 以及 $g(a,b)$：

```
a=5.12345
b=5.12346
g(a,b)=5(c=5.12345 or 5.12346)

a=0.0101
b=0.0202
g(a,b)=2(c=0.02)
```

此时的 $g(a,b)=len+1$，$len$ 为**小数部分**的**最长公共前缀** 的长度。

考虑将所有**整数部分相同**的字符串放到一棵字典树上，$g(a,b)$ 就可以转化为深度。

但是有一种特殊情况：

```
a=11.4514
b=11.45141919810
g(a,b)=4(c=11.4514)
```

此时 $a$ 为 $b$ 的前缀，$g(a,b)=f(a)$。

注意代码里处理这种情况的细节。

完整代码：

```cpp
#include<bits/stdc++.h>
#define N 100005
#define T 3000005
using namespace std;
int n,x[N];string y[N];
inline int read_int(){
	int x(0);char c(getchar());
	while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9') x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return x;
}
inline string read_str(){
	string s;char c(getchar());
	while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9') s=s+c,c=getchar();
	return s;
}
int id[N];
inline bool cmp(const int&a,const int&b){return x[a]<x[b];}
int cnt,son[T][10],flg[T],ans[N];
inline void Insert(string s,int d){
	int u(0);
	for(int i(0);i<s.size();++i){
		flg[u]+=d;
		int val(s[i]^48);
		if(!son[u][val]) son[u][val]=++cnt;
		u=son[u][val];
	}
	//注意这里不需要flg[u]+=d
}
inline int Query(string s){
	int res(0),u(0);
	for(int i(0);i<s.size();++i){
		res+=flg[u];
		int val(s[i]^48);
		if(!son[u][val]) break;
		u=son[u][val];
	}
	return res;
}
inline void Solve(int l,int r){
	for(int i(l);i<=r;++i) Insert(y[id[i]],1);
	for(int i(l);i<=r;++i) ans[id[i]]+=Query(y[id[i]]);
	for(int i(l);i<=r;++i) Insert(y[id[i]],-1);
}
int main(){
	n=read_int();
	for(int i(1);i<=n;++i){
		x[i]=read_int();
		y[i]=read_str();
	}
	for(int i(1);i<=n;++i) id[i]=i;
	sort(id+1,id+1+n,cmp);
	for(int i(1),lst(1);i<=n;++i)
		if(i==n||x[id[i]]^x[id[i+1]]){
			Solve(lst,i);
			lst=i+1;
		}
	for(int i(1);i<=n;++i) printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：N0_1 (赞：1)

关于本题的分析各位大佬已经讲的非常详细了，本文不在此说明。
本文主要写关于本题的其他实现方法。

将小数点当成编号为 $10$ 的点，即在建树过程中

```int x = (ch == '.' ? 10: ch - '0');```

这样在查询过程中，只需要一个布尔参数 $flag$ 来记录是否到了小数点部分。

在只考虑字符串 ```a``` 是字符串 ```b``` 的前缀时（或者 ```b``` 是 ```a``` 的前缀），不难发现在查询 ```a``` 时，答案为 $s_{i}$ 是 ```a``` 的前缀与 ```a``` 是 $s_{i}$ 的前缀之和。

令 $flag$ 表示是否已经到达了小数点后面，$cnt_{rt}$ 表示经过 ```rt``` 节点的个数。

在查询过程中，对于遍历到的每一个 ```rt``` 节点，只需要对 $cnt_{rt}$ 求和即可（~~想想为什么？~~）。

```
int query(const string &s) {
	int rt = 0, sum = 0;
	bool flag = 0;
	for (auto &ch: s) {
		int x = (ch == '.' ? 10: ch - '0');
		rt = trie[rt][x];

		sum += cnt[rt] * flag;
		flag |= (x == 10);
	}
	
	return sum;
}
```

引申到这种情况
```
a = 1.19198
b = 1.114
```
很明显的知道 ```a``` 对 ```b``` 的贡献为 $g(a, b) = 1 + 1$，即当 ```a``` 不是 ```b``` 的前缀且 ```b``` 不是 ```a``` 的前缀时， $g(a, b) = len + 1$，其中 ```len``` 为 ```a``` 和 ```b``` 的最长公共前缀。

对于这种情况，只需要查询时统计已经计算过了多少个完整的 $s_{i}$ 加上以 ```a``` 为前缀的个数，最后返回时维护答案为：

$$sum + n - tmp - (cnt_{rt} - ed_{rt})$$

其中 $tmp$ 为查询过程中计算过的完整的 $s_{i}$ 的个数，$ed_{rt}$ 表示以 ```rt``` 节点为结尾的个数。$cnt_{rt} - ed_{rt}$ 表示以 ```a``` 为前缀的个数。

则有：
```
int query(const string &s) {
	int rt = 0, tmp = 0, sum = 0;
	bool flag = 0;
	for (auto &ch: s) {
		int x = (ch == '.' ? 10: ch - '0');

		rt = trie[rt][x];
		
		if (flag) {
			sum += cnt[rt];
			tmp += ed[rt];
		}
		flag |= (x == 10);
	}
	return sum + n - tmp - (cnt[rt] - ed[rt]);
}
```

还有一种情况：
```
a = 15.11
b = 1.11
```
此时 ```a``` 对 ```b``` 的贡献应该是 $0$，但在上一份代码的查询过程中，由于我们的答案是通过的 $n$ 的大小来维护的，此时答案会超出（超出部分为与 ```b``` 整数部分不同的数的个数），所以应当再统计一下具有相同整数部分的数个数 $num$，最后维护的答案即为：

$$sum + num - tmp - (cnt_{rt} - ed_{rt})$$

最后附上完整的代码（仅供参考，请勿抄袭）：
```cpp
#include<bits/stdc++.h>

using namespace std;

const int N = 3e6 + 10;
int trie[N][15], cnt[N], ed[N], tot = 0;
string ss[N];
int n; 

void Insert(const string &s) {
	int rt = 0;
	for (auto &ch: s) {
		int x = (ch == '.' ? 10: ch - '0');
		if (!trie[rt][x]) trie[rt][x] = ++tot;
		rt = trie[rt][x];
		cnt[rt] ++;
	}
	ed[rt] ++;
}

int query(const string &s) {
	int rt = 0, tmp = 0, num = 0, sum = 0;
	bool flag = 0;
	for (auto &ch: s) {
		int x = (ch == '.' ? 10: ch - '0');

		rt = trie[rt][x];
		
		if (flag) {
			sum += cnt[rt];
			tmp += ed[rt];
		}
		flag |= (x == 10);
		
		if (flag && !num) num = cnt[rt];
	}
	return sum + num - tmp - (cnt[rt] - ed[rt]);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> ss[i];
		Insert(ss[i]);
	}
	
	for (int i = 1; i <= n; i++) {
		cout << query(ss[i]) << "\n";
	}

	return 0;
}
/*
6
2
1.114
1.114
1.1145
1.1145
1.1145
*/
```



---

## 作者：konyakest (赞：1)

## 前置分析

首先我们先考虑整数部分相同的情况

这种情况中，$g(a_i,a_j)$ 取决于 $a_i$、$a_j$ 的**最长公共前缀**长度

进一步分析，我们可以得到：

- 如果 $a_i$、$a_j$ 的小数部分一个是另一个的前缀，则答案为较短的数的小数部分的长度

- 否则，设 $a_i$、$a_j$ 小数点后前 $k$ 位相同而第 $k+1$ 位不同，则答案为 $k+1$

然后，我们发现，如果 $a_i$、$a_j$ 的整数部分不同，则 $g(a_i,a_j)=0$

## 算法

对于一个串，统计它与其他串的最长公共前缀，我们可以想到字典树

我们对每个整数部分开一个字典树（用 ``map`` 一类的东西实现），先把所有串对应加到字典树上，然后在字典树上查找即可

具体地，我们记录每个节点的 ``siz``、``cnt`` 分别表示这个节点的子树中有几个字符串，以这个节点结尾的有几个字符串，然后查询如下：

```cpp
int dfs(string s){
    int node=0,ans=0;
    F(i,0,s.size()-1){
        Trie_node& now=v[v[node].mp[s[i]-'0']];
        ans+=(v[node].cnt-now.cnt)*(i+1);//其他分支的数目乘以当前长度
        ans-=v[node].siz-1;              //如情况一所说，这些部分的长度被多算了1，所以要减去
        node=v[node].mp[s[i]-'0'];
    }
    return ans+(v[node].siz-1+(v[node].cnt-v[node].siz))*s.size();
}
```

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define F(i,j,k) for(auto i=j;i<=k;i++)
#define view(x) begin(x),end(x)
#define pb push_back
const int maxn=1e5+5;

struct Trie{
    struct Trie_node{
        int cnt,siz;
        unordered_map<int,int> mp;
    };
    vector<Trie_node> v={{}};
    void insert(string s){
        int node=0;
        for(auto i:s){
            v[node].cnt++;
            if(!v[node].mp[i-'0']) v[node].mp[i-'0']=v.size(),v.pb({});
            node=v[node].mp[i-'0'];
        }
        v[node].cnt++;
        v[node].siz++;
    }
    int dfs(string s){
        int node=0,ans=0;
        F(i,0,s.size()-1){
            Trie_node& now=v[v[node].mp[s[i]-'0']];
            ans+=(v[node].cnt-now.cnt)*(i+1);
            ans-=v[node].siz-1;
            node=v[node].mp[s[i]-'0'];
        }
        return ans+(v[node].siz-1+(v[node].cnt-v[node].siz))*s.size();
    }
};

unordered_map<string,Trie> mp;

int n;
string s[maxn],pre[maxn],las[maxn];

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n;
    F(i,1,n) cin>>s[i];
    F(i,1,n){
        bool f=0;
        for(auto j:s[i]){
            if(f) las[i]+=j;
            else if(j!='.') pre[i]+=j;
            if(j=='.') f=1;
        }
        mp[pre[i]].insert(las[i]);
    }
    F(i,1,n) cout<<mp[pre[i]].dfs(las[i])<<endl;
    return 0;
}
```

---

## 作者：xrz114514 (赞：0)

# P9218 题解
## [题目](https://www.luogu.com.cn/problem/P9218)
## 思路
可以用字典树求解。

如果两数的整数部分都不一样，则他们的 $g$ 的值一定为 0，所以可以将每个整数部分分别讨论。

如果两数的整数部分相同，发现此时 $g$ 函数其实就两种情况：
- 要么是第一个两个数小数部分不一样的地方的精度，也就是字典树中分岔的地方。
- 要么是两个数中精度最小的数的精度，则此时他们成前缀关系。
  
所以，可以将他的小数部分用 string 存储，这样，就成了字典树板子了。

注意！！！直接全部清空会炸，所以要将所有遍历道德进行清空。

时间 $O((\sum\limits_{i = 1}^{n} len ) \cdot \log n)$。

## 代码


```cpp
#include <bits/stdc++.h>
#define fi first
#define se second

using namespace std;
using ll = long long;

const int N = 3e6 + 5;

int n;
ll ans[N];
map<int, vector<pair<int, string>>> mp;

struct Trie{
  int tot = 1, nex[N][10], cnt[N];

  void Init(){
    fill(cnt, cnt + tot + 1, 0);
    fill(&nex[0][0], &nex[tot][9] + 1, 0);
    tot = 1;
  }

  void Insert(const string &s){
    int rt = 0;
    for(int i = 0; i < s.size(); ++i){
      int c = s[i] - '0';
      if(!nex[rt][c]){
        nex[rt][c] = ++tot;
      }
      cnt[rt]++;
      rt = nex[rt][c];
    }
    cnt[rt]++;
  }

  ll Query(const string &s){
    int rt = 0;
    ll res = 0;
    for(int i = 0; i < s.size(); ++i){
      int c = s[i] - '0';
      ll sum = 0;
      for(int j = 0; j <= 9; ++j){
        if(j == c || !nex[rt][j]){
          continue;
        }
        sum += cnt[nex[rt][j]];
      }
      //cout << s << ' ' << (i + 1) << ' ' << (sum) << '\n';
      //cout << s << ' ' << (cnt[rt] - sum - cnt[nex[rt][c]]) << ' ' << i << '\n';
      res += 1ll * sum * (i + 1) + (cnt[rt] - sum - cnt[nex[rt][c]]) * i;
      rt = nex[rt][c];
    }
    res += 1ll * cnt[rt] * (int)s.size();
    return res;
  }
}T;

int main(){
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  for(int i = 1, x; i <= n; ++i){
    char c;
    string s;
    cin >> x >> c >> s;
    mp[x].push_back({i, s});
  }
  for(auto it : mp){
    T.Init();
    for(auto i : it.se){
      T.Insert(i.se);
    }
    for(auto i : it.se){
      ans[i.fi] = T.Query(i.se);
    }
  }
  for(int i = 1; i <= n; ++i){
    cout << ans[i] << '\n';
  }
  return 0;
}

```

---

## 作者：wpl123456wpl (赞：0)

# 题目描述

给定 $n$ 个非负小数 $a_1, a_2, a_3, a_4, \ldots, a_n$。$a_i$ 的精度 $f(a)$ 代表非负整数 $k$，使 $10^k \times a$ 小数部分为 0，求出最小 $k$。$g(a,b)$ 的定义为在 $\min(a,b)$ 到 $\max(a,b)$ 的所有数中，函数 $f$ 的最小值，**保证 $a_i$ 没有后导 0**。

让求出对于每个 $1 \le i \le n$ 输出 $\sum_{j = 1}^{n} g(a_i,a_j)$。

# 思路分析

首先，先让它们位与位对齐，将整数部分都补为 9 位数，去除小数点。1.1451 与 1.1454，它们在小数部分第 4 位开始不同，$g(1.1451,1.1454) = 4$，很明显吧。1.145 与 1.1451419，在第一个小数部分比较结束后与第二个小数位部分任未有不同之处，这是 $g(1.145,1.1451419) = 3$，$f(1.145)$ 达到最小值 $3$，也比较明显。

这时，将小数当成字符串，先进行补前导 0，在从左往右，从数字高位往数字低位扫。假设这一位上有 $x$ 不一样的就代表与这些数字的 $g$ 值已经求解出来，不在需要处理，只需要管还未出现不同数位的数字。扫完后，还有数字未被求解，那么就是第二种情况。这可以使用 01Tire 求解维护，每次更新当前位置 rt 只管往自身当前位置递进，因为其他位置已经可以在本轮求解。

# code

```cpp
#include<bits/stdc++.h>

using namespace std;
using ll = long long;

const int N = 1e5 + 5, M = 4e6 + 5;

int n;
string s[N], t;

struct edge{
  int son[10];
};

struct Tire{
  edge g[M];
  int len, cnt[M];
  void Insert(const string &s){
    int rt = 0;
    for(int i = 0; i < s.size(); i++){
      int ch = s[i] - '0';
      cnt[rt]++;
      if(!g[rt].son[ch]) g[rt].son[ch] = ++len;
      rt = g[rt].son[ch];
    }
  }
  ll query(const string &s){
    ll sum = 0;
    int rt = 0;
    for(int i = 0; i < s.size(); i++){
      int ch = s[i] - '0';
      sum += 1ll * max(0, i - 8) * (cnt[rt] - cnt[g[rt].son[ch]]); // 还有整数部分不能算，原式 (i + 1) - 9。当前未改动时的叶子个数 - 改动后的叶子个数 = 当前位数出现不同的叶子个数。
      rt = g[rt].son[ch];
    }
    return sum + 1ll * max(0, int(s.size()) - 9) * cnt[rt];//第二种情况要加上。
  }
}d;

int main(){
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n;
  for(int i = 1; i <= n; i++){
    cin >> s[i];//未保证单次小数部分长度。
  }
  for(int i = 1; i <= n; i++){
    int cnt = 0;
    t = s[i];
    for(int j = 0; j < t.size() && t[j] != '.'; j++){
      cnt++;
    }
    s[i] = "";
    while(cnt < 9){
      cnt++;
      s[i] += '0';
    }
    for(int j = 0; j < t.size(); j++){
      if(t[j] != '.') s[i] += t[j];
    }
    d.Insert(s[i]);
  }
  for(int i = 1; i <= n; i++){
    cout << d.query(s[i]) << '\n';
  }
  return 0;
}
```

---

## 作者：_Chronostatis_ (赞：0)

## 题意
给定 $n$ 个小数 $a_1, a_2, \dots, a_n$，定义 $f(x)$ 为 $x$ 的小数位数，$g(x, y) = \min \limits_{x \le i \le y} f(x)$。对于 $1 \le i \le n$，求 $\sum \limits_{j = 1}^n g(a_i, a_j)$。

## 思路
炒鸡模拟题。

观察性质。举个例子，两个小数 $114.514, 114.524$：

![](https://cdn.luogu.com.cn/upload/image_hosting/1ydsa6g7.png)

注意到，设两个小数 $a, b$ 的整数部分相同，在小数点后第 $i$ 位第一次遇到不同，那么 $f_{\min}(x)$ 的自变量取值就可以确定，此时 $f(x)$ 的值为 $i$。所以，对于整数部分相同的小数，我们可以使用字典树求答案，可以只记录小数点后面的数位。

具体地，可以对字典树中的每个节点记录一个经过次数 $cnt_i$，每次遍历到一个结点时，要将答案加上当前结点的子节点中除当前下一步要访问的节点外所有节点的 $cnt$，并将答案乘上下一位的的数位下标。因为当前搜索的数与这些数的答案为下一位数位下标。

注意，遇到前缀（即一个字符串是另一个字符串的前缀）时，例如 $114.514$ 和 $114.5$，此时 $f_{\min}(x) = 1$，需要在遍历第二位时，将上一位的答案加上。

对于整数部分不同的小数，可以分开处理。

## 代码
```cpp
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int MAXN = 1e5 + 10;

int n, l, len[MAXN];
ll res[MAXN];
pair<string, int> s[MAXN];
string t[MAXN];

struct Trie {
  int nxt[MAXN * 30][10], tot = 1;
  ll cnt[MAXN * 30];
  void Init() {
    for (int i = 1; i <= tot; i++) {
      cnt[i] = 0;
      for (int j = 0; j < 10; j++) {
        nxt[i][j] = 0;
      }
    }
    tot = 1;
  }
  void Insert(string &s) {
    int k = 1;
    for (char c : s) {
      int r = c - '0';
      if (!nxt[k][r]) nxt[k][r] = ++tot;
      k = nxt[k][r], cnt[k]++;
    }
  }
  ll Find(string s, int v) {
    int k = 1;
    ll ans = 0;
    for (int i = 0; i < len[v]; i++) {
      char c = s[i];
      int r = c - '0', sum = 0;
      for (int j = 0; j < 10; j++) {
        sum += cnt[nxt[k][j]];
        if (j == r) continue;
        ans += cnt[nxt[k][j]] * (i + 1);
      }
      if (i) ans += (cnt[k] - sum) * i;
      k = nxt[k][r];
    }
    return ans + cnt[k] * len[v];
  }
} T;

bool C(string &a, string &b) {
  int i = a.find('.'), j = b.find('.');
  return a.substr(0, i + 1) != b.substr(0, j + 1);
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> s[i].first;
    s[i].second = i;
  }
  sort(s + 1, s + n + 1);
  for (int i = 1; i <= n; i++) {
    t[i] = s[i].first;
    int r = s[i].first.find('.');
    s[i].first = s[i].first.substr(r + 1);
    len[i] = s[i].first.size();
    l = max(l, int(s[i].first.size()));
  }
  int last = 1;
  for (int i = 1; i <= n; i++) {
    if (i == 1 || C(t[i], t[i - 1])) {
      for (int j = last; j < i; j++) {
        res[s[j].second] = T.Find(s[j].first, j);
      }
      last = i;
      T.Init();
    }
    T.Insert(s[i].first);
  }
  for (int i = last; i <= n; i++) {
    res[s[i].second] = T.Find(s[i].first, i);
  }
  for (int i = 1; i <= n; i++) {
    cout << res[i] << '\n';
  }
  return 0;
}
```

---

## 作者：leiaxiwo (赞：0)

# 题解：P9218 「TAOI-1」Apollo
[传送门](https://www.luogu.com.cn/problem/P9218)

### 题意分析
这道题乍一看和 trie 没什么关系，但是
对于两个十进制小数 $a$ 和 $b$：

如果 $\lfloor a \rfloor = \lfloor b \rfloor$，$g(a,b)$ 显然是 $a$ 与 $b$ 小数部分**最长公共前缀的长度**。否则 $g(a,b)=0$。

如果我们将这些小数看成字符串，这就变成了一道寻找字符串间最大公共前缀的题目，这样就能用 trie 完成它了。

那么我们不妨统计 $a$ 和 $b$ 在字典树上第 $i$ 位小数的的经过次数 ${cnt}_{i}$，它的深度 ${deep}_{i}$，以及它的父节点 $father$。

当 $f(a) \leq f(b)$ 且 $g(a,b) \neq f(a)$ 时，$a$ 与 $b$ 不在 trie 的同一条链上，二者的 $i$ 点对答案的贡献为 ${d}_{i} \times ({cnt}_{father} - {cnt}_{i})$。

其中 ${cnt}_{father} - {cnt}_{i}$ 表示以 $father$ 为父节点的除去 $i$ 号点的儿子个数，${d}_{i}$ 等价于字符串中的最大公共前缀。

当 $f(a) \leq f(b)$ 且 $g(a,b)=f(a)$ 时，$a$ 与 $b$ 在字典树的同一条链上，需要特殊处理：

统计树上 $i$ 号点被作为终点的次数 ${e}_{i}$，可以得到贡献为 ${d}_{i} \times ({cnt}_{father} - {cnt}_{i} - {e}_{father} + {e}_{i})$，并且如果这个点是 $a$ 点，还要加上 $a$ 终点的儿子节点的 $cnt$ 之和。因为还存在 $g(a,b)=0$ 的情况，我们可以特殊处理。


那么这题就结束战斗了。
### 参考代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,p,c;
int a,b,tot;
int ans,deep,u;
int trie[3000005][15],cnt[3000005],en[3000005];
string s[100005];
struct __Trie{
	void insert(string x){
		a=0;
		p=0;
		u=1;
		for(b=0;x[b]!='.';b++){
			a=a*10+(x[b]-'0');
		}
		for(int i=1;i<=9;i++){
			u*=10;
		}
		for(;u;u/=10){
			c=a/u%10;
		    if(!trie[p][c]){
		    	trie[p][c]=++tot;
			}	
			p=trie[p][c];
			cnt[p]++;
		}
		for(int i=b+1;i<x.size();i++){
			c=x[i]-'0';
		    if(!trie[p][c]){
		    	trie[p][c]=++tot;
			}	
			p=trie[p][c];
			cnt[p]++;
		}
		en[p]++;
		return ;
	}
	void find(string x){
	    ans=p=deep=a=0,u=1;
	    for(b=0;x[b]!='.';b++){
	    	a=a*10+(x[b]-'0');
		} 
	    for(int i=1;i<=9;i++){
	    	u*=10;
		} 
	    for(;u;u/=10){
		    c=a/u%10;
		    p=trie[p][c];
	    }
	    for(int i=b+1;i<x.size();i++){
		    c=x[i]-'0';
			deep++;
		    ans+=deep*(cnt[p]-cnt[trie[p][c]]-en[p]+en[trie[p][c]]);
	    	p=trie[p][c];
    	}
    	for(int i=0;i<=9;i++){
	    	if(trie[p][i]){
	    		ans+=deep*cnt[trie[p][i]];
			} 
    	}
	    printf("%lld\n",ans); 
    }
}liver_trie;
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		cin>>s[i];
		liver_trie.insert(s[i]);
	}
	for(int i=1;i<=n;i++){
		liver_trie.find(s[i]);
	}
	return 0;
}
```

---

