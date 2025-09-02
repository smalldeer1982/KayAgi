# Dima and Containers

## 题目描述

# Dima和容器


Dima 的生日快到了！这是个重要的日子！Saryozha 送给 Dima的礼物是，他会离开房间，不打扰 Dima 和 Inna 庆祝生日。Inna 送给 Dima 的礼物是一个堆栈（stack）、一个队列（queue）和一个双端队列（deck）。

Inna 希望她的礼物能向 Dima 展示他是多么优秀的程序员。为此，她会逐个给 Dima 发送命令。有两种类型的命令：

1. 将给定的数字添加到其中一个容器中。对于队列和堆栈，你只能将元素添加到末尾。对于双端队列，你可以将元素添加到开头或末尾。
2. 从至多三个不同的容器中提取一个数字。将所有提取出的数字告诉 Inna，然后清空所有容器。对于队列容器，你只能从开头提取数字。对于堆栈容器，你只能从末尾提取数字。对于双端队列容器，你可以从开头或末尾提取数字。你不能从空容器中提取数字。

每次 Dima 执行第二类型的命令时，Inna 就会亲吻 Dima 若干次（可能为零）。Dima 非常了解 Inna，他确定这个数字等于他在此操作中从容器中提取的数字之和。

正如我们之前说的，Dima 非常了解 Inna，他知道 Inna 将给他什么命令以及命令的顺序。帮助 Dima 找到让他在生日上获得尽可能多亲吻的策略！

## 样例 #1

### 输入

```
10
0
1
0
1
2
0
1
2
3
0
```

### 输出

```
0
pushStack
1 popStack
pushStack
pushQueue
2 popStack popQueue
pushStack
pushQueue
pushFront
3 popStack popQueue popFront
```

## 样例 #2

### 输入

```
4
1
2
3
0
```

### 输出

```
pushStack
pushQueue
pushFront
3 popStack popQueue popFront
```

# 题解

## 作者：流绪 (赞：4)

贪心+模拟？

我们先定义 a,b,c 三个变量来分别存队列，栈，双端队列的最大值，因为要每个数据结构里提取一个，又要最大，那我们贪心地把最大的三个放到三种数据结构里,其他的随便放哪都可以，我是放在双端队列的尾部。所以我们一重循环 i 遍历输入，然后二重循环 j 从当前的 i 开始往下做，记录最大值，等到 0 的时候，记录 j ,开另一个循环 k 开始遍历 i 到 j,如果是刚才记录的就输出 push 到三个数据结构,其他的 pushback 放到尾部,然后再根据最大值有几个输出要弹出几个值就好啦,然后把 j 的值赋给 i，因为刚才 j 前面的已经遍历过了，我们跳过他们，然后一直往下就好啦

下面是 AC 代码,一些细节注释在里面了
```cpp
#include<bits/stdc++.h>
#define maxn 1000010
int p[maxn];
using namespace std;
int main()
{
	char pop[3][10]={"popStack","popQueue","popFront"};
	int n;
	cin >> n;
	for(int i=1;i<=n;i++)
		cin >> p[i];
	int a,b,c;
	for(int i=1;i<=n;i++)
	{
		a=b=c=0;
		int j=i;
		while(p[j]&&j<=n)
		{
			if(p[j] > a)
				c=b,b=a,a=p[j];
			else if(p[j] > b)
				c=b,b=p[j];
			else if(p[j] > c)
				c=p[j];
			j++;
		}//找到一个轮回
		if(!a&&!b&&!c)
			cout << 0 <<endl;//即没有输入值
		else
		{
			int cnt = 3;//记录最大值有几个
			if(!b)
				cnt--;
			if(!c)
				cnt--;//cnt 至少为1,否则上面就输出 0 了
			for(int k=i;k<j;k++)
			{
				if(p[k] == a)
				{
					cout << "pushStack\n";
					a=0;
				}
				else if(p[k] == b)
				{
					cout << "pushQueue\n";
					b=0;
				}
				else if(p[k] == c)
				{
					cout << "pushFront\n";
					c=0;
				}
				else//输出并清空,因为可能有其他值等于最大值,避免多输出了
					cout << "pushBack\n";
			}
			if(j > n)
				break;//注意可能最后没有 0,那么久不同弹出
			cout << cnt;
			for(int k=0;k<cnt;k++)
				cout << " " << pop[k];
			cout << endl;//弹出
			i=j;
		}
	}
}
```


---

## 作者：expecto__patronum (赞：2)

### 操作 1：
把数字 x 压入 3 种数据结构中的其中一种。

### 操作 2:
遇到输入 x==0 将弹出 3 个数据结构中的非受限端 。并且清空该数据结构。并且要求每次操作 2 弹出的数之和要最大。

每遇到操作 2 后，所用数据都清空，所以将两个 0 之间的数，分开来考虑。

因为 Deck 只能弹出一个数，所以可以选择其一端放没用的数。那么显然可以每次遇到操作 2 都弹出前 3 大的数。

最大放 queue，次大放 stack，第三大放 Front，剩余的都放 Back。

## 上代码
```
#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef pair<int,int> ii;
const int N=2e+5;
int mk[5];
vector<ii> v;
string s[4]={"Queue","Stack","Front","Back"};
bool cmp(ii a,ii b)
{
	return a.se<b.se;
}
void calc()
{
	int ans=0;
	vector<int> res(v.size());
	sort(v.begin(),v.end());
	reverse(v.begin(),v.end());
	for(int i=0;i<v.size();i++)
		res[v[i].se]=3;
	for(int i=0;i<min(3,(int)v.
```
管理大大求过！！

[博客](https://blog.csdn.net/noone0/article/details/79368587)

---

## 作者：wish_ (赞：1)

### 思路

这道题是一个贪心+模拟。

1. 设置一个储存输入的数组 $o$（是 `long long` 类型）和一个输出答案的数组 $p$（是 `string` 类型）。

2. 因为贪心要取得队列，栈，双端队列的最大值，所以设置变量 $a,b,c$ 分别储存。

3. 其他的数为了方便我们放在双端队列的尾部。

4. 之后就是模拟。

#### 模拟：

- 先是输入，将输入值储存进数组 $o$ 中。

- 使用 $a,b,c$ 记录队列，栈，双端队列的最大值，等到 $0$ 的时候，记录 $j$。

- 从 $i$ 循环到 $j$，如果这个数是刚才记录的就输出 `push` 到三个数据结构。其他的 `pushback` 放到尾部。

- 根据最大值有几个，输出要弹出几个值。

- 因为在 $j$ 前面的已经循环判断过了， 所以把 $j$ 的值赋给 $i$，跳过他们。

#### 模拟代码

```cpp
	for(int i=1;i<=n;i++){
		a=b=c=0;
		j=i;
		while(o[j]&&j<=n){
			if(o[j]>a)c=b,b=a,a=o[j];
			else if(o[j]>b)c=b,b=o[j];
			else if(o[j]>c)c=o[j];
			j++;
		}
		if(!a&&!b&&!c)cout<<0<<endl;
		else{
			int cnt=3;
			if(!b)cnt--;
			if(!c)cnt--;
			for(int k=i;k<j;k++){
				if(o[k]==a)cout<<"pushStack\n",a=0;
				else if(o[k]==b)cout<<"pushQueue\n",b=0;
				else if(o[k]==c)cout<<"pushFront\n",c=0;
				else cout<<"pushBack\n";
			}
			if(j>n)break;
			cout<<cnt;
			for(int k=0;k<cnt;k++)
				cout<<" "<<p[k];
			cout<<endl;
			i=j;
		}
	}
```

那在模拟代码基础上加上输入和设置，就可以了。

在这设置的数组 $p$，不知道如何设置的，如下。

`string p[3]={"popStack","popQueue","popFront"};
`

[AC](https://www.luogu.com.cn/record/163050429)

---

## 作者：beigongbaishan (赞：0)

一道典型的贪心。
# 题意
有三个容器：栈、队列、双端队列。  

有两种操作：  
1.  把一个数放进任意容器。
2.  从三个容器中各取一个（不能从受限端取），要求三个数总和最大，最后清空容器。  
 
 如果输入非 0 元素执行操作一。  
 如果输入 0 执行操作二。

# 关于这三种数据结构
简单讲一下。 


1. 栈（stack）  
+ 重点：先进后出。
+ 定义：```stack <变量类型> 变量名```
+ 压入：```变量名 . push ( 压入元素 )```
+ 弹出：```变量名 . pop()```
+ 查询栈顶：```变量名 . top()```

2. 队列（queue）  
+ 重点：先进先出。
+ 定义：```queue <变量类型> 变量名```
+ 压入：```变量名 . push ( 压入元素 )```
+ 弹出：```变量名 . pop()```
+ 查询队首：```变量名 . front()```

3. 双端队列（deque）  
+ 重点：两端都能进出。
+ 定义：```deque <变量类型> 变量名```
+ 从队首压入：```变量名 . push_front ( 压入元素 )```
+ 从队尾压入：```变量名 . push_back ( 压入元素 )```
+ 从队首弹出：```变量名 . pop_front()```
+ 从队尾弹出：```变量名 . pop_back()```
+ 查询队首：```变量名 . front()```
+ 查询队尾：```变量名 . back()```

注：这些函数并非全部。
# 思路
很显然：栈和队列只能从一端弹出，如果被一个较小的数字堵住了弹出的通道，就得不到最优解。而双端队列的两端都能弹出，所以我们把小的数字压入双端队列的一端，把大的数字压入另一端，遇到提取指令就从另一端弹出，就能得到最优解。

代码就不附了，祝大家 AC++ 。

---

