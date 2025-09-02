# Team

## 题目描述

Now it's time of Olympiads. Vanya and Egor decided to make his own team to take part in a programming Olympiad. They've been best friends ever since primary school and hopefully, that can somehow help them in teamwork.

For each team Olympiad, Vanya takes his play cards with numbers. He takes only the cards containing numbers 1 and 0. The boys are very superstitious. They think that they can do well at the Olympiad if they begin with laying all the cards in a row so that:

- there wouldn't be a pair of any side-adjacent cards with zeroes in a row;
- there wouldn't be a group of three consecutive cards containing numbers one.

Today Vanya brought $ n $ cards with zeroes and $ m $ cards with numbers one. The number of cards was so much that the friends do not know how to put all those cards in the described way. Help them find the required arrangement of the cards or else tell the guys that it is impossible to arrange cards in such a way.

## 样例 #1

### 输入

```
1 2
```

### 输出

```
101
```

## 样例 #2

### 输入

```
4 8
```

### 输出

```
110110110101
```

## 样例 #3

### 输入

```
4 10
```

### 输出

```
11011011011011
```

## 样例 #4

### 输入

```
1 5
```

### 输出

```
-1
```

# 题解

## 作者：Zxsoul (赞：5)

# CF401C Team 题解   
####  （~~我肝了两个小时，就在崩溃之际我AC了，可能是我太菜~~）
### [友情传送门](https://www.luogu.com.cn/problem/CF401C)
### [欢迎光临我的Bolg](https://home.cnblogs.com/u/lToZvTe)

---
**思路概括**：

- 先用 **01** 或者$m>2n$ 或者 $n > m + 1$  的情况———即输出 -1 的情况。

              
			m>2n  ||  n > m + 1 
 
# 当序列成立时就会有三种情况 :

## 当 **n >  m** 时  
   即 **0** 的个数比 **1** 的个数多时，此时就会多出一个 **0** 
(如果疑惑，**Code** 有详解 ，最好独立思考)

## 当 **n <=  m < 2n** ,
  当前的 **n** 和 **m** 刚好可以凑成符合条件的序列，只是 **01** 和 **011** 的个数问题——( **011** 的个数是 **m - n**，则剩余的 **n** 个自然就是 **01** ,~~感觉**贪心**~~ )
      
##  当 **m > 2n** 时，
   就会多出 **m - 2n** 个 **1** ,剩余的 **2n** 个数与 **2** 做相同处理
 
 ##  三种情况的部分 **Code**
1
---
```cpp
		(n > m)
  		{
			cout<<"0";
		for( int i = 1;i <= m;i++)
			cout<<"10";
     		 }
```


2
---

```cpp
		(n <= m <= 2n)              
  			{
 			for(int i = 1;i <= m - n; i++)
		 		cout<<"011";		 	
			for(int i = 1;i <= 2*n-m; i++)
				 cout<<"01";
  			}
```
3
--
```cpp

		(m > 2n)
			for(int i = 1;i <= m-n*2; i++)
		 		cout<<"1";
      			 m = 2*n;
         		for(int i = 1; i <= m; i++)
         			cout<<"110";

```



#                 Code
```cpp
/*
 	2020/10/3 20:59
 	CF401C Team
	by BZQ
*/
#include<iostream>
using namespace std;
int n,m;
int main(){
	cin >> n;
	cin >> m;
	if(m > n*2 + 2 || n > m+1) cout << -1;//判断无解的情况 
	else
	{
		if(m > n*2){         //此处将 m >= n 的情况和 m > 2n 的情况做个合并。                
			for(int i = 1;i <= m - n*2; i++)//先对 m > 2n 进行预处理，之后操作一样。
				cout << "1";
			m = 2 * n; //注意：在做完预处理后，现在的序列就相当于是一个满011和01的序列，所以更新m; 				
		}
	    if(m >= n){
			for(int i = 1;i <= m - n; i++) // 先贪大后贪小 
		 		cout << "011";
			for(int i = 1;i <= 2*n-m; i++)
		 		cout << "01";
		}
 		if(n > m){
			cout << "0"; // 回复思路 1 中的问题：以为无解的边界为 n > m+1 故要想此时的 n > m 成立，当且仅当 n = m + 1; 
			for(int i = 1;i <= m;i++)
			 	cout << "10";
		}
	}
	return 0;
} //感谢观看， 
```
## 不懂得可以问我，My Bolg


---

## 作者：Terrific_Year (赞：4)

这里先声明，本方法样例1不过，但测试点全过

可行数据：```m<=n*2+2,n<=m+1```

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int main(){
	cin>>n>>m;
	if(n>m+1||m>n*2+2)cout<<-1;//如果超出:-1;
	else{//没超出：
		if(n>m){1.n>m;//输出m个01后输出0；
			for(int i=1;i<n;i++)cout<<"01";
			cout<<0;
		}
		else{//2.m>2n;输出m-2n个1；输出n个011；3.2n>m>=n;输出m-n个011；输出2n-m个01；
			if(m>n*2){
            for(int i=0;i<m-n*2;i++)
            	cout<<1;
            m=2*n;
        }
			for(int i=0;i<m-n;i++)cout<<"011";
			for(int i=0;i<n*2-m;i++)cout<<"01";
		}
	}
	return 0;
}
```
~~再也不见~~

---

## 作者：KEBrantily (赞：2)

## 扯在前面

本题的英文翻译很有意思，很符合CF大多题的故事风格，但是luogu的翻译更过于直白易懂

~~如果让我看英文故事做题我怕我都不知道该怎么下手~~



------------
# 正文

**题意**：

构造一个01序列，包含n个0，m个1要求不存在连续2个0，或3个1


------------


什么意思呢，简单说就是，理想状态下我们能把所有0和1消耗完且消耗的最多的情况就是这样

```latex
假设有十个1
那么最多有
010101010101010101010
十一个0

最少有
11011011011011
四个0
```

#### 因此我们可以得出两种无解的情况：

- 0很多（1很少） 此时n>m+1  或m<n-1;
- 0很少（1很多） 此时n<(m+2)/2  或m>2n+2;

那我们就判断出来，输出-1；


------------


之后再想想怎么构造01序列：

根据测试，我们可以发现，同样的m和n可能会构造出不同的01序列（像本题的样例一，若输出011也是对的，因为评测机只统计0和1的个数而不是具体排列方式）

### 那我们就找规律，做法如下：

1. 我们可以选择构造01和011序列来把总序列拼出来；
1. 当m=2n时，我们就可以愉快的输出n个011，同理，当m=n时，我们也可以愉快的输出n个01；
1. 如果情况并不是正好怎么办，因为无解的情况已经判断完，所以我们手中的情况保证有解，所以**如果多了1就在总序列前面输出，如果少了1就从把后面的011换成01就好了**

之后输出，代码如下
```cpp
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<algorithm>

using namespace std;

int n,m,tot1,tot2,cnt;

int main(){
	scanf("%d%d",&n,&m);
	if(m>2*n+2){
		cout<<-1;
		return 0;
	}
	if(m<n-1){
	    cout<<-1;
	    return 0;
	}
	if(m==n*2+1){cout<<1;m--;}
	if(m==n*2+2){cout<<11;m-=2;}
	while(n){
		cout<<0;
		if(m!=0){
			if(m<n*2){cout<<1;m--;}
			else {cout<<11;m-=2;}
		}
		n--;
	}
	return 0;
}
```

##### 谢谢观看


---

## 作者：Blunt_Feeling (赞：2)

## CF401C Team 题解
首先，可以发现 $m$ 的最小值为 $n-1$（01 01 01 $\cdots$ 01 01 0），$m$ 的最大值为 $2 \times (n+1)$（11 011 011 011 $\cdots$ 011 011）。所以如果 $m$ 不在这个范围之内，直接输出 $-1$。

接下来是有解的情况：不妨考虑字典序最小的一种解。为了让字典序最小，输出的第一个数字最好是 $0$。但是当 $m>2n$ 时，开头第一个数字一定要是 $1$。这时候可以分两种情况：
- $m=2 \times n+1$ 时，输出一个 $1$，$m \gets m-1$；
- $m=2 \times (n+1)$ 时，输出两个 $1$，$m \gets m-2$。

之后可以把输出的内容分成 $n$ 段，每段为 $0$ 加上一到二个 $1$。当然，如果 $m=0$ 了也就不用输出 $1$ 了。于是再分两步走：
- $m<2 \times n$ 时，输出一个 $1$，$m \gets m-1$；
- $m \ge 2 \times n$ 时，输出两个 $1$，$m \gets m-2$。

这样可以合理地控制 $1$ 的个数，又让字典序最小。

### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int main()
{
	cin>>n>>m;
	if(m<n-1||m>2*(n+1)) cout<<-1,exit(0); //无解的情况
	if(m==2*n+1) cout<<1,m--;
	else if(m==2*(n+1)) cout<<11,m-=2;
	while(n) //循环n次
	{
		cout<<0;
		if(m!=0)
		{
			if(m<n*2) cout<<1,m--;
			else cout<<11,m-=2;
		}
		n--;
	}
	return 0;
}
```


---

## 作者：米奇奇米 (赞：2)

## 题解-CF401C Team

### 题目意思
很小清新，构造一个$01$序列，包含$n$个$0$以及$m$个$1$要求不存在连续$2$ 个$0$或$3$个$1$

### $Solution$

* **对于输出$-1$的情况很简单**：

当$n>m+1$ 或者 $m>n*2+2$

* ** 

* **对于$n*2>m$的情况**

如果$n=m+1$需要特判输出$m$对$[0,1]$,最后在输出$0$

对于其他的情况我们可以把$[1,1,0]$拼成一对，把$[1,0,1,0]$拼成一对。那么我们可以设前面一种方案出现次数为$t$,则有方程：$t+(m/2-t)*2=n$。但是如果$m$为奇数最后还要输出一对$[1,0]$

* **
* **对于剩余的情况**

只要输出$n$对$[1,1,0]$,如果$m-k*2!=0$在输出$m-k*2$对$[1]$即可。

### $Code$
```cpp
#include <bits/stdc++.h>
using namespace std;

int n,m,now1,now2;

int main() {
	scanf("%d%d",&n,&m);
	if(n>m+1||m>n*2+2) {
		printf("-1\n"); 
		return 0;
	}
	if(n==2&&m==1) 	{
		printf("010\n"); 
		return 0;
	}
	int k=n;
	if(n==m+1) {
		for ( int i=1;i<=m;i++ ) putchar('0'),putchar('1');
		putchar('0');
		return 0;
	}
	if(k*2>m) {
		int sum=m-n;
		for ( int i=1;i<=sum;i++ ) putchar('1'),putchar('1'),putchar('0');
		for ( int i=1;i<=m/2-sum;i++ ) putchar('1'),putchar('0'),putchar('1'),putchar('0');
		if(m&1) putchar('1'),putchar('0');
		return 0;
	}
	for ( int i=1;i<=k;i++ ) putchar('1'),putchar('1'),putchar('0');
	if(m-k*2!=0) 
		for ( int i=1;i<=m-k*2;i++ ) putchar('1');
	return 0;
}
	
	
```



---

## 作者：LightningUZ (赞：1)

还是一样，为了防爆，请在[博客](https://blog.csdn.net/LightningUZ/article/details/89433745)中查看这篇题解。
代码：
```cpp
#include<bits/stdc++.h>
#define N 2001000
using namespace std;
string s;
bool pre0[N];
int n,m;

void Construct()
{
    if (n==m+1)//特判n=m+1
    {
        for(int i=0;i<n+m;i++)
        {
            putchar(i%2+'0');
        }//01交替输出
        putchar('\n');
        return;
    }
    if (n>=(m+1)/2-1 and n<=m+1)//有解
    {
        for(int i=0;i<m;i++)//先放m个1
        {
            s+='1';//准确来讲这个s只是为了骗分（骗0分）用的，下面没用
        }


        int cnt0=0;//放了多少0
        for(int i=2;i<m;i+=2)//隔两个插入0
        {
            pre0[i]=1;++cnt0;
        }

        int rest=n-cnt0;//还要放多少
        int put=0/*接下来放了多少0*/,pos=0/*第一个能放0(即pre0[i]=0)的位置*/;
        while(put<rest)
        {
            while(pre0[pos]) ++pos;//找一个能放的位置
            pre0[pos]=1;++put;//放上
        }

        for(int i=0;i<m;i++)
        {
            if (pre0[i])//如果前有0就输出
            {
                putchar('0');
            }
            putchar('1');//输出1
        }
    }
    else//无解
    {
        puts("-1");
    }
}
main()
{
    scanf("%d%d",&n,&m);
    Construct();
    return 0;
}


```

---

## 作者：Strange_S (赞：1)

十分简单易懂

没有太多的if和else

无需做太多的判断

经楼上大佬提示，才做出来的。否则很麻烦。
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n,m,k,l;
inline void out(){
	int i;
	for(register int i=1;i<=n;i++){
		cout<<"10";
	}
	return ;
}
int main(){
	cin>>n>>m;                 //读入
	if(n>m+1||m>2*(n+1)){      //判断能否排出
		cout<<"-1";
		return 0;
	}
	if(n==m){                  //分三种，第一种，两数相等。
		out();
		return 0;
	}
	if(n>m){                   //第二种n比m多一
		cout<<"0";
		n--;
		out();
		return 0;
	}
	k=m/2;                    //第三种，m>n
	while(n>k&&n!=0){         //检查n是否是m的一半
		cout<<"1";            //如果不是，让n一个一个和m配对，直到是
		m--;
		cout<<"0";
		n--;
		k=m/2;               //如果一直没有变成m=2n，就一直这样输出
	}
	l=n;
	for(register int i=1;i<=n;i++){     //如果成功，就110的输出
		cout<<"110";                    //就会刚好输出完
		m--;
		m--;
		l--;
	}
	if(m==1){                           //检查有没有多余的m
		cout<<"1";
	}else{
		if(m==2){
			cout<<"11";
		}
	}
	return 0;
}
```

---

## 作者：水里的碳酸钙 (赞：1)

很荣幸第一次提交题解，还是第一份题解。

首先我们可以先判断一下在什么时候这个序列不存在，那么根据题意，最多有连续的2个1，一个0，这个序列一定由110和10或01组成，那么我们可以得出，当n>m+1或者m>2*n+2 时，无解，可以直接输出-1，即：
```cpp
    if(n>m+1||m>2*n+2)	cout << "-1";
```
然后，我们在有解的前提下再分类讨论，分为1比0多和0比1多两种情况。

当1比0多时并且1的个数小于2倍的0的个数时，我们可以用k个110来弥补多的1，k=m-n，剩下的用10补全。如果1的个数比2倍的0的个数还大，由于上面的条件限制，我们只需要输出0的个数个110和一个1或11即可。

当0比1多时，因为0只会比1多1，所以我们只需要输出0的个数个01和一个0即可。

所以，我想这道题还算简单，而且可能有更好的办法做吧，但是，能捉到耗子的猫就是好猫。

完整代码双手奉上：
```cpp
#include<iostream> 
using namespace std;

int main() {
    int n, m;
    cin >> n >> m; //n为0的个数,m为1的个数
    if(n>m+1||m>2*n+2)	cout << "-1";
    else {
    	//分类讨论!! 
        int k;
        if(m>=n&&m<=2*n) {
            k=m-n;
            for(int i=1;i<=k;i++) cout<<"110";
            for(int i=1;i<=(n-k);i++) cout<<"10";
            }
        else if(m>=n&&m>2*n) {
            for(int i=1;i<=n;i++) cout<<"110";
			if(m%2==1) 
				cout<<"1";
			else if(m%2==0)
				cout<<"11";
            }
        else if(m<n) {
            for(int i=1;i<=m;i++) cout<<"01"; //这里跟上面不一样的哈！
			cout<<"0";
        }
    }
    return 0;
}
```

--【END】--

---

## 作者：Suzt_ilymtics (赞：0)

# **日拱一卒，功不唐捐**


------------



### 本人今天刚学数论，因此来水一片题解（逃


------------

## [-->题目传送门<--](https://www.luogu.com.cn/problem/CF401C)
## [-->博客食用更佳<--](https://www.luogu.com.cn/blog/Silymtics/cf401c-team-ti-xie)

------------
相信大家对这道题都有或多或少的想法，那么在这里由本蒟蒻来分享一下自己的思路

------------

# Solution：

题意还是十分简单的，构造一个01序列，并且要求满足不能有两个连续的0或者三个连续的1.

那么先让我们看一下不满足的情况，最后再进行构造

这里我提供两种不满足情况：
## 情况一
```cpp
钦定我们已知有n个0，那么最多可以在序列里填1的方式是：
110110110……11011
我们可以发现，在这种填法下，这个序列已经饱和，且m有一个最大值，即2（n+1）
所以我们可以得出，只要
m > 2 * (n + 1)
那么便不能构造
```

## 情况二
```cpp
钦定我们已知有m个1，按照同样的思路，我们最多可以这样填0：
01010101……01010
此时序列已经达到饱和（指不能再填0了），且0的个数有最大值m+1，所以如果
n > m + 1
那么便不能构造
```

### 下面是判断不能构造的情况的代码
```cpp
	if(m > 2 * n + 2 || n > m + 1) {
		printf("-1");
		return 0;//防止以后出意外，本人喜欢在这里直接结束程序
	}
```

## 下面让我们开始构造序列

我们按“10”和“110”这两个串来输出

### 输出110的条件：

这里有个条件m-1>n，意思是如果m比n多1个以上，只能构造一个110串来减小m和n的差距，同时这个可以保证，当m-1<=n时不去浪费1来构造整个串（大家可以自行考虑一下这个的正确性）
```cpp
if((m-2) <= 2 * n && (m-2) >= 0 && n-1 >= 0 && m - 1 > n) printf("110"),m-=2,n--;
```
### 输出10的条件：
```cpp
if((n-1) <= m && (m-1) >= 0 && n-1 >= 0)	printf("10"),n--,m--;
```
### 考虑到最后可能以1结尾：
```cpp
if(m-1 >= 0) printf("1"),m--;
```
### 如果以0结尾（其实因为我们构造的串是“10”和“110”，所以0结尾的情况已经被包含了）：
```cpp
if(n-1 >= 0) printf("0"),n--;
```
### 然后我信心满满的提交，结果WA声一片，看一眼代码，原来自己忘记考虑以0开头的情况了

通过大量实例我们不难发现，必须以0开头的情况只有n==m+1时

```cpp
if(n - 1 == m) printf("0"),n--;
```

下面是AC代码（自我感觉是所有题解中最简洁的）：
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n,m;
int main()
{
	scanf("%d%d",&n,&m);
	if(m > 2 * n + 2 || n > m + 1) {
		printf("-1");
		return 0;
	}
	while(n>0||m>0){
		if(n - 1 == m) printf("0"),n--;
		if((m-2) <= 2 * n && (m-2) >= 0 && n-1 >= 0 && m - 1 > n) printf("110"),m-=2,n--;
		else if((n-1) <= m && (m-1) >= 0 && n-1 >= 0)	printf("10"),n--,m--;
		else if(m-1 >= 0) printf("1"),m--;
		else if(n-1 >= 0) printf("0"),n--;
	}
	return 0;
}
```

### 最后，如果您在阅读过程中有什么不理解的地方或者发现本蒟蒻的思路有误，可以直接私信或评论告诉我



---

## 作者：FutaRimeWoawaSete (赞：0)

此题首先判断是否输出 $-1$ ，我们分别看 $0$ 是否可以隔开所有的 $1$ 以及$1$是否可以隔开所有的 $0$ 。  
在最优的情况下我们的 $0$ 可以隔开 $2$个$1$，相当于就是 $110110110...$ 这样隔，  
$(n + 1) * 2 < m$ 话就肯定隔不开。  
同理可以推出用 $1$ 去隔 $0$ 的情况，即 $010101...$ 这样隔，  
倘若 $(m + 1) < n$ 的话也肯定隔不开。  
判断完了$-1$ 我们就可以去想如何正确并且不难写的构造这个 $01$ 串，  
我们发现此时 $n <= m + 1$ ，如果我们能保证 $m >= n$ 的话这道题貌似就有点好想了，所以直接特判掉 $n == m + 1$ 的情况。  
```cpp
if(n > m) 
{
	for(int i = 1 ; i <= n + m ; i ++)
	{
		if(i % 2 == 1) printf("0");
		else printf("1");
	}
}
```
然后我们就直接以 $110$ 的方式构造到 $m == n$ 的情况后在以 $10$ 的方式去构造，这样这道题就做完了。  
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int Len = 1e6 + 5;
int n,m,a[Len];
int main()
{
	scanf("%d %d",&n,&m);
	if((n + 1) * 2 < m) printf("-1");
	else if((m + 1) < n) printf("-1");
	else
	{
		if(n > m) 
		{
			for(int i = 1 ; i <= n + m ; i ++)
			{
				if(i % 2 == 1) printf("0");
				else printf("1");
			}
		}
		else
		{
			while(n > 0 || m > 0)
			{
				if(n == 0)
				{
					while(m > 0) 
					{
						printf("1");
						m --;
					}
					break;
				}
				else if(m > n) 
				{
					printf("110");
					m -= 2 , n --;
				}
				else 
				{
					printf("10");
					m -- , n --;
				}
			}
		}
	}
	return 0;
}
```

---

## 作者：莫得感情 (赞：0)

貌似就是一道模拟题，但是要注意**输出的优先顺序**

------------
构造一个 01 序列，包含 n 个 0，m 个 1 要求不存在连续 2 个 0，或 3 个 1 1 <= n; m<=1000000

根据样例我们发现:1和0的分布规律是，能单独放一个1或0就单独放

因此，我们先假设1，0单个交叉分布，当1不足时无解，再把多出来的1按照从前往后逐个添加。

当然，如果连两个1放置满的情况下都还有剩余，则此时无解

简单易懂的几个判断就可以了，下面就是代码


~~~
#include<bits/stdc++.h>
using namespace std;
int n,m;
int main(){
    scanf("%d%d",&n,&m);
    if(n>m+1||m>n*2+2){ //判断无解情况，即1不足或1过量
        printf("-1");
        return 0;
    }
    if(n==m+1){
        for(int i=1;i<=m;i++)
            printf("01");   //特判
        printf("0");
    }
    else{
        int more=m-n-1;   //more是指多出来的个数
        for(int i=1;i<=n;i++){
            if(more>0){
                printf("1");
                more--;
            }
            printf("10");
        }
        if(more!=-1) printf("1");
        while(more>0){
            printf("1");
            more--;
        }
    }
    return 0;
}
~~~


------------
~~华丽结束~~

---

## 作者：Histone (赞：0)

哇，题解区的构造方法都那么复杂的嘛？？

献上我的代码~

这里设 $n$ 为 $0$ 的剩余量，$m$ 为 $1$ 的剩余量

- 如果$n=m+1$，输出一个前导 `0`

- 如果$n<m$，输出 `110`

- 如果$n=m$，输出 `10`

- 检查是否输出完毕，否则末尾补 `1`

上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(v0id){
	int n,m;
	scanf("%d%d",&n,&m);
	if(n*2+2<m||n>m+1)printf("-1");
	else{
		if(n>m){
			printf("0");n--;
		}
		while(n<m&&n&&m){
			printf("110");n--;m-=2;
		}
		while(n&&m){
			printf("10");n--;m--;
		}
		while(m--)printf("1");
	}
	return 0;
}
```


---

## 作者：叶枫 (赞：0)

### 思路
- 题目要求：00和111不能出现

那么只有01和011这两种情况，开头可以是1或11，末尾可以是0

如果$0$的个数 $-$ 末尾$1$个$>1$的个数 

或 $0$的个数$\ast 2<1$的个数 $-$ 开头$2$个 则情况为$-1$

处理开头时$1$或$11$或末尾为$0$的特殊情况，再处理中间的就简单多了。
### $Code$

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define maxn 100010
#define inf 2147483647
#define mod 998244353
#define eps 1e-8
inline int read(){
    int x=0,f=1; char ch=getchar();
    while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch)) {x=x*10+ch-48;ch=getchar();}
    return x*f;
}
int main(){
	int n=read(),m=read();
	if(m>n*2+2||n-1>m) return puts("-1"),0;
	int flag=0;
	if(m-2*n==1) printf("1"),m--;
	else if(m-2*n==2) printf("11"),m-=2;
	else if(n-1==m) flag=1,n--;
	while(n!=m){
		printf("011");
		n--; m-=2;
	}
	for(int i=0;i<n;i++) printf("01");
	if(flag) printf("0");
    return 0;
}
```
~~谢谢观看~~

---

