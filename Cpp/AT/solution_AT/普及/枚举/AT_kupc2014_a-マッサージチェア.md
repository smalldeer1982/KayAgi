# マッサージチェア

## 题目描述

[problemUrl]: https://atcoder.jp/contests/kupc2014/tasks/kupc2014_a



# 题解

## 作者：幻之陨梦 (赞：4)

[$\color{blue}\text{安利一下自己的博客}$](https://www.luogu.org/blog/ZhanLang/)

**解题思路：** 先把输入进来的学生的位置和作为的位置各自排序，然后再循环加上 $|a_i-b_i|$，也就是学生与座位间的距离。

**AC Code:**
```cpp
#include<bits/stdc++.h>//万能头
using namespace std;//标准库
int a[5],b[5],ans;//定义学生的数组，椅子的数组和最终答案
int main(void)
{
	for(int i=1;i<4;i++) scanf("%d",&a[i]);
	//输入学生位置
	for(int i=1;i<4;i++) scanf("%d",&b[i]);
	//输入座椅位置
	sort(a+1,a+4);//排序学生位置
	sort(b+1,b+4);//排序座椅位置
	for(int i=1;i<4;i++) ans+=abs(a[i]-b[i]);
	//循环学生与座椅，求学生与座位间的距离之差的绝对值
	printf("%d\n",ans);//输出最终答案
}
```

---

## 作者：梦里调音 (赞：2)

温馨提示：

您可能做了一道假的黄题。

思路很简单：

	a数组和b数组都从小到大排序。

原因：

	要使总路途最短，应该使每个同学对号入座。
    
    举个例子：1、4是座位，2、3是同学，则两名同学走的路尽量不重叠。
    
    n名同学同理。
    
    
    
```
#include <bits/stdc++.h>
using namespace std;
int ans=0;
int main(){
	int i,j,k;
	int a[4],b[4];
	for(i=1;i<=3;i++)cin>>a[i];
	for(i=1;i<=3;i++)cin>>b[i];
	sort(a+1,a+4);
	sort(b+1,b+4);
	for(i=1;i<=3;i++)ans+=abs(a[i]-b[i]);
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：CZQ_King (赞：1)

题意：
```
给出6个整数，前三个代表学生，后三个代表座椅。他们在一条直线上。每一个学生都要坐到一把椅子上，请问当三个学生都就位时，他们走过的最短总距离是多少？
```
~~顺便说一下题目好像有错，不是$66$个整数~~

------------
思路：

将学生和座位都排一下序，因为要尽量挑近的坐，所以对应相减即可。

（即学生$a$与座位$x$坐，且$a$是三个学生中最小的，座位$x$也是三个座位中坐标最小的；

学生$b$与座位$y$坐，且$b$是三个学生中第二小的，座位$y$也是三个座位中坐标第二小的，以此类推）

注意：**记得要加绝对值！** 否则会出现相减得到负数的情况！

~~因为不会用py的数组和``sort``所以用的冒泡~~

------------
代码：
```
a,b,c,x,y,z=map(int,input().split()) #输入坐标
# a,b,c为学生  x,y,z为座位
t=0; # 临时变量temp

if a>b:
    t=b
    b=a
    a=t #模拟swap(a,b)过程
    
if a>c:
    t=c
    c=a
    a=t #同上
    
if b>c:
    t=c
    c=b
    b=t #同上
# 将a,b,c进行升序排序

if x>y:
    t=y
    y=x
    x=t #同上
    
if x>z:
    t=z
    z=x
    x=t #同上
    
if y>z:
    t=z
    z=y
    y=t #同上
# 将x,y,z进行升序排序
print (abs(a-x)+abs(b-y)+abs(c-z))# 输出最小的距离总和
```

---

## 作者：_lyc233 (赞：1)

## AT953 【マッサージチェア】 详解

------------
思路：

由于要求最短，所以由直线上的第一把椅子（从左往右观察）交给第一个人最好，第二把椅子交给第二个人......

如此如此，对应好之后，把第一个人到第一把椅子的距离求出来，再加上第二个人到第二把椅子的距离，再加上......

又是如如此此，**换行**输出总和就好了。

------------
所以，需要两个1~3的数组储存，**分别**排序后，已经做到一一对应，就按上面思路再做就行了。

------------
```pascal
var
  a,b:array[1..3] of longint;
  i,j,s:longint;
begin
  for i:=1 to 3 do read(a[i]);  //输入学生坐标
  for i:=1 to 2 do
   for j:=i+1 to 3 do
    if a[i]>a[j] then begin a[0]:=a[i];a[i]:=a[j];a[j]:=a[0]; end;  //对学生坐标进行从左到右排序（即从小到大），选排
  for i:=1 to 3 do read(b[i]);  //输入座椅坐标
  for i:=1 to 2 do
   for j:=i+1 to 3 do
    if b[i]>b[j] then begin b[0]:=b[i];b[i]:=b[j];b[j]:=b[0]; end;  //对座椅坐标进行从左到右排序
  for i:=1 to 3 do s:=s+abs(a[i]-b[i]);
  //abs即绝对值的函数，负数绝对值是0-这个数，整数为其本身，整数的绝对值都是正整数，因为要把s累加，所以必须是正整数，那么就需要用到abs函数。
  //也同等于if a[i]>b[i] then s:=s+a[i]-b[i] else s:=s+b[i]-a[i];
  writeln(s);  //输出换行
end.
{***Pascal***防伪标识***}
```

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[4],b[4];
int main()
 {
   for(int i=1;i<=3;i++) cin>>a[i]; //输入学生坐标
   for(int i=1;i<=3;i++) cin>>b[i]; //输入座椅坐标
   sort(a+1,a+4);
   sort(b+1,b+4);  //c++ sort大法好啊！
   int s=0;
   for(int i=1;i<=3;i++) s+=abs(a[i]-b[i]);  //emm，同上代码（复制下来就不简洁了qwq）
   cout<<s<<endl;
   return 0;
 }
```


---

## 作者：konglk (赞：0)

终于又来写题解了......注意一下，不是66个数，而是6个数！！！~~@chen_zhe @memset0改一下题~~不过应该没多少人入坑吧。

最左边的人坐最左边的椅子，中间的坐中间的，右边的坐右边的，这一定是最近的了（不然右边的走到中间，中间的走到右边之类的？）所以，只要把人的位置排序，把座位也排序即可。

由于数据量小，作者直接swap
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int a,b,c,k,l,m;
	cin>>a>>b>>c;
	if(a>b)swap(a,b);
	if(a>c)swap(a,c);
	if(b>c)swap(b,c);//依次swap，相当于排序
	k=a,l=b,m=c;//这样下面就可以复制上面的了
	cin>>a>>b>>c;
	if(a>b)swap(a,b);
	if(a>c)swap(a,c);
	if(b>c)swap(b,c);
	cout<<abs(k-a)+abs(l-b)+abs(m-c)<<endl;//一定要加绝对值！不然距离-1？
	return 0;
}
```


---

## 作者：绝艺 (赞：0)

思路楼下大佬都说得很清楚了

这里不再解释（~~其实是偷懒~~）

就只有我一个用冒泡的吗？！

# AC Code

```cpp
#include <iostream>
#include <cmath>
using namespace std;
int main(){
	int a[5],b[5],temp,ans=0;//数组开大点没关系
	for(int i=1;i<=3;i++) cin>>a[i];
	for(int i=1;i<=3;i++) cin>>b[i];
	for(int i=1;i<3;i++){
		for(int j=i+1;j<=3;j++){
			if(a[i]>a[j]){//这里的交换要小心
				temp=a[i];
				a[i]=a[j];
				a[j]=temp;
			}
		}
	}
	for(int i=1;i<3;i++){//复制粘贴大法好
		for(int j=i+1;j<=3;j++){
			if(b[i]>b[j]){
				temp=b[i];
				b[i]=b[j];
				b[j]=temp;
			}
		}
	}
	for(int i=1;i<=3;i++) ans+=abs(a[i]-b[i]);
	cout<<ans<<endl;
	return 0;
} 
```


---

## 作者：wushuang0828 (赞：0)

思路：先给输入进来的数排序，前三个数从小到大排序，后三个数从小到大排序，因为这样差比较小，总距离也会比较小。

下面就是代码：
```pascal
var
 i,j,t,s:longint;
 a,b:array[0..4] of longint;
begin
 readln(a[1],a[2],a[3],b[1],b[2],b[3]);//用两个数组保存，更方便
 for i:=1 to 2 do
  for j:=i+1 to 3 do//冒泡排序
   if a[i]>a[j] then//从小到大排
    begin
     t:=a[i];//交换
     a[i]:=a[j];//交换
     a[j]:=t;//交换
    end;
 for i:=1 to 2 do
  for j:=i+1 to 3 do//冒泡排序
   if b[i]>b[j] then//从小到大排
    begin
     t:=b[i];//交换
     b[i]:=b[j];//交换
     b[j]:=t;//交换
    end;
 if a[1]>b[1] then s:=s+(a[1]-b[1])
              else s:=s+(b[1]-a[1]);//比较哪个数大，然后再大的数减小的数
 if a[2]>b[2] then s:=s+(a[2]-b[2])
              else s:=s+(b[2]-a[2]);//比较哪个数大，然后再大的数减小的数
 if a[3]>b[3] then s:=s+(a[3]-b[3])
              else s:=s+(b[3]-a[3]);//比较哪个数大，然后再大的数减小的数
 writeln(s);//输出最短总距离
end.
```

---

## 作者：准点的星辰 (赞：0)

这题暴力做法，直接暴力枚举所有的情况，取最小输出答案。
```
#include<iostream>
#include<cstdio>
using namespace std;
int a[4],b[4];
bool mark[4];
inline int abs(int x)
{
	return x<0 ? -x:x; 
}
int main()
{
	for (int i=1;i<=3;i++)
	scanf("%d",&a[i]);
	for (int i=1;i<=3;i++)
	scanf("%d",&b[i]);
	int ans=min(abs(a[1]-b[1])+abs(a[2]-b[2])+abs(a[3]-b[3]),abs(a[1]-b[1])+abs(a[2]-b[3])+abs(a[3]-b[2]));
	ans=min(abs(a[1]-b[2])+abs(a[2]-b[1])+abs(a[3]-b[3]),ans);
	ans=min(abs(a[1]-b[2])+abs(a[2]-b[3])+abs(a[3]-b[1]),ans);
	ans=min(abs(a[1]-b[3])+abs(a[2]-b[1])+abs(a[3]-b[2]),ans);
	ans=min(abs(a[1]-b[3])+abs(a[2]-b[2])+abs(a[3]-b[1]),ans);
	printf("%d\n",ans);
	return 0;
 } 
```

看了一下枚举的b[i]情况，1 2 3,1 3 2，2 1 3，2 3 1,3 1 2,3 2 1，等等，这不就是3的全排列吗。

于是我们有了dfs枚举全排列的暴力做法。
```
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
const int n=3;
int a[5],b[5],c[5];
int ans=99999;
bool mark[5];
void dfs(int x)
{
	if (x==n+1)
	{
		int sum=0;
		for (int i=1;i<=n;i++)
		sum+=abs(a[i]-b[c[i]]);
		ans=min(ans,sum);
		return ;
	}
	for (int i=1;i<=n;i++)
	if (!mark[i])
	{
		c[x]=i;mark[i]=1;
		dfs(x+1);
		mark[i]=0;
	}
	return ;
}
int main()
{
	for (int i=1;i<=3;i++)
	scanf("%d",&a[i]);
	for (int i=1;i<=3;i++)
	scanf("%d",&b[i]);
	dfs(1);
	printf("%d\n",ans);
	return 0;
}
```
不会dfs搜全排列的请点[P1706 全排列问题](https://www.luogu.org/problemnew/show/P1706)。

---

## 作者：RioBlu (赞：0)

两个排序+绝对值函数解决所有问题
```
#include<bits/stdc++.h>
using namespace std;
long long a[10],b[10];
int main()
{
    cin>>a[0]>>a[1]>>a[2]>>b[0]>>b[1]>>b[2];//输入
    sort(a,a+3);//快排
    sort(b,b+3);//快排
    cout<<abs(a[0]-b[0])+abs(a[1]-b[1])+abs(a[2]-b[2])<<endl;
}
```

---

