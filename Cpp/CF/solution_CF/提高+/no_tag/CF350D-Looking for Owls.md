# Looking for Owls

## 题目描述

### 题意简述
给出一些圆和线段。

定义一个“猫头鹰”是满足以下四个条件的一条线段和两个圆的集合。
1. 两个圆半径相等
1. 两个圆没有交点
1. 两个圆关于线段对称
1. 两个圆圆心的连线和线段有交点

请找出图上不同“猫头鹰”的数量。

## 样例 #1

### 输入

```
1 2
3 2 3 -2
0 0 2
6 0 2
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3 2
0 0 0 1
0 -1 0 1
0 -1 0 0
2 0 1
-2 0 1
```

### 输出

```
3
```

## 样例 #3

### 输入

```
1 2
-1 0 1 0
-100 0 1
100 0 1
```

### 输出

```
0
```

# 题解

## 作者：ran_qwq (赞：0)

枚举两个圆，先把前两个条件判掉。满足条件三和四当且仅当线段和两圆连心线的中垂线重合，且线段经过连心线的中点。

所以每条直线答案是独立的。考虑对于一条直线，把它作为连心线的中垂线的所有连心线中点找出来，再把在它上面的线段找出来，计算这么一个问题：

- 对每个连心线中点，求有多少条线段包含它。

直接差分做即可，不需要二维偏序。

实现较为繁琐。

```cpp
int n,m,l,rk[]={0,2,1,3}; ll ans;
struct LINE {int x1,y1,x2,y2;} p[N];
struct CIR {int x,y,r;} q[N];
#define NODE tuple<db,db,int>
map<NODE,vpii> m1,m2,m3;
void QwQ() {
	n=rd(),m=rd();
	for(int i=1;i<=n;i++) {
		p[i]={rd(),rd(),rd(),rd()}; NODE t; db k,b;
		if(p[i].x1==p[i].x2) t={0,p[i].x1,1};
		else if(p[i].y1==p[i].y2) t={0,p[i].y1,0};
		else k=1.*(p[i].y1-p[i].y2)/(p[i].x1-p[i].x2),b=p[i].y1-k*p[i].x1,t={k,b,0};
		if(p[i].x1>p[i].x2||p[i].x1==p[i].x2&&p[i].y1>p[i].y2) swap(p[i].x1,p[i].x2),swap(p[i].y1,p[i].y2);
		m2[t].pb({p[i].x1,p[i].y1}),m3[t].pb({p[i].x2,p[i].y2});
	}
	for(int i=1;i<=m;i++) q[i]={rd(),rd(),rd()};
	for(int i=1;i<m;i++) for(int j=i+1;j<=m;j++) {
		if(q[i].r!=q[j].r||hypot(q[i].x-q[j].x,q[i].y-q[j].y)<=q[i].r*2) continue;
		db mx=0.5*(q[i].x+q[j].x),my=0.5*(q[i].y+q[j].y),k,b; NODE t;
		if(q[i].x==q[j].x) t={0,my,0};
		else if(q[i].y==q[j].y) t={0,mx,1};
		else k=-1.*(q[i].x-q[j].x)/(q[i].y-q[j].y),b=my-k*mx,t={k,b,0};
		if(m2.count(t)) m1[t].pb({mx,my});
	}
	for(auto [t,v1]:m1) {
		vpii &v2=m2[t],&v3=m3[t]; int cnt=0;
		if(!v2.size()) continue;
		#define pip pair<int,pii>
		#define vpip vector<pip>
		vpip v;
		for(auto p:v1) v.pb({1,p});
		for(auto p:v2) v.pb({2,p});
		for(auto p:v3) v.pb({3,p});
		sort(v.begin(),v.end(),[&](pip a,pip b) {return a.sec!=b.sec?a.sec<b.sec:rk[a.fir]<rk[b.fir];});
		for(auto [ty,p]:v)
			if(ty==1) ans+=cnt;
			else if(ty==2) cnt++;
			else cnt--;
	} 
	wrll(ans,"\n");
}
```

---

