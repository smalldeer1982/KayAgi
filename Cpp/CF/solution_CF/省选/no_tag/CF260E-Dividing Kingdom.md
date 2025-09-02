# Dividing Kingdom

## 题目描述

A country called Flatland is an infinite two-dimensional plane. Flatland has $ n $ cities, each of them is a point on the plane.

Flatland is ruled by king Circle IV. Circle IV has 9 sons. He wants to give each of his sons part of Flatland to rule. For that, he wants to draw four distinct straight lines, such that two of them are parallel to the $ Ox $ axis, and two others are parallel to the $ Oy $ axis. At that, no straight line can go through any city. Thus, Flatland will be divided into 9 parts, and each son will be given exactly one of these parts. Circle IV thought a little, evaluated his sons' obedience and decided that the $ i $ -th son should get the part of Flatland that has exactly $ a_{i} $ cities.

Help Circle find such four straight lines that if we divide Flatland into 9 parts by these lines, the resulting parts can be given to the sons so that son number $ i $ got the part of Flatland which contains $ a_{i} $ cities.

## 说明/提示

The solution for the first sample test is shown below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF260E/f25dd1f6e7f7e19d7007bdb9da678c4a92207eda.png)The solution for the second sample test is shown below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF260E/cfb5bf22cb67c702c1b27adab1d86b1bf50d84b5.png)There is no solution for the third sample test.

## 样例 #1

### 输入

```
9
1 1
1 2
1 3
2 1
2 2
2 3
3 1
3 2
3 3
1 1 1 1 1 1 1 1 1
```

### 输出

```
1.5000000000 2.5000000000
1.5000000000 2.5000000000
```

## 样例 #2

### 输入

```
15
4 4
-1 -3
1 5
3 -4
-4 4
-1 1
3 -3
-4 -5
-3 3
3 2
4 1
-4 2
-2 -5
-3 4
-1 4
2 1 2 1 2 1 3 2 1
```

### 输出

```
-3.5000000000 2.0000000000
3.5000000000 -1.0000000000
```

## 样例 #3

### 输入

```
10
-2 10
6 0
-16 -6
-4 13
-4 -2
-17 -10
9 15
18 16
-5 2
10 -5
2 1 1 1 1 1 1 1 1
```

### 输出

```
-1
```

# 题解

## 作者：1234567s (赞：6)

大意即为，通过两条竖线于两条横线将平面分成九块，给定区域内的点数量和，请求出一种划分方案。  
由于限制过多，九又很小，考虑通过搜索确定每种个数的位置。  
现在我们就需要较快的判定方式。  
首先，通过搜索的位置，每块区域数量固定，可以快速确定分界线。  
接下来只需要判定数量是否正确，转化为二位数点维护即可。  
代码放了跟放了一样，啥用没有。 
```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 1000005
namespace lzz
{
	int n;
	struct node
	{
		int x,y,id;
	}a[N],s[N];
	bool cmp1(node x,node y){return x.x<y.x;}
	bool cmp2(node x,node y){return x.y<y.y;}
	int flag;
	int b[N],o;
//	double ans[5];
	int id[N],bj[N];
//	struct kkk
//	{
//		int x,y,id,op;
//		bool operator<(const kkk &b)const
//		{
//			return x<b.x; 
//		}
//	}q[N];
	int rt[N];
	struct qqq
	{
		int ls,rs,size;
	};
	struct segment_tree
	{
		int cnt=0;
		qqq tree[N<<2];
		void chijiu(int &u){tree[++cnt]=tree[u],u=cnt;}
		void pushup(int p){tree[p].size=tree[tree[p].ls].size+tree[tree[p].rs].size;}
		void modify(int &p,int l,int r,int x,int val)
		{
			if(l>x||r<x)return ;
			chijiu(p);
			if(l==r)
			{
				tree[p].size+=val;
				return ;
			}
			int mid=(l+r)>>1;
			modify(tree[p].ls,l,mid,x,val),modify(tree[p].rs,mid+1,r,x,val);
			pushup(p);
		}
		int query(int u,int v,int l,int r,int L,int R)
		{
			if(l>R||r<L)return 0;
			if(L<=l&&r<=R)return tree[u].size-tree[v].size;
			int mid=(l+r)>>1;
			return query(tree[u].ls,tree[v].ls,l,mid,L,R)+query(tree[u].rs,tree[v].rs,mid+1,r,L,R);
		}
	}T1;
	int u[5],v[5];
	int id1[N],id2[N];
//	struct sss
//	{
//		int x,y,id,op;
//	}q[N]; int cnt;
	int SZ(int x1,int x2,int y1,int y2)
	{
		return T1.query(rt[x2],rt[x1-1],1,o,y1,y2);
	}
	int nd[N];
	void check()
	{
	//	cnt=0;
		u[1]=id1[nd[id[1]]+nd[id[4]]+nd[id[7]]],u[2]=id1[nd[id[1]]+nd[id[4]]+nd[id[7]]+nd[id[2]]+nd[id[5]]+nd[id[8]]];
		v[1]=id2[nd[id[1]]+nd[id[2]]+nd[id[3]]],v[2]=id2[nd[id[1]]+nd[id[2]]+nd[id[3]]+nd[id[4]]+nd[id[5]]+nd[id[6]]];
		
		int a1=id1[nd[id[1]]+nd[id[4]]+nd[id[7]]+1],a2=id1[nd[id[1]]+nd[id[4]]+nd[id[7]]+nd[id[2]]+nd[id[5]]+nd[id[8]]+1];
		int a3=id2[nd[id[1]]+nd[id[2]]+nd[id[3]]+1],a4=id2[nd[id[1]]+nd[id[2]]+nd[id[3]]+nd[id[4]]+nd[id[5]]+nd[id[6]]+1];
		if(s[u[1]].x==s[a1].x||s[u[2]].x==s[a2].x||s[v[1]].y==s[a3].y||s[v[2]].y==s[a4].y)return ;
		
//		cout<<"**"<<u[1]<<" "<<u[2]<<" "<<v[1]<<" "<<v[2]<<endl;
//		a[++cnt]=node({a[u[1]].x,a[v[1]].y,1,1});
//		a[++cnt]=node({a[u[2]].x,a[v[1]].y,2,1});
//		a[++cnt]=node({o,a[v[1]].y,3,1});//这三个区域要依次减
//		 
//		a[++cnt]=node({a[u[1]].x,a[v[2]].y,4,1});
//		a[++cnt]=node({a[u[2]].x,a[v[2]].y,5,1});
//		a[++cnt]=node({o,a[v[2]].y,6,1});
//		
//		a[++cnt]=node({a[u[1]].x,o,1,1});
//		a[++cnt]=node({a[u[2]].x,o,1,1});
//		a[++cnt]=node({o,o,1,1});
	//	cout<<"!!"<<SZ(1,s[u[1]].x,1,s[v[1]].y)<<" "<<nd[id[1]]<<endl;
	//	cout<<nd[id[1]]<<endl;
        // cerr << b[s[u[1]].x]<< ' ' <<b[s[u[2]].x]<< ' ' << b[o] << ' ' <<b[s[v[1]].y]<< ' ' <<b[s[v[2]].y]<<' ' << b[o]<< '\n';
        // cerr << SZ(1,s[u[1]].x,1,s[v[1]].y) << ' ' << SZ(s[u[1]].x+1,s[u[2]].x,1,s[v[1]].y) << ' ' << SZ(s[u[2]].x+1,o,1,s[v[1]].y) << ' ' << 
        // SZ(1,s[u[1]].x,s[v[1]].y+1,s[v[2]].y) << ' ' << SZ(s[u[1]].x+1,s[u[2]].x,s[v[1]].y+1,s[v[2]].y) << ' ' << SZ(s[u[2]].x+1,o,s[v[1]].y+1,s[v[2]].y) << ' ' << 
        // SZ(1,s[u[1]].x,s[v[2]].y+1,o) << ' ' << SZ(s[u[1]].x+1,s[u[2]].x,s[v[2]].y+1,o) << ' ' << SZ(s[u[2]].x+1,o,s[v[2]].y+1,o) << '\n';
		if(SZ(1,s[u[1]].x,1,s[v[1]].y)!=nd[id[1]])return ;
		if(SZ(s[u[1]].x+1,s[u[2]].x,1,s[v[1]].y)!=nd[id[2]])return ;
		if(SZ(s[u[2]].x+1,o,1,s[v[1]].y)!=nd[id[3]])return ;//1 2 3
		
		if(SZ(1,s[u[1]].x,s[v[1]].y+1,s[v[2]].y)!=nd[id[4]])return ;
		if(SZ(s[u[1]].x+1,s[u[2]].x,s[v[1]].y+1,s[v[2]].y)!=nd[id[5]])return ;
		if(SZ(s[u[2]].x+1,o,s[v[1]].y+1,s[v[2]].y)!=nd[id[6]])return ;//4 5 6
		
		if(SZ(1,s[u[1]].x,s[v[2]].y+1,o)!=nd[id[7]])return ;
		if(SZ(s[u[1]].x+1,s[u[2]].x,s[v[2]].y+1,o)!=nd[id[8]])return ;
		if(SZ(s[u[2]].x+1,o,s[v[2]].y+1,o)!=nd[id[9]])return ;//7 8 9
		
		printf("%.3lf %.3lf\n%.3lf %.3lf\n",1.0*(b[s[u[1]].x]+b[s[a1].x])/2,
		1.0*(b[s[u[2]].x]+b[s[a2].x])/2,
		1.0*(b[s[v[1]].y]+b[s[a3].y])/2,
		1.0*(b[s[v[2]].y]+b[s[a4].y])/2
		);flag=1;
	}
	void dfs(int now)
	{
		if(flag)return ;
		if(now==10)
		{
			check();
			return ;
		}
		for(int i=1;i<=9;i++)
		{
			if(!bj[i])
			{
				bj[i]=1;
				id[now]=i,dfs(now+1),bj[i]=0;
			}
		}
	}vector<int>q[N];
	int main()
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)scanf("%d%d",&a[i].x,&a[i].y),a[i].id=i,b[++o]=a[i].x,b[++o]=a[i].y; sort(b+1,b+o+1),o=unique(b+1,b+o+1)-b-1;
		for(int i=1;i<=9;i++)scanf("%d",&nd[i]); for(int i=1;i<=n;i++)a[i].x=lower_bound(b+1,b+o+1,a[i].x)-b,a[i].y=lower_bound(b+1,b+o+1,a[i].y)-b,s[i]=a[i];
		sort(a+1,a+n+1,cmp1);
		for(int i=1;i<=n;i++)id1[i]=a[i].id,q[a[i].x].push_back(a[i].y);
		for(int i=1;i<=o;i++)
		{
			rt[i]=rt[i-1];
			for(int j=0;j<q[i].size();j++)T1.modify(rt[i],1,o,q[i][j],1);
		}
		sort(a+1,a+n+1,cmp2);
		for(int i=1;i<=n;i++)id2[i]=a[i].id;
		dfs(1); if(!flag)cout<<"-1";
		return 0;
	}
}
int main()
{
	return lzz::main();
}
```

---

## 作者：流水行船CCD (赞：5)

这道题还是挺难入手的。

## 算法一

看到分割，没有告诉我们 $9$ 块内点数的顺序，想到枚举四条线段，然后 $O(\log_2 N)$ 的二维数点判断 $9$ 块内点数是否符合条件，但是这样复杂度明显是承受不了的，哪怕我们离散化坐标。

## 算法二

瓶颈在于没有告诉我们 $9$ 块内点数的顺序，很难处理，所以我们考虑搜索确定顺序，将排序后的限制记作 $a_{1 \dots 9}$，分割线记作 $Sx_1,Sx_2,Sy_1, Sy_2$, 则如下图（原点在左下角）：

```

 7 | 8 | 9
---+---+--- Sy2
 4 | 5 | 6
---+---+--- Sy1
 1 | 2 | 3
  Sx1 Sx2
```

对于确定了顺序后的点数，发现现在我们就可以快速确定四条线段的位置，因为我们知道 $Sx_1$ 左侧点个数为 $a_1 + a_4 + a_7$，$Sx_2$ 左侧点个数为 $a_1 + a_4 + a_7 + a_2 + a_5 + a_8$，此时我们只需要将点提前按 $x$ 坐标排序就可以 $O(1)$ 求解分割线的位置（根本不需要二分），$y$ 坐标的分割线同理，代码如下：

```cpp
int Sx1 = dot_sort_x[a[1] + a[4] + a[7]].x, Sx2 = dot_sort_x[Sx1 + a[2] + a[5] + a[8]].x;
int Sy1 = dot_sort_y[a[1] + a[2] + a[3]].y, Sy2 = dot_sort_y[Sy1 + a[4] + a[5] + a[6]].y;
```
确定分割线之后，就是计算分割成的 $9$ 块，每块内部个数是否是满足条件，二维数点问题，用主席树或 CDQ 分治即可求解。注意此时的分割线是整点的坐标，容易混淆，在此基础上加上一个实数偏移量如 $0.5$ 即可。

时间复杂度可以通过。

## AC Code

```cpp
//Largest Common Enemy
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define REP(i, l, r) for (int i = l; i <= r; ++i)
#define PER(i, l, r) for (int i = l; i >= r; --i)
using namespace std;
namespace fast_IO{
// 省略快读
}using namespace fast_IO;
const int N = 2e5 + 7;
namespace nogf {
    int n, arr[10], brr[10], vis[10], lsh[N << 1], V = 0;
    struct Nodes {int x, y;} c[N], d[N];
    inline bool cmp1(Nodes a, Nodes b) {return a.x == b.x ? a.y < b.y : a.x < b.x;}
    inline bool cmp2(Nodes a, Nodes b) {return a.y == b.y ? a.x < b.x : a.y < b.y;}
    struct Node {
        int lc, rc;
#define ls(x) tr[x].lc
#define rs(x) tr[x].rc
        int sz;
    } tr[N * 20]; int Rt[N], trc = 0;
#define pushup(x) (tr[x].sz = tr[ls(x)].sz + tr[rs(x)].sz)
    inline void update(int &x, int old, int l, int r, int now, int c) {
        x = ++trc, tr[x] = tr[old];
        if (l == r) {tr[x].sz += c; return;}
        int mid = (l + r) >> 1;
        if (now <= mid) update(ls(x), ls(old), l, mid, now, c);
        else update(rs(x), rs(old), mid + 1, r, now, c);
        pushup(x); 
    }
    inline int ask(int x, int old, int l, int r, int L, int R) {
        if (L <= l && r <= R) return tr[x].sz - tr[old].sz;
        int mid = (l + r) >> 1, c = 0;
        if (L <= mid) c = ask(ls(x), ls(old), l, mid, L, R);
        if (mid < R) c += ask(rs(x), rs(old), mid + 1, r, L, R);
        return c;
    }
    inline int Sz(int l, int r, int L, int R) {return ask(Rt[r], Rt[l - 1], 1, V, L, R);}
    // 7 | 8 | 9
    //---+---+--- Sy2
    // 4 | 5 | 6
    //---+---+--- Sy1
    // 1 | 2 | 3
    //  Sx1 Sx2
    inline void solve() {
        int Sumx1 = brr[1] + brr[4] + brr[7], Sumx2 = Sumx1 + brr[2] + brr[5] + brr[8];
        if (c[Sumx1 + 1].x == c[Sumx1].x) return; Sumx1 = c[Sumx1].x;
        if (c[Sumx2 + 1].x == c[Sumx2].x) return; Sumx2 = c[Sumx2].x;
        int Sumy1 = brr[1] + brr[2] + brr[3], Sumy2 = Sumy1 + brr[4] + brr[5] + brr[6];
        if (d[Sumy1 + 1].y == d[Sumy1].y) return; Sumy1 = d[Sumy1].y;
        if (d[Sumy2 + 1].y == d[Sumy2].y) return; Sumy2 = d[Sumy2].y;
        if (Sz(1, Sumx1, 1, Sumy1) != brr[1]) return;
        if (Sz(Sumx1 + 1, Sumx2, 1, Sumy1) != brr[2]) return;
        if (Sz(Sumx2 + 1, V, 1, Sumy1) != brr[3]) return;
        if (Sz(1, Sumx1, Sumy1 + 1, Sumy2) != brr[4]) return;
        if (Sz(Sumx1 + 1, Sumx2, Sumy1 + 1, Sumy2) != brr[5]) return;
        if (Sz(Sumx2 + 1, V, Sumy1 + 1, Sumy2) != brr[6]) return;
        if (Sz(1, Sumx1, Sumy2 + 1, V) != brr[7]) return;
        if (Sz(Sumx1 + 1, Sumx2, Sumy2 + 1, V) != brr[8]) return;
        if (Sz(Sumx2 + 1, V, Sumy2 + 1, V) != brr[9]) return;
        double Ansx1 = lsh[Sumx1] + 0.114, Ansx2 = lsh[Sumx2] + 0.514, Ansy1 = lsh[Sumy1] + 0.1919, Ansy2 = lsh[Sumy2] + 0.810;
        printf("%f %f %f %f\n", Ansx1, Ansx2, Ansy1, Ansy2);    
        exit(0);
    }
    inline void Order(int i) {
        if (i > 9) {solve(); return;}
        REP(j, 1, 9) {
            if (vis[j]) continue;
            vis[j] = 1, brr[j] = arr[i], Order(i + 1), vis[j] = 0;
        }
    } vector<int> G[N];
    signed main() {
        ld >> n;
        REP(i, 1, n) 
            ld >> c[i].x >> c[i].y,
            lsh[++V] = c[i].x, lsh[++V] = c[i].y;
        sort(lsh + 1, lsh + V + 1), V = unique(lsh + 1, lsh + V + 1) - lsh - 1;
        REP(i, 1, n) 
            c[i].x = lower_bound(lsh + 1, lsh + V + 1, c[i].x) - lsh,
            c[i].y = lower_bound(lsh + 1, lsh + V + 1, c[i].y) - lsh,
            d[i] = c[i];
        sort(c + 1, c + n + 1, cmp1), sort(d + 1, d + n + 1, cmp2);
        REP(i, 1, n) G[c[i].x].emplace_back(i);
        REP(i, 1, V) { // 建立主席树
            Rt[i] = Rt[i - 1];
            for (auto v : G[i]) update(Rt[i], Rt[i], 1, V, c[v].y, 1);
        }
        ld >> arr[1] >> arr[2] >> arr[3] >> arr[4] >> arr[5] >> arr[6] >> arr[7] >> arr[8] >> arr[9];
        Order(1);
        printf("-1\n");
        return 0;
    }
} 
signed main() {
    nogf::main();
    return 0;
}	
```

---

## 作者：Hyc_ (赞：3)

我们可以考虑枚举全排列，再通过找分割线解决问题。

![](https://cdn.luogu.com.cn/upload/image_hosting/jp7u0yug.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

定义一个全排列数组 $f$ ，如果这是一种解，那么上图中第 $i$ 号格子中城市的数量为 $a_{f_{i}}$。

先把横纵坐标离散化，建立 $x$ 轴,$y$ 轴的两个前缀和数组（接下来没有特殊说明坐标为离散化后的）。

令靠左红线横坐标为 $fx1$，靠右的红线坐标为 $fx2$，靠下的蓝线纵坐标为 $fy1$，靠上的蓝线纵坐标为 $fy2$。

通过前缀和数组二分出 $fx1$、$fx2$、$fy1$、$fy2$ 是否存在就可以初步判断是否有解。

然后再判定 $1,2,3,4,5,6$ 号格子中城市数量是否符合要求（如果前面的符合，那么应为有初步判定 $7,8,9$ 号也一定符合）。

再以横坐标建立一颗树状数组，纵坐标压入相应的 `vector` 中并对每个 `vector` 内部排序，再通过数点时二分纵坐标，就可以求出每个小格子有多少城市了。

时间复杂度：$O(\log_2(n)^2)$，空间复杂度：$O(n\log_2(n))$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,a[12],bx[N],by[N],lenx,leny,f[12],sx[5],sy[5];
struct node{int x,y;}c[N];
struct tree{
	int t[N],n;
	inline void add(int i){++t[i];}
	inline void init(){
		for(int i=1;i<=n;++i)
			t[i]+=t[i-1];
	}
	inline int find(int x){
		int l=1,r=n,mid,s;
		while(l<=r){
			mid=l+r>>1,s=t[mid];
			if(s==x)return mid;
			if(s<x)l=mid+1;
			else r=mid-1;
		}
		return 0;
	}
}tx,ty;
vector<int>t[N];
inline void add(int i,int x){
	for(;i<=tx.n;i+=i&-i)
		t[i].push_back(x);
}
inline int query(int i,int x){
	int sum=0;
	for(;i;i^=i&-i)
		sum+=upper_bound(t[i].begin(),t[i].end(),x)-t[i].begin();
	return sum;
}
inline void check(){
	int fx1,fx2,fy1,fy2;
	sx[1]=a[f[1]]+a[f[4]]+a[f[7]];
	sx[2]=sx[1]+a[f[2]]+a[f[5]]+a[f[8]];
	sy[1]=a[f[1]]+a[f[2]]+a[f[3]];
	sy[2]=sy[1]+a[f[4]]+a[f[5]]+a[f[6]];
	fx1=tx.find(sx[1]);if(!fx1)return;
	fx2=tx.find(sx[2]);if(!fx2)return;
	fy1=ty.find(sy[1]);if(!fy1)return;
	fy2=ty.find(sy[2]);if(!fy2)return;
	if(query(fx1,fy1)!=a[f[1]])return;
	if(query(fx1,fy2)-a[f[1]]!=a[f[4]])return;
	if(query(fx2,fy1)-a[f[1]]!=a[f[2]])return;
	if(query(fx2,fy2)-a[f[1]]-a[f[2]]-a[f[4]]!=a[f[5]])return;
	if(query(tx.n,fy1)-a[f[1]]-a[f[2]]!=a[f[3]])return;
	if(query(tx.n,fy2)-a[f[1]]-a[f[2]]-a[f[3]]-a[f[4]]-a[f[5]]!=a[f[6]])return;
	printf("%.1lf %.1lf\n",bx[fx1]+0.5,bx[fx2]+0.5);
	printf("%.1lf %.1lf\n",by[fy1]+0.5,by[fy2]+0.5);
	exit(0);
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;++i){
		cin>>bx[i]>>by[i];
		c[i]={bx[i],by[i]};
	}
	for(int i=1;i<=9;++i)
		cin>>a[i],f[i]=i;
	sort(bx+1,bx+n+1),sort(by+1,by+n+1);
	tx.n=lenx=unique(bx+1,bx+n+1)-bx-1;
	ty.n=leny=unique(by+1,by+n+1)-by-1;
	for(int i=1;i<=n;++i){
		c[i].x=lower_bound(bx+1,bx+lenx+1,c[i].x)-bx;
		c[i].y=lower_bound(by+1,by+leny+1,c[i].y)-by;
		add(c[i].x,c[i].y),tx.add(c[i].x),ty.add(c[i].y);
	}
	tx.init(),ty.init();
	for(int i=1;i<=tx.n;++i)sort(t[i].begin(),t[i].end());
	do{check();}while(next_permutation(f+1,f+10));
	cout<<"-1\n";
	return 0;
}
```

---

## 作者：红黑树 (赞：1)

[可能更好的阅读体验](https://rbtr.ee/CF260E)

## [题意](https://codeforces.com/contest/260/problem/E)
平面上有 $n$ 个点，你要找到一种方式，画出两条横线和两条竖线，使得可以将平面分成 $9$ 个部分，将第 $i$ 个部分里包含的点数记为 $b_i$，要求 $b$ 是给定的 $a$ 的一个排列。

$1 \leq n \leq 10^5$

## 题解
由于洛谷的死板限制，我这里需要设 $k = 9$，来避免复杂度重出现“常数”。

我们用 $k!$ 的时间枚举所有的排列 $b$。

对原先横坐标和纵坐标排序后就可以知道此时分割线的位置。

然后用一个树套树就可以知道每个部分的点的个数了，判断是否与 $b$ 匹配即可。

复杂度 $\mathcal O\left(n \log^2 n + k! \cdot \log^2 n\right)$。

## 代码
```cpp
constexpr tp Hat_N = 1e5 + 3;
 
tp x[Hat_N], y[Hat_N];
PTT p[Hat_N];
vector<tp> all[Hat_N * 4];
 
void build(tp x, tp l, tp r) {
  for (tp i = l; i <= r; ++i) all[x].push_back(p[i].second);
  if (l != r) {
    stable_sort(FULL(all[x]));
    tp mid = (l + r) / 2;
    build(x * 2, l, mid);
    build(x * 2 + 1, mid + 1, r);
  }
}
 
tp query(tp x, tp l, tp r, tp qa, tp qb) {
  if (p[l].first > qa) return 0;
  if (p[r].first <= qa) {
    // bg(upper_bound(FULL(all[x]), qb) - all[x].begin());
    return upper_bound(FULL(all[x]), qb) - all[x].begin();
  }
  tp mid = (l + r) / 2;
  return query(x * 2, l, mid, qa, qb) + query(x * 2 + 1, mid + 1, r, qa, qb);
}
 
signed STRUGGLING([[maybe_unused]] unsigned long TEST_NUMBER) {
  tp n = bin;
  for (tp i = 1; i <= n; ++i) bin >> x[i] >> y[i];
  for (tp i = 1; i <= n; ++i) p[i] = PTT(x[i], y[i]);
  stable_sort(x + 1, x + n + 1);
  stable_sort(y + 1, y + n + 1);
  stable_sort(p + 1, p + n + 1);
  vector<tp> a = bin.vcr(9);
  vector<tp> b(9); iota(FULL(b), 0);
  vector<tp> c(9);
  build(1, 1, n);
  do {
    for (tp i = 0; i < 9; ++i) c[i] = a[b[i]];
    tp foo = c[0] + c[3] + c[6];
    tp bar = foo + c[1] + c[4] + c[7];
    tp baz = c[0] + c[1] + c[2];
    tp qux = baz + c[3] + c[4] + c[5];
    if (x[foo] == x[foo + 1] || y[baz] == y[baz + 1]) continue;
    if (x[bar] == x[bar + 1] || y[qux] == y[qux + 1]) continue;
    if (query(1, 1, n, x[foo], y[baz]) != c[0]) continue;
    if (query(1, 1, n, x[foo], y[qux]) != c[0] + c[3]) continue;
    if (query(1, 1, n, x[bar], y[baz]) != c[0] + c[1]) continue;
    if (query(1, 1, n, x[bar], y[qux]) != c[0] + c[1] + c[3] + c[4]) continue;
    bin << x[foo] + .5 << " " << x[bar] + .5 << "\n" << y[baz] + .5 << " " << y[qux] + .5 << "\n";
    return 0;
  } while (next_permutation(FULL(b)));
  bin << "-1\n";
  return 0;
}
 
void MIST() {
}
 
// :\ *//
```

---

## 作者：MoonPie (赞：1)

## Solution - CF260E

[题目连接](https://codeforces.com/problemset/problem/260/E)

### 题意

平面上有 $n$ 个点，还有一个长度为 $9$ 的数列 $a$ 满足 $\sum_{i=1}^{9}a_i=n$.

你需要画水平和竖直的直线各两条，将平面分为 $9$ 个部分，每个部分的点数记为 $b_1,b_2\dots b_9$.

要求 $b$ 是 $a$ 的一种排列. 请你输出任意一种方案；若无解，输出 $-1$.

### 题解

这里提供一种 **树状数组** 的做法.

由于 $9$ 很小，可以暴力枚举每一种 $a$ 的排列，然后判断是否可行.

如果直接在线查询，显然需要主席数来支持二维数点，

但如果我们先 **初步判断** 一下是否可行，就是 *横竖* 的三大部分是否满足要求，这个可以用离散化+前缀和 $logn$ 求出.

然后把可以的点离线下来.  现在的点分为两种：原来给的 $n$ 个点，和后面加进来需要判断是否有解的点.

按横坐标从小到达，纵坐标从小到大给所有点排个序，

依次扫过来，

如果是第一种点，就按 **纵坐标** 加入树状数组中；

如果是第二中点，就判断 比其 **纵坐标** 小的点的数量是否满足要求.

由于已经排序，树状数组中的点 **横坐标** 肯定比当前点小，只需关心 **纵坐标** 即可.

### Code

```cpp
const int N=1e5+5,M=4e6,mod=998244353;
int n,cx,cy,cq=0;
// 一共最多 2n 种竖线  原来的 中间的
// 让原来的线全部都在偶数下标
int X[N],pre_x[N];  
int Y[N],pre_y[N];
int a[10],pl[10],tot_p;
map<ll,int> mp;

struct coor 
{ 
    int x,y,num,b;
}po[N],pin[M];

struct question
{ 
    int x[4],y[4],b[4];
}que[M/2];

int tr[M*2],ok[M];
void add(int x,int v) {
    for(;x<=cy*2+1;x+=x&-x) tr[x]+=v;
}
int ask(int x) {
    int res=0;
    for(;x;x-=x&-x) res+=tr[x];
    return res;
}

bool cmp(coor a,coor b) {
    if(a.x!=b.x) return a.x<b.x;
    else return a.y<b.y;
}
void solve() {
    cin>>n;
    for(int i=1;i<=n;++i) {
        scanf("%d%d",&po[i].x,&po[i].y);
        X[i] = po[i].x;
        Y[i] = po[i].y;
    }
    tot_p = n;
    sort(X+1,X+n+1);
    sort(Y+1,Y+n+1);
    cx = unique(X+1,X+n+1)-X-1;
    cy = unique(Y+1,Y+n+1)-Y-1;

    for(int i=1;i<=n;++i) {
        po[i].x = lower_bound(X+1,X+cx+1,po[i].x)-X;
        po[i].y = lower_bound(Y+1,Y+cy+1,po[i].y)-Y;
        pin[i].x=po[i].x*2;
        pin[i].y=po[i].y*2;
        pre_x[po[i].x]++;
        pre_y[po[i].y]++;
    }

    for(int i=1;i<=cx;++i) pre_x[i]+=pre_x[i-1];
    for(int i=1;i<=cy;++i) pre_y[i]+=pre_y[i-1];

    for(int i=1;i<=9;++i) scanf("%d",&a[i]),pl[i]=i;
    
    for(int fx,fy,i=1;i<=362880;++i,next_permutation(pl+1,pl+10)) {
        ll key=0;
        for(int j=1;j<=9;++j) key=(1ll*key*(n+1)%mod+1ll*a[pl[j]])%mod;
        if(mp[key]) continue;
        mp[key]=1;

        int xx=0,yy=0;
        int tx1,tx2,ty1,ty2;

        xx = a[pl[1]]+a[pl[4]]+a[pl[7]];
        fx = lower_bound(pre_x+1,pre_x+cx+1,xx)-pre_x;
        if(pre_x[fx] == xx) tx1 = fx*2+1;
        else {continue;}
        xx += a[pl[2]]+a[pl[5]]+a[pl[8]];
        fx = lower_bound(pre_x+1,pre_x+cx+1,xx)-pre_x;
        if(pre_x[fx] == xx) tx2 = fx*2+1;
        else {continue;}

        yy = a[pl[1]]+a[pl[2]]+a[pl[3]];
        fy = lower_bound(pre_y+1,pre_y+cy+1,yy)-pre_y;
        if(pre_y[fy] == yy) ty1 = fy*2+1;
        else {continue;}
        yy += a[pl[4]]+a[pl[5]]+a[pl[6]];
        fy = lower_bound(pre_y+1,pre_y+cy+1,yy)-pre_y;
        if(pre_y[fy] == yy) ty2 = fy*2+1;
        else {continue;}

        /* 
        找出所有 满足大块的要求的划分 -> 已经满足了6个要求
        每一种划分可以变成4个点
        离线下来，然后一起判断是否满足另外3个要求
        表示插在 X[fx] / Y[fy] 的后面
        */

        ++cq;
        que[cq].x[0] = tx2; que[cq].y[0] = ty2; que[cq].b[0] = a[pl[1]]+a[pl[4]]+a[pl[2]]+a[pl[5]];
        que[cq].x[1] = tx1; que[cq].y[1] = ty1; que[cq].b[1] = a[pl[1]];
        que[cq].x[2] = tx1; que[cq].y[2] = ty2; que[cq].b[2] = a[pl[1]]+a[pl[4]];
        que[cq].x[3] = tx2; que[cq].y[3] = ty1; que[cq].b[3] = a[pl[1]]+a[pl[2]];


        for(int j=0;j<=3;++j) {
            tot_p++;
            pin[tot_p].x=que[cq].x[j];
            pin[tot_p].y=que[cq].y[j];
            pin[tot_p].num=cq;
            pin[tot_p].b=que[cq].b[j];
        }
    }
    
    sort(pin+1,pin+tot_p+1,cmp);

    for(int i=1;i<=tot_p;++i) {
        if(pin[i].x%2) 
        {   // 询问点
            if(ask(pin[i].y) == pin[i].b) ok[pin[i].num]++;
            if(ok[pin[i].num] == 4) {
                int op = pin[i].num;
                printf("%0.9lf %0.9lf\n",1.0*(X[que[op].x[1]/2]+X[que[op].x[1]/2+1])/2,1.0*(X[que[op].x[3]/2]+X[que[op].x[3]/2+1])/2);
                printf("%0.9lf %0.9lf\n",1.0*(Y[que[op].y[1]/2]+Y[que[op].y[1]/2+1])/2,1.0*(Y[que[op].y[2]/2]+Y[que[op].y[2]/2+1])/2);
                return ;
            }
        }
        else 
        {  // 原来点
            add(pin[i].y , 1);
        }
    }
    cout<<"-1\n";
}
```

---

## 作者：liujiaxi123456 (赞：1)

## 关键词：搜索，二维数点，rank1 代码
### 思路：
没有什么性质，考虑想办法创造一些性质。

观察到只有 9 个 $a$，考虑花掉 $9!$ 的时间把每个 $a$ 对应的块枚举出来。

发现由于确定了 $a$ 过后，每一条直线左右/上下的点数量是固定的，可以直接求出直线的位置。

但是由于在二分中直线是把两个维度分开考虑的，所以还需要判断是否合法，具体的，把左下 4 个块二维数点，判断与对应的 $a$ 是否相符，剩下 5 个块由于 $\sum a_i=n$，就不用判断了。
### Code：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int Maxn = 1e5+5;
int Ma, Mb, reala[Maxn], realb[Maxn];

class ChairManTree {
private:
	int num; 
	struct Segment { int lson, rson, sum; } seg[Maxn*20];
	inline int copy(int t) { return seg[++num] = seg[t], num; }
public:
	inline int Modify(int t, int pos) {
		int  l = 1, r = Mb, mid, rt = copy(t); 
		for(t=rt; l^r; ) {
			seg[t].sum++, mid = (l+r)>>1;
			if(pos <= mid)	r = mid, t = seg[t].lson = copy(seg[t].lson);
			else 	l = mid+1, t = seg[t].rson = copy(seg[t].rson);
		}
		return seg[t].sum++, rt;
	}
	inline int Query(int t, int pos) {
		int l = 1, r = Mb, mid, res = 0;
		for(; l^r; ) {
			mid = (l+r)>>1;
			if(pos <= mid)	r = mid, t = seg[t].lson;
			else 	res += seg[seg[t].lson].sum, l = mid+1, t = seg[t].rson;
		}
		return res + seg[t].sum;
	}
	inline void print(int t, int l=1, int r=Mb) {
		if(!t)	return ;
		printf("t:%d, l:%d, r:%d, sum:%d, lson:%d, rson:%d\n", t, realb[l], realb[r], seg[t].sum, seg[t].lson, seg[t].rson);
		int mid = (l+r)>>1; print(seg[t].lson, l, mid), print(seg[t].rson, mid+1, r);
	}
} tree;

namespace Josh_zmf {
	
	int N, a[Maxn], b[Maxn], rnka[Maxn], rnkb[Maxn], rt[Maxn], f[9], g[9]; bool vis[9];
	vector <int> have[Maxn];

	inline void solve(int tim) {
		if(tim == 9) {
			int x1 = a[rnka[g[0]+g[3]+g[6]]], x2 = a[rnka[N-g[2]-g[5]-g[8]]]; // 两条竖线
			int y1 = b[rnkb[g[6]+g[7]+g[8]]], y2 = b[rnkb[N-g[0]-g[1]-g[2]]]; // 两条横线
			if(x1 == a[rnka[g[0]+g[3]+g[6]+1]] || x2 == a[rnka[N-g[2]-g[5]-g[8]+1]])	return ;
			if(y1 == b[rnkb[g[6]+g[7]+g[8]+1]] || y2 == b[rnkb[N-g[0]-g[1]-g[2]+1]])	return ;
			if(tree.Query(rt[x1], y1) != g[6])	return ;
			if(tree.Query(rt[x1], y2) != g[6]+g[3])	return ;
			if(tree.Query(rt[x2], y1) != g[6]+g[7])	return ;
			if(tree.Query(rt[x2], y2) != g[6]+g[3]+g[7]+g[4])	return ;
			// printf("g[0~2]:: %d, %d, %d\n", g[0], g[1], g[2]);
			// printf("g[3~5]:: %d, %d, %d\n", g[3], g[4], g[5]);
			// printf("g[6~8]:: %d, %d, %d\n", g[6], g[7], g[8]);
			// printf("g[0+3+6]:%d->a:%d\n", g[0]+g[3]+g[6], reala[x1]);
			// printf("g[N-2-5-8]:%d->a:%d\n", N-g[2]-g[5]-g[8], reala[x2]);
			// printf("g[6+7+8]:%d->b:%d\n", g[6]+g[7]+g[8], realb[y1]);
			// printf("g[N-0-1-2]:%d->b:%d\n", N-g[0]-g[1]-g[2], realb[y2]);
			printf("%lf %lf\n%lf %lf\n", reala[x1]+0.5, reala[x2]+0.5, realb[y1]+0.5, realb[y2]+0.5);
			exit(0);
		}
		for(int i=0; i<9; i++) if(!vis[i]) vis[i] = 1, g[tim] = f[i], solve(tim+1), vis[i] = 0;
	}

	inline int main() {
		cin>> N;
		for(int i=1; i<=N; i++) {
			cin>> a[i]>> b[i], rnka[i] = rnkb[i] = i;
			reala[i] = a[i], realb[i] = b[i]; 
		}
		sort(rnka+1, rnka+1+N, [&](const int &x, const int &y) { return a[x] < a[y]; } );
		sort(rnkb+1, rnkb+1+N, [&](const int &x, const int &y) { return b[x] < b[y]; } );
		sort(reala+1, reala+1+N), Ma = unique(reala+1, reala+1+N) - (reala+1);
		sort(realb+1, realb+1+N), Mb = unique(realb+1, realb+1+N) - (realb+1);
		for(int i=1; i<=N; i++) {
			a[i] = lower_bound(reala+1, reala+1+Ma, a[i]) - reala;
			b[i] = lower_bound(realb+1, realb+1+Mb, b[i]) - realb;
			have[a[i]].push_back(b[i]);
			// rt[a[i]] = tree.Modify((rt[a[i]] ?rt[a[i]] :rt[a[i]-1]), b[i]);
			// printf("i:%d, a:%d, b:%d, rt[%d]:%d:: \n", i, a[i], b[i], a[i], rt[a[i]]), tree.print(rt[a[i]]), puts("");
		}
		for(int i=1; i<=Ma; i++) {
			rt[i] = rt[i-1];
			for(int y: have[i])	rt[i] = tree.Modify(rt[i], y);
			// printf("rt[%d]:%d:: \n", reala[i], rt[i]), tree.print(rt[i]), puts("");
		}
		for(int i=0; i<9; i++)	cin>> f[i];
		solve(0), cout<< "-1\n";
		return 0;
	}

}

int main() {
	Josh_zmf::main();
	return 0;
}
```
### 结语：
都看到这里了，点个赞再走吧。：）

---

## 作者：cike_bilibili (赞：0)

首先肯定要枚举 $b$ 数组的全排列，再对于每一块区域画出分割线，直接做是不好做的，但我们可以利用每两条分割线（假设边界上有分割线）之间的三个区域的城市和并使用二分转成判定性问题，最后要判断每一个区域中的城市数是否合法。

代码较为冗长，谨慎观看。
```cpp
#include <bits/stdc++.h>
#define ls tree[i].lson
#define rs tree[i].rson
using namespace std;
inline int read(){
	int ans=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		ans=(ans<<1)+(ans<<3)+ch-'0';
		ch=getchar();
	}
	return w*ans;
}
int n;
struct node{
	int x,y;
	bool operator<(const node &a)const{
		return x<a.x;
	}
}a[100005];
int Root[100005];
struct Segment_tree{
	struct tree{
		int lson;
		int rson;
		int val;
	}tree[10000005];
	int tim;
	void add(int &b,int i,int l,int r,int pos,int val){
		b=++tim,tree[b]=tree[i];
		tree[b].val+=val;
		if(l==r)return;
		int mid=l+r>>1;
		if(mid>=pos)add(tree[b].lson,ls,l,mid,pos,val);
		else add(tree[b].rson,rs,mid+1,r,pos,val);
	}
	int ask(int x,int y,int l,int r,int L,int R){
		if(l>R||r<L)return 0;
		if(l>=L&&r<=R)return tree[y].val-tree[x].val;
		int mid=l+r>>1;
		return ask(tree[x].lson,tree[y].lson,l,mid,L,R)+ask(tree[x].rson,tree[y].rson,mid+1,r,L,R);
	}
}T;
int b[100005]; 
int li[100005],lcnt;
map<int,int>Map;
int blx[100005],bly[100005];
bool vis[15];
int p[15];
bool check(int h1,int h2,int l1,int l2){
	if(T.ask(0,Root[l1],1,n,1,h1)!=p[1])return 0;
	if(T.ask(Root[l1],Root[l2],1,n,1,h1)!=p[2])return 0;
	if(T.ask(Root[l2],Root[n],1,n,1,h1)!=p[3])return 0;
	if(T.ask(0,Root[l1],1,n,h1+1,h2)!=p[4])return 0;
	if(T.ask(Root[l1],Root[l2],1,n,h1+1,h2)!=p[5])return 0;
	if(T.ask(Root[l2],Root[n],1,n,h1+1,h2)!=p[6])return 0;
	if(T.ask(0,Root[l1],1,n,h2+1,n)!=p[7])return 0;
	if(T.ask(Root[l1],Root[l2],1,n,h2+1,n)!=p[8])return 0;
	if(T.ask(Root[l2],Root[n],1,n,h2+1,n)!=p[9])return 0;
	return 1;
}
void solve(){
	int h1=0,h2=0,l1=0,l2=0;
	int L=1,R=n;
	while(L<=R){
		int mid=L+R>>1;
		if(T.ask(0,Root[n],1,n,1,mid)<=p[1]+p[2]+p[3])h1=mid,L=mid+1;
		else R=mid-1;
	}
	L=h1+1,R=n;
	while(L<=R){
		int mid=L+R>>1;
		if(T.ask(0,Root[n],1,n,h1+1,mid)<=p[4]+p[5]+p[6])h2=mid,L=mid+1;
		else R=mid-1;
	}
	L=1,R=n;
	while(L<=R){
		int mid=L+R>>1;
		if(T.ask(Root[0],Root[mid],1,n,1,n)<=p[1]+p[4]+p[7])l1=mid,L=mid+1;
		else R=mid-1;
	}
	L=l1+1,R=n;
	while(L<=R){
		int mid=L+R>>1;
		if(T.ask(Root[l1],Root[mid],1,n,1,n)<=p[2]+p[5]+p[8])l2=mid,L=mid+1;
		else R=mid-1;
	}
	if(check(h1,h2,l1,l2)){
		printf("%.5lf %.5lf\n%.5lf %.5lf",blx[l1]+0.5,blx[l2]+0.5,bly[h1]+0.5,bly[h2]+0.5);
		exit(0);
	}
}
void dfs(int now){
	if(now==10){
		solve();
		return;
	}
	for(int i=1;i<=9;i++){
		if(vis[i])continue;
		vis[i]=1;
		p[now]=b[i];
		dfs(now+1);
		p[now]=0;
		vis[i]=0;
	}
}
int main(){
	n=read();
	for(int i=1;i<=n;i++){
		a[i].x=read(),a[i].y=read();
	}
	sort(a+1,a+1+n); 
	li[0]=-2e9;
	for(int i=1;i<=n;i++)li[i]=a[i].x;
	sort(li+1,li+1+n);
	for(int i=1;i<=n;i++){
		if(li[i]>li[i-1])++lcnt;
		Map[li[i]]=lcnt;
		blx[lcnt]=li[i];
	}
	for(int i=1;i<=n;i++)a[i].x=Map[a[i].x];
	Map.clear(),lcnt=0;
	for(int i=1;i<=n;i++)li[i]=a[i].y;
	sort(li+1,li+1+n);
	for(int i=1;i<=n;i++){
		if(li[i]>li[i-1])++lcnt;
		Map[li[i]]=lcnt;
		bly[lcnt]=li[i];
	}
	for(int i=1;i<=n;i++)a[i].y=Map[a[i].y];
	//离散化
	for(int i=1;i<=9;i++)b[i]=read();
	for(int i=1;i<=n;i++){
		if(a[i].x>a[i-1].x)Root[a[i].x]=Root[a[i-1].x];
		T.add(Root[a[i].x],Root[a[i].x],1,n,a[i].y,1);
	}
	for(int i=a[n].x+1;i<=n;i++)Root[i]=Root[i-1];
	dfs(1);
	cout<<-1;
}
/*
枚举排列
7 | 8 | 9 
========= h2
4 | 5 | 6
========= h1
1 | 2 | 3 
  l1  l2
*/
```

---

