# [ICPC 2017 WF] Visual Python++

## 题目描述

# 题意

有 $n$ 个矩形，每个矩形左上角为 $(r_1,c_1)$ ，右下角为 $(r_2,c_2)$。

矩形可以嵌套（矩形包含在其他矩形中）任意层。在合法的情况下，任意两个矩形要么是嵌套的（一个包含在另一个中），要么是不交的（不重叠）。在这两种情况中，他们的 **边界也不能重叠**。

## 样例 #1

### 输入

```
2
4 7
9 8
14 17
19 18
```

### 输出

```
2
1
```

## 样例 #2

### 输入

```
2
4 7
14 17
9 8
19 18
```

### 输出

```
1
2
```

## 样例 #3

### 输入

```
2
4 8
9 7
14 18
19 17
```

### 输出

```
syntax error
```

## 样例 #4

### 输入

```
3
1 1
4 8
8 4
10 6
6 10
10 10
```

### 输出

```
syntax error
```

# 题解

## 作者：FxorG (赞：9)

## 前言：这题真是扫描线好题！

## $\text{Solution}$

先离散化下。

考虑贪心，每次让一个右下角匹配列最近的合法左上角（合法指的是行在它同行或者上面）

那么这个样子匹配出来一定是最优的，实现可以用个 set。

无解的情况：

1. 仍有一部分右下角无法匹配到左上角

2. 如何判断矩形是否嵌套或者不交呢？这就要用扫描线了。

![](https://cdn.luogu.com.cn/upload/image_hosting/nfd916d1.png)

扫到红色的边 $+1$ ，绿色的边 $-1$ 。

那么我们在查询小矩阵时，答案是不是 $4$ ？即 $4$ 个顶点。在查询大矩阵的时候答案也是 $4$ ，因为小矩阵的贡献在经过第三条蓝色边之后已经被消除了。

![](https://cdn.luogu.com.cn/upload/image_hosting/5u678n9n.png)

考虑嵌套，我们在查询第一个矩形的贡献时，自然就不是 $4$ 了。

可以得到，假如我们匹配方案合法，那么一定满足扫描线出来的答案是 $4n$.


## $\text{Code}$
```cpp
#include <bits/stdc++.h>

#define N (int)(4e5+5)
#define fir first
#define sec second
#define IT set<pair<int,int> >::iterator
#define ED return puts("syntax error"),0;
#define ll long long

using namespace std;
int rd() {
	int f=1,sum=0; char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-') f=-1;ch=getchar();}
	while(isdigit(ch)) {sum=(sum<<3)+(sum<<1)+ch-'0';ch=getchar();}
	return sum*f;
}

struct node {
	int x,y,id;
	bool operator < (const node &qwq) const {
		return x<qwq.x;
	}
}a[N],b[N];

pair<int,int>p[N];
set<pair<int,int> >s;
vector<int>d[N];
vector<pair<int,int> >q[N];
int n,m,c[N],match[N],tot,vcnt;
IT it;

ll sum[N];
int lowbit(int x) {
	return x&(-x);
}

void add(int x,int v) {
	while(x<N) sum[x]+=1ll*v,x+=lowbit(x);
}

int qry(int x) {
	int res=0;
	while(x) res+=sum[x],x-=lowbit(x);
	return res;
}

int main() {
	n=rd();
	for(int i=1;i<=n;i++) a[i].x=rd(),a[i].y=rd(),a[i].id=i;
	for(int i=1;i<=n;i++) b[i].x=rd(),b[i].y=rd(),b[i].id=i;
	for(int i=1;i<=n;i++) p[++tot]=make_pair(a[i].x,i),p[++tot]=make_pair(b[i].x,i+n);
	sort(p+1,p+1+tot);
	for(int i=1;i<=tot;i++) {
		if(p[i].sec<=n) a[p[i].sec].x=p[i].fir==p[i-1].fir?vcnt:++vcnt;
		else b[p[i].sec-n].x=p[i].fir==p[i-1].fir?vcnt:++vcnt; 
	}
	tot=vcnt=0;
	for(int i=1;i<=n;i++) p[++tot]=make_pair(a[i].y,i),p[++tot]=make_pair(b[i].y,i+n);
	sort(p+1,p+1+tot);
	for(int i=1;i<=tot;i++) {
		if(p[i].sec<=n) a[p[i].sec].y=p[i].fir==p[i-1].fir?vcnt:++vcnt;
		else b[p[i].sec-n].y=p[i].fir==p[i-1].fir?vcnt:++vcnt;
	} 
	sort(a+1,a+1+n); sort(b+1,b+1+n);
	int j=1;
	for(int i=1;i<=n;i++) {
		while(j<=n&&a[j].x<=b[i].x) s.insert(make_pair(a[j].y,j)),++j;
		it=s.upper_bound(make_pair(b[i].y,n));
		if(it==s.begin()) ED;
		c[i]=(--it)->sec; s.erase(it);
	}
	for(int i=1;i<=n;i++) {
		d[a[c[i]].x].push_back(b[i].y); d[b[i].x+1].push_back(-b[i].y);
		d[a[c[i]].x].push_back(a[c[i]].y); d[b[i].x+1].push_back(-a[c[i]].y); 
		q[a[c[i]].x].push_back(make_pair(a[c[i]].y,b[i].y));
		q[b[i].x].push_back(make_pair(a[c[i]].y,b[i].y));
	}
	ll res=0;
	for(int i=1;i<=2*n;i++) {
		for(int j=0;j<d[i].size();j++) {
			int qwq=d[i][j];
			if(qwq>0) add(qwq,1);
			else add(-qwq,-1);
		}
		for(int j=0;j<q[i].size();j++) {
			res+=qry(q[i][j].sec)-qry(q[i][j].fir-1);
		}
	}
	if(res!=1ll*4*n) ED;
	for(int i=1;i<=n;i++) match[a[c[i]].id]=b[i].id;
	for(int i=1;i<=n;i++) printf("%d\n",match[i]);
	return 0;
} 
```

---

