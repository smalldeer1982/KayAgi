# [USACO3.2] 魔板 Magic Squares

## 题目背景

在成功地发明了魔方之后，鲁比克先生发明了它的二维版本，称作魔板。这是一张有 $8$ 个大小相同的格子的魔板：

$1\quad2\quad3\quad4$

$8\quad7\quad6\quad5$


## 题目描述

我们知道魔板的每一个方格都有一种颜色。这 $8$ 种颜色用前 $8$ 个正整数来表示。可以用颜色的序列来表示一种魔板状态，规定从魔板的左上角开始，沿顺时针方向依次取出整数，构成一个颜色序列。对于上图的魔板状态，我们用序列 $\{1,2,3,4,5,6,7,8\}$ 来表示。这是基本状态。

这里提供三种基本操作，分别用大写字母 $\text A$，$\text B$，$\text C$ 来表示（可以通过这些操作改变魔板的状态）：

$\text A$：交换上下两行；

$\text B$：将最右边的一列插入最左边；

$\text C$：魔板中央四格作顺时针旋转。

下面是对基本状态进行操作的示范：

$\text A$：

$8\quad7\quad6\quad5$

$1\quad2\quad3\quad4$



$\text B$：

$4\quad1\quad2\quad3$

$5\quad8\quad7\quad6$

$\text C$：

$1\quad7\quad2\quad4$

$8\quad6\quad3\quad5$

对于每种可能的状态，这三种基本操作都可以使用。

你要编程计算用最少的基本操作完成基本状态到目标状态的转换，输出基本操作序列。


## 说明/提示

题目翻译来自 NOCOW。

USACO Training Section 3.2


## 样例 #1

### 输入

```
2 6 8 4 5 7 3 1 ```

### 输出

```
7 
BCABCCB```

# 题解

## 作者：getchar123 (赞：90)

第一次写题解，不太会用emm将就一下吧。
步入正题：广搜+map去重
可以先把它当字符串处理，再找出ABC三种操作的规律，用函数模拟。map里存操作序列。
贴代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
string a;
map<string,string>m;
queue<string>q;
void A(string x){
	string xx=x;
	for(int i=0;i<4;i++){
		char x1=x[i];
		x[i]=x[7-i];
		x[7-i]=x1;
	}
	if(m.count(x)==0){//没有出现过
		q.push(x);
		m[x]=m[xx]+'A';
	}
	return;
}
void B(string x){
	string xx=x;
	x[0]=xx[3],x[1]=xx[0],x[2]=xx[1],x[3]=xx[2],x[4]=xx[5],x[5]=xx[6],x[6]=xx[7],x[7]=xx[4];
	if(m.count(x)==0){
		q.push(x);
		m[x]=m[xx]+'B';
	}
	return;
}
void C(string x){
	string xx=x;
	x[1]=xx[6],x[2]=xx[1],x[5]=xx[2],x[6]=xx[5];
	if(m.count(x)==0){
		q.push(x);
		m[x]=m[xx]+'C';
	}
	return;
}
void bfs(){
	q.push("12345678");
	m["12345678"]="";
	while(q.empty()==false){
		A(q.front());
		B(q.front());
		C(q.front());
		if(m.count(a)!=0){//当出现目标序列
			cout<<m[a].size()<<endl<<m[a];
			return;
		}
		q.pop();
	}
	return;
}
int main(){
	for(int i=0;i<8;i++){
		char a1;
		cin>>a1;
		a+=a1;
		getchar();
	}
	bfs();
	return 0;
}
```

---

## 作者：fdfdf (赞：33)

一道经典的搜索题


- 大家都能想到用广搜吧

- 但难点在判重上：

- 需要把每个搜索到的魔板状态加入bfs的队列里面

- 1、我们可能会想到将魔板的8个位置上的数字直接转换为8位数加入队列

- 这样的话我们需要将每个魔板的8位置状态转换为一个8位数

- 判重时需要长度近10^8的布尔数组，空间将近200M，肯定是过不了的

- 2、继续思考：魔板的所有排列方式共有8！=40320种，如果把魔板的每一种排列方式都用某种方法遍上一个序号

，那么判重的时候就只需要长度略大于40000的布尔数组，空间少了很多

- 那么到底应该怎么编号？

- 我们先从简单一点的例子看起：

- 当需要排列的数字只有2个:1,2的时候，很容易就能找出所有的排列方式：（1,2），（2,1）；只有两种；

- 如果排列的数字有3个:1,2,3，那么我们可以根据排列的第一位数字进行分类：

- 第一位为1的排列:(1,2,3),(2,1,3),

- 第一位为2的排列:(2,1,3),(2,3,1),

- 第一位为3的排列:(3,1,2),(3,2,1);

- 那么规律就出来了：对于从1到n的排列，如果第1位数字为i，那么这个排列的编号肯定在（i-1)\*(n-1)!-i\*(n-1)!的范围内。这样我们就可以把这个问题的规模缩小。

- 但是留下来的数字并不一定是1到（n-1），需要重新给它们排序吗？

- 其实上面的规律也可以这样解释：当排列的第一位数字为所有元素中第i大的数字时，这个排列的编号在（i-1)(n-1)!-i(n-1)!之间。

- 那么我们只需要寻找当前排列中某个数的后方:有多少个数字与它不组成升序序列，那么就说明它是在后面所有元素中的第几位

- 那么我们就可以得到一个编号用的方程:

**X=a[n]\*(n-1)!+a[n-1]\*(n-2)!+...+a[i]\*(i-1)!+...+a[1]\*0!**其中**a[i]**为当前未出现的元素中是排在第几个（从0开始）。

其实这就是康托展开。


这个难点解决了，接下来的问题就很简单了，上代码：

```cpp
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
using namespace std;
bool bb[9],b[50000];//判重数组 
int MS[9];//我们需要转换到的魔板状态 
char re[10];//用于输出 
struct node{    //每个结点表示该魔板的状态 
    int a[9];    //魔板上的数字 
    int step,father;//已变换步数和其前驱 
    char c;//上一步做的转换 
}l[50000];//总共只有40000多种排列，所以队列不必开很大 

void print(node x){
    int s=0;
    while(x.father!=0){
        re[++s]=x.c;
        x=l[x.father];
    }
    for(int i=s;i>=1;i--){
        printf("%c",re[i]);
    }
    return;
}//通过反复调用目标节点的前驱进行回溯输出 

int fc(int x){        //阶乘 
    if(x==0)return 0;
    if(x==1)return 1;
    return x*fc(x-1);
}
inline int KT(node x){        //康拓展开在这里 
    int num=0;
    for(int i=1;i<=8;i++){
        int s=0;
        for(int j=i+1;j<=8;j++){
            if(x.a[i]>x.a[j])s++;
        }
        num+=s*fc(8-i);
    }
    return num;
}
inline void swapp(int &a,int &b) 
{int c=a;a=b;b=c;}
node A(node),B(node),C(node);

int main(){
    for(int i=1;i<=8;i++)scanf("%d",&MS[i]);
    int head=0,tail=1;
    for(int i=1;i<=9;i++)l[1].a[i-1]=i-1;
    l[1].step=0;
    l[1].father=0;//初始化 
    do
    {
        head++;
        int flag=1;
        for(int i=1;i<=8;i++){
            if(l[head].a[i]!=MS[i]){
                flag=0;break;
            }
        }
        if(flag){
            printf("%d\n",l[head].step);
            print(l[head]);
            return 0;
        }
        
        for(int i=1;i<=3;i++){
            node k;
            if(i==1)k=A(l[head]);
            if(i==2)k=B(l[head]);
            if(i==3)k=C(l[head]);
            int kk=KT(k);
            if(!b[kk]){
                b[kk]=1;
                tail++;
                l[tail]=k;
                l[tail].step++;
                l[tail].father=head;//记录该状态的前驱（前一步） 
                l[tail].c=i+'A'-1;
            }
        }
    }while(head<tail);//bfs的板子 
    printf("0");
    return 0;
}
node A(node x){
    for(int i=1;i<=4;i++)
        swapp(x.a[i],x.a[9-i]);
    return x;
}
node B(node x){
    for(int i=4;i>=2;i--){
        swapp(x.a[i-1],x.a[i]);
        swapp(x.a[9-i],x.a[10-i]);
    }
    return x;
}
node C(node x){
    swapp(x.a[3],x.a[2]);
    swapp(x.a[7],x.a[6]);
    swapp(x.a[2],x.a[6]);
    return x;//题目所说三种变换 
}
```

---

## 作者：顾z (赞：18)


没看过题的童鞋请去看一下题-->[P2730 魔板 Magic Squares](https://www.luogu.org/problemnew/show/P2730)

不了解康托展开的请来这里-->[我这里](https://rpdreamer.blog.luogu.org/p2524)

## 广告： [安利blog](https://www.luogu.org/blog/RPdreamer/#)

至于这题**为什么可以用康托展开**?~~(瞎说时间到.~~

因为只有8个数字,且只有1~8这8个数字,所以我们可以算出最多情况有8！=40320个.

所以我们完全可以开数组记录这些状态并且记录这些答案.

康托展开的作用就是**把这些排列映射成一个排名**.

如果我们存储排列,那极限情况应该是87654321,很容易就炸掉的.

而映射成排名的话,我们开的极限只有40320,大约是1/2173的空间.

因此我们就可以这样去存储状态.

即
	 
    vis[i]代表排名为i的排列存在
    to[i]代表从初状态到达排名为i的状态的操作序列.//要开成string类型.


**求解：**

那么如何求解呢？

对于初状态{1,2,3,4,5,6,7,8}是不变的,因此我们可以用bfs预处理出来其他状态.

而要满足字典序最小,我们可以先尝试进行A操作,B操作,C操作即可。其他操作就和普通的bfs差不多了。

对操作之后的序列,我们去求一下他的排名,那我们就可以得到 变成他的操作序列.把操作序列存储进to[]数组即可。

**ps:字符串string类型支持拼接操作**

而我们**不要忘记把序列还原**。

即改变一个序列有三种操作,我们不能连续进行A,B,C操作,需要对当前的序列操作.

因此就预处理出来了。

**解决：**

然后我们如何输入？(这里卡了好久的QwQ

getchar()可以读一切字符~~(应该是~~

所以我们就可以**每次放一个getchar()**!

而去一位一位的存储读入的字符串。

所以说我们就可以完美的解决这个题啦！

部分代码参考-->[ @qiqi_starsky](https://blog.csdn.net/qiqi_skystar/article/details/49493357)

-------------------代码---------------------

```
#include<bits/stdc++.h>
#define IL inline
#define RI register int
using namespace std;
const int fac[]={1,1,2,6,24,120,720,5040,40320,362880};//阶乘
struct code
{
	string st,step;
}s,ss;
string to[666666];
bool vis[666666];
IL int Contor(string &s)//这里本应该不加&就可以正确的.
						//但不加会Wa
                        //应该是你谷评测机的锅.
                        //已经尝试过在bzoj提交,不加&是可以过的
{
    int ans=0;
    for(RI i=0;i<8;i++)
    {
        //std::cout<<ans<<std::endl;
        int smaller=0;
        for(RI j= i+1 ;j<8;j++)
        {
            if(s[i] > s[j])smaller++;
        }
        ans += smaller*fac[8-i-1];
    }
    return ans+1;
}
IL void A(string &s)
{
	for(RI i=0;i<4;i++)
		swap(s[i],s[8-i-1]);
}
IL void B(string &s)
{
	int t=s[3];
	for(RI i=3;i>=1;i--)
		s[i]=s[i-1];
	s[0]=t;
	int tt=s[4];
	for(RI i=4;i<=6;i++)
		s[i]=s[i+1];
	s[7]=tt;
}
IL void C(string &s)
{
    int t=s[6];
    s[6]=s[5];
    s[5]=s[2];
    s[2]=s[1];
    s[1]=t;
}

/*
1 2 3 4
5 6 7 8
↓ ↓ ↓ ↓
1 7 2 4
8 6 3 5
*/
IL void bfs()
{
	std::queue<code>q;
	s.st="12345678";
	s.step="";
	q.push(s);
	vis[Contor(s.st)]=true;
	while(!q.empty())
	{
		s=q.front();q.pop();
		ss=s;
		A(ss.st);//A操作
		int cnt=Contor(ss.st);//对于改变的操作序列求出他的排名
		if(!vis[cnt])
		{
			ss.step+="A";
			to[cnt]=ss.step;//字符串可以直接整个赋过去
			q.push(ss);//把一个新的字符串放过去,接下来扩展
			vis[cnt]=true;//标记
		}
		ss=s;//还原的操作！！！很重要！
		B(ss.st);//B操作
		cnt=Contor(ss.st);
		if(!vis[cnt])
		{
			ss.step+="B";
			to[cnt]=ss.step;
			q.push(ss);
			vis[cnt]=true;
		}
		ss=s;
		C(ss.st);//C操作
		cnt=Contor(ss.st);
		if(!vis[cnt])
		{
			ss.step+="C";
			to[cnt]=ss.step;
			q.push(ss);
			vis[cnt]=true;
		}
	}
}
int main()
{
	bfs();
	string str;
	cin>>str[0];getchar();cin>>str[1];getchar();
    cin>>str[2];getchar();cin>>str[3];getchar();
    cin>>str[4];getchar();cin>>str[5];getchar();
    cin>>str[6];getchar();cin>>str[7];getchar();
    //这输入厉害不厉害！
	int cnt=Contor(str);
	cout<<to[cnt].length()<<endl;//字符串用.length()
	cout<<to[cnt]<<endl;
}
```
**后话**

如果给定的初始序列不是{1,2,3,4,5,6,7,8}怎么办?

把初始序列看成{1,2,3,4,5,6,7,8}即可


## Upd

**2018.09.03**

**回来填坑**

当我们的初始序列不是{1,2,3,4,5,6,7,8}该怎么做？

    例如：   瞎出的例子emmmm
     初始状态：65783241——>12345678
     对应位置得到这种状态↓
     终止状态：13486572——>85741236
更详细一点↓

看好如何对应。
       
      初状态 6 5 7 8 3 2 4 1
             ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓
      对应为 1 2 3 4 5 6 7 8
      即我们要把想得到的状态
            1 3 4 8 6 5 7 2
      用上面的对应关系转化
      
  **过程↓**
  
         1 发现 1->8
         3 发现 3->5
         4 发现 4->7
         8 发现 8->4
         6 发现 6->1
         5 发现 5->2
         7 发现 7->3
         2 发现 2->6
      最终得到8 5 7 4 1 2 3 6
如果不理解,请仔细再看一下。

这样我们求解{6,5,7,8,3,2,4,1}到{1,3,4,8,6,5,7,2}的操作,

就转变为了{1,2,3,4,5,6,7,8}到{8,5,7,4,1,2,3,6}的操作.

代码实现转化↓(尝试理解一下,~~懒得码字了 emmm~~
```cpp
 for (int i=0; i<8 ; i++)
    num[s[i]-'0']=i+1;
 //看看我们的枚举,所以需要i+1得到1,2,3.....8
 //get关系↑.s存储初状态
 
 //转化关系↓.str存储末状态
 for (int i=0; i<8 ; i++)
 	str[i]=num[str[i]-'0']+'0';
```
如果有新的知识,我还会来Upd的

**~~(逃~~**

## Upd:

**2018.09.05**

关于**康托展开那里的字符串是否需要加&**不知道是否会有疑问?

感谢[@cellur925](https://www.luogu.org/space/show?uid=60124)
的提问

已经在bzoj尝试不加&,是可以AC的.

并通过在我谷下载数据并尝试debug,发现输出是一样的.

Contor函数并没有涉及到修改原串,因此不加&应该是正确的.

~~感觉应该是你谷评测机的锅~~

而其他A,B,C操作是需要修改原串的,需要加&.

PS：加&是可以引用变量的.

---

## 作者：Kan_kiz (赞：12)

蒟蒻的第一道蓝题……~~好像也没有蓝的程度~~

## 一篇无STL的超弱题解（入门写法无误了QAQ

### [传送门](https://www.luogu.org/problemnew/show/P2730)

###### 很经典的一道BFS

#### 这是初始状态。

![这是初始状态](http://media.openjudge.cn/images/upload/1475147151.png)

### 操作A

![qwq侵删](http://media.openjudge.cn/images/upload/1475147420.png)

### 操作B

![qwq侵删](http://media.openjudge.cn/images/upload/1475147463.png)

### 操作C

![qwq侵删](http://media.openjudge.cn/images/upload/1475147491.png)

#### 思路1 不使用cantor展开的情况

### 1. 对于存储这个操作序列
- ~~一个没有什么用的空间小优化~~
#### ~~（然后时间就炸了）~~

- 存储一个字符，我们都知道需要1个Byte。那么我们存储一个魔板序列时，就需要8个Byte。

- 魔板的状态有8！=40320种，那我们在不断的存储许多新的状态时，需要预先开至少8*40320个字节的空间。

- 如果我们使用int类型进行存储，每个int类型只需要4Byte，那么就只需要4*40320个字节。~~（也没优化多少啊）~~

### 2.进行扩展
- 建立一个队列，初始的状态为队列[1][1]=12345678

- 接着我们判断，如果初始状态已经等于目标状态，直接输出0，即不需要操作

- 这个队列中的每个状态，我们需要三个空间，分别存储魔板的状态，魔板的父亲位置（就是现在魔板的状态是由队列中哪个下标的状态进行一次变化而来的），以及魔板是由魔板父亲状态经过什么操作来达到现在状态的。我们可以将三种操作简写为1，2，3。

- 对魔板状态进行扩展。即将魔板分别进行三种操作。

- PS：由于我们存储了int类型，可以手推一下三种操作的公式。推荐参考上面三幅图片。

- 每一种操作结束后，判断现在魔板状态是否在之前有出现过。（判重）

- PS：判重不使用康托展开，开87654322大的数组即可。亲测可过。

- 一旦判断已经达到目标状态，输出。

### 3.输出
- 我们在队列中已经存储过魔板的父亲位置。现在要利用这个位置来逆推我们的步骤。

- 建立一个way数组。不断的存储父亲位置。

- 逆向输出。输出对应位置上的操作。

- 详情查看代码。

## 请从变量定义及主函数开始阅读

```cpp
#include <cstdio>
#include <cmath>//pow函数的头文件

int tl[100000][3],maxn=100000;//tl是我们存储状态的队列。tl[i][1]是指第i个情况的魔板状态，tl[i][0]是第i个情况的父亲位置，t[i][2]是指第i个情况的父亲的操作（能得到i情况）

int now=12345678,finish=0;//初始状态&目标状态

int way[100000];//用于最后逆推过程的时候存储父亲位置

bool book[87654322]={};//判重（真的不会M可能是因为最开始存int

//下面三个操作函数都很乱，建议手算公式<qwq>

void A(int j)//A操作！
{
	int qwq=0;
	for (int i=8;i>=1;i--)
	{
		qwq+=((tl[j][1]%10)*pow(10,i-1));
		tl[j][1]/=10;
	}
	tl[j][1]=qwq;
	return;
}


void B(int j)//B操作！
{
	tl[j][1]=(tl[j][1]%100000/10000)*10000000+(tl[j][1]/100000)*10000+tl[j][1]%1000*10+tl[j][1]%10000/1000;
}


void C(int j)//C操作！
{
	tl[j][1]=tl[j][1]-((tl[j][1]/100000)%100)*100000-(tl[j][1]%1000)/10*10+tl[j][1]/1000000%10*100000+tl[j][1]/100000%10*100+tl[j][1]/100%10*10+tl[j][1]/10%10*1000000;//2367->7236
}

///////////////////////////////////分割线正常阅读


bool look_for(int n)//判重，即新情况的模版状态有没有在队列中出现过
{
	return book[ tl[n][1] ];
}



bool found(int w)//判断是否达到目标状态
{
	if ( tl[w][1] == finish )
	{
		return true;
	}
	return false;
}


void print(int zt)//打印函数。zt是指队列第zt种情况
{
	if ( zt == 1 )//请联系start函数的第一句“if……”理解
	{
		printf("0");
		return;
	}
	int k=0,z=zt;
	while (z>0)//逆推！比较难理解可以试着手画一下示意
	{
		k++;
        
		way[k] = z;
		z = tl[z][0];
	}
	printf("%d\n",k-1);
	for (int i=k-1;i>0;i--)
	{
		z = way[i];
        
		printf("%c",tl[z][2]+'A'-1);//转化为字符输出！原本是用123表示ABC操作
	}
	return;
}
void start()//开始啦！
{
	if ( found(1) )//如果初始状态==目标状态
	{
		print(1);
        
		return;
	}
	int i=1,j=2;
	while ( i<j && j<maxn )//仍有状态可以扩展&未溢出上限
	{
		for (int k=1;k<=3;k++)
		{
        
			tl[j][1]=tl[i][1];//预入队!
            
            
			if (k==1){  A(j);  }//A操作
            
			if (k==2){  B(j);  }//B操作
            
			if (k==3){  C(j);  }//C操作
            
            
			if ( ! look_for(j) )//如果这种状态在之前没有出现过
			{
            
				tl[j][0]=i;//tl[j][0]：我父亲叫i！
                
				tl[j][2]=k;//tl[j][2]:我是i和k的孩子！
                
                
                if (found(j))//如果已经达到了目标状态
				{
					print(j);//输出！
					return;
				}
				else {  book[ tl[j][1] ]=1;  j++;  }//标记这种状态已经出现过&队尾+1
			}
		}
		i++;//一种情况的扩展完毕，队首+1
	}
}
int main()
{
	for (int i=8;i>=1;i--)//输入，转换成int
	{
		int x;
		scanf("%d",&x);
		finish+=(x*pow(10,i-1));
	}
    
	tl[1][1]=now; tl[1][0]=0;//队列的第一个状态就是初始状态now，ta的父亲没有了……
    
	start();//开始吧！
    
	return 0;//圆满的结束……
}
```
#### 思路2 cantor展开

### 什么是康托展开？

- 对于n的一个排列，我们可以通过康托展开，映射出这个排列在n的全排列中占第几小。

- 那么我们本来使用87654322大的数组来标记出现过的状态，这时就只需要开8！=40320大的数组进行标记。

- 注意！使用康托展开需要将数位一位位分离。请慎重考虑要使用什么类型存储。推荐使用字符存储。

这里提供一个正向康托展开的代码。 具体可以[戳这里](https://baike.baidu.com/item/%E5%BA%B7%E6%89%98%E5%B1%95%E5%BC%80/7968428?fr=aladdin)
```cpp
int factorial[11]={1,1,2,6,24,120,720,5040,40320,362880};//0-10的阶乘！


int cantor(int a[]){//正向康托展开，求排列a[]在1~8的全排列中占第几小

    int ans=0,sum=0;
    for(int i=1;i<=7;i++)//最后一位不用计算(0*0!) 
	{
        for(int j=i+1;j<=8;j++)//寻找这个排列的第i位的后面有多少个数小于ta 
        {
        
        	if(a[j]<a[i]) sum++;
            
        }
        
        ans+=sum*factorial[8-i];//ans+=sum*(8-1)! 
        
        sum=0;//计数归零 
    }
    
    
    return ans+1;//这里计算的ans是比a[]排列小的排列的个数，所以a[]排列是第ans+1小的！ 
}
```
其余的思路基本是相同的。**不过**对于ABC三种操作请使用swap来实现。

蒟蒻的第一篇题解qwq 求过鸭
~~准备被残忍拒绝~~

---

## 作者：Silent_E (赞：9)

# 朴素的蒟蒻解法
众所周知，这是一道**广搜题**（假装大犇们都会广搜 ~~怎么可能不会~~）
那么本题的大体思路就明确了，剩下的就是耐心地解决一些细节问题。~~不会康拓QAQ~~

- #### 降维打击！！！（~~我不知道爱酱~~）
魔板原本是2X4的矩阵，但一维处理起来一定比二维方便，于是便可以降维，**但**，要注意技巧。

  以样例来说，括号里面代表这个数储存的一维数组的位置

| 2（a1） | 6（a2） | 8（a3） | 4（a4） |
| :----------: | :----------: | :----------: | :----------: |
| 5（a5） | 7（a6） | 3（a7） | 1（a8） |
具体实现请看代码：
```cpp
 for(int i=1;i<=8;i++){//基本状态
    	if(i<=4) sak[1].before[i]=i;
    	if(i>4) sak[1].before[i]=13-i;
    }
```

```cpp
for(int i=1;i<=4;i++)//双循环输入目标状态（真~~朴素~~）
    	scanf("%d",&after[i]);
    for(int i=8;i>=5;i--)
    	scanf("%d",&after[i]);
```
- #### 判重问题
8个数排列组合一定，所以只需要判定前七个数就一定能知道最后一个数，这样就不会超出内存限制啦。然后用标记数组给这个七位数打个标记。
```cpp
int pan(int a[]){//自定义pan函数用来判重 
	int ans=0;
	for(int i=7;i>=1;i--)
		ans=ans*10+a[i];
	return ans;
}
```
- #### 三种操作
无脑模拟。
- #### 合理使用结构体使代码不复杂
- #### 尽量保证广搜框架完整
- #### 其他细节问题（各位dalao一定能自我解决）

下面就是~~大家期待~~的代码啦，祝大家题题AC！（~~代码刚好100行~~）

```cpp
#include <bits/stdc++.h>
using namespace std;
int after[9],ans,o,jishu;//after数组为目标状态，o和jishu为累加器辅助判断一些奇怪的东西 
bool fla[9000005],k;
struct sakura{//结构体 
	int before[9],f;char step;
}sak[100086];

int pan(int a[]){//自定义pan函数用来判重 
	int ans=0;
	for(int i=7;i>=1;i--)
		ans=ans*10+a[i];
	return ans;
}

bool judge(int a[]){
	for(int i=1;i<=8;i++)
		if(a[i]!=after[i])
			return 0;
	return 1;
}

void print(int a){//递归输出 
	if(sak[a].f!=0){
		o++;
		print(sak[a].f);
	}
	if(!sak[a].f) return;
	if(!k){//输出步数 
		printf("%d\n",o);
		k=1;
	}
	printf("%c",sak[a].step);
	jishu++;
	if(!jishu%60)//隔60个换行 
		printf("\n");
}
void bfs(){
	int h=0,t=1;sak[t].f=0;
	while(h<t){
		h++;
		for(int i=1;i<=3;i++){//保证框架完整 
			int bit[9];
			if(i==1){//A操作 
				for(int i=1;i<=4;i++){
					bit[i]=sak[h].before[i+4];
					bit[i+4]=sak[h].before[i];
				}					
			}
			if(i==2){//B操作 
				bit[1]=sak[h].before[4];bit[5]=sak[h].before[8];
				bit[2]=sak[h].before[1];bit[6]=sak[h].before[5];
				bit[3]=sak[h].before[2];bit[7]=sak[h].before[6];
				bit[4]=sak[h].before[3];bit[8]=sak[h].before[7];
			}
			if(i==3){//C操作 
				bit[1]=sak[h].before[1];
				bit[2]=sak[h].before[6];
				bit[3]=sak[h].before[2];
				bit[4]=sak[h].before[4];
				bit[5]=sak[h].before[5];
				bit[8]=sak[h].before[8];
				bit[7]=sak[h].before[3];
				bit[6]=sak[h].before[7];
			}
			if(!fla[pan(bit)]){
				t++;
				if(i==1) sak[t].step='A';
				if(i==2) sak[t].step='B';
				if(i==3) sak[t].step='C';
				fla[pan(bit)]=1;//标记 
				sak[t].f=h;//记录爸爸 
				for(int i=1;i<=8;i++)
					sak[t].before[i]=bit[i];
				if(ans==pan(bit)){
					print(t);
					exit(0);//万恶之源结束
				}
			}
		}
	}
}
int main(){
    for(int i=1;i<=8;i++){//降维打击！！！ 
    	if(i<=4) sak[1].before[i]=i;
    	if(i>4) sak[1].before[i]=13-i;
    }
    fla[pan(sak[1].before)]=1;
    for(int i=1;i<=4;i++)
    	scanf("%d",&after[i]);
    for(int i=8;i>=5;i--)
    	scanf("%d",&after[i]);
	ans=pan(after);
    if(ans==pan(sak[1].before)){//特判（貌似并不需要） 
    	printf("0\n");
    	return 0;
    }
    bfs();//万恶之源开始 
    return 0;
}
```

---

## 作者：嚯呀嚯呀 (赞：7)

**P党题解来袭！**

话说这道题目深搜和宽搜的时间差好大啊，深搜只有一个点A，其他全TLE了(可能是我深搜死循环了吧)

来看一看题目吧，这道题目一看就是搜索，但是怎么判重是一个问题，hash是一种很优秀的判重方法，我这里使用了BKDRHash。听起来很高大上，其实很简单.

```
seed:=31; point:=0;
for i:=1 to length(s) do
  point:=(point*seed+ord(s[i])) and $FFFF;
```
**这是一种很好的hash,冲突少，点紧凑，而且还好记。比赛中唯一要改的地方就是后面and 的部分。$表示后面的数字是16进制数，and $FFFF就可以把数据范围控制在6万多以内，而这题的状态数只有4万多，可以满足。    其他题目可以根据状态数改变F的个数，这个要自己算**

然后就是宽搜了,相信来做这道题目的人都会，小心一点都可以过了，还有一个难点是怎么输出方案，我这里用pro表示这个状态是由队列里第几个状态转移过来的，now表示转移到这个状态用了哪一种方案，然后递归输出就可以了

献上我丑陋的代码，dalao们随便看看吧
```
var
  head,tail,seed:longint;
  ans,a2,a1,i,j,m,n,k,p:longint;
  hash:array[0..70000]of string;
  a5,s,aim,t,a4:string;
  now:array[0..70000]of char;
  f:array[0..70000]of string;
  num,pro:array[0..70000]of longint;
function ha(t:string):longint;//hash
var
  point:longint;
begin
  point:=0;
  for i:=1 to 8 do
    point:=(point*seed+ord(t[i])) and $FFFF;
  while (hash[point]<>'%')and(hash[point]<>t) do
    begin
      inc(point);
      if point=70000 then point:=0;
    end;
  exit(point);
end;
begin
  seed:=31;
  for i:=1 to 8 do
    begin
      read(a1);
      aim:=aim+chr(a1+48);
    end;
  s:='12345678';
  for i:=0 to 70000 do
    hash[i]:='%';
  a2:=ha(s);
  hash[a2]:=s;
  if s=aim then//特判一开始就相同的情况(第2个点就是这样的)
    begin
      writeln('0');
      exit; 
    end;
  head:=0; tail:=1; f[1]:=s; num[1]:=0;//令人窒息的宽搜
  while head<tail do
    begin
      inc(head);
      a4:='';
      a4:=f[head][8]+f[head][7]+f[head][6]+f[head][5]+f[head][4]
      +f[head][3]+f[head][2]+f[head][1];
      p:=ha(a4);
      if hash[p]='%' then
        begin
          hash[p]:=a4;
          inc(tail); f[tail]:=a4; num[tail]:=num[head]+1;
          now[tail]:='A'; pro[tail]:=head;
          if a4=aim then
            begin
              ans:=tail; break;
            end;
        end;

      a4:='';
      a4:=f[head][4]+f[head][1]+f[head][2]+f[head][3]+f[head][6]
      +f[head][7]+f[head][8]+f[head][5];
      p:=ha(a4);
      if hash[p]='%' then
        begin
          hash[p]:=a4;
          inc(tail); f[tail]:=a4; num[tail]:=num[head]+1;
          now[tail]:='B'; pro[tail]:=head;
          if a4=aim then
            begin
              ans:=tail; break;
            end;
        end;

      a4:='';
      a4:=f[head][1]+f[head][7]+f[head][2]+f[head][4]+f[head][5]
      +f[head][3]+f[head][6]+f[head][8];
      p:=ha(a4);
      if hash[p]='%' then
        begin
          hash[p]:=a4;
          inc(tail); f[tail]:=a4; num[tail]:=num[head]+1;
          now[tail]:='C'; pro[tail]:=head;
          if a4=aim then
            begin
              ans:=tail; break;
            end;
        end;
    end;
  writeln(num[ans]);
  a5:='';
  while ans<>1 do
    begin
      a5:=a5+now[ans];
      ans:=pro[ans];
    end;
  for i:=length(a5) downto 1 do
    write(a5[i]);
end.

```
dalao们给个赞呗，谢谢

---

## 作者：空の軌跡 (赞：5)

  关于这道题，发现别的dalao们代码很长，其实用不了那么多，50行内就可以解决的

  ~~码风不好，不喜勿喷~~
  # 思路

  这道题一眼望去，就看到了 “**最少的操作**” 这几个字，所以显而易见是BFS

  关于BFS的代码，我觉得不成问题，主要的是题目要求输出顺序，可能有些人不晓

  得如何记录，其实开一个字符串记录就可以了

  然后由于只有八个方块，所以 bool 型开8维也没关系，可以记录所有的状态
  
 ~~这道题好水啊，为什么是蓝题，不就麻烦点吗~~

  # 代码
  ```
  #include<iostream>
  #include<cstdio>
  #include<algorithm>
  #include<queue>
  using namespace std;
  struct aq
  {
      int t,y,u,i,g,h,j,k,time;     //八个格子（你们可以看下自己的键盘上的那8个按键）和运转的次数
      string c;				     //保存路径的字符串
  }m,z;
  bool ok[9][9][9][9][9][9][9][9];  //判重的bool数组
  queue<aq>qa;				      //创建队列进行BFS
  int main()
  {
  	//读入目标数据，将初始状态调整并压入队列，开始BFS循环
      cin>>m.t>>m.y>>m.u>>m.i>>m.k>>m.j>>m.h>>m.g;
      m.time=0;
      qa.push((aq){1,2,3,4,8,7,6,5,0,""});
      ok[1][2][3][4][8][7][6][5]=1;
      while(!qa.empty())
      {
      	//取出队首元素并弹出
          z=qa.front();qa.pop();
          //判断是否达到目标状态，满足条件后输出并结束程序
          if(z.t==m.t&&z.y==m.y&&z.u==m.u&&z.i==m.i&&z.g==m.g&&z.h==m.h&&z.j==m.j&&z.k==m.k)
          {
              cout<<z.time<<"\n"<<z.c;
              return 0;
          }
          //模拟三个操作，并将操作保存在c字符串中
          if(!ok[z.g][z.h][z.j][z.k][z.t][z.y][z.u][z.i])
          {
              ok[z.g][z.h][z.j][z.k][z.t][z.y][z.u][z.i]=1;
              qa.push((aq){z.g,z.h,z.j,z.k,z.t,z.y,z.u,z.i,z.time+1,z.c+"A"});
          }
          if(!ok[z.i][z.t][z.y][z.u][z.k][z.g][z.h][z.j])
          {
              ok[z.i][z.t][z.y][z.u][z.k][z.g][z.h][z.j]=1;
              qa.push((aq){z.i,z.t,z.y,z.u,z.k,z.g,z.h,z.j,z.time+1,z.c+"B"});
          }
          if(!ok[z.t][z.h][z.y][z.i][z.g][z.j][z.u][z.k])
          {
              ok[z.t][z.h][z.y][z.i][z.g][z.j][z.u][z.k]=1;
              qa.push((aq){z.t,z.h,z.y,z.i,z.g,z.j,z.u,z.k,z.time+1,z.c+"C"});
          }
      }
  }
  ```

---

## 作者：「　」 (赞：5)

# 不会康拓的同学们看这里！！  
### 表示作者的朋友都太厉害了，经过为时30分钟的思考就想出了康拓展开（他在此之前都还不了解康拓[@wasa855](https://www.luogu.org/space/show?uid=70780)）  
### 但作者是一个不会康拓的蒟蒻，所以怎么办呢？  
### 本题十分明显，如果用8进制的权值记录，进行判重，有百分之80的几率MLE（可能更高，作者没有尝试过）。  
### 所以作者就想出了一种神奇的方法，而应用的知识，仅仅是：
## 二分查找  
### 下面就进入正题，如何二分呢？  
### 当然是~~打一张巨表~~了  
### 贴代码：  
```cpp
for(int i=1;i<=8;++i)
{
    s[l].a[i]=i;
}
for(int i=1;i<=40320;++i)
{
    for(int j=1;j<=8;++j)
    {
        f[i].a[j]=s[l].a[j];
    }
    next_permutation(s[l].a+1,s[l].a+1+8);
}
```  
### 传说中的巨表！！！  
### 眼尖的同学可能发现了，next_permutation是什么呢？  
### 这其实是一个神奇的全排列函数，可以帮你求下一个排列，是C++的STL库< algorithm >中的函数。（请大家打开P1088，用这个函数水过）  
### 再进行二分：  
```cpp
int big_small(int a[],int b[])
{
    for(int i=1;i<=8;++i)
    {
        if(a[i]>b[i])
        return 1;
        if(a[i]<b[i])
        return -1;
    }
    return 0;
}
bool used(int a[])
{
    int l=1,r=40320,mid,t;
    while(l<=r)
    {
        mid=(l+r)/2;
        t=big_small(f[mid].a,a);
        if(t>0)
        r=mid-1;
        if(t<0)
        l=mid+1;
        if(t==0)
        break;
    }
    if(f[mid].n==false)
    {
        f[mid].n=true;
        return false;
    }
    else
    return true;
}
```  
### 以上就是判重的思路，然而最重要的，其实是广搜（不要告诉我你不会！！！）  
### 大佬wasa855说，深搜和广搜就是傻子和聪明人走迷宫的区别。  
### 深搜就是傻子一个劲的往里冲，碰到不能走或者边界（边界好像也不能走），就往回走（回溯）广搜呢，就是聪明人，他们把能走的都先看一遍，再往下走。  
### 不过傻子和聪明人各有所长，大家要因题而异。（不要因为我说深搜是傻子就不用）  
### 最后贴代码，祝大家题题AC：  
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
struct Squares
{
    int a[9];
    int n;
    char p[100];
}s[40321];
struct squares
{
    int a[9];
    bool n;
}f[40321];
int ans[9];
int l=0,r=1;
int t1,t2;
bool cmp(int a[])
{
    for(int i=1;i<=8;++i)
    {
        if(a[i]!=ans[i])
        return false;
    }
    return true;
}
int big_small(int a[],int b[])
{
    for(int i=1;i<=8;++i)
    {
        if(a[i]>b[i])
        return 1;
        if(a[i]<b[i])
        return -1;
    }
    return 0;
}
bool used(int a[])
{
    int l=1,r=40320,mid,t;
    while(l<=r)
    {
        mid=(l+r)/2;
        t=big_small(f[mid].a,a);
        if(t>0)
        r=mid-1;
        if(t<0)
        l=mid+1;
        if(t==0)
        break;
    }
    if(f[mid].n==false)
    {
        f[mid].n=true;
        return false;
    }
    else
    return true;
}
void A()
{
    s[r]=s[l];
    for(int i=1;i<=4;++i)
    {
        t1=s[r].a[i];
        s[r].a[i]=s[r].a[8-i+1];
        s[r].a[8-i+1]=t1;
    }
    if(used(s[r].a)==true)
    {
        return ;
    }
    s[r].p[s[r].n]='A';
    ++s[r].n;
    ++r;
}
void B()
{
    s[r]=s[l];
    t1=s[r].a[4];
    t2=s[r].a[5];
    for(int i=4;i>=2;--i)
    {
        s[r].a[i]=s[r].a[i-1];
        s[r].a[8-i+1]=s[r].a[8-i+2];
    }
    s[r].a[1]=t1;
    s[r].a[8]=t2;
    if(used(s[r].a)==true)
    {
        return ;
    }
    s[r].p[s[r].n]='B';
    ++s[r].n;
    ++r;
}
void C()
{
    s[r]=s[l];
    t1=s[r].a[2];
    s[r].a[2]=s[r].a[7];
    s[r].a[7]=s[r].a[6];
    s[r].a[6]=s[r].a[3];
    s[r].a[3]=t1;
    if(used(s[r].a)==true)
    {
        return ;
    }
    s[r].p[s[r].n]='C';
    ++s[r].n;
    ++r;
}
int main()
{
    for(int i=1;i<=8;++i)
    {
        scanf("%d",&ans[i]);
    }
    f[1].n==true;
    for(int i=1;i<=8;++i)
    {
        s[l].a[i]=i;
    }
    for(int i=1;i<=40320;++i)
    {
        for(int j=1;j<=8;++j)
        {
            f[i].a[j]=s[l].a[j];
        }
        next_permutation(s[l].a+1,s[l].a+1+8);
    }
    for(int i=1;i<=8;++i)
    {
        s[l].a[i]=i;
    }
    while(1)
    {
        if(cmp(s[l].a)==true)
        break;
        A();
        B();
        C();
        ++l;
    }
    printf("%d",s[l].n);
    for(int i=0;i<s[l].n;++i)
    {
        if(i%60==0)
        printf("\n");
        printf("%c",s[l].p[i]);
    }
}
```  
### 不知是数据太水还是正解，反正AC！！！

---

## 作者：吴思余 (赞：5)

看到都是康拓，set之类的。这题的第一眼想法不应该是trie字典树吗？既快又好写，空间还小，新人肯定都喜欢这么写。发篇题解顺便吐槽下。
```cpp
#include <iostream>
#include <queue>
#include <algorithm>
#define lemon(i,a,b) for(int i=(a);i<=(b);i++)
#define Lemon(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
struct stage
{
	int a[10];
};
stage tar;
stage start;
stage tr[10000001];
int top=1;
void ins(stage now,int dep,int rt)//字典树插入 
{
	if(dep>8) return;
	if(tr[rt].a[now.a[dep]]) ins(now,dep+1,tr[rt].a[now.a[dep]]);
	else
	{
		tr[rt].a[now.a[dep]]=++top;
		ins(now,dep+1,tr[rt].a[now.a[dep]]);
	}
}
bool check(stage now)
{
	lemon(i,1,8) if(now.a[i]!=tar.a[i]) return false;//lemon(i,1,8)=for(int i=1;i<=8;i++)
	return true;
}
stage cA(stage now)//A操作 
{
	lemon(i,1,4) swap(now.a[i],now.a[8-i+1]);
	return now;
}
stage cB(stage now)//B操作 
{
	int tmp[4];
	tmp[1]=now.a[4];tmp[2]=now.a[5];
	lemon(i,5,7) now.a[i]=now.a[i+1];
	Lemon(i,4,2) now.a[i]=now.a[i-1];//Lemon(i,4,2)=for(int i=4;i>=2;i--)
	now.a[1]=tmp[1];
	now.a[8]=tmp[2];
	return now;
}
stage cC(stage now)//C操作 
{
	int tmp;
	tmp=now.a[2];
	now.a[2]=now.a[7];
	now.a[7]=now.a[6];
	now.a[6]=now.a[3];
	now.a[3]=tmp;
	return now;
}
bool find(stage now,int dep,int rt)//字典树查询 
{
	if(dep>8) return true;
	if(tr[rt].a[now.a[dep]]) return find(now,dep+1,tr[rt].a[now.a[dep]]);
	else return false;
}
int main()
{
	lemon(i,1,8) start.a[i]=i;
	lemon(i,1,8) cin >> tar.a[i];
	ins(start,1,1);
	queue <pair<stage,string> > q;
	string s;
	q.push(make_pair(start,s));
	while(!q.empty())
	{
		stage now=q.front().first;
		string nows=q.front().second;
		q.pop();
		if(check(now))
		{
			cout << nows.length() << endl;
			cout << nows << endl;
			return 0;
		}
		stage tmp;
		tmp=cA(now);
		if(!find(tmp,1,1)) q.push(make_pair(tmp,nows+"A")),ins(tmp,1,1);//A转换可以则入队，计入树中，并且累加字符A 
		tmp=cB(now);
		if(!find(tmp,1,1)) q.push(make_pair(tmp,nows+"B")),ins(tmp,1,1);//同上 
		tmp=cC(now);
		if(!find(tmp,1,1)) q.push(make_pair(tmp,nows+"C")),ins(tmp,1,1);//同上 
	}
	return 0;
}
```

---

## 作者：Zimo (赞：5)

菜OJ题号：[1047](http://caioj.cn/problem.php?id=1047)

洛谷题号：[P2730](https://www.luogu.org/problemnew/show/P2730)

题目请自己向上看。这里没有。

此题很明显是宽搜（广搜）。

并且还要用康托展开。

[菜OJ康托展开（内含文档）](http://caioj.cn/problem.php?id=1220)

康托不会就看上面吧，宽搜不会就别来了吧。。。

##### 我的思路：

首先魔板读入时候下面一行反着读，就会让表达的方式转换成我们平常的表达方式

例如：

1 2 3 4

8 7 6 5     用{{1,2,3,4},{8,7,6,5}}表示而不是{{1,2,3,4},{5,6,7,8}}

建一个操作（A、B、C）函数，给定A或B或C和一个魔板结构体，返回操作后的结构体。

操作都储存在结构体里，每个结构体一个字符数组，每次都继承列表里上次的操作并加上自己的

用康托和宽搜你们也应该知道怎么做了

##### 代码：

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
struct node
{
    int a[3][5],dep;
    char st[500];
}list[110000];
int head,tail;
int d[10];
bool myhash[400000];
int kangtuo(node tno)
{
    int sum=0,b[10],len=0;
    for(int i=1;i<=2;i++)
        for(int j=1;j<=4;j++)
            b[++len]=tno.a[i][j]+1;
    bool bo[20];memset(bo,0,sizeof(bo));
    for(int i=1;i<=7;i++)
    {
        int k=0;
        for(int j=1;j<b[i];j++)
            if(bo[j]==false) k++;
        sum+=k*d[8-i];bo[b[i]]=true;
    }
    return sum+1;
}
node Cz(node tno,char mode)
{
    if(mode=='A')
    {
        int a;
        for(int i=1;i<=4;i++)
            {a=tno.a[1][i];
            tno.a[1][i]=tno.a[2][i];
            tno.a[2][i]=a;}
        return tno;
    }
    if(mode=='B')
    {
        int a[2];
        a[1]=tno.a[1][4];a[2]=tno.a[2][4];
        for(int i=4;i>=2;i--)
        {tno.a[1][i]=tno.a[1][i-1];
        tno.a[2][i]=tno.a[2][i-1];}
        tno.a[1][1]=a[1];tno.a[2][1]=a[2];
        return tno;
    }
    if(mode=='C')
    {
        int a[5];
        a[1]=tno.a[1][2];a[2]=tno.a[1][3];
        a[3]=tno.a[2][3];a[4]=tno.a[2][2];
        tno.a[1][2]=a[4];tno.a[1][3]=a[1];
        tno.a[2][3]=a[2];tno.a[2][2]=a[3];
        return tno;
    }
}
main()
{
    int tt;
    memset(myhash,false,sizeof(myhash));
    d[0]=1;
    for(int i=1;i<=8;i++) d[i]=d[i-1]*i;
    list[1].a[1][1]=1;list[1].a[1][2]=2;list[1].a[1][3]=3;list[1].a[1][4]=4;
    list[1].a[2][1]=8;list[1].a[2][2]=7;list[1].a[2][3]=6;list[1].a[2][4]=5;
    list[1].dep=0;
    myhash[kangtuo(list[1])]=true;
    for(int j=1;j<=4;j++) scanf("%d",&list[0].a[1][j]);
    for(int j=4;j>=1;j--) scanf("%d",&list[0].a[2][j]);
    int ed=kangtuo(list[0]);
    if(myhash[ed]==true) {printf("0");return 0;}
    int head=1,tail=1;
    node tno;
    while(head<=tail)
    {
        for(char i='A';i<='C';i++)
        {
            tno=Cz(list[head],i);
            tno.dep=list[head].dep+1;
            int now=kangtuo(tno);
            if(myhash[now]==false)
            {
                strcpy(list[head].st,tno.st);
                tno.st[tno.dep]=i;
                if(now==ed)
                {
                    printf("%d\n",tno.dep);
                    for(int i=1;i<=strlen(tno.st+1);i++)
                        {printf("%c",tno.st[i]);
                        if(i%60==0) printf("\n");}
                    return 0;
                }
                list[++tail]=tno;
                myhash[now]=true;
            }
        }
        head++;
    }
}
```

---

## 作者：Log_x (赞：4)

##**分析** 哈希表 + 广度优先搜索

- 看到这样的题目应该很容易想到搜索，但如果用深度优先搜索做，则可能会一直无法变换到目标状态，从而导致死循环，所以我们只能用广度优先搜索，那么最先搜到的步数肯定最少。而问题的关键在于如何对已经搜索过的状态进行判重，于是对于这一类的问题，我们很容易想到哈希表。

- 考虑一种最为简单的思路，把一种状态中的八个数字对应转换成八位十进制数上的某一位上，但这样是存储不下的。我们想到除余法，发现共有全排列$8!=40320$个情况。于是我们设的模数大概是比$40320$稍大的素数，然后将每一种情况对应到哈希表中。（膜拜用康托展开做的大神）

- 鉴于本题的特殊性，其实我们还可以考虑另一种较为简便的哈希函数，因为状态只包含这八个数字，我们统一令其减一，则我们就可以将这八个数字作为一个八位八进制数上的每一位，也就是**基数转换法**。

- 这样做的优点在哪呢？我们会发现最大的状态$(76543210)_8=(16434824)_{10}$，那么我们只要开一个大约$1650$万的$bool$数组就可以直接用来判重了，而不需要再使用除余法等等的操作。并且每一种状态是唯一的，也不可能发生冲突的情况，另外转成八进制数的乘以$8$也可以用位运算中的右移来快速实现。

##**代码**

```cpp
#include <iostream>
#include <cstdio>

using namespace std;
const int N = 5e4 + 5, M = 165e5;
const int G[3][9] = {{0, 8, 7, 6, 5, 4, 3, 2, 1}, 
                     //操作A：交换上下两行 
                      {0, 4, 1, 2, 3, 6, 7, 8, 5}, 
                     //操作B：将最右边的一列插入最左边 
                      {0, 1, 7, 2, 4, 5, 3, 6, 8}};
                     //操作C：魔板中央四格作顺时针旋转 

//我们可以用一个常量数组来简单地表示ABC三种操作 
//即经过这一次操作后，现在状态中的第i个位置是有原先的哪一个位置变换来的 

int h[N][9], a[9], pf[N][2]; char stk[N];
int t, w = 1, x, edt, now, top;
bool vis[M]; //用于判重的bool数组 
                     
int main()
{
    for (int i = 1; i <= 8; ++i)
     scanf("%d", &x), edt = (edt << 3) + x - 1;
    //同样将目标状态转换为八进制数，便于我们直接判断 
    for (int i = 1; i <= 8; ++i) 
     now = (now << 3) + (h[1][i] = i - 1);
    //“<< 3”即表示位运算的右移三位，也就是乘以8 
    vis[now] = true; //注意初始状态也要标记为已经搜索过 
    if (now == edt) return puts("0"), 0;
    //注意如果初始状态和目标状态相同应直接退出 
    while ((t++) < w)
    {
        for (int i = 0; i < 3; ++i)
        //对于答案中的操作字典序问题，我们考虑按照操作ABC的顺序搜索
        //这样先搜索到的一定是字典序最小的 
        {
            now = 0;
            for (int j = 1; j <= 8; ++j) 
             now = (now << 3) + (a[j] = h[t][G[i][j]]);
            //计算经过转换后的状态 
            
            if (vis[now]) continue; //判重 
            vis[now] = true;
            pf[++w][0] = t; pf[w][1] = i + 'A';
            //因为题目中要求输出操作序列
            //记录队列中每一个元素是由之前的哪一个元素、经过哪一个操作转换来的
            //然后按着当前搜到的目标状态倒着找回去，再顺着输出操作就是答案了 
            h[w][0] = h[t][0] + 1;
            for (int j = 1; j <= 8; ++j) h[w][j] = a[j];
        
            if (now == edt) //转换到了目标状态 
            {
                printf("%d\n", h[w][0]); x = w;
                while (pf[x][0]) stk[++top] = pf[x][1], x = pf[x][0];
                //数组stk即记录转换到目标状态依次进行的操作 
                for (int i = top; i >= 1; --i) putchar(stk[i]);
                return 0;
            }
        }
    }
    return 0;
}
```

---

## 作者：EarthGiao (赞：3)

其实是普通的bfs。但是三种情况处理起来比较麻烦。

判重咱用的是map。

然后12345678是
1234
8765
然后存用12345678的话就比较麻烦，于是我存的话就是12348765，处理起来也方便一些。

读入的目标状态我们存的时候也做下处理，如样例：26845731，我们存的话是26841375。这样判断是否搜到的时候会比较方便。

三种情况的处理话自己推一下就出来了，见代码。‘

```cpp
#include<set> 
#include<map> 
#include<list> 
#include<queue> 
#include<stack> 
#include<string> 
#include<math.h> 
#include<time.h> 
#include<vector> 
#include<bitset> 
#include<memory> 
#include<utility> 
#include<stdio.h> 
#include<sstream> 
#include<iostream> 
#include<stdlib.h> 
#include<string.h> 
#include<algorithm>
#define LL unsigned long long  
using namespace std;
map<int,bool> f;//判重用
int i,l,r;
int x,xx;
int fff=0;
struct haha
{
    int pred;//存上一个在队列中的位置
    char c;//存操作方式的
    int n;//存当前状态的
    int sum;//存当前操作的长度
} a[500000];
void digui(int k)//递归倒着输出
{
    if (a[k].pred!=-1)digui(a[k].pred);
    if (a[k].pred!=-1)printf("%c",a[k].c);
    return;
}
void sc(int x)//输出
{
    printf("%d\n",a[x].sum);
    fff=1;
    digui(x);
    printf("\n");
    return;
}
void aa(int k)//操作A
{
    int an=k/10000;//第一行
    int bn=k%10000;//第二行
    int d=bn*10000+an;//第一行与第二行进行交换
    if (f[d]==1) return;//去重
    //printf("A:%d %d sum:%d\n",r+1,d,a[l].sum+1);
    f[d]=1;//标记
    r++;//入队
    a[r].pred=l;//标记上一个
    a[r].c='A';//标记为操作A
    a[r].n=d;
    a[r].sum=a[l].sum+1;//记操作次数
    if (d==x) sc(r);//找到了就输出
    return;
}
 
void bb(int k)//操作B
{
    int an=k/10000;//第一行
    int bn=k%10000;//第二行
    an=(an%10)*1000+(an/10);//最后一列插入到第一列
    bn=(bn%10)*1000+(bn/10);//最后一列插入到第一列
    int d=an*10000+bn;
    if (f[d]==1) return;//去重
    //printf("B:%d %d sum:%d\n",r+1,d,a[l].sum+1);
    f[d]=1;//标记
    r++;//入队
    a[r].pred=l;//标记上一个
    a[r].c='B';//标记为操作B
    a[r].n=d;
    a[r].sum=a[l].sum+1;//记操作次数
    if (d==x) sc(r);//找到了就输出 
    return;
}
 
void cc(int k)//操作C，好坑啊。
{
    int an=k/10000;//第一行
    int bn=k%10000;//第二行
    int rr=an;//存an修改前的值
    an=(an/1000*1000)/*第一位不变*/
    +(bn/100%10*100)/*第二位来自第二行*/
    +(an/100%10*10)/*第二位成第三位*/
    +(an%10);/*最后一位不变*/
    bn=(bn/1000*1000)/*第一位不变*/
    +(bn%100/10*100)/*第三位变成第二位*/
    +(rr%100/10*10)/*来自第一行的第三位*/
    +(bn%10);/*最后一位不变*/
    //这处理，我TM要炸了。
    int d=an*10000+bn;
    if (f[d]==1) return;//去重
    //printf("C:%d %d sum:%d\n",r+1,d,a[l].sum+1);
    f[d]=1;//标记
    r++;//入队
    a[r].pred=l;//标记上一个
    a[r].c='C';//标记为操作B
    a[r].n=d;
    a[r].sum=a[l].sum+1;//记操作次数
    if (d==x) sc(r);//找到了就输出 
    return;
}
int main()
{
    freopen("msquare.in","r",stdin);
    freopen("msquare.out","w",stdout);
    int xxx=0;
    for (i=1;i<=8;i++)
    {
        scanf("%d",&xx);//读入
        xxx=xxx*10+xx;
    }
    x=xxx/10000;
    xxx=xxx%10000;//保留最后四位
    x=x*10000//前4位不变
    +(xxx%10*1000)
    +(xxx%100/10*100)
    +(xxx/100%10*10)
    +(xxx/1000);
    if (x==12348765)//不需要变动
    {
        printf("0\n\n");
        return 0;
    }
    //printf("x:%d\n",x);
    f[12348765]=1;//标记
    l=0;
    r=1;
    a[1].n=12348765;
    a[1].pred=-1;
    while (l!=r)
    {
        l++;
        aa(a[l].n);//三种操作
        if (fff==1) return 0;
        bb(a[l].n);
        if (fff==1) return 0;
        cc(a[l].n);
        if (fff==1) return 0;
    }
    return 0;
}
``                      
         

---

## 作者：syksykCCC (赞：3)

~~哈哈看见题解有29篇，马上要达到30的临界值了，故来凑个整~~

其实是看见各位大佬的代码都很难懂（~~我太蒟了~~），所以来和大家分享一下我的代码哈！希望大家喜欢

### 时间效率：46ms, 3972KB ，~~应该还不错~~

个人思路很简单，通过$BFS$来寻找最优方案，关于判重使用的是$\text{康拓展开}$，具体实践看代码吧！

这里提出一个节省空间的思路：因为数字只有$0\sim8$，可以用`char[]`来代替`int[]`，起到节省$3/4$空间的作用

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 12;
const int S = 50000; // S > 8!
/*
A, B, C 三种方法的操作
以TA为例 TA[i]表示的是以A方法操作一次后第i位上的是原来第TA[i]位上的数 
*/
const int TA[S] = { 0, 8, 7, 6, 5, 4, 3, 2, 1 };
const int TB[S] = { 0, 4, 1, 2, 3, 6, 7, 8, 5 };
const int TC[S] = { 0, 1, 7, 2, 4, 5, 3, 6, 8 };

int fact[N], cnt = 1; // fact为康拓展开的阶乘数组
bool vis[S]; // 判重数组 
char state[S][N], goal[N]; // state[]用来记录所有的状态，goal是目标 
string way[S]; // way[i]代表编号为i的状态对应的操作串  

void calc_fact() // 康拓展开的预处理 
{
    fact[0] = 1;
    for (int i = 1; i <= 9; i++) fact[i] = fact[i - 1] * i;
}
int contor(char *perm) // 康拓展开：将全排列perm[]映射为一个编码code 
{
    int code = 0;
    for (int i = 1; i <= 8; i++) 
	{
        int cnt = 0;
        for (int j = i + 1; j <= 8; j++) cnt += perm[i] > perm[j];
        code += fact[8 - i] * cnt;
    }
    return code;
}

void bfs() 
{
    queue<int> que; // 注意，que里面存放的不是状态，而是状态编号 
    que.push(1); // 加入初始状态 
    vis[0] = true; // 1,2...8 的contor值为0 
    while (!que.empty()) 
	{
        int u = que.front(); // 取出当前状态 
        que.pop();
        char A[S], B[S], C[S]; // 存放三种操作后的状态 
        for (int i = 1; i <= 8; i++) // 计算状态 
		{
            A[i] = state[u][TA[i]];
            B[i] = state[u][TB[i]];
            C[i] = state[u][TC[i]];
        }
        int cA = contor(A), cB = contor(B), cC = contor(C); // 求出contor值 
        if (!vis[cA]) // 如果还没访问过 
		{
            strcpy(state[++cnt] + 1, A + 1); // 将新状态存入 
            way[cnt] = way[u] + 'A'; // 通过当前编号的操作串推出新编号的操作串 
            vis[cA] = true; // 去重 
            que.push(cnt); // 入队 
            if (!strcmp(A + 1, goal + 1)) // 发现目标 
                return;
        }
        // 下文B, C同理 
        if (!vis[cB]) 
		{
            strcpy(state[++cnt] + 1, B + 1);
            way[cnt] = way[u] + 'B';
            vis[cB] = true;
            que.push(cnt);
            if (!strcmp(B + 1, goal + 1))
                return;
        }
        if (!vis[cC]) 
		{
            strcpy(state[++cnt] + 1, C + 1);
            way[cnt] = way[u] + 'C';
            vis[cC] = true;
            que.push(cnt);
            if (!strcmp(C + 1, goal + 1))
                return;
        }
    }
}
int main() 
{
    calc_fact(); // 预处理 
    for (int i = 1; i <= 8; i++) 
	{
        scanf("%d", &goal[i]);
        goal[i] += 48; // 数字转字符 
        state[1][i] = i + 48; // 存入初始全排列 
    }
    if (!strcmp(goal + 1, state[1] + 1)) // 特判：如果目标就是初始全排列就直接退出 
        return puts("0") && 0;
    bfs();
    printf("%d\n", way[cnt].size());
    for (int i = 0; i < way[cnt].size(); i++) 
	{
        printf("%c", way[cnt][i]);
        if ((i + 1) % 60 == 0) // 换行处理 
            puts("");
    }
    return 0;
}
```

~~如果喜欢我的码风，麻烦点个赞哈~~

## Update
我来补充说一下这题的几种不同的判重方法供大家参考

### $1.\text{康拓展开}$
 本文即是
### $2.hash$
 通过将八位数字转化为一个数存入哈希表内进行判重，大家可以参考我[P1379 八数码难题](https://www.luogu.org/problemnew/show/P1379)的[代码](https://www.luogu.org/paste/bnqaod4i)
### $3.M\!AP$
看了一下题解圈，发现 @[getchar123](https://www.luogu.org/space/show?uid=102754)的[题解](https://www.luogu.org/blog/getchar123/solution-p2730)就是这么写的，~~不过常数比较大~~，大家可以去看

---

## 作者：0Zero丶紫瞳 (赞：3)

# P2730 / USACO 3.2 魔板~~(模板)~~
### 算法：BFS
###### 135ms, 77584KB
 _本蒟蒻的第一篇题解_ 
 
[本题链接](https://www.luogu.org/problemnew/show/P2730)

这个魔板共有 8 位，所以最多也就会出现 8！种情况。

因为是求变化次数最少的解决方案，所以重复的情况不用再次搜索，广搜 O(8!) 的复杂度是不会T的。

我们可以从最初12345678开始搜索，达到读入的目标为止。每次搜索三种操作能到的状态。

记录的话就用一个结构体，一个 8 位整数记录魔板的状态 _(但是会有许多空间是浪费的，用 康托展开 可以优化一下，但是本蒟蒻不会)_ ，一个数记录到达这个状态的最小步数，一个字符串记录达到这步进行的操作。

![](https://s1.ax1x.com/2018/09/11/ikkv80.png)
# 图中A后面第一行是8765，手滑打错了，感谢 @撩妹凛酱 的提醒
```cpp
#include<bits/stdc++.h>
using namespace std;

	bool b[87654322];//判断重复。如果再次达到，已经不是最优，而且会死循环
	int t,h,a，
    	gol,	//因为输入是用空格隔开的，这里用一个整数记录目标状态
        nxt,	//记录状态，用于每次搜索前对于下一步可行性的判断 以及为下一状态赋值
        ansstep;//最小步数
	struct bfs	//用于广搜的队列
	{
		int z,step;	//z是状态，step是本状态最小步数
		string cz;	//已经进行的操作
	}dl[40325];		//8！应该已经够用了
	string ans;		//记录要输出的方案
	
int A(int a)
{
	int b = 0;
	for(int i = 1; i <= 8; i++)
	{
		b = b*10+a%10;
		a /= 10;
	}
	return b;
}
int B(int a)
{
	int w[10]={0},b = 0;
	for(int i = 1; i <= 8; i++)
	{
		w[i] = a%10;
		a /= 10;
	}					//把每一位取出，转换成下一步的状态
	b = w[5]*10000000
	   +w[8]*1000000
       +w[7]*100000
       +w[6]*10000
       +w[3]*1000
       +w[2]*100
       +w[1]*10
       +w[4];
	return b;
}
int C(int a)
{
	int w[10]={0},b = 0;
	for(int i = 1; i <= 8; i++)
	{
		w[i] = a%10;
		a /= 10;
	}
	b = w[8]*10000000
       +w[2]*1000000
	   +w[7]*100000
	   +w[5]*10000
	   +w[4]*1000
	   +w[6]*100
       +w[3]*10
       +w[1];
	return b;
}
string s()
{
	dl[++t].z=12345678;
	b[12345678] = 1;
	while(h<t)
	{
		h++;
		if(dl[h].z == gol)	//如果到达目标，输出步数并返回方案
		{
			ansstep = dl[h].step;
			cout<<dl[h].step<<endl;
			return dl[h].cz;
		}
		if(!b[nxt = A(dl[h].z)])
		{
			dl[++t].z = nxt;
			dl[t].cz = dl[h].cz + "A";
			b[dl[t].z] = 1;
			dl[t].step = dl[h].step + 1;
		}
		if(!b[nxt = B(dl[h].z)])
		{
			dl[++t].z = nxt;
			dl[t].cz = dl[h].cz + "B";
			b[dl[t].z] = 1;
			dl[t].step = dl[h].step + 1;
		}
		if(!b[nxt = C(dl[h].z)])
		{
			dl[++t].z = nxt;
			dl[t].cz = dl[h].cz + "C";
			b[dl[t].z] = 1;
			dl[t].step = dl[h].step + 1;
		}
	}
}
int main()
{
ios::sync_with_stdio(false);	//我就是流输入T掉，优化ce，也不会再碰格式化输入输出一次！ ~~真香~~
	for(int i = 1; i <= 8; i++)
	{
		cin>>a;
		gol = gol*10 + a;		//把输入的 8 个数变为一个整数
	}
	ans = s();
	for(int i = 0; i <= ansstep; i+=60)//每60个字符换一次行
	{
		cout<<ans.substr(i,i+59)<<endl;
        /*
        cout<<str.substr(i,i+n)
        输出 str[i] 到 str[i+n] 闭区间，共 n+1 位 
		*/
    }
return 0;
}
```
 _第一次写，不太会用，感觉格式好奇怪啊。。。_ 

---

## 作者：feng_chengjie (赞：3)

这个题可以用广搜，在搜出每个状态之后可以用康托展开来判重（康托展开其实是另一种哈希，他把字符串的位置信息与值联系起来），但是一定要用map作为VIS数组，因为康托会很大。

剩下的前辈们已经讲得很清楚了，就是强调一下map，要不然交到USACO上会RE


/\*
ID: linda\_f1

PROG: msquare

LANG: C++

\*/










```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <map>
using namespace std;
int fac[9]={1,1,2,6,24,120,720,5040,40320};//contor 
struct point
{
    int a[10];
    int n;
    int step;
}p[80000];
int goal,bas,tot=0;
int f[50320];
map<int,bool> vis;
int contor(int t)
{
    int num=0,k=0;
    for(int i=1;i<=8;i++)
    {
        k=0;
        for(int j=i+1;j<=8;j++)
            if(p[t].a[i]>p[t].a[j]) 
                k++;
        num+=k*fac[8-i];
    }
    return num;
}
void init()
{
    for(int i=1;i<=4;i++)
        p[1].a[i]=i;
    for(int i=5;i<=8;i++)
        p[1].a[i]=13-i;
    vis[contor(1)]=true;
}
void out(int t)
{
    if(t==1)
        return;
    out(f[t]);
    if(f[t]==1)
        cout<<tot<<endl;
    if(p[t].n==1)
        cout<<"A";
    if(p[t].n==2)
        cout<<"B";
    if(p[t].n==3)    
        cout<<"C";
}
void A(int t)
{
    swap(p[t].a[1],p[t].a[5]);
    swap(p[t].a[2],p[t].a[6]);
    swap(p[t].a[3],p[t].a[7]);
    swap(p[t].a[4],p[t].a[8]);
}
void B(int t)
{
    swap(p[t].a[4],p[t].a[3]);swap(p[t].a[8],p[t].a[7]);
    swap(p[t].a[3],p[t].a[2]);swap(p[t].a[7],p[t].a[6]);
    swap(p[t].a[2],p[t].a[1]);swap(p[t].a[6],p[t].a[5]);
}
void C(int t)
{
    swap(p[t].a[2],p[t].a[3]);
    swap(p[t].a[2],p[t].a[7]);
    swap(p[t].a[2],p[t].a[6]);
}
void bfs()
{
    int h=0,t=1;
    p[1].step=0;
    while(h<=t)
    {
        h++;
        for(int i=1;i<=3;i++)
        {
            t++;
            for(int j=1;j<=8;j++)
                p[t].a[j]=p[h].a[j];
            if(i==1) A(t);
            if(i==2) B(t);
            if(i==3) C(t);
            bas=contor(t);
            if(vis[bas]) t--;
            else
            {
                vis[bas]=1;
                p[t].step=p[h].step+1;
                p[t].n=i;
                tot=p[t].step;
                f[t]=h;
                if(goal==bas)
                {
                    out(t);
                    return ;                    
                }
            }                            
        }
    }
}
int main()
{
    freopen("msquare.in","r",stdin);
    freopen("msquare.out","w",stdout);
    init();//建立基本态
    for(int i=1;i<=4;i++)
        cin>>p[0].a[i];
    for(int i=5;i<=8;i++)
        cin>>p[0].a[13-i];
    goal=contor(0);
    int ff=0;
    if(vis[goal]) 
    {
        cout<<0<<endl;
        ff=1;
    //    return 0;
    }
    if(!ff)
    bfs();
    cout<<endl;
    return 0;
}

```

---

## 作者：____蒟蒻____ (赞：2)

这里提供一种面向对象思想的写法

###  基本思路

首先这题看一眼感觉数据很小是个广搜~~虽然我还是写了迪杰斯特拉不过这不重要~~，关键问题还是在于如何判重以及进行状态转移（就是三种操作）。

最简单的想法是用字符串表示表示每个魔板，但是我感觉字符串操作很麻烦所以就用了一种更加舒服~~奇奇怪怪~~的方法：面向对象编程（其实stl里面那些容器能当做函数参数传递也是因为面向对象，所以用这种方法可以把很多复杂的状态变成一个struct或者class传递，然后就可以舒服的广搜了（比如[孤岛营救行动](https://www.luogu.org/problem/P4011)）

所以我们可以写出一个雏形

```cpp
struct Block {
	int arr[2][4];
	
	Block() {} // 默认构造函数
	Block(const Block& p) {} // 复制构造函数
	
	bool operator < (const Block &b) const {} //以下是所有比较运算符
	bool operator > (const Block &b) const {}
	bool operator <= (const Block &b) const {}
	bool operator >= (const Block &b) const {}
	bool operator == (const Block &b) const {}
	bool operator != (const Block &b) const {}
	
	inline Block operateA() {} // 操作A
	inline Block operateB() {} // 操作B
	inline Block operateC() {} // 操作C
};
```

然后就可以在stl队列里面直接传递Block类进行bfs

### struct中的函数实现

~~似乎struct中的成员函数是默认inline可以不写emmm但是我还是写了~~

首先考虑默认构造函数，把魔板设置成初始状态，于是简单模拟一下就可以得到结果

```cpp
Block() {
    int cnt = 1;
    for (int i = 0; i < 4; ++i) arr[0][i] = cnt++;
    for (int i = 3; i >= 0; --i) arr[1][i] = cnt++;
} // 在成员函数的实现中，this是指向当前对象的指针，可以省略不写
```

然后是复制构造函数，也就是把魔板A变成魔板B，相当于赋值，也是直接模拟

```cpp
Block(const Block& p) {
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 4; ++j) {
            arr[i][j] = p.arr[i][j];
		}
	}
}
```

接下来考虑比较运算符的重载（划重点）

虽然在最后提交的代码中是用哈希来判重的，但是写代码雏形就用哈希实在太麻烦，用set往往会更舒服，然而set需要提供比较运算符，所以还是写一下六种比较运算符

根据比较运算符的一些性质，我们可以通过只写小于运算符来实现所有的六种运算符。

首先提供小于的实现方式（实现方法不唯一，根据个人需要自行选择）

```cpp
bool operator < (const Block &b) const {
    for (int i = 0; i < 4; ++i) if (this->arr[0][i] != b.arr[0][i]) return this->arr[0][i] < b.arr[0][i];
    for (int i = 3; i >= 0; --i) if (this->arr[1][i] != b.arr[1][i]) return this->arr[1][i] < b.arr[1][i];
		return false;
	}
```

现在有了小于运算符，其他的运算符可以根据不等式的性质推出

```cpp
bool operator > (Block b) const {
    return b < *this;// a大于b即b小于a
}
bool operator <= (Block b) const {
    return !(*this > b); // a小于等于b即a不大于b
}
bool operator >= (Block b) const {
    return !(*this < b); // a大于等于b即a不小于b
}
bool operator == (Block b) const {
    return !(*this < b || *this > b); // a等于b即a不大于b且a不小于b
}
bool operator != (Block b) const {
    return *this < b || *this > b; //a不等于b即a大于b或a小于b
    // 也可以写成!(*this == b)，即直接实现a不等于b
}
```

接下来的三种操作仍然是通过模拟实现，那么直接上代码就好了

```cpp
inline Block operateA() {
    Block ret = *this;
    int temp;
    for (int i = 0; i < 4; ++i) {
        temp = ret.arr[1][i]; ret.arr[1][i] = ret.arr[0][i]; ret.arr[0][i] = temp;
    }
    return ret;
}
inline Block operateB() {
    Block ret = *this;
    int temp[] = { ret.arr[0][3], ret.arr[1][3] };
    for (int i = 0; i < 2; ++i) {
        for (int j = 3; j > 0; --j) {
            ret.arr[i][j] = ret.arr[i][j - 1];
        }
    }
    ret.arr[0][0] = temp[0], ret.arr[1][0] = temp[1];
    return ret;
}
inline Block operateC() {
    Block ret = *this;
    int temp = ret.arr[0][1];
    ret.arr[0][1] = ret.arr[1][1];
    ret.arr[1][1] = ret.arr[1][2];
    ret.arr[1][2] = ret.arr[0][2];
    ret.arr[0][2] = temp;
    return ret;
}
```

有了这三种操作之后，我们可以直接通过Block tmp = k.operatorA()（或者B，C）得到操作后的魔板，于是在搜索的时候能够更加方便。

### 两种流运算符的重载

于是写着写着，我们会发现：好像读入很麻烦，还要循环读入，输出的时候也很麻烦。

所以根据c++流的性质，我们可以通过重载operator>>和operator<<进行更加方便的读入输出。（详细内容参见博客[读入输出流的一些介绍](https://from.blog.luogu.org/guan-yu-cin-di-ren-shi-yi-ji-shou-xie-du-ru-liu-lei-xing)）

那么我们就可以根据题目的输入格式进行读入

```cpp
istream& operator >> (istream& in, Block &p) {
    for (int i = 0; i < 4; ++i) cin >> p.arr[0][i];
        for (int i = 3; i >= 0; --i) cin >> p.arr[1][i];
    return in; // 一定要记得return，否则会原地去世
}

ostream& operator << (ostream& out, const Block &p) {
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 4; ++j) {
            out << p.arr[i][j] << ' ';
        }
        out << '\n';
    }
    return out; // 同上
}
```

于是我们就可以开始欢乐的搜索了，而且会发现在面向对象预处理之后，搜索过程会变得很短（因为大部分内容都在类中实现完毕了，只要调用就可以了）。

### 完整代码

~~跟上面的缩进好像不太一样emmm，这里是两格缩进的~~

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <set>
#include <map> // 一堆头文件

using namespace std;

struct Block { // 面向对象
  int arr[2][4];
  
  Block() {
    int cnt = 1;
    for (int i = 0; i < 4; ++i) arr[0][i] = cnt++;
    for (int i = 3; i >= 0; --i) arr[1][i] = cnt++;
  }
  Block(const Block& p) {
        for (int i = 0; i < 2; ++i) {
      for (int j = 0; j < 4; ++j) {
        arr[i][j] = p.arr[i][j];
      }
    }
  }
  
  bool operator < (const Block &b) const {
      for (int i = 0; i < 4; ++i) if (this->arr[0][i] != b.arr[0][i]) return this->arr[0][i] < b.arr[0][i];
    for (int i = 3; i >= 0; --i) if (this->arr[1][i] != b.arr[1][i]) return this->arr[1][i] < b.arr[1][i];
    return false;
  }
  bool operator > (const Block &b) const {
    for (int i = 0; i < 4; ++i) if (this->arr[0][i] != b.arr[0][i]) return this->arr[0][i] > b.arr[0][i];
    for (int i = 3; i >= 0; --i) if (this->arr[1][i] != b.arr[1][i]) return this->arr[1][i] > b.arr[1][i];
    return false;
  }
  bool operator <= (const Block &b) const {
    return !(*this > b);
  }
  bool operator >= (const Block &b) const {
    return !(*this < b);
  }
  bool operator == (const Block &b) const {
    return !(*this < b || *this > b);
  }
  bool operator != (const Block &b) const {
    return *this < b || *this > b;
  }
  
  inline Block operateA() {
    Block ret = *this;
    int temp;
    for (int i = 0; i < 4; ++i) {
      temp = ret.arr[1][i]; ret.arr[1][i] = ret.arr[0][i]; ret.arr[0][i] = temp;
    }
    return ret;
  }
  inline Block operateB() {
    Block ret = *this;
    int temp[] = { ret.arr[0][3], ret.arr[1][3] };
    for (int i = 0; i < 2; ++i) {
      for (int j = 3; j > 0; --j) {
        ret.arr[i][j] = ret.arr[i][j - 1];
      }
    }
    ret.arr[0][0] = temp[0], ret.arr[1][0] = temp[1];
    return ret;
  }
  inline Block operateC() {
    Block ret = *this;
    int temp = ret.arr[0][1];
    ret.arr[0][1] = ret.arr[1][1];
    ret.arr[1][1] = ret.arr[1][2];
    ret.arr[1][2] = ret.arr[0][2];
    ret.arr[0][2] = temp;
    return ret;
  }
};

istream& operator >> (istream& in, Block &p) {
  for (int i = 0; i < 4; ++i) cin >> p.arr[0][i];
    for (int i = 3; i >= 0; --i) cin >> p.arr[1][i];
  return in;
}

ostream& operator << (ostream& out, const Block &p) {
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 4; ++j) {
      out << p.arr[i][j] << ' ';
    }
    out << '\n';
  }
  return out;
}

struct Node {
  Block pos;
  int step;
  string vec;
  
  Node(Block b, int s, string vec): pos(b), step(s), vec(vec) {}
}; // 搜索中队列需要的内容，vec是用来记录答案的，本来是个vector后来发现string更方便，变量名还是没改回来

struct cmp {
  bool operator() (const Node &a, const Node &b) const {
    return (a.step > b.step) || (a.step == b.step && a.vec > b.vec);
  }
}; // 优先队列中的比较functional

Block pos; // 目标
set<Block> vis; // 判重（比较运算重载就是为了这个）
map<Block, int> dist; // 记录最小的操作次数
priority_queue<Node, vector<Node>, cmp> que; // 搜索时用的队列

inline string getStr(string str, char ch) {
  str.push_back(ch);
  return str;
} // 这个函数是为了方便，不写也行

inline void dijkstra() { // 我的搜索跟别人写的可能不太一样，被B站洗脑
  que.push(Node(Block(), 0, string()));
  while (!que.empty()) {
    Node u = que.top(); que.pop(); // 取队首不解释
    if (vis.count(u.pos)) continue; // 懒惰删除不解释
    dist[u.pos] = u.step; //区别在这里，每次找到最短的之后才进行更改
    vis.insert(u.pos);
    if (u.pos == pos) { // 得出结果后一顿操作
      printf("%d\n", dist[pos]);
      for (int i = 0, cnt = 0; i < u.vec.size(); ++i, ++cnt) {
        if (cnt == 60) {
          puts("");
          cnt = 0;
        }
        printf("%c", u.vec[i]);
      }
      return;
    }
    Block k1 = u.pos.operateA(); // 进行三种操作并入队
    if (dist.find(k1) == dist.end()) que.push(Node(k1, u.step + 1, getStr(u.vec, 'A')));
    Block k2 = u.pos.operateB();
    if (dist.find(k2) == dist.end()) que.push(Node(k2, u.step + 1, getStr(u.vec, 'B')));
    Block k3 = u.pos.operateC();
    if (dist.find(k3) == dist.end()) que.push(Node(k3, u.step + 1, getStr(u.vec, 'C')));
  }
  dist[pos] = -1; // 搜索完毕，无法到达
}

int main() {
  cin >> pos;
  dijkstra();
  return 0;
  // 非常短的主函数
}
```



---

## 作者：沧海之耀 (赞：2)

### 按照题目，很容易跟全排列挂上钩

## 那么如何判重就成了很重要的问题

### 在我努力的学习之后，我找到了康托展开

这样的话，该题迎刃而解

 _ __ _ 
------------

## 小优化：

### 魔板原本是2X4的矩阵，降至一维数组

以样例说明

```
1234

8765 ☞ 12348765
```

------------


------------


------------

## 代码：


```cpp
#include<iostream>
#include<cstdio>
#include<queue>
using namespace std;
char a[10];
long long fac(int t)//阶乘 
{
	if(t==0||t==1) return 1;
	long long sum=1;
	for(int i=2;i<=t;i++) sum*=i;
	return sum;
}
long long ct(char a[])//康托展开
{
    long long ans=0,sum=0;
    for(int i=0;i<7;i++)
	{
        for(int j=i+1;j<8;j++)
            if(a[j]<a[i]) sum++;
        ans=ans+sum*fac(7-i);
        sum=0;
    }
    return ans+1;
}
bool book[40321];
queue<int> q;
char step[40321][1001];
int step1[40321];
int main()
{
    for(int i=0;i<8;i++)
	{
		a[i]=getchar();
		getchar();
	}
    q.push(12345678);
    book[1]=1;
	int key=ct(a);//康托展开——目标步 
    while(!book[key])//未走到目标步时（逆推：从最终步推目标步） 
    {
    	int t=q.front();
    	q.pop();
    	char a[10],b[10],c[10];
    	sprintf(a,"%08d\n",t);//将头存入当前步 
    	sprintf(b,"%08d\n",t);
    	sprintf(c,"%08d\n",t);
    	int cnt=ct(a);//康托展开
    	
    	//尝试A 
    	int k;
    	for(int j=0;j<4;j++)//开始走一步
    		swap(a[j],a[8-j-1]);
    	k=ct(a);//康托展开——当前步 
    	if(!book[k])//判断走没走过这一步 
		{
			for(int i=0;i<step1[cnt];i++) step[k][i]=step[cnt][i];//接上之前走过的步 
			step[k][step1[cnt]]='A';//接上当前步 
			step1[k]=step1[cnt]+1;//步长+1 
			int newn=0;
			for(int i=0;i<8;i++) newn=newn*10+a[i]-'0';//将新数转成整型入队
		    q.push(newn);
		    book[k]=1;
		}
		
		//尝试B 
		for(int j=3;j>0;j--)//内容同上 
		{
			swap(b[j],b[j-1]);
			swap(b[8-j-1],b[8-j]);
		}
		k=ct(b);
    	if(!book[k])
		{
			for(int i=0;i<step1[cnt];i++) step[k][i]=step[cnt][i];
			step[k][step1[cnt]]='B';
			step1[k]=step1[cnt]+1;
			int newn=0;
			for(int i=0;i<8;i++) newn=newn*10+b[i]-'0';
		    q.push(newn);
		    book[k]=1;
		}
		
		//尝试C 
		char s=c[1];
		c[1]=c[6];c[6]=c[5];c[5]=c[2];c[2]=s;
		k=ct(c);
    	if(!book[k])
		{
			for(int i=0;i<step1[cnt];i++) step[k][i]=step[cnt][i];
			step[k][step1[cnt]]='C';
			step1[k]=step1[cnt]+1;
			int newn=0;
			for(int i=0;i<8;i++) newn=newn*10+c[i]-'0';
		    q.push(newn);
		    book[k]=1;
		}
	}
	cout<<step1[key]<<endl;
	for(int i=0;i<step1[key];i++) cout<<step[key][i];
}
```


---

## 作者：Valhalla_Is_Calling (赞：2)

## 这是一道非常经典的BFS题目

### 如果把所有都扫描一遍，将会面临指数级的时间复杂度，所以要另想办法

所以一般的广搜都会用一个数组来实现。数组下标运用一个Hash函数来设计，所以重点放在Hash函数上。

### 概念

将任意长度的输入变换为固定长度的输出的不可逆的单向密码体制

Hash函数在数字签名和消息完整性检测等方面有着广泛的应用

Hash函数同时是一种具有压缩特性的单向函数，其像通常称为数字指纹，消息摘要或散列值。

散列值的生成过程可以表示为

h = H(M)

其中h是定长的散列值，H是哈希函数，M是一个变长消息

散列函数主要用于消息认证和数字签名，因此需要具备以下特性

H可应用于任意长度的消息

H产生定长的输出
对任意给定的消息x，计算H(x)比较容易，用硬件软件均可实现

单向性：对任意给定的散列值h，找到满足H(x) = h 的x在计算上是不可行的

抗弱碰撞性：对任意给定的消息x，找到x != y并且H(x) = H(y)的消息y在计算上是不可行的

抗强碰撞性：找到任何满足H(x) = H(y) 的偶对（x,y）在计算上是不可行的

### 应用
数字签名

由于消息散列值通常比消息本身短的多，因此对消息散列值进行数字签名在处理上比对消息本身进行签名要高效的多。

生成程序或文档的数字指纹

hash函数可以用来保证消息的完整性。首先，通过哈希函数变换得到程序或文档的散列值，然后将散列值存储，对程序或文档进行定时的检测，与已存储的散列值进行比较，以此来实现完整性验证。

用于安全传输和用户口令

用于保存用户登陆口令（密码），通过用户id及口令生成相应的散列值，然后保存，用户在进入系统输入口令时，生成散列值与存储的散列值进行比较，这样可以确保用户口令不被管理员或攻击者获取到

![](https://img2018.cnblogs.com/blog/1387012/201901/1387012-20190109121820782-592441859.png)

Hash函数介绍完了，接下来说一下这道题目。

关于本体Hash函数的设计：我们容易想到8个数字顺时针顺序组合成8进制，所以要引入康托展开。

定义：
康托展开是一个全排列到一个自然数的双射，常用于构建哈希表时的空间压缩。 康托展开的实质是计算当前排列在所有由小到大全排列中的名次，因此是可逆的。

原理介绍
**X = A[0] * (n-1)! + A[1] * (n-2)! + … + A[n-1] * 0! **

A[i] 指的是位于位置i后面的数小于A[i]值的个数,后面乘的就是后面还有多少个数的阶乘

说明 ：这个算出来的数康拖展开值，是在所有排列次序 - 1的值，因此X+1即为在全排列中的次序
列 ：
在（1，2，3，4，5）5个数的排列组合中，计算 34152的康托展开值。
带入上面的公式

X = 2 * 4! + 2 * 3! + 0 * 2! + 1 * 1! + 0 * 0!
=>X = 61

本题的代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int jc[10]={1,1,2,6,24,120,720,5040};
int g,st,prt[50005],b[1000000]={0},step[50005];
char a[50005];
struct mb{int a[2][4];}start,goal,q[90000];


int Turn(mb x)
{
	int i,j,res=0,t[8],s;
	for(i=0;i<4;i++) t[i]=x.a[0][i];
	for(i=3;i>=0;i--) t[7-i]=x.a[1][i];
	for(i=0;i<8;i++)
	{
		s=0;
		for(j=i+1;j<=7;j++) if(t[j]<t[i]) s++;
		res+=jc[7-i]*s;
	}	
	return res;
} 

mb Change(int way,int num)
{
	mb temp;
	if(way==1)
	{
		for(int i=0;i<4;i++) temp.a[0][i]=q[num].a[1][i];
		for(int i=0;i<4;i++) temp.a[1][i]=q[num].a[0][i];
		return temp;
	}
	if(way==2)
	{
		temp.a[0][0]=q[num].a[0][3];
		temp.a[1][0]=q[num].a[1][3];
		for(int i=1;i<4;i++) temp.a[0][i]=q[num].a[0][i-1];
		for(int i=1;i<4;i++) temp.a[1][i]=q[num].a[1][i-1];
		return temp;
	}
	if(way==3)
	{
		temp.a[0][0]=q[num].a[0][0];temp.a[0][3]=q[num].a[0][3];
		temp.a[1][0]=q[num].a[1][0];temp.a[1][3]=q[num].a[1][3];
		temp.a[0][1]=q[num].a[1][1];temp.a[0][2]=q[num].a[0][1];
		temp.a[1][2]=q[num].a[0][2];temp.a[1][1]=q[num].a[1][2];
		return temp;
	}
}

void Print(int num)
{
	if(num==1) return;
	Print(prt[num]);
	cout<<a[num];
}

void Bfs()
{
	int op=1,cl=1,i,t;
	mb temp;
	q[1]=start;
	step[1]=0;
	prt[1]=1;
	while(op<=cl)
	{
		for(i=1;i<=3;i++)
		{
			temp=Change(i,op);
			t=Turn(temp);
			if(!b[t])
			{
				q[++cl]=temp;
				step[cl]=step[op]+1;
				b[t]=1;
				prt[cl]=op;
				a[cl]=char('A'+i-1);
				if(t==g) 
				{
					cout<<step[cl]<<endl;
					Print(cl);
					return;
				}
				
			}
			
		
		}
	op++;
	} 
}
int main()
{
	int i;
	for(i=0;i<4;i++) start.a[0][i]=i+1;
	for(i=3;i>=0;i--) start.a[1][i]=8-i;
	st=Turn(start);
	b[st]=1;
	for(i=0;i<4;i++) cin>>goal.a[0][i];
	for(i=3;i>=0;i--) cin>>goal.a[1][i];
	g=Turn(goal);
	if(g==st) 
	{
		cout<<0;
		return 0;
	}
	Bfs();
	return 0;
}
```
## 杜绝作弊，请勿抄袭



---

## 作者：Myrcella (赞：2)

看到dalao们都用了康托展开？？？
juruo表示根本没听说过这个玩意儿 
于是直接用哈希+map苟过去了？？？？？（大雾
毕竟只是个8位数嘛int都能表示


------------
不错的搜索题，一开始差点想成dfs，但仔细琢磨琢磨似乎bfs更好一点，因为每一步操作的代价都为1嘛。。。
为了方便写了一个struct用来记录：当前的图cur（注意我的数组都是按照一开始是1 2 3 4 5 6 7 8写的。即题图中蛇形的顺序。）、当前所用步数step（其实这个变量时多余的，可以直接用ans.size()表示）以及记录当前操作步骤的字符串ans（感觉这个比记录每一步的前驱然后递归输出方便许多唉。。）。
然后基本上就是核心的bfs部分了。。没有什么特别的直接看代码吧2333
至于A B C的操作部分这里运用了swap。。。稍微画下图应该很好理解，而且还有很多方法
求dalao轻虐
```c
#include<bits/stdc++.h>
using namespace std;

struct graph{ //前文中提到的struct
    int cur[8];
    int step;
    string ans;
};

queue <graph> q; //用于bfs的队列
map <int,bool> vis;  //用来记录是否访问过的map（结合哈希使用）

int goal;

int Hash(int a[]) { //哈希
    int ret=0;
    for (int i=0;i<8;i++) ret=ret*10+a[i];
    return ret;
}

int main(){
    graph a;
    a.step=0;
    a.ans="";
    for (int i=0;i<8;i++) {
        int x;
        scanf("%d",&x);
        goal=goal*10+x;
        a.cur[i]=i+1; //之前忘+1了。。。结果一直死循环调了好一会儿才发现
    }
    q.push(a);
    while (q.size()){
        graph p=q.front();
        q.pop();
        int tmp=Hash(p.cur);
        if (tmp==goal) {
            cout<<p.step<<endl<<p.ans<<endl;
            return 0;
        }
        if (vis[tmp]==true) continue;
        vis[tmp]=true;
        graph x=p;
        //A
        for (int i=0;i<4;i++) swap(x.cur[i],x.cur[7-i]);
        x.step=p.step+1;
        x.ans+="A";
        q.push(x);
        //B
        x=p;
        swap(x.cur[0],x.cur[3]);
        swap(x.cur[2],x.cur[3]);
        swap(x.cur[1],x.cur[2]);
        swap(x.cur[7],x.cur[4]);
        swap(x.cur[5],x.cur[4]);
        swap(x.cur[5],x.cur[6]);
        x.step=p.step+1;
        x.ans+="B";
        q.push(x);
        //C
        x=p;
        swap(x.cur[2],x.cur[5]);
        swap(x.cur[1],x.cur[2]);
        swap(x.cur[1],x.cur[6]);
        x.step=p.step+1;
        x.ans+="C";
        q.push(x);
    }
    return 0;
}
```

---

## 作者：NeosKnight (赞：2)

bfs   加康托展开判重  ，输入的时候要注意顺序，用一维数组存储状态，操作过程用三个函数即可，其实也不是很难。

但要注意这鬼畜的数据，有一个就是初态，这里要特判一下；


```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<cstdlib>
using namespace std;
const int fac[9]={1,1,2,6,24,120,720,5040,40320};
struct node{
    int a[10];//描述数字分布；
    node(){
        memset(a,0,sizeof(a));
    } 
    int n;int step;
}p[800000];
bool gg[5040*8];
int f[5040*8];
int goal=0;
inline void swapp(int &a,int &b)
{
    int c=a;
    a=b;b=c;
}
void A(node &s)
{
    swapp(s.a[1],s.a[5]);
    swapp(s.a[2],s.a[6]);
    swapp(s.a[3],s.a[7]);
    swapp(s.a[4],s.a[8]);
}
void B(node &s)
{
    swapp(s.a[4],s.a[3]);swapp(s.a[8],s.a[7]);
    swapp(s.a[3],s.a[2]);swapp(s.a[7],s.a[6]);
    swapp(s.a[2],s.a[1]);swapp(s.a[6],s.a[5]);
}
void C(node &s)
{
    swapp(s.a[2],s.a[3]);swapp(s.a[2],s.a[7]);swapp(s.a[2],s.a[6]);
}
int tot=0;
int KT(node s)
{
    int num=0;
    for(int i=1;i<=8;i++)
    {
        int k=0;
        for(int j=i+1;j<=8;j++)
        {
            if(s.a[i]>s.a[j]) k++;
        }
        num+=k*fac[8-i];
    }
    return num;
}
void out(int T)//递归输出
{
    if(T==1) return ;
    out(f[T]);
    if(f[T]==1) cout<<tot<<endl;
    if(p[T].n==1) cout<<"A";
    if(p[T].n==2) cout<<"B";
    if(p[T].n==3) cout<<"C";
}
void bfs()
{
    int h=0;int t=1;p[1].step=0;
    do{
        h++;
        for(int i=1;i<=3;i++)
        {
            t++;
            for(int j=1;j<=8;j++)
            p[t].a[j]=p[h].a[j];
            if(i==1) A(p[t]);
            if(i==2) B(p[t]);
            if(i==3) C(p[t]);
            int g=KT(p[t]);
            if(gg[g]==true) t--;
            else {
                gg[g]=true;p[t].step=p[h].step+1;//记录步数 
                p[t].n=i;//表示这一状态是通过哪个步骤得来的; 
                f[t]=h;//记录路径;
                if(g==goal)
                {
                    tot=p[t].step;
                    out(t);
                    return ;
                 } 
            }
        }
    }while(h<t);
}
int main()
{
    for(int i=1;i<=4;i++) p[1].a[i]=i;
    for(int i=5;i<=8;i++) p[1].a[i]=13-i;
    memset(gg,0,sizeof(gg));
    gg[KT(p[1])]=true;
    node zhong;
    for(int i=1;i<=4;i++)
    {
        cin>>zhong.a[i];
    }
    for(int i=5;i<=8;i++)
    {
        cin>>zhong.a[13-i];//分上下处理输入
    }
    goal=KT(zhong);
    if(gg[goal]==true){//特判
        cout<<0<<endl;return 0;
    }
    bfs();
    return 0;
}
```

---

## 作者：「QQ红包」 (赞：2)

其实是普通的bfs。但是三种情况处理起来比较麻烦。


判重咱用的是map。


然后12345678是

1234
8765
然后存用12345678的话就比较麻烦，于是我存的话就是12348765，处理起来也方便一些。


读入的目标状态我们存的时候也做下处理，如样例：26845731，我们存的话是26841375。这样判断是否搜到的时候会比较方便。


三种情况的处理话自己推一下就出来了，见代码。

```cpp
/*
ID: ylx14274
PROG: msquare
LANG: C++     
*/
#include<set>  
#include<map>  
#include<list>  
#include<queue>  
#include<stack>  
#include<string>  
#include<math.h>  
#include<time.h>  
#include<vector>  
#include<bitset>  
#include<memory>  
#include<utility>  
#include<stdio.h>  
#include<sstream>  
#include<iostream>  
#include<stdlib.h>  
#include<string.h>  
#include<algorithm> 
#define LL unsigned long long   
using namespace std;
map<int,bool> f;//判重用 
int i,l,r;
int x,xx;
int fff=0;
struct haha
{
    int pred;//存上一个在队列中的位置 
    char c;//存操作方式的 
    int n;//存当前状态的 
    int sum;//存当前操作的长度 
} a[500000];
void digui(int k)
{
    if (a[k].pred!=-1)digui(a[k].pred);
    if (a[k].pred!=-1)printf("%c",a[k].c);
    return;
} 
void sc(int x)//输出
{
    printf("%d\n",a[x].sum);
    fff=1;
    digui(x);
    printf("\n");
    return;
}
/**************************************************/
void aa(int k)//操作A 
{
    int an=k/10000;//第一行 
    int bn=k%10000;//第二行
    int d=bn*10000+an;//第一行与第二行进行交换
    if (f[d]==1) return;//去重
    //printf("A:%d %d sum:%d\n",r+1,d,a[l].sum+1);
    f[d]=1;//标记 
    r++;//入队
    a[r].pred=l;//标记上一个 
    a[r].c='A';//标记为操作A 
    a[r].n=d;
    a[r].sum=a[l].sum+1;//记操作次数 
    if (d==x) sc(r);//找到了就输出 
    return;
}

void bb(int k)//操作B
{
    int an=k/10000;//第一行 
    int bn=k%10000;//第二行
    an=(an%10)*1000+(an/10);//最后一列插入到第一列 
     bn=(bn%10)*1000+(bn/10);//最后一列插入到第一列 
     int d=an*10000+bn;
     if (f[d]==1) return;//去重
    //printf("B:%d %d sum:%d\n",r+1,d,a[l].sum+1);
    f[d]=1;//标记
    r++;//入队 
    a[r].pred=l;//标记上一个 
    a[r].c='B';//标记为操作B
    a[r].n=d;
    a[r].sum=a[l].sum+1;//记操作次数 
    if (d==x) sc(r);//找到了就输出  
    return;
}

void cc(int k)//操作C，好坑啊。 
{
    int an=k/10000;//第一行 
    int bn=k%10000;//第二行
    int rr=an;//存an修改前的值 
    an=(an/1000*1000)/*第一位不变*/
    +(bn/100%10*100)/*第二位来自第二行*/
    +(an/100%10*10)/*第二位成第三位*/
    +(an%10);/*最后一位不变*/
    bn=(bn/1000*1000)/*第一位不变*/
    +(bn%100/10*100)/*第三位变成第二位*/
    +(rr%100/10*10)/*来自第一行的第三位*/
    +(bn%10);/*最后一位不变*/ 
    //这处理，我TM要炸了。
    int d=an*10000+bn;
     if (f[d]==1) return;//去重
    //printf("C:%d %d sum:%d\n",r+1,d,a[l].sum+1);
    f[d]=1;//标记
    r++;//入队 
    a[r].pred=l;//标记上一个 
    a[r].c='C';//标记为操作B
    a[r].n=d;
    a[r].sum=a[l].sum+1;//记操作次数 
    if (d==x) sc(r);//找到了就输出  
    return;
}
/**************************************************/
int main() 
{
    int xxx=0;
    for (i=1;i<=8;i++)
    {
        scanf("%d",&xx);//读入 
        xxx=xxx*10+xx;
    }
    x=xxx/10000;
    xxx=xxx%10000;//保留最后四位
    x=x*10000//前4位不变
    +(xxx%10*1000)
    +(xxx%100/10*100)
    +(xxx/100%10*10)
    +(xxx/1000);
    if (x==12348765)//不需要变动 
    {
        printf("0\n\n");
        return 0;
    }
    //printf("x:%d\n",x);
    f[12348765]=1;//标记 
    l=0;
    r=1;
    a[1].n=12348765;
    a[1].pred=-1;
    
    while (l!=r)
    {
        l++;
        aa(a[l].n);//三种操作 
        if (fff==1) return 0;
        bb(a[l].n);
        if (fff==1) return 0;
        cc(a[l].n);
        if (fff==1) return 0;
    }
    return 0;
}

```

---

## 作者：光明正大 (赞：2)

**蒟蒻写于阶段二考试后6小时~~~**

这题一看是到蓝题就有点犹豫，但我还是硬着头皮写下来了

下面进入正题

------------
搜索显而易见，虽然只有8个方块，但其情况数显然超出普通深搜要求（~~其实我不会打高级的深搜剪枝~~）

大致思路是用结构体队列存储每一种情况及其操作

```cpp
struct magic{int shu,k;string s;};
queue<magic> q;
```
k是操作次数，s是对应操作（AABBCC之类的），shu是这种情况顺时针都出来的数

每次让队首出队，对它进行A,B,C三种操作

然后让这三种情况入队

```cpp
magic mag=q.front();q.pop();
q.push((magic){A(mag.shu),mag.k+1,mag.s+'A'});
q.push((magic){B(mag.shu),mag.k+1,mag.s+'B'});
q.push((magic){C(mag.shu),mag.k+1,mag.s+'C'});
```
ABC我写的三种转换函数
```cpp
inline int A(int x)
{
	for(int i=8;i>=1;i--) lin[i]=x%10,x/=10;
	for(int i=8;i>=1;i--) x=x*10+lin[i];
	return x;
}
inline int B(int x){return x/10000%10*10000000+x/100000*10000+x%10000/1000+x%1000*10;}
inline int C(int x)
{
	for(int i=8;i>=1;i--) lin[i]=x%10,x/=10;
	lin[0]=lin[2];lin[2]=lin[7];lin[7]=lin[6];
	lin[6]=lin[3];lin[3]=lin[0];
	for(int i=1;i<=8;i++) x=x*10+lin[i];
	return x; 
}
```
这就导致一个问题：**重复情况怎么办？**

用**map**

开一个map存储相应到达相应情况所需要的最小步数

如果搜到情况相同且步数不小于但前最少步数则跳过
```cpp
		if(mag.k>1+m[mag.shu]&&m[mag.shu]!=0) continue;
```
最后搜到答案结束
```cpp
		if(mag.shu==z)
		{
			if(mag.k<ans) {ans=mag.k;anss=mag.s;}
			else if(mag.k==ans) if(mag.s<anss) anss=mag.s;
			continue;
		}
```
完整代码如下：
不太理解的看注释

```cpp
#include<bits/stdc++.h>
using namespace std;
map<int,int> m;
struct magic{int shu,k;string s;};
queue<magic> q;//结构体队列
string anss;//答案
int ss,z,ans=1e5,len,p,lin[10];
//三种操作
inline int A(int x)
{
	for(int i=8;i>=1;i--) lin[i]=x%10,x/=10;
	for(int i=8;i>=1;i--) x=x*10+lin[i];
	return x;
}
inline int B(int x) {return x/10000%10*10000000+x/100000*10000+x%10000/1000+x%1000*10;}
inline int C(int x)
{
	for(int i=8;i>=1;i--) lin[i]=x%10,x/=10;
	lin[0]=lin[2];lin[2]=lin[7];lin[7]=lin[6];
	lin[6]=lin[3];lin[3]=lin[0];
	for(int i=1;i<=8;i++) x=x*10+lin[i];
	return x; 
}
int main()
{
	//读入目标状态
	for(int i=1;i<=8;i++) cin>>ss,z=z*10+ss;
	q.push((magic){12345678,0,""});
	while(!q.empty())
	{
		magic mag=q.front();q.pop();
		if(mag.k>ans) continue;//超过最少步数
		if(mag.shu==z)//与最终目标相同
		{
        	//判断是否步数更少以及字典序更小
			if(mag.k<ans) {ans=mag.k;anss=mag.s;}
			else if(mag.k==ans) if(mag.s<anss) anss=mag.s;
			continue;
		}
        //若比已知最少步数多则跳过（map初始值为0）
		if(mag.k>1+m[mag.shu]&&m[mag.shu]!=0) continue;
		if(!m[A(mag.shu)])
		{
			m[A(mag.shu)]=mag.k;
			q.push((magic){A(mag.shu),mag.k+1,mag.s+'A'}); 
		}
		if(!m[B(mag.shu)])
		{
			m[B(mag.shu)]=mag.k;
			q.push((magic){B(mag.shu),mag.k+1,mag.s+'B'}); 
		}
		if(!m[C(mag.shu)])
		{
			m[C(mag.shu)]=mag.k;
			q.push((magic){C(mag.shu),mag.k+1,mag.s+'C'}); 
		}
	}
    //输出答案及步数
	cout<<ans<<endl;len=anss.size();
	while(p<len)
	{
		cout<<anss[p++];
        //注意换行
		if(p%60==0) cout<<endl;
	}
	return 0;
}

```
不会的可以留言或私信我~~~

望管理员通过~~~

愿段二不要爆炸太狠

------------


---

## 作者：doby (赞：2)

用字符串做会简便一些，因为字符串可以随便换……

这么点状态搜一个加一个就计一个(map)就好了……

难点在于存操作串……

开一个字符串数组(m[])专门存这个，然后map判重的东西(d[])就可以作为这个数组的下标从而代表这个状态(m[d[string]])是由m所存的操作串得到的……

推荐先去看最下面那个题解，dalao说到：操作串不超过22个字符(最多应该是22步)，所以根本不用换行……

```cpp
//当然其实大家都没写换行……
#include<iostream>
#include<string>
#include<map>
using namespace std;
string qs[50010],m[50010],s,c,a="12345678",b="";
int u,tim[50010],head=0,tail=1,t,x,k,ss,cnt;
char cc,p;
map<string,int>d;
void sap(int x,int y)
{
    p=s[x],s[x]=s[y],s[y]=p;//这只是交换操作
}
int main()
{
    for(int i=1;i<=8;i++){cin>>cc;b=b+cc;}
    if(a==b){cout<<"0";return 0;}
    qs[1]=a,tim[1]=0;
    while(head!=tail)
    {
        head++,c=qs[head],t=tim[head],k=d[c];//取出状态
        s=c;
        sap(0,7);//A操作
        sap(1,6);
        sap(2,5);
        sap(3,4);
        if(s==b)
        {
            cout<<t+1<<"\n";
            for(int i=0;i<m[k].size();i++)//逐位输出
            {
                cout<<m[k][i];
                ss++;
                if(ss==60)//既然都写了，那就不删了……
                {
                    cout<<"\n";
                    ss=ss-60;
                }
            }
            cout<<'A';//一定要输出当前的操作
            return 0;
        }
        if(!d[s])//这就是判重
        {
            cnt++, m[cnt]=m[k]+"A",/*从上个状态记录下来*/d[s]=cnt,//这也是判重
            tail++,qs[tail]=s,tim[tail]=t+1;//这也是记录状态
        }
        s=c;
        sap(0,3);//B操作
        sap(1,3);//基本完全同上……
        sap(2,3);//所以不做过多解释了……
        sap(4,7);
        sap(4,6);
        sap(4,5);
        if(s==b)
        {
            cout<<t+1<<"\n";
            for(int i=0;i<m[k].size();i++)
            {
                cout<<m[k][i];
                ss++;
                if(ss==60)
                {
                    cout<<"\n";
                    ss=ss-60;
                }    
            }
            cout<<'B';
            return 0;
        }
        if(!d[s])
        {
            cnt++, m[cnt]=m[k]+"B",d[s]=cnt,
            tail++,qs[tail]=s,tim[tail]=t+1;
        }
        s=c;
        sap(1,6);//C操作
        sap(2,6);
        sap(5,6);
        if(s==b)
        {
            cout<<t+1<<"\n";
            for(int i=0;i<m[k].size();i++)
            {
                cout<<m[k][i];
                ss++;
                if(ss==60)
                {
                    cout<<"\n";
                    ss=ss-60;
                }
            }
            cout<<'C';
            return 0;
        }
        if(!d[s])
        {
            cnt++, m[cnt]=m[k]+"C",d[s]=cnt,
            tail++,qs[tail]=s,tim[tail]=t+1;
        }
    }
    return 0;
}
```

---

## 作者：__wfx (赞：2)

这题就是一BFS

难点在于判重和储存

本来想写哈希

但炸了

然后写了map想试试

容易炸空间
于是我就把一数组压成了一个数

直接更改数

至于输出步数 我在队列里加了一个string

至于三个操作

A操作是把该数翻转一下

1 2 3 4

8 7 6 5

压缩成数是 12345678

进行 A操作后是

8 7 6 5 

1 2 3 4

压缩成数是 87654321

```cpp
inline node A(node x)
{
	unsigned int s = x.a;
	int a = s % 10 * 10000000, f = s / 10 % 10 * 1000000, g = s / 100 % 10 * 100000, h = s / 1000 % 10 * 10000;
	int b = s / 10000000, c = s / 1000000 % 10 * 10, d = s / 100000 % 10 * 100, e = s / 10000 % 10 *1000;//取出每一数位 并计算出之后应在的数位 
	x.a = a + b + c + d + e + f + g + h;//翻转 
	x.s += "A";
	return x;
}
```

进行B操作后是

4 1 2 3 

5 8 7 6

压缩成数是 41236785

```cpp
inline node B(node x)
{ 
	unsigned int s = x.a;
	int a = s / 10000 % 10 * 10000000, b = s % 10000 / 1000;
	int c = s / 100000 * 10000, d = s % 1000 * 10;// 计算出每一部分应在哪里 
	x.a = a + b + c + d; 
	x.s += "B";
	return x;
}
```

C操作后是 

1 7 2 4

8 6 3 5

17245368
```cpp
inline node C(node x)
{
	unsigned int s = x.a;
	unsigned int a = s / 10 % 10, b = s / 100 % 10, c = s / 100000 % 10, d = s / 1000000 % 10;
	s -= (a * 10 + b * 100 + c * 100000 + d * 1000000);
	a *= 1000000; b *= 10; c *= 100; d *= 100000;
	x.a = a + b + c + d + s;
	x.s += "C";
	return x;
}
```

最后套进一个BFS框架即可

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstdlib>
#include<cstring>
#include<string>
#include<queue>
#include<ctime>
#include<deque>
#include<set>
#include<bitset>
#include<vector>
#include<list>
#include<stack>
#include<map>
#include<cmath>
#define ull unsigned long long
#define ll long long
#define inf 99999999
#define N 1010000
#define mod 1000009
using namespace std;
inline ll read()
{
 	ll res=0,bo=1;
 	char ch=getchar();
 	while(ch<'0'||ch>'9'){if(ch=='-')bo=-1;ch=getchar();}
 	while(ch>='0'&&ch<='9'){res=(res<<1)+(res<<3)+ch-'0';ch=getchar();}
 	return bo*res;
}
struct node{
	unsigned int a;
	string s;
}a, z;
inline node A(node x)
{
	unsigned int s = x.a;
	int a = s % 10 * 10000000, f = s / 10 % 10 * 1000000, g = s / 100 % 10 * 100000, h = s / 1000 % 10 * 10000;
	int b = s / 10000000, c = s / 1000000 % 10 * 10, d = s / 100000 % 10 * 100, e = s / 10000 % 10 *1000;//取出每一数位 并计算出之后应在的数位 
	x.a = a + b + c + d + e + f + g + h;//翻转 
	x.s += "A";
	return x;
}
inline node B(node x)
{ 
	unsigned int s = x.a;
	int a = s / 10000 % 10 * 10000000, b = s % 10000 / 1000;
	int c = s / 100000 * 10000, d = s % 1000 * 10;// 计算出每一部分应在哪里 
	x.a = a + b + c + d; 
	x.s += "B";
	return x;
}
inline node C(node x)
{
	unsigned int s = x.a;
	unsigned int a = s / 10 % 10, b = s / 100 % 10, c = s / 100000 % 10, d = s / 1000000 % 10;
	s -= (a * 10 + b * 100 + c * 100000 + d * 1000000);
	a *= 1000000; b *= 10; c *= 100; d *= 100000;
	x.a = a + b + c + d + s;
	x.s += "C";
	return x;
}
queue <node> q;
map <int, int> m;//用来判重
int minn(int a, int b){
	return a < b ? a : b;
}
inline void print(node a)
{
	printf("%d\n", a.s.size());
	for(int i = 0; i < minn(60, a.s.size()); ++i)//要求只输出前60次操作
		putchar(a.s[i]);
	return;
}
inline void BFS()
{
	q.push(a);
	while(!q.empty()){
		node k = q.front();
		q.pop();
		node a = A(k);
		if(a.a == z.a) {print(a); return;}
		node b = B(k);
		if(b.a == z.a) {print(b); return;}
		node c = C(k);
		if(c.a == z.a) {print(c); return;}//判断是否搜过了
		if(m[a.a] == 0) {
			q.push(a);
			m[a.a] = 1;//标记已经搜过了
		}
		if(m[b.a] == 0){
			q.push(b);
			m[b.a] = 1;
		}
		if(m[c.a] == 0){
			q.push(c);
			m[c.a] = 1;
		}
	}
}
int main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	for(int i = 1; i <= 8; ++i){
		int p = read();
		z.a = (z.a << 1) + (z.a << 3) + p;
		a.a = (a.a << 1) + (a.a << 3) + i;
	}
	if(z.a == a.a) putchar('0');//特判如果目标状态是初始状态则输出0
	else BFS();
//	fclose(stdin);fclose(stdout);
    return 0;
}
```


---

## 作者：Rocket_raccoon_ (赞：2)

作为蒟蒻，各位大佬的解法看得很累......

对于本题来说，解法最好用宽搜而不是双向广搜（字典序）。

代码丑得出奇，但是思路很好理解，在函数中极其暴力的把情况手写出来，

但相信对爱好暴力解题的同学有一定的帮助。

ps：bfs的地方有点乱，但看完main（）里的代码就能明白。



```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int b[40320][2][4],c[40320],bi[2][4];
int n[40320][3],l[40320];
char r[5000];
bool se[9][9][9][9][9][9][9];
int ans;
int h=-1,t=0;
int bfs(){//可以略过，只是把原始思想暴力手写出来，没有偷懒。也没什么好说的
    c[0]=0; 
    do{
        h++;
        t++;
        b[t][0][0]=b[h][1][0];b[t][0][1]=b[h][1][1];
        b[t][0][2]=b[h][1][2];b[t][0][3]=b[h][1][3];
        b[t][1][0]=b[h][0][0];b[t][1][1]=b[h][0][1];
        b[t][1][2]=b[h][0][2];b[t][1][3]=b[h][0][3];
        if(se[b[t][0][0]][b[t][0][1]][b[t][0][2]][b[t][0][3]]           [b[t][1][0]][b[t][1][1]][b[t][1][2]]){
            t--;
        }
        else{
            se[b[t][0][0]][b[t][0][1]][b[t][0][2]][b[t][0][3]]                [b[t][1][0]][b[t][1][1]][b[t][1][2]]=1;
            c[t]=c[h]+1;
            n[h][0]=t;
            l[t]=h;
            if(b[t][0][0]==bi[0][0]&&b[t][0][1]==bi[0][1]&&b[t]                [0][2]==bi[0][2]&&b[t][0][3]==bi[0][3]&&b[t][1]                    [0]==bi[1][0]&&b[t][1][1]==bi[1][1]&&b[t][1]                    [2]==bi[1][2]&&b[t][1][3]==bi[1][3]){
                return c[t];
            }
        }
        t++;
        b[t][0][0]=b[h][0][3];b[t][0][1]=b[h][0][0];
        b[t][0][2]=b[h][0][1];b[t][0][3]=b[h][0][2];
        b[t][1][0]=b[h][1][3];b[t][1][1]=b[h][1][0];
        b[t][1][2]=b[h][1][1];b[t][1][3]=b[h][1][2];
        if(se[b[t][0][0]][b[t][0][1]][b[t][0][2]][b[t][0][3]]            [b[t][1][0]][b[t][1][1]][b[t][1][2]]){
            t--;
        }
        else{
            se[b[t][0][0]][b[t][0][1]][b[t][0][2]][b[t][0][3]]                [b[t][1][0]][b[t][1][1]][b[t][1][2]]=1;
            c[t]=c[h]+1;
            n[h][1]=t;
            l[t]=h;
            if(b[t][0][0]==bi[0][0]&&b[t][0][1]==bi[0][1]&&b[t]                [0][2]==bi[0][2]&&b[t][0][3]==bi[0][3]&&b[t][1]                    [0]==bi[1][0]&&b[t][1][1]==bi[1][1]&&b[t][1]                    [2]==bi[1][2]&&b[t][1][3]==bi[1][3]){
                return c[t];
            }
        }
        t++;
        b[t][0][0]=b[h][0][0];b[t][0][1]=b[h][1][1];
        b[t][0][2]=b[h][0][1];b[t][0][3]=b[h][0][3];
        b[t][1][0]=b[h][1][0];b[t][1][1]=b[h][1][2];
        b[t][1][2]=b[h][0][2];b[t][1][3]=b[h][1][3];
        if(se[b[t][0][0]][b[t][0][1]][b[t][0][2]][b[t][0][3]]            [b[t][1][0]][b[t][1][1]][b[t][1][2]]){
            t--;
        }
        else{
            se[b[t][0][0]][b[t][0][1]][b[t][0][2]][b[t][0][3]]                [b[t][1][0]][b[t][1][1]][b[t][1][2]]=1;
            c[t]=c[h]+1;
            n[h][2]=t;
            l[t]=h;
            if(b[t][0][0]==bi[0][0]&&b[t][0][1]==bi[0][1]&&b[t]                [0][2]==bi[0][2]&&b[t][0][3]==bi[0][3]&&b[t][1]                    [0]==bi[1][0]&&b[t][1][1]==bi[1][1]&&b[t][1]                    [2]==bi[1][2]&&b[t][1][3]==bi[1][3]){
                return c[t];
            }
        }
    }while(h<t);
}
int main(){
    memset(se,0,sizeof(se));
    memset(n,0,sizeof(n));
    memset(c,0,sizeof(c));//数组清0
    b[0][0][0]=1;b[0][0][1]=2;
    b[0][0][2]=3;b[0][0][3]=4;
    b[0][1][0]=8;b[0][1][1]=7;
    b[0][1][2]=6;b[0][1][3]=5;//目标情况
    cin>>bi[0][0]>>bi[0][1]>>bi[0][2]>>bi[0][3]>>bi[1][3]>>bi[1]    [2]>>bi[1][1]>>bi[1][0];
    if(b[0][0][0]==bi[0][0]&&b[0][0][1]==bi[0][1]&&b[0][0]            [2]==bi[0][2]&&b[0][0][3]==bi[0][3]&&b[0][1][0]==bi[1]            [0]&&b[0][1][1]==bi[1][1]&&b[0][1][2]==bi[1][2]&&b[0][1]        [3]==bi[1][3]){
        cout<<"0"<<endl;//直接为目标情况
    }
    else{
        ans=bfs();
        cout<<ans<<endl;
        int e=0;
        while(1){
            for(int i=0;i<3;i++){
                if(n[l[t]][i]==t){//判断应该进行的操作
                    if(i==0) r[e]='A';
                    else if(i==1) r[e]='B';
                    else r[e]='C';
                    break;
                }
            }
            e++;
            if(t==0) break;
            t=l[t];
        }
        for(int i=e-2;i>=0;i--) cout<<r[i];//输出
        cout<<endl;
    }
    return 0;
}

```

---

## 作者：Brainless (赞：1)

#### 我太菜了啊，不会康托展开~~~

不过我也有我自己的方法把这道题A掉

我看到这道题的时候，瞬间想起[P1379 八数码难题](https://www.luogu.com.cn/problem/P1379)。其实那道题我就是 字符串 + $map$ 哈希 + 双向广搜，但是这道题只有 $8$ 位数，我就机($zuo$)智($si$)地用了状压。

但是八位数开数组不会爆吗？ 别忘了我们地数字只有$1$ ~ $8$ 
所以完全可以用八进制来表。这样算上表示方式最大的数，也只有$1e7$+$6e6$的数组大小，对于$125MB$的内存也是绰绰有余的啊。所以开数组方面完全不用担心。

现在就开始对解题进行一步步的思考了。

1. 首先这道题的情境实在二维的环境下，开始我们要思考的就是如何将二维操作转化成一维中对序列的操作。为了方便，在非二进制的状压下，我们可以用这样一个函数来获取数字的某一位：
```cpp
inline int getN(int st, int x)
{
    return st / p[x - 1] % 8; //p[i]为8的i次方,可以预处理出
//这里的是八进制，x代表从低到高的第x位，其他进制可以自行修改
}
```
**对于$A$:**

	1  2  3  4  5  6  7  8
	|  |  |  |  |  |  |  | 
	V  V  V  V  V  V  V  V
	8  7  6  5  4  3  2  1
可以发现$A$操作就是把整个序列翻转一下，算是最简单的一个了，在八进制状压下可以写出如下代码：
```cpp
int A(int st)
{
    rep(i, 0, 3)
    {
        int l = getN(st, i + 1), r = getN(st, 8 - i);//取低位和高位交换。
        st += (l - r) * p[7 - i]; st += (r - l) * p[i];
    }
    return st;
}
```
**对于$B$:**

	1  2  3  4  5  6  7  8
	|  |  |  |  |  |  |  |
	V  V  V  V  V  V  V  V
	4  1  2  3  6  7  8  5
   

$B$也很有规律，就是把第3、4位移动到第1、8位。
在翻转时注意未翻转部分的左移右移。
```cpp
int B(int st)
{
    int r1 = getN(st, 4), r2 = getN(st, 5), //r1 r2存右排两个
        h = st / p[4] / 8, l = st % p[3]; //l, h存左三列上下两排
    return r1 + r2 * p[7] + h * p[4] + 8 * l;
}
```

**对于$C$:**

	1  2  3  4  5  6  7  8
	|  |  |  |  |  |  |  |
	V  V  V  V  V  V  V  V
	1  7  2  4  5  3  6  8
$C$中的只需要将$2$，$3$，$6$，$7$位按照二维中的顺时针移动就行了
所以统计四个位置上的数字再将其移到目标位置就行了；
```cpp
int C(int st)
{
    int lu = getN(st, 2), ru = getN(st, 3),
        ld = getN(st, 7), rd = getN(st, 6);
    st += (ld - lu) * p[1]; st += (lu - ru) * p[2];
    st += (ru - rd) * p[5]; st += (rd - ld) * p[6];
    return st;
}
```
- 进行了这些操作之后，广搜就不是问题了，用最简单的就行了。这道题的重点不在广搜。

上完整代码：
```
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#define RG register int
#define rep(i,a,b)  for(RG i=a;i<=b;++i)
#define per(i,a,b)  for(RG i=a;i>=b;--i)
using namespace std;
int s, e;
int p[9] = {1, 8, 64, 512, 4096, 32768, 262144, 2097152, (int)2e9};
//打一个8的0~7次方的表，这个计算器可以轻松完成
short int vis[16434830]; //luogu上可以开int 但是一本通上内存更小，只能开short int
inline int getN(int st, int x)
{
    return st / p[x - 1] % 8;
}
int A(int st)
{
    for(int i = 0; i < 4; ++i)
    {
        int l = getN(st, i + 1), r = getN(st, 8 - i);
        st += (l - r) * p[7 - i]; st += (r - l) * p[i];
    }
    return st;
}
int B(int st)
{
    int r1 = getN(st, 4), r2 = getN(st, 5),
        h = st / p[4] / 8, l = st % p[3];
    return r1 + r2 * p[7] + h * p[4] + 8 * l;
}
int C(int st)
{
    int lu = getN(st, 2), ru = getN(st, 3),
        ld = getN(st, 7), rd = getN(st, 6);
    st += (ld - lu) * p[1]; st += (lu - ru) * p[2];
    st += (ru - rd) * p[5]; st += (rd - ld) * p[6];
    return st;
}
void bfs()
{
    queue<pair<int, string> > q;
    q.push(make_pair(s, ""));
    vis[s] = 0;
    while(!q.empty())
    {
        int n = q.front().first;
        string str = q.front().second;
        q.pop();
        if(n == e)
        {
            printf("%d\n", vis[n]); cout << str << '\n';
            return;
        }
        int tn = A(n); //进行每一种操作。
        if(vis[tn] > str.size() + 1)
            vis[tn] = str.size() + 1, 
            q.push(make_pair(tn, str + "A"));
        tn = B(n);
        if(vis[tn] > str.size() + 1)
            vis[tn] = str.size() + 1, 
            q.push(make_pair(tn, str + "B"));
        tn = C(n);
        if(vis[tn] > str.size() + 1)
            vis[tn] = str.size() + 1, 
            q.push(make_pair(tn, str + "C"));
    }
}
int main()
{
    memset(vis, 0x6f, sizeof vis);
    s = 16434824; //八进制初始状态的十进制表示
    //cout << A(s) << endl << B(s) << endl << C(s) << endl;
    rep(i, 0, 7)
    {
        int a;
        cin >> a;
        e += (a - 1) * p[i]; //读入终止状态0
    }
    bfs();
    return 0;
}
```
然后。。。**没了**




---

## 作者：一只萌新 (赞：1)

##  没有用康托展开的算法
 ~~莫名AC~~

蒟蒻看不懂康托展开 不过自己做出来了

如果我们不用数组去存状态

那内存就不会爆了啊

**这里用字符串来表示现在的状态，省去了一个一维数组**

**那么就可以用map来判重**

**这道题就是一个简单的bfs了**

个人觉得康托展开可能知道的人少

所以写了这道题后最好了解一下康托展开

而用字符串表示状态比较好想到

上代码~~其实很简单就是个bfs~~
```cpp
#include<iostream>//手打头文件是个好习惯
#include<cstdio>
#include<queue>
#include<map>
#include<string>
using namespace std;
string goal="",start="12348765";//初始状态
struct Magic{
	string now;int step;//现在魔板的样子 步数
	string op;//操作的序列 
};
queue<Magic> q;
map<string,bool> vis;//注意bfs一定要判重！！！
string change(int opp,string s){	//模拟三种转换
	switch(opp){
		case 0:{	//A
			string temp1="",temp2="";
			for(int i=0;i<4;i++) temp1=temp1+s[i];
			for(int i=4;i<8;i++) temp2=temp2+s[i];
			s=temp2+temp1;
			break;
		}
		case 1:{	//B
			string temp="";
			temp=temp+s[3]+s[0]+s[1]+s[2]+s[7]+s[4]+s[5]+s[6];
			s=temp;
			break;
		}
		case 2:{	//C
			string temp=s;
			s[1]=temp[5];s[2]=temp[1];s[5]=temp[6];s[6]=temp[2];
			break;
		}
	}
	return s;
}
void bfs(){
	Magic s;
	s.now=start;s.step=0;s.op="";
	q.push(s);vis[start]=1;		//bfs的开始
	while(!q.empty()){
		Magic u=q.front();q.pop();
		if(u.now==goal){	//找到目标状态
			printf("%d\n",u.step);
			for(int i=0;i<u.op.size();i++){
				printf("%c",u.op[i]);
				if(i%60==59&&i!=0) printf("\n");
     //题中说：Line 2: 在字典序中最早出现的操作序列，
     //用字符串表示，除最后一行外，每行输出60个字符。
			}
			return;
		}
		for(int i=0;i<3;i++){	//三种操作
			string ss=change(i,u.now);
			if(vis[ss]) continue;
            Magic v；	//入队
			v.now=ss;v.step=u.step+1;
            v.op=u.op+(char)(i+'A')；//操作序列更新
			vis[ss]=1;
			q.push(v);
		}
	}
}
int main(){
	for(int i=1;i<=4;i++){
		int a;
		scanf("%d",&a);
		goal=goal+(char)(a+'0');
	}
	string sx="";
	for(int i=1;i<=4;i++){
		int a;
		scanf("%d",&a);
		sx=(char)(a+'0')+sx;
	}
	goal=goal+sx;
   //这个读入是因为我看错题目了
	bfs();
	return 0;//结束~
}
```
~~大概是数据的问题 竟然AC~~

 #8 171ms/4176KB

由于这道题给出了初始和目标状态，可以用双向宽搜，会更快

但是操作序列可能不太好打 这里就不用双向了

---

## 作者：Long·J·William (赞：1)

模拟一下它的三种操作，宽搜一下就好了。

注意判重，它本来是吓到我了，超过60个字符换行，粗略一算3^60+呐，其实最多应该是22步，状态有40320种（跑了一遍全排列）。

至于判重，建议用map，然而我非常浪费空间的把bool数组开到了10^8.

代码实现（友好的标上了序号，老实敲吧）：

···cpp

```cpp
 1 #include<cstdio>
 2 const int maxn=40321;
 3 int ans,n,s,head,tail,e;
 4 int a[]={10000000,1000000,100000,10000,1000,100,10,1};
 5 int b[]={10,100,1000,1,10000000,10000,100000,1000000};
 6 int c[]={1,1000000,10,1000,10000,100,100000,10000000};
 7 char ch[30];
 8 bool v[100000000];
 9 struct nate{
10     int now,step;//now是目前状态，step是步数。
11     char ts[30];//记录操作指令编码。
12 }q[maxn];
13 void write(int x){//输出部分
14     printf("%d\n",q[x%maxn].step);
15     for(int i=1;i<=q[x%maxn].step;i++)
16     printf("%c",q[x%maxn].ts[i]);
17 }
18 int main(){
19     for(int i=0,j;i<8;i++){
20         scanf("%d",&j);
21         ans*=10;
22         ans+=j;
23     }
24     q[head++].now=12345678;
25     v[q[0].now]=1;
26     if(q[0].now==ans){write(0);return 0;}
27     while(head>tail){
28         n=q[tail%maxn].now;
29         s=q[tail%maxn].step;
30         for(int i=1;i<=s;i++) ch[i]=q[tail%maxn].ts[i];
31         tail++;
32         for(int i=0,j=1;i<8;i++){e+=n/j%10*a[i];j*=10;}
33         if(!v[e]){//操作A
34             q[head%maxn].now=e;v[e]=1;
35             for(int i=1;i<=s;i++) q[head%maxn].ts[i]=ch[i];
36             q[head%maxn].step=s+1;q[head%maxn].ts[s+1]='A';
37             if(q[head%maxn].now==ans){write(head);return 0;}
38             head++;
39         }
40         e=0;
41         for(int i=0,j=1;i<8;i++){e+=n/j%10*b[i];j*=10;}
42         if(!v[e]){//操作B
43                q[head%maxn].now=e;v[e]=1;
44                for(int i=1;i<=s;i++) q[head%maxn].ts[i]=ch[i];
45                q[head%maxn].step=s+1;q[head%maxn].ts[s+1]='B';
46                if(q[head%maxn].now==ans){write(head);return 0;}
47                head++;
48         }
49         e=0;
50         for(int i=0,j=1;i<8;i++){e+=n/j%10*c[i];j*=10;}
51         if(!v[e]){//操作C
52             q[head%maxn].now=e;v[e]=1;
53                for(int i=1;i<=s;i++) q[head%maxn].ts[i]=ch[i];
54                q[head%maxn].step=s+1;q[head%maxn].ts[s+1]='C';
55                if(q[head%maxn].now==ans){write(head);return 0;}
56                head++;
57         }
58         e=0;
59     }
60 }
···
```

---

## 作者：JayYee (赞：1)

**看到题目第一眼，自然而然地想到了康托展开。。（什么？不知道康托展开？？下面的神犇们有解释，你也可以选择百度一下，类似哈希。。我这种苣蒻就不讲了（因为讲不来。。））**

**知道康托，bfs，看着题目觉着思路很容易，就准备操作了，然后一番扫操作之后，发现GG。。那么到底是如何出拐的呢？我在代码里面解释了233**

//膜板（滑稽） 

/\*
这题顺着思路BFS就行了，关键是他要让你输出步骤，你如果每个结构体都用string储存到这一步的所有步骤

的话就会爆空间，所以我们可以在结构体里面定义op为这次的操作，然后用指针存储上一次的状态，最后再用

递归输出最先一个状态的op，然后往后来。

\*/



        

        
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
using namespace std;
const int N=362809;//闲得慌用的9！。。浪费空间，别学我。 
struct node{
    int a[10],step; 
    char op;
    node *pre;  //指针 
    node():step(0),op(0),pre(NULL){ }
}st,ed;
int fac[15]={1},vis[N],kt;
int kangtuo(node x){
    int w[10]={0},sum=0;
    for(int i=1;i<=8;i++)
    for(int j=i+1;j<=8;j++){
        if(x.a[i]>x.a[j]) w[i]++;
    }
    for(int i=1;i<=8;i++)
    sum+=w[i]*fac[8-i];
    return sum+1; 
    //康托展开 
} 
void print(node *k){
    //递归输出步骤 
    if(k->pre==NULL) return;//找到最原始的状态（也就是st）了，什么都不做 
    print(k->pre);
    printf("%c",k->op);
}
int main(){
    for(int i=1;i<=8;i++) fac[i]=fac[i-1]*i;//定义阶乘 
    for(int i=1;i<=8;i++)
    st.a[i]=i;
    st.step=0;
    for(int i=1;i<=8;i++)
    scanf("%d",&ed.a[i]);
    kt=kangtuo(ed);//先记录下end状态的康托 
    queue <node> q;
    q.push(st);
    vis[kangtuo(st)]=1;
    node *k; 
    while(!q.empty()){
        k=new node;//注意，你每次都要新建一个node单元，如果单单是k=q.front()的话他永远都指的是这个单元 ； 
        *k=q.front();
        q.pop();
        if(kangtuo(*k)==kt){
            //搜到结果，就输出步骤和顺序 
            printf("%d\n",k->step);
            print(k);
            break;
        }
        node x;
        //A步骤
        {
        x=*k;
        for(int i=1;i<=4;i++)
        swap(x.a[i],x.a[8-i+1]);
        x.step++; //步骤+1 
        x.op='A';//记录步骤 
        x.pre=k;//记录指针 
        int ktt=kangtuo(x);
        if(!vis[ktt]){
            q.push(x);
            vis[ktt]=1;
            }
        }
        //B步骤
        {
        x=*k;
        swap(x.a[1],x.a[4]);
        swap(x.a[5],x.a[8]);
        swap(x.a[2],x.a[4]);
        swap(x.a[7],x.a[5]);
        swap(x.a[3],x.a[4]);
        swap(x.a[6],x.a[5]);
        x.step++;
        x.op='B';
        x.pre=k;
        int ktt=kangtuo(x);
        if(!vis[ktt]){
            q.push(x);
            vis[ktt]=1;
        }
        }
        //C步骤 
        {
        x=*k;
        swap(x.a[2],x.a[3]);
        swap(x.a[2],x.a[7]);
        swap(x.a[7],x.a[6]);
        x.step++;
        x.op='C';
        x.pre=k;
        int ktt=kangtuo(x);
        if(!vis[ktt]){
            q.push(x);
            vis[ktt]=1;
        }
        }
    }
    printf("\n");
    return 0;
}
```

---

## 作者：Viktley (赞：0)

**看了大佬们的blog，发现都用了map QAQ！！于是来写一篇hash**

---

分析：该题目很明显是用搜索做，如果用深度优先搜索，则可能出现死循环，而且时间很长，所以只能用宽度优先搜索。但是如果没有一种好的方法来判断是否已经加入列表，时间可能会超时，所以，我想到了哈希表。按照初始状态标号，则共有8！=40320个情况。可以将每一种情况唯一对应到0~40319中的一个数。再用宽度优先搜索可以很轻松的实现这一算法。

```cpp
#include<cstdio>
#include<string>
using namespace std;
const int maxx=100003; 
const int rule[3][8]={{8,7,6,5,4,3,2,1},{4,1,2,3,6,7,8,5},{1,7,2,4,5,3,6,8}};
int father[maxx],num[maxx],xx,head,tail; 
string state[maxx],ss,hs[maxx];
char lq[maxx];

bool hash(string s)  //判断字状态s是否存在，存在返回True,不存在添加在hash表中
{
	int ans=0; 
	for (int i=0;i<8;i++)
	 ans=(ans<<3)+(ans<<1)+s[i]-48; 
	int i=0; ans%=maxx; 
	while (i<maxx&&hs[(i+ans)%maxx]!=""&&hs[(i+ans)%maxx]!=s) 
	 i++; 
	if (hs[(i+ans)%maxx]=="")
	{
		hs[(i+ans)%maxx]=s; 
		return false; 
	} else return true; 
}
void bfs()  //广搜
{
	hash("12345678"); 
	state[1]="12345678"; 
	head=0; tail=1; 
	do
	{
		head++; 
		for (int i=0;i<3;i++)
		{
			tail++; 
			father[tail]=head; 
			state[tail]=""; 
			num[tail]=num[head]+1; 
			if (i==0) lq[tail]='A'; else
			if (i==1) lq[tail]='B'; else
			if (i==2) lq[tail]='C'; 
			for (int j=0;j<8;j++)
			 state[tail]+=state[head][rule[i][j]-1];
			if (hash(state[tail])) tail--;//利用hash表判重
			 else if (state[tail]==ss) return;
		}
	} while (head<tail); 
}
void write(int x)
{
   if (x==1) return; 
    write(father[x]); 
   printf("%c",lq[x]); 
}

int main()
{
   	for (int i=0;i<8;i++)
	 {scanf("%d",&xx);ss+=xx+48; }
	if (ss=="12345678") printf("0"); else 
	{
		bfs(); 
		printf("%d\n",num[tail]); 
		write(tail);
	}
}

```
              

---

## 作者：gznpp (赞：0)

显然，这题是一道广搜题。

广搜肯定是要判重的，但是怎么判重呢？

答曰：用STL set。

set是一个基于红黑树的有序集合，不允许有重复元素，正好用来判重。

在set内find一下，也就是在整个set中寻找这个状态，如果返回s.end()，那就是没找到，也就是没有搜索到这种状态。我们就把这种状态push到队列里就可以了。

我们用字符串（STL string）保存状态，因为它自带比较函数，可以丢进set里面去。string中应有8位，从左上角开始按顺时针排列。

不过怎么转移呢？

手写3种操作呗。

对于操作1，分析性质之后发现直接reverse整个字符串即可。

对于操作2右插左，1~3位整体后移，6~8位前移（从1开始标号），用两个临时变量记录再交换左右两列即可。

操作3直接临时变量记录，暴力交换即可。

这题思维难度不算很高，干就是了。很练码功。
```cpp
#include <bits/stdc++.h>
#define rgi register int
using namespace std;
set<string> uni;
string s,e,emp;
queue<string> op,st;
inline string op1(string t)
{
	reverse(t.begin(),t.end());
	return t;
}
inline string op2(string t)
{
	char t1=t[3],t2=t[4];
	for(rgi i=3;i>=1;--i)
		t[i]=t[i-1];
	for(rgi i=4;i<=6;++i)
		t[i]=t[i+1];
	t[0]=t1,t[7]=t2;
	return t;
}
inline string op3(string t)
{
	char t1=t[1],t2=t[2],t5=t[5],t6=t[6];
	t[1]=t6,t[2]=t1,t[5]=t2,t[6]=t5;
	return t;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	for(rgi i=1;i<=8;++i)
	{
		char c;
		cin>>c;
		s.push_back(i+'0');//初状态
		e.push_back(c);
	}
	st.push(s),op.push(emp);//st表示当前魔板状态，op是操作序列
	while(!st.empty())
	{
		string tst=st.front(),top=op.front();//top=temporary op
		st.pop(),op.pop();
		if(tst==e)//搜到了
		{
			cout<<top.size()<<endl<<top<<endl;
			break;
		}
		string tr1=op1(tst),tr2=op2(tst),tr3=op3(tst);//开3个字符串保存3种操作后的状态
		if(uni.find(tr1)==uni.end())//set里没找到，以前没搜过，push进队
		{
			uni.insert(tr1);
			string top1=top;
			top1.push_back('A');
			st.push(tr1),op.push(top1);
		}
		if(uni.find(tr2)==uni.end())
		{
			uni.insert(tr2);
			string top2=top;
			top2.push_back('B');
			st.push(tr2),op.push(top2);
		}
		if(uni.find(tr3)==uni.end())
		{
			uni.insert(tr3);
			string top3=top;
			top3.push_back('C');
			st.push(tr3),op.push(top3);
		}//要求字典序最小，先判A再是B和C
	}
	return 0;
}
```

---

## 作者：千灯 (赞：0)

数据小。  
先寻找到0的位置。  
再往相邻四格互换，模拟每一种情况。  
再用用bfs爆搜，再用map记录就行了。  
其中本蒟蒻把这几个数字拼接起来作为map的下标，写了turn_函数做这个工作 
map为空代表着这个情况没有发生。  
然后再用yes函数判断struct类型的两个变量是否相同。就可以模拟整一个bfs的过程。  
当然最开始必须手动的打一遍初始情况。。。  
但是我用了2个for搞定了。。。  
很显然我的不是最好(代码短)的方法。。。  
但是能AC:  
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node
{
	char ch[3][5];
	int number;
}k,AC;
struct
{
	int last;
	char plan;
}father[50010];
int f=1,r=1;
queue <node> q;
map <string,bool> _map;
int yes(node a,node b)
{
	int key=1;
	for(int i=1;i<=2;++i)
		for(int j=1;j<=4;++j)
		if(a.ch[i][j]!=b.ch[i][j])
		{
			key=0;
			break;
		}
	return key;
}
string turn_(node a)
{
	string str="";
	str=str+a.ch[1][1]+a.ch[1][2]+a.ch[1][3]+a.ch[1][4]+a.ch[2][1]+a.ch[2][2]+a.ch[2][3]+a.ch[2][4];
	return str; 
}
void do_A(node &a)
{
	char tmp[5];
	for(int i=1;i<=4;++i) tmp[i]=a.ch[1][i];
	for(int i=1;i<=4;++i) a.ch[1][i]=a.ch[2][i];
	for(int i=1;i<=4;++i) a.ch[2][i]=tmp[i];
}
void do_B(node &a)
{
	char ch1=a.ch[1][4],ch2=a.ch[2][4];
	for(int i=4;i>=1;--i)
		a.ch[1][i]=a.ch[1][i-1],a.ch[2][i]=a.ch[2][i-1];
	a.ch[1][1]=ch1;
	a.ch[2][1]=ch2;
}
void do_C(node &a)
{
	char ch1=a.ch[1][3];
	a.ch[1][3]=a.ch[1][2];
	a.ch[1][2]=a.ch[2][2];
	a.ch[2][2]=a.ch[2][3];
	a.ch[2][3]=ch1;
}
void dfs(int x)
{		
	if(x==1) return;
	if(father[x].last==1) 
	{
		cout<<father[x].plan;
		return;
	}
	dfs(father[x].last);
	cout<<father[x].plan;
}
int main()
{
	for(int i=1;i<=4;++i) cin>>AC.ch[1][i];
	for(int i=4;i>=1;--i) cin>>AC.ch[2][i];
	for(int i=1;i<=4;++i) k.ch[1][i]=i+'0';
	for(int i=4;i>=1;--i) k.ch[2][i]=9-i+'0';
	q.push(k);
	_map[turn_(k)]=1;
	while(q.empty()==false)
	{
		if(yes(q.front(),AC)==1) 
		{
			cout<<q.front().number<<endl;
			dfs(f);
			return 0;
		}
		k=q.front();
		do_A(k);
		k.number=q.front().number+1;
		if(_map[turn_(k)]==0)
			++r,q.push(k),_map[turn_(k)]=1,father[r].last=f,father[r].plan='A';
		//B
		k=q.front();
		do_B(k);
		k.number=q.front().number+1;
		if(_map[turn_(k)]==0)
			++r,q.push(k),_map[turn_(k)]=1,father[r].last=f,father[r].plan='B';
		//C
		k=q.front();
		do_C(k);
		k.number=q.front().number+1;
		if(_map[turn_(k)]==0)
			++r,q.push(k),_map[turn_(k)]=1,father[r].last=f,father[r].plan='C';	
		q.pop();
		++f;
	}
	return 0;
}
//1 2 3 4 5 6 7 8
```


---

## 作者：QianhanOfficial (赞：0)

bfs+map 308ms AC  
蒟蒻不知道康托展开 不会哈希表 但是蒟蒻硬是用bfs和map水过了这道题。  
具体思路就是把二维的魔板降维~~打击~~成为字符串，然后bfs枚举操作 map映射字符串来判断是否重复 同时队列中记录操作 极其易于理解。  
而且本题解只用了map 没有哈希表 和之前的dalao们不一样orz
```cpp
#include<iostream>
#include<cstdio>
#include<map>
#include<queue>
#include<algorithm>
#include<cstring>
#define re register
using namespace std;
struct node
{
	string p;//储存字符串
	string opr;//储存操作
};
string str = "12345678";//起始状态
string st;//目标状态
map<string, bool> m;
//ABC三种操作在降维之后可以找到规律 之前的dalao们讲的很详细了 蒟蒻就不献丑了
string movea(string s)//操作A
{
	for(re int i = 0; i < 4; ++i) swap(s[i], s[7 - i]);//注意string下标从0开始
	return s;
}
string moveb(string s)//操作B
{
	swap(s[0], s[3]), swap(s[4], s[7]), swap(s[1], s[3]), swap(s[4], s[5]), swap(s[2], s[3]), swap(s[5], s[6]);
	return s;
}
string movec(string s)//操作C
{
	swap(s[1], s[6]), swap(s[2], s[6]), swap(s[5], s[6]);
	return s;
}
void bfs(string istart)//目标字符串
{
	queue<node> q;
	q.push((node){istart, "."});//加入初始状态 一开始没有操作 随便放一个字符就行
	while(!q.empty())
	{
		string s = q.front().p, opr = q.front().opr;
		q.pop();
		if(s == st)//如果相同
		{
			printf("%d\n", opr.size() - 1);//输出操作个数 注意一开始的"."不算在操作个数中
			for(re int i = 1; i < opr.size(); ++i) cout << opr[i];//不要输出"."
			return;//退出
		}
		string a = movea(s), b = moveb(s), c = movec(s);//各种操作
		if(!m[a] && opr[opr.size() - 1] != 'A') m[a] = true, q.push((node){a, opr + "A"});//加了一个小小的剪枝 A不可能连续出现两次(因为那相当于没动)
		if(!m[b]) m[b] = true, q.push((node){b, opr + "B"});//标准bfs 注意opr里把操作加上
		if(!m[c]) m[c] = true, q.push((node){c, opr + "C"});
	}
}
int main()
{
	string s;
	while(cin >> s) st += s;//我们只要数字
	bfs(str);
	return 0;
}
```

---

## 作者：blackjack (赞：0)

康托展开？不存在的，四万多个数字而已，直接map搞定的。
模拟三种操作，我写的是构造函数（呃，希望我没记错名字）。
宽搜的地方都是互相复制的，因为代码基本相似。没写子程序。
两个结构体绕了一点，sta是state的缩写，放在队列里面，记录状态。node表示魔板，用二维数组储存。
凑合着看看吧。
注意特判，当一开始的状态就是结束状态的时候，输出0。
```cpp
#include<bits/stdc++.h>

using namespace std;

int ans=0;
string astr;
int en;

map<int,bool>M;

struct node{
	int rec[3][5];
	node(){
		memset(rec,0,sizeof(rec));
	}
	node A(){
		node tp;
		tp=*this;
		swap(tp.rec[1],tp.rec[2]);
		return tp;
	}
	node B(){
		node tp;
		tp=*this;
		int ta,tb;
		ta=tp.rec[1][1];
		tb=tp.rec[2][1];
		tp.rec[1][1]=tp.rec[1][4];
		tp.rec[2][1]=tp.rec[2][4];
		swap(ta,tp.rec[1][2]);
		swap(tb,tp.rec[2][2]);
		swap(ta,tp.rec[1][3]);
		swap(tb,tp.rec[2][3]);
		swap(ta,tp.rec[1][4]);
		swap(tb,tp.rec[2][4]);
		return tp;
	}
	node C(){
		node tp;
		tp=*this;
		swap(tp.rec[2][2],tp.rec[2][3]);
		swap(tp.rec[1][2],tp.rec[2][3]);
		swap(tp.rec[1][3],tp.rec[2][3]);
		return tp;
	}
	int ha(){
		int res=0;
		for (int i=1;i<=4;++i)
			res=res*10+rec[1][i];
		for (int i=4;i;--i)
			res=res*10+rec[2][i];
		return res;
	}
};

struct sta{
	int step;
	string s;
	node no;
};
queue<sta>que;

void bfs(node be){
	sta a,nx;
	a.step=0;
	a.no=be;
	a.s="";
	que.push(a);
	node tp;
	int temp=0;
	while (!que.empty()){
		a=que.front();
		tp=a.no.A();
		temp=tp.ha();
		if (!M[temp]){
			M[temp]=1;
			nx.s=a.s;
			nx.s=nx.s+'A';
			nx.no=tp;
			nx.step=a.step+1;
			que.push(nx);
		}
		if (temp==en){
			ans=nx.step;
			astr=nx.s;
			return ;
		}
		tp=a.no.B();
		temp=tp.ha();
		if (!M[temp]){
			M[temp]=1;
			nx.s=a.s;
			nx.s=nx.s+'B';
			nx.no=tp;
			nx.step=a.step+1;
			que.push(nx);
		}
		if (temp==en){
			ans=nx.step;
			astr=nx.s;
			return ;
		}
		tp=a.no.C();
		temp=tp.ha();
		if (!M[temp]){
			M[temp]=1;
			nx.s=a.s;
			nx.s=nx.s+'C';
			nx.no=tp;
			nx.step=a.step+1;
			que.push(nx);
		}
		if (temp==en){
			ans=nx.step;
			astr=nx.s;
			return ;
		}
		que.pop();
	}
}
		
int main(){
	freopen("msquare.in","r",stdin);
//	freopen("msquare.out","w",stdout);
	node enn,be;
	for (int i=1;i<=4;++i)
		cin>>enn.rec[1][i];
	for (int i=4;i;--i)
		cin>>enn.rec[2][i];
	en=0;
	en=enn.ha();
	for (int i=1;i<=4;++i)
		be.rec[1][i]=i;
	be.rec[2][4]=5;
	for (int i=3;i;--i)
		be.rec[2][i]=be.rec[2][i+1]+1;
	if (en!=12345678)
		bfs(be);
	else{
		cout<<0<<endl;
		return 0;
	}
	cout<<ans<<endl<<astr<<endl;
	return 0;
}

```

---

## 作者：Celebrate (赞：0)

既然楼下说了康托的地址，我也不重复了，直接看代码了：

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
struct node
{
    int a[3][5],len;
    char st[210];
}list[410000];
int head,tail;int ed;
bool myhash[410000];
int d[11];bool bk=false;
int kangtuo(node tno)//康托展开 
{
    int a[11],L,k,i,j;
    L=0;
    for(i=1;i<=2;i++)
        for(j=1;j<=4;j++)
        {
            L++;
            a[L]=tno.a[i][j];
        }
    bool bo[10];
    memset(bo,true,sizeof(bo));
    int sum=0;
    for(i=1;i<=7;i++)
    {
        k=0;
        for(j=1;j<a[i];j++) if(bo[j]==true) k++;
        sum=sum+k*d[8-i];
        bo[a[i]]=false;
    }
    return sum+1;
}
void mb_a()//交换上下两行 
{
    node tno=list[head];int i,j;
    for(i=1;i<=4;i++) {int t=tno.a[1][i];tno.a[1][i]=tno.a[2][i];tno.a[2][i]=t;}//改变 
    int k=kangtuo(tno);//康托 
    tno.len=list[head].len+1;
    tno.st[tno.len]='A';
    if(myhash[k]==true)//如果没有找过的话 
    {
        myhash[k]=false;//变为找过 
        tail++;list[tail]=tno;//往下搜索 
        if(k==ed)//如果是最后一个 
        {
            printf("%d\n",tno.len);
            for(i=1;i<=tno.len;i++)
            {
                printf("%c",tno.st[i]);
                if(i%60==0) printf("\n");
            }
            bk=true;
        }
    }
}
void mb_b()//将最右边的一列插入最左边 
{
    node tno=list[head];int i,j;
    tno.a[1][1]=list[head].a[1][4];
    for(i=2;i<=4;i++) tno.a[1][i]=list[head].a[1][i-1];
    tno.a[2][1]=list[head].a[2][4];
    for(i=2;i<=4;i++) tno.a[2][i]=list[head].a[2][i-1];
    int k=kangtuo(tno);
    tno.len=list[head].len+1;
    tno.st[tno.len]='B';
    if(myhash[k]==true)
    {
        myhash[k]=false;
        tail++;list[tail]=tno;
        if(k==ed)
        {
            printf("%d\n",tno.len);
            for(i=1;i<=tno.len;i++)
            {
                printf("%c",tno.st[i]);
                if(i%60==0) printf("\n");
            }
            bk=true;
        }
    }
}
void mb_c()//魔板中央四格作顺时针旋转 
{
    node tno=list[head];int i,j;
    tno.a[1][2]=list[head].a[2][2]; tno.a[1][3]=list[head].a[1][2];
    tno.a[2][2]=list[head].a[2][3]; tno.a[2][3]=list[head].a[1][3];
    int k=kangtuo(tno);
    tno.len=list[head].len+1;
    tno.st[tno.len]='C';
    if(myhash[k]==true)
    {
        myhash[k]=false;
        tail++;list[tail]=tno;
        if(k==ed)
        {
            printf("%d\n",tno.len);
            for(i=1;i<=tno.len;i++)
            {
                printf("%c",tno.st[i]);
                if(i%60==0) printf("\n");
            }
            bk=true;
        }
    }
}
int main()
{
    int i,j;d[0]=1;for(i=1;i<=8;i++) d[i]=d[i-1]*i;
    int gg[10];for(i=1;i<=8;i++) scanf("%d",&gg[i]);
    bool bbb=true;
    for(i=1;i<=8;i++) if(gg[i]!=i) bbb=false;
    if(bbb==true) 
    {
        printf("0");
        return 0;
    }
    list[0].a[1][1]=gg[1];list[0].a[1][2]=gg[2];//一开始记录魔板的状态 
    list[0].a[1][3]=gg[3];list[0].a[1][4]=gg[4];//我用for会玄学错误 
    list[0].a[2][1]=gg[8];list[0].a[2][2]=gg[7];
    list[0].a[2][3]=gg[6];list[0].a[2][4]=gg[5];
    list[0].len=0;
    list[1].a[1][1]=1;
    list[1].a[1][2]=2;list[1].a[1][3]=3;
    list[1].a[1][4]=4;list[1].a[2][1]=8;
    list[1].a[2][2]=7;list[1].a[2][3]=6;
    list[1].a[2][4]=5;
    ed=kangtuo(list[0]);//记录尾 
    head=tail=1;
    memset(myhash,true,sizeof(myhash));myhash[kangtuo(list[1])]=false;
    while(head<=tail)
    {
        mb_a();if(bk==true) return 0;
        mb_b();if(bk==true) return 0;
        mb_c();if(bk==true) return 0;
        head++;
    }
    return 0;
}
```

---

## 作者：Sarah (赞：0)

初看此题的时候就想到用广搜，然后就觉得需要两个函数，一个能够给定全排列的字典序次序能够求出这个全排列，第二个是给定全排列求它的字典序次序，搞了好长时间终须肝出来了，结果看了题解才知道有现成的算法(康托展开)，误打误撞写出来了233333，那么下面就给大家看看我的乱搞算法吧
```cpp
/*
ID: z8493331
LANG: C++
TASK: msquare
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using std::swap; 
using std::next_permutation;
using std::queue;
int fac[20];
int target[20];
struct node{
	int pre,order;
	char opt;
	void init(int ord,int p,int o){
		order=ord;pre=p;opt=o;
	}
};
int get_order(int a[]){
	int ans=0;
	for(int i=1;i<=8;i++){
		int cnt=0;
		for(int j=1;j<i;j++){
			if(a[j]<a[i])
				cnt++;
		}
		ans+=(a[i]-cnt-1)*(fac[8-i]);
	}
	return ans+1;
}
void get_per(int order,int a[]){
	bool vis_[9];
	memset(vis_,0,sizeof(vis_));
	for(int i=1;i<=8;i++){
		int k;
		for(k=1;k<=8&&order>(k-1)*fac[8-i];k++);
		k--;
		int z=k;
		int j=1;
		while(1){
			if(vis_[j])
				k++;
			if(j==k)
				break;
			j++;
		}
		a[i]=j;
		vis_[j]=true;
		order-=(z-1)*fac[8-i]; 
	}
}
bool vis[40321];
queue<node> q;
void init(){
	memset(vis,0,sizeof(vis));
	fac[0]=1;
	for(int i=1;i<=8;i++){
		fac[i]=i*fac[i-1];
	}
	for(int i=1;i<=8;i++){
		scanf("%d",&target[i]);
	}
}
void opt_A(int a[]){
	for(int i=1;i<=4;i++){
		swap(a[i],a[8-i+1]);
	}
}
void opt_B(int a[]){
	int x=a[4],y=a[5];
	for(int i=4;i>1;i--){
		a[i]=a[i-1];
	}
	for(int i=5;i<8;i++){
		a[i]=a[i+1];
	}
	a[1]=x;
	a[8]=y;
}
void opt_C(int a[]){
	int x=a[2];
	a[2]=a[7];
	a[7]=a[6];
	a[6]=a[3];
	a[3]=x;
}
char pre_opt[40321];
int pre_node[40321];
void print(int order, int ans_){
	if(order==1){
		printf("%d\n",ans_);
		return ;
	}
	print(pre_node[order],ans_+1);
	printf("%c",pre_opt[order]);
}
void bfs(){
	while(!q.empty()) q.pop();
	node a;a.init(1,0,' ');
	q.push(a);
	vis[1]=true;
	int tar=get_order(target);
	if(tar==1){
		printf("0\n");
		return;
	}
	while(!q.empty()){
		int per[9];
		node f=q.front();q.pop();
		get_per(f.order,per);
		int p_=get_order(per);
		int per_[9];
		memcpy(per_,per,sizeof(per));
		opt_A(per_);
		int x=get_order(per_);
		if(!vis[x]){
			node p;p.init(x,p_,'A');
			pre_opt[x]='A';
			pre_node[x]=p_;
			q.push(p);
			vis[x]=true;
			if(x==tar){
				print(x,0);
				return ;
			}
		}
		memcpy(per_,per,sizeof(per));
		opt_B(per_);
		x=get_order(per_);
		if(!vis[x]){
			node p;p.init(x,p_,'B');
			pre_opt[x]='B';
			pre_node[x]=p_;
			q.push(p);
			vis[x]=true;
			if(x==tar){
				print(x,0);
				return ;
			}
		}
		memcpy(per_,per,sizeof(per));
		opt_C(per_);
		x=get_order(per_);
		if(!vis[x]){
			node p;p.init(x,p_,'C');
			pre_opt[x]='C';
			pre_node[x]=p_;
			q.push(p);
			vis[x]=true;
			if(x==tar){
				print(x,0);
				return ;
			}
		}
	}
}
int main(){
	freopen("msquare.in","r",stdin);
	freopen("msquare.out","w",stdout);
	init();
	bfs();
	printf("\n");
	return 0;
}
```

---

