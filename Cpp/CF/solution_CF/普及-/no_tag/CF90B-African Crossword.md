# African Crossword

## 题目描述

An African crossword is a rectangular table $ n×m $ in size. Each cell of the table contains exactly one letter. This table (it is also referred to as grid) contains some encrypted word that needs to be decoded.

To solve the crossword you should cross out all repeated letters in rows and columns. In other words, a letter should only be crossed out if and only if the corresponding column or row contains at least one more letter that is exactly the same. Besides, all such letters are crossed out simultaneously.

When all repeated letters have been crossed out, we should write the remaining letters in a string. The letters that occupy a higher position follow before the letters that occupy a lower position. If the letters are located in one row, then the letter to the left goes first. The resulting word is the answer to the problem.

You are suggested to solve an African crossword and print the word encrypted there.

## 样例 #1

### 输入

```
3 3
cba
bcd
cbc
```

### 输出

```
abcd```

## 样例 #2

### 输入

```
5 5
fcofd
ooedo
afaoa
rdcdf
eofsf
```

### 输出

```
codeforces```

# 题解

## 作者：Zachary_Cloud (赞：3)

## 题意

有一个 $n×m$ 的字符矩阵，对于每行**或**每列，删去**相同**的字符，最后**按顺序**输出剩下的字符。

## $Sol$

没什么好讲的，就是——$\Large\color{red}\texttt{暴力}$！

没错。$n,m$ 的数据范围就是这么小：$1 \le n,m \le 100$。

$\texttt{However}$，我们就能~~轻松愉快地~~~~水~~过这道题啦。

## $Attention$

$\texttt{First}$，如果你使用的是$\text{字符串}$，这并没有甚问题。但是——如果你真的像题目描述所说的，**把相同的字符删去或改动**的话——

$\huge\texttt{Boom!}$

$\large\color{red}\text{WA}$

55555……$qwq$

$\texttt{So,we should use the}$ $\Large\text{Check}$ $\texttt{or so on.}$

## $Code$

```cpp
#include <bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
using namespace std;
int n, m;
char a[110][110]; //开大点死不了
bool check(int x, int y) {
	for (int i = 1; i <= n; ++i) //判断同一列中是否有相同字符
		if (i == x) continue; //同一个字符当然不能判断
		else if (a[i][y] == a[x][y]) return 0; //返回 false
	for (int i = 1; i <= m; ++i) //判断同一行中是否有相同字符
		if (i == y) continue;
		else if (a[x][i] == a[x][y]) return 0;
	return 1; //返回 true
}
int main() {
	IOS; //独家优化
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		string s;
		cin >> s; //我们知道，cin 是字符串最好的朋友
		for (int j = 1; j <= m; ++j) a[i][j] = s[j - 1]; //读入并存入数组
	}
	for (int i = 1; i <= n; ++i) //逐行逐列一个个扫过去
		for (int j = 1; j <= m; ++j)
			if (check(i, j)) cout << a[i][j]; //如果不重复，输出
	return 0;
}
```

- - -

$\Large\text{The End.}$

---

## 作者：ZolaWatle (赞：3)

# CF90B 【African Crossword】 题解

### 题外话（读者可直接跳到“思路”处）

首先看到这道题，本蒟蒻就被吓到了。因为按照题上所说的方式，不管咋样都不能将样例输入消成样例输出的样子。

后来仔细一看题面才发现，题上说的是: 

输入$ n $,$ m $, 有一个$ n*m $的字符阵，**对于每行或每列**，删去相同的字符，最后按顺序输出剩下的字符。

这根本就不是每行**或**每列嘛，明明是每行**和**每列！（大喊）

然后去看了看英语原文：

To solve the crossword you should cross out $ all $ repeated letters in rows $ and $ columns

这明明说的就是行和列都要消嘛~

所以建议管理大大改一下翻译orz

### 思路

本题的数据范围：$ 1 \leq n,m \leq 100 $, 所以使用$ O(n^3) $的暴力方法可以轻松通过。

于是基本思路就是：每个字符都访问一遍，全部枚举出其字符所在的行与列有无其他与该字符相同的其他字符，如果有，便删去。

这里我们就要用到一个$ opt $数组，$ opt_{i,j} $表示第$ i $行$ j $列的字符是否要删去。遇到重复的字符，就把其所对应的$ opt $数组置为$ 1 $，因为对于每个字符，$ opt $只有$ 01 $两种情况，故使用$ bool $型数组即可。

最后输出时只要看$ opt_{i,j} $是否为零即可，是零就输出。不要有空格或是换行。

### 代码

```cpp
#include <iostream>
#include <cstdio>
#define re register int
using namespace std;

int n,m;
char a[101][101];
bool opt[101][101];  //习惯用全局变量（懒得初始化 

int main()
{
	ios::sync_with_stdio(false);  //玄学优化，只适用于cin，scanf加这个似乎要RE 
	
	std::cin>>n>>m;
	for(re i=1;i<=n;i++)
		for(re j=1;j<=m;j++)
			std::cin>>a[i][j];  //输入不解释 
	
	for(re i=1;i<=n;i++)
		for(re j=1;j<=m;j++)
		{
			for(re k=i+1;k<=n;k++)  //注意是从i+1开始，自己跟自己总不能算重复吧？ 
				if(a[k][j]==a[i][j])
					opt[i][j]=opt[k][j]=1;  //枚举当前行 
			for(re k=j+1;k<=m;k++)
				if(a[i][k]==a[i][j])
					opt[i][j]=opt[i][k]=1;  //枚举当前列 
		}
		
	for(re i=1;i<=n;i++)
		for(re j=1;j<=m;j++)
			if(opt[i][j]==0)
				std::cout<<a[i][j];  //没有重复过就输出 

	return 0;
}

```

### 一个思考：

大家可以想想看，为什么这样的一种优化是错误的，会造成什么样的问题？萌新们可以评论区留言或者私信我，dalao们就当没看见好了~

```cpp
for(re i=1;i<=n;i++)
	for(re j=1;j<=m;j++)
	{
		if(opt[i][j]==1)
			continue;  //这就是那个优化 
		for(re k=i+1;k<=n;k++)
			if(a[k][j]==a[i][j])
				opt[i][j]=opt[k][j]=1;
		for(re k=j+1;k<=m;k++)
			if(a[i][k]==a[i][j])
				opt[i][j]=opt[i][k]=1;
	}
```

博客食用更佳：[戳这里](https://www.luogu.com.cn/blog/FourLeafLovesDZY/solution-cf90b)

原题链接：[CF90B African Crossword](https://www.luogu.com.cn/problem/CF90B)

---

## 作者：伟大的王夫子 (赞：2)

首先，我们按照题目所给方式读入，将所得数组存在一个数组 $a$ 中。

然后，我们按每行和每列来。

先处理每一行。

设 $v_{i, j}$ 表示 $a_{i, j}$ 是否被删去(被删去则为 $1$ )

对于第 $i$ 行，我们遍历 $a_{i, j} $，其中 $j \in [1, m]$

统计每种字符出现的个数并将所得的值计入一个数组 $c$ 中。

然后，我们再重新遍历一次。如果 $a_{i, j}$ 这个字符出现了两次及以上，
那么就说明，它是这一行重复的字符，应当删去。

列的话，同理。

最后，再遍历一遍数组，当遍历到 $a_{i, j}$ 这个字符时，如果 $v_{i, j}=0$ 再输出，否则就不输出这个字符。

这样按顺序遍历便能得到正确答案。

这是一道非常适合新手练习的题目，可以锻炼新手的打字与调试能力，只有把这些基本的题目做好，并练就一定的熟练度，才能为以后的竞赛学习打好扎实的基础。

现在放上代码，供大家参考一下。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, m;
char a[110][110];
bool v[110][110];
main() {
	cin >> n >> m;
	memset(v, 0, sizeof v);
	for (register int i = 1; i <= n; ++i) 
		for (register int j = 1; j <= m; ++j) cin >> a[i][j];
	for (register int i = 1; i <= n; ++i) {
		int c[210];
		memset(c, 0, sizeof c);
		for (register int j = 1; j <= m; ++j) c[a[i][j]]++;
		for (register int j = 1; j <= m; ++j) 
			if (c[a[i][j]] >= 2) v[i][j] = 1;
	}
	for (register int j = 1; j <= m; ++j) {
		int c[210];
		memset(c, 0, sizeof c);
		for (register int i = 1; i <= n; ++i) c[a[i][j]]++;
		for (register int i = 1; i <= n; ++i) if (c[a[i][j]] >= 2) v[i][j] = 1;
	}
	for (register int i = 1; i <= n; ++i)
		for (register int j = 1; j <= m; ++j) 
			if (!v[i][j]) cout << a[i][j];
}
```

---

## 作者：_Legacy (赞：1)

### 分析

本题有一个坑，那就是你要是用了删除法(找每行里相同的字母并删除)可能会出现下面的情况
```
cba ---发现'c'与第三行的'c'重复。
bcd
cbc
```
```
~ba ---删除，变成~。
bcd
~bc
```
这时候输出结果会变成```abcdc```。
### 上代码：

#### 错误代码
```
#include <bits/stdc++.h>
using namespace std;
int n,m;
char a[101][101],b[101];
bool check(int c,int d){
	for(int i=0;i<n;i++){
		if(a[i][d]==a[c][d]&&i!=c){
			a[i][d]='~';
			a[c][d]='~';
			return 0;
		} 
	}
	for(int j=0;j<m;j++){
		if(a[c][j]==a[c][d]&&j!=d){
			a[j][d]='~';
			a[c][d]='~';
			return 0;	
		} 
	}
	return 1;
}//检查是否有重复，发现重复便将其变成'~'.
int main(){
	cin >> n >> m;
	for(int i=0;i<n;i++){
		cin >> b;
		for(int j=0;j<m;j++){
			a[i][j]=b[j];
		}
	}//输入。
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			check(i,j);
		}
	}//检查
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			if(a[i][j]!='~') cout << a[i][j];
		}
	}//输出
} 
```
**输入样例1:**
```
3 3
cba
bcd
cbc
```
**输出样例1：**
```
abcdc
```
**输入样例2:**
```
5 5
fcofd
ooedo
afaoa
rdcdf
eofsf
```
**输出样例2：**
```
cofdeofoadces
```
#### 正确代码
```
#include <bits/stdc++.h>
using namespace std;
int n,m;
char a[101][101],b[101];
bool check(int c,int d){
	for(int i=0;i<n;i++){
		if(a[i][d]==a[c][d]&&i!=c) return 0;
	}
	for(int j=0;j<m;j++){
		if(a[c][j]==a[c][d]&&j!=d) return 0;	
	}
	return 1;
}//检查是否有重复。
int main(){
	cin >> n >> m;
	for(int i=0;i<n;i++){
		cin >> b;
		for(int j=0;j<m;j++){
			a[i][j]=b[j];
		}
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			if(check(i,j)){//若有重复拒绝输出。
				cout << a[i][j];
			}
		}
	}
}
//CF90B
```

---

## 作者：chl123123 (赞：0)

总的来说，这道题不难，但是一道十分有价值题目。

思路：

我的思路是用一个数组存字符矩阵，然后用两个数组分别存横排删去的字符与竖列删去的字符，用三层循环解决。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
char a[110][110];
int bj1[110][110],bj2[110][110];
int main()
{
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>a[i][j];
   	//------------------------------------------------------
 	//核心代码：
   	//每一行，每一列开始查找
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(bj1[i][j]!=1)//特判防止重复查找
				for(int k=j+1;k<=m;k++)
					if(a[i][j]==a[i][k])
						bj1[i][j]=bj1[i][k]=1;
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
			if(bj2[j][i]!=1)
				for(int k=j+1;k<=n;k++)
					if(a[j][i]==a[k][i])
						bj2[j][i]=bj2[k][i]=1;
   	//------------------------------------------------------
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(bj1[i][j]!=1&&bj2[i][j]!=1)//看有没有被删去
				cout<<a[i][j];
	return 0;
}

```
 _最后 [AC](https://www.luogu.com.cn/record/55077047)_ 

---

## 作者：Allanljx (赞：0)

## 题意
输入 $n$ ， $m$ ，有一个 $n * m$ 的字符阵，对于每行和每列，删去相同的字符，最后按顺序输出剩下的字符。
## 思路
一看数据范围：$1<=n,m<=100 $ ，暴力。

暴力枚举每个字符，去找这个字符的所在行有没有和它相同的字符，如果有，就将 $book$ 赋值成一。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
char a[101][101];
bool book[101][101];//零代表没有重复，一代表有重复 
int main()
{
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)//输入 
		for(int j=1;j<=m;j++)
			cin>>a[i][j];
	for(int i=1;i<=n;i++)//枚举行 
		for(int j=1;j<=m;j++)//枚举列 
			for(int k=i+1;k<=n;k++)//枚举这列有没有和当前字符一样的 
				if(a[i][j]==a[k][j])//如果一样就标记为一 
					book[i][j]=book[k][j]=1;
	for(int i=1;i<=n;i++)//枚举行 
		for(int j=1;j<=m;j++)//枚举列 
			for(int k=j+1;k<=m;k++)//枚举这行有没有和当前字符一样的 
				if(a[i][j]==a[i][k])//如果一样就标记为一 
					book[i][j]=book[i][k]=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(book[i][j]==0)//如果为零就输出 
				cout<<a[i][j];
	return 0;
}
```


---

## 作者：Zhoumy (赞：0)

因为$n$和$m$都小于$100$，所以可以直接枚举过  
```
#include<iostream>
using namespace std;
char map[101][101];//数组存储
int main(){
	int a,b;
	cin>>a>>b;
	for(int i=1;i<=a;i++)for(int j=1;j<=b;j++)cin>>map[i][j];
	for(int i=1;i<=a;i++){
		for(int j=1;j<=b;j++){
			bool tmp=1;
			for(int k=1;k<=b;k++){//判断行列是否有重复的
				if(k!=j&&map[i][k]==map[i][j]){
					tmp=0;
					break;
				}
			}
			for(int k=1;k<=a;k++){//判断行列是否有重复的
				if(k!=i&&map[k][j]==map[i][j]){
					tmp=0;
					break;
				}
			}
			if(tmp==1)cout<<map[i][j];//如果没有直接输出
		}
	}
	return 0;
}
```

---

## 作者：K2sen (赞：0)

### CF90B African Crossword
两边才A，菜死了/kk
[传送门](https://www.luogu.com.cn/problem/CF90B)
### 思路
行和列分这改的

改的时候不要直接在字符串中改，要不然会WA

就是行和列直接会产生影响，所以开个数组还是比较好的

分着改的时候不要枚举错$n$和$m$

### code
```cpp
#include <bits/stdc++.h>
#define ll long long
#define N 100010
#define M 110

using namespace std;
int n, m;
char ss[M][M]; bool sy[M][M];

int read() {
	int s = 0, f = 0; char ch = getchar();
	while (!isdigit(ch)) f |= (ch == '-'), ch = getchar();
	while (isdigit(ch)) s = s * 10 + (ch ^ 48), ch = getchar();
	return f ? -s : s;
}

int main() {
	n = read(), m = read();
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			cin >> ss[i][j];
	for (int i = 1; i <= n; i++) {
		map<char, int> ma;
		for (int j = 1; j <= m; j++)
			ma[ss[i][j]]++;
		for (int j = 1; j <= m; j++)
			if (ma[ss[i][j]] > 1) 
				sy[i][j] = 1;
	}
	for (int i = 1; i <= m; i++) {
		map<char, int> ma;
		for (int j = 1; j <= n; j++)
			ma[ss[j][i]]++;
		for (int j = 1; j <= n; j++)
			if (ma[ss[j][i]] != 1) 
				sy[j][i] = 1;
	}
	for (int i = 1; i <= n; i++) 
		for (int j = 1; j <= m; j++)
			if (!sy[i][j]) cout << ss[i][j];
}
```

---

## 作者：cq_loves_Capoo (赞：0)

这个蒟蒻发现他的方法和别人的都不同，于是他又来水题解了。     
   
本题的思路应该不太难，暴力枚举 $O(N^{3})$ 可以卡过，所以，我就用了一种暴力枚举的办法来AC了这道题。     
     
AC代码：（有解释）
```
#include<bits/stdc++.h>
using namespace std;
int n,m; //n行m列 
bool b[101][101];//定义一个 bool 数组来标记每个点是否有过重复 
char a[101][101];//二维字符数组 
int main()//主程序（为了让大家适应这个人改了下码风） 
{
	ios::sync_with_stdio(false);//这个可以加也可以不加，一般用于卡常 
	cin>>n>>m;//输入 
	for (int i=1;i<=n;i++)
	for (int j=1;j<=m;j++)
		cin>>a[i][j];//二维字符数组输入 
	for (int i=1;i<=n;i++)
	for (int j=1;j<=m;j++)
	{
		//可怕的暴力枚举，从上到下从左到右都扫一遍 
		for (int k=i+1;k<=n;k++) if (a[k][j]==a[i][j]) b[k][j]=true,b[i][j]=true;//如果有相同的就把该字符和他对应的字符标记 
		for (int k=i-1;k>=1;k--) if (a[k][j]==a[i][j]) b[k][j]=true,b[i][j]=true;//同上 
		for (int k=j+1;k<=m;k++) if (a[i][k]==a[i][j]) b[i][k]=true,b[i][j]=true;
		for (int k=j-1;k>=1;k--) if (a[i][k]==a[i][j]) b[i][k]=true,b[i][j]=true;
	}
	for (int i=1;i<=n;i++)
	for (int j=1;j<=m;j++)
	if (b[i][j]==false) cout<<a[i][j];//判断并输出 
	return 0;//程序结束 
}

```


---

## 作者：Lucifer_Bartholomew (赞：0)

# ~~其实直接暴力就好了~~
直接暴力对整个表遍历。

对于每个点，对于与它同列或同行的相同的字符，用bool数组标记位置。最后输出时，未被标记的点直接输出就行了
代码
------------

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
char ma[110][110];
bool v[110][110];
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
	{
		getchar();
		for(int j=1;j<=m;++j)
			scanf("%c",&ma[i][j]);
	}
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
		{
			for(int k=1;k<=n;++k)
				if(!v[k][j]&&ma[k][j]==ma[i][j]&&k!=i)v[k][j]=1;
			for(int k=1;k<=m;++k)
				if(!v[i][k]&&ma[i][k]==ma[i][j]&&k!=j)v[i][k]=1;
		}
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			if(!v[i][j])printf("%c",ma[i][j]);
	puts("");
	return 0;
}
```
~~蒟蒻代码，大佬勿喷~~

---

