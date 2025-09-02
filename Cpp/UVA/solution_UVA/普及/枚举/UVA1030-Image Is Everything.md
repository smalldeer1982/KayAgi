# Image Is Everything

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=245&page=show_problem&problem=3471

[PDF](https://uva.onlinejudge.org/external/10/p1030.pdf)

# 题解

## 作者：残阳如血 (赞：3)

# 思路分析
## 猜想
我们可以在题目中看出一下几个突破口：
- 能“看穿”的位置所对应的单位立方体是**一定不存在**的。
- 如果前视图的右上角的颜色 $A$ 和顶视图的的右下角颜色 $B$ 不同，那么对应的格子就**一定不存在**。

在删除这个立方体后，我们还可以发现，挖去立方体的左侧和 $B$ 左侧的颜色不同。这样，我们又能删除一个新的立方体，并且暴露出新的表面。**当无法继续删除时，剩下的立方体就是质量最大的物体。**
## 证明
为什么上面的猜想是正确的呢？

首先，不难证明第一次删除行为是必要的（即被删除的那个立方体不可能存在于任意可行解中），因为只要不删除这个立方体，**对应的两个视图的“矛盾”将会一直存在**；接下来，我们可以用数学归纳法来证明。我们假设算法的前 $k$ 次删除时必要的，那么第 $k+1$ 次删除是否也是必要的呢？由刚才的推理，**我们不能通过继续删除立方体来消除矛盾**，而由归纳假设，已经删除的立方体也不能回复，因此矛盾无法消除。
# 代码实现
```cpp
#include <bits/stdc++.h>
#define rep(i, n) for (int i = 0; i < (n); i++)
using namespace std;
const int MAXN = 15;
int n;
char pos[MAXN][MAXN][MAXN], view[6][MAXN][MAXN];
char read() {
	char ch;
	while (true) {
		ch = getchar();
		if ((ch >= 'A' && ch <= 'Z') || ch == '.') return ch;
	}
}
void get(int op, int i, int j, int len, int &x, int &y, int &z) {
	switch (op) {
	case 0:
		x = len, y = j, z = i;
		break;
	case 1:
		x = n - 1 - j, y = len, z = i;
		break;
	case 2:
		x = n - 1 - len, y = n - 1 - j, z = i;
		break;
	case 3:
		x = j, y = n - 1 - len, z = i;
		break;
	case 4:
		x = n - 1 - i, y = j, z = len;
		break;
	case 5:
		x = i, y = j, z = n - 1 - len;
		break;
	}
}
int main() {
	while (scanf("%d", &n) == 1 && n) {
		rep(i, n) rep(k, 6) rep(j, n) view[k][i][j] = read();
		rep(i, n) rep(j, n) rep(k, n) pos[i][j][k] = '#';
		rep(k, 6) rep(i, n) rep(j, n)
			if (view[k][i][j] == '.')
				rep(p, n) {
				int x, y, z;
				get(k, i, j, p, x, y, z);
				pos[x][y][z] = '.';
			}
		while (true) {
			bool done = true;
			rep(k, 6) rep(i, n) rep(j, n)
				if (view[k][i][j] != '.') {
					rep(p, n) {
						int x, y, z;
						get(k, i, j, p, x, y, z);
						if (pos[x][y][z] == '.') continue;
						if (pos[x][y][z] == '#') {
							pos[x][y][z] = view[k][i][j];
							break;
						}
						if (pos[x][y][z] == view[k][i][j]) break;
						pos[x][y][z] = '.';
						done = false;
					}
				}
			if (done) break;
		}
		int ans = 0;
		rep(i, n) rep(j, n) rep(k, n)
			if (pos[i][j][k] != '.') ans++;
		printf("Maximum weight: %d gram(s)\n", ans);
	}
	return 0;
}
```

---

## 作者：Onana_in_XMFLS (赞：2)

**刘汝佳大法好！**

这个问题有**亿**点棘手，不过我们可以找到突破口：

- **能被“看穿”的位置所对的所有单位立方体一定都不存在**。

- **如果前视图的右上角颜色 $A$ 和顶视图的右下角颜色 $B$ 不同，那么对应的格子一定不存在。**

![](https://cdn.luogu.com.cn/upload/image_hosting/yz8jzbmn.png)
			（图114514）

然后我们在做了第二条后，会有一些奇奇怪怪的发现：

**$C$ 和 $D$ 的颜色不同（见图114514）。**

这样，我们就可以又删除一个新的立方体，并暴露出新的表面。当无法继续删除后，剩下的立方体就是重量最大的。

下面是对上述结论的证明：

- 首先，第一次删除肯定是**必要的**。

- 其次，假设算法的前 $k$ 次删除都是**必要的**，那么 $k+1$ 次是否是**必要的**？

由上述推理，我们将不能通过继续删除立方体来消除矛盾，而由归纳假设，已经删除的立方体不能恢复，所以矛盾无法消除。

证毕。

```cpp
#include<bits/stdc++.h>
#define LL long long
#define ULL unsigned long long
#define LD long double
#define rep(i,n) for(int i = 0;i < (n);++i)
#define mem(x) memset((x),(0),(sizeof(x)))
using namespace std;
int n;
char pos[10][10][10];
char view[6][10][10];
inline void get(int k,int i,int j,int len,int &x,int &y,int &z)
{
	if(k == 0) x=len,y=j,z=i;
	else if(k == 1) x=n-1-j,y=len,z=i;
	else if(k == 2) x=n-1-len,y=n-1-j,z=i;
	else if(k == 3) x=j,y=n-1-len,z=i;
	else if(k == 4) x=n-1-i,y=j,z=len;
	else if(k == 5) x=i,y=j,z=n-1-len;
}
inline LL read()
{
	LL x=0,f=1;
	char ch = getchar();
	while(!isdigit(ch)) {if(ch == '-') f = -1;ch = getchar();}
	while(isdigit(ch)) {x=x*10+ch-48;ch=getchar();}
	return f*x;
}
int main(int argc,char *argv[])
{ 
	//freopen("data.in","r",stdin);
	//freopen("data.out","w",stdout);
	while(scanf("%d",&n) == 1 && n)
	{
		rep(i,n) rep(k,6) rep(j,n) cin>>view[k][i][j];
		rep(i,n) rep(j,n) rep(k,n) pos[i][j][k] = '#';
		rep(k,6) rep(i,n) rep(j,n) 
			if(view[k][i][j] == '.')
				rep(p,n)
				{
					int x,y,z;
					get(k,i,j,p,x,y,z);
					pos[x][y][z] = '.';
				}
		while(1)
		{
			bool done = true;
			rep(k,6) rep(i,n) rep(j,n)
				if(view[k][i][j] != '.')
				{
					rep(p,n)
					{
						int x,y,z;
						get(k,i,j,p,x,y,z);
						if(pos[x][y][z] == '.') continue;
						if(pos[x][y][z] == '#')
						{
							pos[x][y][z] = view[k][i][j];
							break;
						}
						if(pos[x][y][z] == view[k][i][j])
							break;
						pos[x][y][z] = '.';
						done = false;
					}
				}
			if(done) break;
		}
		int ans = 0;
		rep(i,n) rep(j,n) rep(k,n)
			if(pos[i][j][k] != '.') ++ans;
		printf("Maximum weight: %d gram(s)\n",ans);
	}	
	#ifndef ONLINE_JUDGE
		printf("Time used = %.0lfms\n",((double)clock()/(double)CLOCKS_PER_SEC) * 1000.0);
	#endif
	return 0;exit(0);
}  
```

代码很短。

---

## 作者：比企谷·八幡 (赞：2)

[题目链接](https://www.luogu.org/problem/UVA1030)

首先这题的n很小。考虑暴力，要求可能的最大体积，先假设为最大。

然后根据条件，如果有两面不相同就删除。

大概时间复杂度是O（n^6）.绝对可行。

思路都很好像，感觉读入才是考察的重点。

a[i][j][k][l]表示第i行第j列第k层第l个面看到的是什么。

按照题目给的前、左、后、右、顶、底分别为0-5.


于是我们用强大的想象力读入完了。
```cpp
for(int j=1;j<=n;++j)
    for(int i=0;i<=5;++i)
	for(int k=1;k<=n;++k)
	{
		char x=read();
		if(i==1) a[j][k][1][i]=x;
		else if(i==2) a[j][1][n-k+1][i]=x;
		else if(i==3) a[j][n-k+1][n][i]=x;
		else if(i==4) a[j][n][k][i]=x;
		else if(i==5) a[1][k][n-j+1][i]=x;
		else a[n][k][j][i]=x;
	}
```


先写出判断该正方体是否删除的函数，如果有两个面不相同就删除，并且把他的6个面都传递一下。
```cpp
inline bool check(int i,int j,int k)
{
	char last=0;
	for(int l=0;l<=5;++l)
	{
		if(a[i][j][k][l]>='A'&&a[i][j][k][l]<='Z'&&!last) last=a[i][j][k][l];
		else if((a[i][j][k][l]!=last&&a[i][j][k][l])||a[i][j][k][l]=='.')
		{
			for(int m=1;m<=6;++m)
			{
				if(m==1) a[i][j][k+1][m-1]=a[i][j][k][m-1];
				else if(m==2) a[i][j+1][k][m-1]=a[i][j][k][m-1];
				else if(m==3) a[i][j][k-1][m-1]=a[i][j][k][m-1];
				else if(m==4) a[i][j-1][k][m-1]=a[i][j][k][m-1];
				else if(m==5) a[i+1][j][k][m-1]=a[i][j][k][m-1];
				else a[i-1][j][k][m-1]=a[i][j][k][m-1];
			}
			ans--;
			return false;
		}
	}
	return true;
}
```
感觉直接暴力应该就差不多过了，每次查询是否有一个需要删，如果删了就再重新查。直到没有为止。最坏的时间复杂度是O（n^6）,也就是每个都删。

但是因为有多组数据，考虑优化。

怎么优化呢，我们搜的时候其实搜了很多没有用的格子。也就是之前搜过已经成立的格子。

所以可以把可能会被删的格子入队，每次只判断队里的格子即可。

交一下，WA了，QAQ。感觉理论上没错啊。

冷静分析。没什么思路，下载数据试试。

没有数据啊，怎么办？TAT。

我们考虑对拍，但是因为暴力很麻烦，所以直接抄lrj的正解。QAQ

很好，以下是对拍的~~暴力~~正解。

```cpp
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;

#define REP(i,n) for(int i = 0; i < (n); i++)

const int maxn = 10;
int n;
char pos[maxn][maxn][maxn];
char view[6][maxn][maxn]; 

char read_char(){
	char ch;
	for(;;) {
		ch=getchar();
		if((ch >= 'A' && ch <= 'Z') || ch == '.') return ch;
	}
}

void get(int k, int i, int j, int len, int &x, int &y, int &z)
{
	if (k == 0) { x = len; y = j; z = i; }
	if (k == 1) { x = n - 1 - j; y = len; z = i; }
	if (k == 2) { x = n - 1 - len; y = n - 1 - j; z = i; }
	if (k == 3) { x = j; y = n - 1 - len; z = i; }
	if (k == 4) { x = n - 1 - i; y = j; z = len;}
	if (k == 5) { x = i; y = j; z = n - 1 - len;} 
}

int main(){
	while(scanf("%d", &n) == 1 && n){
		REP(i,n) REP(k,6) REP(j,n) view[k][i][j] = read_char();
		REP(i,n) REP(j,n) REP(k,n) pos[i][j][k] = '#'; 
		
		REP(k,6) REP(i,n) REP(j,n) if (view[k][i][j] == '.')
			REP(p,n){
				int x, y, z;
				get(k, i, j, p, x, y, z);
				pos[x][y][z] = '.';
			}
		
		for(;;){
			bool done = true;
			REP(k,6) REP(i,n) REP(j,n) if (view[k][i][j] != '.'){
				REP(p,n){
					int x, y, z;
					get(k, i, j, p, x, y, z);
					if (pos[x][y][z] == '.') continue;
					if (pos[x][y][z] == '#'){
						pos[x][y][z] = view[k][i][j];
						break;
					}
					if (pos[x][y][z] == view[k][i][j]) break;
					pos[x][y][z] = '.';
					done = false;
				}
			}
			if(done) break;
		}
		
		int ans = 0;
		REP(i,n) REP(j,n) REP(k,n)
			if (pos[i][j][k] != '.') ans ++;
		printf("Maximum weight: %d gram(s)\n", ans); 
	}
	return 0;
}
```
就这样，很愉快的找到了一组对拍数据。

3
.R. YYS .Y. RYY .Y. .R.
GRB AXS XYS RBA GYB GSB
.R. ZXR .Y. R.S .R. .Y.

答案是0,程序输出1.

先手算模拟，好难。。。

应该是3 2 1错了，咦！明明到最后什么都没有了，为什么它还有一个面不知道？

对了，因为其实如果当前格子被删，信息不一定是传递到了下一个格子，而是中间有好几个格子已经被删完了，直接看穿了好几个。

最后的AC代码

```cpp
#include<cstdio>
#include<queue>
#include<cstring>
#include<iostream>
using namespace std;
const int N=12;
int n,ans;
char a[N][N][N][6];
bool book[N][N][N],Ans[N][N][N];

struct node
{
	int x,y,z;
	node(int xi,int yi,int zi){x=xi;y=yi;z=zi;}
};
queue<node> Q;

inline char read()
{
	char c=getchar();
	while((c>'Z'||c<'A')&&c!='.') c=getchar();
	return c;
}

inline bool check(int i,int j,int k)
{
	char last=0; book[i][j][k]=false;
	for(int l=0;l<=5;++l)
	{
		if(a[i][j][k][l]>='A'&&a[i][j][k][l]<='Z'&&!last) last=a[i][j][k][l];
		else if((a[i][j][k][l]!=last&&a[i][j][k][l])||a[i][j][k][l]=='.')
		{
			for(int m=1;m<=6;++m)
			{
				if(m==1)
				{
					int K=k; while(Ans[i][j][K+1]) K++;
					a[i][j][K+1][m-1]=a[i][j][k][m-1];
					if(!book[i][j][K+1]){ Q.push(node(i,j,K+1)); book[i][j][K+1]=true;}
				} 
				else if(m==2)
				{
					int J=j; while(Ans[i][J+1][k]) J++;
					a[i][J+1][k][m-1]=a[i][j][k][m-1];
					if(!book[i][J+1][k]){ Q.push(node(i,J+1,k)); book[i][J+1][k]=true;}
				} 
				else if(m==3)
				{
					int K=k; while(Ans[i][j][K-1]) K--;
					a[i][j][K-1][m-1]=a[i][j][k][m-1];
					if(!book[i][j][K-1]){ Q.push(node(i,j,K-1)); book[i][j][K-1]=true;}
				} 
				else if(m==4)
				{
					int J=j; while(Ans[i][J-1][k]) J--;
					a[i][J-1][k][m-1]=a[i][j][k][m-1];
					if(!book[i][J-1][k]){ Q.push(node(i,J-1,k)); book[i][J-1][k]=true;}
				} 
				else if(m==5)
				{
					int I=i; while(Ans[I+1][j][k]) I++;
					a[I+1][j][k][m-1]=a[i][j][k][m-1];
					if(!book[I+1][j][k]){ Q.push(node(I+1,j,k)); book[I+1][j][k]=true;}
				} 
				else
				{
					int I=i; while(Ans[I-1][j][k]) I--;
					a[I-1][j][k][m-1]=a[i][j][k][m-1];
					if(!book[I-1][j][k]){ Q.push(node(I-1,j,k)); book[I-1][j][k]=true;}
				} 
			}
			ans--; book[i][j][k]=1; Ans[i][j][k]=1;
			return false;
		}
	}
	return true;
}

int main(void)
{
	//freopen("in.txt","r",stdin);
	while(scanf("%d",&n)==1&&n)
	{
		memset(book,1,sizeof(book));
		memset(Ans,0,sizeof(Ans)); 
		memset(a,0,sizeof(a));
		for(int i=1;i<=n;++i)
		  for(int j=1;j<=n;++j)
		  	for(int k=1;k<=n;++k)
		  	  book[i][j][k]=0;
		ans=n*n*n;
		for(int j=1;j<=n;++j)
		  for(int i=0;i<=5;++i)
			for(int k=1;k<=n;++k)
			{
				char x=read();
				if(i==0){ a[j][k][1][i]=x;if(!book[j][k][1]){book[j][k][1]=1;Q.push(node(j,k,1));}} 
				else if(i==1){ a[j][1][n-k+1][i]=x;if(!book[j][1][n-k+1]){book[j][1][n-k+1]=1;Q.push(node(j,1,n-k+1));}} 
				else if(i==2){ a[j][n-k+1][n][i]=x;if(!book[j][n-k+1][n]){book[j][n-k+1][n]=1;Q.push(node(j,n-k+1,n));}} 
				else if(i==3){ a[j][n][k][i]=x;if(!book[j][n][k]){book[j][n][k]=1;Q.push(node(j,n,k));} } 
				else if(i==4){ a[1][k][n-j+1][i]=x;if(!book[1][k][n-j+1]){book[1][k][n-j+1]=1;Q.push(node(1,k,n-j+1));}} 
				else{ a[n][k][j][i]=x;if(!book[n][k][j]){book[n][k][j]=1;Q.push(node(n,k,j));}} 
			}
		while(Q.size())
		{
			node now=Q.front(); Q.pop();
			check(now.x,now.y,now.z);
		}
		printf("Maximum weight: %d gram(s)\n",ans);
	}
	return 0;
}
```

---

## 作者：AK_heaven (赞：1)

这道题可谓是十分棘手，乍一看去没有什么突破口。

但分析题目后，你会发现其实这道题就是让我们去求立方体到底最多由多少个单位立方体组成，这下思路就有了。我们先给出一个完整的 n * n * n 的立方体，然后再去删除那些必须删除的单位方块，这样最后的立方体便是我们想要的了。

思路从题目给出的输入开始，六个视角，其中除了颜色还有透视的地方。

从这里就有思路了，我们先去掉所有可透视方块，那些方块必须删除。

然后题目要求一个单位方块由同一种颜色填充，那么假设前视图右上角颜色 A 和顶视图右上角颜色 B 不同，那么对应的这个单位方块就肯定不存在。

所以现在我们做题共有四步：

1.初始化出一个立方体

2.通过透视，先删除掉一些方块

3.再通过颜色辨认，删除掉剩下两个视图矛盾的方块

4.最后统计剩下的方块数量，输出结果

奉上注释完备的代码：

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio> 
#include <cmath>

using namespace std;
#define REP(i,n) for(int i=0;i<(n);i++)
const int maxn = 10;
int n;
char pos[maxn][maxn][maxn];//我们构建的新立方体 
char view[6][maxn][maxn];//存放我们6个视图 

char read_char(){
	char ch;
	while(true){
		ch=getchar();
		if((ch>='A'&&ch<='Z')||ch=='.') return ch;
	}//读入颜色，getchar比cin和scanf都要快并且保证每次只读入一个字符 
}
//获取方块准确的位置信息 
void get(int k,int i,int j,int len,int &x,int &y,int &z){
	if(k==0) {x=len;y=j;z=i;}//前视图 
	if(k==1) {x=n-1-j;y=len;z=i;}// 左视图  
	if(k==2) {x=n-1-len;y=n-1-j;z=i;}//后视图，与前视图刚刚相反 
	if(k==3) {x=j;y=n-1-len;z=i;}//右视图 ，与右视图相反 
	if(k==4) {x=n-1-i;y=j;z=len;}//顶视图 ， 
	if(k==5) {x=i;y=j;z=n-1-len;}//底视图 ，与底视图相反 
} 
int main() {
	while(scanf("%d", &n)==1&&n){
		REP(i,n) REP(k,6) REP(j,n) view[k][i][j]=read_char();//读入k视图的 i行 j列 
		REP(i,n) REP(j,n) REP(k,n) pos[i][j][k]='#';//初始化 i行 j列 k层的方块 
		//注意，下面的p代表的是深度 
		REP(k,6) REP(i,n) REP(j,n) if(view[k][i][j]=='.')//如果 k视图的 i行 j列 是透视的，那么就修改该相应位置的所有方块为空 
		 REP(p,n){
		 	int x,y,z;
		 	get(k,i,j,p,x,y,z);//获取位置信息 
		 	pos[x][y][z]='.';//将目标方块删除掉 
		 } 
		while(true){
			bool done=true;
			REP(k,6) REP(i,n) REP(j,n) if(view[k][i][j]!='.'){
				REP(p,n) {
					int x,y,z;
					get(k,i,j,p,x,y,z);
					if(pos[x][y][z]=='.') continue;//在第一轮操作中就被删除的方块 
					if(pos[x][y][z]=='#'){
						pos[x][y][z]=view[k][i][j];
						break;//当前该方块未被操作过，就染色然后退出 
					}
					if(pos[x][y][z]==view[k][i][j]) break;//如果是已经操作过且没有发生矛盾就退出 
					pos[x][y][z]='.';//如果是已操作过但是出现矛盾就直接删掉
					done=false;//如果在本次遍历中仍然存在矛盾且执行了删除操作，说明仍然有可能还有矛盾方块存在 
				}
			}
			if(done) break; 
		}
		int ans=0;
		REP(i,n) REP(j,n) REP(k,n) 
		  if(pos[i][j][k]!='.') ans++;//循环遍历统计仍然剩下的方块数量 
		  
		printf("Maximum weight: %d gram(s)\n", ans);
	}
	return 0;
}
```


---

## 作者：Steadywelkin (赞：1)

### 题意

给出一个 $n\times n\times n$ 的立方体，其中有部分单位立方体缺失，给出六个方向的视图，求出剩余部分的最大重量

### 思路

每个单位立方体有各自的颜色，这就意味着如果有一个立方体的位置在两个不同的视图内表现出来的颜色不相同，这个单位立方体就一定不存在

可以先考虑将所有被挖穿的部分去除之后对冲突进行处理，将每一个单位立方体的颜色设置为 “#” 号，表示没有被访问过，直接删除挖穿的部分

每次处理冲突时判断是否要新删除一些单位立方体，新删除会对其他部分造成影响，所以设置 $flag=false$ 继续搜索

本题中由于有六个视图，而立方体的坐标固定有利于我们对题目的求解，所以可以设置下面代码中的 $getin()$ 函数实现对不同视图下的坐标统一

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

inline char read_char(void)
{
	char ch=getchar();
	for(;!isalpha(ch)&&ch!='.';ch=getchar());
	return ch;
}

const int N=10+5;int n;
char pos[N][N][N],v[6][N][N];

inline void getin(int k,int i,int j,int len,int& x,int& y,int& z)
{
	switch(k)
	{
		case 0:{x=len;     y=j;       z=i;       break;}
		case 1:{x=n-1-j;   y=len;     z=i;       break;}
		case 2:{x=n-1-len; y=n-1-j;   z=i;       break;}
		case 3:{x=j;       y=n-1-len; z=i;       break;}
		case 4:{x=n-1-i;   y=j;       z=len;     break;}
		case 5:{x=i;       y=j;       z=n-1-len; break;}
	}
	return;
}

signed main()
{
	while(scanf("%d",&n)==1&&n)
	{
		for(int i=0;i<n;i++)
		for(int k=0;k<6;k++)
		for(int j=0;j<n;j++)
		v[k][i][j]=read_char();
		
		for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
		for(int k=0;k<n;k++)
		pos[i][j][k]='#';	
		
		for(int k=0;k<6;k++)
		for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
		if(v[k][i][j]=='.')
		{
			for(int p=0;p<n;p++)
			{
				int x,y,z;
				getin(k,i,j,p,x,y,z);
				pos[x][y][z]='.';
			}
		}
		
		while(true)
		{
			bool flag=true;
			for(int k=0;k<6;k++)
			for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
			if(v[k][i][j]!='.')
			{
				for(int p=0;p<n;p++)
				{
					int x,y,z;
					getin(k,i,j,p,x,y,z);
					if(pos[x][y][z]=='.')
						continue;
					if(pos[x][y][z]=='#')
						pos[x][y][z]=v[k][i][j];
					if(pos[x][y][z]==v[k][i][j])
						break;
					pos[x][y][z]='.';
					flag=false;
				}
			} 
			if(flag)break;
		}
		int ans=0;
		
		for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
		for(int k=0;k<n;k++)
		if(pos[i][j][k]!='.')
		ans++;
		
		printf("Maximum weight: %d gram(s)\n",ans);
	}
	return 0;
}
```


---

## 作者：破忆 (赞：1)

## 【题意】
若干个方块构成一个至多$n*n*n$的立体图形，给定六个方向的视图，求最多的满足题意的方块数

## 【分析】

不妨假设初始时所有方块都是存在的

我们需要检验当前这个图形是否合法

若某个位置的方块从两种视图上看有矛盾，则这个方块不合法

这个位置必定没有方块

那么把这个位置的方块删掉

接下来又构成了一个新的图形，继续重复以上步骤即可

如果当前没有任何矛盾，就得到了合法的图形

计算当前还剩多少方块即可

------------
此题维度较高，动辄三层循环

宏定义可以使代码可读性更强


```cpp
#define FOR(i,l,r) for(int i=l;i<=r;i++)
```

------------

判断是否合法，需要知道某个视图上某个位置对应的坐标

分别处理$6$个视图$i$行$j$列深度为$d$对应的坐标

```cpp
void get(int k,int i,int j,int dep,int &x,int &y,int &z){
	if(k==1) x=i,y=j,z=dep;else
	if(k==2) x=i,y=dep,z=n-j+1;else
	if(k==3) x=i,y=n-j+1,z=n-dep+1;else
	if(k==4) x=i,y=n-dep+1,z=j;else
	if(k==5) x=dep,y=j,z=n-i+1;else
	if(k==6) x=n-dep+1,y=j,z=i;
}
```
------------
判断是否矛盾，可以记录方块已知的类型

判断当前类型是否与之前冲突
```cpp
bool flg=1;
		while(flg){
			flg=0;
			int x,y,z;
			FOR(k,1,6) FOR(i,1,n) FOR(j,1,n) if(view[k][i][j]!='.'){
				FOR(d,1,n){
					get(k,i,j,d,x,y,z);
					if(mp[x][y][z]=='.') continue;
					if(mp[x][y][z]=='#'){mp[x][y][z]=view[k][i][j];break;}
					if(mp[x][y][z]==view[k][i][j]) break;
					flg=1;
					mp[x][y][z]='.';
					break;
				}
			}
		}
```
## 【代码】
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=12;
int n;
#define FOR(i,l,r) for(int i=l;i<=r;i++)
char mp[maxn][maxn][maxn];
char view[8][maxn][maxn];
void get(int k,int i,int j,int dep,int &x,int &y,int &z){
	if(k==1) x=i,y=j,z=dep;else
	if(k==2) x=i,y=dep,z=n-j+1;else
	if(k==3) x=i,y=n-j+1,z=n-dep+1;else
	if(k==4) x=i,y=n-dep+1,z=j;else
	if(k==5) x=dep,y=j,z=n-i+1;else
	if(k==6) x=n-dep+1,y=j,z=i;
}
int ans;
int main(){
	freopen("UVA1030.in","r",stdin);
	freopen("UVA1030.out","w",stdout);
	while(scanf("%d",&n)==1&&n){
		FOR(i,1,n) FOR(j,1,n) FOR(k,1,n) mp[i][j][k]='#';
		FOR(i,1,n) FOR(k,1,6) FOR(j,1,n){
			char ch=getchar();
			while(ch!='.'&&(ch>'Z'||ch<'A')) ch=getchar();
			view[k][i][j]=ch;
		}
		FOR(k,1,6) FOR(i,1,n) FOR(j,1,n) if(view[k][i][j]=='.'){
			FOR(d,1,n){
				int x,y,z;
				get(k,i,j,d,x,y,z);
				mp[x][y][z]='.';
			}
		}
		bool flg=1;
		while(flg){
			flg=0;
			int x,y,z;
			FOR(k,1,6) FOR(i,1,n) FOR(j,1,n) if(view[k][i][j]!='.'){
				FOR(d,1,n){
					get(k,i,j,d,x,y,z);
					if(mp[x][y][z]=='.') continue;
					if(mp[x][y][z]=='#'){mp[x][y][z]=view[k][i][j];break;}
					if(mp[x][y][z]==view[k][i][j]) break;
					flg=1;
					mp[x][y][z]='.';
					break;
				}
			}
		}
		ans=0;
		FOR(i,1,n) FOR(j,1,n) FOR(k,1,n){
			ans+=mp[i][j][k]!='.';
		}
		printf("Maximum weight: %d gram(s)\n",ans);
	}
	return 0;
}
```
## 【提醒】
此题数据格式可能有些问题，读数据需要写得细致一点

---

## 作者：520Enterprise (赞：1)

首先，能够“看穿”的地方所对应的所有立方体一定都不存在。
然后，如果同一个立方体从不同方向看颜色不同，这个立方体亦不存在。
删除不存在的正方体，反复进行删除操作直至不能删除，此时剩下的就是重量最大的。
```
#include<cmath>
#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<map>
#include<queue>
using namespace std;
const int maxn=20;
int n;
char pos[maxn][maxn][maxn],view[maxn][maxn][maxn];
inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
	if(ch=='-')
	    f=-1;
	ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
	x=(x<<1)+(x<<3)+(ch^48);
	ch=getchar();
    }
    return x*f;
}
char read_char()
{
    char ch;
    while(1)
    {
	ch=getchar();
	if((ch>='A'&&ch<='Z')||ch=='.')
	    return ch;
    }
}
void get(int k,int i,int j,int len,int &x,int &y,int &z)
{
    if(k==0)
	x=len,y=j,z=i;
    if(k==1)
	x=n-1-j,y=len,z=i;
    if(k==2)
	x=n-1-len,y=n-1-j,z=i;
    if(k==3)
	x=j,y=n-1-len,z=i;
    if(k==4)
	x=n-1-i,y=j,z=len;
    if(k==5)
	x=i,y=j,z=n-1-len;
}
int main()
{
    while(scanf("%d",&n)==1&&n)
    {
	for(int i=0;i<n;i++)
	    for(int k=0;k<6;k++)
		for(int j=0;j<n;j++)
		    view[k][i][j]=read_char();
	for(int i=0;i<n;i++)
	    for(int j=0;j<n;j++)
		for(int k=0;k<n;k++)
		    pos[i][j][k]='#';
	for(int k=0;k<6;k++)
	    for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
		    if(view[k][i][j]=='.')
			for(int p=0;p<n;p++)
			{
			    int x,y,z;
			    get(k,i,j,p,x,y,z);
			    pos[x][y][z]='.';
			}
	while(1)
	{
	    bool done=1;
	    for(int k=0;k<6;k++)
		for(int i=0;i<n;i++)
		    for(int j=0;j<n;j++)
			if(view[k][i][j]!='.')
			    for(int p=0;p<n;p++)
			    {
				int x,y,z;
				get(k,i,j,p,x,y,z);
				if(pos[x][y][z]=='.')
				    continue;
				if(pos[x][y][z]=='#')
				{
				    pos[x][y][z]=view[k][i][j];
				    break;
				}
				if(pos[x][y][z]==view[k][i][j])
				    break;
				pos[x][y][z]='.';
				done=0;
			    }
	    if(done)
		break;
	}
	int ans=0;
	for(int i=0;i<n;i++)
	    for(int j=0;j<n;j++)
		for(int k=0;k<n;k++)
		    if(pos[i][j][k]!='.')
			ans++;
	printf("Maximum weight: %d gram(s)\n",ans);
    }
    return 0;
}



---

## 作者：Lyccrius (赞：0)

能 “看穿” 的位置所对应的所有单位立方体一定都不存在。

如果 $k_1$ 视图的颜色和 $k_2$ 视图的颜色不同，那么对应的格子一定不存在。

在删除一个立方体之后，又暴露出新的表面。

当无法继续删除的时候，剩下的立方体就是质量最大的物体。

用一个函数来表示第 $k$ 个视图中第 $i$ 行 $j$ 列、深度为 $\text{len}$ 的单位立方体在原立方体中的坐标 $(x, y, z)$。

```
#include <cstdio>
#include <cstring>

#define front 1
#define left 2
#define back 3
#define right 4
#define top 5
#define bottom 6

const int maxn = 10 + 10;

int n;

char pos[maxn][maxn][maxn];
char view[10][maxn][maxn];

void translate(int k, int i, int j, int p, int &x, int &y, int &z) {
    switch(k) {
        case front: {
            x = p;
            y = j;
            z = i;
            break;
        }
        case left: {
            x = n - j + 1;
            y = p;
            z = i;
            break;
        }
        case back: {
            x = n - p + 1;
            y = n - j + 1;
            z = i;
            break;
        }
        case right: {
            x = j;
            y = n - p + 1;
            z = i;
            break;
        }
        case top: {
            x = n - i + 1;
            y = j;
            z = p;
            break;
        }
        case bottom: {
            x = i;
            y = j;
            z = n - p + 1;
            break;
        }
    }
    return;
}

int main() {
    while (scanf("%d", &n) == 1 && n) {
        for (int i = 1; i <= n; i++) {
            for (int k = 1; k <= 6; k++) {
                for (int j = 1; j <= n; j++) {
                    scanf(" %c", &view[k][i][j]);
                }
            }
        }
        std::memset(pos, '#', sizeof(pos));
        for (int k = 1; k <= 6; k++) {
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= n; j++) {
                    if (view[k][i][j] == '.') {
                        for (int p = 1; p <= n; p++) {
                            int x, y, z;
                            translate(k, i, j, p, x, y, z);
                            pos[x][y][z] = '.';
                        }
                    }
                }
            }
        }
        bool deleted = true;
        while (deleted) {
            deleted = false;
            for (int k = 1; k <= 6; k++) {
                for (int i = 1; i <= n; i++) {
                    for (int j = 1; j <= n; j++) {
                        if (view[k][i][j] != '.') {
                            for (int p = 1; p <= n; p++) {
                                int x, y, z;
                                translate(k, i, j, p, x, y, z);
                                if (pos[x][y][z] == '.') continue;
                                if (pos[x][y][z] == '#') {
                                    pos[x][y][z] = view[k][i][j];
                                    break;
                                }
                                if (pos[x][y][z] == view[k][i][j]) break;
                                pos[x][y][z] = '.';
                                deleted = true;
                            }
                        }
                    }
                }
            }
        }
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                for (int k = 1; k <= n; k++) {
                    if (pos[i][j][k] != '.') ans++;
                }
            }
        }
        printf("Maximum weight: %d gram(s)\n", ans);
    }
    return 0;
}
```

---

