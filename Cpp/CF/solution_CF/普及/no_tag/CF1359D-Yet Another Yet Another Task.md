# Yet Another Yet Another Task

## 题目描述

Alice and Bob are playing yet another card game. This time the rules are the following. There are $ n $ cards lying in a row in front of them. The $ i $ -th card has value $ a_i $ .

First, Alice chooses a non-empty consecutive segment of cards $ [l; r] $ ( $ l \le r $ ). After that Bob removes a single card $ j $ from that segment $ (l \le j \le r) $ . The score of the game is the total value of the remaining cards on the segment $ (a_l + a_{l + 1} + \dots + a_{j - 1} + a_{j + 1} + \dots + a_{r - 1} + a_r) $ . In particular, if Alice chooses a segment with just one element, then the score after Bob removes the only card is $ 0 $ .

Alice wants to make the score as big as possible. Bob takes such a card that the score is as small as possible.

What segment should Alice choose so that the score is maximum possible? Output the maximum score.

## 说明/提示

In the first example Alice chooses a segment $ [1;5] $ — the entire row of cards. Bob removes card $ 3 $ with the value $ 10 $ from the segment. Thus, the final score is $ 5 + (-2) + (-1) + 4 = 6 $ .

In the second example Alice chooses a segment $ [1;4] $ , so that Bob removes either card $ 1 $ or $ 3 $ with the value $ 5 $ , making the answer $ 5 + 2 + 3 = 10 $ .

In the third example Alice can choose any of the segments of length $ 1 $ : $ [1;1] $ , $ [2;2] $ or $ [3;3] $ . Bob removes the only card, so the score is $ 0 $ . If Alice chooses some other segment then the answer will be less than $ 0 $ .

## 样例 #1

### 输入

```
5
5 -2 10 -1 4```

### 输出

```
6```

## 样例 #2

### 输入

```
8
5 2 5 3 -30 -30 6 9```

### 输出

```
10```

## 样例 #3

### 输入

```
3
-10 6 -15```

### 输出

```
0```

# 题解

## 作者：45dinо (赞：12)

### 前言

看到巨佬们都用的是一些奇怪的算法+数据结构，但远没有那么复杂。

~~黄题就要用黄题的方法做~~

~~标题套娃好评~~

~~翻译人名为什么要加粗QAQ~~

### 整体思路

注意到尽管 $n$ 的数据范围较大，可以卡掉 $O(n^3)$ 的暴力，但 $a_i$ 的数据范围小的可怜，于是将思路转换为枚举最大值求答案。

**注意一个细节：** 由于最大值应该是正整数，所以只用枚举 $[0,30]$ 之间的数即可。

设当前的最大值为 $i$ ，目前只要求区间元素最大和即可。

假如这个区间不是 $[l,r]$，而是 $[1,r]$ ,怎么做？

可以想到，直接枚举 $r$，对于每一个 $r$，更新答案。

**注意一个细节：** 当 $a_r>i$ 时，终止循环。

但是现在左区间并不是固定的，怎么处理？

很容易。

如果 $[1,l]$ 的元素和为负数，则 $[1,r]$ 的元素和小于 $[l,r]$ 。

根据这个，在枚举 $r$ 时特判，当 $[1,r]$ 的元素和为负数时，将计数器清零，此时 $l=r$ 。

开始想到这个做法时，我还有一个问题，在枚举最大值时，如何保证这一区间有这个最大值？换句话讲，有没有可能最后答案区间的最大值不是 $i$？

肯定是不可能的。

显而易见，答案的最大值不可能大于 $i$。

其实也不能小于 $i$，因为此时不是最优的。

用这样的一种单重限制就可以做到双重限制，实在是巧妙。

喜闻乐见的代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100001],ans,res;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=31;i++)
	{
		res=0;
		for(int j=1;j<=n;j++)
		{
			res+=a[j];
			if(a[j]>i)
				res=0;
			res=max(res,0);
			ans=max(ans,res-i);
		}
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：Lily_White (赞：6)

题目本质是要你选出一个区间 $[l, r]$，使得
$$
\sum^{r}_{i = l}a_i-\max^{r}_{i = l}a_i
$$
的值尽量大。

注意到 $a_i$ 的数据范围极小，考虑将它作为复杂度的一部分。这时我们可以枚举 $l$ 和 $r$ 可以得到一个复杂度为 $O(n^2\max a_i)$ 的算法。

那么，我们应该如何优化这个算法呢？

考虑减少一维枚举，也就是，减少枚举 $l$ 的过程。

维护一个前缀和，因为我们只在乎最大值，因此如果遇到 $\sum^{r}_{i=1}a_i$ 的值为负数，那么**将 $[1,r]$ 段加入答案一定不会更优。**

但是，我们并没有保证选出的区间里一定包含枚举的最大值。尽管如此。我们还是可以证明这么做是正确的。

**证明** 如果这么做不正确，则必定能够分为下面两种情况：
1. 区间内的最大值**大于**枚举的最大值

	这时我们可以特判解决：如果 $a_r > \text{maxValue}$，那么直接把维护的前缀和清成 $0$，不选择这一段。
    
2. 区间内的最大值**小于**枚举的最大值
	
    这时，我们在枚举区间内的最大值的时候，应该对同一个区间得到更优的解，因此可以不用考虑。
    
综上，我们得到了下面的算法：

$$
\qquad\begin{array}{l}
\textbf{for } m \textbf{  in } [1\ldots 31] \textbf{ do}\\
\qquad res \gets 0\\
\qquad \textbf{for } r \textbf{  in } [1\ldots n] \textbf{ do}\\
\qquad \qquad sum \gets sum + a_r\\
\qquad \qquad \textbf{if } a_r > m \textbf{ or } sum < 0 \textbf{ then}\\
\qquad \qquad \qquad sum \gets 0\\
\qquad \qquad \textbf{end }\\
\qquad \qquad ans \gets \min(ans, sum - m)\\
\qquad \textbf{end}\\
\textbf{end}\\
\textbf{return } ans
\end{array}
$$

---

## 作者：Tenshi (赞：3)

~~这题难度评得是不是太低了 qwq，它在 CF 上的过题人数甚至不到两千。~~

## 分析

我们记读入的数组为 `w[]`。

我的思路是从左到右枚举位置 $i$，然后找 $i$ 最左边的点 $x$ 使得对于 $j\in [x, i-1]$ 有 $w[i] \leq w[i]$，类似地找到 $i$ 最右边的点 $y$ 使得 $j\in [i+1, y]$ 有 $w[y]\leq w[i]$。

因为最值是具有单调性的，我们可以用二分和 ST 表来实现上面的查找过程。

接下来我们从 $[x, i-1]$ 找到最大的后缀和以及从 $[i+1, y]$ 找到最大的前缀和，这一步也可以用 ST 表来解决，最后更新答案即可。

细节见代码：

```cpp
#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;

#define endl '\n'
#define debug(x) cerr << #x << ": " << x << endl
#define pb push_back
#define eb emplace_back
#define set0(a) memset(a,0,sizeof(a))
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define dwn(i,a,b) for(int i=(a);i>=(b);i--)

#define INF 0x3f3f3f3f

inline void read(int &x) {
    int s=0;x=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-')x=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') s=(s<<3)+(s<<1)+ch-'0',ch=getchar();
    x*=s;
}

const int N=1e5+5;

int n;
int w[N];
int Log[N];

void init(){
	Log[1]=0;
	rep(i,2,N-1) Log[i]=Log[i/2]+1;
}

struct ST{
	int f[N][25];
	
	void init(int *a){
		rep(i,1,n) f[i][0]=a[i];
	}
	
	void build(){
		rep(j,1,20) for(int i=1; i+(1<<j)-1<=n; i++)
			f[i][j]=max(f[i][j-1], f[i+(1<<j-1)][j-1]);
	}
	
	int query(int l, int r){
		int k=Log[r-l+1];
		return max(f[l][k], f[r-(1<<k)+1][k]);
	}
}a, p, q;

int pre[N], suf[N];

int find(int l, int r, int v, bool op){
	int L=l, R=r;
	if(op){
		while(L<R){
			int mid=L+R>>1;
			if(a.query(mid, r)<=v) R=mid;
			else L=mid+1;
		}
		if(a.query(L, r)>v) return 0;
		else return L;
	}
	else{
		while(L<R){
			int mid=L+R+1>>1;
			if(a.query(l, mid)<=v) L=mid;
			else R=mid-1;
		}
		if(a.query(l, L)>v) return 0;
		else return L;
	}
}

int main(){
	init();
	read(n);
	rep(i,1,n) read(w[i]), pre[i]=pre[i-1]+w[i];
	dwn(i,n,1) suf[i]=suf[i+1]+w[i];
	
	a.init(w);
	p.init(pre);
	q.init(suf);
	
	a.build(), p.build(), q.build();
	
	int res=0;
	rep(i,1,n){
		int x, y;
		x=y=0;
		
		if(i-1>0) x=find(1, i-1, w[i], 1);
		if(i+1<=n) y=find(i+1, n, w[i], 0);
		
		int t=0;
		if(x) t+=max(0, q.query(x, i-1)-suf[i]); // 这里需要取 max(0, )，因为我们有权利不取这部分。
		if(y) t+=max(0, p.query(i+1, y)-pre[i]);
		res=max(res, t);
	}
	
	cout<<res<<endl;
	
	return 0;
}
```

附送 debug 数据：
```
in:
202
28 17 17 -25 -26 -17 18 1 16 -26 -30 8 -22 17 -20 16 -23 16 -25 3 21 27 -21 -16 -8 21 -22 19 10 -11 -18 -27 -15 -4 6 -22 -30 -25 -18 -6 -27 18 -17 -7 -30 -16 -30 -17 -23 21 -16 27 -14 -18 18 -7 -4 -28 -19 -23 27 0 -8 -6 4 -3 -3 28 -30 11 -10 -2 6 -21 1 -13 -22 -22 22 -9 -23 -6 19 4 -10 -10 -12 10 -25 -3 -20 -29 28 10 7 11 17 27 -30 -20 -12 -24 16 -23 -10 -7 -29 -12 -25 -30 -18 24 11 -23 4 8 0 -11 -3 21 -2 3 -25 -18 2 -26 4 5 27 15 -11 -23 4 -8 -14 -6 13 -20 -3 1 24 4 -4 -19 -29 -11 -25 -7 -7 26 -11 23 -19 -2 -15 0 5 -3 -23 24 2 19 -14 28 -9 -26 -9 -5 -23 -7 -22 6 -6 -23 -9 8 17 -29 -12 -4 4 14 8 -24 -1 -5 -28 -23 24 17 -25 12 -29 14 13 17 -11 19 27 6 -17 3 

out:
72

=======================

in:
7
-5 7 -10 1 1 -8 3 

out:
1
```

---

## 作者：AIskeleton (赞：2)

[博客园查看](https://www.cnblogs.com/AIskeleton/p/16683812.html)

提供一种 DP 做法。

可以发现，$a_i$ 的值域不大，可以在复杂度中出现。

设 $f_{i,j}$ 为 **当前选择段尾为 $i$，最大值为 $j$ 时的最优答案。**

那么不难推出状态转移方程：

$\begin{cases} f_{i,a_i} = f_{i-1,j} + j & j\le a_i \\f_{i,j} =\max \left(f_{i-1,j} + a_i,f_{i,j} \right) &j > a_i\end{cases}$

因为状态是以 $i$ 为结束，所以最后的答案要遍历整个 $f$ 数组。

**时间复杂度：$O(60 \cdot n)$**。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define L(i,j,k) for(int (i)=(j);i<=(k);(i)++)
#define FST ios::sync_with_stdio(0);cin.tie(0);
const int N=1e5+10,INF=1e18;
int n,a[N],ans,f[N][65];
void work(){
  cin>>n;L(i,1,n) cin>>a[i];
  L(i,1,n) L(j,0,61) f[i][j]=-INF;
  f[1][a[1]+30]=0;
  L(i,2,n){
    int x=a[i]+30;f[i][x]=0;
    L(j,0,x) f[i][x]=max(f[i][x],f[i-1][j]+j-30);
    L(j,x+1,60) f[i][j]=max(f[i][j],f[i-1][j]+a[i]);
  }L(i,1,n) L(j,0,60) ans=max(ans,f[i][j]);cout<<ans;
}signed main(){
  freopen("test.in","r",stdin);
  FST work();
}
```

---

## 作者：fighter (赞：2)

扫描线大佬真的强……

我来说说我的奇怪做法。

根据题意，只要先手选定一个区间之后，拿掉的一定是最大值，那么我们可以考虑枚举这个被拿掉的最大值。

于是考虑每个数作为最大值能影响的范围，显然可以用单调栈求出左右第一个比它大的。

记$i$在$[l,r]$内是最大值，那么我们就是要从这个位置开始，分别向左向右找到一段和最大的子段。

先考虑右边，左边同理。我们对原序列进行前缀和，那么也就是要找到$[i,r]$中前缀和的最大值。所以我们用st表预处理，查询区间最大值即可。

代码中为了方便，开了正反两个数组，分别处理左右情况。

```cpp
#include <bits/stdc++.h>
#define MAX 100005
using namespace std;

int n;
int a[MAX], lg[MAX];

struct solve{
    int s[MAX], st[MAX][22], r[MAX], q[MAX];

    int query(int l, int r){
        int len = lg[r-l+1];
        return max(st[l][len], st[r-(1<<len)+1][len]);
    }

    void build(int *a){
        memset(s, 0, sizeof(s));
        for(int i = 1; i <= n; i++){
            s[i] = st[i][0] = s[i-1]+a[i];
        }
        for(int j = 1; j <= 19; j++){
            for(int i = 1; i+(1<<j-1) <= n; i++){
                st[i][j] = max(st[i][j-1], st[i+(1<<j-1)][j-1]);
            }
        }
        int top = 0;
        for(int i = 1; i <= n; i++){
            while(top && a[q[top]] < a[i]) r[q[top]] = i, top--;
            q[++top] = i;
        }
        for(int i = 1; i <= top; i++){
            r[q[i]] = n+1;
        }
    }
}s1, s2;

int main()
{
    cin >> n;
    lg[0] = -1;
    for(int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
        lg[i] = lg[i/2]+1;
    }

    s1.build(a);
    reverse(a+1, a+n+1);
    s2.build(a);
    int ans = (int)-1e9;
    for(int i = 1; i <= n; i++){
        int p1 = i, p2 = n-p1+1;
        int t1 = s1.query(p1, s1.r[p1]-1)-s1.s[p1], t2 = s2.query(p2, s2.r[p2]-1)-s2.s[p2];
        ans = max(ans, t1+t2);
    }
    cout << ans << endl;

    return 0;
}
```

---

## 作者：XL4453 (赞：0)

### 解题思路：

这个题麻烦的地方就在于有去除最大值这个奇怪的操作，结合值域不大这个条件，可以考虑确定下最大值然后像正常的区间最大值一样做。

此时，由于已经确定了区间最大值，所以一旦遇到超过这个值的数就只能直接跳过（原则上最大值比取得的数大也是不行的，但是这个对于正确性没有影响，可以不写）。

这个正确性显然，在确定了减数后直接让被减数最大就会使得最终结果最大。

---
### 代码：

```cpp
#include<cstdio>
#include<queue>
using namespace std;
priority_queue <int> q;
int sum,ans,n,a[100005];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int maxn=0;maxn<=30;maxn++){
		sum=0;
		for(int i=1;i<=n;i++){
			if(a[i]>maxn){
				continue;
				sum=0;
			}
			sum+=a[i];
			ans=max(ans,sum-maxn);
			if(sum<0)sum=0;
		}
	}
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：SUNCHAOYI (赞：0)

由于 $a_i \in [-30,30]$，所以我们可以考虑枚举区间出现的最大值。由于可以只选一张牌，所以最大得分的最小值为 $0$。

那么我们首先枚举 $i \in [1,30]$，表示该段区间的最大值为 $i$，然后内层循环求和，即 `sum += a[j]`。由于最小值为 $0$，所以 `sum = max (sum,0)` 可以排除掉区间和为负数的情况。又因为第一重循环中已经限制了最大值，所以当出现 `a[j] > i` 的情况时，也要将 `sum` 更新为 $0$。答案的更新显然有 `ans = max (ans,sum - i)`，该语句成立的充分条件是序列中出现了 $i$。只需要再用一个数组记录出现数字的情况即可，注意负数的情况（我就是因为这个错误 $\texttt{RE}$ 了一次 qwq），同时还需要注意该数组在 `sum` 更新时也要同时更新。

最后来简单看一下代码：

```cpp
#include <iostream>
#include <cstdio>
#define ll long long
#define INF 0x3f3f3f3f
using namespace std;
const int MAX = 1e5 + 5;
const int MOD = 1e7 + 9;
inline int read ();
int a[MAX],sum,n,ans;
bool f[50];
int main ()
{
	n = read ();
	for (int i = 1;i <= n;++i) a[i] = read ();
	for (int i = 1;i <= 30;++i)
	{
		sum = 0;
		for (int j = 1;j <= 30;++j) f[j] = 0;
		for (int j = 1;j <= n;++j)
		{
			sum += a[j];
			if (sum < 0 || a[j] > i) sum = 0,f[i] = 0;//不符合条件就将 sum 置为 0
			else if (a[j] > 0) f[a[j]] = 1;//标记数字，注意筛去非正数
			sum = max (sum,0);
			if (f[i]) ans = max (ans,sum - i);//i 出现过
		}
	}
	printf ("%d\n",ans);
	return 0;
}
inline int read ()
{
    int s = 0;int f = 1;
    char ch = getchar ();
    while ((ch < '0' || ch > '9') && ch != EOF)
	{
        if (ch == '-') f = -1;
        ch = getchar ();
    }
    while (ch >= '0' && ch <= '9')
	{
        s = s * 10 + ch - '0';
        ch = getchar ();
    }
    return s * f;
}
```

----

后记。看了别的 $\texttt{dalao}$ 的题解，发现 `f[i]` 的设置有些多余，因为即使最大值 $i$ 没有出现，那么相当于被多减，答案一定不会最优。

---

## 作者：FZzzz (赞：0)

赛时没看到值域，就秒了个扫描线做法。

幸亏这题和 E 都很水，救了我一命。

------------
题意：选一个区间，使得区间和减去区间最大值最大。

考虑扫描线，从小到大枚举 $r$，计算相对应的最优的 $l$。

使用线段树，在 $l$ 处维护区间 $[l,r]$ 的价值，节点维护区间最大值。

在扫描到 $r$ 时，先把 $[1,r]$ 都加上 $a_r$，然后更新每个 $[l,r]$ 的最大值。

使用单调栈处理，一次可以更新一整个区间的最大值。不会的话大概可以去模板题学一下？

再不懂的话看代码吧。

时间复杂度 $O(n\log n)$。code：
```cpp
#include<algorithm>
#include<cctype>
#include<cstdio>
using namespace std;
inline int readint(){
	int x=0;
	bool f=0;
	char c=getchar();
	while(!isdigit(c)&&c!='-') c=getchar();
	if(c=='-'){
		f=1;
		c=getchar();
	}
	while(isdigit(c)){
		x=x*10+c-'0';
		c=getchar();
	}
	return f?-x:x;
}
const int maxn=1e5+5;
int n,a[maxn];
struct node{
	int l,r;
	node* ch[2];
	int mx,add;
	void pushup(){
		mx=max(ch[0]->mx,ch[1]->mx);
	}
	node(int l,int r):l(l),r(r),mx(0),add(0){
		if(l<r){
			int mid=l+(r-l)/2;
			ch[0]=new node(l,mid);
			ch[1]=new node(mid+1,r);
		}
	}
	void pushtag(int k){
		add+=k;
		mx+=k;
	}
	void pushdown(){
		ch[0]->pushtag(add);
		ch[1]->pushtag(add);
		add=0;
	}
	void modify(int ql,int qr,int k){
		if(ql<=l&&qr>=r) pushtag(k);
		else{
			pushdown();
			if(ql<=ch[0]->r) ch[0]->modify(ql,qr,k);
			if(qr>=ch[1]->l) ch[1]->modify(ql,qr,k);
			pushup();
		}
	}
}*rt;
int s[maxn],top=0;
int main(){
	#ifdef LOCAL
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	#endif
	n=readint();
	for(int i=1;i<=n;i++) a[i]=readint();
	rt=new node(1,n);
	int ans=0;
	for(int i=1;i<=n;i++){
		rt->modify(1,i,a[i]);
		while(top&&a[s[top]]<a[i]){
			rt->modify(s[top-1]+1,s[top],a[s[top]]);
			top--;
		}
		rt->modify(s[top]+1,i,-a[i]);
		s[++top]=i;
		ans=max(ans,rt->mx);
	}
	printf("%d\n",ans);
	return 0;
}
```

---

