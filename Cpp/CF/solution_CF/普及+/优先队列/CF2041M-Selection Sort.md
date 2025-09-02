# Selection Sort

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2041M/d5dc69f2c95d765850bbfc6e16bfc04c742abf70.png)Every student enrolled in the algorithms course is required to submit an assignment this week. The task is to implement an $ O(n^2) $ -time algorithm to sort $ n $ given integers in non-decreasing order. Alice has already completed her assignment, and her implementation is shown below.

```
<pre class="lstlisting">```
int alice_sort(int *s, int n){<br></br>  for(int i = 0; i < n; ++i){<br></br>    for(int j = i + 1; j < n; ++j){<br></br>      if(s[i] > s[j]){<br></br>        int swap = s[i];<br></br>        s[i] = s[j];<br></br>        s[j] = swap;<br></br>      }<br></br>    }<br></br>  }<br></br>  return 0;<br></br>}<br></br>
```
```

While you have access to Alice's code, you prefer not to simply copy it. Instead, you want to use Alice's sorting function as a building block for your own solution. There are two ways as listed below you can utilize her function, but each of them can be applied at most once. The order in which these two operations are invoked can be arbitrary.

- Prefix sort: choose a length $ i \in \{1, 2, \ldots, n\} $ and call $ \texttt{alicesort(}s, i\texttt{)} $ . This sorts the first $ i $ elements in the array $ s $ .
- Suffix sort: choose a length $ i \in \{1, 2, \ldots, n\} $ and call $ \texttt{alicesort(}s+n-i, i\texttt{)} $ . This sorts the last $ i $ elements in the array $ s $ .

Due to the time complexity of the sorting algorithm, the cost of performing either a prefix or suffix sort is $ i^2 $ , where $ i $ is the length of the chosen subarray. Your goal is to determine the minimum cost to sort the input array $ s $ of $ n $ integers in non-decreasing order using Alice's function, following the rules mentioned above.

For example, Let $ s=[3,2,5,5,4,1] $ . We can first perform a suffix sort of length $ 4 $ , and the array becomes $ [3,2,1,4,5,5] $ . Then, we perform a prefix sort of length $ 3 $ , and the array becomes $ [1,2,3,4,5,5] $ , which is a sorted array. The cost is $ 4^2+3^2=25 $ . Here is another example, let $ s=[4,3,2,1] $ . We can complete the sorting by performing only a prefix sort of length $ 4 $ , and the cost is $ 4^2=16 $ .

## 样例 #1

### 输入

```
6
3 2 5 5 4 1```

### 输出

```
25```

## 样例 #2

### 输入

```
4
4 3 2 1```

### 输出

```
16```

# 题解

## 作者：lfxxx (赞：0)

假设排序区间是 $[1,l],[r,n]$，可以按照其是否相交分类讨论。

不妨假设先进行前缀的排序，若相交，那么注意到第一次排序的作用是在第一次排序后假若使得序列前 $k$ 项与排好的序列相同，那么后面只用对 $[k+1,n]$ 排序即可，所以关键是如何计算 $k$。

考虑从前往后扫时拿两个小根堆维护前缀中的数与排好序后的序列前缀中的数对消即可。

不相交和先进行后缀的排序的情况是类似的，注意只排序一次的情况要特判下。

时间复杂度 $O(n \log n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e6+114;
int n,a[maxn],b[maxn];
int pre[maxn],suf[maxn];
long long ans;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i],b[i]=a[i];
    sort(b+1,b+n+1);
    priority_queue<int> q1,q2;
    ans=1ll*n*n;
    for(int i=1;i<=n;i++){
        q1.push(-a[i]);
        q2.push(-b[i]);
        while(q1.size()>0&&q1.top()==q2.top()) q1.pop(),q2.pop();
        if(q1.size()==0) pre[i]=1;
        ans=min(ans,1ll*i*i+1ll*(n-i+(int)q1.size())*(n-i+(int)q1.size()));
    }
    while(q1.size()>0) q1.pop();
    while(q2.size()>0) q2.pop();
    for(int i=n;i>=1;i--){
        q1.push(a[i]);
        q2.push(b[i]);
        while(q1.size()>0&&q1.top()==q2.top()) q1.pop(),q2.pop();
        if(q1.size()==0) suf[i]=1;
        ans=min(ans,1ll*(n-i+1)*(n-i+1)+1ll*(i-1+(int)q1.size())*(i-1+(int)q1.size()));
    }
    int nxt=n+1;
    for(int i=n;i>=1;i--){
        if(pre[i]==1) ans=min(ans,1ll*i*i+1ll*(n-nxt+1)*(n-nxt+1));
        if(a[i]!=b[i]) nxt=0;
        if(suf[i]==1) nxt=max(nxt,i);
    }
    for(int i=1;i<=n;i++){
        if(a[i]!=b[i]) break;
        ans=min(ans,1ll*(n-i)*(n-i));
    }
    for(int i=n;i>=1;i--){
        if(a[i]!=b[i]) break;
        ans=min(ans,1ll*(i-1)*(i-1));
    }
    cout<<ans<<'\n';
    return 0;
}
```

---

## 作者：ccjjxx (赞：0)

贪心题。

题目给这定两个函数：

- 前缀排序函数：选择 $\forall i\in [1,n]$，把区间 $[1,i]$ 排序，花费代价是 $i^2$；

- 后缀排序函数：选择 $\forall i \in [1,n]$，把区间 $[n-i+1,n]$ 排序，花费代价是 $i^2$。

给出一个序列，问你把它排成升序序列的最小花费。

---

观察可以发现，一定是一次前缀一次后缀，并且排序的次数一定不大于 $2$。考虑先前已经经过了一次前缀排序，再进行一次前缀排序一定会涉及前面已经有序的区间，会使得答案不优。因为我们答案更优一定要让越少的地方被多次排序。

那么策略就很明显了，首先，如果选定一个位置 $i$ 做前缀排序，一定可以找到另一个位置 $j$ 做后缀排序，使得序列有序。易得极端情况下 $j$ 取 $1$ 一定可以满足。先后缀排序再前缀排序同理。

那么，我们如何找到这个位置呢？

以先前缀再后缀为例，假设排完前缀，前 $k$ 小的数已经到前 $k$ 个位置，那么第二次排序一定是从 $k+1$ 开始排的。也就是说，若当前排好的序列中有 $k$ 个前 $k$ 小（或大）的数，那么第二次排序的位置就是 $k+1$。

预处理很简单，用优先队列即可。

有一个小细节，就是形如 `3 2 1 4 5 6 8 9 7` 的序列，先给 $3$ 前缀排序，你会发现第二次排序的位置是 $7$，也就是有可能有更多的有序位置在后面（或前面）出现，特判一下就好。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n;
const int N=1e6+6;
int a[N];
priority_queue<int>q,tmp;
priority_queue<int,vector<int>,greater<int> >q1,tmp1;
int pos[N];
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	if(is_sorted(a+1,a+1+n)) return cout<<0,0;
	for(int i=1;i<=n;i++) q.push(a[i]);
	for(int i=n;i>=1;i--)
	{
		if(a[i]==q.top())q.pop();
		else tmp.push(a[i]);
		while(!tmp.empty()&&!q.empty()&&tmp.top()==q.top()) tmp.pop(),q.pop();
		if(q.size()==i-1)
		{
			int j=i-1;
			for(j=i-1;j>=1;j--) if(a[j]==q.top()) q.pop(); else break;
			j++;
			for(int k=i;k>=j;k--) pos[k]=q.size();
			i=j;
		}
		pos[i]=q.size();
	}
//	for(int i=1;i<=n;i++) cout<<pos[i]<<" ";
//	cout<<"\n";
	int ans=1e18;
	for(int i=1;i<=n;i++) ans=min(ans,(n-i+1)*(n-i+1)+pos[i]*pos[i]);
	for(int i=1;i<=n;i++)q1.push(a[i]);
	for(int i=1;i<=n;i++)
	{
		if(a[i]==q1.top())q1.pop();
		else tmp1.push(a[i]);
		while(!tmp1.empty()&&!q1.empty()&&tmp1.top()==q1.top()) tmp1.pop(),q1.pop();
		if(q1.size()==n-i)
		{
			int j=i+1;
			for(j=i+1;j<=n+1;j++) if(a[j]==q1.top()) q1.pop(); else break;
			j--;
//			cout<<i<<" "<<j<<"\n";
			for(int k=i;k<=j;k++) pos[k]=q1.size();
			i=j;
		}
		pos[i]=q1.size();
	}
	for(int i=1;i<=n;i++) ans=min(ans,i*i+pos[i]*pos[i]);
	cout<<ans;
}
```

---

## 作者：沉石鱼惊旋 (赞：0)

## M. Selection Sort

给定长度为 $n$ 的序列 $a$，对长度为 $m$ 的序列使用一次 Alice-Sort 的代价为 $m^2$。

```cpp
int alice_sort(int *s, int n){
  for(int i = 0; i < n; ++i){
    for(int j = i + 1; j < n; ++j){
      if(s[i] > s[j]){
        int swap = s[i];
        s[i] = s[j];
        s[j] = swap;
      }
    }
  }
  return 0;
}
```

有两种操作：

可以使用 Alice-Sort 对一个前缀排序。

可以使用 Alice-Sort 对一个后缀排序。

每种操作**限用一次**。

问把序列排好序的最小代价。

$1\leq n\leq 10^6$，$0\leq a_i\lt 2^{31}-1$。

---

一共只排两次序，枚举先排前缀还是先排后缀。

不妨认为先排前缀。枚举前缀需要排序到哪里，然后算出后缀排到哪里。

重复值有点难搞（其实也不难搞，先处理了后面操作更顺利），我们把这个数组先改成 $[1,n]$ 的排列，相同值越前面的越小。

枚举前缀排序到了哪里，维护值的连续段。$lst$ 表示值在 $[1,lst]$ 的数都可以归为了。那么 $[lst+1,n]$ 的就是需要重排的。

$lst$ 可以直接维护。再维护一个小根堆，里面是已经在区间内但是连不起来的元素，$lst$ 每次根据堆里的元素尝试往后扩展。

但是这有个问题，我们无法判断那些，后缀无需排序的，和我们已经扩展了前缀的，但是没有必要把一些元素加进去排序的。

先处理第一个，我们找到原数组最后一个不合法（$a_i\neq i$）的位置记作 $r$，那么 $i=r$ 的时候不要加上后缀排序的贡献。

第二个，我们维护**上一个**需要排序的位置，就是无法直接加入的，即堆内有元素，或者 $a_i\neq lst+1$。记这个位置为 $pos$，那么前缀排序到 $i$ 的代价只为 $pos^2$。

以上是先选前缀排序的做法，先选后缀排序本质一样。代码复制一遍改一改就行了。

<https://codeforces.com/contest/2041/submission/294548198>

---

