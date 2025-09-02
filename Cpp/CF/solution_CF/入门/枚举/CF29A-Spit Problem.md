# Spit Problem

## 题目描述

In a Berland's zoo there is an enclosure with camels. It is known that camels like to spit. Bob watched these interesting animals for the whole day and registered in his notepad where each animal spitted. Now he wants to know if in the zoo there are two camels, which spitted at each other. Help him to solve this task.

The trajectory of a camel's spit is an arc, i.e. if the camel in position $ x $ spits $ d $ meters right, he can hit only the camel in position $ x+d $ , if such a camel exists.

## 样例 #1

### 输入

```
2
0 1
1 -1
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
3
0 1
1 1
2 -2
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
5
2 -10
3 10
0 5
5 -5
10 1
```

### 输出

```
YES
```

# 题解

## 作者：06ray (赞：10)

这道题数据水，普通直接暴力枚举可以过。

首先读入n，每只骆驼的位置以及吐口水的距离，用两个数组储存他们。

接下来开始暴力。用双重循环分别枚举其中的两只骆驼，判断他们是否能互相吐口水，如果可以，输出YES，结束程序。最后如果循环结束，说明无解，此时可以输出NO。

复杂度为O（n^2）。

```cpp
下面贴一段极其简短的代码：
#include <iostream>//头文件
using namespace std;//名字空间
int a[10000],x[10000];//定义两个数组
int main()
{
    int n;
    cin>>n;//读入n
    for(int i=1; i<=n; i++)
    {
        cin>>a[i]>>x[i];//读入每只骆驼的位置以及吐口水的距离
    }
    for(int i=1; i<=n; i++)//暴力枚举
    {
        for(int j=1; j<=n; j++)
        if(i!=j)//如果他们两不是同一只骆驼
        {
            if(a[i]+x[i]==a[j]&&a[j]+x[j]==a[i])//如果他们可以互相吐口水
            {
                cout<<"YES";//输出YES
                return 0;//可以直接结束程序
            }
        }
    }
    cout<<"NO";//输出NO
    return 0;
}
```

# 思路极其简单，此题也比较水，不要不想就直接抄代码，请大家创造一个美好的洛谷！！！

---

## 作者：封禁用户 (赞：1)

## 前言

~~这题差一点把我吓死了，以为是一道"入门"的DP~~，接着一看数据范围：$1\leq{n}\leq{100}$


看完题目之后，~~我真佩服出题人竟然能想得出这种东西~~，我的思路是 ```枚举```

## 思路

思路其实很简单，就是用两个数组存放距离和位置。

然后双层循环枚举，如果这两个骆驼可以相互吐口水，

那么就输出```YES```,否则输出```NO```。

```cpp
#include <iostream>
#include <cstdio>
#define INF 105
using namespace std;
int n,a[INF],b[INF];
int main()
{
	cin>>n;// 读入n 
	for (int i=1;i<=n;i++) cin>>a[i]>>b[i];// 读入两个数组 
	for (int i=1;i<=n;i++)
	{//双层循环暴力枚举 
		for (int j=1;j<=n;j++)
		{
			if (a[i]+b[i]==a[j] && a[j]+b[j]==a[i])
			{
				//如果找到了，那么就输出YES然后终止程序 也就是return 0 
				cout<<"YES"<<endl;
				return 0;
			} 
		}
	}
	//如果一次都没有成立那么就输出NO 
	cout<<"NO"<<endl;
	return 0;
}
```

> 咦？这个代码怎么感觉不太对？

试试看数据:

1

0 0

~~恭喜我，成功被自己卡掉了！~~

其实很简单只要加上一个

```cpp
if (i==j) continue; 
```

就可以了。

~~不过CF好像没有卡我~~

## 总结

此题目可以用来给新手练习! 

---

## 作者：_newbie_ (赞：1)

```c
#include<cstdio>
#include<cstring> 
#include<iostream>
using namespace std;
int main()
{
    int a[1001]={0},b[1001]={0};
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
    cin>>a[i]>>b[i];
    for(int i=1;i<=n;i++)
    {
    	int num=a[i]+b[i];  //吐到的坐标
    	int place=a[i];  //标记骆驼的位置
    	for(int j=1;j<=n;j++)
    	{
    		if(num==a[j])
    		{
    			if(a[j]+b[j]==place)  //互相能吐到
    			{
    				cout<<"YES";
    				return 0;
    			}
    		}
    	}
    }
    cout<<"NO"; //否则没有
    return 0;    	
}
```

---

## 作者：PC_DOS (赞：1)

这是一道模拟题，我们可以通过STL的map数据结构建立从一个位置到另一个位置的映射关系，在执行每次输入时，以输入的x为索引，x+d为值插入到map中，如果map(map(x))=x，那么就说明两只骆驼可以互相吐到口水。

务必注意，由于map(map(x))不一定存在，因此必须在读取前使用map提供的find()方法检查对应位置是否存在，如果find()方法返回的值不等于map.end()返回的植，则说明对应位置的项目存在，此时才可以进行映射关系的检查。

代码:
```
#include <iostream>
#include <map>
using namespace std; //头文件和命名空间
int main(){
	ios::sync_with_stdio(false); //输入输出加速
	map<long long,long long> mapCamels; //存放骆驼的位置以及对应的位置
	int nCount,iPos,iDist; //nCount-个数；iPos-位置；iDist-距离
	bool IsFound=false; //标识是否找到
	register int i; //循环计数器
	cin>>nCount; //读入个数
	for (i=1;i<=nCount;++i){ //循环读入
		cin>>iPos>>iDist; //读入位置和距离
		mapCamels[iPos]=iPos+iDist; //保存位置和对应的位置
		if (mapCamels.find(mapCamels[iPos])!=mapCamels.end() && mapCamels[mapCamels[iPos]]==iPos){ //进行映射关系检查，务必注意，由于map(map(x))不一定存在，因此必须在读取前使用map提供的find()方法检查对应位置是否存在，如果find()方法返回的值不等于map.end()返回的植，则说明对应位置的项目存在
			IsFound=true; //标识找到
		}
	}
	if (IsFound) //找到否
		cout<<"YES"; //输出
	else //否则
		cout<<"NO"; //输出
	return 0; //结束
}
```

---

## 作者：hensier (赞：1)

该题双重循环即可。~~（暴力出奇迹）~~

为了保存骆驼的位置和喷射范围，我们可以在二维数组和$struct$之间选用一个。本蒟蒻这次使用了$struct$。

首先是输入：

```cpp
scanf("%d",&n);//输入个数
while(n--)//重复n次
{
    x++;
    scanf("%d%d",&c[x].p,&c[x].range);
}
```
注意！！！上述不能改成：

```cpp
scanf("%d%d",&c[++x].p,&c[x].range);
```

否则后果不堪设想——~~第一个点就听取蛙声一片~~。

然后设置一个双重循环，分别用$i,j$，满足$i∈[1,x],j∈(i,x]$，其实也可以$i∈[1,x)$，不过出入也不大。即：

```cpp
for(i=1;i<=x;i++)//区间循环
{
    for(j=i+1;j<=x;j++)//区间循环
    {
        if(c[i].p+c[i].range==c[j].p&&c[i].range==-c[j].range)//条件：如果i骆驼的喷射位置等于j骆驼的位置，且j骆驼的喷射位置等于i骆驼的位置就满足条件——这时输出YES并直接结束整个程序
        {
            printf("YES");
            return 0;
        }
    }
}
```

这个问题解决了，基本上程序就没有多大问题。

你们最爱的无注释无损清晰$AC$代码：[（本蒟蒻AC记录）](https://www.luogu.com.cn/record/31175200)

```cpp
#include<cstdio>
struct camel
{
    int p,range;
}c[101];
int n,i,j,x;
int main()
{
    scanf("%d",&n);
    while(n--)
    {
        x++;
        scanf("%d%d",&c[x].p,&c[x].range);
    }
    for(i=1;i<=x;i++)
    {
        for(j=i+1;j<=x;j++)
        {
            if(c[i].p+c[i].range==c[j].p&&c[i].range==-c[j].range)
            {
                printf("YES");
                return 0;
            }
        }
    }
    printf("NO");
}
```


---

## 作者：OdtreePrince (赞：0)

# -模拟-

百忙之中无聊的我开始傻傻的写了一个排序，后来才发现并没什么卵用，QAQ。

本题除了模拟还是模拟，用结构体更好看一点吧！

求神犇膜拜！

~~~
#include<bits/stdc++.h>
using namespace std;
int n;
struct luotuo{
    int x,d;
}lt[105];
bool cmp(const luotuo a,const luotuo b){
    return a.x<b.x;
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d%d",&lt[i].x,&lt[i].d);
    }
    sort(lt+1,lt+n+1,cmp);
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            if((lt[i].x+lt[i].d==lt[j].x)&&(lt[j].x+lt[j].d==lt[i].x)){
                cout<<"YES";
                return 0;
            }
        }
    }
    cout<<"NO";
    return 0;
}
~~~

---

## 作者：LJY_ljy (赞：0)

# 这道题目很简单。

只要**看两只不相同的骆驼**能不能互相看口水。

定义一个bool型的flag来判断是否能成立。**flag一开始赋值为false.**

一旦能，就可以输出YES,然后高兴的flag=true了。

如果**最后**flag是true,则成立，输出YES，否则输出NO。


------------
上代码：
```cpp
#include <iostream>
using namespace std;
int a[1200],b[1200];
int main()
{
    int n;
    cin>>n;
    bool flag=false;
    for (int i=1;i<=n;i++)
    {
        cin>>a[i]>>b[i];
    }
    for (int i=1;i<n;i++)
    {
        for (int j=i+1;j<=n;j++)//这样就不会有两只重复的骆驼了。
        {
            if (a[i]+b[i]==a[j] && a[i]==a[j]+b[j])//看能不能互相都能吐出口水往另一只骆驼上喷，所以是&&。
                flag=true;
        }
    }
    if (flag)
        cout<<"YES";
    else
        cout<<"NO";
    return 0;
}
```

---

