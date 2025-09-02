# [ABC019A] 高橋くんと年齢

## 题目描述

高桥君忘记了自己的年龄。

他成功地找来了 3 个朋友，于是决定用这 3 个人预测的高桥君年龄的中位数，来代替高桥君的年龄。

请你代替高桥君，编写一个程序，从 3 个整数 $a,\ b,\ c$ 中求出中位数。

3 个整数的中位数是指将它们按从小到大排序后，处于中间位置的那个整数。

## 说明/提示

### 样例解释 1

$2,\ 3,\ 4$ 的中位数是 $3$。

### 样例解释 2

$5,\ 100,\ 5$ 的中位数是 $5$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2 3 4```

### 输出

```
3```

## 样例 #2

### 输入

```
5 100 5```

### 输出

```
5```

## 样例 #3

### 输入

```
3 3 3```

### 输出

```
3```

## 样例 #4

### 输入

```
3 3 4```

### 输出

```
3```

# 题解

## 作者：Elairin176 (赞：2)

一道大水题。   
我们可以把这三个数字看做一个数组，之后 sort，再输出中间数字即可。    
```cpp
#include <iostream>
#include <algorithm>
using namespace std;
int a[3];
int main(void){
	cin>>a[0]>>a[1]>>a[2];//读入
	sort(a,a+3);//排序
	cout<<a[1]<<endl;//输出中间数
}
```


---

## 作者：「已注销」 (赞：1)

## [`std::partial_sort`](http://zh.cppreference.com/w/cpp/algorithm/partial_sort)最棒了!
语法:
```cpp
void partial_sort( RandomIt first, RandomIt middle, RandomIt last );
```
重排元素，使得范围 $[first, middle)$ 含有范围 $[first, last)$ 中已排序的 $middle - first$ 个最小元素。
不保证保持相等的元素顺序。范围 $[middle, last)$ 中剩余的元素顺序未指定。

时间复杂度只有$O((last-first)log(middle-first) )$

本题为$3log2$
```cpp
#include<iostream>
#include<algorithm>
int main(){
	int a[3];
	std::cin>>a[0]>>a[1]>>a[2];
	std::partial_sort(a,a+2,a+3);
	std::cout<<a[1]<<'\n';
}
```

---

## 作者：Tomone (赞：1)

我发现我最近越来越喜欢用优先队列了
```cpp
#include<cstdio>
#include<iostream>
#include<string>
#include<vector>
#include<queue>
using namespace std;

priority_queue <int, vector<int>, greater<int> > q; //声明一个优先队列

int main()
{
	int tmp;
	for(int i=0;i<3;++i){
		cin>>tmp;
		q.push(tmp); //入队
	}
	q.pop(); //要中间的 所以让第一个出队
	cout<<q.top()<<endl; //出队（这是为中间的那个）
}
```
蒟蒻博客：www.aptx.xin
一些关于优先队列的用法https://www.aptx.xin/queue.html

---

## 作者：Andysun06 (赞：1)

### 一道水题，不用快排，冒泡就可以了。
#### 上代码：
    var n,m,i,j:longint;
    x:array[1..3]of longint;//方便交换
    begin
    readln(x[1],x[2],x[3]);//输入
    for i:=1 to 2 do//冒泡排序
     for j:=1+i to 3 do
    if x[i]<x[j] then
     begin
      n:=x[i];//交换
      x[i]:=x[j];
      x[j]:=n;
     end;
    writeln(x[2]);//输出
    end.

---

## 作者：LJC00111 (赞：1)

水题，只需排序，再输出第二个

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int a[4];
	for(int i=1;i<4;i++)
	cin>>a[i];
	sort(a+1,a+4);
	cout<<a[2]<<endl;
	return 0;
}
```

---

## 作者：Messi李 (赞：0)

这题可以用判断，还蛮简单

没有用排序，可能会麻烦一点

```
#include<bits/stdc++.h> //万能文件头
using namespace std;
int main(){
  int a,b,c;
    cin>>a>>b>>c; //输入
    if((a>=b && a<=c) || (a<=b && a>=c))
    //判断第一个数如果是三个数中的大小适中的那个数，就输出
    {
        cout<<a<<endl;
    }
    else if((b>=a && b<=c) || (b<=a && b>=c))
    //同理，第二个数如果是，就输出
    {
        cout<<b<<endl;
    }
    else if((c>=a && c<=b) || (c<=a && c>=b))
    //同理，如果是，就输出
    {
        cout<<c<<endl;
    }
}
```

如果是新手来做肯定是像我这样啦

在座给位大佬都是比较高级点，不过这个比较直接

---

## 作者：_newbie_ (赞：0)

```c
#include<cstdio>
#include<iostream> 
#include<cmath>
#include<cstring>
using namespace std;
int a[3];
int main()
{
	cin>>a[0]>>a[1]>>a[2];	
    for(int i=2;i>=0;i--)  //冒泡排序 
    {
    	for(int j=0;j<=i;j++)
    	{
    		if(a[j]<a[j-1])
    		swap(a[j],a[j-1]);
    	}
    }
	cout<<a[1]<<endl;  //输出中间的数		
	return 0;
}
```

---

