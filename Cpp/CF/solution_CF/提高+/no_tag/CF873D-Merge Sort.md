# Merge Sort

## 题目描述

归并排序是有名的排序算法。对数组$a$的元素进行排序的主要功能可以按如下步骤实现：
1. 如果$[l,r)$区间已经以非降序排列时（即对于任意$i$满足$l<=i<r-1$,都有$a[i]<=a[i+1])$,这时结束函数调用；
2. 令$mid=[(l+r)/2]$;
3. 调用$mergesort(a,l,mid)$;
4. 调用$mergesort(a,mid,r)$;
5. 合并$[l,mid),[mid,r)$区间，使$[l,r)$按非降序排列。合并算法不会调用任何其他函数。

题中数组索引从0开始，因此对整个数组进行排序需调用$mergesort(a,0,n)$。

函数$mergesort$的调用次数非常重要，因此Ivan决定在对数组进行排序时对其进行计算。例如，如果$a=1,2,3,4$，那么就会有1次$mergesort$调用—— $mergesort(0,4)$，其检查到数组已排好序并结束程序。如果$a=2,1,3$，则调用次数为3：首先，调用$mergesort(0,3)$，然后设$mid=1$，调用$mergesort(0,1)$和$mergesort(1,3)$，此后不执行任何递归调用，因为$(0,1)$和$(1,3)$已经排好序。

Ivan已经实现了计算$mergesort$调用次数的程序，但现在他需要测试这个程序。为此，他需要找到一个长度为$n$的序列$a$（即$a$中的元素数是$n$，且这个数组包含$[1,n]$中的每个整数），并且在排序数组时$mergesort$调用的次数正好是$k$。

请帮Ivan找到他想要的序列！

## 样例 #1

### 输入

```
3 3
```

### 输出

```
2 1 3 ```

## 样例 #2

### 输入

```
4 1
```

### 输出

```
1 2 3 4 ```

## 样例 #3

### 输入

```
5 6
```

### 输出

```
-1
```

# 题解

## 作者：da32s1da (赞：3)

一道构造题。

考虑到每次调用$\mathrm{mergesort}$都是$2$次，加上初始的一次，总次数一定是**奇数**。

所以**偶数一定**是$-1$。

考虑怎么让调用次数$+2$，假设已经到区间$\mathrm{[l,r)}$，此时$\mathrm{[l,r)}$是递增的，只需$\mathrm{swap(a[mid-1],a[mid])}$。这样既能保证$\mathrm{[l,r)}$不递增，又保证了$\mathrm{[l,mid),[mid,r)}$递增。

```cpp
#include<cstdio>
const int N=1e5+50;
int n,k,a[N];
inline void swap(int &u,int &v){int o=u;u=v;v=o;}
void dfs(int l,int r){
	if(l+1>=r||!k)return;//单独元素或没有必要交换就返回
	k-=2;//调用次数-2
	int mid=l+r>>1;
	swap(a[mid-1],a[mid]);
	dfs(l,mid);dfs(mid,r);
}
int main(){
	scanf("%d%d",&n,&k);
	if(k&1^1){puts("-1");return 0;}//偶数判掉
	for(int i=0;i<n;i++)a[i]=i+1;
	k--;//初始调用一次
	dfs(0,n);
	if(k)puts("-1");//还有调用次数，为-1
	else for(int i=0;i<n;i++)printf("%d ",a[i]);
}
```

---

## 作者：「　」 (赞：3)

#### 其实最优的方法其他的题解已经讲得很好了，本题解仅用于记录和分享一个新的思路。
这道题是让你输出符合条件的序列，而序列的每个数之间具有一定的**逻辑关系**，很容易想到拓扑排序，于是此题就变为，如何找出满足条件的逻辑关系。

我们可以先看一下操作次数最多的序列：

![](https://cdn.luogu.com.cn/upload/image_hosting/26j5lfcl.png)

（每一条红线都是一次操作），我们可以删除一次操作，当且仅当左半边与右半边都排好序的情况下，即删除了所有子操作的情况下，使得左半边与右半边中间建一条边，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/yqoz7wk7.png)

我们可以通过在$1$与$2$之间**建一条边**来删除$1$与$2$两者的操作

![](https://cdn.luogu.com.cn/upload/image_hosting/9km1xbi5.png)

我们还可以通过在$2$与$3$之间建一条边来删除$1$与$2$之间，$3$与$4$之间的操作，但此时$1$与$2$，$3$与$4$之间必须**已经建边**。

上述操作可以通过递归完成，最后再跑一边拓扑排序，复杂度$O(nlogn)$

```cpp
#include<cstdio>
#include<iostream>
#include<queue>
using namespace std;
int n,k;
struct Edge
{
	int to,nxt;
}e[100005];
int fir[100005],size;
int d[100005];
void add(int u,int v)
{
	e[++size].to=v;
	e[size].nxt=fir[u];
	fir[u]=size;
	++d[v];
}
int cnt;
void merge(int l,int r)
{
	if(l==r-1)
	{
		return ;
	}
	int mid=(l+r)/2;
	merge(l,mid);
	merge(mid,r);
	if(cnt>k)
	{
		add(mid-1,mid);
		cnt-=2;
	}
}
queue <int> q;
int ans[100005];
void top()
{
	for(int i=n-1;i>=0;--i)
	{
		if(d[i]==0)
		q.push(i);
	}//一定要反向塞入，拓扑排序仅能保证逻辑关系，本题顺序非正即反，所以未建边的位置就是反的
	cnt=0;
	while(q.size())
	{
		int tmp=q.front();
		q.pop();
		ans[tmp+1]=++cnt;//我们建边和拓扑的是点的位置，根据出队顺序决定数字顺序
		for(int i=fir[tmp];i;i=e[i].nxt)
		{
			--d[e[i].to];
			if(d[e[i].to]==0)
			q.push(e[i].to);
		}
	}
}
int main()
{
	cin>>n>>k;
	if(k%2==0||k>2*n-1)
	{
		printf("-1\n");
		return 0;
	}
	cnt=2*n-1;
	merge(0,n);
	top();
	for(int i=1;i<=n;++i)
	{
		printf("%d ",ans[i]);
	}
	printf("\n");
	return 0;
}
```


---

## 作者：uncle_steve (赞：2)

### 题型：一道构造题（通过构造条件，推原始序列）

给出一个 `n` 与 `k` ，求满足归并排序函数调用次数为 `k` 的，且长度为 `n` 的序列。

归并排序的模板：


```cpp
void merge_sort(int l,int r){
	if(l==r) return;
	int m=(l+r)/2;
	merge_sort(l,m);
	merge_sort(m+1,r);
    ……（以下略）
}
```
可以看出，每次都会调用 `2` 次归并排序函数，再加上开头的一次（检查序列是否已经有序），得出：**`k` 一定是奇数。( 2 是偶数，加上 1 一定是奇数）**

所以先特判：偶数一定是 `-1` 。

考虑将调用次数加 `2` ，因为区间 $ [l,r) $ 递增，则必然要让 $ [l,mid) $ 与 $ [mid,r) $  不递增，但 $ [l,r) $ 仍然递增。只需 $swap(a[mid-1],a[mid])$ 即可。

![](https://cdn.luogu.com.cn/upload/image_hosting/zjxoso4b.png?x-oss-process=image/resize,m_lfit,h_500,w_1000)

结束条件： $k$ 达到标准或单独元素（没有必要交换）。

特判2：当所有调用都为单一元素时，$k>0$ 则输出 `-1` （没有元素可交换了，但还没有达标）。

例如：$ n = 5,k = 11 $  时，最大交换次数为 $2*5-1=9$ 次，不满足条件，输出 `-1` 。


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a[100001];
void merge_sort(int l,int r){
	if(l+1==r||k<=0) return;//单一元素或k达标时return掉。
	int m=(l+r)/2;
	swap(a[m-1],a[m]);//交换，使[l,r)不递增。
	k-=2;//调用2次
	merge_sort(l,m);
	merge_sort(m,r);
}
int main(){
	cin>>n>>k;
	if(k%2==0){//特判1：k非偶数。
		cout<<"-1"<<endl;
		return 0;
	}
	k--;
	for(int i=0;i<n;i++) a[i]=i+1;//重置数组为1~k
	merge_sort(0,n);
	if(k>0){//特判2：分完时k仍然>0，则输出-1
		cout<<"-1"<<endl;
		return 0;
	}
	for(int i=0;i<n;i++){//否则输出符合条件的序列
		cout<<a[i]<<" ";
	}
		
	return 0;
}
```

---

## 作者：SuperCowHorse (赞：1)

构造水蓝一道。

先证明一个东西：无论序列是否有序，最开始一定需要递归 mergesort 这个函数，而每个函数内部又会调用零或二次 mergesort 函数，所以合法的 $k$ 一定是偶数。

~~那就可以愉快地特判了。~~

考虑进行深度优先搜索。

若 $k$ 是奇数，直接进行搜索，找出合法解。如果搜索结束 $k$ 还不为 $0$，说明无法构造，输出`-1`。

详见注释。
``` cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
int n,k,a[maxn];
void solve_merge(int l,int r){
	if(l+1==r||k<=0) return;
	int mid=l+r>>1;
	swap(a[mid],a[mid-1]);//交换
	k-=2;//每个函数调用0或2次，这里的k>0，由于不是奇数，仍能够减2
	solve_merge(l,mid);solve_merge(mid,r);//搜索
}
signed main(){
	scanf("%d%d",&n,&k);
	if(!(k&1)){//是偶数就特判掉
		printf("-1");
		return 0;
	}
	for(int i=0;i<n;++i)//初始化
		a[i]=i+1;
	--k;
	solve_merge(0,n);
	if(k){
		printf("-1");
		return 0;
	}
	for(int i=0;i<n;++i)//输出
		printf("%d%c",a[i]," \0"[i==n-1]);
	return 0;
}
```

---

## 作者：FReQuenter (赞：0)

考虑什么情况下会多两次函数调用。

一个子序列（$a_{[l,r)}$）不有序。

如何使得它不有序且不会影响之后的结果呢？

调换 $a_{mid-1},a_{mid}$，其中 $mid=\lfloor\frac{l+r}{2}\rfloor$

然后就做完了。从 $[0,n)$ 开始递归，如果当前的调用函数数量小于 $k$，那么就调换，让调用次数加二。最后凑不到 $k$ 就是 $-1$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a[100005];
void dfs(int l,int r){
	if(r-l==1||k==1) return;
	int mid=(l+r)>>1;
	swap(a[mid-1],a[mid]);
	k-=2;
	dfs(l,mid);
	dfs(mid,r);
}
signed main(){
	cin>>n>>k;
	for(int i=0;i<n;i++) a[i]=i+1;
	dfs(0,n);
	if(--k) cout<<-1;
	else for(int i=0;i<n;i++) cout<<a[i]<<' ';
}
```

---

## 作者：zjjws (赞：0)

[CF873D](https://codeforces.com/problemset/problem/873/D)

我的思路就是直接模拟

设当前做到区间 $[l,r)$ ，还要操作 $k$ 次（已经减去调用 $[l,r)$ 的这一次）

如果 $k$ 等于0，就直接按顺序赋值

否则就说明区间 $[l,r)$ 不有序

那么就先递归右区间，再递归左区间，能保证右边赋的值全部小于左边

设中间断点为 $mid$

上述那句话的意思就是对于任意 $x\in [l,mid),y\in [mid,r)$ 满足 $a[x]>a[y]$


1.题目给的操作方案就是左闭右开区间，不要写自己习惯的左闭右闭

2.可以从最后结果往回一步推出对于每个区间，分到的操作数k必须是奇数

3.由题目给的操作知道只有右边的区间可能更大，所以当分不均时需右边分到的多

```
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int MAX=1e5+3;
int a[MAX];
int nam=0; 
bool b=false;
inline void dfs(int l,int r,int k)
{
	if(l==r-1&&k!=1){b=true;return;}
	if(k==1){for(int i=l;i<r;i++)a[i]=++nam;return;}
	k--;
	int k_r=k>>1;
	if(k_r%2==0)k_r++;
	int mid=(l+r)>>1;
	dfs(mid,r,k_r);
	dfs(l,mid,k-k_r);
}
LL rin()
{
	LL s=0;
	char c=getchar();
	bool bj=0;
	for(;(c>'9'||c<'0')&&c!='-';c=getchar());
	if(c=='-')bj=true,c=getchar();
	for(;c>='0'&&c<='9';c=getchar())s=(s<<1)+(s<<3)+(c^'0');
	if(bj)return -s;
	return s;
}
int main() 
{
    int i,j;
    int n,k;
    n=rin();k=rin();
    if(k%2==0){printf("-1");return 0;}
    dfs(1,n+1,k);
    if(b)printf("-1");
    else for(i=1;i<=n;i++)printf("%d ",a[i]);
	return 0;
}
```

---

