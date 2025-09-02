# Walking Robot

## 题目描述

There is a robot staying at $ X=0 $ on the $ Ox $ axis. He has to walk to $ X=n $ . You are controlling this robot and controlling how he goes. The robot has a battery and an accumulator with a solar panel.

The $ i $ -th segment of the path (from $ X=i-1 $ to $ X=i $ ) can be exposed to sunlight or not. The array $ s $ denotes which segments are exposed to sunlight: if segment $ i $ is exposed, then $ s_i = 1 $ , otherwise $ s_i = 0 $ .

The robot has one battery of capacity $ b $ and one accumulator of capacity $ a $ . For each segment, you should choose which type of energy storage robot will use to go to the next point (it can be either battery or accumulator). If the robot goes using the battery, the current charge of the battery is decreased by one (the robot can't use the battery if its charge is zero). And if the robot goes using the accumulator, the current charge of the accumulator is decreased by one (and the robot also can't use the accumulator if its charge is zero).

If the current segment is exposed to sunlight and the robot goes through it using the battery, the charge of the accumulator increases by one (of course, its charge can't become higher than it's maximum capacity).

If accumulator is used to pass some segment, its charge decreases by 1 no matter if the segment is exposed or not.

You understand that it is not always possible to walk to $ X=n $ . You want your robot to go as far as possible. Find the maximum number of segments of distance the robot can pass if you control him optimally.

## 说明/提示

In the first example the robot can go through the first segment using the accumulator, and charge levels become $ b=2 $ and $ a=0 $ . The second segment can be passed using the battery, and charge levels become $ b=1 $ and $ a=1 $ . The third segment can be passed using the accumulator, and charge levels become $ b=1 $ and $ a=0 $ . The fourth segment can be passed using the battery, and charge levels become $ b=0 $ and $ a=1 $ . And the fifth segment can be passed using the accumulator.

In the second example the robot can go through the maximum number of segments using battery two times and accumulator one time in any order.

## 样例 #1

### 输入

```
5 2 1
0 1 0 1 0
```

### 输出

```
5
```

## 样例 #2

### 输入

```
6 2 1
1 0 0 1 0 1
```

### 输出

```
3
```

# 题解

## 作者：灵乌路空 (赞：5)

如果您是看到**蓝题难度**就直接来看题解了  
请您左转 **返回题面** ，再好好看看题目  
此题难度顶天 **普及-**

------------

无良宣传一下博客wwwwww  
[文章列表 - 核融合炉心 - 洛谷博客](https://www.luogu.org/blog/koishikoishi/)


#### 算法：贪心+模拟

在走一段路程的时候，  

可以选择消耗普通电池，也可以选择消耗充电电池    

选择不同的电池，对后续都会有影响  

**则** 在选择电池的策略上，需要用到贪心的思想。 

  - 具体怎么贪：
  
    当两个电池 **非都没有电** ，且 **未到终点** 时，前进。
    
    对于某一条线段： 
      1. 如果当前线段 **不能被阳光照到**：
       
         - 若充电电池有电，选择消耗充电电池
         
         - 否则，选择消耗普通电池
      2. 如果当前线段 **能被阳光照到** ：
      
         - 如果充电电池电量已满，选择消耗充电电池
         
         - 否则，若普通电池有电，选择消耗普通电池，并使充电电池电量加 $1$ 。

------------

按照上述策略，将整个数轴扫一遍。

最后输出 所在点的编号 即可

复杂度为 $O(n)$ , 对本题来说够用了。

------------

#### 附 ~~巨丑的~~ AC代码:
```cpp
#include<cstdio>
using namespace std;
int n,b,a;
int map[10000010];  //存数轴
int main()
{
	scanf("%d%d%d",&n,&b,&a);  //输入
	for(int i=1;i<=n;i++)
	  scanf("%d",&map[i]);
	int i=0;  //存当前所在点
	int b1=b,a1=a;  //存当前电量
	while( (a1 || b1) && i++ <=n)
	  {
	  	if(map[i]==0)  //无光情况
	  	  if(a1)  a1--;
	  	  else  b1--;
		if(map[i]==1)  //有光情况
		  if(b1 && a1<a) b1--,a1++;
		    else a1--;
		if(i==n) break;  //到达终点
	  }
	printf("%d",i);
}
```

---

## 作者：first_fan (赞：3)

$\large\sf\text{本题其实很简单，只要看懂了题就行。}$

分析下题目类型：

### 两种电池：贪心

### 走一步耗一单位电：模拟

好的，我们来看看具体怎么贪：

* 有光的时候，我们可以给太阳能电池充电，当且仅当选择固态电池。说明：在有光时，尽量选择固态电池前进。

* 太阳能电池有上限。我们考虑在无光时，消耗太阳能电池以备下一次充电。

* 如果在到达下一个光段前太阳能电池已满，则可以把该光段视作暗段，因为消耗可再生能源总是最优。

* 两个电池至少有一个不空时，说明走完全程，输出$n$即可。

下面考虑存储电池量：

当前太阳能电池的量$solar[1]$

原来太阳能电池的量$solar[0]$

当前固态电池的量$solid[1]$

原来固态电池的量$solid[0]$

那么每次前进只要找对电池，自减即可。

给出简明代码（已进行疏松处理，应该看着舒适）

```cpp
#include<bits/stdc++.h>
#define ri register int
using namespace std;
bool lit[300000];
int ans=0;
int read()
{
        int num=0;
        int flg=1;
        char c=getchar();
        while(!isdigit(c))
        {
                if(c=='-')
                {
                        flg=-1;
                }
                c=getchar();
        }
        while(isdigit(c))
        {
                num=(num<<1)+(num<<3)+(c^48);
                c=getchar();
        }
        return num*flg;
}
int main()
{
	int solid[2];
	int solar[2];//0->满电 1->现在
	int n=read();
	solar[0]=solar[1]=read();//太阳能
	solid[0]=solid[1]=read();//固态电池
	
	for(int i=1;i<=n;i++)
	{
		lit[i]=read();//光
	}
	for(int i=1;i<=n;i++)
	{
		if(lit[i])//此处有光，优选固态电池
		{
			if(solid[1]<solid[0])//固态不满（用过
			{
				if(solar[1]!=0)//太阳能有电
				{
					solar[1]--;
					solid[1]++;
				}
				else if(solid[1]!=0)//固态电池有电，太阳能无电
				{
					solid[1]--;
				}
			}
			else
			{
				solid[1]--;
			}
			ans++;//走一步
			if(solar[1]==0&&solid[1]==0)
			{
				return 0&printf("%d",ans);
			}//耗尽
		}
		else//无光，优先太阳能
		{
			if(solid[1]!=0)
			{
				solid[1]--;
			}
			else if(solar[1]!=0)
			{
				solar[1]--;
			}//模拟耗电过程
			ans++;
			if(solar[1]==0&&solid[1]==0)
			{
				return 0&printf("%d",ans);
			}//耗尽
		}
	}
	return 0&printf("%d",n);
}
```

---

## 作者：一扶苏一 (赞：2)

[本场题解博客](https://www.cnblogs.com/yifusuyi/p/10727303.html)

# D

## Description

在一个数轴上，有一个机器人要从 $x = 0$ 处移动到 $x = n$ 处。机器人身上有两种电池，第一种是普通电池，第二种是太阳能可充电电池，普通电池的容量上限为 $b$ 点电量，太阳能电池的容量上限为 $a$ 点电量。

定义数轴上的第 $i$ 段线段代表左端点为 $x = i - 1$，右端点为 $x = i$ 的线段。

这 $n$ 条线段中，有一些线段可以被太阳照射到。

当机器人向右移动一个单位时，它会消耗一点电量。

当机器人走到一个可以被太阳照射到的线段上时，如果他是**使用普通电池**走到这条线段的并且**太阳能电池的电量不满**，则可以增加一点电量。这里的线段特指长度为 $1$ 的线段。即如果它从一条被照射到的线段上走到另一条被照射的线段上，依然有可能增加电量。

机器人总电量为 $0$ 或到达终点时会停下。现在请你求出机器人最远可以走多远。

## Limitation

$1~\leq~n,~b,~a~\leq~2~\times~10^5$

$\forall~i~\in~[1,~n],~0~\leq~s_i~\leq~1$

## Solution

考虑贪心。一个显然的事实是不考虑充电时在任意时刻机器人剩的总电量越多走的就越远。那么我们考虑优先使用太阳能电池，因为太阳能电池有恢复的可能。需要充电时会消耗普通电池的能量，于是不充电时优先使用太阳能电池不会更劣。

考虑走到一个能充电的格子上，如果太阳能电池是满的则不能充电，这时用太阳能电池同上可以证明不会更劣。考虑如果不是满的，则贪心的将电冲上。因为充电后电的总量不会减少但是可消耗的太阳能电池能量变多了。

更加严谨的证明可以考虑在可以充电的位置使用太阳能电池不会让答案更优。

于是 $O(n)$ 的扫描整个数轴即可。

## Code

```cpp
#include <cstdio>
#ifdef ONLINE_JUDGE
#define freopen(a, b, c)
#endif

typedef long long int ll;

namespace IPT {
  const int L = 1000000;
  char buf[L], *front=buf, *end=buf;
  char GetChar() {
    if (front == end) {
      end = buf + fread(front = buf, 1, L, stdin);
      if (front == end) return -1;
    }
    return *(front++);
  }
}

template <typename T>
inline void qr(T &x) {
  char ch = IPT::GetChar(), lst = ' ';
  while ((ch > '9') || (ch < '0')) lst = ch, ch=IPT::GetChar();
  while ((ch >= '0') && (ch <= '9')) x = (x << 1) + (x << 3) + (ch ^ 48), ch = IPT::GetChar();
  if (lst == '-') x = -x;
}

namespace OPT {
  char buf[120];
}

template <typename T>
inline void qw(T x, const char aft, const bool pt) {
  if (x < 0) {x = -x, putchar('-');}
  int top=0;
  do {OPT::buf[++top] = static_cast<char>(x % 10 + '0');} while (x /= 10);
  while (top) putchar(OPT::buf[top--]);
  if (pt) putchar(aft);
}

const int maxn = 200010;

int n, a, b;
int MU[maxn];

int main() {
  freopen("1.in", "r", stdin);
  qr(n); qr(a); qr(b);
  int x = a, y = b;
  for (int i = 1; i <= n; ++i) qr(MU[i]);
  for (int i = 1; i <= n; ++i) {
    if ((x | y) == 0) {
      qw(i - 1, '\n', true);
      return 0;
    } else {
      if (MU[i]) {
        if ((y == b) || (x == 0)) {
          --y;
        } else {
          --x; ++y;
        }
      } else {
        if (y == 0) --x;
        else --y;
      }
    }
  }
  qw(n, '\n', true);
  return 0;
}
```

---

## 作者：Disjoint_cat (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1154D)

## 0.前言

不要看到这是道蓝题就直接看题解，我认为这题只有**橙题**难度。

## 1.题意

一个机器人，初始时在数轴的位置 $0$ 上。它有两块电池，一块能充电电量为 $a$，另一块不能充电，电量为 $b$。

在这条数轴上，有一些位置，如果使用了不可充电的电池走到这里，就可以给充电电池充电。当机器人没有电或走到终点的的时候就会停下。

求机器人最远能走到哪里。

## 2.解法

算法：**贪心**。

讨论每个位置。

1. 如果这个位置能充电：

	- 当充电电池电量不满，且普通电池有电时，那么给充电电池充电一定比不充电更好，所以使用普通电池并充电；
    
   - 当普通电池没电时，显然只能用充电电池；
   
   - 当充电电池满电时不能充电，那么不应浪费能为充电电池充电的普通电池，应使用充电电池。
   
2. 如果这个位置不能充电：

	- 如果充电电池有电，则应用充电电池，因为普通电池可以为充电电池充电。
    
   - 如果充电电池没电，则只能用普通电池。
   
当然，如果没电了，直接输出该位置即可。

这样，每个位置都只需要 $O(1)$ 的时间判断，总的时间复杂度为 $O(n)$。

## 3.code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200005;
int n,a,b,A;//a是当前充电电池电量，A是上限。
bool s[N];
int main()
{
	cin>>n>>b>>A;
	a=A;
	for(int i=1;i<=n;i++)scanf("%d",&s[i]);
	for(int i=1;i<=n;i++)
	{
		if(s[i]==1)
			if(b&&a<A)b--,a++;
			else a--;
		else
			if(a)--a;
			else --b;
		if(a+b==0)
		{
			cout<<i;
			return 0;
		}
	}
	cout<<n;
	return 0;
}
```

---

## 作者：Pretharp (赞：1)

~~*这道题评蓝是认真吗 QwQ*~~

### 1、实现思路

这道题目稍稍贪心即可。

如果这里没有阳光，我们可以优先使用太阳能电池，因为太阳能电池是可以充电的。

如果这里有阳光，我们尽量使用普通电池让太阳能电池充电。前提是太阳能电池电量不满，如果满了还是优先使用太阳能电池，这样太阳能电池才能在下一次继续充电。

**注意一下，初始电量是满的，~~题目里是没有说吗 QAQ 。~~**

### 2、代码实现

奉上简短的代码，具体看注释吧！

```cpp
#include<bits/stdc++.h>
#define int long long
#define QwQ while(233==233) cout<<"yee"
using namespace std;
const int N=2e5+5;
int k[N],n,B,A,b,a;
// k 数组用于储存每个线段的状态 （即是否有阳光）。
// n 是数组长度， A、B 是电量上限，a、b 是当前电量。 
signed main()
{
	QwQ; // QwQ
	cin>>n>>B>>A;
	for(int i=1;i<=n;i++) cin>>k[i];
	b=B,a=A;
	// 输入，并将当前电量初始化成电量上限。 
	for(int i=1;i<=n;i++){
		if(k[i]==0){ // 如果此地没有阳光。 
			if(a) a--; // 优先使用太阳能电池。
			else if(b) b--; // 如果太阳能电池的电已经用完，则使用普通电池。 
			// 使用的条件是有电。 
		}else{ // 如果此地有阳光。 
			if(a==A) a--; // 如果太阳能电池电量已满，也使用太阳能电池。 
			else if(b) b--,a++; // 否则，使用普通电池，并为太阳能电池充电。 
			else if(a) a--; // 如果普通电池的电已经用完了，那就只能使用太阳能电池了。 
			if(a>A) a=A; // 注意不要让太阳能电池的电量超过上限。 
		}
		if(!a && !b){ // 如果两种电池的电都用完了，机器无法继续前行。 
			cout<<i;
			return 0;
		}
	}
	cout<<n; // 特殊情况，如果机器到达终点还有电，那就输出 n 。 
    return 0;
}
```

---

