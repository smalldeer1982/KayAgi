# Vanya and Fence

## 题目描述

有n个人，如果这个人的高度大于k，那么马路宽度+2，否则+1，输出最终的宽度值。

## 样例 #1

### 输入

```
3 7
4 5 14
```

### 输出

```
4
```

## 样例 #2

### 输入

```
6 1
1 1 1 1 1 1
```

### 输出

```
6
```

## 样例 #3

### 输入

```
6 5
7 6 8 9 10 5
```

### 输出

```
11
```

# 题解

## 作者：666yuchen (赞：5)

 ### 二话不说上代码：
```c++
//666yuchen
#include<iostream>
#include<cmath>
#include<cstdio>
#include<string>
#include<cstring>
#include<cstdlib>
#include<algorithm>//文件头
#define ii int
using namespace std;
ii n,k,a,gs;//定义
int main()
{
  cin>>n>>k;//输入
  for(int i=1;i<=n;i++)
  {
  	cin>>a;//输入这个人的高度
  	if(a>k)gs+=2;//如果这个人的高度＞篱笆的高度(也就是k)，那么能量值+2。
  	else gs++;//否则+1。
  }
  cout<<gs;//输出
  return 0;
}
```
### 为了营造美好的洛谷，请不要抄袭!!!

---

## 作者：wyy134 (赞：1)

来自蒟蒻的第三波题解

------我系分界线------ 

话不多说，直接上简单易懂滴代码

```
#include<iostream>
using namespace std;
int main()
{
	long long i,n,k,q,a;
	cin>>n>>k;
	q=n;//反正每个人都是至少要+1的，那就直接先赋值人数
	for (i=1;i<=n;i++)
	{
	    cin>>a;
	    if (a>k) q++;//判断 如果超过k 那就+1
	}
	cout<<q<<endl;
	return 0;
}
```
随便吐槽一句，现在翻译真是简单，对于我这个英语渣渣来说真是好极了

~~唉，复制英文粘贴到百度翻译后发现其实机器翻译后更容易理解，就是会有bug嘻嘻~~

---

## 作者：FP·荷兰猪 (赞：1)

> 题意：有n个人，如果这个人的高度大于k，那么马路宽度+2，否则+1，输出最终的宽度值。

这题直接模拟即可，时间复杂度O(n)：
```cpp
#include <iostream>
using namespace std;
int main()
{
	int n,k;
	cin>>n>>k;
	int i,x,ans;
	ans=0;
	for (i=1;i<=n;i++)
	{
		cin>>x;
		if (x>k)//判断是否比k大
		{
			ans+=2;
		}
		else
		{
			ans+=1;
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：monkeywoora (赞：1)

Python3代码奉上。
```
a=input().split()
b=int(a[1])
c=input().split() //接收数据
for i in range(len(c)):
    c[i]=int(c[i])
d=int(0)
for j in range(len(c)):
    if c[j]>b:
        d+=2 //大者则加2
    else:
        d+=1 //小者或等者则加1
print(int(d))
```
蒟蒻第一次提交，请诸位多多指教！

---

## 作者：TRZ_2007 (赞：0)

看见大家好像都没有拿数组存啊！  
看来我是太蒟蒻了~~  
### 这道题的思路
首先我们来查看一下$n$和$k$的取值范围，嗯，小于$1000$。好的，看来不用定义长整型了，一个$int$就搞定。  
输入$n$和$k$，开始读入数组$a$，读完后再从1一直循环到$n$，碰到大于$k$的+2，小于$k$的+1最后输出就好啦$qwq$  
### 附$AC$代码一篇
```
#include <stdio.h>
#define N 1100//小于1000，就定义1100
int n,k,ans;//三个变量
int a[N];
int main()
{
	int i;
	scanf("%d %d",&n,&k);
	for(i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(i=1;i<=n;i++)
		if(a[i]>k) ans+=2;//大于k的+2，小于k的+1
			else ans+=1;
	printf("%d\n",ans);//输出就好啦
}
```

---

## 作者：不到前10不改名 (赞：0)

//这题翻译的太直白了...直接把cf的坑题给变成了一道水题，按照题意做就行
```
#include<stdio.h>
int n,k,t,i,srx;
int main()
{
    scanf("%d%d",&n,&k);
    for(i=1;i<=n;++i)//自从day1t2暴力模拟75re不够大，加大范围没变反而tle，把i++改成++i后90...我就再也不用i++了~
    {scanf("%d",&t);//又用不着，不用拿数组存了...
    if(t>k)//只要比k大，就加2（等于不行，只能加1）
    srx+=2;
    else
    srx+=1;}//否则加1
    printf("%d",srx);//输出总和
    return 0;
}
```

---

## 作者：OdtreePrince (赞：0)

本人花30sA掉这道题，模拟出奇迹！

ans统计答案，输出即可，纯模拟，没有谁看不懂代码吧？！

~~~
#include<bits/stdc++.h>
using namespace std;
int main(){
    int ans=0,n,k,a;;
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++){
        scanf("%d",&a);
        if(a>k) ans+=2;
        else ans++;
    }
    cout<<ans;
    return 0;
}~~~

---

## 作者：开心的猪 (赞：0)

这道题可以直接按照题意进行模拟。

直接上代码。

```cpp
#include<bits/stdc++.h>

using namespace std;

int main()
{
	int n, k, ans=0;;
	scanf("%d%d", &n, &k);
	for(int i=0; i<n; i++)
	{
		ans++;
		int temp;
		scanf("%d", &temp);
		if(temp>k)
		{
			ans++;
		}
	}
	printf("%d", ans);
	return 0;
}
```


---

## 作者：thename (赞：0)

其实还是很水的，但是这个翻译真良心，竟然这样简单(~~一不小心道出了自己语文渣的事实~~)

废话不多讲，其实这道题的思路很简单，大致分为三部分：

**一、输入部分，输入n和k（~~废话，各位大佬可以无视~~）**

```
cin>>n>>k;//输入
```
**二、主体部分，从零到n-1遍历输入，判断**
```
	for(int i=0;i<n;i++)//从零开始输入 
	{
		cin>>a;//输入 
		if(a>k)ans++;//如果大于了那个数，就额外加一，因为无论多高，最少加一，少加的在后面那条语句补全 
		ans++;//每个人都加1 
	}
```
**三、输出部分（~~又是废话，各位大佬可以接着无视~~）**
```
cout<<ans;//输出 
```
最后贴上完整代码

```
#include<iostream>
using namespace std;
int a,n,ans,k;
int main()
{
	cin>>n>>k;//输入 
	for(int i=0;i<n;i++)//从零开始输入 
	{
		cin>>a;//输入 
		if(a>k)ans++;//如果大于了那个数，就额外加一，因为无论多高，最少加一，少加的在后面那条语句补全 
		ans++;//每个人都加1 
	}
	cout<<ans;//输出 
	return 0;//完美结束 
} 
```



---

