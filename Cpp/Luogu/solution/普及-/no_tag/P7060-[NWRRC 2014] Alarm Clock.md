# [NWRRC 2014] Alarm Clock

## 题目描述

Alice 喜欢她的数字闹钟。她每天晚上都会设置好闹钟。昨晚 Alice 做了一个关于她闹钟的梦。不幸的是，她唯一能记得的是闹钟上高亮显示的段数。Alice 想知道她梦中闹钟上设置的时间。

Alice 的闹钟有四位数字：两个表示小时，两个表示分钟。例如，下面的闹钟显示的是 $9:30$（注意前导零）。

![](https://cdn.luogu.com.cn/upload/image_hosting/6dl4fhwk.png)

闹钟使用以下数字表示法。

![](https://cdn.luogu.com.cn/upload/image_hosting/igdzsez5.png)

## 说明/提示

时间限制：2 秒，内存限制：256 MB。

spj 提供者：@[rzh123](user/237530)

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
23
```

### 输出

```
09:30
```

## 样例 #2

### 输入

```
28
```

### 输出

```
Impossible
```

## 样例 #3

### 输入

```
2
```

### 输出

```
Impossible
```

# 题解

## 作者：幻想繁星 (赞：11)

### 蒟蒻的第一篇题解

------------

首先预处理 $0$ 到 $9$ 每个数字所用的段数，分别为：$6,2,5,5,4,5,6,3,7,6$。则会为接下来的枚举提供极大的便利。
```cpp
int n[10]={6,2,5,5,4,5,6,3,7,6};
```

------------

然后就是枚举，枚举每一个分钟点一共有  $24\times60=1440$  种情况，完全可以跑过去。枚举时统计该分钟点的段数，如果段数等于题目输入的 $n$，则输出该分钟点，并结束程序。如果枚举完所有分钟点还没有找到，就输出“Impossible”。  
~~（灰常简单有木有）~~

------------

代码如下：
```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
int n[10]={6,2,5,5,4,5,6,3,7,6},a,s;//预处理和定义
int main()
{
	cin>>a;
	for(int i=0;i<=23;i++) for(int j=0;j<60;j++)//开始枚举
	{
		s=0;//s统计段数
		s+=n[i%10];//累加小时的个位
		s+=n[i/10];//累加小时的十位
		s+=n[j%10];//累加分钟的个位
		s+=n[j/10];//累加分钟的十位
		if(s==a)
		{
			printf("%02d:%02d",i,j);//输出（printf可以自动补零，省去了if判断）
			return 0;
		}
	}
	cout<<"Impossible";//没有找到，就输出"Impossible"
	return 0;
}
```

---

## 作者：Wind_Smiled (赞：4)

## 题意
给定一个数字 $n$，要求用 $n$ 根火柴组成一个正确的时间。若不能组成，则输出 Impossible 。


------------

### 补零的另一种方法
这里我用的是一个函数返回的值来确定组成一个数字所需要的火柴数，然后直接用双重循环模拟时间的变化，若是找到了需要的时间，输出后结束程序，若不能找到，则在枚举完之后输出 Impossible 即可。

程序中的 $a,b,c,d$ 所储存的是时间的每一位，且可以存储并输出前导零，不用特判或特殊输出。即 $a$ 储存小时的十位，$b$ 储存小时的个位，$c$ 储存分钟的十位，$d$ 储存分钟的个位。


------------

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int h,n,s,a,b,c,d;
int change(int x){
    if(x==0) return 6;
    else if(x==1) return 2;
    else if(x==2) return 5;
    else if(x==3) return 5;
    else if(x==4) return 4;
    else if(x==5) return 5;
    else if(x==6) return 6;
    else if(x==7) return 3;
    else if(x==8) return 7;
    else if(x==9) return 6;
}
int main(){
    cin>>n;
    for(int i=0;i<=23;i++){
        for(int j=0;j<=59;j++){
            a=i/10,b=i%10,c=j/10,d=j%10;
            s=change(a)+change(b)+change(c)+change(d);
            if(s==n){
                cout<<a<<b<<":"<<c<<d;
                return 0;
            }
        }
    }
    cout<<"Impossible";
    return 0;
}
```

---

## 作者：iterator_it (赞：2)

这道题目非常水，我们可以发现，点钟的时间只可能在 $0$ 到 $23$ 之间，分钟的时间只可能在 $0$ 到 $59$ 之间，所以我们只需要双层循环枚举即可。

**注意：题目中的数字需要有前导零，所以我们不能直接输出。**

AC CODE：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
const int num[]={6, 2, 5, 5, 4, 5, 6, 3, 7, 6};
void print(int x){    //手写输出函数，可以输出前导零
    if(x<10) cout<<0;
    cout<<x;
}
int main(){
    cin>>n;
    for(int i=0;i<24;i++){
        for(int j=0;j<60;j++){
            int a=i/10,b=i%10,c=j/10,d=j%10;//各个数位的数字
            if((num[a]+num[b]+num[c]+num[d])==n){
                print(i);//调用输出函数
                cout<<":";
                print(j);
                return 0;//找到第一个就直接结束程序
            }
        }
    }
    cout<<"Impossible";//如果都不符合，就说明无解
    return 0;
}
```

---

## 作者：_zhy (赞：1)

[Link](https://www.luogu.com.cn/problem/P7060)

## 题目大意

给定一个火柴棒的数量 $n$，你需要使用这 $n$ 根火柴棒组成一个合法的时间。

如果无法组成，输出 `Impossible`。

**注意：一定是合法的时间，题目中要求小时不超过 $23$，分钟不超过 $59$。还有，火柴棒一定是刚好用完。**

## 思路

看到这个题，我首先想到了搜索，我们可以把每一种 $0 \sim 9$ 的数字排列求出来，并用一个变量 $x$ 记录下用来都少根火柴棒。

最后判断是否合法即可。

因为是时间，所以搜四位数字就行。

为了方便，我们还可以用一个数组 $a$ 表示 $0 \sim 9$ 每一个数字分别需要多少火柴棒。

如果搜到了答案，就输出并结束**整个程序**。

如果搜搜索结束了程序还没结束，就输出 `Impossible`。

## code

```cpp
#include <cstdio>
#include <iostream>

const int a[15] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};	//记录每种数字需用多少根火柴棒。 

int n, b[5];

inline void dfs(int x, int y) {
	if (y == 5) {	//已经搜到了四个数 
		if (x == n)		//火柴棒数量满足条件。 
			if (b[1] < 2 || (b[1] == 2 && b[2] < 4))	//小时不超过24。 
				if (b[3] < 6) {		//分钟不超过59。 
					for (int i = 1; i <= 4; i++) {
						printf("%d", b[i]);
						if (i == 2)
							putchar(':');	//不要忘记冒号。 
					}
					exit(0); 
				}
		return ;
	}
	for (int i = 0; i <= 9; i++) {
		b[y] = i;
		dfs(x + a[i], y + 1);
	}
}

int main() {
	scanf("%d", &n);
	dfs(0, 1);
	puts("Impossible");	//如果程序还没结束，输出不可能。 
	return 0;
}
```

---

## 作者：Supor__Shoep (赞：1)

这道题可以说是非常水了。。。

我们可以暴力枚举一波，从 $00:00$ 一直枚举到 $23:59$ 。运用到循环里，就是双重循环。

对于每个数字用的火柴，我们可以用数组存放，只要摆的四个数字的火柴和刚好等于 $n$ ，我们就直接输出这个答案。一直等到循环结束，也就是没有摆的出来的时间，我们就可以输出 Impossible 了。

其实呢这道题的答案是多种的，只不过我们遇到一个正确的答案输出，就覆盖了后面所有的答案了。

不过在这里，我用了一个输出的 void 函数，因为输出时间的时候我们要考虑到输出 $0$ 的情况，还有冒号。因此我用比较简短的方式写了一下：

如果时为一位数，那么就补一个 $0$ ，输出冒号，然后用同样的方式判断分，如果分也是一位数，那么也要在前面补 $0$ 。我们在这里只用判断一位数，因为补完了 $0$ 之后的输出无论如何也变成了两位数，不必在意。代码如下：

```cpp
void print(int n,int m)
{
	if(n<10)
	{
		cout<<"0";
	}
	cout<<n<<":";
	if(m<10)
	{
		cout<<"0";
	}
	cout<<m;
}
```

#### 代码时刻

```cpp
#include<bits/stdc++.h>
using namespace std;
int hc[13]={6,2,5,5,4,5,6,3,7,6};
void print(int n,int m)
{
	if(n<10)
	{
		cout<<"0";
	}
	cout<<n<<":";
	if(m<10)
	{
		cout<<"0";
	}
	cout<<m;
}
int main()
{
	int n;
	cin>>n;
	for(int i=0;i<24;i++)
	{
		for(int j=0;j<60;j++)
		{
			if(hc[i/10]+hc[i%10]+hc[j/10]+hc[j%10]==n)
			{
				print(i,j);
				return 0;
			}
		}
	}
	cout<<"Impossible";
	return 0;
}
```

---

## 作者：rzh123 (赞：1)

# P7060 题解

题目链接：[P7060 [NWRRC2014]Alarm Clock](https://www.luogu.com.cn/problem/P7060)  

简单题，枚举小时和分钟，再判断是否符合条件  

```cpp
#include <cstdio>
int n,x[13]={6,2,5,5,4,5,6,3,7,6};
int ok(int a,int b){
	int t=x[a/10]+x[a%10]+x[b/10]+x[b%10];
	return t==n;
}
int main(){
	scanf("%d",&n);
	for(int i=0;i<24;++i){
		for(int j=0;j<60;++j){
			if(ok(i,j)){
				printf("%02d:%02d\n",i,j);
				return 0;
			}
		}
	}
	puts("Impossible");
	return 0;
}
```  

当然，$0 \le n \le 30$，可以打表。  

Generator:  

```cpp
#include <cstdio>
int n,x[13]={6,2,5,5,4,5,6,3,7,6};
int ok(int a,int b){
	int t=x[a/10]+x[a%10]+x[b/10]+x[b%10];
	return t==n;
}
void solve(int nn){
	n=nn;
	for(int i=0;i<24;++i){
		for(int j=0;j<60;++j){
			if(ok(i,j)){
				printf("\"%02d:%02d\"",i,j);
				return;
			}
		}
	}
	printf("\"Impossible\"");
}
int main(){
	freopen("P7060_2.cpp","w",stdout);
	puts("#include <cstdio>");
	printf("char ans[37][17]={");
	for(int i=0;i<=30;++i){
		if(i>0){
			putchar(',');
		}
		solve(i);
	}
	puts("};");
	puts("int main(){");
	puts("\tint n;");
	puts("\tscanf(\"%d\",&n);");
	puts("\tputs(ans[n]);");
	puts("\treturn 0;");
	puts("}");
	return 0;
}
```  

打表程序：  

```cpp
#include <cstdio>
char ans[37][17]={"Impossible","Impossible","Impossible","Impossible","Impossible","Impossible","Impossible","Impossible","11:11","11:17","11:14","11:12","01:11","01:17","01:14","01:12","00:11","00:17","00:14","00:12","00:01","00:07","00:04","00:02","00:00","00:08","08:08","Impossible","Impossible","Impossible","Impossible"};
int main(){
	int n;
	scanf("%d",&n);
	puts(ans[n]);
	return 0;
}
```  

请不要抄题解！

---

## 作者：封禁用户 (赞：0)

## 思路
其实也没啥，就是把枚举 $24 \times 60=1440$ 个分钟点，然后把每个数字的火柴棒数量打成一张表，大概长这个样子:

$$[6,2,5,5,4,5,6,3,7,6
]$$

看看有没有符合要求的，如果没有就输出 ```Impossible```。

代码应该也比较好理解。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int match[]={6,2,5,5,4,5,6,3,7,6};//一张火柴棒数量的表
int main(){
	cin>>n;
	for(int i=0;i<=23;i++){//枚举24小时
		for(int j=0;j<=59;j++){//枚举60分钟
			if(match[i/10]+match[i%10]+match[j/10]+match[j%10]==n){//符合条件就直接输出
				printf("%02d:%02d\n",i,j);//一个用printf快捷的输出方法
				goto end;//退出循环
			}
		}
	}
	cout<<"Impossible"<<endl;//无解
	end:;
	return 0;
}
```


---

## 作者：zeekliu (赞：0)

由于此题对时间和空间要求极低，因此直接枚举 $ 00:00 $ ~ $ 23:59 $。

首先记录 $ 0 $ ~ $ 9 $ 的火柴棒根数：
$ {6,2,5,5,4,5,6,3,7,6} $

然后统计每一分钟的火柴棒根数，记录在数组里，最后输入 $ n $，然后寻找相应的根数输出，没有就输出 ```Impossible```。

~~好像有点麻烦~~

下面代码：

```cpp
//P7060 22-08-24
#include <bits/stdc++.h>
using namespace std;
int a[10]={6,2,5,5,4,5,6,3,7,6};
int x[24][60];

int main() 
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	for (int i=0;i<=23;i++)
		for (int j=0;j<=5;j++)
			for (int k=0;k<=9;k++)
				x[i][j*10+k]=a[i/10]+a[i%10]+a[j]+a[k];
	int n; cin>>n;
	for (int i=0;i<=23;i++)
		for (int j=0;j<=59;j++)
			if (x[i][j]==n)
			{
				if (i<10) cout<<0;
				cout<<i<<":";
				if (j<10) cout<<0;
				cout<<j<<endl;
				exit(0);
			}
	cout<<"Impossible"<<endl;
	return 0;
}
```

---

## 作者：_lmz_ (赞：0)

管理大大看到以后记得把这题变成橙题。

首先，我们数出来数字 $0$ 到 $9$ 分别需要：$6,2,5,5,4,5,6,3,7,6$ 根火柴棒，然后这题就变成了一道非常简单的朴素枚举。

我们分别枚举点钟和分钟，然后计算，如果需要的是 $n$ 根，就直接输出，如果循环到最后还没有找到，就输出 `Impossible`。

注意事项：

1.要计算前导零。

2.样例 #1 最小的输出应该为 $00:02$，就这一点让我以为程序写错了。~~然后结合了灰题的难度冥想了半小时。~~

最后给出代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int num[]={6, 2, 5, 5, 4, 5, 6, 3, 7, 6};
int n;
int main(){
	cin>>n;
	for(int i=0;i<=23;i++){
		for(int j=0;j<60;j++){
			int sum=0;
			int x=i%10;sum+=num[x];
			x=i/10;sum+=num[x];
			x=j%10;sum+=num[x];
			x=j/10;sum+=num[x];
			if(sum==n){
				if(i<10)cout<<'0'<<i<<':';
				else cout<<i<<':';
				if(j<10)cout<<"0"<<j;
				else cout<<j;
				return 0;
			}
		}
	}
	cout<<"Impossible";
	return 0;
}
```

---

