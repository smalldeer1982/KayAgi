# Uncowed Forces

## 题目描述

凯文刚刚完成了 CF 的比赛。测试时间为 120 分钟，有 5 个题目。题目 1~5 的满分分别是: 500、1000、1500、2000  和 2500。他作答了所有的题。

他知道自己每个问题的提交时间、每个问题上他提交错误的次数，以及它提交正确和错误的总数。

但 CF 评分的机制很复杂， 凯文想知道他的最终得分。

评分机制：设一个问题的最高分是 x ,提交者在第 m 分钟时提交正确，提交者错误提交了 w 此。那么，他的每道题的得分是： 

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF604A/3fb27769d723e1978a19f6c6254058e35687ad16.png)

他的总成绩是他每道题成绩的和。此外，凯文每通过一道题，他的总分数将增加 100 ；反之，他每错误一次，他的总分数将减少 50 分。

所有运算都是觉得准确的，没有四舍五入。凯文的得分绝对是整数。

## 样例 #1

### 输入

```
20 40 60 80 100
0 1 2 3 4
1 0
```

### 输出

```
4900
```

## 样例 #2

### 输入

```
119 119 119 119 119
0 0 0 0 0
10 0
```

### 输出

```
4930
```

# 题解

## 作者：Chtholly_L (赞：4)

这道题我觉得除了模拟，没什么可说的了。

### 题意：

在一场比赛中，共 $5$ 道题，每道题的分数 $x$ 为 $500,1000,1500,2000,2500$ （即每道题的分数是前一道题的分数加 $500$ ）， $m$ 为用时， $w$ 为错误次数。输入每道题的 $m,w$ 、正确题数和错误题数，求出他的总分，总分的计算规则为：$score=\max(0.3x,(1-\frac{m}{250})x-50w)$

---

### 分析：

定义三个数组，分别存每道题的 $m,w$ ，用一个初始分数 $x=500$ ，在每次运算是都加 $500$ ，就可以省去定义五个分数的力气了。

没什么好说的，就是简简单单的模拟，直接上代码。

---

### $AC$ $Code$

```cpp
#include<bits/stdc++.h>
using namespace std;
double m[6];
double w[6];
double s[6];
double ac,wa,x=500,sum;
int main()
{
	for(int i=1;i<=5;i++)
	{
		cin>>m[i];
	}
	for(int i=1;i<=5;i++)
	{
		cin>>w[i];
	}
	cin>>ac>>wa;
	for(int i=1;i<=5;i++)
	{
		s[i]=max(0.3*x,(1-m[i]/250)*x-50*w[i]);
		x+=500;
	}
	for(int i=1;i<=5;i++)
	{
		sum+=s[i];
	}
	cout<<sum+100*ac-50*wa;
	return 0;
}
```


---

## 作者：封禁用户 (赞：4)

题目传送>>[CF604A](https://www.luogu.com.cn/problem/CF604A)  
### 题意简述：  
- Kevin 参加了一场满分分别为 $500,1000,1500,2000,2500$ 的含 $5$ 题比赛，给定其每题的提交时间（$m_1,m_2,m_3,m_4,m_5$）、提交错误次数（$w_1,w_2,w_3,w_4,w_5$）、提交通过的次数、提交未通过的次数，依据评分机制求最终得分。  
- 评分机制:  
每题得分为:  $\max(0.3x,(1-\frac{m}{250})x-50w)$。  
(说明：$x$ 为每题最高分)。  
总成绩是每道题成绩的和，此外，每通过一道题，总分数将增加 $100$ ,反之，每错误一次，总分数将减少 $50$。    

### 题目分析：  
此题题意已经说得足够详细了，无非就是输入数据，按公式计算每道题分数并累加，最后再根据奖罚机制调整最终得分即可。  
#### 唯一需要注意的是：会出现精度损失，我们使用 double 即可。  
### Code:  
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
struct problem{   //利用结构体存数据
	double x;   //每题满分
	double m;   //每题的提交时间
	double w;   //提交错误次数
	double f;   //每题得分
}t[6];
double score=0,ac,uac;   //定义最终得分、提交通过的次数、提交未通过的次数
int main()
{
	//freopen("contest.in","r",stdin);
	//freopen("contest.out","w",stdout);
	ios::sync_with_stdio(0);   //关同步流加速cin输入和cout输出
	for(int i=1;i<=5;i++)
	{
		cin>>t[i].m;
	}
	for(int i=1;i<=5;i++)
	{
		cin>>t[i].w;
	}
	cin>>ac>>uac;
	for(int i=1;i<=5;i++)
	{
		t[i].x=500.0*i;   //计算保存每题满分
	}
	for(int i=1;i<=5;i++)
	{
		t[i].f=max(0.3*t[i].x,(1-t[i].m/250)*t[i].x-50*t[i].w);   //依据公式计算每题得分
		score+=t[i].f;   //累加得分
	}
	score=score+100*ac-50*uac;   //根据奖罚机制调整最终得分
	cout<<score;
	//fclose(stdin);fclose(stdout);
	return 0;   //结束整个程序
}
```
### 结果(未吸氧):  
![JieGuo](https://cdn.luogu.com.cn/upload/image_hosting/euvzs7l6.png)  
企鹅的题解到此结束，祝各位 OIers 进步 ++~

---

## 作者：_Harrisonwhl_ (赞：2)

这道题的算法只有模拟！

这道题可以直接用题目里的公式，顺带打表打出 $x$,直接套用题目公式，就可以做了，具体来说就是循环一下，遍历每场比赛可以为总分数做多少贡献，最后再加上通过总数乘$100$，减去错误总数乘$50$。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
int m[6],w[6],x[6] = {0,500,1000,1500,2000,2500};//打表
double sum = 0;//记得开double
int AC,WA;
int main()
{
    for (int i = 1;i <= 5;i++)
        cin >> m[i];
    for (int i = 1;i <= 5;i++)
        cin >> w[i]; 
    cin >> AC >> WA;
    for (int i = 1;i <= 5;i++)
        sum += max(0.3 * x[i],(1 - m[i] / 250.0) * x[i] - 50 * w[i]);//直接代公式
    cout << sum + 100 * AC - 50 * WA;
    return 0;
}
```

---

## 作者：流绪 (赞：2)

模拟！

这题可以用题目的公式！楼上老哥讲的不对哦。

完全按照题意模拟就好啦，代码的意思注释在代码里了。

下面是 AC 代码。
```cpp
#include<bits/stdc++.h>
#define ll long long 
#define ld long double
#define inf 0x7f7f7f7f
#define maxn 1000010
#define mod 10
using namespace std;
double m[6],w[6],a[6]={0.0,500.0,1000.0,1500.0,2000.0,2500.0};
int main()//初始化每题的分数
{
	ios::sync_with_stdio(false);
	for(int i=1;i<=5;i++)
		cin >> m[i];
	for(int i=1;i<=5;i++)
		cin >> w[i];
	double hs,hu;
	cin >> hs >> hu;//输入
	int ans=0;
	for(int i=1;i<=5;i++)//计算每题真实得分
		a[i] = max((1.0-m[i]/250)*a[i]-50*w[i],0.3*a[i]);
	for(int i=1;i<=5;i++)
		ans += a[i];//计算总分
	ans += (hs*100-50*hu);//加上额外的分数
	cout << ans;
	return 0; 
}  
```


---

## 作者：Nt_Tsumiki (赞：1)

### 题意
[CF60A](https://www.luogu.com.cn/problem/CF604A)

有一个人参加了CF比赛，做了5道题，每道题的得分为 $x_i$，他知道他自己提交题的时间 $m$ 和提交错误的次数 $w$，每道题的得分为 $sum$，计算方式为`max(0.3*x,(1-m/250)*x-50*w)`，他做对了 $t$ 道题，做错了 $f$ 道题，他做对一道题加 $100$ 分，做错一道题减 $50$ 分，现求他的总分。
### 做法
题意直观明了，连重要代码都给了出来，那就很好做了，
首先输入他提交每道题的时间和错误提交数量，算出每一道题的得分 $sum$，然后加入总分，最后再根据提交正确和错误的题目数量计算进总分，然后输出，上代码（无注释）。
### Code
```cpp
#include<iostream>
#define db double

using namespace std;
db x[6]={0,500,1000,1500,2000,2500};
db m[6],w[6],ans;
int t,f;

int main() {
	for (int i=1;i<=5;i++) cin>>m[i];
	for (int i=1;i<=5;i++) cin>>w[i];
	cin>>t>>f;
	for (int i=1;i<=5;i++) {
		int sum=max(0.3*x[i],(1-m[i]/250)*x[i]-50*w[i]);
        ans+=sum;
	}
	ans+=t*100;
	ans-=f*50;
	cout<<ans;
	return 0;
}
```

---

## 作者：Ybocean_s (赞：1)

题意概括：给出凯文的每个问题的提交时间，每个问题上他提交错误的次数，以及它提交正确和错误的总数，按照评分机制，求出最后得分。

------------

大体思路：按照公式进行模拟，把每个数据用对，尤其是正确和错误次数，根据题意进行加分，求出最后总分。

------------

注意:虽然题目中说：“所有运算都是觉得准确的，没有四舍五入。凯文的得分绝对是整数。”
但在计算过程中仍会出现小数情况，造成精度缺失。所以在定义时，需要注意，为了简便，使用了结构体，将每个题的最高分、时间、错误次数放入结构体。

------------

代码为：

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
struct po{
	double m,w,x;//运用结构体。
} a[10001];
int main()
{                    
	int n=5;//一共五道题
	a[1].x=500;a[2].x=1000;a[3].x=1500;a[4].x=2000;a[5].x=2500;//将最高分赋值
	double z,y,ans=0;//正确和错误次数，以及总分。
	for(int i=1;i<=n;i++){
		scanf("%lf",&a[i].m);
	}
	for(int i=1;i<=n;i++){
		scanf("%lf",&a[i].w);
	}
	scanf("%lf%lf",&z,&y);
	for(int i=1;i<=n;i++){
		ans+=max(0.3*a[i].x,(1-(a[i].m/250))*a[i].x-50*a[i].w);//运用公式。
	}
	ans+=z*100;ans-=y*50;//规定加减分。
	printf("%.0lf",ans);//输出。
	return 0;
}
```
撒花。

---

## 作者：zplqwq (赞：1)

# CF604A题解

Hello! 

我们来看一下这道题。

# Section 1 题目

## 题意

共有5道题，每道题的满分分别为 500、1000、1500、2000 和 2500。

若此题的最高分是 x ,提交者在第 m 分钟时提交正确，提交者错误提交了 w 此。那么，他此题的得分是：

![img](https://cdn.luogu.com.cn/upload/vjudge_pic/CF604A/3fb27769d723e1978a19f6c6254058e35687ad16.png)

另外，若他AC一道题总分数就增加100，反之则减少50.

求此提交者能得到的总分。

## 算法

这道题应该就是到~~大~~模拟了吧。

按照题目模拟其实问题就不大呢。

毕竟题目把公式给你了。

那你为何不用呢？

## 坑点

1. **精度** ！！！（具体处理方法见代码）

# Section 2 代码

```c++
#include<bits/stdc++.h>//万能头
using namespace std;
const int N=10000010;
//我爱洛谷
double a[6]={0.0,500.0,1000.0,1500.0,2000.0,2500.0};//打表打法吼啊，好吧其实也不是打表
double w[N],m[N];
int n,k;
int main()
{
	for(int i=1;i<=5;i++)//输入，千万别搞混惹
	{
		cin>>m[i];
	}
	for(int i=1;i<=5;i++)
	{
		cin>>w[i];
	}
	double ans=0;//其实处理精度的方法很简单，都开double就行了（雾
	cin>>n>>k;
	for(int i=1;i<=5;i++)
	{
		a[i]=max(0.3*a[i],(1.0-m[i]/250)*a[i]-50*w[i]);//题目的公式，注意double与1.0
	}
	for(int i=1;i<=5;i++)//算总分
	{
		ans+=a[i];
	}
	ans+=(100*n-50*k);//AC与WA.....
	cout<<ans<<endl;//输出
    return 0;
}

```

~~管理大大求过~~

---

## 作者：WOWHandsome (赞：1)

~~刚刚做完黑题的蒟蒻有点膨胀来发一篇题解~~

此题坑点：精度

动态类型转换，`double` 转 `int`, `long long` 等类型，是有技巧的。我 WA 了 4 次才得出。

1. `printf` 里面尽量直接写变量，不要写复杂表达式。

2. 每一个 `max` 操作都要强制转换

3. 加减法操作单独写 `+=` 或 `-=`，不能直接写表达式。

其他的就是模拟了

C代码 10行

```c
# include <stdio.h>
# define max(a, b) (a > b) ? (a) : (b) //宏定义max
signed main() { double w[5], x[5], m[5]; int sc = 0, ac, wrong; //变量定义
    for (int i = 0; i < 5; i++) scanf("%lf", &m[i]), x[i] = i * 500.0 + 500.0; //输入 m，顺便计算 x[i]
    for (int i = 0; i < 5; i++) scanf("%lf", &w[i]); //输入
    scanf("%d%d", &ac, &wrong);  //还是输入
    for (int i = 0; i < 5; i++) sc += (int)(max(0.3 * x[i], (1.0 - m[i] / 250.00) * x[i] - 50.00 * w[i]) + 0.5); //直接套公式，注意max前用 (int) 强转
    sc += 100 * ac - 50 * wrong;  //算出最终得分，单独写
    return printf("%d\n", sc) & 0;  // printf并返回0
}  //结束
```

---

## 作者：ZJMZJM (赞：1)

大水题

注意：不要直接用题目的公式，会挂精度的
```
#include<iostream>
#include<cstring>
#include<string>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cmath>//头文件
#define For(k,i,j) for(int k=i;k<=j;k++)//for循环
#pragma GCC optimize(4)//O4
using namespace std;
inline int read()
{
    char ch;
    int res=1;
    while((ch=getchar())<'0'||ch>'9') if(ch=='-') res=-1;
    res*=ch-48;
    while((ch=getchar())>='0'&&ch<='9')
        res=res*10+ch-48;
    return res;
}//快读
int m[10],w[10];
int main()
{
    For(i,1,5)
        m[i]=read();
    For(i,1,5)
        w[i]=read();
    int H=read(),IH=read();//输入
    int ans=0;
    For(i,1,5)
        ans+=max((150*i),(250-m[i])*i*2-50*w[i]);//公式（自己推）
    ans+=100*H-50*IH;
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：happybob (赞：0)

这题比较简单，套用公式就好了，不用转int，直接用double算就OK的，677ms，目前第3

代码：

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

double m[10], w[10], score[10];

double AC, WA, ans = 0;

int main()
{
    for(int i = 1; i <= 5; i++)
    {
        score[i] = score[i - 1] + 500;//顺便初始化，第一次因为score[0] = 0，所以 + 500可以得到500的
        cin >> m[i];
    }
    for(int i = 1; i <= 5; i++)
    {
        cin >> w[i];
    }
    cin >> AC >> WA;
    for(int i = 1; i <= 5; i++)
    {
        ans += max(score[i] * 0.3, (1.0 - m[i] / 250) * score[i] - 50 * w[i]);//公式不说
    }
    ans += 100 * AC - 50 * WA;//注意这个
    cout << ans << endl;
    return 0;
}
```


---

