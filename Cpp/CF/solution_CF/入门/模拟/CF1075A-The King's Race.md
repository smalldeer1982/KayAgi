# The King's Race

## 题目描述

在一个宽为 $n$、高为 $n$ 的国际象棋棋盘上，行号从下到上依次为 $1$ 到 $n$，列号从左到右依次为 $1$ 到 $n$。因此，棋盘上的每一个格子都可以用坐标 $(r, c)$ 表示，其中 $r$ 表示行号，$c$ 表示列号。

白王已经在坐标为 $(1,1)$ 的格子上坐了一千年，而黑王则一直坐在坐标为 $(n,n)$ 的格子上。他们本可以继续这样坐下去，但突然有一枚漂亮的硬币掉在了坐标为 $(x, y)$ 的格子上……

两位国王都想得到这枚硬币，于是他们决定按照稍作修改的国际象棋规则来进行一场竞赛：

与国际象棋一样，白王先走一步，黑王再走一步，接着白王再走一步，如此交替进行。然而，在本题中，两个国王可以同时站在相邻的格子，甚至可以同时站在同一个格子。

谁先到达硬币所在的格子 $(x, y)$，谁就获胜。

我们回顾一下，国王是一种可以向所有方向移动一格的棋子，也就是说，如果国王当前在 $(a, b)$，那么他可以一步移动到 $(a+1, b)$、$(a-1, b)$、$(a, b+1)$、$(a, b-1)$、$(a+1, b-1)$、$(a+1, b+1)$、$(a-1, b-1)$ 或 $(a-1, b+1)$。禁止走出棋盘之外。

请判断，如果白王先走，谁会先到达 $(x, y)$ 所在的格子。

## 说明/提示

下面是第一个样例的竞赛过程示例，假设两位国王都采取最优策略：

1. 白王从 $(1,1)$ 移动到 $(2,2)$。
2. 黑王从 $(4,4)$ 移动到 $(3,3)$。
3. 白王从 $(2,2)$ 移动到 $(2,3)$，这就是硬币所在的格子，因此白王获胜。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1075A/f254caab5d6689c7762373bad40ea730253add20.png)

下面是第二个样例的竞赛过程示例，假设两位国王都采取最优策略：

1. 白王从 $(1,1)$ 移动到 $(2,2)$。
2. 黑王从 $(5,5)$ 移动到 $(4,4)$。
3. 白王从 $(2,2)$ 移动到 $(3,3)$。
4. 黑王从 $(4,4)$ 移动到 $(3,5)$，这就是硬币所在的格子，因此黑王获胜。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1075A/8da824ef69161fea610dd68f5d79c6e1d4915d1c.png)

在第三个样例中，硬币正好掉在了黑王的起始格子，因此黑王立即获胜。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1075A/ef64633e6cdf332ba74f49b9036ceea6af7c9df5.png)

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
2 3
```

### 输出

```
White```

## 样例 #2

### 输入

```
5
3 5
```

### 输出

```
Black```

## 样例 #3

### 输入

```
2
2 2
```

### 输出

```
Black```

# 题解

## 作者：Lips (赞：4)

# ~~先吐槽一句：这是恶评题吧~~

第一眼康到这题，便认为对于白王`white`与黑王`black`跑 $2$ 次最短路便可，当我兴冲冲地打完了~~重构~~代码的 $\frac{2}{3}$ 时，才发现了 $n\le 10^{18}$ 这个可怕的数据范围，暴力肯定 $T$ 飞无疑。

猛然间，想起了众所周知的[一个问题](https://www.luogu.com.cn/problem/P6474)——可以直接求每个国王到硬币的曼哈顿距离鸭！

$$\operatorname{abs}(x1-x2)+\operatorname{abs}(y1-y2)$$

但我相信您不会贸然地把我刚才所讲的写成代码提交上去——必 $WA$ 无疑。

由于题目中说王也珂以**斜着走**，曼哈顿瞬间变成废柴。那咋做？先康一张图片：

![](https://cdn.luogu.com.cn/upload/image_hosting/5e543v1e.png)

珂以举个栗子，如果从 $(1,1)$ 走到 $(3,2)$ 的最短合法路径为：$(1,1)->(2,2)->(3,2)$，花费为 $2$，当然长度不唯一。同理，$(1,1)$ 走到 $(3,3)$ 的花费为 $2$，以此类推。从中，窝们便珂发现一个规律，若从 $(x1,y1)$ 走到 $(x2,y2)$，其花费为 

$$\max(\operatorname{abs}(x1-x2),\operatorname{abs}(y1-y2))$$


~~读者自证不难~~

把这个距离公式封装到一个 $dis$ 函数里，并算出`white`和`black`需要走的距离，比较一下便珂。

最后温馨提示~~一个万年老坑~~：$10$ 年 $OI$ 一场空，不开 $**$ 见祖宗。

$Code:$

```cpp
#include<cstdio>
#include<cmath>
#include<algorithm>//头文件 
using namespace std;
typedef long long ll;//一定要记得开long long 
ll n,x,y;
ll dis(ll x1,ll y1,ll x2,ll y2){return max(abs(x1-x2),abs(y1-y2));}//计算距离公式 
int main()
{
	scanf("%lld%lld%lld",&n,&x,&y);//输入 
	ll white=dis(1,1,x,y),black=dis(n,n,x,y);
	//分别计算白王和黑王所要走的路程 
	if(white<=black) puts("White");//比较谁先到硬币那里 
	else puts("Blackkk");//防抄袭 
	return 0;//完结撒花~~ 
}
```

~~理解以后再抄~~

---

## 作者：Laurenceshao (赞：3)

蒟蒻第一次发题解，还请各位巨佬海涵校正。

在纸上画几个草图可以知道，如果金币在对角线('\')左下方，就是白方赢；如果在对角线右上方，就是黑方赢。
在对角线上时，因为白方先出，所以白方赢。
若要证明，把对角线（'\'）所在的直线想成该正方形的一个对称轴，黑王百王都各占和对称轴有相同距离的一个顶点。

代码如下：
```cpp
#include <iostream>
using namespace std;
long long n,x,y;
int main(){
    cin>>n>>x>>y;
    if(x+y<=n+1)cout<<"White"<<endl;
    else cout<<"Black"<<endl;
    return 0;
}
```

---

## 作者：star_looker (赞：1)

水题。

本题主要考察的应该是两个王距离硬币的距离，我们来求一下。

设 有个棋子要从$(1,1)$走到$(4,5)$，如果题目要求不可以斜走，那直接走$4+5-1-1=7$步如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/x0tbecbt.png)

但题目说可以斜走，我们冷静分析一下。斜走就走了一个正方形。为了方便，我们把$(1,1)$改成$(0,0)$画图分析：

![](https://cdn.luogu.com.cn/upload/image_hosting/omxtscun.png)

设 棋子坐标$(x1,x2)$,要走到$(x2,y2)$,则路径步数为$max(abs(x1-x2),abs(y1-y2)$。

CODE:

```cpp
#include<cstdio>//格式化输入输出流
#include<cmath>//max、abs的老家
long long js(ll x1,ll y1,ll x2,ll y2){
    return max(abs(x1-x2),abs(y1-y2));
}int main(){
    long long n,x,y;
	 scanf("%lld%lld%lld",&n,&x,&y); 
	 long long white=js(1,1,x,y),black=js(n,n,x,y);//重点
	 if(white<=black) 
    	printf("White");
	 else 
      printf("Black");
	 return 0;
}
```


---

## 作者：PersistentLife (赞：0)

**这题不是最短路，是一个结论题，最短路肯定炸！**

我们回忆一下~~小学~~数学知识，如下图，从一个点到另一个点要走多远呢？

![1](https://cdn.luogu.com.cn/upload/image_hosting/dl3278b3.png)

答案就是 $5$，如果表示出来就是 $abs(x_1-y_2)+abs(y_1-y_2)$。

那就好办了，交上去吧！

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,x,y,white,black;
int main()
{
    cin>>n>>x>>y;
    white=(x-1)+(y-1);
    black=(n-x)+(n-y);
    if(white<=black) cout<<"White";
    else cout<<"Black";
    return 0;
}
```
我们愉快的 WA 了……

为什么呢？原来王是可以斜着走的，那要怎么算距离呢？

还是拿上面那张图举例，最短路是这样的：

![2](https://cdn.luogu.com.cn/upload/image_hosting/lmvf64lw.png)

多试几次就能得出结论，最短路是：$\max(abs(x_1-y_2),abs(y_1-y_2))$

证明：

因为可以斜着走，所以只需要走长，宽中比较长的边，因为短的可以在走长的时候用“斜走”的方法走掉。

那么代码就很好写啦，注意白王先走，而且要开 `long long`。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,x,y,white,black;
int main()
{
    cin>>n>>x>>y;
    white=max(x-1,y-1);
    black=max(n-x,n-y);
    if(white<=black) cout<<"White";
    else cout<<"Black";
    return 0;
}
```

---

## 作者：Seauy (赞：0)

某天无聊翻了翻同学Fanhy大佬的AC记录

突然发现……

他过了尚无评定的题！（我滴天难不成他隐藏了多年的巨佬身份？）

心下奇怪，翻了翻他AC过的题，突然发现了这道题……（没错他就是第一个过这道题的男人）

于是我不甘示弱，也要过一道尚无评定的题！（然后就选中了这道无辜的题）

~~debug路慢慢，编程经历一何坎坷，迭代版本无数！~~先看看我错得一塌糊涂的版本1吧

```cpp
#include<bits/stdc++.h>
using namespace std;

unsigned long long n_size;

struct Point
{
	unsigned long long x,y;
	void scan()
	{
		cin>>x>>y;
	}
}coin,white,black;

int main()
{
	cin>>n_size,coin.scan();
	white.x=white.y=1;
	black.x=black.y=n_size;
	if(coin.x==white.x && coin.y==white.y) cout<<"White",exit(0);
	if(coin.y==black.y && coin.x==black.x) cout<<"Black",exit(0);
	//计算白色要走的步数
	int white_step=0,black_step=0;
	if(coin.x>1 && coin.y>1)//要斜着走
	{
		white_step+=min(coin.x-1,coin.y-1);
		white.x=white.y=min(coin.x,coin.y);
	}//到达与硬币 x 相等或 y 相等的格子 
	if(white.x==coin.x)//y可能不一样
		white_step+=(white.y>coin.y ? white.y-coin.y : coin.y-white.y);
	if(white.y==coin.y)//x可能不一样
		white_step+=(white.x>coin.x ? white.x-coin.x : coin.x-white.x);
	if(coin.x<n_size && coin.y<n_size)//black也要大费周折地斜着走
	{
		black_step+=min(n_size-coin.x,n_size-coin.y);
		black.x=black.y=n_size-black_step;
	}
	if(black.x==black.x)//y可能不一样
		black_step+=(black.y>coin.y ? black.y-coin.y : coin.y-black.y);
	if(black.y==coin.y)//x可能不一样
		black_step+=(black.x>coin.x ? black.x-coin.x : coin.x-black.x);
	cout<<white_step<<' '<<black_step<<endl;
	cout<<(white_step<=black_step ? "White" : "Black");
	return 0;
}
```

由于懒得写公式于是想模拟一下（也不算模拟，因为至少没一格格走），但大体思路没错：

1.（不管是哪个王）先斜着走，直到x坐标与硬币对齐或者y坐标对齐

2.然后笔直地向胜利前进

大概是写得太复杂了导致某个语句出了点问题，那就写得简单一点。版本2，上！
```cpp
#include<bits/stdc++.h>
using namespace std;

unsigned long long n,x,y;

int main()
{
	cin>>n>>x>>y;
	cout<<(min(x,y)-1+y-min(x,y)+x-min(x,y)<=n-max(x,y)+max(x,y)-y+max(x,y)-x ? "White" : "Black");
	return 0;
}
```

好了重头戏来了，这里先简单讲一下"?"于":"的搭配用法

n=(条件表达式 ? 值1 : 值2)

其中 值1 的类型要与 值2 相同

其含义是：当条件表达式成立，n就为 值1，要是不成立，n就为 值2

好了这只是一个缩短代码的小技巧，我们先来看不等式左边的那坨玩意

min(x,y)-1+y-min(x,y)+x-min(x,y)

它代表了白王所要走的步数，min(x,y)-1 是为了使x坐标与硬币对齐或者y坐标对齐走的步数,当然，是走了斜线，如下图
```
.....B
......
..$...
......
......
W.....
```

其中W代表白皇后，B代表黑皇后，$代表那个硬币

为了使x坐标与硬币对齐或者y坐标对齐，W一直往右上走，直到……
```
.....B
......
..$...
..W...
......
......
```

此时 x 轴W与硬币已经对齐了，现在要干嘛嘞？当然是一直沿着这条y轴往上走！就有了接下来的

+y-min(x,y)+x-min(x,y)

这时，由于一直在往右上走，W的x与y其实是一样的，那min(x,y)既代表了走完斜线的x又代表了y

由于对齐之后硬币只可能是在W的上面或右面了（或者已经拿到了），所以此时的硬币的 x 和 y 肯定是都 >= W的 x 与 y 的，所以是 x 与 y 作为被减数

但是，黑国王也不是吃素的！

与此同时，他也走了！

与白国王类似，他一上来也是一直往左下斜着走，当他走完斜线的时候……
```
......
......
..$B..
..W...
......
......
```

当然，此时的他走了 n-max(x,y) 步

这个式子的推导与W的差不多，B可以看做是把棋盘颠倒以后的W，于是 min 变成了 max,坐标也要从 (n,n) 开始算起，1 就变成了 n

然后 +max(x,y)-y+max(x,y)-x 也差不多，颠倒后 min 变成 max,x 与 y 的位置也从被减数变成了减数

此时，W与B都之差一步就可以拿到硬币了！那是不是他们同时都拿到了硬币嘞？

并不是蛤，由于W是先走的，所以接下来是W走，然后W就拿到硬币了

所以不等式是由 <= 连接的，当步数相同的时候，白皇后就占优势了（黑皇后：赖皮！）

然后么，简化简化这个式子，就变成了Fanhy大佬的 max(x,y)-1<=n-min(x,y) 了

但是，他的式子还不是最简的。

我们可以把 min(x,y) 给移到不等式左边，就可以变成 max(x,y)+min(x,y)-1 <= n 。

这个时候我们可以看到，x y 中大的那个又加上了小的那个，总共也就两个数字，所以 min(x,y)+max(x,y) 其实就等于 x+y 。（各位同学可以自己来举例证明一下）

所以最简的式子其实就是楼上大佬的式子啦


---

## 作者：liuyz11 (赞：0)

原比赛题解：[https://www.cnblogs.com/nblyz2003/p/9907114.html](https://www.cnblogs.com/nblyz2003/p/9907114.html)

题意：有一黑一白两个旗子，白的在(1, 1)上，黑的在(n, n)上。每次可以将旗子移动到周围一圈这八个位置，给你三个数n, a, b(1 <= a, b <= n <= 10 ^ 18)，让你求那个旗子可以先到达(a, b)。注：先移动的是白棋。

只要求出黑棋到(a, b)和白棋到(a, b)的步数，如果白棋小于等于（因为白棋动下）黑棋的，那么就是白棋，否则就是黑棋。

至于求所需的步数，就是max(行 - a, 列 - b)。

代码如下

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#define rep(x, l, r) for(int x = (int)l; x <= (int)r; x++)
#define repd(x, r, l) for(int x = (int)r; x >= (int)l; x--)
#define clr(x,y) memset(x, y, sizeof(x))
#define all(x) begin(x), end(x)
#define pb push_back
#define mp make_pair
#define MAXN    
#define fi first
#define se second
#define SZ(x) ((int)x.size())
using namespace std;
typedef long long LL;
typedef vector<int> vi;
typedef pair<int, int> pii;
const int INF = 1 << 30;
const int p = 10000007;
//head by DYH

LL judge(LL X0, LL Y0, LL X1, LL Y1){
    return max(abs(X0 - X1), abs(Y0 - Y1));
}

int main(){
    LL n, a, b;
    scanf("%I64d%I64d%I64d", &n, &a, &b);
    LL res1 = judge(1, 1, a, b), res2 = judge(n, n, a, b);
    if(res1 <= res2) puts("White");
    else puts("Black");
    return 0;
}
 Problem-A
```

---

