# Little Elephant and Inversions

## 题目描述

## 题意翻译
给你一个长度为 n 的序列 A[1], A[2], …, A[n].
问你有多少组 (l, r) （1 <= l < r <= n) 满足
A[1], A[2], …, A[l], A[r], A[r+1], ..., A[n] 的逆序对个数不超过 k。

## 样例 #1

### 输入

```
3 1
1 3 2
```

### 输出

```
3
```

## 样例 #2

### 输入

```
5 2
1 3 2 1 7
```

### 输出

```
6
```

# 题解

## 作者：Cylete (赞：3)

首先有个很显然的结论

若$(l, r)$满足条件，那么$(l, r + 1), (l, r + 2)……(l, n)$都满足条件

类似尺取法

我们考虑每一个$l$，只需要找到最小的一个满足条件的$r$统计答案$ans += n - r + 1$即可

显然对于$1 <= l <= n$，$r$是单调不减的

因为数字越多逆序对也会多

然后我们考虑如何转移$l$和$r$

对于一个$a_l$,增加的逆序对个数就是前面$[1, l - 1]$比它大的和后面[r, n]比它小的

对于一个$a_r$,减少的逆序对个数就是前面$[1, l]$比它大的和后面$[r + 1, n]$比它小的

注意要先离散化

```cpp
const int N = 1e5 + 10;

int n, k, now, ans;
int a[N], lsh[N], qaq;

struct node
{
	int num;
	int tree[N];
	inline void add(int x, int val)
	{
		num += val;
		for(; x <= 100000; x += x & -x) tree[x] += val; 
	}
	inline int ask(int x)
	{
		int res = 0;
		for(; x; x -= x & -x) res += tree[x];
		return res;
	}
}t1, t2;

signed main()
{
	into();
	read(n); read(k);
    //离散化
	for(R int i = 1; i <= n; i++) read(a[i]), lsh[i] = a[i];
	sort(lsh + 1, lsh + n + 1);
	qaq = unique(lsh + 1, lsh + n + 1) - lsh - 1;
	for(R int i = 1; i <= n; i++) a[i] = lower_bound(lsh + 1, lsh + qaq + 1, a[i]) - lsh;
    //先处理r，统计一开始的逆序对数
	for(R int i = 1; i <= n; i++)
	{
		now += t2.num - t2.ask(a[i]);
		t2.add(a[i], 1);
	}
    
	R int l, r = 1;
	for(l = 1; l < n && r <= n; l++)
	{
		if(l == r)//l == r不合法
		{
			now -= t1.num - t1.ask(a[r]);
			now -= t2.ask(a[r] - 1);
			t2.add(a[r], -1);
			r++;
		}
		now += t1.num - t1.ask(a[l]);
		now += t2.ask(a[l] - 1);
		t1.add(a[l], 1);
		while(now > k && r <= n)
		{
			now -= t1.num - t1.ask(a[r]);
			now -= t2.ask(a[r] - 1);
			t2.add(a[r], -1);
			r++;
		}
		ans += (n - r + 1);
	}
	writeln(ans);
	return 0;
}
```

---

## 作者：maruize (赞：1)

前置知识：

树状数组

离散化

最好会树状数组求逆序对

------------

首先，对于每个符合条件的（l，r）：

		（l，r+1），（l，r+2）...都符合条件。
        
			（数越少，逆序对越少
        
因此，只需对每个 l ，找到符合条件的最小的 r 。

然而还可发现，随着 l 的右移，最小的 r 也会右移！
（two-pointer? !）

这样只需求移动 l 和 r 时逆序对的变化！

------------

l 每向右扩展，逆序对数量增长 

a[ 1 ~ l-1]中大于a[ l ]的元素的数量，a[r~n]中小于a[ l ]的元素的数量

r 每向右扩展，逆序对数量减少 

a[ 1 ~ l-1]中大于a[ r ]的元素的数量，a[r~n]中小于a[ r ]的元素的数量

可以用树状数组维护。

------------

做法是：
先将数组离散化，对于[ 1 , l ]维护树状数组S，

对于[ r , n ]维护树状数组T，

S[i]表示a[ 1 , l ]中等于i的数的数量（a表示离散化后数组）

T[i]表示a[ r , n ]中等于i的数的数量（a表示离散化后数组）

移动 l 和 r 。

------------


代码：

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
#define N 500050
#define lowbit(i) ((i)&(-(i)))
struct TreeArray{
	int tree[N],n;
	inline void add(int a,int b)
		{for(;a<N;a+=lowbit(a))tree[a]+=b;}
	inline int sum(int l,int r){
		if(l>r)return 0;
		int res=0;l--;
		while(r>l)res+=tree[r],r-=lowbit(r);
		while(l>r)res-=tree[l],l-=lowbit(l);
		return res;
	}
}S,T;//树状数组的struct 
struct node{int id,d,t;}data[N];
inline bool cmp1(node a,node b){return a.d<b.d;}
inline bool cmp2(node a,node b){return a.id<b.id;}
signed main(){
	int n;long long k,ans=0;
	scanf("%d%I64d",&n,&k);//题面让用I64D，lld好像也可以？ 
	for(int i=1;i<=n;i++)scanf("%d",&data[i].d),data[i].id=i;
	sort(data+1,data+n+1,cmp1);data[n+1].t=-1;
	for(int i=1,j=1;i<=n;i++,j++){
		data[i].t=j;
		while(data[i+1].d==data[i].d)i++,data[i].t=j;//相同的數要离散化成相同的数 
	}
	sort(data+1,data+n+1,cmp2);
	//==离散化== 
	
	int l=0,r=1;long long num=0;
	for(int i=r;i<=n;i++)num+=T.sum(data[i].t+1,N),T.add(data[i].t,1);
	while(l<n){
		l++;
		num+=S.sum(data[l].t+1,N),num+=T.sum(1,data[l].t-1);
		S.add(data[l].t,1);
		while(num>k||l==r){//l==r时不合法 
			num-=S.sum(data[r].t+1,N),num-=T.sum(1,data[r].t-1);
			T.add(data[r].t,-1);
			r++;
			if(r>n)goto End;//用goto偷个懒 
		}
		ans+=n-r+1;//从r往后全是答案，都要加上 
	}
	End:
	printf("%I64d",ans);
	return 0;
}
```



---

## 作者：intel_core (赞：0)

简要题意：求有多少对 $(l,r)$ 满足 $a_1,a_2,\cdots,a_l,a_r,a_{r+1},\cdots,a_n$ 的逆序对不超过 $k$ 个，$n\le 10^5$。

发现如果 $(l,r)$ 满足条件，如果 $x\le l,r\le y$，那么 $(x,y)$ 一定满足条件。

所以我们只需要找出对于固定的 $l$，符合条件最小的 $r$ 在哪里就可以。

这不就是双指针嘛。。。

所以我们双指针扫一遍，把 $a_1,a_2,\cdots,a_l$ 开一个树状数组，再对 $,a_r,a_{r+1},\cdots,a_n$ 开一个树状数组；这样就可以快速知道插入/删除一个数对于逆序对数的贡献了。

双指针，$O(n\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NR=1e5+10;
#define int long long
int n,k,a[NR],v[NR],len,ans;

struct BIT{
	int c[NR];
	void init(){
		memset(c,0,sizeof(c));
	}
	int lowbit(int x){
		return x&(-x);
	}
	void add(int x,int y){
		while(x<=len){
			c[x]+=y;
			x+=lowbit(x);
		}
	}
	int sum(int x){
		int res=0;
		while(x){
			res+=c[x];
			x-=lowbit(x);
		}
		return res;
	}
	int calc(int l,int r){return sum(r)-sum(l-1);}
}T1,T2;
	

signed main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++)
		scanf("%lld",&a[i]),v[++len]=a[i];
	sort(v+1,v+1+len);
	len=unique(v+1,v+1+len)-v-1;
	for(int i=1;i<=n;i++)a[i]=lower_bound(v+1,v+1+len,a[i])-v;
	int now=1,cnt=0;
	for(int i=1;i<=n;i++)cnt+=T2.calc(a[i]+1,len),T2.add(a[i],1);
	for(int i=1;i<=n;i++){
		cnt+=T1.calc(a[i]+1,len)+T2.calc(1,a[i]-1);
		T1.add(a[i],1);
		while(now<=i||(cnt>k&&now<=n))cnt-=T1.calc(a[now]+1,len)+T2.calc(1,a[now]-1),T2.add(a[now],-1),now++;
		ans+=n-now+1;
	}
	cout<<ans<<endl;
	return 0;
}
```

---

