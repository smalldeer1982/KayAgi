# [ICPC 2016 WF] Oil

## 题目背景

_本题征集题目中缺失的“图 G.1”。_

## 题目描述

世界经济的很大一部分依赖于石油，这就是为什么对发现和开采石油的新方法的研究仍然活跃。石油公司的利润在一定程度上取决于他们能够多么有效地钻探石油。国际原油石油联盟（ICPC）希望通过广泛的计算机模拟来更容易地确定如何以最佳方式钻探油井。

每天钻探油井变得越来越困难，因为新发现的油藏通常不是一个整体，而是分裂成许多部分。ICPC 目前关注的是分层沉积物。

为了简化其分析，ICPC 只考虑二维情况，其中油藏被建模为与地球表面平行的水平线段。ICPC 想知道如何放置一个单独的油井以提取最大量的石油。油井沿着一条直线从地面钻井，并可以从其下降的路径上相交的所有沉积物中提取石油，即使相交点位于沉积物的端点处。图 G.1 中显示了一个这样的井，击中三个沉积物。在这个简单的模型中，一个沉积物中含有的石油量等于该沉积物的宽度。你能帮助 ICPC 确定通过一个单井可以提取的最大石油量吗？
![](https://cdn.luogu.com.cn/upload/image_hosting/97ob9pkd.png)

## 样例 #1

### 输入

```
5
100 180 20
30 60 30
70 110 40
10 40 50
0 80 70```

### 输出

```
200```

## 样例 #2

### 输入

```
3
50 60 10
-42 -42 20
25 0 10```

### 输出

```
25```

# 题解

## 作者：tribool4_in (赞：5)

题意理解：油井（直线）不一定垂直于地面，可以是倾斜的，只要不平行于地面就行。

发现 $n\le 2000$，端点个数为 $O(n)$，考虑 $O(n^2)$ 枚举端点以确定直线。容易发现一个性质：经过两条线段端点上的直线一定可以成为最优解。证明考虑对于一条最优解直线，将其平移至与某个端点相交；然后绕着此点旋转直到与另一个端点相交。此时得到的直线的答案与原来相同。

发现直接枚举两个端点无法求出其经过的线段权值和。于是考虑 $O(n)$ 枚举其中一个端点，由其斜率即可确定直线。此时对于所有与其不在同一高度的线段，与之有交的直线斜率构成一段区间。于是问题转化为有若干个带权区间 $[k_l,k_r]$，找出一个位置使得覆盖它的区间权值和最大。$O(n)$ 求出这些区间，排序然后扫一遍即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e3 + 10;
const double eps = 1e-7;
int n;
struct line {
    int x1, x2, y;
} l[N];
#define k(x1, y1, x2, y2) (1.0 * ((x2) - (x1)) / ((y2) - (y1)))
vector<pair<double, int>> ud;
int calc(int x0, int y0) {
    ud.clear();
    for (int i = 1; i <= n; i++) {
        if (l[i].y == y0) continue;
        double k1 = k(x0, y0, l[i].x1, l[i].y), k2 = k(x0, y0, l[i].x2, l[i].y);
        if (k1 > k2) swap(k1, k2);
        ud.emplace_back(k1, abs(l[i].x2 - l[i].x1)), ud.emplace_back(k2 + eps, -abs(l[i].x2 - l[i].x1));
    }
    sort(ud.begin(), ud.end());
    int cur = 0, ans = 0;
    for (auto [k, v] : ud) {
        cur += v;
        ans = max(ans, cur);
    }
    return ans;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> l[i].x1 >> l[i].x2 >> l[i].y;
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        ans = max(ans, calc(l[i].x1, l[i].y) + abs(l[i].x2 - l[i].x1));
        ans = max(ans, calc(l[i].x2, l[i].y) + abs(l[i].x2 - l[i].x1));
    }
    cout << ans << '\n';
    return 0;
}
```

---

## 作者：wwwwwza (赞：1)

假设已经找到了一条最优的直线，将其平移直到不能再次移动，发现这条直线上一定存在至少一个端点。

枚举每一个端点，求出这个端点和其他端点所在直线的斜率（这两个端点的 $y$ 不能相等，不然斜率为 $0$ 不满足题目要求）。

将斜率从小到大排序，然后用类似扫描线的思路扫一遍，第一次遇到一条线段（即遇到这条线段的一个端点）时，将其价值加入，否则将价值减去。

注意，若许多点的斜率相等时，要先处理能加入价值的点。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+5;
const double eps=1e-5;
int n,ans=0;
bool vis[N];
struct node{
	int l,r,x;
}line[N];
struct dot{
	double k;
	int pos;
}a[N];
double calc(int x1,int y1,int x2,int y2){
	return (double)(x1-x2)/(y1-y2);
}
bool cmp(dot p,dot q){
	return p.k<q.k;
}
void solve(int x,int y,int val){
	int tot=0,res=val;
	ans=max(ans,val);
	for(int i=1;i<=n;i++){
		if(line[i].x==y)continue;
		a[++tot]={calc(line[i].l,line[i].x,x,y),i};
		a[++tot]={calc(line[i].r,line[i].x,x,y),i};
		vis[i]=0;
	}
	sort(a+1,a+1+tot,cmp);
//	for(int i=1;i<=tot;i++)cout <<a[i].k<<" "<<a[i].pos<<endl;
	for(int i=1,j=1;i<=tot;i=j+1){
		j=i;
		while(a[j].k==a[i].k&&j<=tot)j++;
		j--;
		int p=res;
		for(int k=i;k<=j;k++){
			if(!vis[a[k].pos]){
				res+=line[a[k].pos].r-line[a[k].pos].l;
			}
		}
		ans=max(ans,res);
		res=p;
		for(int k=i;k<=j;k++){
			if(!vis[a[k].pos]){
				vis[a[k].pos]=1;
				res+=line[a[k].pos].r-line[a[k].pos].l;
			}else{
				vis[a[k].pos]=0;
				res-=line[a[k].pos].r-line[a[k].pos].l;
			}
		}
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d%d",&line[i].l,&line[i].r,&line[i].x);
		if(line[i].l>line[i].r)swap(line[i].l,line[i].r);
	}
	for(int i=1;i<=n;i++){
		solve(line[i].l,line[i].x,line[i].r-line[i].l);
		solve(line[i].r,line[i].x,line[i].r-line[i].l);
	}
	printf("%d",ans);
	return 0;
}
```

---

