# Rectangles and Square

## 题目描述

You are given $ n $ rectangles, labeled 1 through $ n $ . The corners of rectangles have integer coordinates and their edges are parallel to the $ Ox $ and $ Oy $ axes. The rectangles may touch each other, but they do not overlap (that is, there are no points that belong to the interior of more than one rectangle).

Your task is to determine if there's a non-empty subset of the rectangles that forms a square. That is, determine if there exists a subset of the rectangles and some square for which every point that belongs to the interior or the border of that square belongs to the interior or the border of at least one of the rectangles in the subset, and every point that belongs to the interior or the border of at least one rectangle in the subset belongs to the interior or the border of that square.

## 说明/提示

The first test case looks as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF335D/b555a1b2f0fa9850a908273e7c5806edefd08e25.png)Note that rectangles 6, 8, and 9 form a square as well, and would be an acceptable answer.

The second test case looks as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF335D/50fe7d9330ec3e3fa026a900ee9c84c7d3b58755.png)

## 样例 #1

### 输入

```
9
0 0 1 9
1 0 9 1
1 8 9 9
8 1 9 8
2 2 3 6
3 2 7 3
2 6 7 7
5 3 7 6
3 3 5 6
```

### 输出

```
YES 5
5 6 7 8 9
```

## 样例 #2

### 输入

```
4
0 0 1 9
1 0 9 1
1 8 9 9
8 1 9 8
```

### 输出

```
NO
```

# 题解

## 作者：Purslane (赞：2)

# Solution

另一篇题解的复杂度貌似是 $O(nk)$ 的，但是常数比较小，很难卡满。提供一个严格 $O(k^2)$ 的题解。

一个正方形是合法的，当且仅当：

1. 正方形内部所有点都被覆盖。由于所有矩形不交，因此直接计算覆盖的总点数。
2. 边界周长为 $4$ 倍边长。

考虑枚举正方形的一条对角线。对于左下角，我们可以找到满足“左边界和下边界总长为 $2$ 倍边长”的右上角的范围；对于右上角，我们可以找到满足“右边界和上边界总长为 $2$ 倍边长”的左下角范围，还可以使用双指针找到满足“矩形被完全覆盖”的左下角的范围。

具体的，我们把左上角对应的最高的右上角高度记作序列 $a$，那么我们要做的就是：对于每个 $i$，是否存在 $l \le x < i$（$l$ 是计算出来的常数）使得 $a_x > i$。

使用单调栈，注意到如果 $i<j$ 且 $a_i < a_j$ 那么 $i$ 必定无用，那么这个单调栈是单调递减的；另一方面，如果栈首 $\le i$ 必定也无用，因为我们查询的 $i$ 是单调的。

预处理好多好多东西，可以做到 $O(k^2)$。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=3000+10,MAXM=1e5+10;
int n,m=3000,tl[MAXN][MAXN],tr[MAXN][MAXN],tu[MAXN][MAXN],td[MAXN][MAXN],cov[MAXN][MAXN];
int xl[MAXM],xr[MAXM],yl[MAXM],yr[MAXM];
int a[MAXN],recl[MAXN][MAXN],recr[MAXN][MAXN];
void output(int x0,int y0,int x1,int y1) {
	cout<<"YES ";
	vector<int> ans;
	ffor(i,1,n) if(x0<=xl[i]&&xr[i]<=x1&&y0<=yl[i]&&yr[i]<=y1) ans.push_back(i);
	cout<<ans.size()<<'\n';
	for(auto id:ans) cout<<id<<' ';
	exit(0);	
}
void solve(int x0,int y0,int x1,int y1) {
	stack<int> st;
	int covx=x0,covy=y0;
	int len=x1-x0+1;
	ffor(i,1,len) {
		while(cov[x0+i-1][y0+i-1]-cov[covx][y0+i-1]-cov[x0+i-1][covy]+cov[covx][covy]) covx++,covy++;
		int l=max({covx-x0+1,i-tl[x0+i-1][y0+i-1],i-td[x0+i-1][y0+i-1]});
		while(!st.empty()&&a[st.top()]<i) st.pop();
		if(!st.empty()&&st.top()>=l) output(x0+st.top()-1,y0+st.top()-1,x0+i-1,y0+i-1);
		a[i]=min(i+tr[x0+i-1][y0+i-1],i+tu[x0+i-1][y0+i-1]);
		while(!st.empty()&&a[i]>=a[st.top()]) st.pop();
		st.push(i);
	}
	return ;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	ffor(i,1,n) {
		cin>>xl[i]>>yl[i]>>xr[i]>>yr[i];
		recl[xl[i]][yl[i]]=i;
		recr[xr[i]][yr[i]]=i;
	}
	roff(i,m,0) roff(j,m,0) if(recl[i][j]) {
		int id=recl[i][j];
		tr[i][j]=tr[xr[id]][j]+xr[id]-xl[id];
		tu[i][j]=tu[i][yr[id]]+yr[id]-yl[id];
	}
	ffor(i,0,m) ffor(j,0,m) if(recr[i][j]) {
		int id=recr[i][j];
		tl[i][j]=tl[xl[id]][j]+xr[id]-xl[id];
		td[i][j]=td[i][yl[id]]+yr[id]-yl[id];	
	}
	ffor(i,1,n) {
		int X0=xl[i]+1,X1=xr[i],Y0=yl[i]+1,Y1=yr[i];
		cov[X0][Y0]++,cov[X0][Y1+1]--,cov[X1+1][Y0]--,cov[X1+1][Y1+1]++;
	}
	ffor(i,1,m) ffor(j,1,m) cov[i][j]=cov[i-1][j]+cov[i][j-1]-cov[i-1][j-1]+cov[i][j];
	ffor(i,1,m) ffor(j,1,m) cov[i][j]=cov[i-1][j]+cov[i][j-1]-cov[i-1][j-1]+(cov[i][j]^1);
	ffor(i,0,m) solve(0,i,m-i,m);
	ffor(i,1,m) solve(i,0,m,m-i);
	cout<<"NO";
	return 0;
}
```

---

## 作者：james1BadCreeper (赞：2)

拼成的正方形的右上角一定是一个矩形的右上角，正方形的左下角一定是一个矩形的右下角。然后怎么限制？

注意到所有矩形都不相交。这样我们可以用一些前缀和的方式直接判断一些内容。首先一定能铺满，其次正方形的边界一定由矩形的边界构成。这些都很好使用二维前缀和维护。

枚举正方形的右上角和在这条斜线上的合法左下角，时间复杂度 $O(k^2+n)$。

```cpp
#include <bits/stdc++.h>
using namespace std; 

int n, s[3005][3005]; 
int xl[100005], yl[100005], xr[100005], yr[100005]; 
int b1[3005][3005], b2[3005][3005], b3[3005][3005], b4[3005][3005]; 
vector<int> a[6005]; 

inline bool check(int xl, int yl, int xr, int yr) {
    if (xl > xr) return 0; 
    if ((xr - xl + 1) * (yr - yl + 1) != s[xr][yr] - s[xl - 1][yr] - s[xr][yl - 1] + s[xl - 1][yl - 1]) return 0; 
    if (b1[xr][yl] - b1[xl - 1][yl] != xr - xl + 1) return 0; 
    if (b2[xl][yr] - b2[xl][yl - 1] != yr - yl + 1) return 0; 
    if (b3[xr][yr] - b3[xl - 1][yr] != xr - xl + 1) return 0; 
    if (b4[xr][yr] - b4[xr][yl - 1] != yr - yl + 1) return 0; 
    vector<int> ans; 
    for (int i = 1; i <= n; ++i) if (::xl[i] >= xl && ::xr[i] <= xr && ::yl[i] >= yl && ::yr[i] <= yr) ans.emplace_back(i); 
    cout << "YES " << ans.size() << "\n"; 
    for (int i : ans) cout << i << " "; 
    return cout << "\n", 1; 
}

int main(void) {
    ios::sync_with_stdio(0); cin >> n; 
    for (i-nt i = 1; i <= n; ++i) {
        cin >> xl[i] >> yl[i] >> xr[i] >> yr[i]; ++xl[i], ++yl[i]; 
        a[xl[i] - yl[i] + 3000].emplace_back(i); 
        for (int x = xl[i]; x <= xr[i]; ++x) for (int y = yl[i]; y <= yr[i]; ++y) ++s[x][y]; 
        for (int x = xl[i]; x <= xr[i]; ++x) ++b1[x][yl[i]], ++b3[x][yr[i]]; 
        for (int y = yl[i]; y <= yr[i]; ++y) ++b2[xl[i]][y], ++b4[xr[i]][y]; 
    }
    for (int i = 1; i <= 3000; ++i)
        for (int j = 1; j <= 3000; ++j) 
            s[i][j] += s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1], 
            b1[i][j] += b1[i - 1][j], b2[i][j] += b2[i][j - 1], 
            b3[i][j] += b3[i - 1][j], b4[i][j] += b4[i][j - 1]; 
    for (int i = 1; i <= n; ++i) {
        int t = xr[i] - yr[i] + 3000; 
        for (int x : a[t]) if (check(xl[x], yl[x], xr[i], yr[i])) return 0; 
    }
    return cout << "NO\n", 0; 
}
```

利用数据结构维护上述过程可以做到 $O(n\log n)$，具体可以参考官方题解。

---

