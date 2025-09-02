# [AGC038B] Sorting a Segment

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc038/tasks/agc038_b

すぬけくんは、$ (0,1,\cdots,N-1) $ の順列 $ (P_0,P_1,\cdots,P_{N-1}) $ を持っています。

すぬけくんは、以下の操作を**ちょうど $ 1 $ 回**だけ行います。

- $ P $ の連続する $ K $ 要素を選び、それらを昇順に並び替える。

操作後の $ P $ としてありうる順列の個数を求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 200000 $
- $ 2\ \leq\ K\ \leq\ N $
- $ 0\ \leq\ P_i\ \leq\ N-1 $
- $ P_0,P_1,\cdots,P_{N-1} $ はすべて異なる。
- 入力される値はすべて整数である。

### Sample Explanation 1

操作後の $ P $ としてありうる順列は、$ (0,1,2,4,3),(0,2,1,3,4) $ の $ 2 $ 個です。

## 样例 #1

### 输入

```
5 3
0 2 1 4 3```

### 输出

```
2```

## 样例 #2

### 输入

```
4 4
0 1 2 3```

### 输出

```
1```

## 样例 #3

### 输入

```
10 4
2 0 1 3 7 5 4 6 8 9```

### 输出

```
6```

# 题解

## 作者：红尘万李 (赞：6)

# AT_agc038_b [AGC038B] Sorting a Segment 题解
[题面传送门](https://www.luogu.com.cn/problem/AT_agc038_b)

------------
## 题意概括
题目要我们求的是：将 $n$ 个数构成的排列进行**一次**排序，这次排序将选择长度为 $k$ 的区间，并将区间内的数进行升序排序，试问最后能得到多少种不同的序列。

显然，我们可以理解为，一个长度为 $k$ 的窗口可以在长度为 $n$ 的窗框上任意滑动至某一位置，并把窗框覆盖的地方进行升序排序，求最后可以得到多少种不同的序列。

------------
## 题目分析
由于窗口在窗框上有 $n-k+1$ 种位置，所以我们可以得到 $n-k+1$ 个排列，且有可能重复。

因为题目要求的是不同的序列数，所以接下来我们进行去重操作。有两种情况需要去重：

1. 窗口内的数列本来就是升序的，排序后相对原序列没有任何改变；

2. 窗口在某一个位置时，其内部序列的最小值在窗口左端，在相邻的下一个位置时，其内部序列的最大值在窗口右端。是不是有些绕？下面是 $n=4,k=3$，原始序列 $a$ 为 ${2,5,3,8}$ 的情况，附图以详细分析：![刷新试试？](https://cdn.luogu.com.cn/upload/image_hosting/a479bptx.png)当窗口滑至红色部分（即区间为 $[i,i+k-1]$）时，我们发现，$2$ 为该窗口内的最小值，且在窗口的最左端，那么升序排序后将不会改变 $2$ 的位置；当窗口滑至蓝色部分（即区间为 $[i+1,i+k]$）时，我们发现，$8$ 为该窗口内的最大值，且在窗口的最右端，那么升序排序后将不会改变 $8$ 的位置。这样的两次排序都只改变了 $5$ 和 $3$ 的位置，所以我们可以认为这两次排序是等价的。

其实不难发现，上述两种情况可以统一，因为第一种情况的窗口内序列同样满足第二种情况。只不过输入的序列不保证数字各不相等，所以如果要统一，我们需要进行额外的判断。因此，我们这里分成两种情况讨论:

1. 对于第一种情况，我们可以使用一个数组 $b$，储存当前位置**连续升序**的个数。什么意思？看图秒懂：![](https://cdn.luogu.com.cn/upload/image_hosting/he4970kb.png)换句话说，$b_i$ 储存的数是序列 $a$ 中直到 $a_i$ 已经连续升序的数的个数。储存了这样一个数组的用处在于，对于每一个 $b_i$，如果 $k≤b_i$，那么 $[a_{i-k+1},a_i]$ 一定是升序的，也就是说此时 $a$ 中连续升序的个数大于等于了区间的长度 $k$。通过这个 $b$ 数组，我们可以求出有 $x$ 个长度为 $k$ 的区间是升序的，并将 $ans$ 减去 $x$ 即可。如果 $x>0$，我们还需将 $ans+1$，因为所有的第一种情况是会产生一个和原始序列相同的序列的，正如第二个样例，输入为 ```4 4 0 1 2 3```，输出为 ```1```，而不是 ```0```；

2. 第二种情况就是一个很明显的单调队列求区间的最大值和最小值。根据我们刚才的分析，我们需要判断窗口右端是否为最大值，以及窗口左端是否为最小值。因此我们考虑使用 bool 型的数组 $maxa$ 和 $mina$ 分别储存当前位置的 $a_i$ 作为某次窗口的右端是否为窗口内部序列最大值，以及作为某次窗口的左端是否为窗口内部序列最小值。对于某个窗口，如果 $mina_i$ 为真，且 $maxa_{i+k}$ 为真，我们便可认为对 $[a_i,a_{i+k-1}]$ 排序和对 $[a_{i+1},a_{i+k}]$ 排序得到的序列是相同的，并将 $ans-1$。
------------
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans,k,a[200001],b[200001];
bool t,maxa[200001],mina[200001];//变量名如题意，t 待会儿会用到
deque<int> q,r;//原生态非模拟队列，如下写法为标准单调队列模板
int main()
{
	scanf("%d%d",&n,&k);
	ans=n-k+1;
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)//从左往右找
	{
		while(!q.empty()&&a[q.back()]<a[i])
			q.pop_back();
		q.push_back(i);
		if(i>k)
			while(!q.empty()&&q.front()<i-k+1)//+1 不能忘！
				q.pop_front();
		maxa[i]=a[q.front()]<=a[i];//判断该点在作为窗口最右端时是否为窗口内部序列最大值
	}
	for(int i=n;i>=1;i--)//从右往左找
	{
		while(!r.empty()&&a[r.back()]>a[i])
			r.pop_back();
		r.push_back(i);
		if(i<n-k+1)
			while(!r.empty()&&r.front()>i+k-1)//-1 不能忘！
				r.pop_front();
		mina[i]=a[r.front()]>=a[i];//判断该点在作为窗口最左端时是否为窗口内部序列最小值
	}
	b[1]=1;
	for(int i=2;i<=n;i++)
	{
		if(a[i]>=a[i-1])b[i]=b[i-1]+1;
		else b[i]=1;//如题目分析中的 b 数组
		if(k<=b[i])
		{
			ans--;
			t=1;//t 用于判断题目分析中的 x 是否大于 0
		}
		else if(i>k)
			if(mina[i-k]&&maxa[i])ans--;
	}
	if(t)ans++;//如题目分析，若 x>0，ans+1
	printf("%d",ans);
	return 0;
}
```
记得，顶一下！

---

## 作者：Limit (赞：4)

# 题目大意

给出一个 $0\sim n-1$ 的排列,每次操作会将一个长度为 $k$ 的子串从小到大排序,问经过一次操作后会产生多少种不同的排列.

# 分析

显然有 $n-k+1$ 种排序的方式,但是在这当中可能会存在一些重复的,经过一些简单的分析不难发现重复只有两种情况:

1. 这次排序并没有改变这个序列,也就是说这次排序的区间本来就是有序的.这种情况下的所有状况都只会产生一种结果.
2. 假如某次排序的左端点为 $l$ 右端点为 $l+k-1$,那么这次排序可能与 $l-1\sim l+k-2$ 这次排序相同,且相同的条件为 $l+k-1$ 位置上的数比 $[l,l+k-2]$ 中的数都要大(这样在排序后才不会改变位置),$l-1$ 位置上的数要比 $[l,l+k-2]$ 都要小.因为区间的长度是固定的,显然可以单调队列解决.

# 代码

```cpp
#include<bits/stdc++.h>
#define REP(i,first,last) for(int i=first;i<=last;++i)
#define DOW(i,first,last) for(int i=first;last<=i;--i)
//宏定义模板
namespace IO
//快读模板
using namespace IO;
using namespace std;
const int MAXN=2e5+5;
int n,k;
int arr[MAXN];
int que[MAXN];
bool maxr[MAXN],minl[MAXN];
int order[MAXN];
int main()
{
	Read(n,k);
	REP(i,1,n)
	{
		Read(arr[i]);
	}
	int head=0,tail=0;
	REP(i,1,n)//单调队列处理长度为 k 的区间的最大值和最小值
	{
		while(head<=tail&&arr[que[tail]]<arr[i])
		{
			--tail;
		}
		que[++tail]=i;
		while(head<=tail&&k<i-que[head])
		{
			++head;
		}
		maxr[i]=arr[que[head]]<=arr[i];
	}
	head=0;
	tail=0;
	DOW(i,n,1)
	{
		while(head<=tail&&arr[i]<arr[que[tail]])
		{
			--tail;
		}
		que[++tail]=i;
		while(head<=tail&&k<que[head]-i)
		{
			++head;
		}
		minl[i]=arr[i]<=arr[que[head]];
	}
	order[1]=1;
	int answer=n-k+1;
	bool flag=1;
	REP(i,2,n)//判断第一种情况
	{
		order[i]=arr[i-1]<arr[i]?order[i-1]+1:1;
		if(k<=order[i])
		{
			answer+=flag;//所有的第一种情况总共会产生一个贡献
			flag=0;
			--answer;
		}
	}
	REP(i,k+1,n)
	{
		if(order[i]<k&&order[i-1]<k&&minl[i-k]&&maxr[i])//在不满足第一种的情况下判断第二种情况
		{
			--answer;
		}
	}
	Writeln(answer);
	return 0;
}
```



---

## 作者：Caro23333 (赞：3)

没人的话还是抢个一血。

首先不难发现，排序后结果相同等价于排序时位置发生变化的数的集合相同（不难自证）。

考虑区间在移动的过程中，两个相邻的位置$[x,x+k-1]$和$[x+1,x+k]$，可以发现在这两次排序中，$[x+1,x+k-1]$上的数变化情况相同，或者说 _$[x+1,x+k-1]$上的数_ 和 _发生了变化的数_ 这两个集合的交集是不变的。

所以要判断这两次变化集合是否相同，只要看$a_x$是否在对$[x,x+k-1]$排序时变化位置以及$a_{x+k}$是否在对$[x+1,x+k]$排序时变化位置即可：如果二者满足至少其一，则两次变化的集合一定不同，排序结果一定不同；否则集合与排序结果一定相同。

但是要注意特判一种情况：如果$[x+1,x+k-1]$中的变化的数的集合非空，那么一定不会被重复计算；但是如果$[x+1,x+k-1]$中没有数发生变化，而$a_x$发生变化，$a_{x+k}$不发生变化（这意味着整个序列没有变化），那么按照上面的统计方式$[x+1,x+k]$会被算作新的一种结果，而实际上没有变化的情况在前面可能被统计过，导致重复计算。所以要单独统计是否出现过完全没有变化的情况，避免重复。

注意到$a_x$在对$[x,x+k-1]$排序时不变等价于$a_x$是$[x,x+k-1]$上的最小值，$a_{x+k}$在对$[x+1,x+k]$排序时不变等价于$a_{x+k}$是$[x+1,x+k]$上的最大值，所以可以用单调队列或者ST表预处理区间最值来判断。

代码：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;
typedef long long ll;
const int MAXN = 200005;
inline int readint()
{
	int res = 0, f = 1;
	char c = 0;
	while(!isdigit(c))
	{
		c = getchar();
		if(c=='-')
			f = -1;
	}
	while(isdigit(c))
		res = res*10+c-'0', c = getchar();
	return res*f;
}
int n,k,a[MAXN];
int len[MAXN],mina[MAXN],maxa[MAXN],q[MAXN],front,rear;

int main()
{
	n = readint(), k = readint();
	for(int i = 1; i<=n; i++)
	    a[i] = readint();
	len[1] = 1;
	for(int i = 2; i<=n; i++)
		len[i] = a[i]>a[i-1]?len[i-1]+1:1;
	front = rear = 0;
	for(int i = 1; i<=n; i++)
	{
		while(front<rear&&a[q[rear-1]]<a[i])
			rear--;
		while(front<rear&&q[front]<=i-k)
			front++;
		q[rear++] = i;
		if(i>=k)
			maxa[i-k+1] = a[q[front]];
	}
	front = rear = 0;
	for(int i = 1; i<=n; i++)
	{
		while(front<rear&&a[q[rear-1]]>a[i])
			rear--;
		while(front<rear&&q[front]<=i-k)
		    front++;
		q[rear++] = i;
		if(i>=k)
			mina[i-k+1] = a[q[front]];
	}
	int ans = 1;
	bool flag = len[k]==k;
	for(int i = 1; i<n-k+1; i++)
	{
		int dt = 0;
		if(a[i]!=mina[i]||a[i+k]!=maxa[i+1])
			dt = 1;
		if(len[i+k]>=k&&flag)
			dt = 0;
		flag |= len[i+k]>=k;
		ans += dt; 
	}
	cout << ans << endl;
	return 0;
}

```


---

## 作者：feecle6418 (赞：1)

排序后相同的情况只有两种：

- $a_i$ 是 $[i,i+k]$ 中最小值，$a_{i+k}$ 是 $[i,i+k]$ 中最大值：排 $[i,i+k-1]$ 和 $[i+1,i+k]$ 的结果是相同的。
- $[i,i+k-1]$ 本来就是递增的。这样排序后与原序列相同。

第一种，需要判断 $a_i$ 是不是 $[i,i+k]$ 中最小值，注意这里不用“求”，只是判断，因此**不需要求最值的数据结构（比如堆，ST 表，单调队列等）**，只需用单调栈求出满足 $a_j$ 小于 $a_i$ 的最小 $j(j>i)$ 再把 $j$ 和 $i+k$ 比较。

第二种，可以做 $[a_i>a_{i-1}]$ 的前缀和 $s$，判断 $s_i-s_{i-k+1}=k-1$ 即可。

每次判到相同的，就把左端点在并查集里 Merge 起来。

复杂度 $O(n)$（忽略并查集）。而且超好写。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,K,a[200005],fl[200005],fa[200005],fr[200005],st[200005],sum[200005],top,ans=0;
int gf(int x){
	return fa[x]==x?x:fa[x]=gf(fa[x]);
}
void Merge(int x,int y){
	fa[gf(x)]=gf(y);
}
int main(){
	cin>>n>>K;
	for(int i=1;i<=n;i++)cin>>a[i],a[i]++,fa[i]=i;
	st[top=0]=0;
	for(int i=1;i<=n;i++){
		while(top&&a[st[top]]<a[i])top--;
		fl[i]=st[top]+1,st[++top]=i;
	}
	st[top=0]=n+1;
	for(int i=n;i;i--){
		while(top&&a[st[top]]>a[i])top--;
		fr[i]=st[top]-1,st[++top]=i;
	}
	for(int i=1;i<=n-K;i++)if(fl[i+K]<=i&&fr[i]>=i+K)Merge(i,i+1);
	for(int i=2,p=0;i<=n;i++){
		sum[i]=sum[i-1]+(a[i]>a[i-1]);
		if(i>=K&&sum[i]-sum[i-K+1]==K-1){
			if(!p)p=i-K+1;
			else Merge(i-K+1,p);
		}
	}
	for(int i=1;i<=n-K+1;i++)if(gf(i)==i)ans++;
	cout<<ans;
}

```

---

## 作者：Zhddd_ (赞：0)

首先，在不重的情况下，一共有 $n-k+1$ 种不同的排序方式。

接下来考虑去重。

如果两次排序重复，只可能是以下两种情况：

1. 两次排序对原序列都没有变动。

2. 对于右端点相邻的两次排序，设靠后的那次排序的右端点是 $i$，那么如果原序列第 $i$ 项是靠后的排序的最大值，原序列第 $i-k$ 项是靠前的序列的最小值，那么显然，这两次排序是完全等价的。

用单调队列来 $O(n)$ 求出最大值和最小值。注意特判。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int n, k, l, r, res;
int q[N], a[N], mx[N], mn[N];
bool flag;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> k;
	for (int i = 1; i <= n; i++) cin >> a[i];
	l = 1, r = 0;
	for (int i = 1; i <= n; i++) {
		while (q[r] - q[l] >= k - 1 && l < r) l++;
		while (l <= r && a[q[r]] < a[i]) r--;
		q[++r] = i;
		mx[i] = a[q[l]];
	}
	l = 1, r = 0;
	for (int i = 1; i <= n; i++) {
		while (q[r] - q[l] >= k - 1 && l < r) l++;
		while (l <= r && a[q[r]] > a[i]) r--;
		q[++r] = i;
		mn[i] = a[q[l]];
	}
	for (int i = 2, cnt = 1; i <= n; i++) {
		a[i] > a[i - 1] ? cnt++ : cnt = 1;
		if (i == k && cnt != k) res++;
		if ((i >= k + 1 && (a[i - k] > mn[i - 1] || a[i] < mx[i]) && cnt < k)) res++;
		if (cnt == k) flag = true;
	}
	cout << res + flag << endl;
	return 0;
} 
```

---

