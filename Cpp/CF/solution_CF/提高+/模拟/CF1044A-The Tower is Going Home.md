# The Tower is Going Home

## 题目描述

在一个宽度为 $10^9$、高度为 $10^9$ 的棋盘上，行号自下而上从 $1$ 到 $10^9$，列号自左而右从 $1$ 到 $10^9$。因此，每个格子都可以用坐标 $(x, y)$ 表示，其中 $x$ 是列号，$y$ 是行号。

每天，黑白棋子都会在这块棋盘上激烈厮杀。今天，黑方获胜，但付出了惨重的代价——只剩下一只车存活下来，并且被逼到了左下角的格子 $(1,1)$。不过它依然很高兴，因为胜利属于它，现在是时候庆祝了！为了庆祝，车需要回家，也就是到达棋盘的最上边（即任意一个行号为 $10^9$ 的格子）。

本来一切都很顺利，但狡猾的白棋子在比赛结束前对棋盘上的某些位置施加了魔法。魔法分为两种类型：

- 垂直魔法。每个垂直魔法由一个数字 $x$ 定义。这样的魔法会在第 $x$ 列和第 $x+1$ 列之间制造一条无限阻挡线。
- 水平魔法。每个水平魔法由三个数字 $x_1$、$x_2$、$y$ 定义。这样的魔法会在第 $y$ 行、第 $x_1$ 列到第 $x_2$ 列（包含两端）之间的格子上方制造一段阻挡线。这类魔法有个特点：任意两条水平魔法线段不会有公共点。注意，水平魔法可以与垂直魔法有公共点。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1044A/4d99e8dcb502f146f754f5a6e1fe990cd7a19a89.png)

我们再回顾一下，车是一种可以在一步内移动到同一行或同一列任意位置的棋子。在本题中，车可以从格子 $(r_0, c_0)$ 移动到格子 $(r_1, c_1)$，前提是 $r_1 = r_0$ 或 $c_1 = c_0$，并且这两个格子之间没有阻挡线或阻挡段（具体可参考样例）。

幸运的是，车可以移除魔法，但这需要付出极大的努力。因此，它希望移除的魔法数量尽可能少，使得它能够回家。请你计算，车最少需要移除多少个魔法，才能从 $(1,1)$ 到达至少一个行号为 $10^9$ 的格子。

## 说明/提示

在第一个样例中，为了让车回家，只需移除第二个水平魔法。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1044A/9992fec5adf078b64d855d970d260a491b71be69.png)

在第二个样例中，只需移除唯一的垂直魔法。如果只移除某一个水平魔法，车依然无法回家，因为它会被剩下的水平魔法从上方阻挡，右侧又被垂直魔法阻挡。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1044A/55c35aa981684ef1bef35aec7b2c7bc122d79cca.png)

在第三个样例中，有两条横跨整个棋盘的水平魔法，无法绕过，必须全部移除。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1044A/4798caa5246fd4cee2f0cac48238b0b3e5e86d50.png)

在第四个样例中，没有任何魔法，因此无需移除任何魔法。

在第五个样例中，可以移除第一个垂直魔法和第三个水平魔法。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1044A/7e60e0d3bee2b2095c31f53125c2acbd54e1dc82.png)

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2 3
6
8
1 5 6
1 9 4
2 4 2
```

### 输出

```
1```

## 样例 #2

### 输入

```
1 3
4
1 5 3
1 9 4
4 6 6
```

### 输出

```
1```

## 样例 #3

### 输入

```
0 2
1 1000000000 4
1 1000000000 2
```

### 输出

```
2```

## 样例 #4

### 输入

```
0 0
```

### 输出

```
0```

## 样例 #5

### 输入

```
2 3
4
6
1 4 3
1 5 2
1 6 5
```

### 输出

```
2```

# 题解

## 作者：_xxxxx_ (赞：3)

### 题意

现在有一个大小为 $10^{9} \times 10^{9}$ 的棋盘，一个国际象棋的车在棋盘 $(1,1)$ 的位置上，在这个棋盘上，有 $n$ 道竖着的墙，有 $m$ 道横着的墙。竖着的墙表示整条竖线不能通过，横着的表示这一条指定的横线不能通过。对于横线，有 $3$ 个参数 $l,r,h$。代表在棋盘第 $h$ 行的 $l$ 到 $r$ 不能通过。

现在这个车要去到棋盘 $10^{9}$ 行，问它最少要消除多少堵墙才能到达。

### 分析

要跑到 $10^{9}$ 行，数据很大，不能直接建数组存哪里能去。横线的 $l,r$ 范围也是 $10^{9}$。因此不能通过暴力解决。

再看 $n,m$ 是 $10^{5}$。时间复杂度 $O(n^{2})$ 肯定过不了。那就想比 $O(n^{2})$ 快的算法。

可行的有 $O(n)$ 或者 $O(n \log n)$。$O(n)$ 是线性的，就是只扫一遍，对于有横有竖的棋盘不好实现。考虑 $O(n \log n)$。

那 $O(n \log n)$ 有什么算法呢？

二分？

二分找出要消掉多少堵墙，看看到了每一条竖线要消掉多少条横线。

理解完上面的就差不多能做了，方向对了就只是时间问题。

---

下面是细节部分。

容易发现，对于一条横线，我们有绕过或者消除两种办法。当然最优是绕过。先看右端点，如果右端点在我们当前枚举的竖线右边的话，就是不能从右边绕过去。那左边只要看它的左端点是否为 $1$，不是的话就可以从 $1$ 处绕过去了。

那只需要存下左端点为 $1$ 的横线，如果右端点大于当前竖线就要消除了。

我们要走到这条竖线，那就还要消除这条竖线以前的竖线。

最后注意一下棋盘边界为 $10^{9}$，造一条 $10^{9}$ 处的竖线就能避免越界。

### 代码

```
#include <iostream>
#include <cmath>
#include <cstdio>
#include <algorithm>
#define LL long long
using namespace std;
const int N = 2e5 + 10;
const int INF = 0x3f3f3f3f;
int n, m;
struct node
{
	int h, l, r;
}p[N];
int k[N], need[N], cnt;
int find(int x)//找出第一个右边过不去的线  
{
	int l = 1, r = cnt + 1;
	while(l < r)
	{
		int mid = (l + r) >> 1;
		if(need[mid] < x)
		{
			l = mid + 1;
		}
		else
		{
			r = mid;
		}
	}
	int ans = cnt - l + 1;
	//当前算出来的l是下标，ans才是有多少个要消除的线  
	return ans;
}
signed main()
{
	cin >> n >> m;
	for(int i = 1; i <= n; i++)
	{
		cin >> k[i];
	}
	sort(k + 1, k + n + 1);
	k[++n] = 1000000000;//手动加边界 
	for(int i = 1; i <= m; i++)
	{
		cin >> p[i].l >> p[i].r >> p[i].h;
		//注意这里，错了调了好久
	}
	for(int i = 1; i <= m; i++)
	{
		if(p[i].l == 1)
		{
			need[++cnt] = p[i].r;
			//只留下能挡住车的 
		}
	}
	sort(need + 1, need + cnt + 1);//二分必须有序 
	int minn = 1000000000;
	for(int i = 1; i <= n; i++)
	{
		minn = min(minn, i - 1 + find(k[i]));
	}
	cout << minn << endl;
	return 0;
}
```

---

## 作者：lilong (赞：1)

注意到横着的障碍如果左端点不是 $1$ 那么是一定不用拆的（要么把挡在它下面的左端点是 $1$ 的障碍直接拆掉，要么拆掉若干个竖的障碍然后把左端点是 $1$ 的障碍绕掉，反正拆了也没用，左端点是 $1$ 的还会挡着）。那么对竖的障碍和**有效的横的障碍**分别按横坐标排序后，考虑二分答案，判定时如果当前已经能够拆完水平障碍就可以（除去能绕开的），否则花费 $1$ 次拆掉最靠左的竖的障碍，继续下去即可。

注意 $l=1,r=10^9$ 的情况，此时直接拆掉即可。


```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define N 500010
#define int long long
using namespace std;
int n,m,a[N],b[N],tot,mid,ans,sum;
bool ck(int x){
    for(int i=1,j=1;i<=n;i++){
        while(j<=m&&b[j]<a[i])j++;
        if(m-j+1<=x)return true;
        x--;
    }
    if(x>=0)return true;
    return false;
}
signed main(){
    int l,r,h,mid;
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    sort(a+1,a+n+1);
    for(int i=1;i<=m;i++){
        cin>>l>>r>>h;
        if(l==1&&r!=1e9)b[++tot]=r;
        else if(l==1&&r==1e9)sum++;
    }
    m=tot;
    sort(b+1,b+m+1);
    l=0,r=n+m;
    while(l<=r){
        mid=(l+r)/2;
        if(ck(mid))ans=mid,r=mid-1;
        else l=mid+1;
    }
    cout<<ans+sum;
    return 0;
}
```

---

## 作者：Gordon_Song (赞：1)

# 思路

因为横着的障碍不会相交，所以所有 $x1_i$ 不是 $1$ 的横障碍都毫无用处。 

因为竖着的障碍是整行禁止通行，所以删除的一定是排序后前 $i$ 小的障碍。当删除前 $i$ 小的障碍后，所有 $x2_j \leq x_i-1$ 的障碍都可以绕过去，所以删除前 $i$ 个后最小需删除的横障碍数量为 $ x_i \leq x2_j$ 的 $j$ 的个数。

# 实现方法

### step1

将 $x_i$ 从大到小排序

### step2

对于每个 $1 \leq i \leq n$ 的 $i$，用二分（你想的话可以用线段树）计算出比 $x_i$ 大的 $x2_i$ 的数量，加上 $i$ 后更新答案。


# 代码

```cpp
int n,m;
int a[1000001];
int x[1000001],p[1000001],len;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	for(int i=1,x,y,z;i<=m;i++){
		scanf("%d%d%d",&x,&y,&z);
		if(x==1){
			len++;
			p[len]=y;
		}
	}
	sort(p+1,p+1+len);sort(a+1,a+1+n);a[n+1]=1e9;
	int ans=1e9;
	for(int i=1,t;i<=n+1;i++){
		t=lower_bound(p+1,p+len+1,a[i])-p;
		ans=min(ans,i+len-t);
	}
	printf("%d\n",ans);
}
```


---

## 作者：AFO_Lzx (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF1044A)

### $\texttt{Description}$

有一个 $10^9 \times 10^9$ 的棋盘，一个国际象棋的车在位置 $(1,1)$ 上， 现在在这个棋盘上，一共有 $n$ 道竖着的墙和 $m$ 道横着的墙，竖的墙表示这一列的点都不能通过，横墙表示在给定的区间内的点不能通过。现在要去到第 $10^9$ 行，问最少要消除多少个点才能到达。

### $\texttt{Solution}$

先看数据范围，竟然有 $n,m \le 10^5$ 这么大，那么我们的时间复杂度只能是 $O(n)$ 或 $O(n \log n)$ 的。

$O(n)$ 是不可能的，但是 $O(n \log n)$ 还是能实现的。因为我们可以用二分来解决问题。所以这题其实就是一道贪心以及二分的题目。

因为需要二分，所以我们需要让数组具有单调性，即为排序。

我们只需要枚举每一个竖着的墙，然后用二分去寻找比 $x1_i$ 大的 $x2_i$ 的数量，设其为 $c$，$x1_i$ 为 $1$ 的数量为 $cnt$，则我们只需要用 $i+cnt-c$ 去更新答案即可。

### $\texttt{Code}$

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1e5 + 5;
const int inf = 1e18;
int n, m, a[N], b[N], ans = 1e18;

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	
	cin >> n >> m;
	
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	
	int cnt = 0;
	
	while (m--) {
		int x, y, z;
		cin >> x >> y >> z;		
		if (x == 1) b[++cnt] = y; // 存入 x = 1 时的 y
	}
	
	sort(a + 1, a + n + 1); // 排序
	a[n + 1] = 1e9; // 把 1e9 加入
	
	sort(b + 1, b + cnt + 1); // 把 b 数组排序
	
	for (int i = 1; i <= n + 1; i++) {
		int c = lower_bound(b + 1, b + cnt + 1, a[i]) - b; // 二分查找
		ans = min(ans, i + cnt - c); // 更新答案
	}
	
	cout << ans;
	return 0;
}
```

经过 $51$ 个测试点的检验，这个代码成功地 $\texttt{AC}$ 了。希望这篇题解能够对大家有帮助。

---

## 作者：liuyz11 (赞：0)

原比赛题解：https://www.cnblogs.com/nblyz2003/p/9907114.html

题意：在一个(10 ^ 9) * (10 ^ 9)棋盘的(1, 1)有一个车，需要走到最上面一行。现在有n个竖行障碍和m个横行障碍，竖行障碍会挡住所有从x[i]列到x[i] + 1列的路（两个竖行障碍不会在同一地方），横行障碍会挡住第x1[i]到x2[i]列从y[i]到y[i] + 1的路（两个横行障碍不会有任何接触），现在问你最少去掉多少障碍使得车能到达。

因为横行障碍不会相交，且竖行障碍都是整行禁止通行的，那么只要x1[i]不是1那么这个障碍i就一定不用删去，障碍i要删去仅当x2[i] >= x[j]都被删除（j为余下的最左边的竖行障碍。

因为竖行障碍是整行都禁止通行且起点再(1, 1)，那么如果删掉第i竖行障碍，所有x[j] < x[i] 的障碍j都要删掉，不然障碍i删掉和不删掉一样。

我们只要将a[i]排个序，记录所有x1[i] = 1的障碍i的右端x2[i]并排序。然后枚举i表示1～i的竖行障碍被删除，然后可以求得当前情况下要删掉的横行障碍（我用了二分）。

注：以上的最好手动模拟。

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
#define MAXN 100005
#define fi first
#define se second
#define SZ(x) ((int)x.size())
using namespace std;
typedef long long LL;
typedef vector<int> vi;
typedef pair<int, int> pii;
const int INF = 1e9;
const int p = 10000007;
//head by DYH

int a[MAXN], b[MAXN];

int main(){
    int n, m;
    scanf("%d%d", &n, &m);
    rep(i, 1, n) scanf("%d", &a[i]);
    sort(a + 1, a + n + 1);
    a[n + 1] = INF;
    int cnt = 0;
    rep(i, 1, m){
        int X0, X1, y;
        scanf("%d%d%d", &X0, &X1, &y);
        if(X0 == 1) b[++cnt] = X1;
    }
    sort(b + 1, b + cnt + 1);
    int ans = INF;
    rep(i, 1, n + 1){
        int id = lower_bound(b + 1, b + cnt + 1, a[i]) - b;
        ans = min(ans, i + cnt - id);
    }
    printf("%d\n", ans);
    return 0;
}
```

---

