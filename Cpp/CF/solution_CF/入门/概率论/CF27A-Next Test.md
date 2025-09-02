# Next Test

## 题目描述

### 题面描述

给出 $n$ 个互不相同的整数 $a_i$ ，从小到大找第一个没有出现过的整数。

## 说明/提示

$1\leq n\leq 3000$

 $1\leq a_i\leq 3000$

## 样例 #1

### 输入

```
3
1 7 2
```

### 输出

```
3
```

# 题解

## 作者：judgejudge (赞：14)

# 最简做法！！！
~~突然发现自己写的跟别人有点像。。。~~

思路：

1. 定义一个数组a
1. 输入一个数n，a[n]++
1. 从头至尾开始寻找，如果发现a[n]==0，输出并且return 0

下面奉上AC代码：
```cpp
#include <iostream>
using namespace std;
int a[300001];//注意：测试点没有题目给的那么小，开大点！！
int main(){
	int i,j,k,n;
	cin>>n;
	for(i=1;i<=n;i++){
		cin>>k;
		a[k]++;//输入n，它作为一个指针，它指向的数++
	}
	for(i=1;i<=300001;i++)
	if(a[i]==0){//一旦发现没有出现过，输出且程序结束
		cout<<i<<endl;
		return 0;
	}
	return 0;
}
```


---

## 作者：醉梦未苏 (赞：4)

~~看到只有两篇题解，忍不住发一篇~~

此题$n<=3000$ 果断STL暴力解决

#### 大致作法

1. 先读入数据到vec(`vector<int>`)中
* 从一开始枚举1~3000的正整数
* 如果该数在vec中没有出现，输出并退出循环
* 否则重复2,3

**如何判断一个数是否出现？**

```cpp
//返回一个整数，代表vec.begin()~vec.end()间i的个数
if(count(vec.begin(),vec.end(),i)==0)
{cout<<i;break;}
```
看函数返回值是否为0即可

#### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
//向量
vector<int> vec;
int main()
{
    int n;
    //读入
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        int k;
        cin>>k;
        //将k存进vec尾部
        vec.push_back(k);
    }
    for(int i=1;true;i++)
    {
    	//如果整个vec中找不到i,输出并退出
        if(count(vec.begin(),vec.end(),i)==0)
        {cout<<i;break;}
    }
    return 0;
    //STL大法好
}

```

---

## 作者：liuyifan (赞：4)

因为这道题的数据很小,直接用桶排

思路:每输入一个数x就a[x]++,然后统计第一个a[i]=0输出

code:
```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
int a[3005]//桶,n,x;
//全局数组自动初始化为0
int main()
{
	scanf("%d",&n);
	for(register int i=1;i<=n;i++)
	{
		scanf("%d",&x);
		a[x]++;//上面已经说得很清楚了
	}
	for(register int i=1;;i++)//这道题不能加i<=3000,不然会WA最后一个点
	if(a[i]==0)
	{
		printf("%d",i);
		return 0;
	}
	return 0;
}
```
[My Blog](https://www.luogu.org/blog/liuyifan/)

---

## 作者：Bronya18C (赞：2)

# 做法：

首先输入完排序，然后一直枚举这个数与前面的数比较，相差大于1的说明它们中间不止一个整数没有（包括一个），要是一直没找到，直接输出最大的加1.
## 注意：
要把第一个初始为0，不是1（有可能没1）。
### 楼下的做法没有和我一样的（~~突然滑稽~~）
---
# 答案：
```
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n,N[3005];
    cin>>n;
    N[0]=0;
    for(int i=1;i<=n;i++)
    {
        cin>>N[i];
    }
    sort(N,N+n+1);
    for(int i=1;i<=n;i++)
    {
        if(N[i]-N[i-1]>1)
        {
            cout<<N[i-1]+1;
            break;
        }
        if(i==n)
        {
        cout<<N[i]+1;
        }
    }
    return 0;
}
```

---

## 作者：Aw顿顿 (赞：1)

这道题真的很简单，用一个没人用过的思路：优先队列

首先读入 $n$ ，然后循环读入 $x$ ，每次都把 $x$ 压入到队列中，即得到一个排好序的队列。

然后结束之后循环判断：

- 如果队头等于循环变量 $i$ ，那就弹出。

- 否则输出 $i$ ，结束循环。


看一下代码如何实现：

```cpp
#include<bits/stdc++.h>
using namespace std;
priority_queue<int,vector<int>,greater<int> >q;
int main()
{
    int n;
    cin>>n;
    int x;
    for(int i=0;i<n;i++)
	{
        cin>>x;
        q.push(x);
    }
    for(int i=1;i<=100000001;i++)
	{
        if(i==q.top())q.pop();
        else{
        	cout<<i<<endl;
        	return 0;
		}
    }
    return 0;
}

```

注意优先队列后面的`> >`不可以写在一起，编译器会报错误认为是位运算符`>>`

---

## 作者：_D06 (赞：1)

方法：用一个bool数组记录一个数有没有出现，然后从1开始扫一遍即可。
c++代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
bool b[3005];
int a[3005];
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		b[a[i]]=true;//标记 
	} 
	for(int i=1;i<=3001;i++)
	{
		if(b[i]==false)//找到第一个没被标记的数 
		{
			cout<<i<<endl;//输出 
			return 0;
		}
	}
	return 0;
}

```

---

## 作者：紫金依旧 (赞：0)

这道题从题面上来讲,就是一道~~大水题~~

接下来上代码——

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[3001],cnt[3001]/*桶*/,i;
int main()
{
	cin>>n;
	for(i=1;i<=n;i++)
	{
		cin>>a[i];//输入
		cnt[a[i]]++;//将一个个变量丢进桶里面
	}
  	i=1;//初始化
	while(1)//无条件进行循环
  	{
  		i++;
  		if(cnt[i]==0)//如果没有出现过这个变量
		{
			cout<<i<<endl;//输出
			return 0;//结束
		}
  	}
	return 0;
}
```

# 最后——求过

---

## 作者：谷民 (赞：0)

### 题解 CF27A 【Next Test】

由于数据范围较小，本题可利用桶排思想，标记读入数列，再从一开始扫，找到第一个未标记数。
```
#include<bits/stdc++.h>//万能头
using namespace std;
int n,a[3010],k;
int main(){
	cin>>n;//读入
	for(int i=1;i<=n;i++){
		cin>>k;
		a[k]=1;//标记数列
	}
	for(int i=1;i<=3005;i++){//找出第一个未标记的数
		if(a[i]==0){
			cout<<i<<endl;//输出，结束
			return 0;
		}
	}
	return 0;
}
```


---

## 作者：Jinyeke (赞：0)

### 题目：给出n个互不相同的整数a[i]，从小到大找第一个没有出现过的整数。输入:第一行一个正整数n，之后是n个整数a[i];输出:一个整数x，即第一个没有出现过的整数。1<=n<=3000 1<=a[i]<=3000。
### 这题有坑啊啊啊，本题本小蒟蒻用的桶排（别的没试过），看一下本小蒟蒻一开始做的（掉坑了！！！）。
```pascal
var
 max,i,j,n,x:longint;
 a:array[1..3000] of longint;
begin
 readln(n);
 for i:=1 to n do
  begin
   read(x);
   a[x]:=1;
   if x>max then max:=x;
  end;
 for i:=1 to max do 
  if a[i]=0 then begin write(i);break;end;
end.

```
### 结果，当本小蒟蒻正为找到一道水题而开心时，系统显示：WA！！！然后小蒟蒻改了一下代码，就AC了，以下放代码
```pascal
var
 max,i,j,n,x:longint;
 a:array[0..3000] of longint;//还是0~3000保险一点
begin
 readln(n);
 for i:=1 to n do
  begin
   read(x);//直接输一个数
   a[x]:=1;//用桶排存放
   if x>max then max:=x;//找最大值，虽然说这题不可能超时，但本小蒟蒻还是追求最优解
  end;
 for i:=1 to max+1 do //注意！如果用了本小蒟蒻的方法，最好max+1，因为可能一共max个数，这时候就得输出max+1
  if a[i]=0 then begin write(i);break;end;//判断，这个数是否是第一个未出现过的数。（注意：一定要break;不然会输出很多很多答案）
end.

```
 ## 共建文明洛谷，请勿Ctrl+C！


---

## 作者：BMMULLER (赞：0)

# 桶排思想

**数据不大**，直接用桶排就可以

也就是记下出现过的数，把出现次数一个数组里，然后找这个数组里第一个为零的元素，输出它的下标就可以了（就是**桶排思想**）

要注意可能1-3000这些数**都出现过**的情况，不然会WA一个点

```
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int main(){
	int a[3010],tong[3010],n;
	cin>>n;
	memset(tong,0,sizeof(tong));
	for(int i=0;i<n;i++){
		cin>>a[i];
	}
	for(int i=0;i<n;i++){
		tong[a[i]]++;
	}
	for(int i=1;i<=3001;i++){
		if(tong[i]==0){
			cout<<i;
			break;
		}
	}
	return 0;
} 
```


---

