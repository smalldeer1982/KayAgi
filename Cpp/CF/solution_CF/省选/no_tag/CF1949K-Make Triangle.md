# Make Triangle

## 题目描述

已知 $n$ 个数 $\{x_i\}$，求任意一种把它们分成数量分别为 $n_a, n_b, n_c$ （保证其和为 $n$）的 $3$ 份的方案，满足各份中的数的和 $s_a, s_b, s_c$ 可以构成三角形的三边（不允许三个顶点共线）。

## 样例 #1

### 输入

```
4
6 2 2 2
1 1 1 1 1 1
5 3 1 1
1 1 1 1 1
6 2 2 2
1 1 1 1 1 3
8 1 2 5
16 1 1 1 1 1 1 12```

### 输出

```
YES
1 1 
1 1 
1 1 
NO
NO
YES
16 
12 1 
1 1 1 1 1```

# 题解

## 作者：OccDreamer (赞：3)

首先容易将问题转化为划分为三个大小分别为 $n_a,n_b,n_c$ 的集合使得总和均小于 $\frac{\sum a_i}{2}$。

为了方便，我们记 $S=\frac{\sum a_i}{2}$，默认 $a_i \leq a_{i+1}$，$n_a \leq \min\{n_b,n_c\}$。

有两个显然无解的条件：

1. $\sum_{i=1}^{n_a-1} a_i+a_n \geq S$，此时你最大值所在的集合总和一定 $\geq S$。
2. $\sum_{i=1}^{\max\{n_b,n_c\}} a_i \geq S$，此时你元素最多的集合总和一定 $\geq S$。  

接下来我们考虑将 $a_1,a_2\dots a_{n_a-1},a_n$ 放在集合 $\text A$ 中，剩下的元素随意。

如果 $S_B<S$ 且 $S_C <S$ 那么已经找到了一组解。

否则假设 $S_B \geq S$，此时显然可以任意 **交换**  $\text A$、$\text C$ 之间的元素。

如果我们交换 $\text B$ 和 $\text C$ 中的一个元素，那么不可能在交换完之后 $S_B <S$ 且 $S_C \geq S$。

证明如下：

因为 $S_B \geq S$，$a_n$ 在集合 $\text A$ 中，所以 $S_C \leq S-a_n$，交换一个元素最坏情况是换进来 $a_n$，换出去 $1$，也就是说 $S_C$ 最多增加 $a_n-1$，所以 $S'_C \leq S-1$。

也就是说我们也可以任意交换 $\text B$、$\text C$ 之间的元素。

那么实际上，$\text B$ 内部元素可以和外部元素任意交换（不交换 $a_n$）。

只要 $S_B < S$ 那么就说明我们找到了一组解。

因为 $\sum_{i=1}^{n_b} a_i < S$，所以肯定可以通过不断调整使得 $S_B < S$。

那么我们从小到大枚举 $a_i$，将 $a_i$ 换到集合 $\text B$ 即可。

时间复杂度 $O(n \log n)$。

---

## 作者：weitianyi (赞：1)

这是一道很有意思的构造题，思路来源于官方题解。

首先，我们考虑能组成三角形的条件：对于任意一个集合 $A$，都应该满足 $sum_A < \frac{sum}{2}$。

那么，我们可以考虑一些不合法的条件, 我们设 $S=\frac{sum}{2}$, 假设 $n_a \leq n_b \leq n_c$ 并且 $x_i$ 递增：

* $\sum \limits_{i=1} ^ {n_c} x_i \geq S$，考虑最大的集合，如果这个集合取最小值都不行，一定无解。
* $(\sum \limits_{i=1} ^ {n_a - 1} x_i) + x_n\geq S$，考虑最大的元素，如果这个元素所在集合取最小都不行，一定无解。

我们以此为启发，想一想更为一般的情况。

考虑当前有三个集合分别剩下 $l_a,l_b,l_c$ 个位置可以放，当前的和为 $sum_a, sum_b, sum_c$，那么我们可以考虑如果有界必须满足的条件有哪些，可以仿照上面, 设剩下的元素 $x'_i$ 从小到大排列：

1. 对于任意集合 $u$，都有 $sum_u + \sum\limits_{i = 1}^{l_u} x'_i < S$。
2. 存在一个集合 $u$，并且该集合不为满，都有 $sum_u + \sum\limits_{i = 1}^{l_u - 1} x'_i + x'_{n'} < S$。

因此，我们只要证明这种判定方法是充分的即可。

我们可以假设 $x'_{n'}$ 放的集合是 $a$, 剩下的元素随便放在 $b$ 和 $c$ 中，如果 $b$ 和 $c$ 都满足条件,那么就万事大吉了，如果不对，那就交换调整。

我们假设 $b$ 中的和 $\geq S$，那么 $a$ 和 $c$ 中的元素一定可以随意交换，因为 $a$ 和 $c$ 中的元素和都 $<S$。

我们考虑 $b$ 和 $c$ 中的元素，我们考虑 $c$ 会不会因此不满足条件。容易得到 $x'_{n'}$ 在 $a$，所以 $c$ 的和不会超过 $S-x'_{n'}$, 考虑到换入的最大是 $x'_{n'}$，换出的最小是 $1$，那么换完后 $c$ 的和不会超过 $S - 1$。因此，只要 $b$ 不符合要求，那么 $b$ 和 $c$ 中的元素可以任意互换。

那么我们继续考虑 $a$ 和 $b$ 中的元素，只要 $b$ 不符合条件，那么交换 $a、c$ 和 $b、c$ 就一定能行。综上所述，因为满足第一条性质，那么一定可以通过交换使得原本不符合要求的 $b$ 变得符合要求。

因此，我们可以使用一种极其简单的构造方法，将 $x_i$ 从大到小依次加入，那么如果满足上面的两条判定，直接插入一个合法的集合即可，可以参考如下通过代码：[MyCode](https://codeforces.com/contest/1949/submission/293459734)。

---

## 作者：yizhiming (赞：0)

补充说明一下另一篇题解，免得有人和我一样误入歧途。

[Link](https://www.luogu.com.cn/problem/CF1949K)

## 题目大意

给定 $n,na,nb,nc$，以及 $n$ 个数 $a_i$，求将 $a$ 划分成三个集合大小分别为 $na,nb,nc$，使得三个集合的 $a_i$ 和可以凑成三角形。

$3\leq n \leq2\times 10^5$,$1\leq na,nb,nc\leq n-2$,$na+nb+nc=n$。

## 题目分析

假设你已经看过另一篇文章了，已经知道无解情况只有两种，我们现在将集合称为 $A,B,C$，对应的和为 $SA,SB,SC$，则只有 $SB\geq S$，其中 $S = \lceil \frac{\sum a_i}{2}\rceil$，钦定 $a_i$ 从小到大排序。

我们需要调整使得 $SB<S$，已知在钦定 $na\leq nb \leq nc$ 的情况下，$a_n+\sum_{i=1}^{na-1}a_i<S$ 且 $\sum_{i=1}^{nc}a_i<S$，是能够调整的充要条件。

换句话说我们每次选择一个数加入集合中之后，就会变成子问题，这个子问题有解只需要划分后满足那两个条件即可。

所以我们只需要将原序列排序，预处理前缀和 $s_i$，从大到小将 $i$ 划分进入集合，判断一下当前集合，假设为 $A$，在加入了 $i$ 之后是否合法，即 $SA+s_{na-|A|}<S$ 即可，而此时对于 $B,C$ 集合，其约束是没有变化的。

也即只要 $A$ 满足这个条件，其划分出来的子问题一定有解，我们每次只需要任选一个有解的集合，将 $i$ 加进去即可，一旦某一刻时刻无解，那么报告全局无解即可。

容易发现对于第二个约束条件，若满足，一定会导致在某一时刻使子问题不合法。所以每次划分子问题足以解决两种约束。

## Code

实现起来不难，就不放了（实际上是我没写）。

给大家看看我误入歧途，没有注意到可以直接任选，而选择调整的代码，还挂了三发。

```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
#include <vector>
#define int long long
using namespace std;
int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N = 2e5+5;
int na,nb,nc,n;
int a[N],sum,bel[N];
struct Heap{
	struct aa{
		int x,id;
		bool operator<(const aa&u)const{
			if(x==u.x){
				return id<u.id;
			}
			return x<u.x;
		}
	};
	priority_queue<aa>q1,q2;
	void init(){
		while(!q1.empty()){
			q1.pop();
		}
		while(!q2.empty()){
			q2.pop();
		}
//		q1.clear();q2.clear();
	}
	void ins(int x,int k){
		q1.push((aa){a[x]*k,x});
	}
	void del(int x,int k){
		q2.push((aa){a[x]*k,x});
	}
	void clear(){
		while(!q2.empty()){
			if(q1.top().id==q2.top().id){
				q1.pop();q2.pop();
			}else{
				break;
			}
		}
	}
	int Top(){
		clear();
		if(!q1.empty()){
			return q1.top().id;
		}else{
			return 0;
		}
	}
}H1,H2,H3;//A中最小值，B中最小值，C中最大值 
int sum1,sum2,sum3;
int id[5];
void print(){
	cout<<"YES\n";
	for(int j=1;j<=3;j++){
		for(int i=1;i<=n;i++){
			if(id[bel[i]]==j){
				cout<<a[i]<<" ";
			}
		}
		cout<<"\n";
	}
}
int inf = 2e9;
void upd(int u,int v){//交换u,v，保证要么AB要么BC 
	int x = bel[u],y = bel[v];
	if(x==1&&y==2){
		sum1-=a[u];sum1+=a[v];
		sum2-=a[v];sum2+=a[u];
		H1.del(u,-1);H2.del(v,-1);
		H2.ins(u,-1);H1.ins(v,-1);
		swap(bel[u],bel[v]);
	}else{
		sum2-=a[u];sum2+=a[v];
		sum3-=a[v];sum3+=a[u];
		H2.del(u,-1);H3.del(v,1);
		H3.ins(u,1);H2.ins(v,-1);
		swap(bel[u],bel[v]);
	}
}
void init(){
	n = read();na = read();nb = read();nc = read();
	id[1]=1;id[2]=2;id[3]=3;
	if(na>nb){
		swap(na,nb);
		swap(id[1],id[2]);
	}
	if(na>nc){
		swap(na,nc);
		swap(id[1],id[3]);
	}
	if(nb>nc){
		swap(nb,nc);
		swap(id[2],id[3]);
	}
//	cout<<na<<" "<<id[1]<<" "<<nb<<" "<<id[2]<<" "<<nc<<" "<<id[3]<<"\n";
	sum = 0;
	for(int i=1;i<=n;i++){
		a[i] = read();
		sum+=a[i];
	}
	sum = (sum/2)+(sum&1);
	sort(a+1,a+1+n);
	int pre = 0;
	for(int i=1;i<na;i++){
		pre+=a[i];
	}
	pre+=a[n];
	if(pre>=sum){
		cout<<"NO\n";
		return;
	}
	pre-=a[n];
	for(int i=na;i<=nc;i++){
		pre+=a[i];
	}
	if(pre>=sum){
		cout<<"NO\n";
		return;
	}
	sum1 = sum2 = sum3 = 0;
	for(int i=1;i<na;i++){
		bel[i] = 1;
		sum1+=a[i];
	}
	sum1+=a[n];
	bel[n] = 1;
	for(int i=na;i<=na+nb-1;i++){
		bel[i] = 2;
		sum2+=a[i];
	}
	for(int i=na+nb;i<n;i++){
		bel[i] = 3;
		sum3+=a[i];
	}
	if(sum3<sum){
		print();
		return;
	}
	a[0] = inf;
	H1.init();H2.init();H3.init();
	for(int i=1;i<=n;i++){
		if(bel[i]==1){
			H1.ins(i,-1);
		}else if(bel[i]==2){
			H2.ins(i,-1);
		}else{
			H3.ins(i,1);
		}
	}
	while(sum3>=sum){
		int u,v,x;
		u = H1.Top();
		v = H2.Top();
		x = H3.Top();
		if(a[u]<=a[v]){
			upd(v,x);
			if(sum3<sum){
				break;
			}
			upd(u,x);
			upd(u,v);
		}else{
			upd(v,x);
		}
	}
	print();
}
signed main(){
//	freopen("data.txt","r",stdin);
//	freopen("me.txt","w",stdout);
	int T = read();
	while(T--){
//		cout<<T<<"\n";
		init();
	}
	return 0;
}
/*
三条边能够组成三角形等价成三边都小于和的一半 

先从无解情况想

钦定na<=nb<=nc,a_i<=a_{i+1}，令 sum = sum(i[1,n])a_i/2 上取整 

第一种无解是 sum{i[1,na-1]}a_i +a_n >=sum，这种情况下，选到了最大值的集合一定不合法

第二种是 sum{i[1,nc]}a_i >=sum，这种集合C一定不合法

若两种都不满足，不妨令A集合为[1,na-1]+[n,n]，此时<sum

令B和C为剩余元素随意组合起来，为了方便，不妨让剩下的也是按从小到大先放入B在放入C，这样就保证了此时sumc>=sumb

假设此时sumc<sum 那么直接输出即可，否则考虑调整 

首先由于sumc>=sum，所以AB集合之间互换一定不会使得其中一个>=sum，此时AB可以任意互换

再来考虑BC集合，由于sumc>=sum 然后由于a_n在 A 中，所以sumb<=sum-a_n

由于a_i<=a_n，所以此时C集合与B集合交换的增量最大为a_n-1， 此时交换一定满足 sumb<=sum-1即sumb<sum

这也就是说在sumc>=sum时，BC进行一次交换，要么两者都合法，要么不改变

而由于AB,BC可互换，所以 AC 可互换，我们可以贪心每次将AB中最小的与C交换，且一旦某次操作后sumc<sum那么直接输出

然后由于 sum[1,nc]a_i <sum，所以一定能够调整出来一个合法解 

草糖丸了，输出格式写错了 
*/
```

---

