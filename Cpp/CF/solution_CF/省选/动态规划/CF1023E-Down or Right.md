# Down or Right

## 题目描述

这是一个交互题。

Bob 住在一个 $n \times n$ 的正方形网格中，行编号从上到下为 $1$ 到 $n$，列编号从左到右为 $1$ 到 $n$。每个格子要么是允许通过的，要么是被阻塞的，但你并不知道网格的具体情况。你只知道一个整数 $n$。

Bob 只能在允许通过的格子中移动，并且只能向下或向右移动到相邻的格子（前提是该格子允许通过）。

你最多可以询问 $4 \cdot n$ 次，询问的格式为 "? $r_1$ $c_1$ $r_2$ $c_2$"（$1 \le r_1 \le r_2 \le n$，$1 \le c_1 \le c_2 \le n$）。如果 Bob 能够从格子 $(r_1, c_1)$ 走到格子 $(r_2, c_2)$，则回答为 "YES"；否则回答为 "NO"。特别地，如果两个格子中有任意一个是被阻塞的，那么答案一定是 "NO"。由于 Bob 不喜欢短距离旅行，你只能询问曼哈顿距离不少于 $n-1$ 的两点对，即必须满足 $(r_2 - r_1) + (c_2 - c_1) \ge n - 1$。

保证 Bob 一定可以从左上角 $(1, 1)$ 走到右下角 $(n, n)$，你的任务是找到一条这样的路径。你需要以 "! S" 的形式输出答案，其中 $S$ 是一个长度为 $2n-2$ 的字符串，仅包含字符 'D' 和 'R'，分别表示向下和向右移动。向下移动会使第一维加 $1$，向右移动会使第二维加 $1$。如果有多种方案，任意一种都可以。输出答案后应立即结束程序。

## 说明/提示

第一个样例如下图所示。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1023E/5c73703184bd02b7d0f8ba7f8a384569ae4b95fb.png)

对于 hack 数据，输入格式如下：

第一行包含一个整数 $n$（$2 \le n \le 500$），表示网格的大小。

接下来的 $n$ 行，每行包含 $n$ 个字符，'#' 表示被阻塞的格子，'.' 表示允许通过的格子。

例如，下面的文本描述了上图的样例：

```
4
..#.
#...
###.
....
```

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
 
YES
 
NO
 
YES
 
YES
 
```

### 输出

```
 
? 1 1 4 4
 
? 1 2 4 3
 
? 4 1 4 4
 
? 1 4 4 4
 
! RDRRDD
```

# 题解

## 作者：mango2011 (赞：1)

简单交互题。

首先，我们发现一个很简单的方法：

我们可以从结束点 $(n,n)$ 倒着找，看看每一次能不能走到 $(1,1)$，但是有一个问题，就是会出现 $(x1-x2)+(y1-y2)<n-1$ 的情况，所以我们考虑修一下这个做法：

把整个网格按照对角线分成左右（也可说是上下）两个部分，这样有什么好处呢？好处就是我们只需要左边的问 $(n,n)$，右边的问 $(1,1)$，就可以保证 $(x1-x2)+(y1-y2)\ge n-1$。

但是这样也有一个问题（详见 Test #6）：我们发现这样一找，有可能 $(x,y)$ 可以到 $(n,n)$ 但是 $(1,1)$ 到不了 $(x,y)$，从而引发 WA 或 TLE！这个问题怎么修复呢？

我们已经分成两半了，就彻底一点：

先从 $(n,n)$ 开始找，我们一定能在对角线上找到一个点 $(x,y)$，使得 $(1,1)$ 能走到 $(x,y)$；再从 $(1,1)$ 开始找（始终保证当前位置与 $(n,n)$ 连通），在横纵位置不超过 $(x,y)$ 的情况下去找到与 $(x,y)$ 重合的 $(x_1,y_1)$ 就可以了，显然，我们总是可以找到的。
注意询问过程中要记录怎么走。

询问次数？容易发现是 $2n-2$ 次，远远低于题目限制，于是我们就做完了！

---

## 作者：DJRzjl (赞：1)

# [CF1023E](https://www.luogu.com.cn/problem/CF1023E)  Down or Right$~~~$

从左上走到右下，总共要走 $2(n-1)$​ 步，而题目要求询问次数上限为 $4n$，这提示我们每走一步后需要通过 $2$ 次询问判断出下一步应该往哪走，向下还是向右。

如果在现在在 $(x,y)$​​，询问 `? x+1 y n n` 和 `? x y+1 n n` 就可以确定下和右哪边可以走，但询问还需要满足两点之间曼哈顿距离大于等于 $n-1$​​，所以这样询问最多走到对角线（指左下—右上，下同）上，此时离 $(n,n)$ 曼哈顿距离等于 $n-1$ ，就不能再这样询问得到下一步了。

到达对角线后，我们会发现很难确定下一步方向了，所以我们应该换一种思考方式，如果考虑从终点走回起点，那么我们仍然可以用类似之前的方式得到一条从终点走到对角线的路线，也就是假设现在在 $(x,y)$​，询问 `? 1 1 x-1 y` 和 `? 1 1 x y-1` 从而确定往回走的方向。

虽然我们已经可以在 $4n$ 次询问内找到从起点和终点两个方向到达对角线上的路线，但怎么保证它们能构成一条连续的路呢？也就是说，还需要使起点和终点到达对角线上的位置是同一个点。

这很好做到，我们仅需要在从前往后找路的过程中优先判断是否可以往右走，在从后往前找过程中优先往上走，这样如果起点到终点有多条路交对角线于多个交点，那么前半段与后半段找到的路一定会在对角线的最靠近右上方的交点处重合。

事实上，因为只有两种走法，我们在询问下一步时只用询问一次，所以在 $2n$​ 次询问以内就可以解决问题。

## code
```cpp
#include<bits/stdc++.h>
#define x1 x11
#define x2 x22
#define y1 y11
#define y2 y22
using namespace std;


bool ask(int x1,int y1,int x2,int y2){
	printf("? %d %d %d %d\n",x1,y1,x2,y2);
	fflush(stdout);
	char fl[10];
	scanf("%s",fl);
	if(fl[0]=='Y') return true;
	else return false;
}
string ans,anss;
int n;

int main(){
	scanf("%d",&n);
	int px=1,py=1;
	for(int i=1;i<n;i++){
		if(py<n&&ask(px,py+1,n,n)) ans+='R',py++;
		else ans+='D',px++;
	}
	px=n,py=n;
	for(int i=1;i<n;i++){
		if(px>1&&ask(1,1,px-1,py)) anss+='D',px--;
		else anss+='R',py--;
	}
	printf("! ");
	reverse(anss.begin(),anss.end());
	cout<<ans<<anss<<endl;
	fflush(stdout);
	return 0;
}
```


---

## 作者：skyskyCCC (赞：0)

## 前言。
神神奇奇交互题。
## 分析。
既然他们要让我们找到一条通路，不难想到搜索，但是可惜这道题是一个交互题，所以我们需要手动模拟一下 DFS 的寻路过程。

如果我们现在到了一个点，则我们根据题意，只有两种选择，即下行或右行，那我们就可以询问，从当前节点出发，它的右边的一个节点是否可达目的地，如果可以走右边，如果不行就走下面。

此时我们只需要询问 $2n-2$ 次就可以得到答案。

那么我们怎么模拟寻路呢？我们可以考虑先找一个路径，然后再找一个路径，一个从 $\left(1,1\right)$ 开始寻找，我们命名它为路径 $A$。一个从 $\left(n,n\right)$ 开始寻找，我们命名它为路径 $B$。题目说要求询问的点的距离不低于 $n-1$ 所以路径 $A$ 相当于从开始的节点，遍历到 $n-1$ 个节点终止，此时找到当前的一半路径。然后同理，路径 $B$ 就是从终止点出发，遍历到距离为 $n-1$ 的节点即可，此时就找到了另外一半的路径。

最后的一个问题就是，我们如何保证这两条路径接在一起呢？因为保证有一个答案，所以只要正我们寻找路径 $A$ 的时候，保证先右后下，寻找路径 $B$ 的时候，保证先上后左，就一定能接在一起。

代码如下，仅供参考：
```
#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cmath>
using namespace std;
int n;
int x=1,y=1,sum;
char ans[200005];
string now;
bool cheak(int xx,int yy,int st,int ls){
	cout<<"? "<<xx<<" "<<yy<<" "<<st<<" "<<ls<<"\n";
	fflush(stdout);
	cin>>now;
	if(now=="YES"){
		return 1;
	}
	else return 0;
}
int dis(int x11,int y11,int x22,int y22){
	return abs(x11-x22)+abs(y11-y22);
}
int main(){
	cin>>n;
	while(dis(x,y,n,n)>=n){
		if(y+1<=n&&cheak(x,y+1,n,n)){
			//cout<<"qwq\n";
			y++;
			sum++;
			ans[sum]='R';
		}
		else{
			x++;
			sum++;
			ans[sum]='D';
		}
	}
	sum=2*n-1;
	x=y=n;
	while(dis(x,y,1,1)>=n){
		if(x-1>0&&cheak(1,1,x-1,y)){
			//cout<<"yep!\n";
			x--;
			sum--;
			ans[sum]='D';
		}
		else{
			y--;
			sum--;
			ans[sum]='R';
		}
	}
	for (int i=1;i<=2*n-2;i++){
		if(i==1){
			cout<<"! ";
		}
		//cout<<i<<" ";
		cout<<ans[i];
		//cout<<"\n";
	}
	return 0;
}
```
## 分析。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：小闸蟹 (赞：0)

```cpp
// 交互题
#include <iostream>
#include <string>
#include <algorithm>

// 询问从(x, y)能否到达(n, m)
bool Ask(int x, int y, int n, int m)
{
    std::cout << "? " << x << ' ' << y << ' ' << n << ' ' << m << std::endl;
    std::fflush(stdout);

    std::string s;
    std::cin >> s;
    std::fflush(stdout);
    if (s.front() == 'Y')
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
    int n;
    std::cin >> n;
    std::fflush(stdout);

    std::string s1, s2;
    int x = 1, y = 1;   // 首先从前往后走
    for (int i = 0; i < n - 1; ++i)
    {
        if (y < n && Ask(x, y + 1, n, n))
        {
            ++y;
            s1.push_back('R');
        }
        else
        {
            ++x;
            s1.push_back('D');
        }
    }

    x = n;
    y = n;  // 然后再从后往前走
    for (int i = 0; i < n - 1; ++i)
    {
        if (x > 1 && Ask(1, 1, x - 1, y))
        {
            --x;
            s2.push_back('D');
        }
        else
        {
            --y;
            s2.push_back('R');
        }
    }

    std::reverse(s2.begin(), s2.end()); // 由于从后往前走是反过来的，这里要反回去
    std::cout << "! " << s1 + s2 << std::endl;

    return 0;
}
```

---

