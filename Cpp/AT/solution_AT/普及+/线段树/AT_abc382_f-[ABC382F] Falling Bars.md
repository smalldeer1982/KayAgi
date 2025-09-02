# [ABC382F] Falling Bars

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc382/tasks/abc382_f

$ H $ 行 $ W $ 列のグリッドがあります。 このグリッドの上から $ i\ (1\leq\ i\leq\ H) $ 行目、左から $ j\ (1\leq\ j\leq\ W) $ 列目のマスを $ (i,j) $ と表記します。

$ 1 $ から $ N $ までの番号が付けられた $ N $ 個の横長のバーがグリッド上に置かれています。 バー $ i $ は $ 1\times\ 1 $ のブロックが横に $ L_i $ 個繋がった形をしており、その左端のブロックは最初マス $ (R_i,C_i) $ 上にあります。 すなわち、バー $ i $ は最初マス $ (R_i,C_i),\ (R_i,C_i+1),\ \dots,\ (R_i,C_i+L_i-1) $ を占めています。 ここで、相異なる $ 2 $ つのバーに占められているマスは存在しないことが保証されます。

現在の時刻は $ t=0 $ です。 非負整数 $ n $ を用いて $ t=0.5+n $ と表されるようなすべての時刻において、$ i=1,2,\dots,N $ の順に以下のことが起こります。

- バー $ i $ が一番下の行（$ H $ 行目）になく、かつバー $ i $ が占める各マスの $ 1 $ つ下のマスをどのバーも占めていない場合、バー $ i $ 全体が $ 1 $ マス分下に移動する。 すなわち、その時点でバー $ i $ が占めているマスが $ (r,C_i),(r,C_i+1),\dots,(r,C_i+L_i-1)\ (r\ <\ H) $ であり、どの $ j\ (0\leq\ j\leq\ L_i-1) $ についてもマス $ (r+1,C_i+j) $ を占めているバーが存在しないならば、 バー $ i $ の占めるマスが $ (r+1,C_i),(r+1,C_i+1),\dots,(r+1,C_i+L_i-1) $ に変化する。
- そうでないならば、何も起こらない。
 
$ t=10^{100} $ においてバー $ i $ が占めているマスを $ (R'_i,C_i),\ (R'_i,C_i+1),\ \dots,\ (R'_i,C_i+L_i-1) $ とします。 $ R'_1,R'_2,\dots,R'_N $ を求めてください。

## 说明/提示

### 制約

- $ 1\leq\ H,W\ \leq\ 2\times\ 10^5 $
- $ 1\leq\ N\ \leq\ 2\times\ 10^5 $
- $ 1\leq\ R_i\leq\ H $
- $ 1\leq\ C_i\leq\ W $
- $ 1\leq\ L_i\leq\ W-C_i+1 $
- 与えられる初期状態において、相異なる $ 2 $ つのバーに占められているマスは存在しない
- 入力は全て整数
 
### Sample Explanation 1

以下の $ 3 $ つの図は左から順に $ t=0,1,2 $ でのグリッドの様子を表しています。 色の塗られた長方形は各バーを表し、長方形の中に書かれた数字はそのバーの番号です。 !\[\](https://img.atcoder.jp/abc382/57581b182e43915bce2b78747acfa2a6.png) グリッドの状態の変化は以下の通り説明されます。 - $ t=0.5 $: - $ i=1 $: バー $ 1 $ が占める各マスの $ 1 $ つ下のマスである $ (2,2),(2,3),(2,4) $ のうち、$ (2,2) $ がバー $ 3 $ に、$ (2,4) $ がバー $ 4 $ にそれぞれ占められているため、何も起こらない。 - $ i=2 $: バー $ 2 $ が占める各マスの $ 1 $ つ下のマスである $ (4,2),(4,3) $ がいずれも他のバーに占められていないため、バー $ 2 $ 全体が $ 1 $ マス分下に移動する。 - $ i=3 $: バー $ 3 $ が占める各マスの $ 1 $ つ下のマスである $ (3,1),(3,2) $ がいずれも他のバーに占められていないため、バー $ 3 $ 全体が $ 1 $ マス分下に移動する。 - $ i=4 $: バー $ 4 $ が占めるマスの $ 1 $ つ下のマスである $ (3,4) $ が他のバーに占められていないため、バー $ 4 $ 全体が $ 1 $ マス分下に移動する。 - $ t=1.5 $: - $ i=1 $: バー $ 1 $ が占める各マスの $ 1 $ つ下のマスである $ (2,2),(2,3),(2,4) $ がいずれも他のバーに占められていないため、バー $ 1 $ 全体が $ 1 $ マス分下に移動する。 - $ i=2 $: バー $ 2 $ は一番下の行にあるため、何も起こらない。 - $ i=3 $: バー $ 3 $ が占める各マスの $ 1 $ つ下のマスである $ (4,1),(4,2) $ のうち、$ (4,2) $ がバー $ 2 $ に占められているため、何も起こらない。 - $ i=4 $: バー $ 4 $ が占めるマスの $ 1 $ つ下のマスである $ (4,4) $ が他のバーに占められていないため、バー $ 4 $ 全体が $ 1 $ マス分下に移動する。 $ t=2.5,3.5,\dots $ においては $ 1 $ つ下のマスがすべて空いているようなバーが存在せず、何も起こらないため、$ t=10^{100} $ でのグリッドの状態は $ t=2 $ でのグリッドの状態（上図における一番右の状態）と同じです。 よって、$ R'_1=2,R'_2=4,R'_3=3,R'_4=4 $ です。

## 样例 #1

### 输入

```
4 4 4
1 2 3
3 2 2
2 1 2
2 4 1```

### 输出

```
2
4
3
4```

## 样例 #2

### 输入

```
382 382 3
3 3 3
8 8 8
2 2 2```

### 输出

```
382
382
381```

## 样例 #3

### 输入

```
5 10 8
2 2 1
4 3 1
4 8 2
1 2 2
2 5 3
5 4 3
4 5 2
1 5 2```

### 输出

```
5
5
5
4
3
5
4
2```

# 题解

## 作者：Down_syndrome (赞：11)

你是一个默默无闻的 OIer。

你自认为你自己很菜，菜到 NOIP2024 都拿不了省一。

你在早上花费绝大多数时间死磕 T1，换来的却是怎么都过不了的大样例。

你开始思考要不要 AFO，开始思考这一路走来的意义是什么。

晚上 8 点，你发现今天的 abc 照常。或许是因为习惯，你准备 ur 报名打一打涨信心。

或许还是有点功底在的，你有些艰难地切掉了前五题，来到了 f。

你开始思考这道难度高达 1443（尽管 e 更难）的题目。

题目大意是一个平面上有 $N$ 个砖块，当一个砖块下面的位置都是空的时候，这个砖块会掉落。最后询问每个砖块结束掉落后再哪一层。

你尝试用一个 $H\times W$ 的矩阵刻画每个位置的状态。

具体的，你想要按 $R_i$ 从大到小考虑每个砖块，然后考虑它会掉落到哪一层。因为只有 $R_j>R_i$，第 $j$ 个砖块才会挡住第 $i$ 个砖块，而我们是按照 $R_i$ 从大到小考虑的，所以在 $i$ 之前，我们已经确定了所有满足条件的砖块 $j$ 的位置，所以这样做是对的。

那怎么才能知道 $i$ 会掉落在那一层呢？

你考虑枚举砖块 $i$ 的每一个位置，对于每个位置都查询该位置上目前最高的砖块的位置，然后取最小值再减一，就是砖块 $i$ 所在的位置。

你发现求区间最小值是你的拿手好戏，于是你不到 10 分钟就敲出了一个线段树模板。

你进而发现 $H\times W$ 的空间并不能开的下，但是你发现你实际只用一个长为 $W$ 的数组就能刻画一切事情。

你给这个数组取名为 $A$，令 $A_i$ 表示到目前为止第 $i$ 列上最高的砖块的位置。一开始，你给 $A$ 中的所有值都赋为 $H+1$。

你像上述内容一样，按 $R_i$ 从大到小枚举每个砖块，令 $ANS_i\gets\min_{j=C_i}^{C_i+L_i-1} A_j-1$，然后再令 $\forall j\in[C_i,C_i+L_i)\cup \Z,A_j\gets ANS_i$，使用线段树维护，然后按原来的顺序输出 $ANS$。

留给你的时间不多了，你在比赛结束前火速码好了以下代码，还贴心地写上了注释。

```cpp
#include<bits/stdc++.h>
#define ls (k<<1)
#define rs (k<<1|1)
using namespace std;
const int N=2e5+5;
int h,w,n,r,c,l,ans[N];
struct node{
	int id,p,l,r;
}d[N];//因为要整体排序，用一个结构体存 
bool cmp(node a,node b){
	return a.p>b.p;
} 
struct seg{
	int l,r,mina,tag;
}t[N<<2];//线段树，记得开 4 倍空间 
void change(int k,int v){//以下都是区间修改区间查询最小值线段树模板，不会的可以看 P1253 
	t[k].mina=t[k].tag=v;
}
void push_up(int k){
	t[k].mina=min(t[ls].mina,t[rs].mina);
}
void push_down(int k){
	if(~t[k].tag){
		change(ls,t[k].tag);
		change(rs,t[k].tag);
		t[k].tag=-1;
	}
}
void build(int k,int l,int r){
	t[k].l=l;
	t[k].r=r;
	t[k].mina=h+1;
	t[k].tag=-1;
	if(l==r) return;
	int mid=l+r>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
}
void modify(int k,int l,int r,int v){
	if(r<t[k].l||t[k].r<l) return;
	if(l<=t[k].l&&t[k].r<=r){
		change(k,v);
		return;
	}
	push_down(k);
	modify(ls,l,r,v);
	modify(rs,l,r,v);
	push_up(k);
}
int query(int k,int l,int r){
	if(r<t[k].l||t[k].r<l) return 1e9;
	if(l<=t[k].l&&t[k].r<=r) return t[k].mina;
	push_down(k);
	return min(query(ls,l,r),query(rs,l,r));
}
int main(){
	scanf("%d%d%d",&h,&w,&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d%d",&r,&c,&l);
		d[i]={i,r,c,c+l-1};//封进结构体排序 
	}
	sort(d+1,d+n+1,cmp);
	build(1,1,w);
	for(int i=1;i<=n;i++){
		ans[d[i].id]=query(1,d[i].l,d[i].r)-1;//计算第 i 个砖块的答案 
		modify(1,d[i].l,d[i].r,ans[d[i].id]);//更新这些位置上的最小值 
	}
	for(int i=1;i<=n;i++) printf("%d\n",ans[i]);//按照原顺序输出 
	return 0;
}
```

或许你会想：如果 NOIP 也能 abc382 这样一帆风顺就好了。但是相信吧，朋友。你的成绩不会辜负你的热爱，只要你坚持走下去，你总能在赛场上闪烁出最耀眼的火光。

愿大家都 rp+++！

（顺带一提这并不是我的个人经历，但可能是千千万万个“你”）

---

## 作者：_RainCappuccino_ (赞：6)

> $\mathtt{TAG}$：CDQ，DP

题意实际上就是每个横块会自然下落，问最终的纵坐标。

以下横块的初始纵坐标表示为 $x_i$，左端点横坐标为 $l_i$，右端点横坐标为 $r_i = l_i + l_i - 1$。

首先，所有的块最终的高度一定为在横坐标区间上与之相交且初始纵坐标大于该块初始纵坐标的块的最终高度 $- 1$。

用式子表示出来即为：$h_i = \min(h_j) - 1, x_i > x_j,l_i \le r_j,r_i \ge l_j$。

发现这里转移条件是三维偏序，不难想到用 cdq 进行解决。

首先先按 $x$ 作为第一关键字排序。

即分治处理，对于区间 $(l, r)$，处理 $(l, mid)$ 对 $(mid + 1, r)$ 的贡献，此时对 $(l, mid)$ 区间按照 $r$ 降序排序，$(mid + 1, r)$ 区间按照 $l$ 降序排序。

然后双指针将满足条件 $l_i \le r_j$ 的 $(l, mid)$ 区间中的元素对应的 $h_j$ 加入某个数据结构（此题用的是树状数组进行查询，当然线段树也可以）。完毕后进行查询，更新当前元素的 $h_i$。

这一部分的时间复杂度是 $O(len \log len),len = r - l + 1$。

对于区间 $(l, r)$ 处理完毕后，再按照同样的方式对区间 $(l, mid)$ 和 $(mid + 1, r)$ 的位置进行更新。

总的复杂度即为 $O(n\log^2 n)$。

注意这里转移有顺序要求所以先递归处理 $(l, mid)$ 再处理跨块的转移，最后处理 $(mid + 1, r)$ 的部分。

下面给出我的写法，供大家参考：

这里我将最底部设成 $1$，所以式子会转化成取 $h_i = \max(h_j) - 1, x_i > x_j,l_i \le r_j,r_i \ge l_j$。

```cpp
struct node {
    int x , l , r , dp , id; // 存 id 这样方便输出
}a[N] , b[N];
bool cmp0(node x , node y) {
    return x.x > y.x;
}
bool cmp(node x , node y) {
    return x.l > y.l;
}
bool cmp2(node x , node y) {
    return x.r > y.r;
}
struct bit { // 树状数组
    int c[N] , len;
#define l(x) (x & -x)
    void add(int x , int d) {
        for (int i = x; i <= len; i += l(i)) c[i] = max(c[i] , d);
    }
    void clean(int x) {
        for (int i = x; i <= len; i += l(i)) c[i] = 0;
    }
    int getx(int x) {
        int res = 0;
        for (int i = x; i; i -= l(i)) res = max(res , c[i]);
        return res;
    }
}t;
void cdq(int l , int r) {
    if (l == r) return;
    int mid = l + r >> 1;
    sort(a + l , a + 1 + r , cmp0);
    cdq(l , mid);
    sort(a + l , a + mid + 1 , cmp2) , sort(a + mid + 1 , a + 1 + r , cmp);
    int j = l;
    for (int i = mid + 1; i <= r; i++) {
        while (a[j].r >= a[i].l && j <= mid) { // l[i] <= r[j]
            t.add(a[j].l , a[j].dp);
            j++;
        }
        a[i].dp = max(a[i].dp , t.getx(a[i].r) + 1); // r[i] >= l[j]
    }
    for (int i = l; i < j; i++) t.clean(a[i].l); // 记得清空
    cdq(mid + 1 , r);
}
```
还有一些推荐例题：[P4093 [HEOI2016/TJOI2016] 序列](https://www.luogu.com.cn/problem/P4093) 也是 cdq 优化转移 DP。

---

## 作者：Ray662 (赞：4)

建议评绿。

考虑这是一个类似不断向上叠的问题，从下往上考虑（指的是先把所有线段按纵坐标从大到小排序），这里的坐标系为左上角是 $(1, 1)$。

假设对于一个横坐标为 $x_i$ 的线段 $i$，设他最终的深度 $dep_i$ 为 `h - 答案值 + 1`，含义很好理解（就是被叠在了第几层）。

如何求 $dep_i$？显然 $dep_i$ 为被压在他下面的线段的深度最大值 +1，证明显然。所以问题转化成了：求 $[l_i, r_i]$ 的最大值，然后区间将 $[l_i, r_i]$ 赋值为 $dep_i$。

线段树维护即可。复杂度 $O((w + n) \log w)$。

[code](https://atcoder.jp/contests/abc382/submissions/60323260)

---

## 作者：whx2009 (赞：2)

## 本题思路：
我们知道他要掉的轮数近似于无穷，那么题目就转化为了一个不带移动不带变化不带删除的俄罗斯方块。最后问的是每一块落到了第几层，我们明显就可以发现每个块落到第几层就和比他低且二者在宽上有交集的个数有关。

考虑用线段树维护横坐标方块个数的区间最小值，按初始高度先给方块排序后每个落到的最终位置就是他所对应的宽的最小值减一，线段树维护当前宽的值即可。
## 本题代码：
```cpp
#include<bits/stdc++.h>
#define int long long
#define mid (tr[p].l+tr[p].r)/2
using namespace std;
struct f{int r,c,l,id;}a[200005];
struct ff{
	int l,r,sum,add;
}tr[200005*4];
int ans[200005],h,w;
void wei(int p){tr[p].sum=min(tr[p*2].sum,tr[p*2+1].sum);}
void jianshu(int p,int l,int r){
	tr[p].l=l,tr[p].r=r;
	if(tr[p].l==tr[p].r){tr[p].sum=h+1;return;}
	jianshu(p*2,l,mid),jianshu(p*2+1,mid+1,r);
	wei(p);
}
void chuan(int p){
	tr[p*2].sum=tr[p].add;
	tr[p*2+1].sum=tr[p].add;
	tr[p*2].add=tr[p].add;
	tr[p*2+1].add=tr[p].add;
	tr[p].add=0;
}
void xiugai(int p,int l,int r,int k){
//	cout<<l<<" "<<r;
	if(tr[p].l>=l&&tr[p].r<=r){tr[p].sum=k,tr[p].add=k;return;}
	if(tr[p].add) chuan(p);
	if(l<=mid) xiugai(p*2,l,r,k);
	if(r>mid) xiugai(p*2+1,l,r,k);
	wei(p);
}
int cha(int p,int l,int r){
//	cout<<l<<" "<<r<<" "<<tr[p].l<<" "<<tr[p].r<<endl;
	if(tr[p].l>=l&&tr[p].r<=r) return tr[p].sum;
	int ans=1e18;
	if(tr[p].add) chuan(p);
	if(l<=mid) ans=cha(p*2,l,r);
	if(r>mid) ans=min(ans,cha(p*2+1,l,r));
	return ans;
}
bool cmp(f x,f y){return x.l>y.l;}
signed main(){
	int n;cin>>h>>w>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].l>>a[i].c>>a[i].r;a[i].id=i;
	}
	sort(a+1,a+1+n,cmp);
	jianshu(1,1,w);
	for(int i=1;i<=n;i++){
		int num=cha(1,a[i].c,a[i].c+a[i].r-1);
//		cout<<num;
		ans[a[i].id]=num-1;
		xiugai(1,a[i].c,a[i].c+a[i].r-1,num-1);
	}
	for(int i=1;i<=n;i++) cout<<ans[i]<<'\n';
	return 0;
}
```

---

## 作者：XiaoJuRuoUP (赞：1)

[~~不会更好的阅读体验~~](https://www.cnblogs.com/XiaoJuRuoUP/p/-/luogu_AT_abc382_f)
## 题意
$W\times H$ 的网格，上面 $n$ 个 $1\times L_i$ 的方块，最左侧位置为 $(R_i,C_i)$，求这些方块下落后行 $R'_i$ 是多少。
## sol
可以按照 $R_i$ 对每个方块从大到小排序，容易发现下落时一定要按照方块顺序操作。当下落时，方块在第 $R'_i$ 行当且仅当第 $R'_i$ 行的对应位置没有方块，且 $R'_i+1$ 行的至少一个对应位置有方块（或是边界）。容易发现这个位置是对应列可放位置的最小值。

使用线段树来维护最小值，这样这道题就变成了区改区查最小值的线段树问题。

注意处理好 $lazytag$ 和 $tr$ 之间的关系。
## 代码
```cpp
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 200005;

struct Block{
    int r, c, l, id;
    bool operator< (const Block &W) const {
        if (r != W.r) return r > W.r;
        return c < W.c;
    }
} blocks[N];

int h, w, n;
int tr[N << 2], lazytag[N << 2];
int ans[N];

void build(int u, int l, int r){
    if (l == r) {
        tr[u] = h;
        lazytag[u] = h;
        return ;
    }

    int mid = l + r >> 1;
    build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
    lazytag[u] = tr[u] = h;
}

void pushdown(int u, int l, int r){
    if (l != r){
        lazytag[u << 1] = min(lazytag[u], lazytag[u << 1]);
        tr[u << 1] = min(lazytag[u], tr[u << 1]);
        lazytag[u << 1 | 1] = min(lazytag[u], lazytag[u << 1 | 1]);
        tr[u << 1 | 1] = min(lazytag[u], tr[u << 1 | 1]);
    }
}

void update(int u, int l, int r, int L, int R, int x){
    if (L <= l && r <= R) {
        lazytag[u] = x;
        tr[u] = x;
        return ;
    }
    pushdown(u, l, r);
    int mid = l + r >> 1;
    if (L <= mid) update(u << 1, l, mid, L, R, x);
    if (R > mid) update(u << 1 | 1, mid + 1, r, L, R, x);
    tr[u] = min(tr[u << 1], tr[u << 1 | 1]);
}

int query(int u, int l, int r, int L, int R){
    if (L <= l && r <= R) return tr[u];
    pushdown(u, l, r);
    int mid = l + r >> 1, minn = 0x3f3f3f3f;
    if (L <= mid) minn = min(minn, query(u << 1, l, mid, L, R));
    if (R > mid) minn = min(minn, query(u << 1 | 1, mid + 1, r, L, R));
    return minn;
}

int main(){
    scanf("%d%d%d", &h, &w, &n);
    for (int i = 1; i <= n; i ++ ) scanf("%d%d%d", &blocks[i].r, &blocks[i].c, &blocks[i].l), blocks[i].id = i;

    sort(blocks + 1, blocks + n + 1);

    build(1, 1, w);

    for (int i = 1; i <= n; i ++ ){
        ans[blocks[i].id] = query(1, 1, w, blocks[i].c, blocks[i].c + blocks[i].l - 1);
        update(1, 1, w, blocks[i].c, blocks[i].c + blocks[i].l - 1, ans[blocks[i].id] - 1);
    }

    for (int i = 1; i <= n; i ++ ) printf("%d\n", ans[i]);
}
```
## 蒟蒻犯的若至错误
* 线段树写炸了

---

## 作者：Ivan422 (赞：1)

在这里记录我第一次通过 F 题。

题意：给你一个简化版的俄罗斯方块，每一个方块变成一个长条，要求你模拟这些方块掉落后的结果，输出每一个方块的位置的高度。由于题目的特殊，地面高度为 $h$，最上面的一个高度为 $1$。

思路：考虑按照方块从低到高处模拟。对于一开始的一个方块都没有放，所有的点都是高度为 $h$ 的。我们放了一个方块，那么这个方块所属区间 $[r_i,r_i+c_i-1]$ 所有位置都将要更新。而一个方块的落脚高度将是这个区间的最低位置，即靠近 $1$ 坐标的位置。设这个落脚高度为 $h$，那么放完之后，下一个能放的位置将会变成 $h-1$。那么，我们只需要维护出空格位置即可。我们发现，这个问题可以维护一个能区间赋值，区间取 $\min$ 的线段树，就可以求出答案。当然你也可以直接用[扶苏的问题](https://www.luogu.com.cn/problem/P1253)的代码稍加修改。注意初始的高度全部为 $h$，在维护 $tag$ 时要将 $+\infty$ 的赋值改成 $h+1$，不要写成 $h$，不然过不去样例，我是不会告诉你我因为这个吃了一发罚时的。

没有线段树的部分是这样的：

```cpp
int main(){
    cin>>h>>w>>n;
    for(int i=1;i<=n;i++)cin>>a[i].r>>a[i].c>>a[i].l,a[i].i=i;
    sort(a+1,a+n+1);
    build(1,1,w); // 初始化空格, 最大空格位置位于 h 行, 区间 1...w
    for(int i=1;i<=n;i++){
        lps=a[i].c,rps=a[i].c+a[i].l-1; // 求出 bar 的位置区间
        hgh=qry(1,1,w,lps,rps);   // 查询 lps 到 rps 范围内的最小值, 找到尽可能底下的空格位子 
        upd(1,1,w,lps,rps,hgh-1); // 更改 lps 到 rps 范围内的值, 最大空格位置变为 hgh-1
        ans[a[i].i]=hgh;  // 求出答案, 对于每一个 bar, r'[i] 的值就是 hgh
    }
    for(int i=1;i<=n;i++)cout<<ans[i]<<"\n"; // 输出答案
    return 0;
}
```

总代码有点长，这里放个赛时的链接：[代码](https://atcoder.jp/contests/abc382/submissions/60345498)。

---

## 作者：dingwenzheng (赞：1)

# 题解：AT_abc382_f [ABC382F] Falling Bars

## 题目大意

有 $N$ 个长条，每一秒内，若一个长条下方没有长条，就会下落，问 $10^{100}$ 秒后每一个长条分别位于哪一行。

## 前置芝士：线段树

（注：部分内容引自 [OI Wiki](https://oiwiki.com/ds/seg/)）

线段树具有树的结构特性，其上的每一个节点都代表序列中的一个区间，可以在 $O(\log{N})$ 的时间复杂度内实现单点修改、区间修改、区间查询（区间求和，求区间最大值，求区间最小值）等操作。

### 建树

线段树将每个长度不为 $1$ 的区间划分成左右两个区间递归求解，把整个线段划分为一个树形结构，通过合并左右两区间信息来求得该区间的信息。

例如，根节点代表的是区间 $[1, n]$；对于代表区间 $[l, r]$ 的节点，它的左右子节点分别代表 $[l, (l+r)\div2]$ 和 $[(l+r)\div2+1, r]$。在储存时，$x$ 号节点的左孩子是 $x\times2$，右孩子是 $x\times2+1$。

### 区间查询

在本题中以查询区间最大值为例，从根节点进入，将要查询的区间划分成几个区间，再将这些区间的值合并。

设要查询的区间为 $[x, y]$ ，若当前节点被 $[x, y]$ 完全覆盖，直接返回当前节点的值；若 $[x, y]$ 与当前节点的左子节点有交集，就递归进入左子节点，若与右子节点有交集，就递归进入右子节点，再取两者中的较大者。

一般地，对于每个要查询的区间，可以将其拆成最多为 $O(\log{N})$ 个**极大**的区间，合并这些区间即可求出整个区间的答案。

### 区间修改

如果要求修改区间 $[l,r]$，把所有包含在区间 $[l,r]$ 中的节点都遍历一次、修改一次，时间复杂度无法承受。我们这里要引入一个叫做 **「懒惰标记」** 的东西。

懒惰标记，简单来说，就是通过延迟对节点信息的更改，从而减少可能不必要的操作次数。对于一个被完全覆盖在 $[l,r]$ 内的节点，先修改当前节点的值，再在这个节点上打一个懒惰标记（这意味着懒惰标记记录的是对当前节点的子节点的影响），直接返回。也就是先将修改记在父节点上，需要用到子节点时再传给子节点，以减少无用的修改。

如果当前节点没有被完全覆盖，就用类似区间查询的方式递归左右子树。

## 思路

$10^{100}$ 秒，对于所有长条的下落都是完全充足的，即所有长条都会堆在底部。

![](https://cdn.luogu.com.cn/upload/image_hosting/m3hzvrv0.png)

我们以样例为例，对于长条 $2$，它的下方没有长条，所以会落在最后一行；对于长条 $3$，它的下方有长条 $2$，会使长条 $3$ 无法继续下落，最终落在倒数第二行。

所以，每一个长条的最终位置取决于其所覆盖的区间内的最大高度，而这个长条又会对其所覆盖的整个区间产生影响。既需要区间查询，又需要区间修改，选择使用线段树维护每一段区间内的最大高度。

注意到，下方的长条会对上方的长条产生影响，而上方的不会对下方的产生影响，所以可以先按照每个长条的行号从大到小排序，在依次处理。

## 代码

```cpp
#include<bits/stdc++.h>
#define FOR(i, l, r) for(int (i)=(l); (i)<=(r); (i)++)
#define ROF(i, r, l) for(int (i)=(r); (i)>=(l); (i)--)
using namespace std;
const int N = 2e5+10;
struct bar{
	int r, c, l, id;
}p[N];
struct node{  // 线段树中维护从下往上的高度
	int dat, l, r, tag;
}tr[N*4];
int ans[N];
void pushup(int x){  // 合并左右子节点的信息到父节点上
	tr[x].dat = max(tr[x*2].dat, tr[x*2+1].dat);
} 
void pushdown(int x){  // 下传懒惰标记
	tr[x*2].dat = max(tr[x*2].dat, tr[x].tag);     // 更改子节点的值
	tr[x*2+1].dat = max(tr[x*2+1].dat, tr[x].tag); 
	tr[x*2].tag = max(tr[x*2].tag, tr[x].tag);   // 更改子节点的懒惰标记
	tr[x*2+1].tag = max(tr[x*2+1].tag, tr[x].tag);
	tr[x].tag = 0;   // 撤销当前节点的懒惰标记
}
void build(int x, int l, int r){
	tr[x] = {0, l, r, 0};
	if(l==r)return;
	int mid = l+r>>1;
	build(x*2, l, mid);
	build(x*2+1, mid+1, r);
}
int query(int x, int l, int r){
	int pl = tr[x].l, pr = tr[x].r;
	if(pl>r || pr<l) return 0;
	if(pl>=l && pr<=r){
		return tr[x].dat;
	}
	pushdown(x);
	int mid = pl+pr>>1, sum = 0;
	if(l<=mid) sum = max(sum, query(x*2, l, r));
	if(r>mid) sum = max(sum, query(x*2+1, l, r));
	return sum; 
}
void update(int x, int l, int r, int k){
	int pl = tr[x].l, pr = tr[x].r;
	if(pl>r || pr<l) return;
	if(pl>=l && pr<=r){
		tr[x].dat = max(tr[x].dat, k);
		tr[x].tag = k;
		return;
	}
	pushdown(x);  // 在区间修改和查询进入子节点前都需要下传懒惰标记
	int mid = pl+pr>>1;
	if(l<=mid) update(x*2, l, r, k);
	if(r>mid) update(x*2+1, l, r, k);
	pushup(x);
} 
int main(){
	int h, w, n;
	cin >> h >> w >> n;
	FOR(i, 1, n){
		cin >> p[i].r >> p[i].c >> p[i].l;
		p[i].id = i;
	}
	sort(p+1, p+n+1, [&](bar x, bar y){
		return x.r>y.r;
	});
	build(1, 1, w);
	FOR(i, 1, n){
		int tmp = query(1, p[i].c, p[i].l+p[i].c-1);
		ans[p[i].id] = tmp; 
		update(1, p[i].c, p[i].l+p[i].c-1, tmp+1);
	}
	FOR(i, 1, n){
		cout << h-ans[i] << endl;
	}
	return 0;
}
```

---

## 作者：1234567890sjx (赞：1)

考虑简单线段树。将所有格子离线下来然后从低到高排序，按照顺序考虑每一个格子覆盖的区间 $[L_i,R_i]$，显然答案就是该段区间内被覆盖的格子高度最大值 $+1$，然后更新区间覆盖的最高高度。直接做时间复杂度为 $O(n^2)$ 过不去，但是可以使用线段树优化做到 $O(n\log n)$。

代码：

```cpp
struct qwq {
    int r, c, l, id;
} z[N];
struct awa {
    int l, r, mx, tag;
    void init(int p) {
        l = r = p;
        mx = 1, tag = 0;
    }
    void yhb(int v) {
        mx = max(mx, v), tag = max(tag, v);
    }
    void qwq(int v) {
        mx += v;
    }
} y[N << 2];
awa operator+(const awa &l, const awa &r) {
    return {l.l, r.r, max(l.mx, r.mx), 0ll};
}
void build(int l, int r, int rt) {
    if (l == r) return y[rt].init(l);
    int mid = l + r >> 1;
    build(l, mid, rt << 1);
    build(mid + 1, r, rt << 1 | 1);
    y[rt] = y[rt << 1] + y[rt << 1 | 1];
}
void qwp(int x) {
    if (y[x].tag) {
        y[x << 1].qwq(y[x].tag);
        y[x << 1 | 1].qwq(y[x].tag);
        y[x].tag = 0;
    }
}
void pwp(int x) {
    if (y[x].tag) {
        y[x << 1].yhb(y[x].tag);
        y[x << 1 | 1].yhb(y[x].tag);
        y[x].tag = 0;
    }
}
void modify(int l, int r, int rt, int ll, int rr, int v) {
    if (ll <= l && r <= rr) return y[rt].yhb(v);
    int mid = l + r >> 1; pwp(rt);
    if (ll <= mid) modify(l, mid, rt << 1, ll, rr, v);
    if (mid < rr) modify(mid + 1, r, rt << 1 | 1, ll, rr, v);
    y[rt] = y[rt << 1] + y[rt << 1 | 1];
}
int query(int l, int r, int rt, int ll, int rr) {
    if (ll <= l && r <= rr) return y[rt].mx;
    int mid = l + r >> 1, mx = 1; pwp(rt);
    if (ll <= mid) mx = max(mx, query(l, mid, rt << 1, ll, rr));
    if (mid < rr) mx = max(mx, query(mid + 1, r, rt << 1 | 1, ll, rr));
    return mx;
}
int res[N];
void run() {
    int n = read(), m = read(), q = read();
    for (int i = 1; i <= q; ++i)
        z[i].r = read(), z[i].c = read(), z[i].l = read(), z[i].id = i;
    sort(z + 1, z + q + 1, [&](auto l, auto r) {
        return l.r > r.r;
    });
    build(1, m, 1);
    for (int i = 1; i <= q; ++i) {
        int now = query(1, m, 1, z[i].c, z[i].c + z[i].l - 1);
        res[z[i].id] = n - now + 1;
        modify(1, m, 1, z[i].c, z[i].c + z[i].l - 1, now + 1);
    }
    for (int i = 1; i <= q; ++i) cout << res[i] << '\n'; 
}
```

但是这又是怎么回事呢？

![pAI5jHg.png](https://s21.ax1x.com/2024/12/02/pAI5jHg.png)

---

## 作者：xiaofu15191 (赞：0)

前言：NOIP 没用的 RP 好像捐给 ABC 了。

对于一个 `bar`，它肯定会下落到它的左右范围 $[c_i,c_i+l_i-1]$ 中最高的格子上方。

将 `bar` 按照 $r_i$ 从大到小排序，因为 $r_i$ 较大的更先下落到底部。

然后用一棵区间修改线段树维护区间最小值即可。但是要注意线段树的初值为 $h+1$。

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
long long h,w,n,tree[800010],lazy[800010],ans[200010];
struct bar
{
	long long r,c,l,id;
}bars[200010];
bool cmp(bar a,bar b)
{
	if(a.r!=b.r) return a.r>b.r;
	else return a.c<b.c;
}
void build(long long now,long long l,long long r)
{
	if(l==r)
	{
		tree[now]=h+1;
		return;
	}
	long long mid=(l+r)>>1;
	build(now<<1,l,mid);
	build(now<<1|1,mid+1,r);
	tree[now]=max(tree[now<<1],tree[now<<1|1]);
}
void pushdown(long long now)
{
	if(lazy[now])
	{
		tree[now<<1]=lazy[now];
		tree[now<<1|1]=lazy[now];
		lazy[now<<1]=lazy[now];
		lazy[now<<1|1]=lazy[now];
		lazy[now]=0;
	}
}
void update(long long now,long long l,long long r,long long x,long long y,long long val)
{
	if(r<x||l>y) return;
	if(x<=l&&r<=y)
	{
		tree[now]=val;
		lazy[now]=val;
		return;
	}
	pushdown(now);
	long long mid=(l+r)>>1;
	if(x<=mid) update(now<<1,l,mid,x,y,val);
	if(y>mid) update(now<<1|1,mid+1,r,x,y,val);
	tree[now]=min(tree[now<<1],tree[now<<1|1]);
}
long long query(long long now,long long l,long long r,long long x,long long y)
{
	if(r<x||l>y) return h+1;
	if(x<=l&&r<=y) return tree[now];
	pushdown(now);
	long long mid=(l+r)>>1,ans=h+1;
	if(x<=mid) ans=min(ans,query(now<<1,l,mid,x,y));
	if(y>mid) ans=min(ans,query(now<<1|1,mid+1,r,x,y));
	return ans;
}
int main()
{
	scanf("%lld%lld%lld",&h,&w,&n);
	for(long long i=1;i<=n;i++) scanf("%lld%lld%lld",&bars[i].r,&bars[i].c,&bars[i].l),bars[i].id=i;
	sort(bars+1,bars+n+1,cmp);
	build(1,1,w);
	for(long long i=1;i<=n;i++)
	{
		long long tmp=query(1,1,w,bars[i].c,bars[i].c+bars[i].l-1);
		tmp--;
		ans[bars[i].id]=tmp;
		update(1,1,w,bars[i].c,bars[i].c+bars[i].l-1,tmp);
	}
	for(long long i=1;i<=n;i++) printf("%lld\n",ans[i]);
}
```

---

## 作者：Liuhy2996 (赞：0)

## 思路
看到当横条下面一排什么都没有时才能往下移，想到维护每一列从下往上数被占据了几个，将横条放到底实际上是查询区间最大值并区间赋值，使用线段树维护。注意要按最开始从下到上放横条，因为上面的肯定不会影响下面的。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e6+10;
int n,m,q,x,y,z,ans[N],tr[N],tg[N];
struct A{int x,l,r,id;}a[N];
void psu(int x){tr[x]=max(tr[x*2],tr[x*2+1]);}
void psd(int x){
	if(tg[x]) tr[x*2]=tr[x*2+1]=tg[x*2]=tg[x*2+1]=tg[x],tg[x]=0;
}
void upt(int x,int l,int r,int ql,int qr,int k){
	if(ql<=l&&r<=qr) return tr[x]=tg[x]=k,void();
	int mid=(l+r)>>1;
	psd(x);
	if(ql<=mid) upt(x*2,l,mid,ql,qr,k);
	if(qr>mid) upt(x*2+1,mid+1,r,ql,qr,k);
	psu(x);
}
int qry(int x,int l,int r,int ql,int qr){
	if(ql<=l&&r<=qr) return tr[x];
	int mid=(l+r)>>1,ans=0;
	psd(x);
	if(ql<=mid) ans=max(ans,qry(x*2,l,mid,ql,qr));
	if(qr>mid) ans=max(ans,qry(x*2+1,mid+1,r,ql,qr));
	return ans;
}
//上面几乎是线段树模板
signed main(){
	cin>>n>>m>>q;
	for(int i=1;i<=q;++i) cin>>x>>y>>z,a[i]={x,y,y+z-1,i};
	sort(a+1,a+q+1,[](A x,A y){return x.x>y.x;});
	for(int i=1;i<=q;++i){
		ans[a[i].id]=qry(1,1,m,a[i].l,a[i].r)+1;
		upt(1,1,m,a[i].l,a[i].r,ans[a[i].id]);
	}
	for(int i=1;i<=q;++i) cout<<n+1-ans[i]<<endl;
	return 0;
}
```

---

## 作者：joe_zxq (赞：0)

~~样例里的图形像我堆的块。~~

首先，肯定是先让下面的块先落，所以将块按行号从大到小排序。

然后，就是要看每次落块最低落到哪里，也就是说这个块正下方已经有一个有块的行号最小的行上面一行。显然可以开一颗 $1 \sim W$ 的线段树维护这个东西，就是区间赋值和区间询问最小值。

然后就结束了，很基础的数据结构题。

```cpp
// Problem: F - Falling Bars
// Contest: AtCoder - AtCoder Beginner Contest 382
// URL: https://atcoder.jp/contests/abc382/tasks/abc382_f
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define AC return 0

const ll mod = 1; // Be careful, 998244353 or 998244853.
const ll dx[] = {0, 1, 0, -1};
const ll dy[] = {1, 0, -1, 0};
mt19937 rnd(chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count());
	
void ts() {
	cerr << "The code is running!\n";
}

ll read() {
    char c;
    bool isf = 0;
    while (!isdigit(c = getchar())) isf = (c == '-');
    ll res = (c ^ 48);
    while (isdigit(c = getchar())) res = (res << 3) + (res << 1) + (c ^ 48);
    return isf ? -res : res;
}

void write(ll x) {
    if (x < 0)
        putchar('-'), x = -x;
    if (x >= 10)
        write(x / 10);
    putchar('0' + x % 10);
}

void updmin(ll& x, ll y) {
	x = min(x, y);
}

void updmax(ll& x, ll y) {
	x = max(x, y);
}

ll qpow(ll x, ll y) {
	if (y == 0) {
		return 1;
	}
	ll res = qpow(x, y / 2);
	res *= res;
	res %= mod;
	if (y % 2) {
		res *= x;
		res %= mod;
	}
	return res;
}

ll randint(ll l, ll r) {
	return rnd() % (r - l + 1) +  l;
}

void openf(string s) {
    freopen((s + ".in").c_str(), "r", stdin);
    freopen((s + ".out").c_str(), "w", stdout);
}

ll tc = 1, n, m, q;

struct SegTree {
	struct node {
		ll l, r, mn, lzy;
	} tr[214514 << 2];
	
	void pushup(ll p) {
		tr[p].mn = min(tr[p << 1].mn, tr[p << 1 | 1].mn);
	}
	
	void pushdown(ll p) {
		if (tr[p].lzy != 1e18) {
			updmin(tr[p << 1].lzy, tr[p].lzy);
			updmin(tr[p << 1 | 1].lzy, tr[p].lzy);
			updmin(tr[p << 1].mn, tr[p].lzy);
			updmin(tr[p << 1 | 1].mn, tr[p].lzy);
		}
		tr[p].lzy = 1e18;
	}
	
	void build(ll l, ll r, ll p = 1) {
		tr[p].l = l;
		tr[p].r = r;
		tr[p].lzy = 1e18;
		tr[p].mn = 1e18;
		if (l == r) {
			tr[p].mn = n + 1;
			return;
		}
		ll mid = (l + r) >> 1;
		build(l, mid, p << 1);
		build(mid + 1, r, p << 1 | 1);
		pushup(p);
	}
	
	void update(ll l, ll r, ll k, ll p = 1) {
		if (l <= tr[p].l && tr[p].r <= r) {
			updmin(tr[p].lzy, k);
			updmin(tr[p].mn, k);
			return;
		}
		pushdown(p);
		ll mid = (tr[p].l + tr[p].r) >> 1;
		if (l <= mid) {
			update(l, r, k, p << 1);
		}
		if (r > mid) {
			update(l, r, k, p << 1 | 1);
		}
		pushup(p);
	}
	
	ll query(ll l, ll r, ll p = 1) {
		if (l <= tr[p].l && tr[p].r <= r) {
			return tr[p].mn;
		}
		pushdown(p);
		ll mid = (tr[p].l + tr[p].r) >> 1, res = n + 1;
		if (l <= mid) {
			updmin(res, query(l, r, p << 1));
		}
		if (r > mid) {
			updmin(res, query(l, r, p << 1 | 1));
		}
		return res;
	}
} T;

struct nd {
	ll l, r, x, id;
} a[214514];

ll ans[214514];

bool cmp(nd qw, nd er) {
	if (qw.x != er.x) {
		return qw.x > er.x;
	}
	return qw.id < er.id;
}

void init() {
	;
}

void solve() {
	init();
	n = read(), m = read(), q = read();
	T.build(1, m);
	for (ll i = 1; i <= q; i++) {
		a[i].x = read(), a[i].l = read(), a[i].r = read();
		a[i].r += a[i].l - 1;
		a[i].id = i;
	}
	sort(a + 1, a + q + 1, cmp);
	for (ll i = 1; i <= q; i++) {
		ans[a[i].id] = a[i].x = T.query(a[i].l, a[i].r) - 1;
		T.update(a[i].l, a[i].r, a[i].x);
	}
	for (ll i = 1; i <= q; i++) {
		write(ans[i]);
		putchar('\n');
	}
}

int main() {
	
    // openf("data");
    
    // ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    // tc = read();
    
    while (tc--) {
    	solve();
    	putchar("\n "[(!tc)]);
    }
    
    // printf("Time: %.6lf\n", (double)clock() / CLOCKS_PER_SEC);

    AC;
}

/*
Things to check:

1. When testing multiple sets of data, remember to clear the array.

2. When clearing, pay attention to clearing the area, starting from 0 or 1. If time permits, use memset.

3. Delete the debugged code.

4. Do you need to enable file input/output.

5. Use faster input and output methods.

6. INT or long long.

7. Pay attention to time complexity and space complexity, and control constants.

8. Think twice before acting.

9. Talk is cheap, show me the code.

10. The most important one, zxq's brain.
*/

/*
                                                                                              
_|_|_|_|_|  _|      _|    _|_|          _|      _|        _|_|      _|      _|_|    _|  _|    
      _|      _|  _|    _|    _|          _|  _|        _|    _|  _|  _|  _|    _|  _|  _|    
    _|          _|      _|  _|_|            _|              _|    _|  _|      _|    _|_|_|_|  
  _|          _|  _|    _|    _|          _|  _|          _|      _|  _|    _|          _|    
_|_|_|_|_|  _|      _|    _|_|  _|      _|      _|      _|_|_|_|    _|    _|_|_|_|      _|    
          
.................................................................................................................
.................................................................................................................
.................................................................................................................
.................................................................................................................
.................................................................................................................
.......RRRRRRRRRRRRRRRRRRRR...................PPPPPPPPPPPPPPPPPPPP...............................................
.......RRRRRRRRRRRRRRRRRRRRRR.................PPPPPPPPPPPPPPPPPPPPPP.............................................
.......RRRRRRRRRRRRRRRRRRRRRRR................PPPPPPPPPPPPPPPPPPPPPPPP...........................................
.......RRRR.................RRRRR.............PPPP...............PPPPP...........................................
.......RRRR.................RRRRR.............PPPP................PPPPP..........................................
.......RRRR.................RRRRR.............PPPP................PPPPP..........................................
.......RRRR...............RRRRR...............PPPP...............PPPPP...........................................
.......RRRR............RRRRRR.................PPPP.............PPPPPP............................................
.......RRRR............RRRRRR.................PPPP............PPPPPP.............................................
.......RRRR........RRRRRR.....................PPPP........PPPPPPP................................................
.......RRRRRRRRRRRRRRRRRR.....................PPPPPPPPPPPPPPPPPP.................................................
.......RRRRRRRRRRRRRRRRRR.....................PPPPPPPPPPPPPPPP...................................................
.......RRRR..........RRRR.....................PPPPP.................................+++................+++.......
.......RRRR...........RRRR....................PPPPP.................................+++................+++.......
.......RRRR.............RRRR..................PPPPP.................................+++................+++.......
.......RRRR..............RRRR.................PPPPP...........................+++++++++++++++....+++++++++++++++.
.......RRRR...............RRRR................PPPPP...........................+++++++++++++++....+++++++++++++++.
.......RRRR................RRRR...............PPPPP.................................+++................+++.......
.......RRRR.................RRRR..............PPPPP.................................+++................+++.......
.......RRRR...................RRRR............PPPPP.................................+++................+++.......
.................................................................................................................
.................................................................................................................
.................................................................................................................
.................................................................................................................
.................................................................................................................
                                                                                    
                                                                 
*/
```

---

## 作者：wei2013 (赞：0)

## 思路：
对于每一个下落的长条，显然它有一个应该的顺序，即先从 $x$ 大的线下落到最底部，这样才能保证正确性，但是 $1 \le H,W \le 2 \times 10^5$，导致还是无法 $AC$，有什么数据结构可以维护这样的信息呢？显然是线段树。

考虑用线段树维护最矮的方块，然后最低的可以到达的地方就是答案，线段树板子。
## code:

```cpp
#include<iostream>
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN=2e5+5;
int n,m,asd;
struct stick{
	int x,y,l,id;
}a[MAXN];
int ans[MAXN];
struct node{
	int val,lazytag;
}t[MAXN<<2];
int k,lt,rh;
void push_up(int rt){
    t[rt].val=min(t[rt<<1].val,t[rt<<1|1].val);
}
void build(int l,int r,int rt){
    if(l==r){
		t[rt]=(node){n,0};
    	return;
	}
    int mid=l+r>>1;
    build(l,mid,rt<<1);
	build(mid+1,r,rt<<1|1);
    push_up(rt);
}
void push_down(int rt){
    if(!t[rt].lazytag){
    	return;
	}
    t[rt<<1].val=t[rt].lazytag;
    t[rt<<1].lazytag=t[rt].lazytag;
    t[rt<<1|1].val=t[rt].lazytag;
    t[rt<<1|1].lazytag=t[rt].lazytag;
    t[rt].lazytag=0;
}
void update(int l,int r,int rt){
    if(l>=lt && r<=rh){
    	t[rt].val=k;
    	t[rt].lazytag=k;
    	return;
	}
    push_down(rt);
    int mid=l+r>>1;
    if(mid>=lt){
    	update(l,mid,rt<<1);
	}
    if(mid+1<=rh){
    	update(mid+1,r,rt<<1|1);
	}
    push_up(rt);
}
int query(int l,int r,int rt){
    if(l>=lt && r<=rh){
    	return t[rt].val;
	}
    push_down(rt);
    int mid=l+r>>1,res=1e18;
    if(mid>=lt){
    	res=min(res,query(l,mid,rt<<1));
	}
    if(mid+1<=rh){
    	res=min(res,query(mid+1,r,rt<<1|1));
	}
    return res;
}
void upd(int l,int r,int _k){
	k=_k;
	lt=l;
	rh=r;
	update(1,m,1);
}
int q(int l,int r){
	lt=l;
	rh=r;
	return query(1,m,1);
}
bool cmp(stick a,stick b){
	if(a.x!=b.x){
		return a.x>b.x;
	}
	return a.y<b.y;
}
signed main(){
    cin>>n>>m>>asd;
    for(int i=1;i<=asd;i++){
    	cin>>a[i].x>>a[i].y>>a[i].l;
		a[i].id=i;
	}
    sort(a+1,a+asd+1,cmp);
    build(1,m,1);
    for(int i=1;i<=asd;i++){
        int x=a[i].x,y=a[i].y,l=a[i].l,now=q(y,y+l-1);
        upd(y,y+l-1,now-1);
        ans[a[i].id]=now;
        //cout<<a[i].id<<endl;
    }
    for(int i=1;i<=asd;i++){
    	cout<<ans[i]<<'\n';
	}
    return 0;
}
```

---

## 作者：T_TLucas_Yin (赞：0)

注意到 $10^{100}$ 个时间单位对于题目数据范围下横条的下降已经非常大了。所以可以认为题目询问的是所有横条都不再移动后横条的状态。

根据题目要求，由于横条不能穿过网格边界或在它正下方的其他横条，所以：

1. 最终横条按横坐标排序的结果与最初是一样的。
2. 每个横条最终的横坐标为它下面最靠上一根横条的横坐标 $+1$。

所以我们先将横条按一开始的横坐标从大到小排序，这样就能实现从下到上模拟。遍历到一个横条时，找到当前其覆盖的纵坐标范围内已被覆盖的横坐标的最小值 $x$（即摞得最高的一根横条的高度，初始时为网格的下边界），记录该条的答案为 $x+1$，再用 $x+1$ 更新对应纵坐标范围内的最小横坐标即可。

如上操作可以使用一个存储区间最大值、支持区间修改的线段树实现。

```cpp
#include<bits/stdc++.h>
using namespace std;
int read(){
	int x=0;
	char c=getchar();
	while(!isdigit(c)) c=getchar();
	while(isdigit(c)) x=x*10+(c-'0'),c=getchar();
	return x;
}
int n,m,q,x,y,z;
struct node{
	int x,l,r,k;
}a[1000005];
bool cmp(node a,node b){
	return a.x>b.x;
}
int f1[1000005];
int f[4000005],flag[4000005];
void build(int root,int l,int r){
	if(l==r){ f[root]=n+1;return; }
	int mid=(l+r)>>1;
	build(root<<1,l,mid);
	build(root<<1|1,mid+1,r);
	f[root]=min(f[root<<1],f[root<<1|1]);
}
void pushdown(int root){
	if(!flag[root]) return;
	f[root<<1]=flag[root],flag[root<<1]=flag[root];
	f[root<<1|1]=flag[root],flag[root<<1|1]=flag[root];
	flag[root]=0;
}
void update(int root,int l,int r,int fl,int fr,int k){
	if(fl<=l&&r<=fr){ f[root]=k,flag[root]=k;return; }
	int mid=(l+r)>>1;
	pushdown(root);
	if(fl<=mid) update(root<<1,l,mid,fl,fr,k);
	if(fr>mid) update(root<<1|1,mid+1,r,fl,fr,k);
	f[root]=min(f[root<<1],f[root<<1|1]);
}
int Find(int root,int l,int r,int fl,int fr){
	if(fl<=l&&r<=fr) return f[root];
	int mid=(l+r)>>1,minn=2e9;
	pushdown(root);
	if(fl<=mid) minn=min(minn,Find(root<<1,l,mid,fl,fr));
	if(fr>mid) minn=min(minn,Find(root<<1|1,mid+1,r,fl,fr));
	return minn;
}
int main(){
	n=read(),m=read(),q=read();
	for(int i=1;i<=q;i++){
		x=read(),y=read(),z=read();
		a[i]={x,y,y+z-1,i};
	}
	sort(a+1,a+1+q,cmp);
	build(1,1,m);
	for(int i=1;i<=q;i++){
		f1[a[i].k]=Find(1,1,m,a[i].l,a[i].r)-1;
		update(1,1,m,a[i].l,a[i].r,f1[a[i].k]);
	}
	for(int i=1;i<=q;i++) printf("%d\n",f1[i]);
	return 0;
}
```

---

## 作者：_smart_stupid_ (赞：0)

发现，初始位置靠下的长条会先掉下，所以从下往上确定长条落在哪里。

当长条落下时，我们用 $A$ 数组记录每一个点的高度，那么长条的位置就是长条覆盖范围中 $A$ 的最大值加一。确定位置后，我们还要更新 $A$ 数组。区间最大，区间加。

线段树维护，完了。

## AC Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
int h, w, n;
struct node{
	int r, c1, c2, idx;
} a[200100];
bool operator <(node a, node b) {
	return a.r > b.r;
}
struct tnode{
	int l, r, maxx, tag;
} t[1600100];
void pushtag(int p) {
	t[p * 2].tag = max({t[p].maxx, t[p * 2].maxx, t[p].tag});
	t[p * 2 + 1].tag = max({t[p].maxx, t[p * 2].maxx, t[p].tag});
	t[p].maxx = t[p].tag, t[p].tag = 0;
}
void maketree(int l, int r, int p) {
	t[p].l = l, t[p].r = r;
	if (l < r) {
		int mid = (l + r) / 2;
		maketree(l, mid, p * 2);
		maketree(mid + 1, r, p * 2 + 1);
	}
}
void add(int l, int r, int x, int p) {
	if (t[p].tag) pushtag(p);
	if (l <= t[p].l && t[p].r <= r) {
		t[p].tag = x;
		pushtag(p);
		return;
	}
	if (l > t[p].r || r < t[p].l) return;
	add(l, r, x, p * 2); add(l, r, x, p * 2 + 1);
	t[p].maxx = max(t[p * 2].maxx, t[p * 2 + 1].maxx);
}
int get(int l, int r, int p) {
	if (t[p].tag) pushtag(p);
	if (l <= t[p].l && t[p].r <= r) {
		return t[p].maxx;
	}
	if (l > t[p].r || r < t[p].l) return 0;
	return max(get(l, r, p * 2), get(l, r, p * 2 + 1));
}
int ans[200100];
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> h >> w >> n;
	for (int i = 1; i <= n; i++) {
		int l;
		cin >> a[i].r >> a[i].c1 >> l;
		a[i].c2 = a[i].c1 + l - 1, a[i].idx = i;
	}
	sort(a + 1, a + n + 1);
	maketree(1, w, 1);
	for (int i = 1; i <= n; i++) {
		int x = get(a[i].c1, a[i].c2, 1);
		ans[a[i].idx] = x + 1;
		add(a[i].c1, a[i].c2, x + 1, 1);
	}
	for (int i = 1; i <= n; i++) cout << h - ans[i] + 1 << '\n'; //由于从下往上记录，所以要反过来。
	cout << '\n';
	return 0;
}
```

---

## 作者：zhangzheng2026 (赞：0)

由于操作次数很大，每个块都会落到能落到的深度最大的位置。为了避免计算时两个有重叠部分（即深度不等，但左右端点掌控的区间横坐标有交集）的块上下位置交换，我们先将块按原深度大小从大到小排序。我们考虑一个块落下时，它能落到的最终位置就是它所在区间深度的最小值减一；在这个块落下后，它所在的区间都会被修改为它落下后的深度。查询区间最大值和区间修改完全可以用线段树 $O(\log N)$ 维护。所以总的时间复杂度是 $O(N \log N)$ 的，可以通过过此题。  
参考代码：  

```cpp
#include <bits/stdc++.h>
using namespace std;
int h,w,n,ans[200005],tr[800005],bj[800005];
struct node{int r,c,l,num;}a[200005];
bool cmp(node x,node y){return x.r>y.r;}
//-------------------------------------------------
void push_down(int num,int l,int r)
{
	if(bj[num]==1e9) return;
	tr[num]=min(tr[num],bj[num]);
	if(l<r)
	{
		bj[num<<1]=min(bj[num<<1],bj[num]);
		bj[num<<1|1]=min(bj[num<<1|1],bj[num]);
	}
	bj[num]=1e9;
}
int ask(int num,int l,int r,int x,int y)
{
	push_down(num,l,r);
	if(r<x||l>y) return h+1;
	if(x<=l&&r<=y) return tr[num];
	int mid=(l+r)/2;
	return min(ask(num<<1,l,mid,x,y),ask(num<<1|1,mid+1,r,x,y));
}
void change(int num,int l,int r,int x,int y,int s)
{
	push_down(num,l,r);
	if(r<x||l>y) return;
	if(x<=l&&r<=y){bj[num]=s,push_down(num,l,r);return;}
	int mid=(l+r)/2;
	change(num<<1,l,mid,x,y,s),change(num<<1|1,mid+1,r,x,y,s);
	tr[num]=min(tr[num<<1],tr[num<<1|1]);
}
//线段树
//-------------------------------------------------
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>h>>w>>n;
	for(int i=1;i<=800000;i++) bj[i]=1e9,tr[i]=h+1;
	//懒标记要初始化为极大值，深度最大值初始为h+1
	for(int i=1;i<=n;i++) cin>>a[i].r>>a[i].c>>a[i].l,a[i].num=i;
	sort(a+1,a+n+1,cmp);//按深度从大到小排序
	for(int i=1;i<=n;i++)
	{
		ans[a[i].num]=ask(1,1,w,a[i].c,a[i].c+a[i].l-1)-1;
		change(1,1,w,a[i].c,a[i].c+a[i].l-1,ans[a[i].num]);
	}
	for(int i=1;i<=n;i++) cout<<ans[i]<<'\n';
	return 0;
}
```

---

## 作者：small_lemon_qwq (赞：0)

水。

有 $n$ 个高为 $1$ 的长方形，重力垂直于第 $H+1$ 行。考虑从最下面的长方形开始，往下掉，例如处理到一个长方形的左端点为 $(x,l)$，右端点为 $(x,r)$，掉到了第 $y$ 层，那么标记区间 $(l,r)$ 为 $y$，考虑掉到那一层时取 $(l,r)$ 的最大值为 $t$，那么一定是掉到第 $t-1$ 层。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAX_LEN =200005;
int seg_tree[MAX_LEN << 2];
int Lazy[MAX_LEN << 2];
int arr[MAX_LEN];
void push_up(int root){
	seg_tree[root]=max(seg_tree[root << 1], seg_tree[root << 1 | 1]);
}
void push_down (int root, int L, int R) {
	if(Lazy[root]){
		Lazy[root << 1] = Lazy [root];
		Lazy[root << 1 | 1] = Lazy[root];
		int mid = (L + R) >> 1;
		seg_tree[root << 1] =  Lazy[root] ;
		seg_tree[root << 1 | 1] = Lazy[root] ;
		Lazy[root] = 0;
	}
}
void build (int root, int L, int R) {
	Lazy[root] = 0;
	if(L == R) {
		seg_tree[root] = arr[L];
		return ;
	}
	int mid = (L + R) >> 1;
	build(root << 1, L, mid);
	build(root<<1|1, mid + 1, R);
	push_up(root);
}
int query (int root, int L, int R, int LL, int RR) {
	if (LL <= L && R <= RR) return seg_tree[root];
	push_down(root, L, R);
	int Ans = 0;
	int mid = (L + R) >> 1;
	if(LL <= mid) Ans = max(Ans, query(root << 1, L, mid, LL, RR));
	if(RR > mid) Ans = max(Ans, query(root << 1 | 1, mid + 1, R, LL, RR));
	return Ans;
}
void update_Interval(int root, int L, int R, int LL, int RR, int val){
	if (LL<=L&&R<=RR) {
		Lazy[root]=val;
		seg_tree[root]=val;
		return ;
	}
	push_down(root, L, R);
	int mid = (L + R) >> 1;
	if (LL <= mid) update_Interval(root << 1, L, mid, LL, RR, val);
	if (RR > mid) update_Interval(root << 1 | 1, mid + 1, R, LL , RR, val);
	push_up(root);
}
struct lemon{
	int x,L,R,id;
	bool operator<(const lemon&t)const{
		return x<t.x;
	}
}did[200005];
int ans[200005];
signed main(){
	int H,W,N;
	cin>>H>>W>>N;
	for(int i=1;i<=W;i++){
		arr[i]=0;
	}
	build(1,1,W);
	for(int i=1;i<=N;i++){
		cin>>did[i].x>>did[i].L>>did[i].R;
		did[i].R+=did[i].L-1;
		did[i].id=i;
	}
	stable_sort(did+1,did+N+1);
	for(int i=N;i>=1;i--){
		int t=query(1,1,W,did[i].L,did[i].R);
		ans[did[i].id]=t+1;
		update_Interval(1,1,W,did[i].L,did[i].R,t+1);
	}
	for(int i=1;i<=N;i++){
		cout<<H-ans[i]+1<<"\n";
	}
	return 0;
}
/*
5 4
3 2 4 5 1
1 2
2 4
3 5
2 3
*/
```

---

