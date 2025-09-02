# Tokitsukaze and Mahjong

## 题目描述

Tokitsukaze is playing a game derivated from Japanese mahjong. In this game, she has three tiles in her hand. Each tile she owns is a suited tile, which means it has a suit (manzu, pinzu or souzu) and a number (a digit ranged from $ 1 $ to $ 9 $ ). In this problem, we use one digit and one lowercase letter, which is the first character of the suit, to represent a suited tile. All possible suited tiles are represented as 1m, 2m, $ \ldots $ , 9m, 1p, 2p, $ \ldots $ , 9p, 1s, 2s, $ \ldots $ , 9s.

In order to win the game, she must have at least one mentsu (described below) in her hand, so sometimes she should draw extra suited tiles. After drawing a tile, the number of her tiles increases by one. She can draw any tiles she wants, including those already in her hand.

Do you know the minimum number of extra suited tiles she needs to draw so that she can win?

Here are some useful definitions in this game:

- A mentsu, also known as meld, is formed by a koutsu or a shuntsu;
- A koutsu, also known as triplet, is made of three identical tiles, such as \[1m, 1m, 1m\], however, \[1m, 1p, 1s\] or \[1m, 4m, 7m\] is NOT a koutsu;
- A shuntsu, also known as sequence, is made of three sequential numbered tiles in the same suit, such as \[1m, 2m, 3m\] and \[5s, 7s, 6s\], however, \[9m, 1m, 2m\] or \[1m, 2p, 3s\] is NOT a shuntsu.

Some examples:

- \[2m, 3p, 2s, 4m, 1s, 2s, 4s\] — it contains no koutsu or shuntsu, so it includes no mentsu;
- \[4s, 3m, 3p, 4s, 5p, 4s, 5p\] — it contains a koutsu, \[4s, 4s, 4s\], but no shuntsu, so it includes a mentsu;
- \[5p, 5s, 9m, 4p, 1s, 7p, 7m, 6p\] — it contains no koutsu but a shuntsu, \[5p, 4p, 6p\] or \[5p, 7p, 6p\], so it includes a mentsu.

Note that the order of tiles is unnecessary and you can assume the number of each type of suited tiles she can draw is infinite.

## 说明/提示

In the first example, Tokitsukaze already has a shuntsu.

In the second example, Tokitsukaze already has a koutsu.

In the third example, Tokitsukaze can get a shuntsu by drawing one suited tile — 1p or 4p. The resulting tiles will be \[3p, 9m, 2p, 1p\] or \[3p, 9m, 2p, 4p\].

## 样例 #1

### 输入

```
1s 2s 3s
```

### 输出

```
0
```

## 样例 #2

### 输入

```
9m 9m 9m
```

### 输出

```
0
```

## 样例 #3

### 输入

```
3p 9m 2p
```

### 输出

```
1
```

# 题解

## 作者：Eismcs (赞：6)

oier常说，暴力出奇迹。

这题就诠释了这句话。当然，并非时间上的暴力，而是代码写法的暴力

只需要列举每种情况，要么是操作0次，要么操作1次，最多操作2次。当操作0或1次的情况都不满足那么便是操作2次了
```cpp
#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<queue>
#include<map> 
using namespace std;
#define re register int
inline int read(){
    int x=0,ff=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')ff=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    return x*ff;
}
signed main(){
    string a,b,c;
    cin>>a>>b>>c;
    if(a[1]==b[1]&&b[1]==c[1]&&a[0]+1==b[0]&&b[0]+1==c[0]){cout<<0<<endl;return 0;}
    if(a[1]==b[1]&&b[1]==c[1]&&a[0]-1==b[0]&&b[0]-1==c[0]){cout<<0<<endl;return 0;}
    if(a[1]==b[1]&&b[1]==c[1]&&a[0]+2==b[0]&&b[0]-1==c[0]){cout<<0<<endl;return 0;}
    if(a[1]==b[1]&&b[1]==c[1]&&a[0]-2==b[0]&&b[0]+1==c[0]){cout<<0<<endl;return 0;}
    if(a[1]==b[1]&&b[1]==c[1]&&a[0]-1==b[0]&&b[0]+2==c[0]){cout<<0<<endl;return 0;}
    if(a[1]==b[1]&&b[1]==c[1]&&a[0]+1==b[0]&&b[0]-2==c[0]){cout<<0<<endl;return 0;}
    if(a[1]==b[1]&&b[1]==c[1]&&a[0]==b[0]&&b[0]==c[0]){cout<<0<<endl;return 0;}
    if(a[1]==b[1]&&a[0]==b[0]){cout<<1<<endl;return 0;}
    if(a[1]==b[1]&&a[0]+1==b[0]){cout<<1<<endl;return 0;}
    if(a[1]==b[1]&&a[0]-1==b[0]){cout<<1<<endl;return 0;}
    if(a[1]==b[1]&&a[0]+2==b[0]){cout<<1<<endl;return 0;}
    if(a[1]==b[1]&&a[0]-2==b[0]){cout<<1<<endl;return 0;}
    if(a[1]==c[1]&&a[0]==c[0]){cout<<1<<endl;return 0;}
    if(a[1]==c[1]&&a[0]+1==c[0]){cout<<1<<endl;return 0;}
    if(a[1]==c[1]&&a[0]-1==c[0]){cout<<1<<endl;return 0;}
    if(a[1]==c[1]&&a[0]+2==c[0]){cout<<1<<endl;return 0;}
    if(a[1]==c[1]&&a[0]-2==c[0]){cout<<1<<endl;return 0;}
    if(c[1]==b[1]&&c[0]==b[0]){cout<<1<<endl;return 0;}
    if(c[1]==b[1]&&c[0]+1==b[0]){cout<<1<<endl;return 0;}
    if(c[1]==b[1]&&c[0]-1==b[0]){cout<<1<<endl;return 0;}
    if(c[1]==b[1]&&c[0]+2==b[0]){cout<<1<<endl;return 0;}
    if(c[1]==b[1]&&c[0]-2==b[0]){cout<<1<<endl;return 0;}
    //上面是根据题意的每种操作0或1次的情况，只要理解题意都能看懂
    cout<<2<<endl;
    //0或1次都不行，那么最多操作2次
    return 0;
}
```
看着有些棘手，但是暴力却简单解决，只是思考要全面

---

## 作者：GONGX (赞：5)

## 题意简述
给出 $3$ 个麻将，每个麻将上有一个 $2$ 位的字符串（ 由 $1-9$ 的一位数字和 $m,s,p$ 组成 ）。

求至少要换多少个麻将才能一次出完 $3$ 个麻将。

有两种出牌方式:

1. $3$ 个完全相同的麻将

2. 第 $2$ 位相同，且前面是连号的

## 解题思路
这道题只需用简单的模拟即可。

观察题目即可发现本题的答案只有 $3$ 个可能 ：$0$，$1$，$2$。所以只需先排好顺序再列举出所有情况即可。

### 排序规则：先按第二位的大小排序，再按第一位的大小进行排序 

通过推理即可得到所有的情况，所有情况如下：

### 一、当需要交换 $0$ 次时：
1. 三个麻将全部相同。
2. 所有麻将第二位全部相同，且第一位为连续的序号。

### 二、当需要交换 $1$ 次时：
1. 其中两个麻将相同。
2. 其中有两个麻将第二位相同，第一位则相差 $2$。
3. 其中有两个麻将第二位相同，且第一位为连续的序号。

### 三、当需要换 $2$ 次时：
除了上述情况都是需要换两次的。

## 代码展示
```c
#include<bits/stdc++.h>
using namespace std;
int cmp(string a,string b){//先按第二位的大小排序，再按第一位的大小进行排序 
	if(a[1]<b[1]){
		if(a[0]<b[0]) return 1;
		else return 0;
	}else if(a[1]==b[1]){
		if(a[0]<b[0]) return 1;
		else return 0;
	}else return 0;
}string a[4];
int main(){for(int i=0;i<3;i++)cin>>a[i];//输入数据（本题输入数据很小不用循环也可以）
	sort(a,a+3,cmp);
	//当无需交换时： 
	if(a[0]==a[1]&&a[1]==a[2])puts("0");//全部相同 
	else if(a[0][1]==a[1][1]&&a[0][1]==a[2][1]&&a[0][0]+1==a[1][0]&&a[1][0]+1==a[2][0])puts("0");//当所有麻将后一位都相同且第一位为升序时
	//当需要交换1次或2次时:
	else{//本蒟蒻采用循环枚举求解，也可以直接采用暴力判断求解
		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++){
				if(i==j||a[i][1]!=a[j][1])continue;
				if(a[i]==a[j]){puts("1");return 0;}//当有两个麻将相同时 
				else if(a[i][1]==a[j][1]&&(a[i][0]+1==a[j][0]||a[i][0]+2==a[j][0])){puts("1");return 0;}
				//当确定答案为2时直接结束程序即可 
			}
		}puts("2");//还没结束程序就说明答案是2 
	}
return 0;
}
```

---

## 作者：hsfzLZH1 (赞：3)

## 题目大意

~~本人不会玩麻将，所以翻译尽可能按照题面来~~

这是日式麻将的一种衍生版。

一张麻将牌由一种类型（ $m,p,s$ ）和一个数字（ $1,2,...,9$ ）组成。类型为 $p$ ，数字为 $4$ 的牌表示为 $4p$ 。

**一开始你手中有三张牌**。每次你会抽一张牌，这张牌可以是任意一张合法的麻将牌（和手中已有的牌一样也可以）。你可以抽任何一张你想要的牌。

要赢得这个游戏，你手中至少要有一个 mentsu 。

一个 mentsu 由一个 koutsu **或** 一个 shuntsu 组成。 koutsu 就是三张完全一样的牌。 shuntsu 就是三张类型一样，数字 **连续** 的三张牌。（和你手中牌的顺序无关，只要有三张牌构成这一类型即可）

给出一开始你手中的三张牌，问你最少还要抽多少张牌才能赢。

## 解题思路

有一种用二维数组的解法。

我们用一个二维数组 $tf[i][j]$ 表示数字为 $i$ ，类型为 $j$ 的牌在初始手牌中的出现次数。我们不必对每种类型的牌确定一个对应的编号，由于输入的是字符类型，我们可以开一个 $128\times 128$ 的数组在存储。

首先我们考虑用手中的牌构成 koutsu 的情况，我们找到 $tf[i][j]$ 的最大值，这就是手牌中最多相同的牌数。要构成 koutsu 而胜利，最优的方法就是把这张牌补到三张，这样的答案就是 $3-\max\{tf[i][j]\}$ 。

接下来考虑构成 shuntsu 的情况。 shuntsu 的要求是三张类型相同的牌，数字连续。我们枚举相同的类型 $j$ ，接着枚举 shuntsu 中最小的数字，需要补全的最小牌数为 $3-$ 从最小的数字开始连续的三个位置有多少个 $tf=0$ 。

上面的写法要 **处理边界条件** 。本人的写法是判断相同类型连续的数字有多少个，用 $3$ 减去这个值计入答案，并特判形如 $2m~4m$ 的两张牌，只需补一张 $3m$ 即可的情况。

## 代码展示

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
const int maxn=5;
int ans,maxx;
char s[maxn][maxn];
int tf[128][128];
int main()
{
    for(int i=1;i<=3;i++)scanf(" %c%c",s[i]+1,s[i]+2),tf[(int)s[i][1]][(int)s[i][2]]++;
    for(int i=0;i<128;i++)for(int j=0;j<128;j++)maxx=max(maxx,tf[i][j]);
    ans=3-maxx;
    for(int j=0;j<128;j++)
    {
    	maxx=0;
    	for(int i=0;i<128;i++)
    	{
    		if(tf[i][j])maxx++;
    		else maxx=0;
    		ans=min(ans,3-maxx);
    		if(i-2>=0&&tf[i][j]&&tf[i-2][j])ans=min(ans,1);
    	}
    }
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：hhhppp (赞：2)

_一道字符串模拟题。_ 

## 简述题意

给出三个麻将，有两种出牌方式：
 
1.  三个麻将相同。

2. 第二位相同，前面连号。

求换几个麻将可以出牌。

## 思路

既然麻将数量只有三个，那么可以比较简单地推出一共有一下几种情况：

####  换 0 个麻将的情况：
- 三个麻将相同。
- 第二位相同，前面连号。

####  换 1 个麻将的情况：
- 其中有两个麻将相同。
- 其中有两个麻将第二位相同，第一位连号。
- 其中有两个麻将第二位相同，第一位相差 2。

#### 换 2 个麻将的情况：
- 除了上面的情况都是换两个麻将。

为了更方便判断，先给这三个麻将排一下序，然后就可以直接模拟了。

##  _那么，理论存在，实践开始。_ 


## 代码实现

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>//sort要用的头文件 
using namespace std;
int cmp(string a,string b){//先按第二位大小来排序，再按照第一位大小排序 
	if(a[1]==b[1]){
		if(a[0]<b[0]) return 1;
		else return 0;
	}
	else if(a[1]<b[1]){
		if(a[0]<b[0]) return 1;
		else return 0;
	}
	else return 0;
}
int main(){
	string a[10];
	cin>>a[0]>>a[1]>>a[2];
	sort(a,a+3,cmp);
	//排完序方便判断 
	if(a[0]==a[1]&&a[0]==a[2]) cout<<0<<endl;
	else if(a[0][1]==a[1][1]&&a[0][1]==a[2][1]&&a[0][0]+1==a[1][0]&&a[1][0]+1==a[2][0]) cout<<0<<endl;
	//交换0个麻将的情况 
	else if(a[1][1]==a[2][1]&&a[1][0]+1==a[2][0]) cout<<1<<endl;
	else if(a[0][1]==a[1][1]&&a[0][0]+1==a[1][0]) cout<<1<<endl;
	else if(a[0][1]==a[2][1]&&a[0][0]+1==a[2][0]) cout<<1<<endl;
	else if(a[1][1]==a[2][1]&&a[1][0]+2==a[2][0]) cout<<1<<endl;
	else if(a[0][1]==a[1][1]&&a[0][0]+2==a[1][0]) cout<<1<<endl;
	else if(a[0][1]==a[2][1]&&a[0][0]+2==a[2][0]) cout<<1<<endl;
	else if(a[0]==a[1]||a[1]==a[2]||a[0]==a[2]) cout<<1<<endl;
	//交换1个麻将的情况 
	else cout<<2<<endl;
	//其余情况交换2个 
	return 0;//完美结束QAQ 
}
```

刚开始卡了好多次，后来参考了 Alex_Wei 大佬的代码才过的，拜谢 Orz。

---

## 作者：Alex_Wei (赞：2)

因为本题的数据很小，所以模拟即可

观察题目，可以发现 要想凑成一个 $mentsu$，**那么它们末尾的字母一定是相同的**

所以，我们可以把题目给的 $3$ 个字符串排序，规则如下：

**优先字母从小到大排，字母相同数字从小到大排**

然后就可以愉快地模拟啦~

具体实现细节见代码

```cpp
#include<bits/stdc++.h>
using namespace std;
string a[3];
bool cmp(string a,string b){return a[1]<b[1]||a[1]==b[1]&&a[0]<b[0];}
//排序规则
int main()
{
	cin>>a[0]>>a[1]>>a[2];
	if(a[0]==a[1]&&a[1]==a[2])cout<<0,exit(0);
	//如果三个字符串相同，那么它们一定可以构成一个"mentsu"
	sort(a,a+3,cmp);//排序
	if(a[0][1]==a[1][1]&&a[1][1]==a[2][1]&&a[0][0]+1==a[1][0]&&a[1][0]+1==a[2][0])cout<<0,exit(0);
	//如果三个字符串字母相同，数字连续（已经排过序了）那么它们一定可以构成一个"mentsu"
	if(a[0][1]==a[1][1]&&a[0][0]+1==a[1][0])cout<<1,exit(0);
	if(a[1][1]==a[2][1]&&a[1][0]+1==a[2][0])cout<<1,exit(0);
	//如果有两个字符串字母相同，数字连续，那么就还要1个麻将才能凑出"mentsu"
	if(a[0][1]==a[1][1]&&a[0][0]+2==a[1][0])cout<<1,exit(0);
	if(a[1][1]==a[2][1]&&a[1][0]+2==a[2][0])cout<<1,exit(0);
	//如果有两个字符串字母相同，数字相隔1，那么也还要1个麻将才能凑出"mentsu"
	if(a[0]==a[1]||a[1]==a[2])cout<<1,exit(0);
	//如果有两个字符串相同，那么也还要1个麻将才能凑出"mentsu"
	cout<<2;//否则需要两个 
	return 0;
}
```


---

## 作者：Meatherm (赞：1)

### 概述

一堆`if`即可。~~然而我写出了一堆`bug`居然还`Pretest Passed`了。当然最后`Failed System Test`辣QAQ~~。

### 思路

专业麻将术语：

- `shuntsu`。这堆牌里三张牌**类别相同**，且排序之后的**数字是连续的**。

- `koutsu`。这堆牌里有三张牌**完全一致**。

题目要求的胜利条件：

 `mentsu`。这堆牌里有`shuntsu`或`koutsu`的**至少一种**。

容易发现，要胜利最多只用画$2$张牌。假设原来有一张牌$x$，最多再画两张$x$就组成`koutsu`了。

--- 

将题目给到的三张牌按照第一关键字为**类别**，第二关键字为**牌上的数字**进行排序。

1. 如果它们全部相等，那么满足`koutsu`，需要加$0$张牌。

2. 如果它们类别全部相同，且数字连续，那么满足`shuntsu`，需要加$0$张牌。

3. 如果它们类别全部不相同，那么需要加$2$张牌。

4. 如果有两张牌完全相同，那么需要加$1$张牌。

5. 如果有两张牌类型相同，且数字连续，那么需要加$1$张牌。

6. 如果有两张牌类型相同，且数字相差$2$，那么需要加$1$张。

7. 如果上述的条件都不满足，那么需要加$2$张牌。

注意：如果某三张牌同时满足上面的几个条件，那么答案为编号最小的条件的答案。


```cpp
# include <bits/stdc++.h>
# define rr register
struct Node{
	int s,c;
}a[100];
bool cmp(Node a,Node b){
	if(a.c!=b.c)
		return a.c<b.c;
	return a.s<b.s;	
}
bool operator == (Node a,Node b){
	if(a.c==b.c&&a.s==b.s){
		return true;
	}
	return false;
}
int main(void){
	for(rr int i=1;i<=3;++i){
		char tmp1,tmp2;
		std::cin>>tmp1>>tmp2;
		a[i].s=tmp1-48;//smp
		if(tmp2=='s')
			a[i].c=1;
		if(tmp2=='m')
			a[i].c=2;
		if(tmp2=='p')
			a[i].c=3;
	}
	std::sort(a+1,a+1+3,cmp);
	if(a[1]==a[2]&&a[2]==a[3]){//全部相等 
		printf("0");
		return 0;
	}
	if(a[1].c==a[2].c&&a[2].c==a[3].c&&a[2].s-1==a[1].s&&a[3].s-1==a[2].s){//顺子 
		printf("0");
		return 0;
	}
	if(a[1].c!=a[2].c&&a[2].c!=a[3].c){//都不相等 
		printf("2");
		return 0;
	}
	if(a[1]==a[2]){//有两个相等
		printf("1");
		return 0;
	}
	if(a[2]==a[3]){
		printf("1");
		return 0;
	}
	if(a[1].c==a[2].c&&a[2].s-a[1].s==1){//有两个连续 
		printf("1");
		return 0;
	}
	if(a[2].c==a[3].c&&a[3].s-a[2].s==1){
		printf("1");
		return 0;
	}
	if(a[1].c==a[3].c&&a[1].s+2==a[3].s){//要加在中间
		printf("1");
		return 0;
	}
	if(a[1].c==a[2].c&&a[1].s+2==a[2].s){
		printf("1");
		return 0;
	}
	if(a[2].c==a[3].c&&a[2].s+2==a[3].s){
		printf("1");
		return 0;
	}
	printf("2");//都不满足
	return 0;
}
```

---

## 作者：fish_love_cat (赞：1)

一道贪心题？

---

既然可以变牌，那么贪心的思考一下，即可发现答案就只有 $0,1,2$ 这三种可能。

当答案为 $0$ 时，就必须满足牌是同色且数字为一个连或相同。

当答案为 $1$ 时，就必须让两个牌同色且这两个牌数字差距不超过 $2$。

不然的话答案为 $2$。

还整不明白的就自己去代码里看注释吧。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int a,b,c;char A,B,C;
    cin>>a>>A>>b>>B>>c>>C;
    if(A==B&&B==C&&(a+1==b&&b+1==c||a+1==c&&c+1==b||b+1==a&&a+1==c||b+1==c&&c+1==a||c+1==b&&b+1==a||c+1==a&&a+1==b/*合法只有差 1*/||a==b&&b==c/*碰*/))puts("0");//如果已经合法……
    else if(a+2==b&&A==B||b+2==c&&B==C||a+2==c&&A==C||c+2==b&&C==B||b+2==a&&B==A||c+2==a&&C==A/*差 2*/||a+1==b&&A==B||b+1==c&&B==C||a+1==c&&A==C||c+1==b&&C==B||b+1==a&&B==A||c+1==a&&C==A/*差 1*/||a==b&&A==B||b==c&&B==C||a==c&&A==C/*碰*/)puts("1");//如果已有两个符合要求……
    else puts("2");//那就这样吧……
    return 0;
}
```

---

## 作者：cff_0102 (赞：0)

很明显，答案最大为 $2$，即将后面两块换成和第一块一模一样的麻将。

那么可以直接枚举要换几块。

- 要换 $0$ 块，当且仅当这三块完全一致，或者数字连续。如何判断数字连续呢？只要判断它们的差（的绝对值）是否有 $2$ 个是 $1$，有 $1$ 个是 $2$ 即可。
- 要换 $1$ 块，当且仅当这三块中有两块完全一致，或者这三块中有两块种类相同的数字之差（的绝对值）小于等于 $2$。
- 否则就要换两块。

具体实现时，可以用九个变量 $m_0,m_1,m_2,p_0,p_1,p_2,s_0,s_1,s_2$ 分别记录三个种类中两块数字差为 $0,1,2$ 的个数，最后分别对三个种类进行判断。

- 若 $m_0=3$ 或 $p_0=3$ 或 $s_0=3$，则输出 $0$；
- 若 $m_1=2$ 且 $m_2=1$，或 $p_1=2$ 且 $p_2=1$，或 $s_1=2$ 且 $s_2=1$，也输出 $0$；
- 若 $m_0=1$ 或 $p_0=1$ 或 $s_0=1$，则输出 $1$；
- 若 $m_1=1$ 或 $m_2\ge1$，或 $p_1=1$ 或 $p_2\ge1$，或 $s_1=1$ 或 $s_2\ge1$，也输出 $1$（为什么是大于等于？因为有可能出现类似 `m1 m3 m5` 的情况，此时 $m_2=2$）；
- 否则，输出 $2$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t[128][10];
int main(){
	ios::sync_with_stdio(false);
	int a,b,c;char x,y,z;
	cin>>a>>x>>b>>y>>c>>z;
	int m0=0,m1=0,m2=0,p0=0,p1=0,p2=0,s0=0,s1=0,s2=0;//小提醒：在 bits/stdc++.h 中 include 的 cmath 中有函数 j0,j1,jn,y0,y1,yn，所以代码中要避免使用这些变量名 
	if(x==y){
		t[x][abs(a-b)]++;
	}
	if(x==z){
		t[x][abs(a-c)]++;
	}
	if(y==z){
		t[y][abs(b-c)]++;
	}
	m0=t['m'][0];m1=t['m'][1];m2=t['m'][2];p0=t['p'][0];p1=t['p'][1];p2=t['p'][2];s0=t['s'][0];s1=t['s'][1];s2=t['s'][2];
	//赋值完成
	if(m0==3||p0==3||s0==3){
		cout<<0;
		return 0;
	}if((m1==2&&m2==1)||(p1==2&&p2==1)||(s1==2&&s2==1)){
		cout<<0;
		return 0;
	}
	if(m0==1||p0==1||s0==1){
		cout<<1;
		return 0;
	}if((m1==1||m2>=1)||(p1==1||p2>=1)||(s1==1||s2>=1)){
		cout<<1;
		return 0;
	}
	cout<<2;
	return 0;
}
```

---

## 作者：SMall_X_ (赞：0)

[原题传送门](https://www.luogu.com.cn/problem/CF1191B)

---
## 题目大意

$3$ 块麻将，求需要换掉几张牌才能一次出完 $3$ 块麻将。

每块麻将，用一个长度为 $2$ 的字符串给出，字符串由 $(1,9)$ 的一位数字和 $m$、$s$ 或 $p$ 组成。

$3$ 块一模一样的麻将或第 $2$ 位相同，前面是连号的 $3$ 块麻将都可以一次性出完。

## 思路分析

分类讨论所有情况。

首先，为了方便讨论，可以先将 $3$ 块麻将排一下序。先将同花色放一起，再按数字大小从小到大排序。

如果字符串都完全相同或满足同花色且连号，则不用换牌，输出 `0`。

接着讨论那两块麻将可以放在一起，那么换那块不在一起的麻将，输出 `1`，详见代码。

我们可以认为，最多只需要换两块与其中一块麻将一样的麻将便可出完，所以最多只有可能换 $2$ 次。所以，如果不满足以上两种情况，则输出 `2`。

代码：
```cpp
/*Written by smx*/
#include<bits/stdc++.h>
using namespace std;
string a[3];
bool cmp(string a,string b)
{
	if(a[1]!=b[1])
	{
		return a[1]<b[1];
	}
	else
	{
		return a[0]<b[0];
	}
}
int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>a[0]>>a[1]>>a[2];
	sort(a,a+3,cmp);
	if(a[0]==a[1]&&a[1]==a[2]||a[0][1]==a[1][1]&&a[1][1]==a[2][1]&&a[0][0]+1==a[1][0]&&a[1][0]+1==a[2][0])
	{
		cout<<"0";
	}
	else if(a[0][1]==a[1][1]&&a[0][0]+1==a[1][0]||a[1][1]==a[2][1]&&a[1][0]+1==a[2][0])//任意两块连号，换掉不是连号的那块
	{
		cout<<"1";
	}
	else if(a[0][1]==a[1][1]&&a[0][0]+2==a[1][0]||a[1][1]==a[2][1]&&a[1][0]+2==a[2][0])//任意两块的号相差 1，换一块两个号中间的号
	{
		cout<<"1";
	}
	else if(a[0]==a[1]||a[1]==a[2])//任意两块相同，换一块和它们相同的
	{
		cout<<"1";
	}
	else//最劣情况，否则输出 2
	{
		cout<<"2";
	}
	return 0;
}
```

---

## 作者：灵光一闪 (赞：0)

这个其实就是个分类讨论（真的吗？

代码：
```
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<cstdio>

#include<vector>
#include<string>
using namespace std;
string s[3];
int main(){
    for(int i=0;i<3;i++){
        cin>>s[i];
    }
    sort(s,s+3);
    if(s[0]==s[1]&&s[1]==s[2]){//3个相等的
        puts("0");
        return 0;
    }
    if(s[0][0]+1==s[1][0]&&s[1][0]+1==s[2][0]&&s[0][1]==s[1][1]&&s[1][1]==s[2][1]){//顺子
        puts("0");
        return 0;
    }
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(i==j){//两两循环
                continue;
            }
            if(s[i][1]==s[j][1]){
                if(s[i][1]==s[j][1]&&(s[i][0]+1==s[j][0]||s[i][0]+2==s[j][0])){差一个顺子
                    puts("1");//就是1
                    return 0;
                }
                if(s[i]==s[j]){//有两个相等的话就是1
                    puts("1");
                    return 0;
                }
            }
        }
    }
    puts("2");//如果都没有就是2，不可能是3
    return 0;
}
```
The End.

---

## 作者：SunsetVoice (赞：0)

模拟题，但是全是细节。

首先容易想到 $0\le ans\le 2$，因为不可能把 $3$ 个牌全部换掉。

- 当 $ans=0$ 时，则要么是三个牌全部一样，要么类型一样，但出现连号。

- 当 $ans=1$ 时，要么是有两个一样的牌，要么是有两个**类型一样，数字绝对值小于 $2$ 的牌。**

- 否则，$ans=2$。

采取了开桶存储的方式记录三张牌的数字，比暴力枚举好多了。

时间复杂度 $O(1)$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct mojang{
	int num;char type;
}a,b,c;
bool lian(){
	bool u[10] = {0};
	u[a.num]++;
	u[b.num]++;
	u[c.num]++;
	for(int i = 0;i<=7;i++){
		if(u[i]==1 and u[i+1]==1 and u[i+2]==1)return true;
	}
	return false;
}
bool type(mojang x,mojang y){
	return x.type==y.type;
}
bool num(mojang x,mojang y){
	return x.num==y.num;
}
bool is(mojang x,mojang y){
	return x.num==y.num and x.type==y.type;
}
signed main(){
	cin>>a.num>>a.type>>b.num>>b.type>>c.num>>c.type;
	if(a.num==b.num and c.num==b.num and a.type==b.type and c.type==b.type)cout<<0<<endl;
	else if(a.type==b.type and c.type==b.type and lian())cout<<0<<endl;
	else if((type(a,b) and abs(a.num-b.num)<=2) or (type(b,c) and abs(b.num-c.num)<=2) or (type(a,c) and abs(a.num-c.num)<=2))cout<<1<<endl;
	else if(is(a,b) or is(b,c) or is(a,c))cout<<1<<endl;
	else cout<<2<<endl;
	return 0;
}
```


---

