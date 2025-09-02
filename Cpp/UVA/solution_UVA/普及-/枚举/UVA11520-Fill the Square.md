# Fill the Square

## 题目描述

在一个$n*n$的网格中填了一些大写字母，你的任务是把剩下的格子中也填满大写字母，使得任意两个相邻的格子(即有公共边的格子)中的字母不同。如果有多种填法，则要求按照从上到下，从左到右的顺序把所以格子连接起来得到的字符串的字典序应该尽量小。

## 样例 #1

### 输入

```
2
3
...
...
...
3
...
A..
...```

### 输出

```
Case 1:
ABA
BAB
ABA
Case 2:
BAB
ABA
BAB```

# 题解

## 作者：Kdlyh (赞：3)

## _又是一道蓝书上的题呢。_


楼下的咋是直接抄蓝书的啊,我觉得吧做题要有自己的思想，我看到这道题，第一个想的就是bfs。大概就是直接搜每一个点。
- 如果这个点本来就有字母，那就直接把这个字符存入答案

- 否则从$'A'$到$'Z'$枚举，如这个点四周没有相同的字符就把这个字符存入答案，然后直接break,**因为要字典序最小的，而因为是从$'A'$到$'Z'$枚举，所以每次先找到的可行解一定是字典序最小的**。

#### CODE（STL实现)

```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>

using std::queue;
using std::cin;
using std::cout;
using std::ios;
const int dx[4]={0,0,-1,1},dy[4]={1,-1,0,0};
int n,T;
int vis[3242][3422];
char map[324][234];
char ans[324][234];

inline bool in_side(int x,int y)
{
    return (x>0 && x<=n && y>0 && y<=n);
}

inline bool check(int x,int y,char xs)
{
    int ok=1;
    for(int i=0; i<4; i++)
    {
        int sx=x+dx[i],sy=y+dy[i];
        if(in_side(sx,sy) && (ans[sx][sy] == xs))
        {
            ok=0;
            break;
        }
    }
    return ok;
}
struct node
{
    int x,y;
};

inline void bfs(int x,int y)
{
    queue<node> Q;
    Q.push({x,y});
    while(!Q.empty())
    {
        node fr=Q.front();
        Q.pop();
        if(ans[fr.x][fr.y] == '.')
        {
            for(int ch='A'; ch<='Z'; ch++)
            {
                if(check(fr.x,fr.y,ch))
                {
                    ans[fr.x][fr.y]=ch;
                    break;
                }
            }
        }
        
        for(int i=0; i<4; i++)
        {
            int sx=fr.x+dx[i],sy=fr.y+dy[i];
            if(in_side(sx,sy) && !vis[sx][sy])
            {
                vis[sx][sy]=1;
                Q.push({sx,sy});
            }
        }
       // printf("ans[%d][%d]=%c\n",fr.x,fr.y,ans[fr.x][fr.y]);
    }
    
}

int main()
{
    scanf("%d",&T);  
    for(int Case=1; Case<=T; Case++)
    {
        memset(vis,0,sizeof vis);
        scanf("%d",&n);
        for(int i=1; i<=n; i++)
        {
            for(int j=1; j<=n; j++)
            {
                cin>>map[i][j];
                ans[i][j]=map[i][j];
            }
        }
        vis[1][1]=1;
        bfs(1,1);
        printf("Case %d:\n",Case);
        for(int i=1; i<=n; i++)
        {
            for(int j=1; j<=n; j++)
            {
                printf("%c",ans[i][j]);
            }
            printf("\n");
        }
    }
    return 0;
}
```


---

## 作者：woai__Accepted (赞：2)

## 题目描述

在 $n \times n$ 方格空格内填满大写字母，使得上下左右的大写字母不同。

## 解题思路

### 直接遍历

因为要保证最后方格的字-典序尽量小，所以可以从 $A$ 遍历到 $Z$，找出最小的上下左右不同的大写字母，填入空格。

### $\texttt {check}$ 函数

```cpp
bool check(int x,int y,char ch){
	if(s[x+1][y]==ch||s[x][y+1]==ch||s[x-1][y]==ch||s[x][y-1]==ch){
		return false;
	}
	return true;
} 
```
## 完整 $\texttt {AC}$ 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
char s[15][15];
int t,n;
bool check(int x,int y,char ch){
	if(s[x+1][y]==ch||s[x][y+1]==ch||s[x-1][y]==ch||s[x][y-1]==ch){
		return false;
	}
	return true;
} 
int main(){
	cin>>t;
	for(int k=1;k<=t;k++){
		cin>>n;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				cin>>s[i][j];
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				if(s[i][j]=='.'){
					for(char a='A';a<='Z';a++){
						if(check(i,j,a)) {
							s[i][j]=a;
							break;
						}
					}
				}
		printf("Case %d:\n",k);
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				cout<<s[i][j];
			}
			cout<<endl;
		}	
	}
	return 0;
}
```


---

## 作者：YB_is_short (赞：1)

这题是一个暴力

它让我们求字典序最小

而且数据小得可怜$(1≤n≤10)$

所以可以暴力地枚举每个点

如果他没有填过字母

就暴力的枚举每个字母是否在上下左右四个格子里出现过

没有就填上

代码:
```cpp
#include<bits/stdc++.h>
using namespace std;
char c[11][11];
int t,n;
int main()
{
	ios::sync_with_stdio(false);
	cin>>t;
	for(int _=1;_<=t;_++)
	{
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
			{
				cin>>c[i][j];
			}
		}
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
			{
				if(c[i][j]=='.')
				{
					for(char ch='A';ch<='Z';ch++)
					{
						if(c[i-1][j]!=ch&&c[i+1][j]!=ch&&c[i][j-1]!=ch&&c[i][j+1]!=ch)
						{
							c[i][j]=ch;
							break; 
						}
					}
				}
			}
		}
		cout<<"Case "<<_<<":"<<endl;
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
			{
				cout<<c[i][j];
			}
			cout<<endl;
		}
	}
	return 0;
}
```

---

## 作者：zzh_han (赞：1)

## 题意

就是有 $T$ 组数据，每组都有一个 $n$ 然后输入一个 $n*n$ 的一个字符矩阵，矩阵上的字符可以是 $A$ 到 $Z$ 的任何字母也可以是 $'.'$ 如果是 $'.'$ 那我们要在上面填上一个字母，这个字母不能和上下左右重合也要是这个填上去的字母的ASCII码尽量达到最小。

## 做法

我们可以直接暴力的进行扫描只要当前的字符为 $'.'$ 那么我们就从 $A$ 到 $Z$ 进行枚举看是否达到了条件，如果符合条件就将字母填入最后输出字符矩阵。上代码！！！

```c++
#include <bits/stdc++.h>
using namespace std;
int n,s;
int k=0,ans;
char f[15][15];
int main()
{
	int T;
	scanf("%d",&T);
	for(int ii=1;ii<=T;ii++)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				cin>>f[i][j];
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				if(f[i][j]=='.')//判断这个是否为.
				{
					for(int c='A';c<='Z';c++)//暴力枚举是否合法
						if(f[i-1][j]!=c  && f[i][j-1]!=c && f[i+1][j]!=c && f[i][j+1]!=c)//在上下左右进行判读看是否符合条件
						{
							f[i][j]=c;
							break;//符合条件就将字符填入字符矩阵并弹出
						}
				}
		cout<<"Case "<<ii<<":"<<endl;
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
				cout<<f[i][j];
			cout<<endl;
		}
	}
	return 0;
}
```

~~啊一天写两篇题解的感觉太棒了~~

---

## 作者：二叉苹果树 (赞：0)

考虑对每个矩阵的位置字符，依次从左上角至右下角依次填入。

填入字符时，暴力枚举  $\rm{A}$ ~ $\rm{E}$ , 因为对于一个位置的字母,它与其相邻的字母一共有 $5$ 个，所以也只会填上 $\rm{A}$ ~ $\rm{E}$ 之一的字母。

需要注意对于边界的处理，防止出现越界情况。

根据以上思路，不难写出一下代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=15;
char g[MAXN][MAXN];
int n;
int main()
{
	int t;
	cin>>t;
	for(int k=1;k<=t;k++)
	{
		cin>>n;
		for(int i=0;i<n;i++)
		    scanf("%s",g[i]); 
		for(int i=0;i<n;i++)
		    for(int j=0;j<n;j++)
		        if(g[i][j]=='.')
		            for(char ch='A';ch<='Z';ch++)
		            {
		            	bool f=1;
		            	if(i>0&&g[i-1][j]==ch)
		            	    f=0;
		            	if(i<n-1&&g[i+1][j]==ch)
		            	    f=0;
		            	if(j>0&&g[i][j-1]==ch)
		            	    f=0;
		            	if(j<n-1&&g[i][j+1]==ch)
		            	    f=0;
		            	if(f)
		            	{
		            		g[i][j]=ch;
		            		break;
						}
					}
	    printf("Case %d:\n",k);
	    for(int i=0;i<n;i++)
	        printf("%s\n",g[i]);
	}
	return 0;
 } 
```


---

## 作者：Micnation_AFO (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/UVA11520)  
[$\texttt{AC}$ 记录](https://www.luogu.com.cn/record/75622490)

--------------------


考虑对每个位置按照字典序大小依次枚举，对于输入中已经给出的字母，直接输出即可。否则判断一下边界是否有相同字母，并输出满足要求的最小值即可。

显然，不会出现字母不够用的情况。对于每个格子，只有上、下、左、右四个边界，因此 $5$ 个字母就够用了。

读入数据需要 $\mathcal{O}(n^2)$，枚举可看成常数项（因为只有需要枚举 $5$ 个字母），一共 $T$ 组数据，总复杂度约为 $\mathcal{O}(T\times n^2)$。

$\texttt{AC}$ 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define maxn 15
int T, cnt;
const char word[] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };
char ch[maxn][maxn];

int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') { f = (ch == '-' ? -1 : f); ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
    return x * f;
}

char getch() {
    char ch = getchar();
    while (ch != '.' && !(ch >= 'A' && ch <= 'Z')) ch = getchar();
    return ch;
}

void empty() {
    for (int i = 0; i < maxn; i++)
        for (int j = 0; j < maxn; j++) ch[i][j] = '.';
}

bool check(int i, int j, int k) {
    if (ch[i - 1][j] == word[k]) return false;
    if (ch[i][j - 1] == word[k]) return false;
    if (ch[i + 1][j] == word[k]) return false;
    if (ch[i][j + 1] == word[k]) return false;
    return true;
}

signed main() {
    //for (int i = 'A'; i <= 'Z'; i++) cout << "\'" << char(i) << "\'" << ","; 
    cin >> T;
    while (T--) {
        int n = read();
        empty();
        cout << "Case " << ++cnt << ":" << endl;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++) ch[i][j] = getch();
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (ch[i][j] != '.') { cout << ch[i][j]; continue; }
                for (int k = 0; k < 5; k++) 
                    if (ch[i][j] == '.' && check(i, j, k)) { ch[i][j] = word[k]; cout << word[k]; break; }
            }
            cout << endl;
        }
    }
    return 0;
}

```


---

## 作者：zmza (赞：0)

### 这题是暴力。

这题的样例只有AB两个字母，但是应该把所有大写字母都枚举一遍。我是一个一个的填入方框，最后输出的。如果这个地方有字母，就不填

废话不多说，上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int read()//快读
{
	int i = 0, f = 1;
	char ch;
	for (ch = getchar(); (ch < '0' || ch > '9') && ch != '-'; ch = getchar());
	if (ch == '-')
	{
		f = -1;
		ch = getchar();
	}
	for (; ch >= '0' && ch <= '9'; ch = getchar())
	{
		i = (i << 3) + (i << 1) + (ch ^ 48);
	}
	return i * f;
}
void write(int a)//快写
{
	if (a < 0)
	{
		putchar('-');
		a = -a;
	}
	if (a == 0)
	{
		putchar('0');
		putchar(' ');
		return;
	}
	int sta[100] = {}, cnt = 0;
	while (a)
	{
		cnt++;
		sta[cnt] = a % 10;
		a /= 10;
	}
	while (cnt)
	{
		putchar(sta[cnt] + '0');
		cnt--;
	}
	putchar(' ');
}
int t;
int n;
char mp[15][15];
int zu;
const int dx[] = { -1,0,0,1 };//横方向
const int dy[] = { 0,-1,1,0 };//纵方向
void findans(int x, int y)//填入答案
{
	for (char i = 'A'; i <= 'Z'; i++)//从A 到 Z都枚举一遍，看看哪个字母可以填入
	{
		bool flag = 0;//可以为0，不可以为1
		for (int j = 0; j < 4; j++)//四个方向
		{
			int xx = x + dx[j];
			int yy = y + dy[j];
			if (xx < 0 || xx >= n || yy < 0 || yy >= n)//判断是否越界
			{
				continue;
			}
			if (i == mp[xx][yy])//只要有一个不满足，就不能填
			{
				flag = 1;
				break;
			}
		}
		if (flag == 0)//如果可以填，就填入，跳出
		{
			mp[x][y] = i;
			break;
		}
	}
}
int main()
{
	t = read();
	while (t--)//多组数据
	{
		zu++;
		n = read();
		for (int i = 0; i < n; i++)//输入
		{
			scanf("%s", mp[i]);
		}
		for (int i = 0; i < n; i++)//枚举每一个要填的地方
		{
			for (int j = 0; j < n; j++)
			{
				if (mp[i][j] == '.')//如果没有字母，就填进去
				{
					findans(i, j);
				}
			}
		}
		printf("Case %d:\n", zu);//输出
		for (int i = 0; i < n; i++)
		{
			printf("%s\n", mp[i]);
		}
	}
	return 0;
}

```
~~暴力出省一！！！~~

---

