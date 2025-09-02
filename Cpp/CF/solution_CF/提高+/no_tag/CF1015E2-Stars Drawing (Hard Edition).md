# Stars Drawing (Hard Edition)

## 题目描述

定义一个星星是下面形状的图形：  
1. 由' $*$ '组成；  
2. 星星的大小就是它向四个方向延伸的' $*$ '个数，注意四个方向要取最短的，不允许出现大小为$0$的星星。 

空的格子是' $.$ '，下面是几种星星的例子：  
![](https://cdn.luogu.com.cn/upload/image_hosting/9pop6ksc.png)
不难发现，左图是大小为$1$的星星，中间的星星大小为$2$，而右侧的星星大小为$3$。  
现在给定一个大小为$n\times m$，由' $.$ '和' $*$ '构成的的矩阵。你的任务是使用任意数量和大小的星星，画出这个矩阵上' $*$ '的图案，星星之间可以相交或重合。但星星不能超出矩阵。

## 样例 #1

### 输入

```
6 8
....*...
...**...
..*****.
...**...
....*...
........
```

### 输出

```
3
3 4 1
3 5 2
3 5 1
```

## 样例 #2

### 输入

```
5 5
.*...
****.
.****
..**.
.....
```

### 输出

```
3
2 2 1
3 3 1
3 4 1
```

## 样例 #3

### 输入

```
5 5
.*...
***..
.*...
.*...
.....
```

### 输出

```
-1
```

## 样例 #4

### 输入

```
3 3
*.*
.*.
*.*
```

### 输出

```
-1
```

# 题解

## 作者：冯老师 (赞：5)

[题面](https://www.luogu.com.cn/problem/CF1015E2)

题目就是说要你用不超过 $n\times m$ 个星星覆盖所有的 $\texttt{*}$ 字符。不难发现。我们发现这个数量限制，正好可以对于每一个点，选一个以其作为中心的星星。为了尽可能地覆盖更多的点，我们一定选的是**最大**的星星，因为任何小星星覆盖的范围被包括在了这个大星星里面，可以不选。

如何求出以某个点为中心的星星的最大范围呢？可以发现这个值就是以某个 $\texttt{*}$ 为中心能往四个方向延申的最长距离的**最小值**。这里用 $up,down,pre,suf$ 四个数组来表示。以 $up_{i,j}$ 的求法为例（其中 $(i,j)$ 是 $\texttt{*}$），如果 $(i-1,j)$ 是 $\texttt{*}$，那么 $up_{i,j}=up_{i-1,j}+1$，否则 $up_{i,j}=1$。

处理好范围之后，我们要给这一行、一列覆盖的位置打上标记，然后再枚举所有 $\texttt{*}$ 的位置看是否覆盖。但是暴力枚举复杂度过高。考虑给一个一维的区间 $[l,r]$ 打上覆盖标记、单点查询是否覆盖怎么做。用 $cnt_i$ 表示覆盖的次数，显然将  $cnt_l\sim cnt_r$ 全部 $+1$，可以差分。对于这题也是如此，将一个位置的覆盖次数拆成横向的覆盖次数加上纵向的覆盖次数。然后就变成了一维差分。

最后暴力检查就行了。时空复杂度均为 $\mathcal{O}(nm)$。

[评测记录](https://www.luogu.com.cn/record/120736354)

代码（差分那边写臃肿了，其实不用映射成一维序列的）：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1005;
int n,m,up[N][N],down[N][N],pre[N][N],suf[N][N],cf_row[N*N],cf_col[N*N],range[N][N],cnt,sum_row[N*N],sum_col[N*N];
char ma[N][N];
int id_row(int x,int y){
    return (x-1)*m+y;
}
int id_col(int x,int y){
    return (y-1)*n+x;
}
signed main(){
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(0);
    memset(ma,'k',sizeof ma);
    cin>>n>>m;
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
            cin>>ma[i][j];
            if(ma[i][j]=='*'){
                up[i][j]=(ma[i-1][j]=='*'?up[i-1][j]+1:1);
                pre[i][j]=(ma[i][j-1]=='*'?pre[i][j-1]+1:1);
            }
        }
    }
    for(int i=n;i>=1;--i){
        for(int j=m;j>=1;--j){
            if(ma[i][j]=='*'){
                down[i][j]=(ma[i+1][j]=='*'?down[i+1][j]+1:1);
                suf[i][j]=(ma[i][j+1]=='*'?suf[i][j+1]+1:1);
                range[i][j]=min({up[i][j],down[i][j],pre[i][j],suf[i][j]})-1;
                if(range[i][j]>=1){
                    ++cnt;
                    ++cf_row[id_row(i,j-range[i][j])];
                    --cf_row[id_row(i,j+range[i][j]+1)];
                    ++cf_col[id_col(i-range[i][j],j)];
                    --cf_col[id_col(i+range[i][j]+1,j)];
                }
            }
        }
    }
    for(int i=1;i<=n*m;++i){
        sum_row[i]=sum_row[i-1]+cf_row[i];
        sum_col[i]=sum_col[i-1]+cf_col[i];
    }
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
            if(ma[i][j]=='*'){
                if(sum_row[id_row(i,j)]+sum_col[id_col(i,j)]<1){
                    cout<<"-1";
                    return 0;
                }
            }
        }
    }
    cout<<cnt<<'\n';
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
            if(ma[i][j]=='*'){
                if(range[i][j]>=1){
                    cout<<i<<' '<<j<<' '<<range[i][j]<<'\n';
                }
            }
        }
    }
    return 0;
}
```


---

## 作者：HoshizoraZ (赞：3)

其实这题应该要缩短时间限制，不然感觉暴力都可以卡过去。

这里提供一个 $O(nm \cdot\log \min(n,m))$ 的做法。

首先 E1 的暴力做法比较好实现：

- 枚举每一个 `*` 的位置，并且**尽可能**向四个方向扩展，标记每一个扩展的位置。
- 如果出现没有标记过的 `*`，输出 `-1`，否则输出刚刚扩展的方案。

这个想法的时间复杂度是三次方级别的，我们应将其优化。

**如何快速定位每个位置的最大扩展长度**

我们可以先只考虑一行或一列的情况。

如果我们把 `'*'` 的值视作 $1$，其余视作 $0$，那么一段区间的价值和就是区间中 `'*'` 的数量。

**所以，如果区间 $[l,r]$ 内全是** `'*'` **而没有 `'.'`，那么该区间的价值和为 $r-l+1$。** 

而我们扩展的时候，需要保证的是这个「星星图案」内没有 `'.'` 。

若从 $(i,j)$ 扩展长度 $k$，那么需要保证第 $i$ 行的第 $j-k~ \sim j+k$ 列位置**全部**为 `'*'`，第 $j$ 列同理。

上述条件，等价于第 $i$ 行的 `'*'` 总数为 $j+k-(j-k)+1=2k+1$。

如果不理解，可以看如下例子：

```plain
...*...
...*...
...*...
*******
...*...
...*...
...*...
`````

这是一个大小为 $3$ 的「星星图案」。

其中有「星星图案」的行、列的区间 `'*'` 数均为 $2\times3+1=7$。

而如下这个图没有长度为 $3$「星星图案」。

```plain
...*...
.......
...*...
*******
...*...
...*...
...*...
`````

原因是若以 $(4,4)$ 为中心扩展 $3$ 格，那么第 $4$ 列的区间和为 $6$，与 $7$ 不相等。

静态维护区间和，我们就可以使用**前缀和**。

只不过这是一个二维图案，我们需要分别对它进行行、列的前缀和。

**如何优化时间复杂度**

可以发现，如果以某点为中心，可以向外扩展 $k+1$ 个单位，那么它也绝对可以向外扩展 $k$ 个单位。

因此，扩展的长度相对条件具有**单调性**，我们可以**二分查找**。

**如何快速判断无解**

如果我们一个一个标记每个 `'*'` 的位置是否访问过，那复杂度就退化了。

但是我们有足够的复杂度可以**在最后时刻**一次性访问每个位置，判断它是否被访问过。

所以，将整个区间进行标记，可以是用**差分**，最后用前缀和求得答案。

注意一个「星星图案」的行、列都要标记。

有人会有所担心行、列若分别标记一次，中心会被标记两次，影响答案。

其实并不会，因为最后只有**行、列的差分数组前缀和均为 $0$**，才代表这个位置没有访问过。因此访问次数我们并不需要在意。

**以下是代码，不理解的地方可以参考注释**

```cpp
#include <bits/stdc++.h>
#define INF 1e9
#define eps 1e-6
typedef long long ll;
using namespace std;

int n, m, suml[1010][1010], sumu[1010][1010], l, r;
int addl[1010][1010], addw[1010][1010], sl[1010][1010], sw[1010][1010];
int ss, ans1[1000010], ans2[1000010], ans3[1000010];
bool vis[1010][1010];
char s[1010][1010];

bool check(int i, int j, int x){	// 判断是否全为 *
	if(sumu[i + x][j] - sumu[i - x - 1][j] != x + x + 1) return 0;
	if(suml[i][j + x] - suml[i][j - x - 1] != x + x + 1) return 0;
	return 1;
}

int main(){

	cin >> n >> m;
	for(int i = 1; i <= n; i++)
		scanf("%s", s[i] + 1);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)	// 行和列分别前缀和
			suml[i][j] = suml[i][j - 1] + (s[i][j] == '*');
	for(int i = 1; i <= m; i++)
		for(int j = 1; j <= n; j++)
			sumu[j][i] = sumu[j - 1][i] + (s[j][i] == '*');
			
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++){
			// 扩展范围不能超出边界
			l = 0, r = min(i - 1, min(n - i, min(j - 1, m - j)));
			while(l < r){
				int mid = (l + r + 1) >> 1;
				if(check(i, j, mid)) l = mid;
				else r = mid - 1;
			}
			if(l != 0){	// 记录答案、标记差分数组
				ans1[++ss] = i, ans2[ss] = j, ans3[ss] = l;
				addl[i - l][j]++, addl[i + l + 1][j]--;
				addw[i][j - l]++, addw[i][j + l + 1]--;
			}
		}
	for(int i = 1; i <= n; i++)	// 将差分数组进行前缀和得到访问记录
		for(int j = 1; j <= m; j++)
			sw[i][j] = sw[i][j - 1] + addw[i][j];
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			sl[i][j] = sl[i - 1][j] + addl[i][j];
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++){
			if(sw[i][j] == 0 && sl[i][j] == 0 && s[i][j] == '*'){	// 没有访问过的 * 需要输出 -1
				puts("-1");
				return 0;
			}
		}
	cout << ss << endl;	// 输出答案
	for(int i = 1; i <= ss; i++)
		printf("%d %d %d\n", ans1[i], ans2[i], ans3[i]);

	return 0;
}

```

---

## 作者：eEfiuys (赞：2)

题目：[CF1015E2](https://www.luogu.com.cn/problem/CF1015E2)

题目翻译见 [CF1015E1](https://www.luogu.com.cn/problem/CF1015E1)

### 枚举：
- 如果是 `*`，则进行扩展（没有要求最小化数量）。
- 由于边界上的不可能是中心，因此从 $(2,2)$ 枚举到 $(n-1,m-1)$ 即可。

### 扩展：
- 如果四个方向任何一个相邻的不是 `*`，那么直接跳过。
- 向 $4$ 个方向同时枚举，枚举到的进行标记，表示包含在这个星星里。
- 直到越界或不是 `*` 时停止，枚举的长度即为星星大小，存在对应坐标处，星星个数加 $1$。

### 输出：
- 如果有 `*` 没有被标记，即不被包含，则输出 `-1`。
- 输出枚举时统计的星星个数。
- 若某个坐标存了星星大小，则它是一个中心，输出。

时间复杂度 $O(n \times m \times \min(n,m))$。由于某些常数优化，数据很水，因此根本达不到这个上界，加之 $3s$ 的时限和 CF 机子的速度，可以 AC。

------------

## Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int read(){/*快读*/}
void print(){/*快写*/}
const int N=105;
int n,m;
bool mp[N][N];
bool star[N][N];
int siz[N][N];
int ans;
bool check(int i,int j,int k){
	return (i-k)&&(i+k<=n)&&(j-k)&&(j+k<=m)&&mp[i-k][j]&&mp[i+k][j]&&mp[i][j-k]&&mp[i][j+k];
}//扩展的判断
signed main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			char ch;cin>>ch;
			mp[i][j]=(ch=='*');//如果直接存字符的话，比较麻烦
		}
	for(int i=2;i<n;i++)
		for(int j=2;j<m;j++){
			if(!mp[i][j]||!mp[i][j-1]||!mp[i][j+1]||!mp[i-1][j]||!mp[i+1][j])continue; //不是星星中心
			star[i][j]=1; //标记
			int k;
			for(k=1;check(i,j,k);k++)star[i-k][j]=star[i+k][j]=star[i][j-k]=star[i][j+k]=1; //扩展，标记
			siz[i][j]=k-1,ans++; //记录星星大小，统计个数
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(mp[i][j]&&!star[i][j]){ //不被包含
				print(-1,'\n');
				return 0;
			}
	print(ans,'\n');
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(siz[i][j]) //是中心
				print(i,' '),print(j,' '),print(siz[i][j],'\n');
	return 0;
}
```

---

## 作者：__Deng_Rui_Song__ (赞：1)

# preface

~~优雅的暴力~~

# problem

[传送门](https://www.luogu.com.cn/problem/CF1015E2)

给你一个图案，定义一个长度为 $k$ 的“星星”为四条由'\*'组成且长度为 $k+1$ 且互相垂直的线交于一点，求这个图案是不是由“星星”组成。

# solution

此题很具有思维能力，考虑到如果要以一个点作为中心，那么这个星星肯定越大越好，所以对于每个点，都看一看最多能覆盖多少个'\*'~~，多问多答启动~~。

q1：怎样快速判断最多可以覆盖多少个点呢？

a1：不难想到如果长度为 $x$ 的“星星”可以覆盖，那么长度为 $x-1$ 的“星星”也可以覆盖，所以可以用**四个**二分，check 函数用前缀和判断。

q2：就算求出最多能覆盖多少点，可是有可能不合法啊，怎么判断呢？

a2：把“星星”看成三个矩阵，用差分即可。![](https://cdn.luogu.com.cn/upload/image_hosting/jhz50ohp.png)

# code

~~古有八十天环游地球，今有八十天切掉蓝题，石山代码请过目~~

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, pre[1005][1005], d[1005][1005], val[1005][1005];
char a[1005][1005];
vector<array<int, 3> > v;
int get_sum(int x1, int y1, int x2, int y2) { return pre[x2][y2] - pre[x1 - 1][y2] - pre[x2][y1 - 1] + pre[x1 - 1][y1 - 1]; }
void change(int x1, int y1, int x2, int y2) {
  d[x1][y1]++;
  d[x1][y2 + 1]--;
  d[x2 + 1][y1]--;
  d[x2 + 1][y2 + 1]++;
}
int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++) {
      cin >> a[i][j];
      pre[i][j] = pre[i - 1][j] + pre[i][j - 1] - pre[i - 1][j - 1] + (a[i][j] == '*');// 前缀和
    }
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      if (a[i][j] == '*') {
        int l = 0, r = i, minn;
        while (l + 1 < r) {
          int mid = (l + r) / 2;
          if (get_sum(i - mid, j, i, j) == mid + 1)// 如果全是'*'，则合法，下面同理
            l = mid;
          else
            r = mid;
        }
        minn = l;
        l = 0;
        r = j;
        while (l + 1 < r) {
          int mid = (l + r) / 2;
          if (get_sum(i, j - mid, i, j) == mid + 1)
            l = mid;
          else
            r = mid;
        }
        minn = min(minn, l);
        l = 0;
        r = n - i + 1;
        while (l + 1 < r) {
          int mid = (l + r) / 2;
          if (get_sum(i, j, i + mid, j) == mid + 1)
            l = mid;
          else
            r = mid;
        }
        minn = min(minn, l);
        l = 0;
        r = m - j + 1;
        while (l + 1 < r) {
          int mid = (l + r) / 2;
          if (get_sum(i, j, i, j + mid) == mid + 1)
            l = mid;
          else
            r = mid;
        }
        minn = min(minn, l);// 二分求最大能覆盖多少点
        if (minn) {
          v.push_back({i, j, minn});
          change(i - minn, j, i + minn, j);
          change(i, j - minn, i, j - 1);
          change(i, j + 1, i, j + minn);
        }
      }
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++) {
      val[i][j] = val[i - 1][j] + val[i][j - 1] - val[i - 1][j - 1] + d[i][j];
      if (a[i][j] == '*' && !val[i][j]) {// 如果这个点是'*'，但没有覆盖到，那么非法
        cout << -1;
        return 0;
      }
    }
  cout << v.size() << '\n';
  for (int i = 0; i < v.size(); i++) cout << v[i][0] << ' ' << v[i][1] << ' ' << v[i][2] << '\n';
  return 0;
}
```

---

## 作者：Vitamin_B (赞：0)

# 思路
设 $u_{i,j},d_{i,j},l_{i,j},r_{i,j}$ 分别为从 $a_{i,j}$ 开始向上、下、左、右方向延升出去的最长连续的星号，而以 $s_{i,j}$ 表示 $a_{i,j}$ 为中心能包含的最大星星大小，$s_{i,j}$ 其实就是 $\min(u_{i,j},d_{i,j},l_{i,j},r_{i,j})$。然后暴力标记一下，如果有点是星号却没被标记就无解，否则对于每个 $s_{i,j}>0$ 的都输出一次就行。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
int n, m, l[1005][1005], r[1005][1005], u[1005][1005], d[1005][1005], sum[1005][1005], ans;
string a[1005];
bitset <1005> vis[1005];
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> n >> m;
	for (int i = 1; i <= n; ++ i) {
		cin >> a[i];
		a[i] = '*' + a[i];
		for (int j = 1; j <= m; ++ j)
			if (a[i][j] == '*')
				l[i][j] = l[i][j - 1] + 1, u[i][j] = u[i - 1][j] + 1;
	}
	for (int i = n; i; -- i)
		for (int j = m; j; -- j)
			if (a[i][j] == '*') {
				r[i][j] = r[i][j + 1] + 1;
				d[i][j] = d[i + 1][j] + 1;
				sum[i][j] = min ({l[i][j], r[i][j], u[i][j], d[i][j]}) - 1;
				if (sum[i][j]) {
					++ ans;
					for (int x = i - sum[i][j]; x <= i + sum[i][j]; ++ x)
						vis[x][j] = 1;
					for (int y = j - sum[i][j]; y <= j + sum[i][j]; ++ y)
						vis[i][y] = 1;
				}
			}
	for (int i = 1; i <= n; ++ i)
		for (int j = 1; j <= m; ++ j)
			if (a[i][j] == '*' && ! vis[i][j]) {
				cout << -1;
				return 0;
			}
	cout << ans << '\n';
	for (int i = 1; i <= n; ++ i)
		for (int j = 1; j <= m; ++ j)
			if (sum[i][j])
				cout << i << ' ' << j << ' ' << sum[i][j] << '\n';
	return 0;
}
```

---

## 作者：zerlingx (赞：0)

# CF1015E2 Stars Drawing (Hard Edition) 题解（暴搜）

数据比较水。代码和Easy Edition几乎一样，只需要把数组开大点。 \
1000^3都能暴力…… \
唯一的问题是输出较多，卡了cout。

```c++
#include<iostream>
#include<cstring>
#include<queue>
#include<cstdio>
#define maxn (int)(1005)
using namespace std;
int n, m;
char mp[maxn][maxn];
int vis[maxn][maxn];
int draw(int x, int y){
    int i = x, j = y, len = 1;
    while(1){
        if(mp[i][j+len] == '*' && mp[i][j-len] == '*' && mp[i+len][j] == '*' && mp[i-len][j] == '*'
        && j+len < m && j-len >= 0 && i+len < n && i-len >= 0){
            vis[i][j] = 1;
            vis[i][j+len] = 1;
            vis[i][j-len] = 1;
            vis[i+len][j] = 1;
            vis[i-len][j] = 1;
            len++;
        }else{
            return len-1;
        }
    }
}
struct NODE{
    int x, y, len;
};
queue<NODE> q;
int main(){
    ios::sync_with_stdio(false);
    memset(vis, 0, sizeof(vis));
    int i, j;
    NODE tmp;
    cin >> n >> m;
    for(i = 0 ; i < n ; i++){
        cin >> mp[i];
    }
    
    int len;
    for(i = 1 ; i < n-1 ; i++){
        for(j = 1 ; j < m-1 ; j++){
            if(mp[i][j] == '*'){
                len = draw(i, j);
                if(len){
                    // cout << i << ' ' << j << ' ' << len << endl;
                    tmp.x = i;
                    tmp.y = j;
                    tmp.len = len;
                    q.push(tmp);
                }
            }
        }
    }

    for(i = 0 ; i < n ; i++){
        for(j = 0 ; j < m ; j++){
            if(mp[i][j] == '*'){
                if(vis[i][j] == 0){
                    cout << -1 << endl;
                    return 0;
                }
            }
        }
    }

    cout << q.size() << endl;
    while(!q.empty()){
        tmp = q.front();
        q.pop();
        // cout << tmp.x+1 << ' ' << tmp.y+1 << ' ' << tmp.len << endl;
        //还真卡cout，无语
        printf("%d %d %d\n", tmp.x+1, tmp.y+1, tmp.len);
    }


    return 0;
}
```

---

