# [JOIST 2024] 有趣的家庭菜园 5 / Growing Vegetables is Fun 5

## 题目描述

Bitaro，一个多年来一直热衷于园艺的人，计划从今年春天开始种植一种名为 Bita-radish 的植物。 

Bitaro 已经准备好了 $2N$ 个 Bita-radish 幼苗。这些幼苗从 $1$ 到 $2N$ 编号，Bitaro 计划按照这个顺序进行栽培。第 $i$ 个幼苗（$1 \leq i \leq 2N$）的大小为 $A_i$。Bitaro 希望每个幼苗都能得到足够的阳光，因此幼苗的大小满足以下条件：

- $A_1 \leq A_2 \leq \cdots \leq A_N \leq A_{N+1}$. 
- $A_{N+1} \geq A_{N+2} \geq \cdots \geq A_{2N-1} \geq A_{2N} \geq A_1$. 

注意，幼苗 $1$ 最小，幼苗 $N+1$ 最大。

Bitaro 还准备了 $N$ 个红色花盆和 $N$ 个蓝色花盆，每个花盆也有一定大小。第 $j$ 个（$1 \leq j \leq N$）红色花盆的大小是 $B_j$，第 $k$ 个（$1 \leq k \leq N$）蓝色花盆的大小是 $C_k$。Bitaro 在这总共 $2N$ 个花盆中各种植一株 Bita-radish 幼苗，并按某种顺序排列花盆，使幼苗按 $1,2,...,2N$ 顺序依次放入花盆中。

考虑到外观，这 $2N$ 个花盆必须被安排在一个美观的顺序中。这里，美观的顺序意味着花盆的排列使得存在连续的 $N$ 个花盆颜色相同。更确切地说，一个花盆排列被称为是美观的，当且仅当存在一个整数 $l$，满足 $1 \leq l \leq N+1$，使得种植了幼苗 $l, l+1, \ldots, l+N-1$ 的花盆颜色都相同。

当尺寸为 $y$ 的幼苗种植在尺寸为 $x$ 的花盆中时，该对的栽培难度是绝对值 $|x-y|$。Bitaro 种植 Bita-radish 的工作量是 $2N$ 对花盆和幼苗中的**最大**栽培难度。编写一个程序，给定 Bita-radish 幼苗和花盆的信息，找到种植幼苗的最小可能 Bitaro 工作量值，并且花盆需要按美观的顺序排列。

## 说明/提示

#### 样例解释 1

在这个样例输入中，Bitaro 可以通过以下方式种植幼苗来实现工作量为 $2$：

- 将幼苗 $1$ 种植在第一个红色花盆中。这对的栽培难度是 $|2 - 1| = 1$。
- 将幼苗 $2$ 种植在第二个蓝色花盆中。这对的栽培难度是 $|3 - 2| = 1$。
- 将幼苗 $3$ 种植在第一个蓝色花盆中。这对的栽培难度是 $|4 - 6| = 2$。
- 将幼苗 $4$ 种植在第二个红色花盆中。这对的栽培难度是 $|5 - 3| = 2$。

种植了幼苗 $2$ 和 $3$ 的花盆的颜色都是蓝色，因此花盆是按美观顺序排列的。

当种植幼苗以使花盆按美观顺序排列时，无法实现工作量小于 $2$。因此，输出为 $2$。

这个样例输入满足所有子任务的约束条件。


#### 样例解释 2

这个样例输入满足子任务 $2,3,4,5$ 的约束条件。

#### 样例解释 3

这个样例输入满足子任务 $2,3,5$ 的约束条件。

### 约束条件

- $1 \leq N \leq 300,000$.
- $1 \leq A_i \leq 10^9$ （$1 \leq i \leq 2N$）.
- $1 \leq B_j \leq 10^9$ （$1 \leq j \leq N$）.
- $1 \leq C_k \leq 10^9$ （$1 \leq k \leq N$）.
- $A_1 \leq A_2 \leq \cdots \leq A_N \leq A_{N+1}$.
- $A_{N+1} \geq A_{N+2} \geq \cdots \geq A_{2N-1} \geq A_{2N} \geq A_1$.
- 所有输入值都是整数。

### 子任务

1. (4 分) $N \leq 5$。
2. (5 分) $N \leq 10$。
3. (21 分) $N \leq 2,000$。
4. (37 分) 所有的 $A_i$ 的值都是不同的。另外，满足 $A_N < A_{2N}$。
5. (33 分) 没有额外的约束条件。

## 样例 #1

### 输入

```
2
1 2 6 3
2 5
4 3```

### 输出

```
2```

## 样例 #2

### 输入

```
9
1 2 3 4 5 6 7 8 9 18 17 16 15 14 13 12 11 10
2 7 4 1 7 6 4 10 6
6 8 9 3 7 1 9 5 4
```

### 输出

```
8```

## 样例 #3

### 输入

```
7
13 16 18 18 21 22 22 23 23 21 19 17 15 14
14 14 20 19 22 17 25
24 15 18 25 24 19 11```

### 输出

```
3```

# 题解

## 作者：C1942huangjiaxu (赞：2)

我们将 $2N$ 个花盆顺时针排成一个环，题目的要求就是 $2$ 种颜色的花盆各是一个半圆。

考虑如果已经确定了花盆颜色，怎么安排最优。

那么问题就是，给定 $2$ 个长度为 $n$ 的序列 $a,b$，要求两两配对，使得配对的 $2$ 个数的差值最大值最小。

可以发现，将 $a,b$ 排序后，**从小到大依次配对一定是最优的**。

证明考虑，假如我们已经知道了最优答案为 $k$，要求一组配对方案。

那么这相当于一个二分图匹配问题，注意到排序后每个 $a$  可以匹配的都是 $b$ 的**一段区间**，并且这些区间的**左右端点都是单调递增的**，因此从小到大依次匹配是最优的。

上述证明过程启示我们考虑二分答案，判断是否存在可行解。

注意到 $B$ 和 $C$ 是等价判定，所以我们相当于要判断 $2N$ 个半圆中，每个半圆是否可行。

枚举半圆似乎并不好解决，我们考虑**枚举圆环上的点，判断经过每个点的 $N$ 个半圆中哪些是可行的**。

首先用双指针求出每个 $A_i$ 在 $B$ 上可以匹配的区间 $[l_i,r_i]$，那么根据上述匹配方式，**半圆可行当且仅当半圆中小于等于 $A_i$ 的数的个数在 $l_i$ 和 $r_i$ 之间**，注意这里我们要将 $A$ 中相等的数钦定大小关系。

然后题目还保证了一个关键性质，那就是 $A$ 是一个前一半增后一半减的序列。

那么我们按照顺时针的顺序考虑经过一个 $A_i$ 的所有半圆中小等 $A_i$ 的数的个数，通过一些推导或者打表观察可以发现，把其写为函数的形式，**一定是一段水平线段和一段 $45$ 度的斜线段拼接在一起的形式**，那么合法的半圆的也是**圆环上的一段区间**。

那么我们用差分的方式对一段区间的半圆做标记，可行的半圆就是被所有点都标记的半圆。

上述过程都可以在线性的复杂度内解决，加上二分的复杂度，时间复杂度 $O(n\log V)$。

参考代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=6e5+5;
int n,m,a[N],b[N],c[N],lim,ans[N],Ans[N],vl[N],vr[N],p1[N],p2[N];
void upd(int o,int l,int r){
	l=(l+o)%m,r=(r+o)%m;
	if(l>r)++ans[0],--ans[r+1],++ans[l];
	else ++ans[l],--ans[r+1];
}
void solve(int *v){
	for(int i=0,j=1;i<n;++i){
		while(j<=n&&v[j]<a[i]&&a[i]-v[j]>lim)++j;
		vl[i]=j;
	}
	for(int i=n-1,j=n;~i;--i){
		while(j&&v[j]>a[i]&&v[j]-a[i]>lim)--j;
		vr[i]=j;
	}
	for(int i=m-1,j=1;i>=n;--i){
		while(j<=n&&v[j]<a[i]&&a[i]-v[j]>lim)++j;
		vl[i]=j;
	}
	for(int i=n,j=n;i<m;++i){
		while(j&&v[j]>a[i]&&v[j]-a[i]>lim)--j;
		vr[i]=j;
	}
	for(int i=0;i<m;++i)ans[i]=0;
	for(int i=0;i<n;++i)if(vl[i]<=vr[i]){
		int ct=i+1+m-max(p1[i],i+n+1);
		if(ct<vl[i])continue;
		if(p1[i]>=i+n+1){
			int dt=p1[i]-(i+n+1);
			if(ct-(n-dt)>vr[i])continue;
			if(ct<=vr[i])upd(i+n+1,0,min(n-1,dt+ct-vl[i]));
			else upd(i+n+1,dt+ct-vr[i],min(n-1,dt+ct-vl[i]));
		}else{
			int dt=i+n+1-p1[i];
			if(ct-(n-dt)>vr[i])continue;
			if(ct-(n-dt)>=vl[i])upd(i+n+1,max(0,ct-vr[i]),n-1);
			else upd(i+n+1,max(0,ct-vr[i]),ct-vl[i]);
		}
	}
	for(int i=n;i<m;++i)if(vl[i]<=vr[i]){
		int ct=1+max(0,p2[i]-(i-n));
		if(ct>vr[i])continue;
		if(p2[i]>=i-n){
			int dt=p2[i]-(i-n);
			if(ct+(n-dt)<vl[i])continue;
			if(ct>=vl[i])upd(i-n+1,0,min(n-1,dt+vr[i]-ct));
			else upd(i-n+1,dt+vl[i]-ct,min(n-1,dt+vr[i]-ct));
		}else{
			int dt=i-n-p2[i];
			if(ct+(n-dt)<vl[i])continue;
			if(ct+(n-dt)<=vr[i])upd(i-n+1,max(0,vl[i]-ct),n-1);
			else upd(i-n+1,max(0,vl[i]-ct),vr[i]-ct);
		}
	}
	for(int i=1;i<m;++i)ans[i]+=ans[i-1];
}
bool check(int mid){
	lim=mid;
	solve(b);
	for(int i=0;i<m;++i)Ans[i]=ans[i];
	solve(c);
	for(int i=0;i<m;++i)if(Ans[i]+ans[(i+n)%m]==m)return true;
	return false;
}
int main(){
	scanf("%d",&n);
	m=2*n;
	for(int i=0;i<m;++i)scanf("%d",&a[i]);
	for(int i=1;i<=n;++i)scanf("%d",&b[i]);
	for(int i=1;i<=n;++i)scanf("%d",&c[i]);
	for(int i=0,j=m-1;i<n;++i){
		while(a[j]<a[i])p2[j--]=i-1;
		p1[i]=j+1;
		if(i==n-1)while(j>=n)p2[j--]=i;
	}
	sort(b+1,b+n+1),sort(c+1,c+n+1);
	int l=0,r=1e9;
	while(l<r){
		int mid=l+r>>1;
		if(check(mid))r=mid;
		else l=mid+1;
	}
	printf("%d\n",l);
	return 0;
}
```

---

## 作者：DeepSkyCore (赞：0)

怎么其他题解的复杂度都是 $O(n \log V)$，这里记录一个 $O(n \log n)$ 的做法。

首先考虑暴力怎么做，那就是直接枚举红蓝色花盆的位置，然后分别求最小代价。这里观察到直接对 $a, b$ 都排序之后，从小到大逐个匹配就是最优的，证明也比较经典，这里不多赘述。

接下来考虑优化这个过程。

考虑特殊性质的测试点，我们考察红色花盆区间在从 $[1, n]$ 每次向右移动一格，最后移动到 $[n + 1, 2n]$ 的代价。

这相当于动态维护一个有序数列 $S = (s_1, s_2, \dots, s_n)$ 满足 $s_i \le s_{i + 1}$，然后计算 $\max(|s_i - b_i|)$。把绝对值拆开，相当于计算 $\max(\max(s_i - b_i), \max(b_i - s_i))$。

向右移动一格相当于什么？从 $S$ 删除 $a_i$ 然后插入 $a_{i + n}$。注意到在特殊性质下有 $a_i \le a_{i + n}$，因此在这个过程中，**有序数列 $S$ 的每个元素分别都是不降的**。这意味着 $\max(s_i - b_i)$ 是不降的，且 $\max(b_i - s_i)$ 是不升的。

考察了红色花盆从 $[1, n]$ 到 $[n + 1, 2n]$ 的代价，我们再对应考虑蓝色花盆从 $[n + 1, 2n]$ 每次向右（循环）移动一格到 $[1, n]$ 的代价。性质是类似的，不过这次是插入的比删除的要小，因此大小关系是完全反过来的。

我们记红色花盆的两个 $\max$ 分别为 $mx_0, mn_0$，而蓝色的两个为 $mx_1, mn_1$，那么某个放置位置的代价应该表示为 $\max(mx_0, mn_0, mx_1, mn_1)$。根据之前得到的性质，$mx_0, mn_1$ 单调不降，而 $mn_0, mx_1$ 单调不升。那么，以放置位置作为自变量，考虑这四个值的函数，它们应该形如：

![](https://cdn.luogu.com.cn/upload/image_hosting/wdnpv64u.png)

注意四个变量的大小关系不一定形如上图，但是最终答案函数（紫色）一定是一个先减后增的函数。

那么就可以进行二分。每次考虑一个位置，求出对应四个变量的值，就可以确定答案的最低点在二分点的左侧还是右侧。

当前只考虑了红色对应 $[1, n]$ 到 $[n + 1, 2n]$ 的情况，对于剩下的情况也是高度相似的。

考虑了特殊性质，我们再来考虑没有特殊限制的测试点。注意到上述算法中，利用特殊限制的点只有：每次插入都不是插入一个最小的（或者最大的）值，这保证了有序数列 $s$ 每个元素分别的单调性。

事实上，我们尝试从 $[1, n]$ 往右平移，直到遇到第一个插入了最小值的区间 $[i, i + n - 1]$。那么我们从 $[i + n, i - 1]$ 开始向右移动 $n$ 步，就能保证插入的不是最小值。另一边的最大值也是同理。

因此我们变换一下起点就可以套用特殊性质的算法。

考虑复杂度：二分是对于序列下标二分的；而对于计算贡献，$b, c$ 数组可以预排序；对于每次截取 $a$ 的一个子区间排序，由于 $a$ 可以分解为两个有序数组，因此排序可以用归并做到 $O(n)$。总时间复杂度 $O(n \log n)$。

应该是目前最优解。[参考代码](https://loj.ac/s/2350639)。

---

## 作者：cwfxlh (赞：0)

## [P10435 [JOISC 2024] 有趣的家庭菜园 5 (Day2)](https://www.luogu.com.cn/problem/P10435)   

首先二分答案。    

不妨令颜色连续的是 B 类花盆，枚举第一个 B 类花盆的位置 $x$，分别将 $[x,x+n-1]$ 的花拿出来匹配 B 类花盆，剩余的匹配 C 类花盆。根据 exchange argument，花盆大小越大，匹配的花越大。于是将其排序，然后看能否匹配即可判定。    

以上做法复杂度过高，考虑优化判定的过程。将 B 类花盆和 C 类花盆排序，对于一朵花 $a_i$ 而言，能与它匹配的 B 类花盆是一段区间 $[l,r]$（C 类花盆同理），如果 $i\in[x,x+n-1]$，$i$ 被选作 B 类花盆，那么大小小于 $a_i$ 的花的数量要在 $[l-1,r-1]$ 内，发现加上这个限制后，合法的 $x$ 是一段区间。C 类花盆的限制也是类似的。   

那么我们枚举 $x$，$[x,x+n-1]$ 内的花是 B 类限制，其余的是 C 类限制，需要查询若干区间内区间的交，分别维护 $l$ 的最大值与 $r$ 的最小值。记得交换 BC 再做一遍。复杂度 $O(n\log V)$。   

代码：   

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[600003],b[300003],c[300003],lft,rgt,mid,ans;
class ST_Table{
	public:
		int val[600003],fff;
		int pre1[600003],pre2[600003],suf1[600003],suf2[600003];
		void _init(int _fff){
			fff=_fff;
			for(int i=1;i<=n*2;i++)val[i]=-10000000;
			return;
		}
		void modify(int wz,int v){
			val[wz]=max(val[wz],v*fff);
			return;
		}
		void build(){
			pre1[0]=pre2[n]=suf1[n+1]=suf2[2*n+1]=-10000000;
			for(int i=1;i<=n;i++)pre1[i]=max(pre1[i-1],val[i]);
			for(int i=n;i;i--)suf1[i]=max(suf1[i+1],val[i]);
			for(int i=n+1;i<=2*n;i++)pre2[i]=max(pre2[i-1],val[i]);
			for(int i=2*n;i>n;i--)suf2[i]=max(suf2[i+1],val[i]);
			return;
		}
		int Query(int l,int r){
			if(l>r)return fff*-10000000;
			if(l==1){
				if(r<=n)return fff*pre1[r];
				return fff*max(pre2[r],pre1[n]);
			}
			if(r==2*n){
				if(l>n)return fff*suf2[l];
				return fff*max(suf1[l],suf2[n+1]);
			}
			return fff*max(suf1[l],pre2[r]);
		}
}Bl,Br,Cl,Cr;
int sl,sr;
void upd(int l,int r){
	l=max(l,1);r=min(r,n+1);
	if(l>r)return;
	if(sl>sr){sl=l;sr=r;return;}
	sl=min(sl,l);sr=max(sr,r);
	return;
}
bool chk(){
	Bl._init(1);Br._init(-1);Cl._init(1);Cr._init(-1);
	int posB1=1,posB2=0,posC1=1,posC2=0;
	for(int i=1,j=2*n+1;i<=n;i++){
		while(j-1>n&&a[j-1]<a[i])j--;
		while(posB1<=n&&b[posB1]<a[i]-mid)posB1++;
		while(posC1<=n&&c[posC1]<a[i]-mid)posC1++;
		while(posB2+1<=n&&b[posB2+1]<=a[i]+mid)posB2++;
		while(posC2+1<=n&&c[posC2+1]<=a[i]+mid)posC2++;
		
		pair<int,int>p=make_pair(posB1,posB2);
		sl=1;sr=0;
		if(i+(2*n-j+1)>=p.first&&i+(2*n-j+1)<=p.second)upd(i+1,j-n);
		if(i<=p.second)upd(max(n-(p.second-i)+1,max(i+1,j-n+1)),n-(p.first-i)+1);
		if(p.first>p.second){sl=1;sr=0;}
		Bl.modify(i,sl);Br.modify(i,sr);
		
		p=make_pair(posC1,posC2);
		sl=1;sr=0;
		if(n-(j-i-1)>=p.first&&n-(j-i-1)<=p.second)upd(j-n+1,i);
		upd(i-p.second+1,min(i-p.first+1,min(j-n,i)));
		if(p.first>p.second){sl=1;sr=0;}
		Cl.modify(i,sl);Cr.modify(i,sr);
	}
	posB1=1,posB2=0,posC1=1,posC2=0;
	for(int i=2*n,j=0;i>n;i--){
		while(j+1<=n&&a[j+1]<=a[i])j++;
		while(posB1<=n&&b[posB1]<a[i]-mid)posB1++;
		while(posC1<=n&&c[posC1]<a[i]-mid)posC1++;
		while(posB2+1<=n&&b[posB2+1]<=a[i]+mid)posB2++;
		while(posC2+1<=n&&c[posC2+1]<=a[i]+mid)posC2++;
		
		pair<int,int>p=make_pair(posB1,posB2);
		sl=1;sr=0;
		if((2*n-i+1)+j>=p.first&&(2*n-i+1)+j<=p.second)upd(j+1,i-n);
		if(2*n-i+1<=p.second)upd((p.first-(2*n-i+1))+1,min(p.second-(2*n-i+1)+1,min(j,i-n)));
		if(p.first>p.second){sl=1;sr=0;}
		Bl.modify(i,sl);Br.modify(i,sr);
		
		p=make_pair(posC1,posC2);
		sl=1;sr=0;
		if(n-(i-j-1)>=p.first&&n-(i-j-1)<=p.second)upd(i-n+1,j);
		upd(max((i+p.first-1-n+1),max(i-n+1,j+1)),(i+p.second-1-n+1));
		if(p.first>p.second){sl=1;sr=0;}
		Cl.modify(i,sl);Cr.modify(i,sr);
	}
	Bl.build();Br.build();Cl.build();Cr.build();
	for(int i=1;i<=n+1;i++){
		if(Bl.Query(1,i-1)>i||Bl.Query(i+n,n*2)>i)continue;
		if(Cl.Query(i,i+n-1)>i||Cr.Query(i,i+n-1)<i)continue;
		if(Br.Query(1,i-1)<i||Br.Query(i+n,n*2)<i)continue;
		return true;
	}
	return false;
}
int sol(){
	lft=0;
	rgt=1000000000;
	while(lft<rgt){
		mid=((lft+rgt)/2);
		if(chk())rgt=mid;
		else lft=mid+1;
	}
	return lft;
}
int main(){
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n*2;i++)cin>>a[i];
	for(int i=1;i<=n;i++)cin>>b[i];
	for(int i=1;i<=n;i++)cin>>c[i];
	sort(b+1,b+n+1);sort(c+1,c+n+1);
	b[0]=c[0]=-10000000;
	ans=sol();
	for(int i=1;i<=n;i++)swap(b[i],c[i]);
	ans=min(ans,sol());
	cout<<ans;
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/P10435)

**题目大意**

> 给定序列 $a_1\sim a_{2n}$，满足 $a_1\sim a_{n+1}$ 递增，$a_{n+1}\sim a_{2n}$ 递减。
>
> 把每个元素匹配到 $b_1\sim b_n$ 或 $c_1\sim c_n$ 上，要求存在一个长度为 $n$ 的子区间上每个元素都匹配到 $b$ 上或都匹配到 $c$ 上。
>
> 最小化每对匹配的元素差的最大值。
>
> 数据范围：$n\le 3\times 10^5$。

**思路分析**

先考虑暴力，枚举哪个区间填 $b/c$，然后把两个要匹配的序列都升序排列，对应位置的元素匹配即可。

先二分答案，把 $a$ 放到环上，对于每个长度为 $n$ 的弧，判定这些元素能否和 $b$ 匹配，计算出所有和 $b,c$ 可匹配的弧即可判定答案。

那么每个 $a_i$ 可以匹配的元素是一段区间 $b[l_i,r_i]$，一个过 $i$ 的弧 $[j,j+n)$ 合法当且仅当 $\le a_i$ 的元素个数 $\in[l_i,r_i]$（需要给相等元素钦定顺序）。

注意到 $\le a_i$ 的元素一定是原序列的一段前缀和一段后缀，那么 $[j,j+n)$ 和这个范围的交集大小不难直接写出。

这是一份暴力检验的代码：[Submission Link](https://loj.ac/s/2270519)

注意到对于每个 $i$，合法的 $j$ 都是 $\mathcal O(1)$ 个区间，分类讨论求得这些区间即可。

时间复杂度 $\mathcal O(n\log V)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=6e5+5,inf=1e9;
int n,a[MAXN],ord[MAXN],d[MAXN],L[MAXN],R[MAXN];
bool in(int x,int l,int r) { return l<=x&&x<=r; } 
void solve(int lim,int *b,int *f) {
	for(int o=1,p=1,q=1;o<=2*n;++o) {
		int i=ord[o];
		while(p<=n&&b[p]<a[i]-lim) ++p;
		while(q<=n&&b[q]<=a[i]+lim) ++q;
		L[i]=p,R[i]=q-1;
	}
	auto add=[&](int l,int r) { if(l<=r) ++f[l],--f[r+1]; };
	for(int i=1,x;i<=n;++i) if(L[i]<=R[i]) {
		x=min(i,d[i]-n);
		if(in(n+i+1-d[i],L[i],R[i])) add(x+1,i);
		add(max(1,i-R[i]+1),min(x,i-L[i]+1));
		x=max(d[i],n+i+1);
		if(in(2*n+1-d[i]+i,L[i],R[i])) add(n+i+1,x-1);
		add(max(x,2*n+1+i-R[i]),min(2*n,2*n+1+i-L[i]));
	}
	for(int i=n+1,x;i<=2*n;++i) if(L[i]<=R[i]) {
		x=min(d[i]+n+1,i);
		add(max(n+1,L[i]-n+i),min(x,R[i]-n+i));
		if(in(2*n-i+1+d[i],L[i],R[i])) add(x+1,i);
		x=max(d[i]+1,i-n+1);
		if(in(n-i+d[i]+1,L[i],R[i])) add(i-n+1,x-1);
		add(max(x,L[i]-n+i),min(n,R[i]-n+i));
	}
}
int b[MAXN],c[MAXN],f[MAXN],g[MAXN];
bool chk(int lim) {
	memset(f,0,sizeof(f));
	memset(g,0,sizeof(g));
	solve(lim,b,f),solve(lim,c,g);
	for(int i=1;i<=2*n;++i) f[i]+=f[i-1],g[i]+=g[i-1];
	for(int i=1;i<=n;++i) {
		if(f[i]==n&&g[i+n]==n) return true;
		if(g[i]==n&&f[i+n]==n) return true;
	}
	return false;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=2*n;++i) cin>>a[i],ord[i]=i;
	for(int i=1;i<=n;++i) cin>>b[i];
	for(int i=1;i<=n;++i) cin>>c[i];
	sort(ord+1,ord+2*n+1,[&](int x,int y){ return a[x]<a[y]; });
	sort(b+1,b+n+1),sort(c+1,c+n+1);
	for(int i=1,j=2*n;i<=n;++i) {
		while(a[j]<a[i]) d[j--]=i-1;
		d[i]=j+1;
		if(i==n) while(j>n) d[j--]=i;
	}
	int l=0,r=inf,p=inf;
	while(l<=r) {
		int mid=(l+r)>>1;
		if(chk(mid)) p=mid,r=mid-1;
		else l=mid+1;
	}
	cout<<p<<"\n";
	return 0;
}
```

---

