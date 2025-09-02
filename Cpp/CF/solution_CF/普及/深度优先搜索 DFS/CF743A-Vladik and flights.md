# Vladik and flights

## 题目描述

Vladik is a competitive programmer. This year he is going to win the International Olympiad in Informatics. But it is not as easy as it sounds: the question Vladik face now is to find the cheapest way to get to the olympiad.

Vladik knows $ n $ airports. All the airports are located on a straight line. Each airport has unique id from $ 1 $ to $ n $ , Vladik's house is situated next to the airport with id $ a $ , and the place of the olympiad is situated next to the airport with id $ b $ . It is possible that Vladik's house and the place of the olympiad are located near the same airport.

To get to the olympiad, Vladik can fly between any pair of airports any number of times, but he has to start his route at the airport $ a $ and finish it at the airport $ b $ .

Each airport belongs to one of two companies. The cost of flight from the airport $ i $ to the airport $ j $ is zero if both airports belong to the same company, and $ |i-j| $ if they belong to different companies.

Print the minimum cost Vladik has to pay to get to the olympiad.

## 说明/提示

In the first example Vladik can fly to the airport $ 2 $ at first and pay $ |1-2|=1 $ (because the airports belong to different companies), and then fly from the airport $ 2 $ to the airport $ 4 $ for free (because the airports belong to the same company). So the cost of the whole flight is equal to $ 1 $ . It's impossible to get to the olympiad for free, so the answer is equal to $ 1 $ .

In the second example Vladik can fly directly from the airport $ 5 $ to the airport $ 2 $ , because they belong to the same company.

## 样例 #1

### 输入

```
4 1 4
1010
```

### 输出

```
1```

## 样例 #2

### 输入

```
5 5 2
10110
```

### 输出

```
0```

# 题解

## 作者：piggymichael (赞：5)

各位大佬把思路讲得已经很清楚了。这道题思维难度比较高，但没啥代码难度。我对这种神奇的题目背景感到很惊奇。

给一串由0和1组成的数和两个整数a,b。

判断这串数上的第a个和第b个是否相等。

如果相等，输出0；

如果不相等，输出1。

仔细想想，想通了就这么简单。~~主要是你不看题解能不能想到！~~

上代码：
```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
int x,y,z;
string a;
int main()
{
	cin>>x>>y>>z;//输入
	cin>>a;//输入
	if(a[y-1]==a[z-1])//判断
		cout<<0<<endl;//一样就输出0
	else
		cout<<1<<endl;//不一样就输出1
	return 0;//就这样简单地结束了。
}
```

[](https://www.luogu.org/record/24558705)

事实证明数据有点水，string可以过。x好像没啥用。

我只是大胆地尝试string，惊奇地发现竟然AC了！

---

## 作者：wxwoo (赞：5)

[$$\color{#0e90d2}\huge{\texttt{my blog}}$$](https://wxwoo.github.io/2019/03/13/solution-cf743a/)

******

[原题目链接](https://www.luogu.org/problemnew/show/CF743A)

写这题翻译的时候，突然就有了思路

实际上这题重在思考

若$a$机场和$b$机场是同一家公司，输出0，这个很容易想到

若$a$机场和$b$机场不是同一家公司，输出1，这是为什么呢？

首先，一定有两个不同公司的机场相邻

我们设这两个机场为$i$和$j$，且$i$与$a$同公司，$j$与$b$同公司

那么就有如下航线：

$$a\to i\to j\to b$$

由于$i$与$j$相邻且不为同一家公司，所以总费用为1

代码如下
```cpp
#include<cstdio>
#include<algorithm>
#include<iostream>
using namespace std;

template<typename T> inline void read(T &x)//快读
{
    char ch;
    T f=1;
    x=0;
    do
    {
        if(ch=='-')
            f=-1;
        ch=getchar();
    }while(!('0'<=ch&&ch<='9'));
    do
    {
        x=(x<<3)+(x<<1)+ch-48;
        ch=getchar();
    }while('0'<=ch&&ch<='9');
    x*=f;
}
int n,a,b;
int f[100010];
int main()
{
    read(n);
    read(a);
    read(b);//输入n,a,b
    for(int i=1;i<=n;i++)
    {
        char c=getchar();
        f[i]=c-48;//输入公司
    }
    if(f[a]==f[b])//如果公司相同
        putchar('0');//输出0
    else//如果公司不同
        putchar('1');//输出1
    return 0;
}

```

---

## 作者：dingcx (赞：4)

~~本题无疑是一道水题~~

## 我是仗着没用数组才来的

(如果没有给n的范围，开数组可能就爆了)

思路：其实第二行有用的只有两个字符，其余的直接冲掉都没问题。

注意：如果a=b答案一定是0，要特判。

上代码——
```cpp
#include<cstdio>
using namespace std;
int main(){
	int n,a,b,t;//一波定义
	char c1,c2;
	scanf("%d%d%d\n",&n,&a,&b);//读入。写\n是为了不让读字符时多读一个换行(cin没有这个问题)
	if(a==b){//特判
		printf("0");//不用钱
		return 0;//直接return
	}
	if(a>b) t=a,a=b,b=t;//保证a<b
	for(int i=1;i<=a;i++) scanf("%c",&c1);//从1读到a，前面的都没用
	for(int i=a+1;i<=b;i++) scanf("%c",&c2);//从a+1读到b，其它的都没用
	printf("%d",!(c1==c2));//相等输出0，不相等输出1。强调一下'!'的优先级高，所以要打括号
	return 0;//华丽结束
}
```

---

## 作者：wpy233 (赞：4)

这个题是恶评么。。。。。。。

本萌新乍看题目这么长。。。感到一阵阵恐慌。。。

但在仔（kan）细（guo）阅（ti）读（jie）后，发现这题一点都不难。。。

其实这个题完全可以转化为一道红题：
```
给定一个长度为n的字符串和两个整数a,b
求字符串上的第a个字符和第b个字符是否相等。
如果相等，输出0；
如果不相等，输出1.
```
emmm、、、这就结束了。。。

不过听说这题唯一的亮点是要用到快读？

https://www.luogu.org/recordnew/show/20092080

。。。。。。。。。。

#事实证明不会超时哈#
```
#include <bits/stdc++.h>//万能头文件
using namespace std;
int n,o,p;
char a[100005];//注意这里不能用字符串，因为最大有十万
int main()
{
	cin>>n>>o>>p;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	if(a[o]==a[p])//判断
		cout<<0<<endl;
	else
		cout<<1<<endl;//输出
	return 0;
} 
```
emmm所以这是一道红题？

---

## 作者：JS_TZ_ZHR (赞：2)

~~本题的背景是真的强~~

教你们一种优化空间的方法。

由于本题的输出(到达机场的费用)只与a[m]与a[k]有关系，所以只要用last和a两个变量存储，所以根本没必要开一个数组
```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
int n,m,k,m1,k1;
char a,last;//定义变量
int main() {
	cin>>n>>m>>k;
	m1=min(m,k);
	k1=max(m,k);//保证k1>=m1
	for(int i=1; i<=n; i++) {
		cin>>a;
		if(i==m1)last=a;//判断
		if(i==k1){
			cout<<1-(last==a)<<endl;//输出
			return 0;//结束
		}
	}
}
```


---

## 作者：铃宕 (赞：2)

#### 分类讨论：

**1.** $a$ ,$b$ 属于同一家公司，则费用为 $0$

**2.** $a$ , $b$ 属于不同公司：
  
> **因为** 只有两家公司

> **所以** 必有两个不同公司的机场相邻（互相到达费用为 $1$ ） , 而 $a$ , $b$ 到其中之一的费用为 $0$ ,最小费用就为 $1$

#### 注意！

请使用快读，不然会超时（无负数，**int** 即可）

输入公司用 **getchar** ，两个数据之间无空格

#### code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,b,f[100020];
inline int read(){//快读
    int ans=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){ans=ans*10+ch-'0';ch=getchar();}
    return ans;
}
int main(){
    n=read();a=read();b=read();
    for(int i=1;i<=n;i++){//输入
        char ch=getchar();
        f[i]=ch;
    }
    if(f[a]==f[b]) putchar('0');//判断
    else putchar('1');
}
```


---

## 作者：幻之陨梦 (赞：2)

**解题思路：输入完之后直接判断第i位和第j位相不相等就行了。如果相等就输出0，不相等就输出1。**

[$\color{blue}\text{AC证据}$](https://www.luogu.org/recordnew/show/20663727)

AC Code：
```cpp
#include<bits/stdc++.h>//万能头
using namespace std;//标准库
int n,x,y;//定义
char a[100001];
//注意：这里必须用 char类型数组，要不然会溢出(本人亲测)
int main(void)//我就喜欢用void
{
	scanf("%d%d%d",&n,&x,&y);//输入
	for(int i=1;i<=n;i++) cin>>a[i];
	//循环读入char类型的a数组
	if(a[x]==a[y]) puts("0");
	//判断如果这两处相等，就输出0
	else puts("1");//否则输出1
	//PS：puts大法好
}
```

---

## 作者：_Camille_ (赞：0)

~~所以说这又是一道水题qwq~~

题意是给一n个由0和1组成的数和两个整数a，b，判断这n个数的第a个和第b个是否相等。相等输出0，不相等输出1。

具体细节看代码。

代码呀：
```cpp
#include<bits/stdc++.h>//养成好习惯，用万能头（逃
using namespace std;
char s[100001];//定义字符串数组，有点怕爆
int main(){
    int n,a,b;
    cin>>n>>a>>b;
    for(int i=1;i<=n;i++) cin>>s[i];
    if(s[a]==s[b]) cout<<"0";//判断相等的时候
    else cout<<"1";判断不等的时候
    return 0;
}
```
~~结束了？好吧，管理员大大求过啊qwq~~

---

## 作者：仰望半月的夜 (赞：0)

# 这篇给出最短代码

#### 作为一篇题解，先介绍一下思路
**原题：[$\text{CF743A Vladik and flights}$](https://www.luogu.org/problem/CF743A)**

航空公司只有两家，所以我们可以发现，与每一个机场相邻的，要么就是同事，要么就是~~异端~~竞争对手。

于是会有两种情况出现：
>1、若起点及终点机场都属于同一航司，只坐一次飞机，即选择直航航线，费用为0；

>2、若起点与终点机场属于不同航司，最多坐三次飞机。先从起点（记为航司A）到离终点最近的属于航司A的机场，此时因为这个机场已经是离终点最近的属于航司A的机场了，所以离终点更近的机场（也有可能是终点的机场）都是属于航司B的了，于是显然，此机场有一个相邻的机场必然是属于航司B的，然后我们就再坐一次飞机到相邻机场，此时费用为1；如果你还是没有到终点的话，就再坐一次飞机，直航到终点机场。总费用为1。

~~话说$\text{Vladik}$老是中转真不好，这样容易浪费时间在候机上，要是迟到那$\text{IOI}$赛场上就少了一个$\text{AK}$的人了呢。~~

$\color{skyblue}\text{Code：}$
```cpp
#include<cstdio>
int n,a,b;char s[100002];
int main(){
	scanf("%d%d%d",&n,&a,&b);
	scanf("%s",s+1);//s+1代表从s[1]开始读字符
	return s[b]==s[a]?puts("0"):puts("1");//不换行就去见祖宗QwQ
}
```
~~当然你要减掉几个换行再压一压也可以更短~~

---

