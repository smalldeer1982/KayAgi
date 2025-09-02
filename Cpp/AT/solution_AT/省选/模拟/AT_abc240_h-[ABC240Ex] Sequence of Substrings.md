# [ABC240Ex] Sequence of Substrings

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc240/tasks/abc240_h

$ 0 $ と $ 1 $ のみからなる長さ $ N $ の文字列 $ S\ =\ s_1\ s_2\ \ldots\ s_N $ が与えられます。

整数の $ 2 $ つ組を $ K $ 個並べた列 $ \big((L_1,\ R_1),\ (L_2,\ R_2),\ \ldots,\ (L_K,\ R_K)\big) $ であって以下の $ 3 $ つの条件をすべて満たすものが存在するような最大の整数 $ K $ を出力してください。

- $ i\ =\ 1,\ 2,\ \ldots,\ K $ について、$ 1\ \leq\ L_i\ \leq\ R_i\ \leq\ N $
- $ i\ =\ 1,\ 2,\ \ldots,\ K-1 $ について、$ R_i\ \lt\ L_{i+1} $
- $ i\ =\ 1,\ 2,\ \ldots,\ K-1 $ について、文字列 $ s_{L_i}s_{L_i+1}\ \ldots\ s_{R_i} $ は文字列 $ s_{L_{i+1}}s_{L_{i+1}+1}\ldots\ s_{R_{i+1}} $ より**辞書順で真に小さい**

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2.5\ \times\ 10^4 $
- $ N $ は整数
- $ S $ は $ 0 $ と $ 1 $ のみからなる長さ $ N $ の文字列

### Sample Explanation 1

$ K\ =\ 3 $ のとき、例えば $ (L_1,\ R_1)\ =\ (1,\ 1),\ (L_2,\ R_2)\ =\ (3,\ 5),\ (L_3,\ R_3)\ =\ (6,\ 7) $ が問題文中の条件を満たします。 実際、$ s_1\ =\ 0 $ は $ s_3s_4s_5\ =\ 010 $ より辞書順で真に小さく、$ s_3s_4s_5\ =\ 010 $ は $ s_6s_7\ =\ 10 $ より辞書順で真に小さいです。 $ K\ \geq\ 4 $ のときは、問題文中の条件を満たす $ \big((L_1,\ R_1),\ (L_2,\ R_2),\ \ldots,\ (L_K,\ R_K)\big) $ は存在しません。

## 样例 #1

### 输入

```
7
0101010```

### 输出

```
3```

## 样例 #2

### 输入

```
30
000011001110101001011110001001```

### 输出

```
9```

# 题解

## 作者：Lynkcat (赞：14)

更优复杂度做法。

首先给出一个复杂度为 $O(n^2)$ 的相对简单的解法：

设 $dp_i$ 为以 $s_{[1,i]}$ 的答案，整个问题可以被割裂成两部分：第一部分，给 $\frac{n(n+1)}{2}$ 个子串按字典序排序；第二部分 dp 转移。

首先第一部分，暴力建后缀树跑前序遍历；第二部分，一个暴力的做法是每次转移一个区间 $[l,r]$ 的时候把 $dp_{l-1}+1$ 的值转移到 $dp_{r,r+1,...,n}$ 上，使用 BIT 做到 $O(n^2\log n)$。当然复杂度更优秀的做法是观察到 $dp_i$ 上界为 $n$ 并且始终单调不降，因此每次更新的一定是 $dp_{r,r+1,...r+x}$ 这一段前缀。因为每个点最多被更新 $n$ 次，所以复杂度也可以做到 $O(n^2)$。综上所述可以得到一个时空复杂度均为 $O(n^2)$ 的做法。

当然后缀树前序遍历不需要完全建出后缀树来做，可以边遍历边维护当前点下所属的左端点集合，每次分裂成下一位为 $0,1,\text{empty}$ 三个部分，接着先递归 $0$ 的部分，然后递归 $1$ 的部分。具体实现直接 $\text{work}(l,r,dep)$ 表示当前过程的集合为整体序列下标的 $[l,r]$ 区间，深度为 $dep$ 即可。

这样空间被优化成 $O(n)$ 之后，可以直接通过原题数据。

---

接下来基于一个关键性质来优化复杂度。

注意到两个相邻的被选择的区间 $[x,y],[l,r]$ 满足 $y<l$，一定有 $r-l+1\leq y-x+2$。证明是简单的，如果 $\text{lcp}_{x,l}\geq y-x+1$ 那么将 $y$ 调整成 $y=x+1$ 一定不会使答案序列非法，否则一定满足 $r-l+1\leq y-x+1$。

那么相当于每个区间长度要么 $+1$ 要么变小，而区间长度的和最多为 $n$，因此单个区间最长长度是在 $O(\sqrt{2n})$ 级别的，设具体的阈值为 $B$。

因此上面这个做法直接把 $dep>B$ 的扔了，复杂度可以做到 $O(n\sqrt{n}\log n)$。

考虑继续基于后缀树结构分析一些结论，试图把树状数组这个东西去掉。

首先考虑将原来的 $dp_i$ 替换成新的状态 $dp_{l,r}$ 表示最后一个选的区间是 $[l,r]$。

接下来转移有两种条件，第一种是 $[x,y]$ 在后缀树上的前序遍历要比 $[l,r]$ 靠前，第二种是 $y<l$。

![](https://cdn.luogu.com.cn/upload/image_hosting/edwouhoc.png)

对于上图，对于节点 $6$ 上的区间 $[l,r]$，能转移到它的 $[x,y]$ 在其他任意一个节点上。

考虑转移拥有的一些性质，首先，因为节点 $6$ 上有区间 $[l,r]$，而 $[l,r-1]$ 在 $4$ 上，那么考虑 $0,1,2,3$ 这四个点，因为合法转移只与 $y$ 与 $l$ 有关，所以合法的转移都能转移到 $[l,r-1]$，直接继承 $[l,r-1]$ 的答案就能解决，现在也就是说只需要解决从父亲节点上的区间转移到它以及父亲的左儿子的区间转移到它即可。

对于第一种情况，考虑如何限制 $y<l$ ，发现因为我们上面维护左端点集合的时候实际上可以始终保持有序，所以可以双指针解决。

对于第二种情况，因为 $y$ 取 $x$ 节点能取的最大值一定不会劣，因此分成两种，第一种是 $y$ 取满到 $x+B-1$ 都满足 $y<l$，这种情况类似上面双指针转移即可；第二种是 $y$ 只能取到 $l-1$，设 $g_i$ 为当前遍历过程中已经被遍历过的满足区间右端点为 $i-1$ 的区间的答案的最大值，我们只需要用每个区间 $[i,j]$ 更新 $g_{j+1}$ 的取值，然后查询的时候查个 $g_l$ 的值就可以解决这种转移。

综上所述所有转移都可以在 $O(n\sqrt{n})$ 的时间复杂度以及 $O(n)$ 的空间复杂度内解决。

实测非常快，最大点运行时间不超过 39ms。

---

## 作者：Leasier (赞：13)

首先有一个暴力：

- 把所有子串 $[l, r]$ 抓出来按字典序排序。
- 考虑 dp，设 $dp_i$ 表示按字典序排序后以第 $i$ 个**不去重**子串结尾的最大长度。
- 对每个 $i$ 预处理前面第一个不同的 $lst_i$，则 $dp_i = \max(\displaystyle\max_{j = 1}^{lst_i} dp_j, 0) + 1$。
- 树状数组优化即可。时间复杂度为 $O(n^2 \log n)$。

人类智慧地，注意到如下性质：

- 一定存在一种最优方案，使得不存在一个被选中的子串满足 $r_i - l_i + 1 > \sqrt{2n}$。

证明：把最优方案中的子串按长度排序，若此时存在相邻两项长度差 $> 1$，则可以把较长者的长度删到较短者的长度 $+ 1$。若要让最长者的长度最大，设其长度为 $M$，则理论上需要满足 $\frac{M(M + 1)}{2} \leq n$，于是可以得到一个宽松的上界 $M \leq \sqrt{2n}$，进而得证。

于是我们把满足条件的子串抓出来跑前述算法即可。时间复杂度为 $O(n \sqrt{n} \log n)$.

代码：
```cpp
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

typedef struct {
	int nxt[7];
	vector<pair<int, int> > v;
} Node;

int id1 = 1, id2 = 0;
int ref[25007][327], l[5550257], bit[5550257], dp[5550257];
char s[25007];
Node trie[5550257];
vector<int> v1[25007], v2[25007];

inline void insert(int l, int r){
	int x = 1;
	for (register int i = l; i <= r; i++){
		int ch = s[i] - '0';
		if (trie[x].nxt[ch] == 0) trie[x].nxt[ch] = ++id1;
		x = trie[x].nxt[ch];
		trie[x].v.push_back(make_pair(l, i));
	}
}

void dfs(int x){
	int size = trie[x].v.size(), pre = id2;
	for (register int i = 0; i < size; i++){
		id2++;
		l[id2] = pre;
		v1[trie[x].v[i].first].push_back(id2);
		v2[trie[x].v[i].second].push_back(id2);
	}
	if (trie[x].nxt[0] != 0) dfs(trie[x].nxt[0]);
	if (trie[x].nxt[1] != 0) dfs(trie[x].nxt[1]);
}

inline int lowbit(int x){
	return x & (-x);
}

inline void update(int x, int k){
	while (x <= id2){
		bit[x] = max(bit[x], k);
		x += lowbit(x);
	}
}

inline int get_max(int x){
	int ans = 0;
	while (x > 0){
		ans = max(ans, bit[x]);
		x -= lowbit(x);
	}
	return ans;
}

int main(){
	int n, m, ans = 0;
	cin >> n;
	cin >> &s[1];
	m = sqrt(n * 2);
	for (register int i = 1; i <= n; i++){
		insert(i, min(i + m - 1, n));
	}
	dfs(1);
	for (register int i = 1; i <= n; i++){
		int size1 = v1[i].size(), size2 = v2[i].size();
		for (register int j = 0; j < size1; j++){
			int x = v1[i][j];
			dp[x] = get_max(l[x]) + 1;
			ans = max(ans, dp[x]);
		}
		for (register int j = 0; j < size2; j++){
			int x = v2[i][j];
			update(x, dp[x]);
		}
	}
	cout << ans;
	return 0;
}
```

---

## 作者：yuanruiqi (赞：13)

## 思路

很独特的方法，与其它题解不同。

### 朴素想法

刚看题应该会有一个 DP 的想法，$f_{i}$ 表示以 $i$ 结尾的前缀最多选出的子串数量。接下来发现转移时处理不了字典序严格递增的关系。尝试在 DP 状态中增加维度，记录结尾的子串。即 $f_{i,l,r}$，这样转移的确可以进行，但是复杂度妥妥爆炸，而且看起来就很累赘，似乎不需要记录每一种 $l, r$ 的取值。

### 01串的意义

注意到给定了一个 01 串，而上文仍未使用这个信息。不妨考虑答案最大的取值，由于要求字典序递增，那么每一个子串就必定本质不同，可以简单统计一下。首先得到满足 $\sum_{i=1}^{k}{i \times 2 ^ i} \geq n$ 的 $k$ 的最小取值，然后 $\sum_{i=1}^{k}{2^i}$ 也就是答案的上界了。对于本题 $n \leq 2.5 \times 10^4$，答案不会超过 $3 \times 10 ^ 3$。

### DP方法

接下来的想法就很自然了，交换 DP 状态和答案，即 $f_{x,i}$ 表示长度为 $i$ 的前缀中选出 $x$ 个子串（注意不一定要取到 $s_i$），结尾的子串字典序最小的一种。转移也是简单的，一种是直接从 $i-1$ 转移过来，一种是考虑 $i+1$ 开头的后缀，至少需要新开一个多长的子串，才能满足字典序严格比 $f_{x,i}$ 记录的子串大，记这个长度为 $y$，则更新 $f_{x+1,i+y}$。若无法满足，则不进行转移。

### 实现细节

考虑实现，预处理部分建出后缀数组及 height 数组，并对 height 数组建立 st 表。即可 $O(1)$ 求出两个子串的大小关系。这样 DP 的转移也是 $O(1)$，总复杂度即为 $O(n \log n + n \cdot ans)$。

### 复杂度

复杂度看起来相当玄学，还得看看上面的式子。

$$n \leq\sum_{i=1}^{k}{i \times 2 ^ i} = 8k2^{k-1}+1$$

$$ans = \sum_{i=1}^{k}{2^i} = 2 ^ {k+1} - 1$$

忽略常数。

$$ \frac{n}{ans} \approx \frac{8k2^{k-1}}{2^{k+1}} = 2k $$

$k$ 是 $O(\log{n})$ 级别的，那么 $ans$ 是 $O(\frac{n}{\log{n}})$ 级别的，总复杂度即为 $O(n \log n + \frac{n^2}{\log{n}})$。

这样计算的话，对于本题的数据范围，复杂度优于 $O(n\sqrt{n}\log n)$，实测跑起来也是飞快。

## 代码

[模拟赛时代码](https://atcoder.jp/contests/abc240/submissions/45063979)

---

## 作者：Purslane (赞：7)

# Solution

一个朴素的想法是把整个串全部本质不同的子串拉出来跑数据结构优化 $\rm DP$。

过不了，因为本质不同的子串个数是 $O(n^2)$ 的。

但是注意到如果后一个串比前一个串长，而且长了至少两位，我们就可以把它末尾砍掉使最多长一位，字典序关系不变。

因此可能的子串的长度为 $O(\sqrt n)$ 量级的。把它们全部插到字典树并且 $\rm DFS$ 遍历即可。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=25000+10,MAXM=1e7+10;
int n,cnt,sum,tot,dp[MAXN],dep[MAXM],trie[MAXM][2];
vector<int> pos[MAXM];
string S;
void update(int pos,int v) {while(pos<=n) dp[pos]=max(dp[pos],v),pos+=pos&-pos;return ;}
int query(int pos) {int ans=0;while(pos) ans=max(ans,dp[pos]),pos-=pos&-pos;return ans;}
void insert(int l,int r) {
	int u=0;
	ffor(i,l,r) {
		if(trie[u][S[i]-'0']==0) trie[u][S[i]-'0']=++tot,dep[tot]=i-l+1;
		u=trie[u][S[i]-'0'],pos[u].push_back(i);
	}
	return ;
}
void dfs(int u) {
	sort(pos[u].begin(),pos[u].end(),[](int A,int B) {return A>B;});
	for(auto v:pos[u]) update(v,query(v-dep[u])+1);
	if(trie[u][0]) dfs(trie[u][0]);
	if(trie[u][1]) dfs(trie[u][1]);
	return ;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>S,S="&"+S;
	ffor(i,1,n) {cnt++,sum+=i;if(sum>=n) break ;}
	ffor(i,1,n) insert(i,min(i+cnt-1,n));
	dfs(0),cout<<query(n);
	return 0;
}
//繁华如三千东流水 我只取一瓢爱了解 只恋你化身的蝶
```

---

## 作者：Miraik (赞：7)

数据范围看上去就是根号老哥或者三只老哥的东西。

首先，我们选出来的子串，相邻的长度差一定不会大于 $1$。

于是我们容易发现直接过滤掉长度大于 $\sqrt{2n}$ 的子串对答案没有影响。

那么像 Trie 那样直接 dfs 一遍，把所有长度在 $\sqrt{2n}$ 之内的子串按字典序排好序，然后就是一个类似于最长上升子序列的问题，直接树状数组优化 dp 就好。时间复杂度 $O(n \sqrt{n} \log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=25005;
const int sq=231;
int n,m,a[N]; vector<int>o[2]; char str[N];
struct BIT{
    int c[N];
    #define lowbit(x) (x&(-x))
    inline void update(int x,int y){ while(x<=n) c[x]=max(c[x],y),x+=lowbit(x); }
    inline int query(int x){ int res=0; while(x) res=max(res,c[x]),x-=lowbit(x); return res; }
}T;
struct Str{ int l,r; }b[N*sq];
inline void solve(vector<int>e,int len){
    if(e.empty() || len*len>n*2) return;
    vector<int>v[2];
    for(int i=0;i<e.size();i++){
        b[++m]={e[i],e[i]+len-1};
        if(e[i]+len-1<n) v[a[e[i]+len]].emplace_back(e[i]);
    }
    for(int i=0;i<2;i++) solve(v[i],len+1);
}
int main(){
    scanf("%d%s",&n,str+1);
    for(int i=1;i<=n;i++) a[i]=str[i]^'0';
    for(int i=n;i;i--) o[a[i]].emplace_back(i);
    solve(o[0],1); solve(o[1],1);
    for(int i=1;i<=m;i++){
        int ri=T.query(b[i].l-1)+1;
        T.update(b[i].r,ri);
    }
    printf("%d\n",T.query(n));
    return 0;
}
```


---

## 作者：N2MENT (赞：2)

[blog](https://www.cnblogs.com/0x0620AF/articles/ABC240Ex.html)

[ABC240Ex](https://www.luogu.com.cn/problem/AT_abc240_h)

---

模拟赛题。

有意思的。

注意到奇怪的 $n\leq 2.5 \times 10^4$。

首先可以写出暴力 dp。设 $f_{i,j}$ 表示考虑长度为 $i$ 的前缀，最后一次选了 $s[i - j + 1, i]$ 的贡献。

转移：

$$f_{i, j} = \max_{1\leq x \leq i - j,s[x - y + 1, y] < s[i - j + 1, i]}\{f_{x, y}\} + 1$$

这是一个二维偏序的形式，但是状态数是 $O(n^2)$ 的，直接转移复杂度为 $O(n^2\log n)$。

稍微推一推，发现最优决策中一定有一种情况满足，一个子串的长度如果为 $len$，那么其后继长度最多为 $len + 1$，那么所有的答案串长度都无法超过 $2\sqrt n$，所以有用的状态数只有 $O(n\sqrt n)$。

于是就做完了，把所有有用状态全部压进一棵 trie 里面，一边遍历一边做二维偏序，复杂度 $O(n\sqrt n \log n)$。

代码非常好写。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2.5e4 + 10;
const int maxs = 2 * sqrt(2.5e4) + 10;
int lowbit(int x) {return x & (-x);}
int tr[maxn * maxs][2], cnt = 1;
vector<int> loc[maxn * maxs];
int mxl;
int ans;
int n;
class Fenwick {
public:
    int tr[maxn];
    void Update(int x, int val) {
        while(x <= n) {
            tr[x] = max(val, tr[x]);
            x += lowbit(x);
        }
    }
    int Query(int x) {
        int res = 0;
        while(x) {
            res = max(res, tr[x]);
            x -= lowbit(x);
        }
        return res;
    }
}fw;
string s;
void Insert(int x) {
    int p = 1;
    int lim = min(n, x + mxl);
    for(int i = x; i <= lim; i++) {
        int &nxt = tr[p][s[i - 1] - '0'];
        if(!nxt) nxt = ++cnt;
        p = nxt;
        loc[p].emplace_back(i);
    }
}
vector<pair<int, int>> tmp;
void Dfs(int u, int len) {
    tmp.clear();
    for(int i : loc[u]) {
        int f = fw.Query(i - len) + 1;
        ans = max(ans, f);
        tmp.emplace_back(i, f);
    }
    for(auto cur : tmp) {
        fw.Update(cur.first, cur.second);
    }
    for(int i = 0; i < 2; i++) if(tr[u][i]) Dfs(tr[u][i], len + 1);
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n >> s;
    mxl = 2 * sqrt(n);
    for(int i = 1; i <= n; i++) {
        Insert(i);
    }
    Dfs(1, 0);
    cout << ans;
}

```

---

## 作者：DengDuck (赞：2)

图灵杯出了原，发现题解区的实现或多或少跟我不太一样啊。

我们考虑一种朴素的 $\mathcal O(n^2\log n)$ 做法。

首先，我们设 $F_{l,r}$ 表示以 $[l,r]$ 结尾的 LIS。

然后维护这个东西，参考 [LIS 的 $\mathcal O(n \log n)$ 做法](https://www.luogu.com.cn/article/vexjto1d)。

我们可以用一个 `set`，第 $i$ 项表示使得 LIS 长度为 $i$ 的字典序最小的结尾区间。

显然从字典序上看，`set` 是单调的。

所以我们可以用 `set` 来求 $F_{l,r}$，然后再拿去更新。

注意啊！这里的选择要满足区间无交的关系，所以枚举上有点要注意的东西，看看我的代码。

然后场上我卡在这里没啥思路了。

注意到神秘地，这个做法在一些 $2.5\times 10^4$ 的数据下跑得飞快，怎么回事呢？也有人在说有原题，在传根号结论。

（我看见榜上一车子 $60\to 100$ 的老哥，就猜正解和暴力大概差得不多）

然后，根号结论就容易发现啦！

简单来说，如果一个区间的长度超过了 $\sqrt {2n}$，那我们就可以无视它。

因为我们在 LIS 中的相邻两个区间，后一个区间比前一个区间长度长 $1$ 的时候，你就可以确定二者的字典序大小关系，后一个无论再怎么延长，都无法改变结果了。

而我们又希望结尾的字典序尽可能小，所以我们肯定希望后一个的长度不要过度延伸。

所以后一个区间，要么前面的部分已经比前一个大，这是长度会比前一个区间短，要么长度比前一个区间长 $1$。

我们设满足以上条件的 LIS 中最长的区间长度为 $B$，由于长度要一个一个加，所以最起码得是 $1+2+3+4+\cdots+B=\dfrac 1 2 B(B+1)$。

所以变形得到 $B^2+B\leq 2n$，舍去 $B$，可以得到 $B\leq \sqrt {2n}$。

所以我们只考虑所有小于 $\sqrt {2n}$ 区间，套用上面的结论就可以啦！

P.S.：这里的字符串大小比对，包括 `set` 内部的排序，我都是用二分加上哈希求 LCP，再比对下一位来解决的，这一点可以参考[我的远古题解](https://www.luogu.com.cn/article/jt76bkq1)。

时间复杂度为 $\mathcal O(n\sqrt n\log^2 n)$，似乎全场最差，但是两个平台都过了，而且没咋卡常。

```cpp
#include<bits/stdc++.h>
#define LL int
#define pLL pair<LL,LL>
#define Fi first
#define Se second
#define pb push_back
#define LowBound lower_bound
#define UpBound upper_bound
using namespace std;
const LL N=3e4+5;
const LL P=1331;
const long long Mod=998244353;
LL n;
long long H[N],Pw[N];
unordered_map<LL,LL>F[N];
char S[N];
inline LL Gt(LL l,LL r)
{
	return (H[r]-H[l-1]*Pw[r-l+1]%Mod+Mod)%Mod;
}
inline LL Sam(LL l,LL r,LL L,LL R)
{
	return Gt(l,r)==Gt(L,R);
}
inline bool Pd(LL L,LL R,LL L2,LL R2)
{
	LL l=1,r=min(R-L+1,R2-L2+1),Ans=0;
	while(l<=r)
	{
		LL mid=l+r>>1;
		if(Sam(L,L+mid-1,L2,L2+mid-1))l=mid+1,Ans=mid;
		else r=mid-1;
	}
	//cout<<L<<" "<<R<<" "<<L2<<" "<<R2<<' '<<Ans<<endl;
	//	cout<<Ans<<endl;
	if(Ans==min(R-L+1,R2-L2+1))return R-L+1<R2-L2+1;
	return S[L+Ans]<S[L2+Ans];
}
struct Nde
{
	LL L,R,W;
	bool operator<(const Nde&A)const{return Pd(L,R,A.L,A.R);}
};
set<Nde>Q;
pLL Fd[N];
int main()
{
	scanf("%d%s",&n,S+1);
	LL B=sqrt(2*n)+1;
	Pw[0]=1;
	for(int i=1;i<=n;i++)Pw[i]=Pw[i-1]*P%Mod;
	for(int i=1;i<=n;i++)H[i]=(H[i-1]*P%Mod+S[i]-'0')%Mod;		
	for(int L=1;L<=n;L++)
	{
		for(int R=L;R<=n&&R<=L+B;R++)
		{
			auto it=Q.LowBound({L,R,0});
			if(it!=Q.begin())F[L][R]=(--it)->W+1;
			else F[L][R]=1;
		}
		for(int j=L;j>=1;j--)
		{
			if(L-j+1>B)break;
			if(Fd[F[j][L]].Fi==0)
			{
				Q.insert({j,L,F[j][L]});
				Fd[F[j][L]]={j,L};
				continue;
			}
			LL X=Fd[F[j][L]].Fi,Y=Fd[F[j][L]].Se;
			if(Pd(j,L,X,Y))Q.erase({X,Y,F[j][L]}),Q.insert({j,L,F[j][L]}),Fd[F[j][L]]={j,L};
		}
	}
	printf("%d",Q.size());
	return 0;
}
//RP++
```

---

## 作者：hyman00 (赞：1)

## [ABC240H] Sequence of Substrings 题解

#### 题意

给定一个长度为 $n$ 的 `01` 序列，要在其中选择若干个字串，满足从左到右排列，且字典序严格递增。

$n\le 2.5\times 10^4$ 

#### 做法

发现后一个字串长度一定不会大于前一个的长度+1，否则可以缩短它的长度，这样有可能被选的只有 $O(n^{1.5})$ 级别的，具体为长度小于 $(2n)^{0.5}$ 的有用。

把这些串暴力跑出来，按字典序排列，相同的串按照出现位置从右往左排列。

然后考虑直接 dp，设 `dp[i]` 表示考虑了长度为 $i$ 的前缀，最多选多少个，注意是把之前处理出来的所有串依次更新 `dp` 数组。

更新的式子形如 $dp_{r+1}=\max\{dp_{r+1},\max_{i=0}^{l}\{dp_i\}+1\}$ 这样的，要快速求前缀 `max` ，可以想到树状数组。

#### 卡常

首先加 `inline`，加 `register`，加火车头就不说了。

前半部分如果把所有串扔 `vector` 里然后 `sort` 会非常慢，因为要比较字符串。

字符串是第一关键字，所以可以把所有串扔 `trie` 上然后 `dfs` 一边就得到排序，这样找串的时候直接枚举左端点，在 `trie` 上跳即可。

这样发现只有在多个字串完全相同的时候要 `sort` 下标，虽然复杂度没变，但是优化效果明显。

后半部分也可以优化，直接树状数组是 $O(n^{1.5}\log n)$ 的，随机生成几组 $25000$ 的数据发现答案期望只有 $500$ 左右，特殊构造的数据也不会超过 $4000$ ，应该是 $O(\frac{n}{\log n})$ 级别的。

所以 `dp` 数组值域只有 $O(\frac{n}{\log n})$ ，可以考虑暴力，把方程改为对任意 $i\gt r$，$dp_i=\max\{dp_i,dp_l+1\}$ ，由于这个数组是单调不降的，且每次只会增加，直接暴力求可以做到 $O(\frac{n^2}{\log n})=O(n\times ans)$ 虽然比较大，但是实测略快。



---

## 作者：Butterfly_qwq (赞：0)

xyd 考了这道题然后这道题 7 篇题解变成了 13 篇题解。

考虑对子串排序，排序之后数组是 $s_i$，找出 $pre_i$ 为最大的满足 $s_j\not=s_i$ 且 $j<i$ 的 $j$。

则显而易见的我们有 $dp_i=\max\limits_{j=1}^{pre_i}dp_j+1$。

考虑 DP。直接 DP 是 $O(n^4)$ 的，随便树状数组一下就是 $O(n^2\log n)$ 的了。

易证只有长度小于 $\sqrt{2n}$ 的字串才能入选，那么时间复杂度为 $O(n\sqrt n\log n)$。

Code:
```
#include<bits/stdc++.h>
using namespace std;
const int N=25005,NS=5600005;
struct sec{int l,r;};
struct Node
{
	int ch[2];
	vector<sec> v;
}trie[NS];
int ans,cnt=1,idx,lmt,n,c[NS],dp[NS],pre[NS];
vector<int> l[N],r[N];
string s;
void add(sec sc)
{
	int u=1;
	for(int i=sc.l,num;i<=sc.r;i++)
	{
		num=s[i]-'0';
		if(!trie[u].ch[num])trie[u].ch[num]=++cnt;
		u=trie[u].ch[num];
		trie[u].v.push_back((sec){sc.l,i});
	}
}
void init(int u)
{
	if(!u)return;
   int res=idx;
   for(sec sc:trie[u].v)
   {
   	pre[++idx]=res;
   	l[sc.l].push_back(idx);
   	r[sc.r].push_back(idx);
	}
	for(int i:{0,1})init(trie[u].ch[i]);
}
void update(int u,int w)
{
	for(int i=u;i<=idx;i+=i&-i)c[i]=max(c[i],w);
}
int query(int u)
{
	int res=0;
	for(int i=u;i;i-=i&-i)res=max(res,c[i]);
	return res;
}
int main()
{
	cin>>n>>s;
	s="%"+s;
	lmt=sqrt(n*2);
	for(int i=1;i<=n;i++)add((sec){i,min(i+lmt-1,n)});
	init(1);
	for(int i=1;i<=n;i++)
	{
		for(int u:l[i])
		{
			dp[u]=query(pre[u])+1;
			ans=max(ans,dp[u]);
		}
		for(int u:r[i])update(u,dp[u]);
	}
	cout<<ans;
}
```

应该说是比较短的了。

---

## 作者：binbin_200811 (赞：0)

# [ABC240Ex Sequence of Substrings](https://www.luogu.com.cn/problem/AT_abc240_h)

LIS 的好题改编。

### 约定

$S(l,r)$ 为字符串 $s$ 中第 $l$ 位到底 $r$​ 位。

$S(l,r)<S(x,y)$ 为字符串中 $[l,r]$ 的子串字典序比 $[x,y]$ 的子串小。

### 前置

LIS 的 $n\log n$ 求法。

### 题解

我们考虑按照类似于朴素 LIS 的方式设状态，$f[l][r]$ 表示 $[l,r]$ 这个区间作为当前选的最后一个划分，所得到的 LIS 最大值。

显然有转移：
$$
f[l][r]=\max(f[x][y])+1
$$
要求 $S(x,y)<S(l,r)$。

我们可以使用一个很经典的判断两个字符串字典序大小的技巧，先使用 `hash+二分` 求出 LCP（最长公共前缀），然后用比较 LCP 的下一位求字典序大小。

对于方程里的 $\max$ 操作，类似于 LIS 的 $n\log n$ 做法维护一个 $g$ 数组，之前 $g[i]$ 表示 LIS 为 $i$ 的最小数字，同时 $g$ 数组有单调递增的性质。现在还是维护这样的一个 $g$ 数组，$g[i]$ 表示 LIS 为 $i$ 的字典序最小区间，$g[i]$ 可以用一个 `pair` 类型维护。

当然为了方便，笔者把数组变成了 set，维护相同的东西，方便直接使用 `lower_bound` 查询。

每一个 $f[l][r]$ 都要做一次上述转移，转移复杂度包含：$g$ 数组查找的 $O(\log n)$，每次的查找的比较 $O(\log n)$，共 $O(\log^2 n)$。总共复杂度 $O(n^2\log^2 n)$。

这个复杂度是肯定过不了的，我们考虑从这题的性质上去优化。

每一个 $S(l,r)$ 肯定是从一个比他小的串 $S(x,y)$ 转移过来的，我们可以分两种情况讨论：

1. $S(l,r)$ 靠长度比 $S(x,y)$ 大。
2. $S(l,r)$ 通过字符比较比 $S(x,y)$​ 大。

考虑通过 2 类型的方式转移，那么 $S(l,r)$ 的长度肯定小于等于 $S(x,y)$。

考虑通过 1 类型做贡献的子串的最大长度是 $B$。显然 $B$ 肯定是从 $1$ 开始累加起来的，那么前面肯定出现过长度为 $B-1,B-2,B-3,\cdots,1$ 通过 1 类型转移的子串，他们总共的长度为 $\frac{(1+B)\times B}{2}$，满足
$$
\frac{(1+B)\times B}{2} \leq n
$$
解得
$$
B \leq \sqrt{2n}
$$
说明了什么呢？

通过 1 类型做贡献的子串最大长度是 $\sqrt{2n}$，通过 2 类型做贡献的子串长度小于等于最大子串长度。

那么我们每次只需要求子串长度在 $\sqrt{2n}$ 以内状态，即只需要求满足 $r-l+1\leq \sqrt{2n}$ 所有 $f[l][r]$。

时间复杂度降至 $O(n\sqrt n \log^2 n)$。

擦一把汗还是可以过的，信友队高级组 T1 和这题重了,实测也可以跑过。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define mod 998244353

const int maxn=2e4+5e3+5;

#define ll long long
#define pii pair<int,int>
#define S second
#define F first

int n,B;
char s[maxn];

int ans;
ll sum[maxn],base[maxn];

unordered_map<int,int>f[maxn];

inline ll gt(int r,int l)
{
    return (sum[r]-sum[l-1]*base[r-l+1]%mod+mod)%mod;
}
inline bool cmps(int x,int rx,int y,int ry)
{
    return gt(rx,x)==gt(ry,y);
}
inline bool cmp(int x,int rx,int y,int ry)
{
    int l=1,r=min(rx-x+1,ry-y+1),ans=0;
    while(l<=r)
    {
        int mid=(l+r)>>1;
        if(cmps(x,x+mid-1,y,y+mid-1)) l=mid+1,ans=mid;
        else r=mid-1;
    }
   if(ans==min(rx-x+1,ry-y+1)) return rx-x+1<ry-y+1;
    return s[x+ans]<s[y+ans];
}

struct node
{
    int l,r,w;
    bool operator<(const node a)const{return cmp(l,r,a.l,a.r);}
};
set<node>st;
pii fd[maxn];

int main()
{
    scanf("%d",&n);
    B=sqrt(2*n);
    base[0]=1;for(int i=1;i<=n;i++) base[i]=base[i-1]*113%mod;
    scanf("%s",s+1);
    for(int i=1;i<=n;i++) sum[i]=(sum[i-1]*113+s[i]-'0'+mod)%mod;
    for(int L=1;L<=n;L++)
    {
        for(int R=L;R<=n&&R<=L+B;R++)
        {
            auto it=st.lower_bound({L,R,0});
            if(it!=st.begin()) f[L][R]=(--it)->w+1;
            else f[L][R]=1;
        }
        for(int j=L;j;j--)
        {
            if(L-j+1>B) break;
            if(fd[f[j][L]].F==0)
            {
                st.insert({j,L,f[j][L]});
                fd[f[j][L]]={j,L};
            }
            else if(cmp(j,L,fd[f[j][L]].F,fd[f[j][L]].S))
            {
                st.erase({fd[f[j][L]].F,fd[f[j][L]].S,f[j][L]});
                st.insert({j,L,f[j][L]});fd[f[j][L]]={j,L};
            }
        }
    }
    printf("%d",st.size());
}
```

---

## 作者：居然有个高手 (赞：0)

打完某知名比赛，过来写写好写的 $O(n^2)$ 题解。

考虑一个子串 $[l_1,r_1]$，那么它在最长上升子序列中的上一个元素 $[l_2,r_2]$ 需要满足两个条件：$r_2 < l_1$ 且 $[l_2,r_2]$ 的字典序小于 $[l_1,r_1]$ 的字典序。我们可以考虑将每个子串按字典序从小到大处理，再根据其在序列中的右端点更新对后面子串的转移，使用 trie 处理字典序问题，树状数组取前缀 $\max$ 可以做到 $O(n^2\log n)$。

发现树状数组的第 $i$ 个位置值至多为 $i$，即树状数组中总和为 $O(n^2)$ 级别，所以我们可以暴力更新答案，到更新无效时跳出，这样的复杂度是 $O(n^2)$ 的。

发现使用 trie 时空间复杂度为 $O(n^2c)$，考虑使用 sa 处理字典序信息，这样可以做到线性空间。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2.5e4+5;
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    return x*f;
}
int n,tax[N],rnk[N],sa[N],tp[N],m=300,ans[N],vis[N],st[15][N],lg[N];
char s[N];
inline void sort(){
	for(int i = 0;i<=m;i++)tax[i]=0;
	for(int i = 1;i<=n;i++)tax[rnk[i]]++;
	for(int i = 1;i<=m;i++)tax[i]+=tax[i-1];
	for(int i = n;i>=1;i--)sa[tax[rnk[tp[i]]]--]=tp[i];
}
inline void add(int x,int y){
	if(x>n)return;
	if(ans[x]<y ){
		for(int i = x;i<=n&&ans[i]<y;i++)ans[i]=y;
	}
}
vector<pair<int,int>>v;
inline int query(int l,int r){
	if(l>r)return 11451419;
	int k = lg[r-l+1];
	return min(st[k][l],st[k][r-(1<<k)+1]);
}
int main(){
	int res=0;
	n=read(),scanf("%s",s+1);
	for(int i = 1;i<=n;i++)rnk[i]=s[i]-'0'+1,tp[i]=i;
	sort();
	for(int w=1,p=0;p<n;w<<=1,m=p){
		p=w;
		for(int i = 1;i<=w;i++)tp[i]=n-i+1;
		for(int i = 1;i<=n;i++)if(sa[i]>w)tp[++p]=sa[i]-w;
		sort();
		swap(rnk,tp);
		p=rnk[sa[1]]=1;
		for(int i = 2;i<=n;i++)rnk[sa[i]]=(tp[sa[i]]==tp[sa[i-1]] && tp[sa[i]+w]==tp[sa[i-1]+w])?p:++p;
	}
	lg[0]=-1;
	for(int i = 1,k=0,j;i<=n;i++){
		lg[i]=lg[i>>1]+1;
		if(k)k--;
		j=sa[rnk[i]-1];
		while(s[i+k]==s[j+k])k++;
		st[0][rnk[i]]=k;
	}
	for(int j = 1;j<=lg[n];j++){
		for(int i = 1;i+(1<<j)-1<=n;i++)st[j][i] = min(st[j-1][i],st[j-1][i+(1<<(j-1))]);
	}
	// cout<<lcp[4][2]<<endl;
	for(int i = 1;i<=n;i++){
		// cout<<"!"<<sa[i]<<endl;
		for(int j = 1;j<=n-sa[i]+1;j++){
			if(vis[i] < j){
				// cout<<i<<' '<<j<<' '<<res<<endl;
				for(int k = i;k<=n;k++){
					if(n-sa[k]+1 < j ||query(i+1,k) < j )break;
					vis[k]=j;
					int now=ans[sa[k]]+1;
					// cout<<sa[k]<<' '<<j<<' '<<now<<endl;
					res=max(res,now);v.push_back({sa[k]+j,now});
				}
				for(auto[x,y]:v)add(x,y);
				v.clear();
			}
		}
	}
	cout<<res;
    return 0;
}
```

---

## 作者：PTqwq (赞：0)

# [ABC240Ex] Sequence of Substrings

我居然自己做出了 *3200。/jy

首先发现数据范围 $2.5 \times 10^4$，很可疑，考虑往根号上想（甚至 5s 告诉我们还可以带个 log）。

首先，设选出来的字符串（按顺序排列）为 $s_1, s_2, \dots, s_k$，那么最优的序列一定满足：

$$\forall 1 \leq i < k, |s_{i + 1}| \leq |s_i| + 1$$

考虑证明：根据题意，$s_{i}$ 的字典序严格小于 $s_{i + 1}$，所以只有两种情况：

- $s_i$ 是 $s_{i + 1}$ 的一个前缀。
- 存在 $1 \leq j \leq |s_i|$ 满足 $s_{i, j'} = s_{i + 1, j'}(1 \leq j' < j)$ 且 $s_{i, j} < s_{i + 1, j}$。

第一种情况一定可以保证 $|s_i| < |s_{i + 1}|$，只需要保留 $s_{i + 1}$ 的前 $|s_i| + 1$ 个字符即可。第二种情况可以只保留 $s_{i + 1}$ 的前 $j$ 个字符，也可以满足条件。

考虑 $|s_{i + 1}| \leq |s_{i}| + 1$ 可以给我们带来什么，对于任意一个正整数 $B$，都有：

$$\max\{|s_1|, |s_2|, \dots, |s_k|\} \leq B + \dfrac{n}{B}$$

如果 $\max\{|s_1|, |s_2|, \dots, |s_k|\} < B$ 我们不管，考虑字符串长度先从 $B$ 开始递增，最坏就是每个就增加 $1$，也最多有 $\dfrac{n}{B}$ 个串，长度的上界就是 $B + \dfrac{n}{B}$ 了，取 $B = \sqrt{n}$，就有：

$$\max\{|s_1|, |s_2|, \dots, |s_k|\} \leq \sqrt{n} + \dfrac{n}{\sqrt{n}} = 2\sqrt{n}$$

现在考虑 DP，设 $f_{i, j}$ 表示现在考虑最后一个字符串是子串 $s[i \sim i + j - 1]$，显然有 $j \leq 2\sqrt{n}$，转移就是从之前的字符串中选一个严格小于 $s[i \sim i + j - 1]$ 且右断点严格小于 $i$ 的字符串即可。

考虑把所有长度 $\leq 2\sqrt{n}$ 的子串排序，然后转移就是选取一个前缀的 max 然后加上 $1$，可以用 max 的树状数组维护。

现在有一个问题，就是如何处理字符串相等的情况，这时候我们按左端点 **从大到小** 排序，这样我们按 $i$ 从大到小转移就不会出问题了。

还有一个问题，如果避免右端点 $ > i$ 的情况？很简单，只需要按右端点 **从小到大** 加到树状数组里就行，这样就做完了，时间复杂度 $O(n \sqrt{n} \log n)$，有 $3$ 倍常数。

比较子串大小可以用 SA。

实测跑了 2s。

```cpp
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#include <ext/rope>

bool Mbe;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;

std :: mt19937 rnd (std :: chrono :: steady_clock :: now ().time_since_epoch ().count ());
template < typename T > T gen (const T l, const T r) {
  return rnd () % (r - l + 1) + l;
}
const double pi = std :: acos (-1);

template < typename T > inline void read (T &val) {
  T x = 0;
  bool f = false;
  char c = std :: getchar ();
  for ( ; c < '0' || c > '9' ; c = std :: getchar ()) {
    f |= (c == '-');
  }
  for ( ; c >= '0' && c <= '9' ; c = std :: getchar ()) {
    x = (x << 1) + (x << 3) + (c & 15);
  }
  val = (!f) ? (x) : (-x);
  return ;
}

#define debug(fmt, ...) fprintf(stderr, fmt, ##__VA_ARGS__)
const i64 hashmod1 = 2147483579, hashmod2 = 1610612741, hashmod3 = 805306457;

template < typename T, typename I > void chkmin (T &p, I q) {
  T q_ = q; 
  p = std :: min (p, q_); 
  return ;
}
template < typename T, typename I > void chkmax (T &p, I q) {
  T q_ = q; 
  p = std :: max (p, q_); 
  return ;
}

template < int N, int M >
struct SA {
  int str[N], n;
  int st[N][M], lg[N];
  int rk[N << 1], sa[N], tmp[N << 1], height[N];
  bool empty () {return (n == 0);}
  int size () {return n;}
  void clear () {
    for (int i = 0;i <= n; ++ i) str[i] = 0;
    for (int i = 0;i <= n; ++ i) {
      for (int j = 0;j < M; ++ j) {
        st[i][j] = 0;
      }
      lg[i] = 0;
      sa[i] = 0;
      height[i] = 0;
    }
    for (int i = 0;i <= 2 * n; ++ i) {
      rk[i] = 0;
      tmp[i] = 0;
    }
    n = 0;
    return ;
  }
  void pushchar (int ch) {
    str[++ n] = ch; 
    return ;
  }
  void popchar () {
    assert (!empty ());
    n --;
    return ;
  }
  void init () {
    if (n == 1) {
      rk[1] = sa[1] = 1;
      height[1] = 0;
      lg[0] = -1, lg[1] = 0;
      st[1][0] = height[1];
      return ;
    }
    for (int i = 1;i <= n; ++ i) rk[i] = str[i], sa[i] = i;
    for (int w = 1; w < n; w <<= 1) {
      auto f = [&] (int x) -> std :: pair < int, int > {
        return std :: make_pair (rk[x], rk[x + w]);
      };
      auto g = [&] (int x, int y) -> bool {
        return f (x) < f (y);
      };
      std :: sort (sa + 1, sa + 1 + n, g);
      int p = 1;
      tmp[sa[1]] = 1;
      for (int i = 2;i <= n; ++ i) {
        p += (f (sa[i]) != f (sa[i - 1]));
        tmp[sa[i]] = p;
      }
      for (int i = 1;i <= n; ++ i) rk[i] = tmp[i];
    }
    for (int i = 1, p = 0;i <= n; ++ i) {
      if (p > 0) p --;
      while (str[i + p] == str[sa[rk[i] - 1] + p]) p ++;
      height[rk[i]] = p;
    }
    for (int i = 1;i <= n; ++ i) st[i][0] = height[i];
    for (int j = 1;j < M; ++ j) {
      for (int i = 1;i + (1 << j) - 1 <= n; ++ i) {
        st[i][j] = std :: min (st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
      }
    }
    lg[0] = -1;
    for (int i = 1;i <= n; ++ i) lg[i] = lg[i >> 1] + 1;
    return ;
  }
  int LCPsuf (int x, int y) {
    if (x == y) return n - x + 1;
    x = rk[x], y = rk[y];
    if (x > y) std :: swap (x, y);
    x ++;
    int k = lg[y - x + 1];
    return std :: min (st[x][k], st[y - (1 << k) + 1][k]);
  }
  int LCP (int l, int r, int x, int y) {
    return std :: min ({LCPsuf (l, x), r - l + 1, y - x + 1});
  }
};

const int N = 25025;
const int M = 8000025;
const int L = 320;

SA < N, 17 > str;

struct String {
  int l, r;
  int len () {
    return r - l + 1;
  }
} st[M];

int c[M], tot;

void update (int x, int d) {
  for (int i = x; i <= tot; i += i & -i) chkmax (c[i], d);
  return ;
}

int query (int x) {
  int ans = 0;
  for (int i = x; i > 0; i -= i & -i) chkmax (ans, c[i]);
  return ans;
}

int n, mp[N][325], f[N][325];
char s[N];

std :: vector < std :: pair < int, int > > S[N];

bool Med;
signed main () {
  debug ("%.8lf MB\n", (&Mbe - &Med) / 1048576.0);

  read (n);
  scanf ("%s", s + 1);
  int ans = 0;
  str.clear ();
  S[0].clear ();
  for (int i = 1;i <= n; ++ i) S[i].clear ();
  for (int i = 1;i <= n; ++ i) {
    str.pushchar (s[i]);
    for (int j = 1;i + j - 1 <= n && j <= L; ++ j) {
      tot ++;
      st[tot].l = i, st[tot].r = i + j - 1;
      S[st[tot].r].emplace_back (i, j);
    }
  }
  str.init ();

  std :: sort (st + 1, st + 1 + tot, [&] (String lhs, String rhs) -> bool {
    int lcp = str.LCP (lhs.l, lhs.r, rhs.l, rhs.r);
    if (lcp == lhs.len () && lcp == rhs.len ()) return lhs.l > rhs.l;
    if (lcp == lhs.len ()) return true;
    if (lcp == rhs.len ()) return false;
    return s[lhs.l + lcp] < s[rhs.l + lcp];
  });

  for (int i = 1;i <= tot; ++ i) {
    mp[st[i].l][st[i].len ()] = i;
  }

  for (int i = 1;i <= n; ++ i) {
    for (auto [lef, len] : S[i - 1]) {
      update (mp[lef][len], f[lef][len]);
    }
    for (int j = 1;i + j - 1 <= n && j <= L; ++ j) {
      f[i][j] = query (mp[i][j] - 1) + 1;
      chkmax (ans, f[i][j]);
    }
  }

  printf ("%d\n", ans);

  debug ("%.8lf ms\n", 1e3 * clock () / CLOCKS_PER_SEC);
  return 0;
}
// g++ "[ABC240Ex] Sequence of Substrings.cpp" -o ABC240Ex -std=c++14 -O2 -Wall -Wextra -Wshadow
// check! no inline! (except fastIO)
```

---

## 作者：ningago (赞：0)

图灵杯赛时写的神秘做法，复杂度 $O(\text{能过})$。

令 $dp_{i,j}$ 表示考虑了**开头** $\leq i$ 的子串，当前最后一个子串是 $[i,i+j-1]$ 的最大子串个数。

那么 $dp_{i,j}$ 可以转移到 开头 $\geq i+j$ 且字典序严格大于 $[i,i+j-1]$ 的位置。

剪枝 $1$：如果有 $j<k$ 满足 $dp_{i,j}\geq dp_{i,k}$，那么显然可以忽略 $dp_{i,k}$。

这样每次转移只需要转移到 $lcp(suf_i,suf_k)+1$（保证字典序的前提下）（其中 $k$ 是枚举下一个串的开头）。所以每个状态只有 $O(n)$ 种转移。

具体的转移方法：求出 SA 以后，从 $rk_i$ 分别向前向后扫描，即可动态维护 $lcp$。

剪枝 $2$：$j\leq O(\sqrt i)$。因为字典序是严格递增的，所以取满的情况下，对于最大的串长 $x$，有 $1+2+\cdots +x\leq n$。

所以暴力转移的复杂度为 $O(n^2\sqrt n)$。

称无效转移为：从 $dp_{i,j}$ 转移到 $dp_{x,y}$ 时 $dp_{i,j}+1\leq dp_{x,y}$ 的转移，即无法更新状态。

剪枝 $3$：上述过程中从 $rk_i$ 向后扫描，如果出现无效转移，则可以 `break` 掉。因为字典序比大小是有传递性的，后面肯定都是无效转移。（向前扫同理，但需要先二分出左端点，然后向后扫）。

剪枝 $4$：令 $t$ 为 $sa$ 中与 $i$ 相邻的下一个后缀，即 $sa_{rk_i+1}$。如果 $t<i$，$dp_{i,j}\leq dp_{t,j}$，那么可以不转移 $dp_{i,j}$。原因是显然的。

这样剪枝以后代码跑的很快，很快啊。最劣的点也只跑了 $3s$，平均不超过 $0.3s$。

代码：

```cpp
char s[N];
std::vector <int> dp[N];
void makelen(int x, int y)
{
	while((int)dp[x].size() <= y) dp[x].push_back(0);
}

bool ckmx(int x, int z, int y)
{
	int res = 1;
	if(y < (int)dp[x].size()) 
	{
		res = (z > dp[x][y]);
		ckmax(dp[x][y], z);
	}
	else
	{
		if(z <= dp[x].back()) return 0;
		makelen(x, y); dp[x][y] = z;
	}
	return res;
}
int right[N], left[N];
int kheight[N][15];
int LG[N];

void solve()
{
	n = read(); readstr(s, 1);
	SA_prework();
	for(int i = n; i >= 1; i--) kheight[i][0] = height[i];
	for(int j = 1; j < 15; j++) for(int i = (1 << j); i <= n; i++)
		kheight[i][j] = std::min(kheight[i][j - 1], kheight[i - (1 << (j - 1))][j - 1]), LG[i] = j;
	for(int i = n; i; i--)
	{
		right[i] = i;
		if(i != n && height[i + 1] == n - sa[i] + 1) right[i] = right[i + 1];
	}
	for(int i = 1; i <= n; i++)
	{
		left[i] = i;
		if(i != 1 && height[i] == n - sa[i - 1] + 1) left[i] = left[i - 1];
	}
	for(int i = 1; i <= n; i++) makelen(i, 1), dp[i][1] = 1;
	int ans = 1;
	for(int i = 1; i <= n; i++)
	{
		int L = 0;
		if(i != n && sa[rk[i] + 1] < i) L = std::min(height[rk[i] + 1], (int)dp[sa[rk[i] + 1]].size());
		for(int sz = dp[i].size(), j = 0, lst = 0, p = rk[i]; j < sz; j++)
		{
			if(dp[i][j] <= lst) continue;
			if(j < L && dp[i][j] <= dp[sa[rk[i] + 1]][j]) continue;
			lst = dp[i][j];
			int len = j, lcp = len;
			ckmax(ans, lst);
			for(int j = rk[i] + 1; j <= n; j++)
			{
				ckmin(lcp, height[j]);
				if(sa[j] <= i + len - 1) continue;
				if(sa[j] + lcp <= n) if(!ckmx(sa[j], lst + 1, lcp + 1)) break;
			}
			lcp = len;
			p = rk[i];
			for(int j = LG[p]; ~j; j--) if(kheight[p][j] >= lcp) p -= (1 << j);
			for(int j = p; j < rk[i]; j++)
			{
				if(sa[j] <= i + len - 1) continue;
				if(sa[j] + lcp <= n) if(!ckmx(sa[j], lst + 1, lcp + 1)) break;
			}
		}
	}
	print(ans, '\n');
}
```

---

## 作者：Z1qqurat (赞：0)

感谢学长讲课。校 OJ 最劣解，真有我的。

首先考虑一个暴力做法，设 $f_{i, j}$ 表示选的最后一个子串是 $s(i, j)$ 时能取的字符串数量最大值。那转移就是找选的上一个子串：
$$
f_{i, j} = \max\limits_{i' \le j' < i, s(i', j') < s(i, j)} f_{i', j'} + 1
$$
直接这么做是 $\mathcal {O}(n ^ 4)$ 的。考虑优化。首先发现合法的 $(i, j)$ 并不多：假如我们现在已经有了所选的所有子串的左端点，现在让我们为其选出右端点，那我们肯定贪心地选，相邻两个子串之间长度至多增加 $1$。现在我们想要最大化最后选的那个子串，那就使得相邻子串之间长度增加 $1$，总长为 $1 + 2 + \cdots$，易知最后一个子串的长度上限是 $lim = \sqrt {(2n)}$。所以我们只需要预处理出所有长度 $\le lim$ 的子串，并将它们按照字典序排序就可以了。有效的子串状态总数是 $\mathcal{O} (n \sqrt n)$ 级别的。

但是如果直接把这些状态 sort，还得用哈希比较，两只 $\log$，打不过。发现这样一个性质：如果一个子串 $t$ 为有效状态，那它的所有前缀都是有效状态。这些有前缀关系的子串之间的关系是已知的，直接 sort 就浪费了。考虑将它们放上字典树，然后每个字典树上节点就会代表一个有效状态了，点数 $\mathcal{O} (n \sqrt n)$ 级别。然后对字典树做一次前序遍历就能得到合法状态之间的字典序大小关系了。

现在设 $f_i$ 表示最后一个子串是合法状态 $i = (l, r)$ 时的子串数量最大值。设 $i$ 的相对字典序为 $val_i$：
$$
f_i = \max\limits_{j = (l', r'), val_j < val_i, l' \le r' < l} f_j + 1
$$
以 $val$ 为下标建树状数组，$f$ 为权值，相当于求一个前缀 $\max$，很好做。但是这个 $l\ \le r' < l$ 怎么保证？很简单，把 $l$ 相同的状态一起处理，这时候再把所有右端点为 $l - 1$ 的状态插入树状数组就可以保证了。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define lc tr[u][0]
#define rc tr[u][1]
#define pii pair<int, int>
#define fi first
#define se second
using namespace std;
const int N = 2.5e4 + 5, M = 5.6e6 + 5;
int n, m, tr[M][2], tot, dfn, mx[M], f[M], val[M];
string s;
vector <pii> vec[M];
vector <int> vl[N], vr[N];

void insert(int l, int r) {
    int u = 0;
    for (int i = l; i <= r; ++i) {
        int k = s[i] - '0';
        if(!tr[u][k]) tr[u][k] = ++tot;
        u = tr[u][k];
        vec[u].emplace_back(l, i);
    }
    return ;
}

void dfs(int u) {
    if(vec[u].size()) dfn++;
    for (pii i : vec[u]) {
        m++, val[m] = dfn;
        vl[i.fi].emplace_back(m), vr[i.se].emplace_back(m);
    }
    if(lc) dfs(lc);
    if(rc) dfs(rc);
    return ;
}

void modify(int x, int v) {
    while(x <= dfn) {
        mx[x] = max(mx[x], v);
        x += (x & -x);
    }
    return ;
}

int query(int x) {
    int ret = 0;
    while(x > 0) {
        ret = max(ret, mx[x]);
        x -= (x & -x);
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n; cin >> s; s = '0' + s;
    int lim = sqrt(n * 2);
    for (int i = 1; i <= n; ++i) {
        int j = min(n, i + lim - 1);
        insert(i, j);
    }
    dfs(0);
    int ans = 0;
    for (int l = 1; l <= n; ++l) {
        for (int j : vr[l - 1]) modify(val[j], f[j]);
        for (int j : vl[l]) {
            f[j] = query(val[j] - 1) + 1, ans = max(ans, f[j]);
        }
    }
    cout << ans << "\n";
    return 0;
}
```

---

