# Tetris

## 题目描述

You are given a following process.

There is a platform with $ n $ columns. $ 1 \times 1 $ squares are appearing one after another in some columns on this platform. If there are no squares in the column, a square will occupy the bottom row. Otherwise a square will appear at the top of the highest square of this column.

When all of the $ n $ columns have at least one square in them, the bottom row is being removed. You will receive $ 1 $ point for this, and all the squares left will fall down one row.

You task is to calculate the amount of points you will receive.

## 说明/提示

In the sample case the answer will be equal to $ 2 $ because after the appearing of $ 6 $ -th square will be removed one row (counts of the squares on the platform will look like $ [2~ 3~ 1] $ , and after removing one row will be $ [1~ 2~ 0] $ ).

After the appearing of $ 9 $ -th square counts will be $ [2~ 3~ 1] $ , and after removing one row it will look like $ [1~ 2~ 0] $ .

So the answer will be equal to $ 2 $ .

## 样例 #1

### 输入

```
3 9
1 1 2 2 2 3 1 2 3
```

### 输出

```
2
```

# 题解

## 作者：幻之陨梦 (赞：4)

[$\color{blue}\text{安利一下自己的博客}$](https://www.luogu.org/blog/ZhanLang/)

**解题思路：** 因为题目说让你求所有相同的数中，选最少的数量输出，所以我们就可以运用到桶排序来求，并且因为 $n$ 的范围并不大，所以才能用桶排序。
```cpp
#include<bits/stdc++.h>//万能头
using namespace std;//标准库
inline int read()//快读 
{
    int x=0,k=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-') k=-1;c=getchar();}
    while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
    return x*k;
}
int n,m,x,a[1001];//定义
int main(void)
{
	n=read(),m=read();//输入
	for(int i=1;i<=m;i++)
	{
		x=read();//输入当前数
		a[x]++;//桶排序的关键
	}
	sort(a+1,a+n+1);//因为要输出最小，所以排序一下
	printf("%d",a[1]);//输出最小的数量
}
```


---

## 作者：Register (赞：3)

奇怪，大佬们为什么要用sort呢？
# 这道题太水了，1~n每个位置都有数，不会留白！也不用担心数不在1~n里！！！
这道题原文好像是一个正方形怎么怎么了，我也不清楚（蒟蒻英语差）

话不多说，上代码：
```cpp
#include <iostream>//输入输出流库
#include <cstring>//memset库
using namespace std;
int main(){
	int s[1001]/*桶*/,n,m,a,minn=1000/*统计最小的*/;
	memset(s,0,sizeof(s));//清零
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		cin>>a;
		s[a]++;//往桶里面填充
	}
	for(int i=1;i<=n;i++)
		if(s[i]<minn) minn=s[i];//比较，寻找最小
	cout<<minn<<endl;
	return 0;//一道CF水题就这么结束了
}
```

---

## 作者：rill4474 (赞：2)

## 这题只要用基础桶排+查找最小值就可以了
# （注意1..n每个数都会有，所以要1..n查找，而不用特意不统计0的个数）
```pascal
program chaoxi is sb;
var
 i,j,k,n,m,s,max,min,l,r,mid:longint;//定义必备
 a:array[1..100000]of longint;
begin
s:=maxlongint;//最大longint
read(n,m);
for i:=1 to m do
begin
 read(k);//输入数
 inc(a[k]);//都给我进桶里去（感觉桶要爆了）
end;
for i:=1 to n do if (a[i]<s)then s:=a[i];//找最小值
write(s);//输出
end.
```

---

## 作者：两年打铁 (赞：1)

很简单的一道题，只需要开一个数组记录各个数字出现的次数然后排序以下就可以了。
超级代码分割线



------------
```
#include<bits/stdc++.h>
using namespace std;
int a[1001],b[1001],c,d,i;
int main()
{
	cin>>c>>d;
	for(i=1;i<=d;++i)
	{
		cin>>a[i];
		b[a[i]]++;可以在输入的时候就用b数组来统计各个数字的出现次数。
	}
	sort(b+1,b+c+1);最后将b数组进行一个排序。
	cout<<b[1];	找到第一位即出现次数最小的那一位。
}
```

---

## 作者：meyi (赞：1)

# 本蒟蒻又AC了一道~~（shui）~~题（笑）
### 看见已有的C++题解中，作者使用桶排思想，所以开了两个数组，其实有一个数组没有必要开，只需要用变量代替就行了。
#### 废话不多说，接下来就是~~超短~~的AC代码了（可能有些注释较绕口，请谅解）：
```cpp
#include<cstdio>
#include<algorithm>	//手打快排？不存在的，直接使用sort，STL大法好！
int a[1001],b,n,m;	//n和m变量同题意，a数组统计出现的数的出现次数，b变量为出现的数。
main(){
	scanf("%d%d",&n,&m);
	while(m--)scanf("%d",&b),++a[b];	//输入出现的数，同时次数加上一。
	std::sort(a+1,a+n+1);	//因为题目中有说出现的数>=1，所以起始地址应为1，忽略0，同时需要排到n，所以结束地址应为n+1。
	printf("%d ",a[1]);	//排过序后，a数组的一号地址存放的便是出现次数最少的数的出现次数了，完美输出，结束程序。
}
```

---

## 作者：hensier (赞：0)

该题不需要使用$sort$，可以使用桶排序类似的算法。时间复杂度大约为$O(m+n)$。

```cpp
#include<cstdio>
#define min(a,b) a<b?a:b//这里没有调用algorithm，所以可以自己定义一下
int n,m,i,a[1001],b[1001],minn=1e8;//a数组保存输入的数，b为桶
int main()
{
    scanf("%d%d",&n,&m);
    for(i=1;i<=m;i++)scanf("%d",&a[i]),b[a[i]]++;//往桶里装
    for(i=1;i<=n;i++)minn=min(minn,b[i]);//在[1,n]区间通过替换的方法寻找最小
    printf("%d",minn);
}
```

---

## 作者：封禁用户 (赞：0)

# CF961A Tetris 题解

这道题目如果理清思路就不难，我们来分析一下：

- 我们可以输入之后来判断，如果这个数字 $\le n$ 我们就把他像**桶排序**一样插入到一个桶里面
- 插入完之后，来比较桶里面哪一个数量最少
- 输出即可

时间复杂度：$O(nlogn) ~ O(n^2)$ 之间。

代码：

```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;//using不多说
int main()
{
    int n,m,a[10001],flag[100001];//定义
    cin>>n>>m;//输入
    for(int i=1;i<=m;i++)//循环输入并判断
    {
        cin>>a[i];//输入
        if(a[i]<=n) flag[a[i]]++;//如果这个数字小于n，插进桶里面
    }
    sort(flag+1,flag+n+1);//快排
    cout<<flag[1];//输出最小的那个
    return 0;//华丽结束
}
```

学会了吗？

[Thomas_ 的博客](https://zyy-txws-noip.blog.luogu.org/)

原创，侵权必究

---

## 作者：一滴小水滴 (赞：0)

**这道题其实是不需要用sort的**
## 思路：
不断输入数a，然后用一个记录每个数出现此数的数组sum来记录，即sum[a]++，最后从1到n每个数出现的此数都比较一遍，求出最小值。
## AC代码：
```cpp
#include<bits/stdc++.h>
#define maxn 1005
#define INF 0x7ffffff
    //没什么好讲的，就是为了装个X
using namespace std;
inline int read()
{
	int x=0,w=0;
	char ch=0;
	while(!isdigit(ch))
	{
		w|=ch=='-';
		ch=getchar();
	}
	while(isdigit(ch))
	{
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return w? -x:x;
}
inline void write(int x)
{
	if(x<0)
	{
		putchar('-');
		x=-x;
	}
	if(x>9)write(x/10);
	putchar(x%10+'0');
}   //本人最近爱上了快读快写。
int n,m,a,sum[maxn],minn=INF;
   //记得将minn初始化为最大值（a可以不用数组，节省空间）。
int main()
{
	memset(sum,0,sizeof(sum));
	n=read(),m=read();
	for(int i=1;i<=m;i++)
	{
		a=read();
		sum[a]++;
	}
	for(int i=1;i<=n;i++)
		minn=min(sum[i],minn);
             /由于本题不会超出n的范围，所以直接1~n比较就可以了。
	write(minn);
	return 0;
}
```

---

## 作者：Ace_Radom (赞：0)

## 还是很~~shui~~的啦

许多大佬都在用sort

### 为啥呢

这……其实是一道非常好的**桶排练习题**啊

那么桶排是啥呢？

	桶排序（Bucket Sort）是一种线性排序算法
    由于不使用比较排序算法，它的时间复杂度为O(n)，并不受下线O(n log n）的限制
    工作的原理是将数组分到有限数量的桶子里。每个桶子再个别排序（有可能再使用别的排序算法或是以递归方式继续使用桶排序进行排序）。它是鸽巢排序的一种归纳结果。
    
桶排速度快（线性速度你能说不快？），数据再大也没什么关系啊

总的来说，算法就是先把所有数据读入，再在1-n的范围内找出出现次数最少的数

这里**桶**就是记录每个数字出现次数的数组

再用一个变量求出最小值，输出即可

嗯好想不出可以讲啥了

上代码：

```
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n,m;
    cin >> n >> m;
    int a[1001],i,minn = 315360000;  
    //minn要预设一个较大的数，否则会出错
    //数组a用来记录每个数出现的个数
    memset( a , 0 , sizeof( a ) );  //数组归零
    for ( i = 1 ; i <= m ; i++ )
    {
        int t;
        cin >> t;  //读入每一个数，再把数组里统计这个数的那个桶加1
        a[t]++;
    }
    for ( i = 1 ; i <= n ; i++ )
    {
        if ( a[i] < minn )
            minn = a[i];  //找最小值
    }
    cout << minn;  //输出，结束
    return 0;
}
```

虽然用sort也能过……

### 但是能优化就优化一下吧……

### 毕竟如果遇到大数据的话是过不了的

---

## 作者：hgoicjl (赞：0)

#### 翻译：
您将获得以下流程。 有一个有n列的平台。在这个平台上的一些列中，1×1的方块一个接一个地出现。**如果该列中没有正方形，则正方形将占据底行。否则，方块将出现在此列的最高平方的顶部。** 当所有n列最底行都被方块填满时，底行将被删除。你将获得1分，剩下的所有方格都将落下一排。 您的任务是计算您的积分。（Google翻译+略微修改）

这不就是**俄罗斯方块**！

## 题意：
给定一串数字，范围（1<=ai<=n），统计（1<=ai<=n）里出现次数最少的次数

### 思路：

用一个数组a[1000]，下标表示对应的数字，而它的值表示出现的次数
从头到尾扫一遍取得最小值输出即可  
#### 并没有坑！

### AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int a[1001]={0},b,c,mi/*记录最小值*/=9999;
	cin>>b>>c;
	for(int i=1;i<=c;i++)
	{
		int j;
		cin>>j;
		a[j]++;//统计出现的次数
	}
	for(int i=1;i<=b;i++)
		mi=min(mi,a[i]);//寻求最小值
	cout<<mi;
   	return 0;
 } 
```


---

## 作者：pascalfans (赞：0)

首先，看到题目时感觉是道计数题~~真香~~。

计数就是桶。

所以上代码:
```cpp
var
 n,m,x,i,min:longint;
 a:array of longint;//动态数组
begin
 readln(n,m);
 setlength(a,n);//动态数组 下标0~n-1 a是数组名 n是长度
 for i:=1 to m do
  begin
   read(x);
   a[x-1]:=a[x-1]+1;//Why要-1？ 0~n-1，不-1数组等着炸掉吧
  end;
 for i:=0 to n-1 do
  if a[i]<min then min:=a[i];//打擂台
 writeln(min);
end.
```
还有个小Bug，自己找去

提示:找最小时要干什么？

动态数组：

setlength(a,x) 上面解释过了

其他同普通数组，就是Watches显示～～～～挺哲学的

---

## 作者：洛潇 (赞：0)

#### 显然，这是一道水题
那就直接上代码吧...
```c
#include<bits/stdc++.h>//万能头
using namespace std;
const int maxn=100001;//直接初始化
int main()
{
	int  n,m,i,a[maxn],min=100001,k;
	cin>>n>>m;//输入数据
	for(i=1;i<=m;i++)
	{
		cin>>k;//录入m个数
		a[k]++;//分别统计输入的每个数字的个数
	}
	for(i=1;i<=n;i++)//把所有要找的数过一遍
	{
		if(a[i]<min) min=a[i];//比较，选出最小值
	}
	cout<<min;//输出
	return 0;
}
```
个人感觉也就是桶+查找最小值...

---

## 作者：FP·荷兰猪 (赞：0)

> 题意：给定n，m和c[1]...c[m]，求1~n在c数组中出现次数最少的数的出现次数

**模拟即可！**

n和m都只到1000，可以开一个a[1005]作为标记数组，每读入一个c[i]就在数组中统计一次c[i]，最后sort一遍，输出最小的元素。

详见代码：
```cpp
#include <iostream>
#include <algorithm>
using namespace std;
const int FXT=1005;
int a[FXT],n,m;//数组开在全局会给每个元素自动清零
int main()
{
	ios::sync_with_stdio(false);
	cin>>n>>m;
	int c[m+1],i;
	for (i=1;i<=m;i++)
	{
		cin>>c[i];
		a[c[i]]++;//一遍读入c[i]一边给a数组中相应的元素++
	}
	sort(a+1,a+n+1);//将a数组从小到大排序
	cout<<a[1]<<endl;
	return 0;
}
```

---

