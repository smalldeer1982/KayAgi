# Binary Matrix

## 题目描述

You are given a matrix of size $ n×m $ . Each element of the matrix is either 1 or 0. You have to determine the number of connected components consisting of 1's. Two cells belong to the same component if they have a common border, and both elements in these cells are 1's.

Note that the memory limit is unusual!

## 说明/提示

In the first example the matrix is:

`<br></br>0001<br></br>1010<br></br>1000<br></br>`It is clear that it has three components.

The second example:

`<br></br>01011111<br></br>11100011<br></br>`It is clear that the number of components is 2.

There are no 1's in the third example, so the answer is 0.

## 样例 #1

### 输入

```
3 4
1
A
8
```

### 输出

```
3
```

## 样例 #2

### 输入

```
2 8
5F
E3
```

### 输出

```
2
```

## 样例 #3

### 输入

```
1 4
0
```

### 输出

```
0
```

# 题解

## 作者：reyik (赞：6)

~~这题居然没有题解~~

并查集+滚动数组

像$dp$的滚动数组一样

每一次存这一行和上一行，并查集的时候，保留上一行的father,这一行初始化，然后合并到上一行里面取即可。

代码：（当前$rank1$)

```cpp
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
using namespace std;
int father[40005];
int n,m,nt,ans=0;
bool a[2][40005];
char s[40005];
inline int find(int x) {
        if(father[x]==x) return x;
        father[x]=find(father[x]);
        return father[x];
}
int main() {
        scanf("%d%d",&n,&m);
        for (int i=1;i<=n;++i) {
                int knd=i&1;
                scanf("%s",s+1);
                for (int j=1;j<=m/4;++j) {
                        int res;
                        if(isdigit(s[j])) res=s[j]-'0';
                        else res=s[j]-'A'+10;
                        a[knd][j*4]=res&1,ans+=(res&1),res>>=1;
                        a[knd][j*4-1]=res&1,ans+=(res&1),res>>=1;
                        a[knd][j*4-2]=res&1,ans+=(res&1),res>>=1;
                        a[knd][j*4-3]=res&1,ans+=(res&1),res>>=1;
                }
                int res1=knd*m;
                for (int j=1;j<=m;++j) father[res1+j]=res1+j;
                for (int j=1;j<m;++j) {
                        if((a[knd][j]) && (a[knd][j+1])) {
                                int x=res1+j,y=x+1;
                                int xf=find(x),yf=find(y);
                                if(xf!=yf) father[yf]=xf,--ans;
                        }
                }
                for (int j=1;j<=m;++j) {
                        if((a[knd][j]) && (a[knd^1][j])) {
                                int x=res1+j,y=(knd^1)*m+j;
                                int xf=find(x),yf=find(y);
                                if(xf!=yf) father[yf]=xf,--ans;
                        }
                }
        }
        printf("%d\n",ans);
        return 0;
}
```

---

## 作者：jucason_xu (赞：2)

题意：对于一个使用十六进制读入的 $01$ 矩阵，求其中 $1$ 的连通块个数，空间限制 `16MB` 。$n\le 2^{12},m\le2^{14}$

我们认为如何读入是比较基础的内容，不作过多的介绍，具体请看代码。

### 离线下来怎么做

首先，如果不考虑空间限制，这题是比较简单的。我们可以直接在图上 `DFS` 获得 $O(nm)$ 的做法。但是空间限制要求我们不能把全图存下来。我们就只能一行一行读入，考虑在线的做法。

### 在线，但不考虑空间限制

我们每次读入一行，考虑会发生什么。我们发现 `DFS`的本质就是 __染色__ 。我们保存上一行的状态和颜色，读入当前一行的状态。

然后从当前行往上看。如果上一行的当前位置是 $1$，那么它一定被涂色过了，给当前格子涂上它的颜色。从它开始往左右两边循环涂色（在这一层扩张连通块），如果遇到了 $0$ 就结束， __如果遇到了别的颜色，那么就意味着当前的颜色和另外的颜色会合并起来。__

最后，有些格子可能不能从上一行继承颜色，就需要新建颜色给它们。

先不考虑空间限制，考虑如何在线维护。

我们可以给所有的颜色开一个并查集，每次在并查集上维护两种颜色是否相同，合并两种颜色。最后直接扫描整个并查集，看其中有多少个等价类。

注意实现细节，为了每个点都只被扫到一次，我们 __优先用左侧的颜色覆盖右边的__ ，当覆盖到一个可以从上方继承别的颜色的格子的时候，进行颜色合并。

但是颜色的数量可能达到 $O(nm)$ 的级别，不能直接开并查集，考虑优化。

### 在线且考虑空间复杂度

我们发现，执行到当前行， __有效的颜色（可能对下面产生影响的）只有前一行的所有颜色，总数是 $O(m)$ 的级别。__ 我们可以每次重新给颜色编号，例如，当前前一行的颜色是 `1 2 5 6 7` ，我们直接将其改成 `1 2 3 4 5` ，后面新增颜色的时候就从 `6` 开始。

如果有相同颜色呢？用 `map` 吗？带 $\log$ 基本就挂了。我们发现，每行增加的颜色数量也是 $O(m)$ 的，所以颜色的值域是 $O(m)$ 的。我们就可以直接用长度 $2m$ 的数组暴力维护原先值域的所有颜色到新值域的映射，$O(1)$ 检查 __当前值映射是否存在，从而决定是否建立新的映射。__

因此，我们就可以只开 $O(m)$ 的并查集数组而非 $O(nm)$ 的。注意并查集每次都要初始化（因为我们是在 __滚动地处理问题__ ）。并且，因为每次的并查集不往下继承，即使上一层属于同一并查集的结果，下面也会认为他们是不同的，所以 __每次运算结束之后要进行推平。__

具体而言，当前在并查集上， `1` 和 `2` 是同一集合内的。但是如果到了下面一层，因为当前的信息丢失，下一层就会认为 `1` 和 `2` 是不同颜色。因此，我们最后把所有的 `color[i]` 更改成 `find(color[i])` ，就可以保证下一次不会把同样的颜色辨认成不同的。 __（相当于路径压缩）__

如何计算答案呢？我们发现，每当我们分配一个颜色，就会增加一个连通块。 __合并两种颜色，其中一个颜色就被删除，减去一个连通块。__ 可以直接在合并的同时计算。

### 时间复杂度优化

而直接实现的做法会带一个并查集的 $\log$，会挂。

众所周知，如果我们同时在并查集上使用启发式合并和路径压缩，就可以把并查集的复杂度优化到 $O(\alpha(n))$ 。而 $\alpha(m)$ 是很小的，能有 $4$ 就顶了天了。于是，我们就得到了一个 $O(nm\alpha(m))$ 的做法，空间是 $O(m)$ 的，足以通过这道题。

### 代码
```cpp
#define rd(i,n) for(int i=0;i<n;i++)
#define rp(i,n) for(int i=1;i<=n;i++)
#define st string
#define pb push_back
typedef long long ll;
int n,m;
int a[20005],b[20005],cnt,cb[20005],c[20005],ans,ers[20005];
int fa[40005],sz[40005],app[40005],lstcnt;
inline void getlne(){
	st s;
	cin>>s;
   //滚动
	rp(i,m)b[i]=a[i],cb[i]=c[i],c[i]=0;
   //读入
	rd(i,m/4){
		int val=0;
		if(s[i]>='A')val=10+s[i]-'A';
		else val=s[i]-'0';
		a[4*i+1]=(val>>3&1);
		a[4*i+2]=(val>>2&1);
		a[4*i+3]=(val>>1&1);
		a[4*i+4]=(val>>0&1);
	}
   //建立旧的值域到新的值域的映射
	lstcnt=cnt,cnt=0;
	rp(i,m)if(cb[i]){
		if(app[cb[i]]){
			cb[i]=app[cb[i]];
		}else {
			int cur=++cnt;
			app[cb[i]]=cur;
			cb[i]=cur;
		}
	}
   //记得清空映射，初始化并查集
	rp(i,lstcnt)if(app[i])app[i]=0;
	rp(i,cnt)fa[i]=i,sz[i]=1;
}
inline void merge(int x,int y){
	if(x==y)return;
	else ans--;//在这里维护答案
	if(sz[x]>sz[y])sz[x]+=sz[y],fa[y]=x;
	else sz[y]+=sz[x],fa[x]=y;
}
inline int head(int x){
	return fa[x]==x?x:fa[x]=head(fa[x]);
}
inline void solve(){
	//先考虑有颜色继承的往左右覆盖
	rp(i,m)if(a[i]&&b[i]&&!c[i]){
		int l=i,r=i;c[i]=cb[i];
		while(l>1&&a[l-1])l--,c[l]=c[i];
		while(r<m&&a[r+1]){
			r++;
        //合并颜色
			if(cb[r]&&cb[r]!=c[i])merge(head(cb[r]),head(c[i]));
			c[r]=c[i];
		}
		i=r;
	}
   //颜色推平
	rp(i,m)if(c[i])c[i]=head(c[i]);
   //新分配颜色
	rp(i,m)if(a[i]&&!c[i]){
		c[i]=++cnt;ans++;
		while(i<m&&a[i+1])i++,c[i]=c[i-1];
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>n>>m;
	rp(i,n){
		getlne();
		solve();
	}
	cout<<ans<<endl;
	return 0;
}
//Crayan_r
```


---

