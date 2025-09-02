# Power Crisis

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=87

[PDF](https://uva.onlinejudge.org/external/1/p151.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA151/2b7fc9e4df48b383902b9f5285f0316b5f437407.png)

## 样例 #1

### 输入

```
17
0```

### 输出

```
7```

# 题解

## 作者：Nanfeng (赞：20)

第一篇题解 ~~可以点个赞再走么~~

此题只需要从1到n-1枚举所有m，找到最后输出的为13的即可。

（m >= n时与m%n等价）

因为，最开始要停1号，所以问题转化为从2到n中去m的约瑟夫环，最后取13，转化为：

从1到n-1中去m的约瑟夫环，最后取12。

约瑟夫环公式：f[i+1] = (f[i]+m)%i   { f[0] = 0 }

（数字从0到n-1，f[i]为长度为i的环最后的输出，原理为映射转化）

~~不应该是黑题~~

代码很短

	#include <bits/stdc++.h>
	using namespace std;
    int n;
	int main()
	{
    	while ( cin >> n && n ) //输入为0结束 
		{
    		for(int i = 1; i < n; i++) 
			{
        		int k = 0;
        		for(int j = 1; j < n; j++)
            		k = (k + i) % j;//约瑟夫环公式
        		if(k == 11) 
				{
            		printf("%d\n", i);
            		break;
        		}
    		}
		}
    	return 0;
	}

---

## 作者：Augen_stern (赞：3)

### Part 1 分析算法：

这是一道经典的约瑟夫环问题；

首先我们知道解决这类问题有一个公式是 $f[i+1]=(f[i]+m) \bmod i$ 且初始化 $f[0]=0$；

但题目中 $m$ 未知，所以可以采取枚举 $m$ 的循环来实现；

### Part 2 CODE：

解决问这些，就可以飞速秒代码了：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<math.h>
#include<algorithm>
#define INF 0x7fffffff/2
using namespace std;
int n;
int main() {
	while(scanf("%d",&n)) // 多组数据
	{
		if(n==0) return 0; // 是0直接程序结束;
		for(int i=1;i<n;i++) // 枚举题目中的m; 
		{
			int k=0;
			for(int j=1;j<n;j++) 
			{
				k=(k+i)%j; // 约瑟夫环公式; 
			}
			if(k==11) // 13是从0-12中取，而去掉首个(第一个舍掉)就变成了0-11; 
			{
				printf("%d\n",i);
				break; // 找到答案后停止枚举; 
			}
		}
	}
}
```
自己动手，丰衣足食！

2021.8.9 12:04：第一次提交；

若干次提交（新手）还是在排版上有所忽略；

终于一个月后，在自己的博客中看见了这一篇危险的题解；

于是，痛定思痛，完善了排版；

2021.9.16 16:13 第六次提交！

---

## 作者：Moon_Lighter (赞：3)

### 题意：
有n个电场，按约瑟夫环的规则断电，最后一个不断电，要求将最后一个断电的电场停在13号。
### 分析：
约瑟夫环公式： $f_{i+1}=(f_i+m)$ $\bmod$ $i$ 。
注意，编号一定是从 $0-n$  。

---
## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main() 
{    
    int n; 
    while(cin>>n&&n）
    {
      for(int i=1;i<n;i++) 
      {
	  int x = 0; 
	  //为什么不是j<=n 因为第一个人直接走了。所以只有n-1个人 
	  //为什么j=2开始，因为只有一个人(j=1)时，循环一次结果也不会变。 
	  for(int j=2;j<n;j++)  
	  x=(x+i)%j;
	  //等于11是因为13是从0-12，去掉首个(第一个电站直接没了)就变成了0-11。
          if(x==11) 
          { 
             cout<<i; 
             break; 
          } 
     }
     return 0;
 }
```


---

## 作者：lyb666666 (赞：2)



- #### 题意 （~~题面上翻译的貌似过于简洁~~）
嗯。。让你输出好几个整数N（13<=N<=100），**并以0结尾**。
然后让你求**最小的m**，使得**13号**是最后一个出列的数字。
此处的”列“呢就是以m为周期出列的约瑟夫环。。（~~似乎还是没讲清？？~~）



- #### 思路
数据范围不大，那就模拟整个过程吧quq

	~~ps：第一篇题解上的蜜汁公式真的tql~~
 


- #### 代码（~~废话太多？？？~~）
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
bool check(int p){//判断m=p时符不符合条件 
	int num=0,NUM=0;//num:已循环次数。。NUM:已出队个数 
	queue<int>q;//用一个队列来模拟过程 
	for(int i=2;i<=n;i++)q.push(i);//先让所有数字都入队（由于1直接出列就不鸟ta了） 
	while(!q.empty()){//一直循环到所有数字都出列为止 
		num++;//循环次数++ 
		int firstnum=q.front();//保存一下当前队首（轮到哪个数） 
		if(num%p==0){//如果到了循环周期 
			q.pop();NUM++;//出列。。出列个数++ 
			if(NUM==(n-1)&&firstnum==13)return 1;//如果这是最后出列的，并且还是13，那就符合条件 
			else if(firstnum==13)return 0;//反之，若13要出列，却不是最后一个，那就不符合条件 
		}
		else{q.pop();q.push(firstnum);}
		//如果不是循环周期，只是很普通的路过，那就把这个数放队尾，这就形成了一个环quq 
	}
}
int main(){
	while(cin>>n&&n!=0){//只要不为"0"就一直输 
		for(int i=1;i<=n;i++)//从小枚举,这样一找到就可以输出辣 
			if(check(i)){cout<<i<<endl;break;}//当m=i时能符合条件就输出并跳出循环 
	}
	return 0;
}
```


------------


---

## 作者：fengyuhaoz (赞：1)

好的，依旧是我。（第二篇）

先来一段开场白：好的，介绍完了。

直入主题：

首先

来不及解释了，上代码！

```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
int n;//全局变量 
int m;//定义 
int main()
{
    while(scanf("%d",&n)&&n!=0)//因为不知道多少次，所依用while 
    {
        for(int i=1;i<n;i++){//for循环 
            m=0;//关键！！！！ 
            for(int j=1;j<n;j++)
                m=(m+i)%j;//约瑟夫环的公式，关键！！！（不会的去做一做题目） 
            if(m==11){printf("%d\n",i);break; }}}// 当m==11时，输出 
    return 0;//结束 
}
```
最后，希望管理大大通过！
还有，切勿抄袭！
有不对的地方，请大家斧正！
制作不易，请谅解！

---

## 作者：Tenshi (赞：1)

这道题其实和约瑟夫问题差不多嘛~

用队列模拟一下这个过程就可以过啦！~~知道思路想要AC Code的直接下拉qwq~~

不知道队列是什么的同学可以baidu一下，或者看看这个：

https://oi-wiki.org/ds/queue/

## 具体思路：
##### 首先准备两个容器：
```cpp
		queue<int>q;
		stack<int>s;
```
queue是用来模拟队列的。

而stack则用于存放出队的成员，我们需要求的最后一个出队成员正好就在栈顶。

因为这题数据很松，所以直接开始枚举m

```cpp
for(int m=1;m<=n;m++)//开始枚举m 
```
然后，将队列的成员入队

```cpp
for(int i=1;i<=n;i++) q.push(i);
```
### 下面是关键语句：
```cpp
while(!q.empty())//队列非空时候进行模拟
{
	if(cnt%m==0)
	{
		s.push(q.front());//把出队的成员入栈 
		q.pop();
		cnt++;
	} //模拟出队
			 
	else
	{
		q.push(q.front());
		q.pop();
		cnt++;
	}//如果暂时不需要出队就塞入队尾 
}
```
想象一下这个过程是怎么样的吧，从1开始走，我们先让1出队，并且压入栈中，然后通过cnt计算走了多少步

当cnt%m=0的时候，就意味着相应的元素需要入栈、出队;

如果cnt%m≠0，我们认定这个成员暂时不需要出队，把他压入队尾即可。

~~理解了这些，就可以AC啦~~

AC Code：
```cpp
#include<cstdio>
#include<iostream>
#include<cmath>
#include<queue> 
#include<stack>
#include<cstring>
#include<cstdlib>
using namespace std;
typedef unsigned long long ll;
int main(){
	int n;
	while(cin>>n&&n!=0){
		queue<int>q;
		stack<int>s;

		for(int m=1;m<=n;m++)//开始枚举m 
		{
			for(int i=1;i<=n;i++) q.push(i);
			int cnt=0;
			while(!q.empty())//队列非空时候进行模拟
			{
				if(cnt%m==0)
				{
					s.push(q.front());//把出队的成员入栈 
					q.pop();
					cnt++;
				} //模拟出队
			 
				else
				{
					q.push(q.front());
					q.pop();
					cnt++;
				}//如果暂时不需要出队就塞入队尾 
			}
			 
			if(s.top()==13)//如果最后一个出队的元素确实是13，则输出答案，结束枚举
			{
				cout<<m<<endl;
				break;
			} 
		}		
	}
	return 0;
}
```


---

## 作者：Victorique_De_Blois (赞：1)

这一题有点类似于[P1996约瑟夫问题](https://www.luogu.org/problemnew/show/P1996)。

约瑟夫问题是比较经典的循环模拟问题。我讲解一下循环有关语句。

### 1.for循环

格式：

    for(初始化;在什么条件下执行循环;每循环一次都会执行的语句)
    {
        ...;
    }	

我举个例子：

	for(int i=1;i<=3;i++)//初始化定义i等于1;当i<=3时执行循环语句，每循环一次i自增1
    {
    	printf("i=%d\n",i);
    }

输出：

		i=1
        i=2
        i=3
        
是不是很容易鸭！

### 拓展：for语句其实很万能。

从以上我们了解到的for语句的性质来看，for语句有很多种用途。

例如可以将它当做if语句使用。

将两个对比一下：

	if(...)
    {
    	...;
    }
    
等同于：

	for( ;...; )
    {
    	...;
    }

但是注意：圆括号内无论如何都要打上两个分号。

联想起最简单的快读模板，有一种写法就是利用for循环的性质。

	int x=0;
	char ch=getchar();
    for(;ch<='9'&&ch>='0';ch=getchar())
    	x=x*10+ch-48;
        
这里快读运用了getchar比输入流或scanf语句更加快速的优势，结合for循环使用。

将它翻译成~~易语言~~我们容易理解的内容：

	读入一个字符存入ch;
    当ch在0~9的范围内执行以下语句，且每执行一次都会再次读入一次ch,直到ch不为数字：
    	x=x*10+ch-48;

不会快读同学的暂且不需要特意学习它，只需要理解它的一个特性即可。
### 2.while语句

格式：
	
    	while(执行这个循环的条件)
        {
        	...；
        }

注意，当符合括号中的循环条件时，它会一直重复循环。所以在写这类语句的时候必须思考清楚条件会不会一直存在，否则可能会陷入死循环的局面。

同理，条件一直存在只需写一个

	while(true) 或者while(1)
    
程序就会死循环，除非在程序内使用break或goto。这两个语句在后面会讲解。

### 3.do-while语句

while语句与do-while语句不同的是，do-while语句即使一开始不符合条件，至少也会执行一次。

格式：

	do{
    ...;
    }while(执行条件);
    
请注意，条件表达式出现在循环的尾部，所以循环中的语句会在条件被测试之前至少执行一次。

如果条件为真，控制流会跳转回上面的 do，然后重新执行循环中的语句这个过程会不断重复，直到给定条件变为假为止。

在做广度优先搜索的题目的时候，经常需要使用到do-while语句和队列的配合使用。

## 循环的控制语句

### 1.break语句

用法：

在循环内使用。当遇到break语句时跳出循环。当循环嵌套的时候，仅跳出小循环。

举个例子：

		for(int i=1;i<=10;i++)
        	if(i==9)
            	break;
以上程序，当运行到i等于9的时候，便不再循环，跳出了这次循环。

不要试图在循环外使用break，这会使你的程序编译错误。

### 2.continue语句

这个语句与break不同的是：当在循环内执行了continue语句，会跳过这一次循环并进入下一次循环。

举个例子看看吧：

		for(int i=1;i<=10;i++)
        {
        	if(i%2==0)
            	continue;
            ...;
         }

以上语句会执当i=1、3、5、7、9的情况；而将continue换成break，那么仅能执行i=1的情况。

不要试图在循环外使用continue，理由和break一样。

### 3.goto语句

将控制转移到被标记的语句。但是不建议在程序中使用 goto 语句。

语法
C++ 中 goto 语句的语法：

    goto label;
    ...;
    ....;
    label: statement;
    在这里，label 是识别被标记语句的标识符，可以是任何除 C++ 关键字以外的纯文本。标记语句可以是任何语句，放置在标识符和冒号（:）后边。
    
   以上摘自baidu.
   
   实测：将label写成中文不行。在c++中除了注释，不允许在任何语句中出现中文。谁让中文占两个ASSIC码。
   
虽然在有时候显得十分方便，但还是不建议使用goto语句。

## 回到题目

循环嵌套+暴力枚举轻松解决。

    #include<cmath>
    #include<queue>
    #include<cstdio>
    #include<vector>
    #include<iomanip> 
    #include<cstring>
    #include<iostream>
    #include<algorithm>
    #include<Windows.h>//究极防止抄袭：加了直接爆炸 
    using namespace std;
    int n,m;
    int main()
    {
        while(scanf("%d",&n)&&n!=0)//当读入且读入的不为0  
        {
            for(int i=1;i<n;i++)//仔细想一想为什么不从1开始 
            {
                m=0;//重要的一步：初始化 ,在许多程序中，缺少一个初始化会导致致命错误，例如最短路问题 
                for(int j=1;j<n;j++)//开始踢人 
                    m=(m+i)%j;//约瑟夫环，不懂的去做例题 
                if(m==11)//
                {
                    printf("%d\n",i);
                    break;//输出后可以跳出循环了。 
                }
            }
        }
        return 0;//好习惯 
    }

---

## 作者：cyrxdzj (赞：0)

### 一、基本思路

本题考察[约瑟夫环](https://baike.baidu.com/item/%E7%BA%A6%E7%91%9F%E5%A4%AB%E9%97%AE%E9%A2%98/3857719?fromtitle=%E7%BA%A6%E7%91%9F%E5%A4%AB%E7%8E%AF&fromid=348830&fr=aladdin)的知识。

数据范围是 $13\le N <100$，还算比较小，可以暴力模拟。

### 二、具体思路

现在的问题是，如何暴力模拟约瑟夫环。

我们可以创建一个队列，初始状态下，该队列从队头到队尾依次为 $1$ 到 $N$。

然后循环以下操作，直到队列中只有一个数字。

1. 弹出队头，并不再进入队列中。

2. 将一个数弹出队头，但立即进入队尾。本步骤重复 $m-1$ 次。

该队列中只有一个数字时，这个数字就是“最后一个出列的数字”。只需判断这是不是 $13$ 即可。

### 三、完整代码

```cpp
#include<cstdio>
using namespace std;
bool check(int m,int n)
{
	int queue[10000],front=1,back=n;//queue代表队列数组，front代表队头指针，back代表队尾指针。
	for(int i=1;i<=n;i++)
	{
		queue[i]=i;//初始化。
	}
	for(int i=1;back!=front;i++)//当back=front时，队列中只剩一个数字。
	{
		front++;//执行上面的步骤1。
		for(int j=1;j<=m-1;j++)//重复执行上面的步骤2。
		{
			back++;
			queue[back]=queue[front];
			front++;
		}
	}
	return queue[front]==13;
}
int main()
{
	while(true)
	{
		int n;
		scanf("%d",&n);
		if(n==0)
		{
			break;
		}
		for(int m=1;m<=n-1;m++)
		{
			if(check(m,n))
			{
				printf("%d\n",m);
				break;
			}
		}
	}
	return 0;
}

```

### 四、后记

记录：<https://www.luogu.com.cn/record/51405789>。

By [dengzijun](https://www.luogu.com.cn/user/387836)

---

## 作者：happy_dengziyue (赞：0)

### 1 思路

通过约瑟夫环公式 $f_{i+1}=(f_i+m)$ $mod$ $i$ 可得代码。

### 2 代码与记录

```cpp
#include<cstdio>
using namespace std;
int n;
int main(){
	while(true){
		scanf("%d",&n);
		if(n==0){//退出循环
			break;
		}
		for(int m=1,k;m<n;++m){
			k=0;
			for(int i=1;i<n;++i){//约瑟夫环公式部分
				k=(k+m)%i;
			}
			if(k==11){//可以输出
				printf("%d\n",m);
				break;
			}
		}
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/51477396)

By **dengziyue**


---

## 作者：F_S_R_M (赞：0)

#### 不会公式。。。通俗易懂的方法：
# 核心思路：
1、从1枚举到n，一定至少会有一个符合条件，

所以最外层是一个for循环

2、进行do-while循环，约瑟夫问题，

将符合条件的标记已访问过，下一次就略过这个数，不计入计数器里面

3、如果已经有n-1个已访问过，而13却没有被访问过，直接输出i，退出

**注意:**


数据千万条，清空第一条。

多测不清空，爆零两行泪。

# 代码：
```cpp
#include<iostream>
#include<bits/stdc++.h>
using namespace std;
int visit[10000];
int o=1;
int main()
{
	while(1)
	{
		int n;
		cin>>n;
		if(n==0)
			break;		//如果输入的是0，就退出 
		int t=1,s=0,u=1;
		for(int i=1;i<=n;i++)
		{
			memset(visit,0,sizeof(visit));
			t=1;
			s=0;
			u=1;
			visit[1]=1;			//注意清空 
			do
			{
				t++;		
				if(t==n+1)
					t=1;	//到头就 = 1 
				if(visit[t]==0)
					s++;		//如果没有被访问过就计入计数器 
				if(s==i)		//如果计数器到达指定的数，就标记为已访问过 
				{
					s=0;
					u++;		//计数器 ++ 
					visit[t]=1;
				}
			} while(u<n-1);
			if(visit[13]==0)
			{
				cout<<i<<'\n';
				break;
			}
		}
	}
	return 0;
}
```


---

