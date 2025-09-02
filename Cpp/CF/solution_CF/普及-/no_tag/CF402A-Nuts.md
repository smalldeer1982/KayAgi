# Nuts

## 题目描述

You have $ a $ nuts and lots of boxes. The boxes have a wonderful feature: if you put $ x $ $ (x>=0) $ divisors (the spacial bars that can divide a box) to it, you get a box, divided into $ x+1 $ sections.

You are minimalist. Therefore, on the one hand, you are against dividing some box into more than $ k $ sections. On the other hand, you are against putting more than $ v $ nuts into some section of the box. What is the minimum number of boxes you have to use if you want to put all the nuts in boxes, and you have $ b $ divisors?

Please note that you need to minimize the number of used boxes, not sections. You do not have to minimize the number of used divisors.

## 说明/提示

In the first sample you can act like this:

- Put two divisors to the first box. Now the first box has three sections and we can put three nuts into each section. Overall, the first box will have nine nuts.
- Do not put any divisors into the second box. Thus, the second box has one section for the last nut.

In the end we've put all the ten nuts into boxes.

The second sample is different as we have exactly one divisor and we put it to the first box. The next two boxes will have one section each.

## 样例 #1

### 输入

```
3 10 3 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3 10 1 3
```

### 输出

```
3
```

## 样例 #3

### 输入

```
100 100 1 1000
```

### 输出

```
1
```

# 题解

## 作者：Tarsal (赞：13)

本蒟蒻又来发题解啦！

这题是个紫题？

好吧，恶意评分可海星？

#### 回到正题

这题很明显是贪心啊；

有a个坚果，b个隔板，x个隔板，最多分成v个区间。

那么我们的贪心策略是：

如果一共使用的挡板小于x，且当前的箱子个数不足k。

那么，就继续往这个箱子内加，直到大于为止，很水是吧。

直接看代码（附详解：

```cpp
#include<bits/stdc++.h>
using namespace std;

int a, b, k, v, sum, ans;
//a, b, k, v如题，sum是当前箱子的区间数，ans 是箱子的个数 
int main()
{
	scanf("%d%d%d%d", &k, &a, &b, &v);//输入k, a, b, v; 
	while(true)//有点皮，不过就是这么写的 
	{
		if(a <= 0)//如果坚果装够了，那就跳出。 
			break;
		sum = 1;//最开始的每个箱子中都有一个区间 
		while(b > 0)//如果还有隔板 
			if(sum < k)//且这个箱子中区间的个数小于k 
			{
				++ sum;//区间个数加加 
				-- b;//隔板数目减减 
			}
			else
				break;//如果没隔板了就退出 
		a -= sum * v;//坚果的个数要减去这个箱子中的区间的个数 乘上 最大坚果量的个数
		//莫非你一个区间内可以装v个，你却只装1个，还是v - 1个？ 
		++ ans;//统计箱子个数； 
	}
	printf("%d", ans);//输出啦 
	return 0;
}
```
本蒟蒻又双叒叕被爆踩了

---

## 作者：DinnerHunt (赞：4)

贪心:每个盒子放尽量多的隔板最优
```cpp
#include<iostream>
using namespace std;
int k,a,b,v,ans,num;
int main()
{
    cin>>k>>a>>b>>v;
    while(1)
    {
        if(a<=0) break;
        else
        {
            num=1;
            while(b>0)
                if(num<k) num++,b--;
                else break;
            a-=num*v;
            ans++;
        }
    }
    cout<<ans<<endl;
    return 0;
}
```


---

## 作者：nofall (赞：3)

~~恶意评分啊~~

每个箱子最多能放$k*v$个坚果，花费$k-1$个分隔。

最少能放$v$个坚果，花费$0$个分隔。

```cpp
#include <cstdio>
int num[1002];
int main() {
    int k, a, b, v;  //花费k-1个分隔放k*v个坚果
    scanf("%d%d%d%d", &k, &a, &b, &v);
    for (int i = 0; i < k; i++) num[i] = (i + 1) * v;
    int ans = 0;
    while (1) {
        ans++;
        if (b >= (k - 1)) {  //分隔够
            a -= num[k - 1];
            b -= (k - 1);
            if (a <= 0)
                break;
        } else {  //分隔不够
            a -= num[b];
            b -= b;
            if (a <= 0)
                break;
        }
    }
    printf("%d\n", ans);
    return 0;
}
```

---

## 作者：liangbowen (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF402A)

[$\color{red}{see}\space \color{blue}{in}\space \color{green}{my}\space \color{purple}{blog}$](https://www.luogu.com.cn/blog/liangbowen/solution-cf402a)

小学生又双叒叕来写题解啦！

看到其他题解描述得并不清晰，我就来一发。

这道题实际上不困难，重点就是**贪心**。

只要遵循“能用隔板就用隔板，尽量将一个箱子所能装的坚果数最大化”的原则就好。

我们试着在一个箱子里塞尽可能多的隔板。

具体看这一部分代码：

```cpp
if (b >= k - 1)  
//贪心，能用隔板就用隔板，尽量将一个箱子所能装的坚果数最大化。 
{
	b -= (k - 1);
	a -= k * v;   
}
else
{
	//隔板不够，为了最大化，就将全部隔板都塞进去。
	a -= (b + 1) * v;
	b = 0;
}
```

细心的童鞋会想到 $a$ 这样减后不是可能会**出现负数**吗？

你想啊，$a$ 既然能达到负数，那 $a = 0$ 不就更能达到了吗！

所以并不需要特判什么的，一直循环，只需要在 $a \le 0$ 时停止循环并输出答案就完事了。

## 最后给出完整代码：

```cpp
#include <iostream>
#include <cstdio>
using namespace std;

int main()
{
	int k, a, b, v, cnt = 0;  //cnt 记录箱子的数量。 
	scanf("%d%d%d%d", &k, &a, &b, &v);
	while (true)
	{
		cnt++;
		if (b >= k - 1)  
		//贪心，能用隔板就用隔板，尽量将一个箱子所能装的坚果数最大化。 
		{
			b -= (k - 1);
			a -= k * v;   
		}
		else
		{
			//隔板不够，为了最大化，就将全部隔板都塞进去。
			a -= (b + 1) * v;
			b = 0;
		}
		//实际上，此时的 a 有可能为负数，但这显然不重要。 
		if (a <= 0) break;
	}
	printf("%d", cnt);
    return 0;
}
```

---

## 作者：Forgotten_Dream (赞：1)

~~原来这题之前是黑题吗~~

是一个简单的贪心。既然要求箱子最少，那很显然的可以看出要尽量让每个箱子装的最多，也就是要尽量放置多的隔板。

详见代码
```cpp
#include <bits/stdc++.h>

using namespace std;

int main () {
	
	int a, b, k, v, x=0;
	
	cin>>k>>a>>b>>v;//翻译好像出锅了,应该是按照k,a,b,v输入的
	
	for (;;) {
		
		if (a<=0) break;//如果装完了就跳出
		
		int sum=1;//计数器记录区间,初始为1
		
		while(sum<k) {//如果隔板可以继续放就放
			
			if (b<=0) break;//如果隔板没了就跳出
			sum++, b--;//区间增加同时隔板减少
		}
		
		a-=sum*v;//总数减去放入个数
		x++;//箱子数增加
	}
	
	cout<<x;
	
	return 0;
}
```


---

## 作者：赤霞QvQ (赞：1)

这道题就是用好多变量名来扰乱你的思绪，其实就是个贪心

让你求最少的箱子数，那么我就要让每个箱子装的东西尽量多

看到“尽量多”了对不对？就是贪心了

那怎么贪呢？每个箱子都用$k-1$个隔板分成$k$个区间，每个区间内都放$v$个坚果，当然，如果隔板不够$k-1$的时候就停止这么做，或者是坚果没了，当然，如果这样的话就可以直接输出了

如果隔板不够$k-1$了，就把剩下的隔板全运用在一个箱子上

但如果板子没了，但是坚果还有呢？没关系，我们不是有无数个箱子吗？那么我们把一个箱子当做一个区间（好奢侈啊！），总归可以摆完坚果的

然后可以~~容易地~~证明这个贪心方式是正确的，就直接上代码了！

```cpp
#include<bits/stdc++.h>
using namespace std;
int k,a,b,v,s;
int main()
{
	cin>>k>>a>>b>>v;
	while(b>=k-1)
	{
		s++;
		b-=k-1;
		a-=v*k;
		if(a<=0)    //没坚果了
		{
			cout<<s<<endl;
			return 0;
		}
	}
	s++;
	a-=(b+1)*v;
	if(a<=0)    //可以再用一个箱子摆满
	{
		cout<<s<<endl;
		return 0;
	}
	if(a%v==0)
	{
		cout<<s+a/v<<endl;
		return 0;
	}
	cout<<s+a/v+1<<endl;    //如果不可以
	return 0;
}
```

完美结束程序

---

## 作者：ImmortalWatcher (赞：1)

这道题明显恶意评分啊！！

看到没有 $Pascal$ 的题解，我今天就发一篇，给小萌新们好好理解。

其实这道题很简单，就是贪心。

## 题目大意

你有若干个箱子和 $a $个坚果，$b$ 个隔板，$x$ 个隔板可以将箱子分成 $x+1$ 个区间，每个盒子不能被分成超过 $k$ 个区间，每个区间最多只能放 $v$ 个坚果，给定 $a$ , $b$ , $k$ , $v$，问装下所有坚果最少需要多少个箱子。

## 思路

我们先看这一句话，“装下所有坚果最少需要多少个箱子”，要求最少的箱子数，那我们肯定要一个箱子能放多少坚果就放多少坚果。在实现的过程中，注意边界的问题，比如：隔板够不够？这个箱子最多能放多少隔板？搞定这些就很好办了。

代码如下：

```pascal
var
    ans,k,a,b,v:longint;
    //ans表示答案。
begin   
    read(k,a,b,v); //输入。
    while true do
    begin
        inc(ans); //先用一个箱子。
        if b>k-1 then //如果隔板够，就放满箱子。
        begin
            dec(b,k-1); //对应减去用去的隔板
            dec(a,k*v); //对应减去放进箱子的坚果
            if a<=0 then break; //如果坚果放完了，那么程序就结束了。
        end
        else //如果隔板不够的情况。
        begin
            dec(a,(b+1)*v); //对应减去能放进去的坚果数
            if a>0 then inc(ans,a div v); //如果坚果还没放完，那么我们只能用箱子来凑，一个箱子能放v个隔板。
            if a mod v>0 then inc(ans); //因为上面用的是下取整（div），实际上我们要上取整，就比如说：一个箱子放3个坚果，你要放10个坚果，你需要用4个箱子才能放完，所以这里相当与一个查漏补缺。
            break; //然后因为坚果放完了，所以程序结束了。
        end;
    end;
    write(ans);
end.
```
希望大家能看懂，AC这道题，继续想神犇进发！


---

## 作者：TEoS (赞：1)

明显的恶意评分，这道题还是很简单的，实际上大概红题或橙题难度吧 ~~本来想水一道黑题，没想到变紫题了~~

这里给这题带来一个简单易懂的数学解法


------------
先定义一个函数$xjh(x,y)$（不要在意这个名字qaq）表示大于等于$x/y$的最小整数，即对$x/y$向上取整。通过小学奥数我们可以知道，把$10$个坚果放入最多能放$3$个坚果的区间，需要$xjh(10,3)=4$个箱子。（听说有一个$ceil$函数可以实现向上取整，然而这个函数并不是真正的向上取整，对于整数会直接$+1$，因此我们还是自定义一个吧）

设放下所有坚果至少需要$cnt$个区间，至少用$x$个箱子，此时用了$y$个隔板。为了判定用下所有隔板后还需不需要额外的箱子，这里再设只用下所有的隔板可以隔出$u$个区间，用了$w$个箱子。因为对于每个箱子，最多隔出$k$个区间，用$k-1$个隔板。于是有：
```cpp
cnt=xjh(a,v)=x+y//相当于把每个箱子看作一个挡板，则挡板数与区间数相等
w=xjh(b,k-1)//每个箱子最多用k-1个隔板
u=w+b=xjh(b,k-1)+b//与第一个式子原理相同
```
只要判定$u$是否比$cnt$大，就可以判定需不需要额外的箱子了。于是有以下两种情况：

1. 不需要额外的箱子

此时只要求出隔出$cnt$个区间至少需要几个箱子就可以了，有：
```cpp
x=xjh(cnt,k)
```
2. 需要额外的箱子

因为此时已经用了所有的隔板，即$y=b$，可以直接得出所需的箱子，有：
```cpp
x=cnt-y=cnt-b
```


------------
这样问题就解决了！是不是很简单。最后奉上代码：
```cpp
#include<iostream>
using namespace std;
int a,b,k,v,cnt;
int xjh(int x,int y)
{
    return x%y==0?x/y:x/y+1;
}//向上取整
int main()
{
    cin>>k>>a>>b>>v;
    cnt=xjh(a,v);
    if(xjh(b,k-1)+b>=cnt)
        cout<<xjh(cnt,k);
    else
        cout<<cnt-b;
    return 0;
}
```
~~其实还可以更短~~

希望对大家有帮助

---

## 作者：传奇英雄 (赞：0)

## 介绍一个此题的数学题解，欢迎Hack
此题最开始是黑题，显然是恶评。请各位大佬遵守道德，不要恶评哦QAQ
### 思路：分别求出全放隔板需要的箱子数、全放隔板需要的隔板数、剩余的坚果、剩下的坚果需要的空间数，在分类讨论，隔板够或隔板不够。
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
int a,b,v,k,x,y,z,w;
int main()
{
	//freopen("in","r",stdin);
	scanf("%d%d%d%d",&k,&a,&b,&v);
	x=a/(v*k);//全放隔板需要的箱子数
	y=x*(k-1);//全放隔板需要的隔板数
	z=a%(v*k);//剩余的坚果
	w=z/v;//剩下的坚果需要的空间数
	if(z%v) w++;
	if(y>b)//隔板不够
	{
		x+=y-b+w;//一个箱子相当于一个隔板
		printf("%d",x);
	}
	else
	{
		if(a%(v*k)) x+=max(1,w-b+y);//剩余有坚果
		printf("%d",x);
	}
	return 0;
}

```


---

