# Gravity Flip

## 题目描述

小克里斯在物理课上很无聊（太容易了），所以他建了一个玩具箱让自己的有事做。这个盒子很特别，因为它有改变重力的能力。 盒子内排列 NN 列的玩具立方体。第$i$列包含$A_i$个立方体。首先，盒子里的重力向下拉动立方体。当克里斯切换重力时，它开始将所有立方体拉到盒子的右侧。

![](https://cdn.luogu.org/upload/vjudge_pic/CF405A/f9e5056d82c9422148cc319b310a47b3094fcd5f.png)

该图显示了方块中的立方体的初始和最终位置：改变了它们的位置的立方体用橙色突出显示。 给定盒子中的玩具立方体的初始位置，在重力开关之后找到$N$列中的每个立方体的数量！

## 样例 #1

### 输入

```
4
3 2 1 2
```

### 输出

```
1 2 2 3 
```

## 样例 #2

### 输入

```
3
2 3 8
```

### 输出

```
2 3 8 
```

# 题解

## 作者：土川崇贺 (赞：2)

	本题实际上只要将数据排序后输出即可。
    代码奉上：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    long long n;
    cin>>n;
    int a[n];
    for(int i=0;i<n;i++)
    {
    	cin>>a[i];
	}
	sort(a,a+n);
	for(int i=0;i<n;i++)
	{
		cout<<a[i]<<" ";
	}
	return 0;
}

```

---

## 作者：sxtm12138 (赞：1)

###  **我看到之前的dalao都想到了排序的方法，这里就不展开了。如果没想到排序怎么办呢？下面是我一开始的想法，虽然效率不高，但代码还算简短，所以拿出来与大家分享，如有错误望大家帮忙指正。**
 **_代码如下_ **

------------

```cpp
#include<bits/stdc++.h>
using namespace std;
int a,f[105]={0},b[105]={0},n;//初始化数组，F表示每行方块数，B表示每列方块数
int main()
{cin>>n;
 for(int i=1 ;i<=n;i++)//i表示列数 
   {cin>>a;//读入、计算合二为一
    for(int i=1;i<=a;i++)//第二次循环将每列方块向右对齐、叠加
      {b[n-f[i]]++;//行与列的转化（总列数N-当前方块高度=此方块所处的列数）
       f[i]++;//记录重力转向后每行最高方格位置，为下次叠加做准备
      }
   }
 for(int i=1;i<=n;i++) cout<<b[i]<<" ";//从左至右输出方块数
 return 0;//这个方法更容易想到，虽然比较复杂，不过AC这题足够了
}
```

---

## 作者：Gu_Ren (赞：1)

来篇pas题解壮我大p党

看题数据范围贼小，大概有两种做法，一种是直接模拟（麻烦），但其实就是小到大排序（想想就知道了），就和[这位大佬](https://www.luogu.org/blog/lcwwer/solution-cf405a)说的一样啦

排序方法贼多，最优解 桶排可，但我想了想普通桶排管理员大大怎么会让我过呢，于是我打了个调用自身的桶排，详细见代码（劝大家不要学习）

```cpp
type
  arr=array[0..100]of integer;
var
  b:arr;
  n,i:longint;

  procedure sort3(n,k:longint);
   var
     x:integer;
   begin
     if k>n then exit;
     read(x);
     b[x]:=b[x]+1;
     sort3(n,k+1);
   end;
begin
  read(n);
  sort3(n,1);
  for i:=1 to 100 do
  while b[i]>0 do begin write(i,' ');b[i]:=b[i]-1;end;
end.
```

---

## 作者：Pheasant_YQ (赞：0)

### CF水题

根本不需要看花里胡哨的题面,以及两张图.~~(反正我是这样)~~

看输入输出可以看出这仅仅是一个简单的sort快排

用即将AFO的脑子直接写出一行代码便可以AC

Code:
```
#include <bits/stdc++.h>
#define ll long long

using namespace std;

inline int read(){
    int x = 0,f = 1;
    char c = getchar();
    while(c < '0' || c > '9'){
        if(c == '-')
        f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9'){
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
} 

int n,a [100010];

int main () {
	n = read ();
	for (int i = 0; i < n; ++ i) {
		a [i] = read ();
	}
	sort (a,a + n);
	for (int i = 0; i < n; ++ i) {
		cout << a [i] << " " [i == n - 1];//反正卡空格的小办法
	}
	return 0; 
}
```


---

## 作者：狂犇 (赞：0)

~~这道题为什么大家都用了O（n^2）的冒泡排序呢~~

这道题我想为大家介绍复杂度最低又稳定的归并排序。

归并排序的核心思想就是**分治**

步骤：

1.当我们要排序这样一个数组的时候，归并排序法首先将这个数组分成一半。

2.然后我们要想办法把左边的数组给排序，右边的数组给排序，之后再将它们归并起来。当然当我们对左边的数组和右边的素组进行排序的时候，再分别将左边的数组和右边的数组分成一半，然后对每一个部分先排序，再归并。

3.……

4.分到一定细度的时候，每一个部分就只有一个元素了，那么我们此时不用排序，对他们进行一次简单的归并就好了。

5.归并到上一个层级之后继续归并，归并到更高的层级，直到完成为止。

这就是归并排序的基本步骤了，至于代码吗……有点丑。。。

```cpp
#include<iostream>
using namespace std;
void Merge(int *a,int p, int q, int r)
{
    int n1 = q - p + 1;       
    int n2 = r - q;           
    int i, j, k;
    int *L = new int[n1+1];
    int *R = new int[n2+1];
    for(i=0;i<n1;i++)
        L[i]=a[p+i];
    for(j=0;j<n2;j++)
        R[j]=a[q+j+1];
    L[n1]=11111111;
    R[n2]=11111111;
    for(i=0,j=0,k=p;k<=r;k++)
    {
        if(L[i]<=R[j])
            a[k]=L[i++];
        else
            a[k]=R[j++];
    }
 
    delete []L;
    delete []R;
}
 
void MergeSort(int *a, int l, int r)//这就是二分搜索了
{
    if(l<r)
    {
        int m = (l+r)/2;
        MergeSort(a,l,m);
        MergeSort(a,m+1,r);
        Merge(a,l,m,r);
    }
}
int main()
{
    int i,n;
    cin>>n;
    int a[n+1];
    for(i=0;i<n;i++)
        cin>>a[i];
    MergeSort(a,0,n-1);
    for(i=0;i<n;i++)
        cout<<a[i]<<' ';
    return 0;
}
```


---

## 作者：ACE_ZY (赞：0)

不多说 直接进入主题

题意大家都明白 简单说就是排序

排序有很多种 就看大家喜欢哪种了

附上pascal选排代码

```pascal
var
  n,i,j,t:longint;
  a:array[0..1000] of longint;
begin
  readln(n);//n个数
  for i:=1 to n do read(a[i]);//分别读入数字
  for i:=1 to n-1 do
    for j:=i+1 to n do
    if a[i]>a[j] then begin t:=a[i];a[i]:=a[j];a[j]:=t;end;//选择排序
  for i:=1 to n do write(a[i],' ');//输出
end.
```

pascal桶排代码
```pascal
var
  n,i,j,t,x:longint;
  a:array[0..1000] of longint;
begin
  readln(n);
  for i:=1 to n do begin read(x);a[x]:=a[x]+1;end;//读入数字 累计个数在a数组里 就是桶排了
  for i:=1 to 101 do//for i:=1 to 这个数不要比数据小就行
  begin
    for j:=1 to a[i] do write(i,' ');//有多少个输多少个
  end;
end.
```

pascal快排代码
```pascal
var
  i,r,l,n:longint;
  a:array[1..1000] of longint;
procedure kp(l,r:longint);
var
  t,tl,tr,m:int64;
begin
  tl:=l;
  tr:=r;
  m:=a[(l+r) div 2];
  while tl<tr do
  begin
    while a[tl]<m do tl:=tl+1;
    while a[tr]>m do tr:=tr-1;
    if tl<=tr then
    begin
      t:=a[tl];a[tl]:=a[tr];a[tr]:=t;
      tl:=tl+1;
      tr:=tr-1;
    end;
  end;
  if l<tl then kp(l,tr);
  if tr<r then kp(tl,r);
end;
begin
  readln(n);//n个数
  for i:=1 to n do read(a[i]);//分别读入数字
  l:=1;
  r:=n;
  kp(l,r);//快排
  for i:=1 to n do write(a[i],' ');//输出
end.
```
pascal冒泡排序代码
```pascal
var
  a:array[1..1000] of longint;
  i,j,temp,n:integer;
begin
  readln(n);//n个数
  for i:=1 to n do read(a[i]);//读入
  for i:=1 to n do//冒泡排序
    for j:=1 to n-i do
      if a[j]>a[j+1] then//和后一个比
      begin
        temp:=a[j];
        a[j]:=a[j+1];
        a[j+1]:=temp;
      end;
  for i:=1 to n do write(a[i],' ');//输出
end.

```

差不多就这些排序了

因为不会插排 所以就不发了

望通过

---

## 作者：lcwwer (赞：0)

题中题目的意思是输入n个数，结果按从小到大输出这n个数，数据范围不大，可以用桶排。

贴代码

```cpp

#include<iostream>
#include<cstring>//头文件
using namespace std;
int main()
{
    int n;
    int a[1000],b[2000];//虽然题目的数据范围是100，但是数组开大比较保险
    memset(b,0,sizeof(b));//数组初始化   
    cin>>n;
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
        b[a[i]]++;
    }//对每个桶进行标记
    for(int i=0;i<=1500;i++)
    {
        if(b[i]!=0)
        {            for(int j=1;j<=b[i];j++)
            cout<<i<<" ";
        }
    }//按照顺序输出
    return 0;    
}
```


---

## 作者：PC_DOS (赞：0)

本题是一道模拟题，通过题面和样例可以看出，本题的目的是对所给的序列升序排序后输出。

C++的algorithm库中提供了快速排序函数sort()，通过该函数，我们可以轻松实现对序列进行排序的需求。

sort()函数常用的重载版本有两个，其中一个是sort(start,end)，该重载将按照升序排序的方法将从start所指向的位置到end-1所指向的位置中的内容升序排列，这要求所给序列必须是有序且可比较的，如果数据类型为您自己定义的类型则需要为其重载比较运算符。另一个重载则是sort(start,end,sort_method)，第三个参数可以设定为自行编写的或者库中提供的比较函数，使得sort()的方法更为多样。

代码:

```
#include <iostream>
#include <algorithm>
using namespace std; //头文件和命名空间
int main(){
	ios::sync_with_stdio(false); //输入输出加速
	int n, i, arr[105]; //n-项目数；i-循环计数器；arr[]-容器
	cin >> n; //读入个数
	for (i = 0; i<n; ++i){ //读入内容
		cin >> arr[i];
	}
	sort(arr, arr + n); //排序
	for (i = 0; i<n; ++i) //输出
		cout << arr[i] << " ";
	return 0; //结束
}
```

---

