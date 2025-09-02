# Bear and Raspberry

## 题目描述

给定一个序列，请求出相邻两个数之间（前数$-$后数）差的最大值与$c$的差。

如果结果小于$0$的话就输出$0$。

## 样例 #1

### 输入

```
5 1
5 10 7 3 20
```

### 输出

```
3
```

## 样例 #2

### 输入

```
6 2
100 1 10 40 10 40
```

### 输出

```
97
```

## 样例 #3

### 输入

```
3 0
1 2 3
```

### 输出

```
0
```

# 题解

## 作者：LRL65 (赞：2)

### 思路：

这题可直接用两个变量表示前一个数和后一个数，然后每次输入后做差并和最大值比较。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,b,c,maxn=-100;
int main() {
    cin>>n>>c;//输入
    cin>>a;//先输入第一个数
    for(int i=2;i<=n;i++) {//循环n-1次
        cin>>b;//输入当前这个数
        maxn=max(a-b,maxn);//做差并比较
        a=b;//这个数变成前一个数
    }
    cout<<max(maxn-c,0)<<endl;//如果这个数小于0，就输出0
    return 0;
}
```


---

## 作者：PrincessYR✨～ (赞：1)

这个道题相对来说比（te）较（bie）简单。

我们直接读入数组，在一个一个用max函数进行比较求出最大值，最后再用最大值减去C，就是最终答案。

上代码（含讲解）：

```
#include<bits/stdc++.h>
using namespace std;
inline int read()//快读
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
		f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
int n,b,a[105],c;
int main()
{
	n=read();b=read();
	for(int i=1;i<=n;i++)
		a[i]=read();//先读入数组
	for(int i=1;i<n;i++)
	c=max(c,a[i]-a[i+1]);//在依次找最大值
	if(c-b<=0) cout<<"0";//如果最终值小于0或者等于0直接输出0
	else
	cout<<c-b;//否则输出C-B。
	return 0;
}
```


---

## 作者：AkiwaZawa (赞：0)

## 暴力 之 一个循环就完事

我们先找出这个序列中的最大差值，最后输出其与0的差即可。

但是，请注意，若结果为负数，则输出0.

代码没有注释，但也是简单易懂的哦。




```
#include<bits/stdc++.h>
using namespace std;
#define N 105
int n,c,a[N];
int main () 
{
    int ans=0;
    scanf("%d%d",&n,&c);
    for (int i=0;i<n;i++) 
		scanf("%d",&a[i]);
    for (int i=1;i<n;i++) 
		ans=max(ans,a[i-1]-a[i]);
    printf("%d\n",max(ans-c,0));
    return 0;
}
```


---

## 作者：18lxxrz (赞：0)

### 题意


------------


给定一个序列，请求出相邻两个数之差的最大值与c的差。
#### 如果结果小于0的话就输出0。


------------

### 思路


------------
①普通人的想法。将这n个数存储到数组中，然后O（n）扫一遍，求出最大差值。代码如下

------------
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,c,ans=INT_MIN/9,a[110];
int main ()
{
	scanf("%d%d",&n,&c);
	for(register int i=1;i<=n;++i)
		scanf("%d",&a[i]);
	for(register int i=1;i<n;++i)
		ans=max(ans,a[i]-a[i+1]);
	printf("%d\n",max(0,ans-c));
	return 0;
}
```

------------
这样已经可以拿满分了！

但是……

------------
②蒟蒻 ~~（就是我）~~ 的想法。用两个变量代替数组，边输入边操作。代码如下


------------
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,c,ans=INT_MIN/9;
int main ()
{
	scanf("%d%d",&n,&c);
	int x,y;
	scanf("%d",&x);
	for(register int i=2;i<=n;++i)
	{
		if(i&1)
			scanf("%d",&x),ans=max(ans,y-x);
		else 
			scanf("%d",&y),ans=max(ans,x-y);
	}
	printf("%d\n",max(0,ans-c));
	return 0;
}
```
一样可以AC啦！

---

## 作者：CobaltChloride (赞：0)

```
没有pas题解???
var n,c,i,maxn:longint;
a:array[1..101] of longint;
function max(p,q:longint):longint;
begin
if p>q then exit(p)
else exit(q);
end;
//求最大值
begin
maxn:=-201;//初始化
read(n,c);
for i:=1 to n do begin
read(a[i]);
if i>=2 then maxn:=max(maxn,a[i-1]-a[i]);
end;//求差
if maxn>=c then write(maxn-c)
else write('0');//注意看题,题意提醒你了maxn<c时要输出0！
end.
```

---

## 作者：damage (赞：0)

# 题意

### 题目描述

给定一个序列，请求出相邻两个数之间（前数$-$后数）差的最大值与$c$的差。

如果结果小于$0$的话就输出$0$。

### 输入格式

第一行输入$n$和$c$。

接下来一行$n$个数字，描述整个序列。

### 输出格式

输出一行表示结果。

---

# 题解

### 直接膜你

直接按题意膜你即可。

可以不用数组存储，只要用两个变量```last```表示上一个数，```a```则表示当前输入的数。

可以一开始先读入```last```，然后读入$n-1$次```a```，逐次打擂比较出最大的```last-a```，计入结果```res```。

最后输出```res-c```即可。

### 注意题意提醒你了```res-c```$\lt{0}$时要输出$0$！

---

# 代码

```cpp
#include<stdio.h>
#include<iostream>
int n,c,a,last,res;
int main()
{
	scanf("%d%d%d",&n,&c,&last); //记得先读入第一个数last
	while(--n) //while(--n)可以直接表示读入n-1次数据
	{
		scanf("%d",&a);
		if(last-a>res) res=last-a; //比较出最大的last-a计入res
		last=a; //滚动变量记录序列
	}
	printf("%d\n",std::max(res-c,0)); //输出res-c，注意res-c小于0时要输出0，此处可以用取最大值函数来特判
	return 0;
}
```

---

