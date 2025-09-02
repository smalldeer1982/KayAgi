# faebdc 的烦恼

## 题目背景

upd on On July 29, 2024：加入一组 hack 数据，之前的数据均满足 $q\le 10^5$。

鸟哥（faebdc）自从虐暴 NOIP2013 以来依然勤奋学习，每天上各种 OJ 刷题，各种比赛更是不在话下。但这天他遇到了一点小小的麻烦：在一届“Orz 鸟哥杯”上，题目是在是太多了！鸟哥看得头晕眼花，他需要你的帮助。

## 题目描述

这场比赛共有 $n$ 道题，每道题都有一个难度值 $a_i$，由于 wangxz 神犇已经提前帮助鸟哥将这些难度值升序排列，所以鸟哥并不想知道哪些题难度低或者高，他只想知道在某些题目 $a_l,a_{l+1},\ldots,a_r$中，出现最多的难度值出现的次数。


你的任务就是对于鸟哥的每一次询问 $(l, r)$，告诉他在从 $a_l$ 到 $a_r$ 这 $(r-l+1)$ 道题之中，出现最多的难度值出现的次数（询问共有 $q$ 次）。


如果你成功地帮助了鸟哥，鸟哥将会带你通过省选。


## 说明/提示

#### 数据规模与约定

对于全部的测试点，保证 $1 \leq n \leq 10^5$，$1 \leq q \leq 2\times 10^5$，$-10^5 \leq a_i \leq 10^5$，$1 \leq l \leq r \leq n$。

## 样例 #1

### 输入

```
9 1
1 1 1 2 2 3 3 4 4
3 8```

### 输出

```
2
```

# 题解

## 作者：MY（一名蒟蒻） (赞：21)

[P1997 faebdc 的烦恼](https://www.luogu.com.cn/problem/P1997)

题意分析：让您求出区间众数出现的次数。

---
区间问题考虑莫队。

加入操作非常好写，如果 $\text{x}$ 的出现个数大于当前答案，直接更新即可。

删除操作要考虑删掉的 $\text{x}$ 出现次数是不是会影响答案。

分类讨论
1. 当出现次数小于当前 $\text{ans}$ ，对答案没有影响；
2. 当出现次数等于当前 $\text{ans}$ ，且只有这个数出现了 $\text{ans}$ 次， $\text{ans}$ 减一；
3. 当出现次数等于当前 $\text{ans}$ ，且不止一个数出现了 $\text{ans}$ 次，对答案没有影响。

综上所述，我们需要开一个**辅助数组记录出现了 $i$ 次的数的个数。**（可能有点拗口，没明白建议多读几遍）如果只有一个数 $\text{ans}$ 就需要减一。

**注意事项**： 值域中有负数，但是并不大，我们懒得写离散化，于是开双倍空间然后全体~~起立~~加上 $\max(n)$ ，也就是 $10^5$ 。

一个小优化：没有必要在一个数字出现次数增加时改变之前的辅助数组记录的数值，因为求的是 $\max$ ，之前的不会对答案造成影响，在删除的时候也会被删掉。

还没明白就看看代码吧。
```cpp
#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

const int N=1e5+10;

int n,m,a[N],cnt[N << 1],len,bl[N],ans[N*2],maxn,sum[N];//cnt[i]:数字i出现的个数；sum[i]:出现次数为i的数字个数 
struct query
{
	int l,r,id;
	bool operator <(const query x) const {return bl[l]^bl[x.l]? l<x.l:bl[l]&1? r<x.r:r>x.r;}
} q[N << 1];

inline void add(int x)
{
	sum[++cnt[a[x]]]++;
	if(cnt[a[x]] > maxn) maxn=cnt[a[x]];
	return ;
}
inline void del(int x)
{
	if(sum[cnt[a[x]]] == 1 && maxn == cnt[a[x]]) maxn--;
	sum[cnt[a[x]]--]--;
	return ;
}

int main()
{
// 	freopen("work.in","r",stdin); freopen("work.out","w",stdout);
	scanf("%d%d",&n,&m);
	len=sqrt(n);
	for(int i=1;i<=n;i++) {scanf("%d",&a[i]); a[i]+=N-10; bl[i]=(i-1)/len+1;}
	for(int i=1;i<=m;i++) {scanf("%d%d",&q[i].l,&q[i].r); q[i].id=i;}
	sort(q+1,q+1+m);
	int l=1,r=0;
	for(int i=1;i<=m;i++)
	{
		while(l > q[i].l) add(--l);
		while(r < q[i].r) add(++r);
		while(r > q[i].r) del(r--);
		while(l < q[i].l) del(l++);
		ans[q[i].id]=maxn;
	}
	for(int i=1;i<=m;i++) printf("%d\n",ans[i]);
// 	fclose(stdin); fclose(stdout);
	return 0;
}
```
建议切完这题后做一下[P3709 大爷的字符串题](https://www.luogu.com.cn/problem/P3709)，在此安利一下本人关于这题的[题解](https://www.luogu.com.cn/blog/nizhuan/solution-p3709)。

## Thank you for your reading!
您的点赞和评论是对作者最好的支持！

---

## 作者：皎月半洒花 (赞：5)

这是一篇主席树的题解。

我们思考主席树的本质，其实就是可以刨出一个区间$l,r$让我们可以在树高复杂度$log$的基础上进行一波常规线段树不能进行的、权值查找操作。那么由于主席树本质上是一棵权值线段树，所以直接$return$的$val$一定是最小的（只要我们保证先查找左子树）。

以上是老生常谈，~~是我从自己以前整理过的笔记扒拉出来的~~。

而对于这道题，我们考虑二分。为什么满足二分的性质呢？比较显然的是，如果我们通过查找出现次数为$k$的数，发现访问的值为`NULL`，那么对于任何$k+x(x \in \mathbb{N})$，访问的$val$都将会是`NULL`。

那么我们就可以二分实现(这份代码有$81pts~with$ `TLE*2`)


```cpp
int build(const int &l, const int &r){
    register int rt = ++ cnt ;
    sum[rt] = 0 ;
    if(l < r){
    	register int mid = (l + r) >> 1 ;
        L[rt] = build(l, mid), R[rt] = build(mid + 1, r) ;
    }
    return rt;
}
int update(const int &last, const int &l, const int &r, const int &x){
    register int rt = ++ cnt ;
    sum[rt] = sum[last] + 1, R[rt] = R[last], L[rt] = L[last] ;
    if (l < r){
    	register int mid = (l + r) >> 1 ;
        if (x <= mid) L[rt] = update(L[last], l, mid, x) ;
        else  R[rt] = update(R[last], mid + 1, r, x) ;
    }
    return rt ;
}
int query(const int &Left,const int &Right,const int &l, const int &r, const int &k){
    if (l == r) return aft[l] ; 
    register int mid = (l + r) >> 1, qwq ;
    if (sum[Right] - sum[Left] < k) return -1 ;
    int x = sum[L[Right]] - sum[L[Left]], y = sum[R[Right]] - sum[R[Left]] ;
    if (x >= k) 
        if ((qwq = query(L[Left], L[Right], l, mid, k)) > 0) return qwq ;
    if (y >= k) 
        if ((qwq = query(R[Left], R[Right], mid + 1, r, k)) > 0) return qwq ;
    return -1 ;
}
int main(){
    cin >> N >> M; for (i = 1; i <= N; i ++)  base[i] = qr() + ADD, aft[i] = base[i] ;
    sort (aft + 1, aft + N + 1), Len = unique(aft + 1, aft + N + 1) - (aft + 1), T[0] = build(1, Len) ;
    for (i = 1; i <= N; i ++) pos = lower_bound(aft + 1, aft + Len + 1, base[i]) - aft, T[i] = update(T[i - 1], 1, Len, pos) ;
    for (i = 1; i <= M; i ++){
        scanf("%d%d", &a, &b) ;
        register int l = 1, r = b - a + 1, ans = 1 ;
        while (l <= r){
           	register int mid = (l + r) >> 1 ;
            if (query(T[a - 1], T[b], 1, Len, mid) > 0) ans = mid, l = mid + 1 ; 
            else r = mid - 1 ;
        }
        printf("%d\n", ans) ;
    }
}
```
但事实上，我们认知中的主席树上二分的复杂度应该是$\Theta(q \log ^2n)$，其中一个$\log$用来二分，一个$\log$用来查找。但事实上我们这么写，其复杂度并不是对的。因为我们为了防止漏掉可行解，每次需要查询两棵子树，而查询两棵子树的复杂度，最坏情况下却是单次$\Theta(2^n)$的。那么复杂度就会完全爆炸，以至于最后我不得不写两个$subtask$用暴力去$AC$（事实上，这种情况下的主席树是没有暴力快的）。

换句话说，这复杂度特么根本不对……

那么接下来是一个剪枝，由巨佬[乖≮闹√€](https://www.luogu.org/space/show?uid=70863)提出，并且时间效率十分的高。

大体思路就是，考虑对于主席树上的每一个点维护一个$max$一个$min$，记录区间内**单个数值出现的最大次数和最小次数**，那么我们在$check$的时候就可以直接用这种方式判——如果$r$版本的主席树内出现的最大次数减去$l-1$版本内出现的数的最小次数$k<q$（$q$是二分出的$val$），那么一定不满足。

事实上，这种剪枝并不是最优性剪枝，但是通过此题足矣：

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>

#define il inline
#define ADD 393216
#define rr register
#define MAXN 100073

using namespace std ;
int a, b, c, pos, N, base[MAXN], mx[(MAXN << 5) + 1], mn[(MAXN << 5) + 1], aft[MAXN], M, i ;
int cnt, Len, T[(MAXN << 5) + 1], L[(MAXN << 5) + 1], R[(MAXN << 5) + 1], sum[(MAXN << 5) + 1] ;

il int qr(){
    register int k = 0, f = 1 ; char c = getchar() ;
    while(!isdigit(c)){ if (c == '-') f = -1 ; c = getchar() ; }
    while(isdigit(c)) k = (k << 1) + (k << 3) + c - 48, c = getchar() ;
    return k * f ;
}
int update(const int &last, const int &l, const int &r, const int &x){
    register int rt = ++ cnt, mid ;
    sum[rt] = sum[last] + 1, R[rt] = R[last], L[rt] = L[last] ;
    if (l == r){
    	mx[rt] = mn[rt] = sum[rt] ; 
        return rt ;
    }
    mid = (l + r) >> 1 ;
    if (x <= mid) L[rt] = update(L[last], l, mid, x) ;
    else  R[rt] = update(R[last], mid + 1, r, x) ;
    mn[rt] = min(mn[L[rt]], mn[R[rt]]), mx[rt] = max(mx[L[rt]], mx[R[rt]]) ;
    return rt ;
}
bool query(const int &Left,const int &Right,const int &l, const int &r, const int &k){
    if (l == r) return 1 ; rr int mid = (l + r) >> 1, qwq ;
    if (mx[L[Right]] - mn[L[Left]] >= k && query(L[Left], L[Right], l, mid, k)) return 1 ;
    if (mx[R[Right]] - mn[R[Left]] >= k && query(R[Left], R[Right], mid + 1, r, k)) return 1 ;
    return 0 ;
}
int main(){
    cin >> N >> M; for (i = 1; i <= N ; ++ i)  base[i] = qr() + ADD, aft[i] = base[i] ;
    sort (aft + 1, aft + N + 1), Len = unique(aft + 1, aft + N + 1) - (aft + 1) ;
    for (i = 1; i <= N ; ++ i) pos = lower_bound(aft + 1, aft + Len + 1, base[i]) - aft, T[i] = update(T[i - 1], 1, Len, pos) ;
    for (i = 1; i <= M ; ++ i){
        a = qr(), b = qr() ;
        register int l = 1, mid, r = b - a + 1, ans = 1 ;
        while (l <= r){
           	mid = (l + r) >> 1 ;
            if (query(T[a - 1], T[b], 1, Len, mid)) ans = mid, l = mid + 1 ; 
            else r = mid - 1 ;
        }
        printf("%d\n", ans) ;
    }
}
```

最后是_rqy提的$hack$思路：

![](https://cdn.luogu.com.cn/upload/pic/54752.png)

---

## 作者：SIXIANG32 (赞：4)

改码风后的第一篇题解呢 qwq  
闲话少说，切入正题——  

---
简单点说，这道题就是让我们找区间众数的出现次数。  
算得上是一道~~我没写过的~~经典题了吧，因为 $n\le 10^5$，并且可离线，我们就可以用莫队来做。  
我们用莫队维护两个数组，$awa$ 和 $qwq$，$awa_i$ 表示有多少个出现了 $i$ 次的数，$qwq_i$ 表示值为 $i$ 的数出现了多少次。  
毕竟是莫队，考虑两个情况：添加和删除。  

添加一个值为 $a_i$ 的数，相应的，$qwq_{a_i}$ 会增加， $awa_{qwq_{a_i}}$ 也会增加（这里的 $qwq_{a_i}$ 是增加过后的）。我们就可以在这个时候更新答案 $ans$ 为 $\max(ans,qwq_{a_i})$。  

删除一个值为 $a_i$ 的数，那么 $awa_{qwq_{a_i}}$ 要减一，$qwq_{a_i}$ 也要减一，如果答案是从 $a_i$ 这个状态转移而来，答案还要减一。  

剩下的就是莫队板子了，代码：  
```cpp
#include <cstdio>
#include <cmath>
#include <algorithm>
#define MAXN 200000
#define QWQ printf("qwq");
using namespace std;
struct node {
	int l,r,cl,ind;
}q[MAXN+10];
int a[MAXN+10],b[MAXN+10],qwq[MAXN+10],awa[MAXN+10],Ans[MAXN+10],ans;
int max(int x,int y) {return ((x > y)?(x):(y));}
bool cmp(node &x,node &y) {
	return ((x.cl != y.cl)?(x.l < y.l):((x.cl & 1)?(x.r < y.r):(x.r > y.r)));
}
void add(int x) {
	awa[++qwq[a[x]]]++;
	ans = max(ans,qwq[a[x]]);
}
void del(int x) {
	if(awa[qwq[a[x]]] == 1 && qwq[a[x]] == ans)
		ans--;
	awa[qwq[a[x]]--]--;
}
int main() {
	int n,m;
	scanf("%d%d",&n,&m);
	for(int p = 1; p <= n; p++)
		scanf("%d",&a[p]),b[p] = a[p];
	sort(b + 1,b + n + 1);//离散化，因为这里有负数
	int LL = unique(b + 1,b + n + 1) - b - 1,len = sqrt(n);
	for(int p = 1; p <= n; p++)
		a[p] = lower_bound(b + 1,b + LL + 1,a[p]) - b;
	for(int p = 1; p <= m; p++) {
		scanf("%d%d",&q[p].l,&q[p].r);
		q[p].cl = (q[p].l - 1) / len,q[p].ind = p;
	}
	sort(q + 1,q + m + 1,cmp);
	int l = 1,r = 0;
	for(int p = 1; p <= m; p++) {
		while(l < q[p].l) del(l++);
		while(l > q[p].l) add(--l);
		while(r < q[p].r) add(++r);
		while(r > q[p].r) del(r--);
		Ans[q[p].ind] = ans;
	} 
	for(int p = 1; p <= m; p++)
		printf("%d\n",Ans[p]);
}
PS：刚转码风，很多地方手刹不住还是写成老样子，有点不太自然，见谅 qwq
```

---

## 作者：依依 (赞：4)

解：莫队（不能说是裸题吧）

我们开两个桶：

sum[i]表示i这个数的出现次数；

cnt[i]表示出现次数为i的数的个数 

即目前出现次数的最大值为tot;

当指针外扩时，更新sum[ ],cnt[ ],如果出现了比tot大的,tot++;

当指针内缩时，更新sum[ ],cnt[ ],如果  cnt[tot]==0 那么tot--;
[代码](http://www.cnblogs.com/adelalove/p/8509877.html)
还有，这道题可以说和“大爷的字符串”那道题代码简直一样   
只是少了个负号
貌似分块也可做？

---

## 作者：1沃尔克 (赞：3)

题目要求输出询问区间的最多的数值所出现的次数。

首先，我们把每个区间挑出来并标号，看起来就像是离散化，得到ls数组，同时记录区间的左右端点到l，r数组，记录区间长度到st数组。

这样，我们就记下了区间的所有信息。这时，我们就可以发现题目要求变成了求st数组所在询问区间的最大值，两端不完整区间只要端点相减就好啦。

而对于这种求某个区间的最值问题，可以有ST和线段树等，
而对此题（没有区间修改而且多次询问），ST的程序实现更简单，运行速度更快。预处理O（nlogn），询问O(1)。

ST算法利用了倍增的思想，以达到logn的水平。

另f[i][j]为区间[i,i+2^j-1]的最值，区间共2^j个元素，从中间分成两部分，每份2^(j-1),显然f[i][j]=max(f[i][j-1],f[i+2^(j-1)][j-1];所以询问区间[l,r]的最值，首先要找到最大的x满足2^x<=r-l+1,可以用STL里的log函数，但效率不高。有两种递推方法。

1.
```cpp
lg[1]=0;
for(int i=2;i<=n;i++) lg[i]=lg[i/2]+1;
```
2.
```cpp
for(int i=1;i<=;i++) lg[i]=lg[i-1]+(1<<lg[i-1]==i)
```
第一种从二开始，得到lg[i]满足i/2<1<<lg[i]<=i;

第二种从一开始，得到lg[i]满足1<<lg[i]>i;

两者刚好相差1，本题用第一种或者第二种减1都可以，其实两者没有本质区别，但后这显得更高大上。

处理完lg就可以执行ST基本方针啦。

对于区间[l,r](内部区间完整，即去除两端不完整区间）
k=lg[r-l+1]；

ans=max(st[l][k],st[r-(1<<k)+1][k];//+1很重要，否则取不到最后一个区间。

code
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n,q,a[100005];
int pre,cur,num,ls[100005];
int st[100005][18],l[100005],r[100005],lg[100005];
int rmq(int x,int y)
{
	if(x>y) return 0;
	int k=lg[y-x+1];
	return max(st[x][k],st[y-(1<<k)+1][k]);
}
int main()
{
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++)
	scanf("%d",&a[i]);
	pre=1;cur=1;
	while(cur<=n)
	{
		++num;
		while(a[cur]==a[pre]) ls[cur]=num,cur++;
		l[num]=pre;r[num]=cur-1;st[num][0]=cur-pre;pre=cur;
	}
	for(int i=2;i<=num;i++)
	lg[i]=lg[i/2]+1;
	for(int i=1;i<=17;i++)
		for(int j=1;j<=num;j++)
		st[j][i]=max(st[j][i-1],st[j+(1<<(i-1))][i-1]);
	for(int i=1,x,y;i<=q;i++)
	{
		int ans=0;
		scanf("%d%d",&x,&y);
		int px=ls[x],py=ls[y];
		if(px==py)
		{
			printf("%d\n",y-x+1);
			continue;
		}
		ans=max(ans,r[px]-x+1);
		ans=max(ans,y-l[py]+1);
		ans=max(ans,rmq(px+1,py-1));
		printf("%d\n",ans);
	}
	return 0;
}
```

致谢

---

## 作者：夏色祭 (赞：3)

#没人发题解额。。。

#一次过。。。（逃

#简单的线段树（滑稽）

我们先把相同的数值的区间看成是一个点（整题最关键的部分，蒟蒻的我想到这个，整道题就直接迎刃而解了），用l[i]和r[i]表示第i个区间的头和尾，一个数组记录第i个区间数的个数，还有一个数组记录第i个数属于哪个区间，这些做个O(n)的预处理就行了。

然后建树，对于每次读入的x~y，首先处理头上和尾上多出来的部分，剩下的部分用线段树的常规操作query就行了，最后在三者之中找个max就行了。。。

注意两种特殊情况，x~y只有一个区间则输出y-x+1，x~y有两个区间则不用query，直接输出头上和尾上多出来的部分的max

线段树不懂的同学请自行百度。。。

献上没有66666a代码丑陋的AC代码：




```cpp
uses math;
type
  tree=record
  sum,l,r:longint;
end;
var 
  a:array[0..400001]of tree;
  b,l,r,c,tt:array[0..100001]of longint;
  n,m,i,x,y,len,max1,max2,ans:longint;
procedure build(k,l,r:longint);
var
  mid:longint;
begin
  a[k].l:=l; a[k].r:=r;
  if l=r then 
    begin
      a[k].sum:=tt[l];
      exit;
    end;//叶子结点
  mid:=(l+r) >> 1;
  build(k*2,l,mid);
  build(k*2+1,mid+1,r);
  a[k].sum:=max(a[k*2].sum,a[k*2+1].sum);
end;
function query(k,l,r:longint):longint;
begin
  if (a[k].l>r)or(a[k].r<l) then exit(0);
  if (a[k].l>=l)and(a[k].r<=r) then exit(a[k].sum);
  exit(max(query(k*2,l,r),query(k*2+1,l,r)));
end;//线段树的常规操作
begin
  readln(n,m);
  for i:=1 to n do read(b[i]);
  len:=1;
  l[1]:=1;
  c[1]:=1;
  for i:=2 to n do 
    if b[i]<>b[i-1] then 
      begin
        c[i]:=c[i-1]+1;
        r[len]:=i-1;
        tt[len]:=r[len]-l[len]+1;
        inc(len);
        l[len]:=i;
      end
      else c[i]:=c[i-1];//预处理
  r[len]:=n;
  build(1,1,len);//建树
  for i:=1 to m do 
    begin
      readln(x,y);
      if c[y]-c[x]=0 then 
        begin
          writeln(y-x+1);
          continue;
        end;//只有1个区间
      max1:=r[c[x]]-x+1;//头
      max2:=y-l[c[y]]+1;//尾
      if c[y]-c[x]=1 then  
        begin
          writeln(max(max1,max2));
          continue;
        end;//只有2个区间
      ans:=query(1,c[x]+1,c[y]-1);//查询中间区间的最大值
      writeln(max(ans,max(max1,max2)));//输出三者的最大值
    end;
end.

```

---

## 作者：白木偶君 (赞：3)

## 离散化+莫队
**cnt数组表示某个颜色出现的次数**

**sum数组表示某个数量出现的颜色种类**

其它细节问题就按照莫队的模板来的
```cpp
#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cmath>
using namespace std;
const int N=1e7+10;
struct E{
	int l,r,id;
}e[N*2];
int belong[N];
bool cmp(E a,E b){
	return (belong[a.l]^belong[b.l]) ? a.l<b.l : a.r<b.r;
}
int a[N];
int cnt[N],sum[N],op;
inline void add(int x){
	cnt[a[x]]++;
	sum[cnt[a[x]]]++;
	op=max(cnt[a[x]],op);
}
inline void del(int x){
	sum[cnt[a[x]]]--;
	if(sum[cnt[a[x]]]==0)op--;
	cnt[a[x]]--;
}
int ans[N];
int w[N];
int main(){
	int n,q;
	cin>>n>>q;
	int size=sqrt(n*2.0/3.0);
	int num=ceil((double)n/size);
	for(int i=1;i<=num;i++)
	for(int j=(i-1)*size+1;j<=i*size;j++)
	belong[j]=i;
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		w[i]=a[i];
	}
	sort(w+1,w+1+n);
	int len=unique(w+1,w+n+1)-w-1;//去重
	for(int i=1;i<=n;i++)
	a[i]=lower_bound(w+1,w+1+len,a[i])-w;//离散化

	for(int i=1;i<=q;i++){
		scanf("%d%d",&e[i].l,&e[i].r);
		e[i].l=max(1,e[i].l);
		e[i].l=min(n,e[i].l);
		e[i].r=max(1,e[i].r);
		e[i].r=min(n,e[i].r);
		e[i].id=i;
	}
	sort(e+1,e+1+q,cmp);
	int l=e[1].l,r=e[1].r;
	for(int i=l;i<=r;i++)add(i);
	for(int i=1;i<=q;i++){
		while(l<e[i].l)del(l++);
		while(l>e[i].l)add(--l);
		while(r<e[i].r)add(++r);
		while(r>e[i].r)del(r--);
		ans[e[i].id]=op;
	}
	for(int i=1;i<=q;i++){
		printf("%d\n",ans[i]);
	}
}
```


---

## 作者：cjZYZtcl (赞：2)

# 来~~水~~一发线段树的题解
题目让我们求一段区间中最多题目的难度等级的题目数量，那么暴力做法就呼之欲出了：每次遍历查询区间，求出每一段相同难度的题目区间的题目数量，求最大值。

但是暴力显然是拿不了满分的。

我们考虑怎么去优化这个暴力。

由于题目说难度按照升序排列，所以同样难度的题目都是连续的，那么我们可以把相同难度的题目区间看作是一个点，然后在此基础上构建线段树，存储几个连续的难度的题目数量的最大值。

但是查询区间的左右端点不一定是每一段难度区间的边界，所以我们对于左右端点所在的区间去直接计算，而对于被整个包含在查询区间内的难度区间直接线段树维护，最后对三者取最大值即可。

然后还要考虑特殊情况：

- 如果左右端点在同一难度区间内，那么直接计算左右端点之间的长度即可。
- 如果左右端点在相邻的两个难度区间，那么就可以直接省略线段树查询的部分。

时间复杂度 $O(n\ log\ n)$，轻松通过此题。

## AC Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
struct node{
	int l, r;
}b[100005];
int a[100005], c[100005];
int tree[400005];
inline int read(){
	int x = 0, m = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') m = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	return x * m;
}
inline void write(int x){
	if(x < 0){
		putchar('-');
		write(-x);
		return;
	}
	if(x >= 10) write(x / 10);
	putchar(x % 10 + '0');
}
void update(int num){
	tree[num] = max(tree[num * 2], tree[num * 2 + 1]);
}
void build(int l, int r, int num){
	if(l == r){
		tree[num] = b[l].r - b[l].l + 1;
		return;
	}
	int mid = (l + r) / 2;
	build(l, mid, num * 2);
	build(mid + 1, r, num * 2 + 1);
	update(num);
}
int query(int l, int r, int x, int y, int num){
	if(l == x && r == y){
		return tree[num];
	}
	int mid = (l + r) / 2;
	if(x <= mid && y > mid){
		return max(query(l, mid, x, mid, num * 2), query(mid + 1, r, mid + 1, y, num * 2 + 1));
	}
	else if(y <= mid){
		return query(l, mid, x, y, num * 2);
	}
	else{
		return query(mid + 1, r, x, y, num * 2 + 1);
	}
}
signed main(){
	int n = read(), q = read();
	for(int i = 1; i <= n; i++){
		a[i] = read();
	}
	int m = 1;
	b[1].l = 1;
	c[1] = 1;
	for(int i = 2; i <= n; i++){
		if(a[i] != a[i - 1]){
			b[m].r = i - 1;
			b[++m].l = i;
		}
		c[i] = m;
	}
	b[m].r = n;
	build(1, m, 1);
	while(q--){
		int x = read(), y = read();
		int l = c[x], r = c[y];
		int ans = max(b[l].r - x + 1, y - b[r].l + 1);
		if(l == r){
			ans = y - x + 1;
		}
		if(l + 1 < r){
			ans = max(ans, query(1, m, l + 1, r - 1, 1));
		}
		write(ans);
		putchar('\n');
	}
}
```


---

## 作者：pitiless0514 (赞：2)

### 【题意简述】
有一个长度为 $n$ 的序列，每次询问一段区间，询问区间众数的出现次数。

### 【题目分析】

这道题的做法肯定可以很多，因为我是为了水题而来，所以不想写主席树，写了莫队离线做。

离线后前面是莫队的板子。要求记录出现最多次数的数，在往外扩张时这个可以很简单的通过比较计数数组与当前答案谁更大来更新。

问题在于莫队删除的时候去记录这个东西，可以还开一个桶，记录当前区间内出现次数为 $x$ 的数量。那么久判断这个时候这个出现次数为 $x$ 的数量是否为 $1$ ，如果为 $1$ ，那么就需要把记录的答案向下减一。否则就不用减，因为还有其他出现这么多次数的数。

然后就可以解决问题了。

### 【代码】

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5; 
int n,m,a[N],tot;
struct node{
	int l,r,id;
}q[N];
int bnum,siz,pos[N];
int cmp(node x,node y){
	return (pos[x.l]^pos[y.l]) ? pos[x.l]<pos[y.l] : ( (pos[x.l]&1) ? x.r<y.r :x.r>y.r);
}
int now,cnt[N],sum[N];
void add(int x){
	sum[ ++cnt[a[x]] ]++;
	if(now<cnt[a[x]]){now=cnt[a[x]];}
}
void del(int x){
	if(sum[cnt[a[x]]]==1&&now==cnt[a[x]]) now--;
	sum[cnt[a[x]]--]--;
}
int ans[N];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=m;i++){
		int l,r;
		cin>>l>>r;
		q[++tot].l=l;
		q[tot].r=r;
		q[tot].id=i;
	}
	siz=pow(n,2.0/3.0);
	bnum=ceil((double)n/siz);
	for(int i=1;i<=bnum;i++){
		for(int j=(i-1)*siz+1;j<=i*siz;j++){
			pos[j]=i;
		}
	}
	sort(q+1,q+m+1,cmp);
	int l=1,r=0;
	for(int i=1;i<=m;i++){
		int ql=q[i].l,qr=q[i].r;
		while(l<ql) del(l++);
		while(l>ql) add(--l);
		while(r<qr) add(++r);
		while(r>qr) del(r--);
		ans[q[i].id]=now;
	}
	for(int i=1;i<=m;i++){
		cout<<ans[i]<<"\n";
	}
	return 0;
} 
```


---

## 作者：一只书虫仔 (赞：2)

#### Description

> 给定一个长为 $n$ 的上升序列 $a_i$，并给定 $q$ 次询问，每次询问给出 $i,j$，询问区间 $[i,j]$ 的众数。

#### Solution

因为是上升序列，可以转化为求上升序列区间 $[i,j]$ 的连续出现次数最多的数是什么。

一说到区间和出现次数，不难想到 RMQ 问题，这里我们用 ST 表进行解决。

假设 $st_{[l,r]}$ 为对 $[l,r]$ 用 ST 表跑区间最大值的结果。

首先我们想如果询问的区间是全局的（$i=1$，$j=n$）该怎么做，不难得知，可以采用一个递归的思路，建立一个 $f_i$ 数组：

- 如果 $a_i=a_{i-1}$，$f_i=f_{i-1}+1$。
- 如果 $a_i \ne a_{i-1}$，$f_i=1$。

这样，$f_i$ 就是连续的均为 $a_i$ 的一段 $a_i$ 是这一段的第几个数。

对这个 $f_i$ 跑一遍 ST 表，就是最终答案 $st_{[1,n]}$。

那么如果 $[i,j]$ 是个普通的区间，又该怎么分析呢？

不难发现，对于一个普通的区间，很有可能 $f_i \ne 1$，导致跑出来的结果会有偏差。

所以，我们可以假设 $k$ 是离 $i$ 最近的能使得 $f_k=1$ 的数，那么，答案也就拆分为了 $[i,k-1]$ 和 $[k,j]$，前一部分的答案是 $f_{k-1}-f_i+1$，后一部分的答案即 $st_{[k,j]}$。

取一个最大值即可。

问题来到了我们如何求这个 $k$，这里介绍三种方法：

1. 暴力从 $i$ 开始枚举。啥都好，就是有点慢。另外注意边界情况。笔者写这种方法时考虑了两种边界：$f_i=f_j$，$f_i=1$，但仍然是 WA，所以笔者决定换到第 3 种方你发。
2. 将暴力枚举换成二分，笔者二分能力极差，因此并没有写，并且二分写法细节有亿丶多。
3. 建立一个数组 $rs_i$，定义为一块均为 $a_i$ 数值的右界，比如举个栗子：

- $a_i=\{1,1,1,3,4,4,4,4,4,4,5,5\}$
- $rs_i=\{3,3,3,4,10,10,10,10,10,10,12,12\}$

那么不难发现，对于区间 $[i,j]$，$rs_i$ 即为我们需要寻找的 $k$，因此答案即为 $\max\{rs_i-i+1,st_{[rs_i+1,j]}\}$。

注意，这里也有边界情况，就是 $rs_i\ge j$ 的时候，即这个区间里的所有数相等的时候，输出 $j-i+1$ 即可。

算一下第三种方法的复杂度，不难发现预处理 $rs$ 和 $f$ 都是 $\mathcal O(n)$ 的，加上预处理 ST 表的 $\mathcal O(n\log n)$，查询 $\mathcal O(q)$，我们仍然可以轻松通过此题。

---

## 作者：Heartlessly (赞：2)

## Description
给定一个区间 $[l,r]$，求区间众数出现的次数。
## Solution
这道题的解法好像有很多，比如RMQ，线段树，分块等等都可以，这里给出一种**莫队**(离线)的方法。我们用 $cnt[i]$ 表示当前区间内 $i$ 出现的次数，$num[i]$ 表示当前区间内出现次数为 $i$ 的数字有几个。**注意：**序列中可能存在负数，使用前可以先离散化，或者给每个数加上一个很大的数($10^5$)，防止 $cnt$ 数组下标变成负数。$add$ 操作和 $del$ 操作时，修改 $num$ 和 $cnt$ 数组的值，如果满足要求，则改变答案，很好理解，具体实现见代码。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

template < class T > inline void read(T &x) {
    x = 0;
    char c = getchar();
    bool f = 0;
    for (; !isdigit(c); c = getchar()) f ^= c == '-';
    for (; isdigit(c); c = getchar()) x = (x << 3) + (x << 1) + (c ^ 48);
    x = f ? -x : x;
}

const int maxN = 5e5 + 1;

int n, m, l = 1, r, res, size, len, a[maxN], b[maxN], num[maxN], ans[maxN], cnt[maxN];

struct node {
    int l, r, id;
} q[maxN];

inline bool cmp(node a, node b) { return (a.l / size) ^ (b.l / size) ? a.l < b.l : (((a.l / size) & 1) ? a.r < b.r : a.r > b.r); }//奇偶性排序

inline void add(int x) { num[cnt[a[x]]]--, num[++cnt[a[x]]]++; if (cnt[a[x]] > res) res = cnt[a[x]]; }

inline void del(int x) { num[cnt[a[x]]]--, num[--cnt[a[x]]]++; if (cnt[a[x]] == res - 1 && !num[cnt[a[x]] + 1]) res--; }

int main() {
    read(n), read(m), size = n / sqrt(m * 2 / 3);//size为块的大小
    for (int i = 1; i <= n; i++) read(a[i]), b[i] = a[i];
    sort(b + 1, b + n + 1), len = unique(b + 1, b + n + 1) - b - 1;//排序+去重
    for (int i = 1; i <= n; i++) a[i] = lower_bound(b + 1, b + len + 1, a[i]) - b;//离散化
    for (int i = 1; i <= m; i++) read(q[i].l), read(q[i].r), q[i].id = i;
    sort(q + 1, q + m + 1, cmp);
    for (int i = 1; i <= m; i++) {
        while (l < q[i].l) del(l++);
        while (l > q[i].l) add(--l);
        while (r < q[i].r) add(++r);
        while (r > q[i].r) del(r--);
        ans[q[i].id] = res;//莫队板子
    }
    for (int i = 1; i <= m; i++) printf("%d\n", ans[i]);
    return 0;
}
```

---

## 作者：sunyt (赞：2)

##二分查找+RMQ（ST表实现）

题目简化后如下：给定一个升序数列和多次询问，求询问区间内的众数出现的次数。

看到这个题，我的第一想法就是序列的元素是多少不重要，重要的是每种元素的个数，所以我们就记录左右端点和它的长度，长度另开一个数组来存，然后我们对询问的区间内哪个数出现次数最多进行运算。

自然的，我们想求出左右端点的数字a[l],a[r]是第几种数字，所以我们考虑二分。

而它们又并不一定在这个区间内全部出现，所以我们将二分出的种类序号对应的左（右）端点求出来，作一个差，把a[l]和a[r]在区间内出现的次数求出来，求一个最大值。

接下来我们就是把区间内全组完整存在的数出现的次数的最大值求出来，这里我们就可以用RMQ来logn查询区间最大值，然后在更新刚才的最大值即可，这里我的RMQ用了ST表来实现，当然也能用线段树。

举个例子吧：

如样例所示

9 1
1 1 1 3 3 5 5 7 7

3 8
令p=3,q=8

由于1出现3次，3出现2次，5出现2次，7出现2次，所以个数数组为：3 2 2 2，然后我们先初始化掉RMQ的ST表。

```cpp
a[1].left=1,a[1].right=3
a[2].left=4,a[2].right=5
a[3].left=6,a[3].right=7
a[4].left=8,a[4].right=9
```
我们求区间【3,8】，所以首先二分求出位置3所在的组数，即为第1组，同理位置8在第4组。
然后第1组在区间内有a[1].right-p+1=1个数；

然后第4组在区间内有a[4].left-q+1=1个数；

然后我们只需要求[p+1,q-1]组之间的出现次数的最大值，用ST表做一个RMQ问题就好了。

值得注意的一点就是，如果询问区间是某一组所在区间的真子集，比如本例中询问[1,2]，那么我们更新就应该更新a[1].right-a[1].left+1，而不是a[1].right-p+1与a[4].left-q+1。这一点一定注意，如果没有的话是51分（第一次没有AC就是这样的）。

时间复杂度上表现不是很好：最差情况下是O（M\*3logN）。

推介一波博客[Stockholm\_Sun萌萌的博客](http://blog.csdn.net/Stockholm\_Sun)

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
int i,j,m,n,t,temp;
int a[100001];
int map[100001][20];
struct data
{
    int ll,rr;
}b[100001];

int r()//读入优化
{
    int ans=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')
        f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        ans*=10;
        ans+=ch-'0';
        ch=getchar();
    }
    return ans*f;
}

int erfen1(int x)//两个二分
{
    int mid,le=1,ri=temp,ans;
    while(le<=ri)
    {
        mid=le+ri;
        mid>>=1;
        if(b[mid].ll<x) ans=mid,le=mid+1;
        else if(b[mid].ll>x) ri=mid-1;
        else return mid;
    }
    return ans;
}

int erfen2(int x)
{
    int mid,le=1,ri=temp,ans;
    while(le<=ri)
    {
        mid=le+ri;
        mid>>=1;
        if(b[mid].rr<x) le=mid+1;
        else if(b[mid].rr>x) ans=mid,ri=mid-1;
        else return mid;
    }
    return ans;
}

void work()//ST表的构建
{
    int i,j;
    for(j=1;1<<j<=n;j++)
    for(i=1;i+(1<<j)-1<=n;i++)
    map[i][j]=max(map[i][j-1],map[i+(1<<j-1)][j-1]);
}

int question(int z,int y)//区间查询最大值
{
    int x=(int)(log(y-z+1)/log(2));
    return max(map[z][x],map[y-(1<<x)+1][x]);
}

int main()
{
    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    n=r(),m=r();
    b[++temp].ll=1;
    a[1]=r();
    for(i=2;i<=n;i++)
    {
        a[i]=r();
        if(a[i]!=a[i-1])
        {
            b[temp].rr=i-1;
            b[++temp].ll=i;
        }
    }
    b[temp].rr=n;
    
    for(i=1;i<=temp;i++)
    {
        map[i][0]=b[i].rr-b[i].ll+1;//初始化ST表
    }
    work();
    int p,q,maxx=0;
    for(i=1;i<=m;i++)
    {
        maxx=0;
        p=r(),q=r();
        int st=erfen1(p);//这两种二分一定要区分开
        int en=erfen2(q);
        maxx=max(maxx,min(b[st].rr-p+1,q-p+1));//特殊情况判断
        maxx=max(maxx,min(q-b[en].ll+1,q-p+1));
        if(st+1<=en-1)
        maxx=max(maxx,question(st+1,en-1));
        cout<<maxx<<endl;
    }
    return 0;
}
/*

*/
```

---

## 作者：dyf_DYF (赞：1)

### Section1 题意

给你一个长度为 n 的数列，询问 m 次从 l 到 r 的区间众数出现次数。

### Section2 做法

区间问题，考虑莫队。很容易发现向区间内加入一个数很简单，但是删除一个数复杂度无法保证（因为要重新找到最大值），对于这样的添加容易，删除较难的题目我们可以选择另一种优雅的暴力算法——**回滚莫队**（当然这题还有很多其他做法）。

回滚莫队，又名不删除莫队，顾名思义，就是不进行删除操作的莫队。

具体的，我们可以先对询问按左端点分块，在块内再按右端点排序，这样就可以保证每一块右端点不下降，而对于左端点，我们可以在每次处理时强行从左端点所在的块的末尾一个一个处理到左端点即可（这里我个人习惯单独开辟出一个用来处理左边这部分的数组），在处理结束后再清空。

每次处理左端点到块末尾时，最多有 $\sqrt{n}$ 次处理，所以总时间复杂度是 $O(m \times \sqrt n)$ 量级的。

如果不太理解可以看下图和代码：

![0](https://cdn.luogu.com.cn/upload/image_hosting/ft2rvf2p.png)

（第一次询问为 1，6，第二次询问为 2，8。）

模板题[P5906 【模板】回滚莫队&不删除莫队](https://www.luogu.com.cn/problem/P5906)

坑点：

1. 如果每次都 memset 清空数组，时间会偏慢，这里我采用了一个栈记录被更改过的值的位置。

2. $a_i$ 可小于 0，注意离散化。

### Section3 代码

```cpp
#include<cmath>
#include<cstdio>
#include<cctype>
#include<algorithm>
#define ll long long
using namespace std;
const int maxn=200010;
//已做防ctj处理。
int in(){
	int val=0,sig=1;char c=getchar();
	while(!isdigit(c)&&c!='-')c=getchar();
	if(c=='-')sig=-1,c=getchar();
	while( isdigit(c))val=((val<<1)+(val<<3)+(c^48)),c=getchar();
	return val*sig;
}
struct que{int l,r,id;}q[maxn];int spn[maxn];
bool cmp(const que x,const que y){return (spn[x.l]^spn[y.l])?(spn[x.l]<spn[y.l]):(x.r<y.r);}
int c[maxn],n,m;
struct dIScReTiZatIoN{
	int res[maxn],tmp[maxn],cdx;
	int lOweR_BoUnd(int x,int len){
		int pos=0;
		for(int dx=cdx;dx;dx>>=1){
			int nxd=pos|dx;
			if(nxd>len)continue;
			if(res[nxd]<x)pos=nxd;
			if(res[nxd]==x)return nxd;
		}
		return -1;
	}
	void discretization_main(int *c,int n){
		int cnt=0;
		for(int i=1;i<=n;i++)tmp[i]=c[i];
		sort(tmp+1,tmp+1+n);
		res[0]=-200001;
		for(int i=1;i<=n;i++)if(res[cnt]!=tmp[i])res[++cnt]=tmp[i];
		cdx=1<<(int)floor(log(cnt)/log(2));
		for(int i=1;i<=n;i++)c[i]=lOweR_BoUnd(c[i],cnt);
		return;
	}
}Src;
//离散化处理。
struct stk{
	int isin[maxn],clr[maxn],tot;
	void push(int x){
		if(isin[x])return;
		clr[++tot]=x;
		isin[x]=1;
		return ;
	}
	int top(){
		return clr[tot];
	}
	int size(){return tot;}
	bool empty(){return tot==0;}
	void pop(){
		if(!tot)return;
		isin[clr[tot]]=0;
		clr[tot]=0;
		tot--;
	}
}s,ls;
//记录被更改过的值的位置。
int tim[maxn],ltim[maxn];
int lans,ans,ANS[maxn];
void chg(int cul){
	tim[cul]++;
	ans=max(ans,tim[cul]);
}
//处理右指针右移。
void lchg(int cul){
	if(ltim[cul]==0&&tim[cul]!=0)ltim[cul]=tim[cul];
	ltim[cul]++;
	lans=max(lans,ltim[cul]);
}
//处理左指针左移。
int bfc[maxn];
int bf(int l,int r){
	int ansx=0;
	for(int k=l;k<=r;k++){
		int cul=c[k];
		bfc[cul]++;
		ansx=max(ansx,bfc[cul]);
	}
	for(int k=l;k<=r;k++)bfc[c[k]]=0;
	return ansx;
}
int main(){
	n=in(),m=in();
	int blc=ceil(sqrt(n));
	for(int i=1;i<=n;i++)c[i]=in(),spn[i]=(i-1)/blc+1;
	for(int i=1;i<=m;i++)q[i].l=in(),q[i].r=in(),q[i].id=i;
	Src.discretization_main(c,n);//离散化处理。
	sort(q+1,q+1+m,cmp);
	for(int i=1,j=1;j<=spn[n]&&i<=m;j++){//i枚举询问，j枚举左端点所在的块。
		int rg=min(blc*j,n),l=rg+1,r=rg;//rg为左端点所在的块的右边界，每次左指针从这里开始处理。
		ans=0;
		for(;spn[q[i].l]==j&&i<=m;i++){
			if(spn[q[i].r]==j){//在同一个块内，直接暴力做。
				ANS[q[i].id]=bf(q[i].l,q[i].r);
				continue;
			}
			while(r<q[i].r){//右指针右移。
				r++;
				s.push(c[r]);
				chg(c[r]);
			}
			lans=ans;
			while(l>q[i].l){//左指针左移。
				l--;
				ls.push(c[l]);
				lchg(c[l]);
			}
			ANS[q[i].id]=lans;//记录答案。
			while(!ls.empty()){//去除从l到rg的贡献。
				ltim[ls.top()]=0;
				ls.pop();
			}
			l=rg+1;//左指针复位。
		}
		while(!s.empty()){//去除右指针的贡献。
			tim[s.top()]=0;
			s.pop();
		}
	}
	print(ANS,m);
	return 0;
}
```

---

## 作者：moosssi (赞：1)

普通莫队+离散化

本题求的是询问的区间内的众数出现的次数，可以直接套莫队板子，主要考虑如何统计答案。

定义两个数组$num[i]$表示$i$出现的次数,$cnt[i]$表示有多少数出现$i$次，答案可以在每次$add$时,直接与前者取最大值，后者主要是在$del$时改变答案,具体见代码。

最后记得加上离散化。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int a[N],dt[N],ans[N],d[N];
int n,m,len,res,cnt[N],num[N];
struct nod{
	int id,l,r;
}q[N];
bool cmp(nod x,nod y){
	int i=dt[x.l],j=dt[y.l];
	if(i!=j)return i<j;
	if(dt[x.l]%2==1)return x.r<y.r;
	return x.r>y.r;
}
void add(int x){
	num[x]++;
	cnt[num[x]]++;
	res=max(res,num[x]);//直接更新最大值 
}
void del(int x){
	if(res==num[x]&&cnt[num[x]]==1)res--;//如果答案是由当前值转移过来并且出现num[x]次的数只有一个的，则答案更新 
	cnt[num[x]]--;
	num[x]--;
}
int main(){
	scanf("%d%d",&n,&m);
	len=sqrt((long long)n*n/m);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		d[i]=a[i];
		dt[i]=(i-1)/len+1;
	}
	sort(d+1,d+n+1);
	int le=unique(d+1,d+n+1)-d-1;
	for(int i=1;i<=n;i++)
		a[i]=lower_bound(d+1,d+le+1,a[i])-d;//离散化 
	for(int i=1;i<=m;i++){
		scanf("%d%d",&q[i].l,&q[i].r);
		q[i].id=i;
	}
	sort(q+1,q+m+1,cmp);
	int l=1,r=0;
	for(int i=1;i<=m;i++){ //莫队模板 
		while(l>q[i].l)add(a[--l]);
		while(l<q[i].l)del(a[l++]);
		while(r>q[i].r)del(a[r--]);
		while(r<q[i].r)add(a[++r]);
		ans[q[i].id]=res;
	}
	for(int i=1;i<=m;i++){
		printf("%d\n",ans[i]);
	}
	return 0;
} 
```


---

## 作者：Others (赞：0)

双倍经验题:[P3709 大爷的字符串题](https://www.luogu.com.cn/problem/P3709)。
# 分析
这题有区间，有统计，有离线，一看就是莫对。

那这题要求的是众数出现的次数，首先，我们需要统计每个数出现的次数，这样可以显而易见的找到众数出现的次数，然后就是删除了，这里我们要很好的维护最大的出现次数，那么如果当前最大的那个数少了一个，只存在两种情况：
1. 还有一个众数，答案不变
2. 只有这一个众数，答案减一

这里可以给我们一个简单的思路，记录一下出现的这个次数的数字个数，然后在删除时处理两个数组，在加一行 $if$，就完美的 solve 了这个问题。

因为 $a_i$ 可以是负数，记得离散化 qwq。
```cpp
#include <bits/stdc++.h>
using namespace std;
struct node{
	int l,r,id;
}p[200005];
int n,m,s,l=1,r,L,R,tot,a[200005],flag[200005],cnt[200005],ccnt[200005],ans[200005],idx[200005];
bool cmp(node x,node y){
	return idx[x.l]==idx[y.l]?(idx[x.l]&1?x.r<y.r:x.r>y.r):x.l<y.l;//养成习惯，奇偶排序 
}
void add(int i){
	--ccnt[cnt[a[i]]];  //统计数出现的次数出现的次数
	++ccnt[++cnt[a[i]]];//看不懂中文可以参考代码理解
	tot=max(tot,cnt[a[i]]);
}
void del(int i){
	--ccnt[cnt[a[i]]];
	if(tot==cnt[a[i]]&&ccnt[cnt[a[i]]]==0) --tot;//这里如果删掉的是众数而且是唯一的，那么将答案减一 
	++ccnt[--cnt[a[i]]]; 
}
int main() {
	scanf("%d%d",&n,&m);
	s=sqrt(n);
	for(int i=1;i<=n;++i){
		scanf("%d",&a[i]);
		idx[i]=(i+s-1)/s;//分块 
		flag[i]=a[i];//离散化1：记录 
	}
	sort(flag+1,flag+n+1);//离散化2：排序 
	int lenlen=unique(flag+1,flag+n+1)-flag-1;//离散化3：去重 
	for(int i=1;i<=n;++i) a[i]=lower_bound(flag+1,flag+lenlen+1,a[i])-flag;//离散化4：赋值
	for(int i=1;i<=m;++i){
		scanf("%d%d",&p[i].l,&p[i].r);
		p[i].id=i;
	}
	sort(p+1,p+m+1,cmp);
	for(int i=1;i<=m;++i){
		L=p[i].l,R=p[i].r;
		while(l>L) add(--l);
		while(r<R) add(++r);
		while(l<L) del(l++);
		while(r>R) del(r--);
		ans[p[i].id]=tot;
	}
	for(int i=1;i<=m;++i) printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：Strelitzia (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P1997)

---

题目要求你求区间的众数，很明显可以用莫队。

维护一个 $\operatorname {cnt}$ 来记录出现的次数，$\operatorname {sum}$ 来维护（出现次数）出现的次数。

注意 $a_i$ 有负数，可以统一加上一个值。

```cpp
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

template<typename T>void read(T &x) {
    T f = 1;x = 0;char s = getchar();
    while(s < '0' || s > '9') {if(s == '-')f = -1;s = getchar();}
    while(s >= '0' && s <= '9') {x = x * 10 + s - '0';s = getchar();}
    x *= f;
}
template<typename T>void print(T x) {
    if(x < 0) putchar('-'),x = -x;
    if(x > 9) print(x / 10);
    putchar(x % 10 + '0');
}

const int maxn = 200005;

int n,m,res,a[maxn],b[maxn],pos[maxn],cnt[maxn],ans[maxn],sum[maxn];

struct node {
	int l,r,id;
	bool operator <(node y) const {
		return pos[this->l] ^ pos[y.l] ? this->l < y.l : (pos[this->l] & 1 ? this->r < y.r : this->r > y.r);
	}
}ask[maxn];

bool cmp(int x,int y) {
	return a[x] < a[y];
}

void Add(int x) {
	sum[cnt[x]] --;
	sum[++ cnt[x]] ++;
	res = max(cnt[x],res);
}

void Sub(int x) {
	if (cnt[x] == res && sum[cnt[x]] == 1) res --;
	sum[cnt[x]] --;
	sum[-- cnt[x]] ++;
}

int main () {
	read(n);read(m);
	int t = sqrt(n);
	for (int i = 1 ; i <= n ; ++ i) {
		read(a[i]);pos[i] = i / t;
		a[i] += 1e5;
	}
	for (int i = 1 ; i <= m ; ++ i) {
		read(ask[i].l);read(ask[i].r);
		ask[i].id = i;
	}
	sort(ask + 1,ask + 1 + m);
	int l = 1,r = 0;
	for (int i = 1 ; i <= m ; ++ i) {
		while (l > ask[i].l) Add(a[-- l]);
		while (r < ask[i].r) Add(a[++ r]);
		while (l < ask[i].l) Sub(a[l ++]);
		while (r > ask[i].r) Sub(a[r --]);
		ans[ask[i].id] = res;
	}
	for (int i = 1 ; i <= m ; ++ i) print(ans[i]),putchar('\n');
	return 0;
}
```

---

## 作者：Wall_breaker (赞：0)

### 算法什么的前面的大佬都讲的差不多了，我就来讲讲本题莫队算法的易错点，写莫队过不去的小伙伴可以看看。

核心算法：维护两个数组，sum[x]表示值为x的数出现了几次。cnt[x]表示出现次数为x的数有几种。然后用莫队去暴力维护，上一次的答案与当前最大cnt比较更新。

下面是我跳了5次的坑：

#### 一、你注意到ai可以是负数了吗？

ai可以是负数，所以我们需要离散化或者整体右移，反正不能让数组下标是负数。

#### 二、你在维护的时候有没有考虑怎么记cnt？（肯定有人用堆）

实际上，sum[x]每次只会减少或增加1，所以如果当前数减少后，原来的cnt[sum[x]]为0，说明答案要改变，变成减一；数增加后，直接比较取较大值就行了。

#### 三（超级重要）你的莫队比较函数有没有写成这样子？

```c++
inline bool comp(info x, info y) {
	if (bel[x.l] ^ bel[y.l]) return bel[x.l] < bel[y.l];
	return (x.r < y.r) == (bel[x.l] & 1);
}
```
那么恭喜你，你之前所有写的程序都是错的（大雾）。

**comp的正确打开方式：**
```c++
inline bool comp(info x, info y) {
	if (bel[x.l] ^ bel[y.l]) return bel[x.l] < bel[y.l];
	if (bel[x.l] & 1) return x.l < y.l;
	else return x.l > y.l;
}
```

为什么?很简单，~~你家的sort能取等号吗（超大雾）~~ 万一出现等于号，即x.l==y.l && x.r == y.r，你模拟一下sort试试，然后你发现无论把x放在y前面还是y放在x前面都是对的，然后你就RE了（居然不是TLE，我吐了）。一下子，你开始慌了：我之前的莫队题目是怎么过的？

上代码：
```c++
#include<bits/stdc++.h>
using namespace std;
template <typename T>
inline void readin(T &x) {
	x = 0;
	T fh = 1;
	char ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') fh = -1;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
	x *= fh;
}
inline void d_read(double &x) {
	x = 0.0;
	int fh = 1;
	char ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') fh = -1;
	for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch ^ 48);
	if (ch == '.') {
		double num = 1.0;
		ch = getchar();
		for (; isdigit(ch); ch = getchar()) x = x + (num /= 10) * (ch ^ 48);
	}
	x *= fh;
}

template <typename T>
inline void wt(T x) {
	if (x > 9) wt(x / 10);
	putchar(x % 10 + 48);
}
template <typename T>
inline void writeln(T x, char c) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	wt(x);
	putchar(c);
}
int res, sum[200005], a[200005], ans[200005], bel[200005], cnt[200005], len;
struct info{
	int l, r, pos;
}q[200005];
inline bool comp(info x, info y) {
	if (bel[x.l] ^ bel[y.l]) return bel[x.l] < bel[y.l];
	if (bel[x.l] & 1) return x.l < y.l;
	else return x.l > y.l;
}
inline void add(int x) {
	cnt[sum[x]] --;
	sum[x] ++;
	cnt[sum[x]] ++;
	res = max(res, sum[x]);
}
inline void del(int x) {
	cnt[sum[x]] --;
	if (res == sum[x] && cnt[sum[x]] == 0) res --;
	sum[x] --;
	cnt[sum[x]] ++;
} 
int main() {
	int n, Q;
	readin(n); readin(Q);
 	for (int i = 1; i <= n; i ++) {
	 	readin(a[i]);
	 	a[i] += 1e5 + 1;
	}
	for (int i = 1; i <= Q; i ++) {
	 	readin(q[i].l);
	 	readin(q[i].r);
	 	q[i].pos = i;
	}
	len = (int)sqrt(n);
	for (int i = 1; i <= n; i ++) {
		bel[i] = (i - 1) / len + 1;
	}
	sort(q + 1, q + Q + 1, comp);
	int li = 1, ri = 0;
	for (int i = 1; i <= Q; i ++) {
		while (ri < q[i].r) {
			ri ++;
			add(a[ri]);
		}
		while (ri > q[i].r) {
			del(a[ri]);
			ri --;
		}
		while(li < q[i].l) {
			del(a[li]);
			li ++;
		}
		while(li > q[i].l) {
			li --;
			add(a[li]);
		}
		ans[q[i].pos] = res;
	}
	for (int i = 1; i <= Q; i ++) {
		writeln(ans[i], '\n');
	}
	return 0;
}
```

---

## 作者：嘉年华 (赞：0)

分块之后直接可以过掉这道题（因为数据水）。看到没有人写分块的题解我就来写一个。因为这里的a序列是升序的，所以众数一定是在一段连续的区间中，我们可以先把每一个连续的数列合并了，代码如下
```cpp
class line
{
	public:
		int start,end;
}l[maxn];

inline void first(void)
{
	int la=a[1];
	int cnt=1;//个数
	l[cnt].start=1;
	l[cnt].end=0;
	for(int i=1;i<=n;i++)
   {
     if(a[i]==la) l[cnt].end++;
     else l[++cnt].start=i,l[cnt].end=i,la=a[i];
   }
}
```
每个line就表示了某个值在a中占的为止，这样会比直接暴力搜边界要快一些。
然后，我们按line分块就可以了，查询的时候因为是升序的所以可以二分。相信大家都会分块（蒟蒻必备骗分神器），我就不放代码了。
复杂度O（q×n×sqrt(n)）,但常数比一般的分块小一点点。

---

## 作者：BeyondHeaven (赞：0)

题意：

给定静态序列$a$，每次查询区间$[l,r]$众数的出现次数。

$n\leq 1e5,q\leq 2e5$



RMQ。并不需要二分。

将原序列中极大的一段连续相同的数记为一组，对每组数记$3$个值$L,R,len$，表示这组数在原序列的位置为$[L,R]$，$len=R-L+1$。对原序列中每个位置记一个值$bel$，表示这个位置在哪一组中。

对于一个询问$[l,r]$，分两种情况讨论

1.若$bel[l]=bel[r]$，表明$[l,r]$中是同一个数，答案为$r-l+1$。

2.若$bel[l]\neq bel[r]$，则答案为$max(max(R[bel[l]-l+1],r-L[bel[r]+1]),RMQ_{len}(bel[l]+1,bel[r]-1))$

对每一组数的$len$建立$ST$表，用以快速查询$RMQ$。

复杂度$O(nlogn+q)$。

代码：

其中$cnt$为组的数量，其余变量如上。

注意$RMQ$时区间不能为空，需要特判。

```cpp
#include<cstdio>
#define MaxN 100123
#define LogN 18
template<typename T>
inline void read(T&x)
{
	x=0;int ch=getchar(),f=1;
	while(ch<48||ch>57){if(ch==45)f=0;ch=getchar();}
	while(ch>47&&ch<58)x=10*x+ch-48,ch=getchar();
	if(!f)x=-x;
}
template<typename T>inline T max(const T&a,const T&b){return a>b?a:b;}
int n,q;
int a[MaxN];
int L[MaxN],R[MaxN],bel[MaxN],len[MaxN],cnt;
int Log2[MaxN],ST[MaxN][LogN];
inline void Init()
{
	read(n);read(q);
	for(int i=1;i<=n;++i)
	read(a[i]);
	L[cnt=1]=bel[1]=1;
	for(int i=2;i<=n;++i)
	if(a[i]==a[i-1])
	bel[i]=cnt;
	else
	{
		R[cnt]=i-1;
		len[cnt]=R[cnt]-L[cnt]+1;
		L[++cnt]=i;
		bel[i]=cnt;
	}
	R[cnt]=n;len[cnt]=R[cnt]-L[cnt]+1;
	Log2[0]=-1;
	for(int i=1;i<=n;++i)
	Log2[i]=Log2[i>>1]+1;
}
inline void Build()
{
	for(int i=1;i<=cnt;++i)
	ST[i][0]=len[i];
	for(int j=1;j<=Log2[n];++j)
	for(int i=1;i+(1<<j)-1<=cnt;++i)
	ST[i][j]=max(ST[i][j-1],ST[i+(1<<j-1)][j-1]);
}
inline int RMQ(int l,int r)
{
	int s=Log2[r-l+1];
	return max(ST[l][s],ST[r-(1<<s)+1][s]);
}
inline void Solve()
{
	for(int i=1,l,r;i<=q;++i)
	{
		read(l);read(r);
		if(bel[l]==bel[r])
		printf("%d\n",r-l+1);
		else if(bel[l]+1==bel[r])
		printf("%d\n",max(R[bel[l]]-l+1,r-L[bel[r]]+1));
		else
		printf("%d\n",max(max(R[bel[l]]-l+1,r-L[bel[r]]+1),RMQ(bel[l]+1,bel[r]-1)));
	}
}
int main()
{
	Init();
	Build();
	Solve();
	return 0;
}
```



---

## 作者：Treaker (赞：0)

$$\color{CornflowerBlue}{\mathcal{Treaker}}$$
# 莫队 + 桶
还是莫队那个套路，加加减减，这个题注意一下细节。

有负下标，我们可以整体加上一个数。

记录每一个数出现的次数和有多少个这样的次数的数。

加一个数时，如果这个数出现次数比ans多，就替换。

减一个数时，如果这个数是这个次数的最后一个数了，就替换。

完整代码如下：
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;
inline int read()
{
	int x = 0 , f = 1;	char ch = getchar();
	while(ch < '0' || ch > '9')	{if(ch == '-')	f = -1; ch = getchar();}
	while(ch >= '0' && ch <= '9') {x = (x << 3) + (x << 1) + (ch ^ 48); ch = getchar();}
	return x * f;
}
const int N = 100010;
int n , Q , len , ans;
int cnt[N << 1] , num[N] , as[N] , pos[N] , a[N];
struct node
{
	int l , r , id;
	friend bool operator < (const node & a,const node & b) {return pos[a.l] == pos[b.l] ? a.r < b.r : pos[a.l] < pos[b.l];}
}e[N << 1];
inline void del(int x)
{
	num[cnt[x]] --;	num[--cnt[x]] ++;
	if(ans == cnt[x] + 1 && !num[cnt[x] + 1])	ans = cnt[x];
}
inline void add(int x)
{
	num[cnt[x]] --; num[++cnt[x]] ++;
	if(ans < cnt[x])	ans = cnt[x];
}
int main()
{
	n = read(); Q = read();
	len = sqrt(n);
	for(int i = 1;i <= n;i ++)	a[i] = read() + N , pos[i] = (i - 1) / len + 1;
	for(int i = 1;i <= Q;i ++)	e[i] = (node){read(),read(),i};
	sort(e+1,e+1+Q);
	int l = 1 , r = 0;
	for(int i = 1;i <= Q;i ++)
	{
		while(l < e[i].l) del(a[l++]);
		while(l > e[i].l) add(a[--l]);
		while(r > e[i].r) del(a[r--]);
		while(r < e[i].r) add(a[++r]);
		as[e[i].id] = ans;
	}
	for(int i = 1;i <= Q;i ++)	printf("%d\n",as[i]);
	return 0;
}
```


---

## 作者：Forever_Lin (赞：0)

    这道题简直有毒。。。只是个简单的RMQ，弄了我一个下午加一个晚上。检查了半天，最主要的错误就是数组开小了，越界，他提示的竟然是wa了。还有第三个点我觉得要凭运气才能过（~~考验人品的时候到了~~）
    最主要的是输出的时候要分四种情况
    1 1 1 1 2 2 2 3 3 4 4 4 
    (1)l=1,r=7
    (2)l=2,r=7
    (3)l=5,r=9
    (4)l=3,r=8
    要注意a[l]==a[r]的情况，我就在上面被坑了好长时间

---

## 作者：xayata_ (赞：0)

线段树区间最长连续子段和模板题
线段树记录：
区间左，右端点颜色
区间从左右端点起最长连续的长度
合并时注意从区间左右端点起最长连续长度的合并
```
#include <bits/stdc++.h>

const int N = 1e5 + 10;

int data[N], Maxn[N << 2], Lcol[N << 2], Rcol[N << 2], Ljs[N << 2], Rjs[N << 2];
int S[N << 2];

#define lson jd << 1
#define rson jd << 1 | 1

void Updata(int jd) {
	Maxn[jd] = std:: max(Maxn[lson], Maxn[rson]);
	if(Rcol[lson] == Lcol[rson]) Maxn[jd] = std:: max(Maxn[jd], Rjs[lson] + Ljs[rson]);
	Lcol[jd] = Lcol[lson], Rcol[jd] = Rcol[rson];
	Ljs[jd] = Ljs[lson], Rjs[jd] = Rjs[rson];
	if(S[lson] == Ljs[lson] && Lcol[rson] == Rcol[lson]) Ljs[jd] += Ljs[rson];
	if(S[rson] == Rjs[rson] && Lcol[rson] == Rcol[lson]) Rjs[jd] += Rjs[lson];
}

void Build_tree(int l, int r, int jd) {
	S[jd] = (r - l + 1);
	if(l == r) {
		Maxn[jd] = Ljs[jd] = Rjs[jd] = 1; Lcol[jd] = Rcol[jd] = data[l];
		return ;
	}
	int mid = (l + r) >> 1;
	Build_tree(l, mid, lson);
	Build_tree(mid + 1, r, rson);
	Updata(jd);
}

int Sec_A(int l, int r, int jd, int x, int y) {
	if(x <= l && r <= y) return Maxn[jd];
	int mid = (l + r) >> 1;
	if(y <= mid) return Sec_A(l, mid, lson, x, y);
	else if(x > mid) return Sec_A(mid + 1, r, rson, x, y);
	else {
		int ret = std:: max(Sec_A(l, mid, lson, x, y), Sec_A(mid + 1, r, rson, x, y));
		int other = 0;
		if(Rcol[lson] == Lcol[rson]) {
			other += std:: min(Rjs[lson], mid - x + 1);
			other += std:: min(Ljs[rson], y - mid);
			ret = std:: max(ret, other);
		}
		return ret;
	}
}

int main() {
	int n, q;
	std:: cin >> n >> q;
	for(int i = 1; i <= n; i ++) std:: cin >> data[i];
	Build_tree(1, n, 1);
	for(; q; q --) {
		int x, y;
		std:: cin >> x >> y;
		std:: cout << Sec_A(1, n, 1, x, y) << "\n";
	}
	
	return 0;
}
```

---

## 作者：Santiego (赞：0)

[广告](https://www.cnblogs.com/santiego/p/11323090.html)

### 思路

有点难想的莫队。

首先我们肯定要一个`cnt[i]`记录难度`i`出现的次数，但是我们发现每次删去一个难度后，如果那个难度的个数恰好是当前最多次数，我们就可能要更新一下答案，**而这取决于有多少难度的个数恰好是当前最多次数**，于是我们再开一个`sum[i]`记录有多少难度的个数为`i`。

经过上述分析容易得到莫队更新规则：

```cpp
inline void add(int x){
	--sum[cnt[a[x]]];
	++cnt[a[x]];
	++sum[cnt[a[x]]];
	ans=max(cnt[a[x]], ans);
}
inline void del(int x){
	--sum[cnt[a[x]]];
	if(cnt[a[x]]==ans&&sum[cnt[a[x]]]==0) --ans;
	--cnt[a[x]];
	++sum[cnt[a[x]]];
}
```

另外注意一下因为范围为$-10^5\le a[i]\le 10^5$，所以我们可以将所有数先加上$10^5$（不用离散化了）

### 例码

```cpp
#include <cstdio>
#include <algorithm>
#include <cmath>
#define MAXN 100010
#define MAXQ 200010
using namespace std;
int ans,cnt[100001*2],sum[100001];
int a[MAXN];
inline void add(int x){
	--sum[cnt[a[x]]];
	++cnt[a[x]];
	++sum[cnt[a[x]]];
	ans=max(cnt[a[x]], ans);
}
inline void del(int x){
	--sum[cnt[a[x]]];
	if(cnt[a[x]]==ans&&sum[cnt[a[x]]]==0) --ans;
	--cnt[a[x]];
	++sum[cnt[a[x]]];
}
struct nod{
	int l,r,bid,qid;
} q[MAXQ];
bool cmp(const nod &a, const nod &b){
	return (a.bid^b.bid?(a.l<b.l):((a.bid&1)?(a.r<b.r):(a.r>b.r)));
}
int n,m,blo,res[MAXQ];
int main()
{
	scanf("%d %d", &n, &m);
	blo=n/sqrt(m*2/3);
	for(int i=1;i<=n;++i) scanf("%d", &a[i]),a[i]+=100000;
	for(int i=1;i<=m;++i){
		scanf("%d %d", &q[i].l, &q[i].r);
		q[i].bid=q[i].l/blo;
		q[i].qid=i;
	}
	sort(q+1, q+1+m, cmp);
	int l=1,r=1;cnt[a[1]]=1;sum[1]=1;ans=1;
	for(int i=1;i<=m;++i){
		while(l<q[i].l) del(l++);
		while(l>q[i].l) add(--l);
		while(r>q[i].r) del(r--);
		while(r<q[i].r) add(++r);
		res[q[i].qid]=ans;
	}
	for(int i=1;i<=m;++i) printf("%d\n", res[i]);
	return 0;
}
```



---

