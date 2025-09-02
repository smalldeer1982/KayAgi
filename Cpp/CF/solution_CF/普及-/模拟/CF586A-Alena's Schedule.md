# Alena's Schedule

## 题目描述

Alena has successfully passed the entrance exams to the university and is now looking forward to start studying.

One two-hour lesson at the Russian university is traditionally called a pair, it lasts for two academic hours (an academic hour is equal to 45 minutes).

The University works in such a way that every day it holds exactly $ n $ lessons. Depending on the schedule of a particular group of students, on a given day, some pairs may actually contain classes, but some may be empty (such pairs are called breaks).

The official website of the university has already published the schedule for tomorrow for Alena's group. Thus, for each of the $ n $ pairs she knows if there will be a class at that time or not.

Alena's House is far from the university, so if there are breaks, she doesn't always go home. Alena has time to go home only if the break consists of at least two free pairs in a row, otherwise she waits for the next pair at the university.

Of course, Alena does not want to be sleepy during pairs, so she will sleep as long as possible, and will only come to the first pair that is presented in her schedule. Similarly, if there are no more pairs, then Alena immediately goes home.

Alena appreciates the time spent at home, so she always goes home when it is possible, and returns to the university only at the beginning of the next pair. Help Alena determine for how many pairs she will stay at the university. Note that during some pairs Alena may be at the university waiting for the upcoming pair.

## 说明/提示

In the first sample Alena stays at the university from the second to the fifth pair, inclusive, during the third pair she will be it the university waiting for the next pair.

In the last sample Alena doesn't have a single pair, so she spends all the time at home.

## 样例 #1

### 输入

```
5
0 1 0 1 1
```

### 输出

```
4
```

## 样例 #2

### 输入

```
7
1 0 1 0 0 1 0
```

### 输出

```
4
```

## 样例 #3

### 输入

```
1
0
```

### 输出

```
0
```

# 题解

## 作者：TLMPEX (赞：2)

思路：在输入的过程中，若是一则总和加一。输入完后用一层for循环从1枚举到n-1了，如果是0且上一个为1且下一个为1了，则总和加一，最后输出总和。

上代码。
```c
#include<bits/stdc++.h>
using namespace std;
int k[101];
int main(){
	int n,i,z=0;
	cin>>n;
	for(i=1;i<=n;i++){
		cin>>k[i];
		if(k[i]==1)z++;//如果是1则总和加一
	}
	for(i=2;i<n;i++)
		if(k[i]==0&&k[i-1]==1&&k[i+1]==1)z++;//如果第i个是0且前后两个都是1则总和加一
	cout<<z;
}
```


---

## 作者：Chtholly_L (赞：1)

#  CF586A 【Alena's Schedule】题解

###### ~~大家好啊，我还是那个奆蒟蒻！（你是蒟蒻还很骄傲吗？）~~

###### 拿到这个题之后，~~哇，又是超长题干，好慌，还是 $English$~~

但是， _普及-_ 又双叒叕让我停下了脚步。

看到翻译后，我都快蒙了，原来这么简单？？？~~连我这个奆蒟蒻都会！感谢大佬翻译~~

#### 话不多说，开始讲解！

题干再翻译成最简单，直观的就是：输入 $n$ ，再输入 $n$ 个数，这 $n$ 个数只有 $0$ 和 $1$ 。统计一下有多少个 $1$ 和 多少个 $1$ $0$ $1$ 。

那么我们先开一个数组，开到下标 $101$ 就可以，题干中有说明。

然后输入 $n$ 。再用两个if来判断是否满足条件。再用一个计数器累加。

上代码

## $AC$ $Code$
```cpp
#include<iostream>
using namespace std;
int a[101];  //定义数组
int main()
{
	int ans=0; //计数器，一定要赋一个初值0，否则会乱码，也可以开成全局变量，自动赋值0.
	int n;  // n如题
	cin>>n;
	for(int i=1;i<=n;i++)
	{
	    cin>>a[i];  //读入，直接输入就行，不用字符串，因为是整型，且输入时中间是有空格的
	}
	for(int i=1;i<=n;i++)
	{
	    if(a[i]==1)ans++;  /判断有多少个1
	    if(a[i-1]==1 and a[i]==0 and a[i+1]==1)ans++;  //判断有多少个两个1加一个0
	}
	cout<<ans;  //输出个数
	return 0;  //结束程序
}
```
[评测记录](https://www.luogu.com.cn/record/46280379)

[博客食用更佳](https://www.luogu.com.cn/blog/maxsuper/)

---

## 作者：zplqwq (赞：1)

# CF586A

啊吧啊吧，据说考前水题解可以增加rp

那我试试喽

## Section 1 题目

题意：

给你一个长度为n的用空格分开的01串，问其中1的个数和被夹在两个1之间的0的个数的总和。

做法：

其实这道题理解题意之后就很简单了，毕竟是CF的A题

按照题目模拟就好。

可以先判断一下这个01串里面有多少个1，然后再判断一下夹在两个1里面的个数就好啦。

坑点

1. 判断夹在两个1里面的0的个数时，循环范围从2到n-1而非1到n

## Section 2 代码

```c++
#include<bits/stdc++.h>//万能头
using namespace std;

int n,m;

const int N=10000010;

int a[N];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)//输入
	{
		cin>>a[i];
	}
	int ans=0;
	for(int i=1;i<=n;i++)//判断1的个数
	{
		if(a[i]==1)
		{
			ans++;
		} 
	} 
	for(int i=2;i<n;i++)//注意循环范围
	{
		if(a[i]==0 and a[i+1]==1 and a[i-1]==1)//如果当前的数为0且它相邻两边的数为1，即夹在两个1中间
		{
			ans++;//ans++
		}
	}
	cout<<ans<<endl;//输出
    return 0;
    
}

```

管理大大求过

---

## 作者：Waaifu_D (赞：1)

~~蒟蒻刚注册好CF账号，于是马上来刷CF水题了！~~

第一眼看到这题的题面和难度，我震惊了，~~（太适合我了）~~，于是3分钟敲完代码，火速AC

代码↓

```cpp
#include<bits/stdc++.h>
using namespace std;
bool k[110];//因为数据只有0和1就用bool（省空间）
int n;
int ans;//统计
int main()
{
	cin>>n;
	for(int i=1; i<=n;i++)
	{
		cin>>k[i];
	}
	for(int i=1; i<=n;i++)
	{
		if(k[i]==1)//不需要解释
		{
			ans++;
		}
		if(k[i-1]==1&&k[i]==0&&k[i+1]==1)//根据题意前为1中间为0后为1的都加到ans里
		{
			ans++;
		}
	}
	cout<<ans;//直接输出
	return 0;//快乐AC
}
```
祝大家CSPrp++！

---

## 作者：asasas (赞：1)

这题翻译已经将题意说的很清楚了，其实就是求1的个数和串101的个数之和。

我们读进来后，将串101的0变为1，最后直接计算1的个数即可。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
bool a[105];//只有0或1，拿bool数组存即可。
int main(){
	int n;
	cin >> n;
	for (register int i=1;i<=n;i++){
		cin >> a[i];
	}
	int ans=0;//最终答案
	for (register int i=1;i<=n-2;i++){
		if (a[i]==1&&a[i+1]==0&&a[i+2]==1) a[i+1]=1;//将两个1中间的0变为1 
	} 
	for (register int i=1;i<=n;i++) ans+=a[i];//计算有多少个1
	cout << ans;//ans为1的个数 
} 
```


---

## 作者：Programmtion (赞：1)

#### ~~这明明是道入门题~~

------------
# 思路：
for循环枚举遇到1则总和加一，遇到0且上一个为1且下一个为1了，则总和加一，最后输出总和。

废话不多说,上代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
	int n,a[101],ans=0;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]==1) ans++;
	}
	for(int i=2;i<n;i++){ //第1个不可能是，最后一个也不可能 
		if(a[i]==0&&a[i-1]==1&&a[i+1]==1)
        ans++;
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：_tommysun_ (赞：1)

真的要感谢这道题的翻译啊。。。这道题的难度其实就全在题面上了，理解了题面这就是道入门题。

~~而翻译直接把精华提取出来了。。。~~

这道题我是分成两个部分完成的：第一个部分扫这个数组中有多少个$1$，第二个部分扫有多少$0$被$1$夹在中间。

## 话不多说，上代码
```
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n;
	cin>>n;
	int a[n+1];
	for(int i=0;i<n;i++){
		cin>>a[i];
	}
	int suma=0; int sumb=0; //suma和sumb分别表示有多少个1，以及被1夹在中间的0的个数。
	for(int i=0;i<n;i++){
		if(a[i]==1) suma++;
	}
    for(int i=0;i<n;i++){
    	if(a[i]==0)
        	if(a[i-1]==1&&a[i+1]==1) sumb++;
    }
	cout<<suma+sumb;
	return 0;
}
```


---

## 作者：DPair (赞：1)

## 【题意】
Alena一天有$n$节课，由于她家离学校很远，她只会在有连续两个以上课间才会回家，而且她一旦可以回家就一定会回家。问她要在学校待多久？

第一行输入一个$n$，表示她有$n$节课。

后面一行$n$个数字，数字只会是$0$或$1$，如果是$0$，则表示这是个课间，否则是一节课。

输出仅一行，表示她要在学校待的时间。

## 【思路】
很简单，由于如果有连续两个$0$，那么它的前一个或者后一个一定是$0$，且它本身是$0$，就这么判断有多少时间她在家里，然后减一下就完成了。

```cpp
#include <iostream>
using namespace std;
int n, a[10001];
int ans;
int main()
{
    cin >> n;
    for (register int i = 1;i <= n;i ++) cin >> a[i];
    ans = n;
    for (int i = 1;i <= n;++ i)
    {
        if(!a[i])
        {
            if(!a[i - 1] || !a[i + 1])
            {
                ans --;
            }
        }
    }
    cout << ans;
}
```

---

## 作者：绝艺 (赞：0)

英文题面给了那么长结果被一句中文翻译浓缩成了精华。。。

边读入边记录1的个数，然后扫一遍求夹在两个1中间的0的个数即可

毕竟n<=100还是很令人愉悦的

~~华丽丽的~~代码：

```cpp
#include <iostream>
using namespace std;
int main()
{
	int n,a[101],ans=0;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		if(a[i]==1) ans++;记录1的个数
	}
	for(int i=2;i<n;i++)
	{
		if(a[i]==0)先找到0
		{
			if(a[i-1]==1&&a[i+1]==1) ans++;判断是不是夹在1中间
		}
	}
	cout<<ans<<endl;
	return 0;
}
```


---

