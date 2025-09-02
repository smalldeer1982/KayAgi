# Subsegments

## 题目描述

Programmer Sasha has recently begun to study data structures. His coach Stas told him to solve the problem of finding a minimum on the segment of the array in ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF69E/8d33f6dbc21a91477b8c6a86185f0b1fd0e74ad4.png), which Sasha coped with. For Sasha not to think that he had learned all, Stas gave him a new task. For each segment of the fixed length Sasha must find the maximum element of those that occur on the given segment exactly once. Help Sasha solve this problem.

## 样例 #1

### 输入

```
5 3
1
2
2
3
3
```

### 输出

```
1
3
2
```

## 样例 #2

### 输入

```
6 4
3
3
3
4
4
2
```

### 输出

```
4
Nothing
3
```

# 题解

## 作者：BFSDFS123 (赞：3)

比较基础的一道权值线段树题目，可以用来练手。


**什么是权值线段树？**

权值线段树，可以视为用线段树维护一个桶。这个线段树可以完成许多与桶有关的操作，而且更加方便快捷。可以实现的操作，包括不限于区间最大、区间最小、区间 k 大值等。

具体思路是将每一个叶子节点**看作一个权值**，存储一些值（比如这个数的出现次数），然后再像普通线段树那样进行值的合并与计算。


**题目详解**

题意：

给定一个长度为 $n$ 的序列，求每一段长度为 $k$ 的子串里只出现过一次的数的最大值；如果都出现过，输出 ``Nothing``。

看到这种出现次数题，首先考虑权值线段树。

可以发现，我们可以在叶子节点上存储下来每一个数的出现次数。如果是 1，那么这个数就可以成为答案，将其答案储存为这个数；否则将其答案储存为 0

在不是叶子节点的点上，出现次数可以忽略，答案即为两个儿子节点的最大值。

但是我们会发现 $-10^9\le a_i \le 10^9$，权值线段树明显存不了这么大，所以我们考虑离散化。

我采用的离散化方式是使用 ``unique`` 和 ``lower_bound`` 进行离散化。


代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define eps 1e-8
const int inf=0x3f3f3f3f;
const int Maxn=1e5+10;
int n,k; 
struct SegTree{
	int ans; // 满足的答案的最大值 
	int sum; // 叶子节点 only：存储数出现的次数 
}t[Maxn<<4];
#define ls node<<1
#define rs node<<1|1
void pushup(int node)
{
	t[node].ans=max(t[ls].ans,t[rs].ans);
}
void update(int node,int l,int r,int pos,int val)
{
	if(l==r)
	{
		t[node].sum+=val;
		if(t[node].sum==1)
		{
			t[node].ans=l;
		}else{
			t[node].ans=0;
		}
		return ;
	}
	int mid=(l+r)>>1;
	if(pos<=mid)
	{
		update(ls,l,mid,pos,val);
	}else{
		update(rs,mid+1,r,pos,val);
	}
	pushup(node); // 合并叶子节点答案
}
int Ar[Maxn];
int tmp[Maxn];
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&Ar[i]);
		tmp[i]=Ar[i];
	}
	sort(tmp+1,tmp+1+n);
	int newn=unique(tmp+1,tmp+1+n)-tmp-1;
	for(int i=1;i<=n;i++)
	{
		Ar[i]=lower_bound(tmp+1,tmp+1+newn,Ar[i])-tmp;
//		cout<<Ar[i]<<" ";
	}
	 
	// 上面是离散化

//	cout<<endl;
	for(int i=1;i<k;i++)
	{
		update(1,1,newn,Ar[i],1); // 将前 k-1 个值插入权值线段树
	}
	for(int i=k;i<=n;i++)
	{
		update(1,1,newn,Ar[i],1); // 插入新一个值
		int ans=t[1].ans;
//		cout<<"ans="<<ans<<endl;
		if(ans==0)
		{
			puts("Nothing");
		}else{
			printf("%d\n",tmp[ans]);
		}
		update(1,1,newn,Ar[i-k+1],-1); // 删除现在序列的第一个值
	}
	return 0;
}

```

---

## 作者：vandijk (赞：3)

这题思路很好想，先求出前 $k$ 个的答案，用一个 $set$ 来保存 $1$ 的答案，用一个 $map$ 来保存数出现的数量，之后用类似滑动窗口的做法做就行了。

$Tips$ : 在 $set$ 中找最大值可以插入这个数的负数，直接调用 $s.begin()$ 就行了

$Code$ :

```cpp
#include <bits/stdc++.h>
#define rep(i,n) for(int i=0;i<n;i++)
#define forn(i,a,b) for(int i=a;i<b;i++)
using namespace std;
typedef long long ll;
map<int,int> mp;
set<int> st;
int n,k;
int a[100010];
int main(){
	cin>>n>>k;
	for(int i=0;i<n;i++){
		cin>>a[i];
	}
	for(int i=0;i<k;i++){
		mp[a[i]]++;
	}
	for(int i=0;i<k;i++){
		if(mp[a[i]]==1)st.insert(-a[i]);
	}
	if(st.empty()){
		cout<<"Nothing\n";
	}
	else cout<<-(*st.begin())<<"\n";
	for(int i=k;i<n;i++){
		if(mp[a[i-k]]==1)st.erase(-a[i-k]);
		if(mp[a[i]]==1)st.erase(-a[i]);
		mp[a[i-k]]--;
		mp[a[i]]++;
		if(mp[a[i-k]]==1)st.insert(-a[i-k]);
		if(mp[a[i]]==1)st.insert(-a[i]);
		if(!st.empty())cout<<-(*st.begin())<<"\n";
		else cout<<"Nothing\n";
	}
	return 0;
}
```


---

## 作者：rEdWhitE_uMbrElla (赞：1)

好简单的一道E题啊。。。

把数扔进set来求得最大值，用map纪录每个数上次进入的时间来去重，然后模拟就行了啊。。。

代码如下：

```cpp
#include <cstdio>
#include <cstring>
#include <set>
#include <map>
#include <algorithm>
using namespace std;

int a[100000];
set<int> now;
map<int,int> cnt;

void push(int value, int offset){
    if((cnt[value]+=offset)==1){
        now.insert(value);
    }else{
        now.erase(value);
    }
}

int main(){
    int n,k;
    scanf("%d%d",&n,&k);
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
        push(-a[i],1);
        if(i-k>=0) push(-a[i-k],-1);
        if(i-k>=-1) if(now.empty()) puts("Nothing"); else printf("%d\n",-*now.begin());
    }
}
```

---

## 作者：xiezheyuan (赞：1)

[也许有更好的阅读体验](https://www.cnblogs.com/zheyuanxie/p/wsgt.html)

## 简要题意

给出两个整数 $n,k$ 和一个序列 $a$。

你需要对于每一个长度为 $k$ 的区间。求出区间中仅出现过一次的元素的最大值。如果不存在仅出现过一次的元素，输出 `Nothing`。

$1 \leq n \leq 10^5,1 \leq k \leq n,-10^9\leq a_i\leq 10^9$

## 思路

考虑使用权值线段树解决这个问题。

先将 $[1,k-1]$ 的元素插进权值线段树，然后对于每一个区间，维护一个类似滑动窗口的东西。我们滑动区间时删除不在窗口里的元素，插入新来的元素。然后考虑如何求出仅出现过一次的元素的最大值。

单点修改时，维护 $t,v$。$t$ 表示元素个数，$v$ 表示对答案的贡献。到达叶子节点时，先更新 $t$。如果 $t=1$，则 $v=l$，否则 $v=0$。然后 `pushup` 时对 $v$ 取 $\max$ 即可。答案为 `Nothing` 当且仅当根节点的 $v=0$。

至于值域问题，我们加上偏移值 $10^9$，然后使用动态开点线段树。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define ls (t[i].l)
#define rs (t[i].r)
#define mid ((l+r)>>1)
#pragma GCC optimize("Ofast", "inline", "-ffast-math")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")
using namespace std;

const int N = 1e5+5;
const int MOV = 1e9;

struct node{
    int v,t,l,r;
} t[N<<4];
int tot,root;

inline void pushup(int i){
    t[i].v=max(t[ls].v,t[rs].v);
}

void update(int p,int v,int &i,int l,int r){
    if(!i) i=(++tot);
    if(l==r){
        t[i].t+=v;
        if(t[i].t==1) t[i].v=l;
        else t[i].v=0;
        return; 
    }
    if(p<=mid) update(p,v,ls,l,mid);
    else update(p,v,rs,mid+1,r);
    pushup(i);
}

int n,k,a[N];

signed main(){
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<k;i++) update(a[i]+MOV,1,root,0,2e9);
    for(int i=1;i<=(n-k+1);i++){
        update(a[i+k-1]+MOV,1,root,0,2e9);
        if(t[root].v) cout<<(t[root].v-MOV)<<'\n';
        else cout<<"Nothing"<<'\n';
        update(a[i]+MOV,-1,root,0,2e9);
    }
    return 0;
}
```

---

## 作者：activeO (赞：1)

## 题目大意

就是给你个长度为 n 序列，求每一段长度为 k 的字串中只出现过一次的数的最大值，如果都重复出现过，就输出 Nothing。

## 思路

考虑写权值线段树，先插完 $ [1,k-1] $ 的区间，每一次查询就把第一个删掉，往后新添一个。离散化后插入就就维护如果 x 这个点可以贡献，就标记，不能就标为 0，要的就是标记最大那个。

## 代码

```cpp
#include <bits/stdc++.h>//祝大家学习愉快！

using namespace std;

const int maxn=1e5+10;
int tr[maxn<<2],bot[maxn<<2];
int tmp[maxn],a[maxn];

void pushup(int x){
	tr[x]=max(tr[x<<1],tr[x<<1|1]);
}
void update(int now,int l,int r,int x,int v){//正常板子
	if(l==r){
		bot[now]+=v;
		if(bot[now]==1) tr[now]=l;
		else tr[now]=0;
		return;
	}
	int mid=(l+r)>>1;
	if(x<=mid) update(now<<1,l,mid,x,v);
	else update(now<<1|1,mid+1,r,x,v);
	pushup(now); 
}

int main(){
	
	int n,k;
	
	scanf("%d %d",&n,&k);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		tmp[i]=a[i];
	}
	
	sort(tmp+1,tmp+n+1);//离散化
	int cnt=unique(tmp+1,tmp+n+1)-tmp-1;
	for(int i=1;i<=n;i++) a[i]=lower_bound(tmp+1,tmp+cnt+1,a[i])-tmp;
	
	for(int i=1;i<k;i++) update(1,1,cnt,a[i],1);//先插好 k-1 个
	
	for(int i=1;i<=(n-k+1);i++){
		update(1,1,cnt,a[i+k-1],1);//加入后一个
		if(tr[1]) printf("%d\n",tmp[tr[1]]);//tr[1]就是标记最大的，要套回原来的数。
		else puts("Nothing");
		update(1,1,cnt,a[i],-1);//删掉前一个
	}
	
	return 0;
}
```


---

## 作者：AFewSuns (赞：1)

### 题目大意

给定一个长度为 $n$ 的数列 $a_i$，求每个区间 $[a_i,a_{i+k-1}](1 \leq i \leq n-k+1)$ 中，出现次数为 $1$ 的数的最大值。没有则输出 $Nothing$。

$1 \leq k \leq n \leq 10^5,-10^9 \leq a_i \leq 10^9$

### 题目分析

本人不善用 STL，所以来写一篇线段树的题解。

首先，我们需要查询的区间是连续的，可以看做一个区间在不断往右移。所以每往右移一个数，相当于删除最前面的数，然后加入最后面的数。

这样一来，我们就能快速知道哪些数出现的次数为 $1$ 了。可以先对 $a_i$ 离散化，再开个桶，记录一下 $a_i$ 出现的次数。当次数为 $1$ 时，它就能对答案做贡献。

现在的问题就在于如何求最大值了。开一颗值域线段树，维护区间内出现次数为 $1$ 的数的最大值，让次数不为 $1$ 的最大值为 $0$，更新的时候与左右儿子取最大值即可。当然你也可以像我一样，把桶放到线段树里一起维护。

时间复杂度为 $O(n\log n)$，代码可能会相对比较长，但挺好写的。

### 代码

```cpp
#include<bits/stdc++.h>
#define LC x<<1
#define RC x<<1|1
using namespace std;
int n,k,a[100010],lsh[100010],cnt=0,tree[400040],maxx[400040];//tree：桶，maxx：区间最大值 
void pushup(int x){
	maxx[x]=max(maxx[LC],maxx[RC]);//直接取最大值 
}
void mdf(int x,int l,int r,int pos,int v){//正常的线段树修改操作 
	if(l==r){
		tree[x]+=v;//更新次数 
		if(tree[x]==1) maxx[x]=l;//如果出现次数恰好为1，就把maxx赋成l 
		else maxx[x]=0;//否则变成0，说明不可贡献 
		return;
	}
	int mid=(l+r)>>1;
	if(pos<=mid) mdf(LC,l,mid,pos,v);
	else mdf(RC,mid+1,r,pos,v);
	pushup(x);
}
int main(){
	scanf("%d %d",&n,&k);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++) lsh[++cnt]=a[i];
	sort(lsh+1,lsh+cnt+1);//离散化 
	cnt=unique(lsh+1,lsh+cnt+1)-lsh-1;
	for(int i=1;i<=n;i++) a[i]=lower_bound(lsh+1,lsh+cnt+1,a[i])-lsh;
	for(int i=1;i<k;i++) mdf(1,1,cnt,a[i],1);//先把前面k-1个加进去 
	for(int i=1;i<=(n-k+1);i++){
		mdf(1,1,cnt,a[i+k-1],1);//把最后一个加进来 
		if(!maxx[1]) printf("Nothing\n");//maxx[1]就是全局最大值，等于0说明没有 
		else printf("%d\n",lsh[maxx[1]]);
		mdf(1,1,cnt,a[i],-1);//把最前面的删掉 
	}
}
```

---

## 作者：fisheep (赞：0)

### 题意：
对于固定长度的每个数列，Sasha必须找到在给定数列上出现的元素的最大值。帮Sasha解决这个问题。

第一行两个整数$n$ 和$k$ $(1\leq n \leq 10^5,1 \leq k \leq n)$,表示数组元素的数目和数列的长度。

然后 $n$ 行，第 $i$ 行包含一个数字$a_i(-10^9 \leq a_i \leq 10^9)$

输出 $n−k+1$ 个数，每行输出一个数，第$i$行输出以为$i$为起点，长度为$k$的数列中的最大值。

并且在$a_i  a_{i+1} .....a_{i+k-1}$,中每个数只能出现一次(重复视为没有元素)，如果数列中没有元素，输出$Nothing$。

### 分析：
不难看出我们只需要统计数列内最大值即可。

**注意:** 如果数列中出现了$i (i>1)$次同一个数，则这个数对数列贡献为$0$。

### Code
```cpp
#include <cstdio>
#include <cstring>
#include <set>
#include <map>
#include <algorithm>
using namespace std;

inline int read() {
	int x=0,f=1;
	char ch=getchar();
	while(ch>'9'||ch<'0') {
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}

int a[100000];
set<int> now;
map<int,int> cnt;

void push(int v, int c){
    if((cnt[v]+=c)==1){
        now.insert(v);
    }else{
        now.erase(v);
    }
}

int main(){
    int n,k;
    n=read(),k=read();
    for(int i=0;i<n;i++){
        a[i]=read();
        push(-a[i],1);
        if(i-k>=0) push(-a[i-k],-1);
        if(i-k>=-1) if(now.empty()){
		 printf("Nothing"); 
		 }else {
		 printf("%d\n",-*now.begin());
	}
    }
}
```




---

