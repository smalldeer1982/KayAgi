# Cakeminator

## 题目描述

给你一个矩形蛋糕，表示为r×c网格。每个网格都可能有一个邪恶的草莓或者没有。例如，3×4蛋糕可能如下所示：【见图】

cakeminator将要吃蛋糕啦！每次他吃东西，他都会选择一个不含任何邪恶草莓的行或列，并且至少包含一个以前没有吃过的蛋糕，并吃掉那一行或列的所有蛋糕。他可能会吃多次。

请输出cakeminator可以吃的最大蛋糕数。

## 样例 #1

### 输入

```
3 4
S...
....
..S.
```

### 输出

```
8
```

# 题解

## 作者：Eason_AC (赞：2)

## Content
有一个 $r$ 行 $c$ 列的矩形蛋糕，由 $r\times c$ 块 $1\times 1$ 的蛋糕组成，其中有几块蛋糕上有一些草莓。你不喜欢吃草莓，又想吃得很爽，于是你决定每次吃不含任何草莓的一行或一列（前提是至少能吃到一块 $1\times 1$ 的蛋糕）。求你最多能够吃多少块蛋糕。

**数据范围：$2\leqslant r,c\leqslant 10$。**
## Solution
我们不妨从每个草莓的行和列入手，那么这个草莓所在的行和列都要被排除掉。剩下的没被排除掉的就是我们可以吃的那部分蛋糕。

设总共有 $a$ 排、$b$ 列可以能够吃蛋糕，那么通过容斥原理，我们可以发现多算了 $ab$ 块蛋糕，所以要减去。那么答案就是 $ac+br-ab$。
## Code
```cpp
#include <cstdio>
using namespace std;

int n, m, row[17], line[17], ansr, ansl;
char s[17][17];

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i)	row[i] = 1;
	for(int j = 1; j <= m; ++j)	line[j] = 1;
	for(int i = 1; i <= n; ++i)	{
		scanf("%s", s[i] + 1);
		for(int j = 1; j <= m; ++j)
			if(s[i][j] == 'S')	row[i] = line[j] = 0;
	}
	for(int i = 1; i <= n; ++i)	ansr += row[i];
	for(int j = 1; j <= m; ++j)	ansl += line[j];
	printf("%d", ansr * m + ansl * n - ansr * ansl);
}
```

---

## 作者：PeterBei (赞：1)

这题的正解应该是利用数论的知识直接计数并去重就行了，不过数据范围那么小（题目的 $\LaTeX$ 貌似炸了，实际上数据范围是 $2\le r,c\le 10$ ），所以可以使用暴力。

对行与列分别进行枚举，只要枚举到 $S$ 就跳过该列，对于初学者来说需要注意枚举列时 $i$ 与 $j$ 的范围等，具体为枚举列时需要外循环需要从 $1$ 到 $m$，内循环需要从 $1$ 到 $n$。同时由于枚举的方向发生变化，“枚举行”代码段中的 $i$ 和 $j$ 要全部颠倒才能用于“枚举列”中。可以通过阅读代码来理解上文的内容。

原代码：

```
#include<iostream>
#include<cstring>
using namespace std;

char a[100][100];
int cnt = 0;

int mian()
{
    int n = 0, m = 0;

    scanf("%d%d", &n, &m);

    for(int i = 1; i <= n; i++)
	{
		scanf("%s", a[i] + 1);
	}
	
	for(int i = 1; i <= n; i++)//枚举行
	{
		bool flag = 1;
		for(int j = 1; j <= m; j++)
		{
			if(a[i][j] == 'S')
			{
				flag = 0;
				break;
			}
		}
		if(flag)
		{
			for(int j = 1; j <= m; j++)
			{
				if(a[i][j] != '*')
				{
					cnt++;
					a[i][j] = '*';
				}
			}
		}
	}
	
	for(int i = 1; i <= m; i++)//枚举列（注意此处i和j的变化）
	{
		bool flag = 1;
		for(int j = 1; j <= n; j++)
		{
			if(a[j][i] == 'S')
			{
				flag = 0;
				break;
			}
		}
		if(flag)
		{
			for(int j = 1; j <= n; j++)
			{
				if(a[j][i] != '*')
				{
					cnt++;
					a[j][i] = '*';
				}
			}
		}
	}
	
	printf("%d", cnt);

    return 0;
}
```

---

## 作者：Sternenlicht (赞：0)

思路：

用 $rows_i$ 表示 cakeminator 是否能吃到 $i$ 行上的蛋糕，用 $line_j$ 表示 cakeminator 是否能吃到 $j$ 列上的蛋糕。

当 $rows_i$ 等于 $1$ 时，cakeminator 可以吃到 $i$ 行上的蛋糕。$line_j$ 同理。若 $s_{i,j}$ 为字符 $S$，将 $rows_i$ 和 $line_j$ 变为 $0$。

用 $a$ 记录有几行蛋糕能吃，$b$ 记录有几列蛋糕能吃，最终答案为 $a\times m+b\times n -a\times b$ （$a\times b$ 为算重的蛋糕数）。
```cpp
#include <bits/stdc++.h>
#define LL long long
#define endl '\n'
using namespace std;

const int N = 20;
int rows[N],line[N],n,m,a,b;
char s[N][N];
int main(){
	cin>>n>>m;
	//初始化rows数组和line数组
	for (int i=1;i<=n;i++)rows[i]=1;
	for (int i=1;i<=m;i++)line[i]=1;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++){
			cin>>s[i][j];
			if (s[i][j]=='S')rows[i]=line[j]=0;//标记为零
		}
	for (int i=1;i<=n;i++)a+=rows[i];//记录能吃蛋糕的行数
	for (int i=1;i<=m;i++)b+=line[i];//记录能吃蛋糕的列数
	write(a*m+b*n-a*b);
	return 0;
}

---

## 作者：封禁用户 (赞：0)

~~A 题果然大水题~~

这题就是个**暴力**。我们记录每行每列是否有邪恶的草莓，如果没有就吃。重点是要容斥去重。

部分核心代码：
```cpp
#define fo(i,n) for(int i=0;i<n;i++)

    int row[m+10]={0},col[n+10]={0};
    fo(i,m)
    {
    	cin>>s;
    	fo(j,n)
    		if(s[j]=='S')
    			row[i]=1,col[j]=1;    //标记草莓是否存在
    }
    ll countr1=0,countr2=0,countr3=0;
    fo(i,m)
    	if(row[i]==0)
    		countr1++;
    fo(i,n)
    	if(col[i]==0)
    		countr2++;
    ll cnt=0;
    cnt=(countr1*n)+(m*countr2)-(max(countr1,countr2)*min(countr1,countr2)); 	//容斥
```

~~无耻~~安利[博客](https://www.luogu.com.cn/blog/356740/)

完结撒花~

---

## 作者：Suuon_Kanderu (赞：0)

这题就是个 ~~模拟~~ 暴力啊。

用一个二维字符数组，每一块蛋糕都看看每行每列有没有邪恶的草莓，如果行中的每个都没有邪恶的草莓或列中没有，ans++;

再加些优化便大功告成了。

code：
```
#include<bits/stdc++.h>
using namespace std;
int main()
{
     int r,c,ans=0,flag;//flag用来存是否有草莓
     char a[11][11];
     cin>>r>>c;
     for(int i=1;i<=r;i++)
        for(int j=1;j<=c;j++)
		cin>>a[i][j];//输入不说了
         for(int i=1;i<=r;i++)
        for(int j=1;j<=c;j++)
{
    	        if(a[i][j]=='S')continue;	//优化
    	        flag=1;
		for(int k=1;k<=r;k++)
        //看看同一列有没有草莓
		if(a[k][j]=='S')
		{
			flag=0;
			break;
		}
		if(flag==1)
		{
		 ans++;
	//	 cout<<i<<' '<<j<<endl;
		continue;//优化 
		}
        //如果flag没有等于1，也就是没有continue就这样做
			flag=1;
			for(int s=1;s<=c;s++)
			if(a[i][s]=='S')//判断同一行有没有草莓
			{
				flag=0;
				break;
			}
		if(flag==1)
		{
		 ans++;
		// cout<<i<<" "<<j<<endl;
		}
}   
   cout<<ans<<endl;
    return 0;
}
```
 


---

## 作者：七夜 (赞：0)

这道题只需要发现一个地方，也就是只要他的行或者列能走就能被吃，所以只需要用两个数组去记录行和列是否能走就完了。

代码也很简单，甚至连二维数组都不用

代码如下（注释在代码里）：

```
#include<bits/stdc++.h>//偷懒专用库 
inline int read() {
	char c = getchar(); int x = 0, f = 1;
	while(c < '0' || c > '9') {if(c == '-') f = -1; c = getchar();}
	while(c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
	return x * f;
}//这里是快读，可以忽略，也可以借鉴 
using namespace std;
int  r,c,b[1314],ans,d[1314];//r，c表示行和列，ans记录答案，b记录行能否走，d记录列能否走 
char a;//不需要开数组，只需要一个字符 
int main()
{
	r=read();
	c=read();//快读读入行和列 
	for(int i=1;i<=r;++i) 
	 for(int j=1;j<=c;++j)
	  {
	  	cin>>a;//读入字符 
	  	if(a=='S')//判断，如果是邪恶草莓表示这个草莓在的行和列不能走了 
	  	 {
	  	 	b[i]=1;
	  	 	d[j]=1;
		 }
	  }
	for(int i=1;i<=r;++i) 
	 for(int j=1;j<=c;++j)
	  {
	  	if(!b[i]||!d[j])
	  	 ans++;
	  }//循环找，只要行和列有一个能走，在表能吃掉，就让ans++； 
	cout<<ans;//输出 
	return 0;//完美落幕 
}
```


---

