# Crunching Numbers Just for You

## 题目描述

你正在为销售机票的网站开发一项新功能：按能够对价格进行票分类照片你已经提取了票价，所以只有最后一步要做...

## 样例 #1

### 输入

```
3 3 1 2
```

### 输出

```
1 2 3 
```

# 题解

## 作者：做梦想Peach (赞：4)

这题一看嘛，就是排序，突然灵光一现——$STL$里有$sort$![/xyx](https://cdn.luogu.com.cn/upload/pic/62230.png)，来看看代码吧。

时间复杂度 $O(n log n)$
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
int main () {
	int a[10],n,i;
	scanf ("%d",&n);
	for (i=0;i<n;i++) scanf ("%d",&a[i]);
	sort (a,a+n);//直接排序（从小到大）
	for (i=0;i<n;i++) printf ("%d ",a[i]);//直接输出即可。
	return 0;
}
```
下面我又看到了$1<=a_i<=100$，这么小，让我突然想到了桶！![/se](https://cdn.luogu.com.cn/upload/pic/62244.png)

桶排序的思想就是用一个数组记录$x$在输入序列中出现的次数，然后直接从头至尾的查找$a[i]$是否大于等于1，如果大于等于1的话就输出$a[i]$次$i$。

下面我们来看代码。
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
int a[110],n,i,x,j;//a就是桶。
int main () {
	scanf ("%d",&n);
	for (i=0;i<n;i++) 
        scanf ("%d",&x),a[x]++;//记录x出现的次数。
	for (i=0;i<110;i++) 
	    if (a[i]>=1) {
	        for (j=a[i];j>0;j--)
	            printf ("%d ",i);//输出。
	    }
	return 0;
}
```
结束啦，再见！


---

## 作者：Dream_It_Possible (赞：3)

此题就是个排序。

我用了优先队列。

# 优先队列
优先队列容器与队列一样，只能从队尾插入元素，从队首删除元素。但是它有一个特性，就是队列中最大的元素总是位于队首，所以出队时，并非按照先进先出的原则进行，而是将当前队列中最大的元素出队。这点类似于给队列里的元素进行了由大到小的顺序排序。元素的比较规则默认按元素值由大到小排序，可以重载“<”操作符来重新定义比较规则。

优先级队列可以用向量(vector)或双向队列(deque)来实现(注意list container不能用来实现queue，因为list的迭代器不是任意存取iterator，而pop中用到堆排序时是要求randomaccess iterator 的!)： priority_queue<vector<int>, less<int> > pq1; 　　　 // 使用递增less<int>函数对象排序 priority_queue<deque<int>, greater<int> > pq2; 　　// 使用递减greater<int>函数对象排序 其成员函数有“判空(empty)” 、“尺寸(Size)” 、“栈顶元素(top)” 、“压栈(push)” 、“弹栈(pop)”等。


## **基本操作**：

empty() 　　 如果队列为空，则返回真

pop()　　　　删除对顶元素，删除第一个元素

push() 　　 加入一个元素

size() 　　　 返回优先队列中拥有的元素个数

top() 　　　　返回优先队列对顶元素，返回优先队列中有最高优先级的元素

code:
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
priority_queue<int,vector<int>,greater<int> >a;//大根堆，升序。
inline void read(int &a)//快读
{
	int k=1; a=0; char c=getchar();
	while(c<'0'||'9'<c){if(c=='-')k=-1; c=getchar();}
	while('0'<=c&&c<='9'){a=a*10+c-'0'; c=getchar();}
	a*=k;
}
int main()
{
	int n,i,j;
	cin>>n;
	for (i=1;i<=n;i++)
	{
		int b;
		read(b);
		a.push(b);
	}
	for (i=1;i<=n;i++)
	{
		printf("%d ",a.top());
		a.pop();
	}
	return 0;
}
```

---

## 作者：Kevin_Zhen (赞：1)

## 归并排序解法
题目链接 [CF784F](https://www.luogu.com.cn/problem/CF784F)。  
这里用的是**归并排序**。归并排序具体可以用于[求逆序对](https://www.luogu.com.cn/problem/P1908)的实现。
## AC CODE
```cpp
#include <iostream>
#include <cstdio>
using namespace std;

int n;
int a[110], m[110];

void msort(int l, int r) {
	if (l == r) return;
	int mid = l + r >> 1;
	msort(l, mid); msort(mid + 1, r);
	int i = l, j = mid + 1, k = l;
	while (i <= mid && j <= r) {
		if (a[i] <= a[j]) m[k++] = a[i++];
		else m[k++] = a[j++];
	}
	while (i <= mid) m[k++] = a[i++];
	while (j <= r) m[k++] = a[j++];
	for (int p = l; p <= r; ++p) a[p] = m[p];
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	msort(1, n);
	for (int i = 1; i <= n; ++i) printf("%d ", a[i]);
	return 0;
}
```
## 感谢观赏！

---

## 作者：PragmaGCC (赞：1)

看到这道题，我直接写了一个快排（STL不香吗）。

不懂快排的去看[P1177 【模板】快速排序](https://www.luogu.com.cn/problem/P1177)

直接上code：
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int a[15],n;
void qsort(int l,int r){
	int mid=a[(l+r)>>1],i=l,j=r,p;
	do{
		while(a[i] < mid) i++;
		while(a[j] > mid) j--;
		if(i <= j){
			p=a[i];a[i]=a[j];a[j]=p;
			i++;j--;
		}
	}while(i <= j);
	if(l < j) qsort(l,j);
	if(i < r) qsort(i,r);
	return ;
}
int main(){
	//freopen("putin.txt","r",stdin);
	//freopen("putout.txt","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	qsort(1,n);
	for(int i=1;i<=n;i++){
		printf("%d ",a[i]);
	}
	return 0;
}
```
STL不用我说了吧。。。

---

## 作者：Franka (赞：0)

~~一道排序的模板题我竟然提交了n次（感觉我好蒻啊~~
### **题目**
将n个数**从小到大**排序。

注意：**n和这些数是在同一行**。
### **思路**
#### 注意$a_i$，发现$a_i$并不大，因此可以用桶排；
#### 注意$n$，发现$n$也不大，因此可以用选排、插排、快排、冒泡。
### **代码**
#### 桶排
```pascal
var n,i,j:longint;a:array[1..100] of longint;//定义
begin
 read(n);//读入n
 for i:=1 to n do//n个数
  begin
   read(x);inc(a[x]);//累加桶
  end;
 for i:=1 to 100 do//1到100
  for j:=1 to a[i] do write(i,' ');//输出
end.
```
#### 选排
```pascal
var n,i,j:longint;a:array[0..10] of longint;//定义
begin
 read(n);//读入n
 for i:=1 to n do read(a[i]);//读入a数组
 for i:=1 to n-1 do for j:=i+1 to n do//指定两个不同的数
  if a[i]>a[j] then//从小到大
   begin
    a[i]:=a[i]+a[j];a[j]:=a[i]-a[j];a[i]:=a[i]-a[j];//加减法交换
   end;
 for i:=1 to n do write(a[i],' ');//输出a数组
end.
```


---

## 作者：hensier (赞：0)

首先，快排$sort$可以一遍过，因此这里不再介绍。

对于$C$语言来说，可以采用二分排序。

```c
#include<stdio.h>
int n,i,j,a[10];
int main()
{
    scanf("%d",&n);
    for(;i<n;i++)scanf("%d",&a[i]);//输入
    for(i=1;i<n;i++)//二分
    {
        int t=a[i],low=0,high=i-1,mid=-1;//定义t、low、high、mid（一开始为-1）
        while(low<=high)//区间循环
        {
            mid=(low+high)/2;//mid赋值
            if(t<a[mid])high=mid-1;//小就high=mid-1
            else low=mid+1;//否则low=mid+1
        }
        for(j=i-1;j>=low;j--)a[j+1]=a[j];//替换
        if(low-i)a[low]=t;//low!=i的话就把a[low]赋值为t
    }
    for(i=0;i<n;i++)printf("%d ",a[i]);//输出
}
```

当然，还有一种使用不多的$qsort$。注意，$qsort$与$sort$是有明显区别的。因此我们必须要注意其用法。$qsort$的格式也需要注意，其格式为：

$\red{\text{qsort(数组,数组元素个数,数组类型大小,顺序)}}$

|数组名|数组元素个数|数组类型大小|顺序函数|
| :----------: | :----------: | :----------: | :----------: |
|$a$|$n$|$sizeof(int)$或$sizeof(a[0])$或$4$|$compare$|

$\red{\text{注意！注意！注意！正规C语言是没有bool类型的，如果用bool的话会CE！}}$

所以可以使用$int$，参数用$void*$，返回值为$**$（双指针）。

完整代码：
```c
#include<stdio.h>
#include<stdlib.h>
int n,i,a[10];
int cmp(void *a,void *b)//比较函数
{
    return *(int*)a-*(int*)b;
}
int main()
{
    scanf("%d",&n);
    for(;i<n;i++)scanf("%d",&a[i]);//输入
    qsort(a,n,sizeof(int),cmp);//qsort
    for(i=0;i<n;i++)printf("%d ",a[i]);//输出
}
```

---

## 作者：Arghariza (赞：0)

这题很容易知道是排序。

那我来介绍一下2种经典的排序。

1. sort排序（STL）

>众所皆知，Algorithm头文件里面有一个大名鼎鼎的排序函数——sort()，使用时如果从小到大，只用传递两个参数：a + 1, a + n + 1（a是数组名），sort的用法大家都知道，我就不在此赘述了

>主要我是想说```#include <functional>```里面的```less<int> ()```，这个是充当sort函数第3个参数（也就是大小函数），表示从小到大排序，譬如:sort(a + 1, a + n + 1, less<int> ())表示把整型数组a的第1位到第n + 1位从小到大排序
  
>相信现在不难得出代码：
  
```#include <iostream>
#include <functional>
#include <algorithm>
using namespace std;

int n, a[100001];

int main() {
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];
    sort(a + 1, a + n + 1, less<int> ());
    for(int i = 1; i <= n; i++) cout << a[i] << " ";
    return 0;
}
```
                                                
2.桶排序
>什么是桶？桶就等于一个标记，我们可以这样：用一个一维数组vis[]->vis[i]表示的是数组a中i出现的次数，最后我们从尾到头扫一次只要vis[i] != 0即可

```
#include <iostream>
using namespace std;

int n, a[100001], vis[100001];

int main() {
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        vis[a[i]]++;
    }
    for(int i = 0; i <= 100001; i++) {
        if(vis[i]) {
            for(int j = 1; j <= vis[i]; j++) cout << i << " ";
        }
    }
    return 0;
}  
```

---

## 作者：USS_Enterprise (赞：0)

这一道题，可以用STL来做。

首先，程序输入了一个$n$，为个数。
接着，从$1$~$n$输入$a_i$，$STL$会自动排序，所以，省了排序的时间。

```c
map<int,int> a;//由于不清楚是否会重复，所以要加计数器
cin >> n;
for(int i = 1; i <= n; i++){
	int o;
	cin >> o;
	a[o]++;
}
```
注意，$map$的头文件不能少。

输出如下：

```
for(map<int, int>::iterator it = a.begin(); it != a.end(); it++){
	for(int i = 1; i <= it -> second; i++)//it->……是一种指针用法
    //it->second是输出的次数
	cout << it ->first << ' ';//即输出输入过的数
}
```
结束，你就可以$AK$了！

---

## 作者：TRZ_2007 (赞：0)

自从可以用$STL$之后，C++党就越来越懒了……  
于是，本蒟蒻打算安慰一下没有$STL$的P党……  
于是，就有了冒泡排序  
$code$
```
#include <bits/stdc++.h>
using namespace std;
int num[100];
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>num[i];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=i;j++)
			if(num[i]<num[j])
				swap(num[i],num[j]);
	for(int i=1;i<=n;i++)
		cout<<num[i]<<" ";
}
```
PS:敲了这题后才发现，自己快排都不会打了……

---

## 作者：qwerta (赞：0)

AC的时候我是不敢相信的（堂堂CF愚人节题目竟然没有坑？！

想像中愚人节高级限定的画风[April Fools Day Contest 2016--Da Vinci Powers](http://codeforces.com/contest/656/problem/A)

按照题意读入然后排序就行了，数据极小（n<=10），爱怎么排都可以

没！有！坑！

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int a[17];
int main()
{
    int n,i;
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    scanf("%d",&a[i]);
    sort(a+1,a+n+1);
    for(i=1;i<=n;i++)
    printf("%d ",a[i]);
    return 0;
}
```

---

