# チーム戦 (Team Contest)

## 题目描述

# [JOISC 2022 Day2] 团队竞技

## 题目背景

JOISC 2022 D2T3


JOI 大学有 $N$ 只海狸，他们都参与竞技编程。每只海狸有三项能力值：思考值，行动值和运气值。如果一个能力值很大，意味着他这项能力比较强大。对于第 $i~(i\in[1,N])$ 只海狸，他的思考值为 $X_i$，行动值为 $Y_i$，运气值为 $Z_i$。

今年 JOI 大学的海狸们将参与一场团体竞技编程，一支队伍由三名队员组成。Bitaro 是 JOI 大学的教练，由于团队合作很重要，Bitaro 决定从 $N$ 只海狸中选出三只海狸组成队伍，这三只海狸要满足以下条件：

**条件**：每个成员都有自己的优势，这意味着每个成员都有一项能力值严格大于其他两人的对应能力值。

在所有符合条件的组队中，Bitaro 想要选一个总能力最强的队伍，一个队伍的总能力定义为：三人最大思考值，三人最大行动值和三人最大运气值之和。

请你求出，是否存在一个符合条件的组队，如果是，计算队伍总能力可能的最大值。

## 说明/提示

**【样例解释 #1】**

由海狸 $1,4,5$ 组成的队伍符合条件，因为：

1. 海狸 $1$ 的优势是运气。
2. 海狸 $4$ 的优势是行动。
3. 海狸 $5$ 的优势是思考。

总能力值为：$5+4+4=13$。

可以证明这是符合条件的组队中，总能力值最高的队伍。

注意如果选择海狸 $1,3,5$，总能力值将达到 $15$，但是这会导致海狸 $1$ 没有特长。

这组样例满足所有子任务的限制。

**【样例解释 #2】**

最优组队为：海狸 $2,3,4$。

这组样例满足所有子任务的限制。

**【样例解释 #3】**

任何组队方式都会导致队员没有特长，不存在符合条件的组队。

这组样例满足所有子任务的限制。


对于所有数据，满足：

- $3\leq N\leq 150000$。
- $1\leq X_i,Y_i,Z_i\leq 10^8$ $(1\leq i\leq N)$。

详细子任务附加限制及分值如下表所示：

|子任务编号|附加限制|分值|
|:-:|:-:|:-:|
|$1$|$N\leq 300$|$8$|
|$2$|$N\leq 4000$|$29$|
|$3$|$X_i,Y_i,Z_i\leq 5$ $(i\in[1,N])$|$9$|
|$4$|$X_i,Y_i,Z_i\leq 20$ $(i\in[1,N])$|$9$|
|$5$|$X_i,Y_i,Z_i\leq 300$ $(i\in[1,N])$|$9$|
|$6$|$X_i,Y_i,Z_i\leq 4000$ $(i\in[1,N])$|$9$|
|$7$|无附加限制|$27$|

# 题解

## 作者：yr409892525 (赞：2)

## [チーム戦 (Team Contest)](https://www.luogu.com.cn/problem/AT_joigsc2022_c)  

我们首先使用优先队列，将所有人中能力中最大的 $x,y,z$ 找出来，因为其中一个人，它必是那一项的第一，但题目中说要严格大于，就只要找到一对满足条件的数，就输出和。  
### 条件
- 如果这个人在之前就被排除，就不行，使用 $vis$ 数组标记。
- 如果自己的特长和其余两个人的这一项相等，就不行，标记 $vis$。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1500005;
int n;
int x[N];
int y[N];
int z[N];
struct code{
	int k,id;
	bool operator <(const code &x) const{
		return k<x.k;
	}
};
priority_queue<code> px,py,pz;
bool v[N];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x[i]>>y[i]>>z[i];
		px.push({x[i],i});
		py.push({y[i],i});
		pz.push({z[i],i});
	}
	while(!px.empty() && !py.empty() && !pz.empty()){
		code a=px.top();
		code b=py.top();
		code c=pz.top();
		if(v[a.id]){ //a.id 项之前有没有被排除
			px.pop();
			continue;
		}
		if(v[b.id]){ //b.id 项之前有没有被排除
			py.pop();
			continue;
		}
		if(v[c.id]){ //c.id 项之前有没有被排除
			pz.pop();
			continue;
		}
		if(x[b.id]==a.k){  //b是否和a相同
			v[b.id]=1;
			py.pop();
			continue;
		}
		if(x[c.id]==a.k){  //c是否和a相同
			v[c.id]=1;
			pz.pop();
			continue;
		}
		if(y[a.id]==b.k){  //a是否和b相同
			v[a.id]=1;
			px.pop();
			continue;
		}
		if(y[c.id]==b.k){  //c是否和b相同
			v[c.id]=1;
			pz.pop();
			continue;
		}
		if(z[a.id]==c.k){  //a是否和c相同
			v[a.id]=1;
			px.pop();
			continue;
		}
		if(z[b.id]==c.k){  //b是否和c相同
			v[b.id]=1;
			py.pop();
			continue;
		}
		cout<<a.k+b.k+c.k<<"\n";
		return 0;
	}
	cout<<-1<<"\n";
	return 0;
}
```

---

## 作者：quanguanyu (赞：1)

## 思路


根据此题，不难想到是通过模拟来得到最大的值。

由于具有单调性，仔细一想，也不难想到可以用优先队列来维护最大值并模拟出合法的最大值。

那么什么时候它不合法呢？

如果，有一个人，任意两个值都是最大值，那么我们并不会选他。

比如说第一个人思考值和行动值都是最好的，我们不能用他，因为每个技能最好的只能有 1 个人。

如果，有一个人他思考值是最好的，但他的行动值与现在行动值最大值一样，我们也不会选他。

还有就是我们要拿一个 vis 来标记那些我们是不要的。

---

## code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,a[150010],b[150010],c[150010];
struct node{
	int d,id;
	bool operator < (const node&other) const {
		return d<other.d;
	}
};
priority_queue<node>x,y,z;
int read(){
	char ch=getchar();
	int x=0;
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x;
}
bool vis[150010];
signed main() {
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read(),b[i]=read(),c[i]=read();
		x.push((node){a[i],i});
		y.push((node){b[i],i});
		z.push((node){c[i],i});
	}
	while(x.size()>=3&&y.size()>=3&&z.size()>=3){//当人数不大于三人时，不合法
		node xx=x.top(),yy=y.top(),zz=z.top();
		if(vis[xx.id]){
			x.pop();
			continue;
		}
		if(vis[yy.id]){
			y.pop();
			continue;
		}
		if(vis[zz.id]){
			z.pop();
			continue;
		}
		if(xx.d==a[yy.id]){
			y.pop();
			vis[yy.id]=1;
			continue;
		}
		if(xx.d==a[zz.id]){
			z.pop();
			vis[zz.id]=1;
			continue;
		}
		if(yy.d==b[xx.id]){
			x.pop();
			vis[xx.id]=1;
			continue;
		}
		if(yy.d==b[zz.id]){
			z.pop();
			vis[zz.id]=1;
			continue;
		}
		if(zz.d==c[xx.id]){
			x.pop();
			vis[xx.id]=1;
			continue;
		}
		if(zz.d==c[yy.id]){
			y.pop();
			vis[yy.id]=1;
			continue;
		}
		cout<<xx.d+yy.d+zz.d;
		return 0;
	}
	cout<<-1;
	return 0;
}
```

---

## 作者：sieve (赞：1)

# 题解：[チーム戦 (Team Contest)](https://www.luogu.com.cn/problem/AT_joigsc2022_c)

## 思路

我们这题直接贪心即可。

首先我们写一个结构体，一个存能力值（不管它是哪个），一个存位置，然后写一个重载运算符，维护优先队列中取出的为结构体的值最大。

然后我们就将三个能力值分别丢进三个优先队列里面，记得把下表也丢进去。

循环的时候只要三个优先队列里面都有值，就可以继续，否则停止。

我们分别取出三个队列的顶部结构体，如果这种能力已经出现过了，直接将这个顶部删除，然后循环下一个。

对于其他的不可行情况，就是这个能力的值已经有别的海狸有过了，那么，我们也把这个顶部删除，循环下一个。

如果所有的不可行情况都通过了，也就是当前方案可行，直接输出三个顶部的和，然后退出程序。

对于无解情况，一定没有退出过程序，那么，我们在循环外面再输出$-1$。

## Code:


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct no{
	int val,id;
	bool operator <(const no &D) const 
	{
		return val<D.val;
	}
};
int a[1000005],b[1000005],c[1000005];
priority_queue<no> pa,pb,pc;
bool vis[1000005];
int n;
signed main()
{
	cin>>n;
	for(int i=1;i<=n;++i)
	{
		cin>>a[i]>>b[i]>>c[i];
		pa.push(no{a[i],i});
		pb.push(no{b[i],i});
		pc.push(no{c[i],i});
	}
	while(!pa.empty()&&!pb.empty()&&!pc.empty())
	{
		no aa=pa.top(),bb=pb.top(),cc=pc.top();
		if(vis[aa.id]==1)
		{
			pa.pop();
			continue;
		}
		if(vis[bb.id]==1)
		{
			pb.pop();
			continue;
		}
		if(vis[cc.id]==1)
		{
			pc.pop();
			continue;
		}
		if(a[bb.id]==aa.val)
		{
			vis[bb.id]=1;
			pb.pop();
			continue;
		}
		if(a[cc.id]==aa.val)
		{
			vis[cc.id]=1;
			pc.pop();
			continue;
		}
		if(b[aa.id]==bb.val)
		{
			vis[aa.id]=1;
			pa.pop();
			continue;
		}
		if(b[cc.id]==bb.val)
		{
			vis[cc.id]=1;
			pc.pop();
			continue;
		}
		if(a[bb.id]==aa.val)
		{
			vis[bb.id]=1;
			pb.pop();
			continue;
		}
		if(c[bb.id]==cc.val)
		{
			vis[bb.id]=1;
			pb.pop();
			continue;
		}
		if(c[aa.id]==cc.val)
		{
			vis[aa.id]=1;
			pa.pop();
			continue;
		}
		cout<<aa.val+bb.val+cc.val;
		return 0;
	}
	cout<<-1;
	return 0;
}
```

---

## 作者：2b2b2bbb (赞：0)

# 思路
我们知道想要找到最优的答案那么尽量就要我们的每一线的能力最大。                            
那么我们就可以用优先队列来维护让我们的能力是尽可能大的，但是这道题还有几个限制条件。                
首先对于每一次选出的海狸我们都要保证这只海狸的最大能力值严格大于另外两只。                   
那么我们就要思考几种情况。首先如果有只海狸的另外的能力等于了我们原本定好的那只海狸的能力那么这只海狸就不能选。                   
因为我们每次找的肯定是当前能力值最优的当有一只海狸的并不是最有能力的能力都是第 $1$ 了那么如果我们选他就必定会满足不了条件。                     
如果所有条件都满足了。那么我们就要输出这三种能力的总和并不要再找了毕竟已经是最优了。               
如果找不到那么就要输出 $-1$。                 
# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
struct pi{
	int val,id;
	bool operator<(const pi x) const{
		return val < x.val;
	}
};
priority_queue<pi> x,y,z;
bool vis[150005];
int a[150005],b[150005],c[150005],n;
int main(){
	cin >> n;
	for(int i = 1 ; i <= n ; i ++){
		cin >> a[i] >> b[i] >> c[i];
		x.push({a[i] , i});
		y.push({b[i] , i});
		z.push({c[i] , i});
	}
	while(!x.empty() && !y.empty() && !z.empty()){
		pi xx = x.top();
		pi yy = y.top();
		pi zz = z.top();
		if(vis[xx.id]){
			x.pop();
			continue;
		}
		if(vis[yy.id]){
			y.pop();
			continue;
		}
		if(vis[zz.id]){
			z.pop();
			continue;
		}
		if(a[yy.id] == xx.val){
			vis[yy.id] = true;
			y.pop();
			continue;
		}
		if(a[zz.id] == xx.val){
			vis[zz.id] = true;
			z.pop();
			continue;
		}
		if(b[xx.id] == yy.val){
			vis[xx.id] = true;
			x.pop();
			continue;
		}
		if(b[zz.id] == yy.val){
			vis[zz.id] = true;
			z.pop();
			continue;
		}
		if(c[xx.id] == zz.val){
			vis[xx.id] = true;
			x.pop();
			continue;
		}
		if(c[yy.id] == zz.val){
			vis[yy.id] = true;
			y.pop();
			continue;
		}
		cout << xx.val + yy.val + zz.val;
		return 0;
	}
	cout << -1;
	return 0;
} 
```

---

## 作者：jinfanhao (赞：0)

利用优先队列来维护每个能力的最大值。\
如果当前的最大值都不属于同一只海狸，就输出。\
否则把重复的元素弹出队列。\
如果队列空了还没有找到，说明没有符合要求的组队，输出无解。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=15e4+1;
int n,x[N],y[N],z[N];
bool ok[N];
struct node{
	int key,value;
	bool operator <(const node op) const{
		return value<op.value;
	}
};
priority_queue<node>pq1,pq2,pq3;
signed main(){
	scanf("%lld",&n);
	for(int i=1; i<=n; ++i){
		scanf("%lld%lld%lld",&x[i],&y[i],&z[i]);
		pq1.push({i,x[i]});
		pq2.push({i,y[i]});
		pq3.push({i,z[i]});
	}
	while(pq1.size() && pq2.size() && pq3.size()){
		node now1=pq1.top(),now2=pq2.top(),now3=pq3.top();
		if(ok[now1.key]){
			pq1.pop();
			continue;
		}if(ok[now2.key]){
			pq2.pop();
			continue;
		}if(ok[now3.key]){
			pq3.pop();
			continue;
		}if(x[now2.key]==now1.value){
			ok[now2.key]=true;
			pq2.pop();
			continue;
		}if(x[now3.key]==now1.value){
			ok[now3.key]=true;
			pq3.pop();
			continue;
		}if(y[now1.key]==now2.value){
			ok[now1.key]=true;
			pq1.pop();
			continue;
		}if(y[now3.key]==now2.value){
			ok[now3.key]=true;
			pq3.pop();
			continue;
		}if(z[now1.key]==now3.value){
			ok[now1.key]=true;
			pq1.pop();
			continue;
		}if(z[now2.key]==now3.value){
			ok[now2.key]=true;
			pq2.pop();
			continue;
		}
		printf("%lld",now1.value+now2.value+now3.value);
		return 0;
	}
	printf("-1");
	return 0;
}
```

---

## 作者：Ak_hjc_using (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/AT_joigsc2022_c)
### 思路
考虑贪心。对于每项属性，我们都希望取到最大值，但如果选出的一只海狸有两项或三项属性优势那此方案必定不满足要求。

维护三个优先队列分别维护思考值，行动值和运气值的动态最大值，然后判断是否有选出一只海狸有两项或三项属性优势，若有就标记上并重新选新的最大值，最后把三个值加起来就愉快通过啦！

### 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct node
{
	int val,id;
	bool operator < (const node&D) const 
	{
		return val < D.val;
	}
};
const int N = 1e6 + 1;
int a[N], b[N], c[N];
priority_queue<node> pa, pb, pc;
bool vis[N];
int n;
signed main()
{
	cin >> n;
	for (int i = 1;i <= n;i ++)
	{
		cin >> a[i] >> b[i] >> c[i];
		pa.push( node{a[i], i});
		pb.push( node{b[i], i});
		pc.push( node{c[i], i});
	}
	while (!pa.empty() && !pb.empty() && !pc.empty())
	{
		node aa = pa.top(), bb = pb.top(), cc = pc.top();
		if (vis[aa.id] == true)
		{
			pa.pop();
			continue;
		}
		if (vis[bb.id] == true)
		{
			pb.pop();
			continue;
		}
		if  (vis[cc.id] == true)
		{
			pc.pop();
			continue;
		}
		if (a[bb.id] == aa.val)
		{
			vis[bb.id] = true;
			pb.pop();
			continue;
		}
		if (a[cc.id] == aa.val)
		{
			vis[cc.id] = true;
			pc.pop();
			continue;
		}
		if (b[aa.id] == bb.val)
		{
			vis[aa.id] = true;
			pa.pop();
			continue;
		}
		if (b[cc.id] == bb.val)
		{
			vis[cc.id] = true;
			pc.pop();
			continue;
		}
		if (a[bb.id] == aa.val)
		{
			vis[bb.id] = true;
			pb.pop();
			continue;
		}
		if (c[bb.id] == cc.val)
		{
			vis[bb.id] = true;
			pb.pop();
			continue;
		}
		if (c[aa.id] == cc.val)
		{
			vis[aa.id] = true;
			pa.pop();
			continue;
		}
		cout << aa.val + bb.val + cc.val << endl;
		return 0;
	}
	cout << -1 << endl;
	return 0;
}
```

---

## 作者：sccc_ (赞：0)

## 思路  
一道贪心题。  

我们可以定义一个结构体，存能力值和下标。  

并定义三个优先队列，分别存三个的能力值和当前下标。  

判断以下两点：
- 是否已经在别的优先队列中将队顶下标的元素弹出，也就是之前该下标的元素判断不合法；
- 该元素所在的下标是否在两个队顶出现，如果是，则代表不是每个成员都有一项能力值严格大于其他两人的对应能力值，将队顶元素弹出。

如果某一次循环中，条件全部避开，也就是全部合法，就输出并结束程序。  

如果没有输出，就是不存在符合条件的组队，输出 `-1`。  

注意需要重载运算符，让优先队列中取出的为结构体的值最大。  

## 代码
```c++
#include <bits/stdc++.h>
using namespace std;

const int N = 150005;
int a[N];
int b[N];
int c[N];
bool vis[N];
int n;
 
struct node
{
	int val, id;
	bool operator < (const node & x) const
	{
		return val < x.val;
	}
};
priority_queue<node> QA, QB, QC;

signed main()
{
	cin >> n;
	for (int i = 1; i <= n; i ++)
	{
		cin >> a[i] >> b[i] >> c[i];
		QA.push({a[i], i});
		QB.push({b[i], i});
		QC.push({c[i], i});
	}
	while (!QA.empty() and !QB.empty() and !QC.empty())
	{
		node A = QA.top();
		node B = QB.top();
		node C = QC.top();
		if (vis[A.id])
		{
			QA.pop();
			continue;
		}
		if (vis[B.id])
		{
			QB.pop();
			continue;
		}
		if (vis[C.id])
		{
			QC.pop();
			continue;
		}
		if (a[B.id] == A.val)
		{
			vis[B.id] = 1;
			QB.pop();
			continue;
		}
		if (a[C.id] == A.val)
		{
			vis[C.id] = 1;
			QC.pop();
			continue;
		}
		if (b[A.id] == B.val)
		{
			vis[A.id] = 1;
			QA.pop();
			continue;
		}
		if (b[C.id] == B.val)
		{
			vis[C.id] = 1;
			QC.pop();
			continue;
		}
		if (c[B.id] == C.val)
		{
			vis[B.id] = 1;
			QB.pop();
			continue;
		}
		if (c[A.id] == C.val)
		{
			vis[A.id] = 1;
			QA.pop();
			continue;
		}
		cout << A.val + B.val + C.val << endl;
		return 0;
	}
	cout << -1 << endl;
	return 0;
} 
```

---

## 作者：FReQuenter (赞：0)

# 题意~~简述~~

## 题目背景

JOISC 2022 D2T3

## 题目描述

JOI 大学有 $N$ 只海狸，他们都参与竞技编程。每只海狸有三项能力值：思考值，行动值和运气值。如果一个能力值很大，意味着他这项能力比较强大。对于第 $i~(i\in[1,N])$ 只海狸，他的思考值为 $X_i$，行动值为 $Y_i$，运气值为 $Z_i$。

今年 JOI 大学的海狸们将参与一场团体竞技编程，一支队伍由三名队员组成。Bitaro 是 JOI 大学的教练，由于团队合作很重要，Bitaro 决定从 $N$ 只海狸中选出三只海狸组成队伍，这三只海狸要满足以下条件：

**条件**：每个成员都有自己的优势，这意味着每个成员都有一项能力值严格大于其他两人的对应能力值。

在所有符合条件的组队中，Bitaro 想要选一个总能力最强的队伍，一个队伍的总能力定义为：三人最大思考值，三人最大行动值和三人最大运气值之和。

请你求出，是否存在一个符合条件的组队，如果是，计算队伍总能力可能的最大值。

## 输入格式

第一行一个整数 $N$ 表示海狸数。

接下来 $N$ 行每行三个整数 $X_i,Y_i,Z_i$ 表示海狸的各项能力值。

## 输出格式

一行一个整数，如果不存在符合条件的组队，输出 `-1`，否则输出队伍总能力的最大值。

## 样例 #1

### 样例输入 #1

```
5
3 1 4
2 3 1
1 5 5
4 4 2
5 2 3
```

### 样例输出 #1

```
13
```

## 样例 #2

### 样例输入 #2

```
8
1 1 1
1 1 5
1 5 1
5 1 1
1 5 5
5 1 5
5 5 1
5 5 5
```

### 样例输出 #2

```
15
```

## 样例 #3

### 样例输入 #3

```
4
1 2 3
1 2 3
1 2 3
1 2 3
```

### 样例输出 #3

```
-1
```

## 提示

**【样例解释 #1】**

由海狸 $1,4,5$ 组成的队伍符合条件，因为：

1. 海狸 $1$ 的优势是运气。
2. 海狸 $4$ 的优势是行动。
3. 海狸 $5$ 的优势是思考。

总能力值为：$5+4+4=13$。

可以证明这是符合条件的组队中，总能力值最高的队伍。

注意如果选择海狸 $1,3,5$，总能力值将达到 $15$，但是这会导致海狸 $1$ 没有特长。

这组样例满足所有子任务的限制。

**【样例解释 #2】**

最优组队为：海狸 $2,3,4$。

这组样例满足所有子任务的限制。

**【样例解释 #3】**

任何组队方式都会导致队员没有特长，不存在符合条件的组队。

这组样例满足所有子任务的限制。

**【数据范围】**

对于所有数据，满足：

- $3\leq N\leq 150000$。
- $1\leq X_i,Y_i,Z_i\leq 10^8$ $(1\leq i\leq N)$。

详细子任务附加限制及分值如下表所示：

|子任务编号|附加限制|分值|
|:-:|:-:|:-:|
|$1$|$N\leq 300$|$8$|
|$2$|$N\leq 4000$|$29$|
|$3$|$X_i,Y_i,Z_i\leq 5$ $(i\in[1,N])$|$9$|
|$4$|$X_i,Y_i,Z_i\leq 20$ $(i\in[1,N])$|$9$|
|$5$|$X_i,Y_i,Z_i\leq 300$ $(i\in[1,N])$|$9$|
|$6$|$X_i,Y_i,Z_i\leq 4000$ $(i\in[1,N])$|$9$|
|$7$|无附加限制|$27$|

[双倍经验](https://www.luogu.com.cn/problem/P9525)~~双倍题解~~

考虑贪心。

先抛结论：如果一个人的其中两种能力值为剩余所有人中该能力值的最大值，那么这个人一定不能被选择。

证明很简单：如果这个人被选上了，那么他的两（三）种能力值都是最大的，不符合题意。

所以每次只要删除对于当前最大值不合法的人之后更新最大值，随后持续这个过程直到没有修改为止。

关于具体实现：使用 set/map/堆等记录对于当前这种能力值的最大的人然后判断是否合法即可。复杂度 $O(n \log n)$。

其实也可以用哈希+计数排序把复杂度降到 $O(n)$。

用大型数据结构（cdq分治+大分讨+维护序列的数据结构）也可做。

放一下贪心的代码：

```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
int n,a[150005][3];
set<pair<int,int>,greater<pair<int,int>>> v[3];
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		for(int j=0;j<3;j++){
			cin>>a[i][j];
			v[j].insert({a[i][j],i});
		}
	}
	while(n--){
		int pos=0,f=0;
		for(int i=0;i<3;i++){
			int tmp=v[i].begin()->se,cnt=0;
			for(int j=0;j<3;j++){
				if(a[tmp][j]==v[j].begin()->fi) cnt++;
			}
			if(cnt>=2){
				pos=tmp;
				f=1;
				break;
			}
		}
		if(f) for(int i=0;i<3;i++) v[i].erase(v[i].lower_bound({a[pos][i],pos}));
	}
	if(v[0].empty()) cout<<-1;
	else cout<<v[0].begin()->fi+v[1].begin()->fi+v[2].begin()->fi;
}
```

---

