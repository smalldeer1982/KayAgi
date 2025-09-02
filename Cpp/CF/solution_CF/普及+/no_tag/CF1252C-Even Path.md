# Even Path

## 题目描述

Pathfinding is a task of finding a route between two points. It often appears in many problems. For example, in a GPS navigation software where a driver can query for a suggested route, or in a robot motion planning where it should find a valid sequence of movements to do some tasks, or in a simple maze solver where it should find a valid path from one point to another point. This problem is related to solving a maze.

The maze considered in this problem is in the form of a matrix of integers $ A $ of $ N \times N $ . The value of each cell is generated from a given array $ R $ and $ C $ of $ N $ integers each. Specifically, the value on the $ i^{th} $ row and $ j^{th} $ column, cell $ (i,j) $ , is equal to $ R_i + C_j $ . Note that all indexes in this problem are from $ 1 $ to $ N $ .

A path in this maze is defined as a sequence of cells $ (r_1,c_1), (r_2,c_2), \dots, (r_k,c_k) $ such that $ |r_i - r_{i+1}| + |c_i - c_{i+1}| = 1 $ for all $ 1 \le i < k $ . In other words, each adjacent cell differs only by $ 1 $ row or only by $ 1 $ column. An even path in this maze is defined as a path in which all the cells in the path contain only even numbers.

Given a tuple $ \langle r_a,c_a,r_b,c_b \rangle $ as a query, your task is to determine whether there exists an even path from cell $ (r_a,c_a) $ to cell $ (r_b,c_b) $ . To simplify the problem, it is guaranteed that both cell $ (r_a,c_a) $ and cell $ (r_b,c_b) $ contain even numbers.

For example, let $ N = 5 $ , $ R = \{6, 2, 7, 8, 3\} $ , and $ C = \{3, 4, 8, 5, 1\} $ . The following figure depicts the matrix $ A $ of $ 5 \times 5 $ which is generated from the given array $ R $ and $ C $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1252C/bfefd5b3fc308f224043cfc77f140d207f38f3a0.png)Let us consider several queries:

- $ \langle 2, 2, 1, 3 \rangle $ : There is an even path from cell $ (2,2) $ to cell $ (1,3) $ , e.g., $ (2,2), (2,3), (1,3) $ . Of course, $ (2,2), (1,2), (1,3) $ is also a valid even path.
- $ \langle 4, 2, 4, 3 \rangle $ : There is an even path from cell $ (4,2) $ to cell $ (4,3) $ , namely $ (4,2), (4,3) $ .
- $ \langle 5, 1, 3, 4 \rangle $ : There is no even path from cell $ (5,1) $ to cell $ (3,4) $ . Observe that the only two neighboring cells of $ (5,1) $ are cell $ (5,2) $ and cell $ (4,1) $ , and both of them contain odd numbers (7 and 11, respectively), thus, there cannot be any even path originating from cell $ (5,1) $ .

## 说明/提示

Explanation for the sample input/output #1

This is the example from the problem description.

## 样例 #1

### 输入

```
5 3
6 2 7 8 3
3 4 8 5 1
2 2 1 3
4 2 4 3
5 1 3 4
```

### 输出

```
YES
YES
NO
```

## 样例 #2

### 输入

```
3 2
30 40 49
15 20 25
2 2 3 3
1 2 2 2
```

### 输出

```
NO
YES
```

# 题解

## 作者：Yawnsean (赞：7)

**提示 1：** 考虑某一次从 $(x,y)$ 到 $(x',y')$ 的操作是否合法应该如何判断。

**提示 2：** 接下来解决原问题。为了从原位置走到新位置，需要跨越一些行和列。

首先，我们考虑单次操作。可以认为一个走法是 “合法的” ，当且仅当其两端的数字奇偶性相同，因为题目实际也只要求了这一点。

因此，如果竖着走，由于两个格子在同一列，因此对应的 $c_i$ 相同，因此，由于其奇偶性相同，**对应的行的数字奇偶性也相同**。

同理，如果横着走，**对应的列的数字奇偶性也相同**。

而从起点 $(r_1,c_1)$ 走到终点 $(r_2,c_2)$ 存在 “偶数路径”，只需要起点是偶数，中间每个点都跟前一个点奇偶性相同即可。

而中间至少需要发生从第 $r_1$ 行到第 $r_2$ 行的连续移动，以及第 $c_1$ 列到第 $c_2$ 列的连续移动。因此，**这些行和列应当奇偶性相同**。

而我们只需要对一个连续的奇偶性相同的区间赋同一个值，就可以快速判断两行 / 列是否在同一个连续的奇偶性相同的区间内。

这件事只需要 $\mathcal{O}(n)$ 预处理，因此总复杂度为 $\mathcal{O}(n+q)$ 。

### 具体代码如下——

Python 做法如下——

```Python []
def main():
    n, q = MII()
    nums1 = LII()
    nums2 = LII()
    
    p1 = list(range(n))
    for i in range(1, n):
        if nums1[i] % 2 == nums1[i-1] % 2:
            p1[i] = p1[i-1]
    
    p2 = list(range(n))
    for i in range(1, n):
        if nums2[i] % 2 == nums2[i-1] % 2:
            p2[i] = p2[i-1]
    
    outs = []
    for _ in range(q):
        x1, y1, x2, y2 = GMI()
        outs.append('YES' if p1[x1] == p1[x2] and p2[y1] == p2[y2] else 'NO')
    
    print('\n'.join(outs))
```

C++ 做法如下——

```cpp []
signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, q;
    cin >> n >> q;

    vector<int> nums1(n), nums2(n);
    for (auto &v: nums1) cin >> v;
    for (auto &v: nums2) cin >> v;

    vector<int> p1(n), p2(n);
    for (int i = 1; i < n; i ++) {
        p1[i] = (nums1[i] % 2 == nums1[i-1] % 2 ? p1[i-1] : i);
        p2[i] = (nums2[i] % 2 == nums2[i-1] % 2 ? p2[i-1] : i);
    }

    while (q --) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        x1 -- , y1 -- , x2 -- , y2 --;
        cout << (p1[x1] == p1[x2] && p2[y1] == p2[y2] ? "YES\n" : "NO\n");
    }

    return 0;
}
```

---

## 作者：Peter20122012 (赞：0)

## [洛谷传送门](https://www.luogu.com.cn/problem/CF1252C) [CF 传送门](https://codeforces.com/problemset/problem/1252/C)

## 思路
发现这道题的数据范围是 $N \le 10^{5}$，不可能构造原矩阵，所以只能在给出的两个数组上寻找规律。

因为每一步是向上下左右任意一个方向移动一步，也就相当于在给出的一个数组往前或往后一位。如果我们记变动前两数为 $x, y$，变动后 $y$ 变为 $z$，那么要求 $x + y \equiv x + z \pmod{2}$，所以 $y \equiv z \pmod{2}$。发现我们只能走到奇偶性相同的位，所以我们可以将**连续的**一段同奇偶性的数变成同一个数，然后每次询问时判断这一段的数是否相同，两个数组都相同则输出 `YES`，否则输出 `NO`。

## AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;

#define MAX(x, y) (((x) >= (y)) ?(x) :(y))
#define MIN(x, y) (((x) <= (y)) ?(x) :(y))
#define FOR(st, ed, i) for (int i = (st); i <= (ed); ++i)
#define RFOR(st, ed, i) for (int i = (ed); i >= (st); --i)
#define fir first
#define sec second

// #define debug

typedef long long ll;
typedef double db;
typedef pair<int, int> pii;

const int maxn = 1e5 + 10;

int n, q;
int r[maxn];
int c[maxn];
	int ar, ac, br, bc;

void init (int *a) {
	int cnt = 0;
	
	cnt = !(a[1]%2);
	a[0] = cnt;
	FOR (1, n, i) {
		cnt += ((a[i]%2 == a[i - 1]%2) ?(0) :(1));
		a[i] = cnt;
	}
}

void work_q () {
	scanf("%i%i%i%i", &ar, &ac, &br, &bc);

	if (r[ar] == r[br] && c[ac] == c[bc]) {printf("YES\n");}
	else {printf("NO\n");}
}
int main () {
	scanf("%i%i", &n, &q);
	FOR (1, n, i) {scanf("%i", &r[i]);}
	FOR (1, n, i) {scanf("%i", &c[i]);}

	init(r);
	init(c);

	while (q--) {work_q();}
	return 0;
}
```

---

## 作者：OIerZhao_1025 (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF1252C)

## 思路
给定一个大小为 $N\times N$ 的整数矩阵。\
你的任务是确定是否存在从单元格 $(r_a,c_a)$ 到单元格 $(r_b,c_b)$ 的偶数路径。为简化问题，保证单元格 $(r_a,c_a)$ 和单元格 $(r_b,c_b)$ 均为偶数。

这道题数据有点大，题目告诉我们一定要路径上全是偶数，而且保证出发点和结束点都是欧束，所以一旦路径上的某一个数的就行与别的不一样就肯定不行，所以一开始就要把每一个数都模二，这样数据就小了很多。注意一下这里需要预处理因为有多条路径。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n,q,r[N],c[N],a[N],b[N],x_1,x_2,y_1,y_2;
int main()
{
    cin>>n>>q;
    for(int i=1;i<=n;i++) 
		cin>>r[i],r[i]%=2;
    for(int i=1;i<=n;i++)
		cin>>c[i],c[i]%=2;
    for(int i=2;i<=n;i++)
	{
        a[i]=(r[i]==r[i-1]?a[i-1]:i);
        b[i]=(c[i]==c[i-1]?b[i-1]:i);
    }
    while(q--)
	{
        cin>>x_1>>y_1>>x_2>>y_2;
        if(a[x_1]==a[x_2]&&b[y_1]==b[y_2])cout<<"YES\n";
        else cout<<"NO\n";
    }
    return 0;
}
```

---

## 作者：CountState (赞：0)

考虑到只要行进过程中奇偶性发生变化就一定不可能完成。

如果 $c_{x1}$ 到 $c_{x2}$ 这段区间内的奇偶性不完全相同，那么在行进过程中奇偶性一定会发生变化，从而不能完成，对于 $r$ 亦是同理。

所以 $c_{x1},c_{x1+1}\cdots c_{x2}$ 的奇偶性要相同，$r_{y1},r_{y1+1}\cdots r_{y2}$ 的奇偶性要相同。

考虑 $O(n)$ 预处理，如果 $c_i=c_{i-1}$，那么 $a_i=a_{i-1}$，否则 $a_i=i$；如果 $r_i=r_{i-1}$，那么 $b_i=b_{i-1}$，否则 $b_i=i$。

最后当且仅当 $a_{x1}=a_{x2}$ 并且 $b_{y1}=b_{y2}$ 时方案可行。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int n,m,c[N],r[N],a[N],b[N];
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>c[i];
	for(int i=1;i<=n;i++) cin>>r[i];
	for(int i=1;i<=n;i++){
		if(c[i]%2==c[i-1]%2) a[i]=a[i-1];
		else a[i]=i;
		if(r[i]%2==r[i-1]%2) b[i]=b[i-1];
		else b[i]=i;
	}
	while(m--){
		int sx,sy,dx,dy;
		cin>>sx>>sy>>dx>>dy;
		if(a[sx]==a[dx]&&b[sy]==b[dy]) puts("YES");
		else puts("NO");
	}
}

```

---

## 作者：ivyjiao (赞：0)

来源：CF 决斗场。

输了，来水一篇题解。

题意不再复述。

考虑到当往左或往右走一步时，$y=y'$，所以 $r_x$ 和 $r_{x'}$ 的奇偶性要相同。

考虑到当往上或往下走一步时，$x=x'$，所以 $c_y$ 和 $c_{y'}$ 的奇偶性要相同。

综上我们得到，$r_{x1},r_{x1+1}\cdots r_{x2}$ 的奇偶性要相同；$c_{y1},c_{y1+1}\cdots c_{y2}$ 的奇偶性要相同。

考虑 $O(n)$ 预处理奇偶性的信息。我们先把每个 $r_i=r_i\bmod 2,c_i=c_i\bmod 2$，因为我们只关注奇偶性不关注其真实数值。然后对于每个 $i$，当 $r_i=r_{i-1}$ 时，$a_i=a_{i-1}$，否则 $a_i=i$；当 $c_i=c_{i-1}$ 时，$b_i=b_{i-1}$，否则 $b_i=i$。判断能否走通的条件就是 $a_{x1}=a_{x2}$ 且 $b_{y1}=b_{y2}$。

然后就过了，不需要数据结构来维护。

代码：

```cpp
#include<bits/stdc++.h>
#define y1 IAKIOI
using namespace std;
const int N=1e5+1;
int n,q,r[N],c[N],a[N],b[N],x1,x2,y1,y2;
int main(){
    cin>>n>>q;
    for(int i=1;i<=n;i++) cin>>r[i],r[i]%=2;
    for(int i=1;i<=n;i++) cin>>c[i],c[i]%=2;
    for(int i=2;i<=n;i++){
        a[i]=(r[i]==r[i-1]? a[i-1]:i);
        b[i]=(c[i]==c[i-1]? b[i-1]:i);
    }
    while(q--){
        cin>>x1>>y1>>x2>>y2;
        if(a[x1]==a[x2]&&b[y1]==b[y2]) cout<<"YES\n";
        else cout<<"NO\n";
    }
}
```

---

## 作者：OIerZhang (赞：0)

# [CF1252C Even Path](https://www.luogu.com.cn/problem/CF1252C)

## 思路

这道题的 $n$ 有 $10^5$ 那么大，$O(n^2)$ 的算法都无法通过，我们可以从网格的构建和合法路径的定义入手解决此题。

设网格是 $g$，则 $g_{i, j} = r_i + c_j$。众所周知，奇偶性相同的数加起来为偶数，所以该格为偶数时，它所在行和列奇偶性相同。那么问题就转换成了：找一条路径，使路径上的格子奇偶性相同。也就是 $r_1$ 到 $r_2$ 的奇偶性相同，$c_1$ 到 $c_2$ 的奇偶性相同。

这样就可以进行预处理，设 $a_1 = 1$，当 $r_i$ 和 $r_{i - 1}$ 奇偶性相同时，$a_i$ 设为 $a_{i - 1}$，反之则将 $a_i$ 设为 $a_{i - 1}$ 的取反。$c$ 数组同理。再将两个数组进行前缀和。

判断时，只需判断 $a_{r_1}$ 到 $a_{r_2}$ 的和是否为 $r_2 - r_1 + 1$ 或 $0$ 以及 $b_{c_1}$ 到 $b_{c_2}$ 的和是否为 $c_2 - c_1 + 1$ 或 $0$。

## 核心代码

```cpp
mr[1] = true;
mc[1] = true;
for (int i = 2; i <= n; i++)
{
    if (r[i] % 2 == r[i - 1] % 2)
        mr[i] = mr[i - 1];
    else
        mr[i] = !mr[i - 1];
    if (c[i] % 2 == c[i - 1] % 2)
        mc[i] = mc[i - 1];
    else
        mc[i] = !mc[i - 1];
}
for (int i = 1; i <= n; i++)
    sr[i] = sr[i - 1] + mr[i];
for (int i = 1; i <= n; i++)
    sc[i] = sc[i - 1] + mc[i];
while (q--)
{
    int r1, c1, r2, c2;
    cin >> r1 >> c1 >> r2 >> c2;
    if (r1 > r2) swap(r1, r2);
    if (c1 > c2) swap(c1, c2);
    if ((sr[r2] - sr[r1 - 1] == r2 - r1 + 1 || sr[r2] - sr[r1 - 1] == 0) && (sc[c2] - sc[c1 - 1] == c2 - c1 + 1 || sc[c2] - sc[c1 - 1] == 0))
        cout << "YES\n";
    else
        cout << "NO\n";
}
```

---

## 作者：Echo_Long (赞：0)

### [Even Path](https://www.luogu.com.cn/problem/CF1252C)

练习 st 表的好题。

因为我们起点的 $R$ 和 $C$ 数组奇偶性相同，那么我们一次移动一步，奇偶性显然不能改变。

从 $(lx,ly)$ 走到 $(rx,ry)$ 的路径上，每一个区间内的 $R$ 数组和 $C$ 数组都会被至少取得一次，那么组合起来就必定是要让区间内的 $R$ 数组和 $C$ 数组奇偶性相同。

那么开四个 st 表分别维护第一个数组的区间奇偶性，第二个数组的区间奇偶性即可。

事实上本题可以舍弃 st 表直接用前缀和来实现，有兴趣的读者可以自行尝试。

```c++
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define inl inline
#define getchar() cin.get()
#define int long long
const int N = 2e5 + 5;

int read()
{
	int f = 1 , x = 0;
	char ch = getchar();
	while ( !isdigit(ch) ) { if ( ch == '-' ) f = -1; ch = getchar(); }
	while ( isdigit(ch) ) { x = ( x << 1 ) + ( x << 3 ) + ( ch ^ 48 ); ch = getchar(); }
	return x * f;
}

int n , q , a[N] , b[N];

struct ST
{
    int st[N][26];
    void init ( int sum[] , int op )//j1o2
    {
        if ( op == 1 ) { for ( int i = 1 ; i <= n ; i ++ ) if ( sum[i] % 2 ) st[i][0] = 1; }
        else { for ( int i = 1 ; i <= n ; i ++ ) if ( ! ( sum[i] % 2 ) ) st[i][0] = 1; }
        for ( int j = 1 ; j <= __lg(n) ; j ++ )
            for ( int i = 1 ; i + ( 1 << j ) - 1 <= n ; i ++ )
                st[i][j] = min ( st[i][j-1] , st[i+(1<<j-1)][j-1] );
    }
    int query ( int l , int r )
    {
        if ( l > r ) swap ( l , r );
        int len = __lg(r-l+1);
        return min ( st[l][len] , st[r-(1<<len)+1][len] );
    }
}st1o,st2o,st1j,st2j;

signed main ()
{
	ios::sync_with_stdio(false);
	cin.tie(0) , cout.tie(0);
    n = read() , q = read();
    for ( int i = 1 ; i <= n ; i ++ ) a[i] = read();
    for ( int i = 1 ; i <= n ; i ++ ) b[i] = read();
    st1j.init(a,1) , st1o.init(a,2) , st2j.init(b,1) , st2o.init(b,2);
    for ( int i = 1 ; i <= q ; i ++ )
    {
        int lx = read() , ly = read() , rx = read() , ry = read();
        if ( ( st1j.query ( lx , rx ) && st2j.query ( ly , ry ) ) || ( st1o.query ( lx , rx ) && st2o.query ( ly , ry ) ) ) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}   
```



---

## 作者：fchwpo (赞：0)

考虑找规律，起始点横纵坐标必然都是偶数或者都是奇数，因为它一次只能改变横坐标或纵坐标，所以可以发现你从起点到终点的每一个 $r_i$ 和 $c_i$ 的奇偶性是不变的，又因为每一行和每一列都会经过，所以可以发现起点到终点的矩形内坐标奇偶性全部相同，用线段树维护下区间有没有奇数或者偶数就可以了。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ls (k<<1)
#define rs (k<<1|1)
#define mid (l+r>>1)
using namespace std;
int n,q;
const int maxn=1e5+5;
int c[maxn];
int d[maxn];
int maxx[maxn*16][5];
void build3(int k,int l,int r){
	if(l==r){
		if(c[l]&1) maxx[k][3]=1;
		return;
	}
	build3(ls,l,mid);
	build3(rs,mid+1,r);
	maxx[k][3]=max(maxx[ls][3],maxx[rs][3]);
}
void build4(int k,int l,int r){
	if(l==r){
		if(!(c[l]&1)) maxx[k][4]=1;
		return; 
	}
	build4(ls,l,mid);
	build4(rs,mid+1,r);
	maxx[k][4]=max(maxx[ls][4],maxx[rs][4]);
}
void build1(int k,int l,int r){
	if(l==r){
		if(d[l]&1) maxx[k][1]=1;
		return;
	}
	build1(ls,l,mid);
	build1(rs,mid+1,r);
	maxx[k][1]=max(maxx[ls][1],maxx[rs][1]);
}
void build2(int k,int l,int r){
	if(l==r){
		if(!(d[l]&1)) maxx[k][2]=1;
		return; 
	}
	build2(ls,l,mid);
	build2(rs,mid+1,r);
	maxx[k][2]=max(maxx[ls][2],maxx[rs][2]);
}
int query(int k,int l,int r,int x,int y,int val){
	int res=0;
	if(x<=l&&r<=y){
		return maxx[k][val];
	}
	if(x<=mid){
		res=max(res,query(ls,l,mid,x,y,val));
	}
	if(y>mid){
		res=max(res,query(rs,mid+1,r,x,y,val));
	}
	return res;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>d[i];
	for(int i=1;i<=n;i++) cin>>c[i];
	build1(1,1,n);
	build2(1,1,n);
	build3(1,1,n);
	build4(1,1,n);
	while(q--){
		int stx,sty,edx,edy;
		cin>>stx>>sty>>edx>>edy;
		if(stx>edx) swap(stx,edx);
		if(sty>edy) swap(sty,edy);
		if((d[stx]+c[sty])%2!=0||(d[edx]+c[sty])%2!=0){
			cout<<"NO"<<'\n';
			continue;
		}
		if(d[stx]&1){
			if(query(1,1,n,stx,edx,2)+query(1,1,n,sty,edy,4)==0) cout<<"YES"<<'\n';
			else cout<<"NO"<<'\n';
		}
		else{
			if(query(1,1,n,stx,edx,1)+query(1,1,n,sty,edy,3)==0) cout<<"YES"<<'\n';
			else cout<<"NO"<<'\n';
		}
	}
	return 0;
}

```

---

