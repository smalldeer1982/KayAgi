# [KSN2021] Colouring Balls

## 题目描述

**这是一道交互题。**

有 $N$ 个小球，从 $1$ 到 $N$ 编号。

你每次可以询问编号在 $[l,r]$ 之间的小球有几种不同的颜色，你需要求出每个小球的颜色。由于你并不知道具体颜色是什么，你只要将同种颜色用同一个数字表示即可。

## 交互格式

第一行输入一个正整数 $T$，**代表 Subtask 编号（而不是测试数据组数）**。

第二行输入两个整数 $N,Q$，代表小球数量和询问次数限制。

接下来你可以提出不超过 $Q$ 个询问并读取交互库返回的答案，每个询问的格式为 ``? l r``，代表你询问 $[l,r]$ 中小球颜色的数量。

当你确认所有小球的颜色后，你需要输出 ``! a1 a2 ... an`` 代表所有小球的颜色。你需要保证：

* $1\leq a_i\leq N$ 且 $a_i$ 均为整数。
* 相同颜色的小球的 $a_i$ 相同。
* 不同颜色的小球的 $a_i$ 不同。

你的每次输出后都需要刷新缓冲区，你可以使用如下语句来清空缓冲区：

- 对于 C/C++：`fflush(stdout)`；
- 对于 C++：`std::cout << std::flush`；
- 对于 Java：`System.out.flush()`；
- 对于 Python：`stdout.flush()`；
- 对于 Pascal：`flush(output)`；
- 对于其他语言，请自行查阅对应语言的帮助文档。

## 说明/提示

**【数据范围】**

**本题采用捆绑测试。**

* Subtask 1（8 points）：$Q=10000$, 保证每种颜色的球的编号连续。
* Subtask 2（7 points）：$Q=2000$，保证每种颜色的球的编号连续。
* Subtask 3（19 points）：$Q=2000$，保证球只有至多 $3$ 种颜色。
* Subtask 4（14 points）：$Q=2000$，保证球只有至多 $4$ 种颜色。
* Subtask 5（12 points）：$Q=2000$，保证球有至少 $(N-1)$ 种颜色。
* Subtask 6（21 points）：$Q=10000$，保证 $N\le 100$。
* Subtask 7（19 points）：$Q=10000$。

对于所有数据，保证 $1\leq T\leq 7$，$2\leq N\leq 10^3$。

## 样例 #1

### 输入

```
1
5 10000

2

1

2
 ```

### 输出

```
 

? 1 5

? 1 3

? 2 4

! 1 1 1 2 2```

# 题解

## 作者：Natsume_Rin (赞：5)

入 OI 以来做的第二道交互题。

[题目传送门](https://www.luogu.com.cn/problem/P7971)

### 题意简述

有 $n$ 个颜色未知的球，你现在可以通过 $Q$ 次询问，每次询问一个区间 $[l,r]$ 中球的颜色数，需要你确定最后的所有球的颜色异同。

数据范围 $n \leq 1000$，$2000 \leq Q \leq 10000$，$Q$ 的范围与子任务特性有关。

--------------------------------------------

### 一般性解法

先可以不考虑子任务，考虑 $n=1000,Q=10000$ 时怎么做。

首先我们可以从 $n$ 号球推到 $1$ 号球，假设当前的颜色已经出现了 $k$ 个不同的，分别为 $c_1,c_2,c_3\dots c_k$，它们出现的 **最靠前的位置** 分别为 $p_1,p_2,p_3\dots p_k$，满足 $p$ 序列升序。

那么假设当前需要求解 $i$ 号球，那么在 $[1,k]$ 中二分一个 $p_{mid}$，可以自行想象一下，如果询问区间 $[i,p_{mid}]$，得到的结果是 $res$，如果

- $res = mid$，那么说明这一个球在颜色 $c_1,c_2,c_3\dots c_{mid}$ 之间，将二分的右端点变为 $mid-1$。
- $res=mid+1$，那么说明这一个球在颜色 $c_{mid+1},c_{mid+2},c_{mid+3}\dots c_k$ 中 **或者是一个新颜色**，将二分的左端点变为 $mid+1$。
- 好吧，其实没有第三种情况了。

最后就可以通过二分得到答案。这里举一个 $col=[1,3,2,2,2,1]$ 的例子求解 $col_1$ 以便大家理解。

- 当前 $c=[3,2,1]$，$p=[2,3,6]$，二分左右端点为 $[1,3]$。
	- $mid=2$，$p_{mid}=3$，询问 $[1,3]$，$res=3$，说明这一个颜色是 $1$ 或者是一个新颜色 $4$。二分左右端点为 $[3,3]$。
   - $mid=3$，$p_{mid}=6$，询问 $[1,6]$，$res=3$，说明这一个球就是颜色 $1$。
- 最后更新 $c=[1,3,2]$，$p=[1,2,3]$。

这样需要询问 $n \log_2 n$，实测可以通过 $Q=10000$ 的子任务。

---------------------------------------

### 数据分治

~~不知道正解是否需要，但是我的需要。~~

- $T=2$

颜色段连续，所以对于每一个球 $i$，只需要询问 $[i,i+1]$ 即可知道异同关系。询问次数为 $n-1$。

- $T=3$

照常做，用一般性解法，询问次数大约为 $2n-2$。

- $T=5$

每次询问区间 $[i,n]$，如果 $res_{i,n}=res_{i+1,n}$，那么就二分，否则就是新颜色，询问次数大约为 $n+\log_2 n$。

- $T=4$

有点意思。

当颜色数为 $4$ 时，那么就不可能出现新颜色。一个可能二分的过程是这样的。

- $[1,4]$，$mid=2$。
- $[3,4]$，$mid=3$。
- $[4,4]$，$mid=4$。

你会发现这样子每一个球会询问 $3$ 次，总询问次数约为 $3n$ 无法通过。

怎么优化呢？

突破口就在于 **不可能出现新颜色**，所以当二分区间 $[l,r]$ 满足 $l=r$ 且颜色数为 $4$ 时，那么 $col_i=c_l$，因为 **只有这一种颜色可选，又不可能出现新颜色**。这样就可以将询问次数降到 $2n$ 级别，可以通过。

---------------------------------------------

### 放在最后

很好的一道题。~~我才不会告诉你我做了很久。~~
代码就不放了（太丑了）。

完结撒花。

---

## 作者：gyh20 (赞：4)

从前往后枚举，每次新确定一个点 $i$ 的颜色，根据 Subtask 不同做法不同：

Subtask 2：

每种球颜色连续，可以类似双指针，维护一个指针 $pos$，如果 $[pos,i]$ 的颜色不为 $1$ 就 $pos$ 向右移，可以做到 $2N$ 次。

Subtask 3&4：

对于 $3$ 种颜色，维护每种颜色最后出现的位置，将颜色按照位置排序，一一询问判断，可以做到 $2N$ 次。

$4$ 种颜色时这样做是 $3N$ 次的，可以直接手动在 $4$ 种颜色上二分做到 $2N$ 次。

Subtask 5：

这个 Subtask 采取一个不一样的做法。

先特判所有颜色互不相同。

维护两个指针 $L,R$，一直将 $L$ 向右移，保证 $[L,R]$ 的颜色为 $R-L$，之后再把 $R$ 向左移，$L,R$ 就是颜色相同的两个点。

Subtask 7：

$N=1000,Q=10000$，是一个 $N\log N$ 级别的算法。

不难想到二分，二分一个位置 $mid$，判断 $[mid,i-1]$ 与 $[mid,i]$ 之间的颜色数是否相同，如果相同说明 $[mid,i-1]$ 中有与 $i$ 颜色相同的点，数 $[mid,i-1]$ 的颜色可以直接暴力数。

```cpp
#include<bits/stdc++.h>
#define re register
using namespace std;
inline int read(){
	re int t=0;re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
}
const int M=998244353;
inline void add(re int &x,re int y){(x+=y)>=M?x-=M:x;}
inline int Mod(re int x){return x>=M?x-M:x;}
inline int ksm(re int x,re int y){
	re int s=1;
	while(y){
		if(y&1)s=1ll*s*x%M;
		x=1ll*x*x%M,y>>=1;
	}
	return s;
}
int t,n,m,a[1000002],ans,c[10002],tot,v[10002],tim,lst[8],p[8];
inline bool cmp(re int x,re int y){return lst[x]>lst[y];}
inline int Count(re int l,re int r){
	++tim;
	re int s=0;
	for(re int i=l;i<=r;++i)if(v[c[i]]!=tim)v[c[i]]=tim,++s;
	return s;
}
inline int ask(re int l,re int r){
	printf("? %d %d\n",l,r);
	fflush(stdout);
	return read();
}
int main(){
	t=read(),n=read(),m=read();
	if(t==2){
		c[1]=tot=1;re int pos=1;
		for(re int i=2;i<=n;++i){
			while(ask(pos,i)!=1)++pos;
			if(pos==i)c[i]=++tot;
			else c[i]=c[pos];
		}
		printf("! ");
		for(re int i=1;i<=n;++i)printf("%d ",c[i]);
		fflush(stdout);
		return 0;
	}
	if(t==3){
		c[1]=tot=1,lst[1]=1,p[1]=1,p[2]=2,p[3]=3;
		for(re int i=2;i<=n;++i){
			sort(p+1,p+4,cmp);
			for(re int j=1;j<=3;++j){
				if(j==3||lst[p[j]]==0){c[i]=p[j];break;}
				if(ask(lst[p[j]],i)==j){c[i]=p[j];break;}
			}
			lst[c[i]]=i;
		}
		printf("! ");
		for(re int i=1;i<=n;++i)printf("%d ",c[i]);
		fflush(stdout);
		return 0;
	}
	if(t==4){
		c[1]=tot=1,lst[1]=1,p[1]=1,p[2]=2,p[3]=3,p[4]=4;
		for(re int i=2;i<=n;++i){
			sort(p+1,p+5,cmp);
			if(lst[p[2]]==0||ask(lst[p[2]],i)<=2){
				if(ask(lst[p[1]],i)==1)c[i]=p[1];
				else c[i]=p[2];
			}
			else{
				if(!lst[p[3]]||ask(lst[p[3]],i)==3)c[i]=p[3];
				else c[i]=p[4];
			}
			lst[c[i]]=i;
		}
		printf("! ");
		for(re int i=1;i<=n;++i)printf("%d ",c[i]);
		fflush(stdout);
		return 0;
	}
	if(t==5){
		re int L=1,R=n;
		if(ask(L,R)==n){
		printf("! ");
		for(re int i=1;i<=n;++i)printf("%d ",i);
		fflush(stdout);
		return 0;
	}
		while(ask(L,R)==R-L)--R;
		++R;
		while(ask(L,R)==R-L)++L;
		--L;
		for(re int i=1;i<=n;++i)if(i!=R)c[i]=++tot;else c[i]=c[L];
		printf("! ");
		for(re int i=1;i<=n;++i)printf("%d ",c[i]);
		fflush(stdout);
		return 0;
	}
	c[1]=1,tot=1;
	for(re int i=2;i<=n;++i){
		re int l=1,r=i-1,pos=i;
		while(l<=r){
			re int mid=l+r>>1;
			if(ask(mid,i)!=Count(mid,i-1))pos=mid,r=mid-1;
			else l=mid+1;
		}
		if(pos==1)c[i]=++tot;
		else c[i]=c[pos-1];
	}
	printf("! ");
	for(re int i=1;i<=n;++i)printf("%d ",c[i]);
	fflush(stdout);
}
```


---

## 作者：serene_analysis (赞：3)

提供一个不一样的数据分治做法。

---

题意已经很清楚了。

不考虑 Subtask，先思考一下正常做法。

首先第 $1$ 个球颜色直接就是 $1$。第 $2$ 个球询问 $[1,2]$ 的颜色数 $t$，颜色其实就是 $t$。到第三个球时事情变得复杂起来，如果直接询问 $[2,3]$ 颜色数，回答如果是 $2$，就还要问一遍 $[1,3]$。以此类推。

结合数据范围 $N=10^3,Q=10^4$，一个大概的二分想法浮出水面。设当前球是 $i$，在 $[1,i-1]$ 上二分，如果当前中点 $m$ 到 $i-1$ 的已知颜色数（这里直接暴力遍历）等于询问 $[m,i]$ 的回答，那就说明 $\exists \ j \in [m,i-1],col_j=col_i$，缩小二分左边界；否则缩小二分右边界。如果最后没有得到答案，说明 $i$ 是没有出现过的颜色，否则 $i$ 的颜色就是二分答案位置的颜色。这样的写法足够通过任何 $Q=10^4$ 的点。

$Q=2 \times 10^3$ 的点怎么做？看起来只能数据分治了。

先考虑最简单的 Subtask 2&5。对于编号连续，一个球的颜色直接询问其与前一个球的颜色总数，若为 $1$ 则二者颜色相同，否则是一个新颜色。对于至多只有 $2$ 个球的颜色相同，设两个指针 $L=R=1$，持续将 $R$ 右移直到 $[L,R]$ 的颜色不等于区间长度，然后持续将 $L$ 右移直到 $[L+1,R]$ 的颜色数等于 $R-L$，此时的 $L,R$ 就是颜色相同的两个球。

对于 Subtask 3&4，极小的颜色数量给了我分类讨论的勇气。设当前出现过的颜色数量为 $k$，按最近一次出现的位置从小到大排序后分别是 $\texttt{std::pair<int,int>fir,sec,thi,fou}$，其中第一个元素是位置（以下用 $pos1,pos2,pos3,pos4$ 表示），第二个元素是颜色编号（以下用 $id1,id2,id3,id4$ 表示）。

- 若不存在 $thi$，直接询问 $[pos4,i]$，根据回答判断是否是新颜色。
- 若不存在 $sec$，询问 $[pos4,i]$，若回答为 $1$ 则 $col_i=id4$，否则询问 $[pos3,i]$，若回答为 $2$ 则 $col_i=id3$，否则是新颜色。
- 若不存在 $fir$，询问 $[pos3,i]$，若回答为 $2$ 则根据 $[pos4,i]$ 的答案判断是 $id4$ 还是新颜色；若回答是 $3$ 则根据 $[pos2,i]$ 的回答判断是 $id2$ 还是新颜色。
- 若都存在，询问 $[pos3,i]$，若回答是 $2$ 则根据 $[pos4,i]$ 的回答判断是 $id3$ 还是 $id4$；若回答是 $3$ 则根据 $[pos2,i]$ 的回答判断是 $id1$ 还是 $id2$，因为此时已经不存在新颜色了。

实际上代码远比想象中好写，别被吓到了。

以上的所有数据分治，都可以直接看出询问次数不超过 $2n$，能通过本题。

正常做法的时间复杂度为 $\Theta(n^2 \log n)$，数据分治的时间复杂度是 $\Theta(n)$。

给个分类讨论的部分。

```cpp
pii mem[10];
int last[10];
void tturn(pii &a,pii &b,pii &c){
	mem[1]=a,mem[2]=b,mem[3]=c;
	std::sort(mem+1,mem+4);
	a=mem[1],b=mem[2],c=mem[3];
	return;
}
void fturn(pii &a,pii &b,pii &c,pii &d){
	mem[1]=a,mem[2]=b,mem[3]=c,mem[4]=d;
	std::sort(mem+1,mem+5);
	a=mem[1],b=mem[2],c=mem[3],d=mem[4];
	return;
}
void refer(int i,int ncol){
	col[i]=ncol;
	last[ncol]=i;
	return;
}
#define id second
void count(int gave){
	col[1]=ccnt=last[1]=1;
	if(gave==3){
		for(int i=2;i<=n;i++){
			pii fir={last[1],1},sec={last[2],2},thi={last[3],3};
			tturn(fir,sec,thi);
			if(!sec.first){
				if(qcol(thi.first,i)==2)refer(i,++ccnt);
				else refer(i,1);
			}
			else if(!fir.first){
				if(qcol(sec.first,i)==3)refer(i,++ccnt);
				else{
					if(qcol(thi.first,i)==1)refer(i,thi.id);
					else refer(i,sec.id);
				}
			}
			else{
				if(qcol(sec.first,i)==3)refer(i,fir.id);
				else{
					if(qcol(thi.first,i)==1)refer(i,thi.id);
					else refer(i,sec.id);
				}
			}
		}
	}
	else{
		for(int i=2;i<=n;i++){
			pii fir={last[1],1},sec={last[2],2},thi={last[3],3},fou={last[4],4};
			fturn(fir,sec,thi,fou);
			if(!sec.first){
				if(!thi.first){
					if(qcol(fou.first,i)==2)refer(i,++ccnt);
					else refer(i,1);
				}
				else{
					if(qcol(thi.first,i)==3)refer(i,++ccnt);
					else{
						if(qcol(fou.first,i)==1)refer(i,fou.id);
						else refer(i,thi.id);
					}
				}
			}
			else if(!fir.first){
				if(qcol(thi.first,i)==3){
					if(qcol(sec.first,i)==4)refer(i,++ccnt);
					else refer(i,sec.id);
				}
				else{
					if(qcol(fou.first,i)==1)refer(i,fou.id);
					else refer(i,thi.id);
				}
			}
			else{
				if(qcol(thi.first,i)==3){
					if(qcol(sec.first,i)==4)refer(i,fir.id);
					else refer(i,sec.id);
				}
				else{
					if(qcol(fou.first,i)==1)refer(i,fou.id);
					else refer(i,thi.id);
				}
			}
		}
	}
	report();
	return;
}
#undef id
```

感谢你的阅读。

---

## 作者：Ristear (赞：2)

## 题目大意：
有 $n$ 个未知颜色的小球，我们最多可以询问 $Q$ 次，每次询问返回区间 $[l,r]$ 内小球颜色种类的个数。

## 题解：
我们可以通过不同的 $T$ 来分别解决问题。

初始时我们定义 $a_1 = 1$。

- $T = 1$ 或 $T = 2$

因为颜色块都是连续的，所以我们查询 $n-1$ 次，每次查询相邻两个小球，若为 $1$，则与上一个相同，反之则不同。

```cpp
void solve1()
{
	a[1]=1;
	for(int i=1;i<n;i++)
	{
		int x=query(i,i+1);
		if(x==1) {a[i+1]=a[i];}
		else {a[i+1]=a[i]+1;}
	}
	return ;
}
```

- $T = 3$

因为颜色数很少，所以我们可以维护每种颜色最后出现的位置，并且按照最后出现的顺序排序，然后分类讨论求解。

```cpp

void solve2()
{
	a[1]=1;
	for(int i=2;i<=n;i++)
	{
		sort(p+1,p+4,cmp);
		if(query(Last[p[1]],i)==1) {a[i]=p[1];}
		else if(query(Last[p[2]],i)==2) {a[i]=p[2];}
		else {a[i]=p[3];}Last[a[i]]=i;
	}
	return ;
}
```
- $T = 4$

同 $T = 3$ 的情况，不过要分类讨论的情况要多一些。

```cpp

void solve3()
{
	a[1]=1;
	for(int i=2;i<=n;i++)
	{
		sort(p+1,p+5,cmp);
		if(Last[p[2]]==0||query(Last[p[2]],i)<=2)
		{
			if(query(Last[p[1]],i)==1) {a[i]=p[1];}
			else {a[i]=p[2];}
		}
		else
		{
			if(!Last[p[3]]||query(Last[p[3]],i)==3) {a[i]=p[3];}
			else {a[i]=p[4];}
		}
		Last[a[i]]=i;
	}
	return ;
}
```

- $T = 5$

这种情况因为色块数很多，但是最多只会有两个是颜色相同的，所以我们只需要建立两个下标，如果有两个相同颜色的色块，记录相同的两个点的位置。

```cpp

void solve4()
{
	int X=0,Y=0;
	for(int i=2;i<=n;i++) {if(query(1,i)!=i) {X=i;break;}}
	for(int i=1;i<=X;i++) {if(query(i,X)==X-i+1) {Y=i-1;break;}}
	cnt=a[X]=a[Y]=1;
	if(!X) {cnt--;}
	for(int i=1;i<=n;i++)
	{
		if(i==X||i==Y) {continue;}
		cnt++;a[i]=cnt;
	}
	return ;
}
```

- $T = 6$ 或 $T = 7$

因为数据范围比较大，所以可以考虑二分求解，查询区间 $[mid,i-1]$ 的小球颜色个数与区间 $[mid,i]$ 的小球颜色个数是否相同，若相同，则说明 $[mid,i−1]$ 中有与 $i$ 颜色相同的点，反之则没有。因为我们从 $1$ 开始枚举 $i$，所以对于区间 $[mid,i-1]$ 的小球颜色都是已知的，可以直接暴力查询。

```cpp
void solve5()
{
	a[1]=1;cnt=1;
	for(int i=2;i<=n;i++)
	{
		int l=1,r=i;
		while(l<r)
		{
			int mid=(l+r)>>1;
			if(query(mid,i)==Count(mid,i-1)) {l=mid+1;}
			else {r=mid;}
		}
		if(r==1) {cnt++;a[i]=cnt;}
		else {a[i]=a[r-1];}
	}
	return ;
}
```


### 题外话：
这道题的数据有点问题，如果只输出 $1$ 竟然可以过，希望管理员可以修一下这道题的数据。

---

## 作者：Steven_lzx (赞：2)

更好的阅读体验，以及代码，请见 <https://www.cnblogs.com/2020gyk080/p/16878561.html>。

纪念一下人生中第一道数据分治题。

## Subtask 1&2

这一部分具有的特殊性质是颜色段连续，那我们可以判断当前与前一个的颜色数是否为 1，若是则颜色相同，否则让颜色 +1。


## Subtask 3&4

这一部分由于颜色数不多，我们可以记录当前位置已经出现的颜色数量以及每种颜色最后出现的位置，根据这个直接分类讨论当前位置的颜色。

## Subtask 5

首先特判掉每个位置颜色都不同的情况。

然后我们考虑双指针，维护两个指针 $i,j$，让它们不断向中间移动的同时保证 $[i,j]$ 的颜色数等于 $j-i$，最后找到的两个指针的位置就是颜色相同的地方。

## Subtask 6&7

考虑二分，判断 $[mid,i-1]$ 的颜色数是否等于 $[mid,i]$ 的颜色数，如果相同则说明 $[mid,i-1]$ 中有与 $i$ 颜色相同的点，暴力数出来即可。

---

## 作者：Eafoo (赞：1)

很有意思的一道交互题。

# 题意

给定一个颜色序列 $a$，每次可以询问 $l$ ~ $r$ 中不同的颜色个数，要求复原出整个序列。

# Subtask 1 & 2

送分的，每次询问 $p$ 和 $p + 1$ 位置，如果返回 $2$ 就说明他俩颜色不同，$p + 1$ 位置是一个新的颜色，否则它俩颜色相同。

# Subtask 3 ~ 4 & 6 ~ 7

观察这几组 Subtask 的询问次数限制，发现都是 $n \log n$ 级别的，我们考虑二分。

首先假设我们现在要求 $a_i$ 并且我们已经求出了 $a_1$ ~ $a_{i-1}$。

考虑这样一种情况：

```
1 2 3 3 2 4
```

其中前六项是我们在之前过程中求得的，我们要求出颜色序列的第七项。

那么我们从右往左遍历整个序列，每次出现一种新颜色就记下它的位置，存入 $p$ 数组中。

例中这个序列中我们记下的位置为 6(颜色 4)、5(颜色 2)、4(颜色 3)、1(颜色 1)，则 $p = [6, 5, 4, 1]$。

容易发现 $p_j$ 到 $i$ 位置中 共有 $j$ 种不同的颜色。

考虑对于 $p_j$ ~ $i$ 进行一次查询，如果结果刚好等于 $j$ 则说明 $a_i$ 在 $a_{p_j}$ ~ $a_{i - 1}$ 中出现过，如果结果等于 $j + 1$ 则说明 $a_i$ 未在 $a_{p_j}$ ~ $a_{i - 1}$ 中出现过。

比如例中若 $a_7 = 3$，我们查询 $5$ ~ $7$ 结果为 $2$，说明 $a_7$ 未在 $a_5$ ~ $a_6$ 出现过，我们查询 $4$ ~ $7$ 结果为 $2$，说明 $a_7$ 在 $a_4$ ~ $a_6$ 中出现过。

那么我们就可以二分了。每次对于 $mid$ 用上述方式进行查询，若 $a_i$ 在 $a_{p_j}$ ~ $a_{i - 1}$ 中出现过则左移右指针，否则右移左指针。

需要注意的是，如果二分最后无解，就说明 $a_i$ 未在 $a_1$ ~ $a_{i-1}$ 中出现过，那么 $a_i$ 就是一种新颜色。

另外，我们发现 Subtask 4 中我们的查询次数会被卡，这是因为如果直接在 $1$ ~ $4$ 的值域内二分，则每一个位置的查询次数上界为 $3$，总查询次数上界为 $3n$。

那么我们需要考虑优化。

首先查询一次 $1$ ~ $n$ 来查询序列的总颜色数 $tot$，如果当前出现过的颜色数量等于 $tot$，我们就把二分中 $r$ 的初始值改为 $tot - 1$。如果最后二分无解那么就说明当前颜色为 $a_{p_{tot}}$ 了。

这样二分的值域变为 $1$ ~ $3$，每个位置的查询次数上界变为 $2$，可以通过 Subtask 4 了。

# Subtask 5

二分做法 $10^4$ 的次数上界不足以直接通过 Subtask 5。

首先查询一次 $1$ ~ $n$ 求出序列的总颜色数 $tot$。

如果 $tot = n$，直接输出 $1$ ~ $n$ 即可。

如果 $tot = n - 1$，那么一定有两个位置的颜色相同。

我们维护两个指针 $l$，$r$，初值为 $1$ 与 $n$。

当 $Query(1, r) = r - 1$ 时不断左移 $r$，

当 $Query(l, n) = n - l$ 时不断右移 $l$，

那么 $l - 1$ 与 $r + 1$ 显然就是两个重复颜色的位置。

# 参考代码

```cpp
#include <bits/stdc++.h>
#define ff fflush(stdout)
#define fop(i, l, r) for (int i = l; i <= r; ++i)
#define pof(i, r, l) for (int i = r; i >= l; --i)
#define edg(i, u) for (int i = head[u], v = to[i]; i; i = nxt[i], v = to[i])
typedef long long ll;
typedef unsigned long long ull;
#define int ll
const int inf = 0x3f3f3f3f;
using namespace std;

int read() {
    int x = 0; bool f = 0; char c;
    while (!isdigit(c = getchar())) if (c == '-') f = 1;
    do x = (x << 1) + (x << 3) + (c ^ 48); while (isdigit(c = getchar()));
    return f ? -x : x;
}

const int maxn = 1e3 + 4;

int col[maxn]; bool vis[maxn];

int query(int l, int r) { printf("? %lld %lld\n", l, r); ff; return read(); }

int TOT; int p[maxn], tot;

int get(int x) {
	tot = 0;
	pof(i, x - 1, 1) if (!vis[col[i]]) vis[col[i]] = 1, p[++tot] = i;
	pof(i, x - 1, 1) vis[col[i]] = 0;
	int l = 1, r = tot, res = -1;
	if (tot == TOT) r = tot - 1;
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (query(p[mid], x) == mid + 1) l = mid + 1;
		else r = mid - 1, res = mid;
	}
	if (res == -1 && tot == TOT) return col[p[tot]];
	if (res == -1) return ++tot;
	return col[p[res]];
}

signed main() {
	int T = read(), N = read(), Q = read();
	if (T <= 2) {
		fop(i, 2, N) if (query(i - 1, i) == 2) vis[i] = 1;
		int tot = 1;
		fop(i, 1, N) { if (vis[i]) ++tot; col[i] = tot; }
	}
	else {
		TOT = query(1, N);
		if (TOT == N) fop(i, 1, N) col[i] = i;
		else if (TOT == N - 1) {
			int l = 1, r = N;
			while (query(1, r) == r - 1) --r;
			while (query(l, N) == N - l) ++l;
			++r, --l;
			fop(i, 1, N) if (i == r) col[i] = l; else col[i] = i;
		}
		else {
			col[1] = 1;
			fop(i, 2, N) col[i] = get(i);
		}
	}
	printf("! "); fop(i, 1, N) printf("%lld ", col[i]); ff;
}
```


---

## 作者：zhouyuhang (赞：0)

数据分治。

不少于 $N-1$ 种颜色 / 同种颜色编号连续：思博题。

无特殊限制：从前往后扫，假设进行到第 $i$ 个球时，已经求出前 $i-1$ 个球的情况。记 $f(l,r)$ 为 $[l,r]$ 内颜色数，$g(x)=[f(x,i-1)=f(x,i)]$。注意到 $g$ 取值具有单调性，$f(x,i-1)$ 可以自己算，$f(x,i)$ 可以询问交互库得到，二分即可在不超过 $\log N!\le \frac{1}{2}N\log N$ 次询问解决。

不超过 $4$ 种颜色：维护每种颜色当前最靠右的位置，将其排序后并对此二分。精细实现可以使询问数不超过 $2N$。

不懂可以看代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1005;

int Query(int l, int r) {
	int x;
	cout << "? " << l << ' ' << r << endl;
	cin >> x;
	return x;
}

int T;
int n, Q;
int col[N], totc = 0; 

bool vis[N];

int myque(int l, int r) { // l,r < i 时不必浪费一次询问，自己计算即可
	memset(vis, false, sizeof vis);
	int cnt = 0;
	for (int i = l; i <= r; ++i) if (!vis[col[i]]) vis[col[i]] = 1, ++cnt;
	return cnt;
}

int pos[5], tmp[5];

int main() {
	cin >> T;
	cin >> n >> Q;
	if (T == 2) {
		col[1] = ++totc;
		for (int i = 2; i <= n; ++i) col[i] = Query(i - 1, i) > 1 ? ++totc : col[i - 1];
	}
	else if (T == 3 || T == 4) {
		pos[col[1] = ++totc] = 1;
		for (int i = 2; i <= n; ++i) {
			for (int j = 1; j <= totc; ++j) tmp[j] = pos[j];
			sort(tmp + 1, tmp + totc + 1);
			if (totc == 1) col[i] = (Query(1, i) == 1 ? col[1] : ++totc);
			else if (totc == 2) col[i] = (Query(tmp[2], i) == 1 ? col[tmp[2]] : Query(tmp[1], i) == 2 ? col[tmp[1]] : ++totc);
			else if (totc == 3) col[i] = (Query(tmp[2], i) == 2 ? (Query(tmp[3], i) == 1 ? col[tmp[3]] : col[tmp[2]]) : (Query(tmp[1], i) == 3 ? col[tmp[1]] : ++totc));
			else col[i] = (Query(tmp[3], i) == 2 ? Query(tmp[4], i) == 1 ? col[tmp[4]] : col[tmp[3]] : Query(tmp[2], i) == 3 ? col[tmp[2]] : col[tmp[1]]); // 这里是手动二分以保证询问次数，长但很好想清楚
			pos[col[i]] = i;
		}
	}
	else if (T == 5) {
		bool flag = false;
		for (int i = 1; i <= n; ++i) {
			if (!flag && Query(1, i) < i) {
				flag = true;
				col[i] = col[1];
				for (int j = i - 1; j > 1; --j) {
					if (Query(j, i) < i - j + 1) {
						col[i] = col[j];
						break;
					}
				}
			} else col[i] = ++totc;
		}
	} else {
		for (int i = 1; i <= n; ++i) {
			int l = 1, r = i - 1, p = 0;
			while (l <= r) {
				int mid = (l + r) / 2;
				if (Query(mid, i) == myque(mid, i - 1)) l = mid + 1, p = mid;
				else r = mid - 1;
			}
			if (!p) col[i] = ++totc;
			else col[i] = col[p];
		}
	}
	cout << "! ";
	for (int i = 1; i <= n; ++i)
		if (i < n) cout << col[i] << ' ';
		else cout << col[i];
	cout << endl;
	return 0;
}
```
```

---

## 作者：Celtic (赞：0)

从前往后枚举 $i$，维护一下当前每个颜色最后出现的位置。按最后出现的位置排序，这样就可以知道某个位置和 $i-1$ 之间的颜色数。

考虑二分哪个位置和他颜色相同，当二分到 $j$ 这个颜色时如果他最后的出现位置到 $i-1$ 的颜色数和到 $i$ 的颜色数相同就可以说明 $i$ 的颜色按出现位置排序后在 $j$ 之后。如果是新颜色就是在所有颜色之前，判一下就行。

复杂度 $O(n^2\log n)$，询问次数 $O(n\log n)$。
```cpp
#include<bits/stdc++.h>
#define N 2005
using namespace std;
typedef int ll;
typedef double db;
ll pre[N];
pair<ll,ll>c[N];
inline ll query(ll l,ll r)
{
	cout<<"? "<<l<<" "<<r<<endl;
	ll res;
	cin>>res;
	return res;
}
vector<int> getColor(int t,int n,int q)
{
	ll val=query(1,n);
	vector<int>res;
	if(val>=n-1)
	{
		if(val==n)
		{
			for(int i=1;i<=n;i++)
				res.push_back(i);
			return res;
		}
		res.resize(n);
		for(int i=1;i<=n;i++)
		{
			if(query(1,i)<i)
			{
				for(int j=i;j;j--)
				{
					if(query(j,i)<i-j+1)
					{
						ll tot=0;
						for(int k=1;k<=n;k++)
						{
							if(k==i||k==j)
								continue;
							res[k-1]=++tot;
						}
						tot++;
						res[i-1]=res[j-1]=tot;
						return res;
					}
				}
			}
		}
	}
	else if(q==2000&&val>4)
	{
		ll las=0;
		ll tot=0;
		for(int i=1;i<=n;i++)
		{
			ll tmp=query(1,i);
			if(tmp==las)
				res.push_back(res.back());
			else
				res.push_back(++tot);
			las=tmp;
		}
		return res;
	}
	for(int i=1;i<=val;i++)
		pre[i]=0;
	ll tot=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=tot;j++)
			c[j]=make_pair(pre[j],j);
		sort(c+1,c+tot+1);
		ll l=1,r=tot,mid;
		while(l<r)
		{
			mid=l+r>>1;
			if((l+r)&1)
				mid++;
			if(query(c[mid].first,i)==tot-mid+1)
				l=mid;
			else
				r=mid-1;
		}
		if(l==1)
		{
			if(tot<val)
			{
				if(query(1,i)>tot)
				{
					tot++;
					pre[tot]=i;
					res.push_back(tot);
					continue;
				}
			}
		}
		res.push_back(c[l].second);
		pre[c[l].second]=i;
	}
	return res;
}
int main()
{
	ll t,n,q;
	cin>>t>>n>>q;
	vector<int>ans=getColor(t,n,q);
	cout<<"! ";
	for(auto x:ans)
		cout<<x<<" ";
	cout<<endl;
	exit(0);
}
```

---

## 作者：yukimianyan (赞：0)

## problem
交互库有一个长为 $n$ 的颜色序列，你可以询问区间 $[l,r]$ 中有多少种颜色，最后还原交互库手中的序列，只需要保持相对顺序不变。$n\leq 10^3$，最多询问次数 $Q=2000$ 或 $Q=10^4$。

## solution
令 $C$ 为 $[1,n]$ 的颜色种类数，一开始就 $query(1,n)$ 一次。

### $C=1,C=n$：$Q=O(1)$
？

### 相同颜色连续：$Q=O(n)$
做一个类似于去重的工作，把相邻两个颜色相同的（$query(i-1,i)=1$）合并成同一种颜色。因为相同颜色连续，所以不需要考虑其它，这样就能通过 $T\leq 2$ 的测试点。

### $C=3$：$Q=O(n)$
考虑先去重，去掉相邻的相同颜色。对于连续的 $a,b,c$ 的颜色块，如果
- $query(a,c)=1$，这可能吗？
- $query(a,c)=2$，可以推出 $a$ 的颜色和 $c$ 的颜色相同。
- $query(a,c)=3$，这三个颜色互不相同，假设我们已经知道 $a,b$ 的颜色，那么 $c$ 就是异于它们的第三种颜色。实现时暴力找出 $[1,b]$ 中有什么颜色，最后去掉 $a,b$，剩下的就是 $c$ 的颜色（如果没有说明 $c$ 是新颜色）。

这样就能通过 $T=3$ 的测试点。

### $C=n-1$：$Q=O(n)$
因为 $C=n-1$，所以一定存在一对 $i,j$ 使得这两个下标的颜色相同。

考虑一个包含了 $[i,j]$ 的区间，这一段区间里一定有 $len-1$ 种颜色。那么令 $l=1,r=n$，让 $l$ 一直往右扫，$r$ 一直往左扫，什么时候 $query(l,r)=r-l+1$，那么就找到了 $i,j$。这样就通过了 $T=5$ 的测试点

### 通解：$Q=O(n\log n)$
考虑一遍扫过去，用 $[1,i-1]$ 的颜色求出 $i$ 的颜色。

对于 $i$，假设我们有一个编号 $k$：
- 若 $query(k,i)=query(k,i-1)$，说明 $i$ 的颜色**一定**是 $[k,i-1]$ 中的其中一种；
- 若 $query(k,i)=query(k,i-1)+1$，说明 $i$ 的颜色**不**是 $[k,i-1]$ 中的其中一种，它可能是 $[1,k-1]$ 的其中一种，或者是一种不同于 $[1,i-1]$ 的全新的颜色。

发现 $query(k,i)$ 有单调性，试图二分 $k\in[1,i-1]$，于是你解决了 $T=6$ 和 $T=7$ 的测试点。

### $Q=O(n\log C)$ 及小优化
动态维护一个 $pre_c$ 表示颜色为 $c$ 的最大的编号，这样，$query(k,i-1)$ 就等同于有多少个 $pre_c$ 落在 $[k,i-1]$ 中。把所有有意义的 $pre_c$ 的值拉出来排序（容易发现只有 $O(C)$ 个），对着排序的 $pre$ 二分，那么就能通过 $T=3$ 的测试点。注意到因为 $n\leq 10^3$，所以排序部分直接写 $O(n^2+n\cdot C \log C))$ 的**时间复杂度**也能过。

还不能通过 $T=4$ 的测试点，因为这样每个颜色需要询问 $3$ 次，需要优化。这个优化很简单：如果 $\color{red}{C}=4$（而不是 $T=4$），当前有意义的 $pre$ **恰**有 $C$ 个，那么不需要特判 $i$ 是新颜色的情况，这是不可能的，询问次数降为 $2$ 次（若 $pre$ 有 $3$ 个那么只需要询问 $2$ 次）。于是可以通过 $T=4$ 的测试点。

## code
实现时可以用并查集。
```cpp
#include <set>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
template<int N> struct dsu{
	int fa[N+10],siz[N+10],cnt;
	dsu(int n=N):cnt(n){for(int i=1;i<=n;i++) fa[i]=i,siz[i]=1;}
	int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
	void merge(int x,int y){
		if(x=find(x),y=find(y),x!=y){
			if(siz[x]<siz[y]) swap(x,y);
			cnt--,siz[x]+=siz[y],fa[y]=x;
		}
	}
};
int n,T,f[1010][1010],last[1010],p[1010];
dsu<1010> s;
int query(int l,int r){
	if(l>r) swap(l,r);
	if(f[l][r]==-1){
		printf("? %d %d\n",l,r);
		fflush(stdout);
		scanf("%d",&f[l][r]);
	}
	return f[l][r];
}
int flower(){
	int cnt=0;
	p[++cnt]=1;
	for(int i=2;i<=n;i++){
		if(query(p[cnt],i)==1) s.merge(p[cnt],i);
		else p[++cnt]=i;
	}
	return cnt;
}
int main(){
	memset(f,-1,sizeof f);
	scanf("%d%d%*d",&T,&n);
	if(T==1||T==2) flower();
	else if(query(1,n)==n-1){
		int L=1,R=n;
		while(query(n,L)==n-L) L++;
		while(query(R,1)==R-1) R--;
		s.merge(L-1,R+1);
	}else if(query(1,n)==3){
	    int cnt=flower();
	    if(query(p[1],p[3])==2) s.merge(p[1],p[3]);
		for(int i=4;i<=cnt;i++){
			if(query(p[i-2],p[i])==2) s.merge(p[i-2],p[i]);
			else{
				set<int> fs;
				for(int j=1;j<i;j++) fs.insert(s.find(p[j]));
				fs.erase(s.find(p[i-1]));
				fs.erase(s.find(p[i-2]));
				if(!fs.empty()) s.merge(*fs.begin(),p[i]);
			}
		}
	}else if(query(1,n)!=n){
		for(int i=1;i<=n;i++){
			int cnt=0;
			for(int j=1;j<=1000;j++) if(last[j]) p[++cnt]=last[j];
			sort(p+1,p+cnt+1);
			int L=1,R=cnt;
			while(L<R){
				int mid=(L+R+1)>>1;
				if(query(p[mid],i)==cnt-mid+1) L=mid;
				else R=mid-1;
			}
			if(query(1,n)==cnt||!cnt||query(p[L],i)==cnt-L+1) s.merge(p[L],i);
			last[s.find(i)]=i;
		}
	}
	printf("! ");
	for(int i=1;i<=n;i++) printf("%d%c",s.find(i)," \n"[i==n]);
	fflush(stdout);
	return 0;
}
/*
1213
*/
```


---

