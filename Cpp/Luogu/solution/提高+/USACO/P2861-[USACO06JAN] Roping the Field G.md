# [USACO06JAN] Roping the Field G

## 题目描述

约翰真是一个自然派艺术大师，他常常在他的田地上创作一些巨大的艺术杰作。今天，他想在麦田上创作一幅由绳索构成的巨画。他的麦田是一个多边形，由 $N\ (1 \le N \le 150)$ 个篱笆粧和之间的篱笆围成。为了创作他的巨画，他打算用尽量多的数量的绳索，笔直地连接两个不相邻的篱笆粧。但是为了画作的优美，任意两根绳索不得交叉。

约翰有一个难处：一些邪恶的外星人在他的麦田上整出了 $G\ (0 \le G \le 100)$ 个怪圈。这些怪圈都有一定的半径 $R\ (1\le R\le 100000)$。他不敢惹外星人，所以不想有任何绳索通过这些怪圈，即使碰到怪圈的边际也不行。这些怪圈的圆心都在麦田之内，但一些怪圈可能有部分在麦田之外。一些篱笆或者篱笆粧都有可能在某一个怪圈里。

给出篱笆粧和怪圈的坐标，计算最多的绳索数。所有的坐标都是 $[0,10^6]$ 内的整数。

## 说明/提示

样例解释：唯一一条绳索连接了 $(10,7)$ 和 $(2,0)$。

## 样例 #1

### 输入

```
5 3 1
6 10
10 7
9 1
2 0
0 3
2 2
5 6
8 3```

### 输出

```
1```

# 题解

## 作者：Iscream2001 (赞：3)

其实这题不难但是不知道为什么没人过。。

首先看到题目应该是几何题无误（假装很有道理

看到n<=150感觉似乎暴力也能过。。想想边数最多也只有22500条。。。

于是这时候应该马上想到先预处理每条边是否可以连。。。

于是怎么与预处理呢。。。。。。

直接算圆和线段的交点？感觉应该可以但是似乎不怎么好写。。。

考虑题意。。只要线段有部分含于圆内就不能连。。而这个“部分”可以直接认为是线段上与圆心最近的点。。

于是这个预处理就转化成了求点到线段的最小距离。。这个套套公式就好。。感觉三分也可以但是tle了（可能是我写炸了。。

预处理完之后，考虑怎么求答案。。。

要求线段之间不可以相交。。。。

说白了就是不能有1->4 , 2->5这样的线段同时存在。。考虑DP。。那肯定只能区间DP了。。

n<=150的话O(n^3)还是很轻松的吧

推销一波我的博客：
http://www.cnblogs.com/Yuigahama/p/8672146.html

然后是代码
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<algorithm>
#define N 20050
#define ept 1e-6
using namespace std;
int n,m;
double R;
struct P{
	double x,y;
}a[200],b[200];
int f[200][200];
bool vis[200][200];
double dis(P u,P v){
	return sqrt((u.x-v.x)*(u.x-v.x)+(u.y-v.y)*(u.y-v.y));
}
double DIS(P u,P v,P w) {  
    double space=0;  
    double a,b,c;  
    a=dis(u,v);
    b=dis(u,w);  
    c=dis(v,w);
    if(c<=ept||b<=ept) {  
        space=0;  
        return space;  
    }  
    if(a<=ept){  
        space=b;  
        return space;  
    }  
    if(c*c>=a*a+b*b){  
        space=b;  
        return space;  
    }  
    if(b*b>=a*a+c*c) {  
        space=c;  
        return space;  
    }  
    double p=(a+b+c)/2;
    double s=sqrt(p*(p-a)*(p-b)*(p-c));
    space=2*s/a; 
    return space;
}
bool judge(P u,P v,P w){
	double d1=DIS(u,v,w);
	if(d1>R) return 0;
	return 1;
}
bool check(P u,P v){
	for(int i=1;i<=m;i++)
		if(judge(u,v,b[i])) return 0;
	return 1;
}
int main(){
	scanf("%d%d%lf",&n,&m,&R);
	for(int i=1;i<=n;i++)
		scanf("%lf%lf",&a[i].x,&a[i].y);
	for(int i=1;i<=m;i++)
		scanf("%lf%lf",&b[i].x,&b[i].y);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i==j) continue;
			vis[i][j]=check(a[i],a[j]);
		}
	}
	for(int len=3;len<=n;len++){
		for(int i=1;i<=n-len+1;i++){
			for(int j=i;j<=i+len-1;j++)
				f[i][i+len-1]=max(f[i][i+len-1],f[i][j]+f[j][i+len-1]);
			if(vis[i][i+len-1]&&(i!=1||i+len-1!=n))
				f[i][i+len-1]++;
		}
	}
	printf("%d\n",f[1][n]);
	return 0;
}
```

---

