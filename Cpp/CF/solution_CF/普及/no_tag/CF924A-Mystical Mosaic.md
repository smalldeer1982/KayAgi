# Mystical Mosaic

## 题目描述

There is a rectangular grid of $ n $ rows of $ m $ initially-white cells each.

Arkady performed a certain number (possibly zero) of operations on it. In the $ i $ -th operation, a non-empty subset of rows $ R_{i} $ and a non-empty subset of columns $ C_{i} $ are chosen. For each row $ r $ in $ R_{i} $ and each column $ c $ in $ C_{i} $ , the intersection of row $ r $ and column $ c $ is coloured black.

There's another constraint: a row or a column can only be chosen at most once among all operations. In other words, it means that no pair of $ (i,j) $ ( $ i<j $ ) exists such that ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF924A/970bfdc984412d650a4edcfe5e0a8df4329d1b0b.png) or ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF924A/74963b959d98ef5a1623c0fa6c3ddc72e6be47dd.png), where ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF924A/f53ec93ace7ac116d42268fc65398baf94289b39.png) denotes intersection of sets, and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF924A/a8551b5381914bb6ecc9b38259329c2377122e54.png) denotes the empty set.

You are to determine whether a valid sequence of operations exists that produces a given final grid.

## 说明/提示

For the first example, the desired setup can be produced by $ 3 $ operations, as is shown below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF924A/74e6b77ab65d49c640ecfae7cdd0e283eea435f7.png)For the second example, the desired setup cannot be produced, since in order to colour the center row, the third row and all columns must be selected in one operation, but after that no column can be selected again, hence it won't be possible to colour the other cells in the center column.

## 样例 #1

### 输入

```
5 8
.#.#..#.
.....#..
.#.#..#.
#.#....#
.....#..
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
5 5
..#..
..#..
#####
..#..
..#..
```

### 输出

```
No
```

## 样例 #3

### 输入

```
5 9
........#
#........
..##.#...
.......#.
....#.#.#
```

### 输出

```
No
```

# 题解

## 作者：Big_Dinosaur (赞：1)

分两步。

第一步：按行去重，将相同的行只留一个。如样例一变成：
```
.#.#..#.
.....#..
#.#....#
```
第三行与第一行相同，第五行与第二行相同，去掉。

第二步：设还剩 $k$ 行，无解情况当存在 $1\le i<j\le k$，这两行字符串存在 $0\le l<m$，第 $i$ 行与第 $j$ 行中下表为 $k$ 的字符都是 `#` 字符，否则无解。

#### AC Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
namespace Dino{
inline int r(){
int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+ch-48;ch=getchar();}return x*f;
}
int n,m,k;string s[66],ss[66];map<string,int>mp;
inline void _(){
  n=r(),m=r();
  for(int i=1;i<=n;++i){
  	cin>>s[i];++mp[s[i]];if(mp[s[i]]==1)ss[++k]=s[i];
  }
  for(int i=1;i<=k;++i)
  for(int j=1;j<i;++j)
  for(int l=0;l<m;++l)
  if(ss[i][l]=='#'&&ss[j][l]=='#'){puts("No");return;}
  cout<<"Yes";
}
}
signed main(){Dino::_();}
```

---

## 作者：过氧化氢_syq0057 (赞：1)

## Solution

好像是某场比赛的 T1。

题意：每次可以选择任意多行和任意多列，把这些行和列的交点标记为 ```#```。每行每列只能选择一次。给定一个元素全部为 ```.``` 的矩阵，问你是否可以利用任意次上述操作变成一个给定的矩阵，能则输出 ```Yes```，不能则输出 ```No```。

注意每行每列只能选一次，于是对于任意一行，我们一定要选择所有有 ```#``` 的列操作来达成给定矩阵。

于是题目转化为：对于任意两行，若它们存在 ```#``` 在同一列中且这两行完全一致，则可行，否则不可行。

时间复杂度其实远小于 $O(n^2m^2)$。

## Code
```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <map>
#include <algorithm>
#include <ctime>
#include <cstdlib>
using namespace std;
const int N = 55;
const int M = 200005;
#define ll long long
const int INF = 0x3f3f3f3f;
const int mod = 1000000007;
int n, m;
int a[N][N];
bool vis[N];
bool isok(int x, int y) {
	for (int j=1; j<=m; j++)
		if (a[x][j] != a[y][j])
			return 0;
	return 1;
}//两行是否完全一致
int main() {
	scanf("%d%d", &n, &m);
	getchar();
	char ch;
	for (int i=1; i<=n; i++) {
		for (int j=1; j<=m; j++) {
			ch = getchar();
			a[i][j] = (ch == '#');
		}
		getchar();
	}
	bool flag;
	for (int i=1; i<=n; i++) {
		if (vis[i]) continue;//匹配成功可以不再判断
		for (int j=1; j<=m; j++) {
			if (a[i][j]) {
				flag = 0;
				for (int k=i+1; k<=n; k++) {
					if (a[k][j]) {
						flag = 1;
						if (!isok(i, k)) {
							printf("No\n");
							return 0;
						}
						else vis[k] = 1;
					}
				}
				if (flag) break;//对于当前行我们已经匹配了所有其它行，如果匹配成功就可以退出了
			}
		}
	}
	printf("Yes\n");
	return 0;
}
```

---

## 作者：Tsz1024_AK (赞：0)

### 题意解析
有一个 $n \times m$ 的字符矩阵，初始全部为点，请问可以将其变成你输入的摸样吗？如果可以输出 `Yes`，否则输出 `No`。操作步骤：

选择任意多行和任意多列，把这些行和列的交点标记为井号，每行每列只能选择一次。

数据范围：$1 \le n,m \le 100$。
### 题目思路
注意每行每列只能选则一次，对于任意一行，要选择所有井号的列操作来变成输入导弹矩阵模样。简单来讲，就是对于任意两行，若它们存在井号在同一列中且这两行完全一致，则输出 `Yes`，否则输出 `No`。

时间复杂度：$O(n^2 \times m)$

判断两行是否完全一致：

```cpp
bool add(int x,int y){
	for(int i=1;i<=m;i++)
		if(a[x][j]!=a[y][j])
			return 0;
	return 1;
}
```

核心部分代码：

```cpp
for(int j=1;j<=m;j++){
	if(arr[i][j]){
		ok=0;
		for(int k=i+1;k<=n;k++){
			if(arr[k][j]){
				ok=1;
				if(!add(i,k)){
					printf("No\n");
					return 0;
				}else
					vis[k]=1;
			}
		}
		if(ok) break;
	}
}
```

---

## 作者：xuan_gong_dong (赞：0)

## 题面
[Mystical Mosaic](https://www.luogu.com.cn/problem/CF924A)
## 分析
我们不妨枚举行，并设第 $i$ 行上有井号的列存储在一个字符串上，比如第一个样例的第一列所产生的字符串为 $\texttt{247}$，第二列为 $\texttt{6}$。

然后我们考虑当前的第 $i$ 行是否合法，发现若符合一下两种情况之一即为合法：

1. 当前的字符串在 $1$ 到 $i-1$ 出现过（之前选的时候可以顺便把这一行也选了）。
2. 当前字符串第一次出现且当前字符串的每一个字符从未出现过（第一次选择这一行与这些列）。

直接枚举每一行即可，时间复杂度为 $O(n^2 \times m)$，可以通过。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
char mp[100][100];
map < string , int > mpp;
bool book[100];
int main()
{
	string tmp;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%s",mp[i]+1);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(mp[i][j]=='#')
			{
				tmp.clear();
				int flag=0;
				for(int k=j;k<=m;k++)
				{
					if(mp[i][k]=='#')
					{
						tmp+=char(k+'0');
						if(book[k])flag=1;
						book[k]=1;
					}
				}
//				cout<<i<<' '<<tmp<<endl;
				if(mpp[tmp]==0&&flag)
				{
					puts("No");
					return 0;
				}
				mpp[tmp]++;
				break;
			}
		}
	}
	puts("Yes");
	return 0;
}
```


---

## 作者：Fu_Da_Ying (赞：0)

## [原题链接](https://www.luogu.com.cn/problem/CF924A)
## 题意：
每次可以选择任意多行和任意多列，把这些行和列的交点标记为 ```#```。每行每列只能选择一次。给定一个元素全部为 ```.``` 的矩阵，问你是否可以利用任意次上述操作变成一个给定的矩阵，能则输出 ```Yes```，不能则输出 ```No```。
## 思路：
注意每行每列只能选一次，于是对于任意一行，我们一定要选择所有有 ```#``` 的列操作来达成给定矩阵。

于是题目转化为：对于任意两行，若它们存在 ```#``` 在同一列中且这两行完全一致，则可行，否则不可行。
## Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m;
bool a[61][61],vis[61];
bool isok(int x, int y){
	for(int i=1;i<=m;i++){
		if(a[x][i]!=a[y][i]){
			return 0;
		}
	}
	return 1;
}//用于判断两行是否完全一致
int main(){
	scanf("%lld%lld",&n,&m);
	getchar();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(getchar()=='.'){
				a[i][j]=0;
			}else{
				a[i][j]=1;
			}
		}
		getchar();
	}
	bool flag;
	for(int i=1;i<=n;i++){
		if(vis[i]!=0){//此行匹配成功可以不再判断
		    continue;
		}
		for(int j=1;j<=m;j++){
			if(a[i][j]!=0){
				flag=0;
				for(int k=i+1;k<=n;k++) {
					if(a[k][j]!=0){
						flag=1;
						if(isok(i,k)==0){
							printf("No");
							return 0;
						}else{
						    vis[k]=1;
						}
					}
				}
				if(flag!=0){//对于当前行我们已经匹配了所有其它行，如果匹配成功就可以退出了
				    break;
				}
			}
		}
	}
	printf("Yes");
    return 0;
}
```

---

