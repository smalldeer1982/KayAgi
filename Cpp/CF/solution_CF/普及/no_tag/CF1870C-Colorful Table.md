# Colorful Table

## 题目描述

You are given two integers $ n $ and $ k $ . You are also given an array of integers $ a_1, a_2, \ldots, a_n $ of size $ n $ . It is known that for all $ 1 \leq i \leq n $ , $ 1 \leq a_i \leq k $ .

Define a two-dimensional array $ b $ of size $ n \times n $ as follows: $ b_{i, j} = \min(a_i, a_j) $ . Represent array $ b $ as a square, where the upper left cell is $ b_{1, 1} $ , rows are numbered from top to bottom from $ 1 $ to $ n $ , and columns are numbered from left to right from $ 1 $ to $ n $ . Let the color of a cell be the number written in it (for a cell with coordinates $ (i, j) $ , this is $ b_{i, j} $ ).

For each color from $ 1 $ to $ k $ , find the smallest rectangle in the array $ b $ containing all cells of this color. Output the sum of width and height of this rectangle.

## 说明/提示

In the first test case, the entire array $ b $ consists of color $ 1 $ , so the smallest rectangle for color $ 1 $ has a size of $ 2 \times 2 $ , and the sum of its sides is $ 4 $ .

In the second test case, the array $ b $ looks like this:

1112One of the corner cells has color $ 2 $ , and the other three cells have color $ 1 $ . Therefore, the smallest rectangle for color $ 1 $ has a size of $ 2 \times 2 $ , and for color $ 2 $ it is $ 1 \times 1 $ .

In the last test case, the array $ b $ looks like this:

1111112221123211222111111

## 样例 #1

### 输入

```
5
2 1
1 1
2 2
1 2
3 5
3 2 4
4 2
1 2 1 2
5 3
1 2 3 2 1```

### 输出

```
4 
4 2 
0 6 6 2 0 
8 6 
10 6 2```

# 题解

## 作者：SunnyYuan (赞：3)

## 思路

当一个数字 $x$ 碰上了比它更大的数字 $y$ 才有可能在 $\min(x, y)$ 被输出。

所以这道题的思路就是对于 $k$，找到**最小**的 $j$ 使得 $a_j \ge k$，找到**最大**的 $p$ 使得 $a_p \ge k$，一定有 $\min(a_j, k) = k, \min(a_p, k) = k$，反过来也一样，$\min(k, a_j) = k, \min(k, a_p) = k$，所以对于 $k$ 的影响力也就 $j\sim p$ 行和 $j \sim p$ 列，所以必须拿长宽都为 $p - j + 1$ 的正方形覆盖，所以答案为长宽之和为 $2(p - j + 1)$（题目要求的）。

## 代码

代码中 `first[i]` 表示数字 $i$ 第一次出现在数组中的位置；`last[i]` 表示数字 $i$ 最后一次出现在数组中的位置；`max_last[i]` 表示最大的坐标 $p$ 使得 $a_p \ge i$；`min_first[i]` 表示最小的坐标 $j$ 使得 $a_j \ge i$。

**还有，一定要注意，如果一个数字没有出现过，那么一定不要计算进去啊！**

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 100010, INF = 0x3f3f3f3f;

int n, k;
int a[N];
int first[N], last[N];
int max_last[N];
int min_first[N];    // 数组的意思都在上面写过了

void solve() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) {
        if (!first[a[i]]) first[a[i]] = i;
        last[a[i]] = i;
    }
    for (int i = 0; i <= k + 1; i++) min_first[i] = INF, max_last[i] = -INF;
    for (int i = k; i >= 1; i--) {
        if (last[i]) max_last[i] = max(max_last[i + 1], last[i]);
        else max_last[i] = max_last[i + 1];    // 如果一个数字没有出现过，那么一定不要计算进去
    }
    for (int i = k; i >= 1; i--) {
        if (first[i]) min_first[i] = min(min_first[i + 1], first[i]);
        else min_first[i] = min_first[i + 1];    // 如果一个数字没有出现过，那么一定不要计算进去
    }
    for (int i = 1; i <= k; i++) {
        if (!first[i]) {
            cout << "0 ";
            continue;
        }
        int p1 = min_first[i], p2 = max_last[i];
        cout << 2 * (p2 - p1 + 1) << ' ';
    }
    cout << '\n';
    for (int i = 0; i <= k; i++) first[i] = last[i] = max_last[i] = min_first[i] = 0;    // 清空
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    while (T--) solve();

    return 0; 
}
```

---

## 作者：xlpg0713 (赞：3)

似乎正解不是这样，我来讲一下我的做法。

### 题意：

给定序列 $a$，构建矩阵 $b$ 使得 $b_{i,j}=\min(a_i,a_j)$。求解对于值域里每一个数：在矩阵上的最小包含矩形的长宽之和。

### 分析：

例如：对于 ${1,4,2,3}$ 的矩阵如下

![](https://z1.ax1x.com/2023/09/19/pP4cWJx.png)

易于发现的性质：该矩阵关于主对角线对称（这是显然的）。另外在这张图上，覆盖 $1,2,3,4$ 的矩形分别为边长为 $4,3,3,1$ 的正方形。

考虑原因：每一个出现的数都一定对称的成对出现，分布在以主对角线为对称轴的正方形的两个顶点，因此最小覆盖矩形一定是正方形。

因此，如果一个数出现在了某一行或某一列的某些位置，对他的最小覆盖的正方形的边长就是对这些位置的最小覆盖（例如在上图中：$3$ 占据了第二列和第四列，那么该正方形的边长就是3）。比较有趣的是，只有一个数完全占据了剩余矩阵的第一行或最后一行（列）下一个数的答案才会有所缩减。

由于图是对称的，我们不妨只对一维考虑。把序列 $a$ 从小到大排序，最小的一定至少占据了一行或一列（既然他是最小，这一行一列的最小值就是他），他的答案就是剩余矩阵的边长。然后统计这一个数对答案的影响：如果删去了头尾的一行，他就会对剩余矩阵有所影响。

做完就行了，统计影响是 $O(n)$ 的，复杂度瓶颈在排序上 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t, n, k, a[100010], b[100010], vis[100010];
inline bool cmp(int x, int y){return a[x] < a[y];}
int main(){ memset(vis, -1, sizeof vis);
    cin >> t; while(t--){
        cin >> n >> k;
        for(int i = 1; i <= n; i++) cin >> a[i];
        for(int i = 1; i <= n; i++) b[i] = i; int l = 1, r = n;
        sort(b + 1, b + n + 1, cmp); int res = n, lasans = 0;
        for(int i = 1; i <= n;){
            for(int j = lasans + 1; j < a[b[i]]; j++) cout << 0 << ' ';
            cout << res * 2 << ' '; int p = i; vis[b[p]] = t;
            while(a[b[p]] == a[b[i]]) vis[b[p++]] = t; lasans = a[b[i]];
            for(l = l; l <= r;){if(vis[l] != t) break; l++, res--;}
            for(r = r; r >= l;){if(vis[r] != t) break; r--, res--;} i = p;
        } for(int i = lasans + 1; i <= k; i++) cout << 0 << ' '; cout << '\n';
    }
}
```

---

## 作者：xwh_hh (赞：2)

一道相当不错的思维题（思维要求也不高吧）。

手造一组数据：
```
6 4
1 4 2 3 4 2
```
表格如下：  
![](https://cdn.luogu.com.cn/upload/image_hosting/v4fjktr0.png)  

---

下面，对于颜色 $2$ 着重分析：  
![](https://cdn.luogu.com.cn/upload/image_hosting/1j5viamz.png)  
对于颜色 $2$，它会与颜色 $2,3,\dots,k$ 产生 $2$，而 $a_2$ 是第一个在 $2,3,\dots,k$ 中的数，所以最上方的 $2$ 出现在第 $2$ 行，最左边的 $2$ 出现在第 $2$ 列。类似的，最下方的 $2$ 出现在第 $6$ 行，最右边的 $2$ 出现在第 $6$ 列，因为 $a_6$ 是最后一个在 $2,3,\dots,k$ 中的数。  
所以，在代码实现中，只需维护数列 $l_i$、$r_i$，分别表示 $\{a\}$ 中第一个 $\ge i$ 的数、$\{a\}$ 中最后一个 $\ge i$ 的数。这个实现起来应该不难，模仿一下之前学习求序列最大值时用的方法即可。  
注意一个小坑点：并不是所有颜色都存在！  
上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100005];
int l[100005],r[100005];
int book[100005];
int t,n,k;
int main(){
	cin>>t;
	while(t--){
		cin>>n>>k;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			book[a[i]]=1;
		}
		int nowmax=0;
		for(int i=1;i<=n;i++){
			if(a[i]>nowmax){//大于当前最大值 
				for(int j=nowmax+1;j<=a[i];j++) l[j]=i;//更新 
				nowmax=a[i];
			}
		}
		nowmax=0;
		for(int i=n;i>=1;i--){
			if(a[i]>nowmax){
				for(int j=nowmax+1;j<=a[i];j++) r[j]=i;
				nowmax=a[i];
			}
		}
		for(int i=1;i<=k;i++) cout<<2*(r[i]-l[i]+1)*book[i]<<' ';
		cout<<'\n';
		for(int i=1;i<=n;i++) a[i]=0;
		for(int i=1;i<=k;i++) book[i]=l[i]=r[i]=0;//清零要规范，防TLE 
	}
	return 0;
}
```


---

## 作者：_空白_ (赞：1)

自己把矩阵画出来后，不难发现，整个矩阵以对角线为轴**轴对称**，因而只要求一条边长，最后结果 $\times2$ 即可。

再看生成方式，发现每个点的值是横纵坐标处**较小**的数组值，因而对于原数组的每一项所在的行和列，只要出现比这个数**更大**或与它**相等**的值，这个位置最后的值就是该数组值。

综上所述，我们想要找到能包含所有某个值的最小矩形（其实是正方形）的边长，只要找到原数组中**大于等于这个值**且位置**最靠左和最靠右**的元素即可（因为所有大于等于这个值的元素都会被填充成它，只要找到最左和最右端点就能求出边长了）。

想要求以上内容直接暴力即可（当然我进行了优化），复杂度 $O(n+k)$（$k$ 为题目中给的原数组值域大小）。

最后别忘了没有出现过的元素不会有边长。

_AC_ _code_

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e5+100;
int a[MAXN]; 
int be[MAXN];
int en[MAXN];
bool fl[MAXN];
int ma;
int mi;
 
int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		int n,k;
		cin>>n>>k;
		ma=0;
		for(int i=1;i<=n;++i)
		{
			cin>>a[i];
			fl[a[i]]=1;
			if(a[i]>ma)
			{
				for(int j=ma+1;j<=a[i];j++)
					be[j]=i;
				ma=a[i];
			}
		}
		
		ma=0;
		
		for(int i=n;i>=1;--i)
		{
			if(a[i]>ma)
			{
				for(int j=ma+1;j<=a[i];j++)
					en[j]=i;
				ma=a[i];
			}
		}
		
		for(int i=1;i<=k;i++)
		{
			
			if(!fl[i])
			{
				en[i]=0;
				be[i]=0;
				cout<<"0 ";
				continue;
			}
			cout<<(en[i]-be[i]+1)*2<<" ";
			fl[i]=0;
			en[i]=0;
			be[i]=0;
		}
		cout<<endl;
	}
	return 0;
}
```


---

## 作者：LIUYC_C (赞：1)

[题目链接](https://www.luogu.com.cn/problem/CF1870C)

## 大体思路：

首先观察到我们肯定是建不出这个图的，那么我们就来观察一下有什么性质。

因为一个坐标的权值为 $\min(a_{i},a_{j})$，那么就不难想到一个最小的 $a_{i}$ 肯定会把它的那一行与那一列都占满，再考虑第二小的，也会把它这一行和一列没有被最小占过的格子都占满，剩下的权值也都是这样。

再考虑它们的答案如何计算，首先最小的权值的答案肯定就是 $2n$，考虑什么时候需要更新答案，当边界被更新时答案才需要更新，可以感性理解，因此，我们可以设出四个边界，左边界，右边界，上边界，下边界，当要更新的点在边界上的时候，边界就降一级或升一级，这样答案的贡献就是：

$down-up+1+right-left+1$。

至于存储问题，我们只需要开两个数组，分别用来判断哪一行或哪一列被占就好了。

我认为代码更好理解：

## 代码实现：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=201010;
vector<int>a[N];
#define int long long 
int h[N];
int l[N];


void solve(){
    
    int n,k;
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        h[i]=0;
        l[i]=0;
    }
    for(int i=1;i<=k;i++){
        a[i].clear();
    }
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        a[x].push_back(i);
    }
    int up=1,down=n,left=1,right=n;
    for(int i=1;i<=k;i++){
        int ans=0;
        for(auto t:a[i]){
            ans=max(ans,down-up+1+right-left+1);
            h[t]=1;
            l[t]=1;
            while(h[up]){
                up++;
            }
            while(h[down]){
                down--;
            }
            while(l[left]){
                left++;
            }
            while(l[right]){
                right--;
            }
        }
        cout<<ans<<" ";
    }cout<<endl;
}


signed main(){
    ios::sync_with_stdio(false);
    int t;
    cin>>t;
    while(t--){
        solve();
    }
}
```
时间复杂度 $O(n+k)$。因为覆盖只需要最多 $n^2$ 次，且跑不满。



---

## 作者：huangrenheluogu (赞：0)

显然是一个长和宽相同的矩形（正方形），因为行和列是等价的。

因为是 $\min$，我们可以让数字从小到大填入，这样空的格子直接填上去。

发现具有对称性，所以可以直接在一维上做完，然后求出来“边长”乘 $2$ 就是答案。

一维怎么做？对于一个数，找到最左边比它大的，最右边比它大的，两个坐标差就是我们求的“边长”。

用二分+线段树维护即可。

那么直接二分线段树上判断即可。

~~VP 的时候出现了罚时，样例没看清导致的；使用倍增导致的。~~

```cpp
#include<bits/stdc++.h>
#define ls p << 1
#define rs p << 1 | 1
using namespace std;
const int N = 1e5 + 5;
int T, n, k, a[N], maxn[N << 2], l, r, mid, lg[N], now, L, R;
vector<int>ver[N];
inline void build(int p, int l, int r){
	if(l == r){
		maxn[p] = a[l];
		return ;
	}
	int mid = l + r >> 1;
	build(ls, l, mid);
	build(rs, mid + 1, r);
	maxn[p] = max(maxn[ls], maxn[rs]);
}
inline int query(int p, int l, int r, int x, int y){
	if(x <= l && r <= y){
		return maxn[p];
	}
	int mid = l + r >> 1, res = 0;
	if(mid >= x) res = max(res, query(ls, l, mid, x, y));
	if(mid < y) res = max(res, query(rs, mid + 1, r, x, y));
	return res;
}
int main(){
	scanf("%d", &T);
	while(T--){
		scanf("%d%d", &n, &k);
		for(int i = 2; i <= n + 5; i++) lg[i] = lg[i >> 1] + 1;
		for(int i = 1; i <= k; i++) ver[i].clear();
		for(int i = 1; i <= n; i++){
			scanf("%d", &a[i]);
			ver[a[i]].push_back(i);
		}
		build(1, 1, n);
		for(int kk = 1; kk <= k; kk++){
			L = n + 1, R = 0;
			for(auto pos : ver[kk]){
				l = pos, r = n;
				while(l <= r){
					mid = l + r >> 1;
					if(query(1, 1, n, mid, n) >= kk) R = max(R, mid), l = mid + 1;
					else r = mid - 1;
				}
				l = 1, r = pos;
				while(l <= r){
					mid = l + r >> 1;
					if(query(1, 1, n, 1, mid) >= kk) L = min(L, mid), r = mid - 1;
					else l = mid + 1;
				}
			}
			if(L > R) printf("0 ");
			else printf("%d ", (R - L + 1) << 1);
		}
		putchar('\n');
	}
	return 0;
}
/*
1
3 5
3 2 4
*/
```

[评测链接](https://codeforces.com/contest/1870/submission/237124073)

---

## 作者：_Wind_Leaves_ShaDow_ (赞：0)

一眼线段树。

对于 $a_i$，当且仅当 $a_j\ge a_i$ 时出现在矩阵。经过画图或者一些简单的推导，我们发现这个矩阵是沿对角线对称的（$\min(x,y)=\min(y,x)$），所以这个矩阵为正方形。

那么答案就是对于一个颜色 $k$，我们找到序列中 **最靠左且比他大的** 和 **最靠右的比他大的** 数的位置 $i$ 和 $j$，然后答案就是 $2(j-i+1)$。

很显然的线段树。

我们维护一个区间最大值，然后递归找上面两个值，写两个递归就好。下面只以前者举例。

查找 $x$ 时，对于一个节点 $p$，如果它的左子树中有大于 $x$ 的，那么往左找，否则往右找。此时我们找到的一定就是最靠左的，因为我们在任何合法情况都选择往左走。

注意一下如果一个数没有出现那么特判掉，否则会出现无法预料理解的小问题。

[随便过](https://www.luogu.com.cn/record/135690768)。

贴代码：

```cpp
#include <bits/stdc++.h>
#define int long long	

using namespace std;
const int N=1e5;

int T,n,K,a[N+5];

int sg[(N<<2)+5];

inline void build(int l,int r,int p){
	sg[p]=a[l];
	if(l==r)return;
	int mid=(l+r)>>1;
	build(l,mid,p<<1);
	build(mid+1,r,p<<1|1);
	sg[p]=max(sg[p<<1],sg[p<<1|1]);
	return; 
}

inline int find(int l,int r,int p,int x){
	if(l==r)return l;
	int mid=(l+r)>>1;
	if(sg[p<<1]>=x)return find(l,mid,p<<1,x);
	else return find(mid+1,r,p<<1|1,x);
}

inline int Find(int l,int r,int p,int x){
	if(l==r)return l;
	int mid=(l+r)>>1;
	if(sg[p<<1|1]>=x)return Find(mid+1,r,p<<1|1,x);
	else return Find(l,mid,p<<1,x);
}

unordered_map<int,bool>mp;

inline void solve(){
	mp.clear();
	cin>>n>>K;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		mp[a[i]]=1;
	}
	build(1,n,1);
	for(int i=1;i<=K;i++)cout<<(mp[i]?((Find(1,n,1,i)-find(1,n,1,i)+1)<<1):0)<<' ';
	cout<<'\n';
	return;
}

signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--)solve();
	return 0;
}
```

---

## 作者：cyz_czy (赞：0)

## 具体思路
看到这题，不妨先自己画一个图模拟一遍。可以发现：因为对于一个数 $a_i$，只有 $a_j \ge a_i$ 时才会写出 $a_i$，所以对于每一个数 $i$，找到最右端不小于 $i$ 的数，记为 $bi_i$，即为 $i$ 的最大单元格行，列编号；找到最左端不小于 $i$ 的数，记为 $smal_i$，即为 $i$ 的最小单元格行，列编号。

为何最大最小单元格行列编号相同呢？因为 $b_{i,j} = \min(a_i,a_j)$，所以 $b_{i,j} = b_{j,i}$，所以编号相同。

想好之后就可以想到二分答案。每个数最靠左大于它的数可以这么求：新建一个数组 $c$，从前往后枚举数组 $a$，如果当前数不小于 $c$ 数组的最后一个数，就加入 $c$ 数组。然后对于当前数在 $c$ 数组中二分，记录最大值即可。最靠右也是同理，只要把枚举方向反过来即可。

最后对于每个数 $i$ 答案即为 $(bi_i - smal_i + 1) \times 2$。

## Code:

```cpp
#include <iostream>

#define int long long

using namespace std;

const int N=2e6+10;

int n,k,p,T;

int a[N],smal[N],bi[N];

struct node{
	int i,num;
}c[N];

signed main(){
	scanf("%lld",&T);
	while(T--){
		
		scanf("%lld %lld",&n,&k); 
		for(int i=1;i<=n;i++)
			scanf("%lld",&a[i]);
		
		for(int i=1;i<=k;i++)
			smal[i]=1e17;

		for(int i=1;i<=n;i++){//计算最小编号 
			
			if(a[i]>=c[p].num){//加入数组 
				
				c[++p].num=a[i];
				c[p].i=i;
			}
			int l=1,r=p;
			while(l<r){//二分，找到不小于它的数 
				
				int mid=(l+r)>>1;
				if(c[mid].num<a[i])
					l=mid+1;
				else
					r=mid;
			}
			
			if(c[l].num<a[i])
				smal[a[i]]=min(smal[a[i]],i);
			else
				smal[a[i]]=min(smal[a[i]],c[l].i);
			//统计答案 
		}
		
		for(int i=0;i<=n;i++)
			c[i]=(node){0,0};
		
		p=0;
		for(int i=n;i>=1;i--){//计算最大编号，过程与上方同理 
			
			if(a[i]>=c[p].num){
				
				c[++p].num=a[i];
				c[p].i=i;
			}
			int l=1,r=p;
			while(l<r){
				
				int mid=(l+r)>>1;
				if(c[mid].num<a[i])
					l=mid+1;
				else
					r=mid;
			}
			
			if(c[l].num<a[i])
				bi[a[i]]=max(bi[a[i]],i);
			else
				bi[a[i]]=max(bi[a[i]],c[l].i);
		}
		
		for(int i=1;i<=k;i++){
			
			if(bi[i]==1e17||smal[i]==1e17)
				printf("0 ");//没出现这个数 
			else 
				printf("%lld ",(bi[i]-smal[i]+1)*2);//出现了这个数，输出答案 
		}
		
		p=0;
		for(int i=1;i<=n;i++)
			c[i]=(node){0,0};
			
		for(int i=1;i<=k;i++)
			smal[i]=bi[i]=0;
			
		printf("\n");
	}
}
```

---

## 作者：Cynops (赞：0)

好玩题。

由于矩阵对称，我们只需考虑一条边。

我们考虑颜色 $i$ 会延伸到哪里。显然的，满足 $a_p > i$ 离 $i$ 最远的左右端点 $L_i,R_i$ 可以作为正方形的边界。

但是我们还得对每个 $a_i$ 取一下下标的极值，用数学语言描述即：

$$\large L_i =\min_{a_p \ge i,p \in [1,n]} p,\large R_i =\max_{a_p \ge i,p \in [1,n]} p$$

我们求解 $L_i,R_i$ 可以做到 $\mathcal{O(n)}$，做法平凡。

至此，我们就用 $\mathcal{O(n+k)}$ 的算法解决了问题。

[代码](https://www.luogu.com.cn/paste/49xoqixl)，注意没有出现过的颜色要输出 $0$。

---

## 作者：Z_X_D_ (赞：0)

## 题意翻译
给你两个整数 $n$ 和 $k$。同时给你一个大小为 $n$ 的整数数组 $a_1, a_2, \ldots, a_n$。已知对于所有 $1 \leq i \leq n$，$1 \leq a_i \leq k$。

定义大小为 $n \times n$ 的二维数组 $b$ 如下：$b_{i, j} = \min(a_i, a_j)$。将数组 $b$ 表示为一个正方形。让一个单元格的颜色就是写在其中的数字（坐标为 $(i, j)$ 的单元格的颜色是 $b_{i, j}$）。

对于从 $1$ 到 $k$ 的每种颜色，找出数组 $b$ 中包含该颜色所有单元格的最小矩形。输出该矩形的宽和高之和。
## 思路
可以将问题看作颜色覆盖，先涂编号较大的颜色，再涂小编号颜色，每种颜色都会覆盖到其单元格的上下左右。

考虑对颜色编号从大到小排序，再进行一次扫描，后扫到的颜色一定能覆盖先扫到的，又因为需要用矩形覆盖所有同色格，需要记录目前位置扫到的最大位置和最小位置，再用它们分别更新当前颜色矩阵的上下左右边界。

另外，不难发现，能覆盖所有同色格的矩形一定是正方形，因此只需要记录矩形的左右边界就可以了。
## Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define inf 1000000000
#define otto auto
using namespace std;
int f[100010];
struct R
{
	int w,nb;
	bool operator <(const R &a)const
	{
		return w>a.w;
	}
}a[100010];
struct r
{
	int l,r;
}cl[100010];
signed main()
{
	int i,x,t,n,k,nwi,nwa;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&n,&k);
		for(i=1;i<=k;i++)
		{
			f[i]=0;
			cl[i].r=0;
			cl[i].l=inf;
		}
		for(i=1;i<=n;i++)
		{
			scanf("%d",&a[i].w);
			a[i].nb=i;
			f[a[i].w]++;
		}
		sort(a+1,a+n+1);
		nwi=inf;nwa=0;
		for(i=1;i<=n;i++)
		{
			nwi=min(nwi,a[i].nb);
			nwa=max(nwa,a[i].nb);
			x=a[i].w;
			cl[x].l=min(cl[x].l,nwi);
			cl[x].r=max(cl[x].r,nwa);
		}
		for(i=1;i<=k;i++)
		{
			if(f[i])
				printf("%d ",2*(cl[i].r-cl[i].l+1));
			else printf("0 ");
		}
		printf("\n");
	}
	return 0;
}

```

---

