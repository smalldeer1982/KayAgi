# King Escape

## 题目描述

艾丽丝和鲍勃正在一个n*n大棋盘上下棋。爱丽丝只剩下一个皇后，位于(a_x，a_y)，而鲍勃只有一个国王，位于(b_x，b_y)。爱丽丝认为，她的皇后是主宰棋盘的，所以胜利是属于她的。但是鲍勃已经制定了一个计划来赢得胜利，他需要移动国王到(c_x，c_y)，以便为自己争取胜利。当爱丽丝被她的自信所分心时，她将不会移动他的皇后，只有鲍勃才能进行移动。如果鲍勃能把他的国王从(b_x，b_y)移到(c_x，c_y)，他就会赢。请记住，国王可以移动到任何8个相邻的棋格。如果国王与皇后处于同一行、同一列或同一对角线，则将所到攻击。看看鲍勃能不能赢。

## 样例 #1

### 输入

```
8
4 4
1 3
3 1
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
8
4 4
2 3
1 6
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
8
3 5
1 2
6 1
```

### 输出

```
NO
```

# 题解

## 作者：yzh_Error404 (赞：3)

### 题意
给你一个$n*n$的棋盘，$(a_x,a_y)$上有一个皇后（不移动），处于$(b_x,b_y)$的国王想移动到$(c_x,c_y)$，问这个国王能不能到达

### 题解

先看图：

![](https://cdn.luogu.com.cn/upload/image_hosting/4reptxnj.png?x-oss-process=image/resize,m_lfit,h_170,w_225)
$\implies$![](https://cdn.luogu.com.cn/upload/image_hosting/p3v2xss7.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

可以发现，皇后只能控制它上下左右的格子(浅绿色)，并且将整个棋盘分成了四块（深绿色框）

如果国王和目标点在同一个区块中，国王一定能到达目标点，所以直接判断一下国王和目标点的位置即可

上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ax,ay,bx,by,cx,cy;
int main()
{
	scanf("%d%d%d%d%d%d%d",&n,&ax,&ay,&bx,&by,&cx,&cy);
	if(bx<ax&&by<ay&&cx<ax&&cy<ay){puts("YES");return 0;}
	if(bx>ax&&by<ay&&cx>ax&&cy<ay){puts("YES");return 0;}
	if(bx<ax&&by>ay&&cx<ax&&cy>ay){puts("YES");return 0;}
	if(bx>ax&&by>ay&&cx>ax&&cy>ay){puts("YES");return 0;}
	puts("NO");
	return 0;
}
```

~~深搜是不可能深搜的，这辈子都不可能深搜的~~

---

## 作者：yazzkl (赞：3)


## 法一：深搜（~~不讲了~~）,还行
## 法二：建！立！直！角！坐！标！系！
### 以(ax,ay)为原点建立直角坐标系

因为要检查是在同一等级，国王只能在该象限内运动。

只需要看国王移动的起点与终点是否在同一象限内即可。

接下来判断象限，，就很简单了。。

```
#include <bits/stdc++.h>
#include<string>
using namespace std;
int main()
{
    int n,ax,ay,bx,by,cx,cy;
    cin>>n>>ax>>ay>>bx>>by>>cx>>cy;
    if((bx<ax && cx>ax)||(bx>ax && cx<ax)||(by>ay && cy<ay)||(by<ay && cy>ay))
       cout<<"NO";
    else
        cout<<"YES";
}
```
就轻轻松松解决一道蓝题。。

这里，强烈推荐建系，在几何题里虽然计算麻烦，但是实用性强（~~也不要看到题，就建系~~）

---

## 作者：hhrq (赞：2)

老规矩，先来审题。

棋盘为$n * n$ 大小， $a_x a_y$为皇后的位置， $b_x，b_y$为国王的位置， 国王需要移到$c_x, c_y$。国王可以移动到任何8个相邻的棋格。如果国王与皇后处于同一行、同一列或同一对角线，则将所到攻击。判断国王的胜负。

再来看一下样例的图片：
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1033A/e1724c6b8b5ec4aee00605b5e9263ab174895bb4.png)

我们可以看到， 红色的方块为国王不可以走的地方， 于是就出现了一种思路：定义一个$bool$二维数组，$ 0$为可以走， $1$为不能走 。

```
int dx[8] = {1, 1, 1, 0, 0, -1, -1, -1};
int dy[8] = {1, 0, -1, 1, -1, 1, 0, -1};

for(int i = 1;i <= n;i++)
{
	map[ax][i] = true;//纵向
	map[i][ay] = true;//横向
	if(ax - i >= 1 && ay + i <= n) map[ax - i][ay + i] = 1;//四个斜向
	if(ax + i <= n && ay - i >= 1) map[ax + i][ay - i] = 1;
	if(ax + i <= n && ay + i <= n) map[ax + i][ay + i] = 1;
	if(ax - i >= 1 && ay - i >= 1) map[ax - i][ay - i] = 1; 
}
```

记录之后， 进行深搜：

```
void dfs(int x, int y)//当前搜索的坐标
{
	if(x == cx && y == cy) //抵达终点直接返回
	{
		flag = 1;//记录是否到达， 1为到达
		return;
	}
	map[x][y] = 1;//走过位置不再走
	for(int i = 0;i <= 7;i++)
	{
		int x_new = x + dx[i], y_new = y + dy[i];//搜索周围八个方块
		if(!map[x_new][y_new] && x_new >= 1 && y_new >= 1 && x_new <= n && y_new <= n)
		{
			dfs(x_new, y_new);//可以走就继续搜索
		}
	}
}
```

最后判断$flag$的值， $1$则输出$YES$, $0$ 则输出$NO$。

下面是完整代码
```
#include<cstdio>
#include<iostream>
using namespace std;

int n, ax, ay, bx, by, cx, cy;
bool flag, map[1005][1005];//0为可以走，1为不能走 
int dx[8] = {1, 1, 1, 0, 0, -1, -1, -1};
int dy[8] = {1, 0, -1, 1, -1, 1, 0, -1};

void dfs(int x, int y)
{
	if(x == cx && y == cy) 
	{
		flag = 1;
		return;
	}
	map[x][y] = 1;
	for(int i = 0;i <= 7;i++)
	{
		int x_new = x + dx[i], y_new = y + dy[i];
		if(!map[x_new][y_new] && x_new >= 1 && y_new >= 1 && x_new <= n && y_new <= n)
		{
			dfs(x_new, y_new);
		}
	}
}

int main()
{
	cin >> n >> ax >> ay >> bx >> by >> cx >> cy;
	for(int i = 1;i <= n;i++)
	{
		map[ax][i] = true;
		map[i][ay] = true;
		if(ax - i >= 1 && ay + i <= n) map[ax - i][ay + i] = 1;
		if(ax + i <= n && ay - i >= 1) map[ax + i][ay - i] = 1;
		if(ax + i <= n && ay + i <= n) map[ax + i][ay + i] = 1;
		if(ax - i >= 1 && ay - i >= 1) map[ax - i][ay - i] = 1; 
	}
	dfs(bx, by);
	if(flag == 1) cout << "YES" << endl;
	else cout << "NO" << endl;
	return 0;
}

```

---

## 作者：alex_liu (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1033A)

# 思路：
由于国王可以向斜方向走，那么皇后的斜向障碍就没有用了：

（ K 为当前国王的位置， Q  为皇后的控制区域， N  为国王下一步要走的位置， O  为空格）

| K | Q |
|:----------:|:----------:|
| Q | N |


这样子斜着走就可以过去

但是这样子就过不去了：

| K | Q | O |
| :----------: | :----------: | :----------: |
| O | Q | O |
| O | Q | N |

所以我们可以建立一个坐标系，设皇后的位置为原点，如果国王当前的位置与要去到的位置在同一个 [象限](https://baike.so.com/doc/5702880-5915597.html) 内，就可行（满足以下四种情况中的一个），否则不行（不满足以下四种情况）：

1. 在第一象限内，则：

` ax<bx&&ax<cx&&ay>by&&ay>cy `

2. 在第二象限内，则：

` ax>bx&&ax>cx&&ay>by&&ay>cy `

3. 在第三象限内，则：

` ax<bx&&ax<cx&&ay<by&&ay<cy `

4. 在第四象限内，则：

` ax>bx&&ax>cx&&ay<by&&ay<cy `

那就用四个函数去判断这四个条件，有一个为  true 则输出 "  YES  " ；四个都为  false  则输出 "  NO  "

# 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ax,ay,bx,by,cx,cy;
bool check1(){//第一象限
	if(ax<bx&&ax<cx&&ay>by&&ay>cy)return true;
	else return false;
}
bool check2(){//第二象限
	if(ax>bx&&ax>cx&&ay>by&&ay>cy)return true;
	else return false;
}
bool check3(){//第三象限
	if(ax<bx&&ax<cx&&ay<by&&ay<cy)return true;
	else return false;
}
bool check4(){//第四象限
	if(ax>bx&&ax>cx&&ay<by&&ay<cy)return true;
	else return false;
}
int main(){
	cin>>n>>ax>>ay>>bx>>by>>cx>>cy;//输入
	if(check1()||check2()||check3()||check4())cout<<"YES"<<endl;//判断
	else cout<<"NO"<<endl;
	return 0;//结束程序
}
```


---

## 作者：MasQx (赞：0)

一开始做的时候当成dfs搜了半天，但1000*1000的棋盘面积大小让我放弃了这个念头。

仔细看题后发现，王是可以斜的走的，也就是说王可以从王后斜的攻击路线的空隙内穿过

![](https://cdn.luogu.com.cn/upload/image_hosting/lkgmxv1x.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

（如图，红色为皇后攻击范围，黑色箭头代表王行动路线）

所以我们从中可以得出，王后斜着的4条斜线其实并没有什么用

也就是说，王后一横一竖聊天攻击范围将整张棋盘分为了四个部分（王不能跨过一部分到另一部分，否则将会被王后攻击）

所以我们只需要判断起点和终点是否在同一部分内就行，时间复杂度 $O(1)$

附上代码：

```cpp

#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,ax,ay,bx,by,cx,cy,a[1001][1001];
signed main()
{
    cin>>n>>ax>>ay>>bx>>by>>cx>>cy;
    if((bx<ax&&by<ay&&cx<ax&&cy<ay)||
       (bx<ax&&by>ay&&cx<ax&&cy>ay)|| 
       (bx>ax&&by<ay&&cx>ax&&cy<ay)||
       (bx>ax&&by>ay&&cx>ax&&cy>ay))//判断是否在同一部分内
       printf("YES");
    else
       printf("NO");
}//第一次写题解，码风不好勿喷
```



---

## 作者：きりと (赞：0)

**[题目传送门](https://www.luogu.com.cn/problem/CF1033A)**

### 题目大意

见中文翻译

### 解题思路

我们可以沿着皇后的攻击范围将整个棋盘分成$8$部分，然后只要判断起点和终点是否在一个部分里就好……

**了吗？**

**你确定吗？**

![](https://cdn.luogu.com.cn/upload/image_hosting/x20cw143.png?x-oss-process=image/resize,m_lfit,h_170,w_225)



如图所示，黑色格子表示皇后的对角线攻击范围，显然，王是**能斜走走过对角线**的，也就是说，皇后的**对角线攻击范围只是摆设**



那么我们去掉皇后对角线的攻击范围，然后判断即可。

### 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
signed main()
{
	ios::sync_with_stdio(0);
	int n;
	cin>>n;
	int ax,ay,bx,by,cx,cy;
	cin>>ax>>ay>>bx>>by>>cx>>cy;
	if(((ax>bx)&&(ax<=cx))||((ax<bx)&&(ax>=cx)))
	{
		cout<<"NO"<<endl;
		return 0;
	}
	if(((ay>by)&&(ay<=cy))||((ay<by)&&(ay>=cy)))
	{
		cout<<"NO"<<endl;
		return 0;
	}
	cout<<"YES"<<endl;
	return 0;
}
```



---

## 作者：洛璟 (赞：0)

## Solution:

蓝题？不至于，顶多黄题。

一开始大家肯定都想到了暴搜，而事实证明暴搜也是可以过的，~~那么这个题解完结力~~那么我现在来讲一讲一个~~离谱的~~做法，时间复杂度为 $O(1)$

首先我们其实不难想到，国王无论如何也无法逾越皇后的纵横的攻击范围，于是我们首先就出了一个判断，如果国王和目标点隔了皇后的横纵攻击范围，那么就是NO。

那我们再考虑去“建系”，即以皇后为原点，建立一个平面直角坐标系，如果国王和目标点不在同一个象限内，则为NO。

那如果再同一个象限内呢？

皇后的对角线是可以轻易被逾越的，可以手动进行模拟，这应该很快就可以得出来，他根本无法阻挡国王，只要国王不断前进，就会离终点越来越近，因此，~~不要停下来啊~~我们可以直接忽略对角线，也就是说只要起点和终点在同一象限内，即为YES。

那么代码就极为简单了，只要判断两个点是否在坐标系同一象限内即可力。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int ax, ay, bx, by, cx, cy;
inline int read()
{
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c>'9')
    {
        if (c == '-') f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
    {
        x = (x << 3) + (x << 1) + (c ^ '0');
        c = getchar();
    }
    return x * f;
}

int main()
{
    n = read();
    ax = read();
    ay = read();
    bx = read();
    by = read();
    cx = read();
    cy = read();
    if ((bx <= ax && cx < ax && by >= ay && cy > ay) || (bx >= ax && cx > ax && by >= ay && cy > ay) || (bx <= ax && cx < ax && by <= ay && cy < ay) || (bx >= ax && cx > ax && by <= ay && cy < ay))
    {
        printf("YES");
    }
    else printf("NO");
    return 0;
}

```


---

## 作者：灵光一闪 (赞：0)

这题感觉属于BFS，可是……看完题后……这是BFS？？？

王后的放射范围：
```
*.*.*
.***.
**q**
.***.
*.*.*
```

可是，因为是8联通，所以……王后的封锁范围：
```
..*..
..*..
*****
..*..
..*..
```
所以说，只要目标和国王所在的位置在一起，就绝对能赢 ~~（当然现实中不可能的~~ 

code：
```
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<cstdio>

using namespace std;
struct point{
    int x,y;
};
int q,w;
point a[3];
int main(){
    int n;
    cin>>n;
    for(int i=0;i<3;i++){
        cin>>a[i].x>>a[i].y;
    }
    if(a[0].x>a[1].x&&a[0].y>a[1].y){//判断国王在哪块
        q=1;
    }
    else if(a[0].x<a[1].x&&a[0].y>a[1].y){
        q=2;
    }
    else if(a[0].x>a[1].x&&a[0].y<a[1].y){
        q=3;
    }
    else{
        q=4;
    }
    if(a[0].x>a[2].x&&a[0].y>a[2].y){//目标
        w=1;
    }
    else if(a[0].x<a[2].x&&a[0].y>a[2].y){
        w=2;
    }
    else if(a[0].x>a[2].x&&a[0].y<a[2].y){
        w=3;
    }
    else{
        w=4;
    }
    if(q==w){//在同一块就是YES
        puts("YES");
    }
    else{//不然NO
        puts("NO");
    }
    return 0;
}
```

---

