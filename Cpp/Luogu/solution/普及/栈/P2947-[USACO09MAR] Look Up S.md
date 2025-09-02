# [USACO09MAR] Look Up S

## 题目描述

Farmer John's N (1 <= N <= 100,000) cows, conveniently numbered 1..N, are once again standing in a row. Cow i has height H\_i (1 <= H\_i <= 1,000,000).

Each cow is looking to her left toward those with higher index numbers. We say that cow i 'looks up' to cow j if i < j and H\_i < H\_j. For each cow i, FJ would like to know the index of the first cow in line looked up to by cow i.

Note: about 50% of the test data will have N <= 1,000. 

约翰的 $N(1\le N\le10^5)$ 头奶牛站成一排，奶牛 $i$ 的身高是 $H_i(1\le H_i\le10^6)$。现在，每只奶牛都在向右看齐。对于奶牛 $i$，如果奶牛 $j$ 满足 $i<j$ 且 $H_i<H_j$，我们可以说奶牛 $i$ 可以仰望奶牛 $j$。 求出每只奶牛离她最近的仰望对象。

Input

## 说明/提示

FJ has six cows of heights 3, 2, 6, 1, 1, and 2.


Cows 1 and 2 both look up to cow 3; cows 4 and 5 both look up to cow 6; and cows 3 and 6 do not look up to any cow.

【输入说明】$6$ 头奶牛的身高分别为 3,2,6,1,1,2。

【输出说明】奶牛 #1,#2 仰望奶牛 #3，奶牛 #4,#5 仰望奶牛 #6，奶牛 #3 和 #6 没有仰望对象。

【数据规模】

对于 $20\%$ 的数据：$1\le N\le10$；

对于 $50\%$ 的数据：$1\le N\le10^3$；

对于 $100\%$ 的数据：$1\le N\le10^5,1\le H_i\le10^6$。


## 样例 #1

### 输入

```
6 
3 
2 
6 
1 
1 
2 
```

### 输出

```
3 
3 
0 
6 
6 
0 
```

# 题解

## 作者：胡萝卜2333333333 (赞：51)

### 破题：
其实可以把本体看成就求序列中每一个在其右边的第一个比它大的值，就是向右找寻第一个比他本身大的值，并且储存下来，没找到则得0。

### 思路：
当我第一次看到这题的时候，第一个想到的就是用双重循环来做，但是我看了一眼题目的难度系数【普及/提高-】，所以这道题肯定有什么坑！但是我还是自信满满的写下了代码，嗯，然后我TLE了，GG。

双重循环代码如下：

```
#include<iostream>
#include<cstdio>
using namespace std;
int n,i,j;
int a[100010];
int ans[100010];
int main()
{
    cin>>n;
    for(i=1;i<=n;i++)cin>>a[i];
    for(i=1;i<=n;i++)
    {
        for(j=i;j<=n;j++)
        {
            if(a[i]<a[j])
            {
                ans[i]=j;
                break;
            }
        }
    }
    for(i=1;i<=n;i++)cout<<ans[i]<<endl;
    return 0;
}
```
很简单的代码，TLE了5个点。
【所以千万不要作死！！】

其实这道题考虑的只是如何将**优化时间**，那么就只有在处理数据的时候下功夫了，其实就有点像是递推的思维，就是要在比对的时候，采用一个跳跃的思维，就好比如有这样一组数据:3 2 6 1 1 2，那么选取其中的6，那么6就要和它右边的1进行比较，因为6>1，所以这个时候，就把1的仰望对象与6进行对比，这样就可以节省在2的仰望对象与2之间的这些数据的比较了，从而达到优化的效果。然后经过递推一点点推回来，我采用的是倒序的方法。

下面是我的AC代码：

```
#include<iostream>
#include<cstdio>
using namespace std;
int n,i,j,gg=1;
int a[100010];
int ans[100010];//定义
int main()
{
	cin>>n;
	for(i=1;i<=n;i++)cin>>a[i];//输入
	for(i=n-1;i>=1;i--)//采用倒序，因为ans[n]=0，所以就从n-1开始
	{
		j=i+1;//先和它右边的第一个数进行比对
		while(a[i]>=a[j] && a[j]>0)j=ans[j];//如果没有找到比它自己大的数的话，就把另一个数的仰望对象与它进行比对
		ans[i]=j;//标记
	}
	
	for(i=1;i<=n;i++)cout<<ans[i]<<endl;//输出
	return 0;//over~~~~
}
```
！！！也是很简单的几行代码，但是要注意的是在if语句里的判断条件a[j]>0，因为在往回寻找仰望对象的同时，也会有涉及到ans[0]的时候，所以这时候要么使a[0]等于一个很大的数，要不就是在if语句之中添加一个a[j]>0，否则就会陷入死循环而导致没有输出！！！

---

## 作者：Seanq (赞：28)

**P2947 [USACO09MAR]向右看齐Look Up题解**  
算法：单调栈  
何为单调栈？  
解释一下：  
单调栈类似单调队列，这道题中要运用到单调栈。  
如下：  
令f[i]为向右看齐的人的标号  
6 
3 
2 
6 
1 
1 
2   
f分别为 3 3 0 6 6 0  
首先，最后一个人必然没有向右看齐的人的编号  
先将最右边的人加入栈  
接着，我们发现1，1比2小，先加入栈，当前f值为6  
接着，又来了一个1，发现1=1，弹出1，接着发现1<2,则将1加进栈，当前f值为6  
接着，来了一个6，6>2,弹出2，当前f值为0  
接着，来了一个2，2<6，加入2，当前f值为3  
最后，来了一个3，3>2，弹出2，将3加入栈，当前f值为3  
最后的栈中有3和6  
最后的答案就是3 3 0 6 6 0  
每次只在栈中存数字标号，进来一个数，就把小于等于他的数全部弹出，若剩下有数，则答案是剩下的数，否则答案是0  
为什么？  
因为：  
若x小于当前数，x不会成为答案。  
这就是单调栈的用法  
弹栈：  
```cpp
while(!s.empty()&&a[s.top()]<=a[i]) s.pop();

```
更新：  
```cpp
if(!s.empty()) f[i]=s.top();
		else f[i]=0;
```
存入：  
```cpp
s.push(i);
```
std:  
```cpp
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
#include <cctype>
using namespace std;
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define frep(i,x,y) for(int i=x;i>=y;i--)
const int N=100005;
int n;
stack<int> s;
int a[N];
int f[N];
int main()
{
	scanf("%d",&n);
	rep(i,1,n)
		scanf("%d",&a[i]);
	frep(i,n,1)
	{
		while(!s.empty()&&a[s.top()]<=a[i]) s.pop();
		if(!s.empty()) f[i]=s.top();
		else f[i]=0;
		s.push(i);
	}
	rep(i,1,n) printf("%d\n",f[i]);
	return 0;
} 
```

---

## 作者：牛奶黄油 (赞：15)

这道题可以构建一个单调递减栈。

每次输入一个数a就while判断a是否比原来栈顶的数大。

如果比栈顶的数大就证明这个a是之前栈顶数的仰望对象，记录它的仰望对象并将原来栈顶的数出栈。

之后再将a进栈。

最后将记录的仰望对象输出。

这道题就完美的解决了。


```
#include<bits/stdc++.h>//万能头文件
using namespace std;
int a,n,top=1,ans[110000];//把数组开大点才能不出事
struct pigu
{
	int hao,shu;//hao表示这个数是第几个输入的，便于之后记录仰望对象，shu是他的高度。
}que[100005];//把数组开大点才能不出事
int main()
{
	cin>>n;//输入
	for(int i=1;i<=n;i++)
	{
		cin>>a;
		while(a>que[top-1].shu&&top>1)
        //将原来栈里的数记录仰望对象并出栈
        //必须要tot大于1，不然他会一直减
		{
			ans[que[top-1].hao]=i;
			top--; 
		}
		que[top].shu=a;//将新的数入栈
		que[top].hao=i;
		top++;
	}
	for(int i=1;i<=n;i++)//输出答案。
		cout<<ans[i]<<endl;
	return 0; 
} 
```

---

## 作者：蔡俊黠 (赞：10)

我用的是单调队列，很容易理解，一遍过，跑测试点最快的3ms,最慢的20ms

用deque去维护一个单调递减队列q，拿样例来说

3，2，6，1，1，2 

给他们编号，成这样

（3,1），（2,2），（6,3），（1,4），（1,5），（2,6）

首先（3,1）入队（从队尾入，下面一样）

##### q:（3,1）

（2,2）入队，队列不变

##### q:（3,1），（2,2）

（6,3）入队，因为6比3和2都大，所以6是他们的第一个仰望对象，把3和2删除，记录他们的答案就是6的编号3，此时

##### q:（6,3）

（1,4）入队，队列不变

##### q:（6,3），（1,4）

（1,5）入队，队列不变

##### q:（6,3），（1,4），（1,5）

（2,6）入队，因为2比队里的两个1都大，所以2是他们的第一个仰望对象，把两个1删除，记录他们的答案就是2的编号6，此时

##### q:（6,3），（2,6）

没有新的数字入队，结束，6和2的答案没有更新，说明他们没有仰望对象

#### code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,f[100010];
struct node{
	int num;
	int id;
}e;
deque <node> q;
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		int a;
		scanf("%d",&a);
		while (!q.empty()&&q.back().num<a) f[q.back().id]=i,q.pop_back();
		//找比它小的数，成为这些数的仰望对象 
		e.num=a; e.id=i;
		q.push_back(e); //入队 
	}
	for (int i=1;i<=n;i++) printf("%d\n",f[i]);
	return 0;
}
```




---

## 作者：Clever_Jimmy (赞：7)

----------

## 算法1
#### (枚举)  $O(n^2)$

##### 思路：

我们可以考虑从小到大枚举任意的两个点$i, j(i < j)$：

如果找到了一个$j$，使得$a[i] < a[j]$，那么可以`break`掉，进行下一层的枚举。


##### 时间复杂度分析：

显然，枚举`i`需要$n$次；

而对应每个`i`，枚举`j`需要$n - i$次；

所以时间复杂度是$O(n^2)$的。


### C++ 代码
```cpp
int main()
{
	n = read();
	for(rgi i = 1; i <= n; ++i)
		a[i] = read();
	for(rgi i = 1; i <= n; ++i)
		for(rgi j = i + 1; j <= n; ++j)
			if(a[j] > a[i])
			{
				out[i] = j;
				break;
			}
	for(rgi i = 1; i <= n; ++i)
		printf("%d\n", out[i]);
	return 0;
}
```

----------

## 算法2
#### (单调栈)  $O(n)$

##### 思路：

我们注意到，**被仰视的奶牛的身高一定是单调不递减的**，于是我们就可以用一个单调栈来维护。

在枚举每个奶牛的时候，我们可以比较当前奶牛的升高与栈顶的奶牛的身高

如果当前奶牛的身高$>$栈顶奶牛的身高，那么**再见了，栈顶的奶牛，以后的任意一个奶牛都不会仰视你了**，

因为当前的奶牛**一定是更优解**；

如果当前奶牛的身高$<$栈顶奶牛的身高，那么就**没什么事**，压进栈里就好了。

##### 时间复杂度分析：

显然，每个奶牛都**只会进出栈$1$次**，

所以时间复杂度是$O(n)$的。


### C++ 代码
```cpp
struct node
{
	int id, val;
};

int main()
{
	n = read();
	for(rgi i = 1; i <= n; ++i)
		a[i] = read();
	for(rgi i = 1; i <= n; ++i)
	{
		struct node tmp;
		tmp.id = i, tmp.val = a[i];
		while(!stk.empty() && tmp.val > stk.top().val)
		{
			out[stk.top().id] = i;
			stk.pop();
		}
		stk.push(tmp);
	}
	for(rgi i = 1; i <= n; ++i)
		printf("%d\n", out[i]);
	return 0;
}
```

---

## 作者：Iowa_BattleShip (赞：7)

看看题解里竟然没有单调队列的题解，而这题标签却有单调队列……所以我来补一发吧。
单调队列的解法目前不加register和inline，就只有快读，不开O2只要40ms就能过，还是比较快的，毕竟O(n)算法。
具体算法解释看代码吧
```cpp
#include<cstdio>
using namespace std;
const int N=1e5+10;
int a[N],q[N],an[N];//a是原数，q是队列，用来储存队列中数在数组a的下标，an则储存答案
int re()//快读
{
	int x=0;
	char c=getchar();
	for(;c<'0'||c>'9';c=getchar());
	for(;c>='0'&&c<='9';c=getchar())
		x=x*10+(c-'0');
	return x;
}
int main()
{
	int i,n,tail=0;//这题不需要head，因为没有区间大小，head一直为1
	n=re();
	for(i=1;i<=n;i++)
		a[i]=re();//输入
	for(i=1;i<=n;i++)
	{
		while(tail&&a[i]>a[q[tail]])//单调队列模板打法，因为head为1，所以要保证tail>0，当目前扫到的数大于队列末尾的数时，这个数一定是队列末尾这个数右端第一个比它大的数，所以就把这个这个数储存入队列末尾数的an数组中，并将tail--，即把末尾数移除队列，紧接着比较队列中下个数，直到遇到第一个≥这个数或队列空为止。 总的核心思想就是维护一个不上升连续序列，在维护的同时找到答案
		{
			an[q[tail]]=i;
			tail--;
		}
		q[++tail]=i;//将这个数加入队列
	}
	for(i=1;i<=n;i++)
		printf("%d\n",an[i]);//最大的数和最后的一个不上升连续序列的数对应的answer是不会修改的，所以放心直接输出
	return 0;
}
```

---

## 作者：MloVtry (赞：4)

虽然没开栈不过感觉思路大概差不多的样子（？）

倒序枚举，然后从i+1处开始寻找，如果可行，ans[i]=i+1,不然就去尝试i仰望的点，然后直到可以仰望为止



```cpp
#include<iostream>
#include<cstdio>
#define inf 1<<30
using namespace std;
int n,a[100010];
int look[100010];
int main()
{
    scanf("%d",&n);
    a[0]=inf;
    for(int i=1;i<=n;++i) scanf("%d",&a[i]);
    for(int i=n-1;i>=1;--i)
    {
        int now=i+1;//从这里开始尝试
        while(a[i]>=a[now]) now=look[now];//直到可行
        look[i]=now;//记录
    }
    for(int i=1;i<=n;++i) cout<<look[i]<<endl;//输出
    return 0;
}//今天也依旧没有捞到47厌战岛风呢QwQ
```

---

## 作者：PaulFrank (赞：4)

此题不能是单纯的二重循环

还需要有所优化,无需一个一个枚举,只要直接枚举其仰望对象即可用ans记录一下就行了

注释在代码中,详情自己看！！

代码src :

```cpp
#include <cstdio>
#include <stack>
#include <iostream>
#include <algorithm>
using namespace std;
int i,j,n,h[100005],ans[100005];
int main(){
    freopen("2947.in","r",stdin);
    freopen("2947.out","w",stdout);
    scanf("%d",&n);
    for(i=1;i<=n;i++)
        scanf("%d",&h[i]);
    h[0]=1<<30;
    //此处一定要注意,要赋值为无穷大,因为在从后面枚举的时候,往前扫到一个最大的,如果仍旧比原来的小
    //并且它没有仰望对象,那么原来的也一定没有仰望对象 
    for(i=n-1;i>=1;i--){
        for(j=i+1;h[i]>=h[j];j=ans[j]);//优化 ,直接指向下一个(即为它的仰望对象) 
        ans[i]=j; //把i的仰望对象记为j 
    }
    for(i=1;i<=n;i++)
        printf("%d\n",ans[i]);
    return 0;
}
```

---

## 作者：柠青哟 (赞：2)

问题表述可翻译为：寻找第一个大于该数的数。
这类问题都可以用单调队列解决。
我们尝试维护一个单调递减队列，当一个大于队尾元素的数要入队时，我们就找到了第一个大于队尾元素的数，所以记录队尾元素的仰望对象，队尾元素出队。然后比较新的队尾元素与该元素的大小，如果小于，那么该元素也是新的队尾元素的仰望对象，于是记录，出队，比较，直到队尾元素大于该元素（或者队列为空），该元素进队。
这样就可以在O(N)的复杂度下完成。
由于我比较偷懒，所以队列是用的deque
~~STL大法好
```c
#include<iostream>
#include<cstdio>
#include<queue>
using namespace std;
int n,b[100086];
struct qing{
	int s,No;
}a[100086];
deque<qing>q;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i].s);
		a[i].No=i;
	}
	for(int i=1;i<=n;i++){
		while(!q.empty()&&a[i].s>q.back().s){
			b[q.back().No]=a[i].No;
			q.pop_back();
		}
		q.push_back(a[i]);
	}
	for(int i=1;i<=n;i++){
		printf("%d\n",b[i]);
	}
	return 0;
}
```


---

## 作者：CloudStroll (赞：2)

看到这一题，我的思路是比较清晰的。因为本题的本质其实是从前往后遍历找出最邻近最大的一个数的下标（这一点很重要，注意一会儿我的单调栈所存储的）对单调栈还不大熟悉的同学可以看一看百度，有很多可供参考的博客。

那么，问题是怎么处理单调栈，其实单调栈的a数组存储的并不是原来牛的高度，而是它所对应的下标，这也是题目所要求的。

那么我的h[a[t]]便可以调用出下表所对应的高度来进行单调的选择，这道题有一个点需要注意的是单点栈中也需要包含高度一样的牛。

代码如下

```
//begin
#pragma warning (disable:4996)//vs的调用scanf，不用在意。
#include <cstdio>
#define run(a,b,c) for(a=b;a<=c;a++)
using namespace std;
//head
//By CJ

const int MAXN = 100005;
//const

long long   N, h[MAXN], i, now, ans, t,a[MAXN],b[MAXN];
//variable

void Read_In()
{
	scanf("%lld", &N);
	run(i, 1, N)
	{
		scanf("%lld", &h[i]);
	}
}



void Solve()
{
	for (i = N; i >= 1; i--)
	{
		while (t && h[a[t]] <= h[i])//关键的单调栈，需要理解键值对应关系
		{
			t--;
		}

		if (t == 0)
		{
			b[i] = 0;
		}
		else
		{
			b[i] = a[t];
		}
		a[++t] = i;
	}
}



void Write_Out()
{
	run(i, 1, N)
	{
		printf("%d\n", b[i]);
	}
}
//function

int main()
{
	Read_In();
	Solve();
	Write_Out();
	return 0;
}
//main
//end//完成！
```

---

## 作者：Misaka_Azusa (赞：2)

因为在单调队列上被dalao们锤爆

怒刷单调队列题

### 何为单调队列？

设我们的队列为从左至右单调递增

对于样例数据 3 2 6 1 1 2

我们先把3入队 此时队列：3

再将2从后面入队 此时队列：2 3

再将6从后面入队 但是，为了满足队列从左至右的单调性，我们将2，3出队 此时队列：6

再将1从后面入队 此时队列：1 6

再将1从后面入队 此时队列：1 1 6

再将2从后面入队 但是，为了满足队列从左至右的单调性，我们将1，1出队 此时队列：2 6

由此可以类推其他单调性。

于是，我们观察到单调队列和这道题的关系：

#### “谁把我从队列里赶了出去我就仰望谁。”

所以，2，3被6赶出去，2，3仰望的位置为6的位置即3。

所以，1，1被2赶出去，1，1仰望的位置为2的位置即6。

#### 那么，如果我一直在队里。我就谁也不仰望。

下面介绍实现方式：

我先说：

### "我永远都喜欢$Stella$!"
~~没良心的Master~~

单调队列需要一个支持从两边操作的队列——双端队列

$STL$中有现成的deque:

### $code:$


```
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int maxn = 100000 + 10;
struct node{
	int pos, val;
}a[maxn];//因为我们需要记录位置，所以开一个结构体。val为高度，pos为在序列的位置。
int n, ans[maxn];
deque<node> q;//双端队列。
int main()
{
	scanf("%d",&n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d",&a[i].val); a[i].pos = i;//输入高度，给位置赋值。
		while(!q.empty() && a[i].val > q.back().val) ans[q.back().pos] = a[i].pos, q.pop_back();//当队列不为空时，如果当前输入的值大于我队列中后面的元素值，那么我就要仰望当前的输入值的位置。同时把我出队。
		q.push_back(a[i]);//从后面将元素入队。
	}
	for(int i = 1; i <= n; i++) 
	printf("%d\n",ans[i]);
	return 0;
}
```
#### 至于为什么需要一个支持两头操作的队列。

在大部分单调队列题目中，需要维护的区间有时并不是整一个区间，而是多个区间。所以当如果我们单调队列中最前面的数已经不在当前区间里，我们需要将他从前面出队。

最前面的数一定比当前维护好的队列里所有数入队都早。如果他入队不是最早还比之前入队的数大，前面入队的数直接被他挤出队了。

欢迎交流/指错

一起共同进步。

QQ:935145183/3203600070

---

## 作者：Jy_Amoy (赞：2)

这题的数据有点大，所以我们需要一些优化来加快程序

我的思路很简单，我最开始构思的代码是这样的：（58分）

```
#include<cstdio>
#define maxn 100005
using namespace std;
int a[maxn],f[maxn],n;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
        scanf("%d",&a[i]);
    a[0]=1e9;int j;
    for(int i=n-1;i>=1;i--)
    {
        j=i+1;
		while(a[i]>=a[j])
		{
			++j;
			if(j>n)
			{	
				j=0;
				break;
			}
		}
        f[i]=j;
    }
    for(int i=1;i<=n;++i)
        printf("%d\n",f[i]);	
}
```
然后这个代码TLE了5个点

很明显中间这一段代码：
```
while(a[i]>=a[j])
		{
			++j;
			if(j>n)
			{	
				j=0;
				break;
			}
		}
```
耗费的时间太久了

我们再来看看这一段代码的功能：

他是用来求如果一个点他的右边比他矮然后求下一个仰望对象的，而这里我们选查看后面全部的有没有比他高的。
但显而易见1000000太吉尔大了

**所以我们来考虑优化**

在这段代码里，我们可以不必查看他后面的每一个，我们可以直接看他右边的仰慕对象的仰慕对象的仰慕对象···没错就是递推，直到搜到比他高的，则读入

接下来是AC代码：

```
#include<cstdio>
#define maxn 100005
using namespace std;
int a[maxn],f[maxn],n;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%d",&a[i]);
	a[0]=1e9;int j;//第0个需要定义大一点，不然下面判断不过 
	for(int i=n-1;i>=1;i--)
	{
		j=i+1;//仰望对象只能在自身右边 
		while(a[i]>=a[j]) j=f[j];//一个类似于递推的东西，是一种优化的思路:当a[i]>=a[j]时直接查看a[j]的仰望对象，直到找到为止 
		f[i]=j; 
	}
	for(int i=1;i<=n;++i)
		printf("%d\n",f[i]);	
}
```

---

## 作者：用户已注销 (赞：1)


这题好像是NOIP2018的初赛完善程序题。。。

~~所以说有没有人用双向链表写？反正我是不会。~~

最让人气愤的是。。。置顶的几篇题解居然都是复杂度平方+剪枝优化的啊。。。构造一个总体呈上升趋势，有少量点权为极大值的数据就可以卡成平方啊。。。所以建议加强数据！

正解：

复杂度严格线性的单调栈（话说作者: Iowa_BattleShip 的题解挂着单调队列的牌子打了个单调栈的代码？）

从后往前做，维护一个单调栈，每次先弹栈，然后记栈顶为答案，再把当前的数字放在栈顶。

正确性：

因为先弹栈，所以可以保证找到的数是比当前数大的，且可以自动处理0的情况。
因为所有数都会进栈，所以可以保证找到的数是符合条件的数里最近的。
时间复杂度显然是线性的。

以上。代码

```
#include <cstdio>

using namespace std ;

inline int Readin() {
	
	register int K = 0 ;
	register char C = getchar() ;
	for( ; C < '0' or C > '9' ; C = getchar() ) ;
	for( ; C <= '9' and C >= '0' ; C = getchar() )
		K = ( K << 1 ) + ( K << 3 ) + C - '0' ;
	return K ;
	
}

const int MaxN = 100005 ;

int N , A[MaxN] ;
int Stack[MaxN] , Top ;
int Ans[MaxN] ;

int main() {
	
	N = Readin() ;
	for(register int i = 0 ; ++i <= N ; A[i] = Readin() ) ;
	for(register int i = N ; i ; --i ) {
		while( Top and ( A[i] >= A[Stack[Top]] ) ) --Top ;
		Ans[i] = Stack[Top] ;
		Stack[++Top] = i ;
	}
	for(register int i = 0 ; ++i <= N ; printf( "%d\n" , Ans[i] ) ) ;
	return 0 ;
	
}
```

---

## 作者：颜祎宸yyc (赞：1)

这道题可以有两种写法

但如果用暴力会超时

```cpp
//第一种可以运用栈来写
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<string>
#include<cstring>
using namespace std;
int h[100001],ans[100001],s[100001];
int main(){
        int n;
        cin>>n;
        for(int i=1;i<=n;i++){
                cin>>h[i];
        }
        int top=0;
        s[++top]=1;
        for(int i=2;i<=n;i++){
                while(h[i]>h[s[top]]&&top>0){    //每一位与栈顶进行比较
                        ans[s[top]]=i;
                        top--;                                    //出栈
                }
                top++;
                s[top]=i;                                    //统一进栈
        }
        while(top>0){ans[s[top]]=0;top--;} //将栈中剩余元素清空
        for(int i=1;i<=n;i++){
                cout<<ans[i]<<endl;
        }
        return 0;
}
```
```cpp
//第二种是暴力搜索的改良版
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int h[100001],ans[100001];
int main(){
        int n;
        cin>>n;
        for(int i=1;i<=n;i++){
                cin>>h[i];
        }
        for(int i=n-1;i>=1;i--){
                if(h[i]<h[i+1]){
                        ans[i]=i+1;
                }
                else{
                        int j=ans[i+1];
                        while(1){
                                if(j==0)break;
                                if(h[i]<h[j]){ans[i]=j;break;}
                                if(h[i]>=h[j]&&j>0)j=ans[j];
            }
                }
        }
        for(int i=1;i<=n;i++){
                cout<<ans[i]<<endl;
        }
        return 0;
}

---

## 作者：zhengrunzhe (赞：1)

貌似也没有用STLstack的题解

于是来一发。思路楼下几个的都很明确了，不讲了。

```cpp
#include<stack>
#include<iostream>
using namespace std;
const int N=100001;
struct look{int h,p;};
int n,x,ans[N],i;
stack<look>s;
int main()
{
    cin>>n;
    for (i=1;i<=n;i++)
    {
        cin>>x;
        while (s.size() && x>s.top().h)ans[s.top().p]=i,s.pop();
        s.push((look){x,i});
    }
    for (i=1;i<=n;i++)cout<<ans[i]<<endl;
    return 0;
}
```

---

## 作者：卡车cckk (赞：0)

读题之后果断认为是我还不会的单调队列。。。
然后我曲线救题地想了个logn方搜索方法

**用线段树维护区间最大值，二分搜索答案 #滑稽**

大致是：建树后，对每一个牛i，询问i+1 - mid 和 mid+1 - n

mid即（i+1 + n）/2

若左区间最大的牛>当前牛，就缩到左边找

否则，若右区间最大的牛>当前牛，就缩到左边找

若两边区间都没有牛大的过当前牛直接输出0

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
struct Tree
{
	int maxx,a,b;
}tree[800000];
int c[100003];
int ma(int a,int b){return a>b?a:b;}
int n,x;
int create(int k,int a,int b)
{
	tree[k].a=a;
	tree[k].b=b;
	if(a==b){tree[k].maxx=c[a];return 0;}
	create(k*2,a,(a+b)/2);
	create(k*2+1,(a+b)/2+1,b);
	tree[k].maxx=ma(tree[k*2].maxx,tree[k*2+1].maxx);
}
int findd(int k,int a,int b)
{
	if(a<=tree[k].a&&tree[k].b<=b)
	{
		return tree[k].maxx;
	}
	int ans=0;
	if(a<=(tree[k].a+tree[k].b)/2)
		ans=ma(findd(k*2,a,b),ans);
	if(b>(tree[k].a+tree[k].b)/2)
		ans=ma(findd(k*2+1,a,b),ans);
	return ans;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&c[i]);
	}
	create(1,1,n);
	for(int i=1;i<n;i++)
	{
		int l=i+1,r=n,mid;
		while(l+1<r)
		{
			mid=(l+r)/2;
			if(findd(1,l,mid)>c[i])r=mid;
			else if(findd(1,mid+1,r)>c[i])l=mid+1;
			else break;
		}
		if(c[l]>c[i])printf("%d\n",l);
		else if(c[r]>c[i])printf("%d\n",r);
		else printf("0\n");
	}
	printf("0");
	return 0;
}
```

我这脑子看来是学不会单调队列了，以后这类题就用这个方法代替吧
logn方勉强能接受吧，大概也许

---

## 作者：Promise诺言 (赞：0)

这是一种链表的写法唔。

此题最难处置的是654321这类递减数据。

根据以下代表，每输入一个数就判断前面的数。

如果前面的大于后面的，就继续输入。

比如2 3 2 5····这个序列

先输入2和3。发现2比3小，于是将2的仰望对象设为3.再输入2时发现前面的一个数3比2大，继续输入5。

发现5比2大，将2的仰望对象填写后往前看。发现3仰望对象也是5.

此时第一个数已经看不见了，因为<cow[cow[j].head].tail=cow[j].tail;cow[cow[j].tail].head=cow[j].head;>一步已经将头尾更换。

第一次发题解。欢迎交友

```cpp
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
using namespace std;
int N;

struct news
{
    int longness;
    int number;
    int head;
    int tail;
}cow[100001];

int main()
{
    scanf("%d",&N);
    for (int i=1;i<=N;i++) {
        scanf("%d",&cow[i].longness);
        cow[i].head=i-1;
        cow[i].tail=i+1;
            for (int j=cow[i].head;j>=1;j=cow[j].head){
                if (cow[j].longness<cow[i].longness){
                    cow[cow[j].head].tail=cow[j].tail;
                    cow[cow[j].tail].head=cow[j].head;
                    cow[j].number=i;
                }
                else break;
            }
    }
    for (int i=1;i<=N;i++) printf("%d\n",cow[i].number);  
    return 0;
}
```

---

## 作者：syx2000121910 (赞：0)

单调栈，如果递减就入栈，如果是一个大于栈顶的数，那么就把栈顶元素不断弹出，使整个栈保持单调性。

那么可以出栈的元素都是比当前元素小的元素，这些小的元素的答案就指向当前元素。

最后还在栈里的元素，证明没有比这些元素大的元素了，那么这些元素答案为0；

```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#define INF 0x7fffffff
using namespace std;
int n,ans[1000080],top;
struct node{
    int pos,h;
}stack[1000080];
int main(){
    cin>>n;
    stack[top=0].h=INF;
    for(int i=1;i<=n;i++){
        int tmp;
        cin>>tmp;
        if(stack[top].h>=tmp){
            ++top;
            stack[top].h=tmp;
            stack[top].pos=i;
        }
        else{
            while(stack[top].h<tmp&&top>=1){
                ans[stack[top].pos]=i;
                --top;
            }
            ++top;
            stack[top].h=tmp;
            stack[top].pos=i;
        }
    }
    for(int i=1;i<=n;i++)cout<<ans[i]<<endl;
    return 0;
}
```

---

