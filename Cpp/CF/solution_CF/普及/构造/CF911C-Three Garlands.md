# Three Garlands

## 题目描述

Mishka is decorating the Christmas tree. He has got three garlands, and all of them will be put on the tree. After that Mishka will switch these garlands on.

When a garland is switched on, it periodically changes its state — sometimes it is lit, sometimes not. Formally, if $ i $ -th garland is switched on during $ x $ -th second, then it is lit only during seconds $ x $ , $ x+k_{i} $ , $ x+2k_{i} $ , $ x+3k_{i} $ and so on.

Mishka wants to switch on the garlands in such a way that during each second after switching the garlands on there would be at least one lit garland. Formally, Mishka wants to choose three integers $ x_{1} $ , $ x_{2} $ and $ x_{3} $ (not necessarily distinct) so that he will switch on the first garland during $ x_{1} $ -th second, the second one — during $ x_{2} $ -th second, and the third one — during $ x_{3} $ -th second, respectively, and during each second starting from $ max(x_{1},x_{2},x_{3}) $ at least one garland will be lit.

Help Mishka by telling him if it is possible to do this!

## 说明/提示

In the first example Mishka can choose $ x_{1}=1 $ , $ x_{2}=2 $ , $ x_{3}=1 $ . The first garland will be lit during seconds $ 1,3,5,7,... $ , the second — $ 2,4,6,8,... $ , which already cover all the seconds after the $ 2 $ -nd one. It doesn't even matter what $ x_{3} $ is chosen. Our choice will lead third to be lit during seconds $ 1,4,7,10,... $ , though.

In the second example there is no way to choose such moments of time, there always be some seconds when no garland is lit.

## 样例 #1

### 输入

```
2 2 3
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
4 2 3
```

### 输出

```
NO
```

# 题解

## 作者：きりと (赞：3)

**[题目传送门](https://www.luogu.com.cn/problem/CF911C)**

### 题目大意

见中文翻译

### 解题思路

假设秒数（即自然数）共有$N$个，则$k_i$可以点亮$\frac{N}{k_i}$个秒数，我们令$S=\sum^{3}_{i=1}\frac{N}{k_i}$，则要满足：$S$为整数且$S≥N$，则有$4$种情况：

- 有一个$k_i=1$
- 有两个$k_i=2$
- 有三个$k_i=3$
- 有一个$k_i=2$，两个$k_i=4$

逐一判断即可

### 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
int num[5];  //桶，存每个数的个数
signed main()
{
	int k;
	for(int i=1;i<=3;i++)
	{
		cin>>k;
		if(k>=1&&k<=4)   //别的数没有意义，不用存
		{
			num[k]++;
		}
	}
	if(num[1])
	{
		cout<<"YES"<<endl;
		return 0;
	}
	if(num[2]>=2)
	{
		cout<<"YES"<<endl;
		return 0;
	}
	if(num[3]==3)
	{
		cout<<"YES"<<endl;
		return 0;
	}
	if(num[2]==1&&num[4]==2)
	{
		cout<<"YES"<<endl;
		return 0;
	}
	cout<<"NO"<<endl;
	return 0;
}
```



---

## 作者：YuRuiH_ (赞：2)



------------
**~~感谢找CF的一道水题~~**

直接模拟+瞎搞就完事了吧

```
#include<cstdio>
#include<iostream>
using namespace std;
int vis[1505];
int main(){
    int k1,k2,k3;
    scanf("%d%d%d",&k1,&k2,&k3);
    vis[k1]++;
    vis[k2]++;
    vis[k3]++;
    if(vis[1]) printf("YES\n"); //如果k1=1, x1=1,x2,x3任意 
    else if(vis[2]>=2) printf("YES\n");//如果k1=2,k2=2,x1=1,x2=2,x3任意 
    else if(vis[3]>=3) printf("YES\n");//如果k1=k2=k3=3 x1=1,x2=2,x3=3 
    else if(vis[2]&&vis[4]>=2) printf("YES\n");//如果k1=2,k2=k3=4,x1=1,x2=2,x3=4
    else printf("NO\n");
    return 0;
} 

```


---

## 作者：Clay_L (赞：1)

### 题意简述

这里就不都赘述了，自己看题目翻译~~（我是不会告诉你我转述不出这题的题意的）~~。

### 算法分析

很明显，是道数学题。

易得：当 $\large{\frac{1}{k_1}+\frac{1}{k_2}+\frac{1}{k_3}\ge 1}$ 时就可以实现。

而这样的情况只有四种。

所以这道题的精髓就在**分类讨论**（数学老师再也不用担心我们的思维了）。

在 $k_1$ 到 $k_3$ 中：

> 1. `'2'` 出现两次及以上（错开一位排）；
> 2. `'1'` 出现一次及以上（直接放就行）；
> 3. `'2'` 出现一次并且 `'4'` 出现两次（两个 `'4'` 可以组成一个 `'2'`）；
> 4. `'3'` 出现三次（各错开一位）。

除了这四情况以外的所有情况都不可能满足题意~~（不信自己去手模一遍）~~。

这个时候应该都知道怎么打了吧。不知道脑袋里浮现出的冗长代码把你们整怕没有。包括其他题解对于我的代码来说都比较长。

那怎么优化“代码复杂度”呢？换个角度去想，怎么去存一个数出现的次数呢？

很容易想到，用桶。

所以，代码就很容易出来了。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int x,t[1510],n=3;
signed main(){
	ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
	while(n--) cin>>x,t[x]++;//桶思想（就只存三个数）
	if(t[2]>=2||t[1]>0||(t[4]==2&&t[2]==1)||t[3]==3) cout<<"YES\n";//简单判断
	else cout<<"NO\n";
	return 0;
}
```

就这么简单，自己理解。谢谢。

完结撒花！

---

## 作者：zhengzidu (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF911C#submit)

# Introduction

## 题面
圣诞树上有三个花环，Mishka 将开启这些花环。 有时候花环会亮，有时候不会。如果第i个花环在第 $x$ 秒开启，则仅在以第 $x,x+k\times i,x+2\times k\times i$ $\dots$ 秒时是亮的。 Mishka 想要打开花环，以便在每秒至少有一个点亮的花环。 在 Mishka 想要选择三个整数 $x1,x2,x3$，以便在第 $x1$ 秒期间接通第一个花环，在第 $x2$ 秒期间接通第二个花环，并且在第 $x3$ 秒期间接通第三个花环， 并且在从 $max(x1,x2,x3)$ 开始的每秒中，至少一个花环将被点亮。 帮助 Mishka 告诉她是否有可能做到这一点。

# Solution

$tag$：数学加分类讨论。

易得：当 $1\le \frac{1}{x1} +\frac{1}{x2}+\frac{1}{x3}$ 时就可以实现。

所以分类讨论：

- 当 $x1,x2,x3$ 其中一个为 $1$ 时，则上式恒成立。

- 当 $x1,x2,x3$ 其中两个为 $2$ 时，上式也恒成立。

- 同理，当 $x1,x2,x3$ 均为 $3$ 或 $x1,x2,x3$ 中有任意两个数为 $4$，一个数为 $2$ 时，上式也成立。

- 综上所述，该不等式解集为

$\left\{\begin{matrix}
  x1=1& \\
  x2\in N& \\
  x3\in N&
\end{matrix}\right.$ 或 $\left\{\begin{matrix}
  x1\in N& \\
  x2=1 & \\
  x3\in N&
\end{matrix}\right.$ 或 $\left\{\begin{matrix}
  x1\in N& \\
  x2=1 & \\
  x3\in N&
\end{matrix}\right.$ 或 $\left\{\begin{matrix}
  x1=2& \\
  x2=2& \\
  x3\in N&
\end{matrix}\right.$ 或 $\left\{\begin{matrix}
  x1=2& \\
  x2\in N& \\
  x3=2&
\end{matrix}\right.$ 或 $\left\{\begin{matrix}
  x1\in N& \\
  x2=2& \\
  x3=2&
\end{matrix}\right.$ 或 $\left\{\begin{matrix}
  x1=3& \\
  x2=3& \\
  x3=3&
\end{matrix}\right.$ 或 $\left\{\begin{matrix}
  x1=4& \\
  x2=4& \\
  x3=2&
\end{matrix}\right.$ 或 $\left\{\begin{matrix}
  x1=4& \\
  x2=2& \\
  x3=4&
\end{matrix}\right.$ 或 $\left\{\begin{matrix}
  x1=2& \\
  x2=4& \\
  x3=4&
\end{matrix}\right.$。

所以，对输入的 $x1,x2,x3$ 进行判断，若符合上方其中一组解，则输出 `YES`。

# Code

```cpp
#include<bits/stdc++.h>
#define int long long
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
	x=x*10+ch-'0';
	ch=getchar();
}
	return x*f;
}
void write(int x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
		write(x/10);
	putchar(x%10+'0');
	return;
}
using namespace std;
signed main(){
	int x1=read();
	int x2=read();
	int x3=read();
	if(x1==1||x2==1||x3==1){
		printf("YES");
		return 0;
	}
	if(x1==2&&x2==2||x1==2&&x3==2||x2==2&&x3==2){
		printf("YES");
		return 0;
	}
    if(x1==3&&x2==3&&x3==3){
    	printf("YES");
		return 0;
    }
	if((x1==2&&x2==4&&x3==4)||(x2==2&&x1==4&&x3==4)||(x1==4&&x2==4&&x3==2)){
		printf("YES");
		return 0;
	}
	printf("NO");
 	return 0;
} 
```

# Record

[record](https://codeforces.com/problemset/status?my=on)

---

## 作者：Moon_Wind (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF911C)

------------

**思路：**

有 $3$ 盏灯，第 $i$ 盏灯每 $a_i$ 秒亮一次，可以随意安排开始时间，要求每一秒都有灯亮着。那么，可以得到当 $\frac{1}
{a_1}+\frac{1}{a_2} + \frac{1}{a_3} \ge 1$ 时，就可以实现，有四种情况，分类讨论一下即可。
   
**代码部分：**   
   
------------




```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,n1,n2;
	cin>>n>>n1>>n2;
	if(n==1||n1==1||n2==1) cout<<"Yes";
            //有一盏灯每一秒亮一次时，可以实现。
	else if(n==2&&n2==2||n==2&&n1==2||n1==2&&n2==2)
             cout<<"Yes";
            //有两盏灯每两秒亮一次，也可以实现。
	 else if(n==3&&n1==3&&n2==3)   cout<<"Yes";
         //有三盏灯每三秒亮一次时。
	 else if(n==2&&n1==4&&n2==4)   cout<<"Yes";
         else if(n==4&&n1==2&&n2==4)   cout<<"Yes"; 
         else if(n==4&&n1==4&&n2==2)   cout<<"Yes";
         //有两盏灯每四秒亮一次，一盏灯每两秒亮一次时。
	else cout<<"No";//否则不行。
 	return 0;
} 

```



------------
本人只是一名蒟蒻，若有错误请多多包涵，谢谢大家。


---

## 作者：oddy (赞：0)

## Description

有三盏灯，第 $i$ 盏灯每 $k_i \  \text{s}$ 亮一次。问你是否从第 $\max\{k_1, k_2, k_3\} \  \text{s}$ 开始，每秒都至少有一盏灯亮着。

如果是，输出 `YES`，否则输出 `NO`。

## Limitations

对于 $100 \%$ 的数据，$1 \leqslant k_1, k_2, k_3 \leqslant 1\ 500$。

## Solution

容易证明，当 $k_1, k_2, k_3$ 均大于 $4$ 时，永远无解。

令 $a_{1..3}$ 为 $k_{1..3}$ 从小到大排序后的结果，则下面是枚举得到的有解的几种情况：

1. $a_1 = 1$，无论什么时候它都亮；
2. $a_1 = a_2 = 2$，两盏灯可以交错着亮；
3. $a_1 = a_2 = a_3 = 3$，三盏灯交错着亮；
4. $a_1 = 2, a_2 = a_3 = 4$，如下图所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/k015m4g9.png)

## Code

```cpp
#include <cstdio>
#include <algorithm>

int k[3];

void input() {
    scanf("%d%d%d", k, k+1, k+2);
}

void work() {
    std::sort(k, k+3);
    if(k[0] == 1)                                puts("YES");
    else if(k[0] == 2 && k[1] == 2)              puts("YES");
    else if(k[0] == 3 && k[1] == 3 && k[2] == 3) puts("YES");
    else if(k[0] == 2 && k[1] == 4 && k[2] == 4) puts("YES");
    else puts("NO");
}

int main() {
    input();
    work();
    return 0;
}
```



---

