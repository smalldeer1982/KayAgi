# I Can Guess the Data Structure!

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=229&page=show_problem&problem=3146

[PDF](https://uva.onlinejudge.org/external/119/p11995.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11995/55cb8a2c5cf1532ff4a8dff640c7538c0998c78c.png)

## 样例 #1

### 输入

```
6
1 1
1 2
1 3
2 1
2 2
2 3
6
1 1
1 2
1 3
2 3
2 2
2 1
2
1 1
2 2
4
1 2
1 1
2 1
2 2
7
1 2
1 5
1 1
1 3
2 5
1 4
2 4```

### 输出

```
queue
not sure
impossible
stack
priority queue```

# 题解

## 作者：MY_Lee (赞：3)

#### 闲聊
此题就是个 STL 顶级豪华套餐.....

---
#### 思路
计算机不是人，不能像我们一样用逻辑推理做，怎么办呢？

计算机能暴力！

我们就可以直接开一个 ``stack``，一个 ``queue``，一个 ``priority_queue``。每次操作 $2$ 时就判断是不是有误即可。最后看一下还有哪些是可行的输出。

---
这里给没学过 ``stack``,``queue``,``priority_queue`` 的稍微介绍一下。

- stack，中文名栈，先进后出，即最先进的最后出。
- queue，中文名队列，先进先出，即最先进的最后出。
- priority_queue，中文名优先队列，先进优先级最大的先出，即 DS(数据结构) 中的堆。

C++ 有可口的 STL 容器已经帮我们写好了，我们只需要学习如何使用。

---
先来说 stack。

- 头文件
```cpp
#include<stack>
```
- 定义
```cpp
stack<type>name;
```
PS：其中 ``type`` 是数据类型，你可以放例如 ``int,long long,double`` 以及自定义的 ``struct`` 等等。``name`` 是这个栈的名字，你可以随便取(保留字除外)。

- 压入
```cpp
name.push(x);
```
PS: 其中 ``x`` 是要压入栈的量。

- 弹出
```cpp
name.pop();
```
- 取栈顶元素(不弹出)
```cpp
name.top();
```
- 判断栈是否空
```cpp
name.empty()
```
PS：若返回的是 ``true``，则栈为空，``false`` 则栈不空，这个不要搞反了。

这道题要用的操作就这些了吧，其他的我就不讲了。

---
然后我们讲讲 queue。
- 头文件
```cpp
#include<queue>
```
- 定义
```cpp
queue<type>name;
```
PS：``type`` 和 ``name`` 的用法见上面的栈。
- 进队
```cpp
name.push(x);
```
PS: ``x`` 见上面的栈。
- 出队
```cpp
name.pop();
```
- 取队首元素(不出队)
```cpp
name.front();
```
- 判断队列是否为空
```cpp
name.empty();
```
PS：``true`` 和 ``false`` 的含义见上面的栈。

此题中的队列操作——完毕！

---
最后就是我们的 priority_queue。
- 头文件
```cpp
#include<queue>
```
- 定义
```cpp
priority_queue<type>name;
```
PS：``type`` 和 ``name`` 的用法见上面的栈。
- 压入
```cpp
name.push(x);
```
PS: ``x`` 见上面的栈。
- 弹出
```cpp
name.pop();
```
- 取堆顶元素(不弹出堆)
```cpp
name.top();
```
- 判断堆是否为空
```cpp
name.empty();
```
PS：``true`` 和 ``false`` 的含义见上面的栈。

此题的所有用法到这里就说完了。~~(可怜非 C 党 $3$ 秒钟)~~

---
回归本题。
看完上面的部分，敲码应该很简单了。哦，**注意多组数据。**

放上我滴参考代码：

~~(limingye 的同学：limingye 的码风丑死了！)~~
```cpp
#include<stack>
#include<queue>
#include<cstdio>
#include<iostream>
using namespace std;
int n,op,x;
bool canstk,canque,canprique;//判断是否可行
stack<int>stk;
queue<int>que;
priority_queue<int>prique;
inline void insert(){
	stk.push(x);
	que.push(x);
	prique.push(x);
}//压进去
inline void check(){
	bool checkstk=stk.empty()==false&&stk.top()==x,checkque=que.empty()==false&&que.front()==x,checkprique=prique.empty()==false&&prique.top()==x;
	canstk&=checkstk;canque&=checkque;canprique&=checkprique;
	if(canstk==true){
		stk.pop();
	}
	if(canque==true){
		que.pop();
	}
	if(canprique==true){
		prique.pop();
	}
}//注意判断栈，队列，优先队列是否为空，否则 RE 愉快。
int main(){
	while(1==scanf("%d",&n)){//多组数据
		while(stk.empty()==false){
			stk.pop();
		}
		while(que.empty()==false){
			que.pop();
		}
		while(prique.empty()==false){
			prique.pop();
		}//清空栈，队列，优先队列
		canstk=true;canque=true;canprique=true;//初始化
		for(register int i=1;i<=n;i++){
			scanf("%d%d",&op,&x);
			switch(op){
				case 1:insert();break;
				case 2:check();break;
			}
		}
		int flag=canstk*100+canque*10+canprique;//这个比较玄学。把三个答案变成一个三位数，然后对三位数进行判断
		switch(flag){
			case 100:printf("stack\n");break;//100->stack=true,其他=false
			case 10:printf("queue\n");break;//10->queue=true,其他=false
			case 1:printf("priority queue\n");break;//1->priority_queue=true,其他=false
			case 110:case 101:case 11:case 111:printf("not sure\n");break;//有多于 2 个的答案
			default:printf("impossible\n");break;//其他就是不可能的。
		}//这个地方有点玄学理解一下。
	}
	return 0;
}
```
---
#### 番外
说实话这题感觉有点“牵强”，硬是把 $3$ 个数据结构搞在了一起。

不过也不难，最难的地方是~~你没有看[我的博客](https://moon-snow.blog.luogu.org/)~~。

---

## 作者：YosemiteHe (赞：1)

一道数据结构题。

因为栈、队列、优先队列都是STL支持的，所以就直接用STL。

定义方式：
- 栈：`stack <数据类型> 名称;`
- 队列：`queue <数据类型> 名称;`
- 优先队列：`priority_queue <数据类型> 名称;`

本题要用到的一些基本操作：
- 栈：`push();`（元素入栈）`pop();`（弹出元素）`top();`（栈顶元素）`empty();`（栈是否为空）
- 队列：`push();`（元素入队）`pop();`（弹出元素）`front();`（队首元素）`empty();`（队列是否为空）
- 优先队列：`push();`（元素入队）`pop();`（弹出元素）`top();`（最高优先级的元素）`empty();`（队列是否为空）

当然也要加上头文件：
- 栈：`<stack>`
- 队列/优先队列：`<queue>`

判断是否为栈/队列/优先队列可以用一个函数，用 $1$ 表示它是一个栈/队列/优先队列，用 $0$ 表示不是，比较方便。

有一个小坑点：**如果 $P_i = 2$**（$P_i$ 表示第 $i$ 次操作的类型是 $1$ 还是 $2$）**，并且栈/队列/优先队列为空，直接返回 $0$（栈/队列/优先队列已经没有元素，再取出元素必定错误）。**

还有一点，**一定要用UVA的经典读入方式。**

然后就能打出AC代码了。

```cpp
#include <iosteram>//头文件
#include <cstdio>
#include <stack>//栈的头文件
#include <queue>//队列/优先队列的头文件
#define N 1005//也可以用const int
#define int long long//宏定义，个人习惯
using namespace std;//命名空间
inline int read() { //快读
    int s = 0, v = 1;
    char c = getchar();
    while (!isdigit(c)) {if (c == '-') v = -1; c = getchar();}
    while (isdigit(c)) s = s * 10 + c - '0', c = getchar();
    return s * v;
}
int n, s, q, pq, P[N], x[N];//定义
int STACK() { //判断是否为栈
	stack <int> s;//定义一个栈
	for (int i = 1; i <= n; ++i) { //共n次
		if (P[i] == 1) s.push(x[i]);//如果是第一种操作，压入x[i]
		else { //否则就是第二种操作
			if (s.empty()) return 0;//特判
			int t = s.top();
			if (t != x[i]) return 0;//如果栈顶不是x[i]，那它就不是一个栈，返回0
			s.pop();//弹出栈顶元素
		}
	}
	return 1;//否则就是一个栈
}
int QUEUE() { //与STACK函数相似
	queue <int> s;
	for (int i = 1; i <= n; ++i) {
		if (P[i] == 1) s.push(x[i]);
		else {
			if (s.empty()) return 0;
			int t = s.front();//注意队首元素是front()
			if (t != x[i]) return 0;
			s.pop();
		}
	}
	return 1;
}
int PQUE() { //同STACK函数
	priority_queue <int> s;
	for (int i = 1; i <= n; ++i) {
		if (P[i] == 1) s.push(x[i]);
		else {
			if (s.empty()) return 0;
			int t = s.top();
			if (t != x[i]) return 0;
			s.pop();
		}
	}
	return 1;
}
signed main(void) { //主函数
	while (scanf("%d", &n) == 1) { //UVA经典读入方法
		for (int i = 1; i <= n; ++i) {
			P[i] = read(), x[i] = read();//读入P[i]和x[i]
		}
		s = STACK();//变量s表示是否为栈
		q = QUEUE();//变量q表示是否为队列
		pq = PQUE();//变量pq表示是否为优先队列
		if (s && !q && !pq) puts("stack");//判断并输出
		else if (!s && q && !pq) puts("queue");
		else if (!s && !q && pq) puts("priority queue");
		else if (!s && !q && !pq) puts("impossible");
		else puts("not sure");
	}
    return 0;//结束
}
```

---

## 作者：念古兰 (赞：1)

## ~~这道题算是一个STL大杂烩~~
难度不大，但是如果刚入手STL的话，倒是建议做一做，习惯手写数据结构的同学也可以在这道题检查自己的手打堆，手写队列跟手写栈的正确性


------------
接下来是题目的分析：
题目的包包是一个数据结构，这个有点像rails，也是数据结构的模拟，而且这道题的模拟还要更简单一些。我们假设包包初始状态为三种都有可能，然后跟着数据验证，有一个数据出现错误就排除一种可能，最后再检查一遍还有哪一种数据结构是包包，就可以得出答案了；  
代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
//uva 11995
int main(){
int m=0;
while(scanf("%i",&m)!=EOF)       //uva常用输入模式
{     
	int x=0,y=0;
	bool ok1=1,ok2=1,ok3=1; //queue,stack,priority_queue
	//开队列，栈跟优先队列（大根堆）
        queue<int> q;
	stack<int> s;
	priority_queue<int,vector<int>,less<int> > pq;
	for(register int i=0;i<m;i++)
        {
		scanf("%i%i",&x,&y);
		if(x==1) q.push(y),pq.push(y),s.push(y);
		else 
		{
                if(!q.empty())   //题目要求无错的返回，要先判断
		  {
		    if(q.front() !=y) ok1=0;
		    if(s.top() != y)  ok2=0;
		    if(pq.top() !=y)  ok3=0;
		    q.pop(),s.pop(),pq.pop();
		  }
		  else ok1=ok2=ok3=0; 
		}	
	}
    //根据情况输出
	if(ok1+ok2+ok3>1) printf("not sure\n");
	else if(ok1+ok2+ok3==0) printf("impossible\n");
	else
       {
		if(ok1==1) printf("queue\n");
		else if(ok2==1) printf("stack\n");
		else printf("priority queue\n");
	} 
}
return 0;
}

```


---

## 作者：UKE自动稽 (赞：1)

模拟题，没啥好说的，具体看程序

```
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<stack>
using namespace std;
queue<int> q;
stack<int> s;			//仨容器一块模拟
priority_queue<int> pq;
int main() {
	int n;
	int op, num;
	while(scanf("%d",&n) == 1) {//日常毒瘤输入
		while(!q.empty())
			q.pop();
		while(!s.empty())
			s.pop();
		while(!pq.empty())
			pq.pop();
		bool is_que = 1;
		bool is_sta = 1;
		bool is_prique = 1;
        //以上是初始化
		while(n--) {
			scanf("%d%d",&op,&num);
			if(op == 1) {
				if(is_que)				//操作一（压入容器）
					q.push(num);
				if(is_sta)
					s.push(num);
				if(is_prique)
					pq.push(num);
			}
			if(op == 2) {			//操作二（弹出）
				if(is_que) {
					if(q.empty())	//空的
						is_que = 0; //标记不可能
					else {
						if(q.front() != num) //如果队列头不是那个数字
							is_que = 0;//标记不可能
						else
							q.pop();   //否则出队
					}
				}
				if(is_sta) {
					if(s.empty())		//空的
						is_sta = 0;     //标记不可能
					else {
						if(s.top() != num)//栈顶不是那个数字
							is_sta = 0;	  //标记不可能
						else
							s.pop();	//弹栈
					}
				}
				if(is_prique) {
					if(pq.empty())		//空的
						is_prique = 0;  //不可能
					else {
						if(pq.top() != num)//队头不是那个数字
							is_prique = 0;//不可能
						else
							pq.pop();    //出队
					}
				}
			}
		}
        //后面的有点基础的都能看得懂（毫无别的意思）
		if(is_sta && !is_que && !is_prique)
			printf("stack\n");
		else if(!is_sta && is_que && !is_prique)
			printf("queue\n");
		else if(!is_sta && !is_que && is_prique)
			printf("priority queue\n");
		else if(!is_sta && !is_que && !is_prique)
			printf("impossible\n");
		else
			printf("not sure\n");
	}
}
```

---

## 作者：caibet (赞：0)

### 题意：

你有一个数据结构（栈，队列或优先队列），但你不知道具体是哪一个。给出两种行为：

- `1 x` 表示在这个数据结构里加入一个数 $x$。
- `2 x` 表示从这个数据结构里弹出一个数，且这个数为 $x$。

根据这些信息，输出这个数据结构是什么、指出有多种可能或者指出不可能是任何一种。

### 解法：

这一题看上去很难，因为题目只给你两种操作和其结果，看起来很抽象。

不过，既然只有三种数据结构，那我们就可以把每一种都试一下：让我加入一个数时我就加入一个数；让我弹出一个数时，我就把三种数据结构弹出的结果与给出的 $x$ 对比，如果与哪个数据结构不同，这种数据结构就不可能是答案。

值得注意的是，题目中给出的 `2 x`，表示**不存在任何错误的情况下**弹出了一个数，因而如果数据结构都为空还被题目要求弹出一个数，那么果断指出不可能是任何一种即可。

另外，我使用一个数来存储三个数据结构的状态，每个数据结构的结果占一个二进制位，如果存在加强版可以节省很多空间。

```cpp
namespace{
	int m,op,x,ans;
	void work(){
		while(scanf("%d",&m)==1){
			stack<int> q1;
			queue<int> q2;
			priority_queue<int> q3;
			ans=7;//即二进制的111，表示开始时三种数据结构皆有可能
			while(m--){
				op=read();x=read();
				if(op==1){
					q1.push(x);
					q2.push(x);
					q3.push(x);
				}else{
					if(q1.empty()){
						ans=0;//不可能是任何一种数据结构
					}else{
						if(q1.top()!=x) ans&=3;//即二进制的011，表示排除第一种数据结构
						if(q2.front()!=x) ans&=5;//即二进制的101，表示排除第二种数据结构
						if(q3.top()!=x) ans&=6;//即二进制的110，表示排除第三种数据结构
						q1.pop();q2.pop();q3.pop();
					}
				}
			}
			if(ans==0) puts("impossible");
			else if(ans^(ans&-ans))//奇妙用法，即 ans 去掉其最低位以后还存在非 0 二进制位，那么有多种答案
				puts("not sure");
			else if(ans&4) puts("stack");//与二进制100按位与，判断第一种数据结构
			else if(ans&2) puts("queue");//与二进制010按位与，判断第二种数据结构
			else if(ans&1) puts("priority queue");//与二进制001按位与，判断第三种数据结构
		}
	}
}
```

---

## 作者：SpectatorX (赞：0)

难度不大，可以用来练习STL，也可以自己手打数据结构~~但我太懒了~~。

介绍一下用到的三种数据结构``stack``，``queue``和``priority_queue``。

## ``stack``

栈的修改遵循先进后出原则，~~应该都知道吧~~。
```cpp
#include <stack>
stack<Typename T> s;
s.top()//返回栈顶
s.empty()//返回是否为空
s.size()//返回元素数量
s.push()//插入传入的参数到栈顶
s.pop()//弹出栈顶
```

## ``queue``

队列的修改遵循先进先出原则，就像你在很多地方排队一样，~~虽然人有可能插队~~。
```cpp
#include <queue>
queue<Typename T> q;
q.front()//返回队头
q.empty()//返回是否为空
q.size()//返回元素数量
q.push()//插入传入的参数到队尾
q.pop()//弹出队头
```
## ``priority_queue``

优先队列每次弹出队列当中的最高优先级元素（可以自己定义规则，例如``greater<int>``）。
```cpp
#include <queue>
qriority_queue<Typename T> q;
q.top()//返回堆顶元素
q.empty()//返回是否为空
q.push()//插入传入的参数到堆中
q.pop()//弹出队头
```
---
本题需要让你做的就是同时进行三种数据结构的插入与弹出，判断哪一种数据结构是符合要求的。

另外还有一个坑点，每次弹出时，需要判断队列是否为空，否则可能RE。

代码:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,opt,x;
stack<int> st;
queue<int> q;
priority_queue<int> pq;
int is_st,is_q,is_pq;
void clear()
{
	while(!st.empty())st.pop();
	while(!q.empty())q.pop();
	while(!pq.empty())pq.pop();
	is_st=is_q=is_pq=1;
}
void insert(int x)
{
	st.push(x);
	q.push(x);
	pq.push(x);
}
void pop(int x)
{
	if(q.empty())is_st=is_q=is_pq=0;
	else
	{
		int t=st.top();st.pop();
		if(t!=x)is_st=0;
		t=q.front();q.pop();
		if(t!=x)is_q=0;
		t=pq.top();pq.pop();
		if(t!=x)is_pq=0;
	}
}
inline int read()
{
	int x=0;char ch=getchar();
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))x=x*10+ch-48,ch=getchar();
	return x;
}
int main()
{
	while(scanf("%d",&n)!=EOF)
	{
		clear();
		while(n--)
		{
			opt=read();x=read();
			if(opt==1)insert(x);
			else pop(x);
		}
		if(is_st&&!is_q&&!is_pq)puts("stack");
		else if(!is_st&&is_q&&!is_pq)puts("queue");
		else if(!is_st&&!is_q&&is_pq)puts("priority queue");
		else if(!(is_st||is_q||is_pq))puts("impossible");
		else puts("not sure");
		//clear();
	}
	return 0;
}
```

---

## 作者：lowAltitudeFlyer (赞：0)

## Description
你有一个类似“包包”的数据结构，支持两种操作，如下表所示。

| 操作 | 备注 |
| :----------: | :----------: |
| $1\ x$ | 把元素$x$放进包包 |
| $2$ | 从包包中拿出一个元素 |

给出一系列操作以及返回值，你的任务是猜猜这个“包包”到底是什么。它可能是一个栈，队列，优先队列（数值大的整数先出，即大根堆）或者其他什么奇怪的东西。  
一条类型2命令后面跟着一个整数$x$，表示执行完这条类型2的命令后，包包无错地返回了$x$。
## Solution
STL大法好！！  
显然，栈、队列和优先队列这三种数据结构都可以使用STL直接定义。
大根堆的声明方式如下：
```cpp
priority_queue<int> h;
```
符合本题要求。而小根堆的声明方式如下：
```cpp
priority_queue<int, vector<int>, greater<int> > h;
```
于是本题直接模拟，依次判断输入是否有可能是栈、队列或优先队列，然后综合起来即可。具体实现方式见代码及注释。
## Tips
- 注意题目所说的**无错地返回**。即需要判断包包是否为空。如果包包为空时执行了操作2，则操作不合法，此时答案为impossible。
- 不要忘记清空栈、队列和优先队列，以及重置记录答案的数组。题目有多组数据。

## Code
~~自信地认为自己的注释较为完整，码风较为标准QAQ~~
```cpp
#include<bits/stdc++.h>
using namespace std;
int n, opt, x;
stack<int> s; //栈 
queue<int> q; //队列 
priority_queue<int> h; //优先队列 
int ans[5]; //ans[1]记录stack是否有可能，ans[2]记录queue是否有可能，ans[3]记录priority_queue是否有可能 
int main() {
	while(scanf("%d", &n) != EOF) {
		ans[1] = ans[2] = ans[3] = 1; //开始时stack，queue，priority_queue都有可能 
		while(!s.empty()) s.pop(); //清空栈 
		while(!q.empty()) q.pop(); //清空队列 
		while(!h.empty()) h.pop(); //清空优先队列 
		while(n--) {
			scanf("%d%d", &opt, &x);
			if(opt == 1) {
				s.push(x); q.push(x); h.push(x); //模拟操作1：把x放入包包 
			}
			else {
				if(s.empty()) {
					ans[1] = ans[2] = ans[3] = 0; //包包中没有元素，出现错误 
				}
				else {
					if(s.top() != x) ans[1] = 0; //如果从栈中取出的元素并非x，则不可能是栈 
					if(q.front() != x) ans[2] = 0; //如果从队列中取出的元素并非x，则不可能是队列 
					if(h.top() != x) ans[3] = 0; //如果从优先队列中取出的元素并非x，则不可能是优先队列 
					s.pop(); q.pop(); h.pop(); //模拟操作2：从包包中拿出一个元素 
				}
			}
		}
		if(ans[1] + ans[2] + ans[3] >= 2) printf("not sure\n"); //有2种以上的数据结构是可能的 
		else if(ans[1] == 1) printf("stack\n"); //栈 
		else if(ans[2] == 1) printf("queue\n"); //队列 
		else if(ans[3] == 1) printf("priority queue\n"); //优先队列 
		else printf("impossible\n"); //都不可能 
	}
	return 0;
}
```


---

## 作者：LHN200861 (赞：0)

# 题目解释：

猜猜数据结构

试题描述：

你有一个类似“包包”的数据结构，支持两种操作，如下表所示。

1：把元素x放进包包

2：从包包中拿出一个元素

给出一系列操作以及返回值，你的任务是猜猜这个“包包”到底是什么。它可能是：

一个栈（后进先出）

队列（先进先出）

优先队列（数值大的整数先出）

或者其他什么奇怪的东西。

输入：

第一行为一个整数n（1≤n≤1 000）。以下n行每行要么是一条类型1的命令，要么是一条类型2的命令后面跟着一个整数x(1≤x≤100)。这个整数x表示执行完这条类型2的命令后，包包无错地返回了x。输入文件大小不超过1MB。

输出：

输出一行。一共有5种可能的输出。

stack:一定是一个栈

queue:一定是一个队列

priority queue:一定是一个优先队列

impossible:一定不是以上三种

not sure:至少有两种是可能的

## 看完题目，我们看一下如何解答这道题。

举个判断栈的例子吧：

```cpp
bool isstack()//判断是否是栈
{
	int i,t;
	stack<int>s;//定义栈
	for(i=1;i<=n;i++)
	{
		if(op[i]==1)s.push(x[i]);//加入栈
		else if(s.empty())return false;//如果栈为空，则出错
		else//如果没有出错
		{
			t=s.top();//取用栈顶元素
			if(t!=x[i])return false;//与题目不符
			s.pop();//弹出元素
		}
	}
	return true;//被忘了返回，不然会一直输出impossible
}
```

再给大家看一下主程序部分：

```cpp
int main()
{
	bool s,q,pq;//存储是否为栈、队列、优先队列
	int i;
	while(cin>>n)//输入n
	{
		for(i=1;i<=n;i++)//输入并存储op数组和x数组
		{
			cin>>op[i]>>x[i];
		}
		s=isstack();//判断是否是栈
		q=isqueue();//判断是否是队列
		pq=ispriqueue();//判断是否是优先队列
		if(!s&&!q&&!pq)puts("impossible");//一定不是以上三种
		else if(s&&!q&&!pq)puts("stack");//一定是一个栈
		else if(!s&&q&&!pq)puts("queue");//一定是一个队列
		else if(!s&&!q&&pq)puts("priority queue");//一定是一个优先队列
		else puts("not sure");//至少有两种是可能的
	}
	return 0;//养成好习惯，加上"return 0;"。
}
```

看到这儿，大家应该会写代码了吧。

如果还是不会，那就看一下我的AC代码吧。

# 接下去上AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x[1005],op[1005];//定义n，x数组和op数组
bool isstack()//判断是否是栈
{
	int i,t;
	stack<int>s;//定义栈
	for(i=1;i<=n;i++)
	{
		if(op[i]==1)s.push(x[i]);//加入栈
		else if(s.empty())return false;//如果栈为空，则出错
		else//如果没有出错
		{
			t=s.top();//取用栈顶元素
			if(t!=x[i])return false;//与题目不符
			s.pop();//弹出元素
		}
	}
	return true;//被忘了返回，不然会一直输出impossible
}
bool isqueue()//判断是否是队列
{
	int i,t;
	queue<int>s;//定义队列
	for(i=1;i<=n;i++)
	{
		if(op[i]==1)s.push(x[i]);//加入队列
		else if(s.empty())return false;//如果队列为空，则出错
		else//如果没有出错
		{
			t=s.front();//取用队头元素
			if(t!=x[i])return false;//与题目不符
			s.pop();//弹出元素
		}
	}
	return true;//被忘了返回，不然会一直输出impossible
}
bool ispriqueue()//判断是否是优先队列
{
	int i,t;
	priority_queue<int>s;//定义优先队列
	for(i=1;i<=n;i++)
	{
		if(op[i]==1)s.push(x[i]);//加入优先队列
		else if(s.empty())return false;//如果优先队列为空，则出错
		else//如果没有出错
		{
			t=s.top();//取用堆顶元素
			if(t!=x[i])return false;//与题目不符
			s.pop();//弹出元素
		}
	}
	return true;//被忘了返回，不然会一直输出impossible
}
int main()
{
	bool s,q,pq;//存储是否为栈、队列、优先队列
	int i;
	while(cin>>n)//输入n
	{
		for(i=1;i<=n;i++)//输入并存储op数组和x数组
		{
			cin>>op[i]>>x[i];
		}
		s=isstack();//判断是否是栈
		q=isqueue();//判断是否是队列
		pq=ispriqueue();//判断是否是优先队列
		if(!s&&!q&&!pq)puts("impossible");//一定不是以上三种
		else if(s&&!q&&!pq)puts("stack");//一定是一个栈
		else if(!s&&q&&!pq)puts("queue");//一定是一个队列
		else if(!s&&!q&&pq)puts("priority queue");//一定是一个优先队列
		else puts("not sure");//至少有两种是可能的
	}
	return 0;//养成好习惯，加上"return 0;"。
}
//完美地结束
```

接下来你就会发现：

![](https://www.luogu.org/images/congratulation.png)

---

## 作者：lv_1977839633 (赞：0)

# 这道题其实只是一道大模拟而已

**~~十分简单~~**

------------
**写完之后，我以为自己只是A了一道**[普及-](https://www.luogu.org/problem/list?difficulty=2&page=1)


------------
**~~废~~** 闲话少说，进入~~正题~~ ：



------------
身为一道模拟，就看着题目打代码就完了，它让干什么咱们就干什么，所以先开三个数据结构。。。。。。**（具体解释请看代码！）**




**~~<本人觉得代码码风还是不错的>~~**

**（温馨提示：本篇题解中的各变量和名称可能有些长，但是含义很容易理解，方便看下面题解时理解）**

**（P.S:	本题题目翻译未指出每个测试点会有好几次测试，所以记得[不定项输入](https://www.luogu.org/blog/kill-weak-killer/fou-ding-xiang-shu-ru)）**

------------
**C++代码：**
**~~（也只有C++代码<只会C++和PHP>）：~~**



------------

```cpp
//——UVA11995 I Can Guess the Data Structure!.cpp 

#include<iostream>//必要的头文件 
#include<cstdio>//优化(ios语句)用的头文件 
#include<stack>//stack的头文件 
#include<queue>//queue和priority_queue的头文件 

using namespace std;//声明命名空间 

int a,n,k;//n : 数据点个数  a : 指令(即 1 或 2)  k : 当前数据(即题目中的x) 

stack<int> _stack;//定义一个栈 _stack 
queue<int> _queue;//定义一个队列 _queue 
priority_queue<int> _priority_queue;//定义一个优先队列 _priority_queue 

bool judge_stack(int a,int k);//判断其是否是栈，是 ：返回值为 1  否 ：返回值为 0 
bool judge_queue(int a,int k);//判断其是否是队列，是 ：返回值为 1  否 ：返回值为 0 
bool judge_priority_queue(int a,int k);//判断其是否是优先队列，是 ：返回值为 1  否 ：返回值为 0 

string judging(void)
{
	bool flag_stack = 1 , flag_queue = 1 , flag_priority_queue = 1;
	//存储其是否为 stack，queue，priority_queue ，值为 1 ，是；值为 2 ，否 
	//设为局部变量，不用每次测试后重置为 1了 
	
	for(int i = 0 ; i < n ; ++i)//顺序输入n次 
	{
		cin>>a>>k;//输入指令 
		
		if(flag_stack /* == 1*/)//如果已判断其不为栈，则停止对栈的判断 
			flag_stack = judge_stack(a,k);//调用函数，进行判断 
			
		if(flag_queue)//如果已判断其不为队列，则停止对栈的队列 
			flag_queue = judge_queue(a,k);//调用函数，进行判断 
			
		if(flag_priority_queue)//如果已判断其不为优先队列，则停止对栈的优先队列 
			flag_priority_queue = judge_priority_queue(a,k);//调用函数，进行判断 
		
	}
	
	//重点！！！：判断 
	
	int judge = flag_stack + flag_queue + flag_priority_queue;
	//判断方法：judge为三个数之和，简化判断过程易于判断 ！
	//判断过程请看下文 
	
	while(!_stack.empty())
		_stack.pop();//清空栈 
	
	while(!_queue.empty())
		_queue.pop();//清空队列 
	
	while(!_priority_queue.empty())
		_priority_queue.pop();//清空优先队列 
	
	if(judge >= 2) // 两个以上为 true (1)
		return "not sure\n";
	
	if(judge == 0) // 三个全为 false (0) 
		return "impossible\n";
	
	//经过上面的判断后，便只有 judge == 1，即：是其中的一个这一种情况了
	//只需依次判断即可 
	
	if(flag_stack)
		return "stack\n";
		
	if(flag_queue)
		return "queue\n";
	
	if(flag_priority_queue)
		return "priority queue\n";
	
}

int main(void)
{
	ios::sync_with_stdio(false);//优化输入输出 
	
	while(cin>>n)//不定项输入 
		cout << judging();
	
	return 0;//终止程序 
}

bool judge_stack(int a,int k)//栈的判断 
{
	if(a == 1)//即：输入指令 
	{
		_stack.push(k);
		return 1;
	}
	
	//经上面的判断，即可确认 a一定为 2，即为输出指令 
	
	if(_stack.empty())//若栈已空，则不是栈，返回 0 
		return 0;
	
	if(_stack.top() == k)//判断输出值是否相同 
	{
		_stack.pop();
		return 1;
	}	
	
	return 0;
}

bool judge_queue(int a,int k)//队列的判断 
{
	if(a == 1)
	{
		_queue.push(k);
		return 1;
	}
	
	//经上面的判断，即可确认 a一定为 2，即为输出指令 
	
	if(_queue.empty())//若队列已空，则不是队列，返回 0 
		return 0;
	
	if(_queue.front() == k)//判断输出值是否相同 
	{
		_queue.pop();
		return 1;
	}
	
	return 0;
}

bool judge_priority_queue(int a,int k)//优先队列的判断 
{
	if(a == 1)
	{
		_priority_queue.push(k);
		return 1;
	}
	
	//经上面的判断，即可确认 a一定为 2，即为输出指令 
	
	if(_priority_queue.empty())//若优先队列已空，则不是优先队列，返回 0 
		return 0;
	
	if(_priority_queue.top() == k)//判断输出值是否相同 
	{
		_priority_queue.pop();
		return 1;
	}
	
	return 0;	
}


//注意上面的pop()不能少！ 
//十年OI一场空，不加pop见祖宗！！！ 
```

------------

~~十年OI一场空，不加pop见祖宗！！！~~

**再会！！！**






---

## 作者：andyli (赞：0)

本题考察了栈、队列和优先队列3种$\text{ADT}$的概念。只要熟悉这些概念，本题不难解决。事实上，$\text{STL}$ 中已经封装好了这3种数据结构，分别是`stack`，`queue`和`priority_queue`。这样，本题只需要依次判断输入是否有可能是栈，队列或优先队列，然后综合起来即可。注意到题目中说的“无错误的返回”，因此在执行`pop`操作的时候要调用一下`empty()`，否则可能会异常退出。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1005;

int A[maxn], B[maxn], n;
bool CheckStack()
{
    stack<int> s;
    for (int i = 0; i < n; i++)
    {
        if (A[i] == 2)
        {
            if (s.empty())
                return false;
            int x = s.top();
            s.pop();
            if (x != B[i])
                return false;
        }
        else
            s.push(B[i]);
    }
    return true;
}

bool CheckQueue()
{
    queue<int> q;
    for (int i = 0; i < n; i++)
    {
        if (A[i] == 2)
        {
            if (q.empty())
                return false;
            int x = q.front();
            q.pop();
            if (x != B[i])
                return false;
        }
        else
            q.push(B[i]);
    }
    return true;
}

bool CheckPQ()
{
    priority_queue<int> pq;
    for (int i = 0; i < n; i++)
    {
        if (A[i] == 2)
        {
            if (pq.empty())
                return false;
            int x = pq.top();
            pq.pop();
            if (x != B[i])
                return false;
        }
        else
            pq.push(B[i]);
    }
    return true;
}

int main()
{
    while (~scanf("%d", &n))
    {
        for (int i = 0; i < n; i++)
            scanf("%d%d", &A[i], &B[i]);
        int Stack = CheckStack(), Queue = CheckQueue();
        int sum = Stack + Queue + CheckPQ();
        if (!sum)
            printf("impossible");
        else if (sum > 1)
            printf("not sure");
        else if (Stack)
            printf("stack");
        else if (Queue)
            printf("queue");
        else
            printf("priority queue");
        printf("\n");
    }
    return 0;
}
```

---

