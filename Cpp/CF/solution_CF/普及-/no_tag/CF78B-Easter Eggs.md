# Easter Eggs

## 题目描述

The Easter Rabbit laid $ n $ eggs in a circle and is about to paint them.

Each egg should be painted one color out of 7: red, orange, yellow, green, blue, indigo or violet. Also, the following conditions should be satisfied:

- Each of the seven colors should be used to paint at least one egg.
- Any four eggs lying sequentially should be painted different colors.

Help the Easter Rabbit paint the eggs in the required manner. We know that it is always possible.

## 说明/提示

The way the eggs will be painted in the first sample is shown on the picture:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF78B/89e74426378989547383b9ed8ec253c74d4ce7d9.png)

## 样例 #1

### 输入

```
8
```

### 输出

```
ROYGRBIV
```

## 样例 #2

### 输入

```
13
```

### 输出

```
ROYGBIVGBIVYG
```

# 题解

## 作者：Colead (赞：12)

# CF78B
大家好，我是WT20071112，为大家带来这道Easter Eggs的题解。

我已经看到各位大佬用推理的方式对最后末尾的几个字母进行归纳总结。

### 然鹅！

我们为什么不可以直接大力分类讨论呢？

那么我们就开始吧！

（提前说明：以下程序中涉及到的变量：n:彩蛋数，k:n/7(保留整数），即为循环次数（具体见程序），i：用于循环。）
#### i）n%7==0
被7整除？那么直接循环。

ROYGBIVROYGBIV

两循环之间无需加任何字母。

```
if(n%7==0)
   {
   	  for(int i=1;i<=k;i++)
   	  {
   	     cout<<"ROYGBIV";
	  }
   }
```

#### ii)n%7==1
ROYGBIV①ROYGBIV

①={R,O,Y,G}∩（G,B,I,V}

∴①=G.

```
if(n%7==1)
   {
   	  for(int i=1;i<=k;i++)
   	  {
   	  	 cout<<"ROYGBIV";
	  }
	  cout<<"G";
	  return 0;
   }
```
#### iii)n%7==2
ROYGBIV①②ROYGBIV

我们先忽视①的存在，根据上一种情况可以得到②=G（当然你如果要让①=G也可以，这是两种对称的情况，在此不再赘述）。

此时数列变成了这样：

ROYGBIV①GROYGBIV

①={R,O,Y,G}∩（Y,B,I,V}

∴①=Y.
```
if(n%7==2)
   {
   	  for(int i=1;i<=k;i++)
   	  {
   	  	 cout<<"ROYGBIV";
	  }
	  cout<<"YG";
   }
```

#### iV)n%7==3
根据和上文相似的办法，可以得到：

ROYGBIV①②③ROYGBIV

①②③=OYG
```
if(n%7==3)
   {
   	  for(int i=1;i<=k;i++)
   	  {
   	  	 cout<<"ROYGBIV";
	  }
	  cout<<"OYG";
   }
```
#### 到这里我们先暂停一下。
发现什么了吗？

- n%7==0 ROYGBIV

- n%7==1 ROY**G**BIV

- n%7==2 RO**YG**BIV

- n%7==3 R**OYG**BIV

所以第五种情况就无需那么费力了。
#### V)n%7==4

- n%7==4 **ROYG**BIV

```
if(n%7==4)
   {
   	  for(int i=1;i<=k;i++)
   	  {
   	  	 cout<<"ROYGBIV";
	  }
	  cout<<"ROYG";
   }
```
#### Vi)n%7==5  与  Vii)n%7==6
这两个小分支与前面就有一点不一样了。

这四个字母不够用了怎么办？没关系，把G接到前面不就行了吗？

ROYGBIV**GROYG**ROYGBIV

没有问题！

啥？五个字母还不够用？没事，再把Y接到前面去呀！

ROYGBIV**YGROYG**ROYGBIV

这样问题就解决了！

```
if(n%7==5)
   {
   	  for(int i=1;i<=k;i++)
   	  {
   	  	 cout<<"ROYGBIV";
	  }
	  cout<<"GROYG";
   }
   if(n%7==6)
   {
   	  for(int i=1;i<=k;i++)
   	  {
   	  	 cout<<"ROYGBIV";
	  }
	  cout<<"YGROYG";
   }
```

（呼……终于把分类讨论讲完了！）

最后上完整代码：（请注意，由于整合时有一些写法上的改动，所以会有注释。）（别看代码长，思路极简单！）
```
#include <bits/stdc++.h>//万能头
using namespace std;
int main()
{
   int n;//彩蛋个数。
   cin>>n;
   int k=n/7;//循环次数。
   if(n%7==0)//分类开始！
   {
   	  for(int i=1;i<=k;i++)
   	  {
   	     cout<<"ROYGBIV";
	  }
	  return 0;//改动来了！既然判断完了输出完了就结束，省时间。
   }
   if(n%7==1)//我们都有return 0了还要else干嘛？
   {
   	  for(int i=1;i<=k;i++)//提醒：下方几十行无注释。
   	  {
   	  	 cout<<"ROYGBIV";
	  }
	  cout<<"G";
	  return 0;
   }
   if(n%7==2)
   {
   	  for(int i=1;i<=k;i++)
   	  {
   	  	 cout<<"ROYGBIV";
	  }
	  cout<<"YG";
	  return 0;
   }
   if(n%7==3)
   {
   	  for(int i=1;i<=k;i++)
   	  {
   	  	 cout<<"ROYGBIV";
	  }
	  cout<<"OYG";
	  return 0;
   }
   if(n%7==4)
   {
   	  for(int i=1;i<=k;i++)
   	  {
   	  	 cout<<"ROYGBIV";
	  }
	  cout<<"ROYG";
	  return 0;
   }
   if(n%7==5)
   {
   	  for(int i=1;i<=k;i++)
   	  {
   	  	 cout<<"ROYGBIV";
	  }
	  cout<<"GROYG";
	  return 0;
   }
   if(n%7==6)
   {
   	  for(int i=1;i<=k;i++)
   	  {
   	  	 cout<<"ROYGBIV";
	  }
	  cout<<"YGROYG";
	  return 0;
   }//之前的分类不重不漏，总会return掉的，最后不加也无所谓。
   return 0;//还是加上吧。
}
```
## 写在最后

//UPDATE 2020-07-16 修改了一个笔误。

首先AC记录是要看一看哒！

[AC没商量](https://www.luogu.com.cn/record/35226292)

~~终于写完了！~~

码字不易，看在我这么认真~~又可爱~~的份上，你真的不给我点个赞再走吗？

再见啦~


---

## 作者：SUNCHAOYI (赞：4)

再次强调题目中的**重点**：   
- 每一种颜色都必须用上  
- 任何四个相连的蛋都要涂上不同的颜色  
- 如果存在多个答案，输出其中一种即可。（看到这句话，我们就可以得出这道题一定是$\texttt{SPJ}$，因此我们只要找到一种可行的解就可以了）

一共有七种颜色，如果$n$刚好是$7$的倍数，那么就以`ROGYBIV`为**循环节**输出即可。但是，这只是一种特殊的情况，我们还要考虑其它的情况。如图，所有都是围成一个圆圈的，所以**首尾的连接处**要特别的注意。（在图中则为$\texttt{Tail}$和$\texttt{Head}$）因此我们只需要找到一个合理的解即可。我们可以以`ROGYBIV`这个循环节为基础，若不是整除情况（多出了$1-6$个），则我们加上`YBIV`$\dots$，这样就可以**避免重复**的情况了。   
![图](https://cdn.luogu.com.cn/upload/image_hosting/w0xet1nr.png)

---

### 代码如下：
因为不是唯一解，所以仅供参考。
```
#include <iostream>
#include <cmath>
using namespace std;
int main()
{
	string str = "ROGYBIV",ans = "YBIVYBI";
	int n;
	cin>>n;
	for(int i = 1;i <= ceil(n / 7.0);i++)//向上取整 
	{
		if(i == ceil(n / 7.0) && n % 7 != 0) for(int j = 0;j < n % 7;j++) cout<<ans[j];//多出的部分 
		else cout<<str;//循环节 
	}
	cout<<endl;
	return 0;
}

```


---

## 作者：GusyNight (赞：3)

这道题.....

不说，先读题，记住**不管在什么时候，读题第一!**
```
复活节兔子把n个蛋围成了一个圆圈。她打算给它们上色。
每一个蛋都要被涂上红橙黄绿蓝靛紫七色中的一个颜色，并满足如下条件：
1、每一种颜色都必须用上
2、任何四个相连的蛋都要涂上不同的颜色。
帮助复活节兔子涂上颜色，当然，这肯定是有解的！
输入：
一行：n（7<=n<=100）
输出：
一行：用下列字符表示所涂上的颜色：R（红red），O（橙orange），Y（黄：yellow），G（绿green），B（蓝blue），I（靛indigo），V（紫violet）
注意：如果存在多个答案，输出其中一种即可
```
大意就是
```
有n个数，每个数都要表上号1~7中的一个，每4个数不能重复，七个号都要有~~~
```
我的思考
```
貌似只要我前面不停的输出"RYOG"最后一次输出"BIV"就可以了~~~
```

循环
```cpp
for(int i=1;i<=n;i++){
        if(i%4==1){printf("R");}
        if(i%4==2){printf("Y");}
        if(i%4==3){printf("O");}
        if(i%4==0){printf("G");}
    }
```

```
但是这样交上去在第2个就会WA
```
***仔细思考，发现是我的顺序不对真正的顺序是 "ROYG" 在最后输出 "BIV"***

**代码**
```cpp
#include<bits/stdc++.h>
#define I int
#define L long long
#define C char
#define S string
#define B bool
#define Max 100000009
#define Mid 1000009
#define Sml 10009
#define Lit 109
using namespace std;
inline I read(){
    char c=getchar();
    I x=0;
    B f=0;
    while(!isdigit(c))f^=!(c^45),c=getchar();
    while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();
    if(f)x=-x;return x;
}
int n;
char colour[8]={' ','R','O','Y','G','B','I','V'};
int main(){
	n=read();
    for(int i=1;i<=4;i++){
        printf("%c",colour[i]);
    }
    return 0;
    n-=7;
    for(int i=1;i<=n;i++){
        if(i%4==1){printf("R");}
        if(i%4==2){printf("O");}
        if(i%4==3){printf("Y");}
        if(i%4==0){printf("G");}
    }
    puts("BIV");
    return 0;
}
```
**还是WA这次实在第一个点**
**反思ing**
```cpp
#include<bits/stdc++.h>
#define I int
#define L long long
#define C char
#define S string
#define B bool
#define Max 100000009
#define Mid 1000009
#define Sml 10009
#define Lit 109
using namespace std;
inline I read(){
    char c=getchar();
    I x=0;
    B f=0;
    while(!isdigit(c))f^=!(c^45),c=getchar();
    while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();
    if(f)x=-x;return x;
}
int n;
char colour[8]={' ','R','O','Y','G','B','I','V'};
int main(){
	n=read();
    for(int i=1;i<=4;i++){
        printf("%c",colour[i]);
    }
    return 0;
    n-=7;
    for(int i=1;i<=n;i++){
        if(i%4==1){printf("R");}
        if(i%4==2){printf("O");}
        if(i%4==3){printf("Y");}
        if(i%4==0){printf("G");}
    }
    puts("BIV");
    return 0;
}
```
**看我这么口爱，不点个赞再走？**

---

## 作者：Eason_AC (赞：1)

## Content
有一个有 $n$ 个点的环，你可以将其染成一种颜色。一共有 $7$ 种颜色（`R`，`O`，`Y`，`G`，`B`，`I`，`V`）可以选择。你的染色方案应该满足下面的要求：

- 每一个点都要被染色，且 $7$ 种颜色都要用上。
- 任何四个相邻的蛋都应当是是不同种颜色。

求一种满足上述要求的方案。

**数据范围：$7\leqslant n\leqslant 100$。**
## Solution
很显然，如果 $n<7$，那么显然没有满足条件的方案，又因为数据范围给出 $n\geqslant 7$，所以**一定会有满足条件的方案**。

接下来考虑如何构造。我们不妨将前 $n-3$ 个点循环涂上前 $4$ 种颜色，如 `ROYGROYG...`，最后三个点再去填剩下三个颜色 `BIV`。可以发现无论 $(n-3)\mod 4$ 的余数是什么，这样的填色方案一定能够满足题目要求。
## Code
```cpp
int n;
const string s = "ROYGBIV";

int main() {
	n = Rint;
	F(i, 0, n - 4) putchar(s[i % 4]);
	F(i, 4, 6) putchar(s[i]);
	return 0;
}
```

---

## 作者：goodier (赞：1)

## **题目简述**

n个蛋摆成一圈，七种颜色，将它们上色，要求相邻的四个颜色不相同，如果有多种上色方法输出一种即可,且每种颜色必须用上。

------------
## **题意分析**

这道题的话第一反应就是直接循环推+比较，毕竟$n ≤ 100$。

不过我在细细思考之后发现了一种更加容易的方法，下面来介绍一下：

首先，换个角度思考一下，题目中要求的是相邻的四个不能重复。

也就是说如果我们将四个中的三个染成不相同的颜色，剩下的一个只要用这三个颜色以外的颜色即可。

本题的难点在于它是个环形的，也就是说需要注意的就是尾部和前最前面的几个不能重。

那么我们可以在前三个用三个不同的颜色，后面的用剩下的四个颜色循环，就不会出现最前端和最后端颜色重复的问题。

具体方法就是先输出前三个的颜色，剩下的用剩下的四个颜色循换输出即可。

代码奉上：
```cpp
#include <iostream>
using namespace std;
int main()
{
    int n;
    cin >> n;
    cout << "BIV";//输出前三个的颜色。
    char ch[4];
    ch[1] = 'R';
    ch[2] = 'O';
    ch[3] = 'Y';
    ch[0] = 'G';
    for(int i = 1; i <= n - 3; i++)
    {
        int num = i % 4;
        cout << ch[num];//输出第三个之后的球的颜色。
    }
    return 0;
}
```


管理员大大求通过！！！

## 若有错误，欢迎指出！！！



---

## 作者：lixiao189 (赞：1)

## 一道大力猜结论的题目
### 思路:
为了方便解释我用1~7表示7种颜色
我们可以发现如果我们再这个序列中开始如果开头四种颜色为1、2 、3、4。结尾处的颜色为5、 6 、7。最后中间按需要循环输出1 2 3 4就可以解决这个问题
### 代码：
```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int n;
char colour[8]={' ','R','O','Y','G','B','I','V'};

int main(){

    //freopen ("input.in","r",stdin);

    scanf ("%d",&n);
    for (int i=1;i<=4;i++){
        printf("%c", colour[i]);
    }
        
    n-=7;
    for (int i=1;i<=n;i++){
        if (i%4==1){
            printf("R");
        }
        if (i%4==2){
            printf("O");
        }
        if (i%4==3){
            printf("Y");
        }
        if (i%4==0){
            printf("G");
        }
    }

    printf ("BIV\n");

    return 0;

}
```

---

## 作者：Allanljx (赞：0)

## 思路
只要前面不停地重复输出ROYG三个字母，最后三个输出BIV，这样就可以让七个颜色都出现，并且任意四个连续的格子颜色都不一样。不能用其他的循环是因为这是一个环。

例如：ROYGBIV，ROYGRBIV，ROYGROBIV，ROYGROYBIV……
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
char a[7]={'R','O','Y','G','B','I','V'};
int main()
{
	int n;
	cin>>n;
	for(int i=0;i<n-3;i++)//反复输出：ROYG直到只剩三个格子
	{
		cout<<a[i%4];
	}
	cout<<"BIV";//输出：BIV
    return 0;
}
```

---

## 作者：翼德天尊 (赞：0)

## STEP 1 题意简述

给一个环涂色，有 $7$ 种颜色供选择，要求涂色后相邻四个格子颜色不同，任意输出一种符合条件的涂色方案。

## STEP 2 浅谈做法

### 1. 典型错误

看到这道题，第一个感觉就是很水。

>只要 $7$ 种颜色轮流枚举就好了嘛。

于是就会写出如下代码：

```cpp
cin>>n;
for (int i=1;i<=n;i++) 
	ans[i]=color[(i-1)%7+1];
for (int i=1;i<=n;i++) 
	putchar(ans[i]);
```

如果你也是这么想的，那么恭喜你，$\color{darkred}\text{WA}$ 了！

### 2. 检查错误

那么，为什么会错呢？？？原来我们的大脑自动将最优情况呈现了出来：$n\% 7$ 为 $0$。

考虑 $n\% 7 \ne 0$ 时（假设为 $1$ 吧），那么最后会多出来一个颜色刚好与第一个颜色相同，不符合条件。

所以正确做法应该是什么呢？

### 3. 正确做法

因为是相邻 $4$ 个颜色不同，所以我们在刚开始模拟的时候就只需要用 $4$ 种颜色轮流涂，最后再用剩下 $3$ 种颜色涂掉剩下 $3$ 个格子即可，这样就能保证最后三种颜色不仅与第一个格子的颜色不同，也与最后一个格子的颜色不同，就可以过了。

**代码如下：**

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
char ans[105],color[8]={'a','R','O','Y','G','B','I','V'};//分别表示答案和每种颜色
int read(){//快读
	int w=0,f=1;
	char c=getchar();
	while (c>'9'||c<'0'){
		if (c=='-') f=-1;
		c=getchar();
	}
	while (c>='0'&&c<='9'){
		w=(w<<3)+(w<<1)+(c^48);
		c=getchar();
	}
	return w*f;
}

int main(){
	n=read();
	for (int i=0;i<n-3;i++)//前n-3种
		ans[i]=color[i%4+1];
	for (int i=5;i<=7;i++)//最后三种
		ans[n+i-8]=color[i];
	for (int i=0;i<n;i++)//输出
		putchar(ans[i]);
	return 0;
}

```

完结撒花✿✿ヽ(°▽°)ノ✿！

---

## 作者：江山_远方 (赞：0)

### 本题最短代码，没有之一！
本题呢是要给每个复活节彩蛋涂上颜色，并且相邻4个彩蛋颜色不能相同  
刚拿到这个题，我就露出了轻松的笑容：真是道水题！  
然后我想：只要7种颜色轮流枚举，相邻4个当然不会有的重复颜色了

```cpp
#include<bits/stdc++.h>
using namespace std;
const char c[]={' ','R','O','Y','G','B','I','V'};//用数组储存颜色
int n;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)putchar(c[(i-1)%7+1]);
	return 0; 
}
```
![](https://cdn.luogu.com.cn/upload/image_hosting/f2grj9sd.png)  
错哪了？？？  
直到我看到了![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF78B/89e74426378989547383b9ed8ec253c74d4ce7d9.png)  
哦 这是个环    
首尾也要判断是否重复呢
所以我们可以先ROYGROYG的重复循环，最后输出BIV3个字符，这样就不会重复啦  
难道我就要重写代码了吗？  
不，我不要  
~~我懒~~  
所以我轻改代码，啊咧！
```
#include<bits/stdc++.h>
using namespace std;
const char c[]={' ','R','O','Y','G','B','I','V'};
int n;
int main()
{
	cin>>n;
	for(int i=1;i<=n-3;i++)putchar(c[(i-1)%4+1]);
	for(int i=5;i<=7;i++)putchar(c[i]);
	return 0; 
}	
```
~~AC抱回家~~

---

## 作者：peppaking8 (赞：0)

## 思路
题目的要求就是，给出一个由 $n$ 个点形成的环，要求每相邻的四个点的颜色都不一样。

乍一看题非常简单，我们只需要构造出来一种就行了。

因为要求相邻四个不相同，所以考虑**七位**为一组，进行 ```ROYGBIV``` 的循环即可。但是这是对的吗？考虑 $n=8$ 的情况，按理来说应该输出 ```ROYGBIVR```，但是显然第八个与第一个相同了，**不满足要求**。

这个方法之所以不行，是在环这个问题上出了锅。那么我们再想一想：如果**四位为一组**，是不是会好一些呢？接下来就有了两个问题：剩下的三个颜色如何用上？如何保证环的情况下也成立？

这两个问题可以一起解决。我们让最后三个数为 ```BIV```，即另外三个颜色。然后前面几位进行 ```ROYG``` 的四位循环。这样就解决了。因为 $n\ge 7$，所以这种方法一定可行。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
char a[4]={'G','R','O','Y'};//循环用数组，可大大减少码量
int main(){
    int n;
    cin>>n;
    n-=7;
    //四位循环
    cout<<"ROYG";
    for(int i=1;i<=n;i++) cout<<a[i%4];
    cout<<"BIV"<<endl;//最后输出三个其它颜色
}
```

---

