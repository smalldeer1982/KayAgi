# Puzzles

## 题目描述

The end of the school year is near and Ms. Manana, the teacher, will soon have to say goodbye to a yet another class. She decided to prepare a goodbye present for her $ n $ students and give each of them a jigsaw puzzle (which, as wikipedia states, is a tiling puzzle that requires the assembly of numerous small, often oddly shaped, interlocking and tessellating pieces).

The shop assistant told the teacher that there are $ m $ puzzles in the shop, but they might differ in difficulty and size. Specifically, the first jigsaw puzzle consists of $ f_{1} $ pieces, the second one consists of $ f_{2} $ pieces and so on.

Ms. Manana doesn't want to upset the children, so she decided that the difference between the numbers of pieces in her presents must be as small as possible. Let $ A $ be the number of pieces in the largest puzzle that the teacher buys and $ B $ be the number of pieces in the smallest such puzzle. She wants to choose such $ n $ puzzles that $ A-B $ is minimum possible. Help the teacher and find the least possible value of $ A-B $ .

## 说明/提示

Sample 1. The class has 4 students. The shop sells 6 puzzles. If Ms. Manana buys the first four puzzles consisting of 10, 12, 10 and 7 pieces correspondingly, then the difference between the sizes of the largest and the smallest puzzle will be equal to 5. It is impossible to obtain a smaller difference. Note that the teacher can also buy puzzles 1, 3, 4 and 5 to obtain the difference 5.

## 样例 #1

### 输入

```
4 6
10 12 10 7 5 22
```

### 输出

```
5
```

# 题解

## 作者：皮卡丘最萌 (赞：2)

这道题目还是比较简单的。

因为题目只要求最大披萨和最小披萨的差最小，没有要求其他东西，所以我们考虑排序。

例如10,12,10,7,5,22排序后得到5,7,10,10,12,22，此时我们只需要O(n)的枚举头，再计算出尾，最后得出差值即可。

i=1时差值为5,i=2时差值为5，i=3时差值为12，所以答案就是5。

这里的枚举次数是n-m+1次，并且当头为i时，结尾为i+m-1。

另外，由于此题n,m比较小，所以我们可以直接用选择排序做，总的时间复杂度为O(n^2)。

代码：
```pascal
uses math;
var n,m,i,j,s,t:longint; a:array[0..10001] of longint;
begin
readln(m,n); 
s:=maxlongint;                 //把最小值设为最大
for i:=1 to n do read(a[i]);   //读入数据
for i:=1 to n do
  for j:=i+1 to n do
    if a[i]>a[j] then
      begin t:=a[i];a[i]:=a[j];a[j]:=t; end;    //从小到大排序
for i:=1 to n-m+1 do             //枚举头指针
  s:=min(s,a[i+m-1]-a[i]);          //计算比较最小值
writeln(s);
end.
```


---

## 作者：做梦想Peach (赞：1)

这题还是竟然是黄题？

#### 窝百思不得其解，觉得最多橙题罢了。

 ~~这题虽然比较水，但是还是有一些细节要注意的。~~

#### 1. 它既然要求max-min最小，那么就先对原序列进行排序。

#### 2. 注意数组的下标，代码中会有体现。

数据范围：$2≤n≤m≤50$，很小的范围，所以用任意一种排序方法都可以。

下面 ，我们来康康代码是怎么写滴。

请不要埋怨我奇怪的马蜂![/kk](https://cdn.luogu.com.cn/upload/image_hosting/y609uyc8.png)。

```cpp
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>//一堆没啥用的头文件。
using namespace std;
int a[60],n,m,i,ans=0x7fffffff;//它既然是求最小的，所以ans初值定义一个很大的值
int min (int a,int b) {
	return a < b ? a : b;//求最小值。
}
int main () {
	scanf ("%d%d",&n,&m);
	for (i=0;i<m;i++)
		scanf("%d",&a[i]);//注意，i是从0开始的。下面注意。
	sort (a,a+m);//利用系统函数进行排序。
	for(i=0;i<=m-n;i++) //这里写成i<m-n也可以过，不知道为啥。
		ans=min (a[i+n-1]-a[i],ans);//求最小的解。
    printf ("%d\n",ans);
    return 0;
}
```
再见咯，![/bb](https://cdn.luogu.com.cn/upload/image_hosting/eelk6mg4.png)。

---

## 作者：锦瑟，华年 (赞：1)

# 本题思路：排序

好了，我们来具体说说这题的思路。老师想要取 $n$ 个数（披萨），要求其中最大的数与最小数的差最小，大家开动脑筋想一想，并不难发现：在 $m$ 个数从小到大排序过后的连续的 $n$ 个数中的最大的数与最小数的差最小。也就是说，有序序列的连续的一串数的最大的数与最小数的差最小。这样的话，我们只需要 sort 排序一遍,在从头到位遍历一串数，找出这些数串的最小的最大的数与最小数的差，记在 minn 中，最后输出即可。

废话不多说，看代码：

	#include<stdio.h>
	#include<algorithm>
	using namespace std;
	int a[55];
	int main(){
		int n,m,i;
		scanf("%d%d",&n,&m);
		for(i=1;i<=m;i++){//输入
			scanf("%d",&a[i]);
		}
		sort(a+1,a+1+m);//sort排序，需要头文件algorithm加持
		int minn=1234567890;//记录最小的最大的数与最小数的差的变量
		for(i=1;i<=m-n+1;i++){
	    	if(minn>a[i+n-1]-a[i])minn=a[i+n-1]-a[i];//计算，其功效相当于min
		}
    	printf("%d",minn);//输出
    	return 0;
	}
    
OK，题解结束，谢谢观看，byebye~~，(^_^)。

---

## 作者：Nortrom (赞：1)

# 枚举就行了
###### 其实这题十分简单，枚举在没m<=50时怎样都不会超时，所以，我选了最直接，精简的方法。


------------
思路：

1.先排一遍序，从小到大排（其实也可以从大到小，用自定义函数）

2.枚举1到m-n+1的起点，则终点为n到m，之所以起点用m-n+1,因为从终点x倒退n个，但实际位置在回退位置的前一位，所以+1。得原式=m-n+1

3.依次比较输出

```cpp
#include<iostream>
#include<cstdio>//习惯
#include<algorithm>//sort头文件
using namespace std;
int n,m,a[110],maxn=0x7fffffff;//其实到51就够了
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
		scanf("%d",&a[i]);
	sort(a+1,a+m+1);//排序
	for(int i=1;i<=m-n+1;i++)
	{
		int s=a[i+n-1]-a[i];//将最大值减去最小值，m-n+1详情看前文
		maxn=min(maxn,s); //比较
	}
	printf("%d\n",maxn);//输出
	return 0;
}
```
提供第二种思路，深搜，但要注意时间复杂度和层数，避免超时。

拒绝通过抄题解方式刷题，珍惜每一次测评机会。

---

## 作者：codemap (赞：0)

~~又是一道水题~~

将披萨大小从小到大排序,然后枚举一个i从1到m-n+1

mmin=min(a[i+n-1]-a[i])

然后就可以了

上代码
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int main()
{
	int n,m,i,a[51],mmin=1e9;
	cin>>n>>m;
	for(i=1;i<=m;i++)
		cin>>a[i];
	sort(a+1,a+m+1);//排序
	for(i=1;i<=m-n+1;i++)(m-n+1)+(n-1)==m
		mmin=min(mmin,a[i+n-1]-a[i]);//计算
	cout<<mmin;//输出
	return 0;//完美结束
}
```
# 请勿抄袭

---

