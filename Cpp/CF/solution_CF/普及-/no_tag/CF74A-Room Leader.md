# Room Leader

## 题目描述

比赛开始时，参赛者被分进几个不同的房间。每个房间恰好包含 $n$ 位参赛者。在比赛中，参与者被要求解决五个问题， $A$ 、 $B$ 、 $C$ 、 $D$ 和 $E$ 。

对于每个问题，参赛者会根据解决给定问题的时长以及是否彻底解决获得一些积分。此外，参赛者可以对其他参赛者进行攻击。每成功攻击一次，即可赢得 $100$ 分；攻击不成功一次，则会损失 $50$ 分。每个参赛者的得分由他从所有问题及攻击中获得的得分总和表示。

请确定给定的一个房间内得分最高的参与者。

## 说明/提示

$0 \leqslant plus_i,minus_i \leqslant 50$ ；

 $150 \leqslant a_i \leqslant 500$ 或 $a_i=0$ （若问题 $A$ 没有解决）；

 $300 \leqslant b_i \leqslant 1000$ 或 $b_i=0$ （若问题 $B$ 没有解决）；

 $450 \leqslant c_i \leqslant 1500$ 或 $c_i=0$ （若问题 $C$ 没有解决）；

 $600 \leqslant d_i \leqslant 2000$ 或 $d_i=0$ （若问题 $D$ 没有解决）；

 $750 \leqslant e_i \leqslant 2500$ 或 $e_i=0$ （若问题 $E$ 没有解决）；

所有数字都是整数。所有参与者都有不同的名称。可以确保房间中不存在多个参与者分数均为最高。

## 样例 #1

### 输入

```
5
Petr 3 1 490 920 1000 1200 0
tourist 2 0 490 950 1100 1400 0
Egor 7 0 480 900 950 0 1000
c00lH4x0R 0 10 150 0 0 0 0
some_participant 2 1 450 720 900 0 0
```

### 输出

```
tourist```

# 题解

## 作者：Eason_AC (赞：0)

## Content
一场 CF 比赛有 $n$ 个人，有 ABCDE 五道题目。在比赛过程中，参赛者还可以随时互相攻击，成功一次加 $100$ 分，失败一次扣 $50$分，已知第 $i$ 个人攻击成功了 $plus_i$ 次，失败了 $minus_i$ 次，并且 TA 五道题目的分数分别是 $a_i,b_i,c_i,d_i,e_i$。试判断出本场比赛的第一名。

## Range

**$n,plus_i,minus_i$ 的范围：**

$1\leqslant n\leqslant 50,0\leqslant plus_i,minus_i\leqslant 50$。

**$a_i,b_i,c_i,d_i,e_i$ 的范围：**

$150\leqslant a_i\leqslant 500,300\leqslant b_i\leqslant 1000,450\leqslant c_i\leqslant 1500,600\leqslant d_i\leqslant 2000,750\leqslant e_i\leqslant 2500$。但是其中 $a_i,b_i,c_i,d_i,e_i$ 中的任意一个都可以为 $0$，代表五个问题中可能会有没解决出来的。

## Solution
这道题目属于看完了以后立马就会有思路的，也就是说，我们可以用**模拟**的方法解决。

可以很明显的知道，第 $i$ 为参赛者的得分就是 $100\cdot plus_i-50\cdot minus_i+a_i+b_i+c_i+d_i+e_i$，计算完分数后再按照分数为关键字排序，输出第一位的名字就可以通过这道题目了。
## Code
```cpp
#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <cmath> 
#include <algorithm>
using namespace std;

struct user {
	string name;
	int win, lose, ai, bi, ci, di, ei;
	long long score;
	bool operator < (const user& kkk) const {return score > kkk.score;}
}a[57];
int n;

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		cin >> a[i].name;
		scanf("%d%d%d%d%d%d%d", &a[i].win, &a[i].lose, &a[i].ai, &a[i].bi, &a[i].ci, &a[i].di, &a[i].ei);
		a[i].score = a[i].win * 100 - a[i].lose * 50 + a[i].ai + a[i].bi + a[i].ci + a[i].di + a[i].ei;
	}
	sort(a + 1, a + n + 1);
	cout << a[1].name;
	return 0;
}
```

---

## 作者：Sham_Sleep (赞：0)

字符串+排序+模拟，上手秒切

算得上是普及-的难度，类似的题还有贪婪的送礼者。

总体来说就是定义一个结构体，将每个人的名字记录下来，然后根据题目计算每个人的分数。

最后用sort+自定义排序就可以了（也可以使用下标进行排序）

AC代码
```
#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;


struct people{
	char name[105];
	int tr;
	int fa;
	int s;
};


int cmp(people a , people b)
{
	return a.s > b.s; 
}


int n;
people p[55];


int main()
{
	scanf("%d" , &n);
	for(int  i = 1; i <= n; ++i){
		scanf("%s" , p[i].name);
		scanf("%d %d" , &p[i].tr , &p[i].fa);
		p[i].s = p[i].tr * 100 - p[i].fa *50;
		int t;
		for(int j = 1; j <= 5; ++j){
			scanf("%d" , &t);
			p[i].s += t;
		}
	}
	sort (p + 1 , p + 1 + n , cmp);
	printf("%s" , p[1].name);
}
```


---

## 作者：Peter0701 (赞：0)

规定一次成功的攻击加 $100pts$ ，失败的攻击加 $50pts$ 。设一个选手的总得分是攻击分数与做题得分之和。

给定 $n$ 个选手的姓名、成功攻击次数、失败攻击次数以及 $A,B,C,D,E$ 五题的得分，求总得分最大的选手姓名。

做法是按照题意模拟。将每个人的姓名以一个字符串 $name_i$ 的形式存起来，直接根据读入算出得分 $val_i$ ，然后遍历一遍所有的选手找出 $\max \{ val_i \}(i \in [1,n])$ ，存下该最大得分所对应的选手位置 $pos$ ，然后输出 $name_{pos}$ 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int ret=0,f=1;
	char ch=getchar();
	while(ch>'9'||ch<'0')
	{
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		ret=(ret<<1)+(ret<<3)+ch-'0';
		ch=getchar();
	}
	return ret*f;
}
const int inf=1e9+7;
int n,val[55],maxn=-inf,pos;
char name[55][25];
int main()
{
	n=read();
	for(register int i=1;i<=n;i++)
	{
		cin>>name[i];
		val[i]=read()*100-read()*50+read()+read()+read()+read()+read();
	}
	for(register int i=1;i<=n;i++)
	{
		if(val[i]>maxn)
		{
			maxn=val[i];
			pos=i;
		}
	}
	printf("%s",name[pos]);
	return 0;
}
```

---

