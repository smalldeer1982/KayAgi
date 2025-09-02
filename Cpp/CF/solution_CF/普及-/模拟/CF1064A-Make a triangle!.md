# Make a triangle!

## 题目描述

Masha有三根长度分别为a,b,c厘米的小棒。每一分钟，Masha可以选择一根小棒并将它的长度增加一厘米，但他不可以折断小棒。
现在他要你求出他最少需要多少时间使得这三根小棒可以构成一个三角形。

## 样例 #1

### 输入

```
3 4 5
```

### 输出

```
0
```

## 样例 #2

### 输入

```
2 5 3
```

### 输出

```
1
```

## 样例 #3

### 输入

```
100 10 10
```

### 输出

```
81
```

# 题解

## 作者：communist (赞：6)

要让这个三角形合法，只需满足三角形不等式

即$a+b>c$，设$c=max\left\{a,b,c\right\}$，上式转化为$c<a+b$

如果已经满足，不需消耗代价

否则消耗$c-a-b+1$的代价

```
#include<iostream>
#include<cstdio>
using namespace std;
int a,b,c,maxn;
int main()
{
	scanf("%d%d%d",&a,&b,&c);
	maxn=max(a,max(b,c));
	if(2*maxn<a+b+c)
		printf("0\n");
	else
		printf("%d\n",maxn-(a+b+c-maxn)+1);
	return 0;
}
```

---

## 作者：C20212724杨京朝 (赞：2)

看到很多大佬用数学方法做，这是一篇模拟的题解
------------
思路概要：三角形中任意两边之和大于第三边 => a + b > c && b + c > a && a + c > b，根据小学数学，可以简化成：较小的两边之和大于第三边

代码实现：数组输入三边的长度，sort一遍即可得到较小的两边,然后只要不满足较小的两边之和大于第三边，就加长最短一边的长度，并刷新答案

------------
    #include <iostream>
    #include <algorithm>//sort头文件
    using namespace std;
    int a[15],ans = 0;//a数组记录输入的三个数，ans为答案
    int main() {
        for(int i = 1;i <= 3;i ++) cin >> a[i];//输入
        sort(a+1,a+4);//排序
        while(a[1] + a[2] <= a[3] && a[1] < a[3]) ans ++,a[1] ++;//详见上文
        printf("%d",ans);//输出
        return 0;
    } 

---

## 作者：冽酒灬忄 (赞：1)

题目大意：a,b,c三个整数，判断是否能组成三角形

如果能，则输出0；

如果不能，则增大这些数，使其能够组成三角形，输出增大的值的最小值

~~小学数学题~~

用两边之和大于第三边判断是否能组成三角形

如果不能就输出较长边长度+1减去剩下两边长度之和

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int a[4];
int main(){
	for(int i=1;i<=3;i++)
		cin>>a[i];
	sort(a+1,a+4);
	if(a[3]>=a[2]+a[1])//判断两边之和是否大于第三边
		cout<<a[3]-(a[2]+a[1])+1;
	else
		cout<<0;
}
```

---

## 作者：WsW_ (赞：0)

### 更新
这是一篇**已通过**的题解。
- $2024.12.14$ 更新题解。

---
### 思路

只有满足最大的边**大于**另外两边之和的三条边才能构成三角形，不然两条短边碰不到一起。  
所以我们先排序，求两短边之和比长边短了多少，然后补上短的长度就行了。但是要大于而不能等于，所以还要加 $1$。  
如果算出来是负数就说明两短边之和比长边要长，直接城里，输出 $0$。  
比较代码：

---
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[4];
int main(){
	scanf("%d%d%d",&a[1],&a[2],&a[3]);
	sort(a+1,a+4);
	printf("%d",max(a[3]-a[2]-a[1]+1,0));
	return 0;
}
```

---

## 作者：Cym10x (赞：0)

#### 题意解析
有三根小棒，求总共增加多少长度时，这三根小棒可组成三角形

#### 题目分析
设这三根小棒长度分别为$a$,$b$,$c$。
学过一点点数论/小学数学的OIer都知道：要使它们形成三角形，当$a \leq b \leq c$时，须满足$a+b>c$。考虑不停增加a的长度，直至$a+b>c$。

#### 解题步骤
1. 对$a$,$b$,$c$排序，使得$a \leq b \leq c$
2. 判断$a+b>c$，如果满足答案为0
3. 否则，根据上述解法，答案应为$c-a-b+1$\
(**易错点：这里的$+1$十分重要，因为$a+b$不能等于$c$**)

#### demo
```cpp
#include<stdio.h>
#define in(x) scanf("%d",&x)
#define out(x) printf("%d",x)
#define enter putchar(10)
#define space putchar(32)
/*这是本OIer的习惯*/
int swap(int &a,int &b){
	int t=a;a=b;b=t;return t;
}/*尽量少导入头文件，节约内存*/
int main(){
	int a,b,c;
	in(a);in(b);in(c);/*输入*/
	if(b>c)swap(b,c);
	if(a>c)swap(a,c);
	if(a>b)swap(a,b);
	/*上面3行用于排序，使得a<=b, b<=c*/
	if(a+b>c)out(0);/*如果一开始就已达到目标*/
	else out(c-a-b+1);/*有些人用O(n)小心翼翼地推，在此直接O(1)计算答案*/
	return 0;
	/*
		至此，本解法结束。
		时间复杂度：O(1)
		空间复杂度：O(1)
	*/
} 
```

[Cym10x](https://www.luogu.com.cn/user/354015)的第一篇题解

---

## 作者：Autism_ever (赞：0)

### 众所周知，三角形任意两条边之和大于第三条边
### 所以

### 太水了

### 上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[4],cnt=0;//记录摆多少根才可以 
int main()
{
	cin>>a[1]>>a[2]>>a[3];//输入 
	sort(a+1,a+3+1);//排个序 
	while(a[1]+a[2]<=a[3])//任意两边之和大于第三遍 
	{
		a[1]++;//最小的加1 
		cnt++;//总数+1 
	}
	cout<<cnt<<endl;
	return 0;
}
```


---

## 作者：Cult_style (赞：0)

按照题意模拟即可，但是可以用$O(1)$算法。

众所周知，想要组成三角形，需要任意两边之和大于第三边，那么，如果本来就满足条件，输出$0$，不然输出$a[3]-a[2]-a[1]+1$（需要先排序）

```
#include<bits/stdc++.h>
#define P(a,n) sort(a+1,a+1+n); 
using namespace std;
int a[5];
int main(){
	scanf("%d%d%d",&a[1],&a[2],&a[3]);
	P(a,3);
	if(a[1]+a[2]>a[3]) printf("0");
	else printf("%d",a[3]-a[1]-a[2]+1);
	
	return 0;
}
```


---

## 作者：xgwpp6710 (赞：0)

首先，三角形需要较小的两边之和大于第三边。

因此输入后先从小到大排序三条边。

然后直到满足要求，就一直给最小的一条边加。

很水的代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[3],t=0;
int main()
{
	cin>>a[0]>>a[1]>>a[2];
	sort(a,a+3);
	while(a[0]+a[1]<=a[2])//直到满足要求
	{
		a[0]++;
		t++;
	}
	cout<<t;
	return 0;
}
```

---

## 作者：Eason_AC (赞：0)

## Content
有三条长度分别为 $a,b,c$ 的线段。你可以在一个单位时间内将一条线段的长度增加 $1$，试求出能使这三条线段组成一个三角形的最短时间。

**数据范围：$1\leqslant a,b,c\leqslant 100$。**
## Solution
将这三个线段按照长度从小到大排序，设排序后的三条线段的长度依次为 $x_1,x_2,x_3$，然后判断是否有 $x_1+x_2>x_3$，是的话就直接可以组成一个三角形，否则需要 $x_3-(x_1+x_2)+1$ 个单位的时间才能使 $x_1+x_2>x_3$（注意不是 $\geqslant$）。
## Code
```cpp
int a[4], ans;

int main() {
	getint(a[1]), getint(a[2]), getint(a[3]);
	sort(a + 1, a + 4);
	writeint(ans = max(a[3] - (a[1] + a[2]) + 1, 0));
	return 0;
}
```

---

## 作者：tZEROちゃん (赞：0)

[题目传送门](https://www.luogu.org/problem/CF1064A)

反正数学方法我是不会

那只能模拟了~~一只连模拟题解都看不懂的哀怨~~

我的思路大体如下

1.定义3个变量a,b,c并输入
```cpp
	int a,b,c;
	cin>>a>>b>>c;
```
2.定义一个计数变量，归零；再定义一个最小值的变量，每次找出最小值增加1cm
```cpp
	int cnt=0;
	int minv;
```
3.~~前方高能~~代码核心处，使用循环

```cpp
	while(1)
```

因为懒得算循环几次，直接用死循环，符合要求就`break`即可

4.判断是否符合要求，符合要求就`break`即可
```cpp
	if(a+b>c && a+c>b && c+b>a){break;}
```

5.找出最小值minv
```cpp
	minv=min(a,min(b,c));
```

6.找到最小值对应的数 注意用`else`
```cpp
	if(minv==a)a++;
	else if(minv==b)b++;
	else if(minv==c)c++;
```

7.计数器++
```cpp
	cnt++;
```

8.最后输出计数器即可
```cpp
	cout<<cnt;
```

最后，上代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	int a,b,c;
	cin>>a>>b>>c;
	int cnt=0;
	int minv;
	while(1)
	{
		if(a+b>c && a+c>b && c+b>a){break;}
		minv=min(a,min(b,c));
		if(minv==a)a++;
		else if(minv==b)b++;
		else if(minv==c)c++;
		cnt++;
	}
	cout<<cnt;
	return 0;
}
```

---

## 作者：XMK_萌新 (赞：0)

前面有两位大佬用~~较为简易的~~数论知识发了两篇让人~~振奋人心~~能看懂的题解              

现在鄙人不才为了要赚贡献值用模拟手把手教你把大水题做成大火题~~然后让你怀疑人生的意义~~【滑稽】
```
#include <algorithm>
#include <iostream>
using namespace std;
int ans,a[3];	
int main()
{
    cin>>a[0]>>a[1]>>a[2];	//读入。为什么用数组存，要sort嘛。。
    sort(a,a+3);	//排个序才好找最小值
    while(a[0]+a[1]<=a[2])	//还不满足三角形条件，继续循环
    {
        a[0]++;	//把最短的木棒添长（其实你把次短木棒添长也没事啦233）
        ans++;	//年与时驰意与日去
        sort(a,a+3);	//然后还要再排个序
    }	//如果已经符合条件了，循环全部不会执行哦
    cout<<ans;	// 输出
    return 0;	//THE END
}
```

## **  __ _By xmkmx，一只回文蒟蒻（什么叫回文感受一下？）_ __  **

---

