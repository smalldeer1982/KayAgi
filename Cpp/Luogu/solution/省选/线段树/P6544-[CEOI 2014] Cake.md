# [CEOI 2014] Cake

## 题目背景

CEOI2014 Day2 T2，译者：小粉兔

## 题目描述

Leopold 和 Molly 都喜欢蛋糕：Leopold 喜欢吃蛋糕，Molly 喜欢看 Leopold 吃蛋糕。

现在有 $n$ 块蛋糕排成一排，从左到右数的第 $i$ 块蛋糕编号为 $i$，每块蛋糕有一个美味度 $d_i$。

Leopold 会先吃掉编号为 $a$ 的蛋糕，这样位置 $a$ 就空了。接下来每次他会选择一个与空出的位置相邻的蛋糕中美味度最小的蛋糕吃掉（要把好吃的留到最后）。你可以发现空出的位置一定是一个连续的区间。

为了让事情更加有趣，Molly 有时会给某一块蛋糕上加一点装饰，以增加它的美味度。她保证做完此操作后，这块蛋糕的美味度会变成所有蛋糕中前 $10$ 大的。而且在任何时候任意两块蛋糕的美味度都不同。

有时 Molly 好奇在 Leopold 吃掉某块特定的编号为 $b$ 的蛋糕之前，他会吃掉多少块蛋糕。

请你帮助 Molly 编写一个程序，给出操作序列，回答 Molly 的询问。

## 说明/提示

**【样例解释】**

在第一次增加美味度之前，编号为 $3, 2, 4, 5, 1$ 的蛋糕会依次被吃掉。但接下来编号为 $1$ 的蛋糕太好吃了以至于它不会先被吃掉，编号为 $4$ 和 $5$ 的蛋糕先被吃掉了。注意最后一次对编号为 $5$ 的蛋糕的美味度的增加不会改变吃蛋糕的顺序。

**【数据范围与提示】**

对于所有数据，保证 $1 \le n \le 2.5 \times {10}^5$，$1 \le q \le 5 \times {10}^5$，$1 \le d_i, a, i, b \le n$，$1 \le e \le 10$。

| 子任务编号 | 分值 | 特殊限制 |
| :-: | :-: | :-: |
| $1$ | $15$ | $n, q \le {10}^4$ |
| $2$ | $15$ | $n \le 2.5 \times {10}^4$ 且 `F` 操作的数量不超过 $500$ |
| $3$ | $20$ | $q \le {10}^5$ 且 `E` 操作的数量不超过 $100$ |
| $4$ | $50$ | 无特殊限制 |

## 样例 #1

### 输入

```
5 3
5 1 2 4 3
17
F 1
F 2
F 3
F 4
F 5
E 2 1
F 1
F 2
F 3
F 4
F 5
E 5 2
F 1
F 2
F 3
F 4
F 5```

### 输出

```
4
1
0
2
3
4
3
0
1
2
4
3
0
1
2```

# 题解

## 作者：hegm (赞：4)

### [P6544 [CEOI2014] Cake](https://www.luogu.com.cn/problem/P6544)

比较有意思，先不考虑修改操作，只看询问。

非常简单，对于 $b$ 到 $a$（不包含）的区间找到最大值 $mx$，然后找反方向第一个比这个值大的点 $c$ 那么答案就是区间 $(b,c)$ 的长度。

证明：

考虑现在先把 $a$ 删掉了，那么想要删掉 $b$，就必须要删掉 $a\sim b$ 之间的全部蛋糕，删掉他们的条件是另一侧出现了大于这个区间最大值的与元素，所以区间另一侧就是 $c$。

首先这个东西可以用线段树简单解决。

考虑修改操作，如果我们线段树存贮的是排名那么修改相当于对在 $[e,w_i)$ 的**权值**区间的位置进行 $+1$ 操作，这是不好做的，但是我们似乎不太能存贮权值，因为修改是将某个元素变为某个排名，如果是将 $i$ 插入 $3,4$ 两个权值之间，那么就需要小数了，精度容易爆炸。

考虑特殊性质：

> 这块蛋糕的美味度会变成所有蛋糕中前 $10$ 大的。

我们不妨记录相对权值，那么在修改的时候，将前 $e-1$ 大的 $+1$ ，然后将 $w_i$ 变为之前第 $e$ 大的多 $1$。

容易发现，这样的话每次最多修改 $10$ 个数，复杂度可以接受。

---

## 作者：FutaRimeWoawaSete (赞：3)

做了两个小时，还去要了点提示才把这道题给勉强做了出来。    

这道题其实有一个性质比较难找，刚开始时候完全没思路，后来各种乱想乱凑才找出来了这个性质。    

我们可以想到，如果我们从分界点把原序列分成两个序列处理，也就是 $1 \sim a - 1$ 和 $a + 1 \sim n$ 。    

现在为了行文方便，左边序列的“前面”就指的是它右边，右边序列的“前面”就指的是它左边……模拟的是吃蛋糕过程。

以左边序列举例。

我们发现一个左边序列的蛋糕之前能被吃掉多少块蛋糕和它前面的 $d_i$ 最大的蛋糕有关系，比如说它前面(包括它)最大的蛋糕的值为 $Maxd$ ，那么从右边序列的头到尾里面如果一直没出现一个值大于(毕竟没有相等数) $Maxd$ 就会一直杀下去，   

相反，如果出现一个蛋糕大于 $Maxd$ 的话，那么这个蛋糕就可以一直杀到左边序列的这个蛋糕。    

所以对于每个蛋糕的查询，我们就查询它前面(包括它)的所有蛋糕的 $Maxd$ ， 然后从右边序列的头到尾找到第一个值大于 $Maxd$ 为止，然后计算即可。     

这里不难发现，我们这个计算方法可以用线段树维护，可以直接维护区间最小值，我自己推的时候发现做个前缀最小值然后跑二分好像也可以过(不过这过程最后修改的时候还是得套个线段树，尽管死不成 $logn^2$ 但是确实复杂了一些)，最后还是直接维护的区间最小值……    

接着我们往里面加入修改操作，发现这个修改操作总之就是特别不讲武德，首先要单点修，接着还要改变相对大小关系……这就不是人好不好。    

我们回归原题，看数据发现 $d_i$ 值就是一个排列，并且我们最后计算答案的时候只需要它们的下标，而我们将 $d_i$ 转换成排名，我们刚才就 $Maxd$ 的过程就可以转换成求最小排名。    

走到这里，我们发现自己好像是在兜圈，我们可以再推一步，我们肯定可以知道第几个位置上的数的相对排名，如果我们把当前这个排名 $x$ 变成了 $y$ ， 那么其实我们需要改变的就是把 $x \sim y$ 的排名全部往后移一位……    

想到这里，其实已经很接近正解了，也是我思路中断的地方。我们现在必须要解决这个改变区间排名的毒瘤问题……貌似得套个更高级的数据结构？    

其实我们再认真整合一下我们的推导过程会发现我们还有一个东西没有用到极致——相对大小和数据范围。    

我们观察到 $1 \leq e \leq 10$ ，也就是说这道题给了我们可以暴力修改最前面的排名们的时间。  

其实也就是刚才的相对大小，我们发现我们把中间一段的排名往后面整体平移时，其实变化的相对大小就是把第 $i$ 个位置的相对排名进行了变化，所以只要能正确处理第 $i$ 个位置的相对排名，这道题就可以青结了。   

我们可以巧妙把 $+1$ 改成 $-1$ ，如果我们移到了 $x$ 大，就把 $1 \sim x$ 整体向左移，直到移到我们保存的排名下面第 $x$ 大的数与 第 $x + 1$ 大的数可以正确处理出其相对关系，由于是一起平移所以我们前面的数们的相对大小肯定可以不变，然后暴力把现在的前 $x$ 大的位置保存的相对排名打进线段树进行修改即可。    

我画图能力有限，就只能再尽可能描述了……相当于就是说把当前这个位置的排名移到前面的排名里去，然后我们现在其实唯一需要改动的是当前这个数与其它数的相对排名大小，我们可以记录当前的最小排名是多少，就把 $1 \sim x$ 移到这个排名还要往前，这样就可以保证我们的 $x$ 现在一定能和 $x + 1$ 确定出相对大小，然后我们暴力从 $x \sim 1$ 扫一遍，给他们赋一个新的“排名”。 

比如说，现在 $5$ 个数，当前只是第一次进行 $E$ 操作，最小排名肯定是 $1$ ，如果把第 $4$ 大数移到第 $2$ 大数去的话，那么我们就把 $1 \sim 2$ 的排名假定为 $-1 , 0$ ，就可以保证当前的第 $2$ 大的相对排名一定小于 第 $3,4,5$ 大的值里面保存的相对排名即确定了它们之间的相对关系，并且第 $1,2$ 大之间的相对排名即相对大小也可以处理出来。

具体实现可以看代码：    
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<vector>
using namespace std;
const int Len = 2.5e5 + 5;
struct node
{
	int val,idx;
}d[Len];
bool cmp(node x,node y){return x.val > y.val;}
int Id[Len],n,a,q,ans[Len << 2][2],rk[Len];
int ls(int x){return x << 1;}
int rs(int x){return x << 1 | 1;}
void push_up(int x,int t){ans[x][t] = min(ans[ls(x)][t] , ans[rs(x)][t]);}
void build(int p,int l,int r,int t)
{
	if(l == r)
	{
		ans[p][t] = d[l].val;
		return;
	}
	int mid = (l + r) >> 1;
	build(ls(p) , l , mid , t);
	build(rs(p) , mid + 1 , r , t);
	push_up(p , t);
}
void update(int p,int l,int r,int idx,int w,int t)
{
	if(l == r)
	{
		ans[p][t] = w;
		return;
	}
	int mid = (l + r) >> 1;
	if(idx <= mid) update(ls(p) , l , mid , idx , w , t);
	else update(rs(p) , mid + 1 , r , idx , w , t);
	push_up(p , t);
}
int query(int p,int l,int r,int nl,int nr,int t)
{
	if(nl <= l && nr >= r) return ans[p][t];
	int mid = (l + r) >> 1 , res = 1e9;
	if(nl <= mid) res = min(res , query(ls(p) , l , mid , nl , nr , t));
	if(nr > mid) res = min(res , query(rs(p) , mid + 1 , r , nl , nr , t));
	return res;
}
int find_l(int p,int l,int r,int fd)
{
	if(ans[p][0] > fd) return l - 1;//找不到
	if(l == r) return l;
	int mid = (l + r) >> 1;
	if(ans[rs(p)][0] < fd) return find_l(rs(p) , mid + 1 , r , fd);
	else return find_l(ls(p) , l , mid , fd); 
}
int find_r(int p,int l,int r,int fd)
{
	if(ans[p][1] > fd) return r + 1;
	if(l == r) return l;
	int mid = (l + r) >> 1;
	if(ans[ls(p)][1] < fd) return find_r(ls(p) , l , mid , fd);
	else return find_r(rs(p) , mid + 1 , r , fd);
}
char s[5];
int main()
{
	scanf("%d %d",&n,&a);
	for(int i = 1 ; i <= n ; i ++) 
	{
		scanf("%d",&d[i].val);
		d[i].val = n - d[i].val + 1;
		d[i].idx = i;
	}
	if(a != 1) build(1 , 1 , a - 1 , 0);
	if(a != n) build(1 , a + 1 , n , 1);
	sort(d + 1 , d + 1 + n , cmp);
	for(int i = 1 ; i <= n ; i ++) rk[i] = d[i].idx , Id[d[i].idx] = i;
	scanf("%d",&q);
	int nowminrk = 1;//用来记录当前的最小排名
	while(q --)
	{
		scanf("%s",s + 1);
		if(s[1] == 'F')
		{
			int x;scanf("%d",&x);
			if(x == a) printf("0\n");
			else if(x > a)//去左边查 
			{
				if(a == 1){printf("%d\n",x - 1);continue;}
				int Minn = query(1 , a + 1 , n , a + 1 , x , 1) , 
				Pos = a - 1 - find_l(1 , 1 , a - 1 , Minn);
				printf("%d\n",Pos + x - a);
			}
			else 
			{
				if(a == n){printf("%d\n",a - x);continue;}
				int Minn = query(1 , 1 , a - 1 , x , a - 1 , 0) , 
				Pos = find_r(1 , a + 1 , n , Minn) - a - 1;
				printf("%d\n",Pos + a - x);
			}
		}
		else 
		{
			int x,y,nowp = min(n , 10);scanf("%d %d",&x,&y);
			for(int i = 1 ; i <= min(n , 10) ; i ++) if(rk[i] == x) nowp = i;
			for(int i = nowp - 1 ; i >= y ; i --) rk[i + 1] = rk[i];
			rk[y] = x;
			for(int i = y ; i >= 1 ; i --)
			{
				nowminrk --;
				if(rk[i] > a) update(1 , a + 1 , n , rk[i] , nowminrk , 1);
				else if(rk[i] < a) update(1 , 1 , a - 1 , rk[i] , nowminrk , 0);
			} 
		}
	}
	return 0;
}
```

---

## 作者：djh0314 (赞：2)

[洛谷](https://www.luogu.com.cn/problem/P6544)。

## 题意
一共 $n$ 个蛋糕，每个蛋糕用有一个权值 $d_i$，会从某一个开始，吃两端权值更小的那个蛋糕。             
有 $q$ 个操作，分为两种：     
1. 修改，将编号为 $i$ 的蛋糕升为第 $e$ 美味的，保证一定是提高排名。
2. 查询，询问在吃掉编号为 $b$ 的蛋糕前会吃掉多少蛋糕。

$e\le 10$，$n\le 2.5 \times 10^5$，$q\le 5 \times 10^5$。

先划一下重点：$e\le 10$，并且是提升至 $e$ 这个排名。

## 分析

重新分析一下题目让我们做一些什么事，我们需要从我们的起始点开始，直到吃到指定点，再吃到指定点的过程中，我们必然吃到从指定点到起始点这一整块上的所有店，那也就代表，要么我们一边吃到了底，否则，就是在那一段有一个比我们这个路径都要大的点。

简单来说，我们的另一端是一个大于我们起始点至结束点最大值的点。

这是我们的查询操作，很明显满足二分性质，只要我们运用前缀和或者区间查询，就可以以 $O(\log n )$ 的时间复杂度解决。

由于起始点与终点的位置关系，因此要分类，此处只贴一边，另一边相近。
~~~cpp
inline int queryl(int id) {
	int x=tree.query(1,1,n,id,be-1),l=be+1,r=n,res=n+1;
	while(l<=r) {
		int mid=l+r>>1;
		int num=tree.query(1,1,n,be+1,mid);
		if(num>x) {
			res=mid;
			r=mid-1;
		} else l=mid+1;
	}
	return res;
}
~~~

接下来，我们的重点就到了修改上，这个修改很不同寻常，一般的修改应该是修改一个值，而此处却是修改到一个排名。

### 暴力

为了方便表述，坐标为 $id$。

我们的 $d_i$ 两两不同并且 $d_i\le n$，因此，我们的 $d$ 就是一个排列，那么我们只需要将所有值在 $d_{id}$ 与第 $e$ 个之间的 $d$ 下降，然后再将 $id$ 顶上即可。     
时间复杂度 $O(n)$，配合暴力的查询可以拿下 15，配合 $O(\log n)$ 的查询可以再拿下 20。

~~~cpp
int id=read(),x=read();
for(int j=1;j<=n;++j) if(a[j]>=x&&a[j]<a[id]) ++a[j];
a[id]=x;
tree.build(1,1,n);
~~~

## 正解

我们观察一下我们的查询操作，我们并不需要值的大小，而是需要值的大小关系，我们需要的序列并不一定是一个排列，只要大小关系，排名不变即可。

我们再观察一下我们这个非常优秀的性质 $e\le 10$，这个性质题目的一个约束条件。       

我们修改了比我们要修改的更小的值，那我们是不是也可以修改更大的值，而且非常巧啊，我们的这些更大值只要 10 个呢。     

我们讲前十大的记录，在修改时，将小于 $e$ 的全部 +1，修改当前点的值，重新维护前十小即可。

~~~cpp
int id=read(),x=read();
int num=b[x].num-1;
for(int i=1; i<x; ++i) tree.change(1,1,n,b[i].id,b[i].num-1),b[i].num--;
tree.change(1,1,n,id,num);
int flag=cnt+1;
for(int i=1; i<=cnt; ++i) if(b[i].id==id) flag=i;	
b[flag]=<%num,id%>;
if(flag<cnt+1) sort(b+1,b+cnt+1);
else sort(b+1,b+cnt+2);
~~~


### 总结一下，我们此题的问题并不是数据结构的难度，而是发掘题目的性质，并合理利用，解决即可。

---

## 作者：free_fall (赞：1)

首先是暴力的写法。

记录每一个点的答案，修改时重新跑一边，修改的时间复杂度为 $O(n)$，查询为 $O(1)$。发现有两个点可以过。

我们在这种写法上进行优化，发现时间的瓶颈在于修改，而题目中有一个特殊的条件“美味度一定会修改为前十大”。那么我们就可以暴力记下前十大的数以及它们的下标，当一个数修改时，将它的值变为比第 $e$ 块蛋糕的美味度加一的值，再将前 $e-1$ 块蛋糕的美味度加一即可。（注意有一个坑，如果修改前已经在前十，将它自己的值修改后重新排序）。

查询时我们需要用到线段树，每次找到起点与修改点之间的最大值，然后在起点的另一边找到第一个大于这个值的数，就可以计算出答案，查找的过程可以用二分实现（代码中有详细演示）。那么在修改时注意同时修改线段树上的值即可。

修改的时间复杂度为 $O(\log n)$，查询的时间复杂度为 $O(\log^2 n)$,总时间复杂度为 $O(n \log^2 n)$。
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5;
int n,a,q,d[N],ans[N],l,r,tot;
struct kk{
	int val,id;
	bool operator<(const kk &x)const{
		return val<x.val;
	}
}c[N];
struct seg_tree{
	#define ls p<<1
	#define rs p<<1|1
	int ma[N<<2];
	void push_up(int p){
		ma[p]=max(ma[ls],ma[rs]);
		return;
	}
	void build(int p,int l,int r){
		if(l==r){
			ma[p]=d[l];
			return;
		}
		int mid=l+r>>1;
		build(ls,l,mid);
		build(rs,mid+1,r);
		push_up(p);
		return;
	}
	void change(int p,int l,int r,int x,int c){
		if(l==r){
			ma[p]=c;
			return;
		}
		int mid=l+r>>1;
		if(x<=mid)change(ls,l,mid,x,c);
		if(mid<x)change(rs,mid+1,r,x,c);
		push_up(p);
		return;
	}
	int query(int p,int l,int r,int L,int R){
		if(L<=l&&r<=R)return ma[p];
		int mid=l+r>>1,res=0;
		if(L<=mid)res=max(res,query(ls,l,mid,L,R));
		if(mid<R)res=max(res,query(rs,mid+1,r,L,R));
		return res;
	}
	#undef ls
	#undef rs
}seg;
void add(kk x){
	for(int i=tot;i>=1;i--){
		if(c[i].id==x.id){
			c[i].val=x.val;
			for(int j=i-1;j>=1;j--){
				if(c[j]<c[j+1])swap(c[j],c[j+1]);
			}
			return;
		}
	}
	c[tot+1]=x;
	for(int i=tot;i>=1;i--){
		if(c[i]<c[i+1])swap(c[i],c[i+1]);
	}
	return;
}
signed main(){
	scanf("%lld%lld",&n,&a);
	tot=min(n,10ll);
	for(int i=1;i<=n;i++){
		scanf("%lld",&d[i]);
		add({d[i],i});
	}
	seg.build(1,1,n);
	scanf("%lld",&q);
	while(q--){
		char op[3];
		scanf("%s",op);
		if(op[0]=='E'){
			int i,e;
			scanf("%lld%lld",&i,&e);
			seg.change(1,1,n,i,c[e].val+1);
			for(int j=e-1;j>=1;j--){
				c[j].val++;
				seg.change(1,1,n,c[j].id,c[j].val);
			}
			add({c[e].val+1,i});
		}
		if(op[0]=='F'){
			int b,now;
			scanf("%lld",&b);
			if(b==a){
				printf("0\n");
				continue;
			}
			if(b<a){
				int l=1,r=n-a,res=n-a+1;
				now=seg.query(1,1,n,b,a-1);
				while(l<=r){
					int mid=l+r>>1;
					if(seg.query(1,1,n,a+1,a+mid)>now){
						r=mid-1;
						res=mid;
					}
					else l=mid+1;
				}
				res--;
				printf("%lld\n",a-b+res);
				continue;
			}
			now=seg.query(1,1,n,a+1,b);
			int l=1,r=a-1,res=a;
			while(l<=r){
				int mid=l+r>>1;
				if(seg.query(1,1,n,a-mid,a-1)>now){
					r=mid-1;
					res=mid;
				}
				else l=mid+1;
			}
			res--;
			printf("%lld\n",b-a+res);
		}
	}
	return 0;
}
```

---

## 作者：Azazеl (赞：1)

CEOI 的题目都好难啊qwq

#### 题意

> 给了一个长 $n$ 序列和开始位置，从开始位置起，每次走到两边最小的一个。中间可以修改某个数的**排名**到前十以内，多次询问每个数在被走到之前会先走多少个数。  

#### 题解

本篇题解中，我们以起始位置为分界线，把整个序列分成两部分。

不难发现每次我们的走法一定是走到某个地方，然后掉头，以此类推向两边扩展。而掉头的时候就是遇到了一个数，其值大于另一边的数的时候。可以发现在掉头之前，另一边的数是不会变化的。

而且我们不难想到若能走到某个数，则该数到起始位置之间（不包括起始位置）之间所有的数都被走过了。当然，也不难想到最有价值的其实应该是**最大的**那一个，因为它最有可能在从另一边过来的时候有**阻挡**。

那么什么时候最大的这个数也会被走到呢？那就是另外一边被走完了或者另外一边有更大的数进行了**阻挡**，由于向另一边走时，这边的最大值是不变的，因此进行阻挡的就是另一边第一个会被走到的大于那个最大值的数。

所以对于每个操作，我们需要维护：**这个数到起始位置（不包括起始位置）之间的区间最大值** 与 **某一部分最靠近起始位置的、大于某个数的数的位置**以及 **单点修改排名** 之后的结果，很容易想到线段树，同时对第二个操作进行二分。

至于略微有些恶心的排名，由于一开始这个序列中所有元素值都在 $n$ 以内，因此我们设一个极大值为 $n$ ，而题目保证了每次修改后的排名都在前十，所以暴力给前十的元素按排名改值就可以了。~~其实我猜出题人是出数据发现要保证序列中元素不重复懒得出了然后直接改成了改排名~~

然后我们就能以 $\mathcal{O(q \log n)}$ （再加上 $10$ 的常数）通过这道题了。

#### 代码

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
int n;
int d[250005],arr[250005],rk[250005];
struct SegmentTree{
	#define ls p<<1
	#define rs p<<1|1
	#define lson p<<1,l,mid
	#define rson p<<1|1,mid+1,r
	int tr[1000005]; 
	void pushUp(int p){tr[p]=max(tr[ls],tr[rs]);}
	void build(int p,int l,int r)
	{
		if(l==r)
		{
			tr[p]=d[l];
			return;
		}
		int mid=(l+r)>>1;
		build(lson);build(rson);
		pushUp(p);
		return;
	}
	void Modify(int p,int l,int r,int aim,int val)
	{
		if(l==r&&l==aim)
		{
			tr[p]=val;
			return;
		}
		int mid=(l+r)>>1;
		if(aim<=mid) Modify(lson,aim,val);
		else Modify(rson,aim,val);
		pushUp(p);
	}
	int queryMax(int p,int l,int r,int lx,int rx)
	{
		if(lx<=l&&r<=rx) return tr[p];
		int mid=(l+r)>>1,ret=0;
		if(lx<=mid) ret=max(ret,queryMax(lson,lx,rx));
		if(mid<rx)  ret=max(ret,queryMax(rson,lx,rx));
		return ret; 
	}
	int upper_bound_left(int p,int l,int r,int lx,int rx,int val)
	{
		if(l>rx||r<lx) return -1;
		if(tr[p]<val) return -1;
		if(l==r) return l;	
		int mid=(l+r)>>1;
		int rres=upper_bound_left(rson,lx,rx,val);
		if(rres>=1) return rres;
		else return upper_bound_left(lson,lx,rx,val);
	}
	int upper_bound_right(int p,int l,int r,int lx,int rx,int val)
	{
		if(l>rx||r<lx) return -1;
		if(tr[p]<val) return -1;
		if(l==r) return l;
		int mid=(l+r)>>1;
		int lres=upper_bound_right(lson,lx,rx,val);
		if(lres>=1) return lres;
		else return upper_bound_right(rson,lx,rx,val);
	}
	void Debug(int p,int l,int r)
	{
		int mid=(l+r)>>1;
		printf("[%d,%d]:%d\n",l,r,tr[p]);
		Debug(lson);Debug(rson);
	}
}Tr;
char s[250005];
int main() {
	int a,m;
	scanf("%d %d",&n,&a);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&d[i]);
		if(n-d[i]+1<=10) rk[n-d[i]+1]=i;
	}
	Tr.build(1,1,n);
	scanf("%d",&m);
	int Maxn=n,pos,val;
	while(m--)
	{
		scanf("%s",s+1);
		if(s[1]=='E')
		{
			int lst=min(n,10);
			scanf("%d %d",&pos,&val);
			for(int i=1;i<=10;i++) if(rk[i]==pos) lst=i;
			for(int i=lst-1;i>=val;i--) rk[i+1]=rk[i];
			rk[val]=pos;
			for(int i=val;i>=1;i--) Maxn++,Tr.Modify(1,1,n,rk[i],Maxn);
		}
		if(s[1]=='F')
		{
			scanf("%d",&pos);
			if(pos==a)
			{
				puts("0");
				continue;
			}
			if(pos<a)
			{
				int MAX=Tr.queryMax(1,1,n,pos,a-1);
				int k=Tr.upper_bound_right(1,1,n,a+1,n,MAX);
				if(k==-1) k=n+1;
				printf("%d\n",k-pos-1);
			}
			else
			{
				int MAX=Tr.queryMax(1,1,n,a+1,pos);
				int k=Tr.upper_bound_left(1,1,n,1,a-1,MAX);
				if(k==-1) k=0;
				printf("%d\n",pos-k-1);
			}
		}
	}
	return 0;
}
```





---

## 作者：Erica_N_Contina (赞：0)

如果没有修改操作，那么应该怎么样求？假设 $b$ 在 $a$ 左侧，记 $mx$ 为 $[b,a-1]$ 中的最大美味值，在 $[a+1,n]$ 中找到最靠左的满足 $d_p>mx$ 的位置 $p$，则我们要先吃完 $[b+1,p-1]$ 中的蛋糕才会吃 $b$，答案易求。我们对 $d$ 数组维护一个线段树（以下标为位置，权值为 $d_i$），在树上求区间最大值，以及树上二分查找即可。

问题是我们如何在修改操作中维护这棵线段树。我们记录数组 $c$ 表示当前权值从大到小排名第 $i$ 为的蛋糕的下标为 $c_i$。

假设我们现在要将第 $id$ 个蛋糕拿到第 $e$ 位，我们可以考虑把前 $e-1$ 位的蛋糕的 $d$ 都 $+1$，然后把 $id$ 插入 $c_e$（原先的 $c_e$ 及以后的向后挪动一位）。将 $d_{id}$ 赋值为原先的 $d_{c_e}+1$。

这个过程我们模拟即可，因为我们只需要维护长度最长为 $10$ 的 $c$ 数组即可。记得在修改 $d$ 值时在线段树上同步进行修改。

```C++
/*  Erica N  */
#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define int long long
#define ull unsigned long long
#define pii pair<int, int>
#define ps second
#define pf first
#define itn int
#define rd read()
int read(){
    int xx = 0, ff = 1;char ch = getchar();
    while (ch < '0' || ch > '9') {if (ch == '-')ff = -1; ch = getchar();}
    while (ch >= '0' && ch <= '9')xx = xx * 10 + (ch - '0'), ch = getchar();
    return xx * ff;
}
// void write(int out) {
// 	if (out < 0)
// 		putchar('-'), out = -out;
// 	if (out > 9)
// 		write(out / 10);
// 	putchar(out % 10 + '0');
// }
#define cdbg(x...) do { cerr << #x << " -> "; err(x); } while (0)
void err() { cerr << endl; }
template<template<typename...> class T, typename t, typename... A>
void err(T<t> a, A... x) { for (auto v: a) cerr << v << ' '; err(x...); }
template<typename T, typename... A>
void err(T a, A... x) { cerr << a << ' '; err(x...); }


const int N = 3e5 + 5;
const int INF = 1e18;
const int M = 1e7;
const int MOD = 1e9 + 7;

int d[N];
int n;

namespace SGT{
    //区间查询max 树上二分 单点覆盖

    int t[N<<2];

    inline void pushup(int x){
        t[x]=max(t[x<<1],t[x<<1|1]);
    }

    void build(int x,itn l,int r){
        if(l==r){
            t[x]=d[l];
            return ;
        }
        int mid=l+r>>1;
        build(x<<1,l,mid);
        build(x<<1|1,mid+1,r);
        pushup(x);
    }

    void change(int x,int l,int r,int p,int v){
        if(l==r){
            t[x]=v;
            return ;
        }
        int mid=l+r>>1;
        if(p<=mid)change(x<<1,l,mid,p,v);
        else change(x<<1|1,mid+1,r,p,v);
        pushup(x);
    }

    int query(int x,int l,int r,int pl,int pr){
        if(pl<=l&&pr>=r){
            return t[x];
        }
        int mid=l+r>>1;
        int res=0;
        if(pl<=mid)res=max(res,query(x<<1,l,mid,pl,pr));
        if(pr>mid)res=max(res,query(x<<1|1,mid+1,r,pl,pr));
        return res;
    }

    int locateL(int x,int l,int r,int pl,int pr,int v){
        if(l==r){
            if(t[x]>v)return l;
            return n+1;
        }
        int mid=l+r>>1;
        int res=n+1;
        if(t[x<<1]>v&&mid>=pl)res=locateL(x<<1,l,mid,pl,pr,v);
        if(t[x<<1|1]>v)res=min(res,locateL(x<<1|1,mid+1,r,pl,pr,v));
        return res;
    }

    int locateR(int x,int l,int r,int pl,int pr,int v){
        if(l==r){
            if(t[x]>v)return l;
            return 0;
        }
        int mid=l+r>>1;
        int res=0;
        if(t[x<<1|1]>v&&mid+1<=pr)res=locateR(x<<1|1,mid+1,r,pl,pr,v);
        if(t[x<<1]>v)res=max(res,locateR(x<<1,l,mid,pl,pr,v));
        return res;
    }
}using namespace SGT;

int c[12];
pii b[N];

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    

     n=rd;
     int A=rd;
    for(int i=1;i<=n;i++){
        d[i]=rd;
        b[i]={d[i],i};
    }

    sort(b+1,b+n+1);
    for(int i=1;i<=min(10ll,n);i++){
        c[i]=b[n-i+1].ps;
    }

    build(1,1,n);
    int q=rd;
    while(q--){
        char op;
        cin>>op;
        if(op=='E'){
            int id=rd,e=rd;
            int r=min(n,10ll);
            int cur=INF;
            for(int i=1;i<=r;i++){
                if(id==c[i]){
                    cur=i;
                    break;
                }
            }
            
            for(int i=min(cur-1,r);i>=e;i--){
                c[i+1]=c[i];
            }
            
            for(int i=1;i<e;i++){
                d[c[i]]++;
                change(1,1,n,c[i],d[c[i]]);
            }
            d[id]=d[c[e]]+1;
            change(1,1,n,id,d[id]);
            c[e]=id;
        }else{
            int B=rd;
            if(A==B){
                cout<<0<<'\n';
            }else if(A<B){
                int mx=query(1,1,n,A+1,B);
                int loc=locateR(1,1,n,1,A-1,mx);// >mx
                cout<<B-loc-1<<'\n';

            }else{
                int mx=query(1,1,n,B,A-1);
                int loc=locateL(1,1,n,A+1,n,mx);
                cout<<loc-B-1<<'\n';

            }
        }
    }

}
```

---

## 作者：_Kenma_ (赞：0)

# P6544 解题报告

## 前言

感觉没有紫……

但是评了我也没意见。

## 思路分析

首先考虑怎样计算答案。

如果 $b$ 在 $a$ 的左侧，那么设 $x$ 为 $[b,a]$ 的最大值，$c$ 为 $[a,n]$ 中最靠左的 $d_c>x$ 的位置，那么答案为 $b-c-1$。

应该不难理解。想要吃掉 $b$，必须吃掉 $[b,a]$ 的所有蛋糕，和 $[a,n]$ 中部分比 $d_b$ 小的蛋糕。

可以直接线段树二分解决。

瓶颈在于修改。

发现这个修改非常神秘，它只修改值的大小关系，但是不修改具体的值。

因为 $e\le 10$ 非常不正常，所以考虑从这里入手解决。

发现如果我们只维护前 $10$ 大所在的位置，那么修改时可以把前 $e-1$ 大的值整体向前平移一段距离，给第 $e$ 大留出位置，然后把第 $e+1$ 大往后的排名整体后移。

感觉上比维护实数值好写多了。

然后就做完了。

实际上，只需要维护一棵支持单点修改，查询最大值，查询区间 $>k$ 的最靠左/右的下标的线段树就行了。

总体复杂度 $O(en\log n)$，在洛谷上跑进了 300 ms。

## 代码实现

感觉上不是很难写，但是从想到做完还是用了 1 h。

```cpp

#include<bits/stdc++.h>
using namespace std;
int n,m,a,pos,maxn,sum,num,id,e,d[250005],c[250005];
char op;
int val[500005],ls[500005],rs[500005],dcnt,rt;
void pushup(int x){
	val[x]=max(val[ls[x]],val[rs[x]]);
}
void build(int l,int r,int &x){
	x=++dcnt;
	if(l==r){
		val[x]=d[l];
		return;
	}
	int mid=(l+r)>>1;
	build(l,mid,ls[x]);
	build(mid+1,r,rs[x]);
	pushup(x);
}
void modify(int l,int r,int pos,int k,int x){
	if(l==r && l==pos){
		val[x]=k;
		return;
	}
	int mid=(l+r)>>1;
	if(pos<=mid) modify(l,mid,pos,k,ls[x]);
	else modify(mid+1,r,pos,k,rs[x]);
	pushup(x);
}
int query(int l,int r,int ql,int qr,int x){
	if(ql<=l && r<=qr){
		return val[x];
	}
	int mid=(l+r)>>1,ans=0;
	if(ql<=mid) ans=max(ans,query(l,mid,ql,qr,ls[x]));
	if(qr>=mid+1) ans=max(ans,query(mid+1,r,ql,qr,rs[x]));
	return ans; 
}
int find_l(int l,int r,int ql,int qr,int k,int x){
	if(l==r){
		if(val[x]<k) return -1;
		else return l;
	}
	int mid=(l+r)>>1;
	if(ql<=mid && val[ls[x]]>=k){
		int ans=find_l(l,mid,ql,qr,k,ls[x]);
		if(ans!=-1) return ans;
	}
	if(qr>=mid+1){
		return find_l(mid+1,r,ql,qr,k,rs[x]);
	}else return -1;
}
int find_r(int l,int r,int ql,int qr,int k,int x){
	if(l==r){
		if(val[x]<k) return -1;
		else return l;
	} 
	int mid=(l+r)>>1;
	if(qr>=mid+1 && val[rs[x]]>=k){
		int ans=find_r(mid+1,r,ql,qr,k,rs[x]);
		if(ans!=-1) return ans;
	}
	if(ql<=mid){
		return find_r(l,mid,ql,qr,k,ls[x]);
	}else return  -1;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>a;
	for(int i=1;i<=n;i++){
		cin>>d[i];
		if(n-d[i]+1<=10) c[n-d[i]+1]=i;
	}
	build(1,n,rt);
	cin>>m;
	sum=n;
	for(int i=1;i<=m;i++){
		cin>>op;
		if(op=='F'){
			cin>>pos;
			if(pos==a){
				cout<<0<<'\n';
			}else if(pos<a){
				maxn=query(1,n,pos,a-1,rt);
				int k=(a==n?-1:find_l(1,n,a+1,n,maxn,rt));
				if(k==-1) k=n+1;
				cout<<k-pos-1<<'\n';
			}else{
				maxn=query(1,n,a+1,pos,rt);
				int k=(a==1?-1:find_r(1,n,1,a-1,maxn,rt));
				if(k==-1) k=0;
				cout<<pos-k-1<<'\n';
			}
		}else{
			int lst=min(n,10);
			cin>>pos>>num;
			for(int i=1;i<=10;i++){
				if(c[i]==pos) lst=i;
			}
			for(int i=lst-1;i>=num;i--){
				c[i+1]=c[i];
			}
			c[num]=pos;
			for(int i=num;i>=1;i--){
				sum++;
				modify(1,n,c[i],sum,rt);
			}
		}
	}
	return 0;
}


```

## 后记

最后要谴责 nfls 机子慢还要开小时限，使某些人的正解被卡常了。

还有我不是高二的老年选手……

---

## 作者：Seauy (赞：0)

## 题目大意

- 长度为 $n$ 排列 $\{d_i\}$，起点 $a$ 和 $q$ 次操作。

- 修改操作是将 $d_i$ 提升至第 $k$ 大（$k\in [1,10]$）。

- 每次查询 $i$，先删除位置 $a$，设空位置集合为 $[L,R]$，删除 $d_{L-1},d_{R+1}$ 中较小的，回答删除 $d_i$ 时已删除多少个数。

- $ n \in [1,2.5\times 10^5],q\in [1,5\times 10^5] $

# 一. 分析

可以把 $\{d_i\}$ 分为 $a$ 左边和右边两部分。单独看左半边，删除顺序是从右往左（左半部分的正方向），单独看右边就是从左往右（右半部分的正方向），最终的删除顺序其实可以认为是按顺序将左半部分插入右半部分（或者右半部分插入左半部分）。

考虑插入的过程，先是找到右边第一个比 $d_{a-1}$ 大的位置，然后把 $d_{a-1}$ 插入那个位置之前；接着从插入 $d_{a-1}$ 的位置开始找第一个比 $d_{a-2}$ 大的位置……以此类推。

如果左半部分中 $d_i>d_{i-1}$，那么最终的删除序列中 $d_{i-1}$ 就紧接着在 $d_i$ 右边，因为 $d_{i-1}$ 不足以跨越阻挡 $d_i$ 的数。既然如此，我们只需要分别维护左右部分“先于我插入的数都比我小”的位置，这样简化后的左右部分都是单调递增的了。

那么来处理查询。不妨 $i<a$，我们先找出简化后的左序列 $i$ 的前驱 $x$（最小的 $\geq i$ 的位置），然后找出 $x$ 在简化的右序列的后继 $y$（最小的 $d_y>d_x$ 的位置），答案就为 $y-x-1$。

对于修改操作，可以暴力维护前 $10$ 大的数的权值，然后左右的简化序列做对应修改。

# 二. 实现

维护简化序列可以用平衡树。对于查询操作在平衡树上二分即可；对于修改操作，提升 $d_i$ 的权值后删除简化序列后比他小的元素即可。

单次查询 $O(\log n)$，总的修改复杂度 $O((q+n)\log n + 10q)$。

总的时间复杂度 $O(n \log n + q(10+\log n))$，空间 $O(n+q)$。

# 三. 代码

~~懒得手打平衡树因此写了两个 log 的 set~~

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef set<int>::iterator it;

const int MAXN=2.5e5,MAXQ=5e5;

int n,beg,q;
int d[MAXN+5];
int Top[11];//最大的 10 个蛋糕
set<int> Q;
int inTop[MAXN+5];

int main()
{
	scanf("%d %d",&n,&beg);
	for(int i=1;i<=n;i++) scanf("%d",&d[i]);
	scanf("%d",&q);
	if(n<=10)
	{
		char opt;
		for(int x,v;q--;)
		{
			cin>>opt;
			if(opt=='E')
			{
				scanf("%d %d",&x,&v);
				v=n-v+1;
				for(int i=1;i<=n;i++)
					if(d[x]<d[i] && d[i]<=v) --d[i];
				d[x]=v;
			}
			else
			{
				scanf("%d",&x);
				if(beg==x) {printf("0\n");continue;}
				int L=beg-1,R=beg+1;
				int ans=0;
				while(x<=L || R<=x)
				{
					int Lval=n+1,Rval=n+1;
					if(L>=1) Lval=d[L];
					if(R<=n) Rval=d[R];
					if(Lval<Rval) --L;
					else ++R;
					++ans;
				}
				printf("%d\n",ans);
			}
		}
		return 0;
	}
	for(int i=1;i<=n;i++)
		if(d[i]>=n-9) Top[n-d[i]+1]=i,inTop[i]=n-d[i]+1;//从大到小 
	//for(int i=1;i<=10;i++) printf("%d ",Top[i]);printf("\n");
	
	Q.insert(beg);
	int lst=0;
	for(int i=beg+1;i<=n;i++)
		if(d[i]>lst) lst=d[i],Q.insert(i);
	lst=0;
	for(int i=beg-1;i>=1;i--)
		if(d[i]>lst) lst=d[i],Q.insert(i);
	Q.insert(0),Q.insert(n+1);
	d[0]=d[n+1]=2*MAXQ;
	
	char opt;
	for(int x,v;q--;)
	{
		cin>>opt;
		if(opt=='E')
		{
			scanf("%d %d",&x,&v);

			d[x]=d[Top[v]]+1;
			if(!inTop[x])
			{
				inTop[Top[10]]=0;
				for(int i=10;i>v;i--) Top[i]=Top[i-1],inTop[Top[i]]=i;
			}
			else for(int i=inTop[x];i>v;i--) Top[i]=Top[i-1],inTop[Top[i]]=i;
			
			Top[v]=x;
			inTop[x]=v;
			for(int i=v-1;i>=1;i--) d[Top[i]]=d[Top[i+1]]+1;
			
			if(x==beg) continue;
			it now;
			if(x<beg)
			{
				now=Q.upper_bound(x);
				if(d[x]<d[*now] && (*now)<beg) continue;
				Q.insert(x);
				while(1)
				{
					now=(--Q.lower_bound(x));
					if(d[x]<d[*now]) break;
					Q.erase(now);
				}
			}
			else
			{
				now=(--Q.lower_bound(x));
				if(d[x]<d[*now] && (*now)>beg) continue;
				Q.insert(x);
				while(1)
				{
					now=Q.upper_bound(x);
					if(d[x]<d[*now]) break;
					Q.erase(now);
				}
			}
		}
		else
		{
			scanf("%d",&x);
			
			if(x==beg) {printf("0\n");continue;}
			if(x<beg)
			{
				int val=d[*Q.lower_bound(x)];
				it i;
				for(i=++Q.lower_bound(beg);1;i++)
					if(d[*i]>val) break;
				printf("%d\n",(*i)-1-x);
			}
			else
			{
				int val=d[*--Q.upper_bound(x)];
				it i;
				for(i=--Q.lower_bound(beg);1;i--)
					if(d[*i]>val) break;
				printf("%d\n",x-(*i)-1);
			}
		}
	}
	return 0;
}
```


---

