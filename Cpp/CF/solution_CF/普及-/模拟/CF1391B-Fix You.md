# Fix You

## 题目描述

给你一个 $n \times m$ 的矩阵，每一格上有个一标记不是 $R$ 就是 $D$，如果为 $R$ 表示这一格的物品会被送到这一格紧邻的右边的那一格，如果为 $D$ 表示这一格的物品会被送到这一格紧邻的下边的那一格。问你最少修改（$R$ 变 $D$ 或者 $D$ 变 $R$）多少次使得不管哪一个里的物品最后都能到达 $(n,m)$。

translated by [yu__xuan](https://www.luogu.com.cn/user/142110)

## 样例 #1

### 输入

```
4
3 3
RRD
DDR
RRC
1 4
DDDC
6 9
RDDDDDRRR
RRDDRRDDD
RRDRDRRDR
DDDDRDDRR
DRRDRDDDR
DDRDRRDDC
1 1
C```

### 输出

```
1
3
9
0```

# 题解

## 作者：Dry_ice (赞：5)

> 个人认为这个题目评级$\color{gold}{\text{黄}}$左右还是较为合适的。

## 思路

别管题目中说那么多的传送带，简化着说就是能送到最后一个，就肯定不会出界。出界则分 $2$ 种情况：

- 在 $A_{i,m}(i=1,2,\cdots,n-1)$ 的位置有向右的传送带即 $R$，这时会右溢出（出界）。

- 在 $A_{n,j}(j=1,2,\cdots,m-1)$ 的位置有向下的传送带即 $D$，这时会下溢出（出界）。

这样的话只需要一个 $O(nm)$ 的遍历就能过了。略加优化：只遍历最后一行和最后一列就是 $O(n+m)$。

## CODE
```cpp
#include <stdio.h>
int n, m;
char mp[105][105];
inline bool check(int x, int y) {
    if (y == m && mp[x][y] == 'R')
        return false;
    if (x == n && mp[x][y] == 'D')
        return false;
    return true;
}
int main(void) {
    int t;
    for (scanf("%d", &t); t--; ) {
        scanf("%d %d", &n, &m);
        for (int i = 1; i <= n; ++i)
            scanf("%s", mp[i] + 1);
        int ans = 0;
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j) {
                if (i == n && j == m)
                    continue;
                if (!check(i, j))
                    ++ans;
            }
        printf("%d\n", ans);
    }
    return 0;
}
```

如果您觉得这篇题解还珂以的话，就丢个赞吧！

---

## 作者：smallfang (赞：2)

 这道题、我们发现、所有传送带只能向下传送或者向右传送，所以不会出现环。因为环需要上下同时出现或者左右同时出现。这证明、所有点都会走到最后一行或者最后一列。那么最后一列需要让所有步骤变为**下**才能到达重点、最后一行需要所有步骤变为**右**，才能到达终点。那就统计最后一列右的个数、最后一行下的个数即可。

Code

```cpp
#include <iostream>

using namespace std;

const int MAXN = 1e5;
const int INF = 1e9;

int n, m;

int main()
{
	int t;
	scanf("%d", &t);
	while (t -- )
	{
		scanf("%d%d", &n, &m);
		char x;
		int c = 0;
		for (int i = 1; i <= n; i ++ )
		{
			for (int j = 1; j <= m; j ++ )
			{
				cin >> x;
				if (i == n && j == m)
				{
					continue;
				}
				if (i == n)
				{
					c += (x != 'R');
				}
				if (j == m)
				{
					c += (x != 'D');
				}
			}
		}
		printf("%d\n", c);
	}
	return 0;
}
```

---

## 作者：Acapplella (赞：1)

我们发现，所有的货物都是向右或者向下的，也就是说所有的货物最终都是会运到网格传送带的最右端或最下端。因此，我们只需要将最右端处的传送带改成向下，最下端的传送带改成向右就可以满足题目要求了。

**代码略...**

---

## 作者：yu__xuan (赞：1)

### 题目
[CF1391B Fix You](https://www.luogu.com.cn/problem/CF1391B)

### 思路
思路题。

如下图，因为方格中只存在 $R$ 或者 $D$，物品一开始位于 $(x, y)$，$x \in [1, n), \ y \in [1, m)$，物品最后都会到达最后一行或者是最后一列，因此只需要最后一行都是 $R$ 并且最后一列都是 $D$ 即可。最后答案就是最后一行 $D$ 的数目加最后一列 $R$ 的数目。

![](https://cdn.luogu.com.cn/upload/image_hosting/kde3oddz.png)

### Code

```cpp
#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <algorithm>

int t, n, m;
char map[518][518];

int main() {
	scanf("%d", &t);
	while(t--) {
		int ans = 0;
		scanf("%d %d", &n, &m);
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				std::cin >> map[i][j];
				if (i == n && j == m) continue;
				if (j == m && map[i][j] != 'D') ++ans;
				if (i == n && map[i][j] != 'R') ++ans;
			}	
		}
		printf("%d\n", ans);	
	}	
	return 0;
}	
```

---

## 作者：Ryo_Yamada (赞：1)

又是一道大水题。

分析一下题意：更改每个格子的行进方向使你不会走出地图，更改最少的格子使得你无论怎样都能到达 $(n, m)$。

注意到行进方向只有 `R` 代表向右一格和 `D` 代表向下一格，所以不需要考虑从左边和从上面走出地图的情况。而只需要修改最右一列和最下一排，从而不会走出地图。最右一列 `R` 的个数和最下一排 `D` 的个数的和即为最终答案。

$\text{Code}$：

```cpp
#include <iostream>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <set>

using namespace std;

char c[105][105];

int main() {
	int t;
	cin >> t;
	while(t--) {
		int n, m;
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; i++) 
			scanf("%s", c[i] + 1);
		int cnt = 0;
		for(int i = 1; i <= n; i++) {
			if(c[i][m] == 'R') cnt++;//最右一列'R'的数量
		}
		for(int i = 1; i <= m; i++) {
			if(c[n][i] == 'D') cnt++;//最下一排'D'的数量
		}
		printf("%d\n", cnt);//输出
	}
	return 0;
}

```


---

## 作者：kradcigam (赞：0)

题目大概就是在说，对于任意 $(i,j)$ 都有一个标记，如果标记为 $\texttt{D}$ j就是说到了这个格子会往下走，否则就是往右走。现在问你，如果最少要修改多少个格子的标记使得 $i\neq n$ 且 $j\neq m$，就一定能顺着格子的路径走到 $(n,m)$，不会出界。

我们发现一个格子的标记要么是向下走，要么是向右走，因此，不会出左边界和右边界。然后，就只有可能出下边界和右边界了，然后出下边界就一定是最后一行的格子标记为下（除了 $(n,m)$），同理出右边界一定最后一列的格子标记为右（除了 $(n,m)$）。

因此，答案为这些格子的个数。

```cpp
int work(){
	int n,m;read(n);read(m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			char ch;cin>>ch;
			if(ch=='R')a[i][j]=1;
			else a[i][j]=2;
		}
	int ans=0;
	for(int i=1;i<m;i++)
		if(a[n][i]==2)ans++;
	for(int i=1;i<n;i++)
		if(a[i][m]==1)ans++;
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：KSToki (赞：0)

由于每个格子不是 R 就是 D，所以物品每一步都在靠近 $(n,m)$。要使所有位置都能到 $(n,m)$ 处，我们不用管那么多细枝末节，所有格子最终都会到达第 $n$ 行或第 $m$ 列，所以我们只需要把第 $n$ 行和第 $m$ 列的方向调对即可。如果不都调对，那么至少没调对的那一格到不了。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m;
char Map[101][101];
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n>>m;
		int ans=0;
		for(register int i=1;i<=n;++i)
		    for(register int j=1;j<=m;++j)
		        cin>>Map[i][j];
		for(register int i=1;i<n;++i)
		    if(Map[i][m]=='R')
		        ++ans;
		for(register int i=1;i<m;++i)
		    if(Map[n][i]=='D')
		        ++ans;
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：引领天下 (赞：0)

首先我们考虑最后一行和最后一列（均不包括右下角的终点）。

显然最后一列只能全部为 `D` ，否则在最后一列的行李将出界。

同理最后一行只能全部为 `R` 。

于是至少需要将最后一列和最后一行分别全部改为 `D` 和 `R` 。

那么再考虑 1~n-1 行和 1~m-1 列。

由于每个位置要么为 `R` 要么为 `D` ，故中间的每一个行李最后必然停在最后一行或者最后一列。

而最后一行和最后一列我们刚才已经处理过了，是可以保证合法的。

那么答案就是让最后一行和最后一列合法所需要的次数咯。

```cpp
#include <bits/stdc++.h>
using namespace std;
string s[105];
int main(){
    register int t,n,m;
    scanf("%d",&t);
    while(t--){
        scanf("%d%d\n",&n,&m);
        for(int i=1;i<=n;i++)cin>>s[i];
        register int ans=0;
        for(int i=1;i<n;i++)ans+=s[i][m-1]=='R';
        for(int i=0;i<m-1;i++)ans+=s[n][i]=='D';
        printf("%d\n",ans);
    }
    return 0;
}
```

---

## 作者：Error_Eric (赞：0)

### 前言

同学说:诶这道题怎么叫"F\*\*k You"。

### 解法1
##### 并查集

我们这样思考：当这个机场没电的时候（别问我为什么没电，~~我把电闸拉了~~），每一个点都是单独的存在。也就是说，每一个点是一个单独的集合。

现在机场来电了，（也别问我为什么来电，~~我把电闸接上了~~）某个传送带开始转动了起来，于是这个传送带上的所有东西都会到它所指向的传送带 $(i,j+1)$ 或者 $(i+1,j)$ 上面 。

当然，其它传送带传过来的东西也会被传送到它所指向的传送带 $(i,j+1)$ 或者 $(i+1,j)$ 上面 。

这个操作，就可以理解为并查集的“并”，并查集的根节点就是这个传送带最终传送到的地方。

那么需要多少次操作呢？

其实，不难发现，当只有一个集合时，所有的行李都是可以到达柜台的。

当有多个集合时，这个集合的根节点（柜台除外）的右边或者下面，一定有一个是另外一个集合的。

改变一个集合的根节点的朝向，相当于合并了两个集合。

那么需要的操作数就是 $\text{集合数}-1$ 。

$Code$
```cpp
#include<iostream>
#include<algorithm>
#include<stdio.h>
using namespace std;
int fa[100*100+500],vfa[100*100+500];//代码采用二维化一维。
//也就是(x,y)变成(x*m+y)
char ch;
int find(int x){//寻找根节点
	if(fa[x]==x) return x;
	else return fa[x]=find(fa[x]);//路径压缩
}
void solve(){//核心代码
	int n,m,cnt=0;//n，m见题目，cnt记录个数
	scanf("%d%d",&n,&m);//输入
	for(int i=1;i<=n*m;i++)//初始化
		fa[i]=i,vfa[i]=0;//这里采用了二维化一维的方法
	for(int i=1;i<n*m;i++,ch=getchar()){
		while(ch!='R' and ch!='D')ch=getchar();//啊这该死的空格和回车。
		if(ch=='R' and i%m!=0)fa[find(i)]=find(i+1);//合并区间
		if(ch=='D' and i<=m*(n-1))	fa[find(i)]=find(i+m);//合并区间
     //注意这里的判断条件还要判断是否在边缘
     //如果往右的话就是自身加一
     //往下就是自身加n
	}
	scanf("%c",&ch);//啊这该死的结尾还有一个C。
	for(int i=1;i<=n*m;i++)
		if(!vfa[find(i)])cnt++,vfa[fa[i]]=1;//循环判断集合个数
	printf("%d\n",--cnt);//注意减一
}
int main(){
	int t;//多组数据
	scanf("%d",&t);//显然
	while(t--)solve();//显然
	//system("pause");
   return 0;
} 
```

### 解法2
##### 方法就是没有方法

行李没在柜台，行李去哪了呢？

行李掉下去了。

如果我们把所有会让行李掉下去的传送带转向，是不是就可以了呢？

是的，就可以了。

真的这么简单吗？

~~不好意思，真的这么简单。~~

$Code:$

```cpp
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<cmath>
using namespace std;
int n,m,t;
int main(){
     scanf("%d",&t);
     while(t--){
          scanf("%d%d",&n,&m);
          char ch;int cnt=0;
          for(int i=1;i<=n;i++){
               for(int j=1;j<=m;j++,ch=getchar()){
                    while(ch!='D' and ch!='R' and ch!='C')ch=getchar();
                         if(i==n and ch=='D') cnt++;
                         if(j==m and ch=='R') cnt++;
               }
          }
          printf("%d\n",cnt);
     }
} 
```

注意如果不止这两个方向，是不可以这么做的！

---

