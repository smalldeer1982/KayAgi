# Vasya and Robot

## 题目描述

Vasya has got a robot which is situated on an infinite Cartesian plane, initially in the cell $ (0, 0) $ . Robot can perform the following four kinds of operations:

- U — move from $ (x, y) $ to $ (x, y + 1) $ ;
- D — move from $ (x, y) $ to $ (x, y - 1) $ ;
- L — move from $ (x, y) $ to $ (x - 1, y) $ ;
- R — move from $ (x, y) $ to $ (x + 1, y) $ .

Vasya also has got a sequence of $ n $ operations. Vasya wants to modify this sequence so after performing it the robot will end up in $ (x, y) $ .

Vasya wants to change the sequence so the length of changed subsegment is minimum possible. This length can be calculated as follows: $ maxID - minID + 1 $ , where $ maxID $ is the maximum index of a changed operation, and $ minID $ is the minimum index of a changed operation. For example, if Vasya changes RRRRRRR to RLRRLRL, then the operations with indices $ 2 $ , $ 5 $ and $ 7 $ are changed, so the length of changed subsegment is $ 7 - 2 + 1 = 6 $ . Another example: if Vasya changes DDDD to DDRD, then the length of changed subsegment is $ 1 $ .

If there are no changes, then the length of changed subsegment is $ 0 $ . Changing an operation means replacing it with some operation (possibly the same); Vasya can't insert new operations into the sequence or remove them.

Help Vasya! Tell him the minimum length of subsegment that he needs to change so that the robot will go from $ (0, 0) $ to $ (x, y) $ , or tell him that it's impossible.

## 说明/提示

In the first example the sequence can be changed to LULUU. So the length of the changed subsegment is $ 3 - 1 + 1 = 3 $ .

In the second example the given sequence already leads the robot to $ (x, y) $ , so the length of the changed subsegment is $ 0 $ .

In the third example the robot can't end his path in the cell $ (x, y) $ .

## 样例 #1

### 输入

```
5
RURUU
-2 3
```

### 输出

```
3
```

## 样例 #2

### 输入

```
4
RULR
1 1
```

### 输出

```
0
```

## 样例 #3

### 输入

```
3
UUU
100 100
```

### 输出

```
-1
```

# 题解

## 作者：yeshubo_qwq (赞：9)

## 题意
给你机器人的操作序列及终点。要求修改这个序列使机器人最终移动到终点。其修改的花费为**修改的操作的下标的最大值减修改的操作的下标的最小值加一。如果没有修改，则花费为 $0$。** 问：最小化的花费是多少，**如果最后不能够移动到终点，输出 $-1$。**
## 思路：二分答案+前缀和
若修改花费为 $l$ 可行，则修改花费大于 $l$ 一定可以实现。因为修改花费大于 $l$ 只要包含**可行的**修改花费为 $l$ 的区间就行了。因此，本题具有**单调性**，可以二分答案。

于是，我们可以直接套上二分模板。
```cpp
	l=0;r=n; 
	ans=-1;//初始化默认无法到达 
	while(l<=r){
		mid=(l+r)>>1;
		if(check(mid))r=mid-1,ans=mid;
		else l=mid+1;
	}
	cout<<ans;
```
**二分的判断**：判断修改花费为 $l$：枚举修改的长度为 $l$ 的区间的头、尾，然后求出除去这段区间会移动到的位置，然后判断加上任意的 $l$ 次操作，能否到达终点。

可以到达终点的情况：

第一种：可修改的操作数等于差的步数可以。

第二种：可修改的操作数如果有多且是偶数也可以（因为多余操作数走出去还得走回来，所以必须是偶数）。

**但是，如何求出除去某段区间会移动到的位置？**

每次都直接模拟显然会超时，因此，我们可以用前缀和进行预处理，将每次求出除去某段区间会移动到的位置的时间复杂度降到 $O\left(1\right)$。
```cpp
	for(i=1;i<=n;i++){//预处理前缀和，x数组为行，y数组为列
		x[i]=x[i-1];y[i]=y[i-1];
		switch(s[i]){
			case 'U':y[i]++;break;
			case 'D':y[i]--;break;
			case 'L':x[i]--;break;
			case 'R':x[i]++;break;
		}
	}
```
于是，我们就可以愉快打出二分的判断了。
```cpp
bool check(int l){
	int i,j,n2,m2,p;
	for(i=1,j=i+l-1;j<=n;i++,j++){
		n2=x[n]-x[j]+x[i-1];//行的位置 
		m2=y[n]-y[j]+y[i-1];//列的位置
		p=abs(n1-n2)+abs(m1-m2);//还差几步 
		if(l==p)return true; 
		else if(l>p&&(l-p)%2==0)return true;
	}
	return false;
}
```
## The End.

---

## 作者：JMercury (赞：5)

一个机器人从$(0,0)$出发，L,R,U,D表示其移动方向。你可以将移动指令中的一个子段任意修改使他到$(x,y)$。问这个子段长度最小是多少（如果无论如何都无法到达，输出0）

如果修改某个长度为len的子段可以满足题意，那么一定存在长度大于len的子段满足题意，故答案是满足单调性的。而这里求最小，故可以考虑二分答案。但是怎么判断可行性呢？

如果我们枚举出长度为$len$的所有子段，其中有一个可以满足条件，那么x就是可行的。那么又怎么判断一个子段是满足的呢？

注意到我们可以任意修改这个子段，而它的前后指令仍是固定的。我们可以先计算出它的前后指令对机器人位置的影响，然后考虑加上这个子段后能否走到终点。如果，子段长度为$len$，通过前后指令机器人到达$(x_1,y_1)$，最终目标为$(x,y)$，那么当

$$len>=abs(x-x_1)+abs(y-y_1)$$

且

$$2\ |\ len-abs(x-x_1)-abs(y-y_1)$$

时，机器人可以到达。

复杂度$O(n\ logn)$

附上AC代码

```cpp
#include<bits/stdc++.h>
const int maxn=200010;
using namespace std;

int n,x,y;
string step;
int frty[maxn],frtx[maxn];
int l,r,mid,ans=-1;

bool check(int len)
{
    for(int l=1,r=len;r<=n;l++,r++)
    {
        int nx=frtx[n]-(frtx[r]-frtx[l-1]);
        int ny=frty[n]-(frty[r]-frty[l-1]);
        if(len>=abs(x-nx)+abs(y-ny) && (len-abs(x-nx)-abs(y-ny))%2==0) return true;
    }
    return false;
}

int main()
{
    scanf("%d",&n);
    cin>>step;
    scanf("%d%d",&x,&y);
    for(int i=1;i<=n;i++)
    {
        frty[i]=frty[i-1];frtx[i]=frtx[i-1];
        if(step[i-1]=='U') frty[i]++;
        if(step[i-1]=='D') frty[i]--;
        if(step[i-1]=='R') frtx[i]++;
        if(step[i-1]=='L') frtx[i]--;
    }
    l=0,r=n;
    while(r>=l)
    {
        mid=(l+r)>>1;
        if(check(mid)) r=mid-1,ans=mid;
        else l=mid+1;
    }
    printf("%d",ans);
    return 0;
}
```

~~考试竟然没做出来呜呜呜呜~~

---

## 作者：Zechariah (赞：4)

nlogn的二分  
二分修改的序列的长度，判断一下是否能满足条件就行了  
几个需要注意的地方：  
1) 二分的边界l=0,r=n  
2) 如果在x轴方向或者y轴方向走的步数比需要的坐标撅对值要大，多出来的部分一定要是偶数，因为走到别的地方去以后还要走回来  
3) 用前缀和维护不含修改的序列走到的坐标  
非常好写，看代码
```cpp
#include <bits/stdc++.h>
const int N = 200010;
using namespace std;
inline long long read()
{
	register long long num = 0;
	register char ch;
	register bool flag = false;
	while ((ch = getchar()) == ' ' || ch == '\n' || ch == '\r');
	if (ch == '-')flag = true; else num = ch ^ 48;
	while ((ch = getchar()) != ' '&&ch != '\n'&&ch != '\r'&&~ch)
		num = num * 10 + (ch ^ 48);
	if (flag)return -num; return num;
}
char s[N];
int px[N], py[N],n,x,y;
inline bool judge(register int mid)
{
	for (register int l = 1, r = mid; r <= n; ++l, ++r)
	{
		register int fx = px[n] - (px[r] - px[l - 1]);
		register int fy = py[n] - (py[r] - py[l - 1]);
		if (abs(x - fx) + abs(y - fy) <= mid && !(abs(x + y + fx + fy + mid) & 1))return true;
	}
	return false;
}

int main()
{
	n = read();
	scanf("%s", s + 1);
	x = read(), y = read();
	for (register int i = 1; i <= n; ++i)
	{
		px[i] = px[i - 1];
		py[i] = py[i - 1];
		if (s[i] == 'U')++py[i];
		else if (s[i] == 'D')--py[i];
		else if (s[i] == 'L')--px[i];
		else if (s[i] == 'R')++px[i];
	}
	register int l = 0, r = n, ans = -1;
	while (l <= r)
	{
		register int mid = l + r >> 1;
		if (judge(mid))r = mid - 1, ans = mid;
		else l = mid + 1;
	}
	cout << ans;
	return 0;
}
```

---

## 作者：Chupeiz (赞：3)

[【题目传送门】](https://www.luogu.org/problemnew/show/CF1073C)

标签：二分

**分析题目**，首先思考一个问题：这里修改的代价是什么？看到$max-min+1$感到有些熟悉，很像我们已知区间右端点和左端点后求区间长度的式子。实际上正是这样的，考虑到修改代价仅仅取决于你修改的点的最大下标与最小下标，那么是不是说：在这两个操作之间修改任何操作都是免费的？所以我只需要考虑修改某一个区间就可以了（区间内可以存在不改变的点）。

那这样的话我们就将“修改哪些操作让代价最小”转化成了“修改一个区间且要让区间尽量小”，似乎更容易做了。

**特殊情况**：接着我们考虑另一个问题，什么情况下无解。

显然有一种情况一定无解。既然每一个操作只能移动一个单位长度，那么n个操作最多能让小机器人移动n个单位长度，对不对？（也就是小机器人不往回走）所以说，如果我需要的位移 _（这里指曼哈顿距离，之后出现“位移”与这里同义）_ $dis(x,y)$大于了总操作次数，那么肯定无解。

还有一种情况，就是我操作次数的奇偶性必须和位移的奇偶性一致。因为移动奇数次不可能移动到偶数点上，移动偶数次同理。注意，这里的“奇偶性”指的同样是曼哈顿距离，而不是x坐标或y坐标。

**check函数**：如何判断修改一个区间是不是满足条件？![我画画真好看啊](https://cdn.luogu.com.cn/upload/pic/40708.png)

我们可以设灰色区域以外的x方向的位移（注：这里的位移是有方向的，也就是有正负性的）是△$x$，$y$方向的位移是△$y$，那么我距离目标点$(x,y)$在x方向还需要$abs(x-$△$x)$的位移，$y$方向还需要$abs(y-$△$y)$的位移，总共需要$abs(x-$△$x)+abs(y-$△$y)$的位移，如果我当前的修改区间长度（最大修改次数）不小于我还需要的位移，就说明这种修改方案是成立的。

可以看下这部分的代码：

```cpp
bool check(int sta,int len){
//sta表示区间左端点，len表示长度
    int xx=sumx[sta-1]+sumx[n]-sumx[sta+len-1]; 
    //设前区间（0~sta-1）的x和后区间的（sta+len-1~n)x之和为△x 
    int yy=sumy[sta-1]+sumy[n]-sumy[sta+len-1];//同上 
    int c=abs(xx-x)+abs(yy-y);//还需要的移动距离
    if(len>=c)return 1; 
    return 0;
}
```

**代码实现**：最朴素的想法是直接枚举区间的左端点和右端点，每次检查这样的区间修改后能不能到达终点，检查的时候需要再挨个计算区间内位移，计算时遍历整个区间，所以这样做的时间复杂度是$O(n^3)$

当然有一个比较常用的优化是前缀和。我们把初始操作指令看成x方向和y方向的+1/-1，就可以预处理出前缀和，实现$O(1)$区间查询时间复杂度。于是时间复杂度被优化为$O(n^2)$

这样好像还是过不了，怎么办呢。答曰二分。

这个优化~~最强~~有点难想到，主要是因为二分需要满足单调性，而这道题的单调性有点抽象。

因为，我修改次数多了以后，能进行的位移也就多了，那么我比起修改次数少的位移肯定更容易到终点。换句话说，如果修改次数多的到不了，那么修改次数少的肯定到不了；而如果我修改次数少的能到终点，那么修改次数多的必定能到终点（大不了让其中某些操作不变）。从这个层面讲，我们以能不能到达终点作为目的：

**更长的区间一定优于更短的区间**。

在这一结论的基础上就可以二分区间长度，找到最短的满足条件的区间长度。再具体地说，如果当前长度满足条件，那么我找更短的，如果不满足条件，那么我找更长的。这样就把内层循环时间复杂度降到了$O(logn)$。可以AC了。

最后提醒一下，如果把枚举左端点放在二分外面，需要在所有可能答案（mid）中取最小值。

**附上代码**

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

char s[500005];
int x,y,n,sumx[500005],sumy[500005];
int l,r,mid,dis,ans=2147483647;

bool check(int sta,int len){//如图示，需要满足条件：
    int xx=sumx[sta-1]+sumx[n]-sumx[sta+len-1]; //设前区间的x和后区间的x之和为△x 
    int yy=sumy[sta-1]+sumy[n]-sumy[sta+len-1]; //设前区间的y与后区间的y之和为△y
    int c=abs(xx-x)+abs(yy-y);
    if(len>=c&&c%2==len%2)return 1; 
    return 0;
}

int main() {
    scanf("%d",&n);
    getchar();
    for (int i=1;i<=n;i++){
        s[i]=getchar();
        sumx[i]=sumx[i-1];
        sumy[i]=sumy[i-1];//之前前缀和写错了orz 
        if(s[i]=='U')sumy[i]=sumy[i-1]+1;
        if(s[i]=='D')sumy[i]=sumy[i-1]-1;
        if(s[i]=='R')sumx[i]=sumx[i-1]+1;
        if(s[i]=='L')sumx[i]=sumx[i-1]-1;             //前缀和优化，减小求区间内x、y的时间复杂度 O(n)->O(1) 
    }
    scanf("%d%d",&x,&y);
    dis=abs(x)+abs(y);
    if (n<dis){//特判：1.整个字符串操作次数总和小于至少需要的操作次数（曼哈顿距离/每次操作的单位长度） 
        printf("-1\n"); //2.操作次数的奇偶性和“能到达终点”的操作次数的奇偶性不同 
        return 0;
    }
    for (int i=1;i<=n;i++){//O(nlogn) 
        l=0,r=n-i+1;
        while(l<=r){//更长序列一定更优（操作次数多，比更短的更容易到达终点），不会更劣（大不了我序列中的某个字母不动就是了） 
            mid=(l+r)>>1;
            if (check(i,mid)){
            r=mid-1;ans=min(ans,mid);}//二分长度，这个长度太短那就向更长的挪一挪 
            else l=mid+1;//够长那我就找还有没有更短的 
        }
    }
    if(ans==2147483647)ans=-1;
    printf("%d",ans);
    return 0;
}
```

---

## 作者：NotNaLocker (赞：2)

## CF1073C Vasya and Robot 题解
### ~~几~~句闲话

顶楼的 dalao 解释得好！~~但是本蒟蒻蒙了~~。

### 主要思路

**前缀和+二分+枚举**

### 具体实现

我们先创一个样例。

![](https://cdn.luogu.com.cn/upload/image_hosting/ghopcio5.png)


黑色是机器人初始位置，即 $(0,0)$，灰色是机器人走的路线，红色是目标点。

现在要修改路线达到红点，怎么办呢？首先要便捷地存储路线。**前缀和**刚好可以实现。

```cpp
void init(){
	for(int i=1;i<=n;i++){
		qzhx[i]=qzhx[i-1],qzhy[i]=qzhy[i-1];  //继承
		switch(s[i]){  //判断
			case 'U': qzhy[i]++;break;
			case 'D': qzhy[i]--;break;
			case 'L': qzhx[i]--;break;
			case 'R': qzhx[i]++;break;
		}
	}
}
```

接下来我们要考虑修改路线的**长度**。设 $l$ 为起点，$r$ 为终点。
通过看图可以知道，我们需要修改的是绿色框起来的这一段：

![](https://cdn.luogu.com.cn/upload/image_hosting/ziciimvt.png)

但这一段已经用前缀和存储了，该如何选出这一段呢？

![](https://cdn.luogu.com.cn/upload/image_hosting/486150cn.png)

先用总长度减去红色的一段，也就是 `x[n]-x[r]`。这时 `x[l-1]` 也一并删除，但我们并不想这么做。于是加上 `x[l-1]`，就可以了。

接下来，求距离、判断是否能到达，就都不难了。

```cpp
bool revise(int stp){
	if(strlen(s)>max(qzhx[n],qzhy[n])) return 0;  //特判目标点距离超过。
	int nowx,nowy,f;
	for(int i=1,j=i+stp-1;j<=n;i++,j++){
		nowx=qzhx[n]-qzhx[j]+qzhx[i-1];
		nowy=qzhy[n]-qzhy[j]+qzhy[i-1];
		f=abs(x-nowx)+abs(y-nowy);  //求距离
		if(f==stp) return 1; 
		if(stp>f&&(stp-f)%2==0) return 1;  //如果花费大于且为偶数（可返回），楼上讲的很详细了。
	}
	return 0;
}
```

## AC Coding

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,x,y,ans=-1;
int qzhx[100005],qzhy[100005];
char s[100005];
void init(){
	for(int i=1;i<=n;i++){
		qzhx[i]=qzhx[i-1],qzhy[i]=qzhy[i-1];
		switch(s[i]){
			case 'U': qzhy[i]++;break;
			case 'D': qzhy[i]--;break;
			case 'L': qzhx[i]--;break;
			case 'R': qzhx[i]++;break;
		}
	}
}
bool revise(int stp){
	if(strlen(s)>max(qzhx[n],qzhy[n])) return 0;
	int nowx,nowy,f;
	for(int i=1,j=i+stp-1;j<=n;i++,j++){
		nowx=qzhx[n]-qzhx[j]+qzhx[i-1];
		nowy=qzhy[n]-qzhy[j]+qzhy[i-1];
		f=abs(x-nowx)+abs(y-nowy);
		if(f==stp) return 1; 
		if(stp>f&&(stp-f)%2==0) return 1;
	}
	return 0;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>s[i];
	cin>>x>>y;
	init();
	int l=0,r=n;
	while(l<=r){  //二分模板
		int mid=(l+r)>>1;
		if(revise(mid)) r=mid-1,ans=mid;
		else l=mid+1;
	}
	cout<<ans;
	return 0;
}
```

## Thanks for watching.

---

## 作者：eb0ycn (赞：1)

# [CF1073C](https://codeforces.com/problemset/problem/1073/C)题解

## 简化题意

已知一字符串 $s$ 长度为 $n$，且 $s$ 中各字符代表的意义如下。

------------

- $U$ 向上走一步；
- $D$ 向下走一步；
- $L$ 向左走一步；
- $R$ 向右走一步；

------------

现在你在平面直角坐标系的原点，你需要改变字符串 $s$ 中的某个**子串**中的字符，使得最后能到 $(x,y)$ 位置。求这个子串的最小长度。

------------

## 思路

### 二分

------------

首先，二分的要求：有界性、单调性、二段性。

本题中，我们设答案为 $l$**（固定）**，则所有大于 $l$ 的答案都可行，也就是说一定可以通过改变长度大于 $l$ 的子串以到达目标点（比如你可以让多余的子串里选一些 $R$ 改成 $L$，相同数量的 $L$ 改成 $R$，相当于没改……）。

显然，本题满足二分的条件。

![图1 二分的单调性](https://cdn.luogu.com.cn/upload/image_hosting/igswtmgi.png)

由于题解里面有很多二分的做法，所以在这里我就稍微带一下，代码就不传了。

时间复杂度 $O(n\log{n})$。

------------

### 尺取

尺取的概念、模板题等详见[【洛谷日报#73】尺取法小结](https://www.luogu.com.cn/blog/Nero-Yuzurizaki/chi-qu-fa-xiao-jie)。	

这里我先简单说一下尺取的基本内容。

------------

#### 尺取的要求

- 取的是一段连续的区间（有两个端点）；

- 结果不会因区间的变长而由成立变成不成立；

- 左端点右移，右端点不会往左移。

要求一是本题的条件，要求二前面已经证明过。所以本题满足尺取的条件。

------------

#### 方法

1. 按照题意，算出实际上最后到达的位置，并设答案为 $n + 1$；

1. 特判不用改动就能到的情况；

1. 设左端点为 $l$，右端点为 $r$，并赋初始值 $1$；

1. 从左到右枚举每个右端点，被枚举到的点取消 $s_r$ 的对应操作。如果**区间长度**大于等于**当前位置与目标点的[曼哈顿距离](https://baike.baidu.com/item/%E6%9B%BC%E5%93%88%E9%A1%BF%E8%B7%9D%E7%A6%BB/743092)**，就右移左端点；

1. 对于每次右移左端点，如果**当前区间长度**和**两点的曼哈顿距离**同奇同偶，更新答案；

1. **“回溯”**，更新答案后，恢复 $s_l$ 的操作；

1. 若答案为 $n + 1$，说明无解。

------------

#### 证明

为什么判断是否右移左端点只要看曼哈顿距离：类比一下“撤回”操作。取消 $s_r$ 的操作后，可以修改成向任意方向走一步，此时相当于从 $l - 1$ 位置开始，看走 $r - l + 1$ 步能否到达目标点。设曼哈顿距离为 $p$，则：

- 当 $p = r - l + 1$ 时，正好能走到目标点；

- 当 $p \leq r - l + 1$ 且 $p \equiv r - l + 1 \pmod 2$ 时，可以通过“一上一下，一左一右”走到目标点。


![图2 满足题目要求的条件](https://cdn.luogu.com.cn/upload/image_hosting/xb75ccda.png)

我们发现，有用的步数就是曼哈顿距离 $p$。多往某个方向走一步，就得多往相反的方向走一步，所以多余的步数**一定**是偶数。由于任何一个整数加偶数，奇偶性不变，所以当且仅当曼哈顿距离 $p$ 和区间长度 $r - l + 1$ 同奇同偶时，修改后可以到达目标点。

时间复杂度 $O(n)$。

## 上代码！


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
char s[N];
int main()
{
    int sx=0,sy=0;
    int n;
    scanf("%d",&n);
    scanf("%s",s+1);
    int fx,fy;
    scanf("%d%d",&fx,&fy);
    for(int i=1;i<=n;i++)
    {
        if(s[i]=='U')
            ++sy;
        else if(s[i]=='D')
            --sy;
        else if(s[i]=='L')
            --sx;
        else
            ++sx;//计算最终位置 。 
    }
    if(sx==fx&&sy==fy)
        return 0*printf("0\n");//特判不用修改的情况 。 
    int l=1,minn=n+1;
    for(int r=1;r<=n;++r)
    {
        if(s[r]=='U')
            --sy;
        else if(s[r]=='D')
            ++sy;
        else if(s[r]=='L')
            ++sx;
        else
            --sx;//枚举右端点，取消s[r]操作 。 
        while(l<=r&&abs(fx-sx)+abs(fy-sy)<=r-l+1)
        {
            if(((abs(fx-sx)+abs(fy-sy)))%2==(r-l+1)%2)
                minn=min(minn,r-l+1);
            if(s[l]=='U')
                ++sy;
            else if(s[l]=='D')
                --sy;
            else if(s[l]=='L')
                --sx;
            else
                ++sx;//枚举左端点，恢复s[l]操作。
            ++l;
        }
    }
    printf("%d\n",minn==n+1?-1:minn);
    return 0;
}
//陈文忻　2023-10-22。 
//诚信做题，拒绝ctrl C+ctrl V。 
```

------------

[AC 啦！](https://www.luogu.com.cn/record/130574376)

讲得不是很详细，自己意会吧。

---

## 作者：CYZZ (赞：1)

# [Vasya and Robot](https://www.luogu.com.cn/problem/CF1073C)
本题是一道二分答案的好题。
# 题意简明
给出机器人的 $n$ 个移动操作和目标位置。求出修改的操作中下标最大与最小的差的最小值。
# 思路分析
我们发现本题的花费 $maxID-minID+1$ 是求**区间长度**的公式，所以我们只需要使修改区间的长度尽量小。

而对于长度为 $len$ 的修改区间，长度大于 $len$ 的修改都可行，只需包含长度为 $len$ 的可行区间。因此，答案满足**单调性**，可以**二分答案**。

如何判断修改长度为 $len$ 的区间可不可行呢？遍历每个长度为 $len$ 的子序列，若有一个可行，则 $len$ 是可行的。

我们注意到，修改其中一个区间的值并不影响其它区间的值。所以，我们可以先处理出其它区间的值。则走到目标位置的最小花费是：
$$|nx-x|+|ny-y|$$
又因为最多修改 $len$ 次，所以该区间可行当且仅当：
$$len\ge|nx-x|+|ny-y|$$
且
$$len-|nx-x|-|ny-y|\equiv 0 \pmod 2$$
另外，如果每次都模拟求一次区间的值，复杂度会很高。所以，可以利用前缀和预处理出每个区间的值，这样就可以做到 $O(1)$ 查询了。

剩下的都代码见吧。
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,tx,ty,sum[200005][2];
char s[200005];
bool flag;
bool check(int x)
{
	int l=1,r=x;
	while(r<=n)
	{
		int nx=sum[n][0]-sum[r][0]+sum[l-1][0];//求出除修改区间以外的区间值 
		int ny=sum[n][1]-sum[r][1]+sum[l-1][1];
		int step=abs(nx-tx)+abs(ny-ty);
		if(x>=step&&!((x-step)&1))
			return 1;
		l++;r++;
	}
	return 0;
}
int main()
{
	scanf("%d%s",&n,s+1);
	for(int i=1;i<=n;i++)
	{
		sum[i][0]=sum[i-1][0];//前缀和 
		sum[i][1]=sum[i-1][1];
		if(s[i]=='U')
			sum[i][1]++;
        if(s[i]=='D')
			sum[i][1]--;
        if(s[i]=='R')
			sum[i][0]++;
        if(s[i]=='L')
			sum[i][0]--; 
	}
	scanf("%d%d",&tx,&ty);
	int l=0,r=n;
	while(l<=r)//二分 
    {
        int mid=(l+r)>>1;
        if(check(mid))
        {
        	r=mid-1;
        	flag=1;//flag判断是否有解 
		}
        else 
			l=mid+1;
    }
	printf("%d",flag?l:-1);
}
```
希望本篇题解可以帮到大家！！！

---

## 作者：Light_Star_RPmax_AFO (赞：0)

# 思路——前缀和 + 二分 + 枚举

## 1.前缀和

使用 **前缀和** 记录原来每秒所在的位置，这样就可以知道在每个区间机器人所走的 $x$ 轴与 $y$ 轴的长度。

## 2.枚举

**枚举** 每一个长度为需要修改序列长度 $len$ 的序列，这时我们就使用前缀和来求出去除这一段之后我们所走 $x$ 轴与 $y$ 轴的长度，详情如下：

首先我们选择一个需要去除的 **序列的左端点** $l$ 和 **右端点** $r$。

肯定是想要取出这一部分的。

![](https://cdn.luogu.com.cn/upload/image_hosting/gzc3rin6.png)

怎么实现呢？

![](https://cdn.luogu.com.cn/upload/image_hosting/ruyp7d5e.png)

只需要 **总序列** 减去 $r$ **红色的部分**，加上 $l-1$ **绿色部分** 这样我们就实现了将 $l$ 到 $r$ 的去除。

我们现在就可以知道去除这一段之后我们所走 $x$ 轴与 $y$ 轴的长度。

用原本最后到的位置 $x,y$ 分别减去 $r$ 的，再加上 $l-1$ 的。

## 3.二分

可以二分这个 **修改序列的长度**。

1. 边界：

$$l=0,r=n$$

最小为 **原序列可以实现到达**，最小修改次数为 $0$，而最大就是 **修改整个序列**（如果修改整个序列都到达不了，那么一定是无解了）。

2. check：

那么 check 怎么写呢？

枚举在序列中所有满足长度为 $mid$ 的序列。

得到去除这一段之后我们所走 $x$ 轴与 $y$ 轴的长度。

这时中间的序列是可以随意重置的。

因为一次只变换 $x$ or $y$ 一个值所以我们可以知道 $x$ 和 $y$ 各自相差多少。

这时又有两种情况了。

### 1.$x + y$ 刚好满足序列长度。

此时我们就可以修改最小值。

同时缩小 $r$。

### 2.$x+y>$ 序列长度，但是 序列长度 $-x+y$ 可以被 $2$ 整除。

如果多出偶数步，那么一定是可以跳回来的。

### 3.$x+y<$ 序列长度或者	序列长度 $-x+y$ 不可以被 $2$ 整除。

如果枚举完所有的序列之后没有可以成立的，就说明要扩大 $l$。

# AC Code

```cpp
#include <bits/stdc++.h>
#define ll long long
#define F(i,j,k) for(int i=j;i<=k;i++)
using namespace std;

const int maxn = 2e5 + 10;
string s;
int n, sx, sy, x[maxn], y[maxn];
map<char, map<char, int>>direction;

void Initialize() {//初始化方向
	direction['U']['x'] = 0, direction['U']['y'] = 1;
	direction['D']['x'] = 0, direction['D']['y'] = -1;
	direction['L']['x'] = -1, direction['L']['y'] = 0;
	direction['R']['x'] = 1, direction['R']['y'] = 0;
}
void searchnow(int now) {//使用递归得到每一步所在位置。
	if (now > n)return;
	y[now] = y[now - 1] + direction[s[now - 1]]['y'];
	x[now] = x[now - 1] + direction[s[now - 1]]['x'];
	searchnow(now + 1);
	return;
}
bool check(int len)
{
	for (int l = 1, r = len; r <= n; l++, r++)
	{
		int xx = x[n] - (x[r] - x[l - 1]);
		int xy = y[n] - (y[r] - y[l - 1]);
		if (len >= abs(sx - xx) + abs(sy - xy) && (len - abs(sx - xx) - abs(sy - xy)) % 2 == 0) return true;
	}
	return false;
}
int main() {
	cin >> n >> s >> sx >> sy;
	Initialize();
	searchnow(1);
	int l = 0, r = n, ans = -1;
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (check(mid))r = mid - 1, ans = mid;
		else l = mid + 1;
	}
	cout << ans;
}
```



---

## 作者：秋云暗几重 (赞：0)

#### 【题意】

给定机器人的终点和移动序列，求如何修改移动序列使机器人可以到达终点，并使这个修改的长度序列的前后下标差最小

#### 【分析】

首先可以确定的一点是，对于一个移动序列，如果确定了它的最前的和最后的修改位置，那么修改的代价就确定了。那么在这两个点中间的操作就可以看作是免费修改。

换句话说：使修改区间长度最小即可

很容易使人想到二分区间长度

#### 【实现】

二分区间的长度，再对每个长度判断是否可以经过修改而到达终点

而区间的左右两个部分对到达这个点也是有影响的，我们就可以计算这个影响，并求出由此需要多少操作才能到达终点（看不懂的话...看代码吧...）

时间复杂度O（n^2logn） 超时了鸭

#### 【优化】

对每个操作，我们可以求出它及之前操作的总影响（其实就是前缀和阿~~废话针多~~）

所以就省去了枚举两端外的操作来计算影响

#### 【特殊】

因为每个操作对到达终点的影响为1（x坐标或y坐标上移动一个单位）

所以终点坐标绝对值之和与操作序列长度的奇偶性不同时，无法到达

当然像样例三，无论如何操作都无法到达，就是终点坐标绝对值之和 > 操作序列总长度，也无法到达

当然如果总影响 = 终点坐标，无需改变序列

##### 代码实现
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
inline int read(){
    int x=0,f=1;char c;c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x*=10;x+=c-'0';c=getchar();}
    return f*x;
}//快读  
int n,x,y,sx,sy,cx,cy,l,r,len,mid,ans=0x7ffffff,sum[200050][2];
char opt;
inline int abs(int a){return a>=0?a:-a;}//取绝对值  
inline bool judge(int len){//二分核心 
    for(int i=1;i<=n-len+1;i++){//枚举每个起点	
        sx=sum[n][0]-sum[i+len-1][0]+sum[i-1][0];
        sy=sum[n][1]-sum[i+len-1][1]+sum[i-1][1];//计算当前起点修改长度为len的左右端部分的影响 
        cx=sx-x;cy=sy-y;//需要达到的修改要求  
        if(abs(cx)+abs(cy)<=len) return 1;
    }
    return 0;
}
int main() {
    n=read();
    for(int i=1;i<=n;i++){
        scanf("%c",&opt);
        if(opt=='U'){
            sum[i][0]=sum[i-1][0];sum[i][1]=sum[i-1][1]+1;
        }
        else if(opt=='D'){
            sum[i][0]=sum[i-1][0];sum[i][1]=sum[i-1][1]-1;
        }
        else if(opt=='L'){
            sum[i][0]=sum[i-1][0]-1;sum[i][1]=sum[i-1][1];
        }
        else{
            sum[i][0]=sum[i-1][0]+1;sum[i][1]=sum[i-1][1];
        }//初始化前缀和  
    }
    x=read();y=read();
    if(sum[n][0]==x&&sum[n][1]==y){
        printf("0");return 0;
    }
    if(!((abs(x)+abs(y))%2)==(n%2)){
        printf("-1");return 0;
    }
    if(abs(x)+abs(y)>n){
        printf("-1");return 0;//几个特判  
    }
    l=0;r=n;
    while(l<=r){//二分  
        mid=l+r>>1;
        if(judge(mid)) r=mid-1;
        else l=mid+1;
    }
    printf("%d",l);
    return 0;
}
```
时间复杂度 O（nlogn）

---

## 作者：EternalAlexander (赞：0)

二分答案。  
二分l，即判定修改一个长度为l的区间能否满足题意。  
O(n)枚举原串中长度为l的所有连续子段，设执行这一段区间之前和之后的所有操作之后的坐标为(x1, y1)，v为(x1, y1)和目标点(x, y)的距离，那么如果v<=l并且v和l模2同余则可以成立。
```
#include <cstdio>

int n, x, y;
int sum[200005][2];
char cmd[200005];

int abs(int x) {
	if (x>0) return x;
	else return -x;
}

bool check(int l) {
	for (int i=1;i+l-1<=n;++i) {
		int nx=sum[i-1][0]+sum[n][0]-sum[i+l-1][0];
		int ny=sum[i-1][1]+sum[n][1]-sum[i+l-1][1];
		int v=abs(nx-x)+abs(ny-y);
		if (v<=l&&v%2==l%2) return 1;
	}return 0;
}

int main() {
	scanf("%d %s %d %d", &n, cmd+1, &x, &y);
	if (abs(x)+abs(y)>n) {
		printf("-1");
		return 0;
	}
	sum[0][0]=sum[0][1]=0;
	for (int i=1;i<=n;++i) {
		sum[i][0]=sum[i-1][0];
		sum[i][1]=sum[i-1][1];
		if (cmd[i]=='U') sum[i][1]+=1;
		if (cmd[i]=='D') sum[i][1]-=1;
		if (cmd[i]=='L') sum[i][0]-=1;
		if (cmd[i]=='R') sum[i][0]+=1;
	}
	int l=0,r=n,ans=-1;
	while (l<=r) {
		int mid=(l+r)>>1;
		if (check(mid)) {r=mid-1;ans=mid;}
		else l=mid+1;
	}printf("%d", ans);
	return 0;
}
```

---

## 作者：liuyz11 (赞：0)

原比赛题解：[https://www.cnblogs.com/nblyz2003/p/9909038.html](https://www.cnblogs.com/nblyz2003/p/9909038.html)
C.Vasya and Robot

题意：有一个机器人，有四种移动的操作。

U — move from (x,y)(x,y) to (x,y+1)(x,y+1);
D — move from (x,y)(x,y) to (x,y−1)(x,y−1);
L — move from (x,y)(x,y) to (x−1,y)(x−1,y);
R — move from (x,y)(x,y) to (x+1,y)(x+1,y).
现在有一个由操作指令组成的字符串，让你修改一些操作，使得机器人从(0, 0)走到(x, y)，并且maxID - minID + 1最小，即修改最小的长度的子串。如果怎么更改都无法到达，输出-1。

这题用二分法和尺取法都可以做，也很好证明，就是在判断的时候有点麻烦。

对于每一个[l, r]的区间，最简单的方法就是现将这段区间全部删去，求出此时机器人到达的点(x2, y2)。如果进行r - l + 1次操作就能到达(x, y)，即abs(x2 - x) + abs(y2 - y) <= r - l + 1，前提是同奇偶。

能否到达也无需另外判断，直接把答案的初值赋为-1即可。（然而我是一开始就判断的）

代码如下：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#define rep(x, l, r) for(int x = (int)l; x <= (int)r; x++)
#define repd(x, r, l) for(int x = (int)r; x >= (int)l; x--)
#define clr(x,y) memset(x, y, sizeof(x))
#define mp(x, y) make_pair(x, y)
#define all(x) begin(x), end(x)
#define MAXN 200005
#define fi first
#define se second
#define Size(x) ((int)size(x))
using namespace std;
typedef long long LL;
typedef vector<int> vi;
typedef pair<int, int> pii;
const int INF = 1 << 30;
const int p = 10000007;
//head by DYH

pii t, sum[MAXN];
int len;
char st[MAXN];

bool judge(int l, int r){
    return abs(t.fi - (sum[len].fi - sum[r].fi + sum[l - 1].fi)) + abs(t.se - (sum[len].se - sum[r].se + sum[l - 1].se)) <= r - l + 1;
}

int main(){
    scanf("%d", &len);
    scanf("%s", st);
    rep(i, 1, len){
        if(st[i - 1] == 'U') sum[i].fi = sum[i - 1].fi, sum[i].se = sum[i - 1].se + 1;
        if(st[i - 1] == 'D') sum[i].fi = sum[i - 1].fi, sum[i].se = sum[i - 1].se - 1;
        if(st[i - 1] == 'L') sum[i].fi = sum[i - 1].fi - 1, sum[i].se = sum[i - 1].se;
        if(st[i - 1] == 'R') sum[i].fi = sum[i - 1].fi + 1, sum[i].se = sum[i - 1].se;
    }
    int x, y;
    scanf("%d%d", &x, &y);
    if(abs(x) + abs(y) > len || abs(abs(x) + abs(y) - len) & 1){
        puts("-1");
        return 0;
    }
    t = mp(x, y);
    int l = 1, r = 0, ans = INF;
    while(r <= len){
        while(judge(l, r)){
            ans = min(ans, r - l + 1);
            l++;
        }
        r++;
    }
    printf("%d\n", ans);
    return 0;
}
```

---

