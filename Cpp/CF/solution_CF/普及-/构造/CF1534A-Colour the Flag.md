# Colour the Flag

## 题目描述

Today we will be playing a red and white colouring game (no, this is not the Russian Civil War; these are just the colours of the Canadian flag).

You are given an $ n \times m $ grid of "R", "W", and "." characters. "R" is red, "W" is white and "." is blank. The neighbours of a cell are those that share an edge with it (those that only share a corner do not count).

Your job is to colour the blank cells red or white so that every red cell only has white neighbours (and no red ones) and every white cell only has red neighbours (and no white ones). You are not allowed to recolour already coloured cells.

## 说明/提示

The answer for the first example case is given in the example output, and it can be proven that no grid exists that satisfies the requirements of the second example case. In the third example all cells are initially coloured, and the colouring is valid.

## 样例 #1

### 输入

```
3
4 6
.R....
......
......
.W....
4 4
.R.W
....
....
....
5 1
R
W
R
W
R```

### 输出

```
YES
WRWRWR
RWRWRW
WRWRWR
RWRWRW
NO
YES
R
W
R
W
R```

# 题解

## 作者：zct_sky (赞：2)

### 思路：
可以分两种情况讨论：

1.第一个是红色（ `R` ），例如：

$\begin{matrix}{\mathrm{RWRWRWRWRW}}\\{\mathrm{WRWRWRWRWR}}\\{\mathrm{RWRWRWRWRW}}\end{matrix}$

2.第一个是白色（ `W` ），例如：

$\begin{matrix}{\mathrm{WRWRWRWRWR}}\\{\mathrm{RWRWRWRWRW}}\\{\mathrm{WRWRWRWRWR}}\end{matrix}$

然后分别判断所给矩阵是否能变成上面两种矩阵的其中一种，若可以，则输出 `YES` 以及可变成的那一种矩阵，否则输出 `NO` 。

### 代码：
```c++
#include<bits/stdc++.h>
#define ll long long
#define un unsigned
using namespace std;
inline int read(){//快读 
	int x=0,y=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')y=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return x*y;
}
char a[51][51];
int n,m,t;
void work(){
	char b[51][51],c[51][51];//b数组为第一个是白色的矩阵，c数组为第一个是红色的矩阵
	bool fb=1,fc=1;
	for(int i=0;i<n;i++)//存入矩阵 
	    for(int j=0;j<m;j++)
	        if((i+j)%2) b[i][j]='W',c[i][j]='R';
	        else b[i][j]='R',c[i][j]='W';
	for(int i=0;i<n;i++)//判断 
	    for(int j=0;j<m;j++)
	        if(a[i][j]!='.'){ 
			    if(a[i][j]!=b[i][j])fb=0;
	            if(a[i][j]!=c[i][j])fc=0;
	        }
	if(fb){
		cout<<"YES\n";
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++) cout<<b[i][j];
			puts("");
		}
	}else if(fc){
		cout<<"YES\n";
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++) cout<<c[i][j];
			puts("");
		}
	}else cout<<"NO\n";
}
int main(){
	t=read();
	for(int k=0;k<t;k++){
		n=read(),m=read();
		for(int i=0;i<n;i++)
		    for(int j=0;j<m;j++)
		        cin>>a[i][j];
		work();
	}
	return 0;
}
```

---

## 作者：HerikoDeltana (赞：2)

# A Colour the Flag

[CF1534A Colour the Flag](https://www.luogu.com.cn/problem/CF1534A)

## 题意简述

给你一个方阵，方阵由 "W" "R" "." 这三种字符组成，其中 "." 代表的是空位置，可以任意的填放剩下两种字符。

现在问你当前给出的方阵能否填充为一个 "WR相间" 的方阵，

若可行，输出 "YES" 并输出这个符合要求的方阵；

否则输出 "NO" 。

每个测试点有多组数据。

## 思路简述

可以发现实际上能够满足要求的方阵只有两种，即**左上角是 W** 和**左上角是 R** 两种。

于是我们可以预处理一下然后进行比较即可。

## Code

赛时代码，略丑勿喷。

```cpp
#include <bits/stdc++.h>
#define Heriko return
#define Deltana 0
#define S signed
#define LL long long
#define R register
#define I inline
#define CI const int
#define mst(a, b) memset(a, b, sizeof(a))
#define ON std::ios::sync_with_stdio(false)
using namespace std;
I void fr(LL & x)
{
    LL f=1;
    char c=getchar();
    x=0;
    while(c<'0' or c>'9')
    {
        if(c=='-') f=-1;
        c=getchar();
    }
    while (c>='0' and c<='9') 
    {
        x=(x<<3)+(x<<1)+c-'0';
        c=getchar();
    }
    x*=f;
}
I void fw(LL x)
{
    if(x<0) putchar('-'),x=-x;
    static LL stak[35];
    LL top=0;
    do
    {
        stak[top++]=x%10;
        x/=10;
    }
    while(x);
    while(top) putchar(stak[--top]+'0');
}
char ch[100][100];
LL t,n,m,a[100][100],b[100][100],c[100][100];
I void cw()
{
    mst(b,0);mst(c,0);
    for(R LL i=1;i<=100;++i)
        for(R LL j=1;j<=100;++j)
            if((i+j)&1) b[i][j]=1,c[i][j]=2;
            else b[i][j]=2,c[i][j]=1;
}
S main()
{
    fr(t);
    cw();
    while(t--)
    {
        fr(n),fr(m);
        mst(a,0);
        for(R LL i=1;i<=n;++i)
            for(R LL j=1;j<=m;++j)
                cin>>ch[i][j];
        for(R LL i=1;i<=n;++i)
            for(R LL j=1;j<=m;++j)
                if(ch[i][j]=='W') a[i][j]=1;
                else if(ch[i][j]=='R') a[i][j]=2;
        bool c1,c2;
        c1=c2=true;
        for(R LL i=1;i<=n;++i)
            for(R LL j=1;j<=m;++j)
                if(b[i][j]!=a[i][j] and a[i][j])
                {
                    c1=false;
                    break;
                }
        if(c1)
        {
            puts("YES");
            for(R LL i=1;i<=n;putchar('\n'),++i)
                for(R LL j=1;j<=m;++j)
                    if(b[i][j]==2) putchar('R');
                    else putchar('W');
            continue;
        }
        for(R LL i=1;i<=n;++i)
            for(R LL j=1;j<=m;++j)
                if(c[i][j]!=a[i][j] and a[i][j])
                {
                    c2=false;
                    break;
                }
        if(c2)
        {
            puts("YES");
            for(R LL i=1;i<=n;putchar('\n'),++i)
                for(R LL j=1;j<=m;++j)
                    if(c[i][j]==2) putchar('R');
                    else putchar('W');
            continue;
        }
        else
        {
            puts("NO");
            continue;
        }   
    }
    Heriko Deltana;
}
```

---

## 作者：张语诚ZYC (赞：1)

## 题意回顾

你需要给一面 $n \times m$ 的旗上色。你将得到一个矩阵，有 $n$ 行，每行  $m$ 个元素。每个元素包含 `R` ， `W` 和 `.` 三个字符。其中 `R` 表示红色，`W` 表示白色，`.`表示还没有涂色。你需要把 `.` 图上色，使涂完颜色的旗中，每一个颜色上下左右不与另一个颜色相同。

## 思路分析

其实这可以分为两种情况：

1. 第一个颜色是红色，比如：

![](https://pic.imgdb.cn/item/60c83696844ef46bb2e13b91.png)

2. 第一个颜色是白色，比如：

![](https://pic.imgdb.cn/item/60c836f9844ef46bb2e6ee6f.png)

假设 $x$ 和 $y$ 分别表示一个点的行号和列号。

通过观察，我们发现，如果 $(x+y) \bmod 2 = 0$ 那么所有满足这个条件的点都是同一个颜色，如果 $(x+y) \bmod 2 = 1$，所有满足这个条件的点都是另外一个颜色。

所以我们通过程序判断出对应点的颜色，如果出现同样颜色的点出现在上述不同情况中，或者是同一情况中出现不同颜色的点，直接输出 `NO` ，否则，输出整个矩阵。

建议使用假设法判断，如果不在意时间（毕竟数据规模不大），使用搜索判断也行（从一个已知点向四个方向扩展，遇到其他已知点判断是否出现无解情况后退出）。

---

## 作者：BorisDimitri (赞：1)

# 题意
给出一个大小为 $n\times m$ 的矩阵 $S$，由 `.`,`R`,`W` 三种字母组成，现在要求将 `.` 替换为 `R`,`W` ，使得 :

>`R` 的 **上下左右** 没有 `R`。
>
>`W` 的 **上下左右** 没有 `W`。

# 分析
**满足要求的矩阵只有两种形式：**
>1 . 对于 $\forall (i,j) \in S$ 且 $S(i,j) = $ `R`,有 $i+j \mod 2 = 0$,即下图形式。

![](https://cdn.luogu.com.cn/upload/image_hosting/riiwotug.png)

>2 . 对于 $\forall (i,j) \in S$ 且 $S(i,j) = $ `W`,有 $i+j \mod 2 = 0$,即下图形式。

![](https://cdn.luogu.com.cn/upload/image_hosting/kbri1iy7.png)

所以我们可以直接将这两种矩阵 **预处理** 出来，再与输入的矩阵进行**配对**，有匹配的就输出，没有就输出 `no`。

# Code
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 55;

int t;
int n,m;
char g[N][N];
char ans[N][N][2];

bool check(int x)
{
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            if(ans[i][j][x] != g[i][j] && g[i][j] != '.')
                return false;
    return true;
}

void print(int x)
{
    cout<<"YES"<<endl;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
            cout<<ans[i][j][x];
        cout<<endl;
    }
}

int main()
{
    cin>>t;

    for(int i=0;i<=50;i++)
        for(int j=0;j<=50;j++)
            if((i+j) % 2 == 0) ans[i][j][0] = 'W',ans[i][j][1] = 'R';
            else ans[i][j][0] = 'R',ans[i][j][1] = 'W';
 
    while(t--)
    {
        cin>>n>>m;
        for(int i=0;i<n;i++) cin>>g[i];

        if(check(0)) print(0);
        else if(check(1)) print(1);
        else cout<<"NO"<<endl;
    }

    return 0;
}

```

---

## 作者：Halberd_Cease (赞：0)

[CF1534A](https://www.luogu.com.cn/problem/CF1534A)

模拟就可以了。
## 分析
### 初始化
已知要求红 ```R``` 白 ```W``` 各不相交，容易想到共有2种情况：

1. 从 ```R``` 开始：
```
RWRWRWR
WRWRWRW
RWRWRWR
WRWRWRW
RWRWRWR
WRWRWRW
RWRWRWR
```
2. 从 ```W``` 开始：
```
WRWRWRW
RWRWRWR
WRWRWRW
RWRWRWR
WRWRWRW
RWRWRWR
WRWRWRW
```
可以想到开两个数组存储这两个状态。

### 判断
如果是 ```.``` 就跳过。

否则判断，如果和情况 1 不符就将标志 1 改为 ```false``` ，和情况 2 不符就将标志 2 改为 ```false``` 。

最后如果两个标志都是 ```false``` ，返回 ```0``` ；

否则返回值为 ```true``` 标志的编号。


### 输出
没什么好说的，成立直接打印即可。

## 最终代码
```cpp
#include<bits/stdc++.h>
#define N 50+10
using namespace std;
bool c1[N][N],c2[N][N];//1=R,0=W;
char mapp[N][N],ans[2]={'W','R'};
void init()
{
    bool t=0;
    for(int i=1;i<=51;i++)
    for(int j=1;j<=51;j++)
    {
        c1[i][j]=t;
        c2[i][j]=!t;
        if(t==1)t=0;
        else t=1;
    }
}
int check(int n,int m)
{
    bool flag1=1,flag2=1;
    for(int i=1;i<=n;i++)
    for(int j=1;j<=m;j++)
    {
        if(mapp[i][j]=='.')
        continue;
        if(mapp[i][j]!=ans[c1[i][j]])flag1=0;
        if(mapp[i][j]!=ans[c2[i][j]])flag2=0;
    }
    if(flag1)return 1;
    if(flag2)return 2;
    return 0;
}
void print1(int n,int m)
{
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            cout<<ans[c1[i][j]];
        }
        cout<<endl;
    }
}
void print2(int n,int m)
{
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            cout<<ans[c2[i][j]];
        }
        cout<<endl;
    }
}
int main()
{
    init();
    int t;
    cin>>t;
    while(t--)
    {
        memset(mapp,0,sizeof(mapp));
        int m,n;
        cin>>n>>m;
        for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        cin>>mapp[i][j];
        int flag=check(n,m);
        if(flag==0)cout<<"NO\n";
        else
        {
            cout<<"YES\n";
            if(flag==1)print1(n,m);
            else print2(n,m);
        }
    }
}
```


---

## 作者：jiangtaizhe001 (赞：0)

[题目传送门](https://codeforces.com/problemset/problem/1534/A)
## 题目大意
给定一个带有 `R`，`W` 和 `.` 的 $n$ 行 $m$ 列的字符矩阵。  
请你将所有 `.` 的位置换成 `R` 或者 `W`，要求最终每个 `R` 的位置上下左右没有 `R`，每个 `W` 的位置上下左右没有 `W`。  
如果做不到，输出 `NO`。  
否则输出 `YES`，并且输出方案。  
## 题目解析
显然我们发现，所有的 `R` 的四周全部是 `W`，所有的 `W` 四周全是 `R`，那么大致就成了一张网格状的矩阵，大概长这样：
```
WRWRWRWRWRWRWRWR
RWRWRWRWRWRWRWRW
WRWRWRWRWRWRWRWR
RWRWRWRWRWRWRWRW
WRWRWRWRWRWRWRWR
RWRWRWRWRWRWRWRW
```
或者是这样：
```
RWRWRWRWRWRWRWRW
WRWRWRWRWRWRWRWR
RWRWRWRWRWRWRWRW
WRWRWRWRWRWRWRWR
RWRWRWRWRWRWRWRW
WRWRWRWRWRWRWRWR
```
由于我们发现 `W` 和 `R` 都是相间存在的，我们可以考虑横纵坐标之和的奇偶性。  
不难发现，两种形式中任意一个都有以下性质：  
同种颜色的横纵坐标之和的奇偶性相同，不同种颜色的横纵坐标之和的奇偶性不同。  

具体大概是这样：  
| 情况 | W | R |
|--|--|--|--|
| 第一种 | 1 | 0 |
| 第二种 | 0 | 1 |
`W` 代表任意的 `W` 的横纵坐标之和除以 $2$ 的余数  
`R` 代表任意的 `R` 的横纵坐标之和除以 $2$ 的余数  

代码：
```cpp
#include<cstdio>
#define maxn 139
using namespace std;
//#define debug
typedef int Type;
inline Type read(){
	Type sum=0;
	int flag=0;
	char c=getchar();
	while((c<'0'||c>'9')&&c!='-') c=getchar();
	if(c=='-') c=getchar(),flag=1;
	while('0'<=c&&c<='9'){
		sum=(sum<<1)+(sum<<3)+(c^48);
		c=getchar();
	}
	if(flag) return -sum;
	return sum;
}
int T,n,m,a[maxn][maxn];
int flag,c;
int check(){
	for(int i=1;i<=n;i++)
	    for(int j=1;j<=m;j++){
	    	if(a[i][j]){
	    		if(flag==-1) flag=(i+j+a[i][j])%2;
				else{
					if(flag==(i+j+a[i][j])%2);
					else return 0;
				}
			}
		}
	return 1;
}
int main(){
	//freopen(".in","r",stdin);
	//freopen("1.out","w",stdout);
    T=read();
    while(T--){
    	flag=-1;
    	n=read(); m=read();
    	for(int i=1;i<=n;i++)
    	    for(int j=1;j<=m;j++){
    	    	c=getchar();
    	    	while(c!='R'&&c!='.'&&c!='W') c=getchar();
    	    	if(c=='R') a[i][j]=1;
    	    	else if(c=='W') a[i][j]=2;
    	    	else a[i][j]=0;
			}
		if(check()){
			if(flag==-1) flag=0;
			printf("YES\n");
			for(int i=1;i<=n;i++){
				for(int j=1;j<=m;j++)
				    if((i+j)%2==flag) putchar('W');
				    else putchar('R');
				putchar('\n');
			}
		}
		else printf("NO\n");
	}
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：0)

## 题目描述

给出一个矩阵包含 $.$，$W$，$R$。

请问你能不能将它用 $W$ 和 $R$ 间隔染色。

## 题解

考虑两种情况：
```
WRWRWR...
RWRWR...
WRWR...
RWR...
WR...
R...
```
和
```
RWRWRW...
WRWRW...
RWRW...
WRW...
RW...
W...
```
查看是否可以和原矩阵匹配（即原矩阵每一个 $W$ 新矩阵均是 $W$，每一个 $R$ 新矩阵均是 $R$），如果可以输出 `Yes`，不可以 `No`。

## 代码


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main() {
	int t;
	cin>>t;
	while(t--){
		int n,m;
		cin>>n>>m;
		char c[100][100],d[100][100],e[100][100];
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				cin>>c[i][j];
			}
		} 
		bool tf=true;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				if((i+j)%2==0){
					d[i][j]='R';
				}
				else{
					d[i][j]='W';
				}
				if(c[i][j]!='.'&&c[i][j]!=d[i][j]){
					tf=false;
				}
			}
		}
		if(tf){
			cout<<"YES"<<endl;
			for(int i=1;i<=n;i++){
				for(int j=1;j<=m;j++){
					cout<<d[i][j];
				}
				cout<<endl;
			}
			continue;
		}
		tf=true;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				if((i+j)%2==0){
					d[i][j]='W';
				}
				else{
					d[i][j]='R';
				}
				if(c[i][j]!='.'&&c[i][j]!=d[i][j]){
					tf=false;
				}
			}
		}
		if(tf){
			cout<<"YES"<<endl;
			for(int i=1;i<=n;i++){
				for(int j=1;j<=m;j++){
					cout<<d[i][j];
				}
				cout<<endl;
			}
			continue;
		}
		cout<<"NO"<<endl;
	}

	return 0;
}

```

---

