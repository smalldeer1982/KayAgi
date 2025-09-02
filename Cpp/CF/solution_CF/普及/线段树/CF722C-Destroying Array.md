# Destroying Array

## 题目描述

给你一个由 $n$ 个非负整数组成的数列 $a_1$，$a_2$，$\cdots$，$a_n$。

你将要一个一个摧毁这个数列中的数。并且，现在给你一个由 $1$ 到 $n$ 组成的序列来告诉你每个数被摧毁的时间顺序。

每当一个元素被摧毁时，你需要找到这个当前数列中的未被摧毁的数组成的和最大的连续子序列，另外，如果当前剩余的序列是空的的话，最大和就是 $0$。

## 说明/提示

第一个样例：

1.第三个数被删除了，现在的数列是 1 3 x 5 ，5由一个数5组成。

2.第四个数被删除了，现在的数列是 1 3 x x ，4由两个数1和3组成。

3.第一个数被删除了，现在的数列是 x 3 x x ，3由一个数3组成。

4.最后一个剩下的数被删除了，现在的数列中没有东西啦，所以答案是0呢！


感谢 @FangHaosb 提供的翻译

## 样例 #1

### 输入

```
4
1 3 2 5
3 4 1 2
```

### 输出

```
5
4
3
0
```

## 样例 #2

### 输入

```
5
1 2 3 4 5
4 2 3 5 1
```

### 输出

```
6
5
5
1
0
```

## 样例 #3

### 输入

```
8
5 5 4 4 6 6 5 5
5 2 8 7 1 3 4 6
```

### 输出

```
18
16
11
8
8
6
6
0
```

# 题解

## 作者：Mr_think (赞：15)

## [CF722C Destroying Array](https://www.luogu.com.cn/problem/CF722C)

## 题目大意：
给定由 $n$ 个非负整数组成的数列 $\lbrace a_i\rbrace$ 每次可以删除一个数，求每次删除操作后的最大连续子序列。
## solution:
不难想到，我们可以使用一种支持修改和查询的数据结构。每次删除等价于把下标为 $i$ 的数修改成一个极小值，此时的最大连续子序列就不会选择这个数。维护最大连续子序列的实现可以参考[这道题](https://www.luogu.com.cn/problem/SP1043)：

## 接下来是细节的处理：

1. 题目中 $0<=a<=10^9$ 且 $1<=n<=10^5$ 最大连续子序列的和会超过 $\text {int}$ 我们需要开个 $\text{long long }$。
2. 删除的数要修改成一个极小值 $-9\times 10^{13}$ ，但是这样写会有一个问题，相信聪明的你一定能解决 (~~其实也是对思路理解的反馈~~)。
3. 对于查询，我们只输出根节点的信息就可以了。

看到这的同学，可以自己去写代码了(~~tf口吻~~)

[code](https://www.luogu.com.cn/paste/dyodpx67)
### End
## 作者的碎碎念：

有用留赞(~~言简意赅~~)

---

## 作者：shenmadongdong (赞：5)

其他的题解的方法都太麻烦了吧。。。

要什么并查集,直接暴力用 multiset 维护就好了

首先可以用 set 求出哪个点在哪个区间，然后当一个点被摧毁时，先 erase 掉它所在的区间和，然后把这个区间这个点以左的部分的和丢进 set 里，把这个区间这个点以右的部分的和丢进 set 里，查找一遍最大值就完事了

具体实现可以看代码，u1s1这真的十分好写

```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,l,r,x,a[100010];
multiset<long long>s,res;//s记录区间端点，res记录区间和
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],a[i]+=a[i-1];//通过计算前缀和快速求出区间和
	a[n+1]=a[n];
	res.insert(a[n]);//将整个区间和插入res中
	s.insert(0),s.insert(n+1);//将左右端点插入s中
	for(int i=1;i<=n;i++)
	{
	    cin>>x;
	    auto it=s.lower_bound(x);//找到这个点所在区间
	    r=*it;l=*--it;//求出这个区间的左右端点
	    s.insert(x);//插入断点（新端点）
	    res.erase(res.find(a[r-1]-a[l]));//把原先区间和erase掉
	    res.insert(a[x-1]-a[l]);//插入左区间和
	    res.insert(a[r-1]-a[x]);//插入右区间和
	    cout<<*--res.end()<<'\n';//查询最大值
	}
	return 0;
}
```

彩蛋：这份代码的时间复杂度非常正确，而且也能轻松通过此题，但 set 显然跑不过并查集，于是我喜提本题最劣解（（（

---

## 作者：QuAckB33 (赞：3)

可以用**并查集**经典的时光倒流法（奇妙的叫法）。

题目是一个一个数删除，但由于并查集**只能加边不能减边**，且根据题意并不是强制在线，所以可以考虑**从后往前**一个数一个数加，用数组存储答案再输出。

在此题中，可以在相邻两数间加“边”，这样每组相邻的数看作一个联通分量，用数组 $sum$ 记录每个根节点对应的联通分量里数的总和，加边时更新。

至于取最大值，不用全部遍历一遍，因为每次加数之后最大值**只会增大不会变小**，直接用原来的 $ans$ 与新加的数的根节点所对应的 $sum$ 比较取最大值就可以了。

要注意的细节还是有一些的 OvO，看代码。

代码：



```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long//暴力开long long……
int fa[100010];
int sum[100010];
int a[100010],b[100010];
int anss[100010];
int getfa(int x){
	if(fa[x]!=x){
		fa[x]=getfa(fa[x]);
		return getfa(fa[x]);
	}
	return x;
}//经典并查集的find函数
void merge(int x,int y){
	int a=getfa(x),b=getfa(y);
	if(a==b)return;
	fa[b]=a;
	sum[a]+=sum[b];//将一个节点的sum转移
}//并查集模板加一点改动
signed main(){
	int n;cin>>n;
	for(int i=1;i<=n;++i)cin>>a[i];
	for(int i=1;i<=n;++i)cin>>b[i];
	int ans=0;
	for(int i=n;i>=1;--i){
		fa[b[i]]=b[i];//初始化放这里，方便下面判断数是否已经被加过
		sum[b[i]]=a[b[i]];
		if(fa[b[i]-1])merge(b[i]-1,b[i]);
		if(fa[b[i]+1])merge(b[i]+1,b[i]);//和左右的数建边，只和已经在的数建边
		ans=max(ans,sum[getfa(b[i])]); 
		anss[i]=ans;
	}//这里特别注意b数组的值是a数组下标……
	for(int i=2;i<=n;++i){
		cout<<anss[i]<<endl;
	}
	cout<<0<<endl;
}
```

---

## 作者：xyf007 (赞：2)

- 注意到删除操作是我们不喜欢的。在没有强制在线的情况下，往往可以倒着转化成加入元素。
- 那么加入元素之后就比较好处理了。我们只需要在加入时将它与左右两段所在的并查集合并。
- 维护答案时，由于$a$中元素非负，只需要直接更新$max$。
- 因为是倒序，用一个栈来存储。
- 时间复杂度$O(nlogn)$。
```
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <stack>
using namespace std;
long long n, a[100001], fa[100001], sum[100001], order[100001];
stack<long long> ans;
void checkmax(long long &x, long long y)
{
	if (x < y)
	{
		x = y;
	}
}
long long find(long long x)
{
	if (fa[x] == x)
	{
		return x;
	}
	return fa[x] = find(fa[x]);
}
int main()
{
	scanf("%lld", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%lld", &a[i]);
	}
	for (int i = 1; i <= n; i++)
	{
		scanf("%lld", &order[i]);
	}
	ans.push(0);
	long long maxx = 0;
	for (int i = n; i > 1; i--)
	{
		long long x = order[i];
		if (!fa[x])
		{
			fa[x] = x;
			sum[x] = a[x];
		}
		long long fx = find(x);
		if (x > 1 && fa[x - 1])
		{
			long long fy = find(x - 1);
			if (fx != fy)
			{
				sum[x] += sum[fy];
				sum[fy] = 0;
				fa[fy] = x;
			}
		}
		if (x < n && fa[x + 1])
		{
			long long fy = find(x + 1);
			if (fx != fy)
			{
				sum[x] += sum[fy];
				sum[fy] = 0;
				fa[fy] = x;
			}
		}
		checkmax(maxx, sum[x]);
		ans.push(maxx);
	}
	while (!ans.empty())
	{
		printf("%lld\n", ans.top());
		ans.pop();
	}
	return 0;
}
```

---

## 作者：冽酒灬忄 (赞：2)

这个题我们倒着考虑：每次添加一个数，然后求最大字段和


很显然这个题我们可以用并查集切掉

字段和我们可以用并查集来维护

我们维护一个sum[i]表示以i为父亲的集合的点的和

每次添加一个点就处理他的左右两个点，将他的左右两个点的集合的值都添加进当前节点

由于我们是倒着处理，所以还要倒着输出，由于最后一个值是整个区间的和，所以这个值舍弃掉，同时在最后输出一个0以保证答案的正确



```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[100001],b[100001],f[100001],sum[100001],ans[100001],num,maxx;
long long father(long long x){
	if(x==f[x])
		return x;
	return f[x]=father(f[x]);
}
int main(){
	cin>>n;
	for(long long i=1;i<=n;i++)
		cin>>a[i];
	for(long long i=1;i<=n;i++)
		cin>>b[i];
	for(long long i=n;i>=1;i--){
		long long now=b[i];//now为当前节点
		if(f[now]==0)
			f[now]=now,sum[now]=a[now];
		long long fnow=father(now);
		if(f[now-1]!=0&&now-1>0){//处理左节点
			long long fl=father(now-1);
			if(fnow!=fl){
				sum[now]+=sum[fl];
				sum[fl]=0;//这里一定要清零
				f[fl]=now;
                //将左集合并到当前节点
			}
		} 
		if(f[now+1]!=0&&now+1<=n){//处理右节点
			long long fr=father(now+1);
			if(fnow!=fr){
				sum[now]+=sum[fr];
				sum[fr]=0;//这里一定要清零
				f[fr]=now;
                 //将右集合并到当前节点
			}
		}
		maxx=max(maxx,sum[now]);
        //看一看新的子段是否比以前的最大值还要大
		ans[++num]=maxx; 
	}
	for(long long i=n-1;i>=1;i--)
		cout<<ans[i]<<endl;
	cout<<0<<endl; //很重要的0！
}
```

---

## 作者：让风忽悠你 (赞：1)

[原题](https://www.luogu.com.cn/problem/CF722C)

## 题意

- 给出一个数列并且告诉你每个数被删除的顺序。
- 要求每个数被删除后这个数列的最大子段和。

## 做法

这题的最大子段和显然是要用线段树维护，**大致就是维护区间最大子段和、区间和、区间最大前缀和以及区间最大后缀和**。

- 最大子段和

有两种情况，第一种是在左儿子或者右儿子中取最大值，即取 $max(ms[lson],ms[rson)$，而另外一种则是左右儿子都占一部分，即取左儿子的最大后缀和加上右儿子的最大前缀和。

- 区间和

与最大子段和相似，也有两种情况，这里以区间最大前缀和为例，第一种就是取左儿子的最大前缀和，第二种则是从左端点开始到右儿子的某一个点，即取左儿子的区间和加上右儿子的最大前缀和。
    
------------

而删除操作我们可以将这个点的值赋值为一个极小值，那么此时算上这个数的最大子段和肯定劣于其他子段和。

## 代码

```cpp
#include<cstdio>
#include<algorithm>
#define N 400005 // 线段树要开四倍空间 
#define ll long long // 记得开LL 
#define inf -9e13 // 极小值要开小一点 

using namespace std;

int n,m,opt,x,z;
ll y=inf;
struct node{
	int l,r;
	ll ls,rs,ms,w;
  	// 分别对应区间最大前缀和、区间最大后缀和、区间最大子段和、区间和
}tree[N];

inline void pushup(int k){
	tree[k].w=tree[k*2].w+tree[k*2+1].w;
	tree[k].ls=max(tree[k*2].ls,tree[k*2].w+tree[k*2+1].ls);
	tree[k].rs=max(tree[k*2+1].rs,tree[k*2+1].w+tree[k*2].rs);
	tree[k].ms=max(max(tree[k*2].ms,tree[k*2+1].ms),tree[k*2].rs+tree[k*2+1].ls);
} // 合并操作 

void build(int k,int l,int r){
	tree[k].l=l; tree[k].r=r;
	if(l==r){
		scanf("%lld",&tree[k].w);
		tree[k].ls=tree[k].rs=tree[k].ms=tree[k].w;
		return;
	}
	int mid=(l+r)>>1;
	build(k*2,l,mid);
	build(k*2+1,mid+1,r);
	pushup(k);
} // 建树 

void change(int k){
	if(tree[k].l==tree[k].r){
		tree[k].w=tree[k].ms=tree[k].ls=tree[k].rs=y; 
		return;
	}
	int mid=(tree[k].l+tree[k].r)>>1;
	if(x<=mid) change(k*2);
	else change(k*2+1);
	pushup(k);
}

node query(int k,int x,int y){
	if(x<=tree[k].l && y>=tree[k].r) return tree[k];
	int mid=(tree[k].l+tree[k].r)>>1;
	if(x>mid) return query(k*2+1,x,y);
	if(y<=mid) return query(k*2,x,y);
	else{
		node T,ansl,ansr;
		ansl=query(k*2,x,y); ansr=query(k*2+1,x,y);
		T.w=ansl.w+ansr.w;
        T.ms=max(max(ansl.ms,ansr.ms),ansl.rs+ansr.ls);
        T.ls=max(ansl.ls,ansl.w+ansr.ls);
        T.rs=max(ansr.rs,ansr.w+ansl.rs);
		return T;
	}
} // 求区间最大子段和 

int main(){
	scanf("%d",&n);
	build(1,1,n);
	for(int i=1;i<n;i++){
		scanf("%d",&x);
		change(1);
		printf("%lld\n",query(1,1,n).ms);
	}
	printf("0"); 
	return 0;
}
```


---

## 作者：AC自动机 (赞：1)

## 解题思路

### FBI WARNING ：THIS SOLUTION IS BULL SH\*T！！

 

好吧我们正经做题qwq

我们看到询问最大区间，那么第一反应应该可以想到线段树维护，那我们如何实现快速删除呢？

 

很简单，我们不需要删除。

你想，我们假如要删除一个数，那么我们只需要把他改成-99999999999.....这样一个很小的数，那么我们在统计最大序列时，不可能把他算进去，对吧？ 不然把整个序列都变成负的了23333

所以我们只需要单点修改即可，连查询都不需要写。

维护区间和，最大子序列，从左开头的最大子序列，从右开始的最大子序列，用push_up进行转移就好啦！

ps：注意两个负无穷的数相加的时候特判一下，不要加爆了（雾）。

如果不会用线段树维护最大连续和的童鞋自行百度一下啦~\(≧▽≦)/~


##  代码
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=800400;
const long long INF=-90000000000000LL;
long long ml[maxn],mr[maxn],m[maxn],sum[maxn];
long long n;
inline void read(long long &x){
    x=0; register char ch=getchar();
    while(ch<'0'||ch>'9')ch=getchar();
    while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
}
inline void push_up(int ID){
    if(mr[ID<<1]==INF&&ml[ID<<1|1]==INF){
        m[ID]=max(m[ID<<1],m[ID<<1|1]);
    }
    else m[ID]=max(m[ID<<1],max(m[ID<<1|1],mr[ID<<1]+ml[ID<<1|1]));
    if(sum[ID<<1]==INF&&ml[ID<<1|1]==INF){
        ml[ID]=max(ml[ID<<1],INF);
    }
    else ml[ID]=max(ml[ID<<1],sum[ID<<1]+ml[ID<<1|1]);
    if(sum[ID<<1|1]==INF&&mr[ID<<1]==INF){
        mr[ID]=max(mr[ID<<1|1],INF);
    }
    else mr[ID]=max(mr[ID<<1|1],sum[ID<<1|1]+mr[ID<<1]);
    if(sum[ID<<1]==INF&&sum[ID<<1|1]==INF){
        sum[ID]=INF;
    }
    else sum[ID]=sum[ID<<1]+sum[ID<<1|1];
}
inline void ins(int ID,int nl,int nr,int pos,long long v){
    if(nl==nr){
        sum[ID]=ml[ID]=mr[ID]=m[ID]=v;
        return;
    }
    int m=(nl+nr)>>1;
    if(m>=pos)ins(ID<<1,nl,m,pos,v);
    else ins(ID<<1|1,m+1,nr,pos,v);
    push_up(ID);
}
int main(){
    read(n);
    register long long temp;
    for(register int i=1;i<=n;i++){
        read(temp);
        ins(1,1,n,i,temp);
    }
    int p;
    for(register int i=1;i<n;i++){
        cin>>p;
        ins(1,1,n,p,INF);
        long long ans=max(m[1],max(ml[1],mr[1]));
        cout<<ans<<endl;
    }
    cin>>p;
    cout<<0<<endl;
}
```

---

## 作者：XL4453 (赞：0)

注意删除数后数的位置还是空的。

---
### 解题思路：

正过来不是太好想，考虑反过来做，也就是加点算最长。

这样的作用就是这个操作结束后答案只有可能是上一次的答案或者是这一次更改后的新答案。否则正过来做的话可能会从奇怪的地方蹦出一个答案什么的，不太方便。

然后具体考虑如何维护。

注意到每一个值都是非负的，所以每一次添加后，连成的一个整区间一定是一个不劣于包含这个区间的最大答案的结果。所以每一次只需要连成的两个区间连起来就行了。用并查集维护就行了。

---
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
#define int long long
int fa[100005],n,a[100005],book[100005],b[100005],ans[100005],pri[100005];
int find(int now){
	if(fa[now]==now)return now;
	return fa[now]=find(fa[now]);
}
signed main(){
	scanf("%I64d",&n);
	for(int i=1;i<=n;i++)scanf("%I64d",&a[i]);
	for(int i=1;i<=n;i++)scanf("%I64d",&b[i]);
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=n;i>=1;i--){
		book[b[i]]=1;
		ans[b[i]]=a[b[i]];
		if(book[b[i]-1]){
			ans[b[i]]+=ans[find(b[i]-1)];
			fa[find(b[i]-1)]=fa[b[i]];
		}
		if(book[b[i]+1]){
			ans[b[i]]+=ans[find(b[i]+1)];
			fa[find(b[i]+1)]=fa[b[i]];
		}
		pri[i]=max(ans[b[i]],pri[i+1]);
	}
	for(int i=2;i<=n+1;i++){
		printf("%I64d\n",pri[i]);
	}
	return 0;
}
```


---

## 作者：_HMZ_ (赞：0)

## 解题思路：

这题带一个删除，但是如果把删除改为赋值成 $-\text{INF}$ 就变成维护最大子段和了。

看见各位大佬都是用的并查集，其实用线段树也可以维护。

定义如下结构体：


```
struct node
{
	int l,r,mid,sum;
};
```

$l$ 代表以最左边为起点的最大子段和，$r$ 同理。$mid$ 即为当前最大子段和。

$sum$ 应该不用解释了吧……

每次合并两个区间的时候，当前的 $l$ 只有两种情况。

可以整个左边的区间都选，再加上右区间的 $l$。

否则选取左区间的 $l$。

当前 $r$ 同理。

当前的 $mid$ 即为左/右子树的 $mid$，或者是左子树的 $r$ 合并右子树的 $l$。

注意，十年 OI 一场空，不开 long long 见祖宗。

## AC代码：

```cpp
#include<iostream>
using namespace std;
#define int long long
const int INF=0x3fffffffffff;
int n,val[1000005],del[1000005],ans[1000005];
struct node
{
    int l,r,mid,sum;
}tree[1000005];
node merge(node x,node y)//上文提到的合并
{
    node tmp={max(x.l,x.sum+y.l),max(y.r,y.sum+x.r),max(max(x.mid,y.mid),x.r+y.l),max(x.sum+y.sum,-INF)};//这里 sum 要取一个 max 是因为很多个 -INF 加起来会爆掉 long long。
    return tmp;
}
void build(int now,int l,int r)
{
    if(l==r)
    {
        tree[now].sum=val[l];
        tree[now].l=tree[now].r=tree[now].mid=max(val[l],0ll);
        return;
    }
    int mid=(l+r)/2;
    build(now*2,l,mid);
    build(now*2+1,mid+1,r);
    tree[now]=merge(tree[now*2],tree[now*2+1]);
}
void update(int now,int l,int r,int x,int w)//每次删除一个数字，就将其赋值为 -INF。
{
    if(l>x || r<x)
        return;
    if(l==x && r==x)
    {
        tree[now].sum=w;
        tree[now].l=tree[now].r=tree[now].mid=max(w,0ll);
        return;
    }
    int mid=(l+r)/2;
    update(now*2,l,mid,x,w);
    update(now*2+1,mid+1,r,x,w);
    tree[now]=merge(tree[now*2],tree[now*2+1]);
}
signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>val[i];
    build(1,1,n);
    for(int i=1;i<=n;i++)
    {
        int u;
        cin>>u;
        update(1,1,n,u,-INF);
        cout<<tree[1].mid<<endl;//最后输出的时候就输出 1 到 n 的最大子段和（即为第一个区间的最大子段和）。
    }
    return 0;
}
```


---

## 作者：Plozia (赞：0)

宣传博客->[link](https://blog.csdn.net/BWzhuzehao/article/details/113766310)

根据目前作者了解，本题有两种解法：并查集/线段树。

# 1. 并查集

对于并查集这种只能合并不能删除的数据结构，当然要想一点珂技。

我们倒过来思考，将删除操作变为插入操作，相邻点合并。

考虑到序列里面的数都为正数，那么直接取出子树权值和最大的即可。

预计时间复杂度 $O(n)$，上界 $O(n \log n)$。

# 2. 线段树

这个需要模仿 GSS 系列，维护前缀和，后缀和，总和，最大子段和，然后删除操作处理成最小值。**这个方法支持数为负数的情况。**

没了解过 GSS 系列的读者可以看一看这篇文章：[线段树算法总结&专题训练3](https://blog.csdn.net/BWzhuzehao/article/details/111566557)

时间复杂度 $O(n \log n)$，上下界也为 $O(n \log n)$。

代码：（只有线段树）

```cpp
#include <bits/stdc++.h>
#define Max(a, b) ((a > b) ? a : b)
using namespace std;

typedef long long LL;
const int MAXN = 1e5 + 10;
const LL inf = -1e14;
int n, a[MAXN];
struct node
{
	int l, r, flag;
	LL sum, pre, aft, maxn;
	#define l(p) tree[p].l
	#define r(p) tree[p].r
	#define s(p) tree[p].sum
	#define p(p) tree[p].pre
	#define a(p) tree[p].aft
	#define m(p) tree[p].maxn
	node operator +(const node &fir)
	{
		node sec;
		sec.l = l; sec.r = fir.r;
		sec.sum = sum + fir.sum;
		sec.pre = Max(pre, sum + fir.pre);
		sec.aft = Max(fir.aft, fir.sum + aft);
		sec.maxn = Max(fir.maxn, Max(maxn, aft + fir.pre));
		sec.flag = flag | fir.flag;
		return sec;
	}
}tree[MAXN << 2];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	while (ch < '0' || ch > '9') {if (ch == '-') fh = -1; ch = getchar();}
	while (ch >= '0' && ch <= '9') {sum = (sum << 3) + (sum << 1) + (ch ^ 48); ch = getchar();}
	return sum * fh;
}

void build(int p, int l, int r)
{
	l(p) = l, r(p) = r;
	if (l == r) {s(p) = a(p) = p(p) = m(p) = a[l]; tree[p].flag = 1; return ;}
	int mid = (l + r) >> 1;
	build (p << 1, l, mid); build(p << 1 | 1, mid + 1, r);
	tree[p] = tree[p << 1] + tree[p << 1 | 1];
}

void deal(int p, int x)
{
	if (l(p) == r(p) && r(p) == x)
	{
		tree[p].flag = 0;
		s(p) = m(p) = a(p) = p(p) = inf;
		return ;
	}
	int mid = (l(p) + r(p)) >> 1;
	if (x <= mid) deal(p << 1, x);
	else deal(p << 1 | 1, x);
	tree[p] = tree[p << 1] + tree[p << 1 | 1];
}

int main()
{
	n = read();
	for (int i = 1; i <= n; ++i) a[i] = read();
	build(1, 1, n);
	for (int i = 1; i <= n; ++i)
	{
		int x = read();
		deal(1, x);
		printf("%lld\n", Max(0ll, tree[1].maxn));
	}
	return 0;
}
```

---

## 作者：huangxianghui (赞：0)

不得不提一句：我的并查集真的诡异……
# 题目大意
一个序列，每次摧毁序列后求最大连续子段和。
# solution
并查集是不能拆的，那就把过程倒过来，再逆序输出。

把整个过程倒回来，变成每次恢复一个数，然后求连续子段和，这就可以用并查集维护，每次恢复一个数，然后把两边相邻的数（如果有的话）用并查集连起来，然后把答案归并，最后max一下就可以了

代码如下：
```
#include<bits/stdc++.h>//4321894712308947123908471238904
#define f(i,a,b) for (int i=a;i<=b;i++)//41234132412341234
#define ll long long
using namespace std;
const int maxn=1e5+10;
ll n;
ll f[maxn];
ll a[maxn],b[maxn];
ll ans[maxn],ans1;
inline ll read()
{
	ll l=0,f=1;
	char c=getchar();
	while (c<'0' || c>'9')
	{
		if (c=='-') f=-1;
		c=getchar();
	}
	while (c>='0' && c<='9') l=(l<<3)+(l<<1)+(c^48),c=getchar();
	return l*f;
}
int find(int x)
{
	if (f[x]!=x) return f[x]=find(f[x]);
	return x;
}
int main()
{
	n=read();
	f(i,1,n) a[i]=read();
	f(i,1,n) b[i]=read();
	for (int i=n; i>=1; i--)
	{
		int y=b[i];
		ans[i]=ans1,f[y]=y;
		if (f[y-1])//前后合并
		{
			int x=find(y-1);
			a[y]+=a[x],f[x]=f[y];
		}
		if (f[y+1])
		{
			int x=find(y+1);
			a[y]+=a[x],f[x]=f[y];
		}
		ans1=max(ans1,a[y]);
	}
	f(i,1,n) cout<<ans[i]<<endl;
}
```


---

## 作者：MuYC (赞：0)

#### 前言

或许我们可以称这道题为:动态最大子段和

#### 做法

删点实在是不容易处理。

不妨离线后转化为加点。

题目标签带有并查集，但是实际上我们观察到，$a_i<=10^9$，你看这个数据显然就很小（大雾

为什么我说数据给得很小？因为它相对于$-10^{14}$来说实在太小了。

所以，我们不妨将一开始的序列全部初始化为$-10^{14}$，加入一个数就相当于单点修改。如果两个地方没有联通，显然它们也不会选择中间的$-10^{14}$。

所以，这个题目直接丢线段树维护最大子段和板子即可，不需要用并查集维护什么“连通性”。

$Don't$ $stop$ $thinking$ $, the$ $man$ $who$ $stop$ $thinking$ $will$ $hardly$ $be$ $successful$

#### Code:

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 100005,INF = 100000000000000;

int a[MAXN],n;
int Ans[MAXN];

struct Segment {
	int l,r,lmax,rmax,dat,sum;
	int laz;
} T[MAXN * 4];

struct AD {
	int x,data;
} Q[MAXN];

void build(int x,int l,int r)
{
	T[x].l = l , T[x].r = r;
	T[x].lmax = T[x].rmax = T[x].dat = T[x].sum = -INF;
	T[x].laz = -INF;
	if(l == r)return ;
	int mid = (l + r) >> 1;
	build(x << 1 , l , mid);
	build(x << 1 | 1 , mid + 1 , r);
	T[x].sum = T[x << 1].sum + T[x << 1 | 1].sum;
	return ;
}

void ad(int x,int k)
{
	T[x].lmax = T[x].rmax = T[x].dat = T[x].sum = k;
	T[x].laz = k;
}

void pushdown(int x)
{
	if(T[x].laz == -INF)return ;
	ad(x << 1 , T[x].laz);
	ad(x << 1 | 1 , T[x].laz);
	T[x].laz = -INF;
	return ;
}

void change(int x,int pos,int k)
{
	if(T[x].l >= pos && T[x].r <= pos){ad(x,k);return ;}
	int mid = (T[x].l + T[x].r) >> 1;
	pushdown(x);
	if(pos <= mid)change(x << 1 , pos , k);
	else change(x << 1 | 1 , pos , k);
	T[x].sum = T[x << 1].sum + T[x << 1 | 1].sum;
	T[x].lmax = max(T[x << 1].lmax,T[x << 1].sum + T[x << 1 | 1].lmax);
	T[x].rmax = max(T[x << 1 | 1].rmax,T[x << 1 | 1].sum + T[x << 1].rmax);
	T[x].dat=max(max(T[x << 1].dat, T[x << 1 | 1].dat), T[x << 1].rmax + T[x << 1 | 1].lmax);
	return ;
}

signed main()
{
	cin >> n;
	for(int i = 1 ; i <= n ; i ++)cin >> a[i];
	for(int i = 1 ; i <= n ; i ++)
	{
		cin >> Q[i].x;
		Q[i].data = a[Q[i].x];
	}
	Ans[n] = 0;
	build(1,1,n);
	for(int i = n ; i >= 2 ; i --)
	{
		change(1,Q[i].x,Q[i].data);
		Ans[i - 1] = T[1].dat;
	}
	for(int i = 1 ; i <= n ; i ++)cout << Ans[i] << endl;
	return 0;
}
```

---

## 作者：H_D_NULL (赞：0)

- 显而易见，操作顺序离线给出，每次操作都输出当前答案，所以选择将删除操作改为倒着插入；

- 如何快速插入、判断连续序列并找最大连续序列和？毫无疑问，肯定需要数据结构的支持。因为每一个连续子序列之间互相独立，所以要用多个独立且可合并的子数据结构，很容易想到并查集；


------------


- ### 区间并查集

- 区间并查集只是一种处理区间连续段合并的技巧，和普通并查集基本没有区别。其核心是将连续的一段区间视作一个并查集；

- 如上每插入一个点时，将其视作一个独立的并查集。如果其左边一位已经插入，则左边一定属于一个并查集（有可能大小为一），因为它们连续，所以合并这两个并查集，对右边一位同理。插入一个点不会影响整个序列中其他段的连续，所以每一次插入可以用两次并查集合并操作达到维护所有子序列连续的目的；

- 区间并查集往往还附带权值的查询，但是对于本题，对于一个连续子序列，只需要求它的权值和，所以只要定义一个 $v$ 变量，每次合并时更新根节点就行了。为了方便，我们每次合并时将连续子序列的左端点定义为根节点（本题用不上），方便进行更深层次的操作。



------------

*Talk is cheap, show me the code*

```cpp
#include<bits/stdc++.h>
#define re register
#define N 100005
#define int long long
using namespace std;

inline int read(){
	re int ret=0;
	re char c=getchar();
	while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9') ret=(ret<<1)+(ret<<3)+c-'0',c=getchar();
	return ret;
}

int n,ma;
int v[N];
int fa[N];
int qu[N];
int ans[N];

bool vis[N]; //特别鸡肋，只是蒟蒻为了防止出错设的，其实可以只用fa数组

int getfa(int x){
	return fa[x]==x?x:fa[x]=getfa(fa[x]);
}

inline void merge(int x,int y){
	x=getfa(x); y=getfa(y);
	if(x==y) return;
	v[x]+=v[y];
	fa[y]=x;
}

signed main(){
	n=read();
	for(re int i=1;i<=n;i++) v[i]=read(),fa[i]=i;
	for(re int i=1;i<=n;i++) qu[i]=read();
	for(re int i=n;i;i--){
		ans[i]=ma;
		if(vis[qu[i]-1]) merge(qu[i]-1,qu[i]);
		if(vis[qu[i]+1]) merge(qu[i]+1,qu[i]);
		ma=max(ma,v[getfa(qu[i])]);
		vis[qu[i]]=1;
	}
	for(re int i=1;i<=n;i++) printf("%lld\n",ans[i]);
	return 0;
}
```



---

## 作者：fls233666 (赞：0)

首先显而易见的是，直接操作是 $O(n^2)$ 的，肯定过不去，要另外想办法。

仔细观察发现，我们可以用类似于 [P1197 星球大战](https://www.luogu.com.cn/problem/P1197) 的思想，采用逆向思维。**将每次的删除操作变成增加操作**，我们发现题目简单了很多。

变成增加操作后，我们要考虑如何维护和最大的子序列。

我们发现**这题中的 $a_i$ 都是非负数**。这是一个极好的性质。这意味着我们只要**比较所有未被删除的位置连续的子序列上所有数的和，找到最大值**即可。

那么如何维护每次增加操作后未被删除的位置连续的子序列上的和呢？

这个时候就要用到**并查集**了。

具体的方法是，**每次新加入一个位置上的数时，我们检查这个位置的左右两边的数是否已经在之前被加入。如果有，则把左边或右边的数合并到这个位置上面，并比较大小更新答案。**

值得注意的是，如果加入一个数，这个数的左边和右边的数都还没有被加入，那么这个数自己本身也构成一个子序列，也要比较大小更新答案。

那么本题的思路到此为止，下面是代码实现：

```cpp
#include<iostream>
#include<cstdio>
#define ll long long
#define qmx(a,b) a<b?b:a
#define rgt register int
using namespace std;
const int mxn = 1e5+5;
int n,fa[mxn],del[mxn];
//del记录每个位置被删除的顺序
bool use[mxn];   //use记录一个位置是否已经被加入回数组中
ll num[mxn],mx,ans[mxn];

int fd(int px){
	return fa[px]==px?px:fa[px]=fd(fa[px]); 
}   //并查集查找函数【有路径压缩】

int main(){
	scanf("%d",&n);
	for(rgt i=1;i<=n;i++){
		scanf("%lld",&num[i]);
		fa[i]=i;  //并查集初始化
	}
	for(rgt i=1;i<=n;i++)
		scanf("%d",&del[i]);
        //数据读入
        
	for(rgt f1,f2,i=n;i>1;i--){  //倒序操作
    
		use[del[i]]=true;  //打上标记
		f2=del[i];
        
		if(use[del[i]-1]){  //合并左边
			f1=fd(del[i]-1);
			fa[f1]=f2;
			num[f2]+=num[f1];
		}
        
		if(use[del[i]+1]){  //合并右边
			f1=fd(del[i]+1);
			fa[f1]=f2;
			num[f2]+=num[f1];
		}
        
		mx=qmx(num[f2],mx);  //比大小
		ans[i-1]=mx;  //更新答案
        
	}
    
	for(rgt i=1;i<=n;i++)
		printf("%lld\n",ans[i]);   //输出结果
        
	return 0;
}
```


---

## 作者：X2H_tato (赞：0)

**题目大意**
- 给你n个正数以及一个排列 让你按照排列中的顺序依次摧毁这n个数 每摧毁一次求一下连通块的最大和

**思路**
- 倒着并查集：先将所有点摧毁，再倒序连接，维护最大和。

**这里是~~简单的~~代码：**
```cpp
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int Max=1e5+10;
ll a[Max],ans[Max],sum[2*Max]={0};
int b[Max],n,f[2*Max];
bool des[Max]={0};
void init()
{
    for(int i = 1; i <= n; ++i) {
        f[i]=f[i+n]=i+n;
    }
}
int findset(int u)
{
    return u==f[u]?u:f[u]=findset(f[u]);
}
int main()
{
    scanf("%d",&n);
    for(int i = 1; i <= n; ++i) {
        scanf("%I64d",&a[i]);
        sum[i+n]=a[i];
    }
    for(int i = 1; i <= n; ++i) {
        scanf("%d",&b[i]);
    }
    init();
    ll maxn=0;
    for(int i = n; i > 1; --i) {
        int index=b[i];
        des[index]=1;
        if(des[index-1]) {
            int _y=findset(index),_x=findset(index-1);
            f[_x]=_y;
            sum[_y]+=sum[_x];
            if(des[index+1]) {
                int _yy=findset(index+1);
                f[_y]=_yy;
                sum[_yy]+=sum[_y];
                maxn=max(maxn,sum[_yy]);
            }
            maxn=max(maxn,sum[_y]);

        }
        else if(des[index+1]) {
            int _x=findset(index),_y=findset(index+1);
            f[_x]=_y;
            sum[_y]+=sum[_x];
            maxn=max(maxn,sum[_y]);
        }
        else {
            maxn=max(maxn,a[index]);
        }
        ans[i-1]=maxn;
    }
    for(int i = 1; i <= n; ++i) {
        printf("%I64d\n",ans[i]);
    }
    return 0;
}

```



---

