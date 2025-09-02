# Die Roll

## 题目描述

Yakko, Wakko and Dot, world-famous animaniacs, decided to rest from acting in cartoons, and take a leave to travel a bit. Yakko dreamt to go to Pennsylvania, his Motherland and the Motherland of his ancestors. Wakko thought about Tasmania, its beaches, sun and sea. Dot chose Transylvania as the most mysterious and unpredictable place.

But to their great regret, the leave turned to be very short, so it will be enough to visit one of the three above named places. That's why Yakko, as the cleverest, came up with a truly genius idea: let each of the three roll an ordinary six-sided die, and the one with the highest amount of points will be the winner, and will take the other two to the place of his/her dreams.

Yakko thrown a die and got Y points, Wakko — W points. It was Dot's turn. But she didn't hurry. Dot wanted to know for sure what were her chances to visit Transylvania.

It is known that Yakko and Wakko are true gentlemen, that's why if they have the same amount of points with Dot, they will let Dot win.

## 说明/提示

Dot will go to Transylvania, if she is lucky to roll 4, 5 or 6 points.

## 样例 #1

### 输入

```
4 2
```

### 输出

```
1/2
```

# 题解

## 作者：Cambridge (赞：15)


小学生又来发题解了！

~~最近排名下降了，赶紧刷回来~~。言归正传，题意就不讲了，直接讲思路：由于小Y和小W非常绅士，所以如果小D的得分和他们一样，他们也会算作小D获胜。那我们就不是6-maxs,而是6-maxs+1，其中maxs指小Y和小W的得分中的最大值。那么为什么是求最大值呢？因为假设如果小D的得分虽然大于小Y，但是小D的得分并不大于小Y。但是如果小D的得分大于maxs，就说明小D的得分也大于另外一个人，那么小D就获胜了。还有得分一样的情况，那就是判断小D的得分是否等于maxs，所以要用6-maxs+1。

    #include<iostream>
    #include<cstring>
    #include<cstdio>
    #include<cmath>
    #include<string>
    #include<cstdlib>
    #include<algorithm>//文件头不解释 
    using namespace std;
    int y,w;
    int maxs,pd;//定义变量 
    int main()
    {
    cin>>y>>w;//读入小Y和小W的得分 
    maxs=max(y,w);//求最大值 
    pd=6-maxs;//我后面再加1 
    if(pd+1==1)cout<<"1/6";//自行理解 
    if(pd+1==2)cout<<"1/3";//自行理解
    if(pd+1==3)cout<<"1/2";//自行理解
    if(pd+1==4)cout<<"2/3";//自行理解
    if(pd+1==5)cout<<"5/6";//自行理解
    if(pd+1==6)cout<<"1/1";//自行理解
    return 0;
    }

好了，本蒟蒻就讲到这里，希望对读者有所帮助。 


---

## 作者：午尘 (赞：10)

啊啊啊真的好久好久没有颓废啦……

思路：先找最大值，再根据最大值算概率，然后约分后输出~

```cpp
#include <bits/stdc++.h>
using namespace std;
int a,b,n,m,i,j,k,s;
int gcd(int x,int y){ 
 if (y==0)  return  x;
    else return gcd(y,x%y);
}
int main(){
	 cin>>a>>b;
	 k=max(a,b);
	 k=6-k+1;
     n=k;m=6;
     if (gcd(k,6)!=1)
     {
     	n=n/gcd(k,6);
     	m=m/gcd(k,6);
	 }
	cout<<n<<"/"<<m<<endl;
   return 0;
}
```


---

## 作者：lwz2002 (赞：5)

由于小Y和小W很绅士，那么小D也就当仁不让啦。
详解看代码
```
#include<bits/stdc++.h>//万能库不解释

using namespace std;
int main()
{
int n,m;
cin>>n>>m;
int s=max(n,m);/*由于是求小D获胜的概率，所以求出小Y和小W
当中点数最大的，然后拿7（注意是7，而不是6）减去就是小D赢的
点数*/
int ans=7-s;
//前方高能（其实我不想打代码约分了。。）
if(ans==1) cout<<"1/6";
else
if(ans==2) cout<<"1/3";
else
if(ans==3) cout<<"1/2";
else
if(ans==4) cout<<"2/3";
else
if(ans==5) cout<<"5/6";
else
if(ans==6) cout<<"1/1";
//由于小Y和小W的绅士风度，所以小D不可能没有赢的概率
return 0;//完美结束
}
```

---

## 作者：哔哩哔哩 (赞：3)

来一个看着比较简单的思路

题目翻译真的逗

a表示小Y

b表示小W

小D可能性就是总-max

再用2,3进行分解

算出全部的可能性

输出

__PS:别忘特判__

```cpp
#include<cstdio>
int main()
{
    int a,b,yin,e=0,s=0,max;
    scanf("%d%d",&a,&b);
    if(a>b) max=a; else max=b;
    yin=7-max;
    if(yin%2==0) yin/=2,e++;
    if(yin%3==0) yin/=3,s++;
    if(e==0&&s==0) printf("%d/%d",yin,6);
    else printf("%d/%d",yin,6/(e*2+s*3));
    return 0;
} 
```

---

## 作者：蒟蒻取不来名 (赞：3)

$$QwQ$$
你们这群大佬解法有点复杂啊

这题不是打表吗

PS：

1.AT要换行

2.你只需要得分与他们相同就可以赢（小Y和小W非常绅士，如果小D的得分和他们一样，他们也会算作小D获胜），所以其实不存在0/1。

~~3.这题是暴力~~
```
#include<iostream>
using namespace std;
int a, b;
int main()
{
	cin >> a >> b;
	a = max(a, b);//你要与最大值相当才会赢，所以取最大值就OK了
	if(a == 1) cout << "1/1";//当最大值为1时，胜率为100%，即1/1
	if(a == 2) cout << "5/6";//当最大值为2时，胜率为83.333...%，即5/6
	if(a == 3) cout << "2/3";//当最大值为3时，胜率为66.666%，即2/3
	if(a == 4) cout << "1/2";//当最大值为4时，胜率为50%，1/2
	if(a == 5) cout << "1/3";//当最大值为5时，胜率为33.333%，即1/3
	if(a == 6) cout << "1/6";//当最大值为6时，胜率为1.666...%，即1/6
	return 0;
}
```


---

## 作者：ShineEternal (赞：2)

## 题目链接：
https://www.luogu.org/problem/CF9A

## 分析：
这道题是一道简单的概率题。

我们的答案就是：

$\frac{D_{win}}{6}$

- 其中$D_{win}$表示小D获胜的情况。

然后我们观察到了一句话：

> 小Y和小W非常绅士，如果小D的得分和他们一样，他们也会算作小D获胜

也就是说

$ans=\frac{D_{win}+1}{6}$

然后小D只需比其他两人中最大的还要大就行。

∴$D_{win}=6-max(Y,W)$

所以说最后的式子就是

$ans=\frac{6-max(Y,W)+1}{6}$

当然，最后还需要约分一下，除以个gcd就行。

## $code:$

```cpp
#include<cstdio>
#include<iostream>
using namespace std;
int gcd(int x,int y)
{
    if(y==0)return x;
    return gcd(y,x%y);
}
int main()
{
	int x,y;
    scanf("%d%d",&x,&y);
    int ans=max(x,y);
    ans=7-ans;
    int GCD=gcd(6,ans);
    printf("%d/%d",ans/GCD,6/GCD);//上文解释qwq
    return 0;
}
```


---

## 作者：洛谷亿亿岁 (赞：1)

这道题不难

注释详见代码

```
#include<bits/stdc++.h>
using namespace std;
int a,b,ans1=0,ans2=0;//ans1存大于等于的概率ans2存总的概率
int main(){
	cin>>a>>b;
	a=max(a,b);//只要找出小Y，小W中较大的进行比较，因为比较结果取决于大的那个
	for(int i=1;i<=6;i++){//模拟每次骰子显示的数
		if(i>=a)//比他两大
		ans1++,ans2++;//赢了耶
		if(i<a)//比他小
		ans2++;//输了哎
	}
	int x=__gcd(ans1,ans2);//找最大公约数，不是gcd是__gcd
	if(ans1==0){cout<<0<<"/"<<1;return 0;}//如果没有赢的概率是0/1
	else if(ans1==ans2){cout<<1<<"/"<<1;return 0;}//如果每次都赢的概率是1/1
	else cout<<ans1/x<<"/"<<ans2/x//正常输出;
}
```


---

## 作者：君饭否 (赞：0)

因为考虑到约分，所以要写一个gcd（最大公约数）函数，再将分子和分母各除以函数的返回值。
函数代码如下：```

int gcd(int x,int y){
	
    for(int i=x;i>=1;i--){
		if(x%i==0&&y%i==0)
			return i;
}

```
好吧就是这个样子
------------
因为掷出一样的数字也算赢，所以最后的比例为
```
```cpp
(6-max(y,w)+1)/gcd((6-max(y,w)+1),6)<<'/'<<6/gcd((6-max(y,w)+1),6)
```

```
完整代码如下
```cpp
#include<bits/stdc++.h>
using namespace std;
int gcd(int x,int y){
	for(int i=x;i>=1;i--){
		if(x%i==0&&y%i==0)
			return i;
}
}
int main(){
	int y,w;
	cin>>y>>w;
	cout<<(6-max(y,w)+1)/gcd((6-max(y,w)+1),6)<<'/'<<6/gcd((6-max(y,w)+1),6);
}
```
第一篇题解，各位大佬不喜勿喷



---

## 作者：文·和 (赞：0)

### 楼上的大佬这么忙约分，都不想想有最简单的方法吗-----打表

思路很简单，如果两位绅士分数为a和b(a>=b),那么小D最少要获得max(a,b)分

而小D获胜的可能数就是6-小D最少分数+1也就是7-a。而最后的约分嘛.....六个情况手打就行了

贴出代码：

```
#include <bits/stdc++.h>
using namespace std;
int a,b,c; //a开始是输入后来是小D最小分数，b是输入的，c是可能种数
int main(){
cin>>a>>b;
a=max(a,b);  //求出最小分数
c=6-a+1;     //可能种数
if(c==1) cout<<"1/6";
if(c==2) cout<<"1/3";
if(c==3) cout<<"1/2";
if(c==4) cout<<"2/3";
if(c==5) cout<<"5/6";
if(c==6) cout<<"1/1";    //以上为打表
return 0;
}

```

好了，本蒟蒻的题解就到此结束了，求通过QWQ

---

## 作者：反手for循环 (赞：0)

话说小Y和小W非常绅士，如果小D的得分和他们一样，他们也会算作小D获胜，这里的数据也非常友好，没有特别离谱的（像掷骰子掷出7点及以上的点数。）

只要计算小D赢的结果数有多少除去总共结果（6个）即可。

代码中关于二进制gcd的原理：[here](https://www.luogu.org/blog/for1-666/solution-p4057)

AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int i,j,a,b,maxn;
int gcd(int  m,int n){//二进制gcd
    if(m==n)return m;
    if(m<n) return gcd(n,m);
    if(m%2==0){
        if(n%2==0) return 2*gcd(m>>1,n>>1);//位运算">>"，等效于"/"。
        else return gcd(m>>1,n);
    }
    else
    {
    if(n%2==0) return gcd(m,n>>1);
        else return gcd(n,m-n);	
    }
}
int main()
{
	cin>>a>>b;
	maxn=max(a,b);
	cout<<(6-maxn+1)/gcd(6-maxn+1,6)<<'/'<<6/gcd(6-maxn+1,6)<<"\n";//6-maxn+1代表小D能赢的结果数，6是总结果数。
	return 0;//完美结束！
}

```
希望管理员大大能让这份题解过，在此感激不尽。

---

## 作者：由比滨丶雪乃 (赞：0)

## CF9A Die Roll


- [题目链接](https://www.luogu.org/problem/CF9A)  

- [更好的阅读体验](https://www.luogu.org/blog/Hikigaya/cf9a-die-roll-ti-xie)

题意很简单，小D赢的概率为（6-max（小Y的点数，小W的点数）+1）/6（**+1是因为绅士风度qwq**）

**注意约分= =**

Code（~~我知道你们只看这个qwq~~）


```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

int x,y;
inline int gcd(int a,int b)//辗转相除法求gcd
{
	if(b==0) return a;
	return gcd(b,a%b);
}

inline int max(int a,int b)//自定义max函数qwq，快一点
{
	return a>b?a:b;
}

int main()
{
    scanf("%d%d",&x,&y);
    int ans=max(x,y);
    ans=7-ans;
    int Gcd=gcd(6,ans);
    printf("%d/%d",ans/Gcd,6/Gcd);//上文解释qwq
    return 0;
}
```





---

## 作者：Suuon_Kanderu (赞：0)

这才叫真正的打表。

首先是表生成器

这个题思路实际上是，找到小Y和小W中的最大值x，然后用6-x和6约分，但我根本就不知道什么GCD函数。只能用蒟蒻的方法。

```
#include <bits/stdc++.h>
using namespace std;
long long a,b,c,d;
int main()
{    
     for(int a=1;a<=6;a++)//从1到6枚举
           for(int b=1;b<=6;b++)
 {
    c=6-max(a,b)+1;//寻找，6-这个值
    d=6;
    for(int i=2;i<=6;i++)
    while(c%i==0&&d%i==0)//如果能除尽，就使劲往下除
	{
   c/=i;
	 d/=i;	}
	 cout<<'"'<<c<<"/"<<d<<'"'<<","<<endl;
    }
	return 0;
}
```
有人肯定要问了，“ ”是干什么的？

答：要用string数组。

有两个人，需要用两个坐标确定啊

对，用二维string数组！！
（也许相当于char的三维）但高维数组我不会

上代码！！

```
#include <bits/stdc++.h>
using namespace std;
string a[8][8]=
{
{"0",  "0",  "0",  "0",  "0",  "0", "0" },//如果不放0，就输出a[b-1][c-1]
{"0","1/1","5/6","2/3","1/2","1/3","1/6"},
{"0","5/6","5/6","2/3","1/2","1/3","1/6"},
{"0","2/3","2/3","2/3","1/2","1/3","1/6"},
{"0","1/2","1/2","1/2","1/2","1/3","1/6"},
{"0","1/3","1/3","1/3","1/3","1/3","1/6"},
{"0","1/6","1/6","1/6","1/6","1/6","1/6"}

};
int main()
{    
    int b,c;
    cin>>b>>c;
    cout<<a[b][c];
	return 0;
}
```



---

## 作者：TRZ_2007 (赞：0)

## Solution  
这是一道还算可以的数论题，我们让小W的得分与小Y的得分进行对比，取最大值，然后计算即可，注意，最后的结果要约分。
## code
```
#include <bits/stdc++.h>
using namespace std;

int Y,W;

void read(int & x)
{
	int buf = 1;
	char c = getchar();
	if(c == '-') buf = -1;
	while(c<'0' || c>'9') c = getchar();
	while(c>='0' && c<='9')
	{
		x = (x<<3)+(x<<1)+(c^48);
		c = getchar();
	}
	x = x*buf;
}

int main()
{
	read(Y);read(W);
	int now = max(Y,W),N = 6;
	now = N-now+1;
	int Maxgcd = __gcd(N,now);//约分
	printf("%d/%d\n",now/Maxgcd,N/Maxgcd);
}
```

---

## 作者：RioBlu (赞：0)

我的思路：

输入a,b **代表小Y和小W**

又有他俩非常绅士相等也算小D赢所以要加1

于是算出6-max(a,b)+1  **（也可以用for循环从max(a,b)到6）**

最后得到答案但是还要约分！

约分一个分数就是__分子和分母__同时除**分子和分母的最大公约数**

然而C++自带的**__gcd**可以很好的求出两个数的最大值
```
#include<bits/stdc++.h> 
using namespace std;
int a,b,a_max_b,to6;
int main()
{
	cin>>a>>b;
	a_max_b=max(a,b);//求最大值
	for(int s=a_max_b;s<=6;s++)//从max(a,b) 到 6 的整数个数
	{
		to6++;
	}
	cout<<to6/(__gcd(to6,6))<<"/"<<6/(__gcd(to6,6));//用__gcd约分
}
```

---

## 作者：_newbie_ (赞：0)

```c
#include<iostream> //挺简单的一道题
#include<cstdio>
#include<cmath>
using namespace std;
int turn(int a,int b) //递归求最大公约数
{
    int r=a%b;
    if(r==0)
    return b;
    else
    turn(b,r);
}
int main()  
{
     int a,b;cin>>a>>b;
     int c=a>b?a:b;  
     int d=6-c+1;  //获胜几率的分子
     int num; //最大公约数  
     num=turn(d,6);  
     cout<<d/num<<"/"<<6/num; 	    	  
    return 0;
}
```

---

## 作者：览遍千秋 (赞：0)

一道数论题。

很显然，因为两人的绅士风度，不可能出现小D赢不了的情况

所以看看扔到几及以上就可以知道有多少种赢的情况，_gcd_一下就行了

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c;
int gcd(int x,int y)
{
	if(y==0) return x;
	if(x%y==0) return y;
	return gcd(y,x%y);
}
int main()
{
	scanf("%d%d",&a,&b);
	c=max(a,b);
	printf("%d/%d",(6-c+1)/gcd(max(6-c+1,c-1),min(6-c+1,c-1)),6/gcd(max(6-c+1,c-1),min(6-c+1,c-1)));
	return 0;
}
```


---

