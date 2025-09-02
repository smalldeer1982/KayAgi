# Plate Game

## 题目描述

You've got a rectangular table with length $ a $ and width $ b $ and the infinite number of plates of radius $ r $ . Two players play the following game: they take turns to put the plates on the table so that the plates don't lie on each other (but they can touch each other), and so that any point on any plate is located within the table's border. During the game one cannot move the plates that already lie on the table. The player who cannot make another move loses. Determine which player wins, the one who moves first or the one who moves second, provided that both players play optimally well.

## 说明/提示

In the first sample the table has place for only one plate. The first player puts a plate on the table, the second player can't do that and loses.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF197A/616ddb445b80df1d3e6e847cff2f0e32d4fd3dd4.png)In the second sample the table is so small that it doesn't have enough place even for one plate. So the first player loses without making a single move.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF197A/c6393d7d89b7426c75efde7ce23de7dae72901f3.png)

## 样例 #1

### 输入

```
5 5 2
```

### 输出

```
First
```

## 样例 #2

### 输入

```
6 7 4
```

### 输出

```
Second
```

# 题解

## 作者：Anyonion (赞：7)

**很水**的一道**蓝题**，简单分析一下就可以解决  

先手放在**正中心**，之后放在与后手位置**中心对称**的位置，这样就不会**在后手之前**悬空

但是如果**第一次**就悬空呢 ? ( 即盘子比桌子大 )  
所以要加**特判**！！！

 _**code**~_ 
 ```cpp
#include<bits/stdc++.h>
using namespace std;
int a/*长*/,b/*宽*/,c/*半径*/;
int main()
{
    cin>>a>>b>>c;
    c*=2;//半径*2=直径 
    if(a>=c&&b>=c) cout<<"First"<<endl;//盘子比桌子小
    else cout<<"Second"<<endl;//盘子比桌子大
    return 0;
}
```
题解部分落幕

大佬们发的题解都提到了“博弈论”，于是本蒟蒻就去查了一下  
博弈论不是一种算法，是现代数学的一个新分支，也是运筹学的一个重要学科，有兴趣的可以了解一下：[博弈论-百度百科](https://baike.baidu.com/item/%E5%8D%9A%E5%BC%88%E8%AE%BA/81545?fr=aladdin)  
博弈论在我们生活中经常用到，就连小学的奥数题里都有  
不用专门去学它，这主要考验的是逻辑分析能力

## 完美落幕~~~

---

## 作者：梨衣 (赞：7)

## 博弈论入门题
一般此题型一定存在某个条件，可以判断先手是否必胜。此题是二维平面，可以先简化成宽为一个圆盘直径长度的矩形推条件。

首先思考，两人轮流落子，设矩形长度为 $a$ ，若不考虑最优取胜方案，两人从起始位置开始，则可分为两种情况

### **$a$ 最多有直径的偶数倍。此时后手落子后矩形无剩余位置**
### **$a$ 最多有直径的奇数倍。此时先手落子后矩形无剩余位置**
考虑先手获胜方案，继续分析情况一。若先手在中间位置落子，则两边位置被隔开，原本可再落下的圆盘自然便没有位置了。

**综上所述，只要先手能够落子，则先手必胜，代码便很简单了。**
## 代码如下
```cpp
#include<cstdio>
using namespace std;
int main(){
	int a,b,r;
	scanf("%d%d%d",&a,&b,&r);
	if(a<r*2||b<r*2)printf("Second");
	else printf("First");
	return 0;
}
```
## 谢谢观赏


---

## 作者：mzyc_jx (赞：2)

[Plate Game](https://www.luogu.com.cn/problem/CF197A)

~~又是一道适合蒟蒻的大水题~~

### 思想：博弈论

只要放得下一个盘子，先手就可以放在桌子正中心，然后放在与后手放的位置相对称的位置，就一定能赢。所以只需要判断能否放盘子就行了。

### CODE：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int a,b,r;
    cin>>a>>b>>r;
	 if(a<r*2||b<r*2)//判断是否放得下
    cout<<"Second";
    else 
    cout<<"First";
}
```

---

## 作者：mzyc_pzx (赞：2)

先手必胜策略：
假设放的下一个盘子，先手就可以先放在盘子正中心，后面就可以放在与后手位置对称的位置。
```
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int x,y,z;
    cin>>x>>y>>z;
    z*=2;
    if(x>=z&&y>=z)
	cout<<"First";
    else
	cout<<"Second";
}
```


---

## 作者：王炸拆开打 (赞：1)

看了前面几位大佬的解答，发现思路清晰了不少，但是我这个蒟蒻好像还是没有领悟到博弈论的精髓，感觉和在做**博弈论+递归分治**一样

------------
# 核心思想：博弈论

其实我们可以将这个问题不断缩小（就像汉诺塔的递归一样）

当我们缩小到面积只够放下一个盘子时，就会发现，**谁先下谁赢**（$Frist$），除非**从一开始就根本放不下**（$Second$）

那我们开始将缩小的问题整合（开始回溯），发现只要先手能下且下在中间，他就~~随随便便~~赢了

![](https://cdn.luogu.com.cn/upload/image_hosting/lkpp1i40.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

**其实随便划出一个矩形，都是一种子问题**（手模一下试试也可以）

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
inline int read(){//上个题遗留下来的祖传快读
	register int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
	while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}
int main(){
    int a=read(),b=read(),c=read();
    c*=2;//我第一遍提交直接忘了，放出代码也是为了这个 
    if(a>=c&&b>=c) printf("First");
    else printf("Second");
    return 0;
}
```


---

## 作者：_JX_ (赞：0)

[CF197A Plate Game](https://www.luogu.com.cn/problem/CF197A)

这道题是一道简单的博弈论。

博弈论的题,一般都是后手赢，但这题竟然是先手赢。

### 思路：
若放得下一个盘子，先手就可以放在正中心，后面就可以放在后手位置对称的位置，就一定能赢。但是，还要判断能否**放得下一个**。

### CODE:
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int a,b,r;
    cin>>a>>b>>r;
	if(a<r*2||b<r*2)
    cout<<"Second";
    else 
    cout<<"First";
    return 0;
}
```

---

## 作者：NATO (赞：0)

首先，若盘子已经比桌子小了，那么先手先放在正中间，之后再与后手对称着放，就可以保证先手一定有放的地方，所以先手一定赢。

但是，若盘子已经比桌子大了，那先手一来就没地方放了，那后手就赢了。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a,b,c;
int main()
{
    ios::sync_with_stdio(0);
   cin>>a>>b>>c;
   c*=2;
   if(a>=c&&b>=c) 
        cout<<"First"<<endl;
   else 
        cout<<"Second"<<endl;
   return 0;
}
```



---

## 作者：MatrixCascade (赞：0)

非常水的一眼题

若放的下一个盘子，先手就可以先放在正中心，后面就可以放在关于后手位置中心对称的位置，就必胜。

所以只要判断是否放的下一个就可以了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int a,b,c;
    cin>>a>>b>>c;
    c*=2;
    if(a>=c&&b>=c) puts("First");
    else puts("Second");
}
```


---

## 作者：Ryan_ (赞：0)

一道简单的博弈论~~codeforcesA题经常遇到~~

代码实现及思路都非常简单~~记得是一道小学奥数题qwq~~

我们的策略是若先手（First）刚开始可以合法放置即win

每次First都放在桌子的最中间，那么Second只有两个选择——不放或放在First的左右两边，无论Second放在哪一边First都可以放置在其对称的那一边，直到Second不能再放置了，即First win

AC Code：

```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
inline int read(){
	char c=getchar();
	int x=0,f=1;
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=x*10+c-'0';
		c=getchar();
	}
	return x*f;
}
int a,b,r;
int main(){
	a=read();
	b=read();
	r=read();
	if(2*r<=a&&2*r<=b)cout<<"First"<<endl,exit(0);
	else return cout<<"Second"<<endl,0;
}

```


---

## 作者：恨穹不是妹 (赞：0)

这道题实际上并不难，难只是难在论证过程罢了。

题目这样描述，实际上就给了我们一种方向，典型的博弈论嘛。

而博弈论的题,一般都是后手赢的哦。

但可惜这题是先手赢

所以我们来论证一下；

例如此图

![](https://cdn.luogu.com.cn/upload/pic/46168.png)

假设盘子**直径**是1然后，先手可以这么放

![](https://cdn.luogu.com.cn/upload/pic/46169.png)

哈哈哈，后手没得放了吧。
那如果是长为三的长方形呢？

先手可以放中间啊
![](https://cdn.luogu.com.cn/upload/pic/46170.png)
那么后手只能选择前面和后面其中一个放了，放完后先手还可以再放最后一个位置，后手就输了。

我们继续推广

![](https://cdn.luogu.com.cn/upload/pic/46171.png)
把四的情况分解成和三的情况一样。

emm，五个的
![](https://cdn.luogu.com.cn/upload/pic/46172.png)
接下来轮到后手摆盘了

已知后手如果摆右边的三个盘一定把它挤满，然后先手还可以在左边再放一个，后手输。

若后手摆了左边，先手就可以把右边挤满，后手输。

你也可以继续推广，由于有点麻烦，我就不推广了。

只有一种方法可以让先手输。就是一个都摆不下。。。

但是如果是图呢？也是一样道理嘛，你就可以理解成是n行的表嘛
时间有限，不再推广啦

好了，上代码，十分简单

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n,a,b,c;
        cin>>a>>b>>c;
        if(a<c*2||b<c*2)
        cout<<"Second"<<endl;
        else 
        cout<<"First"<<endl;
}
```

---

