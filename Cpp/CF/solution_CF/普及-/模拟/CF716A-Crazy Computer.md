# Crazy Computer

## 题目描述

ZS the Coder is coding on a crazy computer. If you don't type in a word for a $ c $ consecutive seconds, everything you typed disappear!

More formally, if you typed a word at second $ a $ and then the next word at second $ b $ , then if $ b-a<=c $ , just the new word is appended to other words on the screen. If $ b-a&gt;c $ , then everything on the screen disappears and after that the word you have typed appears on the screen.

For example, if $ c=5 $ and you typed words at seconds $ 1,3,8,14,19,20 $ then at the second $ 8 $ there will be $ 3 $ words on the screen. After that, everything disappears at the second $ 13 $ because nothing was typed. At the seconds $ 14 $ and $ 19 $ another two words are typed, and finally, at the second $ 20 $ , one more word is typed, and a total of $ 3 $ words remain on the screen.

You're given the times when ZS the Coder typed the words. Determine how many words remain on the screen after he finished typing everything.

## 说明/提示

The first sample is already explained in the problem statement.

For the second sample, after typing the first word at the second $ 1 $ , it disappears because the next word is typed at the second $ 3 $ and $ 3-1&gt;1 $ . Similarly, only $ 1 $ word will remain at the second $ 9 $ . Then, a word is typed at the second $ 10 $ , so there will be two words on the screen, as the old word won't disappear because $ 10-9<=1 $ .

## 样例 #1

### 输入

```
6 5
1 3 8 14 19 20
```

### 输出

```
3```

## 样例 #2

### 输入

```
6 1
1 3 5 7 9 10
```

### 输出

```
2```

# 题解

## 作者：k3v1n070828 (赞：4)

**本题解适合萌新们看：比楼下一位大佬的~~深奥~~讲解较为易懂**

**思路如下：**

1.在输入时就进行计算，比较方便。

2.如果一段时间内未打字，那么清屏。

3.如果在规定时间内再次打字，则答案变量$ans++$。

这道题是一道模拟题，虽然不难，但还是**有一些坑点**的

坑点1：答案变量的初始值应设为$1$，因为在输入第一个字符时

坑点2：每次清屏时，答案变量也应该赋值为$1$。

AC Code:

```
#include<cstdio> //scanf要用cstdio头文件
using namespace std;
int n,m,ans=1;//ans初始化为1
int a[100010];
int main(){
	scanf("%d%d",&n,&m);//输入（建议用scanf，更快一些）
	scanf("%d",&a[1]);//先单独输入第一个打字时间
	for(int i=2;i<=n;i++)//循环输入其他时间
	{
		scanf("%d",&a[i]);
		if(a[i]-a[i-1]>m) ans=1;//如果规定时间内没有打字，则清屏，ans赋值为1
		else ans++;//打字了的话，ans自增1
	}
	printf("%d\n",ans);//输出答案
    return 0;//程序结束
}
```

~~码风毒瘤，大佬勿喷~~

Bye~

---

## 作者：Aw顿顿 (赞：0)

确实有这么一个手写板，一段时间不输入就会清空的；用来写 $\mathsf{Article}$ 是不错的选择（

### 目录

- 题意简析：简写题意
- 解法简析：概括解法
- 参考代码：对拍调试

## 题意简析

写字板在 $c$ 秒内未输入则会清空，现给定 $n$ 个字符的输入时间 $a_i$，问最后会剩下几个字母？

其中，$a_i$ 是严格不降排列的，且 $1\le n\le 10^5$，$1\le c\le 10^9$。

## 解法简析

简单的模拟，根据“时间不降”的规则，我们可以知道只要在读入过程中判断相邻两次的时间差 $a_{i}-a_{i-1}$：

- 若大于 $c$ 则记录字符数量的 $s=1$。
- 否则 $s=s+1$ 记录新输入的字符。

为什么“清空”不是 $s=0$ 而是 $s=1$ 呢？原因是在清空的同时也输入了新的一个字符，所以在整个过程中，写字板是不会有变化的。你也可以理解为一个“触发”的机制，即只有在输入新字符的时候才会判断是否清空这个写字板。

## 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,c,a[100005],s=1;
int main() {
	cin>>n>>c;
	for(int i=0;i<n;i++)cin>>a[i];
	for(int i=1;i<n;i++){
	    if(a[i]-a[i-1]>c)s=1;
	    else s++;
	}cout<<s<<endl;
}
```

[**【题目通过记录/完全隐私保护导致不可查看】**](https://www.luogu.com.cn/record/41962160)

---

## 作者：Eason_AC (赞：0)

## Content
有一个电脑，如果过了 $c$ 秒之后还没有任何打字符的操作，就把屏幕上面所有的字符清空。现在，给定 $n$ 次打字符的时间 $t_1,t_2,...,t_n$，求最后屏幕剩下的字符数。

**数据范围：$1\leqslant n\leqslant 10^5,1\leqslant c\leqslant 10^9,1\leqslant t_1\leqslant t_2\leqslant t_3\leqslant ...\leqslant t_n\leqslant 10^9$。**
## Solution
由于输入数据的特殊性，即保证输入的时间是升序的，所以我们直接判断两次操作之间的时间是否大于 $c$，大于 $c$ 就清空，否则就再加上一个字符。注意你可以 $i=2\to n$，判断 $a_i-a_{i-1}$ 是否大于 $m$，也可以从 $i=1\to n-1$，判断 $a_{i+1}-a_i$ 是否大于 $m$，注意循环范围和判断要一一对应。
## Code
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;

int n, m, a[100007], ans = 1;

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i)	scanf("%d", &a[i]);
	for(int i = 2; i <= n; ++i) {
		if(a[i] - a[i - 1] > m)	ans = 1;
		else	ans++;
	}
	printf("%d", ans);
}
```

---

## 作者：Pkixzx (赞：0)

提交了好几次，因为这道题的坑点是真多。

1.初始值应该为1，因为第一个字母也要打进去。

2.每次清零后，值要为1，这点多读读题就可以防止踩坑。

3.要单独输入第一个打字时间，以便后面操作。

找完坑点我们就可以写代码了，代码如下：
```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,m,ans=1,x,y;
	cin>>n>>m;
	cin>>x;
	for(int i=2;i<=n;i++)
	{
		cin>>y;
		if(y-x>m)
		ans=1;//超时，初始值为1
		else
		ans++;//没超时，加1
		x=y;
	}
	cout<<ans;
}

```


---

## 作者：ljm1621 (赞：0)

## 题目描述

给你一个$N(N<=100000)$个字母敲击的时间$t_{i}(t_{i}≤10^9)$，如果在$C$时间内没有敲击那么屏幕就清零，否则屏幕上就多一个字母，问最后屏幕剩下几个字母。

打下一个字母的时候，如果和之前字母打下的时间不超过$k$的话，则保留前面的继续打，如果超过了，则前面的字母全部消失，只留下这一个字母。

这道题是一道模拟题，不需要太多的技巧，**但是这道题还是有一些坑点的：**

1. **单独输入第一个打字时间，也就是$t_{1}$**
2. **ans的初值要赋为1，而不是赋为0**
3. **当$t_{i}-t_{i-1}>c$时，ans应当重新赋为1**

[AC记录](https://www.luogu.com.cn/record/35819211)

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main ()
{
	int n,c,ans=1;
	cin>>n>>c; 
	int time[100010];
	cin>>time[1];
	for(int i=2;i<=n;i++)
	{
		cin>>time[i];
		if(time[i]-time[i-1]>c)	ans=1;
		else					ans++;
	}
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：SqrtSecond (赞：0)

简单的一道水题。


------------
这道题在$M$时间内没有打字那么就从零开始，实际上就是从后往前循环，连续两次打字的时间差大于$M$就停止循环，否则答案加一。

上~~华丽的~~代码
```cpp
#include<bits/stdc++.h>//依然是万能头 
using namespace std;
int n,m,t[1000100],ans=1;//ans需要初始化成1，因为后面少循环了一次 
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
	scanf("%d",&t[i]);//读入 
	for(int i=n-1;i>=1;--i)//倒着循环 
	{
		if(t[i+1]-t[i]>m)break;
		ans++; 
	}
	printf("%d",ans);
}
```


---

## 作者：ZolaWatle (赞：0)

### CF716A 题解

这道题是我和机房里的同学颓废的时候偶然发现的。

其实这道题**根本不需要开数组**，一个变量存现在这个按键盘的时间，再来一个变量存上一次敲键盘的时间。

如果这次的时间与上一次时间间隔不超过m的限制，那么屏幕上会多一个字母。

```cpp
if(temp-last<=m)
		ans++;
```

不巧超过了m，那么屏幕上的字母全部消失。

```cpp
else
		ans=1;
```

当然了，还要把这一次按键盘的时间**赋回去**，以便下一次使用。

```cpp
last=temp;
```

### 完整代码：

```
#include <iostream>
#include <cstdio>
#define re register int
using namespace std;

int n,m,ans,last;  //last存上一次按键盘的时间

int main()
{
	std::scanf("%d%d",&n,&m);
	for(re i=1;i<=n;i++)
	{
		re temp;
		std::scanf("%d",&temp);
		if(temp-last<=m)
			ans++;
		else
			ans=1;  //像上面所说的那样判断键盘上字母数量
		last=temp;  //赋回去
	}
		
	std::printf("%d",ans);
	return 0;
}
```



---

## 作者：打表大蒟蒻 (赞：0)

模拟水题。。。。

直接按题意模拟就行了，没有繁多的步骤，直接上代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[100001];  //定义数组
int main ()
{
	int n, m, sum=1;  //定义计数器，因为处理时是从1开始处理，而我们是从0开始存的，所以先把a0累计加上去
	cin>>n>>m;
	for(int i=0;i<n;i++) cin>>a[i];  //标准读入，懒得用scanf
	for(int i=1;i<n;i++){ //从一开始处理也可以从0循环到n-1，但计数器要清0
		if(a[i]-a[i-1]>m) sum=1;  //如果超过了m，计数器变成1
		else sum++;  //否则计数器继续加
	}
	cout<<sum<<endl;  //输出计数器
	return 0;  //完美结束
}
```


---

