# Berpizza

## 题目描述

Monocarp and Polycarp are working as waiters in Berpizza, a pizzeria located near the center of Bertown. Since they are waiters, their job is to serve the customers, but they choose whom they serve first differently.

At the start of the working day, there are no customers at the Berpizza. They come there one by one. When a customer comes into the pizzeria, she sits and waits for Monocarp or Polycarp to serve her. Monocarp has been working in Berpizza for just two weeks, so whenever he serves a customer, he simply chooses the one who came to Berpizza first, and serves that customer.

On the other hand, Polycarp is an experienced waiter at Berpizza, and he knows which customers are going to spend a lot of money at the pizzeria (and which aren't) as soon as he sees them. For each customer, Polycarp estimates the amount of money this customer can spend, and when he serves a customer, he chooses the one that is expected to leave the most money at Berpizza (in case there are several such customers, he chooses the one who came first among them).

Obviously, no customer can be served twice, so Monocarp and Polycarp choose which customer to serve only among those who haven't been served yet.

When the number of customers gets really high, it becomes difficult for both Monocarp and Polycarp to choose the customer they are going to serve. Your task is to write a program that makes these choices for them. Formally, your program should be able to process three types of queries:

- $ 1 $ $ m $ — a customer comes to Berpizza, and Polycarp estimates the amount of money that they will spend as $ m $ ;
- $ 2 $ — Monocarp serves a customer which came to the pizzeria first;
- $ 3 $ — Polycarp serves a customer which is expected to spend the largest amount of money at the pizzeria (if there are several such customers, the one that came to the pizzeria first is chosen).

For each query of types $ 2 $ and $ 3 $ , report the number of the customer who was served (the customers are numbered in the order they come to the pizzeria, starting from $ 1 $ ).

## 样例 #1

### 输入

```
8
1 8
1 10
1 6
3
2
1 9
2
3```

### 输出

```
2 1 3 4```

## 样例 #2

### 输入

```
6
1 8
1 10
1 8
3
3
3```

### 输出

```
2 1 3```

## 样例 #3

### 输入

```
8
1 103913
3
1 103913
1 103913
3
1 103913
1 103913
2```

### 输出

```
1 2 3```

# 题解

## 作者：D_xbang (赞：3)

**题意：**
-  $op$ 等于 $1$ 时，在序列中插入一个元素。
-  $op$ 等于 $2$ 时，从序列中删除最早插入的元素，并输出该元素是第几个插入的。
-  $op$ 等于 $3$ 时，从序列中删除最大的元素，并输出该元素是第几个插入的。



---


**思路：**

 1. 根据 $op$ 等于 $1$ 时，可以想到使用队列加结构体。
```cpp
struct node {
	int fl, w; //fl 是记录第几个进入队列的 w为值
};
```

2. 根据 $op$ 等于 $2$ 时，因为每个元素插入的顺序不同，所以我们可以定义一个布尔数组，通过循环判断是否在被删除。
```cpp
bool flag[500010];
```

3. 根据 $op$ 等于 $3$ 时，为了找出最大元素，故使用优先队列，构体再加上排序。
```cpp
priority_queue<node> q;
```

```cpp
struct node {
	int fl, w; //fl 是记录第几个进入队列的 w为值
	friend bool operator < (const node & a, const node & b) {
		if (a.w != b.w) return a.w < b.w;
		return a.fl > b.fl;
	}
};
```


---

****整体代码逻辑：****

1. $op$ 等于 $1$ 时，插入元素和第几个。
2. $op$ 等于 $2$ 时，遍历布尔数组，寻找最早插入的元素，并标记。
3. $op$ 等于 $3$ 时，访问队头元素，查询此元素是否被删除，若没被删除，则输出为第几个，最后弹出队头。


---


**代码：**

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, op, x;
bool flag[500010];
struct node {
	int fl, w; //fl 是记录第几个进入队列的 w为值
	friend bool operator < (const node & a, const node & b) {
		if (a.w != b.w) return a.w < b.w;
		return a.fl > b.fl;
	}
};
priority_queue<node> q;
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	int z = 1; // flag[] 的指针
	int yy = 0; // 记录 op==1 时，是第几个插入的
	for (int i = 1; i <= n; i++) {
		cin >> op;
		if (op == 1) {
			cin >> x;
			q.push({++yy, x});
		} else if (op == 2) {
			for (int j = z; j <= n; j++) {
				if (!flag[j]) {
					cout << j << " ";
					flag[j] = 1;
					z++;
					break;
				}//判断是否在被删除
			}
		} else {
			while (!q.empty()) {
				node nn = q.top();
				if (!flag[nn.fl]) {
					cout << nn.fl << " ";
					flag[nn.fl] = 1;
					break;
				}
				q.pop();
			}
		}
	}
	return 0;
}
```

---

## 作者：xyx404 (赞：2)

## 思路：
先考虑用队列和结构体进行模拟。

把输入的那个数的 $id$ 和值一起放进队列，然后照着题目模拟就可以得出代码。

```cpp
struct node{
	int id;
	int num;
};
queue<node>dl,d;
int main(){
	cin>>n;
	while(n--){
		cin>>op;
		if(op==1){
			int x;cin>>x;
			dl.push({++i,x});
		}
		else if(op==2){
			cout<<dl.front().id<<" ";
			dl.pop();
		}
		else if(op==3){
			queue<node>d;
			int id=0;
			int maxx=-5;
			int cnt=0;
			while(dl.empty()==0){
				node tamp=dl.front();
				dl.pop();
				d.push(tamp);
				if(tamp.num>maxx){
					maxx=tamp.num;
					id=tamp.id;
				}
			}
			while(d.empty()==0){
				node tamp=d.front();
				d.pop();
				if(tamp.id!=id)dl.push(tamp);
				else cout<<tamp.id<<" ";
			}
		}
	}
	return 0;
}


```

提交后发现超时了，考虑怎么优化。

因为 $id$ 是唯一的，所以我们可以使用一个数组把输出过的 $id$ 进行标记，也就是这个 $id$ 表示的数被删除了，然后使用 `priority_queue` 处理操作 $3$，注意要输出最大的没有被删除的最早加入堆的数的 $id$。


## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define itn int
#define ull unsigned long long
int n;
int op;
int i;
bool bj[int(5*1e5+10)];
struct node{
	int id;
	int num;
	friend bool operator<(const node &a,const node &b){ 
		return a.num==b.num?a.id>b.id:a.num<b.num; 
	}
};
int last=1;
priority_queue<node>dl;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n;
	while(n--){
		cin>>op;
		if(op==1){
			int x;cin>>x;
			dl.push({++i,x});
		}
		else if(op==2){
			while(1){
				if(!bj[last]){
					cout<<last<<" ";
					bj[last]=1;
					break;
				}
				last++;
			}
		}
		else if(op==3){
			while(bj[dl.top().id])dl.pop();
			cout<<dl.top().id<<" ";
			bj[dl.top().id]=1;
			dl.pop();
		}
	}
	return 0;
}


```

---

## 作者：A_Bit_Cold (赞：2)

这是一个堆操作的模板题，但是需要一些思维。

对于一个堆，显然每一个元素都需要有两个值对应，$x$ 与 $id$，$x$ 表示该元素的数值，$id$ 表示该元素进入堆的编号。

对于堆的排序规则，显然是按 $x$ 从小到大排，如果 $x$ 相等，则按 $id$ 从大到小排。

为什么要这样排呢？主要是因为 $op=3$ 时的输出，因为是按照 $x$ 从小到大排，所以出堆的一定是最大值，但是有可能这个值已经出过堆了，所以用 $v$ 记录一下出堆状况，若最大值相同，那出来的 $id$ 也一定是最小值，因为 $id$ 时从大到小拍的，在 $x$ 相同的情况下，$id$ 越小也就越在上面，然后将现在的 $id$ 记为已出堆。

接下来解决其他两个 $op$ 值：

- $op=1$ 直接将 $x$ 与 $id$ 入堆即可。

- $op=2$ 由于是查询最小入堆的，则只需让 $id$ 从 $1$ 遍历到目前没出堆的编号最小值即可，并将现在的 $id$ 记为已出堆。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int a[N],b[N],v[N];
struct node {
	int x,id;
};
bool operator <(const node &a,const node &b) {
	if(a.x!=b.x) return a.x<b.x;
	return a.id>b.id;
}
priority_queue <node> q;
int main() {
	//freopen("heap.in","r",stdin);
	//freopen("heap.out","w",stdout);
	int Q,op,pointer=1,x,s=0;
	cin>>Q;
	while(Q--) {
		cin>>op;
		if(op==1) {
			cin>>x;
			q.push((node) {
				x,++s
			});
		}
		else if(op==2) {
			while(v[pointer]) pointer++;
			cout<<pointer<<" ",v[pointer++]=true;
		}
		else {
			node tmp=q.top();
			while(v[tmp.id]) q.pop(),tmp=q.top();
			cout<<tmp.id<<" ",v[tmp.id]=1,q.pop();
		}
	}
	return 0;
}
```


---

## 作者：lzy120406 (赞：1)

## [原题](https://codeforces.com/problemset/problem/1468/C)
我们需要处理三种类型的查询：

类型 1：一个新顾客进入餐厅，并记录其预计消费金额 $m$。

类型 2：Monocarp 服务最早进入餐厅的顾客。

类型 3：Polycarp 服务预计消费金额最大的顾客（如果有多个，选择**最早**进入的）。

## 思路
对于类型 2，我们可以利用队列**先进先出**的性质，维护一个队列。

对于类型 3，我们可以使用一个**优先队列**（堆）来维护 Polycarp 服务的顺序（按消费金额从大到小排序，金额相同则按进入顺序排序）。

对于类型 1 查询，将顾客信息同时加入队列和优先队列。

对于类型 2 查询，从队列中取出最早进入的顾客。

对于类型 3 查询，从优先队列中取出消费金额最大的顾客。

但还没完。

使用一个标记数组记录顾客是否已经被服务，避免重复服务。

具体细节看代码。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
struct Customer {
	int id;
	int money;
	bool operator<(const Customer& other) const {
		if (money == other.money) {
			return id > other.id; // 金额相同，按 id 升序
		}
		return money < other.money; // 金额降序
	}
};
queue<int> monoQueue; // Monocarp 的队列
priority_queue<Customer> polyQueue; // Polycarp 的优先队列
bool served[500005]; // 标记顾客是否被服务
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int q;
	cin >> q;
	int customerId = 0;
	while (q--) {
		int type;
		cin >> type;
		if (type == 1) {
			int m;
			cin >> m;
			customerId++;
			monoQueue.push(customerId);
			polyQueue.push({customerId, m});
		} else if (type == 2) {
			while (!monoQueue.empty() && served[monoQueue.front()]) {
				monoQueue.pop(); // 跳过已服务的顾客
			}
			if (!monoQueue.empty()) {
				int id = monoQueue.front();
				monoQueue.pop();
				served[id] = true;
				cout << id << " ";
			}
		} else if (type == 3) {
			while (!polyQueue.empty() && served[polyQueue.top().id]) {
				polyQueue.pop(); // 跳过已服务的顾客
			}
			if (!polyQueue.empty()) {
				int id = polyQueue.top().id;
				polyQueue.pop();
				served[id] = true;
				cout << id << " ";
			}
		}
	}
	cout << '\n';
	return 0;
}
```
时间复杂度 $ \mathcal{O}(q \log n) $，可以通过本题。

---

## 作者：wangkelin123 (赞：1)

~~这题目看着很简单，其实**一点也不难**，但我还是调了很久……~~
## 题目大意
- $op=1$，序列中插入 $m$。
- $op=2$，删除序列中最先插入的那个数，并输出那个数的序号。
- $op=3$，删除序列中最大的那个数，并输出那个数的序号。

**注意：$1 \le N,M \le 5\times10^5$！**
## 思路
题目好像只用了一个序列（数组），但却有两种排序方法。我们不可能每次都更换关键词排序（那时间肯定会炸！），所以需要用两个序列交替使用。

经过~~多重考虑~~，在本题目中要用一个 bool 数组记录编号 $i$ 是否被用过，因为值可能相同，但序号一定不同；一个优先队列-大根堆，这样可以实时进行排序。

- $op=1$，直接在中插入 $m$，但考虑到最后要输出的是序号，所以需建立一个 struct，并进行重载小于号。
```
struct Node{
	int id,val;
	bool operator<(const Node &_)const{
		if(val==_.val) return id>_.id;
		return val<_.val;
	}
};
priority_queue<Node,vector<Node> > q;
```
**注意：优先队列使用的大小于号与最终排序结果相反，比如大根堆就要用小于号。**
- $op=2$，可能有一些数在优先队列中已经删除，但在 bool 数组中还没有。所以要先从上次记录过的位置往下“扫一遍” bool 数组（其实这个地方总共最多也就执行 $N$ 次），直到找到没有记录过的序号，输出，再标记。当然，用来遍历的是全局变量 $t$。
```
int t=0;//全局

while(vis[++t]);
cout<<t<<' ';
vis[t]=true;
```
- $op=3$，同理，也需先遍历优先队列，删除在 bool 数组中已经删除了的值。接着便是输出队首然后再 pop。
```
while(vis[q.top().id]) q.pop();
cout<<q.top().id<<' ';
vis[q.top().id]=true;
q.pop();
```
## 组合起来就是……
```
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
int m,n,a[N],op,tot,t;
bool vis[N];
struct Node{
	int id,val;
	bool operator<(const Node &_)const{
		if(val==_.val) return id>_.id;
		return val<_.val;
	}
};
priority_queue<Node,vector<Node> > q;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>op;
		if(op==1){
			cin>>m;
			q.push({++tot,m});
		}else if(op==2){
			while(vis[++t]);
			cout<<t<<' ';
			vis[t]=true;
		}else{
			while(vis[q.top().id]){
				q.pop();
			}
			cout<<q.top().id<<' ';
			vis[q.top().id]=true;
			q.pop();
		}
	}
	return 0;
}
```
[AC！](https://codeforces.com/contest/1468/submission/299757056)

---

## 作者：yekc2010 (赞：1)

## 思路。
首先说下这道题的题意：有一个序列，对于这个序列有三种操作。

1. $op = 1$，向序列插入一个数。
2. $op = 2$，删除序列最早插入的数，并输出它是第几个插入。
3. $op = 3$，删除序列最大的数，输出它是第几个插入的。

在 $op = 2$ 时，它是顺序输入输出的，可知要用队列和结构体。

结构体用于存放数和数第几个插入的。


```cpp
struct node{
	int x,time;
};
queue<node>q;
```

然后 $op = 3$ 时，要找出序列中最大的数，所以我们又要用到优先队列。

优先队列结构体的定义。

```cpp
struct node{
	int x,time;
	friend bool operator<(const node &x,const node &y){ 
	    if(x.x!=y.x) return x.x<y.x;//先判断数的大小 
	    else return x.time>y.time;//如果数一样大再判断它第几个插入的 
    }
};
priority_queue<node>q;
```

再就要想两个队列不相通，要是删除了这边队列的数，另一个队列的数不会变，所以用一个数组判断这个数有没有找过。
```cpp
bool b[500010];
```

最后结合起来。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
int op,n,m;
bool b[500010];//判断是否找过 
struct node1{
	int x,time;
};
struct node2{
	int x,time;
	friend bool operator<(const node2 &x,const node2 &y){ 
	    if(x.x!=y.x) return x.x<y.x;//先判断数的大小 
	    else return x.time>y.time;//如果数一样大再判断它第几个插入的 
    }
};
queue<node1>q1;
priority_queue<node2>q2;
int main(){
	IOS
	cin>>n;
	int i=1;//第几个插入的数 
	while(n--){
		cin>>op;
		if(op==1){
			cin>>m;//插入的数 
			node1 t;
			node2 t1;
			t.x=m;t.time=i;//队列的 
			t1.x=m,t1.time=i;//优先队列的 
			q1.push(t);
			q2.push(t1);
			i++; 
		}
		else if(op==2){
			while(1){//一直找，直到找到没弹出过的 
				node1 t=q1.front();
			    q1.pop(); 
			    if(!b[t.time]/*没标记过的*/){
				   cout<<t.time<<" ";//输出它是第几个插入的 
				   b[t.time]=1;//标记 
				   break;//结束循环 
			    }
			    //如果遇到标记过的就弹出了 
			}
		}
		else {
			while(1){//跟op==2差不多，只是换了个队列 
				node2 t=q2.top();
				q2.pop();
				if(!b[t.time]){
					cout<<t.time<<" ";
					b[t.time]=1;
					break;
				} 
			}
		}
	}
	return 0;
} 
```

---

## 作者：2021sunzishan (赞：1)

就是可爱的延迟操作。

## 思路
如果不看操作 $2$，那就是一个非常基础的大根堆操作。每次把元素的值和序号放进堆就好了。

那么如果加上操作 $2$ 呢？把序号最小的删掉，它还在大根堆里，删除它非常麻烦。所以我们就索性不删它，开一个标记数组记录它是否被删除，这题算是了了。

以上就是本题的思路了，如果还是不懂，就看看代码吧。

**切勿抄袭！！！**
## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 500005
bool vis[N];
struct node{
	int id,s;
	bool operator<(const node &a)const{//重载运算符
		if(s!=a.s) 
			return s<a.s;
		return id>a.id;
	}
};
priority_queue<node,vector<node>,less<node> >q;//大根堆
inline int read(){
	int a=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		a=a*10+c-'0';
		c=getchar();
	}
	return a*f;
}
queue<int>q1;//存序号
int n;
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	n=read();
	int cnt=0;
	while(n--){
		int k=read();
		if(k==1){
			node ls;
			ls.id=++cnt,ls.s=read();
			q.push(ls),q1.push(cnt);
		}
		if(k==2){
			while(vis[q1.front()])//没有被删
				q1.pop();
			vis[q1.front()]=1;
			printf("%d ",q1.front());
			q1.pop();
		}
		if(k==3){
			while(vis[q.top().id])q.pop();
			vis[q.top().id]=1;
			printf("%d ",q.top().id);
			q.pop();
		}
	}
	return 0;
}
```

完结~

---

## 作者：KSToki (赞：1)

这题用一个堆（priority_queue）即可，并不需要用到队列（queue）。

操作 $1$：直接将 $m$ 和编号组合成 pair 扔进大根堆即可，由于要求数字相同先删编号最小的，把编号取成相反数更好处理。

操作 $2$：增加一个变量 $now$，记录当前该删第几个和一个 $vis$ 数组，$vis[i]$ 记录编号为 $i$ 的数是否已被删除，每次操作循环向后找第一个没有被标记的位置并打上标记，加入答案数组。

操作 $3$：循环判断堆顶元素是否已被删除（看编号对应的 $vis$），如果已被删除则弹出，继续寻找。当找到一个未被删除的元素时，取出，在 $vis$ 数组中打上标记，加入答案数组。

每个数最多只会进堆一次、出堆一次，且 $now$ 最多只会遍历一遍 $vis$ 数组，复杂度为 $O(nlogn)$，可以通过。

代码~~忽略宏定义~~：
```cpp
#include<bits/stdc++.h>
#define R register
#define I inline
#define ll long long
#define ull unsigned long long
#define LL __int128
#define db double
using namespace std;
#define pii pair<int,int>
#define mp(x,y) make_pair(x,y)
#define piii pair<pair<int,int>,int>
#define mp3(x,y,z) make_pair(make_pair(x,y),z)
#define fi first.first
#define se first.second
#define th second
#define putint(x) printf("%d\n",x)
#define putll(x) printf("%lld\n",x)
#define putull(x) printf("%llu\n",x)
#define lowbit(x) ((x)&(-(x)))
#define inf (0x7fffffff)
#define INF (1e18)
inline int read()
{
	char ch=getchar();
	int res=0,flag=1;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			flag=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		res=res*10+ch-'0';
		ch=getchar();
	}
	return res*flag;
}
int n,op,x,ans[500001],now=1,cnt;
bool vis[500001];
priority_queue< pii >q;
int main()
{
	n=read();
	while(n--)
	{
		op=read();
		if(op==1)
		{
			x=read();
			++cnt;
			q.push(mp(x,-cnt));
		}
		else if(op==2)
		{
			while(vis[now])
				++now;
			vis[now]=1;
			ans[++ans[0]]=now;
		}
		else
		{
			while(vis[-q.top().second])
				q.pop();
			vis[-q.top().second]=1;
			ans[++ans[0]]=-q.top().second;
			q.pop();
		}
	}
	for(R int i=1;i<=ans[0];++i)
		printf("%d ",ans[i]);
    return 0;
}
```


---

## 作者：SuperBeetle (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1468C)

这道题一眼过去，模拟 + 打标记，不能用 sort，每次排序时间复杂度太高，用堆与重载运算符即可，话不多说，上代码。

```cpp
#include <bits/stdc++.h>
#define IAKIOI ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
#define UPB(x, y, z) upper_bound(x + 1, x + y + 1, z) - x
#define LWB(x, y, z) lower_bound(x + 1, x + y + 1, z) - x
#define rep(i, l, r) for (int i = l; i <= r; i++)
#define pre(i, l, r) for (int i = r; i >= l; i--)
#define UNQIUE(x, y) unqiue(x + 1, x + y + 1)
#define SORT(x, y) sort(x + 1,x + y + 1)
#define pf push_front 
#define pb push_back 
#define IT iterator
#define endl '\n';

//奇奇怪怪的码风

const int N = 5e5 + 5, INF = 0x3f3f3f3f;
const double ecnts = 1e-6;

#define int long long

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef double db;

void read(int &x) { //快读
	int f = 1, y = 0;
	char c = getchar();
	while (!isdigit(c)) {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (isdigit(c)) {
		y = y * 10 + c - '0';
		c = getchar();
	}
	x = y * f;
}

void write(int x) { //快写
	if(x < 0) putchar('-'), x = -x;
	if(x > 9) write(x / 10);
	putchar(x % 10 + '0');
}

inline int max(int x, int y) {return x > y ? x : y;}
inline int min(int x, int y) {return x < y ? x : y;}

inline void swap(int &x, int &y) {int t = x;x = y, y = t;}
inline int pow(int x, int y) {
	int ans = 1;
	while (y) {
		if (y & 1) ans *= x;
		x *= x, y = y >> 1;
	}
	return ans;
}

struct people { //为3操作做准备
	int money, id;
	people(int r, int c) : money(r), id(c) {}
	bool operator > (const people& x) const{ //先按先排序，若相等，编号小在上，钱大在上
		return money == x.money ? id > x.id : money < x.money;
	}
};

int n;
priority_queue<people, vector<people>, greater<people> > q; //Polycarp的服务顺序
priority_queue<int, vector<int>, greater<int> > s; //记2操作的编号Monocarp的服务顺序
int mp[N]; //记录走或没走

void solve() {
	cin >> n;
	int id = 0;
	while (n--) {
		int op;
		cin >> op;
		if (op == 1) { //操作1
			int x;
			cin >> x;
			id++;
			q.push(people(x, id));//将编号与钱加入
			s.push(id); //将id加入
		}
		else if (op == 2) { //操作2
			while (mp[s.top()]) s.pop(); //走了的人标记了，就出堆
			cout << s.top() << ' '; //输出
			mp[s.top()] = 1;//走了就标记
			s.pop();
		}
		else { //操作3同上
			while (mp[q.top().id]) q.pop();
			cout << q.top().id << ' ';
			mp[q.top().id] = 1;
			q.pop();
		}
	}
}

signed main() {
	IAKIOI;
	int t = 1;
//	cin >> t;
	while (t--) {
		solve();
	}
}
```

---

## 作者：wawatime1 (赞：0)

### 题目分析
本题需要处理三种操作：

1.顾客到来，记录其预计消费金额。

2.按顾客先来顺序服务，即服务最早进入的顾客。

3.按预计消费金额最高原则服务顾客，若金额相同则选择先来的顾客。

### 解题思路
使用**队列**来实现先来先服务的逻辑。使用优先队列实现按预计消费金额最高服务的逻辑。通过重载 $<$ 运算符，使得优先队列按金额从大到小排序，金额相同则按顾客编号从小到大排序。用一个数组 $ f $ 来标记顾客是否已被服务。

- 若 $op = 1$，顾客到来时，给顾客分配一个递增的编号，将顾客的编号和预计消费金额封装成结构体，同时加入队列和优先队列。

- 若 $op = 2$，从队列中取出队首元素，若该元素已被服务则跳过，直到找到未被服务的顾客。输出该顾客编号，标记其已被服务，然后将其从队列中移除。

- 若 $op = 3$，从优先队列中取出队首元素，若该元素已被服务则跳过，直到找到未被服务的顾客。输出该顾客编号，标记其已被服务，然后将其从优先队列中移除。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

int n;
int op, x;
struct node {
    int id, v;
};
// 重载小于运算符，用于优先队列排序
bool operator < (const node& x, const node& y) {
    if (x.v == y.v)
        return x.id > y.id;
    return x.v < y.v;
}
queue <node> q;
priority_queue <node> pq;
int l;
int f[500010];

int main () {
    scanf ("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf ("%d", &op);
        if (op == 1) {
            scanf ("%d", &x);
            l++;
            q.push({l, x});
            pq.push({l, x});
        }
        if (op == 2) {
            while (f[q.front().id] == 1) q.pop();
            printf("%d ", q.front().id);
            f[q.front().id] = 1;
            q.pop();
        }
        if (op == 3) {
            while (f[pq.top().id] == 1) pq.pop();
            printf("%d ", pq.top().id);
            f[pq.top().id] = 1;
            pq.pop();
        }
    }
    return 0;
}
```

---

## 作者：I_Love_DS (赞：0)

我们需要一个能维护插入一个元素，删除一个元素，找最值的数据结构。

所以 STL 中的 `set` 当然是最优选啦！

```cpp
#include <bits/stdc++.h>

using namespace std;

int q;

set <pair <int, int>> s1, s2;

void solve() {
	int cnt = 0;
	scanf("%d", &q);
	while (q--) {
		int op, x;
		scanf("%d", &op);
		if (op == 1) {
			scanf("%d", &x);
			++cnt;
			s1.insert({cnt, x});
			s2.insert({-x, cnt}); // 方便找最小
		} else if (op == 2) {
			pair <int, int> x = *s1.begin();
			//cerr << x.second << endl;
			printf("%d ", x.first);
			s1.erase(s1.begin());
			x.second = -x.second;
			swap(x.first, x.second);
			s2.erase(x);
            // 两边都要删
		} else {
			pair <int, int> x = *s2.begin();
			printf("%d ", x.second);
			s2.erase(s2.begin());
			x.first = -x.first;
			swap(x.first, x.second);
			s1.erase(x);
		}
	}
	printf("\n");
}

int main() {
	solve();
	return 0;
}
```

---

## 作者：Michael1234 (赞：0)

- 本题可以使用**数据结构**构建代码

- 首先设置一个结构体：$node$，$node$ 用来储存插入序列的数的值和插入顺序。

- 其次设置 $dlt$ 数组，用于记录这个数是否已被删除。

- **操作一：** 将这个数的值与插入顺序组合并分别推入队列和优先队列。

- **操作二：** 在队列中查找，如果队首已被删除，将其推出队列，否则将其插入顺序输出，并从队列和标记数组删除。

- **操作三：** 在优先队列中查找，如果队首已被删除，将其推出优先队列，否则将其插入顺序输出，并从优先队列和标记数组删除。

- 在使用优先队列时，需要重载运载符 $<$，排序顺序为：按数值大小排列，在数值相等时，按插入顺序进行排列。

## CODE

~~~cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=5e5+5;
int t,op,m,cnt;
bool dlt[N];//该数是否已被删除
struct node
{
	int num,id;
	friend/*在结构体内调用两个数需加friend*/ bool operator <(node a,node b)
	{
		if(a.num==b.num)//数值若相等
		{
			return a.id>b.id;//按顺序排列
		}
		return a.num<b.num;//数值不相等直接排列
	}//重载运算符,先队列会用到小于号
}n;
priority_queue<node>p;//排大小
queue<node>q;//排顺序
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin>>t;
	while(t--)
	{
		cin>>op;
		if(op==1)//操作一
		{
			cin>>m;
			cnt++;
			n.num=m;//记录数值
			n.id=cnt;//记录 顺序
			q.push(n);//推入队列
			p.push(n);//推入优先队列
		}
		else if(op==2)//操作二
		{
			while(dlt[q.front().id])//已被删除
			{
				q.pop();//推出
			}
			cout<<q.front().id<<" ";//剩下中最先进入序列的数
			dlt[q.front().id]=true;//标记删除
			q.pop();//推出
			
		}
		else
		{
			while(dlt[p.top().id])//已被删除
			{
				p.pop();//推出
			}
			cout<<p.top().id<<" ";//剩下中最大的数
			dlt[p.top().id]=true;//标记删除
			p.pop();//推出
		}
	}
	return 0;
}
~~~

[也是凭一己之力最优解第二](https://www.luogu.com.cn/record/list?pid=CF1468C&orderBy=1&status=&page=1)

---

## 作者：zibenlun (赞：0)

# 优先队列与动态数组！

首先我们看到了第三种操作，需要我们输出最大的数的最早的插入位置。最大我们不免想到可以用优先队列也就是堆，最早又可以想到动态数组 vector，所以我们就可以得出两者相结合的方法完成第三种操作。

之后第二种操作就显得简单了许多，大家都知道队列的特点是先进先出，正好可以做到把先插入的先删除。

# 十分详细的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
queue<int> q1;
priority_queue<int> q2;
vector<int> v[1000005];
int a[1000005],vis[1000005],cnt;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		int op;
		cin>>op;
		if(op==1) {
			int m;
			cin>>m;
			a[++cnt]=m;
			q1.push(cnt);
			q2.push(m);
			v[m].push_back(cnt);
			//存储所有要用到的数据 
		}
		else if(op==2) {
			while(vis[q1.front()]) q1.pop();
			//删除已经使用过的数据 
			vis[q1.front()]=1;
			cout<<q1.front()<<" ";
			q1.pop();
		}
		else{
			while(vis[v[q2.top()][0]]) v[q2.top()].erase(v[q2.top()].begin()),q2.pop();
			//对于一个值找到他最早的插入时间，依然将使用过的先删除 
			vis[v[q2.top()][0]]=1;
			cout<<v[q2.top()][0]<<" ";
			v[q2.top()].erase(v[q2.top()].begin());
			//vector的erase函数中填入的是元素地址 
			q2.pop();
		}
	} 
	return 0;
}
```


---

## 作者：hzoi_liuchang (赞：0)

## 分析
题目大意：你需要维护以下三种操作

$1\ m$：加入一个价值为 $m$ 的数，第 $i$ 个加入的数的标号为 $i$

$2$：询问剩下的数中标号最小的数的标号并将该数删除

$3$：询问剩下的数中价值最大的数的标号并将该数删除，如果有多个价值最大的输出标号最小的

我们开两个堆，一个按照标号从小到大排序，另一个按照价值从大到小排序

每次取出堆顶的元素并给标号打标记即可
## 代码
``` cpp
#include<cstdio>
#include<algorithm>
#include<queue>
#define rg register
inline int read(){
	rg int x=0,fh=1;
	rg char ch=getchar();
	while(ch<'0' || ch>'9'){
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(ch>='0' && ch<='9'){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*fh;
}
const int maxn=1e6+5;
struct asd{
	int id,tim;
	asd(){}
	asd(rg int aa,rg int bb){
		id=aa,tim=bb;
	}
	bool operator < (const asd& A)const{
		return tim>A.tim;
	}
};
struct jie{
	int id,val;
	jie(){}
	jie(rg int aa,rg int bb){
		id=aa,val=bb;
	}
	bool operator < (const jie& A)const{
		if(val==A.val) return id>A.id;
		return val<A.val;
	}
};
bool vis[maxn];
std::priority_queue<asd> q1;
std::priority_queue<jie> q2;
int q;
int main(){
	q=read();
	rg int aa,bb,cnt=0;
	for(rg int i=1;i<=q;i++){
		aa=read();
		if(aa==1){
			cnt++;
			bb=read();
			q1.push(asd(cnt,i));
			q2.push(jie(cnt,bb));
		} else if(aa==2){
			while(!q1.empty() && vis[q1.top().id]) q1.pop();
			printf("%d ",q1.top().id);
			vis[q1.top().id]=1;
			q1.pop();
		} else {
			while(!q2.empty() && vis[q2.top().id]) q2.pop();
			printf("%d ",q2.top().id);
			vis[q2.top().id]=1;
			q2.pop();
		}
	}
	printf("\n");
	return 0;	
}
```

---

