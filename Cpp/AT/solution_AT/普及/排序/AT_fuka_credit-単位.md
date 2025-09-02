# 単位

## 题目描述

[problemUrl]: https://atcoder.jp/contests/fuka5/tasks/fuka_credit



# 题解

## 作者：该起什么名字 (赞：7)

趁没有题解赶紧水一波   
~~题目描述不太清楚，一定是我语文太菜了~~  
好像是少了一句说学习了一门课就会获得一学分  
那就容易了  
~~请初次做AT水题的大佬注意，一定要在答案后输出回车，除非题目中有说明~~

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[105];
int main()
{
	std::ios::sync_with_stdio(false);
	while(1)//到读到0,0才停止，我就用while了
	{	
		int m,n;
		cin>>n>>m;//n和k
		if(n==0&&m==0) break;//跳出
		for(int i=1;i<=n;i++)
		cin>>a[i];
		sort(a+1,a+1+n);//把出席次数从小到大排个序，因为是要输出最少的出席次数
		int sum=0;
		for(int i=1;i<=m;i++)//累加，直到获得K学分，也就是上了k节课
		sum+=a[i];
		cout<<sum<<endl;//AT的题都要输出回车
	}
	return 0;
}

```

---

## 作者：Tsumi (赞：2)

### 蒟蒻的题解，话不多说直接上代码（~~无话可说~~
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,k;
	int sum; 
	int i;
	int a[110]={0};
	while(cin>>n>>k){
		if(n==0&&k==0) return 0;//输入结束
		sum=0;//需要出席的次数 
		for(i=0;i<n;i++){
			cin>>a[i];
		}
		sort(a,a+n);//排序一下，最少出席次数赢得最多的学分 
		i=0;//把i归零，从数组头开始计算sum 
		while(i<k)//i同时也是所加的学分，大于k即可毕业 
		{
			sum+=a[i];
			i++;
		}
		cout<<sum<<endl;
		//输出别忘了换行 
		//输出别忘了换行 
		//输出别忘了换行 
	}
	return 0;
}

```
怎么样是不是~~很简单~~

---

## 作者：空城旧梦— (赞：2)

## pascal  的计数排序解法！！

不得不说，这真的不是道绿题，和红题的难度差不了多少…

首先肯定想到的是对x数组排序，然后分析一下。归并排序、堆排序、基数排序o(n ㏒ n)不会超时；快 
排平均o(n ㏒ n)，最差o(n²)，应该也不会超时；忽然发现这题的时限竟然是2秒！！所以…貌似插入排 
序、冒泡排序、选择排序o(n²)都能过……但这次我介绍一个新算法——计数排序

由于这题的每个课的所需出席次数均小于等于100（x[i]<=100），所以我们可以定义一个数组s，记录需 
要出席i次的课程有s[i]个，最后只需一次遍历即可求出最小所需。是不是听起来很666的样子？？时间 
复杂度o(2n)。

代码详见如下：

```pascal
var  s:array[0..100]of  longint;
     n,k,x,i,j,ans:longint;
begin
  while  true  do
    begin
      readln(n,k);
      if  (n=0)and(k=0)then  exit;

      fillchar(s,sizeof(s),0);//注意别忘了每次清零
      for  i:=1  to  n  do
        begin
          read(x);
          inc(s[x]);
        end;

      ans:=0;
      for  i:=0  to  100  do//线性遍历得出结果
        if  s[i]>0  then
          if  s[i]<k
            then  begin  inc(ans,s[i]*i);  dec(k,s[i]);  end
            else  begin  inc(ans,k*i);  break;  end;
      writeln(ans);
    end;
end.

```

---

## 作者：Mr_WA的大号 (赞：0)

因为我刚好遇见你，留下题解才美丽。小学生又来发题解了！

题号：AT173

难度：★★

算法：排序、模拟

## 开课了！

这道题总体来讲还是挺容易的。总结一下就只有三步骤：

第一步：输入，判断n和k是否为0，均为0则退出或结束，否则进入第二步

第二步：输入变量，表示在各讲课中可以取得的单位数。之后把这些单位数从小到大排序。

第三步：用for循环从1到k累加数字，最后输出。

细节：

1.输入可以嵌套在while(1)或for(int i=1; ; i++)中，到n和k均为0时再退出。

2.累加器在加时应该先清0。

课讲完了，上代码：

```cpp
#include<iostream>
#include<fstream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<string.h>
#include<algorithm>
using namespace std;
int n,k,ans,a[110];//定义
int main()
{
	for(int i=1; ; i++)//这条语句会一直循环下去，因为它没有结束条件
	{
		cin>>n>>k;//输入
		if(n==0&&k==0)return 0;//如果n、k都为0，结束程序
		for(int j=1; j<=n; j++)
			scanf("%d",&a[j]);//循环输入
		sort(a+1,a+1+n);//快排
		ans=0;//要把累加器清零
		for(int j=1; j<=k; j++)
			ans+=a[j];//累加器累加
		printf("%d\n",ans);//输出
	}
	return 0;
}
```
祝大家能AC！

---

