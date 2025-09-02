# Cooperative Game

## 题目描述

这是一个交互题。

Misha 喜欢玩不完全信息的合作游戏。今天他邀请了他的十位朋友一起玩一个名为“湖泊”的合作游戏。

Misha 已经为即将到来的游戏设计好了场地。这个场地是一个有向图，由两部分组成。第一部分是沿湖岸的一条道路，这条道路是一个包含 $c$ 个顶点的环。第二部分是从家到湖边的一条路径，这条路径是一个包含 $t$ 个顶点的链，并且这条链的最后一个顶点有一条边指向湖岸道路上风景最美的顶点，也就是终点顶点。Misha 决定对场地保密，因此没有人知道 $t$ 和 $c$ 的具体数值。

注意，场地中的每个顶点恰好有一条出边，除了家和终点顶点外，其他所有顶点恰好有一条入边。家顶点没有入边，终点顶点有两条入边。

游戏开始时，所有十位玩家的棋子（编号为 $0$ 到 $9$ 的连续整数）都在家顶点。之后，每一回合，部分玩家可以请求 Misha 同时将他们的棋子沿着对应的边移动。Misha 最多会回答 $q$ 次这样的请求。每次移动后，Misha 会告诉玩家哪些棋子在同一个顶点，哪些棋子在不同的顶点。

游戏的目标是将所有棋子移动到终点顶点。Misha 的朋友们并不知道如何在不知道 $c$、$t$ 和 $q$ 的情况下获胜，但幸运的是他们有你这个朋友。请帮助他们：协调他们的行动以赢得游戏。

Misha 设计的场地满足 $1 \le t, c$，且 $t+c \leq 1000$，并且 $q = 3 \cdot (t+c)$。

## 说明/提示

样例输入输出的对齐仅为便于按时间顺序理解。在实际交互中，不应出现“额外”的换行。

在示例中，朋友们的移动如下所示：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1137D/49a5c12b9834889c7b07dbaecbdc8d9c67955b2f.png)

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2 05 12346789

3 246789 135 0

3 246789 0 135

3 246789 0 135

2 135 0246789

1 0123456789
```

### 输出

```
next 0 5

next 0 1 3

next 2 3 0 1 4 5 6 7 8 9

next 9 8 7 6 5 4 3 2 1 0

next 0 1 3 5

next 1 3 5

done```

# 题解

## 作者：Jμdge (赞：5)

# 题意

有一张有向图，由一条长度为 T 的链和一个长度为 C 环组成，但是你并不知道 T 和 C 是多少

图的出发点在链的一段，终点在链的另一端，同时终点与一个环相连，大概有点内向树感觉

![内向树？](https://img2018.cnblogs.com/blog/1452724/201903/1452724-20190315100137520-2132148955.png)

现在有 10 个人，你可以每次操作让一些人沿着路径前进一步，然后交互库会返回你多少个点上有人以及上面的人分别是谁（其实是谁可能不重要？）


你的目标就是在   $3*(T+C)$  次操作内让所有人**同时**到达终点，然后输出 done



# 分析


其实很好做？


我们只要首先  重复让 0 号走一步，然后 0 号 1 号一起走一步，直到 0 1 相遇（也就是返回有 2 个点上有人）

不难看出此时  0  1  一定在环上，然后我们让 10 个人一起走，等他们所有人相遇，就是走到终点了

什么？为什么这么做是对的？

我们设 1 走了 $T + x$ 步后和 0 相遇 ，那么 0 就走了 $2*(T + x)$   (T 就是链长)

那么 $T+x$ 必然是 $C$ 的倍数，因为  0  1 相遇， 0 肯定在环上多走了几圈

于是 1 号点再走 T 步就能到终点了， 0 和 1 一起走的，看做一个点就好了

而其他所有的点走了 T 步之后也到终点了

虽然我们不知道 T 是多少，但是让他们走着就对了（反正相遇了就是到终点了）



# 关于交互的问题

首先就是不知道能不能用文件读入...（好像不行，亲测出锅了）

然后就是记得 fflush

当然用 cout  +  endl  的好像连 fflush 都可以省掉不用了QVQ


```
//by Judge
#include<bits/stdc++.h>
using namespace std;
inline int read(){ int x=0; char c=getchar();
	for(;!isdigit(c);c=getchar());
	for(;isdigit(c);c=getchar()) x=x*10+c-'0'; return x;
} char s[15];
inline int get(){ int x=read();
	for(int i=1,t;i<=x;++i) scanf("%s",s); return x;
}
int main(){
	while(1){
		puts("next 0"),fflush(stdout),get();
		puts("next 0 1"),fflush(stdout);
		if(get()==2) break;
	}
	while(1){
		puts("next 0 1 2 3 4 5 6 7 8 9"),fflush(stdout);
		if(get()==1) break;
	} return puts("done"),fflush(stdout),0;
}

```

---

## 作者：mrsrz (赞：4)

用Floyd判圈法。即一个人每走一步，则另一个人走两步。由于有环，所以在某一时刻，跑得快的一定会追上跑得慢的，且此时跑的慢的一定没跑满一圈。

假设跑得慢的走了$t+k$步，那么跑得快的走了$2t+2k$步（$0\leqslant k < c$）。

忽略在链上的$t$步，由于它们现在在同一个点，所以$k\equiv t+2k\pmod c$。

转化得$t+k\equiv 0\pmod c$，$t\equiv c-k\pmod c$。

当前这两个人所处的位置再走$c-k$步恰好是目标位置，而由于$t$和$c-k$模$c$同余，所以再走$t$步就能到目标位置。

由于其他在起点的人走$t$步后也能到目标位置，所以我们无需知道$t$和$c$的具体位置，只需要让他们继续走，相遇的时候就是在目标位置。

一共花费的步数为$3t+2k< 3t+3c$。

## Code：
```cpp
#include<cstdio>
int group[11],step1=1,step2=2;
inline void update(){
	int x;
	static char s[12];
	fflush(stdout),scanf("%d",&x);
	for(int i=1;i<=x;++i){
		scanf("%s",s);
		for(int j=0;s[j];++j)group[s[j]^'0']=i;
	}
}
int main(){
	puts("next 0"),update();
	puts("next 0 1"),update();
	for(int t=1;;++t){
		if(t&1)puts("next 0 1"),++step1,++step2;else puts("next 0"),++step2;
		update();
		if(group[0]==group[1])break;
	}
	while(group[0]!=group[2])
	puts("next 0 1 2 3 4 5 6 7 8 9"),update();
	puts("done"),fflush(stdout);
	return 0;
}
```

---

## 作者：littleqwq (赞：2)

# CF1137D Cooperative Game 题解

### 前言：

今天学双指针的时候，讲了这个神奇的 Floyd 判环。

### 大致思路：

虽然题目上写了有 $10$ 枚棋子，但我们最多只需要用到 $3$ 颗即可。利用类似 Floyd 判环的方法，随便拿出 $2$ 颗棋子，其中命名慢棋子和快棋子，他们代表的意思显而易见，慢棋子移动慢，快棋子移动快。快棋子每次操作都移动一遍，慢棋子每两次操作移动一遍，那么在最多 $2(t + c)$ 次操作后，两个棋子会相遇在一个点上，接下来每次操作把所有棋子都挪动一次，如果所有棋子都在一个点时，说明找到答案点了，总次数最多 $3t + 2c$ 次，可以通过。

### 代码实现：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 10;
const int MOD = 1000000007;
inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-'){
			w = -1;
		}
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}
int n;
signed main()
{
	while(1)
	{
		cout << "next 0\n";
		fflush(stdout);
		n = read();
		for(int i = 1;i <= n; ++ i)
		{
			int x;
			x = read();
		}
		cout << "next 0 1\n";
		fflush(stdout);
		n = read();
		for(int i = 1;i <= n; ++ i)
		{
			int x;
			x = read();
		}
		if(n == 2)
		{
			break;
		}
	}
	while (1)
	{
		cout << "next 0 1 2 3 4 5 6 7 8 9\n";
		fflush(stdout);
		n = read();
		for(int i = 1;i <= n; ++ i)
		{
			int x;
			x = read();
		}
		if(n == 1)
		{
			break;
		}
	}
	cout << "done\n";
	fflush(stdout);
	return 0;
}
```

---

## 作者：Melo_DDD (赞：1)

交互题？

# 题目大意

如果你不看原题面，你根本就不会知道这个蠢题目读入的是什么。

解释一下：

- 首先读入一个整数 $k$，表示现在有 $k$ 个位置上有棋子。

- 接下来对每个位置读入一个字符串，表示当前位置都有哪几个棋子。

# 题目实现

很明显的 Floyd 判圈法板题，不知道的先移步其他地方学习一下。

我们设 $0$、$1$ 号棋子分别为快、慢指针（当然其他的两个也行），那么开始我们让 $0$ 每次走两步，$1$ 每次走一步，其他的不管。

判圈法结论：两个棋子第一次相遇时，把所有棋子都看做慢指针，每次同时移动 $1$ 步，最后一定会在环的起点处相遇。

容易证明至多 $3\times t + 2\times c$ 次就会相遇，$3\times (t+c)$ 的次数限制可过。

注意输出后要刷新缓冲区。

## 代码

```cpp
#include <bits/stdc++.h>
#define f(i ,m ,n ,x) for (int i = (m) ;i <= (n) ;i += (x))
using namespace std ;
inline int in () {
	int n ;
	cin >> n ;
	f (i ,1 ,n ,1) {
		string str ;
		cin >> str ;
	}
	return n ;
}
int main () {
	for ( ; ; ) {
		puts ("next 0") ;
		fflush (stdout) ;
		in () ; // 第一次 n = 2 时不能结束循环
		puts ("next 0 1") ;
		fflush (stdout) ;
		if (in () == 2) {
			break ; // 第二次 n = 2 时说明 0、1 号相遇，跳出
		}
	}
	for ( ; ; ) {
		puts ("next 0 1 2 3 4 5 6 7 8 9") ;
		fflush (stdout) ;
		if (in () == 1) { // 所有棋子相遇，结束
			break ;
		}
	}
	puts ("done") ;
	fflush (stdout) ;
	return 0 ;
}
//kafka & かみや & 申鶴
```

---

## 作者：xzyxzy (赞：1)

## [BLOG](https://www.cnblogs.com/xzyxzy/p/10512730.html)

# [Codeforces1137D]Cooperative Game
Tags：题解

---

## 题意
这是一道交互题。

给你一张下面这样的地图，由一条长为$t$的有向链和一个长为$c$的环构成。
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1137D/34a9ab7816c73b7f2368756224775ddf156360e3.png)
现在你有$10$颗棋子，编号$0$到$9$，你不知道$t$和$c$的值，你每次可以移动若干颗棋子。

请你输出方案，使得所有棋子走到环和链的交点处，并在走到时输出`done`。

你每次可以输出`next a b c ...`，交互库将返回`k a1 a2 ... ak`表示当前有$k$个位置有棋子，$ai$表示一个字符串，表示第$i$个位置的棋子编号是什么。

你的移动次数不能超过$3(t+c)$，$t+c\le 1000$。

## 题解
神仙题，一直在想$10$颗棋子的二进制意义，然而$t$和$c$再大也没有关系。

步骤：

选定两颗棋子$0$,$1$，$0$每次都移动，$1$每两次移动一次。

走了$2t$步之后$1$刚好到达交点$T$，把环按照以$T$为$1$按边的方向依次编号，则此时$0$在环上的$t$位置。

这时$0$还需要$c-t$步追上~~（到）~~ $1$，追上的位置是$c-t$。

然后惊奇地发现：把所有点同时走$t$步就可以让所有点都在$T$上了！

服了服了。这场掉分掉得爽啊（第一次掉分）

## 代码
```cpp
#include<iostream>
using namespace std;
char s[100];
int In() {int x,p;scanf("%d",&x);for(p=x;p;p--) scanf("%s",s);return x;}
int main()
{
	while(1)
	{
		puts("next 0");fflush(stdout);In();
		puts("next 0 1");fflush(stdout);
		if(In()==2) break;
	}
	while(1)
	{
		puts("next 0 1 2 3 4 5 6 7 8 9");
		fflush(stdout);if(In()==1) break;
	}
	puts("done");fflush(stdout);
}
```

---

## 作者：wjyyy (赞：1)

## （前言

由于之前做过的交互题都是和倍增/二进制有关，本题给出了 $10$ 个点，而且 $\log_2 1000$ 也恰好是 $10$，于是就这样陷进去了…

## 题解

实际上我们只需要 $3$ 个点就能解决本题的问题，我们可以把这 $10$ 个点分为 $0,1,23456789$ 三个部分。

首先让 $0$ 每走 $2$ 步，$1$ 走一步。当 $0,1$ 相遇时环长即为 $0$ 走过的距离减去 $1$ 走过的距离。每次 $0$ 总比 $1$ 快一步。除了一种情况以外，环长也等于 $1$ 走过的步数。这叫做**Floyd判环**。

> **一种情况：**
>
> ![](http://www.wjyyy.top/wp-content/uploads/2019/03/201903102139.png)
>
> 如果下一步是 $0,1$ 一起走的话，那么 $0$ 走的步数就不恰好是 $1$ 走的步数的两倍了，因此需要判一下。

此时我们知道 $0,1$ 在环上的某个点相遇了。我们现在知道了环长 $c$ 和链长 $t$，但是我们不知道 finish vertex 在哪里。

我们为了让 $01$ 与 $23456789$ 在 finish vertex 相遇，我们可以构造出环上的一个点。设 $1$ 号棋子已经走了 $m$ 步，因此令 $01$ 在环上“倒退 $m$ 步”，也就是前进 $-m\pmod c$ 步，此时就和 $23456789$ 同步了。我们发现，环长**一般情况下**也恰好是 $m$（特殊情况是 $m+1$，让 $01$ 先走一步就可以了），然后让 $0123456789$ 同时移动。

最终所有点相遇的地方就是 finish vertex 了。输出 `done` 即可。

一般情况下步数为 $2(t+c)-1$，上面提到的情况步数为 $2(t+c)$。


## 代码

```cpp
#include<cstdio>
#include<cstring>
#include<vector>
//#define wjyyy
char s[100];
int main()
{
    int sum=0,n,p=0;
    while(++p)
    {
        printf("next 0 ");
        if(!(p&1))
        {
            printf("1");
            ++sum;
        }
        puts("");
        #ifndef wjyyy
            fflush(stdout);
        #endif
        scanf("%d",&n);
        int flag=0;
        for(int i=1;i<=n;++i)
        {
            scanf("%s",s);
            int tmp=0;
            for(int j=0;s[j]!='\0';++j)
                if(s[j]=='0'||s[j]=='1')
                    ++tmp;
            if(tmp==2)
                flag=1;

        }
        if(flag)
            break;
    }
    //环长是p-sum 1 走的是sum
    bool g=(p-sum==sum);
    
    while(n>1)
    {
        if(g)
            puts("next 0 1 2 3 4 5 6 7 8 9");
        else
            puts("next 0 1");
        g=1;
        #ifndef wjyyy
            fflush(stdout);
        #endif
        scanf("%d",&n);
        int flag=0;
        for(int i=1;i<=n;++i)
            scanf("%s",s);
    }
    puts("done");
    #ifndef wjyyy
        fflush(stdout);
    #endif
    return 0;
}
```

---

## 作者：jijidawang (赞：1)

一道经典面试题到 Codeforces 上咋就成 \*2400 了（

***

Floyd 判圈法，~~又叫双指针，快慢指针等~~ .

大概就是给一个和题目一样的 $\rho$ 形图，然后在起点处放两个指针 $p_1,p_2$ .

每次 $p_1$ 走一步，$p_2$ 走两步，则 $p_1,p_2$ 总会相遇 .

这非常平凡，就是环形跑道相遇问题呗 .
***
设链长为 $t$，环长为 $c$，则走的步数 $step$ 满足
$$t+step\equiv 2\cdot step+3t\pmod c$$
即 $step+2t\equiv 0\pmod c$，从而 $step\equiv c-2t\pmod c$

根据定义再走 $c-2t$ 步就到环和链的交点了，也就是再走 $step$ 步就好了 .

也就引出那个经典的方法找到环和链的交点：
1. 三个指针 $p_1,p_2,p_3$ 都初始化在链的头部 .
2. 每次 $p_1$ 走 $1$ 步，$p_2$ 走 $2$ 步，直到它们相遇 .
3. 相遇后，$p_1,p_2,p_3$ 均每次走一步，相遇点即为环链交点 .

然而我们有 $10$ 个点，不就随便做了 .

我们在第 $2$ 步之后将所有点一起动，要不然会超次数 .

这样步数显然是不超过 $3(t+c)$ 的，留作练习 .

CF Submission: [161472728](https://codeforces.com/contest/1137/submission/161472728) .

---

## 作者：PDAST (赞：0)

### 思路
想到可以让一个棋子走的更快，在环路上从后面追上另一个，一旦相遇，便停止。此时再让所有棋子向前走 $T$ 步便可以达到目的。
### 证明
我们设走的慢的棋子在环路上走了 $x$ 步，则它一共走了 $T+x$ 步，另一个棋子走了 $2(T+x)$ 步，而我们知道，快的棋子一定比慢的多走了 $C$ 的整数倍，所以 $2(T+x)-(T+x)$ 即 $T+x$ 必定是 $C$ 的整数倍。而此时，留在起点的棋子相距终点 $T$ 步，在环上的两个棋子再走 $T+x-x$ 步就能到达终点，所以可以让全部棋子一起向前走 $T$ 步以达到目的。
### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
string st[21];
bool get(int p){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>st[i];
	return n!=p;
}
signed main(){
	int t=0;
	while(1){
		t++;
		cout<<"next 0"<<endl;
		get(2);
		cout<<"next 0 1"<<endl;
		if(!get(2))break;
	}
	while(1){
		cout<<"next ";
		for(int i=0;i<10;i++)cout<<i<<" ";
		cout<<endl;
		if(!get(1))break;
	}
	cout<<"done"<<endl;
}
```

---

## 作者：chala_tea (赞：0)

## 题意

一个有向图，由一条边数为 $t$ 的链和一个长度为 $c$ 的环组成，每个点有且仅有一条出边。链的开头（图中房子处）有 $10$ 枚棋子。

交互机将给你提供：

1. 目前有多少个点上有棋子；

1. 哪些棋子在同一个点上。

你的输出：你需要让哪些棋子向前移动一步。

最终目标：把所有 $10$ 枚棋子移动到链和环的交点处。

## 解题思路：双指针 之 [Floyd 判环法](https://oi-wiki.org/misc/two-pointer/#%E5%9C%A8%E5%8D%95%E5%90%91%E9%93%BE%E8%A1%A8%E4%B8%AD%E6%89%BE%E7%8E%AF)

（链接来自 oi-wiki.org）

利用 floyd 判环法，可以随意将两个棋子设为快慢指针以判断链环交点。我们只需要知道目前有几个点上有棋子即可。

设快指针为棋子 $1$，慢指针为棋子 $0$，每次返回值有 $x$ 个点上有棋子，则可以：

- 开始时就输出 “next 1”、“next 0 1” 并不断循环，直至 $x=2$ （快慢指针相遇）为止；

- 此时我们可以**省去快指针回到链头的操作**，因为除棋子 $0$ 与 $1$ 外的所有棋子还留在链头，则可将棋子 $0$ 与 $1$ 整体视作留在原位的“慢指针”，其余棋子整体视作回到链头的“快指针”，并共同以单位速度前进，直至 $x=1$ （快慢指针相遇）为止并输出 done。

记得刷新缓冲区！！

### 代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define MAXN 114514
#define int long long

int x;
string s;
void get(){
	cin>>x;
	for(int i=1;i<=x;i++)cin>>s;
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	
	while(x!=2){
		cout<<"next 1"<<endl;
		cout.flush();
		get();
		cout<<"next 0 1"<<endl;
		cout.flush();
		get();
	}
	while(x!=1){
		cout<<"next 0 1 2 3 4 5 6 7 8 9"<<endl;
		cout.flush();
		get();
	}
	cout<<"done"<<endl;
	cout.flush();

	return 0;
}

```

---

## 作者：Y2y7m (赞：0)

题意：

有一张有向图，左边一条链，右边一个环：
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1137D/34a9ab7816c73b7f2368756224775ddf156360e3.png)

现在有十个人 $(0,1,2....9)$ 从起点开始，你每次告诉他有哪些人向前走一步，他告诉你哪些人在一起，问你什么时候这十个人都在链与环的交界处，如果你确认了，就输出 done。

链长为 $t$，环长为 $c$，操作次数不超过 $3 \times (t+c)$。

----

你从这十个人中，让 $0$ 号先走两步，再让 $1$ 号走一步，直到他俩相遇。

注意：**相遇在环上！**

接下来，我们让所有人动起来。

直到他们相遇，就在链与环的交点。

![](https://cdn.luogu.com.cn/upload/image_hosting/irg28qyo.png)

设从链与环的交点之间的距离为 $x$。

我们就可以知道：$(t+x)$ 整除 $c$。

如果不能理解，就看看图。

接下来我们来看这十个人的相遇情况：

当其他八个人走到交点时走了 $t$ 步。

所以 $0，1$ 两人就走到了 $(t+x)\mod c$ 的位置上……

**正好是链与环的交点处**

code:

```cpp
#include<bits/stdc++.h>
 
using namespace std;
char s[110];
int get()
{
	int x;
	cin>>x;
	for(int i=1;i<=x;i++)
		cin>>s;
	return x;
}
int main(){
	while(1)
	{
		cout<<"next 0"<<endl;
		get();
		cout<<"next 0 1"<<endl;
		if(get()==2)
			break;
	}
	while(1)
	{
		cout<<"next 0 1 2 3 4 5 6 7 8 9"<<endl;fflush(stdout);
		if(get()==1)
			break;
	}
	cout<<"done"<<endl;
	return 0;
}


```


---

## 作者：风随逐影 (赞：0)

## 神仙交互题

**记得以前听lch神仙讲过，不过当时还没做过这道题**

### 题意(来自yyb神仙的翻译)：

有一张图是由一个长度为$t$的链和一个大小为$c$的环中间连上一条边组成的。
假如这条边连接的是链的右端点，和环上的T点。
令链的左端点是S。
现在在S处有$10$个棋子，编号$0−9$，每次你可以让任意数量的棋子向出边方向走一步，交互库会返回若干个集合，每一个集合内的棋子都在同一个位置上，并且这个位置上的所有棋子都在这个集合中。
现在你既不知道$t$也不知道$c$。你需要使用不超过$3(t+c)$次操作使得所有棋子都移动到T位置上并且返回交互库

### 官方题解翻译......（手动翻译，不是机翻）

棋子的数量在这里是迷惑你的，其实只需要三个棋子就可以解决问题

我们把移动速度快的棋子叫做$fast$，慢的叫$slow$，$slow$每走一步，$fast$走两步，当他们相遇时停止

显然，$slow$无法在环上走完完整的一圈，因为$slow$每走1圈，$fast$走两圈，一定会被$fast$追上

故他们相遇时行走的距离$slow=t+x$，$fast=t+x+k*c$，且$fast=2*slow$

解得$x≡-t(mod   c)$

所以再走t步就能到达终点了，但我们不知道t是多少，注意到留在原点的棋子离终点距离刚好为t，故让所有棋子同时走，相遇时就都到达了终点

询问次数$q=2*t+2*x+t=2*x+3*t<3*(x+t)$，故可以通过此题

```c
#include<bits/stdc++.h>
using namespace std;

#define go(i,a,b) for(int i=a;i<=b;++i)
#define com(i,a,b) for(int i=a;i>=b;--i)
#define mem(a,b) memset(a,b,sizeof(a))
#define fo(i,a) for(int i=0;i<a;++i)
#define il inline

string s;

il int read(){
	int x;scanf("%d",&x);
	go(i,1,x) cin>>s;
	return x;
}

int main(){
	//freopen("input.txt","r",stdin);
	while(23333){
		puts("next 0 1");
		cout.flush();
		read();
		puts("next 0");
		cout.flush();
		if(read()==2) break;
	}
	while(23333){
		puts("next 2 3 0 1 4 5 6 7 8 9");
		cout.flush();
		if(read()==1) break;
	}
	puts("done");
	cout.flush();
	return 0;
}
```

---

## 作者：xukuan (赞：0)

题目中说了“This is an interactive problem.”

交互题，就是你给出一些输出，题目根据你的输出给出输入，你再给出输出……

一般会给出最大限制，如输出不超过100KB，输出次数不超过1K，总时间不超过10s等等。

通常根据OJ的不同性质会有不同的要求，Codeforces给出的要求是用
```cpp
fflush(stdout);
```
表示一组输出的结束。所以，每次输出完毕后都要加上这句话

思路：floyd判环+瞪眼找规律

所有点同时走t步就可以都在T上！

```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;

char s[100];

inline ll scan(){
    ll n;
    scanf("%lld",&n);
    for(ll i=1; i<=n; i++) scanf("%s",s);
    return n;
}

int main(){
    do{
        printf("next 0\n"); fflush(stdout); scan();
        printf("next 0 1\n"); fflush(stdout);
    }while(scan()!=2);
    do{
        printf("next 0 1 2 3 4 5 6 7 8 9\n");
        fflush(stdout);
    }while(scan()!=1);
    printf("done\n");
    fflush(stdout);
    return 0;
}
```

---

