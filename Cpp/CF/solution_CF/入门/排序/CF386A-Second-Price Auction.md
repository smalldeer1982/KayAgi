# Second-Price Auction

## 题目描述

In this problem we consider a special type of an auction, which is called the second-price auction. As in regular auction $ n $ bidders place a bid which is price a bidder ready to pay. The auction is closed, that is, each bidder secretly informs the organizer of the auction price he is willing to pay. After that, the auction winner is the participant who offered the highest price. However, he pay not the price he offers, but the highest price among the offers of other participants (hence the name: the second-price auction).

Write a program that reads prices offered by bidders and finds the winner and the price he will pay. Consider that all of the offered prices are different.

## 样例 #1

### 输入

```
2
5 7
```

### 输出

```
2 5
```

## 样例 #2

### 输入

```
3
10 2 8
```

### 输出

```
1 8
```

## 样例 #3

### 输入

```
6
3 8 2 9 4 14
```

### 输出

```
6 9
```

# 题解

## 作者：Sai0511 (赞：4)

**此题的感想**：此题难度为**提高+/省选-**，描述又如此简单，我顿时傻眼了，于是我就去看了看数据范围：2<=n<=1000，顿时感觉自己又A了道水题，~~事后才发现这题如此毒瘤~~ 

### 我一开始的思路：
#### ①:存储思想：            

开三个变量，$maxn,maxb,second$。其中$maxn$表示当前范围内的最大值，$maxb$表示当前范围内最大值的编号，$second$表示当前范围内第二大的值.        

#### ②:主要算法
一边输入一边统计，每次更新最大值以及最大值的编号。**需要注意的是，当更新第二大的值的时候，最大值的编号不能为当前数值的编号，如果仅仅判断最大值为当前值的话，碰到与最大值一样的数，也会被忽略掉。**
### 这样乍看是正确的，其实不然。我后面会跟大家讲。
不管怎样，先看看代码再说：         
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,maxn=-1,maxb,second,i,j,a,b;
bool isnumber(char c){//判断一个数是否为整数，辅助快读
	if(c>='0'&&c<='9') return 1;
	else return 0;
}
inline int read(){//我有快读快写综合征，此为快读
	int x=0,f=1;
	char c=getchar();
	while(!isnumber(c)){
		if(c=='-') f=-1;
		c=getchar();
	}  
	while(isnumber(c)) x=x*10+c-48,c=getchar();
	return x*f;
}
inline void write(int x){//快速输出（快写）
	if(x<0) x=-x,putchar('-');
	if(x/10>0) write(x/10);
	putchar(x%10+48);
	return;
}
int main(){
	n=read();//输入
	for(i=1;i<=n;i++){
		x=read();//输入
		if(x>maxn){//如果当前值大于最大值
			maxn=x;//更新最大值
			maxb=i;//更新最大值的编号
		}
		if(x>second&&i!=maxb) second=x;
       //若当前值大于第二大的值且当前编号不是最大值时，更新第二大值
	}
	write(maxb);//输出
	putchar(' ');
	write(second);//输出
}
```
### 然而，这样做连样例都过不去，第一个点就被卡了。 
        
        
为什么呢？我们举个例子，如果一个数列第一个元素为第二大的值，那么一开始最大值就会更新为第一个元素，而第二大的值就不会接收到这个元素，于是乎，就会出错。

### 所以，我们来讲讲正确的思路：          
既然不能一边做一边解决，我们就不妨开个结构体数组。   

**该结构体存储的有两个变量:wz,val**  其中,wz表示的是该元素**原始的坐标**，val表示此元素的值。那么我们就可以对这个数组的值进行从大到小排序，之后输出最大的值得编号和第二大的值。        

### 话不多说，看代码。   
```cpp
#include<bits/stdc++.h>
#define MAXN 1010  //定义最大值
using namespace std;
int n,i,j;
struct Node{//定义结构体
	int wz,val;
};
Node a[MAXN];//申明变量
bool isnumber(char c){//判断是否为整数，辅助快读
	if(c>='0'&&c<='9') return 1;
	else return 0;
}
inline int read(){//快速输入
	int x=0,f=1;
	char c=getchar();
	while(!isnumber(c)){
		if(c=='-') f=-1;
		c=getchar();
	}  
	while(isnumber(c)) x=x*10+c-48,c=getchar();
	return x*f;
}
inline void write(int x){//快速输出
	if(x<0) x=-x,putchar('-');
	if(x/10>0) write(x/10);
	putchar(x%10+48);
	return;
}
bool cmp(Node a,Node b){
	return a.val>b.val;
    // 用于sort比较
}
int main(){
	n=read();//输入
	for(i=1;i<=n;i++) a[i].val=read(),a[i].wz=i;//输入元素，把元素初始位置读入a数组
	sort(a+1,a+n+1,cmp);//排序
	write(a[1].wz);//输出
	putchar(' ');
	write(a[2].val);//输出
	return 0;//结束程序
}
```


---

## 作者：zjh111111 (赞：4)

## 这题提高+/省选-的难度是假的别被吓到！

## 本人写一发O(n)+无数组在线的题解(简洁版)

##### ~~先双手呈上代码~~

c++：

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
  int n,x,Ms=-1e9,Mx,Ss;
  scanf("%d",&n);
  for (register int i=1; i<=n; i++)
    {
      scanf("%d",&x);
      if (x>Ms)
        {
          Mx=i; Ss=Ms; Ms=x;
        }
      if (x>Ss && x<Ms) Ss=x;
    }
  printf("%d %d",Mx,Ss);
  return 0;
}
```
pascal：
```
var
  n,i,x,Ms,Mx,Ss:longint;
begin
  Ms:=-maxlongint;
  read(n);
  for i:=1 to n do
    begin
      read(x);
      if x>Ms then
        begin
          Mx:=i; Ss:=Ms; Ms:=x;
        end;
      if (x>Ss) and (x<Ms) then Ss:=x;
    end;
  write(Mx,' ',Ss);
end.
```
#### 重点来了，~~咚咚咚敲黑板~~
## 【思路】

为了题解简洁

#### 把最大值设为Ms，最大值编号设为Mx，次大值设为Ss，当前读进去的值为x (同程序中) ，次大值编号设为Sx。

### 我们可以把最终答案分两种情况

1. ### Mx<Sx
1. ### Sx<Mx

#### 也就是说考虑次大值在最大值左边还是右边这两种情况

##### 这样子题目就变得十分简单了

先考虑情况1(即最大值在次大值左边)

- ### 从编号1~Mx都没问题，就直接跟最大值打擂台

- ### 接下去也不难想象，当x<Ms且x>目前的次大值时将目前次大值更新为x

再考虑情况2(即最大值在次大值右边)

- ### 从1~Sx打擂台没问题

- ### Sx后就要处理一下，每当x>Ms(目前最大值)时都要更新Ss(目前次大值)为当前最大值。稍微举个例子试一试就知道了。

~~既然所有情况都考虑完全了，那岂不是程序唾手可得？~~

### 由于我们并不知道是哪种情况(1 or 2)，所以都处理进去就可以了

#### 题解就到这了，提醒大家：尽管代码短但是还请大家不要复制粘贴，理解后再自己码出来

##### 宣传一下[我的博客](https://www.luogu.org/blog/zjh--rill7747/#)，~~虽然里面没有多少题解~~

如有不懂私信或加QQ：2242579009

#### 欢迎打扰前来查错拍砖！

---

## 作者：hzx1 (赞：3)

好~~水~~难

思路很~~简单~~复杂

开个数组然后排序就行咯
```cpp
#include<iostream>
#include<algorithm>  //懒，用sort排序，sort头文件
using namespace std;
int main(){
	int n,i,a[10001],k,maxn;
	cin>>n;                   //输入
	for(i=1;i<=n;i++)
		cin>>a[i];
		maxn=a[1];   //记得初始化
		k=1;        //同上
		for(i=2;i<=n;i++)  //从第2个位置开始
		if(a[i]>maxn){     //如果后面的数大于a[1]
			maxn=a[i];     //赋值
			k=i;           //记下i的位置
		}
		cout<<k<<" ";      //输出最大数的位置
	sort(a+1,a+n+1);       //sort排序
	cout<<a[n-1]<<endl;    // 输出第2大的数
	return 0;              //结束
} 
```
祝各位AC…

---

## 作者：huyang2007 (赞：1)

##### 本蒟蒻发第一篇题解

##### 写法比较简单：

先定义一个结构体，一个表示数字，一个表示编号。

然后将他们按数字从大到小排序，最后直接输出第一名的编号和第二名的数就行了。

~~我也不会多说什么~~

看代码：
```
#include<bits/stdc++.h>//万能头文件
using namespace std;
struct node{
    int t,s;
}a[10001];//定义一个结构体，s是数字，t是编号
int n;
int cmp(node x,node y){
    return x.s>y.s;
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i].s;
        a[i].t=i;
    }
    sort(a+1,a+1+n,cmp);//sort快速排序
    cout<<a[1].t<<" "<<a[2].s;
    return 0;//结束程序
}
```
### 蒟蒻代码，大佬勿喷！！！

---

## 作者：climax (赞：1)

这题很简单，数据范围又小，又容易。只需个每个数编个号，然后再进行冒泡排序就可以了。

上代码：
```
#include<bits/stdc++.h>
using namespace std;
int a[100001],b[100001];
int main()
{
  int n,j,i,o;
  cin>>n;//输入
  for(i=1;i<=n;i++)	
  {
  	cin>>a[i];//输入每个数
  	b[i]=i;//给这个输入的数编号  
  }
  for(i=1;i<=n;i++)//冒泡排序，由于数据范围很小，所以不要担心超时这个问题
     for(j=i;j<=n;j++)
       if(a[i]<a[j])
       {
       	  o=a[i];
       	  a[i]=a[j];
       	  a[j]=o;
       	  o=b[i];
       	  b[i]=b[j];
       	  b[j]=o;
	   }
  cout<<b[1]<<' '<<a[2];//最后就只需按照题目要求输出最大的那个数的编号，和第二大的数的数值就可以了。
  return 0;//结束。
}
```

---

## 作者：luowa (赞：1)

看水题被评为noip+，我深感悲痛，给了个入门难度拯救一下，并决定来水一下题解。

首先题意据某大佬说“求最大值的下标，次大值的数值”，于是我们可以对数据进行sort快排（不会sort的可以问学长或者问度娘），并输出要求的数值。

直接上代码，入门难度就不注释了。

```c
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
struct number
{
	int xiabiao;
	int dota;
}w[9999999];
bool cmp(number a,number b)
{
	if(a.dota==b.dota)	return a.xiabiao>b.xiabiao;
	return a.dota>b.dota;
}
int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
		scanf("%d",&w[i].dota);
		w[i].xiabiao=i;
    }
    sort(w+1,w+n+1,cmp);
    cout<<w[1].xiabiao<<' '<<w[2].dota;
	return 0;
}
```

---

## 作者：YZ_hang (赞：0)

## 较经典的冒泡排序题

~~看到简短的题目描述，断定这是一道水题（确实是水色的）~~

有的蒟蒻看到这题一定很高兴，然后~~很偷懒~~很自然地想到了sort，就开始敲代码

然而敲到一半会发现，**光用sort很难解决编号的问题**

于是乎，还是老老实实敲冒泡吧

不得不说，冒泡倒是确实要用，但这概率论好像和这题没啥关系吧

开一个数组存储a[i]的编号就可以解决编号的问题了

```
#include<iostream>
#include<cstdio>
using namespace std;
int a[1001],b[1001],n;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		b[i]=i;//b[i]用来存储每个a[i]的编号，也就是位置
	}
	bool p=false; //这是用来优化冒泡排序的
	for(int i=1;i<=n;i++){//优化过的冒泡排序部分（核心代码）
		for(int j=i+1;j<=n;j++)
		if(a[i]>=a[j]){//这里决定了排序是从小到大还是从大到小，我这里是从小到大
			swap(a[i],a[j]);//这里是原本的冒泡方法，很好理解
			swap(b[i],b[j]);//当两个a需要交换时，将编号也随之交换，这样就保证每个a对应的b保持不变
            p=true;
        }
        if(p==false)break;
	}
	printf("%d %d\n",b[n],a[n-1]);//输出第一大的编号和第二大的值
	return 0;
}
```
~~自我感觉比较短~~

比较易懂，而且数据再大点的话把数组开大就行了，毕竟是优化过的

这种方法可以得到每一个数的排序和对应编号，比较推荐

---

## 作者：Goldbach (赞：0)

本蒟蒻发现其他的题解处理编号的方法都是迭代诶

而我瞄了一眼数据范围和时间限制，没必要用快排

于是我果断地打了一个冒泡排序的代码

并且用一个数组存编号

就好办了
```cpp
#include<bits/stdc++.h>//简洁的万能头
using namespace std;
int n,a[1005],a1[1005];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		a1[i]=i;//用a1数组存编号
	}
    //冒泡排序
	for(int i=1;i<n;i++){
		for(int j=i+1;j<=n;j++){
			if(a[i]>a[j]){
				swap(a[i],a[j]);//swap是交换两数的函数
				swap(a1[i],a1[j]);
			}
		}
	}
	cout<<a1[n]<<' '<<a[n-1];
	return 0;
}
```


---

## 作者：BCZSX (赞：0)

~~突然发现这又是一道恶意评分的题~~这其实就是一道排序题嘛！！！~~不~~具体的讲解看代码。
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
struct node//结构体
{
    int a,num;//a存储数值，num存储原始序号
};
node k[1100];
int n;
inline cmp(node x,node y)//排序方式
{
    return x.a<y.a;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&k[i].a),k[i].num=i;//读入数值，序号赋值
    sort(k+1,k+1+n,cmp);//排序
    printf("%d %d",k[n].num,k[n-1].a);//输出最大值的编号和第二大数的值
    return 0;//完美结束
}
```

---

## 作者：DreamShadow (赞：0)

```pascal
var
  a,b:array[0..1000]of longint;//数组元素故意将他们的下界作为0，方便使用，同下面排序
  i,j,n:longint;
 begin
   readln(n);
   for i:=1 to n do
   begin
     read(a[i]);
     b[i]:=i;//b数组作为编号
   end;
   for i:=1 to n-1 do//基本原理，在这不多说
    for j:=n downto i+1 do
    if a[i]<a[j] then//注意，千万别做成从小到大排，因为要和输出对应
    begin
      a[0]:=a[i];a[i]:=a[j];a[j]:=a[0];//这边a[0]就相当与一个暂时的储存器(插入排序有类似)
      b[0]:=b[i];b[i]:=b[j];b[j]:=b[0];//同上
    end;
    writeln(b[1],' ',a[2]);//千万别被题目坑了，第一个是最大数的【编号】！！！，而第二大的数是输出数值，
    //(另起一行)b[1]随着最大数a[1]的编号，而a[2]是第二大的数，输出就OK\(≧▽≦)/
 end.

```

---

## 作者：政凯 (赞：0)

  这道题，就是让我们求出最大数的位置和第二大数的数值
  
  怎么求最大数位置？可边输入，边判断：如果那个数大于最大值，最大值为那个数，最大的位置为那个数的位置
  
  怎么求第二大数的数值？可排序（从小到大），输出第n-1个数（就是第二大的数）

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int n,max1,maxi,a[1000000+5];
int main()
{
	cin>>n;
	for (int i=1;i<=n;i++)
    {
    	scanf("%d",&a[i]);
    	if (a[i]>max1) max1=a[i],maxi=i;//如果那个数大于最大值，最大值为那个数，最大的位置为那个数的位置
    }
    sort(a+1,a+1+n);//排序（从小到大）
    cout<<maxi<<" "<<a[n-1];
	return 0;
}
```


---

