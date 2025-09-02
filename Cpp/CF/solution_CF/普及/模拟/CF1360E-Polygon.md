# Polygon

## 题目描述

Polygon is not only the best platform for developing problems but also a square matrix with side $ n $ , initially filled with the character 0.

On the polygon, military training was held. The soldiers placed a cannon above each cell in the first row and a cannon to the left of each cell in the first column. Thus, exactly $ 2n $ cannons were placed.

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1360E/af538d3417e3bff02f7ca9d4302ffeb8985b4df9.png)Initial polygon for $ n=4 $ . Cannons shoot character 1. At any moment of time, no more than one cannon is shooting. When a 1 flies out of a cannon, it flies forward (in the direction of the shot) until it collides with a polygon border or another 1. After that, it takes the cell in which it was before the collision and remains there. Take a look at the examples for better understanding.

More formally:

- if a cannon stands in the row $ i $ , to the left of the first column, and shoots with a 1, then the 1 starts its flight from the cell ( $ i, 1 $ ) and ends in some cell ( $ i, j $ );
- if a cannon stands in the column $ j $ , above the first row, and shoots with a 1, then the 1 starts its flight from the cell ( $ 1, j $ ) and ends in some cell ( $ i,         j $ ).

For example, consider the following sequence of shots:

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1360E/b0a2a2240d9a0a11c84c2c0dd9be686db3e431b3.png) 1. Shoot the cannon in the row $ 2 $ . 2. Shoot the cannon in the row $ 2 $ . 3. Shoot the cannon in column $ 3 $ .

You have a report from the military training on your desk. This report is a square matrix with side length $ n $ consisting of 0 and 1. You wonder if the training actually happened. In other words, is there a sequence of shots such that, after the training, you get the given matrix?

Each cannon can make an arbitrary number of shots. Before the training, each cell of the polygon contains 0.

## 说明/提示

The first test case was explained in the statement.

The answer to the second test case is NO, since a 1 in a cell ( $ 1, 1 $ ) flying out of any cannon would continue its flight further.

## 样例 #1

### 输入

```
5
4
0010
0011
0000
0000
2
10
01
2
00
00
4
0101
1111
0101
0111
4
0100
1110
0101
0111```

### 输出

```
YES
NO
YES
YES
NO```

# 题解

## 作者：Zhoumy (赞：6)

首先，我们需要知道什么是一个**合法的炮弹**。炮弹到边界一定会停，然后一个炮弹碰到另一个停止的炮弹才会停，所以炮弹停的地方要么是边界，要么是碰到的已停止的炮弹的位置在本炮弹发射来的方向$-1$。   
**思路**：我们可以遍历每一个位置，看是否符合一个合法炮弹。如果有一个不合法的炮弹，那么就不能通过炮台打出来
```
#include<iostream>
using namespace std;
int w,n;
bool die;
char a[55][55];
int main(){
	cin>>w;
	for(int i=1;i<=w;i++){
		cin>>n;
		for(int j=1;j<=n;j++)for(int k=1;k<=n;k++)cin>>a[j][k];
		for(int j=1;j<n;j++)for(int k=1;k<n;k++)if(a[j][k]=='1'&&a[j][k+1]=='0'&&a[j+1][k]=='0')die=1;//因为一个在边界的炮弹一定是合法的，不用判断，所以是<n
		if(die==0)cout<<"YES"<<endl;
		else cout<<"NO"<<endl;
		die=0;
	}
	return 0;
}
```


---

## 作者：_xbn (赞：2)

发一个爆搜题解。

由于题目约束，最下和最右的子弹肯定是合法的，于是我们可以从最下方和最右方的每一颗子弹开始向左上方搜索，遇到没有搜过的子弹就加入答案。

这样搜所得的答案是合法的子弹数量，如果子弹总数大于合法子弹数量，说明有子弹不能通过炮台打出来，矩阵不合法。否则矩阵合法。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2002, mod = 1e9 + 7;
const int dx[3] = {0, -1, 0}, dy[3] = {0, 0, -1};
int n, m, l, r, p, t, k, ans, sum, tot, cnt, a[N], b[102], c[N], d[N], vis[52][52];
char s[52][52];
inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
	{
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while('0' <= ch && ch <= '9')
	{
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
void dfs(int x, int y)
{
    vis[x][y] = 1;
    for (int i = 1; i <= 2; i++)
    {
        int gx = x + dx[i], gy = y + dy[i];
        if(s[gx][gy] == '1' && !vis[gx][gy])
        {
            vis[gx][gy] = 1;
            sum++;
            dfs(gx, gy);
        }
    }
}
int main()
{
    int T = read();
    while (T--)
    {
        n = read();
        tot = 0 ;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++) 
            {
                cin >> s[i][j];
                if(s[i][j] == '1') tot++;
            }
        }
        sum = 0;
        memset(vis, 0, sizeof(vis));
        for (int i = 1; i <= n; i++)
        {
            if(s[n][i] == '1') sum++, dfs(n, i);
        }
        for (int i = 1; i <= n - 1; i++)
        {
            if(s[i][n] == '1' && !vis[i][n]) sum++, dfs(i, n);
        }
        if(sum == tot) puts("YES");
        else puts("NO");
    }
    return 0;
}
```


---

## 作者：Warriors_Cat (赞：2)

## CF1360E

一道很好的思维题，当然也可以找规律~

首先，根据题意，发射 $1$ 后会被第一个 $1$ 或者边界挡住，所以每个 $1$ 的右边或下边非边界即 $1$。然后我们就可以处理掉 `NO` 的情况了。

接下来说一下如果全部 $1$ 的右边或下边是 $1$ 或边界就可以构造，大概是一种递归的思想，就是找到一个 $1$ 就向它的右边或下边搜索，搜到边界为止，然后回溯按顺序填上 $1$ 即可。大家也可以自己多找几个例子试试。

这样的话这道题的实现就很简单了，主要难度是在思维上。

下面是代码：

### $Code:$

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
inline int read(){
	int x = 0, f = 1; char ch = getchar();
	while(ch < '0' || ch > '9'){ if(ch == '-') f = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9'){ x = x * 10 + (ch ^ 48); ch = getchar(); }
	return x * f;
}
#define F(i, a, b) for(int i = a; i <= b; ++i)
#define R(i, a, b) for(int i = a; i >= b; --i)
int t, n, a[60][60];
int main(){
	scanf("%d", &t);
	while(t--){
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i){
			for(int j = 1; j <= n; ++j){
				scanf("%1d", &a[i][j]);
			}
		}//这里用了一下 scanf 的小技巧
		for(int i = 1; i <= n; ++i) a[n + 1][i] = 1, a[i][n + 1] = 1;
		a[n + 1][n + 1] = 1;//先判了边界的 1，后面好处理。
		bool flag = 1;
		for(int i = 1; i <= n; ++i){
			for(int j = 1; j <= n; ++j){
				if(a[i][j] == 1 && !a[i + 1][j] && !a[i][j + 1]){
					flag = 0;
					puts("NO");
					break;
				}//如果右边下边全是 0 就挂了
			}
			if(!flag) break;
		}
		if(flag) puts("YES");//否则一定可以构造
	}
	return 0;
}

```


---

## 作者：Aisaka_Taiga (赞：1)

## 基本思路

本题中的炮弹有一个特点，如果他的下边或者右边是有炮弹了，那么他就是合法的，否则就不合法，右边界和下边界比较特殊，不需要考虑此条件，所以枚举的时候枚举到 $n-1$ 就好了。需要注意的是，他输入的 $01$ 矩阵之间是没有空格的，所以不能 int 定义数组，要用 char 类型的。~~你告诉我哪里还是代码部分?~~

附：学长说用 int 的数组存也可以，但需要用这个：
```cpp
scanf("%1d",&a[i][j]); 
```

## code
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,flag;//flag判断是否合法 
char a[101][101];//a存放输入的01矩阵 
int main()
{
	cin>>t;
	while(t--)
	{
		flag=0;//每次都要重置一下 
		cin>>n;
		for(int i=1;i<=n;i++)
		  for(int j=1;j<=n;j++)
		    cin>>a[i][j]; 
		for(int i=1;i<n;i++)
		  for(int j=1;j<n;j++)
		  	  if(a[i][j]=='1'&&a[i+1][j]=='0'&&a[i][j+1]=='0')//如果不合法 
		  	  	flag=1;//标记 
		if(!flag)cout<<"YES"<<endl;
		else cout<<"NO"<<endl;
	}
	return 0;
}
```


---

## 作者：Eraine (赞：1)

# 题目标签
[CF1360E](https://www.luogu.com.cn/problem/CF1360E)
## 标签
模拟
## 难度
普及/提高-
# 思路分析
## 思路一

时间复杂度 $O(n^2t)$

说实在，这一题其实很简单。一道纯模拟题。我们先来分析一下题目：“且遇到边界后会停止，遇到一个停止的子弹也会停止”。这个点可以说明每一个子弹的最终坐标只可能在边界上，或者右方/下方有一个子弹。如果这些条件都不满足，这种答案是错误的。因为我们来想想，炮弹往右射出去，必定要碰到边界和子弹才会停下来。可出现了还没碰到边际和子弹就停下来的情况是不可能的。所以只需判断是否存在上述情况即可。当有出现这种情况时，则停止循环，输出 $NO$ 。否则，输出 $YES$ 。

从代码来分析，首先要求输入一个边长为 $n$  的正方形矩阵，那每次循环只需要把这个矩阵的所有数组循环一次就好了。先来分析一下在边界的情况。如何判断是否在边界呢？其实很简单。只要把矩阵的右面一层和下面一层全部用 $1$ 扫过一边就OK了。

```cpp
	//这些是用1扫过的
	for(int i=1;i<=n;i++)a[i][n+1]=1;
	for(int i=1;i<=n;i++)a[n+1][i]=1;
```
把在矩阵范围内的 $1$ 判断完毕就好了。出现这种情况的时候是右面和下面都为 $0$ 的时候。这样就简单了。

```cpp
	bool g=true;//这个bool是用来判断是否有出现 NO 的情况
	for(int i=1;i<=n&&g;i++)for(int j=1;j<=n&&g;j++)if(a[i][j]==1&&!(a[i+1][j]==1||a[i][j+1]==1)){cout<<"NO"<<endl;g=false;}
	if(g)cout<<"YES"<<endl;
```
# 错因分析
1.把 $0$ 都当做 $1$ 来扫了，这样是错的！！！只有当前有子弹时才扫，没子弹时扫了没有意义。~~（似乎也就这一个错因）~~ 
# AC代码

```cpp
#include<iostream>
using namespace std;
int main()
{
int t;
cin>>t;
for(int h=1;h<=t;h++){
	bool g=true;
	string b;
	int a[55][55]={0},n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>b;
		for(int j=1;j<=n;j++)a[i][j]=b[j-1]-48;
	}
	for(int i=1;i<=n;i++)a[i][n+1]=1;
	for(int i=1;i<=n;i++)a[n+1][i]=1;
	for(int i=1;i<=n&&g;i++)for(int j=1;j<=n&&g;j++)if(a[i][j]==1&&!(a[i+1][j]==1||a[i][j+1]==1)){cout<<"NO"<<endl;g=false;}
	if(g)cout<<"YES"<<endl;
}	
return 0;
}
```


---

## 作者：rui_er (赞：1)

拿到这题一头雾水，找找规律。

按照游戏规则，一个数的右侧和下侧必须有数才可能被大炮发射到这里。

看到样例，发现如果去掉最后一行以及最后一列，剩余的所有 $1$ 的右侧或下侧的格子有 $1$，就是可以完成；反之不能。

大胆猜测：除了最右列与最下行，如果每个 $1$ 右侧或下侧都有 $1$，则可以完成；有一个 $1$ 右侧下侧均没有 $1$ 就不能完成。

考试时直接交了，没有证明正确性，发现 PP 了。现在口胡一个，不是特别严谨，可以画画图试着理解：

- 如果一个 $1$ 右侧有 $1$，可以通过左侧大炮发射过来。
- 如果一个 $1$ 下侧有 $1$，可以通过上方大炮发射过来。
- 最右列和最下行一定可以达到。

类似数学归纳法的思想，证明上面的猜测。

代码：

```cpp
//By: Luogu@rui_er(122461)
#include <bits/stdc++.h>
using namespace std;

int T, n, a[55][55];

int main() {
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i=1;i<=n;i++) {
			for(int j=1;j<=n;j++) {
				char c = getchar();
				while(!isdigit(c)) c = getchar();
				a[i][j] = c - '0';
			}
		}
		bool book = true;
		for(int i=1;i<n;i++) {
			for(int j=1;j<n;j++) {
				if(a[i][j] && !a[i][j+1] && !a[i+1][j]) {
					book = false;
					break;
				}
			}
			if(!book) break;
		}
		if(book) puts("YES");
		else puts("NO");
	}
	return 0;
}
```

---

## 作者：lu_fish (赞：0)

## CF1360E题解

思路：对每一个点进行判断，如果这个点下面和右边是 0 那就可以直接判断是 NO （不包括最右和最下）。

**WHY？ **
因为 炮弹遇到边界后会停止，遇到一个停止的子弹也会停止，显然当下方和右方的地方都为 0 是不可能停下的。

code：
```cpp
#include<iostream>
using namespace std;
int t;
int main(){
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        char f[52][52];
        bool pd=1;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)cin>>f[i][j];
        for(int i=1;i<n&&pd;i++)//注意这里不需要考虑最右边和最下边的点
            for(int j=1;j<n&&pd;j++){
                if(f[i][j]=='1'){
                    if(f[i+1][j]=='0'&&f[i][j+1]=='0'){//下，右均为0.
                        cout<<"NO\n";
                        pd=0;
                    }
                }
            }
        if(pd){
            cout<<"YES\n";
        }
    }
}
```

---

## 作者：mot1ve (赞：0)

**先说出结论，如果这个图的某点是1并且它的右边的点和下面的点都是0，那么这个图就不合法
（最后一行和最后一列的点除外）**

看到第一篇题解证明居然用到了数学归纳法，显然我不知道这是个啥，我有一种非常简单的证明方法供大家参考

**一个炮弹打过去，停下的条件是遇到障碍，（也就是得有个东西承接它）这个障碍可以是墙也可以是之前打过去的炮弹**

这就证明完了，最后一行和最后一列的点不用考虑，因为它靠墙，肯定会停下来，如果一个点不在最后一行和最后一列并且它的右边和下面的点都是0，那么就没有任何可以承接它的东西,所以必定不合法

```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int T,n;
int a[60][60];
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			string s;
			cin>>s;
			for(int j=0;(unsigned)j<s.length();j++)
			{
				a[i][j+1]=s[j]-'0';
			}
		}
		int flag=0;
		for(int i=1;i<=n-1;i++)
		{
			for(int j=1;j<=n-1;j++)
			{
				if(a[i][j]==1&&(!a[i+1][j]&&!a[i][j+1]))
				{
					printf("NO\n");
					flag=1;
				}
				if(flag==1)
				break;
			}
			if(flag==1)
			break;
		}
		if(flag==0)
		{
			printf("YES\n");
		}
	}
	return 0;
}

---

## 作者：45dino (赞：0)

突然发现那时候的 E 好简单呀QAQ

首先由题意得，在最右边和最下边的所有点都是合法的。

然后推理得，如果一个点不符合上述情况，但右边或下边有点也是合法的。

不符合上述两条件的点就不行。

经过样例验证，的确如此。

喜闻乐见的代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,ans,a[51][51];
string s;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		ans=1;
		for(int i=1;i<=n;i++)
		{
			cin>>s;
			for(int l=0;l<s.size();l++)
				a[i][l+1]=s[l]-'0';
		} 
		for(int i=1;i<n;i++)
			for(int l=1;l<n;l++)
				if(a[i][l])
					if(!a[i+1][l]&&!a[i][l+1])
						ans=0;
		if(ans)
			puts("YES");
		else
			puts("NO");
	} 
	return 0;
}
```
所以还是无法理解为什么题目和多边形有什么关系……

---

## 作者：cherish_ (赞：0)

题意：有点类似于俄罗斯方块，炮弹遇到墙会停下并变成新的墙即所给矩阵中的1（边界是墙）。问：所给矩阵中所有墙的位置是否合理，是则输出YES，不是则输出NO。

本题只需判断所给矩阵中所有值为1的点的下面和右边的点是否都为1，若是则输出YES，否则输出NO。

参考代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

int read() {
	char c = getchar();
	int x = 0, f = 1;
	for (; !isdigit(c); c = getchar())
		if (c == '-')
			f = -1;
	for (; isdigit(c); c = getchar())
		x = x * 10 + c - 48;
	return x * f;
}
int t, n;
int main() {
	t = read();
	while (t--) {
		n = read();
		int s[55][55] = { 0 };
		string ss;
		//读入矩阵
		for (int i = 1; i <= n; ++i) {
			cin >> ss;
			for (int j = 0; j < n; ++j)
				s[i][j + 1] = ss[j] - '0';
		}
		bool flag = 0;
		for (int i = 1; i <= n - 1; ++i) {
			for (int j = 1; j <= n - 1; ++j)
				if (s[i][j] && !s[i + 1][j] && !s[i][j + 1])
					flag = 1;
			if (flag)
				break;
		}
		if (!flag)
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}
	return 0;
}
```



---

