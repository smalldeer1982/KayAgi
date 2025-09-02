# Book Reading

## 题目描述

【题目大意】 最近Luba买了一本书，他希望在接下来的$n$  天里抽出$t$  秒看完这本书。（总计$t$  秒） 但是Luba每天会有一些工作，对于第$i$天，他需要花费$a_i$ 秒时间来工作。 问Luba最早在什么时候能看完这本书。（注意一天有$86400$ 秒）

## 样例 #1

### 输入

```
2 2
86400 86398
```

### 输出

```
2
```

## 样例 #2

### 输入

```
2 86400
0 86400
```

### 输出

```
1
```

# 题解

## 作者：Phykyer (赞：5)

究极无敌大水题  
注意事项题目里都有，就是每天86400s  
具体看代码 非常简单︿(￣︶￣)︽(￣︶￣)︿
```
#include<iostream>
using namespace std;

int n,t,a;

int main()
{
	cin>>n>>t;
	for(int i=1;i<=n;i++)
	{
		cin>>a;//边读边处理，无需开数组 
		t-=86400-a;//把能当天能抽出来的时间减去 
		if(t<=0){cout<<i;return 0;}//若小于等于0输出i(天数)退出 
	}
	//因为题目有保证有解，所以无需再进行操作 
	return 0;/*perfect!*/ 
}
```

---

## 作者：北雪2009 (赞：0)

这道题最关键就是要计算天数。   
首先先按照正常的思路想，只要将每天工作完之后剩余的时间减去阅读时间并让计数器增加1.最后再输出就行了。   
不过，为了以防万一，蒟蒻我还是加了一个if判断：如果在工作日看不完，就在休息日继续看。   
附上代码：   
```
#include<bits/stdc++.h>   //万能头
#include<stdio.h>    //万能头2
using namespace std;    
long long n,t,a[100+5],ans;    //定义变量
int main(){    //开启主程序
	ios::sync_with_stdio(false);   //cin,cout快读快输，用scanf和printf的朋友就不要贪心了，会RE
	cin>>n>>t;    //读入n和t
	for(int i=1;i<=n;i++)    //循环读入
		cin>>a[i];
	for(int i=0;t>0;)   //开始处理t
		t-=(86400-a[++i]),ans++;   //每次都用a[i]减去t，并且ans++
	if(t>0){   //以防万一的特判：如果在工作日的剩余时间还没有看完书
		ans+=t/86400;   //增加天数
		if(t%86400>0) ans++;   //如果有余数就再加1
	}
	cout<<ans;   //输出
    return 0;    //以一个华丽的return 0;结束主函数
}    //完结
```


---

## 作者：Frank_R_Z (赞：0)

###
开个一维数组轻松水过。
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,t,a[10002],ans=0;
	cin>>n>>t;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];//不能在运行中进行测试，或者可以用一个数保存
	}
	for(int i=1;i<=n;i++)
	{
		ans=ans+86400-a[i];//计算当天时间
		if(ans>=t)
		{
			cout<<i<<endl;
			return 0;//当即结束
		}
	}
	return 0;
}

```


---

## 作者：FP·荷兰猪 (赞：0)

> 题意：最近Luba买了一本书，他希望在接下来的n天里抽出t秒看完这本书。（总计t秒） 但是Luba每天会有一些工作，对于第i天，他需要花费a[i] 秒时间来工作。 问Luba最早在什么时候能看完这本书。（注意一天有86400秒）

这题还是很水的，数据范围也很小，O(n)模拟一遍即可。原本惟一需要自己算的东西——1day=86400s题目也给你了。

代码详解：
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	int n,t;
    cin>>n>>t;
    int cnt,i;
    for(i=1;i<=n;i++)
    {
        cin>>cnt;//这里做了一个空间上的优化，没开一维数组，一边读入一遍进行处理
        t=t-86400+cnt;减去第i天能抽出的时间
        if(t<=0)//如果没时间了
		{
			cout<<i<<endl;//直接输出i，结束
			return 0;
		}
    }
    return 0;
}
```

---

## 作者：我不是dalao (赞：0)

# **水题啊！！**
这题都能是“普及-”

我也是醉了

不多说，

一个大模拟，O（n） 0msAC

## 上代码
```c
#include<iostream>//bits浪费时间
using namespace std;
int main()
{
	int n,t,sum=0,j;
	cin>>n>>t;//读入n与t
	int a[n+1],b[n+1];
	for(int i=1;i<=n;i++)
	{
	cin>>a[i]; //读入每天不可以读书的时间
	b[i]=86400-a[i];//读入每天读书的时间
	}
	for(int i=1;i<=n;i++)
	{
		sum+=b[i];//总和加上每天的时间
		if(sum>=t)//如果大于等于的话
		{
		j=i;//记录天数
		break;	//退出
		}
		else//否则回头继续算
		continue;
	}
	cout<<j<<endl;//输出天数
	return 0;//千万别忘
}
```
### ~~诚信第一，请勿抄袭~~

---

## 作者：PC_DOS (赞：0)

一天一天地模拟即可。计算每一天用来读书的时间并加到累加器上，如果累加器的值不小于总阅读时间，那么输出当前的天数并退出循环。

代码:
```
#include <iostream>
using namespace std; //头文件和命名空间
int main(){
	ios::sync_with_stdio(false); //输入输出加速
	const long long DAY_SEC = 24 * 60 * 60; //定义一天的秒数
	long long iTimeTotal,  iTimeWork, nDay, i, iTimeCurrent=0; //iTimeTotal-所需要的时间；iTimeWork-工作时间；nDay-总天数；i-循环计数器；iTimeCurrent-总阅读时间
	cin >> nDay >> iTimeTotal; //读入总天数和所须阅读时间
	for (i = 1; i <= nDay; ++i){ //一天一天模拟
		cin >> iTimeWork; //读入当日工作时间
		iTimeCurrent += DAY_SEC-iTimeWork; //计算阅读时间并累加
		if (iTimeCurrent >= iTimeTotal){ //如果累加器的值不小于总阅读时间
			break; //退出循环
		}
	}
	cout << i; //输出天数
	return 0; //结束
}
```

---

