# Professor Higashikata

## 题目描述

Josuke is tired of his peaceful life in Morioh. Following in his nephew Jotaro's footsteps, he decides to study hard and become a professor of computer science. While looking up competitive programming problems online, he comes across the following one:

Let $ s $ be a binary string of length $ n $ . An operation on $ s $ is defined as choosing two distinct integers $ i $ and $ j $ ( $ 1 \leq i < j \leq n $ ), and swapping the characters $ s_i, s_j $ .

Consider the $ m $ strings $ t_1, t_2, \ldots, t_m $ , where $ t_i $ is the substring $ ^\dagger $ of $ s $ from $ l_i $ to $ r_i $ . Define $ t(s) = t_1+t_2+\ldots+t_m $ as the concatenation of the strings $ t_i $ in that order.

There are $ q $ updates to the string. In the $ i $ -th update $ s_{x_i} $ gets flipped. That is if $ s_{x_i}=1 $ , then $ s_{x_i} $ becomes $ 0 $ and vice versa. After each update, find the minimum number of operations one must perform on $ s $  to make $ t(s) $ lexicographically as large $ ^\ddagger $ as possible.

Note that no operation is actually performed. We are only interested in the number of operations.

Help Josuke in his dream by solving the problem for him.

 ——————————————————————  $ \dagger $ A string $ a $ is a substring of a string $ b $ if $ a $ can be obtained from $ b $ by the deletion of several (possibly, zero or all) characters from the beginning and several (possibly, zero or all) characters from the end.

 $ \ddagger $ A string $ a $ is lexicographically larger than a string $ b $ of the same length if and only if the following holds:

- in the first position where $ a $ and $ b $ differ, the string $ a $ has a $ 1 $ , and the string $ b $ has a $ 0 $ .

## 说明/提示

In the first test case,

Originally, $ t(s) = s(1,2) + s(1,2) = 0101 $ .

After the $ 1 $ -st query, $ s $ becomes $ 11 $ and consequently $ t $ becomes $ 1111 $ . You don't need to perform any operation as $ t(s) $ is already the lexicographically largest string possible.

After the $ 2 $ -nd query, $ s $ becomes $ 01 $ and consequently $ t $ becomes $ 0101 $ . You need to perform $ 1 $ operation by swapping $ s_1 $ and $ s_2 $ . Consequently, $ t(s) $ becomes $ 1010 $ which is the lexicographically largest string you can achieve.

## 样例 #1

### 输入

```
2 2 4
01
1 2
1 2
1
1
2
2```

### 输出

```
0
1
0
1```

## 样例 #2

### 输入

```
8 6 10
10011010
5 6
2 3
6 8
5 7
5 8
6 8
3
5
6
2
5
2
5
8
4
1```

### 输出

```
2
3
2
2
1
2
2
2
2
2```

# 题解

## 作者：y_kx_b (赞：9)

感谢比赛延长的 15min。

首先看到题目感觉很晕，通过最小的交换次数使得 $m$ 个可交子串依次拼成的字符串字典序最大……？但是考虑到这个字符串只有 0 和 1，那么字典序最大就是前面要有尽可能多的 1 了。

现在考虑相交的问题。（如果没有相交那么很好说，贪心把当前所有 1 都往第一个子串放，放满了还有多的就去第二个子串……）如果 $t(s)$ 第二次出现了 $s$ 字符串的某个位置，那么显然：

- 如果第一次出现的位置填的是 0：和这个第二次出现没关系了（因为 1 已经用完了）。
- 如果第一次出现的位置填的是 1：这个（第二次出现的）位置一定是 1，也和这个位置没关系了（因为不影响最大字典序）。

那么我们显然只需要考虑原 $s$ 串中的每个位置第一次在 $t(s)$ 中间出现的位置（即抢 1 的优先级）即可。预处理之后，设当前 $s$ 串中有 $x$ 个 1，那么显然这 $x$ 个 1 都应该去填优先级前 $x$ 名的位置。那么只要查询这前 $x$ 名原来已经有多少个 1 了，答案就是 0 的数量（每一个 0 都可以被其他地方的空闲的 1 交换，需要且仅需要一次操作）。

如何维护？考虑映射。把优先级为 1（最大）的点映射成 1 号点，优先级为 2（次大）的点映射成 2 号点……那么上述操作就是查询（映射后的）$1\sim x$ 区间和，外加单点修改（flip）。显然可以树状数组维护之。

最后一个问题，如何处理优先级？对于暴力做法，我们可以考虑依次扫一遍每个线段，扫到如果没有扫到的元素（第一次在 $t(s)$ 中出现），并且当前已经有 $k$ 个已扫过的元素，那么当前元素优先级为 $k+1$（除去已有的 $k$ 个元素，这是优先级最大的元素）。

但是暴力是 $O(nm)$ 的。如何优化？发现中途可能扫到成片的已扫过的区域，浪费了很多时间。我们考虑类似 [P4145 花神游历各国](https://www.luogu.com.cn/problem/P4145)的并查集方法，令 `find(x)` 表示 x 右边的第一个已扫过的连续段的最右端点（如果 `vis[x+1] = 0` 那么 `find(x) = x`），那么每次扫线段的时候把 `j++` 改成 `j=find(j)+1` 就可以让时间复杂度降到 $O(n+m)$。为什么？因为空位的数量是 $n$，而这样写 `j` 只会跳到空位。

完结撒花 qwq

code：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int DUST = 327, N = 214514;
int read() {int x; scanf("%d", &x); return x;}

char str[N]; bool s[N];//原 s 串，用 bool 存方便点。
int p[N];//优先级（值越小越优先）
int fa[N]; bool vis[N];
int find(int x) {
	return fa[x] == x ? x : (fa[x] = find(fa[x]));
}//返回该点右边连通块的最右端点
int idx2;
#define lowbit(x) ((x) & -(x))
int c[N];
void add(int P, int x) {
	if(!P) return;//如果这个点没访问过（不在 t(s) 串内）
				  //那么对这个点的修改显然不影响答案，可以忽略
	while(P <= idx2)
		c[P] += x, P += lowbit(P);
}
int query(int x) {
	int ans = 0;
	while(x) ans += c[x], x -= lowbit(x);
	return ans;
}
bool major(int Testcase = 1) {//（可以理解为你们写的 solve 函数，虽然这题不需要多测）
	int n = read(), m = read(), q = read();
	scanf("%s", str + 1);
	for(int i = 1; i <= n; i++)
		s[i] = str[i] - '0', fa[i] = i, vis[i] = 0, /**/p[i] = 0, c[i] = 0;;//这个 baka 还是下意识写了多测清空……
	/*int */idx2 = 0;
	for(int i = 1; i <= m; i++) {
		int l = read(), r = read();
		for(int j = l; j <= r; /*j++*/j = find(j) + 1)
			if(!vis[j])
				vis[j] = 1, p[j] = ++idx2, fa[j - 1] = j;
			//当前点被访问过了，更新这个点左边的点的fa即可
	}
	// for(int i = 1; i <= n; i++) debug(i, p[i]);//这个 sb 没注释调试语句 T 了一发（cerr 太慢了）
	int sumx = 0;//当前序列 1 的数量
	for(int i = 1; i <= n; i++) if(s[i]) sumx++, add(p[i], 1);
	while(q--) {
		int x = read();
		if(s[x]) sumx--, s[x] = 0, add(p[x], -1);
		else sumx++, s[x] = 1, add(p[x], 1);
		int r = min(sumx, idx2);//最多可以填多少个 1 来达成 t(s) 字典序最大
		printf("%d\n", r - query(r));//还需要往 [1, r] 填多少个 1 才能变成全 1
	}
	return Testcase;
}
int main() {
	int T = 1; while(T--) major();
}
```

---

## 作者：Binary_Lee (赞：5)

## [题面传送门](https://www.luogu.com.cn/problem/CF1847D)

### 解决思路

首先我们考虑，优先把原字符串 $s$ 中哪些位置变 `1` 会使得拼接后字符串 $t$ 的字典序尽可能大。我们把每个位置的这一信息称为“优先级”。根据题目意思可以得出，将 $m$ 个区间依次拼接，一个位置第一次出现越靠前，它的优先级越高。

然后考虑如何求出每个位置的优先级。这里讲一种区间覆盖的方法。从最后一个区间开始做区间覆盖。对于第 $m-i+1(1\le i\le m)$ 个区间，我们将这个区间的值覆盖为 $i$。所有区间覆盖完成后，对全部位置进行排序：第一关键字为覆盖上去的值，从大到小（最后被覆盖的说明区间靠前，优先级高）；第二关键字为原先的位置，从小到大（同一区间内位置靠前的优先）。这样我们就得出了每个位置的优先级。

再考虑求出优先级后如何计算每次询问的答案。我们假设当前原字符串 **有用的** `1` 的个数为 $cnt$，那么要使得拼接得到的字符串 $t$ 的字典序最大，应该让原字符串中优先级前 $cnt$ 个位置全部变成 `1`。设原字符串中优先级前 $cnt$ 个位置当前有 $tot$ 个 `1`。那么答案显而易见，就是 $cnt-tot$。

注意上一段的粗体字：什么是**有用的** `1`？考虑一种情况，那就是原字符串 $s$ 中，有一些位置根本没有出现在拼接后字符串 $t$ 中。这些位置上是 `0` 或 `1` 是无所谓的。所以如果计算全部 `1` 的个数作为 $cnt$，就可能导致一些无关的位置被变成 `1`，从而使答案偏大。所以 $cnt$ 应该是 $\min(\text{总共 1 的个数},\text{在 t 串中出现过的位置数})$。（~~没有考虑这一点会导致 Wa on 13~~）

具体实现中，区间覆盖和维护 `1` 的个数我选用的都是线段树，所以看着比较长，其实是不难写的。

### AC Code

```cpp
//If, one day, I finally manage to make my dreams a reality...
//I wonder, will you still be there by my side?
#include<bits/stdc++.h>
#define IOS ios::sync_with_stdio(false)
#define TIE cin.tie(0),cout.tie(0)
#define int long long
#define y1 cyy
#define fi first
#define se second
#define cnt1(x) __builtin_popcount(x)
#define mk make_pair
#define pb push_back
#define pii pair<int,int>
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)
#define lbt(x) (x&(-x))
using namespace std;
struct SGT{
    struct node{
        int l,r,sum,tag;
    }tr[800005]; 
    void build(int i,int l,int r){
        tr[i].l=l,tr[i].r=r,tr[i].tag=0;
        if(l==r) return ;
        int mid=(l+r)>>1;
        build(ls(i),l,mid),build(rs(i),mid+1,r);
        tr[i].sum=tr[ls(i)].sum+tr[rs(i)].sum;
    }
    void pushdown(int i){
        if(tr[i].tag){
            tr[ls(i)].tag=tr[i].tag;
            tr[rs(i)].tag=tr[i].tag;
            tr[ls(i)].sum=(tr[ls(i)].r-tr[ls(i)].l+1)*tr[i].tag;
            tr[rs(i)].sum=(tr[rs(i)].r-tr[rs(i)].l+1)*tr[i].tag;
            tr[i].tag=0;
        }
    }
    void turn(int i,int l,int r,int k){
        if(tr[i].l>=l&&tr[i].r<=r){
            tr[i].tag=k,tr[i].sum=(tr[i].r-tr[i].l+1)*k;
            return ;
        }
        pushdown(i);
        int mid=(tr[i].l+tr[i].r)>>1;
        if(l<=mid) turn(ls(i),l,r,k);
        if(mid<r) turn(rs(i),l,r,k);
        tr[i].sum=tr[ls(i)].sum+tr[rs(i)].sum; 
    }
    int query(int i,int l,int r){
        if(tr[i].l>=l&&tr[i].r<=r) return tr[i].sum;
        pushdown(i);
        int mid=(tr[i].l+tr[i].r)>>1,ans=0;
        if(l<=mid) ans+=query(ls(i),l,r);
        if(mid<r) ans+=query(rs(i),l,r);
        return ans;
    }
}sgt;

struct SGT2{
    struct node{
        int l,r,sum,tag;
    }tr[800005]; 
    void build(int i,int l,int r){
        tr[i].l=l,tr[i].r=r,tr[i].sum=tr[i].tag=0;
        if(l==r){
        	tr[i].sum=0;
        	return ;
		}
        int mid=(l+r)>>1;
        build(ls(i),l,mid),build(rs(i),mid+1,r);
        tr[i].sum=tr[ls(i)].sum+tr[rs(i)].sum;
    }
    void pushdown(int i){
        if(tr[i].tag){
            tr[ls(i)].tag+=tr[i].tag;
            tr[rs(i)].tag+=tr[i].tag;
            tr[ls(i)].sum+=(tr[ls(i)].r-tr[ls(i)].l+1)*tr[i].tag;
            tr[rs(i)].sum+=(tr[rs(i)].r-tr[rs(i)].l+1)*tr[i].tag;
            tr[i].tag=0;
        }
    }
    void add(int i,int l,int r,int k){
        if(tr[i].l>=l&&tr[i].r<=r){
            tr[i].tag+=k,tr[i].sum+=(tr[i].r-tr[i].l+1)*k;
            return ;
        }
        pushdown(i);
        int mid=(tr[i].l+tr[i].r)>>1;
        if(l<=mid) add(ls(i),l,r,k);
        if(mid<r) add(rs(i),l,r,k);
        tr[i].sum=tr[ls(i)].sum+tr[rs(i)].sum; 
    }
    int query(int i,int l,int r){
        if(tr[i].l>=l&&tr[i].r<=r) return tr[i].sum;
        pushdown(i);
        int mid=(tr[i].l+tr[i].r)>>1,ans=0;
        if(l<=mid) ans+=query(ls(i),l,r);
        if(mid<r) ans+=query(rs(i),l,r);
        return ans;
    }
}sgt2;

struct node{
	int l,r;
}a[200005];
struct dot{
	int id,rk;
}b[200005];
bool cmp(dot a,dot b){
	if(a.rk==b.rk) return a.id<b.id;
	return a.rk>b.rk;
}
int T,n,m,q,t;
string s;
int yxj[200005];
void solve(){
	cin>>n>>m>>q>>s;
	s=" "+s;
	for(int i=1;i<=m;i++) cin>>a[i].l>>a[i].r;
	int tmp=1;
	sgt.build(1,1,n);
	for(int i=m;i>=1;i--) sgt.turn(1,a[i].l,a[i].r,tmp++);
	for(int i=1;i<=n;i++) b[i]={i,sgt.query(1,i,i)};
	sort(b+1,b+n+1,cmp);
	int mx=n;
	for(int i=1;i<=n;i++){
		yxj[b[i].id]=i;
		if(b[i].rk==0) mx=min(mx,i-1);
	}
	int c1=0;
	sgt2.build(1,1,n);
	for(int i=1;i<=n;i++){
		if(s[i]=='1') c1++,sgt2.add(1,yxj[i],yxj[i],1);
	}
	while(q--){
		cin>>t;
		if(s[t]=='0'){
			s[t]='1';c1++;
			sgt2.add(1,yxj[t],yxj[t],1);
		}
		else{
			s[t]='0';c1--;
			sgt2.add(1,yxj[t],yxj[t],-1);
		}
		cout<<min(c1,mx)-sgt2.query(1,1,min(c1,mx))<<endl;
	}
}
signed main(){
	IOS;TIE;
	T=1;
	while(T--) solve();
	return 0;
}
```



---

## 作者：Flanksy (赞：3)

### 并查集、树状数组、二分、倍增

赛时看到题秒想的做法然而一个半小时都没调出来，笔者很生气所以要写一篇题解。**这个做法代码难度和思维难度都很高。**

晚上十一点调到早晨四点半，感觉自己是大脑缺失的生物。

和大多数做法的不同之处是答案是现算的，不需要从上一个答案转移。

------------

#### 转化到树上

由于 $t(s)$ 是一大堆 $01$ 串起来的，想让字典序最大就要让 $t(s)$ 前边的位尽可能变成 $1$。考虑维护前 $i$ 条线段的并集长度和每次修改后的 $1$ 的个数，贪心填充前 $i$ 条线段。

然后需要快速求出前 $i$ 条线段并中有多少 $1$，还要求出把当前所有 $1$ 全部填到 $t(s)$ 前边需要的最小操作代价，需要支持修改操作。

动态维护 $1$ 的数量可以用树状数组，最小代价有些不好求。由于线段的并很可能是不连续的不方便维护，所以考虑把线段并集拍上树使用 dfs 序化成子树问题处理。

以样例为例，把每个位置作为一个节点，每个线段生成一个新节点，然后连接成树形结构，如果不是第一条线段，还需要连接上一条线段代表的节点。

![Example](https://cdn.luogu.com.cn/upload/image_hosting/7oex8cah.png)

**线段代表的节点只应连接代表上一条线段的节点和加入这条线段后第一次被线段并集包含的位置。**

使用一个并查集维护没有被线段包含的位置，另一个并查集维护树的结构，边合并边建树，从而成功地把序列扔到树上。

------------

#### 处理答案

dfs 一遍，求出每个节点的 dfs 序、子树大小和子树内的叶子数量。

由于 $t(s)$ 字典序最大的状态是形如 $11000$ 的前 $1$ 后 $0$ 的串，而深度较大的叶节点代表的位置在 $t(s)$ 中更靠前，所以它们应当被优先染色（仅帮助理解）。

由于这棵树的性质很好（非叶节点子树代表前缀线段并），对于编号更大的非叶节点，它们子树内的叶节点数量比起编号较小者是单调不降的。

二分求出编号最小的子树叶子数量大于等于全局 $1$ 数量的非叶节点，这个节点所管辖的叶子会被按照深度从大到小换成 $1$，同深度叶节点会被按编号从小到大换成 $1$。换到所有的 $1$ 都被用完为止（本来是 $1$ 就不用换）。

新的问题：**子树不一定会被填满，即使在子树内部，也有可能会把一个位置的 $1$ 换到另一个位置来取得最大字典序，不能简单地用 dfs 序和子树大小解决。**

考虑再维护一个树状数组，所有叶子节点的 dfs 序位置的值为 $1$，其余为 $0$，使用倍增求出全局 $1$ 数量在子树内可以填充到的最大 dfs 序，即最后一个被填充的叶节点的 dfs 序。

然后在维护全局 $1$ 的树状数组内区间查询二分到的线段代表的节点的 dfs 序和倍增出节点代表的 dfs 之间的这段区间，这段区间内的 $1$ 不需要被移动。其他所有的 $1$ 都应当被换到区间内部。

于是全局 $1$ 数量减去这个区间的 $1$ 数量就是答案，而修改操作只需要改动统计全局 $1$ 的树状数组。

最后发现子树大小没用，可以省略。

------------

#### 注意事项

- 并查集和树状数组都使用了多个，最好封装。
- 新增节点至多 $m$ 个，数组应当开大。
- **必须让在 $t(s)$ 中最靠前的位对应的节点 dfs 序最小，建树时每个非叶节点能遍历到的第一个节点应当是上一条线段所代表的节点（如果有），其余节点按照编号从小到大加入。**
- 部分位置没有被任何线段包含，但全局 $1$ 的统计仍然需要计入这些位置，手动分配它们的 dfs 序，否则树状数组会被 $0$ 卡死。这些节点与被覆盖的节点不做区分一同更新。
- 可能会出现 $1$ 的数量多于叶节点数量的情况，此时不能正确统计答案。应当在查询时特判，出现此种情况则输出叶节点数量减去树上值为 $1$ 的叶节点数量。
- **树上值为 $1$ 的叶节点数量需要记录最大有效 dfs 序，由于手动分配了 dfs 序，树状数组有一部分是无效的。**

由于 $n$，$m$，$q$ 同阶，总体时间复杂度 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
struct BIT{//alls 维护所有叶节点位置 ones 维护全局 1 数量与位置 
	int lim,c[400005];
	inline void start(int x){lim=x;}
	void add(int x,int y){
		while(x<=lim) c[x]+=y,x+=x&-x;
	}
	int sum(int x){
		int ret=0;
		while(x) ret+=c[x],x-=x&-x;
		return ret;
	}
	int frank(int x){//倍增找到第一个大于等于 x 的位置 
		int ret=0,sum=0;
		for(int i=1<<18;i;i>>=1) if((ret|i)<=lim&&sum+c[ret|i]<x) sum+=c[ret|=i];
		return ret+1;
	}
}alls,ones;
struct DSU{//leaf 维护未被线段覆盖过的位置 tree 维护树形结构 
	int f[400005];
	void start(int x){iota(f+1,f+x+1,1);}
	int ask(int x){return x==f[x] ? x:f[x]=ask(f[x]);}
	void merge(int x,int y){//合并 x 到 y 所在集合 
		x=ask(x),y=ask(y),f[x]=y;
	}
}leaf,tree;
int n,m,q,cnt,pos,maxpos,a[200005],p[200005],dfn[400005],lea[400005];
vector<int> v[400005];
void dfs(int x){
	lea[x]=(x<=n),dfn[x]=++pos;//统计子树叶节点数量 
	for(int i:v[x]) dfs(i),lea[x]+=lea[i];
}
int query(int x){
	ones.add(dfn[x],a[x] ? -1:1),a[x]^=1;//修改树状数组 
	int l=1,r=m,poi=m,all=ones.sum(pos);//由于 all 计入了所有位置 可能没有任何子树满足要求 
	if(all>lea[cnt]) return lea[cnt]-ones.sum(maxpos);//[1,cnt] 可能不全在树上 需要记录最大有效 dfn
	while(l<=r){
		int mid=(l+r)>>1;
		if(lea[p[mid]]<all) l=mid+1;
		else poi=mid,r=mid-1;//poi:编号最小的符合要求的 非叶节点 
	}
	poi=p[poi],l=dfn[poi],r=alls.frank(alls.sum(l-1)+all);
	return all-ones.sum(r)+ones.sum(l-1);
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>m>>q,cnt=n;
	for(int i=1;i<=n;i++){
		static char x;
		cin>>x,a[i]=x-'0';
	}
	leaf.start(n+1),tree.start(n+m);//注意这个初始化 
	for(int i=1;i<=m;i++){
		static int l,r;
		cin>>l>>r,p[i]=++cnt;//建新节点 直接连单向边 
		if(i>=2) v[cnt].push_back(cnt-1);
		for(int j=leaf.ask(l);j<=r;j=leaf.ask(j+1)){
			v[cnt].push_back(j);
			leaf.merge(j,j+1);
			tree.merge(tree.ask(j),cnt);
		}
	}
	dfs(cnt),maxpos=pos;//注意根节点是指定的 同时需要保存 pos 最大值 
	for(int i=1;i<=n;i++) if(!dfn[i]) dfn[i]=++pos;
	alls.start(pos),ones.start(pos);
	for(int i=1;i<=n;i++) alls.add(dfn[i],1),ones.add(dfn[i],a[i]);
	for(int i=1;i<=q;i++){
		static int x;
		cin>>x;
		cout<<query(x)<<'\n';
	}
	return 0;
}
```

------------

#### 后记

感觉这种把序列问题拍上树的做法很像 kruskal 重构树。

那个树状数组上倍增可以直接换成前缀和加二分的。

~~大脑缺失的生物~~

---

## 作者：ballpoint_pen (赞：2)

给一种不同于官解的做法。

题目要求字典序最大，那么 $t(s)$ 最前面的 1 应尽可能多。考虑给每个数一个排名，排名越靠前代表我们把它变为 1 的优先级越大。记录当前字符串 $s$ 中 1 的个数 $k$，那么只要将排名在 $1-k$ 之间的数全部变为 1，最终的字符串字典序就一定是最大的。

可以暴力地用 set 维护当前还没有排名的节点，对于每个区间，我们不断地在集合中二分出最小的 $\ge l_i$ 的点，如果它越过了右端点说明所有区间内的节点已经有排名了，进行下一个区间的操作；否则将计数器加一，给它赋上排名并将它从集合中删除。

这样就将所有操作挂到了排名中连续的一段上。然后不难发现求将前缀变为 1 的最小步数等于这个前缀中 0 的个数，那么随便用个数据结构维护一下就做完了。

时间复杂度：$O((n+q)\log n)$，比官解慢一点，但是思路应该比较一眼。

[代码](https://codeforces.com/contest/1847/submission/212414858)

---

## 作者：LOVE_Ynoi (赞：2)

## 题目简述

- 给你一个长度为 $n$ 的 $\texttt{01}$ 字符串 $s$ 和 $m$ 个区间 $[l_i,r_i]$。
- 每一个区间都代表 $s$ 的一个子串 $t_i$。
- 定义字符串 $t$ 为 所有的 $t_i$ 按顺次拼接而成的字符串。
- 定义一次操作为交换 $s$ 中的两个字符。  
- 有 $q$ 个询问，每一个询问将 $s$ 中的一个位置取反。  
- 求最少进行多少次操作使得 $t$ 的字典序最大。
- $1 \le n,m,q \le 2 \times 10^5$

## 题目分析

### 如何在不带询问的情况下求出答案
若想使 $t$ 的字典序最大，由于是顺次拼接:  
所以一定先让 $t_1$ 中的所有位交换为 $1$，然后再把 $t_2$ 中所有的位交换为 $1$，以此类推。

例如，$t_1 = [2,3],t_2 = [3,4],t_3 = [4,5]$：  
我们交换为 $1$ 的顺序即为 $2 \to 3 \to 3 \to 4 \to 4 \to 5$。  
考虑到相同的数不需要重复调换，所以最终我们只需要以 $2 \to 3 \to 4$ 的顺序从其他的位置交换 $1$ 即可。  

**记录这个顺序为数组 $a$**，那么**答案**即为满足 $s_{a_i} = \texttt{0}$ 的 $i$ 的个数（即需要被交换的个数）和 $s$ 中 $\texttt{1}$ 的个数中的较小值。

### 优化细节
朴素的处理出数组 $a$ 的时间复杂度显然是 $\sum_{i = 1}^m{(r_i-l_i})$，即 $O(nm)$ 级别。  
考虑如何在较低的时间复杂度内求出 $a$。

我们可以用 **`set`** 来进行求解。  
先把所有的下标插入 `set`，代表还没有覆盖过的下标。  
然后 `lowerbound` $l_i$ 配合迭代器，覆盖一个就从 `set` 里删除一个。  
时间复杂度 $O(n \log n)$。  
**这里有个细节**，就是删除的时候不能直接 `erase`，有迭代器会乱。  
如果无法理解的话，看代码手推一下应该更好理解。

当然，还有线段树倒序推平或者并查集或者珂朵莉树之类的方法，这里不多赘述。

### 考虑询问
一个显然的结论就是对于每一次询问，答案的变化**不会很大**。

可以考虑分类讨论：

1. 如果修改位置在之前已经被覆盖过的话，从 $\texttt{1}$ 改为 $\texttt{0}$ 就答案加 $1$，反之则答案减 $1$。  
2. 如果新增了一个 $\texttt{1}$ 的话，如果还有没覆盖的位置，答案就加 $1$。  
3. 如果新增了一个 $\texttt{0}$ 的话，如果还有没覆盖的位置，说明所有的 $\texttt{1}$ 都被用于覆盖，减少一个 $\texttt{1}$ 对结果有影响，答案减 $1$。

这里在实现上可以考虑把每个下标在 $a$ 里的位置记录一下，然后通过将 $\texttt{1}$ 的个数与 $a$ 的长度作比较即可。

时间复杂度 $O(1)$。

还有可以用树状数组等数据结构维护前缀和的方法，思维难度比较低。

最终总的时间复杂度为 $O(m \log n)$，对于 $2 \times 10^5$ 的数据范围来说绰绰有余。

## 代码
```c++
// cf1857 D
//自己的代码可读性过差，所以借鉴了一下 cf 官方的代码写法
#include <bits/stdc++.h>
using namespace std;
int n, m, q;
string str;
int pos[200010];
int main()
{
    memset(pos, 0x7f, sizeof(pos));
    cin >> n >> m >> q;
    cin >> str;
    int cnt = 0;
    for (int i = 0; i < n; i++)
        if (str[i] == '1')
            cnt++;
    set<int> s;
    for (int i = 0; i < n; i++)
        s.insert(i);
    vector<int> in;
    for (int i = 1; i <= m; i++)
    {
        int l, r;
        cin >> l >> r;
        l--, r--;
        auto it = s.lower_bound(l);
        vector<int> te;
        while (it != s.end() && (*it) <= r)
        {
            te.push_back(*it);
            in.push_back(*it);
            pos[*it] = in.size() - 1;
            it++;
        }
        //注意这里要最后再erase
        for (auto x : te)
            s.erase(x);
    }
    int ans = 0;
    for (int i = 0; i < min(cnt, (int)in.size()); i++)
        if (str[in[i]] == '0')
            ans++;
    while (q--)
    {
        int x;
        cin >> x;
        x--;
        if (pos[x] < cnt) //分类讨论 1
        {
            if (str[x] == '0')
                ans--;
            else
                ans++;
        }
        if (str[x] == '0') //分类讨论 2
        {
            str[x] = '1';
            if (cnt < in.size() && str[in[cnt]] == '0')
                ans++;
            cnt++;
        }
        else //分类讨论 3
        {
            str[x] = '0';
            if (cnt <= in.size() && str[in[cnt - 1]] == '0')
                ans--;
            cnt--;
        }
        cout << ans << endl;
    }
    return 0;
}

```

---

## 作者：kernel_panic (赞：1)

## 思路

先考虑区间不交的情况．

容易观察到，若给出的区间不交，操作后拼接出的串的一定形如若干个 $1$ 拼接上若干个 $0$．

考虑如何计算操作数．由于区间不交，设区间并的大小为 $k$，那么我们可以构造一个置换 $p$，使得 $p$ 作用在原序列上后，新序列的前 $k$ 位恰好对应拼接出的串．再令当前序列中 $1$ 的个数为 $w$，由于新序列中长度为 $\min\{k, w\}$ 的前缀在操作后应当全为 $1$，那么操作次数就是这个前缀中 $0$ 的个数，容易维护．

构造 $p$ 可以依次拼接区间．具体地，我们维护变量 $\mathrm{tp}$，初始为 $0$．然后按照顺序遍历区间，每到一个位置 $i$，先令 $\mathrm{tp}$ 自增，然后将 $p_i$ 赋值为 $\mathrm{tp}$．最后仍未确定的元素可以瞎填，保证 $p$ 仍然是一个置换即可．

考虑将这个做法扩展到区间有交的情况．两区间有交时，需优先保证编号小的区间被填 $1$．那么我们在构造 $p$ 的方式上动一点手脚，不对已经确定的元素赋值，这样构造出的置换作用在原序列上后，新序列的前 $k$ 位恰好对应将编号较大的区间中与编号较小的区间的交去掉后拼接出的串．为了使高位尽可能填 $1$，操作后的新序列长度为 $\min\{k, w\}$ 的前缀也应当全为 $1$．维护答案的方式不变．

这时如果我们暴力构造 $p$，时间复杂度会退化到 $O(n^2)$，所以我们应当只填没有填过的位置．这里有很多实现方式，我使用了一棵线段树．具体地，维护区间内第一个未被填过和被填过的位置，每次找到 $[l, r]$ 内第一个未被填过的位置，记作 $a$，再找到 $[a, r]$ 内第一个被填过的位置，记作 $b$，$[a, b)$ 就是区间 $[l, r]$ 内第一个未被填过的区间，暴力填即可．不断重复这一次操作，时间复杂度 $O(n \log n)$．

## 代码

```cpp
#include <algorithm>
#include <cstdio>

inline int rd() {
	int x = 0, f = 1, c = getchar();
	while (((c - '0') | ('9' - c)) < 0)
		f = c != '-', c = getchar();
	while (((c - '0') | ('9' - c)) > 0)
		x = x * 10 + c - '0', c = getchar();
	return f ? x : -x;
}

const int N = 2e5;

int n, m, q, a[N + 5];

#define lch (p * 2)
#define rch (p * 2 + 1)
#define mid ((t[p].l + t[p].r) / 2)
struct dat {
	int f0, f1;
};
dat operator+(dat a, dat b) {
	dat res;
	if (a.f0 == -1) {
		if (b.f0 == -1) res.f0 = -1;
		else res.f0 = b.f0;
	} else res.f0 = a.f0;
	if (a.f1 == -1) {
		if (b.f1 == -1) res.f1 = -1;
		else res.f1 = b.f1;
	} else res.f1 = a.f1;
	return res;
}
struct node {
	int l, r;
	dat v;
	int tg;
	void upd() {
		v = {-1, l};
		tg = 1;
	}
} t[N * 4 + 5];
void pushup(int p) { t[p].v = t[lch].v + t[rch].v; }
void pushdown(int p) {
	if (!t[p].tg) return;
	t[lch].upd(), t[rch].upd();
	t[p].tg = 0;
}
void build(int p = 1, int cl = 1, int cr = n) {
	t[p].l = cl, t[p].r = cr;
	if (cl == cr) return t[p].v = {cl, -1}, void();
	build(lch, cl, mid), build(rch, mid + 1, cr);
	pushup(p);
}
void upd(int l, int r, int p = 1) {
	if (l > r) return;
	if (t[p].l == l && t[p].r == r) return t[p].upd();
	pushdown(p);
	if (r <= mid) upd(l, r, lch);
	else if (l > mid) upd(l, r, rch);
	else upd(l, mid, lch), upd(mid + 1, r, rch);
	pushup(p);
}
dat que(int l, int r, int p = 1) {
	if (l > r) return {-1, -1};
	if (t[p].l == l && t[p].r == r) return t[p].v;
	pushdown(p);
	if (r <= mid) return que(l, r, lch);
	else if (l > mid) return que(l, r, rch);
	else return que(l, mid, lch) + que(mid + 1, r, rch);
}
#undef lch
#undef rch
#undef mid

namespace fwt {
	int t[N + 5];
	int lowbit(int x) { return x & (-x); }
	void upd(int x, int d) {
		for (int i = x; i <= n; i += lowbit(i)) {
			t[i] += d;
		}
	}
	int que(int x) {
		int res = 0;
		for (int i = x; i >= 1; i -= lowbit(i)) {
			res += t[i];
		}
		return res;
	}
};

int p[N + 5], b[N + 5];

char s[N + 5];
int main() {
	n = rd(), m = rd(), q = rd(), scanf("%s", s + 1);
	for (int i = 1; i <= n; i++) a[i] = s[i] - '0';

	build(); int tp = 0;
	for (int _ = 1; _ <= m; _++) {
		int l = rd(), r = rd(), i = l, j = r;
		while (i <= j) {
			int a = que(i, j).f0; if (a == -1) a = j + 1;
			int b = que(a, j).f1; if (b == -1) b = j + 1;
			for (int k = a; k <= b - 1; k++) p[k] = ++tp;
			i = b + 1;
		}
		upd(l, r);
	}
	int lim = tp;
	for (int i = 1; i <= n; i++) {
		if (!p[i]) p[i] = ++tp;
	}

	for (int i = 1; i <= n; i++) b[p[i]] = a[i];
	for (int i = 1; i <= n; i++) fwt::upd(i, b[i]);

	for (int i = 1; i <= q; i++) {
		int pos = p[rd()]; b[pos] ^= 1;
		b[pos] ? fwt::upd(pos, 1) : fwt::upd(pos, -1);
		int tot = std::min(lim, fwt::que(n));
		int x = tot - fwt::que(tot);
		printf("%d\n", x);
	}
	return 0;
}
```


---

## 作者：FLAMEs_ (赞：1)

无脑做法。~~（哼哼啊啊啊啊啊啊啊啊啊啊啊啊赛时想到正解了没写完啊啊啊啊啊啊啊啊啊）~~

---

考虑拼接而成的字符串中必定有重复的字符，此时我们只关心每个位置在拼接后的字符串**第一次**出现的位置，只有该位置对字典序存在实际上的贡献。

此时有一种无脑做法：离线每个拼接的区间，倒序维护其时间戳（区间推平），即可做到维护一个位置在拼接后的字符串中第一次出现的位置。这个部分可以采用线段树维护区间推平的方法（直接维护一次函数即可）。~~常数大，但是无脑！不好写，但是无脑！~~

考虑字典序最大的时候所有的 $1$ 均在拼接而成的字符串的最左边。记拼接而成的字符串中出现了 $\text{cntF}$ 种不同字符，原来字符串中的 $1$ 个数为 $\text{cnt1}$。当 $\text{cntF}<\text{cnt1}$ 时，我们只需关注前 $\text{cntF}$ 个字符即可；同理，当 $\text{cntF}\ge\text{cnt1}$ 时，我们只需关注前 $\text{cnt1}$ 个字符。综上，我们只需关注前 $\text{min(cnt1,cntF)}$ 个字符便可完成维护。

若要使该字符串字典序最大，则须将所有 $1$ 放到最前面。不难发现前 $\text{min(cnt1,cntF)}$ 个字符中 $0$ 的个数即为需要修改的次数。这步树状数组动态维护前缀和即可做到 $\Theta(\text{q log n})$ 级别的复杂度。

总时间复杂度 $\Theta(\text{(m+q)log n})$，好想，有点难写。

[代码](https://codeforces.com/contest/1847/submission/212489415)

---

## 作者：Rei_Sen (赞：0)

呜呜呜呜，最近铃仙老读错题。

可怜的铃仙把「交换」读成了「邻项交换」，然后被 $1900$ 干碎了。

直观的，我们有个性质：

> 重合部分不会影响拿取 $1$ 的优先级。

这里的优先级指的是指在合并后形成的串 $T$ 中的第一次出现的位置。

所以我们可以直接将有效部分依据优先级映射在一起，然后维护一个树状数组，来统计映射后部分内 $1$ 的个数，最后用 $1$ 的总个数减一下就好了。

现在的关键问题来到了如何快速做完映射，因为如果我们暴力映射的话时间复杂度是一个 $O(mn)$ 的东西。

这里有一个经典的 trick，就是对于这种区间处理，但是只能处理上一次的情况（因为我们只需要映射一次），我们可以考虑维护一个并查集，然后让 $fa$ 指向已染色的右端点，这样我们可以边处理边 `merge`，然后让 $j \gets find(j) + 1$ 直接跳过已处理部分，可以将 $O(mn)$ 优化为 $O(m \log n)$。

**注意，千万不要按秩合并。**

时间复杂度 $O((m+n) \log n)$。

```cpp
string s;
int n, m;

int fa[MAX_SIZE];
int siz[MAX_SIZE];
void init(int qwq) {
	for(int i = 1; i <= qwq; i++){
		fa[i] = i;
		siz[i] = 1;
	}
}

int find(int u){
	if(fa[u] == u) return fa[u];
	return fa[u] = find(fa[u]);
}

void merge(int u, int v) {
	int fu = find(u);
	int fv = find(v);
	fa[fv] = fu;
}

int bit[MAX_SIZE];
void add(int pos, int val) {
	for(int i = pos; i <= n; i += lowbit(i)) {
		bit[i] += val;
	}
}

int ask(int pos) {
	int ans = 0;
	for(int i = pos; i; i -= lowbit(i)) {
		ans += bit[i];
	}
	return ans;
}

int phi[MAX_SIZE];

void main() {
	ios::sync_with_stdio(false);
	int q;
	cin>>n>>m>>q;
	int askers = q;
	cin>>s;
	init(n + 10);
	int priority = 0;
	for(int i = 1; i <= m; i++) {
		int l, r;
		cin>>l>>r;
		int j = l;
		while(j <= r) {
			if(!phi[j])
				phi[j] = ++priority;
			int nxt = find(j) + 1;
			if(nxt <= r) {
				merge(nxt, j);
			}
			j = nxt;
		}
	}
	int totalcnt = 0;
	for(int i = 0; i < n; i++) {
		totalcnt += s[i] - '0';
		if(phi[i + 1]) {
			add(phi[i + 1], s[i] - '0');
		}
	}
	while(askers--){
		int p;
		cin>>p;
		int delta = (s[p - 1] - '0' + 1) & 1;
		if(!delta)
			delta = -1;
		s[p - 1] += delta;
		totalcnt += delta;
		if(phi[p])
			add(phi[p], delta);
		int r = min(priority, totalcnt);
		write(r - ask(r), '\n');
	}
	return void();
}
```

---

## 作者：封禁用户 (赞：0)

如果不带修改，那么可以把题目转化为。给定 $m$ 个区间 $[l,r]$，将 $l \sim r$ 的数添加至一个集合里。最后给这个集合去重。

我们维护一个代表未添加的数的集合。初始时，这个集合大小为值域，即 $n$，元素 $1 \sim n$。

对于每次添加，我们对于这个集合暴力删除。很显然，最多只能卡到每一个数删除一次。对于每次删除的数，把它添加到另一个集合，该集合就是我们求的。

以上过程似乎掏出一个数据结构就能维护。

复杂度 $O(n \log n)$。

处理出这个之后，我们对于每个元素当作下标，给定的那个数组中看是否为 $0$ 来做贡献。

对于修改部分，似乎只需要看看字典序的影响了。上文中做贡献的部分，显然 $1 \to 0$ 时贡献增加，反之减少。对于没有覆盖的部分，还是要字典序最大，把 $1$ 堆过去即可，$1 \to 0$ 则连续 $1$ 段减少贡献，反之同理。这里注意一下，如果本身是 $1$，就无法贡献。

复杂度 $O(1)$。

---

## 作者：ProzacPainkiller (赞：0)

给一个树状数组加二分的解法。

首先考虑优先级，用一个树状数组 `lctr` 维护从 $1$ 到查询位置有多少个数。添加一段时，就可以用二分来找到第一个空缺的位置，填完每段第一个连续的空缺的优先级后，又二分寻找第二个，直到找完。时间复杂度为 $\mathcal{O}((n+m)\log^2 n)$。

而第二个树状数组 `bit` 维护的是拥有从 $1$ 到查询的优先级的位置的 $1$ 的数量。也是代码中 `oa` 数组的前缀和。

另外我们还要维护 `tot1` 和 `unused` 两个变量，分别代表字符串中 $1$ 的总数和字符串中在交换之前没被用到的 $1$ 的数量，为之后的询问做准备。

首先每次询问先取反，维护 `bit` 和其外几个变量。

然后二分求出优先级最小的一个 $1$ 的位置，然后求出优先级比他大的 $0$ 的数量，就是预计要填的空，所以将其命名为 `kong`。

如果 `unused` 大于等于 `kong` 那么答案就是 `unused` 和会被用到的位置上 $0$ 中的数量之中的最小值。具体来说，就是将不会用到的 $1$ 来填补要用到的 $0$。

而当 `unused` 小于 `kong` 时，答案则是 `kong` 和优先级小于等于 `tot1` 的位置上 $0$ 的数量之中的最小值。具体来说，就是将不会用到的 $1$ 全部来填补要用到的 $0$，然后再用优先级较小的 $1$ 来填补优先级较大的 $0$。

所有询问操作的时间复杂度是 $\mathcal{O}(q\log^2 n)$。而整个程序的时间复杂度是 $\mathcal{O}((n+m+q)\log^2 n)$。虽然理论复杂度比较大，但是还是只用了 311ms。

```
#include<bits/stdc++.h>
#define lowbit(x)	(x&-x)
using namespace std;
const int N=2e5+5;
int n,m,q;
bool geted[N],oa[N];
int order[N],unused;
string s;
struct BIT
{
	int t[N];
	BIT()
	{
		memset(t,0,sizeof(t));
	}
	void update(int x,int ad)
	{
		while(x<=n)
		{
			t[x]+=ad;
			x+=lowbit(x);
		}
	}
	int query(int x)
	{
		int ret=0;
		while(x)
		{
			ret+=t[x];
			x-=lowbit(x);
		}
		return ret;
	}
}bit,lctr;
int locate(int l,int r)
{
	int ans=-1,mid;
	while(l<=r)
	{
		mid=l+r>>1;
		if(lctr.query(mid)-lctr.query(l-1)<mid-l+1)
		{
			ans=mid;
			r=mid-1;
		}
		else	l=mid+1;
	}
	return ans;
}
int get_kong(int x)
{
	int ans=x,mid,l=0,r=x;
	while(l<=r)
	{
		mid=l+r>>1;
		if(bit.query(mid)==bit.query(x))
		{
			ans=mid;
			r=mid-1;
		}
		else	l=mid+1;
	}
	return ans-bit.query(ans);
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>n>>m>>q>>s;
	int ortot=0;
	for(int i=0,a,b;i<m;++i)
	{
		cin>>a>>b;
		a=locate(a,b);
		while(a!=-1)
		{
			while(a<=b&&!geted[a])
			{
				geted[a]=1;
				order[a]=++ortot;
				lctr.update(a,1);
				++a;
			}
			if(a>b)	break;
			a=locate(a,b);
		}
	}
	int tot1=0;
	for(int i=1;i<=n;++i)
		if(s[i-1]=='1')
		{
			++tot1;
			oa[i]=1;
			if(order[i])	bit.update(order[i],1);
			else	++unused;
		}
	for(int i=0,qq;i<q;++i)
	{
		cin>>qq;
		if(oa[qq])
		{
			oa[qq]=0;
			if(order[qq])	bit.update(order[qq],-1);
			else	--unused;
			--tot1;
		}
		else
		{
			oa[qq]=1;
			if(order[qq])	bit.update(order[qq],1);
			else	++unused;
			++tot1;
		}
		int kong=get_kong(ortot);
		if(unused>=kong)	cout<<min(unused,ortot-bit.query(ortot))<<'\n';
		else	cout<<min(kong,tot1-bit.query(tot1))<<'\n';
	}
	return 0;
}
```

---

## 作者：Leonid (赞：0)

数据结构学傻了，赛时调了好久。

首先他从原字符串中要提出 $m$ 个子串合并，通过交换操作使字典序最大，那么我们可以处理出原字符串中每个字符的优先级。我们将处理出来的优先级拼接起来作为字符串 $p$。

直接扫一遍是平方级别的，用线段树标记打过的 $tag$ 并跳过可以优化到 $O(n\log n)$。

接下来就是计算操作次数。容易发现把 $s$ 中的所有 $1$ 放在 $p$ 的开头位置即可，换句话说就是拿 $1$ 的个数 $cnt$ 去补在 $p$ 的开头。所以我们只要维护 $cnt$ 的值和 $p$ 中 $[1,cnt]$ 中 $0$ 的个数即可，因为我在 $[1,cnt]$ 中的 $0$ 总能找到后面的 $1$ 予以补之。

注意 $cnt$ 可能大于 $p$ 长度，所以线段树的上界要 $\min(cnt,tot)$，$tot$ 代指 $p$ 长度。

那么后面显然是一个单点修改和区间加，用线段树维护即可。

复杂度 $O((n+q) \log n$)。

```cpp
#include<bits/stdc++.h>

using namespace std;

#define ll long long
#define ull unsigned long long

#define M 800005
#define mod 998244353
#define inf 1e9

int n,m,q;
int s[M];
int l[M],r[M];
int fst[M],tot; // 优先级顺序，影响答案的元素个数
int mp[M]; // 优先级映射

struct segment_tree{ // 线段树模板
	int sum[M],tag[M];
	
	#define ls p<<1
	#define rs ls|1
	
	void build(){
		memset(tag,-1,sizeof tag);
	}
	
	void push_up(int p){
		sum[p]=sum[ls]+sum[rs];
	}
	
	void push_down(int p,int l,int r){
		if(!~tag[p]) return;
		int mid=(l+r)>>1;
		tag[ls]=tag[rs]=tag[p];
		sum[ls]=(mid-l+1)*tag[p];
		sum[rs]=(r-mid)*tag[p];
		tag[p]=-1;
	}
	
	void update(int p,int l,int r,int L,int R,int x){
		if(l<=L&&R<=r){
			tag[p]=x;
			sum[p]=(R-L+1)*x;
			return;
		}
		push_down(p,L,R);
		int mid=(L+R)>>1;
		if(l<=mid) update(ls,l,r,L,mid,x);
		if(r>mid) update(rs,l,r,mid+1,R,x);
		push_up(p);
	}
	
	void makefst(int p,int l,int r,int L,int R){ // 线段树优化优先级处理
		if(L>R) return; // 记得加这步，不然会递归死循环 RE
		if(sum[p]==(R-L+1)) return;
		if(l<=L&&R<=r&&!sum[p]){ 
			for(int i=L;i<=R;++i) fst[++tot]=i;
			return;
		} // 如果当前区间全部没有打过 tag 直接暴力，这样每个点只会被扫过 1 次
		push_down(p,L,R);
		int mid=(L+R)>>1;
		if(l<=mid) makefst(ls,l,r,L,mid);
		if(r>mid) makefst(rs,l,r,mid+1,R);
	}
	
	int query(int p,int l,int r,int L,int R){
		if(l<=L&&R<=r) return sum[p];
		push_down(p,L,R);
		int mid=(L+R)>>1,res=0;
		if(l<=mid) res+=query(ls,l,r,L,mid);
		if(r>mid) res+=query(rs,l,r,mid+1,R);
		return res;
	}
}t,t1; // 处理优先级的线段树，维护

int main(){
	scanf("%d %d %d",&n,&m,&q);
	int cnt=0;
	for(int i=1;i<=n;++i) scanf("%1d",&s[i]),cnt+=s[i];
	t.build();
	for(int i=1;i<=m;++i){
		scanf("%d %d",&l[i],&r[i]);
		t.makefst(1,l[i],r[i],1,n);
		t.update(1,l[i],r[i],1,n,1);
	} // 因为每个点只会扫过一次，加上线段树的 log，均摊复杂度便是 O(n log n)
	for(int i=1;i<=tot;++i) mp[fst[i]]=i;
	t1.build();
	for(int i=1;i<=tot;++i) t1.update(1,i,i,1,tot,s[fst[i]]);
//	for(int i=1;i<=tot;++i) printf("%d ",fst[i]); printf("\n");
	while(q--){
		int x;
		scanf("%d",&x);
		cnt-=(s[x]-(s[x]^1));
		s[x]^=1;
		if(mp[x]) t1.update(1,mp[x],mp[x],1,tot,s[x]);
//		printf("qwq ");
		if(cnt==0) printf("0\n"); // 记得判 cnt=0 的情况，直接做会 RE
		else printf("%d\n",min(cnt,tot)-t1.query(1,1,min(cnt,tot),1,tot)); // 需要填的长度减去 1 的个数就是 0 的个数
	}
	return 0;
}
```


---

