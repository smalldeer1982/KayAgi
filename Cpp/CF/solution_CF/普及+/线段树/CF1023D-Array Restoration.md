# Array Restoration

## 题目描述

Initially there was an array $ a $ consisting of $ n $ integers. Positions in it are numbered from $ 1 $ to $ n $ .

Exactly $ q $ queries were performed on the array. During the $ i $ -th query some segment $ (l_i, r_i) $ $ (1 \le l_i \le r_i \le n) $ was selected and values of elements on positions from $ l_i $ to $ r_i $ inclusive got changed to $ i $ . The order of the queries couldn't be changed and all $ q $ queries were applied. It is also known that every position from $ 1 $ to $ n $ got covered by at least one segment.

We could have offered you the problem about checking if some given array (consisting of $ n $ integers with values from $ 1 $ to $ q $ ) can be obtained by the aforementioned queries. However, we decided that it will come too easy for you.

So the enhancement we introduced to it is the following. Some set of positions (possibly empty) in this array is selected and values of elements on these positions are set to $ 0 $ .

Your task is to check if this array can be obtained by the aforementioned queries. Also if it can be obtained then restore this array.

If there are multiple possible arrays then print any of them.

## 说明/提示

In the first example you can also replace $ 0 $ with $ 1 $ but not with $ 3 $ .

In the second example it doesn't really matter what segments to choose until query $ 10 $ when the segment is $ (1, 3) $ .

The third example showcases the fact that the order of queries can't be changed, you can't firstly set $ (1, 3) $ to $ 6 $ and after that change $ (2, 2) $ to $ 5 $ . The segment of $ 5 $ should be applied before segment of $ 6 $ .

There is a lot of correct resulting arrays for the fourth example.

## 样例 #1

### 输入

```
4 3
1 0 2 3
```

### 输出

```
YES
1 2 2 3
```

## 样例 #2

### 输入

```
3 10
10 10 10
```

### 输出

```
YES
10 10 10 
```

## 样例 #3

### 输入

```
5 6
6 5 6 2 2
```

### 输出

```
NO
```

## 样例 #4

### 输入

```
3 5
0 0 0
```

### 输出

```
YES
5 4 2
```

# 题解

## 作者：ysner (赞：6)

### 题面

有长度为$n$的数列。有$m$次操作。

第$i$次操作中，必须把$[l,r](1\leq l\leq r\leq n)$中所有数字改为$i$。

现在给出**疑似**最终数列，其中几个数被改成了$0$。回答是否存在初始数列。

 - $n,m\leq2*10^5$
 
### 解析

很显然的是，如果两个相同数之间存在比它们小的数，这个序列一定不合法。

同样，如果这个序列不存在值为$m$的数，这个序列也不合法。

思考怎么填数。

首先，如果没有数列中没有数字$m$，优先填$m$。

其次，设数$x$分别在该位左右两边存在，则该位应取$\max\{x\}$。

再次，如果不存在$x$，该位填$1$。（因为绝对合法，且不可能干扰到其它位的填数）

然后想怎么维护这个$max\{x\}$。

考虑弄个$set$维护$x$，所有$x$的第一个出现时，$insert(x)$；所有$x$的最后一个出现时，$erase(x)$。

可删除大根堆也可以，只是写着麻烦。

还有，取$set$中最后一个数可以用*--Q.end()，end不会真的自减。
```
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<vector>
#include<set>
#define re register
#define il inline
#define ll long long
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
#define fp(i,a,b) for(re int i=a;i<=b;i++)
#define fq(i,a,b) for(re int i=a;i>=b;i--)
using namespace std;
const int mod=45989,N=5e5+100;
int n,m,top,a[N],L[N],R[N],mx,mn;
set<int>Q;
set<int>::iterator it;
il int gi()
{
  re int x=0,t=1;
  re char ch=getchar();
  while((ch<'0'||ch>'9')&&ch!='-') ch=getchar();
  if(ch=='-') t=-1,ch=getchar();
  while(ch>='0'&&ch<='9') x=x*10+ch-48,ch=getchar();
  return x*t;
}
int main()
{
  n=gi();m=gi();
  fp(i,1,n) a[i]=gi(),mx=max(mx,a[i]),mn=min(mn,a[i]);
  fq(i,n,1) if(!R[a[i]]) R[a[i]]=i;
  fp(i,1,n) if(!L[a[i]]) L[a[i]]=i;
  fp(i,1,n)
    {
      if(a[i]==0)
    {
      if(mx<m) a[i]=m,mx=m;
      else if(Q.size()) a[i]=*--Q.end();
      else a[i]=1;
    }
      else
    {
      if(L[a[i]]==i&&L[a[i]]<R[a[i]]) Q.insert(a[i]);
      if(R[a[i]]==i&&L[a[i]]<R[a[i]]) Q.erase(a[i]);
      if(Q.size()) if(a[i]<(*--Q.end())) {puts("NO");return 0;}
    }
    }
  if(mx<m) {puts("NO");return 0;}
  puts("YES");
  fp(i,1,n) printf("%d ",a[i]);puts("");
  return 0;
}
```
[蒟蒻博客](https://www.cnblogs.com/yanshannan/p/9505754.html)

---

## 作者：tangml (赞：5)

题意很简单，相当于给你了一个颜色覆盖的可能部分结果，要你判断该结果是否正确并补充完整输出。

考虑无解情况。

若整个区间中没有最大值则一定无解，因为每个颜色都一定要被涂上，不可以不涂，则最大值一定会出现在其中一个位置。如果其他颜色没有出现没关系，因为可以看作每次都涂在最大值的位置上，最后被最大值覆盖了。

如果区间没有最大值，则看区间内有没有 $0$，如果有 $0$ 的话，把其中一个涂成最大值即可，如果没有则一定无解。

另外一种无解的情况是存在两个相同的数中间有数比它小则一定无解，这个很好判断，可以写单调栈，我写的是稀疏表。

考虑剩下的 $0$ 如何涂色。我们可以发现，如果两个相同的数在一起，则可以看作为一个数，正确性显然。

所以我们把所有 $0$ 都可以涂成它旁边的数。如果是第一个数则一定可以涂成 $1$。


```cpp
#include<bits/stdc++.h>
#define int long long

using namespace std;

const int N=2e5+100;

int n,m;
int a[N],s[N];
bool sg;

int f[N][30];
void ST_prework()
{
	for(int i=1;i<=n;i++)	f[i][0]=a[i];
	int t=log(n)/log(2)+1;
	for(int j=1;j<t;j++)
		for(int i=1;i<=n-(1<<j)+1;i++)
			f[i][j]=min(f[i][j-1],f[i+(1<<(j-1))][j-1]);
}

int ST_query(int l,int r)
{
	int t=log(r-l+1)/log(2);
	return min(f[l][t],f[r-(1<<t)+1][t]);
}

signed main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        if(a[i]==m) sg=true;
    }

    for(int i=1;i<=n;i++)
        if(!sg && a[i]==0)
            sg=true,a[i]=m;

    if(!sg) return cout<<"NO"<<endl,0;//区间里面必须存在最大值

    for(int i=1;i<=n;i++)
        if(a[i]==0)
            a[i]=max({a[i-1],a[i+1],(int)1});//直接涂色，涂成隔壁的数，如果第一个数是0就可以直接涂成1，正确性显然

    for(int i=1;i<=n;i++)   s[a[i]]=i;

    ST_prework();

    for(int i=1;i<=n;i++)
    {
        if(s[a[i]]==i)  continue;
        if(ST_query(i,s[a[i]])!=a[i])   return cout<<"NO"<<endl,0;
    }

    cout<<"YES"<<endl;
    for(int i=1;i<=n;i++)   cout<<a[i]<<" ";

    return 0;
}

```

---

## 作者：novax (赞：5)

[题面](https://www.luogu.com.cn/problem/CF1023D)

### 题意

给你一个长度为 $n$ 的数列，初始全部为 $0$ ，进行 $q$ 次操作，第 $i$ 次操作使 $[l_i,r_i]$ 内的数全部变为 $i$ ，每个操作区间都不能为空且所有点都应被操作过。给出一个数列，问能否通过上述的 $q$ 次操作得到这个数列。

### 思路

提供一种只需要**线段树**的做法。

我们需要一个支持区间覆盖单点查询的线段树模拟题目中要求的操作过程，然后按照给出数列的情况贪心地模拟区间覆盖的操作。

维护数字 $i$ 在给出序列中第一次和最后一次出现的位置 $\text{first}_i$ 和 $\text{last}_i$，则 $[\text{first}_i,\text{last}_i]$一定是第 $i$ 次操作覆盖的区间子集。由于所有 $0$ 位置都需要被填上数字，所以可以同时维护 $\text{first}_i$ 左侧连续若干个 $0$ 中最小的下标 $sl_i$ 和 $\text{last}_i$ 右侧连续若干个 $0$ 中最大的下标 $sr_i$，则我们可以在第 $i$ 次操作将 $[sl_i,sr_i]$ 整个覆盖为 $i$，因为 $0$ 可以被覆盖为任何数字，因此只要输入数据有解，那么如此操作一定不会出现矛盾。

如果给出数列中没有 $0$ 且数字 $q$ 未曾出现，那么一定无解；否则可以将 $q$ 填在任意一个 $0$ 的位置上。对于其他没有出现过的数字可以在模拟覆盖时直接跳过，因为同一个位置可以多次覆盖，我们可以选择将所有这些未出现过的数字都覆盖在将来 $q$ 所在的位置上。另外需要注意的是，如果整个初始数列都是 $0$，应该将整个数列填满。

最后再单点查询线段树上每个点最终的值，如果有某个在给出数列中不为 $0$ 的位置的值与最终序列的不同，则说明产生了矛盾，无解；否则存在操作方式使得最终序列满足题目条件，输出最终序列即可。

### 代码

```cpp
#include <cstdio>
#define ls(p) ((p)<<1)
#define rs(p) (((p)<<1)|1)
const int Nx=200010;
int N,Q,A[Nx],al[Nx],ar[Nx],sl[Nx],sr[Nx],final[Nx],p0;
int col[4*Nx];
void adtag(int p,int ca){col[p]=ca;}
void pushdown(int p)
{
	if(!col[p])
		return;
	adtag(ls(p),col[p]);
	adtag(rs(p),col[p]);
	col[p]=0;
}
void update(int ll,int rr,int p,int L,int R,int ca)
{
	if(L<=ll&&R>=rr)
	{
		adtag(p,ca);
		return;
	}
	pushdown(p);
	int mid=(ll+rr)>>1;
	if(L<=mid)
		update(ll,mid,ls(p),L,R,ca);
	if(R>mid)
		update(mid+1,rr,rs(p),L,R,ca);
}
int query(int ll,int rr,int p,int pos)
{
	if(ll==rr)
		return col[p];
	pushdown(p);
	int mid=(ll+rr)>>1;
	if(pos<=mid)
		return query(ll,mid,ls(p),pos);
	else
		return query(mid+1,rr,rs(p),pos);
}
int main()
{
	scanf("%d%d",&N,&Q);
	int i,j,k;
	sl[0]=1;sr[N+1]=N;
	for(i=1;i<=N;i++)
	{
		scanf("%d",&A[i]);
		if(A[i]==0&&p0==0)
			p0=i;
		if(al[A[i]]==0)
			al[A[i]]=i;
		sl[i]=(A[i-1]==0)?sl[i-1]:i;
	}
	for(i=N;i>=1;i--)
	{
		if(ar[A[i]]==0)
			ar[A[i]]=i;
		sr[i]=(A[i+1]==0)?sr[i+1]:i;
	}
	for(i=1;i<=Q;i++)
	{
		if(al[i]==0)
		{
			if(i!=Q)
				continue;
			if(p0==0)
			{
				printf("NO\n");
				return 0;
			}
			al[i]=ar[i]=p0;
		}
		update(1,N,1,sl[al[i]],sr[ar[i]],i);
	}
	for(i=1;i<=N;i++)
	{
		final[i]=query(1,N,1,i);
		if(A[i]!=0&&A[i]!=final[i])
		{
			printf("NO\n");
			return 0;
		}
	}
	printf("YES\n");
	for(i=1;i<=N;i++)
		printf("%d ",final[i]);
	printf("\n");
}
```


---

## 作者：liaojie159357 (赞：1)

# 一篇只用了稀疏表的题解
## **题意**
给定一个长度为 $n$ 的序列，由非负整数组成；

要进行 $q$ 次操作，第 $i$ 次操作可以选择一段 $[l_i,r_i]$ 将其中所有数变为 $i$，所有操作的区间并必须为 $[1,n]$。

当序列中有数为 $0$ 的时候，你可以填任意数。

问由这个序列能否构造出一个合法的序列，不能输出`NO`，否则输出`YES`并输出合法序列。

## **分析**
这是一道构造题，接下来寻找题目的性质：

1. 因为后面进行操作的区间可以覆盖前面的操作区间，每次操作的区间都是连续的一段，且第 $i$ 次操作覆盖的 $i$ 是单调递增的，所以在两个相等的数之前是不能存在比这两个数小的数的。

2. 因为每次的操作区间不为空，且有 $q$ 次操作，再根据第一条性质，那么序列中一定至少有一个数是 $q$。

有了这两条性质，我们就可以找到构造的方法了。

## **做法**
#### 在序列中没有 $0$ 的情况下：
由分析中的两条性质可得：序列中必须有 $q$ 存在，且每两个相同的数之间没有比这两个数小的数，那么这个序列就是合法的。
  
具体操作：先判断序列中的最大值是否是 $q$，用一个数组 $pr[i]$ 来存 $i$ 在序列中从前往后出现的第一个位置，再用一个数组 $re[i]$ 来存 $i$ 在序列中从后1往前出现的第一个位置，最后加一个稀疏表来对每一个 $i$ 判断在 $[pr[i],re[i]]$ 中的最小值是否是 $i$ 即可。

#### 在序列中有 $0$ 的情况下：
受到没有 $0$ 的情况的启发，因为必须得有 $q$ 在序列中，所以先判断，如果没有就把一个 $0$ 变成 $q$。接着就是将剩下的 $0$ 都变成旁边不为 $0$ 的数，这样一定是不劣的（留作思考题）。

具体操作：先特判是否有 $q$，如果没有就先将一个 $0$ 变成 $q$，再将剩下的 $0$ 变成旁边不为 $0$ 的数，然后按照没有 $0$ 的情况判断即可。

> Talk is easy,show me your code.

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;

const int M=2e5+10;
int n,q;
int a[M];
int pr[M],re[M];
int f[M][30];
int mx,tot;
//mx:原序列中最大值
//tot:原序列中0的个数 

void work()
{
	for(int i=1;i<=n;i++)
		if(a[i]==0) a[i]=a[i-1];//将0改为旁边不为0的数 
	for(int i=n;i>=1;i--)
	{
		if(a[i]==0) a[i]=a[i+1];//前后都跑一遍，不然最前面可能还是0 
		f[i][0]=a[i];//ST表初始化 
	}
	for(int i=1;i<=n;i++)
		if(pr[a[i]]==0) pr[a[i]]=i;//从前往后i出现的第一个位置 
	for(int i=n;i>=1;i--)
		if(re[a[i]]==0) re[a[i]]=i;//从后往前i出现的第一个位置 
	
	for(int j=1;j<=log2(n);j++)
		for(int i=1;i+(1<<j)-1<=n;i++)
			f[i][j]=min(f[i][j-1],f[i+(1<<(j-1))][j-1]);//ST表 
	
	int s;
	for(int i=1;i<=q;i++)
	{
		if(re[i]==0||pr[i]==0) continue;//没这个数就跳过 
		s=log2(re[i]-pr[i]+1);
		if(i!=min(f[pr[i]][s],f[re[i]-(1<<s)+1][s]))//在两个相等的数之间的最小值不是这两个数时无解 
		{
			cout<<"NO";
			return;
		}
	}
	
	cout<<"YES"<<endl;
	for(int i=1;i<=n;i++)
		cout<<a[i]<<" ";//合法的 
	return;
}

int main()
{
	cin>>n>>q;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		if(a[i]==0) tot++;//0的个数 
		mx=max(mx,a[i]);//最大值 
	}
	
	if(tot==n)//全是0的情况一定有解，都是q 
	{
		cout<<"YES"<<endl;
		for(int i=1;i<=n;i++)
			cout<<q<<" ";
		return 0;
	}
	
	bool sg=false;//mx<q的特判 
	if(mx<q)
	{
		for(int i=1;i<=n;i++)
			if(a[i]==0)
			{
				a[i]=q;
				sg=true;
				break;//只用改一个 
			}
		if(sg==false)//没有0 
		{
			cout<<"NO";
			return 0;
		}
		work();
		return 0;
	}
	
	work();
	
	return 0;
}
```

---

## 作者：1234567890sjx (赞：1)

首先显然是一个构造问题。

首先判断无解的特殊情况。

容易发现，因为区间是呈覆盖现象（有点说的不清楚），所以最后一个插入的元素 $m$ 一定需要在序列里。所以如果 $m$ 不在序列里那么显然无解。

同理，如果两个相同的数字分别在 $l$ 和 $r$，那么若有一个位置 $p$ 满足 $l<p<r$ 并且 $a_l>a_p$，也就是两个相同的数之间有比这个数小的数，那么因为是不同的数区间覆盖所以无解。

那么考虑构造一组解。

容易发现对于每一个数 $x$ 覆盖的区间 $[l,r]$，显然可以先把这个区间在现在的数组里找出来，然后对 $l\sim r$  这一段区间全部区间覆盖成 $x$ 即可。

但是数组中可能存在一个数 $x$ 满足这个数组中并没有出现过这个数！

这样就麻烦了。

那怎么做？发现操作是区间覆盖操作。

通过前面判断无解的分析，发现 $m$ 数所在的区间是必然存在的。找到 $m$ 数覆盖的区间 $[l',r']$，在区间 $[l',r']$ 中等概率随机一个整数 $p$，最后令 $l=r=p$ 即可。

当然，实际上只需要找到一个 $[l',r']$ 的子区间 $[l'',r'']$，令这个子区间是不存在数的区间即可。

那么就很简单了。用一个线段树或者珂朵莉树来维护区间推平操作，最后单点查询答案即可。

如果用线段树时间复杂度是 $O(n\log n)$ 的。~~珂朵莉树不会分析时间复杂度呜呜呜qwq~~

---

## 作者：穷源溯流 (赞：0)

$1.$  如果 $a[i]!=0$，那么一定涂有颜色，可以将 $i$ 的最远位置和最近位置记录下来，然后利用线段树区间覆盖。

$2.$ 如果 $a[i]=0$，那么举一个例子：$3\ 0\ 0\ 1\ 0\ 2 $，$3\ 0\ 0\ 1$ 里面的 $0$ 可以被染成 $3$ 或 $1$，$1\ 0\ 2$ 中的 $0$ 可以被染成 $1$ 或 $2$，这是一定可以的，因为是区间边界的扩充

值得注意的是，一个序列一定要包含 $n$ 才是合法的，因为 $[1, n- 1]$ 可以只出现在 $n$ 所出现的位置上而被覆盖掉


```
const int N = 2e5 + 5;

	int n, m, k;
	int a[N];
	int l[N], r[N];
	struct Node
	{
		int lazy;
		void update(int x){
			lazy = x;
		}
		#define lson id << 1
		#define rson (id << 1) + 1
	}t[N << 2];
	int ans[N];

void push_down(int id)
{
	int x = t[id].lazy;
	if(x){
		t[lson].update(x);
		t[rson].update(x);
		t[id].lazy = 0;
	}
}

void build(int l, int r, int id)
{
	t[id].lazy = 0;
	if(l == r) return ;
	else{
		int mid = l + r >> 1;
		build(l, mid, lson);
		build(mid + 1, r, rson);
	}
}

void update(int id, int l, int r, int L, int R, int x)
{
	if(L >= l and r >= R){
		t[id].lazy = x;
	}
	else{
		int mid = L + R >> 1;
		push_down(id);
		if(mid >= l) update(lson, l, r, L, mid, x);
		if(r >= mid + 1) update(rson, l, r, mid + 1, R, x);
	}
}

int query(int id, int l, int r, int L, int R)
{
	if(L >= l and r >= R){
		return t[id].lazy;
	}
	else{
		int mid = L + R >> 1;
		push_down(id);
		int ans = 0;
		if(mid >= l) ans = query(lson, l, r, L, mid);
		if(r >= mid + 1) ans =  query(rson, l, r, mid + 1, R);
		return ans; 
	}
}

signed main()
{
	// IOS;
	while(~ sdd(n, m)){
		ms(l, 127);
		int pos = -1;
		rep(i, 1, n){
			sd(a[i]);
			if(a[i] == 0) pos = i;
			l[a[i]] = min(l[a[i]], i);
			r[a[i]] = i;
		}
		if(r[m] == 0 and pos != -1){
			l[m] = r[m] = pos;
		}
		int ok = 1;
		build(1, n, 1);
		for(int i = 1; i <= m; i ++){
			if(r[i] == 0){
				if(i == m) ok = 0;
				continue;
			}
			update(1, l[i], r[i], 1, n, i);
		}
		for(int i = 1; i <= n; i ++){
			// if(a[i] == 0) continue;
			int x = query(1, i, i, 1, n);
			if(x == 0){
				continue;
			}
			if(a[i] == x or a[i] == 0){
				ans[i] = x;
			}
			else ok = 0;
		}
		if(ok){
			puts("YES");
			for(int i = n - 1; i >= 1; i --) if(ans[i] == 0) ans[i] = ans[i + 1];
			for(int i = 2; i <= n; i ++) if(ans[i] == 0) ans[i] = ans[i - 1];
			for(int i = 1; i <= n; i ++) printf("%d ", ans[i]);
		}
		else puts("NO");
	}
    return 0;
}
```

---

## 作者：chengni (赞：0)

先判断 $m$ 是否存在以及能否存在

对于已知的数，他不能大于左边和右边都出现过的数

对于未知的数如果还没有 $m$ 就先填 $m$，然后判断这个位置的数是否有要求，否则就填 $1$，防止对别的点造成影响

判断一个数是否在一个点左右两边都出现过不难，记录下这个值最左和最右的位置就好

这道题的主要难点在于如何求左边和右边都出现过的数里最大的那个数是什么

楼上大佬用的是 $set$ ，不习惯用 $stl$ 的话怎么办呢？用权值线段树来完成这个操作就可以了。

如果一个数在当前这个点的左右都出现过，我们就在线段树上这个值的地方加一个 $1$

查询出现过最大的数可以直接判断遍历

我习惯动态开点了，正常线段树也是可以的


```cpp
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

inline ll read(){
	char ch=getchar();ll x=0,f=1;
    while(ch<'0' || ch>'9') {
       if(ch=='-') f=-1;
	  	  ch=getchar();
	}
    while(ch<='9' && ch>='0') {
	   x=x*10+ch-'0';
	   ch=getchar();
	}
    return x*f;
}

int a[2020202];
int l[2020202],r[3202020];
int mx,mi;

struct node{
	int ls,rs;
	int s;
}t[4040404];

int rt;
int cnt=0;

void add(int &p,int l,int r,int x){
	if(p==0){
		p=++cnt;
	}
	t[p].s++;
	if(l==r) return;
	int mid=l+r>>1;
	if(x<=mid) add(t[p].ls,l,mid,x);
	else add(t[p].rs,mid+1,r,x);
}

void del(int &p,int l,int r,int x){
	if(p==0){
		p=++cnt;
	}
	t[p].s--;
	if(l==r) return;
	int mid=l+r>>1;
	if(x<=mid) del(t[p].ls,l,mid,x);
	else del(t[p].rs,mid+1,r,x);
}

int find(int p,int l,int r){
	if(l==r) return l;
	int mid=l+r>>1;
	if(t[t[p].rs].s!=0){
		return find(t[p].rs,mid+1,r);
	}
	return find(t[p].ls,l,mid);
}

int main(){
	int n=read(),m=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		mx=max(mx,a[i]);mi=min(mi,a[i]);
		r[a[i]]=max(r[a[i]],i);
		if(l[a[i]]==0) l[a[i]]=i;
	}
	for(int i=1;i<=n;i++){
		if(a[i]==0){
			if(mx<m) {
				a[i]=m;
				mx=m;
			}
			else {
				if(t[rt].s!=0) a[i]=find(rt,1,m);
				else a[i]=1;
			}
		}
		else{
			if(l[a[i]]==i) add(rt,1,m,a[i]);
			if(r[a[i]]==i) del(rt,1,m,a[i]);
			if(t[rt].s!=0) {
				if(a[i]<find(rt,1,m)) {
					puts("NO");
					return 0;
				}
			}
		}
	}
	if(mx<m){
		puts("NO");
		return 0;
	}
	puts("YES");
	for(int i=1;i<=n;i++){
		printf("%d ",a[i]);
	}
	return 0;
}

```


---

## 作者：Jμdge (赞：0)

表示并不会做此题，于是用了非常麻烦的方法。


首先我用了st表处理区间最小值以此判断是否有解。


然后我用了线段树扫描线来处理答案。

扫描线？这里有道比较经典的题：[【USACO07OPEN】城市的地平线City Horizon](https://www.luogu.org/problemnew/show/P2061)

最后就WA掉了。
因为没搞清楚题目。。。q 次操作是必须进行的啊，所以 q 一定会在最后的数列中出现，否则就不满足题目条件了。如果 q 数组无论如何也不会出现在最后的数列中的话，输出 "NO" 就好了

代码如下。

```
//by Judge
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#define P pair<int,int> 
#ifndef Judge
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
#endif
using namespace std;
const int M=2e5+11;
char buf[1<<21],*p1=buf,*p2=buf;
inline int read(){
    int x=0,f=1; char c=getchar();
    for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
    for(;isdigit(c);c=getchar()) x=x*10+c-'0'; return x*f;
} char sr[1<<21],z[20];int C=-1,Z;
inline void Ot(){fwrite(sr,1,C+1,stdout),C=-1;}
void print(int x,char ch='\n'){
    if(C>1<<20)Ot(); while(z[++Z]=x%10+48,x/=10);
    while(sr[++C]=z[Z],--Z);sr[++C]=ch;
} int n,m,flag,a[M],vis[M],fir[M],las[M],lg[M];
vector<P> vec[M]; int t[M<<2],mx[M<<2],st[M][21];
#define mid (l+r>>1)
#define ls k<<1
#define rs k<<1|1
#define lson ls,l,mid
#define rson rs,mid+1,r
inline void pushup(int k,int l,int r){
	if(t[k]) mx[k]=r-l+1;
	else if(l==r) mx[k]=0;
	else mx[k]=mx[rs]+mx[ls];
} void update(int k,int l,int r,int pos,int v){
	if(r<=pos) return t[k]+=v,pushup(k,l,r);
	if(mid<pos) update(rson,pos,v);
	if(l<=pos) update(lson,pos,v); pushup(k,l,r); 
} inline int get(int l,int r){
	int len=r-l+1,k=lg[len];
	return min(st[l][k],st[r-(1<<k)+1][k]);
} int main(){ n=read(),m=read();
	for(int i=1;i<=n;++i){
		st[i][0]=a[i]=read(),las[a[i]]=i;
		if(!fir[a[i]]) fir[a[i]]=i;
	} int num=0;
	for(int i=1;i<=n;lg[i++]=num)
		if((1<<num+1)<=i) ++num;
	
	for(int i=1;i<=n;++i) if(!st[i][0]) st[i][0]=m+1,flag=i;
	for(int j=1;j<=lg[n];++j) for(int i=1;i+(1<<j)-1<=n;++i)
		st[i][j]=min(st[i][j-1],st[i+(1<<j-1)][j-1]);
	
	fir[1]=1,las[1]=n;
	if(!fir[m]){
		if(!flag) return puts("NO"),0;
		else fir[m]=las[m]=flag;
	} for(int i=1;i<=m;++i) if(fir[i]){
		vec[fir[i]].push_back(P(i,1)),
		vec[las[i]+1].push_back(P(i,-1));
		if(get(fir[i],las[i])<i) return puts("NO"),0;
	} puts("YES");
	for(int i=1;i<=n;print(mx[1],' '),++i)
		for(int j=0;j<vec[i].size();++j)
			update(1,1,m,vec[i][j].first,vec[i][j].second);
	sr[++C]='\n'; return Ot(),0;
}
```


代码看起来很烦（看完楼上大佬的题解我自己都这么觉得）

但无非就是 读优输优 线段树 st表 长了点嘛，

而且思路很清晰，何况网上有人的思路也和我差不多.

所以...（我编不下去了`_(:з」∠)_` ）


---

