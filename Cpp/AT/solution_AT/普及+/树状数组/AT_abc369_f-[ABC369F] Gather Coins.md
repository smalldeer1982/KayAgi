# [ABC369F] Gather Coins

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc369/tasks/abc369_f

縦 $ H $ 行、横 $ W $ 列のグリッドがあります。 このグリッドの上から $ i $ 行目、左から $ j $ 列目にあるマスのことを $ (i,j) $ と表記します。

このグリッド上には $ N $ 枚のコインが落ちており、$ i $ 個目のコインはマス $ (R_i,C_i) $ を通ることで拾うことができます。

あなたの目標は、マス $ (1,1) $ から始めて下か右に $ 1 $ マス移動することを繰り返し、できるだけ多くのコインを拾いながらマス $ (H,W) $ まで行くことです。

あなたが拾うことのできるコインの枚数の最大値、およびそれを達成するための移動経路を $ 1 $ つ求めてください。

## 说明/提示

### 制約

- $ 2\leq\ H,W\ \leq\ 2\times\ 10^5 $
- $ 1\leq\ N\ \leq\ \min(HW-2,\ 2\times\ 10^5) $
- $ 1\leq\ R_i\ \leq\ H $
- $ 1\leq\ C_i\ \leq\ W $
- $ (R_i,C_i)\neq\ (1,1) $
- $ (R_i,C_i)\neq\ (H,W) $
- $ (R_i,C_i) $ は互いに相異なる
- 入力は全て整数
 
### Sample Explanation 1

!\[\](https://img.atcoder.jp/abc369/8c45374379376c75b6cfd44cb8efeaf8.png) 上図のように $ (1,1)\rightarrow\ (2,1)\rightarrow\ (2,2)\rightarrow\ (2,3)\rightarrow\ (3,3)\rightarrow\ (3,4) $ と移動することで、$ (2,1),(2,3),(3,3) $ にある $ 3 $ 枚のコインを拾うことができます。

### Sample Explanation 2

`RD` という移動経路も正解となります。

## 样例 #1

### 输入

```
3 4 4
3 3
2 1
2 3
1 4```

### 输出

```
3
DRRDR```

## 样例 #2

### 输入

```
2 2 2
2 1
1 2```

### 输出

```
1
DR```

## 样例 #3

### 输入

```
10 15 8
2 7
2 9
7 9
10 3
7 11
8 12
9 6
8 1```

### 输出

```
5
DRRRRRRRRDDDDDRRDRDDRRR```

# 题解

## 作者：__Allen_123__ (赞：43)

你是一名普通的 OIer。

> 学习 OI 的时候，合理分配 OI 和文化课的学习时间是很重要的。你一共需要花 $H-1$ 单位时间在文化课上，$W-1$ 单位时间在 OI 上。
>
> OI 和文化课是可以相互支持的，所以当你花了 $R_i$ 单位时间在文化课上，同时花了 $C_i$ 单位时间在 OI 上时，你可以获得一个 OI 奖项。
>
> 你的学习时间一共有 $H+W-2$ 单位，每次你可以选择把这 $1$ 单位时间用来学习文化课或者 OI（其中文化课的总学习时间为 $H-1$ 单位，OI 的总学习时间为 $W-1$ 单位）。你想要通过合理安排自己的时间来获得更多的奖项。求你可以获得的最多的奖项个数以及此时你的学习方式（`D` 代表学习文化课，`R` 代表学习 OI）。

你马上意识到可以把这个题目转化成一个网格上问题，用行号表示学习文化课的时间，用列号表示学习 OI 的时间。每次你可以向下或向右一个，遇到一个满足条件的 $(R_i,C_i)$ 就相当于获得一个奖项。

你知道可以整理出对于特定的文化课学习时间（即行号），有哪些对应的 OI 学习时间可以使你多获得一个奖项。于是你把这些奖项的位置 $(R_i,C_i)$ 进行了双关键字排序。

接着，你把重心放在每一个奖项获得的学习时间条件上。你观察到排序后，只需要注意每个列号就可以。

你考虑进行 dp，设 $dp_{i}$ 为到达排序后第 $i$ 个奖项处为止所获得的最多的奖项数。那么，如果 $C_j\le C_i$，则可以从第 $j$ 个奖项进行转移。故转移方程式为：$dp_i=\max\limits_{j=1}^{j\le i-1,C_j\le C_i}dp_j+1$。

以此进行类似最长不降子序列的计算即可。你这样做的时间复杂度为 $O(n\log n)$。

[你的 AC 记录](https://atcoder.jp/contests/abc369/submissions/57337639)。

进行完 OI 和文化课的学习后，你获得了不少的奖项，但也怅然若失。如果你把这 $H+W-2$ 单位的时间全部花在 OI 上，那结果是不是或许会更好？纵使你规划得无比完美，但这些规划都是基于限制之中的。若破除了限制，你认为你自己的结果也将会更佳。

你回到了第 $1$ 单位时间处。面对着前方的网格，你充满了信心，义无反顾地向右走着。

这个属于你的网格好像是无限大的。你把 $H+W-2$ 单位的时间都用在了 OI 上，正准备继续大步向前，却遇到了如墙一般的障碍物。这堵墙的反作用力十分巨大，你甚至撞了一下就直接被撞晕了过去。迷迷糊糊中，你眼前看到了一句话：

> ... and reach cell $(H,W)$ while picking up as many coins as possible ...

你想回去，但一切都为时已晚。时间不会因你的悔恨而倒流。文化课的学习纵使对你来说已经是附属品，但不知道为什么，你还要被迫为文化课付出时间。家长的质疑，老师的劝阻，同学的眼光……不知是因为接触了 OI 还是因为接触了文化课，你已经接近了麻木。

麻木到眩晕之际，你醒来在了中考考场。可你却一点没有为你刚刚所想而感到悲伤。**因为你根本就没有学过 OI。这只是你的幻想而已**。

---

## 作者：cjh20090318 (赞：14)

树状数组优化 DP 模板题。

## 题意

有 $N$ 枚硬币，第 $i$ 枚硬币的位置在 $(R_i,C_i)$。

你每次可以向右或向下移动一格，求从 $(1,1)$ 到 $(H,W)$ 最多能拾取多少枚硬币，并给出任意一种可行的移动方案。

## 分析

将所有硬币按照 $R_i$ 为第一关键字，$C_i$ 为第二关键字升序排列。

先考虑设一个朴素 DP，$f_i$ 表示前 $i$ 枚硬币且拾取第 $i$ 枚硬币能获得的最大硬币数量。
$$
f_i = 1 + \max\limits_{j \in [1,i)}^{R_j \le R_i \land C_j \le C_i} f_j
$$
最终答案即为 $\max\limits_{i = 1}^N f_i$。

这个东西很显然可以用树状数组或者线段树优化，在转移的时候记录一下每个硬币是从哪个硬币转移而来。

为了方便实现分别在开头和结尾添加 $(1,1)$ 和 $(H,W)$，时间复杂度 $O(N \log N)$。

## 代码

```cpp
//the code is from chenjh
#include<cstdio>
#include<algorithm>
#include<string>
#include<utility>
#define MAXN 200002
#define x first
#define y second
using namespace std;
typedef pair<int,int> PII;
using ci=const int;
int h,w,n;
PII a[MAXN];
int p[MAXN];
template<typename T>
struct fenwick_tree{
    public:
        fenwick_tree(int _SIZE=0):SIZE(_SIZE){dt=new T[SIZE+1]();for(int i=0;i<=SIZE;i++)dt[i]=T(0,0);}
        ~fenwick_tree(){delete[] dt;}
        void add(int x,const T&v){for(;x<=SIZE;x+=x&-x)dt[x]=max(dt[x],v);}
        T sum(int x)const{T ret(0,0);for(;x;x^=x&-x)ret=max(ret,dt[x]);return ret;}
    private:
        T*dt;
        int SIZE;
};
int main(){
	scanf("%d%d%d",&h,&w,&n);
	fenwick_tree<PII> T(w);
	a[0]=PII(1,1),a[++n]=PII(h,w);
	for(int i=1;i<n;i++) scanf("%d%d",&a[i].x,&a[i].y);
	sort(a+1,a+n);
	for(int i=1;i<=n;i++){
		PII r=T.sum(a[i].y);//查询前缀。
		p[i]=r.second;
		T.add(a[i].y,PII(r.first+1,i));//更新单点。
	}
	printf("%d\n",T.sum(w).first-1);//最后一个硬币 (H,W) 是人为添加的，所以需要减去最后一个的贡献。
	string ans="";
	for(int i=n,t;i;i=p[i]){//一直跳上一个点，逆序构造。
		t=p[i];
		for(int _=a[i].x-a[t].x;_--;)ans+='D';
		for(int _=a[i].y-a[t].y;_--;)ans+='R';
	}
	reverse(ans.begin(),ans.end());
	puts(ans.c_str());
	return 0;
}
```

---

## 作者：gesong (赞：6)

题目传送门：[[ABC369F] Gather Coins](https://www.luogu.com.cn/problem/AT_abc369_f)。
# 思路

遇到这种题，一般都是 dp，我们假设 $f_i$ 表示以第 $i$ 个硬币为终点的最优硬币个数，显然初始 $f_i=1$，最终答案为 $\max(f_1,f_2,\cdots,f_n)$。

我们考虑转移，发现只有 $R_j\le R_i,C_j\le C_i$，$j$ 才能走到 $i$，因此我们得到转移 $f_i=\max(f_j+1)$ 其中 $1\le j<i,R_j\le R_i,C_j\le C_i$，但这样做 dp 会有后效性，因此需要一开始需要将所有硬币按照先行后列双关键字升序排序。

然后考虑如何求解答案，我们可以记录 $pre_i$ 表示 $f_i$ 从哪个状态转移过来，即满足 $f_i=f_{j}+1$  和 $1\le j<i,R_j\le R_i,C_j\le C_i$ 的其中一个 $j$ 的值，然后我们就可以逆推求出我们行动的整个过程，然后输出即可。

但是我们发现这样子暴力做是 $O(n^2)$ 的，我们需要使用树状数组进行优化，优化过程类似一种打擂台的过程，如果这个数比原来的值大，就将这个值记录下来，并把这个位置记录下来，转移用最优解即可。
# 代码

赛时代码，其中被注释的是暴力 dp。

```cpp
#include<bits/stdc++.h>
#define int long long
#define lowbit(x) x&-x
#define pii pair<int,int>
using namespace std;
const int N=2e5+10;
int f[N],c[N],n,m,xx,d[N],pre[N],anss[N],cnt;
void dfs(int x){
	if (!x) return ;
	dfs(pre[x]);
	anss[++cnt]=x;
}
inline void add(int i,int x,int xxx){
	for (;i<N;i+=lowbit(i)){
		if (c[i]<x) c[i]=x,d[i]=xxx; 
	}
}
inline pair<int,int> get(int i){
	int ans=0,xxx;
	for (;i;i-=lowbit(i)){
		if (c[i]>ans) ans=c[i],xxx=d[i];
	}
	return {ans,xxx};
} 
struct nord{
	int a,b;
}a[N];
inline void print(int x1,int y1,int x2,int y2){
	for (int i=x1;i<x2;i++) cout <<"D";
	for (int i=y1;i<y2;i++) cout <<"R";
}
inline int read(){
	char c=getchar();
	int f=1,ans=0;
	while(c<48||c>57) f=(c==45?f=-1:1),c=getchar();
	while(c>=48&&c<=57) ans=(ans<<1)+(ans<<3)+(c^48),c=getchar();
	return ans*f;
}
main(){
	n=read(),m=read(),xx=read();
	for (int i=1;i<=xx;i++) a[i]={read(),read()},f[i]=1;
	sort(a+1,a+xx+1,[](nord x,nord y){
		if (x.a==y.a) return x.b<y.b;
		return x.a<y.a;	
	});
	/*
	for (int i=1;i<=xx;i++)
		for (int j=1;j<i;j++) 
			if (a[j].b<=a[i].b) f[i]=max(f[i],f[j]+1);*/
	for (int i=1;i<=xx;i++){
		pii x=get(a[i].b);
		if (x.first>1) f[i]=x.first,pre[i]=x.second;
		add(a[i].b,f[i]+1,i);
	}
	int ans=0,k;
	for (int i=1;i<=xx;i++){
		if (f[i]>ans) ans=f[i],k=i;
	}
	cout <<ans<<endl;
	dfs(k);
	print(1,1,a[anss[1]].a,a[anss[1]].b);
	for (int i=1;i<cnt;i++)
		print(a[anss[i]].a,a[anss[i]].b,a[anss[i+1]].a,a[anss[i+1]].b);
	print(a[anss[cnt]].a,a[anss[cnt]].b,n,m);
    return 0;
}

```

---

## 作者：Dtw_ (赞：4)

# 前言
拜谢 @[__ryp__](https://www.luogu.com.cn/user/723993) 大佬。
# 题意
给定一个网格，以及一些硬币，给定每个硬币的坐标，从 $(1,1)$ 开始，每一步只能往下走或者往右走，走到 $(h,w)$ 求获得硬币最多的数量，以及走的方案。
# 思路
考虑 $h,w$ 很大，不能直接转移，但是 $n$ 比较小，所以只在硬币上转移，我们发现，每个硬币只可能由他左上部分转移而来，所以先按 $x$ 排序，现在就只需要找 $y$ 比他小的点了，至于这个我们可以用树状数组维护前缀最大值，然后就转移完了。

至于方案我们用 $pre_i$ 表示 $i$ 点是由哪个点转移过来的，最后直接倒序输出就行。

细节看代码。
# Code

```cpp
#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

#define fi first
#define se second

#define int long long

#define pii pair<int, int>

#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

const int INF = 0x3f3f3f3f3f3f3f3f;

const int P = 998244353;

const int N = 1e6 + 10;

int h, w, n, pre[N], g[N];

pii a[N], f[N];

#define lb(o) (o)&(-o)

void add(int x, int p, int k)
{
	for(; x<=N-10; x+=lb(x))
	{
		if(k > f[x].se) f[x] = {p, k}; // first 维护最大值的下标，second 维护最大值 
	}
}

pii query(int x)
{
	int res = 0, p = 0; // 同时查询最大值以及最大值的下标 
	for(; x; x-=lb(x))
	{
		if(f[x].se > res) res = f[x].se, p = f[x].fi;
	}
	return make_pair(res, p);
}

signed main()
{
	fst
	cin >> h >> w >> n;
	for(int i=1; i<=n; i++) cin >> a[i].fi >> a[i].se;
	sort(a+1, a+n+1); // 按 x 排序 
	a[++n] = {h, w};  // 先加入 (h, w) 便于算答案 
	for(int i=1; i<=n; i++)
	{
		auto p = query(a[i].se); // 找 y 之前的最大值 
		pre[i] = p.se; // 最大值的下标 
		g[i] = p.fi + 1; // 最大值 + 我这一位 
		add(a[i].se, i, g[i]); // 更新 
	}
	cout << g[n] - 1 << endl; // 因为 (h, w) 没有，但是我们算进去了，所以要把它减 1 
	a[0] = {1, 1}; // 方便记录答案 
	int t = n; // 从最后一个点开始往前找 
	string s;
	while(t)
	{
		int x = a[t].fi, y = a[t].se; // 求出当前点和前一个点 
		int nx = a[pre[t]].fi, ny = a[pre[t]].se;
		int l = x - nx; // 差值 
		while(l--) s += 'D'; // 因为这个路径也就 4e5 个点左右，所以直接暴力加 
		l = y - ny;
		while(l--) s += 'R';
		t = pre[t]; // 跳到上一个点 
	}
	reverse(s.begin(), s.end()); // 因为我们从 n 开始找的，所以要反转 
	cout << s;
	return 0;
}



```

---

## 作者：_determination_ (赞：2)

直接暴力 dp，设 $f_i$ 为以第 $i$ 枚硬币为终点的最大收益。dp 顺序就是现将所有点按 $x$ 为第一关键字，以 $y$ 为第二关键字。然后按点的顺序 dp。我们只能从左上角的点转移。

我们发现这样是 $n^2$ 的，我们需要找到所有有效点，直接树套树启动，复杂度 $O(n\log ^2n)$。

---

## 作者：PikachuQAQ (赞：1)

### Description

[Link](https://www.luogu.com.cn/problem/AT_abc369_f)

### Solution

新东西。

可以转化为二元上升子序列问题，具体来讲先以 $x$ 排序，造一个数组 $f$，每次找到一个元素就二分大于它的元素，如果没有就直接插入，否则放进二分出的地方。

将所有被记录答案的 $y$ 标记 $i$，随后标记步骤。

然后，使用一个 `DFS`，求出步骤，求出所有坐标后模拟输出步骤即可。

### Code

```cpp
// PikachuQAQ 2024/09/02

#include <bits/stdc++.h>

using namespace std;

const int kMaxN = 2e5 + 2, INF = 1e9;

int n, m, k, f[kMaxN], b[kMaxN], p[kMaxN], ans;
pair<int, int> a[kMaxN];
vector<pair<int, int> > res; 

void DFS(int x) {
    if (p[x]) DFS(p[x]);
    res.push_back(a[x]);
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m >> k;
    for (int i = 1, x, y; i <= k; i++) {
        cin >> x >> y, a[i] = {x, y};
    }
    sort(a + 1, a + k + 1);
    fill(f + 1, f + k + 1, INF);
    for (int i = 1; i <= k; i++) {
        auto [x, y] = a[i];
        int t = upper_bound(f, f + k + 1, y) - f;
        f[t] = y;
        if (t) p[i] = b[f[t - 1]];
        b[y] = i, ans = max(ans, t);
    }
    cout << ans << '\n';
    DFS(b[f[ans]]);
    res.push_back({n, m});
    int lstx = 1, lsty = 1;
    for (auto [x, y] : res) {
        for (int i = lstx; i < x; i++) cout << 'D';
        for (int i = lsty; i < y; i++) cout << 'R';
        lstx = x, lsty = y;
    }

    return 0;
}
```

---

## 作者：Cure_Wing (赞：1)

[AT_abc369_f [ABC369F] Gather Coins](https://www.luogu.com.cn/problem/AT_abc369_f)

### 解析

第一反应暴力 $\texttt{dp}$ 设 $f_{i,j}$ 表示从 $(1,1)$ 到 $(i,j)$ 可以收获的硬币的最大数量，显然有：

$$f_{i,j}=\max\limits_{1\le u\le i,1\le v\le j}f_{u,v}+vis_{i,j}$$

$vis_{i,j}$ 表示该点是否存在硬币。

这样空间复杂度和时间复杂度都是 $O(HW)$ 的，显然不行。

首先当然可以直接枚举存在硬币的点，但是时间复杂度 $O(N^2)$，空间依旧爆炸。

但是对于同一列的到达方案中，选择越下面的转折点一定时更优秀的。

此时重新定义 $f_i$ 表示到先按纵坐标从小到大排序，再按横坐标从小到大排序的存在硬币的格子的编号的最优答案，$b$ 数组表示枚举到 $i$ 格子时各列硬币数的最大值，则有：

$$f_i=\left(\max\limits_{j=1}^{C_i}b_j\right)+1$$

同时为了方便统计答案，我们会在起点和终点各放一枚硬币，计算最后答案时除去放的这两枚即可。

注意每次需要对 $b$ 查询前缀最大值，单点修改，上一个树状数组维护即可，时间复杂度 $O(N\log_2(NH))$ 或 $O(N\log_2(NW))$，空间复杂度 $O(N+H)$ 或 $O(N+W)$。

不要忘记输出方案，具体你在树状数组和 $\texttt{dp}$ 方程中记下转移的点即可。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using std::cin;using std::cout;
constexpr int N=200005;
int h,w,n,f[N],to[N],l[N];
struct A{int r,c;}a[N];
inline void print(int p){
	if(to[p]==-1) return ;
	print(to[p]);
	for(int i=a[to[p]].r;i<a[p].r;++i) cout<<'D';
	for(int i=a[to[p]].c;i<a[p].c;++i) cout<<'R';
}
struct Tree{
	int b[N],pos[N];
	inline int lowbit(int x){return x&-x;}
	inline void update(int x,int y,int k){
		for(int i=x;i<=w;i+=lowbit(i)) if(y>b[i]){b[i]=y;pos[i]=k;}
	}
	inline A query(int x){
		int ans=0,id=0;
		for(int i=x;i;i^=lowbit(i))
			if(b[i]>ans){ans=b[i];id=pos[i];}
		return A{ans,id};
	}
}tree;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
	cin>>h>>w>>n;
	for(int i=1;i<=n;++i) cin>>a[i].r>>a[i].c;a[++n]=A{h,w};a[++n]=A{1,1};
	std::sort(a+1,a+n+1,[](A a,A b){return a.r<b.r||a.r==b.r&&a.c<b.c;});
	f[1]=1;to[1]=-1;l[1]=1;tree.update(1,1,1);
	for(int i=2;i<=n;++i){
		A p=tree.query(a[i].c);
		f[i]=p.r+1;to[i]=p.c;
		tree.update(a[i].c,f[i],i);
	}
	cout<<f[n]-2<<'\n';
	print(n);
	return 0;
}//第八十七回 感深秋抚琴悲往事 坐禅寂走火入邪魔
```

顺带纪念第一次 $\texttt{AK\;ABC}$。

---

## 作者：JOKER_chu (赞：1)

写的比较复杂好懂。

## 题意

给出二维平面上的 $n$ 个点，每个点 $(x_i, y_i)$ 上有一枚金币，求从 $(1, 1) \rightarrow (h, w)$ 的路径上可以获取的最多金币数量，并输出路径，只能向下或往右走。

## 解法

注意到只有 $n$ 个点，先按 $x$ 排个序，然后就只用考虑 $y$ 了，然后对 $n$ 个点做 `dp`，状态就是 $dp_{i, x}$ 表示前 $i$ 个点最后 $y$ 坐标在 $x$ 处时的最大获得金币数量，然后转移 $dp_{i, x} = \max \{dp_{i - 1, j} \} \land 1 \leq j \leq x$，显然动态前缀最大值，直接树状数组维护，然后记录最优转移，乱搞还原路径就行了。

## 代码

代码是按照 $y$ 排序的，因为比较好推。

```cpp
#include <iostream>

#include <algorithm>

#include <vector>

#define endl '\n'

using namespace std;

const int N = 2e5 + 5;

struct Point{ // 点
	int x, y;
}p[N];

struct State{ // 状态
	int x, from;
}dp[N];

struct Node{ // 树状数组
	int x, id;
}t[N];

int h, w, n, in[N];

bool cmp(Point &i, Point &j){
	return i.y < j.y || i.y == j.y && i.x < j.x;
}

int lowbit(int x){
	return x & -x;
}

void update(int x, int k, int id){
	for(; x <= h; x += lowbit(x)) if(t[x].x < k) t[x] = {k, id};
}

Node query(int x){ // 维护最大值的树状数组
	Node ret = {-1, 0};
	for(; x > 0; x -= lowbit(x)) ret = (ret.x < t[x].x ? t[x] : ret);
	return ret;
}

int main(){
	ios :: sync_with_stdio(0), cin.tie(0);
	cin >> h >> w >> n;
	for(int i = 1; i <= n; ++i) cin >> p[i].x >> p[i].y;
	sort(p + 1, p + n + 1, cmp); // 降掉一个维度
	for(int i = 1; i <= n; ++i){
		dp[p[i].x] = {query(p[i].x).x + 1, query(p[i].x).id}; // 更新 dp，可以降维
		in[i] = query(p[i].x).id; // 从哪个点最优就走哪个点
		update(p[i].x, dp[p[i].x].x, i); // 更新树状数组
	}
	cout << query(h).x << endl;
	int id = query(h).id; // 还原路径
	vector<string>anss;
	string temp = "";
	for(int i = 1; i <= abs(h - p[id].x); ++i) temp += "D";
	for(int i = 1; i <= abs(w - p[id].y); ++i) temp += "R";
	anss.push_back(temp);
	p[0].x = p[0].y = 1;
	while(id > 0){ // 还有点在这个点之前
		string t = ""; // 从这个点到上一个点的路径
		for(int i = 1; i <= abs(p[id].x - p[in[id]].x); ++i) t += 'D'; // 从这个点到上一个点的路径要走多少下
		for(int i = 1; i <= abs(p[id].y - p[in[id]].y); ++i) t += 'R'; // 从这个点到上一个点的路径要走多少右
		id = in[id]; // 从这个点回到上一个点
		anss.push_back(t);
	}
	for(int i = anss.size() - 1; i > -1; --i)
		cout << anss[i]; // 由于是倒序还原的路径，倒序输出
	return 0;
}
```

---

## 作者：zibenlun (赞：1)

# 思路

每一个硬币一定是从比它横纵坐标都小的硬币上转移过来，我们将所有硬币先按横坐标排序，再按纵坐标排序，枚举每一个硬币，用树状数组维护，并标记每一个硬币从哪一个硬币转移过来。

# 代码

``` cpp
#include<bits/stdc++.h>
#define int long long
#define lowbit(x) (x&(-x))
#define faster ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
using namespace std;
int n,m,q;
int c[200005];
int ans;
struct nd{
	int x,y;
}a[200005];
int dp[200005];
int v[200005];
int pos[200005];
bool cmp(nd x,nd y){
	if(x.x==y.x) return x.y<y.y;
	return x.x<y.x;
}
void add(int x,int e,int id){
	for(int i=x;i<=m;i+=lowbit(i)){
		if(e>=c[i]) c[i]=e,pos[i]=id;
	}
}
int ask(int x){
	int sum=0,ps=0;
	for(int i=x;i;i-=lowbit(i)){
		if(c[i]>=sum){
			sum=c[i];
			ps=pos[i];
		}
	}
	return ps;
}
signed main() {
	faster
	cin>>n>>m>>q;
	for(int i=1;i<=q;i++){
		cin>>a[i].x>>a[i].y;
	}
	sort(a+1,a+1+q,cmp);
	a[0].x=1;
	a[0].y=1;
	a[q+1].x=n;
	a[q+1].y=m;
	for(int i=1;i<=q;i++){
		int x=ask(a[i].y);
		dp[i]=dp[x]+1;
		v[i]=x;
		add(a[i].y,dp[i],i);
	}
	int k=ask(m);
	// cout<<x;
	cout<<dp[k];
	cout<<"\n";
	int x=1,y=1;
	stack<int> s;
	s.push(q+1);
	int pos=k;
	while(pos!=0){
		s.push(pos);
		pos=v[pos];
	}
	while(s.size()){
		int i=s.top();
		s.pop();
		while(x<a[i].x) {
			cout<<"D";
			x++;
		}
		while(y<a[i].y){
			cout<<"R";
			y++;
		}
	}
	return 0;
}
```

---

## 作者：D0000 (赞：1)

如果地图大小没那么大，就是一道非常简单的 DP 了。

现在地图太大了，但是许多点上的值都为空，而只有可能在有值的地方产生贡献。于是每次只能从某个点左上方有值的地方转移而来。

将 $x$ 坐标作为第一关键字，$y$ 坐标作为第二关键字排序，这样子后面的答案就不会对前面的造成影响。并且能够转移的变成了它左边的了。就可以使用线段树维护。

至于输出方案，就记录每个点是从哪个店转移而来，依次跳回去即可。

---

## 作者：HasNoName (赞：1)

### 思路
由于路径只能从上到下，从左到右，所以考虑以横轴为第一关键字，纵轴为第二关键字排序，这样枚举路径时只用考虑纵轴。

由于暴力做时 $O(N^2)$ 的，无法通过，所以考虑优化。

可以证明，如果从一个点以前能有总和最大的点到当前点的话，当前点的权值总和一定最大。

所以可以使用线段树或树状数组来维护。

但由于要输出路径，故还需要记录下标。

这里使用树状数组。
### 代码
```cpp
#include<bits/stdc++.h>
#define lowbit(x) (x&(-x))
using namespace std;
const int N=200005;
typedef long long ll;
struct T
{
	int x,y,v;
}a[N];
struct coin
{
	int v,w;//v表示权值，w表示位置
};
ll c[N],id[N],f[N],ne[N],sta[N*2],top;
string ans;
coin get(int k)//树状数组的查询操作
{
	int ans=-1,p;
	for(int i=k;i;i-=lowbit(i))
	{
		if(c[i]>ans)
		{
			ans=c[i];
			p=id[i];
		}
	}
	return (coin){ans,p};
}
void to(int k,int x,int p)//树状数组的修改操作
{
	for(int i=k;i<N;i+=lowbit(i))
	{
		if(x>=c[i])
		{
			c[i]=x;
			id[i]=p;
		}
	}
}
bool cmp(T a,T b)
{
	if(a.x!=b.x)return a.x<b.x;
	return a.y<b.y;
}
void run(T a,T b)//两个点间的具体路径
{
	for(int i=a.x;i<b.x;i++)ans+='D';
	for(int i=a.y;i<b.y;i++)ans+='R';
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n,m,k;
	cin>>n>>m>>k;
	for(int i=1;i<=k;i++)
	{
		cin>>a[i].x>>a[i].y;
		a[i].v=1;
	}
	sort(a+1,a+k+1,cmp);//排序
	to(1,0,0);//位置为(1,1)的点特殊考虑
	for(int i=1;i<=k;i++)
	{
		f[i]=get(a[i].y).v+a[i].v;
		ne[i]=get(a[i].y).w;
		to(a[i].y,f[i],i);
	}
	int maxn=-1,maxi=0;
	for(int i=1;i<=k;i++)//找最大值
	{
		if(f[i]>maxn)
		{
			maxn=f[i];
			maxi=i;
		}
	}
	a[0]={1,1,0};
	a[++k]={n,m,0};//由于必须走到(n,m)，故加入
	cout<<maxn<<'\n';
	int s=maxi;
	sta[++top]=k;//sta表示存储点的栈
	while(s)
	{
		sta[++top]=s;
		s=ne[s];
	}
	sta[++top]=0;
	for(int i=top;i>1;i--)//得到路径
		run(a[sta[i]],a[sta[i-1]]);
	cout<<ans<<'\n';//输出路径
	return 0;
}
```

---

## 作者：liruixiong0101 (赞：1)

# F - Gather Coins
## 题意：
现在有一个 $h\times w$ 的网格，网格上有 $n$ 枚金币，第 $i$ 枚金币在网格 $(x_i,y_j)$ 处，现在你在网格 $(1,1)$ 处，你想走到网格 $(h,w)$ 处且获得最多的金币，你每次只能向下或向右走。请问你做多能获得多少金币，并输出其中的一种路径。

## 思路：
容易发现路径的横纵坐标是单调不减的，所以所获得到的金币的横纵坐标也都得是单调不减的，且若所获得的金币的横纵坐标都是单调不减的，那么你一定都能获取到。那么其实就是要求金币按照横坐标从小到大排序后，选取子序列最长且满足纵坐标单调不减，那么题目就转化成了二维偏序问题，可以用最长不下降子序列解决。

## 代码：
<https://atcoder.jp/contests/abc369/submissions/57324756>

---

## 作者：yanwh1 (赞：1)

赛时有思路的，但是没打出来（悲）。
# 题目大意：
给你一个 $H$ 行 $W$ 列的网格，你只能往右或往下走。网格中有 $N$ 个点，每走过其中一个点会获得一点贡献。问从 $(1,1)$ 开始，到 $(H,W)$ 怎么走能使贡献最大，并给出一条可行路径。
# 思路解析：
因为只能往右或往下走，所以当一个点为起点时，对于它有供献的点只能是它右下的点，于是我们可以先将这 $N$ 个点从下往上，从右往左排序。处理完后，便能用线段树，处理以当前点为起点，贡献最大可以是多少，顺便记一下最大贡献路径上带供献的点即可。
# 代码实现：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define rint register int
inline int read(){
    int f=0,t=0;
    char c=getchar();
    while(!isdigit(c)) t|=(c=='-'),c=getchar();
    while(isdigit(c)) f=(f<<3)+(f<<1)+c-48,c=getchar();
    return t?-f:f;
}
inline void write(int x) {
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar('0'+x%10);
}const int N=2e5+5;
int mx[N],to[N],wh[N];
struct node{int x,y;}s[N];
inline int cmp(node a,node b){return a.x==b.x?a.y>b.y:a.x>b.x;}
struct edge{int l,r,mx;}tr[N<<2];
inline void build(int p,int l,int r){
	tr[p]={l,r,0};
	if(l==r)return;
	int mid=l+r>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
}inline void update(int p,int x){
	if(tr[p].l==tr[p].r){
		tr[p].mx=tr[p].l;
		return;
	}int mid=tr[p].l+tr[p].r>>1;
	if(x<=mid)update(p<<1,x);
	else update(p<<1|1,x);
	tr[p].mx=mx[tr[p<<1].mx]>mx[tr[p<<1|1].mx]?tr[p<<1].mx:tr[p<<1|1].mx;
}inline int query(int p,int l,int r){
	if(l<=tr[p].l&&tr[p].r<=r)return tr[p].mx;
	int mid=tr[p].l+tr[p].r>>1,r1=0,r2=0;
	if(l<=mid)r1=query(p<<1,l,r);
	if(mid<r)r2=query(p<<1|1,l,r);
	return mx[r1]>mx[r2]?r1:r2;
}
signed main(){
	int h=read(),w=read(),n=read();build(1,1,w);
	for(rint i=1;i<=n;i++)s[i]={read(),read()};
	sort(s+1,s+n+1,cmp);
	for(rint i=1;i<=n;i++){
		int x=query(1,s[i].y,w);
		to[i]=wh[x],wh[s[i].y]=i;
		mx[s[i].y]=mx[x]+1;
		update(1,s[i].y);
	}int ans=0,wz=0;
	for(rint i=1;i<=w;i++){
		if(ans<mx[i])ans=mx[i],wz=wh[i];
	}write(ans),puts("");
	int zx=1,zy=1,rx=s[wz].x,ry=s[wz].y;
	while(wz){
		while(zx<rx)putchar('D'),zx++;
		while(zy<ry)putchar('R'),zy++;
		wz=to[wz],rx=s[wz].x,ry=s[wz].y;
	}while(zx<h)putchar('D'),zx++;
	while(zy<w)putchar('R'),zy++;
	return 0;
}
```

---

## 作者：Lydia1010__ (赞：0)

## 本题思路：
这道题我们知道到一个有金币的点收到的最多的金币一定是以起始点与当前点为对角点围成的长方形中的每个金币点可以收的最多的金币数量加一。

这样我们就可以用扫描线加树状数组维护以起始点与当前点为对角点围成的长方形中可以收到的最多的金币是多少，树状数组时顺便记录一下是从上面的哪一个金币转过来的。随后直接找到最大的可收集金币数量，以当前节点开始逆推出所有点。

然后直接一个一个点走就可以了。
## 本题代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct f{int l,r;}a[200005],ans[200005],tr[200005];
int cnt;
bool cmp(f x,f y){
	if(x.r==y.r) return x.l<y.l;
	return x.r<y.r;
}
int dp[200005],q[200005];
int suan(int p){return (-p)&p;}
int h;
void add(int q,int p,int k){
//	if(!p) return ;
	for(int i=p;i<=h;i+=suan(i)){if(tr[i].l<k){tr[i].r=q,tr[i].l=k;}}
}
f cha(int p){
	f ans;ans.l=0;ans.r=0;
	for(int i=p;i;i-=suan(i)){
		if(tr[i].l>ans.l){
			ans.l=tr[i].l,ans.r=tr[i].r;
		}
	}
	return ans;
}
bool vis[200005];
signed main(){
	int w,n;
	cin>>h>>w>>n;
	for(int i=1;i<=n;i++) {cin>>a[i].l>>a[i].r;}
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<=h;i++) tr[i].l=0,tr[i].r=0;
	int l=1;
	for(int i=1;i<=n;i++){
		f sum=cha(a[i].l);
		dp[i]=sum.l+1;
		q[i]=sum.r;
		add(i,a[i].l,dp[i]);
	}
	int ma=0,maa=0;
	for(int i=1;i<=n;i++){if(ma<dp[i]) ma=dp[i],maa=i;}
	int p=maa;
	while(p){
		if(vis[p]==1) break;
		vis[p]=1;
		p=q[p];
	}
	for(int i=1;i<=n;i++){
		if(vis[i]) ans[++cnt]=a[i];
	}
	sort(ans+1,ans+1+cnt,cmp);
	int h1=1,w1=1;
	cout<<cnt<<'\n';
	for(int i=1;i<=cnt;i++){
		while(w1<ans[i].r) cout<<"R",w1++;
		while(h1<ans[i].l) cout<<"D",h1++;
	}
	while(h1<h) cout<<"D",h1++;
	while(w1<w) cout<<"R",w1++;
	return 0;
}
```

---

## 作者：JackMerryYoung (赞：0)

# 前言

做这个题的时候糖丸了。

# 正文

这个题目实际上非常简单，我们可以把这个题看成要求满足二维偏序关系的最长序列，但最后其实可以转化成求最长上升子序列。

先按 $R$ 为第一关键字，$C$ 为第二关键字排个序，然后对序列按照 $C$ 做个 LIS，然后就好了。

# 代码

赛时写了二维偏序代码，大家也可以写 LIS 做法。

``` cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll N, M, K, mm2;

struct node {
	ll x, y;
} arr[200005];

ll tree[200005];
bool cmp(node xx, node yy)
{
	if(xx.x != yy.x) return xx.x < yy.x;
	else return xx.y < yy.y; 
}

ll dis[200005];

ll lowbit(ll x)
{
	return x & -x;
}

ll query(ll x)
{
	ll sum = 0;
	while(x) sum = max(tree[x], sum), x -= lowbit(x);
	return sum;
}

void add(ll x, ll z)
{
	while(x <= M) tree[x] = max(tree[x], z), x += lowbit(x);
}

char c[400005];

signed main()
{
	cin >> N >> M >> K;
	for(ll i = 1; i <= K; ++ i) cin >> arr[i].x >> arr[i].y;
	sort(arr + 1, arr + K + 1, cmp);
	ll maxn = 0;
	for(ll i = 1; i <= K; ++ i)
	{
		dis[i] = query(arr[i].y) + 1;
		add(arr[i].y, dis[i]);
		maxn = max(maxn, dis[i]);
	}
	
	ll x = N, y = M, kk = K;
	cout << maxn << endl;
	while(maxn)
	{
		for(ll i = kk; i > 0; -- i)
		{
			if(dis[i] == maxn && y >= arr[i].y)
			{
				kk = i - 1;
				for(ll j = x - arr[i].x; j; -- j) c[++ mm2] = 'D';
				for(ll j = y - arr[i].y; j; -- j) c[++ mm2] = 'R'; 
				x = arr[i].x,y = arr[i].y;
				break;
			}
		}
		
		-- maxn;
	}
	
	for(ll i = x - 1; i; -- i) c[++ mm2] = 'D';
	for(ll i = y - 1; i; --i) c[++ mm2] = 'R';
	for(ll i = mm2; i; --i) cout << c[i];
	cout << endl;
	return 0;
}
```

---

## 作者：_ZML_ (赞：0)

# 思路
第一次独立做出来第六题（虽然是赛后做出来的）。

可以考虑动态规划。

发现只有有硬币的点对答案有贡献，一个点只能从左上方转移过来，而且只会从有硬币的点转移过来。

我们枚举横坐标，把对应的点按照纵坐标从小到大排序。因为枚举了横坐标，所以保证了横坐标的单调，所以我们需要用一个数据结构来计算纵坐标小于当前的点的 $dp$ 的最大值，可以用树状数组来实现。

输出方案可以记录这个点从哪里转移过来。

具体的可以看代码。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define fi first
#define sc second
int n,m,k;
vector<int> dp[200010];
vector<pair<int,int> > ans[200010];//这个点
vector<pair<int,int> > p[200010];
pair<int,int> a[200010];
pair<int,int> res[200010];
map<pair<int,int>,pair<int,int> > mp;
struct node{
	int w,y,id;
}c[2000010];	
int tot=0;
//树状数组求前缀最大值
void add(int x,int y,int id,int z) {
	for(;x<=n;x+=x&-x) {
		if(c[x].w<z) {
			c[x].w=z;
			c[x].y=y;
			c[x].id=id;
		}
	}
}
pair<int,int> query(int x) {
	int mx=0, y=0,id=0;
	for(;x;x-=x&-x) {
		if(c[x].w>mx) {
			y=c[x].y,id=c[x].id,mx=c[x].w;
		}
	}
	return {y,id};
}
signed main() {
	cin>>n>>m>>k;
	for(int i=1;i<=k;i++) {
		cin>>a[i].fi>>a[i].sc;
		p[a[i].sc].push_back({a[i].fi,1});//把这个点挂到 a[i].sc 上
	} 
	for(int i=1;i<=m;i++) {
		sort(p[i].begin(),p[i].end());
    //按照纵坐标排序，
		dp[i].resize(p[i].size()+1,0);
		ans[i].resize(p[i].size()+1);
		for(auto &x:ans[i]) {
			x.first=x.second=0;
		}
    //清空数组
	}
	int qwq=p[m].size();
	if(qwq-1<0||p[m][qwq-1].fi!=n) {
		p[m].push_back({n,0});
		qwq=p[m].size();
	}
  // 把终点看成一个价值为 0 的硬币
	for(int now=1;now<=m;now++) {
		if(!p[now].size()) {
			continue;
		}
		int s_now=p[now].size();
		for(int i=0;i<s_now;i++) {
			auto tmp=query(p[now][i].fi);
			int y=tmp.first, id=tmp.second;
            //计算当前点左上角最大的答案
			dp[now][i]=(y==0?0:dp[y][id])+p[now][i].sc;
			ans[now][i]={y,id};
			if(y) mp[{p[now][i].fi,now}]={p[y][id].fi,y};
			else mp[{p[now][i].fi,now}]={1,1};
          //记录当前点由哪个点转移过来的
			add(p[now][i].fi,now,i,dp[now][i]);
		}
	}
	int nx=n,ny=m;
	cout<<dp[m][qwq-1]<<"\n";
	while(1) {
		res[++tot]={nx,ny};
		if(nx==1&&ny==1) break;
		auto tmp=mp[{nx,ny}];
		nx=tmp.first,ny=tmp.second;
	}
	reverse(res+1,res+tot+1);
	for(int i=2;i<=tot;i++) {
		int gx=res[i].fi,gy=res[i].sc;
		int nx=res[i-1].fi,ny=res[i-1].sc;
		for(int j=1;j<=abs(nx-gx);j++) cout<<"D";
		for(int j=1;j<=abs(ny-gy);j++) cout<<"R";
		nx=gx,ny=gy;
	}
	return 0;
}
```
# 后记
明天就开学了，祝大家在新的一学期突破自我。

加油，前方的路还长。

---

## 作者：Fire_flame (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc369_f)

## $\mathtt{Solution}$

二维问题显然是不好做的，我们考虑把棋子的位置转成一维。

一个显然的套路是，把点按照 $x$ 坐标为第一关键字，$y$ 坐标为第二关键字排序。

此时就变成了一个以 $y$ 为权值的最长不下降子序列问题，最大值是好求的。

-----

然后考虑输出方案，令最长不下降子序列为 $\{a_1,a_2,\dots,a_k\}$。

我们要预处理出一个数组 $pos_i$，表示这个数在最长不下降子序列中能够排到的位置。也就是说，$pos_i$ 满足 $a_{pos_i}\le y_i<a_{pos_i + 1}$。

从后往前填，假设我们现在在填第 $cnt$ 个数，如果 $pos_i=cnt$ 且 $y_i$ 小于等于上一个填的数，那么就可以加进去。

赛时代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int read(){
	int s = 0, f = 1;char ch = getchar();
	while(!isdigit(ch)){if(ch == '-')f = -1;ch = getchar();}
	while(isdigit(ch)){s = s * 10 + ch - '0';ch = getchar();}
	return s * f;
}
void write(int x){
    if(x < 0){putchar('-'); x = -x;}
    if(x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
const int MAXN = 5e5 + 5;
struct node{
	int x, y;
	bool operator < (const node &zzz)const{
		if(x != zzz.x)return x < zzz.x;
		return y < zzz.y;
	}
}a[MAXN];
int n, m, k, cnt, res, f[MAXN], c[MAXN], ans[MAXN], pos[MAXN];
void print(int sx, int sy, int ex, int ey){//输出方案的函数
//	printf("%d %d %d %d\n", sx, sy, ex, ey);
	for(int i = ey - sy;i;i --)printf("R");
	for(int i = ex - sx;i;i --)printf("D");
}
int main(){
	n = read(), m = read(), k = read();
	for(int i = 1;i <= k;i ++)
		a[i] = {read(), read()};
	a[++ k] = {1, 1}, a[++ k] = {n, m};//这里偷了个懒，把起点终点放进去了，最后答案-2即可
	sort(a + 1, a + k + 1);
	c[++ cnt] = a[1].y, pos[1] = 1;
	for(int i = 2;i <= k;i ++){
		if(a[i].y >= c[cnt]){
			c[++ cnt] = a[i].y;
			pos[i] = cnt;//预处理pos数组
		}
		else{
			int p = upper_bound(c + 1, c + cnt + 1, a[i].y) - c;
			c[p] = a[i].y;
			pos[i] = p;//预处理pos数组
		}
//		printf("%d %d %d %d\n", i, a[i].x, a[i].y, pos[i]);
	}
	printf("%d\n", cnt - 2);
	res = cnt;
	int last = 1145141919;
	for(int i = k;i >= 1;i --){//从后往前填数
		if(cnt == 0)break;
		if(cnt == pos[i] && last >= a[i].y){
//			printf("%d %d %d\n", i, a[i].x, a[i].y);
			ans[cnt --] = i;
			last = a[i].y;
		}
	}
//	for(int i = 1;i <= res;i ++)printf("%d %d\n", a[ans[i]].x, a[ans[i]].y);
	for(int i = 1;i < res;i ++)
		print(a[ans[i]].x, a[ans[i]].y, a[ans[i + 1]].x, a[ans[i + 1]].y);
	return 0;
}
```

---

## 作者：fire_and_sweets (赞：0)

**前置知识：$\mathcal{O}(n\log n)$ LIS 及其方案输出**

第一次遇到这么经典的 F。

注意到一条合法的路径一定是从左上角到右下角，而且选取的坐标中，$x$ 必须单调不减，$y$ 也必须单调不减。

注意到我们不能很好的处理两维的问题，所以我们考虑把它转化成一维 LIS。我们只要把给出的所有关键点按照 $x$ 从小到大排序即可，这样只要对 $y$ 做一个 LIS。

另外这题要输出方案，直接写 LIS 的方案输出，再转换成题目中所给的 `RD` 路径即可。

完整代码不放了，就放一个把坐标转换成方案的代码吧。（其实这一段很好写，但也是我的代码中唯一一个不是板子的地方）

```
void print(PII p1, PII p2)
{
	int X1 = p1.first, Y1 = p1.second, X2 = p2.first, Y2 = p2.second;
	int dx = X2 - X1, dy = Y2 - Y1;
	while (dx -- ) cout << 'D';
	while (dy -- ) cout << 'R';
}
```

---

## 作者：Genius_Star (赞：0)

[**或许更好的阅读体验。**](https://www.cnblogs.com/rgw2010/p/18391497)

### 题意：

给定一个 $h \times w$ 的棋牌，有 $n$ 个位置上有一个棋子，其它位置没有棋子，人每次可以往下或往左走，问从 $(1,1)$ 走到 $(n,n)$ 能收集到的最多的棋子数量。

$1 \le h,w \le 2 \times 10^5,1 \le n \le \min(hw-2,2 \times 10^5)$。

### 思路：

考虑动态规划，令 $dp_i$ 表示到达第 $i$ 个棋子最大权值，则状态转移方程为：

$$dp_i = \max [x_j \le x_i] [y_j \le y_i ] dp_j + 1$$

这是二维偏序优化动态规划问题，考虑先按 $x$ 从小到大排序，若 $x$ 相同则按 $y$ 从小到大排序，那么这样对于 $j < i$，自然都满足 $x_j \le x_i$，则状态转移方程降了一维：

$$dp_i = \max [y_j \le y_i] dp_j +1$$

相当于询问 $[1,y_i]$ 区间内的最大值，因为需要输出路径，所以我们还需要记录一下最大值的位置，使用线段树维护即可。

时间复杂度为 $O(N \log N)$。

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
#define For(i,l,r) for(int i=l;i<=r;i++)
#define _For(i,l,r) for(int i=r;i>=l;i--)
using namespace std;
typedef long double lb;
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
struct Node{
	ll x,y;
	bool operator<(const Node&rhs)const{
		if(x^rhs.x)
		  return x<rhs.x;
		return y<rhs.y;
	}
}a[N];
struct St{
	ll l,r;
	ll Max,id;
}X[N<<2];
ll h,w,n,id,cnt,ans;
ll dp[N],pre[N];
string S[N];
void pushup(ll k){
	X[k].Max=max(X[k<<1].Max,X[k<<1|1].Max);
	if(X[k].Max==X[k<<1].Max)
	  X[k].id=X[k<<1].id;
	else
	  X[k].id=X[k<<1|1].id;
}
void build(ll k,ll l,ll r){
	X[k].l=l,X[k].r=r;
	if(l==r)
	  return ;
	ll mid=(l+r)>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
}
void add(ll k,ll i,ll v,ll id){
	if(X[k].l==i&&i==X[k].r){
		if(v>X[k].Max){
			X[k].Max=v;
			X[k].id=id;
		}
		return ;
	}
	ll mid=(X[k].l+X[k].r)>>1;
	if(i<=mid)
	  add(k<<1,i,v,id);
	else
	  add(k<<1|1,i,v,id);
	pushup(k);
}
pi query(ll k,ll l,ll r){
	if(X[k].l==l&&r==X[k].r)
	  return {X[k].Max,X[k].id};
	ll mid=(X[k].l+X[k].r)>>1;
	if(r<=mid)
	  return query(k<<1,l,r);
	else if(l>mid)
	  return query(k<<1|1,l,r);
	else{
		auto x=query(k<<1,l,mid),y=query(k<<1|1,mid+1,r);
		pi ans;
		ans.fi=max(x.fi,y.fi);
		if(ans.fi==x.fi)
		  ans.se=x.se;
		else
		  ans.se=y.se;
		return ans;
	}
}
int main(){
	h=read(),w=read(),n=read();
	a[0]={1,1};
	a[n+1]={h,w};
	For(i,1,n)
	  a[i]={read(),read()};
	build(1,1,w);
	sort(a+1,a+n+1);
	dp[1]=ans=id=1;
	add(1,a[1].y,1,1);
	For(i,2,n){
		auto t=query(1,1,a[i].y);
		dp[i]=t.fi+1;
		pre[i]=t.se;
		add(1,a[i].y,dp[i],i);
		if(dp[i]>ans){
			ans=dp[i];
			id=i;
		}
	}
	pre[n+1]=id;
	id=n+1;
	while(1){
		ll x=pre[id];
		++cnt;
		ll sx=a[x].x,sy=a[x].y,tx=a[id].x,ty=a[id].y;
		For(i,1,tx-sx)
		  S[cnt]+='D';
		For(i,1,ty-sy)
		  S[cnt]+='R';
		id=x;
		if(!x)
		  break;
	}
	write(ans);
	putchar('\n');
	_For(i,1,cnt)
	  for(auto c:S[i])
		putchar(c);
	return 0;
}
```

---

## 作者：Wei_Han (赞：0)

这东西显然不好贪心，考虑 dp，设计 $f_{x,y}$ 表示到第 $x$ 行，第 $y$ 列的最大棋子数，显然有转移，$f_{i,j} = \max_{x=1}^{i} \max_{y=1}^{j} f_{x,y} + a_{i,j}$，$a_{i,j}$ 为 $0/1$ 表示当前这一位有无棋子。

发现这样转移我们的数组显然开不下 $n\times m$，进一步地，能够发现，对于一个没有棋子的位置，我们并不需要记录他的答案，因为有无他答案都不会进行更新，所以重新设计 $f_i$ 表示到第 $i$ 个有棋子的位置的最大棋子数，可是这样就牵扯到了如何正确更新的问题。会发现，我们如果要更新一个点值，上一个点只能是他与 $(1,1)$ 位置形成的矩形内的点，这就类似于二维偏序问题了，我们对于一维排序，再用数据结构维护另一维即可，对应到本题，我们将有棋子的点按照横坐标排序，这样就只需要考虑 $1$ 到 $y$ 列中的最大值即可，要支持动态修改，区间查询，直接线段树即可。

对于求移动路径，按照 $f_i$ 的值反推就好了，具体可以参考代码实现。

复杂度 $O(n\log w)$。

```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f3f3f3f3f
#define inf 0x3f3f3f3f
#define pr putchar('\n')
#define pp putchar(' ')
#define pii pair<ll,ll>
#define pdi pair<ll,ll>
#define mem(aa,bb) memset(aa,bb,sizeof(aa))
#define fo(a,i,b) for(register ll i = a ; i <= b ; ++ i )
#define Fo(a,i,b) for(register ll i = a ; i >= b ; -- i )
#define bug(x,y) (x>=1&&x<=n&&y>=1&&y<=m&&!mp[x][y])
#define fi first
#define se second
#define pb push_back
//#pragma GCC optimize(2)
using namespace std;
typedef long long ll;
//typedef int ll;
typedef double db;
const ll N=1e6+105,M=2e5;
inline void read(ll &opp){ll x=0,t=1;char ch;ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-'){t=-1;}ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}opp=x*t;return; }
inline void wr(ll x){if(x<0){putchar('-');x=-x;}if(x>9){wr(x/10);}putchar(x%10+'0');}
inline ll reaD(){ll x=0,t=1;char ch;ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-'){t=-1;}ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*t; }

ll n,m,k,f[N];
struct node{
	ll x,y,sum;
}a[N];

inline bool cmp(node x,node y){if(x.x!=y.x)return x.x<y.x;return x.y<y.y;}
struct sgt{ll l,r,maxn,lazy;}tree[N<<2];
#define rt tree[root]
#define ls tree[root<<1]
#define rs tree[root<<1|1]
inline void pushup(ll root){rt.maxn=max(ls.maxn,rs.maxn);}
inline void build(ll root,ll l,ll r){rt.l=l,rt.r=r;ls.maxn=rs.maxn=0;if(l==r) return;ll mid=l+r>>1;build(root<<1,l,mid),build(root<<1|1,mid+1,r);pushup(root);}
inline void pd(ll root){ll lazy=rt.lazy;rt.lazy=0;ls.lazy=max(ls.lazy,lazy),rs.lazy=max(rs.lazy,lazy);ls.maxn=max(ls.maxn,lazy),rs.maxn=max(rs.maxn,lazy);}
inline void upd(ll root,ll x,ll y,ll k){ll l=rt.l,r=rt.r;if(x<=l&&y>=r){rt.maxn=max(rt.maxn,k);rt.lazy=max(rt.lazy,k);return;}ll mid=l+r>>1;pd(root);if(x<=mid) upd(root<<1,x,y,k);if(y>mid) upd(root<<1|1,x,y,k);pushup(root);}
inline ll ask(ll root,ll x,ll y){ll l=rt.l,r=rt.r;if(x<=l&&y>=r) return rt.maxn;ll mid=l+r>>1,ans=0;pd(root);if(x<=mid) ans=max(ans,ask(root<<1,x,y));if(y>mid) ans=max(ans,ask(root<<1|1,x,y));return ans;}

signed main(){
	read(n),read(m),read(k);fo(1,i,k) read(a[i].x),read(a[i].y),a[i].sum=a[i].x+a[i].y;build(1,1,max(n,m));
	sort(a+1,a+1+k,cmp);ll maxnn=0;
//	fo(1,i,k) wr(a[i].x),pp,wr(a[i].y),pr;
	fo(1,i,k){
		f[i]=ask(1,1,a[i].y)+1;
		upd(1,a[i].y,m,f[i]);
		maxnn=max(maxnn,f[i]);
	}
	ll las=-1,lassum=0;
	wr(maxnn);pr;
	string s="";
	Fo(k,i,1){
		if(las==-1&&f[i]==maxnn){
			fo(1,j,n-a[i].x) s+="D";
			fo(1,j,m-a[i].y) s+="R";
			las=i;lassum=f[i];
			continue;
		}
		if(las!=-1&&!lassum) break;
		if(f[i]==lassum-1&&las!=-1){
			fo(1,j,a[las].x-a[i].x) s+="D";
			fo(1,j,a[las].y-a[i].y) s+="R";
			las=i;lassum--;
		}
	}
	fo(1,j,a[las].x-1) s+="D";
	fo(1,j,a[las].y-1) s+="R";
	reverse(s.begin(),s.end());cout<<s;
	return 0; 
}	
``````

---

## 作者：imljw (赞：0)

### 思路
看完题目之后，我们会发现：对于两个点 $(x,y)$ 和 $(x2,y2)$，当且仅当 $x < x2$ 且 $y < y2$ 或 $x > x2$ 且 $y > y2$，我们才能同时捡到这两个点的硬币。那就把他们照 $x$ 坐标排序，求 $y$ 坐标的最长上升子序列即可。

他还要求求出具体怎么走，就用树状数组解决上升子序列，在转移时，我们通过树状数组维护前缀最大值，找到 $y$ 坐标比它小的的点中以其结尾上升子序列长度最大的那个点，这可以通过在转移时加一个编号解决，把每个点从哪转移来的记下来，就可以找出任意一个最长上升子序列了。

至于输出，~~都讲到这了，输出还不会自己写干脆别做了~~。

### 代码
仅供参考，切勿抄袭。
```cpp
#include <bits/stdc++.h>
using namespace std;
int h,w,n,f[200005],d[200005],p;
pair<int,int> t[200005];
struct node{
	int x,y,id;
}a[200005];
int lowbit(int x){
	return x&-x;
}
pair<int,int> query(int x){
	pair<int,int>res={0,0};
	for(int i=x;i;i-=lowbit(i)){
		if(t[i]>res)res=t[i];
	}
	return res;
}
void add(int x,pair<int,int> y){
	for(int i=x;i<=w;i+=lowbit(i))t[i]=max(t[i],y);
}
bool cmp(node a,node b){
	return a.x<b.x||(a.x==b.x&&a.y<b.y);
}
bool cm(node a ,node b){
	return a.id<b.id;
}
int main(){
	scanf("%d%d%d",&h,&w,&n);
	for(int i=1;i<=n;i++){
		int x,y;
		scanf("%d%d",&a[i].x,&a[i].y);
		a[i].id=i;
	}
	for(int i=1;i<=w;i++)t[i]={0,0};
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++){
		pair<int,int>c=query(a[i].y);
		c.first+=1;
		f[a[i].id]=c.second;
		c.second=a[i].id;
		add(a[i].y,c);
	}
	printf("%d\n",p=query(w).first);
	d[1]=query(w).second;
	for(int i=2;i<=p;i++)d[i]=f[d[i-1]];
	reverse(d+1,d+p+1);
	a[n+1]={h,w,n+1};
	sort(a+1,a+n+1,cm);
	d[++p]=n+1;
	int x=1,y=1;
	for(int i=1;i<=p;i++){
		while(x<a[d[i]].x)putchar('D'),x++;
		while(y<a[d[i]].y)putchar('R'),y++;
	}
	return 0;
}
```

---

## 作者：__Floze3__ (赞：0)

## 思路简述

由于只能向右或是向下移动的限制，一个格子只能从它左上角的格子转移而来。由于总格子数太多，但有硬币的格子不多，我们可以只考虑有硬币之间的格子的转移，最后对右下角特殊考虑即可。我们把硬币的坐标以行数为第一关键字，列数为第二关键字进行排序，那么一个格子就可以从之前已经扫描过的，列数小于等于它的格子转移而来，我们可以使用树状数组维护这一点。为了输出路径，我们树状数组要存储的是格子编号而非具体数量。其他细节见代码。

## 代码

```cpp
#include <bits/stdc++.h>
#define fi first
#define se second
#define mp(x, y) std::make_pair(x, y)
#define eb emplace_back
#define il inline

using ll = long long;
using pii = std::pair<int, int>;

constexpr int N = 2e5 + 5;
constexpr int mod = 1e9 + 7;
constexpr int inf = 0x3f3f3f3f;
constexpr ll infll = 0x3f3f3f3f3f3f3f3fll;

using std::cin;
using std::cout;
using std::cerr;

int n, m, k, t[N], pre[N], num[N];
pii a[N];

void print(int x) {
  if (!x) return ;
  print(pre[x]);
  for (int i = a[pre[x]].fi; i < a[x].fi; ++i) cout << 'D';
  for (int i = a[pre[x]].se; i < a[x].se; ++i) cout << 'R';
  return ;
}

il void update(int p, int id) {
  for (; p <= m; p += p & -p)
    if (num[id] > num[t[p]]) t[p] = id;
  return ;
}

il int query(int p) {
  int res = 0, id = 0;
  for (; p; p -= p & -p)
    if (num[t[p]] > res) res = num[t[p]], id = t[p];
  return id;
}

signed main() {
  cin >> n >> m >> k;
  for (int i = 1; i <= k; ++i) cin >> a[i].fi >> a[i].se;
  std::sort(a + 1, a + 1 + k);
  a[0] = mp(1, 1), a[k + 1] = mp(n, m);
  for (int i = 1; i <= k; ++i) {
    pre[i] = query(a[i].se);
    num[i] = num[pre[i]] + 1;
    update(a[i].se, i);
  }
  pre[k + 1] = query(m);
  num[k + 1] = num[pre[k + 1]];
  cout << num[k + 1] << '\n';
  print(k + 1);
  return 0;
}
```

---

## 作者：Lotus_Land (赞：0)

### 题意

有一个网格，网格中有 $H$ 行和 $W$ 列。让 $(i,j)$ 表示从上往下数第 $i$ 行，从左往右数第 $j$ 列的单元格。

在这个网格中有 $N$ 枚硬币，通过 $(R_i,C_i)$ 单元格可以拾取第 $i$ 枚硬币。

你的目标是从 $(1,1)$ 单元格开始，反复向下或向右移动一个单元格，到达 $(H,W)$ 单元格，同时尽可能多地拾取硬币。

请找出您能拾取的最大硬币数以及能达到最大值的路径之一。

### 分析


赛时打算冲一下 A 六题的，结果脑子短路了，没想到怎么记录答案。不过已经是历史最好成绩了。赛后感觉这题只有绿。

显然，对于每一行，把本行要取的硬币全部取完了才能取下面的，且下面取的硬币的 $y$ 坐标都要大于等于本行最右一枚硬币的 $y$ 坐标。容易想到把所有硬币按 $x$ 坐标排序，$x$ 坐标相同的按 $y$ 坐标排序，求 $y$ 坐标的最长不下降子序列。

重点是输出方案。只要确定了被选出的硬币，那么输出就是一件很简单的事情。设有两枚硬币 $u,v$ 是在路径上相邻的，那么这两枚硬币之间的路径就是 $|x_v-x_u|$ 个向下的移动和 $|y_v-y_u|$ 个向右的移动。

都知道动态规划能轻松解决最长不下降子序列的长度，那么怎么确定被选出的硬币是哪些呢？这在我看来是本题最大的难点。~~赛时就是因为没想出来这个然后寄了。~~

开几个名为 $pre,g,t,d,f$ 的数组。

$pre_i$ 表示路径中第 $i$ 个硬币的编号。输出要用。

$g_i$ 表示硬币 $i$ 的上一个硬币编号。$t_p$ 表示长度为 $p$ 的最长不下降子序列的最后一个硬币编号。这两个数组对于求出路径至关重要。

剩下的都是常规操作：

$d_p$ 表示长度为 $p$ 的最长不下降子序列的最后一个硬币的 $y$ 坐标。

$f_i$ 表示以硬币 $i$ 结尾的最长不下降子序列的长度。

```cpp
vector<int>pre;
void putpre(int x){
	if(!x)return;
	putpre(g[x]);
	pre.push_back(x);
}
//---------------
int p;
for(int i=1;i<=n;i++){
	p=upper_bound(d,d+len+1,b[i])-d;
	if(p>len)len=p;
	f[i]=p;
	g[i]=t[p-1];
	d[p]=b[i];
	t[p]=i;
}
cout<<len<<endl;
pre.push_back(0);
for(int i=1;i<=n;i++){
	if(f[i]==len){
		putpre(i);
		break;
	}
}
```

完整代码：

```cpp
const int N=200005;
int h,w,n;
struct node{
	int r,c;
}a[N];
int b[N];
bool cmp(node x,node y){
	if(x.r!=y.r)return x.r<y.r;
	return x.c<y.c;
}
int len,d[N],t[N],f[N],g[N];
void print(int x,int y){
	for(int i=1;i<=a[y].c-a[x].c;i++)cout<<"R";
	for(int i=1;i<=a[y].r-a[x].r;i++)cout<<"D";
}
vector<int>pre;
void putpre(int x){
	if(!x)return;
	putpre(g[x]);
	pre.push_back(x);
}
int main(){
	cin>>h>>w>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].r>>a[i].c;
	}
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<=n;i++)b[i]=a[i].c;
	int p;
	for(int i=1;i<=n;i++){
		p=upper_bound(d,d+len+1,b[i])-d;
		if(p>len)len=p;
		f[i]=p;
		g[i]=t[p-1];
		d[p]=b[i];
		t[p]=i;
	}
	cout<<len<<endl;
	pre.push_back(0);
	for(int i=1;i<=n;i++){
		if(f[i]==len){
			putpre(i);
			break;
		}
	}
	for(int i=1;i<=a[pre[1]].c-1;i++)cout<<"R";
	for(int i=1;i<=a[pre[1]].r-1;i++)cout<<"D";
	for(int i=1;i<len;i++){
		print(pre[i],pre[i+1]);
	}
	for(int i=1;i<=w-a[pre[len]].c;i++)cout<<"R";
	for(int i=1;i<=h-a[pre[len]].r;i++)cout<<"D";
	return 0;
}
```

---

## 作者：ThySecret (赞：0)

## Statement

给定一个 $H \times W$ 的网格以及 $N$ 个硬币的位置，从 $(1, 1)$ 开始每次往下或往右移动一个单元格，求到达 $(H, W)$ 单元格能拾取的最多硬币以及该路径。

## Solution

考虑如何转化问题：由于每次只能向下或者向右走，则运动路径在二维平面上看来必然是在横纵坐标上分别非严格单调递增的。换句话说，第 $i$ 个硬币可以被捡到当且仅当上一个捡到的硬币 $j$ 满足 $X_j \le X_i$ 且 $Y_j \le Y_i$，很显然的二维偏序求最长上升子序列问题。

题目中的 $H,W \le 2 \times 10^5$，朴素的 $O(n^2)$ 求法无法通过，我们采取更为优秀的二分查找法，定义 $f_i$ 表示满足长度为 $i$ 的非严格上升子序列的末尾的最小值，遍历序列时找到 $f$ 数组中最后一个小于等于当前数的**下一个数**（即大于待选数的第一个数），将这个数替换进去（因为它满足可以构成长度为 $i$ 的子序列并且值更优）。

>   这里用到了一种贪心的思想，末尾的数更小显然可以匹配更多的数。

这种做法不可以直接求出路径方案，就像最短路一样，它的 $f$ 数组在不断的变化，它代表的不是点的下标而是值的大小，类似最短路路径方案的求法，我们记录每一个更新进来的数的下标以及它的前驱，不断的回退前驱就可以得出路径方案了。

具体的做法见代码：

## [Code](https://atcoder.jp/contests/abc369/submissions/57344710)

```c++
signed main()
{
	cin >> h >> w >> n;
    for (int i = 1; i <= n; i ++) cin >> a[i].x >> a[i].y;
	sort(a + 1, a + 1 + n);

    for (int i = 1; i <= n; i ++)
    {
        if (q[len] <= a[i].y)
        {
            q[++ len] = a[i].y, id[len] = i, pre[i] = len >= 2 ? id[len - 1] : -1;
            continue;
        }

        int l = 1, r = len, res = 0;
        while (l <= r)
        {
            int mid = l + r >> 1;
            if (q[mid] > a[i].y) r = mid - 1, res = mid;
            else l = mid + 1;  
        }
        q[res] = a[i].y, id[res] = i, pre[i] = res >= 2 ? id[res - 1] : -1;	// 第一个数不存在前驱
    }
    cout << len << '\n';

    int cur = id[len], idx = len;
    while (~cur)	// 不断寻找前驱直到 cur ==
    {
        path[idx --] = cur;
        cur = pre[cur];
    }

    path[0] = 0, path[++ len] = n + 1, a[0] = {1, 1}, a[n + 1] = {h, w};	// 定义边界范围
    for (int j = 1; j <= len; j ++)
    {
        int tempx = a[path[j]].x - a[path[j - 1]].x, tempy = a[path[j]].y - a[path[j - 1]].y;
        while (tempx --) putchar('D');
        while (tempy --) putchar('R');
    }

    return 0;
}
```

---

## 作者：Union_Find (赞：0)

第一眼，直接暴力 $O(HW)$ dp。

呃，没看清数据范围。但是我们想到了一种神奇做法，因为有用的转移只有 $O(n)$ 个，所以可以离散化。但是我们不用离散化，~~因为太难写。我同学写了离散化，赛时没有调出来。~~

我们知道，如果只能向下或向右走，那么从 $i$ 号硬币走到 $j$ 号硬币，要满足 $x_i \le x_j$ 且 $y_i \le y_j$。

我们就可以定义 $f_i$ 表示你走到 $i$ 号硬币你可以得到的硬币数最大值。但是同时维护上面两个条件比较难，所以我们可以先按照 $x_i$ 为第一关键字，$y_i$ 为第二关键字进行排序，这样我们就只要满足 $y_j \le y_i 且 j < i$ 即可。

我们记录满足上述条件且 $f_j$ 最大的 $j$ 为 $pre_i$。所以我们就知道 $f_i = f_{pre_i} + 1$。最后我们就可以找到 $f_i$ 最大的 $i$，就是最后一个硬币，第一问就是 $f_i$，第二问就可以利用 $pre_i$ 求出路线。这样我们就有了一份 $O(n^2)$ 的代码。

只是，$O(n^2)$ 还不够，我们要优化。这时时间复杂度劣在单词转移是 $O(n)$ 的，我们要优化。如果只是找到 $y_j$ 比 $y_i$ 小的最大 $f_j$，就可以直接权值线段树了。但是现在我们还要求出对应的 $j$ 就比较麻烦了。

我们可以魔改一下线段树。令 $tr_p$ 表示这段区间内满足 $f_i$ 最大的 $i$。然后就可以考虑如何 pushup 了。

如果 $f_{tr_{ls}} > f_{tr_{rs}}$，那么 $tr_p = {tr_{ls}}$，否则 $tr_p = tr_{rs}$。这样 update 就可以了。而 ask 同理，就不细说了。

有一个小技巧，可以加上一个硬币，位置在 $(H,W)$，最后答案就是 $f_{n+1} - 1$。（我们假设加上的硬币是第 $n+1$ 个硬币），而最后一个拿的硬币就是第 $n+1$ 个硬币。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define il inline
#define N 200005
il ll rd(){
	ll s = 0, w = 1;
	char ch = getchar();
	for (;ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') w = -1;
	for (;ch >= '0' && ch <= '9'; ch = getchar()) s = ((s << 1) + (s << 3) + ch - '0');
	return s * w;
}
ll n, m, k, f[N], pre[N], ans, tr[N << 2], top;
char s[N << 1];
struct P{
	ll x, y, w;
}p[N];
il bool cmp(P a, P b){
	if (a.x == b.x) return a.y < b.y;
	return a.x < b.x;
}
void upd(ll p, ll l, ll r, ll x, ll k){
	if (l == x && r == x){
		if (f[tr[p]] < f[k]) tr[p] = k;
		return ;
	}if (l > x || r < x) return ;
	ll mid = (l + r) >> 1;
	upd(p << 1, l, mid, x, k), upd(p << 1 | 1, mid + 1, r, x, k);
	if (f[tr[p << 1]] < f[tr[p << 1 | 1]]) tr[p] = tr[p << 1 | 1];
	else tr[p] = tr[p << 1];
}
ll ask(ll p, ll l, ll r, ll nl, ll nr){
	if (nl <= l && r <= nr) return tr[p];
	if (nl > r || l > nr) return 0;
	ll mid = (l + r) >> 1;
	ll a = ask(p << 1, l, mid, nl, nr), b = ask(p << 1 | 1, mid + 1, r, nl, nr);
	if (f[a] > f[b]) return a;
	else return b;
}
int main(){
	n = rd(), m = rd(), k = rd();
	for (int i = 1; i <= k; i++) p[i] = P{rd(), rd(), 1};
	p[0] = P{1, 1, 0};
	sort (p + 1, p + k + 1, cmp);
	p[++k] = P{n, m, 0};
	for (int i = 1; i <= k; i++){
		ll pp = ask(1, 1, m, 1, p[i].y);
		f[i] = f[pp] + p[i].w, pre[i] = pp;
		upd(1, 1, m, p[i].y, i);
	}
	printf ("%lld\n", f[k]);
	for (int u = k; u; u = pre[u]){
		for (int i = 1; i <= p[u].y - p[pre[u]].y; i++) s[++top] = 'R';
		for (int i = 1; i <= p[u].x - p[pre[u]].x; i++) s[++top] = 'D';
	}for (;top;) cout << s[top--];
	return 0;
}

```

---

## 作者：Alcl000000 (赞：0)

为方便描述，用 $x$ 和 $y$ 代表一个点的行号和列号。

首先将每个硬币按行排序，行相同按列排序。这样对于每一个点，都可以由列号小于等于它的点转移，这样，我们可以维护前 $y$ 列的最大值，还要记录位置，每次转移取出前 $y$ 列的最大值，加上 $1$ 就是到这个点的最大值，记录前驱，再修改 $y$ 到 $n$ 列的最大值就可以。

由于最后要到 $(h,w)$，开始要在 $(1,1)$，所以我们可以强行插入点 $(h,w)$，特判 $(1,1)$。

对于最大值维护，我用的是树状数组，因为代码短。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ios ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
using namespace std;
vector<int> pos[200005],ma[1000005],val[1000005];
vector<pair<int,int> > pre[1000005];
int m[1000005],mx[1000005],my[1000005],h,w,n;
struct node{
	int x,y,ma;
}tr[1000005];
int lowbit(int x){
	return x&-x;
}
void change(int x,node nd){
	for(int i=x;i<=w;i+=lowbit(i)) {
		if(nd.ma>tr[i].ma){
			tr[i]=nd;
		}
	}
	return ;
}
node query(int x){
	node res={0,0,-1};
	for(int i=x;i;i-=lowbit(i)){
		if(tr[i].ma>res.ma){
			res=tr[i];
		}
	}
	return res;
}
void output(int x,int y){
	if(pre[x][y].first==0&&pre[x][y].second==0){
		int a=x-1,b=pos[x][y]-1;
		while(a--) cout<<"D";
		while(b--) cout<<"R";
		return ;
	}
	output(pre[x][y].first,pre[x][y].second);
	int a=x-pre[x][y].first,b=pos[x][y]-pos[pre[x][y].first][pre[x][y].second];
	while(a--) cout<<"D";
	while(b--) cout<<"R";
}
signed main(){
	ios;
	cin>>h>>w>>n;
	for(int i=1;i<=n;i++){
		int r,c;
		cin>>r>>c;
		pos[r].push_back(c);
		ma[r].push_back(0);
		val[r].push_back(1);
		pre[r].push_back({0,0});
	}
	++n;
	pos[h].push_back(w);
	ma[h].push_back(0);
	val[h].push_back(0);
	pre[h].push_back({0,0});
	for(int i=1;i<=h;i++) sort(pos[i].begin(),pos[i].end());
	for(int i=1;i<=h;i++){
		for(int j=0;j<ma[i].size();j++){
			node bma=query(pos[i][j]);
			ma[i][j]=val[i][j]+bma.ma;
			pre[i][j]={bma.x,bma.y};
			bma.ma=ma[i][j];
			change(pos[i][j],{i,j,ma[i][j]});
		}
	}
	cout<<ma[h][pos[h].size()-1]<<'\n';
	output(h,pos[h].size()-1);
	return 0;
}
```

---

## 作者：ma_niu_bi (赞：0)

### F-Gather Coins

#### 题意

给定一个 $H\times W$ 的网格图，上面有 $n$ 个格子有金币。

只能向右和向下走，求从 $(1,1)$ 走到 $(H,W)$ 最多能捡到多少金币，并给出一种路径。

#### 思路

考虑对金币动态规划，每个金币 $(x,y)$ 只能从金币 $(p,q)(p\le x)(q \le y)$ 转移过来，转移方程：

$$
dp_i = \max dp_j+1
$$

暴力转移时间复杂度 $O(n^2)$，不能通过，而且存在后效性。

发现转移限制为二维偏序，可先把 $x$ 从小到大排序，再用线段树维护所有 $y$。统计最小值及最小值的位置。

路径可记录一个 $pre_i$ 表示 $i$ 从哪里转移过来，倒着输出路径即可。

坑点：排序时不能只排 $x$，当 $x$ 相同时要按 $y$ 从小到大排序。

#### 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
#define ll long long
const int N = 2e5 + 5;
int h, w, n;
struct P {int x, y;};
struct segt {
    struct node {
        int l, r, mx, MX;
    } t[N << 2];
    #define ls (p << 1)
    #define rs (p << 1 | 1)
    friend node operator + (node a, node b) {
        node res; res.l = a.l, res.r = b.r;
        if (a.mx > b.mx) res.mx = a.mx, res.MX = a.MX;
        else res.mx = b.mx, res.MX = b.MX;
        return res;
    }
    void build(int p, int l, int r) {
        t[p].l = l, t[p].r = r;
        if (l == r) return;
        int mid = (l + r) >> 1;
        build(ls, l, mid);
        build(rs, mid + 1, r);
    }
    void modify(int p, int id, int v, int val) {
        if (t[p].l == t[p].r) {
            t[p].mx = max(t[p].mx, v);
            if (t[p].mx == v) t[p].MX = val;
            return ;
        }
        if (id <= t[ls].r) modify(ls, id, v, val);
        else modify(rs, id, v, val);
        t[p] = t[ls] + t[rs];   
    }
    node query(int p, int l, int r) {
        if (l <= t[p].l && t[p].r <= r) return t[p];
        node res; res.l = -1;
        if (t[ls].r >= l) res = query(ls, l, r);
        if (t[rs].l <= r) {
            if (res.l == -1) res = query(rs, l, r);
            else res = res + query(rs, l, r);
        }
        return res;
    }
} T;
P a[N];
bool cmp(P A, P B) {
    if (A.x == B.x) return A.y < B.y;
    return A.x < B.x;
}
int dp[N], pre[N], ans, lst;
vector <int> path;
string ANS[N];
void solve() {
    cin >> h >> w >> n;
    for (int i = 1; i <= n; i ++) cin >> a[i].x >> a[i].y;
    a[0].x = 1, a[0].y = 1;
    a[n + 1].x = h, a[n + 1].y = w;
    sort(a + 1, a + n + 1, cmp);
    T.build(1, 1, max(h, w));
    T.modify(1, a[1].y, 1, 1);
    pre[1] = 0, dp[1] = 1, ans = 1, lst = 1;
    for (int i = 2; i <= n; i ++) {
        segt::node res = T.query(1, 1, a[i].y);
        dp[i] = dp[res.MX] + 1;
        pre[i] = res.MX;
        if (dp[i] > ans) {
            ans = dp[i];
            lst = i;
        }
        T.modify(1, a[i].y, dp[i], i);
    }
    pre[n + 1] = lst;
    int now = n + 1, tot = 0;
    while (now) {
        lst = pre[now], tot ++;
        for (int i = 1; i <= a[now].x - a[lst].x; i ++) ANS[tot] += 'D';
        for (int i = 1; i <= a[now].y - a[lst].y; i ++) ANS[tot] += 'R';
        now = pre[now];
    }
    cout << ans << "\n";
    for (int i = tot; i >= 1; i --) 
        cout << ANS[i];
    cout << "\n";
}
signed main() {
    int T = 1;
    // cin >> T;
    while (T --) 
        solve();
    return 0;
}
```

---

## 作者：卡卡卡卡卡卡 (赞：0)

## 题解：
一道水题，可惜考场没调出来，针对一个金币 $(r,c)$ 到另一个金币 $(r',c')$ 定要满足 $r\leq r'$ 且要满足 $c \leq c'$。

两个变量不太好维护，便考虑针对 $r$ 为第一关键字排序，保证 $r\leq r'$，接下来考虑 $c\leq c'$。

无非是求最长的 $c\leq c'$ 的序列长度，如果直接 ``dp`` 是 $\mathcal O(N^2)$ 的 会 ``TLE``，于是我们考虑树状数组维护前面 ``dp`` 的最大值，时间复杂度降为 $\mathcal O(N \log N )$ 可以接受。

在中间记录一下编号即可解决第二问。

## CODE：
```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,m,q,last[1000005],tot;
char ans[5000005];
struct node{
    long long x,y;
}a[1000005];
bool cmp(node a,node b) { return a.x < b.x || (a.x == b.x && a.y < b.y); }
namespace BIT
{
    long long tr[1000005],d[1000005];
    long long lowbit(long long x){return x&(-x);}
    void add(long long x,long long y,long long id)
    {
        for (; x <= m; x += lowbit (x))
            if (tr[x]<y) tr[x]=y,d[x]=id;
    }
    pair<long long,long long> ask(long long x)
    {
        long long pos=0,ans=0;
        for(;x;x-=lowbit(x))
        {
            if(ans<tr[x])ans=tr[x],pos=d[x];
        }
        return {pos,ans};
    }
}
int main()
{
    cin >> n >> m >> q;
    for(long long i=1;i<=q;i++) cin>>a[i].x>>a[i].y;
    sort (a+1,a+q+1,cmp);
    for (long long i=1;i<=q;i++)
    {
        pair<long long,long long> j=BIT::ask(a[i].y);
        last[i]=j.first;
        BIT::add(a[i].y,j.second+1,i);
    }
    pair<long long, long long> ed=BIT::ask (m);
    long long now=ed.first,cnt=ed.second,x=n,y=m;
    for(long long i=x;i>a[now].x;i--) ans[++tot]='D';
    for(long long i=y;i>a[now].y;i--) ans[++tot]='R';
    x=a[now].x;
    y=a[now].y;
    while(last[now])
    {
        long long t=last[now];
        for(long long i=x;i>a[t].x;i--) ans[++tot]='D';
        for(long long i=y;i>a[t].y;i--) ans[++tot]='R';
        x = a[t].x; y = a[t].y;
        now = t;
    }
    for(long long i=x;i>1;i--) ans[++tot]='R';
    for(long long i=y;i>1;i--) ans[++tot]='R';
    reverse(ans+1,ans+1+tot);
    cout<<cnt<<endl;
    for(int i=1;i<=tot;i++) cout<<ans[i];
}
```

---

