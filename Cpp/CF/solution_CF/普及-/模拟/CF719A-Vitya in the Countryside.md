# Vitya in the Countryside

## 题目描述

Every summer Vitya comes to visit his grandmother in the countryside. This summer, he got a huge wart. Every grandma knows that one should treat warts when the moon goes down. Thus, Vitya has to catch the moment when the moon is down.

Moon cycle lasts 30 days. The size of the visible part of the moon (in Vitya's units) for each day is $ 0 $ , $ 1 $ , $ 2 $ , $ 3 $ , $ 4 $ , $ 5 $ , $ 6 $ , $ 7 $ , $ 8 $ , $ 9 $ , $ 10 $ , $ 11 $ , $ 12 $ , $ 13 $ , $ 14 $ , $ 15 $ , $ 14 $ , $ 13 $ , $ 12 $ , $ 11 $ , $ 10 $ , $ 9 $ , $ 8 $ , $ 7 $ , $ 6 $ , $ 5 $ , $ 4 $ , $ 3 $ , $ 2 $ , $ 1 $ , and then cycle repeats, thus after the second $ 1 $ again goes $ 0 $ .

As there is no internet in the countryside, Vitya has been watching the moon for $ n $ consecutive days and for each of these days he wrote down the size of the visible part of the moon. Help him find out whether the moon will be up or down next day, or this cannot be determined by the data he has.

## 说明/提示

In the first sample, the size of the moon on the next day will be equal to $ 8 $ , thus the answer is "UP".

In the second sample, the size of the moon on the next day will be $ 11 $ , thus the answer is "DOWN".

In the third sample, there is no way to determine whether the size of the moon on the next day will be $ 7 $ or $ 9 $ , thus the answer is -1.

## 样例 #1

### 输入

```
5
3 4 5 6 7
```

### 输出

```
UP
```

## 样例 #2

### 输入

```
7
12 13 14 15 14 13 12
```

### 输出

```
DOWN
```

## 样例 #3

### 输入

```
1
8
```

### 输出

```
-1
```

# 题解

## 作者：ahawzlc (赞：5)

CF719A 【Vitya in the Countryside】，if好题，你值得拥有。

----

题目大意就是给出月亮盈亏，然后预测下面的情况。

来看一个图：

![4.4tj1.png](https://i.loli.net/2020/04/04/JDFl2k1GaTYMV3g.png)

（手工绘制，不要在意美观细节。）

很显然的两个点：

1. 当题目数据同 A、E 相同时，答案是```UP```。

2. 当题目数据同 C 相同时，答案是```DOWN```。

因为 A 段是单调上升的，B段是单调下降的。

那么当题目数据是 ABC 三段或者 CDE 三段呢？

很显然前者```UP```，后者```DOWN```。

因为无论前面怎么变，最后预测还是看最后一段上升或下降的曲线。

而判断一个曲线最后的方向，只需看两个数据，因为2个数据是最短的能够判断升降序的序列。

由此，我们得出一般性结论（敲黑板）：

**当前序列($\mathtt {len \ge 2}$)最后的升降序，由最后两个数据决定。**

但是！

如果序列像 AB 或者 CD 呢？

由于 B 点和 D 点分别是峰顶和峰底，下面的数据会*峰回路转*，所以先进行对最后一个数据的判断：

**如果这个数据是15，那么输出升序；**

**如果这个数据是0，那么输出降序。**

还有一种特殊情况，当 $len == 1$ 时，除上述为 15 和 0 的情况外，其他的数字都无法判断下面的是升序还是降序。理由就是**2个数据是最短的能够判断升降序的序列**。

分析结束，~~喜闻乐见~~上代码。

``` cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
	int va1,va2,n;
	cin>>n;
	for(int i=1;i<n;i++) cin>>va1;
	cin>>va2;
	if(va2==15) puts("DOWN");//特判1
	else if(va2==0) puts("UP");//特判2
	else if(n==1) puts("-1");//序列len==1，无法判断
	else if(va2>va1) puts("UP");//升序
	else puts("DOWN");//降序
	return 0;
}
```

---

## 作者：CobaltChloride (赞：1)

```
又是一个大水题!!!
判断最后一天,若是0则UP,是15则DOWN.
若n是1且a[1]不是0或15则-1.
否则比较a[n]与a[n-1]即可.
附上代码:
#include<bits/stdc++.h>
using namespace std;
int n,a【93】,i;
void write(int k){
	if(k==1) cout<<"UP";
	if(k==2) cout<<"DOWN";
	if(k==0) cout<<"-1";
}
int main(){
	cin>>n;
	for(i=1;i<=n;i++) cin>>a[i];
	if(!a[n]) write(1);
	else if(!(a[n]-15)) write(2);
	else if(n==1) write(0);
	else if(a[n]>a[n-1]) write(1);
	else write(2);
	return 0;
}
```

---

## 作者：蒟蒻lxy (赞：0)

$$\text{QAQer出品}$$


~~从没见过这么水的浅蓝题~~   
### 简要分析

每个月月亮的大小变化过程是：

>0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1

可以看出，在最后一天之后又会开始新的一月，所以大小又由$0$变成$1$。

那么我们考虑使用最后$2$个大小数字判断下一个数字是什么（按规律来就行），由此得出答案。~~（前面的数字不要面子的~~

那么当$n=1$时呢？    
$n=1$时由于只有一个数，无法判断是升序还是降序所以只能输出$-1$.

没什么毛病吧？   
然而考虑到$0$和$15$的特殊性，我们发现只要以$0$作为结尾必然得出$1$，只要以$15$为结尾必然得出$14$。

所以我们应在开头特判$0$和$15$。

分析完毕。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[105];
int main()
{
	cin >> n;
	for(int i=1;i<=n;i++)
		cin >> a[i];
	if(a[n]==0)//特判0的情况
		cout <<"UP\n";//由0变为1所以是UP
	else
		if(a[n]==15)//特判15的情况
			cout <<"DOWN\n";//由15变成14所以是DOWN
		else
			if(n==1)//除以上情况外n=1是答案恒为-1
				cout <<"-1\n";
			else
			{
				int next=a[n]+(a[n]-a[n-1]);//由结尾2个数推出接下来的大小
				if(next<a[n])//判断升序降序
					cout <<"DOWN\n";
				else
					cout <<"UP\n";
			}
	return 0;//好习惯（滑稽
}

```


---

## 作者：锦瑟，华年 (赞：0)

又是一道蓝蓝的水题。

题目：

我们知道每个月月亮从月牙到圆形切换，zpy把月亮的圆的程度定义了0~15级，那么一个月30天月亮圆的程度变化为：0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1。每个月都是这样周期的从0变到15再变到1。

zpy将最近n天月亮的变化记录下来，现在问你，下一天月亮是变大还是变小，变大输出“UP”，变小输出”DOWN”。

输入

第一行输入n

第二行输入n个整数(0到15之间的整数)，代表最近n天月亮变化情况

输出

下一天月亮变大输出“UP”，变小输出”DOWN”。 如果不能确定变大还是变小就输出”-1”。

在题目的三个样例中，只列举了三种最基础的情况，还有以下几种：

（注：与题解配合食用效果更佳）

第一种：n==0，在此之下有三种情况：

1：a[1]==0，由于是最小的，故应输出UP；

2：a[1]==15,最大的，输出DOWN；

3：除a[1]==0||a[1]==15外，输出-1。

第二种：a[n]>a[n-1]：

同样的，若a[n]==15，输出DOWN，否则输出UP。

第三种：a[n]<a[n-1]：

很显然，若a[n]==0，输出UP，否则，输出DOWN。

以上一个一个判断即可。

代码:

	#include<stdio.h>
	using namespace std;
	int a[105];
	int main(){
		int n,i;
		scanf("%d",&n);
		for(i=1;i<=n;i++)scanf("%d",&a[i]);
		if(n==1){//第一种情况
			if(a[1]==0){
				printf("UP");return 0;
			}
			if(a[1]==15){
				printf("DOWN");return 0;
			}
			printf("-1");return 0; 
		}
		if(a[n]>a[n-1]){//第二种情况
			if(a[n]==15){
				printf("DOWN");return 0;
			}
			else printf("UP");
		}
		else {//第三种情况
			if(a[n]==0)printf("UP");
			else printf("DOWN");
		}
		return 0;
	}
    
AC完成，over~。

---

## 作者：shenmadongdong (赞：0)

1、n=1时，若a=0，则为上升，若a=15则为下降，否则无法判断；

2、n<>1时，只需看后两数即可，当第一个数比第二个数大且不为1、0时即为下降，反之则为上升；

代码：
```
var n,i,a,b:longint;
begin
  read(n);
  if n=1 then begin read(a); if a=0 then writeln('UP') 
  else if a=15 then writeln('down') else writeln('-1'); end//当n=1时的判断
  else begin
    for i:=1 to n-2 do read(a);
    read(a,b);
    if ((a<b)and(a<>14))or((a>b)and(b=0)) then writeln('UP') else writeln('DOWN');//当n<>1时的判断
  end;
end.
```

---

