# Sudoku

## 题目描述

数独是一个非常简单的任务。一个包含 9 行和 9 列的正方形表格被分成了 9 个小的 3x3 方块，如图所示。一些单元格中写有从 1 到 9 的十进制数字。其他单元格为空。目标是以从 1 到 9 的十进制数字填充空单元格，每个单元格一个数字，使得每行、每列和每个标记的 3x3 子方块中都出现从 1 到 9 的所有数字。编写一个程序来解决给定的数独任务。

![](https://cdn.luogu.com.cn/upload/image_hosting/3zh25t4g.png)

## 样例 #1

### 输入

```
1
103000509
002109400
000704000
300502006
060000050
700803004
000401000
009205800
804000107
```

### 输出

```
143628579
572139468
986754231
391542786
468917352
725863914
237481695
619275843
854396127
```

# 题解

## 作者：LostKeyToReach (赞：6)

这是一道搜索题。

虽然我们直接搜索，不用优化也能通过此题，但我在这里讲一下位运算优化。

考虑分别用 $9$ 个二进制数来表示每行、每列、每格哪些数用过了，那么我们想给某个数 $x$ 打上标记，只需异或上 $2^{x-1}$ 即可。

代码如下：
```cpp
#include <iostream>
#include <bitset>
using namespace std;
int a[10][10];
#define bi bitset <9>
bool dfs(int h, int l);
int A[9], B[9], C[9];
void print() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            putchar(a[i][j] + '0');
        }
        putchar('\n');
    }
}
bool solve() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (a[i][j] != 0) {
                int num = a[i][j] - 1;
                A[i] ^= (1 << num);
                B[j] ^= (1 << num);
                C[i / 3 * 3 + j / 3] ^= (1 << num);
            }
        }
    }
    return dfs(0, 0);
}
bool dfs(int h, int l) {
    if (h == 9) return 1;
    if (l == 9) {
        return dfs(h + 1, 0);
    }
    if (a[h][l] != 0) {
        return dfs(h, l + 1);
    }
    for (int i = 0; i < 9; i++) {
        int idx = h / 3 * 3 + l / 3;
        if ((A[h] & (1 << i)) == 0 && (B[l] & (1 << i)) == 0 && (C[idx] & (1 << i)) == 0) {
            a[h][l] = i + 1;
            A[h] ^= (1 << i);
            B[l] ^= (1 << i);
            C[h / 3 * 3 + l / 3] ^= (1 << i);
            if (dfs(h, l + 1)) return 1;
            a[h][l] = 0;
            A[h] ^= (1 << i);
            B[l] ^= (1 << i);
            C[h / 3 * 3 + l / 3] ^= (1 << i);
        }
    }
    return 0;
}
int t;
int main() {
    ios::sync_with_stdio(0);
    cin >> t;
    while (t--) {
        for (int i = 0; i < 9; i++) A[i] = B[i] = C[i] = 0;
        for (int i = 0; i < 9; i++) {
            string s;
            cin >> s;
            for (int j = 0; j < 9; j++) {
                a[i][j] = s[j] ^ 48;
            }
        }
        if (solve()) {
            print();
        }
    }
    return 0;
}
```

---

## 作者：zhlzt (赞：6)

### 题解
众所周知，Dancing Links 是一种优美的数据结构，而其对应的 X 算法可以用来解决 [P4929](https://www.luogu.com.cn/problem/P4929) 这样的精确覆盖问题。

当了解了精确覆盖问题中 Dancing Links 的使用方法，这题也就很简单了，考虑到需要满足如下条件：

- 点：每一点恰填一个数。
- 行：每一行中每种数恰填一个。
- 列：每一列中每种数恰填一个。
- 宫：每一宫中每种数恰填一个。

于是我们可以构造一个 $729$ 行 $324$ 列的矩阵，其中每行有 $4$ 个点为 $1$。

接下来就是精确覆盖问题了，具体可以参考[这篇博客](https://www.luogu.com.cn/article/53by9ud1)，应该说是挺详尽的。

### 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
struct dlx{ 
    int row,col;
	int left,right,up,down;
}node[3000]; int cntd=0; 
int row[750],ans[100],cnt[350],dp[10][10];
void initnode(int m){ 
	for(int i=0;i<=m;i++){
		node[i].left=i-1; node[i].right=i+1; 
		node[i].up=i; node[i].down=i;
	} 
	memset(row,0,sizeof row);
	memset(cnt,0,sizeof cnt);
	node[0].left=m; node[m].right=0; cntd=m;
}
void add(int p,int q){ 
    ++cntd; cnt[q]++;
	node[cntd].row=p; node[cntd].col=q;
	node[cntd].up=node[q].up; node[cntd].down=q;
	node[node[q].up].down=cntd; node[q].up=cntd;
	if(row[p]==0){ 
	    row[p]=cntd;
		node[cntd].left=cntd;
		node[cntd].right=cntd;
	} else{
		node[cntd].left=node[row[p]].left;
		node[cntd].right=row[p]; 
		node[node[cntd].left].right=cntd; 
		node[node[cntd].right].left=cntd; 
	}
} 
void remove(int p){ 
	for(int i=node[p].down;i!=p;i=node[i].down){
		for(int j=node[i].right;j!=i;j=node[j].right){
			node[node[j].up].down=node[j].down; 
			node[node[j].down].up=node[j].up; 
			cnt[node[j].col]--; 
		} 
	} 
	node[node[p].right].left=node[p].left;
	node[node[p].left].right=node[p].right;
}
void resume(int p){
	node[node[p].right].left=p; 
	node[node[p].left].right=p; 
	for(int i=node[p].down;i!=p;i=node[i].down){
		for(int j=node[i].right;j!=i;j=node[j].right){
			node[node[j].up].down=j; 
			node[node[j].down].up=j; 
			cnt[node[j].col]++; 
		} 
	} 
}
bool dfs(int dep){ 
	if(node[0].right==0){ 
		for(int i=1;i<dep;i++){
			int p=(ans[i]-1)/9/9+1,q=(ans[i]-1)/9%9+1;
			int d=(ans[i]-1)%9+1; dp[p][q]=d; 
		} 
		return 1; 
	} 
	int p=node[0].right; 
	for(int i=node[0].right;i!=0;i=node[i].right){
		if(cnt[i]<cnt[p]) p=i; 
	}
	remove(p); 
	for(int i=node[p].down;i!=p;i=node[i].down){
		ans[dep]=node[i].row; 
		for(int j=node[i].right;j!=i;j=node[j].right){
			remove(node[j].col); 
		} if(dfs(dep+1)) return 1;
		for(int j=node[i].right;j!=i;j=node[j].right){
			resume(node[j].col);
		} 
	} 
	resume(p); return 0; 
}
int main(){
    int t;scanf("%d",&t);
    while(t--){
		cntd=0; initnode(324);
    	for(int i=1;i<=9;i++){
    		for(int j=1;j<=9;j++){
    			char ch;cin>>ch;
    			int p=ch^48;
    			for(int k=1;k<=9;k++){ 
    				if(p!=k&&p!=0) continue; 
    				int p1=81*0+9*(i-1)+j; add(81*(i-1)+9*(j-1)+k,p1);
    				int p2=81*1+9*(i-1)+k; add(81*(i-1)+9*(j-1)+k,p2);
    				int p3=81*2+9*(j-1)+k; add(81*(i-1)+9*(j-1)+k,p3);
    				int n=3*((i-1)/3)+(j-1)/3+1;
    				int p4=81*3+9*(n-1)+k; add(81*(i-1)+9*(j-1)+k,p4);
    			}
    		}
    	} 
    	dfs(1); 
    	for(int i=1;i<=9;i++){
    		for(int j=1;j<=9;j++) printf("%d",dp[i][j]);
    		printf("\n"); 
    	} 
    }
	return 0; 
}
```

---

## 作者：FRZ_29 (赞：4)

# Sudoku

来自蓝书  
[也许更好的阅读体验](https://www.cnblogs.com/FRZ29/p/18327650)
## 思路

优化搜索顺序，位运算常数优化。

### 优化搜索顺序

数独问题的搜索很简单，“搜索状态”就是每个位置上填了什么数。在每个状态下，选择一个未填位置，检查那些填入仍能满足数独条件（合法）的数字。构成的新的局面即为该状态的“分支”。  

足够暴力的写法为依次对每个位置进行搜索，但盲目搜索的效率肯定相当低，让人类玩数独的话，我们会先填已经能唯一确定的位置，这样就可以减少其他位置的合法数字，使数独的复杂程度降低。  

在搜索中，我们也可以采取类似的策略，从**能填的合法数字最少的位置向下搜索**，这样就能大大减少分支数量，也就是优化顺序的剪枝方法。

### 常数优化

1. 对于每行每列每个九宫格，分别用一个 9 位二进制保存有那些数能用。
2. 对于每个数字，把它所在的行、列、九宫格的三个二进制数做按位与运算，就可以知道该位置可以填那些数，再用 lowbit 运算就可以将能填的数字取出。
3. 当一个位置上填上某个数后，把该位置所在行、列、九宫格的二进制数对应位改为 0 更新装态，回溯时改为 1 还原现场。可以联想利用异或的性质。
4. 用 lowbit 运算预处理每个 9 位二进制数有几位 1 ，即可快速确定能填的合法数字最少的位置
5. 打表确定用 lowbit 运算取出来的位置对应的数字

代码
```cpp
#include <iostream>
#include <cstdio>

using namespace std;

const int N = 1 << 9;

int cnt[N], f[N], T, sukodu[9][9], x[9], y[9], z[9];
char c;

int gon(int i, int j) { return i / 3 * 3 + j / 3; }

int get_cnt(int i)
{
    int ans = 0;
    while(i)
        ans++, i -= (i & -i);
    return ans;
}

void work(int i, int j, int v)
{
    x[i] ^= (1 << v);
    y[j] ^= (1 << v);
    z[gon(i, j)] ^= (1 << v);
}

bool dfs(int tot)
{
    if (!tot) return true;

    int t = 10, nx, ny;

    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
        {
            if (!sukodu[i][j])
            {
                int w = x[i] & y[j] & z[gon(i, j)]; // 优化2
                if (cnt[w] < t)
                    nx = i, ny = j, t = cnt[w];
            }
        }

    int w = x[nx] & y[ny] & z[gon(nx, ny)];
    while(w)
    {
        int now = f[w & -w];
        sukodu[nx][ny] = now + 1;
        work(nx, ny, now);
        if (dfs(tot - 1)) return true;

        sukodu[nx][ny] = 0;
        work(nx, ny, now);
        w -= w & -w;
    } 
    return false;
}

int main()
{
    for (int i = 0; i < N; i++) cnt[i] = get_cnt(i); //优化4
    for (int i = 0; i < 9; i++) f[1 << i] = i;  // 优化5

    scanf("%d", &T);
    while(T--)
    {
        int tot = 0;
        for (int i = 0; i < 9; i++) x[i] = y[i] = z[i] = N - 1; // 优化1

        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++)
            {
                cin >> c;
                sukodu[i][j] = c - '0';
                if (sukodu[i][j]) work(i, j, sukodu[i][j] - 1); // 优化3
                else tot++;
            }

        if (dfs(tot))
            for (int i = 0; i < 9; i++)
            {
                for (int j = 0; j < 9; j++)
                    printf("%d", sukodu[i][j]);
                puts("");
            }
    }
    return 0;
}
```
### 后记

这道题目数据很水，完全不需要优化就能过，这很明显。  

但作为蓝书的题目，我想应该要有蓝书的写法，我是蒟蒻，我写不来蓝书的方法，我想也有人不会，所以发出来给像我这样的蒟蒻参考。

位运算优化会快很多，我的代码实测为 4ms ，比大多数题解快一些。

---

## 作者：niuzh (赞：3)

### 思路

由于数独最多只有 $81$ 个格子，所以可以用暴搜。

考虑定义三个数组，分别维护行，列，每个 $3 \times 3$ 的方格里有哪几个数字出先过。在输入的时候就可以先预处理好已经填好的，其余在搜索里改变。

搜索时可以从上往下搜，从左往右搜，再用一个 $flag$  记录有没有找到答案，然后枚举每一个格子能填哪个数，搜到最后直接输出。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=10+10;
int a[N][N];
bool h[N][N],l[N][N],m[N][N],flag;
void init()
{
	memset(h,0,sizeof(h));
	memset(l,0,sizeof(l));
	memset(m,0,sizeof(m));
	memset(a,0,sizeof(a));
	flag=0;
}
void dfs(int x,int y)
{
	if (x==9)//搜索玩，输出
	{
		for (int i=0; i<9; i++)
		{
			for (int j=0; j<9; j++)
			{
				cout<<a[i][j];
			}
			cout<<'\n';
		}
		flag=1;
	}
	if(flag)//已有答案，返回
	{
		return;
	}
	if (a[x][y])//已经有数，跳过
	{
		dfs(x,y+1);
		return;
	}
	if (y==9)//下一行
	{
		dfs(x+1,0);
		return;
	}
	int id=x/3*3+y/3;//在m中当前宫的下标
	for (int i=1; i<=9; i++)
	{
		if (!h[x][i]&&!l[y][i]&&!m[id][i])
		{
			a[x][y]=i;
			h[x][i]=l[y][i]=m[id][i]=true;
			dfs(x,y+1);
			a[x][y]=0;
			h[x][i]=l[y][i]=m[id][i]=false;//回溯
		}
	}
}
int main()
{
	int T;
	cin>>T;
	while (T--)
	{
		init();
		char c;
		for (int i=0; i<9; i++)
		{
			for (int j=0; j<9; j++)
			{
				cin>>c;
				if (c!='0')
				{
					a[i][j]=c-'0';
					h[i][c-'0']=l[j][c-'0']=m[i/3*3+j/3][c-'0']=1;//预处理
				}
			}
		}
		dfs(0,0);
	}
	return 0;
}
```

---

## 作者：be_RISK (赞：2)

怎没人写 dancing link X？
## 思路
这题和 [P1784](https://www.luogu.com.cn/problem/P1784) 一样，对：

- 点：每一个点只能填一个数
- 行：每行每种数只能填恰好一个
- 列：每列每种数只能填恰好一个
- 宫：每宫每种数只能填恰好一个

使用 DLX 算法进行精确覆盖，如果不懂 DLX，请戳[这里](https://oi-wiki.org/search/dlx/)。

还有一点，就是这题输入比较特殊，在代码中给出。
## code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=114514;
int n,m,cnt,cn;
int u[N],d[N],l[N],r[N];
int row[N],col[N];
int h[N];
int s[N];
int ans[N];
int a[10][10];
void init(){
	for(int y=0;y<=m;y++){
		r[y]=y+1;
		l[y]=y-1;
		u[y]=d[y]=y;
	}
	r[m]=0;
	l[0]=m;
	memset(h,-1,sizeof(h));
	memset(s,0,sizeof(s));
	cnt=m+1;
}
void link(int x,int y){
	s[y]++;
	row[cnt]=x;
	col[cnt]=y;
	u[cnt]=y;
	d[cnt]=d[y];
	u[d[y]]=cnt;
	d[y]=cnt;
	if(h[x]<0)h[x]=r[cnt]=l[cnt]=cnt;
	else{
		r[cnt]=h[x];
		l[cnt]=l[h[x]];
		r[l[h[x]]]=cnt;
		l[h[x]]=cnt;
	}cnt++;
}
void removee(int y){
	r[l[y]]=r[y];
	l[r[y]]=l[y];
	for(int i=d[y];i!=y;i=d[i]){
		for(int j=r[i];j!=i;j=r[j]){
			u[d[j]]=u[j];
			d[u[j]]=d[j];
			s[col[j]]--;
		}
	}
}
void resume(int y){
	for(int i=u[y];i!=y;i=u[i]){
		for(int j=l[i];j!=i;j=l[j]){
			u[d[j]]=j;
			d[u[j]]=j;
			s[col[j]]++;
		}
	}	
	r[l[y]]=y;
	l[r[y]]=y;
}
bool dance(int dep){
	if(r[0]==0){
		for(int i=0,x,y,v;i<dep;i++){
			x=(ans[i]-1)/9/9;
			y=(ans[i]-1)/9%9;
			v=(ans[i]%9);
			a[x][y]=v?v:9;
		}
		return 1;
	}
	int y=r[0];
	for(int i=r[0];i!=0;i=r[i])if(s[i]<s[y])y=i;
	removee(y);
	for(int i=d[y];i!=y;i=d[i]){
		ans[dep]=row[i];
		for(int j=r[i];j!=i;j=r[j])removee(col[j]);
		if(dance(dep+1)==1)return 1;
		for(int j=l[i];j!=i;j=l[j])resume(col[j]);
	}
	resume(y);
	return 0;
}
int T; 
int main(){
	cin>>T;
	while(T--){
		n=729;
		m=324;
		init();//初始化
		for(int i=0;i<9;i++){
			for(int j=0;j<9;j++){
			    char c;
			    cin>>c;
			    a[i][j]=c-'0';//利用cin输入char解决输入问题
			}
		}
		for(int i=0;i<9;i++){
			for(int j=0;j<9;j++){
			    int x=a[i][j];
				for(int k=1;k<=9;k++){
					if(x!=0&&x!=k)continue;
						int t=i*9*9+j*9+k;//建链
						link(t,i*9+j+1);//点
						link(t,81*1+i*9+k);//行
						link(t,81*2+j*9+k);//列
						link(t,81*3+(i/3*3+j/3)*9+k);//宫
					
				}
			}
		}
		dance(0);//开始舞蹈
		for(int i=0;i<=8;i++){//输出
			for(int j=0;j<=8;j++)printf("%d",a[i][j]);
			puts("");
		}
	}
	return 0;
}//~*完结撒花*~
```

---

## 作者：sdsswyd (赞：1)

**[题目传送门](https://www.luogu.com.cn/problem/P10481)**

# 题目考察内容

搜索 DFS。

## DFS 方法

1. 如果已填的个数 $q$ $\ge$ $81$ ，输出保存的 $a$ 数组，将 $flag$ $\gets$ $1$，然后结束。
1. 从第 $1$ 个格子枚举到第 $81$ 个格子，若该格子已经被填充过，则开启下一轮循环，如果 $flag$ 是 $1$ 则返回，否则从 $1$ 到 $9$ 进行枚举，之中还要进行 $flag$ 判断，如果都填不进去，可别忘记回溯哟。

## Code

[Look this.](https://www.luogu.com.cn/paste/lga1sg6d)

---

## 作者：__qkj__ (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P10481)
## 解题思路
暴搜。

如果输入的非零，把行、列、单元格的当前数字记录一下，防止之后重复算；如果输入的是零，让 $tp\gets tp+1$（$tp$ 表示需要搜的个数），记录位置。

至于 dfs 内容吗：
- 当 $fl=1$（已经搜到正确答案），直接 `return`；
- 当 $t=tp+1$（搜到正确答案），输出，$fl\gets 1$，`return`；
- 否则，$i$ 从 $1$ 到 $9$ 尝试，记录方案，搜索下一层，别忘了回溯。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
bool f[20][20],ff[20][20],fff[20][20],fl;
int a[20][20],x[110],y[110],tp,g[20][20];
void dfs(int t)
{
	if(fl)return;
	if(t==tp+1)
	{
		for(int i=1;i<=9;i++)
		{
			for(int j=1;j<=9;j++)
				cout<<a[i][j];
			cout<<'\n';
		}
		fl=1;
		return;
	}
	for(int i=1;i<=9;i++)
		if(!f[x[t]][i]&&!ff[y[t]][i]&&!fff[g[x[t]][y[t]]][i])
		{
			f[x[t]][i]=1;
			ff[y[t]][i]=1;
			fff[g[x[t]][y[t]]][i]=1;
			a[x[t]][y[t]]=i;
			dfs(t+1);
			if(fl)return;
			f[x[t]][i]=0;
			ff[y[t]][i]=0;
			fff[g[x[t]][y[t]]][i]=0;
		}
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin>>t;
	while(t--)
	{
		fl=tp=0;
		memset(f,0,sizeof f);
		memset(ff,0,sizeof ff);
		memset(fff,0,sizeof fff);
		memset(a,0,sizeof a);
		memset(x,0,sizeof x);
		memset(y,0,sizeof y);
		memset(g,0,sizeof g);
		for(int i=1;i<=9;i++)
			for(int j=1;j<=9;j++)
				g[i][j]=(i-1)/3*3+(j-1)/3+1;//单元格
		for(int i=1;i<=9;i++)
			for(int j=1;j<=9;j++)
			{
				char c;
				cin>>c;
				a[i][j]=c-'0';
				if(a[i][j])
				{
					f[i][a[i][j]]=1;
					ff[j][a[i][j]]=1;
					fff[g[i][j]][a[i][j]]=1;
				}
				else
				{
					tp++;
					x[tp]=i;
					y[tp]=j;
				}
			}
		dfs(1);
	}
	return 0;
}

```

---

## 作者：Z_AuTwT (赞：0)

~~明显的一道舞蹈链。~~

但是此题数据范围较小，可以使用搜索通过。

对于每一个空位，我们可以枚举 $[1,2,…,9]$ 的数字分别进行搜索。

## CODE：

```c++
#include<bits/stdc++.h>
using namespace std;
bool flag;
int g[10][10]={{0,0,0,0,0,0,0,0,0,0},{0,1,1,1,2,2,2,3,3,3},{0,1,1,1,2,2,2,3,3,3},{0,1,1,1,2,2,2,3,3,3},{0,4,4,4,5,5,5,6,6,6},{0,4,4,4,5,5,5,6,6,6},{0,4,4,4,5,5,5,6,6,6},{0,7,7,7,8,8,8,9,9,9},{0,7,7,7,8,8,8,9,9,9},{0,7,7,7,8,8,8,9,9,9}};//标记当前位置是哪一宫
int l[10][10],h[10][10],mat[10][10],gg[10][10];
void dfs(int x,int y){
    if(x==9&&y==10){//搜索边界
    	flag=true;
        for(int i=1;i<=9;i++){
            for(int j=1;j<=9;j++){
                printf("%d",mat[i][j]);
            }puts("");
        }
        return;
    }if(mat[x][y]!=0){//当前位置已有数字
        int nx=x,ny=y;
        ny++;
        if(nx!=9&&ny>=10){
            nx++;
            ny=1;
        }
		dfs(nx,ny);
    }else{//当前位置需填充数字
        for(int i=1;i<=9;i++){
        	if(flag==true) return;
            if(h[x][i]==0&&l[y][i]==0&&gg[g[x][y]][i]==0){
                h[x][i]=1;
                l[y][i]=1;
                gg[g[x][y]][i]=1;
                mat[x][y]=i;
                int nx=x,ny=y;
                ny++;
                if(nx!=9&&ny==10){
                    nx++;
                    ny=1;
                }
				dfs(nx,ny);
                h[x][i]=0;
                l[y][i]=0;
                gg[g[x][y]][i]=0;
                mat[x][y]=0;
            }
        }
    }
}
int main(){
    int t;
    cin>>t;
    while(t--){
        memset(l,0,sizeof(l));//记得清空
        memset(h,0,sizeof(h));
        memset(gg,0,sizeof(gg));
        for(int i=1;i<=9;i++){
            for(int j=1;j<=9;j++){
                char x;
                cin>>x;
                mat[i][j]=x-'0';
                l[j][mat[i][j]]=1;
                h[i][mat[i][j]]=1;
                gg[g[i][j]][mat[i][j]]=1;
            }
        }dfs(1,1);
        flag=false;
    }
}
```

---

## 作者：zhchz (赞：0)

## 思路
搜索。
1. 初始化、读入。
2. 选择一个空位置进行填充。
3. 对于每个可能的数字，使用 `check` 函数检查在该位置放置该数字是否违反数独的规则。如果某个数字可行，那么将其放置在当前位置。
5. 递归地继续填充下一个空位置。
6. 如果在某个位置上，所有可能的数字都无法放置，那么回溯到上一个位置，并尝试其他数字。
7. 当所有位置都被填充，且符合数独规则时，得到一个解决方案。
## Code
```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<math.h>
#include<string>
#include<string.h>
using namespace std;

char ch;
int board[9][9];// 数独盘面

inline void read(char &x){
	x=getchar();
	while(!isdigit(x))
		x=getchar();
	return;
}

// 输出
void outt(){
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++)
			printf("%d",board[i][j]);
		printf("\n");
	}
	return;
}

// 检查放置数字 num 是否合法
bool check(int x,int y,char num){
	for(int i=0;i<9;i++)
		if(board[x][i]==num)return 0;// 检查行
	for(int i=0;i<9;i++)
		if(board[i][y]==num)return 0;// 检查列
	// 检查子方块
	int stx=x-x%3,sty=y-y%3;
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			if(board[i+stx][j+sty]==num)
				return 0;
	return 1;
}

// 使用回溯算法尝试解决数独
bool solve(){
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			if(board[i][j]==0){ // 如果当前单元格为空
				for(int num=1;num<=9;num++){
					if(check(i,j,num)){ // 检查是否可以在当前位置放置 num
						board[i][j]=num;
						if(solve())return 1;// 如果后续的解法成功，返回 true
						board[i][j]=0;// 如果后续的解法失败，回溯
					}
				}
				return 0;// 如果1-9都不行，返回 false
			}
		}
	}
	return 1;// 如果所有单元格都填充了数字，返回 true
}

int main(){
	int T;
	cin>>T;
	while(T--){
		for(int i=0;i<9;i++)
			for(int j=0;j<9;j++){
				read(ch);// 读取
				board[i][j]=ch-'0';
			}
		solve();// 解决数独
		outt();// 输出解决方案
	}
	return 0;
}
```

---

## 作者：Cute__yhb (赞：0)

## 思路

搜索。

用三个数组分别存行、列、$3\times 3$ 方块中出现的数，如果这个数在这三个数组中都没有出现，那么就可以选。

搜索时，如果这一行搜完了，就去下一行的第一个。

如果搜到了 $n+1$ 行，就代表有解。

注意回溯。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define INF 0x3f3f3f3f
#define re register
#define ri register int
#define rll register long long
#define ld long double
#define endl '\n'
#define fi first
#define se second
#define pii pair<int,int>
#define p_q priority_queue
#define iter iterator
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define nep(i,a,b) for(int i=(a);i>=(b);i--)
#define popcount __builtin_popcount
#define pb push_back
#define mem(a,x) memset((a),x,sizeof(a))
#define eps 1e-8
#define oper operator
#define mk make_pair
int a[15][15],n=9;
int h[15][15],l[15][15],f[5][5][15];//行、列、3*3
bool flag=0;//是否有解
void dfs(int x,int y){
	if(flag==1) return ;//有解，结束
	if(x==n+1&&y==1){//搜完了
		flag=1;//有解
		for(int i=1;i<=n;i++){//输出
			for(int j=1;j<=n;j++){
				cout<<a[i][j];
			}
			puts("");
		}
		return ;
	}
	if(a[x][y]!=0){//已经有数
		if(y==n) dfs(x+1,1);
		else dfs(x,y+1);
		return ;
	}
	for(int i=1;i<=9;i++){//搜索
		if(h[x][i]==0&&l[i][y]==0&&f[(x-1)/3][(y-1)/3][i]==0){//可选
			h[x][i]=1;//打标记
			l[i][y]=1;
			f[(x-1)/3][(y-1)/3][i]=1;
			a[x][y]=i;
			if(y==n) dfs(x+1,1);
			else dfs(x,y+1);//搜索
			h[x][i]=0;
			l[i][y]=0;
			f[(x-1)/3][(y-1)/3][i]=0;
			a[x][y]=0;//回溯
		}
	}
}
void solve(){
	flag=0;
	memset(h,0,sizeof h);//赋初值
	memset(l,0,sizeof l);
	memset(f,0,sizeof f);
	memset(a,0,sizeof a);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			char c;
			cin>>c;
			a[i][j]=c-'0';
			if(a[i][j]==0) continue;//没有数
			h[i][a[i][j]]=1;//打标记
			l[a[i][j]][j]=1;
			f[(i-1)/3][(j-1)/3][a[i][j]]=1;
		}
	}
	dfs(1,1);//搜索
}
int main(){
	int t;
	cin>>t;
	while(t--) solve();
    return 0;
}
```

---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P10481)

## 思路

看到是数独问题，可以直接想到搜索解决。我们定义三个数组，分别存储每行的一个数、每列的一个数、每宫的一个数是否用过。为了方便解释，我们定义三个维度为行、列、宫。读入数据后记录三个维度上用过的数并存图，然后进行搜索。

搜索时记录一个变量 ``flag`` 用以记录是否找到方案，找到了就退出。一行一行向右搜，如果到头了就搜下一行的第一个位置。当前位置有值就跳过不搜。枚举每个数字，把三个维度上都没用过的数字放进图，然后搜索。

搜到第一个不存在的行就说明找到一种方案了，输出答案并退出。

- 别忘回溯。

- 多组测试数据，别忘清空。

- 可以尝试从 $(0,0)$ 开始存图，这样容易计算。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
char readc(){
	char c=getchar();
	while(c=='\n'||c=='\r'||c==' ')c=getchar();
	return c;
}
#define gong(i,j) (i)/3*3+(j)/3//用宏定义计算宫，减少码量。
const int N=15;
bool h[N][N],l[N][N],g[N][N],flag;
int a[N][N];
void clear(){
	flag=0;
	memset(h,0,sizeof h);
	memset(l,0,sizeof l);
	memset(g,0,sizeof g);
	memset(a,0,sizeof a);
	return ;
}
void dfs(int x,int y){
	if(flag)return ;
	if(y==9){
		dfs(x+1,0);
		return ;
	}
	if(a[x][y]){
		dfs(x,y+1);
		return ;
	}
	if(x==9){
		flag=1;
		for(int i=0;i<9;++i){
			for(int j=0;j<9;++j)putchar(a[i][j]^48);//相当于 a[i][j]+'0'。
			putchar('\n');
		}
		return ;
	}
	for(int i=1;i<=9;++i){
		if(!h[x][i]&&!l[y][i]&&!g[gong(x,y)][i]){
			h[x][i]=l[y][i]=g[gong(x,y)][i]=1;
			a[x][y]=i;
			dfs(x,y+1);
			a[x][y]=0;
			h[x][i]=l[y][i]=g[gong(x,y)][i]=0;
		}
	}
	return ;
}
signed solution(){
    int T;
    cin>>T;
	while(T--){
		clear();
		for(int i=0;i<9;++i){
			for(int j=0;j<9;++j){
				char ch=readc();
				int c=ch-'0';
				h[i][c]=l[j][c]=g[gong(i,j)][c]=1;
				a[i][j]=c;
			}
		}
		dfs(0,0);
	}
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/160549204)

---

## 作者：qinmingze (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P10481)

### 思路

本题是一道很明显的搜索题。

在搜索时，我们需要对每一个位置进行枚举，同时对有数字的位置进行标记，防止重复处理。同时在搜索时，如果当前行搜索完了，需要向下一行第一个进行搜索。最后输出就可以了。

```cpp
#include <bits/stdc++.h>

using namespace std;

int ans[10][10];

bool row[10][10], col[10][10], square[10][10];

bool flag;

void dfs(int x, int y) {
    if (flag) {
        return;
    }
    if (x == 9) {//找到答案。
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                cout << ans[i][j];
            }
            cout << endl;
        }
        flag = true;
        return;
    }
    if (y == 9) {//搜索下一行。
        dfs(x + 1, 0);
        return;
    }
    if (ans[x][y]) {//当前位置有数字，搜索下一个位置。
        dfs(x, y + 1);
        return;
    }
    int id = x / 3 * 3 + y / 3;
    for(int i = 1; i <= 9; i++){
        if(!row[x][i] && !col[y][i] && !square[id][i]){//可以放置。
            ans[x][y] = i;
            row[x][i] = col[y][i] = square[id][i] = true;//更新。
            dfs(x, y + 1);//向下搜索。
            ans[x][y] = 0;//回溯。
            row[x][i] = col[y][i] = square[id][i] = false;
        }
    }
}
int main() {
    int T;
    cin >> T;
    while(T--){
        char c;
        memset(row, 0, sizeof row);
        memset(col, 0, sizeof col);
        memset(square, 0, sizeof square);
        memset(ans, 0, sizeof ans);
        flag = false;
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                cin >> c;
                if (c != '0') {
                    int id = i / 3 * 3 + j / 3;//对应子方块编号。
                    ans[i][j] = c - '0';//标记。
                    row[i][c - '0'] = col[j][c - '0'] = square[id][c - '0'] = true;//对数字进行标记。
                }
            }
        }
        dfs(0, 0);
    }
    
    return 0;
}
```

---

