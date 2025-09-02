# [GCJ 2019 #1B] Manhattan Crepe Cart

## 题目描述

曼哈顿有许多很棒的街头小吃摊，但毫无疑问，味道最棒的是 Code Jam 可丽饼车！

你想找到这辆小吃车，但你只知道它在某个街道交叉口。你认为来自曼哈顿各地的人们正朝着这个交叉口走去，因此你会尝试找出最多人正前往的那个交叉口。

在本题中，曼哈顿是一张规则的网格，坐标轴与罗盘方向对齐，每个坐标轴的取值范围为 $0$ 到 $\mathbf{Q}$（包含 $0$ 和 $\mathbf{Q}$）。东西向的街道对应于 $y = 0, y = 1, y = 2, \cdots, y = \mathbf{Q}$ 的网格线，南北向的街道对应于 $x = 0, x = 1, x = 2, \cdots, x = \mathbf{Q}$ 的网格线，人们只能沿着这些街道行走。网格线的交点（如 $(0, 0)$ 和 $(1, 2)$）即为街道交叉口。两个交叉口之间的最短距离是曼哈顿距离，即横向距离与纵向距离的绝对值之和。

你知道有 $\mathbf{P}$ 个人的位置，他们都站在交叉口上，并且你知道每个人当前前进的方向：北（$y$ 增大方向）、南（$y$ 减小方向）、东（$x$ 增大方向）或西（$x$ 减小方向）。如果某个人当前的移动方向在曼哈顿网格中是通往某个交叉口的最短路径之一，则认为此人正朝该交叉口前进。例如，如果某人位于 $(x_0, y_0)$ 并向北移动，则他们正朝所有 $y > y_0$ 的交叉口前进。

你认为可丽饼车就在最多人正前往的交叉口处。此外，你认为岛屿的更南部和更西部更有可能有可丽饼车，因此如果有多个这样的交叉口，你会选择 $x$ 坐标最小的那个，如果仍有多个，则选择 $y$ 坐标最小的那个。你会选择哪个交叉口？

## 说明/提示

**样例解释**

在样例 1 中，只有一个人，他从 $(5, 5)$ 向北移动。这意味着所有 $y \geqslant 6$ 的交叉口都是可丽饼车可能的位置。在这些位置中，选择 $x \geqslant 0$ 最小的，再选择 $y \geqslant 6$ 最小的。

在样例 2 中，有四个人都朝着 $(2, 5)$ 这个位置移动，没有其他位置有这么多人朝向。

在样例 3 中，八个人中有六个人都朝着 $(0, 4)$ 这个位置移动，没有其他位置有这么多人朝向。

**数据范围**

- $1 \leqslant \mathbf{T} \leqslant 100$。
- $1 \leqslant \mathbf{P} \leqslant 500$。
- $0 \leqslant \mathbf{X}_i \leqslant \mathbf{Q}$，对所有 $i$。
- $0 \leqslant \mathbf{Y}_i \leqslant \mathbf{Q}$，对所有 $i$。
- 对所有 $i$，如果 $\mathbf{X}_i = 0$，则 $\mathbf{D}_i \neq \text{W}$。
- 对所有 $i$，如果 $\mathbf{Y}_i = 0$，则 $\mathbf{D}_i \neq \text{S}$。
- 对所有 $i$，如果 $\mathbf{X}_i = \mathbf{Q}$，则 $\mathbf{D}_i \neq \text{E}$。
- 对所有 $i$，如果 $\mathbf{Y}_i = \mathbf{Q}$，则 $\mathbf{D}_i \neq \text{N}$。

**测试点 1（9 分，可见）**

- $\mathbf{Q} = 10$。

**测试点 2（18 分，隐藏）**

- $\mathbf{Q} = 10^5$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
1 10
5 5 N
4 10
2 4 N
2 6 S
1 5 E
3 5 W
8 10
0 2 S
0 3 N
0 3 N
0 4 N
0 5 S
0 5 S
0 8 S
1 5 W```

### 输出

```
Case #1: 0 6
Case #2: 2 5
Case #3: 0 4```

# 题解

## 作者：__CuSO4__ (赞：5)

## 题解

前置知识：差分。

不懂的可以戳这里->[OI-wiki 差分](https://oi-wiki.org/basic/prefix-sum/#%E5%B7%AE%E5%88%86)。

---

看到题，自然会想到用一个二维数组标记每个点的人数，

但 $ \mathbf{Q} $ 是 $1$ 到 $10^5$，$O(n^2)$ 直接做肯定不行。

注意到，一个人如果向北（$ y $ 坐标增大方向）走，那么在**所有的** $ x $ 坐标上，我们就把 $\mathbf{Y}_i$ 到 $\mathbf{Q}$ 的人数 $+1$。

所以只需要把 $ x $ 坐标与 $ y $ 坐标分开处理。

既然区间操作，就很容易想到差分。

于是正解来了：对于 $ x $ 坐标与 $ y $ 坐标都各自维护一个差分数组，最后分别找到最大的人数对应的坐标。

具体地，对于不同的操作，有如下处理方法：

1. N：把 $ y $ 坐标的 $\mathbf{Y}_i+1$ 到 $\mathbf{Q}$ 的人数 $+1$；
2. S：把 $ y $ 坐标的 $0$ 到 $\mathbf{Y}_i-1$ 的人数 $+1$；
3. E：把 $ x $ 坐标的 $\mathbf{X}_i+1$ 到 $\mathbf{Q}$ 的人数 $+1$；
4. W：把 $ x $ 坐标的 $0$ 到 $\mathbf{X}_i-1$ 的人数 $+1$。

仅需在差分数组上完成对应的操作即可。

---

Code:

``` cpp
#include <iostream>
#include <cstring>
using namespace std;

int T, X, Y, P, Q;
char D;
int xc[100005], yc[100005];

int main()
{
    cin >> T;
    for (int t = 1; t <= T; t++)
    {
        //多测，注意初始化
        memset(xc, 0, sizeof(xc));
        memset(yc, 0, sizeof(yc));
        cin >> P >> Q;
        for (int i = 1; i <= P; i++) 
        {
            int X, Y;
            char D;
            cin >> X >> Y >> D;
            //差分
            if (D == 'N')
                yc[Y + 1]++, yc[Q + 1]--;
            else if (D == 'S')
                yc[0]++, yc[Y]--;
            else if (D == 'E')
                xc[X + 1]++, xc[Q + 1]--;
            else if (D == 'W')
                xc[0]++, xc[X]--;
        }
        //max_x表示最大的人数对应的坐标
        //max_xc表示最大的人数
        int max_x = 0, max_xc = xc[0];
        for (int x = 1; x <= Q; x++)
        {
            xc[x] += xc[x - 1];
            if (xc[x] > max_xc) 
            {
                max_xc = xc[x];
                max_x = x;
            }
        }
        int max_y = 0, max_yc = yc[0];
        for (int y = 1; y <= Q; y++)
        {
            yc[y] += yc[y - 1];
            if (yc[y] > max_yc)
            {
                max_yc = yc[y];
                max_y = y;
            }
        }
        printf("Case #%d: %d %d\n", t, max_x, max_y);
    }
    return 0;
}
```

---

## 作者：Hkb150429 (赞：1)

## 题意

你知道有 $\mathbf{P}$ 个人的位置，他们都站在交叉口上，并且你知道每个人当前前进的方向：北（$y$ 增大方向）、南（$y$ 减小方向）、东（$x$ 增大方向）或西（$x$ 减小方向）。如果某个人当前的移动方向在曼哈顿网格中是通往某个交叉口的最短路径之一，则认为此人正朝该交叉口前进。例如，如果某人位于 $(x_0, y_0)$ 并向北移动，则他们正朝所有 $y > y_0$ 的交叉口前进。求最多人正前往的交叉口处。

## 思路

强烈建议看一下这一个[差分](https://oi-wiki.org/basic/prefix-sum/#%E5%B7%AE%E5%88%86)知识点以及[差分题单](https://www.luogu.com.cn/training/200)~

看到人数，我们就要想到只有区间才有不同人数，那么说到区间，我们会想到前缀和以及差分。

那么怎么查分呢，这就要说到我们的与众不同——方向，所以我们要分情况讨论。

若 $\mathbf{D}_i = \text{N}$，那么将 $\mathbf{Y}_i+1$ 至 $\mathbf{Q}$ 加上 $1$。$\mathbf{D}_i = \text{S}$ 反之。

若 $\mathbf{D}_i = \text{E}$，那么将 $\mathbf{X}_i+1$ 至 $\mathbf{Q}$ 加上 $1$。$\mathbf{D}_i = \text{W}$ 反之。

根据上述思路，就可以通过本题啦！

## AC code

为了防止抄袭，也让大家练一练差分，我就不放代码啦~

---

## 作者：Zjb13927701829 (赞：1)

# P13109 [Manhattan Crepe Cart](https://www.luogu.com.cn/problem/P13109) 题解
## 题目简化
有一张规则的 $\mathbf{Q \times Q}$ 的网格，每个坐标轴的取值范围为 $0$ 到 $\mathbf{Q}$（包含 $0$ 和 $\mathbf{Q}$）,网格线的交点即为街道交叉口。有 $\mathbf{P}$ 个人在网格上，他们正在朝着北（$y$ 增大方向）、南（$y$ 减小方向）、东（$x$ 增大方向）或西（$x$ 减小方向）前进。\
例如：如果某人位于 $ (x_0,y_0) $ 并向北移动，则他正朝所有 $y>y_0$ 的交叉口前进。

我们要求的是人最多且 $x$ 坐标最小、$y$ 坐标也最小的交叉口的 $x$ 坐标和 $y$ 坐标。
## 解题思路
看完题目题目中 $\mathbf{Q}$ 的最大值是 $10^5$，如果用 for 循环累加的话 $O(\mathbf{Q}^2)$ 的时间复杂度肯定会超时。所以就要运用到本题最关键的知识点——差分来解决。

[不懂差分的可以戳这里](https://oi-wiki.org/basic/prefix-sum/#%E5%B7%AE%E5%88%86)（感谢大佬提供的链接）。

既然本题需要区间操作，肯定少不了差分。我们可以用两个数组 $x$ 和 $y$ 进行差分，最后分别找到两个数组人数最多的下标，具体操作如下（同样的方法，步骤会也相似，没有盗用）：
1. 方向为`N`，将 $y$ 坐标 $\mathbf{Y}_i +1$ 到 $\mathbf{Q}$ 的区间人数 $+1$；
2. 方向为`S`，将 $y$ 坐标 $0$ 到 $\mathbf{Y}_i -1$ 的区间人数 $+1$；
3. 方向为`E`，将 $x$ 坐标 $\mathbf{X}_i +1$ 到 $\mathbf{Q}$ 的区间人数 $+1$；
4. 方向为`W`，将 $x$ 坐标 $0$ 到 $\mathbf{X}_i -1$ 的区间人数 $+1$。

在差分数组上进行相应的操作即可。

为了维护社区安全~~其实是不想~~，所以代码就不放了，希望大家能独立完成本题。

---

## 作者：IkillDream (赞：1)

# P13109 题解

## 思路

我们只需要使用前缀和加差分就可以轻松过掉此题。

首先我们使用差分数组记录每个方向影响的行列范围，$N\div S$ 影响 $y$ 坐标，$E\div W$ 影响 $x$ 坐标。

最后再作一便前缀和计算，确定最大值对应的 $x$ 和 $y$。

就可以 AC 这题了。

## [AC](https://www.luogu.com.cn/record/225504680) 代码

```c++
#include<bits/stdc++.h>
using namespace std;
int dx[100005],dy[100005];
int main(){
	int t;
	cin>>t;
	for(int k=1;k<=t;k++){
		int p,q;
		cin>>p>>q;
		memset(dx,0,sizeof(dx));
		memset(dy,0,sizeof(dy));
		for(int i=0;i<p;i++){
			int x,y;
			char d;
			cin>>x>>y>>d;
			if(d=='N') dy[y+1]++;
			else if(d=='S') dy[0]++,dy[y]--;
			else if(d=='E') dx[x+1]++;
			else if(d=='W') dx[0]++,dx[x]--;
		}
		int mx=0,my=0,bx=0,by=0,cx=0,cy=0;
		for(int i=0;i<=q;i++){
			cx+=dx[i];
			if(cx>mx)mx=cx,bx=i;
		}
		for(int i=0;i<=q;i++){
			cy+=dy[i];
			if(cy>my)my=cy,by=i;
		}
		cout<<"Case #"<<k<<": "<<bx<<" "<<by<<endl;
	}
	return 0;
}
```

## 后记

前缀和，一种仅需 $O(n)$ 即可求出在一个数列中子序列的和，例如 [P8218](https://www.luogu.com.cn/problem/P8218) 这题，大家最先想到的方法大概长下面这个样子：

```c++
#include<bits/stdc++.h>
using namespace std;
int a[100005];
int main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    int q;
    cin>>q;
    while(q--){
        int l,r;
        long long sum=0;
        cin>>l>>r;
        for(int i=l;i<=r;i++) sum+=a[i];
        cout<<sum<<endl;
    }
    return 0;
}
```

但是这段代码者能拿 $40$ 分，因为观察数据范围可以发现，上面的代码的时间复杂度是 $O(n^2)$ 但题目中 $n$，的范围是 $1 \le n \le 10^5$，$10^5\times10^5=10^{10}$ 这已经严重超时了，所以我们得想办法优化，既然我们可以循环暴力找，那么我们是不是可以先统计一下前 $n$ 位的和，然后再减去前 $l$ 位的和呢，现在我们就来验证一下：

```
6
4 3 2 1 3 5
1
2 5
```

首先我们先将前 $n$ 位的数值相加并存到一个数组里，```4 7 9 10 13 18```,现在数组里就是前 $n$ 位的数字之和了，现在将 $l$ 和 $r$ 套进，刚刚的数组中，发现，$13-7=5$，我们再用暴力代码测试一下算出来的结果，$3+2+1+3=9$，发现结果不对啊，再看一下，不难发现，我们要求的是从 $l$ 到 $r$ 的值，但我们刚刚算出的却是前 $r$ 项的值 $-$ 前 $l$ 项的值，所以多减了一个第 $l$ 项的值，推倒出正确的前缀和公式为 `sum=a[r]-a[l-1]` 就是答案，最后附上代码：

```c++
#include<bits/stdc++.h>
using namespace std;
int a[100005];
int main(){
    int n,sum=0;
    cin>>n;
    for(int i=1;i<=n;i++){
        int k;
        cin>>k;
        sum+=k;
        a[i]=sum;
    }
    int q;
    cin>>q;
    while(q--){
        int l,r;
        long long sum=0;
        cin>>l>>r;
        sum=a[r]-a[l-1];
        cout<<sum<<endl;
    }
    return 0;
}
```
题解制作不容易如果觉得我的题解写的好的话可以点个赞吗 qwq。

题解可以抄，但是你要学会哦！

祝大家 CSP-J/S 初赛，会的都对，蒙的全对。

---

## 作者：zhongjunnan561234 (赞：0)

# 题意
一共有 $P$ 个人的位置，都站在交叉口上，而每个人的移动方向有：北（$y$ 增大方向）、南（$y$ 减小方向）、东（$x$ 增大方向）或西（$x$ 减小方向）。如果某个人当前的移动方向在曼哈顿网格中是通往某个交叉口的最短路径之一，则认为此人正朝该交叉口前进。例如，如果某人位于 （$x_0$，$y_0$） 并向北移动，则他们正朝所有 $y>y_0$ 的交叉口前进。并求最多人正前往的交叉口处。
# 思路
这道题可以用 $x$ 和 $y$ 进行[差分](https://oi-wiki.org/basic/prefix-sum/#%E5%B7%AE%E5%88%86)来写，具体步骤：

1. 方向为 `N`：将 $y$ 坐标 $Y_i+1$ 到 $Q$ 的区间人数 $+1$。
2. 方向为 `S`：将 $y$ 坐标 $0$ 到 $Y_i−1$ 的区间人数 $+1$。
3. 方向为 `E`：将 $x$ 坐标 $X_i+1$ 到 $Q$ 的区间人数 $+1$。
4. 方向为 `W`：将 $x$ 坐标 $0$ 到 $X_i−1$ 的区间人数 $+1$。
# AC Code
为了维护社区安全，所以代码就不放了，希望大家能独立完成本题，并练一练差分。

---

## 作者：_aszxqw_ (赞：0)

一道[差分](https://oi-wiki.org/basic/prefix-sum/)的题。直接用两差分数组维护东南西北即可。最后用前缀和计算出 $x$ 和 $y$ 覆盖人最多的点就可以了。    
具体操作如下：    
- 方向为 `N`，将 $y$ 坐标 $Y_i+1$ 到 $Q$ 的区间人数 $+1$      
- 方向为 `S`，将 $y$ 坐标 $0$ 到 $Y_i−1$ 的区间人数 $+1$     
- 方向为 `E`，将 $x$ 坐标 $X_i+1$ 到 $Q$ 的区间人数 $+1$    
- 方向为 `W`，将 $x$ 坐标 $0$ 到 $X_i-1$ 的区间人数 $+1$
### AC 代码
```
#include <bits/stdc++.h>
using namespace std;
const int K = 1e5+5;
int main() {
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        int p, q;
        cin >> p >> q;
        int X[p], Y[p];
        char d[p];
        for (int i = 0; i < p; i++) 
            cin >> X[i] >> Y[i] >> d[i];
        int xc[K + 2] = {0}; 
        for (int i = 0; i < p; i++) {
            if (d[i] == 'E') {
                xc[X[i] + 1]++;
                xc[q + 1]--;
            } else if (d[i] == 'W') {
                xc[0]++;
                xc[X[i]]--;
            }
        }
        int xp[K + 1] = {0};
        int ans = 0;
        int mx = -1;
        int mxx = 0;
        for (int x = 0; x <= q; x++) {
            ans += xc[x];
            xp[x] = ans;
            if (ans > mx) {
                mx = ans;
                mxx = x;
            }
        }
        int yc[K + 2] = {0};
        for (int i = 0; i < p; i++) {
            if (d[i] == 'N') {
                yc[Y[i] + 1]++;
                yc[q + 1]--;
            } else if (d[i] == 'S') {
                yc[0]++;
                yc[Y[i]]--;
            }
        }
        int yp[K + 1] = {0};
        int cnt = 0;
        int my = -1;
        int mxy = 0;
        for (int y = 0; y <= q; y++) {
            cnt += yc[y];
            yp[y] = cnt;
            if (cnt > my) {
                my = cnt;
                mxy = y;
            }
        }
        cout << "Case #" << t << ": " << mxx << " " << mxy << '\n';
        }
    return 0;
}
```

---

## 作者：__Harry__Potter__ (赞：0)

这里先给大家普及一下这道题的前置知识：差分。

差分，就是用一个数组存储实际数组中当前数与前一个数的差，也就是 $c[i]=a[i]-a[i-1]$。

它可以让区间修改的时间复杂度降到 $O(1)$。

比如你想让 $a[l]$~$a[r]$ 增加 $x$，只需要让 $c[l]$ 加 $x$，$c[r-1]$ 减 $x$。

但是会让求值的复杂度变成 $O(n)$，需要求差分数租的前缀和。

有了这个前置知识，这道题就会变得非常简单。

只需要给横坐标和纵坐标各设置一个差分数组，每次输入的时候维护一下。

输入完之后再求一下分别的最小值和最大值就行。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,t,p,q,x,y,sumx,sumy,maxx,maxy,cfx[111111],cfy[111111];
char c;
int main(){
	cin>>n;
	for(int t=1;t<=n;t++){
		cin>>p>>q;
		memset(cfx,0,sizeof(cfx));
		memset(cfy,0,sizeof(cfy));
		while(p--){
			cin>>x>>y>>c;
			if(c=='N') cfy[y+1]++;
			if(c=='S'){
				cfy[0]++;
				cfy[y]--;	
			}if(c=='E') cfx[x+1]++;
			if(c=='W'){
				cfx[0]++;
				cfx[x]--;
			}
		}x=y=sumx=sumy=maxx=maxy=0;
		for(int i=0;i<=q;i++){
			sumx+=cfx[i];
			if(sumx>maxx){
				maxx=sumx;
				x=i;
			}
		}for(int i=0;i<=q;i++){
			sumy+=cfy[i];
			if(sumy>maxy){
				maxy=sumy;
				y=i;
			}
		}printf("Case #%lld: %lld %lld\n",t,x,y);
	}
	return 0;
}
```

---

## 作者：Rainbow_SYX (赞：0)

## 思路
看完题后很容易想到使用差分来做，很简单，维护 $xx$，$yy$ 两个差分数组来统计每一个十字路口前往人数，最后遍历一遍，找到两个数组的最大值就行了。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int xx[100005],yy[100005];
int T;
int p,q,x,y;
char di;
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>T;
	for(int tT=1;tT<=T;tT++)
	{
		cin>>p>>q;
		memset(xx,0,sizeof(xx));
		memset(yy,0,sizeof(yy));
		for(int i=1;i<=p;i++)
		{
			cin>>x>>y>>di;
			if(di=='N')
			{
				yy[y+1]++;
				yy[q+1]--;
			}
			if(di=='S')
			{
				yy[0]++;
				yy[y]--;
			}
			if(di=='E')
			{
				xx[x+1]++;
				xx[q+1]--;
			}
			if(di=='W')
			{
				xx[0]++;
				xx[x]--;
			}
		} 
		int maxx=0,maxtx=xx[0];
		for(int i=1;i<=q;i++)
		{
			xx[i]=xx[i]+xx[i-1];
			if(xx[i]>maxtx)
			{
				maxtx=xx[i];
				maxx=i;
			}
		}
		int maxy=0,maxty=yy[0];
		for(int i=1;i<=q;i++)
		{
			yy[i]=yy[i]+yy[i-1];
			if(yy[i]>maxty)
			{
				maxty=yy[i];
				maxy=i;
			}
		}
		cout<<"Case #"<<tT<<": "<<maxx<<" "<<maxy<<"\n";
	}
	return 0;
}
```

---

