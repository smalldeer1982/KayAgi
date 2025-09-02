# The Blocks Problem

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=37

[PDF](https://uva.onlinejudge.org/external/1/p101.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA101/4657c698576c8c299dbbf5655d7dbe63bf148978.png)

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

## 作者：Zlc晨鑫 (赞：51)

[*My blog*](https://www.luogu.com.cn/blog/Zlc/)

这道题就是一道模拟，不过比较复杂，码量较大。看到好多题解都是用 ```vector``` 做的。那我就来用数组模拟一波。

首先，总共有 ```0 < n < 25``` 个木块堆。所以可以用一个二维数组来存。最坏的情况就是所有的木块都在一堆，所以只需声明 ```int wood[30][30]``` 即可。可以将数组初始化为 ```-1``` ，表示“没有木块”。

首先我们先来实现几个基本操作：
1. 找到```a```在数组中的位置
```cpp
// * 找到a所在的木块堆编号及高度
void find(int a, int& x, int& y) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; wood[i][j] != -1; j++) {
            if (wood[i][j] == a) {
                x = i; y = j;
                return;
            }
        }
    }
}
```
2. 求木块的高度
```cpp
// * 获取第a堆木块的高度
void height(int a, int& h) {
    for (h = 0; wood[a][h] != -1; h++);
}
```

然后，在此基础上，再将插入和删除操作给写出来。

```cpp
// * 在数组中删除一个元素
void del(int x, int y) {
    int h;
    height(x, h);
    for (int i = y; i < h; i++) {
        wood[x][i] = wood[x][i+1];
    }
}

// * 在a上面插入一个元素b
void ins(int x, int y, int b) {
    int h;
    height(x, h);
    for (int i = h; i > y+1; i--) {
        wood[x][i] = wood[x][i-1];
    }
    wood[x][y+1] = b;
}
```

至此，几个基本操作就完成了。下面开始实现题意操作。

观察四种指令，发现都有将木块归位的操作，所以可以先写一个```back```函数。

```cpp
// * 把第x堆的高度为y的木块及以上的木块归位
void back(int x, int y) {
    int h;
    height(x, h);
    for (int i = y; i < h; i++) {
        int p, q;
        p = wood[x][i];
        height(p, q);
        ins(p, q-1, wood[x][i]);
    }
    // * 删除已经归位的木块
    for (int i = h-1; i >= y; i--) {
        del(x, i);
    }
}
```

不知道大家有没有注意到，再写```del```和```ins```函数时，参数用的是下标而非数值，你可能觉得可以用```find```函数找到数值的下标。但此处，```back```函数中，在完成归位操作之后，还要将原来的木块删除，所以，会出现两个木块，只能用下标来表示。

接下来的事就好办了，直接根据题意模拟即可，这里封装为一个```struct```：

```cpp
struct Robot {
    void mvot(int a, int b) {
        int x, y, p, q; 
        find(a, x, y);
        back(x, y+1);
        find(b, p, q);
        back(p, q+1);
        ins(p, q, a);
        del(x, y);
    }

    void mvoe(int a, int b) {
        int x, y, p, q;
        find(a, x, y); find(b, p, q);
        back(x, y+1);
        int h; height(p, h);
        ins(p, h-1, a);
        del(x, y);
    }

    void plot(int a, int b) {
        int x, y, p, q;
        find(a, x, y); find(b, p, q);
        back(p, q+1);
        int h; height(x, h);
        for (int i = h-1; i >= y; i--) ins(p, q, wood[x][i]);
        for (int i = h-1; i >= y; i--) del(x, i);
    }

    void ploe(int a, int b) {
        int x, y, p, q;
        find(a, x, y); find(b, p, q);
        int h; height(x, h); int H; height(p, H);
        for (int i = h-1; i >= y; i--) ins(p, H-1, wood[x][i]);
        for (int i = h-1; i >= y; i--) del(x, i);
    }
}robot;
```

这里有一个值得注意的地方：在插入时要从后往前，不然顺序会反过来；删除时也一样。如果你不能理解，自己在纸上模拟一下就知道为什么了。

接下来给出完整代码：

```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
using namespace std;

const int maxn = 28;
int wood[maxn][maxn], n;

void init() {
    for (int i = 0; i < 28; i++) {
        for (int j = 0; j < 28; j++) {
            wood[i][j] = -1; // * -1表示无效数字
        }
    }
}

void input() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        wood[i][0] = i; // * 将第i个木块堆的第一个数字设置为i
}

void output() {
    for (int i = 0; i < n; i++) {
        printf("%d:", i);
        for (int j = 0; wood[i][j] != -1; j++)
            printf(" %d", wood[i][j]);
        putchar('\n');
    }
}

// * 找到a所在的木块堆编号及高度
void find(int a, int& x, int& y) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; wood[i][j] != -1; j++) {
            if (wood[i][j] == a) {
                x = i; y = j;
                return;
            }
        }
    }
}

// * 获取第a堆木块的高度
void height(int a, int& h) {
    for (h = 0; wood[a][h] != -1; h++);
}

// * 在数组中删除一个元素
void del(int x, int y) {
    int h;
    height(x, h);
    for (int i = y; i < h; i++) {
        wood[x][i] = wood[x][i+1];
    }
}

// * 在a上面插入一个元素b
void ins(int x, int y, int b) {
    int h;
    height(x, h);
    for (int i = h; i > y+1; i--) {
        wood[x][i] = wood[x][i-1];
    }
    wood[x][y+1] = b;
}

// * 把第x堆的高度为y的木块及以上的木块归位
void back(int x, int y) {
    int h;
    height(x, h);
    for (int i = y; i < h; i++) {
        int p, q;
        p = wood[x][i];
        height(p, q);
        ins(p, q-1, wood[x][i]);
    }
    // * 删除已经归位的木块
    for (int i = h-1; i >= y; i--) {
        del(x, i);
    }
}

struct Robot {
    void mvot(int a, int b) {
        int x, y, p, q; 
        find(a, x, y);
        back(x, y+1);
        find(b, p, q);
        back(p, q+1);
        ins(p, q, a);
        del(x, y);
    }

    void mvoe(int a, int b) {
        int x, y, p, q;
        find(a, x, y); find(b, p, q);
        back(x, y+1);
        int h; height(p, h);
        ins(p, h-1, a);
        del(x, y);
    }

    void plot(int a, int b) {
        int x, y, p, q;
        find(a, x, y); find(b, p, q);
        back(p, q+1);
        int h; height(x, h);
        for (int i = h-1; i >= y; i--) ins(p, q, wood[x][i]);
        for (int i = h-1; i >= y; i--) del(x, i);
    }

    void ploe(int a, int b) {
        int x, y, p, q;
        find(a, x, y); find(b, p, q);
        int h; height(x, h); int H; height(p, H);
        for (int i = h-1; i >= y; i--) ins(p, H-1, wood[x][i]);
        for (int i = h-1; i >= y; i--) del(x, i);
    }
}robot;

int main() {
    init();
    input();
    while (1) {
        string s1, s2, s3;
        int a, b;
        cin >> s1 >> a >> s2 >> b;
        if (s1 == "quit") break;
        int x, y, p;
        find(a, x, y); find(b, p, y);
        if (x == p) continue;
        s3 = s1 + s2;
        if (s3 == "moveonto") robot.mvot(a, b);
        else if (s3 == "moveover") robot.mvoe(a, b);
        else if (s3 == "pileonto") robot.plot(a, b);
        else if (s3 == "pileover") robot.ploe(a, b);
    }
    output();
    return 0;
}
```

如果有什么错误欢迎各位指出，谢谢阅读。

你看的这么认真，确定不点个赞再走？

---

## 作者：zxcmiao (赞：11)

```
这是一道模拟题。
对于每个块，记录它上方的块和下方的块，归位清理为-1，
操作时递归查询即可。
细节见代码
```
~~是不是很简单，怒刷水题找信心~~
```cpp
#include<cstdio>
int n;
struct blocks
{
	int up,down;
}block[25];
int find_up(int x)
{
	if(block[x].up==-1)return x;
	return find_up(block[x].up);
}
int find_down(int x)
{
	if(block[x].down==-1)return x;
	return find_down(block[x].down);
}
void move_up(int x)
{
	if(x==-1)return;
	block[block[x].down].up=-1;
	block[x].down=-1;
	move_up(block[x].up);
}
void solve(int x)
{
	printf(" %d",x);
	if(block[x].up==-1)
	  return;
	  else solve(block[x].up);
}
int main()
{
	int i;
	while(scanf("%d",&n)!=EOF)
	{
		for(i=0;i<n;i++)block[i].up=-1,block[i].down=-1;
		while(1)
		{
			int a,b,bb;char ope1[10],ope2[10];
			scanf("%s",ope1);if(ope1[0]=='q')break;
			scanf("%d",&a);scanf("%s",ope2);scanf("%d",&b);
			if(find_down(a)==find_down(b))continue;
			if(ope1[0]=='m')move_up(block[a].up);
			if(ope2[1]=='n')
			{
				move_up(block[b].up);
				bb=b;
			}
			else
			{
				bb=find_up(b);
			}
			block[block[a].down].up=-1;
			block[a].down=bb;
			block[bb].up=a;
		}
		for(i=0;i<n;i++)
		{
			printf("%d:",i);
			if(block[i].down==-1)solve(i);
			printf("\n"); 
		}
	}
	return 0;
}
```

---

## 作者：WanderingTrader (赞：9)

乍一看这道题貌似并没有什么好方法，主要思路还是模拟。  
不过模拟也是有技巧的。
### 题目分析
首先我们自然要选取合适的数据结构。  
这里显然没有树或图那种复杂的关系，肯定是线性表。  
|数据类型|优点|缺点
|:-:|:-:|:-:
|数组/动态数组|查找$O(1)$|任意插入/删除$O(n)$
|链表|任意插入/删除$O(1)$|查找$O(n)$，容易写错
|队列|找最早放入的数据$O(1)$|其他都很差
|栈|找最近放入的数据$O(1)$|其他都很差
|双端队列|头尾$O(1)$|其他都很差

但题目中要求的数据结构有点复杂，要既满足数组的查找$O(1)$，又要满足链表的插入/删除$O(1)$，那怎么办呢？

这时我想到了手写链表。  

首先我给大家介绍一下手写链表的原理。  
```cpp
struct node
{
  int val;
  int pre,next;
}arr[N];
```
手写链表的基本模板如上。可以看到，我们既可以直接用$arr[i]$的方式查找数据，又可以通过修改$pre$和$next$“简单粗暴”的插入或删除数据。

了解了手写链表的原理，我们可以开始做题了。
### 代码
初始化：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 40
#define INF 32
struct node
{
	int val;
	int pre,next;
	void clear()
	{
		pre = next = INF;
	}
}box[N];
int main()
{
	int n;
	for(int i = 0;i < 25;i ++) box[i].val = i;
	while(cin >> n)
	{
		int a,b;
		string s1,s2;
		for(int i = 0;i < n;i ++)
			box[i].clear();
		cin >> s1;
		while(s1 != "quit")
		{
			scanf("%d",&a);
			cin >> s2;
			scanf("%d",&b);
			cin >> s1;
		}
	}
	return 0;
}
```
这里我们在结构体中加入一个clear函数，把pre和next都设为INF，标志头和尾。  
1. move a onto b  
这里我们写一个$reset(x)$函数来把$x$上面的盒子归位：
```cpp
void reset(int x)
{
	for(int i = box[x].next,t;i != INF;i = t)
	{
		t = box[i].next;
		box[i].clear();
	}
}
```
这里我们也可以了解遍历手写链表的方法。注意由于clear执行过后以后box[i].next已经变成INF了，所以要用一个t保存一下。(其实用递归可以解决这个问题，不用变量t，但由于递归涉及到函数调用，会消耗大量时间，所以笔者采用了非递归写法)  
把a放在b上面其实就是连接一条边(b,a)，写一个link函数：
```cpp
void link(int x,int y)
{
	box[x].next = y;
	box[y].pre = x;
}
```
所以这一条很好写，如下：
```cpp
if(s1 == "move")
{
	if(s2 == "onto")
	{
		reset(a);
		reset(b);
		box[box[a].pre].next = INF;
		link(b,a);
		box[a].next = INF;
	}
	else
	{
	}
}
```
注意要将a前一个结点的后继设为INF，保证链表结尾。  
2. move a over b  
这里要将b的结尾与a相连，我们写一个end函数：
```cpp
int end(int x)
{
	int i = x;
	for(;box[i].next != INF;)
		i = box[i].next;
	return i;
}
```
这个很好理解，笔者就不做过多赘述了。  
这个操作的代码也很好写：  
```cpp
else
{
	reset(a);
	int k = end(b);
	link(k,a);
	box[a].next = INF;
}
```
将常用操作封装成函数有助于我们写代码。  
3. pile a onto b  
这个需要一点“思维”了，我们画张图：  
![](https://cdn.luogu.com.cn/upload/image_hosting/37xx7sig.png)  
根据题目的要求，连接几条边即可：  
![](https://cdn.luogu.com.cn/upload/image_hosting/243ie2o2.png)  
于是代码如下：
```cpp
else
{
	if(s2 == "onto")
	{
		reset(b);
		box[box[a].pre].next = INF;
		link(b,a);
	} 
}
```
注意要把a前驱的后继设为INF(怎么听起来那么拗口呢)，保证链表有头有尾。  
4. pile a over b  
这也很简单，调用一下end函数即可：
```cpp
else
{
	int k = end(b);
	box[box[a].pre].next = INF;
	link(k,a);
} 
```

至此，4种操作都做完了。

不过题目中还说，如果a和b处于同一堆，忽略操作，我们为此写一个函数：
```cpp
bool same(int x,int y)
{
	return x == y || end(x) == end(y);
}
```
判断是否在同一堆，只要判断end是否相同即可（想一想，为什么）。  

全部代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 40
#define INF 32
struct node
{
	int val;
	int pre,next;
	void clear()
	{
		pre = next = INF;
	}
}box[N];
int end(int x)
{
	int i = x;
	for(;box[i].next != INF;)
		i = box[i].next;
	return i;
}
void reset(int x)
{
	for(int i = box[x].next,t;i != INF;i = t)
	{
		t = box[i].next;
		box[i].clear();
	}
}
void link(int x,int y)
{
	box[x].next = y;
	box[y].pre = x;
}
bool same(int x,int y)
{
	return x == y || end(x) == end(y);
}
int main()
{
	int n;
	for(int i = 0;i < 25;i ++) box[i].val = i;
	while(cin >> n)
	{
		int a,b;
		string s1,s2;
		for(int i = 0;i < n;i ++)
			box[i].clear();
		cin >> s1;
		while(s1 != "quit")
		{
			scanf("%d",&a);
			cin >> s2;
			scanf("%d",&b);
			if(!same(a,b))
			{
				if(s1 == "move")
				{
					if(s2 == "onto")
					{
						reset(a);
						reset(b);
						box[box[a].pre].next = INF;
						link(b,a);
						box[a].next = INF;
					}
					else
					{
						reset(a);
						int k = end(b);
						link(k,a);
						box[a].next = INF;
					}
				}
				else
				{
					if(s2 == "onto")
					{
						reset(b);
						box[box[a].pre].next = INF;
						link(b,a);
					} 
					else
					{
						int k = end(b);
						box[box[a].pre].next = INF;
						link(k,a);
					} 
					
				}
			}
			cin >> s1;
		}
		for(int i = 0;i < n;i ++,printf("\n"))
		{
			printf("%d:",i);
			if(box[i].pre != INF) continue;
			for(int j = i;j != INF;j = box[j].next)
				printf(" %d",j);
		}
	}
	return 0;
}
```

### 反思与总结
这题主要还是考察对数据结构的掌握。代码中有很多细节，稍不留神就容易写错。如果你是看了题解AC此题的，建议自己独立重写一下完整代码。

时间复杂度最少$O(n)$，最多$O(n^2)$，已经足够AC此题。  

$\mathrm{The\ End.}$

---

## 作者：Snowlanuck (赞：4)

题目地址:https://www.luogu.org/problem/UVA101


首先审题,题目的要求是创建n个木块堆,然后对木块堆进行四个操作:

```
move a onto b: 把a和b上方的木块全部放回初始的位置，然后把a放到b上面
move a over b: 把a上方的木块全部放回初始的位置，然后把a放在b所在木块堆的最上方
pile a onto b: 把b上方的木块部放回初始的位置，然后把a和a上面所有的木块整体放到b上面
pile a over b: 把a和a上面所有的木块整体放在b所在木块堆的最上方
```

观察发现,所有操作的最后一步都是将 a和a上方的所有木块移动到b木块堆的上方

以及只要有move或者onto 就是把a或b上方的木块归位,move归位a,onto归位b
上面两步之后,发现不需要管over了...


所以大体思路就出来了,读入数据 判断是否有move,有就归位a;判断是否有onto,有就归位b,最后一步就是将 a和a上方的所有木块移动到b木块堆的上方


我看了一下洛谷的题解列表,好像没有像我一样引入速查表的,也就是多开一个数组专门存储方块所在位置,这样可以节省循环查找位置的时间,并且占用空间也不算多(0<n<25)


下面放代码
```cpp
#include<bits/stdc++.h>
using namespace std;

struct Pos
{//坐标
	int x;
	int y;
};

vector<int> blocks[30];//方块堆
Pos poss[30];//速查表

void MoveBack(int), MoveAll(int, int);

int main()
{
	int blocks_num;
	cin >> blocks_num;//输入木块堆的数量
	for (int i = 0; i < blocks_num; i++)
	{//初始化木块堆&速查表
		blocks[i].push_back(i);
		poss[i].x = i;
		poss[i].y = 0;
	}
	string Com1;
	while (cin >> Com1)
	{
		if (Com1 == "quit")
			break;
		string  Com2;
		int a, b;
		cin >> a >> Com2 >> b;

		if (poss[a].x == poss[b].x)
			continue;
		if (Com1 == "move")
			MoveBack(a);
		if (Com2 == "onto")
			MoveBack(b);
		MoveAll(a, b);
	}
	//输出结果
	for (int i = 0; i < blocks_num; i++)
	{
		cout << i << ":";
		for (int j = 0; j < blocks[i].size(); j++)
		{
			cout << " " << blocks[i][j];
		}
		cout << endl;
	}


	return 0;
}

//把num木块上的方块归位
void MoveBack(int num)
{
	Pos local = poss[num];//当前方块位置
	int Length = blocks[local.x].size();//木块的数量
	for (int i = local.y + 1; i < Length; i++)
	{
		int current = blocks[local.x][i]; //当前操作的方块
		blocks[current].push_back(current);

		//更新速查表
		poss[current].x = current;
		poss[current].y = blocks[current].size() - 1;
	}
	blocks[local.x].resize(local.y + 1);//重置大小(删除方块堆后面的方块)
}

void MoveAll(int a, int b)
{//将a与a上方的木块移动到b上方
	Pos a_local = poss[a];//获取a的位置
	Pos b_local = poss[b];//获取b的位置
	int Length = blocks[a_local.x].size();//a木块堆的方块数
	for (int i = a_local.y; i < Length; i++)
	{
		int current = blocks[a_local.x][i];
		blocks[b_local.x].push_back(current);

		//更新速查表
		poss[current].x = b_local.x;
		poss[current].y = blocks[b_local.x].size() - 1;
	}
	blocks[a_local.x].resize(a_local.y);
}
```


---

## 作者：Peanut_Tang (赞：4)

这是道大模拟。

每个木块堆高度不定，可以使用C++STL里的不定长数组vector。

其他，没什么了。。。。。注意细节。

Code：
```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#define il inline
using namespace std;

int n;
vector<int> block[30]; 

//返回木块a所在的p 
il int find_p(int a)
{
	int i,j;
	for (i=0; i<n; i++)
	{
		for (j=0; j<block[i].size(); j++)
		{
			if (block[i][j]==a)
			    return i;
		}
	}
}

//返回木块a所在的h 
il int find_h(int a)
{
	int i,j;
	for (i=0; i<n; i++)
	{
		for (j=0; j<block[i].size(); j++)
		{
			if (block[i][j]==a)
			    return j;
		}
	}
}

//把第p堆高为h的木块上面的所有木块移回原位 
il void doing(int p,int h)
{
	int i;
	for (i=h+1; i<block[p].size(); i++)
	{
		int where=block[p][i];
		
		block[where].push_back(where);
	}
	
	block[p].resize(h+1);
}

//把第p堆高度为h的木块及其以上所有木块的整体移到第p2堆的顶端 
il void onto(int p,int h,int pp)
{
	int i;
	for (i=h; i<block[p].size(); i++)
	{
		block[pp].push_back(block[p][i]);
    }
	
	block[p].resize(h);
}

//初始化 
il void init()
{
	scanf("%d",&n);
	
	int i;
	for (i=0; i<n; i++)
	{
		block[i].push_back(i);
	}
}

//解决 
il void solve()
{
	int a,b; string s1,s2;
	while (cin>>s1)
	{
		if (s1=="quit") break;
		
		cin>>a>>s2>>b;
		
		int pa,pb,ha,hb;
		
		pa=find_p(a),ha=find_h(a),
		pb=find_p(b),hb=find_h(b);
		
		if (pa==pb) continue;//非法指令 
		
		if (s2=="onto") doing(pb,hb);
		if (s1=="move") doing(pa,ha);
		
		onto(pa,ha,pb);
	}
}

//输出 
il void print()
{
	int i,j;
	for (i=0; i<n; i++)
	{
		printf("%d:",i);
		
		for (j=0; j<block[i].size(); j++)
		{
			printf(" %d",block[i][j]);
		}
		
		printf("\n");
	}
}

int main()
{
    init();
    solve();
    print();
    
	return 0;
}

```

---

## 作者：1446435502l (赞：3)

写加调试，应该花了将近三个小时……再次感受到了紫书模拟题的威力，用vector模拟这题会稍微好写一点（吧），我来说一下这题需要注意的点。

把a上方的木块放回去，不是像栈那样子从上往下一个一个弹出去，而是从下往上，就是一个整体一样挪过去。例如：1：1 2 4 5 6，2：3，这时需要pile 2 over 3，就应该是 2：3 2 4 5 6，而不是2：3 6 5 4 2，一定要注意看题目（这坑了我好久）。

我用了一个struct去储存每一个木块当前所处的位置，这样需要移动的时候就好操作得多啦！

那剩下的就看我的代码啦，毕竟纯模拟好像需要讲的不多。
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<vector>
#include<string>
using namespace std;
vector<int>v[30];
string s1,s2;
int n,a,b;
struct node
{
	int x,y;
}m[30];//x就是木块处于第几堆，y就是木块处于那堆的第几个 
int main()
{
	ios::sync_with_stdio(false);//关闭同步流 
	cin>>n;
	for(int i=0;i<n;i++)
	{
		v[i].push_back(i);
		m[i]=(node){i,0};
	}
	while(cin>>s1)
	{
		if(s1=="quit")break;
		cin>>a>>s2>>b;
		if(m[a].x==m[b].x)continue;//当同一堆就不要这个操作啦 
		if(s1[0]=='m'&&s2[1]=='n')//第一种操作 
		{
			int len;
			int zhong1=m[a].x;int zhong2=m[a].y; 
			len=v[zhong1].size();
			for(int i=zhong2+1;i<=len-1;i++) //从a的上一个开始，直到该堆的顶，一直推进b堆，记得修改被推元素的位置呀 
			{
				v[v[m[a].x][i]].push_back(v[m[a].x][i]);
				m[v[m[a].x][i]]=(node){v[m[a].x][i],v[v[m[a].x][i]].size()-1};
			}
			for(int i=zhong2+1;i<=len-1;i++)
			{
				v[zhong1].pop_back();
			}
			int zhong3=m[b].x;
			len=v[zhong3].size();
			for(int i=m[b].y+1;i<=len-1;i++)//我觉得可以参考上面那句话吧 
			{
				v[v[m[b].x][i]].push_back(v[m[b].x][i]);
				m[v[m[b].x][i]]=(node){v[m[b].x][i],v[v[m[b].x][i]].size()-1};
			}
			for(int i=m[b].y+1;i<=len-1;i++)
			{
				v[zhong3].pop_back();
			}
			v[m[b].x].push_back(a);//把a放到b啦 
			v[m[a].x].pop_back();
			m[a]=(node){m[b].x,v[m[b].x].size()-1};
		}
		if(s1[0]=='m'&&s2[1]=='v')//这一part的代码可以参考上面的啦 
		{
			int len;
			int zhong1=m[a].x;
			len=v[zhong1].size();
			for(int i=m[a].y+1;i<=len-1;i++)
			{
				v[v[m[a].x][i]].push_back(v[m[a].x][i]);
				m[v[m[a].x][i]]=(node){v[m[a].x][i],v[v[m[a].x][i]].size()-1};
			}
			for(int i=m[a].y+1;i<=len-1;i++)
			{
				v[zhong1].pop_back();
			}
			v[m[b].x].push_back(a);
			v[m[a].x].pop_back();
			m[a]=(node){m[b].x,v[m[b].x].size()-1};
		}
		if(s1[0]=='p'&&s2[1]=='n')
		{
			int len;
			int zhong1=m[b].x;
			len=v[zhong1].size();
			for(int i=m[b].y+1;i<=len-1;i++)//从b开始，一直到顶，不断推回原来的堆 
			{
				v[v[m[b].x][i]].push_back(v[m[b].x][i]);
				m[v[m[b].x][i]]=(node){v[m[b].x][i],v[v[m[b].x][i]].size()-1};
			}
			for(int i=m[b].y+1;i<=len-1;i++)//推了记得弹出那些元素啊 
			{
				v[zhong1].pop_back();
			}
			int zhong2=m[a].x,zhong3=m[a].y;
			len=v[zhong2].size();
			for(int i=zhong3;i<=len-1;i++)
			{
				v[m[b].x].push_back(v[zhong2][i]);
				m[v[zhong2][i]]=(node){m[b].x,v[m[b].x].size()-1};
			}
			for(int i=zhong3;i<=len-1;i++)
			{
				v[zhong2].pop_back();
			}
		}
		if(s1[0]=='p'&&s2[1]=='v')//解释同上哈 
		{
			int zhong1=m[a].x;int zhong2=m[a].y;
			int len=v[zhong1].size();
			for(int i=zhong2;i<=len-1;i++)
			{
				v[m[b].x].push_back(v[zhong1][i]);
				m[v[zhong1][i]]=(node){m[b].x,v[m[b].x].size()-1};
			}
			for(int i=zhong2;i<=len-1;i++)
			{
				v[zhong1].pop_back();
			}
		}
	}
	for(int i=0;i<=n-1;i++)//留意一下输出格式 
	{
		cout<<i<<":";
		for(int j=0;j<v[i].size();j++)
		{
			cout<<" "<<v[i][j];
		}
		cout<<endl;
	}
}
```


---

## 作者：ShineEternal (赞：3)

# 写在前面：如想获得更佳阅读效果，请点击[这里](https://blog.csdn.net/kkkksc03/article/details/84555725)，如有任何疑问，欢迎私信作者交流~

# 题目链接：https://www.luogu.org/problemnew/show/UVA101
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



---

## 作者：XCD_OIworld_rookie (赞：2)

再明白积木世界的操作规律之后，现在就是要思考一下怎样来解决这个问题。

当我看到输出结果的时候，我会想到二维数组。为什么呢？因为每次的输出都要把相对应位置的积木编号输出，总共的行数已知也就是输入时的积木个数（同时积木编号是从0开始，也是方便了二维数组的使用，不必再其中修改序号），另外的原因就是，这四种操作有着一定的规律。

规律：无需考虑将积木放回原位时原位被占的情况，因为没有任何一个操作可以把积木放在空的位置上，因此也不可能出现在第i个位置上，第i个积木的下面有其它积木的情况。可将操作分为两类，一类需要清空上面的积木，一类不需要。

这样就更容易理解题目和操作。

但是在我开始向大家讲我使用二维数组的时候，希望大家自己思考使用不同的解题方法。（不得不承认二维数组实在是太麻烦了）。

那么你在有自己的想法之后，我的二维数组就是一个对过程很具体很细致的描述。你会感觉到二维数组看似很合适其实很麻烦。

下面我就开始讲一下二维数组怎么来解决这个问题。

我们倒着来想，我的结果输出需要序号同时也需要把相对应的积木编号输出来。这样积木中一摞就相当于二维数组的一行，这一点还是很清楚的。所以我们的目的就是进过一次操作之后就把二维数组的每一行进行更新。（这里不是全部行都要更新，只是更新操作中所涉及到的那些摞积木所对应的行）。一定要明白目的是什么，不然下面的分析不是很好懂。

首先我们需要把二维数组进行初始化。二维数组中所存储的是积木的编号。由于题目中给出积木的编号在25之内，所以二维数组的初始化见下：

 

0	INF	INF	INF	INF	...

1	INF	INF	INF	INF	...

2	INF	INF	INF	INF	...

3	INF	INF	INF	INF	...

4	INF	INF	INF	INF	...

...	...	...	...	...	...

其中的INF可以设置为大于25的数字或者负数，关键是能够起到标记该位置没有积木的作用就可以。

 然后就要进行输入操作指令。声明string类型变量s1（move 或pile）,s2（onto或over）.声明int类型start,to分别表示移动积木的编号。

进行指令的判断。

在进行操作之前，我们还需要一个很重要并且很简单很无脑的函数。遍历二维数组找到元素所在位置的行下标和列下标。（自己写find_pos函数来实现找位置）

【每次指令都会调用这个find_pos函数，但是由于题目数据量不是很大，所以速度还是可以的】

（1）如果是move start onto to 类型的指令：

首先需要把start和to上的所有积木全部放回原来的位置。（根据前面的分析，放回原来的位置不需要考虑有没有积木占着这个位置，因为没有积木可以移动到不是自己原来位置的空位上）。然后把start放到to上。利用之前的find_pos函数来找到start的位置，然后使用for循环把这一摞的积木都按照编号放回原来的位置，对于to也是这样的操作。最后只需要把编号为start积木放到编号为to的积木上。（注意在操作过程中一定要把移动的积木后位置初始化为INF）

(2)如果是move start over to 类型指令:

按照上面的操作方法，只需要把start上面的所有积木都放回原来的位置（所谓原来的位置就是编号的积木编号一样的位置）.这时候不需要移动to上面的积木。最后把start积木移动到to积木上。初始化原来start积木位置为INF.

(3)如果是pile start onto to类型指令：

按照上面的操作方法，把to积木上面的积木都初始化，然后这些位置也相应的初始化为INF。然后把start以及start上的所有积木都拿到to积木上，不能改变积木顺序。利用嵌套的for循环加上一定的判断语句很容易实现

(4)如果是pile start over to 类型指令：

需要把start以及start上的积木都拿到to积木着一摞的上面。同样需要在操作中把没有积木的位置初始化为INF。移动一摞积木到另一摞积木的方法类似上面的操作，使用嵌套的for循环加上判断语句。

【注意1】：在移动积木的过程中一定要保持没有积木的位置的值为INF.

【注意2】：由于题目要求如果操作的积木处于同一摞则忽视该操作，同时该操作对积木世界没有任何影响。所以在判定每个指令之后首先要做的就是判断start积木和to积木是否位于同一摞。方法还是调用之前的无脑函数find_pos

利用二维数据求解的参考代码：
```cpp
//by xuchendong_2006	 编程时间： Wed Aug 07 13:26:48 2019

#include<bits/stdc++.h>
using namespace std;
inline void inputread(int &x){
    x=0;int f=1;char c=getchar();
    while(!isdigit(c)){if(!(c-'-'))f=-1;c=getchar();}
    while (isdigit(c))x=(x<<3)+(x<<1)+(c^48),c=getchar();
    x*=f;
}
inline void outputprintf(int x){
    if(!x){putchar('0');return;}
    if(x<0)x=~x+1,putchar('-');
    char c[30]={0};
    while(x)c[++c[0]]=x%10+48,x/=10;
    while(c[0])putchar(c[c[0]--]);
}
#define MAX 30
#define INF 10000000
int MAP[MAX][MAX];
void find_pos(int MAP[MAX][MAX],int n,int temp,int &posx,int &posy)
{
    bool flag=false;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(MAP[i][j]==temp)
            {
                posx=i;
                posy=j;
                flag=true;
                break;
            }
            if(flag==true)
                break;
        }
    }
}
int main()
{
    int n,i,j;
	for(;~scanf("%d",&n);)
    {
        string s1,s2;
        int start,to;
        int posx,posy;
        for(i=0; i<n; i++)
        {
            for(j=0; j<n; j++)
                if(j==0)
                    MAP[i][j]=i;
                else
                    MAP[i][j]=INF;
        }
		for(;cin>>s1;)
        {
            if(s1=="quit")
                break;
            else if(s1=="move")
            {
                cin>>start>>s2>>to;
                if(s2=="onto")
                {
                    int x1,x2;
                    find_pos(MAP,n,start,posx,posy);
                    x1=posx;
                    find_pos(MAP,n,to,posx,posy);
                    x2=posx;
                    if(x1==x2)
                        continue;
                    find_pos(MAP,n,start,posx,posy);
                    for(j=posy+1;j<n;j++)
                    {
                        if(MAP[posx][j]!=INF)
                        {
                            MAP[MAP[posx][j]][0]=MAP[posx][j];
                            MAP[posx][j]=INF;
                        }
                    }
                    MAP[posx][posy]=INF;
                    find_pos(MAP,n,to,posx,posy);
                    for(j=posy+1;j<n;j++)
                    {
                        if(MAP[posx][j]!=INF)
                        {
                            MAP[MAP[posx][j]][0]=MAP[posx][j];
                            MAP[posx][j]=INF;
                        }
                    }
                    MAP[posx][posy+1]=start;
                }
                else if(s2=="over")
                {
                    int x1,x2;
                    find_pos(MAP,n,start,posx,posy);
                    x1=posx;
                    find_pos(MAP,n,to,posx,posy);
                    x2=posx;
                    if(x1==x2)
                        continue;
                    find_pos(MAP,n,start,posx,posy);
                    for(j=posy+1;j<n;j++)
                    {
                        if(MAP[posx][j]!=INF)
                        {
                            MAP[MAP[posx][j]][0]=MAP[posx][j];
                            MAP[posx][j]=INF;
                        }
                    }
                    MAP[posx][posy]=INF;
                    find_pos(MAP,n,to,posx,posy);
                    for(j=posy+1;j<n;j++)
                    {
                        if(MAP[posx][j]==INF)
                        {
                            MAP[posx][j]=start;
                            break;
                        }
                    }
                }
            }
            else if(s1=="pile")
            {
                cin>>start>>s2>>to;
                if(s2=="onto")
                {
                    int x1,x2;
                    find_pos(MAP,n,start,posx,posy);
                    x1=posx;
                    find_pos(MAP,n,to,posx,posy);
                    x2=posx;
                    if(x1==x2)
                        continue;
                    find_pos(MAP,n,to,posx,posy);
                    for(j=posy+1;j<n;j++)
                    {
                        if(MAP[posx][j]!=INF)
                        {
                             MAP[MAP[posx][j]][0]=MAP[posx][j];
                             MAP[posx][j]=INF;
                        }
                    }
                    int tempx=posx,tempy=posy;
                    find_pos(MAP,n,start,posx,posy);
                    for(j=tempy+1;j<n;j++)
                    {
                        for(int j2=posy;j2<n;j2++)
                        {
                            if(MAP[posx][j2]!=INF)
                            {
                                MAP[tempx][j]=MAP[posx][j2];
                                MAP[posx][j2]=INF;
                                break;
                            }
                        }
                    }
                }
                else if(s2=="over")
                {
                    int x1,x2;
                    find_pos(MAP,n,start,posx,posy);
                    x1=posx;
                    find_pos(MAP,n,to,posx,posy);
                    x2=posx;
                    if(x1==x2)
                        continue;
                    find_pos(MAP,n,to,posx,posy);
                    int tempx=posx,tempy=posy;
                    for(j=posy;j<n;j++)
                    {
                        if(MAP[tempx][j]==INF)
                        {
                            tempy=j;
                            break;
                        }
                    }
                    find_pos(MAP,n,start,posx,posy);
                    for(j=tempy;j<n;j++)
                    {
                        for(int j2=posy;j2<n;j2++)
                        {
                            if(MAP[posx][j2]!=INF)
                            {
                                MAP[tempx][j]=MAP[posx][j2];
                                MAP[posx][j2]=INF;
                                break;
                            }
                        }
                    }
                }
            }
        }
        for(i=0;i<n;i++)
        {
            printf("%d:",i);
            for(j=0;j<n;j++)
            {
                if(MAP[i][j]!=INF)
                {
                    printf(" %d",MAP[i][j]);
                }
            }
            printf("\n");
        }
    }
}
```


---

## 作者：Law_Aias (赞：2)

# 一个大模拟！！！
总的来说就是碰到ｍｏｖｅ就要把ａ上面的全部放回原处。

如果碰到　ｏｎｔｏ　就要把ｂ上面的全部放到原处。
因为ｍｏｖｅ是只移动ａ一个，所以ａ上面的要归位，而ｐｉｌｅ是移一堆，所以不用。

ｏｎｔｏ是要和ｂ贴在一起，所以ｂ上面的要归位，而ｏｖｅｒ是上方，不需要直接接触，所以不用。。

思路就是用栈来模拟，一开始就是ｎ个栈。每个栈里都是一个元素，然后按照指令移，在这个栈里ｐｏｐ（）掉它，在另一个栈里ｐｕｓｈ（）进去。。
分四种情况来做移动，每种情况处理方式不一样。要注意如果是一堆移过去，因为还是要按照这个顺序，多以要先把这一堆放到另一个数组，再按顺序ｐｕｓｈj进去。
模拟完输出即可。。

## CODE：
```cpp
#include<iostream>  
#include<cstdio>  
#include<string>  
#include<stack>  

using namespace std;  

stack <int> sta[100];  
int t,num[100];  
int res[100];  
string m1,m2;  
int p1,p2;  
  
int main () {  
    cin >> t;  
    getchar();  
    for( int i = 0; i < t ;i++) {  
        sta[i].push(i);  
        num[i] = i;  
  
    }  
    while(1) {  
        cin >> m1;  
        if(m1 == "quit")  
            break;  
        cin >>p1 >>m2 >>p2;  
        if (num[p1] == num[p2])  
            continue;  
        if (m1 == "move" && m2 == "over") {  
            for (;sta[num[p1]].top() != p1; ) {  
                sta[ sta[num[p1]].top() ].push(sta[num[p1]].top());   
                num[sta[num[p1]].top()] = sta[num[p1]].top();  
                sta[num[p1]].pop();  
            }  
            sta[num[p2]].push(p1);  
            sta[num[p1]].pop();  
            num[p1] = num[p2];  
        }  
        if (m1 == "pile" && m2 == "over") {  
            int k = 0;  
            int temp[200];  
            for (;sta[num[p1]].top() != p1; ) {  
                temp[k++] = sta[num[p1]].top();  
                num[sta[num[p1]].top()] = num[p2];  
                sta[num[p1]].pop();  
            }  
            sta[num[p1]].pop();  
            temp[k] = p1;  
            num[p1] = num[p2];  
            for(int w = k ;w >= 0; w--)  
                sta[num[p2]].push(temp[w]);  
        }  
        if (m1 == "move" && m2 == "onto") {  
            for (;sta[num[p1]].top() != p1; ) {  
                sta[ sta[num[p1]].top() ].push(sta[num[p1]].top());   
                num[sta[num[p1]].top()] = sta[num[p1]].top();  
                sta[num[p1]].pop();  
            }  
            for (;sta[num[p2]].top() != p2; ) {  
                sta[ sta[num[p2]].top() ].push(sta[num[p2]].top());   
                num[sta[num[p2]].top()] = sta[num[p2]].top();  
                sta[num[p2]].pop();  
            }  
            sta[num[p2]].push(sta[num[p1]].top());  
            sta[num[p1]].pop();  
            num[p1] = num[p2];  
        }  
        if (m1 == "pile" && m2 == "onto") {  
            int k = 0;  
            int temp[200];  
            for (;sta[num[p1]].top() != p1; ) {  
                temp[k++] = sta[num[p1]].top();  
                num[sta[num[p1]].top()] = num[p2];  
                sta[num[p1]].pop();  
            }  
            sta[num[p1]].pop();  
            temp[k] = p1;  
            num[p1] =num[p2];  
            for (;sta[num[p2]].top() != p2; ) {  
                sta[ sta[num[p2]].top() ].push(sta[num[p2]].top());   
                num[sta[num[p2]].top()] = sta[num[p2]].top();  
                sta[num[p2]].pop();  
            }  
            for(int w = k ;w >= 0; w--)  
                sta[num[p2]].push(temp[w]);  
          
        }  
    }  
    int j;  
    for(int i = 0;i < t;i++) {  
        cout << i <<":";  
        for( j = 0 ;!sta[i].empty();j++) {  
            res[j] =  sta[i].top();  
            sta[i].pop();  
        }  
        for (j = j -1; j >= 0;j--)  
            cout<<" "<<res[j];  
        cout << endl;  
    }  
    return 0;  
}  



```

---

## 作者：Praise_sincerity (赞：2)

# 分析
## 每个木块堆的高度不确定，所以用vector来保存很合适；而木块堆的个数不超过n，所以用一个数组来存就可以了。代码如下：
```c
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;

const int maxn=30;
int n;
vector<int> pile[maxn];   //每个pile[i]是一个vector 

//找木块a所在的pile和height，以引用的形式返回调用者 
void find_block(int a,int& p,int& h)   
{
	for(p=0;p<n;p++)
	for(h=0;h<pile[p].size();h++)
	if(pile[p][h]==a)
	return ;
}

//把第p堆高度为h的木块上方的所有木块移回原位 
void clear_above(int p,int h)
{
	for(int i=h+1;i<pile[p].size();i++)
	{
		int b=pile[p][i];
		pile[b].push_back(b);     //把木块b放回原位 
	}
	pile[p].resize(h+1);          //pile只应保留下标0~h的元素 
}

//把第p堆高度为h及其上方的木块整体移动到p2堆的顶部 
void pile_onto(int p,int h,int p2)
{
	for(int i=h;i<pile[p].size();i++)
	pile[p2].push_back(pile[p][i]);
	pile[p].resize(h);
}

void print()
{
	for(int i=0;i<n;i++)
	{
		printf("%d:",i);
		for(int j=0;j<pile[i].size();j++)
		printf(" %d",pile[i][j]);
		printf("\n");
	}
}

int main()
{
    int a,b;
	cin>>n;
	string s1,s2;
	for(int i=0;i<n;i++)
	pile[i].push_back(i);
	while(cin>>s1>>a>>s2>>b)
	{
		int pa,pb,ha,hb;
		find_block(a,pa,ha);
		find_block(b,pb,hb);
		if(pa==pb)
		continue;         //非法指令 
		if(s2=="onto")
		clear_above(pb,hb);
		if(s1=="move")
		clear_above(pa,ha);
		pile_onto(pa,ha,pb);
	}
	print();
	return 0;
}
```
## 数据结构的核心是vector<int>pile[maxn],所有的操作都是围绕它进行的。vector就像是一个二维数组，只是第一维的大小是固定的（不超过maxn），但第二维的大小不固定。

---

## 作者：Times_New_man (赞：1)

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

