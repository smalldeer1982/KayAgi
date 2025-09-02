# NEKO's Maze Game

## 题目描述

NEKO#ΦωΦ 刚刚给自己的电脑添加了一款新的迷宫游戏！

这个游戏的主要谜题，是一个在 $2 \times n$ 的矩形网格上的迷宫。NEKO 的任务是操控女主角 Nekomimi 从格子 $(1, 1)$ 开始，移动到位于格子 $(2, n)$ 的大门处，并离开迷宫。女主角只能在有公共边的两个格子之间移动。

然而在游戏的某些时刻，有些格子会改变它们的状态：从正常的地面变成岩浆（禁止移动到岩浆格子上）或反过来（让该格子再次变得能够通行）。游戏刚开始时，每个格子都是正常的地面。

当直播过去了数个小时后，NEKO 才终于弄明白了，只有 $q$ 个这样的时刻：第 $i$ 个时刻会翻转格子 $(r_i, c_i)$ 的状态（从地面变成岩浆或相反）。

知道了这些后，NEKO 想问在每个时刻结束后，还是否有可能从格子 $(1, 1)$ 移动到格子 $(2, n)$，并且不经过岩浆格子。

虽然 NEKO 是一个硬核玩家兼热门主播，她还是没有足够的[脑力](https://www.bilibili.com/video/av5299187)去解答这些问题。你可以帮帮她吗？

## 样例 #1

### 输入

```
5 5
2 3
1 4
2 4
2 3
1 4```

### 输出

```
Yes
No
No
No
Yes```

# 题解

## 作者：Konnyaku_LXZ (赞：5)

$2 \times N$ 的矩形网格有个特殊性质，对于一个点 $(1,x)$ ，若其为岩浆，则它挡路的情况有且仅有以下三种：

### ①$(1,x)$ 和 $(2,x)$ 同时为岩浆
### ②$(1,x)$ 和 $(2,x-1)$ 同时为岩浆
### ①$(1,x)$ 和 $(2,x+1)$ 同时为岩浆

对于点 $(2,x)$ 也是一样。

所以我们开一个计数器，每次将一个点修改成岩浆时判断是否会新出现挡路的情况，如果有则计数器加上新出现的情况数量；当一个点被修改成普通的地面时，判断是否有挡路的情况消失，如果有则计数器减去消失的情况数量。

Code:

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;

const int MAXN=1e5+50;

int N,Q,x,y,cnt=0,t[2][MAXN];//cnt是计数器,t存储每个点的情况

void Init(){
	memset(t,0,sizeof(t));
	scanf("%d%d",&N,&Q);
}

void Solve(){
	scanf("%d%d",&x,&y);
	--x;
	t[x][y]^=1;//修改当前点的状态
	if(t[x^1][y-1]) cnt+=t[x][y]?1:-1;//三种挡路的情况
	if(t[x^1][y]) cnt+=t[x][y]?1:-1;
	if(t[x^1][y+1]) cnt+=t[x][y]?1:-1;
}

void Print(){
	puts(cnt>0?"NO":"YES");//有挡路的情况则输出NO
}
int main(){
	Init();
	while(Q--){
		Solve();
		Print();
	}
	return 0;
}
```

---

## 作者：pigstd (赞：5)

玄学的线段树做法

思路：如果不能通过，那么就可能有下面几种情况:

![](https://cdn.luogu.com.cn/upload/image_hosting/07tgg5ox.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/aztrgszv.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/gnog5gzv.png)
(其中'X'表示不能经过)

即对于点$(x,y)$（把$flag[x][y]$标记为$1$）,如果$flag[d(x)][y]$,$flag[d(x)][y-1]$,$flag[d(x)][y+1]$中有一个为$1$,就无法通过了。（附：$d(x)$指如果$x$为$1$，则返回$2$，否则返回$1$）

那么如果每次把一个点（$x,y$）变为无法通过，则先把$flag[x][y]$设为$1$,然后如果$flag[d(x)][y]$为$1$,则把该点和原来的点+1，同理，其他两个点也这么操作

如果每次把一个点（$x,y$）变为可以通过，则先把$flag[x][y]$设为$0$,然后如果$flag[d(x)][y]$为$1$,则把该点和原来的点-1，同理，其他两个点也这么操作

如果想判断是否通行，则在所有点中找到一个最大值$maxn$，如果$maxn$为$0$，就说明全部都是$0$，即可以通过

然后用线段树维护每个点上的值即可，时间复杂度:$O(nlogn)$

c++代码如下:
```cpp
#include<bits/stdc++.h>
using namespace std;
 
const int M=1e5+10;
int n,q,sum[3][M];
bool flag[3][M];
 
int d(int a)
//即上文的d函数
{
	if (a==1)
		return 2;
	else
		return 1;
}
 
int f(int x,int y)
//一开始每一个点是二维的，这个函数可以把每一个二维的点变为一个一维的数
{
	return (x-1)*n+y;
}
 
struct node
{
	int tl,tr,sum;
}a[4*2*M];
 
void build(int k,int l,int r)
{
	a[k].tl=l,a[k].tr=r;
	if (l==r)
		return;
	int Mid=(l+r)>>1;
	build(k<<1,l,Mid);
	build(k<<1|1,Mid+1,r);
}
 
void add(int k,int l,int z)
{
	if (l>a[k].tr||l<a[k].tl)
		return;
	if (l==a[k].tl&&l==a[k].tr)
	{
		a[k].sum+=z;
		return;
	}
	add(k<<1,l,z),add(k<<1|1,l,z);
	a[k].sum=max(a[k<<1].sum,a[k<<1|1].sum);
}
 
int quary(int k,int l,int r)
{
	if (l>a[k].tr||r<a[k].tl)
		return 0;
	if (l<=a[k].tl&&r>=a[k].tr)
		return a[k].sum;
	return max(quary(k<<1,l,r),quary(k<<1|1,l,r));
}
//以上都是线段树
int main()
{
	scanf("%d%d",&n,&q);
	build(1,1,n);
	for (int i=1;i<=q;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		int k=f(x,y);
		if (!flag[x][y])
		{
			flag[x][y]=1;
			if (flag[d(x)][y-1])
				add(1,f(d(x),y-1),1),add(1,k,1);
			if (flag[d(x)][y])
				add(1,f(d(x),y),1),add(1,k,1);
			if (flag[d(x)][y+1])
				add(1,f(d(x),y+1),1),add(1,k,1);
		}
		else
		{
			flag[x][y]=0;
			if (flag[d(x)][y-1])
				add(1,f(d(x),y-1),-1),add(1,k,-1);
			if (flag[d(x)][y])
				add(1,f(d(x),y),-1),add(1,k,-1);
			if (flag[d(x)][y+1])
				add(1,f(d(x),y+1),-1),add(1,k,-1);
		}
		int q=quary(1,1,f(2,n));//f(2,n)是最大的点
		if (q==0)
			printf("Yes\n");
		else
			printf("No\n");
	}
	return 0;
}
```

---

## 作者：zjh111111 (赞：3)

#### $CF1292A$ $\ NEKO's\ Maze\ Game$

[$problem$ $link$](https://www.luogu.com.cn/problem/CF1292A)

【题意】

一个$2\times n$的地图，起点$(1,1),$ 终点$(2,n)$。

只能上下左右走，即不能斜着走。

$q$次改变，每次改变$(ri,ci)$的状态 $($可走->不可走，不可走->可走$)$。

$(1,1)$与$(2,n)$不会改变。

问每次改变后能否从$(1,1)$到达$(2,n)$。

【思路】

楼下大佬的图已经很清楚了。

如果$(x,y)$ $(y\in(1,n))$不能走,且$(3-x,y-1)$或$(3-x,y)$或$(3-x,y+1)$不能走, 那么就无法到达。

$(3-x$表示另一行，因为$x\in[1,2])$

当然上面的$x$和$y$都是整数。

所以就记录一下有几种上述情况，如果大于等于$1$种，就为$No$。

$0$种就是$Yes$。

建议难度评级 普及$-$。


【$code$】

```cpp
#include <bits/stdc++.h>
#define For(i,l,r) for (register int i=l; i<=r; i++)
using namespace std;
typedef unsigned long long LL;
typedef signed long long ll;
template <typename T>
inline void read(T &x) {
	char c = getchar(); int w = 1; x = 0;
	while (!isdigit(c))
		(c == '-') && (w = -w), c = getchar();
	while (isdigit(c))
		x = (x << 1) + (x << 3) + (c ^ '0'), c = getchar();
	x *= w;
}

int n, q, ri, ci, cnt = 0;
bool f[3][100010];
int main() {
	read(n); read(q);
	while (q --) {
		read(ri); read(ci);
		if (f[ri][ci]) { //从不可走到可走
			if (f[3-ri][ci]) -- cnt; //原来算上去的都减掉
			if (f[3-ri][ci-1]) -- cnt;
			if (f[3-ri][ci+1]) -- cnt;
		}
		else { //从可走到不可走
			if (f[3-ri][ci]) ++ cnt; //加上去
			if (f[3-ri][ci-1]) ++ cnt;
			if (f[3-ri][ci+1]) ++ cnt;
		}
		f[ri][ci] = !f[ri][ci]; //当前状态改变
		if (cnt) puts("No");
			else puts("Yes");
	}
	getchar();
	return 0;
}

```

之前可走不可走写反了哈 $ $ 已改正。

另外这题的地图拓展成 3*n 的谁会做，会的麻烦私信告诉我一声 万分感谢。

by 2020.2.14 16:30。

---

## 作者：gyh20 (赞：3)

我们先考虑在什么情况下无法到达。


| |  | x |  |  |
| -----------: | -----------: | -----------: | -----------: | -----------: |
|  | y | y | y |  |
假如$x$位置被占，那么如果再占$y$位置中的任何一个都会导致无法到达。

统计这样的对数再判断是不是$0$即可。

代码:
```cpp
#include<cstdio>
#include<iostream>
#include<cmath>
#include<cstring>
#define re register
using namespace std;
int t,n,a[100002],b[100002],c,q,x,y;
signed main(){
scanf("%d%d",&n,&q);
for(re int i=1;i<=q;++i){
	scanf("%d%d",&x,&y);
	if(x==1){
		if(a[y]){
			if(b[y-1])--c;
			if(b[y])--c;
			if(b[y+1])--c;
			a[y]^=1;
		}
		else{
			if(b[y+1])++c;
			if(b[y-1])++c;
			if(b[y])++c;
			a[y]^=1;
		}
	}
	else{
		if(b[y]){
			if(a[y-1])--c;
			if(a[y+1])--c;
			if(a[y])--c;
			b[y]^=1;
		}
		else{
			if(a[y-1])++c;
			if(a[y+1])++c;
			if(a[y])++c;
			b[y]^=1;
		}
	}
	if(c)puts("No");
	else puts("Yes");
}
	}
```


---

## 作者：寒鸽儿 (赞：2)

更高更妙的骗分技巧  
即便想不出正解,但是AC还是要AC的  
被堵住的情况只有同一列有两个lava或者相邻列上下各一个lava。  
把两行转化为两个01串$s_1$、$s_2$,显然只要$(s_1 \& s_2 == 0) \space\space \&\& \space\space ((s_1 << 1) \& s_2 ==0) \space\space \&\& \space\space ((s_1>>1)\&s_2 == 0) $为真就是堵上了。  
直接模拟的话单次修改查询的复杂度是$O(n)$,$q$次的复杂度是$O(qn)$。是无法承受的。  
考虑用bitset优化常数,这样的话就变成$O(\frac{1}{32}qn)$(不知道能不能这么表示),还是可以接受的。  
进一步优化常数:移动是很费时间的,我们建立三个串$s_{11}$、$s_{12}$、$s_{13}$分别表示$s_1$、$s_1 << 1$、$s_1 >> 1$。修改时直接对三个串进行修改。  
复杂度:$O(\frac{1}{32}qn)$  
```cpp
#include <cstdio>
#include <bitset>

using namespace std;

bitset<100100> s11, s12, s13, s2;


int main() {
	int n, q, r, c;
	scanf("%d %d", &n, &q);
	while(q--) {
		scanf("%d %d", &r, &c);
		if(r == 1) {
			s11.flip(c);
			if(c - 1 > 0) s12.flip(c - 1);
			if(c + 1 <= n) s13.flip(c + 1);
		} else {
			s2.flip(c);
		}
		if((s11 & s2).none() && (s12 & s2).none() && (s13 & s2).none()) {
			printf("Yes\n");
		} else {
			printf("No\n");
		}
	}
	return 0;	
}
```

---

## 作者：Su_Zipei (赞：1)

## 大意
有一个$2×n$的迷宫，每次可以让一个块不能通过或可以通过，问每次修改后是否可以从起点到终点
## 分析
先说说我的想法，暴力的话$O(NM)$，时限是$1.5s$，好像是差不多，但是一般卡着时间效率的代码都会T掉，所以暴力肯定不行，因为只有0和1俩状态，可以用$bitset$但我$bitset$只会用$count$，所以还是算了。

再想的话就是考虑什么时候能从起点到终点，这道题很有意思的就是它宽度只有2，当且仅当一个块与其对着的三个块都不同时不可以通过时，即不形成墙，才可以走到，所以维护这个就好。
![](https://cdn.luogu.com.cn/upload/image_hosting/cnnxcn49.png?x-oss-process=image/resize,m_lfit,h_00,w_600)

也就是说，当修改4时，分别判断一下1，2，3就好了，这样的话可以做到$O(M)$的时间复杂度，可以过。

下面讨论一下这种做法的正确性，当1-4，3-4，2-4都形成墙时，说明至少要拆三次才能通过，而拆除任意一堵墙都不能使其联通，故至少要拆三次，其他情况同理。
```
#include<iostream>
#include<algorithm>
using namespace std;
const int N=1e5+10;
int q[2][N];
inline int read(){
    int x=0;
    char ch=getchar();
    while(ch<'0'||ch>'9')ch=getchar();
    while(ch<='9'&&ch>='0'){
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x;
}
int main(){
    int cnt=0;
    int n=read(),m=read();
    while(m--){
        int a=read(),b=read();
        a--;
        if(q[a][b]){
            if(q[a^1][b-1])cnt--;
            if(q[a^1][b])cnt--;
            if(q[a^1][b+1])cnt--;
        }else {
            if(q[a^1][b-1])cnt++;
            if(q[a^1][b])cnt++;
            if(q[a^1][b+1])cnt++;
        }
        q[a][b]^=1;
        if(cnt)cout<<"No"<<'\n';
        else cout<<"Yes"<<'\n';
    }
}
```

---

## 作者：Meatherm (赞：1)

当答案为 `No` 的时候，必定存在两个点 $i,j$，使得它们不在同一行且它们的列坐标差的绝对值 $\leq 1$。

像这样：

![https://cdn.luogu.com.cn/upload/image_hosting/8ja9kvv0.png](https://cdn.luogu.com.cn/upload/image_hosting/8ja9kvv0.png)

出现图上任意一种情况的时候，路都会被封住，答案是 `No`。

考虑维护图上这样的点对数量。


当一个点从 $0$ 变 $1$ 的时候，如果它所在行的另外一行与它列坐标差 $\leq 1$ 的点是 $1$，点对数量 $+1$。注意这样的点有 $3$ 个。

像这样：

![I AK IOI](https://cdn.luogu.com.cn/upload/image_hosting/zq8bgm8v.png)

当一个点从 $1$ 变 $0$ 的时候，如果它所在行的另外一行与它列坐标差 $\leq 1$ 的点是 $1$，点对数量 $-1$（因为在之前这个点对一定是对答案有贡献的）。



当点对数量为 $0$ 时，答案是 `Yes`，反之是 `No`。

```cpp
# include <bits/stdc++.h>
# define rr register
const int N=200010;
bool a[2][N];
int n,q;
int ans;
int main(void){
	std::cin>>n>>q;
	for(rr int i=1,x,y;i<=q;++i){
		std::cin>>x>>y;
		--x;//把 x 减一下 这样就可以用 x^1 获取它的相反行
		a[x][y]=!a[x][y];
		if(a[x][y]){
			for(rr int j=std::max(1,y-1);j<=std::min(n,y+1);++j){
				if(a[x^1][j]){
					++ans;
				}
			}
		}else{
			for(rr int j=std::max(1,y-1);j<=std::min(n,y+1);++j){
				if(a[x^1][j]){
					--ans;
				}
			}
		}
		if(!ans){
			puts("Yes");
		}else{
			puts("No");
		}
	}
	return 0;
}
```

---

## 作者：Naganorhara_Yoimiya (赞：0)

# 题解：CF1292A NEKO's Maze Game

## 思路
这道题目还是比较简单的。

我们发现，当添加了一个岩浆块 $(x,y)$ 时，当且仅当 $(3-x,y),(3-x,y+1),(3-x,y-1)$ 中有一个及以上岩浆块，才可以构成挡路的情况。

我们称一对点 $(1,y_1)$ 与 $(2,y_2)$ 可以构成一对“挡路的情况”，当且仅当 $|y_1- y_2| \le 1$。因此，我们使用 $cnt$ 统计“挡路的情况”。我们可以统计 $(3-x,y),(3-x,y+1),(3-x,y-1)$ 里面有几个岩浆，如果当前块是从平地变成岩浆，那么 $cnt$ 就加上岩浆个数，否则减去岩浆个数。

时间复杂度 $O(q)$。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5+10; 
int n,q,cnt = 0;
bool ma[3][(maxn<<1)+100];

int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> n >> q;
	memset(ma,0,sizeof(ma));
	for(int i = 1,x,y;i <= q;i++){
		cin >> x >> y;
		int tmp = 0;
		if(ma[3-x][y] == 1) tmp++;
		if(ma[3-x][y+1] == 1) tmp++;
		if(ma[3-x][y-1] == 1) tmp++; 
		if(ma[x][y] == 0) cnt += tmp,ma[x][y] = 1;
		else cnt -= tmp,ma[x][y] = 0;
		if(cnt != 0) cout << "No\n";
		else cout << "Yes\n";
	} 
	return 0;
}
```

---

## 作者：lizihan250 (赞：0)

# Codeforces Round 614 Div 2 C & Div 1 A. NEKO's Maze Game

## 题意简述

给定一个 $2 \times n (1 \le n \le 10^5)$ 的网格图，一开始时所有点都可以通行。现进行 $q (1 \le q \le 10^5)$ 次操作，每次操作会将一个原来可以通行的点改为不可通行，或将一个原来不可通行的点改为可以通行。问：每次操作后，能否只通过移动到上下左右相邻的可以通行的点，从点 $(1,1)$ 走到 $(2,n)$。

## 解题思路

稍微思考一下，我们发现，点 $(x_0,y_0)$ 与其它点一起构成“屏障”，使得主角无法从 $(x_0,y_0-1)$ 移动到 $(x_0,y_0+1)$，当且仅当存在 $(3-x_0,y_0-1),(3-x_0,y_0),(3-x_0,y_0+1)$ 中的至少一个。

因此，不妨记录每次操作时，全局的“屏障”数量。若将 $(x_0,y_0)$ 从空地变为障碍，则全局“屏障”数增加 $(3-x_0,y_0-1),(3-x_0,y_0),(3-x_0,y_0+1)$ 中障碍的数量；反之，则减去相应的数量。每次操作结束后进行一次判定：若全局“屏障”数为 $0$，则答案为 `Yes`，否则为 `No`。时间复杂度 $O(q)$。

## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q,ux,uy,sum=0;
bool ok[3][100005];
int main()
{
    memset(ok,0,sizeof(ok));
    scanf("%d %d",&n,&q);
    while(q--)
    {
        scanf("%d %d",&ux,&uy);
        if(ok[ux][uy])
        {
            if(ok[3-ux][uy-1]) sum--;
            if(ok[3-ux][uy]) sum--;
            if(ok[3-ux][uy+1]) sum--;
        }
        else
        {
            if(ok[3-ux][uy-1]) sum++;
            if(ok[3-ux][uy]) sum++;
            if(ok[3-ux][uy+1]) sum++;
        }
        ok[ux][uy]^=1;
        printf("%s\n",sum==0?"Yes":"No");
    }
    return 0;
}
```

---

## 作者：liuli688 (赞：0)

### 思路：
题目中的 $2 \le n \le 10^5,1 \le q \le 10^5$ 告诉我们这道题肯定不能 DFS（会 TLE）。

观察地图每一时刻的变化，会发现地图每时刻只会改变一个格子的状态，而改变一个格子的状态对于 Nekomimi 的影响是有限的：若 $(1,c_i)$ 是岩浆，则它会挡住 Nekomimi 的路（即 Nekomimi 能移动到与其相邻的格子却无法到达终点）的情况只有以下三种：
- $(2,c_{i-1})$ 是岩浆
- $(2,c_i)$ 是岩浆
- $(2,c_{i+1})$ 是岩浆

即下图中任意一个 `#` 是岩浆时就会无法到达终点。（`.` 是正常的地面，`X` 是岩浆）
```
..
..
.#
X#
.#
..
..
```
所以对于每次翻转状态只要检查一下三个格子的状态即可，再对应加上贡献。用变量储存一下所有格子有多少“挡路的贡献”。贡献为零则可以通过，输出 `Yes`，否则为 `No`。

---

## 作者：Larry76 (赞：0)

## 题目大意：
给你 $2\times n$ 的迷宫，初始时没有任何障碍，给定 $q$ 次询问，每次询问给予坐标 $(x,y)$，问将坐标 $(x,y)$ 反转状态（即无障碍变有障碍，有障碍变无障碍）后，该迷宫还能否到达终点 $(2,n)$，并应用更改。

## 题目分析：
因为是 $2\times n$ 的迷宫，很显然的是，若下方一个位置为有障碍，则他的左上角或正上方或右上角有障碍时，角色无法到达终点。

同理，对于上方的情况，就是他的左下角或正下方或右下角有障碍时，角色无法到达终点。

如果觉得不大显然的话，可以看下图：

![帮助理解的图](https://s1.ax1x.com/2022/10/28/x4n58S.png)

故，我们只需要统计一下形成关联的地方有多少就行了，时间复杂度 $O(q)$。

## 代码实现：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define TIME_LIMIT (time_t)1.5e3
#define dbg(x) cerr<<#x<<": "<<x<<endl;
#define MAX_SIZE (int)114514
bool bmap[2][MAX_SIZE];
signed main() {
    ios::sync_with_stdio(false);
#ifdef LOCAL
    freopen("in.in", "r", stdin);
    freopen("out.out", "w", stdout);
    time_t cs = clock();
#endif
    //========================================
    int n, q;
    cin >> n >> q;
    int blocked = 0;

    while (q--) {
        int x, y;
        cin >> x >> y;
        x -= 1;

        if (x) {
            if (bmap[x][y]) {
                blocked -= bmap[x - 1][y - 1];
                blocked -= bmap[x - 1][y];
                blocked -= bmap[x - 1][y + 1];
            } else {
                blocked += bmap[x - 1][y - 1];
                blocked += bmap[x - 1][y];
                blocked += bmap[x - 1][y + 1];
            }
        } else {
            if (bmap[x][y]) {
                blocked -= bmap[x + 1][y - 1];
                blocked -= bmap[x + 1][y];
                blocked -= bmap[x + 1][y + 1];
            } else {
                blocked += bmap[x + 1][y - 1];
                blocked += bmap[x + 1][y];
                blocked += bmap[x + 1][y + 1];
            }
        }

        bmap[x][y] = !bmap[x][y];

        if (blocked)
            cout << "No" << endl;
        else
            cout << "Yes" << endl;
    }

    //========================================
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
    time_t ce = clock();
    cerr << "Used Time: " << ce - cs << " ms." << endl;

    if (TIME_LIMIT < ce - cs)
        cerr << "Warning!! Time exceeded limit!!" << endl;

#endif
    return 0;
}
```

---

## 作者：YouXam (赞：0)


## 分析

这道题的大概思路还是挺好想的,大概就是每次输入的时候记录下挡路的"单元"

![](https://img2020.cnblogs.com/blog/1975074/202004/1975074-20200404182101617-467743414.png)


上图用圈出来的部分都是一个单元,可以阻挡玩家通过,如果整个地图只有一个熔浆单元格,显然是不足以构成一个单元,至少两个(上面三种情况)才可以构成.

那么思路就有了,如果在反转的时候对面三个格子已经有了熔浆单元,单元的数量加一.

![](https://img2020.cnblogs.com/blog/1975074/202004/1975074-20200404182116097-812467219.png)



在反转的时候,如果对面已经有了熔浆单元,说明这个格子在从地面到熔浆的过程中,单元的数量增加了,那么反转的时候自然要减回去.

## 代码

```cpp
#include <cstdio>
int vis[2][100005];
int n, q, x, y, ans;
int main() {
    scanf("%d%d", &n, &q);
    while (q--) {
        scanf("%d%d", &x, &y);
        x--;
        if (vis[x][y]) {
            if (vis[!x][y]) ans--;
            if (vis[!x][y + 1] && y + 1 <= n) ans--;  //注意边界
            if (vis[!x][y - 1] && y - 1 >= 1) ans--;
        } else {
            if (vis[!x][y]) ans++;
            if (vis[!x][y + 1] && y + 1 <= n) ans++;
            if (vis[!x][y - 1] && y - 1 >= 1) ans++;
        }
        vis[x][y] = !vis[x][y];
        printf("%s\n", ans ? "No" : "Yes");
    }
}
```

---

## 作者：DarthVictor (赞：0)

## 题目
[题目链接](https://www.luogu.com.cn/problem/CF1292A)
## 解说
思维题，想明白了极其简单。

首先，考虑一下什么情况下路会被封死：

![](https://cdn.luogu.com.cn/upload/image_hosting/4o0c9bbe.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

共有以上三种情况。

所以很显然我们不需要每次都从1到n找一遍有没有路，每改变一个格子的状态就检查一下另一列三个格子的状态即可。再用一个ans变量储存一下共有多少对足以堵死路的格子。ans为零则YES，否则就NO。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=100000+5;
bool a[3][maxn];
int n,q;
int main(){
    ios::sync_with_stdio(false);
    cin>>n>>q;
    int ans=0;
    for(int i=1;i<=q;i++){
        int x,y;
        cin>>x>>y;
        if(x==1){
            if(a[x][y]){
                a[x][y]=0;
                if(a[2][y]) ans--;
                if(a[2][y+1]) ans--;
                if(a[2][y-1]) ans--;
            }
            else{
                a[x][y]=1;
                if(a[2][y]) ans++;
                if(a[2][y+1]) ans++;
                if(a[2][y-1]) ans++;
            }
        }
        else{
            if(a[x][y]){
                a[x][y]=0;
                if(a[1][y]) ans--;
                if(a[1][y+1]) ans--;
                if(a[1][y-1]) ans--;
            }
            else{
                a[x][y]=1;
                if(a[1][y]) ans++;
                if(a[1][y+1]) ans++;
                if(a[1][y-1]) ans++;
            }
        }
        if(ans) cout<<"No"<<endl;
        else cout<<"Yes"<<endl;
    }
    return 0;
}
```


---

## 作者：YLWang (赞：0)

乱搞题。

像这种题，只要是个算法都是能过的。

我们考虑答案是"Yes"时，当且仅当**不**存在$i, j$使得$|i-j|<=1$且$a[1][i] == a[2][j] == 1$

于是这启发我们维护所有$|i-j|<=1$且$a[1][i] == a[2][j] == 1$的$(i, j}$对数

这非常好维护

代码也极其好写

```cpp
const int MAXN = 100005;
int a[2][MAXN], n, Qnum, num;
signed main()
{
	cin >> n >> Qnum;
	while(Qnum--) {
		int x = read()-1, y = read();
		if(a[x][y]) num -= a[x^1][y-1] + a[x^1][y+1] + a[x^1][y];
		else num += a[x^1][y-1] + a[x^1][y+1] + a[x^1][y];
		a[x][y] ^= 1;
		puts(num ? "No" : "Yes");
	}
    return 0;
}
```

---

## 作者：Erina (赞：0)

这并不是一个简单的线段树算法......

其实这一题有很多想不到的黑科技可以使用.

如果是暴力的话, 那么应该是一个类似于DP的方法对吧...... 就是你维护一个数组表示现在这个地方能不能走到

就是每一行的第几个格子能不能走到.

那么我们发现每一次是一个向量进一个向量出, 长度还一样, 果断线段树优化矩阵乘法. 线段树的每一个节点的`mat[i][u]`就是从第i个地方出发能不能到达线段右边的第u个地方。

最后看的其实就是能不能从(1,0)走到(2,n+1)

然后就是这样了.

那个线段树维护最小值的没有看懂...... 这是我对于线段树做这道题的思路, 可以拓展到很多题目上, 比如将大小变为`5*n`什么的......

代码:

```cpp
#include<iostream>
#include<cstring>
#define mid ((l+r)>>1)
using namespace std;
namespace fio{
	streambuf*in=cin.rdbuf();
	char bb[1000000],*s=bb,*t=bb;
	#define gc() (s==t&&(t=(s=bb)+in->sgetn(bb,1000000),s==t)?EOF:*s++)
	inline int read(){
		int x=0;
		char ch=gc();
		while(ch<48)ch=gc();
		while(ch>=48)x=x*10+ch-48,ch=gc();
		return x;
	}// 简单的快读
}using fio::read;
int sum;
int n,q;
int arr[100005][2];
class mat{
public:
	bool huaji[2][2];
	mat(){memset(huaji,0,sizeof(huaji));}
	bool*operator[](int x){return huaji[x];}
	mat operator * (mat _){
		mat ans;
		for(int i=0;i<2;i++)for(int u=0;u<2;u++)for(int j=0;j<2;j++)
			ans[i][u]|=huaji[i][j]&&_[j][u];
		return ans;
	}// 矩阵乘法
}tree[400005];
void build(int x,int l,int r){
	memset(tree[x].huaji,1,4*sizeof(bool));
	if (l != r)build(x << 1, l, mid), build(x << 1 | 1, mid + 1, r);
}
void change(int x,int l,int r,int p){
	if (l == r) {
		memset(tree[x].huaji, 1, 4 * sizeof(bool));
		if (arr[p][0])tree[x][0][1] = tree[x][0][0] = tree[x][1][0] = 0;
		if (arr[p][1])tree[x][1][0] = tree[x][0][1] = tree[x][1][1] = 0;
	}
	else if (p <= mid)change(x << 1, l, mid, p), tree[x] = tree[x << 1] * tree[x << 1 | 1];
	else change(x << 1 | 1, mid + 1, r, p), tree[x] = tree[x << 1] * tree[x << 1 | 1];
}// 线段树的单点修改操作
int main(){
	n=read(),q=read();
	build(1, 1, n);
	while(q--){
		int x=read()-1,y=read();
		swap(x,y);
		arr[x][y]^=1;
		change(1,1,n,x);
		cout<<(tree[1][0][1]?"YeS\n":"nO\n");// 判断
	}
}
```

不要在意那个"YeS", "nO"啦......


---

