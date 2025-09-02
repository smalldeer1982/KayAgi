# [ABC258F] Main Street

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc258/tasks/abc258_f

xy 平面上にある AtCoder 王国の道路は、全ての整数 $ n $ に対する直線 $ x=n $ および直線 $ y=n $ からなります。 そのうち、全ての整数 $ n $ に対する直線 $ x=Bn $ および直線 $ y=Bn $ は大通りです。

高橋君は $ (x,y) $ にいるときに、$ (x,y-1),(x,y+1),(x+1,y),(x-1,y) $ のいずれかに移動することができます。 また、$ 1 $ 回の移動につき、大通りに沿って移動する場合は $ 1 $ 秒、それ以外の場合は $ K $ 秒かかります。

$ (S_x,S_y) $ にいる高橋君が $ (G_x,G_y) $ に移動するのに最短で何秒かかるかを求めてください。

この問題は $ T $ ケース与えられます。

## 说明/提示

### 制約

- $ 1\ \le\ T\ \le\ 2\ \times\ 10^5 $
- $ 1\ \le\ B,K\ \le\ 10^9 $
- $ 0\ \le\ S_x,S_y,G_x,G_y\ \le\ 10^9 $
- 入力はすべて整数。

### Sample Explanation 1

$ 1 $ 個目のテストケースについて、$ (2,2) $ から $ (2,3) $ に $ 4 $ 秒かけて移動し、$ (2,3) $ から $ (4,3) $ に $ 2 $ 秒かけて移動し、$ (4,3) $ から $ (4,4) $ に $ 4 $ 秒かけて移動することで $ 10 $ 秒で $ (2,2) $ から $ (4,4) $ に移動することができます。$ 10 $ 秒より早く移動することはできないため、解は $ 10 $ です。 $ 2 $ 個目のテストケースについて、初めから $ (G_x,G_y) $ にいるため解は $ 0 $ です。

## 样例 #1

### 输入

```
4
3 4 2 2 4 4
5 6 2 3 2 3
1 1000000000 0 0 1000000000 1000000000
1000000000 1000000000 500000000 500000000 1000000000 1000000000```

### 输出

```
10
0
2000000000
500000000500000000```

## 样例 #2

### 输入

```
10
928184439 674654465 203937094 186855052 851783856 805293696
55480262 448852233 823161539 786348805 550018803 322680316
891870741 235679524 32164572 497841190 620600021 96487871
321502816 428964257 499656016 521484999 717623189 824784374
144040837 680268887 76238777 371138006 350230937 78690135
768922620 799628518 403830696 60449731 218880692 88319939
482031503 121412614 472330444 284479575 949635609 427232765
389524418 132987043 656496997 678732442 23028233 488463974
857778764 629964237 714551548 739330018 579247790 874251485
461612428 535402609 555160129 833592114 44418273 287363785```

### 输出

```
177606591118701316
6205925075792263
30320747646118343
84136273267803188
83764071874751489
118960470930399064
2929499649126153
16403238161749820
84995699148879437
71771264361119335```

# 题解

## 作者：Rannio (赞：5)

### 题意：

你要在平面直角坐标系中行走，每一步可以上下左右四个方向任意移动 $1$，耗时 $k$ 秒。特别地，存在若干条快速通道，若该步起点和终点均满足 $x \equiv 0 \pmod{B}$ 或 $y \equiv 0 \pmod{B}$，则认为该步是在快速通道上进行，仅需耗时 $1$ 秒。询问从 $(S_x, S_y)$ 到 $(G_x, G_y)$ 最少需要多少秒。存在多组数据。

### 思路：

看这个题第一眼没什么思路，先尝试画个图。

![](https://cdn.luogu.com.cn/upload/image_hosting/2xpd5p3x.png)

不难发现可以分类讨论。  
首先有两种基本情况：
- 走通道
- 不走通道

对于走通道这种情况，我们可以分别枚举起点和终点向上、下、左、右的哪一个方向走到达快速通道的距离最短，然后将过起点或终点作垂直于距离最短的快速通道的垂线段的垂足的平面距离与两条垂线段的长度乘以 $k$ 的值相加，即可得到走通道的最短时间。再将这个时间与不走通道的最短时间取个最小值即可。

对于不走通道这种情况，我们可以直接计算，注意特判一下起点和终点都在同一行或同一列的快速通道上的情况即可。

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T,b,k,sx,sy,gx,gy;
int dis(int x_1,int y_1,int x_2,int y_2){
    if(x_1%b==0&&x_2%b==0&&y_1/b==y_2/b) return min(abs(x_1-x_2)+min(y_1%b+y_2%b,b*2-y_1%b-y_2%b),abs(y_1-y_2)+abs(x_1-x_2)*k);
    swap(x_1,y_1),swap(x_2,y_2);
    if(x_1%b==0&&x_2%b==0&&y_1/b==y_2/b) return min(abs(x_1-x_2)+min(y_1%b+y_2%b,b*2-y_1%b-y_2%b),abs(y_1-y_2)+abs(x_1-x_2)*k);
    return abs(x_1-x_2)+abs(y_1-y_2);
}
signed main(){
    scanf("%lld",&T);
    while(T--){
        scanf("%lld%lld%lld%lld%lld%lld",&b,&k,&sx,&sy,&gx,&gy);
        if(sx==gx&&sy==gy) printf("0\n");
        else{
            int res=dis(sx,sy,gx,gy)*k;
            int sup=(sy/b+1)*b,sdo=sy/b*b;
            int sri=(sx/b+1)*b,sle=sx/b*b;
            int gup=(gy/b+1)*b,gdo=gy/b*b;
            int gri=(gx/b+1)*b,gle=gx/b*b;
            res=min(res,dis(sx,sup,gx,gup)+(sup-sy)*k+(gup-gy)*k);//起点向上终点向上
            res=min(res,dis(sx,sup,gx,gdo)+(sup-sy)*k+(gy-gdo)*k);//起点向上终点向下
            res=min(res,dis(sx,sup,gle,gy)+(sup-sy)*k+(gx-gle)*k);//起点向上终点向左
            res=min(res,dis(sx,sup,gri,gy)+(sup-sy)*k+(gri-gx)*k);//起点向上终点向右
            res=min(res,dis(sx,sdo,gx,gup)+(sy-sdo)*k+(gup-gy)*k);//起点向下终点向上
            res=min(res,dis(sx,sdo,gx,gdo)+(sy-sdo)*k+(gy-gdo)*k);//起点向下终点向下
            res=min(res,dis(sx,sdo,gle,gy)+(sy-sdo)*k+(gx-gle)*k);//起点向下终点向左
            res=min(res,dis(sx,sdo,gri,gy)+(sy-sdo)*k+(gri-gx)*k);//起点向下终点向右
            res=min(res,dis(sle,sy,gx,gup)+(sx-sle)*k+(gup-gy)*k);//起点向左终点向上
            res=min(res,dis(sle,sy,gx,gdo)+(sx-sle)*k+(gy-gdo)*k);//起点向左终点向下
            res=min(res,dis(sle,sy,gle,gy)+(sx-sle)*k+(gx-gle)*k);//起点向左终点向左
            res=min(res,dis(sle,sy,gri,gy)+(sx-sle)*k+(gri-gx)*k);//起点向左终点向右
            res=min(res,dis(sri,sy,gx,gup)+(sri-sx)*k+(gup-gy)*k);//起点向右终点向上
            res=min(res,dis(sri,sy,gx,gdo)+(sri-sx)*k+(gy-gdo)*k);//起点向右终点向下
            res=min(res,dis(sri,sy,gle,gy)+(sri-sx)*k+(gx-gle)*k);//起点向右终点向左
            res=min(res,dis(sri,sy,gri,gy)+(sri-sx)*k+(gri-gx)*k);//起点向右终点向右
            printf("%lld\n",res);
        }
    }
    return 0;
}
```

---

## 作者：jokersen (赞：3)

我们将整张地图看成被主干道分成一个个正方形区域。

其实可以发现，这题其实就只有 $17$ 种情况。

第一种就是直接走过去。

其它就是走到出发点所在区域的上下左右边界，再走到终点所在区域的上下左右边界的一个匹配，共 $4\times 4=16$ 种情况。

但手动枚举每种情况代码长且容易出错，所以我们可以用双层循环枚举，就不需要一一写出每种情况了。

计算距离：
```cpp
lli dis(lli x_1,lli y_1,lli x_2,lli y_2){
    if(x_1%n==0&&x_2%n==0&&y_1/n==y_2/n) return min(abs(x_1-x_2)+min(y_1%n+y_2%n,n*2-y_1%n-y_2%n),abs(y_1-y_2)+abs(x_1-x_2)*k);
    swap(x_1,y_1),swap(x_2,y_2);
    if(x_1%n==0&&x_2%n==0&&y_1/n==y_2/n) return min(abs(x_1-x_2)+min(y_1%n+y_2%n,n*2-y_1%n-y_2%n),abs(y_1-y_2)+abs(x_1-x_2)*k);
    return abs(x_1-x_2)+abs(y_1-y_2);
}
```
求出出发点所在区域的上下左右边界和终点所在区域的上下左右边界：
```cpp
a[1]=sx%n,a[2]=n-a[1],a[3]=sy%n,a[4]=n-a[3];
b[1]=gx%n,b[2]=n-b[1],b[3]=gy%n,b[4]=n-b[3];
c[1][0]=sx-a[1],c[2][0]=sx+a[2],c[3][1]=sy-a[3],c[4][1]=sy+a[4];
d[1][0]=gx-b[1],d[2][0]=gx+b[2],d[3][1]=gy-b[3],d[4][1]=gy+b[4];
c[1][1]=sy,c[2][1]=sy,c[3][0]=sx,c[4][0]=sx;
d[1][1]=gy,d[2][1]=gy,d[3][0]=gx,d[4][0]=gx;
```
循环枚举：
```cpp
for(int i=1;i<=4;i++) for(int j=1;j<=4;j++)
ans=min(ans,dis(c[i][0],c[i][1],d[j][0],d[j][1])+(a[i]+b[j])*k);
```
**完整 Code**：
```cpp
#include<bits/stdc++.h> 
using namespace std;
using lli=long long int;
int t;
lli ans,n,k,sx,sy,gx,gy,a[5],b[5],c[5][2],d[5][2];
lli dis(lli x_1,lli y_1,lli x_2,lli y_2){
    if(x_1%n==0&&x_2%n==0&&y_1/n==y_2/n) return min(abs(x_1-x_2)+min(y_1%n+y_2%n,n*2-y_1%n-y_2%n),abs(y_1-y_2)+abs(x_1-x_2)*k);
    swap(x_1,y_1),swap(x_2,y_2);
    if(x_1%n==0&&x_2%n==0&&y_1/n==y_2/n) return min(abs(x_1-x_2)+min(y_1%n+y_2%n,n*2-y_1%n-y_2%n),abs(y_1-y_2)+abs(x_1-x_2)*k);
    return abs(x_1-x_2)+abs(y_1-y_2);
}
int main(){
    scanf("%d",&t);
    while(t--){
        scanf("%lld%lld%lld%lld%lld%lld",&n,&k,&sx,&sy,&gx,&gy);
        ans=(abs(sx-gx)+abs(sy-gy))*k;
        a[1]=sx%n,a[2]=n-a[1],a[3]=sy%n,a[4]=n-a[3];
        b[1]=gx%n,b[2]=n-b[1],b[3]=gy%n,b[4]=n-b[3];
        c[1][0]=sx-a[1],c[2][0]=sx+a[2],c[3][1]=sy-a[3],c[4][1]=sy+a[4];
        d[1][0]=gx-b[1],d[2][0]=gx+b[2],d[3][1]=gy-b[3],d[4][1]=gy+b[4];
        c[1][1]=sy,c[2][1]=sy,c[3][0]=sx,c[4][0]=sx;
        d[1][1]=gy,d[2][1]=gy,d[3][0]=gx,d[4][0]=gx;
        for(int i=1;i<=4;i++) for(int j=1;j<=4;j++)
        ans=min(ans,dis(c[i][0],c[i][1],d[j][0],d[j][1])+(a[i]+b[j])*k);
        printf("%lld\n",ans);
    }
    return 0;
}
```

---

## 作者：Gaode_Sean (赞：3)

![](https://cdn.luogu.com.cn/upload/image_hosting/26eybllp.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

这题有两种最基本的情况：走通道和不走通道。

对于走通道，从出发点到通道的的走法只有上图所示的 $4$ 种，证明平凡。那么我们枚举出发点和结束点分别是走上、下、左、右中的哪个方向，一共有 $4 \times 4=16$ 种走法。最后将答案取最小值。

对于不走通道，直接计算步数即可。

## AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int T;
ll v,k,sx,sy,gx,gy,a[4],b[4],c[4],d[4],ans;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%lld%lld%lld%lld%lld%lld",&v,&k,&sx,&sy,&gx,&gy);
		if(sx>gx) swap(sx,gx),swap(sy,gy);
		ans=((ll)(abs(sx-gx))+(ll)(abs(sy-gy)))*k;
	    a[0]=a[1]=sx,a[2]=sx/v*v,a[3]=a[2]+v;
	    b[0]=sy/v*v,b[1]=b[0]+v,b[2]=b[3]=sy;
	    c[0]=c[1]=gx,c[2]=gx/v*v,c[3]=c[2]+v;
	    d[0]=gy/v*v,d[1]=d[0]+v,d[2]=d[3]=gy;
	    for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
			{
				ll cnt=(abs(sx-a[i])+abs(sy-b[i])+abs(gx-c[j])+abs(gy-d[j]))*k;
		        if(a[i]%v==0&&c[j]%v==0&&b[i]/v==d[j]/v)
		        {
		        	if(a[i]==c[j]) cnt+=abs(b[i]-d[j]);
		        	else cnt+=abs(a[i]-c[j])+min(b[i]%v+d[j]%v,2*v-b[i]%v-d[j]%v);
				}
				else if(b[i]%v==0&&d[j]%v==0&&a[i]/v==c[j]/v)
				{
					if(b[i]==d[j]) cnt+=abs(a[i]-c[j]);
					else cnt+=abs(b[i]-d[j])+min(a[i]%v+c[j]%v,2*v-a[i]%v-c[j]%v);
				} 
				else cnt+=abs(a[i]-c[j])+abs(b[i]-d[j]);
		        ans=min(ans,cnt);
		    }
		}
		printf("%lld\n",ans);
	}
    return 0;	
}
```

---

## 作者：ttq012 (赞：1)

看之前：这不是一个下位黄吗？写完之后：这题评紫都不过分了……后来：算了还是评蓝合适。

首先考虑计算答案。容易发现，若不选择经过快速通道，则答案的贡献为 $k$ 乘以两点之间的曼哈顿距离。若选择经过快速通道，则起点和终点都分别有 $4$ 种不同的方向（上、下、左、右）用最快的速度来到快速通道。所以分 $17$ 种情况就做完了这个题目，这就是 $2300+$ 吗？

这样配得起这个题的 $2300+$ 吗？

事实上这个题目还有一个非常恶心的细节需要考虑。

[![pkAXNFI.png](https://s21.ax1x.com/2024/05/05/pkAXNFI.png)](https://imgse.com/i/pkAXNFI)

注：链接无误。在机房都可以看。

此时 $k=3$。若想要从 A 点经过快速通道到达 B 点，并不能直接通过直线 $y=2$ 到达（不是快速通道）。此时有两种不同的情况：

1. 走上面 $y=3$ 的绿色横线。
2. 走下面 $y=0$ 的紫色横线。

需要分类讨论求 $\min$。列的情况同理。

问题是如何判定这样的情况。因为行和列同理，所以只考虑同一行的情况即可。

容易发现，通过这些横线可以将平面分成若干多块。容易发现，若两个点不在同一列，且都在这些直线分成的同一个块（横线上的点不算）内，则就必须绕行。否则就必须不绕行。

这个地方如何实现？

考虑将每两个横线之间的所有点和每一条横线上的点分别看做一个块。为了方便实现，设三条相邻的横线 $p_1,p_2,p_3$ 之间，$p_1\sim p_2$ 的块的编号为 $x$，$p_2\sim p_3$ 的块的编号为 $x+1$。则令 $p_2$ 的编号为 $x+0.5$，$p_1$ 的编号为 $x-0.5$，$p_3$ 的编号为 $x+1.5$，以此类推。

这一类情况可以通过一个函数来实现。具体的代码实现：

```cpp
double id(int x, int b) {
    if (x % b == 0) return x / b - 0.5;
    else return x / b;
}
int del(int x, int y, int xx, int yy) { // 求两个坐标点通过快速通道最少要走多远
    if (id(x, b) != id(xx, b) && id(y, b) != id(yy, b) || x == xx && x % b == 0 || y == yy && y % b == 0)
        return abs(x - xx) + abs(y - yy);
    else {
        if (abs(x - xx) < b) {
            int shang = abs(y - yy) + abs(x - pre(x)) + abs(xx - pre(xx));
            int xia = abs(y - yy) + abs(nxt(x) - x) + abs(nxt(xx) - xx);
            return min(shang, xia);
        } else {
            int shang = abs(x - xx) + abs(y - pre(y)) + abs(yy - pre(yy));
            int xia = abs(x - xx) + abs(nxt(y) - y) + abs(nxt(yy) - yy);
            return min(shang, xia);
        }
    }
}
```

其实还有一个问题，就是如何计算一个点上方 / 下方最近的横线。这个可以用一个二分来实现。特殊的，除法是向 $0$ 取整，所以为了防止二分的时候出现负数，应当对当前的值加上一个 $b$ 特别大的倍数以让所有的值均为正数。

因为 $17$ 种分讨会大量且重复的求距离一个点上方 / 下方最近的横线，所以应当提前预处理出这些横线的值，否则会 `TLE`。

最后一点。一定记着开 `long long`。

从下午四点开题到晚上七点过题，去掉中间去吃饭的半个小时共计用 $150$ 分钟，最终通过了这个题目。还是太逊了。

```cpp
#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define dbg cerr << "Debug: "
#define int long long
using namespace std;
int b, k, sx, sy, tx, ty;
int pre(int x) {
    int l = x - 2 * b, r = x, best = -1;
    while (l <= r) {
        int mid = l + r >> 1;
        if ((mid + b * 233) / b != (x + b * 233) / b) best = mid, l = mid + 1;
        else r = mid - 1;
    }
    return best + 1;
}
int nxt(int x) {
	int l = x, r = x + 2 * b, best = -1;
    if (x % b == 0) return x;
	while (l <= r) {
		int mid = l + r >> 1;
		if ((mid + b * 233) / b != (x + b * 233) / b) best = mid, r = mid - 1;
		else l = mid + 1;
	}
	return best;
}
double id(int x, int b) {
    if (x % b == 0) return x / b - 0.5;
    else return x / b;
}
int del(int x, int y, int xx, int yy) {
    if (id(x, b) != id(xx, b) && id(y, b) != id(yy, b) || x == xx && x % b == 0 || y == yy && y % b == 0)
        return abs(x - xx) + abs(y - yy);
    else {
        if (abs(x - xx) < b) {
            int shang = abs(y - yy) + abs(x - pre(x)) + abs(xx - pre(xx));
            int xia = abs(y - yy) + abs(nxt(x) - x) + abs(nxt(xx) - xx);
            return min(shang, xia);
        } else {
            int shang = abs(x - xx) + abs(y - pre(y)) + abs(yy - pre(yy));
            int xia = abs(x - xx) + abs(nxt(y) - y) + abs(nxt(yy) - yy);
            return min(shang, xia);
        }
    }
}
signed main() {
//    freopen("test_20.in", "r", stdin);
//    freopen("test_20.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> b >> k >> sx >> sy >> tx >> ty;
        int d[17];
        d[0] = k * (abs(sx - tx) + abs(sy - ty));
        int PRESX = pre(sx), PRETX = pre(tx), PRESY = pre(sy), PRETY = pre(ty);
        int NXTSX = nxt(sx), NXTTX = nxt(tx), NXTSY = nxt(sy), NXTTY = nxt(ty);
        d[1] = k * abs(sx - PRESX) + k * abs(tx - PRETX) + del(PRESX, sy, PRETX, ty);
        d[2] = k * abs(sy - PRESY) + k * abs(tx - PRETX) + del(sx, PRESY, PRETX, ty);
        d[3] = k * abs(NXTSX - sx) + k * abs(tx - PRETX) + del(NXTSX, sy, PRETX, ty);
        d[4] = k * abs(NXTSY - sy) + k * abs(tx - PRETX) + del(sx, NXTSY, PRETX, ty);
        d[5] = k * abs(sx - PRESX) + k * abs(ty - PRETY) + del(PRESX, sy, tx, PRETY);
        d[6] = k * abs(sy - PRESY) + k * abs(ty - PRETY) + del(sx, PRESY, tx, PRETY);
        d[7] = k * abs(NXTSX - sx) + k * abs(ty - PRETY) + del(NXTSX, sy, tx, PRETY);
        d[8] = k * abs(NXTSY - sy) + k * abs(ty - PRETY) + del(sx, NXTSY, tx, PRETY);
        d[9] = k * abs(sx - PRESX) + k * abs(NXTTX - tx) + del(PRESX, sy, NXTTX, ty);
        d[10] = k * abs(sy - PRESY) + k * abs(NXTTX - tx) + del(sx, PRESY, NXTTX, ty);
        d[11] = k * abs(NXTSX - sx) + k * abs(NXTTX - tx) + del(NXTSX, sy, NXTTX, ty);
        d[12] = k * abs(NXTSY - sy) + k * abs(NXTTX - tx) + del(sx, NXTSY, NXTTX, ty);
        d[13] = k * abs(sx - PRESX) + k * abs(NXTTY - ty) + del(PRESX, sy, tx, NXTTY);
        d[14] = k * abs(sy - PRESY) + k * abs(NXTTY - ty) + del(sx, PRESY, tx, NXTTY);
        d[15] = k * abs(NXTSX - sx) + k * abs(NXTTY - ty) + del(NXTSX, sy, tx, NXTTY);
        d[16] = k * abs(NXTSY - sy) + k * abs(NXTTY - ty) + del(sx, NXTSY, tx, NXTTY);
        cout << *min_element(d, d + 17) << '\n';
    }
    return 0;
}
```

最后：因为样例 $2$ 的数据太大不好调，附赠 ATcoder 的 Test20 供调试。数据见[题目附件](https://www.luogu.com.cn/problem/U429136)。

---

## 作者：EuphoricStar (赞：0)

发现这题有个远古的 WA 就来改了（

发现走法很多种，不想分类讨论，考虑最短路。

设起点编号为 $1$，终点为 $11$。

$x = Bn$ 和 $y = Bn$ 把坐标系分成了若干块。考虑过起点作一条平行于 $Ox$ 的直线，与左右两条 $x = Bn$ 的线有两个交点，给它们编号 $3, 5$，同样地作一条平行于 $Oy$ 的直线，与上下两条 $y = Bn$ 的线有两个交点，给它们编号 $4, 2$。然后把起点所在块的四个角分别编号 $6, 7, 8, 9$，然后连 $1 \to 2, 3, 4, 5$，$2, 3, 4, 5$ 再连到 $6, 7, 8, 9$，像这样：

![](https://s1.ax1x.com/2023/06/11/pCZCs4P.png)

对于终点也是类似地建图，编号相对于起点 $+ 10$。

那对于起点和终点不在一个块的情况，先走到起点所在块的四个角的一个再走到终点所在块四个角的一个是一种备选方案。因此连边 $x \to y + 10, x, y \in \{6, 7, 8, 9\}$，边权可以算出来。

在同一个块内，或者起点终点两个块相邻，可以不走到四个角，这个要特判，连相应的边。这里因为连边较复杂不展开，可以看代码。

然后跑一遍 $1$ 到 $11$ 的最短路就行。

[code](https://atcoder.jp/contests/abc258/submissions/42197793)

---

