# Fafa and the Gates

## 题目描述

Two neighboring kingdoms decided to build a wall between them with some gates to enable the citizens to go from one kingdom to another. Each time a citizen passes through a gate, he has to pay one silver coin.

The world can be represented by the first quadrant of a plane and the wall is built along the identity line (i.e. the line with the equation $ x=y $ ). Any point below the wall belongs to the first kingdom while any point above the wall belongs to the second kingdom. There is a gate at any integer point on the line (i.e. at points $ (0,0) $ , $ (1,1) $ , $ (2,2) $ , ...). The wall and the gates do not belong to any of the kingdoms.

Fafa is at the gate at position $ (0,0) $ and he wants to walk around in the two kingdoms. He knows the sequence $ S $ of moves he will do. This sequence is a string where each character represents a move. The two possible moves Fafa will do are 'U' (move one step up, from $ (x,y) $ to $ (x,y+1) $ ) and 'R' (move one step right, from $ (x,y) $ to $ (x+1,y) $ ).

Fafa wants to know the number of silver coins he needs to pay to walk around the two kingdoms following the sequence $ S $ . Note that if Fafa visits a gate without moving from one kingdom to another, he pays no silver coins. Also assume that he doesn't pay at the gate at point $ (0,0) $ , i. e. he is initially on the side he needs.

## 说明/提示

The figure below describes the third sample. The red arrows represent the sequence of moves Fafa will follow. The green gates represent the gates at which Fafa have to pay silver coins.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF935B/b75712c03fca29d89953f4e50f7a0d99cb311364.png)

## 样例 #1

### 输入

```
1
U
```

### 输出

```
0
```

## 样例 #2

### 输入

```
6
RURUUR
```

### 输出

```
1
```

## 样例 #3

### 输入

```
7
URRRUUU
```

### 输出

```
2
```

# 题解

## 作者：落河之秋 (赞：1)

### 题意

在平面直角坐标系中有一条$x=y$的函数图像，有一点从原点 $(0,0)$ 出发，求其**经过**函数图像的次数。

### 分析

No.1：题目中给出的条件为**经过**函数图像，即穿过函数图像，并不是在函数图像上停留的次数。

No.2：题目中给出了两种操作：

 U ：向上移动一个单位长度，即纵坐标加一，也就是y++。

 R ：向右移动一个单位长度，即横坐标加一，也就是x++。

我们可以用字符串（string）类型来读入题目中给出的字符数列，方便快捷。

No.3：当点移动到函数图像上时，我们不难发现只有当点**重复**上一次移动的方向时才能顺利地穿过函数图像。

举个栗子：

当点从 $(3,2)$ 执行操作 R 后移动到了 $(3,3)$ ，此时如果想让它穿过图像，我们只能再执行一遍操作 R ，使其运动到点 $(3,4)$ ，从而顺利地到达函数图像的**右侧**，反之如果执行操作 U ，点会移动到$(4,3)$， 此时它依旧在图像**左侧**，未穿过图像，所以计数器也不再自加。

Ps：为了照顾小五和小六的朋友们，友情提示：

当 x 小于 y 时，点在图像左侧。

当 x 等于 y 时，点在图像上。

当 x 大于 y 时，点在图像右侧。


分析完毕。

### 代码

```cpp
#include<iostream>
#include<string>

using namespace std;

int n,x=0,y=0,k=0;
string s;

int main()
{
	cin>>n>>s; //cin永远是string的好搭档
	
	for(int i=0; i<s.size(); i++)
	{
		if(s[i] == 'U')
		{
			y++;
		}
		if(s[i] == 'R')
		{
			x++;
		}
		
		if(x == y and s[i] == s[i+1]) //实现No.3分析
		{
			k++;
		}
	}
	
	cout<<k;
	return 0;
}
```



---

## 作者：想不好名字 (赞：1)

# 题目大意
  在第一象限有一条$y$=$x$的函数，有一个点从原点出发，问他一共穿过这条函数多少次。
  
# 主要思路

一直模拟，用计数器记录穿过几次对应的函数。

# 注意事项

1.该点一共有两种状态，一种是 U（即向上，可以理解为   y +1)，另一种是 R (即向右，可以理解为 x +1)。

2.穿过函数并不等于该点到达函数，而是该点从函数的一侧到达函数的另一侧。

# 代码


```c
#include<iostream>
#include<cstdio>

using namespace std;

int n,up,r,ans;
char c,c1;

int main()
{
	scanf("%d",&n);
	c1=getchar();//先读入一次，方便比较 
	cin>>c1;
	for(int i=1;i<n;++i)
	{
		c=getchar();
		if(c1=='U') up++;//向上 
		if(c1=='R') r++;//向右 
		cout<<up<<" "<<r<<endl;//纠错用，可忽视 
		if(up==r&&c==c1) ans++;//如果该点在函数上且下一次行驶方向与本次一致，即穿过该点，计数器++ 
		c1=c;//下一次运动的方向 
	}
	cout<<ans;//输出 
	return 0;
}
```


---

## 作者：OneZzy_226 (赞：1)

### 前言
~~看啊这个蒟蒻又来水题解了~~
### 题目大意
* 在一个平面直角坐标系内，从原点开始，$N$ 次移动。
* 每次移动穿过直线 $y = x$ 则计数器加一。
* 每次只能向上向右移动。
* $N \leq 10^5$ 。
### 思路
首先我们要明确一点，只有**穿过**直线 $y = x$ 计数器才能加一，在这条直线上是不加的，阅读样例我们就能得知。  
然后我们开始思考一个问题，如何判断是否穿过直线？  
由于只能向上向右移动，所以如果要穿过直线，只能是连续两个向右或向上，只要判断一下就行了。  
时间复杂度 $O(n)$ , $10^5$ 的~~良心~~数据范围可以稳过。
### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x = 0,y = 0,ans = 0;//ans指计数器 
char c,u;//c指下一个处理的，u指当前处理的 
int main(){
	cin>>n;
	cin>>u;//先输入一个 
	
	for(int i = 1;i < n;i++){
		cin>>c;		
		//对当前的进行判断 
		if(u == 'U'){
			y++;
		}
		else if(u == 'R'){
			x++;
		}

		if(x == y&&c == u){//核心判断 
			ans++;
		}
		u = c;//更新当前的 
	}
	cout<<ans;//输出不解释 
	return 0;//好习惯 
}
```


---

## 作者：zct_sky (赞：0)

### Solution:
-----
一道简单的模拟题。

遍历一遍字符串，如果是 $\texttt{U}$，则 $x$ 坐标加 1，如果是 $\texttt{R}$，则 $y$ 坐标加 1。

当 $x=y$，且下一步的步骤等于当前这一步时，说明法法到另一个王国了，就把要付的银币数量加 1。
### Code:
-----
```c++
#include<bits/stdc++.h>
#define ll long long
#define un unsigned
using namespace std;
int n,ans,x,y;
string a;
int main(){
	cin>>n>>a;
	for(int i=0;i<n;i++){//遍历字符串 
		if(a[i]=='U')x++;//向上(U)，则x++ 
		else y++;//否则就是向右(R)，则y++ 
		if(x==y&&a[i]==a[i+1])ans++;
	}
	cout<<ans;   
	return 0;
}

```

---

## 作者：yimuhua (赞：0)

**题意：**

在平面直角坐标系中有一条 $x = y$ 的函数图像，有一点从原点 _(0, 0)_ 出发，求其穿过函数图像的次数。

**分析：**

题目中给出了两种操作：

U ：向上移动一个单位长度，即纵坐标加一，也就是 "y++"。

R ：向右移动一个单位长度，即横坐标加一，也就是 "x++"。

**思路：**

模拟，用变量记录穿过几次对应的函数。

分三种情况：

1.当 x 小于 y 时，点在图像左侧。

2.当 x 等于 y 时，点在图像上。

3.当 x 大于 y 时，点在图像右侧。

**注意事项：**

**穿过**函数并不等于该点**到达**函数，而是该点**从函数的一侧到达函数的另一侧**。

**AC代码：**

```cpp
#include<bits/stdc++.h>
using namespace std;
//注意：程序中我nowx和nowy是行和列的概念，而不是数学中的x和y轴
//使用一个变量记录下之前是在哪个国家，如果改变了国家，那就金币数量++
char c;
int n, sum, nowx, nowy, pre;  //使用pre来记录之前在哪个国家
int main() {
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> c;
        if(c == 'U') {
            nowx++;
            if(nowx > nowy && pre == 1)  //到了第二个国家，之前在第一个国家 
                sum++;
            else if(nowx<nowy && pre==2)
                sum++;
        }
        else {
            nowy++;
            if(nowx > nowy && pre == 1)
                sum++;
            else if(nowx < nowy && pre == 2)
                sum++;
        }
        if(nowx > nowy)
            pre = 2;  //到了第二个国家，更新一下之前在哪个国家
        if(nowx < nowy)
            pre = 1;  //如果nowx和nowy相同，那么不更新pre
    }
    cout << sum;
    return 0;
}
```

**时间复杂度：**

$O(n)$，$n \le 100000$ 

---

## 作者：Waaifu_D (赞：0)

## 题意简述

有一个点在平面直角坐标系坐标系中移动，求它经过几次 $y=x$ 函数的图像

## 思路

既然移动路径是用字符来表示的，我们就可以用字符串来求解，我个人习惯用字符串来求，当然字符数组也是可以的

首先我们需要理解“经过”是什么意思，按照样例所说的，最后如果点停在图像上，不算“经过”，所以我们需要判断它是否穿过图像，即下一次的移动方向与这次相同

## Code

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
int n,ans,x,y;
string s;
int main()
{
	cin>>n;
	cin>>s;
	for(int i=0; i<s.size();i++)
	{
		if(s[i]=='U') y++;//纵坐标
		if(s[i]=='R') x++;//横坐标
		if(y==x&&s[i+1]==s[i])//如果y=x（即在图像上）且下一次也是这个移动方向，计数器自加
		{
			ans++;
		}
	}
	cout<<ans;愉快AC
	
}
```


---

## 作者：Eason_AC (赞：0)

## Content
一个动点 $F$ 一开始在平面直角坐标系上原点的位置，随后它会移动 $n$ 次，每次只能向上走或者向右走 $1$ 个单位，求经过直线 $y=x$ 的次数。

**数据范围：$1\leqslant n\leqslant 10^5$。**
## Solution
注意，这里是**经过**直线 $y=x$ 的次数而不是**到达**直线 $y=x$ 的次数！比如说你上次操作往上走 $1$ 个单位，到了 $(3,3)$，但随后你又往右走了 $1$ 个单位，这就不算经过了！必须要到达直线 $y=x$ 并且下一步操作和到直线前的上一步操作的方向相同！

其他的不用多说了，直接模拟每一步操作就好。
## Code
```cpp
int n, curx, cury, ans;
string s; 

int main() {
	getint(n);
	cin >> s;
	_for(i, 0, n - 1)	curx += (s[i] == 'R'), cury += (s[i] == 'U'), ans += (curx == cury && s[i + 1] == s[i]);
	writeint(ans);
	return 0;
}
```

---

## 作者：开始新的记忆 (赞：0)

题目大意：现在有两个王国，以y=x这条直线为分界限，如果穿过要付一块钱（在线上不用），现在有一个人从0,0出发，走n步，每步他只会往上或者右走，请问他要付多少钱。

思路：因为是1e5的数据，直接暴力枚举即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x=0,y=0,ans=0;
string a;

int main()
{	cin>>n>>a;
	for(int i=0;i<n;++i)
	{
		if(a[i]=='U')
			++y;
		else
			++x;
		if(x==y && a[i+1]==a[i])
			++ans;
	}
	cout<<ans<<endl;
	return 0;
}
```


---

