# [AGC030A] Poisonous Cookies

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc030/tasks/agc030_a

高橋君は、解毒剤入りの美味しくないクッキーを $ A $ 枚、解毒剤入りの美味しいクッキーを $ B $ 枚、毒入りの美味しいクッキーを $ C $ 枚持っています。

高橋君は、毒入りのクッキーを食べるとお腹を壊し、お腹を壊した状態で毒入りのクッキーを食べると死んでしまいます。 高橋君は死にたくないので、お腹を壊した状態で毒入りのクッキーを食べることはできません。 お腹を壊した状態で解毒剤入りのクッキーを食べると、お腹の調子が治ります。 解毒剤入りのクッキーを食べる以外に、お腹の調子を治す方法はありません。

高橋君が食べることのできる美味しいクッキーの枚数の最大値を求めてください。

## 说明/提示

### 制約

- $ 0\ \leq\ A,B,C\ \leq\ 10^9 $
- $ A,B,C $ は整数である

### Sample Explanation 1

以下のような順番でクッキーを食べることで、美味しいクッキーをすべて食べることができます。 - 毒入りの美味しいクッキー - 解毒剤入りの美味しくないクッキー - 毒入りの美味しいクッキー - 解毒剤入りの美味しいクッキー - 毒入りの美味しいクッキー - 解毒剤入りの美味しくないクッキー - 毒入りの美味しいクッキー

## 样例 #1

### 输入

```
3 1 4```

### 输出

```
5```

## 样例 #2

### 输入

```
5 2 9```

### 输出

```
10```

## 样例 #3

### 输入

```
8 8 1```

### 输出

```
9```

# 题解

## 作者：_acat_ (赞：2)

此题建议评红。
### 题目大意
翻译说的很清楚了，就不解释了，请自行阅读。[Link](https://www.luogu.com.cn/problem/AT4510)
### 思路
我们可以分成两种情况来分析。

1. 当 $A+B \geq C$ 时，代表可以把所有的好吃的毒饼干和好吃的解毒饼干全部吃下去，所以这时候的答案就是： $B+C$。

2. 当 $A+B<C$ 时，我们就可以先吃一个毒饼干，再吃一个解毒饼干，再吃一个毒饼干，再吃一个解毒的饼干……注意，**~~可爱的~~高桥君同学可以在最后没有解药饼干的时候吃下一个毒饼干**，所以这时候的答案就是：$B×2+A+1$。

### 代码
~~都讲这么详细了，还要代码嘛~~

**C++:**
```cpp
#include<iostream>
using namespace std;
int main()
{
	int a,b,c;
    cin>>a>>b>>c;
    if(a+b>=c)
    	cout<<b+c;
    else
    	cout<<b*2+a+1;
    return 0;
}
```
**C：**
```c
#include<stdio.h>
int main()
{
	int a,b,c;
    scanf("%d%d%d",&a,&b,&c);
    if(a+b>=c)
    {
        int ans=b+c;
    	printf("%d",ans);
    }
    else
    {
        int ans=b*2+a+1;
    	printf("%d",ans);
    }
    return 0;
}
```

---

## 作者：CornのQ (赞：2)

本蒟蒻第一篇题解！~~生活不易，赚点估值~~
楼上的有直接计算的，于是我就选择了易懂而又方便的——暴力模拟
以下为AC代码：
```
#include <bits/stdc++.h>//霸气的の万能头 
using namespace std;
long long int a,b,c,sum=0,sun=0,s=0;
int main()
{
	cin>>a>>b>>c;
	while(s==0)//其实这个while主要用于循环，不用于判断 
	{
	    if(sum==0)//sum记录状况。“1”为中毒，“0”为没中毒 
	{ //以下为没中毒状态 
		if(c>0)//有没有毒饼干 
		{
		--c; 
		++sum;//改变状态，为中毒状态 
		++sun;	//记录吃了几块饼干 
		}
	     else
	    {
	    break;
	    }
	}	
	else
	{// 以下为中毒 
		if(b>0)//看看有木有可以解毒的好吃的饼干 
		{
		--b; 
		--sum;
		++sun;
		}
		else
		{
			if(a!=0)//没有好吃的只能吃不好吃的 
			{
			--a;
			--sum;	
			}
			else
			{
			cout<<sun;//如果都没有，只能结束了 
			return 0;
			}
		}
	}
   }
   cout<<sun+b;//因为没有毒饼干了，所以把好吃的解读饼干吃了（b） 
	return 0;
}
```
如果要模拟的话，有特别多的特判，一个样例一个特判，调了好久QAQ
**代码不易，拒绝"Ctrl+c"**（不过这题挺㵘的【滑稽】）

---

## 作者：S__X (赞：1)

### 题意：
有 $A$ 个难吃的解毒饼干，$B$ 个好吃的解毒饼干和 $C$ 个好吃的有毒饼干，问最多能吃多少个好吃的饼干?
### 思路：
1. 当 $A+B\ge C$ 时，最多能吃 $B+C$ 个好吃饼干。
2. 当 $A+B<C$ 时，最多能吃 $B+B+A+1$ 个好吃饼干。

#### 思路二原因：
1. 吃一个 $C$ 饼干，再吃一个 $B$ 饼干，重复执行直到 $B$ 耗尽为止。这时共吃了 $B+B$ 个好吃有毒饼干。
2. 因为 $A+B<C$，所以 $C-B>A$，因此，还可以吃 $A$ 个好吃有毒饼干，此时共吃了 $B+B+A$ 个好吃有毒饼干。
3. 题目中说在中毒情况下，在吃一个毒曲奇就会去世。因此最后可以吃一个吃有毒饼干，此时共吃了 $B+B+A+1$ 个好吃有毒饼干。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int a,b,c;
    cin>>a>>b>>c;
    if(a+b>=c) cout<<b+c<<endl;
    else cout<<b+b+a+1<<endl;
    return 0;
}
```

---

## 作者：Fr0sTy (赞：1)

### 题意简述
------------

题目给定有 $A$ 个不好吃的解毒曲奇，$B$ 个好吃的解毒曲奇，$C$ 个好吃的有毒曲奇

吃了一个有毒曲奇就会中毒，在中毒情况下，吃下一个解毒曲奇可以解毒，但在中毒情况下，在吃一个毒曲奇就会去世。

问最多可以吃多少个好吃的曲奇。

### 解题思路
------------

**分类讨论**。

1. $a+b \geqslant c$

这意味着他可以将所有好吃的饼干都吃完，所以这里输出 $b+c$ 即可。

2. $a+b < c$

这表示他无法将所有的饼干吃完，但他可以将所有的好吃的解毒曲奇吃完（$b$ 块），也能吃完 $a+b$ 块好吃的有毒曲奇，且**最后还能吃一块**好吃的有毒曲奇。这时输出 $a + 2 \times b +1$ 即可。

### 代码实现
------------

``` cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c;
int main() {
	scanf("%d%d%d",&a,&b,&c);
	if(a+b>=c) printf("%d",b+c);
	else printf("%d",a+b*2+1);
	return 0;
}
//code by TheCedar
```

---

## 作者：wheneveright (赞：1)

[AT4510 [AGC030A] Poisonous Cookies](https://www.luogu.com.cn/problem/AT4510)

## 解析

首先 $B$ 个好吃的无毒饼干是一定可以吃的。

然后考虑如果 $C$ 很大的时候可以吃几个 $C$，可以一个有毒饼干加上一个解毒饼干，最后再吃一个有毒饼干（这样虽然中毒，但是死不掉），所以这种情况就是 $A + B + 1$。

然后 $C$ 比较小的情况肯定就是 $C$。

所以贡献就是 $B + \min (A + B + 1, C)$。

## 代码

其实上面这句话已经说明白了。

不明白为什么别的题解那么长。

```cpp
# include <bits/stdc++.h>
using namespace std;

int a, b, c;

int main () {
	cin >> a >> b >> c;
	cout << b + min (c, a + b + 1) << endl;
	return 0;
}
```

---

## 作者：sxb2007 (赞：1)

# 其实还有更~~简单~~暴力的方法:模拟！！！
 _（说明在代码中）_ 

------------
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c,hc=0;
int main()
{
	cin>>a>>b>>c;
	while(1)//开始循环
	{
		if(c>0)//有毒饼干也是好吃饼干
		{
			if(b>0)//如果有好吃解毒饼干，数量就加2
			{
				hc+=2;
				b--;
				c--;
			}
			else if(a>0)//如果没有,数量就加一
			{
				hc++;
				a--;
				c--;
			}
			else//如果都没有,那么久输出并结束
			{
				cout<<hc+1<<endl;//吃一个有毒饼干并不会死
				return 0;//结束
			}
		}
		else//如果没有有毒饼干,那么退出循环
		{
			break;
		}
	}
	cout<<hc+b<<endl;//剩下的好吃解毒饼干也能吃
	return 0;
}
```


---

## 作者：sxb2007 (赞：1)

### 先奉上翻译：


------------

### 高桥君有A块加入了解毒剂的难吃曲奇，B块加入了解毒剂的美味曲奇，C块有毒的美味曲奇。


------------

### 高桥吃了有毒的饼干会坏肚子，肚子坏了吃有毒的饼干会死。高桥君不想死，所以不能在肚子坏了的状态下吃含毒的曲奇。在肚子坏了的状态下吃含有解毒剂的曲奇的话，肚子就会好起来。除了吃含有解毒剂的饼干以外，没有治好肚子状况的方法。


------------

### 请求高桥君能吃到的美味曲奇数量的最大值。
### 有2种情况：


------------

### 第一种：解毒饼干数量大于有毒饼干，那么美味饼干数量为好吃的解毒饼干和有毒饼干的总数。
```cpp
if(a+b>=c)
{
	cout<<b+c;
}

```
### 第二种：解毒饼干数量小于有毒饼干，那么美味饼干数量为好吃的解毒饼干的数量乘 2 再加难吃解毒饼干再加 1 。
```cpp
if(a+b<c)
{
	cout<<b*2+a+1;
}

```
### 奉上完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c;
int main()
{
	cin>>a>>b>>c;
	if(a+b>=c)//第一种方法
	{
		cout<<b+c;
	}
	if(a+b<c)//第二种方法
	{
		cout<<b*2+a+1;
	}
	return 0;
}
```


---

## 作者：EthanC_ (赞：0)

本题是一道思维题。
### 思路：
因为有两种曲奇好吃，一种是有毒的，一种是无毒的，所以我们只需知道以下几个条件即可：
- 如果无毒的曲奇数之和大于等于有毒的曲奇数，那么就可以吧两种好吃的（包含有毒与无毒）曲奇都吃下肚。
- 如果无毒的曲奇数之和小于有毒的曲奇数，那么他可以吃一个有毒再吃一个解毒，等到没了解毒曲奇后再吃一个有毒的曲奇。可以推出公式 $ b\times 2+a+1 $。

### 代码：
```cpp
//AT4510题解代码
#include<iostream>
using namespace std;
typedef long long LL;
inline LL read(){//快读
	register LL x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return x*f;
}
inline void write(int x){//快写
    if(x<0){putchar('-');x=-x;}
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
int main(){
    int a,b,c;
    a=read();b=read();c=read();
    if(a+b>=c)
        write(b+c);
    else 
        write(b*2+a+1);
    return 0;
}
```


---

## 作者：Tobiichi_Origami (赞：0)

一道简单的**数学**题

**题目大意**

有 $a$ 个难吃的解毒饼干，$b$ 个好吃的解毒饼干和 $c$ 个好吃的有毒饼干，问最多能吃多少个好吃的饼干？

**思路**

众所周知，有毒的饼干是好吃的，所以如果可以在保证自己不死的情况下，我们可以把有毒饼干都吃了，同时也可以把好吃的解毒饼干和难吃的解毒饼干全吃了，也就是 $b+c$ 个好吃的饼干。可如果解毒饼干不够用呢？那我们就需要尽可能的解毒，也就是 $a+b$ 次吃毒和解毒，也就是 $b+a+b$ 个好吃的饼干。可是，题里没说自己最后必须活着啊，所以就是 $b+a+b+1$。

**贴代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int a,b,c;
    cin>>a>>b>>c;
    if(a+b>=c) cout<<b+c<<endl;
    else cout<<b+a+b+1<<endl;
    return 0;
}
```


---

## 作者：Kalium (赞：0)

# AT4510 [AGC030A] Poisonous Cookies题解

## 题意：

题面给的很清晰了，请自行[阅读](https://www.luogu.com.cn/problem/AT4510)。

## 思路：

我们将 A、B、C 三类曲奇的个数计为 a、b、c。

容易发现，A 类和 B 类曲奇可以全部吃完，这个时候呢，我们能获得 $a + b$ 个解药，但是好吃的只有 $b$ 个。

C 类是有毒但好吃，那么我们看看他最多吃几个。

因为连续吃两个有毒的才算死，所以我们可以看成有 $a + b + 1$ 个解药，那么当 $a + b + 1 < c$ 时，至多只能吃 $a + b + 1$ 个，答案就是 $a + 2b + 1$，反之，则可以将 $c$ 个全部吃掉，答案就是 $b + c$ 个。

所以总结下，$ans = \min(a + b + 1, c) + b$。

## 代码：

```cpp
#include <iostream>
#include <cstring>
#include <cstdio>

#define ll long long

using namespace std;

ll a, b, c;

inline ll mina(ll a, ll b) {
	return a < b ? a : b;
}

int main() {
	scanf("%lld %lld %lld", &a, &b, &c);
	
	printf("%lld\n", mina(a + b + 1, c) + b);
		
	return 0;
}
```

---

## 作者：Britney_King (赞：0)

### 首先理解题意我们得出，高桥君在没有解毒的情况下，可以多吃一个毒饼干。

### 代码如下(注释在程序里咯)

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a,b,c,d;//d用于记录吃过的好吃的饼干数 
int main(){
   cin>>a>>b>>c;
   while(1){//无限循环 		
      c--,d++;//每吃一个毒饼干，就加1 
      if(b!=0)//优先吃好吃的解毒饼干 
         b--,d++;
      else a--;//不然就吃不好吃的 
      if(c==0 || a+b==-1){//-1是个细节
         cout<<d+b;//因为好吃的解毒饼干可以无限吃，所以要加上剩下的解毒饼干数 
         return 0;//到达条件就弹出 
      }		
   }
}
```
## 安全无码（手动滑稽）
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a,b,c,d;
int main(){
   cin>>a>>b>>c;
   while(1){	
      c--,d++;
      if(b!=0)
         b--,d++;
      else a--;
      if(c==0 || a+b==-1){
         cout<<d+b;
         return 0;
      }		
   }
}
```


---

