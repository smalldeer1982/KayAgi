# [ABC225D] Play Train

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc225/tasks/abc225_d

高橋君は電車のおもちゃを連結させたり分離させたりして遊んでいます。  
 電車は $ N $ 個あり、電車 $ 1 $ 、電車 $ 2 $ 、$ \ldots $ 、電車 $ N $ と名前がついています。  
 はじめ電車どうしは連結しておらず全てバラバラです。

クエリが $ Q $ 個与えられるので、与えられた順番に処理してください。  
 クエリは次の $ 3 $ 種類のいずれかです。

- `1 x y` ：電車 $ x $ の後部と、電車 $ y $ の前部を連結させる。  
   以下のことが保証されます。
  
  
  - $ x\ \neq\ y $
  - クエリを処理する直前に、電車 $ x $ の後部と連結している電車は存在しない
  - クエリを処理する直前に、電車 $ y $ の前部と連結している電車は存在しない
  - クエリを処理する直前に、電車 $ x $ と電車 $ y $ は異なる連結成分に属する
- `2 x y` ：電車 $ x $ の後部と、電車 $ y $ の前部を分離させる。  
   以下のことが保証されます。
  
  
  - $ x\ \neq\ y $
  - クエリを処理する直前に、電車 $ x $ の後部と電車 $ y $ の前部は直接連結している
- `3 x` ：電車 $ x $ が含まれる連結成分に属する電車の番号を、**先頭から順番に**全て出力する。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ Q\ \leq\ 10^5 $
- $ 1\ \leq\ x\ \leq\ N $
- $ 1\ \leq\ y\ \leq\ N $
- 入力は全て整数
- クエリは全て問題文の条件を満たす
- `3 x` の形式のクエリで出力する電車の番号の個数の合計は $ 10^6 $ 以下

### Sample Explanation 1

$ \mathrm{query}_5 $ まで処理した時、電車は以下のようになっています。 この時、たとえば電車 $ 2 $ は、電車 $ 3,5,6,7 $ と同じ連結成分に属していますが、電車 $ 1,4 $ とは同じ連結成分に属していません。 !\[\](https://img.atcoder.jp/ghi/dbfd2666776e351752bba67e9b65fafa.png) $ \mathrm{query}_{11} $ まで処理した時、電車は以下のようになっています。 !\[\](https://img.atcoder.jp/ghi/dad814ca77ec58f31cb88c62b9825bef.png)

## 样例 #1

### 输入

```
7 14
1 6 3
1 4 1
1 5 2
1 2 7
1 3 5
3 2
3 4
3 6
2 3 5
2 4 1
1 1 5
3 2
3 4
3 6```

### 输出

```
5 6 3 5 2 7
2 4 1
5 6 3 5 2 7
4 1 5 2 7
1 4
2 6 3```

# 题解

## 作者：kevin1616 (赞：7)

### 审题
现在有 $Q$ 个操作，每个操作执行 $3$ 种操作：
1. 将 $x$ 和 $y$ 相连。
2. 将 $x$ 和 $y$ 的连接解除。
3. 输出 $x$ 所在链的长度，及其这条链中的所有元素。

***
### 方法
【手写链表】看到题目就可以想到链表，此题用手写链表是再好不过的一个选择。
***
### 思路
相连，即 $a$ 的左边是 $b$。连接解除，即 $a$ 的左边不是 $b$，此时可以建立一个 $0$，使连接断开。输出时找到 $0$ 就停止查找，输出链表长度，再进行第二次查找，输出每个元素。代码实现起来还是比较简单的。
***
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int NR = 2e5 + 5;
int n,q;
int x,y;
int a[NR];
int site,ans;
int l[NR],r[NR];
void link(int x,int y){ //连接
    r[x] = y;
    l[y] = x;
}
void dislink(int x,int y){ //断连
    if(r[x] == y) r[x] = l[y] = 0;
    else l[y] = r[x] = 0;
}
int main(){
    cin >> n >> q;
    while(q--){
        int op;
        cin >> op;
        if(op == 1){
            cin >> x >> y;
            link(x,y);
        }
        else if(op == 2){
            cin >> x >> y;
            dislink(x,y);
        }
        else if(op == 3){ //输出
            cin >> x;
            site = x,ans = 1;
            while(l[site] != 0) site = l[site]; //找到链头
            x = site; //复制，因为要用两次
            while(r[x] != 0){ //查找长度
                ans++;
                x = r[x];
            }
            cout << ans << " ";
            while(r[site] != 0){ //输出元素
                cout << site << " ";
                site = r[site];
            }
            cout << site << endl; //输出另外一个元素，然后换行
        }
    }
    return 0; //好习惯
}
```
不抄题解，从我做起！

---

## 作者：xuchuhan (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc225_d)

[更好的阅读体验](https://www.luogu.com.cn/blog/785639/solution-at-abc225-d)

## Part0：前言

楼上 + 同班同学 **YangXiaopei** 已经写得很详细了，但是我觉得还是有些部分讲的比较粗糙，所以写了这篇题解。

## Part1：前置知识

这道题我们需要用的是链表，下面简单介绍一下链表是什么。

链表是一种非连续的数据结构，元素的顺序是通过链表中的指针次序实现的。不同于数组，链表是不能通过下标查询的。对于链表中的每一个元素 $i$，他们都有自己的前一项 $l_i$ 以及 后一项 $r_i$。那么，我们如何表示元素 $a$ 在元素 $b$ 的前面呢？

```cpp
void link(int a,int b){
	r[a]=b;
	l[b]=a;
}
```

而第 $1$ 项没有前一项，于是我们可以给他加一个，记为 `HEAD`，类似地，最后一项的下一项我们记为 `END`。

于是，我们用一个链状的数据结构记录下了每个元素。

那有人就问了：数组是用 `for` 循环通过下标遍历的，那链表没有下标，如何遍历呢？其实很简单。

```cpp
for(int i=r[HEAD];i!=END;i=r[i])
```

解释一下：我们从 `HEAD` 的后一项开始遍历，遍历到 `END` 时结束， $i$ 每次变到原来的下一项。

知道这些基本知识后，我们来看一下链表和数组的对比。如下表：

|  | 链表 | 数组 | 链表时复 | 数组时复 |
| :-----------: | :-----------: | :-----------: | :-----------: | :-----------: |
| 在 $A$ 和 $B$ 之间插入 $C$  | $A$ 的下一项变成 $C$，$B$ 的上一项变成 $C$ | $B$ 及其以后的元素集体往右挪一个位置，$B$ 原来的位置让给 $C$ | $O(1)$ | $O(n)$ |
| 删除 $A$ 这个元素 | 将 $A$ 的前一项与后一项联系起来 | $A$ 的后面所有元素往左挪一个位置 | $O(1)$ | $O(n)$ |
| 知道元素找位置 | 从头到尾遍历+判断 | 下标查询 | $O(n)$ | $O(1)$ |
| 知道位置找元素 | 从头到尾遍历+记录个数 | 下标查询 | $O(n)$ | $O(1)$ |

可以观察到，链表做插入和删除操作的效率很高。

## Part2：题目大意

三种操作：

- 将 $x$ 和 $y$ 相连。

- 删除 $x$ 和 $y$ 的连接。

- 查询 $x$ 所在链的长度。

## Part3：题目分析

无论是第一种连接操作还是第二种删除操作，链表都可以用 $O(1)$ 的时间复杂度完成。所以，我们愉快地选择用链表解决此题。

## Part4：代码实现

1. 预处理：通常情况下，我们只需要在一条链上进行操作，但这次不同，我们并不知道会出现多少条链，链的个数最大的情况可达到 $n$ 个。所以，我们可以刚开始把每个元素都当成一条链进行操作。

```cpp
for(int i=1;i<=n;i++){
	link(HEAD,i);
	link(i,END);
}
```

2. 连接操作：用上文所讲的 `link` 函数连接 $x$ 和 $y$ 即可。

```cpp
void opera1(){
	int x,y;
	cin>>x>>y;
	link(x,y);
}
```

3. 删除操作：删除 $x$ 和 $y$ 的联系，把一条链在 $x$ 和 $y$ 连接的地方断开。因此原来的 $1$ 条链会变成 $2$ 条，而且第 $1$ 条的结尾是 $x$，第 $2$ 条的开头是 $y$。那把 $x$ 和 `END`，$y$ 和 `HEAD` 连接不就行了！

```cpp
void opera2(){
	int x,y;
	cin>>x>>y;
	link(x,END);
	link(HEAD,y);
}
```

4. 查询操作：纯模拟。先往左右各扫一遍，记录链的长度，然后输出。接着再扫一遍，扫到左端点，一直往右遍历，再不停输出遍历到的点即可。可能有点不太清楚，看代码吧。

```cpp
void opera3(){
	int x;
	cin>>x;
	cnt=1;//刚开始是一，因为无论扫左边还是扫右边都不会扫到x，所以x要被提前记录
	pos=x;
	while(l[pos]!=HEAD){//扫左
		pos=l[pos];
		cnt++;
	}
	pos=x;
	while(r[pos]!=END){//扫右
		pos=r[pos];
		cnt++;
	}
	cout<<cnt<<" ";//输出元素个数
	pos=x;
	while(l[pos]!=HEAD)//再扫左
		pos=l[pos];
	while(1){//一直往右，直到扫到的元素的下一项是END
		cout<<pos<<" ";
		if(r[pos]==END)
			break;
		pos=r[pos];
	}
	cout<<"\n";
}
```

## Part5：最后代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,q,cnt,pos;
int l[N],r[N];
const int HEAD=0;
const int END=1e5+1;//注意END的取值，一般是比n多一点点，这样可以保证不被扫到
void link(int a,int b){
	r[a]=b;
	l[b]=a;
}
void opera1(){
	int x,y;
	cin>>x>>y;
	link(x,y);
}
void opera2(){
	int x,y;
	cin>>x>>y;
	link(x,END);
	link(HEAD,y);
}
void opera3(){
	int x;
	cin>>x;
	cnt=1;//刚开始是一，因为无论扫左边还是扫右边都不会扫到x，所以x要被提前记录
	pos=x;
	while(l[pos]!=HEAD){//扫左
		pos=l[pos];
		cnt++;
	}
	pos=x;
	while(r[pos]!=END){//扫右
		pos=r[pos];
		cnt++;
	}
	cout<<cnt<<" ";//输出元素个数
	pos=x;
	while(l[pos]!=HEAD)//再扫左
		pos=l[pos];
	while(1){//一直往右，直到扫到的元素的下一项是END
		cout<<pos<<" ";
		if(r[pos]==END)
			break;
		pos=r[pos];
	}
	cout<<"\n";
}
int main(){
	cin>>n>>q;
	for(int i=1;i<=n;i++){
		link(HEAD,i);
		link(i,END);
	}
	while(q--){
		int opt;
		cin>>opt;
		if(opt==1)
			opera1();
		if(opt==2)
			opera2();
		if(opt==3)
			opera3();
	}
	return 0;
}
```

---

## 作者：YangXiaopei (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc225_d)

***

## 题目大意：

有三种操作：

* 连接 $x$ 和 $y$。

* 断开 $x$ 和 $y$ 的连接。

* 输出 $x$ 所在链的长度和所有元素，以换行隔开。

## Solution：

当我们看到“连接”，“链”等字眼时，我们必须想到一种数据结构——链表（不会请自己去搜博客）。

所以我们用链表模拟即可。

注意：

第二种操作用 STL 的链表不太好处理，建议用手写链表。

## Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5+5;
int n, q, o, x, y;
int l[N], r[N];
const int HEAD = 0;
const int END = 1e5 + 1;
void link(int a,  int b){
	r[a] = b;
	l[b] = a;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> q;
	for(int i = 1; i <= n; i++){
		link(HEAD, i);
		link(i, END);
	}
	while(q--){
		cin >> o;
		if(o == 1){//操作1
			cin >> x >> y;
			link(x, y);
		}
		if(o == 2){//操作2
			cin >> x >> y;
			link(x, END);
			link(HEAD, y);
		}
		if(o == 3){//操作3
			cin >> x;
			int pos = x;
			int cnt = 1;
			int t = x;
			while(l[pos] != HEAD){
				pos = l[pos];
				cnt++;
			}
			while(r[t] != END){
				t = r[t];
				cnt++;
			}
			cout << cnt << " ";
			for(int i = pos; i != END; i=r[i]){
				cout << i << " ";
			}
			cout << "\n";
		}
	}
	return 0;
}
```

---

## 作者：Hog_Dawa_IOI (赞：1)

校内打比赛时居然 TLE 了，当时把这道题搞得复杂多了，结果喜提 RK1（分数从低到高排序），毁我六一大好心情。     
话不多说，其实就是一个大模拟。     
题目要求我们实现三种操作：
- `1 x y`，将 $x$ 和 $y$ 相连。（$y$ 在 $x$ 之后）
- `2 x y`，将 $x$ 和 $y$ 的连接解除。
- `3 x`，输出 $x$ 所在链的长度，及其这条链中的所有元素。（**从前往后**）

那么我们可以通过记录每个点前面和后面的元素，来维护这一条条的火车链。  
在遇到第三种操作时，我们就要遍历这一整条链，先遍历到最前面，再遍历到最后面。     
那么有人可能就会问：不会超时吗？   
这的确不会超时，因为总的要输出的火车节数量在 $10^6$ 个以内。   
那么这道题就被解决啦！
```cpp
#include<stdio.h>
int n,q,s,x,y,father[100005],son[100005];
int count(int where,int last)
{
	int returns=0;
	if(father[where]!=0&&father[where]!=last) returns+=count(father[where],where);
	if(son[where]!=0&&son[where]!=last) returns+=count(son[where],where);
	return returns+1;
}
void print(int where,int last)
{
	if(father[where]!=0&&father[where]!=last) print(father[where],where);
	printf("%d ",where);
	if(son[where]!=0&&son[where]!=last) print(son[where],where);
}
int main()
{
	scanf("%d%d",&n,&q);
	while(q--)
	{
		scanf("%d",&s);
		if(s==1) scanf("%d%d",&x,&y),father[y]=x,son[x]=y;
		else if(s==2) scanf("%d%d",&x,&y),father[y]=son[x]=0;
		else if(s==3) scanf("%d",&x),printf("%d ",count(x,0)),print(x,0),putchar('\n');
	}
}
```

---

## 作者：_zzzzzzy_ (赞：1)

# 思路
用一个类似并查集的东西，最后同链的数都在一起。

那么我们可以记录一个链的左坐标和右坐标，然后把左坐标当成这个序列的祖先节点。

分开的时候可以像并查集一样把父亲设成自己。

操作三的时候可以找到左坐标然后直到右坐标等于自己，记录到一个数组里面一起输出就可以了。

具体的实现可以看代码。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1000000;
int l[maxn],r[maxn];
int F(int x){
	if(x!=l[x])return F(l[x]);
	return x;
}
int main(){
	int n,q;
	cin>>n>>q;
	for(int i=1;i<=n;i++)l[i]=i,r[i]=i;
	while(q--){
		int op;cin>>op;
		if(op==1){
			int x,y;
			cin>>x>>y;
			r[x]=y;l[y]=x;
		}
		else if(op==2){
			int x,y;
			cin>>x>>y;
			r[x]=x;l[y]=y;
		}
		else{
			int x;
			cin>>x;
			vector<int>ans;
			int y=F(x);
			while(r[y]!=y){
				ans.push_back(y);
				y=r[y];
			}
			ans.push_back(y);
			cout<<ans.size()<<" ";
			for(int i=0;i<ans.size();i++)cout<<ans[i]<<" ";
			cout<<"\n";
		}
	} 
	return 0;
}
```

---

## 作者：him的自我修养 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/AT_abc225_d)
# 思路
这道题我们可以用像是链表的方式做，用数组 $ l_{i} $ 和 $ r_{i} $ 表示第 $i$ 个数连接的前面和后面分别是谁。

# 实现
然后我们分析一下这道题的三个操作。

1.连接 $ x $ 与 $ y $，就是让 $x$ 的后面是 $y$，$y$ 的后面是 $x$。可以用以下代码实现。
```
cin >>x>>y;
l[y]=x;
r[x]=y;
```
2.断开 $x$ 与 $y$ 的连接，这里需要注意以下 $x$ 和 $y$ 谁前谁后。这个操作可以用以下代码实现。
```
cin >>x>>y;
if(r[x]==y){
	r[x]=l[y]=0;
}else{
	r[y]=l[x]=0;
}
```
3.查找 $x$ 所在的链，并从头输出。这个就没什么技术含量了，就是通过 $x$ 不停地找。这个操作可以用以下代码实现。
```
cin >>x;
int id=x;
while(l[id]!=0) id=l[id];
x=id;
int cnt=1;
while(r[x]!=0) cnt++,x=r[x];
cout <<cnt<<" ";
while(r[id]!=0){
	cout <<id<<" ";
	id=r[id];
}
cout <<id<<"\n";
```
最后，再把三个部分拼在一起就可以啦。

# 代码
```
#include <iostream>
using namespace std;
int l[100010],r[100010];
int main(){
	int n,q;
	cin >>n>>q;
	while(q--){
		int op,x,y;
		cin >>op;
		if(op==1){
			cin >>x>>y;
			l[y]=x;
			r[x]=y;
		}
		if(op==2){
			cin >>x>>y;
			if(r[x]==y){
				r[x]=l[y]=0;
			}else{
				r[y]=l[x]=0;
			}
		}
		if(op==3){
  			cin >>x;
			int id=x;
			while(l[id]!=0) id=l[id];
			x=id;
			int cnt=1;
			while(r[x]!=0) cnt++,x=r[x];
			cout <<cnt<<" ";
			while(r[id]!=0){
				cout <<id<<" ";
				id=r[id];
			}
			cout <<id<<"\n";
			
		}
	}
	return 0;
}
```


---

## 作者：CQ_Bab (赞：0)

# 思路
这道题其实我们可以用一种像是链表的结构来解决，我们可以用两个数组 $l$ 和 $r$ 来表示每一个数的前面是谁和后面是谁，并且若有一个数的前面和后面没有就为 $-1$。然后我们对于三种操作分开处理。

- 连接操作，我们可以将 $x$ 的后一个变为 $y$，$y$ 的前一个变为 $x$。
- 删除操作，我们可以将 $x$ 的后一个以及 $y$ 的前一个都赋值为 $-1$。
- 查找操作，我们可以先从 $x$ 一直往前找，然后我们又一直从最前面找到最后面即可求出长度，然后再来一遍从前到后即可输出整个序列。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std ;
#define IOS std::ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
#define re return
#define int long long
#define rep(i,x,y) for(int i=x;i<=y;i=-~i)
const int M=1e5+10;
int read() {
	int s=0,w=1;
	char a=getchar();
	while(a<'0'||a>'9') {
		if(a=='-')w=-1;
		a=getchar();
	}
	while(a>='0'&&a<='9'){
		s=s*10+a-'0';
		a=getchar();
	} 
	return s*w;
}
signed main() {
	int n,m,l[M],r[M];
	n=read();
	m=read();
	rep(i,1,n) l[i]=r[i]=-1;//初始化
	rep(i,1,m) {
		int opt,x,y;
		opt=read();
		x=read();
		if(opt==1) {
			y=read();
			l[y]=x; //赋值
			r[x]=y;
		}else if(opt==2) {
			y=read();
			r[x]=l[y]=-1; //归零
		}else {
			int cnt=0,now=x;
			while(~l[now]) now=l[now]; //找到最前面
			int N=now;
			while(~r[now]) { //找到最后
				cnt++;
				now=r[now];
			}
			printf("%d ",cnt+1); //长度
			while(~r[N]) {
				printf("%d ",N); //每一个数
				N=r[N];
			}
			printf("%d",N);
			putchar('\n');
		}
	}
	re false;
}
```

---

## 作者：WaterSun (赞：0)

# 题意

给定 $N$ 个小车，每个小车的编号分别为：$1,2,\dots,N$。

现在有 $Q$ 个操作，每个操作执行 $3$ 种操作：

- `1 x y`，将 $x$ 和 $y$ 相连。（$y$ 在 $x$ 之后）

- `2 x y`，将 $x$ 和 $y$ 的连接解除。

- `3 x`，输出 $x$ 所在链的长度，及其这条链中的所有元素。（**从前往后**）

# 思路

我们可以定义一个结构体 $a$，对于每一个 $a_i$ 我们保存一个 $l$ 和 $r$，分别记录 $i$ 的前一辆车的编号和 $i$ 后一辆车的编号。

- 对于操作 1，我们只需要将 $a_x$ 的 $r$ 设为 $y$，$a_y$ 的 $l$ 设为 $x$ 即可。

- 对于操作 2，我们只需要将 $a_x$ 的 $r$ 设为 $0$，$a_y$ 的 $l$ 设为 $0$ 即可。

- 对于操作 3，我们可以从 $x$ 这个点开始一直通过 $x \leftarrow a_{x,l}$ 走到这条链的开端，再通过 $x \leftarrow a_{x,r}$ 的方式走到链的结尾即可。（过程中需要记录一下链中的信息和长度）

# code

```cpp
#include <bits/stdc++.h>
#define re register

using namespace std;

const int N = 1e5 + 10;
int n,q;
int ans[N];

struct node{
	int l;
	int r;
}arr[N];

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

int main(){
	n = read();
	q = read();
	while (q--){
		int op;
		op = read();
		if (op == 1){
			int x,y;
			x = read();
			y = read();
			arr[x].r = y;
			arr[y].l = x;
		}
		else if (op == 2){
			int x,y;
			x = read();
			y = read();
			arr[x].r = 0;
			arr[y].l = 0;
		}
		else{
			int x;
			int idx = 0;
			x = read();
			while (arr[x].l) x = arr[x].l;
			while (arr[x].r){
				ans[++idx] = x;//记录 
				x = arr[x].r;
			}
			ans[++idx] = x;
			printf("%d ",idx);
			for (re int i = 1;i <= idx;i++) printf("%d ",ans[i]);
			puts("");
		}
	}
	return 0;
}
```

---

## 作者：loser_seele (赞：0)

这种纯模拟题已经不多见了。

题目实际上是模拟一个链表，支持连接，分裂，查询和一个点相连的所有元素。

所以对每个结点维护一个头指针和尾指针，对于连接和分裂操作显然可以直接通过更新头指针和尾指针 $ \mathcal{O}(1) $ 实现，现在问题在于查询操作。

但注意到题目中的限制：输出元素不会超过 $ 10^6 $，所以可以暴力模拟，每次找到和一个节点相连的所有结点即可，虽然单次查询的复杂度是最差 $ \mathcal{O}(n) $ 的，但是因为输出元素不超过 $ 10^6 $，所以总操作次数也不会超过 $ 10^6 $，可以通过。

时间复杂度 $ \mathcal{O}(\sum ans) $，不会超过 $ 10^6 $，可以通过。

代码：

```cpp
#import <bits/stdc++.h>
using namespace std;
int main()
{
	int n,q;
	cin>>n>>q;
	vector<int>front(n+1),rear(n+1);
	while(q--)
    {
		int c;
		cin>>c;
		if(c==1)
        {
			int x,y;
			cin>>x>>y;
			rear[x]=y;
			front[y]=x;
		}
		else if(c==2)
        {
			int x,y;
			cin>>x>>y;
			rear[x]=0;
			front[y]=0;
		}
		else
        {
			int x;
			cin >> x;
			while(front[x])
			x=front[x];
			vector<int>ans;
			while(x)
			ans.push_back(x),x=rear[x];
			cout<<ans.size()<< ' ';
			for(auto x:ans)
            cout<<x<<' ';
            cout<<'\n';
		}
	}
}
```


---

