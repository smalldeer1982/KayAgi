# [COCI 2022/2023 #1] Desni klik

## 题目背景

NFP 即未来！当谈到金融话题时，Noa 的朋友们都希望听到他说这句话。

## 题目描述

NFP 是一种加密货币。一枚 NFP 在 $s$ 天内的价值可以用一个仅包含字符``.``与``#``的 $r$ 行 $s$ 列字符矩阵表示。第 $i$ 列中自底向上第 $j$ 行的``#``表示第 $i$ 天该 NFP 的价值为 $j$。

NFP 的“不安全度”定义为在 $s$ 天之内其价值到达的最大值与最小值之差。

```
....##.
#..#...
.##....
......#
```
如上，这枚 NFP 在 $7$ 天内的价值依次为：$3,2,2,3,4,4,1$。它的“不安全度”是3。

现在 Noa 想让你帮他确定他手中 $n$ 枚 NFP 的不安全度。

## 说明/提示

| 子任务 | 分值 | 特殊性质 |
| :----------: | :----------: | :----------: |
| $1$ | $5$ | $r=s=2$ |
| $2$ | $15$ | $n=1$ |
| $3$ | $30$ | 无特殊性质 |


对于 $100\%$ 的数据，$1\leq n \leq 20,2\leq r,s \leq50$。

本题满分 $50$ 分。

## 样例 #1

### 输入

```
4 2 2
##
..
..
##
#.
.#
.#
#.```

### 输出

```
0
0
1
1```

## 样例 #2

### 输入

```
1 5 8
.....#.#
...#..#.
..#.#...
.#......
#.......```

### 输出

```
4```

## 样例 #3

### 输入

```
2 3 3
...
##.
..#
.#.
#..
..#```

### 输出

```
1
2```

# 题解

## 作者：QWQ_SenLin (赞：4)

思路其实很好想，就是计算 每个 $\text{NFP}$ 第 $i$ 天的价值 $j$，最大值减最小值既是答案。

需要注意的是要先枚举列，再从下到上枚举行。

```cpp
for(int j = 1;j <= s;j++){ //枚举列
	int i = r;
	while(i >= 1 && t[i][j] == '.') //下到上枚举行直到遇到 #
		i--;
	minn = min(minn , r - i + 1); //更新最小
	maxn = max(maxn , r - i + 1); //更新最大
}
printf("%d\n" , maxn - minn); //答案就是最大-最小
```

---

## 作者：LegendaryGrandmaster (赞：4)

解释一下题目描述：
```
天数 | 1 2 3 4 5 6 7 | 权值
------------------------
     | . . . . # # . | 4
     | # . . # . . . | 3
     | . # # . . . . | 2
     | . . . . . . # | 1
```

这题和往常不同的是，不是看**行**而是看**列**。

我们只需要把行和列调换过来就行了。因为权值和所对应的下标正好相反，所以权值即为 $n-i+1$。

取最大值最小值相减输出即可。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
char a[101][101];
signed main()
{
	int t,n,m;
	cin>>t>>n>>m;
	while(t--){
		int ma=0,mi=INT_MAX;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)cin>>a[i][j];
		for(int j=1;j<=m;j++){
			int x=0;
			for(int i=1;i<=n;i++)
				if(a[i][j]=='#'){
					x=n-i+1;
					break;
				}
			ma=max(ma,x);
			mi=min(mi,x);
		}
		cout<<ma-mi<<'\n';
	}
}
```

---

## 作者：lailai0916 (赞：3)

## 原题链接

- [洛谷 P9028 [COCI2022-2023#1] Desni klik](https://www.luogu.com.cn/problem/P9028)

## 题意简述

给定一个仅包含 `.` 与 `#` 的字符矩阵，求最上面的 `#` 和最下面的 `#` 的行数差。

## 解题思路

每次读入到 `#` 时，分别维护行号的最大值与最小值。

最后输出最大值与最小值的差。

## 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int inf=0x3f3f3f3f;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n,r,s;
	cin>>n>>r>>s;
	while(n--)
	{
		int mx=0,mn=inf;
		for(int i=1;i<=r;i++)
		{
			for(int j=1;j<=s;j++)
			{
				char f;
				cin>>f;
				if(f=='#')
				{
					mx=max(mx,i);
					mn=min(mn,i);
				}
			}
		}
		cout<<mx-mn<<'\n';
	}
	return 0;
}
```

---

## 作者：Yun_Mengxi (赞：2)

[博客食用更佳](https://www.luogu.com.cn/blog/758416/solution-p9028)

#### 题意简述
[题目传送门](https://www.luogu.com.cn/problem/P9028)

给定 $n$ 个 $r$ 行 $s$ 列由`#`和`.`组成的条形统计图，求最大的数与最小的数之间的差，$1\le n\le20$，$1\le r\le20$，$1\le s\le20$。

#### 题目分析
一道典型的模拟题，读入条形统计图可以用 char 数组，用 $Max$ 记录**最大**的数，用 $Min$ 记录**最小**的数。

#### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n, r, s;
char sc[55];                                //sc为输入的每一行的统计图。
int Max, Min;                               //Max为最大的数，Min为最小的数。
int main() {
	cin >> n >> r >> s;
	while (n--) {
		Max = 0;
		Min = 55;
		for (int i = r; i >= 1; i--) {     //
			for (int j = 1; j <= s; j++) { //求最大的数和最小的数。
				cin >> sc[j];
				if (sc[j] == '#') {        //如果这里有数。
					Max = max(Max, i);
					Min = min(Min, i);
				}
			}
		}
		cout << Max - Min << endl;
	}
	return 0;
}
```
完结撒花，[AC记录](https://www.luogu.com.cn/record/101575950)。

---

## 作者：_5t0_0r2_ (赞：1)

这题是个变相求极差的题。求最大数和最小数可以用“打擂台”法，但要注意如何读入。

读入一个字符矩阵，最好的方式是读入 $r$ 个 string 类型。同时行的遍历应该是从 $r$ 到 $1$ ，这样如果读到 ``#`` 时，得到的结果就是 $j$ 。

# AC code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,r,s;
int main(){
	cin >> n >> r >> s;
	for(int i = 1;i <= n;i++){
		int Min = 60,Max = -1;
		for(int j = r;j >= 1;j--){
			string t;
			cin >> t;
			for(int k = 0;k < s;k++){
				if(t[k] == '#'){
					Max = max(Max,j);
					Min = min(Min,j);
				}
			}
		}
		printf("%d\n",Max - Min);
	}
	return 0;
}
```


---

## 作者：gloomy_ (赞：1)

一道简单的字符数组处理题。  
**不安全度定义**  
每一列`#`的位置（从下往上数）为这一列的价值，所有列中最大价值与最小价值的差即为它的不安全度。

**变量定义**  
`char a[][]` 储存字符  
`int b[]` 储存每一列的价值

**每列价值计算**  
双重循环（注意外面一层是列，里面一层是行），每一列只要找到了`#`就可以结束了，因为一列有且仅有1个`#`。
```cpp
for(int j=1;j<=s;j++)
{
	for(int t=1;t<=r;t++)
	{
		if(a[r-t+1][j]=='#')
		{
			b[j]=t;
			break;
		}
	}
}
```
**不安全度计算并输出**  
找到最大最小值，相减。  
```cpp
int maxb=1,minb=1;//最大最小值的下标 
for(int j=1;j<=s;j++)
{
	if(b[j]>b[maxb])
	{
		maxb=j;
	}		
   if(b[j]<b[minb])
	{
		minb=j;
	}
}
cout<<b[maxb]-b[minb]<<endl;
```
**全部代码**  
```cpp
#include<bits/stdc++.h>
using namespace std;
char a[51][51];
int n,r,s,b[51];
int main()
{
	cin>>n>>r>>s;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=r;j++)
		{
			for(int t=1;t<=s;t++)
			{
				cin>>a[j][t];
			}
		}
		for(int j=1;j<=s;j++)
		{
			for(int t=1;t<=r;t++)
			{
				if(a[r-t+1][j]=='#')
				{
					b[j]=t;
					break;
				}
			}
		}
		int maxb=1,minb=1;//最大最小值的下标 
		for(int j=1;j<=s;j++)
		{
			if(b[j]>b[maxb])
			{
				maxb=j;
			}
			if(b[j]<b[minb])
			{
				minb=j;
			}
		}
		cout<<b[maxb]-b[minb]<<endl;
	}
	return 0;
}
```


---

## 作者：Loser_Syx (赞：1)

## 思路

其实代码并不难，就是模拟，但是在这里每天的价值是在一列的而不是一行，我一开始就是因为这个 WA 了不下 $10$ 次，也就是说，在两层 `for` 是要先写遍历列的，再写遍历行的，剩下就没什么好说的，看代码吧。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
string str[101];
int main(){
	int n, r, s;
	scanf("%d %d %d",&n, &r, &s);
	while(n--){
		int mnn = 114514, mxn = -1919810;
		for(int i = 1; i <= r; i++){
			cin >> str[i];
		}
		for(int j = 0; j < s; j++){//天数在列
			for(int i = 1; i <= r; i++){//价格在行
				if(str[i][j] == '#'){//如果是#的话就说明，这一天价格是r-i+1
					mnn = min(mnn, r - i + 1);//取最小值
					mxn = max(mxn, r - i + 1);//取最大值
					break;//下一天
				}
			}
		}
		printf("%d\n", mxn - mnn);
	}
    return 0;
}
```

---

## 作者：InversionShadow (赞：1)

## P9028 [COCI2022-2023#1] Desni klik 题解

### 思路：

考虑到题目求的是每一列，所以不好处理，我们可以将矩阵顺时针旋转 $90$ 度，所以题目求的每一列就变成了每一行。

**注意：旋转后，矩阵的行数变成了 $s$，列数变成了 $r$。**

### Code:

```cpp
#include <bits/stdc++.h>

using namespace std;

int n, r, s, h[10001];
char c[1001][1001], g[1001][1001];

int main() {
  cin >> n >> r >> s;
  for (int i = 1; i <= n; i++) {
    memset(h, 0, sizeof(h));  // 多测清零
    for (int j = 1; j <= r; j++) {
      for (int k = 1; k <= s; k++) {
        cin >> c[j][k];
      }
    }
    for (int j = 1; j <= s; j++) {
      for (int k = r; k >= 1; k--) {
        g[j][k] = c[k][j];
      }
    }
    /*
    for (int j = 1; j <= r; j++) {
      for (int k = s; k >= 1; k--) {
        cout << g[j][k];
      }
      cout << endl;
    }
    */
    for (int j = 1; j <= s; j++) {
      for (int k = 1; k <= r; k++) {
        if (g[j][k] == '#') {
          h[j] = k;
        }
      }
    }
    /*
    for (int j = 1; j <= s; j++) {
      cout << h[j] << ' ';
    }
    cout << '\n'; 
    */
    int maxx = 0;
    for (int j = 1; j <= s; j++) {
      for (int k = 1; k <= s; k++) {
        maxx = max(maxx, abs(h[j] - h[k])); 
      }
    }
    cout << maxx << endl; 
  }
  return 0;
}

/*

.....#.#
...#..#.
..#.#...
.#......
#.......

#....   1
.#...   2
..#..   3
...#.   4
..#..    3
....#    5
...#.    4
....#   5

...
##.
..#

.#.  2   j = 1, k = 2
.#.  2
#..  1
*/ 
```


---

## 作者：zhuweiqi (赞：1)

# 枚举大法：

对于每个 NFP，枚举其每一列的每一行，找出每一列的价值，再记录最小值和最大值即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
char a[55][55];
int main(){
	int n,r,s;
	scanf("%d %d %d",&n,&r,&s);
	while(n--){
		int maxs=0,mins=100;
		for(int i=1;i<=r;i++) scanf("%s",a[i]+1);
		for(int j=1;j<=s;j++){
			for(int i=1;i<=r;i++){
				if(a[i][j]=='#'){
					if(r-i+1<mins) mins=r-i+1;
					if(r-i+1>maxs) maxs=r-i+1;
					break;
				}
			}
		}
		printf("%d\n",maxs-mins);
	}
    return 0;
}
```

---

