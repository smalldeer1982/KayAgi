# Pseudorandom Sequence Period

## 题目描述

Polycarpus has recently got interested in sequences of pseudorandom numbers. He learned that many programming languages generate such sequences in a similar way: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF172B/02c4eeecb957768b3b96e1481a979d6934aab656.png) (for $ i>=1 $ ). Here $ a $ , $ b $ , $ m $ are constants, fixed for the given realization of the pseudorandom numbers generator, $ r_{0} $ is the so-called $ randseed $ (this value can be set from the program using functions like RandSeed(r) or srand(n)), and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF172B/99fd5677ca5c02520be7595d9b1eaf3e9972e601.png) denotes the operation of taking the remainder of division.

For example, if $ a=2,b=6,m=12,r_{0}=11 $ , the generated sequence will be: $ 4,2,10,2,10,2,10,2,10,2,10,... $ .

Polycarpus realized that any such sequence will sooner or later form a cycle, but the cycle may occur not in the beginning, so there exist a preperiod and a period. The example above shows a preperiod equal to 1 and a period equal to 2.

Your task is to find the period of a sequence defined by the given values of $ a,b,m $ and $ r_{0} $ . Formally, you have to find such minimum positive integer $ t $ , for which exists such positive integer $ k $ , that for any $ i>=k $ : $ r_{i}=r_{i+t} $ .

## 说明/提示

The first sample is described above.

In the second sample the sequence is (starting from the first element): $ 0,3,4,1,0,3,4,1,0,... $

In the third sample the sequence is (starting from the first element): $ 33,24,78,78,78,78,... $

## 样例 #1

### 输入

```
2 6 12 11
```

### 输出

```
2
```

## 样例 #2

### 输入

```
2 3 5 1
```

### 输出

```
4
```

## 样例 #3

### 输入

```
3 6 81 9
```

### 输出

```
1
```

# 题解

## 作者：Bla_Bla (赞：6)

这个蒟蒻又来写水题题解了。

首先，仔细读题。看到题目中的**伪随机**没有。有这句话，我们就可以快乐循环了。什么？你问为什么？（~~没有为什么~~

>伪随机数可以用计算机大量生成，在模拟研究中为了提高模拟效率，一般采用伪随机数代替真正的随机数。模拟中使用的一般是**循环周期极长**并能通过随机数检验的伪随机数，以保证计算结果的随机性。

——摘自百度百科

度娘一下，她会告诉你伪随机的循环周期极长。虽然长，但是它还是会循环回来。所以，我们的做法是可行的。具体实现在代码里了。

#### 代码：
```
#include<bits/stdc++.h>
using namespace std;
int Bla[100000];//开大点,绝对没问题的
int main()
{
	int i=1,a,b,m,x;
	memset(Bla,0,sizeof(Bla));//清零
	cin>>a>>b>>m>>x;
	while(1)//直接循环
	{
		x=(a*x+b)%m;//题目中的生成方式
		if(Bla[x]!=0)//如果这个数出现过了
		{
			cout<<i-Bla[x];//输出,结束
			return 0;
		}
  		Bla[x]=i;//记录
  		i++;//不要忘了累加!
	}
}
```

**~~拒绝白嫖,从这次一定开始!~~**

---

## 作者：FQR_ (赞：5)

[题目传送门](https://www.luogu.com.cn/problem/CF172B)

这道题完全可以暴力解决。

可以建立一个`map`
```cpp
map<int,int>k;
```
此时，`k[i]`表示 $i$ 第一次出现的位置。如果 $i$ 没出现过，它就是 $0$ 。

建立一个循环，每次求出 $x$ 的值。如果 $x$ 之前出现过，就能算出循环节的长度了。
___
### AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int a,b,m,x;
	cin>>a>>b>>m>>x;
	map<int,int>k;
	for(int i=1; ;i++)//每次循环i增加1，无终止条件
	{
		x=(a*x+b)%m;
		if(k[x]==0) k[x]=i;//x之前没出现过，记录
		else //x之前出现过，用现在的位置减第一次出现的位置，就是循环节长度
		{
			cout<<i-k[x];
			break;
		}
	}
	return 0;
}

```

---

## 作者：Tune_ (赞：1)

木有c++题解？不如本蒟蒻来一篇QWQ

其实这题水得一批，~~只需要20行~~。

多试几个数据，就会发现，只要出现重复数字，就会无限循环。

可以用一个桶，初始值为0，第一次出现就记录位置，第二次就可以算出循环节长度并输出。

代码如下：

```
#include<bits/stdc++.h>
using namespace std;
int a,b,m,r,s=0,t[100005]={0};//t就是个桶
int main()
{
	cin>>a>>b>>m>>r;
	while(1)//计算
	{
		s++;
		r=(a*r+b)%m;//题目给的公式
		if(t[r]==0)//没出现过
			t[r]=s;//标记一下
		else//出现过
		{
			cout<<s-t[r];//输出长度
			return 0;//拜了个拜~
		}
	}
	return 0;//并没用
}
```
走过路过，点个赞鸭~(〃'▽'〃)~

---

## 作者：Morax2022 (赞：0)

# CF172B 题解
**先读题**

题目先给定了一个公式，然后让我们不断求 $x$ 来算出循环节，因为本蒟蒻不会用 map 所以我用数组模拟了一下。
 
每当算出了一个数，就判这个数是否出现过，若出现过就证明出现循环了，用当前算出数的总个数减去前面没循环的部分，输出然后跳出循环即可。

# AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int appear[100001]; //此数组用来记录循环节出现的数（相当于一个桶） 
int main()
{
	int a, b, m, x;
	cin >> a >> b >> m >> x;
	int cnt = 0;//循环节长度 
	while (1)
	{
		cnt++;
		x = (a * x + b) % m; //公式
		if (appear[x])
		{
			cout << cnt - appear[x]; //记录数量要减去开头多余 
			break;
		 }
		 appear[x] = cnt; //反复利用 
	}
}
```
希望本题解能给大家带来帮助！

---

## 作者：ZhanPJ (赞：0)

题目传送门：[CF172B](https://www.luogu.com.cn/problem/CF172B)

---

**题目大意：**

给出随机数生成函数，求得其循环节长度。

随机函数：
```cpp
while(1){//修改成了 C++ 版本。
  x=(a*x+b)%m;
  printf("%d",x);
}
```

---

**解题思路：**

我们发现数字会取余 $m$，所以生成的数字在 $0$ 到 $m$ 的区间内。而我们知道循环节的出现一定由一个已经出现过的数字为开始（证明见后）。

所以我们做一个数组 $vis$ 用 $vis_i$ 来存储数字 $i$ 第一次出现的位置 $id$。如果 $vis_i$ 为 $0$，证明 $i$ 没有出现过，不管。如果不为 $0$，那么 $i$ 就出现过了，输出本次的 $id$ 减去上次的 $id$ 即可。

---
**证明：**

在输入过 $a$ 和 $b$ 之后，$a$ 和 $b$ 已经成定值，而 $m$ 仅限制取值区间。

所以，对于任意 $x$， $a \times x + b$ 的值是固定的。那么取余 $m$ 的结果也是定值。

因为结果的值可以确定，所以出现相同数字就代表有循环节出现。

---
**代码：**
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
int vis[100005];
int main(){
	int a,m,b,x,i=1;
	scanf("%d%d%d%d",&a,&b,&m,&x);
	vis[x]=1; 
	while(1){
		x=(a*x+b)%m;//题目给的代码
		i++;
		if(vis[x])return !printf("%d",i-vis[x]);
		vis[x]=i;
	}
    //因为取余 m，如果有可能 0 到 m-1 都跑了一遍，它必定会出现循环节。
    //所以使用 return !printf("%d",i-vis[x]); 即可。
} 
```

---

## 作者：duchengjun (赞：0)

# 题意

给你一个生成函数 $x_i=(a \times x_{i-1}+b)\mod m$，在给你 $a$，$b$，$m$ 和 $x_0$，让你求这个数列的循环节是多少。

# 分析

在这题中每一个 $x_i$ 都有一个对应的 $x_{i+1}$，及一旦 $x_i$ 再次出现，则循环节已经出现，为这一次出现的位置与上一次出现的位置之间的元素个数。

我们记录每一个元素的第一次出现的位置，若这个元素再次出现就求解即可。

# Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define For(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int M=1e5+10;
int vis[M];
int a,b,m,r;
signed main(){
	cin>>a>>b>>m>>r;
	for(int i=1;;i++){
		r=(a*r+b)%m;
		if(vis[r]!=0){
			cout<<i-vis[r];
			return 0;
		}
		vis[r]=i;
	}
	return 0;
}

```


---

## 作者：LeTu_Jun (赞：0)

**语言：C++**

这道题主要内容就是给一个生成数字的代码，然后我们需要找出这些数字生成的规律。

循环节小学就学过了，这里不再赘述。

这里重点讲一下伪随机的概念。

------------

伪随机可以理解为使用计算机生成的一些**近似**随机的数。注意这些数是**近似**随机，不完全随机。也就是说这些数还是有一定的规律。

伪随机数与两个因素有关。

1. 生成代码

1. 初值（种子）

注：初值也就是题目里的$\;a$ , $b$ , $m$ , $x$ 。

如果其中哪一项变动，生成的数列就会与原来不一样。


------------
接下来我们来看题本身。

```cpp
i=1
while true:
  x=(a*x+b)%m
  print(x)
```
这是题目里给的伪随机数生成代码。

但是很明显，它不能直接在 C++ 里使用，需要稍稍转换一下才能使用。

转换之后是这个样子：
```cpp
int i=1;
while(1){
	x=(a*x+b)%m;
	printf("%d",x);
	//或：
     //cout<<x<<" ";
     i++;
}
```
然后我们可以使用桶排序的思想，创建一个数组用于存放这个数是否出现过，0就代表没出现，非0就代表出现过了。这样就可以判断循环节了。

可以把这些都封装在一个函数里。
```cpp
void Pseudorandom ()
{
    int i=1;	
    while(1){
       x=(a*x+b)%m;
    	 if(s[x]!=0) 
    	 {
    	     printf("%d",i-s[x]);
    	     //或：
             //cout<<x<<" ";
    	     return ;
         }
		 else
		 {
		     s[x]=i;
		     i++;
		 }
	 }
}
```

那么主函数就会变的非常简单。
```cpp
int main ()
{
	scanf("%d%d%d%d",&a,&b,&m,&x);
	Pseudorandom();
	return 0;
}
```
这道题还是很简单的，要点：

- 理解伪循环

- 使用桶排序的思想理解判断循环节的过程 

具体实现很简单，完整代码就不给了。




---

## 作者：Level_Down (赞：0)

### 题意简述

由给定的a, b, m, x生成一个伪随机数数列，并求出它的循环节并输出。

### 方法：

跟楼上一样，我看到这题目后想到的也是开个桶，但做法与楼上稍有不同。

我开了两个桶，第一个存储某数的出现次数，第二个存储这数第一次的出现位置。

当生成到的数对应的桶大于1，输出现在的项数减去第二个桶中的数就行了。

现在我来解释下为什么最后**输出现在的项数减去第二个桶中的数**。

因为每次伪随机数的生成都是通过固定公式：x=(a*x+b)%m 的，所以当第二次出现某数时，就会按照第一次循环之后的顺序继续出现第三次。

所以担心会出现类似：7 6 7 5 7 5 …… 循环节为{7， 5}的情况是多余的。

最后上一下我的代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int a,b,m,x,tong1[100000],tong2[100000];//桶一桶二功能如上 。 
int main()
{
	cin >> a >> b >> m >> x;
	for (int i = 1;;i++)//相当于while(1),但可以不用手动累加i。 
		{
			x = (a * x + b) % m;//公式。 
			tong1[x]++;
			if (tong1[x] > 1) {cout << i - tong2[x] << endl; return 0;}//解释如上。 
			tong2[x] = i;//因为有可能循环到第二次，所以最后改变桶二的值。 
		}
	return 0;//AC	
}
```

希望我的题解能让大家对这道题有更深的理解，祝大家AC愉快！

---

