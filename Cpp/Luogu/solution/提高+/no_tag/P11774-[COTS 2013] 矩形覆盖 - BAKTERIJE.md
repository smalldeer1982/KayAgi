# [COTS 2013] 矩形覆盖 / BAKTERIJE

## 题目描述

在平面直角坐标系上有 $N$ 个边与坐标轴平行，且互不重叠的矩形，给定它们的左下角坐标 $(x_1,y_1)$ 和右上角坐标 $(x_2,y_2)$。

你现在有一个长为 $W$，宽为 $H$ 的矩形 $S$，你需要选择一个位置放置这个矩形，使得原坐标系上的矩形和 $S$ 有交的矩形的数量尽可能多。

注意：

- 矩形 $S$ 顶点不必放置在整数坐标上（见样例 $1$ 图片）。
- 有交指两个矩形重叠位置的面积 $>0$。

## 说明/提示

【样例解释】

![](https://cdn.luogu.com.cn/upload/image_hosting/f9olyi3c.png)

【数据范围与约定】

- 对于 $30 \%$ 的数据，满足 $N\le 30$。

- 对于 $60 \%$ 的数据，满足 $N\le 1000$。

- 对于 $100 \%$ 的数据，满足 $1 \le N \le 100000,1\le W,H \le 50000,0 \le x_1<x_2 \le 50000,0 \le y_1<y_2 \le 50000$。

## 样例 #1

### 输入

```
4 3 
4 
2 2 5 5 
8 2 11 5 
1 7 4 10 
7 7 10 10```

### 输出

```
3```

## 样例 #2

### 输入

```
7 4 
6 
5 1 8 2 
2 2 4 7 
5 3 8 6 
9 2 11 7 
5 8 6 9 
7 8 8 9```

### 输出

```
5```

## 样例 #3

### 输入

```
3 3 
3 
1 1 5 5 
5 1 9 5 
8 5 10 10```

### 输出

```
2```

# 题解

## 作者：andychen_2012 (赞：1)

考虑你的矩形 $S$ 的左端为 $L$，下端为 $D$，则右端为 $L+W$，上端为 $D+H$。类似的小矩形的四边坐标记作 $l_i,d_i,r_i,u_i$。

那么覆盖则须满足

$$
L< \min r_i\\
D < \min d_i\\
L+W> \max l_i\\
D+H> \max u_i
$$

我们将 $W,H$ 各减去 $1$，然后挪到右边去，同时考虑将 $L,D$ 变为整数坐标，则有

$$
\max(l_i-W) \le L < \min(r_i+1)\\
\max(u_i-H) \le D < \min(d_i+1)
$$

我们对 $L$ 这一维扫描线，然后将每一个加入或删除的矩形的上下端在线段树上维护，求最大前缀和即可。

代码如下：

```cpp
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long ll;
inline int read(){
    int x=0;
    int f=0,ch=0;
    while(ch<48||ch>57) f=(ch=='-'),ch=getchar();
    while(ch>47&&ch<58) x=(x<<3)+(x<<1)+(ch&15),ch=getchar();
    return f?-x:x;
}
inline void write(ll x,char end='\n'){
    if(x==0){
        putchar('0');
        putchar(end);
        return;
    }
    if(x<0) putchar('-'),x=-x;
    int ch[40]={0},cnt=0;
    while(x){
        ch[cnt++]=(int)(x%10);
        x/=10;
    }
    while(cnt--) putchar(ch[cnt]+48);
    putchar(end);
}
const int N=1e5+5;
const int L=5e4+1;
int w,h;
int n;
struct mat{int l,d,r,u;}rec[N];
inline bool cmp(mat x,mat y){return x.r<y.r;}
vector<int> e[L+5];
int sum[N<<2],mxlsum[N<<2];
inline void pushup(int u){
	sum[u]=sum[u<<1]+sum[u<<1|1];
	mxlsum[u]=max(mxlsum[u<<1],sum[u<<1]+mxlsum[u<<1|1]);
}
inline void add(int u,int l,int r,int p,int v){
	if(l==r){
		sum[u]+=v;
		mxlsum[u]=max(sum[u],0);
		return;
	}
	int mid=(l+r)>>1;
	if(p<=mid) add(u<<1,l,mid,p,v);
	else add(u<<1|1,mid+1,r,p,v);
	pushup(u);
}
inline void modify(int id,int v){
	add(1,1,L,max(rec[id].d,1),v);
	add(1,1,L,rec[id].u+1,-v);
}
int main(){
	w=read(),h=read();
	w--,h--;
	n=read();
	for(int i=1;i<=n;++i) rec[i]={read(),read()-h,read(),read()};
	for(int i=1;i<=n;++i){
		e[max(rec[i].l-w,0)].emplace_back(i);
		e[rec[i].r+1].emplace_back(-i);
	}
	int ans=0;
	for(int i=0;i<=L;++i){
		for(auto id:e[i]){
			if(id<0) modify(-id,-1);
			else modify(id,1);
		}
		ans=max(ans,mxlsum[1]);
	}
	write(ans);
    return 0;
}
```

---

