# Vladik and Courtesy

## 题目描述

在一次正规的比赛后Vladik和Valera分别赢得了$a$ 个糖果和$b$  个糖果。Vladik将$1$ 个他的糖果给Valera。然后Valera将$2$ 个的糖果给Vladik，所以没有人认为他不是那么慷慨大方。接下来Vladik因为同样的原因将$3$ 个糖果给Valera。

更确切的说，每个人给对方比上一次自己收到的更多一个糖果

这种情况直到他们其中有人给不出足够的糖果为止。他们从对方那里得到的糖果不被认为是自己的。你需要直到谁是给不出糖果的人。

## 样例 #1

### 输入

```
1 1
```

### 输出

```
Valera
```

## 样例 #2

### 输入

```
7 6
```

### 输出

```
Vladik
```

# 题解

## 作者：kon_tori (赞：3)

### 题意
``Vladik`` 原来有 ``a`` 颗糖果，``Valera`` 原来有 ``b`` 颗糖果。然后他们玩起了一种回合制的游戏： ``Vladik`` 给``Valera`` ``1`` 颗糖，
``Valera`` 给``Vladik`` ``2`` 颗糖；
``Vladik`` 给``Valera`` ``3`` 颗糖，
``Valera`` 给``Vladik`` ``4`` 颗……即每个人给对方比上一次自己收到的多一个糖果，当他们其中有人给不出足够的糖果，游戏结束，输出无法给出足够糖果的人。

一个比较重要的信息：**他们从对方那里得到的糖果不被认为是自己的**。这样我们就不需要再考虑他们两人的糖果还会增加的情况，使得本题难度大大降低。

### 思路
一直循环，每回合根据题意分别对 ``Vladik`` ,``Valera`` 两人的糖果数量进行扣除，直到其中一人给不出要求的数量时，输出这个人的名字，结束循环。

### 代码实现 
```cpp
/* light_chaser */
  #include<bits/stdc++.h>
  using namespace std;
  int a,b;
  int step=1;//应给的糖果数
  int main(){
      cin>>a>>b;
      while(1){//一直循环，直到有一个人给不出糖果
          if(a-step<0){
              puts("Vladik");
              return 0;
          }//若Vladik给不出，输出，结束
          else{
              a-=step;
              step++;
          }//否则扣除Vladik的糖果，更新step的值               
          if(b-step<0){
              puts("Valera");
              return 0;
          }//若Vlalera给不出，输出，结束
          else{
              b-=step;
              step++;
          }//否则扣除Vlalera的糖果，更新step的值
      }
  }
```
### 后记：
之前交过一次本题的题解，然后~~成功~~被打回来了。

>很遗憾，您上传的题解 题解 CF811A 【Vladik and Courtesy】 未能通过审核。原因是 拒绝: 说明过少 。

于是蒟蒻重新写了一篇题解，希望这次管理员能让我通过。

再次感谢管理员的辛勤付出！

~~看在我代码这么通俗易懂的份上能不能点个赞啊~~

---

## 作者：wuwenjiong (赞：2)

## 题意：
有两个人，在比赛中分别赢得了 $a$ 个糖果和 $b$ 个糖果，两人互相送糖果，一个人首先送给对方一个糖果。现在已知他们俩每次送对方的糖果都比上一次对方送给自己的糖果数多一个。求谁最先无法给对方送糖果，输出他的名字，并且**他们从对方那里得到的糖果不被认为是自己的**，这一点十分重要，可能会有人跟本蒟蒻一样，因为没看到这一点而错了。
## 思路：
以循环为框架，定义 $i$ 的初始值为 $0$ 。**每次循环**，先判断一下，如果 $a$ 是负数，输出对应的人的名字并结束程序，否则 $i$ 自增， $a$ 与其相减。然后再判断，如果 $b$ 是负数，输出对应的人的名字并结束程序，否则 $i$ 再次自增， $b$ 与其相减。

最后，代码实现如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	long long a,b,i=0;
	cin>>a>>b;
	while(1==1)//死循环，后面满足条件时就结束程序
	{
		if(a<0)//判断
		{
			cout<<"Vladik";
			return 0;
		}
		else
		{
			i++;//i自增
			a-=i;//a减去i
		}
		if(b<0)//判断
		{
			cout<<"Valera";
			return 0;
		}
		else
		{
			i++;//i再次自增
			b-=i;//b减去i
		}
	}
	return 0;
}
```
谢谢！！！

---

## 作者：Yaixy (赞：2)

# 题意及注意点

- **题意**：$Vladik$ 和 $Valera$ 分别有 $a$，$b$ 颗糖果，$Vladik$ 与 $Valera$ 轮流送给对方糖果，送糖果的数量每次递增一颗，希望求出谁首先无法给出糖果。

- 此题完全是入门题难度。（

- $Vladik$ 和 $Valera$ 从对方那里得到的糖果不被认为是自己的。

- $a$ 和 $b$ 不会炸 $int$，~~可以放心食用~~。

# 思路

这道题大概就是单纯的暴力吧qwq

不断更新送出的糖果数 $i$，分别从 $a$ 和 $b$ 当中减 $i$，减完以后判断 $a$ 和 $b$ 是否小于 $0$，小于 $0$ 就输出，否则继续循环。

顺带一提，对于糖果剩余数量，我是减完直接判的，如果您是在下一次循环中再判也没问题。

具体操作详见代码qwq

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,i;
int main()
{
	ios::sync_with_stdio(false);
	cin>>a>>b;
   //a: Vladik拥有糖的数量
   //b: Valera拥有糖的数量
	while(1)
	 {
	 	a-=++i;//Vladik给糖
	 	if(a<0) //判断
		 {
		 	cout<<"Vladik\n";
		 	return 0;
		 }
	 	b-=++i;//Valera给糖
	    if(b<0)//判断
		 {
		 	cout<<"Valera\n";
		 	return 0;
		 }
	 }
	return 0;
}
```

完结撒花awa

---

## 作者：Waaifu_D (赞：1)

**题意**

A与B互相给糖，第一次A给B一个糖，然后B给A2个糖，B再给A3个糖，以此类推

**思路**


![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF811A/681b7b735b92ff86dc091b8352c15966e26a0a20.png)

研究这个表我们可以发现，step（步数）为偶数时，是Valera给糖，为奇数则Vladik给糖，所以我们可以依据这个确定谁给出糖

**代码**

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
	int a,b,tag=0;
	cin>>a>>b;
	while(1)//直接循环模拟即可
	{
		tag++;
		if(a<0)//谁率先给不出糖，就结束程序
		{
			cout<<"Vladik";
			return 0;
		}
		if(b<0)
		{
			
			cout<<"Valera";
			return 0;
		}
		if(tag%2==1) a-=tag;//如思路中所解释
		if(tag%2!=1) b-=tag;
	}
}
```


---

## 作者：想不好名字 (赞：1)


### 题目分析

大意就是两个大佬AK模拟赛，然后以糖果为奖励；为了表达真挚的友谊，他们互赠糖果，互赠的糖果数依次加一，但你获得的糖果不能互赠，问谁首先给不出糖果。

### **思路**

一直循环，知道有人给不出要求数量的糖果。注意：收到的糖果不能再次给出这样就小了很多难度。



# AC Code

```c
#include<iostream>
#include<cstdio>
using namespace std;
int a,b;
int main()
{
	cin>>a>>b;
	for(int i=1;;++i) //无限循环，i表示循环次数和要给出的糖果数量
	{
		if(a<0)
		{
			cout<<"Vladik";
			return 0;
		}
		if(b<0)
		{
			cout<<"Valera";
			return 0;//如果有人给不出糖果，结束程序
		}
		if(i%2==1) //判断轮到谁给糖果
		a-=i;
		else
		b-=i;
	}
	return 0;
}
```


---

## 作者：「已注销」 (赞：1)

找规律发现Vladik能给$\lfloor\sqrt a\rfloor$次

设Valera能给$x$次

则$x(x+1)\le b$

最大整数解$\lfloor\sqrt{b+0.25}-0.5\rfloor$

比较$\lfloor\sqrt a\rfloor$和$\lfloor\sqrt{b+0.25}-0.5\rfloor$即可
```cpp
#include<cmath>
#include<iostream>
using namespace std;
int a,b;
int main(){
    cin>>a>>b;
    a=sqrt(a);
    b=sqrt(b+0.25)-0.5;
    if(a<=b)cout<<"Vladik";
    else cout<<"Valera";
}
```

---

## 作者：Rosemary_dream (赞：0)

这题，有点水：

**题意描述：**

Vladik 给 Valera 一个糖果 Valera 就会给 Vladik 两个糖果 Vladik 再给 Valera 三个糖果。~~（完美的翻译）~~


读题会发现：两人给彼此的糖果**不会算作是自己的**，所以只要定一个计数器，用两人剩余的糖果轮流减去计数器就好了，这样的话，如下：

```
while(1)//无限循环
	{
		if(a-c>=0)
		{
			a=a-c;//Vladik 给糖
		    c++;//计数器
		}
		else
		{
			cout<<"Vladik";
			return 0;//结束
		}
		if(b-c>=0)
		{
		   b=b-c;//Valera 给糖
		   c++;
		}
		else
		{
			cout<<"Valera";
			return 0;
		}
```
这是一种单独定义计数器的做法，还可以将计数器融入 for 循环里：

```
#include<iostream>
using namespace std;
int main()
{
	long long a,b;
	cin>>a>>b;
	for(int i=1;;i++)
	{
		if(i%2==0)//用 for 循环的话，要判断减去谁的糖果，奇数就减去 Vladik 的，偶数就是减去Valera的。
		{
			if(b-i>=0)
		    {
		        b=b-i;
		    }
		    else
		    {
			    cout<<"Valera";
			    return 0;
		    }
		}
		else
		{
			if(a-i>=0)
		    {
			    a=a-i;
			    continue;
		    }
		    else
		    {
			    cout<<"Vladik";
			    return 0;
		    }
		}
	}
}
```
如此如此，云云。

**（谢谢管理员们的付出！）**

---

## 作者：joy2010WonderMaker (赞：0)

先简化题意。题目的意思是：给定两个数 $a$ 和 $b$，先将 $a$ 减去1，再将 $b$ 减去2，然后再将 $a$ 减3，以此类推，如果 $a$ 先比0小，则输出 Vladik，反之输出 Valera。

AC Code:

```cpp
#include<cstdio>
int main(){
    int a,b;
    scanf("%d%d",&a,&b);
    printf("共建文明洛谷，杜绝抄袭！\n");
    for(int i=1;;i++){//无限循环，便于判断
        if(i%2==1){//判断是a减i，还是b减i
            a-=i;
        }else{
            b-=i;
        }
        if(a<0){
            printf("Vladik");//如果a先小于0,就输出Vladik
            return 0;
        }
        if(b<0){
            printf("Valera");//反之，输出Valera
            return 0;
        }
    }
}
```


---

## 作者：Chtholly_L (赞：0)

**概述**：

这道题比较简单，题意大概就是两个人轮流给互相糖，看谁的糖先没了，谁就输了。类似于拍卖会。

---
分析：

题目难就难在如何模拟这两个人轮流来给糖。其实我们可以发现，Vladik所给的糖永远都是奇数，而Valera所给的糖永远都是偶数，所以我们只需要对给的糖的数量判断是基数还是偶数就可以了。

---

话不多说，上代码。


```cpp
#include<iostream>
using namespace std;
int main()
{
	int a,b,ans=1;
	cin>>a>>b;
	for(int i=1;;i++)  //一直无条件循环
	{
		if(a<0)  //如果没有糖了
		{
			cout<<"Vladik"<<endl;  //对方赢了
			break;  //跳出循环
		}
		if(b<0)  //同上
		{
			cout<<"Valera"<<endl;
			break;
		}
		if(ans%2==1)a-=ans;  //如果是奇数， Vladik 给糖
		else if(ans%2==0)b-=ans;  //如果是偶数， Valera 给糖
		ans++;  //给糖的数量加一
	}
	return 0;  //结束程序
}
```

---

## 作者：int32 (赞：0)

[CF811A](https://www.luogu.com.cn/problem/CF811A/)

### 思路

模拟分配过程，对于每个回合分别减去给的糖数（如题），直到有人给不出糖即可。

注意**别人给的糖果不算自己的，不用考虑糖果增加的情况**。

### 代码

```cpp
int a, b;
int step=1;
signed main(){
	read(a),read(b);
	while(1){
		if(a<step) return puts("Vladik"),0;
		else a-=step++;//等同于 a-=step,++step;
		if(b<step) return puts("Valera"),0;
		else b-=step++;
	}
	return 0;
}
```

---

## 作者：thomas_zjl (赞：0)

这道题其实不用推式子，其实只要一个简单的模拟就可以了。

我们先来模拟第 $2$ 个样例。

```
7 6
```
因为题目中说送的糖不算自己的，所以糖数不会增加。

我们可以列个表。

| 步数 | 送的糖数 | $Vladik$ | $Valera$ |
| -----------: | -----------: | -----------: | -----------: | -----------: |
| $1$ | $1$ | $7-1=6$ | $7$ |
| $2$ | $2$ | $6$ | $7-2=5$ |
| $3$ | $3$ | $6-3=3$ | $5$ |
| $4$ | $4$ | $3$ | $5-4=1$ |
| $5$ | $5$ | $3-5=-2$ | $1$ |

由此我们可以发现，$Vladik$ 在第 $5$ 步就拿不出糖了。

我们也可以写出代码。

```
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,m;
	int zh=1;//zh代表某人给另一个人的糖数。
	int step=1;//step代表步数。
	scanf("%d%d",&n,&m);
	while(1){
		if(step%2==1)//我们通过上面的表发现，如果步数为奇数，那么vladik拿糖。
			n-=zh;
		else//如果不是奇数，那么valera就要拿糖了。
			m-=zh;
		if(n<0){//如果Vladik拿不出糖,输出vladic,跳出循环。
			printf("Vladik");
			break;
		}
		if(m<0){//如果Valera拿不出糖,输出valera,跳出循环。
			printf("Valera");
			break;
		}
		zh++;
		step++;
		//最后不要忘了吧zh和step加1。
	}
	return 0;
}
```




---

## 作者：艾恩葛朗特 (赞：0)

这题完全可以暴力穷举给对方糖的个数。

设一个变量flag，表示现在是谁给谁糖果。
如果这个人的糖果数小于需要给定的糖果数，那么跳出循环。

由于加了快读，超长代码发一拨
```cpp
#include<cstdio>
#include<string>
using namespace std;

int a,b,flag=1;

int read()//快读
{
	int x = 0, f = 1;
	char ch = getchar();
	for (; !isdigit(ch); ch = getchar())
	if (ch == '-') f = -1;
	for (; isdigit(ch); ch = getchar())
	x = x * 10 + ch - '0';
	return x * f;
}

int main()
{
	a=read();
	b=read();
	for (int i=1;;i++)
	{
		if (flag)
		{
			if (a<i)
			{
				printf("Vladik");
				return 0;
			}
			a-=i;
		}
		else 
		{
			if (b<i)
			{
				printf("Valera");
				return 0;
			}
			b-=i;
		}
		flag=(flag+1)%2;//改变状态
	}
	return 0;
}
```

---

