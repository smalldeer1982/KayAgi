# Friends Meeting

## 题目描述

在x-坐标轴（可以视为数轴）上有两个人，分别从$a$ 位置和$b$ 位置出发。

对于每个人，他可以往任意方向无限次地移动。当他第$i$ 次移动时，疲乏度增加$i$ 。例如，一个人第$1$ 次移动疲乏度增加$1$ ，第$2$ 次移动疲乏度增加$2$ （累计疲乏度为$3$ ），第$3$ 次移动增加$3$ （累计疲乏度为$6$ ），以此类推。

试求出这两个人在同一点相遇时疲乏度的和的最小值。

## 样例 #1

### 输入

```
3
4
```

### 输出

```
1
```

## 样例 #2

### 输入

```
101
99
```

### 输出

```
2
```

## 样例 #3

### 输入

```
5
10
```

### 输出

```
9
```

# 题解

## 作者：封禁用户 (赞：3)

### 思路
我们设$len$为两人间的距离，则$len=|a-b|$。

分析题目，我们发现，设两人分别移动了$m_a$，$m_b$步，则结果为

$(1+2+...+m_a)+(1+2+...+m_b)$

$=\frac{m_a\times (m_a+1)}{2}+\frac{m_b\times (m_b+1)}{2}$

$=\frac{m_a^2+m_a}{2}+\frac{(len-m_a)\times (len-m_a+1)}{2}$

$=\frac{m_a^2+m_a+len^2-m_alen+len-m_alen+m_a^2-m_a}{2}$

$=\frac{2m_a^2-2m_alen+len^2+len}{2}$

$=m_a^2-m_alen+\frac{len^2}{2}+\frac{len}{2}$

$=(m_a-\frac{len}{2})^2+\frac{len^2}{4}+\frac{len}{2}$

$\geq \frac{len^2}{4}+\frac{len}{2}$.

至此，我们完成了证明当$m_a=\frac{len}{2}$时结果最小。

然而$len$不一定是偶数，$m_a$又必须是整数，所以我们令$m_a=\lfloor\frac{len}{2}\rfloor$，$m_b=len-\lfloor\frac{len}{2}\rfloor$即可。

如何计算答案？

1. 你可以计算出$m_a$和$m_b$，然后计算$\frac{m_a\times (m_a+1)}{2}+\frac{m_b\times (m_b+1)}{2}$

2. 也可以只计算出$m_a$，并计算$(m_a-\frac{len}{2})^2+\frac{len^2+2len}{4}$

### 代码

使用方法1计算答案。

```c
main(){
    int a,b;
    scanf("%d %d",&a,&b);
    int len=a-b;
    if(len<0)len=-len;//取绝对值
    int ma=len>>1,mb=len-ma;//分别表示a和b移动的总量
    printf("%d\n",(ma*(ma+1)>>1)+(mb*(mb+1)>>1));//等差数列求和
}
```

### 题外话

其实你也可以[模拟](https://yuzhechuan.blog.luogu.org/solution-cf931a)……

---

## 作者：666yuchen (赞：2)

二话不说，上代码。（详情请看注释）
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>//文件头
using namespace std;
int a,b,mid,c,d;
//定义变量
int main()
{
  cin>>a>>b;
  //输入两个朋友的位置
  mid=(a+b)/2;
  //求中间值（这样他们的疲劳值是最小的）
  c=abs(a-mid);
  d=abs(b-mid);
  //算出他们的位置与中间值相差多少
  c=(1+c)*c/2;
  d=(1+d)*d/2;
  //等差数列求和
  cout<<c+d;
  //输出最小的疲劳
  return 0;
}
//程序拜拜
```
### 为了营造美好的洛谷，请不要抄袭!!!

---

## 作者：梦里调音 (赞：2)

**最通俗易懂的题解！！！**（求管理员大大放过）

思路很简单： _取中点_ ！！！

注意等差数列公式：（首项+尾项）*项数/2 //
~~这么简单我都不想说了~~

奉上代码~~
```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
	int i,j,k,a,b,mid,al,bl,ap,bp;
	cin>>a>>b;//输入
	if(a>b)swap(a,b);//注意顺序，a小b大
	mid=(a+b)/2;//敲黑板：取中点了！！！
	al=mid-a;//al为a要走的路程
	bl=b-mid;//bl为b要走的路程
	ap=(al+1)*al/2;//ap为a的疲劳度，利用等差数列公式（等差为1）
	bp=(bl+1)*bl/2;//bp为b的疲劳度
	cout<<ap+bp<<endl;//输出疲劳度的和
}
```

---

## 作者：sxtm12138 (赞：1)

设两人间的距离为l，相信大家都已经知道当两人分别走过l/2(或
l/2+1)时疲乏值总和最小，那我就直接拿来用了。设l=2n+1(设i为
奇数)，疲乏值总和=**(1+…n)+(1+…
n+1)=n(1+n)/2+n(1+n)/2+n+1=(n+1)^2=(l/2+1)(l/2+1)**；设i=2n(设i为偶数)，疲乏值总和=**(1+…n)+(1+…
n)=n(n+1)=(l/2)(l/2+1)**;
综上所述，我们将两式合并为:

## ((l+1)/2)*(l/2+1)
 _（注：l为偶数时(l+1)/2=l/2,l为奇数时(l+1)/2=l/2+1,故可以合并）_ 

 _以下为代码：（无敌精简版）_ 

------------

```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
int main()
{int m,n;//m、n间的距离可用abs(m-n)表示
 cin>>n>>m;//读入两个人的位置
 cout<<((abs(m-n)+1)/2)*(abs(m-n)/2+1);//套用上面的公式
 //本来想用三目运算符的，为了精简就改用了abs取绝对值
 return 0;	 
}

```

---

## 作者：第二小题 (赞：0)

## 前言
一看到这个题就直接上手去做了，懒的去动脑子了，用了一种最笨最直接的方法，~~呜呜呜我弱啊~~。
###### [AC记录](https://www.luogu.com.cn/record/38078533)
## 思路
题目要求我们相遇时疲乏度和的最小值，一个人的每次移动的疲乏度可以组成一个公差是1的等差数列。等差数列越加越大，所以我们得让他的末项也就是走的步数尽量与另外一个人平均，才能使疲乏度尽可能的小。

还有一点需要注意，求距离时需要用到绝对值abs去求。
## 代码
```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
long long a,b,k,t,ans;//t记录总的距离，k记录其中一个人要走的距离，ans记录疲乏度 
int main()
{
	cin>>a>>b;
	t=abs(a-b);//求出总路程 
	k=abs(a-b)/2;//求出较为平均的步数 
	for(int i=1;i<=k;i++) ans+=i;//求疲乏度 
	for(int i=1;i<=t-k;i++) ans+=i;//求另一个人的疲乏度 
	cout<<ans;
	return 0;
}

```


---

## 作者：Pkixzx (赞：0)

其实这就是道贪心的题目。

看到题目我就想到先要求这两个点的**中位数**。求出中位数后，我们就分别讨论中位数的奇偶情况。

如果中位数是个奇数，那么有一个人需要多行一步，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/7tt43qra.png)

5走到8这个点，12走到10这个点时，必须有一个点要多走，我选择让五多走一步，所以总和为1*2+2*2+3*2+4*1=16，此时最优。

如果中位数是个偶数，那么没有人要多走一步，刚刚好平均分配，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/e2lo6mg8.png)

刚好没有剩余，所以5到11的总和为1*2+2*2+3*2=12，此时最优。

那么我们就很好写代码了，代码如下：
```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	long long n,m,t=0;
	cin>>n>>m;
	if(abs(n-m)%2==1)//处理如果是奇数的情况
	{
		for(int i=1;i<=abs(n-m)/2+1;i++)
		{
			t+=i;
			if(i!=abs(n-m)/2+1)//最后一步只让一个人走了
			t+=i;
		}
		
	}
	else
	{
		for(int i=1;i<=abs(n-m)/2;i++)
		t+=i*2;
	}
	cout<<t;
}

```


---

## 作者：FR_qwq (赞：0)

这题，我们珂以这么做：先求出这两个数的平均值（这样的话答案会最小），然后把两个数与平均值的距离求出，算出两人对应的疲乏度，最后相加，$\color{green}\texttt{AC}$。

Code：
```pascal
var n,m:longint;//定义
function qwq(x:longint):longint;//函数
begin
n:=abs(n-x);m:=abs(m-x);//求出与平均值的距离
qwq:=(1+n)*n div 2+(1+m)*m div 2;//求出 n 和 m 等差数列并加和
end;
begin
readln(n,m);//读入
writeln(qwq((n+m)shr 1));//输出（注：这里的“shr 1”等同于 “div 2”，写成这样是为了让速度快些）
end.//完美结束
```
C 党看这：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstdlib>//头文件
using namespace std;
int n,m;//定义
int abs(int x) {
    if(x<0)return -x;
    return x;
}//因为我没有引进有 abs 函数的库，所以窝只能手打/kk
int qwq(int x) {
    n=abs(n-x);
    m=abs(m-x);//求距离
    return (1+n)*n/2+(1+m)*m/2;//求 n，m 的等差数列并加和
}
int main() {
    scanf("%d%d",&n,&m);//输入
    printf("%d\n",qwq((n+m)>>1));//输出（注：这里的“>>1”相当于“/2”，写成这样是问了让速度更快些）
    return 0;//完美结束
}
```
$\ $

$\ $

$\ $

$\ $

__没了__

---

## 作者：Level_Down (赞：0)

### 题意简述：

给定两人在数轴上的位置，他们能移动无数次，但每一次的运动都会增加当前运动次数的疲劳值，求两人相遇时最小的疲劳值总和。

### 方法：

这道题之前的题解基本上都是取中点做，但是这两个人每次都只能走1个单位，所以怎么都没人从移动次数入手啊？

从移动次数入手，就是要使两人的移动次数尽可能相同，所以我们可以用一个循环，每次每次让这两个人各走一次（但前提是这两个人不相遇），相遇之后退出循环，输出ans的值。

就像这样：

```cpp
while (t > 0)//t是两人的距离。
		{
			if (t > 0) {ans += x,t -= 1,x++;}//x和y分别是这两个人的运动次数，或者说是当前疲劳度的累加值。
			if (t > 0) {ans += y,t -= 1,y++;}
		}
```

这方法很容易理解吧，AC代码（14行）：

```cpp
#include <bits/stdc++.h>
using namespace std;
int a,b,t,x = 1,y = 1,ans;//a和b就是两人的起始位置。
int main()
{
	cin >> a >> b;
	t = abs(a - b);//计算两人的距离。
	while (t > 0){//这段上面讲过了。
			if (t > 0) {ans += x,t -= 1,x++;}
			if (t > 0) {ans += y,t -= 1,y++;}
		}
	cout << ans << endl;
	return 0;//AC！！！ 	
}
```


---

## 作者：Mikemao666 (赞：0)

题目：[Here](https://www.luogu.com.cn/problem/CF931A)

看到这道题的第一感觉：水！

思路就是直接模拟but……

**注意** 
题目要求是两人劳累值和要最小，说明：

- 在两人距离为复数时，两人的步数一样，劳累值也一样。
- 但如果是奇数，就要考虑最后一次时只有一个人走过，也就是只累加一次劳累值的情况。

**code**

```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,tired;
int main (){
    cin>>a>>b;
    int c=abs(a-b);//取两人之间的距离
    for(int i=1;/*让循环一直下去~*/;++i){
        c--;//先模拟a走
        tired+=i;//累加劳累值
        if(c==0){//如果已经到了
            cout<<tired;
            break;//return 0;
        }
        c--;//模拟b走
        tired+=i;//同上
        if(c==0){//如果已经到了
            cout<<tired;
            break;//return 0;
        }
    }
	return 0;
}
```
还有，每次累加完都要判断，不然你会蜜汁TLE

---
在一开始没有发现TLE的原因，于是我想了另一种方法：
$Mathe!$

不难发现，在距离为复数时，劳累值为两个从$1-c/2$的等差数列~~不会LATEX~~。

化简得

```cpp
(1+c/2)*(c/2)
```
同理，当距离为单数是，可以化为一个$1…(c+1)/2$的等差数列和一个$1…[c-(c+1)/2]$的等差数列。

化简得
```cpp
(c+1)*(c+1)/4
```
完结撒世纪末彼岸花❀~


---

## 作者：chenpengda (赞：0)

使用贪心法，不妨设a的位置在b的位置的左边：

①如果他们在a的左边或者b的右边相遇，那么比起在a点或b点相遇，**两个人走的路程肯定会更多**，那么不符合题意“疲乏度最小”。

②一定在中点。因为如果不在中点，那么假设在中点的右边一格，**虽然b少走了一步，但是比a多走一步增加的疲乏度要小**（因为a已经走了一半的路程了），也就是不划算。

因此，相遇点在中点，只需要$(b-a)/2$即可，如果b-a为奇数也没关系，中间两个点里面随便取一个就可以了。

还有一个细节，如果a在b的右边，需要$swap(a,b)$，这个函数的功能是交换两个变量的值。

计算出终点之后就可以计算出a和b各自需要走的路程，等差数列相加即可，这里为了简单使用了一个函数dcsl。

```cpp
#include<bits/stdc++.h>
using namespace std;
int dcsl(int k)
{
	int ans=0;
	for(int i=1;i<=k;i++)ans+=i;
	return ans;
}
int main()
{
	int a,b,sum=0;
	cin>>a>>b;
	if(a<b)swap(a,b);
	int midplace=b+(a-b)/2;
	sum+=dcsl(a-midplace);
	sum+=dcsl(midplace-b);
	cout<<sum;
	return 0;
}
```


---

## 作者：hensier (赞：0)

我们先来分析一下题目。~~我们可以很容易地注意到：~~ 这道题需要**分类讨论**。我们设两人坐标分别为$A,B$。设$|A-B|=k$，在$A$位置的人需要移动$d_A$的距离，在$B$位置的人要移动$d_B$的距离，总距离为$d_S$，疲劳总值为$P$。

无论$k$的奇偶性如何，两人需要到达的位置都应该是$\lceil \frac{A+B}{2} \rceil$。

即：

$d_S=d_A+d_B$

$=2d_A$

$=2|k-A|$

$=2|\lceil \frac{A+B}{2} \rceil-A|$

$=2|\lceil \frac{A-B}{2} \rceil|$

当$k$为偶数时，$\lceil \frac{A-B}{2} \rceil=\frac{A-B}{2}$。因此：

$$P=2\sum_{i=1}^k i$$

当$k$为奇数时，$\lceil \frac{A-B}{2} \rceil=\frac{A-B-1}{2}$。因此：

$$P=2\sum_{i=1}^k i+k+1$$

根据上述分析，我们可以得到$AC$代码：

```cpp
#include<cstdio>
int a,b,k;
int main()
{
    scanf("%d%d",&a,&b);
    if(a<b)//等同于swap(a,b);，但是没有头文件
    {
        k=a;
        a=b;
        b=k;
    }
    k=(a-b)/2;
    if((a-b)&1)printf("%d",(1+k)*k+k+1);//n&1返回是否为奇数，位运算更快
    else printf("%d",(1+k)*k);
}
```

---

## 作者：yuzhechuan (赞：0)

## 模拟

| 距离 |0| 1 | 2 | 3 | 4 | 5 | 6 |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| 体力 | 0|1 | 2 | 4 | 6 | 9 | 12 |
| 差值 |0|1|1|2|2|3| 3|


------------


```cpp
#include <bits/stdc++.h>//一个万能库
using namespace std;

int ans,x,y;

int main()
{
	ios::sync_with_stdio(false);//输入输出加速
	cin>>x>>y;//读入
	x=abs(x-y);//得出二人的距离，abs为取绝对值函数
	for(int i=1;i<=x;i++)
		ans+=i/2+i%2;//唯一的优化。。。
        			 //分析后不难得出走第n步时，需耗费n/2+n%2点体力
	cout<<ans;//输出
}
```

---

