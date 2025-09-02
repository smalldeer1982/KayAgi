# Alarm Clock

## 题目描述

每天晚上 Vitalya 会设置 $n$ 个闹钟以便明早醒来。每个闹钟都会正好响一分钟，并正好在那一分钟的开始响起，结束停止。给定 $a_i$ 来表示第 $i$ 个闹钟响起的时间。如果在连续的 $m$ 分钟内有至少 $k$ 个闹钟响起，Vitalya 就会醒来。注意 Vitalya 只会考虑在那一段时间中开始响起的闹钟，即不考虑在之前已经响起而未停止响的闹钟。 

Vitalya 十分疲劳，他想睡整整一天而不起床。您的任务是计算出需要关掉的闹钟总数的最小值。开始时所有闹钟都是打开状态。

## 样例 #1

### 输入

```
3 3 2
3 5 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
5 10 3
12 8 18 25 1
```

### 输出

```
0
```

## 样例 #3

### 输入

```
7 7 2
7 3 4 1 6 5 2
```

### 输出

```
6
```

## 样例 #4

### 输入

```
2 2 2
1 3
```

### 输出

```
0
```

# 题解

## 作者：憨豆Beng (赞：4)

有些类似线段覆盖的贪心。蛮巧妙的。

题意大概是这样的， 
有n个闹钟，第i个会在第ai时刻开始叫m分钟，如果在某一段区间[L,L+m]有超过k个闹钟响小明就会被吵醒，求最少关掉多少闹钟会使得小明不被吵醒，并且在区间外开始响的闹钟不计入区间中。 
1 ≤ k ≤ n ≤ 2⋅105, 1 ≤ ai,m ≤ 106 
其实我第一反应是有些惊讶，毕竟ai竟然不是小于109。想到了什么？没错，值域思想。

先来理性（玄学）分析一波。一个直观的想法是，我们按照重叠最多的顺序排序，但是这样是有问题的，毕竟如果这么一排，就会导致左右两边分开，反而会使情况更糟。 
但是如果我们从左往右扫就不一样了。只要碰到会吵醒的情况，我们就弹出，这样能够保证区间是连续的。并且，由于区间一定会出现问题，所以我们不能就此放置不管！那关哪个呢？我们选择最右面的，因为这样会让剩余的能关的更少。 
而实现也以此分成两大派别。

（伪）滑动窗口派

简洁而明了的实现，类似滑动窗口滚一遍。

```#include <iostream>
  
#include <cstdio>
  
#include <algorithm>
  
#include <deque>
 
using namespace std；

int n, m, k, a[200003], cnt;

int main() {

    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin>>n>>m>>k;
    for(int i = 1; i <= n; ++i) cin>>a[i];
    sort(a + 1, a + n + 1);
    deque<int> dq;1. 
    for(int i = 1; i <= n; ++i) {
        while(dq.size() && dq.front() <= a[i] - m) dq.pop_front();
        dq.push_back(a[i]);
        while(dq.size() >= k) ++cnt, dq.pop_back(); 
    }
    cout<<cnt<<endl;
    return 0;
}

由于双端队列末尾恰好是最右面的，所以可以直接弹走。



BIT派

之前就提到过值域思想，那么我们可以将值域维护成一个差分数组，然后利用树状数组实现前缀和的查询和修改。

#include <iostream>
  
#include <cstdio>
  
#define N 1000003

using namespace std;

int n, m, k;

int bit[N];

inline int lowbit(int x) { return x & -x; }

inline void update(int x, int val) { 

    while(x < N) {
        bit[x] += val;
        x += lowbit(x);
    } 
}
inline int query(int x) {

    int ans = 0;
    while(x) {
        ans += bit[x];
        x -= lowbit(x);
    }
    return ans;
}
inline int getsum(int l, int r) {

    return query(r) - query(l);
}
int main() {

    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin>>n>>m>>k;
    int tmp = 0, ans = 0;
    for(int i = 1; i <= n; ++i) cin>>tmp, update(tmp, 1);
    for(int i = 0; i < N; ++i) {
        if(i < m && getsum(0, i) == k) update(i, -1), ans++;
        if(i >= m && getsum(i - m, i) == k) update(i, -1), ans++;
    }
    cout<<ans<<endl;
    return 0;
}

---

## 作者：staygone (赞：2)

看了大佬们的题解，我有些疑惑，为什么这么复杂？

## solution

从这道题入手，了解题意，第一眼看上去是贪心。所以我们具体讨论一下这个贪心的策略：如果在 $m$ 阶段内，有大于等于 $k$ 个闹钟，小明就应该关掉一些闹钟，那应该关哪些？为了让下一个阶段减少负担，我们尽量关后面的，从而让我们关闹钟的利益最大。

## code

我使用了双指针的办法实现了整个贪心过程。

```
#include <bits/stdc++.h>

using namespace std;

int n, m, k;

int a[1000005];
bool vis[1000005]; // 用来标记

int main () {
	cin >> n >> m >> k;
	
	for (int i = 1; i <= n; i ++) {
		cin >> a[i];
	}
    
	sort (a + 1, a + 1 + n); // 按时间排序，这是必然的
	int ans = 0;
	int l = 1, r = 1, now = 0;
	while (r <= n) {
		now ++;
		while (a[r] - a[l] >= m) { // 枚举这个阶段
			if (!vis[l]) now --;
			l ++;
		}
		if (now >= k) {
			ans ++, now --;
			vis[r] = 1;
		}
		r ++;
	}
	cout << ans;
} 
```

---

## 作者：cqbzrjx (赞：0)

[原题传送门](https://codeforces.com/problemset/problem/898/D)

## 前言

此题甚水，但蒟蒻考试时却没有做出，罪过罪过！

## 分析

题目要求我们在 $[i,i + m]$ 的区间内，闹钟数量不超过 $k$ 个。如果直接枚举第 $i$ 种情况，复杂度为 $O(n \times m)$，显然是会超时的。

此时使用贪心思想，当我们在挨个枚举闹钟数量的时候，可以开个队列 $q$ 记录闹钟的数量。记 $res$ 为拔掉的个数，当需要拔的时候，$a_{i}$ 直接出队并让 $res$ 记录一下即可。但是需要注意，为了让队列只扫 $1$ 遍，所以先排序，保证 $a_{i}$ 单调递增。

时间复杂度：$O(n \log n)$。

## AC code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 5;
int n,m,k,res;
int a[maxn];
queue<int> q;//见思路
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin>>n>>m>>k;//输入
	for(int i = 1;i <= n;i++)
	{
		cin>>a[i];
	}
	sort(a + 1,a + 1 + n);//先排序
	for(int i = 1;i <= n;i++)
	{
		while(!q.empty() && a[i] - q.front() >= m)//清空队列
		{
			q.pop();
		}
		if(q.size() >= k - 1)//满足情况
		{
			res++;
		}
		else//否则再次入队
		{
			q.push(a[i]);
		}
	}
	cout<<res<<endl;//输出
	return 0;//完结，撒花
}
```

[AC submissions](https://codeforces.com/contest/898/submission/278744773)

---

## 作者：ybc2026lhy (赞：0)

[博客食用效果更佳](https://www.luogu.com.cn/article/3db2q3hz)

[双端队列](https://blog.csdn.net/m0_60593173/article/details/131488498)

##### 分析：
此题我用的是双端队列来做，在排序后，如果在遍历时，长度大于等于 $k$ 并且时间小于等于 $m$ 则队尾出列，总答案加一；如果在长度大于等于 $k$ 但是时间大于 $m$ 时，则队首出列。

AC Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,k,a[200005],sum=0;
deque<int> q;//双端队列
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL),cout.tie(NULL);
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+n+1);//必须排序
	for(int i=1;i<=n;i++){
		q.push_back(a[i]);//从队尾入队
		if(a[i]-q.front()+1<=m&&q.size()>=k){//满足条件
			sum++;//删除个数加1
			q.pop_back();//删除队尾
		} else if(q.size()>=k){
			q.pop_front();//长度超过k但时间超过m，把队头出队
		}
	}
	cout<<sum<<"\n";
	return 0;
}

---

## 作者：cqbzcjh (赞：0)

很明显的贪心。

先将闹钟按时间从小到大排序，把排序后的任意 $k$ 个连续的闹钟看作一个区间。

遍历所有区间，如果区间末和区间首的时间差小于等于 $m$ 分钟，就说明这个区间是不满足要求的，需要进行删除：

采取贪心策略，因为区间末对其它区间的影响是最大的（类似于区间贪心问题），所以我们从区间末开始删，每次将区间末的下一个闹钟作为新的区间末，一直删到满足要求为止。
## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,m,k,sum[N],ans;
vector<int> a;
//vector比较方便删除
int main(){
	ios::sync_with_stdio(NULL);
	cin.tie(NULL);cout.tie(NULL);
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		a.push_back(x);
	}
	sort(a.begin(),a.end());
	for(int i=0;i+k-1<a.size();i++){
		int j=i+k-1;
		while(a[j]-a[i]+1<=m&&j<a.size()){
			//还要判断后面全删完的情况
			a.erase(a.begin()+j,a.begin()+j+1);
			//erase删除元素
			ans++;
		}
	}
	cout<<ans;
	return 0;
}
```

[Submission](https://codeforces.com/contest/898/submission/278762322)

---

## 作者：灵茶山艾府 (赞：0)

**题意**：数轴上有 $n$ 个点，要求任意长为 $m-1$ 的闭区间不能包含 $\ge k$ 个点，至少要去掉多少个点？

排序后，用**不定长滑窗**做。

维护窗口内的点的个数 $\textit{cnt}$。枚举 $a_i$ 作为窗口右端点位置，如果窗口长度 $\ge m$ 则移动窗口左端点 $\textit{left}$。如果发现 $\textit{cnt}=k$，则优先删除窗口最右边的点，这样更右边的窗口可以包含的点更少。

代码实现时，把 $a_i$ 置为 $0$，表示删除。移动窗口左端点时，如果 $a_{\textit{left}}>0$ 则把 $\textit{cnt}$ 减一，否则不变。

Go 语言代码：

```go
package main
import("bufio";."fmt";"os";"slices")

func main() {
	in := bufio.NewReader(os.Stdin)
	var n, m, k, cnt, left, ans int
	Fscan(in, &n, &m, &k)
	a := make([]int, n)
	for i := range a {
		Fscan(in, &a[i])
	}
	slices.Sort(a)
	for i, x := range a {
		cnt++ // 移入窗口
		for x-a[left] >= m {
			if a[left] > 0 {
				cnt-- // 移出窗口
			}
			left++
		}
		if cnt == k {
			a[i] = 0 // 删除
			cnt--
			ans++
		}
	}
	Print(ans)
}
```

时间复杂度：$\mathcal{O}(n\log n)$。瓶颈在排序上。

欢迎关注 [B站@灵茶山艾府](https://space.bilibili.com/206214)

---

## 作者：enyyyyyyy (赞：0)

- 题意：

  有 $n$ 个闹钟，第 $i$ 个会在第 $a_{i}$ 时刻开始叫到 $m+a_{i}$ 分钟结束，如果在 $m$ 阶段内，有大于等于 $k$ 个闹钟，就要关掉一些闹钟，输出最少关掉的闹钟数 $ans$。
- 思路：

  第一眼看上去是贪心，贪心策略为排序，可以用队列优化。
  队列还要判断这一段是否大于 $m$。

- 代码：
  
 ```cpp
#include <bits/stdc++.h>
#define ll long long
#define lint __int128
using namespace std;//快读 
inline ll read() {
    ll s = 0, w = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-')
            w = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') s = s * 10 + ch - '0', ch = getchar();
    return s * w;
}
inline void print(ll x) {//快输 
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x >= 10)
        print(x / 10);
    putchar(x % 10 + '0');
    return;
}
ll n,m,k,ans;//变量定义 
queue<ll>q;//队列 
priority_queue<ll,vector<ll>,greater<ll> >a;//优先队列免去排序 
int main(){
	n=read(),m=read(),k=read();//输入 
	for(int i=1;i<=n;i++) a.push(read());
	while(!a.empty()){//同for(ll i=1;i<=n;i++)或while(!a.size()) 
		while(!q.empty()&&a.top()-q.front()>=m) q.pop();//清空队列 
		if(q.size()+1>=k) ++ans;//满足条件 
		else q.push(a.top());//加入队列 
		a.pop();//弹出做过的元素 
	}
	print(ans);//输出 
	return 0;
}
```


---

## 作者：JackMerryYoung (赞：0)

# 前言

这道题是一道单调队列的模板题，一遍即可 $\color{green}\text{AC}$，没有太多的坑点。

可能有人看到题目没有标签就不知所措（我当时就是这样），但是不要放弃。

十分推荐先做一下滑动窗口（一道跟他几乎一模一样的黄题），这里给出链接：[/tp "滑动窗口"](https://www.luogu.com.cn/problem/P1886)

那么，废话不多说，开始讲题！

# 正文

首先观察一下题目本身，我们看到了一句话：

**如果在连续的 $m$ 分钟内有至少 $k$ 个闹钟响起**

这段话极其重要，影响了我们的做题思路。

看到这句话，我们想起了值域问题，可是太麻烦，不想做怎么办？

想想滑动窗口。

我们在这里可以认为有一个大小为 $m$ 的滑动窗口，如果窗口里同时出现了 $k$ 个点，就认为要关掉这个点。

想到这里，就很好做了，直接上单调队列板子，略微调整即可。

至于乱序的问题，直接排序即可。

这里再讲一下单调队列：

在大小为 $k$ 的单调队列里，如果有元素 $i$ 满足 $i \leq tail - k$，那么我们就认为元素 $i$ 是过时的，就得杀了他。

在单调队列里，还有一种情况：

**_我比你小，我又比你新，你就被我杀掉了。_**

意思就是我比你小，可以给后面的人更多机会；我又比你新，可以获得延长一会儿时间，那队列的最后一个人就得死了。

这个操作很好地维护了单调性。

# 代码

~~你们最想要的..~~ 

Talk is$\color{white}\text{n't}$ cheap, $\color{white}\text{Don't}$ show me the code..

``` cpp
#include <bits/stdc++.h>
using namespace std;

int N, M, K, ans;
int arr[200005];

void input();
void work();
void output();

int main()
{
	input();
	work();
	output();
}

void input()
{
	cin >> N >> M >> K;
	for(int i = 1; i <= N; i ++)
	{
		cin >> arr[i];
	}
}

void work()
{
	sort(arr + 1, arr + N + 1);
	int q[200005], head = 1, tail = 0;
	for(int i = 1; i <= N; i ++)
	{
		while(head <= tail && q[head] <= arr[i] - M) ++ head;
		q[++ tail] = arr[i];
		while(tail - head + 1 >= K) 
		{
			++ ans;
			-- tail;
		}
	}
}

void output()
{
	cout << ans << endl;
}
```

注：有些人不喜欢手写队列，其实用 STL Deque 与我的写法是一样的，想用的话可以看这位大佬的博客（[/tp "yongai-ZSR"](https://www.luogu.com.cn/blog/yongai-ZSR/cf898d-ti-xie)）

---

