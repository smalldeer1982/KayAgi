# [eJOI 2020] Exam (Day1)

## 题目描述

给定一个长度为 $N$ 的序列 $A_i$，你可以进行无数次下面这个操作：

- 选定一个大小不小于 $2$ 的区间，使得这个区间里的数等于这个区间里的最大值。

你需要用这些操作使得 $A_i=B_i$，求最多能使得多少数满足要求。

## 说明/提示

#### 样例 1 解释

可以选择对区间 $[1,2]$ 进行操作，最多能有 $2$ 个数满足要求。

#### 样例 2 解释

$A_2$ 或 $A_3$ 能满足要求，但他们不能同时满足要求。

#### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 1（14 pts）：$N \le 10$。
- Subtask 2（12 pts）：$N \le 10^5$，所有 $B_i$ 都相等。
- Subtask 3（13 pts）：$N \le 5000$，$A_i$ 为严格单调递增序列。
- Subtask 4（23 pts）：$N \le 10^5$，$A_i$ 两两不同。
- Subtask 5（16 pts）：$N \le 200$。
- Subtask 6（22 pts）：$N \le 5000$。

对于 $100\%$ 的数据：

- $2 \le N$。
- $1 \le A_i \le 10^9$。
- $1 \le B_i \le 10^9$。

#### 说明

翻译自 [eJOI 2020 Day1 C Exam](https://ejoi2020.ge/static/assets/Day1/Problems/Exam.pdf)。

## 样例 #1

### 输入

```
3
1 2 3
2 2 2```

### 输出

```
2```

## 样例 #2

### 输入

```
4
10 1 9 1
10 9 10 9```

### 输出

```
3```

# 题解

## 作者：Lice (赞：16)

转载于本人 [cnblogs](https://www.cnblogs.com/-Wallace-/p/13955789.html)。

### Description

$n$ 个正整数排成一列，每个位置 $i$ 有一个初始值 $A_i$ 以及目标值 $B_i$。

一次操作可以选定一个区间 $[l, r]$，并将区间内所有数赋值为 $\max_{i\in[l, r]} A_i$。

你可以进行任意次操作，每次操作基于上次操作的结果。

求结果若干次操作后，使得与操作后的值与目标值相同的位置数最大化。

### Hint

$1\le n\le 10^5, 1\le A_i, B_i\le 10^9$。

原题数据过于奇妙于是就直接取最大值反正能做。~~官方那个三合一做法真的 /no~~

### Solution

首先，我们不难求出对于每个 $i\in[1, n]$，该位置可以向左侧取到目标值 $B_i = A_j$ 的第一个位置 $L_i = j(\le i)$ 或者不存在，同理对于右侧 $R_i$ 我们也这么干。

为什么我们只取第一个位置呢？显然可能存在多个可取的位置，不过注意到我们对位置 $i$ 向 $j$ 进行一次取值操作之后，会对中间的这些值造成影响。我们希望成功的取值操作尽可能多，那么影响的范围自然是越少越好了。

观察到一个性质，对于一个 $i$，如果 $L_i$ （$R_i$ 同理不再赘述）存在，说明 $j\in[L_i +1, i]$ 这个区间的所有 $A_j$ 的值都小于 $A_{L_i}$。那么一次操作下去，所有这个区间内的值都会失效，如果有像“从 $A_j$ 取值到 $k(<i)$”这样的操作那必然不能同时与当前这个同时执行。

于是我们尝试大力将题目转化：有两排点，每排 $n$ 个，对于第一排每个点 $i$ 向第二排的第 $L_i, R_i$ 个点分别连一条边。若选取一个第一排的点 $i$，那么需要至少选中连接 $i$ 的两条或一条边的一条边（没有边则不能选）。要求选中的边两两不相交（除端点外），求最多选取第三个第一排的点。

发现当 $A_i$ 互不相同时，每个点最多连出去 $1$ 条边，这就是个经典的 LIS 问题，不过稍加拓展就可以得到本题的正解。

还是令 $f(i, j)$ 为处理到第一排前 $i$ 个点，第二排涉及到的点编号最大的为 $j$，可以选出第一排点个数的最大值。那么转移比较简单：
$$
f(i, L_i) \leftarrow \max_{j \le L_i} \{f(i-1, j)\} +1, \qquad f(i, R_i) \leftarrow \max_{j \le R_i} \{f(i-1, j)\} +1
$$
不难发现把 $i$ 滚掉之后实质上就是一个前缀 $\max$，于是使用树状数组优化为 $O(n\log n)$。

### Code

```cpp
/*
 * Author : _Wallace_
 * Source : https://www.cnblogs.com/-Wallace-/
 * Problem : eJOI2020 Exam
 */
#include <algorithm>
#include <cstdio>
#include <set>
#include <vector>

using namespace std;
const int N = 1e5 + 5;

int n;
int A[N], B[N];
int L[N], R[N];

int tr[N]; // 树状数组求前缀 max
inline void upd(int p, int v) {
  for (; p <= n; p += p & -p) tr[p] = max(tr[p], v);
}
inline int get(int p) {
  int v = 0;
  for (; p; p -= p & -p) v = max(tr[p], v);
  return v;
}

signed main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) scanf("%d", A + i);
  for (int i = 1; i <= n; i++) scanf("%d", B + i);

  vector<pair<int, int> > tmp(n * 2);
  set<int> rec({0, n + 1});
  for (int i = 1; i <= n; i++) tmp[i - 1] = {A[i], i};
  for (int i = 1; i <= n; i++) tmp[i + n - 1] = {B[i], -i};
  sort(tmp.begin(), tmp.end(), greater<pair<int, int> >());
  for (auto it : tmp) {
    if (it.second < 0) {
      int l = *rec.lower_bound(-it.second);
      if (A[l] == it.first) R[-it.second] = l;
      int r = *--rec.upper_bound(-it.second);
      if (A[r] == it.first) L[-it.second] = r;
    } else rec.insert(it.second);
  } // 求 L & R

  for (int i = 1; i <= n; i++) { // 同步更新
    int l = get(L[i]), r = get(R[i]);
    if (L[i]) upd(L[i], l + 1);
    if (R[i]) upd(R[i], r + 1);
  }

  printf("%d\n", get(n));
  return 0;
}
```


---

## 作者：红火恍惚cxy (赞：6)

# P7169 [eJOI2020 Day1] Exam 题解  
前面大佬的题解已经写的很详细啦，我这里就再说一下对于 $L_i$ 和 $R_i$ 的处理和后面 dp 的一些证明。  
*******  
## 对于 $L_i$ 和 $R_i$ 的处理：  
因本人实力太弱这部分想了很久，所以在这里整理一下。  
首先看到数据范围，$N \leq 10^5$，因此暴力 $N^2$ 处理很明显是会超时的，我们需要更快的处理方式。  

我们可以把 $A_i$ 和 $B_i$ 都加入一个结构体，保存他们值的大小，位置，以及它是 A 数组中的值还是 B 数组中的值。按照**大小优先**，之后 $A$ **数组中的值优先**的顺序排序。  

之后建立一个 set，按照位置排序。  
依次扫过排好序的数组。  
* 若为 A 数组中的值，将其加入 set。  
* 若为 B 数组中的值，在 set 中进行二分，找到位置第一个比它大的数和第一个比它小的数。如果这个数和它相等，则加入 $L_i$ 或 $R_i$。如果比它大，则为找不到。  

因为我们是从大到小排序后再依次加入 set 因此 set 中的值只有可能大于等于当前查找的值。  

这样就可以实现 $O(n \log n)$ 处理 $L_i$ 和 $R_i$。  

放一下这块处理的代码：  
```c++
int n,m;
int a[100005],b[100005],l[100005],r[100005];
struct qwq{
	int num,ver,how;
}s[200005];

inline bool cmp(qwq x,qwq y){
	if(x.num>y.num) return 1;
	if(x.num==y.num&&x.how<y.how) return 1;
	return 0;
}
int main(){
    for(int i=1;i<=n;++i){
		scanf("%d",&a[i]);
		s[i].num=a[i];
		s[i].ver=i;
		s[i].how=1;
	}
	for(int i=1;i<=n;++i){
		scanf("%d",&b[i]);
		s[i+n].num=b[i];
		s[i+n].ver=i;
		s[i+n].how=2;
	}
	sort(s+1,s+2*n+1,cmp);
	set<pair<int,int> >se;
	for(int i=1;i<=2*n;++i){
		if(s[i].how==1){
			se.insert(mp(s[i].ver,s[i].num));
		}
		else{
			auto p=se.lower_bound(mp(s[i].ver,s[i].num));
			if(p==se.end()) r[s[i].ver]=-1;
			else{
				if(p->second==s[i].num) r[s[i].ver]=p->first;
				else r[s[i].ver]=-1;
			}
			if(p!=se.begin()&&(p==se.end()||p->first>s[i].ver)) p--;
			if(p!=se.end()&&p->second==s[i].num) l[s[i].ver]=p->first;
			else l[s[i].ver]=-1;
		}//这里一定注意指针不要越界，
	}
}
```  

## 对于 dp 的证明：  
为什么要求连线两两不相交？  
![](https://cdn.luogu.com.cn/upload/image_hosting/ef6oz11x.png)  
假设两条边分别从 $B_i$ 连到 $A_j$，从 $B_x$ 连到 $A_y$，其中 $i \leq y \leq j \leq x,A_j \ne A_y$。  
那么我们需要同时要求 $A_j$ 是 $i$ 到 $j$ 中的最大值，而 $A_y$ 是 $x$ 到 $y$ 中的最大值，这是不可能同时成立的。  

只要不相交就能满足要求吗？  
![](https://cdn.luogu.com.cn/upload/image_hosting/w1c6iv31.png)  
假设两条边分别从 $B_i$ 连到 $A_j$，从 $B_x$ 连到 $A_y$，其中 $i \leq x \leq j \leq y,A_j \leq A_y$。  
那么我们可以先将 $i$ 到 $j$ 处理，再对 $x$ 到 $y$ 处理，这样可以满足要求。  

---

## 作者：wYYSZLwSSY (赞：4)

模拟考的一道题，原题面有些难理解，不过洛谷上这个简要题意还行。
## 题面
给定一个长度为 $N$ 的序列 $A_i$，你可以进行无数次下面这个操作：

选定一个大小不小于 $2$ 的区间，这个区间里的数等于这个区间里的最大值。

你需要用这些操作使得 $A_i=B_i$，求最多能使得多少数满足要求。
### 数据范围与提示

Subtask 1（14 pts）：$N\le10$。  
Subtask 2（12 pts）：$N\le10^5$，所有 $B_i$ 都相等。  
Subtask 3（13 pts）：$N\le5000$，$A_i$ 为严格单调递增序列。  
Subtask 4（23 pts）：$N\le10^5$，$A_i$ 两两不同。  
Subtask 5（16 pts）：$N\le200$。  
Subtask 6（22 pts）：$N\le5000$。  

对于 $100\%$ 的数据：

$2 \le N$。     
$1 \le A_i,B_i \le 10^9$。


## 题解
### Part I：我会暴力！
期望得分 14 pts。
### Part II：我会 Bi 都相等的时候！
这种情况比较简单。

直观来讲，就是在 $A$ 数组的找到与 $B$ 相等的数，然后往开拓展，拓展到不能拓展**（就是有比他大的数，毕竟数字只能变大不能变小）**。

具体操作，可以找到比 $B$ 大的数字，把 $A$ 分开段，然后找其中有没有 $A_i$ 等于 $B$。

期望得分 26 pts。
### Part III：我会 Ai 两两不同的时候。
当 $A_i$ 两两不同时，想要变成 $B_i$，必须或多或少与一个且唯一一个 $A_i$“扯上关系”。

这么一来，我们发现用 $B_i$ 找 $A_j$ 会比 $A_i$ 找 $B_i$ 方便很多很多。

这就是正难则反，把题面转化成了有两排点，每排 $n$ 个点，$B_i$ 连向 $A_j$ 一条边，然后不能交叉。

为什么说不能交叉，如果交叉了会怎么样？  

举个例子：

如图所示：
![](https://cdn.luogu.com.cn/upload/image_hosting/6dphcbzl.png)

现在，蓝线和绿线交叉了，这是不可行的，不论顺序。

首先明确，这样连边有一个性质，蓝线中间的部分 $A$ 值一定严格小于箭头指向的点的 $A$ 值，在图中就是棕色部分（不含端点）的 $A$ 值严格小于蓝箭头指向的那个点，红色同理。

所以，只要选择了棕线，绿线就不能满足。

这是包含的情况，单纯交叉不包含也一样。

这里要明确一下交叉的概念。

交叉必须是“真正意义上”的交叉，仅仅划过的区间有交叉但画出图没有交住是不算的，或者端点交在一起也不算。

比如：
```plain
4 2 0 0
1 4 4 2
```
这组数据。

显然，连出来线长这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/2k4dnzsq.png)

红线和蓝线就属于刚才说到的前者，而绿线与红线就是后者。

显然，这三条线都可以满足。选择区间 $[2,4][1,3]$ 即可。

蓝线和红线可以同时满足原因在于，虽然红线和蓝线值域相交，但蓝线的“起点”在红线之外，所以蓝线在红线之前满足即可。

绿线和红线可以满足原因显然，不需多言。

明确这些性质后，我们再来想想这个部分分。

不难发现，如果以线段 $B$ 端排序，答案就是 $A$ 值的 LIS。

期望得分：68 pts。

### Part IV：我会 Sub56!
其实有了前面那个部分，这个部分就不那么难了。

可以想一想，那些 $A$ 是可以被 $B_i$ 指向的。

显然，我们可以求出对于每个 $i∈[1,n]$，该位置可以向左侧取到目标值 $B_i=A_j$ 且 $A_{[i,j]}$ 都不大于 $B_i$ 的第一个位置 $L_i=j(\le i)$ 或者不存在，同理对于右侧 $R_i$ 我们也这么干。这是唯二两个有意义的点。

为什么这么说呢？显然，如果找到一个“更远”的地方，就会毁坏更多的点。

把 $A$，$B$ 翻转一下。由此，我们把问题转化，有两排点，每排 $n$ 个，对于第一排每个点 $i$ 向第二排的第 $L_i,R_i$ 个点分别连一条边。若选取一个第一排的点 $i$，那么需要至少选中连接 $i$ 的两条或一条边的一条边（没有边则不能选）。要求选中的边两两不相交（除端点外），求最多选取多少个第一排的点。

思考 DP。

考虑状态，令 $f_{i,j}$ 表示必须选第一行的 $i$ 和第二行 $j$，且考虑前 $i$ 行和前 $j$ 行可以选取最多第一排的点。

考虑转移，显然，可以被更新的点是 $f_{i,L_i}$ 和 $f_{i,R_i}$。

于是有  
$$f_{i,L_i}= \max^{L_i}_{j=0}\max^{i-1}_{k=0}f_{k,j}+1$$ 
$$f_{i,R_i}= \max^{R_i}_{j=0}\max^{i-1}_{k=0}f_{k,j}+1$$

然后我们发现，其实有性质：处理 $i$ 以及之后时，保存 $f_{k,j}$ 最大值即可。      

所以赋值 $f_{i,j}=f_{i-1,j}$，是正确的。

这样，就可以消掉 $k$。

数据分治后期望得分：100 pts。
### Part V：我会正解和更正解！
~~实在想不到写什么了起了个“更正解”的名字~~

~~其实就是可以解决更大数据范围~~

思考整体的算力瓶颈，主要是两个，一是 DP，二是求解 $L$ 和 $R$。

先想 DP 优化。

显然得压掉一维，~~数组都是两维复杂度显然下不去啊~~。

然后我们发现，赋值运算就可以省去。只需求出 $\max$ 然后更新。

可以用线段树，不过显然树状数组好用。

再想求解 $L$ 和 $R$。

再次转换问题，求解 $L$ 和 $R$，实质是左右找，找到一个大于等于 $B_i$ 的 $A$，如果这个等于了，就找到了，反之没有。

因此，我们可以把 $A$ 和 $B$ 都压到一个数组中，然后按第一关键字值，从大到小排序，第二关键字 $A$ 或 $B$，把 $A$ 排在 $B$ 前。

然后遍历该数组。

当看到一个数是 $A$ 时，把 $i$ 压进一个 $\operatorname{set}$ 里面。

当看到一个数是 $B$ 时，在 $\operatorname{set}$ 了找 $i$ 值，找到第一个大于等于它的和第一个大于它的前面一个数。

复杂度：$O(n \log n)$。

期望得分：100+pts。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define lowbit(x) (x&(-x))
using namespace std;
int n;
int b[100005];
int c[100005];
int d[100005];
int tree[100005];
int lft[100005];//就是题解中的 L 数组
int rght[100005];//就是题解中的 R 数组
struct P{int x,i;}a[200005];
inline bool cmp(P x,P y){
	if(x.x ==y.x ){
		if(x.i <= n and y.i >n)return 1;
		if(x.i >n)return x.i <y.i ;
		return x.i>y.i;
	}
	return x.x>y.x;
}
int check(int x){
	int maxx=-1;
	for(;x;x-=lowbit(x))maxx=max(maxx,tree[x]);
	return maxx;
}
void change(int x,int y){
	for(;x<=n;x+=lowbit(x))tree[x]=max(tree[x],y);
}
set<int>st;
signed main(){
	ios::sync_with_stdio(0);
	cin>>n;
	for(int i=1;i<=n;++i){
		cin>>a[i].x;
		a[i].i =i;
		c[i]=a[i].x ;
	}
	for(int i=1;i<=n;++i){
		cin>>a[i+n].x ;
		a[i+n].i =i+n;
	}
	sort(a+1,a+n+n+1,cmp);
	st.insert(2*n+1);//防止超界
	st.insert(0);
	for(int i=1;i<=2*n;++i){
		if(a[i].i >n){
			int l=*st.lower_bound(a[i].i -n);
			int r=*(--st.upper_bound(a[i].i -n));
			if(c[l]==a[i].x )lft[a[i].i -n]=l;
			if(c[r]==a[i].x )rght[a[i].i -n]=r;
		}else {
			st.insert(a[i].i );
		}
	}
	for(int i=1;i<=n;++i){
		int l=check(lft[i]),r=check(rght[i]);
		if(lft[i])change(lft[i],l+1);
		if(rght[i])change(rght[i],r+1);
	}
	cout<<check(n)<<'\n';
	return 0;
}
```

---

## 作者：xs_siqi (赞：2)

赛时调了两个小时，终于和暴力全拍上了。但是暴力假了。

线段树 + st 表。

首先我们不难列出一个比较暴力的 dp。设 $f_{i,0}$ 表示目前找到向左第一个 $b_j$ 等于当前的 $a_i$，并将这段区间覆盖为 $a_i$ 时所得的最大价值。$f_{i,1}$ 向右同理。

不妨记 $L_i$ 为从 $i$ 走第一个宇自己相同的位置，$R_i$ 向右同理。

然后大力转移。对于 $f_{i,0}$，我们可以从 $f_{j,0}$ 转移而来，即 $f_{i,0}=f{j,0}+1$。前提是 $L_j\leq L_i$。这是为什么呢？为什么两个区间不能覆盖呢？考虑以下一个情况：


```
a:1 1 3 5 6  ---> 3 3 3 5 6 ---> 3 5 5 5 6
b:3 5 5 5 6       3 5 5 5 6      3 5 5 5 6   
```

在以上这个 $a_i$ 中，我们可以先让 $[1,3]$ 一个区间互相抄袭，然后再让 $[2,4]$ 一个区间互相抄袭。

首先对于这个 $j$ 我知道了 $b_{L_j}=a_j$ 对吧。然后我已经把 $a_{L_j}$ 抄成 $a_j$ 这个值了，如果区间覆盖了，那么这个 $a_{L_j}$ 又变成其他值了，我直接亏麻了。

那为什么能交呢？因为对于 $[L_j,j]$ 这个区间，只有 $b_{L_j}=a_j$（因为 $L_j$ 是第一个对吧）。所以在这个区间内，那我一个都不会亏，无论如何都是赚的，无非是赚的多少的问题嘛。

类似地，$f_{i,0}$ 可以从 $f_{j,1}+1$ 转移而来，前提是 $R_j\leq L_i$。你发现，这个区间又突然没有交了才行！这是为什么？

你想啊，我知道了 $a_{R_j}=b_j$ 对吧，你看你直接把 $a_{R_j}$ 覆盖成别的了，亏爆了。傻逼。

然后对于 $f_{i,1}$ 的转移也是同理的。不多赘述了，直接放核心代码。

```cpp

for(int i=1;i<=n;i++){
	for(int j=i;j>=L[i];j--)
		if(a[j]>b[i]){L[i]=0;break;}
        /*
        这个地方要判断一下你这个区间里面有没有某个 a_j 比 b_i 大。
        因为如果中间有个 a_j 更大，那么我们所有人都会抄这个 a_j 了。
        那么 a_{L_i} 就不可能成为 b_j
        下面同理。
        */
	for(int j=i;j<=R[i];j++)
		if(a[j]>b[i]){R[i]=n+1;break;}
	if(R[i]!=n+1){
		for(int j=0;j<i;j++){
			f[i][1]=max(f[i][1],f[j][0]+1);
			if(R[j]<=R[i])f[i][1]=max(f[i][1],f[j][1]+1);
		}
	}
	if(L[i]){
		for(int j=0;j<i;j++){
			if(L[j]<=L[i])f[i][0]=max(f[i][0],f[j][0]+1);
			if(R[j]<=L[i])f[i][0]=max(f[i][0],f[j][1]+1);
		}
	}
}
```

然后怎么求 $L_i$ 和 $R_i$ 呢。直接记个桶记录上一次的位置即可。因为 $a_i,b_i$ 范围比较大，所以要离散化。

然后我们发现，问题主要是出在了判断 $L_i,R_i$ 上。我们考虑优化这两块地方。

首先，对于中间的 dp，$i$ 仅与 $j$ 有关，可以考虑简单的数据结构优化。不难想到可以直接用两棵权值线段树分别维护 $L$ 和 $R$，分别以 $L_i,R_i$ 为下标记录 $f_{i,0}$ 与 $f_{i,1}$ 即可。

剩下的事就是验证 $L_i$ 和 $R_i$ 了。若 $\max_{j=L_i}^i a_i> b_i$ 那么这个 $L_i$ 一定不满足。这个 $\max$ 可以考虑用 st 表维护。

然后就全部维护完了。时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define ls rt<<1
#define rs rt<<1|1
using namespace std;
const int maxn=1e5+5;
int n,m,tot,ans,L[maxn],R[maxn],a[maxn],b[maxn],stk[maxn],lst[maxn*2],c[maxn*2],f[maxn][2],t,st[maxn][18],trl0[maxn*8],trr1[maxn*8];
void rmq(){
	for(int i=1;i<=n;i++)st[i][0]=a[i];
	for(int j=1;j<=17;j++)
		for(int i=1;i<=n-(1<<j)+1;i++)
			st[i][j]=max(st[i][j-1],st[i+(1<<(j-1))][j-1]);
}
int qmax(int l,int r){
	int t=log2(r-l+1);
	return max(st[l][t],st[r-(1<<t)+1][t]);
}
void pushup(int *tr,int rt){tr[rt]=max(tr[ls],tr[rs]);}
void modify(int *tr,int rt,int l,int r,int ql,int qr,int x){
	if(ql<=l&&r<=qr){tr[rt]=x;return ;}
	int mid=l+r>>1;
	if(ql<=mid)modify(tr,ls,l,mid,ql,qr,x);
	if(qr>mid)modify(tr,rs,mid+1,r,ql,qr,x);
	pushup(tr,rt);
}
int query(int *tr,int rt,int l,int r,int ql,int qr){
	if(ql<=l&&r<=qr){return tr[rt];}
	int mid=l+r>>1,ans=0;
	if(ql<=mid)ans=query(tr,ls,l,mid,ql,qr);
	if(qr>mid)ans=max(ans,query(tr,rs,mid+1,r,ql,qr));
	return ans;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),c[++tot]=a[i];
	for(int i=1;i<=n;i++)scanf("%d",&b[i]),c[++tot]=b[i];
	sort(c+1,c+tot+1);
	int m=unique(c+1,c+tot+1)-c-1;
	for(int i=1;i<=n;i++)a[i]=lower_bound(c+1,c+m+1,a[i])-c;
	for(int i=1;i<=n;i++)b[i]=lower_bound(c+1,c+m+1,b[i])-c;
	
	for(int i=1;i<=n;i++){
		lst[a[i]]=i;
		L[i]=lst[b[i]];
	}
	for(int i=1;i<=m;i++)lst[i]=R[i]=n+1; 
	for(int i=n;i>=1;i--){
		lst[a[i]]=i;
		R[i]=lst[b[i]];
	}
	rmq();
	for(int i=1;i<=n;i++){
		if(qmax(L[i],i)>b[i])L[i]=0;
		if(qmax(i,R[i])>b[i])R[i]=n+1;
		if(R[i]!=n+1)
			f[i][1]=max(f[i][1],query(trl0,1,1,n,1,n)+1),
			f[i][1]=max(f[i][1],query(trr1,1,1,n,1,R[i])+1);
		if(L[i])
			f[i][0]=max(f[i][0],query(trl0,1,1,n,1,L[i])+1),
			f[i][0]=max(f[i][0],query(trr1,1,1,n,1,L[i])+1);
		if(L[i])
			modify(trl0,1,1,n,L[i],L[i],f[i][0]);
		if(R[i]!=n+1)
			modify(trr1,1,1,n,R[i],R[i],f[i][1]);
	}
	for(int i=1;i<=n;i++)ans=max(ans,max(f[i][0],f[i][1]));
	printf("%d\n",ans);
	return 0;
}
```




---

## 作者：djh0314 (赞：1)

[**传送门**](https://www.luogu.com.cn/problem/P7169)。

## 题意

有两个长度为 $N$ 的数列 $A_i$，$B_i$。可以对 $A$ 数组进行若干次操作，每次可以使 $A_i$ 到 $A_j$ 中的所有数变成期间的最大值，求最多能使多少个数满足要求。

## 分析

显然，要使我们的某一个 $A_x$ 变成 $B_x$，至少会包含 $A_{L_x}$ 或 $A_{R_x}$，$L_x$ 是 $x$ 左侧（包括自己）的与 $B_x$ 相等的第一个的下标，$R_x$ 是 $x$ 右侧（包括自己）的与 $B_x$ 相等的第一个的下标。

但是这还有一个条件，那就是 $L_x\sim i$ 之间没有大于 $B_x$ 的数字，$R_x$ 相似。

解决了 $L_x$ 与 $R_x$ 的计算，我们借用这两个数组来解决我们的答案。

形象化的，我们将某一组操作变成一条线段。由上方点 $i$ 连向下方 $L_i$ 或 $R_i$ 的一条边。     

并且线与线之间不能相交。

由此，我们可以定义一个数组，$f_{i,j}$ 表示上方到达 $i$ 点，下方到达 $j$ 点的最多条数。

可以得到转移式：$f_{i,j}= {\textstyle \max_{k=1}^{k\le j} f_{i-1,k}} +1$。

我们可以利用树状数组来解决。
## Code。
~~~
#include <bits/stdc++.h>
#include <vector>
//#define int long long
using namespace std;
const int N = 2e5+5;
inline int read() {
	int x;
	scanf("%d",&x);
	return x;
}
int n, m,a[N],b[N],num[N],L[N],R[N],st[N][20],lg[N];
inline void lsh() {
	int cnt=0;
	for(int i=1; i<=n; ++i) num[++cnt]=a[i];
	for(int i=1; i<=n; ++i) num[++cnt]=b[i];
	sort(num+1,num+cnt+1);
	cnt=unique(num+1,num+cnt+1)-num-1;
	for(int i=1; i<=n; ++i) a[i]=lower_bound(num+1,num+cnt+1,a[i])-num;
	for(int i=1; i<=n; ++i) b[i]=lower_bound(num+1,num+cnt+1,b[i])-num;
}

vector<int > pos[N];
struct Bit {
	int c[N+2];
	inline int lowbit(int x) {
		return x&-x;
	}

	inline void change(int x,int y) {
		for(int i=x; i<=N; i+=lowbit(i)) c[i]=max(c[i],y);
	}

	inline int query(int x) {
		int tot=0;
		for(int i=x; i; i-=lowbit(i)) tot=max(tot,c[i]);
		return tot;
	}
} bit;

inline int query(int l,int r) {
	return max(st[l][lg[r-l+1]],st[r-(1<<lg[r-l+1])+1][lg[r-l+1]]);
}

signed main() {
	n=read();
	for(int i=1; i<=n; ++i) a[i]=read();
	for(int i=1; i<=n; ++i) b[i]=read();
	lsh();
	for(int i=1; i<=n; ++i) st[i][0]=a[i];
	for(int i=2; i<N; ++i) lg[i]=lg[i/2]+1;
	for(int i=1; i<20; ++i) for(int j=1; j+(1<<i)-1<=n; ++j) st[j][i]=max(st[j][i-1],st[j+(1<<i-1)][i-1]);
	for(int i=1; i<=n; ++i) pos[a[i]].push_back(i);
	for(int i=1; i<=n; ++i) {
		if(b[i]<a[i]) continue;
		L[i]=upper_bound(pos[b[i]].begin(),pos[b[i]].end(),i)-pos[b[i]].begin()-1;
		if(L[i]>=0) L[i]=pos[b[i]][L[i]];
		else L[i]=0;
		if(L[i]&&query(L[i],i)>b[i]) L[i]=0;
		R[i]=lower_bound(pos[b[i]].begin(),pos[b[i]].end(),i)-pos[b[i]].begin();
		if(R[i]<pos[b[i]].size()) R[i]=pos[b[i]][R[i]];
		else R[i]=0;
		if(R[i]&&query(i,R[i])>b[i]) R[i]=0;
	}
	for(int i=1; i<=n; ++i) {
		int l=bit.query(L[i]),r=bit.query(R[i]);
		if(R[i]) bit.change(R[i],r+1);
		if(L[i]) bit.change(L[i],l+1);
	}
	cout<<bit.query(n);
	return 0;
}
~~~

---

## 作者：封禁用户 (赞：0)

### 题面
给定一个长度为 $N$ 的序列 $a_i$，你可以进行无数次下面这个操作：

- 选定一个大小不小于 $2$ 的区间，使得这个区间里的数等于这个区间里的最大值。

你需要用这些操作使得 $a_i=b_i$，求最多能使得多少数满足要求。

### 思路
我们要将 $a_i$ 变成 $b_i$，应该优先用 $a$ 内前后第一个 $a_{L_i}=a_{R_i}=b_i$ 且中间没有比 $b_i$ 大的值。因为这样在保证变化的情况下对整个对列影响最少，考虑的也不多，所以一定不劣。

于是将序列抽象成每一段染色接起来的玩意，不难想到 dp。

设 $f_{i,0/1}$ 指染了 $[L_i,i]/[i,R_i]$ 区间的色所能得到的最大贡献，转移就出来了：

$$f_{i,0}=\max(f_{j,0}+1)\ (L_j\leq L_i)$$

$$f_{i,0}=\max(f_{j,1}+1)\ (R_j\leq L_i)$$

第一个就是同向的两个合并，因为可以先染 $i$，所以只要不染掉 $L_j$ 就行。

第二个就是不能把 $R_j$ 染掉。

优化就是发现我们关于 $L_j$ 的加的都是 $f_{j,0}$，关于 $R_j$ 的加的都是 $f_{j,1}$，所以建两棵权值线段树维护最大值，就优化到 $O(n\log n)$ 的了。

至于维护 $L_i$ 和 $R_i$ 不管是用单调栈还是 st 表都可以降低时间复杂度，我这里用的是 st 表。

### 代码
```cpp
#include<bits/stdc++.h>
#define Maxn 100005 
using namespace std;
int a[Maxn],b[Maxn];
int f[Maxn][2],l[Maxn],r[Maxn];
struct Tree {
    int val[Maxn<<2];
    #define lson x<<1,l,mid 
    #define rson x<<1|1,mid+1,r 
    void merge(int x,int l,int r,int u,int w) {
        if(l == r)return val[x]=max(val[x],w),void();
        int mid=l+r>>1;
        if(u<=mid) merge(lson,u,w);
        else merge(rson,u,w);
        val[x]=max(val[x<<1],val[x<<1|1]);
    }
    int query(int x,int l,int r,int L,int R) {
        if(L<=l&&r<=R)return val[x];
        int mid=l+r>>1,ans=0;
        if(L<=mid)ans=max(ans,query(lson,L,R));
        if(mid<R)ans=max(ans,query(rson,L,R));
        return ans;
    }
} tr[2];
int opt[Maxn][18],nxt[Maxn<<1],c[Maxn<<1],n;
void rmq() {
	for(int i=1;i<=n;i++)opt[i][0]=a[i];
	for(int j=1;j<=17;j++)
		for(int i=1;i<=n-(1<<j)+1;i++)
			opt[i][j]=max(opt[i][j-1],opt[i+(1<<(j-1))][j-1]);
}
int qmax(int l,int r) {int t=log2(r-l+1);return max(opt[l][t],opt[r-(1<<t)+1][t]);}
int find(int x,int l,int r) {
    int mid,ans = 0;
    while(l <= r) {
        mid=l+r>>1;
        if(c[mid] >= x)
            ans=mid,r=mid-1;
        else l=mid+1;
    } return ans;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tot = 0;
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i],c[++tot]=a[i];
	for(int i=1;i<=n;i++)cin>>b[i],c[++tot]=b[i];
	sort(c+1,c+tot+1);
	int m=unique(c+1,c+tot+1)-c-1;
	for(int i=1;i<=n;i++)a[i]=find(a[i],1,m),b[i]=find(b[i],1,m);
	for(int i=1;i<=n;i++)nxt[a[i]]=i,l[i]=nxt[b[i]];
	for(int i=1;i<=m;i++)nxt[i]=r[i]=n+1; 
	for(int i=n;i>=1;i--){
		nxt[a[i]]=i;
		r[i]=nxt[b[i]];
	} rmq();
    for(int i=1;i<=n;i++) {
		if(qmax(l[i],i)>b[i])l[i]=0;
		if(qmax(i,r[i])>b[i])r[i]=n+1;
        if(l[i] != 0)f[i][0]=max({f[i][0],tr[0].query(1,1,n,1,l[i])+1,tr[1].query(1,1,n,1,l[i])+1});
        if(r[i] != n+1)f[i][1]=max({f[i][1],tr[0].query(1,1,n,1,n)+1,tr[1].query(1,1,n,1,r[i])+1});
        if(l[i] != 0)tr[0].merge(1,1,n,l[i],f[i][0]);
        if(r[i] != n+1)tr[1].merge(1,1,n,r[i],f[i][1]);
    } int maxn = 0;
    for(int i=1;i<=n;i++)
        maxn=max({maxn,f[i][0],f[i][1]});
    cout << maxn;
    return 0;
}
```

---

