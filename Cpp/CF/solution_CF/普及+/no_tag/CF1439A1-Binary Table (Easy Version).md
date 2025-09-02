# Binary Table (Easy Version)

## 题目描述

This is the easy version of the problem. The difference between the versions is in the number of possible operations that can be made. You can make hacks if and only if you solved both versions of the problem.

You are given a binary table of size $ n \times m $ . This table consists of symbols $ 0 $ and $ 1 $ .

You can make such operation: select $ 3 $ different cells that belong to one $ 2 \times 2 $ square and change the symbols in these cells (change $ 0 $ to $ 1 $ and $ 1 $ to $ 0 $ ).

Your task is to make all symbols in the table equal to $ 0 $ . You are allowed to make at most $ 3nm $ operations. You don't need to minimize the number of operations.

It can be proved that it is always possible.

## 说明/提示

In the first test case, it is possible to make only one operation with cells $ (1, 1) $ , $ (2, 1) $ , $ (2, 2) $ . After that, all symbols will be equal to $ 0 $ .

In the second test case:

- operation with cells $ (2, 1) $ , $ (3, 1) $ , $ (3, 2) $ . After it the table will be: ```
  <pre class="verbatim"><br></br>011<br></br>001<br></br>000<br></br>
  ```
- operation with cells $ (1, 2) $ , $ (1, 3) $ , $ (2, 3) $ . After it the table will be: ```
  <pre class="verbatim"><br></br>000<br></br>000<br></br>000<br></br>
  ```

In the fifth test case:

- operation with cells $ (1, 3) $ , $ (2, 2) $ , $ (2, 3) $ . After it the table will be: ```
  <pre class="verbatim"><br></br>010<br></br>110<br></br>
  ```
- operation with cells $ (1, 2) $ , $ (2, 1) $ , $ (2, 2) $ . After it the table will be: ```
  <pre class="verbatim"><br></br>000<br></br>000<br></br>
  ```

## 样例 #1

### 输入

```
5
2 2
10
11
3 3
011
101
110
4 4
1111
0110
0110
1111
5 5
01011
11001
00010
11011
10000
2 3
011
101```

### 输出

```
1
1 1 2 1 2 2
2 
2 1 3 1 3 2
1 2 1 3 2 3
4
1 1 1 2 2 2 
1 3 1 4 2 3
3 2 4 1 4 2
3 3 4 3 4 4
4
1 2 2 1 2 2 
1 4 1 5 2 5 
4 1 4 2 5 1
4 4 4 5 3 4
2
1 3 2 2 2 3
1 2 2 1 2 2```

# 题解

## 作者：J_Ignite (赞：9)

## CF1439A1 Binary Table (Easy Version) 题解
一道大水题。题目中要求在 $3nm$ 步内把矩阵还原，那么只要保证**每三次操作还原一个点,且不对其它点产生影响**。我们可以发现，假设找到了这样一个矩阵：
```
? 1
? ?
```
$?$ 号表示是0是1无所谓。\
我们在这个矩阵中找到所有 ? 点作为中心 ,依次对其它三个点进行取反：
第一次，找到左上角的 ? ，对另外三个点进行取反。
```
? 0
¿ ¿
```
反问号¿表示原来的?取反后的值。\
第二次：找到左下角的 ¿ ，对另外三个点进行取反。
```
¿ 1
¿ ?
```
第三次：找到右下角的 ? ，对另外三个点进行取反。
```
? 0
? ?
```
这样，原来的 1 就变成了 0，并且其它点不受影响，也就是说，我们每找到一个 1 ， 就可以把它放到一个 $2 * 2$ 的矩阵里，以另外三个点作为中心（即不取反的那个，无论是 0 还是 1）对与其互斥的三个点取反，就能达到目标，即使矩阵全部都是 1 , 也能在 $3nm$ 步内完成。
### Code:
```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int MAXN = 105;
int t;
int n, m;
char a[MAXN][MAXN];
int main()
{
	cin >> t;
	while (t--)
	{
		memset(a, 0, sizeof(a));
		cin >> n >> m;
		for (int i = 1; i <= n; i++)
			cin >> a[i] + 1;
		int ans_1 = 0;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				if (a[i][j] == '1')
					ans_1 += 3;
		printf("%d\n", ans_1);
		if (a[n][m] == '1') // 将要还原的1作为2*2矩阵右下角（最后一排最后一列的数字）（特判）
		{
			printf("%d %d %d %d %d %d\n", n, m, n - 1, m, n, m - 1);	 // n-1,m-1
			printf("%d %d %d %d %d %d\n", n, m, n - 1, m, n - 1, m - 1); // n,m-1
			printf("%d %d %d %d %d %d\n", n, m, n, m - 1, n - 1, m - 1); // n-1,m
		}
		for (int i = 1; i < n; i++) // 将要还原的1作为2*2矩阵左下角（最后一排）（特判）
			if (a[i][m] == '1')
			{
				printf("%d %d %d %d %d %d\n", i, m, i + 1, m - 1, i, m - 1); // i+1,m
				printf("%d %d %d %d %d %d\n", i, m, i + 1, m, i + 1, m - 1); // i,m-1
				printf("%d %d %d %d %d %d\n", i, m, i + 1, m, i, m - 1);	 // i+1,m-1
			}
		for (int i = 1; i < m; i++) // 将要还原的1作为2*2矩阵右上角（最后一列）（特判）
			if (a[n][i] == '1')
			{
				printf("%d %d %d %d %d %d\n", n, i, n - 1, i, n - 1, i + 1); // n,i+1
				printf("%d %d %d %d %d %d\n", n, i, n, i + 1, n - 1, i + 1); // n-1,i
				printf("%d %d %d %d %d %d\n", n, i, n - 1, i, n, i + 1);	 // n-1,i+1
			}
		for (int i = 2; i <= n; i++) // 将要还原的1作为2*2矩阵左上角
			for (int j = 2; j <= m; j++)
				if (a[i - 1][j - 1] == '1')
				{
					printf("%d %d %d %d %d %d\n", i - 1, j - 1, i, j - 1, i - 1, j); // i,j
					printf("%d %d %d %d %d %d\n", i - 1, j - 1, i - 1, j, i, j);	 // i-1,j
					printf("%d %d %d %d %d %d\n", i - 1, j - 1, i, j, i, j - 1);	 // i,j-1
				}
	}
	return 0;
}
```

---

## 作者：wzkdh (赞：4)

众所周知，这题可以模拟过。。。（~~我都不知道我考场上怎么写下来的~~）
```
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#define int long long
using namespace std;
int t,n,m,ans[30010][6];
char a[110][110];
signed main()
{
	cin>>t;
	while(t--)
	{
		scanf("%lld%lld",&n,&m);
		for(int i=0;i<n;i++)
		{
			scanf("%s",a[i]);
		}
		int cs=0;
		for(int i=0;i+2<n;i++)
		{
			for(int j=0;j<m-1;j++)
			{
				if(a[i][j]=='0'&&a[i+1][j]=='1')
				{
					ans[++cs][0]=i+1;
					ans[cs][1]=j;
					ans[cs][2]=i;
					ans[cs][3]=j+1;
					ans[cs][4]=i+1;
					ans[cs][5]=j+1;
					a[i+1][j]='0';
					a[i][j+1]=1-(a[i][j+1]-'0')+'0';
					a[i+1][j+1]=1-(a[i+1][j+1]-'0')+'0';
				}
				else if(a[i][j]=='1'&&a[i+1][j]=='0')
				{
					ans[++cs][0]=i;
					ans[cs][1]=j;
					ans[cs][2]=i;
					ans[cs][3]=j+1;
					ans[cs][4]=i+1;
					ans[cs][5]=j+1;
					a[i][j]='0';
					a[i][j+1]=1-(a[i][j+1]-'0')+'0';
					a[i+1][j+1]=1-(a[i+1][j+1]-'0')+'0';
				}
				else if(a[i][j]=='0'&&a[i+1][j]=='0')
				{
					continue;
				}
				else if(a[i][j]=='1'&&a[i+1][j]=='1')
				{
					ans[++cs][0]=i+1;
					ans[cs][1]=j;
					ans[cs][2]=i;
					ans[cs][3]=j;
					ans[cs][4]=i;
					ans[cs][5]=j+1;
					a[i+1][j]='0';
					a[i][j]='0';
					a[i][j+1]=1-(a[i][j+1]-'0')+'0';
				}
			}
			if(a[i][m-1]=='0'&&a[i+1][m-1]=='1')
			{
				a[i+1][m-1]='0';
				a[i+2][m-1]=1-(a[i+2][m-1]-'0')+'0';
				a[i+2][m-2]=1-(a[i+2][m-2]-'0')+'0';
				ans[++cs][0]=i+1;
				ans[cs][1]=m-1;
				ans[cs][2]=i+2;
				ans[cs][3]=m-1;
				ans[cs][4]=i+2;
				ans[cs][5]=m-2;
			}
			else if(a[i][m-1]=='1'&&a[i+1][m-1]=='0')
			{
				a[i][m-1]='0';
				a[i+2][m-1]=1-(a[i+2][m-1]-'0')+'0';
				ans[++cs][0]=i;
				ans[cs][1]=m-1;
				ans[cs][2]=i+1;
				ans[cs][3]=m-1;
				ans[cs][4]=i+1;
				ans[cs][5]=m-2;
				ans[++cs][0]=i+2;
				ans[cs][1]=m-1;
				ans[cs][2]=i+1;
				ans[cs][3]=m-1;
				ans[cs][4]=i+1;
				ans[cs][5]=m-2;
			}
			else if(a[i][m-1]=='1'&&a[i+1][m-1]=='1')
			{
				a[i][m-1]='0';
				a[i+1][m-1]='0';
				a[i+2][m-1]=1-(a[i+2][m-1]-'0')+'0';
				a[i+2][m-2]=1-(a[i+2][m-2]-'0')+'0';
				ans[++cs][0]=i;
				ans[cs][1]=m-1;
				ans[cs][2]=i+1;
				ans[cs][3]=m-1;
				ans[cs][4]=i+1;
				ans[cs][5]=m-2;
				ans[++cs][0]=i+2;
				ans[cs][1]=m-1;
				ans[cs][2]=i+2;
				ans[cs][3]=m-2;
				ans[cs][4]=i+1;
				ans[cs][5]=m-2;
			}
		}
		for(int j=0;j<m-1;j++)
			{
				int i=n-2; 
				if(a[i][j]=='0'&&a[i+1][j]=='1')
				{
					ans[++cs][0]=i+1;
					ans[cs][1]=j;
					ans[cs][2]=i;
					ans[cs][3]=j+1;
					ans[cs][4]=i+1;
					ans[cs][5]=j+1;
					a[i+1][j]='0';
					a[i][j+1]=1-(a[i][j+1]-'0')+'0';
					a[i+1][j+1]=1-(a[i+1][j+1]-'0')+'0';
				}
				else if(a[i][j]=='1'&&a[i+1][j]=='0')
				{
					ans[++cs][0]=i;
					ans[cs][1]=j;
					ans[cs][2]=i;
					ans[cs][3]=j+1;
					ans[cs][4]=i+1;
					ans[cs][5]=j+1;
					a[i][j]='0';
					a[i][j+1]=1-(a[i][j+1]-'0')+'0';
					a[i+1][j+1]=1-(a[i+1][j+1]-'0')+'0';
				}
				else if(a[i][j]=='0'&&a[i+1][j]=='0')
				{
					continue;
				}
				else if(a[i][j]=='1'&&a[i+1][j]=='1')
				{
					ans[++cs][0]=i+1;
					ans[cs][1]=j;
					ans[cs][2]=i;
					ans[cs][3]=j;
					ans[cs][4]=i;
					ans[cs][5]=j+1;
					a[i+1][j]='0';
					a[i][j]='0';
					a[i][j+1]=1-(a[i][j+1]-'0')+'0';
				}
			}
		if(a[n-2][m-2]=='1'&&a[n-2][m-1]=='1'&&a[n-1][m-2]=='1'&&a[n-1][m-1]=='1')
		{
			ans[++cs][0]=n-2;
			ans[cs][1]=m-1;
			ans[cs][2]=n-1;
			ans[cs][3]=m-1;
			ans[cs][4]=n-2;
			ans[cs][5]=m-2;
			a[n-2][m-1]='0';
			a[n-1][m-1]='0';
			a[n-2][m-2]='0';
		}
			
		if(a[n-2][m-2]=='0'&&a[n-2][m-1]=='0'&&a[n-1][m-2]=='0'&&a[n-1][m-1]=='1')
		{
			ans[++cs][0]=n-1;
			ans[cs][1]=m-1;
			ans[cs][2]=n-1;
			ans[cs][3]=m-2;
			ans[cs][4]=n-2;
			ans[cs][5]=m-2;
			a[n-1][m-1]='0';
			a[n-1][m-2]='1';
			a[n-2][m-2]='1';
		}
		else if(a[n-2][m-2]=='0'&&a[n-2][m-1]=='0'&&a[n-1][m-2]=='1'&&a[n-1][m-1]=='0')
		{
			ans[++cs][0]=n-1;
			ans[cs][1]=m-2;
			ans[cs][2]=n-1;
			ans[cs][3]=m-1;
			ans[cs][4]=n-2;
			ans[cs][5]=m-2;
			a[n-1][m-2]='0';
			a[n-1][m-1]='1';
			a[n-2][m-2]='1';
		}
		else if(a[n-2][m-2]=='0'&&a[n-2][m-1]=='1'&&a[n-1][m-2]=='0'&&a[n-1][m-1]=='0')
		{
			ans[++cs][0]=n-2;
			ans[cs][1]=m-1;
			ans[cs][2]=n-1;
			ans[cs][3]=m-1;
			ans[cs][4]=n-2;
			ans[cs][5]=m-2;
			a[n-2][m-1]='0';
			a[n-1][m-1]='1';
			a[n-2][m-2]='1';
		}
		else if(a[n-2][m-2]=='1'&&a[n-2][m-1]=='0'&&a[n-1][m-2]=='0'&&a[n-1][m-1]=='0')
		{
			ans[++cs][0]=n-1;
			ans[cs][1]=m-1;
			ans[cs][2]=n-1;
			ans[cs][3]=m-2;
			ans[cs][4]=n-2;
			ans[cs][5]=m-2;
			a[n-1][m-1]='1';
			a[n-1][m-2]='1';
			a[n-2][m-2]='0';
		}
		
		if(a[n-2][m-2]=='0'&&a[n-2][m-1]=='1'&&a[n-1][m-2]=='0'&&a[n-1][m-1]=='1')
		{
			ans[++cs][0]=n-2;
			ans[cs][1]=m-1;
			ans[cs][2]=n-1;
			ans[cs][3]=m-2;
			ans[cs][4]=n-2;
			ans[cs][5]=m-2;
			a[n-2][m-1]='0';
			a[n-1][m-2]='1';
			a[n-2][m-2]='1';
		}
		else if(a[n-2][m-2]=='0'&&a[n-2][m-1]=='0'&&a[n-1][m-2]=='1'&&a[n-1][m-1]=='1')
		{
			ans[++cs][0]=n-1;
			ans[cs][1]=m-2;
			ans[cs][2]=n-2;
			ans[cs][3]=m-1;
			ans[cs][4]=n-2;
			ans[cs][5]=m-2;
			a[n-1][m-2]='0';
			a[n-2][m-1]='1';
			a[n-2][m-2]='1';
		}
		else if(a[n-2][m-2]=='0'&&a[n-2][m-1]=='1'&&a[n-1][m-2]=='1'&&a[n-1][m-1]=='0')
		{
			ans[++cs][0]=n-2;
			ans[cs][1]=m-1;
			ans[cs][2]=n-2;
			ans[cs][3]=m-2;
			ans[cs][4]=n-1;
			ans[cs][5]=m-1;
			a[n-2][m-1]='0';
			a[n-1][m-1]='1';
			a[n-2][m-2]='1';
		}
		else if(a[n-2][m-2]=='1'&&a[n-2][m-1]=='0'&&a[n-1][m-2]=='0'&&a[n-1][m-1]=='1')
		{
			ans[++cs][0]=n-2;
			ans[cs][1]=m-2;
			ans[cs][2]=n-2;
			ans[cs][3]=m-1;
			ans[cs][4]=n-1;
			ans[cs][5]=m-2;
			a[n-2][m-1]='1';
			a[n-1][m-2]='1';
			a[n-2][m-2]='0';
		}
		else if(a[n-2][m-2]=='1'&&a[n-2][m-1]=='0'&&a[n-1][m-2]=='1'&&a[n-1][m-1]=='0')
		{
			ans[++cs][0]=n-2;
			ans[cs][1]=m-2;
			ans[cs][2]=n-2;
			ans[cs][3]=m-1;
			ans[cs][4]=n-1;
			ans[cs][5]=m-1;
			a[n-2][m-2]='0';
			a[n-1][m-1]='1';
			a[n-2][m-1]='1';
		}
		else if(a[n-2][m-2]=='1'&&a[n-2][m-1]=='1'&&a[n-1][m-2]=='0'&&a[n-1][m-1]=='0')
		{
			ans[++cs][0]=n-2;
			ans[cs][1]=m-2;
			ans[cs][2]=n-1;
			ans[cs][3]=m-2;
			ans[cs][4]=n-1;
			ans[cs][5]=m-1;
			a[n-2][m-2]='0';
			a[n-1][m-2]='1';
			a[n-1][m-1]='1';
		}
		
		
		
		if(a[n-2][m-2]=='1'&&a[n-2][m-1]=='1'&&a[n-1][m-2]=='1'&&a[n-1][m-1]=='0')
		{
			ans[++cs][0]=n-2;
			ans[cs][1]=m-2;
			ans[cs][2]=n-2;
			ans[cs][3]=m-1;
			ans[cs][4]=n-1;
			ans[cs][5]=m-2;
		}
		else if(a[n-2][m-2]=='1'&&a[n-2][m-1]=='1'&&a[n-1][m-2]=='0'&&a[n-1][m-1]=='1')
		{
			ans[++cs][0]=n-2;
			ans[cs][1]=m-2;
			ans[cs][2]=n-2;
			ans[cs][3]=m-1;
			ans[cs][4]=n-1;
			ans[cs][5]=m-1;
		}
		else if(a[n-2][m-2]=='1'&&a[n-2][m-1]=='0'&&a[n-1][m-2]=='1'&&a[n-1][m-1]=='1')
		{
			ans[++cs][0]=n-2;
			ans[cs][1]=m-2;
			ans[cs][2]=n-1;
			ans[cs][3]=m-1;
			ans[cs][4]=n-1;
			ans[cs][5]=m-2;
		}
		else if(a[n-2][m-2]=='0'&&a[n-2][m-1]=='1'&&a[n-1][m-2]=='1'&&a[n-1][m-1]=='1')
		{
			ans[++cs][0]=n-1;
			ans[cs][1]=m-1;
			ans[cs][2]=n-2;
			ans[cs][3]=m-1;
			ans[cs][4]=n-1;
			ans[cs][5]=m-2;
		}
		cout<<cs<<endl;
		for(int i=1;i<=cs;i++)
		{
			for(int j=0;j<=5;j++)
			{
				printf("%lld ",ans[i][j]+1);
			}
			printf("\n");
		}
	}
	return 0;
}

---

## 作者：TEoS (赞：3)

**题意分析**

给出一个 $n×m$ 的只由 $0,1$ 构成的矩阵，每次可以将一个 $2×2$ 的子矩阵中的 $3$ 个数取反。要求将整个矩阵的所有元素变为 $0$ ，并且操作次数不能超过 $3nm$ 次。要求给出操作次数和具体方案。

**思路分析**

由于每次只能修改一个 $2×2$ 的子矩阵中的 $3$ 个数，想到考虑每个 $2×2$ 的子矩阵的情况，尝试把每个 $2×2$ 的子矩阵单独处理，看看合不合法。

显然可以根据 $1$ 的个数划分为五种情况，对每种情况分别考虑：

###### 情况一： $0$ 个 $1$

显然不用处理，需要 $0$ 次操作。

###### 情况二：  $3$ 个 $1$

将 $3$ 个 $1$ 取反即可，需要 $1$ 次操作。

###### 情况三： $2$ 个 $1$ 

将 $2$ 个 $0$ 和 $1$ 个 $1$ 取反，可以变为情况二，接着处理，需要 $2$ 次操作。

###### 情况四： $1$ 个 $1$

将 $2$ 个 $0$ 和 $1$ 个 $1$ 取反，可以变为情况三，接着处理，需要 $3$ 次操作。

###### 情况五： $4$ 个 $1$

将 $3$ 个 $1$ 取反，可以变为情况一，接着处理，需要 $4$ 次操作。

可以发现，所有情况最多只需要 $4$ 次操作，刚好与子矩阵的元素数目相等，因此一定可以满足操作次数合法。

若 $n$ 或 $m$ 为奇数，不能刚好划分为 $2×2$ 的子矩阵，就先把一行全部变成 $0$ ，然后再处理剩下的即可。注意后面的处理不能影响到前面已经处理过的元素。

```c++
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
using namespace std;
const int N=200,M=3e4+100;
int T,n,m,ans;
int dx[4]={0,1,0,1},dy[4]={0,0,1,1};
int x1[M],x2[M],x3[M],y1[M],y2[M],y3[M],a[N][N];
string s;
int ano(int x)
{
	return ((x-1)^1)+1;
}//找相邻的数，其中奇数较小，偶数较大
void solve1(int i,int j)
{
	ans++;
	for(int k=0,x=i+dx[k],y=j+dy[k];k<4;k++,x=i+dx[k],y=j+dy[k])
		if(!a[x][y])
		{
			if(!x1[ans])
				a[x][y]=1,x1[ans]=x,y1[ans]=y;
			else
				if(!x2[ans])
					a[x][y]=1,x2[ans]=x,y2[ans]=y;//取反 2 个 0
		}
		else
			if(!x3[ans])
				a[x][y]=0,x3[ans]=x,y3[ans]=y;//取反 1 个 1
}//取反 2 个 0 和 1 个 1
void solve2(int i,int j)
{
	ans++;
	for(int k=0,x=i+dx[k],y=j+dy[k];k<4;k++,x=i+dx[k],y=j+dy[k])
		if(a[x][y])
			if(!x1[ans])
				a[x][y]=0,x1[ans]=x,y1[ans]=y;
			else
				if(!x2[ans])
					a[x][y]=0,x2[ans]=x,y2[ans]=y;
				else
					if(!x3[ans])
						a[x][y]=0,x3[ans]=x,y3[ans]=y;
}//取反 3 个 1
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&m);ans=0;
		for(int i=1;i<=n*m;i++)
			x1[i]=x2[i]=x3[i]=y1[i]=y2[i]=y3[i]=0;
		for(int i=1;i<=n;i++)
		{
			cin>>s;
			for(int j=1;j<=m;j++)
				a[i][j]=s[j-1]-'0';
		}
		if(n&1)// n 为奇数，处理第 n 行
			for(int i=1;i<=m;i++)
				if(a[n][i])
					a[n][i]=0,a[n-1][i]^=1,a[n-1][i==m?i-1:i+1]^=1,x1[++ans]=n,x2[ans]=n-1,x3[ans]=n-1,y1[ans]=i,y2[ans]=i,y3[ans]=i==m?i-1:i+1;
		if(m&1)// m 为奇数，处理第 m 列
			for(int i=1;i<=n;i++)
				if(a[i][m])
					if(i<m)
						a[i][m]=0,a[i][m-1]^=1,a[i==1?i+1:i-1][m-1]^=1,x1[++ans]=i,x2[ans]=i,x3[ans]=i==1?i+1:i-1,y1[ans]=m,y2[ans]=m-1,y3[ans]=m-1;
					else
						a[n][m-1]=0,a[n-1][m]^=1,a[n-1][m-1]^=1,x1[++ans]=n,x2[ans]=n-1,x3[ans]=n-1,y1[ans]=m,y2[ans]=m,y3[ans]=m-1;
		for(int i=1;i<=n;i+=2)
			for(int j=1;j<=m;j+=2)
			{
				if(a[i][j]+a[i+1][j]+a[i][j+1]+a[i+1][j+1]==4)
					solve2(i,j);
				if(a[i][j]+a[i+1][j]+a[i][j+1]+a[i+1][j+1]==1)
					solve1(i,j);
				if(a[i][j]+a[i+1][j]+a[i][j+1]+a[i+1][j+1]==2)
					solve1(i,j);
				if(a[i][j]+a[i+1][j]+a[i][j+1]+a[i+1][j+1]==3)
					solve2(i,j);
			}//划分处理，根据处理先后按顺序
		printf("%d\n",ans);
		for(int i=1;i<=ans;i++)
			printf("%d %d %d %d %d %d\n",x1[i],y1[i],x2[i],y2[i],x3[i],y3[i]);
	}
	return 0;
}
```

---

## 作者：引领天下 (赞：1)

提供一个针对A1的易思考做法。

考虑对于每个 $2\times 2$ 的矩阵，都把他的左边两列变成0，这样到最后就只会剩下最后一列和最后一行有1，然后针对最后一行和最后一列单独处理就行了。

针对中间的 $2\times 2$ 矩阵，若左侧只有1个1，则将右侧和左侧的1全部翻转；否则分两种情况：

- 若右上角为1，则翻左侧两个和右上角；

- 否则翻左侧两个和右下角。

然后处理最后一行和最后一列，以最后一行中的 $2\times 1$ 矩阵为例：

若含有两个1，则采取以下策略：

1. 翻转其中的一个1和倒数第二行的两个0

2. 翻转另一个1和倒数第二行的两个1

若只含有一个1，则采取以下策略：

1. 将那个1连同倒数第二行的两个0一起翻转

2. 化为两个1的状态处理（最后一行为两个0，倒数第二行为两个1）

需要注意的是整个矩阵的右下角（即第 $n$ 行 $m$ 列）如果为一个单独的1不需要放进来处理，因为他可能可以跟着第 $n-1$ 行 $m$ 列一起处理，也可能可以跟着第 $n$ 行 $m-1$ 列一起处理。如果整个处理完了他还单着在，再采取单独翻一个的策略处理掉他。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,a[105][105];
struct Opt{
    int a,b,c,d,e,f;
}x[10005];
int main(){
    scanf("%d",&t);
    while(t--){
        scanf("%d%d",&n,&m);
        int k=0;
        for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)scanf("%1d",&a[i][j]);
        for(int i=2;i<=n;i++)
        for(int j=2;j<=m;j++)if(a[i-1][j-1]||a[i][j-1]){
            if(a[i-1][j-1]&&a[i][j-1]){//左侧两个全1
                a[i-1][j-1]=a[i][j-1]=0;
                if(a[i-1][j])x[++k]=(Opt){i-1,j-1,i,j-1,i-1,j},a[i-1][j]^=1;
                else x[++k]=(Opt){i-1,j-1,i,j-1,i,j},a[i][j]^=1;
            }
            else if(!a[i-1][j-1])x[++k]=(Opt){i,j-1,i,j,i-1,j},a[i][j-1]=0,a[i][j]^=1,a[i-1][j]^=1;//只有一个为1
            else x[++k]=(Opt){i-1,j-1,i,j,i-1,j},a[i-1][j-1]=0,a[i-1][j]^=1,a[i][j]^=1;
        }
        for(int j=2;j<=m;j+=2){//单独处理最后一行
            if(a[n][j-1]&&a[n][j]){
                x[++k]=(Opt){n-1,j-1,n-1,j,n,j-1};
                x[++k]=(Opt){n-1,j-1,n-1,j,n,j};
                a[n][j-1]=a[n][j]=0;
            }else if(j!=m&&(a[n][j-1]||a[n][j])){
                if(a[n][j-1]){
                    x[++k]=(Opt){n-1,j-1,n-1,j,n,j-1};
                    x[++k]=(Opt){n-1,j-1,n,j-1,n,j};
                    x[++k]=(Opt){n-1,j,n,j-1,n,j};
                    a[n][j-1]=0;
                }else{
                    x[++k]=(Opt){n-1,j-1,n-1,j,n,j};
                    x[++k]=(Opt){n-1,j-1,n,j-1,n,j};
                    x[++k]=(Opt){n-1,j,n,j-1,n,j};
                    a[n][j]=0;
                }
            }
        }
        for(int i=2;i<=n;i+=2){//单独处理最后一列
            if(a[i-1][m]&&a[i][m]){
                x[++k]=(Opt){i-1,m-1,i,m-1,i-1,m};
                x[++k]=(Opt){i-1,m-1,i,m-1,i,m};
                a[i-1][m]=a[i][m]=0;
            }else if(i!=n&&(a[i-1][m]||a[i][m])){
                if(a[i-1][m]){
                    x[++k]=(Opt){i-1,m-1,i-1,m,i,m-1};
                    x[++k]=(Opt){i-1,m-1,i-1,m,i,m};
                    x[++k]=(Opt){i,m-1,i-1,m,i,m};
                    a[i-1][m]=0;
                }else{
                    x[++k]=(Opt){i-1,m-1,i,m-1,i,m};
                    x[++k]=(Opt){i-1,m-1,i-1,m,i,m};
                    x[++k]=(Opt){i-1,m,i,m-1,i,m};
                    a[i][m]=0;
                }
            }
        }
        if(a[n][m]){//处理整个矩阵的右下角
            x[++k]=(Opt){n-1,m-1,n,m-1,n,m};
            x[++k]=(Opt){n-1,m-1,n-1,m,n,m};
            x[++k]=(Opt){n,m-1,n-1,m,n,m};
        }
        printf("%d\n",k);
        for(int i=1;i<=k;i++)printf("%d %d %d %d %d %d\n",x[i].a,x[i].b,x[i].c,x[i].d,x[i].e,x[i].f);
    }
    return 0;
}
```

---

## 作者：sgl654321 (赞：0)

## 题目大意
给定一个 $n\times m$ 的 $0/1$ 矩阵，每次操作可以选出一个 L 形的三个位置，把 $0$ 变成 $1$，把 $1$ 变成 $0$。在 $n\times m$ 次操作之内把所有位置都变成 $0$。
## 解题思路
由于是 $n\times m$ 次操作，平均下来就是每个位置只有一次操作机会。我们考虑把那些零散的 $1$ 都尽可能聚集到右下角去。

我们遍历 $i\in[1,n-2],j\in[1,m-1]$。如果 $a_{i,j} = 1$，那么就进行操作 $\{a_{i,j},a_{i+1,j},a_{i,j+1}\}$。这样我们只影响到了 $(i,j)$ 下面和右面的位置，已经处理好的左边和上边都不受影响。

那么 $i\in[1,n-2],j=m$ 怎么办呢？如果 $a_{i,m}=1$，我们可以在处理下一行前，先进行操作 $\{a_{i,m},a_{i+1,m},a_{i+1,m-1}\}$。这样对处理过的那些点也是没有影响的。

接下来是 $i\in\{n-1,n\},j\in[1,m-2]$。$i=n-1$ 时，如果 $a_{n-1,j} = 1$，显然操作 $\{a_{n-1,j},a_{n-1,j+1},a_{n,j}\}$。如果 $a_{n,j} =1$，则是操作 $\{a_{n,j},a_{n,j+1},a_{n-1,j+1}\}$。

最终，我们就把除了最右下角的四个点全都变成 $0$ 了，最多操作次数为 $n\times m -4$。还有 $4$ 次机会。

我们对一个 $2\times 2$ 的一个小正方形再次进行讨论。

- 如果其中一个 $1$ 也没有那直接结束了。

- 如果其中有三个 $1$，一次搞定。

- 如果其中有两个 $1$，我们先选出其中有两个 $0$，一个 $1$ 的这个 L 形进行操作。这样就化成三个 $1$ 的情况了。总共要用上两次搞定。

- 如果其中有一个 $1$，我们选出包含这个 $1$ 的一个 L 形，然后就化成有两个 $1$ 的情况了。总共用上三次搞定。

- 如果全是 $1$，那么我们随便选一个 L 形操作，就变成只有一个 $1$ 的情况了。总共用上四次搞定。

经过上述分析，我们知道一个 $2\times2$ 的正方形，$4$ 次就一定可以搞定。

因此本题就在 $n\times m$ 次操作之内解决了，通过了两个版本。

### 参考代码
这题毕竟是个小模拟，码量还是有一点的。

- 用 `change` 这个封装函数来实现位置上的取反并记录答案。

- 用 `work` 这个函数化归思想（即使用递归）来处理最后的 $2\times 2$ 正方形。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
struct oper{
	ll xa, ya, xb, yb, xc, yc;
} ans[10010];
ll tt, n, m, a[110][110], tot, num;
char ch;
void change(ll xa, ll ya, ll xb, ll yb, ll xc, ll yc){
	ans[++tot] = oper{xa, ya, xb, yb, xc, yc};
	a[xa][ya] = 1 - a[xa][ya]; a[xb][yb] = 1 - a[xb][yb]; a[xc][yc] = 1 - a[xc][yc];
}
void work(ll x, ll y){
	if(a[x][y] == 0 && a[x + 1][y] == 0 && a[x][y + 1] == 0 && a[x + 1][y + 1] == 0) return;
	ll num = a[x][y] + a[x + 1][y] + a[x][y + 1] + a[x + 1][y + 1];
	if(num == 3){
		if(a[x][y] == 0) change(x + 1, y, x, y + 1, x + 1, y + 1);
		else if(a[x][y + 1] == 0) change(x, y, x + 1, y, x + 1, y + 1);
		else if(a[x + 1][y] == 0) change(x, y, x, y + 1, x + 1, y + 1);
		else if(a[x + 1][y + 1] == 0) change(x, y, x, y + 1, x + 1, y);
		return;
	} 
	if(num == 2){
		if(a[x][y] == 0 && a[x + 1][y] == 0) change(x, y, x + 1, y, x, y + 1), work(x, y);
		else if(a[x][y] == 0 && a[x][y + 1] == 0) change(x, y, x + 1, y, x, y + 1), work(x, y); 
		else if(a[x][y] == 0 && a[x + 1][y + 1] == 0) change(x, y, x + 1, y, x + 1, y + 1), work(x, y); 
		else if(a[x + 1][y] == 0 && a[x][y + 1] == 0) change(x, y, x + 1, y, x, y + 1), work(x, y); 
		else if(a[x + 1][y] == 0 && a[x + 1][y + 1] == 0) change(x, y, x + 1, y, x + 1, y + 1), work(x, y); 
		else if(a[x][y + 1] == 0 && a[x + 1][y + 1] == 0) change(x, y, x, y + 1, x + 1, y + 1), work(x, y); 
	}
	if(num == 1){
		if(a[x][y] == 1) change(x, y, x, y + 1, x + 1, y + 1), work(x, y);
		else if(a[x][y + 1] == 1) change(x, y, x, y + 1, x + 1, y + 1), work(x, y);
		else if(a[x + 1][y] == 1) change(x, y, x + 1, y, x + 1, y + 1), work(x, y);
		else if(a[x + 1][y + 1] == 1) change(x, y, x, y + 1, x + 1, y + 1), work(x, y);
	} 
	if(num == 4){
		change(x, y, x + 1, y, x, y + 1); work(x, y);
	}

}
void solve(){
	cin >> n >> m; tot = 0;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++) 
			cin >> ch, a[i][j] = ch - '0';
	for(int i = 1; i <= n - 2; i++){
		for(int j = 1; j <= m - 1; j++)
			if(a[i][j] == 1) change(i, j, i + 1, j, i, j + 1);
		if(a[i][m] == 1) change(i, m, i + 1, m - 1, i + 1, m);
	}
	for(int j = 1; j <= m - 2; j++){
		if(a[n - 1][j] == 1) change(n - 1, j, n - 1, j + 1, n, j + 1);
		if(a[n][j] == 1) change(n, j, n - 1, j + 1, n, j + 1);
	}
	work(n - 1, m - 1);
	cout << tot << endl;
	for(int i = 1; i <= tot; i++)
		cout << ans[i].xa << ' ' << ans[i].ya << ' ' << ans[i].xb << ' ' <<ans[i].yb << ' '
		<< ans[i].xc << ' ' <<ans[i].yc <<endl;  
}
int main(){
	cin >> tt; while(tt--) solve();
	return 0;
}

```

---

## 作者：LookatSea (赞：0)

暴力解决即可。

思路：如果是零就不用管它，否则则将他变为一。

看样例可发现一种方法。

假设有一个方阵。

```
p 1
p p
```

注：$p$ 是零或一，$\star$ 是取反。

首先找到左上的 $p$，然后将其他元素取反。

然后找到左下的 $\star p$ 将其他元素取反。

最后找到右下的 $p$ 将其他元素取反。

最后答案就从原来的方阵右上角的 $1$ 变成了 $0$ 得到了答案。

---

## 作者：qusia_MC (赞：0)

直接暴力。对于每个点 $(x,y)$，若 $(x,y)$ 为 $0$ 则不用管他。

否则，则需要把这个点变成 $1$。经过我的一番计算，发现了这样的一个操作方法：

$\neg k$ 为将 $k$ 取反。

当前矩阵：
```
1 k
k k
```
目标：
```
0 k
k k
```

1. 将坐标 $(x,y),(x+1,y),(x,y+1)$ 分别取反。
   
   当前矩阵：
   ```
   0 ¬k
   ¬k k
   ```
   目标：
   ```
   0 k
   k k
   ```

2. 将坐标 $(x,y),(x,y+1),(x+1,y+1)$ 分别取反。
    
    当前矩阵：
    ```
    1 k
    ¬k ¬k
    ```
    目标：
    ```
    0 k
    k k
    ```
3. 将坐标 $(x,y),(x+1,y),(x,y+1)$ 分别取反。
    
    当前矩阵：
    ```
    0 k
    k k
    ```
    完成目标。
## CODE    
```
#include<bits/stdc++.h>
using namespace std;
int a[111][111],n,m;
void zh1(int x,int y)
{
	int k1=1,k2=1;//构成矩阵的坐标差
	if(x==n)k1=-1;//最后一行与前一行构成矩阵。
	if(y==m)k2=-1;//如果是最后一列，则与前面的构成矩阵。
	printf("%d %d %d %d %d %d\n%d %d %d %d %d %d\n%d %d %d %d %d %d\n",x,y,x+k1,y,x,y+k2,x,y,x,y+k2,x+k1,y+k2,x,y,x+k1,y,x+k1,y+k2);//操作
	a[x][y]=0;
}
int main()
{
	int T,ans;char ch;
	cin>>T;
	while(T--)
	{
		ans=0;
		cin>>n>>m;
		for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)
		{
			cin>>ch;
			a[i][j]=ch-'0';
			if(a[i][j]&1)ans+=3;//位运算快很多，一个点要3次
		}
		cout<<ans<<'\n';
		for(int i=1;i<=n;i++)for(int j=1;j<=m;++j)
		{
			if(a[i][j]&1)zh1(i,j);//输出
		}
	}
	return 0;
}
```

---

## 作者：Ba_creeper (赞：0)

#### 题目分析
这道题的 Easy 难度可以暴力模拟，对于每一个 $2×2$ 的矩阵中，01 字符矩阵共有 16 中不同的搭配。我们只要对于每种搭配，制定一个合理的方案，使这个 $2×2$ 的矩阵中的数字全部变为 0 即可。

详细的方案见代码部分。

#### 代码
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
typedef long long ll;

ll T;
char a[102][102];
int ans[100000][6];
ll tot;

void ja(int a,int b,int c,int i,int j) //存储答案用
{
	tot++;
	if(a==1)
	{
		ans[tot][1]=i;
		ans[tot][2]=j;
	}

	else if(a==2)
	{
		ans[tot][1]=i;
		ans[tot][2]=j+1;
	}
	else if(a==3)
	{
		ans[tot][1]=i+1;
		ans[tot][2]=j;
	}
	else if(a==4)
	{
		ans[tot][1]=i+1;
		ans[tot][2]=j+1;
	}
	
	if(b==1)
	{
		ans[tot][3]=i;
		ans[tot][4]=j;
	}

	else if(b==2)
	{
		ans[tot][3]=i;
		ans[tot][4]=j+1;
	}
	else if(b==3)
	{
		ans[tot][3]=i+1;
		ans[tot][4]=j;
	}
	else if(b==4)
	{
		ans[tot][3]=i+1;
		ans[tot][4]=j+1;
	}
	
	if(c==1)
	{
		ans[tot][5]=i;
		ans[tot][6]=j;
	}

	else if(c==2)
	{
		ans[tot][5]=i;
		ans[tot][6]=j+1;
	}
	else if(c==3)
	{
		ans[tot][5]=i+1;
		ans[tot][6]=j;
	}
	else if(c==4)
	{
		ans[tot][5]=i+1;
		ans[tot][6]=j+1;
	}
	return;
}
int main()
{
	T=read();
	while(T--)
	{
		memset(a,0,sizeof a);
		memset(ans,0,sizeof ans);
		ll n,m;
		tot=0;
		n=read();
		m=read();
		for(int i=1; i<=n; ++i)
			for(int j=1; j<=m; ++j)
			{
				char ch;
				cin>>ch;
				a[i][j]=ch;
			}

		for(int i=1; i<=n-1; i++)
		{
			for(int j=1; j<=m-1; ++j) //全排列所有方案
			{

				if(a[i][j]=='0' && a[i+1][j]=='0' && a[i+1][j+1]=='0' && a[i][j+1]=='0')//1
				{
					
					continue;
				}
				else if(a[i][j]=='1' && a[i][j+1]=='0' && a[i+1][j]=='0' && a[i+1][j+1]=='0')//2
				{
					ja(1,3,4,i,j);
					ja(1,2,3,i,j);
					ja(1,2,4,i,j);
					a[i][j]='0';a[i][j+1]='0';a[i+1][j]='0';a[i+1][j+1]='0';
				}
				else if(a[i][j]=='0' && a[i][j+1]=='1' && a[i+1][j]=='0' && a[i+1][j+1]=='0')//3
				{
					ja(1,2,3,i,j);
					ja(1,2,4,i,j);
					ja(2,3,4,i,j);
					a[i][j]='0';a[i][j+1]='0';a[i+1][j]='0';a[i+1][j+1]='0';
				}
				else if(a[i][j]=='0' && a[i][j+1]=='0' && a[i+1][j]=='1' && a[i+1][j+1]=='0')//4
				{
					ja(1,2,3,i,j);
					ja(1,3,4,i,j);
					ja(2,3,4,i,j);
					a[i][j]='0';a[i][j+1]='0';a[i+1][j]='0';a[i+1][j+1]='0';
				}
				else if(a[i][j]=='0' && a[i][j+1]=='0' && a[i+1][j]=='0' && a[i+1][j+1]=='1')//5
				{
					ja(1,2,4,i,j);
					ja(1,3,4,i,j);
					ja(2,3,4,i,j);
					a[i][j]='0';a[i][j+1]='0';a[i+1][j]='0';a[i+1][j+1]='0';
				}
				else if(a[i][j]=='1' && a[i][j+1]=='1' && a[i+1][j]=='0' && a[i+1][j+1]=='0')//6
				{
					ja(2,3,4,i,j);
					ja(1,3,4,i,j);

					a[i][j]='0';a[i][j+1]='0';a[i+1][j]='0';a[i+1][j+1]='0';
				}
				else if(a[i][j]=='1' && a[i][j+1]=='0' && a[i+1][j]=='1' && a[i+1][j+1]=='0')//7
				{
					ja(1,2,4,i,j);
					ja(2,3,4,i,j);
					a[i][j]='0';a[i][j+1]='0';a[i+1][j]='0';a[i+1][j+1]='0';
				}
				else if(a[i][j]=='0' && a[i][j+1]=='0' && a[i+1][j]=='1' && a[i+1][j+1]=='1')//8
				{
					ja(1,2,3,i,j);
					ja(1,2,4,i,j);
					a[i][j]='0';a[i][j+1]='0';a[i+1][j]='0';a[i+1][j+1]='0';
				}
				else if(a[i][j]=='0' && a[i][j+1]=='1' && a[i+1][j]=='0' && a[i+1][j+1]=='1')//9
				{
					ja(1,2,3,i,j);
					ja(1,3,4,i,j);
					a[i][j]='0';a[i][j+1]='0';a[i+1][j]='0';a[i+1][j+1]='0';
				}
				else if(a[i][j]=='1' && a[i][j+1]=='0' && a[i+1][j]=='0' && a[i+1][j+1]=='1')//10
				{
					ja(1,2,3,i,j);
					ja(2,3,4,i,j);
					a[i][j]='0';a[i][j+1]='0';a[i+1][j]='0';a[i+1][j+1]='0';
				}
				else if(a[i][j]=='0' && a[i][j+1]=='1' && a[i+1][j]=='1' && a[i+1][j+1]=='0')//11
				{
					ja(1,3,4,i,j);
					ja(1,2,4,i,j);
					a[i][j]='0';a[i][j+1]='0';a[i+1][j]='0';a[i+1][j+1]='0';
				}
				else if(a[i][j]=='1' && a[i][j+1]=='0' && a[i+1][j]=='1' && a[i+1][j+1]=='1')//12
				{
					ja(1,3,4,i,j);
					a[i][j]='0';a[i][j+1]='0';a[i+1][j]='0';a[i+1][j+1]='0';
				}
				else if(a[i][j]=='0' && a[i][j+1]=='1' && a[i+1][j]=='1' && a[i+1][j+1]=='1')//13
				{
					ja(2,3,4,i,j);
					a[i][j]='0';a[i][j+1]='0';a[i+1][j]='0';a[i+1][j+1]='0';
				}
				else if(a[i][j]=='1' && a[i][j+1]=='1' && a[i+1][j]=='1' && a[i+1][j+1]=='0')//14
				{
					ja(1,2,3,i,j);
					a[i][j]='0';a[i][j+1]='0';a[i+1][j]='0';a[i+1][j+1]='0';
				}
				else if(a[i][j]=='1' && a[i][j+1]=='1' && a[i+1][j]=='0' && a[i+1][j+1]=='1')//15
				{
					ja(1,2,4,i,j);
					a[i][j]='0';a[i][j+1]='0';a[i+1][j]='0';a[i+1][j+1]='0';
				}
				else //16
				{
					ja(1,2,3,i,j);
					ja(1,3,4,i,j);
					ja(1,2,4,i,j);
					ja(2,3,4,i,j);
					a[i][j]='0';a[i][j+1]='0';a[i+1][j]='0';a[i+1][j+1]='0';
				}
			}
		}
		
		ll fi=0;
		for(int i=1;i<=tot;++i)
		{
			if(ans[i][1]!=0) 
			{
				fi=i;
				break;
			}
		}
		ll totans=tot-fi+1;
		printf("%lld\n",tot);
		for(int i=1;i<=tot;++i)
		{
			ll I=ans[i][1];
			ll A=ans[i][2];
			ll K=ans[i][3];
			ll I_I=ans[i][4];
			ll IOI=ans[i][5];
			ll EdisonBa=ans[i][6];
			printf("%lld %lld %lld %lld %lld %lld\n",I,A,K,I_I,IOI,EdisonBa);
		}
	}
	return 0;
}
```

---

## 作者：KSToki (赞：0)

# 题目大意
给定一个 $n\times m$ 的 $01$ 矩阵，每次操作可以将某个 $2\times2$ 的矩阵内的 $3$ 个数取反，请在 $3\times n\times m$ 步内将矩阵变为全 $0$。
# 分析
**大模拟**，首先每次将 $(1,1)$~$(n-2,m-2)$ 中的变为全 $0$，显然每次只需要一步（另外两个可以随便点）。处理最后两列，即 $(1,m-1)$~$(n-2,m)$，显然一行一步，最后两行同理。然后特判最后一个 $2\times2$，可以手模，发现一定能在 $4$ 步内做完，所以能在 $n\times m$ 步内将矩阵变为全 $0$。其实最后一步才是码量最大的。
# 代码
大模拟要有耐心，前方高能：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline int read()
{
    char ch=getchar();
	while(ch<'0'||ch>'9')
		ch=getchar();
	int res=0;
    while(ch>='0'&&ch<='9')
    {
    	res=res*10+ch-'0';
		ch=getchar();
    }
    return res;
}
int T,n,m,a[101][101],ans[10001][6];
int main()
{
	T=read();
	while(T--)
	{
		n=read();
		m=read();
		for(int i=1;i<=n;++i)
			for(int j=1;j<=m;++j)
				scanf("%1d",&a[i][j]);
		int cnt=0;
		for(int i=1;i<n-1;++i)
			for(int j=1;j<m-1;++j)
				if(a[i][j]==1)
				{
					if(a[i+1][j]==1&&a[i+1][j+1]==1)
					{
						++cnt;
						ans[cnt][0]=i;
						ans[cnt][1]=j;
						ans[cnt][2]=i+1;
						ans[cnt][3]=j;
						ans[cnt][4]=i+1;
						ans[cnt][5]=j+1;
						a[i][j]^=1;
						a[i+1][j]^=1;
						a[i+1][j+1]^=1;
					}
					else
					{
						++cnt;
						ans[cnt][0]=i;
						ans[cnt][1]=j;
						ans[cnt][2]=i;
						ans[cnt][3]=j+1;
						ans[cnt][4]=i+1;
						ans[cnt][5]=j+1;
						a[i][j]^=1;
						a[i][j+1]^=1;
						a[i+1][j+1]^=1;
					}
				}
		for(int i=1;i<m-1;++i)
		{
			if(a[n-1][i]==0&&a[n][i]==1)
			{
				++cnt;
				ans[cnt][0]=n;
				ans[cnt][1]=i;
				ans[cnt][2]=n-1;
				ans[cnt][3]=i+1;
				ans[cnt][4]=n;
				ans[cnt][5]=i+1;
				a[n][i]=0;
				a[n-1][i+1]^=1;
				a[n][i+1]^=1;
			}
			else if(a[n-1][i]==1&&a[n][i]==0)
			{
				++cnt;
				ans[cnt][0]=n-1;
				ans[cnt][1]=i;
				ans[cnt][2]=n-1;
				ans[cnt][3]=i+1;
				ans[cnt][4]=n;
				ans[cnt][5]=i+1;
				a[n-1][i]=0;
				a[n-1][i+1]^=1;
				a[n][i+1]^=1;
			}
			else if(a[n-1][i]==1&&a[n][i]==1)
			{
				++cnt;
				ans[cnt][0]=n-1;
				ans[cnt][1]=i;
				ans[cnt][2]=n-1;
				ans[cnt][3]=i+1;
				ans[cnt][4]=n;
				ans[cnt][5]=i;
				a[n-1][i]=a[n][i]=0;
				a[n-1][i+1]^=1;
			}
		}
		for(int i=1;i<n-1;++i)
		{
			if(a[i][m-1]==0&&a[i][m]==1)
			{
				++cnt;
				ans[cnt][0]=i;
				ans[cnt][1]=m;
				ans[cnt][2]=i+1;
				ans[cnt][3]=m;
				ans[cnt][4]=i+1;
				ans[cnt][5]=m-1;
				a[i][m]=0;
				a[i+1][m]^=1;
				a[i+1][m-1]^=1;
			}
			else if(a[i][m-1]==1&&a[i][m]==0)
			{
				++cnt;
				ans[cnt][0]=i;
				ans[cnt][1]=m-1;
				ans[cnt][2]=i+1;
				ans[cnt][3]=m;
				ans[cnt][4]=i+1;
				ans[cnt][5]=m-1;
				a[i][m-1]=0;
				a[i+1][m]^=1;
				a[i+1][m-1]^=1;
			}
			else if(a[i][m-1]==1&&a[i][m]==1)
			{
				++cnt;
				ans[cnt][0]=i;
				ans[cnt][1]=m-1;
				ans[cnt][2]=i;
				ans[cnt][3]=m;
				ans[cnt][4]=i+1;
				ans[cnt][5]=m-1;
				a[i][m-1]=a[i][m]=0;
				a[i+1][m-1]^=1;
			}
		}
		if(a[n-1][m-1]==1&&a[n-1][m]==1&&a[n][m-1]==1&&a[n][m]==1)
		{
			++cnt;
			ans[cnt][0]=n-1;
			ans[cnt][1]=m-1;
			ans[cnt][2]=n-1;
			ans[cnt][3]=m;
			ans[cnt][4]=n;
			ans[cnt][5]=m-1;
			a[n-1][m-1]=a[n-1][m]=a[n][m-1]=0;
		}
		int res=0;
		for(int i=n-1;i<=n;++i)
			for(int j=m-1;j<=m;++j)
				res+=a[i][j];
		if(res==3)
		{
			int now=0;
			++cnt;
			for(int i=n-1;i<=n;++i)
				for(int j=m-1;j<=m;++j)
					if(a[i][j]==1)
					{
						a[i][j]=0;
						ans[cnt][now]=i;
						++now;
						ans[cnt][now]=j;
						++now;
					}
		}
		if(res==1)
		{
			if(a[n-1][m]==1)
			{
				++cnt;
				ans[cnt][0]=n-1;
				ans[cnt][1]=m;
				ans[cnt][2]=n;
				ans[cnt][3]=m;
				ans[cnt][4]=n;
				ans[cnt][5]=m-1;
				a[n-1][m]=0;
				a[n][m]=a[n][m-1]=1;
			}
			else if(a[n-1][m-1]==1)
			{
				++cnt;
				ans[cnt][0]=n-1;
				ans[cnt][1]=m-1;
				ans[cnt][2]=n;
				ans[cnt][3]=m;
				ans[cnt][4]=n;
				ans[cnt][5]=m-1;
				a[n-1][m-1]=0;
				a[n][m]=a[n][m-1]=1;
			}
			else if(a[n][m-1]==1)
			{
				++cnt;
				ans[cnt][0]=n-1;
				ans[cnt][1]=m-1;
				ans[cnt][2]=n-1;
				ans[cnt][3]=m;
				ans[cnt][4]=n;
				ans[cnt][5]=m-1;
				a[n][m-1]=0;
				a[n-1][m-1]=a[n-1][m]=1;
			}
			else
			{
				++cnt;
				ans[cnt][0]=n-1;
				ans[cnt][1]=m-1;
				ans[cnt][2]=n-1;
				ans[cnt][3]=m;
				ans[cnt][4]=n;
				ans[cnt][5]=m;
				a[n][m]=0;
				a[n-1][m-1]=a[n-1][m]=1;
			}
			res=2;
		}
		if(res==2)
		{
			if(a[n][m-1]==a[n-1][m])
			{
				if(a[n][m-1]==1)
				{
					++cnt;
					ans[cnt][0]=n-1;
					ans[cnt][1]=m-1;
					ans[cnt][2]=n-1;
					ans[cnt][3]=m;
					ans[cnt][4]=n;
					ans[cnt][5]=m;
					++cnt;
					ans[cnt][0]=n-1;
					ans[cnt][1]=m-1;
					ans[cnt][2]=n;
					ans[cnt][3]=m-1;
					ans[cnt][4]=n;
					ans[cnt][5]=m;
				}
				else
				{
					++cnt;
					ans[cnt][0]=n-1;
					ans[cnt][1]=m-1;
					ans[cnt][2]=n;
					ans[cnt][3]=m-1;
					ans[cnt][4]=n-1;
					ans[cnt][5]=m;
					++cnt;
					ans[cnt][0]=n;
					ans[cnt][1]=m;
					ans[cnt][2]=n;
					ans[cnt][3]=m-1;
					ans[cnt][4]=n-1;
					ans[cnt][5]=m;
				}
			}
			else
			{
				if(a[n-1][m-1]==1&&a[n-1][m]==1)
				{
					++cnt;
					ans[cnt][0]=n-1;
					ans[cnt][1]=m-1;
					ans[cnt][2]=n;
					ans[cnt][3]=m-1;
					ans[cnt][4]=n;
					ans[cnt][5]=m;
					++cnt;
					ans[cnt][0]=n-1;
					ans[cnt][1]=m;
					ans[cnt][2]=n;
					ans[cnt][3]=m-1;
					ans[cnt][4]=n;
					ans[cnt][5]=m;
				}
				else if(a[n-1][m-1]==1&&a[n][m-1]==1)
				{
					++cnt;
					ans[cnt][0]=n-1;
					ans[cnt][1]=m-1;
					ans[cnt][2]=n-1;
					ans[cnt][3]=m;
					ans[cnt][4]=n;
					ans[cnt][5]=m;
					++cnt;
					ans[cnt][0]=n;
					ans[cnt][1]=m-1;
					ans[cnt][2]=n-1;
					ans[cnt][3]=m;
					ans[cnt][4]=n;
					ans[cnt][5]=m;
				}
				else if(a[n][m]==1&&a[n-1][m]==1)
				{
					++cnt;
					ans[cnt][0]=n;
					ans[cnt][1]=m;
					ans[cnt][2]=n;
					ans[cnt][3]=m-1;
					ans[cnt][4]=n-1;
					ans[cnt][5]=m-1;
					++cnt;
					ans[cnt][0]=n-1;
					ans[cnt][1]=m;
					ans[cnt][2]=n;
					ans[cnt][3]=m-1;
					ans[cnt][4]=n-1;
					ans[cnt][5]=m-1;
				}
				else
				{
					++cnt;
					ans[cnt][0]=n;
					ans[cnt][1]=m;
					ans[cnt][2]=n-1;
					ans[cnt][3]=m;
					ans[cnt][4]=n-1;
					ans[cnt][5]=m-1;
					++cnt;
					ans[cnt][0]=n;
					ans[cnt][1]=m-1;
					ans[cnt][2]=n-1;
					ans[cnt][3]=m;
					ans[cnt][4]=n-1;
					ans[cnt][5]=m-1;
				}
			}
		}
		printf("%d\n",cnt);
		for(int i=1;i<=cnt;++i)
		{
			for(int j=0;j<6;++j)
				printf("%d ",ans[i][j]);
			printf("\n");
		}	
		cnt=0;
	}
	return 0;
}
```


---

