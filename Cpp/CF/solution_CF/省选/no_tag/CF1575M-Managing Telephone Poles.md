# Managing Telephone Poles

## 题目描述

Mr. Chanek's city can be represented as a plane. He wants to build a housing complex in the city.

There are some telephone poles on the plane, which is represented by a grid $ a $ of size $ (n + 1) \times (m + 1) $ . There is a telephone pole at $ (x, y) $ if $ a_{x, y} = 1 $ .

For each point $ (x, y) $ , define $ S(x, y) $ as the square of the Euclidean distance between the nearest pole and $ (x, y) $ . Formally, the square of the Euclidean distance between two points $ (x_1, y_1) $ and $ (x_2, y_2) $ is $ (x_2 - x_1)^2 + (y_2 - y_1)^2 $ .

To optimize the building plan, the project supervisor asks you the sum of all $ S(x, y) $ for each $ 0 \leq x \leq n $ and $ 0 \leq y \leq m $ . Help him by finding the value of $ \sum_{x=0}^{n} {\sum_{y=0}^{m} {S(x, y)}} $ .

## 说明/提示

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1575M/42fc9241bd97024a0a9c88d5b53cdac34497ea2b.png)In the first example, the nearest telephone pole for the points $ (0,0) $ , $ (1,0) $ , $ (2,0) $ , $ (0,1) $ , $ (1,1) $ , and $ (2,1) $ is at $ (0, 0) $ . While the nearest telephone pole for the points $ (0, 2) $ , $ (1,2) $ , and $ (2,2) $ is at $ (0, 2) $ . Thus, $ \sum_{x=0}^{n} {\sum_{y=0}^{m} {S(x, y)}} = (0 + 1 + 4) + (1 + 2 + 5) + (0 + 1 + 4) = 18 $ .

## 样例 #1

### 输入

```
2 2
101
000
000```

### 输出

```
18```

## 样例 #2

### 输入

```
5 4
10010
00000
01000
00001
00100
00010```

### 输出

```
36```

# 题解

## 作者：meyi (赞：3)

~~看着斜率优化分四个方向讨论的代码陷入了沉思。~~

提供一种好写且高效的决策单调性 dp 解法。

先感性证一下决策单调性：如果有两个点 $(x_1,y_1),(x_1,y_2)\ (y_1<y_2)$ 且 离 $(x_1,y_1)$ 最近的点为 $(x_3,y_3)$，那么离 $(x_1,y_2)$ 最近的点 $(x_4,y_4)$ 一定满足 $y_3\le y_4$，否则 $(x_1,y_1)$ 选择 $(x_4,y_4)$ 会更优。


显然可以把答案拆成横纵坐标两种贡献分开考虑，令 $a_{i,j}$ 表示 $(i,j)$ 这个点与它在 $j$ 这列上最近的点的欧式距离的平方，那么则有转移 $f_{i,j}=\min\{a_{i,k}+(j-k)^2\}$，读者可以尝试自行证明这个式子的决策单调性。

时间复杂度 $O(nm\log m)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ri register int
typedef long long ll;
const int maxn=2010;
template<class T>inline bool ckmin(T &x,const T &y){return x>y?x=y,1:0;}
template<class T>inline bool ckmax(T &x,const T &y){return x<y?x=y,1:0;}
template<class T>inline void clear(T *arr,int siz,int val=0){memset(arr,val,sizeof(T)*(siz+1));}
ll a[maxn][maxn],f[maxn],ans;
int m,n;
char s[maxn][maxn];
void solve(int l,int r,int L,int R,int k){
	if(l>r||L>R)return;
	ri mid=l+r>>1,pos=0;
	ll tmp=1145141919810ll;
	for(ri i=L;i<=R;++i){
		ll val=a[k][i]+(mid-i)*(mid-i);
		if(val<tmp)pos=i,tmp=val;
	}
	f[mid]=tmp;
	solve(l,mid-1,L,pos,k);
	solve(mid+1,r,pos,R,k);
}
signed main(){
	scanf("%d%d",&n,&m);
	for(ri i=0;i<=n;++i){
		scanf("%s",s[i]);
		for(ri j=0;j<=m;++j)s[i][j]^=48;
	}
	memset(a,0x3f,sizeof a);
	for(ri i=0;i<=m;++i){
		ll lst=-114514;
		for(ri j=0;j<=n;++j){
			if(s[j][i])lst=j;
			ckmin(a[j][i],(lst-j)*(lst-j));
		}
		lst=114514;
		for(ri j=n;~j;--j){
			if(s[j][i])lst=j;
			ckmin(a[j][i],(lst-j)*(lst-j));
		}
	}
	for(ri i=0;i<=n;++i){
		memset(f,0x3f,sizeof f);
		solve(0,m,0,m,i);
		for(ri j=0;j<=m;++j)ans+=f[j];
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：绝顶我为峰 (赞：3)

首先跑一遍判掉距离最近的黑点和白点在同一行的情况。

扫描线扫描行，维护每行上方的所有黑点，下面的倒过来跑一遍是一样的。

对于每一列，我们只要维护最靠下的一个黑点，第 $j$  列最后一个黑点的行号记为 $lst_j$ 。

那么对于当前行上的每一个白点，上方最近的黑点的距离是 $\min_{k=1}^m(k-j)^2+(lst_k-i)^2$。

$(lst_k-i)^2$ 是个定值，于是式子简化为 $\min_{k=1}^mk^2-2jk+j^2+c$。

一看就很斜率优化，直接建出下凸壳转移就好了，然后倒着跑一遍转移下方的最小距离，是完全相同的。

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
using namespace std;
int n,m,id[3001][3001],cnt,pre[3001],q[6001],head,tail;
vector<int> dp,v[3001],qwq[3001];
bool mp[3001][3001];
long long ans;
inline double slope(int x,int y,int now)
{
    int x1=x,x2=y,c1=(pre[x]-now)*(pre[x]-now),c2=(pre[y]-now)*(pre[y]-now);
    return (x1*x1-x2*x2+c1-c2)*1.0/(x1-x2);
}
int main()
{
    scanf("%d%d",&n,&m);
    ++n,++m;
    dp.push_back(0);
    for(register int i=1;i<=n;++i)
        for(register int j=1;j<=m;++j)
        {
            char c=getchar();
            while(c!='0'&&c!='1')
                c=getchar();
            mp[i][j]=c^48;
            if(mp[i][j])
                v[i].push_back(j);
            else
            {
                qwq[i].push_back(j);
                id[i][j]=++cnt;
                dp.push_back(0x3f3f3f3f);
            }
        }
    for(register int i=1;i<=n;++i)
    {
        int lst=-1;
        for(register int j=1;j<=m;++j)
            if(mp[i][j])
                lst=j;
            else
                if(~lst)
                    dp[id[i][j]]=min(dp[id[i][j]],(j-lst)*(j-lst));
        lst=-1;
        for(register int j=m;j;--j)
            if(mp[i][j])
                lst=j;
            else
                if(~lst)
                    dp[id[i][j]]=min(dp[id[i][j]],(lst-j)*(lst-j));
    }
    for(register int i=1;i<=m;++i)
        pre[i]=-1;
    for(register int i=2;i<=n;++i)
    {
    	for(register int j=0;j<(int)(v[i-1].size());++j)
            pre[v[i-1][j]]=i-1;
        head=1;
        tail=0;
        for(register int j=1;j<=m;++j)
        {
            if(pre[j]==-1)
                continue;
            while(head<tail&&slope(q[tail-1],q[tail],i)>slope(q[tail],j,i))
                --tail;
            q[++tail]=j;
        }
        if(head>tail)
            continue;
        for(register int j=0;j<(int)(qwq[i].size());++j)
        {
            int k=qwq[i][j];
            while(head<tail&&slope(q[head],q[head+1],i)<(k<<1))
                ++head;
            dp[id[i][k]]=min(dp[id[i][k]],(q[head]-k)*(q[head]-k)+(pre[q[head]]-i)*(pre[q[head]]-i));
        }
    }
    for(register int i=1;i<=m;++i)
        pre[i]=-1;
    for(register int i=n-1;i;--i)
    {
    	for(register int j=0;j<(int)(v[i+1].size());++j)
            pre[v[i+1][j]]=i+1;
        head=1;
        tail=0;
        for(register int j=1;j<=m;++j)
        {
            if(pre[j]==-1)
                continue;
            while(head<tail&&slope(q[tail-1],q[tail],i)>slope(q[tail],j,i))
                --tail;
            q[++tail]=j;
        }
        if(head>tail)
            continue;
        for(register int j=0;j<(int)(qwq[i].size());++j)
        {
            int k=qwq[i][j];
            while(head<tail&&slope(q[head],q[head+1],i)<(k<<1))
                ++head;
            dp[id[i][k]]=min(dp[id[i][k]],(q[head]-k)*(q[head]-k)+(pre[q[head]]-i)*(pre[q[head]]-i));
        }
    }
    for(register int i=1;i<=cnt;++i)
        ans+=dp[i];
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：tribool4_in (赞：2)

首先欧氏距离的式子的形式非常像经典斜率优化形式。于是考虑对于某个点 $(x,y)$，其答案可以表示为 $\displaystyle\min_i\{(x-x_i)^2+(y-y_i)^2\}=x^2+y^2+\min_i\{x_i^2+y_i^2-2x_ix-2y_iy\}$。

这个式子跟 $x,y$ 均有关，没法直接斜率优化。于是考虑固定 $y$，点 $(x,y)$ 的答案即 $\displaystyle f_y(x)=x^2+y^2+\min_i\{(x_i^2+y_i^2-2y_iy)-2x_i\cdot x\}$。这就相当于所有 $(2x_i,x_i^2+y_i^2-2y_iy)$ 构成的下凸壳上，斜率为 $k=x$ 的直线切得的截距。

此时由于需要对于每个 $y$ 进行处理，且每次会处理 $O(n^2)$ 个关键点（假设 $n,m$ 同阶），复杂度为 $O(n^3)$ 仍无优化。

但是考虑当固定 $y_0$ 时，若两个点 $i,j$ 满足 $x_i=x_j,|y_i-y_0|<|y_j-y_0|$，则对于所有 $x$ 的点 $(x,y_0)$ 到点 $i$ 的距离一定小于点 $j$。因此只需要对于每个 $x$ 找出同行最近的点加入凸壳即可，这个过程可以 $O(n^2)$ 预处理。于是对于每个 $y$ 只会加入 $O(n)$ 个点，总复杂度 $O(n^2\log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e3 + 10;
int n, m;
int pre[N][N], nxt[N][N];
char s[N][N];
struct Point {
    int x, y;
    Point(int _x, int _y) : x(_x), y(_y) {}
    bool operator<(const Point &rhs) const { return x < rhs.x || (x == rhs.x && y < rhs.y); }
};
Point operator-(const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y); }
int operator*(const Point &a, const Point &b) { return a.x * b.y - a.y * b.x; }
vector<Point> l, h;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n >> m, ++n, ++m;
    for (int i = 1; i <= n; i++) cin >> (s[i] + 1);
    for (int i = 1; i <= n; i++) {
        for (int j = 1, k = 0; j <= m; j++) {
            if (s[i][j] == '1') k = j;
            pre[i][j] = k;
        }
        for (int j = m, k = 0; j >= 1; j--) {
            if (s[i][j] == '1') k = j;
            nxt[i][j] = k;
        }
    }
    long long ans = 0;
    for (int i = 1; i <= m; i++) {
        l.clear(), h.clear();
        for (int j = 1; j <= n; j++) {
            if (!pre[j][i] && !nxt[j][i]) continue;
            int xi = j, yi = 2 * m;
            if (pre[j][i]) yi = abs(pre[j][i] - i) < abs(yi - i) ? pre[j][i] : yi;
            if (nxt[j][i]) yi = abs(nxt[j][i] - i) < abs(yi - i) ? nxt[j][i] : yi;
            assert(yi != 2 * m);
            l.emplace_back(2 * xi, xi * xi + yi * yi - 2 * i * yi);
        }
        sort(l.begin(), l.end());
        int lh = 0;
        for (auto p : l) {
            while (lh > 1 && (p - h[lh - 2]) * (h[lh - 1] - h[lh - 2]) > 0) h.pop_back(), --lh;
            h.push_back(p), ++lh;
        }
        int pt = 0;
        for (int j = 1; j <= n; j++) {
            while (pt < lh - 1 && (h[pt + 1].y - h[pt].y) < j * (h[pt + 1].x - h[pt].x)) ++pt;
            ans += h[pt].y - 1ll * h[pt].x * j + 1ll * j * j + 1ll * i * i;
        }
    }
    cout << ans << '\n';
    return 0;
}
```

---

