# Browser

## 题目描述

Luba正在网上冲浪。她在浏览器里打开了n个标签，从左到右编号为1到n。目前鼠标光标的位置在第pos个标签。Luba需要使用编号从l到r（包含l与r）的标签，并且她想尽可能快地关闭其它的标签。

Luba每秒可以把光标往左移或者往右移（如果光标当前在标签ii，则她可以将光标移到标签max(i-1,a)或者min(i+1,b)，或者关闭它左边或右边所有的标签（如果光标当前在标签i，她可以关闭[a,i−1]这段标签或者[i+1,b]这段标签）。在上述表达式中，a与b分别表示未关闭标签最小与最大的编号。如果最初有7个标签，1、2、7号标签都被关闭了，那么a=3,b=6

为了只留下初始编号从ll到rr的标签，Luba至少花费多少秒钟？

## 说明/提示

第一个样例中Luba需要做下面的操作：移动光标至标签2，关闭它左边的所有标签，移动光标到标签3，再到标签4，然后关闭它右边的所有标签。

第二个样例中她只需要关闭光标右边的所有标签。

第三个样例中Luba不需要做任何事。

## 样例 #1

### 输入

```
6 3 2 4
```

### 输出

```
5
```

## 样例 #2

### 输入

```
6 3 1 3
```

### 输出

```
1
```

## 样例 #3

### 输入

```
5 2 1 5
```

### 输出

```
0
```

# 题解

## 作者：hswfwkj_ (赞：9)

大家好！我们今天来讲[CF915B](https://www.luogu.com.cn/problem/CF915B)这道题。
## 题意简述：
Luba 在上网，网页上有 $n$ 个标签页，按 $1$ 到 $n$ 的顺序标好了号，现在光标在第 $pos$ 个标签页，她每秒可以把鼠标光标往左或右移，也可以关掉光标之前或光标之后所有的标签页，现在她想要留下 $l$ 到 $r$ 的标签页，她最少需要多少秒?
## 思路：
在看过题面之后，我们发现以下几种特殊情况：
- 保留所有的标签页，即 ``l==1&&r==n``，此时 Luba 不需要做任何事。
- 保留$1$到 $r$ 的标签页，即 ``l==1``，此时 Luba 只需要把光标挪到 $r$ 所在的位置，再关闭之后的标签页。
- 保留 $l$ 到 $n$ 的标签页,即 ``r==n``，此时 Luba 只需要把光标挪到 $l$ 所在的位置，再关闭之前的标签页。
- 其余的就是普通情况，只需要先看把光标移动到 $l$ 还是 $r$ 的距离短，再用短的距离所用的时间加上从 $r$ 到 $l$ 的时间再加上关闭标签页的时间即可。

贴上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,pos,l,r;
int main(){
	cin>>n>>pos>>l>>r;
	if(l==1&&r==n)
	cout<<0;
	else if(l==1)
	cout<<abs(pos-r)+1;
	else if(r==n)
	cout<<abs(pos-l)+1;
	else//一个一个判断特殊情况
	cout<<r-l+min(abs(pos-l),abs(pos-r))+2;
}
```
谢谢大家！希望大家能给我点赞！

---

## 作者：inoichi_lim (赞：4)

## 题意：cf 读题真的很恼火，可能我不仅代码能力弱，英语更弱，两个小时只做了AB题，读题都要花一半时间。一个人浏览网页，网页上有n个标签，这个人需要L，R的区间的标签，其余区间的标签关闭掉，让我们求最少多少秒能够只剩下他需要的区间。** _每次鼠标移动一个位置花费一秒，关掉某个区间也要花费一秒。_ **

### 题解：模拟 分类讨论           我们大体上分为三大类，pos鼠标在L左边，pos区间R右边，pos在区间中间，然后还要考虑,L,R和n的关系。

一般人的思路：~~我就是~~
```CPP
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n,pos,l,r,ans;
    while(cin>>n>>pos>>l>>r)
    {
        ans=0;
        if(l==1&&r==n)
            ans=0;
        else if(pos<=l&&r==n)
            ans+=l-pos+1;
        else if(pos>l&&r==n)
            ans+=pos-l+1;
        else if(pos>=r&&l==1)
            ans+=pos-r+1;
        else if(pos<r&&l==1)
            ans+=r-pos+1;
        else
            ans+=min(abs(l-pos)+r-l,abs(pos-r)+(r-l))+2;
        cout<<ans<<endl;
    }
    return 0;
}
```

---

## 作者：正负君 (赞：2)


# CF915B Browser 题解

# 简化题意 
- 给出 $4$ 个数：$n,pos,l,r$；
- 创建一个长度为 $n$ 的序列 $\{a\}$；
- 操作： 向左或右移动位置，或删除当前位置左或右所有的数字;
- 当前位置为 $a_{pos}$，询问至少几次操作，使得序列只剩下 $a_{l\dots r}$。

# 分析
~~其实这道题很水~~ 用一个 `if` 判断就行了。

考虑以下情况：

- 如果 $l=1\land r=n$，直接输出 $0$；
- 否则如果 $l=1$，输出 $\lvert pos-r\rvert+1$；
- 否则如果 $r=n$，输出 $\lvert pos-l\rvert+1$；
- 其他情况，则输出 $r-l+\min\{\lvert pos-l\rvert,\lvert pos-r\rvert\}+2$；

### 也就是执行以下表达式
$$
ans= \begin{cases}0 &(l=1\land r=n)\\\lvert pos-r\rvert+1 &(l=1)\\ \lvert pos-l\rvert+1 &(r=n)\\r-l+\min\{\lvert pos-l\rvert,\lvert pos-r\rvert\}+2&{Otherwise.}\end{cases}$$
- $ans$ 即为答案。

# 代码
接下来放出~~你们最爱的~~完整代码：
```cpp
#include<iostream>
int n,pos,l,r,ans;
using namespace std;
int main()
{
  cin>>n>>pos>>l>>r;
  if(l==1&&r==n)
  {
    ans=0;
  }
  else if(l==1)
  {
    ans=abs(pos-r)+1;
  }
  else if(r==n)
  {
    ans=abs(pos-l)+1;
  }
  else
  {
    ans=r-l+min(abs(pos-l),abs(pos-r))+2;
  }
  cout<<ans<<endl;
  return 0;
}
```
管理员大大审核辛苦啦！

---

## 作者：小王同学哦 (赞：2)

CF915B

# 史上最多的测试点！
### ————解释和代码



------------

众所周知，歪果仁的脑回路是奇葩的----他为了测试代码，用了229个测试点！！！

本题并不难，楼下大佬的代码很强，让我这个蒟蒻读都读不懂。。。。。。于是，我硬肝了一小时，做出了简易且易懂的代码！！

## 1.解释

本题有好几个部分，分为：

l==1,r==n:根本就不用动，输出0。

l==1:左边就不用管了,ans=abs(r-pos)+1。

r==n:右边就不用管了,ans=abs(pos-l)+1。

pos>=l&&pos<=r:pos在l和r中间,ans=min(a,b)+1+a+b+1,转化一下就是min(a,b)*2+max(a,b)+2。

### 注：a=abs(pos-l),b=(r-pos)。本条为转化公式1

pos<l:pos在l的左边，最好情况下是pos到l再变,所以ans=abs(l-pos)+1+abs(r-l)+1,转化一下就是abs(r-pos)+2。

pos>r:pos在r的右边，把上一条改一下即可。

## 2.坑点，难点

### 坑点最大的就是abs，我因为这个挂了两回！

至于难点吗，要考虑周全，剩下就不难了。

## 3.代码

```cpp
#include<bits/stdc++.h>//懒人必备神器 
using namespace std;
int read() {//快读模板
	int x=0,f=1;
	char ch=getchar();
	while (ch<'0' || ch>'9') {
		if (ch=='-')f=-1;
		ch=getchar();
	}
	while ('0'<=ch && ch<='9') {
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
int main() {
	int n=read(),pos=read(),l=read(),r=read();
	if(l==1&&r==n) {//不需要动
		cout<<0;
		return 0;
	}
	if(l==1) {//左边不管去看右边
		cout<<abs(r-pos)+1;//差的是pos到r的距离加上1
		return 0;
	}
	if(r==n) {//右边不管去看左边
		cout<<abs(pos-l)+1;//差的是pos到l的距离加1
		return 0;
	} else if(pos>=l&&pos<=r) {//pos在l和r中间
		int a=abs(pos-l);//pos到l的距离
		int b=abs(r-pos);//pos到r的距离
		if(a>b) {//pos离r近
			cout<<b*2+2+a;//转化公式1 
			return 0;
		} else {//pos离l近
			cout<<a*2+2+b;
			return 0;
		}
	} else if(pos<l) {//pos在l的左边
		cout<<abs(r-pos)+2<<endl;//见转换公式2
		return 0;
	} else {//pos在r的右边
		cout<<abs(pos-l)+2<<endl;//见转换公式3
	}
}
```

到了这里，各位要多练，有什么问题我会及时回答，别忘了，点个赞再走哦qwq！

---

## 作者：danny101 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF915B)

题目大意：通过移动光标 $\texttt{\&}$ 删除端点到光标之间的区间两种操作删除 $\texttt{[l,r]}$ 以外的区间。

#### 大致思路：

首先，可以直接想到普通情况：要么先移到 $l$，删除 $[1,l-1]$ 这个区间，再移到 $r$ ，删除 $[r+1,n]$ 的区间，要么先移到 $r$，再移到 $l$。

可以推出公式为：$r-l+1+\min(|p-l|,|r-p|)+1$。

可以贴标程了？

还不行！！！

还有三种特殊情况：

- $l=1\&r=n$，直接输出 $0$ 结束。

- $l=1$，从 $p$ 的位置移到 $r$，再执行删除操作即可。

- $r=n$，从 $p$ 的位置移到 $l$，再执行删除操作即可。

如果不是这三种情况，直接用公式解决就可以啦！

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,p,l,r;
int main(){
	cin>>n>>p>>l>>r;
	if(l==1&&r==n)cout<<0;//情况1
	else if(l==1)cout<<abs(r-p)+1;//情况2
	else if(r==n)cout<<abs(p-l)+1;//情况3
	else cout<<r-l+1+min(abs(p-l),abs(r-p))+1;//普通情况
    return 0;
}
```

---

## 作者：smyslenny (赞：1)

**Description**：

> 给出 4 个数，$n$，$pos$，$l$，$r$，当前位置为 $pos$,询问至少几次操作，使得序列只剩下 $l \to r$ 的区间。
>
>	规定操作：
>	向左或向右移动当前位置，或删除当前位置左或右所有的数字。


**Solution**

这道题是挺简单的，但是需要讨论的地方比较细节，导致 WA 了好几次才过。


首先根据样例 1，我们可以贪心的想：如果当前位置离左端点近，我们就先跳到左端点的位置，删掉左边的所有数字，再跳到右端点，删掉右边所有的数字。反之亦然。

```c
	Ans+=min(pos-l,r-pos)+1;
	Ans+=r-l+1;
   
```

然后我们发现这连样例 2 都过不了。

对于这种一个端点就在**最左端**或**最右端**的，我们可以拿出来讨论。

当然，如果**两端都在**，我们特判一下，直接输出 $0$ 即可。

考虑要求保留的左端点就在最左端。

那我们就不需要考虑删除左边的情况了，直接从当前点跳到右端点，删掉右边的点就可以了。跳到端点的次数为 `r-pos` 和 `pos-l`。最后加上在这个端点删数的次数。

如果在最右端，也是同样的，跳到最左端删数就可以了。

```c++
	if(!(l-1) && !(r-n)) 
	{
		printf("0\n"); 
		return 0;
	}
	if(!(l-1) || !(r-n))
	{
		printf("%d\n",(l-1)==0?(r-pos+1):(pos-l)+1);
		return 0;
	}
```

但是这样我们还是过不了，通过查看数据点，我们发现还漏了一种情况。

**当前点并不在保留序列**里的时候，我们直接像 `r-pos+1` 和 `pos-l+1` 这样的情况就变成负的了，因此我们还需要对此类情况作出分类。

考虑如果一个端点就在最左端或最右端，而当前位置在他们之外，他们不是靠近左端点就是靠近右端点，我们可以考虑跳到他们，再删除之前的数。从当前位置跳到端点需要 `pos-r` 或 `l-pos` 的次数，还要进行一次删除操作。因此：

```c++
	if(l<=pos && pos<=r)
		printf("%d\n",(l-1)==0?(r-pos+1):(pos-l)+1);
	else printf("%d\n",pos>r?(pos-r+1):(l-pos+1));
```

对于端点不在最左端或最右端的情况，这种情况也需要讨论，

我们考虑先跳到当前点最近的端点，假如是左端点，次数为 `l-pos`，进行一次删数操作，在继续跳到右端点，次数为 `r-l`，再进行一次删数操作，所以总次数为 `l-pos+1+r-l+1=r-pos+2`。然后大家可以顺着推一下靠近右端点的情况。

答案为 `pos-l+2`

```c++
	if(l<=pos&&pos<=r)
		Ans+=min(pos-l,r-pos)+1+r-l+1;
	else 
		Ans+=pos>r?pos-l+2:r-pos+2;
```

呼~，至此，我们就讨论完了这道题。


**Code**


```c++
/*
* @Author: smyslenny
* @Date:    2021.08.22
* @Title:   CF915B
* @Main idea:
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <cstdlib>

using namespace std;

int n,pos,l,r;

int read()
{
	int x=0,y=1;
	char c=getchar();
	while(c<'0' || c>'9') {if(c=='-') y=0;c=getchar();}
	while(c>='0' && c<='9') { x=x*10+(c^48);c=getchar();}
	return y?x:-x;
}
int Ans;
int main()
{
	n=read(),pos=read(),l=read(),r=read();
	if(!(l-1) && !(r-n)) 
	{
		printf("0\n"); 
		return 0;
	}
	if(!(l-1) || !(r-n))
	{
		if(l<=pos && pos<=r)
		printf("%d\n",(l-1)==0?(r-pos+1):(pos-l)+1);
		else printf("%d\n",pos>r?(pos-r+1):(l-pos+1));
		return 0;
	}
	if(l<=pos&&pos<=r)
		Ans+=min(pos-l,r-pos)+1+r-l+1;
	else 
		Ans+=pos>r?pos-l+2:r-pos+2;
	printf("%d\n",Ans);
	return 0;
}
```

如果有问题，请私信我指出，谢谢。

---

## 作者：清清老大 (赞：1)

# 思路

如果都要保留，则不需要删除任何页面，需要 $0$ 秒。

如果有一段不要删，只删除另一端。具体说，当只要删左边时，要 $|pos-l|+1$ 秒，当只要删右边时，要 $|pos-r|+1$ 秒。

如果两边都要删，先删最近的一段，然后删另一段，要 $(r - l + 1) + \min(|pos-l|,|pos-r|) + 1$ 秒。

## 代码
```cpp
#include<bits/stdc++.h>

using namespace std;

int main()
{
    int n,pos,l,r;
    cin >> n >> pos >> l >> r;
    if(l == 1 && r == n)
    {
        cout << 0;
    }
    else if(l == 1)
    {
        cout << abs(pos - r) + 1;
    }
    else if(r == n)
    {
        cout << abs(pos - l) + 1;
    }
    else
    {
        cout << r - l + min(abs(pos - l),abs(pos - r)) + 2;
    }
}
```


---

## 作者：zplqwq (赞：1)

Hello

泥萌好啊，今天我们来康康这道题趴[CF915B](https://www.luogu.com.cn/problem/CF915B)

~~先吐槽一句，测试点好多....~~

# 题目分析

## 题意：

一个人浏览网页，网页上有n个标签，这个人需要L，R的区间的标签，其余区间的标签关闭掉，让我们求最少多少秒能够只剩下他需要的区间

## 解法：

其实这道题就直接分类讨论下就Ok了。

考虑以下情况：

1. l==1&&r==n 直接输出0
2. l==1 输出abs(pos-r)+1
3. r==n 输出abs(pos-l)+1
4. pos>=l&&pos<=r 输出r-l+min(r-pos,pos-l)+2;
5. 其他情况 输出r-l+min(abs(pos-r),abs(pos-l))+2;

然后就愉快的搞定了。

## 坑点

1. 一定要取abs
2. 读懂题
3. 考虑全面

# 代码

```c++
#include<bits/stdc++.h> //万能头
using namespace std;
//洛谷太棒惹
//我爱洛谷
//管理大大求过
int n,pos,l,r;
int main() 
{
	cin>>n>>pos>>l>>r;
	int ans;
	if(l==1&&r==n)//第一种
	{
        cout<<0<<endl;
        return 0;
	}
	if(l==1)//第二种
	{
		ans=abs(pos-r)+1;
		cout<<ans<<endl;
		return 0;
	}
	if(r==n)//第三种
	{
		ans=abs(pos-l)+1;
		cout<<ans<<endl;
		return 0;
	}
	if(pos>=l&&pos<=r)//第四种
	{
		ans=r-l+min(r-pos,pos-l)+2;
	}
	else//其他
	{
		ans=r-l+min(abs(pos-r),abs(pos-l))+2;
	}
	cout<<ans<<endl;
	return 0;
} 

```

~~管理大大求过~~



---

## 作者：CH30S (赞：0)

**数学题**

[link](https://www.luogu.com.cn/problem/CF915B)



------------
### - 算法

**模拟**

------------

### - 思路

这道题明显是数学题，数学题的共同点就是**分类讨论**。



------------

### - 分类讨论

分类讨论前先定义一个 $ ans $ 记录答案。

并且输入。

1.  **保留所有**的标签页，那么简简单单**,输出 0 即可**。
```
cout<<0<<endl;
```
2.  **如果 $ l = 1 $ 时**，我们就将 $pos$ 移到 $ r $  , 然后删除即可。

$ ans = \left\vert pos  - r\right\vert+ 1$ 即可。

```
cout<<ans<<endl;
```

注意要 +1 。

3. **如果  $ r = n $ 时**，同理，我们就将 $pos$ 移到 $ l $  , 然后删除即可。




$ ans = \left\vert pos  - l\right\vert+ 1$ 即可。


4. **其他（普通）情况。**

先说公式： 

```
cout<<r-l+min(abs(pos-l),abs(pos-r))+2;
```


证明如下：

**我们判断鼠标到 $l$ 的距离和鼠标到 $r$ 的距离的最小值，然后加上从 $r$ 到 $l$ 的时间,最后加上关闭标签页的时间即可。**

因为 $r>l$ 所以不用 $abs$ 。





---

## 作者：Obviathy (赞：0)

## 前言
这是到~~超水~~的模拟题
## 解题思路
我们判断好啦！

如果 $l$ 和 $r$ 都是在两端，也就是都需要保留，输出 $0$ 就行。如果只有一端顶头，那就将 $pos$ 移到另一头再关闭就好啦。如果两头都不顶头就在先去左边删再到右边删的时间和先去右边删再到左边删的时间中找一个最小值，即 $min(|pos-l|+r-l+2,|r-pos| + r - l + 2)$ 就好啦！

## Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,pos,l,r;
int main(){
	cin >> n >> pos >> l >> r;
	if(l == 1){
		if(r == n)cout<<0;
		else cout<<abs(r-pos)+1;
	}else{
		if(r == n)cout <<abs(pos - l)+1;
		else cout<<min(abs(pos-l)+r-l+2,abs(r-pos) + r - l + 2); 
	} 
	return 0;
}

```


---

## 作者：几时明月 (赞：0)

## 简化题目：
一个人，要看$l$到$r$之间的网站，要关掉其他的网站，工具只有鼠标。

## 这题有三种情况：

1.鼠标在 $l$ $r$ 之间；

2.鼠标在$l$的左边；

3.鼠标在$r$的右边。

好知道这几种情况就是只用判断了.

## 首先

判断这三种情况，判断完之后再来个否则判断其余情况，就可以AC了

## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n, p, l, r, ans;
int main() {
	cin>>n>>p>>l>>r;;
	if (l == 1 && r != n) 
    ans = abs(r - p) + 1;
	else if (l != 1 && r == n) 
    ans = abs(p - l) + 1;
	else if (l != 1 && r != n) 
    ans = min(abs(r - p) + r - l + 2, abs(l - p) + abs(r - l) + 2);
	else ans = 0;
	cout<<ans;
	return 0;
}
```
完美收尾.

---

## 作者：tribool4_in (赞：0)

解释一下题意（总感觉题中表述不清……）：某人打开了 $n$ 个标签页，每次可以把光标向左或向右移动一个标签页或关闭左边或右边的全部标签页。问共要多少次操作使得只保留 $[l, r]$ 这段区间的标签页。

分情况讨论：

1. 若 $l=0\ \&\&\ r=n$，则无须计算，答案为零（显然）；
2. 若 $l=0\ \&\&\ r\neq n$，只需走到 $r$ 再关闭右侧标签页；
3. 若 $l\neq 0\ \&\&\ r=n$，只需走到 $l$ 再关闭左侧标签页；
4. 若 $l\neq 0\ \&\&\ r\neq n$，即通常情况，走到 $l$ 再关闭左侧标签页再走到 $r$ 再关闭右侧标签页即可（有点乱……）。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, p, l, r, ans;
int main() {
	scanf("%d%d%d%d", &n, &p, &l, &r);
	if (l == 1 && r != n) ans = abs(r - p) + 1;
	else if (l != 1 && r == n) ans = abs(p - l) + 1;
	else if (l != 1 && r != n) ans = min(abs(r - p) + r - l + 2, abs(l - p) + abs(r - l) + 2);
	else ans = 0;
	printf("%d", ans);
	return 0;
}
```


---

