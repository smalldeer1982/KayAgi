# 纵横字谜的答案 Crossword Answers

## 题目描述

有一个 $r$ 行 $c$ 列 $(1<r,c<10)$ 的网格，黑格为 `*` ，每个白格都填有一个字母。如果一个白格的左边相邻位置或者上边相邻位置没有白格（可能是黑格，也可能出了网格边界），则称这个白格是一个起始格。

你的任务是先找出网格中所有横向单词（`Across`）。这些单词必须从一个起始格（左边是黑格，或是第一列）开始，向右延伸到一个黑格的左边或者整个网格的最右列。然后找出所有竖向单词（`Down`），规则同上，这些单词必须从一个起始格（上边是黑格，或是第一行）开始，向下延伸到一个黑格的上边或者整个网格的最下行。

## 样例 #1

### 输入

```
2 2
AT
*O
6 7
AIM*DEN
*ME*ONE
UPON*TO
SO*ERIN
*SA*OR*
IES*DEA
0```

### 输出

```
puzzle #1:
Across
1.AT
3.O
Down
1.A
2.TO
puzzle #2:
Across
1.AIM
4.DEN
7.ME
8.ONE
9.UPON
11.TO
12.SO
13.ERIN
15.SA
17.OR
18.IES
19.DEA
Down
1.A
2.IMPOSE
3.MEO
4.DO
5.ENTIRE
6.NEON
9.US
10.NE
14.ROD
16.AS
18.I
20.A```

# 题解

## 作者：waltz26 (赞：14)

### 按照紫书上面此题所在的位置的学习进度，采用C语言的写法。由于UVA格式很严格，所以从格式先开始讲，需要代码直接拉到底~
------------
### 输入的特点以及解决方法：

- **直接输入行列，以输入最后一个行的值为0时结束**

运用紫书上面例题的输入做法，先输入行判断是否为0

```cpp
while (scanf("%d", &r) == 1 && r != 0) {}
```
------------
### 输出的特点以及解决方法：

- **每个字谜输出结尾要换两次行，但是最后一个不要（PE警告）**

- **序号是右对齐的！（同样PE警告）**

具体解决方法见**最终**题解

------------
### 正文

，Down的输出即用输出Across标记好的位置

**第一部分:读取字谜和Across输出**

- 输入字谜是读取一串即可（scanf），发现我们需要先输出横向(Across)，所以我们将读取和Across的输出合并

- 第八行对于黑格的判断需要提一提紫书上面的一个知识点：||（或）是短路运算符，只要i==0就不会看后面的条件p[i-1][j]访问非法内存

- 如何跳过被读的起始格又使得序号增加？这里运用了pj这个变量，pj会记录当前一行已读到的位置

- 变量解释：r为行，c为列，p为存储字谜的二维数组，po为记录起始格的位置和序号的二维数组（完整代码中po需初始化为0），t记录序号，pj记录当前读到的位置

```cpp
for (int i = 0; i < r; i++)                 
{
	scanf("%s", p[i]);
	int pj = 0;
	for (int j = 0; j < c; j++)
	{
		if (p[i][j] == '*') continue;
		if (i == 0 || p[i - 1][j] == '*' || j == 0 || p[i][j - 1] == '*')                		 {
			t++; po[i][j] = t;
			if (j >= pj)
			{
				int k;
				printf("%3d.", t);
				for (k = j; k < c && p[i][k] != '*'; k++) printf("%c",p[i][k]);
				pj = k+1;
				putchar('\n');
			}
		}
	}
}
```

**第二部分：Down的输出**

- 判断po[i][j]是否不为0，不为0则输出竖列，并在输出过程中将遍历的po[i][j]赋值为0,刚好完成了每一组字谜po初始化为0的任务

- 变量与第一部分的相同

```cpp
for (int i = 0; i < r; i++)
{
	for (int j = 0; j < c; j++)
	{
		if (po[i][j])
		{
			printf("%3d.", po[i][j]);
			for (int k = i; k < r && p[k][j] != '*'; k++)
			{
				po[k][j] = 0; printf("%c", p[k][j]);
			}
			putchar('\n');
		}
	}
}
```

## 其实看到这里你已经完全可以自己补全剩下的代码了

**但还是贴出完整代码吧**

```cpp
#include<cstdio>
using namespace std;
int main()
{
	int po[10][10] = { 0 };               
	char p[10][10];                     
	int r, c,kase=0;                      
	while (scanf("%d", &r) == 1 && r != 0)                 
	{
		scanf("%d", &c);
		if (kase > 0) putchar('\n');                       
		printf("puzzle #%d:\nAcross\n", ++kase);
		int t = 0;
		for (int i = 0; i < r; i++)                             
		{
			scanf("%s", p[i]);
			int pj = 0;
			for (int j = 0; j < c; j++)
			{
				if (p[i][j] == '*') continue;
				if (i == 0 || p[i - 1][j] == '*' || j == 0 || p[i][j - 1] == '*')                
				{
					t++; po[i][j] = t;
					if (j >= pj)
					{
						int k;
						printf("%3d.", t);
						for (k = j; k < c && p[i][k] != '*'; k++) printf("%c",p[i][k]);
						pj = k+1;
						putchar('\n');
					}
				}
			}
		}
		printf("Down\n");
		for (int i = 0; i < r; i++)
		{
			for (int j = 0; j < c; j++)
			{
				if (po[i][j])
				{
					printf("%3d.", po[i][j]);
					for (int k = i; k < r && p[k][j] != '*'; k++)
					{
						po[k][j] = 0; printf("%c", p[k][j]);
					}
					putchar('\n');
				}
			}
		}
	}
	return 0;
}
```

有可能你可以优化这个代码，毕竟本人才刚刚学紫书，这完全是**新手代码**

---

## 作者：SunSkydp (赞：5)

这题是关于字符串的大模拟。

### 题目的输出格式细节 
- 多组数据，每两个多组数据之间要加一个**空行**。
- 输出单词的编号要**占三格（右对齐）**，printf 格式符用 `%3d` 就行。

### 多组数据的读入
用 while 循环，注意先读 $n$，判断不为零（为零就结束）则读 $m$。
```cpp
while(scanf("%d", &n) && n != 0) {
   scanf("%d", &m);
   ...
}
```

### 标记起始格
$ids$ 表示起始格编号，这里 $id$ 和 $id2$ 数组分别用于横向和纵向的输出。
```cpp
int ids = 0;
for(int i = 1; i <= n; i++) {
	for(int j = 1; j <= m; j++) {
		if(a[i][j] != '*' && (j == 1 || a[i][j - 1] == '*' || i == 1 || a[i - 1][j] == '*')) 
        {
			id[i][j] = ++ids, id2[i][j] = ids;
		}
	}
}
```

### 单词的输出
横向和竖向输出大体类似，用三层循环，输出一个单词后，要把单词的每一个字母标记掉，以免下次使用已输出过的起始格。

**再次强调：格式！格式！格式！我格式错了可是交了三遍呢！**

### 代码
最后放完整代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, kase, id[15][15], id2[15][15];
char a[15][15];
int main() {
	while(scanf("%d", &n) && n != 0) {
		scanf("%d", &m);
		memset(id, 0, sizeof(id));
		memset(id2, 0, sizeof(id2));
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= m; j++) {
				cin >> a[i][j];
			}
		}
		int ids = 0;
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= m; j++) {
				if(a[i][j] != '*' && (j == 1 || a[i][j - 1] == '*' || i == 1 || a[i - 1][j] == '*')) {
					id[i][j] = ++ids, id2[i][j] = ids;
				}
			}
		}
		kase++;
		if(kase > 1) printf("\n");
		printf("puzzle #%d:\nAcross\n", kase);
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= m; j++) {
				if(id[i][j] != 0) {
					printf("%3d.", id[i][j]);
					for(int k = j; k <= m; k++) {
						if(a[i][k] == '*') break;
						cout << a[i][k];
						id[i][k] = 0;
					}
					printf("\n");
				}
			}
		}
		printf("Down\n");
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= m; j++) {
				if(id2[i][j] != 0) {
					printf("%3d.", id2[i][j]);
					for(int k = i; k <= n; k++) {
						if(a[k][j] == '*') break;
						cout << a[k][j];
						id2[k][j] = 0;
					}
					printf("\n");
				}
			}
		}
	}
	return 0;
} 
```

---

## 作者：andyli (赞：3)

这一题主要就是按照题意模拟，先找出“起始格”，把起始格的序列存到`vector数组`里面，然后再遍历`vector数组`，按照题意输出即可（每个点最多打印一次）。另外还要注意UVa题目的输出格式，非常坑。其他的注释应该讲明白了把。

Code：
```cpp
#include <iostream>
#include <cstring>
#include <iomanip>
#include <vector>
using namespace std;
const int maxn = 15;

char A[maxn][maxn]; // 输入存在这个数组里
bool vis[maxn][maxn]; // 这个点是否打印过
vector<pair<int, int>> v; // 存起始点的vector数组

int main()
{
    int n, m, kase = 0;
    while (cin >> n && n)
    {
        cin >> m;
        if (kase++)
            cout << endl;
        cout << "puzzle #" << kase << ":" << endl;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                cin >> A[i][j];
        memset(vis, 0, sizeof(vis));
        v.clear();
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if ((!i || !j || A[i - 1][j] == '*' || A[i][j - 1] == '*') && A[i][j] != '*') // 在边界或者左边相邻位置是黑格或者上边相邻位置是黑格。注意这个格子不能是黑格
                    v.emplace_back(i, j);
        cout << "Across" << endl;
        for (size_t i = 0; i < v.size(); i++)
            if (!vis[v[i].first][v[i].second])
            {
                cout << setw(3) << i + 1 << "."; // 宽度为3，setw的头文件是iomanip
                for (int j = v[i].second; j < m; j++)
                    if (A[v[i].first][j] == '*')
                        break;
                    else
                        cout.put(A[v[i].first][j]), vis[v[i].first][j] = true; // 输出字符并打标记
                cout << endl;
            }
        memset(vis, 0, sizeof(vis)); // 重置数组
        cout << "Down" << endl;
        for (size_t i = 0; i < v.size(); i++)
            if (!vis[v[i].first][v[i].second])
            {
                cout << setw(3) << i + 1 << ".";
                for (int j = v[i].first; j < n; j++)
                    if (A[j][v[i].second] == '*')
                        break;
                    else
                        cout.put(A[j][v[i].second]),
                            vis[j][v[i].second] = true;
                cout << endl;
            }
    }
}
```

---

## 作者：chenpengda (赞：2)

纯模拟即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int st[15][15];//st代表这个起始格的编号，0代表不是起始格。 
int main()
{
	int r,c,tail=0,num=0;//tail代表目前的字谜编号 
	char a[15][15];//储存字谜 
	while(cin>>r)
	{
		if(r==0)return 0;
		cin>>c;
		if(tail>0)cout<<"\n";//坑人的格式 
		num=0;
		for(int i=0;i<15;i++)
		{
			for(int j=0;j<15;j++)//初始化。 
			{
				a[i][j]='*';
				st[i][j]=0;
			}
		}
		cout<<"puzzle #"<<++tail<<":\n";//先输出 
		for(int i=1;i<=r;i++)
		{
			for(int j=1;j<=c;j++)
			{
				cin>>a[i][j];//输入，并且判断起始格 
				if((a[i-1][j]=='*'||a[i][j-1]=='*')&&a[i][j]!='*')st[i][j]=++num;
			}
		}
		/*cout<<"TRY:\n";
		for(int i=1;i<=r;i++)
		{
			for(int j=1;j<=c;j++)
			{
				cout<<st[i][j]<<" ";
			}
			cout<<"\n";
		}
		cout<<"\n\n";*/
		//Find ACROOS
		cout<<"Across\n";
		for(int i=1;i<=r;i++)
		{
			for(int j=1;j<=c;j++)
			{
				if(st[i][j]>0&&a[i][j-1]=='*')//判断横向：从一个可以走的起始格开始向右遍历。 
				{
					printf("%3d.",st[i][j]);//格式。 
					int now=j;
					while(a[i][now]!='*')
					{
						cout<<a[i][now];
						now++;
					}
					cout<<endl;
				}
			}
		}
		//Find DOWN
		cout<<"Down\n";
		for(int i=1;i<=r;i++)
		{
			for(int j=1;j<=c;j++)
			{
				if(st[i][j]>0&&a[i-1][j]=='*')//判断纵向：从一个可以走的起始格开始向下遍历。
				{
					printf("%3d.",st[i][j]);//格式。 
					int now=i;
					while(a[now][j]!='*')
					{
						cout<<a[now][j];
						now++;
					}
					cout<<endl;
				}
			}
		}
	}
	return 0;//结束。 
}
```

主要就是这个起始格的问题，只需要用一个数组就可以解决。

其他主要就是格式问题了。

---

## 作者：Snowlanuck (赞：2)

题目本身不难 判断起始点的条件都说了 直接根据意思写代码即可 "左边是黑格，或是第一列" 意思就是说第一行第一列 只要不是黑格就是起始点 除了第一行第一列之外的格子 判断左边或者上边是否有黑格即可 然后再根据起始点找出单词

UVA的题都很注重格式... 这个格式我能吐槽很久 反正格式要求严格,多一行少一行空行都不行

接下来直接上代码,我觉得我的代码还是很通俗易懂的8

```cpp
#include<bits/stdc++.h>
using namespace std;
//UVA232 纵横字谜的答案 Crossword Answers
int main()
{
	//freopen("output", "w", stdout);

	char Nums[10][10];
	int Count = 0;
	while (++Count)
	{
		vector<vector<int>> Starts; //起始格
		memset(Nums, 0, sizeof(Nums));
		int R, C;
		cin >> R;
		if (R == 0) return 0;
		if (Count > 1) cout << endl;
		cin >> C;
		for (int i = 0; i < R; i++)
			for (int j = 0; j < C; j++)
				cin >> Nums[i][j];
		//统计起始格
		for (int i = 0; i < R; i++)
		{
			for (int j = 0; j < C; j++)
			{
				if ((i == 0 || j == 0) && Nums[i][j] != '*')
				{//第一行&第一列的起始格
					Starts.push_back({ i,j });
				}
				if (i > 0 && j > 0)
				{
					if ((Nums[i - 1][j] == '*' || Nums[i][j - 1] == '*')
						&& (Nums[i][j] != '*'))
					{
						Starts.push_back({ i,j });
					}
				}
			}
		}
		printf("puzzle #%d:\n", Count);
		//统计横向单词
		printf("Across\n");
		for (size_t i = 0; i < Starts.size(); i++)
		{
			int x = Starts[i][0], y = Starts[i][1];
			if ((y == 0 || Nums[x][y - 1] == '*') && Nums[x][y] != '*')
			{
				printf("%3d.", i + 1);
				while (Nums[x][y] != '*' && y < C)
				{
					putchar(Nums[x][y++]);
				}
				printf("\n");
			}
		}

		//统计竖向单词
		printf("Down\n");
		for (size_t i = 0; i < Starts.size(); i++)
		{
			int x = Starts[i][0], y = Starts[i][1];
			if ((x == 0 || Nums[x - 1][y] == '*') && Nums[x][y] != '*')
			{
				printf("%3d.", i + 1);
				while (Nums[x][y] != '*' && x < R)
				{
					putchar(Nums[x++][y]);
				}
				/*if (i != Starts.size() - 1) */
				printf("\n");
			}
		}
	}

	return 0;
}
```


---

## 作者：fjy666 (赞：1)

### 0x01 思路
这道题是一道模拟题。  
根据题意，首先我们记录每个起始格的标号。  
在我的代码中，这个编号是用 `St` 数组来记录的。  
然后再分别枚举 $\texttt{Across}$ 和 $\texttt{Down}$ 即可。  

由于题目要求按照起始格从上到下，从左到右的顺序，  
所以 $\texttt{Across}$ 可以直接枚举。  
其中要注意：`***ADE` 这种情况，即字母一直到行尾。  
这种情况我们就要加特判。  
时间复杂度 $\Theta(n \times m)$

而 $\texttt{Down}$ 就不同了。  
我们只能通过枚举起始格，再得出整个单词的方式。  
时间复杂度 $\Theta(n^2 \times m)$

还要注意格式问题。  
本题中，是输出一个 $\texttt{Puzzle}$ **换两行！**   
即
```plain
puzzle #1:
Across
Down(\n)
(\n)
puzzle #2:
Across
Down
```  
然后每个单词的序号要 `printf("%3d.",St[i][j]);`输出。  

总时间复杂度：$\Theta (T \times (n \times m + n^2 \times  m))$

------------
### 0x02 代码
```cpp
#include <cstdio>
#include <cstring>
#define fo(i_,j_,k_) for(int i_=j_;i_<=k_;++i_)
#define fr(i_,j_,k_) for(int i_=j_;i_>=k_;--i_)
#define It(type_) type_::iterator
#define rg register
#define rtn return
#define il inline

typedef long long ll;
const int kMaxn = 11;
char puzzle[kMaxn][kMaxn];
int St[kMaxn][kMaxn];
int n,m;

int main()
{
	int PuzzleCount = 0;
	while(~scanf("%d",&n))
	{
		if(n == 0)break;
		scanf("%d",&m);
		if(PuzzleCount != 0)puts("");
		printf("puzzle #%d:\n",++PuzzleCount);
		memset(St,0,sizeof(St));
		fo(i,1,n)
			scanf("%s",puzzle[i]);
		int CurrCnt = 0;//目前的标号
		fo(i,1,n)
			fo(j,0,m-1) 
				if(puzzle[i][j]!='*')//起始格不能是 *
					if(i == 1 || j == 0 || puzzle [i-1][j] == '*' || puzzle[i][j-1] == '*')
						St[i][j] = ++CurrCnt; 
//		printf("%d\n",St[1][0]);
//		fo(i,1,n)
//			fo(j,0,m-1)
//				printf("St[%d][%d]=%d\n",i,j,St[i][j]);
		puts("Across");
		fo(i,1,n)
		{
			char Word[11]={};
			int StInd = 0,Len = 0;
			while(puzzle[i][StInd]&&puzzle[i][StInd] == '*')
				++StInd;
			fo(j,StInd,m-1)
			{
				if(puzzle[i][j] == '*')
				{
					if(Len)
					{
						Word[Len] = '\0';
						puts(Word);
						Len = 0; 
					}
				}
				else
				{
					if(Len == 0)printf("%3d.",St[i][j]);
					Word[Len++] = puzzle[i][j];
				} 
			}
			if(Len != 0)
			{
				Word[Len] = '\0';
				puts(Word);//Len != 0说明还有剩下的 
			} 
		}
		puts("Down");
		fo(i,1,n)
			fo(j,0,m-1)
			{
				if(St[i][j] == 0) continue;
				if(i != 1 && puzzle[i-1][j] != '*')continue;
				printf("%3d.",St[i][j]);
				int Ind = i;
				while(Ind <= n && puzzle[Ind][j] != '*')
					printf("%c",puzzle[Ind++][j]);
				puts("");
			} 
	} 
	rtn 0;
}
```

---

## 作者：AlienZhan (赞：1)

## **Tip：要理解题意，请看原PDF，要搞清输出格式，还是得看原PDF！**

先说我的解题思路
------------
**1. 开辟两个数组，一个输入谜面，一个用来记录起始格位置**

因为谜面最大为10X10不是很大,我们可以直接把字符数组设置为12X12大小，这样做的好处是可以避免输出结果时下标越界访问

```
char a[12][12];

int b[11][11] = { 0 };
```

我们把字符数组全填上星号，由于字符数组是12X12的，相当于用星号为谜面设置了四周的边界，这样可以在输出解时直接通过当前字符是不是星号判断循环是否到达了边界处，而不用讨论是否会越界


```
for (int i = 0; i < 12; ++i)
            for (int j = 0; j < 12; ++j)
                a[i][j] = '*';
```



**2. 根据题目意思模拟**

如果当前白格左与上方无白格（即为星号），就确定为起始格，把起始格序数存到b中，待用


```
int cnt = 0;
        for (int i = 1; i <= r; ++i)
            for (int j = 1; j <= c; ++j)
            {
                std::cin >> a[i][j];
                if (a[i][j] != '*' && (a[i][j - 1] == '*' || a[i - 1][j] == '*'))
                {
                    ++cnt; b[i][j] = cnt;
                }
            }
```


**3. 输出结果**

- **对Across**

横行输出时，当前白格左无星号就输出b中对应的起始格序号（序号右对齐且宽度为3！由于是横向遍历，起始格序号是有序的），当前白格右边有星号就换行

```
printf("puzzle #%d:\nAcross\n", ++n);
        for (int i = 1; i <= r; ++i)
            for (int j = 1; j <= c; ++j)
            {
                if (a[i][j] != '*')
                {   
                    if (a[i][j - 1] == '*')
                        printf("%3d.", b[i][j]);
                    printf("%c", a[i][j]);
                    if (a[i][j + 1] == '*')
                        printf("\n");
                }
            }
```

- **对Down**

由于直接和套用和Across一样的方式来竖向遍历会导致顺序混乱，所以这次通过b来判断：在b中除起始格序号外的位置都为零，所以我们找到不为零的位置，然后输出该序号及a中对应的字符

对于每次不中断输出经历的所有起始格，我们把b中对应的位置为0，以避免重复输出，同时，这样做也清空了b，之后就不用再单独清空了

```
printf("Down\n");
        for (int i = 1; i <= r; ++i)
            for (int j = 1; j <= c; ++j)
            {
                if (b[i][j] != 0)
                {
                    printf("%3d.", b[i][j]);
                    int i1 = i;
                    while (a[i1][j] != '*')
                    {
                        printf("%c", a[i1][j]);
                        b[i1][j] = 0;
                        ++i1;
                    }
                    printf("\n");
                }
            }
```

关于输出格式
------------

- **相邻的两个解之间要用空行隔开，但最后一个解后面只有换行无空行**


- **输出起始格序号时，序号是右对齐的，且注意宽度为3！**


- **如果全是黑格此时Across和Down也要有，且此时二者之间不存在空行**


- **洛谷WA了可能实际是PE，记得检查Uva的邮件确认**

如果检查邮件发现是PE，请按照以上几点认真检查并进行修改

关于此题的格式问题已经有题解进行了分析，但是作为影响此题AC的重要因素，我觉得还是有必要强调说明一下如何避免PE，毕竟本人数次修改代码，但一直PE，心态爆炸有没有QAQ
![](https://s3.ax1x.com/2020/11/14/D9bnmD.png)


下面是完整代码
------------
```
#include <iostream>
#include <cstdio>
int main() {
    int n = 0, b[11][11] = { 0 };	//b在每次循环后都被清空，所以只需要初始化一次
    while (1)
    {
        int r, c;
        std::cin >> r;
        if (r == 0) return 0;
        std::cin >> c;
        char a[12][12];
        for (int i = 0; i < 12; ++i)
            for (int j = 0; j < 12; ++j)
                a[i][j] = '*';
        int cnt = 0;
        for (int i = 1; i <= r; ++i)
            for (int j = 1; j <= c; ++j)
            {
                std::cin >> a[i][j];
                if (a[i][j] != '*' && (a[i][j - 1] == '*' || a[i - 1][j] == '*'))
                {
                    ++cnt; b[i][j] = cnt;
                }
            }
        if (n)printf("\n");		//用于判断是否在解前面输出空行，第一个解前面不输出
        printf("puzzle #%d:\nAcross\n", ++n);
        for (int i = 1; i <= r; ++i)
            for (int j = 1; j <= c; ++j)
            {
                if (a[i][j] != '*')
                {   
                    if (a[i][j - 1] == '*')
                        printf("%3d.", b[i][j]);
                    printf("%c", a[i][j]);
                    if (a[i][j + 1] == '*')
                        printf("\n");
                }
            }
        printf("Down\n");
        for (int i = 1; i <= r; ++i)
            for (int j = 1; j <= c; ++j)
            {
                if (b[i][j] != 0)
                {
                    printf("%3d.", b[i][j]);
                    int i1 = i;
                    while (a[i1][j] != '*')
                    {
                        printf("%c", a[i1][j]);
                        b[i1][j] = 0;
                        ++i1;
                    }
                    printf("\n");
                }
            }
    }
    return 0;
}
```

---

## 作者：__天__ (赞：1)

这个题主要是纵向单词不太容易找出，还有就是序号的标记，刚开始没有注意这个，还以为序号就是1然后递增。
序号的标记方法我用的是把所有字符遍历一遍，从0，0按顺序一直到到r，c，第一列或者第一行的只要不是星号就会有序号，其他的字符要是上一个或者前一个是星号的话，也会有序号，当然，本身不能是星号，再把序号存放入一个二维数组，输出时再调用，详细方法看代码。**注意，如果全部是星号ACROSS和DOWN也必须输出，输出序号前的空格也要注意，都是坑，一位序号的有两个空格，两位的有一个序号**
（看了那么多的题解Java的少之又少，让我来开个头）
```java
import java.util.*;
public class lalala {
    public static void main(String args[]) {
        String st="";
        Scanner reader = new Scanner(System.in);
        int g=0,num=0,sum=0;//标记变量
        while(reader.hasNextInt()){
            int r=reader.nextInt();
            if(r==0){break;}//读取到0，终止程序
            int c=reader.nextInt();
            reader.nextLine();//吞掉c后的换行
            int e=0,f=0,x=0,y=0,m=0;//标记变量
            g++;//标记标题的次数
            char[][] d=new char[r][c];//存放输入的表格
            int [][] p=new int[r][c];//存放序号
            String str="";
            for(int i=0;i<r;i++){
                str=reader.nextLine();
                for(int j=0;j<c;j++){
                    d[i][j]=str.charAt(j);
                }
            }//读入表格
            if(g>1){System.out.println();}//除了第一个标题，在每两个连续的标题之间输出换行
            System.out.println("puzzle #"+g+":");
            for(int i=0;i<r;i++){
                for(int j=0;j<c;j++){
                    if(i==0||j==0){
                        if(d[i][j]!='*'){m++;p[i][j]=m;}
                        }
                    else if(d[i-1][j]=='*'||d[i][j-1]=='*')
                    {
                        if(d[i][j]!='*') m++;p[i][j]=m;
                    }
                }
            }//序号标记
            String s="";//答案序列
            for(int i=0;i<r;i++){
                for(int j=0;j<c;j++){
                    if(d[i][j]!='*'){
                        num++;
                        if(num==1){sum=p[i][j];}//把要输出的序列号提出
                        y=1;//表示进入循环，不存在全是*
                        s+=d[i][j];//把单词依次存放进字符串
                    }
                    if(d[i][j]=='*'||j==c-1){//如果读取到了*或者读到了数组边界
                        if(s.equals(st)){continue;}//如果直接遇到*，会读入空串，此时跳出循环，不进行输出
                        e++;
                        if(e==1){System.out.println("Across");}//确保只会在第一次输出横行单词前输出标题across
                        System.out.printf("%3d.%s\n",sum,s);
                        s="";//释放答案序列
                        num=0;//清空标记
                    }
                }
            }
            if(y==0){
                System.out.println("Across");//如果一次循环都没有进入，意味着此次全是*，继续输出一个across标题
            }
            for(int i=0;i<r;i++){
                for(int j=0;j<c;j++){
                    if(d[i][j]!='*'){
                        x=1;
                      if(i==0){//如果不是*并且在第一行，必定会输出一个纵向单词
                          int k=0;
                          for(;;){
                              s+=d[i+k][j];
                              if(k==0){sum=p[i][j];}//把第一个单词的序号提出
                              k++;
                              if(i+k>=r||d[i+k][j]=='*'){break;}//一直读取到*或者数组边界
                          }
                          }
                          else if(d[i-1][j]=='*'){//如果该单词的上一个为*，该单词币可以输出一个纵向单词
                              int k=0;
                              for(;;){
                                  s+=d[i+k][j];
                                  if(k==0){sum=p[i][j];}//同上标记序号
                                  k++;
                                  if(i+k>=r||d[i+k][j]=='*'){break;}
                              }
                              }
                          }
                          if(s.equals(st)){continue;}
                            f++;
                            if(f==1){System.out.println("Down");}//与横向输出相同
                            System.out.printf("%3d.%s\n",sum,s);
                            s="";
                      }
                    }
            if(x==0){System.out.println("Down");}
                }
            }
    }
```

---

## 作者：CarryQwQ (赞：1)

## 题意概述
给定一个 $R \times C$ 的二维字符矩阵，输出所有的横向单词和竖向单词。

翻译有些难理解，先用题目的样例做一个说明。

|  A | I | M | * | D | E | N |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
|  * | M | E | * | O | N | E |
|  U | P | O | N | * | T | O |
|  S | O | * | E | R | I | N |
|  * | S | A | * | O | R | * |
|  I | E | S | * | D | E | A |

这是一个 $6 \times 7$ 的字符矩阵。

先给有字母的部分标上序号。标序号要遵守以下规则：

- 第一行或是第一列的字母都有序号。
- 如果不是上面的情况，如若满足左边是 ```'*'``` 或是上边是 ```'*'``` ，则也有序号。

得到这样一张序号表（没有序号的字母格为空）：

|  1 | 2 | 3 | * | 4 | 5 | 6 |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
|  * | 7 |  | * | 8|  |  |
|  9 |   |  | 10| * | 11 |  |
|  12 |  | * | 13 | 14 |  |  |
|  * | 15 | 16 | * | 17 | R | * |
|  18 |  |  | * | 19 |  | 20 |

这就是题干中这张图的意思（用黑格代替上表的 ```'*'```）：

![](https://cdn.luogu.com.cn/upload/image_hosting/vgigu4xc.png)

每个有序号的格子称为起始格，由起始格向右为横列，由起始格向下为纵列。由起始格开头一直延伸至 ```'*'``` 或边缘处，称为横向单词（或字母）称为横向单词 (Across) 或竖向单词 (Down)。

输出所有的横向单词和竖向单词。

## 题目坑点

UVA 的格式。

你以为的输出数据长这个样子：

```
puzzle #1:
Across
1.AT
3.O
Down
1.A
2.TO
puzzle #2:
Across
1.AIM
4.DEN
7.ME
8.ONE
9.UPON
11.TO
12.SO
13.ERIN
15.SA
17.OR
18.IES
19.DEA
Down
1.A
2.IMPOSE
3.MEO
4.DO
5.ENTIRE
6.NEON
9.US
10.NE
14.ROD
16.AS
18.I
20.A
```

它其实长这个样子：

```
puzzle #1:
Across
  1.AT
  3.O
Down
  1.A
  2.TO
puzzle #2:
Across
  1.AIM
  4.DEN
  7.ME
  8.ONE
  9.UPON
 11.TO
 12.SO
 13.ERIN
 15.SA
 17.OR
 18.IES
 19.DEA
Down
  1.A
  2.IMPOSE
  3.MEO
  4.DO
  5.ENTIRE
  6.NEON
  9.US
 10.NE
 14.ROD
 16.AS
 18.I
 20.A
```

它的编号是右对齐的，而且场宽为 3。

## 题目分析

用一个二维数组存储起始点序号。

分两次循环完成。

第一次循环，输出所有的横向单词。

每次找到一个起始点，向右延伸，输出字符，直到星号或是边缘。

第二次循环，输出所有的纵向单词。

每次找到一个起始点，向下延伸，输出字符，直到星号或是边缘。

## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int r, c, puzzle_cnt, ra[15][15], ra_cnt;
char s[15][15], s1[15][15];
int main() {
	while(cin >> r) {
		ra_cnt = 1;
		if (r == 0) break;
		else cin >> c;
		puzzle_cnt++;
		if (puzzle_cnt > 1) printf("\n");
		for (int i = 1; i <= r; i++)
			for (int j = 1; j <= c; j++) {
				cin >> s[i][j];
				s1[i][j] = s[i][j];
			}
		for (int i = 1; i <= r; i++)
			for (int j = 1; j <= c; j++) {
				if (s[i][j] != '*' && ((i == 1) || (j == 1) || (s[i - 1][j] == '*') || (s[i][j - 1] == '*'))) {
					ra[i][j] = ra_cnt;
					ra_cnt++;
				}
			}		
		printf("puzzle #%d:\n", puzzle_cnt);
		cout << "Across\n";
		for (int i = 1; i <= r; i++) {
			for (int j = 1; j <= c; j++) {
				if ((j == 1 || s[i][j - 1] == '*' ) && (s[i][j] != '*')) {
					printf("%3d.", ra[i][j]);
					for (int k = j; k <= c; k++) {
						if (s[i][k] != '*') {
							cout << s[i][k];
							s[i][k] = '.';
						} else break;
					}
					cout << endl;
				}
			}
		}
		cout << "Down\n";
		for (int i = 1; i <= r; i++) {
			for (int j = 1; j <= c; j++) {
				if ((i == 1 || s1[i - 1][j] == '*' ) && (s1[i][j] != '*')) {
					printf("%3d.", ra[i][j]);
					for (int k = i; k <= r; k++) {
						if (s1[k][j] != '*') {
							cout << s1[k][j];
							s1[k][j] = '.';
						} else break;
					}
					cout << endl;
				}
			}
		}
	}
}
```




---

## 作者：四宫辉夜 (赞：0)

# 一个比较与众不同的做法

### 首先说一句，这道题目的格式调整非常麻烦，我卡在这上面卡了很久...

如果需要校对格式可以使用 uva judge 的 debugger

链接：https://www.udebug.com/UVa/232

最近OI学习上遇到瓶颈，于是重新掏出紫书《算法竞赛入门经典》打算将所有习题做一遍...刚好做到这一题

看到这道题目还可以提交题解，就来提供一种我个人的做法

我的做法和前面很多大佬不太一样，我简单阐述一下我的思路。

细心的读者可能已经发现，相较于其他题解的二维数组储存初始格，我使用了三维数组。数组的第一维表示：该初始格是针对横向的单词或是纵向的单词。1代表纵向，0代表横向。判断部分的逻辑如下：

如果格子在第一行，将其记为纵向格子。若其同时满足在第一列或左侧为\*，则将其横向也记为该数字。

如果格子不在第一行，但是在第一列，则将其记为横向格子。若其同时满足上侧为\*，则将其同时记为纵向格子。

如果格子不在第一行也不在第一列，但是上侧格子为\*，则将其记为纵向格子。若同时满足左侧为\*，将其同时记为横向格子。

如果格子只有左侧为\*，将其记为横向格子。

代码如下:

```cpp
#include<cstdio>
#include<cstring>

int main()
{
    //freopen("UVA232.out","w",stdout);
    int n=1;
    while(1)
    {
        int r,c;
        scanf("%d",&r);
        if(!r)return 0;
        scanf("%d",&c);
        if(n-1)puts("");
        printf("puzzle #%d:\n",n++);
        char s[11][11];
        int a[2][11][11];
        memset(a,0,sizeof(a));
        for(register int i=0;i<r;i++)
            scanf("%s",s[i]);
        int num=1;
        for(register int i=0;i<r;i++)
            for(register int j=0;j<c;j++)
                if(s[i][j]!='*')
                    if(!i){a[1][i][j]=num++;if((!j)||s[i][j-1]=='*')a[0][i][j]=a[1][i][j];}
                    else if(!j){a[0][i][j]=num++;if(s[i-1][j]=='*')a[1][i][j]=a[0][i][j];}
                    else if(s[i-1][j]=='*'){a[1][i][j]=num++;if(s[i][j-1]=='*')a[0][i][j]=a[1][i][j];}
                    else if(s[i][j-1]=='*')a[0][i][j]=num++;
        puts("Across");
        //for(register int i=0;i<r;i++)
        //{
        //    for(register int j=0;j<c;j++)
        //        printf("%d",a[i][j]);
        //    puts("");
        //}
        for(register int i=0;i<r;i++)
            for(register int j=0;j<c;)
                if(s[i][j]=='*'||(!a[0][i][j])){j++;continue;}
                else if(a[0][i][j])
                {
                    printf("%3d.",a[0][i][j]);
                    for(register int k=j;k<c;k++)
                        if(s[i][k]=='*'){j=k;break;}
                        else printf("%c",s[i][k]),j=k+1;
                    printf("\n");
                }
        puts("Down");
        for(register int j=0;j<r;j++)
            for(register int i=0;i<c;i++)
                if(s[j][i]=='*'||(!a[1][j][i])){continue;}
                else if(a[1][j][i])
                {
                    printf("%3d.",a[1][j][i]);
                    for(register int k=j;k<r;k++)
                        if(s[k][i]=='*'){break;}
                        else printf("%c",s[k][i]);
                    printf("\n");
                }
    }
}
```

---

## 作者：2020Juruo (赞：0)

调试了无数次，只因为凭感觉瞎蒙，而没有按题意操作……（~~悄悄滚去面壁~~）
# 思路一：
先全部接收再判断。弊端：用循环输出之后的标记完全被改动，不得不用两次标记。
```
#include<math.h>
#include<stdio.h>
#include<string.h>
#define maxn 15
char str[maxn][maxn]; 
int mark[maxn][maxn]={0};
int main()
{
	int r,c,kase=0;
	while(1)
	{
		scanf("%d",&r);
		if(r==0)break;
		scanf("%d",&c);
		getchar();//吸收回车 ，一不小心就忘 
		for(int i=1;i<=r;i++)//这里重复输入，我是一次性输入最后输出，但有个弊端：输出之后的定位不好处理。
		{						//因此我们要善于边读入边输出QAQ 
			for(int j=1;j<=c;j++)
				str[i][j]=getchar();
			getchar();
		}
		int count=0;//开始标记 
		for(int i=1;i<=r;i++)
			for(int j=1;j<=c;j++)
				if((j-1<1||str[i][j-1]=='*'||i-1<1||str[i-1][j]=='*')&&str[i][j]!='*')
					mark[i][j]=++count;
		printf("puzzle #%d:\nAcross",++kase);
		int k=0,f=0;
		for(int i=1;i<=r;i++)//检索时：从左往右，从上到下 
			for(int j=1;j<=c;j++)
			{
				if(mark[i][j])//若有标记 
				{
					printf("\n%d.",mark[i][j]);  
					for(int p=j;p<=c;p++)//输出时：同上 
						if(str[i][p]!='*')
						{
							printf("%c",str[i][p]);mark[i][p]=0;//标记归零便于定位 
						}
						else break;
				}
			}
		count=0;
		for(int i=1;i<=r;i++)//重复标记它来了！ 
			for(int j=1;j<=c;j++)
				if((j-1<1||str[i][j-1]=='*'||i-1<1||str[i-1][j]=='*')&&str[i][j]!='*')
					mark[i][j]=++count;
		printf("\nDown");
		for(int i=1;i<=r;i++)//检索时：同Across 
			for(int j=1;j<=c;j++)
			{
				if(mark[i][j])
				{
					printf("\n%d.",mark[i][j]);//输出时：从上到下 
					for(int p=i;p<=r;p++)
						if(str[p][j]!='*')
						{
							printf("%c",str[p][j]);mark[p][i]=0;//标记归零便于定位 
						}
						else break;
				}
			}
	}
	return 0;
}
```

# 思路二：
Across的边接收边输出。原因在于:此时输出只和已经输出的有关系。Down直接利用标记进行输出。
```
#include<math.h>
#include<stdio.h>
#include<string.h>
#define maxn 15
char str[maxn][maxn]; 
int mark[maxn][maxn]={0};
int main()
{
	int r,c,kase=0;
	while(scanf("%d",&r)==1&&r)
	{
		int count=0,f=0;
		scanf("%d",&c);
		getchar();
		printf("puzzle #%d:\nAcross",++kase);
		for(int i=0;i<r;i++)
		{
			gets(str[i]);//gets(str[i])无法接收：之前没有吸收enter 
			for(int j=0;j<c;j++)//这里可以边输入边判断并输出的原因在于:输出只和已经输出的有关系
			{					//挨个字母判断输出即可，?.就当是附加品即可 
				if((j-1<0||i-1<0||str[i][j-1]=='*'||str[i-1][j]=='*')&&str[i][j]!='*')//别漏了大前提：不能为‘*’ 
					mark[i][j]=++count; 
				if(str[i][j]!='*')
				{
					if(!f)printf("\n%d.",count);//是否输出字母和他是否有标记是两码事！
					printf("%c",str[i][j]);f=1;//是否 输出?.是由上一个字符是否为'*'或另起一行决定的 
				}
				else f=0;
			}
			f=0;//一行结束时f=0！
		}
		printf("\nDown");
		for(int i=0;i<r;i++)
			for(int j=0;j<c;j++)
			{
				if(mark[i][j])
				{
					printf("\n%d.",mark[i][j]);
					for(int p=i;p<r&&str[p][j]!='*';p++)
					{
							printf("%c",str[p][j]);
							mark[p][j]=0;//以有标记的打头输出，归零避免重复输出 
					}
				}
			} 
	}
	return 0;
}
```

---

## 作者：HNFMS_Zbr (赞：0)

# 蒟蒻代码
###### 个人认为比较容易理解
思路:分为两部分,一部分是横向单词查找,另一部分是纵向单词查找,由于纵向序号排列不是按照题目要求顺序,于是使用了快排~~投机取巧地~~机智地排了一下.....

(((o(*ﾟ▽ﾟ*)o)))/
```
#include<cstdio>
#include<string>
#include<iostream>
#include<algorithm>
using namespace std;
typedef struct {
	char val;
	bool flag;
	int index;	
} gezi;				//网格 
typedef struct {
	string s;
	int *first;
} A_node;			//横向单词 
typedef struct {
	string s;
	int *first;
} B_node;			//纵向单词 
bool cmp(A_node a, A_node b){
	return *a.first < *b.first;
}
int main(){
	int ti = 0;
	while(1){
	gezi A[20][20];
	A_node Anode[15];
	B_node Bnode[15];
	int r, c, pi = 0, p1 = 0, p2 = 0;
	scanf("%d", &r);
	if(!r)
		return 0;
	scanf("%d", &c);
	getchar();
	for(int i=0;i<r;i++){
		for(int j=0;j<c;j++){
			A[i][j].val = getchar();
			A[i][j].flag = false;
		}
		getchar();
	}
	for(int i=0;i<r;i++)					//横向单词查找
		for(int j=0;j<c;j++){
			if(A[i][j].val != '*' && (j-1<0 || A[i][j-1].val == '*')){
				A[i][j].flag = true;
				Bnode[++p1].first = &A[i][j].index; 
				Bnode[p1].s += A[i][j].val;
				while(A[i][j+1].val != '*' && j+1 < c)
					Bnode[p1].s += A[i][++j].val;
			}
		}
	for(int j=0;j<c;j++)					//纵向单词查找
		for(int i=0;i<r;i++){
			if(A[i][j].val != '*' && (i-1<0 || A[i-1][j].val == '*')){
				A[i][j].flag = true;
				Anode[++p2].first = &A[i][j].index;
				Anode[p2].s += A[i][j].val;
				while(A[i+1][j].val != '*' && i+1 < r)
					Anode[p2].s += A[++i][j].val;
			}
		}
	for(int i=0;i<r;i++)
		for(int j=0;j<c;j++)
			if(A[i][j].flag)
				A[i][j].index = ++pi;
	sort(Anode+1, Anode+p2+1, cmp);
	printf("puzzle #%d:\n", ++ti);
	printf("Across\n");
	for(int i=1;i<=p1;i++)
		printf(" %2d.%s\n", *Bnode[i].first, Bnode[i].s.c_str());
	printf("Down\n");
	for(int i=1;i<=p2;i++)
		printf(" %2d.%s\n", *Anode[i].first, Anode[i].s.c_str());
	}
	return 0;
}
```
注:  建议不要"借鉴"(善意的提醒,因为某些原因(*^▽^)).

---

