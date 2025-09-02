# Bear and Square Grid

## 题目描述

You have a grid with $ n $ rows and $ n $ columns. Each cell is either empty (denoted by '.') or blocked (denoted by 'X').

Two empty cells are directly connected if they share a side. Two cells $ (r_{1},c_{1}) $ (located in the row $ r_{1} $ and column $ c_{1} $ ) and $ (r_{2},c_{2}) $ are connected if there exists a sequence of empty cells that starts with $ (r_{1},c_{1}) $ , finishes with $ (r_{2},c_{2}) $ , and any two consecutive cells in this sequence are directly connected. A connected component is a set of empty cells such that any two cells in the component are connected, and there is no cell in this set that is connected to some cell not in this set.

Your friend Limak is a big grizzly bear. He is able to destroy any obstacles in some range. More precisely, you can choose a square of size $ k×k $ in the grid and Limak will transform all blocked cells there to empty ones. However, you can ask Limak to help only once.

The chosen square must be completely inside the grid. It's possible that Limak won't change anything because all cells are empty anyway.

You like big connected components. After Limak helps you, what is the maximum possible size of the biggest connected component in the grid?

## 说明/提示

In the first sample, you can choose a square of size $ 2×2 $ . It's optimal to choose a square in the red frame on the left drawing below. Then, you will get a connected component with $ 10 $ cells, marked blue in the right drawing.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF679C/73f9f2e0fd56d2fb7f7f3062a32953f02d9af103.png)

## 样例 #1

### 输入

```
5 2
..XXX
XX.XX
X.XXX
X...X
XXXX.
```

### 输出

```
10
```

## 样例 #2

### 输入

```
5 3
.....
.XXX.
.XXX.
.XXX.
.....
```

### 输出

```
25
```

# 题解

## 作者：intel_core (赞：2)

看到标签里的 `implementation` 就知道这题不太好写（真的是细节一大堆。。。

第一步上来肯定是把相邻的格子用并查集并起来。

用脚指头想一想，形成的最大连通块肯定全包了你指定框的位置。

所以，我们肯定要 $O(n^2)$ 一个一个枚举框的位置。

现在我们固定了框的位置，要求出形成的连通块大小。

因为求的是整个连通块的大小，所以框周围的一圈点的连通块肯定得算到答案里，开一个数组记录每个连通块有没有被统计过，这部分可以 $O(k)$ 做。

框里的有一些格子可能在框外面的连通块那一部分统计了，所以我们要想办法把这一部分贡献去掉。

但是很明显求一个连通块不在某一个矩形框中的部分非常不好求，所以我们考虑补集转化：考虑求出一个框内不与框外任何一个格子联通的格子个数。

如果要求这个东西，那一个连通块的点要么对一个框都有贡献，要么都没贡献；所以我们分连通块考虑这个东西。

我们在并查集合并连通块的时候可以记录一下每个连通块最上，下，左，右的位置分别在哪里。

这样我们直接枚举每一个连通块：

* 如果左右或者上下跨度超过了 $k$，那么这个连通块显然不能被任何一个框完整的包进去。

* 否则，可以完整包住这个连通块的框的位置是可以确定的。具体来说，设连通块最上，下，左，右的位置分别是 $y1,y2,x1,x2$，那么能包住这个连通块的框的左上角一定在 $(x2-k+1,y2-k+1)$ 和 $(x1,y1)$ 围成的矩形中。

这样我们扫一遍所有连通块，接着跑一遍二维前缀和就可以了。

这个思路很自然，但是代码极不友好。。。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NR=1e3+10;
int n,k,ans,fa[NR*NR],size[NR*NR],sum[NR][NR],cnt[NR][NR],vis[NR*NR];
int maxx[NR*NR],maxy[NR*NR],minx[NR*NR],miny[NR*NR];
const int dx[]={1,-1,0,0};
const int dy[]={0,0,1,-1};
char s[NR][NR];
bool exist(int x,int y){
	if(x<1||x>n||y<1||y>n)return 0;
	return 1;
}
void chkmax(int &x,int y){x=x>y?x:y;}
void chkmin(int &x,int y){x=x<y?x:y;}

inline int calc(int x,int y){return (x-1)*n+y;}
void init(){
	for(int i=1;i<=n*n;i++)fa[i]=i,size[i]=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			maxx[calc(i,j)]=minx[calc(i,j)]=i,miny[calc(i,j)]=maxy[calc(i,j)]=j;
}
inline int get(int x){
	if(fa[x]==x)return x;
	return fa[x]=get(fa[x]);
}
void merge(int x,int y){
	x=get(x);y=get(y);
	if(x==y)return;
	fa[x]=y;size[y]+=size[x];
	chkmax(maxx[y],maxx[x]);chkmax(maxy[y],maxy[x]);
	chkmin(minx[y],minx[x]);chkmin(miny[y],miny[x]);
}

int main(){
	cin>>n>>k;init();
	for(int i=1;i<=n;i++){
		scanf(" %s",s[i]+1);
		for(int j=1;j<=n;j++){
			cnt[i][j]=cnt[i-1][j]+cnt[i][j-1]-cnt[i-1][j-1]+(s[i][j]=='.');
			if(s[i][j]=='.')
				for(int k=0;k<4;k++)
					if(s[i+dx[k]][j+dy[k]]=='.')merge(calc(i,j),calc(i+dx[k],j+dy[k]));
		}
			
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(s[i][j]=='.'&&get(calc(i,j))==calc(i,j))
				if(maxx[calc(i,j)]-minx[calc(i,j)]<k&&maxy[calc(i,j)]-miny[calc(i,j)]<k){
					sum[max(maxx[calc(i,j)]-k+1,1)][max(maxy[calc(i,j)]-k+1,1)]+=size[calc(i,j)];
					sum[minx[calc(i,j)]+1][max(maxy[calc(i,j)]-k+1,1)]-=size[calc(i,j)];
					sum[max(maxx[calc(i,j)]-k+1,1)][miny[calc(i,j)]+1]-=size[calc(i,j)];
					sum[minx[calc(i,j)]+1][miny[calc(i,j)]+1]+=size[calc(i,j)];
				}
	for(int x=1;x+k<=n+1;x++)
		for(int y=1;y+k<=n+1;y++){
			sum[x][y]+=sum[x-1][y]+sum[x][y-1]-sum[x-1][y-1];
			int res=k*k-cnt[x+k-1][y+k-1]-cnt[x-1][y-1]+cnt[x+k-1][y-1]+cnt[x-1][y+k-1]+sum[x][y];
			if(x>1)
				for(int i=y;i<y+k;i++)
					if(s[x-1][i]=='.'&&!vis[get(calc(x-1,i))])
						vis[get(calc(x-1,i))]=1,res+=size[get(calc(x-1,i))];
			if(x+k<=n)
				for(int i=y;i<y+k;i++)
					if(s[x+k][i]=='.'&&!vis[get(calc(x+k,i))])
						vis[get(calc(x+k,i))]=1,res+=size[get(calc(x+k,i))];
			if(y>1)
				for(int i=x;i<x+k;i++)
					if(s[i][y-1]=='.'&&!vis[get(calc(i,y-1))])
						vis[get(calc(i,y-1))]=1,res+=size[get(calc(i,y-1))];
			if(y+k<=n)
				for(int i=x;i<x+k;i++)
					if(s[i][y+k]=='.'&&!vis[get(calc(i,y+k))])
						vis[get(calc(i,y+k))]=1,res+=size[get(calc(i,y+k))];
			ans=max(ans,res);
			if(x>1)
				for(int i=y;i<y+k;i++)
					if(s[x-1][i]=='.')vis[get(calc(x-1,i))]=0;
			if(x+k<=n)
				for(int i=y;i<y+k;i++)
					if(s[x+k][i]=='.')vis[get(calc(x+k,i))]=0;
			if(y>1)
				for(int i=x;i<x+k;i++)
					if(s[i][y-1]=='.')vis[get(calc(i,y-1))]=0;
			if(y+k<=n)
				for(int i=x;i<x+k;i++)
					if(s[i][y+k]=='.')vis[get(calc(i,y+k))]=0;
		}
	cout<<ans<<endl;
	return 0;
}
*/
```

---

## 作者：xukuan (赞：1)

文章翻译（由于我被禁言，只能在此翻译 此翻译由我的教练翻译，请不要对我加贡献）

题目描述：

给定一个n行n列的矩阵，每个格子里是空的或者是封闭的。当相邻的格子都是空的，这两个格子就是联通的，多个连通格子组成一个连通快。

现在你有一个k×k的框，使用这个框可以将包含的封闭格子变成是空的。使用框的时候，整个框必须全部在矩阵内。

请问这个矩阵的最大连通块包含的格子的数量。

输入输出格式:

输入格式:

第一行，两个整数n和k。(1≤k≤n≤500)

接下来n行，每行包含n个字符'.' 或者 'X'，其中'.'表示该格子是空的，'X'表示该格子是封闭的。

输出格式:

一行，一个整数，表示最大连通块包含的格子的数量。

输入样例#1： 
```pascal
5 2
..XXX
XX.XX
X.XXX
X...X
XXXX.
```

输出样例#1:

10

输入样例#2:

```pascal
5 3
.....
.XXX.
.XXX.
.XXX.
.....
```

输出样例#2： 

25


提示：

样例1解释如图：
![](http://www.syoj.top/assets/images/problems/syoj1963.png)

--------------------------------------------------

题解正文：

搜索DFS+联通快

先算出原始图联通快的数量，再穷举框的位置，

### 优化移动框时删掉最左边的一列，加上最右边的一列就是要求的数量,O(n^4)变成O(n^3);

预处理：

1.矩阵前缀和（sum）

2.原始图中的联通块

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<string> 
#define ll long long
using namespace std;

ll n,k,ans,all,cnt,tmp;
char a[505][505];
ll f[505][505],colour[250050],sum[505][505],vi[250050];

void dfs(ll x,ll y){//dfs求联通块
    tmp++;//数量增加
    f[x][y]=cnt;
    //四个方向的递归
    if(a[x-1][y]=='.'&&!f[x-1][y]) dfs(x-1,y);
    if(a[x+1][y]=='.'&&!f[x+1][y]) dfs(x+1,y);
    if(a[x][y-1]=='.'&&!f[x][y-1]) dfs(x,y-1);
    if(a[x][y+1]=='.'&&!f[x][y+1]) dfs(x,y+1);
}

inline void Delete(ll x,ll y){//删除点
    if(!f[x][y]) return;
    ll t=f[x][y];
    --vi[t];
    if(!vi[t]) all-=colour[t];
}

inline void insert(ll x,ll y){//加入点
    if(!f[x][y]) return;
    ll t=f[x][y];
    if(!vi[t]) all+=colour[t];
    vi[t]++;
}

inline ll calc(ll x,ll y){//区间内点'.'的数量
    return sum[x+k-1][y+k-1]-sum[x+k-1][y-1]-sum[x-1][y+k-1]+sum[x-1][y-1];
}

int main(){
    ll i,j;
    cin>>n>>k;
    for(i=1; i<=n; ++i){
        scanf("%s",a[i]+1);//字符数组可以当字符串使用
        for(j=1; j<=n; ++j){
            sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];
            if(a[i][j]=='.') sum[i][j]++;
        } 
    }
    
    for(i=1; i<=n; ++i){
	    for(j=1; j<=n; ++j){
			if(a[i][j]=='.'&&!f[i][j]){
            //过a[i][j]的联通块数量
		    	cnt++;
			    tmp=0;
			    dfs(i,j);
			    colour[cnt]=tmp;
			} 
		} 
	}
	
    for(i=1; i<=n-k+1; ++i){
        all=0;
		memset(vi,0,sizeof(vi));
        for(j=i-1; j<=k+i; ++j){
            for(ll l=1; l<=k; ++l)
                insert(j,l);//加点
        }
        
        for(j=i; j<i+k; ++j) insert(j,k+1);//加点
        ans=max(ans,all+k*k-calc(i,1));
        for(j=2; j<=n-k+1; ++j){
            for(ll l=i;l<i+k;++l){
                Delete(l,j-2);//删点
                insert(l,j+k);//加点
            }
            Delete(i-1,j-1);//删点
			Delete(i+k,j-1);//删点
            insert(i-1,j+k-1);//加点
			insert(i+k,j+k-1);//加点
            ans=max(ans,all+k*k-calc(i,j));//ans取较大值
        }
    }
    cout<<ans<<endl;
    return 0;
}
```

---

