# [ABC067B] Snake Toy

## 题目描述

すぬけくん有 $N$ 根木棒。第 $i$ 根木棒的长度为 $l_i$。

すぬけくん想要选择 $K$ 根木棒并将它们连接起来，制作一个蛇形玩具。

蛇形玩具的长度等于所选木棒长度的总和。请你求出所有可能的蛇形玩具长度中的最大值。

## 说明/提示

### 限制条件

- $1 \leq K \leq N \leq 50$
- $1 \leq l_i \leq 50$
- $l_i$ 是整数

### 样例解释 1

如果选择长度为 $3, 4, 5$ 的木棒并连接起来，可以制作出长度为 $12$ 的蛇形玩具，这也是所有可能长度中的最大值。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5 3
1 2 3 4 5```

### 输出

```
12```

## 样例 #2

### 输入

```
15 14
50 26 27 21 41 7 42 35 7 5 5 36 39 1 45```

### 输出

```
386```

# 题解

## 作者：lsyx0918 (赞：1)

这道题就是排序+求和，简直是水题一个（至少对大佬们来说）

ememem……

现在，发射题解：
```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
bool cmp(int a,int b)//排序函数
{
    return a>b;
}
int main()//主函数
{
    int n,k,s=0;//定义变量
    cin>>n>>k;//输入
    int a[n];//定义数组
    for(int i=0;i<n;i++)//输入数组
    {
        cin>>a[i];
    }
    sort(a,a+n,cmp);//排序
    for(int i=0;i<k;i++)//计算总和
    {
        s+=a[i];
    }
    cout<<s<<endl;//输出
    return 0;//拜拜了您嘞！
}
```
最后，~~完了，职业病又犯了，可是好像该在这里写啊~~：

**AT不换行，暴零两行泪！**

---

## 作者：Cambridge (赞：1)


小学生又来发题解了！

这道岛国红题，真心很简单。我们先读入数据，将它们累加起来，用he存储它们的和。再将这n个数进行排序，从小到大排序，再把he减去从1到n-k的排序好的数，这个步骤是与其他大佬的从大到小排序再累加是等价的，最后输出he即可。~~最近掉蓝了，赶紧刷回来~~

    #include<iostream>
    #include<cstring>
    #include<cstdio>
    #include<cmath>
    #include<string>
    #include<cstdlib>
    #include<algorithm>//文件头不解释
    using namespace std;
    long long n,k,he;
    int a[10000];
    int main()
    {
    cin>>n>>k;//读入
    for(int i=1; i<=n; i++)
    {
        cin>>a[i];//读入
        he+=a[i];//累加
    }
    sort(a+1,a+1+n);//从小到大排序
    for(int i=1; i<=n-k; i++)
    {
        he-=a[i];//从1到n-k的数都要减去
    }
    cout<<he<<endl;//输出结果并换行
    return 0;
    }

好了，本蒟蒻就讲到这里，希望对读者有所帮助。


---

## 作者：林家三少 (赞：1)

At题解+1

考的就是排序，所以用快排就行了

排完序以后再循环累加就行了

代码：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>  //打好文件头
using namespace std;
int n,k,ans;  //定义变量
int a[50+10];  //定义数组
int main()
{
	cin>>n>>k;  //输入
	for(int i=1;i<=n;i++)  //循环
		cin>>a[i];  //输入数组
	sort(a+1,a+1+n);  //利用快排
	for(int i=n;i>=n-k+1;i--)
		ans+=a[i];
	cout<<ans<<"\n";  //输出
	return 0;
}
```


---

## 作者：不到前10不改名 (赞：1)

```
//又是排序题，那么再来宣传一下手写快排吧！
#include<stdio.h>
int a[100001],sum;//懒得改成防伪标识了QAQ~
void abcd(int l,int r)//快排部分详解（老套路，见at2823我的题解）
{int i=l,j=r,t;
int p=a[(l+r)/2];//相当于mid
while(i<=j)//循环不说了
{
    while(a[i]<p)
    {i++;}
    while(a[j]>p)
    {j--;}
    if(i<=j)
    {t=a[i]; 
    a[i]=a[j]; 
    a[j]=t;
    i++; 
    j--;}}//处理交换
    if(l<j)
    abcd(l,j);//继续拆分
    if(i<r)
    abcd(i,r); //这里数组我开成全局了所以不需要传参
    }
    int main()
    {	
    int i,n,m;	
 	scanf("%d%d",&n,&m);   
  	for(i=1;i<=n;i++)   
    scanf("%d",&a[i]);   
    abcd(1,n);  
    for(i=n;i>n-m;i--) //这里n到n-m是因为我是升序，若是降序就是1~m了  
    sum+=a[i];
    printf("%d\n",sum);//回车
    return 0;   
    }
    ```

---

## 作者：向日葵小班 (赞：1)

**这道题也是AT众多水题1里的一道啊！**

**（提醒一下来切AT的萌新，所有的AT要打换行！）**

**这次我就用快排了（~~dalao勿喷啊~~）**

## 思路：
**1.定义一个bool函数，用于把sort改成从大到小排**

**2.输入n,k,n个数**

**3.sort，记住要用刚才的bool函数哦**

**4.用for累加前k个数**

**5.输出累加值，AT要打换行哦**


## 放代码时间到!!!:
```cpp
#include<iostream>//头文件
#include<fstream>
#include<algorithm>
using namespace std;
int n,k,a[55],h;//定义n,k,n个数，用于累加的变量h
bool cmp(int a,int b)//bool函数，用于把sort改成从大到小排
{
	return a>b;
}
int main()
{
     cin>>n>>k;//输入n,k
     for(int i=1;i<=n;i++)//循环，输入n个数
     {
     	cin>>a[i];
     }
	 sort(a+1,a+n+1,cmp);//sort,加上bool函数从大到小排序那n个数
	 for(int i=1;i<=k;i++)//循环，用于累加前k个数
     {
     	h=h+a[i];//h+a[i]
     }
     cout<<h<<endl;//输出h(注意:AT要打换行!)
    return 0;//完美结束
}
```


---

## 作者：stry (赞：0)

只是这题就是一道

------------
## 典型排序题

所以这道题的思路很简单：

首先我们只需要先读入a[i]，在从小到大的进行排序。

然后我们再从n，循环到n-k+1，h依次加这些位置的数即可。

代码如下：
```cpp
#include<iostream>
#include<fstream>
#include<algorithm>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>

using namespace std;
long long n,k,h;
int a[100+10];
int main()
{
    cin>>n>>k;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
    }
    sort(a+1,a+1+n);//快排。
    for(int i=n;i>=n-k+1;i--)//注意终止条件。
    {
        h+=a[i];//累加器。
    }
    cout<<h<<endl;//注意换行。
    return 0;
}
```


---

## 作者：孑然成愁 (赞：0)


大家好，我这个小学生第一次发题解，望dalao多多关照！

---------------------------------不怎么华丽的分割线---------------------------------

这道题，考的知识点就是排序。关于排序嘛，萌新们当然是用选排来打基础啦！今天我就来写一篇函数+选排的题（别以为函数是什么nb的东西，其实就是让程序更简洁而已）。

题目解析：求数组中前k大的数之和，可以先用选择排序将数组从大到小排序，然后依次累加就可以了。

贴代码：

```cpp
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<string>
using namespace std;
int n,k,a[100010],s;//定义。 
void input()//读入函数，void是执行类函数，既没有返回值。 
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
		cin>>a[i];
}
void pai()//排序函数。 
{
	for(int i=1;i<n;i++)
		for(int j=i+1;j<=n;j++)//循环变量不能错！
			if(a[i]<a[j])swap(a[i],a[j]);//如果前面比后面小，就交换，确保大数在前面。 
}
void ans()//确认答案函数，即累加器。 
{
	for(int i=1;i<=k;i++)
		s+=a[i];
}
void output()//输出函数 
{
	cout<<s;
	cout<<endl; 
}
int main()
{
	input();//读入
	pai();//排序
	ans();//累加
	output();//输出
	return 0;
} 
```

#### 岛国题目不换行，听取"WA"声一片

---

## 作者：zzhz (赞：0)

这题不难，先看下思路      
# 思路：     
1.输入      
2.排序      
3.累加前k个数            
4.输出     
下面看代码，代码如下：     
```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
int n,k,a[100001],ans=0;
int main(){//主函数
	cin>>n>>k;//输入
	for(int i=1;i<=n;i++){
		cin>>a[i];//输入
	}
	sort(a+1,a+1+n);//排序
	for(int i=n;i>=n-k+1;i--){//由于用的sort，所以从后面开始
		ans+=a[i];//累加
	}
	cout<<ans<<endl;//输出
	return 0;
}

```


---

## 作者：CZQ_King (赞：0)

## 这么小的数据范围居然没有桶排$?$


------------
思路：先桶排，再从后面往前找n个，注意，要等到桶空了之后变量才往前走。

------------
代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t[58],n,f,ans,d;
int main(){
	cin>>n>>d;
	for(int i=0;i<n;i++){
		cin>>f;
		t[f]++;//桶的第f个加上一
	}
	for(int i=50;i>=0;i--){//从后面往前找
		while(t[i]!=0&&d!=0){//直到桶空了或d为0
			t[i]--;//个数减一
			ans+=i;//千万不要加t[i]!!
			d--;
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：RE_Ripper (赞：0)

这一题相对来说比较简单   

（提醒一下来切AT的萌新，所有的AT要打换行！）
------------
~~对像我这样的蒟弱非常好~~   
这题要用到我们的sort函数，再读入后进行排序，前k个便是答案
代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
bool mmp(int a,int b)
{
return a>b;
}
int main()
{
   int n,k,ass=0;
   int a[51];
   cin>>n>>k;
   for(int i=1;i<=n;i++)
    {
   	cin>>a[i];
    }
	sort(a+1,a+n+1,mmp);
	for(int i=1;i<=k;i++)	
	{
		ass+=a[i];
	}
	cout<<ass<<endl;//endl换行
	return 0;
}
```

---

## 作者：Jinyeke (赞：0)

### 题目：输入n个数，输出前k大的数的总和
代码（1）顺着往下
```pascal
var
 a:array[1..100] of longint;
 i,j,t,n,k,m,s:longint;
begin
 readln(n,k);
 for i:=1 to n do read(a[i]);//输入
 for i:=1 to n-1 do 
  for j:=i+1 to n do 
   if a[i]<a[j] then //从大到小排序
    begin
     t:=a[i];
     a[i]:=a[j];
     a[j]:=t;
     end;
 for i:=1 to k do //1~k个大数推下去
 s:=s+a[i];//累加
 writeln(s);//输出（注意换行）
 end.
   
```
（2）pascal
逆推
```pascal
var
 a:array[1..100] of longint;
 i,j,t,n,k,m,s:longint;
begin
 readln(n,k);
 for i:=1 to n do read(a[i]);//输入
 for i:=1 to n-1 do 
  for j:=i+1 to n do 
   if a[i]>a[j] then //从小到大排序
    begin
     t:=a[i];
     a[i]:=a[j];
     a[j]:=t;
    end;
 for i:=n downto n-k+1 do //从第n个小数（其实就是第一大数）倒推到第n-k+1小数（最后一个大数）
 s:=s+a[i];//累加
 writeln(s);//输出（注意换行）
 end.
   
```
pascal while循环做法

  
```pascal
var
a:array[1..100] of longint;
i,j,t,n,k,m,s,sum:longint;
begin
readln(n,k);
for i:=1 to n do read(a[i]);//输入
for i:=1 to n-1 do 
for j:=i+1 to n do 
if a[i]>a[j] then //从小到大
 begin
  t:=a[i];
  a[i]:=a[j];
  a[j]:=t;
 end;
 while s<k do //数量没到
  begin
   sum:=sum+a[n];//累加目前最大的数
   n:=n-1;//n-1，在到次大的那个数
   inc(s);//累加数量
  end;
  writeln(sum);//输出（注意换行）
  end.
   
   
```
### 共建文明洛谷，请勿Ctrl+C！

---

## 作者：陈洋琛 (赞：0)

一道水题，直接将这n个数从大到小排序，然后输出前k大的数的总和就好了

这里我使用的是冒泡排序

直接献上代码：
~~~
#include <iostream>
using namespace std;
int main()
{
	int n,k,a[55],sum=0;
	cin>>n>>k;
	for(int i=0;i<n;i++) cin>>a[i]; //输入
	for(int i=0;i<n-1;i++)
		for(int j=i+1;j<n;j++)
			if(a[i]<a[j]) swap(a[i],a[j]); //将这n个数从大到小排序
	for(int i=0;i<k;i++) sum+=a[i]; //计算前k大的数的总和
	cout<<sum<<endl; //输出
	return 0; //结束程序
}
~~~

---

## 作者：Tomone (赞：0)

使用优先队列解决这个问题
```
#include<cstdio>
#include<iostream>
#include<queue>
#include<algorithm>
#include<vector>
using namespace std;

priority_queue<int, vector<int>, less<int> > q; //新建一个从大到小的优先队列

int main(){
	ios::sync_with_stdio(false); //读入读出优化
	int n,m,tmp,ans=0;
	cin>>n>>m;
	for(int i=0;i<n;++i){
		cin>>tmp;
		q.push(tmp); //入队
	}
	for(int i=0;i<m;++i){
		ans+=q.top(); //加前m个元素
		q.pop();
	}
	cout<<ans<<endl; //输出
	return 0;
}

```
一些优先队列的解析：https://www.aptx.xin/queue.html

---

## 作者：chengni (赞：0)


按照从大到小排序，找到最大的m个数，相加记录输出即可

```cpp
#include<bits/stdc++.h>

using namespace std;

int a[100000];

int main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	cin>>a[i];
	sort(a+1,a+n+1);
	int sum=0;
	for(int i=n;i>=n-m+1;i--)
	sum+=a[i];
	cout<<sum;
	return 0;
}
```

---

