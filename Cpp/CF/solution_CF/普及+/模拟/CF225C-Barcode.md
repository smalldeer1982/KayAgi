# Barcode

## 题目描述

You've got an $ n×m $ pixel picture. Each pixel can be white or black. Your task is to change the colors of as few pixels as possible to obtain a barcode picture.

A picture is a barcode if the following conditions are fulfilled:

- All pixels in each column are of the same color.
- The width of each monochrome vertical line is at least $ x $ and at most $ y $ pixels. In other words, if we group all neighbouring columns of the pixels with equal color, the size of each group can not be less than $ x $ or greater than $ y $ .

## 说明/提示

In the first test sample the picture after changing some colors can looks as follows:

 `<br></br>.##..<br></br>.##..<br></br>.##..<br></br>.##..<br></br>.##..<br></br>.##..<br></br>`In the second test sample the picture after changing some colors can looks as follows:

 `<br></br>.#.#.<br></br>.#.#.<br></br>`

## 样例 #1

### 输入

```
6 5 1 2
##.#.
.###.
###..
#...#
.##.#
###..
```

### 输出

```
11
```

## 样例 #2

### 输入

```
2 5 1 1
#####
.....
```

### 输出

```
5
```

# 题解

## 作者：45dinо (赞：5)

这道题有一个特别的条件：
>The width of each monochrome vertical line is at least $x$ and at most $y$ pixels. In other words, if we group all neighbouring columns of the pixels with equal color, the size of each group can not be less than $x$ or greater than $y$ .

翻成中文，大概就是说相同颜色并连续的列长度要在 $[x,y]$ 之间。

如果直接dp，并不能很好地用状态记录。

所以考虑在转移时将这一点体现出来。

发现最后可以将 $m$ 列分成一些长为 $n$，宽为 $[x,y]$ 的矩形，相邻的矩形颜色不同，矩形内部颜色相同。

设 $dp_{i,0/1}$ 表示考虑到了第 $i$ 位，这一位是 $0/1$ ，从下一位开始颜色不同，且前面颜色都符合条件的最小修改数。

状态转移方程也显而易见

$$dp[i+j][0]=\min(dp[i+j][0],dp[i][1]++sum[i+j]-sum[i])$$
$$dp[i+j][1]=\min(dp[i+j][1],dp[i][0]+n\times j-sum[i+j]+sum[i])$$

最后是喜闻乐见的代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int sum[1001],n,m,x,y,dp[1001][2];
char c;
int main()
{
	scanf("%d %d %d %d",&n,&m,&x,&y);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			c=0;
			while(c!='#'&&c!='.')
				c=getchar();
			if(c=='#')
				sum[j]++;
		}
	for(int i=1;i<=m;i++)
		sum[i]+=sum[i-1];
	memset(dp,63,sizeof(dp));
	dp[0][0]=0;
	dp[0][1]=0;
	for(int i=0;i<m;i++)
		for(int j=x;j<=y;j++)
		{
			if(i+j>m)
				break;
			dp[i+j][0]=min(dp[i+j][0],dp[i][1]+sum[i+j]-sum[i]);
			dp[i+j][1]=min(dp[i+j][1],dp[i][0]+n*j-sum[i+j]+sum[i]);
		}
	cout<<min(dp[m][0],dp[m][1]);
	return 0;
}
```


---

## 作者：fuxuantong123 (赞：3)

# CF225C Barcode 题解
## 思路
首先肯定要把矩阵转化成线性的，就是只存每一列转化成黑、白的代价（转化成黑的代价是白色的数量，白色同理）。

然后想到动归，如果正着动归（收集型）会很不方便，所以可以用扩散型。

>举个例子，斐波那契额数列的式子是 $f_i=f_{i-1}+f_{i-2}$，可以写成 $f_{i+1}=f_{i+1}+f_i$ 和 $f_{i+2}=f_{i+2}+f_i$ 的形式。前者是收集型，后者是扩散型。

所以状态 $f_{i,0/1}$ 表示从 $1$ 到 $i$ 列都满足条件，并且当前列颜色是黑或白的最少修改数。


那如何转移呢？

枚举从当前位置往后 $x$ 到 $y$ 之间的列数 $j$，将现在的位置到 $i+j$ 的矩阵（已经化为区间）修改为同一颜色，也就是把整个图化为相邻颜色不同的矩阵。

得出转移方程：

$$f_{i+j,0}=\min(f_{i+j,0},f_{i,1}+a_{i+j}-a_i)$$

$$f_{i+j,1}=\min(f_{i+j,1},f_{i,0}+b_{i+j}-b_i)$$

其中 $a$ 和 $b$ 数组分别是每一列转成黑色和白色的代价的前缀和。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[1010];
int b[1010];
int f[2010][2];
int main(){
	int n,m,x,y;
	scanf("%d%d%d%d",&n,&m,&x,&y);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			char c;
			cin>>c;
			if(c=='#'){
				b[j]++;
			}
			if(c=='.'){
				a[j]++;
			}
		}
	}
	for(int i=1;i<=m;i++){
		a[i]+=a[i-1];
		b[i]+=b[i-1];
	}
	memset(f,0x3f,sizeof(f));
	f[0][0]=0;
	f[0][1]=0;
	for(int i=0;i<m;i++){
		for(int j=x;i+j<=m && j<=y;j++){
			f[i+j][0]=min(f[i+j][0],f[i][1]+a[i+j]-a[i]);
			f[i+j][1]=min(f[i+j][1],f[i][0]+b[i+j]-b[i]);
		}
	}
	
	printf("%d",min(f[m][0],f[m][1]));
return 0;
}
```



---

## 作者：wxzzzz (赞：3)

### 题意

给定一个 $n×m$ 的黑白矩阵，求至少改变多少个格子的颜色，使得每列颜色相同，并且 $x\le$ 连续相同的列数 $\le y$。

### 思路

看到这么奇怪的要求，就肯定是 DP 了。

设 $f_{i,k}$ 为使 $1$ 到 $i$ 列满足条件，并且当前位置的颜色为 $k$ 的最小修改数。（$k\in0/1$）

如果用 $i$ 之前的状态递推 $i$ 就要考虑很多边界，比较麻烦，因此可以用 $i$ 来递推后面的状态。

**具体实现：**

开辅助数组 $w,b$，$w_i$ 表示第 $i$ 列白色的数量，$b_i$ 表示第 $i$ 列黑色的数量。

用 $j$ 表示当前矩形宽度，有：

$$f_{i+j,0}=\min(f_{i+j,0},f_{i,1}+b_{i+j}-b_i)$$

$$f_{i+j,1}=\min(f_{i+j,1},f_{i,0}+w_{i+j}-w_i)$$

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, x, y, w[1005], b[1005], f[1005][2];
char g[1005][1005];
int main() {
    cin >> n >> m >> x >> y;

    for (int i = 1; i <= n; i++)
        scanf("%s", g[i] + 1);

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (g[j][i] == '.')
                w[i]++;
            else
                b[i]++;
        }

        w[i] += w[i - 1], b[i] += b[i - 1];
    }

    memset(f, 0x3f, sizeof f);
    f[0][0] = f[0][1] = 0;

    for (int i = 0; i < m; i++) {
        for (int j = x; i + j <= m && j <= y; j++) {
            f[i + j][0] = min(f[i + j][0], f[i][1] + b[i + j] - b[i]);
            f[i + j][1] = min(f[i + j][1], f[i][0] + w[i + j] - w[i]);
        }
    }

    cout << min(f[m][0], f[m][1]);
    return 0;
}
```

---

## 作者：pitiless0514 (赞：2)

## CF225C Barcode

#### 1.题目描述：
有一个方阵，要让每一列的颜色相同。然后连续相同的颜色列数在 $x$ 与 $y$ 之间。求最少的染色数。

#### 2.解析：

这是一道有意思的 dp ，给了我一些启发。

你发现这个有一个有意思的限制，它要求了连续相同的颜色列数有一个范围。那你要考虑取限制这个东西。

怎么限制啊，感觉不太好限制。

后面想了一下，你可以这样来设立状态为 dp[i][0/1] 表示的是当前考虑到了第 $i$ 列，染色为白色或者黑色的最少颜色数。

那接下来我们直接枚举从往后染 $x$ 与 $y$ 之间的列数为同一颜色。也就是把整个图划分为相邻颜色不同的矩形。 

我们设 $j$ 表示往后面染 $j$ 列为同一颜色。

那么可以写出状态转移方程为：

$$dp[i+j][0]=\min(dp[i+j][0],dp[i][1]+s[i+j]-s[i])$$
$$dp[i+j][1]=\min(dp[i+j][1],dp[i][0]+t[i+j]-t[i])$$

然后就解决了。

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int N = 2060;
int n,m,x,y,a[N][N],s[N],t[N],ans,vis[N];
int dp[N][3];
signed main(){
	ios::sync_with_stdio(0);cin.tie(0),cout.tie(0);
	cin>>n>>m>>x>>y;
	for(int i=1;i<=n;i++){
		string ssh;
		cin>>ssh;
		for(int j=0;j<m;j++){
			if(ssh[j]=='#') s[j+1]++;
			else t[j+1]++;
		}
	}
 for(int j=1;j<=m;j++){
	 s[j]+=s[j-1];t[j]+=t[j-1];
 }
	memset(dp,127,sizeof(dp));
	dp[0][0]=dp[0][1]=0;
	for(int i=0;i<m;i++){
		for(int j=x;j<=y;j++){
			if(i+j>m) break;
			dp[i+j][0]=min(dp[i+j][0],dp[i][1]+s[i+j]-s[i]);
			dp[i+j][1]=min(dp[i+j][1],dp[i][0]+t[i+j]-t[i]);
		}
	}
	cout<<min(dp[m][0],dp[m][1]);
	return 0;
}
```


---

## 作者：kska (赞：2)

二维前缀和统计一下到某一列为止黑色和白色格子的数量

然后考虑最后一段连续的列，是从之前的另一种颜色转移过来，并且这一次再染这段区间另一种颜色的数量。

最后从前往后扫一遍即可

附上代码

	#include<bits/stdc++.h>
	#define ll long long
	#define maxn 1010
	using namespace std;
	ll n,m,x,y,s[maxn][maxn][2],dp[maxn][2],ts,st;
	char mp[maxn][maxn];
	int main(){
		scanf("%lld%lld%lld%lld",&n,&m,&x,&y);
		for (int i = 1; i <= n; i++) {
			scanf("%s", mp[i] + 1);
		}
		for (int i = 1; i <= n; i++){
			for (int j = 1; j <= m; j++) {
				for (int k = 0; k < 2; k++) {
					s[i][j][k] = s[i][j-1][k];
				}
				if (mp[i][j] == '.') {
					s[i][j][0]++;
				} else {
					s[i][j][1]++;
				}
			}
		}

		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				for(int k=0;k<2;k++){
					s[i][j][k]+=s[i-1][j][k];
				}
			}
		}
		memset(dp,0x3f,sizeof dp);
		dp[0][1] = 0;
		dp[0][0] = 0;
		for(ll i=1;i<=m;i++){
			for(ll j=max(i-y,0LL);j<=i-x;j++){
				for(ll k=0;k<2;k++){
					dp[i][k]=min(dp[i][k],dp[j][k^1]+s[n][i][k^1]-s[n][j][k^1]);
				}
			}
		}
		cout<<min(dp[m][0],dp[m][1])<<endl;
		return 0;
	}

---

## 作者：Special_Tony (赞：1)

# 思路
$s0_i$ 表示第 $i$ 列中 `.` 的个数（此处不是 `#`，因为全改成 `#` 需要修改 `.` 的个数的代价），$s1_i$ 表示第 $i$ 列中 `#` 的个数，$dp_{i,j,k}$ 表示最后一列是第 $i$ 列且最后一列选了 $k$，已经连续相同了 $j$ 列时的最小代价（$0$ 表示 `#`，$1$ 表示 `.`）。$dp_{i,1,k}$ 可以从 $dp_{i-1,l\sim r,\neg k}$ 转移过来，$dp_{i,j,k}$ 可以从 $dp_{i-1,j-1,k}$ 转移过来。最终结果就是 $\min(dp_{n,l\sim r,0\sim1})$。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
int n, m, l, r, dp[1005][1005][2], a[1005][2], minx = 1e9;
string s;
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> n >> m >> l >> r;
	for (int i = 0; i < n; ++ i) {
		cin >> s;
		for (int j = 0; j < m;)
			if (s[j] ^ '#')
				++ a[++ j][0];
			else
				++ a[++ j][1];
	}
	memset (dp, 0x3f, sizeof dp);
	dp[0][0][0] = dp[0][0][1] = 0;
	for (int i = 1; i <= m; ++ i) {
		for (int j = l; j <= r; ++ j)
			for (int k = 0; k < 2; ++ k)
				dp[i][1][k] = min (dp[i][1][k], dp[i - 1][j][! k] + a[i][k]);
		for (int j = 1; j <= r; ++ j)
			for (int k = 0; k < 2; ++ k)
				dp[i][j][k] = min (dp[i][j][k], dp[i - 1][j - 1][k] + a[i][k]);
	}
	for (int j = l; j <= r; ++ j)
		for (int k = 0; k < 2; ++ k)
			minx = min (minx, dp[m][j][k]);
	cout << minx;
	return 0;
}
````

---

## 作者：FstAutoMaton (赞：0)

一道比较水的 ```DP``` 题。

首先，题目说相邻且颜色相同的列数一段的长度 $j$ 必要满足 $x\le j \le y$。那么我们就可以从 $x$ 开始枚举 $j$，枚举到 $y$ 结束。
由此可以得到 ```DP``` 状态为 $f_i$ 表从第 1 列到第 $i$ 列需要的最小费用。那此时可以发现一个问题：由于颜色可以变白也可以变黑，导致当前的最优解在将来不一定是最优解，所以我们可以另加一维，用 $f_{i,0}$ 表示从第 1 列到第 $i$ 列，且第 $i$ 列全变成白所用的最小费用。
同理，$f_{i,1}$ 表示从第 1 列到第 $i$ 列，且第 $i$ 列全变成黑所用的最小费用。可这时又有一个问题，如果每次都去循环求一遍想要变为该颜色的费用，那么时间复杂度是无法通过本题的，那么求区间和只要运用前缀和就可以了。转移方程如下：
$$f_{i+j,0}=\min(f_{i,0}+s_{i+j}-s_i,f_{i+j,0})$$
$$f_{i+j,1}=\min(f_{i,1}+n \times j-s_{i+j}-s_i,f_{i+j,1})$$

那么完整代码如下：
```
#include <bits/stdc++.h>
using namespace std;
const int pty = 2e3 + 5;
int n, m, x, y, a[pty][pty], s[pty], f[pty][2];
int ans;
int main()
{
    memset( f, 127, sizeof( f ) );
    cin >> n >> m >> x >> y;
    for( int i = 1; i <= n; i ++ )
    {   
        for( int j = 1; j <= m; j ++ )
        {
            char a;
            cin >> a;
            s[j] += ( a == '.' );
        }
    }
    for( int i = 1; i <= m; i ++ )
        s[i] = s[i] + s[i - 1];
    f[0][0] = f[0][1] = 0;
    for( int i = 0; i < m; i ++ )
    {
        for( int j = x; j <= y; j ++ )
        {
            if( i + j > m ) break;
            f[i + j][0] = min( f[i + j][0], f[i][1] + s[i + j] - s[i] );
            f[i + j][1] = min( f[i + j][1], f[i][0] + n * j - s[i + j] + s[i] );
        }
    }
    cout << min( f[m][0], f[m][1] );
}
```


---

