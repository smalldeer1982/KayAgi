# 雇用計画

## 题目描述

JOI 社为了扩大业务而开始了新社员招募。社员有 $N$ 名候补者，编号从 $1$ 到 $N$， 每名候补者有称为评价值的一个确定整数。 评价值高于某一个值的候补者全部都将被聘用， 他们还将分为几个组别。如果 $a, b(a \lt b)$ 同时被聘用且 $c(a \le c\le b)$ 全部被聘用时，$a,b$ 进入同一组。

你要处理 $M$ 个查询，查询有以下两种：

- 评价值 $B_j$ 以上的候补者全部聘用时的组数；

- 将候补者 $C_j$ 的评价值更新为 $D_j$。

# 题解

## 作者：WAAutoMaton (赞：6)

[先宣传一下博客(逃](https://waautomaton.tk/2018/08/14/loj-2732-%E9%A2%98%E8%A7%A3/)

#### 解法
&emsp;&emsp;这题标算是1个log的树状数组，然而由于数据范围（也许）没开满，本sb选手直接写了莫队硬肛2e5，差点被卡常了。（atcoder上最慢的点970ms）  
&emsp;&emsp;考虑我们是对一个评价值询问，把这个值作为一个维度，由于有修改所以时间也作为一个维度，我们就得到了一个二维的莫队。其中评价值维度上的移动会触发一次修改，是$O(1)$的，时间上的移动完整的移动一次会触发$O(n)$次修改，所以均摊复杂度$O(1)$。所以分块时如果要按时间轴分块，必须按该时间的修改次数的前缀和分块，而不是按时间分块。

#### 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

template <size_t _I_Buffer_Size = 1 << 23, size_t _O_Buffer_Size = 1 << 23>
struct IO_Tp
{
    //这是读入优化板子，为了阅读体验此部分内容省略。
};
 IO_Tp<1<<25,1<<25> IO;
const int maxn = 200000;
struct Change
{
    int p, before, after;
} ch[maxn + 10];
int a[maxn + 10];
struct Query
{
    int l, r, id;
} q[maxn + 10];
int qcnt, ccnt;
int tong[3 * maxn + 10], tcnt;
vector<int> pl[3 * maxn + 10];
int n, m;
int nans;
int l = ccnt, r = tcnt;
bool b[maxn + 10];
void change(int p, int k)
{
    int cnt = 0;
    if (b[p - 1])
        ++cnt;
    if (b[p + 1])
        ++cnt;
    if (k == 1) {
        if (cnt == 0)
            ++nans;
        else if (cnt == 2)
            --nans;
		massert(!b[p]);
        b[p] = true;
    } else {
        if (cnt == 0)
            --nans;
        else if (cnt == 2)
            ++nans;
		massert(b[p]);
        b[p] = false;
    }
}
void movl(int l, int k)
{
    if (ch[l].before <= r && ch[l].after > r)
        change(ch[l].p, k);
    else if (ch[l].before > r && ch[l].after <= r)
        change(ch[l].p, k ^ 1);
    if (k == 1) {
        a[ch[l].p] = ch[l].after;
    } else {
        a[ch[l].p] = ch[l].before;
    }
}
void movr(int r, int k)
{
    for (auto i : pl[r]) {
        if (a[i] == r)
            change(i, k);
    }
}
int ans[maxn + 10];
int sum[maxn+10];
int main()
{
    iopen();
    IO >> n >> m;
    for (int i = 1; i <= n; ++i) {
        IO >> a[i];
        tong[++tcnt] = a[i];
    }
    for (int i = 1; i <= m; ++i) {
        int op;
        IO >> op;
        if (op == 1) {
            int b;
            IO >> b;
            --b;
            tong[++tcnt] = b;
            ++qcnt;
            q[qcnt] = { ccnt, b, qcnt };
        } else {
            int p, after;
            IO >> p >> after;
            ch[++ccnt] = { p, a[p], after };
            tong[++tcnt] = after;
            a[p] = after;
        }
    }
    sort(tong + 1, tong + 1 + tcnt);
    tcnt = unique(tong + 1, tong + 1 + tcnt) - tong - 1;
    for (int i = 1; i <= n; ++i) {
        a[i] = lower_bound(tong + 1, tong + 1 + tcnt, a[i]) - tong;
    }
    for (int i = 1; i <= ccnt; ++i) {
        ch[i].before = lower_bound(tong + 1, tong + 1 + tcnt, ch[i].before) - tong;
        ch[i].after = lower_bound(tong + 1, tong + 1 + tcnt, ch[i].after) - tong;
    }
    for (int i = 1; i <= qcnt; ++i) {
        q[i].r = lower_bound(tong + 1, tong + 1 + tcnt, q[i].r) - tong;
    }
    for (int i = 1; i <= n; ++i) {
        pl[a[i]].push_back(i);
    }
    for (int i = 1; i <= ccnt; ++i) {
        pl[ch[i].before].push_back(ch[i].p);
    }
	for(int i=1; i<=tcnt; ++i) {
		sort(pl[i].begin(),pl[i].end());
		int t=unique(pl[i].begin(),pl[i].end())-pl[i].begin();
		while(pl[i].size()>t) pl[i].pop_back();
		sum[i]=sum[i-1]+t;
	}
    int S = sqrt(sum[tcnt]);
   sort(q + 1, q + 1 + qcnt, [S](const Query &a, const Query &b) {
        if (sum[a.r] / S == sum[b.r] / S)
            return (sum[a.r]/S %2 ==1)?a.l < b.l:a.l>b.l;
        return sum[a.r] / S < sum[b.r] / S;
    });
    l = ccnt;
    r = 0;
    memset(b, true, sizeof(b));
    b[0] = b[n + 1] = false;
    nans = 1;
    for (int i = 1; i <= qcnt; ++i) {
        while (l < q[i].l)
            movl(++l, 1);
        while (l > q[i].l)
            movl(l--, 0);
        while (r < q[i].r)
            movr(++r, 0);
        while (r > q[i].r)
            movr(r--, 1);
        ans[q[i].id] = nans;
    }
    for (int i = 1; i <= qcnt; ++i) {
        IO << ans[i] << '\n';
    }
    return 0;
}


```


---

## 作者：LEWISAK (赞：1)

教练把这题放到了[模拟赛](https://www.cnblogs.com/lewisak/p/18844652)中并且加了部分分，我觉得有点启发作用于是把部分分也带上了。

## 10pts

调小了数据范围，$n^2$ 暴力维护即可。

## 66pts

这一档只有查询，可以把查询离线一下排序后把只统计 $\ge b$ 的转换为了把 $< b$ 的删掉，排序后就不会加回来了，然后再把初始的人也排序一下，使用双指针和一个很聪明的技巧可线性解决，具体见代码。

```cpp
//好吧其实排序才是瓶颈
sort(q+1,q+1+m,[](s x,s y){return x.v<y.v;});//查询排序
sort(c+1,c+1+n,[](s x,s y){return x.v<y.v;});//初始的人排序
int cnt=1,ant=1;
//vis[i] 表示 i 是所处组的几个端点，即：
// vis[i]=1 表示 i 是组端点
// vis[i]=1 表示 i 所处组只有 i 一个点
vis[1]=vis[n]=1;
for(int i=1;i<=m;i++){
	while(c[cnt].v<q[i].v&&cnt<=n){//便利要删的点
		ant+=1-vis[c[cnt].id];//不是端点多一组，是端点不变，独自成组少一组
		vis[c[cnt].id+1]++;//如果不是端点那左右两边就成了端点，如果是端点那会让左/右边继承，如果独自成组那什么也不会发生
		vis[c[cnt].id-1]++;//这个是不会加到别的组的因为组与组直接都会至少隔一位
		cnt++;
	}
	ans[q[i].id]=ant;
}
```
赛时能想到这档感觉 OI 没白学（
## 100pts

如果按照第二档往下想显然是带修莫队的样子，只需再添加时间一位，如果你对这个做法感兴趣可以看[这里](https://www.luogu.com.cn/article/1qouycty)，因为懒得写所以这里就不阐述了。

教练给的官方正解是考虑每个相邻二元组 $(A_{i-1},A_i)$ 对询问的贡献是对所有 $B_j \in (A_{i-1},A_i]$ 的答案加一，于是我们只需要一个在值域 $10^9$ 的范围内实现区修单查的数据结构。

我这里选择动态开点树状数组，但 stl 自带的哈希表太慢了，遂手写，用校内 OJ 测了一下其实这题的很多这个做法的题解都被卡常了（）

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace kong{bool st;}
namespace easycome{
int read(){
	int aaa(0);
	char ch;
	while((ch=getchar())<48);
	do{
		aaa=(aaa<<1)+(aaa<<3)+(ch^48);
	}while((ch=getchar())>47);
	return aaa;
}
const int mod=10000019;
int n,m,a[200020],ci;
struct hash_map{
	struct{
		int v,nxt;
		long long u;
	}e[mod*2];
	int head[mod],cnt;
	int hs(long long x){
		return(x%mod+mod)%mod;
	};
	int &operator[](long long u){
		int hu=hs(u);
		for(int i=head[hu];i;i=e[i].nxt){
			if(e[i].u==u){
				return e[i].v;
				continue;
			}
		};
		e[++cnt]={0,head[hu],u};
		head[hu]=cnt;
		return e[cnt].v;
	}
}tr;
#define lowbit(x) (x&(-x))
void add(int l,int r,int y){
	if(l>r){
		return;
	}
	while(l<1e9){
		tr[l]+=y;
		l+=lowbit(l);
	}
	r++;
	while(r<1e9){
		tr[r]-=y;
		r+=lowbit(r);
	}
	return;
}
int query(int x){
	int aaa=0;
	while(x){
		aaa+=tr[x];
		x-=lowbit(x);
	}
	return aaa;
}
string main(){
	n=read();m=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		add(a[i-1]+1,a[i],1);
	}
	while(m--){
		int opt,x;
		opt=read();x=read();
		if(opt==1){
			cout<<query(x)<<'\n';
		}
		else{
			add(a[x-1]+1,a[x],-1);
			add(a[x]+1,a[x+1],-1);
			a[x]=read();
			add(a[x-1]+1,a[x],1);
			add(a[x]+1,a[x+1],1);
		}
	}
	return "easygo,little high,little low";
}
}
namespace kong{bool ed;double MB(){return (&st-&ed)/1048576.0;}}
signed main(){
	cerr<<easycome::main();
}~~~~
```

---

## 作者：rainygame (赞：1)

本题题解区甚至没有 $\log$ 复杂度的做法。

对于每个组，考虑只通过组的第一个数统计贡献。当且仅当 $a_{i-1} < B_j$ 且 $a_i \ge B_j$ 时，$a_i$ 是一个组的第一个数。特殊地，$a_0=0$。这样就只需要修改两组 $(a_{i-1},a_i)$ 即可和询问连接。单点修改是简单的。

但是这样仍然不好维护，注意到我们只需要回复好每个询问就可以了，并不需要真的维护数组，所以考虑反过来，统计每个 $(a_{i-1},a_i)$ 对询问的贡献，显然是对 $B_j \in (a_{i-1},a_i]$ 的询问贡献，所以题目变成了区间修改，单点查询，可以用树状数组维护。

但是我很懒，就只写了一个动态开点树状数组维护，时间和空间复杂度均为 $O((N+M) \log^2 k)$，其中 $k$ 为值域。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define MAXN 200001
#define lowbit(x) (x & -x)

int uread(){
    int x(0);
    char ch;
    while ((ch = getchar()) < 48);
    do{
        x = (x << 1) + (x << 3) + (ch ^ 48);
    }while ((ch = getchar())> 47);
    return x;
}

int n, q, opt, x, y;
int a[MAXN];

unordered_map<int, int> c;
void add(int x, int k){
    while (x <= 1e9){
        c[x] += k;
        x += lowbit(x);
    }
}
void add(int l, int r, int k){
    if (l > r) return;
    add(l, k);
    add(r+1, -k);
}

int query(int x){
    int res(0);
    while (x){
        res += c[x];
        x -= lowbit(x);
    }
    return res;
}

signed main(){
    n = uread();
    q = uread();
    for (int i(1); i<=n; ++i) add(a[i-1]+1, a[i] = uread(), 1);

    while (q--){
        opt = uread();
        x = uread();
        if (opt == 1) cout << query(x) << '\n';
        else{
            add(a[x-1]+1, a[x], -1);
            if (x <= n) add(a[x]+1, a[x+1], -1);
            a[x] = uread();
            add(a[x-1]+1, a[x], 1);
            if (x <= n) add(a[x]+1, a[x+1], 1);
        }
    }

    return 0;
}
```


---

## 作者：User_Unauthorized (赞：1)

## 题面
JOI 社为了扩大业务而开始了新社员招募。社员有 $N$ 名候补者，编号从 $1$ 到 $N$，每名候补者有称为评价值的一个确定整数。评价值高于某一个值的候补者全部都将被聘用，他们还将分为几个组别。如果 $a, b(a \lt b)$ 同时被聘用且 $c(a \le c\le b)$ 全部被聘用时，$a,b$ 进入同一组。

你要处理 $M$ 个查询，查询有以下两种：

- 评价值 $B_j$ 以上的候补者全部聘用时的组数；

- 将候补者 $C_j$ 的评价值更新为 $D_j$。

## 题解
**本题存在根号复杂度做法。**

思考过程相对朴素，考虑将询问转化为一个二元组 $\left(time, x\right)$ 表示在第 $time$ 个修改操作后询问评价值 $x$ 的组数。

考虑莫队，以 $time$ 所在块编号为第一关键字，$x$ 的大小为第二关键字进行排序。答案的处理则可以维护一个 $\text{bitset}$，每次修改时判断两侧点的状态来决定对答案贡献的影响。

注意一点，排序只能按上文所说的方法进行排序，因为单次修改的复杂度为严格的 $\mathcal{O}(1)$，而 $x$ 这一边界移动的复杂度为**均摊** $\mathcal{O}(1)$，如果颠倒排序顺序则无法保证复杂度。关于$x$ 这一边界移动的复杂度为均摊 $\mathcal{O}(1)$ 的证明可以考虑将 $x$ 从最小值移动到最大值每个候补者状态至多更新一次。

该种做法如果想在 $\text{LOJ}$ 上通过（应该）需要精湛的卡常技巧。~~笔者秉持着人傻常数大的人生理念成功被卡常。~~

## Code

```cpp
#include <bits/stdc++.h>

typedef int valueType;
typedef std::vector<valueType> ValueVector;
typedef std::set<valueType> ValueSet;
typedef std::vector<ValueSet> SetVector;
typedef std::vector<bool> bitset;

constexpr valueType MAXN = 2e5 + 5;

class Recorder {
private:
    valueType N, ans;
    bitset data;

public:
    explicit Recorder(valueType n) : N(n), ans(0), data(n + 1, false) {}

    void set(valueType i) {
        data[i] = true;

        if (i > 1 && data[i - 1] && i < N && data[i + 1])
            --ans;
        else if ((i == 1 || !data[i - 1]) && (i == N || !data[i + 1]))
            ++ans;
    }

    void reset(valueType i) {
        data[i] = false;

        if (i > 1 && data[i - 1] && i < N && data[i + 1])
            ++ans;
        else if ((i == 1 || !data[i - 1]) && (i == N || !data[i + 1]))
            --ans;
    }

    valueType get() const {
        return ans;
    }

    void set(ValueSet const &pos) {
        for (auto const &iter: pos)
            set(iter);
    }

    void reset(ValueSet const &pos) {
        for (auto const &iter: pos)
            reset(iter);
    }
};

std::array<valueType, MAXN> belong;

struct Modify {
    valueType pos, pre, to;

    Modify() = default;

    Modify(valueType p, valueType pre, valueType to) : pos(p), pre(pre), to(to) {}
};

struct Query {
    valueType time, key, id;

    Query() = default;

    Query(valueType t, valueType k, valueType i) : time(t), key(k), id(i) {}

    bool operator<(Query const &other) const {
        if (belong[time] != belong[other.time])
            return belong[time] > belong[other.time];

        if (belong[time] & 1)
            return key > other.key;
        else
            return key < other.key;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    valueType N, M;

    std::cin >> N >> M;

    valueType const Block = std::ceil(std::pow(M, 0.5));

    for (valueType i = 1; i <= M; ++i)
        belong[i] = (i - 1) / Block + 1;

    ValueVector source(N + 1), bucket({0, INT_MIN, INT_MAX});

    bucket.reserve(N + M + 3);

    for (valueType i = 1; i <= N; ++i) {
        std::cin >> source[i];

        bucket.push_back(source[i]);
    }

    std::vector<Modify> modify(1, Modify(0, INT_MIN, INT_MIN));
    std::vector<Query> query;

    modify.reserve(M);
    query.reserve(M);

    for (valueType i = 1; i <= M; ++i) {
        int type;

        std::cin >> type;

        if (type == 1) {
            valueType x;

            std::cin >> x;

            query.emplace_back(modify.size() - 1, x, query.size());

            bucket.push_back(x);
        } else {
            valueType x, y;

            std::cin >> x >> y;

            modify.emplace_back(x, y, source[x]);

            source[x] = y;

            bucket.push_back(y);
        }
    }

    std::sort(bucket.begin(), bucket.end());
    bucket.erase(std::unique(bucket.begin(), bucket.end()), bucket.end());

    auto const S = (valueType) bucket.size() - 1;

    SetVector pos(S + 1);

    for (valueType i = 1; i <= N; ++i) {
        source[i] = (valueType) std::distance(bucket.begin(),
                                              std::lower_bound(bucket.begin(), bucket.end(), source[i]));

        pos[source[i]].insert(i);
    }

    for (auto &iter: modify) {
        iter.pre = (valueType) std::distance(bucket.begin(),
                                             std::lower_bound(bucket.begin(), bucket.end(), iter.pre));

        iter.to = (valueType) std::distance(bucket.begin(),
                                            std::lower_bound(bucket.begin(), bucket.end(), iter.to));
    }

    for (auto &iter: query)
        iter.key = (valueType) std::distance(bucket.begin(),
                                             std::lower_bound(bucket.begin(), bucket.end(), iter.key));

    Recorder recorder(N);

    std::sort(query.begin(), query.end());

    ValueVector ans(query.size());

    valueType nowTime = (valueType) modify.size() - 1, nowKey = S;

    for (auto const &iter: query) {
        while (nowKey > iter.key) {
            --nowKey;

            recorder.set(pos[nowKey]);
        }

        while (nowKey < iter.key) {
            recorder.reset(pos[nowKey]);

            ++nowKey;
        }

        while (nowTime < iter.time) {
            ++nowTime;

            Modify &mod = modify[nowTime];

            pos[mod.pre].erase(mod.pos);
            pos[mod.to].insert(mod.pos);

            if (mod.pre >= nowKey && mod.to < nowKey)
                recorder.reset(mod.pos);
            else if (mod.to >= nowKey && mod.pre < nowKey)
                recorder.set(mod.pos);

//            source[mod.pos] = mod.to;

            std::swap(mod.pre, mod.to);
        }

        while (nowTime > iter.time) {
            Modify &mod = modify[nowTime];

            pos[mod.pre].erase(mod.pos);
            pos[mod.to].insert(mod.pos);

            if (mod.pre >= nowKey && mod.to < nowKey)
                recorder.reset(mod.pos);
            else if (mod.to >= nowKey && mod.pre < nowKey)
                recorder.set(mod.pos);

//            source[mod.pos] = mod.to;

            std::swap(mod.pre, mod.to);

            --nowTime;
        }

        ans[iter.id] = recorder.get();
    }

    for (auto const &iter: ans)
        std::cout << iter << '\n';

    std::cout << std::flush;

    return 0;
}
```

---

## 作者：HomuraAkemi (赞：1)

令 $q=\Theta(n)$。

考虑连通块数量等于点数减去边数。

点数是好算的。对于边数，将 $(n-1)$ 个二元组 $(a_i,a_{i+1})$ 视为点，实际上就是求 2-side 矩形点数。如果你和我一样糖糖的，直接使用树套树（时空均为 $\Theta(n\log ^2 n)$）或者 CDQ 分治（$\Theta(n\log^2 n)$ 时间，$\Theta(n)$ 空间）已经可以通过，其中树套树写法需要注意空间常数。

考虑进一步优化：对于一次查询 $B$，只有 $\min(a_i,a_{i+1})\ge B$ 的点是有用的，这样就直接维护 $\min(a_i,a_{i+1})$ 就好了，不难直接做到 $\Theta(n\log n)$ 时间、$\Theta(n)$ 空间。

感谢 @gcx12021 指出做法进一步优化/qq

---

## 作者：Shunpower (赞：0)

操作分块入门经典。

-----------

原问题等价于查询此时值 $\ge B_j$ 的那些位置构成多少个极长区间，并支持单点修改。

单点修改和全局状查询，考虑操作分块。

每个询问有一个权值上的偏序限制，我们类似 [	[APIO2019] 桥梁](https://www.luogu.com.cn/problem/P5443)，把块内的修改先丢掉，这样就只剩下没有修改的点。把没有修改的点和询问的权值排序之后双指针一下就只用做动态加点，并且每个点只用加一次。

显然我们可以简单地维护动态加点时的区间数量。

然后考虑有修改的点，这部分点只有块长个。因为询问也只有块长个，所以我们可以每个询问都直接暴力地扫描这部分点，把能贡献到的给加进去。注意每个询问做完之后需要把这部分贡献撤销掉，因为我们之后还需要继续双指针。

每一块结束之后还要把修改做掉重算一下原数组。

这样做复杂度是 $\mathcal O(\frac{nq}{B}\log B+qB)$ 的，最优块长是 $B=\sqrt{q\log q}$ 得到复杂度 $\mathcal O(n\sqrt{q\log q})$，不过直接取 $B=\sqrt q$ 就可以在 4.8 秒左右在 AT 上通过。

如果两次排序都用桶排的话就单根没有 $\log$ 了。

---

