# [COTS 2020] 王国 Kraljevstvo

## 题目背景

译自 [Izborne Pripreme 2020 (Croatian IOI/CEOI Team Selection)](https://hsin.hr/pripreme2020/) D1T1。$\texttt{1s,0.5G}$。


## 题目描述


给定二维平面上的 $N$ 个点。选择 $K$ 个点，最大化这 $K$ 个点的凸包面积。

此外，要求必须选择平面上 $x$ 坐标最小/最大的两个点。保证这两个点所在的与 $y$ 轴平行的直线上没有其他点，且这两个点的 $y$ 坐标为 $0$。

只需要输出最大的面积。


## 说明/提示

####

- 样例 $1$ 解释：选择 $(0, 0), (2, −7),(2, 8) , (9, 0) $ 即可。
- 样例 $2$ 解释：选择 $(0, 0), (10, 0) ,
(5, −5) $ 即可。

亦可参阅下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/jp2ibsfe.png)



#### 数据范围

对于 $100\%$ 的数据，保证：

- $3\le K\le N\le 3\, 000$；
- 给出的点不重合；
- $x$ 坐标最小/最大的点唯一，且对应的点的 $y$ 坐标为 $0$。


| 子任务编号 | $N\le $ | 得分 |  
| :--: | :--: | :--: |
| $ 1 $    | $20$ |$ 11 $   |  
| $ 2 $    | $100$ | $ 25 $   |  
| $ 3 $    | $500$ | $ 15 $   |  
| $ 4 $    | $3\, 000$ | $ 49 $   |  

## 样例 #1

### 输入

```
6 4
0 0
9 0
2 8
6 5
2 -7
8 -7```

### 输出

```
67.5```

## 样例 #2

### 输入

```
5 3
0 0
10 0
5 0
5 5
5 -5```

### 输出

```
25```

## 样例 #3

### 输入

```
8 5
0 0
15 0
2 -2
4 12
10 -14
6 -12
2 -10
13 10```

### 输出

```
238```

# 题解

## 作者：andychen_2012 (赞：1)

对于 $N \le 20$，直接 $O({N \choose K})$ 枚举每个点是否取即可。

对于 $N \le 500$，可以设计一个 $O(N^3)$ 的 dp，设 $f_{i,j}$ 表示在 $i$ 个点中选出 $j$ 个点的最大面积。我们将点划分为上半部分和下半部分，将极左极右点各分到一个部分中，分别从左到右，按凸的方向排序，然后分别做一次 dp，转移方程为：

$$
f_{i,j}=\max_{t=j-1}^{i-1} \{f_{t,j-1}+S_{\triangle p_tp_iP}\}
$$

其中 $P$ 为最左点或最右点。可以获得 51 分。

对于 $N \le 3000$，我们取出上凸包和下凸包，而后注意到对于凸包上的点的面积和满足四边形不等式：$\forall a<b<c<d$，$S_{\triangle p_ap_dP}+S_{\triangle p_bp_cP} < S_{\triangle p_ap_cP}+S_{\triangle p_bp_dP}$。要证明这一点，我们可以考虑相减，令 $P=(0,0)$，上式可以转化为

$$
\frac{1}{2}((x_b-x_a)(y_d-y_c)-(y_b-y_a)(x_d-x_c))<0
$$

注意到这相当于 $\overrightarrow{p_ap_b} \times \overrightarrow{p_cp_d}<0$，由于 $a,b,c,d$ 按顺时针排列，且在凸包上，所以该式成立。

因此我们四边形优化 dp 即可。

代码如下：

```cpp
const int N=3005;
const int inf=1e9;
int n,k;
struct point{ll x,y;}p1[N],p2[N],p[N];
int sz1,sz2,sz;
inline bool cmp1(point a,point b){return a.x^b.x?a.x<b.x:a.y<b.y;}
inline bool cmp2(point a,point b){return a.x^b.x?a.x>b.x:a.y>b.y;}
ll f[N][N];
ll mx1[N],mx2[N];
inline ll area(point a,point b,point c){
	ll x1=b.x-a.x,y1=b.y-a.y;
	ll x2=c.x-a.x,y2=c.y-a.y;
	return x1*y2-x2*y1;
}
inline void DP(int id,int l,int r,int pl,int pr){
	if(l>r) return;
	int mid=(l+r)>>1;
	int opt=l;
	for(int i=pl;i<=pr;++i){
		if(i>=mid) break;
		ll cost=f[id-1][i]+area(p[i],p[1],p[mid]);
//		printf("area(%d,%d,%d)=%lld\n",0,i-1,mid-1,area(p[i],p[1],p[mid]));
		if(cost>=f[id][mid]){
			f[id][mid]=cost;
			opt=i;
		}
	}
	DP(id,l,mid-1,pl,opt);
	DP(id,mid+1,r,opt,pr);
}
int main(){
//	freopen("input.txt","r",stdin);
//	freopen("1.out","w",stdout);
	n=read(),k=read();
	for(int i=1,x,y;i<=n;++i){
		x=read(),y=read();
		p[++sz]={x,y};
	}
	sort(p+1,p+sz+1,cmp1);
	for(int i=1;i<=sz;++i){
		while(sz1>=2&&area(p1[sz1-1],p1[sz1],p[i])>=0)
			--sz1;
		p1[++sz1]=p[i];
	}
	reverse(p+1,p+sz+1);
	for(int i=1;i<=sz;++i){
		while(sz2>=2&&area(p2[sz2-1],p2[sz2],p[i])>=0)
			--sz2;
		p2[++sz2]=p[i];
	}
//	reverse(p2+1,p2+sz2+1);
//	for(int i=1;i<=sz1;++i) printf("%lld %lld\n",p1[i].x,p1[i].y);
//	puts("");
//	for(int i=1;i<=sz2;++i) printf("%lld %lld\n",p2[i].x,p2[i].y);
//	puts("");
	sz=sz1;
	for(int i=1;i<=sz;++i) p[i]=p1[i];
	f[0][1]=0;
	for(int i=2;i<=sz;++i) f[0][i]=-(1ll<<60);
	for(int i=1;i<=k;++i){
		for(int j=0;j<=sz;++j) f[i][j]=0;
		DP(i,1,sz,1,sz);
		mx1[i]=f[i][sz];
	}
	sz=sz2;
	for(int i=1;i<=sz;++i) p[i]=p2[i];
	f[0][1]=0;
	for(int i=2;i<=sz;++i) f[0][i]=-(1ll<<60);
	for(int i=1;i<=k;++i){
		for(int j=0;j<=sz;++j) f[i][j]=0;
		DP(i,1,sz,1,sz);
		mx2[i]=f[i][sz];
	}
	ll ans=0;
	for(int i=1;i<=k&&i<=sz1;++i){
		for(int j=1;i+j<=k&&j<=sz2;++j)
			ans=max(ans,mx1[i]+mx2[j]);
	}
	if(ans&1) printf("%lld.5\n",ans/2);
	else printf("%lld\n",ans/2);
	return 0;
}
```

---

