# [ABC268D] Unique Username

## 题目描述

高桥君有取名选择困难症，于是他找到你，希望帮他取一个用户名。

具体取名规则是：把给定的 $N$ 个字符串 $S_1，S_2,\ldots,S_N$ 以任意顺序排列，并在每两个字符串中间加 $\ge1$ 个下划线，要求不能与后面给定的 $M$ 个字符串 $T_1，T_2,\ldots,T_M$ 中的任意一个相同。

其中，你给出的字符串的长度 $X$ 应该满足 $3\le X \le 16$ 。如果无法满足条件，输出 $-1$。

## 样例 #1

### 输入

```
1 1
chokudai
chokudai```

### 输出

```
-1```

## 样例 #2

### 输入

```
2 2
choku
dai
chokudai
choku_dai```

### 输出

```
dai_choku```

## 样例 #3

### 输入

```
2 2
chokudai
atcoder
chokudai_atcoder
atcoder_chokudai```

### 输出

```
-1```

## 样例 #4

### 输入

```
4 4
ab
cd
ef
gh
hoge
fuga
____
_ab_cd_ef_gh_```

### 输出

```
ab__ef___cd_gh```

# 题解

## 作者：2020luke (赞：6)

# [ABC268D] Unique Username

## 思路解析

根据题目中“以任意顺序排列”以及 $1\le N\le8$ 可以想到用 dfs 做。但是需要分成两块搜索，分别是单词的顺序和下划线的数量。还需要进行剪枝操作，也就是当当前用户名（包括当前已有的下划线和剩下至少要放的下划线）大于 $16$ 时，就 `return` 回溯。而当 $t>n$ 也就是所有单词选完后，我们还要判断新用户名是否在 $T$ 中出现过，可用 `set` $O(n\log n)$ 快速判断 ，**以及判断长度 $X$ 应满足 $3\le X\le16$**，若可行，则输出字符串并 `exit(0)` 终止程序。最后由于第一个单词之前没有下划线，所以要遍历每一个单词开始。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, m;
string str1[10], str2;
set<string> st;
bool vis[10];
int sum = 0;
void dfs(int t, string s, int sum_) {
	if(s.size() > 16) {
		return;
	}
	if(t > n) {
		if(st.find(s) == st.end() && s.size() >= 3) {
			cout << s;
			exit(0);
		}
		return;
	}
	for(int i = 1; i <= n; i++) {
		if(!vis[i]) {
			string tmp_;
			for(int j = 1; j <= 16; j++) {
				tmp_ += '_';
				if(sum + sum_ + j + n - t - 1 <= 16) {
					vis[i] = true;
					dfs(t + 1, s + tmp_ + str1[i], sum_ + j);
					vis[i] = false;
				}
				else {
					break;
				}
			}
		}
	}
}
int main() {
	cin >> n >> m;
	for(int i = 1; i <= n; i++) {
		cin >> str1[i];
		sum += str1[i].size();
	}
	for(int i = 1; i <= m; i++) {
		cin >> str2;
		st.insert(str2);
	}
	for(int i = 1; i <= n; i++) {
		vis[i] = true;
		dfs(2, str1[i], 0);
		vis[i] = false;
	}
	cout << -1;
	return 0;
}
```

---

## 作者：Empty_Dream (赞：2)

## 题意

[题面传送门](https://www.luogu.com.cn/problem/AT_abc268_d)

## 分析

题目一眼看出是 dfs 暴搜的题，只需要先全排列一下每一个字符串的顺序，再根据字符串已有的长度去再 dfs 一遍中间插入 `_` 的数量。

对于不能重复，易得通过一个 map 去存储已经出现的 string，最后在 dfs 找到答案的时候看一下 map 中有没有出现即可。

注意：长度要满足 $3 \le X \le 16$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int n, m;
int a[10], vis[10];
string s[10], t[100005];
vector<string> v;
map<string, int> mp;

void dfs1(int x, int sum){
	if (sum < 0) return ;
	if (x == n){
		if(16 - sum < 3) return;
		string ans = v[0];
		for (int i = 1; i < n; i++){
			for (int j = 1; j <= a[i]; j++) ans += "_";
			ans += v[i];
		}
		if (mp[ans] == 0) cout << ans, exit(0);
		return ;
	}
	for (int i = 1; i <= sum; i++){
		a[x] = i;
		dfs1(x + 1, sum - i);
	}
}

void dfs(int x, int sum){
	if (x == n + 1){
		memset(a, 0, sizeof(a));
		dfs1(1, 16 - sum);
		return ;
	}
	for (int i = 1; i <= n; i++){
		if (vis[i] == 0){
			v.push_back(s[i]), vis[i] = 1;
			dfs(x + 1, sum + s[i].size());
			vis[i] = 0, v.pop_back();
		}
	}
}

int main(){
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> s[i];
	for (int i = 1; i <= m; i++){
		cin >> t[i];
		mp[t[i]] = 1;
	}
	dfs(1, 0);
	cout << -1;
	return 0;
}
```

---

## 作者：Expert_Dream (赞：2)

[博客园](https://www.cnblogs.com/gsczl71/p/17880643.html)。

这一道题的精髓在于：暴搜。

一看 $n \le 8$。简直就是随便搞都可以。他是任意一种情况都可以，那就更简单了。考虑最最暴力的写法。枚举每一个点开始，然后枚举多少个 `_`，然后深搜下去。肯定是会超时。

所以考虑剪枝，通过计算可以得出来之后会不会超过 $16$ 的长度。如果会超过，则退出，这其实已经加快了很多，所以，一提交，你就发现水了一个绿题。

[link](https://atcoder.jp/contests/abc268/submissions/49024495)。

---

## 作者：kczw (赞：2)

# 题意
求能否将给定 $n$ 个字符串用 $\geq1$ 个下划线按任意顺序链接成一个长度大于等于 $3$ 并且 小于等于 $16$ 字符串，并且保证组成后的字符串未在给定的 $m$ 个字符串中出现过。

# 思路
因为 $n\leq8$，直接 DFS 暴搜就可以了，时间复杂度约为 $O(n!)$。

同时关于维护最后的字符串是否在 $m$ 个字符串中出现过，可以用 set 维护。
# 实现 
```cpp
#include<iostream>
#include<set>
using namespace std;
set<string> M;
int n,m,vist[15];
string s[15];
void dfs(string x,int k){
	if(k==n&&!M.count(x)&&x.size()>2){
		cout<<x;
		exit(0);//满足条件，退出程序
	}for(int i=1;i<=n;i++)
		if(!vist[i]){
			vist[i]=1;
			string ss="_";
			while(ss.size()+x.size()+s[i].size()<=16)dfs(x+ss+s[i],k+1),ss+="_";
			vist[i]=0;
		}
}int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)cin>>s[i];M.insert("");
	for(int i=1;i<=m;i++)cin>>s[0],M.insert(s[0]);
	for(int i=1;i<=n;i++){
		vist[i]=1;
		dfs(s[i],1);
		vist[i]=0;
	}printf("-1",0);
	return 0;
}
```


---

## 作者：FFTotoro (赞：2)

赛时做出了 D 却没做出 C，这是什么原因。。。

本题可以使用深度优先搜索 dfs。

搜索过程如下：

1. 首先，枚举作为开端的字符串；

2. 其次，枚举下一个字符串；

3. 接着，枚举两个字符串之间下划线的数量；

4. 将目前的字符串当作第一步“开端的”字符串并将当前搜索过的字符串打上标记，返回第二步继续搜索；

在第 2 步中如果用完了所有的字符串，那么就判断一下搜到的字符串是否合法，如果合法那么就输出这个答案。

用一个 `std::set` 存放所有不能使用的用户名，最终搜到答案时用 `find` 函数判断答案是否合法即可。

注意，这里有一个坑点，就是最终搜到的答案**长度必须不小于 $3$**，赛时被这玩意坑了 2 次 WA。错在这个地方的程序可以用如下的一组数据 hack 掉：

```
1 1
a
x
```

正确答案应该是 `-1`，而错误的程序会输出 `a`。

放代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
string a[9];
set<string> b;
bool x[9]; int n,m;
bool dfs(int t,string s){
    if(s.length()>=3&&t>=n&&b.find(s)!=b.end()){
        cout<<s<<endl;
        return true;
    }
    for(int i=1;i<=n;i++)
        if(!x[i]){
            for(int j=1;j<=16;j++){
                string tt=s; for(int k=1;k<=j;k++)tt+="_"; tt+=a[i];
                if(tt.length()>16)break; x[i]=true;
                if(tt.length()>=3&&dfs(t+1,tt))return true; x[i]=false;
            }
        }
    return false;
}
int main(){
    ios::sync_with_stdio(false);
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=m;i++){
        string s; cin>>s;
        b.emplace(s);
    }
    for(int i=1;i<=n;i++){x[i]=true; if(dfs(1,a[i]))return 0; x[i]=false;}
    cout<<"-1\n";
    return 0;
}
```

---

## 作者：_qingshu_ (赞：1)

# 题意：

有 $N$ 个字符串，你可以以任意顺序将其排序，且需要在任意两个相邻字符串之间增加 $\ge 1$ 个下划线，且最后不能与给出的 $M$ 个字符串中的任意一个相同。

你需要保证最后的字符串长度 $X$ 应该满足 $3\le X \le 16$。

# 思路;

看到 $1\le N \le 8$ ，说明完全是可以暴力求解的，我们钦定一个开头的字符串，然后 dfs 下一个的字符串与中间下划线个数，如果用完了就判断一下是否在 $M$ 个中与长度是否达标就好了。

# Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
map<string,bool>check;
string s[520],t;
bool flag[520];
void dfs(int id,string now,int num){
	if(num==n){
		if(!check[now]&&now.size()>=3){
			cout<<now;
			exit(0);
		}
		return;
	} 
	flag[id]=1;
	for(int i=1;i<=n;i++){
		if(!flag[i]){
			flag[i]=1;
			for(int j=1;;j++){
				if(now.size()+s[i].size()+j>16){
					break;
				}
				else{
					string res=now;
					for(int k=1;k<=j;k++){
						res+='_';
					}
					dfs(i,res+s[i],num+1);
				}
			}
			flag[i]=0;
		}
	}
	flag[id]=0;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>s[i];
	}
	for(int i=1;i<=m;i++){
		cin>>t;
		check[t]=1;
	} 
	for(int i=1;i<=n;i++){
		dfs(i,s[i],1);
	}
	cout<<"-1";
} 
```

---

## 作者：Tsawke (赞：1)

# [[ABC268D] Unique Username](https://www.luogu.com.cn/problem/AT_abc268_d) Solution

[TOC]

## [更好的阅读体验戳此进入](http://blog.tsawke.com?t=ABC268D)

## 题面

给定 $ n $ 各字符串，另外给定 $ m $ 个字符串。你需要对 $ n $ 个字符串进行排列，并在每相邻两个字符串中间插入至少一个下划线，并且最终字符串与给定的 $ m $ 个字符串均不同。输出任意一个长度在 $ [3, 16] $ 的方案。

## Solution

第一眼没什么想法，看了一眼数据范围才反应过来这似乎就是个暴力，我们尝试分析一下：

令 $ n $ 个字符串总长度和为 $ s $，我们还要至少插入 $ n - 1 $ 个下划线，那么剩下的可能长度就只有 $ 16 - s - (n - 1) = 17 - n - s $，同时显然 $ s \ge n $。对于剩下的长度不难发现可以认为其是将下划线可空地放入 $ n - 1 $ 个不同盒子里，显然这就是 $ 17 - n - s $ 个可空的不同球盒问题。关于球盒问题可以去看我的 Blog：[浅析排列组合、斯特林数、贝尔数、二项式定理与推论及其反演、子集反演、广义容斥](http://blog.tsawke.com?t=Permutation-Combination)。再加上枚举全排列的 $ n! $，最终的复杂度大约是：
$$
O(n! \sum_{i = 0}^{17 - n - s} \dfrac{(i - 1 + n - 1)!}{(n - 2)!(i - 1 + n - 1 - (n - 2))!})
$$
化简一下：
$$
O(n! \sum_{i = 0}^{17 - n - s} \dfrac{(i + n - 2)!}{(n - 2)!i!})
$$
这一大坨东西我不知道我是否分析错了，不过大概也八九不离十，总之这个东西我们随便带入几个 $ n $ 算一下，或者感性理解一下发现显然是远小于 $ 1e8 $ 的，所以暴力即可通过。

做法的话先通过调用 $ n! $ 次 `next_permutation()` 函数枚举全排列，此时还会多一个 $ O(n) $ 的常数，不过区别不大。

然后每次跑一遍深搜，用 `string` 的本质是 `basic_string`，且 `basic_string` 支持 `+` 和 `+=` 等的特性，即可十分便捷地实现一般的深搜思路，注意每两个之间至少插入一个下划线，且注意需要限制最多额外添加 $ 17 - n - s $ 个下划线，否则复杂度是不正确的。

## Code

```cpp
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

#define PI M_PI
#define E M_E
#define npt nullptr
#define SON i->to
#define OPNEW void* operator new(size_t)
#define ROPNEW void* Edge::operator new(size_t){static Edge* P = ed; return P++;}

using namespace std;

mt19937 rnd(random_device{}());
int rndd(int l, int r){return rnd() % (r - l + 1) + l;}
bool rnddd(int x){return rndd(1, 100) <= x;}

typedef unsigned int uint;
typedef unsigned long long unll;
typedef long long ll;
typedef long double ld;

template < typename T = int >
inline T read(void);

int N, M;
int mx(-1);
string S[10];
unordered_set < string > block;
string ans;

void dfs(int dep = 1, int lft = mx, string cur = string()){
    if(dep > N){
        if(3 <= (int)cur.length() && (int)cur.length() <= 16 && block.find(cur) == block.end())ans = cur;
        return;
    }
    if(dep == 1)return dfs(dep + 1, lft, cur + S[dep]);
    dfs(dep + 1, lft, cur + "_" + S[dep]);
    for(int i = 1; i <= lft; ++i)
        cur += "_", dfs(dep + 1, lft - i, cur + "_" + S[dep]);
}

int main(){
    N = read(), M = read();
    int slen(0);
    for(int i = 1; i <= N; ++i)cin >> S[i], slen += S[i].length();
    for(int i = 1; i <= M; ++i){string T; cin >> T; block.insert(T);}
    mx = 16 - slen - N + 1;
    if(mx < 0)printf("-1\n"), exit(0);
    int tot(1); for(int i = 1; i <= N; ++i)tot *= i;
    for(int i = 1; i <= tot; ++i)dfs(), next_permutation(S + 1, S + N + 1);
    if(ans.empty())printf("-1\n"), exit(0);
    cout << ans << endl;
    fprintf(stderr, "Time: %.6lf\n", (double)clock() / CLOCKS_PER_SEC);
    return 0;
}

template < typename T >
inline T read(void){
    T ret(0);
    int flag(1);
    char c = getchar();
    while(c != '-' && !isdigit(c))c = getchar();
    if(c == '-')flag = -1, c = getchar();
    while(isdigit(c)){
        ret *= 10;
        ret += int(c - '0');
        c = getchar();
    }
    ret *= flag;
    return ret;
}
```

## UPD

update-2023_01_18 初稿

---

## 作者：Register_int (赞：0)

~~为什么模拟赛要出这种恶心人的题~~

由于 $N\le8$，可以直接考虑搜索算法。问题在于 $M\le10^5$，因此要快速判断重复，并添加有效剪枝。

如何判重？将所有串插入字典树中，在拼接时更新对应节点。如果拼接完成后，指针恰好在词尾，那么说明这一分支搜索失败。

此外，还有一些剪枝优化：

1. 当搜索过程中，指针已经在字典树外，可直接拼接并输出。
2. 当后续串使用最优策略拼接仍无法满足长度要求，直接返回。
3. 返回值使用 `bool` 类型，搜到一个解后直接结束搜索。

最后要注意，答案串的长度需要大于等于 $3$，所以需要添加特判。

最大点可以跑到 $89\ \text{ms}$。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 1e5 + 10;
const int mod = 998244353;

int c[MAXN << 4][27], tot = 1; bool e[MAXN << 4]; 

inline 
void insert(char *s) {
	int k = 1;
	for (int i = 0, t; s[i]; i++) {
		t = s[i] == '_' ? 26 : s[i] - 'a';
		if (!c[k][t]) c[k][t] = ++tot; k = c[k][t];
	}
	e[k] = 1;
}

int n, m, l[10];

char s[10][17], t[17];

bool vis[10]; 

bool dfs(int k, int p, int x) {
	int len = -1;
	for (int i = 1; i <= n; i++) if (!vis[i]) len += l[i] + 1;
	if (x + len > 16) return 0;
	if (!p || k > n && !e[p]) {
		t[x] = 0, printf("%s", t);
		for (int i = 1, f = 0; i <= n; i++) {
			if (!vis[i]) f && (putchar('_'), 0), printf("%s", s[i]), f = 1;
		}
		return 1;
	}
	if (k > n) return 0;
	for (int i = 1, q; i <= n; i++) {
		if (vis[i]) continue; vis[i] = 1, q = p;
		for (int j = 0; j < l[i]; j++) q = c[q][s[i][j] - 'a'], t[x + j] = s[i][j];
		if (k == n) { if (dfs(k + 1, q, x + l[i])) return 1; }
		else for (int j = 0; j + x + len <= 16; j++) {
			t[x + l[i] + j] = '_', q = c[q][26];
			if (dfs(k + 1, q, x + l[i] + j + 1)) return 1;
		}
		vis[i] = 0;
	}
	return 0;
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%s", s[i]), l[i] = strlen(s[i]);
	if (n == 1 && l[1] < 3) return puts("-1"), 0;
	for (int i = 1; i <= m; i++) scanf("%s", t), insert(t);
	if (!dfs(1, 1, 0)) puts("-1");
}
```

---

