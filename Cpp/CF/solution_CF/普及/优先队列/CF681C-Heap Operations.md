# Heap Operations

## 题目描述

题目：堆的操作

题面：

Petya近日学习了一种名为"二元堆"的数据结构。

这个数据结构支持以下操作：

-将给定的数字放入堆中；

-取得堆中最小的元素的值；

-取出(去除)堆中最小的元素；

于是，这个堆在任何时候都包含数个整数(可能是一个)，它们当中有一些是相等的。

为了更好地学习这个数据结构，Petya创立了一个空的堆并在上面应用了一些操作。同时，他小心翼翼地在他的日志中写下了所有的操作，如下：

insert x — 将一个值为x的元素插入堆中;

getMin x — 这个时候，堆中最小的元素的值为x.

removeMin — 移除堆中最小的元素(若有多个相同，只移除其中的一个).

所有的操作都是不矛盾的。换句话说，当应用 getMin 或者 removeMin 操作的时候，堆中有至少一个元素。

当Petya去吃午饭的时候，他的弟弟Vova进入了他的房间，拿走了Petya日志中的数页来做纸船。

现在Vova非常地焦虑，因为他可能已经让Petya的一系列操作变得前后矛盾。例如，如果一个一个地执行日志上所写着的操作，getMin操作所取得的结果可能与Petya记录的结果不同，而且如果这个时候堆是空的，那么 getMin 和 removeMin 操作将会产生错误。

Vova希望在日志中添加一些新的操作来让各项操作的结果正确。也就是说，每个 getMin 操作所得到的结果必须与日志中记录的相吻合，且不会出现操作前后矛盾或者导致错误。Vova想尽可能快地完成这些，因为Petya很快就会回来。现在Vova想要你在日志中添加尽可能少的操作纪录，这些记录可以被添加在日志的任何位置。

## 样例 #1

### 输入

```
2
insert 3
getMin 4
```

### 输出

```
4
insert 3
removeMin
insert 4
getMin 4
```

## 样例 #2

### 输入

```
4
insert 1
insert 1
removeMin
getMin 2
```

### 输出

```
6
insert 1
insert 1
removeMin
removeMin
insert 2
getMin 2
```

# 题解

## 作者：emo_male_god (赞：5)

### 题外话:
下面机房 + 红名大佬 **changwenxuan** 已经写得很详细了，但是我觉得有些部分讲的比较粗糙，所以写了这篇题解。

-------------
## [原题链接](https://www.luogu.com.cn/problem/CF681C)

**题目解析：**

1. 「insert $x$」 操作：直接将 $x$ 加入小根堆。
2. 「getMin $x$」 操作：表示在完整的堆操作里，堆中最小值为 x，注意！是**完整的**堆操作。
3. 「removeMin」 操作：pop 掉堆中最小的值，**这里埋个小小的伏笔**。

先给思路：我们维护一个**小根堆**，题目给什么操作我们就做什么操作。但是如果操作不合法，我们就要**分类讨论**。

### 不合法操作1：
 当前小根堆的最小值为 $x$，但是题目  getMin 函数返回的却比 $x$ 更小。

解决方法：在堆不为空的情况下，把比 $x$ 更大的数都 pop 掉，再 push 进 $x$。
 
-------------
### 不合法操作2：
 当前堆已经空了，但题目给了 getMin $x$ 函数。
 
 
解决方法：直接push $x$ 再 getMin $x$。
 
-------------
### 不合法操作3：
 当前堆已经空了，但题目给了 removeMin 函数。
 
 
解决方法：注意！这里要先随便 push 进一个合法的数，再 removeMin。（我就是在这里改了好几个小时[大哭]）
 
-------------
**注释**：以下代码中的 s 为题目给的函数，o 为函数中的值，ans 为存储输出的结构体数组，q 为小根堆，cnt 为最后输出操作的个数。（其实不用计数，直接输出数组的长度也可以）

-------------
insert 部分代码：
```cpp
if (s == "insert")
{
	cin >> o;
	q.push(o);
	ans.push_back({s, o});
	cnt ++ ;
}
```
-------------
 removeMin 部分代码：
```cpp
if (s == "removeMin")
{
	if (q.empty())//如果堆为空，要先随便insert一个数，再删除
	{
		ans.push_back({"insert", 114514});
		cnt ++ ;
		
		ans.push_back({s});
		cnt ++ ;
	}
	else//如果不为空，直接删除
	{
		q.pop();
		ans.push_back({s});
		cnt ++ ;
	}
}

```
-------------
getMin 部分代码：
```cpp
if (s == "getMin")
{
	cin >> o;
	if (q.empty())//如果堆为空，先insert再getMin
	{
		ans.push_back({"insert", o});
		q.push(o);
		cnt ++ ;
		ans.push_back({"getMin", o});
		cnt ++ ;
	}
	else//如果堆不为空，就继续判断
	{
		if (q.top() < o)//如果堆中有比o更小的数，就全部pop掉
		{
			while (!q.empty() && q.top() < o)//pop
			{
				q.pop();
				ans.push_back({"removeMin", q.top()});
				cnt ++ ;
			}
			if (q.empty())//如果pop完堆空了，直接insert
			{
				q.push(o);
				ans.push_back({"insert", o});
				cnt ++ ;
			}
			else if (q.top() != o)//如果还有数且不等于要查询的数，insert
			{
				q.push(o);
				ans.push_back({"insert", o});
				cnt ++ ;
			}
		}
		else if (q.top() != o)//如果堆中没有比o更小或等于的数，insert
		{
			q.push(o);
			ans.push_back({"insert", o});
			cnt ++ ;
		}
		ans.push_back({"getMin", o});//往答案数组里面加
		cnt ++ ;
	}
}
```
最后的代码没啥难度了，就不给了。

---

## 作者：SCAR_L (赞：3)

[博客食用更佳](https://www.luogu.com.cn/blog/Jiangyuchen-2010/solution-cf681c)

## Part 0: 前置芝士 
关于 C++ 的小根堆，简单说一下基本使用方法：

```cpp
priority_queue <int, vector<int>, greater<int> > q;// 定义int类型的小根堆

q.push(x) 	// 插入一个数

q.pop()		// 弹出优先级最高（最小）的数

q.size()	// 返回容器内元素个数

q.top()		// 返回优先级最高（最小）的数

q.empty()	// 返回优先队列（堆）是否为空
```


------------
## Part 1: 阅读与理解

简要题意：让你修正关于小根堆的指令集。  

修改方法见下文。

------------
## Part 2: 分析与解答

三种指令的修正方式：   

```insert x``` 操作不会出现错误，放心加入元素即可。
 
```getMin x``` 操作有两种错误类型：  
1. 优先队列队首**大于** $x$ 或队列为空：在当前指令前先将 $x$ 加入队列。
1. 优先队列队首**小于** $x$：弹出队首直到队首等于 $x$（正确）或小于 $x$（转换为错误情况 1）。

```removeMin``` 操作有一种错误类型：
1. 优先队列中没有任何元素：先往队列中加入**任意一个元素**，然后再执行操作。



------------


我第开始想用结构体（字符串 + 整型）来存储每条指令，思路上没什么问题：

 _代码-0x01（代码在文末）_ 

注意事项：           
1. 建议把每项操作写进函数，使代码更加简洁；
2. **在使用函数 ```pop()``` 和 ```top()``` 的时候，一定要先判断是否为空（```empty()```）！不然会 RE！**

但是当我写完代码提交时，发现有 2 个点 TLE 了！

~~经调查~~，我发现代码慢在储存 ```string``` 类型。

优化：把结构体（字符串 + 整型）改成（整型 + 整型），最后在输出的时候处理下就好了。

 _代码-0x02_ 
 
这样就通过了。

------------
## Part 3: 回顾与反思

本题难点：
1. 码量较大，需要仔细调试。
2. 数据范围较大，需要一些小优化。

本题还是很适合用作复习堆。

# [代码！](https://www.luogu.com.cn/paste/8bsj2p7k)

有问题或建议可在评论区指出，蒟蒻会随时改进的。

Ps：这是蒟蒻的第 3 篇题解。

---

## 作者：kevin1616 (赞：1)

### 审题
把一组可能会发生错误的操作在不改动原操作的基础上，添加其它操作，改为不会发生错误的一组操作。
***
### 方法
【队列模拟】用 STL 优先队列模拟整个过程，然后按照相应的错误修改操作，此方法可行。
***
### 思路
首先，`insert` 操作不可能出错，过。

其次，`getMin` 操作有两种可能的错误情况：

1. 当队列为空或队内最小值大于 $x$ 时，此时加入 $x$，此时最小值一定为 $x$。
2. 当队列非空且队内最小值小于 $x$ 时，此时要进入循环，每次移除最小值，然后每次查看当前最小值是否大于或等于 $x$，且判断是否为空，如果两者有一者为是的话，需要跳出循环。如果当前最小值大于 $x$ 或队列为空，即可把问题转换为“当队列为空或队内最小值大于 $x$ 时”这个问题；如果当前最小值等于 $x$，此时问题解决。

最后，`removeMin` 操作有一种可能的错误情况，即队列为空。此时添加一个数，再移除即可。

因为要统计个数，所以需要有一个数组存放答案，最后输出数组的长度及每个操作。

而且这道题有些卡输入输出，故推荐使用快读或格式化输入输出。
***
### 代码
```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#define int long long
using namespace std;
struct asdf{
    string n;
    int x;
};
int m;
string s;
priority_queue <int,vector<int>,greater<int> > q; //优先队列（小根堆）
int sum,cnt;
asdf a[300005]; //用于储存答案的数组
int site;
signed main(){
    scanf("%lld",&m);
    for(int i = 1;i <= m;i++){
        cin >> s;
        int x = 0;
        if(s == "insert"){ //插入无影响
            scanf("%lld",&x);
            q.push(x);
        }
        else if(s == "getMin"){ //最小值
            scanf("%lld",&x);
            if(!q.empty() && q.top() < x){ //如果队列非空且队内最小值小于x
                while(!q.empty() && q.top() < x){ //重复至为空
                    a[++site].n = "removeMin";
                    q.pop();
                }
            }
            if(q.empty() || q.top() > x){ //如果队列为空或队内最小值大于x
                a[++site].n = "insert"; //直接加入x
                a[site].x = x;
                q.push(x);
            }
        }
        else if(s == "removeMin"){ //删除最小值
            if(q.empty()){ //如果为空，加入一个数
                a[++site].n = "insert";
                a[site].x = 0;
                q.push(0);
            }
            q.pop();
        }
        a[++site].n = s; //加入该操作
        a[site].x = x;
    }
    printf("%lld\n",site); //输出长度
    for(int i = 1;i <= site;i++){ //输出每个操作
        cout << a[i].n;
        if(a[i].n != "removeMin") printf(" %lld",a[i].x);
        printf("\n");
    }
    return 0;
}
```
不抄题解，从我做起！

---

## 作者：YangXiaopei (赞：1)

这题其实是一道比较简单的模拟。

一看到题，其实就有一个比较清晰的思路——直接按题目写。

一共三种操作：
* 加入一个数 —— insert
* 删除最小数 —— removeMin
* 查询最小是否为 $x$ —— getMin

其中有时会不合法,目标是用一些操作让过程合法。

并且每种操作均与最小数有关，还需用小顶堆维护最小数。

* * *
#### 不合法操作：

removeMin：没有数

* 解决方法：加入 0，删掉 0（相当于啥也没做）.

getMin：没有数

* 解决方法：加入 $x$。

getMin：最小数大于 $x$

* 解决方法：加入 $x$。

getMin：最小数小于 $x$

* 解决方法：一直删除，直到最小数大于等于 $x$

这就是全部操作，模拟即可。
* * *
insert 操作
```cpp
void insert(string x, int y){
	cnt++;//后面还要输出操作次数
	c[cnt] = x + ' ' + to_string(y);//记录进c数组
	q.push(y);
}
```
* * *
removeMin 操作
```cpp
void removeMin(){
	if(q.empty()){//q为空才操作
	 	cnt++;
		c[cnt] = "insert 0";
		cnt++;
		c[cnt] = "removeMin";
     		//虽加入0再出去与结果没有任何变化，但输出还是要有的。
	}
	else{//q不为空的情况
		q.pop();
		cnt++;
		c[cnt] = "removeMin";
	}
	return;
}
```
* * *
getMin 操作
```cpp
void getMin(int x){
	if(q.empty()){//q为空
		cnt++;
		c[cnt] = "insert " + to_string(x);//加入x
		cnt++;
		c[cnt] = "getMin " + to_string(x);
		q.push(x);
	}
	else if(q.top() == x){
		cnt++;
		c[cnt] = "getMin " + to_string(x);//最小为x无矛盾
	}
	else if(q.top() > x){//最小大于x，加入x，最小为x
		cnt++;
		c[cnt] = "insert " + to_string(x);//加入x
		cnt++;
		c[cnt] = "getMin " + to_string(x);
		q.push(x);
	}
	else{
		while(!q.empty() && q.top() < x){//一直删除，直到最小数大于等于x
			q.pop();
			cnt++;
			c[cnt] = "removeMin";//删除操作
		}
      		//在最小数大于等于x后，重复上面操作。
		if(q.empty()){//q为空
			cnt++;
			c[cnt] = "insert " + to_string(x);
			cnt++;
			c[cnt] = "getMin " + to_string(x);
			q.push(x);
		}
		else if(q.top() == x){//最小为x,无矛盾
			cnt++;
			c[cnt] = "getMin " + to_string(x);
		}
		else if(q.top() > x){//最小大于x的操作
			cnt++;
			c[cnt] = "insert " + to_string(x);
			cnt++;
			c[cnt] = "getMin " + to_string(x);
			q.push(x);
		}
	}
	return;
}
```
* * *
最后，完整代码
```cpp
#include<bits/stdc++.h>
//#define int long long
//这里不必用long long,不会爆
using namespace std;
int n, cnt;
string  c[1000005];
priority_queue<int, vector<int>, greater<int> > q;
void rem(){
	if(q.empty()){
		cnt++;
		c[cnt] = "insert 0";
		cnt++;
		c[cnt] = "removeMin";
	}
	else{
		q.pop();
		cnt++;
		c[cnt] = "removeMin";
	}
	return;
}
void get(int x){
	if(q.empty()){
		cnt++;
		c[cnt] = "insert " + to_string(x);
		cnt++;
		c[cnt] = "getMin " + to_string(x);
		q.push(x);
	}
	else if(q.top() == x){
		cnt++;
		c[cnt] = "getMin " + to_string(x);
	}
	else if(q.top() > x){
		cnt++;
		c[cnt] = "insert " + to_string(x);
		cnt++;
		c[cnt] = "getMin " + to_string(x);
		q.push(x);
	}
	else{
		while(!q.empty() && q.top() < x){
			q.pop();
			cnt++;
			c[cnt] = "removeMin";
		}
		if(q.empty()){
			cnt++;
			c[cnt] = "insert " + to_string(x);
			cnt++;
			c[cnt] = "getMin " + to_string(x);
			q.push(x);
		}
		else if(q.top() == x){
			cnt++;
			c[cnt] = "getMin " + to_string(x);
		}
		else if(q.top() > x){
			cnt++;
			c[cnt] = "insert " + to_string(x);
			cnt++;
			c[cnt] = "getMin " + to_string(x);
			q.push(x);
		}
	}
	return;
}
signed main(){
	cin >> n;
	for(int i = 1; i <= n; i++){
		string s;
		cin >> s;
		if(s == "insert"){
			int y = 0;
			cin >> y;
			cnt++;
			c[cnt] = s + ' ' + to_string(y);
			q.push(y);
		}
		else if(s == "removeMin"){
			rem();
		}
		else{
			int x;
			cin >> x;
			get(x);
		}
	}
	cout << cnt << "\n";
	for(int i = 1; i <= cnt; i++){
		cout << c[i] << "\n";
	}
	return 0;
}
```

### 结束撒花！！

---

## 作者：xzggzh1 (赞：1)

没看到 c++ 的题解，就来写一篇好了。

题意：

给你部分小根堆的操作，让你补全所有操作。

操作包含三种：

1.插入元素。

2.删除一个最小元素。

3.查询最小元素。

---

首先，c++的STL中已经内置了优先队列的容器，所以可以直接拿来用。

以下是实现小根堆基本操作。

```cpp

priority_queue <int,vector<int>,greater<int> > q;//定义小根堆

q.push(x);//插入一个数

q.pop();//弹出堆顶的数

q.size();//返回容器内元素个数

q.top();//返回堆顶的数

```

然后考虑原题，思路是模拟。

稍加思考可以轻易知道：无论堆中状态如何，都可以实现第三个操作（最纯的方法就是弹出所有数，再加入一个数）。

所以我们对于前两个操作可以不用修改，直接加入或删除。

但是每到第三个操作就把所有数弹出的策略显然不能通过，所以我们考虑优化：

若查询的元素是最小的元素，什么都不用做。

若查询的元素比堆内最小的元素还小，直接插入该元素即可。

若查询的元素大于堆内最小的元素，弹出堆顶元素直至堆为空或者堆内最小元素比该元素小，最后再插入该元素。

---

除了以上谈到的之外，本题还有一些细节需要注意。

具体可以看代码:

```cpp
#include<bits/stdc++.h>
#define pii pair<int,int > 
#define mp make_pair 
using namespace std;
const int Maxn=1e6+5;
char op[20];
priority_queue<int,vector<int>,greater<int> >q;
inline int R()
{
    char c;int res,sign=1;
    while((c=getchar())>'9'||c<'0') if(c=='-') sign=-1;res=c-'0';
    while((c=getchar())>='0'&&c<='9') res=res*10+c-'0';
    return res*sign;
}
int n,x,top;
pii h[Maxn];
int main()
{
	n=R();
	while(n--)
	{
		cin>>op;
		if(op[0]=='i')
		{
			x=R();
			h[++top]=mp(1,x);
			q.push(x);
		}	
		else if(op[0]=='r') 
		{
			if(q.empty())
			{
				h[++top]=mp(1,0);
				h[++top]=mp(2,0);
				continue;
			}
			h[++top]=mp(2,0);
			q.pop();
		}
		else if(op[0]=='g')
		{
			x=R();
			if(q.empty())
			{
				h[++top]=mp(1,x);
				q.push(x);
				h[++top]=mp(3,x);
				continue;
			}
			int y=q.top();
			while (y<x)
			{
				if(q.empty())
				{
					h[++top]=mp(1,x);
					q.push(x);y=x;
					break;
				}
				h[++top]=mp(2,0);
				q.pop();y=q.top();
			}
			if(y>x)
			{
				h[++top]=mp(1,x);
				q.push(x);y=x;
			}
			h[++top]=mp(3,x);
		}
	}
	printf("%d\n",top);
	for(int i=1;i<=top;i++)
	{
		if(h[i].first==1) printf("insert %d\n",h[i].second);
		if(h[i].first==2) puts("removeMin");
		if(h[i].first==3) printf("getMin %d\n",h[i].second);
	}
}
```


---

## 作者：liuzhongrui (赞：0)

## 题意简述：

这道题是要修改日志中的操作记录，使得执行这些操作时不会产生错误或矛盾。具体来说，要保证 ```getMin``` 操作得到的结果与记录一致，并且在执行 ```getMin``` 和 ```removeMin``` 操作时堆中至少有一个元素。

给定了日志中剩余的操作数量 $n$ 和每个操作的描述，需要输出最小可能的操作数量 $m$ 以及修改后的正确日志。

## 具体思路：

1. 遍历日志中的每个操作，根据操作类型分别处理：
   - 对于插入操作 ```insert x```，直接记录该操作，并将元素 $x$ 加入 multiset 中，并更新操作数量 $m$。
   - 对于移除最小元素操作 ```removeMin```，如果此时 $heap$ 为空，则添加一个插入操作 ```insert 1```，再记录 ```removeMin``` 操作，并从 multiset 中删除最小元素，同时更新操作数量 $m$。
   - 对于获取最小元素值 ```getMin x```，检查 multiset 中最小元素是否小于 $x$，若是，则依次进行移除最小元素操作，直到 multiset 为空或最小元素大于等于 $x$，然后判断是否需要插入新的元素，最后记录当前 ```getMin``` 操作，并更新 $m$。

2. 输出修改后的操作数量 $m$ 和对应的操作日志。

代码实现中可以使用 multiset 作为堆的数据结构，通过模拟执行完整的操作流程来完成日志的修改，确保结果的一致性与正确性。

综上所述，通过遵循以上算法思路，即可完成对日志的修改工作，使得操作执行不会导致错误或矛盾。

## Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int c,i,n,k,b[400004],m;
string t,a[400004];
multiset<int>s;
int main(){
	cin>>n;
	for(i=0;i<n;i++){
		cin>>t;
		if(t[0]=='i'){ cin>>c; a[k]=t;b[k++]=c; s.insert(c);m++;} else
		if(t[0]=='r'){
			if(m==0){a[k]="insert"; b[k++]=1;s.insert(1);m++;}
			a[k++]=t;s.erase(s.begin());m--;
		} else{
			cin>>c;
			while(*s.begin()<c && m>0){
				a[k++]="removeMin"; s.erase(s.begin()); m--;
			}
			if(m==0 || *s.begin()>c){a[k]="insert"; b[k++]=c;s.insert(c);m++;}
			a[k]=t;b[k++]=c;
		}
	}
	cout<<k<<endl;
	for(i=0;i<k;i++){
		if(a[i][0]=='r')cout<<a[i]<<endl;
		else cout<<a[i]<<" "<<b[i]<<endl;
	}
}
```

---

## 作者：Lian_zy (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF681C)

# 分析
本题需要维护一个小根堆,如果你不会，请移步板子：[P3378 【模板】堆](https://www.luogu.com.cn/problem/P3378)。

我们来对三个操作逐一分析。

### insert
这个没有违规的情况，直接加入即可。

### getMin

这个有两个情况：

堆为空：此时需要在前面加入 $x$ 再执行操作。

堆顶（最小值）不为 $x$：重复执行直到堆顶大于等于 $x$，此时如果堆顶大于 $x$，则还要再添加一个 `insert x` 操作。

### removeMin
这个只有一个情况：堆为空。

此时添加任意一个数即可。


思路比较好想，代码比较简单，就不贴了。

---

## 作者：rq_kyz (赞：0)

# 【题解】 Heap Operations

### 传送门

[Heap Operations](https://www.luogu.com.cn/problem/CF681C)

---

### 题目

给定一个小根堆，并给出 $n$ 个操作，分别为一下 $3$ 类：

>insert x——将一个值为 $x$ 的元素插入堆中；
>
>getMin x——这个时候，堆中最小的元素的值为 $x$；
>
>removeMin——移除堆中最小的元素(若有多个相同，只移除其中的一个)。

但直接执行可能会出现错误，请在原操作的基础上增加一些操作，使得原操作合法（当然新操作也得合法）。

---

### 分析

本题可以直接模拟，对于每个不合法操作单独分析。

**Part 1：insert x**

这类操作没有不合法操作，直接加入堆里即可。

**Part 2：getMin x**

首先，堆顶元素可能小于 $x$，所以我们需要先将小于 $x$ 的元素都弹出。

但弹出后可能还有问题，那就是堆顶元素大于 $x$ 或堆为空，这时我们需要手动加入元素 $x$。

上面的操作保证了堆顶元素一定为 $x$，然后我们再执行 `getMin x` 就没问题了。

**Part 3：removeMin**

这类操作只有一个不合法情况：堆为空。因为执行操作时并没有规定弹出的数为多少，所以我们只需要手动添加一个随机的数就行了。**但要注意，题目规定堆中的数不能超过 $10^9$**，所以写 $114514$ 的时候别把 $1919$ 一起加上去了（这里我改了半天，悲……）。

另：我发现 CF 上没有 C++14，所以使用 C++14 提交会 UKE。

---

### 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll h[1000001],len=0;
bool f(ll num1,ll num2){
	return num1>num2;
}
struct s{
	ll op,x;
}a[1000001];
int main(){
	ll n,m=0;
	scanf("%lld",&n);
	while(n--){
		char c;
		scanf("\n%c",&c);
		if(c=='i'){
			ll x;
			scanf("nsert %lld",&x);
			h[len++]=x;
			push_heap(h,h+len,f);
			a[++m]={1,x};
		} else if(c=='g'){
			ll x;
			scanf("etMin %lld",&x);
			while(len && h[0]<x){
				pop_heap(h,h+len,f);
				len--;
				a[++m]={3,0};
			}
			if(!len || h[0]>x){
				h[len++]=x;
				push_heap(h,h+len,f);
				a[++m]={1,x};
			}
			a[++m]={2,x};
		} else {
			scanf("emoveMin");
			if(!len){
				h[len++]=114514;
				push_heap(h,h+len,f);
				a[++m]={1,114514};
			}
			a[++m]={3,0};
			pop_heap(h,h+len,f);
			len--;
		}
	}
	printf("%lld",m);
	for(ll i=1;i<=m;i++){
		if(a[i].op==1)
			printf("\ninsert %lld",a[i].x);
		else if(a[i].op==2)
			printf("\ngetMin %lld",a[i].x);
		else
			printf("\nremoveMin");
	}
	return 0;
}
```

---

## 作者：__LiChangChao__ (赞：0)

## 思路
构造一个操作序列？考虑**模拟**。

由于要维护最小值，使用**小根堆**进行模拟。

这一道题没有太大的思维难度，只要把几种情况捋清楚就行了：

`insert` 操作：直接将 $x$ 加入小根堆。

`getMin` 操作：先判断最小值是不是 $x$，是则不做其他操作，不是分以下几种情况：

* 堆为空，把 $x$ 加入堆。

* 堆顶元素 $y< x$，持续把 $y$ 出堆，直到 $y>x$（下一种情况）或堆为空（上一种情况）或 $x=y$。

* 堆顶元素 $y>x$，直接把 $x$ 加入堆即可。

`removeMin` 操作：如果堆为空，则随便加入一个值再出堆，否则直接将最小值出堆。

然后就能写出代码啦。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+5;
priority_queue<long long, vector<long long>, greater<long long> > a;
string s;
long long num,n,cnt;
struct node {
	long long x,y;
} q[maxn];
int main() {
	scanf("%lld",&n);
	for(int i=1; i<=n; i++) {
		cin>>s;
		if(s=="insert")scanf("%lld",&num),a.push(num),q[++cnt].x=1,q[cnt].y=num;
		if(s=="getMin") {
			scanf("%lld",&num);
			while(!a.empty()&&a.top()!=num) {
				if(a.top()>num)a.push(num),q[++cnt].x=1,q[cnt].y=num;
				else q[++cnt].x=2,a.pop();
			}
			if(a.empty()) {
				q[++cnt].x=1;
				q[cnt].y=num;
				a.push(num);
			}
			q[++cnt].x=3,q[cnt].y=num;
		}
		if(s=="removeMin") {
			if(a.empty()) {
				q[++cnt].x=1;
				q[cnt].y=1;
				a.push(1);
			}
			q[++cnt].x=2;
			a.pop();
		}
	}
	printf("%lld\n",cnt);
	for(int i=1; i<=cnt; i++) {
		if(q[i].x==1) {
			printf("insert %lld\n",q[i].y);
		}
		if(q[i].x==2) {
			printf("removeMin\n");
		}
		if(q[i].x==3) {
			printf("getMin %lld\n",q[i].y);
		}
	}
}
```

---

## 作者：ggtmjts (赞：0)

	--------------------------------------------------
    这道题用到的是堆，C++可以调用函数，好羡慕
    思路：小根堆。
    遇到insert直接加入到堆中
    removeMin如果堆中有数直接删，否则加1个insert 1操作
    getMin如果堆中没有数就直接加后面的数
    否则如果最小的是正确的不用加操作，不对分太大和太小
    太大直接insert这个最小的数
    太小先要把小的删去添加removeMin操作，删完不相等或没有数了
    就加入对并加操作。
    具体见代码。
    code：
	var i,n,t,w,x,te,son:longint;s,ss:string[20];
	a:array[0..500000]of longint;
	b:array[0..500000]of string[20];
	procedure up(x:longint);    //这下面2个子程序是堆
	begin
	while(x div 2>0)and(a[x]<a[x div 2])do
	  begin
	  te:=a[x];a[x]:=a[x div 2];a[x div 2]:=te;
	  x:=x div 2;
	  end;
	end;
	procedure down(x:longint);
	begin
	while x*2<=t do	
	  begin
	  son:=x*2;	
	  if(x*2+1<=t)and(a[son]>a[x*2+1])then son:=x*2+1;
	  if a[son]>=a[x] then break;
	  te:=a[x];a[x]:=a[son];a[son]:=te;
	  x:=son;
	  end;
	end;
	begin
	readln(n);
	for i:=1 to n do
	  begin
	  readln(s);      ss:=s;    //保存这个操作
	  if s[1]='i'then          //insert操作直接加
	    begin
	    delete(s,1,pos(' ',s));
	    inc(t);val(s,a[t]);up(t);
	    end
	  else
	    if s[1]='r'then      //删除操作    
	      begin
	      if t=0 then      //堆为空
	        begin
	        inc(w);b[w]:='insert 1';
           end
	     else
	        begin
	        a[1]:=a[t];dec(t);down(1);
	        end;
 	     end
	    else
	      begin
	      delete(s,1,pos(' ',s));
	      val(s,x);
	      if t=0 then   //堆为空直接加
	        begin
	        inc(w);str(x,b[w]);b[w]:='insert '+b[w];
            inc(t);a[t]:=x;up(t);
	        end
	      else
	        if a[1]<>x then   //最小值不相等
	          begin
	          if a[1]>x then  //太大直接加
	            begin
	            inc(w);str(x,b[w]);b[w]:='insert '+b[w];
                inc(t);a[t]:=x;up(t);
 	            end
	          else
	            begin
	            while(t>0)and(a[1]<x)do//删去小于规定最小值的
	              begin
	              a[1]:=a[t];dec(t);down(1);
	              inc(w);b[w]:='removeMin';
	              end;
	            if(t=0)or(a[1]<>x)then//空和不相等
	              begin
	              inc(w);str(x,b[w]);b[w]:='insert '+b[w];
                  inc(t);a[t]:=x;up(t);
	              end;
	            end;
	          end;
	      end;
	     inc(w);b[w]:=ss;
	    end;
	writeln(w);
	for i:=1 to w do writeln(b[i]);
	end.
    ------------------------------------------------

---

