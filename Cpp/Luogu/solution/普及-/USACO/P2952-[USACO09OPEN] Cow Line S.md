# [USACO09OPEN] Cow Line S

## 题目描述

Farmer John（以下简称 FJ）的 $N$ 头奶牛（用 $1 \dots N$ 编号）在直线上排队。一开始，这条线上没有任何奶牛，随着时间的推移，奶牛们会一个接一个地站到队伍的左边或右边。又过了一会儿，某些奶牛会从队伍里离开，去吃自己最喜欢的草料。

FJ 无法跟踪每一头奶牛，于是，他想让你来帮助他。

奶牛以 $1 \dots N$ 的顺序排队，并且离开的奶牛不会再次回来。数据将会给出 $S$（$1 \le S \le 100000$） 条指令，各占一行，分两种：

- $A$ 头奶牛加入了队列（还有一个参数，表示从左加入还是从右加入）；
- $K$ 头奶牛从左边或者右边离开了队列（还有两个参数，分别表示从左离开还是从右离开和离开多少头奶牛）。

输入的命令一定是可以执行的。

所有的操作结束后，你的程序应该以从左到右的顺序输出这个奶牛队列。数据保证最后的队列不空。

## 样例 #1

### 输入

```
10 
A L 
A L 
A R 
A L 
D R 2 
A R 
A R 
D L 1 
A L 
A R 
```

### 输出

```
7 
2 
5 
6 
8 
```

# 题解

## 作者：Sooke (赞：62)

楼上发的题解实在烦琐，这里教给大家一个 STL 的容器 deque，也就是高端的双向队列。

什么是双向队列？顾名思义，就是前面也可以进出，后面也可以进出的队列。本题中，序号不同的牛既可以从队列左边进出，也可以从队列左边进出，恰好可以用双向队列完美地解决。deque 的基本进入队列操作是 push\_front 和 push\_back，出队列操作是 pop\_front 和 pop\_back，都比原来的单向队列操作多了一些方向的描述。对于进入队列的牛的编号是多少，我们可以使用一个计数器变量 c，每进一头牛给它自增即可。

然而，deque 的时间复杂度可能比较高，平时练习队列的时候能手打最好避免使用，比赛时需要合理考虑时间复杂度酌情使用。

下面便是极短的代码：

```cpp
#include <iostream>
#include <deque>
using namespace std;
deque < int > Q;
int main(){
    int n , c=1 , k;
    char a , b;
    cin >> n;
    for(int i=1 ; i <= n ; i++){
        cin >> a >> b;
        if(a == 'A' && b == 'L') Q.push_front(c++); else
        if(a == 'A') Q.push_back(c++);  else
        if(b == 'L'){
            cin >> k;
            for(int j=1 ; j <= k ; j++) Q.pop_front();
        } else {
            cin >> k;
            for(int j=1 ; j <= k ; j++) Q.pop_back();
        }
    }
    while(!Q.empty()) cout << Q.front() << endl , Q.pop_front();
    return 0;
}
```

---

## 作者：Karl_Aurora (赞：14)

### 这应该是蒟蒻正式发布的第一篇题解，求资瓷啦
（之前写过一个水题的题解，不知道为什么发不了awa)


------------

首先，在切这道黄题前，我们先来看一个新的stl数据结构——deque。

deque，也就是双端队列，它具有普通队列的性质，同时还支持从两端插入。

双端队列需要有头文件`#include<deque>`（实际上，在头文件`#include<queue>`中就包括了双端队列的头文件，所以如果要同时使用stl中的队列和双端队列，只需要打队列的头文件），定义方式和队列类似，为`deque<类型>队列名`。

下面是一些双端队列常用的成员函数：
```cpp
push_front(x);//在队首添加一个元素，时间复杂度为O(1)
push_back(x);//同理，在队尾添加一个元素
front();//返回队首的数值，时间复杂度为O(1)
back();//同理，返回队尾的数值
pop_front();//删除队首元素，时间复杂度为O(1)
pop_back();//同理，删除队尾元素
size();//返回队列内元素个数，时间复杂度为O(1)
clear();//删除队列内所有元素，时间复杂度为O(n)
```
搞清楚deque的用法之后，这道题就迎刃而解了，只需要用deque来对题目每一步操作进行模拟。

下附代码：
```cpp
//xhyAKIOI出品，禁止典型zmxqs行为
#include<iostream>
#include<cstdio>
#include<deque>
using namespace std;
inline int read(){
    int W=0;bool f=false;char ch=getchar();
    while(ch<'0'||ch>'9'){f|=ch=='-';ch=getchar();}
    while(ch>='0'&&ch<='9'){W=(W<<3)+(W<<1)+(ch^48);ch=getchar();}
    return f?-W:W;
    //快速读入啦
}
inline void write(int x){
    if(x==0){putchar('0');return;}
    if(x<0){putchar('-');x=-x;}
    static char num[21];static int top=0;
    while(x){num[++top]=(x%10)^'0';x/=10;}
    while(top)putchar(num[top--]);
    //快速输出啦
}
deque<int>q;
char ch1,ch2;
int k,n,count;
int main(){
    cerr<<"xhytql,AKIOI!";
    n=read();
    for(int i=1;i<=n;i++){
        cin>>ch1>>ch2;
        if(ch1=='A'){//判断操作类型
            if(ch2=='L')q.push_front(++count);
            else q.push_back(++count);
            //判断操作位置
        }
        else{
            k=read();//读入删除个数
            if(ch2=='L'){for(int j=1;j<=k;j++)q.pop_front();}
            else{for(int j=1;j<=k;j++)q.pop_back();}
            //仍然是判断操作位置
        }
    }
    deque<int>::iterator it;
    for(it=q.begin();it!=q.end();it++){
        write(*it);putchar('\n');
        //用迭代器输出
    }
    return 0;
}
```
### 最后，蒟蒻在这里求支持啦

---

## 作者：mahao2002 (赞：11)

### **新手向**

刚开始做这道题因为懒得想就直接看的题解，但是感觉题解对新人都不大友好，所以我写了一份纯模拟的代码。

感觉这道题可以作为新手通过模拟理解队列实现过程的一道好题。

具体代码如下


------------

```
#include<cstdio>
#include<iostream>
using namespace std;
int n,a[10000010],l,r,now;

int main()
{
	cin>>n;
	l=r=5000000; l++; //使插入第一个数的时候实现l==r
	while(n--)
	{
		char o1,o2; int num;
		cin>>o1>>o2;
		if(o1=='A')  //操作
		{
			if(o2=='L') a[--l]=++now;  //方向
			else a[++r]=++now;
            /*
            可以写成
            else
            {
				r++;
                now++;
                a[r]=now;
			}
            */
		else
		{
			cin>>num;
			if(o2=='L') l+=num;
			else r-=num;
		}
	}
	for(int i=l;i<=r;i++) cout<<a[i]<<endl;
	return 0;
}
```

---

## 作者：ShineEternal (赞：10)

# 写在前面：如想获得更佳阅读效果，请点击[这里](https://blog.csdn.net/kkkksc03/article/details/85107973),如有任何疑问，欢迎私信作者！
# 题目链接：https://www.luogu.org/problemnew/show/P2952
# 分析：
这道题非常适合练习deque双端队列，~~既然是是练习的板子题了，建议大家还是练练deque，下面来简单讲解一下deque的一些操作。
## clear()：清空队列
## push_back()：从尾部插入一个元素。
## push_front()：从头部插入一个元素。
> deque双端队列的先进就在这里，它可以两端都支持同样的操作。

## size()：返回队列元素个数
## front()：返回队列首部元素。
## back()：返回尾部元素。
## pop_back()：弹出队尾元素。
## pop_front()：弹出队首元素。
## empty()：检查队列是否为空。
然后输出的方法多种多样，我选择使用迭代器，具体详见代码。
# 代码：

```cpp
#include<cstdio>
#include<deque>
using namespace std;
deque<int>q;
int main()
{
	int s;
	scanf("%d\n",&s);
	int cnt=0;
	for(int j=1;j<=s;j++)
	{
		char c1,c2;
		int c3;
		scanf("%c %c",&c1,&c2);
		if(c1=='A')
		{
			if(c2=='L')
			{
				q.push_front(++cnt);
			}
			else
			{
				q.push_back(++cnt);
			}
			if(j!=s)
			scanf("\n");
		}
		else
		{
			scanf("%d",&c3);
			if(j!=s)
			scanf("\n");
			if(c2=='L')
			{
				for(int i=1;i<=c3;i++)
				{
					q.pop_front();
				} 
			}
			else
			{
				for(int i=1;i<=c3;i++)
				q.pop_back();
			}
		}
	}
	deque<int>::iterator it=q.begin();
	for(it=q.begin();it!=q.end();it++)
	{
		printf("%d\n",*it);
	}
	return 0;
}
```



---

## 作者：恶灬心 (赞：5)

### List的模板题。 几乎用上了所有常用链表的操作。
[ list详解 ](http://www.cplusplus.com/reference/list/list/)

1.建立list
```
/*调用list库*/
#include<list>
list<T>L; 
/*T==该链表存储的数据类型*/
```
2.插入操作
```
/*头插入*/
L.push_begin((T)n);
/*尾插入*/
L.push_end((T)n);
// 注：T==该链表的数据类型；
```
3.查询,删除(等遍历类型的用法）
```
/*list 是一个链表 就不能像数组一样方便的调用，所以它存储简单，遍历困难，需要借助迭代器。*/
list<T>::iterator R;
/*定义一个list,T类型的迭代器R(下面全用R==iter演示）。*/
iter = L.begin();/*指向开头*/

iter = L.end();/*指向结尾*/

*iter /*代表的是iter指向的链表位置上的值*/

//遍历操作
/*1.从头开始-->到末尾*/
for(iter=L.begin();iter!=L.end();iter++)
{
  //......
}
/*2.从尾开始-->到头*/
//注意！L.end()并没有存数，所以上来就应该-1，而链表不支持直接使用L.end()-1的操作。
iter=L.end();
iter--;
for(;iter!=L.begin();iter--)
{
  //......
}
//此处并没有遍历到begin处 需要再补上。

//查询操作
iter = find(List.begin(),List.end(),(T)n);
/*此处find是c++自带的查询函数。查询完后会返回一个位置，如果找到则会返回目标位置，失败会返回结尾位置。*/
if(iter != List.end()) cout<<"find it"<<endl; 
else cout<<"not find it"<<endl;

//删除操作
L.pop_front();
L.pop_back();
/*头尾删除*/

for(iter=L.begin();iter!=L.end();)
L.erase(iter++);
iter=L.end();iter--;
for(;iter!=L.begin();)
L.erase(iter--);
/*遍历删除*/
```
注：本人初学list 如本题解有误 请指出，支持私信。
附代码：
```
#include <bits/stdc++.h>
#include <list>
using namespace std;
list<int>L;
int main()
{
	int n;
	cin>>n;
	int k=1;
	list<int>::iterator iter;
	for(int i=1;i<=n;i++)
	{
		char a,b;
		scanf("\n%c %c",&a,&b);
		if(a=='A')
		{
			if(b=='L') L.push_front(k);
			else L.push_back(k);
			k++;
		}
		else
		{
			int c;
			scanf("%d",&c);
			if(b=='L') 
			{
				iter=L.begin();
				for(int i=1;i<=c;i++) L.erase(iter++);
			}
			else
			{
				iter=L.end(); iter--;
				for(int i=1;i<=c;i++) L.erase(iter--);
			}
		}
	}
	for(iter=L.begin();iter!=L.end();iter++)
	{
		cout<<(*iter)<<endl;
	}
}
```

---

## 作者：fls233666 (赞：4)

**2020年2月14日更新：修正题解排版问题并进一步完善内容**

-----------

我们先来分析一下这题要我们实现的数据结构。这题要我们实现是数据结构具有以下两个特点：

1. **能从两端插入元素**；
2. **能从两端删除元素**。

于是，我想到了一个神奇的数据结构——**双端队列**！

下面，我来介绍一下 STL 中的双端队列（$\texttt{deque}$）。

------------

双端队列 $\texttt{deque}$ 是一个支持在两端插入或删除元素的线性存储空间。它相当于是 $\texttt{vector}$（动态数组）和 $\texttt{queue}$（普通队列）的结合。与 $\texttt{vector}$ 相比，$\texttt{deque}$ **支持在两端修改元素**。与 $\texttt{queue}$ 相比，$\texttt{deque}$ **支持随机访问**。下面我们介绍几个常用的操作：

- 创建双端队列：**deque<存储的元素类型>双端队列名**; （_具体使用方式参考其它 STL 容器的创建_ ）
- 随机访问：$\texttt{deque}$ 支持像数组一样的随机访问，使用方式就是 **双端队列名[下标]**;
- $\texttt{deque}$ 头送代器：**双端队列名.begin()**; （_具体使用方法参考 $\texttt{vector}$_）
- $\texttt{deque}$ 尾送代器：**双端队列名.end()**;（_具体使用方法参考 $\texttt{vector}$_）
- 访问队头元素：**双端队列名.front()**;  （_具体使用方法参考 $\texttt{queue}$_）
- 访问队尾元素：**双端队列名.back()**; （ _具体使用方法参考 $\texttt{queue}$_） 
- 从队头入队：**双端队列名.push_front(元素)**;
- 从队尾入队：**双端队列名.push_back(元素)**;
- 从队头出队：**双端队列名.pop_front(元素)**;
- 从队尾出队：**双端队列名.pop_back(元素)**;
- 清空队列：**双端队列名.clear()**;
- 查询队列的长度：**双端队列名.size()**;
- 查询队列是否为空：**双端队列名.empty()**;

以上操作中，清空队列的时间复杂度为 $O(n)$，其它的时间复杂度都是 $O(1)$。加粗的文字就是实现此操作的指令。

另外，请记住，使用前加上以下头文件：

	#include<deque>

------------

回到此题。

在了解双端队列后，我们来明确一下此题如何实现代码：

1. 读入字符，判断为哪一项操作，以及操作的位置（队头或队尾）；
2. 如果为添加操作，加入元素（使用 push_back 或 push_front）；
3. 如果为删除操作，读入要删除的元素数量，循环删除元素（使用 pop_front 或 pop_back）；
4. 最后使用随机访问 +size（像遍历数组一样输出）或 empty+front+pop_front（像堆一样一个一个的弹出并输出）循环输出整个队列的元素；

下面是代码：

```cpp
#include<iostream>
#include<deque>
using namespace std;
deque<int>line;  //建双端队列
int main(){
    int n,b=1;
  	//b为要入队的牛的编号
    cin>>n;  //读入操作数量
    char c,f;  //c为操作名称，f为操作的位置
    for(int k,i=0;i<n;i++){
        cin>>c>>f;  //读入操作
        if(c=='A'){  //加入元素
            if(f=='L')
                line.push_front(b);
            if(f=='R')
                line.push_back(b);
            b++;
        }
        if(c=='D'){  //删除元素
            cin>>k;
            if(f=='L')
                for(int i=0;i<k;i++)
                    line.pop_front();
            if(f=='R')
                for(int i=0;i<k;i++)
                    line.pop_back();
        }
    }
  	
  //输出
    for(int i=0;i<line.size();i++)
        cout<<line[i]<<endl;
                            
    //以下是输出的等价写法
    /*while(!line.empty()){
        cout<<line.front()<<endl;
        line.pop_front();
    }*/
    return 0;
}
```


---

## 作者：ADay (赞：4)

## 来篇Py题解
众所周知，Py的库函数很强大。那么，它一定有$deque$咯。  
没错，在$collections$库中有$deque$容器，我们用`from collections import deque`来导入它，初始化：`a=deque([])`来创建一个空的$deque$。  
### 基本操作：对于$deque:a$
- $a.append(x)$队尾添加$x$ 
- $a.appendleft(x)$队首添加$x$ 
- $a.pop()$弹出队尾元素（并作为返回值） 
- $a.popleft()$弹出队首元素（并作为返回值）
- $len(a)a$的元素个数

同时，它还支持所有列表操作，详见[Python列表](https://www.runoob.com/python3/python3-list.html)  
那么，这题完全可以通过上述函数解决：
```python
from collections import deque#导入
a=deque([])#初始化
cnt=0#奶牛编号
for t in range(int(input())):#t个操作
    s=input().split()#以空格分割输入
    if s[0]=='A':#插入
        cnt+=1#计数器+1
        if s[1]=='L':#左边
            a.appendleft(cnt)
        else:#右边
            a.append(cnt)
    else:#弹出
        if s[1]=='L':#左边
            for i in range(int(s[2])):
                a.popleft()
        else:#右边
            for i in range(int(s[2])):
                a.pop()
for i in a:
    print(i)#输出最后元素
```


---

## 作者：Graphcity (赞：4)

通过简化，这道题需要这些操作：

1. 往序列的左端插入一个数

2. 往序列的右端插入一个数

3. 往序列的左端和右端分别删除一些数

4. 输出整个序列

我们可以用两种数据结构来执行这些操作——`vector` 和 `deque` 。

---

vector 是 STL 库里面的一种自带容器，你可以用它来实现很多操作：

```cpp
#include<vector>//vector需要用到这个头文件

vector<int> v;//跟stack,queue类似

v.push_back(1);//在它的后面插入一个数

v.pop_back();//删除它最后一个数

v.size();//求它的大小

v.empty();//判断是否为空

v.begin();//返回头指针

v.end();//返回最后一个元素的后面位置

v.insert(位置,元素);//在某个位置插入某个数

v.erase(位置);//删除某个位置的元素

v[1];//vector也可以进行下标运算，从0开始
```

所以我们可以这样做：

```cpp
#include<bits/stdc++.h>
#include<vector>
using namespace std;

vector<int> v;
int s,cnt;

int main()
{
	scanf("%d",&s);
	for(register int i=1;i<=s;++i)
	{
		char a,b;
		cin>>a>>b;
		if(a=='A' && b=='L')
		{
			++cnt;
			v.insert(v.begin(),cnt);
		}
		if(a=='A' && b=='R')
		{
			++cnt;
			v.push_back(cnt);
		}
		if(a=='D' && b=='L')
		{
			int x;
			scanf("%d",&x);
			for(register int j=1;j<=x;++j)
				v.erase(v.begin());
		}
		if(a=='D' && b=='R')
		{
			int x;
			scanf("%d",&x);
			for(register int j=1;j<=x;++j)
				v.pop_back();
		}
	}
	for(register int i=0;i<v.size();++i)
		printf("%d\n",v[i]);
    return 0;
}

```

---

deque，即双端队列，即队头和队尾都可以加入和删除元素了。

```cpp
#include<queue>

deque<int> d;//与queue类似

d.push_back();//从队尾入队

d.push_front();//从队头入队

d.front();//取队头

d.back();//取队尾

d.pop_front();//弹出队头

d.pop_back();//弹出队尾

d.size();//判断大小

d.empty();//判断是否为空
```

我们也可以使用这种数据结构完成操作：


```cpp
#include<bits/stdc++.h>
#include<queue>
using namespace std;

deque<int> d;
int s,cnt;

int main()
{
	scanf("%d",&s);
	for(register int i=1;i<=s;++i)
	{
		char a,b;
		cin>>a>>b;
		if(a=='A' && b=='L')
		{
			++cnt;
			d.push_front(cnt);
		}
		if(a=='A' && b=='R')
		{
			++cnt;
			d.push_back(cnt);
		}
		if(a=='D' && b=='L')
		{
			int x;
			scanf("%d",&x);
			for(register int j=1;j<=x;++j)
				d.pop_front();
		}
		if(a=='D' && b=='R')
		{
			int x;
			scanf("%d",&x);
			for(register int j=1;j<=x;++j)
				d.pop_back();
		}
	}
	while(!d.empty())
	{
		printf("%d\n",d.front());
		d.pop_front();
	}
    return 0;
}

```

---

## 作者：浑生蓝瘦 (赞：3)

```
//deque真好用
#include<bits/stdc++.h>//万能头真好用 
using namespace std;
deque <int> d;//这里先定义为d,方便书写 
int main()
{
	char a,b;//用于判断输入的前两位 
	int n,k,num=0;//这个num圈起来，要考的 
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a>>b;
		if(a=='A')//判断第一位,把输入的内容先分为两种 
		{
			if(b=='L')//若第二位是L，则在队首插入 
			{
				d.push_front(++num);//把队首中插入num这一数字，num会不断变大，这样比较省事(划掉) 
			}
			else//若第二位是R，则在队尾插入，不用写if(b=='R') 
			{
				d.push_back(++num);//梅开二度，若第一位是R，则在队尾插入
			}
		}
		else//如果第一位不是'A',直接认定为要删除元素,则认定第一位为'D' 
		{
			if(b=='L')//三阳开泰 
			{
				cin>>k;
				for(int j=1;j<=k;j++)
				{
				d.pop_front();
			    }
			}
			else//四喜丸子 
			{
				cin>>k;
				for(int j=1;j<=k;j++)
				{
					d.pop_back();
				}
			}
		}	
	    }
		while(!d.empty()) cout << d.front() << endl , d.pop_front();//这边直接输出 
		return 0;
}
%%%抄题解小心屎名哦
//本人菜鸡，第一次写题解，求大佬放过. 
```


---

## 作者：StupidSeven (赞：3)

  这是一个彩笔的第二篇题解www

------------
  
  A了这~~水~~题之后，看了一下题解区，怎么全是写deque的dalao啊（枯了）

毕竟还没学deque，先用vector来练练吧

思路很清晰，用vector维护，然后~~暴力~~模拟

## 上代码
```
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define re register
#define Maxn 2000000
inline int read()//没怎么用的快读
{
    char c=getchar();int f=1,s=0;
    while(!isdigit(c)){if(c=='-')f=-1,c=getchar();}
    while(isdigit(c)){s=s*10+c-48;c=getchar();}
    return f*s;
}
vector<int> v;
int n,s,k;//分别表示事件数，计数器和第三、四种事件中的k
char x,y;
int main(){
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>x>>y;
        if(x=='A'){//加入
            s++;//计数器自加
            if(y=='L') v.insert(v.begin(),s);//加入左边
            else v.push_back(s);//加入右边
        }
        else{//离开
            if(x=='D')
                cin>>k;
                if(y=='L') v.erase(v.begin(),v.begin()+k);//左边k只奶牛离开
                else for(int i=0;i<k;i++) v.pop_back();//右边k只奶牛离开
        }
    }
    for(int i=0;i<v.size();i++) printf("%d\n",v[i]);//按顺序输出
    return 0;//完结撒花
} 
```
求管理员小哥哥给过QWQ



---

## 作者：lagranby (赞：1)

之前的题解写的都是利用数组模拟双向队列，实质上在不知道数据规模的情况下要么过分浪费了空间，要么会意外导致越界。因此比较保险的做法应当是利用双向链表来模拟整个过程，随时随地申请和释放空间，4个函数addleft，addright，popleft，popright控制题目所述的四种操作。


代码如下


```cpp
#include <iostream>
#include <string>

using namespace std;

struct cow
{
    int val;
    cow *left,*right;
};

cow *l,*r,*temp;

void addleft(int n)
{
    temp = new(cow);
    temp->val = n;
    if (l==NULL)
    {
        l=temp;
        r=temp;
        temp->left=NULL;
        temp->right=NULL;
    }
    else
    {
        l->left = temp;
        temp->right=l;
        temp->left=NULL;
        l=temp;
    }
}

void addright(int n)
{
    temp = new(cow);
    temp->val = n;
    if (r==NULL)
    {
        l=temp;
        r=temp;
        temp->left=NULL;
        temp->right=NULL;
    }
    else
    {
        r->right = temp;
        temp->left=r;
        temp->right=NULL;
        r=temp;
    }
}

void popleft(int n)
{
    for (int i=0;i<n;i++)
    {
        temp = l;
        l = l->right;
        delete temp;
    }
}

void popright(int n)
{
    for (int i=0;i<n;i++)
    {
        temp = r;
        r = r->left;
        delete temp;
    }
}

int main()
{
    int s;
    cin>>s;
    l = NULL;
    r = NULL;

    int count = 0;
    for (int i=0;i<s;i++)
    {
        string a,b;
        cin>>a>>b;
        if (a=="A"&&b=="L") addleft(++count);
        else if (a=="A"&&b=="R") addright(++count);
        else
        {
            int t;
            cin>>t;
            if (b=="L") popleft(t);
            else popright(t);
        }
    }
 
    while (l) 
    {
        cout<<l->val<<endl;
        l = l->right;
    }

    return 0;
}
```

---

## 作者：lshhhhhh (赞：1)

这题其实只要理解题目就很简单，可以用队列，从中间开始，模拟入队列和出队列的方法即可，用单调队列

int s,zuo,you,bian,k[200005];//zuo存左节点，you存右节点，k为队列，因为有100000个操作，为了保险，开200000的内存，bian存下一个入队列的牛的序号，伪代码如下，s是操作的个数

```cpp
    for(int i=1;i<=s;i++)
    {
        char a,b;
        cin>>a>>b;
        if(a=='D')
        {
            int c;
            cin>>c;
            if(b=='L')zuo+=c;
            else you-=c;
        }
        else
        {
            if(b=='L')bian++,zuo--,k[zuo]=bian;
            else bian++,k[you]=bian,you++;
        }
    }
    for(int i=zuo;i<you;i++)cout<<k[i]<<endl;
    return 0;
}
```

---

## 作者：Porsche (赞：1)

这道题好多人都用了数据结构，各种deque玄学操作
我的思路很简单，先int一个足够大的数组，然后把第一头奶牛从最中间输入，这样就不用在从左插入奶牛的时候把整队奶牛右移，不用担心TLE了（注意数组要足够大）

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1000001];//a数组存储奶牛
int x=50000,y=49999;//x标记最左端奶牛的位置,y标记最右端奶牛的位置
int sum;//sum记录第几头奶牛
int main()
{
	int S;
	char u,v;
	scanf("%d",&S);
	int k;
	while(S--)
	{
		scanf("\n%c %c",&u,&v);//玄学输入毁我一生
		if(u=='A')
		{
			sum++;//奶牛标号+1
			if(v=='L')a[--x]=sum;//左端插入,x标左移一位,并插入奶牛
			else a[++y]=sum;//右端插入,y标右移一位,并插入奶牛
		}
		if(u=='D')
		{
			scanf("%d",&k);
			if(v=='L')x+=k;//左端删除k个,直接更改左端标记x,其余不用处理
			else y-=k;//右端删除k个,更改右端标记y
		}
	}
	for(int i=x;i<=y;i++)//从左端标记起，右端标记结束输出
		cout<<a[i]<<endl;
	return 0;
}
```

---

## 作者：Sinwind (赞：0)

# 1.分析

1. 因为奶牛可以从队伍的两端加入或离开，符合双端队列$(deque)$的特点，故用双端队列。

- 双端队列参考：[C++ STL之双端队列(deque)](https://www.luogu.org/blog/Singularwind/cpp-stl-deque#)。

# 2.代码

```cpp
#include <iostream>
#include <deque>

using namespace std;

int s;              //事件次数
char ad;          	//增删
char lr;            //左右
int k;              //增删数量
int id = 1;         //编号
deque <int>line;    //双端队列

//处理事件
void work(void)
{
	if(ad == 'A')
	{
		if(lr == 'L')
		{
			line.push_front(id++);
		}
		else
		{
			line.push_back(id++);
		}
	}
	else
	{
		if(lr == 'L')
		{
			while(k--)
			{
				line.pop_front();
			}
		}
		else
		{
			while(k--)
			{
				line.pop_back();
			}
		}
	}
}

int main(void)
{
	cin >> s;
	for(int i = 0; i < s; i++)
	{
		cin >> ad >> lr;
		if(ad == 'D')
		{
			cin >> k;
        }
        work();
	}
	
	int size = line.size();
	for(int i = 0; i < size; i++)
	{
		cout << line[i] << endl;
	}
	
	return 0;
}
```


---

## 作者：蔡俊黠 (赞：0)

这题考deque的基本操作
#### deque的基本操作有：

```cpp
deque <int> q;//创建一个内容为int的双端队列q 

q.push_front(i);//将i插入队头

q.push_back(i);//将i插入队尾

q.pop_front();//弹出队头

q.pop_back();//弹出队尾

a=q.front();//将队头赋值给a

a=q.back();//将队尾赋值给a

q.empty();//判断队列是否为空 
```
然后就按照题目的意思来处理队列

#### code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,cnt;
deque <int> q;
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		char a,b; int c;
		cin>>a>>b;
		if (a=='A')
		{
			cnt++;
			if (b=='L') q.push_front(cnt);
			if (b=='R') q.push_back(cnt);
		}
		if (a=='D')
		{
			scanf("%d",&c);
			if (b=='L') while (c!=0) q.pop_front(),c--;
			if (b=='R') while (c!=0) q.pop_back(),c--;
		}
	}
	while (!q.empty()) 
	{
		printf("%d\n",q.front());
		q.pop_front();
	}
	return 0;
} 
```





---

## 作者：loi_hjh (赞：0)

本蒟蒻附上较短的代码，去除多余头文件（27lines），~~（双端队列是什么，蒟蒻不会）~~今天我来教大家一种超级bug的做法

附上代码：

```cpp
#include<map>
#include<list>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define in inline
#define ri register int
using namespace std;
int a[1001000],p=100000,q=100000,n,m=1,k;//a开到20w即可,p=100000因为我怂左端变成负数 
char b,c;
int main(){
	scanf("%d",&n);
	cin>>b>>c;
	a[p]=1;//第一个数一定是加，而且左右都一样，本来蒟蒻是在for里做的，那样会多输出一个1 
	for(ri i=2;i<=n;i++){
		cin>>b>>c;//scanf会读入空格回车，我怂 
		if(b=='A'){
			m++;//第几次加就是几 
			if(c=='L') a[--p]=m;//增加左端，模拟入队 
			else a[++q]=m;//增加右端 
		}
		else{
			scanf("%d",&k);
			if(c=='L') p+=k;//减少左端，模拟出队 
			else q-=k;//减少右端 
		}
	}
	for(ri i=p;i<=q;i++)
		printf("%d\n",a[i]);
	return ~~(0-0);
}


```

---

## 作者：蒟蒻lxy (赞：0)

deque裸题。。。
用STL模拟一下可以AC了。

```cpp
#include<bits/stdc++.h>
using namespace std;
deque<int> a;//双向队列STL
deque<int>::iterator pos;//迭代器
int n,bianhao,cd;
int main()
{
	cin >> n;
	while(n--)
	{
		char c;
		cin >> c;
		if(c=='A')
		{
			cin >> c;
			if(c=='R')
				a.push_back(++bianhao);//尾插
			else
				a.push_front(++bianhao);//头插
			cd++;
		}
		else
		{
			int m;
			cin >> c;
			if(c=='R')
			{
				cin >> m;
				for(int i=1;i<=m;i++)
					a.pop_back();
				cd-=m;
			}
			else
			{
				cin >> m;
				for(int i=1;i<=m;i++)
					a.pop_front();
				cd-=m;
			}
		}
	}
	for(pos=a.begin();pos!=a.end();pos++)//注：一定要用pos!=a.end()不能用pos<=a.end()，迭代器不一定是连续的
		cout << *pos << endl;
	return 0;
}

```

---

## 作者：Starduster (赞：0)

deque双向队列暴力膜
顺便一波`switch`和`case`

```cpp
#include<bits/stdc++.h>
using namespace std;
deque<int>q;
int cnt;
int main(int argc,char **argv){
	cin.tie(0);
	ios::sync_with_stdio(0);
	register char cmd,perm;
	register int num,n;
	cin>>n;
	while(n--){
		cin>>cmd;
		switch(cmd){
			case 'A':
				cin>>perm;
				switch(perm){
					case 'L':
						q.push_front(++cnt);
						break;
					case 'R':
						q.push_back(++cnt);
				}
				break;
			case 'D':
				cin>>perm>>num;
				switch(perm){
					case 'L':
						while(num--)q.pop_front();
						break;
					case 'R':
						while(num--)q.pop_back();
				}
		}
	}
	while(!q.empty())printf("%d\n",q.front()),q.pop_front();
	return 0;
} 
```

---

## 作者：Sshenyyyu (赞：0)

# 牛线
这题呢，可以用deque容器，也就是双端队列，挺方便的。
贴代码。。。
```
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <deque>
#include <cmath>
#include <iostream>
using namespace std;

const int Maxn=100001;

int n;
char a,b;
int c,index=1;

deque<int> q;//传说中神奇的双端队列

int main()
{
	cin>>n;
	while(n--) {
		cin>>a;
		if(a=='A') {
			cin>>b;
			if(b=='L') q.push_front(index),index++;//入队头
			if(b=='R') q.push_back(index),index++;//入队尾
		}
		else {
			cin>>b>>c;
			if(b=='L') {
				int x=0;
				while(!q.empty()&&x<c) {/计数，出队头
					q.pop_front();
					x++;	
				}
			}
			else {
				int x=0;
				while(!q.empty()&&x<c) {//计数，出队尾
					q.pop_back();
					x++;
				}
			}
		}
	}
	while(!q.empty()) {//输出最后情况
		cout<<q.front()<<endl;
		q.pop_front();
	}
	return 0;
}

```

---

## 作者：猪猪 (赞：0)

其实挺简单的，我用的字符串

然后被每行最后的回车卡了好久

```cpp
//我一直以为数据会像样例一样有回车。。
//然后用队列就行了
var dl:array[-100000..100000] of longint;
    t,w,tot,ii,i,j,wz,wz1,n,jyzsb:longint;
        s,s1,s2:string;
    begin
        t:=0;w:=0;//tot:=1;
        //dl[t]:=1;
        readln(n);
        for ii:=1 to n do
            begin
                readln(s);
                if s[1]='A' then
                    begin
                        if (s[length(s)-1]='L') or (s[length(s)]='L') then//往左边走
                            begin
                                dec(w);
                                inc(tot);
                                dl[w]:=tot;
                            end;
                        if (s[length(s)-1]='R') or (s[length(s)]='R') then//往右边走
                            begin
                                inc(tot);
                                dl[t]:=tot;
                                inc(t);
                            end;
                    end;
                if s[1]='D' then
                    begin
                        s1:='';s2:='';jyzsb:=0;
                        wz:=pos(' ',s);
                        for i:=wz+1 to length(s) do
                                if s[i]=' ' then
                                    begin
                                        wz1:=i;
                                        break;
                                    end;
                        for i:=wz+1 to wz1-1 do
                            s1:=s1+s[i];
                        for i:=wz1+1 to length(s) do//不要写成length（s）-1， 行末没有**回车！**
                            s2:=s2+s[i];
                        val(s2,jyzsb);
                        if s1='R' then
                                t:=t-jyzsb;
                        if s1='L' then
                                w:=w+jyzsb;
                    end;
            end;
                for i:=w to t-1 do writeln(dl[i]);
    end.
//其实jyz是我们机房的大牛
```

---

