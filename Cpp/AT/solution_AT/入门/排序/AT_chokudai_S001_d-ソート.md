# ソート

## 题目描述

[problemUrl]: https://atcoder.jp/contests/chokudai_S001/tasks/chokudai_S001_d

数列 $ a $ を昇順ソートしたものを、スペース区切りにして $ 1 $ 行で出力してください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 100 $

## 样例 #1

### 输入

```
5
3 1 5 4 2```

### 输出

```
1 2 3 4 5```

## 样例 #2

### 输入

```
6
1 2 3 4 5 6```

### 输出

```
1 2 3 4 5 6```

## 样例 #3

### 输入

```
7
7 6 5 4 3 2 1```

### 输出

```
1 2 3 4 5 6 7```

## 样例 #4

### 输入

```
20
19 11 10 7 8 9 17 18 20 4 3 15 16 1 5 14 6 2 13 12```

### 输出

```
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20```

# 题解

## 作者：da32s1da (赞：4)

仔细观察，其实就是1~n的数字。
```
#include<cstdio>
int n;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)printf("%d ",i);
    puts("");
}
```

---

## 作者：Lyria (赞：1)

## 题意

给定一个数列 $a$ 与其个数 $n$，保证 $a$ 中含有 $1-n$ 的的所有正整数，输出将 $a$ 用递增序排好后的数列。

## 思路

- 由于 $a$ 中只含有 $1-n$，所以递增序后排好的数列必然在 $1-n$ 里，所以显然只要将 $1-n$ 顺序输出即可。

- 由于只是要求 $a$ 的递增序，考虑一般做法，只需将 $a$ 排序即可，选择较平稳的归并排序，时间复杂度会十分稳定。

## 代码

这里只给出思路 $2$ 的代码：

```cpp
#include<bits/stdc++.h>
#define N 1000005
using namespace std;
int a[N],tmp[N],n;
void mergesort(int lt,int rt){
    if(lt==rt) return ;
    int mid=(lt+rt)/2;
    mergesort(lt,mid);//排左半边
    mergesort(mid+1,rt);//排右半边
    int i=lt,j=mid+1,p=lt;
    while(i<=mid&&j<=rt){
    	if(a[i]<a[j]) tmp[p++]=a[i++];
    	else tmp[p++]=a[j++];
    }
    while(i<=mid){//如果左半边还有数
    	tmp[p++]=a[i++];
    }
    while(j<=rt){//如果右半边还有数
    	tmp[p++]=a[j++];
    }
    for(int k=lt;k<=rt;k++) a[k]=tmp[k];
    return ;
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
    	cin>>a[i];
    }
    mergesort(1,n);//排序边界
    for(int i=1;i<=n;i++){
    	cout<<a[i]<<" ";
    }
    return 0;
}
```

---

## 作者：jiangzhenghao (赞：1)

## 本人的第一篇题解，大佬勿喷
### ~~明明就是一道排序题，为何有人编了没过？~~

```
#include<iostream>
#include<algorithm>
using namespace std;
int main()
{
	int n,i,a[100];
	cin>>n;
	for(i=0;i<n;i++)
	cin>>a[i];
	sort(a,a+n);//我好像记得有一个排序函数叫sort
	for(i=0;i<n;i++)
	cout<<a[i]<<" ";
	return 0;
}
```

此为满分代码，请勿抄袭。

---

## 作者：不到前10不改名 (赞：0)

虽然这是道比快排模板还水的题，（~哪里水）但是，还是要好好做一下~
我们来手写快排，抵制sort！
```
#include<stdio.h>
int a[100001];//数据好像只有————100...
void abcd(int l,int r)//左端右端不解释
{int i=l,j=r,t;
int p=a[(l+r)/2];//这个吗，好像是————中点（当我没说）貌似是二分？
while(i<=j)
{
	while(a[i]<p)
	{i++;}
	while(a[j]>p)
	{j--;}//遍历（从左到中点p和从右到中点p）
	if(i<=j)
	{t=a[i]; 
	a[i]=a[j]; 
	a[j]=t;
	i++; 
	j--;}//交换
	}
	if(l<j)
	abcd(l,j);
	if(i<r)
	abcd(i,r); }
	int main()
	{	
	int i,n;	
 	scanf("%d",&n);   
  	for(i=1;i<=n;i++)   
    scanf("%d",&a[i]);   
    abcd(1,n);//调用函数  
    for(i=1;i<=n;i++)   
    printf("%d ",a[i]);  
    return 0;   
    }
```

---

## 作者：ztz11 (赞：0)

由题面可知，这是一道排序的模板体

因此，我们可以使用各种排序方法

比如说什么快排，堆排，桶排，泡排等等

这里来一个对新手最友好的--stl快排

实现见我的博客：[ztz11](https://www.cnblogs.com/ztz11/p/9296584.html)



代码：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int n,x[105];
int main()
{
	scanf("%d",&n);
	for(register int i=1;i<=n;i++)
	{
		scanf("%d",&x[i]);
	}
	sort(x+1,x+n+1);
	for(register int i=1;i<=n;i++)
	{
		cout<<x[i]<<" ";
	}
	cout<<endl;
}
```

---

## 作者：goodlearndaydayup (赞：0)

其实这道题就是非常裸的排序题~~（因为直接就是裸的）~~
我们可以用冒泡排序，很容易理解，适合新手们。
上C++代码
```cpp
#include<iostream>
#include<fstream>
#include<algorithm>
using namespace std;
int n ,num[999999];
int main()
{
     cin>>n;
	 for(int i=1;i<=n;i++)
		 cin>>num[i];
	 for(int i=n;i>=1;i--)
		 if(num[i]<num[i-1])swap(num[i],num[i-1]); //冒泡排序，小的往下冒
     for(int i=1;i<=n;i++)
		 cout<<num[i]<<" ";
    return 0;
}
```

---

