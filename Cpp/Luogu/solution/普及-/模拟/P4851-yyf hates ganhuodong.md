# yyf hates ganhuodong

## 题目背景

非酋yyf知道自己太非了，于是他开始爆肝活动。yyf终于成为了一名肝帝，但他还是想尽量节省 $\mathrm{loveca}$ 的花费，不然的话如果花了太多 $\mathrm{loveca}$，yyf会心疼的。

## 题目描述

给你如下 $11$ 个正整数：

$a$：完成一首歌曲所能获得的活动$\mathrm{pt}$

$b$：完成一首歌曲所需的 $\mathrm{LP}$

$c$：你开始肝活动时的 $\mathrm{LP}$ 上限

$d$：你开始肝活动时的 $\mathrm{LP}$

$e$：你开始肝活动时的经验值上限

$f$：你开始肝活动时的经验值

$g$：打一首歌能获得的经验值

$h$：升一级增加的 $\mathrm{LP}$ 上限

$k$：升一级增加的经验值上限

$x$：离活动结束的剩余时间（小时）

$y$：你的目标活动$\mathrm{pt}$

假设yyf打歌不需要花费时间，每打一首歌需要花费一定的 $\mathrm{LP}$ 来获取一定的活动$\mathrm{pt}$ 以及一定的经验值。yyf的初始活动$\mathrm{pt}$ 为 $0$

$\mathrm{LP}$ 每小时自动恢复 $1$ 点，$\mathrm{LP}$ 达到上限后不会自动恢复（本题不需考虑这种情况），但可以通过后文所述方式超过上限。

经验值达到上限后会升级，升级时会增加 $\mathrm{LP}$上限并恢复“新的 $\mathrm{LP}$上限”（增加后的）点 $\mathrm{LP}$，恢复后的 $\mathrm{LP}$ 可以超过 $\mathrm{LP}$ 上限，且溢出的经验值会计入下一次升级，下一次升级所需要的经验值（经验值上限）会增加。

可以随时耗费一个 $\mathrm{loveca}$ 来获得当前 $\mathrm{LP}$上限点 $\mathrm{LP}$（可以超过上限）。

你的目标是获得大于等于 $y$ 的活动$\mathrm{pt}$，请求出最少需要耗费多少个 $\mathrm{loveca}$。

形式化地说，你初始的 $\mathrm{LP}$ 可以视作 $d+x$，你有两种操作：

1. 设你操作前的经验值为 $\mathrm{exp}$，$\mathrm{LP}$上限为 $\mathrm{LPmax}$，$\mathrm{LP}$ 值为 $l$（当且仅当 $l \ge b$ 时能进行操作 $1$ ），经验值上限为 $\mathrm{EXPmax}$，则在你操作后活动$\mathrm{pt}$ 加上 $a$ 。
- 若 $\mathrm{exp+g \ge EXPmax}$，则你的剩余 $\mathrm{LP}$值为 $l-b+\mathrm{LPmax}+h$，经验值为 
 $\mathrm{(exp+g)\bmod EXPmax}$，$\mathrm{LP}$上限加上 $h$，经验值上限加上 $k$
- 否则你的剩余 $\mathrm{LP}$值为 $l-b$，经验值为 $\mathrm{exp+g}$

2. 设你操作前的 $\mathrm{LP}$上限为 $\mathrm{LPmax}$，$\mathrm{LP}$值为 $l$ ，则你操作后的剩余 $\mathrm{LP}$值为 $\mathrm{LPmax}+l$

你的目标为使你的活动$\mathrm{pt}$ 大于等于 $y$ ，请求出最少需要的操作 $2$ 数量

## 由于打歌不计时间可以在活动结束的瞬间打任意次歌，即进行任意次操作1，也就是初始LP可以视作d+x

## 说明/提示

$a∈[1,10]$

$b∈[5,20]$

$c∈[30,50]$

$d∈[5,10]$

$e∈[100,200]$

$f∈[1,50]$

$g∈[10,20]$

$h∈[5,10]$

$k∈[10,20]$

$x∈[10,15]$

$y∈[5000,10000]$

## 样例 #1

### 输入

```
9 7 46 6 114 50 17 6 18 11 9118```

### 输出

```
7```

# 题解

## 作者：Alpha_Zero (赞：10)

这道题，嗯，不难，把题目看懂就行。~~烦~~。
~~~cpp
#include<iostream>
using namespace std;
int a,b,c,d,e,f,g,h,k,x,y,pt,lp,exp;
long long cnt;//注意要用long long
int main()//主函数
{
    cin >> a >> b >> c >> d >> e >> f >> g >> h >> k >> x >> y;//如此繁琐 
    lp=d+x;exp=f;//初值 
    while(pt<y)//开始（核心）
    {
        while(lp<b)cnt++,lp+=c;
        lp-=b;pt+=a;exp+=g;
        if(exp>=e)//如果没加等号就只有96分
        {
            exp-=e;
    	    e+=k;c+=h;lp+=c;
        }
    }
    cout << cnt << endl;//输出答案
    return 0;
}
~~~
跟着题意模拟，没什么好讲的。

---

## 作者：ouuan (赞：6)

就是一道纯模拟题..玩过sif的可以秒切了，没玩过的照着“形式化说明”就可以写了。

怎么说，其实也能算是一道入门难度的贪心？

能进行操作 $1$ 就进行操作 $1$ ，否则进行操作 $2$ ，直到活动 $\mathrm{pt} \ge y$

~~假装这是一道贪心题~~，贪心策略的证明就是先进行操作 $1$ 可以提高 $\mathrm{LP}$ 上限，然后操作 $2$ 能恢复的 $\mathrm{LP}$ 就会变多

时间复杂度：$O(\text{能过})$

期望得分：$100$ 分

~~代码注释被形式化说明吃了~~

### 赛后补充

> 由于你可以选择在任意时候打歌且打歌不计时间，每小时恢复和一开始就恢复是等价的...

本来以为有了形式化说明这里不会有问题的...

另外看不懂的真的可以只看形式化说明...

另外本来这题数据是纯随机的，后来我突然想试着卡一卡，就造了两个如果按大于（没有等于）做会WA的点，竟然真的卡到了好多人..

然而除了0/96/100的其它分我是真的没想到..

### UPD

我知道78分是怎么回事了..有的点会无限升级从而有无限lp，有lp无限打歌的算法就挂了

### 标程

```
#include <iostream>

using namespace std;

int main()
{
	int a,b,c,d,e,f,g,h,k,x,y,pt=0,ans=0;
	
	cin>>a>>b>>c>>d>>e>>f>>g>>h>>k>>x>>y;
	
	d+=x;
	
	while (pt<y)
	{
		if (d>=b)
		{
			pt+=a;
			f+=g;
			if (f>=e)
			{
				d=d-b+c+h;
				c+=h;
				f-=e;
				e+=k;
			}
			else
			{
				d-=b;
			}
		}
		else
		{
			++ans;
			d+=c;
		}
	}
	
	cout<<ans;
	
	return 0;
}
```

---

## 作者：封禁用户 (赞：2)

这题我看到题目已经蒙了。

那一大坨的字我完全看不懂。

后来才慢慢明白。

所以为了不让这种事情再次发生。

我决定在这儿了**简化题目**。

![](https://ss1.bdstatic.com/70cFuXSh_Q1YnxGkpoWK1HF6hhy/it/u=3579833039,2372283244&fm=26&gp=0.jpg)

**题目简单叙述**

给你 $11$ 个数 $a,b,c,d,e,f,g,h,k,x,y$ 。

你自己有 $5$ 个数 $lp,exp,lpmax,expmax,pt$ 。

~~初始值自己思考~~

现在你有两种操作：

1. （**当l≥b时才可以执行这种操作**）若 $exp+g≥expmax$，$lp$  更新为 $l−b+lpmax+h$，$exp$ 更新为 $exp+g-expmax$，$lpmax$ 加上 $h$，$expmax$ 加上 $k$。否则，$lp$ 减去 $b$，$exp$ 加上 $g$。做完这个操作后 $pt$ 加上 $a$。

2. $lp$ 加上 $lpmax$。

现在重复执行，**每次执行两个操作其中一个**，直到 $pt≥y$ 时，求执行操作 $2$ 的最少次数。

我们来思考一下，

因为每次都会执行两个操作中的一个，

而我们要让**操作 $2$ 的执行次数尽量少**就一定要让**操作 $1$ 尽量多**。

按着这个思路，**让可以执行操作 $1$ 时执行它，不行时否则执行操作 $2$ 并记录执行次数。**

最后我们直接输出。


```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
	int a,b,c,d,e,f,g,h,k,x,y,lp,exp,lpmax,expmax,pt,ans;
	cin>>a>>b>>c>>d>>e>>f>>g>>h>>k>>x>>y;
	//初始化
	while(pt<y){
		if(lp>=b){
			if(exp+g>=expmax){
				lp=lp-b+lpmax+h;
				exp=exp+g-expmax;
				lpmax+=h;
				expmax+=k;
			} else{
				lp=lp-b;
				exp+=g;
			}
			pt+=a;
		} else{
			lp+=lpmax;
			++ans;
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：起名字重要吗 (赞：1)

看清题意跟着模拟即可，思路说明：

首先，能进行就进行操作1，否则进行操作2，直到$\mathrm{pt} \ge y$

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a,b,c,d,e,f,g,h,k,x,y,pt,lp,Exp,loveca;
int main() {
	cin>>a>>b>>c>>d>>e>>f>>g>>h>>k>>x>>y;
	lp=d+x,Exp=f;
	while(pt<y) {
		while(lp<b) loveca++,lp+=c;
		lp-=b,pt+=a,Exp+=g;
		if(Exp>=e) Exp-=e,e+=k,c+=h,lp+=c;
	}
	cout<<loveca;
	return 0;
}
```
记得点赞再走！求管理大大给过！

---

## 作者：封禁用户 (赞：1)

```c
#include<cstdio>
int a,b,c,d,e,f,g,h,k,x,y;
int pt,lp,exp;
int main()
{
    scanf("%d%d%d%d%d%d%d%d%d%d%d",&a,&b,&c,&d,&e,&f,&g,&h,&k,&x,&y);//比较恐怖的输入
    pt=0,lp=d+x,exp=f;//初始条件
    long long cnt=0;//注意是long long;
    while(pt<y)
    {
        while(lp<b)cnt++,lp+=c;
        lp-=b;pt+=a;exp+=g;
        if(exp>=e)//没加等号，只有96; 
        {
            exp-=e;
            e+=k;c+=h;lp+=c;//内部替换
        }
    }
    printf("%lld\n",cnt);//最后输出
    return 0;//end...
}
```


------------
##**个人认为是模拟,不知为啥是贪心.如果有人知道原因,就麻烦私信给我讲一下.Thanks!**

---

## 作者：恶灬心 (赞：1)

## 首先 阐述一下我做题解的理由
#### 1.这题很难读
#### 2.~~就因为难读所以~~我要简要分析和记录一下思路
#### 大致分析一下：
****
 从目标谈起：问题让我们输出达到pt>=y时的最小消耗loveca，而pt只有通过打歌才能获得，因此我们可以将问题转化为达到（double）y/a首歌时的最小消耗loveca，再分析打歌需要LP，而LP分为三种获得途径：
- ①初始的LP，此题多一个迷惑条件时间获得LP，没什么用 所以可以认为初始LP=d+x。
- ②通过升级来获得 上限的c（这里c是升级过后的值）
- ③通过loveca获得 上限的c（这里c没有升级）
以上是分析的思路 按照这样即可想出大概的程序就是：
打歌-->检查升级-->检查是否能打歌-->检查是否达到目标pt-->没达到消耗loveca重新开始轮回


------------
附上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c,d,mexp,Exp,g,h,k,x,y,pt,LP,xu_L=0;
void shengji()
{
	while(Exp>=mexp)
	//每升一次 +h上限Lp -mexpEXP +k上限mexp +cLP
	{
		c+=h;
		Exp-=mexp;
		mexp+=k;
		LP+=c;
	}
}
void dage()
{
	while(LP>=b)
	//每一首歌 -bLP +gEXP +aTP  
	{
		int x=LP/b; //能打x首歌
		LP-=(b*x);
		Exp+=(g*x);
		pt+=(a*x);
		if(pt<y) shengji();
		else 
		{
			cout<<xu_L; exit(0);
		}
	}
}
int main()
{
	cin>>a>>b>>c>>d>>mexp>>Exp>>g>>h>>k>>x>>y;
	LP=d+x;
	while(pt<y)
	{	
		dage();
		if(pt<y)
		{
			xu_L++;
			//+xu_L +cLP 
			LP+=c;
		}
	}
	cout<<xu_L;
	return 0;
}

```


---

## 作者：封禁用户 (赞：1)

##**很水的一道题，据说是贪心...个人感觉倒像个模拟

Code:
---------------------
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c,d,e,f,g,h,k,x,y;
int pt,lp,exp;
int main()
{                   
    cin>>a>>b>>c>>d>>e>>f>>g>>h>>k>>x>>y;//输入(好像比较恐怖)
    pt=0,lp=d+x,exp=f;//判断
    long long cnt=0;//需注意是long long;
    while(pt<y)
    {
        while(lp<b)cnt++,lp+=c;
        lp-=b;pt+=a;exp+=g;
        if(exp>=e)//没加等号，只有96 
        {
            exp-=e;
            e+=k;c+=h;lp+=c;
        }
    }
    printf("%lld\n",cnt);//最后输出
    return 0;//end...
}
```

---

## 作者：hhjtutuhe (赞：0)

### 为什么是贪心。。。我也没有太搞明白

不能操作 1 ，就操作 2 ，point>=y为止

这一道题唯一要特别注意的是定义的变量

变量太多了额

```cpp
#include<bits/stdc++.h>//万能头万岁
using namespace std;//记得要加

int a,b,c,d,e,f,g;
int h,k,x,y;//分两段定义看的清楚
int point,LP,EXP;

int main()
{
    cin>>a>>b>>c>>d>>e>>f>>g>>h>>k>>x>>y;//输入
    point=0;
    LP=d+x;
    EXP=f;//条件打上
    long long Answer=0;//开long long以防万一;
    for(;point<y;point+=a)
    {
        for(;LP<b;LP+=c)
          Answer++;
        LP-=b;
        EXP+=g;
        if(EXP>=e) 
        {
            EXP-=e;
            e+=k;
            c+=h;
            LP+=c;//内部更换思路要清晰（本人在此卡了好久）
        }
    }
    cout<<Answer<<'\n';//输出答案
    return 0;//华丽地结束
}
```
~~已AC~~

---

