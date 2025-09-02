# Garden

## 题目描述

Luba thinks about watering her garden. The garden can be represented as a segment of length $ k $ . Luba has got $ n $ buckets, the $ i $ -th bucket allows her to water some continuous subsegment of garden of length exactly $ a_{i} $ each hour. Luba can't water any parts of the garden that were already watered, also she can't water the ground outside the garden.

Luba has to choose one of the buckets in order to water the garden as fast as possible (as mentioned above, each hour she will water some continuous subsegment of length $ a_{i} $ if she chooses the $ i $ -th bucket). Help her to determine the minimum number of hours she has to spend watering the garden. It is guaranteed that Luba can always choose a bucket so it is possible water the garden.

See the examples for better understanding.

## 说明/提示

In the first test the best option is to choose the bucket that allows to water the segment of length $ 3 $ . We can't choose the bucket that allows to water the segment of length $ 5 $ because then we can't water the whole garden.

In the second test we can choose only the bucket that allows us to water the segment of length $ 1 $ .

## 样例 #1

### 输入

```
3 6
2 3 5
```

### 输出

```
2
```

## 样例 #2

### 输入

```
6 7
1 2 3 4 5 6
```

### 输出

```
7
```

# 题解

## 作者：Alex_Wei (赞：13)

#### 看题意就知道这是道排序题（其实不排序更简单，而且更快）

### 思路：先把给定的数列排序，然后从大到小枚举除k余0的数，即x∣k

就拿这题练练排序吧，顺便复习一下，思路已经很清楚了

### 1.优先队列（会的可以跳过）

1.1  这里要用到STL的priority_queue <int> q：制造一个优先队列q，**我们无论按照什么顺序push一堆数，最终在队列里总是top出最大的元素**
  
1.2  如果想要从小到大排序，可以这么写：
  
- priority_queue<int, vector<int>, greater<int> >q;
  
- 也可以重载运算符号，不过比较麻烦，这里不再赘述
  
#### 1.3  优先队列的常用运算符：

- #### push（a）：把a压进优先队列
  
- #### top（）：查询优先队列的最大数
  
- #### pop（）：弹出优先队列的最大数
  
1.4  有了优先队列这个东西，我们很容易就可以排序啦

### 1.5  代码
```cpp
//priority_queue优先队列排序
#include<bits/stdc++.h>
using namespace std;
priority_queue <int> s;
int n,k,a;
int main()
{
	cin>>n>>k;
	for(int x=1;x<=n;x++)cin>>a,s.push(a);//把输入的数一个一个压进去
	for(int x=1;x<=n;x++){
		if(!(k%s.top()))cout<<k/s.top(),exit(0);//如果可以整除就输出
		//因为是从大到小排序，所以可你保证答案的正确性 
		s.pop();
	}
	return 0;
}
```
### 2.归并排序（mergesort）

#### 2.1  归并排序主要用到了递归+合并的思想方法

#### 2.2  归并排序的主要思路

- mergesort（l，r）表示把区间【l，r】排成有序的 

2.2.1  递归边界：l==r则返回

2.2.2  定义m为（l+r）/2

2.2.3  **因为mergesort（l，r）先要保证区间【l，m】与区间【m+1，r】已经是有序的**，所以我们先递归mergesort（l，m）和mergesort（m+1，r）

### 2.2.4  归并排序的核心思想！（从大到小排序）

- 设 lp：区间【l，m】已经选到了第lp个数，初始值为l

- rp：区间【m+1，r】已经选到了第rp个数，初始值为m+1

- s：区间【l，r】已经排好了s个数，初始值为0

- b数组：已经排好的区间【l，r】，为了防止排序的时候把原数据覆盖掉

- 非常关键的一步：当a[lp]>a[rp]时，我们就把a[lp]放进b数组，lp++，否则就把a[rp]放进b数组，rp++

- s++

- 当其中一个区间已经全部选完，还有一个没有选完的时候，把这个区间剩下的数按顺序全部放进b数组

### 2.3 贴两张图更有助于理解：

![](https://cdn.luogu.com.cn/upload/pic/52331.png)

![](https://cdn.luogu.com.cn/upload/pic/52334.png)

### 2.4 在这种方法下，得到的b数组一定是有序的，因为区间【l，m】和区间【m+1，r】都是有序的

#### 2.5 学会归并排序后，也可以十分轻松的A掉这题

### 2.6 核心代码

```cpp
void mergesort(int l,int r)
{
	if(l>=r)return;//递归边界 
	int m=(l+r)/2,b[110],lp=l,rp=m+1,s=0;
	mergesort(l,m);//先要保证区间【l，m】是排好序的 
	mergesort(m+1,r);//同上
	while(lp<=m&&rp<=r){//当两个区间都没有被选完 
		if(a[lp]>a[rp])
			b[s]=a[lp],lp++;
		else b[s]=a[rp],rp++;//选择较大的数放进b数组 
		s++;
	}
	while(lp<=m)b[s]=a[lp],lp++,s++;//特判，把剩下的数全部放进b数组 
	while(rp<=r)b[s]=a[rp],rp++,s++;//同上
	for(int x=l;x<=r;x++)a[x]=b[x-l];//再把b数组赋给a数组
}
```
#### 3.当然，普通的写法更简单，时间复杂度也更低，这里就不再详写了

希望我的这篇题解能给你带来帮助

#### 如果有错误或疑问欢迎在右侧——>评论区留言或私信

码字不易，给个赞吧，谢谢！

---

## 作者：Clever_Jimmy (赞：4)

题意太简洁明了使这道本来应该出在英语阅读理解里面的题变成了一道水题……

```c
#include <stdio.h>
#include <stdlib.h>
int main()
{
	int n,k,i,min=10000,ans=0,t;
/*
	n,k是题目里面的量；
    i是用来循环的量；
    min来存储最小值（所以预设值要尽量的大）；
    ans来储存比值；
    t是用来储存数据的临时变量。
*/
    scanf("%d %d",&n,&k);//先输入n与k
    for(i=0;i<n;i++)
    {
		scanf("%d",&t);//输入到一个变量t里面
        if(k%t==0)//先看能不能整除
		{
			ans=k/t;
			if(ans<min)//如果还有更小的
				min=ans;//更新答案
        }
    }
    printf("%d",min);//把最小的输出
	system("pause");
	return 0;
}

```
直接复制会爆0(善意的提醒)

---

## 作者：Arghariza (赞：1)

我们想一下如何满足一个```min(k / x) (x ∈ A, x ∣ k)```呢？

首先我们的```k```值是一定的，所以求最小值必定是关于```x```的，所以```x```要尽量大，并且```k mod x = 0```，也就是```x | k```（```x```能被```k```整除）

那我们可以把```a```数组从大到小排序，只要```a[i]```能整除k，就输出并跳出循环

接下来就是代码实现了

- 首先是定义变量（不用说吧）：

```
int n, k, a[100001];
```

- 接着输入（也不用说吧）：

```
cin >> n >> k;
for (int i = 1; i <= n; i++) cin >> a[i];
```

- 接下来是STL中的排序加上```#include <functional>```中的从大到小排序规则函数```greater<int> ()```（其实和```bool cmp(int a, int b) {return a > b}```一样，应该也不用说）：

```
sort(a + 1, a + n + 1, greater<int> ());
```

- 然后我们一个一个数组成员地遍历，如果```k % a[i] == 0```，则输出```k / a[i]```：

```
for (int i = 1; i <= n; i++) {	//遍历成员
    if (k % a[i] == 0) {	  	//如果整除
        cout << k / a[i];	  	//输出答案
        break;				  	//跳出循环
    }
}
```

所以整个代码就出来了：

```
#include <iostream>
#include <algorithm>
#include <functional>
using namespace std;

int n, k, a[100001];

int main() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];
    sort(a + 1, a + n + 1, greater<int> ());
    for (int i = 1; i <= n; i++) {
        if (k % a[i] == 0) {
            cout << k / a[i];
            break;
        }
    }
    return 0;
}
```

---

## 作者：FP·荷兰猪 (赞：1)

**发一篇纯c++题解**


此题还是很水的。

先把a[1]到a[n]从大到小快排一遍，然后从头查找能被k整除的，找到就打印，跳出。

```cpp
#include <bits/stdc++.h>
using namespace std;
bool cmp(int a,int b)//从大到小快排
{
    return a>b;
}
int main()
{
    int n,k;
    cin>>n>>k;
    int a[n+1],i;
    for (i=1;i<=n;i++)
    {
        cin>>a[i];
    }
    sort(a+1,a+n+1,cmp);
    for (i=1;i<=n;i++)//从头开始枚举
    {
        if (k%a[i]==0)//查找第一个能被k整除的数
        {
            cout<<k/a[i]<<endl;
            return 0;//找到，直接结束
        }
    }
    return 0;
}
```

---

## 作者：konglk (赞：0)

这题用不到什么排序吧

连数组都用不到，在输入的时候与当前最小值比较即可 ~~看到题目标签快排弄得我还以为有什么坑点我没意识到~~ min函数想必大家都知道，这题就很简单了

```cpp
#include<iostream>
#include<cstring>
using namespace std;
int main()
{
	int n,k,x,mi=2147483646;//这是2的31次方-1-1，一般很少有比这个再大的数
	cin>>n>>k;
	while(n--)
	{
		cin>>x;
		if(k/x==k/(double)x)/*用来判断int形态下是否和double下相等，相等则是整数*/mi=min(mi,k/x);//与当前最小值比较
	}
	cout<<mi<<endl;
 } 
```


---

## 作者：PrefixAMS (赞：0)

# 一道排序题，很适合初学者练习

[如果题目看不懂，可以来这里](https://www.luogu.org/discuss/show/32185)

#### 主要看一下样例

只能用一个水桶（这里很重要）

话不多说上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int k,a[10010];
int main()
{
   freopen("garden.in","r",stdin);
   freopen("garden.out","w",stdout);
   ios :: sync_with_stdio(false);
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+n+1);
	//cout<<"a "<<a[2]<<endl;  debug
	for(int i=n;i>=1;i--)
	{   //cout<<"a["<<i<<"]="<<a[i]<<endl; debug
		if(k%a[i]==0) {
			cout<<k/a[i];
			return 0;
		}
	}
	return 0;
}
```

代码有反作弊
最好不要 Ctrl-C Ctrl-V

粘贴复制毁一生

---

## 作者：温情 (赞：0)

算法标签都是快排,此处应有手写快排...

其实不嫌麻烦的话还可以写个判断质数的函数,如果k是一个质数的话直接输出k就可以了0.0.

```cpp
#include<bits/stdc++.h>
using namespace std;
int sz[1001];
void qqsort(int l,int r)
{
	int mid=sz[(l+r)/2];
	int i=l,j=r,temp;
	do
	{
		while(sz[i]>mid)
			i++;
		while(sz[j]<mid)
			j--;
		if(i<=j)
		{
			temp=sz[i];
			sz[i]=sz[j];
			sz[j]=temp;
			i++;
			j--;
		}
	}while(i<=j);
	if(l<j)
		qqsort(l,j);
	if(i<r)
		qqsort(i,r);
}
int main()
{
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=n;i++)
		cin>>sz[i];
	qqsort(1,n);
	for(int i=1;i<=n;i++)
	{
		if(k%sz[i]==0)    //使用取余是因为k/sz[i]的话是会误判的
		{
			cout<<k/sz[i];
			return 0;
		}
	}
	cout<<k;
	return 0;
}
```

---

## 作者：Loner_Knowledge (赞：0)

纯模拟

---

这道题只需要对每个数进行判断即可，甚至连数组都可以不用。


```cpp
#include<cstdio>
int main() {
    int n,k,ans=0x7FFFFFFF;
    scanf("%d%d",&n,&k);
    for(int i=0,j;i<n;++i) {
        scanf("%d",&j);
        if(!(k%j)&&k/j<ans)    //判断是否能整除和是否能更新答案
            ans=k/j;
    }
    printf("%d",ans);
    return 0;
}
```

---

---

