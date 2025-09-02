# Yet Another Crosses Problem

## 题目描述

你将会得到若干个 $n$ 行 $m$ 列的矩阵。每一格都被涂成了黑色或白色

若矩阵中的某行，某列都为黑色，则这一行与一列构成了一个十字架

如下所示，这些矩阵都包含了至少一个十字架

![qaq](https://cdn.luogu.org/upload/vjudge_pic/CF1194B/88ab70f483371a989bc0a7f4c7494f932bf59239.png)

而下列矩阵则不包含十字架

![233](https://cdn.luogu.org/upload/vjudge_pic/CF1194B/a3af39e3883913d8cb154cdd61325299208144f4.png)

你的任务是，共有 $q$ 次询问。对于每一次询问，给出一个矩阵，求出至少还要将多少个白色格子涂成黑色，才能使这个矩阵包含至少一个十字架

## 样例 #1

### 输入

```
9
5 5
..*..
..*..
*****
..*..
..*..
3 4
****
.*..
.*..
4 3
***
*..
*..
*..
5 5
*****
*.*.*
*****
..*.*
..***
1 4
****
5 5
.....
..*..
.***.
..*..
.....
5 3
...
.*.
.*.
***
.*.
3 3
.*.
*.*
.*.
4 4
*.**
....
*.**
*.**
```

### 输出

```
0
0
0
0
0
4
1
1
2
```

# 题解

## 作者：zhanghanbin (赞：3)

[$ \colorbox{#dd514c}{\color{white}{\text{原文链接}}}$](https://codeforces.com/blog/entry/68405)
$ \colorbox{#3498db}{\color{white}{\text{预览原文}}} $ 

$\texttt{ps:链接进去自己找[手动滑稽]}$

```
Let's consider each cell as a center of a cross and take the fastest one to paint. Calculating each time naively will take ????(????????(????+????)) overall, which is too slow. 

Overall complexity: ????(????????) per query.
/*...详情请查看原文...*/
```

### 正（搬）文（运）开始

**你**要让要涂的格子最少，那么肯定选哪一行那一列空白最少的。

**你**把每行每列是不是白色格子记作 $s_{i,j}$，然后循环判断，然后你 TAT(TLE+MLE) 了。PS:应该先CE才对。

想要暴力计算的**你**会让复杂度达到 $O(nm(n+m))$ （原文是这么说的[滑稽](https://binbin.blog.luogu.org/solution-cf1194b)）

但是~~智商250~~的**你**却想到了每行每列有几个白色格子可以用 $a_{i} $ 和 $ b_{j} $ 表示。

但是**你**最后不会统计$\text{Ans}$，所以你????了，**全剧终**

假的。

要知道 $?$ 等于几，首先要知道你会重复算一个格子。

来看一张图

![](https://cdn.luogu.com.cn/upload/image_hosting/bf9sy9gx.png)

中间有重叠的地方，而且是仅当有白色的时候才会需要减掉哪个 $1$。

所以**你**会做了，**全剧终**

真的。

才怪。

所以**你**得到了一条结论，它叫 $\text{a[i] + b[j] - (s[i][j] == '.')}$。

最后的最后

[$ \colorbox{#dd514c}{\color{white}{\texttt{\tiny 放代码啦(Press to see the code)}}}$](https://binbin.blog.luogu.org/)

lalalala没了，还愁啥？

真没了。

## 全剧终

---

## 作者：RE_Prince (赞：2)

# CF1194B Yet Another Crosses Problem 

[link](https://www.luogu.com.cn/problem/CF1194B)

## Sol

题目大意：给出一个有黑有白的方格，问最少要把几个白色格子染成黑色才能让至少一行**和**一列染黑。


第一个想法是存储起来每行和每列的空白个数，然后暴力枚举要染黑哪行和哪列。但是，这种想法有一个漏洞。比如说在第 $8$ 个样例中，这种算法会算成 $2$，因为中间一行一列的空会算两遍，因此，如果选出的行列的交界处是白色，还要减去 $1$。但是，因为是多测，我习惯性地将数组整体清空。

完全按上面思路写出代码后，会发现时间稳稳地起飞了，甚至没跑过第四个测试点。计算一下复杂度，会发现整体复杂度是 $O(nm)$，仿佛没啥问题。

那么瓶颈在哪里呢？

我用的是数组，习惯每组数据都整体 `memset` 一遍，这样清空非常费时间。但把数组定义在主函数里面，就会爆栈（我不太会部分清空）。那么这里，就可以用 `vector`。`vector` 可以动态分配空间，可以使用 `vector<int> vec(n)` 来定义一个长度为 $n$ 的动态数组。将所有数组都替换成 `vector` 后，时间就马上降下来了。


给下代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,i,j,k;
char ch;
signed main()
{
//	freopen("test.txt","w",stdout);
	int t;
	cin>>t;
	while(t--)
	{
		cin>>n>>m;
		vector<string> a(n);//相当于char a[n][n]，但是a[n][n]会报错
		vector<int> col(m),line(n);//用vector，时间会少很多
		for(i=0;i<n;i++) cin>>a[i];
		for(i=0;i<n;i++)
			for(j=0;j<m;j++)
				line[i]+=(a[i][j]=='.'),
				col[j]+=(a[i][j]=='.');//统计每行每列的空白
		int ans=1e9;
		for(i=0;i<n;i++)
			for(j=0;j<m;j++)
				ans=min(ans,col[j]+line[i]-(a[i][j]=='.'));//计算需要染多少次
		cout<<ans<<endl;
	} 
	return 0;  
}
```

---

## 作者：Llf0703 (赞：2)

## 题意

要求把一些格子染黑，使得图上有一个黑色的十字形。求最少需要染色的个数。

多组数据，$1\le N,M\le 5\times 10^4$，$N\times M\le 4\times 10^5$ 。

## 题解

显然贪心，找到已经涂黑的点最多的行和列，把剩下的涂黑即可。

但如果选取的行和列交界的那一格是白色，那么就重复统计了一次，答案就能少一个。

所以用两个 `vector` 记录所有选取的行和列，如果交界是白色就 `ans--` 并退出。

这题输入还需要处理一下，用一个线性的字符数组记录整张图，用 $f(i,j)$ 表示 $(i,j)$ 对应在图中的位置。

```cpp
#include<bits/stdc++.h>

using namespace std;

inline int read()
{
    char ch=getchar();
    int f=1,x=0;
    while (ch<'0' || ch>'9')
    {
        if (ch=='-') f=-1;
        ch=getchar();
    }
    while (ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return f*x;
}

int t,n,m;
char s[400005],ch[50005];

inline int f(int x,int y) { return m*(x-1)+y; }

signed main()
{
    t=read();
    while (t--)
    {
        n=read(); m=read();
        for (int i=1;i<=n;i++)
        {
            scanf("%s",ch+1);
            for (int j=1;j<=m;j++) s[f(i,j)]=ch[j];
        }
        int mx=0,ans=0; vector<int> mxi;
        for (int i=1;i<=n;i++)
        {
            int cnt=0;
            for (int j=1;j<=m;j++) cnt+=s[f(i,j)]=='*';
            if (cnt>mx) mx=cnt,mxi.clear(),mxi.emplace_back(i);
            else if (cnt==mx) mxi.emplace_back(i);
        }
        ans+=m-mx;
        mx=0; vector<int> mxj;
        for (int j=1;j<=m;j++)
        {
            int cnt=0;
            for (int i=1;i<=n;i++) cnt+=s[f(i,j)]=='*';
            if (cnt>mx) mx=cnt,mxj.clear(),mxj.emplace_back(j);
            else if (cnt==mx) mxj.emplace_back(j);
        }
        ans+=n-mx;
        for (auto i:mxi) for (auto j:mxj) if (s[f(i,j)]!='*') {ans--; goto output;}
        output:printf("%d\n",ans);
    }
    return 0;
}
```

---

## 作者：逃课小姐MS (赞：1)

### 活生生的水题

就是说 则个题目不可以用二维数组来存图 因为存不下。

但是会发现 $n*m$ 不超过400000 所以我们用一位数组来存图，就是$i*m+j$ 一样的方式。

然后我们分别记录最优的一行中有多少空格，最优的一列中有多少空格，最后如果他们相交的那个格子是一个需要填上的格子，那么把答案-1，因为那样会多算一个。

代码如下，就是一个简单模拟。

```
#include<bits/stdc++.h>
using namespace std;
int c[50010],r[50010];
bool mage[400010];
int a1,p1,a2,p2;
int main(){
    ios::sync_with_stdio(false);
    int t;
    cin>>t;
    while(t--){
        int n,m;
        cin>>n>>m;
        for(int i=1;i<=n;i++){
            c[i]=0;
            for(int j=1;j<=m;j++){
                char ch;
                cin>>ch;
                if(ch=='.'){
                    c[i]++,mage[i*m+j]=1;
                }
                else mage[i*m+j]=0;
            }
        }
        for(int i=1;i<=m;i++){
            r[i]=0;
            for(int j=1;j<=n;j++){
                r[i]+=mage[j*m+i];
            }
        }
        int ans=2147483647;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++){
                ans=min(ans,r[j]+c[i]-mage[i*m+j]);
            }
        cout<<ans<<endl;
    }
}
```

---

## 作者：zsh_haha (赞：0)

### 解题思路

题目还是很简单的，主要就是如何存储字符二维数组。

首先，就是刚刚提到的如何存储字符二维数组。

如果我们的字符数组真的开 `char a[50001][50001]` 那么你就会因为数组开得太大而编译错误。

那么到底如何存储字符二维数组呢？我们在题目中发现 $n\times m\le4\times10^5$，所以我们这里需要更灵活的分配空间，这里使用 `string` 类型就是不二之选，因为这里只用开 `string a[50001]`，所以不会编译错误，而 `string` 会根据使用情况分配内存，所以不用担心空间问题。

---

现在就是解题过程了，我们可以把每一行，每一列的 `.` 的个数求出来。

然后遍历每一个位置，若以 $(i,j)$ 为十字架中心，那么需要填的数量就为当前行 `.` 的个数 $+$ 当前列 `.` 的个数，若 $(i,j)$ 位置为 `.`，则需减去一个重复计算的 `.`，最后在遍历完成后取答案最小值。

### AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
string a[50001];
int aa[50001];//a[i] 表示第 i 行 '.' 的个数 
int bb[50001];//b[i] 表示第 i 列 '.' 的个数 
int main(){
	int t;
	cin>>t;
	while(t--){
		int n,m;
		cin>>n>>m;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		for(int i=1;i<=n;i++){
			int sum=0;
			for(int j=0;j<m;j++){
				if(a[i][j]=='.'){
					sum++;
				}
			}
			aa[i]=sum;
		}
		for(int i=0;i<m;i++){
			int sum=0;
			for(int j=1;j<=n;j++){
				if(a[j][i]=='.'){
					sum++;
				}
			}
			bb[i]=sum;
		}
		int minn=500005;
		for(int i=1;i<=n;i++){//循环遍历每一个位置 
			for(int j=0;j<m;j++){
				minn=min(minn,aa[i]+bb[j]-(a[i][j]=='*'?0:1));
				//把当前行当前列点的个数相加，若当前位置是 '.'，则减去重叠的 '.' 
			}
		} 
		cout<<minn<<endl;
	}
    return 0;
}
```

---

## 作者：floatery (赞：0)

题意：“有趣图”为一个至少有一个“十字架”的n行m列的黑白方格图。定义一个数对$x$,$y$，其中$1 \leq x \leq n,1 \leq y \leq m$，如果所有第x行的方格和第y列的方格全是黑色的，则这些方格被称为“十字架”。你有一个画笔和黑墨水，可以让图变得“有趣”。每分钟你可以选择一个方格涂黑，请求出让图变得“有趣”需要的最短时间。

思路：对于任意图，可以求出来含有黑色方格最多的行和含有黑色方格最多的列，如果它们含有的黑色方格数目就是$n$和$m$，那么这张图上一定有十字架，反之亦然。所以，没有十字架的图中，n+m-(含有黑色方格最多的行的黑色方格数目加上含有黑色方格最多的列的黑色方格数目再减去交叉点)就是需要的时间。

由于有毒的数据范围，故只能用一个一维数组当二维数组（当然也可以用`vector`）

```cpp
#include <stdio.h>
#include <iostream>
#include <string.h>
using namespace std;
char str[400001];
int xx[50001],yy[50001];
int main()
{
	int q;
	scanf("%d",&q);
	while(q--)
	{
		int n,m,mx=0,my=0,mxy=0;
		scanf("%d%d",&n,&m);
		memset(str,0,sizeof(str));
		memset(xx,0,sizeof(xx));
		memset(yy,0,sizeof(yy));
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				cin>>str[(i-1)*m+j];
			}
		}
		for(int i=1;i<=n;i++)
		{
			int x=0;
			for(int j=1;j<=m;j++)
			{
				if(str[(i-1)*m+j]=='*') x++;
			}
			//printf("%d\n",x);
			xx[i]=x;
			if(x>mx) mx=x;
		}
		for(int j=1;j<=m;j++)
		{
			int y=0;
			for(int i=1;i<=n;i++)
			{
				if(str[(i-1)*m+j]=='*') y++;
			}
			yy[j]=y;
			if(y>my) my=y;
		}
		int xy=0;
		for(int i=1;i<=n;i++)
		{
			if(xx[i]==mx)
			{
				for(int j=1;j<=m;j++)
				{
					if(yy[j]==my)
					{
						if(str[(i-1)*m+j]=='*')
						{
							//printf("%d %d\n",i,j);
							if(mx+my-1>mxy) mxy=mx+my-1;
						}
						else
						{
							//printf("%d %d\n",i,j);
							mxy=mx+my;
						}
					}
				}
			}
		}
		//printf("%d %d\n",mx,my);
		printf("%d\n",n+m-1-mxy);
	}
	return 0;
}
```

---

