# Anti-Sudoku

## 题目描述

You are given a correct solution of the sudoku puzzle. If you don't know what is the sudoku, you can read about it [here](http://tiny.cc/636xmz).

The picture showing the correct sudoku solution:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1335D/512a05a69fe045d0e0e90836d8dc5e29c119293a.png)

Blocks are bordered with bold black color.

Your task is to change at most $ 9 $ elements of this field (i.e. choose some $ 1 \le i, j \le 9 $ and change the number at the position $ (i, j) $ to any other number in range $ [1; 9] $ ) to make it anti-sudoku. The anti-sudoku is the $ 9 \times 9 $ field, in which:

- Any number in this field is in range $ [1; 9] $ ;
- each row contains at least two equal elements;
- each column contains at least two equal elements;
- each $ 3 \times 3 $ block (you can read what is the block in the link above) contains at least two equal elements.

It is guaranteed that the answer exists.

You have to answer $ t $ independent test cases.

## 样例 #1

### 输入

```
1
154873296
386592714
729641835
863725149
975314628
412968357
631457982
598236471
247189563```

### 输出

```
154873396
336592714
729645835
863725145
979314628
412958357
631457992
998236471
247789563```

# 题解

## 作者：kydbuhuipro (赞：8)

本题要求在9次操作内破坏一个数独，使其成为“反数独”，每行每列每宫都有重复数字。

我们知道，在数独中如果我们填错一个格，那么这一格所在的行、列、宫都会受到影响。所以我们对一个格进行操作后，其行、列、宫都会被破坏。每次操作正好破坏一行一列一宫，完美。

为了避免后续的操作将已经破坏的部分又恢复成数独的形式，我们可以让九次操作的格子互不在同行同列同宫。乍一看好像构造很复杂，**但完整数独中自带这个特性**。

数独游戏的基本规则是：**满足每一行、每一列、每一宫内的数字均含1-9，不重复。**

我们稍作调整便变为：**满足每个数字在每一行、每一列、每一宫仅出现一次。**

这个规则，恰为我们提供了解题的方法。我们只需要将1-9任一数字全部替换，就能保证最终的结果是一个“反数独”。

**附AC代码**
```cpp
#include<iostream>
#include<cmath>
#include<cstdio>
#include<algorithm>
using namespace std;
int main(){
	int t;
	cin>>t;
	for(int x=1;x<=t;x++){
		char c[9][9];
		for(int i=0;i<9;i++){
			for(int j=0;j<9;j++){
				cin>>c[i][j];
				if(c[i][j]=='1')c[i][j]++;
			}
		}
		for(int i=0;i<9;i++){
			for(int j=0;j<9;j++){
				cout<<c[i][j];
			}
			cout<<endl;
		}
	}
	return 0;
}
```


---

## 作者：_jimmywang_ (赞：2)

其实保证每一行、每一列、每个$3*3$的格子中都有且只有$1$个数被改成他相邻的任意一个数就好了。

比如你把$(1,1)(2,4)(3,7)(4,2)(5,5)(6,8)(7,3)(8,6)(9,9)$改一下就行了

代码：
```
#include<algorithm>
#include<bitset>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<map>
#include<iostream>
#include<queue>
#include<set>
#include<stack>
#include<string>
#include<vector>
using namespace std;
#define ll long long
#define f(i,a,b) for(int i=a;i<=b;i++)
inline ll read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
#define d read()
ll T;
ll a[10][10];
int main(){
    T=d;
    while(T--){
        f(i,1,9)
            f(j,1,9)
                scanf("%1d",&a[i][j]);
        f(i,1,9){
            f(j,1,9){
                if((i==1&&j==1)||(i==2&&j==4)||(i==3&&j==7)||(i==4&&j==2)||(i==5&&j==5)||(i==6&&j==8)||(i==7&&j==3)||(i==8&&j==6))cout<<a[i][j+1];
                else if(i==9&&j==9)cout<<a[i][j-1];
                else cout<<a[i][j];
            }
            cout<<endl;
        }
    }
    return 0;
}



```




---

## 作者：oimaster (赞：2)

根据我的小研究，我们只需要把所有的 $1$ 改成 $2$ 即可。

为什么这样子就可以？因为，这个原来的数独就是一个满足九宫格数独的要求，就是说每行、每列、每宫都没有重复，那么改一下 $1$，可以保证行至少有 $2$ 个 $2$ （原来的一个加上现在新改的一个），每列也会发生重复（原来的一个再加上现在新改的一个），每宫也是一样，所以能保证符合题目 Anti-Sudoku 的要求。

我觉得这种方法最简单，不过 dalao 们改一些特定坐标的方法我也是同意的，不过觉得我这种做法更方便，毕竟思维难度、代码难度都低了嘛。

---

## 作者：andyli (赞：2)

题意：  

给一个合法的数独，修改最多 $9$ 个数字，使得满足以下条件：  
- 每个数字均为 $1\sim 9$  
- 每行有至少两个相同的数字
- 每列有至少两个相同的数字
- 每个宫格中至少两个相同的数字

输出一种方案。  

分析：  

在每列、每行、每个宫格中各修改成另一个数即可。  
可修改以下 $9$ 个点：  
$$(1,1),(2,4),(3,7),(4,2),(5,5),(6,8),(7,3),(8,6),(9,9)$$

每列、每行、每个宫格恰好只修改了一个数。  

时间复杂度 $\mathcal O(9\times 9)$。  

代码如下（[模板](https://www.luogu.com.cn/blog/andyli/read-template)）：  
```cpp
const int maxn = 10;

const unsigned short d[][2] = {{}, {1, 1}, {2, 4}, {3, 7}, {4, 2}, {5, 5}, {6, 8}, {7, 3}, {8, 6}, {9, 9}};
unsigned short A[maxn][maxn], ans[maxn][maxn];
int main() {
    int q;
    io.read(q);
    while (q--) {
        for (int i = 1; i <= 9; i++)
            for (int j = 1; j <= 9; j++) {
                char ch;
                io.read(ch);
                ans[i][j] = A[i][j] = ch ^ 48;
            }
        for (int i = 1; i <= 9; i++) 
            for (int j = 1; j <= 9; j++)
                if (j != A[d[i][0]][d[i][1]]) {
                    ans[d[i][0]][d[i][1]] = j;
                    break;
                }
        for (int i = 1; i <= 9; i++, writeln())
            for (int j = 1; j <= 9; j++)
                io.putch(ans[i][j] ^ 48);
    }
    return 0;
}

```

---

## 作者：小恐 (赞：1)

~~div 3的题真是难（$sh \check{u} i$）啊！~~

这题只需要构造出改变9个格子，使得每个行、列、宫都改变了一次（最多才9个格子，不可能有一个行、列、宫改两个数）。至于改变成什么数，随便改个不是它自己的数就行。

比如说可以选择下面几个格子：
![](https://cdn.luogu.com.cn/upload/image_hosting/gq5esas6.png)
然后就上代码吧：
```cpp
#include<stdio.h>
using namespace std;
char a[15][15];
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		for(int i=1;i<=9;++i)
			scanf("%s",a[i]+1);
		for(int i=1;i<=3;++i)
			for(int j=1;j<=3;++j)
			{
				a[(i-1)*3+j][(j-1)*3+i]=a[(i-1)*3+j][(j-1)*3+i]+1;
				if(a[(i-1)*3+j][(j-1)*3+i]>'9')
					a[(i-1)*3+j][(j-1)*3+i]='1';
			}	
		for(int i=1;i<=9;++i)
			puts(a[i]+1);
	}
	return 0;
 } 
```
感谢观看。~~点个赞再走呗！~~

---

## 作者：Daniel_7216 (赞：0)

~~玄学大法吼啊~~

看见这道题首先想到是搜索，但是在构思框架的时候突然发现一个问题：只需要把任意的数字改成其他的就可以了。结果到题解区一看，全部都是这种做法……

这是因为，对于一个合法的数独，一个指定的数字不会出现在任何一行或一列，但是和其他的数一定在每一行每一列都会出现，所以只要把一个数全部换掉，就是所谓的 Anti-Sudoku 了。

那么如果要搜索呢？对于每一次搜索，我们只关注累计修改次数，要改的数字的行和列。还有这几个剪枝：
- 排除等效冗余。同一个格不应该填两次，标记一下即可。
- 可行性剪枝。如果想要修改的格子所在的行或列被涂过色，则认为这一格不需要。

~~（其实搜索算法跟玄学算法本质是相同的）~~

我决定只贴玄学代码，是因为我~~懒得写搜索~~认为只要不超出时限和空间限制还能保证正确性的方法就是正解。连修改的两个数都是随机数 doge 

挑战本题最玄学代码：
```cpp
#include <iostream>
#include <cstdlib>
#include <ctime>
#define random(x) rand()%(x)
int main(){
	int a, b, T;
	char sudoku[10][10];
	int sdk[10][10];
    srand((int)time(0));
    scanf("%d", &T);
    for (int K = 0;K <T; K++){
	    a = random(9) + 1;
	    b = random(9) + 1;
	    while (b == a){
	    	b = random(10);    	
		}
		for (int i = 0; i < 9; i++){
			scanf("%s", sudoku[i]);
		}
		for (int i = 0; i < 9; i++){
			for (int j = 0; j < 9; j++){
				if (sudoku[i][j] - '0' == a){
					sdk[i][j] = b;
				}else sdk[i][j] = sudoku[i][j] - '0';
			}
		}
		for (int i = 0; i < 9; i++){
			for (int j = 0; j < 9; j++){
				printf("%d", sdk[i][j]);
			}
			printf("\n");
		}
	}
    return 0;
}
```

---

## 作者：hanyuchen2019 (赞：0)

## 小学生发题解 第$5$弹

emm...这道题有各位巨佬说的那么难吗？？？

其实，我们只需要把数组中的所有的 $x$ （任意）替换为 $y$ （任意）就行了。$(x≠y)$

因为数独的基本性质是：

>每一行、每一列、每一个粗线宫（3*3）内的数字均含1-9，不重复。 by [百度百科](https://baike.baidu.com/item/%E6%95%B0%E7%8B%AC/74847?fr=aladdin)

也就是说，我们要替换的 $x$ 所在的的行、列、宫必定也都有数 $y$。因此把 $9$ 个 $x$ 替换为 $y$ 后，每个行、列、宫都会有 $2$ 个 $y$，成功变成了一个Anti-Sudoku。

### C++ code:

```
#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		char ch;
		for(int i=0;i<9;i++)
		{
			for(int j=0;j<9;j++)
			{
				cin>>ch;
				if(ch=='1')cout<<'2';//设x=1,y=2。
				else cout<<ch;
			}
			cout<<endl;
		}
	}
	return 0;
}
```
bye~祝你AC这道题！~~真的很水~~

---

## 作者：juicyyou (赞：0)

# CF1335D Anti-Sudoku
## 题目大意:
本题共有 $t$ 组数据, 对于每一组数据, 给定一个保证正确的已经完成的数独, 请你改动**至多 $9$ 个**数独中的数, 使得改动后数独中每行每列每宫中都至少有两个数相等, 请输出一个可行的改动后的数独。
## 解法:
玩玩数独就可以知道, 改变数独中的一个格子中填的数, 会使它所在的那一行、那一列以及那一宫都出现一组重复的数。而我们知道改变一个数会仅使它那一宫出现一组重复的数, 而题目中要求每一宫都有一组重复的数, 所以我们必定要改动 $9$ 个数。在综合前面的结论以及简单构造就可以知道, 改动 $(1, 1), (2, 4), (3, 5), (4, 2), (5, 5), (6, 8), (7, 3), (8, 6)$ 以及 $(9, 9)$ 这几个位置上的数就可以满足要求。然后这题就做完了。

下面是我的Code:
```cpp
#include<iostream>
using namespace std;
typedef long long ll;
ll ans, cnt, n, b, c, t;
char a[10][10];
int main(){
	cin >> t;
	while(t--){
		for(int i = 1;i <= 9;i++){
			for(int j = 1;j <= 9;j++){
				cin >> a[i][j];
			}
		}
		a[1][1] = (char)((a[1][1] - '0') % 9 + 1 + '0');
		a[4][2] = (char)((a[4][2] - '0') % 9 + 1 + '0');
		a[7][3] = (char)((a[7][3] - '0') % 9 + 1 + '0');
		a[2][4] = (char)((a[2][4] - '0') % 9 + 1 + '0');
		a[5][5] = (char)((a[5][5] - '0') % 9 + 1 + '0');
		a[8][6] = (char)((a[8][6] - '0') % 9 + 1 + '0');
		a[3][7] = (char)((a[3][7] - '0') % 9 + 1 + '0');
		a[6][8] = (char)((a[6][8] - '0') % 9 + 1 + '0');
		a[9][9] = (char)((a[9][9] - '0') % 9 + 1 + '0');
		for(int i = 1;i <= 9;i++){
			for(int j = 1;j <= 9;j++){
				cout << a[i][j];
			}
			cout << endl;
		}
	}
	return 0;
}
```
上述算法的复杂度为 $O(t)$, 可以通过此题。

---

## 作者：YuanZhizheng (赞：0)


![](https://cdn.luogu.com.cn/upload/image_hosting/h9zxbnrc.png?x-oss-proc1ess=image/resize,m_lfit,h_170,w_225)

选这么9个位置，分别影响不同的行、列和3*3方块，只要把这几个位置的数字改成非原来的数字即可。

还有一种解法，后来知道的，每种数字在9*9数独里面都是出现9次，所以把全部1替换成2，或者全部2替换成3这种，就可以了....

第一种解法如下，对着图数就行了，当然位置不唯一。

```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
inline ll read()
{
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9')
    {
        if(c=='-')
            f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9')
    {
        x=x*10+c-'0';
        c=getchar();
    }
    return x*f;
}
char s[100][100];
int main()
{
    ll t;
    t=read();
    while(t--)
    {
        int i,j,k;
        for(i=0;i<9;i++)
            scanf("%s",s[i]);
        if(s[0][0]=='9')s[0][0]='1';
        else s[0][0]++;
 
        if(s[3][1]=='9')s[3][1]='1';
        else s[3][1]++;
 
        if(s[6][2]=='9')s[6][2]='1';
        else s[6][2]++;
 
        if(s[2][3]=='9')s[2][3]='1';
        else s[2][3]++;
 
        if(s[4][4]=='9')s[4][4]='1';
        else s[4][4]++;
 
        if(s[1][6]=='9')s[1][6]='1';
        else s[1][6]++;
 
        if(s[7][5]=='9')s[7][5]='1';
        else s[7][5]++;
 
        if(s[5][7]=='9')s[5][7]='1';
        else s[5][7]++;
 
        if(s[8][8]=='9')s[8][8]='1';
        else s[8][8]++;
 
        for(i=0;i<9;i++)
        {
            for(j=0;j<9;j++)
                printf("%c",s[i][j]);
            printf("\n");
        }
    }
    return 0;
}
```

第二种解法，也就是替换法。
```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
inline ll read()
{
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9')
    {
        if(c=='-')
            f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9')
    {
        x=x*10+c-'0';
        c=getchar();
    }
    return x*f;
}
char s[100][100];
int main()
{
    ll t;
    t=read();
    while(t--)
    {
        int i,j,k;
        for(i=0;i<9;i++)
            scanf("%s",s[i]);
        for(i=0;i<9;i++)
        {
            for(j=0;j<9;j++)
            {
                if(s[i][j]=='1')
                    s[i][j]='2';
            }
        }
 
        for(i=0;i<9;i++)
        {
            for(j=0;j<9;j++)
                printf("%c",s[i][j]);
            printf("\n");
        }
    }
    return 0;
}
```

---

## 作者：Karry5307 (赞：0)

### 题面

给你一个数独，你需要改一些格子使得每一行每一列每一宫至少有两个一样的数字。

$\texttt{Data Range:}1\leq T\leq 10^4$

### 题解

这就是考你玩没玩过数独。

考虑构造九个格子使得每行每列每宫都有一个，如果你曾经出过数独题的话很明显你可以发现可能的九个格子的方案为

$$\texttt{A1,B4,C7,D2,E5,F8,G3,H6,I9}$$

所以把这九个格子里的数改成别的就好了。

### 代码

```cpp
// This code is written by Karry5307
#include<bits/stdc++.h>
// Definition
#define For(i,x,y) for(register int i=(x);i<(y);i++)
#define Forr(i,x,y) for(register int i=(x);i<=(y);i++)
#define Rep(i,x,y) for(register int i=(x);i>(y);i--)
#define Repp(i,x,y) for(register int i=(x);i>=(y);i--)
#define ve vector
#define iter iterator
#define pb emplace_back
#define popb pop_back
#define all(x) x.begin(),x.end()
#define sz(x) (int)(x.size())
#define F first
#define S second
using namespace std;
// Typedefs
typedef int ll;
typedef long long int li;
typedef unsigned int ul;
typedef unsigned long long int ull;
typedef double db;
typedef long double ldb;
typedef pair<ll,ll> pii;
typedef pair<li,li> pll;
const ll MAXN=2e5+51,MOD=998244353,inf=0x3f3f3f3f;
// Structures and variables
ll test;
ll x[9]={0,3,6,1,4,7,2,5,8};
char table[9][9];
// Fast IO
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-') ch=getchar();
    if(ch=='-') neg=-1,ch=getchar();
    while(isdigit(ch)) num=(num<<3)+(num<<1)+(ch-'0'),ch=getchar();
    return neg==1?num:-num;
} 
inline li readu()
{
    register li num=0;
    register char ch=getchar();
    while(!isdigit(ch)) ch=getchar();
    while(isdigit(ch)) num=(num<<3)+(num<<1)+(ch-'0'),ch=getchar();
    return num;
} 
template<class T>
inline void writep(T x)
{
	if(x<0){return (void)putchar('-'),writep(-x);}
	if(x<10){return (void)putchar(x|48);}
	writep(x/10),putchar((x%10)|48);
}
template<class T>
inline void write(T x,char ch=' '){writep(x),putchar(ch);}
template<class T>
inline void writeln(T x){writep(x),putchar('\n');}
// chkmin and chkmax
template<class T>
inline void chkmax(T &x,const T &y){x=x>y?x:y;}
template<class T>
inline void chkmin(T &x,const T &y){x=x<y?x:y;}
// Functions
template<class T,class Compare>
inline void sort(ve<T>&v,Compare cmp=less<T>()){sort(all(v),cmp);}
template<class T>
inline void reverse(ve<T>&v){reverse(all(v));}
template<class T>
inline void clear(T *arr){memset(arr,0,sizeof(arr));}
template<class T>
inline void setInf(T *arr){memset(arr,0x3f,sizeof(arr));}
// Math funcs
inline ll qpow(ll base,ll exponent)
{
	li res=1;
	while(exponent)
	{
		if(exponent&1)
		{
			res=(li)res*base%MOD;
		}
		base=(li)base*base%MOD,exponent>>=1;
	}
	return res;
}
inline ll gcd(ll x,ll y)
{
	return !y?x:gcd(y,x%y);
}
inline li lcm(ll x,ll y)
{
	return x/gcd(x,y)*y;
}
// Functions
inline void solve()
{
	for(register int i=0;i<9;i++)
	{
		for(register int j=0;j<9;j++)
		{
			cin>>table[i][j];
		}
	}
	for(register int i=0;i<9;i++)
	{
		table[i][x[i]]++;
		if(table[i][x[i]]=='9'+1)
		{
			table[i][x[i]]='1';
		}
	}
	for(register int i=0;i<9;i++)
	{
		for(register int j=0;j<9;j++)
		{
			cout<<table[i][j];
		}
		cout<<endl;
	}
}
int main()
{
	test=read();
	for(register int i=0;i<test;i++)
	{
		solve();
	}
}
```

---

