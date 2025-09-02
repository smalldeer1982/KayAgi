# Three-dimensional Turtle Super Computer

## 题目描述

有一个 $n\times m \times k$ 的立方体，分成 $1\times 1 \times 1$ 的不同的小方格。

小方格的状态由 $0$ 或 $1$ 表示，$1$ 表示该点为一个有效点，$0$ 表示该点为一个非有效点。

定义每一个点周围的 $6$ 个与该点有两维坐标相等且不同维度坐标绝对差为 $1$ 的点直接相连。

任意两个不同的有效点 $x_1$ 与 $x_2$ 如果存在**有且仅有**一个与两点直接相连且不同的点 $x_3$ 使得两点间接相连，则称 $x_3$ 具有关键性。

## 样例 #1

### 输入

```
2 2 3
000
000

111
111
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3 3 3
111
111
111

111
111
111

111
111
111
```

### 输出

```
19
```

## 样例 #3

### 输入

```
1 1 10
0101010101
```

### 输出

```
0
```

# 题解

## 作者：xuan_gong_dong (赞：2)

~~题目机翻相当答辩~~
## 题目

[Three-dimensional Turtle Super Computer](https://www.luogu.com.cn/problem/CF638D)

大概意思就是找到有多少个点使得如果该点变为 $0$ 后某两个节点从可以传输信息变为不可传输。

## 分析
暴力寻找就好了，因为信息只可能从地址小的到大的那就分以下情况：

- 以下为 $x,y$ 轴情况：

1. 中间节点为关键点：

```
111
```

2. 中间也为关键点：

```
1
1
1
```
- 以下情况为 $x,y$ 轴与 $x,z$ 轴与 $y,z$ 轴的情况  

1. 右上角为关键点：

```
11
01
```

2. 左下角为关键点：

```
10
11
```

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k;
int a[110][110][110];
char t[110];
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
	
			scanf("%s",t+1);
			for(int x=1;x<=k;x++)
			{
				a[i][j][x]=t[x]-'0';
			}
		}
	}
	int hys=0;;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			for(int x=1;x<=k;x++)
			{
				if(a[i][j][x])
				{
					if(a[i][j][x-1]&&a[i][j][x+1])
					{
						hys++;
						continue;
					}
					if(a[i][j+1][x]&&a[i][j-1][x])
					{
						hys++;
						continue;		
					}
					if(a[i+1][j][x]&&a[i-1][j][x])
					{
						hys++;
						continue;
					}
					if(a[i][j-1][x]&&a[i+1][j][x]&&a[i+1][j-1][x]==0)
					{
						hys++;
						continue;
					}					
					if(a[i-1][j][x]&&a[i][j+1][x]&&a[i-1][j+1][x]==0)
					{
						hys++;
						continue;
					}						
					if(a[i+1][j][x]&&a[i][j][x-1]&&a[i+1][j][x-1]==0)
					{
						hys++;
						continue;
					}						
					if(a[i-1][j][x]&&a[i][j][x+1]&&a[i-1][j][x+1]==0)
					{
						hys++;
						continue;
					}					
					if(a[i][j-1][x]&&a[i][j][x+1]&&a[i][j-1][x+1]==0)
					{
						hys++;
						continue;
					}			
					if(a[i][j+1][x]&&a[i][j][x-1]&&a[i][j+1][x-1]==0)
					{
						hys++;
						continue;
					}												
					
				}
			}
		}
	}
	printf("%d",hys);;
	return 0;
}
```


---

## 作者：Tulip_ (赞：0)

### 题意

给你一个长为 $x$，宽为 $y$，高为 $z$ 的三维图，每格可以是 $1$ 或 $0$，现在要找到一个格子，使得它连接了两个值为 $1$ 的格子且这两个格子只被它连接，求这样的格子数量。

### 思路

我们很容易发现三种格子连接的情况有 $2$ 种。

分别是：

```
1 1 1
--- -- 种类分割线
1 1
1 0
```

而他的复杂度是 $O (xyz)$，所以可以用暴力来解决。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int x,y,z;
int ans,a[110][110][110];
char o;
signed main(){
	cin>>x>>y>>z;
	for(int i=1;i<=x;i++)
	for(int j=1;j<=y;j++)
	for(int k=1;k<=z;k++)
	cin>>o,a[i][j][k]=o-'0';
 
	for(int i=1;i<=x;i++)
	for(int j=1;j<=y;j++)
	for(int k=1;k<=z;k++)
	if(a[i][j][k])
	if(a[i][j][k-1]&&a[i][j][k+1])ans++;
	else if(a[i][j+1][k]&&a[i][j-1][k])ans++;	
	else if(a[i+1][j][k]&&a[i-1][j][k])ans++;
	else if(a[i][j-1][k]&&a[i+1][j][k]&&!a[i+1][j-1][k])ans++;
	else if(a[i-1][j][k]&&a[i][j+1][k]&&!a[i-1][j+1][k])ans++;						
	else if(a[i+1][j][k]&&a[i][j][k-1]&&!a[i+1][j][k-1])ans++;				
	else if(a[i-1][j][k]&&a[i][j][k+1]&&!a[i-1][j][k+1])ans++;				
	else if(a[i][j-1][k]&&a[i][j][k+1]&&!a[i][j-1][k+1])ans++;	
	else if(a[i][j+1][k]&&a[i][j][k-1]&&!a[i][j+1][k-1])ans++;
	cout<<ans;
}
```

---

## 作者：ZettaByte (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF638D)

### 题意

~~蜜汁机翻~~

给你一个长为 $x$，宽为 $y$，高为 $z$ 的三维图，每格可以是 $1$ 或 $0$，现在要找到一个格子，使得它连接了两个值为 $1$ 的格子且**这两个格子只被它连接**，求这样的格子数量。

### 解法

容易发现三个格子的连接情况只有以下两种：

- 第一种：
	```
	1 1 1
	```

- 第二种：

	```
	1 1
	1 0
	```

注：此处的连接情况可以旋转、翻转。

因此我们暴力枚举每个点是否合法，复杂度 $\Theta(xyz)$，不会超时。

#### AC CODE：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, k, ret, mp[110][110][110]; char s[110][110][110];
int check(int x, int y, int z)
{
	if (mp[x][y][z - 1] && mp[x][y][z + 1]) return 1;
	if (mp[x][y + 1][z] && mp[x][y - 1][z]) return 1;
	if (mp[x + 1][y][z] && mp[x - 1][y][z]) return 1;				
	if (mp[x + 1][y][z] && mp[x][y][z - 1] && !mp[x + 1][y][z - 1]) return 1;
	if (mp[x - 1][y][z] && mp[x][y + 1][z] && !mp[x - 1][y + 1][z]) return 1;
	if (mp[x - 1][y][z] && mp[x][y][z + 1] && !mp[x - 1][y][z + 1]) return 1;
	if (mp[x][y + 1][z] && mp[x][y][z - 1] && !mp[x][y + 1][z - 1]) return 1;
	if (mp[x][y - 1][z] && mp[x + 1][y][z] && !mp[x + 1][y - 1][z]) return 1;	
	if (mp[x][y - 1][z] && mp[x][y][z + 1] && !mp[x][y - 1][z + 1]) return 1;
	return 0;
}

int main()
{
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) scanf("%s", s[i][j] + 1);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			for (int l = 1; l <= k; l++) mp[i][j][l] = s[i][j][l] - '0';
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			for (int l = 1; l <= k; l++)
				if (mp[i][j][l]) ret += check(i, j, l);
	printf("%d\n", ret);
	return 0;
}
```

---

## 作者：_qingshu_ (赞：0)

# 题意：

~~经典的格子 $=$ 细胞，神秘的机翻~~。大体意思是说给定一个 $x\times y \times z$ 的三维图，求当某个点从 ```1``` 变为 ```0``` 之后其有相邻的两个 ```1``` 无法通过另一个 ```1``` 点把它们两个连接起来的点的个数。

# 思路：

因为 $1 \le x,y,z \le 100$，所以考虑直接暴力枚举，判断该点是否为关键点的方法可以尝试组合它的相邻点，如果是类似 ```L``` 形的结构就多判断一下剩下的那个角是不是 ```0``` 就好了，细节和码量略大。

# Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int x,y,z,ans,a[110][110][110];
char in;
int main(){
	cin>>x>>y>>z;
	for(int i=1;i<=x;i++)
	for(int j=1;j<=y;j++)
	for(int k=1;k<=z;k++){
		cin>>in;
		a[i][j][k]=in-'0';
	}
	for(int i=1;i<=x;i++)
	for(int j=1;j<=y;j++)
	for(int k=1;k<=z;k++)
	if(a[i][j][k])
	if(a[i][j][k-1]&&a[i][j][k+1])ans++;
	else if(a[i][j+1][k]&&a[i][j-1][k])ans++;	
	else if(a[i+1][j][k]&&a[i-1][j][k])ans++;
	else if(a[i][j-1][k]&&a[i+1][j][k]&&!a[i+1][j-1][k])ans++;
	else if(a[i-1][j][k]&&a[i][j+1][k]&&!a[i-1][j+1][k])ans++;						
	else if(a[i+1][j][k]&&a[i][j][k-1]&&!a[i+1][j][k-1])ans++;				
	else if(a[i-1][j][k]&&a[i][j][k+1]&&!a[i-1][j][k+1])ans++;				
	else if(a[i][j-1][k]&&a[i][j][k+1]&&!a[i][j-1][k+1])ans++;	
	else if(a[i][j+1][k]&&a[i][j][k-1]&&!a[i][j+1][k-1])ans++;
	cout<<ans;
}
```

---

## 作者：fish_gugu (赞：0)

## 题意

有一个三维空间，从 $(x,y,z)$ 的信号可以传输到 $(x+1,y,z)$,$(x,y+1,z)$,$(x,y,z+1)$。现在有一些是坏的，就是不能用的，然后问你里面有多少个关键点。关键点就是，如果这个坏了，会改变原来的传输信号的过程。假设原来 $(x,y,z)$ 能够传输到 $(x1,y1,z1)$，但是由于坏了 $(x2,y2,z2)$，导致不能传输了，就说 $(x2,y2,z2)$ 是关键的。

## 思路

这题因为数据并不是很大的缘故，可以用一堆`for`**模拟**一下，只用判断**每一个好的周围的那些路线**就可以了。时间复杂度为 $O(nmk)$，不会爆零。

## 代码
 ```c
#include <bits/stdc++.h>
using namespace std;
int str[120][120][120];
int main()
{
    int n,m,k;
    cin >> n >> m >> k;
    for(int i = 1;i <= n;i++)
    {
        for(int j = 1;j <= m;j++)
        {
            string s;
            cin >> s;
            for(int t = 0;t < s.size();t++) //接下来是处理路线
            {
                if(s[t] == '1') str[i][j][t + 1] = 1;
                else str[i][j][t + 1] = 0;
            }
        }
    }
    int ans = 0;
    for(int i = 1;i <= n;i++)
    {
        for(int j = 1;j <= m;j++)
        {
            for(int t = 1;t <= k;t++)
            {
                if(str[i][j][t]) //判断路线是否是好的，如果是，就让ans + 1
                {
                    if(str[i - 1][j][t] && str[i + 1][j][t]) ans++;
                    else if(str[i][j - 1][t] && str[i][j + 1][t]) ans++;
                    else if(str[i][j][t - 1] && str[i][j][t + 1]) ans++;
                    else if(str[i - 1][j][t] && str[i][j + 1][t] && (!str[i - 1][j + 1][t])) ans++;
                    else if(str[i - 1][j][t] && str[i][j][t + 1] && (!str[i - 1][j][t + 1])) ans++;
                    else if(str[i][j - 1][t] && str[i + 1][j][t] && (!str[i + 1][j - 1][t])) ans++;
                    else if(str[i][j - 1][t] && str[i][j][t + 1] && (!str[i][j - 1][t + 1])) ans++;
                    else if(str[i][j][t - 1] && str[i + 1][j][t] && (!str[i + 1][j][t - 1])) ans++;
                    else if(str[i][j][t - 1] && str[i][j + 1][t] && (!str[i][j + 1][t - 1])) ans++;
                }
                
            }
        }
    }
    cout << ans;
    return 0;
}
```

---

