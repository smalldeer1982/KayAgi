# Getting an A

## 题目描述

Translator's note: in Russia's most widespread grading system, there are four grades: 5, 4, 3, 2, the higher the better, roughly corresponding to A, B, C and F respectively in American grading system.

The term is coming to an end and students start thinking about their grades. Today, a professor told his students that the grades for his course would be given out automatically — he would calculate the simple average (arithmetic mean) of all grades given out for lab works this term and round to the nearest integer. The rounding would be done in favour of the student — $ 4.5 $ would be rounded up to $ 5 $ (as in example 3), but $ 4.4 $ would be rounded down to $ 4 $ .

This does not bode well for Vasya who didn't think those lab works would influence anything, so he may receive a grade worse than $ 5 $ (maybe even the dreaded $ 2 $ ). However, the professor allowed him to redo some of his works of Vasya's choosing to increase his average grade. Vasya wants to redo as as few lab works as possible in order to get $ 5 $ for the course. Of course, Vasya will get $ 5 $ for the lab works he chooses to redo.

Help Vasya — calculate the minimum amount of lab works Vasya has to redo.

## 说明/提示

In the first sample, it is enough to redo two lab works to make two $ 4 $ s into $ 5 $ s.

In the second sample, Vasya's average is already $ 4.75 $ so he doesn't have to redo anything to get a $ 5 $ .

In the second sample Vasya has to redo one lab work to get rid of one of the $ 3 $ s, that will make the average exactly $ 4.5 $ so the final grade would be $ 5 $ .

## 样例 #1

### 输入

```
3
4 4 4
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4
5 4 5 5
```

### 输出

```
0
```

## 样例 #3

### 输入

```
4
5 3 3 5
```

### 输出

```
1
```

# 题解

## 作者：C_Cong (赞：4)

[博客传送门](https://dgsyrc.github.io/2020/04/12/洛谷题解%20CF991B%20【Getting%20an%20A】/#more)

### 题意简述：

给你几门测试的成绩，问你最少要重测几门才能使平均成绩四舍五入为5分

### 解题思路：

其实就是贪心的思想，而且要用到万恶的$sort$（图个方便）

根据我们的生活经验，很容易就能想到先把差的重测

又因为题目中有`最少`的字眼，故我们可以假设重测后就能满分（实际上几乎不可能，但是我们要作为理想状态考虑）

~~是不是有人看到四舍五入就头痛了~~

这里提供一种简便的方法：

所有数据扩大十倍，这样原来的十分位就变成了个位

然后你就可以直接处理了

我的代码没有用整除，取而代之的是乘法（这是有好处的）

显然$sum/n \geq 45$和$n*45 \leq sum$等价

代码实现：

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;

int n,src[110],sum;

int main()
{
	scanf("%d",&n);
	for(int a=1;a<=n;++a)
	{
		scanf("%d",&src[a]);
		src[a]=src[a]*10;//扩大十倍
		sum=sum+src[a];//累加记录总分
	}
	sort(src+1,src+n+1);
	int cot=0;
	while(n*45>=sum)//判断是否满足题目条件
	{
		cot++;//统计重测次数
		sum=sum-src[cot]+50;//把当前最低分改为满分重新计入总分
	}
	printf("%d\n",cot);
	return 0;
}
```

有帮助的话点个赞顶上去才能让更多人看见哦！

---

## 作者：zilingheimei (赞：1)

~~又是一个不知道怎么上黄的题目。~~

先看题目：

[CF991B Getting an A](https://www.luogu.com.cn/problem/CF991B)

样例下面有解释，但是英文的，所以还是讲一下吧：

1. 样例: 重考两门考到5分，平均成绩为4.5，满足四舍五入为5，所以是2。

2. 样例：开始的平均成绩就是4.75，满足四舍五入为5，所以不用重考，所以是0。

3. 样例：重考一门考到5分，平均成绩为4.5，满足四舍五入为5，所以是1。


------------

思路如下：

- 将考试分数总分记录，判断平均成绩是否$\geq$4.5，是直接输出0然后结束。

```cpp
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		x+=a[i];//总分
	}
	if(x/n>=4.5){//x/n为平均成绩
		cout<<0;
		return 0;
	}
```


- 发现不是，先将数组的每个数用$\operatorname{sort}$排序。

```cpp
	sort(a+1,a+n+1);
```

- 然后从小到大循环，每次总分加上重考比之前多的分，判断是否$\geq$4.5,是就输出当前在第几个循环然后结束，不是就加上多的分继续循环。

```cpp
	for(int i=1;i<=n;i++){
		if((x+5-a[i])/n>=4.5){//5-a[i]为多的分
			cout<<i;
			return 0;
		}
		x+=5-a[i];
	}
```


------------

代码上面都讲过了，就不放了（

---

## 作者：happybob (赞：1)

 这个题目先要仔细审题，特别注意是“重测”，不是“再测”。

先想想，如果我们要将平均分变为5，肯定把越少的分先重测变为5好对吧？

那么既然要排序，那么STL久登场喽，用sort轻松解决。

第二个问题，四舍五入：

在cmath库中，有个叫round的函数，可以实现四舍五入

round是四舍五入函数，头文件cmath，round函数只有一个参数，要用double，这个题用int你还要四舍五入干嘛……

继续说，round函数是四舍五入取整，如果需要将x保留n位小数，只需要先乘再除

如下为公式（将x保留n位小数）：

```cpp
round(x * pow(10, n)) / pow(10, n);
```
其中pow(10, n)表示10^n，10的n次方，10的1次方是10，,10的2次方是10 * 10，10的3次方是10 * 10 * 10……

比如round函数将9.9839保留3位小数

```
round(9.9839 * 1000) / 1000
```

那么学会了round，代码就简单啦：

```cpp
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

double arr[105];

int main()
{
    int n, x, sum = 0;
    cin >> n;
    for(int i = 1; i <= n; i++)
    {
        cin >> arr[i];
        sum += arr[i];
    }
    int average = round(sum * 1.0 / n);
    int c = 0;
    sort(arr + 1, arr + n + 1);
    while(average < 5)
    {
        for(int i = 1; i <= n; i++)
        {
            if(arr[i] != 5)
            {
                sum += 5 - arr[i];
                arr[i] = 5;
                break;
            }
        }
        c++;
        average = round(sum * 1.0 / n);
    }
    cout << c << endl;
    return 0;
}
```


---

## 作者：封禁用户 (赞：1)

先解释这道题（那个翻译让人看不懂）：某人做了X次实验，每次拿了2~5分。现在他想重做试验来得到五分（四舍五入），那么他至少要重做几次？

是不是为四舍五入而烦得要死？那么，最简单的方法就是把数字放大十倍。那么，你知道的~~这样用整数就可以出来了，不怕忘记强制转换咯！

这样只要平均分>=45就可以了，不会苦了我们这些不会强制转换的

```
#include <bits/stdc++.h>
using namespace std;
long long n,a[105],sum,x=0;
bool cmp(long long x,long long y)
{
	return x<y;
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)//输入 
	{
		cin>>a[i];
		a[i]*=10;//a[i]*10算出来的总分就会乘10，看是否大于45就可以了，笔者经常我了强制转换，那么就要全部为5分才可以 
		sum=sum+a[i];
	}
	sort(a+1,a+n+1,cmp);//贪心，肯定改分数低的 
	for(int i=1;i<=n;i++)
	{
		if(sum/n>=45)//如果平均分》>45(也就是现实中>4.5)，就不用重做了 
		break;
		else
		{
			sum=sum-a[i]+50;//减去原来的分数，按满分算 
			x++;//变化的次数++ 
		}
	}
	cout<<x;//输出变化的次数 
	return 0;
}
```

---

## 作者：TLMPEX (赞：0)

这道题用贪心做会更简单一些，思路详见代码。

代码：

```c
#include<bits/stdc++.h>
using namespace std;
int a[101];
int main(){
	double x,z=0;
	int n,i;
	cin>>n;
	for(i=1;i<=n;i++){
		cin>>a[i];//输入
		z+=a[i];//累加总和
	}
	x=z/n;//平均分
	if(x-int(x)>=0.5&&ceil(x)>=5||floor(x)>=5){
		cout<<0;
		return 0;
	}
	sort(a+1,a+n+1);//排序
	for(i=1;i<=n;i++){
		z+=5-a[i];//累加每个数与5的差
		x=z/n;//平均分
		if(x-int(x)>=0.5&&ceil(x)>=5||floor(x)>=5){
			cout<<i;//如果符合条件，输出
			return 0;
		}
	}
}
```


---

## 作者：Arghariza (赞：0)

- 当然如果一开始的平均数就大于等于 $4.5$ ，直接输出 $0$ 即可。
- 如果开始平均数小于 $4.5$ ，怎么让每次修改得到的平均数最大？很简单，直接把数组**从小到大**排序，从 $s_1$ 开始修改成 $5$ 即可。每轮修改的时候 $ans++$， 修改的时候要计算平均数，如果此时平均数大于 $4.5$ 的话直接输出 $ans$ 就行了。一次一次算平均数如果怕麻烦的话就多开一个变量 $sum$ 记录当前所有数的总和，如果修改了 $s_i$ 即 $sum=sum+5-s_i$ ，最后 $\frac{sum}{n}$ 即为平均值。

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, sum;
double s[100001];

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> s[i];
		sum += s[i];
	}
	if (sum / (double)n >= 4.5) cout << 0;// 如果一开始平均数大于等于4.5
	else {
		int ans = 0;
		sort(s + 1, s + n + 1, less<double> ());// 从小到大排序
		for (int i = 1; i <= n; i++) {// 一项一项修改
			ans++;// 步数++
			sum += (5 - s[i]);// 计算当前和
			if (sum / (double)n >= 4.5) {// 计算平均数如果大于4.5直接输出
				cout << ans;
				return 0;
			}
		}
	}
	return 0;
}
```

---

## 作者：Insouciant21 (赞：0)

#### 题意

给出 $n$ 次实验得分，让你计算至少需要重新测试其中的几次后平均分能达到 $5$。

#### 方法

很明显这是一道很简单的贪心，使用优先队列排序然后顺次取出直到平均分大于 $5$ 即可。

因为有题目要求最少的次数，所以我们就重测分数最低的实验并认为这次实验是满分，即 $5$ 。

关于四舍五入：

对于一个小数 $x$ ，判断小数位是否大于 $0.5$ 只需对 $x$ 加上 $0.5$ 后再向下取整，即 $round(x)=\lfloor x+0.5\rfloor$

代码如下

```
#include <bits/stdc++.h>

using namespace std;

priority_queue<int, vector<int>, greater<int>> q; // 小顶堆
int n;

int main() {
    double sum = 0;
    cin >> n;
    for (int i = 1, t; i <= n; i++) {
        cin >> t;
        sum += t;
        q.push(t);
    }
    int cnt = 0;
    int avg = int(sum / n + 0.5); // 四舍五入计算平均分
    for (; avg < 5; cnt++) {
        int p = q.top();
        q.pop(); // 取出
        sum -= p;  // 从总分中去掉当前剩下最低分
        sum += 5;  // 设这次最低分为满分
        avg = int(sum / n + 0.5);
    }
    cout << cnt << endl;
    return 0;
}
```

---

## 作者：TRZ_2007 (赞：0)

题解 [CF991B 【Getting an A】](https://www.luogu.com.cn/problem/CF991B)  
# Solution
题目中问你**最少**要做几次试验，所以我们就可以考虑**贪心**，每一次我们都改那个做的**最差的**，这样子平均分上来的就最快。  
那么怎样才可以让平均分**四舍五入**到满分呢？  
我们列个不等式：  
$$\dfrac{s}{n} \ge 4.5$$  
$$\therefore s\ge 4.5n$$  
$$\therefore 2s\ge 9n$$  

所以我们只要让总分 $s$ 满足上面的不等式就好了。  
由于每次改分都会产生一个满分，所以我们通过维护一个**堆**来取得最小值。  
# Code  
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 109;

int a[N],n,s,cnt;

priority_queue<int,vector<int>,greater<int> > q;

int main() {
	scanf("%d",&n);
	for(int i = 1;i <= n;i++) {
		scanf("%d",&a[i]);
		q.push(a[i]);
		s += a[i];
	}
	while(2 * s < 9 * n) {
		cnt++;
		s += (5 - q.top());
		q.pop();q.push(5);
	}
	printf("%d\n",cnt);
    return 0;
}
```

---

## 作者：hensier (赞：0)

这道题是一个较为容易理解的贪心题。我们每次要改分数最低的，所以可以用$sort$进行快排。

$AC$代码：

```cpp
#include<bits/stdc++.h>//万能头文件
#define f()for(int i=0;i<n;i++)//宏定义
int n,a[100],s;//定义
int main()
{
    memset(a,0x7f,sizeof(a));//这里可以把数组的所有元素改成2139062143，与int_max的值相差无几。这样做的原因是一开始a[100]所有元素为0，而sort后这些0就会到前面去
    scanf("%d",&n);//输入
    f()
    {
        scanf("%d",&a[i]);//输入
        s+=a[i];//求和
    }
    if(1.0*s/n>=4.5)//如果已经满足就直接输出0
    {
        printf("0");
        return 0;
    }
    std::sort(a,a+n);//快排
    f()
    {
        s-=a[i]-5;/把s减去a[i]再加上5
        if(s*1.0/n>=4.5)//如果满足就输出并结束程序
        {
            printf("%d",i+1);
            return 0;
        }
        a[i]=5;//必不可少
    }
}
```


---

## 作者：da32s1da (赞：0)

很明显，把分数最低的重做最好。

我们要让$Ans\ge 4.5n$，就要使$\ 2\ Ans\ge 9n$。

这里使用了priority_queue来排序。~~我太懒了没用sort~~

每次取出分数最小的重做即可。

```
#include<cstdio>
#include<queue>
using namespace std;
int n,ans,x,Tim;
priority_queue<int>s;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&x);
		ans+=x;
		if(x!=5)s.push(-x);
        //把不满分的丢进去
	}
	while(ans*2<n*9){
		x=-s.top();//取出分数最低的
		s.pop();
		ans+=5-x;//分数加一下
		Tim++;
	}
	printf("%d\n",Tim);
}
```

---

