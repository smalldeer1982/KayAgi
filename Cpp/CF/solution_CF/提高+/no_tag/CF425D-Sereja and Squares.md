# Sereja and Squares

## 题目描述

Sereja has painted $ n $ distinct points on the plane. The coordinates of each point are integers. Now he is wondering: how many squares are there with sides parallel to the coordinate axes and with points painted in all its four vertexes? Help him, calculate this number.

## 样例 #1

### 输入

```
5
0 0
0 2
2 0
2 2
1 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
9
0 0
1 1
2 2
0 1
1 0
0 2
2 0
1 2
2 1
```

### 输出

```
5
```

# 题解

## 作者：henryhu2006 (赞：2)

## CF425D Sereja and Squares
### 题意
在平面上给定 $n$ 个点，求有多少个所有边 **平行坐标轴** 的正方形，四个顶点都是给定点。

$n\le10^5$, $0 \le x_i,y_i\le 10^5$。

### 分析
首先可以想到两个暴力：

**暴力 1**：枚举纵坐标相同的点对，得到正方形的边长，用哈希表判断剩下的两个点是否是给定点。复杂度最坏 $\Theta(n^2)$。

**暴力 2**：枚举两列，得到两列之间的间隔，即正方形的边长。枚举其中一个列的每个点，用哈希表判断剩下三个点是否是给定点。时间复杂度最坏 $\Theta(n^2)$。

把两个暴力撮合一下。

1. 对于包含点数 $\le \sqrt n$ 的列，进行暴力 1。当有 $\Theta(\sqrt n)$ 个包含 $\Theta (\sqrt n)$ 个点的列时，时间复杂度最差，为 $\Theta (n \sqrt n)$。

2. 枚举所有包含点数 $> \sqrt n$ 的两列，进行暴力 2。这样的列最多有 $\sqrt n$ 个，对于每列，最多被访问 $\sqrt n$ 次，每列长度最大为 $\Theta(n)$，时间复杂度 $\Theta (n\sqrt n)$。

其中，一列小于等于 $\sqrt n$，一列大于 $\sqrt n$ 的情况会在 1 中被统计。

总复杂度 $\Theta(n \sqrt n)$，细节见代码。

### 代码
```cpp
#include<bits/stdc++.h>
#define rint register int
using namespace std;
typedef long long ll;
const int N=1e5+5,K=(1<<17);
int n,id[N],top,ans;
vector<int> vec[N];
struct table{
	int hd[K],nxt[K],x[K],y[K],tot;
	void add(int X,int Y){
		ll k=1ll*X*Y+X+Y;
		x[++tot]=X,y[tot]=Y;
		nxt[tot]=hd[k&(K-1)],hd[k&(K-1)]=tot;
	}
	bool find(int X,int Y){
		ll k=1ll*X*Y+X+Y;
		for(rint i=hd[k&(K-1)];i;i=nxt[i])
			if(x[i]==X&&y[i]==Y) return 1;
		return 0; 
	}
} T; // 哈希表
int main(){
	scanf("%d",&n);
	for(rint i=1,x,y;i<=n;++i){
		scanf("%d%d",&x,&y);
		vec[x].push_back(y),T.add(x,y);
	}
	int S=sqrt(n);
	for(rint x=0;x<=100000;++x){
		if(!vec[x].size()) continue;
		if(vec[x].size()<=S){
			sort(vec[x].begin(),vec[x].end());
			for(rint i=0;i<vec[x].size();++i)
			for(rint j=i+1,len;j<vec[x].size();++j){
				len=vec[x][j]-vec[x][i];
				if(x-len>=0&&T.find(x-len,vec[x][j])&&T.find(x-len,vec[x][i]))
					ans+=(vec[x-len].size()<=S?1:2);
           			// 向左的正方形
				if(x+len<=100000&&T.find(x+len,vec[x][j])&&T.find(x+len,vec[x][i]))
					ans+=(vec[x+len].size()<=S?1:2);
              		// 向右的正方形
              		// 注意：如果正方形的左右边在小于等于 sqrt(n) 的列上，会被计算 2 次，因此答案 + 1
              		// 	 如果正方形的左右边中有且仅有一条在大于 sqrt(n) 的列上，只会被计算一次，因此答案 + 2
			}
		}
		else sort(vec[x].begin(),vec[x].end()),id[++top]=x;
	}
	for(rint t1=1;t1<=top;++t1)
	for(rint t2=t1+1;t2<=top;++t2){
		rint X1=id[t1],X2=id[t2];
		if(vec[X1].size()>vec[X2].size()) swap(X1,X2);
     	// 枚举较小的列，常数优化
		rint len=abs(X1-X2);
		for(rint i=0;i<vec[X1].size();++i)
			if(T.find(X1,vec[X1][i]+len)&&T.find(X2,vec[X1][i])&&T.find(X2,vec[X1][i]+len)) ans+=2;
      	// 只会被计算一次，答案 + 2
	}
	cout<<ans/2; // 最后答案要除以 2
	return 0;
}
```

---

## 作者：Priestess_SLG (赞：0)

很板的根号分治。对每一行内元素数量分治：

+ 若某一行内元素数量 $\le \sqrt n$，则暴力枚举这一行内的两个元素，并用哈希表或类似的 ds 来判断这两个元素是否可以和上面一行或者下面一行的两点组成正方形。特殊的，若四个点所在行元素数量均 $\le \sqrt n$，则该情况会被计算两次，需要额外容斥。
+ 若某一行内元素数量 $>\sqrt n$，则这样的行数目不会超过 $\sqrt n$，因此直接暴力枚举两个这样的行，然后枚举其中一行的任意一个顶点，判断是否存在一个这样的正方形即可。

总时间复杂度为 $O(n\sqrt n)$，可以通过该题。

---

## 作者：_edge_ (赞：0)

来提供一种复杂度神奇，但是能过的做法。

首先，我们考虑暴力怎么做，暴力显然是直接枚举两个点，然后暴力确定另外两个点是否存在。

但是这样显然会被一条直线给 hack，因此，我们要用另外一种智慧的方法来确定值。

我们来思考一下，随便画个正方形，然后我们去枚举那个左下角的那个地方，再在他的正上方和右边枚举两个，但是这样也不够优秀。

这时候就要考虑性质了，正方形的边长全都是相等的，因此我们可以考虑利用两个指针扫描，如果一个距离小了，那就去他的地方，如果相等用 map 来判断右上角这个点是否存在，然后两个指针向后扫。

我并不能很好的证明该算法的复杂度，但是我们会发现这些正方形其实数量挺少的，我这个做法也大致依赖于正方形的个数。

欢迎来 hack 我的题解。

```cpp
#include <iostream>
#include <cstdio>
#include <set>
#include <algorithm>
#include <vector>
#include <map>
#define pb push_back
#define int long long
using namespace std;
const int INF=1e5+5;
int n,k,m,p[INF],p1[INF],x[INF],y[INF];
vector <int> v[INF],vv[INF];
map <int,map<int,int> > L;
void solve() {
	cin>>n;
	for (int i=1;i<=n;i++) 
		cin>>x[i]>>y[i],v[x[i]].pb(y[i]),vv[y[i]].pb(x[i]),L[x[i]][y[i]]=1;
	for (int i=0;i<=1e5;i++) sort(v[i].begin(),v[i].end());
	for (int i=0;i<=1e5;i++) sort(vv[i].begin(),vv[i].end());
	int ans=0;
	for (int i=1;i<=n;i++) {
		int it=lower_bound(v[x[i]].begin(),v[x[i]].end(),y[i])-v[x[i]].begin()+1;
		int it1=lower_bound(vv[y[i]].begin(),vv[y[i]].end(),x[i])-vv[y[i]].begin()+1;
		
		for (int l1=it,l2=it1;l1<v[x[i]].size() && l2<vv[y[i]].size();) {
			while (l2<vv[y[i]].size() && v[x[i]][l1]-y[i]>vv[y[i]][l2]-x[i]) l2++;
			while (l1<v[x[i]].size() && v[x[i]][l1]-y[i]<vv[y[i]][l2]-x[i]) l1++;
			//23333
			if (l1<v[x[i]].size() && l2<vv[y[i]].size()) ;
			else break;
			
//			cout<<x[i]<<" "<<y[i]<<" "<<l1<<" "<<l2<<" "<<v[x[i]][l1]<<" "<<vv[y[i]][l2]<<" qprit\n";
			
			if (v[x[i]][l1]-y[i]==vv[y[i]][l2]-x[i]) 
				ans+=L[vv[y[i]][l2]][v[x[i]][l1]],l1++,l2++;
		}
	}
	cout<<ans<<"\n";
	return ;
}
signed main()
{
	ios::sync_with_stdio(false);
	int t=1;
	while (t--) solve();
	return 0;
}
```


---

