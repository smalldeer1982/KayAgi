# RATAR - Ratar

## 题目描述

Unexpected problems with law enforcement have convinced Mirko to take up a less lucrative but less

## 样例 #1

### 输入

```
3
1 2 3
2 3 4
3 4 8```

### 输出

```
7```

# 题解

## 作者：Hoks (赞：0)

## 前言
不是很难的一题，感觉思维瓶颈还是在高复杂度上了。

每次碰到这种数据超小的题就会脑抽。
## 思路分析
首先看题面不难发现两个矩形会有一个交点，又因为 $n$ 很小，所以可以直接考虑枚举出这个交点。

接着考虑怎么找和相同的矩阵个数。

先预处理个矩阵的二维前缀和，接着还是从小数据入手，直接枚举是 $n^6$ 的，但是可以考虑空间换时间。

由于值域也比较小，所以整个矩阵的和的绝对值最大也只有 $2.5\times10^6$，考虑桶把复杂度硬压到 $n^4$。

但数组不能负数所以空间会变成 $5\times10^6$。

一看空间给的非常足直接随便跑了。

然后就可以轻松 AC 了。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=55,M=2500000,INF=0x3f3f3f3f3f3f3f3f;
int n,ans,s[N][N],f[(M<<1)+10];
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c=='P'||c=='S'||c=='L'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
inline int get(int x,int y,int xx,int yy){if(x>xx) swap(x,xx);if(y>yy) swap(y,yy);return s[xx][yy]+s[x-1][y-1]-s[xx][y-1]-s[x-1][yy];}
signed main()
{
    n=read();for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) s[i][j]=s[i][j-1]+s[i-1][j]+read()-s[i-1][j-1];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            for(int x=i+1;x<=n;x++) for(int y=j+1;y<=n;y++) f[get(i+1,j+1,x,y)+M]++;
            for(int x=1;x<=i;x++) for(int y=1;y<=j;y++) ans+=f[get(i,j,x,y)+M];
            for(int x=i+1;x<=n;x++) for(int y=j+1;y<=n;y++) f[get(i+1,j+1,x,y)+M]--;
            for(int x=1;x<=i;x++) for(int y=j+1;y<=n;y++) f[get(i,j+1,x,y)+M]++;
            for(int x=i+1;x<=n;x++) for(int y=1;y<=j;y++) ans+=f[get(i+1,j,x,y)+M];
            for(int x=1;x<=i;x++) for(int y=j+1;y<=n;y++) f[get(i,j+1,x,y)+M]--;
        }
    print(ans);flush();return 0;
}
```

---

## 作者：Velix (赞：0)

这一道题比较神奇，但只要思路上来了就不难了。

纯粹暴力：

枚举两个长方形左上角坐标+左下角坐标。

时间复杂度为$O(n^8)$

比暴力稍微好一点的方法：

**前缀和优化**+枚举两个长方形交点，在进行对两个长方形剩余坐标的枚举。

时间复杂度为$O(n^6)$

接下来让我们去思考正解：

首先，枚举交点不变，但考虑到我们计算时一个长方形时会增加当且仅当另一半有一个与自己相同的值。

这启发我们用**哈希表**存值。

这样时间复杂度就降为$O(n^4)$

当然有几点需要注意：

1 哈希表可能有负数；

2 由于计算时产生的数过大，memset可能会超时，所以要存储加过的位置，到时候删除时就用加过的位置删除。

## Code

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
int a[600][600],sum[600][600],b,c[2500050],d,e[50000],f;
int main()
{
	//freopen("farmer.in","r",stdin);
	//freopen("farmer.out","w",stdout);
	cin>>b;
	for(int i=1;i<=b;i++)
		for(int j=1;j<=b;j++)
		{
			cin>>a[i][j];
			sum[i][j]=sum[i-1][j]+sum[i][j-1]+a[i][j]-sum[i-1][j-1];
		}
	for(int i=1;i<b;i++)
		for(int j=1;j<b;j++)
		{
			for(int k=0;k<i;k++)
				for(int l=0;l<j;l++)
					++c[sum[i][j]+sum[k][l]-sum[i][l]-sum[k][j]+1250007],e[++f]=sum[i][j]+sum[k][l]-sum[i][l]-sum[k][j]+1250007;
			for(int k=i+1;k<=b;k++)
				for(int l=j+1;l<=b;l++)
					d+=c[sum[i][j]+sum[k][l]-sum[i][l]-sum[k][j]+1250007];
			while(f)c[e[f--]]=0;
			for(int k=0;k<i;k++)
				for(int l=j+1;l<=b;l++)
					++c[sum[i][l]+sum[k][j]-sum[k][l]-sum[i][j]+1250007],e[++f]=sum[i][l]+sum[k][j]-sum[k][l]-sum[i][j]+1250007;
			for(int k=i+1;k<=b;k++)
				for(int l=0;l<j;l++)
					d+=c[sum[i][l]+sum[k][j]-sum[k][l]-sum[i][j]+1250007];
			while(f)c[e[f--]]=0;
		}
	cout<<d;
}
```

~~[双倍经验](https://www.luogu.com.cn/problem/P2363)~~

---

## 作者：帅到报警 (赞：0)

### 【题意】
现在有一个 n * n 的矩阵，现在你要选两个子矩阵，满足：

1.两个子矩阵内的元素之和恰好相等。

2.两个子矩阵的边界（指的是矩形的边界，不是指边界的元素）恰好有一个公共点，并且不存在一个元素同时属于这两个子矩阵。

求符合条件的总方案数。

### 【分析】
经过一个上午的钻研。。。。我发现这就是一道暴力题！！！（只是优化一下）

首先我们要将这个矩阵的前缀和求出来。因为我们最后要找的两个矩阵和要相等。所以先求一遍和，然后枚举一遍公共点，求出对于某个左上角或右下角的和相同的矩阵。

### 【正解】
```cpp
#include <bits/stdc++.h>
#define M 101
#define N 2500010
using namespace std;

int n, ans;
int bio[N << 1];
int sum[M][M], a[M][M];

inline int read()
{
    char ch = getchar();
	int xx = 0, f = 1;
    while(ch > '9' || ch < '0'){
		if(ch == '-')	f = -1;
		ch = getchar();
	}
    while(ch >= '0' && ch <= '9'){
		xx = xx * 10 + ch - '0';
		ch = getchar();
	}
    return xx * f;
}

inline int val(int x1, int y1, int x2, int y2)
{
    if (x1)
        if(y1)
            return (sum[x2][y2] + sum[x1 - 1][y1 - 1] -
			sum[x1 - 1][y2] - sum[x2][y1 - 1]);
        else
            return (sum[x2][y2] - sum[x1 - 1][y2]);

    else
        if(y1)
            return (sum[x2][y2] - sum[x2][y1 - 1]);
        else
            return sum[x2][y2];
}

int main()
{
    n = read();
    for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
        	a[i][j] = read();
    sum[0][0] = a[0][0];
    for(int i = 1; i < n; i++)
		sum[i][0] = sum[i-1][0]+a[i][0],
		sum[0][i] = sum[0][i-1]+a[0][i];

	for(int i = 1; i < n; i++)
		for(int j = 1; j < n; j++)
			sum[i][j] = sum[i][j - 1] + sum[i - 1][j]
			- sum[i - 1][j - 1] + a[i][j];

    for(int i = 1; i < n; i++)
        for(int j = 1; j < n; j++)
        {
            for(int x = 0; x < i; x++)
                for(int y = 0; y < j; y++)
                    bio[val(x, y, i - 1, j - 1) + N]++;

            for(int x = i; x < n; x++)
                for(int y = j; y < n; y++)
                        ans += bio[val(i, j, x, y) + N];

            for(int x = 0; x < i; x++)
                for(int y = 0; y < j; y++)
                    bio[val(x, y, i - 1, j - 1) + N]--;

            for(int x = 0; x < i; x++)
                for(int y = j; y < n; y++)
                    bio[val(x, j, i - 1, y) + N]++;

            for(int x = i; x < n; x++)
                for(int y = 0; y < j; y++)
                    ans += bio[val(i, y, x, j - 1) + N];

            for(int x = 0; x < i; x++)
                for(int y = j; y < n; y++)
                    bio[val(x, j, i - 1, y) + N]--;
        }

    cout << ans;
    return 0;
}
```

---

## 作者：hicc0305 (赞：0)

枚举两个矩形的连接点，然后统计出左上的所有矩形的面积，用f[i]存面积为i的矩形有多少个。然后统计右下的所有矩形的面积的时候，每算出一个矩形面积j，答案就加上f[j]。然后左下和右上同理。

注意：清空时千万不要用memset，会超时的，然后我一开始是用map的，因为STL的劣根性，会T。。是的不管是用clear()还是一个一个删都会T的！但理论时间复杂度上$n^4*log_2n$是过得去的！！

那么代码：
```
#include<map>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#pragma GCC optimize (2)
#define int long long 
#define it int
using namespace std;
const int Max=2500*1000;
inline int read()
{
    int X=0,w=0; char c=0;
    while(c<'0'||c>'9') {w|=c=='-';c=getchar();}
    while(c>='0'&&c<='9') X=(X<<3)+(X<<1)+(c^48),c=getchar();
    return w?-X:X;
}
int n,ans=0;
int a[60][60],b[60][60];
int sum[60][60];
it f[Max*2];
int get(int x1,int y1,int x2,int y2)
{
    if(x1>x2) swap(x1,x2);
    if(y1>y2) swap(y1,y2);
    return sum[x2][y2]-sum[x1-1][y2]-sum[x2][y1-1]+sum[x1-1][y1-1];
}
signed main()
{
    n=read();
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            a[i][j]=read();
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            b[i][j]=b[i][j-1]+a[i][j];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            sum[i][j]=sum[i-1][j]+b[i][j];
    for(int a=1;a<=n;a++)
        for(int b=1;b<=n;b++)
        {
            for(int c=a+1;c<=n;c++)
                for(int d=b+1;d<=n;d++)
                    f[get(a+1,b+1,c,d)+Max]++;
            for(int c=1;c<=a;c++)
                for(int d=1;d<=b;d++)
                    ans+=f[get(a,b,c,d)+Max];
            for(int c=a+1;c<=n;c++)
                for(int d=b+1;d<=n;d++)
                    f[get(a+1,b+1,c,d)+Max]--;
            for(int c=1;c<=a;c++)
                for(int d=b+1;d<=n;d++)
                    f[get(a,b+1,c,d)+Max]++;
            for(int c=a+1;c<=n;c++)
                for(int d=1;d<=b;d++)
                    ans+=f[get(a+1,b,c,d)+Max];
            for(int c=1;c<=a;c++)
                for(int d=b+1;d<=n;d++)
                    f[get(a,b+1,c,d)+Max]--;
        }
    printf("%lld",ans);
    return 0;
}
```

---

