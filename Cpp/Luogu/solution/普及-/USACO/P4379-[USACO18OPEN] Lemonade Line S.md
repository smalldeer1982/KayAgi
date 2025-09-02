# [USACO18OPEN] Lemonade Line S

## 题目描述

这是农场上一个炎热的夏日，Farmer John 要给他的 $N$ 头奶牛发柠檬汽水了！所有的 $N$ 头奶牛（编号为 $1 \dots N$）都喜欢柠檬汽水，只是有些喜欢的程度更高一些。具体来说，奶牛 $i$ 为了获得柠檬汽水，最多愿意排在 $w_i$ 头奶牛之后。现在所有的 $N$ 头奶牛都在田里，但只要 Farmer John 敲响牛铃，这些奶牛就会立刻赶到柠檬汽水站。她们会在 Farmer John 开始分发柠檬汽水之前到达，但没有两头奶牛会在同一时刻到达。此外，当奶牛 $i$ 到达时，当且仅当队伍中至多有 $w_i$ 头奶牛时，她才会加入队伍。

Farmer John 想要提前准备一定量的柠檬汽水，但他不想浪费。排队的奶牛数量可能取决于她们的到达顺序。请帮助他求出在所有可能的到达顺序下，最小的可能排队奶牛数量。


## 说明/提示

在这个情况下，可能最后仅有三头奶牛在队伍中（这也是最小可能值）。假设 $w = 7$ 和 $w = 400$ 的奶牛先到并等在队伍中。然后 $w = 1$ 的奶牛到达并且会离开，因为已经有 $2$ 头奶牛在队伍中了。接着 $w = 2$ 的两头奶牛到达，一头留下排队，另一头离开。

供题：Dhruv Rohatgi

## 样例 #1

### 输入

```
5
7 1 400 2 2```

### 输出

```
3
```

# 题解

## 作者：btc001 (赞：35)

# 这道题真的很水

### 不是我骄傲，而是我的代码是真的一句废话都没有

因为题目说要求尽可能少，所以我们就推出了一个简单的贪心思想，言归正传，言简意赅：

首先，把数组用sort函数排个序（如果连sort都不知道，就不要做普及组的题了）。

然后，再从后往前看，如果目前人（牛）数比这头牛的底线数量还多，就跳出这个循环。否则就把目前人（牛）数++。下面是思路，已经懂了的人可以跳过。

## 思路

为什么要从后往前呢？因为我们要保证牛的数量尽可能少，后面的牛底限会比前面
    
的大，如果把它放在了前面，那么牛的数量会变多，那些更不愿意排队的牛就会离     
去。在第一头牛离去之后，我们就可以不管后面的了，因为我们是倒着看的，所以
    
后面的牛更懒得排队，前面的牛都走了，后面的还留着干嘛？
    
以下是标程：

	#include <bits/stdc++.h>

	using namespace std;

	int main(){
	
    	int n;
	
    	cin >> n;
	
    	int a[n+1], sum=0;
	
    	for(int i=1; i<=n; i++) cin >> a[i];
	
    	sort(a+1, a+n+1);
	
    	for(int i=n; i>=1; i--){
	
    		if(a[i]>=sum)
		
        		sum++;
		
        	else break;
	
    	}
	
    	cout<<sum<<endl;
	
    	return 0;

	}

# 点个赞再走吧！

---

## 作者：hhhyyyfff (赞：15)

这道题是简单的贪心，只要按照wi**从大到小**排序，然后按这个顺序排队，排到奶牛不愿意再排队了，当前队伍中的奶牛数就是答案。因为后面的奶牛wi更小，不会再排队了，而且这样排队的奶牛数最少。

``` cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int a[100000],N;
inline bool cmp(int x,int y){
	return x>y;
}
int main(){
	scanf("%d",&N);
	for(int i=0;i<N;++i)
		scanf("%d",&a[i]);
	sort(a,a+N,cmp);
	for(int i=0;i<N;++i)
		if(a[i]<i){
			printf("%d\n",i);
			return 0;
		}
	printf("%d\n",N);
	return 0;
} 
```

---

## 作者：是真的囬气 (赞：5)

这道题要注意的是：两头奶牛不会同时到达柠檬汁摊，而且每头奶牛来的时间没有固定（要不然题目怎么 要求 找最小值(￣▽￣)"）。
按照题目的意思，其实我们要做的事就是：让尽可能少的奶牛加入队里面。这里用简单的贪心就可以解决：
令“忍耐”度低的奶牛排在后面，离开的可能性更高。或者是：令“忍耐”度高的奶牛排在前面：
然后，我们可以模拟一下这个过程：
当奶牛1先到达时，因为前面没有奶牛，所以奶牛1加入队列

当奶牛3到达时，前面只有1头奶牛，没有超过4，所以奶牛3加入队列

当奶牛4到达时，前面有2头奶牛，没有超过3，所以奶牛4加入队列

当奶牛2到达时，前面有3头奶牛，超过“忍耐”奶牛数1，所以奶牛2离开

所以，最终只有3头奶牛留下来，最小值为3。
我们写代码时模拟这个过程就可以了。
代码见下：
```c++
#include <cstdio>
#include <cstring>  
#include <iostream>  
using namespace std; 
const int maxn = 1e5+5;  
int w[maxn]; 
int cnt;
 bool cmp(int a, int b)
 { 
    return a>b;} 
    
int main(){  
   int n;
    scanf("%d", &n);
      for(int i = 0; i < n; i++){
        scanf("%d", &w[i]);  }
      sort(w, w+n, cmp); //排序 
       cnt = 0;
     for(int i = 0; i < n; i++){
        if(cnt <= w[i]){ //能排就排队  
          cnt++; } 
           } 
      cout << top << endl; 
     return 0;
}
```

---

## 作者：fls233666 (赞：4)

**2020年2月14日：根据要求修复题解格式**

---------

看到要求最少的最少的排队的奶牛数量，首先想到的就是**贪心**。

分析题目和样例可得：**如果想要排队的奶牛的数量最少，我们就要尽可能让 $w$ 值大的奶牛先排，这样 $w$ 小的奶牛就会离开。**  _这就是贪心策略_ 。

想出贪心策略后，**如何实现**？

要先排 $w$ 值大的，就要先把 $w$ 值排序。设奶牛排队的队列长度为$L$，大致归纳出一下的程序实现过程：

1. 读入数据，并把 $L$ 初始值设为 $0$；
2. 对所有的 $w$ 值排序；
3. 从大到小检查每个 $w$；
4. 如果当前 $w$ 的值大于或等于 $L$，则 $L+1$，表示这只奶牛排进队中；
5. 如果当前 $w$ 的值小于 $L$，跳出循环，**因为之后的 $w$ 都比 $L$ 小，无法更新 $L$ (即之后的奶牛都会选择离开)**；
6. ~~输出答案~~。

AC 代码如下：

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int main(){
    int n,l=0;
    cin>>n;
    int w[n];
    for(int i=0;i<n;i++)
        cin>>w[i];
  //读入数据
  
    sort(w,w+n);  //排序
    for(int i=n-1;i>=0;i--){
        if(l<=w[i])
            l++;
        else
            break;
    }
      //贪心更新L的值
     
    cout<<l;  //输出
    return 0;
}
```


---

## 作者：xuezhe (赞：3)

这道题，总体来讲就是这样的贪心思想：让 $w_i$ 大的奶牛先来排队，~~不想排队的奶牛去喝西北风~~。

正确性证明：

假设已经有 $s$ 头奶牛在排队，还有两头奶牛A和B等着来排队，他们分别能忍耐 $x_A$ 头和 $x_B$ 头奶牛( $x_A < x_B$ )，那么有一下几种情况：

(1) $s < x_A$ 

此时无论是哪种顺序，两只奶牛必然都会很情愿地来排队，不影响结果。

(2) $s = x_A$

此时若先让奶牛A来排队，再让奶牛B来排队，两头奶牛都会很情愿地排队，故排队的奶牛数量增长到 $s+2$ 。

反之，若先让奶牛B来排队，此时排队的奶牛数为 $s+1$ ，即 $x_A + 1$ ，此时奶牛A就不愿意来排队了，故最终结果为 $s+1$ 。

先让奶牛B来排队显然更优。

(3) $s > x_A$

此时无论是哪种顺序，奶牛A都不会来排队，不影响结果。

综上所述，先让 $w_i$ 更大的奶牛来排队能得到最优解。

Python3代码：

```
# -*- coding: utf-8 -*-
# 简述排序：由于本蒟蒻不会调整sort的优先级，
# 故直接将其相反数插入list，然后进行升序排序，
# 再将取出的数也取相反数，则最终结果为降序

input()
a=[-int(i) for i in input().split()]
a.sort()
s=0
for i in a:
    if s<=-i:
        s=s+1
print(s)
```

---

## 作者：半笙、凡尘 (赞：2)

# P4379 【[USACO18OPEN]Lemonade Line】
### 蒟蒻的题解，很好理解，但不一定是最优解，也不一定是最简便的做法


------------

~~简单地~~，根据题面，我们可以得出，这道题就是奶牛~~发脾气~~，每一只奶牛都不愿自己前面有$w[i]$只奶牛，而农夫$John$想要给出最少的饮料——就是要让排队的牛最少

要使得排队的牛最少,果断$sort$，将~~脾气最好~~（$w[i]$最大）的奶牛排在最前面，把其他奶牛都气走。。。由于每头奶牛都是一头一头来的，我们可以~~抽象成~~：一只奶牛来，先走进队伍，看到前面牛太多了，走回去，把下一只牛叫来，下一只牛走进队伍，看了看牛，如果牛太多就走，不多就留着。这一过程。。。

~~具体的~~，我们来看**注释**

------------

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,w[100010];
bool cmp(int x,int y){
	return x>y;//从大到小排
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&w[i]);//输入每头牛前面允许排的牛的个数
	}
	sort(w+1,w+1+n,cmp);//sort啦
	int wait=n,still=0;//wait代表最后在排的牛，我们把wait设置成最大，没气走一头就wait--。still为当前队伍里在排队的牛，初始为0
	for(int i=1;i<=n;i++){//从w[i]最大的牛开始枚举
		if(w[i]<still){//如果有牛已经等不下去了（在它前面排队的牛太多了）
			wait--;//它就被气走了，最后排队的牛的个数--
			still--;//还在排队的牛的个数--
		}
		still++;//如果它没有被气走，它就入队，如果他被气走了，仍然在排队的牛的数量不变
	}
	printf("%d",wait);
	return 0;
}
```


---

## 作者：dzy2008 (赞：1)

这道题目是一个明显的贪心题

分析题目，如果想要排队的奶牛的数最少，我们就要尽可能让 $w$ 大的奶牛先排，这样 $w$ 小的奶牛就会先离开。

$1.$ 我们需要定义两个东西:

```cpp
int n, w[100005];//n最大为100000，所以数组开到100005，w数组如题
```

$2.$ 读入部分

```cpp
cin >> n;
for(int i = 0; i < n; i++) cin >> w[i];
```

$3.$ 排序，这里排序需要从大到小排序（前面说的贪心策略），所以我们需要定义一个 $cmp$ 函数：

```cpp
sort(w, w + n, cmp);//从大到小排序，或者可以写成:sort(w, w + n, greater<int>() );
```

$cmp$ 函数：

```cpp
inline bool cmp(int x, int y) {
	return x > y;
}
```

这里顺便提一句：

$cmp$函数的含义：如果返回$true$，则序列中这两个数按照满足逻辑关系式的顺序，举个例子： $return (x > y)$ ，则如果返回 $true$ 的话，$x$ 要放在 $y$ 的前面

$4.$ 找答案，找到第一个 $i > w[i]$ 的奶牛坐标，并输出它，前面贪心策略说过

```cpp
for(int i = 0; i < n; i++) {
	if(w[i] < i) {
		cout << i;
		return 0;
	}
}
```


$5.$ 如果全部的 $w[i]$ 都大于等于 $i$ 时，我们就要输出n，因为前面 $return 0$ 了，所以不用if

```cpp
cout << n;
```

最后，附上精简版代码：

```
#include<iostream>
#include<algorithm>
using namespace std;
int w[100005], n;
inline bool cmp(int x, int y) {
	return x > y;
}
int main()
{
	cin >> n;
	for(int i = 0; i < n; i++) cin >> w[i];
	sort(w, w + n, cmp);
	for(int i = 0; i < n; i++) {
		if(w[i] < i) {
			cout << i;
			return 0;
		}
	}
	cout << n;
	return 0;
}
```




---

## 作者：yyandy (赞：1)

# 对于水题。。。力争简短
本题思路很简单，排序

假设最不利的情况：

忍耐度大的排在前面

后面忍耐度小的就肯定不排队了

。。。我很懒

code：
```
#include<bits/stdc++.h>
using namespace std;
int n,i,a[100010];
int main()
{
	cin>>n;
	for (i=1;i<=n;++i)
 	scanf("%d",&a[i]);
	sort(a+1,a+n+1);//排序，然而我懒得写cmp
	for (i=n;i>=0;--i)//因为排序，所以倒着查找
   //>=0,这是因为边界
	if (a[i]<n-i)
	{
		cout<<n-i;//忍耐度大的都走了，小的不用考虑
		return 0;
	}
}
```


---

## 作者：A_Big_Jiong (赞：1)

# 前言

~~本蒟蒻又来水题解啦!~~

一看见楼上的归并排序，本蒟蒻难受的一批（这么个大水题都能秀起来），最近也是看了许多贪心，就想用堆来水下这题。

------------
# 贪心思路

~~唉~这题问最少的奶牛数量也是坑了我啊！~~

不用任何过赘的证明，用脚趾头想想，问最少肯定**把wi最大的放在最前面**，这样肯定取到的值为最小值！

------------
# 关于优先队列（堆）
### 如果之前没有学过堆的话，建议去P3378看一下，这里只简单说明一下自己的代码
```cpp
#include<queue>
```
这是队列的头文件，里面含有queue（队列）,deque（双端队列）和priority_queue（优先队列或STL堆），可能还有别的，但本蒟蒻只知道这些...（果然trl）

```cpp
priority_queue <int,vector<int>,less<int> > q;
```
声明一个大根堆q~~（为什么less对应着大根堆）~~，这里如果为greater<int>（小根堆），求出来的就是最多的奶牛数（坑啊...）
```
q.push();
q.top();
q.pop();
```
分别对应着放加入堆中，返回堆顶，删除堆顶
  
其实也没有什么可以讲的啦，反正各位应该都看不懂这简陋的讲解~~（bb了这么多说没有可讲的？）~~

------------
# 代码

```cpp
for(int i=0;i<n;i++){
    	if(i>q.top()){
    		printf("%d\n",i);
    		return 0;
    	}
    	q.pop();
    }
```
为什么要单独说一下这里，因为这里的i代表的不是第i只奶牛，而是第i只前面的奶牛数，如果想要i表示奶牛数的话，就得用i-1来表示前面的奶牛数
```cpp
for(int i=1;i<=n;i++){
    	if(i-1>q.top()){
    		printf("%d\n",i-1);
    		return 0;
    	}
    	q.pop();
    }
```
还有，就是最后要输出一个n，因为如果所有wi的最小值大于n的话，最少就是n啦~~（话说我这个菜鸟怎么这里都没注意，**又**被Hack了）~~

### 标程
```cpp
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<queue>
#include<stack>
#include<vector>
using namespace std;
int n;
int a;
priority_queue <int,vector<int>,less<int> > q;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
    	scanf("%d",&a);
    	q.push(a);
    }
    for(int i=0;i<n;i++){
    	if(i>q.top()){
    		printf("%d\n",i);
    		return 0;
    	}
    	q.pop();
    }
    printf("%d\n",n);
	return 0;
}
```

# 最后，请勿抄袭，谢谢！！！

---

## 作者：qmq菜死了 (赞：0)

题目的意思可以理解为：有 N 头奶牛，每头奶牛都想喝汽水，但是第 i 头奶牛只有在不大于 $W_i$ 头奶牛排队的情况下，才会选择去排队喝汽水，否则就会离开，可是农场主 John 非常小气，他想要知道最少有多少个奶牛排队。

这是一道很水的贪心排序题，$W_i$ 值越大的奶牛，即使放在很后面也有很大机会喝到汽水，而 $W_i$ 小的奶牛只有在前面才可能喝到汽水，要让喝汽水奶牛数最少，就把 $W_i$ 大的奶牛放在前面。~~码了那么久让我过吧 QAQ 。~~

```cpp
#include<bits/stdc++.h>//方便的万能头
using namespace std;
int n,a[100100];
int cmp(int x,int y)
{
	return x>y;//按从大到小排
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	sort(a+1,a+n+1,cmp);
	int ans=0;//ans 存储可以喝到汽水的最小奶牛数量，也就是当前排队的数量
	for(int i=1;i<=n;i++)
	{
		if(a[i]>=ans)//如果不小于当前排队数量说明可以排队
		{
			ans++;//排队
		}
		else//由于是从大到小排，当前的不能排队后面的肯定也不行
		{
			break;
		}
	}
	cout<<ans;
    	return 0;
}
```



---

## 作者：YosemiteHe (赞：0)

因为要求出最少可能的排队的奶牛数量，所以要从大到小排序。

因为：

> 此外，当奶牛 $i$ 到达时，当且仅当至多有 $w_i$ 头奶牛在排队时她会来排队。

所以，当 $w_i < i$ 时，$i$ 即为最优解。

介绍一种从大到小排序的方法：

`sort(变量名 + 起始下标, 变量名 + 终止下标, greater <数据类型> ());`

Code：
```cpp
#include <iostream>
#include <algorithm>
using namespace std;
int n, w[100005];
int main(void) {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> w[i];
    }
    sort(w, w + n, greater <int> ());
    for (int i = 0; i < n; ++i) {
        if (w[i] < i) {
            cout << i << endl;
            return 0;
        }
    }
    cout << n << endl;
    return 0;
}
```

---

## 作者：鸿飞 (赞：0)

## PART1:思路
因为第i头奶牛前面的牛数不能超过w[i]，所以将w[i]从大到小排序后模拟一只一只前来的状况，当前面的奶牛数超过排序后的w[i]时结束并输出总数。
## PART2:代码
```cpp
#include<iostream>
#include<algorithm>
#include<string>
using namespace std;
int w[100005];
bool cmp(int a,int b)
{
	return a>b;
}
int main(){
	int n;
	cin >> n ;//输入n
	for(int i=1;i<=n;i++)
	{
		cin >> w[i] ;//输入w[i] 
	}
	sort(w+1,w+n+1,cmp);//排序 
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		if(w[i]>=i-1)
		{
			ans++;
		}else
		{
			cout << ans ;
			return 0;
		}
	}
	cout << ans ;
	return 0;
}
```
## THE END 

---

## 作者：shihoghmean (赞：0)

## 这道题是个简单的贪心题
#### 首先，分析一下题目的意思
#### 可以知道，让$wi$值大的奶牛先排到队伍里，才能使奶牛的数量最少
#### 为什么呢?
#### 首先，每个奶牛都有一个期望值$wi$，这点很重要
#### 想要让奶牛入列的数量最少，就要让$wi$少的奶牛先入列
#### 这样$wi$少的奶牛看到前面的奶牛太多了，就走了
#### 所以让$wi$大的先入队，才能使数量最少
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100001];
int main()
{
    int n,ans;
    cin>>n;//输入数量n
    for(int i=1;i<=n;i++)
    	cin>>a[i];//输入期望值
    sort(a+1,a+n+1);//把期望值从小到大排序
    for(int i=n;i>=1;i--)//因为从小到大排，所以从末尾数
    	if(a[i]>=ans) ans++;//当期望值大于等于已经入队的数量，就入队
    cout<<ans;//输出最小数
    return 0;
}
```
## 谢谢
## 写题解不易，谢绝抄袭

---

## 作者：Real_Create (赞：0)

首先，如何做正解？

第一步：找到这道题

第二步：查看算法

第三步：发现快速排序

第四步：打出
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	cin>>n;
	for(int i=0;i<n;i++)
	{
		cin>>a[i];
	}
	sort(a,a+n);
	return 0;
}

```
第五步：
```
if(是从大到小）
{
	加一个自定义函数;
	if(这个不会)
	{
		关闭洛谷;
	}
}else
{
	if(!是从小到大)
	{
		//关闭此题
	}
}
```


第六步：做一些核心代码

第七步：AC

------------
然后是诡异的选择排序解以及怎么过第10个点。。。

先是一坨丑陋的代码

```
#include <bits/stdc++.h>
using namespace std;

int main()
{
	int n;
	cin>>n;
        int a[n];
	for(int i=0;i<n;i++)
	{
		cin>>a[i];
	}
	for(int i=0;i<n;i++)
	{
		for(int j=i;j<n;j++)
		{
			if(a[i]<a[j])
			{
				swap(a[i],a[j]);
			}
			if(a[i]>=n)
			{
				break;//你都能接受那就排这里咯
			}
		}
		if(i>a[i])
		{
			cout<<i;//不要问我为什么不要-1（因为我是从0开始的呀。
			return 0;
		}
	}
	return 0;
}

```
然后某些愚蠢的人就会开始抄

~~你傻啊，注释那么少洛谷会让我过？~~

没错，那些愚蠢的棕色就会杯具的WA一个点了。

那是为什么呢？因为你如果一直没有超过你就虾米都没输出。

所以你需要这样！

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[100005];//数组开多点又不会内存超限
int main()
{
	int n;
	cin>>n;//输入
	for(int i=0;i<n;i++)
	{
		cin>>a[i];//输入
	}
	for(int i=0;;i++)//不要让循环停下来！
	{
		for(int j=i;j<n;j++)//选择排序
		{
			if(a[i]<a[j])
			{
				swap(a[i],a[j]);
			}
			if(a[i]>=n)//你都比n大了那还排个鬼
			{
				break;所以你不准动了！
			}
		}
		if(i>a[i])
		{
			cout<<i;//输出（上面有解释）
			return 0;AC一道水题
		}
	}
}
```


---

## 作者：B_Qu1e7 (赞：0)

快排+枚举

$w[i]$最大只有$10^9$??

放心食用 提供一种排序方法

```
#include<cstdio>
#include<algorithm>
using namespace std;
int N,w[100001],k=0;
int main()
{
	scanf("%d",&N);
	for(int i=1;i<=N;i++)
	{
		scanf("%d",&w[i]);
		w[i]=1e9-w[i];//相对于最大数来说的相反数
	}
	sort(w+1,w+N+1);
	while(++k<=N)
	{
		w[k]=1e9-w[k];//完全没影响
		if(w[k]<k-1)break;
	}
	printf("%d\n",k-1);
}
```

---

## 作者：Jelly_Goat (赞：0)

不敢快速排序又想要快排的速度，还不用STL的小伙伴们看这里！  
~~小金羊终于学会了堆排以外的另外的一种排序 （打个题解巩固一下）~~
## 归并排序（mergesort）：
时间复杂度和快排一样的优秀。  
先说归并排序的实现：  
首先我们一样的是要进行分解，以达到$O(logn)$の时间复杂度。 
然后我们需要了解一下它的思想：  
### 如果两个序列的顺序已经排好，于是我们合并两个序列。
emmm...由于**分解到最后只有一个元素，一定满足性质。**  
然后合并？~~玄学？~~这咋合并？  
其实比较简单。  
**我们取两个指针，分别指向分解的序列的两个头部，然后比较指针指向的两个元素，满足的就放进我们的辅助空间，直到有一个序列已经用完。**  
所以如果**剩下的序列如何处置？**  
刚刚说了，**两个序列都是有序的**，如果剩下的都不满足比原先的元素满足性质（大或者小，或者结构体之类的），那么**剩下的就依次都放进去就好了。**  
没看懂？模拟一下。  
首先序列`w[10086]`,表示奶牛想等的时间，假设6头，序列情况如下：  
（假设**从小到大的顺序**）
```cpp
//一开始
int w={6,2,3,4,5,1};
//分解第一次
w1={6,2,3},w2={4,5,1};
//分解第二次
w11={6}/*这个好了*/,w12={2,3},w21={4}/*这个也好了*/,w22={5,1};
//分解最后一次,已经分解完毕的不显示
w121={2},w122={3},w221={5},w222={1};
//所以现在序列是
w11={6},w121={2},w122={3},w21={4},w221={5},w222={1};
//接下来合并最后分解的那一拨
w11={6},w12_ok={2,3},w21={4},w22_ok={1/*来自w222*/,5};
//continue the merge
w1_ok={2,3,6/*比较到6剩下了，就放进来*/},;
w2_ok={1/*来自w22_ok*/,4/*来自w21*/,5/*from w22_ok*/};
//finally
w_ok={1/*from w2_ok*/,2/*from w1_ok...省略剩下的注释*/,3,4,5,6};
```
这就是归并排序的步骤。看看代码？  
（仅仅是从小到大的mergesort~~样例~~模板代码）Code:
```cpp
void mergesort(int l,int r)
{
    if (l==r)return;//已经只剩一个元素
    int mid=(l+r)>>1;//中部元素
    mergesort(l,mid);//分解左边
    mergesort(mid+1,r);//分解右边
    int s2[r-l+1]/*辅助空间*/,p1=l,p2=mid+1,p3=1;
    while (p1<=mid&&p2<=r)//没分解完
    {
        if (w[p1]<=w[p2])s2[p3++]=w[p1++];
        else s2[p3++]=w[p2++];//以上两行是把较小的放进辅助空间
    }
    while (p1<=mid)s2[p3++]=w[p1++];//若有剩余，放进去
    while (p2<=r)s2[p3++]=w[p2++];//若有剩余，放进去
    p3=l;
    for (register int i=1;i<=r-l+1;i++)
        w[p3++]=s2[i];//再把排好的序列覆盖回去
}
```
看看这个题:  
![](https://cdn.luogu.com.cn/upload/pic/51427.png)  
#### 贪心策略：
先把最愿意排队的奶牛放前面，这样最不愿意排队的奶牛都吃草去了，保证队伍最小。  
上代码：  
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;
int w[100001],num,cnt=0;
void mergesort(int l,int r)
{
    if (l==r)return;//已经只剩一个元素
    int mid=(l+r)>>1;//中部元素
    mergesort(l,mid);//分解左边
    mergesort(mid+1,r);//分解右边
    int s2[r-l+1]/*辅助空间*/,p1=l,p2=mid+1,p3=1;
    while (p1<=mid&&p2<=r)//没分解完
    {
        if (w[p1]>=w[p2])s2[p3++]=w[p1++];
        else s2[p3++]=w[p2++];//以上两行是把较小的放进辅助空间
    }
    while (p1<=mid)s2[p3++]=w[p1++];//若有剩余，放进去
    while (p2<=r)s2[p3++]=w[p2++];//若有剩余，放进去
    p3=l;
    for (register int i=1;i<=r-l+1;i++)
        w[p3++]=s2[i];//再把排好的序列覆盖回去
}
int main()
{
    scanf("%d",&num);
    for (register int i=1;i<=num;i++)
        scanf("%d",&w[i]);
    mergesort(1,num);
    for (register int i=1;i<=num;i++)
    {
        if (w[i]<cnt)break;
        cnt++;
	}
	printf("%d",cnt);
    return 0;
}
```
### 最后提醒大家一点：  
归并排序的辅助空间需求特别大，如是特别要求或者数据范围特别大，请小心使用。

---

## 作者：CyaNeko (赞：0)

正解:快排+枚举        
首先用快排将奶牛愿意等待的数量按从小到大快排     
然后for循环判断         
如果wi<i-1就退出循环          
输出i-1         
#### 附上pascal代码:
```
var i,n:longint;
    a:array[1..100001]of longint;

    procedure sort(l,r: longint);
      var
         i,j,x,y: longint;
      begin
         i:=l;
         j:=r;
         x:=a[(l+r) div 2];
         repeat
           while a[i]>x do
            inc(i);
           while x>a[j] do
            dec(j);
           if not(i>j) then
             begin
                y:=a[i];
                a[i]:=a[j];
                a[j]:=y;
                inc(i);
                j:=j-1;
             end;
         until i>j;
         if l<j then
           sort(l,j);
         if i<r then
           sort(i,r);
      end;

begin
    read(n);
    for i:=1 to n do read(a[i]);
    sort(1,n);
    for i:=1 to n+1 do if i-1>a[i] then break;
    dec(i);
    write(i);
end.
```

---

## 作者：huhuhuhaha (赞：0)

水题一道嘛，多读几遍题目肯定能A掉

显然为了队伍中总的奶牛数更少，需要让更多的奶牛离开，即让更不愿意排队的奶牛多排队。

于是可以按照$w[i]$从大到小排序，最大的排在最前面。

直到有一只奶牛离开了，那么排队就结束了，因为这只奶牛后面的奶牛一定更加不愿排队。

```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int a[100005];
bool cmp(int x,int y){return x>y;}
int main(){
	int n;
	cin>>n;
	for (int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+1+n,cmp);
	int ans=0;
	for (int i=1;i<=n;i++){
		if (a[i]<ans) break;
		ans++;
	}
	cout<<ans;
}
```

---

## 作者：t14Zack (赞：0)

这题简单到不行……
既然最少，那就排好序后按w的大小从后往前找。  
只要当前找到的w[i]的比牛数小了，说明从这往后所有的奶牛都不愿意排了，输出当前牛数即可。  
我是用冒泡排的序，快排更快。  
不多说了，上代码：
```cpp
#include <cstdio>
int w[10010];
int main() {
	int n, t;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &w[i]);
	for (int i = 0; i < n-1; i++)
		for (int j = 0; j < n-1-i; j++)
			if (w[j] > w[j+1]) t = w[j], w[j] = w[j+1], w[j+1] = t;
	int the_num_of_the_cow = 0;
	for (int i = n-1; i >= 0; i--, the_num_of_the_cow++)
		if (w[i] < the_num_of_the_cow) {printf("%d\n", the_num_of_the_cow); return 0;}
	printf("%d\n", n);
	return 0;
} 
```
~~哈哈哈，大水题啊！！！~~

---

