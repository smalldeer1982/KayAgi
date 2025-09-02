# Gokigen Naname谜题 Gokigen Naname

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=78&page=show_problem&problem=2741

[PDF](https://uva.onlinejudge.org/external/116/p11694.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11694/2821a2ff4c94a298109d6239ae84f49273f2c058.png)

## 样例 #1

### 输入

```
3
1.1.
...0
.3..
..2.
5
.21...
..33.0
......
..33..
0..33.
....11```

### 输出

```
\//
\\\
/\/
/\\//
//\\\
\\\//
\/\\/
///\\```

# 题解

## 作者：zimujun (赞：4)

### 写在前面

请先确保您已学会解这道题之后再来阅读该题解。这篇题解将只提供一个优化。

这个优化甚至不能算是剪枝，而且理论上并没有改变最差情况下的复杂度。

但是在随机数据下它跑得飞快，效果：

![](https://cdn.luogu.com.cn/upload/image_hosting/jumoc28z.png)

### 优化思路

考虑到有些点要求连接的是 $4$ 或者 $0$。那么这些点周围的四个答案就是确定的。

确定完这些点的答案之后，就又有一部分点的答案会被确定，举例：

在 $(1,1)$ 位置有一个 $0$，在 $(2, 2)$ 位置有一个 $3$。那么第一步的时候，红色直线这一个就是必须这样填写的。

那么下一步，显然 $(2, 2)$ 周围就只有一种填写方式了。（如蓝色直线）

![](https://cdn.luogu.com.cn/upload/image_hosting/h72yfc41.png)

这样，每次将当前可以填写的答案填写上，直到没有确定的答案为止。

怎么实现呢？

- 统计每个节点还需要连接的边数和剩余空位数。

- 如果还需要的边数为 $0$。那么把剩余空位上的边全部按照不连接当前节点填写。

- 如果剩余的空位和需要填写的边数相等，那么把剩下的空位上全部填上与当前节点连接的边。

重复执行此过程，直到不能扩展。

这样不断扩展最差情况下的复杂度也仅仅是 $\mathcal O(n^4)$，在 $n = 7$ 的范围下几乎没有时间开销。

然后搜剩下的边。

在数据随机的情况下，这样预先处理一遍，几乎可以填满大半张图。起到很明显的优化效果。

但是仍然可以卡到和朴素搜索一个级别。

### Code

```cpp

char m[10][10];
bool p[10][10];
bool b[10][10];
char a[10][10];
int req[10][10];
int lst[10][10];

inline void xg(int x, int y) {//斜杠
	if(x < 1 || x > n || y < 1 || y > n) return;
	p[x][y] = 1;
	a[x][y] = '/';
	lst[x][y]--;
	lst[x + 1][y + 1]--;
	req[x + 1][y]--; lst[x + 1][y]--;
	req[x][y + 1]--; lst[x][y + 1]--; 
}

inline void fxg(int x, int y) {//反斜杠
	if(x < 1 || x > n || y < 1 || y > n) return;
	p[x][y] = 1;
	a[x][y] = '\\';
	lst[x + 1][y]--;
	lst[x][y + 1]--;
	req[x][y]--; lst[x][y]--;
	req[x + 1][y + 1]--; lst[x + 1][y + 1]--;
}

bool setup() {
	bool flag = 0;
	for(register int i = 1; i <= n + 1; ++i) {
		for(register int j = 1; j <= n + 1; ++j) {
			if(b[i][j]) continue;
			if(req[i][j] == 0) {
				if(!p[i - 1][j - 1]) xg(i - 1, j - 1);
				if(!p[i - 1][j]) fxg(i - 1, j);
				if(!p[i][j - 1]) fxg(i, j - 1);
				if(!p[i][j]) xg(i, j);
				flag = b[i][j] = 1;
			}
			else if(req[i][j] == lst[i][j]) {
				if(!p[i - 1][j - 1]) fxg(i - 1, j - 1);
				if(!p[i - 1][j]) xg(i - 1, j);
				if(!p[i][j - 1]) xg(i, j - 1);
				if(!p[i][j]) fxg(i, j);
				flag = b[i][j] = 1;
			}
		}
	}
	return flag;
}
```

主函数部分（多测所使用的“子主函数”）：

```cpp
void Main() {
	/*something here...*/
  while(setup());
  /*something here...*/
}
```

---

## 作者：Drifting (赞：4)

## 这是一道~~丧心病狂的~~搜索题

调试过程真的让人绝望qaq

**更正一下样例，样例的第一行应该有一个整数T，表示接下来有T组数据。**
```cpp
2
3
1.1.
...0
.3..
..2.
5
.21...
..33.0
......
..33..
0..33.
....11
```

 _不知为何本题只有一个测试点_ 

------------
我们称每个棋盘上**格线**的交点为节点。

我们的基本思路是使用DFS，按从上到下，从左到右的顺序遍历每一个棋盘的节点。

使用并查集查询每个斜的父亲节点，如果有四个节点的父亲是同一个，则说明在同一个棋盘中出现了环。为了处理并查集方便，将棋盘左上角的节点定为1号，然后从左向右从上到下依次标号。

细节已经在注释中写得很详细了。

------------

```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int dx[4] = {0, 0, 1, 1};
const int dy[4] = {0, 1, 0, 1};
int n;
bool flag;
bool ans[101][101];
int fa[10001], m[101][101], cur[101][101], lim[101][101];
// m存原始棋盘，-1为空格;
// lim存一个格子最多能到多少（limit）;
// ans存最终应当输出‘/’还是‘\’;
// cur表示当前已经连接了多少;
inline int read()
{
    char c = getchar();
    while (!(c == '.' || (c >= '0' && c <= '4')))
        c = getchar();
    if (c == '.')
        return -1;
    else
        return c - '0';
}
inline bool board(int x, int y)
{
    if (m[x][y] == -1)
        return 1;
    if (cur[x][y] <= m[x][y] && cur[x][y] + lim[x][y] >= m[x][y])
        return 1;
    //如果当前这个点连接的对角线还不到目标数目，那么继续;
    //如果超过了可连接数lim，那么就停止;
    return 0;
}
int find(int x)
{
    if (!fa[x])
        return x;
    return find(fa[x]);
}
void dfs(int x, int y)
{
    if (y == n)
        y = 1, x++;
    if (x == n)
    {
        flag = 1;
        return;
    }
    int t1, t2, pd = 0;
    // 以下是加左上到右下方向的斜（‘\’）
    ++cur[x][y], ++cur[x + 1][y + 1];
    //左上点和右下点计数 + 1；
    --lim[x][y], --lim[x + 1][y], --lim[x][y + 1], --lim[x + 1][y + 1];
    //不允许有斜交叉，所以 --lim[][];
    for (int i = 0; i < 4; i++)
        if (!board(x + dx[i], y + dy[i]))
        {
            pd = 1;
            break;
        }
    if (!pd)
    {
        t1 = find((x - 1) * n + y), t2 = find(x * n + y + 1);
        // (x - 1) * n + y 为右上节点在整个棋盘中的编号。编号从棋盘左上角第一个开始。
        // x * n + y + 1为右下节点的编号;
        // 因为是从左到右，从上到下进行搜索，所以当前状态的左边的节点肯定不会有环。
        if (t1 != t2) // 有没有环，只要看其父亲是否是一个即可。
        {
            ans[x][y] = 1; //钦定1为‘\’;
            fa[t1] = t2;
            dfs(x, y + 1);
            if (flag)
                return;
            fa[t1] = 0; //回溯原本的并查集状态;
        }
    }
    --cur[x][y], --cur[x + 1][y + 1]; //恢复原状态；
    // 以下是加右上到左下方向的斜（‘/’）
    ++cur[x + 1][y], ++cur[x][y + 1];
    pd = 0;
    //右上点和左下点计数 + 1；
    for (int i = 0; i < 4; i++)
        if (!board(x + dx[i], y + dy[i]))
        {
            pd = 1;
            break;
        }
    if (!pd)
    {
        t1 = find(x * n + y), t2 = find((x - 1) * n + y + 1);
        // (x - 1) * n + y + 1 右上点,
        // x * n + y 左下点;
        if (t1 != t2)
        {
            ans[x][y] = 0; //钦定0为‘/’;
            fa[t1] = t2;
            dfs(x, y + 1);
            if (flag)
                return;
            fa[t1] = 0;
        }
    }
    --cur[x + 1][y], --cur[x][y + 1];
    ++lim[x][y], ++lim[x + 1][y], ++lim[x][y + 1], ++lim[x + 1][y + 1]; //恢复原状态;
}
int main()
{
    // freopen("gokigen.in","r",stdin);
    // freopen("gokigen.out", "w", stdout);
    int T;
    scanf("%d", &T);
    while (T--)
    {
        flag = 0;
        memset(cur, 0, sizeof(cur));
        memset(fa, 0, sizeof(fa));
        scanf("%d", &n), n++;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
            {
                lim[i][j] = 4; //对于任意一个节点，至多能连接四个斜;
                m[i][j] = read();
                if ((i == 1 || i == n) && (j == 1 || j == n)) //特判在棋盘四个角的情况;
                {
                    lim[i][j] = 1;
                    continue;
                }
                if (i == 1 || i == n || j == 1 || j == n) //如果这个点在边界上，则能放的斜数减少为2;
                    lim[i][j] = 2;
            }
        dfs(1, 1);
        for (int i = 1; i < n; i++)
        {                                //输出
            for (int j = 1; j < n; j++)
                if (!ans[i][j])
                    putchar('/');
                else
                    putchar('\\');
            putchar('\n');
        }
    }
    return 0;
}
```

---

## 作者：Zxsoul (赞：1)

# 题解

###  [题面](https://www.luogu.com.cn/problem/UVA11694)

@[**chen_zhe**](https://www.luogu.com.cn/user/8457)数据有误

## 思路

- 	我们从上到下，从左到右，一个格子一个格子搜索是放什么，但是这样可能过不去。要加剪枝。首先要保证，不连成环，这个直接用一个支持删除的并查集就可以维护。在格子中放斜杠时，注意判断上下左右的点度数的关系，遇到不合法的情况直接 $return$ 就$ok$ 了。

- 	具体地讲，就是暴力枚举每个格子的可能，并且枚举的是合法的，即满足数据给出的固定连边数，对于是否存在环，可以用并查集来判断，题目就完成了！

- 	大体思路就是这样，深搜题一是剪枝，二是码力。

## Code

```c
/*
大体思路
先处理好每个点的最多边数，和数据给出边数，
搜索枚举两种情况，两种对角线，分别对其四个方向进行修改
与往常不一样的是这次深搜是两种情况，并且在一种未执行时把他回复原来状态 
*/ 
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <string.h>
#define F(i,l,r) for(int i=l;i<=r;++i)
#define D(i,r,l) for(int i=r;i>=l;--i)
#define P(i,l,r) for(int i=l;i<r;i++)
#define Men(x,a) memset(x,a,sizeof(x))
#define FK(x) Men(x,0)
using namespace std;
typedef long long ll;

const int manx=1e6+10;
const int mamx = 1e6 + 11;
const ll mod = 2123400401301379571;
const int inf = 0x3f3f3f3f;
int dx[4]={0,1,0,1}; 
int dy[4]={0,0,1,1};
inline int read() {
  char c = getchar(); int x = 0, f = 1;
  for ( ; !isdigit(c); c = getchar()) if (c == '-') f = -1;
  for ( ; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
  return x * f;
}
int flag,ans[300][300],t,now[300][300],fa[manx],n,a[300][300],bz[300][300];
char oo;
void prepare(){
	flag=0;
	FK(now);
	FK(ans);
	FK(a);
	FK(bz);
	FK(fa);
}
bool check(int x,int y){
	if(a[x][y] == -1) return 1;
	if(now[x][y] <= a[x][y] && now[x][y]+bz[x][y] >= a[x][y])return 1;
	return 0;
}
int find(int x){
	if(!fa[x]) return x;
	return find(fa[x]);
	//return (fa[x]==x) ? x : fa[x]=find(fa[x]);
}
void dfs(int x,int y){
	
	if(y == n) x++,y=1;
	if(x == n) {flag=1;return;}
	//左上+右下的对角线
	int fax,fay,pd = 0;
	now[x][y]++,now[x+1][y+1]++;
	F(i,0,3) bz[x+dx[i]][y+dy[i]]--;
	F(i,0,3){
		int u = x + dx[i];
		int v = y + dy[i];
		if(!check(u,v)) {pd=1;break;} 
	} 
	//判断环，并查集 
	if(!pd){
		int x1 = (x-1)*n+y,x2 = x*n+y+1;
		 fax = find((x-1)*n+y),fay = find(x*n+y+1);
		if(fax != fay){
			ans[x][y]=0;
			fa[fax] = fay;
			dfs(x,y+1);
			if(flag)return;
			fa[fax] = 0; 
		} 
	}
	//复原
	now[x][y]--,now[x+1][y+1]--;
	
	//左下+右上的对角线
	now[x+1][y]++,now[x][y+1]++;
	pd=0;
	F(i,0,3){
		int u = x + dx[i];
		int v = y + dy[i];
		if(!check(u,v)) {pd=1;break;}
	} 
	//判断环，并查集 
	if(!pd){
		 fax = find(x*n+y),fay = find((x-1)*n+y+1);
		if(fax != fay){
			ans[x][y]=1;
			fa[fax] = fay;
			dfs(x,y+1);
			if(flag)return;
			fa[fax] = 0; 
		} 
	}	 
	now[x+1][y]--,now[x][y+1]--;
	F(i,0,3) bz[x+dx[i]][y+dy[i]]++;//恢复并回溯 
}
void print(){
	P(i,1,n){ 
		P(j,1,n){
			cout<<(!ans[i][j] ? "\\" : "/");
		}
		cout<<'\n';
	} 
}	
void red(){
	t = read();
	while(t--){
		prepare();
		n = read();
		n ++;
		F(i,1,n)
		F(j,1,n){
			bz[i][j] = 4;
			cin>>oo;
			a[i][j] = (oo == '.') ? -1 : (oo-'0');
			int pd = 0;
			if(i == 1 || i == n) bz[i][j]--,pd = 1;
			if(j == 1 || j == n) bz[i][j]--,pd = 1;
			bz[i][j] -= pd;//处理边界的方法 
		}
		dfs(1,1);
		print();
	}
} 
int main(){
	red(); 
	return 0;
}


```



---

## 作者：Suzt_ilymtics (赞：1)

### 写在前面

UVA的题需要自己读入一个 $T$ 组数据，别被样例给迷惑了

### Solution

每个格子只有两种填法且 $n \le 7$，暴力搜索两种填法，开cnt数组统计连接个数。

填一个格子，如果是 "\\"，格子左上角和右下角的 $cnt++$，如果是 "/"，格子左下角和右上角的 $cnt++$。只有更改后的 $cnt$ 小于等于目标 $cnt$才继续向下搜，否则回溯

发现每填一个格子，连接格子左上角的格点的个数就可以被确定，那么只有左上角的格点个数等于目标格点个数或没有要求才继续搜索，否则回溯

如果搜索到第 $n + 1$ 列时，要额外判断边界第 $n + 1$ 列的 $cnt$是否满足对应的个数
如果搜索到第 $n$ 行时，要额外判断边界第 $n + 1$ 行的 $cnt$ 是否满足对应个数


如何保证无环？不难想到，只有在填 "/" 时才有可能出现环，那么在填 "/" 之前，先判断是否有环

如何处理点的坐标？把行看做十位，把列看做个位就好啦

- 算法一：考虑可撤销并查集，~~然而我不会~~

- 算法二：发现n很小，每次判断时 $n^2$ 扫一遍建图，在 $dfs$ 看看能否从左下角跑到右上角

- 算法三：~~很显然算法二很傻逼~~，直接用并查集维护就好，加完边后判断左下角和右上角是否在同一并查集里，省去 $dfs$ 的时间，注意清零！

最后输出方案就好啦

### Code

我一开始建图跑的，后来也没改（~~因为懒~~

```cpp
/*
Work by: Suzt_ilymics
Knowledge: ??
Time: O(??)
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define LL long long
#define orz cout<<"lkp AK IOI!"<<endl

using namespace std;
const int MAXN = 10;
const int INF = 1;
const int mod = 1;

struct edge{
	int from, to, nxt;
}e[10100 << 1];
int head[MAXN * MAXN], num_edge = 0;

int n;
int go[MAXN][MAXN];
int cnt[MAXN][MAXN], now[MAXN][MAXN];
bool flag = false, Flag = false;

int read(){
	int s = 0, f = 0;
	char ch = getchar();
	while(!isdigit(ch))  f |= (ch == '-'), ch = getchar();
	while(isdigit(ch)) s = (s << 1) + (s << 3) + ch - '0' , ch = getchar();
	return f ? -s : s;
}

void add_edge(int from, int to){
	e[++num_edge] = (edge){from, to, head[from]}, head[from] = num_edge;
}

bool bl(int u, int fa, int end){
	for(int i = head[u]; i != -1; i = e[i].nxt){
		int v = e[i].to;
		if(v == fa) continue;
		if(v == end) {
			Flag = 1;
			return true;
		}
		bl(v, u, end);
		if(Flag) { return true;	}
	}
	return false;
}

bool pd(int sx, int sy, int ex, int ey){
	memset(head, -1, sizeof(head)); num_edge = 0;
	Flag = false;
	for(int i = 1; i <= n; ++i){
		for(int j = 1; j <= n; ++j){
			if(now[i][j] == 0){
				add_edge(i * 10 + j, (i + 1) * 10 + j + 1);
				add_edge((i + 1) * 10 + j + 1, i * 10 + j);
			}
			if(now[i][j] == 1){
				add_edge((i + 1) * 10 + j, i * 10 + j + 1);
				add_edge(i * 10 + j + 1, (i + 1) * 10 + j);
			}
		}
	}
	if(bl(sx * 10 + sy, 0, ex * 10 + ey)) return 1;
	else return 0;
}

void dfs(int posx, int posy){
//	cout<<posx<<" "<<posy; 
//	orz;
	if(posx == n && posy == n + 1) { 
		if( ((cnt[posx + 1][posy] == go[posx + 1][posy]) || (go[posx + 1][posy] == 9)) && ((cnt[posx][posy] == go[posx][posy]) || (go[posx][posy] == 9)) ) flag = 1; 
		return ; 
	}// 如果搜到最后一个点，说明已经找到答案。退出 
	if(posy == n + 1){ //如果这一行搜完了 
		if((cnt[posx][posy] == go[posx][posy]) || (go[posx][posy] == 9) ) posx++, posy = 1;//换行 
		else  return ;// 如果已经确定的那个数并没有达到目标，返回 
	}//
	
	now[posx][posy] = 0;// 填 "\" 
	cnt[posx][posy]++, cnt[posx + 1][posy + 1]++;// 对应位置加1 
	
	if(cnt[posx][posy] <= go[posx][posy] && cnt[posx + 1][posy + 1] <= go[posx + 1][posy + 1]) {//如果两个对应位置大于目标位置就不向下搜索 
		if((go[posx][posy] != 9 && go[posx][posy] == cnt[posx][posy]) || (go[posx][posy] == 9)) {//如果已经确定的那个数没有达到目标，停止向下搜索 
			if((posx != n) || (posx == n && ( (go[posx + 1][posy] != 9 && go[posx + 1][posy] == cnt[posx + 1][posy]) || (go[posx + 1][posy] == 9) ) )){
				dfs(posx, posy + 1);//
			}
		}
	}//
	if(flag) return ;// 如果找到答案就返回 
	cnt[posx][posy]--, cnt[posx + 1][posy + 1]--;//回溯 
	
	if(pd(posx + 1, posy, posx, posy + 1)){ return ;}
	
	now[posx][posy] = 1;// 填 "/"
	cnt[posx + 1][posy]++, cnt[posx][posy + 1]++;// 对应位置加1 
	
	if(cnt[posx + 1][posy] <= go[posx + 1][posy] && cnt[posx][posy + 1] <= go[posx][posy + 1]) {//如果两个对应位置大于目标位置就不向下搜索 
		if((go[posx][posy] != 9 && go[posx][posy] == cnt[posx][posy]) || (go[posx][posy] == 9)) {//如果已经确定的那个数没有达到目标，停止向下搜索 
			if((posx != n) || (posx == n && ( (go[posx + 1][posy] != 9 && go[posx + 1][posy] == cnt[posx + 1][posy]) || (go[posx + 1][posy] == 9) ) )){
				dfs(posx, posy + 1);//
			}
		}
	}
	if(flag) return ;// 如果找到答案就返回 
	now[posx][posy] = -1;//回溯 
	cnt[posx + 1][posy]--, cnt[posx][posy + 1]--;// 回溯 
}

int main()
{
//	freopen("gokigen.in","r",stdin);
//	freopen("gokigen.out","w",stdout);
	int T;
	T = read();
	while(T--){
		n = read();
		memset(now, -1, sizeof(now));
		memset(cnt, 0, sizeof(cnt));
		memset(go, 0, sizeof(go));
		flag = 0;
		char ch[10];
		for(int i = 1; i <= n + 1; ++i){
			cin>>(ch + 1);
			for(int j = 1; j <= n + 1; ++j){
				if(isdigit(ch[j])) go[i][j] = ch[j] - '0';
				else go[i][j] = 9;
			}
		}
		
		dfs(1, 1);
//		for(int i = 1; i <= n + 1; ++i){
//			for(int j = 1; j <= n + 1; ++j){
//				cout<<go[i][j]<<" ";
//			}
//			cout<<"\n";
//		}
//		cout<<"\n";
//		
//		for(int i = 1; i <= n + 1; ++i){
//			for(int j = 1; j <= n + 1; ++j){
//				cout<<cnt[i][j]<<" ";
//			}
//			cout<<"\n";
//		}
//		cout<<"\n";
		
		for(int i = 1; i <= n; ++i){
			for(int j = 1; j <= n; ++j){
				if(now[i][j] == 1) cout<<"/";
				else if(now[i][j] == 0) cout<<"\\";
				else cout<<"s";
			}
			cout<<"\n";
		} 	
	}
	return 0;
}
```

---

## 作者：Imy_bisLy (赞：1)

[博客园体验更佳](https://www.cnblogs.com/-wzd233/p/14226690.html)
#### 题解
考场上连暴力都不会打的码农题，深搜是真的难 /kk
######  前置问题
1. 怎么输出“\”
```cpp
cout<<"\\";
```
2.怎么处理不在一个环里，可以考虑并查集，$f$数组的下标为该元素位于矩阵中的个数
例如： 在$3 \times 3 $的矩阵中  $（2,2）$ **坐标指的是交点的坐标**
可以表示为 5 
```
（1,1）---->1
（1,2）---->2
（1,3）---->3
（1,4）---->4
（2,1）---->5
（2,2）---->6
（2,3）---->7
（2,4）---->8
（3,1）---->9
（3,2）---->10
（3,3）---->11
（3,4）---->12
```
如果两个点位于同一个并查里那就不能连边，如果不在，那么就可以连边
**此并查集不同于一般的并查集**
其初值不能为0 ，而且其不能进行路径压缩，自己想一下就会明白,如果路径压缩会这样![wa](https://cdn.luogu.com.cn/upload/image_hosting/6u6msfol.png)

3 .样例输入其实是有问题的
样例输入：
```
2
3
1.1.
...0
.3..
..2.
5
.21...
..33.0
......
..33..
0..33.
....11
```
输出：
```
\//
\\\
/\/
/\\//
//\\\
\\\//
\/\\/
///\\
```
再说一遍这是spj不要看样例不对就以为自己写错了，可能算法不一样也就不一样
####  1.思路
##### 思路1 ：
上面的前置知识中已经解决了一个最大的问题，环的问题，剩下的就是怎么搜索
从$(1,1)$开始搜索，逐行进行处理，因为每一个格子要不放"\"要不就是放"/"因为是spj我们可以考虑首先放"\",然后判断放"/"，种完全不反悔的深搜，一搜到底，适用的范围貌似不是很大
##### 思路2：
可以考虑从$（1,1）$开始搜索， 首先考虑放“/” 如果不合法，那就回溯，重新放置"\",这种想法想的很容易但是想要实现十分困难，反正这位[大佬](https://www.cnblogs.com/Silymtics/ )码量惊人，居然还真写出来了%%%%
#### 对于第一种思路的使用
```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring> 
#include <string> 
#define ll long long

using namespace std;
const int N = 150;
const int dx[4] = {0, 0, 1, 1};
const int dy[4] = {0, 1, 0, 1};
int n ;
int mapp[50][50] ;
int cnt[N][N]; // 这个点已经连接了几条边 
int lim[N][N]; //一个格子可以拓展的方向 
char ans[N][N]; // 一开始我是char想直接输出，我也不知为啥不行 
int f[N*N]; 
bool flag;

void print() {
	puts("");
	for(int i = 1 ; i <= n;i++) {
		for(int j = 1 ; j <= n ;j++) {
			cout<<mapp[i][j] <<" ";
		}
		puts("");
	}
}
//检验自己输入的函数
bool check(int x,int y){
	if(mapp[x][y] == -1) return true;
	if(cnt[x][y] <= mapp[x][y] && cnt[x][y] + lim[x][y] >= mapp[x][y]) return true;
	return false ; 
} 
//判断合法 

int findf(int x) {
	if( !f[x] ) return x;
	return f[x] = findf(f[x]);
}

void dfs(int x, int y) {
	if (y == n)	 {
		y = 1 , x++;
	} 
	if(x == n ) {
		flag = 1;
		return ;
	}
	// 这里因为是逐行搜索，n++后，不会检查第 n+1 行的交点，第n+1行下面已经没有格子了 
	int f1 , f2 ,pd = 0;
	++cnt[x][y], ++cnt[x + 1][y + 1];
	--lim[x][y],--lim[x+1][y+1],--lim[x+1][y],--lim[x][y+1];
	//因为一个格子只能放一种 \ 或者 / 所以  一个格子的四个角都要减少拓展的方向 
	//第一种情况 \ 
	for(int i = 0 ; i < 4 ;i++) {
		int tx = x + dx[i] , ty = y + dy[i];
		if(!check(tx,ty)) {
			pd = 1;
			break; 
		} 
	}
	if(!pd) {
		f1 = findf((x - 1) * n + y),f2 = findf(x * n + y + 1 ) ;
		if(f1 != f2) {
			ans[x][y] = 1; // 1 ---------> \ 
			f[f1] = f2;
			dfs(x,y+1);
			if(flag) return ;
			f[f1] = 0;
		} 
	}
	
	--cnt[x][y], --cnt[x+1][y+1];
	++cnt[x+1][y] ,++cnt[x][y+1];
	// 更换为另一种情况  / 
	pd = 0;
	for(int i = 0 ; i < 4 ;i++) {
		int tx = x + dx[i] , ty = y + dy[i];
		if(!check(tx,ty)) {
			pd = 1;
			break; 
		} 
	}
	if(!pd) {
		f1 = findf(x * n + y ),f2 = findf((x - 1) * n + y + 1) ;
		if(f1 != f2) {
			ans[x][y] = 0; // 0 ------------> /
			f[f1] = f2;
			dfs(x,y+1);
			if(flag) return ;
			f[f1] = 0;
		} 
	}
	--cnt[x+1][y] ,--cnt[x][y+1];
	++lim[x][y] ,++lim[x+1][y+1] ,++lim[x+1][y], ++lim[x][y + 1] ;
	//深搜回溯 
	
}
int main() {
//	freopen("gokigen.in","r",stdin);
//	freopen("gokigen.out","w",stdout);
	int T;
	cin>> T;
	while(T--) {
    //
		memset(cnt , 0 , sizeof(cnt));
		memset(f,0,sizeof(f));
        flag = 0;
	//多组不清我是sb	
        cin>> n; n++;
		for(int i = 1 ; i <= n ;i++) {
			for(int j = 1 ;  j <= n  ;j++) {
				lim[i][j] = 4;
				char ch = getchar() ;
				if(ch == '\n' && i + j != 2 * n ) ch = getchar();
				if(ch == '.') mapp[i][j] = -1;
				else mapp[i][j] = (ch - '0'); 
				if((i == 1 || i == n) && (j == 1 || j == n)) {
					lim[i][j] = 1;
					continue;	
				}
				if(i == 1 || i == n || j == 1 || j == n) lim[i][j] = 2;
			}
		}
		dfs(1,1);
		for(int i = 1 ; i < n ;i++) {
			for(int j = 1 ; j < n ;j++) {
				if(!ans[i][j]) cout<<"/";
				else cout <<"\\"; 
			}
			puts("");
		}		
	}
	return 0;
}
```

---

## 作者：轻尘 (赞：1)

SDWC 的一道题，身为蒟蒻的我不知所措。
在Df大佬的耳提面命下，我...终于A了；


------------
# So
## 。。。为了凑一篇博客

# 代码附上
```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
using namespace std;
int f = 0,n = 0;
int ans[101][101];
int a[101][101],cur[101][101],lim[101][101],fa[100001];
int xx[] = {0,0,1,1},yy[] = {0,1,0,1};
inline int rread()
{
    char c = getchar();
    while (!(c == '.' || (c >= '0' && c <= '4')))
        c = getchar();
    if (c == '.')
        return -1;
    else
        return c - '0';
}
inline int read()
{
    int x = 0;
    char c = getchar();
    while(c<'0'||c>'9') c = getchar();
    while(c>='0'&&c<='9')
    {
        x = x*10+c-'0';
        c = getchar();
    }
    return x;
}
int check(int x,int y)
{
    if(a[x][y] == -1) return 1;
    if(cur[x][y]+lim[x][y]>= a[x][y]&&cur[x][y]<=a[x][y])
    return 1;
    return 0;
}
int find(int a)
{
    if(!fa[a])
    return a;
    return find(fa[a]);
}
void dfs(int x,int y)
{
    if(y == n)
    y = 1,x++;
    if(x == n)
    {
        f = 1;
        return;
    }
    int ch = 0;
    ++cur[x][y],++cur[x+1][y+1];
    --lim[x][y],--lim[x+1][y+1],--lim[x+1][y],--lim[x][y+1];
    for(int i=0;i<4;i++)
        if(!check(x+xx[i],y+yy[i]))
            ch = 1;
    if(!ch)
    {
        int t1 = find((x-1)*n+y),t2 = find(x*n+y+1);
        if(t1!=t2)
        {
            ans[x][y] = 1;
            fa[t1] = t2;
            dfs(x,y+1);
            if(f) return ;
            fa[t1] = 0;
        }
    }
    ch = 0;
    --cur[x][y],--cur[x+1][y+1];
    ++cur[x+1][y],++cur[x][y+1];
    for(int i=0;i<4;i++)
        if(!check(x+xx[i],y+yy[i]))
            ch = 1;
    if(!ch)
    {
        int t1 = find(x*n+y),t2 = find((x-1)*n+y+1);
        if(t1!=t2)
        {
            ans[x][y] = 0;
            fa[t1] = t2;
            dfs(x,y+1);
            if(f) return ;
            fa[t1] = 0;
        }
    }
    --cur[x + 1][y], --cur[x][y + 1];
    ++lim[x][y], ++lim[x + 1][y], ++lim[x][y + 1], ++lim[x + 1][y + 1];
}
int main(){
    int t = read();
    while(t--)
    {
    memset(cur, 0, sizeof(cur));
    memset(fa, 0, sizeof(fa));
    f = 0;
    n  =read();n++;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            lim[i][j] = 4;
            a[i][j] = rread();
			if ((i == 1 || i == n) && (j == 1 || j == n)) 
        	{
                lim[i][j] = 1;
                continue;
            }
            if(i==1||j==1||i==n||j==n)
            lim[i][j] = 2;	
     } 
    dfs(1,1);
    for (int i = 1; i < n; i++)
    {                            
    	for (int j = 1; j < n; j++)
     		 if (!ans[i][j])
      			putchar('/');
     		 else
     			 putchar('\\');
      	putchar('\n');
    }
    }
    return 0;
}

```
丑陋的代码略略》》》
------------
# PS：
# %%% 楼上红名 
# [Drifting]巨佬(https://www.luogu.org/space/show?uid=54877)

---

## 作者：sunxiaofan (赞：0)

### 独创题解，dalao请多指教

此题是一道~~目前本蒟蒻做过的最难的能做出来的~~搜索题

这个题我是这样想的：建立一个map数组，用来存图；在建立一个ans数组用来存答案。其中，**1表示“\”,2表示“/”**。

首先，本题的主要思路是搜索。我用的dfs，从最左上部分开始搜索，先假设是1，若不行为2，再不行return。除了一些比较普通的特判外，当等于2时，还要**判断是否有环**。看dalao们都是写的并查集，而本蒟蒻比较特殊，花了很长时间研究除了bfs算法。

代码如下：
```cpp
#include<cstdio>
#include<iostream>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;
int t;
int n,ans[10][10],dir[4][2]={{0,-1},{-1,0},{-1,-1},{-1,1}};
char map[10][10];
bool flag;
int book[10][10];
struct node 
{
	int x,y,col,step;
}cur,nxt;

void clear(queue<node>& q) {
    queue<node> empty;
    swap(empty, q);
}
void print()
{
	/*for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			printf("%d",ans[i][j]);
		}
		printf("\n");
	}
	printf("\n");*/
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(ans[i][j]==1)printf("\\");
			else if(ans[i][j]==2)printf("/");
		}
		printf("\n");
	}
	flag=1;
}

queue<node> q;

bool bfs(int a,int b)
{
	//printf("$%d %d\n",a,b);
	memset(book,0,sizeof(book));
    clear(q);
    book[a][b]=1;
    cur.x=a;
    cur.y=b;
    cur.col =2;
    cur.step =1;
    q.push(cur); 
    while(!q.empty() )
    {
    	cur=q.front() ;
    	q.pop() ;
   //printf("%d %d %d %d\n",cur.x ,cur.y,cur.col ,cur.step );
    	for(int i=0;i<=3;i++)
    	{
    		if(cur.col ==2&&i==2)continue;
    		if(cur.col ==1&&i==3)continue;
    		if((cur.x+dir[i][0])>0&&(cur.y+dir[i][1])>0&&(cur.y+dir[i][1])<=n)
    		{
			    
    			if(i==1||i==0)
    			{
    				if(ans[cur.x+dir[i][0]][cur.y+dir[i][1]]!=cur.col )
    				{
    					nxt.x =cur.x+dir[i][0];
    					nxt.y =cur.y+dir[i][1];
    					nxt.col =ans[nxt.x ][nxt.y ];
    					nxt.step =cur.step +1;
    					if(!book[nxt.x][nxt.y ])
    					{
    						book[nxt.x][nxt.y ]=nxt.step ;
    						q.push(nxt);
						}
						else if(book[nxt.x ][nxt.y ]==nxt.step&&!(ans[nxt.x ][nxt.y ]==ans[nxt.x+1][nxt.y+1]&&ans[nxt.x+1][nxt.y ]==ans[nxt.x ][nxt.y +1]&&ans[nxt.x+1][nxt.y+1]!=ans[nxt.x ][nxt.y +1]) )
						{
						  //print();
						 //  printf("#\n");
						   
						   // printf("\n\n");
							return 1;
						}
						else if(book[nxt.x ][nxt.y ])
						{
							book[nxt.x][nxt.y ]=nxt.step;
						}
					}
				}
				else if(i==3||i==2)
				{
					
					if(ans[cur.x+dir[i][0]][cur.y+dir[i][1]]==cur.col )
					{
						nxt.x =cur.x+dir[i][0];
    					nxt.y =cur.y+dir[i][1];
    					nxt.col =ans[nxt.x ][nxt.y ];
    						nxt.step =cur.step +1;
    					if(!book[nxt.x][nxt.y ])
    					{
    						book[nxt.x][nxt.y ]=nxt.step;
    						q.push(nxt); 
						}
						else if(book[nxt.x ][nxt.y ]==nxt.step&&!(ans[nxt.x ][nxt.y ]==ans[nxt.x+1][nxt.y+1]&&ans[nxt.x+1][nxt.y ]==ans[nxt.x ][nxt.y +1]&&ans[nxt.x+1][nxt.y+1]!=ans[nxt.x ][nxt.y +1]) )
						{
						//	print();
						   // printf("\n\n");
						    return 1;
						}
						else if(book[nxt.x ][nxt.y ])
						{
							book[nxt.x][nxt.y ]=nxt.step;
						}
					}
				}
			}
		}
	}
	return 0;
}


void dfs(int x,int y)
{
	if(x==n+1)
	{
		print();
		return;
	}
	//printf("%d%d",'0','.');
	if(map[x-1][y-1]>'1')return;
	if(map[x-1][y-1]=='1')
	{
		
		if(y==n&&map[x-1][y]>'0')return;
		if(x==n&&map[x][y-1]>='1')return;
		if(map[x][y]=='0')return;
		if(y==1&&map[x][y-1]=='2')return;
		ans[x][y]=1;
		map[x-1][y-1]='0';
		if(map[x][y]>'0')map[x][y]-=1;
		if(y==n)dfs(x+1,1);
		else dfs(x,y+1);
		if(flag)return;
		ans[x][y]=0;
		map[x-1][y-1]='1';
		if(map[x][y]!='.')map[x][y]+=1;
		return;
	}
	if(y==n&&map[x-1][y]>'0')
	{
		if(x==n&&y==n&&map[x][y]=='1')return;
		if(map[x][y]=='2')return;
		if(map[x-1][y]=='2')return ;
		if(map[x][y-1]=='0')return;
		if(map[x][y-1]!='.')map[x][y-1]-=1;
		map[x-1][y]='0';
		ans[x][y]=2;
		dfs(x+1,1);
		if(flag)return;
		ans[x][y]=0;
		map[x-1][y]='1';
		if(map[x][y-1]!='.')map[x][y-1]+=1;
		return;
	}
	for(int i=1;i<=2;i++)
	{
		if(i==1)
		{
			if(map[x-1][y]>'1'||(y==n&&map[x-1][y]>'0'))
			{
				continue;
			}
			if(x==n&&(map[x][y-1]>'0'))continue;
			if(map[x-1][y-1]=='0'||map[x][y]=='0')continue;
			ans[x][y]=1;
			if(map[x][y]>'0')
			{
				map[x][y]-=1;
			}
			if(y==n)
			dfs(x+1,1);
			else dfs(x,y+1);
			if(flag)return;
			if(map[x][y]!='.')map[x][y]++;
			ans[x][y]=0;
		}
		else if(i==2)
		{
			if(x==n&&y==n&&map[x][y]=='1')return;
			if(x==n&&(map[x][y]>'1'))return;
			if(map[x-1][y]=='0'||map[x][y-1]=='0')return;
			if(map[x-1][y]>'2')return;
			if(bfs(x,y))return;
			ans[x][y]=2;
			if(map[x-1][y]>'0')map[x-1][y]--;
			if(map[x][y-1]>'0')map[x][y-1]--;
			if(y==n)
	     	dfs(x+1,1);
			else dfs(x,y+1);
			if(flag)return;
			if(map[x-1][y]!='.')map[x-1][y]++;
			if(map[x][y-1]!='.')map[x][y-1]++;
			ans[x][y]=0;
		}
	}
}

int main()
{      
    //freopen("1.in","r",stdin);
    //freopen("1.out","w",stdout);
    scanf("%d",&t);
    while(t--)
    {
    	memset(ans,0,sizeof(ans));
    	memset(map,0,sizeof(map));
    	memset(book,0,sizeof(book));
    	flag=0;
    	scanf("%d",&n);
    	for(int i=0;i<=n;i++)
        scanf("%s",map[i]);
        dfs(1,1);
	}
	return 0;
}
```
相较于dalao的代码，本代码明显长了许多，但是对于没有学过并查集的同学来说会比较好理解。

如果有什么不明白，可以问我……

---

