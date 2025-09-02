# [ABC365G] AtCoder Office

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc365/tasks/abc365_g

AtCoder 社のオフィスには $ N $ 人の高橋くんが所属しています。

AtCoder 社ではオフィスの入退室の記録が取られており、記録が取られはじめてから $ M $ 回の入退室が行われました。

$ i $ 番目 $ (1\leq\ i\leq\ M) $ の入退室記録は整数の組 $ (T\ _\ i,P\ _\ i) $ で表され、時刻 $ T\ _\ i $ に $ P\ _\ i $ 番目の高橋くんがオフィスの外にいるならオフィスに入ったことを、オフィスの中にいるならオフィスから出たことを表します。

記録が取られはじめた時点ではどの高橋くんもオフィスの外におり、現在どの高橋くんもオフィスの外にいることがわかっています。

次の形式の $ Q $ 個の質問に答えてください。

$ i $ 番目 $ (1\leq\ i\leq\ Q) $ の質問では整数の組 $ (A\ _\ i,B\ _\ i) $ が与えられるので、記録を取っていた間に $ A\ _\ i $ 番目の高橋くんと $ B\ _\ i $ 番目の高橋くんがどちらもオフィスの中にいた時間の長さを求めてください。

## 说明/提示

### 制約

- $ 2\leq\ N\leq2\times10\ ^\ 5 $
- $ 2\leq\ M\leq2\times10\ ^\ 5 $
- $ 1\leq\ T\ _\ 1\lt\ T\ _\ 2\lt\dotsb\lt\ T\ _\ M\leq10\ ^\ 9 $
- $ 1\leq\ P\ _\ i\leq\ N\ (1\leq\ i\leq\ M) $
- どの $ 1\leq\ p\leq\ N $ についても、$ P\ _\ i=p $ となる $ i $ は偶数個存在する
- $ 1\leq\ Q\leq2\times10\ ^\ 5 $
- $ 1\leq\ A\ _\ i\lt\ B\ _\ i\leq\ N\ (1\leq\ i\leq\ Q) $
- 入力はすべて整数
 
### Sample Explanation 1

$ 3 $ 人の高橋くんがオフィスの中にいた時間はそれぞれ以下の図のようになります。 !\[\](https://img.atcoder.jp/abc365/268561b2e39007a186ef6ce29471170f.png) それぞれの質問に対する答えは以下のようになります。 - $ 1 $ 番目の高橋くんと $ 2 $ 番目の高橋くんが同時にオフィスの中にいた時間は、時刻 $ 20 $ から時刻 $ 30 $ の間と時刻 $ 70 $ から時刻 $ 80 $ の間の $ 2 $ 回です。長さはどちらも $ 10 $ なので、これらの合計である $ 20 $ を出力してください。 - $ 1 $ 番目の高橋くんと $ 3 $ 番目の高橋くんが同時にオフィスの中にいたことはありません。よって、$ 0 $ を出力してください。 - $ 2 $ 番目の高橋くんと $ 3 $ 番目の高橋くんが同時にオフィスの中にいた時間は、時刻 $ 40 $ から時刻 $ 60 $ の間の $ 1 $ 回です。長さは $ 20 $ なので、$ 20 $ を出力してください。

## 样例 #1

### 输入

```
3 8
10 1
20 2
30 1
40 3
60 3
70 1
80 2
90 1
3
1 2
1 3
2 3```

### 输出

```
20
0
20```

## 样例 #2

### 输入

```
10 20
10257 9
10490 4
19335 1
25893 5
32538 9
33433 3
38522 9
40629 9
42896 5
52106 1
53024 3
55610 5
56721 9
58286 9
63128 3
70513 3
70977 4
74936 5
79883 9
95116 9
7
1 3
3 9
1 9
4 9
1 5
5 9
3 5```

### 输出

```
18673
2107
15310
25720
17003
10317
16848```

# 题解

## 作者：freoepn (赞：14)

根号分治。

对于出入次数多于 $\sqrt{M}$ 次的人离散化后维护出现次数的前缀和，并记录下他和所有人询问的结果，因为这样的人顶多有 $\sqrt{M}$  个，复杂度为 $O((N+M)\sqrt{M})$。

现在只需要考虑对两个出入次数少于 $\sqrt{M}$ 次的人的询问，因为出入此时较少，直接双指针复杂度为 $O(\sqrt{M})$，总复杂度不超过 $O(Q\sqrt{M})$。


```cpp
#include <bits/stdc++.h>
using namespace std;
const int kMaxN = 200005, B = 500;
vector<int> v[kMaxN];
int tot = 0;
int p[kMaxN], a[kMaxN],b[kMaxN], sum[kMaxN], ans[B][kMaxN];
int main() {
 ios::sync_with_stdio(0);
 cin.tie(0),cout.tie(0);
  int n, m, q;
  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    cin >> a[i] >> b[i];
    v[b[i]].push_back(i);
  }
  for (int i = 1; i <= n; i++) {
    if (v[i].size() >= B) {
      p[i] = ++tot;
      int u = 0;
      for (int j = 1; j <= m; j++) {
        sum[j] = sum[j - 1];
        if (u == 1) {
          sum[j] += (a[j] - a[j - 1]);
        }
        if (b[j] == i) {
          u ^= 1;
        }
      }
      for (int j = 1; j <= n; j++) {
        for (int k = 1; k < v[j].size(); k += 2) {
          ans[tot][j] += sum[v[j][k]] - sum[v[j][k - 1]];      

        }
      }
    }
  }
  cin >> q;
  while (q--) {
    int x, y;
    cin >> x >> y;
    if (p[x] == 0) {
      swap(x, y);
    }
    if (p[x] != 0) {
      cout << ans[p[x]][y] << '\n';
      continue;
    }
    int p = 1, ans = 0;
    for (int i = 1; i < v[x].size(); i+=2) {
      while (p < v[y].size() && a[v[y][p]] < a[v[x][i]]) {
        ans += max(0, a[v[y][p]] - max(a[v[y][p - 1]], a[v[x][i - 1]]));
        p += 2;
      }
      if(p < v[y].size()){
        ans += max(0, a[v[x][i]] - max(a[v[y][p - 1]], a[v[x][i - 1]]));
      }
    }
    cout << ans << '\n';
  }
  return 0;
}
```

---

## 作者：沉石鱼惊旋 (赞：5)

# 题目翻译

有 $n$ 个人，给定 $m$ 个信息，第 $i$ 条表示 $t_i$ 时刻人 $p_i$ 进 / 出了房间。

进还是出由之前的状态决定。保证最后所有人都是出的。

现在给定 $q$ 个询问，查询 $a,b$ 表示 $a$ 在房间和 $b$ 在房间的时间的交集大小。

$2\leq n,m\leq 2\times 10^5$，$1\leq p_i,a,b\leq n$，$1\leq t_i\leq 10^9$，保证 $t_i$ 严格递增。

# 题目思路

后文复杂度不严格区分 $n$ 与 $m$ 还有 $q$。默认都是 $n$ 量级的。

我们先把进出房间的时刻看成线段的两个端点，线段就是这个人在房间里的时间。

那么这个题转化成问两个人线段的交集大小。

设 $cnt_i$ 表示第 $i$ 个人的线段个数，我们可以得到 $\mathcal O(\sum\limits_{i=1}^n cnt_i)=\mathcal O(n)$。

$n$ 个人 $n$ 条线段，不难想到是根号分治，线段数量 $\gt B$ 的人数量是 $\leq \frac n B$ 的。

根据这个，我们把人分为大人和小人。根据这个讨论怎么做。

- 两个小人

  那么我们把这些线段合并，记 $lst_{0/1}$ 表示 $a$ 或 $b$ 上一个左端点在哪里。往序列里扔每个人的端点，记录三个值 $t,o,p$ 表示时间刻，是左端点还是右端点，是 $a$ 还是 $b$ 的时间刻。

  如果找到左端点更新 $lst$。找到右端点算 $t-\max\{lst_0,lst_1\}$ 就是这一段线段的答案。

  把每个人的线段加进来的过程，需要排序。但是我们如果本来线段就是有序存放的，我们归并即可。两个有序地数组归并到一起只需要维护两个指针移动。这样这部分就是 $\mathcal O(\sqrt n)$ 时间内解决。

- 一大一小

  不妨设 $a$ 是小人 $b$ 是大人。

  单独分这一类不是很必要，但这是两个大人处理的基础。

  枚举小人的区间，那么我们就要支持查询区间内 $b$ 的时间有多长。

  端点数量是 $\mathcal O(n)$ 的，我们设 $sum_{i,j}$ 表示第 $i$ 个大人的前 $j$ 个时刻（时刻是 $10^9$ 级别的，但是可以离散化成 $n$ 级别的）有多少时间在房间里。这个 $sum$ 提前预处理出来，处理方式很简单，不细说了。

  通过前缀和减一下就能得到我们区间内 $b_i$ 的时间数量。

  这一段复杂度 $\mathcal O(\sqrt n)$。

- 两个大人

  设 $ans_{i,j}$ 表示第 $i$ 个大人和第 $j$ 个大人的答案。

  枚举第 $i$ 个大人，枚举第 $j$ 个大人。由于 $\mathcal O(\sum\limits_{i=1}^n cnt_i)=\mathcal O(n)$，那么所有可能的第 $j$ 个大人的线段总数是 $\mathcal O(n)$ 的。**所以暴力预处理 $ans_{i,j}$ 复杂度就是正确的。**

  事实上，一大一小可以和两个大人合并在一起， 设 $ans_{i,j}$ 表示第 $i$ 个大人和第 $j$ 个人的答案。 ~~但是赛时想到了一大一小的做法就先敲上了，不改了。~~


所以我们在 $\mathcal O(n\sqrt n)$ 的时间内完成了这个问题。

实现的时候注意一些小问题，比如要提前离散化信息，两个小人的处理归并合并。这些多的 $\log$ 都可以简单优化掉，这里不细说了。

# 完整代码

[AT submission 56309131](https://atcoder.jp/contests/abc365/submissions/56309131)

成为了全场倒数第二个过 G 的。

一开始写的 $\mathcal O(n\sqrt n\log n)$ 的 TLE 了 $2$ 个点。但是有人 $\mathcal O(n\sqrt n\log n)$ 卡过去了，可能我写的常数有点大。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define getchar() p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1000000, stdin), p1 == p2) ? EOF : *p1++
char buf[1000000], *p1 = buf, *p2 = buf;
template <typename T>
void read(T &x)
{
    x = 0;
    int f = 1;
    char c = getchar();
    for (; c < '0' || c > '9'; c = getchar())
        if (c == '-')
            f = -f;
    for (; c >= '0' && c <= '9'; c = getchar())
        x = x * 10 + c - '0';
    x *= f;
}
template <typename T, typename... Args>
void read(T &x, Args &...y)
{
    read(x);
    read(y...);
}
template <class T>
void write(T x)
{
    static int stk[30];
    if (x < 0)
        putchar('-'), x = -x;
    int top = 0;
    do
    {
        stk[top++] = x % 10, x /= 10;
    } while (x);
    while (top)
        putchar(stk[--top] + '0');
}
template <class T>
void write(T x, char lastChar) { write(x), putchar(lastChar); }
const int inf = 2e9;
const int B = 300;
int n, m;
int Q;
array<int, 2> a[200020];
vector<array<int, 2>> vec[200020];
bool in[200020];
int lst[200020];
int sum[700][200020];
int lsh[200020];
int id[200020], tot;
bool hav[200020];
int aa[700][700];
vector<int> big;
unordered_map<int, int> mp;
int main()
{
    read(n, m);
    for (int i = 1; i <= m; i++)
    {
        read(a[i][0], a[i][1]);
        if (in[a[i][1]])
            vec[a[i][1]].push_back({lst[a[i][1]], a[i][0]});
        else
            lst[a[i][1]] = a[i][0];
        in[a[i][1]] ^= 1;
        mp[a[i][0]] = i;
    }
    big.push_back(0);
    for (int i = 1; i <= n; i++)
    {
        if (vec[i].size() <= B)
            continue;
        big.push_back(i);
        id[i] = ++tot;
        memset(hav, 0, sizeof(hav));
        for (auto [l, r] : vec[i])
        {
            for (int j = mp[l] + 1, ed = mp[r]; j <= ed; j++)
                hav[j] = 1;
        }
        for (int i = 1; i <= m; i++)
        {
            if (hav[i])
                sum[tot][i] = a[i][0] - a[i - 1][0];
        }
        for (int i = 1; i <= m; i++)
            sum[tot][i] += sum[tot][i - 1];
    }
    for (int i = 1; i < big.size(); i++)
    {
        for (int j = 1; j < big.size(); j++)
        {
            if (i == j)
                continue;
            int y = big[j];
            for (auto [l, r] : vec[y])
                aa[i][j] += sum[i][mp[r]] - sum[i][mp[l]];
        }
    }
    read(Q);
    while (Q--)
    {
        int x, y;
        read(x, y);
        if (vec[x].size() > vec[y].size())
            swap(x, y);
        if (vec[y].size() <= B) // 小小
        {
            vector<array<int, 3>> u, v;
            int i = 0, j = 0;
            for (auto [l, r] : vec[x])
            {
                u.push_back({l, 0, 0});
                u.push_back({r, 1, 0});
            }
            for (auto [l, r] : vec[y])
            {
                while (i < u.size() && u[i][0] <= l)
                    v.push_back(u[i]), i++;
                v.push_back({l, 0, 1});
                while (i < u.size() && u[i][0] <= r)
                    v.push_back(u[i]), i++;
                v.push_back({r, 1, 1});
            }
            int lst[2] = {inf, inf};
            int ans = 0;
            for (auto [t, o, p] : v)
            {
                if (o == 1)
                {
                    if (lst[0] < inf && lst[1] < inf)
                        ans += t - max(lst[0], lst[1]);
                    lst[p] = inf;
                }
                else
                {
                    lst[p] = t;
                }
            }
            write(ans, '\n');
        }
        else if (vec[x].size() <= B) // 小大
        {
            int j = id[y];
            int ans = 0;
            for (auto [l, r] : vec[x])
                ans += sum[j][mp[r]] - sum[j][mp[l]];
            write(ans, '\n');
        }
        else // 大大
        {
            write(aa[id[x]][id[y]], '\n');
        }
    }
    return 0;
}
```

---

## 作者：_Yonder_ (赞：5)

说下我的小丑做题历程：

这里令 $val(x)$ 为第 $x$ 个人所待在办公室的总时间数。

首先我看到题解设了个阈值 $v$，于是我便将 $v$ 取为 $\sqrt m$，接着对于查询 $x,y$ 中 $val(x),val(y)\le v$ 的用珂朵莉树求贡献，反之用动态开点线段树。对于已经出现过得查询 $A_i,B_i$ 直接查找之前的记录就好，然后这个 $O(m\sqrt m\log n)$ 的做法他居然超时了！

接着我便疯狂更改阈值，然后一直超时，我是真的难绷，其中一次它还是只超时一个点（阈值取得 100），我最后把阈值改为 0，结果过了？

在这个做法中，我首先将 $val(x),val(y)$ 进行了比较，若 $val(x)$ 更大，则交换 $x,y$ 的值，这一步稳定了时间复杂度，也就是说要出一个平衡的数据来卡，至多是 $O(m\sqrt n\log n)$ 的（这不是一样吗，为什么这个过了，珂朵莉树给我卡成那样，珂朵莉树常数有这么大吗）。

看在我这么惨的份上，给个赞吧（QwQ）。
# Code

```
#include<bits/stdc++.h>
#ifdef ONLINE_JUDGE
static char buf[4500000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,4500000,stdin),p1==p2)?EOF:*p1++
#endif
#define S std::ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
#define rep(i,l,r) for(register int i=l;i<=r;i++)
#define per(i,l,r) for(register int i=l;i>=r;i--)
#define ll long long
#define itset set<node>::iterator
using namespace std;
template<typename P>inline void read(P&x){bool f=0;x=0;char c=getchar();while(!isdigit(c)) f|=c=='-',c=getchar();while(isdigit(c)) x=(x<<3)+(x<<1)+(c^48),c=getchar();x=f?~(x+1):x;}
template<typename P>inline void write(P x){if(x<0) putchar('-'),x=-x;if(x>9) write(x/10);putchar((x%10)^48);}
const int N=2e5+5,inf=1e9;
int L[N*400],R[N*400],sum[N*400],tag[N*400],root[N],cnt;
	inline void ca(int &p,int d,int pl,int pr){if(!p) p=++cnt;tag[p]=d;sum[p]=(pr-pl+1)*d;}
	inline void push_down(int p,int pl,int pr){
		int mid=pl+pr>>1;
		if(~tag[p]) ca(L[p],tag[p],pl,mid),ca(R[p],tag[p],mid+1,pr),tag[p]=-1;
	}inline void push_up(int p){sum[p]=sum[L[p]]+sum[R[p]];}
	inline void Modify(int l,int r,int v,int &p,int pl=1,int pr=inf){
		if(!p) tag[p=++cnt]=-1;
		if(l<=pl&&pr<=r) return ca(p,v,pl,pr);int mid=pl+pr>>1;
		push_down(p,pl,pr);
		if(l<=mid) Modify(l,r,v,L[p],pl,mid);
		if(r>mid) Modify(l,r,v,R[p],mid+1,pr);
		push_up(p);
	}inline int Ask(int l,int r,int &p,int pl=1,int pr=inf){
		if(!p||!sum[p]) return 0;
		if(~tag[p]) return tag[p]*(min(r,pr)-max(l,pl)+1);
		if(l<=pl&&pr<=r) return sum[p];int mid=pl+pr>>1,ans=0;
		push_down(p,pl,pr);
		if(l<=mid) ans+=Ask(l,r,L[p],pl,mid);
		if(r>mid) ans+=Ask(l,r,R[p],mid+1,pr);
		return ans;
	}
vector<pair<int,int>> v[N];
map< pair<int,int> ,int> p;
int n,m,q,x,y,t[N],Sqrt;
inline int ask(int x,int y){
	if(v[x].size()>v[y].size()) swap(x,y);
	int ans=0;
	for(pair<int,int> i:v[x])
		ans+=Ask(i.first,i.second-1,root[y]);
	return ans;
}
int main(){
	S;cin>>n>>m;
	rep(i,1,m){
		cin>>x>>y;
		if(t[y]) v[y].push_back({t[y],x}),t[y]=0;
		else t[y]=x;
	}rep(i,1,n){
		for(pair<int,int> j:v[i])
			Modify(j.first,j.second-1,1,root[i]);
	}cin>>q;
	while(q--){
		cin>>x>>y;
		if(p.count(make_pair(x,y))){cout<<p[make_pair(x,y)]<<endl;continue;}
		int u=ask(x,y);
		p[make_pair(x,y)]=u;
		cout<<u<<endl;
	}
	return 0;
}
```

---

## 作者：Shunpower (赞：3)

无根号分治做法。

## Statement

有 $n$ 个人在工作，还有一间办公室。最开始办公室内没有人。接下来有 $m$ 个事件。

每个事件 $(t,p)$ 表述在时刻 $t$，人 $p$ 是否在办公室内的状态改变。如果 $p$ 在办公室内，则他离开；反之他进入办公室。

有 $q$ 个查询，每个查询输入一对 $(u,v)$，你需要输出 $u,v$ 人同时在办公室内的总时长。

保证事件结束后所有人都在办公室外。

**数据范围：**$1\leq n,m,q\leq 2\times 10^5$，每个事件发生的时刻单调递增。

## Solution

感觉 polylog 不好做，我们考虑根号算法。

类似操作分块，我们把事件每 $B$ 个一块，然后考虑每一块内部的情况对所有询问的贡献。只需要把每个询问每一块的贡献加在一起就是总贡献。

实现的时候，我们假设一块内包含的事件为 $[l,r]$ 的这些事件，那么我们就统计 $[t_l,t_{r+1})$ 这段时间的贡献。

下面称呼在块内改变过办公室状态的人是关键人。

因为只有 $\frac{m}{B}$ 个块，所以考虑在块末枚举所有询问：

1. 若询问的人 $(u,v)$ 都不是关键人，则这一块对这个询问的贡献为整个块的时间跨度（两人都一直在）或 $0$（两人都一直不在）。
2. 若询问的人 $(u,v)$ 有且恰好有一位关键人，则这一块对询问的贡献依赖于关键人或 $0$。具体来说，若那个非关键人一直都不在，则贡献为 $0$，反之贡献为关键人在本块内在办公室内时间的总长。
3. 询问的人 $(u,v)$ 两人都是关键人。

整个块的时间跨度容易通过块的定义计算得到。

考虑一块内的关键人只有 $\mathcal O(B)$ 个。所以我们可以直接对每个关键人扫一遍块，容易算出每个关键人在本块内在办公室内时间的总长。

实现来说，标记一下上次进来是什么时候，出去的时候算一段的贡献即可。特别地，如果一开始就在，可以看成 $T_l$ 时进入；如果最后都没走，可以看成 $T_{r+1}$ 时离开（下一块开始的时候就会看成一开始就在，同一时刻离开进入不影响）。

比较麻烦做的是第三种情况：两个人都是关键人。但我们发现，我们可以尝试直接维护一个 $\mathcal O(B^2)$ 大小的二维数组表示每一对关键人在本块内同时在办公室的时间总长。

考虑嫁接一下一个关键人那个办法。我们记录两个关键人“同时在办公室”这件事开始的时候，再在两个人有一方离开的时候记录上一段同时在办公室的贡献。

具体来说，我们维护两个 $\mathcal O(B^2)$ 大小的二维数组，一个是每对关键人在本块内产生的总贡献，一个是每对关键人从什么时候开始一起在办公室内。我们扫一遍块内的所有事件，当有一个人进入办公室时，扫一遍所有办公室内的关键人，在时刻数组对应位置记录现在的时间，表示两个人开始同时在；当有一个人离开办公室时，也扫一遍所有办公室内的关键人，在贡献数组对应位置加上上一段的贡献。边界的处理和那个办法是一样的。

这样处理询问的时候直接查总贡献表就行。

现在我们会统计每个询问在每一块内产生的贡献了，每一块的加在一起就是最终答案。

精细实现一下（指不用 `map` 开二维数组）复杂度就可以做到 $\mathcal O(\frac{m}{B}q+B(m+n))$ 的。取 $B=\sqrt q$ 就能做到 $\mathcal O((m+n)\sqrt q)$，当然 $B=\sqrt m$ 也跑得飞快。

实现很简单，只是要清空的数组有点多。赛时有点急代码写丑了，虽然最后也没调完就是了。

## Code

加了点注释。

```cpp
//Author:KIT / Shunpower
//Cloud Island & Letter to Past
//May the force be with you and me.
#include <bits/stdc++.h>
// #pragma GCC optimize("Ofast")
#define ET return 0
#define fi first
#define se second
#define mp make_pair
#define pb emplace_back
#define ll long long
#define ull unsigned long long
#define inf INT_MAX
#define uinf INT_MIN
#define pii pair<int,int>
#define pll pair<ll,ll>
#define fr1(i,a,b) for(int i=a;i<=b;i++)
#define fr2(i,a,b) for(int i=a;i>=b;i--)
#define fv(i,p) for(int i=0;i<p.size();i++)
#define ld long double
#define il inline
#define ptc putchar
using namespace std;
const int N=2e5+10;
namespace Shun{
	int lowbit(int x){
		return x&-x;
	}
	template <typename T>
	inline void read(T &x){
	   T s=0,w=1;
	   char ch=getchar();
	   while(ch<'0'||ch>'9'){
	   		if(ch=='-'){
				w=-1;
	   		}
	        ch=getchar();
		}
	   while(ch>='0'&&ch<='9'){
	   		s=s*10+ch-'0';
			ch=getchar();
	   }
	   x=s*w;
	}
	template <typename T>
	inline void write(T x){
	    if(x<0){
	        putchar('-');
	        x=-x;
	    }
	    if(x>9){
	    	write(x/10);
		}
	    putchar(x%10+'0');
	}
}
using namespace Shun;
int n,m,q;
int len;
int t[N],p[N];
vector <pii> query;
int lst;
bool trn[N];
bool vis[N];
vector <int> key;
pll coff[455][455];//关键人对同时在的时间，用来算第三类询问
ll sum[455];//单个关键人在的时间，用来算第二类询问
int lsd[N];
int bac[N];
ll ans[N];
void solve(int l,int r){
    int st=t[l],fn=t[r+1];//这一块管的时间跨度
    fr1(i,1,n) vis[i]=0;
    fr1(i,l,r) vis[p[i]]=1;
    key.clear();
    fr1(i,1,n) if(vis[i]) key.pb(i);//关键人就是被改变状态过的人
    int sz=key.size()-1;
    fr1(i,1,n) bac[i]=lsd[i]=0;
    fr1(i,0,sz) bac[key[i]]=i;
    fr1(i,0,sz) sum[i]=0;
    fr1(i,0,sz) fr1(j,0,sz) coff[i][j]=mp(0,0);//第一项是总贡献，第二项是“同时在”的开始时刻
    fr1(i,0,sz){
        fr1(j,0,sz){
            coff[i][j].fi=0;
            if(trn[key[i]]&&trn[key[j]]) coff[i][j].se=st;//块一开始就同时在
        }
    }
    fr1(i,1,n) if(trn[i]) lsd[i]=st;//块一开始就在
    fr1(i,l,r){
        int x=p[i];
        if(!trn[x]){//从不在变成在
            fr1(j,0,sz){
                if(trn[key[j]]) coff[bac[x]][j].se=coff[j][bac[x]].se=t[i];//“同时在”开始
            }
            lsd[x]=t[i];//开始在
        }
        else{//从在变成不在
            fr1(j,0,sz){
                if(trn[key[j]]){//“同时在”结束，计算上一段贡献，清空开始时刻
                    coff[bac[x]][j].fi+=(t[i]-coff[bac[x]][j].se);
                    coff[bac[x]][j].se=0;
                    coff[j][bac[x]].fi+=(t[i]-coff[j][bac[x]].se);
                    coff[j][bac[x]].se=0;
                }
            }
            sum[bac[x]]+=t[i]-lsd[x];//不在了，计算上一段贡献
            lsd[x]=0;
        }
        trn[x]^=1;//记得改变状态
    }
    fr1(i,0,sz){
        fr1(j,0,sz){
            if(trn[key[i]]&&trn[key[j]]) coff[i][j].fi+=(fn-coff[i][j].se);//最后还同时在，计算最后一段的贡献，可以接上下一块
        }
    }
    fr1(i,1,n){
        if(vis[i]&&trn[i]) sum[bac[i]]+=fn-lsd[i];//最后还在，计算最后一段的贡献，可以接上下一块
    }
    fr1(i,0,q-1){
        if(vis[query[i].fi]&&vis[query[i].se]) ans[i]+=coff[bac[query[i].fi]][bac[query[i].se]].fi;//都是关键人直接查表
        else if(vis[query[i].fi]){//其中一个是关键人就关心另一个人
            if(trn[query[i].se]) ans[i]+=sum[bac[query[i].fi]];
        }
        else if(vis[query[i].se]){
            if(trn[query[i].fi]) ans[i]+=sum[bac[query[i].se]];
        }
        else{
            if(trn[query[i].fi]&&trn[query[i].se]) ans[i]+=fn-st;//两个人都不是关键人直接看两个人的状态
        }
    }
}
// #define Ltp cute
int main(){
#ifdef Ltp
	freopen("G.txt","r",stdin);
	freopen("out.txt","w",stdout);
#endif
    ios::sync_with_stdio(false);
    cin>>n>>m;
    fr1(i,1,m) cin>>t[i]>>p[i];
    cin>>q;
    fr1(i,1,q){
        int u,v;
        cin>>u>>v;
        query.pb(mp(u,v));
    }
    lst=1;
    t[m+1]=1e9+1;
    len=sqrt(m);
    fr1(i,1,m){
        if(i%len==0||i==m){
            solve(lst,i);
            lst=i+1;
        }
    }
    fr1(i,0,q-1) cout<<ans[i]<<'\n';
	ET;
}
//ALL FOR Zhang Junhao.
```

[AC Submission](https://atcoder.jp/contests/abc365/submissions/56335273)

---

## 作者：DGH_Didi (赞：3)

## 这是一篇暴力做法的题解

### 题目大意
给定 $N$ 个人共 $M$ 段可间断工作时间段，有 $Q$ 次询问，每次求两个人工作时间的重叠长度，**时限 5s**。
- $1 \leq N \leq 2 \times 10^5$
- $1 \leq M \leq 2 \times 10^5$
- $1 \leq Q \leq 2 \times 10^5$

### 解题思路
首先要知道的一点是，AT的机子一直是很快的，5s 的时间可以跑到 $10^{10}$ 左右的数据量，可以大胆尝试 $O(n^2)$ 的做法。于是对于每次询问我们直接暴力地计算即可，每次使用双指针计算两个人的答案，总复杂度 $O(NM)$。

一个显而易见的优化是，我们每次算完以后用 `std::map` 记录答案，这样可以防止数据用多次询问一组计算量很大的数据卡死我们。提交后发现只有一个点 `TLE` 了，索性开 O3 通过此题。

### 参考代码 
#### [提交记录(C++20 4986ms)](https://atcoder.jp/contests/abc365/submissions/56295220)
```cpp
#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#define endl '\n'

using namespace std;
using i64 = long long;

const int N = 2e5 + 5;
int n, m, q;
int f[N];
vector<pair<int, int>> ti[N];
map<pair<int, int>, int> ans;

int cal(int x, int y) {
    if (x > y) {
        swap(x, y);
    }
    if (ans.count({x, y})) {
        return ans[{x, y}];
    }
    int p = 0, res = 0;
    for (auto [l, r] : ti[x]) {
        if (p != 0) {
            --p; // 前一个有可能可能和这个区间匹配
        }
        for (p; p < ti[y].size(); p++) {
            auto [l1, r1] = ti[y][p];
            if (l1 > r) {
                break;
            }
            if (r1 < l) {
                continue;
            }
            if (l <= r1 && r1 <= r) {
                res += r1 - max(l, l1);
            } else if (l <= l1 && l1 <= r) {
                res += min(r, r1) - l1;
            } else if (l1 <= l && r <= r1) {
                res += r - l;
            }
            // 这里浅浅分讨一下，赛时没想到优雅的写法
        }
    }
    return ans[{x, y}] = res;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        if (f[y]) {
            ti[y].push_back({f[y], x});
            f[y] = 0;
        } else {
            f[y] = x;
        }
    }
    cin >> q;
    while (q--) {
        int x, y;
        cin >> x >> y;
        cout << cal(x, y) << endl;
    }
    return 0;
}
```

### 后记
第一次赛时 perf2400，还是很激动，虽然是用了点歪门邪道吧。

---

## 作者：Heldivis (赞：2)

## [ABC365G] AtCoder Office

线段树合并解法，用时 $2500\text{ ms}$。

对于每个人开一个线段树，每人在区间的一段时间就是区间加法。动态开点线段树维护即可。

对于询问操作，将两个线段树合并。具体操作：如果某一个线段树当前节点维护的区间和等于区间长度，即 `st[p].dat == tr - tl + 1`，那么另一个节点的区间和就是重叠长度：

```cpp
ll Merge(int p, int q, int tl, int tr) {
  if (st[p].dat == tr - tl + 1) return st[q].dat;
  if (st[q].dat == tr - tl + 1) return st[p].dat;
  if (!p || !q) return 0;
  int mid = (tl + tr) >> 1;
  return Merge(st[p].lc, st[q].lc, tl, mid) +
         Merge(st[p].rc, st[q].rc, mid + 1, tr);
}
```

看上去很对，然后交上去就会发现 [TLE 了 26 个点](https://atcoder.jp/contests/abc365/submissions/56299459)。

考虑这样一种情况：

```plaintext
A: 1 3 5 7 9 ... m-1
B:  2 4 6 8  10 ...  m
```

每次询问都要递归到叶子节点，一次询问复杂度就是 $O(m\log m)$ 的。

但是这样的 $(A,B)$ 对不会很多,因为总的进出次数是有限的，相错的两个人会导致其他进出大量减小,而使得不会有其他很大的相错情况出现，所以只需要加一个储存每次询问答案的标记，防止重复询问同一组相错很长的两人。均摊复杂度不会很大。

完整代码见[最终提交记录](https://atcoder.jp/contests/abc365/submissions/56323941)，用时 $2500\text{ ms}$。

---

## 作者：zrl123456 (赞：2)

[[ABC365G] AtCoder Office](https://www.luogu.com.cn/problem/AT_abc365_g)  

题目考察：根号分治，前缀和。  
题目简述：  
有 $n$ 个人，$m$ 次操作，第 $i$ 次操作发生第 $t_i$ 秒，若第 $p_i$ 个人在办公室里，则他出去；否则他进去。然后有 $q$ 次询问，第 $i$ 次询问给出 $x_i,y_i$，输出有多长时间第 $x_i$ 和第 $y_i$ 个人都在办公室里。  
数据范围：  
- $1\le n,m,q\le 2\times 10^5$
- $\forall i\in[1,n],1\le t_i\le 10^9,1\le p_i\le n$
- $\forall i\in[2,n],t_{i-1}<t_i$
- $\displaystyle\forall i\in[1,n],2|\sum_{j=1}^m[p_j=i]$
- $1\le a_i,b_i\le n$
---
考虑根号分治。  

对于出现次数大于等于 $B$ 的人，我们进行预处理，我们将时间节点拿出来一个一个进行处理。如果这个人在房间里，那么我们给前缀和加上前一个点到现在所过的时间。然后对于剩下的人前缀和求和即可。  
对于每次询问，若两个人的进入次数都不比 $B$ 大，直接暴力两个指针统计即可。  
这样时间复杂度为 $\Theta(\frac{m^2+nm}{B}+qB)$，$B$ 取 $\sqrt m$ 时时间复杂度为 $\Theta((n+m+q)\sqrt m)$。  

[代码](https://atcoder.jp/contests/abc365/submissions/56385927)

---

## 作者：AfterFullStop (赞：2)

这里有个不是根号分治做法的，但复杂度却是根号的（$O(m \sqrt{q} \log m + q \log q)$），十分神奇。

思路简单，预处理出每个人在办公室的时间段和每个人不在办公室的时间段，对于每个询问，去重之后枚举时间段数少的那个的所有不在办公室的时间段，然后在另一个上二分这个时间段，把他占掉的全扣掉。我们设（去重后）第 $i$ 次询问中段数较少的人的段数为 $B_i$，则最终复杂度为 $O(\sum\limits^{q}_{i=1}B_i\log m)$，我们只需证明这玩意这玩意是 $O(m \sqrt{q} \log m)$ 的即可。

首先想要最大化 $\sum\limits^{q}_{i=1}B_i$，自然需要以时间段更多的人作为询问时时间段更少的人。设第 $i$ 人段数为 $A_i$，显然可以列出 $\sum\limits^{n}_{i=1}A_i=\dfrac{m}{2}$。将 $A_i$ 排好序。排序后为使其最大只会用到后 $\sqrt{q}$ 个，因此 $n$ 一定在小于等于 $\sqrt{q}$ 时取最优（如果不是那剩下那些段随便拉一些到后面这些段都比放前面更赚）。对于 $n \lt \sqrt{q}$ 的，我们给他前面补上 0 ，这样就满足 $n=\sqrt{q}$ 了。

接着我们证明 $\sum\limits^{q}_{i=1}B_i$ 最大时 $\max\limits^{n}_{i=1}A_i - \min\limits^{n}_{i=1}A_i \le 1$。考虑反证，若 $\exist i \neq j, A_i-A_j \ge 2$，我们可以另 $A_i \to A_i -1, A_j \to A_j +1$，由于 $A_i \gt A_j$，$i \gt j$，故此次修改产生的贡献为 $((A_j+1) \times (n-j)+(A_i-1) \times (n-i)) - (A_j \times (n-j)+A_i \times (n-i)) \gt 0$，因此一定可以更优，与条件矛盾。

那他既然最后段数是 $O(\sqrt{q})$，每一个人的段数就应当是 $\dfrac{m}{\sqrt{q}}$，然后总的就应当是 $O(\sum\limits^{n}_{i=1}(n-i) \times \dfrac{m}{\sqrt{q}})=O(m \sqrt{q})$。乘上 $\log$ 之后就是 $O(m \sqrt{q} \log m)$。

事实上这个上界可以取到，考虑令 $n=300,m=300\times 300 \times 2,q=300 \times 299$，后面每两个数之间都问一次，这样就取到了（最后 $\sum\limits^{q}_{i=1}B_i$ 大概是 $2 \times 10^7$）。然而这却出乎意料的快，本地只跑了 2s，AT 上只跑了 1.5s，真没想到现在二分这么厉害。

注：复杂度里面的 $q \log q$ 是存询问结果的 map 带来的。

[代码放一下吧](https://atcoder.jp/contests/abc365/submissions/56304224)。

---

## 作者：封禁用户 (赞：1)

天哪，这题的想法太巧妙了。

首先，我们称一个人进入办公室的连续的时间为一块。那么所有人的块数之和即为 $\frac{M}{2}$。设 $K=\sqrt{\frac{M}{2}}$，接下来进行分块决策。

对于一个询问 $a,b$，不妨设 $a$ 的块数 $R_a$ 不高于 $b$ 的块数 $R_b$。

对于所有的 $i$，如果 $R_i\ge K$，那么我们计算每个离散化后的时间之前 $i$ 总共在办公室里面待了多长时间，这样如果 $R_b\ge K$，我们就可以直接在 $R_a$ 每一块的开始和结束的时间点上前缀和作差然后算总和，时间复杂度 $O(R_a)$。

如果 $R_b<K$，那么我们拿指针扫出重叠的时间总长即可。时间复杂度 $O(R_a+R_b)$，极限为 $O(K)$。

你现在肯定在想：$R_b\ge T$ 时 $O(\sum R_a)$ 复杂度过不了这题啊。但是，仔细想想，如果你加上一个记忆化步骤，如果这次的 $a,b$ 在先前被询问过，就直接拿那次询问的答案，那么你就可以通过这道题目。

为什么呢？

如果加上记忆化，那么时间**达到最大**的的时候询问必然只有 $O(\sqrt{Q_0})$ 量级个不同的 $a$，其中 $Q_0$ 为 $R_b\ge K$ 的询问数量。因为 $R_i$ 最大的 $i$ 为了不会被作为 $a$ 查询，而 $R_i$ 次大的 $i$ **不被记忆化省下时间**要与最大的 $i$ 被作为 $a$ 查恰好 $1$ 次，第三大的 $i$ 要与前两大的 $i$ 被查恰好 $2$ 次······$R_i$ 第 $k$ 大的 $i$ 要与最大的 $k-1$ 个 $i$ 被查恰好 $k-1$ 次，除非询问次数耗尽。

继续考虑 $R_a$。容易发现，这时为了使时间达到最高，你需要使被作为 $a$ 查询过的所有值块数均摊（因为 $R$ 越小被查的次数越多），这时满足 $R_b\ge K$ 的这一类的总时间复杂度为 $O(Q_0\times \frac{M}{2\sqrt{Q_0}})=O(M\sqrt{Q_0})$。

总时间复杂度 $O(M\sqrt{Q}+Q\sqrt{M}+Q\log Q)$。

什么，你问后面那个 $O(q\log q)$ 是啥？我会告诉你：这是记忆化的时间。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

int n,m,q,T,timlen[200005],kid[200005],edtot[200005],pres[320][200005],pt;
vector<pair<int,int> >mp[200005];map<pair<int,int>,int>rememb;

int main(){
	cin.tie(0);ios::sync_with_stdio(0);
	cin>>n>>m;T=sqrt(m/2);
	for(int i=1;i<=m;i++){
		int xx,tim;cin>>tim>>xx;
		timlen[i]=tim;
		if(edtot[xx]%2==0){
			mp[xx].push_back(make_pair(i,0));edtot[xx]++;
		}
		else{
			mp[xx][mp[xx].size()-1].second=i;edtot[xx]++;
		}
	}
	for(int i=1;i<=n;i++){
		if(mp[i].size()>T){
			kid[i]=++pt;
			for(int o=0;o<mp[i].size();o++){
				for(int j=mp[i][o].first+1;j<=mp[i][o].second;j++){
					pres[kid[i]][j]=timlen[j]-timlen[j-1];
				}
			}
			for(int j=1;j<=m;j++)pres[kid[i]][j]+=pres[kid[i]][j-1];
		}
	}
	cin>>q;
	while(q--){
		int xx,yy;cin>>xx>>yy;
		if(mp[xx].size()>mp[yy].size())swap(xx,yy);
		if(rememb.find(make_pair(xx,yy))!=rememb.end()){
			cout<<rememb[make_pair(xx,yy)]<<'\n';continue;
		}
		if(mp[yy].size()<=T){
			int ans=0;
			for(int o=0,oo=0;o<mp[xx].size();o++){
				while(oo<mp[yy].size()&&mp[yy][oo].first<mp[xx][o].second){
					if(mp[yy][oo].second>mp[xx][o].first){
						ans+=timlen[min(mp[xx][o].second,mp[yy][oo].second)]-timlen[max(mp[xx][o].first,mp[yy][oo].first)];
					}
					if(mp[yy][oo].second<=mp[xx][o].second)oo++;
					else break;
				}
				if(oo==mp[yy].size())break;
			}
			cout<<(rememb[make_pair(xx,yy)]=ans)<<'\n';
		}
		else{
			int ans=0;
			for(int o=0;o<mp[xx].size();o++){
				ans+=pres[kid[yy]][mp[xx][o].second]-pres[kid[yy]][mp[xx][o].first];
			}
			cout<<(rememb[make_pair(xx,yy)]=ans)<<'\n';
		}
	}
	return 0;
}
```

---

## 作者：Leo11 (赞：1)

### 题目大意

给定 $M$ 次操作，每次给定 $T_i$ 与 $P_i$，表示在时间 $T_i$ 时，若编号为 $P_i$ 的人未在集合中，则将其加入，否则将其弹出。

有 $Q$ 次查询，询问 $A_i$ 与 $B_i$ 一起在集合中的时间是多少。

### 解题思路

首先，本题的 $T_i$ 非常大，我们就无法使用数组储存。同时，$A_i$ 与 $B_i$ 同时在集合中的时间也有可能非常大，所以纯暴力做法会超时。

考虑**根号分治**。我们设定一个 $x$，表示一个分治的分水岭，而根号分治的思想则就是设定一个分水岭，然后分别处理答案。而我们对于操作次数大于 $x$ 的人维护一个操作次数的前缀和，也记录下其他所有大于操作次数大于 $x$ 的人的答案。

想到这里，你会不会觉得会爆空间呢？其实并不会。我们的 $x$ 可以取任何值，但是对于这一道题中，大于 $x$ 的维护答案，其余的~~低级算法~~暴力求解。若 $x$ 太大，暴力会超时；若 $x$ 太小，空间要爆炸。那么 $x$ 究竟该取什么呢？~~你猜它为什么名字里带个根号~~因为 $\sqrt{M}\times\sqrt{M}$ 刚好等于 $M$ ，并且若将 $x$ 取 $\sqrt{M}$，那么暴力复杂度就是 $O(\sqrt{M})$，维护的复杂度为 $O((N+M)\sqrt{M})$，真乃高级算法！实际上，$x$ 不一定取根号，有的时候取一个 $M^{\frac{2}{3}}$ 也很快。主要还是看数据。

---

## 作者：Neil_Qian (赞：1)

# [ABC365G] AtCoder Office 题解

## 题外话

先介绍一个看起来没什么用的技巧：对于所有询问，计算过的记录下来不再计算。笔者曾经用这个套路水掉了百度之星的一道题。不过翻不到提交记录了。

## 解决方案

设 $n,m,q$ 同阶。

注意到 $n$ 在 $10^5$ 而且时限很长，猜测时间复杂度在 $O(n\sqrt n)$ 左右。首先看如何计算一组询问，存储每个人的时间段，计算前缀和，不难发现这是一条折线，于是只记录端点即可计算区间和。选择一个人，在另一个人的折线上查找。时间复杂度视实现而定，笔者使用 $O(x\log y)$ 的复杂度，其中 $x,y$ 为两个人的折线端点数量。

接下来平衡复杂度。如果两个人有一个人的端点数量在 $O(\sqrt n)$ 以内，显然时间复杂度为 $O(\sqrt n\log n)$。如果两个端点数量都超过 $O(\sqrt n)$，首先这样的端点数不超过 $O(\sqrt n)$，于是这部分总时间复杂度为 $O(\sqrt n\log n)$，对于每个人单独考虑即可证明。

于是时间复杂度为 $O(n\sqrt n\log n)$，远远跑不满，轻松通过。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;using ll=long long;using P=pair<int,int>;
const int N=2e5+2;int n,m,Q,x,y,last;vector<P> v[N];map<P,int> ans;
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0),cin>>n>>m;
	for(int i=1;i<=n;i++)v[i].emplace_back(P{0,0});
	while(m--){
		cin>>y>>x;
		if(!(v[x].size()%2))last=y-(*(--v[x].end())).first+(*(--v[x].end())).second,
			v[x].emplace_back(P{y,last});
		else last=(*(--v[x].end())).second,v[x].emplace_back(P{y,last});
	}
	for(int i=1;i<=n;i++)last=(*(--v[i].end())).second,v[i].emplace_back(P{1e9,last});
	cin>>Q;
	while(Q--){
		cin>>x>>y;
		if(v[x].size()>v[y].size()||(v[x].size()==v[y].size()&&x>y))swap(x,y);
		if(ans.count(P{x,y})){cout<<ans[P{x,y}]<<"\n";continue;}
		int res=0,t1,t2,sl,sr;
		for(int i=1;i+1<(int)v[x].size();i++){
			auto t=lower_bound(v[y].begin(),v[y].end(),P{v[x][i].first,0});
			t2=(*t).second,t1=(*(--t)).second,sl=((*t).second+(t1!=t2?v[x][i].first-(*t).first:0));
			i++;t=lower_bound(v[y].begin(),v[y].end(),P{v[x][i].first,0});
			t2=(*t).second,t1=(*(--t)).second,sr=((*t).second+(t1!=t2?v[x][i].first-(*t).first:0));
			res+=sr-sl;
		}
		cout<<(ans[P{x,y}]=res)<<"\n";
	}
	return 0;
}
```

---

## 作者：luogu_gza (赞：1)

不难有双指针的 $O(nq)$ 暴力。

然后考虑一个记忆化，如果 $(A,B)$ 已经被询问过了就直接输出之前计算的答案。

然后我们发现这个东西跑的飞快。我们来分析一下这个做法。

卡这个暴力的方式明显是构造一些长度较大的区间然后反复询问这些区间，但是记忆化发现我们只能问一次。

假设我们构造了 $x$ 个区间，那么次数大概是（可能有一点常数差距） $x\min(10^5,(\frac{n^2}{x^2}))$。

可以发现在 $x=\sqrt n$ 的情况下次数最大，复杂度为 $O(n\sqrt n)$。

代码简单，不放。

---

## 作者：IvanZhang2009 (赞：0)

这里是一个愚蠢的分块做法，常数大，空间还大。相信智慧的你谷网友一定会踩爆这个做法。

看上去就不好 polylog，那就考虑根号。这里自然地想到对 $m$ 个事件分块，考虑长度为 $B$ 的分一块，块内有哪些可以暴力的东西呢？必然与块长相关，于是考虑到单个块内有修改的东西只有块长个（$\frac mB$），那么对于两个都修改的点，我们可以直接用块长的平方的代价预处理出两个点在这个块内的相交部分大小。预处理的空间显然是 $B\cdot(\frac mB)^2=\frac{m^2}B$ 的。

考虑询问。遍历每个块。如果两个点在这个块中都没有改变，则调用这块开始时的信息，检验两点是否都为 $1$，累加答案；如果两个点都修改过，调用预处理信息；如果恰有一个点修改过，则调用另一个点是否修改过的信息，和这个改过的点的预处理信息。

考虑预处理。每次暴力更新的复杂度是错的，高达 $\frac{m^3}{B^2}$。考虑对每个 pair 打个时间戳，每次等一个点更新之后，就更新所有和这个点有关的 pair 的时间戳和答案。在结尾的时候再遍历一遍所有的 pair。时间复杂度改良为 $B((\frac mB)^2)=\frac{m^2}B$，可以接受。

预处理复杂度 $O(\frac{m^2}{B})$，查询复杂度 $O(B)$，平衡复杂度取 $B=\sqrt m$，得到 $O(m\sqrt m)$ 做法。常数大，略微卡常。注意空间开销，因为空间复杂度也是大常数的 $O(mB)$。实测查询常数略大，取 $B=800$，最后 2.7s，800MB 过了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define pii         pair<int,int>
#define all(v)      v.begin(),v.end()
#define pb          push_back
#define REP(i,b,e)  for(int i=(b);i<(int)(e);++i)
#define over(x)     {cout<<(x)<<endl;return;}
#define deal(v)     sort(all(v));v.erase(unique(v.begin(),v.end()),v.end())
int n,m,B=800;
int a[200005],b[200005];
bitset<200005>occ[800];
vector<int>T[800];
signed res[250][800][800],res2[800][800];
int lst[800][800];
int Id[800][200005];
void work(int l,int r,int id,int lstt){
	REP(i,0,m)Id[id][i]=-1;
	vector<int>t,L;
	REP(i,l,r+1)t.pb(b[i]),L.pb(lstt);
	deal(t);
	REP(i,0,t.size())Id[id][t[i]]=i;
	bitset<200005>vis=occ[id];
	int N=t.size();
	REP(i,0,N){
		REP(j,i+1,N)lst[i][j]=lstt,res[id][i][j]=0;
	}
	REP(i,l,r+1){
		int x=Id[id][b[i]];
		if(vis[b[i]])res2[id][x]+=a[i]-L[x];
		L[x]=a[i];
		REP(j,0,x){
			if(vis[t[j]]&&vis[b[i]])res[id][j][x]+=a[i]-lst[j][x];
			lst[j][x]=a[i];
		}
		REP(j,x+1,N){
			if(vis[t[j]]&&vis[b[i]])res[id][x][j]+=a[i]-lst[x][j];
			lst[x][j]=a[i];
		}
		vis[b[i]]=1-vis[b[i]];
	}
	REP(i,0,N){
		if(vis[t[i]])res2[id][i]+=a[r]-L[i];
		REP(j,i+1,N)if(vis[t[i]]&&vis[t[j]]){
			res[id][i][j]+=a[r]-lst[i][j];
		}
	}
}
void Main() {
	cin>>m>>n;
	REP(i,0,n)cin>>a[i]>>b[i],--b[i];
	bitset<200005>vis;
	int num=0;
	REP(i,0,n){
		if(i%B==0)occ[i/B]=vis,++num;
		vis[b[i]]=1-vis[b[i]];
	}
	occ[num]=vis;
	for(int i=0;i<n;i+=B){
		work(i,min(n-1,i+B-1),i/B,(i? a[i-1]:0));
	}
	int q;
	cin>>q;
	while(q--){
		int x,y;
		cin>>x>>y;
		--x,--y;
		int ans=0;
		for(int i=0;i*B<n;++i){
			int o1=Id[i][x]!=-1;
			int o2=Id[i][y]!=-1;
			if(!o1&&!o2){
				if(occ[i+1][x]&&occ[i+1][y])ans+=a[min(n-1,(i+1)*B-1)]-a[i*B-1];
			}else if(o1&&o2){
				o1=Id[i][x];o2=Id[i][y];
				if(o1>o2)swap(o1,o2);
				ans+=res[i][o1][o2];
			}else{
				if(o2)swap(x,y),swap(o1,o2);
				o1=Id[i][x];
				if(occ[i+1][y])ans+=res2[i][o1];
			}
		}
		cout<<ans<<endl;
	}
}
```

---

## 作者：mango2011 (赞：0)

赛时做法，一点也不优美，不过很容易想。

我们可以维护出每一个人在办公室内的时间段。

在一组询问中，我们有下面的暴力方法：

假设这两个人分别有 $x,y$ 段时间在办公室，不妨设 $x\le y$。

显然，我们可以枚举 $x$ 中的时间段，在 $y$ 中二分出对应的端点，配合上前缀和预处理以及边界的处理就可以做到总复杂度 $O(x\log y)$。

但是，如果说每一次询问中的两个人都有很多个时间段呆在办公室里，那么我们的复杂度就会假。

怎么办呢？事实上，我们可以记录下已经算过的答案，如果再一次询问的话直接调用就行了。这样子，我们的复杂度就真了。

为什么上面的做法复杂度正确呢？假设有一个值 $B$（事实上是不存在的），那么在办公室时间段数 $\ge B$ 的人数最多为 $\frac{n}{B}$，最多只能组成 $O(\frac{M^2}{B^2})$ 次本质不同的询问，单次处理复杂度为 $O(B\log B)$；对于 $x\le B$ 的询问直接 $O(B\log B)$ 处理就行了。

可以算得总复杂度是 $O(Q B\log B+\frac{M^2}{B}\log B)$，取一个 $B=\sqrt{M}$ 就可以发现复杂度不超过 $O(M\sqrt{M}\log \sqrt{M})$（$M,Q$ 同阶），可以通过。

上面的 $B$ 仅供读者理解，如果取得更加精细可以发现复杂度其实不到 $O(M\sqrt{M}\log \sqrt{M})$。

[提交记录](https://atcoder.jp/contests/abc365/submissions/56295299)

---

## 作者：Genius_Star (赞：0)

### 思路：

考虑枚举其中一个人的工作区间，然后通过二分求出这个区间内两人同时在的时间段。

按照启发式合并的思路，我们每次选择工作区间较少的那个工人枚举即可。

设 $N,M,Q$ 同阶，时间复杂度均摊为 $O(N \sqrt{N} \log N)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#define Add(x,y) (x+y>=mod)?(x+y-mod):(x+y)
#define lowbit(x) x&(-x)
#define pi pair<ll,ll>
#define pii pair<ll,pair<ll,ll>>
#define iip pair<pair<ll,ll>,ll>
#define ppii pair<pair<ll,ll>,pair<ll,ll>>
#define fi first
#define se second
#define full(l,r,x) for(auto it=l;it!=r;it++) (*it)=x
#define Full(a) memset(a,0,sizeof(a))
#define open(s1,s2) freopen(s1,"r",stdin),freopen(s2,"w",stdout);
using namespace std;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const ll N=2e5+10;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll n,m,q,x,y,sum,ans;
ll a[N],h[N];
map<pi,pi> F;
vector<ll> E[N],S[N];
vector<pi> G[N];
ll get(ll x,ll l,ll r){
	if(l>r)
	  return 0;
	if(l<=0)
	  return S[x][r];
	return S[x][r]-S[x][l-1];
}
bool End;
int main(){
	n=read(),m=read();
	while(m--){
		x=read(),y=read();
		if(a[y]){
			G[y].push_back({a[y],x});
			E[y].push_back(a[y]);
			h[y]+=x-a[y];
			S[y].push_back(h[y]);
			a[y]=0;
		}
		else
		  a[y]=x;
	}
	q=read();
	while(q--){
		ans=0;
		x=read(),y=read();
		if(E[x].size()>E[y].size())
		  swap(x,y);
		if(F[{x,y}].fi){
			write(F[{x,y}].se);
			putchar('\n');
			continue;
		}
		for(int i=0;i<(ll)E[x].size();i++){
			ll l=G[x][i].fi,r=G[x][i].se;
			ll L=lower_bound(E[y].begin(),E[y].end(),l)-E[y].begin(),R=upper_bound(E[y].begin(),E[y].end(),r)-E[y].begin();
			R--;
			ans+=get(y,L,R-1);
			if(R>=0&&G[y][R].se>=l)
			  ans+=min(G[y][R].se,r)-max(G[y][R].fi,l);
			if(L>0){
				L--;
				if(L==R)
				  continue;
				if(G[y][L].se>=l)
				  ans+=min(G[y][L].se,r)-l;
			}
		}
		write(ans);
		putchar('\n');
		F[{x,y}]={1,ans};
	}
	cerr<<'\n'<<abs(&Begin-&End)/1048576<<"MB";
	return 0;
}
```

---

