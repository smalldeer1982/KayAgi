# [USACO07OCT] Super Paintball G

## 题目描述

奶牛们最近从玩具商那里，买来了一套仿真版彩弹游戏设备（类似于真人 CS）。Bessie 把她们玩游戏的草坪划分成了 $N \times N$ 的矩阵（$1 \leq N \leq 100$），同时他算出了她的 $K$ 个对手在草地上的位置（$1 \leq K \leq 10^5$），现在你需要帮 Bessie 算些东西。

在这个游戏中，奶牛们用一把枪向八个方向中的任意一个方向射出子弹，这八个方向分别是：正北，正南，正东，正西，东北，东南，西北，西南（东北指北偏东 $45^\circ$，东南，西北，西南同理）。

Bessie 想要你算出，有多少个位置可以让她射到所有对手。特别地，Bessie 可以和她的某一个对手站在同一格子，这时候她可以射到和她同一格子的对手。

## 说明/提示

可选的位置有：$(2,1),(2,3),(3,2),(4,1),(4,3)$。

## 样例 #1

### 输入

```
4 3
2 1
2 3
4 1```

### 输出

```
5```

# 题解

## 作者：do_while_false (赞：5)

这题暴力枚举即可。

直接记录，左右是 $x$，上下是 $y$，左上到右下是 $x-y+n$，右上到左下是 $x+y-1$，注意可能站在对手的位置射击。

```cpp
#include<bits/stdc++.h>
#define ll long long 
using namespace std;
const int maxn=510,inf=1e9;
int n,k,x,y,z,tot,ans;
int row[maxn],col[maxn],lt[maxn],rt[maxn],map1[maxn][maxn];
inline int read() {//快读 
	int r=0;bool flag=true;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') flag=false;ch=getchar();}
	while(ch>='0'&&ch<='9'){r=(r<<3)+(r<<1)+(ch^48);ch=getchar();}
	return flag==true?r:~r+1;
}
int main(void) {
    n=read();
    k=read();
    for(int i=1;i<=k;i++) {
        x=read();
        y=read();
		map1[x][y]++;
        row[x]++;col[y]++;lt[x-y+n]++;rt[x+y-1]++;
    }
    for(int i=1;i<=n;i++)
    	for(int j=1;j<=n;j++)
    		if(row[i]+col[j]+lt[i-j+n]+rt[i+j-1]-3*map1[i][j]==k) 
				ans++;
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：BotDand (赞：2)

# $\text{Problems}$
奶牛们最近从玩具商那里，买来了一套仿真版彩弹游戏设备（类似于真人 CS）。Bessie 把她们玩游戏的草坪划分成了 $N \times N$ 的矩阵（$1 \leq N \leq 100$），同时他算出了她的 $K$ 个对手在草地上的位置（$1 \leq K \leq 10^5$），现在你需要帮 Bessie 算些东西。

在这个游戏中，奶牛们用一把枪向八个方向中的任意一个方向射出子弹，这八个方向分别是：正北，正南，正东，正西，东北，东南，西北，西南（东北指北偏东 $45^\circ$，东南，西北，西南同理）。

Bessie 想要你算出，有多少个位置可以让她射到所有对手。特别地，Bessie 可以和她的某一个对手站在同一格子，这时候她可以射到和她同一格子的对手。
# $\text{Answer}$
看到$1\le N\le 100$，基本上就是暴力了。

对于每一个点，先自身加一，然后将八个方向（不越界）的坐标都加一。

最后要减去这个点重复算的次数即可。

然后判断每个点是否为K，如果是，则这个点可以站。

最后输出解即可。

时间复杂度$O(NK)$。
# $\text{Code}$
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
int x,y,s;
int a[102][102];
void work()
{
    for(int i=1;i<=n;++i) a[x][i]++;
    for(int i=1;i<=n;++i) a[i][y]++;
    for(int i=1;i<=n;++i) if(i+y-x>=1&&i+y-x<=n) a[i][i+y-x]++;
    for(int i=1;i<=n;++i) if(x+y-i>=1&&x+y-i<=n) a[i][x+y-i]++;
    a[x][y]-=3;
}
int main()
{
    cin>>n>>k;
    for(int i=0;i<k;++i)
    {
        cin>>x>>y;
        work();
    }
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
            if(a[i][j]==k)
                s++;
    cout<<s;
    return 0;
}
```


---

## 作者：seanlsy (赞：1)

~~趁刚考完期中考水篇题解~~

[题目传送门](https://www.luogu.com.cn/problem/P6200)

**朴素算法**

对于每个对手，直接暴力枚举每个点是否可以射击到该点。时间复杂度 $O(kn^2)$，显然无法通过。

**小改动**

在前面的基础上，每次只枚举还有机会的点，可以优化一下常数，不过大概率过不了。

**正解**

还是一样的思路，但是这次不用暴力枚举每个点，而是往每个方向依次标记。显然，对于任意一个点，它所处的对角线以及行和列都是确定的。如此一来，我们可以算出这些点的坐标，再依次标记即可。这样的话时间复杂度就变成了 $O(kn)$，可以通过。

**CODE**
```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0;bool f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=0;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return f?x:-x;
}
int n,k,r,c,ans,vis[105][105];
int main(){
	n=read(),k=read();
	for(int i=1;i<=k;i++){
		r=read(),c=read();
		for(int j=1;j<=n;j++)
			vis[j][c]++;
		for(int j=1;j<=n;j++)
			if(j^c)
				vis[r][j]++;
                //注意这里不要重复标记
		for(int j=1;j<r&&j<c;j++)
			vis[r-j][c-j]++;
		for(int j=1;r+j<=n&&c+j<=n;j++)
			vis[r+j][c+j]++;
		for(int j=1;j<r&&c+j<=n;j++)
			vis[r-j][c+j]++;
		for(int j=1;j+r<=n&&j<c;j++)
			vis[r+j][c-j]++;
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(!(vis[i][j]^k))
				ans++;
	printf("%d\n",ans);
	return 0;
}
```

**另一种思路**

除了直接标记以外，还可以用四个数组存储行、列和两种不同方向的对角线上点的个数。一个点能打到的对手个数就是这四个数的和。不过要小心，当对手就在这个点上时，会重复统计个数。所以统计个数时还要减去当前点上的对手个数的 $3$ 倍。

**CODE**

~~好吧没写这种方法。~~

可以参考别的题解。

**又一种思路**

就是用辅助数组 $dx$ 和 $dy$ 来给标记省代码，不过考虑到标记本身的代码量并不大，其实没有什么必要。

---

## 作者：Mine_King (赞：1)

这题我们如果对于每个点枚举可以打到多少奶牛肯定是会超时的，对于每个奶牛枚举能打到它的地方也有可能超时，所以我们要换个思路。

上面两个想法都是一个点一个点地判断，那么我们能不能一下子判断整一条直线呢？

当然可以。对于每个奶牛：

- 列：奶牛所在的整一列都能打到奶牛，我们让 $l_y++$（$y$ 是奶牛的纵坐标）
- 行：奶牛所在的整一行都能打到奶牛，我们让 $h_x++$（$x$ shi 奶牛的横坐标）
- 左斜线（像这样`\`）：奶牛所在的整一个左斜线都能打到奶牛，他每向右下移一格横纵坐标都 $+1$，向左上移同理，所以在同一条左斜线上的点横纵坐标的差相同，我们让 $zx_{x-y}++$（注意没有绝对值）
- 右斜线（像这样`/`）：奶牛所在的整一个右斜线都能打到奶牛，他每向左下移一格横坐标 $+1$ 但纵坐标 $-1$，向右上移同理，所以再同一条右斜线上的点的横纵坐标的和相同，我们让 $yx_{x+y}++$

那么我们就找到了可以打到每个奶牛的行、列和两条斜线，接下来我们就可以枚举每个点，然后找到他所对应的行、列和两条横线的奶牛数，把他们加起来如果等于 $k$，那么就是满足条件的点。  
时间复杂度 $O(n^2+k)$。

下面是两个注意点：

1. 若奶牛的横坐标小于纵坐标，那么 $x-y$ 就会是负数，而下标不能是负数，所以我们给他加个 $100$ 或 $n$  
2. 若 bessie 和一些奶牛站在一起，那么这些奶牛就会被算 $4$ 次，我们要减掉 $3$ 次（也就是容斥）

具体实现见**code**：
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,k,ans;
int f[105][105];
int h[105],l[105],zx[205],yx[205];//横线，竖线，左斜线（差相等），右斜线（和相等）
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=k;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		h[x]++,l[y]++;
		zx[x-y+100]++;
		yx[x+y]++;
        //标记
		f[x][y]++;//这里标记具体坐标，容斥用
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(h[i]+l[j]+zx[i-j+100]+yx[i+j]-3*f[i][j]>=k) ans++;//注意减去多余的
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：LiuHao2019 (赞：0)

模拟模拟 ~~，巧妙地模拟~~，就这么简单

根据光路是可逆的（严肃），只要别的奶牛能看到Bessie，那么Bessie也能看到别的奶牛。

所以只要对于每一只奶牛，将它们能看到的地方数字+1即可，最后输出数字为k的格子的数量。

注意：**这个奶牛自己在的格子不要漏算！也不要重复算！**

~~这题代码我居然还打了15分钟...~~

AC代码：

```cpp
#include<stdio.h>
int n;
int a[105][105];//表示站在这一格能否打中别人
int k;
int k2;
int r,c;
int main(){
	scanf("%d%d",&n,&k);
	k2 = k;
	while(k --){
		scanf("%d%d",&r,&c);
		for(int i = 1;i <= n;i ++)
			a[r][i]	++;//行 
		for(int i = 1;i <= n;i ++)
			if(i != r) a[i][c] ++;//列 
		for(int i = 1;;i ++){//左上 
			if(r-i >= 1 && c-i >= 1) a[r-i][c-i] ++;
			else break;
		}
		for(int i = 1;;i ++){//右下 
			if(r+i <= n && c+i <= n) a[r+i][c+i] ++;
			else break;
		}
		for(int i = 1;;i ++){//右上 
			if(r-i >= 1 && c+i <= n) a[r-i][c+i] ++;
			else break;
		}
		for(int i = 1;;i ++){//左下 
			if(r+i <= n && c-i >= 1) a[r+i][c-i] ++;
			else break;
		}
	}
	int ans = 0;
	for(int i = 1;i <= n;i ++)
		for(int j = 1;j <= n;j ++)
			if(a[i][j] == k2) ans ++;
	printf("%d\n",ans);
} 
```

---

## 作者：Loser_King (赞：0)

比较水的思维题。

建议评级：普及- ~ 普及/提高-

（某班模拟赛中得分率最高的一题）

## 简明题意

一个点可以向八个基本方向看向其他点。

现在给出 $K$ 个整点， 求在以 $(1,1)$ 为左下角， $(N,N)$ 为右上角的矩形中有几个整点满足：从该点可以看到全部的 $K$ 个点。

$1\le N\le10^2\;,\;1\le K\le 10^5$

## 做法

虽然 $N$ 很小，但是 $K$ 很大。如果枚举所有可能的整点的话，时间复杂度为 $O(N^2K)$ ，最大为 $10^9$ ，会超时。

采用倒推的思想，先从每个点的八个方向发散出去，在矩阵中对可以看到该点的整点打标记，然后再枚举矩阵中的每个整点，如果有一个点被打了 $K$ 个标记，那么答案就加一。

## 代码

```c++
//P6200 AC Code
//written by Loster_King(159686)
// 50ms / 768KB / 514B C++ O2
#include<bits/stdc++.h>
using namespace std;
int const dx[]={-1,-1,-1,0,0,1,1,1},dy[]={-1,0,1,-1,1,-1,0,1};	//八个基本方向
int n,k,res,cnt[233][233];							//cnt：标记数组
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>k;
	for(int i=1;i<=k;i++){
		int x,y;cin>>x>>y;cnt[x][y]++;
      	//这里要注意，可能会有两种问题：
        //一种是cnt[x][y]忘记加（注意看题）；
        //另一种是cnt[x][y]因为写在j循环内，所以加了八次（为我们的yf同志上香）
		for(int j=0;j<8;j++){
			int tx=x+dx[j],ty=y+dy[j];
			while(tx>0&&ty>0&&tx<=n&&ty<=n)
				cnt[tx][ty]++,tx+=dx[j],ty+=dy[j];	//向八个方向打标记
		}
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(cnt[i][j]==k)res++;					//统计答案
	cout<<res<<endl;
}
```



---

## 作者：迷残云 (赞：0)

我感觉这道题的处理方法有点像前几天的月赛的苏联人，都是向几个方向标记。。。

这道题就是向八个方向标记，用个$while$向四周扩散，记得标上自己。。

最后扫一遍整个矩阵，看标记数组是否与k相等，相等$ans++$，最后输出$ ans $

---

## 作者：zhengrunzhe (赞：0)

直接把k个敌人的八个方向的所有点都打上标记

最后扫一遍整个矩阵看有几个全标记点

时间复杂度：$O(nk)$
```cpp
#include<cstdio>
template<class type>inline const void read(type &in)
{
	in=0;char ch(getchar());
	while (ch<48||ch>57)ch=getchar();
	while (ch>47&&ch<58)in=(in<<3)+(in<<1)+(ch&15),ch=getchar();
}
const int N(105);
int n,k,cnt[N][N],ans;
int main()
{
	read(n);read(k);
	for (int j(1);j<=k;j++)
	{
		int x,y;
		read(x);read(y);
		for (int i(1);i<x&&i<y;i++)cnt[x-i][y-i]++; //西北
		for (int i(1);i<x&&i+y<=n;i++)cnt[x-i][y+i]++; //东北
		for (int i(1);i+x<=n&&i<y;i++)cnt[x+i][y-i]++; //西南
		for (int i(1);i+x<=n&&i+y<=n;i++)cnt[x+i][y+i]++; //东南
		for (int i(1);i<x;i++)cnt[i][y]++; //正北
		for (int i(x+1);i<=n;i++)cnt[i][y]++; //正南
		for (int i(1);i<y;i++)cnt[x][i]++; //正西
		for (int i(y+1);i<=n;i++)cnt[x][i]++; //正东
		cnt[x][y]++; //自己
	}
	for (int i(1);i<=n;i++)
		for (int j(1);j<=n;j++)
			ans+=cnt[i][j]==k;
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：Alarm5854 (赞：0)

推销一下我的新博客：https://yce3216037.github.io/post/luo-gu-p6200-ti-jie/

这道题就是一道水题，就是说有多少个点，使得在它的正北，正南，正东，正西，东北，东南，西北，西南和该点所连的直线能覆盖所有点，直接枚举每一个点，然后看一下这个点是否合法即可，时间复杂度为 $O(n^3)$。
### 代码如下：
```cpp
#include<cstdio>
using namespace std;
const int N = 100 + 10;
FILE *fin, *fout;
inline int read(int &x) {
	char c = 0; int f = x = 0;
	while (c < 48 || c > 57) {
		if (c == -1) return 0;
		if (c == '-') f = 1; c = fgetc(fin);
	}
	while (c > 47 && c < 58) x = (x << 3) + (x << 1) + (c & 15), c = fgetc(fin);
	if (f) x = -x; return 1;
}
template<class T, class... Args> inline int read(T &x, Args&... args) {
	return read(x) + read(args...);
}
inline int write(int x) {
	if (x < 0) return fputc(45, fout), write(-x);
	if (x > 9) write(x / 10);
	return fputc((x % 10) | 48, fout), 1;
}
int n, k, x, y, ans, vis[N][N];//vis[i][j]表示第i行第j列的位置有几个对手
inline void work(int x, int y) {
	int res = vis[x][y], temp = vis[x][y]; vis[x][y] = 0;//这个地方的vis[x][y]要先清零，否则可能会被算多次
	for (int i = 1; i <= n; ++i) res += vis[x][i];
	for (int i = 1; i <= n; ++i) res += vis[i][y];
	for (int i = x + 1, j = y + 1; i <= n && j <= n; ++i, ++j) res += vis[i][j];
	for (int i = x - 1, j = y + 1; i && j <= n; --i, ++j) res += vis[i][j];
	for (int i = x - 1, j = y - 1; i && j; --i, --j) res += vis[i][j];
	for (int i = x + 1, j = y - 1; i <= n && j; ++i, --j) res += vis[i][j];
    //8个方向的对手数量
	if (res == k) ++ans; vis[x][y] = temp;//别忘记加回来
}
int main() {
	#ifdef ONLINE_JUDGE
	fin = stdin;
	fout = stdout;
	#else
	fin = fopen("P6200.in", "rb");
	fout = fopen("P6200.out", "wb");
	#endif
	read(n, k);
	for (int i = 1; i <= k; ++i) read(x, y), ++vis[x][y];
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			work(i, j);//枚举每一个点即可
	write(ans);
	return 0;
}
```

---

## 作者：轮换对称式 (赞：0)

## 读题目，理解题意

八个方向分别是：正北，正南，正东，正西，东北，东南，西北，西南。

这八个方向呈“米”字状，如下图：

![](https://s1.ax1x.com/2020/03/22/8oAcZV.png)

（黑色点Bessie，红色点为Bessie可以射击到的格子，绿色点为Bessie射击不到的地方。）



------------

## 解题思路

分析题目，我们可以知道，奶牛所站立的地方必定为一个可以射击到所有对手的格子，即对于每一个对手，可以构造一个“米”字状，这些“米”字状的公共的交点即为解答。

因此容易想到每输入一个$K$，我们可以将能射击到该对手的所有位置打上标记，最后将矩阵遍历，找到被所有$K$打上标记的点，这些点就是奶牛Bessie可以站立的格子。其时间复杂度为$O(NK)$。

在本题中，$O(NK)$的复杂度足以通过此题，那么有没有更快的方法呢？

可以知道，暴力枚举Bessie所在的格子时间复杂度为$O(N^3)$，在本题中，比$O(NK)$要快，因此我们采取暴力枚举的方法。



------------


## 解答

1.给对手做标记（**可能有两个奶牛在同一位置上。**）：
```cpp
for (int i = 1 ; i <= k ; ++i)
	{
		int r , c;
		scanf("%d%d" , &r , &c);
		a[r][c]++;	//直接增加该位置上的奶牛数量。
	}
```

2.搜索“米”字状：
```cpp
void search(int r , int c)	//r即当前搜索到的行，c为列。
{
	int kill = 0;	//标记在该位置可以射击到的对手数。
	for (int i = 1 ; i <= n ; ++i)	//东、南、西、北四个方向搜索。
	{
		if (a[r][i])
			kill += a[r][i];
		if (i != r && a[i][c])	//此处若不进行特判，会对坐标为(r,c)的格子进行两次判断。
			kill += a[i][c];
	}
	int p = r , q = c;
	while (p > 1 && q > 1)	//东南、东北、西南、西北四个方向进行搜索。
		if (a[--p][--q])
			kill += a[p][q];
	p = r , q = c;
	while (p < n && q > 1)
		if (a[++p][--q])
			kill += a[p][q];
	p = r , q = c;
	while (p < n && q < n)
		if (a[++p][++q])
			kill += a[p][q];
	p = r , q = c;
	while (p > 1 && q < n)
		if (a[--p][++q])
			kill += a[p][q];
	if (kill == k)	//判断可以射击到的对手数
		ans++;
}
```




---

