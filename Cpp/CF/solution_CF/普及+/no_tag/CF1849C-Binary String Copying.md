# Binary String Copying

## 题目描述

You are given a string $ s $ consisting of $ n $ characters 0 and/or 1.

You make $ m $ copies of this string, let the $ i $ -th copy be the string $ t_i $ . Then you perform exactly one operation on each of the copies: for the $ i $ -th copy, you sort its substring $ [l_i; r_i] $ (the substring from the $ l_i $ -th character to the $ r_i $ -th character, both endpoints inclusive). Note that each operation affects only one copy, and each copy is affected by only one operation.

Your task is to calculate the number of different strings among $ t_1, t_2, \ldots, t_m $ . Note that the initial string $ s $ should be counted only if at least one of the copies stays the same after the operation.

## 说明/提示

Consider the first example. Copies below are given in order of the input operations. Underlined substrings are substrings that are sorted:

1. 101100 $ \rightarrow $ 011100;
2. 101100 $ \rightarrow $ 011100;
3. 101100 $ \rightarrow $ 101100;
4. 101100 $ \rightarrow $ 101100;
5. 101100 $ \rightarrow $ 000111.

There are three different strings among $ t_1, t_2, t_3, t_4, t_5 $ : 000111, 011100 and 101100.

Consider the second example:

1. 100111 $ \rightarrow $ 100111;
2. 100111 $ \rightarrow $ 001111;
3. 100111 $ \rightarrow $ 001111;
4. 100111 $ \rightarrow $ 010111.

There are three different strings among $ t_1, t_2, t_3, t_4 $ : 001111, 010111 and 100111.

## 样例 #1

### 输入

```
3
6 5
101100
1 2
1 3
2 4
5 5
1 6
6 4
100111
2 2
1 4
1 3
1 2
1 1
0
1 1```

### 输出

```
3
3
1```

# 题解

## 作者：zfx_VeXl6 (赞：19)

先来看这样一个例子。

原串：`001101`，$l_1=2$，$r_1=6$。排完序后变成 `000111`。

设原串为 $s$，排序后的串为 $s'$，可以发现 $s_2=s_2'$，$s_6=s_6'$。

这是因为 $s_2$ 为 `0`，而 $[2,6]$ 这一区间中有 `0` 存在，当这一区间被排序后，$s_2'$ 必为 `0`，就与 $s_2$ 相等。$s_6$ 与 $s_6'$ 同理。所以对区间 $[2,6]$ 排序等价于对区间 $[3,5]$ 排序。

那么，当排序区间是 $[1,6]$ 时，也相当于对区间 $[3,5]$ 排序。

所以可以记录下每一个 `0` 右边第一个 `1` 的位置 $nxt_i$ 和每一个 `1` 左边第一个 `0` 的位置 $pre_i$，那么对区间 $[l,r]$ 排序就相当于对区间 $[nxt_l,pre_r]$ 排序。对于一组数据，最终的答案就是不同的 $[nxt_{l_i},pre_{r_i}]$ 的数量。

但这样做会遇到一个问题。还是上面的例子，对 $[1,3]$ 和 $[5,6]$ 排序，排序后的串是相同的。但按照上述的算法，$[1,3]$ 相当于 $[3,2]$，$[5,6]$ 相当于 $[6,5]$，在统计答案时会被算成两个。但是很明显，当 $nxt_l>pre_r$ 时，相当于没排序，因此看作 $[0,0]$ 就行了。

统计区间时可使用 ```unordered_map```，需要手写哈希函数。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define LL long long
const int N=2e5+2;
int t,n,m,nxt[N],pre[N],ans;
char s[N];
LL hsh(int x,int y){return 1LL*(n+1)*x+y;}
unordered_map<LL,int>vis;
int main()
{
    cin>>t;
    while(t--)
    {
        vis.clear();
        ans=0;
        cin>>n>>m;
        nxt[n+1]=n+1;
        scanf("%s",s+1);
        for(int i=1;i<=n;i++)
            if(s[i]=='1')
                pre[i]=pre[i-1];
            else
                pre[i]=i;
        for(int i=n;i;i--)
            if(s[i]=='0')
                nxt[i]=nxt[i+1];
            else
                nxt[i]=i;
        for(int i=1;i<=m;i++)
        {
            int l,r;
            cin>>l>>r;
            l=nxt[l];
            r=pre[r];
            if(l>r)
                l=r=0;
            if(!vis[hsh(l,r)])
            {
                ans++;
                vis[hsh(l,r)]=1;
            }
        }
        cout<<ans<<'\n';
    }
    return 0;
}
```

---

## 作者：liuhl_weifang (赞：11)

## 题意简述

给你一个长度为 $n$ 的 $01$ 字符串，你又生成了 $m$ 个和这个字符串一模一样的副本，第 $i$ 个副本命名为 $t_i$。还有 $m$ 次操作，第 $i$ 次操作会给出闭区间 $[l_i,r_i]$，表示将 $t_i$ 中 $[l_i,r_i]$ 的字符排序。所有操作完毕后，请你求出 $t_1,t_2,...,t_m$ 中有多少个不同的字符串。 

## 解题思路

观察下面的 $01$ 字符串：

$0011010011$

如果我将它排序，它就会变成这样：

$0000011111$

咦？我们注意到，字符串开头的两个 $0$ 和字符串末尾的两个 $1$，位置并没有发生变化！也就是说，如果我只对字符串的 $[3,8]$ 区间排序，效果是一样的！因此，我们可以把所有的 $[l_i,r_i]$ 区间，过滤掉左边的 $0$ 和右边的 $1$，把所有效果相同的排序都映射成同一个区间，这样就能去重啦！

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m;
char s[200010];
int l[200010];//左边第一个 0 的位置
int r[200010];//右边第一个 1 的位置
map<pair<int,int>,bool> p;

void solve()
{
	p.clear();
	cin >> n >> m >> s+1;
	int pos = 0;
	for (int i=1;i<=n;i++) 
	{
		if(s[i]=='0') pos = i;
		l[i] = pos;
	}
	pos = n+1;
	for (int i=n;i>=1;i--)
	{
		if(s[i]=='1') pos = i;
		r[i] = pos;
	}
	int ans = 0;
	for (int i=1;i<=m;i++)
	{
		int a,b;
		cin >> a >> b;
		a = r[a];//过滤掉左边的 0，相当于跳到右边的 1 
		b = l[b];//过滤掉右边的 1，相当于跳到左边的 0
		if(a>b) a = 1,b = 1;//这种情况属于排序排了个寂寞 
		if(p[make_pair(a,b)]==false)
		{
			p[make_pair(a,b)] = true;
			ans++;
		}
	}
	cout << ans << "\n";
	return;
} 
 
signed main()
{
	int t;
	cin >> t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：escapist404 (赞：8)

### Statement

给定 01 串 $s$，再给定 $m$ 个区间 $\lbrack l, r \rbrack$，代表将这个区间排序。

问排序后的 $m$ 个串有多少个本质不同，每个区间相互独立。

### Solution

考虑字符串 hash。

定义 hash 函数
$$
\mathrm{hash}(s) = \sum_{i = 0}^{n - 1}
\begin{cases}
base_i &\textrm{if }s_i = 1\\
0 &\textrm{if }s_i = 0
\end{cases}
$$

记录字符串的前缀 $[0, i)$ 的 hash 值为 $f_i$，全为 1 的前缀 $[0, i)$ 的 hash 值为 $g_i$，字符串前缀 $[0, i)$ 中 1 的个数 $h_i$。

假设排序的区间为 $[l, r)$，新的字符串 hash 值为

$$
f_n - f_r + f_l + g_r - g_{r - (h_r - h_l)}
$$

丢到 `std::set` 里维护就完了。

### Code

```cpp
#include <bits/stdc++.h>

using i64 = unsigned long long;

std::vector<i64> base;

std::mt19937_64 rnd(time(0));

void get_hash(int n) {
	base.assign(n, 0);
	for (i64& i : base) i = rnd();
}

void solve() {
	int n, m;
	std::cin >> n >> m;
	std::string s;
	std::cin >> s;

    get_hash(n);

	std::vector<i64> pre(n + 1, 0);
	for (int i = 1; i <= n; ++i) {
		pre[i] = pre[i - 1] + (s[i - 1] == '1' ? base[i - 1] : 0);
	}

	std::vector<int> num(n + 1, 0);
	std::vector<i64> fill(n + 1, 0);

	for (int i = 1; i <= n; ++i) {
		num[i] = num[i - 1] + (s[i - 1] == '1' ? 1 : 0);
		fill[i] = fill[i - 1] + base[i - 1];
	}

	std::vector<std::pair<int, int>> q(m);
	for (int i = 0; i < m; ++i) {
		std::cin >> q[i].first >> q[i].second;
        --q[i].first;
	}

    i64 hash = pre[n];

	std::set<i64> set;
	for (auto i : q) {
        i64 old = hash - pre[i.second] + pre[i.first];
        i64 ocr = num[i.second] - num[i.first];
        i64 cur = fill[i.second] - fill[i.second - ocr];
        set.insert(old + cur);
	}

	std::cout << set.size() << '\n';
}

int main() {
	int tt;
	std::cin >> tt;
	while (tt--) {
		solve();
	}
	return 0;
}

```


---

## 作者：saixingzhe (赞：4)

# 分析
看到很多人都写了哈希，来一发简单贪心模拟。

我们可以发现，右边连续的 $1$ 和左边连续的 $0$ 对答案不产生影响，考虑把右端点缩到左边第一个 $0$，把左端点缩到右边第一个 $1$，然后再用 `map` 存本质不同的左右端点。

具体先预处理出每个点右边第一个 $1$ 和左边第一个 $0$，如果字符串排序后不发生改变，需要特判存储。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,l,nxt0[200001],nxt1[200001],a[200001],sl,sr;
char s;
struct Node{
	int L,R;
	friend bool operator < (Node x,Node y){
        if(x.L!=y.L)	return x.L<y.L;
        else	return x.R<y.R;
   }
};
int main(){
	cin>>T;
	while(T--){
		int ans=0;
		map<Node,int>m;
		scanf("%d%d",&l,&n);
		for(int i=1;i<=l;i++)	cin>>s,a[i]=(s-'0'),nxt0[i]=0,nxt1[i]=0;
		for(int i=1;i<=l;i++){
			if(!a[i])	nxt0[i]=i;
			else	nxt0[i]=nxt0[i-1];
		}
		for(int i=l;i>=1;i--){
			if(a[i])	nxt1[i]=i;
			else	nxt1[i]=nxt1[i+1];
		}
		for(int i=1;i<=n;i++){
			scanf("%d%d",&sl,&sr);
			sl=nxt1[sl];
			sr=nxt0[sr];
			if(sl>sr||sl==0||sr==0)	sl=0,sr=0;
			if(m[{sl,sr}]==0)	ans++;
			m[{sl,sr}]=1;
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：Wf_yjqd (赞：4)

不算难，简单梳理一下。

------------

考虑排序一个区间，就相当于将区间内所有 $0$ 放在前，$1$ 放在后。

那如果两个区间的左端点间全为 $0$，右端点间全为 $1$，两个区间排序后的结果就相同。

一开始我想到将所有区间排序，然后前缀和维护区间和判断相邻两个是否相同。

但这样显然是错的，无法确定哪种排序方式刚好能让所有相同的区间相邻。

那到底如何去重呢？显然可以哈希然后用桶数组。

于是考虑两个相同结果的区间有啥共通性。

很快想到，各自左端点后第一个 $1$，右端点前第一个 $0$ 分别相同。

我们只需要线性 dp 维护每个位置前第一个 $1$ 和每个位置后第一个 $0$ 即可。

剩下的用 map 维护一下好了。

复杂度 $\operatorname{O}(n\log n)$。

------------

注意特判排序后无变化的情况。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> p;
const int maxn=2e5+84;
int T,n,m,a[maxn],lst0[maxn],nxt1[maxn],l,r,ans,b;
map<pair<int,int>,bool> vis;
int main(){
    scanf("%d",&T);
    while(T--){
        vis.clear();
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++){
            scanf("%1d",&a[i]);
            lst0[i]=(!a[i])?i:lst0[i-1];
        }
        nxt1[n+1]=0x3f3f3f3f;
        for(int i=n;i>=1;i--)
            nxt1[i]=a[i]?i:nxt1[i+1];
        ans=b=0;
        for(int i=1;i<=m;i++){
            scanf("%d%d",&l,&r);
            if(nxt1[l]>lst0[r]){
                b=1;
                continue;
            }
            if(vis[{nxt1[l],lst0[r]}])
                continue;
            ans++;
            vis[{nxt1[l],lst0[r]}]=1;
        }
        printf("%d\n",ans+b);
    }
    return 0;
}
```


---

## 作者：L0vely_NaiL0ng (赞：2)

字符串哈希，我们直接计算操作后的字符串的哈希值。

具体的我们将操作段前面的前缀的哈希值拿出来，操作段后面的后缀的哈希值拿出来，操作段的哈希值即将所有 $1$ 放在操作段的结尾的哈希值，这个东西很容易预处理出来，然后把 $3$ 段哈希值合并一下就做完了。

```

#define ull unsigned long long
#define int long long

int n, m, s[N];
ull p[N], a[N], g[N];
string st;
map<ull, int> cnt;
ull F(int x, int y) {
	if (x > y) return 0;
	return a[y] - a[x - 1] * p[y - x +1];
}
void solve() {
	cnt.clear(); int ans = 0;
	cin >> n >> m;
	cin >> st; st = " " + st;
	For (i, 1, n) {
		s[i] = s[i - 1];
		if (st[i] == '1') s[i]++;
		a[i] = a[i - 1] * base + (st[i] - '0');
	}
	For (i, 1, m) { 
		int l, r; cin >> l >> r;
		ull v1 = F(1, l - 1), v2 = F(r + 1, n);
		int v3 = s[r] - s[l - 1];
		ull res = v1 * p[n - l + 1] + g[v3] * p[n - r] + v2;
		if (!cnt[res]) ans++;
		cnt[res]++;
	}
	cout << ans << endl;
	return;
}
signed main() {
	p[0] = 1;
	For (i, 1, 200000) {
		p[i] = p[i - 1] * base;
		g[i] = g[i - 1] * base + 1;
	}
	int T;
	scanf("%lld", &T);
	while (T--) solve();
	return 0;
}
```

---

## 作者：船酱魔王 (赞：2)

# CF1849C Binary String Copying 题解

## 题意回顾

对于 $ \texttt{01} $ 串 $ S $，每次生成一个 $ S $ 的副本，将 $ [l_i,r_i] $ 区间内所有字符从小到大排序。求出所有副本中不同的字符串的个数。

**多测**，$ \sum n \le 2 \times 10^5 $，$ \sum m \le 2 \times 10^5 $。

## 分析

不同字符串个数问题，考虑进制哈希。

排序的操作显然就是把排序区间内所有的 $ \texttt{1} $ 放到最后，我们维护前缀 $ \texttt{1} $ 的个数即可知道每次排序后 $ \texttt{1} $ 在排序区间内的位置，预处理进制数幂次前缀和即可求出排序区间哈希值，与排序区间左右的哈希值合并即可得到总哈希值，放进 ```set``` 里去重即可求出不同的个数。

这里我的防卡哈希的方法是范围内取随机质数作为进制数。

## AC 代码

```
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <set>
#include <cstdlib>
#include <ctime> 
#define ull unsigned long long
using namespace std;
const int N = 2e5 + 5;
int base = 0;
int T;
int n, m;
string s;
ull hs[N];
ull pw[N];
int pre[N];
ull pp[N];
set<ull> se;
ull blk(int l, int r) {
	return pp[r] - pp[l - 1];
}
bool prime(int x) {
	for(int i = 2; i * i <= x; i++) {
		if(x % i == 0) {
			return false;
		}
	}
	return true;
}
int makebase() {
	int r = rand() % 11451;
	int x = 990000000;
	while(true) {
		x++;
		if(prime(x)) {
			r--;
			if(r == 0) {
				return x;
			}
		}
	}
}
int main() {
	srand(time(NULL));
	scanf("%d", &T);
	pw[0] = 1;
	base = makebase();
	for(int i = 1; i <= 2e5; i++) {
		pw[i] = pw[i - 1] * base;
	}
	for(int ti = 1; ti <= T; ti++) {
		scanf("%d%d", &n, &m);
		cin >> s;
		se.clear();
		hs[0] = 0;
		for(int i = 1; i <= n; i++) {
			hs[i] = hs[i - 1] * base + (s[i - 1] == '1');
			pre[i] = pre[i - 1] + (s[i - 1] == '1'); 
		}
		pp[0] = 0;
		for(int i = 1; i <= n; i++) {
			pp[i] = pp[i - 1] + pw[n - i];
		}
		int l, r;
		int c = 0;
		for(int i = 1; i <= m; i++) {
			scanf("%d%d", &l, &r);
			int d = pre[r] - pre[l - 1];
			ull val = hs[n] - hs[r] * pw[n - r] + hs[l - 1] * pw[n - l + 1] + blk(r - d + 1, r);
			if(se.find(val) == se.end()) {
				c++;
				se.insert(val);
			}
		}
		printf("%d\n", c);
	} 
	return 0;
}
```

---

## 作者：_Wind_Leaves_ShaDow_ (赞：1)

### 题意

给定 01 序列和 $m$ 次操作，每一次操作给定 $l$ 和 $r$，代表将序列的 $l$ 到 $r$ 段升序排列，**每一次操作分别独立，互不影响**。问最后会得到多少个不同的序列。

### 思路

题目就是说有多少操作 **本质上** 是相同的。考虑在什么情况下，两个操作是相同的。

我们发现在对一段序列进行升序排列时，就是把 $0$ 放在序列左侧，$1$ 放在序列右侧。那么此时原本的前导 $0$ 段和后缀 $1$ 段是没有变化的。

那么我们把前导 $0$ 和后缀 $1$ 删去后，就得到 **实际** 需要更改的段。此时我们看这个段有没有被记录过，就是之前有没有 **恰好访问同样段** 的询问。如果被记录过，那么两操作修改后答案是一样的，不同的序列数会减一。

如何删去前导 $0$？对于原本的序列左端点，找到 **它右边的第一个 1**，并将左端点移到那里。特殊的，如果左端点本身就是 $1$，那么它右边的第一个 $1$ 定义为自身。删后缀 $1$ 同理。

那么接下来考虑的就是，**当两个实际修改端点不一样时，会不会有最终结果相等的情况？**

答案是不会的。我们假设有两个需要修改的序列 $a$ 和 $b$ 且为方便定义 $a$ 长度大于 $b$ 长度。对于两次实际修改的操作，它们的左边一定是 $1$，右边一定是 $0$，而在修改后，左边一定是 $0$，右边一定是 $1$。那么对于 $a$，它的最左或最右端点一定不会被 $b$ 序列修改到，也就是 $b$ 的对应点不会被相应的排序，这样就一定会造成两个不同的序列。

于是就切掉了。~~考场上写挂了，屑。~~

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))

using namespace std;
const int N=2e5+10;

int T,n,m,a[N],nx[N][2];//左边第一个 0 和右边第一个 1
int stk[N],top;//用来找前导 0 和后缀 1 的。太蒻了用类似单调栈的做法搞的，但是复杂度还是 O(N) 的。
char tmp;
map<pair<int,int>,bool>mp;//记录左右端点

inline void solve(){
	int ans=0;
	mp.clear();//不要忘记多测清空
	cin>>n>>m;
	top=0;
	for(int i=1;i<=n;i++){
		cin>>tmp;
		a[i]=(int)tmp-'0';
		if(a[i]){
			while(top)nx[stk[top--]][1]=i;//右边第一个 1
			nx[i][1]=i;//自己的右边第一个 1 也是自己
		}
		else stk[++top]=i;
	}
	while(top)nx[stk[top--]][1]=0;//右边没有 1，记录成 0
	top=0;
	for(int i=n;i;i--){
		if(a[i])stk[++top]=i;
		else{
			while(top)nx[stk[top--]][0]=i;
			nx[i][0]=i;
		}
	}
	while(top)nx[stk[top--]][0]=0;//同上
	for(int i=1;i<=m;i++){
		int l,r;
		cin>>l>>r;
		l=nx[l][1];
		r=nx[r][0];//删去不需要修改的部分
		if(!l||!r||l>r)l=r=0;//如果没有前导 0/后缀 1 或者序列原本就有序就不需要操作了
		if(!mp[{l,r}])mp[{l,r}]=1;
		else ans++;
	} 
	cout<<m-ans<<'\n';
}

signed main(){
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--)solve();
    return 0;
}
```

---

## 作者：happybob (赞：0)

考虑到由于字符集只为 $0$ 或 $1$，可以字符串哈希。容易发现 $0$ 不会对哈希结果造成影响。对于一段排序，肯定是前面一段 $0$，后面是一段 $1$。前面的 $0$ 对哈希值的贡献都为 $0$，只需要管后面的 $1$ 的数量。

所以我们可以预处理 $f_i$ 表示有 $i$ 个 $1$ 的哈希值。使用前缀和维护区间 $1$ 个数即可。

用哈希判重。

由于是 CF 的题，考虑双哈希。

```cpp
#pragma GCC optimize("-Ofast,-inline")
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <set>
#include <map>
#include <unordered_map>
#include <queue>
#include <stack>
#include <vector>
#include <utility>
#include <cstdlib>
#include <string>
using namespace std;

#define ll long long

const int N = 2e5 + 5, INF = 2e9, MOD = 1e9 + 7;

inline int read()
{
	int op = 1, x = 0;
	char ch = getchar();
	while ((ch < '0' || ch > '9') && ch != '-') ch = getchar();
	while (ch == '-')
	{
		op = -op;
		ch = getchar();
	}
	while (ch >= '0' and ch <= '9')
	{
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * op;
}

inline void write(int x)
{
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
}

int n, m, t;
string s;

using ull = unsigned long long;
const long long MOD2 = 1e9 + 7;

ull hashing1[N];
long long hashing2[N];
int cnt[N];

ull hash1(ull x, ull p)
{
	return x * 27 + p;
}

ll hash2(ll x, ll p)
{
	return (x * 27LL % MOD2 + p) % MOD2;
}

ull hashing11[N];
ll hashing22[N];
ull powe1[N];
ll powe2[N];

ull gethash(string t)
{
	ull res = 0;
	for (char i : t)
	{
		res = res * 27 + (i - '0');
	}
	return res;
}

int main()
{
	ios::sync_with_stdio(0), cin.tie(nullptr), cout.tie(nullptr);
	// freopen("*.in", "r", stdin);
	// freopen("*.out", "w", stdout);
	powe1[0] = powe2[0] = 1;
	for (int i = 1; i < N; i++)
	{
		hashing11[i] = hash1(hashing11[i - 1], 1);
		hashing22[i] = hash2(hashing22[i - 1], 1);
		powe1[i] = powe1[i - 1] * 27;
		powe2[i] = powe2[i - 1] * 27LL % MOD2;
	}
	cin >> t;
	while (t--)
	{
		cin >> n >> m;
		cin >> s;
		string p = " ";
		s = p + s;
		for (int i = 1; i <= n; i++)
		{
			hashing1[i] = hash1(hashing1[i - 1], s[i] - '0');
			hashing2[i] = hash2(hashing2[i - 1], s[i] - '0');
			cnt[i] = cnt[i - 1] + (s[i] == '1');
		}
		set<pair<ull, ll> > st;
		while (m--)
		{
			int l, r;
			cin >> l >> r;
			ull nh1 = hashing1[l - 1] * powe1[n - l + 1] + hashing11[(cnt[r] - cnt[l - 1])] * powe1[n - r] + (r == n ? 0 : hashing1[n] - hashing1[r] * powe1[n - r]);
			ll nh2 = (hashing2[l - 1] * powe2[n - l + 1] % MOD2 + hashing22[(cnt[r] - cnt[l - 1])] * powe2[n - r] % MOD2 + (r == n ? 0 : hashing2[n] - (hashing2[r] * powe2[n - r] % MOD2) + MOD2) % MOD2) % MOD2;
			//cout << nh1 << " " << nh2 << "\n";
			st.insert(make_pair(nh1, nh2));
		}
		cout << st.size() << "\n";
	}
	return 0;
}
```


---

## 作者：_Only_this (赞：0)

### CF1849C Binary String Copying 题解

------------

这场光速 A、B 题，然后 C 没动静了。。

------------

这里考虑哈希的思想，将询问的每个区间转化为受排序影响的区间边界。

对于每个询问，$l$ 和 $r$ 往里缩，从左往右找第一个 $1$，从右往左找第一个 $0$。如果位置交错，说明询问区间有序，特别处理一下即可。

否则看一下缩后的区间是否统计过，就结束了。

贴个代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll maxn = 2e5+5;
ll T,n,m;
ll a[maxn],pos0[maxn],pos1[maxn],L[maxn],R[maxn];
map<pair<ll,ll>,ll>mp;
inline void Init(){
	ll last0=0;
	for(ll i=1;i<=n;i++){
		if(!a[i]){
			pos0[i]=i,last0=i;
		}
		else{
			pos0[i]=last0;
		}
	}
	ll last1=n+1;
	for(ll i=n;i>=1;i--){
		if(a[i]){
			pos1[i]=i,last1=i;
		}
		else{
			pos1[i]=last1;
		}
	}
	return ;
}
int main(){
	scanf("%lld",&T);
	while(T--){
		scanf("%lld%lld",&n,&m);
		for(ll i=1;i<=n;i++)
			scanf("%1d",&a[i]);
		Init();
		
		for(ll i=1;i<=m;i++){
			scanf("%lld%lld",&L[i],&R[i]);
		}
		ll ans=0;
		bool flag=0;
		for(ll i=1;i<=m;i++){
			ll loc1=pos1[L[i]],loc2=pos0[R[i]];
			if(loc1>=loc2){
				if(!flag){
					ans++,flag=1;
				}
				continue;
			}
			mp[{loc1,loc2}]++;
		}
		for(auto it: mp){
			ans++;
		}
		printf("%lld\n",ans);
		mp.clear();
		for(ll i=0;i<=n;i++)
			pos0[i]=pos1[i]=0;
	}
	return 0;
}
```


---

