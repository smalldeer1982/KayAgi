# [ABC264G] String Fair

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc264/tasks/abc264_g

文字列品評会では、英小文字のみからなる空でない文字列 $ S $ に対して、その「美しさ」を決定します。

文字列 $ S $ の美しさは、$ N $ 個の審査項目の点数の和として定められます。 $ i\ =\ 1,\ 2,\ \ldots,\ N $ について、$ i $ 番目の審査項目の点数は 「文字列 $ T_i $（入力で与えられる**長さ $ 3 $ 以下**の文字列）が $ S $ に連続な部分文字列として含まれる回数」に $ P_i $ を掛けて得られる値です。

英小文字のみからなる**空でない**文字列 $ S $ の美しさとしてあり得る最大値を出力して下さい。 ただし、美しさとしていくらでも大きい値が考えられる場合は、代わりに `Infinity` と出力して下さい。

ここで、文字列 $ U\ =\ U_1U_2\ldots\ U_{|U|} $ に文字列 $ V $ が連続な部分列として含まれる回数とは、 $ 1\ \leq\ i\ \leq\ |U|-|V|+1 $ を満たす整数 $ i $ であって $ U_iU_{i+1}\ldots\ U_{i+|V|-1}\ =\ V $ を満たすものの個数です。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 18278 $
- $ N $ は整数
- $ T_i $ は英小文字のみからなる長さ $ 1 $ 以上 $ 3 $ 以下の文字列
- $ i\ \neq\ j\ \Rightarrow\ T_i\ \neq\ T_j $
- $ -10^9\ \leq\ P_i\ \leq\ 10^9 $
- $ P_i $ は整数

### Sample Explanation 1

例えば、$ S\ = $ `abzabz` について、 - $ 1 $ 番目の審査項目の点数は、`a` が $ S $ に連続な部分列として含まれる回数が $ 2 $ 回であることから、$ 2\ \times\ (-5)\ =\ -10 $ 点 - $ 2 $ 番目の審査項目の点数は、`ab` が $ S $ に連続な部分列として含まれる回数が $ 2 $ 回であることから、$ 2\ \times\ 10\ =\ 20 $ 点 - $ 3 $ 番目の審査項目の点数は、`ba` が $ S $ に連続な部分列として含まれる回数が $ 0 $ 回であることから、$ 0\ \times\ (-20)\ =\ 0 $ 点 であるので、$ S $ の美しさは $ (-10)\ +\ 20\ +\ 0\ =\ 10 $ となります。 別の例として、$ S\ = $ `abzabzabz` について、 - $ 1 $ 番目の審査項目の点数は、`a` が $ S $ に連続な部分列として含まれる回数が $ 3 $ 回であることから、$ 3\ \times\ (-5)\ =\ -15 $ 点 - $ 2 $ 番目の審査項目の点数は、`ab` が $ S $ に連続な部分列として含まれる回数が $ 3 $ 回であることから、$ 3\ \times\ 10\ =\ 30 $ 点 - $ 3 $ 番目の審査項目の点数は、`ba` が $ S $ に連続な部分列として含まれる回数が $ 0 $ 回であることから、$ 0\ \times\ (-20)\ =\ 0 $ 点 であるので、$ S $ の美しさは $ (-15)\ +\ 30\ +\ 0\ =\ 15 $ となります。 一般に、正の整数 $ X $ について、`abz` を $ X $ 回繰り返した文字列の美しさは $ 5X $ となります。 $ S $ の美しさとしていくらでも大きい値が考えられるため、`Infinity` を出力します。

### Sample Explanation 2

$ S\ = $ `ab` が考えられる美しさの最大値を達成します。

### Sample Explanation 3

$ S $ は空でない文字列でなければならないことに注意して下さい。

## 样例 #1

### 输入

```
3
a -5
ab 10
ba -20```

### 输出

```
Infinity```

## 样例 #2

### 输入

```
28
a -5
ab 10
ba -20
bb -20
bc -20
bd -20
be -20
bf -20
bg -20
bh -20
bi -20
bj -20
bk -20
bl -20
bm -20
bn -20
bo -20
bp -20
bq -20
br -20
bs -20
bt -20
bu -20
bv -20
bw -20
bx -20
by -20
bz -20```

### 输出

```
5```

## 样例 #3

### 输入

```
26
a -1
b -1
c -1
d -1
e -1
f -1
g -1
h -1
i -1
j -1
k -1
l -1
m -1
n -1
o -1
p -1
q -1
r -1
s -1
t -1
u -1
v -1
w -1
x -1
y -1
z -1```

### 输出

```
-1```

# 题解

## 作者：AC_love (赞：2)

最短路好题，但是我不想用最短路算法来解。

我们考虑用 DP 来做这道题。

我们设 $f(i, s)$ 表示长度为 $i$ 且后三位为 $s$ 的字符串的最大分数。

显然我们可以暴力转移，以下令 $s'$ 为一个后两位与 $s$ 前两位相同的字符串，$v_s$ 表示三个包含 $s$ 最后一个字符的子串的美丽度的和。例如 $s = \texttt{abc}$ 时，$v_s = abc + bc + c$。

$$f(i, s) = \max f(i - 1, s') + v_s$$

显然我们可以滚动数组压空间，空间复杂度为常数。

另外我们还可以一边转移一边记录 $\max$，转移的复杂度可以降低至 $O(1)$。

如何判 `Infinity`？

我们考虑：如果答案不是 `Infinity` 的话，原字符串一定不会太长。

如果我们用图论的术语来说，就是：如果不存在正环的话，最长路包含的路径数一定是有限的。

我们暴力转移一万五千位，一边转移一边记录最大值和最大值的出现位数。如果我们发现最大值的出现位数和一万五千很接近，说明出现正环了，寄。

反之则输出最大值即可。

状态数是 $26^3 = 17576$，转移是 $O(1)$ 的，然后转移要进行 $15000$ 次，总运算次数大约是 $2 \times 10^8$ 的级别的，卡卡常随便过。

另：哈希建议自己手写，`map` 会导致无中生 $\log$，`unordered_map` 常数奇大，可能会导致 TLE，建议自己写一个 $O(1)$ 的 `hashtable`。

[参考代码](https://atcoder.jp/contests/abc264/submissions/49034086)

---

## 作者：Tsawke (赞：2)

# [[ABC264G] String Fair](https://www.luogu.com.cn/problem/AT_abc264_g) Solution

[TOC]

## [更好的阅读体验戳此进入](http://blog.tsawke.com?t=ABC264G)

## 题面

给定 $ n $ 条评分规则，每条存在字符串 $ T_i $ 和得分 $ P_i $。你需要构造一个任意长度但非空的字符串 $ S $，在 $ S $ 中每次出现 $ T_i $ 就会获得 $ P_i $ 得分。你需要最大化得分，输出最大值。若无限大则输出 `Infinity`。

## Solution

一个十分精妙的图论。

关键的信息在 $ \lvert T_i \rvert \le 3 $，这样的话我们就可以考虑进行建边。我们令 $ P_{str} $ 表示字符串为 $ str $ 的时候的得分，如果没有该字符串的评分规则即为 $ 0 $。

于是考虑如对于从 $ ab $ 通过 $ c $ 可以有一条边到 $ bc $，边权即为 $ P_{abc} + P_{bc} + P_{c} $。同时注意一些细节，如从空字符串可以通过任意字符，如通过 $ a $ 连结到 $ a $，边权即为 $ P_a $，以及对于长度为 $ 1 $ 的字符串连结到长度为 $ 2 $ 的同理。

这样将图建完之后不难发现只需要 SPFA 跑一遍单源最长路，取最大的 $ dis $ 即可，如果存在正环那么显然无限大。

于是点数为 $ n =  26^2 + 26 + 1 $，边数即为 $ m = 26n $，于是 SPFA 最坏复杂度即为 $ O(nm) $，也就是 $ 26^5 $ 的级别，可以通过。

当然这里我们用 `map` 实现，手动实现一个 `hash()` 之后用 `unorderer_map` 即可去掉 `map` 的 $ \log $。

## Code

```cpp
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

#define PI M_PI
#define E M_E
#define npt nullptr
#define SON i->to
#define OPNEW void* operator new(size_t)
#define ROPNEW(arr) void* Edge::operator new(size_t){static Edge* P = arr; return P++;}

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

struct Edge{
    Edge* nxt;
    int to;
    ll val;
    OPNEW;
}ed[21000];
ROPNEW(ed);
Edge* head[1100];

int N;
int cnt(0);
unordered_map < string, int > score;
map < pair < int, int >, int > mp;
unordered_map < int, pair < int, int > > rmp;
bitset < 1100 > inq;
int dep[1100];
ll dis[1100];
ll ans(LONG_LONG_MIN);

void SPFA(void){
    memset(dis, 0xc0, sizeof dis);
    queue < int > cur;
    cur.push(1); inq[1] = true; dep[1] = 1, dis[1] = 0;
    while(!cur.empty()){
        int p = cur.front(); cur.pop();
        inq[p] = false;
        for(auto i = head[p]; i; i = i->nxt){
            if(dis[p] + i->val > dis[SON]){
                dis[SON] = dis[p] + i->val;
                ans = max(ans, dis[SON]);
                dep[SON] = dep[p] + 1;
                if(dep[SON] > 26 * 26 + 26 + 1)printf("Infinity\n"), exit(0);
                if(!inq[SON])cur.push(SON), inq[SON] = true;
            }
        }
    }
}

int main(){
    N = read();
    for(int i = 1; i <= N; ++i){
        string S; cin >> S;
        score.insert({S, read()});
    }mp.insert({{0, 0}, ++cnt}), rmp.insert({cnt, {0, 0}});
    for(int i = 'a'; i <= 'z'; ++i)mp.insert({{0, i}, ++cnt}), rmp.insert({cnt, {0, i}});
    for(int i = 'a'; i <= 'z'; ++i)for(int j = 'a'; j <= 'z'; ++j)
        mp.insert({{i, j}, ++cnt}), rmp.insert({cnt, {i, j}});
    for(int i = 1; i <= cnt; ++i)for(int j = 'a'; j <= 'z'; ++j){
        ll tot(0); string S;
        if(rmp[i].first)S += (char)rmp[i].first;
        if(rmp[i].second)S += (char)rmp[i].second;
        S += j; tot += score[S];
        while(!S.empty()){
            S.erase(S.begin());
            tot += score[S];
        }
        head[i] = new Edge{head[i], mp[{rmp[i].second, j}], tot};
    }SPFA();
    printf("%lld\n", ans);
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

update-2023_01_03 初稿

---

## 作者：cosf (赞：1)

考虑最长路。

因为给定的字符串长度不超过 $3$，所以我们可以对于每一个字母、每一个【两个字母的组合】建一个点，并附加一个空点。令空点为 $0$ 号点。

连边方式如下：

$$
\begin{CD}
0 @>{v_{\alpha}}>> \alpha\\\\
\alpha @>{v_{\beta} + v_{(\alpha\beta)}}>> (\alpha\beta)\\\\
(\alpha\beta) @>{v_{\gamma} + v_{(\beta\gamma)} + v_{(\alpha\beta\gamma)}}>>(\beta\gamma)
\end{CD}
$$

其中，$\alpha, \beta, \gamma$ 均为字母，$v_{\alpha}$ 表示题目给定的 $\alpha$ 的权值，未给定则为 $0$。

这样子，任意一个字符串都对应了图中的一条从 $0$ 开始的路径，其权值就是经过的边权和。

可以发现，如果存在正环，则答案为 `Infinity`，否则为所有除 $0$ 以外点的最长路的最大值。

点数是 $O(|S|^2)$ 的，边数是 $O(|S|^3)$ 的，因此可以用 SPFA，其复杂度为 $O(|S|^5)$，可以通过。

```cpp
#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>
#include <queue>
using namespace std;

#define x(a) (a - 'a' + 1)
#define y(a, b) (x(a) * 26 + x(b))
#define z(a, b, c) (y(a, b) * 26 + x(c))
#define MAXN 20005
#define MAXM 715

using ll = long long;
using pil = pair<int, ll>;

template <typename T>
T INF = numeric_limits<T>::max() >> 1;

vector<pil> e[MAXM];

ll v[MAXN];

int vis[MAXM];
ll dis[MAXM];

int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        string s;
        ll w;
        cin >> s >> w;
        if (s.length() == 1)
        {
            v[x(s[0])] = w;
        }
        if (s.length() == 2)
        {
            v[y(s[0], s[1])] = w;
        }
        if (s.length() == 3)
        {
            v[z(s[0], s[1], s[2])] = w;
        }
    }
    for (char a = 'a'; a <= 'z'; a++)
    {
        e[0].emplace_back(x(a), v[x(a)]);
        for (char b = 'a'; b <= 'z'; b++)
        {
            e[x(a)].emplace_back(y(a, b), v[y(a, b)] + v[x(b)]);
            for (char c = 'a'; c <= 'z'; c++)
            {
                e[y(a, b)].emplace_back(y(b, c), v[z(a, b, c)] + v[y(b, c)] + v[x(c)]);
            }
        }
    }
    queue<int> q;
    fill(dis + 1, dis + MAXM, -INF<ll>);
    vis[0] = 1;
    q.emplace(0);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        vis[u]++;
        for (auto [v, w] : e[u])
        {
            if (dis[v] < dis[u] + w)
            {
                dis[v] = dis[u] + w;
                if (vis[v] % 2 == 0)
                {
                    vis[v]++;
                    if (vis[v] > MAXM * 2)
                    {
                        cout << "Infinity" << endl;
                        return 0;
                    }
                    q.emplace(v);
                }
            }
        }
    }
    cout << *max_element(dis + 1, dis + MAXM) << endl;
    return 0;
}
```

---

## 作者：Take_A_Single_6 (赞：0)

神奇的最短路题目。  
遇到这种“无限”类型的题目，要么去思考循环节，要么尝试建图用正（负）环处理问题。  
显然本题用后者更有前途，spfa 跑最长路判正环，最大的 $dis$ 值就是答案。  
发现可能的字符串数量很小，可以暴力编号然后暴力转移建边：
- $NULL \to a$ 边权为 $val_a$。
- $a \to ab$ 边权为 $val_b+val_{ab}$。
- $ab \to bc$ 边权为 $val_{abc}+val_{bc}+val_{c}$。

复杂度 $O(\lvert W \rvert^5)$，$\lvert W \rvert$ 表示字符集大小，显然可以随便过。  
代码如下，有一些写法：
```cpp
#include<bits/stdc++.h>
#define int long long
#define db double
#define maxn 1000005
#define mod 1000000007
#define fir first
#define sec second
#define pr pair<int,int>
#define pb push_back
#define mk make_pair
#define inf 10000000000000000
using namespace std;
inline int read()
{
    int SS=0,WW=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
	{
        if(ch=='-')WW=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
	{
        SS=(SS<<1)+(SS<<3)+(ch^48);
        ch=getchar();
    }
    return SS*WW;
}
inline void write(int XX)
{
    if(XX<0)putchar('-'),XX=-XX;
    if(XX>9)write(XX/10);
    putchar(XX%10+'0');
}
int n,w,sz,dis[maxn],cnt[maxn],ans=-inf;//注意ans初始化不是0
bool vis[maxn];
char s[maxn];
string ss;
vector<pr>e[maxn];
map<string,int>p,id;//直接用map记录id和值
deque<int>q;
void spfa(int s)
{
	memset(dis,-0x3f,sizeof dis);
	dis[s]=0,q.push_back(s);
	int u;
	while(!q.empty())
	{
		u=q.front(),q.pop_front(),vis[u]=0;
		for(pr v:e[u])
		{
			if(dis[v.fir]<dis[u]+v.sec)
			{
				dis[v.fir]=dis[u]+v.sec;
				if(!vis[v.fir])
				{
					cnt[v.fir]++,vis[v.fir]=1;
					if(cnt[v.fir]>=sz)puts("Infinity"),exit(0);
					if(q.size()&&dis[q.front()]>dis[v.fir])q.push_back(v.fir);
					else q.push_front(v.fir);//slf优化
				}
			}
		}
	}
}
signed main()
{
    n=read();
    for(int i=1;i<=n;i++)cin>>ss>>w,p[ss]=w;
    ss="000";
    for(ss[0]='a';ss[0]<='z';ss[0]++)
	{
		id[ss.substr(0,1)]=++sz;
		for(ss[1]='a';ss[1]<='z';ss[1]++)
		{
			id[ss.substr(0,2)]=++sz;
			for(ss[2]='a';ss[2]<='z';ss[2]++)
			id[ss.substr(0,3)]=++sz;
		}
	}//可以用substr映射map
    for(ss[0]='a';ss[0]<='z';ss[0]++)
    {
    	e[0].pb(mk(id[ss.substr(0,1)],p[ss.substr(0,1)]));
    	for(ss[1]='a';ss[1]<='z';ss[1]++)
    	{
    		e[id[ss.substr(0,1)]].pb(mk(id[ss.substr(0,2)],p[ss.substr(0,2)]+p[ss.substr(1,1)]));
    		for(ss[2]='a';ss[2]<='z';ss[2]++)
    			e[id[ss.substr(0,2)]].pb(mk(id[ss.substr(1,2)],p[ss.substr(0,3)]+p[ss.substr(1,2)]+p[ss.substr(2,1)]));
		}//直接调用id
	}
    spfa(0);
    for(int i=1;i<=sz;i++)ans=max(ans,dis[i]);
    write(ans);
    return 0;
}
```

---

