# X-Sum

## 题目描述

Timur's grandfather gifted him a chessboard to practice his chess skills. This chessboard is a grid $ a $ with $ n $ rows and $ m $ columns with each cell having a non-negative integer written on it.

Timur's challenge is to place a bishop on the board such that the sum of all cells attacked by the bishop is maximal. The bishop attacks in all directions diagonally, and there is no limit to the distance which the bishop can attack. Note that the cell on which the bishop is placed is also considered attacked. Help him find the maximal sum he can get.

## 说明/提示

For the first test case here the best sum is achieved by the bishop being in this position:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1676D/ef38eda1ec7208a8243b8f6ac83d0d9df8a29fbb.png)

## 样例 #1

### 输入

```
4
4 4
1 2 2 1
2 4 2 4
2 2 3 1
2 4 2 4
2 1
1
0
3 3
1 1 1
1 1 1
1 1 1
3 3
0 1 1
1 0 1
1 1 0```

### 输出

```
20
1
5
3```

# 题解

## 作者：5k_sync_closer (赞：5)

# 题意
有一个 $n×m$ 的国际象棋盘 $a$，$(i,j)$ 上有一个非负整数 $a_{ij}$。

你要在上面放一个象，问它能攻击到的点上的非负整数和最大是多少。

（象走斜线，无距离限制）
# 思路
直接模拟复杂度达到 $O(n^3)$，不太行。

考虑预处理出每条斜线上的点上的非负整数和。

观察得到，左下-右上斜线上的点 $i+j$ 相等，左上-右下斜线上的点 $i-j$ 相等。

（实际上可以把左下-右上斜线看作 $y=-x+b$，
把左上-右下斜线看作 $y=x+b$）

于是计算每个点对它所在斜线的贡献即可。
# 代码
```cpp
#include <cstdio>
#include <cstring>
int T, n, m, s, a[250][250], l[550], r[550];
int main()
{
    scanf("%d", &T);
    while(T--)
    {
        memset(l, 0, sizeof l);
        memset(r, 0, sizeof r);
        scanf("%d%d", &n, &m);s = 0;
        for(int i = 1;i <= n;++i)
            for(int j = 1;j <= m;++j)
                scanf("%d", &a[i][j]), l[i + j] += a[i][j], r[i - j + m] += a[i][j];
        for(int i = 1, t;i <= n;++i)
            for(int j = 1;j <= m;++j)
                if((t = l[i + j] + r[i - j + m] - a[i][j]) > s) s = t;
        printf("%d\n", s);
    }
    return 0;
}
```


---

## 作者：喵仔牛奶 (赞：3)

模拟即可。

需要注意的是，需要特判象所在的那一个只能算一次。

```
#include <bits/stdc++.h>
using namespace std;
const int N = 405;
int n, m, ans, a[N][N];
int solve() {
	cin >> n >> m;
	for (int i = 1; i <= n; i ++)
		for (int j = 1; j <= m; j ++)
			cin >> a[i][j];
	for (int i = 1; i <= n; i ++)
		for (int j = 1; j <= m; j ++) {
			int sum = 0;
			for (int k = 1; k <= n; k ++) {
				int pos = abs(i - k); // 由于是斜线，行差和列差是一样的
				if (j + pos <= m) sum += a[k][j + pos];
				if (j - pos >= 1 && pos) sum += a[k][j - pos]; // 特判 pos != 0
			}
			ans = max(ans, sum);
		}
	cout << ans << '\n';
	return 0;
}
int main() {
	int t;
	cin >> t;
	while (t --)
		ans = 0, solve(); // t组数据
	return 0;
}
```


---

## 作者：Rosemary_dream (赞：2)

### 这题下过国际象棋的可以A了

题意就是给定 $T$ 次询问，每次询问都会给出一个 $n×m$ 的一个棋盘，棋盘每个格子有一个权值，现在要你在棋盘上放一个象(攻击范围是无线长的斜线)，问你把它放在哪才能使它的攻击到的格子的权值和最大。

我们都知道。

这题直接模拟是 $O(n^3)$ 的复杂度，~~如果你的评测机不是天河二号~~基本凉凉。

所以我们可以在输入时做个手脚，进行一个预处理.

#### 像这样：

```cpp
for(register int i=1;i<=n;i++){
	for(register int j=1;j<=m;j++){
		scanf("%lld",&p[i][j]);
		L[i+j]+=p[i][j];
		R[i-j+m]+=p[i][j];
	}
}
```

###  为什么可以这样处理呢？

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1676D/ef38eda1ec7208a8243b8f6ac83d0d9df8a29fbb.png)

从图中可得，当这个象在 $p[3][3]$ 这个格点时，他所攻击到的格点是：     $p[1]p[1],p[2]p[2],p[3]p[3],
p[4]p[4]$ 和 $p[2]p[4],p[4]p[2]$ 

这么几个格点，有什么共同点，不同点？（为什么我要用“和”隔开前后两部分？）

不难看出，下面这张图中的射线所涉及的格点是 $p[2]p[4],p[3]p[3],p[4]p[2]$ 

![](https://cdn.luogu.com.cn/upload/image_hosting/5pqwnj5y.png)

他们所在的斜线的所有格点两坐标的和都怎么了？

都相同。

所以我们把它们加起来，存进一个数组里，如： $L[6]$ 。

这代表着我们无论把象放在这条斜线上的哪一个格点里，我们都只需读取  $L[i+j]$  就可以了。

而另一条斜线呢？

![](https://cdn.luogu.com.cn/upload/image_hosting/4gx0fazo.png)

它通过了  $p[1][1],p[2][2],p[3][3],
p[4][4]$  这几个格点，那么如何处理留给读者自己思考。

进行预处理后，就可以用  $O(n^2)$  时间来找出最优解，时间是足够的。

### $ Code: $
```cpp
#include<cstdio>
#include<cstring>
long long ans=0;
long long n,m,t,x,y;
long long p[300][300];
long long L[600],R[600];
signed main()
{
    scanf("%lld",&t);
    while(t--){
	ans=0;
	memset(L,0,sizeof(L));
	memset(R,0,sizeof(R));
	scanf("%lld %lld",&n,&m);
	for(register int i=1;i<=n;i++){
	    for(register int j=1;j<=m;j++){
		scanf("%lld",&p[i][j]);
		L[i+j]+=p[i][j];
		R[i-j+m]+=p[i][j];
		}
	}
	for(register int i=1;i<=n;i++){
	    for(register int j=1;j<=m;j++){
		if(ans<L[i+j]+R[i-j+m]-p[i][j]){
		    ans=L[i+j]+R[i-j+m]-p[i][j];
		}
            }
        }
	printf("%lld\n",ans);
    }
    return 0;
}
```
$End$

---

## 作者：Coros_Trusds (赞：2)

# 题目大意

有一个 $n\times m$ 的国际象棋盘 $a$，$(i,j)$ 上有一个非负整数 $a[i,j]$。

你要在上面放一个象，问它能攻击到的点上的非负整数和最大是多少。象走斜线，无距离限制。

注意：象所在的点也是它能攻击到的点。

$n,m\le 200$。

# 题目分析

注意到 $n,m$ 均不超过 $200$，所以直接考虑暴力解决问题。

枚举象在 $(i,j)$ 时的攻击值，在所有之中取最小即可。

观察：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1676D/ef38eda1ec7208a8243b8f6ac83d0d9df8a29fbb.png)

我们先算上 $a[i,j]$ 位置的值，然后将整个棋盘分为四个部分：左上、左下、右上和右下。

于是维护两个指针加减来模拟过程即可。

---------

各位可以思考思考 $n,m\le 5000$ 时怎么做。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
 
const int N = 205;
int n,m;
int a[N][N];
inline void solve() {
    cin >> n >> m;
    for (register int i = 1;i <= n; ++ i) {
        for (register int j = 1;j <= m; ++ j) {
            cin >> a[i][j];
        }
    }
    long long ans = 0;
    for (register int i = 1;i <= n; ++ i) {
        for (register int j = 1;j <= m; ++ j) {
            long long res = a[i][j];
            int ta = i - 1,tb = j - 1;
            while (ta >= 1 && tb >= 1) {
                res += a[ta][tb];
                ta --,tb --;
            }
            ta = i + 1,tb = j - 1;
            while (ta <= n && tb >= 1) {
                res += a[ta][tb];
                ta ++,tb --;
            }
            ta = i - 1,tb = j + 1;
            while (ta >= 1 && tb <= m) {
                res += a[ta][tb];
                ta --,tb ++;
            }
            ta = i + 1,tb = j + 1;
            while (ta <= n && tb <= m) {
                res += a[ta][tb];
                ta ++,tb ++;
            }
            ans = max(ans,res);
        }
    }
    cout << ans << "\n";
}
int main(void) {
    int T;
    cin >> T;
    while (T --) {
        solve();
    }
 
    return 0;
}
```

---

## 作者：Mr__Cat (赞：1)

### 题目描述 ###
给一个 $n \times m$ 的棋盘，并且 $(i,j)$ 位置上有 $q_{i,j}$ 这样一个数字（非负整数），我们放一个象在上面（国际象棋中的象只走斜线），问最多可取的数字和为多少？


------------
### 思路 ###

看完题目的第一个想法——枚举，枚举象的位置，并在之前计算好前缀和。当然，要用到 map。最后计算每个点对它所在斜线的贡献好像就可以了！！！


------------


### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[101][101];
int main(){
    int t;
    cin>>t;
    while(t--){
        int n,m,ans=0;;
        cin>>n>>m;
        map<int,int> l,r;
        //(-x)+y可能是负数，这里使用映射
        //如果把每个r的值加上m也可以
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                cin>>a[i][j];
                l[i+j]+=a[i][j];
                r[i-j]+=a[i][j];
                //计算前缀和
            }
        }
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                //枚举象的位置
                ans=max(ans,l[i+j]+r[i-j]-a[i][j]);
                //计算贡献，取max
        cout<<ans<<'\n';
    }
}
```


---

## 作者：WilliamFranklin (赞：1)

这道题还是很简单的，毕竟是一道 $Div.4$ 的。

### 主要思路

这道题其实就是求所有点中以哪个点为中心的对角线上的值的和与斜对角线上的值的和的和的最大值，如题，已有明确说明。

那么我们是不是可以先求出每个点以它为中心的对角线的值的和，存入一个数组 $a$，再求出斜对角线上的值的和，存入另一个数组 $b$，最后求相对应的两个数组中的值，就可以了。

然后我们发现：再同一个对角线上的 $a$ 值发现是相等的，斜对角线也一样，那么程序就好写了。

上代码。

### AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[205][205];
long long x1[210][210], x2[210][210];
int main(){
	int t;
	cin >> t;
	while(t--) {
		int n, m;
		cin >> n >> m;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				cin >> a[i][j];
			}
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				x1[i][j] = x1[i - 1][j - 1] + a[i][j];
			}
		}
		for (int i = n - 1; i >= 1; i--) {
			for (int j = m - 1; j >= 1; j--) {
				x1[i][j] = x1[i + 1][j + 1];
			}
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				x2[i][j] = x2[i - 1][j + 1] + a[i][j];
			}
		}
		for (int i = n - 1; i >= 1; i--) {
			for (int j = 2; j <= m; j++) {
				x2[i][j] = x2[i + 1][j - 1];
			}
		}
		long long ans = 0;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				ans = max(ans, x1[i][j] + x2[i][j] - a[i][j]);
				x1[i][j] = x2[i][j] = 0;
				a[i][j] = 0;
			}
		}
		cout << ans << endl; 
	}
}
```

可能有些讲的不详细的地方，请大家指出，谢谢！

---

## 作者：Engulf (赞：1)

这题中的“主教”其实对应国际象棋中的“象”，是往四面八方走斜线的。

$n,m\le200$，枚举主教的起始位置计算最大值。


```cpp
// author: TMJYH09
// create time: 2022/05/10 22:59:37
#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

int a[205][205];
int n,m;

int calc(int x,int y){
    int dx[]={-1,1,-1,1};
    int dy[]={-1,1,1,-1};
    int ans=a[x][y];
    for(int k=0;k<4;k++){
        int i=x,j=y;
        while(i>=1&&i<=n&&j>=1&&j<=m){
            if(i!=x&&j!=y)ans+=a[i][j];
            i+=dx[k];j+=dy[k];
        }
    }
    return ans;
}

void solve(){
    cin>>n>>m;
    int ans=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>a[i][j];
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            ans=max(ans,calc(i,j));
        }
    }
    cout<<ans<<endl;
}

int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int _;cin>>_;while(_--)solve();
    return 0;
}
```

---

## 作者：FReQuenter (赞：0)

## 思路

直接模拟复杂度达到 $O(n^3)$ ，显然会超时。现在考虑优化：

由于象攻击的是斜线，我们可以抓住斜线上每一个点坐标的性质：要么是 $\{x+1,y-1\}$ （向左上方）要么是 $\{(-x)-1,y+1\}$ （向右上方）。抓住这两个性质以及由于象的攻击距离无限，我们可以计算每条斜线的和，在用坐标映射（一条斜线上每个点坐标和不变）就可以形成前缀和。这样就可以 $O(N^2)$ 求解啦！

## 代码

```cpp
#include<iostream>
#include<cstring>
#include<map>
using namespace std;
int a[205][205];
int main(){
    int t;
    cin>>t;
    while(t--){
        int n,m,ans=0;;
        cin>>n>>m;
        map<int,int> l,r;
        //(-x)+y可能是负数，这里使用映射
        //如果把每个r的值加上m也可以
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                cin>>a[i][j];
                l[i+j]+=a[i][j];
                r[i-j]+=a[i][j];
                //计算前缀和
            }
        }
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                //枚举象的位置
                ans=max(ans,l[i+j]+r[i-j]-a[i][j]);
                //计算贡献，取max
        cout<<ans<<'\n';
    }
}
```

---

## 作者：Otue (赞：0)

## 思路
其实直接暴力就可以了。

枚举象放在哪个位置，再暴力计算斜线上的数值即可。

斜线上的数值可以分为 $5$ 个部分：左上，右上，左下，右下，当前这个格子。

$5$ 个部分分别计算即可，简单的模拟题。
## 代码
VP 时的代码，所以巨丑。
```c++
#include <bits/stdc++.h>
using namespace std;

int t, n, m, a[205][205];

int main() {
	cin >> t;
	while (t--) {
		cin >> n >> m;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				cin >> a[i][j];
			}
		}
		int maxn = -2e9;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				int kx = i, ky = j;
				int res = 0;kx--, ky--;
				while (kx >= 1 && ky >= 1) {   //左上
					
					res += a[kx][ky];kx--, ky--;
				}
				kx = i, ky = j;kx++, ky++;
				while (kx <= n && ky <= m) {  //右下
					
					res += a[kx][ky];kx++, ky++;
				}
				kx = i, ky = j;kx--, ky++;
				while (kx >= 1 && ky <= m) {  
					
					res += a[kx][ky];kx--, ky++;
				}
				kx = i, ky = j;kx++, ky--;
				while (kx <= n && ky >= 1) {
					
					res += a[kx][ky];kx++, ky--;
				}
				res += a[i][j];  //自己
				maxn = max(maxn, res);
			}
		}
		cout << maxn << endl;
	}
}
```

---

## 作者：落花月朦胧 (赞：0)

# 题意

给出一个有权值的棋盘， 现在要求你选定一个象的位置， 使象可以攻击的点的权值和最大。

象的攻击方法是斜着走。

# 解

看到数据范围这么小， 可以想到用暴力， 每个点都计算可能到达的地方的权值和。

至于计算权值和，四个方向模拟一下就可以了。

```cpp
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
constexpr int inf = INT_MAX;
constexpr i64 lnf = LONG_LONG_MAX;
constexpr int N = 210;
constexpr int dx[] = {1, -1},
			  dy[] = {1, -1};

int a[N][N];
void solve() {
	memset(a, 0, sizeof a);
	int n, m;
	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> a[i][j];
		}
	}	
	function<int(int, int)> dfs = [&](int x, int y) {
		int X = x, Y = y, ans = 0;
		while (X >= 0 && Y >= 0) {
			ans += a[X][Y];	
			X--, Y--;
		}
		X = x, Y = y;
		while (X >= 0 && Y < m) {
			X--, Y++;
			if (X >= 0 && Y < m)
				ans += a[X][Y];
		}
		X = x, Y = y;
		while (X < n && Y >= 0) {
			X++, Y--;
			if (X < n && Y >= 0)
				ans += a[X][Y];
		}
		X = x, Y = y;
		while (X < n && Y < m) {
			X++, Y++;
			if (X < n && Y < m)
				ans += a[X][Y];
		}
		return ans;
	};

	int ans = -inf;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			ans = max(ans, dfs(i, j));
		}
	}
	cout << ans << endl;
	
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T;
	cin >> T;
	while (T--) {
		solve();
	}

	return 0;
}
```

---

## 作者：cyrxdzj (赞：0)

### 一、思路

这道题可以枚举所有点，然后暴力计算。

真的没什么好讲的。

### 二、代码

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int t;
int n,m;
int a[205][205];
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				scanf("%d",&a[i][j]);
			}
		}
		long long ans=0;
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)//枚举每个点
			{
				long long temp=0;
				for(int x=i,y=j;x>=1&&y>=1;x--,y--)//左上方以及自己
				{
					temp+=a[x][y];
				}
				for(int x=i+1,y=j+1;x<=n&&y<=m;x++,y++)//右下方
				{
					temp+=a[x][y];
				}
				for(int x=i-1,y=j+1;x>=1&&y<=m;x--,y++)//右上方
				{
					temp+=a[x][y];
				}
				for(int x=i+1,y=j-1;x<=n&&y>=1;x++,y--)//左下方
				{
					temp+=a[x][y];
				}
				ans=max(ans,temp);
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}

```


---

## 作者：ttq012 (赞：0)

**Solution**

由于范围很小，所以可以直接暴力。

我们枚举任意的一个坐标 $(i, j)$，然后枚举这个坐标的左上方，右上方，左下方，右下方四条对角线的大于 $0$ 的值，最后加上当前坐标的值即可。

时间复杂度 $\mathcal O(n\times m\times (n+m))$。

**AC Code**

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <unordered_map>
#include <vector>

using namespace std;

int a[1919][810];

signed main() {
    int T;
    cin >> T;
    while (T --) {
        int n, m;
        cin >> n >> m;
        for (int i = 1; i <= n; i ++)
            for (int j = 1; j <= m; j ++)
                cin >> a[i][j];
        int mx = -114514;
        for (int i = 1; i <= n; i ++) for (int j = 1; j <= m; j ++) {
            int ans = 0;
            for (int x = i + 1, y = j + 1; x <= n && y <= m; x ++, y ++)
                ans += max(0, a[x][y]);
            for (int x = i + 1, y = j - 1; x <= n && y >= 1; x ++, y --)
                ans += max(0, a[x][y]);
            for (int x = i - 1, y = j - 1; x >= 1 && y >= 1; x --, y --)
                ans += max(0, a[x][y]);
            for (int x = i - 1, y = j + 1; x >= 1 && y <= m; x --, y ++)
                ans += max(0, a[x][y]);
            mx = max(mx, ans + a[i][j]);
        }
        cout << mx << '\n';
    }
    return 0;
}

```


---

## 作者：OLE_OIer (赞：0)

这道题是一道经典的二维数组模拟题。

思路是这样的，我们要遍历二维数组，得到一个位置使得它斜向的数之和最大。

模拟即可。不要忘记取最大值用打擂台的方法来实现哟！

代码附上：
```cpp
//CF1676D X-Sum
#include<bits/stdc++.h>
#define int long long
#define elif else if
using namespace std;
void func(){
	int n,m;
	cin>>n>>m;
	int a[n+10][m+10],maxn=0;//maxn存储最大值
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j) cin>>a[i][j];
	}
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			int cnta=0,cntb=0;
			for(int x=i,y=j;x>0&&y>0;--x,--y) cnta+=a[x][y];//向左上方求和。
			for(int x=i+1,y=j+1;x<=n&&y<=m;++x,++y) cnta+=a[x][y];//向右下方求和。
			for(int x=i,y=j;x<=n&&y>0;++x,--y) cntb+=a[x][y];//向左下方求和。
			for(int x=i-1,y=j+1;x>0&&y<=m;--x,++y) cntb+=a[x][y];//向右上方求和。
			maxn=max(cnta+cntb-a[i][j],maxn);//打擂台取最大值。
		}
	}
	cout<<maxn<<"\n";
}
signed main(){
	ios::sync_with_stdio(false);
	int n;
	cin>>n;
	for(int i=1;i<=n;++i) func();
	return 0;
}
```

---

