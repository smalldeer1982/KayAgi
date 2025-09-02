# Approximating a Constant Range

## 题目描述

When Xellos was doing a practice course in university, he once had to measure the intensity of an effect that slowly approached equilibrium. A good way to determine the equilibrium intensity would be choosing a sufficiently large number of consecutive data points that seems as constant as possible and taking their average. Of course, with the usual sizes of data, it's nothing challenging — but why not make a similar programming contest problem while we're at it?

You're given a sequence of $ n $ data points $ a_{1},...,a_{n} $ . There aren't any big jumps between consecutive data points — for each $ 1<=i&lt;n $ , it's guaranteed that $ |a_{i+1}-a_{i}|<=1 $ .

A range $ [l,r] $ of data points is said to be almost constant if the difference between the largest and the smallest value in that range is at most $ 1 $ . Formally, let $ M $ be the maximum and $ m $ the minimum value of $ a_{i} $ for $ l<=i<=r $ ; the range $ [l,r] $ is almost constant if $ M-m<=1 $ .

Find the length of the longest almost constant range.

## 说明/提示

In the first sample, the longest almost constant range is $ [2,5] $ ; its length (the number of data points in it) is 4.

In the second sample, there are three almost constant ranges of length $ 4 $ : $ [1,4] $ , $ [6,9] $ and $ [7,10] $ ; the only almost constant range of the maximum length $ 5 $ is $ [6,10] $ .

## 样例 #1

### 输入

```
5
1 2 3 3 2
```

### 输出

```
4
```

## 样例 #2

### 输入

```
11
5 4 5 5 6 7 8 8 8 7 6
```

### 输出

```
5
```

# 题解

## 作者：Holy_Push (赞：13)

根据楼上说的，因为相邻两数不超过1，所以子串中最大值的值减最小值的结果不超过1，相当于区间内只有两个不同的数。

那很容易想到一种贪心的思想。记五个变量$sum1$,$cnt1$,$sum2$,$cnt2$，$l$，分别表示第一个值、第一个值出现的次数、第二个值、第二个值出现的次数和当前左端点。每读入一个数$x$，就与$sum1$和$sum2$比较。如果$x$和$sum1$或$sum2$相等，那么直接在对应的$cnt$上加即可。如果都不相等，那么直接将$l$不断右移直到$sum1$或$sum2$出现次数为0，然后用$x$来替代就行了。时间复杂度$O(N)$
```cpp
#include<bits/stdc++.h>
using namespace std;

int n,l,sum1,sum2,cnt1,cnt2,a[1000000],ans;

int main()
{
	scanf("%d",&n);
	scanf("%d",&a[1]);
	l=1,sum1=a[1],cnt1=1;
	for (int i=2;i<=n;i++)
	{
		scanf("%d",&a[i]);
		if (sum1==a[i]) cnt1++;
			else if (sum2==a[i]) cnt2++;
				else 
				{
					while (cnt1&&cnt2)
					{
						if (a[l]==sum1) cnt1--;
							else cnt2--;
						l++;
					}
					if (!cnt1) sum1=a[i],cnt1=1;
						else sum2=a[i],cnt2=1;
				}
		ans=max(ans,cnt1+cnt2);
	}
	printf("%d\n",ans);
}
```


---

## 作者：Alex_Wei (赞：5)

~~平衡树 ta 不香吗？~~

~~黑题怎么能直接水过去？~~

每次扩展一个右端点，根据题目的约束更新左端点即可。

来一份 $\mathrm{Treap}$，容易理解~~又好写~~，还能练练手。

- 时间复杂度 $\mathcal O(n\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=1e5+5;
const int inf=1e9+7;
int n,a[N],ans,pos=1;
struct Treap{
	int son[N][2],cnt[N],siz[N],rd[N],val[N],R,num;
	void push(int x){siz[x]=cnt[x]+siz[son[x][0]]+siz[son[x][1]];}
	void rotate(int &x,int d){//左/右旋,Treap基础操作 
		int k=son[x][d^1];
		son[x][d^1]=son[k][d];
		son[k][d]=x;
		push(x); push(k);
		x=k;
	}
	void ins(int &x,int v){//插入,Treap基础操作 
		if(!x){
			x=++num;
			siz[num]=cnt[num]=1;
			rd[num]=rand();
			val[num]=v;
		}
		else if(val[x]==v)siz[x]++,cnt[x]++;
		else{
			int d=v>val[x];
			ins(son[x][d],v);
			if(rd[x]<rd[son[x][d]])rotate(x,d^1);
			push(x);
		}
	}
	void del(int &x,int v){//删除,Treap基础操作
		if(!x)return;
		if(v>val[x])del(son[x][1],v);
		else if(v<val[x])del(son[x][0],v);
		else if(!son[x][0]&&!son[x][1]){
			siz[x]--,cnt[x]--;
			if(siz[x]==0)x=0;
		}
		else if(son[x][0]&&!son[x][1]){
			rotate(x,1); del(son[x][1],v);
		}
		else if(son[x][1]&&!son[x][0]){
			rotate(x,0); del(son[x][0],v);
		}
		else{
			int d=rd[son[x][0]]>rd[son[x][1]];
			rotate(x,d);
			del(son[x][d],v);
		}
		push(x);
	}
	int pre(int x,int v){//前缀,Treap基础操作
		if(!x)return -inf;
		if(v<=val[x])return pre(son[x][0],v);
		else return max(val[x],pre(son[x][1],v));
	}
	int suf(int x,int v){//后缀,Treap基础操作
		if(!x)return inf;
		if(v>=val[x])return suf(son[x][1],v);
		else return min(val[x],suf(son[x][0],v));
	}
	int getdif(){//求当前区间最大值与最小值的差
		return pre(R,inf)-suf(R,-inf);
	}
}tr;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=n;i++){
		tr.ins(tr.R,a[i]);
		while(tr.getdif()>1)tr.del(tr.R,a[pos++]);//更新左端点
		ans=max(ans,i-pos+1);
	}
	cout<<ans<<endl;
    return 0;
}
```

话说这要是在 $\mathrm{CF\ Div.2\ B}$ 题上写个平衡树怕不是已经暴毙了。

---

## 作者：AFOier (赞：4)

又是一道恶评好题~

大佬们都写线段树、ST表，小蒟蒻只会用dp做

维护一个$dp[n][2]$数组，设当前数值为$sum$，$dp[i][0]$维护当前点向后延伸的数值为$sum$和$sum-1$的子串的最大长度，$dp[i][1]$维护当前点向后延伸的数值为$sum$和$sum+1$的子串的最大长度。

显然若$a[i]=a[i+1]$，
则有$dp[i][0]=dp[i+1][0]+1,dp[i][1]=dp[i+1][1]+1$

若$a[i]=a[i+1]-1$，则有$dp[i][0]=dp[i+1][1]+1$

若$a[i]=a[i+1]+1$，则有$dp[i][1]=dp[i+1][0]+1$

倒着遍历即可。时间复杂度$O(n)$

代码：
```
#include <cstdio>
#include <iostream>
using namespace std;
int n,a[100001],dp[100001][2];
int ans;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	dp[n][0]=dp[n][1]=1;
	for(int i=n-1;i>=1;i--){
		dp[i][0]=dp[i][1]=1;
		if(a[i]==a[i+1])dp[i][0]=dp[i+1][0]+1,dp[i][1]=dp[i+1][1]+1;
		else if(a[i]==a[i+1]+1)dp[i][0]=dp[i+1][1]+1;
		else if(a[i]==a[i+1]-1)dp[i][1]=dp[i+1][0]+1;
		ans=max(ans,max(dp[i][0],dp[i][1]));
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：to_be_continued (赞：3)

这题好吧，恶评 emmm

首先这题很水。题意如下

给你一串数，让你找到当中一个子串，使得整个串的最大值-最小值不小于1。

~~那不是很简单吗~~

我直接写暴力，emm

先给一个没有加过优化的。

```cpp
#include <cstdio>
#include <map>

using namespace std;

inline int read(){//玄学快读
    int AK=1,IOI=0;
    char ch=0;
    while (ch<'0'||ch>'9'){
        AK=ch=='-'?-1:1;
        ch=getchar();
    }
    while (ch<='9'&&ch>='0'){
        IOI*=10;
        IOI+=ch-48;
        ch=getchar();
    }
    return AK*IOI;
}

int a[100001];

inline int max(int x,int y){
    return x>y?x:y;
}
inline int min(int x,int y){
    return x<y?x:y;
}
int main(){
    int n=read();
    for (int i=1;i<=n;i++){
        a[i]=read();
    }
    int answer=0;
    for (int i=1;i<=n;i++){
        int now_max=a[i],now_min=a[i];//当前最大值和最小值
        int now_answer=1;//当前的最长子串
        for (int j=i+1;j<=n;j++){
            now_max=max(now_max,a[j]);//找最大值
            now_min=min(now_min,a[j]);//找最小值
            if (now_max-now_min>1) break;//如果不符合要求，那么就退出
            now_answer++;
        }
        answer=max(now_answer,answer);//保存答案
    }
    printf("%d",answer);
}
```

我们发现它很轻松的T了，那么有什么地方可以优化呢。

我们发现如果他的答案很大时那么这个时间肯定是很大的。

那么答案很大就说明j的枚举很大。

答案很大的话，后半个可以完全不用做啊。因为就算后面符合条件，但是它肯定没有现在的子串长不是吗。那么直接把后面半个跳出，那么就不T了。



```cpp
#include <cstdio>
#include <map>

using namespace std;

inline int read(){//玄学快读
    int AK=1,IOI=0;
    char ch=0;
    while (ch<'0'||ch>'9'){
        AK=ch=='-'?-1:1;
        ch=getchar();
    }
    while (ch<='9'&&ch>='0'){
        IOI*=10;
        IOI+=ch-48;
        ch=getchar();
    }
    return AK*IOI;
}

int a[100001];

inline int max(int x,int y){
    return x>y?x:y;
}
inline int min(int x,int y){
    return x<y?x:y;
}
int main(){
    int n=read();
    for (int i=1;i<=n;i++){
        a[i]=read();
    }
    int answer=0;
    for (int i=1;i<=n;i++){
        if (n-answer<i) break;//AC与TLE的区别
        int now_max=a[i],now_min=a[i];//当前最大值和最小值
        int now_answer=1;//当前的最长子串
        for (int j=i+1;j<=n;j++){
            now_max=max(now_max,a[j]);//找最大值
            now_min=min(now_min,a[j]);//找最小值
            if (now_max-now_min>1) break;//如果不符合要求，那么就退出
            now_answer++;
        }
        answer=max(now_answer,answer);//保存答案
    }
    printf("%d",answer);
}
```


此人为C++蒟蒻，在此，膜拜各位C++巨爷。

---

## 作者：静静是他的， (赞：3)

这一道题说求一个序列的字串中能满足 最大值-最小值<=0 的最长那一个，所以想到了二分答案。

二分一段的长度，如果一段的长度不满足的话，那么比它更长的一段也一段不满足，所以能满足二分的单调性。

区间最小值最大值可以使用st表，也可以使用线段树。

具体的做法是二分答案+st表，先二分长度，再使用check函数枚举某一个以i开头的一段，如果这一段的最大值-最小值相差不超过1,那么这一段就满足，否则不满足。

时间复杂度是 $ O(nlogn) $

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

int n,m,ans;
int ai[100010],f[1<<17][20],f1[1<<17][20];

int Max(int l,int r)
{
	int k=log(r-l+1)/log(2);
	return max(f[l][k],f[r-(1<<k)+1][k]); 
} 
int Min(int l,int r)
{
	int k=log(r-l+1)/log(2);
	return min(f1[l][k],f1[r-(1<<k)+1][k]); 
} 
bool check(int k)
{
	for(int i=1;i+k-1<=n;i++)
		if (Max(i,i+k-1)-Min(i,i+k-1)<=1) return true;
	return false;
}

int main()
{

	cin>>n;
	for(int i=1;i<=n;i++) cin>>ai[i],f[i][0]=f1[i][0]=ai[i];
	for(int j=1;(1<<j)<=n;j++)
	{
		for(int i=1;i+(1<<j)-1<=n;i++)
		f[i][j]=max(f[i][j-1],f[i+(1<<(j-1))][j-1]),
		f1[i][j]=min(f1[i][j-1],f1[i+(1<<(j-1))][j-1]);
	}
	
	int l=1,r=n+1;
	while(l+1<r)
	{
		int mid=(l+r)>>1;
		if (check(mid)) l=mid;
		else r=mid;
	}
	cout<<l<<endl;
	return 0;
}

```

---

## 作者：Sooke (赞：3)

### 题意

给你一个相邻数差不超过 $1$ 的序列，求最长子串的长度，满足子串中的最大值减最小值也不超过 $1$。

### 解题思路

容易发现，满足条件的子串最多一定只有两个不同的数，根据这个性质，可以大力 $O(n)$ 维护。

但看在数据范围的面子上，这里给出一个 $O(n\log n)$ 的做法，这个做法即使相邻数差超过 $1$ 也没关系。

用一个大根堆、小根堆分别维护当前子串最大数和最小数，如果不满足条件就要把左边界往右移对吧，但堆又不能直接删除，于是再添加一个大根堆、小根堆，把删除的数往里面放。当对应的原堆和删除堆有相同的 $top$，同时删除即可。

### 代码实现

```cpp
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

inline int read() {
    char c = getchar(); int n = 0; bool f = false;
    while (c < '0' || c > '9') { if (c == '-') { f = true; } c = getchar(); }
    while (c >= '0' && c <= '9') { n = (n << 1) + (n << 3) + (c & 15); c = getchar(); }
    return f ? -n : n;
}

const int maxN = 100005;

int n, ans, a[maxN];
std::priority_queue<int> max, maxDel;
std::priority_queue<int, std::vector<int> , std::greater<int> > min, minDel;

int main() {
    n = read();
    for (int i = 1, j = 1; i <= n; i++) {
        a[i] = read(); max.push(a[i]); min.push(a[i]);
        while (max.top() - min.top() > 1) {
            maxDel.push(a[j]); minDel.push(a[j++]);
            while (maxDel.size() && max.top() == maxDel.top()) { max.pop(); maxDel.pop(); }
            while (minDel.size() && min.top() == minDel.top()) { min.pop(); minDel.pop(); }
        }
        ans = std::max(ans, i - j + 1);
    }
    printf("%d\n", ans);
    return 0;
}
```

---

## 作者：哥你挺6啊 (赞：2)

这是全洛谷最有 **_水_** 准的一道黑题

本蒟蒻的思路很简单，用线段树（或st表等）来存每一个数，树上节点表示每一段数的最大值和最小值，手动模拟队列，如果即将入队的元素和队中所有元素最大值或最小值之差>1，或者队中的最大值和最小值之差已经>1（不过好像没有必要考虑这一步），说明如果把这个数插入到队列中，队中元素无法组成一个合法的子序列，则将队首元素弹出（头指针h++），直到这个数可以和队中元素组成一个合法的子序列为止。

这样每次操作后，队中的元素构成一个合法的子序列，然后更新ans就可以了；

最后尾指针t++。

到尾指针指到最后一位后停止。

思路很简单，~~请大家原谅我对线段树的偏好~~

代码如下：

```
#include<bits/stdc++.h>
using namespace std;
struct mp{
	int l,r,w,f,m;
}p[9999999];
int n,m;
int x,y,maxx,o,a[100050],num,minn;
void build(int l,int r,int k)
{
	p[k].l=l;p[k].r=r;
	if(l==r)
	{
		scanf("%d",&p[k].w);//建树
		p[k].m=p[k].w;
		a[++num]=p[k].w;
		return;
	}
	int m=(l+r)/2;
	build(l,m,k*2);
	build(m+1,r,k*2+1);
	p[k].w=max(p[k*2].w,p[k*2+1].w);
	p[k].m=min(p[k*2].m,p[k*2+1].m);
}
void search(int k,int x,int y)
{
	if(p[k].l>=x&&p[k].r<=y)
	{
		maxx=max(maxx,p[k].w);//找最大值
		minn=min(minn,p[k].m);//找最小值
		return ;
	}
	int m=(p[k].l+p[k].r)/2;
	if(x<=m)search(k*2,x,y);
	if(y>m)search(k*2+1,x,y);
}
int main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n*4;i++)
	p[i].m=999999;//初始化
	build(1,n,1);
	int h=1,t=2,anss=1;
	while(t<=n)
	{
		maxx=0;minn=999999;
		search(1,h,t-1);
		while((abs(a[t]-maxx)>1||abs(a[t]-minn)>1||abs(maxx-minn)>1)&&h<t)
		{
			maxx=0;minn=999999;
			h++;
			search(1,h,t-1);//查弹出队首后的序列最大值和最小值
		}
		anss=max(anss,t-h+1);
		t++;
	}
	printf("%d",anss);
	return 0;
}
```

由于~~CF数据比较毒瘤~~，为了保证正确性，可能有些冗余的判断和操作，~~请各位大佬无视~~

---

## 作者：Mcggvc (赞：2)

## 题目链接：[CF602B Approximating a Constant Range](https://www.luogu.org/problemnew/show/CF602B)
## **模拟了一下就水过去了**

**其实我调了好久（~~我太弱了~~）**

需要用到几个变量：s1,c1,s2,c2,tot,ans

分别代表目前字串其中一个数的值，这个数最后出现的位置，另一个数的值，最后出现的位置，目前子串的长度，已求得的最长的长度

然后就是O（n）模拟

代码
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <queue>
#include <stack>
#include <vector>
using namespace std;
int s1,s2,c1,c2;
int a[100100];
int n,ans=-1000000;
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {cin>>a[i];}
    s1=a[1];c1=1;
    int tot=1;
    for(int i=2;i<=n;i++)
    {
        if(a[i]!=s1&&a[i]!=s2)
        {
            ans=max(ans,tot);
            if(abs(s1-a[i])<abs(s2-a[i]))
            {s2=a[i];tot=i-c2;c2=i;}
            else{s1=a[i];tot=i-c1;c1=i;}
        }
        else if(a[i]==s1) c1=i,tot++;
        else if(a[i]==s2) c2=i,tot++;
    }
    cout<<max(ans,tot);
    return 0;
}
```

**管理大大求过**

---

## 作者：shame_djj (赞：1)

一遍 AC，虽然是道恶意评测的题

原题链接[【Approximating a Constant Range】](https://www.luogu.org/problem/CF602B)

看完本题的题面和数据范围时，我一共想到了三种算法：

		1.二分答案，固定滑动窗口长度，数据结构维护区间最值

		2.滑动窗口长度可变，线段树维护区间最值（或者 ST 表，但是 ST 表常数其实是比线段树要大的）

详见我的[【[SNOI2017]炸弹】](https://162867.blog.luogu.org/solution-p5025#)的题解

		3.单调队列维护当前最值，滑动窗口

当然还有像楼上楼下说的那种维护是哪两个数的操作，但是如果把差值改成 k 就做不了了吧

三种算法的复杂度分别是

		1.O (n logn logn)

		2.O (n logn)

		3.O (n)

我首先写了第二种算法，并且提交了

用的是 线段树 + 滑动窗口

跑的也不算快，不开 O2 用了2.8 s，但是已经 AC 了

也可能是我的线段树常数太大了，QwQ~~

只追求 AC 的同学们可以离开了

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;
const int maxn = 1e5 + 10;
const int INF = 1e9;

inline int read() {
	char c = getchar(); int x = 0, f = 1;
	for (; c > '9' || c < '0'; c = getchar()) if (c == '-') f = -1;
	for (; c >='0' && c <='9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ 48);
	return x * f; 
}

int a[maxn];
int n, ans;

struct djj_lxy_Tree {
	int z_max[maxn << 2], z_min[maxn << 2];

	void build (int l, int r, int now) {
		if (l == r) {
			z_max[now] = a[l];
			z_min[now] = a[l];
			return ;
		}
		int mid = l + r >> 1;
		build (l, mid, now << 1);
		build (mid + 1, r, now << 1 | 1);
		z_min[now] = min (z_min[now << 1], z_min[now << 1 | 1]);
		z_max[now] = max (z_max[now << 1], z_max[now << 1 | 1]);
	}

	int query_min (int l, int r, int now, int nowl, int nowr) {
		if (nowl <= l && r <= nowr)
			return z_min[now];
		int mid = l + r >> 1, ans = INF;
		if (nowl <= mid)
			ans = min (ans, query_min (l, mid, now << 1, nowl, nowr));
		if (mid < nowr)
			ans = min (ans, query_min (mid + 1, r, now << 1 | 1, nowl, nowr));
		return ans;
	}
	
	int query_max (int l, int r, int now, int nowl, int nowr) {
		if (nowl <= l && r <= nowr)
			return z_max[now];
		int mid = l + r >> 1, ans = - INF;
		if (nowl <= mid)
			ans = max (ans, query_max (l, mid, now << 1, nowl, nowr));
		if (mid < nowr)
			ans = max (ans, query_max (mid + 1, r, now << 1 | 1, nowl, nowr));
		return ans;
	}
} t;

void djj_lxy () {
	n = read();
	for (register int i = 1; i <= n; i ++)
		a[i] = read();
	t.build (1, n, 1);
	int l = 1, r = 1, maxx = a[1];
	for (; r <= n; ) {
		int now_max = t.query_max (1, n, 1, l, r);
		int now_min = t.query_min (1, n, 1, l, r);
		if (now_max - now_min <= 1)
			ans = max (ans, r - l + 1), r ++;
		else
			l ++;
	}
	printf ("%d\n", ans);
}

int main () {
	djj_lxy ();
}
```

一种简单的好想的优化思路就是最大值和最小值一起计算

下面我说一下第三种 O（n）的算法

因为我在写第三种算法时其实还不会写单调队列，只是对思想有点了解

所有我其实也是在边学边说

单调队列，以维护最大值为例

要维护最大值，那就要维护一个单调递减的队列

一般使用 deque 实现

注意：单调队列加入元素时，加入下标即可，我既加入了下标，又加入了值，调了半年，改了之后才过样例

入队操作

		每当有一个新的元素入队时，先加到当前的队尾，

		把它前面所有的比它小的元素都删除

出队操作

		利用加入队列的下标判是否删除即可

本题代码，不知为何跑了 1.9 s，STL 的 deque 没开 O2，

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <deque>
#include <cmath>

using namespace std;
const int maxn = 1e5 + 10;

inline int read() {
	char c = getchar(); int x = 0, f = 1;
	for (; c > '9' || c < '0'; c = getchar()) if (c == '-') f = -1;
	for (; c >='0' && c <='9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ 48);
	return x * f;
}

int a[maxn];
int n, ans;

struct djj_queue {
	deque <int> q;

	void push_back (int i, int x) {
		if (q.empty())
			q.push_back (i);
		else if (x > a[q.back()]) {
			for (; x > a[q.back ()]; ) {
				q.pop_back ();
				if (q.empty()) break ;
			}
			q.push_back (i);
		}
		else
			q.push_back(i);
	}
	
	void pop_front (int l) {
		if (!q.empty())
			if (l == q.front())
				q.pop_front();
	}
	
	int query () {
		if (!q.empty())
			return a[q.front()];
		return 0;
	}
} djj_;

struct lxy_queue {
	deque <int> q;

	void push_back (int i, int x) {
		if (q.empty())
			q.push_back (i);
		else if (x < a[q.back()]) {
			for (; x < a[q.back ()]; ) {
				q.pop_back();
				if (q.empty()) break ;
			}
			q.push_back (i);
		}
		else
			q.push_back(i);
	}
	
	void pop_front (int l) {
		if (!q.empty())
			if (l == q.front())
				q.pop_front();
	}
	
	int query () {
		if (!q.empty())
			return a[q.front()];
		return 0;
	}
} lxy_;

void djj_lxy () {
	n = read();
	for (register int i = 1; i <= n; i ++)
		a[i] = read();
	int l = 1, r = 1;
	djj_.push_back (1, a[1]);
	lxy_.push_back (1, a[1]);
	for (; r <= n; ) {
		if (r < l) {
			djj_.push_back (l, a[l]);
			lxy_.push_back(l, a[l]);
			r = l;
		}
		int now_djj = djj_.query();
		int now_lxy = lxy_.query();
		if (now_djj - now_lxy <= 1) {
			ans = max (ans, r - l + 1), r ++;
			djj_.push_back (r, a[r]);
			lxy_.push_back (r, a[r]);
		}
		else {
			djj_.pop_front (l);
			lxy_.pop_front (l);
			l ++;
		}
	}
	printf ("%d\n", ans);
	exit (0);
}

int main () {
	djj_lxy ();
}
```

那就先这样吧，复习滑动窗口顺带学一下单调队列

距离 CSP-S 还有十天，祝大家 rp ++

也希望自己能更努力一些，加油

---

## 作者：pipiispig (赞：1)

###
这个题的做法很多呢但是为什么没人用单调队列来做呢
单调队列完全可以做这个题QwQ;
就是维护两个队列呀，嘻嘻；
```
#include<iostream>
#include<cstdio>
#include<deque>
using namespace std;
const int N=100005;
struct node
{
	int ans;
	int length;
};
deque<node>q1;
deque<node>q2;
int n,s[N],ans=-1,pre;//pre1千万不要中间清零QwQ
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&s[i]);
	for(int i=1;i<=n;i++)
	{
		while(!q1.empty()&&q1.back().ans<s[i])q1.pop_back();//单调递增队列
		while(!q2.empty()&&q2.back().ans>s[i])q2.pop_back();////单调递减队列
		q1.push_back((node){s[i],i});
		q2.push_back((node){s[i],i});
		while(q1.front().ans-q2.front().ans>1&&!q1.empty()&&!q2.empty())
		{
			if(q1.front().length>q2.front().length){pre=q2.front().length+1;q2.pop_front();}
			else {pre=q1.front().length+1;q1.pop_front();}
		}
		ans=max(ans,i-pre+1);//这个地方注意了，我为了好理解写的pre+1,也可以本来就把pre设成pre+1，但是不大好理解是不是；
	}
	printf("%d\n",ans);
	return 0;
}
```

---

