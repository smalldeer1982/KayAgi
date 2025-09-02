# Pineapple Incident

## 题目描述

Ted有一个菠萝。这个菠萝可以像狗一样叫！在第 $t$ 秒它第一次叫。然后每隔 $s$ 秒之后它会叫一次，在叫这一次之后还会在后一秒再叫一次。意思就是说它会在 $t$ 秒，$t+s$ 秒，$t+s+1$ 秒，$t+2s$ 秒，$t+2s+1$ 秒分别叫一次，以此类推。 

Barney在早上醒来，他想吃个菠萝，但这只菠萝叫的时候Barney不能吃它。Barney打算在 $x$ 秒吃它，所以请你告诉Barney在x秒的时候，这个菠萝会不会叫。

## 样例 #1

### 输入

```
3 10 4
```

### 输出

```
NO
```

## 样例 #2

### 输入

```
3 10 3
```

### 输出

```
YES
```

## 样例 #3

### 输入

```
3 8 51
```

### 输出

```
YES
```

## 样例 #4

### 输入

```
3 8 52
```

### 输出

```
YES
```

# 题解

## 作者：lnkkerst (赞：38)

这是一道水题，不要被省选难度给骗了。方法很简单，一个判断语句即可。

因为“菠萝”从t秒开始每隔s秒叫一次，叫这一次之后还会在后一秒再叫一次，所以当x减去t再对s取模的值为0或1时“菠萝”就会叫。
```cpp
#include <cstdio>

int main() {
	int t, s, x;
	scanf("%d%d%d", &t, &s, &x); //读入
	int tmp = x - t;
	if ((tmp % s == 0 || tmp % s == 1) && tmp >= 0 && tmp != 1) //判断x秒时菠萝是否会叫
		printf("YES");
	else
		printf("NO");
	return 0;
}
```
这里要注意的是，当x-t=1时答案为“NO”，即t+1秒时“菠萝”并不会叫（翻译给错了）， 所以要加上判定。

蒟蒻第一次写代码，请多多包涵。如有错误请指出(￣▽￣)~*

---

## 作者：NOILinux_Ubuntu (赞：26)

### 我们需要分析在什么时候会叫，事实上并没有想象中的那么简单。

首先，如果我们在它第一次叫之前就把它吃了，我们一定是输出"NO"

其次，我们再对题意进行**分析**

我们发现题目只给了三个值，所以我们需要充分利用这三个值。

那么，这三个值有什么意义呢？

首先我们考虑**枚举**菠萝叫的时间，为
	$$t+1,\ t+s,\ t+s+1,\ t+2s,\ ...\ ...$$

在提交了一次代码后，我们发现这样枚举是会超时的

所以我们要**优化**我们的算法，考虑题目要让我们求的其实就是$x=k*s+t$或$x=k*s+1$ $\ \ \ 0\le k < +\infty$

那么新的算法就出来了，枚举k！

但是上面的算法会被下面的数据卡掉

>5 1 1000000000

所以算法需要**继续优化**

然后我们要**化开第一个式子**
	$$x=k*s+t$$
    $$x-t=k*s+t-t$$
    $$x-t=k*s$$

同理第二个式子
	$$x=k*s+t+1$$
    $$x-1=k*s+t+1-1$$
    $$x-t-1=k*s+t-t$$
    $$x-t-1=k*s$$
    
当式子化成上面的样子之后，我们的问题基本上就解决了

学过取模的同学一定都知道，$a=b*c\ \ \leftrightarrow\ \ a\%c=0$

所以我们就可以把枚举k的步骤去掉，考虑直接求取模后是否等于零

然而把代码敲完后，我们发现自己连样例都过不了，为什么呢？

这就是这道题最难的地方，我们需要有足够的英文水平**略过翻译**，看到原题中的菠萝并不会在第t+1秒叫，才能通过此题。

>综上，此题将枚举，优化，数论，翻译四种算法巧妙结合在一起，无疑是善良的出题人无私的馈赠，大量精心结合的算法，涵盖了OI中绝大多数的题目组合。你可以利用这道题，对自己的知识点进行全面的盘查，让你脑海中的漏洞无处遁形。我相信，这道美妙的题目，可以给拼搏于进入国家集训队的逐梦之路上的你，提供一个有力的援助。

其实这道题还可以用**查看讨论法**通过此题，在这里就不一一介绍了

```cpp
#include<cstdio>
using namespace std;
int t,s,x;
int main(){
	scanf("%d%d%d",&t,&s,&x);
	if(x<t){puts("NO");return 0;}
	if((!((x-t)%s)||!((x-t-1)%s))&&x!=t+1)puts("YES");
	else puts("NO");
 return 0;
}
```

---

## 作者：棒棒糖是猪 (赞：9)

## ********这到题明显黑题难度呀，紫题真的过分了（hhhhhhh）********
第一次发题解（还是紫题，**真开心**）

------------

```cpp
#include<iostream>
#define pink using namespace
#define is std
#define a ;
#define pretty int main(){
#define girl int t,s,x;
#define who cin>>t>>s>>x;
#define I if
#define will (((x-t)%s==0||(x-t-1)%s==0)&&x-t!=1&&x-t>=0)
#define love cout<<"YES"a
#define ever else cout<<"NO"a
#define till return 0
#define forever a}
pink is a pretty girl who I will love ever till forever


------------

```
#### **（pink 是一个我会爱到天长地久的姑娘）**
我心已死，特此纪念。

---

## 作者：留守新手村 (赞：8)

思路：

首先，假设菠萝从时间0开始叫，则想要吃的时间变为x-t。

然后，菠萝叫的时间变为0,s,s+1,2s,2s+1.

就可以得到下面的极简代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int t,s,x;
    scanf("%d%d%d",&t,&s,&x);
    x-=t;
    if(x < s && x != 0) printf("NO");//当吃的时间小于叫的间隔时，只有时间0才会叫
    else if(x % s == 0 || x % s == 1) printf("YES");//若吃的时间大于叫的间隔，当吃的时间取余叫的间隔等于0或1时，在吃的时间菠萝会叫
    else printf("NO");//当吃的时间取余叫的间隔不等于0或1时，在吃的时间菠萝不会叫
}
```

---

## 作者：Michigan_King (赞：4)

### 为什么大家的题解我都看不懂啊，我认为此题还有更简洁易懂的做法呢。
---------------
我认为可以在一个while循环中查验两次，满足其中之一就可以输出“YES”，然后就可以跳出循环。否则在循环外输出“NO"。

--------
#### 附代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int t,s,x;
int t1,t2;
int main()
{
	cin>>t>>s>>x;
	while(t<=x)
	{
		if(t==x)
		{
			cout<<"YES"<<endl;
			return 0;
		}
		t+=s;
		if(t+1==x)
		{
			cout<<"YES"<<endl;
			return 0;
		}
	}
	cout<<"NO"<<endl;
}
```
十分简洁易懂不是吗？
  

---

## 作者：NCC79601 (赞：3)

这就一道初级题目，居然标的NOI难度…我闷着头用模拟水了一发，居然就过了！第一次遇到这种不卡暴力的题。从起点开始循环就可以了。需要注意的是在起始时间是叫了一次的，而后在t到t+s秒是不会再叫的，读题没读好的话可能就以为t+1秒的时候也会叫，然后某些数据点就gg了。吐槽一下数据点，我全都是0msAC，不知道给的是多良心的数据。
```cpp
#include<bits/stdc++.h>
using namespace std;

int x, t, s;

int main() {
	scanf("%d%d%d", &t, &s, &x); 
	if(x == t) {
		cout << "YES";
		return 0;
	} //特判一下第一段情况
	int wolf1 = t + s;
	int wolf2 = t + s + 1; //从第二段开始循环
	while(wolf1 <= x) { //闷着头皮while，不要管那么多
		if(x == wolf1 || x == wolf2) {
			cout << "YES";
			return 0;
		} //两个情况，满足其中一种直接结束程序
		wolf1 += s;
		wolf2 += s;
	}
	cout << "NO";
	return 0;
}

```

---

## 作者：Zofia (赞：2)

会叫的菠萝？太牛逼了！
来看看题解吧！
我们以s秒叫一次为正常叫，s+1秒叫为非正常叫；

```cpp
#include<bits/stdc++.h>
using namespace std;
//标准开头♂；
int t,s,x,r;
//定义t为初始时间，s为正常叫的间隔，x为吃菠萝的时间，r为非正常叫的时间；
int main(){
	cin>>t>>s>>x;//输入；
	int num=0;//定义num表示是否叫；
	while(t<=x){//一直循环到超过x为止；
	    if(t==x||r==x){
		cout<<"YES"<<endl;//如果要叫，输出“YES”
	   	num++;//记号变为1；
		break;//跳出循环；
		}
		t+=s;//每次循环t增加s秒；
		r=t+1;//r比t多1秒；
	}
	if(num==0) cout<<"NO"<<endl;如果不叫（记号没变），输出“NO”；
	return 0;
}
```

这道题其实简单的一批，不要被他们刷出来的难度所欺骗，相信你自己，Ass♂we♂can♂。

---

## 作者：shenmadongdong (赞：1)

### 首先，题目翻译有误，t+1秒时是不会叫的！
~~既然没有Pascal的题解，那本蒟蒻来水一发~~

若x<t或x=t+1则不可能，否则若x-t模s余0或1则可能

代码：
```
var t,s,x:longint;
begin
  read(t,s,x);
  if x<t then writeln('NO')
  else if x=t+1 then writeln('NO')//特判
  else if ((x-t) mod s=0)or((x-t) mod s=1) then writeln('YES') else writeln('NO');//判断x-t模s是否余0或1
end.
```

---

## 作者：wpj20241021005 (赞：0)

这一道题总的来说是一道水题，很多大佬过不去，是因为翻译的原因。在这里声明一下，**t+1输出是“NO”！！！不是“YES”**，所以，为了避免这种情况，我们需要特判一下。只要注意到了这个槽点，这题也不是很难的。

这道题说的是t+ns||t+ns+1会叫，判断第X时会不会，我不禁想到了小学时学到的除法，所以呢，如果（x-t）%s==0||（x-t-1）%s==0时，那就是它叫的时候了（虽然我也不知道它为什么会叫），还要注意到的是，**题目上没有说x一定会>t**，所以我们还是要判断一下的（我就被坑了QAQ），下面就是我的代码

```
#include<bits/stdc++.h>
using namespace std;
long long a,b,c;//int 应该也够，为了以防万一，所以选择long long
int main(){
	cin>>a>>b>>c;//输入，a就是t，b就是s，c就是x
	if((c-a)%b==0){//判断
		cout<<"YES";
		return 0;
	}
	if((c-a-1)%b==0&&c-a!=1&&c-a>=0){//判断++
		cout<<"YES";
		return 0;
	}
	cout<<"NO";//如果不满足以上所有条件，输出“NO!!”
}
```


---

## 作者：赤霞QvQ (赞：0)

# 这道题翻译有问题！！！
#### 菠萝在第$t+1$秒是不会叫的！！！！！！！！！！！！
那么我们可以分$4$类讨论：

$1$.如果$x=t+1$，输出$NO$

$2$.如果$x<t$，输出$NO$

$3$.如果前两类都不是且$x-t≡0$或$1(mod$ $s)$，输出$YES$

$4$.如果前三类都不是，输出$NO$

![](https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1561006368760&di=a0b3755ab01e3cb348beacece8467dd6&imgtype=0&src=http%3A%2F%2Fmmbiz.qpic.cn%2Fmmbiz_jpg%2FhG4MhP4N1UFk5k53FB73zZ4psiaY2ic5I0u63bKbhjLnYrqbRgEVYy8zDSWT34oykSTzLibYKpecPa9pTw9iaOKSiag%2F640%3Fwx_fmt%3Djpeg)

上代码！！！（会叫的菠萝过度牛逼）

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,s,x;
int main()
{
	cin>>t>>s>>x;
	if(x==t+1||x<t)    //第1类&第2类
	{
		cout<<"NO"<<endl;
		return 0;     //随手return是好习惯！！！
	}
	if((x-t)%s==0||(x-t)%s==1)      //第3类
	{
		cout<<"YES"<<endl;
		return 0;     //随手return是好习惯！！！
	}
	cout<<"NO"<<endl;    //第4类
	return 0;
}
```

$QED$！！！！

---

## 作者：雪鸮 (赞：0)

不会用latex，还望各位见谅

做法似乎看起来和别的大佬的不大一样，但好像本质是一样的？

开讲。

题目给出了t,t+1,t+s,t+s+1,t+2s,t+2s+1···t+ks,t+ks+1(k∈N*)这样一个数列，我们把它据+1或者没有+1（奇数或偶数）分为两个数列：

**{an}**：an=t+ns
**{bn}**：bn=t+ns+1

显然，如果x时刻菠萝会叫，x**必然属于{an}、{bn}之一**

之后就是枚举了。

但是题目的数据范围那么大，一路枚举到1e9肯定超时，所以我们需要一些优化。

很容易看出，~~因为ted没有储存粮食的习惯~~，x时刻以后的任何时刻都对答案无意义，所以枚举到x/s+1即可。为什么+1呢？大概防止翻车咯~~~我倒确实不知道为什么+1反正过了就好了~~

弄完这些，还要注意一个特判，就是在t时刻如果菠萝叫了ted也是吃不了菠萝的，所以如果t=x就直接输出YES。

下面上代码

```cpp
#include<iostream>
using namespace std;
int t,s,x;
int main()
{
	cin>>t>>s>>x;
	if(x==t)   //特判
	{
		cout<<"YES";
		return 0;
	}
	for(int i=1;i<=x/s+1;i++)   //枚举部分
	{
		if(x==t+s*i||x==t+s*i+1)  //属于{an}或{bn}中的任何一个
		{
			cout<<"YES";
			return 0;
		}
	}
	cout<<"NO";
	return 0;
}
```

~~我这好像是全场跑得最慢的代码~~

---

## 作者：我是一个蒟蒻 (赞：0)

# 翻译有问题，菠萝在t+1秒不会叫！
## 伪代码：
```
输入;
判断;
循环
{
	t+=s;//t+s
	判断;
	t+=1;//t+s+1
	判断;
	t=t-1+s;//t+2s
	判断;
	t+=1;//t+2s+1
	判断;
	t-=1;
}
```
# 上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int t,s,x;
    scanf("%d%d%d",&t,&s,&x);
    if(x==t)
    {
        printf("YES");
        return 0;
    }//判断，如果x等于菠萝第一次叫的时间,就说明菠萝会叫
    if(x<t)
    {
        printf("NO");
        return 0;
    }//判断，如果x小于菠萝第一次叫的时间,就说明菠萝不会叫
    if(x>t)
    {
        while(t<x)
        {
            t=t+s;//t+s
            if(x<t)
            {
                printf("NO");
                return 0;
            }
            if(x==t)
            {
                printf("YES");
                return 0;
            }
            t=t+1;//t+s+1
            if(x<t)
            {
                printf("NO");
                return 0;
            }
            if(x==t)
            {
                printf("YES");
                return 0;
            }
            t=t-1;//减掉多余的1
            t=t+s;//t+2s
            if(x<t)
            {
                printf("NO");
                return 0;
            }
            if(x==t)
            {
                printf("YES");
                return 0;
            }
            t=t+1;//t+2s+1
            if(x<t)
            {
                printf("NO");
                return 0;
            }
            if(x==t)
            {
                printf("YES");
                return 0;
            }
            t=t-1;//减掉多余的1
        }
        if(x<t)
        {
            printf("NO");
            return 0;
        }
        if(x==t)
        {
            printf("YES");
            return 0;
        }
    }
    return 0;
}
```

---

## 作者：_Error (赞：0)

首先，我想问一下，这题。。。。。真的是紫题吗？？？这题模拟一下好像就可以了吧。。。但是（果然凡事都有但是），不要看翻译里的“意思就是说它会在t+1秒”这句话（半句），because这翻译错了，所以说还是看原文好，原文是“ t , t+s ,t+s+1”，按着这个来就可以了。
蒟蒻代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,x;
string gc(){
	int k=1;
	int y=0;
	if (n==x) return "YES";  //判断一开始是否就和菠萝叫的时间相等
	while (y<=x){
		y=n+m*k;  //模拟菠萝叫的时间
		if (y==x) return "YES"; //相等就输出YES
		y++;  //再把t+s+1的时间记下来
		if (y==x) return "YES";  //相等就输出YES
		k++; //s乘的倍数，满足s,2s,3s......
	}
	return "NO";
}
int main(){
	cin>>n>>m>>x;
	cout<<gc();
	return 0;
}
```

---

