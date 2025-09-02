# Polycarp's Pockets

## 题目描述

题意   
输入$n$个数，输出其中最多有多少个数是相同的。

## 样例 #1

### 输入

```
6
1 2 4 3 3 2
```

### 输出

```
2
```

## 样例 #2

### 输入

```
1
100
```

### 输出

```
1
```

# 题解

## 作者：Rainbow_qwq (赞：6)

[友好的原题链接](https://www.luogu.org/problemnew/show/CF1003A)

各位大佬都是用桶排写的吗？

桶排虽然快（时间复杂度O(n)）但是数据范围如果大（比如a[i]<=10^18)就不行了，桶排一定爆内存。

这时，我们也可以用普通排序方法。

**思路：**
```cpp
如样例一，原数组：
1 2 4 3 3 2
排序数组：
1 2 2 3 3 4
此时再从头到尾过一遍，就可以记录每个数出现的个数。

时间复杂度：O(n log n)，比桶排差。
空间复杂度：O(n) ，在数据大时比桶排更好。
```
AC代码：
```cpp
#include<iostream>
#include<algorithm>
//sort() c++STL排序用到algorithm
using namespace std;
int n,a[105]={-1},cnt=1,ans=1;
//a[0]初始化为-1，使在后面比较时a[1]!=a[0]
int main()
{
	ios::sync_with_stdio(0);//cin优化
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+n+1);		//排序。
	for(int i=1;i<=n;i++)
	{
		if(a[i-1]==a[i])cnt++;//前后两数相等，那这个数的数量+1
		else cnt=1;			  //若不相等，就是一个新数，个数计为1
		ans=max(ans,cnt);	  //记录最大值
	}
	cout<<ans;
	return 0;
}
```
虽然这道题用桶排更好，但直接排序也是一种方法。

大家可以做一下[这道题](https://www.luogu.org/problemnew/show/P1097)

---

## 作者：meyi (赞：2)

已有题解都是读入后找出现次数的最大值吗...

这里提供一种边读入边找最大值的方法。

上代码:
```cpp
#include<cstdio>
int a,m[101],n,s;
main(){
	scanf("%d",&n);	//输入n
	while(n--){
		scanf("%d",&a);	//输入n个数
		s=(++m[a]>s?m[a]:s);	//找出现次数的最大值
	}
	printf("%d",s);	//输出
}
```


---

## 作者：Franka (赞：1)

### **题目**
给定一个数n，求这**n个数**中**同一个数**出现的**次数**的**最大值**。
### **思路**
#### 方法1：桶
因为题目中已经给出了$a_i≤100$，所以用桶不会炸。

先将每个数放进它对应的桶中，然后从$1$到$100$查找最大值就行了。
#### 方法2：排序
将这$n$个数排好序之后，用最大平台长度来解决这个问题。
### **代码**
#### 方法一
```pascal
var
 n,i,x,max:longint;//定义别的东西
 a:array[1..100] of longint;//定义a数组
begin
 readln(n);//读入n
 for i:=1 to n do//循环
  begin
   read(x);//读入x（也就是a[i]）
   inc(a[x]);//累加x对应的桶
  end;
 for i:=1 to 100 do if a[i]>max then max:=a[i];//找最大值
 writeln(max);//输出
end.
```
#### 方法2
```pascal
var
 a:array[0..100] of longint;//定义a数组
 n,i,j,s,max:longint;//定义别的东西
procedure jh(var x,y:longint);begin x:=x+y;y:=x-y;x:=x-y;end;//利用加减法交换
begin
 readln(n);//读入n
 for i:=1 to n do read(a[i]);//读入a数组
 for i:=1 to n-1 do for j:=i+1 to n do if a[i]>a[j] then jh(a[i],a[j]);//排序
 s:=1;//s初始值
 for i:=2 to n do//最大平台长度
  if a[i]=a[i-1] then inc(s)//如果相邻的两个数相等，s加1
   else//如果不相等
    begin
     if s>max then max:=s;//看看有没有超过最大值
     s:=1;//找到了新的平台，s重新变为1
    end;
 if s>max then max:=s;//因为最后一个连续的没有被找过，所以加一个单判
 writeln(max);//输出最大值
end.
```


---

## 作者：Kevin_Zhen (赞：0)

题目链接 [CF1003A](https://www.luogu.com.cn/problem/CF1003A)。  
做法是排序后统计出现次数，但用的是手写**归并排序**。  
归并排序板子 [CF784F](https://www.luogu.com.cn/problem/CF784F)。同时，归并排序可以用于[求逆序对](https://www.luogu.com.cn/problem/P1908)的实现。
## AC CODE
```cpp
#include <iostream>
#include <cstdio>
using namespace std;

int n, cnt, ans;
int a[110] = { -1 }, m[110];

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
	for (int i = 1; i <= n; ++i) {
		if (a[i] == a[i - 1]) ++cnt; else cnt = 1;
		ans = max(ans, cnt);
	}
	printf("%d", ans);
	return 0;
}
```
## 感谢观赏！

---

## 作者：向日葵小班 (赞：0)

**大家都用桶的吗？我用数组计数（~~数据水~~）**

## 太水不讲，放代码：
```cpp
#include<bits/stdc++.h>//万能头文件
int n,a,s[105],d=-100;//定义n，n个整数a，数组计数数组s，比较的d
using namespace std;
int main()
{
     cin>>n;//输入n
	 for(int i=1;i<=n;i++)
	 {
	 	cin>>a;//输入a
	 	s[a]++;//s的第a个位置++
	 }	
	 for(int i=1;i<=100;i++)//从1-100循环
	 {
	 	if(s[i]>d)d=s[i];//如果s的第i个位置大于当前最大数，d=s[i]
	 }
	 cout<<d;//输出d
    return 0;//完美结束！！！
}
```


---

## 作者：Higashikata_Jousuke (赞：0)

题还是比较水的，蒟蒻思路也算比较好懂的，就来水一发

##  大概思路

 ### _**用两个数组，一边输入，一遍记录输入的数的次数，然后再从用于记录的变量里找出输入次数最多的**_ 
 
## 代码

```
#include<bits/stdc++.h>
//万能头文件，不解释
using namespace std;
int n,a[103],t[103],maxx;
//数组a用于输入，t用于记录，maxx用于寻找最多的次数
int main()
{  
    cin>>n;
	for(int i=0;i<n;i++)
	{
		cin>>a[i];
		t[a[i]]++;
  		//一边读一遍把对应的数的输入次数存进t数组里，后面查找时要用
	}
	for(int i=0;i<=100;i++)
		if(t[i]>maxx)maxx=t[i];
  	//用for循环暴力搜索一遍（数据水），遇到次数多的就存进变量maxx里
	cout<<maxx;
  	//输出最多次数
    return 0;
  	//结束干啥啊，愣着呀！
}

```

就是这么简单

### 温馨提示 ： 请勿抄袭

---

## 作者：FP·荷兰猪 (赞：0)

题意：输入n个数，输出其中最多有多少个数是相同的。

这题n和a[i]都只有100，完全可以开数组打标记，每读入一个数就把相应的数组元素++，最后找个man。时间复杂度O(n)：

```cpp
#include <bits/stdc++.h>
using namespace std;

int my_max(int a,int b)//STL可能跑得比较慢，这里手写了一个max
{
	if (a>b)
	{
		return a;
	}
	else
	{
		return b;
	}
}

int main()
{
	ios::sync_with_stdio(false);
	int n;
    cin>>n;
	int x,i,a[101]={0},maxv;
	maxv=0;
    for (i=1;i<=n;i++)
    {
        
        cin>>x;
        a[x]++;
    }
    for (i=0;i<=100;i++)
    {
        maxv=my_max(maxv,a[i]);//每次比较较大的那个，这样最后留下的会是最大的
    }
    cout<<maxv<<endl;
    return 0;
}
```

---

## 作者：pigstd (赞：0)

思路：循环n次，用桶排的方法记录，最后找到被记录次数最多的即可

~~写的人少我就来水一发吧~~

c++代码：

```
#include<bits/stdc++.h>
using namespace std;

int maxn,n;
int a[105];//用于记录

int main()
{
	cin>>n;
	for (int i=1;i<=n;i++)
	{
		int p;
		cin>>p;
		a[p]++;//次数++
	}
	for (int i=0;i<=100;i++)//寻找最大值 
		maxn=max(maxn,a[i]);
	cout<<maxn;
	return 0;
}
```

---

## 作者：wuyutong111 (赞：0)

```pascal
这题呢……唉，该怎么说呢，简单来说就是打擂台，奀……算了，一边看我的程序一遍理解吧（本人表达能力并不好.
var
 max,min,x,i,m,n:longint;
 a:array[0..10001] of longint;
begin
 max:=-maxlongint;//尽可能定小点
 min:=maxlongint;//尽可能定大点
 readln(n);
 for i:=1 to n do
  begin
   read(x);
   inc(a[x]);//桶的思想
   if x>max then max:=x;//求输入进来的最大值，以方便下面循环使用
   if x<min then min:=x;//求输入进来的最小值，以方便下面循环使用
  end;
 m:=a[min];
 for i:=min+1 to max do
  if a[i]>m then m:=a[i];//打擂台开始
 writeln(m);输出最大的出现次数
end.
```


---

## 作者：不到前10不改名 (赞：0)

//一开始还想着什么去重或记录状态，看到数据第一次也是用暴力过的，准备发题解之前才发现这只是个桶排233...
```
#include<stdio.h>
int max(int x,int y)
{
    if(x>y)
    return x;
    return y;
}
int n,x,i,srx[101],sry;
int main()
{
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    {scanf("%d",&x);
    srx[x]++;}//桶记录
    for(i=1;i<=100;i++)//什么水数据，n<=100，cf和at果然是最水的题库
    sry=max(sry,srx[i]);//求众数
    printf("%d\n",sry);//回车，打at时习惯了~
    return 0;
 } 
```

---

## 作者：准点的星辰 (赞：0)

相同的硬币不能在一个口袋里，一想挺复杂，每次扫一遍已经分的口袋，如果没有就放进去，都有的话再新建一个口袋……好了，不说了，上正解，相同的硬币不能在一个口袋里，所以我们找出现次数最多的数，分成这些组，比这个次数小的数肯定会找到口袋。再一看数据范围，1到100，哇，桶排，于是代码出来了……
```
#include<iostream>
#include<cstdio>
using namespace std;
int n,x;
int t[101];
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&x);
		t[x]++;
	}
	int maxx=0;
	for (int i=1;i<=100;i++)
	maxx=max(maxx,t[i]);
	printf("%d",maxx);
	return 0;
 } 
```

---

