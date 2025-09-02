# 展覧会 (Exhibition)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joi2019ho/tasks/joi2019ho_b

あなたは，絵の展覧会を開催しようとしている．展覧会では，いくつかの絵を額縁に入れ，左から右に一列に並べて展示する．

展覧会で展示する候補となる絵が $ N $ 枚あり，$ 1 $ から $ N $ までの番号が付けられている．絵 $ i $ ($ 1\ \leqq\ i\ \leqq\ N $) の大きさは $ S_i $，価値は $ V_i $ である．

また，これらの絵を入れるための額縁が $ M $ 枚あり，$ 1 $ から $ M $ までの番号が付けられている．額縁 $ j $ ($ 1\ \leqq\ j\ \leqq\ M $) の大きさは $ C_j $ である．額縁 $ j $ には，大きさが $ C_j $ 以下の絵のみを入れることができる．$ 1 $ 枚の額縁には高々 $ 1 $ 枚の絵しか入れることができない．

展示する絵はすべて何らかの額縁に入っていなければならない．見栄えを良くするため，展示する絵は以下の条件を満たさなければならない：

- 左右に隣り合うどの $ 2 $ 枚の絵についても，右側の絵が入っている額縁の大きさは左側の絵が入っている額縁の大きさ以上である．
- 左右に隣り合うどの $ 2 $ 枚の絵についても，右側の絵の価値は左側の絵の価値以上である．

あなたは，できるだけ多くの絵を展示したい．

展示候補の絵の枚数，額縁の枚数，及びそれらの大きさや価値が与えられたとき，展示する絵の枚数の最大値を求めるプログラムを作成せよ．

- - - - - -

## 说明/提示

### 制約

- $ 1\ \leqq\ N\ \leqq\ 100\,000 $．
- $ 1\ \leqq\ M\ \leqq\ 100\,000 $．
- $ 1\ \leqq\ S_i\ \leqq\ 1\,000\,000\,000 $ ($ 1\ \leqq\ i\ \leqq\ N $)．
- $ 1\ \leqq\ V_i\ \leqq\ 1\,000\,000\,000 $ ($ 1\ \leqq\ i\ \leqq\ N $)．
- $ 1\ \leqq\ C_j\ \leqq\ 1\,000\,000\,000 $ ($ 1\ \leqq\ j\ \leqq\ M $)．

### 小課題

1. ($ 10 $ 点) $ N\ \leqq\ 10 $，$ M\ \leqq\ 10 $．
2. ($ 40 $ 点) $ N\ \leqq\ 1\,000 $，$ M\ \leqq\ 1\,000 $．
3. ($ 50 $ 点) 追加の制約はない．

- - - - - -

### Sample Explanation 1

この入出力例では，左から順に (絵 $ 2 $, 額縁 $ 2 $)，(絵 $ 1 $, 額縁 $ 3 $) と並べることで，$ 2 $ 枚の絵を展示することができる．$ 3 $ 枚以上の絵を展示することはできないので，$ 2 $ を出力する．ここで，(絵 $ i $, 額縁 $ j $) は，額縁 $ j $ に入った絵 $ i $ を表す． - - - - - -

### Sample Explanation 2

\- - - - - -

### Sample Explanation 3

\- - - - - -

## 样例 #1

### 输入

```
3 4
10 20
5 1
3 5
4
6
10
4```

### 输出

```
2```

## 样例 #2

### 输入

```
3 2
1 2
1 2
1 2
1
1```

### 输出

```
2```

## 样例 #3

### 输入

```
4 2
28 1
8 8
6 10
16 9
4
3```

### 输出

```
0```

## 样例 #4

### 输入

```
8 8
508917604 35617051
501958939 840246141
485338402 32896484
957730250 357542366
904165504 137209882
684085683 775621730
552953629 20004459
125090903 607302990
433255278
979756183
28423637
856448848
276518245
314201319
666094038
149542543```

### 输出

```
3```

# 题解

## 作者：Msents (赞：2)

介绍一种构式还烧脑子的做法。

先将数据处理一下，将画框按大小排序，将画按美观度排序。

然后就可以通过二分，来判断一张画可以放在第几个画框及之后。

先无脑 dp，设 $f_{i,j}$ 为处理到了第 $i$ 张画，最后一张画放在第 $j$ 个画框里，此时放入的最大的画的个数，式子：

$$f_{i,\max(s_i,j+1)}=\max(f_{i-1,j+1},f_{i,\max(s_i,j+1)})$$

这样能拿一半的分数，观察做完 dp 时的数组，可以发现 $f_{i,j}-f_{i,j-1}\le 1$，这也意味着每次操作 dp 数组，实际上是去掉末尾，将 $[s_i+1,m-1]$ 这一块区域的元素加一，再在这个区间前插入一个元素。

于是可以用平衡树瞎瘠薄维护，并拿下[最慢解](/record/list?pid=AT_joi2019ho_b&orderBy=1&status=&page=2)。

哦对了排序别忘了美观度相等时按大小再拍一次不然爆零哈哈，，

码：

```cpp
#include<bits/stdc++.h>
using namespace std;
using ullong=unsigned long long;
const int MaxN=100005;
mt19937_64 rander(chrono::steady_clock::now().time_since_epoch().count());
int n,m;
struct Paint{
	int s,v;
}a[MaxN+1];
int b[MaxN+1];
struct Node{
	int val,max,tag,size;
	ullong heap;
	int lc,rc;
}tree[MaxN+1];
void PushDown(int u){
	if(tree[u].tag){
		if(tree[u].lc){
			tree[tree[u].lc].val+=tree[u].tag;
			tree[tree[u].lc].max+=tree[u].tag;
			tree[tree[u].lc].tag+=tree[u].tag;
		}
		if(tree[u].rc){
			tree[tree[u].rc].val+=tree[u].tag;
			tree[tree[u].rc].max+=tree[u].tag;
			tree[tree[u].rc].tag+=tree[u].tag;
		}
		tree[u].tag=0;
	}
}
void PushUp(int u){
	tree[u].max=tree[u].val;
	if(tree[u].lc)tree[u].max=max(tree[u].max,tree[tree[u].lc].max);
	if(tree[u].rc)tree[u].max=max(tree[u].max,tree[tree[u].rc].max);
	tree[u].size=1;
	if(tree[u].lc)tree[u].size+=tree[tree[u].lc].size;
	if(tree[u].rc)tree[u].size+=tree[tree[u].rc].size;
}
pair<int,int>Split(int u,int size){
	if(!u)return make_pair(0,0);
	PushDown(u);
	if(size<=tree[tree[u].lc].size){
		auto pi=Split(tree[u].lc,size);
		tree[u].lc=pi.second;
		PushUp(u);
		return make_pair(pi.first,u);
	}else{
		auto pi=Split(tree[u].rc,size-tree[tree[u].lc].size-1);
		tree[u].rc=pi.first;
		PushUp(u);
		return make_pair(u,pi.second);
	}
}
int Merge(int u,int v){
	if(!u||!v)return u+v;
	if(tree[u].heap<tree[v].heap){
		PushDown(u);
		tree[u].rc=Merge(tree[u].rc,v);
		PushUp(u);
		return u;
	}else{
		PushDown(v);
		tree[v].lc=Merge(u,tree[v].lc);
		PushUp(v);
		return v;
	}
}
void Solve(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i].s>>a[i].v;
	for(int i=1;i<=m;i++)cin>>b[i];
	sort(a+1,a+1+n,[](Paint a,Paint b){return a.v==b.v?a.s<b.s:a.v<b.v;});
	sort(b+1,b+1+m);
	for(int i=1;i<=n;i++)a[i].s=lower_bound(b+1,b+1+m,a[i].s)-b;
	int rt=0;
	for(int i=1;i<=m+1;i++){
		tree[i].size=1;
		tree[i].heap=rander();
		rt=Merge(rt,i);
	}
	for(int i=1;i<=n;i++){
		if(a[i].s>m)continue;
		auto pi1=Split(rt,a[i].s);
		auto pi2=Split(pi1.second,1);
		auto pi3=Split(pi2.second,m-a[i].s-1);
		int p1=pi1.first,p2=pi2.first,p3=pi3.first,p4=pi3.second;
		tree[p4].val=tree[p4].max=tree[p2].val+1;
		tree[p2].val=tree[p2].max=tree[p1].max+1;
		tree[p3].val++;
		tree[p3].tag++;
		tree[p3].max++;
		rt=Merge(p1,Merge(p2,Merge(p4,p3)));
	}
	cout<<tree[rt].max;
	
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	Solve();
	return 0;
}
```

---

## 作者：tXX_F (赞：2)

#  AT_joi2019ho_b 展覧会 (Exhibition)

## 解题思路

由题意可知，最后展出的画，画框的大小和画的美观度都是单调不下降的。考虑倒序操作，选择当前画中美观值最大的且大小小于画框的画放入。如果画被放完了，那么直接输出答案并结束程序。

### 证明：

因为要使展出的画尽可能多，所以最后一幅画的美观度以及画框的大小要最大，之后的画的美观度即大小也要选剩下画中的最大者，这样才能保证选法最优。

## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
char buf[1048576], *p1, *p2;
template<typename T>inline void Super_Quick_Read(T &x) {
	bool f = 1;
	x = 0;
	char ch = (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2) ? 0 : *p1++);
	while (ch < '0' || ch > '9') {
		if (ch == '-') f = !f;
		ch = (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2) ? 0 : *p1++);
	}
	while (ch >= '0' && ch <= '9')x = (x << 1) + (x << 3) + (ch ^ 48), ch = (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2) ? 0 : *p1++);
	x = (f ? x : -x);
	return;
}
template<typename T>inline void Quick_Write(T x) {
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) Quick_Write(x / 10);
	putchar(x % 10 + '0');
	return;
}
struct Project_Picture {
	int S, V;
} Pictures[100005];
int N, M, C[100005];
int Answer;
inline bool Compar(Project_Picture A, Project_Picture B) {
	if (A.V == B.V)return A.S > B.S;
	return A.V > B.V;
}
signed main() {
	Super_Quick_Read(N), Super_Quick_Read(M);
	for (register int i = 1; i <= N; ++i) Super_Quick_Read(Pictures[i].S), Super_Quick_Read(Pictures[i].V);
	for (register int i = 1; i <= M; ++i) Super_Quick_Read(C[i]);
	sort(Pictures + 1, Pictures + N + 1, Compar), sort(C + 1, C + M + 1);
	for (register int i = M, now = 1; i >= 0; i--) {
		while (now <= N && Pictures[now].S > C[i]) ++now;
		if (now > N) Quick_Write(Answer), exit(0);
		++now, ++Answer;
	}
	return 0;
}
```

---

## 作者：huangrenheluogu (赞：1)

贪心。

画框从大到小排序之后，从右往左填画，相当于是第 $i$ 幅画需要大小不超过 $c_i$，并且第 $i$ 幅画的美丽度不大于第 $i-1$ 幅的。

可以把画按照美丽度排序，美丽度相同，大小大的放在前面（前面大小限制宽松）。贪心放入，能放入就放入，不能放入就跳过。证明就是放了之后肯定不劣。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e6 + 5;
int n, m, b[N], t;
struct node{
    int a, b;
}a[N];
signed main(){
    // freopen("data.in", "r", stdin);
    // freopen("code.out", "w", stdout);
    scanf("%lld%lld", &n, &m);
    for(int i = 1; i <= n; i++){
        scanf("%lld%lld", &a[i].a, &a[i].b);
    }    
    for(int i = 1; i <= m; i++){
        scanf("%lld", &b[i]);
    }
    sort(a + 1, a + n + 1, [&](node x, node y){
        if(x.b != y.b) return x.b > y.b;
        return x.a > y.a;
    });
    sort(b + 1, b + m + 1, [&](int x, int y){
        return x > y;
    });
    for(int i = 1; i <= n && t < m; i++){
        if(a[i].a <= b[t + 1]){
            t++;
        }
    }
    printf("%lld\n", t);
    return 0;   
}
```

---

## 作者：Evanth (赞：1)

## 翻译
有一个画展，其中有 $n$ 幅画，$m$ 个画框。

每幅画有一个大小 $s_i$ 和一个美观度 $v_i$。每个画框有一个大小 $c_j$。

一幅画能被装进一个画框，当且仅当画的大小不大于画框的大小。

考虑到美观因素，对于展出的任意两幅相邻的画要满足：
- 右边的画框大小不小于左边的画框；

- 右边的画的美观度不小于左边的画的美观度。

问最多能展出多少幅画。

## 分析
我们可以先考虑题目给出的限制条件。

很显然，要求满足的条件本质就是画的美观度以及画框的大小都是**单调不降**的。

于是我们先将画框按照从小到大排序。这样条件就解决了一个维度了。

我们可以模拟一个队列之类的东西，初始没有画框。

每次加入一个画框时，选出**当前 $s_i$ 小于等于这个画框且 $v_i$ 最小**的画，并且使用这个画框。当然如果没有符合条件的画那就 skip。

怎么实现呢？离散化之后树状数组之类的维护一下即可。

这样的贪心很显然是最优的，因为对于每次决策我们能发现，选择其它的画都是不优的。

---

## 作者：ethan0328 (赞：1)

## 题意

展览有 $n$ 幅画。每幅画有大小 $S_i$ 和美观度 $V_i$。

有 $m$ 个画框，每个画框的大小为 $C_i$。只有大小不超过 $C_i$ 的画才能放入画框 $i$ 中。

选出 $k$ 个画和画框，满足对于任意两幅相邻的画，画框大小单调不上升，画的美观度单调不上升。求 $k$ 的最大值。

## 思路

考虑一个贪心。最后选取的画框必为排序后最大的几个。考虑将画框排序，并依次放入画。

显然，先放美观度大的画，美观度相同时先放大小大的。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
struct node
{
	int s,v;
	bool operator <(const node x) const
	{
		if(v==x.v)
		{
			return s>x.s;
		}else
		{
			return v>x.v;
		}
	}
};
int n,m,ans,c[N];
node a[N];
int main()
{
	int x;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i].s>>a[i].v;
	}
	for(int i=1;i<=m;i++)
	{
		cin>>c[i];
	}
	sort(a+1,a+1+n);
	sort(c+1,c+1+m);
	x=1;
	for(int i=m;i;i--)
	{
		while(x<=n&&a[x].s>c[i])
		{
			x++;
		}
		if(x>n)
		{
			break;
		}
		x++;
		ans++;
	}
	cout<<ans;
}
```


---

