# バブルソート (Bubble Sort)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joi2013ho/tasks/joi2013ho5

バブルソートとは，列をソートするアルゴリズムの $ 1 $ つである．長さ $ N $ の数列 $ A $ を昇順にソートしたいとしよう．バブルソートは，隣り合う $ 2 $ つの数で大小関係が崩れているものがあれば，それらの位置を交換する．これを，数列を前から順に走査しながら行う．すなわち，$ A_i\ >\ A_{i\ +\ 1} $ となっている場所があれば，その $ 2 $ 数を交換するということを，$ i\ =\ 1,\ 2,\ \ldots,\ N\ -\ 1 $ に対してこの順で行うのが $ 1 $ 回の走査である．この走査を $ N\ −\ 1 $ 回繰り返すことで，数列を昇順にソートできることが知られている．

数列 $ A $ のバブルソートによる交換回数とは，数列 $ A $ に上記のアルゴリズムを適用した時に，整数の交換が行われる回数である．（バブルソートとして知られるアルゴリズム及び実装には，ループの順番や範囲，及び終了条件など，細かな差異がある場合がある．ただし，同じ数列に適用した際の整数の交換回数はそれらの差異により変化しないことが知られている．）

例えば，以下のプログラムは長さ `n` の整数の配列 `a` をバブルソートによりソートする関数を C 言語で記述したものである．

```cpp
void bubble_sort(int *a, int n) {
  int i, j;
  for (i = 0; i < n - 1; ++i) {
    for (j = 0; j < n - 1; ++j) {
      if (a[j] > a[j + 1]) {
        /* 以下 3 行が 1 回の整数の交換に相当 */
        int x = a[j];
        a[j] = a[j + 1];
        a[j + 1] = x;
      }
    }
  }
}

```

## 说明/提示

### 課題

長さ $ N $ の数列 $ A $ が与えられる．数列 $ A $ の任意の場所の $ 2 $ つの整数を $ 1 $ 回だけ交換した数列 $ A' $ を作るとする．数列 $ A' $ のバブルソートによる交換回数の最小値を求めるプログラムを作成せよ．（最初に交換する $ 2 $ つの整数は必ずしも隣り合っている必要はないことに注意せよ．）

### 制限

$ 2\ \leqq\ N\ \leqq\ 100\,000 $ 数列 $ A $ の長さ$ 1\ \leqq\ A_i\ \leqq\ 1\,000\,000\,000 $ 数列 $ A $ に含まれる数字の大きさ（注）過去問移植時に制約を修正．

- - - - - -

### 採点基準

採点用データのうち，配点の $ 10 $ %分については，$ N\ \leqq\ 1\ 000 $ を満たし，任意の $ i,\ j $ ($ 1\ \leqq\ i\ <\ j\ \leqq\ N $) について $ A_i\ \neq\ A_j $ を満たす．

採点用データのうち，配点の $ 30 $ %分については，$ N\ \leqq\ 5\,000 $ を満たし，任意の $ i,\ j $ ($ 1\ \leqq\ i\ <\ j\ \leqq\ N $) について $ A_i\ \neq\ A_j $ を満たす．

採点用データのうち，配点の $ 80 $ %分については，任意の $ i,\ j $ ($ 1\ \leqq\ i\ <\ j\ \leqq\ N $) について $ A_i\ \neq\ A_j $ を満たす．

- - - - - -

### Sample Explanation 1

数列 $ A $ の最初の $ 10 $ と最後の $ 1 $ を交換することにすると，数列 $ A' $ はソート済みの列となり，バブルソートの交換回数は $ 0 $ となる． - - - - - -

### Sample Explanation 2

数列 $ A $ の $ 3 $ 番目の $ 7 $ と最後の $ 5 $ を交換することで，数列 $ A' $ は $ 3,\ 1,\ 5,\ 9,\ 7 $ となる．$ A' $ のバブルソートによる交換回数は $ 2 $ である． - - - - - -

### Sample Explanation 3

最初から数列 $ A $ がソートされている場合でも，数列 $ A' $ を作る際に交換を行わなければならない．

## 样例 #1

### 输入

```
5
10
3
6
8
1```

### 输出

```
0```

## 样例 #2

### 输入

```
5
3
1
7
9
5```

### 输出

```
2```

## 样例 #3

### 输入

```
3
1
2
3```

### 输出

```
1```

# 题解

## 作者：未来姚班zyl (赞：7)

## 题目大意
有一个长为 $n$ 的序列 $a$。求将其任意两个数交换之后，对其冒泡排序时交换相邻两个数的最小次数。

$1\leqslant n\leqslant10^5$。

## 题目分析

（一篇十分详细的题解）。

乍一看，题目描述十分清晰，~~感觉是道暴力枚举题~~，但仔细一看，发现这题似乎并不简单。不过，既然要求冒泡排序的最小交换次数，就要思考它是否具有某些性质。不难想到，冒泡排序的交换次数就等于序列中逆序对的个数。原因是，每一次交换的前提是相邻两个数构成逆序对，而交换后就是把这个逆序对给调正，并且，其他元素的相对位置不受影响，即减少一个逆序对。

那么，这道题的题面就可以变为，有一个长为 $n$ 的序列 $a$。求将其任意两个数交换之后，新的序列中逆序对的最小个数。

这样的话，就能得到这道题的中心思路了：只要先计算总的逆序对对数，再找到所有方案中使得逆序对对数增量最小的方案。

第一部分可以直接分治求。

那么我们令一种方案对答案的贡献为完成该方案后逆序对减少的数量，则要求所有方案中最大的贡献。接下来就是要分析方案对答案的贡献到底是多少。

### $10$ 分做法
如果有元素相等似乎会使得分析变得困难，我们先考虑元素互不相等的情况。

假设选定了两个数 $a_l,a_r(l<r)$，显然，如果 $a_l<a_r$ 的话，逆序对数量肯定会增加（想一想，为什么）。所以只要能够找到一组 $l<r$ 且 $a_{l}>a_r$，则这组方案对应的逆序对数量绝对会减少（想一想，为什么）。绝对不会选择 $a_l<a_r$ 的情况。如果找不到呢？就说明数组已经有序了，一次交换必然会增加逆序对，不妨就交换一组相邻元素，这样只用再交换一次就行了。

在做完以上贪心后，就已经得到对于最终选择的方案，一定满足 $l<r$ 且 $a_l>a_r$，那么这组方案对答案的贡献就很容易得到：交换它们本身有 $1$ 的贡献，而对于位于中间的元素 $a_i(l<i<r)$，如果 $a_l<a_i$，则数对 $(i,l)$ 会产生 $-1$ 的贡献（即增加一组逆序对），反之，会产生 $1$ 的贡献（即减小一组逆序对），而如果 $a_i<a_r$，则会产生 $-1$ 的贡献，反之，产生 $1$ 的贡献。综上，再加上它们本身，对于这样一种方案 $(l,r)$，产生的贡献就为：

$\sum\limits_{l<i<r}{((a_i<a_l)+(a_i>a_r)-(a_i>a_l)-(a_i<a_r))}+1$

不过，这个式子看起来没什么实用性，别忘了 $a_{l}>a_{r}$，根据不等式的传递性，可以这样化简：

$\sum\limits_{l<i<r}{((a_i<a_l)+(a_i>a_r)-(a_i>a_l)-(a_i<a_r))}+1$

$=\sum\limits_{l<i<r}{((a_i<a_l)+(a_i>a_r)-((a_i>a_r)-(a_r<a_i<a_l))-((a_i<a_l)-(a_r<a_i<a_l)))}+1$

$=\sum\limits_{l<i<r}{2(a_r<a_i<a_l)+1}$

也就是查找区间内的指定值域内的元素个数，可以通过暴力枚举以 $O(n^3)$ 的时间复杂度拿到 $10$ 分（这里同时还能证明在这样的选择下贡献一定为正，反之为负）。
### $80$ 分做法
首先考虑贪心。

我们可以发现，假设当前最优解是 $(l,r)$，如果存在一个位置 $l_0$ 满足 $l_0<l$ 且 $a_{l_0}>a_l$，则无论是区间还是值域，都会比原来大，所以方案的 $(l_0,r)$ 是绝对不劣于 $(l,r)$ 的，对于右端点，相同的思路，如果存在一个位置 $r_0$ 满足 $r_0>r$ 且 $a_{r_0}<a_r$，则 $(l,r_0)$ 更优。所以，最优方案 $(l,r)$ 一定满足不存在任意一个位置 $x$，满足 $x<l$ 且 $a_x>a_l$，或者 $x>r$ 且 $a_x<a_r$。这等同于：**$a_l$ 是前缀最大值，$a_r$ 是后缀最小值。** 

求出来这个性质之后，我们只能缩小可能的方案数，枚举区间复杂度还是无法突破 $O(n^3)$，似乎并没有用。但其用处特别大，因为它为我们确定了这题最核心的性质：**单调性**。即它们在序列中各自单调递增。

单调性在区间上没用，不如考虑对于一个元素 $a_i$ 会对哪一些方案会产生贡献。由上面的式子得到，$a_i$ 会对 $(l,r)$ 产生贡献，当且仅当：$l<i<r$ 且 $a_i>a_r$ 且 $a_i<a_l$。然后，我们惊奇的发现，$a_l$ 和 $a_r$ 都是具备单调性的，这就说明，对于这个元素奏效的方案对应的左端点会形成一个区间，右端点也是如此，找到这两段区间只需 $O(\log n)$ 的复杂度。那么做法很显然了：将左端点视为 $y$ 轴，右端点视为 $x$ 轴，则单个元素的贡献可以视作一个权值为 $2$ 矩形，每个方案就是一个点，问题就变成了最大矩形覆盖，可以用扫描线加上线段树解决，复杂度 $O(n\log{n})$。

### $100$ 分做法

在分析完了以上做法后，满分做法也就简单了。就是在分析过程中加入 $i\neq j$ 且 $a_i=a_j$ 的情况。在过程中依次增加一类讨论就行了：
- 端点选择：如果选定了两个数 $a_l=a_r(l<r)$，则交换后的贡献为 $0$，绝对没有 $a_l>a_r$ 时高。但比 $a_l<a_r$ 时高。所以优先选第二种，其次选第一种，再次选第三种。
- 贡献计算，那就会多出两种情况 $a_i=a_l$，或 $a_i=a_r$。这两种情况都只会有 $1$ 的贡献，贡献变为 $\sum\limits_{l<i<r}{(2(a_r<a_i<a_l)-(a_i=a_l)-(a_i=a_r))+1}$。
- 贪心部分，需要记录的方案的左右端点应该分别为严格前缀最大值和严格后缀最小值（想一想，为什么）。

到此这道题就做完了，代码细节还是不少的，需要自己实践。此外，这题还有分治的做法，静候 dl 们讲解。

```cpp
#include<bits/stdc++.h>
#define I using
#define AK namespace 
#define IOI std 
I AK IOI;
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57) s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
#define ll long long
#define pf printf
#define cf scanf
#define rt return
#define pb push_back
#define fr(x,y,z) for(int (x)=(y);(x)<=(z);(x)++)
#define mid (l+r>>1)
#define lc x<<1,l,mid
#define rc x<<1|1,mid+1,r
#define search(x) for(int i=h[x];i;i=nxt[i])
const int mod=1e9+7;
const int N=1e5+5;
int n,a[N],b[N],lm[N],rm[N],cntl,cntr;
int s[N],top;
bool f;
ll sum,ans;
struct node{
	int x,l,r,w;
}t[N*4];
int tmp,cnt;
struct seg{ll w,lazy;}xd[N*4];
void getup(int x){
	xd[x].w=max(xd[x<<1].w,xd[x<<1|1].w);
}
void pushdown(int x){
	int laz=xd[x].lazy,L=x<<1,R=x<<1|1;
	xd[L].w+=laz,xd[L].lazy+=laz,xd[R].w+=laz,xd[R].lazy+=laz;
	xd[x].lazy=0;
}
void modify(int x,int l,int r,int L,int R,int k){
	if(R<l||L>r)return;
	if(l>=L&&r<=R){xd[x].w+=k,xd[x].lazy+=k;rt;}
	pushdown(x);
	modify(lc,L,R,k),modify(rc,L,R,k);
	getup(x);
}
void cdq(int l,int r){
	if(l>=r)rt;
	cdq(l,mid),cdq(mid+1,r);
	sort(b+l,b+mid+1),sort(b+mid+1,b+r+1);
	int L=mid,R=r;
	for(;R>=mid+1;R--){
		while(L>=l&&b[L]>b[R])L--;
		sum+=mid-L;
	}
}
bool cmp(node a,node b){
	rt a.x<b.x;
}
int findL(int x){
	int l=1,r=cntl,ans=cntl+1;
	while(l<=r){
		if(a[lm[mid]]>=a[x])ans=mid,r=mid-1;
		else l=mid+1;
	}
	return ans;
}
int findR(int x){
	int l=1,r=cntr,ans=0;
	while(l<=r){
		if(a[rm[mid]]<=a[x])ans=mid,l=mid+1;
		else r=mid-1;
	}
	return ans;
}
int main(){
	//freopen("sort.in","r",stdin);
	//freopen("sort.out","w",stdout);
	n=read();
	fr(i,1,n)b[i]=a[i]=read();
	cdq(1,n);
	if(sum==0){
		sort(a+1,a+n+1);
		fr(i,1,n-1)if(a[i]==a[i+1]){
			cout <<0<<endl;
			return 0;
		}
		cout <<1<<endl;
		return 0;
	}
	for(int i=n;i>=1;i--){
		while(top&&a[s[top]]<=a[i])top--;
		s[++top]=i;
	}
	while(top)lm[++cntl]=s[top--];
	fr(i,1,n){
		while(top&&a[s[top]]>=a[i])top--;
		s[++top]=i;
	}
	fr(i,1,top)rm[++cntr]=s[i];
	fr(i,1,n){
		int sl=findL(i),el=lower_bound(lm+1,lm+cntl+1,i)-lm-1,sr=upper_bound(rm+1,rm+cntr+1,i)-rm,er=findR(i);
		if(sl>el||sr>er||lm[sl]==i||rm[er]==i)continue;
		if(a[lm[sl]]==a[i]&&er-(a[rm[er]]==a[i])>=sr){
			t[++cnt]=node{sl,sr,er-(a[rm[er]]==a[i]),1};
			t[++cnt]=node{sl+1,sr,er-(a[rm[er]]==a[i]),-1};	
		}
		if(a[lm[sl]]==a[i])sl++;
		if(sl>el)continue;
		if(a[rm[er]]==a[i]){
			t[++cnt]=node{sl,er,er,1};
			t[++cnt]=node{el+1,er,er,-1};
			er--;
		}
		if(sr<=er){
			t[++cnt]=node{sl,sr,er,2};
			t[++cnt]=node{el+1,sr,er,-2};
		}
	}
	sort(t+1,t+cnt+1,cmp);
	top=1;
	for(int i=1;i<=cntl;i++){
		while(top<=cnt&&t[top].x==i){
			modify(1,1,cntr,t[top].l,t[top].r,t[top].w);
			top++;
		}
		ans=max(ans,xd[1].w);
	}
	cout <<sum-ans-1<<endl;
	return 0;
}
```


---

## 作者：DaiRuiChen007 (赞：6)

# JOI2013 Final E 题解





## 题目大意

> 给一个序列 $a_1,a_2,\dots,a_n$，交换某一对 $a_i,a_j(i<j)$，最小化交换后 $a$ 的逆序对数。
>
> 数据范围：$n\le 10^5$。

## 思路分析

为方便讨论，先假设 $a_i$ 互不相同，若 $a_i$ 可重也可类似解决。

首先考虑如何计算交换 $a_i,a_j$ 后的逆序对变化量，不妨设 $i<j,a_i>a_j$，那么对于每一个满足 $i<k<j,a_j<a_k<a_i$ 的 $k$，逆序对数会 $-2$。

因此假如我们建立二维平面并对每个 $i$ 插入点 $(i,a_i)$，逆序对变化数只需要知道矩形 $(i,a_i),(j,a_j)$ 中点的数量，用一棵主席树维护静态二维数点即可快速计算逆序对变化量。

继续观察 $a_i,a_j$ 满足的条件，容易发现如果存在某个 $i'$ 使得 $i'<i,a_{i}<a_{i'}$ ，那么 $i$ 一定不优，那么剩下的 $i$ 一定是 $a_1\sim a_n$ 的前缀最大值，同理 $a_j$ 一定是 $a_1\sim a_n$ 的后缀最小值。

观察下图有：

[![p9j2Rq1.png](https://s1.ax1x.com/2023/05/30/p9j2Rq1.png)](https://imgse.com/i/p9j2Rq1)

其中 $S_1,S_2,S_3,S_4$ 表示对应矩形区域内点的数量，不妨假设 $a_i$ 在与 $a_{j'}$ 交换时更优，那么显然有 $S_2\ge S_3+S_4$，因此我们知道 $S_2-S_3-S_4\ge 0$，此时我们知道，$a_{i'}$ 与 $a_{j'}$ 交换一定比与 $a_{j}$ 优，因为 $S_1+S_2-S_3\ge S_2-S_3-S_4\ge 0$，因此 $S_1+S_2\ge S_3$，所以交换 $a_{i'}$ 和 $a_{j'}$ 优于交换 $a_{i'}$ 和 $a_j$。

因此假设 $a_i$ 与 $f_i$ 交换更优，那么 $f_i$ 一定单调不降，因此可以用分治优化求值的过程，转移的代价函数用主席树维护。

注意到当 $a_i$ 可以相同时，交换 $a_i,a_j$ 后逆序对还要加上 $a_{i+1}\sim a_{j-1}$ 中 $a_i$ 和 $a_j$ 的数量。

时间复杂度 $\mathcal O(n\log^2n)$

## 代码呈现

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=1e5+1,INF=1e9;
int n,a[MAXN];
class SegmentTree {
    private:
        struct Node {
            int ls,rs,sum;
        }    tree[MAXN*32];
        int siz,root[MAXN];
        inline void pushup(int p) { tree[p].sum=tree[tree[p].ls].sum+tree[tree[p].rs].sum; }
        inline void Modify(int u,int l,int r,int lst,int &pos) {
            pos=++siz;
            if(l==r) { tree[pos].sum=tree[lst].sum+1; return ; }
            int mid=(l+r)>>1;
            if(u<=mid) {
                tree[pos].rs=tree[lst].rs;
                Modify(u,l,mid,tree[lst].ls,tree[pos].ls);
            } else {
                tree[pos].ls=tree[lst].ls;
                Modify(u,mid+1,r,tree[lst].rs,tree[pos].rs);
            }
            pushup(pos);
        }
        inline int __Count(int ul,int ur,int l,int r,int pos) {
            if(ul>ur||!pos) return 0;
            if(ul<=l&&r<=ur) return tree[pos].sum;
            int mid=(l+r)>>1,res=0;
            if(ul<=mid) res+=__Count(ul,ur,l,mid,tree[pos].ls);
            if(mid<ur) res+=__Count(ul,ur,mid+1,r,tree[pos].rs);
            return res;
        }
        inline int Count(int lo,int hi,int l,int r) {
            return __Count(lo,hi,1,n,root[r])-__Count(lo,hi,1,n,root[l-1]);
        }
    public:
        inline void Build() {
            for(int i=1;i<=n;++i) Modify(a[i],1,n,root[i-1],root[i]);
        }
        inline int Query(int l,int r) {
            if(l>=r) return -INF;
            if(a[l]<a[r]) return -Count(a[l]+1,a[r]-1,l+1,r-1)-Count(a[l],a[r],l+1,r-1)-1;
            if(a[l]==a[r]) return 0;
            return Count(a[r]+1,a[l]-1,l+1,r-1)+Count(a[r],a[l],l+1,r-1)+1;
        }
        inline ll Init() {
            ll ans=0;
            for(int i=1;i<=n;++i) ans+=__Count(a[i]+1,n,1,n,root[i]);
            return ans;
        }
}    TR;
int p[MAXN],cp,q[MAXN],cq,f[MAXN];
inline void Solve(int l,int r,int L,int R) {
    if(l>r) return ;
    int M=0,mid=(l+r)>>1;
    for(int i=L;i<=R;++i) {
        int v=TR.Query(p[mid],q[i]);
        if(v>f[mid]) f[mid]=v,M=i;
    }
    Solve(l,mid-1,M,R),Solve(mid+1,r,L,M);
}
signed main() {
    scanf("%d",&n);
    vector <int> vals;
    for(int i=1;i<=n;++i) scanf("%d",&a[i]),vals.push_back(a[i]);
    sort(vals.begin(),vals.end()),vals.erase(unique(vals.begin(),vals.end()),vals.end());
    for(int i=1;i<=n;++i) a[i]=lower_bound(vals.begin(),vals.end(),a[i])-vals.begin()+1;
    TR.Build();
    for(int i=1,v=0;i<=n;++i) if(a[i]>v) p[++cp]=i,v=a[i];
    for(int i=n,v=n+1;i>=1;--i) if(a[i]<v) q[++cq]=i,v=a[i];
    fill(f+1,f+cp+1,-INF);
    Solve(1,cp,1,cq);
    int ans=-INF;
    for(int i=1;i<=cp;++i) ans=max(ans,f[i]);
    printf("%lld\n",TR.Init()-ans);
    return 0;
}

```



---

## 作者：CmsMartin (赞：6)

[更好的阅读体验](http://cmsblog.top/archives/loj535libreojround6%E8%8A%B1%E7%81%AB)

[$\mathcal{Link}$](https://loj.ac/p/535)

**本题解不讨论相等情况。请自行讨论。**

## 思路

如果只能交换相邻的两项，那么答案就是逆序对数量。于是就可以有最裸的暴力枚举第一次可以交换不相邻的两个位置。时间复杂度 $\mathcal{O(n^3 \log n)}$。这样子很慢，有一个显然的事情就是我们交换的两项一定满足：$i > j, h_i < h_j$。如果不构成逆序对肯定不优秀。

设交换之前的逆序对数量为 $A$。则交换 $h_i, h_j(h_i > h_j, i < j)$ 后逆序对数量变成：$A' = A -1 - \sum_{k=i+1}^{j-1}([h_k > h_j] + [h_k < h_i] - [h_k < h_j] - [h_k > h_i]) = A - 1 - 2\sum_{k=i+1}^{j-1}{[h_j < h_k < h_i]}$。答案就是 $A'+1$。

将 $(i,h_i)$  看成二维平面上的一个点，答案就可以通过数左上角为 $(i,h_i)$，右下角为 $(j,h_j)$ 的矩阵中点的数量，时间复杂度 $\mathcal{O}(n^2)$。

可以发现，我们选择的 $i,j$ 必然满足 $(i,h_i)$ 左上方没有东西，$(j,h_j)$ 右下方没有东西，这样肯定不劣。这样已经可以分治 + 主席树平凡在 $\mathcal{O}(n \log^2 n)$ 时间内求解了。但是非常不好写而且常数大

考虑每一个点 $(x,h_x)$ 被哪些矩阵覆盖。设 $l$ 表示最小的 $i$ 满足 $h_i > h_x$，$r$ 表示最大的 $j$ 满足 $h_j < h_x$。那么有 $i \in [l, x - 1], j \in [x + 1, r]$ 表示的以 $(i, h_i)$ 作为左上角，以 $(j, h_j)$ 作为右下角的矩形都是可行解。那么我们将这个矩形重新看做平面上的点 (i, j)。所有可以覆盖 $x$ 的矩阵就在平面上形成了一个矩形，以 $(l, x + 1)$ 为左下角，以 $(x - 1, r)$ 为右上角。

这样问题就转化为求一个被最多矩阵覆盖的点的覆盖次数的最大值。扫描线维护即可。

复杂度是优美的 $\mathcal{O}(n \log n)$。

## 代码

https://loj.ac/s/1863642

---

## 作者：lzyqwq (赞：0)

原来原题在这里。这个题在 loj 上有一个（loj535），之前 xyd 某次 NOIp 模拟赛又出了一次。现在是第三次见了。

考虑最多可以减少多少逆序对。容易求出原逆序对数。

首先一定交换一对逆序对 $(i,j)$，可以发现减少的逆序对数为开区间 $(i,j)$ 中分别与 $i$ 和 $j$ 构成的逆序对数。

把 $(i,a_i)$ 看成平面上的点。那么每个被以 $(i,a_i)$ 为左上角、$(j,a_j)$ 为右下角的矩形包含的点都会起贡献。其中上下边界上的点贡献为 $1$，其余点贡献为 $2$。如果选择的逆序对 $(u,v)$ 使得存在 $i<u$ 且 $a_i\ge a_u$ 那么一定不优。也就是说 $a_u$ 一定是前缀最大值。同理 $a_v$ 是后缀最小值。

那么可以处理出两个序列表示可供选择的 $u,v$。考虑构造一个新平面，点 $(x,y)$ 的权值表示：在两个序列中分别选第 $x$ 和第 $y$ 个元素，所减少的逆序对数。

矩形除了两个角不会包含序列上的点，考虑每个不在序列中的点 $(i,a_i)$ 的贡献。此时要求左上角、右下角构成的矩形包含这个点。容易发现符合条件的左上角、右下角在对应的序列上编号均构成一个区间。容易二分得到这两个区间 $[l,r],[p,q]$。

此时讨论一下 $a_i$ 和端点的大小关系，容易发现 $i$ 给 $x\in [l,r],y\in [p,q]$ 内的所有点加上 $1$ 或 $2$。其中一共会拆分成 $\mathcal{O}(1)$ 个区域。

现在需要支持矩形加、全局最大值。扫描线维护即可。

时间复杂度 $\mathcal{O}(n\log n )$，空间复杂度 $\mathcal{O}(n)$。

---

## 作者：_XHY20180718_ (赞：0)

提供一种分治 + 移动动态维护贡献的 $O(n\log n)$ 做法，请注意此题解不会讨论重复元素的处理。

首先对于两个数，冒泡排序交换的充要条件是 $i<j$ 且 $a_i>a_j$，即逆序对的数量，我们需要找到交换两个数后逆序对的最少数量。

考虑交换两个数对逆序对数量的影响，离散化后，将下标看作 $x$ 轴，值看成 $y$ 轴，那么如果两个点互为逆序关系（设为 $(lx,ry)$ 和 $(rx,ly)$），他们之间的矩形（即由 $(lx,ly)$，$(lx,ry)$，$(rx,ly)$ 和 $(rx,ry)$ 四个点所构成的矩形）中的点（数量为 $s(lx,rx)$）与两点之间构成的逆序对加上两点本身所构成的的逆序对均变成正序对，一共有 $2s+1$ 的逆序对消失。

现在我们要找一个包含点数量最多的且由坐标轴上两点所构成的矩形，可以寻找一些性质，如下图：（搬自某篇题解）

![图怎么挂了555](https://s1.ax1x.com/2023/05/30/p9j2Rq1.png)

发现若 $s(i,j)<s(i,j')$，两边同时减去橙色部分，那么一定有 $s4+s3<s2$，故 $s3<s1+s2$，两边同时加上蓝色部分，即 $s(i',j)<s(i',j')$。如果 $s(i,j')$ 比 $s(i,j)$ 更优，那么我们选择 $s(i',j)$ 是没有意义的。

尝试拓展一下这个性质，固定 $i$，若我们的最优决策为 $j$（即在所有右端点中，矩形 $(x_i,x_j,y_i,y_j)$ 包含的点最多），只需要考虑形如 $ii<i,j<jj$ 或 $$ii>i,jj>j$$ 的点了，因为其余的情况一定更劣，**也就是说决策 $i$ 对于 $j$ 有单调性**。

接下来考虑分治，固定决策点 $i=(l+r)/2$，枚举这一层的所有的被决策点 $j$，求出第 $i$ 个前缀最大值与后缀最小值（因为他们才有可能是最优解，注意保证单调递增），即每次枚举都是 $O(len)$ 的，加起来一共是 $O(n\log n)$。

现在还有一个问题，如何快速维护矩形中的点数，这一点其他题解由于直接分治 $x$ 坐标而不是前缀最大值和后缀最小值的下标导致基本都用的主席树，常数大并且复杂度高。

注意我们的前缀最大值和后缀最小值有一个性质：**单调**，于是我们每次求的矩形右端点坐标必然单调递增且在此范围内，所以我们可以直接上莫队算法，对其进行暴力移动，每层分治移动次数都是 $O(len)$ 的，故总复杂度为 $O(n\log n)$。

参考代码：

```cpp
#include<bits/stdc++.h>
#define lowbit(x) ((x)&-(x))
#define max(x,y) (x>y?x:y)
using namespace std;
const int N=1e6+5;
int n,a[N],p[N],ans;
int lx,rx,ly,ry,Res;
int stq[N],sth[N],rq,rh;
int b[N],c[N],nn;
inline int qry(int x){
    int res=0;
    for(;x;x-=lowbit(x))
        res+=c[x];
    return res;
}
inline void upd(int x,int k){
    for(;x<=nn;x+=lowbit(x))
        c[x]+=k;
}
inline int f(int LX,int RX,int LY,int RY){
    while(lx>LX){
        --lx;
        if(ly<=a[lx]&&a[lx]<=ry)
            ++Res;
    }
    while(rx<RX){
        ++rx;
        if(ly<=a[rx]&&a[rx]<=ry)
            ++Res;
    }
    while(ly>LY){
        --ly;
        if(lx<=p[ly]&&p[ly]<=rx)
            ++Res;
    }
    while(ry<RY){
        ++ry;
        if(lx<=p[ry]&&p[ry]<=rx)
            ++Res;
    }
    while(lx<LX){
        if(ly<=a[lx]&&a[lx]<=ry)
            --Res;
        ++lx;
    }
    while(rx>RX){
        if(ly<=a[rx]&&a[rx]<=ry)
            --Res;
        --rx;
    }
    while(ly<LY){
        if(lx<=p[ly]&&p[ly]<=rx)
            --Res;
        ++ly;
    }
    while(ry>RY){
        if(lx<=p[ry]&&p[ry]<=rx)
            --Res;
        --ry;
    }
    return Res;
}
inline void calc(int l,int r,int ll,int rr){
    if(l>r)return;
    int mid=l+((r-l)>>1),mm=ll,res=-N;
    for(int i=ll; i<=rr; ++i){
        f(stq[mid],sth[i],a[sth[i]],a[stq[mid]]);
        if(stq[mid]>=sth[i]||a[sth[i]]>=a[stq[mid]])continue;
        int fm=f(stq[mid],sth[i],a[sth[i]],a[stq[mid]]);
        if(res<fm)mm=i,res=fm;
    }
    ans=max(ans,2*res-3);
    if(res<=-N)
        while(mm<=rr&&stq[mid]>=sth[mm])
            ++mm;   
    calc(l,mid-1,ll,mm),calc(mid+1,r,mm,rr);
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n;int res=0;
    for(int i=1; i<=n; ++i)
        cin>>a[i],b[i]=a[i];
    sort(b+1,b+1+n);
    nn=unique(b+1,b+1+n)-b-1;
    for(int i=1; i<=nn; ++i)
        a[i]=lower_bound(b+1,b+1+nn,a[i])-b,p[a[i]]=i;
    for(int i=1; i<=n; ++i){
        res+=qry(nn)-qry(a[i]);
        upd(a[i],1);
    }
    for(int i=1; i<=n; ++i)
        if(!rq||a[stq[rq]]<a[i])
            stq[++rq]=i;
    for(int i=n; i>=1; --i)
        if(!rh||a[sth[rh]]>a[i])
            sth[++rh]=i;
    sort(sth+1,sth+1+rh);
    lx=1,rx=0,ly=1,ry=0,Res=0;
    calc(1,rq,1,rh);
    cout<<res-ans<<'\n';
    return 0;
}
//此代码未考虑重复数
```

---

## 作者：Little09 (赞：0)

先判掉原序列已经排好序的情况，此时答案是 $0$ 或 $1$。其他情况总可以使逆序对减少。

先做排列。发现交换 $p_x,p_y(x<y,p_x>p_y)$ 的贡献是 

$$1+2\sum_{i=x+1}^{y-1}[p_y<p_i<p_x]$$

容易发现答案选择的 $x,y$ 需要满足 $p_x$ 前面不存在比他大的（否则应该选那个），也就是前缀最大值，同时 $p_y$ 也要是后缀最小值。这样一来，我们提出所有前缀最大值，后缀最小值。放到平面里去，那么每个 $p_i$ 的贡献就是一个矩形，做一个扫描线维护最大值就行。

相同的情况也是容易的，可以发现当 $p_i=p_x$ 或 $p_i=p_y$ 时，贡献从 $2$ 变成了 $1$，于是只要加入几个矩形就行。

---

