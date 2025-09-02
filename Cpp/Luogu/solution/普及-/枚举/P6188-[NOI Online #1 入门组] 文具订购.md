# [NOI Online #1 入门组] 文具订购

## 题目描述

小明的班上共有 $n$ 元班费，同学们准备使用班费集体购买 $3$ 种物品：

1. 圆规，每个 $7$ 元。
2. 笔，每支 $4$ 元。
3. 笔记本，每本 $3$ 元。

小明负责订购文具，设圆规，笔，笔记本的订购数量分别为 $a,b,c$，他订购的原则依次如下：

1. $n$ 元钱必须正好用光，即 $7a+4b+3c=n$。
2. 在满足以上条件情况下，成套的数量尽可能大，即 $a,b,c$ 中的最小值尽可能大。
3. 在满足以上条件情况下，物品的总数尽可能大，即 $a+b+c$ 尽可能大。

请你帮助小明求出满足条件的最优方案。可以证明若存在方案，则最优方案唯一。

 

## 说明/提示

#### 样例输入输出 3 解释

$a=2,b=4,c=1$ 也是满足条件 $1,2$ 的方案，但对于条件 $3$，该方案只买了 $7$ 个物品，不如 $a=1,b=2,c=6$ 的方案。 

#### 数据规模与约定

- 对于测试点 $1 \sim 6$，保证 $n \leq 14$。
- 对于测试点 $7 \sim 12$，保证 $n$ 是 $14$ 的倍数。
- 对于测试点 $13 \sim 18$，保证 $n \leq 100$。
- 对于全部的测试点，保证 $0 \leq n \leq 10^5$。

## 样例 #1

### 输入

```
1
```

### 输出

```
-1```

## 样例 #2

### 输入

```
14
```

### 输出

```
1 1 1```

## 样例 #3

### 输入

```
33
```

### 输出

```
1 2 6```

# 题解

## 作者：lzqy_ (赞：283)

## 和我一样初学OI的新手看过来了，不用算法、不用DP、不用循环甚至变量都只需两个！！！
### 最无脑代码推导过程：


#### 我们一个一个条件地分析：
 _**1、要花光所有的钱**：_ 
 
首先，三种文具的价格是$3,4,7$，通过证明，发现除了$n=1$,$n=2$,$n=5$以外，任何的价格$n$都可以被花光，所以这个条件并没有什么太大的约束力；

_**2、尽量配成更多套**_ 

一套的价钱是$14$元，所以这个规定就是要我们尽可能地买更多的整$14$元；

 _**3、尽量买更多的物品**_ ：

这个规定其实就是在我们买了尽可能多的整$14$元之后，剩余的钱再尽量拆分成$3$元或$4$元（因为$7=3+4$，这样买的物品数量就会减少，所以不买$7$元的东西）

好了，题目分析完了，我们归纳一下：


------------

```
ans=n/14;

n%=14;

if(n==?)

{

   cout<<ans<<" "<<ans+?<<" "<<ans+?;
   
   return 0;
   
}

if(n==?)

    ·
    ·
    ·
    ·

(注：由于是伪代码，所以？处是代表一个数字)
```

------------

看见了吗？其实这道题就是一个除法，再加上好多个$if$就解决了。。。

但是细心的朋友可能会发现，这个算法有一个漏洞：

如果买完尽量多的套数以后，剩下的是$1,2,5$元呢？这样不就不满足第一个条件了吗？

不用担心，这个问题很简单，我们只需要少配一套物品，再拿出14元来，不就可以花完钱了吗？

所有的问题都处理完了，无算法、无dp甚至无循环的代码就出现了：
```
#include <bits/stdc++.h>
using namespace std;
int main()
{
  int n,ans=0;//ans用来记录套数
  cin>>n;
  if(n==0)//若n=0，则直接输出答案；
  {
    cout<<0<<" "<<0<<" "<<0;
    return 0;
  }
  if(n<6 && n!=4 && n!=3)//若n无法分完，则直接输出答案；
  {
    printf("-1");
    return 0;
  }
  ans=n/14;
  n%=14;//本代码的核心部分（个人觉得），求套数
  if(n<6 && n!=4 && n!=3 && n!=0)
    ans--,n+=14;//若在套数最多时n分不完，套数-1；
    if(n==0)//若正好分完，直接输出三个套数
    {
    	cout<<ans<<" "<<ans<<" "<<ans<<endl;
    	return 0;
	}
   //准备，最长if特判就要来了：                                        
  if(n==3)
  {
    cout<<ans<<" "<<ans<<" "<<ans+1<<endl;
    return 0;
  }
  if(n==4)
  {
    cout<<ans<<" "<<ans+1<<" "<<ans<<endl;
    return 0;
  }
  if(n==6)
  {
    cout<<ans<<" "<<ans<<" "<<ans+2<<endl;
    return 0;
  }
  if(n==7)
  {
    cout<<ans<<" "<<ans+1<<" "<<ans+1<<endl;
    return 0;
  }
  if(n==8)
  {
    cout<<ans<<" "<<ans+2<<" "<<ans<<endl;
    return 0;
  }
  if(n==9)
  {
    cout<<ans<<" "<<ans<<" "<<ans+3<<endl;
    return 0;
  }
  if(n==10)
  {
    cout<<ans<<" "<<ans+1<<" "<<ans+2<<endl;
    return 0;
  }
  if(n==11)
  {
    cout<<ans<<" "<<ans+2<<" "<<ans+1<<endl;
    return 0;
  }
  if(n==12)
  {
    cout<<ans<<" "<<ans<<" "<<ans+4<<endl;
    return 0;
  }
  if(n==13)
  {
    cout<<ans<<" "<<ans+1<<" "<<ans+3<<endl;
    return 0;
  }
  if(n==15)
  {
    cout<<ans<<" "<<ans<<" "<<ans+5<<endl;
    return 0;
  }
  if(n==16)
  {
    cout<<ans<<" "<<ans+1<<" "<<ans+4<<endl;
    return 0;
  }
  if(n==19)
  {
    cout<<ans<<" "<<ans+1<<" "<<ans+5<<endl;
    return 0;
  }
  //是的，这样就没了（亲测，可以AC）
  return 0;
}
```
代码虽长，但是思路任何人都可以明白，并且只要$n$在整型范围内，都可以秒解。

写题解不易，觉得好的，留个赞再走呗~



---

## 作者：Elma_ (赞：66)

### 暴力
好多大佬都用dp或者其他解法做，还没看到有人用我这个方法，蒟蒻就自己写了一篇题解。

没错，就是我们最熟悉的——暴力枚举！

题目要求$a$，$b$，$c$的最小值尽可能大，所以就要让它们的最小值越接近$\frac{n}{14}$越好，如果$a$，$b$，$c$的最小值为$\frac{n}{14}$时无解，则让$a$,$b$,$c$的最小值为$n/14-1$，以此类推，直到有解为止，此时的解就满足了题目的第二个条件。

当然这还不是正解，题目还要求$a+b+c$尽可能大。

举两个例子：

- 当$n=7$时，可以分为一个$a$，或者一个$b$和一个$c$。
- 当$n=12$时，可以分为$3$个$b$，或者$4$个$c$。

显然可以得出结论，如果能拆成$c$就尽量拆$c$，如果不能再拆$b$。因为$a=b+c$，$a$都会被拆成一个$b$和一个$c$,所以此时$a$一定会是$a$，$b$，$c$中的最小值。

所以就有这样的解法：

从$\frac{n}{14}$开始往下枚举最小值，也就是$a$的个数。然后依次枚举$c$，$b$，一旦遇到有解就输出，结束程序。此时的解就是最优解。注意枚举范围，$b$最大为$\frac{n}{4}$，$c$最大为$\frac{n}{3}$。最后如果无解，输出$-1$。

### CODE
```cpp
#include <iostream>
#include <algorithm>
using namespace std;

int n;

int main(void)
{

	cin>>n;
	
	if(n == 0)//特判
	{
	    cout<<"0 0 0"<<endl;
	    return 0;
	}
	
	for(int p=n/14;p>=0;p--)//枚举最小值，也就是a的个数
	{
			for(int j=p;j<=n/4;j++)//枚举b
				for(int k=p;k<=n/3;k++)//枚举c
					if(p*7+j*4+k*3 == n)//如果有解
					{
						cout<<p<<" "<<j<<" "<<k<<endl;
						return 0;//输出，结束程序
					}
	}
	
	cout<<"-1"<<endl;//无解输出-1
	return 0;//完美AC~
}
```

### 提醒
$n=0$坑了我一把，一定记得特判。

上面的代码有三个$for$，看起来很可怕，其实不然。因为我们根本不需要枚举$n^3$次，一旦找到第一个最优解程序就会推出。所以这个代码只需要$63ms$，甚至比其他的解法速度更快。

祝大家：$AKIOI!$

---

## 作者：Minecraft万岁 (赞：17)

我们看一下这个方程式子$7a+4b+3c=n$ 第一反应 $:$ ~~毒瘤~~不就一个枚举吗 但是暴力枚举肯定是不行的 所以我们要优化~~枚举~~暴力   
首先我们枚举 $a$ 从 $0$ 开始 到 $a \times 7 \leq n$ 不必枚举到 $n$  
然后 $a$ 就变为已知的 则有 
$$4b+3c=n-7a$$  
然后我们再来枚举 $b$ 从 $0$ 开始 到 $4 \times b \leq n-a \times 7$ ~~老套路~~  
最后我们知道了 $a$ 和 $b$ 我们就可以算 $c$ 了    
$$3c=n-7a-4b$$
$$c=(n-7a-4b) \div 3$$
但是有一点需要注意 
### 既然要正好把 $n$ 元钱买完 所以 $c$ 必须是整数  
~~所以特判一下就可以了呀~~  
到这里 我们可以算出每一个合法解 我们最后根据题目的要求比较一下哪一个最优 最后输出就行啦   
实测 $n=10^5$ 时 程序 $0.9s$  不会超时  
双手奉上代码 


------------  
```cpp
#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
int n;//n元钱 
int ansa,ansb,ansc;//答案(最优)的 a b c 
int mnans,mntmp;//最优答案的最小值 和  新鲜出炉的 a b c 的最小值 
int totans,tottmp;//最优答案的个数总和 和 新鲜出炉的 a b c 的总和 
bool flag;//判断有没有合法解 
inline void read(int &x)//快读 
{
	int f;char c;
	for (f=1,c=getchar();c<'0'||c>'9';c=getchar()) if(c=='-') f=-1;
	for (x=0;c<='9'&&c>='0';c=getchar()) x=x*10+(c&15);x*=f;
}
inline int mn(int _x,int _y)
{
	return _x<_y?_x:_y;
}
inline int mx(int _x,int _y)
{
	return _x>_y?_x:_y;
}
inline int ab(int _x)
{
	if(_x<0) return -_x;
	else return _x;
}
int main()
{
//	freopen("order.in","r",stdin);//为文件输入输出 
//	freopen("order.out","w",stdout);
	ansa=ansb=ansc=-1;//初始化肯定是最小 -1 就够了 
	totans=-3;
	mnans=-1;
	read(n);//读入 
	for(int a=0;a*7<=n;a++)//第一层循环 求 a 
	{
		int upb=n-7*a;//求出 b 的上限 
		for(int b=0;b*4<=upb;b++)//再枚举 b 
		{
			int c=n-7*a-4*b;//算一下c 但并没有除3 
			if(c%3!=0) continue;//看看是不是整数 
			flag=true;//到这里就有合法解了 
			c/=3;//最后的c是要除3的 
			mntmp=mn(mn(a,b),c);//新鲜出炉的 a b c的最小值 
			if(mntmp>=mnans)//题目条件1 
			{
				if(mntmp>mnans)//不用继续比较条件2了 
				{
					ansa=a;//更新 
					ansb=b;
					ansc=c;
					mnans=mntmp;
					totans=a+b+c;
				}
				else//在比较条件2 
				{
					tottmp=a+b+c;//新鲜出炉的 a b c的总和 
					if(tottmp>totans)//更优解 
					{
						ansa=a;//更新 
						ansb=b;
						ansc=c;
						mnans=mntmp;
						totans=tottmp;
					}
				}
			}
		}
	}
	if(flag) printf("%d %d %d\n",ansa,ansb,ansc);//有解输出最优的 
	else printf("-1\n");//没有就-1呗 
	return 0;
}

```
  

---

## 作者：lndjy (赞：15)

###  P6188 [NOI Online 入门组]文具订购 题解

根据题意，有3个约束条件：

1.钱必须正好用光，$7a+4b+3c=n$ 。

2.在满足以上条件情况下，成套的数量尽可能大，即 $a,b,c$ 中的最小值尽可能大。

3.在满足以上条件情况下，物品的总数尽可能大，即 $a+b+c$ 尽可能大。

对于第一个要求，在枚举最后一个物品时，要判断剩下的钱 $mod$ 价钱是否为0，如果不是0，就会剩余或不够。

对于第二个要求,可以先枚举有几个完整的套，每套14元。

对于第三个要求，因为 $7=4+3$ ,所以不成套的不能买a，因为买a不如一个b一个c。关于b和c买几个，可以枚举取最大值，注意钱没用光时不算最大值。

代码（含有详细注释）

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int inline read()
{
	int ans=0,f=1;
	char ch=getchar();
	while(!isdigit(ch))
	{
		if(ch=='-')
		f=-1;
		ch=getchar();
	}
	while(isdigit(ch))
	{
		ans=ans*10+ch-'0';
		ch=getchar();
	}
	return ans*f;
}
int main()
{
	//freopen("order.in","r",stdin);
	//freopen("order.out","w",stdout);
	int n=read();
	int now;
	int ansa,ansb,ansc;
	bool f=0;
	int maxx=0;
	for(int i=n/14;i>=0;i--)//i为有几套
	{
		now=n-(i*14);//now为不成套剩余多少钱，总共减去成套花费的
		ansa=i;
		ansb=i;
		ansc=i;//初始值，成套的a，b，c都是i个
		for(int j=0;j*3<=now;j++)//枚举c，这里j是c
		{
			if(((now-(j*3))%4)==0)//((now-(j*3))是要用来花b的价钱，%4判断有没有剩余
			{
				f=1;//标记可行方案，取最大值后输出
				if(3*i+j+((now-(j*3))/4)>ansa+ansb+ansc)//如果当前方案数比之前的个数多，选择当前的。((now-(j*3))是要用来花b的价钱，/4表示买几个
				{
					ansa=i;
					ansb=i+((now-(j*3))/4);
					ansc=j+i;//更新答案
				}
			}
		}
		if(f)//如果有方案就输出，套数更少的不满足第二条要求，所以直接退出
		{
			cout<<ansa<<" "<<ansb<<" "<<ansc;
			return 0;
		}
	}
	cout<<-1;//无解没有可行方案
	return 0;
}
```


---

## 作者：江户川·萝卜 (赞：13)

以此题解来纪念**9h**一场只有**3T**的PJ比赛  
~~还不是C某F的YB服务器被我们ZJ PJ组的童鞋炸了4次~~  
咳咳，正式开始题解~

----
这一题，对于数学好(?)的我，一看就发现了问题  

 _订购的原则依次如下：_  
1. n 元钱必须正好用光，即 $7a+4b+3c=n$
2. 在满足以上条件情况下，成套的数量尽可能大，即$a,b,c$中的最小值尽可能大。
3. 在满足以上条件情况下，物品的总数尽可能大，即$a+b+c$尽可能大。  

然后我们可以分成三个步骤来解。

### $Step 1:$  满足第1条件，不能满足输出$-1$
---
$7a+4b+3c=n$  在这个等式中，我们发现，$7=4+3$，由于现在讨论的是能否正好用光，$a$无论是几，都能用$3$和$4$拼凑出来，可以暂时忽略。  
于是等式剩下了$4b+3c=n$,
在《可怕的科学》系列丛书中的《超级公式》一书有提到：  
我们用$H$来代表不可能凑出的最大金额，$x,y$来代表两个价格（即题中的$3,4$），则：
$$H=xy-x-y$$
这个公式在此书中被称为：麦克卡拉公式$(Mac$ $Cullagh's$ $formula)$。~~我不会证明~~  
将$3,4$代入公式，得
$$H=3*4-3-4$$
$$H=5$$

我们再列出下表：  

| n | 能否满足第1条件 | 怎样满足 |
| :----------: | :----------: | :----------: |
| 0 | 能 | 0 0 0 |
| 1 | 不能 | - |
| 2 | 不能 | - |
| 3 | 能 | 0 0 1 |
| 4 | 能 | 0 1 0 |
| 5 | 不能 | - |
~~（观众：这些我们都知道啊）~~  
！！请注意$n$可以$=0$，题中说明：  
_对于$100\%$的数据，保证 $0 \leq n \leq 10^5$_  
~~我就是这么被坑的~~  
所以我们可以写一个特判：
```cpp
if(n!=0&&n<3||n==5){
	cout<<-1;
	return 0;
}
```

### $Step 2:$ 满足第2条件，成套
---
$very$ $easy$，不就是$a,b,c=floor(n/(7+4+3))$嘛！  
~~好的我们过了~~  
代码片段：
```cpp
a=b=c=n/14;
```

### $Step 3:$ 满足第3条件 打表大法好啊
---
接下来，我们来处理$n/14$后的余数  
我实在想不出有什么好的解法，于是我打表。。。  

| 余数 | a | b | c |
| :----------: | :----------: | :----------: | :----------: |
| 0 | 0 | 0 | 0 |
| 1 | -1 | -1 | 4 |
| 2 | -1 | 0 | 3 |
| 3 | 0 | 0 | 1 |
| 4 | 0 | 1 | 0 |
| 5 | -1 | 0 | 4 |
| 6 | 0 | 0 | 2 |
| 7 | 0 | 1 | 1 |
| 8 | 0 | 2 | 0 |
| 9 | 0 | 0 | 3 |
| 10 | 0 | 1 | 2 |
| 11 | 0 | 2 | 1 |
| 12 | 0 | 0 | 4 |
| 13 | 0 | 1 | 3 |

策略：尽量多买笔记本(c)，如若不能恰好用光，则舍二（第2条件）求三（第3条件）。

## C++代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,b,c;
int m[14][3]
{
	0,0,0,
	-1,-1,4,
	-1,0,3,
	0,0,1,
	0,1,0,
	-1,0,4,
	0,0,2,
	0,1,1,
	0,2,0,
	0,0,3,
	0,1,2,
	0,2,1,
	0,0,4,
	0,1,3,
};
int main(){
	//freopen("order.in","r",stdin);
	//freopen("order.out","w",stdout); 
	cin>>n;
	if(n!=0&&n<3||n==5){
		cout<<-1;
		return 0;
	}
	a=b=c=n/14;
	n%=14;
	cout<<a+m[n][0]<<" "<<b+m[n][1]<<" "<<c+m[n][2];
	return 0;
}
```
$end.$

---

## 作者：Diamiko (赞：11)

 #### 更新日志

 ### Update 2020/3/8 :删除代码预编译指令（？）
 	预编译指令应该是指头文件和switch那段吧，已经修改了，应该能审过了吧，麻烦管理员再审一遍
    

------------
 
 ## 我也不会这题的正解，但是这篇题解致力于教大家如何在考场上尽量多骗分√
 
 #### 有时候，我们往往不能像那些神犇一样轻松切题，但我们作为蒟蒻也有蒟蒻的智慧——骗分！
 
 话说这题也太好骗了点
 

 
 [题目传送门](https://www.luogu.com.cn/problem/P6188)
 
#### 数据规模与约定
对于测试点 $1∼6$，保证 $n≤14$。

对于测试点 $7∼12$，保证$n$ 是 $14$ 的倍数。

对于测试点 $13∼18$，保证 $n≤100$。

对于 $100%$ 的数据，保证$0≤n≤10^5$
 
 ### Step 1. $30pts$√
 
 看到测试点$1∼6$了吗，保证$n<=14$，那么我们就可以轻松的拿到这些分，只要手算写个$switch$就$ok$。
 
 当然，必要性后面再具体讲述，还可以进行优化
 
 ```cpp
 if(n<14)
	{
		if(n<3)
		{
			puts("-1");
		}
		else//7 4 3
		{
			switch(n)
			{
				case 3:
					puts("0 0 1");break;
				case 4:
					puts("0 1 0");break;
				case 5:
					puts("-1");   break;
				case 6:
					puts("0 0 2");break;
				case 7:
					puts("0 1 1");break;
				case 8:
					puts("0 2 0");break;
				case 9:
					puts("0 0 3");break;
				case 10:
					puts("0 1 2");break;
				case 11:
					puts("0 2 1");break;
				case 12:
					puts("0 0 4");break;
				case 13:
					puts("0 1 3");break;
				default:
					break;
			}
		}
		return 0;
	}
 ```
 ccf竟然如此良心？
 
 ### Step 2. $60pts$√
 
 看到测试点$7∼12$，保证$n$是$14$的倍数，那么我们就要思考，为什么特意指出$14$呢？看样例我们就明白了，$n=14$时，$a=b=c=1$, 那么很容易想出来，当$n$是$14$的倍数时，$a,b,c$也是原来的多少倍。比如我们可以手算一下，$n=28$时，$a=b=c=2$；$n=98$时，$a=b=c=7$。
 
 因为题目的要求是要使配套尽可能的多，没有什么情况是比三个一样配套多的了
 
 ```cpp
 if(n%14==0)
{
	printf("%d %d %d\n",n/14,n/14,n/14);
	return 0;
}
 ```
 ccf竟如此良心？
 
 ### Step 3. $90pts$√
 
 我们看到测试点$13∼18$，保证 $n≤100$
 
 想不出正解我们可以枚举啊，$100^3$绝对不会超时
 
 我们枚举$a,b,c$三个变量分别从$0∼100$，枚举出所有可能的情况，把符合条件的放进答案数组，最后再根据题目要求进行排序，岂不美哉？
 
 注意点：世上有$10$种人，$1$种是$for$从$0$开始，$1$种是$for$从$1$开始
 
 但这里我们为什么要枚举从$0$开始
 
 因为有可能出现匹配不了一套的情况
 
 ~~反正101^3也炸不了~~
 
 还有就是对于$-1$情况的判断，如果枚举一遍压根没有合适的解，我们就输出$-1$
 
 问题在于，怎么对数组进行排序？
 
 大家要是都做过[P1093奖学金](https://www.luogu.com.cn/problem/P1093)，了解结构体数组排序的话我就不多说了，其实重载运算符也可以~~我怕麻烦写的排序函数~~
 
 #### 结构体及变量定义
 ```cpp
 bool flag;//记录有没有解
struct TYK
{
	int a,b,c;
}tyk[int(1e6+5)];
int cnt;//记录解的数量
 ```
 ~~话说好像用不到flag，cnt为0就没有解~~
 
 #### 枚举
 ```cpp
 for(register int a=0;a<=100;a++)
{
	for(register int b=0;b<=100;b++)
	{
		for(register int c=0;c<=100;c++)
		{
			if(7*a+4*b+3*c==n)
			{
				flag=1;
				addAns(a,b,c);
			}
		}
	}
}
 ```
 
#### 添加答案

```cpp
void addAns(int a,int b,int c)
{
	tyk[++cnt].a=a;
	tyk[cnt].b=b;
	tyk[cnt].c=c;
}
```

#### 排序及输出

```cpp
if(flag==0)
{
	puts("-1");
	return 0;
}
sort(tyk+1,tyk+cnt+1,cmp);
TYK ans=tyk[1];
printf("%d %d %d\n",ans.a,ans.b,ans.c);
```

#### cmp排序函数

```cpp
int my_min(int a,int b,int c)
{
	return min(min(a,b),c);//三个数中求最小
}
bool cmp(TYK l,TYK r)
{
	int l_min_abc=my_min(l.a,l.b,l.c);
	int r_min_abc=my_min(r.a,r.b,r.c);
	int l_sum_abc=l.a+l.b+l.c;
	int r_sum_abc=r.a+r.b+r.c;
	if(l_min_abc==r_min_abc)
		return l_sum_abc>r_sum_abc;//使三个数之和尽量大
	return l_min_abc>r_min_abc;//使三个数中最小值尽量大
}
```

那么，$90pts$就轻松到手了

~~我也不晓得为啥我在洛谷测的85分~~

### Step 4. n>100

~~不会，输出-1吧~~

### 优化

~~其实也没什么好优化的，反正都是暴力~~

但我们可以轻松的发现一个问题，当$n<=100$时我们可以枚举，那为什么$n<=14$时我们要手算？

对呀，为什么。 。 。

那么我们可以直接把switch删掉

对了，我比赛交的时候没删switch，我也没测试删了对不对~~AC率宝贵啊~~

## 最后是整个代码（考场代码，比较丑陋）

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
bool flag;
struct TYK
{
	int a,b,c;
}tyk[int(1e6+5)];
int cnt;
//int a[int(1e6+5)],b[int(1e6+5)],c[int(1e6+5)];
void addAns(int a,int b,int c)
{
	tyk[++cnt].a=a;
	tyk[cnt].b=b;
	tyk[cnt].c=c;
}
int my_min(int a,int b,int c)
{
	return min(min(a,b),c);
}
bool cmp(TYK l,TYK r)
{
	int l_min_abc=my_min(l.a,l.b,l.c);
	int r_min_abc=my_min(r.a,r.b,r.c);
	int l_sum_abc=l.a+l.b+l.c;
	int r_sum_abc=r.a+r.b+r.c;
	if(l_min_abc==r_min_abc)
		return l_sum_abc>r_sum_abc;
	return l_min_abc>r_min_abc;
}
int main()
{
//	freopen("order.in","r",stdin);
//    freopen("order.out","w",stdout);
	
	scanf("%d",&n);
	if(n%14==0)
	{
		printf("%d %d %d\n",n/14,n/14,n/14);
		return 0;
	}
	if(n<=100)
	{
		for(register int a=0;a<=100;a++)
		{
			for(register int b=0;b<=100;b++)
			{
				for(register int c=0;c<=100;c++)
				{
					if(7*a+4*b+3*c==n)
					{
						flag=1;
						addAns(a,b,c);
					}
				}
			}
		}
		if(flag==0)
		{
			puts("-1");
			return 0;
		}
		sort(tyk+1,tyk+cnt+1,cmp);
		TYK ans=tyk[1];
		printf("%d %d %d\n",ans.a,ans.b,ans.c);
		return 0;
	}
	if(n>100)
	{
		puts("-1");
		return 0;
	}
//    fclose(stdin);
//	fclose(stdout);
	return 0;
} 
```
# 完结撒花！
写题解不易，望过审

---

## 作者：pyqpyq (赞：8)

注：下面的 $(x,y,z)$ 表示一个 $a=x,b=y,c=z$ 的方案。
# 题目分析
首先我们可以发现一件有趣的~~小学一年级都会的~~事情：$3+4=7$

~~好的此题完结。~~

这意味着什么？一个圆规可以拆成一支笔和一本笔记本，反过来，一支笔和一本笔记本也可以合成一个圆规。

那么所有的方案 $(x,y,z)$ 都可以通过拆圆规来变成 $(0,y+x,z+x)$，也就是说每个方案都对应着且仅一个 $x=0$ 的方案。

由于这个操作是可逆的，所以所有的 $x=0$ 的方案就把所有合法方案分成了若干个方案组，而每个方案组中都有且仅有一个方案 $x=0$。

因为我们求出所有的 $(0,y,z)$ 便可通过 $(x,y-x,z-x)$ 得轻易得出该方案组所有方案，所以我们可以使用以下策略：

求出所有方案组中的组内最优解，然后再通过比较组内最优解得全局最优解。
# Step 1
先考虑如何找出所有方案组。

当然，我们没必要列举出所有方案组中的方案，这样会TLE+MLE。我们只需求出每个方案组中的代表 $(0,y,z)$ 即可。

那怎么求呢？

把 $a=0,b=y,c=z$ 代入 $7a+4b+3c=n$ 得：$4y+3z=n$

这个不就是二元一次不定方程吗？用扩展欧几里得即可。

不会也没关系，$n\le10^5$，枚举 $y$ 即可。
# Step 2
然后考虑如何求一个方案组中的最优解。

题目要求最优解满足三个条件：
1. $a+b+c=n$

2. 满足条件 1 的情况下，$\min(a,b,c)$ 最大。

3. 满足条件 2 的情况下，$a+b+c$ 最大。

条件一不用管，主要看条件二和条件三。

由于一个方案组中的方案均可表示为 $(x,y-x,z-x)$，而  $y,z\in\mathbb N$，所以 $x\le\min(y,z)$。

注意到一个性质：在一个方案组中，$a+b$ 和 $a+c$ 是恒等的且在当前方案组中其值分别为 $y$ 和 $z$，而 $\min(a,b,c)$ 又要最大，所以最好的情况是 $x$ 和 $\min(y-x,z-x)$ 尽量接近。而刚开始 $x=0$，所以要把 $\min(y,z)$ 均摊给 $x$。

但同时又要满足 $a+b+c$ 最大，而肯定是 $a$ 越小时方案更优，这样就有更多的钱去买别的。所以遇到 $\min(y,z)$ 为奇数我们就把它向下取整赋给 $x$。

所以最优解就是：
$$(\frac{\min(y,z)}{2},y-\frac{\min(y,z)}{2},z-\frac{\min(y,z)}{2})$$
# Step 3
求全局最优解就不用说了吧，先保存一份最优解，如果当前答案比之前的最优解更优就有当前答案更新它。

~~我考场上竟然又用 sort 求最优解。~~

总复杂度 $O(n)$，可以通过该题数据。


当然您也许看到了最小值的最大值，可以二分答案来吊打这篇题解。（我太蒻了没试过）
# 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define MAXN 100011
int n,l,t,as,bs,cs,a,b,c;
inline int minn(int x,int y)
{
	return x<y?x:y;
}
int main()
{
	scanf("%d",&n);
	for(int i=0;4*i<=n;++i)//枚举y
		if((n-4*i)%3==0)//z是否为整数
		{
			a=minn(i,(n-4*i)/3)/2;
			b=i-minn(i,(n-4*i)/3)/2;
			c=(n-4*i)/3-minn(i,(n-4*i)/3)/2;
			if(minn(a,minn(b,c))==minn(as,minn(bs,cs))?a+b+c>as+bs+cs:minn(a,minn(b,c))>minn(as,minn(bs,cs)))//三目运算符……
			{
				as=a;
				bs=b;
				cs=c;
			}
			t=1;
		}
	if(!t)//判断有无解
		printf("-1");
	else
		printf("%d %d %d",as,bs,cs)
	return 0;
}//说句闲话：这不是我考场代码
```

---

## 作者：Misaka屮Mikoto (赞：5)

### 这道题的大概算法：DP+贪心
### 主要是DP

开三个数组，分别是需要a,b,c的数量

然后再开一个bool数组，用来标记当前的钱数是否合法 ~~能不能花完~~

然后主要的说明就写到代码里面去了~~有点亿点暴力~~

```cpp
#include<buyaochaotijie.h>
#include<iostream>
#include<stdio.h>
#include<math.h>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;
bool tr[100001];
int a[100001],b[100001],c[100001],n;//a,b,c,分别存储3元，4元，7元的数量
int main()
{
	tr[0]=true;//当只有0元时，数据合法（能花完）
	scanf("%d",&n);
	for(int i=0;i<=n;i++)//循环n遍，a[i],b[i],c[i]存储的是当钱数为i时的最佳方案
	{
		if(i>=14&&tr[i-14])//能三个都买的就全买（tr[i-14]是判断如果买了三支笔，钱能否花完）
		{
			tr[i]=true;//这个i元是可以被花完的
			a[i]=a[i-14]+1;//将每一种文具的个数加1
			b[i]=b[i-14]+1;
			c[i]=c[i-14]+1;
		}
		else//否则先挑便宜的买
		{
			if(i>=3&&tr[i-3])//判断3元
			{
				tr[i]=true;//这个i元是可以被花完的
				a[i]=a[i-3]+1;//三元文具加1（下面代码一样）
				b[i]=b[i-3];
				c[i]=c[i-3];
			}
			else
			{
				if(i>=4&&tr[i-4])//判断4元
				{
					tr[i]=true;
					a[i]=a[i-4];
					b[i]=b[i-4]+1;
					c[i]=c[i-4];
				}
				else
				if(i>=7&&tr[i-7])//判断7元
				{
					tr[i]=true;
					a[i]=a[i-7];
					b[i]=b[i-7];
					c[i]=c[i-7]+1;
				}
			}
			//如果这四种选择方案都不行，这这个i元不合法，tr[i]就不会被更新为true
		}
	}
	if(tr[n])printf("%d %d %d",c[n],b[n],a[n]);//如果n元合法，则输出方案（输出顺序是c,b,a
	else printf("-1");//如果n不能被花完，则输出-1
	return 0;
}

```

### 提交noinoine的时候要加上freopen

---

## 作者：wpj20241021005 (赞：4)

这一道题，我试过暴力，但很不幸的是，到了十万就炸了，所以，我就开始想简便方法。

因为是优先成套，所以我们可以首先默认所有钱花的时候是成套的，也就是a=b=c=n/14,而剩下来的钱呢，我们可以通过加减来使其正好用完且还要注意最多。

n%14==1时，我们可以将a和b减1，这样就多了12，c就加4.

n%14==2时，我们将a-1，多了9，c就加3.

n%14==3时，我们直接c+1.

n%14==4时，我们直接b+1

n%14==5时，我们可以a-1，c+4

n%14==6时，我们c+2

n%14==7时，我们可以b+1，c+1

n%14==8时，我们可以b+2

n%14==9时，我们可以c+3

n%14==10时，我们可以a+1，c+1

n%14==11时，我们可以a+1，b+1

n%14==12时，我们可以c+4

n%14==13时，我们可以b+1，c+3

然后表就出来了

这就是我的代码：

```
#include<bits/stdc++.h>
using namespace std;
long long n,sum,k,s[14][3]=
{{0,0,0},{-1,-1,4},{-1,0,3},{0,0,1},
{0,1,0},{-1,0,4},{0,0,2},
{0,1,1},{0,2,0},{0,0,3},
{1,0,1},{0,2,1},{0,0,4},{0,1,3}};//核心的表
int main()
{
	cin>>n;
	sum=n%14;
	k=(n-sum)/14;//平均分
	int a=k+s[sum][0],b=k+s[sum][1],c=k+s[sum][2]; 
	if (a>-1&&b>-1&&c>-1)
		cout<<a<<" "<<b<<" "<<c<<endl;
	else
	  	cout<<-1<<endl;
	return 0;//撒花
}
```


---

## 作者：Miraik (赞：3)

### UPDATE:2020.9.18 修正Latex

看到各位dalao的做法，蒟蒻深感佩服，只好贴上自己卑微的暴力

由题意可知：

1.钱必须正好用光，即 $7a+4b+3c=n$ 。

2.在满足以上条件情况下，成套的数量尽可能大，即 $a,b,c$ 中的最小值尽可能大。

3.在满足以上条件情况下，物品的总数尽可能大，即  $a+b+c$ 尽可能大。

## 思路

既然要求 $7a+4b+3c=n$ 的前提下成套的数量尽可能大，那我们就尽可能凑更多套，也就是 $\frac{n}{14}$ ，然后再将剩下的钱凑成尽可能多的 $3$ 与 $4$ 的和（注意没有 $7$ ，因为 $7=3+4$ ，而条件3要求 $a+b+c$ 尽可能大，所以 $3+4$ 显然更优。

但是，上面的做法不是正确的

### 当余数为1，2，5时，无法凑成3与4的和！

因此这种情况下，我们只能转求其次，少凑一套（也就是 $\frac{n}{14}-1$ 套）再将 $14+n \bmod 14 $作拆分

那余数如何拆分呢？

```
1+14=3+3+3+3+3
2+14=3+3+3+3+4
3=3
4=4
5+14=3+3+3+3+3+4
6=3+3
7=3+4
8=4+4
9=3+3+3
10=3+3+4
11=3+4+4
12=3+3+3+3
13=3+3+3+4
```

最后是完整的代码：

```cpp
#include<cstdio>
#include<iostream>
using namespace std;
inline int read(){
	char c=getchar();int x=0;
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return x;
}
int n,a,b,c;
int main(){
	//freopen("order.in","r",stdin);
	//freopen("order.out","w",stdout);
	n=read();
	if(n==1||n==2||n==5){
		puts("-1");
		return 0;
	}
	if(n%14==0)
	    a=b=c=n/14;
	if(n%14==1)
		a=b=n/14-1,c=n/14+4;
	if(n%14==2)
		a=n/14-1,b=n/14,c=n/14+3;
	if(n%14==3)
		a=b=n/14,c=n/14+1;
	if(n%14==4)
	    a=c=n/14,b=n/14+1;
	if(n%14==5)
		a=n/14-1,b=n/14,c=n/14+4;
	if(n%14==6)
	    a=b=n/14,c=n/14+2;
	if(n%14==7)
		a=n/14,b=c=n/14+1;
	if(n%14==8)
		a=c=n/14,b=n/14+2;
	if(n%14==9)
	    a=b=n/14,c=n/14+3;
	if(n%14==10)
	    a=n/14,b=n/14+1,c=n/14+2;
	if(n%14==11)
	    a=n/14,b=n/14+2,c=n/14+1;
	if(n%14==12)
		a=b=n/14,c=n/14+4;
	if(n%14==13)
		a=n/14,b=n/14+1,c=n/14+3;
	printf("%d %d %d\n",a,b,c);
	return 0;
}

```


---

## 作者：wjh_ (赞：3)

### 前言
竟然没有看到和我一样的暴力解法，也来发一发题解。  
不过我不开O2只有95分，开了O2才能AC。(O2是个好东西  

---
我的思路就是暴力枚举+模拟，**注意物品的个数可以是0**：  
- 第一层循环圆规（7元）个数， $0\le i\le \large\frac{n}{7}$  
- 第二层循环笔（4元）的个数， $0\le j \le \large\frac{n-7i}{4}$  
- 于是我们可以知道，笔记本计算公式是 $\large\frac{n-7i-4j}{3}$  

接下来按题意模拟即可。

---
含有详细注释的代码：  
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,ans=-1,ana,anb,anc,ans1,ans2;
//ans存是否找到答案,ana,anb,anc存最优情况下3种物品的个数
//ans1存ana,anb,anc的最小值,ans2存ana+anb+anc的和
int main() {
//	freopen("order.in","r",stdin);
//	freopen("order.out","w",stdout);
	scanf("%d",&n);
	for (int i=0;i<=n/7;i++) { //循环圆规
		for (int j=0;j<=(n-7*i)/4;j++) { //循环笔
			if ((n-7*i-4*j)%3==0) { //判断钱是否花光
				int k=(n-7*i-4*j)/3; //笔记本个数
				int minn=min(i,min(j,k)); //现循环的3种物品的最小值
				if (ans==-1) {//如果还没有答案,更新答案
					ana=i;
					anb=j;
					anc=k;
					ans=1;
					ans1=minn;
					ans2=i+j+k;
				}
				else if (minn>ans1) { //如果最小值更大,更新答案
					ana=i;
					anb=j;
					anc=k;
					ans=1;
					ans1=minn;
					ans2=i+j+k;
				}
				else if (minn==ans1) { //如果最小值一样大
					if (i+j+k>ans2) { //如果物品总数更多
						ana=i;
						anb=j;
						anc=k;
						ans=1;
						ans1=minn;
						ans2=i+j+k;
					}
				}
			}
		}
	}
	if (ans==-1) {//如果仍然没有答案
		cout<<ans<<endl;//输出-1
	}
	else {
		cout<<ana<<" "<<anb<<" "<<anc<<endl;//输出最优答案
	}
}
```

---

## 作者：Sham_Sleep (赞：3)

看到没有人发题解，其实本蒟蒻也是慌的一批，因为感觉我的做法很玄学。可是AC了，那我就来水一发题解了。

本蒟蒻的核心思想：部分和完全背包+贪心

由题目中的第一个条件可知，我们必须满足所买的东西组成给定的整数

完全背包可以解决求几个物品能的价值能否构成一个新的价值。

其做法是：套用完全背包的模板，然后将dp数组除dp[0]除外全部初始化成一个不可能达到的数

这样进行背包运算时，那些不可能组成的数是永远不会被更新的

所以大致思路出来了，可是我们应该如何套用呢？

很简单，我们要满足题目中的第二个条件：套装尽量的多。

所以我们可以先将已有钱除以14，代表当前最多可以有多少套。

然后拿余下的钱去跑一遍dp，如果不行就加上一个14，然后再去跑一趟dp。直到已经把所有套装的钱拆开都还不行，就说明题目无解，输出-1。

最后注意的是跑dp的过程中记录一下各种文具的数量

本蒟蒻AC代码

```
#include <stdio.h>
#include <iostream>
#include <memory.h>
using namespace std;

struct node{
	int num[4];
	int s;
};

int n;
int maxx;
int sum;
int w[4] = {0 , 7 , 4 , 3};
node f[100005];

int dp(int s)
{
	for(int i = 1; i <= s; ++i){
		f[i].num[1] = -999999;
		f[i].num[2] = -999999;
		f[i].num[3] = -999999;
		f[i].s = -99999999;
	}
	for(int i = 1; i <= 3; ++i){
		for(int j = w[i]; j <= s; ++j){
			if(f[j - w[i]].s + 1 > f[j].s)
			{
				f[j] = f[j - w[i]];
				++f[j].num[i];
				++f[j].s;
			}
		}
	}
	if(f[s].s > 0) return 1;
	else return 0;
}

int main()
{
	scanf("%d" , &n);
	maxx = n / 14;
	sum = n % 14;
	if(!sum)
	{
		printf("%d %d %d" , maxx , maxx , maxx);
		return 0;
	}
	for(int i = 0 ; i <= maxx; ++i){
		int s = sum + i * 14;
		int ff = dp(s);
		if(ff)
		{
			printf("%d %d %d" , maxx - i + f[s].num[1] , maxx - i + f[s].num[2] , maxx - i + f[s].num[3]);
			return 0;
		}
		memset(f , 0 , sizeof(f));
	}
	printf("-1"); 
}
```
支持一下本蒟蒻吧QAQ

---

## 作者：BCZSX (赞：2)

## P6188 [NOI Online 入门组]文具订购 题解

~~看到没有用二分的题解，我就来水一篇了……~~

从头开始讲起吧

### 90分做法（~~好可怕，部分分那么多……~~

对于第1~6个测试点和第13~18个测试点，我们可以直接用$O(n^3)$的做法直接暴力枚举每一种文具的数量，然后得到符合题意的答案就可以了……

对于第7~12个测试点，我们发现$n$是$14$的倍数，恰好$7+4+3=14$，所以3种文具可以购买相同的数量。可以证明，在$n$为$14$的倍数这种情况下，如果这三种文件的件数不一样，则这三种物品购买的最小值必定小于$\frac{n}{14}$。所以这种情况可以直接输出三个$\frac{n}{14}$。

### 100分做法

我们可以通过二分枚举最小值，然后分别对圆规和笔，圆规和笔记本，笔和笔记本的可能多出的个数进行枚举，这样我们就可以得出每种文具的件数，最后再根据题意选出最佳答案。注意要判断是否有合法的答案，否则合法答案可能会被不合法答案给覆盖掉（~~我因为这个问题调了半小时……~~


### 代码

```cpp
#include <cstdio>
#include <iostream>
#include <cstdlib>

using namespace std;

int n, ans1, ans2, ans3, anssum, ansmin = -1;//ans1,ans2,ans3,anssum,ansmin分别记录三种文具的答案，文件件数总和，三种文件件数的最小值
bool flag;

bool check(int x)
{
    int p = n - 14 * x, t;//p记录剩余的钱数，t记录合法答案来自哪种方案
    bool f[4] = {0, 0, 0, 0};//记录是否有合法答案
    int k1[4], k2[4], k3[4], sum;//前三个数组分别记录三种情况的件数，sum记录和
    k1[1] = x, k2[1] = 0, k3[1] = 0;//初始化
    for (int i = 0; i <= p / 4; ++ i)//枚举
    {
        if ((p - i * 4) % 3 == 0)如果有合法解
            if (i + (p - i * 4) / 3 > k2[1] + k3[1])如果比原答案更优，则更新
                k2[1] = i, k3[1] = (p - i * 4) / 3, f[1] = 1;
    }
    if (f[1])//如果有合法解再更新
        sum = k1[1] + k2[1] + k3[1] + 2 * x, t = 1;
    k1[2] = 0, k2[2] = x, k3[2] = 0;
    for (int i = 0; i <= p / 7; ++ i)
    {
        if ((p - i * 7) % 3 == 0)
            if (i + (p - i * 7) / 3 > k1[2] + k3[2])
                k1[2] = i, k3[2] = (p - i * 7) / 3, f[2] = 1;
    }
    if (k1[2] + k2[2] + k3[2] + 2 * x > sum && f[2])
        sum = k1[2] + k2[2] + k3[2] + 2 * x, t = 2;
    k1[3] = 0, k2[3] = 0, k3[3] = x;
    for (int i = 0; i <= p / 7; ++ i)
    {
        if ((p - i * 7) % 4 == 0)
            if (i + (p - i * 7) / 4 > k1[3] + k2[3])
                k1[3] = i, k2[3] = (p - i * 7) / 4, f[3] = 1;
    }
    if (k1[3] + k2[3] + k3[3] + 2 * x > sum && f[3])
        sum = k1[3] + k2[3] + k3[3] + 2 * x, t = 3;
    if (! f[1] && ! f[2] && ! f[3])//如果没有合法解，直接返回false
        return 0;
    if (x > ansmin)//如果当前最小值大于原答案最小值可以直接更新
    {
        anssum = sum, ansmin = x;//更新答案
        ans1 = k1[t], ans2 = k2[t], ans3 = k3[t];
        if (t == 1)
            ans2 += x, ans3 += x;
        if (t == 2)
            ans1 += x, ans3 += x;
        if (t == 3)
            ans1 += x, ans2 += x;
        //别忘记加回原本就有的钱数
        return 1;
    }
    return 0;
}

int main()
{
    //freopen("order.in", "r", stdin);
    //freopen("order.out", "w", stdout);
    scanf("%d", &n);
    int l = 0, r = n / 14;//二分端点
    if (n % 14 == 0)//第7~12个测试点做法
        printf("%d %d %d", n / 14, n / 14, n / 14), exit(0);
    while (l <= r)枚举最小值
    {
        int mid = (l + r) >> 1;
        if (check(mid))//如果有合法答案
            l = mid + 1, flag = 1;
        else 
            r = mid - 1;
    }
    if (flag)
        printf("%d %d %d", ans1, ans2, ans3);//输出答案
    else 
        printf("-1");//无解输出-1
    //fclose(stdin);
    //fclose(stdout);
    return 0;
}
```

#### 如果有什么错误，请大佬们指出，谢谢QwQ

---

## 作者：高雍博 (赞：1)

### ~~又~~ 第一篇题解，望各位大佬多多指教

这题~~作为 NOI Online 我唯一切掉的题~~非常好（shui）。

~~“那就水一发题解呗”~~

```cpp
#include<bits/stdc++.h>//万能的脑袋

using namespace std;

long long int n,a,b,c/*这三个是用来保存目前最佳的*/,allmax/*最大的总数*/,mima/*最大的套数*/;//我爱long long int

int main()
{
	freopen("order.in","r",stdin);
	freopen("order.out","w",stdout);//文件输入输出
	
	scanf("%lld",&n);
	if(n<3)//特判，小于笔记本的单价你就啥都买不了了
	{
		printf("-1");
		return 0;//输出就结束
	}
	for(register long long int k=0;k<=n/7;k++)
	{
		for(register long long int i=0;i<=n/4;i++)
		{
			for(register long long int j=0;j<=n/3;j++)//美丽的三层循环。由于不可能买到大于n/3的笔记本，这里有个小优化。上同。
			{
				if(7*k+4*i+3*j==n)//钱得全用光
				{
					long long int ea=min(k,i),eb=min(i,j),ec=min(ea,eb),airchina=k+i+j/*国航没给我广告费*/;//min函数不能判三个，所以就分别判两对不同的，再判结果。
					if(mima>ec)//这种情况肯定不是最佳方案，所以直接过
					{
						continue;
					}
					else if(mima<ec)//这肯定比之前的好，所以正常替换
					{
						mima=ec;
						allmax=airchina;
						a=k;
						b=i;
						c=j;//保存目前最佳。下同。
					}
					else//也就是mima==ec。这时有可能allmax>airchina,也有可能allmax<airchina，需要判断
					{
						if(allmax<airchina)//这时总数更大，更新
						{
							allmax=airchina;
							a=k;
							b=i;
							c=j;
						}
					}
				}
			}
		} 
	}
	printf("%lld %lld %lld",a,b,c);//完美输出，完美结束
	return 0;
} 
```
还是挺简单的，有点像模拟。


```cpp
#include<bits/stdc++.h>
  
using namespace std;

long long int n,a,b,c,allmax,mima;

int main()
{
	freopen("order.in","r",stdin);
	freopen("order.out","w",stdout);
	
	scanf("%lld",&n);
	if(n<3)
	{
		printf("-1");
		return 0;
	}
	for(register long long int k=0;k<=n/7;k++)
	{
		for(register long long int i=0;i<=n/4;i++)
		{
			for(register long long int j=0;j<=n/3;j++)
			{
				if(7*k+4*i+3*j==n)
				{
					long long int ea=min(k,i),eb=min(i,j),ec=min(ea,eb),airchina=k+i+j;
					if(mima>ec)
					{
						continue;
					}
					else if(mima<ec)
					{
						mima=ec；
						allmax=airchina；
						a=k；
						b=i；
						c=j；
					}
					else
					{
						if(allmax<airchina)
						{
							allmax=airchina;
							a=k;
							b=i;
							c=j;
						}
					}
				}
			}
		} 
	}
  	while(true)
		printf("%lld %lld %lld",a,b,c);
	return 0;
} 
```
这里再放一份没注释的。~~（有种你直接复制粘贴啊）~~


---

## 作者：Weak_Konjak (赞：1)

这题乍看上去很简单，实际上也不难。

题目中要求必须用光，且让整套的数量尽可能大，所以考虑先将 $n$ 对 14 取模，求出总套数 $k$ ，对剩下的余数 $r$ 进行讨论。

由于模数只有 0 到 13 ，所以手动打表是个好方法 。二位数的加减法，应该是小学内容吧。

题目还要求满足上述情况下 ，$a+b+c$ 最大，这个好办，假如能买 $3$ 元的，那就尽可能多买。

特别的，当余数为 1,2,5 时 ，不能买3元或4元的物品来将钱花光，就不得不放弃一件7元的圆规，再继续考虑。

处理完了，发现 a<0 则无解，输出 - 1

```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>

using namespace std;
int a,b,c,n;
int main()
{
	cin>>n;
	int k=n/14;
	int r=n%14;
	a=b=c=k;
	switch(r){
		case 0:break;
		case 1:a--,b--,c+=4;break;//这里有点坑，不是a--,b+=2,这种方法会更优
		case 2:a--,c+=3;break;
		case 3:c++;break;
		case 4:b++;break;
		case 5:a--,c+=4;break;
		case 6:c+=2;break;
		case 7:b++,c++;break;
		case 8:b+=2;break;
		case 9:c+=3;break;
		case 10:c+=2,b++;break;
		case 11:c++,b+=2;break;
		case 12:c+=4;break;
		case 13:c+=3,b++;break;
	}
	if(a<0) cout<<"-1";
	else cout<<a<<' '<<b<<' '<<c;
}


```




---

## 作者：WOWHandsome (赞：1)

$\texttt{NOI Online}$ 入门组 $200$分的蒟蒻前来发题解~

## 题意

$\text{满足以下条件}$

$\text{1、}7a+4b+3c=n.$

$\text{2、在满足条件1的情况下，}\ min(a,b,c)\ \text{尽可能大}.$

$\text{3、在满足条件1、2的情况下，}\ a+b+c\ \text{尽可能大}.$

$\text{求满足条件的最优方案} \ {a,b,c} \ \text{（保证最优解唯一，若不满足，输出-1）} $

## 做法

题目要求先满足条件 $1$，但是我们并不能在 $O(1)$ 的时间内快速求出满足条件的 $a,b,c$，所以我们可以先做条件 $2.$ 满足条件 $2$ 很简单，我们可以视作 $1a, 1b, 1c$ 为一组，从最多的组数 $n/14$ 开始向下枚举即可$.$ 最后我们把分组后剩下的再进行枚举，并求出合法的最优解即可。

## 代码

```cpp
/*
 * @Author: 蒟蒻 BYH 
 * @Date: 2020-03-07 14:44:48 
 * @Last Modified by: 蒟蒻 BYH
 * @Last Modified time: 2020-03-07 20:01:36
 */

# include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

int main()
{
    freopen("order.in", "r", stdin);
    freopen("order.out", "w", stdout);
    int n;
    scanf("%d", &n);
    int num = n / 14;
    int Max = -1;       //存储当前最多的物品数量
    int ans[8] = {0};   //存储答案
    for (int i = num; i >= 0; i--)   //尽可能先保证买多组物品，优先满足条件2
    {
        int s = n - i * 14;   //剩下的钱
        bool flag = false;    //是否有解
        for (int j1 = 0; j1 <= s / 3; j1++)    //先买最便宜的
            for (int j2 = 0; j2 <= s / 4; j2++)
                for (int j3 = 0; j3 <= s / 7; j3++)
                {
                    if (j1 * 3 + j2 * 4 + j3 * 7 != s) continue;  //不满足条件1
                    flag = true;
                    if (j1 + j2 + j3 + i*3 > Max)  //记录更优的
                    {
                        Max = j1 + j2 + j3 + i*3;
                        ans[0] = j1 + i;
                        ans[1] = j2 + i;
                        ans[2] = j3 + i;
                    }
                }
        if (flag) 
        {
            printf("%d %d %d\n", ans[2], ans[1], ans[0]);
            return 0;
        }
    }
    printf("-1\n");  //不满足任何条件
    return 0;
}
```

---

## 作者：chenpengda (赞：1)

AC了，来写篇题解。

先给出一些部分分的做法。

### 30 pts

直接暴力枚举就可以啦~

### 60 pts

特判，如果n是14的倍数可以直接输出三个$n/14$。

为什么这样是正确的呢？

因为这样肯定可以满足$a+b+c=n$，而这样可以保证$min(a,b,c)$最大。

因为如果将$a,b,c$中的一种文具多买一个，那么另外一种必定至少要少买一个，这样的话$min(a,b,c)$肯定就小了。

### 90 pts

同样暴力枚举，即可。

### 100 pts

各种乱搞优化。代码已经解释了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int min_t(int a,int b,int c)
{
	return min(a,(min(b,c)));//这里写一个函数。返回三个数中的最小值。 
}
int main()
{
	//freopen("order.in","r",stdin);
	//freopen("order.out","w",stdout);
	int n;
	int best_i=-1,best_j=-1,best_k=-1;//储存最优解。 
	cin>>n;
	//clock_t startTime,endTime;
	//startTime = clock();//计时开始
	if(n%14==0)
	{
		cout<<n/14<<" "<<n/14<<" "<<n/14;//特判。 
		return 0;
	}
	for(int i=n/7;i>=0;i--)//细节①：倒序判断，如果i本来就比min(a,b,c)要小了，那么就不可能有更优的解，直接break 
	{
		if(i<min_t(best_i,best_j,best_k))break;
		int j=0;
		while((n-7*i-4*j)%3!=0)j++;
		for(;j<=n/4;j+=3)//细节②：保持倍数，所以在使得k可以是成立之后，j必须加3，否则无法使得k是整数。 
		{
			if(n-i*7-j*4<min_t(best_i,best_j,best_k))break;//细节③：k太小了，直接break 
			if((n-i*7-j*4)%3!=0)continue;
			int k=(n-i*7-j*4)/3;
			if(min_t(best_i,best_j,best_k)<min_t(i,j,k)||min_t(best_i,best_j,best_k)==min_t(i,j,k)&&best_i+best_j+best_k<i+j+k)
			{//直接判断即可。 
				best_i=i;
				best_j=j;
				best_k=k;//储存为最优解。 
			}
		}
	}
	if(best_i==-1)cout<<-1;//细节④：记得输出-1。另外不可能有-1个文具，所以这里肯定是没有解的。 
	else
	{
		cout<<best_i<<" "<<best_j<<" "<<best_k;
		//if(best_i*7+best_j*4+best_k*3!=n)cout<<"FAKE!!!!";
	}
	cout<<endl;
//	endTime = clock();//计时结束
	//cout << "The run time is: " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	//这里本来是用来统计时间的，发现n<=100000时大约0.8S。 
	return 0;
	//愉快结束！ 
}
```

主要就是暴力稍加优化，比如$i$倒序遍历，$k$倒序遍历等等，只要不符合就马上剪掉。

实测名间AC，望审核通过！

---

## 作者：Licykoc (赞：1)

## 蒟蒻来发题解啦

~~本蒟蒻康不懂上面大佬的方法~~

其实这道题用纯暴力也是可以水过去的 awa

详见下方注释


```pascal
uses math;
var
  n,a,b,c,ma,mb,mc,tt:longint; //ma,mb,mc是储存最优解的变量，tt是有没有答案的标记
begin
  readln(n);  //输入
  if (n mod 14)=0 then  //特判，是14的倍数直接输出
    begin
      write(n div 14,' ',n div 14,' ',n div 14); 
      halt;
    end;
  for a:=n div 7 downto 0 do  //暴力枚举圆规的个数
    for b:=(n-a*7)>>2 downto 0 do  //暴力枚举笔的个数 Ps：>>2是位运算，等同于 div 4，但是更快 
	  begin
	    c:=(n-a*7-b*4) div 3; //省略第三重循环，直接算笔记本的个数
		if a*7+b<<2+c*3=n then  //如果可以用完n元钱，Ps: <<2也是位运算，等同于 *4
		  begin
		    if min(a,min(b,c))>=min(ma,min(mb,mc)) then //题目要求的第2条，3个个数中最小的最大
			  if a+b+c>=ma+mb+mc then //题目要求的第3条，总和最大
			    begin tt:=1; ma:=a; mb:=b; mc:=c; end; //记录当前答案，并更新tt为1
		  end;
	  end;
  if tt=0 then write(-1) //若没有答案，输出-1
    else write(ma,' ',mb,' ',mc);  //输入
end. //完结撒花awa
```

**各位小哥哥小姐姐如果觉得我写的不错，能给个赞嘛QWQ**

---

## 作者：源光 (赞：1)

如题，先是要保证最小值最大，我们可以打包来算（三个都卖一套，14元）

然后如果想要总数最多的话，要用剩下的钱多卖3元的文具

注意：有时候如果全打包可能会出错，比如15元,33元（自己想想），如果不打包是可以买完的，所以还要＋个循环来判断

如下是代码
```cpp
#include<iostream>
using namespace std;
int n;
int main(){
	freopen("order.in","r",stdin);//防抄袭
	freopen("order.out","w",stdout);
	cin>>n;
	int k=n/14;//最多可以打多少包
	for(int l=k;l>=0;l--){//慢慢推，这样打包不行就少打一次再看
		n=n-(l*14);
		for(int a=n/3;a>=0;a--){//3元的以最多算
			for(int b=(n-a*3)/4;b>=0;b--){
				for(int c=(n-a*3-b*4)/7;c>=0;c--){
					if((3*a)+(4*b)+(7*c)==n){
						cout<<(c+l)<<" "<<(b+l)<<" "<<(a+l)<<endl;//如果if((3*a)+(4*b)+(7*c)==n)成立，就一点是最优解，直接输出

						return 0;//落幕
					}
				}
			}
		}
		n=n+l*14;
	}
	cout<<"-1";//怎么算都不行的
	return 0;//落幕
}
```
这样绝对不会TLE，因为每次循环范围很小。

应该是最优解。

谢谢大家看完这期题解（给个赞呗）

---

## 作者：tongyf (赞：0)

考场上唯一能拿分的题就这么爆炸了

这道题就是按照三个条件的优先级不同，依次枚举来满足三个条件。我们依次来看：

1.n 元钱必须正好用光，即 $7a+4b+3c=n$

但是如果直接枚举这个条件的话枚举量过大，我们不如先看第二个条件：

2.在满足以上条件情况下，成套的数量尽可能大

这样我们就可以枚举一共选几套，然后看每种情况下能不能把钱全部花光。扣除成套购买所需的钱了之后，我们来看下一个条件：

3.在满足以上条件情况下，物品的总数尽可能大

显然，我们再枚举物品时就不能选7元的东西了，而是选3元和4元的，那么就枚举三元的物品买几件，看看剩下的钱能不能被4整除，从所有可行解中找最优的就可以

注意：枚举套数的时候要倒着枚举，因为如果较大的套数时出现了可行解，就不需要枚举更少的套数了，枚举3元物品的个数同理

还有，一定注意n是14的倍数的情况，以及n=0的情况！！！

时间复杂度：最坏$O(n^2)$

这是本蒟蒻的考场代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a=0,b=0,c=0,flag=0;//flag表示有无可行解 
int main(){
	//freopen("order.in","r",stdin);
	//freopen("order.out","w",stdout);
	cin>>n;
	if(n%14==0){//对n是14倍数的特判 
		cout<<n/14<<" "<<n/14<<" "<<n/14<<endl;
		return 0;
	}
	if(n<3){//也是特判一下 
		cout<<"-1"<<endl;
		return 0;
	}
	for(int i=n/14;i>=0;i--){//枚举套数 
		int maxsum=0;
		int cc=0,bb=0;
		int sum=0;
		int temp=n-14*i;
		for(int j=temp/3;j>=0;j--){//枚举3元物品的件数 
			if((temp-j*3)%4==0){
				flag=1;
				if(j+(temp-j*3)/4>sum){//如果有更优的解，更新答案 
					sum=j+(temp-j*3)/4;
					a=i;
					c=j+i;
					b=(temp-3*j)/4+i;
				}
			}
		}
		if(flag==1) break;//有可行解了，终止枚举 
	}
	if(!flag){
		cout<<"-1"<<endl;
		return 0;
	}
	else cout<<a<<" "<<b<<" "<<c<<endl;
	return 0;
}

```


---

## 作者：xiayifei (赞：0)

### P1688 【文具订购】题解


------------
[题目链接](https://www.luogu.com.cn/problem/P6188)

作为本蒟蒻在洛谷题库的第一篇题解

心中还是未免有些紧张

我用的方法类似于打表

文字不太好描述，手工列举出 1~19 的分配方法就行

具体方法可以看代码及注释

（14 以下的数只有 1，2，5 三个数无法分配，用 15，16，19 代替，也就是分别加上 14）



------------
```cpp
#include<bits/stdc++.h>//万能的万能头
using namespace std;
int n,a,b,c,y,p[20][3]={{0,0,0},{0,0,5},{0,1,4},{0,0,1},{0,1,0},{0,1,5},{0,0,2},{0,1,1},{0,2,0},{0,0,3},{1,0,1},{0,2,1},{0,0,4},{0,1,3},{0,0,0}};//打表结果，其中 1，2，5 的结果用 15，16，19 的结果代替
int main()
{
	//freopen("order.in","r",stdin);
	//freopen("order.out","w",stdout);
	cin>>n;
	y=n%14;//求出n/14的余数（为什么是14?因为7+3+4=14)
	a=b=c=n/14;//每个14都可以由一个3，一个4和一个7组成
	if(y==1||y==2||y==5)
	{
		a--;b--;c--;//1，2，5无法分配，需要匀出一个14来分
	}
	a+=p[y][0];
	b+=p[y][1];
	c+=p[y][2];/把余数合理分给三个数
	if(a*7+b*4+c*3==n&&a>=0&&b>=0&&c>=0)//注意三个数一定要>=0
		cout<<a<<" "<<b<<" "<<c<<endl;
	else
		cout<<"-1"<<endl;
	
 	return 0;//华丽的结束
}

```


---

## 作者：Demoe (赞：0)

### [传送门](https://www.luogu.com.cn/problem/P6188)

~~虽然我是打提高的但我觉得我还是想写普及题解。~~

## 前置知识

分类讨论（约等于不需要）。

## 简述题意

- 拿 $a$ 个7 $b$ 个4 $c$ 个3 使 $7a+4b+3c=n$ $min{a,b,c}$ 最大 $a+b+c$ 最大 （顺序从前往后）

# 分类讨论

首先不难想到 3+4=7 （废话）。

我们**枚举**7的个数。

每次设还剩下 $sum$。

## 第一种情况

我们假设7**不是最小**，为让最小值最大，我们让3和4个数尽可能相等，这样才能使套数**最大**，然后我们手推规律。

因为3+4=7，所以每有1个7我们可以拿1个3和1个4，于是我们对剩下的%7进行**分类讨论**。

我们发现还有1个 2个 5个时是取不了的，我们特判掉，然后发现8个9个12个都是可以的，那我们就补一个7上去。
		
- 在$sum\equiv0\pmod{7}$时，显然拿3 4的个数相同。

- 在$sum\equiv1\pmod{7}$时，补一个7，发现8个，即可以是2个4，剩下的相同。

- 在$sum\equiv2\pmod{7}$时，补一个7，发现9个，是3个3。 

- 在$sum\equiv3\pmod{7}$时，就多拿1个3。

- 在$sum\equiv4\pmod{7}$时，就多拿1个4。

- 在$sum\equiv5\pmod{7}$时，补一个7，发现12个，可以是3个4也可以是4个3，因为两种情况最小相同，我们让总数最多，即取4个3。

- 在$sum\equiv6\pmod{7}$时，就多拿2个3。

```cpp
		if(sum==1||sum==2||sum==5) break;
		if(sum%7==0){y=z=sum/7;}
		if(sum%7==1){z=(sum-8)/7;y=z+2;}
		if(sum%7==2){y=(sum-9)/7;z=y+3;}
		if(sum%7==3){y=(sum-3)/7;z=y+1;}
		if(sum%7==4){z=(sum-4)/7;y=z+1;}
		if(sum%7==5){y=(sum-12)/7;z=y+4;}
		if(sum%7==6){y=(sum-6)/7;z=y+2;}
```

## 第二种情况

假设7是最小，那么4就取刚好能取完3且只比7多一点的。

那我们对进行讨论

4可以取$x$ $x+1$ $x+2$ 只有一种可以满足$sum\equiv0\pmod{3}$

```cpp
		if(sum-4*x>=0&&(sum-4*x)%3==0){y=x;z=(sum-4*y)/3;}
		if(sum-4*(x+1)>=0&&(sum-4*(x+1))%3==0){y=x+1;z=(sum-4*y)/3;}
		if(sum-4*(x+2)>=0&&(sum-4*(x+2))%3==0){y=x+2;z=(sum-4*y)/3;}
```

所以我们不断更新 就能在O（n）内算出答案。

```cpp
/*
***
还要继续努力
成为一名烤咕学家哦
***
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,a,b,c,sum;
template <typename T> void rd(T &x){
	ll fl=1;x=0;char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') fl=-fl;
	for(;isdigit(c);c=getchar()) x=(x<<3)+(x<<1)+c-'0';
	x*=fl;
}
void wr(ll x){
	if(x<0) x=-x,putchar('-');
	if(x<10) putchar(x+'0');
	if(x>9) wr(x/10),putchar(x%10+'0');
}
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	rd(n);
	if(n==1||n==2||n==5){  //特判掉 
		printf("-1\n");
		return 0;
	}
	sum=n;
	for(ll x=0,y,z;x<=n/7;x++,sum-=7){  //枚举选7的个数 
		if(sum==1||sum==2||sum==5) break;
		if(sum%7==0){y=z=sum/7;}
		if(sum%7==1){z=(sum-8)/7;y=z+2;}
		if(sum%7==2){y=(sum-9)/7;z=y+3;}
		if(sum%7==3){y=(sum-3)/7;z=y+1;}
		if(sum%7==4){z=(sum-4)/7;y=z+1;}
		if(sum%7==5){y=(sum-12)/7;z=y+4;}
		if(sum%7==6){y=(sum-6)/7;z=y+2;}
		if(min(min(x,y),z)>min(min(a,b),c)||min(min(x,y),z)==min(min(a,b),c)&&x+y+z>a+b+c) a=x,b=y,c=z;
		//假设7不是最小 为让最小值最大 我们让3和4个数尽可能相等 这样才能使套数最大 然后我们手推规律
		//因为3+4=7 所以每有1个7我们可以拿1个3和1个4 于是我们对剩下的%7进行分类讨论
		//我们发现还有1个2个5个时是取不了的 我们特判掉 然后发现8个9个12个都是可以的 那我们就补一个7上去
		//在%7==0时 显然拿3 4的个数相同
		//在%7==1时 补一个7 发现8个 即可以是2个4  剩下的相同
		//在%7==2时 补一个7 发现9个 是3个3
		//在%7==3时 就多拿1个3
		//在%7==4时 就多拿1个4
		//在%7==5时 补一个7 发现12个 可以是3个4也可以是4个3 因为两种情况最小相同 我们让总数最多 即取4个3
		//在%7==6时 就多拿2个3 
		if(sum-4*x>=0&&(sum-4*x)%3==0){y=x;z=(sum-4*y)/3;}
		if(sum-4*(x+1)>=0&&(sum-4*(x+1))%3==0){y=x+1;z=(sum-4*y)/3;}
		if(sum-4*(x+2)>=0&&(sum-4*(x+2))%3==0){y=x+2;z=(sum-4*y)/3;}
		if(min(min(x,y),z)>min(min(a,b),c)||min(min(x,y),z)==min(min(a,b),c)&&x+y+z>a+b+c) a=x,b=y,c=z;
		//假设7是最小 那么4就取刚好能取完3且只比7多一点的
		//那我们对%3进行讨论
		//4可以取x x+1 x+2 只有一种可以满足%3==0
		//所以我们不断更新 就能在O（n）内算出答案 
	}
	wr(a);putchar(' ');wr(b);putchar(' ');wr(c);puts("");
	return 0;
}
```


---

## 作者：Ignotus (赞：0)

这道题我用的是纯贪心的思想解决的。  
考场上以为是道水题，结果考后发现漏洞满篇...    

回到正题：  
考虑输出 $-1$的情况，通过严格证(mei)明(ju)可以发现，只有 $n=1, n=2$ 和 $n=5$ 三种情况无解（注意：题目中没有要求 $a,b,c\neq 0$）    
再考虑第二条限制：在满足以上条件情况下，成套的数量尽可能大，即 $a,b,c$ 中的最小值尽可能大。   
定义变量 $maxn=\lfloor{\frac{n}{14}}\rfloor$，表示最多能买的套数，但注意剩下的钱应该够买整数个文具，即如果剩下的钱为 $1,2$ 或 $5$ 元，则不能买整数个文具，$maxn$ 需要减 $1$，剩余的钱数 $tmp=tmp+14$。   
最后考虑第三条限制，贪心可以发现，要尽可能选花钱少的才能使总件数多。  
再处理一下答案即可。

详见代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

int n,a,b,c,maxn,tmp; //定义变量，a，b，c为最后输出的件数

int main()
{
	//freopen("order.in","r",stdin);
	//freopen("order.out","w",stdout);
	cin>>n;
	maxn=n/14; //可以买到文具的套数
	tmp=n%14;  //买完所有的整套文具后剩下的钱
	if(tmp==1 || tmp==2 || tmp==5){  
		maxn--;
		tmp+=14;
	}  //如果剩下的钱不够买整件商品，则tmp+=14，maxn--
	if(maxn==-1){
		cout<<maxn<<endl;
		return 0;
	} //maxn一开始等于0，如果减到-1一定无解，输出-1即可
    
    	a=b=c=maxn;  //三种文具都先买maxn个
	while(tmp>8){
		tmp-=3;
		c++;
	}		//贪心，一直买最便宜的
	if(tmp==8) b+=2;
	if(tmp==7) b++,c++;
	if(tmp==6) c+=2;
	if(tmp==4) b++;
	if(tmp==3) c++;	//如果tmp一开始就等于3或4，直接买相应的文具即可
	printf("%d %d %d\n",a,b,c); //输出答案
	return 0;
}
```


---

## 作者：duyh1114 (赞：0)

看到另几篇题解都用了一个又一个的`for`循环，蒟蒻表示不懂，~~根本不用`for`循环也能过啊~~。  
那么，我们现在来进入解题过程。  


------------

首先来看输出-1的情况：  
当$n=1,2,5$的时候，没有方案满足。  
其他数字都可以有方案。  


------------

如果要成套的文具尽量的多，那么我们只能一次买一套花费14元。  
我们把$n \div 14$记作$m$，把$n \bmod 14$记作$l$。  
难道说如果$l=1,2,5$就无解了？  
当然不是。在$n=1,2,5$的时候，无解。但是在$l=1,2,5$的时候，我们可以拆掉一包文具来使$l+14$！  
```cpp
l=0:0+0+0
l=3:0+0+1
l=4:0+1+0
l=6:0+0+2
l=7:0+1+1
l=8:0+2+0
l=9:0+0+3
l=10:0+1+2
l=11:0+2+1
l=12:0+0+4
l=13:0+1+3
l=15:0+0+5
l=16:0+1+4
l=19:0+1+5
//l表示买完整套剩的钱，第1,2,3个数分别表示a,b,c的值
//这是l元钱能买到的最多的文具，可以证明，他们是最多的
```
分析了这么多，我们应该可以得到代码了：
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
int n,m,l;
inline int read()//读入优化，虽然只输入一个数没有什么用
{
	int s=0;//因为没有负数，所以就不用设负数标记了
	char c=getchar();
	while(c<'0'||c>'9')
		c=getchar();
	while(c>='0'&&c<='9')
	{
		s=(s<<3)+(s<<1)+c-48;
		c=getchar();
	}
	return s;
}
int main()
{
//	freopen("order.in","r",stdin);
//	freopen("order.out","w",stdout);
	n=read();
	if((n>0&&n<3)||n==5)
	{
		printf("-1\n");//无解
		return 0;
	}
	m=n/14;
	l=n%14;//m,l含义见前面的文章
	if((l>0&&l<3)||l==5)//需要拆一包文具
	{
		l+=14;
		m--;
	}
	if(l==0)//繁琐的比较
		printf("%d %d %d\n",m,m,m);
	else if(l==3)
		printf("%d %d %d\n",m,m,m+1);
	else if(l==4)
		printf("%d %d %d\n",m,m+1,m);
	else if(l==6)
		printf("%d %d %d\n",m,m,m+2);
	else if(l==7)
		printf("%d %d %d\n",m,m+1,m+1);
	else if(l==8)
		printf("%d %d %d\n",m,m+2,m);
	else if(l==9)
		printf("%d %d %d\n",m,m,m+3);
	else if(l==10)
		printf("%d %d %d\n",m+1,m,m+1);
	else if(l==11)
		printf("%d %d %d\n",m,m+2,m+1);
	else if(l==12)
		printf("%d %d %d\n",m,m,m+4);
	else if(l==13)
		printf("%d %d %d\n",m,m+1,m+3);
	else if(l==15)
		printf("%d %d %d\n",m,m,m+5);
	else if(l==16)
		printf("%d %d %d\n",m,m+1,m+4);
	else if(l==19)
		printf("%d %d %d\n",m,m+1,m+5);
	else
		printf("INF INF INF");//因为不会是这个值，所以填什么都可以
	return 0;
}
```
希望你在看完这篇博客之后，你可以明白这道题的做法和思路。  
如果你不能明白，欢迎随时私信我。

---

## 作者：OMG_wc (赞：0)

首先可以证明，$a\le b$ 且 $a\le c$ ：

假设存在一种方案满足 $7a+4b+3c=n$ 且  $a>b$，那么可以把原来的 $(a,b,c)$ 变为 $(a-1,b+1,c+1)$，而总和依然是 $n$。 原来三者的最小值为 $\min(b,c)$，而现在为 $\min(a-1,b+1,c+1)$ ，显然后者不会比前者更小（因为 $a-1\ge \min(b,c)$ 且 $b+1 \ge \min(b,c) $ 且  $c+1 \ge \min(b,c) $）。所以修改后，条件二会更优，且在条件二持平的情况下，条件三更优。因而，假设的解不是最优方案， 在最优方案下应该 $a\le b$。

同理可证 $a\le c$。

这样条件二的意思就是 $a$ 要尽可能的大。

设 $d=b-a,e=c-a$，在 $a$ 确定的情况下，问题变为凑出 $d$ 和 $e$ 满足 $4d+3e=n-14a$，且 $d$ 要尽可能小，$e$ 要尽可能大（条件三）。

~~根据《小凯的疑惑》~~，右边只有 $1,2,5$ 是凑不出来的。

那么 $a$ 只可能是 $\lfloor\frac{n}{14}\rfloor$ 或者 $\lfloor\frac{n}{14}\rfloor-1$ ，也就是说这道题是 $O(1)$ 时间可以解决的。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int INF = 0x3f3f3f3f;
const LL mod = 1e9 + 7;
const int N = 100005;

int main() {
    int n;
    cin >> n;
    for (int a = n / 14; a >= 0; a--) {
        int t = n - a * 14;
        for (int b = 0; 4 * b <= t; b++) {
            if ((t - 4 * b) % 3 == 0) {
                int c = (t - 4 * b) / 3;
                printf("%d %d %d\n", a, b + a, c + a);
                return 0;
            }
        }
    }
    puts("-1");
    return 0;
}

```


---

