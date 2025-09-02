# Fox and Cross

## 题目描述

Fox Ciel has a board with $ n $ rows and $ n $ columns. So, the board consists of $ n×n $ cells. Each cell contains either a symbol '.', or a symbol '\#'.

A cross on the board is a connected set of exactly five cells of the board that looks like a cross. The picture below shows how it looks.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF389B/5ccac31668e0d529fa8a5f9e69b4dcfcf1f3b650.png)Ciel wants to draw several (may be zero) crosses on the board. Each cross must cover exactly five cells with symbols '\#', and any cell with symbol '\#' must belong to some cross. No two crosses can share a cell.

Please, tell Ciel if she can draw the crosses in the described way.

## 说明/提示

In example 1, you can draw two crosses. The picture below shows what they look like.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF389B/2961c8465879f5caacf5ebd47c02d06b75cd444e.png)In example 2, the board contains 16 cells with '\#', but each cross contains 5. Since 16 is not a multiple of 5, so it's impossible to cover all.

## 样例 #1

### 输入

```
5
.#...
####.
.####
...#.
.....
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
4
####
####
####
####
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
6
.#....
####..
.####.
.#.##.
######
.#..#.
```

### 输出

```
YES
```

## 样例 #4

### 输入

```
6
.#..#.
######
.####.
.####.
######
.#..#.
```

### 输出

```
NO
```

## 样例 #5

### 输入

```
3
...
...
...
```

### 输出

```
YES
```

# 题解

## 作者：xtr169 (赞：1)

一道字符串操作题。

看到好多人用 dfs 做，我发一篇纯字符串操作的吧。

我们可以双重循环，遇到十字就换成空的，这样暴力做，最终判断是否有井号。如果有就打 NO ，没有就 YES 。

输入代码如下：
```cpp
	int n;
	char tmp;
	cin>>n;
	char s[105][105];
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			cin>>s[i][j];
		}
	}
```
还有判断的方法如下：

```cpp
for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(s[i][j]=='#'&&s[i][j-1]=='#'&&s[i][j+1]=='#'
			&&s[i-1][j]=='#'&&s[i+1][j]=='#')//判断是否有十字
			{
				s[i][j]='.';
				s[i][j-1]='.';
				s[i][j+1]='.';
				s[i-1][j]='.';
				s[i+1][j]='.';
           //有的话全换成'.'
			}
		}
	}
```

和最后的判断+输出：

```cpp
for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(s[i][j]=='#')//只要有#说明没有全部被替换。输出NO
			{
				cout<<"NO";
				return 0;
			}
		}
	}
	cout<<"YES";
```


下面是代码，具体注释在代码里：
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	char tmp;
	cin>>n;
	char s[105][105];
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			cin>>s[i][j];
		}
	}
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(s[i][j]=='#'&&s[i][j-1]=='#'&&s[i][j+1]=='#'
			&&s[i-1][j]=='#'&&s[i+1][j]=='#')//判断是否有十字
			{
				s[i][j]='.';
				s[i][j-1]='.';
				s[i][j+1]='.';
				s[i-1][j]='.';
				s[i+1][j]='.';
           //有的话全换成'.'
			}
		}
	}
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(s[i][j]=='#')
			{
				cout<<"NO";
				return 0;//是no就直接退出
			}
		}
	}
	cout<<"YES";
   //判断加输出
	return 0;
}
```

---

## 作者：hcl156 (赞：0)

# SOULUTION


可以这样想，考虑到十字架这么特殊的图案，以每个十字架的最高点为判断的起始点，也就是说，当能画一个十字架时，绝对是首先遇上它的最高点的，然后判断该点的正下方连续两点，还有下方第一个点紧挨着左右两边是否也为 # 即可。另外一个要考虑的地方是肯定不能画十字架的情况，每一列的第一个和最后一个字符如果为 # 是不能画十字架的，还有，倒数后两行出现 # 也是不行的。

# CODE

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 100 + 10;
char cell[maxn][maxn];
int main(){
    int i, j, n, flag;
    while (scanf("%d", &n) != EOF){
        for (i = 0; i < n; i++)
            scanf("%s", cell[i]);
        flag = 0;
        for (i = 0; i < n && !flag; i++){
            for (j = 0; j < n && !flag; j++){
                if (cell[i][j] == '#'){
                    if (j == 0 || j == n-1 || i >= n-2  || cell[i+1][j] != '#' || cell[i+1][j-1] != '#' || cell[i+1][j+1] != '#' || cell[i+2][j] != '#'){
                        printf("NO\n");
                        flag = 1;
                    }
                    else{
                         cell[i+1][j] = '.';
                         cell[i+1][j-1] = '.';
                         cell[i+1][j+1] = '.';
                         cell[i+2][j] = '.';
                    }
                }
            }
        }
        if (!flag)printf("YES\n");
    }
    return 0;
}
```


---

## 作者：xmkevin (赞：0)

## 题目大意

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF389B/5ccac31668e0d529fa8a5f9e69b4dcfcf1f3b650.png)

本题的意思就是输入一个 $n \times n$ 的矩阵，其中有 `#` 和 `.`。每次遇到如上图所示的图形时就把它去掉，问最后能不能去掉全部的 `#`。

## 解题思路

为了方便，我们把 `#` 看成 $1$，把 `.` 看成 $0$。

我们定义 $tot$ 为 $1$ 的个数，依次判断每个格子，遇到上面的情况就把相邻的 $1$ 变成 $0$。

最后判断 $tot$ 是否为 $0$，如果是则输出 `YES`，否则输出 `NO`。

## 代码

```
#include <iostream>
using namespace std;

char a[105][105];
bool b[105][105];
int n;

int main() {
	int ans = 0;
	for(int i = 1; i <= n; i++) {
		for(int j = 0; j <= n; j++) {
			cin >> a[i][j];
			b[i][j] = a[i][j] == '#'?1:0;
			if(b[i][j]) ans++;
		}
	}
	for(int i = 2; i < n; i++) {
		for(int j = 2; j < n; j++) {
			if(b[i][j] == 1 && b[i - 1][j] == 1 && b[i][j - 1] == 1 && b[i + 1][j] == 1 && b[i][j + 1] == 1) {
				b[i][j] = b[i - 1][j] = b[i][j - 1] = b[i + 1][j] = b[i][j + 1] = 0;
				ans -= 5;
			}
		}
	}
	if(ans) cout << "NO\n";
	else cout << "YES\n";
}
```

---

## 作者：_lzy_ (赞：0)

## 题目大意：
题目给出你一个 $n \times n$ 的矩阵，现在询问你矩阵能分解为几个如下图所表示的十字形。
```
x # x
# # #
x # x
```
## 解题思路：
将这个题目给的矩阵全部遍历一遍，直接去暴力寻找有多少个这样的十字架，如有的话就直接将他抹去，遍历完以后再去看他每一个点位上是否还有没有抹掉的 # ，如果有的话，那就输出 NO ，否则输出 YES 就行了。
## 代码:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int f[101][101];
bool check(){//判断是否清空的函数
	for(int i=1;i<=n;i++)	
		for(int k=1;k<=n;k++)	
			if(f[i][k]==1)
				return false;
	return true;
}
bool checkf(int x,int y){//判断是否构成十字架
	if(f[x][y]&&f[x+1][y])
		if(f[x-1][y]&&f[x][y+1])
			if(f[x][y-1])
				return true;
	return false;
}
void cleaning(int x,int y){//清空十字架
	f[x][y]=0;
	f[x-1][y]=0;
	f[x+1][y]=0;
	f[x][y-1]=0;
	f[x][y+1]=0;
}
int main()
{
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++)
		for(int k=1;k<=n;k++){
			char c;
			cin>>c;
			if(c=='#')f[i][k]=1;
		}
	for(int i=2;i<=n;i++)
		for(int k=2;k<=n;k++)
			if(checkf(i,k))
				cleaning(i,k);
	if(check()){
		puts("YES");
		return 0;
	}
	puts("NO");
	return 0;
}


```


---

## 作者：guozhetao (赞：0)

## 题意

有 个 $n \times n$ 的矩阵，问能否分解成若干个由 `#`  组成的图形。
```
x # x
# # #
x # x
```

## 思路

直接按题意模拟，每找到一个这种图形就把它从地图上抹去，最后看图上还有没有图形。

为了方便，我们可以先设置一个 $ans$ 为 `#` 的个数，如果 $ans \bmod 5$ 再继续，否则直接输出否。每判断出一个这种图形 $ans \gets ans - 5$，这样就不用想其它题解那样一遍一遍循环找是否都抹去了，只需要判断 $ans$ 为不为 $0$ 就可以了。

注意一定要大写，不然[会错](https://www.luogu.com.cn/record/84333043)。

## 代码
（本代码已经测试过，是[正确](https://www.luogu.com.cn/record/84333169)的）
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
char k[101][101];
bool p[101][101];
int ans = 0;
int main() {
	scanf("%d",&n);
	for(int i = 1;i <= n;i++) {
		for(int j = 1;j <= n;j++) {
			cin>>k[i][j];
			if(k[i][j] == '.'){
				p[i][j] = 0;//char改成bool
			}
			else{
				p[i][j] = 1;
				ans++;
			}
		}
	}
	if(ans % 5 != 0) {//直接退出
		printf("NO\n");
		return 0;
	}
	for(int i = 2;i < n;i++) {//避免越界 
		for(int j = 2;j < n;j++) {//同上
			if(p[i][j] && p[i - 1][j] && p[i + 1][j] && p[i][j + 1] && p[i][j - 1]) {
				p[i][j] = 0;
				p[i - 1][j] = 0;
				p[i + 1][j] = 0;
				p[i][j + 1] = 0;
				p[i][j - 1] = 0;
				ans -= 5;
			}
		}
	}
	if(ans) {
		printf("NO\n");
		return 0;
	}
	printf("YES\n");//特别注意要大写
	return 0;
}

```


---

## 作者：Coros_Trusds (赞：0)

[更好的阅读体验](https://www.cnblogs.com/Coros-Trusds/p/15569884.html)

# 题目大意

有一个 $n\times n$ 的矩阵，每个点为 `.` 或 `#` ，问该矩阵是否能够分解成多个如下图的由 `#` 组成的十字形：

```plain
x # x
# # #
x # x
```
`x` 表示任意字母。

# 题目分析

直接模拟。

读入字符数组后，按顺序遍历每个点，判断该点是否为十字形，如果是，则把它们改为 `.`，这样就避免了重复的问题。

当然也可以用一个标记数组来表示该十字形是够被算过。

注意一下边界问题即可。

# 代码

```cpp
//2021/11/17

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include <cstdio>

#include <climits>//need "INT_MAX","INT_MIN"

#define enter() putchar(10)

#define debug(c,que) cerr<<#c<<" = "<<c<<que

#define cek(c) puts(c)

#define blow(arr,st,ed,w) for(register int i=(st);i<=(ed);i++)cout<<arr[i]<<w;

#define speed_up() std::ios::sync_with_stdio(false)

namespace Newstd
{
	inline int read()
	{
		char c;
		bool flag=false;
		while((c=getchar())<'0' || c>'9')
		{
		    if(c=='-') flag=true;
		}
		int res=c-'0';
		while((c=getchar())>='0' && c<='9')
		{
		    res=(res<<3)+(res<<1)+c-'0';
		}
		return flag?-res:res;
	}
	inline void print(int x)
	{
		if(x<0)
		{
			putchar('-');x=-x;
		}
		if(x>9)
		{
			print(x/10);
		}
		putchar(x%10+'0');
	}
}

using namespace Newstd;

using namespace std;

const int ma=105;

char mp[ma][ma];

int n;

inline bool calc(int x,int y)
{
	return (mp[x][y]=='#' && mp[x-1][y]=='#' && mp[x+1][y]=='#' && mp[x][y-1]=='#' && mp[x][y+1]=='#');
}

inline void solve(int x,int y)
{
	mp[x][y]=mp[x-1][y]=mp[x][y-1]=mp[x+1][y]=mp[x][y+1]='.';
}

int main(void)
{
	n=read();
	
	for(register int i=0;i<n;i++)
	{
		scanf("%s",mp[i]);
	}
	
	for(register int i=1;i<n-1;i++)
	{
		for(register int j=1;j<n-1;j++)
		{
			if(calc(i,j)==true)
			{
				solve(i,j);
			}
		}
	}
	
	for(register int i=0;i<n;i++)
	{
		for(register int j=0;j<n;j++)
		{
			if(mp[i][j]=='#')
			{
				puts("NO");
				
				return 0;
			}
		}
	}
	
	puts("YES");
	
	return 0;
}
```

---

## 作者：JCLinux (赞：0)

不要被这个题吓到，其实不难。

要注意解体的关键：**任何#都要被使用，且只能属于某一个十字，不共用**。

我们的思路是遇到一个#，它的周围（上下左右）都有#时，直接认定它是一个十字，一并将他们抹去，不必考虑它周围的#属于别的十字，因为这样，它自身就不完整了，会有#剩余。**因此如果能做到不剩 # ，就一定能这样贪心的做。**

上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
bool board[102][102];
int n;
int main(){
	cin >>n;
	scanf("%d",&n);
	char inp;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cin >>inp;
			if(inp=='#')board[i][j]=1;
			else board[i][j]=0;
		}
	}
	for(int i=2;i<n;i++){
		for(int j=2;j<n;j++){
			if(board[i][j]&&board[i-1][j]&&board[i+1][j]&&board[i][j-1]&&board[i][j+1]){
				board[i][j]=board[i-1][j]=board[i+1][j]=board[i][j-1]=board[i][j+1]=0;
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(board[i][j]){
				cout <<"NO";
				return 0;
			}
		}
	}
	cout <<"YES";
	return 0;
}
```


---

## 作者：千年陈皮精 (赞：0)

我把思路放在代码里了，自己看。
### 代码
```
#include<bits/stdc++.h>
using namespace std;
int n,b[205][205],sum,ans;
char a[205][205];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			cin>>a[i][j]; //输入字符。 
			if(a[i][j]=='#')sum++; //记录 # 的数量，方便最后判断。 
		}
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			if(a[i+1][j]=='#'&&a[i-1][j]=='#'&&a[i][j+1]=='#'&&a[i][j-1]=='#'&&a[i][j]=='#') //判断 # 是不是十字形。 
			{
				if(b[i+1][j]!=1&&b[i-1][j]!=1&&b[i][j+1]!=1&&b[i][j-1]!=1&&b[i][j]!=1) //如果 # 是十字形，就判断有没有被标记。 
				{
					b[i+1][j]=1; b[i-1][j]=1;
					b[i][j+1]=1; b[i][j-1]=1;
					b[i][j]=1; //标记。 
					ans+=5; //记录被标记的 # 的数量，方便最后判断。 
				}
			}		
		}
	if(sum==0||(ans==sum&&sum%5==0))cout<<"YES"; //判断所有的 # 是不是都被标记了，是就输出YES。 
	else cout<<"NO"; //否则就输出NO。 
	
	return 0; //完结撒花。 
}
```


---

