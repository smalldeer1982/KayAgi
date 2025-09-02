# [USACO18DEC] Mixing Milk B

## 题目描述

农业，尤其是生产牛奶，是一个竞争激烈的行业。Farmer John 发现如果他不在牛奶生产工艺上有所创新，他的乳制品生意可能就会受到重创！

幸运的是，Farmer John 想出了一个好主意。他的三头获奖的乳牛，Bessie、Elsie 和 Mildred，各自产奶的口味有些许不同，他打算混合这三种牛奶调制出完美的口味。

为了混合这三种不同的牛奶，他拿来三个桶，其中分别装有三头奶牛所产的奶。这些桶可能有不同的容积，也可能并没有完全装满。然后他将桶 $1$ 的牛奶倒入桶 $2$，然后将桶 $2$ 中的牛奶倒入桶 $3$，然后将桶 $3$ 中的牛奶倒入桶 $1$，然后再将桶 $1$ 的牛奶倒入桶 $2$，如此周期性地操作，共计进行 $100$ 次（所以第 $100$ 次操作会是桶 $1$ 倒入桶 $2$）。当 Farmer John 将桶 $a$ 中的牛奶倒入桶 $b$ 时，他会倒出尽可能多的牛奶，直到桶 $a$ 被倒空或是桶 $b$ 被倒满。

请告诉 Farmer John 当他倒了 $100$ 次之后每个桶里将会有多少牛奶。



## 说明/提示

在这个例子中，每倒一次之后每个桶里的牛奶量如下：

0. 初始状态：3  4  5
1. 桶 1->2：0  7  5
2. 桶 2->3：0  0  12
3. 桶 3->1：10 0  2
4. 桶 1->2：0  10 2
5. 桶 2->3：0  0  12

（之后最后三个状态循环出现……）

## 样例 #1

### 输入

```
10 3
11 4
12 5```

### 输出

```
0
10
2```

# 题解

## 作者：Alex_Wei (赞：23)

按照题意纯模拟即可。

这一题是 $\mathrm{for}$ 循环小练。

---

具体思路见代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int c[4],m[4];//c数组是容量，m数组是桶里牛奶的数量 
int main()
{
	for(int x=1;x<=3;x++)cin>>c[x]>>m[x];//输入 
	for(int x=1;x<=100;x++){//循环模拟100次
		int f=(x-1)%3+1,s;//f是要将牛奶倒出的桶，s则是倒入的桶
		if(f==3)s=1;//桶3要倒给桶1
		else s=f+1;//否则就倒给下一个桶
		int mi=min(c[s]-m[s],m[f]);//mi是倒牛奶的数量，取桶s剩余容积和桶f牛奶数量的最小值 
		m[f]-=mi;//桶f倒出 
		m[s]+=mi;//桶s倒入 
	}
	cout<<m[1]<<endl<<m[2]<<endl<<m[3];//输出 
	return 0;
}
```
$\mathrm{Upd:2019.12.11:}$ 添加 $\mathrm{Latex}$，美化文章。

---

## 作者：Guess00 (赞：17)

### 思路:
$\because\text{100}\equiv\text{4}\pmod{3}$

$\therefore\text{可以把倒100次当做倒4次}$

~~[更好的阅读体验](https://www.luogu.org/blog/Guess00/USACO18DEC-MixingMilk)~~

```cpp
#include <bits/stdc++.h>
using namespace std;
int i,j,k,a[4],b[4];      //a表示容量,b表示现有量
int main()
{
	for (i=1;i<4;i++)
		cin>>a[i]>>b[i];  //输入
	i=0,k=1;
	for (j=1;j<5;j++)   //j循环4次,表示倒4次
	{
		i++,k++;    //i,k表示该次要从第i个桶倒到第k个桶
        /*判断是否越界(毕竟是一个环)*/
		if (i==4)
			i=1;
		if (k==4)
			k=1;
		if (b[i]+b[k]<=a[k])    //倒第k个桶不会溢出
			b[k]+=b[i],b[i]=0;
		else                    //会溢出
			b[i]+=b[k]-a[k],b[k]=a[k];
	}
	for (i=1;i<4;i++)
		cout<<b[i]<<'\n';  //输出
	return 0;    //好习惯哦
} 
```

---

## 作者：LYXin (赞：7)

这题其实完全可以放到入门，其实只要模拟倒牛奶的结果就可以了
```cpp
#include<cstdio>
using namespace std;
struct node{
	int Volume,Milk;//Volume=c,Milk=m
}a[5];//用来存放三个桶的相关信息 
void Pour(int From,int to){//模拟倒牛奶的过程，表示从From桶倒到to桶 
	if(a[From].Milk<=a[to].Volume-a[to].Milk){//如果可以把From桶倒完的情况 
		a[to].Milk+=a[From].Milk;//to桶的牛奶加上了From桶的 
		a[From].Milk=0;//From桶的牛奶倒空了 
	}
	else{//倒不完的情况
		a[From].Milk=a[From].Milk-a[to].Volume+a[to].Milk;//From桶剩下的牛奶 
		a[to].Milk=a[to].Volume;//to桶倒满了 
	}
}
int main(){
	for(int i=1;i<=3;i++)
		scanf("%d%d",&a[i].Volume,&a[i].Milk);//输入 
	for(int i=1;i<=33;i++){//按顺序完成1~99的倒牛奶过程 
		Pour(1,2);//1倒到2 
		Pour(2,3);//2倒到3
		Pour(3,1);//3倒到1
	}
	Pour(1,2);//第100次
	for(int i=1;i<=3;i++)
		printf("%d\n",a[i].Milk);//输出最终结果 
	return 0;
}
```


---

## 作者：Starlight237 (赞：7)

题解中的代皆使用for循环，由于本题的特性，其中还有许多条件判断。

但这最多是道入门难度的题，这些东西会显得有些冗余，本题解将提供一种思维复杂度最低的思路，实际要写的代码只有半行。

假设现在要把第一个桶的牛奶倒入第二个桶，那么显然要倒$\min(m1,c2-m2)$单位的牛奶。故可写为：
$$x=\min(m1,c2-m2),m1+=x,m2-=x$$
仅仅半行。

然后复制粘贴，改几个数字，就成了
```cpp
x=min(m1,c2-m2),m1-=x,m2+=x,
x=min(m2,c3-m3),m2-=x,m3+=x,
x=min(m3,c1-m1),m3-=x,m1+=x;
```
然后我们定义一个宏：
```cpp
#define todo() \
x=min(m1,c2-m2),m1-=x,m2+=x,\
x=min(m2,c3-m3),m2-=x,m3+=x,\
x=min(m3,c1-m1),m3-=x,m1+=x;
```
把它复制粘贴$\lfloor\dfrac{100}3\rfloor=33$次，最后复制一下从1倒到2的代码即可。

code:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define reg register
int main(){
    int c1,m1,c2,m2,c3,m3,x;
    scanf("%d%d%d%d%d%d",&c1,&m1,&c2,&m2,&c3,&m3);
    
    #define todo() \
    x=min(m1,c2-m2),m1-=x,m2+=x,\
    x=min(m2,c3-m3),m2-=x,m3+=x,\
    x=min(m3,c1-m1),m3-=x,m1+=x;
    
    todo()todo()todo()todo()todo()todo()todo()todo()
    todo()todo()todo()todo()todo()todo()todo()todo()
    todo()todo()todo()todo()todo()todo()todo()todo()
    todo()todo()todo()todo()todo()todo()todo()todo()
    todo()x=min(m1,c2-m2),m1-=x,m2+=x;
    printf("%d\n%d\n%d",m1,m2,m3);
    return 0;
}
```

---

## 作者：PrefixAMS (赞：3)

#### 这道题主要就是模拟

## 模拟三个桶

## 注意在 1 3两桶之间的变换

##### 这道题差不多就过了

```cpp
#include<iostream>
#include<bits/stdc++.h>
using namespace std;
long long m1,m2,m3,c1,c2,c3;
int main()
{
	cin>>c1>>m1>>c2>>m2>>c3>>m3;
	for(int i=1;i<=100;i++)
	{
	//	cout<<i<<"*- "<<m1<<" "<<m2<<" "<<m3<<endl;
		if(i%3==1)
		{
		if(m1+m2>c2)
		{
			m1-=c2-m2;
			m2=c2;
		}
		else {
			m2+=m1;
			m1=0;
	    }
		}
		if(i%3==2)
		{
		if(m2+m3>c3)
		{
		    m2-=c3-m3;
			m3=c3;
		}
		else {
			m3+=m2;
			m2=0;
		}
	    }
	    if(i%3==0)
	    {
	    if(m3+m1>c1)
		{
			m3-=c1-m1;
			m1=c1;
		}
		else {
			m1+=m3;
			m3=0;
		}
	    }
		
	//	cout<<i<<" "<<m1<<" "<<m2<<" "<<m3<<endl; debug
	}
	cout<<m1<<endl<<m2<<endl<<m3;
	return 0;
}
```


---

## 作者：Konnyaku_ljc (赞：2)

# 还是个模拟
经由题意所得——“（之后最后三个状态循环出现……）”  
所以，100次循环只来四次就行了……
### 直接上代码，里面有详解（逃
```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
int a[5],b[5],x=1;//a===c，b==m，x代表现在的桶
int main()
{
	cin>>a[1]>>b[1]>>a[2]>>b[2]>>a[3]>>b[3];//输入
	for(int i=1;i<=4;i++)//四层
	{
		if(x==4){x=1;}//4就回去了
		if(x==1||x==2)//在等于1或2时
		{
			int ans=b[x]+b[x+1];//总和是他们俩的和
			if(ans>=a[x+1])//比下一桶容积大时
    		{
	    		b[x]=ans-a[x+1];//是这个（易证明）
		    	b[x+1]=a[x+1];//是这个（易证明）
		    }
    		else
	    	{
			    b[x+1]=ans;//是这个（易证明）
			    b[x]=0;//是这个（易证明）
		    }
		}
		if(x==3)//同上，就是3和1来
		{
			int ans=b[x]+b[1];
			if(ans>=a[1])
    		{
	    		b[x]=ans-a[1];
		    	b[1]=a[1];
		    }
    		else
	    	{
			    b[1]=ans;
			    b[x]=0;
		    }
		}
		x++;
	}
	cout<<b[1]<<endl<<b[2]<<endl<<b[3];//输出
	return 0;
}
```
AC
#### 谢谢观赏！

---

## 作者：TAFE_ZZR (赞：1)

## 今天给大家介绍一下结构体和函数,它们让程序更简洁
## 1.结构体
### 我们都知道C++中有许多种数据类型例如int,char,bool等等,
### 我们也可以自己定义数据类型 , 语句如下:
	struct barrel {
		int v,n; 
	}a,b,c; 
### 这样,我们就定义了a,b,c三个名叫barrel的变量
### 我们可以用"a.n","c.v"等来使用
## 2.函数
### 函数分为很多种,这里用的是void类型的函数
### 函数可以让程序思路更清晰,代码如下:
	void milk(barrel &x,barrel &y) { //传入数据
		if(x.n<=y.v-y.n) {
			y.n+=x.n;
			x.n=0;
		} else {
			x.n-=y.v-y.n;
			y.n=y.v;
		}
	}
### 你可以在main函数中调用或其他函数中调用
#
## 本题直接模拟就好了
## 下面是代码：
	#include<bits/stdc++.h> //万能头文件
	using namespace std;
	struct barrel { //定义结构体
		int v,n; //v表示桶的容量,n表示桶里装的牛奶数量
	}a,b,c; //定义了a,b,c
	void milk(barrel &x,barrel &y) { //定义函数
    //作用:将x桶的牛奶倒入y桶
		if(x.n<=y.v-y.n) {  //模拟
			y.n+=x.n;
			x.n=0;
		} else {
			x.n-=y.v-y.n;
			y.n=y.v;
		}
	}
	int main(){
		cin>>a.v>>a.n>>b.v>>b.n>>c.v>>c.n; //输入
		for(int i=1;i<=100;i++)   //模拟开始
     	//当…时,将…桶的牛奶倒入…桶
			if(i%3==1) milk(a,b);       
			else if(i%3==2) milk(b,c);
			else milk(c,a);
		cout<<a.n<<endl<<b.n<<endl<<c.n; //输出
		return 0;
	}


---

## 作者：秋雨 (赞：0)

不废话，讲思路！

先定义数组（虽然三个可以手打，但for循环输入更方便）

输入不讲

然后循环100次，每一次两种情况：

1. 桶a倒空：桶a为零，桶b加上桶a
1. 桶b倒满：桶b=c[b]，a减去桶b增加的（注意运输按顺序）

最后输出
```
#include<bits/stdc++.h>
using namespace std;
int main(){
	int c[3],m[3];
	for(int i=0;i<3;i++) cin>>c[i]>>m[i];
	for(int i=0;i<100;i++){
		int a=i%3,b=(a+1)%3;
		if(m[a]+m[b]>c[b]) m[a]-=(c[b]-m[b]),m[b]=c[b];
		if(m[a]+m[b]<=c[b]) m[b]+=m[a],m[a]=0;
	}
	for(int i=0;i<3;i++) cout<<m[i]<<endl;
}
```
完美~~啊啊

---

## 作者：fls233666 (赞：0)

**2020年2月16日更新：修正题解排版格式问题**

----------

看到这题，首先会注意到一件事：

FJ 只倒 $100$ 次牛奶！

**只倒 $100$ 次！！！**

次数这么小，直接**模拟**啊！

可以从题目中了解，FJ 的循环周期长度为 $3$。因此，开一个数组记录每次要倒的桶的编号，然后循环 $100$ 遍，对当前的循环次数取模，就能在数组中找到要倒的桶的编号。

但是，还有一个关键问题没有解决：倒牛奶的操作过程。

我们来看看，如果桶 $a$ 中有 $s_a$ 的牛奶，要倒入容积为 $V_b$，里面已经有 $s_b$ 牛奶的 $b$ 桶中，会出现什么情况。

显然，$b$ 桶剩下的用来装牛奶的空间为 $V_b-s_b$。则当 $b$ 桶无法装下 $a$ 桶中的所有牛奶时，有 $a_s>V_b-s_b$。反之，能装下时则有 $a_s \le V_b-s_b$。那么我们取 $u= \min(a_s,V_b-s_b)$，表示倒出去的牛奶量，然后计算 $a_s-u$ 与 $b_s+u$ 即可完成倒牛奶操作。

下面是此题的 AC 代码：

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
struct buc{
    int v;   //容量
    int s;   //当前桶内牛奶量
}b[3];
int pa[3]={0,1,2},pb[3]={1,2,0};   //循环周期桶编号
void pass(struct buc &b1, struct buc &b2){
    int pu=min(b1.s,b2.v-b2.s);
    b1.s-=pu;
    b2.s+=pu;
}   //把b1中的牛奶倒至b2
  
int main(){
    for(int i=0;i<3;i++)
        scanf("%d%d",&b[i].v,&b[i].s);   //读入牛奶的容量和牛奶量
                         
    for(int i=0;i<100;i++)
        pass(b[pa[i%3]],b[pb[i%3]]);//循环倒牛奶100次
  
    for(int i=0;i<3;i++)
        printf("%d\n",b[i].s);  //输出结果
    return 0;
}
```

在完成此题后，可以尝试完成这道搜索题，两题中倒牛奶的操作是相同的：[P1215](https://www.luogu.org/problemnew/show/P1215)

---

## 作者：_aeolian (赞：0)


这道题的思路是　创建一个函数，再循环一百次，求得答案
```cpp
#include<bits/stdc++.h>
using namespace std;
int c[4],m[4];
void work(int from,int to){
	if(c[to]-m[to]>m[from]){
	m[to]+=m[from];
	m[from]=0;
	}
	else{
	m[from]-=c[to]-m[to];
	m[to]=c[to];
	}
	return;
}
int main(){
	for(int i=1;i<=3;i++)
		cin>>c[i]>>m[i];
	for(int i=1;i<=100;i++) {
		if(i==3)work(i%3+3,(i+1)%3);
		if(i==2)work(i%3,(i+1)%3+3);
		else    work(i%3,(i+1)%3);
	}
	cout<<m[1]<<endl<<m[2]<<endl<<m[3]<<endl;
return 0;
}
 
```
非原创，思路等来自damage

---

## 作者：Koakuma (赞：0)

### 看到题解中没有dfs的，这里写一篇dfs的题解
~~其实没必要这么麻烦~~，就算是一次dfs练习吧
## Code

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int A,B,C,a,b,c;
inline void dfs(int a,int b,int c,int time)
{
	if(!time){printf("%d\n%d\n%d\n",a,b,c);return ;}
	if(time%3==1)dfs(max(0,a-min(a,B-b)),min(b+a,B),c,time-1);  //a倒给b
	else if(time%3==0)dfs(a,max(0,b-min(b,C-c)),min(c+b,C),time-1);   //b倒给c
	else if(time%3==2)dfs(min(a+c,A),b,max(0,c-min(c,A-a)),time-1);   //c倒给a
}
int main()
{
	scanf("%d%d%d%d%d%d",&A,&a,&B,&b,&C,&c);
	dfs(a,b,c,100);
	
    return 0;
}

```
其实上述代码还可以优化，~~这里就懒得写了qwq~~

---

## 作者：jacktang233 (赞：0)

Cu的第一题，相当简单感觉读懂题了就行         
题目意思大概是说三个桶各自有容量和初始液体体积      
每次都是1->2 2->3 3->1             
需要注意倒的时候可能溢出        
比如a桶的容量是$V_a$ 初始液体体积是$W_a$      
b桶的容量是$V_b$ 初始体积是$W_b$    
我们要把a倒到b       
那么如果$W_a + W_b > V_b$      
b倒完后的体积就是$V_b$       
a倒完后就是$W_a + W_b - V_b$      
做100次就可以了        
~~其实连循环都不用的 复制粘贴100次就可以了~~
```cpp
#include <iostream>
#include <cstdio>

using namespace std;
int a1,a2,a3;
int c1,c2,c3;
int main() 
{
	cin>>a1>>c1>>a2>>c2>>a3>>c3;
	for(int i=1;i<=33;i++)
	{
		if(c1+c2 <= a2)
		{
			c2+=c1;
			c1-=c1;
		}
		else if(c1+c2 > a2)
		{
			c1 = c1+c2-a2;
			c2 = a2;
		}
		
		if(c2+c3 <= a3)
		{
			c3+=c2;
			c2-=c2;
		}
		else if(c2+c3 > a3)
		{
			c2 = c2+c3-a3;
			c3 = a3;
		}
		
		if(c3+c1 <= a1)
		{
			c1+=c3;
			c3-=c3;
		}
		else if(c3+c1 > a1)
		{
			c3 = c1+c3-a1;
			c1 = a1;
		}
		
	}
    //100 mod 3余1所以还要操作一次
	if(c1+c2 <= a2)
	{
		c2+=c1;
		c1-=c1;
	}
	else if(c1+c2 > a2)
	{
		c1 = c1+c2-a2;
		c2 = a2;
	}
	
	cout<<c1<<endl;
	cout<<c2<<endl;
	cout<<c3<<endl;
	return 0;
	
}
```

---

## 作者：damage (赞：0)

### 题解

```USACO 2018.12月赛 铜组 第一题```

其实就是给你三个桶的容量，然后倒一百次，输出最好的结果。

每次倒的时候，我们用```pour(from,to)```表示从```from```桶倒到```to```桶去（下标从零开始）

倒的时候有两种情况：（用```m[]```表示桶的容量，```c[]```表示桶内牛奶的数量）

1. ```from```桶的牛奶倒光了还装不满```to```桶，即```c[to]-m[to]>m[from]```，此时将```from```桶里的牛奶全部加到```to```桶里然后置零即可。

2. ```to```桶装满了```from```桶还是没有倒完，此时只要将```from```桶里的牛奶数量减去```to```桶里牛奶的剩余空间，然后再把```to```桶里的牛奶数量设为满桶即可

---

### 代码

```cpp
#include<stdio.h>
int c[10],m[10];
void pour(int from,int to)
{
    if(c[to]-m[to]>m[from]) //第一种情况
    {
        m[to]+=m[from]; //from桶全部倒进to桶
        m[from]=0; //置零from桶
    }
    else //第二种情况
    {
        m[from]-=c[to]-m[to]; //from桶的容量减去to桶剩下的
        m[to]=c[to]; //to桶被装满了
    }
    return ;
}
int main()
{
    for(register int i=0;i<3;++i) scanf("%d%d",&c[i],&m[i]);
    for(register int i=0;i<100;++i) pour(i%3,(i+1)%3); //第(i%3)桶倒到下一桶
    printf("%d\n%d\n%d\n",m[0],m[1],m[2]); //最后输出剩余牛奶数量即可
    return 0;
}
```

~~这题难到绿题了吗？~~

---

## 作者：封禁用户 (赞：0)

考虑最暴力的方法。

暴力循环$100$次，没了。

```cpp
/*
ID: Anfangen
LANG: C++
PROG: mixmilk
*/
#include <cstdio>
#include <iostream>
#include <stack>
#include <utility>
#include <algorithm>
#include <set>
#include <cstring>
#include <string>
#include <vector>
#include <cmath>
#define rep(i,a,b) for(int i=(a);i<=(b);++i) 
#define dec(i,a,b) for(int i=(a);i>=(b);--i)
#define gc() getchar()
#define endll putchar('\n')
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
typedef long double ld;
inline ll read(){
	char ch=gc();
	ll x=0,f=1;
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-1;
		ch=gc();
	}
	while(ch>='0'&&ch<='9'){
		x=x*10+ch-'0';
		ch=gc();
	}
	return x*f;
}
inline void print(ll k){
	if(k<0) k=-k,putchar('-');
	if(k>9) print(k/10);
	putchar(k%10+48);
}
inline void println(ll k){
	print(k);
	endll;
}
inline void printsp(ll k){
	print(k);
	putchar(' ');
}
int b[4],cur[4];
int main(){
	//freopen("mixmilk.in","r",stdin);
	//freopen("mixmilk.out","w",stdout);
	rep(i,1,3){
		b[i]=read();
		cur[i]=read();
	}
	rep(i,1,100){
		int tmp=i%3;
		if(tmp==0) tmp=3;
		int next=(tmp+1)%3;
		if(next==0) next=3;
		if(cur[tmp]+cur[next]>b[next]) {
			cur[tmp]=cur[tmp]+cur[next]-b[next];
			cur[next]=b[next];
		}
		else{
			cur[next]+=cur[tmp];
			cur[tmp]=0;
		}
	}
	rep(i,1,3) println(cur[i]);
	return 0;
}
```

---

## 作者：桑树下的邂逅 (赞：0)

~~挺显然的~~，程序里都写了
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int a,x,b,y,c,z;
void check(int &a,int &x,int &b,int &y){
    int t=min(a,y-b);//a为牛奶量，y-b为桶中空的量
    a-=t;b+=t;//至于&而是为了方便修改而传址
}
int main(){
    scanf("%d%d%d%d%d%d",&x,&a,&y,&b,&z,&c);
    for(int i=1;i<=33;i++){
       by Andrew;
       check(a,x,b,y);check(b,y,c,z);check(c,z,a,x);
    }
    check(a,x,b,y);//模拟即可
    printf("%d\n%d\n%d",a,b,c);//输出
    return 0;
}
```

---

## 作者：Real_Create (赞：0)

[能看鼬神和题解的地方](https://www.luogu.org/blog/jerry0802-VX/solution-p5116)

[也许会更好的阅读体验](https://www.luogu.org/blog/jerry0802-VX/solution-p5116)

我们可以只循环4次（原因看上面的大佬）

其次，4次你可以手打

所以有了这个代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	int a,b,c,tj1,tj2,tj3,t;
	cin>>tj1>>a>>tj2>>b>>tj3>>c;
	t=min(a,tj2-b);//A到B
	a-=t;
	b+=t;
	t=min(b,tj3-c);//B到C
	b-=t;
	c+=t;
	t=min(c,tj1-a);//B到C
	c-=t;
	a+=t;
	t=min(a,tj2-b);//A到B
	a-=t;
	b+=t;
	cout<<a<<endl<<b<<endl<<c;
	return 0;//不是很好的AC
}
```
然后我们可以把他压缩

没错，理论上可以压缩成3行代码。我拼尽全力才压成了这样+挑战最短代码（8行）

```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
	int a,b,c,tj1,tj2,tj3,t;
	cin>>tj1>>a>>tj2>>b>>tj3>>c;
	cout<<a-min(a,tj2-b)+min(c+min(b+min(a,tj2-b),tj3-c),tj1-a+min(a,tj2-b))-min(a-min(a,tj2-b)+min(c+min(b+min(a,tj2-b),tj3-c),tj1-a+min(a,tj2-b)),tj2-b-min(a,tj2-b)+min(b+min(a,tj2-b),tj3-c))<<endl<<b+min(a,tj2-b)-min(b+min(a,tj2-b),tj3-c)+min(a-min(a,tj2-b)+min(c+min(b+min(a,tj2-b),tj3-c),tj1-a+min(a,tj2-b)),tj2-b-min(a,tj2-b)+min(b+min(a,tj2-b),tj3-c))<<endl<<c+min(b+min(a,tj2-b),tj3-c)-min(c+min(b+min(a,tj2-b),tj3-c),tj1-a+min(a,tj2-b));
	return 0;//不打这个会更短吧。。。
}//很好的AC
//不对，很短的AC
```
[咕测记录8行AC](https://www.luogu.org/record/23458628)

我们要从下往上压缩，因为下面对上面是没有影响的，所以我们不停在输出去找a，b，c，就可以了！

---

## 作者：__Hacheylight__ (赞：0)

T1 Mixing Milk

【题意】

给你三个桶和他们的容量和现在装了多少，问倒奶100次之后变成什么样（不能倒出来）

【分析】

铜组题都水的要死，这题肯定红题啊，怎么会是绿题呢？

才100次，很明显是模拟题。

我们直接枚举怎么倒

假设倒1桶和2桶，那么能够倒出来的量$sum=min(b[1],a[2]-b[2])$，即当前1的桶内量和b桶还可以放多少。

其他两种倒法类似。

总共100次，为$33*(1->2)+33*(2->3)+33*(3->1)+1->2$

余下来再处理一次$1->2$，就AC了。

【代码】

```cpp
#include <bits/stdc++.h>
using namespace std ;

#define rep(i, a, b) for (int (i) = (a); (i) <= (b); (i)++)
#define Rep(i, a, b) for (int (i) = (a) - 1; (i) < (b); (i)++)
#define REP(i, a, b) for (int (i) = (a); (i) >= (b); (i)--)
#define clr(a) memset(a, 0, sizeof(a))
#define Sort(a, len, cmp) sort(a + 1, a + len + 1, cmp)
#define ass(a, sum) memset(a, sum, sizeof(a))

#define ls ((rt) << 1)
#define rs ((rt) << 1 | 1)
#define lowbit(x) (x & -x)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define endl '\n'
#define ENDL cout << endl
#define SZ(x) ((int)x.size())

typedef long long ll ;
typedef unsigned long long ull ;
typedef vector <int> vi ;
typedef pair <int, int> pii ;
typedef pair <ll, ll> pll ;
typedef map <int, int> mii ;
typedef map <string, int> msi ;
typedef map <ll, ll> mll ;

const int N = 10 ;
const double eps = 1e-8 ;
const int iinf = INT_MAX ;
const ll linf = 2e18 ;
const double dinf = 1e30 ;
const int MOD = 1000000007 ;

inline int read(){
    int X = 0, w = 0 ;
    char ch = 0 ;
    while (!isdigit(ch)) { w |= ch == '-' ; ch = getchar() ; }
    while (isdigit(ch)) X = (X << 3) + (X << 1) + (ch ^ 48), ch = getchar() ;
    return w ? - X : X ;
}

void write(int x){
     if (x < 0) putchar('-'), x = - x ;
     if (x > 9) write(x / 10) ;
     putchar(x % 10 + '0') ;
}

void print(int x) {
    cout << x << endl ;
    exit(0) ;
}

void PRINT(string x) {
    cout << x << endl ;
    exit(0) ;
}

void douout(double x){
     printf("%lf\n", x + 0.0000000001) ;
}

int n ;
int a[N], b[N] ;

int main() { 
	n = 3 ; 
	for (int i = 1; i <= n; i++) scanf("%d%d", &a[i], &b[i]) ;
	for (int rnd = 1, tmp; rnd <= 33; rnd++) {
		tmp = b[1] ;
		if (tmp > a[2] - b[2]) tmp = a[2] - b[2] ;
		b[1] -= tmp ; b[2] += tmp ;
		
		tmp = b[2]  ;
		if (tmp > a[3] - b[3]) tmp = a[3] - b[3] ;
		b[2] -= tmp ; b[3] += tmp ;
		
		tmp = b[3] ;
		if (tmp > a[1] - b[1]) tmp = a[1] - b[1] ;
		b[3] -= tmp ; b[1] += tmp ;
	}
	int tmp = b[1] ;
	if (tmp > a[2] - b[2]) tmp = a[2] - b[2] ;
	b[1] -= tmp ;
	b[2] += tmp ;
	printf("%d\n%d\n%d\n", b[1], b[2], b[3]) ;
} 
```

---

