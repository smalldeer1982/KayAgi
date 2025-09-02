# [ARC149D] Simultaneous Sugoroku

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc149/tasks/arc149_d

$ N $ 個のコマが数直線上の整数座標に置かれています．$ i $ 番目のコマは座標 $ X_i $ に置かれています．

これらのコマを，次のように $ M $ 回移動させます．

- $ i $ 回目の操作では，正整数 $ D_i $ が与えられ，各コマを次のように移動させる．
  - 座標が負の整数であるようなコマは，正の方向に距離 $ D_i $ 進んだ位置に移動させる．
  - 座標が $ 0 $ であるようなコマは動かさない．
  - 座標が正の整数であるようなコマは，負の方向に距離 $ D_i $ 進んだ位置に移動させる．

各コマが原点に到達するか否かを判定してください．原点に到達する場合には，はじめて原点に到達するのが何回目の移動によるものかを出力してください．原点に到達しない場合には，$ M $ 回の移動がすべて終了したときの座標を出力してください．

## 说明/提示

### 制約

- $ 1\leq\ N\leq\ 3\times\ 10^5 $
- $ 1\leq\ M\leq\ 3\times\ 10^5 $
- $ 1\leq\ X_1\ <\ \cdots\ <\ X_N\ \leq\ 10^6 $
- $ 1\leq\ D_i\ \leq\ 10^6 $

### Sample Explanation 1

各コマの座標は次のように変化します． - $ 1 $ 番目のコマ：$ \phantom{0}2\quad\ \longmapsto\ \quad\ -6\quad\ \longmapsto\ \quad\ -4\quad\ \longmapsto\ \quad\ \phantom{-}1\ \quad\ \longmapsto\ \quad\ -6 $. - $ 2 $ 番目のコマ：$ \phantom{0}4\ \quad\ \longmapsto\ \quad\ -4\quad\ \longmapsto\ \quad\ -2\ \quad\ \longmapsto\ \quad\ \phantom{-}3\ \quad\ \longmapsto\ \quad\ -4 $. - $ 3 $ 番目のコマ：$ \phantom{0}6\ \quad\ \longmapsto\ \quad\ -2\quad\ \longmapsto\ \quad\ \phantom{-}0\ \quad\ \longmapsto\ \quad\ \phantom{-}0\ \quad\ \longmapsto\ \quad\ \phantom{-}0 $. - $ 4 $ 番目のコマ：$ \phantom{0}8\ \quad\ \longmapsto\ \quad\ \phantom{-}0\quad\ \longmapsto\ \quad\ \phantom{-}0\ \quad\ \longmapsto\ \quad\ \phantom{-}0\ \quad\ \longmapsto\ \quad\ \phantom{-}0 $. - $ 5 $ 番目のコマ：$ 10\ \quad\ \longmapsto\ \quad\ \phantom{-}2\quad\ \longmapsto\ \quad\ \phantom{-}0\ \quad\ \longmapsto\ \quad\ \phantom{-}0\ \quad\ \longmapsto\ \quad\ \phantom{-}0 $. - $ 6 $ 番目のコマ：$ 12\ \quad\ \longmapsto\ \quad\ \phantom{-}4\quad\ \longmapsto\ \quad\ \phantom{-}2\ \quad\ \longmapsto\ \quad\ -3\ \quad\ \longmapsto\ \quad\ \phantom{-}4 $.

## 样例 #1

### 输入

```
6 4
2 4 6 8 10 12
8 2 5 7```

### 输出

```
No -6
No -4
Yes 2
Yes 1
Yes 2
No 4```

# 题解

## 作者：Leasier (赞：8)

看上去不太能数据结构维护，怎么办呢？

注意到值域是比较小的，考虑对值域内的所有数预处理对应的答案。

注意到一个看上去没啥 p 用的性质：

- 如果 $x, y$ 在某时刻的位置互为相反数，则它们此后的位置必定一直为相反数。

证明：此后操作显然一直对称。

人类智慧地，考虑利用这个性质：

- 我们每次只维护一段符号相同的区间 $[l, r]$ 的情况。
- 若在执行当前操作后符号不完全相同了，则利用上面的对称性将符号不同的两边中元素数量较少的一边扔了——反正后面可以通过对称性得出（实现时可以建边处理）；并对恰好可以取到 $0$ 的位置打上标记。
- 最后 dfs 一遍推出被扔掉的点的信息。

时间复杂度为 $O(n + m + N)$，其中 $N$ 为值域 $10^6$。

代码：
```cpp
#include <stdio.h>

typedef long long ll;

typedef struct {
	int nxt;
	int end;
} Edge;

const int N = 3e5 + 7, M = 1e6;
int cnt = 0;
int x[N], stop[M + 7], head[M + 7], pos[M + 7];
bool vis[M + 7];
Edge edge[M + 7];

inline void add_edge(int start, int end){
	cnt++;
	edge[cnt].nxt = head[start];
	head[start] = cnt;
	edge[cnt].end = end;
}

void dfs(int u){
	if (vis[u]) return;
	vis[u] = true;
	for (register int i = head[u]; i != 0; i = edge[i].nxt){
		int x = edge[i].end;
		if (stop[u] != 0){
			stop[x] = stop[u];
		} else {
			pos[x] = -pos[u];
		}
		dfs(x);
	}
}

int main(){
	int n, m, l = 1, tag = 0, r = M;
	scanf("%d %d", &n, &m);
	for (register int i = 1; i <= n; i++){
		scanf("%d", &x[i]);
	}
	for (register int i = 1; i <= m; i++){
		int d, mid;
		scanf("%d", &d);
		if (l + tag > 0){
			tag -= d;
		} else {
			tag += d;
		}
		mid = -tag;
		if (l <= mid && mid <= r){
			stop[mid] = i;
			if (mid - l < r - mid){
				for (register int j = l; j < mid; j++){
					add_edge(mid * 2 - j, j);
				}
				l = mid + 1;
			} else {
				for (register int j = r; j > mid; j--){
					add_edge(mid * 2 - j, j);
				}
				r = mid - 1;
			}
		}
	}
	for (register int i = l; i <= r; i++){
		if (stop[i] == 0) pos[i] = i + tag;
		dfs(i);
	}
	for (register int i = 1; i < l; i++){
		if (stop[i] != 0) dfs(i);
	}
	for (register int i = M; i > r; i--){
		if (stop[i] != 0) dfs(i);
	}
	for (register int i = 1; i <= n; i++){
		if (stop[x[i]] != 0){
			printf("Yes %d\n", stop[x[i]]);
		} else {
			printf("No %d\n", pos[x[i]]);
		}
	}
	return 0;
}
```

---

## 作者：Phartial (赞：7)

好题。

首先可以发现值域很小，所以我们可以直接算 $[1,10^6]$ 的每个数的对应结果。

如果原点在所有数的左边，那么操作相当于把所有数向左平移 $d$ 个单位，在右边同理。

对于平移操作可以考虑直接移动原点，算一个小 trick。

考虑平移完的图形（假设右半边比左半边要长）：

![](https://cdn.luogu.com.cn/upload/image_hosting/un635fph.png)

首先原点对应的那个点直接清零即可。

可以发现在后面的操作中，绿色部分和黄色部分是对称的，所以我们可以把绿色部分砍掉，只用计算黄色部分。

左半边比右半边长同理。

直接对每次询问给绿色部分暴力打上标记就可以了，后续的查询可以记忆化，时间复杂度 $O(N+M+V)$。

细节还是挺多的，可以参考一下我的代码。

```cpp
#include <iostream>

using namespace std;
using Pii = pair<int, int>;

const int kN = 3e5 + 1, kV = 1e6;

int n, m, x[kN], z;  // z 为原点位置
Pii p[kV + 1];       // 每个点的标记，first 存映射到那个点（-1 表示清零），second 存映射时间戳
Pii f[kV + 1];       // 用于记忆化
bool w;              // 原点在区间左边还是右边（0 为左边，1 为右边）

Pii G(int x) {
  if (f[x].second) {  // 记忆化
    return f[x];
  }
  if (p[x].first == -1) {            // 如果此点为 0
    return f[x] = {0, p[x].second};  // 直接返回 0 和时间戳
  }
  if (!p[x].first) {           // 如果此点没有映射
    return f[x] = {x - z, m};  // 返回按原点偏移的坐标和时间戳
  }
  Pii v = G(p[x].first);                                 // 如果有映射，直接计算对应映射
  return f[x] = {-v.first, max(p[x].second, v.second)};  // 坐标取反，时间戳取 max
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n >> m;
  for (int i = 1; i <= n; ++i) {
    cin >> x[i];
  }
  for (int d, i = 1, l = 1, r = kV; i <= m; ++i) {  // 处理每次操作，[l,r] 为当前区间
    cin >> d;
    z += d * (w ? -1 : 1);  // 偏移原点
    if (z < l) {            // 如果超出范围
      w = 0;                // 直接改位置后退出
    } else if (z > r) {     // 同上
      w = 1;
    } else {
      p[z] = {-1, i};       // 原点清零
      if (z - l > r - z) {  // 如果左区间大于右区间，就把右区间映射到左区间上
        for (int j = z + 1; j <= r; ++j) {
          p[j] = {z - (j - z), i};  // 映射
        }
        w = 1, r = z - 1;  // 缩小区间
      } else {             // 同上
        for (int j = l; j < z; ++j) {
          p[j] = {z + (z - j), i};
        }
        w = 0, l = z + 1;
      }
    }
  }
  for (int i = 1; i <= n; ++i) {
    Pii y = G(x[i]);                       // 计算当前点坐标
    if (y.first) {                         // 如果非 0
      cout << "No " << y.first << '\n';    // 输出坐标
    } else {                               // 如果为 0
      cout << "Yes " << y.second << '\n';  // 输出时间戳
    }
  }
  return 0;
}
```


---

## 作者：critnos (赞：4)

考虑直接维护分段函数，

一段长度为 $len$ 的操作序列会得到大小为 $O(2^{len})$ 的分段函数。

把操作序列按 $B=\Theta(\log n)$ 分块，

并且基数排序就可以得到 $O(\dfrac {n^2} {\log n})$ 的复杂度。

实际上要加一些非常平凡的优化才能过。

这个优化其实是什么呢？

就是说把重复的数去掉，并查集维护。

然后我肯定不是直接分块，

就是我从左往右扫，

扫到运算次数超过一个阈值，$\Theta(n)$ 左右，

然后停下来把这个作为右端点，即可。

https://atcoder.jp/contests/arc149/submissions/44412162

---

## 作者：whx2009 (赞：3)

## 本题思路：
这道题直接上数据结构即可，我们看到操作是把值域比零大的减去当前的位移距离，值域比零小的加上，然后如果当前位置的数到零了就停止。

这明显可以用平衡树合并去做啊，我们每一次分裂出大于零的和小于零的，分别对这两棵树打上更改标记，然后平衡树合并，把新树中和零相等的分裂出来，打上标记即可，没有什么难度。
## 本题代码：
```cpp
#include<bits/stdc++.h>
#define int long long
#define ls tr[p].ch[0]
#define rs tr[p].ch[1]
using namespace std;
int a[300005];
struct f{int rnd,mi,ch[2],id,sum,add;}tr[300005];
void chuan(int p){
	tr[ls].add+=tr[p].add,tr[rs].add+=tr[p].add;
	tr[ls].sum+=tr[p].add;tr[rs].sum+=tr[p].add;
	tr[ls].mi+=tr[p].add,tr[rs].mi+=tr[p].add;tr[p].add=0;
}
void wei(int p){
	tr[p].mi=min(tr[p].sum,min(tr[ls].mi,tr[rs].mi));
}
void split(int p,int &x,int &y,int k){
	if(!p){x=y=0;return;}
	if(tr[p].add) chuan(p);
	if(tr[p].sum<=k){x=p;split(rs,rs,y,k),wei(x);}
	else y=p,split(ls,x,ls,k),wei(y);
}
void merge(int &p,int x,int y){
	if(!x||!y){p=x+y;return;}
	if(tr[x].add) chuan(x);if(tr[y].add) chuan(y);
	if(tr[x].rnd<=tr[y].rnd) p=x,merge(rs,rs,y);
	else p=y,merge(ls,x,ls);
	wei(p);
}
void merg(int &root,int x,int y){
	root=0;
	while(x&&y){
		if(tr[x].mi<tr[y].mi){
			int l;split(x,l,x,tr[y].mi);
			merge(root,root,l);
		}
		else{
			int l;split(y,l,y,tr[x].mi);
			merge(root,root,l);
		}
	}
	merge(root,root,x),merge(root,root,y);
}
int cnt;
int add(int id,int sum){
	tr[++cnt].id=id,
	tr[cnt].sum=tr[cnt].mi=sum;
	tr[cnt].rnd=rand();
	return cnt;
}
int pd[300005],ans[300005];
void dfs(int p,int id,int pdd){
	if(!p)return;
	pd[tr[p].id]=pdd;
	if(pdd==0) ans[tr[p].id]=id;
	else ans[tr[p].id]=tr[p].sum;
	if(tr[p].add) chuan(p);
	dfs(ls,id,pdd),dfs(rs,id,pdd);
}
signed main(){int root=0;
	tr[0].mi=1e18;int n,m;cin>>n>>m;
	for(int i=1;i<=n;i++){
		int x;cin>>x;
		int l,r;split(root,l,r,x);merge(l,l,add(i,x));merge(root,l,r);
	}
	for(int i=1;i<=m;i++){
		int x;cin>>x;
		int l,r;split(root,l,r,0);
		if(l)tr[l].add+=x,tr[l].mi+=x,tr[l].sum+=x;
		if(r) tr[r].add-=x,tr[r].mi-=x,tr[r].sum-=x;
		merg(root,l,r);int lss;
//		dfs1(root);
		split(root,l,r,0);
		split(l,l,lss,-1);
		dfs(lss,i,0);merge(root,l,r);
	}
	dfs(root,0,1);
	for(int i=1;i<=n;i++){
		if(pd[i]==0){
			cout<<"Yes"<<" "<<ans[i]<<'\n';
		}
		else cout<<"No "<<ans[i]<<'\n';
	}
	return 0;
}
```

---

## 作者：hh弟中弟 (赞：2)

类似于 [TEST_100](https://www.luogu.com.cn/problem/P8264) 的思想，预处理出 $[l,r]$ 的答案，时刻维护一个原点 $k$ 与这个区间的**相对关系**，设给出的数为 $x$，有如下情况：
- 原点在区间的右边，那么整个区间要左移，相当于原点右移，$k\gets k+x$。
- 原点在区间的左边，相当于区间翻转后右移了 $x$，相当于原点左移，$k\gets k-x$。

处理完之后，如果区间跨越了原点，就将短的一侧翻折过来即可，因为之后他们的答案互为相反数，这个可以用带权并查集实现。最后，距离原点的距离就是经过这个块后的答案，时间复杂度 $\mathcal{O}(V)$。\
额，貌似审核认为复杂度分析错了，这里确实没有详细说，因为只有在最后才使用并查集，所以每个点只会往上找一次，所以复杂度是线性的，并不会带上并查集常数。
```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
#define pii std::pair<int,int>
#define eb emplace_back
#define pb push_back
typedef long long ll;
typedef unsigned long long ull;
std::mt19937_64 myrand(std::chrono::high_resolution_clock::now().time_since_epoch().count());
inline int R(int n){return myrand()%n+1;}
inline int read(){char ch=getchar();int x=0,f=1;for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')f=-1;for(;ch>='0'&&ch<='9';ch=getchar())x=(x<<3)+(x<<1)+(ch^48);return x*f;}
inline void Min(int &x,int y){if(x>y)x=y;}
inline void Max(int &x,int y){if(x<y)x=y;}
const int N=1e6+10,V=1e6+10;
int n,m,fa[V],a[N],ans[V];
bool v[V];
inline int find(int x){if(fa[x]==x)return x;int d=fa[x];fa[x]=find(fa[x]);return v[x]^=v[d],fa[x];}
signed main(){
    // freopen("in.in","r",stdin);freopen("out.out","w",stdout);
    std::ios::sync_with_stdio(false);std::cin.tie(0);std::cout.tie(0);
    n=read(),m=read();for(int i=1;i<=n;++i)a[i]=read();
    for(int i=a[1];i<=a[n];++i)fa[i]=i;int o=0;
    for(int i=1,l=a[1],r=a[n];i<=m;++i){
    	int x=read();
    	if(o<l)o+=x;else o-=x;
    	if(l<=o&&r>=o){
    		ans[o]=i;
    		if(o-l<r-o){for(int i=l;i<o;++i)fa[i]=2*o-i,v[i]^=1;l=o+1;}
    		else{for(int i=r;i>o;--i)fa[i]=2*o-i,v[i]^=1;r=o-1;}
    	}
    }
    for(int i=1;i<=n;++i){
    	int x=find(a[i]);
    	if(ans[x])std::cout<<"Yes "<<ans[x]<<'\n';
    	else std::cout<<"No "<<(v[a[i]]?o-x:x-o)<<'\n';
    }
}
```

---

## 作者：123456xwd (赞：2)

题解区唯一的并查集做法超级长，遂写一篇题解。

思路很巧妙，首先，很明显，数轴上关于远点对称的一个点对，不论移动了多少次，都任然是对称的。

再看眼数据范围，发现其实点分布的比较紧，考虑直接将所有点看做一个整体（数轴上一个线段），然后依次移动。

关键的是，若这个整体横跨了原点的话，那么在原点的点就有答案了，对于剩下的部分，设在正半轴、负半轴的部分长度为 $len1,len2$，若 $len1>len2$，则将负半轴的部分对称到正半轴，他之后的位置相当于对称后的位置的相反数。

反之同理。

而这个不断对称的过程，我们可以用并查集解决，每个节点就表示初始所在的位置。由于要判断相反数，所以用带权并查集即可。

由于有负半轴，所以记得要把数轴上的位置转化到并查集上，细节较多。

```c++
#include<bits/stdc++.h>
#define int long long
#define m_p make_pair
#define p_b push_back
#define num first
#define color second
using namespace std;
inline int rd(){
	int x=0,f=1; char ch=getchar();
	for(;ch<'0'||ch>'9';ch=getchar())if (ch=='-') f=-1;
	for(;ch>='0'&&ch<='9';ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
	return x*f;
}
const int N=3e5+5,M=1e6;
int a[N],D[N],n,m;
int fa[M*2+5],val[M*2+5];//0:一样，1:变化
int find(int x){
	if(fa[x]==x) return x;
	int dad=fa[x];
	fa[x]=find(fa[x]);
	val[x]^=val[dad];
	return fa[x];
}
int ans[M*2+5];
signed main(){
	n=rd(),m=rd();
	for(int i=1;i<=n;i++) a[i]=rd();
	for(int i=1;i<=m;i++) D[i]=rd();
	int l=a[1],r=a[n];//在数轴上的范围，并查集的范围
	for(int i=0;i<=(M<<1);i++) fa[i]=i;
	int x,fx;
	for(int i=1;i<=m;i++){
		if(l>0) l-=D[i],r-=D[i];
		else l+=D[i],r+=D[i];
		if(l<=0&&0<=r){//横跨了远点
			x=M;fx=find(x);
			ans[fx]=i;
			if(-l<r){//移动往正半轴
				for(int i=1;i<=-l;i++){
					fa[M-i]=M+i;
					val[M-i]^=1;
				}
				l=1;
			}
			else{
				for(int i=1;i<=r;i++){
					fa[M+i]=M-i;
					val[M+i]^=1;
				}
				r=-1;
			}
		}
	}
	int now;
	for(int i=1;i<=n;i++){
		x=find(a[i]+M);
		if(ans[x]) printf("Yes %lld\n",ans[x]);
		else{
			now=x-M;
			if(val[a[i]+M])now*=-1;
			printf("No %lld\n",now);
		}
	}
	return 0;
}
```

---

## 作者：睿智的憨憨 (赞：2)

# ARC149 Simultaneous Sugoroku 解题报告

## 解法分析

数据结构维护这玩意儿似乎不太行。

看看如果题目问的不是离散的某些位置的答案，而是从 $1$ 开始连续的一段位置的答案该怎么求解。

刚开始的区间为 $[1,r]$，第一步，整个区间向左平移，假设平移较短距离，我们会发现原点左侧多出了一小段区间，它和右侧大区间中间相隔的落在原点上的点的答案此时就已经确定了。而我们惊讶的发现，左侧这一小段区间 $A$ 和 $A$ 关于原点对称落在右侧大区间上的一小段 $B$，$A$ 和 $B$ 接下来的移动**完全对称**（建议画个图），这意味着我们只需记录右边大区间中的数的答案，左边小区间的答案可以由右侧对应小区间得到。同理，如果向左平移距离较大，右侧出了个头，那就只需记录左侧的答案。也就是说，只需记录平移后原点两侧点数最多的区间的答案，另一边舍弃即可。

还有一个小 trick，通过上面舍弃区间的操作，每次原点只会在整个有效区间的左侧或右侧，那么区间往左往右移就等价于原点往相反方向移动相同距离，所以只需维护原点坐标与原点在整个区间的那一侧就能知道是否有点落在了原点上，以及原点分开的左右区间了。

为了实现大区间给小区间提供答案这一操作，我们需要让小区间中的每个点向大区间中对应的点连一条边，这样最后答案图就会形成若干棵树，从每个根节点向下 dfs 即可得到所有点的答案。

由于 $X_i$ 最大为 $10^6$，所以可以处理出 $[1,10^6]$ 的答案，最后输出每个 $X_i$ 的答案即可。

## 参考代码

```
#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pushf push_front
#define pushb push_back
#define popf pop_front
#define popb pop_back
#define lowbit(x) (x-(x&(x-1)))
using namespace std;
const int N = 300010, MX = 1000010;

int n, m, X[N], D[N];
bool arv[MX];
int ans[MX];
//当原点在所有点左边时，点左移等价于原点右移 
//同样的，当原点在所有点右边时，点右移等价于原点左移 
int z = 0, f = 0;//z为原点坐标，f=0/1表示原点在所有点左侧/右侧 
vector<int> e[MX], G;

void dfs(int u, bool f){
	for (int v : e[u]){
		arv[v] = arv[u], ans[v] = (f ? ans[u] : -ans[u]);
		dfs(v, f);
	}
}

int main(){
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d", &X[i]);
	for (int i = 1; i <= m; i++)
		scanf("%d", &D[i]);
	int l = 1, r = MX - 10;
	for (int i = 1; i <= m && l <= r; i++){//每次操作后原点都只会在最左侧或最右侧 
		z += (!f ? D[i] : -D[i]);
		if (z > r)//出到界外，并不影响区间内点的数量与答案 
			f = 1;
		else if (z < l)
			f = 0;
		else{
			arv[z] = true, ans[z] = i;//在原点的点之后不会再移动了，直接记录答案 
			G.push_back(z);
			int lc = z - l, rc = r - z;
			if (lc > rc){//左侧点数较多，此时可以舍弃右侧 
				for (int i = z + 1; i <= r; i++)
					e[2 * z - i].push_back(i);
				r = z - 1, f = 1;
			}
			else{//右侧点数较多，此时可以舍弃左侧 
				for (int i = z - 1; i >= l; i--)
					e[2 * z - i].push_back(i);
				l = z + 1, f = 0;
			}
		}
	}
	for (int i = l; i <= r; i++){//此时[l,r]里均是到不了原点的点，记录坐标 
		ans[i] = i - z;
		dfs(i, false);
	}
	for (int u : G)
		dfs(u, true);
	for (int i = 1; i <= n; i++){
		if (arv[X[i]])
			printf("Yes ");
		else
			printf("No ");
		printf("%d\n", ans[X[i]]); 
	}
	return 0;
}
```

---

## 作者：tribool4_in (赞：2)

很巧妙的题。

感觉没法用数据结构维护，发掘题目性质。首先注意到由于原点在所有点的左侧，第一次移动一定是都往同一方向（其实不重要），于是对于平移可以直接移动原点，记录其位置（大概是对于点相同距离的平移的常见 trick）。

乍一看这么做没什么用，因为第一次移动结束后原点左右两边都会有点。此时启动人类智慧，发现原点左右对称的点此后的移动都是对称的，即如果答案为 Yes 则移动次数相同，如果为 No 则最终位置相反。

因此，考虑维护值域上 $10^6$ 个点，每次原点移动后将当前区间劈成两个区间，原点所在位置的答案直接为当前移动次数 $i$，然后将较短段的每个位置暴力映射到较长段上对称位置。最后剩余区间内的每个点答案为 No，将其最终位置计算。

最终求答案时，对于每个点一直跳他的映射关系直到跳到有答案的位置。然后记忆化一下。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e6 + 10;
int n, m, x[N];
int res[N], lst[N], to[N];
void getans(int cur) {
    if (res[cur] || lst[cur]) return;
    getans(to[cur]);
    res[cur] = res[to[cur]], lst[cur] = -lst[to[cur]];
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> x[i];
    int p = 0, lp = 1, rp = (int)(1e6);
    for (int i = 1, d; i <= m; i++) {
        cin >> d;
        assert(p < lp || p > rp);
        if (p < lp) p += d;
        else if (p > rp) p -= d;
        if (p < lp || p > rp) continue;
        res[p] = i;
        if (p - lp < rp - p) {
            for (int i = lp; i < p; i++) to[i] = p * 2 - i;
            lp = p + 1;
        } else {
            for (int i = p + 1; i <= rp; i++) to[i] = p * 2 - i;
            rp = p - 1;
        }
    }
    for (int i = lp; i <= rp; i++) lst[i] = (i - p);
    for (int i = 1; i <= n; i++) {
        getans(x[i]);
        if (res[x[i]]) cout << "Yes " << res[x[i]] << '\n';
        else cout << "No " << lst[x[i]] << '\n';
    }
    return 0;
}
```

---

## 作者：EuphoricStar (赞：2)

很妙的一个题。

没法用数据结构直接维护点的移动。可以挖掘一些性质。

发现对于两个点 $x$ 和 $-x$，它们的移动关于原点对称。可以根据对称性维护森林。

维护当前的区间，初始为 $[1,10^6]$ 并且这个区间总是位于 $x$ 轴的同一个半轴中。假设当前遇到了操作 $d_i$，将区间根据正负向左或向右移 $d_i$ 格。若区间覆盖了原点，就把区间以原点为分界点分割，将较短的那一边对称到较长的那一边。

参考官方题解给的一张图：

![](https://img.atcoder.jp/arc149/9aa345ea3aa518aa46d7cd6f112c0760.png)

初始区间为 $[1,12]$，左移 $8$ 位，则 $8$ 到达了原点，接下来不用考虑了。剩下的两个区间 $[1,7]$ 和 $[9,12]$，将 $[9,12]$ 对称到 $[1,7]$ 中，在树中连向相应的边 $7 \to 9$，$6 \to 10$，$5 \to 11$，$4 \to 12$，表示将来的 $9$ 就继承 $7$ 的状态，等等。最后位置再取个反。后面的右移 $2$ 位同理。

最后一遍 dfs 求出最后每个点的状态。

实现时维护了一个 $add$ 表示整个区间的偏移量。

[code](https://atcoder.jp/contests/arc149/submissions/36366723)

---

## 作者：Genius_Star (赞：2)

**怎么就不能用数据结构维护了？**

### 思路：

考虑使用 fhq 平衡树维护。

一次操作，相当于先按 $0$ 值分裂为 $x, y$，然后将 $x$ 子树全部加上 $D$，$y$ 子树全部减去 $D$。

然后进行合并 $x, y$，这里使用平衡树有交合并，具体如下：

- 先找 $key$ 值较小的为根（设是 $x$）。

- 然后将 $y$ 按照 $x$ 的权值裂开为 $l, r$。

- 最后将 $x$ 的左儿子与 $l$ 合并，$x$ 的右儿子与 $r$ 合并。

- 注意若 $y$ 中存在与 $x$ 的权值相同的数，其的答案肯定和 $x$ 一样的，故使用并查集将其并在一起，然后在平衡树中删掉，不然无法保证复杂度。

之后再按 $0, -1$ 分裂为 $x, y, z$，将 $y$ 子树内的所有点更新为 `Yes`。

时间复杂度为 $O(N \log^2 N)$。

### 完整代码：

```cpp
 #include<bits/stdc++.h>
#define ls(k) k << 1
#define rs(k) k << 1 | 1
#define fi first
#define se second
#define open(s1, s2) freopen(s1, "r", stdin), freopen(s2, "w", stdout);
using namespace std;
typedef __int128 __;
typedef long double lb;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const int N = 3e5 + 10;
inline ll read(){
    ll x = 0, f = 1;
    char c = getchar();
    while(c < '0' || c > '9'){
        if(c == '-')
          f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9'){
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		x = -x;
	}
	if(x > 9)
	  write(x / 10);
	putchar(x % 10 + '0');
}
mt19937 R(time(0));
int n, m, v, cnt, rt;
int ans[N], fa[N];
bool f[N];
struct Node{
	int lson, rson;
	int data, tag, id;
	ll key;
}X[N];
inline int Find(int x){
	if(x != fa[x])
	  return fa[x] = Find(fa[x]);
	return fa[x];
}
inline void dsu_merge(int x, int y){
	x = Find(x), y = Find(y);
	if(x == y)
	  return ;
	fa[x] = y;
}
inline int newnode(int v, int id){
	++cnt;
	X[cnt].lson = X[cnt].rson = X[cnt].tag = 0;
	X[cnt].key = R();
	X[cnt].data = v;
	X[cnt].id = id;
	return cnt;
}
inline void add(int k, int v){
	if(!k)
	  return ;
	X[k].data += v;
	X[k].tag += v;
}
inline void push_down(int k){
	if(X[k].tag){
		add(X[k].lson, X[k].tag);
		add(X[k].rson, X[k].tag);
		X[k].tag = 0;
	}
}
inline void split(int k, int v, int &x, int &y){
	if(!k){
		x = y = 0;
		return ;
	}
	push_down(k);
	if(X[k].data <= v){
		x = k;
		split(X[k].rson, v, X[k].rson, y);
	}
	else{
		y = k;
		split(X[k].lson, v, x, X[k].lson);
	}
}
inline int merge(int x, int y){
	if(!x || !y)
	  return x + y;
	if(X[x].key < X[y].key){
		push_down(x);
		X[x].rson = merge(X[x].rson, y);
		return x;
	}
	else{
		push_down(y);
		X[y].lson = merge(x, X[y].lson);
		return y;
	}
}
inline void addfa(int k, int v){
	if(!k)
	  return ;
	dsu_merge(X[k].id, v);
	addfa(X[k].lson, v), addfa(X[k].rson, v);
}
inline int Merge(int x, int y){
	if(!x || !y)
	  return x + y;
	if(X[x].key > X[y].key)
	  swap(x, y);
	push_down(x);
	int l, r, p; 
	split(y, X[x].data, l, r);
	split(l, X[x].data - 1, l, p);
	addfa(p, X[x].id);
	X[x].lson = Merge(X[x].lson, l);
	X[x].rson = Merge(X[x].rson, r);
	return x;
}
inline void insert(int v, int id){
	int x, y;
	split(rt, v, x, y);
	rt = merge(merge(x, newnode(v, id)), y);
}
inline void sol(int k, int v){
	if(!k)
	  return ;
	push_down(k);
	if(v){
		ans[X[k].id] = v;
		f[X[k].id] = 1;
	}
	else
	  ans[X[k].id] = X[k].data;
	sol(X[k].lson, v), sol(X[k].rson, v);
}
bool End;
int main(){
//	open("A.in", "A.out");
	n = read(), m = read();
	for(int i = 1; i <= n; ++i){
		fa[i] = i;
		v = read();
		if(!v){
			f[i] = 1;
			ans[i] = 0;
			continue;
		}
		insert(v, i);
	}
	for(int i = 1; i <= m; ++i){
		v = read();
		int x, y;
		split(rt, 0, x, y);
		add(x, v), add(y, -v);
		rt = Merge(x, y);
		int z;
		split(rt, 0, x, z);
		split(x, -1, x, y);
		sol(y, i);
		rt = merge(x, z);
	}
	sol(rt, 0);
	for(int i = 1; i <= n; ++i){
		fa[i] = Find(i);
		if(f[fa[i]])
		  printf("Yes %d\n", ans[fa[i]]);
		else
		  printf("No %d\n", ans[fa[i]]);
	}
	cerr << '\n' << abs(&Begin - &End) / 1048576 << "MB";
	return 0;
}
```

---

## 作者：cwfxlh (赞：1)

# [AT_arc149_d](https://www.luogu.com.cn/problem/AT_arc149_d)          

明明做法很简单，但是想起来却怎么也想不到，怎么回事呢。                  

不考虑什么数据结构之类的东西，直接考虑维护答案，显然，如果坐标都是正数或负数，那么移动就是简单的整体平移，记一个位移标记即可。当出现了正负不同时，发现 $a_i$ 的答案与 $-a_i$ 的答案是高度相似的，于是可以将短的一侧翻转过去，向另一侧连边，即可做到线性。             

代码：          


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,a[1000003],d[1000003],ans[1000003][2],bcj[1000003][2],vis[1000003],dltv,lft,rgt,midp;
void getans(int now){
    if(vis[now])return;
    vis[now]=1;
    getans(bcj[now][0]);
    ans[now][0]=ans[bcj[now][0]][0];
    ans[now][1]=bcj[now][1]*ans[bcj[now][0]][1];
    return;
}
signed main(){
    ios::sync_with_stdio(false);
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=m;i++)cin>>d[i];
    for(int i=1;i<=1000000;i++){
        bcj[i][0]=i;
        bcj[i][1]=1;
    }
    lft=1;
    rgt=1000000;
    for(int i=1;i<=m;i++){
        if(lft+dltv<0)dltv+=d[i];
        else dltv-=d[i];
        if(lft+dltv>0||rgt+dltv<0)continue;
        midp=lft-(lft+dltv);
        if(-(lft+dltv)<rgt+dltv){
            while(lft+dltv<0){
                bcj[lft][0]=2*midp-lft;
                bcj[lft][1]=-1;
                lft++;
            }
        }
        else{
            while(rgt+dltv>0){
                bcj[rgt][0]=2*midp-rgt;
                bcj[rgt][1]=-1;
                rgt--;
            }
        }
        if(lft+dltv==0){
            vis[lft]=1;
            ans[lft][0]=1;
            ans[lft][1]=i;
            lft++;
        }
        if(rgt+dltv==0){
            vis[rgt]=1;
            ans[rgt][0]=1;
            ans[rgt][1]=i;
            rgt--;
        }
        if(lft>rgt)break;
    }
    for(int i=lft;i<=rgt;i++){
        ans[i][0]=0;
        ans[i][1]=i+dltv;
        vis[i]=1;
    }
    for(int i=1;i<=1000000;i++)getans(i);
    for(int i=1;i<=n;i++){
        if(ans[a[i]][0])cout<<"Yes ";
        else cout<<"No ";
        if(ans[a[i]][0]==1)ans[a[i]][1]=abs(ans[a[i]][1]);
        cout<<ans[a[i]][1]<<'\n';
    }
    return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：1)

[Problem Link](https://www.luogu.com.cn/problem/AT_arc149_d)

**题目大意**

> 给定一个动点 $x$，$m$ 次操作给定 $d$：若 $x<0$ 则 $x\gets x+d$，$x=0$ 则停止运动，$x>0$ 则 $x\gets x-d$。
>
> $n$ 次询问初始 $x=x_1\sim x_n$ 时，$x$ 会不会停止，什么时候停止，或最终移动到了哪里。
>
> 数据范围：$x\le 10^6,n,m\le 3\times 10^5$。

**思路分析**

注意到值域并不大，因此我们可以维护所有 $[1,V]$ 的答案，注意到某个时刻两个动点位置互为相反数，那么他们之后的位置也一定互为相反数。

类似 [TEST_100](https://www.luogu.com.cn/problem/P8264) 的思路，我们维护一个区间 $[l,r]$ 的答案，每次操作后，如果 $l'\le 0\le r'$，我们就把 $[l',0),(0,r']$ 中较小的一个区间向另一个区间合并，表示该区间的答案可以由另一个区间维护，具体只要连边建图即可。

注意到每个点只会被删除一次，因此复杂度 $\mathcal O(V)$。

时间复杂度 $\mathcal O(n+m+V)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e6+5,V=1e6;
int x[MAXN],p[MAXN],q[MAXN];
vector <int> G[MAXN];
bool vis[MAXN];
void dfs(int u) {
	if(vis[u]) return ; vis[u]=true;
	for(int v:G[u]) (p[u]?p[v]=p[u]:q[v]=-q[u]),dfs(v);
}
signed main() {
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i) scanf("%d",&x[i]);
	int l=1,r=V,d=0;
	for(int i=1,v;i<=m;++i) {
		scanf("%d",&v),d+=(r+d<0?v:-v);
		int k=-d;
		if(l<=k&&k<=r) {
			p[k]=i;
			if(k-l<r-k) {
				for(int j=l;j<k;++j) G[2*k-j].push_back(j);
				l=k+1;
			} else {
				for(int j=r;j>k;--j) G[2*k-j].push_back(j);
				r=k-1;
			}
		}
	}
	for(int i=l;i<=r;++i) if(!p[i]) q[i]=i+d,dfs(i);
	for(int i=1;i<=V;++i) if(p[i]) dfs(i);
	for(int i=1;i<=n;++i) {
		if(p[x[i]]) printf("Yes %d\n",p[x[i]]);
		else printf("No %d\n",q[x[i]]);
	}
	return 0;
}
```

---

## 作者：Feyn (赞：1)

[更多的 ARC 题目](https://www.cnblogs.com/Feyn/p/16977678.html)

相当 educational。

我们希望给一个区间中的数全部减去某个值，等价于区间不动而去移动原点的位置。但是这似乎并不能解决问题，因为如果区间跨原点的话每个元素的决策是不同的。但此时可以注意到一件事情说关于原点对称的两个点答案应该也是对称的，所以可以考虑用原点把区间切成两个部分，然后暴力遍历较小的那个部分的所有元素指向对应元素，然后调整左右端点即可。查询的时候做一次记忆化就可以了，代码写起来非常简单。

```cpp
#include<bits/stdc++.h>
// #define feyn
using namespace std;
const int N=1000000;
inline void read(int &wh){
    wh=0;int f=1;char w=getchar();
    while(w<'0'||w>'9'){if(w=='-')f=-1;w=getchar();}
    while(w<='9'&&w>='0'){wh=wh*10+w-'0';w=getchar();}
    wh*=f;return;
}

int m,n,qu[N+10],d[N+10];

int to[N],ti[N],dataa[N];

inline void find(int wh){
    if(dataa[wh]!=0||ti[wh]!=0)return;
    find(to[wh]);
    ti[wh]=ti[to[wh]],dataa[wh]=-dataa[to[wh]];
    return;
}

signed main(){
	
	#ifdef feyn
	freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    #endif

    read(m);read(n);
    for(int i=1;i<=m;i++)read(qu[i]);
    for(int i=1;i<=n;i++)read(d[i]);

    int l=1,r=N,p=0;
    for(int i=1;i<=n;i++){
        int q=d[i];
        if(p<l)p+=q;else p-=q;
        if(p<l||p>r)continue;

        ti[p]=i;int ll=p-l,rr=r-p;
        if(ll>rr){for(int i=p+1;i<=r;i++){to[i]=p*2-i;}r=p-1;}
        else{for(int i=l;i<p;i++)to[i]=p*2-i;l=p+1;}
    }
    for(int i=l;i<=r;i++)dataa[i]=i-p;
    for(int i=1;i<=m;i++){
        find(qu[i]);
        if(ti[qu[i]])printf("Yes %d\n",ti[qu[i]]);
        else printf("No %d\n",dataa[qu[i]]);
    }

    return 0;
}
```

---

## 作者：youyew2007 (赞：1)

# [ARC149D] Simultaneous Sugoroku

## Translation
请求修改翻译，翻译中没有给出 $D$ 是不同的这一点。\
给定一个数轴，上面有 $n$ 个点 $x_1,x_2,…,x_n$ ，你需要对每一个点进行 $M$ 次移动，规则如下：\
对于每个 $x_i$ :\
若其坐标 $>0$，向负方向移动 $D_j$ 个单位；\
若其坐标 $=0$，停止移动；\
若其坐标 $<0$，向正方向移动 $D_j$ 各单位。\
其中 $1 \leq i \leq n,1 \leq j \leq M$。

你需要判断每个点是否会到达原点，\
是：输出 "Yes" ，然后输出它使用了几次移动；\
否：输出 "No" ，然后输出它 $M$ 次移动后的坐标。

## Solution
### Step 1:
我们观察题意，可以发现对于 $x$ 向左移动 $D$ 个单位和 $-x$ 向右移动 $D$ 个单位是一致的（ $x>0$ )。也就是说，负数和正数在操作上是等价的，他们的操作对于原点对称。

### Step 2:
随后，我们考虑对于点的移动进行分析，由 step 1 我们得到了数轴上的点的对称性，所以我们考虑枚举从原点到最大的 $x_i$ 的绝对值中间的所有点。\
具体地，当进行一次操作后，我们记录当前到达原点的点的操作次数，此时我们的片段被分成了两端，我们可以将少的一段连接到原点另一侧的部分，也就是建立有向边。（见图，图片来自AT官方题解）
![AT](https://img.atcoder.jp/arc149/9aa345ea3aa518aa46d7cd6f112c0760.png)

### 本题的代码比较好实现，这里不再给出。

---

## 作者：Fanch100 (赞：0)

### 背景

[题目链接](https://atcoder.jp/contests/arc149/tasks/arc149_d)

前几周 ARC 赛时写 B 写了很久，导致 D 没时间写了，后来才补上，感觉思想很妙。

### 分析

先来考虑更简单的问题，即数轴每个点都朝**相同**的方向移动，且不会到达原点。

解决这个问题，我们可以换个角度，理解为将原点往反方向移动相同的步数，维护原点当前移动到的位置 $pos$，此时各点和原点的相对坐标差不变，因此最后相对坐标差即为答案。

此题可以沿用相同的思路，但遇到的问题是，原点左右两侧数字的移动方向不同，左侧的向右，右侧的向左，无法用同一个原点左移或右移维护。

假设每次遇到这样的情况都把序列一分为二，复杂度是 $O(2^m)$ 往上的，不能接受。

我们可以发现，原点左右两侧根据原点**对称**的点的移动仍然是根据原点**对称**的（例如当前与原点坐标差分别为 $-1$ 和 $1$ 的点集），因此在最终的结果中一定坐标互为相反数，或者在某一步移动至原点。

这启示我们忽略其中一侧的移动，而是通过把另一侧的对称点向这一侧的点连边建立关系，最后从未被忽略的点开始进行 dfs，每搜索到一个点对坐标取相反数，便可得到得到每个点的最终坐标。

对于原点曾移动到的每个位置 $x$，如果在值域范围内，可以直接标记并记录移动次数，dfs 时把与 $x$ 有连边的点全都更新为和 $x$ 相同的答案即可。

由于每个点入度最多为 $1$，故边数不会超过 $10^6$，复杂度 $O(m+V)$。

附官方题解图以方便更好理解：

![](https://img.atcoder.jp/arc149/9aa345ea3aa518aa46d7cd6f112c0760.png)

### 注意事项：

- 未被忽略的点一定构成了一个区间 $[l,r]$，可能出现当前的 $pos$ 并不在这个区间内（比如 $D_i$ 过大导致原点移到了区间另一侧）的情况，此时不用进行操作，因为仍保持了所有剩余点在原点同一侧，可以继续操作。

- 合并时一定是忽略长度较短的一侧，保证不超出范围，同时由较长的一侧向较短的一侧连边更容易实现。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1000010;
const int M = 1000010;
int head[N], pre[M], ver[M], tot;
void add(int x,int y){
    ver[++tot]=y; pre[tot]=head[x]; head[x]=tot;
}
int n, m;
int a[N], pos;
int ans[N];
bool vis[N], arr[N];//维护每个点是否被忽略，是否达到原点
void dfs(int x){
    for (int i=head[x]; i; i=pre[i]){
        int v=ver[i];
        if (!arr[x]) {
            arr[v]=0;
            ans[v]=-ans[x];
        }
        else {
            arr[v]=1;
            ans[v]=ans[x];
        }
        dfs(v);
    }
}
int main(){
    cin>>n>>m;
    for (int i=1;i<=n;++i) cin>>a[i];
    int l=1,r=1e6;
    for (int i=1;i<=m;++i){
        int x;cin>>x;
        if (pos<l) pos+=x;//pos小于l，右移
        else pos-=x;//实际上pos>l也一定>r
        if (pos<l || r<pos) continue;//这次移动没有影响
        arr[pos]=1; ans[pos]=i;
        if (pos-l<r-pos){
            for (int j=l;j<pos;++j){
                add(2*pos-j,j);
                vis[j]=1;
            }
            l=pos+1;
        }
        else{
            for (int j=r;j>pos;--j){
                add(2*pos-j,j);
                vis[j]=1;
            }
            r=pos-1;
        }
    }
    for (int i=l;i<=r;++i) {
        arr[i]=0; ans[i]=i-pos;
    }
    for (int i=1;i<=1e6;++i){
        if (!vis[i]) dfs(i);
    }
    for (int i=1;i<=n;++i){
        if (arr[a[i]]) printf("Yes ");
        else printf("No ");
        printf("%d\n",ans[a[i]]);
    }
    return 0;
}


```

---

## 作者：_Linver_ (赞：0)

1. 直接上数据结构
   - 用**范浩强平衡树**维护。

2. 步骤
   - 初始按权值 0 分裂为两棵树 `x` 和 `y`。
   - 对 `x` 子树内所有节点权值增加 `D`，对 `y` 子树内所有节点权值减少 `D`。
   - 合并 `x` 和 `y`，需保证合并后平衡性：
     1. 选根：取值较小的树作为根（设为 `x`）。
     2. 分裂 `y` 树：以 `x` 的权值为基准，将 `y` 分裂为左子树 `l` 和右子树 `r`。
     3. 合并：将 `x` 的左子树与 `l` 合并，右子树与 `r` 合并。

3. 标记
   - 最终按权值 `0` 和 `-1` 将整棵树分裂为 `x`, `y`, `z`，将中间子树 `y` 的所有节点标记为 "Yes"。

4. 复杂度
   - 总时间复杂度为 $O(n \log^2 n)$，平衡树合并来的。
  
```cpp
#include <bits/stdc++.h>
std::mt19937_64 myrand (
    std::chrono::high_resolution_clock::now ().time_since_epoch ().count ());
inline int
R (int n)
{
  return myrand () % n + 1;
}
inline int
read ()
{
  char ch = getchar ();
  int x = 0, f = 1;
  for (; ch < '0' || ch > '9'; ch = getchar ())
    if (ch == '-')
      f = -1;
  for (; ch >= '0' && ch <= '9'; ch = getchar ())
    x = (x << 3) + (x << 1) + (ch ^ 48);
  return x * f;
}
inline void
Min (int &x, int y)
{
  if (x > y)
    x = y;
}
inline void
Max (int &x, int y)
{
  if (x < y)
    x = y;
}
namespace std
{
const int N = 3e5 + 10;
inline ll
read ()
{
  ll x = 0, f = 1;
  char c = getchar ();
  while (c < '0' || c > '9')
    {
      if (c == '-')
        f = -1;
      c = getchar ();
    }
  while (c >= '0' && c <= '9')
    {
      x = (x << 1) + (x << 3) + (c ^ 48);
      c = getchar ();
    }
  return x * f;
}
inline void
write (ll x)
{
  if (x < 0)
    {
      putchar ('-');
      x = -x;
    }
  if (x > 9)
    write (x / 10);
  putchar (x % 10 + '0');
}
mt19937 R (time (0));
int n, m, v, cnt, rt;
int ans[N], fa[N];
bool f[N];
struct Node
{
  int lson, rson;
  int data, tag, id;
  ll key;
} X[N];
inline int
Find (int x)
{
  if (x != fa[x])
    return fa[x] = Find (fa[x]);
  return fa[x];
}
inline void
dsu_merge (int x, int y)
{
  x = Find (x), y = Find (y);
  if (x == y)
    return;
  fa[x] = y;
}
inline int
newnode (int v, int id)
{
  ++cnt;
  X[cnt].lson = X[cnt].rson = X[cnt].tag = 0;
  X[cnt].key = R ();
  X[cnt].data = v;
  X[cnt].id = id;
  return cnt;
}
inline void
add (int k, int v)
{
  if (!k)
    return;
  X[k].data += v;
  X[k].tag += v;
}
inline void
push_down (int k)
{
  if (X[k].tag)
    {
      add (X[k].lson, X[k].tag);
      add (X[k].rson, X[k].tag);
      X[k].tag = 0;
    }
}
inline void
split (int k, int v, int &x, int &y)
{
  if (!k)
    {
      x = y = 0;
      return;
    }
  push_down (k);
  if (X[k].data <= v)
    {
      x = k;
      split (X[k].rson, v, X[k].rson, y);
    }
  else
    {
      y = k;
      split (X[k].lson, v, x, X[k].lson);
    }
}
inline int
merge (int x, int y)
{
  if (!x || !y)
    return x + y;
  if (X[x].key < X[y].key)
    {
      push_down (x);
      X[x].rson = merge (X[x].rson, y);
      return x;
    }
  else
    {
      push_down (y);
      X[y].lson = merge (x, X[y].lson);
      return y;
    }
}
inline void
addfa (int k, int v)
{
  if (!k)
    return;
  dsu_merge (X[k].id, v);
  addfa (X[k].lson, v), addfa (X[k].rson, v);
}
inline int
Merge (int x, int y)
{
  if (!x || !y)
    return x + y;
  if (X[x].key > X[y].key)
    swap (x, y);
  push_down (x);
  int l, r, p;
  split (y, X[x].data, l, r);
  split (l, X[x].data - 1, l, p);
  addfa (p, X[x].id);
  X[x].lson = Merge (X[x].lson, l);
  X[x].rson = Merge (X[x].rson, r);
  return x;
}
inline void
insert (int v, int id)
{
  int x, y;
  split (rt, v, x, y);
  rt = merge (merge (x, newnode (v, id)), y);
}
inline void
sol (int k, int v)
{
  if (!k)
    return;
  push_down (k);
  if (v)
    {
      ans[X[k].id] = v;
      f[X[k].id] = 1;
    }
  else
    ans[X[k].id] = X[k].data;
  sol (X[k].lson, v), sol (X[k].rson, v);
}
int
main ()
{
  n = read (), m = read ();
  for (int i = 1; i <= n; ++i)
    {
      fa[i] = i;
      v = read ();
      if (!v)
        {
          f[i] = 1;
          ans[i] = 0;
          continue;
        }
      insert (v, i);
    }
  for (int i = 1; i <= m; ++i)
    {
      v = read ();
      int x, y;
      split (rt, 0, x, y);
      add (x, v), add (y, -v);
      rt = Merge (x, y);
      int z;
      split (rt, 0, x, z);
      split (x, -1, x, y);
      sol (y, i);
      rt = merge (x, z);
    }
  sol (rt, 0);
  for (int i = 1; i <= n; ++i)
    {
      fa[i] = Find (i);
      if (f[fa[i]])
        printf ("Yes %d\n", ans[fa[i]]);
      else
        printf ("No %d\n", ans[fa[i]]);
    }
  return 0;
}
}
const int N = 1e6 + 10, V = 1e6 + 10;
int n, m, fa[V], a[N], ans[V];
bool v[V];
inline int
find (int x)
{
  if (fa[x] == x)
    return x;
  int d = fa[x];
  fa[x] = find (fa[x]);
  return v[x] ^= v[d], fa[x];
}
signed
main ()
{
  std::ios::sync_with_stdio (false);
  std::cin.tie (0);
  std::cout.tie (0);
  n = read (), m = read ();
  for (int i = 1; i <= n; ++i)
    a[i] = read ();
  for (int i = a[1]; i <= a[n]; ++i)
    fa[i] = i;
  int o = 0;
  for (int i = 1, l = a[1], r = a[n]; i <= m; ++i)
    {
      int x = read ();
      if (o < l)
        o += x;
      else
        o -= x;
      if (l <= o && r >= o)
        {
          ans[o] = i;
          if (o - l < r - o)
            {
              for (int i = l; i < o; ++i)
                fa[i] = 2 * o - i, v[i] ^= 1;
              l = o + 1;
            }
          else
            {
              for (int i = r; i > o; --i)
                fa[i] = 2 * o - i, v[i] ^= 1;
              r = o - 1;
            }
        }
    }
  for (int i = 1; i <= n; ++i)
    {
      int x = find (a[i]);
      if (ans[x])
        std::cout << "Yes " << ans[x] << '\n';
      else
        std::cout << "No " << (v[a[i]] ? o - x : x - o) << '\n';
    }
}
```

---

