# 最大値

## 题目描述

请输出排列 $a$ 的最大值。

## 说明/提示

对于 $100\%$ 的数据，$1 \le n \le 100$。

## 样例 #1

### 输入

```
5
3 1 5 4 2```

### 输出

```
5```

## 样例 #2

### 输入

```
6
1 2 3 4 5 6```

### 输出

```
6```

## 样例 #3

### 输入

```
7
7 6 5 4 3 2 1```

### 输出

```
7```

## 样例 #4

### 输入

```
20
19 11 10 7 8 9 17 18 20 4 3 15 16 1 5 14 6 2 13 12```

### 输出

```
20```

# 题解

## 作者：da32s1da (赞：16)

说实话我真不知道数据这么水

~~观察样例得知，答案为n~~
```
#include<cstdio>
int a;
int main(){
    scanf("%d",&a);
    printf("%d\n",a);
}
```

---

## 作者：06ray (赞：3)

这道题是一道很基础的题目，直接打擂台就可AC。而我用的是优先队列的方法。什么是优先队列呢？说白了就是一种以一定的优先级可以自动排序的队列。

首先读入n，接着读入n个数，每读入一个数，就用用push这个操作把这个数放进优先队列里，这时系统已经会把你所插入的数从大到小排好序。

最后用top操作输出优先级最高的那个数。

头文件是#include < queue >


最后贴代码（也就17行）。
```cpp
#include <iostream>//头文件
#include <queue>
using namespace std;//名字空间
priority_queue<int> q;//定义一个优先队列
int main()
{
	int n;
	cin>>n;
	for(int i=1; i<=n; i++)
	{
		int a;
		cin>>a;//读入一个数
		q.push(a);//将数插入优先队列中
	}
	cout<<q.top();//输出优先级最高的一个元素 
	return 0;
}

```
 

---

## 作者：小可爱三岁七 (赞：2)

额。。。入门水题（最近刷上瘾了233....）

思路是这样的：维护一个$maxx$表示当前最大的是多少，然后比较输入的数和现在的$maxx$比较，取较大的值作为$maxx$.
代码如下：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;//头文件不解释
int n;
int now;//打酱油的的变量
int maxx;
int main()
{
	scanf("%d",&n);//n个数
	for(int i=1;i<=n;i++)//循环输入
	scanf("%d",&now),
	maxx=max(maxx,now);//在线更新
	printf("%d",maxx);
	return 0;//程序拜拜。
}
```


---

## 作者：碎月 (赞：1)

sort（看dalao们代码都~~贼长~~其实是我看不懂

来一波小白白白福利


    #include <iostream>
    #include <algorithm>
    int a[233];
    int main () {
        int n;
        std::cin >> n;
        for (int i = 1;i <= n;i++)
            std::cin >> a[i];	
        std::sort (a+1,a+n+1);
        std::cout << a[n];
        return 0;
    }

---

## 作者：Soyilieber (赞：1)

来一个~~简单~~的。
不用排序，也不用数组，直接边读边比较。
```
var
    i,a,n,ans:longint;
begin
    readln(n);
    for i:=1 to n do
        begin
            read(a);
            if a>ans then ans:=a;
        end;
    writeln(ans);
end.
```

---

## 作者：panda_wang (赞：1)

# 【题意】
### 给出一个整数 n , 并给出数组 a[n] , 求 a[n] 中的最大值
# 【解决方法】
### 使用语言：C++
### 解决方案：先定义值MAX，赋值数组第一个元素，或赋值INT_MAX，然后遍历数组，查找比MAX更大的数，如果存在，继续把MAX赋值给a[i]
### 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n; cin >> n;
    
    int a[n]; 
    for (int i = 0 ; i < n ; i ++) {cin >> a[i];}
    
    int MAX = a[0]; 
    for (int i = 0 ; i < n; i ++)
    {
        if (a[i] > MAX)
        {
            MAX = a[i];
        }
    }
    cout << MAX;
}
```
# 【题目分析】
### 为啥要把MAX赋给第一个元素？
### 答：其实赋给哪个元素，甚至哪个值都可以（比如刚刚讲的INT_MAX），最重要的还是if判断部分的赋值及条件是否写正确。

---

## 作者：远山淡影 (赞：0)

快排之后输出最后一个就行了。
```cpp
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
bool cmp(int n1,int n2)
{
	if(n1>n2) return 0;
	if(n2>n1) return 1;
	return 0;
}
int n,a[1000001];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	sort(a+1,a+n+1,cmp);
	printf("%d",a[n]);
	return 0;
}
```
快排很有用，一定要背。（神犇scy说的。。。）

---

