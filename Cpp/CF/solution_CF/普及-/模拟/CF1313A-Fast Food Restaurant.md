# Fast Food Restaurant

## 题目描述

由于Denis工作得很累，他想开家餐厅。

第一天，他做了 $a$ 份饺子，$b$ 份莓果汁和 $c$ 份淋有炼乳的松饼。

Denis餐厅奇怪的地方在于订餐的过程。对于每位客人Denis会自己选**一份套餐**给客人。

Denis选**套餐**的规则是这样的：

1. 每个客人都要至少有一份**食物**（饺子、莓果汁、淋有炼乳的松饼都是食物）。

2. 每个客人**不能收到多于一份饺子**，**不能收到多于一份莓果汁**，**且不能收到多于一份淋有炼乳的松饼**。

3. 每个客人都要有**不一样**的套餐。

Denis**最多**可以为几个客人提供套餐呢？

## 样例 #1

### 输入

```
7
1 2 1
0 0 0
9 1 7
2 2 3
2 3 2
3 2 2
4 4 4```

### 输出

```
3
0
4
5
5
5
7```

# 题解

## 作者：rui_er (赞：2)

这题数据这么小，**就直接暴力吧！**

如果可以选 $A$、$B$ ，选 $AB$ 肯定不合适。先排个序，把原数组变成降序，然后枚举 $7$ 种情况判断是否可以即可。

```cpp
//By: Luogu@rui_er(122461)
#include <bits/stdc++.h>
using namespace std;

int t; 
int a[3]; 
int ans;

int main()
{
	cin>>t;
	while(t--)
	{
		ans = 0;
		cin>>a[0]>>a[1]>>a[2];
		if(a[0] < a[1]) swap(a[0], a[1]);
		if(a[0] < a[2]) swap(a[0], a[2]);
		if(a[1] < a[2]) swap(a[1], a[2]);
		if(a[0]) --a[0], ++ans;
		if(a[1]) --a[1], ++ans;
		if(a[2]) --a[2], ++ans;
		if(a[0] && a[1]) --a[0], --a[1], ++ans;
		if(a[0] && a[2]) --a[0], --a[2], ++ans;
		if(a[1] && a[2]) --a[1], --a[2], ++ans;
		if(a[0] && a[1] && a[2]) --a[0], --a[1], --a[2], ++ans;
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：bunH2O (赞：1)

### Part 1:思路
>每个客人不能收到多于一份饺子，不能收到多于一份莓果汁，且不能收到多于一份淋有炼乳的松饼。

也就是说：每位客人对于每种食品**只有两种选择**：买或不买。

那么我们只要按照**某种顺序**来枚举所有情况即可。
### Part 2:实现Ⅰ
很显然每只选一种食品是最划算的，都买是最不划算的，而先算哪个食品无关紧要。

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int a[3],sum=0;
int main()
{
    int t;
    cin>>t;
    for(int i=0;i<t;i++)
    {
        cin>>a[0]>>a[1]>>a[2];
        sum=0;
        //先算一个
        if(a[0]>0)
        {
            a[0]--;
            sum++;
        }
        if(a[1]>0)
        {
            a[1]--;
            sum++;
        }
        if(a[2]>0)
        {
            a[2]--;
            sum++;
        }
        //再算两个
        if(a[0]>0&&a[1]>0)
        {
            a[0]--;
            a[1]--;
            sum++;
        }
        if(a[0]>0&&a[2]>0)
        {
            a[0]--;
            a[2]--;
            sum++;
        }
        if(a[2]>0&&a[1]>0)
        {
            a[2]--;
            a[1]--;
            sum++;
        }
        //最后算三个
        if(a[0]>0&&a[1]>0&&a[2]>0)
        {
            a[0]--;
            a[1]--;
            a[2]--;
            sum++;
        }
        cout<<sum<<endl;
    }
    return 0;
}

```
但是对于下面这个数据，这个方法就会有漏洞：
```
1
2 2 3
```
正确输出
```
5
```
代码输出：
```
4
```
也就是说，这种方法还有问题。
### Part 3:实现Ⅱ
>兵没了，将军再厉害也要被打败

如果我们取最小情况的话，最小取完了，最大还有很多，这样就得不偿失了。

所以，我们先取最大即可。
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int a[3],sum=0;
bool cmp(int a,int b)
{
    return a>b;
}
int main()
{
    int t;
    cin>>t;
    for(int i=0;i<t;i++)
    {
        cin>>a[0]>>a[1]>>a[2];
        sort(a,a+3,cmp);
        sum=0;
        //先取一个
        if(a[0]>0)
        {
            a[0]--;
            sum++;
        }
        if(a[1]>0)
        {
            a[1]--;
            sum++;
        }
        if(a[2]>0)
        {
            a[2]--;
            sum++;
        }
        //然后两个
        if(a[0]>0&&a[1]>0)//先大
        {
            a[0]--;
            a[1]--;
            sum++;
        }
        if(a[0]>0&&a[2]>0)
        {
            a[0]--;
            a[2]--;
            sum++;
        }
        if(a[2]>0&&a[1]>0)//后小
        {
            a[2]--;
            a[1]--;
            sum++;
        }
        //三个
        if(a[0]>0&&a[1]>0&&a[2]>0)
        {
            a[0]--;
            a[1]--;
            a[2]--;
            sum++;
        }
        cout<<sum<<endl;
    }
    return 0;
}

```


---

## 作者：LB_tq (赞：1)

# Solution
- 看到题目范围，可以得知用搜索。

- 我在这里想介绍一下**二进制枚举子集**的方法：题目中点到每种食品最多只能选一种，我们可以用一个三位二进制数的每一位代表一种食品，1表示选，0表示不选。这样，我们就可以将三种食品的选择情况映射到整数1到7.

- 这种方法的优点在于枚举代码简洁，而且可以使用位运算辅助判断，便于标记某种状态是否已使用。

# Code
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int t,a,b,c,ans,vis[8];//vis数组标记状态是否使用
void dfs(int sum,int x,int y,int z){
	ans=max(ans,sum);//每次更新答案
	int xx=x,yy=y,zz=z;
	for(int i=1;i<=7;i++)//枚举状态
		if(!vis[i]){
			if(i&1)//判断第一位
				x--;
			if((i>>1)&1)//判断第二位
				y--;
			if((i>>2)&1)//判断第三位
				z--;
			if(x>=0&&y>=0&&z>=0){
				vis[i]=1;
				dfs(sum+1,x,y,z);
				vis[i]=0;
			}
			x=xx,y=yy,z=zz;//回溯
		}
}
int main(){
	cin>>t;
	while(t--){
		memset(vis,0,sizeof(vis));
		ans=0;//多测清空
		cin>>a>>b>>c;
		dfs(0,a,b,c);
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：Isprime (赞：0)

CF1313毒瘤比赛

可恶的毒瘤B题卡了我90min……这还是给人做的B题吗

回到正题

## 思路

题目中规定了三个条件

**1. 每个人都至少要有一份食物**

所以不能有什么都不给这种搭配

**2.每个客人不能收到多于一份饺子，不能收到多于一份莓果汁，且不能收到多于一份淋有炼乳的松饼。**

这是题目突破口，这句话表明了每种菜不能多于一份，所以可以得到

|  | 饺子 | 莓果汁 | 松饼 |
| :----------: | :----------: | :----------: | :----------: |
| 1 | 1 | 0 | 0 |
| 2 | 0 | 1 | 0 |
| 3 | 0 | 0 | 1 |
| 4 | 1 | 1 | 0 |
| 5 | 1 | 0 | 1 |
| 6 | 0 | 1 | 1 |
| 7 | 1 | 1 | 1 |


由表格可知：最多有七种不同的搭配方法

**3.每个客人都要有不一样的套餐。**

由于只有七种搭配方法，所以最多只能给七位客人提供套餐

## 实现

楼上大佬说要用dfs，其实有更简便的方法

最多只能满足七位客人，所以我们只需要枚举这七种方法是否可以就行了

```cpp
if(a>=1) ans++,a--;
if(b>=1) ans++,b--;
if(c>=1) ans++,c--;
if(a>=1&&b>=1) ans++,a--,b--;
if(a>=1&&c>=1) ans++,a--,c--;
if(b>=1&&c>=1) ans++,b--,c--;
if(a>=1&&b>=1&&c>=1) ans++;
```
不要在意毒瘤码风……

但是这么做有一个问题

`2 2 3`这组数据，正确输出应该是`5`

然而我们聪明睿智的程序会算出来个`4`

为什么呢？

模拟一下程序运行：

1. `a>=1`成立，`ans=1,a=1,b=2,c=3`

2. `b>=1`成立，`ans=2,a=1,b=1,c=3`

3. `c>=1`成立，`ans=3,a=1,b=1,c=2`

4. `a>=1`成立，`ans=4,a=0,b=0,c=2`

可以发现在第四步出了问题，程序没有找到最优解决方案

因为程序是按照`ab,ac,bc`的优先级去求解的，所以他无法判断出`ac,bc`均成立而不是只有`ab`成立

解决方案也很简单，排个序，把`3`拎到最前面，问题就迎刃而解了

完整代码如下

```cpp
#include <cstdio>
#include <iostream> 
using namespace std;
int t;
int a,b,c,ans;
signed main() {
	scanf("%d",&t);
	while(t--) {
		ans=0;
		scanf("%d%d%d",&a,&b,&c);
		if(a<b) swap(a,b);
		if(b<c) swap(b,c);
		if(a<b) swap(a,b);
		if(a>=1) ans++,a--;
		if(b>=1) ans++,b--;
		if(c>=1) ans++,c--;
		if(a>=1&&b>=1) ans++,a--,b--;
		if(a>=1&&c>=1) ans++,a--,c--;
		if(b>=1&&c>=1) ans++,b--,c--;
		if(a>=1&&b>=1&&c>=1) ans++;
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：ShineEternal (赞：0)

[更佳的阅读效果。](https://blog.csdn.net/kkkksc03/article/details/104465739)

## description：
- 给定你三个数 $a,b,c$ ，保证 $a\le b\le c$。
- 一次操作中，你可以将任何一个数 $+1$ 或者 $-1$ 。
- 问你最少要用多少次操作，可以使得 $a$ 是 $b$ 的因数， $b$ 是 $c$ 的因数。
- **多组数据**，数据组数不大于 $100$，$1\le a,b,c\le 10^4$。
- 先输出最少的操作次数，再输出最终的方案。（方案如果有多组可输出任意一组。）

## solution：
我们发现中间的数 $b$ 是一个与其他两个数都有直接关系的数，所以考虑对 $b$ 进行枚举。

观察数据范围，我们枚举到 $1.5\times 10^4$ 就够了。

然后我们枚举每一个 $b$ 的所有因数，每一个 $b$ 的所有倍数，找到最少的操作次数即可。
## code：
```cpp
#include<cstdio>
#include<cmath>
using namespace std;
int Abs(int x)
{
	if(x<0)return -x;
	return x;
}
int Min(int x,int y)
{
	if(x<y)return x;
	return y;
}
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		int aa,b,c;
		scanf("%d%d%d",&aa,&b,&c);
		int AAA,BBB,CCC;
		int sum=0x3f3f3f3f;
		for(int i=1;i<=15000;i++)
		{
			int ans=0;
			int Zuo,You;
			
			int tmp=0x3f3f3f3f;
			int qaq=sqrt(i);
			ans=Abs(b-i);
			for(int j=1;j<=qaq;j++)
			{
				if(i%j!=0)
				{
					continue;
				}
				if(Abs(aa-j)<tmp)
				{
					tmp=Abs(aa-j);
					Zuo=j;
				}
				if(Abs(aa-(i/j))<tmp)
				{
					tmp=Abs(aa-(i/j));
					Zuo=i/j;
				}
			}
			ans+=tmp;
			tmp=0x3f3f3f3f;
			for(int j=i;j<=32000;j+=i)
			{
				if(Abs(c-j)<tmp)
				{
					You=j;
					tmp=Abs(c-j);
				}
			}
			ans+=tmp;
			if(ans<sum)
			{
				sum=ans;
				AAA=Zuo;
				BBB=i;
				CCC=You;
			}
		}
		printf("%d\n",sum);
		printf("%d %d %d\n",AAA,BBB,CCC);
	}
	return 0;
}
```

---

## 作者：Ludo (赞：0)

## Part I. 思考过程

**套餐**是一组食物，用三元组 $(a,b,c)$ 表示的话，$a,b,c$ 代表每一种食物的数量。

**食物**就是题面里的饺子、莓果汁、淋有炼乳的松饼。

这题是A题，标算肯定不太困难。那么如果考虑贪心，我们或许会想会不会套餐里面食物数量少的先来给客人分配就是答案呢？

写得还挺容易，测测样例吧。嗯，很良心，有错。

思考片刻后，发现做法假了。

再看数据范围。

$0 \leq a,b,c \leq 10$。

诶，好像从这里入手可以哦。

因为 $2^3-1=7$ 是套餐种类数。所以在一组测试数据中最多也只有做$7!$次的检验嘛。

于是使用dfs解决即可。

## Part II. 代码

我的代码比较丑。因为比赛没考虑得透。

不过应该跑得快一点点吧。

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
int T,a,b,c,allt,ans,setting[500][4];
//T,a,b,c的意义跟题面一样。
//allt是套餐的数量共7种。
//ans是答案。
//setting(i,j)是第i种套餐中第j种食物用了多少个。（因为时间关系所以没有特别计算这个i的上界，所以就500算了。）
int dfs(int a,int b,int c,int now,int t)
{
	//if (now<ans) return 0; //这里不可以加。因为还可以再试着加套餐。我不知道为什么自己突然加上去了。
	if (now>ans) ans=now;    //为了剪枝，我们需要保存目前最优答案
	if (t==allt+1) return 0; //最优性剪枝
	for (int i=t+1;i<=allt;i++) //allt就是
	{
		if (a>=setting[i][1]&&b>=setting[i][2]&&c>=setting[i][3])//如果目前还够弄这个套餐
		{
			dfs(a-setting[i][1],b-setting[i][2],c-setting[i][3],now+1,i); //三种食物还剩下来多少，now是做了多少套餐，i因为不想重复选，所以下次dfs时可以用这个
		}
	}
	dfs(a,b,c,now,t+1); //都不选了/不够食物
}
int main(void)
{
	scanf("%d",&T);
	for (int i=0;i<=1;i++)
	{
		for (int j=0;j<=1;j++)
		{
			for (int k=0;k<=1;k++)
			{
				if (i==0&&j==0&&k==0) continue;
				setting[++allt][1]=i;
				setting[allt][2]=j;
				setting[allt][3]=k;
				//cout<<setting[allt][1]<<' '<<setting[allt][2]<<' '<<setting[allt][3]<<endl;
			}
		}
	}
    //setting(i,j)是第i种套餐中第j种食物用了多少个。
	while (T--)
	{
		scanf("%d%d%d",&a,&b,&c);
		ans=0;
		dfs(a,b,c,0,0);
		printf("%d\n",ans);
	}
}
```


---

## 作者：registerGen (赞：0)

题目要求每位顾客的菜是不同的，于是：

>我们可以把 $a,b,c$ 中大于 $4$ 的变成 $4$
>
>而且答案与 $a,b,c$ 的顺序无关（想想为什么？）

于是果断打表，依题意手玩即可~

```cpp
#include<cstdio>
#include<algorithm>

int ans[5][5][5];

// 打表
void init()
{
	ans[0][0][0]=0;
	ans[0][0][1]=1;
	ans[0][0][2]=1;
	ans[0][0][3]=1;
	ans[0][0][4]=1;
	ans[0][1][1]=2;
	ans[0][1][2]=2;
	ans[0][1][3]=2;
	ans[0][1][4]=2;
	ans[0][2][2]=3;
	ans[0][2][3]=3;
	ans[0][2][4]=3;
	ans[0][3][3]=3;
	ans[0][3][4]=3;
	ans[0][4][4]=3;
	ans[1][1][1]=3;
	ans[1][1][2]=3;
	ans[1][1][3]=3;
	ans[1][1][4]=3;
	ans[1][2][2]=4;
	ans[1][2][3]=4;
	ans[1][2][4]=4;
	ans[1][3][3]=4;
	ans[1][3][4]=4;
	ans[1][4][4]=4;
	ans[2][2][2]=4;
	ans[2][2][3]=5;
	ans[2][2][4]=5;
	ans[2][3][3]=5;
	ans[2][3][4]=5;
	ans[2][4][4]=5;
	ans[3][3][3]=6;
	ans[3][3][4]=6;
	ans[3][4][4]=6;
	ans[4][4][4]=7;
}

int main()
{
	init();
	int T;
	scanf("%d",&T);
	while(T--)
	{
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		if(a>4)a=4;if(b>4)b=4;if(c>4)c=4;
		// 排序
		if(a>b)std::swap(a,b);if(a>c)std::swap(a,c);if(b>c)std::swap(b,c);
		printf("%d\n",ans[a][b][c]);
	}
	return 0;
}
```

---

