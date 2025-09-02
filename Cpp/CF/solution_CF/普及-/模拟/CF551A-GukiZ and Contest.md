# GukiZ and Contest

## 题目描述

GukiZ 喜欢 OI，也喜欢出毒瘤题。他喜欢根据比赛的成绩为选手计算 rating。他现在正在准备一套新的毒瘤题。

一共有 $n$ 名选手被骗来做他的毒瘤题，每一位选手有一个正的 rating。选手们的编号为 $1$ 到 $n$。第 $i$ 名选手的 rating 是 $a_{i}$。比赛还没有开始，GukiZ 开始预测比赛结果。

GukiZ 认为，每名选手的排名应该是 $1 + G$，其中 $G$ 表示 rating 严格比这名选手大的选手数量。也就是说，如果选手 A 的 rating 严格比选手 B 高，他的排名就一定在 B 之上；如果两名选手 rating 相同，那么他们就一定会并列。

然而这件事情几乎不可能发生，但 GukiZ 依然想知道根据他的想法，每名选手的排名。

## 样例 #1

### 输入

```
3
1 3 3
```

### 输出

```
3 1 1
```

## 样例 #2

### 输入

```
1
1
```

### 输出

```
1
```

## 样例 #3

### 输入

```
5
3 5 3 4 5
```

### 输出

```
4 1 4 3 1
```

# 题解

## 作者：智子·起源 (赞：8)

#### 红蝶小姐又来了！！~~（真扫兴）~~

这篇题解主要是给刚刚接触c++的朋友们写的。如果你知道c++是什么东西，那你就能看懂。
##### ~~（美智子小姐是照顾新手的^_^）~~

下面，我来结合程序讲讲模拟的过程：
代码献上：
```cpp
#include<iostream>
#include<cstdio>//两句以include开头的，是文件头。用途是把其他的程序段连接到这个程序，从而得到更多函数的运用。
using namespace std;//打了这段话时，大家就可以创建函数了（当然我没用函数）
int n,a[2000],t;//这是全局变量。定义的有：选手的数量、每名选手的rating（用一个数组存起来）、临时变量。
int main()//定义主函数。（main不要打错^_^）
{
  scanf("%d",&n);//scanf是一个可以用比较快的速度读入数据的函数。读入n。（需要打文件#include<cstdio>）
  for(int i=0;i<n;i++)scanf("%d",&a[i]);//把n个选手的分数读入到一个从0~n-1的数组里。
  for(int i=0;i<n;i++)//这里开始模拟每个选手的名次
  {
    t=1;//由于题目说"每名选手的排名应该是 1+G，其中 G 表示 rating 严格比这名选手大的选手数量。"所以给变量赋值时，赋1代表加上他本身的名次。
    for(int j=0;j<n;j++)if(a[j]>a[i])t++;//再次从0~n-1模拟。如果有比正在模拟选手分数大的选手，那名次变量t就加1（即t++）。
    printf("%d ",t);//输出t和空格（printf和scanf通常配套使用）。
  }
  return 0;
}
```

最后，再献上纯代码（无注解）：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int n,a[2000],t;
int main()
{
  scanf("%d",&n);
  for(int i=0;i<n;i++)scanf("%d",&a[i]);
  for(int i=0;i<n;i++)
  {
    t=1;
    for(int j=0;j<n;j++)if(a[j]>a[i])t++;
    printf("%d ",t);
  }
  return 0;
}
```
#### 最后，祝各位新手的c++旅程中快乐成长！
#### 如果这篇题解帮助了你，妾身想让你帮忙点个赞，谢谢！

---

## 作者：Ryan_Yu (赞：4)

题目意思就是给你 $n$ 名同学的成绩，求出他们的名次。

此题有两种思路，我们逐个介绍。

**第一种方法：结构体**

先将每位同学的编号存入 $number_i$ 内，接着排序。

如果相邻两位同学的成绩不同，排名就从当前的下标 $i$ 开始。

如果相同，`sort` 已经将其排好序了，不必操心。

```cpp
#include<bits/stdc++.h>
using namespace std;
struct Node
{
	int number,rating;
} a[2005];
bool cmp(Node a,Node b)
{
	return a.rating>b.rating;
}
int i,n,ans[2005],b=1;
//由于b是排名，最高排名只能是1
int main()
{
	cin>>n;
	for(i=1; i<=n; i++)
		{
			cin>>a[i].rating;
			a[i].number=i;
		}
	sort(a+1,a+1+n,cmp);
	for(i=1; i<=n; i++)
		{
			if(a[i].rating!=a[i-1].rating)
				ans[a[i].number]=b=i;
			else
				ans[a[i].number]=b;
		}
	for(i=1; i<=n; i++)
		cout<<ans[i]<<" ";
	cout<<endl;
	return 0;
}
```
**第二种方法：循环模拟**

把 $ans$ 记为每位选手的排名，利用双重循环判断。

如果目前的选手成绩没有别的选手高，排名就靠后一位。

```cpp
#include<bits/stdc++.h>
using namespace std;
int i,n,j,rating[2005],ans;
int main()
{
	cin>>n;
	for(i=1; i<=n; i++)
		cin>>rating[i];
	for(i=1; i<=n; i++)
	{
		ans=1;
    //每位选手排名统计结束后，排名都从1开始。
		for(j=1; j<=n; j++)
		{
			if(rating[i]<rating[j])
				ans++;
		}
		cout<<ans<<" ";
	}
	cout<<endl;
	return 0;
}
```


---

## 作者：Mikemao666 (赞：0)

题目：[Here](https://www.luogu.com.cn/problem/CF551A)

据题解区各位大佬所言：这是一道贪心。

可是。。。当你看到此题数据是如此之水，你就不会想到---用$sort+cmp$直接排序结构体AC这道题吗？

所以。。。开始我的表演

**code：**
```cpp
#include<bits/stdc++.h>
using namespace std;
struct god {
	int a,b,c;//a代表Rating，b代表输入次序，c代表排名 
} a[2001];
bool cmp1(god e,god v) {//cmp1__把god按Rating大小排序 
	return e.a>v.a;//从大到小 
}
bool cmp2(god e,god v) {//cmp2__把god按输入次序重新排序 
	return e.b<v.b;
}
int n;
int main() {
	cin>>n;
	for(int i=1; i<=n; ++i)
		cin>>a[i].a,a[i].b=i;//输入+标记 
	sort(a+1,a+n+1,cmp1);//cmp1 
	int j=1,a[1].c=1;//初始化为第一名 
	for(int i=1; i<=n; i++) {
		if(a[i].a!=a[i+1].a) {//如果排名改变 
			j=i+1;//j的值替换 
		}
		a[i+1].c=j;//打上排名 
	}
	sort(a+1,a+n+1,cmp2);//cmp2 
	for(int i=1; i<=n; ++i) {
		cout<<a[i].c<<" ";//输出 
	}
	return 0;
}
```
完结撒世纪末彼岸花❀

---

## 作者：打表大蒟蒻 (赞：0)

这道题的题解貌似有点少啊，又是道水题，在这两方面的鼓舞下，蒟蒻我毅然决然地写了一篇题解，望各位多多支持！！！~~不过貌似没有多少人能看到这篇题解~~


------------
接下来进入正题

这道题的翻译说实话真是让人看不懂，~~也许是我语文不好吧~~，但在我~~锲而不舍地~~思索后，总算确定了这道题的解题思路：贪心。

先读入n和一组数据，然后开一个暴力两层循环，第一层从1循环到n，第二层也从1循环到n，看有多少个数比现在处理的数大，大的话就把计数器自增一，每一个数处理后都要把计数器输出，再还原为一，就完美结束了。

话不多说，上代码

code:
```cpp
#include <cstdio>
using namespace std;
int a[10001];  //定义数组
int main ()
{
	int n, sum=1;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);  //读入
		
	for(int i=1;i<=n;i++){  //处理的数
		for(int j=1;j<=n;j++)
			if(a[i]<a[j]) sum++;    //计数器累加
		printf("%d ",sum);  //输出sum,空格不能忘！！！
		sum=1;  //计数器还原为1
	}
	return 0;   //完美结束
}
```

抄袭可耻！！！

---

## 作者：Trimsteanima (赞：0)

纯贪心吧。。。
```cpp
#include <iostream>
using namespace std;
int n, i, j, u, a[2222];
int main() {
	cin >> n;
	for (i = 1; i <= n; i++)
		cin >> a[i];
	for (i = 1; i <= n; i++) {
		u = 1;
		for (j = 1; j <= n; j++)
			if (a[i] < a[j])
				u++;
		cout << u << " ";
	}
	return 0;
}
```

---

## 作者：E1_de5truct0r (赞：0)

这道题题意经过阅读可以简化为：

输入 $n$ 和 $n$ 个数，然后依次输出每个数从大到小排序，并且算上并列后的顺序。

那么我们自然而然的想到结构体排序。用一个 ```id``` 记录输入时的编号，一个 ```x``` 记录数值大小，一个 ```rk``` 记录排名。首先按照 ```x``` 排序，然后把 ```rk``` 记录下来，最后按 ```id``` 排序，再输出 ```rk``` 。

代码就很简单了。

## $\large{Code}$

```cpp
#include <bits/stdc++.h>
using namespace std;
struct Node
{
	int x,id,rk; //结构体
}a[100005];
bool cmp1(const Node &a,const Node &b)
{
	return a.x>b.x;
}
bool cmp2(const Node &a,const Node &b)
{
	return a.id<b.id;
}
int main()
{
	int n; cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i].x;
		a[i].id=i;
	}
	sort(a+1,a+1+n,cmp1); //按 x 排序
	for(int i=1;i<=n;i++)
	{
		while(a[i].x==a[i-1].x && i<=n)
		{
			a[i].rk=a[i-1].rk; //更新排名
			i++;
		}
		a[i].rk=i;
	}
	sort(a+1,a+1+n,cmp2); //按 id 排序
	for(int i=1;i<=n;i++)
		cout<<a[i].rk<<" "; //输出
	return 0;
}
```

$$\texttt{THE END}$$

---

