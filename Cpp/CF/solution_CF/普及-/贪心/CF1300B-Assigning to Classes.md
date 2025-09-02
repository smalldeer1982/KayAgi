# Assigning to Classes

## 题目描述

Reminder: the [median](https://en.wikipedia.org/wiki/Median) of the array $ [a_1, a_2, \dots, a_{2k+1}] $ of odd number of elements is defined as follows: let $ [b_1, b_2, \dots, b_{2k+1}] $ be the elements of the array in the sorted order. Then median of this array is equal to $ b_{k+1} $ .

There are $ 2n $ students, the $ i $ -th student has skill level $ a_i $ . It's not guaranteed that all skill levels are distinct.

Let's define skill level of a class as the median of skill levels of students of the class.

As a principal of the school, you would like to assign each student to one of the $ 2 $ classes such that each class has odd number of students (not divisible by $ 2 $ ). The number of students in the classes may be equal or different, by your choice. Every student has to be assigned to exactly one class. Among such partitions, you want to choose one in which the absolute difference between skill levels of the classes is minimized.

What is the minimum possible absolute difference you can achieve?

## 说明/提示

In the first test, there is only one way to partition students — one in each class. The absolute difference of the skill levels will be $ |1 - 1| = 0 $ .

In the second test, one of the possible partitions is to make the first class of students with skill levels $ [6, 4, 2] $ , so that the skill level of the first class will be $ 4 $ , and second with $ [5, 1, 3] $ , so that the skill level of the second class will be $ 3 $ . Absolute difference will be $ |4 - 3| = 1 $ .

Note that you can't assign like $ [2, 3] $ , $ [6, 5, 4, 1] $ or $ [] $ , $ [6, 5, 4, 1, 2, 3] $ because classes have even number of students.

 $ [2] $ , $ [1, 3, 4] $ is also not possible because students with skills $ 5 $ and $ 6 $ aren't assigned to a class.

In the third test you can assign the students in the following way: $ [3, 4, 13, 13, 20], [2, 5, 8, 16, 17] $ or $ [3, 8, 17], [2, 4, 5, 13, 13, 16, 20] $ . Both divisions give minimal possible absolute difference.

## 样例 #1

### 输入

```
3
1
1 1
3
6 5 4 1 2 3
5
13 4 20 13 2 5 8 3 17 16```

### 输出

```
0
1
5```

# 题解

## 作者：gcwixsxr (赞：2)

题目大意：将一个长度为 $2n$ 的序列 $\{a_i\}$ 分为两组，使得每组中的数量为奇数，要求最小化两组的中位数的差。

根据多次验算，答案是该序列排序后第 $n+1$ 位与第 $n$ 位之差。那么这里就给出一个证明。

我们约定，序列 $\{a_i\}$ 排序后的序列为 $\{b_i\}$。

那么原来的命题就等价于以下命题：对于任意的分组方式，中位数较小组的中位数一定不大于 $b_{n}$，中位数较大组的中位数一定不小于 $b_{n+1}$。

那么我们使用反证法，假设存在一种分组方式使得中位数较小组的中位数大于 $b_{n}$。那么中位数较小组的的中位数就不大于 $b_{n+1}$，中位数较大组的中位数就不大于 $b_{n+2}$。由于比 $b_{n+1}$ 更小的数有 $n$ 个，比 $b_{n+2}$ 大的数有 $n-2$ 个，比中位数小的数和比中位数大的数个数不相等。那么 $b_{n+1},b_{n+2}$ 显然不能同时成为两个组的中位数。

那么矛盾，原命题成立。

则最小值一定即为 $b_{n+1}-b_n$。

这里给出一种构造方式：

 第一组选择 ：
 $$\{b_1,b_2,\dots,b_{\left\lfloor\frac {n-1}2\right\rfloor}\}\cup\{b_{\left\lceil\frac {3n+3}2\right\rceil},\dots,b_{2n-1},b_{2n}\} \cup\{b_n\}$$
 第二组选择剩余部分即可。
 
 ```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>

using namespace std;
const int N=2e5+10;

int T,n,a[N];
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=2*n;i++)scanf("%d",a+i);
		sort(a+1,a+2*n+1);
		printf("%d\n",a[n+1]-a[n]);
	}
}

```


---

## 作者：lemonfor (赞：2)

题目要求两个集合中位数的差值最小，即将数组排序后，中间两个数的差就是答案了 (逃
```cpp
#include<cstdio>
#include<algorithm>
#define _ 0
#define INF 0x3f3f3f
#define int long long
#define re register
#define drep(i ,l ,r) for(re int i = (l) ; i >= (r) ; -- i)
#define rep(i ,l ,r) for(re int i = l ; i <= r ; ++ i)
using namespace std;
int t ,n ,num[300000];
int read() {
    char cc = getchar() ; int cn = 0 ,flus = 1;
    while(cc < '0' || cc > '9') {if(cc == '-') flus = - flus ; cc = getchar();}
    while(cc >= '0' && cc <= '9') cn = cn * 10 + cc - '0' ,cc = getchar();
    return flus * cn;
}
signed main() {
    t = read();
    while(t --) {
        n = read();
        rep(i ,1 ,n * 2) num[i] = read();
        sort(num + 1 ,num + n * 2 + 1);
        printf("%lld\n" ,num[n + 1] - num[n]);
    }
}
```

---

## 作者：JS_TZ_ZHR (赞：1)

人生第一场CF，值得纪念，写个题解吧。

本题的意思是给你一个长度为$2n$的序列，把这两个序列分为两个长度为奇数的序列，使得这两个序列的中位数的差的绝对值最小。

刚开始看到这题时并没有什么思路，于是把样例里的序列排了个序，发现了这种神秘的现象：
  
$1$  $1$  $(1-1=0)$

$1$  $2$  $3$  $4$  $5$  $6$  $(4-3=1)$

$2$  $3$  $4$  $5$  $8$  $13$  $13$  $16$  $17$  $20$  $(13-5=8)$

从中我们可以看出答案即为排序后的第$i+1$个减去第$i$个的差。

于是我们能得到如下代码：

```cpp
#include<bits/stdc++.h>//偷懒... 
using namespace std;
int T,n,a[1000005];
int main() {
	scanf("%d",&T);//输入 
	while(T--) {
		scanf("%d",&n);//输入 
		for(int i=1; i<=n*2; i++)scanf("%d",a+i);//输入 
		sort(a+1,a+n*2+1);//排序 
		printf("%d\n",a[n+1]-a[n]);//输出 
	}
}
```

但这样是过不掉的，因为给出的是长度为**2n**的序列，所以要开两倍空间。

正确代码：

```cpp
#include<bits/stdc++.h>//偷懒... 
using namespace std;
int T,n;
int a[2000005];//别忘了空间开两倍 
int main() {
	scanf("%d",&T);//输入 
	while(T--) {
		scanf("%d",&n);//输入 
		for(int i=1; i<=n*2; i++)scanf("%d",a+i);//输入 
		sort(a+1,a+n*2+1);//排序 
		printf("%d\n",a[n+1]-a[n]);//输出 
	}
}
```


---

## 作者：ShineEternal (赞：1)

## solution：

- 给定一个有 $2\times n$ 个数的数列。
- 让你把它分成两组，使得每一组的数量均为奇数。

- 请你求出两组中位数之差的绝对值的最小值。

首先令 $n=n\times 2$。

发现在数列中差的最小且能被作为中位数的数字是排序后位于 $\dfrac{n}{2}$ 和 $\dfrac{n}{2}+1$位置的数字。

所以就排个序把这两个数做差就行。

然后发现其实数组的范围是 $2\times 10^5$ ，所以数组别开小 RE 了。

## code：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int a[200005];
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		int n;
		scanf("%d",&n);
		int cnt=0,sum=0;
		n=n*2;
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
		}
		sort(a+1,a+n+1);
		printf("%d\n",a[n/2+1]-a[n/2]);
	}
	return 0;
} 
```

---

## 作者：ACE_ZY (赞：1)

Pascal题解

题意:有t组数据(没词汇了)，每组数据会输入2 * n个数，将其排序，输出中位数之差

```pascal
var
  i,j,t,n:longint;
  a:array[0..1000000] of longint;
procedure qsort(l,r:longint);//快排
var
  i,j,m,t:longint;
begin
  i:=l;j:=r;m:=a[(l+r) div 2];
  while i<j do
  begin
    while a[i]<m do inc(i);
    while a[j]>m do dec(j);
    if i<=j then
    begin
      t:=a[i];a[i]:=a[j];a[j]:=t;
      inc(i);dec(j);
    end;
  end;
  if l<j then qsort(l,j);
  if i<r then qsort(i,r);
end;
begin
  readln(t);
  for i:=1 to t do
  begin
    readln(n);
    for j:=1 to 2*n do read(a[j]);
    readln;
    qsort(1,2*n);
    writeln(a[n+1]-a[n]);//输出中位数之差
  end;
end.
```


---

## 作者：_cmh (赞：0)

$\text{Update on 2021.9.30}$：重新进行排版，优化了 $\LaTeX$。

## $\texttt{Description}$

将一个长度为 $2n$ 的排列分为两组，每组个数为奇数，求出其中位数之差的绝对值的最小值。

## $\texttt{Solution}$

读入数据后，我们进行排序。

因为求中位数的差值最小，则对于此序列，$a_{n+1}-a_{n}$ 即为最小值。

通过找规律可以得出，这个值就是题目所求，输出即可。

## $\texttt{Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200010];
int main(){
	int T;
	cin>>T;
	while(T--){
		int n;
		cin>>n;
		for(int i=1;i<=n*2;i++)
			cin>>a[i];
		sort(a+1,a+2*n+1);
		cout<<a[n+1]-a[n]<<endl;
	}
	return 0;
}
```

感谢观看。

---

## 作者：HarryCecil (赞：0)

一看题目，wow，挺水的题。

题目意思：

- 给定一个有 $2\times n$ 个数的数列。

- 让你把它分成两组，使得每一组的数量均为奇数。

- 请你求出两组中位数之差的绝对值的最小值。

那么这题很简单，就是读入后排个序，输出第$n+1$项减第$n$项的值。

附上代码：

```cpp
#include<iostream>//头文件 
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<string>
#include<cstdlib>
using namespace std;
int n,x,a[2000001];//定义 
int main(){
	cin>>n;//读入 
	for(int i=1;i<=n;i++){//循环 
		cin>>x;//读入数量 
		for(int j=1;j<=x*2;j++) cin>>a[j];//记得，要x*2 
		sort(a+1,a+2*x+1);//STL自带函数，排个序 
		cout<<a[x+1]-a[x]<<endl;//输出 
	}
 	return 0;//完结撒花ヽ(°▽°)ノ
}
```

给个赞呗！

蒟蒻的第一篇题解，管理员大大求过~

---

