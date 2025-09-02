# Largest N

## 题目描述

[problemUrl]: https://atcoder.jp/contests/nikkei2019-2-final/tasks/nikkei2019_2_final_c

$ H $ 行 $ W $ 列 のマス目があり、それぞれのマスは黒または白で塗られています。上から $ i $ 行目、左から $ j $ 列目のマスをマス $ (i,\ j) $ と呼びます。

マス $ (a_i,\ b_i)\ (1\ \leq\ i\ \leq\ K) $ は白で塗られており、それ以外の $ H\ \times\ W\ -\ K $ マスは黒で塗られています。

$ 1 $ 以上の整数 $ k $ に対してマス目がサイズ $ k $ の `N` を含むとは、次の条件をみたす整数 $ i,\ j $ が存在することを言います。

- マス $ (i\ +\ t,\ j)\ (0\ \leq\ t\ <\ k) $ がすべて黒
- マス $ (i\ +\ t,\ j\ +\ t)\ (0\ \leq\ t\ <\ k) $ がすべて黒
- マス $ (i\ +\ t,\ j\ +\ k\ -\ 1)\ (0\ \leq\ t\ <\ k) $ がすべて黒

ただし、この条件に関わる全てのマスが $ H $ 行 $ W $ 列のマス目に含まれなければなりません。

このマス目に含まれる `N` のサイズの最大値を求めてください。ただし、どのサイズの `N` も含まない場合は、$ 0 $ を出力してください。

## 说明/提示

### 制約

- $ 1\ \leq\ H,\ W\ \leq\ 3000 $
- $ 0\ \leq\ K\ \leq\ \mathrm{min}(H\ \times\ W,\ 2\ \times\ 10^5) $
- $ 1\ \leq\ a_i\ \leq\ H $
- $ 1\ \leq\ b_i\ \leq\ W $
- $ (a_i,\ b_i)\ \neq\ (a_j,\ b_j)\ (i\ \neq\ j) $
- 入力は全て整数である

### Sample Explanation 1

マス目は以下の状態になっています。(`#` が黒、`.` が白で塗られていることを表しています) ``` ##.# #### ##.# ``` このとき、$ i\ =\ 1,\ j\ =\ 2 $ とすれば $ k\ =\ 3 $ に対して条件を満たすのでこのマス目はサイズ $ 3 $ の `N` を含み、これが最大です。

### Sample Explanation 2

マス目は以下の状態になっています。 ``` .. .. ``` どのサイズの `N` も含まれないので、$ 0 $ を出力してください。

### Sample Explanation 3

マス目は以下の状態になっています。 ``` .# #. ``` $ i\ =\ 2,\ j\ =\ 1 $ または $ i\ =\ 1,\ j\ =\ 2 $ とすれば $ k\ =\ 1 $ に対して条件を満たします。

### Sample Explanation 4

マス目は以下の状態になっています。 ``` ##.# ##.# #.## #..# ```

## 样例 #1

### 输入

```
3 4 2
1 3
3 3```

### 输出

```
3```

## 样例 #2

### 输入

```
2 2 4
2 1
1 1
1 2
2 2```

### 输出

```
0```

## 样例 #3

### 输入

```
2 2 2
1 1
2 2```

### 输出

```
1```

## 样例 #4

### 输入

```
4 4 5
2 3
1 3
4 2
4 3
3 2```

### 输出

```
4```

# 题解

## 作者：nueryim (赞：2)

## 题解：AT_nikkei2019_2_final_c Largest N

### 题意

给你一个矩阵，标记其中的一些点，让你求出最大的一个 $N$ 满足：

- **$N$ 上的点不能有标记**
- **$N$ 是“正”的**，不允许翻转
- **$N$ 是“方”的**，也就是说如果把 $N$ 放进一个正方形，$N$ 的两竖作为正方形的两条边的话，那 $N$ 中间的一斜就在正方形对角线上

### 分析

注意此题时限 $4$ 秒，我们考虑考虑有没有什么暴力的方法。

我们可以 $\mathcal{O(n^2)}$ 预处理出每个点直向上最多能延伸到哪个没有标记的点，存 $up$ 数组里；同时预处理出每个点斜向左上方最多能延伸到哪个没有标记的点，存进 $sli$ 数组里。

统计答案时 $\mathcal{O(n^2)}$ 枚举 $N$ 的右下角 $(i,j)$，然后枚举 $N$ 的边长 $k$，计算出 $N$ 的左下角 $(i,j-k+1)$。如果 $N$ 上没有标记的点，即 $k\leq up_{i,j}$ 同时 $k\leq sli_{i,j}$ 并且 $k\leq up_{i,j-k+1}$。那么用 $k$ 更新答案。

时间复杂度 $\mathcal{O(n^3)}$，但实际可以跑的更快，具体看代码。

### 代码

~~~cpp
//AT_nikkei2019_2_final_c

#include <iostream>
#include <cstdio>

using namespace std;

int read()
{
    int res = 0, f = 1;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar())
        if (ch == '-')
            f = -1;
    for (; isdigit(ch); ch = getchar())
        res = (res << 3) + (res << 1) + (ch - '0');
    return res * f;
}

const int N = 3005;

int n, m, k, ans;
int up[N][N], sli[N][N];
bool mp[N][N];

int main()
{
    n = read(), m = read(), k = read();
    for (int i = 1, x, y; i <= k; i ++)
    {
        x = read(), y = read();
        mp[x][y] = 1;
    }
    //预处理
    for (int i = 1; i <= n; i ++)
        for (int j = 1; j <= m; j ++)
            if (!mp[i][j])
            {
                up[i][j] = up[i - 1][j] + 1;
                sli[i][j] = sli[i - 1][j - 1] + 1;
            }
    for (int i = 1; i <= n; i ++)
        for (int j = 1; j <= m; j ++)
        {
            int tmp = min(up[i][j], sli[i][j]);
            if (mp[i][j] || tmp <= ans)
                continue;
            //只枚举能够对答案有贡献的k
            for (int k = ans; k <= tmp && j - k + 1 >= 1 && i - k + 1 >= 1; k ++)
                if (up[i][j - k + 1] >= k)
                    ans = max(ans, k);
        }
    printf("%d\n", ans);

    return 0;
}
~~~

---

## 作者：phil071128 (赞：1)

> 给定一个 $n\times m$ 的 01 序列，求由 $1$ 构成的 `N` 的最大大小。要求左右高度相同。$n,m\le 3000$。

枚举 `N` 的左上角 $(i,j)$，可以二分出左边的竖线和斜线的最长大小 $len$，然后要求一个最大的 $k\in[j+1,j+len-1]$，满足 $(i,k)$ 向下延伸的连续 $1$ 长度不低于 $(k-j+1)$。


设 $b_{i,k}$ 为该位置的最长向下延伸长度，则有 $b_{i,k}-k+j-1\ge 0$，因此线段树下标为 $k$ 的位置维护 $b_{i,k}-k+j-1$，使用线段树二分即可单 $\log$ 找到这个最大的 $k$。时间复杂度 $O(nm\log m)$。


```cpp
#include <bits/stdc++.h>
#define ll long long
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
int read(){
	char c=getchar();int h=0,tag=1;
	while(!isdigit(c)) tag=(c=='-'?-1:1),c=getchar();
	while(isdigit(c)) h=(h<<1)+(h<<3)+(c^48),c=getchar();
	return h*tag;
}
void fil(){
	freopen("data.in","r",stdin);
	freopen("data.out","w",stdout);
}
const int N=3050;
int a[N][N],hang[N][N],lie[N][N],xie[N][N],b[N][N];
struct seg{
	int t[N*4],tag[N*4];
	#define ls(x) (x<<1)
	#define rs(x) (x<<1|1)
	#define mid ((l+r)>>1)
	void push_up(int p) {
		t[p]=max(t[ls(p)],t[rs(p)]);
	}
	void push_down(int p) {
		t[ls(p)]+=tag[p],t[rs(p)]+=tag[p];
		tag[ls(p)]+=tag[p],tag[rs(p)]+=tag[p];
		tag[p]=0; 
	}
	void build(int p,int l,int r) {
		t[p]=tag[p]=0;
		if(l==r) return;
		build(ls(p),l,mid);build(rs(p),mid+1,r);
	}
	int query(int p,int l,int r,int nl,int nr) {
		if(nl<=l&&r<=nr) {
			return t[p];
		}
		push_down(p); 
		int ans=-1e9+9;
		if(nl<=mid) ans=max(ans,query(ls(p),l,mid,nl,nr));
		if(mid<nr) ans=max(ans,query(rs(p),mid+1,r,nl,nr));
		return ans;
	}
	void update(int p,int l,int r,int nl,int nr,int k) {
		if(nl<=l&&r<=nr) {
			t[p]+=k;tag[p]+=k;
			return ;
		}
		push_down(p);
		if(nl<=mid) update(ls(p),l,mid,nl,nr,k);
		if(mid<nr) update(rs(p),mid+1,r,nl,nr,k);
		push_up(p);
	}
	int binary_search(int p,int l,int r,int nl,int nr) {
		if(l==r) {
			return l;
		}
		push_down(p);
		if(t[rs(p)]>=0) {
			if(mid<nr) return binary_search(rs(p),mid+1,r,nl,nr);
		}
		if(t[ls(p)]>=0) {
			if(nl<=mid) return binary_search(ls(p),l,mid,nl,nr);
		}
		return -1;
	}
	#undef mid
}t;
int main(){
	//fil();
	int h=read(),w=read();
	int k=read();
	for(int i=1;i<=k;i++) {
		int x=read(),y=read();
		a[x][y]=1;
	}
	for(int i=1;i<=h;i++) {
		for(int j=1;j<=w;j++) {
			lie[i][j]=lie[i-1][j]+a[i][j];
			xie[i][j]=xie[i-1][j-1]+a[i][j];
		}
	}
	for(int i=1;i<=w;i++) lie[h+1][i]=lie[h][i]+1;
	for(int i=1;i<=h;i++) {
		for(int j=1;j<=w;j++) {
			int l=0,r=h-i,res=-1;
			while(l<=r) {
				int mid=(l+r)>>1;
				if(lie[i+mid][j]-lie[i-1][j]==0) res=mid,l=mid+1;
				else r=mid-1;
			}
			b[i][j]=res+1;
		}
	}
	int ans=0;
	for(int i=1;i<=h;i++) {
		memset(t.t,0,sizeof t.t);
		memset(t.tag,0,sizeof t.tag);
		for(int j=1;j<=w;j++) {
			t.update(1,1,w,j,j,b[i][j]-j);
		}
		for(int j=1;j<=w;j++) {
			int l=0,r=min(h-i,w-j),res=-1;
			while(l<=r) {
				int mid=(l+r)>>1;
				int tag=0;
				if(lie[i+mid][j]-lie[i-1][j]==0) {
					if(xie[i+mid][j+mid]-xie[i-1][j-1]==0) {
						res=mid;
						l=mid+1;
						tag=1;
					}
				}
				if(tag==0) r=mid-1;
			}
			res++;
			ans=max(ans,t.binary_search(1,1,w,j,j+res-1)-j+1);
			t.update(1,1,w,1,w,+1);
		}
	}
	cout<<ans<<endl;
	return 0;
}


```

---

## 作者：a_blue_cell (赞：0)

显然，这道题的问题是一个与子矩阵相关的问题。

思考一下：我们能不能将矩阵转化成一条线，以至于一个节点呢？

先观察矩阵本身有什么特点：

>该矩阵的最左边一列，最右边一列以及主对角线上的所有点都为黑点。

可以在草稿纸上进行绘画，不能发现：这些黑色节点最终会组成一个`N`字形（其它的黑点不在我们的考虑范围内）：

![](https://cdn.luogu.com.cn/upload/image_hosting/kb6olwoq.png)

为方便后文表述，我们该矩阵行数和列数均为 $k$，设左上角坐标为 $(i,j)$。

现在，我们来看一下如何保证黑色节点最终会组成一个`N`字形，也就是翻译中给出的：

>1.$(i+x,j)$ 为黑点。（$0\le x< k$）

>2.$(i+x,j+k-1)$ 为黑点。（$0\le x< k$）

>3.$(i+x,j+x)$ 为黑点。（$0\le x< k$）

其实就相当于要确保**三条线**上的点全部为黑点。

显然，这三条线的长度都应该为 $k$。

如果我们设黑点的权值为 $1$，白点权值为 $0$，那么，我们只需确保三条线上的权值之和为 $k$，换言之，我们只需确保三个区间的**区间和**为 $k$ 即可。

考虑前缀或后缀和。

这里蒟蒻使用了后缀和。

定义两个数组 `pre_a` 和 `pre_b`，其中，若将 `pre_a[i][j]` 设为 $p$，则 $p=\min\{x\}$（$x$ 满足 $(i+x,j)$ 的权值为 $0$）；同理，若将 `pre_b[i][j]` 设为 $q$，则 $q=\min\{x\}$（$x$ 满足 $(i+x,j+x)$ 的权值为 $0$）。

求法很简单：

```cpp
for(int j=m;j>=1;j--){
	for(int i=n;i>=1;i--){
		if(!flag[i][j]){//如果当前这个点为白点的话，flag[i][j]的结果就是0，而且还会继续影响到接下来的点，所以就直接跳过了
			pre_a[i][j]=pre_a[i+1][j]+1;
		}
	}
}
for(int i=n;i>=1;i--){
	for(int j=m;j>=1;j--){
		if(!flag[i][j]){//同理
			pre_b[i][j]=pre_b[i+1][j+1]+1;
		}
	}
}
```

那么，如果 `pre_a[i][j]>=k`，就说明当前的矩阵是可以满足条件 $1$ 的。大概是下面这个样子：

![](https://cdn.luogu.com.cn/upload/image_hosting/80fiejv3.png)

为什么？`pre_a[i][j]` 存的到底是什么？其实，`pre_a[i][j]` 存的数就相当于向下的方向上，第一个白点与该黑点的距离，就相当于这中间的所有点**全是黑点**，而又有 `pre_a[i][j]>=k`，说明这个矩阵的最左边一列的所有点**全是黑点**。

同理，我们可以将所有的条件改写为：

>1.`pre_a[i][j]>=k`

>2.`pre_b[i][j]>=k`

>3.`pre_a[i][j+k-1]>=k`

枚举 $i,j,k$，更新答案即可。

代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,m,k,x,y,ans=1,OK;
bool flag[3005][3005];
int pre_a[3005][3005];
int pre_b[3005][3005];
int main(){
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=k;i++){
		scanf("%d%d",&x,&y);
		flag[x][y]=1;
		OK++;
	}
	if(OK==n*m){//特判：没有黑点
		printf("0");
		return 0;
	}
	for(int j=m;j>=1;j--){
		for(int i=n;i>=1;i--){
			if(!flag[i][j]){
				pre_a[i][j]=pre_a[i+1][j]+1;
			}
		}
	}
	for(int i=n;i>=1;i--){
		for(int j=m;j>=1;j--){
			if(!flag[i][j]){
				pre_b[i][j]=pre_b[i+1][j+1]+1;
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			for(int k=ans;i+k-1<=n&&j+k-1<=m&&k<=pre_a[i][j]&&k<=pre_b[i][j];k++){
			//在枚举k的时候可以顺便判断当前的k是否满足第1,2个条件
			//小于当前ans的k就没必要枚举了
				if(pre_a[i][j+k-1]>=k){
					ans=max(ans,k);
				}
			}
		}
	}
	printf("%d",ans);
	return 0;
} 
```


---

