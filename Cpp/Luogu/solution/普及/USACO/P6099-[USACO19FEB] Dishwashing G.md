# [USACO19FEB] Dishwashing G

## 题目背景

Bessie 和 Elsie 正在帮助 Farmer John 洗碗，这是一个比人们想象的更复杂的过程。

## 题目描述

两头奶牛决定 Bessie 负责涂肥皂，Elsie 负责冲洗。

刚开始的时候，$N$ 个脏盘子（保证是从 $1$ 到 $N$ 的一个排列）堆在 Bessie 那里，而 Elsie 这边的堆是空的。而在她们俩之间，则有一张专门放涂过肥皂的盘子的桌子。

每个冲洗步骤需要执行以下两个操作之一：

- Bessie 从脏盘子堆顶取出一个盘子，涂上肥皂，然后放在桌子上。将这个盘子放在桌子上时，Bessie 只能放在现有的非空盘堆的顶端，或是在最右边新增一个盘堆。
- Elsie 从桌子最左边的盘堆的顶端拿起盘子，将它冲洗后放在干净的盘堆顶端。

她们希望干净的盘堆能按编号排序，编号最小的在底端，编号最大的在顶端。然而她们发现有的时候这并不可能做到。现在给定脏盘子的堆叠顺序，请你求出一个最大前缀，使得该前缀的所有盘子洗干净后，能按上面的要求堆叠。

## 样例 #1

### 输入

```
5
4
5
2
3
1```

### 输出

```
4```

# 题解

## 作者：45dino (赞：8)

这道题还是挺考验思维的，我思考了一下午才AC。

~~我才不会告诉你我是边水犇犇边玩candybox边玩巴克球边写英语作业边做题的，其实真正代码只写了5min。~~

把问题转换成人话，就是要求前ans个脏盘子必须按顺序排列,输出ans（注意是输入的前ans个而不是编号的前ans个）。

还是看不懂？手玩一下样例：

![](https://cdn.luogu.com.cn/upload/image_hosting/e7dpyy61.png)

看完这排版极为凌乱的图后，有没有一种~~一脸懵逼~~茅塞顿开的感觉呢，如果有，就试着写一写吧。

附上喜闻乐见的代码：

```
#include<bits/stdc++.h>
using namespace std;
int n,placed,base[100001];
vector<int> item[100001];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int x;
		cin>>x;
		if(x<placed)
		{
			cout<<i-1;
			return 0;
		}
		for(int j=x;j>0&&!base[j];j--)
			base[j]=x;
		while(!item[base[x]].empty()&&item[base[x]].back()<x)
		{
			placed=item[base[x]].back();
			item[base[x]].pop_back();
		}
		item[base[x]].push_back(x);
	}
	cout<<n;
	return 0;
}
```


---

## 作者：zzbzwjx (赞：4)

## 题目大意
求前 $ans$ 个脏盘子按顺序排列时 $ans$ 的最大值。

## 思路
我们必须要让第 $i-1$ 个栈的栈底元素小于第 $i$ 个栈的栈顶元素。

对于插入第 $i$ 个数：

* 如果 $i$ 比已经放入答案数组中的元素还要小，输出答案。

* 如果 $i$ 比最后一个栈的栈底元素还要大，则新建一个栈。

* 否则将 $i$ 插入已有的栈中，先二分查询在它应该在哪个栈内，然后将栈中所有比它大的数放进答案数组中，再把它插入栈中。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int>a[100001];
int n,p,b[100001],x;
int main(){
	cin>>n;
	for(int i=1;i<=n;++i){
		cin>>x;
		if(x<p){cout<<i-1;return 0;}
		for(int j=x;j>0&&!b[j];--j)b[j]=x;
		while(!a[b[x]].empty()&&a[b[x]].back()<x){
			p=a[b[x]].back();a[b[x]].pop_back();
		}
		a[b[x]].push_back(x);
	}
	cout<<n;
	return 0;
}
```
~~（这应该是本题最短的代码了吧）~~

---

## 作者：DengDuck (赞：4)

时间复杂度为 $\mathcal O(n\log^2 n)$ 的逆天做法。

首先答案具有单调性，可以二分一手答案。

然后我们想一想放碟子的策略。

显然，碟子堆内部满足单调性，上面比下面小，因为上面应该先取出来。

显然，碟子堆彼此之间也有单调性，左边的堆肯定比右边的堆小（所有元素都是如此，任意左边堆的元素都小于右边堆的任意元素）。

因此我们放碟子时也要维护出这个单调性，找到最左边的顶部编号大于碟子编号的堆即可。

同时，如果最左边的堆可以弹出未弹出的元素中的最小值，就弹出即可。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N=2e5+5;
LL n,a[N],b[N],s[N],t,tot,cnt;
queue<LL>q;
deque<LL>v[N];
bool pd(LL x)
{
	for(int i=1;i<=n;i++)b[i]=a[i],v[i].clear();
	sort(b+1,b+x+1);
	while(!q.empty())q.pop();
	for(int i=1;i<=x;i++)q.push(b[i]);
	t=1,tot=0,cnt=0;
	for(int i=1;i<=x;i++)
	{
		LL l=t,r=tot,ans=-1;
		while(l<=r)
		{
			LL mid=(l+r)/2;
			if(v[mid].front()>a[i])
			{
				r=mid-1;
				ans=mid;
			}
			else l=mid+1;
		}
		if(ans==-1)ans=++tot;
		v[ans].push_front(a[i]);
		while(!q.empty()&&t<=tot&&q.front()==v[t].front())
		{
			v[t].pop_front();
			
			q.pop();
			if(v[t].empty())t++;
		}
	}
	return q.empty();
}
int main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
	}
	LL l=1,r=n,ans=0;
	while(l<=r)
	{
		LL mid=(l+r)/2;
		if(pd(mid))
		{
			l=mid+1;
			ans=mid;
		}
		else r=mid-1;
	}
	printf("%lld",ans);
}
```

---

## 作者：miao5 (赞：3)

**题目大意：**

给定 $n$ 个数，从1到 $n$ ，**数的初始顺序不保证！！！**

每次可以有两种操作：

- 把第 $i$ 个数放到中转栈里：

    - 可以放入一个已有的栈的顶端。
    - 可以在**最右边**创建一个新的栈，把这个数放到新的栈里边。
- 取出**最左边**的栈里的最顶上的数，放到答案数组中。

求答案数组从下标1开始，能连续的，数和下标一样子串的最长长度是多少。

**思路：**

有一种贪心的策略就是我们必须要让第 $i-1$ 个栈的栈底元素小于第 $i$ 个栈的栈顶元素。

对于插入第 $i$ 个数：

- 如果 $i$ 比已经放入答案数组中的元素还要小，输出答案 $i-1$ 。

- 如果 $i$ 比最后一个栈的栈底元素还要大，则新建一个栈。

- 否则将 $i$ 插入已有的栈中，先二分查询在它应该在哪个栈内，然后将栈中所有比它大的数放进答案数组中，再把它插入栈中。

**code:**

```cpp
#include<iostream>
#include<vector>
#define N 100005
using namespace std; 
int n,head;
std::vector<int> a[N];
int main(){
	cin>>n;
	int head=0,maxn=0;
	for(int i=1;i<=n;i++){
		int x; 
		cin>>x;
		if(!head) a[++head].push_back(x);
		else{
			if(x<maxn){
				cout<<i-1;
				return 0;
			}
			if(a[head].front()<x){
				a[++head].push_back(x);
				continue;
			}
			int sum=-1,l=1,r=head;
			while(l<=r){
				int mid=l+r>>1;
				if(a[mid].front()>x){
					r=mid-1;
					sum=mid;
				} 
				else l=mid+1;
			}
			while(!a[sum].empty()&&a[sum].back()<x){
				maxn=max(maxn,a[sum].back());
				a[sum].pop_back();
			}	
			a[sum].push_back(x);
		}
	}
	cout<<n;
	return 0;
}
```


---

## 作者：cyn2006 (赞：3)

这道题翻译成人话其实还是蛮好做的。。。
> 题目~~翻译~~大意：可以操作若干次，每次可以按序将一个数推进已有的栈或新建的一个栈，或者将一个数取出，求最大推进的数的最大前缀使得取出的数有序。

因为是栈，而且需要按序取出，那么我们有一个贪心的策略，假设我们当前有 $n$ 个栈，这 $n$ 个栈都必须满足自上向下从大到小，并且对于任意的编号为 $i$ 的栈（编号越小表示越靠左，$i\geqslant 1$），需满足 $i+1$ 的**栈顶**元素大于 $i$ 的**栈底**元素。

对于插入第 $i$ 个数：

- 如果这个数比最后一个栈的栈底元素还要大，则新建一个栈；
- 如果这个数比之前取出的数的最大值要小，则说明之后无法有序，则答案为 $i-1$（因为这样我们可以从左到右将剩下的栈的元素依次取出且保证有序）；
- 否则将这个数插入栈中，先二分查询在哪个栈内，然后将栈中所有比这个数大的数弹出，再推进栈中。

然后本题就非常愉快地结束了。。。

时间复杂度：基于每一个数至多推入或者弹出 $1$ 次，然后需要二分一下，所以操作的时间复杂度为 $O(\log n)$，总时间复杂度为 $O(n\log n)$（但不知道为什么不加二分也能过，建议加强数据）。

代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define rep(i,x,y) for(int i=x,i##end=y;i<=i##end;++i)
#define _rep(i,x,y) for(int i=x,i##end=y;i>=i##end;--i)

struct istream{
#define gc getchar()
	template<typename T>inline istream&operator>>(T&x){
		char c; bool f=0; x=0;
		for(;!isdigit(c=gc);) f|=c=='-';
		for(x=c&15;isdigit(c=gc);x=x*10+(c&15));
		return f&&(x=-x),*this;
	}
	inline istream&operator>>(char&x){
		for(;!isalpha(x=gc);); return *this;
	}
#undef gc
} cin;

struct ostream{
#define pc putchar
	template<typename T>inline ostream&operator<<(T x){
		static char buf[25]; int cnt=0;
		if(!x) return pc('0'),*this;
		if(x<0) pc('-'),x=-x;
		while(x) buf[++cnt]=x%10|48,x/=10;
		while(cnt) pc(buf[cnt--]);
		return *this;
	}
	inline ostream&operator<<(char x){return pc(x),*this;}
	inline ostream&operator<<(const char*x){
		for(char*p=(char*)x;*p;++p) pc(*p);
		return *this;
	}
#undef pc
} cout;
#define N 100005
int n,head;
std::vector<int> v[N];
int main(){
	cin>>n;
	int head=0,mx=0;
	rep(id,1,n){
		int x; cin>>x;
		if(!head) v[++head].push_back(x);
		else{
			if(x<mx){
				cout<<id-1<<'\n';
				return 0;
			}
			if(v[head].front()<x){
				v[++head].push_back(x);
				continue;
			}
			int ans=-1,l=1,r=head;
			while(l<=r){
				int mid=l+r>>1;
				if(v[mid].front()>x) r=mid-1,ans=mid;
				else l=mid+1;
			}
			while(!v[ans].empty()&&v[ans].back()<x)
				mx=std::max(mx,v[ans].back()),v[ans].pop_back();
			v[ans].push_back(x);
		}
	}
	cout<<n<<'\n';
	return 0;
}
```

---

## 作者：songzhixin (赞：2)

### 解题思路

我们讨论每个盘子，分为三种情况：

1.若这个数字大于前面盘子的所有数，那么就另起一堆。

2.若有比这个数字大的盘子，则找到第一个数字比它大的，且最靠左边的一堆，把这一堆顶上比这个数大的元素全部按顺序放入另一个答案队列中。

3.若这个数字小于答案队列的最低下的元素，即最小的元素，代表着无法再保证升序排列，直接输出 $i-1$ 即可。

我们现在最坏时间复杂度为 $ O(n^2) $，但是可以加一些优化。

#### 优化

* 我们找第一个数字比它大的，且最靠左边的一堆的时候，因为满足单调递增，所以可以用二分。
* 我们不需要另外开一个答案数组，只需要用一个变量记录就可以。

优化后时间复杂度为 $ O(n \log{n}) $，可以过。 

### 正确代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long N=100005;
long long a[N];
deque<long long> q[N];
int main() {
	long long n;
	scanf("%lld",&n);
	for(long long i=1; i<=n; i++) {
		scanf("%lld",&a[i]);
	}
	long long minn=-0x3f3f3f3f;
	long long ans=0,cnt=1;
	q[1].push_front(a[1]);
	for(int i=2;i<=n;i++){
		if(minn>a[i]){
			printf("%lld\n",i-1);
			return 0;
		}
		if(a[i]>q[cnt].back()){
			q[++cnt].push_front(a[i]);
			continue;
		}
		int l=1,r=cnt;
		while(l<r){
			int m=(l+r)/2;
			if(q[m].back()>a[i]){
				r=m;
			}
			else{
				l=m+1;
			}
		}
		while(!q[r].empty()&&a[i]>q[r].front()){
			minn=q[r].front();
			q[r].pop_front();
		}
		q[r].push_front(a[i]);
		
	} 
	printf("%lld",ans);
	return 0;
}
```

### 注意事项

* 二分时比较的是队列的底部，但插入和删除时是队列的底部。
* 表示答案数组的数字应该初始化为极小值，而不是极大值。

---

## 作者：Addicted_Game (赞：1)

## [P6099 [USACO19FEB] Dishwashing G](https://www.luogu.com.cn/problem/P6099)

### 题目大意
~~洗盘子~~

你有 $n$ 个序号为 $x_i$ 的物品，你可以选择将它叠在前面的物品上或者放在最右边另起一堆。

与此同时，你可以拿走最左一堆的顶端物品。

问能以 $x_i$ 升序拿走的最大长度是多少。

### 思路
对于物品 $i$，若 $x_i$ 是当前最大的，那就另起一堆；若不是最大的，就用二分找到它应该在的位置，将比它小的全部拿走，将它放在那里。当 $x_i$ 比拿走的物品中 $x$ 最大的一个的 $x$ 还要大时，它之后的就不能保证升序，答案就是 $i-1$。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int a;
vector<int> v[100005];
int flag,big;
int main(){
	scanf("%d",&n);
	scanf("%d",&a);
	v[++flag].push_back(a);
	for(int i=2;i<=n;i++){
		scanf("%d",&a);
		if(a<big){
			printf("%d",i-1);
			return 0;
		}
		if(v[flag][0]<a){
			v[++flag].push_back(a);
		}else{
			int l=1,r=flag,mid,te=-1;
			while(l<=r){
				mid=l+r>>1;
				if(v[mid][0]>a) r=mid-1,te=mid;
				else l=mid+1;
			}
			while(v[te].size()&&v[te].back()<a){
				big=max(big,v[te].back());
				v[te].pop_back();
			}//因为物品严格递增，拿走这一列前面的就不用管了 
			v[te].push_back(a);
		}
	}
	printf("%d",n);
	return 0;
}
```

---

## 作者：lqsy002 (赞：1)

## 题目大意
[题目链接](https://www.luogu.com.cn/problem/P6099)。

有 $n$ 个按顺序摆放好的盘子，每个盘子都有一个序号，现在有无数个空的栈，按顺序操作盘子，每次你有两个操作：
1. 把当前的盘子放到某个栈的最顶上或者在栈的最右边新建一个栈，把盘子放进去。
2. 从非空栈的最左边的栈的最顶上拿一个盘子，要求按盘子序号从小到大拿出。

但是有可能并不能将所有盘子按序号拿出，所以问你最多能将序列中的前几个盘子按序号拿出。
## 解题思路
**二分。**
1. 按顺序处理每个盘子，遇到一个盘子的时候查找所有栈的最低端元素，以确定它是在哪个栈里面的。
2. 用一个数组维护栈底元素，当找到的栈的栈顶小于这个数的时候，那么必须要弹出，然后记录一个已经弹出的元素的最大值。
3. 之后如果有小的值过来的时候，它无处安放，这样就是不行的。
## 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,l=1,r=1,mx,p,a[100010],bot[100010];
stack<int>s[100010];
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    s[1].push(a[1]);
    bot[1]=a[1];
    for(int i=1;i<=n;i++){
        if(a[i]<mx){
        	printf("%d",i-1);
        	return 0;
	}
        p=upper_bound(bot+l,bot+r+1,a[i])-bot;
        if(p==r+1){
        	s[++r].push(a[i]);
		bot[r]=a[i];
	}
        while(s[p].top()<a[i]){
        	mx=s[p].top();
		s[p].pop();
	}
        s[p].push(a[i]);
    }
    printf("%d",n);
}
```

---

## 作者：柠檬布丁吖 (赞：1)

## 题意

有 $n$ 个编号 $1\sim n$ 的盘子，对于每个盘子，可以放在队列的顶部，也可以放在新的队列中。只有盘子在顶部时才可以取出。求取出盘子能得到的最大的连续编号长度。

## 思路
对于每个等待进入队列的盘子，选择一种方法处理：

1. 当前盘子编号大于之前盘子的编号，新建一个队列
2. 找到一个至少有一个盘子的编号比当前盘子大的队列，这堆盘子**越在左越**好。然后把个队列中所有比当前盘子编号小的盘子丢弃在回收站中。如果当前盘子编号比回收站中最大的盘子编号要小，输出答案。

这样做的原因是，保证每个队列中编号单调不升，最大化答案。

**注意：**

1. 不必真的建一个回收站存储丢弃的盘子。只要在丢弃时用变量记录即可。
2. 用二分优化找盘子堆的过程。

## 分析

请配合样例按食用。
![](https://cdn.luogu.com.cn/upload/image_hosting/zl7g8xg6.png)

- $i=1,x=4$ 
将编号 $4$ 的盘子放入新队列中。
- $i=2,x=5$
编号 $5$ 的盘子大于之前盘子的编号，放入新建的队列中。
- $i=3,x=2$
将编号 $2$ 的盘子放入第一个队列中，第一个队列中没有小于它编号的盘子。
- $i=4,x=3$
由于编号 $3$ 的盘子要放入最左边的队列中，其中编号 $2$ 的盘子小于其编号，将编号 $2$ 的盘子记录，并放入回收站中。接着，将编号 $3$ 的盘子放入最左边（第一个）队列中。
- $i=5,x=1$
编号 $1$ 的盘子小于已经丢入回收站的盘子 $2$ 的编号，输出答案。$ans=i-1$

## AC

```cpp
#include<iostream> 
#include<algorithm> 
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
const int maxn=1e5+55;
vector<int>p[maxn];
int n;
int _max=0,sum=0; 

signed main(void){
	
	cin>>n;
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		if(x<_max){
			cout<<i-1<<endl;
			return 0;
		}
		if(i==1){
			p[1].push_back(x);
			sum++;
			continue;
		}
		if(p[sum][0]<x){
			sum++;
			p[sum].push_back(x);
			continue;
		}
		
		int ret=0,l=1,r=sum,mid=0;
		while(l<=r){
			mid=(l+r)/2;
			if(p[mid][0]>x){
				ret=mid;
				r=mid-1;
			} else {
				l=mid+1;
			}
		}
		
		while(!p[ret].empty()&&p[ret].back()<x){
			_max=p[ret].back();p[ret].pop_back();
		}
		p[ret].push_back(x);
	}
	
	cout<<n<<endl;
	
	return 0;
} 
```


---

## 作者：wu13115899522 (赞：1)

题意：给定 $n$ 个有序的数字，每次可以插入一个序列的底部或者新建一个序列，使得每次取队头能产生的连续数字最多。

显然，“取”这一操作可以分为两类：

- 一直在一个序列里面取。

- 取不同序列的队头。

这两种操作是可以叠加的，所以在第一个不能满足时，我们就会考虑第二个操作，也就是新建一个序列。

那什么情况会满足不了呢？

- 如果当前点的值已经小于目前操作到的值，必定无法连续。两个操作都不能满足，直接输出上一个点。

- 如果当前点的值小于最后一个序列的队头值，则需要在前面的序列中找一个合适的序列进行插队。

需要注意，对于每一个点的队头，一定是满足单调递增。每一个序列内的值也满足单调递增。所以我们可以二分去找到位于的序列，让小于它的点让位，然后插队。

应该还是比较好理解的，代码如下：
```cpp
#include<bits/stdc++.h>
#define N 100005
#define int long long
using namespace std;
int n,x,h=0,maxx=0;
vector<int>a[N];
inline void read(int &x){
	x=0;int f=1;char c=getchar();
	while(!(c<='9'&&c>='0')){if(c=='-')f=-1;c=getchar();}
	while(c<='9'&&c>='0')x=(x<<1)+(x<<3)+(c^48),c=getchar();
	x*=f;
}
signed main(){
	read(n);
	for(int i=1;i<=n;i++){
		read(x);
		if(h==0)a[++h].push_back(x);
		else{
			if(x<maxx){//情况一
				printf("%d\n",i-1);
				return 0;
			}
			if(a[h].front()<x){//情况二
				a[++h].push_back(x);
				continue; 
			}
			int l=1,r=h;
			while(l<=r){//找到最适合的盘子 
				int mid=l+r>>1;
				if(a[mid].front()>x){
					r=mid-1;
				}
				else l=mid+1;
			}
			r++;//r为最合适的盘子 
			while(!a[r].empty()&&a[r].back()<x){
				maxx=a[r].back();//更新最值
				a[r].pop_back();//让位
			}
			a[r].push_back(x);//插队 
		}
	}
	return 0;
}

```




---

## 作者：pengzy (赞：0)

### 思路
理想状态下，题目要求放置一些堆盘子（废话），且对于第 $i$ 堆盘子，从上到下，是**从小号到大号的**（这样才能先洗小号）。并且，第 $i$ 堆盘子中号码最大的盘子的号码（即堆底盘子的号码）要小于第 $i+1$ 堆盘子中号码最小的盘子的号码（即堆顶盘子的号码）。

每个盘堆类似一个栈，于是我们可以开 $n$ 个 `vector` 来维护。对于第 $i$ 堆盘子，`v[i].front()` 是头部元素，也就是该堆盘子中号码**最大**的盘子的号码，而 `v[i].back()` 代表**最小**的号码。

为什么呢？因为 `front` 元素是这堆盘子里最先被 `push_back` 的，需要满足它是这堆里面号码**最大**的。

对于放入编号为 $k$ 的盘子，二分求出合适它的盘堆，再一一判断插入的位置。如果 $k$ 大于**已经洗干净的盘子中编号最大的盘子**，那么 $k$ 就放不了了。

### 注意
题目输出中的小号在下，大号在上的意思是**先洗干净小号盘，在洗干净大号盘**。

时间复杂度 $O(n \log n)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int Max=1e5+10;
int n,nxt,maxx;
//nxt表示盘堆的数量，即最右侧盘堆的编号
//maxx记录已经取出（洗干净）的盘子中号码最大的盘子 
vector<int> v[Max]; 
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++) {
		int k;cin>>k;
		//若没有盘堆，加一个盘堆 
		if(!nxt)v[++nxt].push_back(k);
		else{
			//若该盘子已经不能按顺序洗了
			if(k<maxx) { 
				cout<<i-1;
				return 0;
			}
			//放入新的一堆
			if(v[nxt].front()<k) { 
				v[++nxt].push_back(k);
				continue; 
			}
			//二分插入在哪一堆里 
			int ans,L=1,R=nxt;
			while(L<=R) {
				int mid=(L+R)>>1;
				if(v[mid].front()>k)R=mid-1,ans=mid;
				else L=mid+1;
			}
			//枚举插入在该堆的哪一位置
			//如要插入，就必须把上方小号的盘子洗干净
			//即pop_back掉 
			while(!v[ans].empty()&&v[ans].back()<k) {
				maxx=max(maxx,v[ans].back());
				v[ans].pop_back(); 
			}
			v[ans].push_back(k);
		}
	}
	//最理想状态 
	cout<<n;
	return 0;
}
```

---

## 作者：niaoji (赞：0)

## 题意分析
一些元素入栈，可选择加入原来的栈，也可选择创建新的栈。从上到下，从左到右取出每个元素并加入答案栈，要求答案栈底部小，顶部大。
## 思路
- 很明显这道题最终的答案满足**单调性**，于是在第一步摆放盘子的操作时也需要满足单调性。具体的：![](https://cdn.luogu.com.cn/upload/image_hosting/f0zz05m5.png?x-oss-process=image/resize,m_lfit,h_300,w_400)
- 根据图中的摆放顺序可以看出，当新加入的元素比前一个栈的栈顶元素要大时，就创建一个新的栈，并把上一个栈的所有元素从上往下取出加入答案栈。当新加入的元素比答案栈的栈底元素还要小时，直接输出 $i-1$ 即可，否则就加入当前栈。
## 实现
虽然题目描述是用栈存储，实际就用数组维护就可以了。由于方便首尾操作，我用的 vector 。
## 代码
```c
#include<bits/stdc++.h>
using namespace std;
vector<int> a[100010];
int n,x,b[100010],p;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>x;
		if(x<p)
		{
			cout<<i-1;
			return 0;
		}//新入队的元素小于栈底元素，结束 
		for(int j=x;j>0&&!b[j];j--) b[j]=x;
		while(!a[b[x]].empty()&&a[b[x]].back()<x) 
		{
			p=a[b[x]].back();
			a[b[x]].pop_back();
		}
		a[b[x]].push_back(x);
	}
	cout<<n;
	return 0;
	
}
```

---

## 作者：wanyiheng (赞：0)

### 题目思路：

因为题目要求最后是底部小，顶部大，满足单调性。所以在排放时也应具有单调性。对于编号为 $i$ 的盘子，若有比它小的，就将小的全拿走再放。若它是最大的，就另起一堆。若它是最小的，就输出 $i-1$。

### **code：**

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N=100010;

int n,cnt;
int a[N];

vector<int>vec[N];

int main()
{
	scanf("%d", &n);
	for(int i=1;i<=n;i++)
	{
		int x;
		scanf("%d", &x);
		if(x<cnt)
		{
			printf("%d\n", i-1);
			return 0;
		}
		for(int j=x;j>0&&!a[j];j--)a[j]=x;
		while(vec[a[x]].size()&&vec[a[x]].back()<x)
		{
			cnt=vec[a[x]].back();
			vec[a[x]].pop_back();
		}
		vec[a[x]].push_back(x);
	}
	printf("%d\n", n);
	
	return 0;
}
```

---

