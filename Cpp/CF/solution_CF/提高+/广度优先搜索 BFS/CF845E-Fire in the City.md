# Fire in the City

## 题目描述

The capital of Berland looks like a rectangle of size $ n×m $ of the square blocks of same size.

Fire!

It is known that $ k+1 $ blocks got caught on fire ( $ k+1<=n·m $ ). Those blocks are centers of ignition. Moreover positions of $ k $ of these centers are known and one of these stays unknown. All $ k+1 $ positions are distinct.

The fire goes the following way: during the zero minute of fire only these $ k+1 $ centers of ignition are burning. Every next minute the fire goes to all neighbouring blocks to the one which is burning. You can consider blocks to burn for so long that this time exceeds the time taken in the problem. The neighbouring blocks are those that touch the current block by a side or by a corner.

Berland Fire Deparment wants to estimate the minimal time it takes the fire to lighten up the whole city. Remember that the positions of $ k $ blocks (centers of ignition) are known and ( $ k+1 $ )-th can be positioned in any other block.

Help Berland Fire Department to estimate the minimal time it takes the fire to lighten up the whole city.

## 说明/提示

In the first example the last block can have coordinates $ (4,4) $ .

In the second example the last block can have coordinates $ (8,3) $ .

## 样例 #1

### 输入

```
7 7 3
1 2
2 1
5 5
```

### 输出

```
3
```

## 样例 #2

### 输入

```
10 5 1
3 3
```

### 输出

```
2
```

# 题解

## 作者：xfrvq (赞：5)

[$\tt Link$](/problem/CF845E)。

新思路。。

首先这个答案的值会比较大（$10^9$ 级别），而枚举答案或者直接计算答案的方式都不可行，于是我们考虑二分答案。

二分答案，那么就只需要判断某个时刻 $t$ 有没有被覆盖满。

注意到对于每个时刻，此时的图上应该是若干个矩形重叠的样式。注意到 $n,m$ 很大，不可能存下这些矩形，所以考虑离散化。

离散化完 $n,m$ 是 $k$ 的级别。在图上标记原来的 $k$ 个矩形，每个可能的边长是 $2t+1$ 的矩形，然后看有没有覆盖所有没有被标记的点。

这是另外一篇题解的思路，好想。反正我是不会写（因为有离散化，后面的操作变得复杂）。

我们不妨来考虑另一种思路。

假设已经标记矩形完成，现在应该是 *判断距离最远的两个未标记点的距离是否 $\le2t$*。

要求平面内两点最远距离？直接乱搞。我的方法是按照每个点到原点的距离排序，最后拿前 $40$ 个点和后 $40$ 个点的距离取 $\max$。

离散化是真的挺难写的。。

```cpp
#import<iostream>
#import<vector>
#import<ranges>
#import<algorithm>

using namespace std;

const int K = 1e3 + 5,S = 2e3 + 5;

int n,m,k,px[K],py[K];
int xl[K],xr[K],yl[K],yr[K];
int X[S],Y[S];
pair<int,int> p[S * S];
bool vis[S][S];

bool chk(int t){
	int lx = 0,ly = 0,lp = 0;
	for(int i = 1;i <= k;++i){
		xl[i] = max(px[i] - t,1);
		xr[i] = min(px[i] + t,n);
		yl[i] = max(py[i] - t,1);
		yr[i] = min(py[i] + t,m);
		X[++lx] = xl[i]; X[++lx] = xr[i];
		Y[++ly] = yl[i]; Y[++ly] = yr[i];
		if(xr[i] != n) X[++lx] = xr[i] + 1;
		if(yr[i] != m) Y[++ly] = yr[i] + 1;
	}
	X[++lx] = 1;
	Y[++ly] = 1; 
	sort(X + 1,X + lx + 1);
	sort(Y + 1,Y + ly + 1);
	lx = unique(X + 1,X + lx + 1) - X - 1;
	ly = unique(Y + 1,Y + ly + 1) - Y - 1;
	for(int i = 1;i <= k;++i){
		xl[i] = prev(upper_bound(X + 1,X + lx + 1,xl[i])) - X;
		xr[i] = prev(upper_bound(X + 1,X + lx + 1,xr[i])) - X;
		yl[i] = prev(upper_bound(Y + 1,Y + ly + 1,yl[i])) - Y;
		yr[i] = prev(upper_bound(Y + 1,Y + ly + 1,yr[i])) - Y;
		for(int x = xl[i];x <= xr[i];++x)
			for(int y = yl[i];y <= yr[i];++y) vis[x][y] = true;
	}
	for(int i = 1;i <= lx;++i)
		for(int j = 1;j <= ly;++j)
			if(vis[i][j]) vis[i][j] = 0;
			else p[++lp] = make_pair(i,j);
	sort(p + 1,p + lp + 1,[](auto a,auto b){
		auto[x0,y0] = a; auto[x1,y1] = b;
		return x0 * y0 != x1 * y1 ? x0 * y0 < x1 * y1 : x0 < y0;
	});
	int dis = 0;
	for(int i = 1;i <= min(40,lp);++i)
		for(int j = max(i,lp - 40);j <= lp;++j){
			auto[xi,yi] = p[i]; auto[xj,yj] = p[j];
			if(xi > xj) swap(xi,xj);
			if(yi > yj) swap(yi,yj);
			xi = X[xi]; xj = xj == lx ? n : X[xj + 1] - 1;
			yi = Y[yi]; yj = yj == ly ? m : Y[yj + 1] - 1;
			dis = max({dis,xj - xi,yj - yi});
		}
	return dis <= (2 * t);
}

int main(){
	cin >> n >> m >> k;
	for(int i = 1;i <= k;++i) cin >> px[i] >> py[i];
	int L = 0,R = max(n,m);
	while(R - L + 1 > 5){
		int mid = (L + R) >> 1;
		chk(mid) ? R = mid : L = mid + 1;
	}
	for(int i = L;i <= R;++i)
		if(chk(i)) return printf("%d\n",i),0;
	return 0;
} 
```

---

## 作者：林聪 (赞：4)

本题的题意很好理解，既然要求最短用时，那么不难想到二分答案，问题的关键在于如何check。

观察一下数据范围，发现n、m是1e9级别的，所以直接用二维数组去存储的话肯定是不行的。而k很小，最大只有500，所以考虑从k入手。

由于每个矩形覆盖的范围只跟它的四个角有关，所以考虑离散化，将这k个矩阵的四个角映射到1-1000，这样就可以很好地解决n、m范围过大的问题。

至于计算矩形覆盖面积的话，做一个二维差分+前缀和就好了。

接着，我们只需找到能够覆盖所有未覆盖格子的最小矩形，计算一下在t时间内能否扩散完这个矩形即可。

具体实现见代码。
```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int read()//快读不解释 
{
  int x=0;
  char c=getchar();
  while(c<'0'||c>'9')  c=getchar();
  while('0'<=c&&c<='9')
  {
  	x=(x<<3)+(x<<1)+c-'0';
  	c=getchar();
  }
  return x;
}
int n,m,k;//同题意 
struct node{int x,y;}a[505];//存点 
int x[1010],y[1010],xx[1010],yy[1010];//离散化用到的数组 
int find(int a[],int x,int len)//查找x在a数组中的位置 
{
  int l=1,r=len;
  while(l<=r)
  {
  	int mid=(l+r)>>1;
  	if(a[mid]<=x)  l=mid+1;
  	else  r=mid-1;
  }
  return r;
}
int d[1010][1010],s[1010][1010];//差分数组与前缀和数组 
bool check(int t)
{
  memset(d,0,sizeof(d));
  memset(s,0,sizeof(s));
  for(int i=1;i<=k;i++)//计算这k个矩形的四个角 
  {
  	x[i]=max(1,a[i].x-t),x[k+i]=min(n,a[i].x+t);
  	y[i]=max(1,a[i].y-t),y[k+i]=min(m,a[i].y+t);
  }
  x[k*2+1]=1,x[k*2+2]=n;
  y[k*2+1]=1,y[k*2+2]=m;//整个矩形的四个角也要参与离散化，不然差分会出问题 
  sort(x+1,x+k*2+3),sort(y+1,y+k*2+3);//离散化
  int tot1=0,tot2=0; 
  for(int i=1;i<=k*2+2;i++)  if(x[i]!=x[i-1])  xx[++tot1]=x[i]; 
  for(int i=1;i<=k*2+2;i++)  if(y[i]!=y[i-1])  yy[++tot2]=y[i];//去重  
  for(int i=1;i<=k;i++)
  {
  	int x1=find(xx,max(1,a[i].x-t),tot1);
	int y1=find(yy,max(1,a[i].y-t),tot2);
  	int x2=find(xx,min(n,a[i].x+t),tot1);
  	int y2=find(yy,min(m,a[i].y+t),tot2);//计算映射 
	d[x1][y1]++,d[x2][y1]--,d[x1][y2]--,d[x2][y2]++;
  }
  int up=n,down=1,left=m,right=1;//计算覆盖所有未覆盖格子的最小矩形 
  for(int i=1;i<tot1;i++)
    for(int j=1;j<tot2;j++)
      s[i][j]=s[i-1][j]+s[i][j-1]-s[i-1][j-1]+d[i][j];//计算前缀和 
  for(int i=1;i<tot1;i++)
    for(int j=1;j<tot2;j++)
      s[i][j]=min(s[i][j],1);//令所有格子非0即1，方便后面处理边界上的问题 
  for(int i=1;i<tot1;i++)
    for(int j=1;j<tot2;j++)
      if(!s[i][j])//遇到了一个空格子，然后还要看看有没有空隙 
        if(xx[i]+s[i-1][j]<xx[i+1]||xx[i]==n-1) 
	      if(yy[j]+s[i][j-1]<yy[j+1]||yy[j]==m-1)//还有空隙，说明存在未覆盖格子 
          {
            up=min(up,xx[i]+s[i-1][j]);
		    down=max(down,xx[i+1]-s[i+1][j]);
            left=min(left,yy[j]+s[i][j-1]);
		    right=max(right,yy[j+1]-s[i][j+1]);//更新目标矩形
	      }
  //当然这里还有其他的处理方式，就不赘述了 
  if(up==n&&down==1&&left==m&&right==1)  return 1;//已经全覆盖了 
  if(max(down-up,right-left)<=t*2)  return 1;//可以在t时间内覆盖完目标矩形 
  return 0;
}
int main()
{
  n=read(),m=read(),k=read();
  for(int i=1;i<=k;i++)  a[i].x=read(),a[i].y=read();
  if(k+1==n*m)//特判 
  {
  	printf("0");
  	return 0;
  }
  int l=1,r=max(n,m);
  while(l<=r)//二分答案 
  {
  	int mid=(l+r)>>1;
  	if(check(mid))  r=mid-1;
  	else  l=mid+1;
  }
  printf("%d",l);
  return 0;
}
```


---

## 作者：zesqwq (赞：2)

#  CF845E Fire in the City 题解
[题目链接_luogu](https://www.luogu.com.cn/problem/CF845E)

[题目链接_codeforces](https://codeforces.com/problemset/problem/845/E)

我们发现 $k$ 非常的小，然后就可以去考虑复杂度大于 $O(k^2)$ 的做法。

考虑二分答案，思考如何 $\text{check}$。

我们要先计算现有的火会扩散到哪些地方，然后求未覆盖的点构成的最大矩形。这就类似于一个矩形覆盖问题，显然是可以离散化+二维前缀和的。

但是你要是直接这样打完，可能会 $\text{Wrong answer on test 10}$。因为你会发现，离散化之后，有些火与火之间的间隙就被离散化离散掉了。此时，我们考虑描边，也就是说不仅将 $x_1,x_2,y_1,y_2$ 加入离散化数组，还要将 $x_1-1,x_2+1,y_1-1,y_2+1$ 加入离散化数组即可。

$\text{Code:}$

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e3 + 10;
int tx[N], ty[N], lenx, leny;
int nx[N], ny[N], lx[N], ly[N], rx[N], ry[N], n, m, k, a[N][N];
inline bool check(int x) {
    memset(a, 0, sizeof(a));
    lenx = leny = 0;
    tx[++lenx] = 1, tx[++lenx] = n;
    ty[++leny] = 1, ty[++leny] = m;
    for (int i = 1; i <= k; i++) {
        lx[i] = max(1, nx[i] - x), rx[i] = min(n, nx[i] + x);
        ly[i] = max(1, ny[i] - x), ry[i] = min(m, ny[i] + x);
        tx[++lenx] = lx[i], tx[++lenx] = rx[i], tx[++lenx] = max(1, lx[i] - 1), tx[++lenx] = min(n, rx[i] + 1);
        ty[++leny] = ly[i], ty[++leny] = ry[i], ty[++leny] = max(1, ly[i] - 1), ty[++leny] = min(m, ry[i] + 1);
    }
    sort(tx + 1, tx + lenx + 1), lenx = unique(tx + 1, tx + lenx + 1) - tx - 1;
    sort(ty + 1, ty + leny + 1), leny = unique(ty + 1, ty + leny + 1) - ty - 1;
    for (int i = 1; i <= k; i++) {
        lx[i] = lower_bound(tx + 1, tx + lenx + 1, lx[i]) - tx, ly[i] = lower_bound(ty + 1, ty + leny + 1, ly[i]) - ty;
        rx[i] = lower_bound(tx + 1, tx + lenx + 1, rx[i]) - tx, ry[i] = lower_bound(ty + 1, ty + leny + 1, ry[i]) - ty;
    }
    int L = 0x7f7f7f7f, R = 0, D = 0x7f7f7f7f, U = 0;
    for (int i = 1; i <= k; i++) ++a[lx[i]][ly[i]], --a[lx[i]][ry[i] + 1], --a[rx[i] + 1][ly[i]], ++a[rx[i] + 1][ry[i] + 1];
    for (int i = 1; i <= lenx; i++) {
        for (int j = 1; j <= leny; j++) {
            a[i][j] = a[i][j] + a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
            if (!a[i][j]) L = min(L, i), R = max(R, i), D = min(D, j), U = max(U, j);
        }
    }
    if (!R) return 1;
    int len = max(ty[U] - ty[D] + 1 >> 1, tx[R] - tx[L] + 1 >> 1);
    return len <= x;
}
int main() {
    cin >> n >> m >> k;
    for (int i = 1; i <= k; i++) scanf("%d %d", &nx[i], &ny[i]);
    int l = 0, r = max(n, m) + 1, mid, ans;
    while (l <= r) {
        mid = l + r >> 1;
        if (check(mid))
            r = mid - 1, ans = mid;
        else
            l = mid + 1;
    }
    printf("%d\n", ans);
    return 0;
}
```

---

## 作者：__vector__ (赞：1)

居然没有扫描线题解。  
扫描线远远快于二维前缀和，我的二维前缀和是 CF 上最劣解，而扫描线是最优解。  
## 做法  
可以二分答案。  

设当前二分到的时间是 $t$。 

考虑如何判定。  

显然被火烧过区域由一个个矩形组成。  

而我们的主要任务是求出没被矩形覆盖的区域能不能通过再添加一个边长为 $2t+1$ 的矩形解决，即找到没覆盖点的纵坐标最大值，纵坐标最小值，横坐标最大值，横坐标最小值。  
hy
考虑通过扫描线解决。  

把所有的矩形分成两个竖线，第一个竖线代表这个矩形出现，第二个竖线代表这个矩形消失。  

坐标虽然很大，把纵坐标离散化一下就解决了。 

然后把所有竖线按照升序排列，依次处理。  

如果第一条竖线横坐标大于 $1$，那么没覆盖纵坐标最大值和最小值直接确定为 $n$ 和 $1$，没覆盖最大最小横坐标对应更新一下。  

每处理一条竖线，就利用线段树修改这条竖线对应区间，用当前最高和最低没覆盖点进行更新，如果这条竖线存在点没覆盖，那么还可以更新横坐标。  


如果最后一条竖线后面有空的，再处理一下就行了。

关于线段树细节，树上每个点存储对应区间最高和最低没覆盖的点，然后常规维护就行了。  


注意离散化如果不把 $1$ 和 $n$ 也离散化，会 Wrong answer on test10。  
## Code  
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define FOR(i, a, b) for (int i = a; i <= b; i++)
#define REP(i, a, b) for (int i = a; i >= b; i--)
const int maxn = 3005;
int n, m, k;
struct Node
{
    int x, y;
    // 横坐标，纵坐标
} node[maxn];
ll lsh[maxn * 2];
int lshtop;
struct Line
{// 存储竖线信息
    ll x, y1, y2, mark;
    // y1 是这条竖线的上端点，y2 是下端点
} line[maxn * 2];
int linetop;
ll sgtcnt[maxn << 3], L[maxn << 3], R[maxn << 3], maxup[maxn << 3], mindw[maxn << 3];
// maxup 是最高的没覆盖点，min 是最低的没覆盖，注意这个是离散化之后的值
// sgtcnt 是当前区间被完全覆盖的次数
void build(int pos, int l, int r)
{
    sgtcnt[pos] = 0;
    L[pos] = l;
    R[pos] = r;
    maxup[pos] = r;
    mindw[pos] = l;
    if (l == r)
    {
        return;
    }
    int mid = (l + r) >> 1;
    build(pos << 1, l, mid);
    build(pos << 1 | 1, mid + 1, r);
}
void pushup(int now)
{
    if (sgtcnt[now])
    {
        maxup[now] = -5e9;
        mindw[now] = 5e9;
    }
    else
    {
        if (L[now] != R[now])
        {
            maxup[now] = max(maxup[now << 1], maxup[now << 1 | 1]);
            mindw[now] = min(mindw[now << 1], mindw[now << 1 | 1]);
        }
        else
        {
            maxup[now] = mindw[now] = L[now];
        }
    }
}
void change(int now, int l, int r, int val)
{
    if (l <= L[now] && R[now] <= r)
    {
        sgtcnt[now] += val;
        pushup(now);
        return;
    }
    if (L[now] > r || R[now] < l)
        return;
    int mid = (L[now] + R[now]) >> 1;
    if (mid >= l)
        change(now << 1, l, r, val);
    if (mid < r)
        change(now << 1 | 1, l, r, val);
    pushup(now);
}
bool check(ll time)
{
    lshtop = 0, linetop = 0;
    FOR(i, 1, k)
    {
        lsh[++lshtop] = min(1ll * n, node[i].y + time);
        lsh[++lshtop] = max(1ll, node[i].y - time);
        lsh[++lshtop] = min(1ll * n, node[i].y + time + 1);
        lsh[++lshtop] = max(1ll, node[i].y - time - 1);
        lsh[++lshtop] = min(1ll * n, max(1ll,node[i].y + time - 1));
        lsh[++lshtop] = max(1ll, min(1ll*n,node[i].y - time + 1));
    }
    lsh[++lshtop] = 1;
    lsh[++lshtop] = n;
    sort(lsh + 1, lsh + lshtop + 1);
    lshtop = unique(lsh + 1, lsh + lshtop + 1) - lsh - 1;
    // 离散化
    FOR(i, 1, k)
    {
        int nwy1 = lower_bound(lsh + 1, lsh + lshtop + 1, min(1ll * n, node[i].y + time)) - lsh;
        int nwy2 = lower_bound(lsh + 1, lsh + lshtop + 1, max(1ll, node[i].y - time)) - lsh;
        // 计算离散化之后的 y

        line[++linetop] = {max(1ll, node[i].x - time), nwy1, nwy2, 1};
        line[++linetop] = {min(1ll * m, node[i].x + time) + 1, nwy1, nwy2, -1};
        // 竖线
        // 第二条线代表删除这个矩形
    }
    sort(line + 1, line + linetop + 1, [&](Line &a, Line &b)
         {  if(a.x!=b.x)
                return a.x < b.x; 
            else
                return a.mark>b.mark; });// 对竖线按横坐标升序排列。  
    build(1, 1, lshtop);// 建树
    ll maxupf = -5e9, mindwf = 5e9, maxrigf = -5e9, minleff = 5e9;
    if (line[1].x > 1)
    {// 前面有空的区域
        maxupf = n;
        mindwf = 1;
        minleff = 1;
        maxrigf = line[1].x - 1;
        //       puts("Updated\n");
    }
    int cnt = 0;
    int posx=0;
    ll before_x = 0;
    FOR(i, 1, linetop)
    {// 运行扫描线
        if (line[i].x > m)
            break;
        change(1, line[i].y2, line[i].y1, line[i].mark);

        cnt++; // 计算到目前为止还有多少竖线没处理
        posx=line[i].x;
        if (line[i].x != line[i + 1].x)
        {
            cnt = 0;
            if (mindw[1] != 5e9)
            {
                maxupf = max(maxupf, lsh[maxup[1]]);
                mindwf = min(mindwf, lsh[mindw[1]]);
                maxrigf = max(maxrigf, line[i + 1].x - 1);
                minleff = min(minleff, before_x + 1);
            }
                before_x = line[i].x;
        }
    } 
    if (line[linetop].x < m)
    {// 后面有空的区域
        maxupf = n;
        mindwf = 1;
        maxrigf = m;
        minleff = min(minleff, line[linetop].x  + 1);
    }
    return ((maxupf - mindwf + 1 <= time * 2  + 1) && (maxrigf - minleff + 1 <= time * 2 +1));
}
int main()
{
    scanf("%d%d%d", &n, &m, &k);
    FOR(i, 1, k)
    {
        scanf("%d%d", &node[i].x, &node[i].y);
        swap(node[i].x, node[i].y);
    }
    int l = 0, r = 1e9;
    while (l < r)
    {
        int mid = (l + r) >> 1;
        if (check(mid))
        {
            r = mid;
        }
        else
        {
            l = mid + 1;
        }
    }
    printf("%d", l);
    return 0;
}

```



---

## 作者：ttq012 (赞：0)

看到用时最短就想到了二分答案。问题转化为 $p$ 秒能不能烧完整个格子。

考虑对这个网格图离散化一下，然后二维差分再二位前缀和。因为燃烧是八连通的所以只需要找到所有没有被覆盖的矩形，然后直接套公式算出来每一个矩形最少需要多少秒才能烧完即可。

```cpp
#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 500100;
int n, m, k, x[N], y[N], tx[N], ty[N], lx[N], ly[N], rx[N], ry[N], mp[2010][2010];
bool check(int p) {
    memset(mp, 0, sizeof mp);
    int sx = 0, sy = 0;
    tx[++sx] = 1, ty[++sy] = 1;
    tx[++sx] = n, ty[++sy] = m;
    for (int i = 1; i <= k; i++) {
        lx[i] = max(1ll, x[i] - p), rx[i] = min(n, x[i] + p);
        ly[i] = max(1ll, y[i] - p), ry[i] = min(m, y[i] + p);
        tx[++sx] = lx[i], ty[++sy] = ly[i];
        tx[++sx] = rx[i], ty[++sy] = ry[i];
        tx[++sx] = max(1ll, lx[i] - 1), ty[++sy] = max(1ll, ly[i] - 1);
        tx[++sx] = min(n, rx[i] + 1), ty[++sy] = min(m, ry[i] + 1);
    }
    sort(tx + 1, tx + sx + 1), sort(ty + 1, ty + sy + 1);
    sx = unique(tx + 1, tx + sx + 1) - tx - 1, sy = unique(ty + 1, ty + sy + 1) - ty - 1;
    for (int i = 1; i <= k; i++) {
        lx[i] = lower_bound(tx + 1, tx + sx + 1, lx[i]) - tx;
        rx[i] = lower_bound(tx + 1, tx + sx + 1, rx[i]) - tx;
        ly[i] = lower_bound(ty + 1, ty + sy + 1, ly[i]) - ty;
        ry[i] = lower_bound(ty + 1, ty + sy + 1, ry[i]) - ty;
    }
    for (int i = 1; i <= k; i++) {
        mp[lx[i]][ly[i]]++, mp[lx[i]][ry[i] + 1]--;
        mp[rx[i] + 1][ly[i]]--, mp[rx[i] + 1][ry[i] + 1]++;
    }
    int le = 1e18, up = 1e18, dw = -1e18, ri = -1e18;
    for (int i = 1; i <= sx; i++) for (int j = 1; j <= sy; j++) {
        mp[i][j] = mp[i - 1][j] + mp[i][j - 1] - mp[i - 1][j - 1] + mp[i][j];
        if (!mp[i][j]) le = min(le, i), ri = max(ri, i), dw = max(dw, j), up = min(up, j);
    }
    if (ri < 0) return true;
    else return max(tx[ri] - tx[le] + 1 >> 1, ty[dw] - ty[up] + 1 >> 1) <= p;
}
signed main() {
    cin >> n >> m >> k;
    for (int i = 1; i <= k; i++) cin >> x[i] >> y[i];
    int l = 0, r = max(n, m) + 1, best = -1;
    while (l <= r) {
        int mid = l + r >> 1;
        if (check(mid)) r = mid - 1, best = mid;
        else l = mid + 1;
    }
    cout << best << '\n';
}

---

