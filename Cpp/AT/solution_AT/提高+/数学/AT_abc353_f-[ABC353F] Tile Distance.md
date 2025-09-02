# [ABC353F] Tile Distance

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc353/tasks/abc353_f

座標平面上にタイルが敷き詰められています。 $ 1\times1 $ の大きさの小タイルと $ K\times\ K $ の大きさの大タイルの $ 2 $ 種類があり、次の規則に従って敷き詰められています。

- 整数の組 $ (i,j) $ に対し、正方形 $ \lbrace(x,y)\mid\ i\leq\ x\leq\ i+1\wedge\ j\leq\ y\leq\ j+1\rbrace $ は $ 1 $ つの小タイルもしくは $ 1 $ つの大タイルに含まれる。
  - $ \left\lfloor\dfrac\ iK\right\rfloor+\left\lfloor\dfrac\ jK\right\rfloor $ が偶数のとき、小タイルに含まれる。
  - そうでないとき、大タイルに含まれる。
 
ただし、タイルは境界を含むものとし、共通部分が正の面積をもつような $ 2 $ つの異なるタイルは存在しないとします。

例えば、$ K=3 $ のとき、タイルは以下のようになります。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_abc353_f/4828cef3de44d96612c498eeceffc46bc8c608c7.png)

 高橋君は、はじめ座標平面上の点 $ (S\ _\ x+0.5,S\ _\ y+0.5) $ にいます。

高橋君は、次の移動を好きなだけ繰り返します。

- 上下左右の方向と正の整数 $ n $ を選ぶ。その方向に $ n $ だけ進む。
 
高橋君が異なるタイルを通るたび、高橋君は通行料を $ 1 $ だけ支払います。

高橋君が点 $ (T\ _\ x+0.5,T\ _\ y+0.5) $ にたどり着くために支払わなければならない通行料の最小値を求めてください。

## 说明/提示

### 制約

- $ 1\leq\ K\leq10\ ^\ {16} $
- $ 0\leq\ S\ _\ x\leq2\times10\ ^\ {16} $
- $ 0\leq\ S\ _\ y\leq2\times10\ ^\ {16} $
- $ 0\leq\ T\ _\ x\leq2\times10\ ^\ {16} $
- $ 0\leq\ T\ _\ y\leq2\times10\ ^\ {16} $
- 入力はすべて整数
 
### Sample Explanation 1

例えば、以下のように移動することで支払う通行料を $ 5 $ にすることができます。 !\[\](https://img.atcoder.jp/abc353/35d47ae5cfbcc870ac4d285a8e024278.png) - 上に $ 3 $ 進む。通行料を $ 1 $ 支払う。 - 左に $ 2 $ 進む。通行料を $ 1 $ 支払う。 - 上に $ 1 $ 進む。通行料を $ 1 $ 支払う。 - 左に $ 4 $ 進む。通行料を $ 2 $ 支払う。 支払う通行料を $ 4 $ 以下にすることはできないので、`5` を出力してください。

### Sample Explanation 2

!\[\](https://img.atcoder.jp/abc353/a454c75aab412b8ada226a5e7741e5e1.png) 高橋君が最短距離で移動するとき、どのように移動しても通行料を $ 42 $ だけ支払います。 支払う通行料を $ 41 $ 以下にすることはできないので、`42` を出力してください。

### Sample Explanation 3

通行料を支払わなくてよい場合もあります。

## 样例 #1

### 输入

```
3
7 2
1 6```

### 输出

```
5```

## 样例 #2

### 输入

```
1
41 42
13 56```

### 输出

```
42```

## 样例 #3

### 输入

```
100
100 99
199 1```

### 输出

```
0```

## 样例 #4

### 输入

```
96929423
5105216413055191 10822465733465225
1543712011036057 14412421458305526```

### 输出

```
79154049```

# 题解

## 作者：Register_int (赞：23)

好题，学到很多。

容易发现你真的去硬分讨绝对是写不完的，所以要记住两点：

- 将简单的情况进行归并。
- 用少量的枚举规避分讨。

将 $k=1$ 的情况特判掉，先来找找规律：

- 将大格子从 $(0,0)$ 开始编号，则 $(x,y)$ 对应的大格子为 $(x/k,y/k)$。
- 从小格子 $(x,y)$ 到上、下、左、右的距离分别为 $k-(y\bmod k)$，$(y\bmod k)+1$，$(x\bmod k)+1$，$k-(x\bmod k)$。

那么分讨起点与终点在不在大格子内：

- 都在大格子内。只看大格子，斜着走一格耗费 $2$ 步，直着走两格耗费 $4$ 步。特别的，若 $k=2$，则直着走仅耗费 $3$ 步。最短距离一定是先斜着走一段，再直着走一段。直接计算即可。

```cpp
inline 
ll calc(ll ax, ll ay, ll bx, ll by) {
	ll p = abs(ax - bx), q = abs(ay - by);
	if (p > q) swap(p, q);
	return p * 2 + (q - p) / 2 * min(k + 1, 4ll);
}
```

- 只有一个在大格子内。枚举在小格子的点要往哪个大格子走，再算两个大格子之间的距离。

```cpp
if (bx + by & 1) swap(ax, bx), swap(ay, by), swap(sx, tx), swap(sy, ty);
if (ax + ay & 1) {
	for (int i = 0; i < 4; i++) {
		ll cx = bx + px[i], cy = by + py[i];
		if (i == 0) res = k - tx % k;
		if (i == 1) res = k - ty % k;
		if (i == 2) res = tx % k + 1;
		if (i == 3) res = ty % k + 1;
		ans = min(ans, res + calc(ax, ay, cx, cy));
	}
	printf("%lld", ans);
}
```

- 两个都在小格子内。先判两个在不在同一个格子内，再分别枚举往哪个大格子走。

```cpp
ans = abs(sx - tx) + abs(sy - ty);
for (int i = 0; i < 4; i++) {
	ll cx = ax + px[i], cy = ay + py[i];
	for (int j = 0; j < 4; j++) {
		ll dx = bx + px[j], dy = by + py[j];
		if (i == 0) res = k - sx % k;
		if (i == 1) res = k - sy % k;
		if (i == 2) res = sx % k + 1;
		if (i == 3) res = sy % k + 1;
		if (j == 0) res += k - tx % k;
		if (j == 1) res += k - ty % k;
		if (j == 2) res += tx % k + 1;
		if (j == 3) res += ty % k + 1;
		ans = min(ans, res + calc(cx, cy, dx, dy));
	}
}
```

这样，你就能以约 1.6K 的码量，在 20min 内切掉这个看起来很恶心的题了。

---

## 作者：2022liaojianxiang (赞：5)

这种题一看就是大分讨题（可惜的是比赛是我没有打出来的就是这一题）。

不用想这种题硬着头皮分类讨论是会在巷子里走不出去的。那么我们找到一种对于普遍情况都可以归纳的方式来计算就可以简化问题。接下来就是只花了 $900$ bytes 的思路。

因为在大格子上多走肯定是更加优秀的（不然你在小格子上穿过太多次答案就不优了），所以我们可以枚举刚开始起点和终点靠近它的上下左右 $4$ 个最近的大格子，计算出达到这个大格子的花费，接着更加方便的去计算两个大格子之间花费的代价。这里起点和终点的 $4$ 种状态两两匹配有只 $16$ 种方案不怕超时。计算当前格子到最近的上下左右的大格子的代价很简单直接直线走过去计算穿过的小格子数量即可（本来在大格子里面就不需要计算了）。

接下来我们思考两个大格子之间的代价：我们发现走两个大格子之间的拐角（会穿过一个小格子再拐一个弯）从而走到相邻的左上，左下，右上，右下的大格子是最优的，每次消费 $2$。那么我们从一个大格子走到另一个大格子就会花费他们的高度差和宽度差的最大值在乘上 $2$ 的代价。

当然这要判断一种特殊的情况：$k \le 2$ 时，我们不用走拐角，我们直接直线走过去就可以了，不需要再多拐两个弯，所以要减掉这种多余的代价。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
long long n,sx,sy,tx,ty;
struct node{
	long long x,y,z;
};
long long aabs(long long x)
{
	if(x<0) return -x;
	return x;
}
long long js(node a,node b)
{
	long long dx=aabs(a.x-b.x),dy=aabs(a.y-b.y);
	return a.z+b.z+max(dx,dy)*2-(n<=2)*aabs(dx-dy)/2;
}
node da(long long x,long long y,long long pd)
{
	long long a=(x-1)/n,b=(y-1)/n;
	if((a+b)%2!=0) return {a,b,0};
	else if(pd==0) return {a+1,b,n*(a+1)-x+1};
	else if(pd==1) return {a-1,b,x-n*a};
	else if(pd==2) return {a,b+1,n*(b+1)-y+1};
	else if(pd==3) return {a,b-1,y-n*b}; 
}
int main()
{
	scanf("%lld%lld%lld%lld%lld",&n,&sx,&sy,&tx,&ty);
	sx++,sy++,tx++,ty++;
	long long ans=aabs(sx-tx)+aabs(sy-ty);
	for(long long i=0;i<4;i++)
		for(long long j=0;j<4;j++)
			ans=min(ans,js(da(sx,sy,i),da(tx,ty,j)));
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：g1ove (赞：2)

大分讨，由于没注意到细节挂大分。

下面称大小为 $n\times n$ 的为大格子，$1\times 1$ 的为小格子。把 $n\times n$ 个小格子组成的正方形称为一个部分。
## 分析
我们先来讨论一般情况。
### 思考一
对于 $n\ge3$ 的一般情况，如果要求任意两个**大格子**到对方的距离最小，怎么做？

![](https://cdn.luogu.com.cn/upload/image_hosting/uorh6bs5.png)

根据贪心，我们不难把行走拆为两个部分：
![](https://cdn.luogu.com.cn/upload/image_hosting/ngrz7tej.png)

+ 部分一
从左上角红色格子到绿色格子部分。

+ 部分二
从绿色格子到右下角红色格子部分。

我们发现，假设如果从任意一个点到另一个点，它的路径是这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/eg8z542y.png)

每一部分贪心的走。我们发现相邻两个大格子需要走两次，然后分析一下，不难得出距离公式：$D(sx,sy,tx,ty)=2\times \max(|sx-sy|,|tx-ty|)$。

### 思考二
如果起点、终点在小格子里怎么办？

没有关系。我们这些情况转化为大格子的情况。
![](https://cdn.luogu.com.cn/upload/image_hosting/c7pbxd5s.png)

然后计算权值时再加上蓝色线条部分的长度即可。

这里最多会计算 $4\times 4=16$ 次。

### 思考三
如果在起点，终点在同一部分里，怎么办？

对于在大格子，答案显然是 $0$。

对于小格子，似乎是两点之间的曼哈顿距离？不对！这就是笔者挂分的点！

它还可以绕出去……具体可以看图。
![](https://cdn.luogu.com.cn/upload/image_hosting/capl6guu.png)
所以要归并到上面的情况一起计算。

### 思考四
似乎做完了？不，还有特殊情况。
+ $n=1$

输出曼哈顿距离即可。

+ $n=2$

这个改变的地方在这里：
![](https://cdn.luogu.com.cn/upload/image_hosting/eg8z542y.png)
从绿色格子到终点的部分，我们选择直接穿过所有格子。

因为绕两次需要穿过四次格子，直接穿过却只需要三次。
特判一下即可。

至此，这道题就完工了。

Code
```cpp
#include<bits/stdc++.h>
#define N 600005
#define ll long long
using namespace std;
struct node{
	ll x,y;
};
ll n;
ll sx,sy,tx,ty;
ll d(ll sx,ll sy,ll tx,ll ty)
{
	ll P=max(abs(sx-tx),abs(sy-ty));
	if(n^2) return P*2;
	else return min(abs(sx-tx),abs(sy-ty))*2+(abs(abs(sx-tx)-abs(sy-ty)))/2*3;
}
node B(ll x,ll y)
{
	node tmp;
	tmp.x=x/n;
	tmp.y=y/n;
	return tmp;
}
node S[5],T[5];
ll ds[5],dt[5];
ll sn=1,tn=1;
ll ans=4e18;
ll w[5];
int main()
{
	scanf("%lld",&n);
	scanf("%lld%lld%lld%lld",&sx,&sy,&tx,&ty);
	if(n==1)
	{
		printf("%lld",abs(sx-tx)+abs(sy-ty));
		return 0;
	}
	S[0]=B(sx,sy),T[0]=B(tx,ty);
	if(S[0].x==T[0].x&&S[0].y==T[0].y)
	{
		if((S[0].x&1)==(S[0].y&1)) ans=abs(sx-tx)+abs(sy-ty);
		else
		{
			printf("0");
			return 0;
		}
	}
	if((S[0].x&1)==(S[0].y&1))
	{
		sn=4;
		S[1]=(node){S[0].x-1,S[0].y};ds[1]=abs(S[0].x*n-sx)+1;
		S[2]=(node){S[0].x,S[0].y-1};ds[2]=abs(S[0].y*n-sy)+1;
		S[3]=(node){S[0].x+1,S[0].y};ds[3]=abs(S[0].x*n+n-sx);
		S[4]=(node){S[0].x,S[0].y+1};ds[4]=abs(S[0].y*n+n-sy);
	}
	else S[1]=S[0];
	if((T[0].x&1)==(T[0].y&1))
	{
		tn=4;
		T[1]=(node){T[0].x-1,T[0].y};dt[1]=abs(T[0].x*n-tx)+1;
		T[2]=(node){T[0].x,T[0].y-1};dt[2]=abs(T[0].y*n-ty)+1;
		T[3]=(node){T[0].x+1,T[0].y};dt[3]=abs(T[0].x*n+n-tx);
		T[4]=(node){T[0].x,T[0].y+1};dt[4]=abs(T[0].y*n+n-ty);
	}
	else T[1]=T[0];
	for(int i=1;i<=sn;i++)
	{
		for(int j=1;j<=tn;j++)
		{
			ll dis=d(S[i].x,S[i].y,T[j].x,T[j].y);
			ans=min(ans,dis+ds[i]+dt[j]);
		}
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：fire_and_sweets (赞：1)

显然，为了减小答案，我们尽量在大块之间进行行走。

注意到从一个大块到另一个大块所需要花费的距离为 $2$。于是我们只需要把原图中小格子坐标转换成大格子坐标，直接求距离就可以了。

但是有一个特例，$k=2$。这时，如果要从大格子坐标为 $(i,j)$ 的格子走到大格子坐标为 $(i+2,j)$ 的格子里时，可以直接从小格子横冲直撞而过，距离为 $3$。如果使用上文中提到的方法，距离为 $4$，不如横冲直撞的方法来得要好，因此特判之。

所以这题的做法是，通过枚举第一步的方向把在小格子中的起始位置或终止位置变到大格子里面去进行计算，最后特别处理 $k=2$ 的情况即可。

代码实现略显复杂，但也没有很大挑战性。

```
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int dx[] = {0, -1, 0, 1, 0};
const int dy[] = {0, 0, -1, 0, 1};

int k, sx, sy, tx, ty, res;

int L(int x)
{
    return x * k;
}

int R(int x)
{
    return x * k + k - 1;
}

int get(int dir, int x, int y, int X, int Y) // 计算小块到大块的距离
{
    if (dir == 1) return abs(R(X) - x);
    else if (dir == 2) return abs(R(Y) - y);
    else if (dir == 3) return abs(L(X) - x);
    else if (dir == 4) return abs(L(Y) - y);
    return 0;
}

bool check(int x, int y)
{
    return (x + y) % 2 == 1; // 返回 1 表示是大块
}

signed main()
{
    cin >> k >> sx >> sy >> tx >> ty;
    sx += k, sy += k, tx += k, ty += k;
    res = abs(sx - tx) + abs(sy - ty);
    if (k >= 2)
    {
        int ax = sx / k, ay = sy / k;
        int bx = tx / k, by = ty / k;
        int al = 0, ar = 0, bl = 0, br = 0;
        if (!check(ax, ay)) al = 1, ar = 4;
        if (!check(bx, by)) bl = 1, br = 4;
        for (int i = al; i <= ar; i ++ )
        {
            int x = ax + dx[i], y = ay + dy[i];
            int tmp = get(i, sx, sy, x, y);
            for (int j = bl; j <= br; j ++ )
            {
                int X = bx + dx[j], Y = by + dy[j];
                int cur = tmp + get(j, tx, ty, X, Y);
                if (k > 2) cur += max(abs(X - x), abs(Y - y)) * 2;
                else
                {
                    int t = min(abs(X - x), abs(Y - y));
                    cur += 2 * t + (max(abs(X - x), abs(Y - y)) - t) / 2 * 3;
                }
                res = min(res, cur);
            }
        }
    }
    cout << res << endl;
    return 0;
}
```

---

## 作者：yemuzhe (赞：1)

~~赛时看到这种题一眼细节巨多，先跳去写 G 了，~~

我们把所有 $\big (\lfloor {x \over k} \rfloor, \big \lfloor {y \over k} \rfloor)$ 相同的小方格划分成一块区域。

首先一种可行的通行费是两地的曼哈顿距离（两地在同一块小方格区域的情况下）。

注意，两地在同一块小方格区域的时候答案并不一定是两地的曼哈顿距离，比如说两地都在这块区域的边缘的时候，借路大方格可能会更优 ~~（作者赛时就因为这个吃了一发罚时）~~。

$k = 1$ 时直接判答案为两地曼哈顿距离。接下来讨论 $k \ge 2$ 的情况。

如果两地都在大方格，那么直接计算两个大方格之间的最少通行费。

对于不在大方格上的地，可以枚举其所在小方格区域的上下左右四块大方格，先走到大方格去再说。

我们用一个 `calc` 函数计算这步的通行费，具体可以看代码。

现在来讨论如何计算两块大方格之间的最少通行费：

---

首先我们重新建立坐标系，在新的坐标系中，把 $k$ 作为单位长度，也就是把 $k \times k$ 的区域作为一格。原点不变。

由于斜着很难受，如果我们把坐标系顺时针旋转 $45 ^ \circ$，再把原来在 $(0, 1)$ 的大方格作为原点，会发现对于原来任意一个大方格 $(x, y)$，它的坐标会变成 $\big (\lfloor {x + y \over 2} \rfloor, \lfloor {y - x \over 2} \big \rfloor)$。（感觉一下即可）

补充一点，如果把新坐标系沿 $y = - \frac 1 2$ 翻折，会得到大方格 $(x, y)$ 对应的是 $\big (\lfloor {x + y \over 2} \rfloor, \lfloor {x - y \over 2} \big \rfloor)$。（这只是个人习惯）

设两个大方格新的坐标分别为 $(sx, sy)$ 和 $(tx, ty)$。

如果 $k \ge 3$，容易发现斜着走是最优的，如下图（借用一下题目的图片）：

![](https://cdn.luogu.com.cn/upload/image_hosting/n2j3lz7x.png)

在原坐标系上斜着走等价于在新坐标系上横竖着走，每走一步需穿过边界线两次，所以答案为两点间曼哈顿距离的两倍，即 $2 (|sx - tx| + |sy - ty|)$。

当 $k = 2$ 时，横竖着走比较优，但最优方案一定不会既横着走又竖着走，如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/w97b6h1a.png)

所以我们要让横的或竖的（指原坐标系）尽量多，其它都走斜的，但一定不要为了走横着或竖着而绕远路。

发现横着或竖着走的距离应该为 $\min \{|sx - tx|, |sy - ty|\}$，因为横着或竖着走相当于在新坐标系上斜着走，也就是横坐标之差和纵坐标之差相互抵消的过程。

那么斜着走的距离就应该为横纵坐标之差的差（有点绕），即为 $\big||sx - tx| - |sy - ty|\big|$。

横竖着走每走一步需穿过边界三次，斜着走每走一步需穿过边界两次。

故 $k = 2$ 的答案为 $3 \cdot \min \{|sx - tx|, |sy - ty|\} + 2 \big||sx - tx| - |sy - ty|\big|$。

```cpp
#include <cstdio>
#include <algorithm>
#define abs(x) ((x)>0?(x):-(x))
using namespace std;

const int dx[] = {-1, 1, 0, 0}, dy[] = {0, 0, -1, 1};

long long k, sx, sy, tx, ty, ans;
long long ux, uy, vx, vy;

long long calc (long long x, long long y, int d)
{
    if (!d) return x + 1;
    if (d == 1) return k - x;
    if (d == 2) return y + 1;
    return k - y;
}

long long solve (long long sx, long long sy, long long tx, long long ty)
{
    long long dx = abs (sx + sy - (tx + ty) >> 1);
    long long dy = abs (sx - sy - (tx - ty) >> 1);
    if (k > 2) return 2 * (dx + dy);
    long long mn = min (dx, dy);
    return 3 * mn + 2 * abs (dx - dy);
}

int main ()
{
    scanf ("%lld%lld%lld%lld%lld", &k, &sx, &sy, &tx, &ty);
    ux = sx / k, uy = sy / k, vx = tx / k, vy = ty / k;
    ans = abs (sx - tx) + abs (sy - ty);
    if (k == 1) return 0 * printf ("%lld", ans);
    if (ux + uy & 1 && vx + vy & 1) ans = solve (ux, uy, vx, vy);
    else if (vx + vy & 1)
    {
        for (int i = 0; i < 4; i ++)
        {
            long long mx = ux + dx[i], my = uy + dy[i];
            long long c = calc (sx - ux * k, sy - uy * k, i);
            ans = min (ans, solve (mx, my, vx, vy) + c);
        }
    }
    else if (ux + uy & 1)
    {
        for (int i = 0; i < 4; i ++)
        {
            long long nx = vx + dx[i], ny = vy + dy[i];
            long long c = calc (tx - vx * k, ty - vy * k, i);
            ans = min (ans, solve (ux, uy, nx, ny) + c);
        }
    }
    else
    {
        for (int i = 0; i < 4; i ++)
        {
            long long mx = ux + dx[i], my = uy + dy[i];
            long long c1 = calc (sx - ux * k, sy - uy * k, i);
            for (int j = 0; j < 4; j ++)
            {
                long long nx = vx + dx[j], ny = vy + dy[j];
                long long c2 = calc (tx - vx * k, ty - vy * k, j);
                ans = min (ans, solve (mx, my, nx, ny) + c1 + c2);
            }
        }
    }
    printf ("%lld", ans);
    return 0;
}
```

---

## 作者：sunzz3183 (赞：1)

# AT_abc353_f [ABC353F] Tile Distance 题解

## 分析

首先我们将读入的坐标都加上 $k$，这样代价不变，且处理过程中有可能会向左或下走的情况，这样能保证处理的坐标都是 $>0$，处理的时候直接除以 $k$ 下取整就是大块的坐标了。

我们令 $x,y$ 为小块坐标，$X,Y$ 为大块坐标。

然后我们考虑走的几种情况（先只考虑 $k$ 都比较大的情况）：

1. 小块走到小块

- 直接从小块走到小块

答案就是 $|Sx-Tx|+|Sy-Ty|$。

- 从一个小块走到大块，然后走到其他大块，再走到小块。

我们考虑枚举两个小块分别走到的上、下、左、右方位（相邻）的大块，那么答案就是：起点小块到大块+大块到大块+大块到起点小块。

可以发现，小块到相邻的大块的距离一定是直着走，不拐弯，比较难的就是大块到大块，我们试着画一下图：

![](https://cdn.jsdelivr.net/gh/sunzz3183/szzphoto@img/img/202405161917346.png)

发现从一个大块到另一个步数是 $2$。

所以答案就是 $\max(|SX-TX|,|SY-TY|)\times 2$。

2. 小块到大块

只是少一个枚举，和情况 $1$ 一样。

3. 大块到大块

少枚举两个，和情况 $1$ 一样，答案直接是 $\max(|SX-TX|,|SY-TY|)\times 2$。

### 特判

我们刚才考虑的都是 $k$ 比较大的情况，那么我们想想小的时候会发生什么？

- $k=1$

相当于全是小块，答案 $|Sx-Tx|+|Sy-Ty|$。

- $k=2$

![](https://cdn.jsdelivr.net/gh/sunzz3183/szzphoto@img/img/202405161925740.png)

发现两个同一行的大块直接走显然更优，所以答案要特判。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    char ch=getchar();int x=0;bool f=1;
    while(ch<'0'||'9'<ch){if(ch=='-')f=0;ch=getchar();}
    while('0'<=ch&&ch<='9'){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
    return f?x:-x;
}
const int nxt[5][2]={{0,0},{-1,0},{0,-1},{1,0},{0,1}};//中，下，左，上，右四个方位
int k,sx,sy,tx,ty,ans;
inline int Abs(const int x){return x<0?-x:x;}//手写绝对值
inline int L(const int x){return x*k;}//大块的最左\下的坐标
inline int R(const int x){return x*k+k-1;}//大块的最右\上的坐标
bool check(int x,int y){return (x+y)&1;}
inline int calc(int i,int x,int y,int X,int Y){//小块到大块距离
    if(i==1)return Abs(R(X)-x);
    else if(i==2)return Abs(R(Y)-y);
    else if(i==3)return Abs(L(X)-x);
    else if(i==4)return Abs(L(Y)-y);
    return 0;
}
signed main(){
    k=read();
    sx=read()+k,sy=read()+k,tx=read()+k,ty=read()+k;
    ans=Abs(sx-tx)+Abs(sy-ty);//直接走
    if(k>1){
        int ax=sx/k,ay=sy/k,bx=tx/k,by=ty/k,al=0,ar=0,bl=0,br=0;
        if(!check(ax,ay))al=1,ar=4;//判断大小块，看看是否要枚举
        if(!check(bx,by))bl=1,br=4;
        for(int i=al;i<=ar;i++){
            int x=ax+nxt[i][0],y=ay+nxt[i][1];
            int tmp=calc(i,sx,sy,x,y);
            for(int j=bl;j<=br;j++){
                int X=bx+nxt[j][0],Y=by+nxt[j][1];
                int res=tmp+calc(j,tx,ty,X,Y);
                if(k>2)res+=max(Abs(X-x),Abs(Y-y))*2;
                else{//k=2的特判
                    int t=min(Abs(X-x),Abs(Y-y));
                    res+=t*2+(max(Abs(X-x),Abs(Y-y))-t)/2*3;
                }
                ans=min(ans,res);
            }
        }
    }
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：__Louis__ (赞：0)

### 题解：AT_abc353_f [ABC353F] Tile Distance

### 思路

遇到大模拟千万不要慌，一定要把所有的情况归类，这样就好些很多。

那么如何归类呢？

注意到步子减少的部分都是在走大格子，所以我们可以把答案分成三步。

- 从起点小格子走到一个大格子（如果在大格里就是零）。

- 从大格子移到终点附近的某一个大格子。

- 然后再从大格子走到终点。

注意到我们可以快速算出从大格子到大格子的方案，而且第一步是走到起点四周的大格子，第二步是走到终点四周的大格子。

那么完全可以枚举大格子，然后用处理计算路径长度的函数就行了。

第一步和第三步的函数直接暴力判断即可，现在来说第二步。

这里设 

$$mx=\max(|x_1-x_2|,|y_1-y_2|)\\ mn=\min(|x_1-x_2|,|y_1-y_2|)$$

其中坐标是对于大的格子而言的。

分类讨论如果 $K>2$，那么发现瓶颈在于最大坐标差，于是答案是：

$$ 2\times mx$$

$K=2$ 时，发现斜着走完了以后就没有走大格子的必要了，于是答案是：

$$ 2\times mn + \frac{3\times (mx-mn)}{2}$$

$K=1$ 时直接输出即可，特判掉。

那么现在就全部做完了，好写也好像。

### code


```cpp
// LUOGU_RID: 188495964
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=2e5+10;
int k;
int a1,b1,a2,b2;
int d[5][2]={{1,0},{-1,0},{0,1},{0,-1},{0,0}};
int g(int a,int b,int x,int y){//step 1 and 3
	int p=a/k,q=b/k;
	if(p==x&&y==q) return 0;
	if(p==x+1&&y==q) return a-(x+1)*k+1;
	else if(p==x-1&&y==q) return x*k-a;
	else if(p==x&&q==y+1) return b-(y+1)*k+1;
	else return y*k-b;
}
int h(int p1,int q1,int p2,int q2){//step 2
	if(k==2){
		int mx=max(abs(p1-p2),abs(q1-q2)),mn=min(abs(p1-p2),abs(q1-q2));
		return mn*2+(mx-mn)/2*3;
	}else{
		int mx=max(abs(p1-p2),abs(q1-q2));
		return mx*2;
	}
}
signed main(){
		
	scanf("%lld%lld%lld%lld%lld",&k,&a1,&b1,&a2,&b2);
	if(k==1){
		printf("%lld",abs(a1-a2)+abs(b1-b2));
		return 0;
	}
	int p1=a1/k,q1=b1/k,p2=a2/k,q2=b2/k;
	vector<pair<int,int> > v1,v2;
	for(int i=0;i<5;i++){
		int x=p1+d[i][0],y=q1+d[i][1];
		if((x+y)&1) v1.push_back(make_pair(x,y));
	}
	for(int i=0;i<5;i++){
		int x=p2+d[i][0],y=q2+d[i][1];
		if((x+y)&1) v2.push_back(make_pair(x,y));
	}
	int ans=0x3f3f3f3f3f3f3f3f;
	for(int i=0;i<v1.size();i++){
		for(int j=0;j<v2.size();j++){
			int f=g(a1,b1,v1[i].first,v1[i].second)+g(a2,b2,v2[j].first,v2[j].second);
			ans=min(ans,f+h(v1[i].first,v1[i].second,v2[j].first,v2[j].second));
		}
	}
	if(p1==p2&&q1==q2&&(!((p1+q1)&1))){
		ans=min(ans,abs(a1-a2)+abs(b1-b2));
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：ilibilib (赞：0)

回来补补题。

## 分析：

我先考虑 $k$ 很大的时候，大块和大块间的移动，我们不得不尽量避免小块：

![](https://cdn.luogu.com.cn/upload/image_hosting/yk6jq42o.png)

我们容易发现这样时是最优的，可以发现就是在斜着走，也就是典型的**切比雪夫距离**。斜着走一次需要经过两条边，所以花费是两倍的**切比雪夫距离**。

要是起点和终点不在大块上呢？

首先考虑它们不在同一大块（这里的大块意义不同于前面说的大块，具体见下）内：

![](https://cdn.luogu.com.cn/upload/image_hosting/ga42jiui.png)

显然，路径上必然是从起点到一个相邻的大块，然后进行大块和大块间的移动到达与终点相邻的大块，然后再直直进入。

路径简化为：**起点** 到 **起点相邻的大块** 再到 **终点相邻的大块** 最后到 **终点**。

我们明确起点和终点，但**起点相邻的大块**和**终点相邻的大块**并不确定，但相邻的大块只有 $4$ 个，所以枚举一下 $4\times 4$ 就行了，如果起点或终点本来就在大块上就不用考虑了。

要是它们是在同一大块的小块呢？

如图：



![](https://cdn.luogu.com.cn/upload/image_hosting/z0telt1a.png)

那么它们间的路径可能就不会经过大块了，可以在小块内之间相互抵达，但也可能经过大块，所以还是要进行上面的那种讨论。

$k$ 较小时呢？

$k=1$，显然就不用考虑那么多了，直接就是曼哈顿距离了。

$k=2$ 呢？

![](https://cdn.luogu.com.cn/upload/image_hosting/qaz2q9wg.png)

大块间移动的最短距离不再是切比雪夫距离了，特判一下就行了。

$k=3$ 时就等同于前面 $k$ 很大的情况啦。

然后我们就可以轻松切了这题啦。

## code：

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int k;
int solve(int x1,int y1,int x2,int y2)
{
    if(k==2) return 2*max(abs(x1-x2),abs(y1-y2))-abs(abs(x1-x2)-abs(y1-y2))/2; 
    return 2*max(abs(x1-x2),abs(y1-y2));
}
vector<pair<pair<int,int>,int>>v[2];
void check(int x,int y,int op)
{
    if((x/k+y/k)%2) v[op].push_back({{x/k,y/k},0});
    else
    v[op].push_back({{x/k-1,y/k},(x%k)+1}),v[op].push_back({{x/k,y/k-1},(y%k)+1}),
    v[op].push_back({{x/k+1,y/k},k-(x%k)}),v[op].push_back({{x/k,y/k+1},k-(y%k)});
}
signed main()
{
    int x1,y1,x2,y2,ans=1e18;
    cin>>k;
    cin>>x1>>y1>>x2>>y2;
    if(k==1) {cout<<abs(y1-y2)+abs(x1-x2);return 0;}
    if(x1/k==x2/k&&y1/k==y2/k) ans=abs(y1-y2)+abs(x1-x2);
    check(x1,y1,0);check(x2,y2,1);
    for(auto i:v[0]) for(auto j:v[1]) ans=min(ans,solve(i.first.first,i.first.second,j.first.first,j.first.second)+i.second+j.second);
    cout<<ans;
    return 0;
}
```

---

## 作者：TruchyR (赞：0)

累不死人的一道好的分讨题。  

首先最坏情况即两点的曼哈顿距离然后讨论两点在不在大地砖中。   

如果两点都在大地砖中，直接计算即可。  

如果有点在小地砖中，要先从小地砖走到大地砖，然后就可直接计算。  

需要注意如果两点在同一片小地砖中，有直接走和先到大地砖再回来两种方案，前者就是曼哈顿距离，后者同上。  

所以我们现在要解决的问题就是从一个大地砖走到另一个大地砖的最小代价！  

发现斜着走一次只需要花费 $2$ 的代价，只斜着走就是一种方案。  

但是发现有一些特殊情况（$k<3$），直着走两格只需要花费 $k+1$ 的代价。  

对于这种情况，先尽可能斜着走，再一直直着走显然为一种方案。  

于是这个问题就解决了，有些部分可以看代码。  

```cpp
#include<bits/stdc++.h>
#define CKE if(CHECK)
#define FRE if(FIL)
#define int long long
#define INF 1000000000000000000ll
using namespace std;
const int CHECK=0,FIL=0;int read();
int k,sx,sy,tx,ty,res,spx,spy,tpx,tpy,smo,tmo; 
int Abs(int xx){return xx<0?-xx:xx;}
int findMin(int x,int y){
	//此函数即从一个大地砖走到另一个大地砖的最小代价 
	if(x<0) x=-x;
	if(y<0) y=-y;
	if(x>y) swap(x,y);
	int ans=y*2;//斜着走的代价推一下得到是长的一段的两倍 
	ans=min(ans,(y-x)/2*(k+1)+x*2);//先把短的一段斜着走完，再直着走长的一段 
	return ans;
}
signed main(){
	k=read();
	sx=read();sy=read(); spx=sx/k,spy=sy/k; smo=(spx+spy+1)%2; 
	tx=read();ty=read(); tpx=tx/k,tpy=ty/k; tmo=(tpx+tpy+1)%2; 
	res=Abs(sx-tx)+Abs(sy-ty);//曼哈顿距离 
	sx%=k,sy%=k;tx%=k,ty%=k; 
	if(!smo && !tmo){//都在大地砖内 
		res=min(res,findMin(spx-tpx,spy-tpy));
	}else if(smo && tmo){//都在小地砖内 
		res=min(res,findMin((spx-1)-(tpx-1),spy-tpy)+sx+1+tx+1);
		res=min(res,findMin((spx+1)-(tpx-1),spy-tpy)+(k-sx)+tx+1);
		res=min(res,findMin(spx-(tpx-1),(spy-1)-tpy)+sy+1+tx+1);
		res=min(res,findMin(spx-(tpx-1),(spy+1)-tpy)+(k-sy)+tx+1);
		
		res=min(res,findMin((spx-1)-(tpx+1),spy-tpy)+sx+1+(k-tx));
		res=min(res,findMin((spx+1)-(tpx+1),spy-tpy)+(k-sx)+(k-tx));
		res=min(res,findMin(spx-(tpx+1),(spy-1)-tpy)+sy+1+(k-tx));
		res=min(res,findMin(spx-(tpx+1),(spy+1)-tpy)+(k-sy)+(k-tx));
		
		res=min(res,findMin((spx-1)-tpx,spy-(tpy-1))+sx+1+ty+1);
		res=min(res,findMin((spx+1)-tpx,spy-(tpy-1))+(k-sx)+ty+1);
		res=min(res,findMin(spx-tpx,(spy-1)-(tpy-1))+sy+1+ty+1);
		res=min(res,findMin(spx-tpx,(spy+1)-(tpy-1))+(k-sy)+ty+1);
		
		res=min(res,findMin((spx-1)-tpx,spy-(tpy+1))+sx+1+(k-ty));
		res=min(res,findMin((spx+1)-tpx,spy-(tpy+1))+(k-sx)+(k-ty));
		res=min(res,findMin(spx-tpx,(spy-1)-(tpy+1))+sy+1+(k-ty));
		res=min(res,findMin(spx-tpx,(spy+1)-(tpy+1))+(k-sy)+(k-ty));
	}else{//一个点在小地砖内 
		if(tmo){
			swap(sx,tx);swap(sy,ty);
			swap(spx,tpx);swap(spy,tpy);
			swap(smo,tmo);
		}
		res=min(res,findMin((spx-1)-tpx,spy-tpy)+sx+1);
		res=min(res,findMin((spx+1)-tpx,spy-tpy)+(k-sx));
		res=min(res,findMin(spx-tpx,(spy-1)-tpy)+sy+1);
		res=min(res,findMin(spx-tpx,(spy+1)-tpy)+(k-sy));
		//分别为在小地砖内的点走到周围四个大地砖的情况，两个点都在的情况就是都讨论一遍 
	}
	printf("%lld\n",res);
	return 0;
}
int read(){
	int Ca=0;char Cr=' ';int Cf=1;
	while(Cr<'0' || Cr>'9'){Cr=getchar();if(Cr=='-'){Cf=-1;}}
	while(Cr>='0' && Cr<='9'){Ca=Ca*10+Cr-48;Cr=getchar();}
	return Ca*Cf;
}
```

---

## 作者：louisliang (赞：0)

## [ABC353F] Tile Distance 题解
[cnblogs](https://www.cnblogs.com/louisliang/p/18199656)

题目传送门：[洛谷](https://www.luogu.com.cn/problem/AT_abc353_f)，[Atcoder](https://atcoder.jp/contests/abc353/tasks/abc353_f)

### Solution

很恶心人的分类讨论题。

很显然走大格子大概率比走小格子快。

对终点和起点向上下左右枚举大格子，我们就把问题转化为给两个大格子 $(a,b)$、$(c,d)$，求怎样走最快。

对角的大格子可以通过 $2$ 步相互到达，如下图所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/foknjik1.png)

于是我们可以以以下路径，这是一般情况的最短路径，步数为 $\max(|a-c|,|b-d|)$。（据说这是切比雪夫距离）

![](https://cdn.luogu.com.cn/upload/image_hosting/zucij1d0.png)

然而当 $k \leq 2$，最后一段路不需要上下横跳，直接横穿小格子即可，步数为 $\frac{k+1}{2}\min(|a-c|,|b-d|)+||a-c|-|b-d||$。

![](https://cdn.luogu.com.cn/upload/image_hosting/viknamuv.png)

最后要讨论只通过小格子达到的情况，就让上面算出的答案和曼哈顿距离去最小值就好了。

#### 注意：若起点和终点在同一个小格子的块中，答案不一定是他们的曼哈顿距离，就像下图所示的情况，显然红线比绿线短。

![](https://cdn.luogu.com.cn/upload/image_hosting/58f4e31e.png)

### code
```cpp
#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<queue>
#include<cstring>
#include<cmath>
#include<cassert>
#define pr pair < long long, pair<long long, long long> >
#define mp make_pair
using namespace std;
long long k, sx, sy, tx, ty;
long long gt(long long ax, long long ay, long long bx, long long by){
	long long a = abs(ax - bx), b = abs(ay - by), ans = max(a, b) * 2, sp = max(a, b) - min(a, b);
	if(k == 1)
		return a + b;
	if(k == 2)
		return a + b + sp / 2;
	return ans;
}
vector < pr > a, b;
int main(){
	cin >> k >> sx >> sy >> tx >> ty;
	long long dsx = sx / k, dsy = sy / k, dtx = tx / k, dty = ty / k;
	long long dis = max(sx, tx) - min(sx, tx) + max(sy, ty) - min(sy, ty);
	if((dsx + dsy) % 2 == 0){
		a.push_back(mp(sx - dsx * k + 1, mp(dsx - 1, dsy)));
		a.push_back(mp(sy - dsy * k + 1, mp(dsx, dsy - 1)));
		a.push_back(mp((dsx + 1) * k - sx, mp(dsx + 1, dsy)));
		a.push_back(mp((dsy + 1) * k - sy, mp(dsx, dsy + 1)));
	}
	else
		a.push_back(mp(0, mp(dsx, dsy)));
	if((dtx + dty) % 2 == 0){
		b.push_back(mp(tx - dtx * k + 1, mp(dtx - 1, dty)));
		b.push_back(mp(ty - dty * k + 1, mp(dtx, dty - 1)));
		b.push_back(mp((dtx + 1) * k - tx, mp(dtx + 1, dty)));
		b.push_back(mp((dty + 1) * k - ty, mp(dtx, dty + 1)));
	}
	else
		b.push_back(mp(0, mp(dtx, dty)));
	long long minn = dis;
	for(auto i : a)
		for(auto j : b)
			minn = min(minn, i.first + j.first + gt(i.second.first, i.second.second, j.second.first, j.second.second));
	cout << minn << endl;
	return 0;
}
```

---

## 作者：eastcloud (赞：0)

一个还算简单的写法。

你考虑一条最优路径可能是什么样，我们称一个由很多小方格构成的块是实块，否则是空块。如果两个点都在空块里则是简单，先斜着走让一边的坐标相同，再斜上斜下就是最优的。

如果不在空块里，要么不经过空块相遇，这个特判一下，否则就枚举两个点第一个到达的空块，然后按上面方法处理即可。

赛时代码，写的复杂了点，其实有几个函数可以写的很简单。

```
// Problem: F - Tile Distance
// Contest: AtCoder - AtCoder Beginner Contest 353
// URL: https://atcoder.jp/contests/abc353/tasks/abc353_f
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define ll long long
#define fi first
#define se second
#define inf 0x3f3f3f3f3f3f3f3f
using namespace std;
ll read(){
	ll x=0,f=1;char ch=getchar();
	while(ch<'0' || ch>'9')f=(ch=='-'?-1:1),ch=getchar();
	while(ch>='0' && ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return x*f;
}
void write(ll x){
	if(x<0)x=-x,putchar('-');
	if(x/10)write(x/10);
	putchar(x%10+'0');
}
ll k;
ll solve(pair<ll,ll> c,pair<ll,ll> d){
	ll a=c.fi,b=c.se,x=d.fi,y=d.se;
	ll d1=abs(a-x),d2=abs(b-y),ans=0;
	if(d1>d2)swap(d1,d2);
	ans+=d1*2;d2-=d1;
	ans+=min(d2*(k+1)/2,d2*2);
	return ans;
}
pair<ll,ll> pre(ll a,ll b,ll dir){
	if((a/k+b/k)%2==1)return make_pair(a/k,b/k);
	else{
		if(dir==1)return make_pair((a+k)/k,b/k);
		if(dir==2){
			if(a-k<0)return make_pair(-1,b/k);
			else return make_pair((a-k)/k,b/k);
		}
		if(dir==3)return make_pair(a/k,(b+k)/k);
		if(dir==4){
			if(b-k<0)return make_pair(a/k,-1);
			return make_pair(a/k,(b-k)/k);
		}
	}
}
ll co(ll a,ll b,ll dir){
	if((a/k+b/k)%2==1)return 0;
	else{
		ll x=a-a/k*k,y=b-b/k*k;
		if(dir==1)return k-x;
		if(dir==2)return x+1;
		if(dir==3)return k-y;
		if(dir==4)return y+1;
	}
}
int main(){
	k=read();
	ll a=read(),b=read(),x=read(),y=read();
	ll ans=inf;
	if(a/k==x/k && b/k==y/k){
		if((a/k+b/k)%2==0)ans=abs(a-x)+abs(b-y);
		else ans=0;
	}
	for(ll i=1;i<=4;i++){
		for(ll j=1;j<=4;j++){
			ans=min(ans,co(a,b,i)+co(x,y,j)+solve(pre(a,b,i),pre(x,y,j)));
		}
	}	
	cout<<ans;
	return 0;
}
```

---

## 作者：elbissoPtImaerD (赞：0)

感受那股劲。

先感受一下，曼哈顿距离是可能的答案。当 $k=1$ 时这就是答案。

$k>1$ 时，考虑大格子会对答案产生什么影响。

感受一下，随着 $k$ 变大，最优方案直接穿过 $k\times k$ 的小格子的个数断然不增。因为我们能从大格子绕路。

用一下[官方题解](https://atcoder.jp/contests/abc353/editorial/9936)的图：
![](https://img.atcoder.jp/abc353/8202414d852f152deec2212178393888.png)

当 $k$ 较大时，通过左边这种方式绕路代替直接穿过是更优的。具体计算知，当 $k=2$ 时，直接穿过更优，$k>2$ 时，绕路更优。

那就做完了。

[$\color{green}{\checkmark}$](https://atcoder.jp/contests/abc353/submissions/53402477)

---

