# [ABC359C] Tile Distance 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc359/tasks/abc359_c

座標平面上に $ 2\times1 $ の大きさのタイルが敷き詰められています。 タイルは、次の規則に従って敷き詰められています。

- 整数の組 $ (i,j) $ に対し、正方形 $ A\ _\ {i,j}=\lbrace(x,y)\mid\ i\leq\ x\leq\ i+1\wedge\ j\leq\ y\leq\ j+1\rbrace $ は $ 1 $ つのタイルに含まれる。
- $ i+j $ が偶数のとき、$ A\ _\ {i,j} $ と $ A\ _\ {i\ +\ 1,j} $ は同じタイルに含まれる。
 
ただし、タイルは境界を含むものとし、共通部分が正の面積をもつような $ 2 $ つの異なるタイルは存在しないとします。

原点の近くでは、タイルは以下のように敷き詰められています。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_abc359_c/85986a05648888be0c6d0706034a45ff07ff8b7a.png)

高橋君は、はじめ座標平面上の点 $ (S\ _\ x+0.5,S\ _\ y+0.5) $ にいます。

高橋君は、次の移動を好きなだけ繰り返します。

- 上下左右の方向と正の整数 $ n $ を選ぶ。その方向に $ n $ だけ進む。
 
高橋君が異なるタイルを通るたび、高橋君は通行料を $ 1 $ だけ支払います。

高橋君が点 $ (T\ _\ x+0.5,T\ _\ y+0.5) $ にたどり着くために支払わなければならない通行料の最小値を求めてください。

## 说明/提示

### 制約

- $ 0\leq\ S\ _\ x\leq2\times10\ ^\ {16} $
- $ 0\leq\ S\ _\ y\leq2\times10\ ^\ {16} $
- $ 0\leq\ T\ _\ x\leq2\times10\ ^\ {16} $
- $ 0\leq\ T\ _\ y\leq2\times10\ ^\ {16} $
- 入力はすべて整数
 
### Sample Explanation 1

例えば、以下のように移動することで支払う通行料を $ 5 $ にすることができます。 !\[\](https://img.atcoder.jp/abc359/187d19c48a9a0fcedb2602063689ee77.png) - 左に $ 1 $ 進む。通行料を $ 0 $ 支払う。 - 上に $ 1 $ 進む。通行料を $ 1 $ 支払う。 - 左に $ 1 $ 進む。通行料を $ 0 $ 支払う。 - 上に $ 3 $ 進む。通行料を $ 3 $ 支払う。 - 左に $ 1 $ 進む。通行料を $ 0 $ 支払う。 - 上に $ 1 $ 進む。通行料を $ 1 $ 支払う。 支払う通行料を $ 4 $ 以下にすることはできないので、`5` を出力してください。

### Sample Explanation 2

通行料を支払わなくてよい場合もあります。

### Sample Explanation 3

出力すべき値が $ 32\operatorname{bit} $ 整数の範囲に収まらない場合があることに注意してください。

## 样例 #1

### 输入

```
5 0
2 5```

### 输出

```
5```

## 样例 #2

### 输入

```
3 1
4 1```

### 输出

```
0```

## 样例 #3

### 输入

```
2552608206527595 5411232866732612
771856005518028 7206210729152763```

### 输出

```
1794977862420151```

# 题解

## 作者：Redamancy_Lydic (赞：5)

## 背景

去中考了，比赛没打，来补一下题。

## 分析

这道题让我想起了[这道题](https://www.luogu.com.cn/problem/AT_abc353_f)（连题目名称都是连着的），不过显然要简单一些。

这道题显然要推一些式子。我们发现，和上面提到的那道题目一样，沿着对角线走台阶，纵坐标走到以后再走横坐标显然是最优策略。这时候的答案就是横纵坐标差的和的一半（这就不用证明了）。有一个细节就是当起点和终点在它所处的砖块中位置不同时，式子不成立，这时候应该改变一下，我这里把它们都变到了它所处砖块的左边，这样是不影响答案的。放一下代码：

```cpp
   int x=abs(ex-sx),y=abs(ey-sy);
	if(x%2==0&&y%2==1||x%2==1&&y%2==0)
	{
		if((sx+sy)%2==1)sx--;
		else ex--;
	}
```

但是当起点和终点横坐标差值小于纵坐标差值时，因为按照这个策略要往回走，所以显然要换方法。

多推几个样例可以发现，这种情况的答案就是纵坐标的差。我们来分析一下。（用了样例解释的图）

![](https://img.atcoder.jp/abc359/187d19c48a9a0fcedb2602063689ee77.png)

容易看出，这其实就是上面策略加上几个垂直上升的走法。这时候横坐标可以理解为是在纵坐标转移的时候顺带转移的，所以方法显然正确。

然后就做完了。

## Code

```cpp
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
//#include<atcoder/modint>
#define int long long
#define mod 998244353
using namespace std;
using namespace  __gnu_pbds;
inline int read()
{
	int w=1,s=0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')w=-1;ch=getchar();}
	while(isdigit(ch)){s=s*10+(ch-'0');ch=getchar();}
	return w*s;
}
const int maxn=1e6+10;
int sx,sy,ex,ey;
signed main()
{
//  freopen("xxx.in","r",stdin);
//	freopen("xxx.out","w",stdout);
	cin>>sx>>sy>>ex>>ey;
	int x=abs(ex-sx),y=abs(ey-sy);
	if(x%2==0&&y%2==1||x%2==1&&y%2==0)
	{
		if((sx+sy)%2==1)sx--;
		else ex--;
	}
	x=abs(ex-sx),y=abs(ey-sy);
	if(x<=y)cout<<y;
	else cout<<(x+y)/2;
	return 0;
}

```

---

## 作者：LuukLuuk (赞：3)

# 题解：AT_abc359_c [ABC359C] Tile Distance 2

### 题目大意
在二维平面上有许多方格，如题目中的图那样排列。现在你要从一个点走到另一个点，问最少要经过多少个格子。

---
### 题解
考虑贪心，因为一个方格是 $1 \times 2$ 大小的，所以横着走一格没有花费。则斜着走一格就只需要花费纵坐标上一格的距离走，横坐标上没有花费。故我们可以优先考虑斜着走，在纵坐标花费不变的情况下减少横坐标花费。如图：
![](https://cdn.luogu.com.cn/upload/image_hosting/4n9p0tbr.png)
另外，因为同一个格子不影响花费，我们可以将目标都移动到其所在格的右格便于处理。

---
### 代码
**注意开 `long long`！**
```cpp

#include <algorithm>
#include <cstdio>
using namespace std;

#define int long long
const int mxn = 2e16;
int deta_l, deta_r;
int a, b;
int c, d;
int ans;

void init(int &x, int &y) {
	swap(x, y);//先行后列 
	if (x % 2ll) {
		if (y % 2ll) {
			y++;
		}
	} else {
		if (y % 2ll == 0ll) {
			y++;
		}
	}
}

signed main() {
	scanf("%lld%lld", &a, &b);
	scanf("%lld%lld", &c, &d);
	init(a, b);
	init(c, d);
	deta_l = abs(a - c);
	deta_r = abs(b - d);
	ans = deta_l;
	deta_r = max(0ll, deta_r - deta_l);
	ans += (deta_r + 1ll) / 2ll;
	printf("%lld", ans);
	return 0;
}

```

---

## 作者：I_Love_DS (赞：3)

## 前言

第一眼看到题面的图：不难啊，bfs 一下不就好了？

而看到数据范围的我：$0 \le sx,sy,tx,ty \le 10^{16}$ 哦。。。

## 思路

贪心。

本文题解里：

> $x$ 或 $y$ 轴距离 为 两个点的 $x$ 或 $y$ 坐标的绝对值。

设答案为 $ans$。

1. 先竖着走完起点和终点的 $y$ 轴距离。此时，$ans \gets |ty - sy|$。

2. 为了之后方便，我们使 $sx$ 和 $tx$ 变成**他们所在的长方形中左面正方形的左下角坐标**。

3. 继上面的操作，我们设 $k = |sx - tx| - |sy - ty|$，其实就是从起始点走完起点和终点的 $y$ 轴距离的所在地点离终点的 $x$ 轴距离。（可借助[这位大佬的题解](https://www.luogu.com.cn/article/xtl9ppbo)的图理解一下）

4. 继上面的操作，如果 $k \le 0$，那么说明不用再花费额外的消费。否则每走 $2$ 个 $x$ 轴距离就要多消费 $1$，所以 $ans \gets ans + k \div 2$。

完结，撒花！

## 代码

注意一下 `long long` 就行。

```cpp
#include <bits/stdc++.h>
using namespace std;
long long sx, sy, ex, ey;
int main() {
	scanf("%lld%lld%lld%lld", &sx, &sy, &ex, &ey);
	long long ans = abs(ey - sy);
	//1
	if (sy % 2 == 0) sx -= abs(sx % 2);
	else sx -= abs((sx + 1) % 2);
	if (ey % 2 == 0) ex -= abs(ex % 2);
	else ex -= abs((ex + 1) % 2);
	//2
	long long k = (abs(ex - sx) - abs(ey - sy));
	//3
	ans += max(0LL, k / 2); //防止 k<=0
	//4
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：T_TLucas_Yin (赞：3)

容易发现，不管在什么位置向上或向下走一格，都需要花钱。所以，总花费肯定至少有 $|S_y-T_y|$ 元。同时这也是在纵方向移动的所有花费。

接下来考虑横向移动的钱。（又）容易发现，在一开始先按照横竖交替或竖横交替的顺序走，就不会花钱。所以，接下来可以分两种情况：

- 起点到终点的纵坐标跨度更大，则这样走完后需要纵向走完剩下的路程，需要在纵向花钱。

- 起点到终点的横坐标跨度更大，则这样走完后需要横向走完剩下的路程，需要在横向花钱。

对于第一种情况，由于我们先计算完了纵向花的所有钱，此时就不用考虑了。下面讨论第二种情况要在剩余的横向路径上花多少钱。

我们根据图例，把坐标格分为“在砖块左边”和“在砖块右边”两种类型。对于一条横向的路径，有两种情况：

- 左右端点类型相同，则需要花费 $\lfloor \frac{n}{2}\rfloor$ 元。
- 如果左端点是右边的格子，右端点是左边的格子，则需要花费 $\lfloor \frac{n}{2}\rfloor$ 元。
- 如果左端点是左边的格子，右端点是右边的格子，则需要花费 $(\lfloor \frac{n}{2}\rfloor+1)$ 元。

接下来还需要考虑如何判断一个坐标格的类型。找规律可得，对于一个点，如果它横纵坐标模 $2$ 的余数相同，则它在砖块的左边；否则它在砖块的右边。

接下来其实还需要特判一点：如果最后一段横向路径的起点和终点相距为 $1$ 的话，不能用上面的花费公式来算，而是要直接判断它们是否在同一块砖内，计算花费是 $1$ 还是 $0$。

~~很恶心。~~

```cpp
#include<bits/stdc++.h>
using namespace std;
long long sx,sy,ex,ey,sum;
int main(){
	cin>>sx>>sy>>ex>>ey;
	sx++,sy++,ex++,ey++;
	sum+=abs(sy-ey);//纵向的总花费 
	if(abs(sx-ex)<=abs(sy-ey)){//如果纵向跨度更大 
		cout<<sum;
		return 0;
	}
	long long k=abs(sy-ey),x,y;
	if(sx>ex) x=sx-k;
	else x=sx+k;
	if(sy>ey) y=sy-k;
	else y=sy+k;//计算斜着走完后的坐标 
	bool flag1=(x%2!=y%2),flag2=(ex%2!=ey%2);//表示起点和终点是否为右格子 
	if(flag1==flag2) sum+=abs(x-ex)/2;
	else{
		if(x>ex){
			if(flag1) sum+=abs(x-ex)/2;
			else sum+=abs(x-ex)/2+1;
		}
		else{
			if(flag1) sum+=abs(x-ex)/2+1;
			else sum+=abs(x-ex)/2;
		}
	}//分讨 
	cout<<sum;
	return 0;
}
```

---

## 作者：Guoguo2013 (赞：2)

据说这次 Atcoder 的 C、D 题比 E、F 题都难。

### 题意简介：
对于这样一面砖墙：  
![砖](https://cdn.luogu.com.cn/upload/image_hosting/ikjgod2s.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

你初始的位置在 $(S_x + 0.5, S_y + 0.5)$，也就是一个小格内，你要到达的位置是 $(T_x + 0.5, T_y + 0.5)$，也是一个小格内，由于数据保证：

- $0 \le S_x \le 2 \times 10^{16}$  
- $0 \le S_y \le 2 \times 10^{16}$  
- $0 \le T_x \le 2 \times 10^{16}$  
- $0 \le T_y \le 2 \times 10^{16}$

所以那张图我只给了右上部分。

每穿过一条边就要付 $1$ 的通行费（在一块砖内转悠不需要花钱），问最少需要多少通行费。

### 思路：
这个 C 题难就难在非常难想，这是一道明显的思维题。

首先，不管怎么腾挪，上下走总得穿墙，所以一开始先把答案设成 $\operatorname{abs}(S_y - T_y)$。

然后我们可以发现，到终点那一层的时候可以到达一些点。  
假设上面的 $\operatorname{abs}(S_y - T_y)$ 设成 $daan$。  
如果起点在一块砖的右半部分（怎么判断见代码），那么我们到终点那一层可到达的点就在 $S_x-daan-1 \sim S_x+daan$ 之间，反之，那么我们到终点那一层可到达的点就在 $S_x-daan \sim S_x+daan+1$ 之间。

如果 $T_x$ 就在这个范围之间，那就说明我们可以通过在砖里左右漂移从而使得我们只需要交 $daan$ 的通行费就行了。  
否则，就需要多交从范围的最右边（或最左边）走到 $T_x$ 需要的通行费。

### 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
#define PII pair< int, int >
#define MII map< int, int >
#define MIB map< int, bool >
#define x first
#define y second

using namespace std;

const int N = 1e5 + 5, mod = 998244353;
int daan, ma, mi;
PII s, t;
signed main(){
//	freopen("a.in", "r", stdin);
//	freopen("a.out","w",stdout);
	scanf("%lld%lld%lld%lld", &s.x, &s.y, &t.x, &t.y);
	daan += abs(s.y - t.y);
	if (s.y % 2){ // 如果初始位置在第一个位置空一格，后面两格一块砖的一行上。
		if (s.x % 2){ // 这就说明 Sx 在一块砖的左半部分
			ma = s.x + daan + 1;
			mi = s.x - daan;
		}
		else { // 这就说明 Sx 在一块砖的右半部分
			ma = s.x + daan;
			mi = s.x - daan - 1;
		}
	}
	else { // 如果初始位置在前面不空格，两格一块砖的行上。
		if (s.x % 2){ // 这就说明 Sx 在一块砖的右半部分
			ma = s.x + daan;
			mi = s.x - daan - 1;
		}
		else { // 这就说明 Sx 在一块砖的左半部分
			ma = s.x + daan + 1;
			mi = s.x - daan;
		}
	}
	if (mi <= t.x && t.x <= ma) printf("%lld", daan);
	else printf("%lld", daan + min((abs(mi - t.x) + 1) / 2, (abs(t.x - ma) + 1) / 2)); // 注意：每走两个格才需要交一的通行费，所以加一除以二就行了
	return 0;
}

```
这段代码虽然能过，但比较麻烦，更简单的办法是通过看 $S_y$ 和 $S_x$ 的奇偶性相不相等来判断能走到的范围，这里就不写了。

---

## 作者：kkxacj (赞：2)

#### 思路

看图可得，每次向上走一步，就可以到本来呆的方块的左上一格或右上边一格，也可以不走，下同理。

所以在开始时尽量让 $S_x$ 和 $T_x$ 尽可能近。

如果最近距离小于 $S_y$ 和 $T_y$ 的距离的话，就一定能到。

否则 $S_x$ 每次可以向左或右移动一步或两步，只用 $1$ 的消耗。

暴力分讨就完了。

**code**
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
namespace IO
{
	template<typename T>
	void read(T &_x){_x=0;int _f=1;char ch=getchar();while(!isdigit(ch)) _f=(ch=='-'?-1:_f),ch=getchar();while(isdigit(ch)) _x=_x*10+(ch^48),ch=getchar();_x*=_f;}
	template<typename T,typename... Args>
	void read(T &_x,Args&...others){Read(_x);Read(others...);}
	const int BUF=20000000;char buf[BUF],top,stk[32];int plen;
	#define pc(x) buf[plen++]=x
	#define flush(); fwrite(buf,1,plen,stdout),plen=0;
	template<typename T>inline void print(T x){if(!x){pc(48);return;}if(x<0) x=-x,pc('-');for(;x;x/=10) stk[++top]=48+x%10;while(top) pc(stk[top--]);}
}
using namespace IO;
int x,y,fx,fy,ans,l;
signed main()
{
	read(x),read(y);
	read(fx),read(fy);
	ans = abs(fy-y);
	if(abs(y) % 2 == 0) 
	{
		if(fx < x) 
		{
			x = x/2*2;
			if(fx < x)
			{
				if(abs(fy) % 2 == 0) fx = fx/2*2+1;
				else if(abs(fx) % 2 == 1) fx++;
			}
		} 
		else  if(fx > x)
		{
			x = x/2*2+1;
			if(fx > x)
			{
				if(abs(fy) % 2 == 0) fx = fx/2*2;
				else if(abs(fx) % 2 == 0) fx--;
			}
		}
	}
	else
	{
		if(fx < x) 
		{
			if(abs(x) % 2 == 0) x--;
			if(fx < x)
			{
				if(abs(fy) % 2 == 0) fx = fx/2*2+1;
				else if(abs(fx) % 2 == 1) fx++;
			}
		}
		else if(fx > x)
		{
			if(abs(x) % 2 == 1) x++;
			if(fx > x)
			{
				if(abs(fy) % 2 == 0) fx = fx/2*2;
				else if(abs(fx) % 2 == 0) fx--;
			}
		}
	}
	print(ans + (max(0ll,(abs(x-fx)-ans)+1)/2)); 
	flush();
	return 0;
}
/*

*/

```

---

## 作者：tzzl3035 (赞：1)

# AT_abc359_c 题解
### 题目大意
如图所示，有一面很大砖块墙，砖块交错叠放。询问从 $(S_x+0.5,S_y+0.5)$ 到 $(T_x+0.5,T_y+0.5)$ 的最小花费，每走到一块新砖头要一个花费，起点无需花费。
### 思路
观察数据范围，代码**时间复杂度只能为 $O(1)$ 并且要使用 `long long`**。所以，我们可以先将两个坐标按第 2 个条件变成左半砖的，算出 $T_x - S_x$ 和 $T_y - S_y$ 的绝对值，比较大小。我们发现，每次斜着走，只会在横坐标上增加或减少 $1$。所以，如果横向距离比纵向大，要用纵向距离加剩余的横向距离的一半，否则直接输出纵向距离即可。
### 代码
``` c++
#include <bits/stdc++.h> // 万能头
using namespace std;
using i64 = long long; // 方便打字
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
   
	// 输入
	i64 sx, sy, tx, ty;
	cin >> sx >> sy >> tx >> ty;
   	// 不用管第 1 个条件，直接按第 2 个条件进行特判，将其变成左半砖坐标即可
	if((sx + sy) & 1) sx -= 1;
	if((tx + ty) & 1) tx -= 1;
   	// 计算横向与纵向距离
	i64 x = abs(tx - sx);
	i64 y = abs(ty - sy);
   	// 按总结出来的规律进行输出
	if(x <= y) cout << y;
	else cout <<  y + (x - y) / 2;
	
	return 0;
}

```

[结果](https://atcoder.jp/contests/abc359/submissions/54834512)

---

## 作者：yegengghost (赞：0)

输的最惨的一次，以至于赛事只过了前两个。

这道题开始还想搜索（没救了）。

比较明显的一点是：答案等于纵向穿过的砖块数加横向穿过的砖块数。

纵向的贡献必定就是两个纵坐标之差的绝对值，横向比较难。

可以判断两个坐标分别是否在一个砖块的左边来做预处理，最后计算答案即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int sx,sy,tx,ty;
int read()
{
    int f=1,x=0;char ch;
    do{ch=getchar();if(ch=='-')f=-1;}while(ch<'0'||ch>'9');
    do{x=x*10+ch-'0';ch=getchar();}while(ch>='0'&&ch<='9');
    return f*x;
}
signed main()
{
	sx=read();
	sy=read();
	tx=read();
	ty=read();
    if(abs(sx+sy)%2)
		sx--;
    if(abs(tx+ty)%2)
		tx--;
	//判断两个坐标分别是否在一个砖块的右边
    int ans=abs(ty-sy);
    cout<<ans+max(0LL,(abs(sx-tx)-ans)/2);
}
```

---

