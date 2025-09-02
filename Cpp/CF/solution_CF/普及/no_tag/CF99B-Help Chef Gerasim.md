# Help Chef Gerasim

## 题目描述

In a far away kingdom young pages help to set the table for the King. As they are terribly mischievous, one needs to keep an eye on the control whether they have set everything correctly. This time the royal chef Gerasim had the impression that the pages have played a prank again: they had poured the juice from one cup to another. Now Gerasim wants to check his hypothesis. The good thing is that chef Gerasim always pour the same number of milliliters of juice to all cups in the royal kitchen. Having thoroughly measured the juice in each cup, Gerasim asked you to write a program that will determine from which cup juice was poured to which one; otherwise, the program should determine that this time the pages set the table diligently.

To simplify your task we shall consider the cups to be bottomless so that the juice never overfills a cup and pours out, however much it can be. Besides, by some strange reason in a far away kingdom one can only pour to a cup or from one cup to another an integer number of milliliters of juice.

## 样例 #1

### 输入

```
5
270
250
250
230
250
```

### 输出

```
20 ml. from cup #4 to cup #1.
```

## 样例 #2

### 输入

```
5
250
250
250
250
250
```

### 输出

```
Exemplary pages.
```

## 样例 #3

### 输入

```
5
270
250
249
230
250
```

### 输出

```
Unrecoverable configuration.
```

# 题解

## 作者：hereiszd (赞：3)

蒟蒻的第一篇题解。

这个题还是特别水的，~~但我就被淹死了~~ 。

 ## 读题
 
  给了你一个数组，让你将其中一个数的一部分给另一个数，使所有数相等，**只操作一次**。当我们一看到只操作一次 ，就会很自然而然地想到：
  **就只有两个数不一样。** 
  所以我们就可以在这里下功夫。
  而改变之后所有数相同，**所以平均数就是所有数的数值。**
  
  **所以出现最多的数一定与平均数相同** ，并且,如果可以移动，剩下的两个数的平均数也一定与之相同 。
  
  我们就可以先判断整个数组的和能不能被数组大小 $n$ 整除，如果能，证明所有数的平均数就是 $sum/n$,如果不能的话操作一定不成立 
  如果平均数可以求出，那么这一组数就可以用多次操作使所有数相同。
  
  那怎样才能判断操作一次呢？
  操作一次只能改变两个数，那么**与出现最多的数不同的数只能有两个。** 
  那怎么判断这些数中出现最多的数的呢？
  我们会首先想到桶排。也不是不行，就是太浪费了，~~并且这水题也不足以用桶排~~，我们就又想起刚刚想到的： 
  **只有两个数不一样，其他数都等于平均数** ，所以我们只需要统计与平均数不同的个数即可。
  
  之后按照题目要求给出输出即可，~~千万别打错了~~。 
  ## $code$
  
  ```cpp
#include<iostream>
using namespace std;
int f[1001];
int flag;//与平均数不同的数字个数 
struct node{//可以同时记录最大最小的数值和对应下标 
	int num;//下标记录 
	int data;//数据记录 
};
node maxn,minn={0,0x3f3f3f};//将最小值的数据初始化为一个非常大的数，防止出错 
int sum;
int main(){
	int n;
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>f[i];
		sum+=f[i];
		if(maxn.data<f[i]){
			maxn.data=f[i];
			maxn.num=i;
		}
		if(minn.data>f[i]){
			minn.data=f[i];
			minn.num=i;
		}
	}//找最大和最小，求和，这里推荐写代码时把能合的for循环全部合起来，不仅能使码量更少，还能更快那么一点点 
	if(sum%n!=0) {
	cout<<"Unrecoverable configuration.";//无法整除那么一定不能实现题目要求 
	return 0;}
	else{
		int pj=sum/n;
		for(int i=0;i<n;i++){
			if(f[i]!=pj) flag++;
		}
		if(flag==0) {
			cout<<"Exemplary pages.\n";//如果平均数不同的数字个数为0，就是所有数字都一样 输出 
			return 0;}
		else if(flag>2) {
			cout<<"Unrecoverable configuration.\n";//如果与平均数不同的数超过2个，输出，注意是>而不是>=
			return 0;}
		else{
			printf("%d ml. from cup #%d to cup #%d.\n",(maxn.data-minn.data)/2,minn.num+1,maxn.num+1);//我的数组下标从0开始，所以要加1 
			//这里有个坑点，要从先输出杯中水少的再输出水多的  不要搞反了
			//还有倒水时是将一个杯子里的水倒入另一个，所以两个一个增加一个减少，要除以2 
			return 0;
	}
	}
	return 0;//over
}
```

   
 

---

## 作者：yingkeqian9217 (赞：2)

**前言：大水题一个**

咳咳，题目大意容易理解，要注意的是无论是倒的还是杯子的毫升数都是 **正整数** （曾被坑）。

因为总量的不变，所以我们可以先预处理出平均数，再进行判断。

这题细节比较多，我们先来考虑一下 $\verb!Unrecoverable!$ 的情况。

1.不与平均数相同的量不等于 $0$ 或 $2$。超过两个肯定无法一次倒完。

2.平均数不是整数，显然无法经过倒正整数毫升达到目的。

当全部一样就是 $\verb!Exemplary pages!$，否则就要经过一次操作。

输出的时候要注意两个要交换的量要经过排序，不然就有负数了……

$\huge\color{red}\text{AC }_{\color{black}\huge\text{Code}}\color{black}\text{:}$

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[1000001],x,y,sum;
signed main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),sum+=a[i];//预处理，累加总和
	if(sum%n!=0){//如果平均数不是整数
	 	printf("Unrecoverable configuration.\n");
	 	return 0;
	}
	for(int i=1;i<=n;i++)
	 if(a[i]!=sum/n&&y){//有超过两个不等于平均数的值
	 	printf("Unrecoverable configuration.\n");
	 	return 0;
	 }
	 else if(a[i]!=sum/n) y=x,x=i;//从别人学来的玄学赋值法，免去一个if
	if(a[x]<a[y]) swap(x,y);//按a[i]的值排序
	if(!x&&!y) printf("Exemplary pages.\n");
	else printf("%d ml. from cup #%d to cup #%d.\n",a[x]-sum/n,y,x);//printf快捷
        //注意第一个是小的，第二个才是大的。当然你反过来排序也不是不行
	return 0;
}

```

---

## 作者：foryou_ (赞：1)

分别对三种情况进行分类讨论。

第一种情况： 

- 显然，若 $\sum^{n}_{i=1} a_i \bmod n \neq 0$，则输出 $\texttt{Unrecoverable configuration.}$；

- 同时，我们遍历 $a_{1 \sim n}$，若存在两个以上的 $a_i$ 满足 $a_i \neq \sum^{n}_{i=1} a_i \div n$，则也输出 $\texttt{Unrecoverable configuration.}$。

第二种情况：

- 若 $a_{1 \sim n}$ 满足 $a_1=a_2=...=a_n$，则输出 $\texttt{Exemplary pages.}$。

第三种情况：

- 找到 $\neq \sum^{n}_{i=1} a_i \div n$ 两个数的编号 $x,y$，记 $x$ 应该给予 $y$ 的毫升数 $a_x-\sum^{n}_{i=1} a_i \div n$ 为 $m$（需要保证 $x>y$），则输出 $m \texttt{\ ml. from cup \#} \ y \texttt{\ to cup \#} \ x \texttt{.}$ 即可。注意输出格式。

```cpp
#include<bits/stdc++.h>
using namespace std;

int n,a[1031];
int x,y,sum;

int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i],sum+=a[i]; //读入 ai 并计算 sum
    if(sum%n!=0){ cout<<"Unrecoverable configuration."; return 0; } //第一种情况
    for(int i=1;i<=n;i++){
        if(a[i]!=sum/n&&y){ cout<<"Unrecoverable configuration."; return 0; } //还是第一种情况
        else if(a[i]!=sum/n){ y=x,x=i; } //从题解中学来的赋值方法
    }
    if(a[x]<a[y]) swap(x,y); //需要保证 x > y
    if(!x&&!y){ cout<<"Exemplary pages."; return 0; } //第二种情况
    cout<<a[x]-sum/n<<" ml. from cup #"<<y<<" to cup #"<<x<<"."; //第三种情况
    return 0;
}
```

---

## 作者：ask_silently (赞：0)

## 题目翻译
有 $n$ 个正整数，可以使两个正整数一个减去 $p$ ，一个加上 $p$ ，最后要使 $n$ 个正整数相同。

## 思路
- 首先先求出这 $n$ 个数的平均值，看一看和平均值不相同的有几个。因为我们只能操作两个数，所以我们只能允许两个数字和平均值不相同，如果三个及以上个数字不相同，那我们就输出 ``"Unrecoverable configuration."`` ，如果没有数字不相同，那我们就输出 ``"Exemplary pages."`` 。这是第一个判断。

- 第二个判断是两个数字是否是一个大于平均值，一个小于平均值。如果是的话，我们还要判断两个数字与平均值相减的绝对值是否相同，不相同我们就无法使它们相同。如果相同，我们就可以输出一段字符串。可能有些朋友看不懂字符串的含义，我来解释一下，第一个数字是开始我说的 $p$ 的值，然后是 ``"ml. from cup #"`` 紧接着一个数字是小于平均值的数字，再输出一个字符串 ``" to cup #"`` 然后是一个数字是大于平均值的数字，最后是一个句点。

## 代码
这道题的判断巨多，要注意一下先后关系。

```cpp
#include <iostream>
using namespace std;
int n,jun,xiao,da,flag;
int a[1010];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		jun+=a[i];    //求出平均值 
	}
	if(jun%n){    //如果不能整除直接排除 
		cout<<"Unrecoverable configuration."<<endl;
		return 0;
	}
	jun/=n;
	for(int i=1;i<=n;i++){
		if(a[i]!=jun){
			flag=1;    //标记一下有不等于平均值的 
			if(a[i]<jun){
				if(xiao){cout<<"Unrecoverable configuration."<<endl;return 0;}    //如果已经有小于平均值的话，直接排除 
				xiao=i;
			}else{
				if(da){cout<<"Unrecoverable configuration."<<endl;return 0;}    //如果已经有大于平均值的话，直接排除
				da=i;
			}
		}
	}
	if(!flag){cout<<"Exemplary pages."<<endl;return 0;}    //如果没有被标记过，说明都和平均值相同 
	if(jun-a[xiao]==a[da]-jun) cout<<jun-a[xiao]<<" ml. from cup #"<<xiao<<" to cup #"<<da<<"."<<endl;    //说明可以倒水 
	else cout<<"Unrecoverable configuration."<<endl;    //如果绝对值不同排除 
	return 0;
}

```


---

## 作者：Loser_Syx (赞：0)

逛了逛题解区，没人跟我一样用 STL 做的，于是就有了这篇题解。

## 思路

先定义结构体，分别记录水杯里的毫升数，和原序号，再将其排序，然后分类每种情况。

第一类：$n = 2$：

一开始没分类导致 WA on #9。

很显然当 $a_1 = a_2$ 时答案 `Exemplary pages.`。

当 $a_1$ 和 $a_2$ 的总和 $\bmod 2 = 1$ 时，显然不可能被均分，输出 `Unrecoverable configuration.`。

剩下情况都是 $a_1$ 向 $a_2$ 索要水。

其余：

$a_1 = a_n$ 时说明全部都是同一个数，答案 `Exemplary pages.`。

$a_1$ 和 $a_n$ 的总和 $\bmod$ $2 = 1$ 时不可能被均分，输出 `Unrecoverable configuration.`。

$a_1$ 和 $a_n$ 的总和 $\div 2$ 不等于 $a_2$（由于数组是有序的，且只有两头才会不一样）
，输出 `Unrecoverable configuration.`。

同理，当 $a_2$ 不等于 $a_{n-1}$ 时，也是 `Unrecoverable configuration.`。

其他情况都是 $a_1$ 向 $a_n$ 索要水。

## 代码

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#define int long long
using namespace std;
#define f(W, X, Y, Z) for(int W = X; W <= Y; W += Z)
#define F(W, X, Y, Z) for(int W = X; W >= Y; W -= Z)
#define debug puts("QAQ")
struct INF{
	int num;
	int i;
}a[10086];
bool cmp(INF x, INF y){
	return x.num < y.num;
}
signed main(){
	int n;
	scanf("%lld", &n);
	f(i, 1, n, 1){
		scanf("%lld", &a[i].num);
		a[i].i = i;
	}
	sort(a + 1, a + 1 + n, cmp);
	if(n == 2){
		if(a[1].num == a[2].num){
			puts("Exemplary pages.");
		}
		else if((a[1].num + a[2].num) % 2 == 1){
			puts("Unrecoverable configuration.");
		}else{
			printf("%lld ml. from cup #%lld to cup #%lld.\n", (a[n].num - a[n - 1].num) / 2, a[1].i, a[n].i);
		}
	}
	else if(a[2].num != a[n - 1].num){
		puts("Unrecoverable configuration.");
	}else if(a[1].num == a[n].num){
		puts("Exemplary pages.");
	}else if((a[1].num + a[n].num) % 2 == 1){
		puts("Unrecoverable configuration.");
	}
	else if((a[1].num + a[n].num) / 2 != a[2].num){
		puts("Unrecoverable configuration.");
	}else{
		printf("%lld ml. from cup #%lld to cup #%lld.\n", a[n].num - a[n - 1].num, a[1].i, a[n].i);
	}
	return 0;
}
```

---

## 作者：BushHuang (赞：0)

### 题目大意
 给你 $n$ 个正整数,问你是否能通过将其中一个数减去 $k$，另一个数加上 $k$ 使得这 $n$ 个数相等**且都为正整数**。
 
### 思路
我们设这 $n$ 个数的平均数为 $avg$，即 
$$avg=\frac{\sum_{i=1}^{n}a[i]}{n}$$ 

如果 $avg$ 不是一个正整数，则肯定无解。

如果这 $n$ 个数中有超过两个数或只有一个数不等于 $avg$，也无解。

如果这 $n$ 个数中每个数都等于 $avg$，则每个数相等，不需要进行操作。

否则就将那两个不等于 $avg$ 的数的差值以及编号输出。

### 代码
```
#include<bits/stdc++.h>
using namespace std;
int n,a[1001];
int tot,avg,not_avg=0,x=-1,y=-1,ix,iy;
bool all_avg=1;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		tot+=a[i]; //数列和
	}
	if(tot%n!=0)
	{
		cout<<"Unrecoverable configuration."<<endl; //平均数不是正整数
		return 0;
	}
	avg=tot/n; //平均数
	for(int i=1;i<=n;i++)
	{
		if(a[i]!=avg)
		{
			all_avg=0;
			if((++not_avg)>2)
			{
				cout<<"Unrecoverable configuration."<<endl; //超过两个数不是平均数
				return 0;
			}
			if(x!=-1) {y=a[i];iy=i;}
			else {x=a[i];ix=i;}
		}
	}
	if(all_avg)
	{
		cout<<"Exemplary pages."<<endl; //所有数都相等,无需移动
		return 0;
	}
	cout<<abs(x-y)/2<<" ml. from cup #"<<((x<y)?ix:iy)<<" to cup #"<<((x<y)?iy:ix)<<"."<<endl;
}
```

---

## 作者：_wjr_ (赞：0)

给定一个正整数 $n$ 与一个数组 $x_1,x_2,\cdots,x_n$，问能否只将一个数的一部分移给另一个数，使得所有  $n$ 个数一样。

### 题目思路

不难发现，不管几次操作，总和不变。也就是说，原数组中要有 $n-2$ 个数是平均值才行。若少于 $n-2$，则达不到；若为 $n$，则不用改变任何数。

### AC Code

```cpp
#include<bits/stdc++.h>

using namespace std;

int a[1010];

int main()
{
    int n, sum = 0;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        sum += a[i];
    }
    if (sum % n != 0)
    {
        cout << "Unrecoverable configuration.";
        return 0;
    }
    int m = sum / n, cnt = 0;//m为平均数
    for (int i = 1; i <= n; i++)//计数看原数组中有几个数是平均数
        if (a[i] != m) cnt++;
    if (!cnt)
    {
        cout << "Exemplary pages.";
        return 0;
    }
    else if (cnt > 2 || cnt == 1)//多余两个或为1（不可能为1）则不能满足
    {
        cout << "Unrecoverable configuration.";
        return 0;
    }
    else
    {
        int x1, x2;
        for (int i = 1; i <= n; i++)//判断将谁移向谁
        {
            if (a[i] != m)
            {
                if (a[i] > m) x1 = i;
                else x2 = i;
            }
        }
        cout << (a[x1] - a[x2]) / 2 <<" ml. from cup #" << x2 << " to cup #" << x1 << ".";
        return 0;
    }
    return 0;
}
```

完结撒花~

---

## 作者：windowshappy (赞：0)

题意是让你操作**一次**使所有杯中的水相等。

这题可以判断每个数的出现次数，如果大于 $ 3 $，输出 `Unrecoverable configuration.` 如果都一样，则输出 `Exemplary pages.` 否则输出从哪个杯向另一个杯倒了几毫升水。特别的，如果 $ n = 2 $ 则只判断这两个数。

**Code**
```cpp
#include<bits/stdc++.h>

using namespace std;
int a[1111];
int vis[10004];
int main(){
	int n;
	cin>>n;
	int maxn = 0;
	int minn = INT_MAX;
	int c1,c2;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		vis[a[i]]++;
		if(maxn<a[i]){ // 记录有最多水的杯子
			maxn = a[i];
			c1 = i; // 记录杯号
		}
		if(minn>a[i]){ // 记录有最少水的杯子
			minn = a[i];
			c2 = i;
		}
		
	}
	if(maxn==minn){ // 如果最大和最小相等，则所有元素一定相等
		cout<<"Exemplary pages.";
		return 0;
	}
   // 因为只能操作一次，所以最大和最小只能有一个
	if(vis[maxn]>1||vis[minn]>1){
		cout<<"Unrecoverable configuration.";
		return 0;
	}
	int tt = 0;
	for(int i=minn+1;i<maxn;i++){
		if(vis[i]!=0&&vis[i]!=n-2){ //剩下元素不全部相等也不行
			cout<<"Unrecoverable configuration.";
			return 0;
		}
		if(vis[i]!=0){ //否则记录其他杯子的容量
			tt = i;
			break;
		}
	}
	if((maxn+minn)%2!=0){ // 除不尽不行
		cout<<"Unrecoverable configuration.";
		return 0;
	}
	int cnt = (maxn+minn)/2;
	if(cnt!=tt&&n!=2){ // 除了 n = 2 其他的情况如果不等于平均值也不行
		cout<<"Unrecoverable configuration.";
		return 0;
	}
   // 输出答案
	printf("%d ml. from cup #%d to cup #%d.", maxn-cnt, c2, c1);
	return 0;
}
```


---

## 作者：abensyl (赞：0)

原题：[CF99B Help Chef Gerasim](https://www.luogu.com.cn/problem/CF99B)

推荐：本蒟蒻建议大家尝试 [CF714B](https://www.luogu.com.cn/problem/CF714B)

## 思路

注明：在下文中，将 `Unrecoverable configuration.` 成为无法操作，将 `Exemplary pages.` 称为无需操作，将 ` ml. from cup # to cup #.` 称为操作。

1. 输入所有数。

2. 将所有数的总和算出来。

- 为什么要算总和（设为 $s$）？

>1. 我们可以通过检查 $p \equiv 0 \pmod 8$ 来判断是否可被操作。

>2. 我们最终的目标是将所有数字都变为 $s\over n$。

3. 判断数列可否被操作。

- 如何判断？

>遍历整个数组。

>1. 判断是否正好有 $2$ 个不等于 $s\over n$ 那么需要操作，输出如何操作。

>2. 如果所有数都等于 $s\over n$，那么无需操作，输出 `Exemplary pages.`。

>3. 否则无法操作，输出 `Unrecoverable configuration`。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
  int n, a[1010], x, y, v, flag, i, j, sum, ar;
  scanf("%d", &n);
  sum = 0;
  for (i = 0; i < n; i++) {
    scanf("%d", &a[i]);
    sum += a[i];
  }
  flag = 0;
  if (sum % n)
    printf("Unarecoverable configuration.\n");
  else {
    ar = sum / n;
    for (i = 0; i < n; i++) {
      if (a[i] != ar) flag++;
    }
    if (flag != 2 && flag != 0)
      printf("Unrecoverable configuration.\n");
    else if (flag == 0)
      printf("Exemplary pages.\n");
    else {
      for (i = 0; i < n; i++) {
        if (a[i] < ar) x = i;
        if (a[i] > ar) y = i;
      }
      v = ar - a[x];
      printf("%d ml. from cup #%d to cup #%d.\n", v, x + 1, y + 1);
    }
  }
  return 0;
}
```

[AC记录](https://www.luogu.com.cn/record/83323638)

希望管理员能给个通过！

各位看官大佬，给本蒟蒻点个赞呗！

---

## 作者：MLCabc (赞：0)

 **此题无算法，简单题。**
# 分析

### 1. Exemplary pages.
显然，所有杯子中水量相同时，无需倒水（此处为方便，直接利用最小数    $Min$ 与最大数 $Max$ 是否是同一个数），直接输出“Exemplary pages.”

### 2. Unrecoverable configuration.
- 水量总和不是 $n$ 的倍数
- 有超过两杯水与其它水容量不同，即存在一杯水 $i$ ，既不是最少的，也不是最多的，又与平均数不相等。

这两种情况显然无法完成任务，直接输出“Unrecoverable configuration.”

### 3. 可以完成
实现很简单，让最多的分给最少的一些水，使它们水量一致即可。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,num[1005],Min=1,Max=1,sum;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>num[i];
		if(num[i]>num[Max])
			Max=i;
		if(num[i]<num[Min])
			Min=i;
		sum+=num[i];
	}
	if(sum%n){
		cout<<"Unrecoverable configuration.";
		return 0;
	}
	int pj=sum/n;
	for(int i=1;i<=n;i++){
		if(i!=Min&&i!=Max&&num[i]!=pj){
			cout<<"Unrecoverable configuration.";
			return 0;
		}
	}
	if(Min==Max){
		cout<<"Exemplary pages.";
		return 0;
	}
	cout<<(num[Max]-num[Min])/2<<" ml. from cup #"<<Min<<" to cup #"<<Max<<".";
	return 0;
}
```

**温馨提示：若本地测试看似正确，实际错误的同学，请仔细检查输出格式**



---

## 作者：123456zmy (赞：0)

题意：

给定一个序列，问是否能用一个所有值相等的序列通过一次操作得到。（一次操作指将一个元素增加 $k$ ，另一个元素减少 $k$。）如果可以，参照样例输出方式；如果不需操作输出"Exemplary pages."；如果无法得到，输出"Unrecoverable configuration."。
___
分类讨论一下即可。

~~显然~~当且仅当下列条件成立时，可以得到目标序列：
* 序列平均数是 $n$ 的倍数；
* 序列中除最大值和最小值以外，其它值都相等；
* 最大值和最小值的平均数与序列平均数相等。

于是多打几个 if 就可以了，代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[1001],minn=1,maxn=1,sum;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		if(a[i]>a[maxn])maxn=i;
		if(a[i]<a[minn])minn=i;
		sum+=a[i];
	}
	if(sum%n)
	{
		puts("Unrecoverable configuration.");
		return 0;
	}
	sum/=n;
	for(int i=1;i<=n;i++)
	{
		if(i!=minn&&i!=maxn&&a[i]!=sum)
		{
			puts("Unrecoverable configuration.");
			return 0;
		}
	}
	if(minn==maxn)
	{
		puts("Exemplary pages.");
		return 0;
	}
	printf("%d ml. from cup #%d to cup #%d.",a[maxn]-a[minn]>>1,minn,maxn);
	return 0;
}
```

---

