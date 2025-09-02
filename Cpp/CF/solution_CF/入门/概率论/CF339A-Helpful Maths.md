# Helpful Maths

## 题目描述

Xenia the beginner mathematician is a third year student at elementary school. She is now learning the addition operation.

The teacher has written down the sum of multiple numbers. Pupils should calculate the sum. To make the calculation easier, the sum only contains numbers 1, 2 and 3. Still, that isn't enough for Xenia. She is only beginning to count, so she can calculate a sum only if the summands follow in non-decreasing order. For example, she can't calculate sum 1+3+2+1 but she can calculate sums 1+1+2 and 3+3.

You've got the sum that was written on the board. Rearrange the summans and print the sum in such a way that Xenia can calculate the sum.

## 样例 #1

### 输入

```
3+2+1
```

### 输出

```
1+2+3
```

## 样例 #2

### 输入

```
1+1+3+1+3
```

### 输出

```
1+1+1+3+3
```

## 样例 #3

### 输入

```
2
```

### 输出

```
2
```

# 题解

## 作者：Ofnoname (赞：7)

这么简单的题怎么没有人发题解呢？？

由于只有加法，所以可以直接读入数字。

排序后输出，带上符号。

C++代码：
```
#include <iostream>
#include <algorithm>
//提供sort函数 
#include <iomanip>
//提供输出符号，这里还有各种cout的复杂操作 
using namespace std;

int N,dat[100000];
//N是数据个数，dat是数据
//由于没有找到数据范围，就开100000 

int main()
{
	ios::sync_with_stdio(0);//cin,cout优化 
	cin>>dat[0];//第一个数没有+符号特判 
	while (cin>>dat[++N]);
	//无数据个数输入方法 
	sort(dat,dat+N+1);//排序 
	cout<<dat[0];//第一个数没有+符号特判
	cout<<setiosflags(ios::showpos);
	//该语句设置符号，以后的正数会自带+号 
	for (int i=1; i<=N; i++)
		cout<<' '<<dat[i];
	return 0;
}
```
PS：按理说输入时++N应该是N的值等于数据个数，但使用while(cin或scanf)型输入时，N都会多一个，所以后面的循环都写成``i<N``而不是``i<=N``，否则会多输出0，要深刻体验这一点，可以去做[P1020导弹拦截](https://www.luogu.org/problemnew/show/P1020)。











---

## 作者：PrincessQi (赞：5)

# 我看到这个题的第一眼就是想到排序
## 但是……
# TLE啊！！！！！！！！
以下是我的冒泡TLE排序程序：

```
#include<bits/stdc++.h>
using namespace std;
int i,j;
char s[105];
int main(){
    gets(s);//输入
    for(i=0;i<strlen(s)-2;i+=2)//+=2为了跳过加号
        for(j=i;j<strlen(s);j+=2)
            if(s[i]>s[j])swap(s[i],s[j]);//交换函数
    puts(s);//输出
    return 0;
}//千万别抄，会TLE的233
```
### 然后我看到了题目里说只有1，2，3三个数，于是我想到统计个数，然后输出
## 以下是我的统计数据输出的程序：
```
#include<bits/stdc++.h>
using namespace std;
int a[1001],i,j,m;
char c;
int main(){
    while(c!='\n'){\\当程序没有输入结束时
        scanf("%c",&c);\\输入
        if(c=='1'||c=='2'||c=='3'){\\当输入是数字时
            a[c-'0']++;\\统计
            m=max(m,c-'0');\\选取输入的数中最大的
        }
    }
    for(i=1;i<=3;i++)
        for(j=1;j<=a[i];j++){
            printf("%d",i);\\输出
            if(i!=m||j!=a[i])printf("+");\\输出加号
        }
    return 0;
}
```


---

## 作者：Konjaku_百分百 (赞：4)

```cpp
#include<bits/stdc++.h>
using namespace std;
int x[100005],y;//定义一个数组和计数器
string s;//定义一个字符串
int main()
{
 //freopen(".in","r",stdin);
 //freopen(".out","w",stdout);
 cin>>s;//输入一个字符串
 for(int i=0; i<s.size(); i++)//循环
     if(s[i]!='+') x[++y]=s[i]-'0';//如果s[i]是数字时，那就用数组来存数字
 sort(x+1,x+y+1);//排序
 for(int i=1; i<y; i++)//循环
  	 cout<<x[i]<<'+';//输出从小到大的数组，然后再输出加号
 cout<<x[y];//输出最后的数组，如果在循环里面输出的话，就会输出多一个加号，当然，聪明人会直接一个循环输出
 return 0;//结束程序
}
```

---

## 作者：一滴小水滴 (赞：2)

### 这道题我们可以直接用C++STL优先队列来做。

首先给大家普及一下整型优先队列的相关知识：

升序优先队列：priority_queue<int,vector<int>,greater<int> > q;
  
降序优先队列：priority_queue<int,vector<int>,less<int> > q;
  
优先队列的一些简易操作：

获取队首元素：q.top();
  
获取队列长度：q.size();
  
在队首增加元素：q.push(int x);
  
弹出队首元素：q.pop();

### 那么既然有了优先队列，这道题做起来就很容易了。
因为只有1、2、3 这三个数字，所以只要碰到了数字，就把它加入队列。
  
```cpp
for(int i=0;i<s.size();i++)
	if(s[i]>='0'&&s[i]<='9')q.push(s[i]-'0');
                //只要碰到了数字，就把这个数字放到优先队列中。
                                     
```
                                         
然后再将其全部输出就可以啦。
                                     
```cpp                                      
while(q.size()>1)
{
	cout<<q.top()<<'+';
	q.pop();
}
cout<<q.top();

```
  
所有的重点都已经讲完了，那我们还是照旧附上完整代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	priority_queue<int,vector<int>,greater<int> >q;
	string s;
	getline(cin,s);
	for(int i=0;i<s.size();i++)
		if(s[i]>='0'&&s[i]<='9')q.push(s[i]-'0');
	while(q.size()>1)
	{
		cout<<q.top()<<'+';
		q.pop();
	}
	cout<<q.top();
	return 0;
}
```

## 优先队列是个好东西，大家可以多用用哦。

---

## 作者：EthanWu (赞：2)

# 其实这题很简单 

### ~~但我会告诉你我提交了6次才AC吗？！~~

### ~~我更不会告诉你第一次还是UKE~~


 **好吧，其实是前几次没考虑周全才导致某些点不对**
 
 dalao们用排序操作……~~本蒟蒻就用简单点的方法吧~~
 
 就是统计"+" "1" "2" "3"的个数（数字只有1,2,3），然后……在注释里说吧 
 ### 代码
 
~~听说抄题解会CE~~

```cpp
#include<cstdio>
#include<iostream>
#include<cmath>
#include<string>
#include<cstring>
#include<queue>
#include<stack>
#include<map>
#include<list>
#include<deque>
#include<climits>
#include<algorithm>
#include<cstdlib>//常规头文件
using namespace std;

string a；//字符串
int jia=0,one=0,two=0,three=0;//分别统计“+”“1”“2”“3”的个数，全局变量不写（=0）默认也是0.
int rp=0,ha=0,la=0;

int mian()
{
	cin>>a;//输入字符串
	int len=a.length();//长度
	for(int i=0;i<len;i++)
	{
		if(a[i]=='+')//如果是“+”
		{
			jia++;//jia（统计加号数量）就加一；下面也一样
		}
		if(a[i]=='1')
		{
			one++;
		}
		if(a[i]=='2')
		{
			two++;
		}
		if(a[i]=='3')
		{
			three++;
		}
	}	
	if((jia==0)||((two==0)&&(three==0))||((one==0)&&(two==0))||((one==0)&&(three==0)))//当时我就是因为这里没考虑周全而没AC的……QWQ如果没有加号或只有一种数字
	{
		cout<<a<<endl;//直接输出就行了
		return 0;
	}
	else//否则
	{
		while(rp<one-1)从0到“1”的数量-1
        {
			cout<<"1"<<"+";//输出“1”和“+”
			rp++;			
		}
		if((two!=0||three!=0)&&(one!=0))//如果“1”的个数不为0并且有“2”或“3”
		{
			cout<<"1+";//输出“1+”
		}
		else if(two==0&&three==0)//如果后面没有2和3
		{
			cout<<"1";//只输出“1”，不能有加号了。（其实我觉得这里和上面判断那里有点重复，但我懒得改了QWQ）
		}
		while(ha<two-1)从0到“2”的数量-1
		{
			cout<<"2"<<"+";//输出“2”和“+”
			ha++;			
		}
		if(three!=0&&two!=0)//如果有“2”并且后面有“3”
		{
			cout<<"2+";//输出“2+”
		}
		else if(three==0&&two!=0)//如果有“2”并且后面没有“3”了
		{
			cout<<"2";//也是一样，不能有加号了
		}
		while(la<three-1)从0到3的数量-1
		{
			cout<<"3"<<"+";//输出“3”和“+”
			la++;			
		}
		if(three!=0)//如果有“3”
		{
			cout<<"3";输出“3”
		}
	}
	return 0;//愉快地结束了
}
```
 
### 本蒟蒻第五篇题解祭~~虽然只通过了2篇~~

---

## 作者：AC机 (赞：0)

这题其实很水的…………因为最近在学习新语法，所以代码是纯的c++11。
我们废话不多说直接看代码，有详细注释。
```cpp
#include<stdio.h>
#include<cctype>
#include<algorithm>
#include<cstring>
#include<vector>
#include<iostream>
using namespace std;
char ch;
vector<int>a;//懒得看数据范围了，直接开vector
int main ()
{
	while(cin>>ch//并没有说明输入个数，用cin会读到最后一个自动停止)
	{
		if(isdigit(ch)//如果是数字放到a数组中) a.push_back(ch-'0');
	}
	sort(a.begin(),a.end());//先排个序
	printf("%d",a.front());//对第一数进行特殊处理
	a.erase(a.begin());//输出完第一个数后删除掉第一个数
	for(auto iter : a//c++11新语法遍历迭代器.具体可以参考https://www.luogu.org/blog/64456/ni-fou-zhi-dao-di-c-yu-fa)
	{
		printf("+%d",iter);//在输出的数前面加上'+'
	}
	return 0;
}
```

---

## 作者：不到前10不改名 (赞：0)

//这题果然是细节题！！！
```
#include<stdio.h>
#include<string.h>
int i,srx[4],t;
char sry[1001];
int main()
{
    gets(sry);//while输入多麻烦啊！反正字符都在一行，gets就是了!(scanf也可以)
    for(i=0;i<strlen(sry);i++)
    {if(sry[i]=='1')
    srx[1]++;//记录每个数字的出现个数，反正就三个数字
    else if(sry[i]=='2')
    srx[2]++;
    else if(sry[i]=='3')
    srx[3]++;}
    if(srx[2]==0&&srx[3]==0)//只有1，末尾是1
    t=1;
    else if(srx[3]==0)//只有1和2，末尾是2
    t=2;
    else//都有，末尾是3
    t=3;//这里是在判断最后一个输出的数是几，因为最后一个数后面没有+号了
    for(i=1;i<=3;i++)
    {while(srx[i])
    {if(t==i&&srx[i]==1)//退出
    break;
    srx[i]--;
    printf("%d+",i);}}
    printf("%d",t);//去除加号
    return 0;
}
```

---

## 作者：开心的猪 (赞：0)

。。。这道题只需要把所有的数字都读入后排一下序就行了，输出时在做除了末尾以外每一个数字后都加上一个+。在代码中还会有其他解释。

以下是代码：

```
#include<bits/stdc++.h>

using namespace std;

int main()
{
	int ans;
	int alpha[100]={0};
	char temp;
	for(int i=0; i<=100; i++)
	{
		scanf("%d%c", &alpha[i], &temp);
		ans=i;//统计数字个数
		if(temp=='\n')
		{
			break;//结束读入（如果没结束这里应该是个+号）
		}
	}
	sort(alpha, alpha+ans+1);//排序
	for(int i=0; i<ans; i++)//由于ans是最后一个数字的下标，所以对最后一个数字要特殊处理（不输出“+”）
	{
		printf("%d+", alpha[i]);
	}
	printf("%d", alpha[ans]);
	return 0;
}
```


---

## 作者：开心的猪 (赞：0)

首先读入数组。每读一个数字，都再读一个字符。如果那个字符是换行符，就结束读入。然后sort一下数组，从小到大依序输出。

下面是代码。

```cpp
#include<bits/stdc++.h>

int main()
{
	int a, b, c;
	scanf("%d%d%d", &a, &b, &c);
	int alpha=sqrt((double)a*b/c)+sqrt((double)c*a/b)+sqrt((double)b*c/a);
	printf("%d", 4*alpha);
	return 0;
}
```


---

## 作者：Obito (赞：0)

# 排序

这题想明白了真不难，把数字放到数组中，排序输出就行了！

```
#include<bits/stdc++.h>
using namespace std;
char s;
int i,j,k,n,m,a[10001],ans;//变量定义
int main(){
	int i=1;//i从一开始，记录一共有几个数
	cin>>n;//先输入一个数
	a[i]=n;
	while(cin>>s>>n){//我们可以把输入看成先输入一个数，再一个数+一个加号输入
	i++;//记录量++	
	a[i]=n;//存储
	}
	sort(a+1,a+1+i);//排序
	for(j=1;j<i;j++)//一个数带一个加号输出。
	cout<<a[j]<<"+";
	cout<<a[i]<<endl;//输出最后一个数，换行保平安。
	return 0;//完美结束
}

```
一个方法，非喜勿喷。谢谢。

---

