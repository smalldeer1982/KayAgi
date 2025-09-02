# Tiling Challenge

## 题目描述

One day Alice was cleaning up her basement when she noticed something very curious: an infinite set of wooden pieces! Each piece was made of five square tiles, with four tiles adjacent to the fifth center tile:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1150B/ad6ce0df252a3db4eebc7f2ae8f0d041a8339ee0.png) By the pieces lay a large square wooden board. The board is divided into $ n^2 $ cells arranged into $ n $ rows and $ n $ columns. Some of the cells are already occupied by single tiles stuck to it. The remaining cells are free.Alice started wondering whether she could fill the board completely using the pieces she had found. Of course, each piece has to cover exactly five distinct cells of the board, no two pieces can overlap and every piece should fit in the board entirely, without some parts laying outside the board borders. The board however was too large for Alice to do the tiling by hand. Can you help determine if it's possible to fully tile the board?

## 说明/提示

The following sketches show the example boards and their tilings if such tilings exist:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1150B/4aa3066acea41ad93dd59954e4030c273a6b97d8.png)

## 样例 #1

### 输入

```
3
#.#
...
#.#
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
4
##.#
#...
####
##.#
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
5
#.###
....#
#....
###.#
#####
```

### 输出

```
YES
```

## 样例 #4

### 输入

```
5
#.###
....#
#....
....#
#..##
```

### 输出

```
NO
```

# 题解

## 作者：Nuyoah_awa (赞：1)

### 题目翻译
有一天，爱丽丝正在清理她的地下室，她注意到了一件非常奇怪的事情：一大堆木头！每一块由五块方形瓷砖组成，四块瓷砖与第五块中央瓷砖相邻：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1150B/ad6ce0df252a3db4eebc7f2ae8f0d041a8339ee0.png)

在碎片旁边放着一块大的方形木板。该板分为 $n^2$ 排列成 $n$ 行和 $n$ 列的单元。一些牢房已经被贴在上面的瓷砖占据了。剩下的细胞是自由的。爱丽丝开始怀疑她是否能用找到的碎片填满黑板。当然，每一块必须正好覆盖板上的五个不同的单元，没有两块可以重叠，并且每一块都应该完全适合板，没有一些部分位于板边界之外。然而，这块木板太大了，爱丽丝无法手工铺瓷砖。你能帮我确定是否可以完全平铺木板吗？
### 题目大意
给你一个由 `#` 和 `.` 组成的点阵图，求可以通过若干个不重复覆盖的“十字形”来补充所有的 `.`，问能否把所有 `.` 覆盖完？
### 分析题目
这道题的思路大体是一个贪心。

最后的答案是每个 `.` 都要变成 `#` 于是我们可以每次找到一个 `.` 并对其进行修改。那么问题来了，按照什么顺序找 `.` 呢？
因为每个 `.` 都是要到达的所以直接从左上到右下找就行了，而且这样找到的每一个没有被更改的点都在十字的最上方。


然后对于每一个 `.` 看从它往下建一个十字有没有障碍 `#`，如果没有障碍就覆盖一个十字（要不然当前这个点就没有机会改了）。

### 注意细节

1. 数组下标问题：枚举每一个点 $c_{x, y}$ 时这个点一定在 $1 \le x < n - 1$ 和 $1 < y \le n-1$ 范围内。
2. 枚举时请注意下标为负数的情况。

### code
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
int n, cntx[6] = {0, 1, 1, 1, 2}, cnty[6] = {0, -1, 0, 1, 0};
string s[55];
bool search(int x, int y)
{
	if(x < 0 || x >= n - 2 || y <= 0 || y >= n - 1)
		return false;
	for(int k = 0;k < 5;k++)
		if(s[x+cntx[k]][y+cnty[k]] == '#')
			return false;
	return true;
}
int main()
{
    cin >> n;
    for(int i = 0;i < n;i++)
        cin >> s[i];
    for(int i = 0;i < n;i++)	//注意统一下标
    {
        for(int j = 0;j < s[i].size();j++)
        {
        	if(s[i][j] == '#')
        		continue;
            if(search(i, j))
            {
            	for(int k = 0;k < 5;k++)
            		s[i+cntx[k]][j+cnty[k]] = '#';		//这两行相当于5个if
			}
            else		//如果放不了就不用再找了
            {
                cout << "NO";
                exit(0);
            }
        }
    }
    cout << "YES";
    return 0;
}
```

---

## 作者：Biuld (赞：1)

我们先把字符图转换成数字图， 即把 $.$ 转换为 $1$， 把其他字符转换为 $0$。

如：
```
#.#
...
###
```
转换为
```
010
111
000
```

我们可以从左上角开始遍历， 如果我们遇到了
```
01* //*代表未知
1**
***
```
这样的图形，就把 “十字形” 塞进去（即把 $1$ 变成 $0$）。 如果塞不下（位置上本来就是 $0$）， 就判断无解。 容易看出这样做是正确的。

代码：
```
#include<bits/stdc++.h>
using namespace std;
const int N = 55;

int n;
int a[N][N];
char c;

int sum; //sum 储存图中 '.' 的个数

int main(){
	ios::sync_with_stdio(false);
	
	cin >> n;
	
	for(int i = 1; i <= n; ++ i){
		for(int j = 1; j <= n; ++ j){
			cin >> c;
			a[i][j] = c == '.'; //把字符图转换为数字图
			sum += a[i][j];
		}
	}
	
/*	cout << sum << '\n';
	for(int i = 1; i <= n; ++ i){
		for(int j = 1; j <= n; ++ j){
			cout << a[i][j] << ' ';
		}cout << '\n';
	}*/
	
	if(sum % 5){ //如果不是 5 的倍数
		cout << "NO"; //肯定塞不满
		return 0;
	}
	
	for(int i = 1; i <= n; ++ i){ //从左上角开始遍历
		for(int j = 1; j <= n; ++ j){
			if(a[i][j] == 0 && a[i + 1][j] == 1 && a[i][j + 1] == 1){ //遇到上文说的图形
				if(a[i + 1][j + 1] == 1 && a[i + 2][j + 1] == 1 && a[i + 1][j + 2] == 1){ //能塞下
					a[i + 1][j] = a[i][j + 1] = a[i + 1][j + 1] = a[i + 2][j + 1] = a[i + 1][j + 2] = 0;
					sum -= 5;
				}
				else{ //塞不下
					cout << "NO"; //无解
					return 0;
				}
			}
		}
	}
	
	cout << (sum ? "NO" : "YES"); //这里好像有点多余，只是以防万一
	
	return 0;
}
```   
感谢观看

---

## 作者：ModestCoder_ (赞：0)

普及T2难度

枚举整个矩阵，如果有'.'，把它作为十字架的顶端放置，若不合法直接NO

都能合法就YES

Code：

```cpp
#include <bits/stdc++.h>
#define maxn 110
using namespace std;
int n, a[maxn][maxn];

inline int get(){
	char c = getchar();
	for (; c != '#' && c != '.'; c = getchar());
	return c == '.';
}

void work(int i, int j){
	if (!a[i][j] || !a[i + 1][j] || !a[i + 1][j - 1] || !a[i + 1][j + 1] || !a[i + 2][j]){
		puts("NO"); exit(0);
	}
	a[i][j] = a[i + 1][j] = a[i + 1][j - 1] = a[i + 1][j + 1] = a[i + 2][j] = 0;
}

int main(){
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j) a[i][j] = get();
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			if (a[i][j]) work(i, j);
	puts("YES");
	return 0;
}
```


---

## 作者：叶枫 (赞：0)

这道题。。。~~又是一道恶意评分题~~

### $\textbf{题解}$
- ~~爆搜~~。。。
- 找出十字形的点状图，然后暴力把所有十字形的点状图的点变成$\#$号型的，最后再所有都看一下有没有，再有点，有就输出$NO$,没有就输出$YES$

因为范围很小，爆搜完全在可接受范围内，所以直接暴力。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<string>
#include<queue>
#define re register
#define ll long long
#define maxn 300500
#define inf 2147483647
#define mod 998244353
using namespace std; 
inline int read(){
    int x=0,f=1; char ch=getchar();
    while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch)) {x=x*10+ch-48;ch=getchar();}
    return x*f;
}
struct node{
	int x,y;
}a[2510]; 
char c[55][55]; 
int n,k;
inline bool check(int i){
	if(a[i].x<0||a[i].x>=n) return false;
	if(a[i].y<0||a[i].y>=n) return false;
	if(c[a[i].x][a[i].y]!='.') return false;
	if(c[a[i].x+1][a[i].y]!='.') return false;
	if(c[a[i].x][a[i].y+1]!='.') return false;
	if(c[a[i].x-1][a[i].y]!='.') return false;
	if(c[a[i].x][a[i].y-1]!='.') return false; 
	return true;
}
signed main(){
	n=read();
	for(int i=0;i<n;i++)
	for(int j=0;j<n;j++){
		cin>>c[i][j];
		if(c[i][j]=='.'){
			a[++k].x=i; a[k].y=j;
		}
	}
	for(int i=0;i<k;i++)
		if(check(i)){
			c[a[i].x][a[i].y]='#';
			c[a[i].x+1][a[i].y]='#';
			c[a[i].x][a[i].y+1]='#';
			c[a[i].x-1][a[i].y]='#';
			c[a[i].x][a[i].y-1]='#';
		} 
	int flag=1;
	for(int i=0;i<n;i++){
	for(int j=0;j<n;j++){
		if(c[i][j]=='.') {flag=0;break;}		
		}
		if(flag==0)	break;
	}
	if(flag==1) return puts("YES"),0;
	else return puts("NO"),0;
	return 0;
}
```
$\sout\text{哎，洛谷何时能有压缩代码的功能呢？}$

---

## 作者：Erusel (赞：0)

对于每一个空白的点，以它作为十字架的顶点

如图：

```
#*#
...
#.#
```

图中打"*"的点即为当前扫描的点

判断一下十字架是否符合要求即可

代码：

```
#include<bits/stdc++.h>

#define rd(x) x=read()

using namespace std;

int n;
char a[55][55];

inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

inline void write(int x)
{
    if(x<0){putchar('-');x=-x;}
    if(x>=10)write(x/10);
    putchar(x%10+'0');
}


void check(int x,int y)
{
    if(x<1||x>n||y<1||y>n||a[x][y]=='#')
    {
        printf("NO\n");
        exit(0);
    }
    a[x][y]='#';
}//判断

int main()
{
    rd(n);
    for(int i=1;i<=n;i++)scanf("%s",a[i]+1);
    for(int i=1;i<=n;i++) 
        for(int j=1;j<=n;j++)
            if(a[i][j]=='.')
                check(i,j),check(i+1,j),check(i+2,j),check(i+1,j-1),check(i+1,j+1);//遍历十字架
    printf("YES\n");

    return 0;
}
```

---

## 作者：ztntonny (赞：0)

## 题意
给出一个由“#”和“.”组成的点阵图，求可以通过若干个不重复覆盖的“十字形”来补充所有的“.”，问能否把所有“.”覆盖完？
## 思路
从左上角开始遍历，把它转化成一个 $01$ 构成的二维数组，“.”转化成 $1$，剩下的是 $0$，再遍历一次，只要碰到 $1$ 就检查该点向下做一个十字是否都为 $1$，如果不是就一定覆盖不全结束，否则把十字都变成 $0$，继续，最后如果都填平没有结束过程序就可以。
```cpp
#include <bits/stdc++.h>
using namespace std;
int z[55][55];
int main()
{
	int s1 = 1 , s2 = 0 , s = 0 , a , b , i , h;
	char x;
	cin >> h;
	for ( int j = 1; j <= h; j++ )
	{
		for ( int i = 1; i <= h; i++ )
		{
			cin >> x;
			if ( x == '.' )
			z[i][j] = 1;//转化成二维数组
		}
	}
	for ( int f = 1; f <= h; f++ )
	{
		for ( int k = 1; k <= h; k++ )
		{
			if ( z[k][f] == 1 )
			{
				if ( z[k][f] && z[k - 1][f + 1] && z[k][f + 1] && z[k][f + 2] && z[k + 1][f + 1] )//找是否有十字
				z[k][f] = z[k - 1][f + 1] = z[k][f + 1] = z[k][f + 2] = z[k + 1][f + 1] = 0;//更改
				else
				{
					cout << "NO\n";//不行结束
					return 0;
				}
			}
		}
	}
	cout << "YES\n";//行
	return 0;
}
```

---

## 作者：_HiKou_ (赞：0)

初看以为是状压，再看觉得是 DFS，结果...

爆搜就可以了！可不能对不起 $3 \leq n \leq 50$ 的数据范围，$O(n^2)$ 是能过的！

根据题目，十字架是这样子的图形：

```
#.#
...
#.#
```

具体做法有两种：

- 首先都把字符转化成数字，# 转化成 $0$，而 $.$ 转化为 $1$。

- 第一种是找十字架最上面的那个点，如果这个点连同他下面的点无法组成十字架就输出 NO，否则就把下面连同它自己归零。如果搜完没有出现这种情况（不用再去搜一遍，因为前面已经把所有的点遍历一遍了，如果有剩下的点肯定已经输出 NO 了），就直接输出 YES。

- 第二种是看这个点的四周是不是都是点，如果是就一起归零。最后再搜一遍，如果有剩余的点那么输出 NO，否则输出 YES。

这里只给第一种做法的代码，如果感兴趣的话可以尝试第二种。

CODE：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int a[114][514],i,j;//恶臭数组
int main(){
	int n;
	scanf("%d",&n);
	for(i=1;i<=n;i++)
	for(j=1;j<=n;j++)
	{
		char x;
		cin>>x;
		if(x=='.')a[i][j]=1;//字符串转数字
	}
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		if(a[i][j]==1)
		{
			if(a[i+1][j]&&a[i+1][j-1]&&a[i+1][j+1]&&a[i+2][j])//判断十字架
			a[i][j]=a[i+1][j]=a[i+1][j-1]=a[i+1][j+1]=a[i+2][j]=0;//归零
			else
			{
				printf("NO");
				return 0;
			}
		}
	}
	
	printf("YES");
	return 0;
}
```

---

## 作者：Lacrymabre (赞：0)

题意翻译

给你一个由“#”和“.”组成的点阵图，求可以通过若干个不重复覆盖的“十字形”来补充所有的“.”，问能否把所有“.”覆盖完？

这道题乍一看是一个dfs，但是我们可以用$n^{2}$解决掉它。直接判断：

找到一个$.$点，判断是否满足其周围8格都是$#$，如果是，就填充，否则直接输出NO，结束程序。

当然，如果追求复杂度，在输入时判断，并且压入队列，避免无用的扫描，也可以跑得更快。

这里给出$n^2$写法

```
#include<iostream>
#include<cstdio>
#include<iomanip>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<queue>
#include<stack>
#include<vector>
#include<map>
#include<set>

#define ll long long
#define db double
#define MAX 0x7fffffff
#define init inline int
#define INF 0X3fffffff

using namespace std;

inline long long read()
{
    ll f=1,s=0;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')s=(s<<1)+(s<<3)+ch-'0',ch=getchar();
    return s*f;
}

char a[1001][1001];
ll n;

void dfs(int i, int j){
    if (!a[i][j]||!a[i+1][j]||!a[i+1][j-1]||!a[i+1][j+1]||!a[i+2][j]){
        puts("NO");exit（0);
    }
    a[i][j]=a[i+1][j]=a[i+1][j-1]=a[i+1][j+1]=a[i+2][j]=0;
}

int main(){
    scanf("%d", &n);
    getchar();
    for (int i=1;i<=n;i++)
    {
        for (int j=1;j<=n;j++){
        	char c=getchar();
    		for (;c!='#'&&c!='.';c=getchar());
    			a[i][j]=c=='.';
		}
	}
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++)
            if (a[i][j]) dfs(i, j);
    puts(YE3");
    return 0;
}
```


---

