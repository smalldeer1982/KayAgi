# Chino的树学

## 题目背景

Chino非常喜欢树

## 题目描述

Chino树是一棵具有某种性质的满二叉树，具体来说，对于这棵树的每一个非叶子节点，它的左子节点$(A)$的右子节点$(C)$与它的右子节点$(B)$的左子节点$(D)$的值相同，且$C$与$D$下方的子树也完全相同。现在，Chino想知道，要如何从根节点走到其中任意叶节点使路上经过的节点的权值之和最大。

![](https://cdn.luogu.com.cn/upload/pic/23672.png )

$Orz yky,dyh,wjk,jjy,cxr,gsy,cpy,zcy,tyz,yy,hz,zhr,ygg$

## 说明/提示

![](https://cdn.luogu.com.cn/upload/pic/23674.png )
![](https://cdn.luogu.com.cn/upload/pic/23675.png )
![](https://cdn.luogu.com.cn/upload/pic/23673.png )
答案longlong救星

## 样例 #1

### 输入

```
3
6 17 43 55 20 55 38```

### 输出

```
81```

## 样例 #2

### 输入

```
4
6 20 72 61 26 55 26 7 17 55 26 7 38 7 35```

### 输出

```
159```

# 题解

## 作者：Pisces (赞：17)

这题真的太水了,直接递归输入都不会被卡掉

然后直接暴力取最大值即可

$Code$:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read(){//快读
	int X=0;bool d=0;char ch=0;
	while(!isdigit(ch)) d|=ch=='-',ch=getchar();
	while(isdigit(ch)) X=(X<<3)+(X<<1)+(ch^48),ch=getchar();
	return d?-X:X;
}
short n=read();
int dfs(int x,short dep){
	if(dep==n) return read();//输入完毕,退出递归
	return read()+max(dfs(x<<1,dep+1),dfs(x<<1|1,dep+1));//取最大
}
signed main(){
	cout<<dfs(1,1);
	return 0;
}
```

---

## 作者：ZnHF (赞：3)

[题目链接](https://www.luogu.com.cn/problem/P5551)
### 题意简述
给出一棵树的先序遍历，求从根节点开始走到叶子节点的点权和的最大值。
### 题目分析
本题可以使用 dfs 解决。需要注意在建树时应根据先序遍历的特性写出代码，即先输入节点的权值，再递归地输入该节点的左右子节点的权值。

注意，一棵层数为 $n$ 的满二叉树一共有 $2^n-1$ 个节点。时间限制卡得比较紧，可以使用快读和位运算优化。
### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read() {//快读
	int x = 0, f = 0;
	char c = getchar();
	while (c < '0' || c > '9') { if (c == '-') f |= 1; c = getchar(); }
	while (c >= '0' && c <= '9') { x = (x<<3)+(x<<1)+(c^48); c = getchar(); }
	return f ? -x : x;
}
int n,t[16777220];
long long ans=-1;
void build(int p){
	if(p<=n){
		t[p]=read();
		build(p<<1);
		build((p<<1)|1);
	}
}
void dfs(int p,long long sum){
	if(p<=n){
		dfs(p<<1,sum+t[p]);
		ans=max(sum+t[p],ans);
		dfs((p<<1)|1,sum+t[p]);
		ans=max(sum+t[p],ans);
	}
}
int main(){
	n=read();
	n=pow(2,n)-1;
	build(1);
	dfs(1,0);
	cout<<ans;
	return 0;
}
```
感谢审核志愿者 @蒟酱 指出错误！

---

## 作者：Lian_zy (赞：2)

## 1 分析
看一眼题目，大致意思就是给你一棵树，求从根节点走到叶子结点所经过节点权值和的最大值。

看了一眼数据范围，$n \le 24$，还是很小的。所以直接暴力 dfs 求最大就可以了，注意需要快读，不然会被出题人卡到 TLE。

## 2 输入
这题输入的是前序遍历，所以我们可以使用递归来进行输入。

节点 $u$ 的左子节点为 $u \times 2$，右子节点为 $u \times 2 + 1$。

``` cpp
void read_tree(int u) {
	if (u > n) return ; //边界条件 
	tree[u] = read(); 
	read_tree(u << 1); //左子节点 2u 
	read_tree(u << 1 | 1); //右子节点 2u+1 
	return ;
}
```

## 3 处理/输出
只需要稍微改一下输入就可以了。

注意不开 `long long` 见祖宗。

``` cpp
void dfs(int u, long long sum) {
	if (u > n) return ; //边界条件 
	maxs = max(maxs, sum + tree[u]);
	dfs(u << 1, sum + tree[u]); //左子节点 2u 
	dfs(u << 1 | 1, sum + tree[u]); //右子节点 2u+1 
	return ;
}
```

最后输出的是 `maxs`。

## 4 完整代码

如果你还是不会写，那么就照着注释自己理解一下吧。

~~莫抄袭，没了AC记录，空悲切。~~
``` cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 1 << 24;
long long maxs;
int n, tree[maxn];
int read() { //不加快读见祖宗 
   int X = 0, w = 1;
   char c = getchar();
    while (c < '0' || c > '9') {
		if (c == '-') w = -1; 
		c = getchar(); 
	}
    while (c >= '0' && c <= '9') X = (X << 3) + (X << 1) + c - '0', c = getchar();
    return X * w;
}
void write(int x) { //快输，可不加 
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) write(x / 10);
	putchar((x % 10) + 48);
	return ;
} 
void read_tree(int u) {
	if (u > n) return ; //边界条件 
	tree[u] = read(); 
	read_tree(u << 1); //左子节点 2u 
	read_tree(u << 1 | 1); //右子节点 2u+1 
	return ;
}
//u表示当前访问的节点，sum表示当前累加的和 
void dfs(int u, long long sum) {
	if (u > n) return ; //边界条件 
	maxs = max(maxs, sum + tree[u]);
	dfs(u << 1, sum + tree[u]); //左子节点 2u 
	dfs(u << 1 | 1, sum + tree[u]); //右子节点 2u+1 
	return ;
}
int main() {
	n = (1 << read()) - 1; //一共2^n-1个节点 
	read_tree(1);
	dfs(1, 0);
	write(maxs);
	return 0;
}
```

## 5 废话
在最后的最后，我发现 `read_tree` 函数和 `dfs` 函数可以合并到一起。

拿小号交了下，[AC了](https://www.luogu.com.cn/record/136414585)。
``` cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 1 << 24;
long long maxs;
int n, tree[maxn];
int read() {
   int X = 0, w = 1;
   char c = getchar();
    while (c < '0' || c > '9') {
		if (c == '-') w = -1; 
		c = getchar(); 
	}
    while (c >= '0' && c <= '9') X = (X << 3) + (X << 1) + c - '0', c = getchar();
    return X * w;
}
void write(int x) {
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) write(x / 10);
	putchar((x % 10) + 48);
	return ;
} 
void dfs(int u, long long sum) {
	if (u > n) return ;
	tree[u] = read();
	maxs = max(maxs, sum + tree[u]);
	dfs(u << 1, sum + tree[u]);
	dfs(u << 1 | 1, sum + tree[u]);
	return ;
}
int main() {
	n = (1 << read()) - 1;
	dfs(1, 0);
	write(maxs);
	return 0;
}
```

---

## 作者：2018ljw (赞：2)

Update：简化冗余描述，辛苦管理大大了。

提供一种非暴力做法，不加优化也可过。

对于一颗二叉树，比较常见的存树如下：对于每一个非叶节点 $x$，记其左右子节点编号分别为  $x \times 2$ 和 $x \times 2+1$。

性质翻译：假设当前节点编号为 $x$，那么节点 $x \times 4+1$ 的子树与节点 $x \times 4+2$ 的子树完全相同。

首先有一个比较明显的想法。设 $f_i$ 表示以 $i$ 为根的子树，根节点到叶子节点的最长路；$val_i$ 表示节点 $i$ 的权值，则有递推式 $f_i=\max(f_{i \times 2},f_{i \times 2+1})+val_i$。特别地，对于叶子结点，$f_i=val_i$。

显然，相同的树答案相同，根据性质有 $f_{x \times 4+1}=f_{x \times 4 +2}$。

考虑什么样的节点值相同。

假设 $x$ 的二进制为 $10\dots 01$，可得 $x \times 4 +1$ 的二进制表示法为 $10\dots 01\color{red}01$，$x \times 4 +2$ 的二进制表示法为 $10\dots 01\color{red}10$。

显然，我们只是在原二进制串后分别填上了 $01$ 和 $10$，相比原串都只多了 一个 $1$。因此，它们含有的 $1$ 的个数相同。

结论：**同一层内，若两个节点的编号二进制含有相同个数的 1，那么这两棵子树的 $f_i$ 相同。**

有了这个结论，我们就可以很快得到一个剪枝：类似记忆化搜索，对于每个节点编号，处理出深度和 $1$ 的个数。那么当我们重复遇到这两个值相同的节点时，我们直接返回答案即可。而这两个东西都是可以从上一层信息推下来的，可以直接在搜索过程中求出。

- 注意剪完枝后把没读完的数据读完。

总复杂度 $O(n^2+2^n)$，瓶颈在于大量的无效输入。

代码如下，无任何优化可过。

```cpp
#include<cstdio>
#define max(x,y) (x>y?x:y)
int n;
long long ans[3001][3001];
//第i层，二进制表示法下有j个1时的答案。
bool vis[3001][3001];
long long power[64];
//预处理 2 的幂次，负责计算没读完的数据个数。
long long dfs(int dep,int cnt){
	//cnt 即为二进制下当前节点含有 1 的个数
	int k;
	scanf("%d",&k);
	if(vis[dep][cnt]){
		//相同的子树已经被搜过，直接剪枝
		int unread=power[n-dep+1]-2;
		while(unread--)scanf("%d",&k);
		return ans[dep][cnt];
	}
	vis[dep][cnt]=1;
	if(dep!=n){
		long long res1=dfs(dep+1,cnt);
        	//左子节点，个数不变
		long long res2=dfs(dep+1,cnt+1);
        	//右子节点，个数 +1
		ans[dep][cnt]=k+max(res1,res2);
	}
	else ans[dep][cnt]=k;
	return ans[dep][cnt];
}
int main(){
	int i;
	scanf("%d",&n);
	power[0]=1;
	for(i=1;i<=n;i++)power[i]=power[i-1]*2;
	printf("%lld",dfs(1,1));
}
```

---

## 作者：Nempt (赞：2)

刚学完二叉树来做这道题可真是舒服啊，虽然还是WA了6发QAQ

简单分析一下这道题，我们可以把它拆分成几个模块来设计：

首先，**建树**，这里采用的储存方式是数组，递归输入构建二叉树

其次，**读入**，这里的数据多到恶心，就连scanf都TLE了QWQ，写一个快读函数（熟练的基础上建议背下来）

再次，**树上DFS**。从根节点出发，递归求出左子树的最大权值，更新最大值；再递归求出右子树的最大权值，更新最大值。

最后，**主函数**就是上面几个模块的组合。

上代码解释：

```cpp
#include<bits/stdc++.h>
#define MAX 16777218  //2^24-1大概就是这个值了，这里不想开太多防爆
using namespace std;
typedef long long ll;
inline int read(){    //快读函数
    int X=0;bool d=0;char ch=0;
    while(!isdigit(ch)) d|=ch=='-',ch=getchar();
    while(isdigit(ch)) X=(X<<3)+(X<<1)+(ch^48),ch=getchar();
    return d?-X:X;
}
int a[MAX];
ll n;
ll ans = -1e9;        //保险起见，ans用ll类型储存
ll A(int c) {         //A函数求解返回2^n-1
    ll s = 1;
    while(c--) s = s << 1;
    return (ll)(s-1);
}
void build(ll pos) {
    if(pos<=n) {      //保证在不越界的基础上递归输入
        a[pos] = read();
        build(pos<<1);      //递归输入左子树
        build((pos<<1)|1);  //递归输入右子树
    }
}
void dfs(ll pos,ll sum) {
    if(pos<=n) {
        dfs(pos<<1,sum+a[pos]);     //递归查找左子树最大值
        ans = max(ans,sum+a[pos]);  //更新最大值
        dfs((pos<<1)|1,sum+a[pos]); //递归查找右子树最大值
        ans = max(ans,sum+a[pos]);  //更新最大值
    }
}
int main() {
    cin>>n;
    n = A(n);
    build(1);  //从根节点开始建树
    dfs(1,0);  //从根节点开始DFS
    cout<<ans<<endl;
    return 0;
}

```

这道题为不TLE白费周折，首先改了输入方式，从**cin变成scanf**；然后是**位运算**，用pos<<1代替pos*2，用pos<<1|1代替pos*2+1；最后看了一下楼上大佬的题解，用了**快读函数**，终于AC了。

之前其实也碰到过快读，但那个时候没太留意，今天，这告诉我们一些经典的东西还是要铭记在心的。

---

## 作者：luozhichen (赞：0)

题目意思：

给出一颗二叉树的先序遍历，规划一条路径，使得路径上经过的结点的权值之和最大。哇塞，这不简单？直接暴力 DP 即可。

思路：

你可以发现，一个节点以及它的子树加起来的最大的情况就两种，第一种就是自己加上他的右子树的最大值，第二种就是加上左子树的最大值。所以代码就出来了。（这题竟然没标签！！！建议管理加个贪心和 DP 的标签）

代码：

**最重要的部分：**

```cpp
inline int max(int a,int b){
	return a > b ? a : b;
}
int dfs(int dep){
	if(dep > n){
		return 0;
	}
	dep++;
	int w;
	read(w);
	return w + max(dfs(dep),dfs(dep));
}
int main(){
	read(n);
	write(dfs(1));
	return 0;
}
```

---

## 作者：_lfxxx_ (赞：0)

UPD：修改笔误。
### 题意：
给出一颗二叉树的先序遍历，规划一条路径，使得路径上经过的结点的权值之和最大。

------------
一道入门树上 DP 题。
### 思路：
设节点 $i$ 的权值为 $w_i$，左儿子为 $l_i$，右儿子为 $r_i$，以节点 $i$ 为根的树的最大权值和为 $f_i$。

显然，对于任意一个非叶子节点 $i$，都有 $f_i=w_i+\max(w_{l_i},w_{r_i})$。

再根据先序遍历的根和儿子的遍历顺序，我们就可以解决这道题了。

------------
虽然题目推荐我们开 `long long`，但通过实测，不开 `long long` 开 `int` 也可以 AC。
### 核心代码：
很简短。
```cpp
int dfs(int depth){
	int	res;
	read(res);
	return ++depth>n?res:res+max(dfs(depth),dfs(depth));//超过层数就不再往下了。
}
int main(){
	read(n);
	write(dfs(1));
	return 0;
}
```

---

## 作者：Provicy (赞：0)

这题还是不难的一个关于树的题。

看到这题数据，显然就是一个边读边操作的题。我们看到它的输入顺序是这棵树的先序遍历，那么我们就想去求这个结点的深度，这样就可以记录到每一层的最大点权和。

 因为本人水平太低，模拟推这个求结点深度的方法花了10多分钟。就是记录当前深度的结点已经出现多少个，如果不到2，那么我们看看这个结点的深度是不是第n层。如果是，就把第n层的结点数+1；如果不是，则当前深度的结点数+1，并且把深度+1。

 记录结束之后，返回去推一下当前深度的结点是否有2个，如果满足条件，就把当前深度的结点数清零，然后判断上一层，直到当前深度结点不是两个为止。

这样，当我们每输入一个结点的点权值时，就能快速推出这个结点的深度了。推出了深度，则求点权和最大值就很容易了。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=110;
ll n,deep=1;
ll p[N],dp[N],ans;
inline ll read()
{
    ll s=0,w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')
            w=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9') 
        s=s*10+ch-'0',ch=getchar();
    return s*w;
}
inline void write(ll x)
{
    if(x<0) 
        putchar('-'),x=-x;
    if(x>9) 
        write(x/10);
    putchar(x%10+'0');
}
void Solve()//求出先序遍历的编号的深度 
{
    n=read();
    for(ll i=1;i<(long long)pow(2ll,n);i++)
    {
        printf("%d %d\n",i,deep);
        if(p[deep]<2)
        {
            if(deep==n)
                p[deep]++;
            else
                p[deep]++,deep++;
        }
        while(p[deep]==2)
            p[deep]=0,deep--;
    }
}
ll ksc()
{
    ll ans=1;
    ll p=n,k=2;
    while(p)
    {
        if(p&1)
            ans=ans*k;
        k=k*k;
        p>>=1;
    }
    return ans;
}
int main()
{
    //Solve();
    n=read();
    ll u=ksc();
    for(ll i=1;i<u;i++)
    {
        ll x;
        x=read();
        dp[deep]=dp[deep-1]+x;//求到这个结点的点权值，比赛时我就是这里脑残了，写成了dp[deep]=max(dp[deep-1]+x,dp[deep]);而且样例还都过了。。。
        if(deep==n)//深度为n就记最大点权和
            ans=max(ans,dp[deep]);
        if(p[deep]<2)
        {
            if(deep==n)
                p[deep]++;
            else
                p[deep]++,deep++;
        }
        while(p[deep]==2)
            p[deep]=0,deep--;
    }
    printf("%lld\n",ans);
    return 0;
}
```
## 

---

## 作者：FjswYuzu (赞：0)

Chino的题其实挺有意思的

首先我们写一个暴力出来，也就是类似于数字三角形的一个dp思路，也就是这个节点的dp值应该是自己的两个子树的最大值再加上自己节点的值

代码如下

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
struct node{
	int depth,value,lchi,rchi;
}a[16777216];
int n;
void dfs(int where,int depth)
{
	a[where].depth=depth;
	int x;
	scanf("%d",&x);
	a[where].value=x;
	if(depth==n)	return ;
	a[where].lchi=where<<1;
	a[where].rchi=where<<1|1;
	dfs(where<<1,depth+1);
	dfs(where<<1|1,depth+1);
}
void init(){
	scanf("%d",&n);
	dfs(1,1);
}
int dp(int where){
	return a[where].value+max(dp(a[where].lchi),dp(a[where].rchi));
}
int main(){
	init();
	printf("%d",dp(1));
	return 0;
}
```

因为这样的代码实在是太暴力了，所以全部MLE了

Tip:当然现在我们已经可以发现我们和另外一篇题解的代码很相像了，其实只需要边读边计算就可以过了。当然要加快读，不然会T1个点

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<queue>
using namespace std;
void read(int &t)
{
	t=0;
	char c=getchar();
	while(c<'0' || c>'9')	c=getchar();
	while(c>='0' && c<='9')	t=(t<<1)+(t<<3)+(c^'0'),c=getchar();
}
int n;
int dfs(int node,int depth)
{
	int x;
	read(x);
	if(depth==n)	return x;
	return x+max(dfs(node<<1,depth+1),dfs(node<<1|1,depth+1));
}
int main(){
	read(n);
	printf("%d",dfs(1,1));
	return 0;
}
```

我们考虑优化，里面有一个性质，也就是这棵树是一颗`Chino树`

> Chino树是一棵具有某种性质的满二叉树，具体来说，对于这棵树的每一个非叶子节点，它的左子节点(A)(A)的右子节点(C)(C)与它的右子节点(B)(B)的左子节点(D)(D)的值相同，且CC与DD下方的子树也完全相同。

这是题目描述中的话，这样我们可以通过这个性质进行优化，也就是搜到一个节点的时候，枚举三个子树（最左边的，最右边的，中间两个是相同的）然后我们就可以节省空间与时间了

当然我太弱啦，所以说我不会。。。

然后这道题就被切掉啦

---

## 作者：Genius_Star (赞：0)

### 题目意思：

给出一颗二叉树的先序遍历，规划一条路径，使得路径上经过的结点的权值之和最大。

哇塞，这不简单？直接暴力 DP 即可。

### 思路：

你可以发现，一个节点以及它的子树加起来的最大的情况就两种，第一种就是自己加上他的右子树的最大值，第二种就是加上左子树的最大值。

所以代码就出来了。

### 核心代码：
```cpp
inline int max(int a,int b){
	return a > b ? a : b;
}
int dfs(int dep){
	if(dep > n){
		return 0;
	}
	dep++;
	int w;
	read(w);
	return w + max(dfs(dep),dfs(dep));
}
int main(){
	read(n);
	write(dfs(1));
	return 0;
}
```


---

