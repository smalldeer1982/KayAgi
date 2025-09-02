# Stars Drawing (Easy Edition)

## 题目描述

定义一个星星是下面形状的图形：

- 由 $*$ 组成
- 星星的大小就是它向四个方向延伸的 $*$ 个数，注意四个方向要取最短的，不允许出现大小为0的星星

空的格子是 '$.$'（不包含引号），下面是几种星星的例子：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1015E1/dbf078fd5a2d2cf23bed0e2a7fa98ea60f68c8e9.png)

不难发现，左图是大小为 $1$ 的星星，中间的星星大小为 $2$ ，而右侧的星星大小为 $3$ 。



现在给定一个 $n\times m$ ，由'.'和'\*'（不包含引号）构成的的矩阵，你的任务是使用任意数量和大小的星星，画出这个矩阵上'\*'的图案，星星之间可以相交或重合。但星星不能超出矩阵。

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

[题面](https://www.luogu.com.cn/problem/CF1015E1)

题目就是说要你用不超过 $n\times m$ 个星星覆盖所有的 $\texttt{*}$ 字符。不难发现。我们发现这个数量限制，正好可以对于每一个点，选一个以其作为中心的星星。为了尽可能地覆盖更多的点，我们一定选的是**最大**的星星，因为任何小星星覆盖的范围被包括在了这个大星星里面，可以不选。

如何求出以某个点为中心的星星的最大范围呢？可以发现这个值就是以某个 $\texttt{*}$ 为中心能往四个方向延申的最长距离的**最小值**。这里用 $up,down,pre,suf$ 四个数组来表示。以 $up_{i,j}$ 的求法为例（其中 $(i,j)$ 是 $\texttt{*}$），如果 $(i-1,j)$ 是 $\texttt{*}$，那么 $up_{i,j}=up_{i-1,j}+1$，否则 $up_{i,j}=1$。

处理好范围之后，我们要给这一行、一列覆盖的位置打上标记，然后再枚举所有 $\texttt{*}$ 的位置看是否覆盖。但是暴力枚举复杂度过高。考虑给一个一维的区间 $[l,r]$ 打上覆盖标记、单点查询是否覆盖怎么做。用 $cnt_i$ 表示覆盖的次数，显然将  $cnt_l\sim cnt_r$ 全部 $+1$，可以差分。对于这题也是如此，将一个位置的覆盖次数拆成横向的覆盖次数加上纵向的覆盖次数。然后就变成了一维差分。

最后暴力检查就行了。时空复杂度均为 $\mathcal{O}(nm)$。


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

## 作者：Special_Tony (赞：0)

# 思路
设 $u_{i,j},d_{i,j},l_{i,j},r_{i,j}$ 分别为从 $a_{i,j}$ 开始向上、下、左、右方向延升出去的最长连续的星号，而以 $s_{i,j}$ 表示 $a_{i,j}$ 为中心能包含的最大星星大小，$s_{i,j}$ 其实就是 $\min(u_{i,j},d_{i,j},l_{i,j},r_{i,j})$。然后暴力标记一下，如果有点是星号却没被标记就无解，否则对于每个 $s_{i,j}>0$ 的都输出一次就行。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
int n, m, l[105][105], r[105][105], u[105][105], d[105][105], sum[105][105], ans;
string a[105];
bitset <105> vis[105];
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

## 作者：eEfiuys (赞：0)

题目：[CF1015E1](https://www.luogu.com.cn/problem/CF1015E1)

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

时间复杂度 $O(n \times m \times \min(n,m))$。

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

## 作者：minecraft_herobrine (赞：0)

注意到 $1\le n,m\le 100$ ，所以我们很容易想到暴力找所有位置，若某一个格子里是\*，就以这个格子为中心试着扩展一波，如果能扩展，就把这个星星的参数加入答案序列中直接输出就好了

暴力的方法看看代码应该就能懂吧qwq

```cpp
#include<bits/stdc++.h>
using namespace std;
char mp[114][514];
bool vis[114][514];//如果某一点是*且没有被扩展说明这个点不属于任何星星，输出-1
struct Res
{
	int x,y,s;
}r[19198+10];
int main()
{
	int n,m,i,j,resc=0,len;
	scanf("%d %d",&n,&m);
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++) cin>>mp[i][j];
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=m;j++)
		{
			int l=0,x=i,y=j;//l是星星的大小，xy就是星星中心点的坐标
			if(mp[i][j]=='*')
			{
				for(len=1;i-len>=1 && i+len<=n && j-len>=1 && j+len<=m;len++)
				{
					if(mp[i+len][j]=='*' && mp[i-len][j]=='*' && mp[i][j+len]=='*' && mp[i][j-len]=='*')
					{
						l=len;
						vis[i][j]=true;
						vis[i+len][j]=true;
						vis[i-len][j]=true;
						vis[i][j+len]=true;
						vis[i][j-len]=true;
					}
					else break;
				}
			}
			if(l)
			{
				resc++;
				r[resc].x=i;
				r[resc].y=j;
				r[resc].s=l;
			}
		}
	}
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)
			if(mp[i][j]=='*' && !vis[i][j])
			{
				printf("-1");
				return 0;
			}
	printf("%d\n",resc);
	for(i=1;i<=resc;i++) printf("%d %d %d\n",r[i].x,r[i].y,r[i].s);
	return 0;
}
```

---

