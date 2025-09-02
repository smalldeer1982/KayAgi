# INTERCALC

## 题目描述

DO YOU EXPECT ME TO FIND THIS OUT?

WHAT BASE AND/XOR LANGUAGE INCLUDES string?

DON'T BYTE OF MORE THAN YOU CAN CHEW

YOU CAN ONLY DISTORT THE LARGEST OF MATHEMATICS SO FAR

SAYING "ABRACADABRA" WITHOUT A MAGIC AND WON'T DO YOU ANY GOOD

THE LAST STACK RUPTURES. ALL DIE. OH, THE EMBARRASSMENT!

I HAVE NO ARRAY AND I MUST SCREAM

ELEMENTS MAY NOT BE STORED IN WEST HYPERSPACE

## 样例 #1

### 输入

```
4
2 5 3 1
```

### 输出

```
4
```

# 题解

## 作者：PC_DOS (赞：5)

愚人节题目，要求藏在那一串"诗"里面。

DO YOU EXPECT ME TO **FIND** THIS OUT?

WHAT BASE AND/**XOR** LANGUAGE INCLUDES string?

DON'T BYTE **OF** MORE THAN YOU CAN CHEW

YOU CAN ONLY DISTORT **THE LARGEST** OF MATHEMATICS SO FAR

SAYING "ABRACADABRA" WITHOUT A MAGIC **AND** WON'T DO YOU ANY GOOD

**THE LAST** STACK RUPTURES. ALL DIE. OH, THE EMBARRASSMENT!

I HAVE NO **ARRAY** AND I MUST SCREAM

**ELEMENTS** MAY NOT BE STORED IN WEST HYPERSPACE

所以，题目的要求是: 求出所给数组中最大值和最后一个元素的异或(XOR)值!

代码:
```
#include <iostream>
using namespace std; //头文件和命名空间
int main(){
	ios::sync_with_stdio(false); //输入输出加速
	int iMax=0, nCount, iInput, i,iAns; //iMax-最大项，nCount-总项数，iInput-当前输入的数，i-循环变量，iAns-答案
	cin >> nCount; //输入总项数
	for (i = 1; i <= nCount; ++i){ //循环读入
		cin >> iInput; //读入
		if (iInput > iMax){ //判定最大值
			iMax = iInput;
		}
	}
	iAns = iMax^iInput; //求最大值和最后一项的异或
	cout << iAns; //输出
	return 0; //结束
}
```

---

## 作者：谷民 (赞：2)

## CF784C 【INTERCALC】

#### 要求：求出所给数组中最大值和最后一个元素的异或（XOR）值

那么，什么是异或？

异或操作就是在各种计算机语言中，如C、C++、java等，使用按位异或的思想执行的操作。

x是二进制数0101；
y是二进制数1011；
则结果为x^y=1110；

只有在两个比较的位不同时其结果是1，否则结果为0。
即“相同为0，不同为1”。 

（选自百度百科）


------------

明白了异或，实现很简单，AC代码附上：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n;
	int a[20];//数据范围很水 
	cin>>n;//输入 
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	int x=a[n];//最后一个元素
	sort(a+1,a+n+1);//数据水，可以用sort排序取最大值
	int y=a[n];//取最大值
	int ans=x^y;//取异或
	cout<<ans;//输出 
	return 0;
}
```

---

## 作者：Kevin_Zhen (赞：1)

题目链接 [CF784C](https://www.luogu.com.cn/problem/CF784C)。
## 解题思路
输入的时候全部压进优先队列里，最后输出最后一个元素和堆顶元素的异或值即可。
## AC CODE
```cpp
#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;

int n, a;
priority_queue<int> q;

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		int t;
		scanf("%d", &t);
		q.push(t);
		if (i == n) a = t;
	}
	printf("%d", q.top() ^ a);
	return 0;
}
```
## 感谢观赏！

---

## 作者：hensier (赞：1)

这道题其实可以不需要输出，也不需要$max,sort$等函数。只需要重复输入并不停地替换最大值即可。

$AC$代码：~~（最短代码？）~~

```cpp
#include<cstdio>
int M,n,t;
int main()
{
    scanf("%d",&n);//输入个数
    while(n--){scanf("%d",&t);if(t>M)M=t;}//输入并替换最大值
    printf("%d",M^t);//最后一个元素就是最后一个输入进来的，这是取异或
}
```

---

## 作者：18lxxrz (赞：1)

巨佬都用数组，蒟蒻我来一发不用数组的

------------

```cpp
#include<bits/stdc++.h>
using namespace std;

int main ()
{
	int n,x,Max=-999;//Max用来保存最大值，由于x会自动更新，剩下的值就是最后一个数了
	 
	scanf("%d",&n);//scanf输入加速 
	
	while(n--)
		scanf("%d",&x),Max=max(Max,x);//循环输入x，并用max求取最大值
	printf("%d",x^Max);//^表示异或，直接用就好了 
	return 0*puts("");
}
```



---

## 作者：CZQ_King (赞：0)

由于这题数据小$(1<=n<=10)$，所以可以一行输入一行输出过？

有个巧妙的地方：

可以使用``while(n--)``来输入，节省变量$i$，此时数组是倒过来的，即如果输入$1\ 2\ 3\ 4$那么数组里就是$4\ 3\ 2\ 1$。那么最后一个元素就在$a[0]$中了。

代码：
```C++
#include<bits/stdc++.h>
using namespace std;
int n,a[16];
int main(){
    cin>>n;while(n--)cin>>a[n];//输入
    cout<<(max(a[0],max(a[9],max(a[8],max(a[7],max(a[6],max(a[5],max(a[4],max(a[3],max(a[2],a[1])))))))))^a[0]);//照题意模拟，找出最大值再异或
}
```

---

## 作者：TRZ_2007 (赞：0)

转了一圈，发现没有用优先队列的。  
看到最大值就该想起优先队列啊！  
只不过这里需要改一点东西。  
平常的优先队列定义是这样的  
```
priority_queue<int,vector<int>,greater<int> > num;
```
这代表从小到大来排序，那么这里就最大值，该怎么改呢？  
很简单，只需要把$greater$改成$less$就行了。  
$code$
```
#include <bits/stdc++.h>
using namespace std;
priority_queue<int,vector<int>,less<int> > num;
int main()
{
	int n,x;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>x;
		num.push(x);
	}
	cout<<((num.top())xor(x))<<"\n";//异或可以用xor来运算
}
```

---

