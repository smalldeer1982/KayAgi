# [USACO22JAN] Cow Frisbee S

## 题目描述

Farmer John 的 $N\ (N\le 3\times 10^5)$ 头奶牛的高度为 $1, 2, \ldots, N$。一天，奶牛以某个顺序排成一行玩飞盘；令 $h_1 \ldots h_N$ 表示此顺序下奶牛们的高度（因此 $h$ 是 $1 \ldots N$ 的一个排列）。

队伍中位于位置 $i$ 和 $j$ 的两头奶牛可以成功地来回扔飞盘当且仅当她们之间的每头奶牛的高度都低于 $\min(h_i, h_j)$。

请计算所有可以成功地来回扔飞盘的奶牛所在的位置对 $i\le j$ 之间的距离总和。位置 $i$ 和 $j$ 之间的距离为 $j-i+1$。

## 说明/提示

【样例解释】

这个例子中可以成功的位置对如下：

```
(1, 2), (1, 5), (2, 3), (2, 4), (2, 5), (3, 4), (4, 5), (5, 6), (6, 7)
```

【数据范围】

- 测试点 1-3 满足 $N\le 5000$。

- 测试点 4-11 没有额外限制。

## 样例 #1

### 输入

```
7
4 3 1 2 5 6 7```

### 输出

```
24```

# 题解

## 作者：V1mnkE (赞：21)

## 思路
维护一个单调栈，每进入一个数 $a_i$，就向前扫描直到遇见一个 $s_{top}>a_i$，由于有 $s_{top}$ 挡着，所以之后的我们全部都看不见，此时最终答案加上 $(i-s_{top}+1)$。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,ans=0;
long long a[300005];
stack<long long>s;
int main() {
    cin>>n;
    for (int i=1;i<=n;i++)cin>>a[i];
    for (int i=1;i<=n;i++){
        while (!s.empty()&&a[s.top()]<a[i]){
            ans+=i-s.top()+1;
            s.pop();
        }
        if (!s.empty())ans+=i-s.top()+1;
        s.push(i);
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：YCSluogu (赞：4)

这是一道单调栈的板子题。

我们维护一个单调栈，其中存储着数组 $a$ 的下标，这样方便我们一会计算距离。每当压入一个新的元素 $i$ 时，若栈顶元素 $top$ 对应的 $a_{top}$ 比 $a_{i}$，即可弹出栈顶元素直到栈为空或者 $a_{top} > a_{i}$。

为什么这样做？因为面对一个新的元素 $a_{i}$，其栈内所有比 $a_{i}$ 小的下标对应值都无法对答案产生贡献，也就是可以理解 $a_i$ 挡住了它们丢飞盘的去路。

code:
``` cpp
#include <bits/stdc++.h>

using namespace std;

const long long MAXN = 1e6;

long long n, ans = 0;
long long a[MAXN];
stack<long long> s;

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i <= n; i++) {
    while (!s.empty() && a[s.top()] < a[i]) {
      ans += i - s.top() + 1;
      s.pop();
    }
    if (!s.empty()) {
      ans += i - s.top() + 1;
    }
    s.push(i);
  }
  cout << ans << endl;
  return 0;
}
```

审题难度相对高一点点，但是编写难度基本为 0


---

## 作者：zhaoyp (赞：4)

## Solution

正难则反，考虑不成立的情况。

不难发现，奶牛 $l$ 和奶牛 $r$ $(l < r)$ 可不可以互扔只取决于它们之间最高的奶牛的高度，于是我们只须考虑奶牛 $l$ 到奶牛 $r$ 之间最高的奶牛。

如果奶牛 $l$ 和奶牛 $r$ $(l < r)$ 不可以互扔，由于奶牛的高度互不相同，那么奶牛 $l$ 和奶牛 $r$ 就对应了唯一一头它们之间最高的奶牛，同样地，每头奶牛也对应着若干对无法互扔的奶牛（可能为零）。

分别枚举每头奶牛作为中间那头最高的奶牛。对于每头奶牛 $x$，$l$ 的范围位于 $x$ 左边最近的比奶牛 $x$ 高的奶牛到 $x$ 间， $r$ 的范围位于 $x$ 到 $x$ 右边最近的比奶牛 $x$ 高的奶牛间。这样我们就可以计算出所有无法互扔的奶牛对的距离和，在用所有奶牛对的距离和减去它就是最后的答案了。

1. 计算所有奶牛对的距离和

较暴力的做法：枚举每头奶牛作为奶牛对左边那头奶牛，再用等差数列进行计算，距离和为 $\sum\limits_{i=1}^{n}(n - i + 3) * (n - i) / 2$。

2. 计算所有无法互扔的奶牛对的距离和

对于每头奶牛 $x$，记 $x$ 左边最近的比奶牛 $x$ 高的奶牛为 $l_x$，右边的为 $r_x$，距离和为 $ans$。

- 先处理不含端点的情况：

左右边分别有 $(x - l_x - 1)$ 和 $(r_x - x - 1)$ 头奶牛可选，总共有 $(x - l_x - 1) \times (r_x - x - 1)$ 对，其中左边每头奶牛存在于 $(r_x - x - 1)$ 对中，右边每头奶牛存在于 $(x - l_x - 1)$ 对中，将每对的距离加和。

$$\begin{aligned} ans  & = (x - l_x - 1) \times (r_x - x - 1) + (x - l_x - 1) \times \sum\limits_{i = x + 1}^{r_x - 1}i - (r_x - x - 1) \times \sum\limits_{i = l_x + 1}^{x - 1}i 
\\  & = (x - l_x - 1) \times (r_x - x - 1) + (x - l_x - 1) \times (x + r_x) \times (r_x - x - 1) / 2 - (r_x - x - 1) \times (l_x + x) \times (x - l_x - 1) / 2 
\\  & = (x - l_x - 1) \times (r_x - x - 1) \times (r_x - l_x + 2) / 2
\end{aligned}$$

- 再处理含端点的情况（奶牛 $x$ 左边或右边存在比它高的奶牛）：

将上式奶牛 $x$ 左边或右边用该端点替换即可（具体见代码）。

每头奶牛左右两端最近的比它高的奶牛可以通过两次单调栈预处理。总时间复杂度 $O(n)$。
## code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define s_top()		s[tot]
#define s_size()	tot
#define s_push(x)	s[++tot] = x
#define s_pop()		tot--
long long n,ans,tot,s[300005],a[300005],l[300005],r[300005];
void input()
{
	scanf("%lld",&n);
	for(int i = 1;i <= n;i++)
		scanf("%lld",&a[i]);
}
void prefix()
{
	for(int i = 1;i <= n;i++)
	{
		while(s_size()&&a[s_top()] < a[i])
			s_pop();
		l[i] = s_size() ? s_top() : 0;
		s_push(i);
	}
	while(s_size())
		s_pop();
	for(int i = n;i;i--)
	{
		while(s_size()&&a[s_top()] < a[i])
			s_pop();
		r[i] = s_size() ? s_top() : n + 1;
		s_push(i);
	}
}
void work()
{
	for(int i = 1;i < n;i++)
		ans += (n - i + 1 + 2) * (n - i) / 2;
	for(int i = 2;i < n;i++)
	{
		ans -= (r[i] - l[i] + 2) * (i - l[i] - 1) * (r[i] - i - 1) / 2;
		if(l[i])
			ans -= (i + r[i] - 2 * l[i] + 2) * (r[i] - i - 1) / 2;
		if(r[i] != n + 1)
			ans -= (2 * r[i] - i - l[i] + 2) * (i - l[i] - 1) / 2;
	}
}
void output()
{
	printf("%lld",ans);
}
int main()
{
	input();
	prefix();
	work();
	output();
	return 0 ;
}
```

---

## 作者：luckydrawbox (赞：3)

[$\text{Link}$](https://www.luogu.com.cn/problem/P8094)

考场上唯一会的题（wtcl。

## 题意

>一个 $1\sim n$ 的排列 $h_1,h_2,…,h_n$，求 $\sum^n_{i=1}\sum^n_{j=i+1}[\max^{j-1}_ {k=i+1}h_k<\min(h_i,h_j)]$。

## 分析

设 $h_i=\min(h_i,h_j)$，则满足要求的 $h_j$ 最多只有两个：$h_i$ 左边第一个满足 $h_j>h_i$ 的数和 $h_i$ 右边第一个满足 $h_j>h_i$ 的数。

以下图的 $h_3=5$ 为例：

![](https://cdn.luogu.com.cn/upload/image_hosting/ebi0q98u.png)

对于 $h_3$ 左边的数，$h_1=8$ 是第一个比它大的，因此中间的数都比他们小，必然满足 $\max^{j-1}_ {k=i+1}h_k<h_i<h_j$。

对于 $h_3$ 右边的数，$h_6=6$ 是第一个比它大的，因此中间的数都比他们小，必然满足 $\max^{j-1}_ {k=i+1}h_k<h_i<h_j$。但是 $h_6$ 后面有 $h_8>h_6>h_3$，那么 $h_8$ 能不能算入答案呢？显然不能，因为 $\max^{j-1}_ {k=i+1}h_k=h_6>h_3$。

因为 $h_i\neq h_j$，所以每个数对 $(i,j)$ 只会从较小的 $h_i$ 出发计算的方法计算一次，因此答案不重不漏。

那么如何计算左/右边第一个比 $h_i$ 大的数呢，开个小根堆，统计即可，时间复杂度 $O(n\log n)$。

但好像用栈可以 $O(n)$？管他呢，能过就行。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
long long read(){
	long long x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
void write(long long x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
const int N=3e5+10;
int n,h[N],d[N];
priority_queue<int>q;
ll ans;
int main(){
	n=read();
	for(int i=1;i<=n;i++){
		h[i]=read();
		d[h[i]]=i;
		while(q.size()&&-q.top()<h[i]){
			ans+=abs(i-d[-q.top()])+1;
			q.pop();
		}
		q.push(-h[i]);
	}
	while(q.size())
		q.pop();
	for(int i=n;i;i--){
		while(q.size()&&-q.top()<h[i]){
			ans+=abs(i-d[-q.top()])+1;
			q.pop();
		}
		q.push(-h[i]);
	}
	write(ans);
	return 0;
}
```


---

## 作者：SengRiy (赞：2)

[**题目传送门**](https://www.luogu.com.cn/problem/P80940)

## 题意

给定一组长度为 $n$ 的高度，其中任意两头奶牛高度 $h_i,h_j$ ，中间若干只奶牛高度没有比这两头奶牛高度高的，记录这两头奶牛 $i, j$ 的贡献为 $abs(i - j) + 1$，否则不贡献距离。

## 解题

### 暴力

直接枚举两头奶牛高度，枚举其中间的奶牛是否有奶牛高度大于这两头奶牛高度的最小值，如否，则记录贡献；如是，则不计其贡献。

这里就不放代码了，~~应该没OIer写不出来吧~~

### 正解

中间无一头奶牛高于外面两头奶牛高度最小值……单调？~~我经过了长时间的思想斗争后发现~~这不就是单调栈板子嘛。

我们可以维护一个单调递减栈储存奶牛编号，如样例一（这里为方便存储奶牛编号变为存储奶牛高度）

$4$ 进栈，$3$ 进栈， $1$ 进栈，

这时 $2$ 正要进栈，却大于栈顶元素 $1$，于是 $1$ 出栈， $2$ 进栈。不难发现，这时 $3$ 与 $2$ 中间的 $1$ 不大于其最小值，对总距离有 $3$ 的贡献。

这说明每当一个元素进栈时，如大于栈顶元素，则栈顶后一个元素一定能与这个元素贡献距离（如不明白，可自行手动推导）

## 代码

注：`很抱歉，这次代码打了折扣，只有核心代码`

AC 代码核心 for 循坏

```cpp
for (int i = 2; i <= n; ++i) { // 枚举每头奶牛
  while (h[s[len]] < h[i] && len > 0) { //当奶牛高度大于栈顶奶牛高度，栈顶元素出栈，并记录当前元素与栈下一个栈顶元素的贡献
    --len;
    if (len > 0) {
      ans += i - s[len] + 1;
    }
  }
  s[++len] = i; // 当前元素进栈
}
```

---

## 作者：蒻蒟IOOI蒟蒻 (赞：2)

# **一、题意分析**
题目就是要求有多少奶牛对之间奶牛高度都低于自身。

我们发现因为之间的奶牛高度要低于自身，如果有奶牛挡着，就配不成对。

所以每头奶牛和它左边和右边的奶牛分别最多能组成1个奶牛对。

# **二、思路**
我们发现实际上我们要求的是每头奶牛左边和右边第一个大于等于它的奶牛位置。

我用的是st表+二分查找的方法，因为实际上我们可以把问题转化成求每头奶牛右边区间最大值大于等于该奶牛的高度的第一个位置。

因为最大值满足单调不降，所以我们可以用二分查找来实现  $O(n\log n)$  的时间复杂度。

# **三、具体实现**
对于每头奶牛左边第一个大于等于它的位置，我们可以用 ``reverse``  把数组逆转，然后再做一遍和前面同样的计算就可以了。

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
#define int long long
const int N = 3e5 + 5;
int n, a[N], ans, st[N][30], lg[N];
int get(int l, int r) {
    int s = lg[r - l + 1];
    return max(st[l][s], st[r - (1 << s) + 1][s]);
} 
int bin(int i, int l, int r, int x) {
    if (l + 1 == r) return r;
    int mid = (l + r) / 2, g = get(i, mid);
    if (g > x) return bin(i, l, mid, x);
    else return bin(i, mid, r, x);
}
signed main() {
    scanf("%lld\n", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld\n", &a[i]);
    }
    lg[2] = 1;
    for (int i = 3; i <= n; i++) {
        lg[i] = lg[i >> 1] + 1;
    }
    for (int i = 1; i <= n; i++) {
        st[i][0] = a[i];
    }
    for (int j = 1; (1 << j) <= n; j++) {
        for (int i = 1; i + (1 << j) - 1 <= n; i++) {
            st[i][j] = max(st[i][j - 1], st[i + (1 << j - 1)][j - 1]);
        }
    }
    for (int i = 1; i < n; i++) {
        if (get(i + 1, n) < a[i]) continue; 
        int lb = bin(i, i, n + 1, a[i]);
        ans += lb - i + 1;
    }
    reverse(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++) {
        st[i][0] = a[i];
    }
    for (int j = 1; (1 << j) <= n; j++) {
        for (int i = 1; i + (1 << j) - 1 <= n; i++) {
            st[i][j] = max(st[i][j - 1], st[i + (1 << j - 1)][j - 1]);
        }
    }
    for (int i = 1; i < n; i++) {
        if (get(i + 1, n) < a[i]) continue; 
        int lb = bin(i, i, n + 1, a[i]);
        ans += lb - i + 1;
    }
    printf("%lld\n", ans);
    return 0;
}

```


---

## 作者：I_am_Accepted (赞：1)

### Preface

为啥有人要用 $O(n\log n)$ 树状数组啊（我不理解）。

### Analysis

单调栈维护值递减的位置集合。加入新值时向前 pop 的同时更新答案（飞盘右边的奶牛为当前奶牛的方案数）。

时间 $O(n)$。

由此得到推论：本题能飞飞盘的奶牛对数量不会超过 $n$。

### Code

```cpp
//Said no more counting dollars. We'll be counting stars.
#include<bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define For(i,j,k) for(int i=j;i<=k;i++)

long long n,a[300010],ans=0;
stack<long long> s;
signed main(){IOS;
	cin>>n;
	For(i,1,n) cin>>a[i];
	For(i,1,n){
		while(!s.empty() && a[s.top()]<a[i]) ans+=i-s.top()+1,s.pop();
		if(!s.empty()) ans+=i-s.top()+1;
		s.push(i);
	}
	cout<<ans<<endl;
return 0;}
```

---

## 作者：__lyh__ (赞：1)

## 题意

在一排山峰中，对于每两座山，如果两座山之间没有山比这两座高，则答案累加这两座山的距离。

## 解决

不难发现有以下的性质：

- 对于每一座山，至多只有另外两座山与其配对（向左一座，向右一座）。

- 对于一座较矮的山峰，向左看，第一座比它高的山峰可以与其配对，向右看也是第一座比它高的山峰可以与其配对。

那么，只要对于每一座山，求出其左边和右边第一座比它高的山峰的序号，计算距离，累加答案即可。

当然，也可以只求右边后，把数组反过来再求一边向右。（也就是我代码中的思路）。

现在关键在于，对于每一座山，如何求出向左和向右首座比它高的山峰的序号。

对于这个问题，用单调栈解决即可。

## 代码

```cpp
#includ#include<bits/stdc++.h>
#define int long long
#define N 300005
using namespace std;
inline int read()
{
	int x = 0, f = 1; char ch = getchar();
	while(!isdigit(ch)){if(ch == '-') f = -1; ch = getchar();}
	while(isdigit(ch)){x = x * 10 + ch - 48; ch = getchar();}
	return f * x;
}

int nxt[N], ans, n, a[N], b[N];
int head = 1, tail = 0;
int q[N];

signed main()
{
	n = read();
	for (int i = 1; i <= n; i++)
	{
		a[i] = read();
	}
	q[++tail] = 1;
	for (int i = 2; i <= n; i++)
	{
		while(head<=tail&&a[q[tail]]<a[i])
		{
			nxt[q[tail]] = i;
			tail--;
		}
		q[++tail] = i;
	}
	for (int i = 1; i <= n; i++)
	{
		if(nxt[i])
		{
			ans += nxt[i] - i + 1;
		}
	}
	head = 1, tail = 0;
	memset(nxt, 0, sizeof(nxt));
	for (int i = 1; i <= n; i++)
	{
		b[i] = a[n-i+1];
	}
	q[++tail] = 1;
	for (int i = 2; i <= n; i++)
	{
		while(head<=tail&&b[q[tail]]<b[i])
		{
			nxt[q[tail]] = i;
			tail--;
		}
		q[++tail] = i;
	}
	for (int i = 1; i <= n; i++)
	{
		if(nxt[i])
		{
			ans += nxt[i] - i +1;
		}
	}
	printf("%lld", ans);
}
```

---

## 作者：lsj2009 (赞：1)

## 题目大意
给定一个正整数序列 $a$，问有多少个 $(i,j)$，满足 $\max\limits_{i<k<j}(a_k)<\min(a_i,a_j)$。
## 思路
个人认为这是一道经典的****单调栈****练习题（~~然而我一眼竟然没有看出来~~。

为什么是单调栈呢？

暴力的 $O(n^2)$ 思路是对于每一个 $i$，循环对大于 $i$ 的 $j$，看看 $\max\limits_{i<k<j}(a_k)$ 是否小于 $\min(a_i,a_j)$。其中对于 $\max\limits_{i<k<j}(a_k)$ 可以一路比较维护。

## code
```cpp
int ans=0;
for(int i=1;i<=n;i++) {
	int max_val=0;
	for(int j=i+1;j<=n;j++) {
		if(max_val<min(a[i],a[j]))
			ans+=j-i+1;
		max_val=max(max_val,a[j]);
   }
}
```

接下来我们考虑****只循环 $j$，维护 $i$ 的变化****。

我们构造一个****单调递减****的单调栈，每进入一个数 $a_i$，就向前扫描直到遇见一个 $s_{top}>a_i$，由于有 $s_{top}$ 挡着，所以之后的我们全部都看不见。

由于有 $a_i$ 挡着，所以除了 $s_{top}$ 以及之前高度 $>a_i$ 的，剩下的 $a_{i+1}$ 均看不见。

## code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+5;
int a[N],n;
int Solve() {
	stack<int> s;
	int ans=0;
	for(int i=1;i<=n;i++) {
		while(!s.empty()&&a[s.top()]<a[i]) ans+=i-s.top()+1,s.pop(); //能看见，弹出并累加距离
		if(!s.empty()) ans+=i-s.top()+1; //能看见，累加距离
		s.push(i); //入栈
	}
	return ans;
}
signed main() {
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	cout<<Solve();
	return 0;
}
```

---

## 作者：mcDinic (赞：1)

银组最简单的题，抢篇题解区沙发。

这题是道单调栈模板题，判断出队时边累加答案，并累加出队元素对当前元素答案的贡献，维护递减单调栈，就解决了，详见代码。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[500005],ans,q[500005][2],t;
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	a[n+1]=0x3f3f3f3f;
	for(int i=1;i<=n+1;i++){
		int sk2=0;
		while(t&&a[q[t][0]]<a[i]){
			sk2+=i-q[t][0]+1;
			ans+=q[t][1];
			t--;
		}
		if(t)sk2+=i-q[t][0]+1;
		q[++t][0]=i,q[t][1]=sk2;
	}
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：junxis (赞：0)

## 1.分析
我们不妨设现在分析的奶牛为第 $i$ 头，想象它向左扔出了一个飞盘，显然它的飞行高度为奶牛的高度。飞盘不断飞行，直到有一头奶牛的身高大于它的飞行高度此时飞盘停下。那么这头奶牛向左扔飞盘对答案的贡献就是飞盘经过的所有奶牛到他的距离之和。
## 2.实现
我们考虑用 set 维护这个过程，设有一个 set 叫 $S$ 。从左向右循环，对于每头奶牛，只要 $S$ 的第一个元素小于它，就从 $S$ 中取出，并对答案加上贡献，一直取到第一个元素大于它或 $S$ 空了。因为被取出的奶牛比当前奶牛矮，所以接下来遍历到的所有奶牛都不可能朝它成功地扔出飞盘，直接把取出的奶牛从 $S$ 中删除即可。

如此一来，便算出了向左扔飞盘的所有距离之和，只要把原数组反转，然后再重复刚才的过程，便求出了完整答案，输出即可。

代码环节！

```cpp
#include<bits/stdc++.h>
using namespace std;
const int INF=0x7ffffff;
int n,a[300005],pos[300005];
long long ans;
set<int>s;
int _abs(int x){return x>0 ? x : -x ;}
void _swap(int &x,int &y){int t=x;x=y;y=t;return ;}
int main()
{
    cin>>n;
    s.clear();s.insert(INF);//往set里塞个INF防止奇奇怪怪的一些错误 
    for(int i=1;i<=n;i++)
    {
    	scanf("%d",&a[i]);
    	pos[a[i]]=i;//计算贡献时还要知道这头奶牛的位置 
    	while(s.size()>1&&*s.begin()<a[i])//由于塞了INF，所以判断set不空是s.size()>1 
    	{
    		ans+=_abs(pos[*s.begin()]-i)+1;
    		s.erase(s.begin());
		}//参考分析理解 
		s.insert(a[i]);//将这头奶牛也扔进set，因为对于下一头奶牛，这头奶牛也是有可能可以接受飞盘的 
	}
	for(int i=1;i<=n/2;i++)_swap(a[i],a[n-i+1]);
	for(int i=1;i<=n;i++)pos[a[i]]=i;
	//反转数组并重新处理奶牛位置 
	s.clear();s.insert(INF);
	for(int i=1;i<=n;i++)
	{
		while(s.size()>1&&*s.begin()<a[i])
		{
			ans+=_abs(pos[*s.begin()]-i)+1;
			s.erase(s.begin());
		}
		s.insert(a[i]);
	}//同样的求答案过程，不再解释 
	cout<<ans;//输出答案即可 
    return 0;
}
```
蒟蒻的第一篇题解，求过 QaQ。

---

## 作者：wwz1428572008 (赞：0)

## 思路
我先在读入后，处理好一个数组 $nxt$（可以用平衡树，链表，单调栈，ST 表等），代表每个元素右边最近的大于它的元素的下标。（如果这个元素右边的元素都比它小，则这个值不存在。）

接下来，枚举每一个可以作为可行位置对的第一个元素 $i$：

首先，因为相邻位置一定可行，所以先算上当前的下一个位置；
还可以发现，如果到一个位置 $p$ 可行，那么下一个可行位置就是 $nxt[p]$（如果它存在）。因为假设下一个可行位置是在 $q$（$p<q<nxt[p]$），则 $h[q]<h[p]$，不满足可行位置对的定义。同理，可得出最后一个可行的位置就是 $nxt[i]$。所以，可以遍历每一个可行的位置。

时间复杂度：类似的，可以证明最多只会有 $2N$ 对可行。于是此方法的时间复杂度是 $O(N)$ 的。

### 代码
```cpp
#include<iostream>
#include<cmath>
using namespace std;
int h[300002];
int nxt[300002],st[300002][20];
int getmax(int x,int y)
{
	int lg=log2(y-x+1);
	return max(st[x][lg],st[y-(1<<lg)+1][lg]);
}
long long ans=0;
int main()
{
	ios::sync_with_stdio(0);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>h[i];
	for(int i=1;i<=n;i++)
		st[i][0]=h[i];
	for(int j=1;(1<<j)<=n;j++)
	{
		for(int i=1;i<=n;i++)
		{
			if(i+(1<<(j-1))<=n)
				st[i][j]=max(st[i][j-1],st[i+(1<<(j-1))][j-1]);
			else
				st[i][j]=st[i][j-1];
		}
	}
	for(int i=1;i<=n;i++)
	{
		int l=i+1,r=n;
		while(l<r)
		{
			int m=(l+r)/2;
			if(getmax(i,m)==h[i])
				l=m+1;
			else
				r=m;
		}
		nxt[i]=l;
		if(l>n||getmax(i,l)==h[i])
			nxt[i]=n+1;
	}
	for(int i=1;i<n;i++)
	{
		int pos=i+1;
		while(pos<=n && pos<=nxt[i])
			ans+=(pos-i+1),pos=nxt[pos];
	}
	cout<<ans;
	return 0;
}

```

---

