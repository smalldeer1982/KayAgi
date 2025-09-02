# Initial Bet

## 题目描述

There are five people playing a game called "Generosity". Each person gives some non-zero number of coins $ b $ as an initial bet. After all players make their bets of $ b $ coins, the following operation is repeated for several times: a coin is passed from one player to some other player.

Your task is to write a program that can, given the number of coins each player has at the end of the game, determine the size $ b $ of the initial bet or find out that such outcome of the game cannot be obtained for any positive number of coins $ b $ in the initial bet.

## 说明/提示

In the first sample the following sequence of operations is possible:

1. One coin is passed from the fourth player to the second player;
2. One coin is passed from the fourth player to the fifth player;
3. One coin is passed from the first player to the third player;
4. One coin is passed from the fourth player to the second player.

## 样例 #1

### 输入

```
2 5 4 0 4
```

### 输出

```
3
```

## 样例 #2

### 输入

```
4 5 9 2 1
```

### 输出

```
-1
```

# 题解

## 作者：clockwhite (赞：2)

超级水的一道题
题目大意：有五个人在玩游戏 每个人一开始有b个硬币 有一种操作是把一个硬币给另一个人 给你所有人经过若干次操作的硬币数 求b，若无解输出-1

因为硬币总数不变，五个人下的注又是一样的，所以若每个人最后的硬币数加起来是五的倍数，答案为所有硬币除以5，若除不尽就-1，（注意特判五个0qwq）

第一篇题解望过

---

## 作者：Mr_Avalan (赞：1)

### 题目大意：
有 $5$ 个人，每人都有 $b$ 个硬币，他们可以把自己的一个硬币给另一个人，现在给你经过若干次操作后每个人拥有的硬币数，让你求他们之前每个人有多少硬币。

简单地分析题面，我们可以发现不管他们怎么操作，硬币的总数是始终不变的，所以把硬币的总数求出来后，判断能不能平均分给 $5$ 个人，如果可以就输出总数除以 $5$，如果不能就输出 $-1$。

## 注意

如果硬币的总数是 $0$，那也属于无解，要输出$-1$。

## 上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[6],s=0;
int main()
{
	for(int i=1;i<=5;i++)
	{
		cin>>a[i];//输入
		s+=a[i];//求总数
	}
	if(s%5==0&&s)//如果是5的倍数并且不为0
	{
		cout<<s/5;//输出
		return 0;
	}
	cout<<-1;//因为如果有解在if中程序就结束了,所以这里没有写else
	return 0;
}
```

---

## 作者：JimmyF (赞：1)

 [CF478A Initial Bet 题目直通车](https://www.luogu.com.cn/problem/CF478A)

这题注意硬币总数
**始终不变**
。

如果五个人
**交换后**
的硬币数分别等于
$a$
、
$b$
、
$c$
、
$d$
、
$e$
，
每人一开始有
$x$
枚硬币
。

那么
$a+b+c+d+e=5$
$\cdot$
$x$
。

而五个人交换后的硬币已经分别给出，那除以
$5$
不就是
$x$
，
也就是题目中说的
$b$
了吗。

而除不尽的情况就输出
$-1$
。

但是注意这里还有一个细节，就是如果五个人的硬币总和是
$0$
，也得输出
$-1$
。

### AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c,d,e,sum;
int main()
{
    cin>>a>>b>>c>>d>>e;
    sum=a+b+c+d+e;
    if(sum%5==0&&sum!=0)cout<<sum/5; //注意细节
	else cout<<-1;
    return 0;
}
```



---

## 作者：仗剑_天涯 (赞：0)

首先，这道题的描述（有五个人在玩游戏 每个人一开始有b个硬币 有一种操作是把一个硬币给另一个人 给你所有人经过若干次操作的硬币数 求b，若无解输出-1）经过蒟蒻转化后，大概是这样：
```
所有人的硬币总数必须是五的倍数
```
还有，和为0是无解的。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int x,s; 
void doit()//void表示只做一件事情，不返回值
{
	for(int i=1;i<=5;i++)
    {
        cin>>x;
        s+=x;
    }
    if(s==0)//特判0
	{
		cout<<-1;//无解
		return;//结束函数
	}
    if(s%5!=0) cout<<-1;//无解
    else cout<<s/5;//有解
}
int main()
{
   	doit();//调用过程函数
    return 0;
}
```



---

## 作者：江山_远方 (赞：0)

题目很简单，思路1楼和2楼已经给的很清楚了，今天我们来重点介绍下数组

所谓数组，是有序的元素序列若将有限个类型相同的变量的集合命名，那么这个名称为数组名。组成数组的各个变量称为数组的分量，也称为数组的元素，有时也称为下标变量。用于区分数组的各个元素的数字编号称为下标。数组是在程序设计中，为了处理方便， 把具有相同类型的若干元素按无序的形式组织起来的一种形式。这些无序排列的同类数据元素的集合称为数组。数组是用于储存多个相同类型数据的集合。

数组定义的下标从0开始，实际能使用的为定义大小减一

举个例子 定义int a[10]，实际可使用的下标为a[0]~a[9],若使用了超过范围的数组空间，you'll have Surprise.~~RE抱回家！~~

好吧，数组的使用还需要一些实战，那么看一下这题的代码吧：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[10];
int sum; 
int main()
{
	for(int i=1;i<=5;i++)
	{
		scanf("%d",&a[i]);
		sum+=a[i];
	}
	if(sum%5==0&&sum!=0)cout<<sum/5;
	  else cout<<-1;
	return 0;
} 
```
想实战一下吗？做做这些题吧
：

[陶陶摘苹果](https://www.luogu.org/problemnew/show/P1046)

[校门外的树](https://www.luogu.org/problemnew/show/P1047)

[小鱼的数字游戏](https://www.luogu.org/problemnew/show/P1427)

[小鱼比可爱](https://www.luogu.org/problemnew/show/P1428)

[珠心算测验](https://www.luogu.org/problemnew/show/P2141)

[统计天数](https://www.luogu.org/problemnew/show/P1567)

---

## 作者：yuangq (赞：0)

题目很简单就是要注意特判0的情况

~~~
#include<bits/stdc++.h>
#define MAXN 10005
#define LL long long
using namespace std;
//int a[MAXN];
int main()
{
	//freopen("train.in","r",stdin);
	//freopen("train.out","w",stdout);
	int n,a,b,c,d,e;
	cin>>a>>b>>c>>d>>e;
	n=a+b+c+d+e;//相加 
	if(n%5==0 && n!=0)//如果是五的倍数又不是0，则输出它除以五的商 
	{
		cout<<n/5;
	}
	else//反则输出-1 
	{
		cout<<-1;
	}
	return 0;
}

~~~

---

