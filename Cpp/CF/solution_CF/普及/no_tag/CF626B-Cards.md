# Cards

## 题目描述

Catherine has a deck of $ n $ cards, each of which is either red, green, or blue. As long as there are at least two cards left, she can do one of two actions:

- take any two (not necessarily adjacent) cards with different colors and exchange them for a new card of the third color;
- take any two (not necessarily adjacent) cards with the same color and exchange them for a new card with that color.

She repeats this process until there is only one card left. What are the possible colors for the final card?

## 说明/提示

In the first sample, Catherine has one red card and one blue card, which she must exchange for a green card.

In the second sample, Catherine has two green cards and one red card. She has two options: she can exchange the two green cards for a green card, then exchange the new green card and the red card for a blue card. Alternatively, she can exchange a green and a red card for a blue card, then exchange the blue card and remaining green card for a red card.

In the third sample, Catherine only has blue cards, so she can only exchange them for more blue cards.

## 样例 #1

### 输入

```
2
RB
```

### 输出

```
G
```

## 样例 #2

### 输入

```
3
GRG
```

### 输出

```
BR
```

## 样例 #3

### 输入

```
5
BBBBB
```

### 输出

```
B
```

# 题解

## 作者：L_zaa_L (赞：7)


## 题意
就有两种变卡片的情况：

1. 两种卡片颜色相同——颜色不变，卡片少一张
2. 两种卡片颜色不同——变另一种颜色

比如：```BB```,我们可以变成```B```，
		
   ```GR```可以变成```B```。
   
 然后叫你求出最后一张卡片可以是哪张。

------------
## 分析

我们一个一个地枚举，看看最后一张卡片能不能是这个颜色。而判断这个颜色能不能成为最后一张卡片，就又可以有三种情况：
###### 1. 当两个另外的卡片的数量都大于一张：
两张卡片可以由变换卡片的第一种情况将两种卡片变为数量一样的，然后由变换卡片的第二种情况将两种卡片都变为目标颜色，然后再由变换卡片的第一种情况将所有目标颜色卡片变为一张目标卡片。

###### 2. 一张卡片（不是目标卡片）大于两张，目标颜色最少有一张，最后一张卡片没有：

两张卡片（目标卡和大于两张）可以由变换卡片的第二种情况将两种卡片变为最后一张，然后就变为了第一种判断。

###### 3. 全是目标卡：

直接由变换卡片的第一种情况将所有目标颜色卡片变为一张目标卡片。
	
## Code

上面废话了这么多，直接上代码吧：
```c
#include<stdio.h>
char c[201];
int main(){
	int n,r,b,g;
	scanf("%d%s",&n,&c);
	g=0,b=0,r=0;
	for(int i=1;i<=n;i++){
		if(c[i-1]=='G') g++;
		if(c[i-1]=='R') r++;
		if(c[i-1]=='B') b++;
	}//记录每张卡片出现的次数
	if((g>0&&r>0)||(g==0&&r>1&&b>0)||(r==0&&g>1&&b>0)||b==n) printf("B");//判断蓝颜色可不可以成为最后一张卡片
	if((b>0&&r>0)||(b==0&&r>1&&g>0)||(r==0&&b>1&&g>0)||g==n) printf("G");//判断绿颜色可不可以成为最后一张卡片
	if((g>0&&b>0)||(g==0&&b>1&&r>0)||(b==0&&g>1&&r>0)||r==n) printf("R");//判断红颜色可不可以成为最后一张卡片
	return 0;
}
```

楼上大佬的方法的确非常的优秀。

于是敝人弱弱地交上了一篇题解。


---

## 作者：wangzhihong10002 (赞：4)

[传送门。](https://www.luogu.com.cn/problem/CF626B)

# 题目分析：

这是一道很简单的题目，我们可以分类讨论，那该怎么讨论呢？这里有三种要讨论的地方：

- 如果只有一种牌我们就可以一直做动作 $2$ 来的到这种牌。
- 如果有其他颜色的牌我们就重复执行动作 $1$ 来得到目标牌。
- 如果其他两种牌有一种没有且另一种的牌数大于 $2$ 且我们想的到的目标牌数大于 $1$ 我们也可以得到目标牌。\
  以上就是所有要讨论的地方，自己想一想为什么。

# 代码实现

分析完了，那该怎么实现呢？直接一个个判断即可。\
注意：**题目中要你按顺序输出**，所以判断的顺序尤为重要。\
这里给出代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int b,g,r,n;//b,g,r是计数器。
string s;
int main(){
	cin>>n>>s;
	for(int i=0;i<s.size();i++){//开始计数。
		if(s[i]=='G')g++;
		else if(s[i]=='R')r++;
		else b++;
	}
	if(r==0&&g==0||r>0&&g>0||r>1&&b>0&&g==0||g>1&&b>0&&r==0){//分类讨论。
		cout<<"B";//注意：输出顺序为B，G，R。
	}
	if(r==0&&b==0||r>0&&b>0||b>1&&g>0&&r==0||r>1&&g>0&&b==0){
		cout<<"G";
	}
	if(b==0&&g==0||b>0&&g>0||b>1&&r>0&&g==0||g>1&&r>0&&b==0){
		cout<<"R";
	}
	return 0;//华丽的结束。
}
```

---

## 作者：如履薄冰 (赞：3)

# 解法
我们先看一下我们能做的操作：

1. 用两张不同颜色的牌换一张第三种颜色的牌。
2. 用两张相同颜色的牌换一张这个颜色的牌。

我们发现，第二种操作就是减少一张用来做此操作的牌。这下就很好分析啦，我们来分析一下所有解法吧。
## 第一种解法
如果只有一种颜色，那我们就可以一直执行第二种操作，直到只剩下一张这种颜色的牌。
## 第二种解法
如果有其他颜色，我们就果断执行第一种操作，直到只剩下目标颜色的牌。这下，我们就可以使用第一种解法直到目标牌只剩一张。
## 第三种解法
如果有**至少一张**目标牌且有**至少两张**第二种牌，且没有第三种牌。我们可以用若干张目标牌和第二种牌合成若干张第三种牌。现在的情况就可以用第二种解法得到目标牌。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    int n,cntb=0,cntr=0,cntg=0;
    cin>>n;
    string s;
    cin>>s;
    for(int i=0;i<n;i++){
    	if(s[i]=='B'){
    		cntb++;
		}else if(s[i]=='R'){
			cntr++;
		}else{
			cntg++;
		}
	}
	if(cntg>0&&cntr>0||cntg==0&&cntr==0||cntb>=1&&cntr>=2&&cntg==0||cntb>=1&&cntg>=2&&cntr==0){
		cout<<'B';
	}
	if(cntb>0&&cntr>0||cntb==0&&cntr==0||cntg>=1&&cntr>=2&&cntb==0||cntg>=1&&cntr>=2&&cntb==0){
		cout<<'G';
	}
	if(cntb>0&&cntg>0||cntb==0&&cntg==0||cntr>=1&&cntg>=2&&cntb==0||cntg>=1&&cntb>=2&&cntg==0){
		cout<<'R';
	}
    return 0;
}
```

---

## 作者：__UrFnr__ (赞：2)

**题目思路：**

经过长时间的推导，可能是颜色 $x$ 的满足条件如下（满足任意一项即可）：

+ 全部卡片都是颜色 $x$。
+ 除了颜色 $x$ 以外，其他颜色的卡片都有。
+ 其中一种颜色非 $x$ 的卡片数量 $>1$，另一种颜色非 $x$ 的卡片数量为 $0$，颜色为 $x$ 的卡片数量 $>0$（两种情况）。

然后进行代码实现，就能解决本题。

**注意：** 本人尝试过，判断的顺序必须是 B G R，否则会有数据出现错误。

代码如下：


```cpp
#include <bits/stdc++.h>
using namespace std;
int n, gr, re, bl;
string s;
int main () {
    cin >> n >> s;
    for (int i = 0; i < s.size (); i ++) {
        if (s[i] == 'G') 
            gr ++;
        else if (s[i] == 'R') 
            re ++;
        else 
            bl ++;
    }
    if ((gr > 0 && re > 0) || (bl == n) || (re > 1 && gr == 0 && bl > 0) || (gr > 1 && re == 0 && bl > 0)) cout << 'B';
    if ((bl > 0 && re > 0) || (gr == n) || (re > 1 && bl == 0 && gr > 0) || (bl > 1 && re == 0 && gr > 0)) cout << 'G';
    if ((gr > 0 && bl > 0) || (re == n) || (bl > 1 && gr == 0 && re > 0) || (gr > 1 && bl == 0 && re > 0)) cout << 'R';
    
}
```

---

## 作者：Ray_yi (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF626B)

## 思路：

其实简单想一想就能发现，想要得到目标颜色的卡片，只有 $3$ 种可能：

- 这 $n$ 张卡片**只有一种颜色**。这时，我们就能发现只能不断地进行操作 $2$，而这样一直进行下去，最后得到的卡片一定只有这一张。
- 这 $n$ 张卡片**有两种或三种颜色且必须有除了目标颜色之外的其他两种**。这时，我们发现，用除了目标颜色之外的两种颜色不断进行操作 $1$，如果有目标颜色，再进行操作 $2$，这时，是无论如何都能得到目标颜色的。
- 这 $n$ 张卡片**除了目标颜色之外的两种颜色有一种没有，而另一种颜色大于二，且有目标颜色**。这时，我们可以通过把另一种颜色的卡片与目标颜色进行操作 $1$，得到没有的那种颜色，再与另一种颜色进行操作 $1$，即可得到目标颜色。

所以，我们只需要统计每种颜色有多少张卡片，再根据以上 $3$ 种可能分类讨论即可得到答案。

最后，注意一下输出的顺序，就能解决本题。

思路比较详细，就不放代码了。

---

## 作者：linan04195 (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/CF626B)
---
## 思路
读完题后，可以总结出一些规律，颜色 $colour$ 满足一些规律：

1. 字符串 $s$ 中全部都是颜色为 $colour$ 的卡片。
2. 字符串 $s$ 中有三种颜色的卡片。
3. 字符串 $s$ 中有两种颜色的卡片。

我们可以用 $B$，$R$，$G$ 三个变量来储存三种颜色出现的次数。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int size;
int B,R,G;
int main(){
	cin>>size;
	for(int i=0;i<size;i++){
		char ch;
		cin>>ch;
		switch(ch){
			case 'B':
				B++;
				break;
			case 'R':
				R++;
				break;
			case 'G':
				G++;
				break;
		}
	}
	if(B==size||(B==0&&G==1&&R)||(G>1&&R==0&&B==1)||(G==0&&R>1&&B==1)) cout<<"B";
	
	if(R==size||(R==0&&B==1&&G==1)||(B>1&&G==0&&R==1)||(B==0&&G>1&&R==1)) cout<<"R";
	
	if(G==size||(G==0&&B==1&&R==1)||(B>1&&R==0&&G==1)||(B==0&&R>1&&G==1)) cout<<"G";
}
```

---

## 作者：封禁用户 (赞：1)

## 思路
读完题目，不难看出，最后一张卡可能的颜色 $i$ 需要满足以下条件：
- 卡片颜色均为 $i$。
- 有一种颜色不是 $i$ 的卡片，没有另一种颜色不是 $i$ 的卡片，且颜色是 $i$ 的卡片出现过。（分别有两种）
- 除了 $i$ 意外，其他颜色字符串 $s$ 中都有。

此外，要按 $\texttt{BGR}$ 的顺序输出。

## Code

```cpp
#include <bits/stdc++.h>

using namespace std;

int n, G, R, B;
string s;

int main(void) 
{
	cin >> n >> s;
	
	for (int i = 0; i < s.size(); i ++) {
		if (s[i] == 'G') {
			G++;
		} else if (s[i] == 'R') {
			R++;
		} else {
			B++;
		}
	}
	
	if ((G > 0 && R > 0) || 
		(B == n) || 
		(R > 1 && G == 0 && B > 0) || 
		(G > 1 && R == 0 && B > 0)) 
	{
		cout << 'B';
	}
	
	if ((B > 0 && R > 0) || 
		(G == n) || 
		(R > 1 && B == 0 && G > 0) || 
		(B > 1 && R == 0 && G > 0)) 
	{
		cout << 'G';
	}
	
	if ((G > 0 && B > 0) || 
		(R == n) || 
		(B > 1 && G == 0 && R > 0) || 
		(G > 1 && B == 0 && R > 0)) 
	{
		cout << 'R';
	}

	return 0;
}
```

---

## 作者：Yiyi_52MIYEON1314 (赞：0)

# 题意
[题目链接，不爱看题的快去给我看！！](https://www.luogu.com.cn/problem/CF626B)

题意简洁，就是有两种操作，这里不再赘述。

# 思路
设经过操作后可能变成的颜色为 $c$，序列中蓝色个数为 $b$，绿色个数为 $g$，红色个数为 $r$。  
那么需满足下面条件中的任意一点即可。

- 所有卡片颜色均为 $x$。只需一直进行**操作二**就可以达成效果。
- 除了颜色 $x$ 以外，其他颜色都有。只需一直进行**操作一**，直到所有卡片均为颜色 $x$，最后再使用**操作二**就可以达成效果。 
- 颜色 $x$ **大于一张**，其他的两种卡片，一种**没有** 设为颜色 $y$，一种**大于两张** 设为颜色 $z$。只需一直进行**操作二**，直到所有颜色 $z$ 的卡片变为两张，颜色 $x$ 的卡片变为一张后，再使用**操作一**将颜色 $x$ 的卡片和颜色 $z$ 的卡片中的一张变为颜色 $y$，最后再使用**操作一**将颜色 $z$ 和颜色 $y$ 变为颜色 $x$ 就可以达到效果。  

如果不能理解，可以根据样例或自己再举几个例子进行分析。

~~自认为已经很详细了。~~

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,b,g,r;
string s;
int main()
{
	cin>>n>>s;
	for(int i=0;i<n;i++){
		if(s[i]=='B')b++;
		else if(s[i]=='G')g++;
		else if(s[i]=='R')r++;
	}
	if(r==0&&g==0||r>0&&g>0||r>1&&b>0&&g==0||g>1&&b>0&&r==0){
		cout<<"B";
	}
	if(r==0&&b==0||r>0&&b>0||b>1&&g>0&&r==0||r>1&&g>0&&b==0){
		cout<<"G";
	}
	if(b==0&&g==0||b>0&&g>0||b>1&&r>0&&g==0||g>1&&r>0&&b==0){
		cout<<"R";
	}
 	return 0;
}

```
### 谢谢大家！

---

## 作者：syf159 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF626B)

## 分析

对于本题，如何操作并不重要，重要在于每一种颜色的分布。

我们可以统计三种颜色每个颜色的分布，并进行分析，即可求出答案。

对于可以实现的颜色，有以下几种情况：

1. $n$ 张卡片全是一种颜色；
2. 其他两种卡片数量都在 $1$ 及以上（操作 1）；
3. 一种卡片没有，一种卡片数量大于等于 $2$，最后一种数量大于等于 $1$；

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
string s;
int red,green,blue;
int main(){
	cin>>n>>s;
	for(int i=0; i<n; i++)
	{
		if(s[i]=='R') red++;
		else if(s[i]=='G') green++;
		else blue++;
	}//统计每一种颜色卡牌的数量
	//-----------分界线-----------// 
	if(green>=1&&red>=1) cout<<'B';
	else if(green==0&&red>=2&&blue>=1) cout<<'B';
	else if(red==0&&green>=2&&blue>=1) cout<<'B';
	else if(blue==n) cout<<'B';
	//-----------分界线-----------// 
	if(blue>=1&&red>=1) cout<<'G';
	else if(blue==0&&red>=2&&green>=1) cout<<'G';
	else if(red==0&&blue>=2&&green>=1) cout<<'G';
	else if(green==n) cout<<'G';
	//-----------分界线-----------// 
	if(blue>=1&&green>=1) cout<<'R';
	else if(green==0&&blue>=2&&red>=1) cout<<'R';
	else if(blue==0&&green>=2&&red>=1) cout<<'R';
	else if(red==n) cout<<'R';
	//-----------分界线-----------// 
	//按照 B、G、R 的顺序依次判断
	return 0;
}
```

---

## 作者：Zheng_iii (赞：0)

## 思路
枚举三种能够得到该颜色的方法。

- 全是该颜色的卡牌。
- 另外两种卡牌的数量都大于等于一张。
- 另外的两种卡牌，一种大于等于两张，一种为零张，该颜色的卡牌大于等于一张。

我们用三个变量来记录每种卡牌出现的次数，然后按照以上的三种方法模拟即可。

## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
int n,r,b,g;
char a;

int main(){
	// freopen("text.in","r",stdin);
	// freopen("text.out","w",stdout);
	ios::sync_with_stdio(0),cout.tie(0),cin.tie(0);
	cin>>n;
	for(int i = 1;i <= n;i++){
		cin>>a;
		if(a == 'R')r++;
		if(a == 'G')g++;
		if(a == 'B')b++;
	}
	if(b==n||(b==0 && g && r)||(g > 1 && r==0 &&b)||(g==0&& r>1 &&b)){
		cout<<"B";
	}
	if(g==n||(g==0 && b && r)||(b>1 && r==0 && g)||(b==0 && r>1 &&g)){
		cout<<"G";
	}
	if(r==n||(r==0 && b && g)||(b>1 && g==0 && r)||(b==0 && g>1 && r)){
		cout<<"R";
	}
	return 0;
}
```

---

## 作者：glass_goldfish (赞：0)

## 题意
操作分为：
1. 取两张（不一定是相邻的）不同颜色的卡片，换成第三种颜色的新卡片；
2.  取两张（不一定是相邻的）相同颜色的卡片，换成一张有这种颜色的新卡片。
## 结论
1. 只有某种颜色，那么那种颜色可以。
2. 某种颜色没有，其他都有，那么那种颜色可以。
3. 某种颜色有，另一种颜色 $>1$，最后一种没有，那么那种颜色可以。
## 分析
让我们开始证明：  
1. 只有某种颜色，那么那种颜色可以。一直执行操作二即可。
2. 某种颜色没有，其他都有。首先，把其他通过操作二都变成 $1$ 张，然后执行操作一即可。
3. 某种颜色有，另一种颜色 $>1$，最后一种没有。首先，把这一种颜色通过操作二变成 $1$ 张，然后把另一种颜色通过操作二变成 $2$ 张。首先，结合这两种各一张，得到原先没有的颜色；然后执行操作一即可。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define INF 0x3f3f3f
using namespace std;
int n,b,g,r;
char c;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>c;
		if(c=='B')b++;
		else if(c=='G')g++;
		else if(c=='R')r++;
	}
	if(b==n||(b==0&&g&&r)||(g>1&&r==0&&b)||(g==0&&r>1&&b)){
		cout<<"B";
	}
	if(g==n||(g==0&&b&&r)||(b>1&&r==0&&g)||(b==0&&r>1&&g)){
		cout<<"G";
	}
	if(r==n||(r==0&&b&&g)||(b>1&&g==0&&r)||(b==0&&g>1&&r)){
		cout<<"R";
	}
    return 0;
}
```

---

## 作者：liyp (赞：0)

## 思路
只需要推导一下题目即可。

首先提出一个问题：当满足什么条件时结果可能是某种颜色？

经过推导我们可以得出，只要满足以下三个条件中的一个，就可能是目标颜色（接下来我们设目标颜色为 $x$）：

1. 当**所有卡牌都是** $x$ 颜色时。

2. 除 $x$ 颜色以外的颜色卡牌**每一种都有**。

3. 当其中一种颜色非 $x$ 的卡牌**没有**，且另一种颜色非 $x$ 卡牌有**至少两个**，同时也**有**颜色为 $x$ 的卡牌。（写成代码实际会有两种情况）

写得可能有点绕，可以结合**代码**进行理解。

既然这些都推出来了，那接下来就简单了。

## 完整代码
```cpp
#include <bits/stdc++.h>
using namespace std;
signed main()
{
    int n;
    int g = 0, r = 0, b = 0;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        char c;
        cin >> c;
        if (c == 'B') b++;
        if (c == 'G') g++;
        if (c == 'R') r++;
    }
    if ((g && r) || (r > 1 && !g && b) || (b == n) || (g > 1 && !r && b)) {
        cout << "B";
    }
    if ((b && r) || (r > 1 && !b && g) || (g == n) || (b > 1 && !r && g)) {
        cout << "G";
    }
    if ((g && b) || (b > 1 && !g && r) || (r == n) || (g > 1 && !b && r)) {
        cout << "R";
    }
    return 0;
}
```

---

## 作者：lpx666666 (赞：0)

## 题面
给出一些牌，同色的两张牌合成这个颜色的一张牌，异色的两张牌合成第三个颜色的一张牌，问最后可能合成的所有颜色的牌。

## 思路
这道题很明显需要分类思考，用给出的卡牌颜色种类数量分类，一共有三种可能。

当只有一种牌时，它们只能同色合成，最后得出的也只可能是这个颜色。

当有两种牌时，稍微复杂，我们可以先整理题面的操作，通过同色合成的操作我们可以发现，我们可以将每一种牌减少到任意数量（但不小于一），而第二个操作中，我们不难发现，当一张牌与另外两张牌操作，且另外两张牌颜色相同，那么最终得到的依旧是这张牌，所以当有两张牌时，只要一种牌的数量大于或等于二，那么结合上述，这种牌就能成为可能。

所以第三种颜色是一定能得出的。

但我们发现此时又需要按大于或等于二牌的颜色种类数量分类。

当没有时，那就只有第三种颜色能得出。

一个时，除了那个大于或等于二牌的颜色种类以外，其他的都可以。

两个时，这两种牌都能利用另一种牌得出，那么三种就都能得出。

当有三种牌时，我们可以将每种都转为一张，那么每一种颜色都能通过另外两种的合成得出。

## 代码
思路出来了，代码难度非常低，但最近此题洛谷上交不了，原站的[提交记录](https://codeforces.com/contest/626/submission/276054310)。

上代码。

```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
int n,p[11][2];
string s,ss="";
int main(){
	cin>>n>>s;
	for(int i=0;i<s.size();i++){
		if(s[i]=='B'){
			if(!p[1][1]) ss+="B";
			p[1][1]=1;
			p[1][2]++;
		}
		else if(s[i]=='G'){
			if(!p[2][1]) ss+="G";
			p[2][1]=1;
			p[2][2]++;
		}
		else{
			if(!p[3][1]) ss+="R";
			p[3][1]=1;
			p[3][2]++;
		}
	}
	int u=p[1][1]+p[2][1]+p[3][1];
	if(u==1){
		cout<<ss;
	}
	else if(u==2){
		int cnt=0;
		if(p[1][2]>=2){
			cnt++;
		}
		if(p[2][2]>=2){
			cnt++;
		}
		if(p[3][2]>=2){
			cnt++;
		}
		if(cnt==0){
			if(p[1][2]==0){
				cout<<"B";
			}
			else if(p[2][2]==0){
				cout<<"G";
			}
			else{
				cout<<"R";
			}
		}
		else if(cnt==1){
			if(p[1][2]>=2){
				cout<<"GR";
			}
			else if(p[2][2]>=2){
				cout<<"BR";
			}
			else{
				cout<<"BG";
			}
		}
		else{
			cout<<"BGR";
		}
	}
	else{
		cout<<"BGR";
	}
	return 0;//华丽收场
}

```

---

## 作者：Breath_of_the_Wild (赞：0)

题意：翻译已经很清楚了，不说了。

这题就是一个分类讨论的题，只要你不重不漏的枚举所有的情况，就可以过本题。

对于每种颜色，我们都判断它能否成为最终颜色。我们暂且就把当前试着判断的叫做【最终颜色】。

分 $3$ 种情况：
1. 最终颜色除外的两种颜色个数都 $>0$。这时可以用第一种操作把两种颜色都消成 $1$ 个，再用第二种操作把两种剩下的替换成最终颜色。剩下两个最终颜色，再用第一种操作消成 $1$ 个最终颜色。这时符合要求的。
2. 最终颜色 $>0$，剩下的一种 $>1$，另外一个 $=0$。此时可以用最终颜色和 $>1$ 的这种换成 $=0$ 的那种，这样就变成了第一种，同样符合条件。注意，这种情况你需要判断两种情况，即看看除最终颜色外，哪一种 $>1$ 且另外一个 $=0$。
3. 字符串中全是最终颜色，即样例 $3$ 的情况。显然满足条件。

所以预处理每个颜色的个数，然后每种颜色判断就行了。代码不给了。

---

## 作者：enyyyyyyy (赞：0)

大模拟！把所有的字符标记一下，放进数组中，再枚举有没有满足：

- 两张（不一定是相邻的）不同颜色的卡片；

- 两张（不一定是相邻的）相同颜色的卡片。

如果有那就输出:

- 第三种颜色的新卡片；

- 一张有这种颜色的新卡片。
## AC code:

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef __int128 lint;
typedef double db;
typedef void vd;
typedef bool bl;
inline ll read() {
	ll s = 0, w = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-')
			w = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') s = s * 10 + ch - '0', ch = getchar();
	return s * w;
}
inline vd print(ll x) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x >= 10)
		print(x / 10);
	putchar(x % 10 + '0');
	return;
}
ll cnt[3],n;
string s;
int main(){
 	n=read(),cin>>s;
  	for(ll i=0;i<s.size();i++) 
    	if(s[i]=='B') cnt[0]++; 
    	else if(s[i]=='G') cnt[1]++;
    	else cnt[2]++;
  	for(ll i = 0; i < 3; i++) {
    	ll x=cnt[i%3],y=cnt[(i+1)%3],z=cnt[(i+2)%3];
    	bool flag=0;
    	if(y&&z) flag=1;
    	if(x&&max(y,z)>1) flag=1;
    	if(!y&&!z) flag=1;
    	if(flag) cout<<"BGR"[i];
  	}	
	return 0;
}

```


---

## 作者：Crab_Dave (赞：0)

## T1题解

+ 题意

  给出一叠卡，卡有三种颜色`R`、`G`、`B`，我们可以把两张相同的卡合为一张（如`RR`->`R`），也可以把两张不同的卡换成另一张（如`BG`->`R`）。问是否存在最终剩下某种颜色的牌的方案。

+ 思路

  由第一个性质可知，重复的牌可以不要（合二为一）。

  那我们考虑记录是否分别出现了三种牌。

  显然每种牌只有0/1张的时候我们只能通过以二转一的方式得到另一张牌。

  直接枚举一下特判掉。

  但是又注意到`BRB`->`GB`->`R`，此时我们得到了另一种方式。

  通过枚举可以证明只有这一种情况会对答案造成额外影响。

  加入特判即可。复杂度 $O(3*3*3)$，人脑级别的特判。

+ 代码

  无注释版。

  ```cpp
  if(B){
      if(G){
          if(R){fr=fg=fb=1;goto print;}
          else{
              fr=1;
              if(B>1)fg=1;
              if(G>1)fb=1;
              goto print;
          }
      }
      else{
          if(R){
              fg=1;
              if(B>1)fr=1;
              if(R>1)fb=1;
              goto print;
          }
          else{fb=1;goto print;}
      }
  }
  else{
      if(G){
          if(!R){fg=1;goto print;}
          else{
              fb=1;
              if(R>1)fg=1;
              if(G>1)fr=1;
              goto print;
          }
      }
      else{if(R){fr=1;goto print;}}
  }
  ```

  

---

## 作者：TAN2431 (赞：0)

这一题比较简单。思路如下。\
我们可以将三种不同的卡牌分别视为目标牌。\
当一种颜色的牌为目标时，有几种可能分别是：\
1\. 只有这种颜色。\
2\. 另外两种颜色都有（可换为目标色）。\
3\. 除目标色外，一种颜色无，剩下的一种颜色大于 2（可和目标色换第三种，再用第三种换目标。

```cpp
#include<bits/stdc++.h>
using namespace std;
char a[1000];
int n,b,r,g;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		if(a[i]=='B') b++;
		if(a[i]=='G') g++;
		if(a[i]=='R') r++;
	}
if((g==0&&r==0)||(g>0&&r>0)||(g==0&&b>=1&&r>=2)||(r==0&&b>=1&&g>=2))	cout<<"B";
if((b==0&&r==0)||(b>0&&r>0)||(b==0&&g>=1&&r>=2)||(r==0&&g>=1&&b>=2))	cout<<"G";
if((b==0&&g==0)||(g>0&&b>0)||(g==0&&r>=1&&b>=2)||(b==0&&r>=1&&g>=2))	cout<<"R";
	
}
```

---

