# Dot

## 题目描述

Anton and Dasha like to play different games during breaks on checkered paper. By the 11th grade they managed to play all the games of this type and asked Vova the programmer to come up with a new game. Vova suggested to them to play a game under the code name "dot" with the following rules:

- On the checkered paper a coordinate system is drawn. A dot is initially put in the position $ (x,y) $ .
- A move is shifting a dot to one of the pre-selected vectors. Also each player can once per game symmetrically reflect a dot relatively to the line $ y=x $ .
- Anton and Dasha take turns. Anton goes first.
- The player after whose move the distance from the dot to the coordinates' origin exceeds $ d $ , loses.

Help them to determine the winner.

## 说明/提示

In the first test, Anton goes to the vector (1;2), and Dasha loses. In the second test Dasha with her first move shifts the dot so that its coordinates are (2;3), and Anton loses, as he has the only possible move — to reflect relatively to the line $ y=x $ . Dasha will respond to it with the same move and return the dot in position (2;3).

## 样例 #1

### 输入

```
0 0 2 3
1 1
1 2
```

### 输出

```
Anton```

## 样例 #2

### 输入

```
0 0 2 4
1 1
1 2
```

### 输出

```
Dasha```

# 题解

## 作者：DengDuck (赞：3)

诈骗题，我们发现难点是什么？这个反射到对称点的操作破坏了美好的性质，如果不用发射的话，由于向量都不会使横纵坐标下降，这个坐标系可以转换成一个有向无环图啊！


所以破案了，反射操作没用，狗都不用，因为反射之后距离不变，不能一击制胜，要是你用了之后到了必胜点，对面可以反射回来，要是不是必胜点，换个地方寄罢了。

所以狗都不用反射，这题直接利用向量操作。结合一些简单的博弈论知识就行了。

对于我当前所在的点，要是我走了之后可以到达一个先手必输的点，我就是赢的，然后记忆化搜索就行了。

时间复杂度为 $\mathcal O(nd^2)$ 级别的。

代码实现，我和另外一篇题解的代码不知道为什么写的惊人的相似！想必这就是缘分吧！
```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N=2005;
const LL M=1005;
LL x,y,n,d,a[N],b[N],f[N][N];
bool dfs(LL x,LL y)
{
	if(d*d<x*x+y*y)
	{
		f[x+M][y+M]=1;
		return f[x+M][y+M];
	}
	if(f[x+M][y+M]!=-1)return f[x+M][y+M];
	for(int i=1;i<=n;i++)
	{
		if(!dfs(x+a[i],y+b[i]))
			f[x+M][y+M]=1;
	}
	if(f[x+M][y+M]==-1)f[x+M][y+M]=0;
	return f[x+M][y+M];
}
int main()
{
	memset(f,-1,sizeof(f));
	scanf("%lld%lld%lld%lld",&x,&y,&n,&d);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld%lld",&a[i],&b[i]);
	}
	if(dfs(x,y))puts("Anton");
	else puts("Dasha");
}
```

---

## 作者：ttq012 (赞：3)

水的博弈论。

容易发现，对称反射一个点到原点的距离和原来一样，且对手还可以重新对称回来，所以对称操作是没有用的。

然后发现数据范围很小，直接 dfs 搜索即可。

```cpp
#include <bits/stdc++.h>

using namespace std;

int n, m, x, y;
int f[2333][2333];
int xx[232333], yy[232323];

inline double get_dist(int x, int y) {
    return sqrt(x * x + y * y);
}

bool dfs(int x, int y) {
    if (get_dist(x, y) > m)
        return f[x + 500][y + 500] = true;
    if (f[x + 500][y + 500])
        return f[x + 500][y + 500];
    for (int i = 1; i <= n; i ++)
        if (!dfs(x + xx[i], y + yy[i]))
            return f[x + 500][y + 500] = true;
    return f[x + 500][y + 500] = false;
}

signed main() {
    cin >> x >> y >> n >> m;
    for (int i = 1; i <= n; i ++)
        cin >> xx[i] >> yy[i];
    if (dfs(x, y))
        cout << "Anton\n";
    else
        cout << "Dasha\n";
    return 0;
}

```


---

