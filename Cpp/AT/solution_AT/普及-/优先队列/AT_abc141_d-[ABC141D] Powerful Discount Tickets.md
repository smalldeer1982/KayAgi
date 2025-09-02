# [ABC141D] Powerful Discount Tickets

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc141/tasks/abc141_d

高橋くんは $ N $ 個の品物を $ 1 $ 個ずつ順番に買う予定です。

$ i $ 番目に買う品物の値段は $ A_i $ 円です。

高橋くんは $ M $ 枚の割引券を持っています。

品物を買う際に割引券を好きな枚数使うことができます。

$ X $ 円の品物を買う際に $ Y $ 枚の割引券を使った場合、その品物を $ \frac{X}{2^Y} $ 円(小数点以下切り捨て)で買うことができます。

最小で何円あれば全ての品物を買うことができるでしょうか。

## 说明/提示

### 制約

- 入力は全て整数である。
- $ 1\ \leq\ N,\ M\ \leq\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ 10^9 $

### Sample Explanation 1

以下のように割引券を使えば、合計 $ 9 $ 円で全ての商品を買うことができます。 - $ 1 $ 番目に買う品物には割引券を使わず、$ 2 $ 円で買います。 - $ 2 $ 番目に買う品物には $ 2 $ 枚の割引券を使い、$ 3 $ 円で買います。 - $ 3 $ 番目に買う品物には $ 1 $ 枚の割引券を使い、$ 4 $ 円で買います。

### Sample Explanation 3

$ 1000000000 $ 円の品物を買う際に $ 100000 $ 枚の割引券を使うと $ 0 $ 円で買うことができます。

## 样例 #1

### 输入

```
3 3
2 13 8```

### 输出

```
9```

## 样例 #2

### 输入

```
4 4
1 9 3 5```

### 输出

```
6```

## 样例 #3

### 输入

```
1 100000
1000000000```

### 输出

```
0```

## 样例 #4

### 输入

```
10 1
1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000```

### 输出

```
9500000000```

# 题解

## 作者：_Life_ (赞：3)

### 题意：

有 $n$ 个物品和 $m$ 张打折券，每使用一次打折券都可以让一个物品的价格减半（可对一物品重复使用），求打折后的最低总价格。

### 题解：

因为打折券可以重复使用，我们想最大化折扣力度，所以就有了一个很显然的贪心：每次选出价格最高的物品使用打折券。

代码时间复杂度 $O((n+m)\log n)$

### 代码：
```cpp
#include<queue>
#include<cstdio>
#define int long long
using namespace std;
int n,m,x,ans;
priority_queue <int> q;
signed main()
{
	scanf("%lld %lld",&n,&m);
	for(int i=0;i<n;i++)
	{
		scanf("%lld",&x);
		q.push(x);
	}
	for(int i=0;i<m;i++)
	{
		x=q.top();
		q.pop();
		q.push(x/2);
	}
	while(!q.empty())
	{
		ans+=q.top();
		q.pop();
	}
	printf("%lld",ans);
}
```

---

## 作者：liangbowen (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/AT4864)

小学生又来写题解啦！

对于每张优惠券，我们应该给**当前最大**的物品使用。

如果使用普通的数组，每次都找最大值太慢了。

因此，我们使用传说神器：**优先队列**。

其他题解都没有说优先队列的用法，那么我来告诉大家。

以下程序就是优先队列的基本用法。

```cpp
#include <cstdio>
#include <iostream>
#include <queue>  //优先队列的头文件。 
using namespace std;
priority_queue <int> Q;  //定义一个优先队列。 
//优先队列的作用是：将队列从大到小自动排序。
int main()
{
	Q.push(30);  //在优先队列里增加一个数。
	Q.push(50);  //再增加一个数。
	Q.push(40);  //再增加一个数。
	//此时，队列的元素是：五十、四十、三十。
	printf("%d\n", Q.top());  //输出队首，即五十。
	Q.pop();  //将队首弹出，即删除五十。
	while (!Q.empty()) //条件的意思是，如果队列不为空。 
	{
		printf("QAQ\n");
		Q.pop();
	}
	return 0;
}
```

好了，弄明白优先队列后，我们就可以轻松做这一题了。

## 送上满分代码：


```cpp
#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;
priority_queue <int> Q;
int main()
{
	//以下为输入。 
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		int x;
		scanf("%d", &x);
		Q.push(x);
	}
	//以下是使用优惠券的过程。 
	for (int i = 1; i <= m; i++)
	{
		int t = Q.top();
		Q.pop();
		Q.push(t / 2);
		/*
		注意不能写成下面这样。
		Q.push(Q.top() / 2);
		Q.pop();
		*/
	}
	//计算结果并输出。 
	long long sum = 0;
	while (!Q.empty())
	{
		sum += Q.top();
		Q.pop();
	}
	printf("%lld\n", sum);  //千万别忘了换行。 
	return 0;		
}
```


---

## 作者：_byta (赞：2)

按照贪心的思路，我们每次会找出当前所有物品中价值最大的物品，使用

一张优惠券将其价格减半，用优先队列维护所有物品中价格最大的物品，每次

取出对头元素，将其减半后再加入队列，直到用完所有优惠券。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=100002;
int n,m,p,k,ans,sum,tot,cnt,a[N];
priority_queue<int> q;
signed main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		sum+=a[i];
		q.push(a[i]);
	}
	while(m>0)
	{
		int hh=q.top();
		q.pop();
		sum-=hh;
		hh/=2;
		sum+=hh;
		q.push(hh);
		m--;
	}
	cout<<sum;
	return 0;
}
```



---

## 作者：dd_d (赞：1)

## Sol  
首先很容易想到，若要总花费最少，那么每次打折券都要用在当前最大的物品上。  
那么我们可以维护一个大根堆，每次取出堆顶然后使用一张优惠卷再丢回堆里。  
## Code  
```cpp
//LYC_music yyds!
#include<bits/stdc++.h>
#define int long long
using namespace std;
int read()
{
	int pos=1,num=0;
	char ch=getchar();
	while (!isdigit(ch))
	{
		if (ch=='-') pos=-1;
		ch=getchar();
	}
	while (isdigit(ch))
	{
		num=num*10+(int)(ch-'0');
		ch=getchar();
	}
	return pos*num;
}
void write(int x)
{
	if (x<0)
	{
		putchar('-');
		write(-x);
		return;
	}
	if (x>=10) write(x/10);
	putchar(x%10+'0');
}
void writesp(int x)
{
	write(x);
	putchar(' ');
}
void writeln(int x)
{
	write(x);
	putchar('\n');
}
priority_queue<int> q;
int n,m,a[100001],ans;
signed main()
{
	n=read(); m=read();
	for (int i=1;i<=n;i++)
		a[i]=read();
	for (int i=1;i<=n;i++)
		q.push(a[i]);
	for (int i=1;i<=n;i++)
		ans+=a[i];
	for (int i=1;i<=m;i++)
	{
		int x=q.top();
		q.pop();
		ans-=x;
		x/=2;
		ans+=x;
		q.push(x);
	}
	writeln(ans);
}



```


---

## 作者：_dijkstra_ (赞：0)

小号第二次写水题题解。

## 思路

贪心。每个优惠券等同于 $a_i \to \left\lfloor
\dfrac{a_i}{2}\right\rfloor$。所以可以贪心求解。

每次扔进一个优先队列，取最大值，除以二，再扔回优先队列里。

最后累加队列里的所有元素即可。注意要使用 `long long`。

时间复杂度 $O((n +m) \log n)$，稳过。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
	priority_queue<int>q; //大根堆 
	int n,m;
	cin>>n>>m;
	while(n--) {
		int x;
		cin>>x;
		q.push(x);
	}
	while (m--) { 
		int t=q.top();
		q.pop();
		q.push(t>>1);
	}
	long long sum=0;
	while (!q.empty()) {
		sum+=q.top();
		q.pop();
	}
	cout<<sum;  //记得换行
	return 0;		
}
```

---

## 作者：AlicX (赞：0)

#### 这是一道考验STL中的优先队列的练习题

 前置知识：[优先队列](https://blog.csdn.net/weixin_36888577/article/details/79937886?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522166299110516782428676017%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=166299110516782428676017&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~top_positive~default-1-79937886-null-null.142^v47^pc_rank_34_2,201^v3^control_2&utm_term=%E4%BC%98%E5%85%88%E9%98%9F%E5%88%97&spm=1018.2226.3001.4187)

### 具体思路 
首先我们已经知道了优先队列分为大根堆和小根堆，大根堆就是将大的数放在最前面，小根堆就是将小的数放在最前面，这道题就可以用贪心的写法，为了使优惠的价格最多，便要挑价格最大的出来优惠，所以我们可以将每一个 $a[i]/2$ 放入优先队列中，然后遍历一遍队列就可以了，具体看代码

### AC code
```cpp
#include<bits/stdc++.h>
#define int long long
#define x first
#define y second
using namespace std;
typedef pair<int,int> pii;
const int N=1e5+10;
int n,m;
priority_queue<int> q;//定义优先队列，默认为大根堆 
signed main(){
	cin>>n>>m;
	while(n--){
		int x;
		cin>>x;
		q.push(x);//将为操作的先插入进q 
	}
	while(m--){//共m张优惠价 
		int t=q.top();
		q.pop();
		q.push(t/2);//将t打折后的值放入队列 ，队列内部会将t/2排位置（大的在前，小的在后） 
	}
	int ans=0;
	while(!q.empty()) ans+=q.top(),q.pop();//求和 
	cout<<ans<<endl;
	return 0;
}
```
$The$ $end$

---

## 作者：tZEROちゃん (赞：0)

我们注意到每一件商品是可以使用多张优惠券的，所以有一个很显然的贪心，就是每次在 **目前** 所有商品的价格中找到最贵的，对它使用优惠券。正确性显然。

那么我们发现，这个算法的时间复杂度是 $\mathcal O(NM)$，而 $1\le N,M\le 10^5$，所以 $NM$ 可能会达到 $10^{10}$，必然会超时。

我们考虑使用优先队列，优先队列可以：

- 在 $\mathcal O(\log |Q|)$ 的时间复杂度内删除或插入元素（$|Q|$ 是在优先队列内的元素个数）。
- 在 $\mathcal O(1)$ 的时间复杂度内得到优先队列中的最大值。

使用优先队列之后，我们可以在 $\mathcal O(\log N)$ 的时间复杂度内完成取出队列中最大值并将它除以 $2$ 的操作，所以总的时间复杂度是 $\mathcal O(\log N)$。

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long LL;

#define rep(i, l, r) for(auto i = (l); i <= (r); i ++)
#define per(i, r, l) for(auto i = (r); i >= (l); i --)

int main() {
  LL n, m;
  cin >> n >> m;
  priority_queue<LL, vector<LL>, less<LL>> que;
  rep (i, 1, n) {
    LL x; cin >> x;
    que.push(x);
  }
  rep (i, 1, m) {
    LL a = que.top(); que.pop();
    que.push(a / 2);
  }
  LL ans = 0;
  rep (i, 1, n) {
    ans += que.top(); que.pop();
  }
  cout << ans << endl;
}
```

---

## 作者：sgl654321 (赞：0)

### 题意描述
给定 $k$ 个优惠券，每个优惠券能让任意一个商品的价格 $a_i$ 变为 $\lfloor \dfrac{a_i}{2}\rfloor$。求出最终最小的商品价格之和。

### 解题思路
贪心法。在最优情况下，要把每一张优惠券都作用在**价格最大的商品**上。

用样例 $1$ 举个例子：

- 将第一张优惠券作用在 $13$ 上，变为 $6$。
- 将第二张优惠券作用在 $8$ 上，变为 $4$。
- 将第三张优惠券作用在 $6$ 上，变为 $3$。

所以，答案为 $2+3+4=9$。

如果暴力寻找最大值，时间复杂度为 $O(nm)$，显然会超时。

很容易想到使用大根堆。大根堆就是一个保证父亲节点一定比儿子节点大的一个堆。显然，大根堆的根是整个堆的最大值。我们都要将优惠券作用在根节点上。作用完之后记得维护大根堆，使用下传。

题外话：发现很多人都用了 STL，我来一个手写的。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long ans,x,save,n,k,a[100010],h[800010],tot;
void up(int ii){
	if(ii==1)return;
	if(h[ii/2]<h[ii]){
		swap(h[ii/2],h[ii]);
		up(ii/2);
	} 
}
void down(int ii){
	if(ii*2>tot)return;
	if(ii*2==tot){
		if(h[ii]<h[ii*2])swap(h[ii],h[ii*2]);
		return;
	}
	if(h[ii*2]>h[ii*2+1])save=ii*2;
	else save=ii*2+1;
	if(h[ii]<h[save]){
		swap(h[ii],h[save]);
		down(save);
	}
}
void ins(int x){
	tot++;
	h[tot]=x;
	up(tot);
}
void del(){
	h[1]=h[tot];
	tot--;
	if(tot>0)down(1);
}
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		ins(a[i]);
	}
	for(int i=1;i<=k;i++){
		x=h[1];
		del();
		ins(x/2);
	}	
	for(int i=1;i<=tot;i++)
		ans+=h[i];
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：xieyikai2333 (赞：0)

# AtCoder ~~水~~题

- 第一次写 AtCoder 题解

- [题目传送门](https://www.luogu.com.cn/problem/AT4864)

---

- 这篇题解的代码很短，思路也很清晰，适合初学者食用

题目的意思其实可以转换为：使用一张抵扣券可以使一件物品的价格变成原来的一半（向下取整）。

而题目又要求总价最小，所以每次挑**最贵的**物品打折即可。

这里使用**优先队列**（小根堆）实现维护序列最大值。每次取出队首元素即为最大值，将其变为原来的一半，再插入进去，重复 $m$ 次。最后，求出所有物品总价即为所求答案。

---

**AC 代码**：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
priority_queue<int> q;
signed main()
{
	int n,m,x,ans=0;
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>x,q.push(x);
	while(m--)q.push(q.top()/2),q.pop();
	while(!q.empty())ans+=q.top(),q.pop();
	cout<<ans;
	return 0;
}
```

---

## 作者：Otomachi_Una_ (赞：0)

裸的贪心，每一次都把优惠券放在当前最贵物品上。

先把所有物品压入优先队列，每一次使用优惠券都取出队首将其价格减半后在压入队列。

## _Code_
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
#define ll long long
priority_queue<ll> us;
ll n,m,a;
ll ans=0;
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a;
		us.push(a);
	}
	for(int i=1;i<=m;i++){
		int x=us.top();
		us.pop();
		us.push(x/2);
	}
	while(!us.empty()){
		ans+=us.top();
		us.pop();
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：MiddleRed (赞：0)

## Discription  
$N$ 个物品，买第 $i$ 个要 $A_i$ 元。现有 $ M $ 个抵扣券，使用 $Y$ 个抵扣券可以使需要 $A_i$ 的物品只需要付 $\left\lfloor\frac{A_i}{2^Y}\right\rfloor$ 元。求出购买所有物品需要的最少总额。

## Solution  
裸的贪心。每次选取最贵的物品用一次抵扣券，然后放回去。之后再选一次最贵的，再用一次，如此经过 $M$ 次。  
不难发现，由于我们每次都要选出最贵的物品，所以我们用优先队列来维护。我们先计算原来所有物品总和放入 $ans$ ，然后每次选择算一下用抵扣券后相比原来省了几块钱，从 $ans$ 中减去。最后直接输出即可。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,p;
long long ans;
priority_queue<int> q;
int main()
{
	cin>>n>>m;
	for(int i=0;i<n;i++)	
	{
		cin>>p;
		q.push(p);
		ans+=p;
	}
	for(int i=0;i<m;i++)
	{
		int t=q.top();
		ans-=(t-floor(t/2));
		q.push(floor(t/2));
		q.pop();
	}
	cout<<ans<<endl;
	return 0;
}
```
~~极致压行~~
```cpp
#include<bits/stdc++.h>
long long n,m,p,i,ans;
std::priority_queue<long long> q;
int main(){
    for(scanf("%lld%lld",&n,&m);i<n;scanf("%lld",&p),q.push(p),ans+=p,i++);
	for(i=0;i<m;ans-=(q.top()-floor(q.top()/2)),q.push(floor(q.top()/2)),q.pop(),i++);
	printf("%lld",ans);
}
```


---

