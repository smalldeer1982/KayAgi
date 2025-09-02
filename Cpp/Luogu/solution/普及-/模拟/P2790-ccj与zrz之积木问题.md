# ccj与zrz之积木问题

## 题目背景

ccj和zrz无聊到了玩起了搭积木...(本题选自uva101，翻译来自《算法竞赛入门经典2》)


## 题目描述

从左到右有 $n$ 个木块，编号从 $0$ 到 $n-1$，要求模拟以下 $4$ 种操作（下面的 $a$ 和 $b$ 都是木块编号，归位表示比如 $1$ 号木块归到 $1$ 号位去）。

- $\texttt{move }a\texttt{ onto }b$：把 $a$ 和 $b$ 上方的木块全部归位，然后把 $a$ 摞在 $b$ 上面；
- $\texttt{move }a\texttt{ over }b$：把 $a$ 上方的全部归位，然后把 $a$ 放在 $b$ 所在木块堆的顶部；
- $\texttt{pile }a\texttt{ onto }b$：把 $b$ 上方的木块全部归位，然后把 $a$ 及上面的木块整体摞在 $b$ 上面；
- $\texttt{pile }a\texttt{ over }b$：把 $a$ 及上面的木块整体摞在 $b$ 所在木块堆的顶部；
- 遇到 $\texttt{quit}$ 停止。$a$ 和 $b$ 在同一堆的指令时非法指令，应当忽略。

最后输出每个位置的木块列表，按照从底部到顶部的顺序排列。

## 说明/提示

### 数据范围及约定

对于全部数据，$0<n<25$。

## 样例 #1

### 输入

```
10
move 9 onto 1
move 8 over 1
move 7 over 1
move 6 over 1
pile 8 over 6
pile 8 over 5
move 2 over 1
move 4 over 9
quit```

### 输出

```
0: 0
1: 1 9 2 4
2:
3: 3
4:
5: 5 8 7 6
6:
7:
8:
9:```

# 题解

## 作者：gcwixsxr (赞：12)

# 本蒟蒻第一次发题解
~~日本的蒟蒻还没有吃过呢~~

先说下本题思路

首先用n个动态队列vector

然后先将每个数先存入这n个动态队列中

分别在这n个队列中经过四个操作，最后输出（后面细讲）

### 0.findd函数

用暴力先搜索出某个值的位置，方便以后的函数调用

代码如下
```cpp
void findd(int a,int &p,int &h){//查找原值的位置（"&"可改变原值）
	for(int i=0;i<n;i++){
		for(int j=0;j<v[i].size();j++){
			if(v[i][j]==a)p=i,h=j;//p为队列的指针，h为该数在队列中的位置
	}
}
```
### 1.move_onto函数

先定义p，h然后用以上的findd函数找到a的位置；

将a的高度h以上的木块全部归位

v[p][i]就是v[p][i]的原位，归位即为把v[p][i]放到队列v[v[p][i]]里，然后弹出队列v[p]中的尾位（指针一定要从队尾开始，因为队列中的元素只能从队尾弹出）
```cpp
void move_onto(int a,int b){
	int p,h;
	findd(a,p,h);
	for(int i=v[p].size()-1;i>h;i--){
		v[v[p][i]].push_back(v[p][i]);//把v[p][i]放到队列v[v[p][i]]里
		v[p].pop_back();//弹出队列v[p]中的尾位
	}
	v[p].pop_back();//弹出a	
	findd(b,p,h);
	for(int i=v[p].size()-1;i>h;i--){
		v[v[p][i]].push_back(v[p][i]);//把v[p][i]放到队列v[v[p][i]]里
		v[p].pop_back(); //弹出队列v[p]中的尾位
	}
	v[p].push_back(a);//在b的上方推入a
}
```
### 2.move_over函数

与move_onto函数类似
```cpp
void move_over(int a,int b){
	int p,h;
	findd(a,p,h);
	for(int i=v[p].size()-1;i>h;i--){
		v[v[p][i]].push_back(v[p][i]);//把v[p][i]放到队列v[v[p][i]]里
		v[p].pop_back();//弹出队列v[p]中的尾位
	}
	v[p].pop_back();//弹出a
	findd(b,p,h);//找到b的位置
	v[p].push_back(a);//在b的上方推入a
}
```
### 3.pile_onto函数

归位类似move_onto函数

将a上方的木块移至b上面的操作如下：

在b所在的队列v[pb]里按 _**正序**_ 推入队列v[pa]中a以上的元素

这里有几点容易错的地方：

（1）注意不能像原来一样倒序推入，题目要求a及上面的木块 _**整体**_ 摞在b上面，如果倒序推入，则顺序颠倒，~~这里我也错了好几次~~

（2）不能同时一边弹出v[pa]队列中的数,一边将v[pa]的数推入v[pb]（如第一个for循环中），因为一个是按倒序弹出，一个是正序推入v[pb],会出错

（3）还有最后单独弹出v[pa]中的数时，一定要先用一个变量记录v[pa]的长度，因为随着v[pa]中数的弹出，v[pa]的长度也会缩短（当然此时i倒序时就不用考虑这个问题，即

for(int i=v[pa].size()-1;i>ha;i--)）

```cpp
void pile_onto(int a,int b){
	int pa,ha,pb,hb;
	findd(a,pa,ha);
	findd(b,pb,hb);
	for(int i=v[pb].size()-1;i>hb;i--){
		v[v[pb][i]].push_back(v[pb][i]);
		v[pb].pop_back();
	}
	for(int i=ha;i<=v[pa].size()-1;i++)
		v[pb].push_back(v[pa][i]);//按正序推入队列
	int u=v[pa].size()-1;
	for(int i=ha;i<=u;i++)
		v[pa].pop_back();//弹出队列
}
```
### 4.pile_over函数

类似于pile_onto函数
```cpp
void pile_over(int a,int b){
	int pa,ha,pb,hb;
	findd(a,pa,ha);
	findd(b,pb,hb);	
	for(int i=ha;i<=v[pa].size()-1;i++)
		v[pb].push_back(v[pa][i]);//按正序推入队列
	int u=v[pa].size()-1;
	for(int i=ha;i<=u;i++)
		v[pa].pop_back();//弹出队列
}
```
### 5.out函数（输出函数）
~~很简单吧，就不多说了~~

# 接下来是完整代码

```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
#define MAXN 26
vector<int>v[MAXN];
int n;
void findd(int a,int &p,int &h){
	for(int i=0;i<n;i++){
		for(int j=0;j<v[i].size();j++){
			if(v[i][j]==a)p=i,h=j;
	}
}
void move_onto(int a,int b){
	int p,h;
	findd(a,p,h);
	for(int i=v[p].size()-1;i>h;i--){
		v[v[p][i]].push_back(v[p][i]);
		v[p].pop_back();
	}
	v[p].pop_back();	
	findd(b,p,h);
	for(int i=v[p].size()-1;i>h;i--){
		v[v[p][i]].push_back(v[p][i]);
		v[p].pop_back(); 
	}
	v[p].push_back(a);
}
void move_over(int a,int b){
	int p,h;
	findd(a,p,h);
	for(int i=v[p].size()-1;i>h;i--){
		v[v[p][i]].push_back(v[p][i]);
		v[p].pop_back();
	}
	v[p].pop_back();
	findd(b,p,h);
	v[p].push_back(a);
}
void pile_onto(int a,int b){
	int pa,ha,pb,hb;
	findd(a,pa,ha);
	findd(b,pb,hb);
	for(int i=v[pb].size()-1;i>hb;i--){
		v[v[pb][i]].push_back(v[pb][i]);
		v[pb].pop_back();
	}
	for(int i=ha;i<=v[pa].size()-1;i++)
		v[pb].push_back(v[pa][i]);
	int u=v[pa].size()-1;
	for(int i=ha;i<=u;i++)
		v[pa].pop_back();
}
void pile_over(int a,int b){
	int pa,ha,pb,hb;
	findd(a,pa,ha);
	findd(b,pb,hb);	
	for(int i=ha;i<=v[pa].size()-1;i++)
		v[pb].push_back(v[pa][i]);
	int u=v[pa].size()-1;
	for(int i=ha;i<=u;i++)
		v[pa].pop_back();
}
void out()
{
    for(int i=0;i<n;i++)
    {
        cout<<i<<":";
        if(v[i].empty())
        {
            cout<<endl;
            continue;
        }
        for(int j=0;j<v[i].size();j++)
            cout<<" "<<v[i][j];
        cout<<endl;
    }
}
char s1[10],s2[10];
int a,b;
signed main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++)
    {
        v[i].push_back(i);
    }
    while(1)
    {
        scanf("%s",s1);
        if(strcmp(s1,"quit")==0)break;
        scanf("%d%s%d",&a,s2,&b);
        int wa,wb,ha,hb;
        findd(a,wa,ha);
        findd(b,wb,hb);
        if(wa==wb)continue;
        if(strcmp(s1,"move")==0&&strcmp(s2,"onto")==0)move_onto(a,b);//判断字符串是否相等
        if(strcmp(s1,"move")==0&&strcmp(s2,"over")==0)move_over(a,b);
        if(strcmp(s1,"pile")==0&&strcmp(s2,"onto")==0)pile_onto(a,b);
        if(strcmp(s1,"pile")==0&&strcmp(s2,"over")==0)pile_over(a,b);
    }
	out();
	return 0;
}
```
望洛谷通过


---

## 作者：1124828077ccj (赞：5)

此题很简单，模拟即可。可以用vector来做，虽然我的做法有点麻烦，但是思路还是挺清晰的，把每一个操作都单独写一段函数，自己好好体会吧

附代码

```cpp
#include<cstring>
#include<vector>
#include<cstdio>
using namespace std;
int n,a,b,h1,q1,h2,q2;
char p[10],q[10];
vector<int>s[32];
void find(){
    for (int i=0;i<n;i++)
    for (int o=0;o<s[i].size();o++)
    {if (s[i][o]==a){h1=i;q1=o;}if (s[i][o]==b){h2=i;q2=o;}};
}
void moveonto(){
    for (int i=q1+1;i<s[h1].size();i++)
    s[s[h1][i]].push_back(s[h1][i]);
    for (int i=q2+1;i<s[h2].size();i++)
    s[s[h2][i]].push_back(s[h2][i]);
    s[h1].resize(q1);
    s[h2].resize(q2+1);
    s[h2].push_back(a);
}
void moveover(){
    for (int i=q1+1;i<s[h1].size();i++)
    s[s[h1][i]].push_back(s[h1][i]);
    s[h1].resize(q1);
    s[h2].push_back(a);
}
void pileonto(){
    for (int i=q2+1;i<s[h2].size();i++)
    s[s[h2][i]].push_back(s[h2][i]);
    s[h2].resize(q2+1);
    for (int i=q1;i<s[h1].size();i++)
    s[h2].push_back(s[h1][i]);
    s[h1].resize(q1);
}
void pileover(){
    for (int i=q1;i<s[h1].size();i++)
    s[h2].push_back(s[h1][i]);
    s[h1].resize(q1);
}
int main()
{
    scanf("%d",&n);
    for (int i=0;i<n;i++)s[i].push_back(i);
    for(;;)
    {
        scanf("%s",p);
        if (strcmp(p,"quit")==0)break;
        scanf("%d%s%d",&a,q,&b);
        find();
        if (h1==h2)continue;
        if (strcmp(p,"move")==0 && strcmp(q,"onto")==0)moveonto();
        if (strcmp(p,"move")==0 && strcmp(q,"over")==0)moveover();
        if (strcmp(p,"pile")==0 && strcmp(q,"onto")==0)pileonto();
        if (strcmp(p,"pile")==0 && strcmp(q,"over")==0)pileover();
    }
    for (int i=0;i<n;i++)
    {
        printf("%d:",i);
        for (int o=0;o<s[i].size();o++)
        printf(" %d",s[i][o]);
        printf("\n");
    }
    return 0;
}
```

---

## 作者：KobeBeanBryantCox (赞：4)

# P2790 ccj与zrz之积木问题 题解

------------

[题目传送门](https://www.luogu.com.cn/problem/P2790)

~~话说我的代码才 62 行，算短的了吧QwQ~~

------------

## 题意

此题题目描述简洁无废话，题意见题目描述。

------------

## 分析

先看数据范围：$0<n<25$，于是直接模拟不会超时。

我们先定义两个数组：$a[30][30]$ 和 $height[30]$。

**$a[i][j]$ 表示第 $i$ 堆积木里高度为 $j$ 的积木编号，$height[i]$ 表示第 $i$ 堆积木的高度。**

------------

然后定义几个函数，分别为 $find$、$add$、$back$ 和 $move$。

1. $find(x)$ 返回值为 $int$，用来**寻找编号为 $x$ 的积木所在的堆的编号**。

	- 例子：如图，比如调用 $find(1)$ 返回 $4$。![](https://cdn.luogu.com.cn/upload/image_hosting/66pr3zyv.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

2. $add(x,y)$ 无返回值，作用是**将编号为 $y$ 的积木摞到编号为 $x$ 的堆的顶部**。

	- 例子：如图，比如调用 $add(1,1)$。注意不能调用非顶层积木（如 $add(2,1)$ 是不行的）![](https://cdn.luogu.com.cn/upload/image_hosting/12r384ns.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

3. $back(x)$ 无返回值，是将**编号为 $x$ 的积木上面的积木全部归位**。

	- 例子：如图，比如调用 $back(0)$。![](https://cdn.luogu.com.cn/upload/image_hosting/939yrx7p.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

4. $move(x,y)$ 无返回值，用来将 **编号为 $x$ 的积木以及它以上的积木 全部整体摞在 编号为 $y$ 的积木所在的那一堆的顶部**。

	- 例子：如图，调用 $move(0,2)$ 或 $move(0,4)$。![](https://cdn.luogu.com.cn/upload/image_hosting/v03a70u1.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

注意 $add$ 和 $move$ 的区别。

定义这几个函数是为了方便接下来的操作。

------------

### 重点！！！

1. $\texttt{move }a\texttt{ onto }b$：把 $a$ 和 $b$ 上方的木块全部归位，然后把 $a$ 摞在 $b$ 上面；

	即 $back(a)\text{ --> }back(b)\text{ --> }move(a,b)$。
    
   注：由于先 $back(a)$ 和 $back(b)$ 了，所以 $a$ 和 $b$ 所在的堆上面都没有积木，可以直接 $move(a,b)$。

2. $\texttt{move }a\texttt{ over }b$：把 $a$ 上方的全部归位，然后把 $a$ 放在 $b$ 所在木块堆的顶部；

	即 $back(a)\text{ --> }move(a,b)$。
   
   注：同上。

3. $\texttt{pile }a\texttt{ onto }b$：把 $b$ 上方的木块全部归位，然后把 $a$ 及上面的木块整体摞在 $b$ 上面；

	即 $back(b)\text{ --> }move(a,b)$。

4. $\texttt{pile }a\texttt{ over }b$：把 $a$ 及上面的木块整体摞在 $b$ 所在木块堆的顶部；

	即直接 $move(a,b)$。

5. 遇到 $\texttt{quit}$ 停止。

- **$a$ 和 $b$ 在同一堆的指令时非法指令，应当忽略。**

	~~我就是因为这个调了好久的代码啊啊啊啊QAQ~~

------------

### 实现代码

- $add$ 函数：

```cpp
void add(int x,int y)
// 将编号为 y 的积木摞到编号为 x 的堆得顶部
{
	a[x][++height[x]]=y;
}
```

- $find$ 函数：

```cpp
int find(int x)
// 寻找编号为 x 的积木所在的堆的编号
{
	for(int i=0;i<n;i++)
		for(int j=1;j<=height[i];j++)
			if(a[i][j]==x)return i;
	return 0;
	// 其实可以不要这个，因为编号为 x 的积木一定找得到
	// 但是加上这句养成良好习惯
}
```

- $back$ 函数：

```cpp
void back(int x)
// 编号为 x 的积木上面的积木全部归位
{
	int k=find(x); // 先找到 x 所在的堆
	for(;height[k]>0;height[k]--)
	{
		int u=a[k][height[k]]; // u 表示当前这个堆的最顶层的积木编号
		if(u==x)break;
		add(u,u); // 把它上面的全部归位
	}
}
```

- $move$ 函数：

```cpp
void move(int x,int y)
//编号为 x 的积木以及它以上的积木 全部整体摞在 编号为 y 的积木所在的那一堆的顶部
{
	int ka=find(x),kb=find(y),xx; // 先找到 x 和 y 的堆
	for(int i=1;i<=height[ka];i++)
		if(a[ka][i]==x)
		{
			xx=i;
			break;
		}
		// 再找 x 再这个堆的哪里（就是 x 在堆中的高度）

	for(int i=xx;i<=height[ka];i++)add(kb,a[ka][i]);
	// 把 x 及以上的积木全部添加到 y 的堆的顶部
	// 注意此循环正序，否则添加上去后是反的
	height[ka]=xx-1; // 高度变化
}
```

- 主函数（这个应该都会吧）：

```cpp
int main()
{
	cin>>n;
	for(int i=0;i<n;i++)add(i,i); // 一定要初始化
	while(cin>>s1)
	{
		if(s1=="quit")break;
		cin>>aa>>s2>>bb;
		if(find(aa)==find(bb))continue;
		// 就是这个，让我调好久的代码！！！
		if(s1=="move"&&s2=="onto")back(aa),back(bb),move(aa,bb);
		else if(s1=="move"&&s2=="over")back(aa),move(aa,bb);
		else if(s1=="pile"&&s2=="onto")back(bb),move(aa,bb);
		else if(s1=="pile"&&s2=="over")move(aa,bb);
		// 每种情况分类讨论，见上述分析
	}
	for(int i=0;i<n;i++) // 输出
	{
		printf("%d:",i);
		for(int j=1;j<=height[i];j++)printf(" %d",a[i][j]);
		putchar('\n');
	}
	return 0;
}
```

到此，这个题已经迎刃而解了。

------------

## AC代码

不加注释 62 行。

```cpp
#include<bits/stdc++.h>
#define Code using
#define by namespace
#define wjb std
Code by wjb;
string s1,s2;
int n,a[30][30],aa,bb,height[30];
// a[i][j] 表示第 i 堆积木里高度为 j 的积木编号，height[i] 表示第 i 堆积木的高度
int find(int x)
// 寻找编号为 x 的积木所在的堆的编号
{
	for(int i=0;i<n;i++)
		for(int j=1;j<=height[i];j++)
			if(a[i][j]==x)return i;
	return 0;
	// 其实可以不要这个，因为编号为 x 的积木一定找得到
	// 但是加上这句养成良好习惯
}
void add(int x,int y)
// 将编号为 y 的积木摞到编号为 x 的堆的顶部
{
	a[x][++height[x]]=y;
}
void back(int x)
// 编号为 x 的积木上面的积木全部归位
{
	int k=find(x); // 先找到 x 所在的堆
	for(;height[k]>0;height[k]--)
	{
		int u=a[k][height[k]]; // u 表示当前这个堆的最顶层的积木编号
		if(u==x)break;
		add(u,u); // 把它上面的全部归位
	}
}
void move(int x,int y)
//编号为 x 的积木以及它以上的积木 全部整体摞在 编号为 y 的积木所在的那一堆的顶部
{
	int ka=find(x),kb=find(y),xx; // 先找到 x 和 y 的堆
	for(int i=1;i<=height[ka];i++)
		if(a[ka][i]==x)
		{
			xx=i;
			break;
		}
		// 再找 x 再这个堆的哪里（就是 x 在堆中的高度）

	for(int i=xx;i<=height[ka];i++)add(kb,a[ka][i]);
	// 把 x 及以上的积木全部添加到 y 的堆的顶部
	// 注意此循环正序，否则添加上去后是反的
	height[ka]=xx-1; // 高度变化
}
int main()
{
	cin>>n;
	for(int i=0;i<n;i++)add(i,i); // 一定要初始化
	while(cin>>s1)
	{
		if(s1=="quit")break;
		cin>>aa>>s2>>bb;
		if(find(aa)==find(bb))continue;
		// 就是这个，让我调好久的代码！！！
		if(s1=="move"&&s2=="onto")back(aa),back(bb),move(aa,bb);
		else if(s1=="move"&&s2=="over")back(aa),move(aa,bb);
		else if(s1=="pile"&&s2=="onto")back(bb),move(aa,bb);
		else if(s1=="pile"&&s2=="over")move(aa,bb);
		// 每种情况分类讨论，见上述分析
	}
	for(int i=0;i<n;i++) // 输出
	{
		printf("%d:",i);
		for(int j=1;j<=height[i];j++)printf(" %d",a[i][j]);
		putchar('\n');
	}
	return 0;
}
```

------------

后记 1：版权所有@[wangjianbo123](https://www.luogu.com.cn/user/865625)，请勿抄袭代码。

后记 2：写代码的习惯一定要好，代码不要乱七八糟，优秀的码风是很醉人的~

~~还有，能不能不要脸地要个赞呀QwQ~~

---

## 作者：袁宇轩 (赞：3)

前往[题目](https://www.luogu.com.cn/problem/P2790)

n<25，直接上模拟。

题解里的大佬们（不包括我）都是vector，那么我就写了一个最朴素的用数组来模拟，供大家参考。

里面有坑点注意一下：

1.a,b都是木块编号，而不是位置，要是像我这种傻乎乎的人一样把它搞错了，那就只能重写。

2.当a,b在同一个位置上是就该忽略这条语句。

3.最后一点就是要非常细心，特别是我这种~~没事找事用数组写的~~，写了一大堆密密麻麻。

具体我会在代码中注释。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,y,vis[30],a[30][30];//vis[i]存储木块i当前的位置；a[i][j]存储i位置上第j个木块编号，a[i][0]存储i位置上木块数量； 
string s1,s2;

int main()
{
	cin>>n;
	for (int i=0;i<n;i++) a[i][0]=1,a[i][1]=vis[i]=i;//一开始每个木块在自己的位置上 
	while (cin>>s1 && s1!="quit"){//当遇到quit则退出 
		cin>>x>>s2>>y;
		if (vis[x]==vis[y]) continue;//x,y在同一个位置 
		//分成四种情况讨论 
		if (s1=="move" && s2=="onto"){
			while (a[vis[x]][a[vis[x]][0]]!=x && a[vis[x]][0]>0)//把x之上的木块归位 
			  vis[a[vis[x]][a[vis[x]][0]]]=a[a[vis[x]][a[vis[x]][0]]][++a[a[vis[x]][a[vis[x]][0]]][0]]=a[vis[x]][a[vis[x]][0]],a[vis[x]][0]--;
			while (a[vis[y]][a[vis[y]][0]]!=y && a[vis[y]][0]>0)//把y之上的木块归位 
			  vis[a[vis[y]][a[vis[y]][0]]]=a[a[vis[y]][a[vis[y]][0]]][++a[a[vis[y]][a[vis[y]][0]]][0]]=a[vis[y]][a[vis[y]][0]],a[vis[y]][0]--;
			a[vis[y]][++a[vis[y]][0]]=x;//把x移到y上面 
			a[vis[x]][0]--;
			vis[x]=vis[y];
		}
		else if (s1=="move" && s2=="over"){
			while (a[vis[x]][a[vis[x]][0]]!=x && a[vis[x]][0]>0)//把x之上的木块归位 
			  vis[a[vis[x]][a[vis[x]][0]]]=a[a[vis[x]][a[vis[x]][0]]][++a[a[vis[x]][a[vis[x]][0]]][0]]=a[vis[x]][a[vis[x]][0]],a[vis[x]][0]--;
		    a[vis[y]][++a[vis[y]][0]]=x;//把x移到y上面
			a[vis[x]][0]--;
			vis[x]=vis[y];
		}
		else if (s1=="pile" && s2=="onto"){
			while (a[vis[y]][a[vis[y]][0]]!=y && a[vis[y]][0]>0)//把y之上的木块归位 
			  vis[a[vis[y]][a[vis[y]][0]]]=a[a[vis[y]][a[vis[y]][0]]][++a[a[vis[y]][a[vis[y]][0]]][0]]=a[vis[y]][a[vis[y]][0]],a[vis[y]][0]--;
		    int j=1,k=vis[x];
		    while (j<=a[vis[x]][0] && a[vis[x]][j]!=x) j++;//找到x的位置j 
		    for (int i=j;i<=a[k][0];i++)//把x和x上的木块移到y上面 
		      a[vis[y]][++a[vis[y]][0]]=a[k][i],vis[a[k][i]]=vis[y];
		    a[k][0]=j-1;
		}
		else if (s1=="pile" && s2=="over"){
		    int j=1,k=vis[x];
		    while (j<=a[vis[x]][0] && a[vis[x]][j]!=x) j++;//找到x的位置j 
		    for (int i=j;i<=a[k][0];i++)//把x和x上的木块移到y所在木块堆的上面 
		      a[vis[y]][++a[vis[y]][0]]=a[k][i],vis[a[k][i]]=vis[y];
		    a[k][0]=j-1;
		}
	}
	for (int i=0;i<n;i++){//输出 
		cout<<i<<':';
		for (int j=1;j<=a[i][0];j++)
		  cout<<' '<<a[i][j];
		cout<<endl;
	}
	return 0;
}
```


---

## 作者：船医 (赞：2)

本蒟蒻来一篇基础题解

看到这种一个操作进行多次且无序进行的

首先就想到定义函数。

那么首先本题思路就显而易见了

虽然长但是很好写

## 1.find函数

显然只有四个操作的函数是不够的，因为我们并不知道a，b的位置。

这时候就需要一个find函数了。
```cpp
void find(int x,int &p,int &h) {
	for (int i=0; i<n; ++i)
		for (int j=0; j<v[i].size(); ++j)//两重循环全扫一遍
			if (v[i][j]==x) {
				p = i;//p为位置
				h = j;//h为高度
				break;
			}
```
~~就这~~

#### 接下来就是4个操作函数了
## 1.moveonto函数
```cpp
void moveonto() {
	find(a,p,h);//找到a的位置与高度
	for (int i=v[p].size()-1; i>h; --i) {
		v[v[p][i]].push_back(v[p][i]);
		v[p].pop_back();
	}//还原a上方块
	v[p].pop_back();//删去a
	find(b,p,h);//找到b的位置与高度（接下来不对find进行阐述）
	for (int i=v[p].size()-1; i>h; --i) {
		v[v[p][i]].push_back(v[p][i]);
		v[p].pop_back();
	}//还原b上的方块
	v[p].push_back(a);
}
```
## 2.moveover函数
```cpp
void moveover() {
	find(a,p,h);
	for (int i=v[p].size()-1; i>h; --i) {
		v[v[p][i]].push_back(v[p][i]);
		v[p].pop_back();
	}//还原a上
	v[p].pop_back();
	find(b,p,h);
	v[p].push_back(a);//a置于b列上
}
```
## 3.pileonto函数
```cpp
void pileonto() {
	find(b,p,h);
	for (int i=v[p].size()-1; i>h; --i) {
		v[v[p][i]].push_back(v[p][i]);
		v[p].pop_back();
	}
	int t=p;
	find(a,p,h);
	int l=v[p].size();
	for(int i=h; i<l; i++) {
		v[t].push_back(v[p][i]);
	}//a及上方方块置于b列
	for(int i=v[p].size()-1; i>=h; i--) {
		v[p].pop_back();
	}//删去a及以上
}
```
## 4pileover函数
```cpp
void pileover() {
	find(b,p,h);
	int t=p;
	find(a,p,h);
	int l=v[p].size();//数组长度
	for(int i=h; i<l; i++) {
		v[t].push_back(v[p][i]);
	}//将a及上方木块摞上去
	for(int i=v[p].size()-1; i>=h; i--) {
		v[p].pop_back();//弹出
	}
}
```
## AC代码如下

```cpp
#include<bits/stdc++.h>
using namespace std;
int p,h,a,b,n,u;
string s1,s2,s3;
vector<int> v[630];
void find(int x,int &p,int &h) {
	for (int i=0; i<n; ++i)
		for (int j=0; j<v[i].size(); ++j)
			if (v[i][j]==x) {
				p = i;
				h = j;
				break;
			}
}
void moveonto() {
	find(a,p,h);
	for (int i=v[p].size()-1; i>h; --i) {
		v[v[p][i]].push_back(v[p][i]);
		v[p].pop_back();
	}
	v[p].pop_back();
	find(b,p,h);
	for (int i=v[p].size()-1; i>h; --i) {
		v[v[p][i]].push_back(v[p][i]);
		v[p].pop_back();
	}
	v[p].push_back(a);
}

void moveover() {
	find(a,p,h);
	for (int i=v[p].size()-1; i>h; --i) {
		v[v[p][i]].push_back(v[p][i]);
		v[p].pop_back();
	}
	v[p].pop_back();
	find(b,p,h);
	v[p].push_back(a);
}
void pileonto() {
	find(b,p,h);
	for (int i=v[p].size()-1; i>h; --i) {
		v[v[p][i]].push_back(v[p][i]);
		v[p].pop_back();
	}
	int t=p;
	find(a,p,h);
	int l=v[p].size();
	for(int i=h; i<l; i++) {
		v[t].push_back(v[p][i]);
	}
	for(int i=v[p].size()-1; i>=h; i--) {
		v[p].pop_back();
	}
}
void pileover() {
	find(b,p,h);
	int t=p;
	find(a,p,h);
	int l=v[p].size();
	for(int i=h; i<l; i++) {
		v[t].push_back(v[p][i]);
	}
	for(int i=v[p].size()-1; i>=h; i--) {
		v[p].pop_back();
	}
}
int main() {
	cin>>n;
	for (int i=0; i<n; ++i) {
		v[i].push_back(i);
	}
	while(1+1==2){
		cin>>s1;
		if(s1=="quit") {

			for(int i=0; i<n; i++) {
				cout<<i<<':';
				for (int j=0; j<v[i].size(); j++)
					cout<<' '<<v[i][j];
				cout<<endl;
			}//判停
			break;
		} else {

			cin>>a>>s2>>b;
			find(a,p,h);
			u=p;
			find(b,p,h);
			if(u==p)
				continue;//a，b不能在同一行
			if(s1=="move") {
				if(s2=="onto") {
					moveonto();
				} else {
					moveover();
				}
			} else {
				if(s2=="onto") {
					pileonto();
				} else {
					pileover();
				}
			}
		}
	}
	return 0;
}
```


---

## 作者：zhouj2006 (赞：2)

#### 蒟蒻又来写题解了

看到 `0<n<25` 我们知道，这是一道~~水~~模拟。

我们附上一张图，来分析一下题目


------------
![](https://cdn.luogu.com.cn/upload/image_hosting/ufoxt7wj.png)


------------
通过这张图，我们可以把题目中的操作条理清晰地实现。

因为`0<n<25`，所以我选择用vector

如果不太清楚vetcor，可以康康这个
[vetcor常见用法详解](https://www.cnblogs.com/isChenJY/p/11534378.html)

##### 我们说一下题目中需要注意的几个点
- 归位

因为题目4中操作，三种涉及到了归位，所以我单独拿出来

```cpp
while(v[cnt[tn1]].back()!=tn1)
			{
				cnt[v[cnt[tn1]].back()]=v[cnt[tn1]].back();
				v[v[cnt[tn1]].back()].push_back(v[cnt[tn1]].back());
				v[cnt[tn1]].pop_back();
			}
```
形如这样的，都是归位操作
- 输出

题目的输出不要忘了空格

最后，上代码，具体的解析见注释。

```cpp
#include <iostream>
#include <cstdio> 
#include <string>
#include <vector>

using namespace std;

typedef vector<int>::iterator VI;   //偷个懒 
 
vector<int> v[30];	//vector数组 
int cnt[30];	//标志 
int n;
 
VI Find(vector<int> &v,int num)  //查找函数，找到指定的箱子编号目前所在的位置 
{
	for(VI i=v.begin();i!=v.end();i++)
		if(*i==num)
			return i;
	return v.begin()-1;
}

void out()		//输出函数，不要忘了空格 
{
	for(int i=0;i<n;i++)
	{
		cout<<i<<":";
		if(v[i].empty())
		{
			cout<<endl;
			continue;
		}
		cout<<" "<<v[i][0];
		for(int j=1;j<v[i].size();j++)
			cout<<" "<<v[i][j];
		cout<<endl;
	}
}
 
int main()
{
	cin>>n;
	for(int i=0;i<n;i++)		//将1-n存入v数组中 
	{
		v[i].clear();
		v[i].push_back(i);
		cnt[i]=i;
	}
	
	string ts;
	int tn1,tn2;
	
	while(cin>>ts&&ts!="quit")	//输入，并且不是quit 
	{
		if(ts=="move")
		{
			cin>>tn1>>ts>>tn2;
			if(cnt[tn1]==cnt[tn2])
				continue;
			while(v[cnt[tn1]].back()!=tn1)    //归位操作 
			{
				cnt[v[cnt[tn1]].back()]=v[cnt[tn1]].back();
				v[v[cnt[tn1]].back()].push_back(v[cnt[tn1]].back());
				v[cnt[tn1]].pop_back();
			}
			v[cnt[tn1]].pop_back();
			if(ts=="onto")		//move...onto 
			{
				VI i;
				while(v[cnt[tn2]].back()!=tn2)
				{
					cnt[v[cnt[tn2]].back()]=v[cnt[tn2]].back();
					v[v[cnt[tn2]].back()].push_back(v[cnt[tn2]].back());
					v[cnt[tn2]].pop_back();
				}
				v[cnt[tn2]].push_back(tn1);
				cnt[tn1]=cnt[tn2];
			}
			else		//move...over
			{
				v[cnt[tn2]].push_back(tn1);
				cnt[tn1]=cnt[tn2];    //更新 
			}
		}
		else
		{
			cin>>tn1>>ts>>tn2;
			if(cnt[tn1]==cnt[tn2])
				continue;
			if(ts=="onto")		//pile...onto 
			{
				while(v[cnt[tn2]].back()!=tn2)    //归位 
				{
					cnt[v[cnt[tn2]].back()]=v[cnt[tn2]].back();
					v[v[cnt[tn2]].back()].push_back(v[cnt[tn2]].back());
					v[cnt[tn2]].pop_back();
				}
				VI pos1=Find(v[cnt[tn1]],tn1),pos2=Find(v[cnt[tn2]],tn2);
				int tmp[25],sum=0;
				for(VI i=v[cnt[tn1]].end()-1;i>=pos1;i--)
				{
					tmp[sum++]=*i;
					v[cnt[tn1]].erase(i);
					cnt[*i]=cnt[tn2];
				}
				for(int i=0;i<sum/2;i++)
				{
					int t=tmp[i];
					tmp[i]=tmp[sum-i-1];
					tmp[sum-i-1]=t;
				}
				v[cnt[tn2]].insert(pos2+1,tmp,tmp+sum);  //整体插入
			}
			else	  //pile...over
			{
				VI pos1=Find(v[cnt[tn1]],tn1);
				int tmp[25],sum=0;
				for(VI i=v[cnt[tn1]].end()-1;i>=pos1;i--)
				{
					tmp[sum++]=*i;
					v[cnt[tn1]].erase(i);
					cnt[*i]=cnt[tn2];
				}
				for(int i=0;i<sum/2;i++)
				{
					int t=tmp[i];
					tmp[i]=tmp[sum-i-1];
					tmp[sum-i-1]=t;
				}
				v[cnt[tn2]].insert(v[cnt[tn2]].end(),tmp,tmp+sum);  //整体插入 
			}
		}
	}
	out();   //输出 
	return 0;
}
```

写题解不易，希望各位多多支持！

---

## 作者：Wy_x (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P2790)

[更好的阅读体验？](https://www.luogu.com.cn/blog/73-54-16/solution-p2790)

## 思路：

依照题意直接模拟即可，需要注意题目中的坑。**特别注意**，$n$ **指的是积木数量，不是指令数**，如果用数组模拟，还要特别注意细节（后面会说）。

（本题解使用自增自减运算符，不懂它们的同学可以先[百度](https://www.baidu.com/)）。

## 代码拆分：

### 定义：

- 需要记忆 $a$ 和 $b$ 在哪一个积木堆里，方便以后寻找。

- 建一个二维数组存积木的详细位置，例如，$ans_{i,j}$ 表示在编号为 $i$ 的积木堆中从下往上数第 $j$ 个位置的积木编号。

- 还需要记忆每堆积木的数量，方便以后进行移位操作。

- 定义四个变量存指令信息，两个 `int` 类型 两个 `string `类型（`char` 也行），还需定义积木数 $n$。

```cpp
int ans[105][105];//ans存x现在在哪 
int num[105];//存x号位积木数量 
int vis[105];//记忆i存到了几号位 
int a,b,n;
string nw1,nw2;//存指令 
```

### 初始化：

- 所有积木编号由 $0$ 到 $n-1$。

- 起初，每个积木都在自己编号的位置上，每堆积木数量都是 $1$。

```cpp
for(int i=0;i<=n-1;i++)//初始化 
{
	vis[i]=i;//记忆积木位置 
	ans[i][1]=i;//初始的积木堆上 
	num[i]=1;//记忆数量 
}
```

### 核心模拟：

- **重点**：循环的语句格式为 `while(true)`，不是 `for(int i=1;i<=n;i++)`！！！

- 遇到 `quit` 时应立刻停止循环。

- 当积木 $a$ 和积木 $b$ 在同一堆里时，应当忽略这条指令。

- $a$ 和 $b$ 是积木编号，不是积木堆号，它们的位置应该用记忆化数组寻找，调用。


#### 寻找 $a$ 和 $b$ 在积木堆中的位置：

- 已经记忆过了。

```cpp
int x=vis[a];//寻找a在积木中的位置 
int y=vis[b];//寻找b在积木中的位置
```


#### $a$ 上方的木块全部归位:

- 需要归位的有：积木的记忆位置，详细位置。

- $a$ 所在积木堆的数量可以边循环边减。

```cpp
for(int j=num[x];j>=1;j--)//a上方的木块全部归位
{
	if(ans[x][j]==a)  break;//到a了就停止寻找 
	num[x]--;//a积木塔上积木数减一 
	int z=ans[x][j];//计算当前积木堆顶的值 
	ans[z][++num[z]]=z;//归位 
	vis[z]=z;//记忆归位 
}
```
#### $b$ 上方的木块全部归位:

- 类比 $a$ 上方积木的归位方法。

```cpp
for(j=num[y];j>=1;j--)//把b上方的木块全部归位
{
	if(ans[y][j]==b)  break;
	num[y]--;
	int z=ans[y][j];
	ans[z][++num[z]]=z;
	vis[z]=z;
}
```
#### 把 $a$ 移到 $b$ 上面：

- 不要忘了记忆的更改，同时，因为循环结束条件，还要把 $a$ 原来所在的积木堆的积木数减 $1$。

```cpp、
ans[y][++num[y]]=a;//把a放到b上方 
num[x]--;
vis[a]=y;
```

#### 把 $a$ 及上面的木块整体摞在 $b$ 上面：

- 需要先查找 $a$ 记忆里是在从下往上数的第几个积木。

- 在函数内定义变量时值是随机的，需要清零。

- 注意移位方法：整体移位。

```cpp
int j,p=0,rember=0;
while(ans[x][++p]!=a);//寻找a的位置 
for(;p<=num[x];p++)//注意循环的写法 
{//把a及上面的木块整体摞在b上面 
	int z=ans[x][p];
	ans[y][++num[y]]=z;
	vis[z]=y;
}
num[x]=rember-1;
//现在a原来所在的积木数为
//a原来的位置减1 
//因为a已经被移走了 
```

### 输出：

- 从 $0$ 到 $n-1$。

- 注意格式：在字符`:`后有空格。

```cpp
for(int i=0;i<=n-1;i++)//按照题意输出，从0到n-1 
{
	cout<<i<<":";
	for(int j=1;j<=num[i];j++)
	{
		cout<<" "<<ans[i][j];//别忘了:后的空格 
	}
	cout<<endl;//别忘了换行 
}
```

## 完整代码之一：
```cpp
#include<bits/stdc++.h>//万能头文件   
using namespace std;

int ans[105][105];//ans存x现在在哪 
int num[105];//存x号位积木数量 
int vis[105];//记忆i存到了几号位 
int a,b,n;
string nw1,nw2;//存指令 

int main()
{
	cin>>n;
	
	for(int i=0;i<=n-1;i++)//初始化 
	{
		vis[i]=i;//记忆积木位置 
		ans[i][1]=i;//初始的积木堆上 
		num[i]=1;//记忆数量 
	}
	
	while(true)//注意，是 while(true),while(true),while(true)!!!!
	{
		cin>>nw1>>a>>nw2>>b;//输入 
		if(nw1=="quit")  break;//遇到quit停止
		
		if(vis[a]==vis[b])  continue;//指令非法 
		
		int x=vis[a];//寻找a在积木中的位置 
		int y=vis[b];//寻找b在积木中的位置
		
		if(nw1=="move"&&nw2=="onto")
		{
			for(int j=num[x];j>=1;j--)//a上方的木块全部归位
			{
				if(ans[x][j]==a)  break;//到a了就停止寻找 
				num[x]--;//a积木塔上积木数减一 
				int z=ans[x][j];//计算当前积木堆顶的值 
				ans[z][++num[z]]=z;//归位 
				vis[z]=z;//记忆归位 
			}
			
			for(int j=num[y];j>=1;j--)//b上方的木块全部归位
			{
				if(ans[y][j]==b)  break;
				num[y]--;
				int z=ans[y][j];
				ans[z][++num[z]]=z;
				vis[z]=z;
			}
			
			ans[y][++num[y]]=a;//把a放到b上方 
			num[x]--;
			vis[a]=y;
		}
		
		if(nw1=="move"&&nw2=="over")
		{
			for(int j=num[x];j>=1;j--)//把a上方的全部归位
			{
				if(ans[x][j]==a)  break;//同上 
				num[x]--;
				int z=ans[x][j];
				ans[z][++num[z]]=z;
				vis[z]=z;
			}
			num[x]--;//同上 
			ans[y][++num[y]]=a;
			vis[a]=y;
		}
		
		if(nw1=="pile"&&nw2=="onto")
		{
			int j,p=0,rember=0;
			//主函数内定义变量时值是随机的，需要清零 
			for(j=num[y];j>=1;j--)//把b上方的木块全部归位
			{
				if(ans[y][j]==b)  break;//同上 
				num[y]--;
				int z=ans[y][j];
				ans[z][++num[z]]=z;
				vis[z]=z;
			}
			while(ans[x][++p]!=a);//寻找a的位置 
			rember=p;//记录a的位置 
			for(;p<=num[x];p++)//注意循环的写法 
			{//把a及上面的木块整体摞在b上面 
				int z=ans[x][p];
				ans[y][++num[y]]=z;
				vis[z]=y;
			}
			num[x]=rember-1;
			//现在a原来所在的积木数为
			//a原来的位置减1 
			//因为a已经被移走了 
		}	
		
		if(nw1=="pile"&&nw2=="over")
		{
			int p=0,rember=0;
			while(ans[x][++p]!=a);
			rember=p;//记录a的位置 
			for(;p<=num[x];p++)//同上 
			{
				int z=ans[x][p];
				ans[y][++num[y]]=z;
				vis[z]=y;
			}
			num[x]=rember-1;//同上 
		}
	}
	
	for(int i=0;i<=n-1;i++)//按照题意输出，从0到n-1 
	{
		cout<<i<<":";
		for(int j=1;j<=num[i];j++)
		{
			cout<<" "<<ans[i][j];//别忘了:后的空格 
		}
		cout<<endl;//别忘了换行 
	}
	return 0;
}
```

## 另一些代码：

[清奇的代码](https://www.luogu.com.cn/paste/nai10uow)

[函数封装代码1](https://www.luogu.com.cn/paste/un13yi5u)

[函数封装代码2](https://www.luogu.com.cn/paste/h7jhzupc)

[还可以点这里下载代码](https://www.luogu.com.cn/problem/U253357)


---

## 作者：ShineEternal (赞：1)

# 写在前面：如想获得更佳阅读效果，请点击[这里](https://blog.csdn.net/kkkksc03/article/details/84555384)，如有任何疑惑，欢迎私信交流！

( ⊙ o ⊙ )啊！好像2000字了，看在蒟蒻这么辛苦的份上，求过，求赞！

# 题目链接：https://www.luogu.org/problemnew/show/P2790
这题码量稍有点大。。。
# 分析：
这道题模拟即可。因为考虑到所有的操作vector可最快捷的实现，所以数组动态vector。每一种情况分别考虑。

其他的见代码注释
## 部分过长的注释防在这里，请对照序号到代码中查看。
**①**：wa意为a的位置，记录当前a所在位置的序号。
wb意为b的位置，记录当前b所在位置的序号。
ca意为a的层数，记录当前a所在这堆积木中第几个。
cb意为b的层数，记录当前b所在这堆积木中第几个。

其他定义显而易见。

**②**：search遍历一遍所有位置所有积木，找到a或b后记录他们的位置和位置中第几个，相当于为后面的一个初始化吧。

**③**：此函数即move onto，按照题意模拟即可，之后④⑤⑥均如此，具体模拟步骤会详细说明。

# 代码：

```cpp
#include<cstdio>
#include<vector>
#include<cstring>
using namespace std;
int wa,wb,ca,cb;//①
char s1[10],s2[10];
int a,b;
vector<int>v[30];
int n;
void search()//②
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<v[i].size();j++)
		{
			if(v[i][j]==a)
			{
				wa=i;
				ca=j;
			}
			if(v[i][j]==b)
			{
				wb=i;
				cb=j;
			}
		}
	}
}
void moon()//③
{
	for(int i=ca+1;i<v[wa].size();i++)
	{
		v[v[wa][i]].push_back(v[wa][i]);
	}//把a以上的归位
	for(int i=cb+1;i<v[wb].size();i++)
	{
		v[v[wb][i]].push_back(v[wb][i]);
	}//把b以上的归位
	v[wa].resize(ca);//只保留当前vector到a-1
	v[wb].resize(cb+1);//但是b要保留，因为a是要摞到b上的
	v[wb].push_back(a);//摞上去
}//下面的都换汤不换药，我想大家都应该知道
void moov()//④
{
	for(int i=ca+1;i<v[wa].size();i++)
	{
		v[v[wa][i]].push_back(v[wa][i]);
	}
	v[wa].resize(ca);
	v[wb].push_back(a);
}
void pion()//⑤
{
	for(int i=cb+1;i<v[wb].size();i++)
	{
		v[v[wb][i]].push_back(v[wb][i]);
	}
	v[wb].resize(cb+1);
	for(int i=ca;i<v[wa].size();i++)
	{
		v[wb].push_back(v[wa][i]);
	}
	v[wa].resize(ca);
}
void piov()//⑥
{
	for(int i=ca;i<v[wa].size();i++)
	{
		v[wb].push_back(v[wa][i]);
	}
	v[wa].resize(ca);
}
int main()
{
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		v[i].push_back(i);
	}
	while(1)
	{
		scanf("%s",s1);
		if(strcmp(s1,"quit")==0)break;//提前判断是否退出
		scanf("%d%s%d",&a,s2,&b);
		search();
		if(wa==wb)continue;//根据题意，如果a和b在同一堆，那么忽略
		if(strcmp(s1,"move")==0&&strcmp(s2,"onto")==0)moon();
		if(strcmp(s1,"move")==0&&strcmp(s2,"over")==0)moov();
		if(strcmp(s1,"pile")==0&&strcmp(s2,"onto")==0)pion();
		if(strcmp(s1,"pile")==0&&strcmp(s2,"over")==0)piov();
		//逐一判断每种操作，其中相应的子函数对应去两个单词的首字母连起来
	}
	for(int i=0;i<n;i++)
	{
		printf("%d:",i);//暂时不输出括号，有了再打
		for(int j=0;j<v[i].size();j++)
		{
			printf(" %d",v[i][j]);//当前位置有积木，那么就打出来，别忘了空格
		}
		printf("\n");//每次换行
	}
	return 0;
}
```

~完结撒花

---

## 作者：不是憨憨 (赞：1)

来一波题解

（1）注意四个操作，最后都有把a及上面的木块整体放在b所在木块堆的顶部的要求（如果只是a的话是因为a上面已经没有其他木块了），所以    我们可以考虑单独写一个函数实现。

（2）注意如果是1,3操作（即含有onto的操作）都需要把b上方的木块全部归位，所以这个也可以写在一起。

（3）注意如果是1,2操作  (即含有move的操作）都需要把a上方的木块全部归位，所以这个也可以写在一起。

综上所述，其实操作只需要两个函数（一个用来使木块归位，一个用来将a及其上方木块整体移动到b上方），但还是需要一个函数找出a，b的初始位置。

好了，废话就不说了。题解如下。

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------








```cpp
#include <cstdio>
#include <string>
#include <vector>
#include <iostream>
using namespace std;
const int maxn = 30;
int n;
vector<int> pile[maxn];         //每个pile[i]是一个vector
//找木块a所在的pile和height, 以引用的形式返还调用者
void find_block(int a, int& p, int& h) {
    for(p = 0; p < n; p++)
        for(h = 0; h < pile[p].size(); h++)
            if (pile[p][h] == a) return;
} 
//把第p堆高度为h的木块上方的所有木块移回原位
void clear_above(int p, int h) {
    for(int i = h+1; i < pile[p].size(); i++) {
        int b = pile[p][i];
        pile[b].push_back(b);        //把木块b放回原位 
    }
    pile[p].resize(h+1);            //pile只应保留下标0~h的元素
} 
//把第p堆高度为h及其上方的木块整体移动到p2堆的顶部
```
void pile\_onto



```cpp
(int p, int h, int p2) {
    for(int i = h; i < pile[p].size(); i++)
        pile[p2].push_back(pile[p][i]);
    pile[p].resize(h);
} 
void print() {
    for(int i = 0; i < n; i++) {
        printf("%d:", i);
        for(int j = 0; j < pile[i].size(); j++) printf(" %d",pile[i][j]);
        printf("\n");
    }
} 
int main() {
    int a, b;
    cin >> n;
    string s1, s2;
    for(int i = 0; i < n; i++) pile[i].push_back(i);
    while(cin >> s1 >> a >> s2 >> b) {
        int pa, pb, ha, hb;
        find_block(a, pa, ha);
        find_block(b, pb, hb);
        if(pa == pb) continue; //非法指令
        if (s2 == "onto") clear_above(pb, hb);
        if (s1 == "move") clear_above(pa, ha);
        pile_onto(pa, ha, pb); 
    }
    print();
    return 0;
}

```

---

## 作者：T21C06 (赞：0)

[题目](https://www.luogu.com.cn/problem/P2790)


## 思路
### 核心思路
这道题数据范围较小，$0 < n < 25$，所以直接**模拟**。
### 数据结构
由于搭积木是先放的被压在下面，类似于栈（先进后出），所以本人的代码用的是**栈**。

### 方法
每次输入一条指令，判断是题目中的哪一条指令，按题意执行即可。最后输出答案。

### 一些坑点
- 输入的 $n$ 只是积木编号，**并不是指令的条数**，而且编号是**从 $0$ 开始到 $n-1$ 的**。
- **注意输出格式**：

  $n$ 行，第 $i$ 行输出一个 $i$ 和冒号，然后一个**空格**，输出，它位置上的所有积木。

- 仔细做题，因为栈要比其他数据结构难调，容易出错。

## 代码
### 函数
每条指令的操作如果都放在循环里，就会很乱，用函数就能更好地解决问题。

### 1. move a onto b 

作用：把 $a$ 和 $b$ 上方的木块全部归位，然后把 $a$ 摞在 $b$ 上面。

```cpp
void m1(int a,int b){
	int t=book[a],k=book[b]; 
        //book[i] 表示编号为i的木块所在的堆
	while(q[t].top()!=a){ //将 a 上方的木块归位
		book[q[t].top()]=q[t].top();
        //编号 q[t].top() 为的木块改变所在堆
		q[q[t].top()].push(q[t].top());
        //编号 q[t].top() 为的木块压入（堆上）所在堆
		q[t].pop();
        //编号 q[t].top() 为的木块弹出（拿出）原堆
	} 
	while(q[k].top()!=b){ //将 b 上方的木块归位
    //这些操作和上面的操作基本一致，不再说明
		book[q[k].top()]=q[k].top();
		q[q[k].top()].push(q[k].top());
		q[k].pop();
	}
	q[t].pop(); //a 从原堆拿出
	q[k].push(a); //a 摞在 b 上面。
	book[a]=book[b]; //a 改变所在堆
}
```

### 2. move a over b

作用：把 $a$ 上方的全部归位，然后把 $a$ 放在 $b$ 所在木块堆的顶部。

```cpp
//和指令1基本一致，只少了 b 上方的木块归位的步骤
void m2(int a,int b){
	int t=book[a],k=book[b];
	while(q[t].top()!=a){
		book[q[t].top()]=q[t].top();
		q[q[t].top()].push(q[t].top());
		q[t].pop();
	} 
	q[t].pop();
	q[k].push(a);
	book[a]=book[b]; 
}
```

### 3. pile a onto b

作用：把 $b$ 上方的木块全部归位，然后把 $a$ 及上面的木块整体摞在 $b$ 上面。
```cpp
void p1(int a,int b){
	int t=book[a],k=book[b],s=0;
	memset(f,0,sizeof(f));//数组清空！！！
	while(q[t].top()!=a){ //提取 a 及上面的木块整体
		book[q[t].top()]=k;
        //编号 q[t].top() 为的木块改为 b 所在堆
		f[++s]=q[t].top();  
        //f 数组存要移走的木块
		q[t].pop();
        //编号 q[t].top() 为的木块弹出（拿出）原堆
	} 
   //上面循环中 a 并没有被移走，所以重复操作一次，把 a 移走
	book[q[t].top()]=k;
	f[++s]=q[t].top();
	q[t].pop();
	while(q[k].top()!=b){
    //此循环部分前面已说明，不再重复说明
		book[q[k].top()]=q[k].top();
		q[q[k].top()].push(q[k].top());
		q[k].pop();
	}
    //因为拿的时候是先拿上面的，数组里存的其实是倒的，需要倒序存放
	for(int i=s;i>=1;i--) q[k].push(f[i]);
}
```

### 4. pile a over b
作用：把 $a$ 及上面的木块整体摞在 $b$ 所在木块堆的顶部。

```cpp
//和指令3基本一致，只少了 b 上方的木块归位的步骤
void p2(int a,int b){
	int t=book[a],k=book[b],s=0;
	memset(f,0,sizeof(f));
	while(q[t].top()!=a){
		book[q[t].top()]=k;
		f[++s]=q[t].top();
		q[t].pop();
	} 
	book[q[t].top()]=k;
	f[++s]=q[t].top();
	q[t].pop();
	for(int i=s;i>=1;i--) q[k].push(f[i]);
}
```


### 主函数
```cpp
int main(){
    cin>>n;
    //初始化（编号 i 为的木块在 i 号堆）
    for(int i=0;i<n;i++) book[i]=i,q[i].push(i);
    while(1){
    //一条指令分成4部分：字符串 数字 字符串 数字
    //这样就不用提取数字了
    	cin>>st1;
    	if(st1=="quit") break; //如果等于字符串”quit“，结束
    	cin>>a>>st2>>b;
		if(book[a]==book[b]) continue;// 如果 a 和 b 在同一堆，后面的就不用执行了
        //判断应该执行那一条指令
    	if(st1=="move"){
    		if(st2=="onto") m1(a,b);
    		else m2(a,b);
		}else{
			if(st2=="onto") p1(a,b);
			else p2(a,b);
		}
	}
        //输出，方法和3、4两条指令差不多
	for(int i=0;i<n;i++){
		cout<<i<<": "; //冒号后面有空格！！！
		s=0;
        //提取第 i 堆每一块木块的编号
		memset(f,0,sizeof(f));
		while(q[i].empty()==0) f[++s]=q[i].top(),q[i].pop();
        //倒序输出
		for(int j=s;j>=1;j--) cout<<f[j]<<" ";
		cout<<endl;
	}
	return 0;
}
```


## AC代码

```cpp
#include<bits/stdc++.h>
#include<string>
#include<stack>
using namespace std;
string st1,st2;
stack<int>q[30];
int book[30],a,b,f[30],n,s;
void m1(int a,int b){
	int t=book[a],k=book[b];
	while(q[t].top()!=a){
		book[q[t].top()]=q[t].top();
		q[q[t].top()].push(q[t].top());
		q[t].pop();
	} 
	while(q[k].top()!=b){
		book[q[k].top()]=q[k].top();
		q[q[k].top()].push(q[k].top());
		q[k].pop();
	}
	q[t].pop();
	q[k].push(a);
	book[a]=book[b]; 
}
void m2(int a,int b){
	int t=book[a],k=book[b];
	while(q[t].top()!=a){
		book[q[t].top()]=q[t].top();
		q[q[t].top()].push(q[t].top());
		q[t].pop();
	} 
	q[t].pop();
	q[k].push(a);
	book[a]=book[b]; 
}
void p1(int a,int b){
	int t=book[a],k=book[b],s=0;
	memset(f,0,sizeof(f));
	while(q[t].top()!=a){
		book[q[t].top()]=k;
		f[++s]=q[t].top();
		q[t].pop();
	} 
	book[q[t].top()]=k;
	f[++s]=q[t].top();
	q[t].pop();
	while(q[k].top()!=b){
		book[q[k].top()]=q[k].top();
		q[q[k].top()].push(q[k].top());
		q[k].pop();
	}
	for(int i=s;i>=1;i--) q[k].push(f[i]);
}
void p2(int a,int b){
	int t=book[a],k=book[b],s=0;
	memset(f,0,sizeof(f));
	while(q[t].top()!=a){
		book[q[t].top()]=k;
		f[++s]=q[t].top();
		q[t].pop();
	} 
	book[q[t].top()]=k;
	f[++s]=q[t].top();
	q[t].pop();
	for(int i=s;i>=1;i--) q[k].push(f[i]);
}
int main(){
    cin>>n;
    for(int i=0;i<n;i++) book[i]=i,q[i].push(i);
    while(1){
    	cin>>st1;
    	if(st1=="quit") break;
    	cin>>a>>st2>>b;
		if(book[a]==book[b]) continue;
    	if(st1=="move"){
    		if(st2=="onto") m1(a,b);
    		else m2(a,b);
		}else{
			if(st2=="onto") p1(a,b);
			else p2(a,b);
		}
	}
	for(int i=0;i<n;i++){
		cout<<i<<": ";
		s=0;
		memset(f,0,sizeof(f));
		while(q[i].empty()==0) f[++s]=q[i].top(),q[i].pop();
		for(int j=s;j>=1;j--) cout<<f[j]<<" ";
		cout<<endl;
	}
	return 0;
}
```
## 其他

- 这是本人第一篇题解，如有错误欢迎指出。
- 祝愿看了这篇题解的人本题AC！

---

## 作者：andyli (赞：0)

定义一个归位函数 `reposition`，和移动函数 `move`，则题述操作均可以使用这两个函数完成。

```python
s = [*open(0)]
n = int(s[0])
A = [[i] for i in range(n)]

# 把 a 上方的木块全部归位
# p 为 a 当前所在位置的编号
def reposition(a, p):
    # 需要对 len(A[p]) - A[p].index(a) - 1 个木块进行归位
    for _ in range(len(A[p]) - A[p].index(a) - 1):
        # 依次取出 a 这一堆末尾的木块归位，即 pop 后放到对应堆末尾
        x = A[p].pop()
        A[x] += x,

# 把 a 及上面的木块移动至 b 所在木块堆的顶部
# pa, pb 为木块 a, b 当前所在位置的编号
def move(a, pa, pb):
    A[pb] += A[pa][A[pa].index(a):] # index 找到 a 在这一堆中的位置，用切片取出这一堆中 a 及上面的木块加入到 b 所在堆的末尾
    A[pa] = A[pa][:A[pa].index(a)] # 用切片取出这一堆中 a 下面的部分替换这一堆

for s in s[1:-1]:
    s = s.split()
    a, b = int(s[1]), int(s[3])
    # 找出木块 a, b 当前所在位置的编号
    pa = [i for i in range(n) if a in A[i]][0] # 首个 i 满足 a 在第 i 堆中
    pb = [i for i in range(n) if b in A[i]][0] # 首个 i 满足 b 在第 i 堆中
    if pa == pb: # a 和 b 在同一堆的指令时非法指令，应当忽略。
        continue
    s = s[0] + s[2]
    if s == 'moveonto':
        reposition(a, pa)
        reposition(b, pb)
        move(a, pa, pb)
    if s == 'moveover':
        reposition(a, pa)
        move(a, pa, pb)
    if s == 'pileonto':
        reposition(b, pb)
        move(a, pa, pb)
    if s == 'pileover':
        move(a, pa, pb)
for i in range(n):
    print(f'{i}:', *A[i])
```

---

## 作者：duchengjun (赞：0)

### 预处理

一开始，每一个积木的上方只有本身。

```cpp
void init(){
	for(int i=0;i<n;i++)
		t[i].push_back(i);
}
```

### 找积木在哪一个积木之上和在哪个积木的第几个

遍历 -> 查找。

```cpp
void find(int a,int &p,int &h){
	for(int i=0;i<n;i++)
		for(int j=0;j<t[i].size();j++)
			if(t[i][j]==a){
				p=i,h=j;
				return;
			}
}
```

### 归位

将 $h$ 上方的积木放在自己原本的位置的最上方。

再将移走的积木运用 resize 移除。

```cpp
void homing(int p,int h){
	for(int i=h+1;i<t[p].size();i++){
		int b=t[p][i];
		t[b].push_back(b);
	}
	t[p].resize(h+1);
}
```

### 放在顶部

将要移走的积木放在 $p2$（文章中的 $b$）。

再将移走的积木运用 resize 移除。

```cpp
void pile_onto(int p,int h,int p2){
	for(int i=h;i<t[p].size();i++)
		t[p2].push_back(t[p][i]);
	t[p].resize(h);
}
```

### 输出

按照题目输出即可。

```cpp
void print(){
	for(int i=0;i<n;i++){
		cout<<i<<": ";
		for(int j=0;j<t[i].size();j++)
			cout<<t[i][j]<<" ";
		cout<<endl;
	}
}
```

### 代码

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int N=30;
int n;
vector<int>t[N];
string s1,s2;
int a,b;
void init(){
	for(int i=0;i<n;i++)
		t[i].push_back(i);
}
void find(int a,int &p,int &h){
	for(int i=0;i<n;i++)
		for(int j=0;j<t[i].size();j++)
			if(t[i][j]==a){
				p=i,h=j;
				return;
			}
}
void homing(int p,int h){
	for(int i=h+1;i<t[p].size();i++){
		int b=t[p][i];
		t[b].push_back(b);
	}
	t[p].resize(h+1);
}
void pile_onto(int p,int h,int p2){
	for(int i=h;i<t[p].size();i++)
		t[p2].push_back(t[p][i]);
	t[p].resize(h);
}
void print(){
	for(int i=0;i<n;i++){
		cout<<i<<": ";
		for(int j=0;j<t[i].size();j++)
			cout<<t[i][j]<<" ";
		cout<<endl;
	}
}
signed main(){
	cin>>n;
	init();
	while(cin>>s1&&s1!="quit"){
		cin>>a>>s2>>b;
		int pa,pb,ha,hb;
		find(a,pa,ha);
		find(b,pb,hb);
		if(pa==pb)continue;
		if(s2=="onto")homing(pb,hb);
		if(s1=="move")homing(pa,ha);
		pile_onto(pa,ha,pb);
	}
	print();
	return 0;
}
```

---

## 作者：Times_New_man (赞：0)

[$\tiny\texttt{点击这里食用效果更佳}$](https://www.luogu.org/blog/SMARTsoft/solution-uva101)

# $\Huge\texttt{爆炸模拟}$
$$\large\texttt{当然不会TLE}$$

# 重点$:vector$
### 特点:
```
（0）vector是一个模板类,可以定义任何类型的数组vector<类型名>数组名
（1）存在唯一的一个被称为“第一个”的数据元素
（2）存在唯一的一个被称为“最后一个”的数据元素
（3）除第一个元素之外，集合中的每个数据元素均只有一个前驱
（4）除最后一个元素之外，集合中的每个数据元素均只有一个后继
```
### 使用:
```cpp
(1)头文件#include<vector>.

(2)创建vector对象，vector<int>vec;

(3)尾部插入数字：vec.push_back(a);

(4)使用下标访问元素，cout<<vec[0]<<endl;	//记住下标是从0开始的。
 
(5)使用迭代器访问元素.
vector<int>::iterator it;
for(it=vec.begin();it!=vec.end();it++)
    cout<<*it<<endl;

(6)插入元素：    vec.insert(vec.begin()+i,a);在第i+1个元素前面插入a;

(7)删除元素：
vec.erase(vec.begin()+2);删除第3个元素
vec.erase(vec.begin()+i,vec.end()+j);删除区间[i,j-1];区间从0开始

(8)排序：sort(vec.begin(),vec.end());

(9)数组大小:vec.size();

(10)直接赋值:vector<int>v=vec;

(11)清空:v.clear();
```

# $\huge\texttt{亮代码!}$


```cpp
#include<iostream>		//cin和cout 
#include<vector>		//[不定长数组](敲黑板划重点)
using namespace std;

const int maxn=30;		//最多只有25堆(也就是25个木块)  
int n;		//总堆数(也是总木块数) 
vector<int>pile[maxn]; //数组的数组,没学过vector的请定义二维数组 

void find_block(int a,int&p,int&h)		//找木块a所在的堆以及它是p堆的第几个木块(高度h),以[引用](敲黑板划重点)的形式返回调用者 
{
	for(p=0;p<n;p++)		//暴力*1 
		for(h=0;h<pile[p].size();h++)		//暴力*2
			if(pile[p][h]==a)		//如果你有幸找到 
				return;			//当然是和这个函数说拜拜啦 
	//由于传入的p和h作为循环变量一直在变化,所以直接返回即可 
}

void clear_above(int p,int h)			//把第p堆高度为h的木块上方的所有木块移回原位 
{
	for(int i=h+1;i<pile[p].size();i++)		//从第h+1个元素开始操作 
	{
		int b=pile[p][i];		//多定义一个变量,代码简洁又好看 
		pile[b].push_back(b); //把木块b放回原位[注意只是在原位加了一个数,木有把它删掉](敲黑板划重点)
  	}
	pile[p].resize(h+1);	//这一堆只应保留下标0~h的元素,h就是这个木块本身 
}

void pile_onto(int p,int h,int p2)	////把第p堆高度h及其上方的木块(如果有的话)整体移动到p2堆的顶部
{
	for(int i=h;i<pile[p].size();i++)		//从h这个元素开始搬(我很好奇怎么从底下开始抽) 
		pile[p2].push_back(pile[p][i]);		//[注意只是在p2堆加了一个数,木有把它删掉](敲黑板划重点)
	pile[p].resize(h);				//只保留下标从0~h的元素 
}

void print()		//最后打印结果 
{
	for(int i=0;i<n;i++)		//每一堆都要打印 
	{
		//按照规则打印,不解释 
		cout<<i<<':';
		for(int j=0;j<pile[i].size();j++)
			cout<<' '<<pile[i][j];
		cout<<endl;
	}  
}

int main()
{
  	cin>>n;			//输入总堆数(也是总木块数) 
  	int a,b;		//指令中的两个木块的编号(注意不是堆号)
  	string s1,s2;	/*两条指令中的字符[见下] 
	move a onto b: 把a和b上方的木块全部放回初始的位置，然后把a放到b上面 
	move a over b: 把a上方的木块全部放回初始的位置，然后把a放在b所在木块堆的最上方 
	pile a onto b: 把b上方的木块部放回初始的位置，然后把a和a上面所有的木块整体放到b上面 
	pile a over b: 把a和a上面所有的木块整体放在b所在木块堆的最上方 
	*/
  	for(int i=0;i<n;i++)		//初始化循环,从0到总堆数(也是总木块数)
	  	pile[i].push_back(i);	//将每一个木块归位 
	while(cin>>s1>>a>>s2>>b)	//每次输入,如果任何一个读不到cin函数就会return 0,由于quit只有1个string,a s2 b均读不到,所以不用判断 
	{
		int pa/*木块a在哪一堆*/,pb/*木块b在哪一堆*/,ha/*木块a是pa堆的第几个木块(高度)*/,hb/*木块b是pb堆的第几个木块(高度)*/;
		find_block(a,pa,ha);		//找到木块a的位置 
		find_block(b,pb,hb);		//找到木块b的位置 
		if(pa==pb)		//发现两个木块在同一堆非法指令,调到下一条指令 
			continue;		//与break不同,不会跳出循环,会直接进入下一次循环 
		//我们发现,当出现onto指令时,需要还原b木块以上的木块 
		// 同　理 ,当出现move指令时,需要还原a木块以上的木块
		if(s2=="onto")
			clear_above(pb,hb);		//还原b上面的木块 
		if(s1=="move")
			clear_above(pa,ha);		//还原a上面的木块
		pile_onto(pa,ha,pb);		//将a以及他上面的木块(如果有的话)一起摞在b木块所在的堆的顶部 
	}
	print();			//输出结果,如果忘了,写对了WA声一片,写错了还是WA声一片 
	return 0;
}
```


---

