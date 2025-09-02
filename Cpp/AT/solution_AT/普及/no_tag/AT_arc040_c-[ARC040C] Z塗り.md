# [ARC040C] Z塗り

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc040/tasks/arc040_c

イカの高橋君は床を塗るのが大好きです。床は $ N\ \times\ N $ のマス目状に区切られており、すでにいくつかのマスは塗られています。$ i $ 行目 $ j $ 列目のマスをマス $ (i,j) $ と呼ぶことにします。高橋君は特殊なインク発射装置を用いて床を塗ろうとしています。この装置を使うと、以下のように床を塗ることができます。

- 任意の整数 $ r,\ c $ を入力して装置のボタンを押すと、「$ i\ =\ r $ かつ $ j\ ≦\ c $」または「$ i\ =\ r+1 $ かつ $ j\ ≧\ c $」を満たすようなすべてのマス $ (i,j) $ を塗ることができる。

高橋君は、全てのマスをこの装置で塗ろうと思っています。このとき、装置を使う必要のある回数の最小値を求めてください。

## 说明/提示

### Sample Explanation 1

インク発射装置はこの入力のような形を綺麗に塗ることができます。

### Sample Explanation 3

はじめから全て塗られていることもあります。

## 样例 #1

### 输入

```
7
...oooo
oo.....
ooooooo
ooooooo
.....oo
oooo...
ooooooo```

### 输出

```
2```

## 样例 #2

### 输入

```
4
.oo.
..oo
o..o
oo..```

### 输出

```
3```

## 样例 #3

### 输入

```
1
o```

### 输出

```
0```

# 题解

## 作者：Ray_yi (赞：1)

### 思路：

可以直接暴力枚举。

我们可以先找到最右上角的那个格子，枚举这个位置能否涂色。涂色时，按照题目给的两种方式涂色，建一个计数器，每次加 $1$ 最后输出即可。

### 代码：


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,ans;
signed main(){
	cin>>n;
	vector<string> s(n);
	for(int i=0;i<n;i++) cin>>s[i];
	for(int i=0;i<n;i++){//i表示r 
		for(int j=n-1;j>=0;j--){//j表示c 
			if(s[i][j]=='.'){//如果需要涂色 
				for(int k=j;k>=0;k--) s[i][k]='o';//第一个条件 
				if(i!=n-1){//特判 
					for(int k=j;k<n;k++) s[i+1][k]='o';//第二个条件 
				}
				ans++;//涂色次数+1 
			}
		}
	}
	cout<<ans<<"\n";
	return 0;
}
//已AC
```

---

## 作者：Eric1030 (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/AT_arc040_c)
---
这道题就是一个枚举题，通过题目中说的涂色条件我们就知道要先从右上角开始枚举，但枚举什么呢？答案是我们要枚举每个位置看它能不能涂色，能涂色就涂色。

下面是枚举时的代码框架。
```cpp
for (int i = 1;i <= n;i++)//i也就是r，j是c
{
    for (int j = n; j >= 1; j--)//枚举，从右上角开始
    {
        if (能涂色)
        {
            涂色次数+1
            涂色
        }
    }
}
```
我们可以用输入进来的二维数组来看它能不能涂色，当当前的 $a[i][j]$ 是 ```.``` 时就可以涂色。那么判断就可以转换为下面的代码。

```cpp
if(a[i][j]=='.')
```

涂色次数 $+1$ 这件事很简单，我们只要用 $cnt$ 来记录就可以了。

涂色的时候我们可以用题目给的条件来涂色，但要注意的是在涂色时要把那个点变成字符  ```o```。转换成代码就是这样。


```cpp
for (int x = 1; x <= j; x++)//第一个条件
{
	a[i][x] = 'o';//涂色
}
for (int x = j; x <= n; x++)//第二个条件
{
	a[i + 1][x] = 'o';//涂色
}
```
整体的思路就讲完了，下面就是 [AC](https://www.luogu.com.cn/record/197980924) 代码。
```cpp
#include <bits/stdc++.h> 
using namespace std;
int n, cnt;
char a[105][105];
void cor(int i, int j)//涂色函数
{
	for (int x = 1; x <= j; x++)//第一个条件
	{
		a[i][x] = 'o';//涂色
	}
	for (int x = j; x <= n; x++)//第二个条件
	{
		a[i + 1][x] = 'o';//涂色
	}
}
int main()
{
	//输入数据
	cin >> n;
	for (int i = 1;i <= n;i++)
	{
		for (int j = 1;j <= n;j++)
		{
			cin >> a[i][j];
		}
	}
	for (int i = 1;i <= n;i++)//i也就是r，j是c
	{
		for (int j = n; j >= 1; j--)//枚举，从右上角开始
		{
			if (a[i][j] == '.')//如果能涂色
			{
				cnt++;//涂色次数+1
				cor(i, j);//调用涂色函数
			}
		}
	}
	cout << cnt << endl;//输出cnt（不换行不得分）
	return 0;//结束！
}
```

无注释版本。

```cpp
#include <bits/stdc++.h> 
using namespace std;
int n, cnt;
char a[105][105];
void cor(int i, int j)
{
	for (int k = 1; k <= j; k++)
	{
		a[i][k] = 'o';
	}
	for (int k = j; k <= n; k++)
	{
		a[i + 1][k] = 'o';
	}
}
int main()
{
	cin >> n;
	for (int i = 1;i <= n;i++)
	{
		for (int j = 1;j <= n;j++)
		{
			cin >> a[i][j];
		}
	}
	for (int i = 1;i <= n;i++)
	{
		for (int j = n; j >= 1; j--)
		{
			if (a[i][j] == '.')
			{
				cnt++;
				cor(i, j);
			}
		}
	}
	cout << cnt << endl;
	return 0;
}
```

---

## 作者：Dream_Stars (赞：0)

## 题目大意：
这道题让我们将一个正方形按题目的涂色规则全部涂色，并且求出最少涂色的次数。

## 算法分析：
暴力枚举。\
我们可以选择两重循环求解。枚举每一个 $r$ 和 $c$ 点，直到每一个点都涂色了。\
按照两种涂色规则进行涂色，并记录答案，输出。
## 代码展示：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define T 'o'

using namespace std;

const int N = 10010;

ll n,ans;
char a[N][N];

void read(){
	cin >> n;
	for(int i = 1 ; i <= n ; i++)
	  for(int j = 1 ; j <= n ; j++)
	    cin >> a[i][j];
	return ;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
  read();//读入。
	for(int r = 1 ; r <= n ; r++)
		for(int c = n ; c >= 1 ; c--)//暴力枚举。
			if(a[r][c] != T){
	      for(int i = 1 ; i <= c ; i++)
				  a[r][i] = T;
	      for(int i = c ; i <= n ; i++)
				  a[r + 1][i] = T; //涂色。
				ans++;//记录。
		  }
	cout << ans << endl;//输出记得加换行，你谷AT特性。
	return 0;
}
```

---

## 作者：Red_river (赞：0)

### 题目大意
题目讲的其实已经很清楚了，就是涂色，只要满足以下条件就会上色。

1. $i=r,j\le c$。
1. $i=r+1,j\ge c$。

所以我们就可以发现，肯定要优先考虑右上角的，毕竟在方法二中可是要下一行涂色的。所以我们就可以得出：**从右上角一次涂色**。至于如何实现，具体看**代码及注释部分**。

### CODE
```
#include<bits/stdc++.h>
#define wk(x) write(x),putchar(' ')
#define wh(x) write(x),putchar('\n')
#define ll long long
#define ull unsigned long long
#define ri register int
#define INF 2147483647
#define mod 998244353
#define N 2005
#define NO printf("No\n")
#define YES printf("Yes\n")
#define f(x,k,y) for(int x=k;x<=y;x++)
using namespace std;
int n,m,k,jk,ans,sum,num,cnt,tot;
int head[N],dis[N],vis[N],wis[N],f[N];
char a[N][N];

void read(int &x)
{
	x=0;int ff=1;char ty;
	ty=getchar();
	while(!(ty>='0'&&ty<='9'))
	{
		if(ty=='-') ff=-1;
		ty=getchar();
	}
	while(ty>='0'&&ty<='9')
		x=(x<<3)+(x<<1)+ty-'0',ty=getchar();
	x*=ff;return;
}

void write(int x)
{
	if(x==0){
		putchar('0');return;
	}
	if(x<0){
		x=-x;putchar('-');
	}
	char asd[201];int ip=0;
	while(x) asd[++ip]=x%10+'0',x/=10;
	for(int i=ip;i>=1;i--) putchar(asd[i]);
	return;
}

void solve(int x,int y)//清除'.'
{
	for(int i=1;i<=y;i++) a[x][i]='o';//方法一 
	for(int i=y;i<=n;i++) a[x+1][i]='o';//方法二 
	return;
} 

signed main()
{
	read(n);
	for(int i=1;i<=n;i++) scanf("%s",a[i]+1);
	for(int i=1;i<=n;i++){
		for(int j=n;j>=1;j--){
			if(a[i][j]=='.'){
				solve(i,j);//在函数里执行，更清楚一点。 
				ans++;
			}
		}
	}
	wh(ans);//你家AT的性质：必须换行？ 
	return 0;
}
```

#### 题外话
这道题其实很简单，它不是说了吗，只要满足条件就会给他涂上色，但其他题解似乎有一点指代不明，还要讨论一下哪个方案的性价比更高？不应该是哪个位置的性价比吗？

---

## 作者：Fubaogege (赞：0)

有一个 $N×N$ 个正方形，其中，第 $i$ 行第 $j$ 列的格子称为格子$(i,j)$。其中一些格子被涂上了色。

我们可以按如下的涂色方法进行任意次涂色：

选定任意整数 $r,c$，然后将所有的格子$(i,j)$进行涂色。格子$(i,j)$必须满足如下条件中的任意一个：

- $i=r,j \le c$。
- $i=r+1,j \ge c$。

所以，我们可以用到遍历，先找到最右上角的一个格子，按照 $r=i,c=j$ 的方法进行涂色，重复执行直到找不到处于右上角的格子。

---

## 作者：a_blue_cell (赞：0)

简单的思维题。

首先，考虑目前的网格中第一个具有如下性质的格子 $(i,j)$。

>所有的格子 $(k,j)(1\le k<i,1\le j\le m)$ 都已涂过了色，所有的格子 $(i,k)(j<k\le m)$ 也都已涂过了色。

我们称这个格子是“处于右上角的格子”。

我们用红圈来代表这个格子，涂有绿色的地方就代表这个地方一定涂了色。

![](https://cdn.luogu.com.cn/upload/image_hosting/5qf4ovuw.png)

显然，想要让这个格子涂上色，我们有两种方法：

1. $r=i,c=j$
2. $r=i-1,c\le j$

让我们用图像来表示（黑色线代表方法 $1$，橙色线代表方法 $2$）：

![](https://cdn.luogu.com.cn/upload/image_hosting/2p1jkco4.png)

显然，由于方法 $2$ 的路径上会经过大量的一定已经涂过色的格子，而方法 $1$ 不会，所以方法 $1$ 的性价比大于方法 $2$。

综上，我们得到了算法思路：

暴力遍历该网格，找到“处于右上角的格子”，按照 $r=i,c=j$ 的方法进行涂色，然后反复执行，直到再也找不到“处于右上角的格子”，输出答案。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans;
char a[105][105];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%s",a[i]+1);
	}
	for(int i=1;i<=n;i++){
		for(int j=n;j>=1;j--){
			if(a[i][j]=='.'){
				ans++;
				int I=i,flag=0;
				for(int k=1;k<=n;k++){
					a[I][k]='o';
					if(k==j&&flag==0){
						flag=1;
						I++,k--;
					}
				}
			} 
		}
	}
	printf("%d\n",ans);
	return 0;
}
```

---

