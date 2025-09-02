# 【MX-X17-T1】Walk,Walk,Walk

## 题目描述

在一个二维平面中，给你 $n$ 条与 $x$ 轴平行或与 $y$ 轴平行的直线，求从 $(sx,sy)$ 走到 $(tx,ty)$ 需要经过的最少的直线的数量。注意，可能存在直线经过起点坐标或者终点坐标，这种直线是无论如何都会被经过的；如果经过了多条重合的直线，也要被计算多次。

## 说明/提示

**【样例解释 #1】**

在样例 1 中，从 $(1,1)$ 直线走到 $(3,3)$ 将经过第一条及第三条直线。可以证明不存在经过直线数量更少的方案。

**【样例解释 #2】**

在样例 2 中，有两条直线经过起点，另外两条经过终点，所以四条直线都必须被经过。

**【数据范围】**

对于 $50\%$ 的数据，保证所有 $t=1$。

对于 $100\%$ 的数据，$1 \le n \le 10^5$，$t\in\{1,2\}$，$-10^9\le k,sx,sy,tx,ty \le 10^9$。

## 样例 #1

### 输入

```
3
1 2
2 0
2 2
1 1 3 3```

### 输出

```
2```

## 样例 #2

### 输入

```
4
1 1
1 1
1 2
1 2
1 0 2 0```

### 输出

```
4```

# 题解

## 作者：CR400BF_1145 (赞：3)

题目链接：[P13752](https://www.luogu.com.cn/problem/P13752)
## 题目大意
给定 $n$ 条平行于 $x$ 轴或 $y$ 轴的直线，现在要从点 $(sx,sy)$ 移动到 $(tx,ty)$，每次移动可以任意向上下左右四个方向移动 $1$ 单位长度，求最少经过的直线数。

存在重叠的直线，这些直线需要重复计算。
## 大致思路
我们发现，无论起点和终点的横纵坐标是什么，从起点到终点无论如何都必须经过 $\{x=k|\min(sx,tx)\le k \le\max(sx,tx) \}$ 与 $\{y=k|\min(sy,ty)\le k \le\max(sy,ty) \}$ 中的所有直线。显然，最优方案就是仅经过这些直线。

于是我们对输入的直线进行判断。如果它属于这两个集合，那么计数器增加一。最后输出计数器即可。
## 最终代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,sx,sy,tx,ty;
long long ans;
int k[100005],t[100005];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n;
    for(int i=1;i<=n;i++) cin>>t[i]>>k[i];
    cin>>sx>>sy>>tx>>ty;
    for(int i=1;i<=n;i++)
    {
        if(t[i]==1&&min(sx,tx)<=k[i]&&k[i]<=max(sx,tx)) ans++;
        else if(t[i]==2&&min(sy,ty)<=k[i]&&k[i]<=max(sy,ty)) ans++;
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：lg12321a (赞：3)

# [题目传送门](https://www.luogu.com.cn/problem/P13752)
## part 1 题意描述
我们首先输入的是直线位置,观察样例可以发现，我们输入的两个整数 $t$ 和 $k$ 中如果 $t=1$ 则直线平行于 $x$ 轴，否则直线平行于 $y$ 轴，而 $k$ 代表直线在 $x$ 轴或 $y$ 轴上的坐标。

当我们输入完起点与终点后，一副这样的图就出现了。（红色表示直线，圆圈是起点和终点）
![](https://cdn.luogu.com.cn/upload/image_hosting/khbkjkmk.png)
## part 2 思路
本蒟蒻没什么高明的解法，来一个萌新也能听懂的。

我们可以发现由于直线是无限长的，没法绕过去，所以不管你怎么走，在起点和终点之间的直线就必须经过，而起点坐标和终点坐标有三种情况。

1. 起点坐标在终点坐标上面。
2. 起点坐标在终点坐标下面。
3. 起点坐标和终点坐标在一条线上。

我们把三种情况都判断一下即可。
## part 3 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int mp[100005][2],n,sx,sy,tx,ty,ans;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>mp[i][0]>>mp[i][1];
	cin>>sx>>sy>>tx>>ty;
	for(int i=1;i<=n;i++){
		if(mp[i][0]==1){//如果对应的是x轴，则用sx,tx去比。 
			//这里分三种情况，起点x轴坐标在终点x轴坐标上面，下面，或在一条线上。 
			if(tx>sx&&mp[i][1]<tx&&mp[i][1]>sx)//直线在tx,sx中间。
				ans+=1;
			if(tx<sx&&mp[i][1]>tx&&mp[i][1]<sx)//同上。
				ans+=1;
			if(tx==sx&&mp[i][1]==tx)//直线正好穿过起点和终点。
				ans+=1;
		}
		if(mp[i][0]==2){//如果对应的是y轴，则用sy,ty去比。 
			//同理也有三种情况，这边不再复述。 
			if(ty>sy&&mp[i][1]<ty&&mp[i][1]>sy)
				ans+=1;
			if(ty<sy&&mp[i][1]>ty&&mp[i][1]<sy)
				ans+=1;
			if(ty==sy&&mp[i][1]==ty)
				ans+=1;
		}
	}
	cout<<ans;//完美结束 
	return 0;
}
```
不要抄题解，小心被棕哦。
## [AC记录](https://www.luogu.com.cn/record/list?pid=P13752&user=1217878&page=1)

---

## 作者：bayiran (赞：1)

由于直线长度无限长，所以不能通过绕的方式来减小经过直线的数量。直接判断以起点和终点连线为对角线的矩形的内部和边上有多少条线经过。

创建两个数组分别存储平行于 $x$ 轴和平行于 $y$ 轴的直线的纵坐标和横坐标，排序后判断有多少条直线在区间内部。

需要注意起点的坐标不一定比终点的坐标小，所以需要提前判断。

代码如下。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
    int n;
    cin>>n;
    int x[200005];
    int y[200005];
    int cx = 0,cy = 0;
    while(n--){
        int t,k;
        cin>>t>>k;
        if(t==1){
            x[cx] = k;
            cx ++;
        }
        else{
            y[cy] = k;
            cy ++;
        }
    }
    int sx,sy,tx,ty;
    cin>>sx>>sy>>tx>>ty;
    if(sx>tx)swap(sx,tx);//判断大小并交换
    if(sy>ty)swap(sy,ty);
    sort(x,x+cx);//排序
    sort(y,y+cy);
    int ans = 0;
    for(int i=0;i<cx;i++){
        if(x[i]<sx)continue;
        if(x[i]>tx)break;//提前结束
        ans++;
    }
    for(int i=0;i<cy;i++){
        if(y[i]<sy)continue;
        if(y[i]>ty)break;
        ans++;
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：xxxel (赞：1)

这里我们设 $tx > sx$，$ty > sy$（注意存在 $tx < sx$ 和 $ty < sy$ 的情况）。 
-   若一条形如 $x = k$ 的直线中的 $k$ 满足 $k \in \lbrack {sx,tx} \rbrack$，则这条直线一定被经过。
-   若一条形如 $y = k$ 的直线中的 $k$ 满足 $k \in \lbrack {sy,ty} \rbrack$，则这条直线一定被经过。
-   否则，这条直线不被经过。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int n;
    cin>>n;
    int a[n+1][3];
    for(int i=1;i<=n;i++)cin>>a[i][1]>>a[i][2];
    int sx,sy,tx,ty,ans=0;
    cin>>sx>>sy>>tx>>ty;
    for(int i=1;i<=n;i++){
        if((a[i][1]==1&&a[i][2]>=sx&&a[i][2]<=tx)||(a[i][1]==2&&a[i][2]<=sy&&a[i][2]>=ty)||(a[i][1]==1&&a[i][2]<=sx&&a[i][2]>=tx)||(a[i][1]==2&&a[i][2]>=sy&&a[i][2]<=ty))ans++;
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：XingYueLi (赞：1)

## 思路

将直线分为两类存储，分别是 $x=k$ 的直线和 $y=k$ 的直线。

对两类直线分别排序，便于后续统计。

- 对于 $x=k$ 的直线，统计所有 $k$ 在 $[\min(sx,tx), \max(sx,tx)]$ 区间内的直线，因为从 $sx$ 到 $tx$ 的过程中，必定要经过这些直线。
- 对于 $y=k$ 的直线，统计所有 $k$ 在 $[\min(sy,ty), \max(sy,ty)]$ 区间内的直线，因为从 $sx$ 到 $tx$ 的过程中，必定要经过这些直线。

注意：包括直线恰好经过起点或终点的情况。

## Code

```c++
#include<iostream>
#include<algorithm>
using namespace std;

long long n, sx, sy, tx, ty;
long long xline[100005], yline[100005];
int xls = 0, yls = 0;
int cnt = 0;

int main() {
    cin >> n;
    for(int i = 1; i <= n; i++) {
        int t;
        long long k;
        cin >> t >> k;
        if(t == 1) {
            xls++;
            xline[xls] = k;
        } else {
            yls++;
            yline[yls] = k;
        }
    }
    
    // 排序x方向和y方向的直线
    sort(xline + 1, xline + xls + 1);
    sort(yline + 1, yline + yls + 1);
    
    cin >> sx >> sy >> tx >> ty;
    
    // 统计x方向的直线
    long long x_lower = min(sx, tx);
    long long x_upper = max(sx, tx);
    for(int i = 1; i <= xls; i++) {
        if(xline[i] > x_upper) break;
        if(xline[i] >= x_lower) cnt++;
    }
    
    // 统计y方向的直线
    long long y_lower = min(sy, ty);
    long long y_upper = max(sy, ty);
    for(int i = 1; i <= yls; i++) {
        if(yline[i] > y_upper) break;
        if(yline[i] >= y_lower) cnt++;
    }
    
    cout << cnt;
    return 0;
}
```

---

## 作者：Aellen998 (赞：0)

# 模拟
题意：给出两点起始坐标 $(sx,sy)$ 与 $(tx,ty)$。
给出 $n$ 条水平或竖直直线信息 $t$，$k$ 表示直线竖直或水平情况。求由点 $(sx,sy)$ 至点  $(tx,ty)$ 至少经过直线数。
### 思路
由数据范围 $n \le 1 \times 10^5$，$-10^9sx,sy,tx,ty \le10^9$ 可知需开二维数组 $num$ 记录信息 $t$，$k$，同时需处理终点在起点左侧情况情况。虽然本题不会卡时间超时，但建议使用较快读入读写方式，如快读或关闭输入输出同步流，养成好习惯。

由样例可画出下图：
![](https://cdn.luogu.com.cn/upload/image_hosting/xf6sri4x.png)
对于每条直线 $i$ 若为以下情况：

-  当 $t_i = 1$ ，且 $sx \le k_i \le tx$ 或 $tx \le k_i \le sx$ 时。
-  当 $t_i = 2$ ，且 $sy \le k_i \le ty$ 或 $ty  \le k_i \le sy$ 时。

则必须经过直线 $i$。

命名一变量 $ans$ 用于记录答案，跑一遍循环和判断累加 $ans$，由于本题不是多测，故不用清空 $ans$。

时间复杂度 $O(n)$ 稳过。
### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,sx,sy,tx,ty,ans;
int num[100005][2];//num[i][0]存储t，num[i][1]存储k
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);//加速cin，cout（c党狂喜）
	cin >> n;
	for(int i = 1;i <= n;i ++){
		cin >> num[i][0]>>num[i][1];
	}
	cin >> sx >> sy >> tx >> ty;
	for(int i = 1;i <= n;i ++){
		if(num[i][0] == 1){
			if((num[i][1] >= sx && num[i][1] <= tx) || (num[i][1] <= sx && num[i][1] >= tx)){
				ans ++;
			}
		}else if((num[i][1] >= sy && num[i][1] <= ty) || (num[i][1] <= sy&&num[i][1] >= ty)){
			ans ++;
		}
	}
	cout << ans;
	return 0;
}
```

---

## 作者：shx2011 (赞：0)

[题目链接](https://www.luogu.com.cn/problem/P13752)
## 题目大意
给出 $n$ 条与 $x$ 轴或 $y$ 轴平行的直线，并给定 $2$ 个点的坐标，要求从起点到终点的路径中最少要经过多少条直线。

## 分析
可以发现，无需考虑最优性问题，因为**在路径当中的直线无论如何也无法避免**，因此只需考虑起点到终点的连线与多少条直线有交点即可。

在具体实现中，只需判断该直线的 $k$ 的值是否在 $x$ 坐标或 $y$ 坐标的范围内即可。

::::info[tips]
由于直线平行与坐标轴，只要判断是否在坐标范围内而无需实际求交点。
::::

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int cntx,cnty;
int ans;
int linex[100005],liney[100005];//与x,y轴平行的直线 
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		int t,k;
		cin>>t>>k;
		if(t==1){
			liney[++cnty]=k;//与y轴平行 
		}else{
			linex[++cntx]=k;//与x轴平行 
		}
	}
	
	
	int sx,sy,tx,ty;
	cin>>sx>>sy>>tx>>ty;
	//分别计算有多少横线与竖线 
    if(ty<sy) swap(sy,ty);
    if(tx<sx) swap(sx,tx);
  //注意交换坐标大小
	for(int i=1;i<=cntx;i++){
		if(linex[i]>=sy && linex[i]<=ty) ans++;
	}
	
	for(int i=1;i<=cnty;i++){
		if(liney[i]>=sx && liney[i]<=tx) ans++;
	}
	
	cout<<ans;
	return 0;
}

```

[AC记录](https://www.luogu.com.cn/record/231550947)

---

## 作者：sunyizhe (赞：0)

这题其实是个简单的结论题。通过画图容易发现，无论怎么走，因为直线都是平行于坐标轴的，且 $x$ 坐标一定有从 $\min(sx,tx)$ 增大到 $\max(sx,tx)$ 的过程，$y$ 坐标一定有从 $\min(sy,ty)$ 增大到 $\max(sy,ty)$ 的过程，所以直线 $x \in [\min(sx,tx),\max(sx,tx)]$ 和 $y \in [\min(sy,ty), \max(sy,ty)]$ 是必定会被经过的。（这里数学符号的使用不是很准确，请见谅）

::::info[对于上面这句话更详细的解释]{open}
虽然中途可以往反方向走，但是如果想要到点 $(tx, ty)$，那么就必须再走回来，所以 $x,y$ 一定有从 $(sx, sy)$ 向着 $(tx,ty)$ 变化的趋势。而且中途有可能会经过不必要的直线。

举个例子：假设 $(sx, sy) = (1,1),(tx,ty) = (3,3)$，有直线 $x=2,x=0$。画图发现，你因为要从 $x = 1$ 到 $x = 3$，必定要跨过 $x = 2$，因为这里 $x$ 是连续变化的。然后如果 $x$ 向着负方向变化，则还有可能碰到 $x = 0$，这是不必要的。否则和 $x$ 向着正方向变化没有区别。
::::

所以我们对于两种直线分别记录下来，将每条直线枚举一遍，看是否在上述的直线范围内。统计答案即可。

::::info[代码]
```cpp
// 这里省略了快读模板
using namespace std;
const int N = 1e5 + 10;

int n, x[N], y[N], totx, toty;
int sx, sy, tx, ty;

int main() {
    read(n);
    for (int i = 1; i <= n; i++) {
        int op, k;
        read(op, k);
        if (op == 1) x[++totx] = k;
        else y[++toty] = k;
    }

    read(sx, sy, tx, ty);

    int ans = 0;
    for (int i = 1; i <= totx; i++) {
        if (x[i] >= min(sx, tx) && x[i] <= max(sx, tx)) ans++;
    }
    for (int i = 1; i <= toty; i++) {
        if (y[i] >= min(sy, ty) && y[i] <= max(sy, ty)) ans++;
    }

    write(ans);
    return 0;
}
```
::::

---

## 作者：jimmy9_666 (赞：0)

首先我们看横这走的方向，无论你怎么走，都一定会经过所有满足 $t = 1 \land sx \le k \le tx$ 的直线。

然后竖直方向也是同理，会经过所有满足 $t = 2 \land sy \le k \le ty$。

接下来就是代码实现了，但是要注意， $sx$ 有可能小于 $fx$，$sy$ 也有可能小于 $fy$，这时候就需要将两数交换。

:::info[代码]

```cpp line-numbers
#include <algorithm>
#include <iostream>
#include <cstdio>
#define LL long long
//#define int long long

using namespace std;

int read() {
	int k = 0, kk = 1;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-')
			kk = -1;
		c = getchar();
	}
	while ('0' <= c && c <= '9') {
		k = k * 10 + c - '0';
		c = getchar();
	}
	return k * kk;
}

void write(int x) {
	if (x < 0)
		putchar('-'), x = -x;
	if (x > 9)
		write(x / 10);
	putchar(x % 10 + '0');
}

const int N = 1e5 + 10;

int n;
int a[N][3];
int sx, sy, tx, ty;
int ans = 0;

signed main() {
	n = read();
	for (int i = 1; i <= n; i ++ )
		a[i][1] = read(), a[i][2] = read();
	sx = read(), sy = read(), tx = read(), ty = read();
	if (sx > tx)
		swap(sx, tx);
	if (sy > ty)
		swap(sy, ty);
	for (int i = 1; i <= n; i ++ ) {
		if (a[i][1] == 1)
			ans += (sx <= a[i][2] && a[i][2] <= tx);
		else
			ans += (sy <= a[i][2] && a[i][2] <= ty);
	}
	write(ans);
	return 0;
}
```
:::

然后你就会发现这题做完了。

---

