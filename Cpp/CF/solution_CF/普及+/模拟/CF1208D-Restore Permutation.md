# Restore Permutation

## 题目描述

An array of integers $ p_{1},p_{2}, \ldots,p_{n} $ is called a permutation if it contains each number from $ 1 $ to $ n $ exactly once. For example, the following arrays are permutations: $ [3,1,2], [1], [1,2,3,4,5] $ and $ [4,3,1,2] $ . The following arrays are not permutations: $ [2], [1,1], [2,3,4] $ .

There is a hidden permutation of length $ n $ .

For each index $ i $ , you are given $ s_{i} $ , which equals to the sum of all $ p_{j} $ such that $ j < i $ and $ p_{j} < p_{i} $ . In other words, $ s_i $ is the sum of elements before the $ i $ -th element that are smaller than the $ i $ -th element.

Your task is to restore the permutation.

## 说明/提示

In the first example for each $ i $ there is no index $ j $ satisfying both conditions, hence $ s_i $ are always $ 0 $ .

In the second example for $ i = 2 $ it happens that $ j = 1 $ satisfies the conditions, so $ s_2 = p_1 $ .

In the third example for $ i = 2, 3, 4 $ only $ j = 1 $ satisfies the conditions, so $ s_2 = s_3 = s_4 = 1 $ . For $ i = 5 $ all $ j = 1, 2, 3, 4 $ are possible, so $ s_5 = p_1 + p_2 + p_3 + p_4 = 10 $ .

## 样例 #1

### 输入

```
3
0 0 0
```

### 输出

```
3 2 1
```

## 样例 #2

### 输入

```
2
0 1
```

### 输出

```
1 2
```

## 样例 #3

### 输入

```
5
0 1 1 1 10
```

### 输出

```
1 4 3 2 5
```

# 题解

## 作者：兮水XiShui丶 (赞：12)

现在有一个从$1$到$n$的一个全排列,但是你不知道这个排列到底是什么,但是你有一个$sum[i]$,其中$sum[i]$表示$\sum_{j=1}^{i-1}(a_j<a_i)?a_j:0$,现在给你$sum$数组,让你求出这个排列$a$  

乍一看十分的不可做(没错就是十分不可做)  
我们可以考虑一下,对于某一个$a_i$,我们设他前面比他小的数有$k$个,而且在$a_i$被确定之后,$a_i$就不可能再对前面的数有贡献了.所以我们可以考虑倒序枚举,即从$n$到$1$来确定每一位.  

然后我们从后往前考虑,假设我们现在考虑的是第$n$位,那么我们就可以发现 

$$sum[n]=\sum_{i=1}^{n-1}(a_i<a_n)?a_i:0$$  

看起来并不能快速的求出这个式子....不过没关系,我们考虑一下传说中的**加法结合律**.  

我们考虑某些$i<=n$,如果有某些$a_i<=a_n$,那么这些个连续的$a_i<a_n$组成的区间的$sum$(我们暂时称之为$tmp_k$),那么显然

$$\sum_{idx}tmp_{idx}=a_n$$  

我们画一张图(没错我就是灵魂画师):  

![qwq.png](https://i.loli.net/2019/08/26/x7siJzvBa3tLulf.png)

看一下这张图,~~嗯,花里胡哨~~  


我们回到之前的那个式子,显然发现,我们把那些小于$a_n$的$a_i$结合形成$idx$个$tmp$时,我们可以把那些式子想分成几组就分成几组.所以我们可以考虑到树状数组的方式.

但是这样找一次不是$nlogn$的嘛,还不如暴力找呢qwq~~暴力出奇迹~~

注意到,我们放到这个树状数组里的东西,就是按顺序排列的序列$1,2,3....n$

(为什么要这么放呢?)  

我们注意到了之前的  
$$\sum_{idx}tmp_{idx}=a_n$$  

这个式子,其实每个$tmp$都可以拆分成若干$a_i$的和,而$a_i$的值域与序列$1,2,3....n$的值域相等,所以考虑合并成若干个$tmp$的话,序列$1,2,3....n$与原来的$a$数组是完全等价的.  

模型构建完了,现在开始考虑正事.  

我们考虑当前的$a_i$(之前已经假设过这个是$a_n$了)我们看上面的那张图,可以发现:我们可以把这个树状数组的节点可以分成$log_2n$层(每一条红线代表一层,圆内的数字指这个点控制的原序列中数的个数)所以我们可以枚举每一层的树状数组的节点,$if(tree[x]+sum<=a_n)$那么我们就$sum+=tree[x]$.  

经过了这样一遍乱搞之后,~~貌似时间复杂度还是和暴力一样啊qwq~~  

我们分析这样做的复杂度瓶颈在哪里,显然,我们在枚举树状数组上的每一层的时候,我们都要把这一层所有的节点枚举一遍.**但是**我们发现,对于第$i$层的某一个节点.如果我们选中了他,那么他之前的点完全可以不用考虑了(详见上图中的蓝线,因为在倒序枚举$i$的过程中,每个节点能控制的区间长度是单调递减的).所以我们在上一种方法中,多记录一个$num$表示现在已经考虑了前$num$位.所以我们枚举的时候,我们要多判断一个$(1<<i)+num<=n$就可以了.  

好,我们现在已经推导完了特殊情况,考虑除了$a_n$之外其他$a_i$的解决~~长征只开始了第一步~~(滑稽)  

其实并没有什么特殊的东西qwq...我们发现,我们在解决了第$a_{i+1}$个数到底是多少之后,因为我们之前是倒序枚举,所以$a_{i+1}$对$a_i$已经一点影响都莫得了.我们这时候就要在树状数组进行一次单点修改(将原来的$a_{i+1}$的点修改为$0$).  

注意一点,我们这么做的理由,是因为如果$j>i$,那么$j>(i-1)$~~废话~~,所以在题目保证有解的过程中,我们完全可以这么做.

然后....就莫得东西了吧qwq....树状数组不会写的话....线段树也不错啊qwq(滑稽).  

第一次写那么长的题解,好累啊QAQ.... 

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 5;
int n;
int s[N],tree[N],ans[N];
inline int lowbit(int x){
	return (x&-x);
}
void add(int x, int delta){
	while(x<=n){
		tree[x]+=delta;
		x+=lowbit(x);
	}
    return;
}
int query(int x){
    int sum = 0;
    while(x){
		sum+=tree[x];
		x-=lowbit(x);
	}
    return sum;
}
int find(int x){
    int num = 0 , sum=0;
    for(int i=log2(n)+1;i>=0;i--)
        if((num+(1<<i)<=n)&&(sum+tree[num+(1<<i)]<=x)){
            num+=(1<<i);
            sum+=tree[num];
        }
    return num + 1;
}
signed main(void){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s[i];
		add(i,i);
	}
	for(int i = n; i >= 1; --i){
        ans[i] = find(s[i]);
        add(ans[i],-ans[i]);
    } 
    for(int i=1;i<=n;i++)
		cout<<ans[i]<< " ";	
    return 0;
}
```


---

## 作者：tzc_wk (赞：7)

~~蒟蒻不会树状数组，因此只好写一个线段树题解~~

题意：有一个$1$到$n$的排列，但是你不知道它。现在给出每个数在它之前并且值比它小的数的和。求出这个排列。

思路：首先先找到最靠后的$0$，将这个位置$s$值赋上$INF$，$p$值赋上$1$，并将后面所有$s_i$的值$-1$。然后继续找到最靠后的$0$，将这个位置$s$值赋上$INF$，$p$值赋上$2$，并将后面所有$s_i$的值$-2$……这样进行$n$次就行了。区间减的操作可以用线段树来维护。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,a[200005],ans[200005];
struct SegTree{
	struct node{
		int l,r,val,lz;
	} s[2000005];
	inline void build(int k,int l,int r){
		s[k].l=l;s[k].r=r;
		if(l==r){
			s[k].val=a[l];
			return;
		}
		int mid=(l+r)>>1;
		build(k<<1,l,mid);
		build(k<<1|1,mid+1,r);
		s[k].val=min(s[k<<1].val,s[k<<1|1].val);
	}
	inline void pushdown(int k){
		s[k<<1].val+=s[k].lz;
		s[k<<1].lz+=s[k].lz;
		s[k<<1|1].val+=s[k].lz;
		s[k<<1|1].lz+=s[k].lz;
		s[k].lz=0;
	}
	inline void modify(int k,int l,int r,int x){
		if(l>r)	return;
		if(l<=s[k].l&&s[k].r<=r){
			s[k].val+=x;
			s[k].lz+=x;
			return;
		}
		pushdown(k);
		int mid=(s[k].l+s[k].r)>>1;
		if(r<=mid)		modify(k<<1,l,r,x);
		else if(l>mid)	modify(k<<1|1,l,r,x);
		else			modify(k<<1,l,mid,x),modify(k<<1|1,mid+1,r,x);
		s[k].val=min(s[k<<1].val,s[k<<1|1].val);
	}
	inline int query(int k,int l,int r){
		if(l<=s[k].l&&s[k].r<=r){
			return s[k].val;
		}
		pushdown(k);
		int mid=(s[k].l+s[k].r)>>1;
		if(r<=mid)		return query(k<<1,l,r);
		else if(l>mid)	return query(k<<1|1,l,r);
		else			return min(query(k<<1,l,mid),query(k<<1|1,mid+1,r));
	}
	inline int last_zero(){
		int l=1,r=n,ans;
		while(l<=r){
			int mid=(l+r)>>1;
			if(query(1,mid,n)==0)	ans=mid,l=mid+1;
			else					r=mid-1;
		}
		return ans;
	}
} s;
int cnt=0;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)	cin>>a[i];
	s.build(1,1,n);
	for(int i=1;i<=n;i++){
		int x=s.last_zero();
		ans[x]=++cnt;
		s.modify(1,x,x,1e12);
		s.modify(1,x+1,n,-cnt);
	}
	for(int i=1;i<=n;i++)	cout<<ans[i]<<" ";
	return 0;
}
```

---

## 作者：Tx_Lcy (赞：4)

[更差的阅读体验](https://www.cnblogs.com/tx-lcy/p/16850349.html)

[题目传送门](https://www.luogu.com.cn/problem/CF1208D)

## 思路

别的题解讲的比较奇妙，来一篇易懂的题解。

首先我们发现最后一个位置的值是可以首先确定的，因为它前面的数已经填完了。

所以我们考虑从后往前填写。

设最后一个位置的数为 $x$，则它的贡献就是 $\frac{x \times (x+1)}{2}$，所以最后一个数就是满足 $\frac{x \times (x+1)}{2}=a_n$ 的 $x$。

以此类推，我们从后往前考虑，对于每个节点的数可以二分求得，直接树状数组动态维护前缀和即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int const N=1e6+10;
int a[N],ans[N],n,vis[N];
struct Tree_Array{
    int c[N];
    inline int lowbit(int x){return x&-x;}
    inline void update(int x,int v){while (x<=n) c[x]+=v,x+=lowbit(x);}
    inline int query(int x){int res=0;while (x) res+=c[x],x-=lowbit(x);return res;}
}T;
inline int check(int x){return (x+1)*x/2-T.query(x);}
inline int qry(int x){
    int l=0,r=n;
    while (l<r){
        if (l+1==r){
            if (check(r)<=x) ++l;
            break;
        }
        int mid=(l+r)>>1;
        if (check(mid)>x) r=mid-1;
        else l=mid;
    }
    return l+1;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>n;
    for (int i=1;i<=n;++i) cin>>a[i];
    for (int i=n;i>=1;--i){
        ans[i]=qry(a[i]);
        T.update(ans[i],ans[i]);
    }
    for (int i=n;i;--i){
        while (vis[ans[i]]) --ans[i];
        vis[ans[i]]=1;
    }
    for (int i=1;i<=n;++i) cout<<ans[i]<<' ';
    cout<<'\n';
    return 0;
}
```


---

## 作者：yinqf (赞：2)

### Part1 题目大意

现在有一个从 $1$ 到 $n$ 的一个全排列，你只知道一个 $sum_i$，其中 $sum_i$ 表示 $\sum_{j=1}^{i-1}[a_j<a_i]\times a_j$，让你求出这个排列 $a$。

### Part2 做法介绍

从后往前确定，由于当前剩余可选的数已经确定，也就是对于每个数，都可以知道它的唯一确定的 $sum_i$，因此可以确定这一位填什么。然后更新当前剩余可选数。

但是目前是 $O(n^2)$，包过不了的。

考虑优化，用树状数组就可以 $O(\log n)$ 求出 $sum_i$，在配合上二分  $a_i$，就可以做到 $O(n\log^2 n)$ 求出答案，通过此题足以。

~~但这还不够~~，发现可以采用倍增思想，边倍增边计算答案，就是 $O(n\log n)$。（详见代码实现）

### Part3 完整代码

```cpp
#include<bits/stdc++.h>
#define faster ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define int long long
using namespace std;
const int N=2e5+5;
int n,a[N],ans[N],f[N],lg[N];
int lowbit(int x)
{
    return x&(-x);
}
void upd(int pos,int k)
{
    while(pos<=n)
    {
        f[pos]+=k;
        pos+=lowbit(pos);
    }
}
int find(int x)
{  
    int ret=0,sum=0;
    for(int i=lg[n];i>=0;i--)
    {
        if(ret+(1<<i)<=n&&sum+f[ret+(1<<i)]<=x)
        {
            ret=ret+(1<<i);
            sum+=f[ret];
        }
    }
    return ret+1;
}
signed main()
{
    faster;
    cin >> n;
    for(int i=1;i<=n;i++)
    {
        cin >> a[i];
    }
    for(int i=2;i<=n;i++)
    {
        lg[i]=lg[i>>1]+1;
    }
    for(int i=1;i<=n;i++)
    {
        upd(i,i);
    }
    for(int i=n;i>=1;i--)
    {
        ans[i]=find(a[i]);
        upd(ans[i],-ans[i]);
    }
    for(int i=1;i<=n;i++)
    {
        cout << ans[i] <<' ';
    }
    return 0;
}
```

---

## 作者：tian720 (赞：1)

题目传送门：[[CF1208D] Restore Permutation](https://www.luogu.com.cn/problem/CF1208D)。
## Solution：
考虑每次找最小值循环构造。

发现 $s_i$ 有两种情况：


当 $s_i\ne0$ 时，
它的前面一定有小于它的数，因此它不是最小值。

当 $s_i=0$ 时，
它的前面全部都大于它，因此它是 $1$ 到 $i$ 中的最小值，对于所有位置上是 $0$ 的数，直接选择最后一个是 $0$ 的位置时，它就比前面所有是 $0$ 的数都要小，那它就是最小值。

在第一次找最小值中，我们找到最小值 $1$ 的位置，此时删去这一位和它对后面的数产生的贡献，在剩下的序列找最小值就能找到 $2$ 了。

那么直接循环 $n$ 次，用线段树找到序列中最后一个为 $0$ 的位置 $id$，将其删去（设为正无穷），再将 $[id+1,n]$ 减去贡献就行了。
## Code：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N=2e5+5;
struct node{
	int l,r;
	ll sub,v;
}tr[N*4];
int n;
ll a[N];
void pushup(int u){
	tr[u].v=min(tr[u<<1].v,tr[u<<1|1].v);
}
void pushdown(int u){
	if(tr[u].sub){
		tr[u<<1].v-=tr[u].sub,tr[u<<1].sub+=tr[u].sub;
		tr[u<<1|1].v-=tr[u].sub,tr[u<<1|1].sub+=tr[u].sub;
		tr[u].sub=0;
	}
}
void build(int u,int l,int r){
	tr[u].l=l,tr[u].r=r;
	if(l==r){
		tr[u].v=a[l];
		return;
	}
	int mid=l+r>>1;
	build(u<<1,l,mid),build(u<<1|1,mid+1,r);
	pushup(u);
}
void modify(int u,int l,int r,ll x){
	if(l<=tr[u].l&&tr[u].r<=r){
		tr[u].v-=x,tr[u].sub+=x;
		return;
	}
	pushdown(u);
	int mid=tr[u].l+tr[u].r>>1;
	if(l<=mid) modify(u<<1,l,r,x);
	if(r>mid) modify(u<<1|1,l,r,x);
	pushup(u);
}
int query(int u){
	if(tr[u].l==tr[u].r) return tr[u].l;
	pushdown(u);
	if(tr[u<<1|1].v==0) return query(u<<1|1);
	return query(u<<1);
}
int seq[N];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	build(1,1,n);
	for(int i=1;i<=n;i++){
		int id=query(1);
		seq[id]=i;
		modify(1,id,id,-1e18);
		if(id+1<=n) modify(1,id+1,n,i);
	}
	for(int i=1;i<=n;i++) printf("%d ",seq[i]);
	return 0;
}
```

---

## 作者：Crazyouth (赞：1)

## 分析

~~由做题经验~~，这道题应该先把 $1$ 的位置求出来，我们注意到 $sum_1=0$，且所有下标在 $1$ 的下表标后面的 $sum$ 值必大于 $0$，因为加了个 $1$。所以最后的 $0$ 的位置就是 $1$ 的位置，那么我们把 $1$ 删去，再把 $1$ 下标后面的数的 $sum$ 值全部减一，那么就可以确定 $2$ 的位置，以此类推。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+10;
int mn[N<<2],a[N],ans[N],b[N<<2];
void build(int l,int r,int p)
{
	if(l==r)
	{
		mn[p]=a[l];
		return;
	}
	int m=l+r>>1;
	build(l,m,p<<1);
	build(m+1,r,p<<1|1);
	mn[p]=min(mn[p<<1],mn[p<<1|1]);
}
void update(int l,int r,int s,int t,int p,int k)
{
	if(l<=s&&t<=r)
	{
		mn[p]+=k;
		b[p]+=k;
		return;
	}
	int m=s+t>>1;
	if(b[p])
	{
		b[p<<1]+=b[p];
		b[p<<1|1]+=b[p];
		mn[p<<1]+=b[p];
		mn[p<<1|1]+=b[p];
		b[p]=0;
	}
	if(l<=m) update(l,r,s,m,p<<1,k);
	if(r>m) update(l,r,m+1,t,p<<1|1,k);
	mn[p]=min(mn[p<<1],mn[p<<1|1]);
}
int query(int l,int r,int s,int t,int p)
{
	if(l<=s&&t<=r) return mn[p];
	int m=s+t>>1;
	if(b[p])
	{
		b[p<<1]+=b[p];
		b[p<<1|1]+=b[p];
		mn[p<<1]+=b[p];
		mn[p<<1|1]+=b[p];
		b[p]=0;
	}
	int ans=1e18;
	if(l<=m) ans=query(l,r,s,m,p<<1);
	if(r>m) ans=min(ans,query(l,r,m+1,t,p<<1|1));
	return ans;
}
signed main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	build(1,n,1);
	for(int i=1;i<=n;i++)
	{
		int l=1,r=n,mid,idx;
		while(l<=r)
		{
			mid=l+r>>1;
			if(!query(mid,n,1,n,1)) idx=mid,l=mid+1;
			else r=mid-1;
		}
		update(idx,idx,1,n,1,1e18);
		update(idx+1,n,1,n,1,-i);
		ans[idx]=i;
	}
	for(int i=1;i<=n;i++) cout<<ans[i]<<' ';
	return 0;
}
```

---

## 作者：TernaryTree (赞：1)

有趣的构造题。

考虑

$$
\begin{aligned}
s_n
&=\sum\limits_{i=1}^{n-1}[a_i<a_n]a_i\\
&=\sum\limits_{i=1}^{n}[i<a_n]i\\
&=\sum\limits_{i=1}^{a_n-1}i\\
&=\dfrac12a_n(a_n-1)
\end{aligned}
$$

因此我们可以直接得到 $a_n$。

同理

$$
\begin{aligned}
s_{n-1}
&=\sum\limits_{i=1}^{n-2}[a_i<a_{n-1}]a_i\\
&=\sum\limits_{i=1}^{n}[i\neq a_n][i<a_{n-1}]i\\
&=\sum\limits_{i=1}^{a_{n-1}-1}i\ [i\neq a_n]\\
\end{aligned}
$$

再手玩几组可以得到

$$
s_{i} =\sum_{j=1}^{a_i-1}j\ [j\notin \{a_z\mid i+1\le z\le n\}]
$$

---

比方说，当 $s=\{0,0,4,1,6\}$ 时：

首先我们有一个完整的排列 $\{1,2,3,4,5\}$，当前 $s_5=6$，是排列前 $3$ 项之和，其下一项为 $4$，将 $4$ 移出排列，此时剩余序列为 $\{1,2,3,5\}$；

接下来有 $s_4=1$，是当前序列前 $1$ 项之和，所以 $a_4$ 等于当前序列的第 $1+1=2$ 项，即 $2$，将 $2$ 移出排列，此时剩余 $\{1,3,5\}$；

照样，$s_3=4=1+3$，$a_3$ 即序列中第三项 $5$。接下来可以依次得到 $a_2=1,a_1=3$。

使用树状数组维护，每次二分第一个 $>s_i$ 的当前序列前缀和，然后将此位清零即可。

树状数组上二分前缀和貌似是可以 $\Theta(n\log n)$ 的，但是懒得写就写了朴素二分，复杂度 $\Theta(n\log^2n)$。

[Code](https://www.luogu.com.cn/paste/vtcxv6ws)。

---

## 作者：ny_jerry2 (赞：0)

### 思路
这道题的思路是这样的：  
1. 从 $1 \to n$ 遍历。
2. 找到序列中**位置最靠后的一个零，该位置上的数即为我们当前遍历的数**。
3. 将该位置删除。
4. 减去该位置上的数对之后的数的贡献。

然后逐个来解释（第一个略过）。  

- 考虑简单证明一下第二个。  
   设当前遍历的数为 $i$，当前找到的位置为 $w$（**下面都是考虑还没有被删除的位置**）。

  
   下面是分情况讨论。

  
   - 对于在 $w$ 之前的数，因为该位上的值为 $0$，所以 $i$ 小于前面的任何数。  
   - 对于在 $w$ 之后的数，因为它们位置上的值不为 $0$，所以它们起码大于 $i$（因为 $i$ 是最小的嘛）。
   
  所以就证明到了。当然每一位上的值是有可能会变化的，这个后面来处理。

- 删除数位不需要真的删除，只需要用一个线段树做一个单点修改，将这个位置上面的数值改为赋成一个极大值即可，这样后面它就不可能产生贡献了。。

- 减去贡献就是一个区间修改，让当前位置后面的位置上的值减去这个数就好了。还是线段树，可以用 lazy-tag 来搞，只不过要稍微处理一下被删的位置。

同样，操作 $2$ 就是线段树上的区间查询。

因此就用线段树完美解决了。对于题解中的树状数组的写法只能 orz。

## 正解
```cpp
#include<iostream>
using namespace std;
int n;
const int N=2e5+10;
long long a[N];
int ans[N];
struct tree{
	int l,r;
	long long v;
	long long add;
}tr[N<<2];
void push_up(int u){
	tr[u].v=min(tr[u<<1].v,tr[u<<1|1].v);
}
void add(int u,long long k){
	if(tr[u].v){
		tr[u].v-=k;
	}
	tr[u].add+=k;
}
void push_down(int u){
	if(!tr[u].add){
		return;
	}
	add(u<<1,tr[u].add);
	add(u<<1|1,tr[u].add);
	tr[u].add=0;
}
void build(int u,int l,int r){
	tr[u].l=l,tr[u].r=r;
	if(l==r){
		tr[u].v=a[l];
		return;
	}
	int mid=(l+r)>>1;
	build(u<<1,l,mid);
	build(u<<1|1,mid+1,r);
	push_up(u);
}
int query(int u){
	if(tr[u].l==tr[u].r){
		return tr[u].l;
	}
	push_down(u);
	int mid=(tr[u].l+tr[u].r)>>1;
	if(!tr[u<<1|1].v){
		return query(u<<1|1);
	}else if(!tr[u<<1].v){
		return query(u<<1);
	}
}
void modify(int u,int l,int r,int x){
	if(tr[u].l>=l&&tr[u].r<=r){
		add(u,x);
		return;
	}
	push_down(u);
	int mid=(tr[u].l+tr[u].r)>>1;
	if(l<=mid){
		modify(u<<1,l,r,x);
	}
	if(r>mid){
		modify(u<<1|1,l,r,x);
	}
	push_up(u);
}
void modify(int u,int x,long long v){
	if(tr[u].l==tr[u].r){
		tr[u].v=v;
		return;
	}
	push_down(u);
	int mid=(tr[u].l+tr[u].r)>>1;
	if(x<=mid){
		modify(u<<1,x,v);
	}else{
		modify(u<<1|1,x,v);
	}
	push_up(u);
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
	}
	build(1,1,n);
	for(int i=1;i<=n;i++){
		int id=query(1);
		ans[id]=i;
		if(id<n){
			modify(1,id+1,n,i);
		}
		modify(1,id,1e18);
	}
	for(int i=1;i<=n;i++){
		cout<<ans[i]<<' ';
	}
}
```

---

## 作者：songzhixin (赞：0)

### 题意

给定每一个数前面比它小的数的总和，让你还原这个排列。

### 思路

这道题首先可以发现一个规律，最后一个 $0$ 所对应的一定是最后小的一个数，切任何时候都是用。理由如下：若这里不是最小的数，则要么前面有，这里就不应该是 
$0$ 了，要么后边有，那后边那一个为何会不是 $0$ 呢？

而确定了某个数之后，其后边所有位置上的 $a$ 值都应该减去当前这个数所对应的值，这个过程其实是可以通过线段树维护的。

如何查询最后一个 $0$ 呢？其实可以维护一个区间最小值，若这个数到 $n$ 的最小值为 $0$ 则这个数及之后一定存在 $0$，可以用二分来锁定区间。

这题有两个坑：

- 极大值需要足够大

- 这个数用过之后要标记为用过（设为极大值）。


### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const long long N=4*1e5+5;
struct node {
	long long l,r,v;
	long long minn;
};
node t[N*4];
long long a[N];
void build(long long x,long long fl,long long fr) {
	t[x].l=fl;
	t[x].r=fr;
	t[x].v=0;
	if(fl!=fr) {
		long long mid=(fl+fr)>>1;
		build(x*2,fl,mid);
		build(x*2+1,mid+1,fr);
		t[x].minn=min(t[x*2].minn,t[x*2+1].minn);
	}
	else{
		t[x].minn=a[fl];
	}
	return;
}
void add(long long x,long long fl,long long fr,long long y) {
	if(fl<=t[x].l&&t[x].r<=fr) {
		t[x].v+=y;
		t[x].minn+=y;
		return;
	}
	if(t[x].v!=0) {
		t[x*2].v+=t[x].v;
		t[x*2].minn+=t[x].v;
		t[x*2+1].v+=t[x].v;
		t[x*2+1].minn+=t[x].v;
		t[x].v=0;
	}
	long long mid=(t[x].l+t[x].r)>>1;
	if(fl<=mid) {
		add(x*2,fl,fr,y);
	}
	if(fr>mid) {
		add(x*2+1,fl,fr,y);
	}
	t[x].minn=min(t[x*2].minn,t[x*2+1].minn);
	return;
}
long long ask(long long x,long long fl,long long fr) {
	if(fl<=t[x].l&&t[x].r<=fr) {
		return t[x].minn;
	}
	if(t[x].v!=0) {
		t[x*2].minn+=t[x].v;
		t[x*2].v+=t[x].v;
		t[x*2+1].minn+=t[x].v;
		t[x*2+1].v+=t[x].v;
		t[x].v=0;
	}
	long long mid=(t[x].l+t[x].r)>>1;
	long long ans=1e18;
	if(fl<=mid) {
		ans=min(ans,ask(x*2,fl,fr));
	}
	if(fr>mid){
		ans=min(ans,ask(x*2+1,fl,fr));
	}
	return ans;
}
long long ans[N];
int main() {
	long long n;
	scanf("%lld",&n);
	for(long long i=1; i<=n; i++) {
		scanf("%lld",&a[i]);
	}
	build(1,1,n);
	long long cnt=0;
	for(long long i=1;i<=n;i++){
		long long res=0,fl=1,fr=n;
		while(fl<=fr){
			long long mid=(fl+fr)>>1;
			if(ask(1,mid,n)==0){
				res=mid;
				fl=mid+1;
			}
			else{
				fr=mid-1;
			}
		}
		ans[res]=++cnt;
		if(res!=n){
			add(1,res+1,n,-cnt);
		}
		add(1,res,res,1e18);
	}
	for(long long i=1;i<=n;i++){
		printf("%lld ",ans[i]);
	}
	return 0;
}
```

---

## 作者：ny_Dacong (赞：0)

首先，最后一个 $0$ 一定是 $1$。因为在它前面没有比它更小的数了，而它后面的所有数都有比自身更小的数。

那么 $1$ 的位置确定，不妨设其位置为 $i$。那么 $1$ 会对 $i+1 \sim n$ 的所有数产生贡献。所以把 $i+1 \sim n$ 的所有数减去 $1$，然后删掉 $i$ 位置的这个数。

然后讨论 $2$。跟 $1$ 的思路一样，讨论完 $1$ 之后，最后一个 $0$ 就是 $2$。以此类推。

所以我们需要一个可区间修改，区间查询最小值的数据结构。

太好了，是线段树，我们有救了！

至于如何知道最后一个 $0$ 的具体下标，可以用二分。所以复杂度应该是双 $\log$。

至于如何删掉这个数，其实不用真的删，赋值为 $\infty$ 即可。

注意开 `long long`，而且 `0x3f3f3f3f` 不够用。

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long inf = 0x3f3f3f3f3f3f3f3f;
long long n;
long long num[200050],ans[200050];
long long tree[200050<<2],tag[200050<<2];
long long ls(long long x){
	return x<<1;
}
long long rs(long long x){
	return x<<1|1;
}
void push_up(long long p){
	tree[p] = min(tree[ls(p)],tree[rs(p)]);
	return;
}
void build(long long p,long long pl,long long pr){
	tree[p] = inf,tag[p] = 0;
	if(pl == pr){
		tree[p] = num[pl];
		return;
	}
	long long mid = pl+((pr-pl)>>1);
	build(ls(p),pl,mid);
	build(rs(p),mid+1,pr);
	push_up(p);
	return;
}
void addtag(long long p,long long opt){
	tree[p] -= opt;
	tag[p] += opt;
	return;
}
void push_down(long long p){
	if(tag[p]){
		addtag(ls(p),tag[p]);
		addtag(rs(p),tag[p]);
		tag[p] = 0;
	}
	return;
}
void modify(long long p,long long pl,long long pr,long long l,long long r,long long opt){
	if(l <= pl && pr <= r){
		addtag(p,opt);
		return;
	}
	long long mid = pl+((pr-pl)>>1);
	push_down(p);
	if(l <= mid){
		modify(ls(p),pl,mid,l,r,opt);
	}
	if(mid < r){
		modify(rs(p),mid+1,pr,l,r,opt);
	}
	push_up(p);
	return;
}
long long query(long long p,long long pl,long long pr,long long l,long long r){
	if(l <= pl && pr <= r){
		return tree[p];
	}
	long long mid = pl+((pr-pl)>>1),res = inf;
	push_down(p);
	if(l <= mid){
		res = min(res,query(ls(p),pl,mid,l,r));
	}
	if(mid < r){
		res = min(res,query(rs(p),mid+1,pr,l,r));
	}
	return res;
}
int main(){
	scanf("%lld",&n);
	for(long long i = 1; i <= n; i++){
		scanf("%lld",&num[i]);
	}
	build(1,1,n);
	for(long long i = 1; i <= n; i++){
		static long long l,r,mid,tp;
		l = 1,r = n;
		while(l <= r){
			mid = l+((r-l)>>1);
			if(query(1,1,n,mid,n) == 0){
				tp = mid;
				l = mid+1;
			}else{
				r = mid-1;
			}
		}
		ans[tp] = i;
		modify(1,1,n,tp,tp,-inf);
		modify(1,1,n,tp+1,n,i);
	}
	for(long long i = 1; i <= n; i++){
		printf("%lld ",ans[i]);
	}
	return 0;
}
```

---

## 作者：xuyifei0302 (赞：0)

看完这道题，我们仔细想一想，$1$ 肯定小于所有的数，所以 $1$ 这一位上的 $s_i$ 的值一定为 $0$，而且一定是最后一个 $0$，它会对后面的数字产生 $1$ 的贡献，我们就可以将这一位之后的 $s_i$ 全部减少 $1$，然后这个数列的最小值就是 $2$，所以 $2$ 这一位上的 $s_i$ 的值一定为 $0$，而且一定是最后一个 $0$，它会对后面的数字产生 $2$ 的贡献，我们就可以将这一位之后的 $s_i$ 全部减少 $2$，然后这个数列的最小值就是 $3$，以此类推。

所以我们就可以用线段树来维护这个过程，每次找最后一个为 $0$ 的位置，对于确定了的位置，就删去其 $s_i$ 值，即赋值为极大值。

下面是代码环节：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int INF = 1e16;
int n, s[200005], minn[800005], tag[800005], ans[200005];
void buildtree(int p, int l, int r) {
	minn[p] = INF;
	tag[p] = 0;
	if (l == r) {
		minn[p] = s[l];
		return;
	}
	int mid = (l + r) >> 1;
	buildtree(p * 2, l, mid);
	buildtree(p * 2 + 1, mid + 1, r);
	minn[p] = min(minn[p * 2], minn[p * 2 + 1]);
}
void pushdown(int p, int l, int r) {
	if (l == r) {
		minn[p] -= tag[p];
		tag[p] = 0;
		return;
	}
	tag[p * 2] += tag[p];
	tag[p * 2 + 1] += tag[p];
	minn[p] -= tag[p];
	tag[p] = 0;
}
void change(int p, int l, int r, int ll, int rr, int d) {
	if (tag[p]) {
		pushdown(p, l, r);
	}
	if (ll <= l && r <= rr) {
		tag[p] += d;
		pushdown(p, l, r);
		return;
	}
	int mid = (l + r) >> 1;
	if (ll <= mid) {
		change(p * 2, l, mid, ll, rr, d);
	}
	if (rr > mid) {
		change(p * 2 + 1, mid + 1, r, ll, rr, d);
	}
	minn[p] = min(minn[p * 2], minn[p * 2 + 1]);
}
void change1(int p, int l, int r, int x) {
	if (tag[p]) {
		pushdown(p, l, r);
	}
	if (l == r) {
		minn[p] = INF;
		return;
	}
	int mid = (l + r) >> 1;
	if (x <= mid) {
		change1(p * 2, l, mid, x);
	} else {
		change1(p * 2 + 1, mid + 1, r, x);
	}
	minn[p] = min(minn[p * 2], minn[p * 2 + 1]);
}
int get_num(int p, int l, int r) {
	if (tag[p]) {
		pushdown(p, l, r);
	}
	if (l == r) {
		return l;
	}
	int mid = (l + r) >> 1;
	pushdown(p * 2, l, mid);
	pushdown(p * 2 + 1, mid + 1, r);
	if (minn[p * 2 + 1] == 0) {
		get_num(p * 2 + 1, mid + 1, r);
	} else {
		get_num(p * 2, l, mid);
	}
}
void data(int p, int l, int r) {
	if (tag[p]) {
		pushdown(p, l, r);
	}
	if (l == r) {
		cout << l << " " << minn[p] << "\n";
		return;
	}
	int mid = (l + r) >> 1;
	data(p * 2, l, mid);
	data(p * 2 + 1, mid + 1, r);
}
signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i ++) {
		cin >> s[i];
	}
	buildtree(1, 1, n);
	for (int i = 1; i <= n; i ++) {
		int tmp = get_num(1, 1, n);
		ans[tmp] = i;
		change(1, 1, n, tmp + 1, n, i);
//		data(1, 1, n);
		change1(1, 1, n, tmp);
//		cout << tmp << "\n";
//		data(1, 1, n);
	}
	for (int i = 1; i <= n; i ++) {
		cout << ans[i] << " ";
	}
	return 0;
}
```

---

## 作者：rainbow_cat (赞：0)

显然的，答案中为 $1$ 的数的 $s$ 值为 $0$，因此，最后一个 $s$ 为 $0$ 的位置值为 $1$。  

这个位置对后面有 $1$ 的贡献，考虑移除这一位和其贡献，则最后一个 $s$ 为 $0$ 的位置值为 $2$。   

因此，得出解法，枚举 $1$ 到 $n$， $s$ 为 $0$ 的最后一个位置值为 $i$，移除这一位和其贡献。   

使用线段树维护，二分求最后一个 $0$，至于移除某一位，将其赋值为 $n^2$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[200010],ans[200010];
struct node{int x,y,v,tag;}tree[800010];
void init(int p,int l,int r)
{
	tree[p]={l,r,0x3f3f3f3f3f3f3f3f};
	if(l==r)
	{
		tree[p].v=a[l];
		return;
	}
	int mid=(l+r)/2;
	init(p*2,l,mid),init(p*2+1,mid+1,r);
	tree[p].v=min(tree[p*2].v,tree[p*2+1].v);
}
void pushdown(int p)
{
	if(tree[p].x==tree[p].y)return;
	tree[p*2].tag+=tree[p].tag,tree[p*2].v+=tree[p].tag;
	tree[p*2+1].tag+=tree[p].tag,tree[p*2+1].v+=tree[p].tag;
	tree[p].tag=0;
}
void change(int p,int x,int y,int v)
{
	if(tree[p].tag)pushdown(p);
	if(x<=tree[p].x&&tree[p].y<=y)
	{
		tree[p].v+=v,tree[p].tag+=v;
		return;
	}
	int mid=(tree[p].x+tree[p].y)/2;
	if(x<=mid)change(p*2,x,y,v);
	if(mid<y)change(p*2+1,x,y,v);
	tree[p].v=min(tree[p*2].v,tree[p*2+1].v);
}
int query(int p,int x,int y)
{
	if(tree[p].tag)pushdown(p);
	if(x<=tree[p].x&&tree[p].y<=y)return tree[p].v;
	int mid=(tree[p].x+tree[p].y)/2;
	int res=0x3f3f3f3f3f3f3f3f;
	if(x<=mid)res=min(res,query(p*2,x,y));
	if(mid<y)res=min(res,query(p*2+1,x,y));
	return res;
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	init(1,1,n);
	for(int i=1;i<=n;i++)
	{
		int l=1,r=n;
		while(l<r)
		{
			int mid=(l+r+1)/2;
			if(query(1,mid,n)==0)l=mid;
			else r=mid-1;
		}
		ans[l]=i;
		//cout<<l<<' ';
		change(1,l,l,n*n);
		if(l+1<=n)change(1,l+1,n,-i);
	}
	for(int i=1;i<=n;i++)cout<<ans[i]<<' ';
	return 0;
}
/*
seg-tree:sum
find 0:i
sum[pos+1]~sum[n] -1
mid search pos,use min;
*/
```

---

## 作者：_ZHONGZIJIE0608_ (赞：0)

上课讲的神秘构造题。

注意到一个数一定可以表示为 **现在可用的数** 从小到大排序后的前缀的前缀和。

比如说最后一个数一定可以表示为 $\frac{x(x-1)}{2}$ 的形式，并且最后一个数就是 $x$。然后我们就可以把 $x$ 标记为 **不可用**。

单点修改，快速求前缀和，树状数组可以胜任。

至于怎么找 $x$ 呢？不难考虑到 $a$ 是一个排列，我们直接存储 $1$ 到 $n$ 中每个数的数值。然后发现前缀和显然有单调性（不会减小），二分就可以了。

那么打标记的处理方法就是直接在树状数组上把找到的数 $x$ 修改为 $0$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
int n,a[N],t[N],ans[N];
void upd(int x,int k){
    for(int i=x;i<=n;i+=(i & -i))t[i]+=k;
}
int qry(int x){
    int s=0;
    for(int i=x;i;i-=(i & -i))s+=t[i];
    return s;
}
signed main(){
    ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;++i)cin>>a[i],upd(i,i);
    for(int i=n;i;--i){
        int L=0,R=n+1,res=0;
        while(L+1<R){
            int mid=(L+R)/2;
            if(qry(mid-1)<=a[i])L=res=mid;
            else R=mid;
        }
        ans[i]=res;
        upd(res,-res);
    }
    for(int i=1;i<=n;++i)cout<<ans[i]<<' ';
    return 0;
}
```

---

## 作者：Muse_Dash (赞：0)

好题。

注意到，$sum$ 中最后一个出现的 $0$，其 $a$ 上对应值必定为 $1$，然后，其对之后所有数的 $sum$ 贡献为 $1$。然后，删掉这个 $1$ 以及它产生的贡献，发现最后一个出现的 $0$ 为 $2$，贡献是 $2$，以此类推。

然后得到了一个做法，就是 $n$ 次循环，第 $i$ 次找到最后一个 $0$，并把对应 $a$ 值设为 $i$，删去它（赋权 $\inf$）以及其对后面的数产生贡献 $i$。

显然可以线段树维护这个过程。

---

## 作者：RedreamMer (赞：0)

[$\Large\texttt {CF1208D}$](https://www.luogu.com.cn/problem/CF1208D)

思路：~~手玩~~，树状数组，线段树

这道题的思路就是先自己手玩数据，可以逐渐发现方法，思维难度不高。

---

$\large\texttt{Meaning}$

有一个长度为 $n$ ，各个数字值域为 $[1,n]$ 的全排列序列 $a$ ，给出序列 $b$ ，$b_i=\sum_{j=1}^{i-1}a_j\times[a_j<a_i]$，请求出序列 $a$。（保证有解）

---

$\large\texttt{Solution}$

第一种方法：

乍一看好像毫无头绪，可以先观察下面的数据

```
a={5,2,3,4,1,6}

b={0,0,2,5,0,15}
```

容易发现， $b$ 序列最后一个 $0$ 的位置 $a$ 序列对应的位置就是 $1$ ，因为没有一个数小于 $1$ ，并且除 $1$ 外所有数都大于 $1$ （只能是 $b$ 序列中最后一个 $0$ ）。

找到了 $1$ ，我们先将在 $b$ 序列的这个位置后面的贡献减去 $1$ 。

就可以进一步推出 $2$ 的位置，然后你会惊喜地发现找 $2$ 的方法和 $1$ 一样。

注意下细节：找到最后一个 $0$ 后，要将 $b$ 的这一位的数赋为 $-1$ 。

这样用线段树维护就能搞定这道题。

---

第二种方法：

对于一开始 $a$ 序列最后一个数 $x$ ， $b$ 最后一个数的值必为 $(1+x)\times x/2$ 。

但是对于 $x$ 之前的数 $y$ ，它有可能大于 $x$ ，这使得 $b$ 这个位置上的值不是 $(y+1)\times y/2$ ,少了一个 $x$ 。

从后往前推，并边找边用数据结构改。

可以发现可以用树状数组维护上述的 $(y+1)\times y/2-\sum x~~~(x<y)$
。（即区间修改 $x$ ，单点查询）。

找的时候在外面套一个二分查询就行了。

---


$\large\texttt{Code}$

第二种方法的代码（第一种没写QwQ）

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 2e6;
inline int read()
{
    register int s = 0;
    register bool neg = 0;
    register char c = getchar();
    for (; c < '0' || c > '9'; c = getchar())
        neg |= (c == '-');
    for (; c >= '0' && c <= '9'; s = s * 10 + (c ^ 48), c = getchar())
        ;
    return (neg ? -s : s);
}

int a, l, r, s[N + 10], p[N + 10], ans[N + 10];

inline void insert(int n, int m)
{
    while (n <= a)
    {
        p[n] += m;
        n += n & -n;
    }
}

inline int query(int n)
{
    int m = 0;
    while (n)
    {
        m += p[n];
        n -= n & -n;
    }
    return m;
}

signed main()
{
    a = read();
    for (int i = 1; i <= a; i++)
        s[i] = read(), insert(i, i);
    for (int i = a; i >= 1; i--)
    {
        int l = 1, r = a, mid, sum = 0;
        while (l <= r)
        {
            mid = (l + r) >> 1;
            if (query(mid - 1) <= s[i])
                sum = mid, l = mid + 1;
            else
                r = mid - 1;
        }
        insert(sum, -sum);
        ans[i] = sum;
    }
    for (int i = 1; i <= a; i++)
        printf("%lld ", ans[i]);
    return 0;
}
```

---

## 作者：foreverlasting (赞：0)

[推销博客](https://foreverlasting1202.github.io/2019/08/27/CF1208%E9%A2%98%E8%A7%A3/)

### D Restore Permutation

题意：未知一个长度为$n$的排列，对于位置$i$，假设在上面的数是$a_i$，给出$\sum_{j<i,a_j<a_i} a_j$，求这个排列。$1\leq n\leq 2\ast 10^5$。

做法：从后往前递推，显然最后一个未知的都可以二分出来，只需要动态维护前缀和，树状数组即可。复杂度$O(nlog^2n)$。

code:
```cpp
//2019.8.24 by ljz
//email 573902690@qq.com
//if you find any bug in my code
//please tell me
#include<bits/stdc++.h>
using namespace std;
#define res register int
#define LL long long
#define inf 0x3f3f3f3f
#define INF 0x3f3f3f3f3f3f3f
#define unl __int128
#define eps 5.6e-8
#define RG register
#define db double
#define pc(x) __builtin_popcount(x)
typedef pair<int,int> Pair;
#define mp make_pair
#define fi first
#define se second
#define pi acos(-1.0)
#define pb push_back
#define ull unsigned LL
#define gc getchar
//inline char gc() {
//    static char buf[100000],*p1,*p2;
//    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
//}
inline int read() {
    res s=0,ch=gc();
    while(ch<'0'||ch>'9')ch=gc();
    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=gc();
    return s;
}
//inline int read() {
//    res s=0,ch=gc(),w=1;
//    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=gc();}
//   while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=gc();
//    return s*w;
//}
inline LL Read() {
    RG LL s=0;
    res ch=gc();
    while(ch<'0'||ch>'9')ch=gc();
    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=gc();
    return s;
}
//inline LL Read() {
//    RG LL s=0;
//    res ch=gc(),w=1;
//    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=gc();}
//    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=gc();
//    return s*w;
//}
//inline void write(RG unl x){
//    if(x>10)write(x/10);
//    putchar(int(x%10)+'0');
//}
inline void swap(res &x,res &y) {
    x^=y^=x^=y;
}
//mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
//clock_t start=clock();
//inline void ck(){
//    if(1.0*(clock()-start)/CLOCKS_PER_SEC>0.1)exit(0);
//}
const int N=2e5+10;
namespace MAIN{
    int n;
#define lowbit(x) (x&-x)
    LL tr[N];
    LL a[N];
    inline void modify(const res &x,const res &y){
        for(res i=x;i<=n;i+=lowbit(i))tr[i]+=y;
    }
    inline LL query(const res &x){
        RG LL ret=0;
        for(res i=x;i;i-=lowbit(i))ret+=tr[i];
        return ret;
    }
    int A[N];
    inline void MAIN(){
//        printf("%d\n",0^2^4^11);
//        printf("%d\n",19^55^11^39^32^36^4^52);
        n=read();
        for(res i=1;i<=n;i++)a[i]=Read(),modify(i,i);
        for(res i=n;i;i--){
            res l=1,r=n,ret=0;
            while(l<=r){
                res mid=(l+r)>>1;
                if(query(mid-1)<=a[i])l=mid+1,ret=mid;
                else r=mid-1;
            }
            A[i]=ret;
            modify(ret,-ret);
        }
        for(res i=1;i<=n;i++)printf("%d ",A[i]);
    }
}
int main(){
//    srand(19260817);
//    freopen("signin.in","r",stdin);
//    freopen("signin.out","w",stdout);
    MAIN::MAIN();
    return 0;
}
```

---

