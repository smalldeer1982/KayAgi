# Unique Array

## 题目描述

You are given an integer array $ a $ of length $ n $ . A subarray of $ a $ is one of its contiguous subsequences (i. e. an array $ [a_l, a_{l+1}, \dots, a_r] $ for some integers $ l $ and $ r $ such that $ 1 \le l < r \le n $ ). Let's call a subarray unique if there is an integer that occurs exactly once in the subarray.

You can perform the following operation any number of times (possibly zero): choose an element of the array and replace it with any integer.

Your task is to calculate the minimum number of aforementioned operation in order for all the subarrays of the array $ a $ to be unique.

## 说明/提示

In the second test case, you can replace the $ 1 $ -st and the $ 3 $ -rd element, for example, like this: $ [3, 4, 1, 4] $ .

In the third test case, you can replace the $ 4 $ -th element, for example, like this: $ [3, 1, 2, 3, 2] $ .

## 样例 #1

### 输入

```
4
3
2 1 2
4
4 4 4 4
5
3 1 2 1 2
5
1 3 2 1 2```

### 输出

```
0
2
1
0```

# 题解

## 作者：jiazhichen844 (赞：19)

题意：定义一个数组 $a_1,a_2,\cdots,a_n$ 是合法的当且仅当对于所有子区间 $[l,r]$，都存在一个数 $x$，满足 $x$ 在 $a_l,a_{l+1},\cdots,a_r$ 中只出现一次，给定一个数组，求至少替换多少个元素，才可以使数组合法。



首先，一个显然的策略，设把 $a_x$ 替换成 $y$，则 $y$ 两两不同且不在原数组中出现，此时，对于 $l\in[1,x],r\in[x,n]$ 的所有子区间都会合法，相当于把原数组从 $x$ 下标处断开。



所以，题意可以理解为，至少分成多少段，使得每段均合法（段与段之间有 $1$  的空隙）。



此时，有一个显然的贪心，从头扫到尾，若扫到一个前缀不合法，就把这个前缀断开，去掉结尾，分成一段。



证明也是显然的，首先，不可能延后断开位置，这样会使其不合法，若提前了断开的位置，相当于给后面的前缀前面插入若干数，这样不会新前缀的断开位置变优。



然后，我们考虑如何判断一段前缀是否合法。



注意到，若扫到了 $[pre,r]$，且 $[pre,r-1]$ 时均未断开，则只需判断满足 $l\in[pre,r]$ 的 $[l,r]$ 的合法情况，用一个数据结构维护每个 $l$ 是否合法（即 $[l,r]$ 中只出现一次的数的个数），若加入一个数 $x$，前面一个 $x$ 在位置 $t1_x$，前面倒数第二个 $x$ 在位置 $t2_x$，则可以区间 $(t2_x,t1_x]$ 减 $1$，区间 $(t1_x,r]$ 加 $1$，查询是否合法也只需查询区间 $[pre,r]$ 最小值，如果为 $0$ 则不合法，令 $pre$ 赋值为 $r+1$，答案 $+1$ 即可。



数据结构就用一个区间加，求区间 $\min$ 的线段树就行。



代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct segment_tree
{
	int l,r,lazy,minn;
}a[1200005];
int b[300005];
const int inf=0x3f3f3f3f;
void build(int pos,int l,int r)
{
	a[pos]={l,r,0,0};
	if(l==r)
		return;
	int mid=l+r>>1;
	build(2*pos,l,mid);
	build(2*pos+1,mid+1,r);
}
void update(int pos)
{
	a[pos].minn=min(a[2*pos].minn,a[2*pos+1].minn);
}
void putlazy(int pos,int x)
{
	a[pos].lazy+=x;
	a[pos].minn+=x;
}
void pushdown(int pos)
{
	putlazy(2*pos,a[pos].lazy);
	putlazy(2*pos+1,a[pos].lazy);
	a[pos].lazy=0;
}
void add(int pos,int l,int r,int x)
{
	if(r<a[pos].l||l>a[pos].r||l>r)
		return;
	if(l<=a[pos].l&&r>=a[pos].r)
	{
		putlazy(pos,x);
		return;
	}
	pushdown(pos);
	add(2*pos,l,r,x);
	add(2*pos+1,l,r,x);
	update(pos);
}
int getmin(int pos,int l,int r)
{
	if(r<a[pos].l||l>a[pos].r)
		return inf;
	if(l<=a[pos].l&&r>=a[pos].r)
		return a[pos].minn;
	pushdown(pos);
	return min(getmin(2*pos,l,r),getmin(2*pos+1,l,r));
}
int t1[300005],t2[300005];
void test()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>b[i];
	for(int i=1;i<=n;i++)
		t1[i]=t2[i]=0;
	build(1,1,n);
	int pre=1,cnt=0;
	for(int i=1;i<=n;i++)
	{
		add(1,t2[b[i]]+1,t1[b[i]],-1);
		add(1,t1[b[i]]+1,i,1);
		t2[b[i]]=t1[b[i]];
		t1[b[i]]=i;
		if(getmin(1,pre,i)==0)
		{
//			cout<<i<<" ";
			cnt++;
			pre=i+1;
		}
	}
	cout<<cnt<<"\n";
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin>>t;
	for(int i=1;i<=t;i++)
		test(); 
}
```

---

## 作者：_LSA_ (赞：6)

我们先探究如何判断 $1$ 到 $i$ 的任意子数组是否合法。

考虑一个数 $a_i$ 在哪些子数组中是唯一出现的。

记 $lst_{a_i}$ 表示 $a_i$ 上一个出现的位置，$nxt_{a_i}$ 表示 $a_i$ 下一个出现的位置。

显然当子数组的左端点 $l \in ( lst_{a_i},i]$ 并且右端点 $r \in [i,nxt_{a_i})$ 时，$a_i$ 是唯一出现的。

我们从 $1$ 到 $n$ 扫描，假设当前已经扫描到 $i$，由于我们每次往序列右端增加一个数，所以我们只需考虑如何判断以 $i$ 为右端点的子数组是否合法。

根据上面的结论，我们很容易发现对于一个 $a_j$，当 $nxt_{a_j} < i$，左端点 $l \in (lst_{a_j},j]$ 时合法。

那么我们可以开一棵线段树，每个叶子节点 $j$ 维护左端点为 $j$ 时，$j$ 到当前位置 $i$ 中有多少个数是唯一出现的。

记 $a_i$ 上上次出现的位置为 $llst_{a_i}$，当我们扫描到 $a_i$ 时，$l \in (llst_{a_i},lst_{a_i}]$，$r=i$ 的 $a_i$ 不再唯一，所以我们对这段区间区间 $-1$，而对于 $l \in (lst_{a_i},i]$，$r=i$ 中 $a_i$ 唯一，故我们对这段区间 $+1$。

显然存在 $j \in[1,i]$，线段树上 $j$ 所在叶节点的权值为 $0$ 时是不合法的，线段树维护区间最小值即可。

这时我们就得进行一次修改操作，显然将 $a_i$ 变为序列中没有出现的数是最优的，因为这样不仅使前 $i$ 个数构成的序列合法，还使得任意 $l \in [1,i],r \in [i+1,n]$ 都是合法的。反映到线段树上就是区间 $[1,i]$ 进行 $+1$ 操作，并使得答案 $+1$。

然后这题就做完了。

时间复杂度 $O(n \log n)$。

```cpp

const int N = 3e5+10;
const int inf = 1e9;
int n,a[N];
int t[N<<2],tag[N<<2];
#define ls rt<<1
#define rs rt<<1|1
inline void push_up(int rt){
	t[rt] = min(t[ls],t[rs]);
}
void build(int rt,int l,int r){
	t[rt] = tag[rt] = 0;
	if(l == r){
		return ;
	}
	int mid = (l+r)>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
}
inline void change(int rt,int d){
	t[rt] += d;
	tag[rt] += d;
}
inline void push_down(int rt){
	if(tag[rt]){
		change(ls,tag[rt]);
		change(rs,tag[rt]);
		tag[rt] = 0;
	}
}
void update(int rt,int l,int r,int ql,int qr,int d){
	if(ql <= l && r <= qr){
		change(rt,d);
		return ;
	}
	push_down(rt);
	int mid = (l+r)>>1;
	if(ql <= mid) update(ls,l,mid,ql,qr,d);
	if(qr >  mid) update(rs,mid+1,r,ql,qr,d);
	push_up(rt); 
}
int query(int rt,int l,int r,int ql,int qr){
	if(ql <= l && r <= qr) return t[rt];
	push_down(rt);
	int mid = (l+r)>>1,res = inf;
	if(ql <= mid) res = min(res,query(ls,l,mid,ql,qr));
	if(qr >  mid) res = min(res,query(rs,mid+1,r,ql,qr));
	return res;
}
int lst[N],llst[N];
int main(){
	int T = read();
	while(T--){
		n = read();
		for(int i=1;i<=n;i++) a[i] = read(),lst[i] = llst[i] = 0;
		build(1,1,n);
		int ans = 0;
		for(int i=1;i<=n;i++){
			if(!lst[a[i]]) update(1,1,n,1,i,1),llst[a[i]] = 1,lst[a[i]] = i;
			else update(1,1,n,llst[a[i]],lst[a[i]],-1),update(1,1,n,lst[a[i]]+1,i,1),llst[a[i]] = lst[a[i]]+1,lst[a[i]] = i;
			if(query(1,1,n,1,i) == 0) ans++,update(1,1,n,1,i,1);
		}
		cout << ans << "\n";
	}
	return 0;
}
```

---

## 作者：FerventTemp0 (赞：5)

逆天做法，博君一乐。

首先，考虑如果只给一个数组，让我们判断这个数组是否 good，怎么做。

这里有一个大暴力，每次选择一个 unique 的数，然后把这个数删掉，原数组变成两个子数组，然后对两个子数组进行递归。复杂度喜提 $O(n^2)$，光判一个就都已经跑不过去了（叉满考虑一个 $a_i=i$，然后得到一个类似快排的退化情况）。

考虑优化，每次选择最接近中间的 unique 的数，这样复杂度就很对了，变成每个 $O(n\log n)$。考虑 unique 的结构，一个 unique 的数被删掉之后，无法在更中心创造出一个新的 unique 的数。所以每次要么几乎对半切开，要么整个死掉，要么没切几层就直接退回去了，所以复杂度是对的（比较难证，感性理解就行了）。

这里有一个实现细节，你需要很快的对每个元素计数，并且支持 $O(1)$ 的均摊清空，你直接 memset 整个 cnt 就直接挂飞了，此时有一个很聪明的办法就是你直接枚举那个区间的数然后直接减回去，复杂度就成功均摊到计数的时候了。

接下来，好数组很显然是有单调性的，所以考虑二分查找下一个我要断开的点（一发修改过去直接改成一个从来没出现过的数，相当于把原数组断开了），然后复杂度就是每一个断点 $O(n\log^2 n)$，整个 $O(n^2\log^2n)$，很显然不可行。

有一个很好用的东西叫做倍增二分查找，这个可以避免你一下子就询问很右边的东西，被查询的总长度不会超过下一个的距离乘以一个常数。这样分析下来直接消掉一整只 $n$，复杂度到达 $O(n\log^2 n)$，稍微卡卡常就可以通过（指交一整页）。

代码：
```
#include <iostream>
#include <vector>
#pragma GCC optimize("Ofast","inline","-ffast-math")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")
 
using namespace std;
 
int arr[300001],Q[300001];
bool isGoodVector(int start,int end) {
   if(end<=start+1)
      return true; 
   for(int i=start;i<end;++i)
      arr[Q[i]]++;
   int center=(start+end)/2;
   int uniqueElement=-1;
   for(int i=start;i<end;++i)
      if(arr[Q[i]]==1)
         if(abs(i-center)<=abs(uniqueElement-center)||uniqueElement==-1)
            uniqueElement=i;
   for(int i=start;i<end;++i)
      arr[Q[i]]=0;
   if(uniqueElement==-1)
      return false;
   return isGoodVector(start,uniqueElement)&&isGoodVector(uniqueElement+1,end);
}
int nxt(int l,int r) {
   int index=l-1;
   int jump=1;
   while(jump>0) {
      int nextIndex=index+jump;
      if(nextIndex>=r||!isGoodVector(l,nextIndex)) jump/=2;
      else {
         index=nextIndex;
         jump*=2;
      }
   }
   if(index==r-1)
   if(isGoodVector(l,r))
      return r;
   return index;
}
int main() {
   ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
   int t;
   cin >> t;
   while (t--) {
      int n;
      cin >> n;
      for(int i=0;i<n;++i)
         cin >> Q[i];
      int count=0;
      int lastModifiedIndex=-1;
      while(true) {
         int nextIndex=nxt(lastModifiedIndex+1,n);
         if(nextIndex==n)
            break;
         Q[nextIndex]=-count;
         lastModifiedIndex=nextIndex;
         count++;
       }
       cout << count << endl;
   }
   return 0;
}
```
-----
彩蛋，为保护隐私，已对当事人打码。

![](https://cdn.luogu.com.cn/upload/image_hosting/xpwaqww0.png)

比赛的时候我把思路发给 GPT 直接让 GPT 写代码了，然后 GPT 开了个 `arr[300000]` 越界了一位给我干 FST 了，很高手。

[这里是 GPT 的代码](https://codeforces.com/contest/1969/submission/258768973)，加了注释，看过了复杂性和正确性都没问题的，就是常数太大了。可读性比我写的好很多，如果看不懂题解的话可以试试读读 GPT 的代码。

---

## 作者：聪明的乖宝宝 (赞：3)

贪心+线段树
## 思路
### 贪心部分
首先，显然如果我们改变以个数字，一定是把这个数字改成一个数组中不存在的数字是最优解

其次，假设数组的 $1$ 到 $i-1$ 个数字全部符合题意，即子序列 $a_1,a_2,{\dots}a_{i-1}$ 中的任意子序列均包含一个唯一数，而到了 $a_i$ ，如果开始不符合题意，则一定出现了一个子序列 $a_k,a_{k+1},\dots,a_i$ 不符合题意，这种情况当且仅当子序列 $a_k,a_{k+1},\dots,a_{i-1}$ 的唯一数为 $a_i$ ，这时在不改变前 $i-1$ 个数字的前提下，一定要对 $a_i$ 进行修改，才能保证最终结果符合题意

那么，为什么不考虑对前 $i-1$ 个数进行修改捏？
假设 $0<k<i-1$ ，如果我们对 $a_k$ 进行修改，会产生的结果是所有包含 $a_k$ 的子序列均符合题意，这些子序列分为两部分，一种是不包含 $a_i$ 的子序列，显然，这些子序列原本就符合题意，故这些影响可以视为不存在，而另一部分包含 $a_i$ 的子序列，在修改 $a_i$ 之后，也可以均符合题意，且由于 $k<i$ 会存在一部分子序列，在 $a_i$ 修改之后符合题意，而修改 $a_k$ 对其无影响，故贪心，修改 $a_i$ 一定比修改 $a_k$ 更优。
### 线段树部分
根据贪心，我们的出结论，可以从左向右搜索，如果遇到一个 $i$ 使得 $a_1,a_2,\dots,a_i$ 中存在子序列不满足题意，那么修改 $a_i$ ，答案加加，可以考虑用线段树维护（也不一定一定要用线段树~~但我也想不到用其他方式~~）

依旧假设当前处理的数字是第 $i$ 个，维护一个数组 $c$ 
令 $c_k$ 表示从子序列 $a_k,a_{k+1},\dots,a_i$ 中唯一的数的个数

举个例子：
假设当前处理到第 $5$ 个数
令 $a$ 数组的前五个元素为
 $$
1,3,2,3,1
$$ 
那么对应的 $c$ 数组为
 $$
1,2,3,2,1
$$ 
因为在 $a_1,a_2,\dots,a_5$ 这个子序列中只有一个唯一数 $1$ ，故 $c_1=1$ 

至于 $c$ 数组该如何维护呢？
通过观察我们不难发现，假设 $a_i=x$ ，如果 $a_k,a_{k+1},\dots,a_{i-1}$ 中没有出现过 $x$ ，那么显然， $c_k,c_{k+1},\dots,c_i$ 的值均加 $1$ ，而如果在此情况下， $a_{k-1}=x$ ，那么之前因包含 $a_{k-1}$ ，而存在一个唯一数 $x$ 的区间，在拓展到第 $i$ 位之后，唯一数均减 $1$ ，事实上通过观察，这个减 $1$ 的范围是 $a_{w+1},a_{w+2},\dots,a_{k-1}$ ，其中 $w$ 表示在 $k$ 之前 $x$ 里 $k$ 位置最近的 $x$ 的位置

现在有了 $c$ 数组，判断拓展到第 $i$ 位是数组是否出现非法就容易了，我们只需要判断是否存在 $c_k=0$ ，其中 $k<i$ ，就可以了，而显然， $c$ 中元素永远不小于 $0$ ，故，只需要求区间最小值，即可判断是否 $c_k=0$ 

如果确定了 $a_i$ 必须修改，那么只需修改 $a_i$ 后重新维护一下 $c$ 就可以了

那么我们只需要一个支持区间修改以及求区间最值的数据结构就可以了，显然，线段树
## 放代码：
```cpp
#include<iostream>
#include<cstdio>
#include<map>
using namespace std;
const int N=300010;
int v[N],x1[N],x2[N];
struct SegTree
{
    int l,r;
    int sum,add;
}t[N*4];
int e,n;
void Build(int p,int l,int r)
{
    t[p].l=l,t[p].r=r;
    if(l==r)
    {
        t[p].sum=0;
        t[p].add=0;
        return;
    }
    int mid=(l+r)/2;
    Build(p*2,l,mid);
    Build(p*2+1,mid+1,r);
    t[p].sum=t[p].add=0;
}
void qk()
{
    for(int i=1;i<=n;i++)
    {
        v[i]=0;
        x1[i]=0;
        x2[i]=0;
    }
    Build(1,1,n);
}
void Spread(int p)
{
    if(t[p].add)
    {
        t[p*2].sum+=t[p].add;
        t[p*2+1].sum+=t[p].add;
        t[p*2].add+=t[p].add;
        t[p*2+1].add+=t[p].add;
        t[p].add=0;
    }
}
void Change(int p,int l,int r,int k)
{
    if(t[p].l>=l&&t[p].r<=r)
    {
        t[p].sum+=k;
        t[p].add+=k;
        return;
    }
    Spread(p);
    int mid=(t[p].l+t[p].r)/2;
    if(mid>=l)Change(p*2,l,r,k);
    if(mid<r)Change(p*2+1,l,r,k);
    t[p].sum=min(t[p*2].sum,t[p*2+1].sum);
}
int Ask(int p,int l,int r)
{
    if(t[p].l>=l&&t[p].r<=r)
    {
        return t[p].sum;
    }
    Spread(p);
    int mid=(t[p].l+t[p].r)/2;
    int ans0=1e9;
    if(mid>=l)ans0=Ask(p*2,l,r);
    if(mid<r)ans0=min(ans0,Ask(p*2+1,l,r));
    t[p].sum=min(t[p*2].sum,t[p*2+1].sum);
    return ans0;
}
int main()
{
    cin>>e;
    while(e--)
    {
        scanf("%d",&n);
        qk();
        int ans=0;
        for(int i=1;i<=n;i++)
        {
            int x;
            scanf("%d",&x);
            if(v[x]==0)
            {
                v[x]=1;
                Change(1,1,i,1);
                x1[x]=i;
            }
            else
            {
                v[x]++;
                if(Ask(1,x2[x]+1,x1[x])==1)
                {
                    ans++;
                    Change(1,1,i,1);
                    Change(1,x1[x]+1,i,1);
                }
                else
                {
                    Change(1,x1[x]+1,i,1);
                    Change(1,x2[x]+1,x1[x],-1);
                }
                x2[x]=x1[x];
                x1[x]=i;
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}

```

---

## 作者：xiezheyuan (赞：1)

阅读本题解前，请阅读并注意区分【简要题意】中好的序列和优秀的序列的概念。

## 简要题意

定义一个序列是好的，当且仅当存在一个数在序列中出现且仅出现一次。定义一个序列是优秀的，当且仅当其所有非空子段都是好的。

给定一个长度为 $n$ 的序列 $a$，你可以进行任意次操作，每次操作将 选定一个 $a_i$ 修改为任意整数。你需要将 $a$ 变成优秀的序列，输出最小操作次数。

$T$ 组数据。$1\leq n,\sum n\leq 3\times 10^5,1\leq a_i\leq n$。

## 思路

非常厉害的一道题目，明明每一步都很自然，为什么我想不出来？

首先我们考虑修改一个位置，一定会修改成一个不在序列中出现的数，以消除其影响。所以其实相当于在序列中选择若干个数充当断点，用这些断点分割序列（抛弃断点），则每个分割得到的段都必须是优秀的（由于断点的数是唯一的，所以跨越段的区间，一定是好的）。

根据这个题意转化，我们很容易设计一个贪心，我们从左往右扫，遇到一个点，如果到这个点的前缀不再是优秀的了，就将这个点充当断点。这个贪心的策略正确性几乎是显然的。

由于对于前缀 $[1,x]$ 不再是优秀的，而 $[1,x-1]$ 是优秀的，所以一定是存在一个右端点为 $x$ 的区间不是好的。这启发我们研究哪些子段是好的。

对于每个数 $a_i$，记其前面第一个与 $a_i$ 相同的数为 $a_{\mathrm{pre}_i}$，后面第一个与 $a_i$ 相同的数为 $a_{\mathrm{nxt}_i}$，则所有左端点位于 $[\mathrm{pre}_i+1,i]$，右端点位于 $[i,\mathrm{nxt}_i-1]$ 的区间都是好的（因为包含了一个出现一次的元素 $a_i$）。

于是可以设计一个类似扫描线的过程，维护一个数据结构，支持区间加区间查询最小值，一个位置 $\geq 1$ 表示可以以这个点为左端点，那么遇到 $i$ 就将 $[\mathrm{pre}_i+1,i]$ 增加 $1$，遇到 $\mathrm{nxt}_i$ 就将这个区间减去 $1$，这是容易实现的。实现时只需要处理出 $\mathrm{pre}_i$ 即可。

时间复杂度 $O(Tn\log n)$。

## 代码

```cpp
#include <bits/stdc++.h>
#define ls (i << 1)
#define rs (i << 1 | 1)
#define mid ((l + r) >> 1)
using namespace std;

const int N = 3e5 + 5;
int n, a[N], bkt[N], pre[N];

int t[N << 2], tag[N << 2];

void mktag(int i, int v){ tag[i] += v, t[i] += v; }
void pushdown(int i){
    if(tag[i]) mktag(ls, tag[i]), mktag(rs, tag[i]), tag[i] = 0;
}

void update(int ql, int qr, int v, int i, int l, int r){
    if(ql > qr) return;
    if(ql <= l && r <= qr) return mktag(i, v);
    pushdown(i);
    if(ql <= mid) update(ql, qr, v, ls, l, mid);
    if(mid < qr) update(ql, qr, v, rs, mid + 1, r);
    t[i] = min(t[ls], t[rs]);
}

int query(int ql, int qr, int i, int l, int r){
    if(ql > qr) return INT_MAX;
    if(ql <= l && r <= qr) return t[i];
    pushdown(i);
    int res = INT_MAX;
    if(ql <= mid) res = min(res, query(ql, qr, ls, l, mid));
    if(mid < qr) res = min(res, query(ql, qr, rs, mid + 1, r));
    return res;
}

void solve(){
    cin >> n;
    for(int i=1;i<=n;i++) cin >> a[i];
    for(int i=1;i<=n;i++) pre[i] = bkt[a[i]], bkt[a[i]] = i;
    int p = 1, ans = 0;
    for(int i=1;i<=n;i++){
        update(pre[i] + 1, i, 1, 1, 1, n);
        update(pre[pre[i]] + 1, pre[i], -1, 1, 1, n);
        if(!query(p, i, 1, 1, n)) p = i + 1, ans++;
    }
    cout << ans << '\n';
}

void clear(){
    fill(bkt + 1, bkt + n + 1, 0);
    fill(pre + 1, pre + n + 1, 0);
    fill(t + 1, t + (n << 2) + 1, 0);
    fill(tag + 1, tag + (n << 2) + 1, 0);
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int t; cin >> t;
    while(t--) solve(), clear();
    return 0;
}

// Written by xiezheyuan
```

---

## 作者：迟暮天复明 (赞：1)

有点牛的。

显然我们可以注意到两个性质：

+ 修改操作一定会把数改成一个没出现过的数。在这之后，它两侧的段可以分别考虑。

+ 每次修改一定出现在到当前位置为止恰好出现 non-unique 子段的位置。

第一条性质显然。

对于第二条性质，假设当前从左到右出现的第一个 NU 子段为 $[l,r]$，那么显然该子段中至少需要修改一个位置。同时，在修改完了之后，修改位置左边留下的东西就没有用了。所以，贪心地考虑，就可以发现修改的位置一定是 $r$，也就是恰好出现了 NU 的位置。

现在，问题便转化为：对于一个位置，判断上一次修改的位置 $s$ 和当前位置 $r$ 之间，是否存在一个位置 $l$，使得 $[l,r]$ 子段形成一个 NU。

我们考虑暴力求解的过程。我们从 $r$ 往左扫的过程中，记录 unique 数码的数量。那么，如果出现了一个新的数字，那么 unique 增加一。如果一个数字出现了第二次，那么 unique 减少一。其他情况下不变。存在 NU 当且仅当存在某个位置 $l$ 使得做到该位置时 unique 计数为 $0$。

那我们将暴力求解的思路进行转化，也就相当于每个数字前两次出现的贡献分别为 $1,-1$，然后求后缀和最小值的问题。这个不难想到转化成区间加区间最小值问题，用线段树维护。

但是，现在问题在于我需要将 $r$ 推到 $r+1$。假设 $r+1$ 这个位置上的数字前三次出现位置分别为 $p_0=r+1,p_1,p_2$，那么原来三个位置上的贡献分别为 $0,1,-1$，现在要改为 $1,-1,0$。这个东西可以线段树区间加维护。

总结起来，本题只需要 $r$ 指针扫一遍，对于每个位置更新线段树并求解区间最小值，如果最小值为 $0$ 就增加一次操作并 $r\to s$。总时间复杂度 $O(n\log n)$。

---

## 作者：Kevin_Lsy (赞：0)

# Solution
希望用最少的替换次数使整个序列的每一个子序列中都至少存在一个元素仅出现一次, 考虑我们修改 $a_i$ , 那么可以发现性质: 
- 一定是把 $a_i$ 修改为 $x$ 满足 $\forall y\in[1..n]\ ,\ a_y\neq x$ 这样我们的修改没有后效性
- 通过上述修改后, 发现对于 $l\in[1..i)\ ,\ r\in(i..n]\ ,$ 子区间 $[l,r]$ 都是合法的了

因为上述性质, $a_i$ 修改后的任意前缀区间左界 $l\in[1..i)$ 都一定是合法的了, 每次从上一次修改的后一位开始找最近的下一个不合法区间即可。\
考虑用线段树这一支持区间修改及查询的数据结构, 维护一个区间中只出现一次的值的个数, 从 $1$ 到 $n$ 扫一遍, 计上一次修改的位置的后一位 $pre$ , 每一个值的上次以及上上次出现位置 $p_1,\ p_2$ , 每加入一个值 $a_p$ , 在线段树上让 $(p_2, p_1]\ -1$ 并 $(p_1,p]\ +1$ 便可完成更新信息, 同时可以更新值 $a_p$ 的 $p_1,\ p_2$ 。判断不合法区间只需要在线段树上查询 $\min\limits_{i\in[pre,p]}\operatorname{CntSingleOccurence}$ , 如果为 $0$ 则不合法, 进行修改, 更新 $pre$ 的值。\
时间复杂度 $O(t\cdot n\log n)$ .\
[Code](https://codeforces.com/contest/1969/submission/271811342)

---

## 作者：yuanruiqi (赞：0)

若选择更改 $i_1,i_2,\cdots,i_k$ 的值，则将它们分别改为 $n+1,n+2,\cdots,n+k$ 是不劣的。若原来有 $m$ 个不唯一的子数组 $(l_1,r_1),\cdots,(l_m,r_m)$，那么位置 $i_x$ 可以使 $\forall j,l_j\le i_x\le r_j$ 合法。

考虑从左到右枚举右端点扫描序列，若存在左端点构成一个不合法序列，则将右端点标记为特殊位置是不劣的。

对于每种颜色，在区间中要么不存在，要么存在多次，那么对应的左端点是两段区间。左端点位置要求满足每一种颜色的限制，可以用线段树维护区间加，区间最大值，并检查最大值是否等于颜色个数。

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
constexpr int maxn = 600000 + 10;
int t[maxn << 2], tag[maxn << 2];
void maketag(int rt, int x)
{
    tag[rt] += x;
    t[rt] += x;
}
void down(int rt)
{
    if (tag[rt])
    {
        maketag(rt << 1, tag[rt]);
        maketag(rt << 1 | 1, tag[rt]);
        tag[rt] = 0;
    }
}
void update(int rt, int l, int r, int L, int R, int x)
{
    if (L <= l && r <= R) return maketag(rt, x);
    int m = (l + r) >> 1;
    down(rt);
    if (L <= m) update(rt << 1, l, m, L, R, x);
    if (m < R) update(rt << 1 | 1, m + 1, r, L, R, x);
    t[rt] = max(t[rt << 1], t[rt << 1 | 1]);
}
int query(int rt, int l, int r, int L, int R)
{
    if (L <= l && r <= R) return t[rt];
    int m = (l + r) >> 1, ans = 0;
    down(rt);
    if (L <= m) ans = query(rt << 1, l, m, L, R);
    if (m < R) ans = max(ans, query(rt << 1 | 1, m + 1, r, L, R));
    return ans;
}
int a[maxn], p[maxn], lst[maxn];
void solve()
{
    int n;
    cin >> n;
    for (int i=1;i<=n;++i) cin >> a[i];
    memset(t, 0, sizeof(t[0]) * (n + 5) * 4);
    memset(tag, 0, sizeof(tag[0]) * (n + 5) * 4);
    memset(p, 0, sizeof(p[0]) * (n + n + 10));
    for (int i=1;i<=n;++i) update(1, 1, n, 1, n, 1);
    int m = n, ans = 0;
    for (int i=1;i<=n;++i)
    {
        lst[i] = p[a[i]];
        update(1, 1, n, p[a[i]] + 1, n, -1);
        if (i < n) update(1, 1, n, i + 1, n, 1);
        if (lst[lst[i]]) update(1, 1, n, 1, lst[lst[i]], -1);
        if (lst[i]) update(1, 1, n, 1, lst[i], 1);
        if (query(1, 1, n, 1, i) == m)
        {
            ++ans;
            update(1, 1, n, p[a[i]] + 1, n, 1);
            if (i < n) update(1, 1, n, i + 1, n, -1);
            if (lst[lst[i]]) update(1, 1, n, 1, lst[lst[i]], 1);
            if (lst[i]) update(1, 1, n, 1, lst[i], -1);
            lst[i] = 0;
            a[i] = ++m;
            if (i < n) update(1, 1, n, i + 1, n, 1);
        }
        p[a[i]] = i;
    }
    cout << ans << '\n';
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}
```

---

## 作者：C_Pos_Princess (赞：0)

## 题意
一次操作定义为替换数组中的一个数为任意一个整数。

询问最少经过多少次操作可以使任意一个子数组都是唯一的。

唯一定义为当前序列中存在一个数 $x$ 在此序列中仅出现一次。

## 题解
肯定贪心，替换为一个没出现过的数字，那么序列就从这个位置分开了，问题转换成最少分成多少段使每一段都合法。

我们维护当前位置的值上一次出现的位置和上上次出现的位置，进行区间加一或减一，从而通过区间最小值判断合法与否。

## 代码
```cpp
const int N = 3e5 + 10;
const int INF = 0x3f3f3f3f;
using namespace std;
int n;
int a[N];
int lst[N], llst[N];
int t;

struct node {
	int l, r;
	int minn;
	int lazy;

} tr[N << 2];

void pushup(int rt) {
	tr[rt].minn = min(tr[rt << 1].minn, tr[rt << 1 | 1].minn);
}

void build(int rt, int l, int r) {
	tr[rt].l = l;
	tr[rt].r = r;
	tr[rt].lazy = 0;
	if (l == r) {
		tr[rt].minn = 0;
		return;
	}
	int mid = l + r >> 1;
	build(rt << 1, l, mid);
	build(rt << 1 | 1, mid + 1, r);
	pushup(rt);
}

void pushdown(int rt) {
	int l = tr[rt].lazy;
	if (l) {
		tr[rt << 1].lazy += l;
		tr[rt << 1 | 1].lazy += l;
		tr[rt << 1].minn += l;
		tr[rt << 1 | 1].minn += l;
		tr[rt].lazy = 0;
	}
}


void update(int rt, int l, int r, int k) {
	if (l <= tr[rt].l && r >= tr[rt].r) {
		tr[rt].minn += k;
		tr[rt].lazy += k;
		return;
	}
	pushdown(rt);
	int mid = tr[rt].l + tr[rt].r >> 1;
	if (l <= mid) update(rt << 1, l, r, k);
	if (r > mid) update(rt << 1 | 1, l, r, k);
	pushup(rt);
}


int query(int rt, int l, int r) {
	if (l <= tr[rt].l && r >= tr[rt].r) {
		return tr[rt].minn;
	}
	pushdown(rt);
	int mid = tr[rt].l + tr[rt].r >> 1;
	int ans = INF;
	if (l <= mid) ans = min(ans, query(rt << 1, l, r));
	if (r > mid) ans = min(ans, query(rt << 1 | 1, l, r));
	return ans;
}



int main() {
	read(t);
	while (t--) {
		read(n);
		for (int i = 1; i <= n; i++) {
			read(a[i]);
			lst[i] = llst[i] = 0;
		}
		build(1, 1, n);
		int ans = 0;
		for (int i = 1; i <= n; i++) {
			if (!lst[a[i]]) {
				update(1, 1, i, 1);
				llst[a[i]] = 1;
				lst[a[i]] = i;
			} else {
				update(1, llst[a[i]], lst[a[i]], -1);
				update(1, lst[a[i]] + 1, i, 1);
				llst[a[i]] = lst[a[i]] + 1;
				lst[a[i]] = i;
			}
			if (query(1, 1, i) == 0) {
				ans++;
				update(1, 1, i, 1);
			}
		}
		write(ans);
		LF;
	}

	return 0;
}

```

---

