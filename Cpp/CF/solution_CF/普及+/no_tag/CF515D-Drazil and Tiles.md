# Drazil and Tiles

## 题目描述

Drazil created a following problem about putting $ 1×2 $ tiles into an $ n×m $ grid:

"There is a grid with some cells that are empty and some cells that are occupied. You should use $ 1×2 $ tiles to cover all empty cells and no two tiles should cover each other. And you should print a solution about how to do it."

But Drazil doesn't like to write special checking program for this task. His friend, Varda advised him: "how about asking contestant only to print the solution when it exists and it is unique? Otherwise contestant may print 'Not unique' ".

Drazil found that the constraints for this task may be much larger than for the original task!

Can you solve this new problem?

Note that you should print 'Not unique' either when there exists no solution or when there exists several different solutions for the original task.

## 说明/提示

In the first case, there are indeed two solutions:

```plain
<>^
^*v
v<>
```

and

```plain
^<>
v*^
<>v
```

so the answer is "Not unique".

## 样例 #1

### 输入

```
3 3
...
.*.
...
```

### 输出

```
Not unique
```

## 样例 #2

### 输入

```
4 4
..**
*...
*.**
....
```

### 输出

```
<>**
*^<>
*v**
<><>```

## 样例 #3

### 输入

```
2 4
*..*
....
```

### 输出

```
*<>*
<><>```

## 样例 #4

### 输入

```
1 1
.
```

### 输出

```
Not unique
```

## 样例 #5

### 输入

```
1 1
*
```

### 输出

```
*
```

# 题解

## 作者：ZJMZJM (赞：4)

一道水题

每次将度数为1的点取出来构造一个多米诺，直到没有度数为1的点。

若此时黑色格子已经被完全覆盖，则找到唯一解，否则有多解。

证明： 
将多米诺覆盖的两个点用黑边相连，其余用白边相连，由于这是一个存在环的二分图，我们显然可以将黑边与白边交换颜色，得到另一种解。

code
```
#include<iostream>
#include<cstring>
#include<string>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<queue>//头文件
#define For(k,i,j) for(int k=i;k<=j;k++)//for循环简写
#pragma GCC optimize(4)//O4
#define MAXN 2005 //数组常数
using namespace std;
inline int read()
{
    char ch;
    int res=1;
    while((ch=getchar())<'0'||ch>'9') if(ch=='-') res=-1;
    res*=ch-48;
    while((ch=getchar())>='0'&&ch<='9')
        res=res*10+ch-48;
    return res;
}//快读
int n,m,cnt;
char s[MAXN],color[MAXN][MAXN],ans[MAXN][MAXN];
bool flag;
int d[MAXN][MAXN];
int sx[4]={1,-1,0,0}; 
int sy[4]={0,0,1,-1};
struct hp
{
	int x,y;
};
queue <hp> q;
int main()
{
	n=read(),m=read();
    For(i,1,n)
    {
        gets(s);
        For(j,1,m)
        {
            color[i][j]=s[j-1];
            if(color[i][j]=='*') 
				cnt++;
        }
    }
    if(cnt==n*m)
    {
        For(i,1,n)
        {
            For(j,1,m)
				printf("*");
            printf("\n");
        }
        return 0;
    }
    For(i,1,n)
    	For(j,1,m)
            if(color[i][j]=='.')//遍历找出节点度数为1的节点，度数表示节点周围'.'的个数
            {
                int du=0;
                For(k,0,3)
                {
                    int nowx=i+sx[k],nowy=j+sy[k];
                    if(nowx<=0||nowx>n||nowy<=0||nowy>m||color[nowx][nowy]!='.') 
						continue;
                    du++;
                }
                d[i][j]=du;
                if(d[i][j]==1) 
					q.push((hp){i,j});
            }
            else 
				ans[i][j]='*';
    while(1)//更新两点周围所有节点的度数，将度数为1的节点继续放入队列中
    {
        int i,j;
        if(!q.empty())
        {
            hp pt=q.front(); 
			q.pop();
            i=pt.x; 
			j=pt.y;
            if(color[i][j]=='*'||d[i][j]!=1) 
				continue;
            for (int k=0;k<4;++k)
            {
                int nowx=i+sx[k],nowy=j+sy[k];
                if(nowx<=0||nowx>n||nowy<=0||nowy>m) 
					continue;
                if(color[nowx][nowy]=='.')
                {
                    For(l,0,3)
                    {
                        int nxtx=nowx+sx[l],nxty=nowy+sy[l];
                        if (nxtx<=0||nxtx>n||nxty<=0||nxty>m||color[nxtx][nxty]=='*') 
							continue;
                        d[nxtx][nxty]--;
                        if(d[nxtx][nxty]==1) 
							q.push((hp){nxtx,nxty});
                    }
                    color[nowx][nowy]=color[i][j]='*';
                    d[nowx][nowy]=d[i][j]=0;
                    cnt+=2; 
					flag=false;
                    switch(k)
                    {
                        case 0:
                        {
                            ans[i][j]='^';
                            ans[nowx][nowy]='v';
                            break;
                        }
                        case 1:
                        {
                            ans[i][j]='v';
                            ans[nowx][nowy]='^';
                            break;
                        }
                        case 2:
                        {
                            ans[i][j]='<';
                            ans[nowx][nowy]='>';
                            break;
                        }
                    	case 3:
                        {
                            ans[i][j]='>';
                            ans[nowx][nowy]='<';
                            break;
                        }
                    }
                    break;
                }
            }
        }
        else break;
    }
    if(cnt==n*m)
    {
		For(i,1,n)
        {
            For(j,1,m) 
				printf("%c",ans[i][j]);
            printf("\n");
        }
    }
    else
        printf("Not unique\n");//判断并输出
    return 0;
}
```

---

## 作者：_edge_ (赞：1)

CF div2 的 D 题，难度其实不大。

如果说没有唯一方案的限制，这题目就变得非常困难了，要用状压 DP 或者插头 DP 做。

但是有了这个限制之后就变成非常简单，考虑将输入的数据搞成一张图，`.` 向上下左右 `.` 连边，然后你会发现，如果存在度数为 $1$ 的点，那么它必然和它所连的点是被同一个给覆盖掉的。

上面那个结论非常显然，因为如果不被覆盖掉，那么这个点肯定是到最后也不会被覆盖的。

那么我们考虑这样一个过程，将入度为 $1$ 的点和它连的点都给删掉，然后继续找是否有入度为 $1$ 的点。

你会发现这个过程可以 $O(n \times m)$ 做。

于是这道题目就做完了么？不，还有无解的情况。

如果说是无解的话，我们可以最后直接扫一遍是否都填上了。

否则的话，我们考虑有多解。

多解的情况下，肯定是不存在度数为 $1$ 的点，即存在一条环，这种情况下，不会影响上述过程。

最终我们只需要扫一遍是不是都填满就可以了。

代码：

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int INF=2005;
const int fx[]={0,0,1,-1};
const int fy[]={1,-1,0,0};
const char fz[]={'<','>','^','v'};
int n,m,in[INF][INF],aa[INF*INF][2],tot;
char ch[INF][INF];
signed main()
{
        ios::sync_with_stdio(false);
        cin>>n>>m;
        for (int i=1; i<=n; i++)
                for (int j=1; j<=m; j++)
                        cin>>ch[i][j];
        for (int i=1; i<=n; i++) {
                for (int j=1; j<=m; j++) {
                        if (ch[i][j]!='.') continue;
                        for (int k=0; k<4; k++) {
                                int gx=fx[k]+i,gy=fy[k]+j;
                                if (gx<1 || gy<1 || gx>n || gy>m) continue;
                                if (ch[gx][gy]!='.') continue;
                                in[i][j]++;
                        }
                        if (in[i][j]==1)
                                aa[++tot][0]=i,aa[tot][1]=j;
                }
        }
        // cout<<tot<<"\n";
        for (int i=1; i<=tot; i++) {
                int xx=aa[i][0],yy=aa[i][1];
                // cout<<xx<<" "<<yy<<"\n";
                in[xx][yy]=0;
                for (int k=0; k<4; k++) {
                        int gx=fx[k]+xx,gy=fy[k]+yy;
                        if (gx<1 || gy<1 || gx>n || gy>m) continue;
                        if (ch[gx][gy]!='.') continue;
                        // cout<<xx<<" "<<yy<<" "<<gx<<" "<<gy<<" "<<ch[gx][gy]<<"\n";
                        in[gx][gy]--;
                        if (k==0 || k==1) ch[xx][yy]=fz[k],ch[gx][gy]=fz[1-k];
                        if (k==2 || k==3) ch[xx][yy]=fz[k],ch[gx][gy]=fz[(k==2 ? 3 : 2)];
                        xx=gx,yy=gy;
                        break;
                }
                for (int k=0; k<4; k++) {
                        int gx=fx[k]+xx,gy=fy[k]+yy;
                        if (gx<1 || gy<1 || gx>n || gy>m) continue;
                        if (ch[gx][gy]!='.') continue;
                        in[gx][gy]--;
                        if (in[gx][gy]==1)
                                aa[++tot][0]=gx,aa[tot][1]=gy;
                }
                // for (int i=1; i<=n; i++) {
                //         for (int j=1; j<=m; j++)
                //                 cout<<ch[i][j];
                //         cout<<"\n";
                // }
        }
        int fl=1;
        for (int i=1; i<=n; i++)
                for (int j=1; j<=m; j++)
                        if (ch[i][j]!='.');
                        else fl=0;
        if (!fl) cout<<"Not unique\n";
        else {
                for (int i=1; i<=n; i++) {
                        for (int j=1; j<=m; j++)
                                cout<<ch[i][j];
                        cout<<"\n";
                }
        }
        return 0;
}

```

如有问题还请指出。

---

## 作者：distjr_ (赞：0)

作为绿题，本题还是比较水的。

每次从所有点中找到周围只有一个点的点，将这两个点构成一个 $1 \times 2$ 的矩阵。重复执行直到没有符合条件的点。如果此时已经不存在 `.` 了，就证明有唯一解并将其输出，否则就有多组解或无解，输出 `Not unique` 即可。

这个思路的证明是比较显然的，此处不过多赘述。

代码如下：

```cpp
#include <cstdio>
#include <algorithm>
#include <queue>
#define MAXN 2010
// #define DEBUG
using namespace std;

typedef pair<int, int> pii;
int n, m, degree[MAXN][MAXN], d[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
char Map[MAXN][MAXN];
queue<pii> stack;	//原本想用栈的，后来发现用不了，就改成这个样子了qwq

int main()
{
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            [](char &c)
            {c = ''; while (c != '.' && c != '*') c = getchar(); }(Map[i][j]);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if ((degree[i][j] = ((Map[i + 1][j] == '.') + (Map[i - 1][j] == '.') + (Map[i][j + 1] == '.') + (Map[i][j - 1] == '.'))) == 1 && Map[i][j] == '.')
                stack.push({i, j});
#ifdef DEBUG	//调试代码
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
            printf("%d", degree[i][j]);
        printf("\n");
    }
#endif
    while (!stack.empty())
    {
        pii now = stack.front();
        stack.pop();
#ifdef DEBUG	//调试代码
        printf("%d %d\n", now.first, now.second);
#endif
        for (int i = 0; i < 4; ++i)
        {
            pii nxt = make_pair(now.first + d[i][0], now.second + d[i][1]);
            if (Map[nxt.first][nxt.second] == '.')
            {
                if (i == 0)
                    Map[now.first][now.second] = '^', Map[nxt.first][nxt.second] = 'v';
                else if (i == 1)
                    Map[now.first][now.second] = 'v', Map[nxt.first][nxt.second] = '^';
                else if (i == 2)
                    Map[now.first][now.second] = '<', Map[nxt.first][nxt.second] = '>';
                else if (i == 3)
                    Map[now.first][now.second] = '>', Map[nxt.first][nxt.second] = '<';
                for (int j = 0; j < 4; j++)
                {
                    pii nnxt = make_pair(nxt.first + d[j][0], nxt.second + d[j][1]);	//只用考虑nxt四周的点，now周围的不用管，因为now周围已经没有可用的点了
                    if (Map[nnxt.first][nnxt.second] == '.' && (--degree[nnxt.first][nnxt.second]) == 1)
                        stack.push(nnxt);
                }
                break;
            }
        }
    }
    for (int i = 1; i <= n; ++i)	//如果还有未标记的点，证明有多组解或无解
        for (int j = 1; j <= m; ++j)
            if (Map[i][j] == '.')
            {
                printf("Not unique\n");
                return 0;
            }
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
            putchar(Map[i][j]);
        printf("\n");
    }
    int qwq = 0;
    return qwq;
}
```

以上。如有问题烦请指出，谢谢。

---

## 作者：Error_Eric (赞：0)

### 前言

大家提交的时候一定要注意大小写和标点符号啊...

### 正文

首先，不难发现四周只有一个空地的空地一定是方案唯一的。于是这些空地填好了。

然后，这些空地填好之后，又出现了若干个周围只有一个空地的空地。于是这些空地也填好了。

接着，套娃。

最后我们发现：

- 1 所有空地都填满了： 显然这意味着只有一个答案。

- 2 不是所有空地都填满了：这意味着不只一个答案。

2的证明：

如果没有解，输出 ``not unique``。

如果有一个解：

对于任意一个这样的连通块：把行数+列数之和为偶数的涂成白色，行数+列数之和为奇数的涂成黑色，（国际象棋棋盘）得出存在一个环，使得其中的元素为``（黑白）（黑白）（黑白）……（黑白）``。

那么另一个解就是 ``黑）（白黑）（白黑）……（白黑）（白`` 。

举个例子：

![](https://cdn.luogu.com.cn/upload/image_hosting/fkobie97.png)

(左上角对应1，左下角对应2的第一种情况，右上角对应2的第二种情况，右下角是综合情况)。

那么代码就非常简单了。

### Code

马蜂清奇,以至于只用了53行。

```cpp
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<stack>
using namespace std;
#define il inline 
#define rei register int
#define ll long long
int n,m;
#define ar ((c[i+1][j]=='.')+(c[i-1][j]=='.')+(c[i][j+1]=='.')+(c[i][j-1]=='.'))
#define pii pair<int,int>
#define mp make_pair
#define nx nex.first
#define ny nex.second
#define Each() for(rei i=1;i<=n;i++)for(rei j=1;j<=m;j++)//快乐压行宏定义
il void readln(int &I){//快读不解释
    I=0;char C=getchar();
    while(!isdigit(C))C=getchar();
    while( isdigit(C))I=I*10+C-'0',C=getchar();
}
il void readch(char&C){C='#';while(C!='.' and C!='*')C=getchar();}//读入一个‘.’或者‘*’。
char c[2005][2005];int ds[2005][2005];//存储地图，存储每个‘.’旁边有几个‘.’。
stack<pii >s;//我也不知道是什么，可以理解为深搜广搜结合，用于存储节点。
const pii dir[]={mp(0,0),mp(1,0),mp(-1,0),mp(0,1),mp(0,-1)};//四个方向
pii operator+(pii pa,pii pb){return mp(pa.first+pb.first,pa.second+pb.second);}//便于遍历周围四个节点
int main(){
	readln(n),readln(m);
    Each()readch(c[i][j]);//读入不解释。
    Each()if((ds[i][j]=ar)==1 and c[i][j]=='.')s.push(mp(i,j));//初始化ds数组，将‘.’入栈
    while(!s.empty()){//我也不知道是什么。
        pii now=s.top();s.pop();//取出顶端元素。
        for(rei k=1;k<=4;k++){
            pii nex=now+dir[k];//向四个方向延伸。
            if(c[nx][ny]=='.'){//找到唯一的一个‘.’。
                switch(k){
                case 1:c[now.first][now.second]='^',c[nx][ny]='v';break;//放进答案里面。
                case 2:c[now.first][now.second]='v',c[nx][ny]='^';break;
                case 3:c[now.first][now.second]='<',c[nx][ny]='>';break;
                case 4:c[now.first][now.second]='>',c[nx][ny]='<';break;
                }
                for(rei kk=1;kk<=4;kk++){
                    pii p1=nex+dir[kk],p2=now+dir[kk];
                    if(c[p1.first][p1.second]=='.' and --ds[p1.first][p1.second]==1)s.push(p1);//套娃。
                    if(c[p2.first][p2.second]=='.' and --ds[p2.first][p2.second]==1)s.push(p2);
                }
                break;
            }
        }
    }
    Each()if(c[i][j]=='.')return puts("Not unique"),0;//如果有没有套进去的,not unique。
    for(rei i=1;i<=n;i++)c[i][m+1]=10;
    Each()putchar(c[i][j]);//不然，输出答案。
}
```

---

