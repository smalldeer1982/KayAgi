# 「SWTR-7」Scores（easy version）

## 题目背景

#### 本题是 Scores 的 easy 版本。注意题目限制与 [hard](https://www.luogu.com.cn/problem/P7876) 版本不同。

#### 请注意特殊的时空限制，题目描述下方有简化题意。

## 题目描述

小 A 的班上有 $n$ 个学生。最近他们进行了一场考试，共有 $m$ 个学科。第 $i$ 个学生第 $j$ 门学科的得分为**整数** $s_{i,j}\ (0\leq s_{i,j}\leq 100)$。对于学生 $i$，如果**存在另一个**学生 $j$ 满足：学生 $i$ **每门学科的成绩都不大于**学生 $j$，学生 $i$ 就会感到失落。

中秋节快到了，善良的小 A 不想让任何一个同学感到失落，他决定 hack 学校的管理系统，修改每一位同学的成绩。在做出这样危险的举动之前，小 A 希望知道自己能否达到目标。不过，由于学生和科目实在太多，他想请你帮助他构造出一种合法的方案。

如果存在一张成绩表，满足没有任何一位同学感到失落，请先输出 $\texttt{YES}$，再**任意**输出一种符合要求的成绩表；否则输出 $\texttt{NO}$。

---

**「简化题意」**

试构造一个 $n\times m$ 的矩阵 $s$，满足所有元素为 $[0,100]$ 之间的整数，且对于任意 $i,j\ (i\neq j)$ 存在一个 $k$ 使得 $s_{i,k}>s_{j,k}$。

## 说明/提示

**「Special Judge」**

**本题使用 Special Judge。请认真阅读输出格式，输出格式有误可能导致 UKE。**

SPJ 首先会判断你的第一行输出是否与答案相同。  
如果相同且答案为 $\texttt{YES}$，则 SPJ 会判断你的输出是否符合小 A 的要求：

- $0\leq s_{i,j}\leq 100$ 且 $s_{i,j}$ 为整数。
- 每个学生至少有一个科目的成绩比另一个学生高。

如果有解且你输出 $\texttt{YES}$，但给出方案错误，你将获得该测试点 $50\%$ 的分数。

**「数据范围与约定」**

本题共有 6 个测试点。

- Testcase #0（1 point）：是样例。
- Testcase #1（10 points）：$n=1$。
- Testcase #2（10 points）：$m=1$。
- Testcase #3（20 points）：$m=2$。
- Testcase #4（30 points）：$n\leq m$。
- Testcase #5（29 points）：无特殊限制。

对于 $100\%$ 的数据，$1\leq n,m\leq 100$，$T=20$（除 Testcase #0）。  
对于所有测试点，**时间限制 200ms，空间限制 16MB。**

**「题目来源」**

[Sweet Round 07](https://www.luogu.com.cn/contest/51774) A1。  
idea & solution & data：[Alex_Wei](https://www.luogu.com.cn/user/123294)；验题：[chenxia25](https://www.luogu.com.cn/user/138400)。

## 样例 #1

### 输入

```
0
4
5 3
1 10
17 1
2 7```

### 输出

```
YES
100 99 97
98 100 99
95 97 100
0 98 100
99 99 99
YES
1 2 3 4 5 6 7 8 9 10
NO
YES
95 99 76 88 87 51 49
72 100 80 92 100 60 60```

# 题解

## 作者：MY（一名蒟蒻） (赞：9)

[P7873 「SWTR-07」Scores（easy version）](https://www.luogu.com.cn/problem/P7873)

小清新构造。

我觉得看简化题意不如看原题面，有代入感会比较好理解题目。

不能让一个人的所有科目分数都不比另一个人高。

无解的情况只有有多个人且只有一个科目的时候。

**做题一定要关注数据范围。**

注意到最多只有 $100$ 科和一百个人。那我们可以**假定每一科每个人的分数互不相同**来让题目变得简单一点。这里的语序很重要。

假设有个人在某一科有 $x$ 个人比他高，那么他只要在另一科考得比这 $x$ 个人都高就好。

讲到这里思路已经呼之欲出了。我赛时的想法是安排相邻的两科的分数一科升序一科降序。写题解的时候又想到让前面 $n-1$ 科全部升序或者降序，最后一科反过来就好。这种思路就留给读者实现了~~我懒得写了~~。


代码实现非常容易，没啥核心代码就放整个了。以下是赛时代码。

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

int sco[110][110];

int main()
{
//  freopen("work.in","r",stdin); freopen("work.out","w",stdout);
    int t,n,m;
    scanf("%d%d",&t,&t);
    while(t--)
    {
    	scanf("%d%d",&n,&m);
    	if(m == 1 && n > 1) puts("NO");
    	else
		{
			puts("YES");
			for(int j=1;j<=m;j++)
				for(int i=1;i<=n;i++)
				{
					if(j&1) sco[i][j]=i;
					else sco[i][j]=n-i+1;
				}
			for(int i=1;i<=n;i++)
			{
				for(int j=1;j<=m;j++) printf("%d ",sco[i][j]);
				puts("");
			}
		}
	}
//  fclose(stdin); fclose(stdout);
    return 0;
}
```

***Thank you for your reading !***

---

## 作者：HYdroKomide (赞：9)

其实感觉这题可以降红。

### 题意：
构造一个矩阵，对于矩阵的每一行，都有一个元素大于其他每一行的这个元素。
### 思路：
只要有了构造思路，只需直接循环输出即可。

首先我们发现，如果人数 $\gt1$ 但是却只有一门学科，那么必有一人分数大于等于其他人，于是输出 `NO`。

对于其他的情况，我们直接开始构造。

我们便可以给每一个人构造一个分数了，我们使某一科分数在编号增加的时候递减，其它分数递增：

#### 语言表述：

第一个人的最后一科分数比其他人都高。

第二个人最后一科分数高于大于他编号的人，其它科分数高于第一个人。

...

第 $n$ 个人除最后一科，其它分数都比别人高。

#### 数列：

第 $1$ 个人：$0,0, ... ,0,100$；

第 $2$ 个人：$1,1, ... ,1,99$；

第 $3$ 个人：$2,2, ... ,2,98$；

$...$

第 $n$ 个人：$n-1,n-1, ... ,n-1,100-n+1$。

于是就一目了然，可以证得每一行都有大于其他行的分数。

我们构造的分数必须满足 $0\le score \le 100$，但是由于 $n \le100$，我们表中出现的分数便不可能 $\lt0$ 或者 $\gt 100$。

每一次循环构造即可。

### 程序如下：
```cpp
#include<cstdio>
#define ri register int
using namespace std;
int T,t,n,m;
int main(){
	scanf("%d%d",&T,&t);//大T没啥用
	while(t--){
		scanf("%d%d",&n,&m);
		if(n>1&&m==1)printf("NO\n");//不可能的情况
		else{
			printf("YES\n");
			for(ri i=0;i<n;i++){
				for(ri j=1;j<m;j++)printf("%d ",i);//输出递增的分数
				printf("%d\n",100-i);//和最后那个递减的分数
			}
		}
	}
	return 0;
}
```

### THE END

---

## 作者：Hiynyuan (赞：8)

### 题目化简
有 $T$ 组数据,每组建立一个正序和一个逆序的数列.
### 主要思路
题目说了,任意两行必须有一个数大于其它行,所以如果只有一门科目并且人数大于一,则不可能成立.而其它情况就可以通过输出一个正序和一个倒序数列,其它都用0来补位.
### CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int t,n,m;
	cin>>t>>t;//输入数据数量 
	for(int h=0;h<t;h++)
	{
		cin>>n>>m;//输入人数和科目数量 
		if(n==1)//如果人数为1则直接输出YES 
		{
			cout<<"YES"<<endl;
			for(int i=0;i<m;i++)
			{
				cout<<i<<" ";
			}
			cout<<endl;
			continue;
		}
		if(m==1)//如果人数不为零而科目为零,则直接输出NO 
		{
			cout<<"NO"<<endl;
			continue;
		}
		cout<<"YES"<<endl;//否则就输出YES 
		int a[n][2];
		for(int i=0;i<n;i++)//建立一个正序和一个逆序数列 
		{
			a[i][0]=n-i;
			a[i][1]=i;
		}
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<m;j++)
			{
				if(j<2)//输出正序和逆序 
				cout<<a[i][j]<<" ";
				else//否则直接输出0 
				cout<<0<<" ";
			}
			cout<<endl;
		}
	}
	return 0;
}
```


---

## 作者：Coros_Trusds (赞：7)

[更好的阅读体验](https://www.cnblogs.com/Coros-Trusds/p/15332934.html)

来一发题解。

## 题目大意

给定 $n,m$，请构造一个 $n\times m$ 的矩阵 $\rm Mat$，矩阵的所有元素范围均为 $[0,100]$ 之间的整数，且对于任意 $i,j(i\neq j)$ 存在一个 $k$ 使得 $\rm Mat_{i,k}>Mat_{j,k}$。

如果存在输出 $\texttt{yes}$，否则输出 $\texttt{no}$。

## 题目分析

既然有 $\rm Special~Judge$，那么我们可以随便构造，只要符合条件就行。

* 对于输出 $\texttt{yes}$ 的情况。

考虑到对于矩阵 $\rm Mat$，我们一定要保证 $\rm Mat_{i,k}>Mat_{j,k}$，那么我们一行中一定要有大的，也一定要有比较小的，那么可以这样来构造：

![](https://z3.ax1x.com/2021/09/21/4tt7c9.png)
[$\color{black}\tiny{Image~courtesy~of~a~certain~person}$](https://www.luogu.com.cn/user/142548)

换句话说就是构造 $\rm Mat = \begin{Bmatrix}1&100-1& 100-1&...&100-1 \\...\\n&100-n&100-n&...&100-n\end{Bmatrix}$

直接构造就好啦。

* 对于输出 $\texttt{no}$ 的情况。

特判 $m=1$ 且 $n>1$ 时。

## 代码

```cpp
//2021/9/21

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include <cstdio>

#define debug(c) cerr<<#c<<" = "<<c<<endl

#define cek(c) puts(c)

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

int mp[ma][ma];

int main(void)
{
	int kase=read(),T=read();
	
	while(T--)
	{
		int n=read(),m=read();
		
		if(m==1 && n>1)
		{
			puts("NO");
			
			continue;
		}
		
		for(register int i=1;i<=n;i++)
		{
			mp[i][1]=i;
			
			for(register int j=2;j<=m;j++)
			{
				mp[i][j]=n-i;
			}
		}
		
		puts("YES");
		
		for(register int i=1;i<=n;i++)
		{
			for(register int j=1;j<=m;j++)
			{
				printf("%d ",mp[i][j]);
			}
			
			printf("\n");
		}
	}
	
	return 0;
}
```

---

## 作者：雨伞CKY (赞：2)

# 题意简述
给定正整数 $n$ 和 $m$，试试构造一个 $n\times m$ 的矩阵 $s$，满足所有元素为 $[0,100]$ 之间的整数，且对于任意 $i,j(i\neq j)$ 存在整数 $k$ 使得 $s_{i,k}\gt s_{j,k}$。

# 题目分析
- 当 $m=1,n\geq 2$ 时，显然无法构造满足题意的矩阵 $s$。
- 否则，始终能构造满足题意的矩阵 $s$，如下所示。

$$
\begin{matrix}
   1 & 1 & \dotsc & 1 & 99\\
   2 & 2 & \dotsc & 2 & 98\\
   3 & 3 & \dotsc & 3 & 97\\
   \vdots & \vdots & \ddots & \vdots & \vdots\\
   n & n & \dotsc & n & 100-n
\end{matrix}
$$

# 代码
```cpp
#include <iostream>
using namespace std;

void construct(int n,int m){
    //构造矩阵。
    for (int i = 1;i <= n;i++){
        for (int j = 1;j < m;j++) cout << i << ' ';
        cout << 100 - i << endl;
    }
    return ;
}

int T,t,n,m;

int main(){
    cin >> T >> t;
    for (int i = 1;i <= t;i++){
        cin >> n >> m;
        if (m == 1 && n >= 2){
            cout << "NO\n";
        }
        else{
            cout << "YES\n";
            construct(n,m);
        }
    }
    return 0;
}
```

---

## 作者：Mortis_Vampire (赞：2)

## Part 1：分析题目

这道题让我们构造出一个矩阵 $s$ ，对于任意 $i,j$ 存在一个 $k$，使得 $s_{i,k}>s_{j,k}$。

可以发现 $i \le j$ 时，只要满足 $s_{i,1}>s_{j,2}$ ，$s_{i,2}<s_{j,1}$ ，矩阵即可成立。

也就是说**只有前两个科目有用**。

而关于矩阵无法实现的特判即为：

当 $m=1$ 且 $n\ne1$ 时，矩阵不存在。(只有一个科目时，除非只有一人，否则无法构造)

然后对于前两个科目的构造，$s_{i,1}=i$，$s_{i,2}=n-i+1$ 是一种比较简单的构造方式。

## Part 2：代码实现

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
int n,t,T;
int main()
{
	cin>>t>>T;
	while(T--)
	{
		int n,m;
		cin>>n>>m;
		if(n!=1&&m==1){
			printf("NO\n");//特判
			continue;
		}
		printf("YES\n");
		int k=0;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++)
			{
				if(j==1)//构造第i个同学的科目1
				cout<<i<<" ";
				else if(j==2)cout<<n+1-i<<" ";//构造第i个同学的科目2
				else cout<<100<<" ";//其他科目怎么输出都可以(记得在0~100之间)
			}
		printf("\n");//注意换行
		}
	}
	return 0;
}
```



---

## 作者：cyhyyds (赞：1)

根据测试点我们逐个讨论。

## Testcase #0
输出样例，不用我多说了吧。

## Testcase #1
$n=1$，所以肯定不会有人使这个人失落。


所以输出一行 ~~乱七八糟~~ $0-m$ 就可以了。

## Testcase #2

$m=1$，所以无论怎么构造，除了 $n=1$ 的时候，都会有人失落，所以输出 $\text{NO}$。

## Testcase #3
距离正解很近的一个测试点。

既然有两个科目，那么就让这个矩阵第一列从小到大递增，第二列从大到小递减即可，这样就能保证任意两行中的一行不会出现没有一个数大于等于另一行的情况。

## Testcase #4
没看懂这个测试点的设置意义，不知道干吗的。

## Testcase #5

要上正解了。

从 Testcase #3 我们发现，当矩阵只有两列时我们可以轻松构造出方案。

那么，对于任何两行的前两列，保证第一列递增，第二列递减，所以矩阵已经满足条件，所以对于一行中后面的 $m-2$ 个数字我们就可以不管它了，全为 $0$ 即可。

所以其实正解就是 Testcase #3！

## 核心代码：
```
int t1 = 0, t2 = 100;
			
for (int i = 1; i <= n; i ++) {
	ans[i][1] = t1 ++;//第一列递增。
	ans[i][2] = t2 --;//第二列递减。
    //其余的都为0即可。
}
			
for (int i = 1; i <= n; i ++) {
	for (int j = 1; j <= m; j ++) {
		printf ("%d ", ans[i][j]);
	}
				
	printf ("\n"); 
}
```


---

## 作者：Waaifu_D (赞：0)

## 题目简述

输出一个 $n*m$ 大小的矩阵，对于任意 $(i,j)$ 的元素，满足至少存在一个 $(i_1,j_1)$ 小于 $(i,j)$ 的元素 。

## 题意

其实大可不必像其他大佬的题解一样那么复杂，我们只需要让偶数列的元素下降，奇数列的元素上升即可，这样就可以满足至少有一个学生比另一个学生的一科成绩差。

~~真有学生看不出来这是改了成绩吗~~

```cpp
#include<cstdio>
#include<iostream>
using namespace std;
int t,n,m,T;
int a,b;
int main()
{
	cin>>T;
	cin>>t;
	while(t--)
	{
		a=0,b=0;
		scanf("%d%d",&n,&m);
		if(n==1)
		{
			printf("YES\n");
			for(register int i=1; i<=m;i++)
			{
				printf("%d ",i);
			}
			printf("\n");
			continue;
		}
		if(m==1) printf("NO\n");
		else
		{
			printf("YES\n");
			a=0,b=100;
			for(register int i=1; i<=n;i++)
			{
				for(register int j=1; j<=m;j++)
				{
					if(j%2==1)
					{
						printf("%d ",a);
					}
					else printf("%d ",b);
				}
				b--;a++;
				printf("\n");
			}
		}
	}
	return 0;
}
```


---

## 作者：言琢დ (赞：0)

考虑如下方式构造：

```cpp
100 0
99 1
98 2
97 3
...
```

后面的全部用 `0` 来填就可以。

这样就保证每个人都能用至少一个学科去打败其他的人。如果 A 学科比不过你那么 B 学科就能打败你。

注意：如果 $m=1$ 代表只有一个学科时，那么就只能 $n=1$ 时才有解。

因为只有一个学科时 **只能有一个最强者**。

```cpp
#include<cstdio>
inline int in();
inline void wr(int);
int main(int argc,char**argv){
#ifndef ONLINE_JUDGE
	freopen("7873.in","r",stdin);
	freopen("7873.out","w",stdout);
#endif
	register int t=in();
	register int T=in();
	while(T--){
		register int n=in(),m=in();
		/*
		100 0
		99 1
		98 2
		97 3
		...
		*/
		if(m==1){
			if(n==1)puts("YES\n0");
			else puts("NO");
		}
		else{
			puts("YES");
			for(register int i=1;i<=n;++i,putchar('\n'))
				for(register int j=1;j<=m;++j,putchar(' '))
					if(j>2)putchar('0');
					else if(j==1)wr(i-1);
					else wr(n-i+1);
		}
	}
}
inline int in(){
	register char c=getchar();
	register int x=0,f=1;
	for(;c<'0'||c>'9';c=getchar())
		if(c=='-')f=-1;
	for(;c>='0'&&c<='9';c=getchar())
		x=(x<<1)+(x<<3)+(c&15);
	return x*f;
}
inline void wr(int x){
	if(x<0)putchar('-'),x=-x;
	if(x/10)wr(x/10);
	putchar(x%10+'0');
}
```

---

## 作者：Nygglatho (赞：0)

首先，先看一下怎样才能无解。

显然，是当 $n > 1$ 且 $m = 1$ 的时候，因为假如有解，那么解为一个数组，而这个数组要求要一个每一个数都大于其他所有数，很明显不存在。

接下来从 $n = m$ 的情况分析，可以从 $0$ 开始双重循环，第 $i$ 个人可以在第 $i$ 科的 $100$ 分，其他为 $i$ 分。

例如这张图（$n, m = 8$ 的时候）：

![](https://s3.bmp.ovh/imgs/2021/09/1a24023b7dccd284.jpg)

然后延伸到 $n \le m$ ，第二层循环（即 $j$）循环到比 $n$ 大的时候时，无论填多少都没有影响了，否则跟 $n = m$ 时一样。这里我在第二层循环（即 $j$）循环到比 $n$ 大的时候填 $i$。

例如这张图（$n = 5, m = 10$ 的时候）：

![](https://s3.bmp.ovh/imgs/2021/09/84bd4071c4cd07c5.jpg)

这一部分代码：
```cpp
void work1() {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (j >= n) {
				cout << i << ' ';
			} else {
				if (i == j) cout << 100 << ' ';
				else cout << i << ' ';
			}
		}
		cout << endl;
	}
}
```

接下来是 $n > m$ 的情况了。

前面第一层循环 $i \le n$  时，跟 $n = m$ 时情况一样，但后面要判断，可以前面 $m - 1$ 科**全部**为 $i$，最后一科从 $99$ 分开始依次递减。这样子，前面都不会失落，因为有**至少一科**比其他人高。

而 $i > n$ 时的人前面 $m - 1$ 科比**前面**所有人高（除了 $100$ 分的人），最后一科比**后面**所有人以及当 $i < (n - 1)$ 时所有的人高，所以都不会失落，所以方案是对的。

例如这张图（$n = 10, m = 5$ 的时候）：

![](https://s3.bmp.ovh/imgs/2021/09/55021df3e8cfbf72.jpg)

这一部分代码：
```cpp
void work2() {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (i >= m) {
				if (j == m - 1) cout << (100 + m - i - 1) << ' ';
				else cout << i << ' ';
			} else {
				if (i == j) cout << 100 << ' ';
				else cout << i << ' ';
			}
		}
		cout << endl;
	}
}
```

---

## 作者：cancan123456 (赞：0)

刚刚的题解忘记写无解情况了，补一下。

这个题是个简单的构造题，首先我们判断无解情况：

如果 $m = 1$ 并且 $n > 1$，那么肯定无解。

如果 $m = n = 1$，那么我们输出 ```100``` 就可以了。

否则，因为只有一个科目，所以我们可以给这些成绩排序，然后每一个非榜首的人都会觉得失落。

然后构造如下分数表：

$\begin{matrix} 0 & 100 & 100 & \cdots & 100 \\ 1 & 99 & 100 & \cdots & 100 \\ 2 & 98 & 100 & \cdots & 100 \\ \vdots & \vdots & \vdots & \ddots & \vdots \\ n - 1 & 100 - n + 1 & 100 & \cdots & 100\end{matrix}$

即：第 $i$ 个人第 $j$ 科目的成绩为：

${score}_{i,j}=\begin{cases}i-1&j=1\\100-i+1&j=2\\100&otherwise\end{cases}$

然后我们可以证明：对于任意两个人 $i,j\left(i<j\right)$，每一个人都不会觉得失落。

然后我们考察 $i$ 和 $j$ 的分数：

$\begin{matrix} i-1 & 100-i+1 & 100 & \cdots & 100 \\ j-1 & 100-j+1 & 100 & \cdots & 100\end{matrix}$

因为 $i < j$，所以 $i-1<j-1,100-i+1>100-j+1$，即每个人都有一门科目比别人高，每一个人都不会觉得失落。

代码：

```cpp
#include <cstdio>
using namespace std;
void inline solve() {
	int n, m;
	scanf("%d %d", &n, &m);
	if (m < 2) {
		if (n == 1) {
			printf("YES\n");
			printf("100\n");
		} else {
			printf("NO\n");
		}
	} else {
		printf("YES\n");
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (j == 0) {
					printf("%d ", 100 - i);
				} else if (j == 1) {
					printf("%d ", i);
				} else {
					printf("100 ");
				}
			}
			putchar(10);
		}
	}
}
int main() {
	int t;
	scanf("%*d %d", &t);
	for (int i = 0; i < t; i++) {
		solve();
	}
	return 0;
}
```

---

## 作者：_thiscall (赞：0)

本题的构造方式很多，这里说一种易于理解的方式。

科目 1：每个人都被下一个人吊打。

科目 2：每个人都吊打下一个人。

科目 3：每个人都被下一个人吊打。

科目 4：每个人都吊打下一个人。

以此类推。

**于是，每个人既可以在某一科目上吊打别人，又可以被别人在另一科目上吊打。这正好符合题目的平衡。**

**简而言之，奇数科目每个人都被下一个人吊打，偶数科目每个人都吊打下一个人。最后判断一下是否符合题意即可。**

代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define reg register
template <typename TX>
inline void read(TX &x)
{
	x=0;
	reg int ch=0;
	while (ch<'0' || ch>'9') ch=getchar();
	while (ch>='0' && ch<='9') {
		x=x*10+(ch^48);
		ch=getchar();
	}
}
#define rep(_vr, _st, _ed) for(reg int _vr=_st; (_vr)<=(_ed); _vr++)
int f[110][110]={0};
int n, m;
int construct() {
	memset(f, 0, sizeof(f)); //初始化
	rep (i, 1, n) rep (j, 1, m) {
		if (j&1) { //奇数科目
			f[i][j]=i; //被吊打
		} else { //偶数科目
			f[i][j]=n-i+1; //吊打下一个人
		}
	}
	int flag;
	rep (i, 1, n) { //枚举小 i
		rep (j, 1, n) { //枚举小 j
			if (i==j) continue; //避免判断“我吊打我自己”
			flag=0;
			rep (k, 1, m) { //枚举每个科目
				if (f[i][k]>f[j][k]) { //小 i 有一科吊打小 j
					flag=1; break; //小 i 很开心，符合题意
				}
			}
			if (!flag) return 0; //小 i 被全方位吊打，不合题意，构造失败
		}
	}
	return 1; //构造成功
}
int main()
{
	int T; read(T); read(T); //抛弃第一个数
	while (T--) {
		read(n); read(m);
		if (construct()) { //构造成功
			printf("YES\n");
			rep (i, 1, n) { //输出方案
				rep (j, 1, m) printf("%d ", f[i][j]);
				putchar('\n');
			}
		} else printf("NO\n"); //构造失败
	}
	return 0;
}
```


---

## 作者：ricky0916 (赞：0)

考虑构造。

当 $ n=1 $ 时，直接随便输出分数即可。

当 $ n>1, m=1 $ 时，显然无解。

当 $ n>1,m>1 $ 时，考虑类似这样的这样构造前两个分数：

$ s_{1,1}=100,s_{1,2}=0 $

$ s_{2,1}=99,s_{2,2}=1 $

$ ...... $

$ s_{n,1}=101-n,s_{n,2}=n-1 $

这样可以保证对任意的 $ i\ne j $，满足 $ s_{i,1}>s_{j,1} $ 和 $ s_{i,2}>s_{j,2} $ 中的一个。

剩下分数随便输出即可。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
static char buf[1000],*pa=buf,*pd=buf;
static char buf2[1000000],*pp=buf2;
#define getchar() pa==pd&&(pd=(pa=buf)+fread(buf,1,1000,stdin),pa==pd)?EOF:*pa++
inline void pc(char ch){
	if(pp-buf2==1000000) fwrite(buf2,1,1000000,stdout),pp=buf2;
	*pp++=ch;
}
inline void pcc(){
	fwrite(buf2,1,pp-buf2,stdout);
	pp=buf2;
}
inline int read(){
	int x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9'){
		x=(x<<3)+(x<<1)+ch-'0';
		ch=getchar();
	}
	return x;
}
void write(int x){
	static int sta[20];
	int top=0;
	do{
		sta[top++]=x%10,x/=10;
	}while(x);
	while(top) pc(sta[--top]+48);
}
void we(int x){
	write(x);
	pc('\n');
}
int t,n,m;
int main(){
	srand(time(0));
	t=read();
	t=read();
	while(t--){
		n=read();
		m=read();
		if(m==1&&n==1){
			pc('Y');
			pc('E');
			pc('S');
			pc('\n');
			write(rand()%101);
			pc('\n');
		}
		else if(m==1){
			pc('N');
			pc('O');
			pc('\n');
		}
		else{
			pc('Y');
			pc('E');
			pc('S');
			pc('\n');
			for(int i=1;i<=n;i++){
				write(n+1-i);
				pc(' ');
				write(i);
				pc(' ');
				for(int j=3;j<=m;j++){
					write(rand()%101);
					pc(' ');
				}
				pc('\n');
			}
		}
	}
	pcc();
	return 0;
}
```


---

