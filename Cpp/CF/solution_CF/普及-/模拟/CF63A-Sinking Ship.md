# Sinking Ship

## 题目描述

The ship crashed into a reef and is sinking. Now the entire crew must be evacuated. All $ n $ crew members have already lined up in a row (for convenience let's label them all from left to right with positive integers from 1 to $ n $ ) and await further instructions. However, one should evacuate the crew properly, in a strict order. Specifically:

The first crew members to leave the ship are rats. Then women and children (both groups have the same priority) leave the ship. After that all men are evacuated from the ship. The captain leaves the sinking ship last.

If we cannot determine exactly who should leave the ship first for any two members of the crew by the rules from the previous paragraph, then the one who stands to the left in the line leaves the ship first (or in other words, the one whose number in the line is less).

For each crew member we know his status as a crew member, and also his name. All crew members have different names. Determine the order in which to evacuate the crew.

## 样例 #1

### 输入

```
6
Jack captain
Alice woman
Charlie man
Teddy rat
Bob child
Julia woman
```

### 输出

```
Teddy
Alice
Bob
Julia
Charlie
Jack
```

# 题解

## 作者：Andysun06 (赞：10)

## CF63A 题解
### 一. 题目分析：
首先，看到题目，我们就知道，一共有n个人，有四个等级，分别是：  
1. 老鼠(rat)
1. 妇女(woman)和儿童(child)
1. 男人（man）
1. 船长（captain）

### 二. 题目难度：
- 个人认为在 普及- 难度左右

当船沉时，需要按照这四个等级依次下船，如果等级相同，则按照序号，小的先下船。
### 三. 做法分析：
因为每个人的姓名和身份输入时，就是按顺序的，所以我们可以不用特意用sort来给他们排序，也不用结构体，就用字符串数组记录每个人的姓名和身份就可以了。

#### 第一阶段：
输入每个人的姓名和身份后，就要思考如何去模拟，因为我们知道有分四个等级，先是老鼠（rat）又因为输入时就是按照序号顺序排列的，我们就可以先不管序号，直接从 $1$ 一直搜到 $n$ 如果是 $rat$ 就直接输出他的名字。

代码：
```cpp

for(i=1;i<=n;++i){ // 从 1 一直搜到 n
   if(b[i]=="rat") //判断是否是 rat
     cout<<a[i]<<endl;  //是的话直接输出
	}
    
```
#### 第二阶段：
继续从 $1$ 一直搜到 $n$ 如果有妇女(woman)或小孩(child)，就像第一阶段一样直接输出。

代码：
```cpp
for(i=1;i<=n;++i){
  if(b[i]=="woman"||b[i]=="child") //判断是否是妇女或小孩
    cout<<a[i]<<endl;
}
```
#### 第三四阶段：
通过上面的分析，我们也很容易得出第三四阶段的代码，如下：
```cpp
for(i=1;i<=n;++i){
  if(b[i]=="man") //判断是否是男人
    cout<<a[i]<<endl;
}
for(i=1;i<=n;++i){
  if(b[i]=="captain") //判断是否是船长
    cout<<a[i]<<endl;
}
```
我们已经知道了各个阶段该怎么写了，只要把上面的代码合起来，就可以AC这道题了，具体如下：
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<map>
using namespace std;
string a[102],b[102];
int i;
int main(){
    int n;
    scanf("%d",&n);
    for(i=1;i<=n;++i){
    	cin>>a[i]>>b[i];
    }
    for(i=1;i<=n;++i){ // 从 1 一直搜到 n
        if(b[i]=="rat") //判断是否是 rat
	    cout<<a[i]<<endl; //是的话直接输出
    }
    for(i=1;i<=n;++i){
        if(b[i]=="woman"||b[i]=="child") //判断是否是妇女或小孩
            cout<<a[i]<<endl;
    }
    for(i=1;i<=n;++i){
        if(b[i]=="man") //判断是否是男人
            cout<<a[i]<<endl;
    }
    for(i=1;i<=n;++i){
        if(b[i]=="captain") //判断是否是船长
            cout<<a[i]<<endl;
    }
}
}
```
希望本题解可以给大家一点帮助，也感谢管理员在百忙之中为我审核，谢谢。

---

## 作者：666DHG (赞：4)

这道题是真的水，本地没测还一次过

其实可以用结构体数组来模拟，但是用优先队列
```priority_queue```
会更方便

我的思路如下：

1. 先用
```map```来预处理优先级（不会
```map```
的同学[看过来](http://www.cplusplus.com/reference/map/map/?kw=map)）

2. 把信息存入一个结构体
```Data```
，并将其加入到优先队列当中

3. 由于加入到优先队列后相当于自动排序，所以可以直接输出

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;

int n;
string name,type;
map <string,int> M;

struct Data
  {
  	int num,prio;
	string name;
	bool operator < (const Data &a) const //优先队列中每个元素的排序 
	  {
	  	if(a.prio!=prio) return a.prio<prio; //先判断优先级 
	  	return a.num<num; //再判断序号 
	  }
  }k;

priority_queue <Data> Q;

int main()
  {
  	ios::sync_with_stdio(false);
  	cin.tie(0);
  	//接下来用 map 来处理优先级 
  	M["rat"]=1;
  	M["woman"]=M["child"]=2;
  	M["man"]=3;
  	M["captain"]=4;
  	cin>>n;
  	for (int i=1;i<=n;i++)
  	  {
  	  	cin>>name>>type;
  	  	Q.push((Data){i,M[type],name}); //插入时就已经在排序了 
	  }
	while (!Q.empty()) //由于会自动排序，所以可以直接输出 
	  {
	  	cout<<Q.top().name<<"\n";
	  	Q.pop();
	  }
	return 0;
  }
```

---

## 作者：追风少年σχ (赞：2)

### 本题是比较基础的字符串结构体排序
排序遵循以下几点：

1.首先将乘客类型放在第一位，可以将字符串转化为数字,变成结构体的一个变量type：(以我的程序为例)

   乘客类型s------>type
   
   "rat"------>0
   
   "woman"&&"child"------>1
   
   "man"------>2
   
   "captain"------>3
   
2.结构体记录下乘客的name和num(标号)

3.写个cmp先按type从小到大排序,若相同再按num从小到大排序

最后sort一下按顺序输出即可

##### 贴上AC程序(shu):
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{//结构体
    string name;
    int type,num;
}a[101];
bool cmp(node p,node q){//按上面讲的排序方式
    if(p.type==q.type) return p.num<q.num;
    else return p.type<q.type;
}
int f(string s){//字符串型的乘客类型转化为这个乘客的type
    if(s=="rat")return 0;
    if(s=="child"||s=="woman")return 1;
    if(s=="man")return 2;
    return 3;
}
int main(){
    int n;
    string s;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        cin>>a[i].name>>s;
        a[i].type=f(s);
        a[i].num=i;
    }
    sort(a+1,a+1+n,cmp);
    for(int i=1;i<=n;i++)
        cout<<a[i].name<<endl;
    return 0;
}
```
写的挺轻(xin)松(ku)的

~~蒟蒻题解求过啊！！！~~
  

---

## 作者：chufuzhe (赞：1)

#### 题意：
一批人撤离，每个身份都有自己的优先性，优先性相同的则标号小的先撤离，给出每个人的身份和名字，要按撤离的顺序打印他们的名字。
#### 思路：
要按撤离的顺序打印他们的名字，就需要按他们的优先性来分成4组，每组里面标号小的在前面，最后从前到后输出每个组的名字。在分组的过程中，我们可以用vector动态数组来实现。
#### 实现：
（1）输入。

（2）将名字放入对应他们优先性的动态数组中。

（3）从前到后输出每个组的名字。
#### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
vector<string> v[4]; //定义4个动态数组
int main()
{
	ios::sync_with_stdio(false); //输入输出优化流
	int n; //表示总人数
	string a,b; //分别表示身份及名字
	cin>>n; //输入
	while(n--) //循环
	{
		cin>>a>>b; //输入
		a+='\n'; //换行
		//分组统计
		if(b=="rat") v[0].push_back(a); //优先性第一的老鼠
		if(b=="woman"||b=="child") v[1].push_back(a);//优先性第二的妇女儿童
		if(b=="man") v[2].push_back(a); //优先性第三的男人
		if(b=="captain") v[3].push_back(a); //优先性第四的船长
	}
	for(register int i=0;i<4;i++) //循环每种优先性的动态数组
		for(register int j=0;j<v[i].size();j++) //便利优先性第i+1的动态数组
			for(register int k=0;k<v[i][j].size();k++) //快输
				putchar(v[i][j][k]);
	return 0;
}
```


---

## 作者：Oscar12345 (赞：1)

嗯，水题 _*1_ ；
仅仅是一道有关排序和字符串的题目，难度min

```
#include<iostream>
using namespace std;

int main()
{
	int n,i,a[105],j;
	string s[105],t;
	cin>>n;
	for(i=0;i<n;i++)
	{
		cin>>s[i]>>t;
		if(t=="rat") a[i]=0;
		else if(t=="child" || t=="woman") a[i]=1;
		else if(t=="captain") a[i]=3;
		else a[i]=2;
	}
	
	for(j=0;j<=3;j++)
	{
		for(i=0;i<n;i++)
		{
			if(a[i]==j)
			{
				cout<<s[i]<<endl;
			}
		}
	}
	return 0;
}
```

---

## 作者：hensier (赞：0)

这道题考察了$struct+STL:sort$用法（~~虽然有些大佬使用高端的map~~）。

我们可以按照等级划分：

|$\text{等级}$|$\text{类型}$|
| :----------: | :----------: |
|$1$|$\text{rat}$|
|$2$|$\text{woman/child}$|
|$3$|$\text{man}$|
|$4$|$\text{captain}$|

这种判断方法可以用$if+else\text{ }if+else$进行判断，然后标记一个$grade$，再配置一个$compare$函数，并直接快排。

$AC$代码：

```cpp
#include<bits/stdc++.h>//万能头文件
#define f()for(int i=1;i<=n;i++)//更加方便
using namespace std;
int n;
string type;
struct passenger
{
    string name;
    int id,grade;
}p[101];
bool cmp(passenger a,passenger b)
{
    if(a.grade!=b.grade)return a.grade<b.grade;
    return a.id<b.id;
}
int main()
{
    ios::sync_with_stdio(0);//关同步，省时间
    cin>>n;//输入
    f()
    {
        p[i].id=i;//id标记
        cin>>p[i].name>>type;//输入名字和一个字符串
        if(type=="rat")p[i].grade=1;
        else if(type=="man")p[i].grade=3;
        else if(type=="captain")p[i].grade=4;
        else p[i].grade=2;//对字符串对应的类型进行讨论
    }
    sort(p+1,p+n+1,cmp);//快排
    f()cout<<p[i].name<<endl;//输出
}
```

---

