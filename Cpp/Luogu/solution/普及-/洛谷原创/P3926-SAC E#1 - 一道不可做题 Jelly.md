# SAC E#1 - 一道不可做题 Jelly

## 题目背景

SOL君（炉石主播）和SOL菌（完美信息教室讲师）是好朋友。


## 题目描述

SOL君很喜欢吃蒟蒻果冻。而SOL菌也很喜欢蒟蒻果冻。

有一天，他们在一起搓炉石，而SOL菌则要拿出蒟蒻果冻招待他的客人。

蒟蒻果冻一般在a度下保存在冰箱里。但是刚拿出来的时候太冰了，需要加热。SOL菌打算用一种神奇的电炉加热蒟蒻果冻。根据观察，它有一个特点：

1、蒟蒻果冻小于c度的时候，每p单位时间加热1单位温度；

2、当蒟蒻果冻等于c度的时候，需要q单位时间解冻（大家都知道，晶体物态变化温度不变……SOL君认为果冻属于晶体）；

3、当蒟蒻果冻解冻完成之后，每r单位时间加热1单位温度。


SOL想知道，将果冻加热x单位时间的时候果冻的温度。

温度向下取整，也就是说，如果加热结束时不足p（或q）单位时间，则认为在这最后一小段时间内果冻温度没有任何变化。


## 说明/提示

对于 $30\%$ 的数据，$|a|, |c| \leq 200, x \leq 100$。

对于 $60\%$ 的数据，$|a|, |c| \leq 2 \times 10^9, x \leq 100$。

对于 $100\%$ 的数据，$|a|, |c| \leq 2 \times 10^9, 1 \leq x, p, q, r \leq 10^9$。

数据中可能有 $a = c$，此时算还未解冻的状态。


提示：请使用long long数据类型。


## 样例 #1

### 输入

```
-10 0 2 1 3 26
```

### 输出

```
1```

## 样例 #2

### 输入

```
-10 0 2 1 3 27```

### 输出

```
2```

# 题解

## 作者：kkksc03 (赞：141)

如果 a > c，答案是 a+⌊x r⌋。

如果 a = c，有两种情况： 如果 x≤q，答案是 c。 如果 x > q，答案是 c+⌊(x−q) / r ⌋。

如果 a < c，有三种情况： 如果 x≤ (c−a)p，答案是 a+⌊x /p⌋。 如果 (c−a)p≤x≤ (c−a)p+q，答案是 c

如果 x > (c−a)p+q，答案是 c+⌊(x−(c−a)p−q) / r ⌋


---

## 作者：Raw_Aya9285 (赞：30)

# 跪-超级蒟蒻的第四条题解！
我两遍过的这道题（我才不会告诉你们我想了半小时才有思路）

下面开始分析：（我的代码有点绕，慎看，主要看分析）


------------
### step 1 定义&输入
```cpp
long long a,c,p,q,r,x,temp=0;//temp是最终温度
    cin>>a>>c>>p>>q>>r>>x;//输入
```
这部分注意long long，然后一个一个定义就好啦


------------
### step 2 若a小于c

第一种情况就是从冰箱里拿出来时的温度小于解冻温度啦！
```cpp
if(a<c){
        if((c-a)*p>=x){
            cout<<a+(x/p)<<endl;
            return 0;
        }else{
            x-=(c-a)*p;
            temp=c;//x=6,temp=0
            if(q>=x){
                cout<<temp<<endl;
                return 0;
            }else{
                x-=q;//x=5
                temp+=x/r;//temp=1
                cout<<temp<<endl;
            }
        }
    }
```
我一段一段的分析：

第一段是如果加热到c的用时超过了x的情况
```cpp
if((c-a)*p>=x){ //如果加热到c的用时超过了x
            
            cout<<a+(x/p)<<endl; //这时能加热多少加热多少
            
            return 0; //直接结束代码
        }
```
第二段是如果加热到c的用时不超过x的情况
```cpp
	else{ //如果加热到c的用时不超过x
            x-=(c-a)*p; //将剩余时间减去这部分加热的时间
            
            temp=c;//目前温度就等于解冻时的温度
            
            if(q>=x){ //如果解冻的时间超过x或等于x
            
            	cout<<temp<<endl; //直接输出解冻时的温度
            
            	return 0; //直接结束
            
            }else{ //如果解冻的时间不超过x
            
            	x-=q;//将剩余时间减去解冻时间
            
            	temp+=x/r; //温度能加热多少加热多少
            
            	cout<<temp<<endl; //输出最后温度
            }
        }
```



------------
### step 3 若a等于c
```cpp
else if(a==c){
        if(q>=x){
            cout<<temp<<endl;
            return 0;
        }else{
            x-=q;
            temp=c;
            temp+=x/r;
            cout<<temp<<endl;
        }
```
是不是有点似曾相识的感觉？

那我就不多讲了，和上面一样


------------
### step 4 若a大于c
```cpp
else{
        temp=a;
        temp+=x/r;
        cout<<temp<<endl;
    }
```
依然和上面差不多，也不多讲

最后return 0，结束代码！

完整代码如下：
```cpp
#include<iostream>
using namespace std;
int main(){
    long long a,c,p,q,r,x,temp=0;
    cin>>a>>c>>p>>q>>r>>x;
    if(a<c){
        if((c-a)*p>=x){
            cout<<a+(x/p)<<endl;
            return 0;
        }else{
            x-=(c-a)*p;
            temp=c;
            if(q>=x){
                cout<<temp<<endl;
                return 0;
            }else{
                x-=q
                temp+=x/r;
                cout<<temp<<endl;
            }
        }
    }else if(a==c){
        if(q>=x){
            cout<<tem<<endl;
            return 0;
        }else{
            x-=q;
            temp=c;
            temp+=x/r;
            cout<<temp<<endl;
        }
    }else{
        temp=a;
        temp+=x/r;
        cout<<temp<<endl;
    }
    return 0;
}
```
~~作者：悄悄埋了俩坑，应该没人发现吧？~~


求赞求过！（你看我那真诚的眼神）

---

## 作者：B_Qu1e7 (赞：16)

感觉你们都写得好复杂啊……

好久没写题解了冒出来写一发

其实一个while+一点判断就差不多了

0.21kb
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int a,c,p,q,r,x;
    cin>>a>>c>>p>>q>>r>>x;
    while(a<c)
    {
        if(x>=p)x-=p,a++;
        if(x<p){cout<<a;return 0;}
    }
    if(x<q){cout<<a;return 0;}
    cout<<a+(x-q)/r;
}
```

---

## 作者：sxyugao (赞：15)

没有Pascal题解，我来发一个。

这道题不算难，但是要考虑周全，我本人被一个小地方坑了四五次。。。

```cpp
var
a,c,p,q,r,x,t:int64;//int64别忘
begin
read(a,c,p,q,r,x);
if a<c then//初始温度在熔点以下
  begin
    t:=(c-a)*p;//到达熔点所需的时间
    if t>=x then begin write(a+x div p);halt;end;
    //这都比已有的时间长，说明到不了熔点
    t:=t+q;//加上融化的时间
    if t>=x then begin write(c);halt;end;
    //说明温度过不了熔点，输出熔点
    write(c+(x-t)div r);//剩下的时间继续加热
    halt;
  end;
if a>c then begin write(a+x div r);halt;end;
//原来就比熔点高，什么都不用管
//PS:我这里一开始从上面复制（c+(x-t)div r），结果一直错。。。
if q>=x then begin write(c);halt;end;
//因为前面的判断里全用了halt，所以这种就一定是初始温度等于熔点，老思路
write(a+(x-q)div r);//这里写a和c皆可
end.
```
总结：一定要仔细，多想想！！！

---

## 作者：逆时针的记忆 (赞：9)

我相信大家是被题目的名字吸引的

我就是的，因为卧狠弱，纯粹模拟

一个while完成的事

看到题目本来准备花30分钟写的，但无奈多了25分钟，所以写了这篇题解


```cpp
#include <iostream>
#include <cstdio>
using namespace std;
long long a,c,p,q,r,x;//不晓得要不要longlong，开了反正对
int main()
{
	bool doom;//是否解冻
	cin>>a>>c>>p>>q>>r>>x;
	while (x>0)
	{
		if (a<c)
		{
			if (x-p<0) break;//时间你总不能赊账吧
			x=x-p;
			a++; doom=false;
		}
		else if (a==c&&doom==false)
		{
			if (x-q<0) break;
			x=x-q; doom=true;
		}
		else
		{
			if (x-r<0) break;
			x=x-r;
			a++;
		}
	}
	cout<<a<<endl;
	return 0;
}
```


---

## 作者：hyzxxqc (赞：7)

感觉不爽，发一波题解？
这题无非就分三种情况：

1. 需要一段时间才能进行解冻
1. 立即解冻~~（其实没有必要）~~
1. 已经解冻了

每一类中再分几个小类~~~~呵呵

不多说，上代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
long long a,c,p,q,r,x,jdt,t;
int main()
{
	cin>>a>>c>>p>>q>>r>>x;//输入，不多说
	jdt=p*(c-a);//到开始解冻所需的时间（负的就负的）
	if (jdt>0)//如果还没开始解冻
		if (jdt>=x) t=a+floor((x*1.0)/p);//来不及开始解冻
		else if (jdt+q>=x) t=c;//解冻中
			 else t=c+floor(((x-jdt-q)*1.0)/r);//解冻完毕，继续升温
    if (jdt==0)//立即开始解冻（这一类其实可以合并到上一类的）
		if (x<=q) t=c;//解冻中
		else t=c+floor(((x-q)*1.0)/r);//解冻完毕，继续升温
	if (jdt<0)//不需要解冻
		t=a+floor((x*1.0)/r);//直接计算
	cout<<t;//输出
	return 0;//是不是觉得很简单？？？
}
```

---

## 作者：wulibra (赞：6)

 经过长达1个小时的思索，调试，本蒟蒻终于解出了这道题
 
 接下来，我会把这1个小时放在这篇题解里，给大家讲一下我的思路。
 emm先简化一下题意：
1.  初始为 a 度
1. 小于 c 度，p单位时间加热1单位温度
1. 等于 c 度,q单位时间解冻,温度不变
1. 大于 c 度，每r单位时间加热1单位温度
1. 求加热 x 单位时间的时候果冻的温度
1. 注意开long long

 所以还是不知所云？那就看先看代码叭，我们慢慢解释：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	long long a,c,p,q,r,x;
	cin>>a>>c>>p>>q>>r>>x;
	if(a<c) 
		cout<<a+min(c-a,x/p)+(abs((x-(c-a)*p-q)/r)+(x-(c-a)*p-q)/r)/2;
	if(a==c)
		cout<<a+(abs((x-q)/r)+(x-q)/r)/2;
	if(a>c)
		cout<<a+x/r;
	return 0;
}
```
OIer：？？？

 emm，从简单到复杂开始讲起吧



------------


 ```cpp
	if(a>c)
	cout<<a+x/r;
```


------------
 首先我们要引入一个概念：升温效率（划重点）。升温效率就是在单位时间内果冻升温的多少，在题目中也有相应的表示，如：1/r，1/p(这个要自己琢磨体会一下子喔）。这个时候我们就可以瞎编出一个公式：


------------

# 升高温度=升温时间*升温效率


------------
 知道了它和它的变形式，就找到了解这道题的关键。
 emm言归正传，这行代码应该很好懂（如果不好懂请戳右上方大拇指解气），当初始温度高于解冻温度时（也就是不需要解冻），末温应该等于初始温度+升温时间*升温效率。


------------

```cpp
if(a==c)
cout<<a+(abs((x-q)/r)+(x-q)/r)/2;
```


------------
 这行代码可能就不是很好懂了。a 是初始温度，后面那一坨是啥呢。。。
 当果冻温度与解冻温度相等时，这个果冻需要解冻，也就是要消耗时间 q。那么直接用总时间x减去解冻时间 q，再乘以升温效率 1/r，再加上初温 a，不就好了啦！！！
### （成功入坑，OIer--）
 在你任性地直接减去时，你可能没有想到一个问题：如果减完是负数呢？？放到实际问题里，就相当于你的总时间还没有解冻时间长，所以它的温度根本没升。
### 那该怎么解决呢？
 经过12ms的思考，我找到了一个很诡异的处理方法。为了好表示，我们假设一个数叫 z，z 可能大于0也可能小于0。我们对它进行绝对值处理，然后再加上原数，然后除以2，也就是 （|z|+z）/2 ,这样处理如果z是正数我们让它返回z，如果是负数我们让它返回0来使后面的计算无效，这样就省去了一次if的麻烦，虽然没啥用，但是这样显得我不一般~


------------
```cpp
if(a<c) 
cout<<a+min(c-a,x/p)+(abs((x-(c-a)*p-q)/r)+(x-(c-a)*p-q)/r)/2;
```


------------
 最后，我们来讲讲这最恶心的部分。我们先别看代码，自己思考一下，这种情况应该是这样的：
## 初温 a-->解冻温 c-->解冻-->升温
 好了，我们来挨个处理。最后的解冻升温过程跟上面的类似，相似点不再多说，说一下不一样的地方。
### 它的时间，该怎么求？
 这就需要我们算出第一次升温所耗时间。根据公式可知，第一次升温升了 （c-a）度，效率是 1/p，直接代入公式就可以算出时间，再减去解冻时间   q，就是我们在之前的过程中所消耗的时间。用总时间减去消耗的时间，就是代码中的 (x-(c-a)*p-q)部分，就是我们解冻后升温的时间。再代入公式，用第二个代码下的方法处理之后得到非负值，就是我们在升温过程中所升温度。
### 那由a到c呢？（没错，由a到c，就ac了）
 我写了一个min函数来处理。 c-a 可看作理论升温， x/p 可看作实际升温。当果冻的末温大于 c，x/p 就会较大，min函数就会选择 c-a 输出，也就是第一次升温升到了 c 度。当果冻的末温小于 c， x/p 就会较小，min函数就会选择 x/p 输出，也就是第一次升温没升到 c 度且不进行第二次升温。
 
 
 自己捋一捋，是不是这样？
 
 
新人第一次写题解，如果您觉得不错的话，请给我点一个赞吧！谢谢谢谢！


 如果有错误的地方，还请大家批评指出！
###### 没用什么语法的我，成功把一个OI题做成数学题orz



---

## 作者：盖伦的好朋友 (赞：4)

###这题用循环模拟会TLE的！！

所以，厚颜无耻的我写了一个O（1）的算法

根据时间分情况，然后用p和r整出即可

特别注意，有a>c的数据，所以要特判，不这样只能得80（不要问我是怎么知道的）

最后附上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a,c,p,q,r,x;
int work();
int main()
{
    cin>>a>>c>>p>>q>>r>>x;
    cout<<work();
}
int work()
{
    int te=c-a;
    int t1=te*p;
    int t2=t1+q;
    if(a<c)
    {
        if(x<=t1)return a+x/p;
        if(x>t1&&x<=t2)return c;
        if(x>t2)return c+(x-t2)/r;
    }
    if(a>c)
    return a+x/r;
}
```

---

## 作者：linlin (赞：3)

看到我这种解法似乎没有Pascal的，于是......来一波！！！
****
#题目分析：
本题，嗯，是基础的练手题吧。

分几种情况判断一下，不过有个最坑爹的地方是最后一个点a在一开始就比c大了。。

坑了我好几次啊233
##判断：
1. 果冻未解冻 如果x减p大于等于零 那么a+1
1. a=c 如果x减q大于等于零 将果冻的状态变成解冻的 
1. 果冻解冻了 如果x减r大于等于零 那么a+1
1. a如果一开始大于c，直接把果冻状态变成解冻的（在循环开始前）
****
#Pascal自带函数--continue

作用：直接结束此次循环，开始下一次循环
****
#程序
```pascal
var a,c,p,q,r,x,i:longint;//变量，不用多说吧？

n:boolean;//是否解冻

function t(y:longint):boolean;//此函数用于判断x是否够减

begin

if y<0 then exit(false)

else exit(true);

end;

begin//程序开始

readln(a,c,p,q,r,x);

n:=false;//一开始没有解冻(false)

if a>c then n:=true;//如果一开始a就大于c的话直接解冻啦

while true do//世上最牛逼循环（无限循环，当然后面会跳出）

begin

if (a=c)and(not n) then if t(x-q) then begin n:=true;x:=x-q;continue;end;//这是当a等于c且未解冻情况，变成解冻(true),continue不知道翻上去（你肯定没认真看QAQ）

if not n then begin //如果没解冻，，，

if t(x-p) then begin inc(a);dec(x,p);continue;end;//时间还够就加热

end;

if n then begin//如果解冻了，，，

if t(x-r) then begin  inc(a);dec(x,r);continue;end;//时间还够就加热

end;

break;//如果上面if语句都失效了就会跳出（每个if都有continue，会跳过这个break）

end;

writeln(a);//输出温度

end.//程序结束啦！！

                                                                by linlin
                                                                  
                                                   --2018.3.8（女神节快乐）
                                                   
（小到看不见的ps：如果发现每一句之间都有空行是因为本人的诡异习惯。。见谅见谅啊^-^）
                                                        

---

## 作者：你祖奶我很ok (赞：3)

我来发一道c的题解
```c
#include <bits/stdc++.h>
using namespace std;
long long a,c,p,q,r,x,jdt,t;
int main()
{
    cin>>a>>c>>p>>q>>r>>x;
    jdt=p*(c-a);
    if (jdt>0)
        if (jdt>=x) t=a+floor((x*1.0)/p);
        else if (jdt+q>=x) t=c;//解冻中
             else t=c+floor(((x-jdt-q)*1.0)/r);
    if (jdt==0)
        if (x<=q) t=c;
        else t=c+floor(((x-q)*1.0)/r);
    if (jdt<0)
        t=a+floor((x*1.0)/r);
    cout<<t;
    return 0;
}
```
加油，大佬么！

---

## 作者：SS003 (赞：2)

看了一下其他的模拟解法,发现一个共同点:**代码很长**

那我就发一个短一点的模拟解法吧


```cpp
#include<cstdio>
using namespace std;
    long long a/*原温度*/,c/*熔点温度*/,p/*解冻前加热(时间/℃)*/,q/*解冻时间*/,r/*解冻后加热(时间/℃)*/,x/*加热时间*/;
    int st=0;//存储果冻的状态(是否解冻)
int main(){
    scanf("%lld%lld%lld%lld%lld%lld",&a,&c,&p,&q,&r,&x);
    while(x>0){//以时间作为判断条件
    if(a<c){st=0;x=x-p;a++;}
    if((a==c)&&(st==0)){x=x-q;st=1;}//解冻过程
    if(a>c){st=1;}、、状态判断
    if((a>=c)&&(st==1)){x=x-r;a++;}
    }
    if(x<0){a=a-1;}//当时间条件不符合时,温度-1
    printf("%lld",a);
    return 0;
}
```

---

## 作者：zhi_zhang (赞：2)

十分简单的模拟题

**模拟过程：**

1. 解冻前的升温，每次所剩温度X减去P，如果X还大于等于0，A++，如果X已经小于0，输出A然后退出.
1. 解冻中，X减去Q，如果还大于等于零就继续，如果小于等于0，输出A然后退出。
1. 解冻后的升温，跟第一步一样，但是取消掉A的限制，只对X做限制，X每次减去R，如果小于零就输出A然后退出，不然A++；

**因为做题习惯，代码十分不简洁，但是十分明朗易懂**

200ms, 2082KB

~~PS：读入优化完全可以不要，直接scanf（balabala）就完了~~

```
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cctype>
#include<cmath>
#include<queue>
#include<bitset>
using namespace std;
//常量 

//结构体 

//变量 
int A,C,P,Q,R,X;
//数组

//函数 
int Rein();
//main函数 
int main()
{
	A=Rein(),C=Rein(),P=Rein(),Q=Rein(),R=Rein(),X=Rein();
	while(A<C)//解冻前升温 
	{
		X-=P;
		if(X<0)
		{
			printf("%d",A);
			return 0;
		}
		else A++;
	}
	X-=Q;//解冻 
	if(X<=0)
	{
		printf("%d",A);
		return 0;
	}
	while(1)//解冻后升温 
	{
		X-=R;
		if(X<0)
		{
			printf("%d",A);
			return 0;
		}
		else A++;
	}
	return 0;
}
//函数内容 
int Rein()
{
    int x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9')
    {
        if(c=='-') f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9')
    {
        x=10*x+c-'0';
        c=getchar();
    }
    return f*x;
}

```

---

## 作者：double是新手 (赞：1)

没有Python3的题解，~~特地来水一发~~，来写一下。

本题可以根据加热时间x的消耗，每种情况下都会消耗一定的时间，但要分两情

况，分别是时间x足够加热到c度和时间x不足或刚刚好加热到c度

```python
l = list(map(int, input().split()))
a = l[0]
c = l[1]
p = l[2]
q = l[3]
r = l[4]
x = l[5]
flat = True

t = a
while True:
    if t < c:
        if (x <= (c-a)*p):    #当时间x不够加热到c度时
            w = t + x // p  #最后的温度w就等于起始温度a加上x时间内能够加热的温度
            flat = False
            break
        else:        #当时间x内足够加热到c度时
            x = x - (c - a) * p  #消耗了加热到c度的时间后剩下的x
            t = c
    if t == c:
        x = x - q   #减去解冻时间q后剩下的时间x
    
    w = x // r  #解冻完成后升高了多少温度
    break
if flat == True:  
    print(t+w)   #最后温度等于c度加上解冻后升高的温度
else:
    print(w)    #倘若时间x不够加热到c度时的温度
```



---

## 作者：Marshmallowo (赞：1)

#模拟法

##解题思路

**解题思路很简单，开一个long long的数组，不断循环，每一次温度加1，对应时间就加p或q或r，注意在当温度达到临界值时，需要+q+r，既要解冻，也要加温。输出很巧妙，不论如何time一旦大于x，输出的值肯定就是tem-1**


```cpp
#include <iostream>
using namespace std;
int main() {
    long long tem,c,p,q,r,x,time=0;
    cin>>tem>>c>>p>>q>>r>>x;
    if(x==0) {
        cout<<tem;
        return 0;
    }
    while(1) {
        if(tem<c) {
            tem++;
            time+=p;
        } else if(tem==c) {
            tem++;
            time+=q;
            time+=r;
        } else if(tem>c) {
            tem++;
            time+=r;
        }
        if(time>x) {
            cout<<tem-1;
            return 0;
        }
    }
    return 0;
}
```

---

## 作者：月影困 (赞：1)

我觉得最难的地方在**考虑完整情况**呗（尤其是 **a > c** 这个OTL）

程序的话……其实**直接判断**就能过啊=-=

因为之前做到过剪纸条成方块的某d1t1……，那题循环模拟是要TLE的OvO（虽然最后是因为行末空格直接爆零了TvT）

下面是代码！

```cpp
#include <cstdio>

long long a, c, p, q, r, x;//题目提示用long long了哟 

int main()
{
    scanf("%lld%lld%lld%lld%lld%lld", &a, &c, &p, &q, &r, &x);
    
    if (a <= c)//普通情况：从冰箱里拿出来是冻着的 
    {
        if ((c - a) * p >= x)//如果给的时间不足以达到熔点 
        {
            return !printf("%lld", a + x / p);
            //直接输出初始温度加上加热的温度并结束程序
            //因为给的时间不足，后面继续判断就是浪费时间 
            //另外，用/号就是向下取整啦 
        }
        x -= (c - a) * p;//减去加热时间 
        if (q >= x)//如果在熔点不足以使其融化 
        {
            return !printf("%lld", c);
            //直接输出熔点温度并结束程序
        }
        x -= q;//减去融化时间 
        printf("%lld", c + x / r);//输出最后温度 
    }
    if (a > c)//特殊情况：冰箱坏了（bushi）拿出来是化了的 
    {
        return !printf("%lld", a + x / r);
        //直接输出初始温度加上加热的温度并结束程序
    } 
    
    return 0;
}
```

---

## 作者：Drinkkk (赞：1)

/\*
P3926 题解

模拟算法

\*/
/\*
当时一开始想的就是将果冻一直加热，直到刚好等于c度为止，

然后在解冻，解冻完之后直接将a加上x'/r（向下取整）就好了。

但是，这种思路只能够得到90分。

这是为什么呢？

这是因为我刚刚没有考虑一开始时a>c的情况。

话不多说了，上代码。

（还有，记得要用long long）

\*/
```cpp
#include <cstdio>
int min(int x,int y)
{
    return x<y?x:y;
}
int main()
{
    long long a=0,c=0,p=0,q=0,r=0,x=0;
    scanf("%lld %lld %lld %lld %lld %lld",&a,&c,&p,&q,&r,&x);
    while(1)
    {
        if(a>=c)
        {
            break;
        }
        if(x-p<0)
        {
            printf("%lld",a);
            return 0; 
        }
        x-=p;
        a++;
    }
    x-=min(x,q);
    a+=x/r;
    printf("%lld",a);
    return 0;
}
```

---

## 作者：a120120 (赞：1)

这题没用循环居然ac了！直接用if语句判断温度所在的范围，然后再判断是否要输出，温度和时间一起变。

注意：a==c时只减时间，温度不会增加。还有题目友情提示long long类型啦！

此题还是比较简单的。恩。

```cpp
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<iomanip>
using namespace std;
int main()
{
    long long a,c,p,q,r,x;
    cin>>a>>c>>p>>q>>r>>x;
    if(a<=c&&(x>abs(a-c)*p))//小于且时间至少够到c,不用立马输出，后面还有。
        {
            x-=abs(a-c)*p;//时间
            a=c;//温度
        }
        if(a<=c&&(x<＝abs(a-c)*p))//时间道不了下一阶段了直接输出
        {
            a+=x/p;cout<<a;//基本就是向下取整了
        }
        if(a==c&&x>=q)//临界温度不变并判断是否进入下一步
        {
        x-=q;//时间
        }        
        if(a==c&&x<q)
        {
            cout<<a;
        }
        if(a>=c&&x>=r)//x>=r保险加上吧不过理论上可以不要
        {
            a+=x/r;cout<<a;//还是取整
            }
    return 0;
}
```

---

## 作者：彩云—易散 (赞：1)

个人认为这道题可以看成一道很标准的分段函数。

很基础，于是来练手。

情况不是很复杂，但是要考虑周全，注意分类讨论。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
//a 代表初始温度 c代表晶体的熔点 p，q，r，x意义如题  ans记录答案
long long a,c,p,q,r,x,ans;
//以下是（优美的）快读
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int main()
{
    a=read();c=read();p=read();q=read();r=read();x=read();
    if(a<c)//如果初始温度低于熔点，接下来果冻需要先升温到熔点
    {
        int b=c-a;//升到熔点需要升的温度
        if(x<=b*p)//b*p 即为加热到c度所需时间 
        {
            ans=a+(x/p);
        }
        if(x>b*p&&x<b*p+q)//果冻保持在即将到熔点的温度
        {
            ans=c-1;
        }
        if(x==b*p+q)//果冻恰好达到c
        {
            ans=c;//那么果冻最后依然是c
        }    
        if(x>b*p+q)//果冻已经完成解冻
        {
            int d=b*p+q;
            ans=c+(x-d)/r;
        }
        printf("%lld",ans);
    }
    else if(a==c)//此时果冻恰好达到c，需要判断
    {
        if(x<q)//如果继续加热的时间不够长以至于果冻不能解冻
        {
            ans=c;//那么果冻就会保持在目前这个状态
        }
        if(x==q)//临界状态，其实跟上面的可以合并
        {
            ans=c;
        }
        if(x>q)//果冻可以成功解冻，接下来成为了液体
        {
            int e=x-q;//剩余时间
            ans=c+e/r;// e/r表示液体果冻在剩余时间里可以升的温度
        }
        printf("%lld",ans);
    }
    else if(a>c)//果冻本来就是液体了，继续加热就是液体温度的升高了
    {
        ans=a+x/r;//初始温度+升温
        printf("%lld",ans);
    }
    return 0;//结束程序了
}
```

---

## 作者：feecle6418 (赞：1)

紧跟在kkk后面发个题解。

这题，就是考虑三种情况，多判断，就可以了。

对这代码说一下：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a,c,p,q,r,x;//注意开long long
long long get(long long a,long long c,long long p,long long q,long long r,long long x){
    if(a>c){//情况一：不用考虑c
    //    cout<<a<<' '<<c<<' '<<p<<' '<<q<<' '<<r<<' '<<x<<endl;
        return a+x/r;
    }
    if(a==c){//情况二：没解冻
    //    cout<<a<<' '<<c<<' '<<p<<' '<<q<<' '<<r<<' '<<x<<endl;
        x-=q;
        if(x<=0){
            return c;
        }
        else return a+x/r;
    }
    if(a<c){//情况三：普通情况
    //    cout<<a<<' '<<c<<' '<<p<<' '<<q<<' '<<r<<' '<<x<<endl;
        if(a+x/p<=c)return a+x/p;
        else return get(c,c,p,q,r,x-(c-a)*p);//转化为情况二
    }
}
int main() {
    cin>>a>>c>>p>>q>>r>>x;
    cout<<get(a,c,p,q,r,x);
    return 0;
}
```

---

## 作者：Harmony (赞：1)

这道题应该可以直接模拟吧。。

直接来代码吧：


```cpp
        int ans()//主程序直接省略。
        {
            while (a < c)//固体加热状态。。
            {
                if (x >= p)
                {
                    x -= p;
                    a++;
                }
                if (x < p)//如果已经到时间了，返回。。
                    return a;
            }
            if (x < q)//熔化。。
                return a;
            return a + (x - q) / r;//液体加热状态。。
        }

```

---

