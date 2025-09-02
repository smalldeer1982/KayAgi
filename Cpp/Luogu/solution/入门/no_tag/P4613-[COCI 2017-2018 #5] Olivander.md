# [COCI 2017/2018 #5] Olivander

## 题目描述

哈利·波特在与伏地魔的战斗中损坏了他的魔杖。他决定去奥利凡德的魔杖店买一根新的。在商店的地板上，他看到 N 根魔杖和 N 个魔杖盒。魔杖的长度分别是 $X_1$，$X_2$，...，$X_n$，盒子的尺寸是 $Y_1$，$Y_2$，...，$Y_n$。如果魔杖的长度 X 可以放入尺寸为 Y 的盒子中，则 X ≤ Y。哈利想知道他是否可以将所有的魔杖放入盒子中，使得每个盒子恰好包含一根魔杖。帮助他解决这个难题。

## 说明/提示

在总分数的 60% 的测试用例中，将满足 N ≤ 9。

**第一个测试用例的说明：**

哈利可以将魔杖放入盒子中。例如，他可以将长度为 5 的魔杖放入尺寸为 6 的盒子中，长度为 7 的魔杖放入尺寸为 13 的盒子中，长度为 9 的魔杖放入尺寸为 10 的盒子中。

**第二个测试用例的说明：**

哈利不能将魔杖放入盒子中，因为尺寸为 2 的盒子无法容纳任何魔杖。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
3
7 9 5
6 13 10```

### 输出

```
DA```

## 样例 #2

### 输入

```
4
5 3 3 5
10 2 10 10```

### 输出

```
NE```

## 样例 #3

### 输入

```
4
5 2 3 2
3 8 3 3```

### 输出

```
DA```

# 题解

## 作者：Tarsal (赞：22)

我又双叒叕被包菜辣！

[P4613 [COCI2017-2018#5] Olivander](https://www.luogu.org/problem/P4613)

首先，不知道为什么这题无法提交翻译；

所以，我先放个翻译：

```
哈利波特在与伏地魔的战斗中损坏了他的魔杖。他决定在奥利凡德的魔杖店买一根新的
魔杖。在商店的地板上，他看到了n根魔杖和n个魔杖盒。魔杖的长度分别是，x1，x2，
…，xn，盒子的尺寸是y1，y2，….y.如果x≤y，可以将x长度的魔杖放在y尺寸的盒子中。
哈利想知道他是否能把所有的魔杖都放在盒子里，这样每个盒子里只有一根魔杖。
帮助他解决这个难题。如果可以放入即输出“DA”，否则输出“NE”；
```

我先讲一下这道题的正解，先把魔杖的长度和盒子的长度按从大到小排序，然后依次对比每个魔杖的长度和盒子的长度，如果Rep(1, n)中存在x[i] > y[i]那么就无法成功装入。先上代码，讲解在后面（~~如果只是为了抄代码的就不用往后翻了~~：

```
#include<bits/stdc++.h>
using namespace std;

#define maxn 110//数据很小，空间很大，你想开多大就多大（划掉 
int n, x[maxn], y[maxn];//x[i]和y[i]都如题，分别是魔杖的长度和盒子的长度 

bool cmp(int a, int b)//排序用的cmp，从大到小。 
{
	return a > b;
}

int main()
{
	scanf("%d", &n);//个数 
	for(int i = 1; i <= n; ++ i)
		scanf("%d", &x[i]);//魔杖的长度 
	for(int i = 1; i <= n; ++ i)
		scanf("%d", &y[i]);//盒子的长度 
	sort(x + 1, x + n + 1, cmp);//从大到小排序，其实也可以从小到大，在后面逆序一下就行了，只有保证有序即可 
	sort(y + 1, y + n + 1, cmp);//同上 
	for(int i = 1; i <= n; ++ i)
		if(y[i] < x[i])//存在魔杖的长度比盒子的长度要大 
		{
			printf("NE");//输出 
			return 0;
		}
	printf("DA");//输出 
	return 0;
}
```


然后，开始分析这道题（~~好水~~：

我们试想一下，如果存在x[k]比y[k]要大，那么我没会发生什么？

设k前面有只有一个数

x[] : 10 8

y[] : 11 7

很明显在k这一组，y[k]不可能装下x[k]，

又因为我们已经排好序了，所以在y[k]后面的一点不可能比y[k]大。

那么只可能是y[k]，比如说y[m],前面的来装x[k]，如果前面的来装x[k]了；

那么y[m]怎么办？x[k]肯定装不了，继续往前？那第一个怎么办？

所以，证毕。

PS：~~请看懂再抄~~

---

## 作者：原株龙葵 (赞：6)

# P4613
------------
这道题是个**普及-**，作为一个只敢做**入门**难度的蒟蒻。

做出来这道题我很高兴。

但是凭良心讲，这道题确实只是一个**入门**难度

因为，贪心法+排序就可以求解

所以，作为一个**哈利波特**迷在这里做一下科普吧，

欧利万德是哈利波特世界中的魔杖商店店主。很多强大的魔杖（包括伏地魔，哈利波特）的魔杖，都是他卖的（他不卖魔杖，不就没那么多事了吗emmmm...）。

好了下面放代码
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int n;
int wand[100],boxs[100];
int main(){
	cin>>n;
	for(int i=0;i<n;i++) cin>>wand[i];
	for(int i=0;i<n;i++) cin>>boxs[i];
    
	sort(wand,wand+n,greater<int>());
	sort(boxs,boxs+n,greater<int>());
    
	for(int i=0;i<n;i++){
		if(boxs[i]<wand[i]){
			cout<<"NE"<<endl;
			return 0;
		}
	}
    
	cout<<"DA"<<endl;
	return 0;
}
```

---

## 作者：Ares゜ (赞：3)

#### 先贴一段翻译上来(机器人翻译可能有点水，勿喷)
```
哈利波特在与伏地魔的战斗中损坏了他的魔杖。他决定在奥利凡德的魔杖店买一根新的
魔杖。在商店的地板上，他看到了n根魔杖和n个魔杖盒。魔杖的长度分别是，X1，X2，
……Xn，盒子的尺寸是Y1，Y2……Yn.如果X≤Y，可以将长度为X的魔杖放在尺寸为Y的盒子中。
哈利想知道他是否能把所有的魔杖都放在盒子里，这样每个盒子里只有一根魔杖。
帮助他解决这个难题。如果可以放入即输出“DA”，否则输出“NE”；
```
作为一个忠实的哈利波特迷，我一看到这个题就想，哇，哈利波特啊!他的魔杖断了?冬青木，凤凰尾羽?是不是在戈徳里克山谷那里呢?
### 大家好像都是sort排得序，本蒟蒻表示Orz，还是手打排序吧
## 进入正题，上代码
```
#include<iostream> //标准输入输出头
using namespace std;
int a[101],b[101];//开数组
int main()
{
    int n,c,d;
    cin>>n;//输入数量
    for(int i=1;i<=n;i++)
    cin>>a[i];//输入魔杖
    for(int i=1;i<=n;i++)
    cin>>b[i];//输入盒子
    for(int i=1;i<=n;i++){//一一列举,魔杖排序
    for(int k=i;k>=1;k--){//往回找有没有小的
    if(a[k]<a[i])
    {
    	c=a[k];
    	a[k]=a[i];
    	a[i]=c;//换位置
    }
    }
    }
     for(int i=1;i<=n;i++){//列举
    for(int k=i;k<=n;k++){//往后找有没有更大的
    if(a[k]>a[i])
    {
    	d=a[k];
    	a[k]=a[i];
    	a[i]=d;//换位置
    }
    }
     }
    for(int i=1;i<=n;i++){//把盒子排序
    for(int k=i;k>=1;k--){
    if(b[k]<b[i])
    {
    	c=b[k];
    	b[k]=b[i];
    	b[i]=c;//同上
    }
    }
    }
     for(int i=1;i<=n;i++){
    for(int k=i;k<=n;k++){
    if(b[k]>b[i])
    {
    	d=b[k];
    	b[k]=b[i];
    	b[i]=d;
    }
    }
     }
    
   for(int i=1;i<=n;i++)
    if(a[i]>b[i])//判断能否放下
    {
    	cout<<"NE";//输出
    	return 0;
    	}	
    	cout<<"DA";//输出
    	return 0;
}
```
可能有些复杂，但新手易懂。如果是会sort的大佬也可以把中间的换位置改成sort
### 本蒟蒻的第六篇题解，如有不足之处请大佬指正


---

## 作者：_•́へ•́╬_ (赞：3)

### 话不多说，直接$\color{chocolate}\text{模拟+排序+贪心}$
### 贪心思路：短棍子放在短盒子里面！
```cpp
#include<bits/stdc++.h>//懒人专用头文件
using namespace std;
inline int read()//快读
{
	register int x=0;register char c=getchar();for(;c<'0'||c>'9';c=getchar());
	for(;c>='0'&&c<='9';x=(x<<3)+(x<<1)+(c^48),c=getchar());return x;
}
int n,a[100],b[100];bool ok=1;
main()
{
	n=read();for(register int i=0;i<n;++i)a[i]=read();for(register int i=0;i<n;++i)b[i]=read();//输入
	sort(a,a+n);sort(b,b+n);//排序
	for(register int i=0;i<n&&ok;++i)if(a[i]>b[i])ok=0;//判断
	puts(ok?"DA":"NE");//输出
}/**/
```

---

## 作者：逆战争锋 (赞：2)

这道题的题意为：

哈利·波特在与伏地魔的战斗中损坏了他的魔杖。
他决定在奥利凡德的魔杖店买一根新魔杖。
在商店的地板上，他看到了N根魔杖和N个魔杖盒。
魔杖的长度分别为，x1,x2…xn，盒子大小为y1, y2…yn。
魔杖可以放在大小大于等于它的盒子里。
哈利想知道他是否能把所有的魔杖都放在盒子里。
## ~~这真是一道水题~~
其实这道题用一个sort就可以了呀！（从小到大排序，再比较）

下面上代码
# 杜绝抄袭

```
#include <bits/stdc++.h>//万能头文件 
using namespace std;

int main()
{
	int n,sum=0,a[1000],b[1000];
	cin>>n;
	for(int i=0;i<n;i++)
		cin>>a[i];
	for(int i=0;i<n;i++)
		cin>>b[i];
	sort(a,a+n);//魔杖长度排序 
	sort(b,b+n);//箱子大小排序 
	for(int i=0;i<n;i++)
	{
		if(a[i]<=b[i])//能装进去 
			sum++;
	}
	if(sum<n)//中途有不符合要求的 
		cout<<"NE";//不可以 
	else
		cout<<"DA";//可以 

	return 0;//完美结束 
}
```


---

## 作者：旅行者一号 (赞：1)

### 看到英文题莫慌！其实是水题！

以下是大概的翻译：

哈利波特在一次和伏地魔的战斗中弄断了魔杖，他准备去买一个新的，他到达商店后，发现有n个盒子和n个魔杖，盒子和魔杖都有自己的尺寸。只有魔杖的尺寸小于等于盒子的尺寸才能放进去。哈里波特想知道能否使所有的魔杖恰好放入盒子，且每个盒子里只有一个魔杖。

如果可以，输出“DA"，如果不行，输出”NE“。

这道题的思路很简单：

### 模拟

### 排序

### 贪心

话不多说，上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
    int n,w[105],b[105];  //w数组代表魔杖（wand）,b数组代表盒子（box）
    cin>>n;
    for(int i=0;i<n;i++) {
        cin>>w[i];
    }
    for(int i=0;i<n;i++) {
        cin>>b[i];
    }
    sort(w,w+n);
    sort(b,b+n);
    for(int i=0;i<n;i++) {
        if(b[i]<w[i]) {
            cout<<"NE"<<endl;
            return 0;
        }
    }
    cout<<"DA"<<endl;
    return 0;
}
```

蒟蒻第一次发题解，请多多指教。

---

## 作者：Happy_Dream (赞：1)

又是COCI的一道水题（orz）

这道题的思路很简单（~~只要英语足够好就行~~）

思路：

1，把数字排一下序

2，一对一对的判断看是否适合

3，只要有不行的就跳出去输出NE

4，输出DA+结束

AC Code：

***
```cpp
#include <iostream>
#include <algorithm>//头文件
using namespace std;//常规
int main()
{
	int a[121],b[121];//定义
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	cin>>a[i];//循环输入魔杖的长度
	for(int i=1;i<=n;i++)
	cin>>b[i];//循环输入盒子的长度
	sort(a+1,a+n+1);
	sort(b+1,b+n+1);//把两个都排好序
	for(int i=n;i>=1;i--)
	{
		if(a[i]<=b[i])//一一判断
		continue;//如果可以就继续
		else//如果不行的话
		{
			cout<<"NE";//就输出NE
			return 0;//直接结束
		}
	}
	cout<<"DA";//输出可以（DA）
	return 0;//结束
}
```
请大家勿抄题解

---

## 作者：zhaowangji (赞：1)

**
思路跟其他题解好像差不多。
想的比较简单，含有贪心（~~投机~~）成分也没有想到一下就过了**


请勿直接抄袭，营造良好氛围
------------


------------

------------
```cpp
#include<iostream>
#include<algorithm>//sort的文件头
using namespace std; 
int n,a[101],b[101];
int t;//判断变量，定义在main之上则默认为0
int main()
{
   cin>>n;
   for(int i=1;i<=n;i++)
   cin>>a[i];//魔杖
   for(int i=1;i<=n;i++)
   cin>>b[i];//箱子
   //基本读入操作
   sort(a+1,a+n+1);
   sort(b+1,b+n+1);
   //给两个数组排序
   for(int i=1;i<=n;i++)
   if(a[i]>b[i])t=1;
   //假设可以，由于两个数组都是递增排序
   //则对应的箱子必定能够放进对应的魔杖
   //只要有任何一个箱子无法放进对应魔杖
   //则假设便不成立
   if(t==1)cout<<"NE";
   else cout<<"DA";
   //t为1则说明有情况不成立
   //t为0则说明所有情况都成立
   return 0;
}

```

---

## 作者：张欣奕 (赞：1)

首先，这道题我不知道为什么没有翻译，所以我自己苦苦看了许久，最后摸索出了
~~我是看题解看的~~
双手奉上翻译

哈利波特在与伏地魔的战斗中损坏了他的魔杖。他决定在奥利凡德的魔杖店买一根新的
魔杖。在商店的地板上，他看到了n根魔杖和n个魔杖盒。魔杖的长度分别是，x1，x2，
…，xn，盒子的尺寸是y1，y2，….y.如果x≤y，可以将x长度的魔杖放在y尺寸的盒子中。
哈利想知道他是否能把所有的魔杖都放在盒子里，这样每个盒子里只有一根魔杖。
帮助他解决这个难题。如果可以放入即输出“DA”，否则输出“NE”；

~~这一道题只需要用快排就行了。我第一次提交太兴奋，没写快排，有52分~~

做后是特别简单的代码

```
#include<bits/stdc++.h>
using namespace std；

int main(){
	int a[105], b[105];
	int n；
	cin>>n；
	for(int i=1; i<=n; i++)	cin>>a[i]；
	for(int i=1; i<=n; i++)	cin>>b[i]；
	sort(a+1, a+1+n)；//快排
	sort(b+1, b+1+n)；
	for(int i=n； i>=1； i--){
		if(a[i]>b[i]){ //只要有一个大了就不行
			cout<<"NE"；
			return 0；
		}
	}
	cout<<"DA"； //不然就行
	return 0；
}
```
~~很贴心地把分号换成中文~~

---

## 作者：yu__xuan (赞：1)

闲来无聊刷红题。~~即然是一道红题应该都是我这样的蒟蒻在做吧题解就写得详细一点吧！~~

看到这种题目当然是直接丢给谷歌翻译喽~

题目大意：有n个物体和n个盒子给你每个物体的长度和每个盒子的长度判断能否将物体都装在盒子中（每个盒子只能装一个物体）。

思路：将物体和盒子的最大长度最小长度都记录下来。如果物体的最小长度大于盒子的最小长度则最小的盒子什么都放不进去输出NE，如果物体的最大长度大于盒子的最大长度则最大的物体放不进去输出NE。

代码如下：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<cstdlib>
#include<algorithm>
using namespace std;
int n;
int g[1001],he[1001];
bool pd[10001];
int maxx1,minn1=0x7fffffff,maxx2,minn2=0x7fffffff;
int main()
{
	cin>>n;
	for(int i=1;i<=n;++i)
	{
		cin>>g[i];
		maxx1=max(maxx1,g[i]);
		minn1=min(minn1,g[i]);
	}
	for(int i=1;i<=n;++i)
	{
		cin>>he[i];
		maxx2=max(maxx2,he[i]);
		minn2=min(minn2,he[i]);
	}
	if(maxx2<maxx1||minn2<minn1)
	{
		cout<<"NE";
		return 0;
	}
	cout<<"DA";
	return 0;
}
```
光进行这两种判断就可以的80分哦！
正解思路：物体当然要放到比他大的最少的盒子里，这样大盒子才可以用来放大物体！
AC代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<cstdlib>
#include<algorithm>
using namespace std;
int n;
int g[1001],he[1001];
bool pd[10001];
int maxx1,minn1=0x7fffffff,maxx2,minn2=0x7fffffff;
int main()
{
	cin>>n;
	for(int i=1;i<=n;++i)
	{
		cin>>g[i];
		maxx1=max(maxx1,g[i]);
		minn1=min(minn1,g[i]);
	}
	for(int i=1;i<=n;++i)
	{
		cin>>he[i];
		maxx2=max(maxx2,he[i]);
		minn2=min(minn2,he[i]);
	}
	if(maxx2<maxx1||minn2<minn1)
	{
		cout<<"NE";
		return 0;
	}//以上为输入和两种判断。
	sort(g+1,g+1+n);
	sort(he+1,he+1+n);//sort是一个排序函数。
	int sum=0;//计数器。
	for(int i=1;i<=n;++i)//for物体长度。
	{
		for(int j=1;j<=n;++j)//因为排过序所以这样是盒子长度从小到大。
		{
			if(pd[j]==0&&he[j]>=g[i])//这个盒子没放过东西并且要大于等于物体长度。
			{
				sum++;//计数器加一。
				pd[j]=1;//这个盒子放过东西。
				break;
			}
		}
	}
	if(sum==n) cout<<"DA";//如果都放进去了输出DA否则输出NE
	else cout<<"NE";
	return 0;
}
```

---

## 作者：TAFE_ZZR (赞：0)

## 英文题不好读懂，其实意思是这样的：
哈利·波特在与伏地魔的战斗中损坏了他的魔杖。他决定在奥利凡德的魔杖店买一根新魔杖。在商店的地板上，他看到了N根魔杖和N个魔杖盒。棒的长度分别为，X1X_1X1,X2X_2X2…XnX_nXn，盒子大小为Y1Y_1Y1, Y2Y_2Y2…YnY_nYn。如果X≤Y，可以将长度为X的棒放入大小为Y的盒子中。哈利想知道他是否能把所有的魔杖都放在盒子里，这样每个盒子里就只有一根魔杖。帮助他解决这个难题。

输入格式

第一行输入的是正整数N(1≤N≤100)，即来自任务的数字。第二行包含N个正整数XiX_iXi(1≤XiX_iXi≤10910^9109)，这些数字来自任务。第三行包含N个正整数XiX_iXi(1≤XiX_iXi≤10910^9109)，这些数字来自任务。

输出格式

如果哈利能把所有的魔杖都放在盒子里，那么输出“DA”(克罗地亚语为“是”)，否则输出“NE”(克罗地亚语为“否”)。
## 那么就很简单了，输入+排序+判断+输出即可！

	#include <bits/stdc++.h>//万能头文件 
	using namespace std;
    int n,s,a[105],b[105];
	int main() {
    	cin>>n;//输入
    	for(int i=0;i<n;i++) cin>>a[i];//输入
    	for(int i=0;i<n;i++) cin>>b[i];
    	sort(a,a+n);sort(b,b+n);//STL快速排序
    	for(int i=0;i<n;i++)
        	if(a[i]<=b[i]) s++;//如果能装进去，就累加
    	if(s<n) cout<<"NE"; //若不符，就不可以 
    	else cout<<"DA"; //否则可以
    	return 0;
	}

---

## 作者：sjl40 (赞：0)

我们很容易看出这就是排序+贪心。 贪心就是大盒子配大棍子。排序就是让大盒子和大棍子进行配对。

操作：

First，棍子和盒子都进行排序。

Finally，直接配对，有一个配不上输出'NE'。全部配上输出'DA'。



------------

```cpp
#include<iostream>

#include<algorithm>

using namespace std;

int n;

int a[100+10],b[100+10];

bool cmp(int a,int b)
  
{
 
  return a>b;

}//为从大到小排序做的准备函数。

int main()
{
  
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) cin>>b[i];
    sort(a+1,a+1+n,cmp);//棍子排序
    sort(b+1,b+1+n,cmp);//盒子排序

    for(int i=1;i<=n;i++)
	{
        if(b[i]<a[i])//配不上输出‘NE’
		{
            cout<<"NE";
            return 0;
        }
    }

    cout<<"DA";//全部配对成功输出‘DA’
    return 0;
}
```


---

## 作者：liyifan24 (赞：0)

正如大佬索说，此题较水

思路：**贪心法**：排序+记录+**筛选**+判断

【有能力的,链接发一个:https://www.luogu.org/blog/83547/tan-xin-jiang-xie 】

记录+筛选+判断

代码如下
```cpp
#include<bits/stdc++.h>
using namespace std;
int c[1000];
int main()
{
	int n,a[1000],b[1000];
	bool flag;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)cin>>b[i];
	sort(a+1,a+n+1);
	sort(b+1,b+n+1);//排序
	for(int i=1;i<=n;i++)
	{flag=false;//计录是否符合
		for(int j=i;j<=n;j++)
		{
			if(b[i]>=a[j]&&c[j]!=1)
			{
			  	c[j]=1;//计录，可以增加效率
			  	break;
			}
			else {
				flag=true;//判断
			}
		}
		if(flag){
			cout<<"NE";//否定
			return 0;
		}
	}
	cout<<"DA";
}
```


---

## 作者：dinghongyu (赞：0)

### 此题极水，思路：排序 + 比较   
代码☟：   
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a[101],b[101];
int main()
{
	cin >> n;
	for (int i = 1;i <= n;i++)
	    cin >> a[i];
	for (int i = 1;i <= n;i++)
	    cin >> b[i];
	sort(a + 1,a + n + 1);       //  排序
	sort(b + 1,b + n + 1);       //  排序
	for (int i = 1;i <= n;i++)
	    if (a[i] > b[i])
	    {
	    	cout << "NE";
	    	return 0;
		}                        //  比较 + 输出
	cout << "DA";
	return 0;
}
```

---

