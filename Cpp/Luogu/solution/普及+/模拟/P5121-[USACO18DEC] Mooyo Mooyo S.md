# [USACO18DEC] Mooyo Mooyo S

## 题目描述

由于手上（更确实的，蹄子上）有大把的空余时间，Farmer John 的农场里的奶牛经常玩电子游戏消磨时光。她们最爱的游戏之一是基于一款流行的电子游戏 Puyo Puyo 的奶牛版；名称当然叫做 Mooyo Mooyo。

Mooyo Mooyo 是在一块又高又窄的棋盘上进行的游戏，高 $N$（$1\le N\le 100$）格，宽 $10$ 格。 这是一个 $N=6$ 的棋盘的例子：

```
0000000000
0000000300
0054000300
1054502230
2211122220
1111111223
```

每个格子或者是空的（用 $0$ 表示），或者是九种颜色之一的干草捆（用字符 $1\dots 9$ 表示）。重力会使得干草捆下落，所以没有干草捆的下方是 $0$。

如果两个格子水平或垂直方向直接相邻，并且为同一种非 $0$ 颜色，那么这两个格子就属于同一个连通区域。任意时刻出现至少 $K$ 个格子构成的连通区域，其中的干草捆就会全部消失，变为 $0$。如果同时出现多个这样的连通区域，它们同时消失。随后，重力可能会导致干草捆向下落入某个变为 $0$ 的格子。由此形成的新的布局中，又可能出现至少 $K$ 个格子构成的连通区域。若如此，它们同样也会消失（如果又有多个这样的区域，则同时消失），然后重力又会使得剩下的方块下落，这一过程持续进行，直到不存在大小至少为 $K$ 的连通区域为止。

给定一块 Mooyo Mooyo 棋盘的状态，输出这些过程发生之后最终的棋盘的图案。



## 说明/提示

在上面的例子中，如果 $K=3$，那么存在一个大小至少为 $K$ 的颜色 $1$ 的连通区域，同样有一个颜色 $2$ 的连通区域。当它们同时被移除之后，棋盘暂时成为了这样：

```
0000000000
0000000300
0054000300
1054500030
2200000000
0000000003
```

然后，由于重力效果，干草捆下落形成这样的布局：

```
0000000000
0000000000
0000000000
0000000000
1054000300
2254500333
```

再一次地，出现了一个大小至少为 $K$ 地连通区域（颜色 $3$）。移除这个区域就得到了最终的棋盘布局：

```
0000000000
0000000000
0000000000
0000000000
1054000000
2254500000
```

## 样例 #1

### 输入

```
6 3
0000000000
0000000300
0054000300
1054502230
2211122220
1111111223```

### 输出

```
0000000000
0000000000
0000000000
0000000000
1054000000
2254500000```

# 题解

## 作者：houzhiyuan (赞：26)

# P5121 [USACO18DEC]Mooyo Mooyo
## [题目传送门](https://www.luogu.com.cn/problem/P5121)
这题其实就是支持二个操作：

1.找联通块，然后删掉。

2.把有颜色的方格下落。

**显然，dfs可以完成第一个操作，而第二个操作可以直接暴力。**

**注意每次dfs前都要把数组清空。**

还有一些细节，代码中会提到。

### 接下来是美妙的代码时间：
```cpp
#include<bits/stdc++.h>
using namespace std;
bool biaoji[101][11],f;
int sum,n,k;
char ch[101][11];
int q[4]= {0,1,0,-1};
int w[4]= {1,0,-1,0};
void dfs(int x,int y,int s) {
	biaoji[x][y]=1;//当前点是联通块中的。
	for(int i=0; i<=3; i++) {
		int xx=x+q[i];
		int yy=y+w[i];
		if(biaoji[xx][yy]==0&&ch[xx][yy]==s) {
			sum++;//联通块数目加1。
			dfs(xx,yy,s);
		}
	}
}
void xialuo() {
	for(int i=n; i>=1; i--) {//注意要倒着，下面的掉下去了上面的才能掉。
		for(int j=1; j<=10; j++) {
			if(ch[i][j]!='0') {
				int k=i;
				while(ch[k+1][j]=='0'&&k<=n) {//k是掉到的位置。
					k++;
				}
				if(k!=i) {
					ch[k][j]=ch[i][j];
					ch[i][j]='0';
				}
			}
		}
	}
}
int main() {
	cin>>n>>k;
	for(int i=1; i<=n; i++) {//不用解释的字符输入。
		for(int j=1; j<=10; j++) {
			cin>>ch[i][j];
		}
	}
	f=1;//f表示当前是否有联通块，如果没有联通块就退出。
	while(f) {
		f=0;
		for(int i=1; i<=n; i++) {
			for(int j=1; j<=10; j++) {
				if(ch[i][j]!='0') {
					sum=1;
					memset(biaoji,false,sizeof(biaoji));//数组清空。
					dfs(i,j,ch[i][j]);
					if(sum>=k) {
						for(int xxx=1; xxx<=n; xxx++) {
							for(int xxxx=1; xxxx<=10; xxxx++) {
								if(biaoji[xxx][xxxx]) {//把联通块里的元素赋为0。
									ch[xxx][xxxx]='0';
								}
							}
						}
						f=1;
					}
				}
			}
		}
		if(f==1) {
			xialuo();
		}
	}
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=10; j++) {
			cout<<ch[i][j];
		}
		cout<<endl;
	}
	return 0;
}

```


---

## 作者：hhoppitree (赞：17)

### 题意简述：  
给定一 $n×10$ 的矩阵，若有大小 $\ge k$ 的联通块则**同时**赋值为空，紧接着整个矩阵**同时**向下掉落，求最终矩阵的状态。

### 题目解法： 
显而易见，这道题可以分成消除和掉落两个部分。  
先看消除怎么消除，由于题目说了连通块能消除当且仅当它的联通块大小 $\ge k$，所以我们先处理出每个连通块的大小，然后再消除，具体可以用 dfs 配合 vis 数组实现。  
再看掉落如何处理，我们从下往上循环，从左往右考虑，如果下面没有东西就把这个位置上的数挪到下面的位置，具体详见代码。
### 正确代码：  
```cpp
#include<bits/stdc++.h> 
using namespace std;
inline int read(){
    int res=0;
    char c;
    bool zf=0;
    while(((c=getchar())<'0'||c>'9')&&c!= '-');
    if(c=='-')zf=1;
    else res=c-'0';
    while((c=getchar())>='0'&&c<='9')res=(res<<3)+(res<<1)+c-'0';
    if(zf)return -res;
    return res;
}
int dx[]={0,0,-1,1},dy[]={-1,1,0,0};
int n,p;
int dta[105][105];
bool vis[105][105];
int cnt;
void dfs(int x,int y){
	vis[x][y]=1;
	++cnt;
	for(register int i=0;i<4;++i){
		int xx=x+dx[i],yy=y+dy[i];
		if(xx<1||xx>n||yy<1||yy>10||vis[xx][yy]||dta[xx][yy]!=dta[x][y])continue;
		dfs(xx,yy);
	}
	return;
}
void _clear(int x,int y){
	vis[x][y]=1;
	for(register int i=0;i<4;++i){
		int xx=x+dx[i],yy=y+dy[i];
		if(xx<1||xx>n||yy<1||yy>10||vis[xx][yy]||dta[xx][yy]!=dta[x][y])continue;
		_clear(xx,yy);
	}
	dta[x][y]=0;
	return;
}
inline bool _remove(){
	bool f=0;
	for(register int i=1;i<=n;++i)
		for(register int j=1;j<=10;++j){
			if(dta[i][j]){
				cnt=0;
				memset(vis,0,sizeof(vis));
				dfs(i,j);
				if(cnt>=p){
					f=1;
					memset(vis,0,sizeof(vis));
					_clear(i,j);
				}
			}
		}
	return f;
}
inline void fall(){
	bool f=1;
	while(f){
		f=0;
		for(register int i=n-1;i>=1;--i)
			for(register int j=1;j<=10;++j){
				if(dta[i][j]&&!dta[i+1][j]){
					dta[i+1][j]=dta[i][j];
					dta[i][j]=0;
					f=1;
				}
			}
	}
	return;
}
signed main(){
	n=read(),p=read();
	for(register int i=1;i<=n;++i)
		for(register int j=1;j<=10;++j){
			char c;
			while((c=getchar())<'0'||c>'9');
			dta[i][j]=c-'0';
		}
	while(_remove()){
		fall();
	}
	for(register int i=1;i<=n;puts(""),++i)
		for(register int j=1;j<=10;++j){
			putchar(dta[i][j]+'0');
		}
	return 0;
}
```

如果您没有看懂这篇题解，可以在评论区问我，我将会回答您的问题并且修改这篇题解，使它变得更加通俗易懂，服务更多的 $\text{OIer}$。  
如果您看懂了这篇题解，可以点个赞，使这篇题解的排名上升，服务更多的 $\text{OIer}$。  

---

## 作者：Akoasm_X (赞：12)

把题目翻译一遍就好啦

**代码比较友好哦**

**很耐心地写了注释**

1.统计连通块的大小

dfs实现即可

2.去掉一定大小的连通块

我这里采用的是dfs标记上，最后统一改成0

3.转移数组位置

愉快地搞一下就可以了

**我会在注释里解释一下我的做法**

```cpp
#include<bits/stdc++.h>
using namespace std;
int dx[] = {0,0,0,1,-1};
int dy[] = {0,1,-1,0,0};
//搜索的四个方向 
char mp[120][12];
//大小是n*10不是n*n，泪目 
bool vis[120][12];
//dfs用的标记 
bool v[120][12];
//标记要去掉的位置 
int n,m;
bool in(int x,int y)
{
	return x>=1&&x<=n&&y>=1&&y<=10;
}//判断是否在图中 
int dfs(int x,int y)
{
	int ans = 1;//自己 
	for(int i=1;i<=4;i++)
	{
		int xn = dx[i]+x;
		int yn = dy[i]+y;
		if(in(xn,yn)&&mp[x][y]==mp[xn][yn]&&vis[xn][yn]==0)
		//相等且未搜到 
		{
			vis[xn][yn] = 1;
			ans += dfs(xn,yn);
		}
	}
	return ans;//返回个数 
}
void get0(int x,int y)
{//把满足条件的变成0 
	for(int i=1;i<=4;i++)
	{
		int xn = dx[i]+x;
		int yn = dy[i]+y;
		if(in(xn,yn)&&mp[x][y]==mp[xn][yn]&&!v[xn][yn])
		{
			v[xn][yn] = 1;
			//标记上，搜索 
			get0(xn,yn);
		}
	}
}
bool judge()
{
	bool fa = 0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=10;j++)
			if(mp[i][j]!='0'&&!vis[i][j])
			{
				vis[i][j] = 1;
				if(dfs(i,j)>=m)
				{
					//大小大于等于m。进行删除操作 
					fa = 1;//表明可以操作 
					v[i][j] = 1;
					get0(i,j);
				}		
			}
	//dfs一遍就好啦 
	for(int i=1;i<=n;i++)
		for(int j=1;j<=10;j++)
			if(v[i][j])
				mp[i][j] = '0';
	//最后把标记上的位置都变成0 
	return fa; 
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%s",mp[i]+1);
	while(judge())//判断是否有大于等于m的连通块 
	{
		memset(v,0,sizeof(v));
		memset(vis,0,sizeof(vis));
		//清空数组 
		for(int i=1;i<=10;i++)
		{//再次重复n*10，泪目
		//每列每列操作 
			int tot = n;//设置放置的位置 
			for(int j=n;j>=1;j--)
			{
				if(mp[j][i]!='0')
				{
					mp[tot--][i] = mp[j][i];
					//如果该位置不为0，就放到现在tot标记的位置
					//更改tot的位置
				}
			}
			for(int j=1;j<=tot;j++)	
				mp[j][i] = '0';	
			//把tot以上的位置搞成0 
		}	
	}
	for(int i=1;i<=n;i++)
		printf("%s\n",mp[i]+1);
	//输出即可 
	return 0;
}
```


---

## 作者：_Qer (赞：3)

主要用BFS吧，码量不小

三个操作：  
1. 数单个联通块是否>=k  
2. 清除单个联通块  
3. 下落

前两个操作BFS完成，比较裸吧。第三个操作，每列进行处理，从下往上数，每次遇到一个方块就把它放到当前这列的顶端（前面已放好的），并且清除当前位置上的方块。

不过要注意，搜方块数的时候不删方块，就需要一个vis数组来记录访问过的点，防止重复搜索，vis只需要每次下落时清空，因为显然在下落前一个位置只会搜一次

```cpp
#include <bits/stdc++.h>
using namespace std;
#define LL long long
#define uLL unsigned long long
#define LD long double
using namespace io;
const int gx[] = {1, 0, -1, 0}, gy[] = {0, 1, 0, -1};
//四联通，两个方向上的步幅
int n, k;
char board[1010][15];//图
bool vis[1010][15];
bool Count(int x, int y) {//数联通块
    queue<pair<int, int> > que;  while (!que.empty()) que.pop();
    char sign = board[x][y];  int cnt = 0, tx = 0, ty = 0, nx = 0, ny = 0;;
    //sign记录方块编号
    vis[x][y] = true;
    que.push(make_pair(x, y));
    while (!que.empty()) {
        ++cnt, tx = que.front().first, ty = que.front().second;
        que.pop();
        if (cnt >= k) {//够了直接退出
            return true;
        }
        for (int i = 0; i < 4; ++i) {
            nx = tx + gx[i], ny = ty + gy[i];
            if (!vis[nx][ny] && board[nx][ny] == sign) {
                vis[nx][ny] = true;  que.push(make_pair(nx, ny));
            }
        }
    }
    return false;
}
void Clean(int x, int y) {//清除方块（主体和上面差不多）
    queue<pair<int, int> > que;  while (!que.empty()) que.pop();
    char sign = board[x][y];  int tx = 0, ty = 0, nx = 0, ny = 0;;
    board[x][y] = '0';
    que.push(make_pair(x, y));
    while (!que.empty()) {
        tx = que.front().first, ty = que.front().second;
        que.pop();
        for (int i = 0; i < 4; ++i) {
            nx = tx + gx[i], ny = ty + gy[i];
            if (board[nx][ny] == sign) {
                que.push(make_pair(nx, ny));
                board[nx][ny] = '0';
            }
        }
    }
}
void Move() {//下落
    memset(vis, false, sizeof(vis));//这里要记得清
    int cnt = 1;
    for (int i = 1; i <= 10; ++i) {
        cnt = 1;//当前这一列堆到第几个
        for (int j = 1; j <= n; ++j) {
            if (board[j][i] != '0') {
                board[cnt][i] = board[j][i];
                if (j != cnt)  board[j][i] = '0';
                //特判一下，否则下落后位置不变的方块就会变0
                ++cnt;
            }
        }
    }
}
int main() {
    cin >> n >> k;
    for (int i = n; i >= 1; --i) {
        for (int j = 1; j <= 10; ++j) {
            cin >> board[i][j];
        }
    }
    bool ok = false;//如果没有能消的说明结束了
    //假如没有能下落的也算结束，因为只有下落才可能增加合法联通块数量
    do {
        ok = false;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= 10; ++j) {
                if (board[i][j] != '0' && Count(i, j)) {
                    Clean(i, j);
                    ok = true;
                }
            }
        }
        Move(); 
    } while (ok);
    for (int i = n; i >= 1; --i) {
        for (int j = 1; j <= 10; ++j) {
            putchar(board[i][j]);
        }
        putchar('\n');
    }
    return 0;
}

```


---

## 作者：damage (赞：3)

### 题解

```USACO 2018.12月赛 银组 第三题```

其实还是道膜你题~~只会做膜你题的蒟蒻~~

### 本题实质：联通块（宽搜即可）（顺便三维联通块见[```P3693```](/problemnew/show/P3693)），只是分了不同颜色

用一个二维字符数组来记录地图，然后不停地判断是否可以消除，如果可以就下降，最后输出结果即可（结果我的代码永远都是那么的烂）。

具体：

- 判断```check()```：

 1. 枚举所有方块判断所在联通块
 
 2. 宽搜判断联通块（模板式作业），甚至连去重都不需要，若联通块大小大于规定的$k$就加入搜索到的联通块队列里（记得每次```check()```之前要清空队列）。
 
- 掉落```fall()```

 1. 先将所有搜索到的合法联通块的干草块删掉变成```0```
 
 2. 然后不停掉落（从倒数第二行往上遍历一遍算一次）```check2()```直到没有需要掉落的草方块（用一个```bool```变量记录即可）
 
   - 掉落规则：当前遍历到的方格是草方块但是下面一个是空的格子，那么当前格子会变成空的格子，然后下面一个格子变成当前颜色的草方块

---

### 代码

```cpp
#include<stdio.h>
#include<queue>
using namespace std;
int n,k,dxy[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
char mooyo[110][20];
bool vis[110][20];
struct coordinate //很hentai的结构体
{
    struct _pos
    {
        int x,y;
    }tpos;
    queue<_pos> pos;
}tcod,org;
queue<coordinate> blocks;
void bfs(int x,int y,char cl) //模式化找联通块（只不过我太菜了）
{
    for(register int i=0;i<110;++i)
        for(register int j=0;j<20;++j) vis[i][j]=false; //清零判重数组
    while(!org.pos.empty()) org.pos.pop(); //清空队列
    vis[x][y]=true;
    queue<coordinate::_pos> q;
    tcod.tpos.x=x;
    tcod.tpos.y=y;
    org.pos.push(tcod.tpos);
    q.push(tcod.tpos);
    int nx,ny;
    while(!q.empty()) //下面大家都会（宽搜模板）
    {
        tcod.tpos=q.front();
        q.pop();
        for(register int i=0;i<4;++i)
        {
            nx=tcod.tpos.x+dxy[i][0];
            ny=tcod.tpos.y+dxy[i][1];
            if(nx<0||ny<0||nx>=n||ny>=10||vis[nx][ny]||mooyo[nx][ny]!=cl) continue; //注意这里的边界，以及分不同颜色！
            vis[nx][ny]=true;
            tcod.tpos.x=nx;
            tcod.tpos.y=ny;
            q.push(tcod.tpos); //扩展状态
            org.pos.push(tcod.tpos); //记录方格
        }
    }
    if(org.pos.size()>=k) blocks.push(org); //若联通块大小大于规定的$k$就加入搜索到的联通块队列里
    return ;
}
bool check()
{
    for(register int i=0;i<n;++i) //遍历每个方格判断所属联通块
        for(register int j=0;j<10;++j)
            if(mooyo[i][j]!='0') bfs(i,j,mooyo[i][j]); //注意分颜色
    if(blocks.empty()) return false;
    return true;
}
bool check2()
{
    bool fallen=false; //标记是否有掉落
    for(register int i=n-2;i>=0;--i) //从倒数第二行往上遍历一遍
    {
        for(register int j=0;j<10;++j)
        {
            if(mooyo[i][j]>'0'&&mooyo[i+1][j]=='0') //若可以掉落
            {
                mooyo[i+1][j]=mooyo[i][j]; //如上面说明
                mooyo[i][j]='0';
                fallen=true; //记得记录有掉落的草方块（将会再次引起一次掉落）
            }
        }
    }
    return fallen;
}
void fall()
{
    while(!blocks.empty())
    {
        tcod=blocks.front();
        blocks.pop();
        while(!tcod.pos.empty())
        {
            tcod.tpos=tcod.pos.front();
            tcod.pos.pop();
            mooyo[tcod.tpos.x][tcod.tpos.y]='0'; //将所有合法联通块里的干草块消除
        }
    }
    while(check2()); //不停掉落直到没有可掉落的
    return ;
}
int main()
{
    scanf("%d%d",&n,&k);
    for(register int i=0;i<n;++i) scanf("%s",mooyo[i]); //输入地图
    fall(); //其实可以不加，这个是防止非法（一开始有悬空的）数据（即自己出的数据）
    while(check()) fall(); //不停消除并掉落
    for(register int i=0;i<n;++i) printf("%s\n",mooyo[i]); //输出最终地图
    return 0;
}
```

---

## 作者：Zenith_Yeh (赞：2)

“要想知正解，就先看范围。”

一看范围，就知道可以用模拟来解决。

**总共分两步：**

- 删除连通块。

- 下落干草。

根据这两步模拟即可。

**代码：**
```cpp
#include<bits/stdc++.h>
#define read() Read<int>()
namespace pb_ds{//优美的快读，但是这里不可用。因为会把字符吃掉。
    namespace io{
        const int MaxBuff=1<<15;
        const int Output=1<<23;
        char B[MaxBuff],*S=B,*T=B;
		#define getc() ((S==T)&&(T=(S=B)+fread(B,1,MaxBuff,stdin),S==T)?0:*S++)
        char Out[Output],*iter=Out;
        inline void flush(){
            fwrite(Out,1,iter-Out,stdout);
            iter=Out;
        }
    }
    template<class Type> inline Type Read(){
        using namespace io;
        register char ch;
        register Type ans=0;
        register bool neg=0;
        while(ch=getc(),(ch<'0' || ch>'9') && ch!='-');
        ch=='-'?neg=1:ans=ch-'0';
        while(ch=getc(),'0'<= ch && ch<='9') ans=ans*10+ch-'0';
        return neg?-ans:ans;
    }
    template<class Type> inline void Print(register Type x,register char ch='\n'){
        using namespace io;
        if(!x) *iter++='0';
        else{
            if(x<0) *iter++='-',x=-x;
            static int s[100];
            register int t=0;
            while(x) s[++t]=x%10,x/=10;
            while(t) *iter++='0'+s[t--];
        }
        *iter++=ch;
    }
}
using namespace pb_ds;
using namespace std;
struct bb
{	int x,y;
}dl[105*105];
int n,k,len,S,fx[4][2]={{0,-1},{0,1},{1,0},{-1,0}};
char mp[105][105];
bool bj[105][105];
void dfs(int x,int y,char color)//寻找连通块。
{	S++;
	bj[x][y]=1;
	dl[++len].x=x;
	dl[len].y=y;
	for(register int i=0;i<4;++i)
	{	int ex=x+fx[i][0],ey=y+fx[i][1];
		if(bj[ex][ey])continue;
		if(mp[ex][ey]==color)dfs(ex,ey,color);
	}
}
inline void move()//下落干草
{	for(register int j=1;j<=10;++j)
	{	int now_i=n;
		for(register int i=n;i>=1;--i)
		{	if(mp[i][j]!='0')
			{	swap(mp[now_i][j],mp[i][j]);
				now_i--;
			}
		}
	}
}
int main()
{	scanf("%d%d",&n,&k);
	for(register int i=1;i<=n;++i)
	{	getchar();
        for(register int j=1;j<=10;++j)mp[i][j]=getchar();
	}
	while(1)
	{	move();
		bool flag=0;
		memset(bj,0,sizeof(bj));
		for(register int i=1;i<=n;++i)
			for(register int j=1;j<=10;++j)
			{	if(!isdigit(mp[i][j]))continue;
				if(mp[i][j]=='0')continue;
				S=0;
				len=0;
				dfs(i,j,mp[i][j]);
				if(S>=k)
				{	flag=1;
					for(register int l=1;l<=len;++l)mp[dl[l].x][dl[l].y]='0';
				}
			}
		if(flag==0)break;
	}
	for(register int i=1;i<=n;++i)
	{	for(register int j=1;j<=10;++j)cout<<mp[i][j];
		cout<<endl;
	}
	return 0;
}

```


---

## 作者：Hexarhy (赞：2)

### 思路：搜索

一看到题目，立马就想到了搜索进行**染色**。几个要点：

- 第一步是消。那我们就找联通块，判断遍历个数是否有$k$个，然后再搜一遍进行染色。

- 第二步下落。像消消乐一样，我们可以把大问题分解成简单问题。对于一个宽度只有$1$的棋盘，我们只需要**从下往上搜**，遇到$0$，就把它上面依次往下挪同一个距离。稍微画图就很容易想到。那么对于宽度为$10$的棋盘，也只是多加一层循环而已。

- 最后还要判断是否消完，是不是要重复上述步骤。是否消完其实就看是否有$k$大小的联通块。不妨用一个$\mathrm{bool}$，每次搜索前都是$\mathrm{false}$。在找联通块的时候，**一遇到超过$k$的，就直接赋值为**$\mathrm{true}$。如果搜完了还是$\mathrm{false}$，说明已经消完了。

- 另外，由于$\mathrm{bool}$的初始值是$\mathrm{false}$，可$\mathrm{while}$里是要求$\mathrm{true}$，故采用`do-while`。

- 对于读入，由于数字之间没有空格，不能用普通的`cin`和`scanf("%d")`，但是`scanf("%1d")`可以强制每次只读入一个数位。

- CCF提醒您，搜索千万遍，**清空**第一条。求解不清空，WA两行泪。

另外，数组的横纵坐标要注意，请自行想清楚了来把握。

由于数据太小，所以上述搜索是不会超时的，尽管感觉用了很多循环。

其它的程序会体现。


```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;

const int dx[]={0,0,1,-1};
const int dy[]={1,-1,0,0};//搜索的四个方向
const int MAXN=250;
int n,k,s;
int a[MAXN][MAXN];
bool visit[MAXN][MAXN];
bool f;//判断是否消完

void input(void)
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
	 for(int j=1;j<=10;j++)
	  scanf("%1d",&a[i][j]);//每次只读入一个数位
}

void count(const int x,const int y,const int col)//统计联通块的个数
{
	if(x<1 || x>n || y<1 || y>10 || visit[x][y] || a[x][y]!=col)
	 return;
	visit[x][y]=true;
	s++;//统计
	for(int i=0;i<4;i++)
		count(dx[i]+x,dy[i]+y,col);
}

void disappear(const int x,const int y,const int col)//消除，变为0
{
	if(x<1 || x>n || y<1 || y>10 || visit[x][y] || a[x][y]!=col)
	 return;
	visit[x][y]=true;
	a[x][y]=0;//消除
	for(int i=0;i<4;i++)
		count(dx[i]+x,dy[i]+y,col);
}

void drop(void)//下落
{
	for(int i=1;i<=10;i++)//棋盘每一列逐个下落
	 for(int j=n;j>=1;j--)//从下往上搜
	  if(a[j][i]==0)//遇到了一个0
	   for(int k=j;k>=1;k--)//从当前0的位置出发，继续往上搜，并依次赋值
	    if(a[k][i])
		{
			a[j][i]=a[k][i];
			a[k][i]=0;//掉落之后该位置就是空的了
			break;//这个break是干什么的窝忘了QAQ
		}
}

void solve(void)
{
	do//上文讲过为什么采用do-while
	{
		f=false;//每次搜索前都要赋值
		for(int i=1;i<=n;i++)
	 	 for(int j=1;j<=10;j++)
	 	{
	 		if(a[i][j]==0)//空格没必要搜
	 	 	 continue;
	 		s=0;//联通块个数在搜索之前记得清零
	 		memset(visit,false,sizeof(visit));//别忘了清空
			count(i,j,a[i][j]);
			if(s>=k)
			{
				f=true;//只要有一个符合要求，f就为true
				memset(visit,false,sizeof(visit));//别忘了清空
				disappear(i,j,a[i][j]);
			}	
	 	}
		memset(visit,false,sizeof(visit));//别忘了清空
		drop();//注意掉落是所有染色完了之后再掉落的
	}while(f);
}

void output(void)
{
	for(int i=1;i<=n;i++,puts(""))
	 for(int j=1;j<=10;j++)
	  printf("%d",a[i][j]);
}

int main()
{
// 	freopen("mooyomooyo.in","r",stdin);
// 	freopen("mooyomooyo.out","w",stdout);
	input();
	solve();
	output();
	return 0;
}
```


---

## 作者：raincity (赞：1)

## 吐槽
这是一道膜你题。这题让我膜了整整3个小时啊！
看看我的提交https://www.luogu.com.cn/record/list?pid=P5121&user=Calvincheng1231&page=1

~~糟心……~~

## 题目
https://www.luogu.com.cn/problem/P5121
（自行查看）

## 分析

这题码量**超级大**。有几个麻烦到极点的操作：

1.计算连通块。为了返回得快，选用了广搜（BFS）。一旦目前搜到的个数大于等于$K$,就可以直接返回true。注意 $\color{red}\text{清零!!!}$```
```cpp
bool search(int x,int y){
	if(color[x][y]==0) return false;//空地
	queue<node> q;//广搜队列
	node from;
	from.x=x;from.y=y;
	q.push(from);
	int s=0;//找到了几个
	while(!q.empty()){//队列未空
		node tmp=q.front();q.pop();//取出队首并出队
		if(tmp.x<1||tmp.y<1||tmp.x>n||tmp.y>10) continue;//不在盘内
		if(color[tmp.x][tmp.y]!=color[x][y]) continue;//不同色
		if(vis[tmp.x][tmp.y]) continue;//访问过
		else vis[tmp.x][tmp.y]=true;
		s++;
		if(s>=k) return true;//找到了k个
		for(int i=0;i<4;i++){//扩展新节点
			node t;
			t.x=tmp.x+dxy[i][0],t.y=tmp.y+dxy[i][1];
			q.push(t);
		}
	}
	return false;
}
```
2.消除连通块。只要全部消除即可，为了方便写了DFS。
```cpp
void toss(int x,int y,int c){
	if(x<1||x>n||y<1||y>10) return;//不在格子内
	if(color[x][y]!=c) return;//不同颜色
	else color[x][y]=0;
	for(int i=0;i<4;i++)
		toss(x+dxy[i][0],y+dxy[i][1],c);//递归地扔掉
}
```
3.落下。调了我一个钟头~~因为我太菜了~~。
```cpp
void fall(){
	for(int j=1;j<=10;j++)//一列列处理
		for(int i=n;i>=1;i--)//从低到顶
			if(color[i][j]==0)//空的
				for(int k=i;k>=1;k--)//网上找
					if(color[k][j]!=0){//第一堆干草
						color[i][j]=color[k][j];//会补上空缺
						color[k][j]=0;//落下后原来的就空了
						break;//所以补上了。不用再找了。
					}
}
```
4.每一轮查找。只需要调用前面三个操作就行了。
```cpp
bool find(){
	memset(vis,false,sizeof(vis));//搜索不清零，爆零两行泪
	bool res=false;//连通块
	for(int i=1;i<=n;i++)
		for(int j=1;j<=10;j++){//枚举每一个点
			if(search(i,j)){//如果大于等于k个
				res=true;
				toss(i,j,color[i][j]);//扔掉
			}
		}
	if(res) fall();//扔过，落下。
	return res;
}
```
## 解决
把前面串起来即可。
### 无注释代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,color[110][15];
const int dxy[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
bool vis[110][15];
struct node{
	int x,y;
};
void output(){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=10;j++)
			cout<<color[i][j];
		cout<<endl;
	}
}
void toss(int x,int y,int c){
	if(x<1||x>n||y<1||y>10) return;
	if(color[x][y]!=c) return;
	else color[x][y]=0;
	for(int i=0;i<4;i++)
		toss(x+dxy[i][0],y+dxy[i][1],c);
}
void fall(){
	for(int j=1;j<=10;j++)
		for(int i=n;i>=1;i--)
			if(color[i][j]==0)
				for(int k=i;k>=1;k--)
					if(color[k][j]!=0){
						color[i][j]=color[k][j];
						color[k][j]=0;
						break;
					}
}
bool search(int x,int y){
	if(color[x][y]==0) return false;
	queue<node> q;
	node from;
	from.x=x;from.y=y;
	q.push(from);
	int s=0;
	while(!q.empty()){
		node tmp=q.front();q.pop();
		if(tmp.x<1||tmp.y<1||tmp.x>n||tmp.y>10) continue;
		if(color[tmp.x][tmp.y]!=color[x][y]) continue;
		if(vis[tmp.x][tmp.y]) continue;
		else vis[tmp.x][tmp.y]=true;
		s++;
		if(s>=k) return true;
		for(int i=0;i<4;i++){
			node t;
			t.x=tmp.x+dxy[i][0],t.y=tmp.y+dxy[i][1];
			q.push(t);
		}
	}
	return false;
}
bool find(){
	memset(vis,false,sizeof(vis));
	bool res=false;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=10;j++){
			if(search(i,j)){
				res=true;
				toss(i,j,color[i][j]);
			}
		}
	if(res) fall();
	return res;
}
int main(){
	freopen("mooyo.in","r",stdin);
   	freopen("mooyo.out","w",stdout);
	char ch;
	cin>>n>>k;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=10;j++){
			cin>>ch;
			color[i][j]=ch-'0';
		}
	while(find());
	output();
	return 0;
}


```
## THE END

---

## 作者：糖葫芦 (赞：1)

看到矩阵又看到连块，当然是用dfs了。

直接搜索连块，顺便消除嘛。

但是它必须在连块达到一定个数时才可消除。在搜索中累加到一定个数再清除会有bug，之前返回的快是清除不到的。所以要另外加一个函数来清除连块。

还有一个重要的部分就是下降，因为是每列下降，所以以列为单位，从下往上搜，每找到一个非零数，都与当前列最下方的0互换。

贴下代码：
```cpp
for(int i=1;i<=10;i++){
   int pos=n;
   for(int j=n;j>=1;j--){
     if(s[j][i]!='0')swap(s[j][i],s[pos--][i]);
   }
}
```
以下为完整代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,k,st;//st记录连续块的个数
int dx[4]={-1,0,1,0};
int dy[4]={0,1,0,-1};
char s[101][11];
bool f[101][11],flag=true,fl;
void dfs(int x,int y){//搜素连块
    if(st>=k)fl=true;//当连块超过限定值，标记
    f[x][y]=1;
    for(int i=0;i<4;i++){//2维dfs基本模板
        int tx=x+dx[i];
        int ty=y+dy[i];
        if(tx>0&&ty>0&&tx<=n&&ty<=10&&!f[tx][ty]&&s[tx][ty]==s[x][y]){
            st++;
            dfs(tx,ty);
        }
    }
}
void dfs2(int x,int y){//清除连块
    f[x][y]=1;
    for(int i=0;i<4;i++){//基础模板
        int tx=x+dx[i];
        int ty=y+dy[i];
        if(tx>0&&ty>0&&tx<=n&&ty<=10&&s[tx][ty]!='0'&&s[tx][ty]==s[x][y]&&!f[tx][ty]){

            dfs2(tx,ty);
        }
    }
    s[x][y]='0';//清成0
}
int main(){
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=10;j++){
            cin>>s[i][j];
        }
    }
    while(flag){
        flag=0;
        memset(f,0,sizeof(f));
        for(int i=1;i<=n;i++){
            for(int j=1;j<=10;j++){
                if(!f[i][j]&&s[i][j]!='0'){
                    st=1;
                    fl=false;
                    dfs(i,j);
                    if(fl)flag=true;
                    memset(f,0,sizeof(f));
                    if(fl)dfs2(i,j);
                }
            }
        }
        for(int i=1;i<=10;i++){
            int pos=n;
            for(int j=n;j>=1;j--){
                if(s[j][i]!='0')swap(s[j][i],s[pos--][i]);
                //按列扫,搜到非零数就直接下移
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=10;j++){
            cout<<s[i][j];
        }
        puts("");
    }
    return 0;
}
```


---

## 作者：sycqwq (赞：0)

这是一道很暴力的题

难点就在下落

和一点点套路

思路：

先dfs找连通块

找到大于等于k的连通块后全都赋0

然后下落

给出详细注释代码：

```cpp
#include<bits/stdc++.h>
#define inf 2147283647
using namespace std;
int n,k;
char a[105][105];
int bk[105][105];
int s,tx[5]={0,0,0,1,-1},ty[5]={0,1,-1,0,0};
void dfs(int x,int y,char t)
{
    ++s;//s为这个连通块的面积，必须要≥k
    bk[x][y]=1;//bk数组记录，dfs就不讲了
    for(int i=1;i<=4;i++)
    {
        int dx=x+tx[i],dy=y+ty[i];
        if(dx<1||dx>n||dy<1||dy>10||bk[dx][dy]||a[dx][dy]!=t)
            continue;
        dfs(dx,dy,t);
    }
}
int main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=10;j++)
        {
            cin>>a[i][j];
        }
    }
    while(1)
    {
        int f=0;
        for(int i=1;i<=n;i++)//这里是找连通块、
            for(int j=1;j<=10;j++)
            {
                if(a[i][j]!='0')
                {
                    for(int i=1;i<=n;i++)//bk数组赋0，不建议用memset
                        for(int j=1;j<=10;j++)
                            bk[i][j]=0;
                    s=0;//切记！！！s赋0
                    dfs(i,j,a[i][j]);
                    if(s>=k)
                    {
                        f=1;
                        for(int k=1;k<=n;k++)//因为之前使用bk数组标记的，并没有在a数组中修改，至于为什么要用bk数组，是因为如果在dfs中直接修改a值，如果dfs完后面积不符合要求，就十分的麻烦，需要一个标记数组。
                        
                            for(int l=1;l<=10;l++)
                            {
                                if(bk[k][l])//修改
                                {
                                    a[k][l]='0';
                                }
                            }
                    }
                }
            }
        for(int i=1;i<=10;i++)//下落操作
        /*
        	思路，一列一列的下落
           然后在这一列中查找，如果为0，那么久代表上面要有数掉下来，然后往上查找，找到第一个非0的数，交换（掉落）
        */
        {
            for(int j=n;j>=1;j--)
            {
                if(a[j][i]=='0')
                {
                    int tp=0;
                    for(int k=j-1;k>=1;k--)//往上查找，记得倒叙
                    {
                        if(a[k][i]!='0')
                        {
                            tp=k;
                            break;
                        }
                    }
                    if(tp!=0)//特判
                    {
                        a[j][i]=a[tp][i];//掉落
                        a[tp][i]='0';
                    }
                }
            }
        }
        if(!f)//跳出循环条件，如果这一次查找没有找到≥k的连通块，就代表没有任何消为0的，自然也不会继续掉落了，退出循环
            break;
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=10;j++)
            cout<<a[i][j];
        cout<<endl;
    }
    return 0;
}
```

---

## 作者：linwenchen (赞：0)

这道题目其实就类似于一个消消乐。。。先瞬间消掉连起来超过k长度的方块（把1~9看成不同颜色的方块），然后下落，再消，直到消不了，输出答案就行。

因为数据不大所以（~~给了我菜鸡一条活路~~）我们可以模拟来做。

模拟的过程有：

1.查找连在一起并且超过k长度的联通方块

2.消去联通方块

3.模拟消去方块后的下落过程

4.重复1~3直到没有超过k长度的联通方块，就结束

1、2都是搜图，可以想到深搜，其实就是深搜，一搜图，二搜标记数组消图



```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
typedef long long ll;
//图大小是N*10 N<=100

char map[105][11];//图
int vis[105][11];//标记数组
int v[4][2] = {0,1,1,0,0,-1,-1,0};//四个搜索方向
int n,k;
int sum;
//查map图
//传入当前的坐标和颜色
void search1(int x,int y,char c)
{
    vis[x][y] = 1;//用vis数组标记已经查过图中这个坐标的点了
    for(int i = 0;i<4;i++)
    {
        int xx = x+v[i][0];
        int yy = y+v[i][1];
        if(xx<0 || yy<0 || xx>=n || yy >= 10 || map[xx][yy]!=c || vis[xx][yy])continue;
        sum++;
        search1(xx,yy,c);

    }
}
//清map图
void dfs(int x,int y)
{
    if(vis[x][y])//把map图里面的消掉的同时把vis标记去掉
    {
        map[x][y] = '0';
        vis[x][y] = 0;
    }
    
    for(int i = 0;i<4;i++)
    {
        int xx = x+v[i][0];
        int yy = y+v[i][1];
        if(xx<0 || yy<0 || xx>=n || yy >=10)continue;
        if(vis[xx][yy])dfs(xx,yy);

    }
}
//清vis数组，wa第二个就是因为这个。。。
void dfs1(int x,int y)
{
    if(vis[x][y])vis[x][y] = 0;
    for(int i = 0;i<4;i++)
    {
        int xx = x+v[i][0];
        int yy = y+v[i][1];
        if(xx<0 || yy<0 || xx>=n || yy >=10)continue;
        if(vis[xx][yy])dfs1(xx,yy);

    }
}
//搜图函数
int seamap()
{

    int flag = 0;//如果搜完图之后没有一个颜色长度是大于k的，就可以结束并输出图了
    for(int i = 0;i<n;i++)
    {
        for(int j = 0;j<10;j++)
        {
            //if(j && map[i][j] == map[i][j-1])continue;
            //if(i && map[i][j] == map[i-1][j])continue;
            if(map[i][j]!='0')
            {
                sum = 1;//当前一个点，所以初始化为1
                search1(i,j,map[i][j]);
                if(sum>=k)//满足条件就清图，不满足就把vis数组清了，不影响下一次的标记
                {
                    flag = 1;
                    dfs(i,j);
                }
                else
                    dfs1(i,j);

            }
        }

    }
    if(flag)return 1;
    else return 0;
}
int main()
{
    scanf("%d %d",&n,&k);
    for(int i = n-1;i>=0;i--)
        scanf("%s",map[i]);
    while(seamap())
    {
        //模拟下落过程//
        for(int i = 0;i<10;i++)
        {
            string s;
            int len = 0;
            //记下当前列的非0字符，存到s
            for(int j = 0;j<n;j++)
                if(map[j][i]!='0')
                {
                    s += map[j][i];//看大佬代码学的，很好用
                    len++;
                }
            for(int j = 0;j<n;j++)
            {
                if(j<len)
                    map[j][i] = s[j];
                else
                    map[j][i] = '0';
            }
        }
    }


    for(int i = n-1;i>=0;i--)
    printf("%s\n",map[i]);

    return 0;
}
```

---

## 作者：__Hacheylight__ (赞：0)

T3 Mooyo Mooyo

【题意】

有一个游戏，定义连通块为相邻且颜色相同的元素集。

每一时刻，如果连通块大小>=k,那么该连通块元素消失，然后它上面的元素会全部掉落，然后组成新的连通块。

询问最后的图案长成什么样子。

【分析】

数据范围不大，就变成了一个非常水的题目，直接模拟即可。

直接枚举每个连通块，记录元素，然后如果块大小>=k，则按照记录的元素变成0，然后对于每个元素判断它能够降到哪里就行了。

枚举连通块通过dfs搞，别忘记标记哦。

时间复杂度肯定撑得下，毕竟数据太小了，本人也没有太详细的去算

【代码】

```cpp
#include <map>
#include <set>
#include <cmath>
#include <ctime>
#include <queue>
#include <stack>
#include <vector>
#include <bitset>
#include <cstdio>
#include <cctype>
#include <string>
#include <cstring>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <functional>
using namespace std ;

#define rep(i, a, b) for (int (i) = (a); (i) <= (b); (i)++)
#define Rep(i, a, b) for (int (i) = (a) - 1; (i) < (b); (i)++)
#define REP(i, a, b) for (int (i) = (a); (i) >= (b); (i)--)
#define clr(a) memset(a, 0, sizeof(a))
#define Sort(a, len, cmp) sort(a + 1, a + len + 1, cmp)
#define ass(a, sum) memset(a, sum, sizeof(a))

#define ls ((rt) << 1)
#define rs ((rt) << 1 | 1)
#define lowbit(x) (x & -x)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define endl '\n'
#define ENDL cout << endl
#define SZ(x) ((int)x.size())

typedef long long ll ;
typedef unsigned long long ull ;
typedef vector <int> vi ;
typedef pair <int, int> pii ;
typedef pair <ll, ll> pll ;
typedef map <int, int> mii ;
typedef map <string, int> msi ;
typedef map <ll, ll> mll ;

const int N = 2010 ;
const double eps = 1e-8 ;
const int iinf = INT_MAX ;
const ll linf = 2e18 ;
const double dinf = 1e30 ;
const int MOD = 1000000007 ;

const int dx[] = {-1, 0, 1, 0} ;
const int dy[] = {0, 1, 0, -1} ;

int n, m = 10, k ;
int a[N][20], vis[N][20] ;
vector <pii> vispl ;
string s ;

void dfs(int x, int y) {
	vis[x][y] = 1 ;
	for (int i = 0; i < 4; i++) {
		int tx = x + dx[i], ty = y + dy[i] ;
		if (tx < 1 || ty < 1 || tx > n || ty > m || a[tx][ty] != a[x][y] || vis[tx][ty]) continue ;
		vispl.pb(mp(tx, ty)) ;
		dfs(tx, ty) ;
	}
}

int main() {
	freopen("mooyomooyo.in", "r", stdin) ;
	freopen("mooyomooyo.out", "w", stdout) ;
	scanf("%d%d", &n, &k) ;
	for (int i = 1; i <= n; i++){
		cin >> s ;
		for (int j = 1; j <= m; j++) a[i][j] = s[j - 1] - '0' ;
	}
	while (1) {
		bool flag = false ;
		clr(vis) ;
		for (int i = 1; i <= n; i++) 
		for (int j = 1; j <= m; j++)
		if (!vis[i][j] && a[i][j]) {
			vispl.pb(mp(i, j)) ;
			dfs(i, j) ;
			if (SZ(vispl) >= k) {
				for (int l = 0; l < SZ(vispl); l++) a[vispl[l].fi][vispl[l].se] = 0 ;
				flag = true ;
			}
			vispl.clear() ; 
		}
		if (!flag) break ;
		for (int i = n - 1; i >= 1; i--)
		for (int j = 1; j <= m; j++)
		if (a[i][j]) {
			int tmp = a[i][j], ii = i ; 
			a[i][j] = 0 ;
			while (a[ii + 1][j] == 0 && ii < n) ii++ ;
			a[ii][j] = tmp ;
		} 
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) cout << a[i][j] ;
		ENDL ;
	}
}
```

---

## 作者：StudyingFather (赞：0)

本题是一个简单模拟题。

每次按题意dfs找出连通块，并将其删除即可。

注意当一个格子下面为空的时候，不要忘了把它往下移动。

```cpp
#include <cstdio>
#include <cstring>
#include <set>
using namespace std;
struct node
{
 int x,y;
 bool operator<(const node&a)const
 {
  return x<a.x||(x==a.x&&y<a.y);
 }
};
set<node> se;
char s[105][15];
int vis[105][15],n,k;
int dfs(int x,int y,char cur)//找连通块
{
 vis[x][y]=1;
 se.insert({x,y});//将找到的格子加入集合，便于后面执行删除操作
 int ans=1;
 if((!vis[x-1][y])&&s[x-1][y]==cur)ans+=dfs(x-1,y,cur);
 if((!vis[x+1][y])&&s[x+1][y]==cur)ans+=dfs(x+1,y,cur);
 if((!vis[x][y-1])&&s[x][y-1]==cur)ans+=dfs(x,y-1,cur);
 if((!vis[x][y+1])&&s[x][y+1]==cur)ans+=dfs(x,y+1,cur);
 return ans;
}
int main()
{
 //freopen("mooyomooyo.in","r",stdin);
 //freopen("mooyomooyo.out","w",stdout);
 scanf("%d%d",&n,&k);
 for(int i=1;i<=n;i++)
  scanf("%s",s[i]+1);
 while(1)
 {
  memset(vis,0,sizeof(vis));
  bool flag=false;
  for(int i=1;i<=n;i++)
   for(int j=1;j<=10;j++)
    if((!vis[i][j])&&s[i][j]!='0')
	{
	 int cnt=dfs(i,j,s[i][j]);
	 if(cnt>=k)
	 {
	  for(set<node>::iterator it=se.begin();it!=se.end();it++)
	   s[(*it).x][(*it).y]='0';
	  flag=true;
	 }
	 se.clear();
	}
  for(int i=n-1;i>=1;i--)//模拟下落过程
   for(int j=1;j<=10;j++)
   {
    if(s[i][j]=='0')continue;
    int x=i,y=j;
    while(s[x+1][y]=='0')
     swap(s[x][y],s[x+1][y]),x++;
   }
  if(!flag)break;
 }
 for(int i=1;i<=n;i++)
  puts(s[i]+1);
 return 0;
}
```

---

