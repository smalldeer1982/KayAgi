# 全部相加 Add All

## 题目描述

## 题意翻译
给你 $n$ 个数，求将这 $n$ 个数合并成一个数的成本（成本即为此次相加之和）的最小值。

## 说明/提示

对于 $100\%$ 的数据，$1 \leq n \leq 5 \times 10^3$，$1 \leq a_i \leq 10^{5}$。

## 样例 #1

### 输入

```
3
1 2 3
4
1 2 3 4
0```

### 输出

```
9
19```

# 题解

## 作者：asasas (赞：6)

[前置知识：哈夫曼树](https://baike.baidu.com/item/%E5%93%88%E5%A4%AB%E6%9B%BC%E6%A0%91/2305769?fr=aladdin)

这题就是合并果子。这两题的核心算法是**哈夫曼树**

哈夫曼树的实现需要用到**二叉堆**，也就是STL的priority_queue(STL万岁！)。

我们将所有元素进优先队列（小顶堆），每次取两个最小的值出队，再将这两个元素的和入队，每次累加其和，当队内元素只有两个时
```cpp
#include <bits/stdc++.h>
using namespace std;
int ans=0; 
int main(){
	int n,t;
	while(1){
	int b,c;
	cin >> n;
	if (!n) return 0;
	ans=0;
	priority_queue <int,vector<int>,greater<int> > a;//小根堆
	int x;
	for (register int i=1;i<=n;i++){
		cin >> x;
		a.push(x);//入队
	}
	while(a.size()>=2){
		b=a.top();a.pop();
		c=a.top();a.pop();//每次弹出两个元素
		ans+=b+c;//累加
		a.push(b+c);//再次放入
	}
	cout << ans << endl;//输出
}
} 
```
输出即可。

代码：


---

## 作者：StudyingFather (赞：5)

这道题和NOIP 2004年的合并果子好像没什么区别（其实是一样的），可以证明，将最小的两个数合并成一个数，可以获得最小开销。

所以呢，我们可以维护一个堆，每次从堆顶依次取出两个元素，将两数之和放入堆，并计算开销。

PS：本来可以用优先队列的，老师要求手写一个堆来当做练习，所以这里就不用STL偷懒了。
```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int heap[1000005],cnt;
void up(int p)
{
 while(p>=1&&heap[p]<heap[p/2])
 {
  swap(heap[p],heap[p/2]);
  p/=2;
 }
}
void down(int p)
{
 int s=p*2;
 while(s<=cnt)
 {
  if(s<cnt&&heap[s]>heap[s+1])s++;
  if(heap[s]<heap[p])
  {
   swap(heap[s],heap[p]);
   p=s;
   s=p*2;
  }
  else break;
 }
}
void insert(int x)
{
 heap[++cnt]=x;
 up(cnt);
}
int top()
{
 return heap[1];
}
void pop()
{
 heap[1]=heap[cnt--];
 down(1);
}
int main()
{
 int n;
 while(~scanf("%d",&n)&&n)
 {
  int ans=0;
  cnt=0;
  memset(heap,0,sizeof(heap));
  for(int i=1;i<=n;i++)
  {
   int a;
   scanf("%d",&a);
   insert(a);
  }
  while(cnt!=1)
  {
   int newa=0;
   ans+=top();
   newa+=top();
   pop();
   ans+=top();
   newa+=top();
   pop();
   insert(newa);
  }
  printf("%d\n",ans);
 }
 return 0;
}
```

---

## 作者：JRzyh (赞：2)

[UVA10954](https://www.luogu.com.cn/problem/UVA10954)

这就是合并果子啊，~~好像没啥好说的~~。


$$\text{Part1.贪心思路}$$

可以把合并过程看成一棵二叉树，把 $x$ 和 $y$ 合并可以看成

![graph.png](https://i.loli.net/2020/08/17/uC1xF7BtaIDSH5w.png)


那样例的最优解为：

![graph _2_.png](https://i.loli.net/2020/08/17/AU7R5qloNBk4S1C.png)

可以看出答案 $=\sum (a_i\times dep_i)$

假如要使这个尽量小，就要使较小元素的 $dep$ 尽量小，就是先合并。

所以每回找出 $a$ 中最小的和次小的，合并后放回，直到只剩一个数，但for循环查找肯定要TLE。


$$\text{Part2.堆}$$

<https://visualgo.net/zh/heap>

可以支持的操作，插入一个数，删除最大值，时间复杂度 $O(logn)$ ，查询最大值 时间复杂度 $O(1)$ 。

正好符合我们的要求。

但如何实现呢？ ~~欢迎来到ZYH口胡时间~~

堆就是一棵完全二叉树，他有以下特点：

若是大根堆，则父节点一定 **小于等于** 子节点。

若是小根堆，则父节点一定 **大于等于** 子节点。

也就是说根节点一定是最小/大的节点。$O(1)$ 查询可以做到。

如果要删除根节点，我们就拿最下面的一个节点来放到根的位置，但他一定不是最值，所以我们要调整，把他下放，直到他大于等于/小于等于子节点为止。

若要插入节点，把他放到最下面，再往上调整，直到他大于等于/小于等于子节点为止。

注意STL的优先队列就是用堆实现的。

code(STL):

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	while(1)
	{
		int n;
		cin>>n;
		if(!n)return 0;
		priority_queue<int,vector<int>,greater<int> >q;
		int ans=0;
		for(int i=1;i<=n;i++)
		{
			int x;
			cin>>x;
			q.push(x);
		}
		while(q.size()>1)
		{
			int x=q.top();q.pop();
			int y=q.top();q.pop();
			ans+=x+y;
			q.push(x+y);
		}
		cout<<ans<<endl;
	}
	return 0;
} 
```


---

## 作者：ljcljc (赞：1)

【分析】

毫无疑问，这道题用$O(NlogN)$排序做，肯定是会$TLE$的。所以，我们就要想另一种方法。身为$C++$党，我们有$STL$中一个叫优先队列的好东西，用它可以就可以提高效率，然后剩下的思路就很明确了，详情见代码。

【优先队列】

这里就不细说了QAQ，不会的可以参考[这个博客](https://blog.csdn.net/c20182030/article/details/70757660)

【AC代码】

~~文明你我他，不要抄代码~~
```cpp
#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;
int n;
int main()
{
    while(scanf("%d", &n) && n) {
        priority_queue<int,vector<int>,greater<int> > q; //定义从小到大的优先队列
        for(int i=1; i<=n; i++) {
            int x;
            scanf("%d", &x);
            q.push(x); //x入队列
        }
        int ans = 0;
        for(int i=1; i<n; i++) {
        	//取最小的两个元素
            int x = q.top();
            q.pop();
            int y = q.top();
            q.pop();
            ans += x+y; //代价
            q.push(x+y); //两个元素的和入队列
        }
        printf("%d\n", ans);
    }
    return 0;
}
```

---

## 作者：封禁用户 (赞：1)

## AD
博客同步：http://www.cinema000.xyz/945.ruby

STL建堆函数：http://www.cinema000.xyz/482.ruby
## 题意
就是经典的合并果子
## 分析
用一个堆就好了
## 代码
既然用一个堆，那就用STL的函数建一个堆吧！
```cpp
#include<cstdio>
#include<algorithm>
#include<functional>
#include<vector>

namespace OI{
	using std::vector;
	using std::push_heap;
	using std::pop_heap;
	using std::greater;
	using std::less;
}
using namespace OI;

template<class T>
class Heap{
	public:vector<T> v;
	public:Heap(){
		v.reserve(666666);
	}
	public:~Heap(){
		v.clear();
	}
	
	public:void push(T key){
		v.push_back(key);
		push_heap(v.begin(),v.end(),greater<T>());
	}
	
	public:void pop(){
		pop_heap(v.begin(),v.end(),greater<T>());
		v.pop_back();
	}
	
	public:T front(){
		return v[0];
	}
}; 

int main(){
	int n,x;
		
	while(scanf("%d",&n) == 1 && n){
		Heap<int> h = Heap<int>();
		for(int i = 0;i < n;i++){
			scanf("%d",&x);
			h.push(x);
		}
		int ans = 0;
		for(int i = 0;i < n - 1;i++){
			int a = h.front();h.pop();
			int b = h.front();h.pop();
			ans += a + b;
			h.push(a + b);
		}
		printf("%d\n",ans);
	}
	
	return 0;
}
```

---

## 作者：chenpengda (赞：0)

## 题目大意

有 $n$ 个数的一个集合，每次可以从中删除两个数，然后将其和放入集合，直到剩下一个数。每次操作的花费等于删除两数之和，求最小总花费。

## 题解

本题重题[合并果子](https://www.luogu.com.cn/problem/P1090)，而且是算法竞赛入门经典第$8$章的一道例题（$8-11$）。

其实这个题目相当于模拟哈夫曼编码的建立过程（[哈夫曼编码详解](https://blog.csdn.net/bjweimengshu/article/details/105383513)）其中哈夫曼编码的实现是每次从结点队列中取出最小的两个数，将它们的和加入队列。

实际上，由于$n$比较小，想要模拟哈夫曼编码的建立过程的话，可以考虑使用STL的偷懒大法：优先队列。

优先队列将元素赋予优先级，当访问元素时，元素具有的优先级越高，这个元素越靠前，所以队首元素是整个队列中优先级最高的元素。

比如，用`priority_queue<int> p`来声明一个越大的整数优先级越高的优先队列，用`priority_queue<int, vector<int>, greater<int> > q`来声明一个越小的整数优先级越高的元素。优先队列的用法是：用`push()`进行元素入队，用`pop()`进行元素出队，用`top()`获得队首元素。

这道题选择`priority_queue<int, vector<int>, greater<int> > q`。

从而，每次取出两个队首元素，将它们的和加入队列，重复执行 $n-1$ 次即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int main()
{
	priority_queue<int, vector<int>, greater<int> > q;//建立一个最小数为队首的优先队列
	while(cin>>n)
	{
		if(n==0)return 0;
		for(int i=1;i<=n;i++)
		{
			int x;
			cin>>x;
			q.push(x);//x进队
		}
		int ans=0;
		for(int i=1;i<n;i++)//执行n-1次还剩下最后一个数
		{
			int a=q.top();q.pop();
			int b=q.top();q.pop();//取出队列中最小的两个数
			q.push(a+b);ans+=a+b;//将答案累加这两个数的和，将这两个数的和进队
		}
		q.pop();//清空队列
		cout<<ans<<endl;
	}
} 
```


---

## 作者：_Luminous (赞：0)

### · 题意


------------
~~u1s1这题就是合并果子，题意显然（）~~

### · 解题思路 & 方法


------------

首先考虑最朴素的贪心方法：每合并一次都需要排一次序。但事实上这样会超时，所以我们就想到了C++福利——**堆**。（STL大法好！）

首先维护一个堆，每次从堆顶取出两个元素，将两数相加，把它们的和放入堆，并计算代价。~~然后这题就完美结束啦~~

### · Code


------------
```cpp
#include <iostream>
#include <queue>
using namespace std;
int n;
priority_queue<int,vector<int>,greater<int> > q;
int main(){
	while(cin>>n && n){
		int ans=0;
		for(int i=1,x;i<=n;i++){
			cin>>x;
			q.push(x);
		}
		while(q.size()>2){
			int x=q.top();
            q.pop();
            int y=q.top();
            q.pop();
            ans+=x+y;
            q.push(x+y);
		}
		int x=q.top();
        q.pop();
        int y=q.top();
        q.pop();
		cout<<ans+x+y<<endl;
	}
	return 0;
}
```


---

## 作者：Cripple_Abyss (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/UVA10954)

## STEP 1 大致题意：

与合并果子重题了，又没有翻译，直接点
[这里](https://www.luogu.com.cn/problem/P1090) 吧


## STEP 2 思考过程：
- 既然要让最终的值尽可能小。

- 我们就要让中间的每个值尽可能想。

- 我们不难想到了优先队列，不知道的同学点[优先队列](https://www.cnblogs.com/xzxl/p/7266404.html)

## STEP 3 题目解法：
1. 我们把所有元素放进优先队列中。

1. 每次把前两个元素弹出，将它们相加，放进优先队列中，并用 ans 进行累加。

1. 输出 ans 即可

## STEP 4 Code：

```cpp
#include <cstdio>
#include <iostream>
#include <queue>

using namespace std;

int main()
{
    while (1)
    {
        int n;
        scanf("%d", &n);
        
        if (n == 0)
            return 0;
            
        priority_queue<int, vector<int>, greater<int> > q;
        
        for (int i = 1; i <= n; i++)
        {
            int x;
            scanf("%d", &x);
            q.push(x);
        }
        
        int ans = 0;
        
        while (q.size() > 2)
        {
            int x = q.top();
            q.pop();
            
            int y = q.top();
            q.pop();
            
            ans += x + y;
            
            q.push(x + y);
        }
                
        // 特殊处理
        int x = q.top();
        q.pop();
        
        int y = q.top();
        q.pop();
             
        printf("%d\n", ans + x + y);
    }
    return 0;
}
```

都看到这里了，点个赞再走呗QwQ

---

## 作者：WanderingTrader (赞：0)

首先简述一下题意吧。

给定 $n$ 个数，每次取两个数相加的和作为操作答案，直到求出总和为止。输出每次操作答案之和的最小值。（语文水平有限，请谅解）

诶，这不是 合并果子 吗？
### 代码
既然和合并果子 **一毛一样** ，那我就不作过多解释了，维护一个小根堆，每次取队头两元素，相加后放回队列。给 $ans$ 加上相加的值即可。容易证明这种做法的正确性（贪心常用反证法）
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
priority_queue <ll,vector<ll>,greater<ll> > Q;
inline int read()
{
 	int x=0,f=1;
 	char c=getchar();
 	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
 	while(isdigit(c)){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
 	return x*f;
}
int main()
{
	int n=read();
	ll ans;
	while(n)
	{
		ans=0;
		while(n--)
			Q.push(read());
		while(Q.size()>1)
		{
			int a=Q.top();Q.pop();
			int b=Q.top();Q.pop();
			ans+=a+b;
			Q.push(a+b);
		}
		Q.pop();
		printf("%lld\n",ans);
		n=read();
	}
	return 0;
}
```
别忘了用longlong ~~十年OI一场空，没开LL见祖宗。~~
$$\texttt{The End.}$$

---

## 作者：菜鸡gyf (赞：0)

### 大致题意

有若干个数，每次加减可以把两数替换成两数之和，每进行一次加法需要花费，花费的金额等于两数之和，要使最后仅剩一个数，求最小的花费.

这道题显然是一道贪心题，先相加最小的两个，再排序一遍，可这样显然会 TLE 时间直接爆炸。

说到c++最大的优势，我们都会想到 STL，我们可以建一个堆来实现程序。
```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,ans=0;
	while(scanf("%d",&n))
	{
		priority_queue<int>que; 
		int i,x,tmp;
		if(n==0)
		return 0;//若n==0,结束程序 
		ans=0;
		for(i=0;i<n;++i)
		{
			scanf("%d",&x);
			que.push(-x);
		}//把数压入堆里 
		for(i=1;i<n;++i)//执行n-1次 
		{
			tmp=que.top();
			ans-=que.top();
			que.pop();//第一个数的操作 
			tmp+=que.top();
			ans-=que.top();
			que.pop();//第二个数的操作 
			que.push(tmp);//结果再放进去 
		} 
		printf("%d\n",ans);
	}
}
```


---

