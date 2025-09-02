# [NWRRC 2021] Letters Q and F

## 题目描述

小 Lev 正在学习如何绘制字母 $\tt{Q}$ 和 $\tt{F}$。最初，他有一个 $n \times m$ 的白色网格。然后他会在网格上绘制若干个如下两种形状之一的字母：

![](https://cdn.luogu.com.cn/upload/image_hosting/nmufwv6b.png)

Lev 不会旋转或翻转这两种形状。每次绘制新字母时，他会选择网格中的一个位置，并将该形状的所有格子涂黑。Lev 只会在所有要涂黑的格子都是白色的情况下绘制字母——也就是说，他不会重复涂黑同一个格子。

现在给出网格的最终涂色状态。请你统计 Lev 绘制了多少个字母 $\tt{Q}$ 和多少个字母 $\tt{F}$。

## 说明/提示

第四个样例的示意图如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/xurousuy.png)

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5 3
###
#.#
###
..#
..#```

### 输出

```
1 0```

## 样例 #2

### 输入

```
5 3
###
#..
##.
#..
#..```

### 输出

```
0 1```

## 样例 #3

### 输入

```
5 8
###..###
#.#..#..
###..##.
..#..#..
..#..#..```

### 输出

```
1 1```

## 样例 #4

### 输入

```
8 8
.....###
###..#.#
#.######
###.####
#.###.##
#.#.###.
..#...#.
......#.```

### 输出

```
2 2```

# 题解

## 作者：WuMin4 (赞：1)

## 思路

不旋转不翻转地放置有很多好的性质。 我们考虑每次找整个网格最下面的方块，显然这个方块只可能是 `F` 最下面的方块或 `q` 最下面的方块。

经过一定的~~枚举~~，可以发现当最下面的方块**可以作为 `q` 的一部分时**，它一定属于 `q`，否则为 `F`。

可以尝试构造在 `F` 旁边添加字母使得这个方块既可以作为 `F` 又可以作为 `q` 的一部分的情况，虽然可以构造出来，但会出现在该方块下面的方块，显然会先被消除，但却可以构造出 `q` 旁边添加字母后既可以作为 `q` 又可以作为 `F` 的一部分的情况（比如 ![](https://cdn.luogu.com.cn/upload/image_hosting/1i7cjgjp.png)，红色方块可以作为 `q` 或 `F` 的一部分），这也就印证了上面的结论是正确的。

坐标可以使用 `set` 存储，每次找到最下面的方块判断消除。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,fc,qc;
int F[8][2]={{-4,0},{-4,1},{-4,2},{-3,0},{-2,0},{-2,1},{-1,0},{0,0}};
int Q[10][2]={{-4,-2},{-4,-1},{-4,0},{-3,-2},{-3,0},{-2,-2},{-2,-1},{-2,0},{-1,0},{0,0}};
char mp[305][305];
set<pair<int,int>> s;
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>mp[i][j];
			if(mp[i][j]=='#')
				s.insert({i,j});
		}
	}
	while(!s.empty()){
		int x=prev(s.end())->first,y=prev(s.end())->second;
		bool flag=0;
		for(int i=0;i<10;i++){
			if(!s.count({x+Q[i][0],y+Q[i][1]})){
				flag=1;
				break;
			}
		}
		if(!flag){
			qc++;
			for(int i=0;i<10;i++)
				s.erase({x+Q[i][0],y+Q[i][1]});
		}
		else{
			fc++;
			for(int i=0;i<8;i++)
				s.erase({x+F[i][0],y+F[i][1]});
		}
	}
	cout<<qc<<" "<<fc;
	return 0;
}
```

---

## 作者：tallnut (赞：1)

~~我也不知道我为啥要发电过来写题解。~~
# 思路
观察一下 `Q` 和 `F` 的区别，发现一种判断它们的方式是**取它们最靠左的一列，如果只有连续 $3$ 个字母就是 `F`，否则是 `Q`。**

但是还有问题。如果出现下面的情况：（数字 $1$ 组成左下的 `F`，$2$ 组成右上的 `Q`）

![](https://cdn.luogu.com.cn/upload/image_hosting/sduzfmnb.png)

当你对 `Q` 进行判断时，下面的 `F` 中的字符占用了位置，产生了连续 $>3$ 个字符，导致判断错误。因此我们需要一个合适的顺序处理这些字符。

做过这类题的人应该很快想到：**先从左到右，再从上到下，找第一个有字符的点，判断后将整个字母擦掉。**

凭啥这样是对的？需要一点观察：`Q` 和 `F` 的“大小”（更严谨地说，是最小的包含它们的矩形的尺寸）一样。当扫到一个点时，在它左边和正上方的所有字符都被擦掉了，同时因为 `Q` 和 `F` 尺寸一样，不会出现一个小字母藏在大字母下面的情况，所以能准确判断。

怎么维护这个过程？因为“最靠左的有字符的列”这个东西是在过程中单调不减的，直接指针做。下面证明直接这样的复杂度是 $\Theta(nm)$ 的：

::::info[证明]
每个空字符最多被跳过一次，所以维护开头字符指针是 $\Theta(nm)$。每次擦除显然 $\Theta(1)$，而每个字母都会占用好几个空间，显然整张图中总字母的数量是 $O(nm)$ 的。因此总复杂度 $\Theta(nm)+\Theta(1)\times O(nm)=\Theta(nm)$，证毕。

不明白这题数据范围为啥这么小，是不是想让三次方通过。~~强烈不支持，复杂度比标算劣一只 $\log$ 以上的都应该被卡爆。~~
::::

个人认为这种方式比现在题解区另外一篇好想。
# AC 代码
tallnut 在此题中使用了~~非常牛叉的~~数据结构线段树，成功使代码难写 ??? 倍并使复杂度劣化至 $\Theta(nm\log(nm))$，这才是真的数据结构学傻了。

[AC 链接](https://www.luogu.com.cn/record/229726043)。

::::success[代码]
```cpp
#include <bits/stdc++.h>
//#define MULTITEST
using namespace std;
typedef long long ll;
#define int ll
#define rep1(i,x,y) for (int i = (x);i <= (y);i++)
#define rep2(i,x,y) for (int i = (x);i >= (y);i--)
#define rep3(i,x,y,z) for (int i = (x);i <= (y);i += (z))
#define rep4(i,x,y,z) for (int i = (x);i >= (y);i -= (z))
#define cl(a) memset(a,0,sizeof(a))
const int N = 1010;
int n,m,q,f;
char c;
int a[N][N];
struct segtree
{
	struct node
	{
		int l;
		int r;
		int x;
		int lazy;
	} t[N << 2];
	inline int ls(int p) { return p << 1; }
	inline int rs(int p) { return p << 1 | 1; }
	inline void push_up(int p) { t[p].x = t[ls(p)].x + t[rs(p)].x; }
	inline void push_down(int p)
	{
		if (t[p].lazy)
		{
			t[ls(p)].x += t[p].lazy * (t[ls(p)].r - t[ls(p)].l + 1);
			t[rs(p)].x += t[p].lazy * (t[rs(p)].r - t[rs(p)].l + 1);
			t[ls(p)].lazy += t[p].lazy;
			t[rs(p)].lazy += t[p].lazy;
			t[p].lazy = 0;
		}
	}
	segtree() { cl(t); }
#define mid ((t[p].l + t[p].r) >> 1)
	void build(int p,int l,int r,int col)
	{
		t[p].l = l;
		t[p].r = r;
		if (l == r)
		{
			t[p].x = a[l][col];
			return;
		}
		build(ls(p),l,mid,col);
		build(rs(p),mid + 1,r,col);
		push_up(p);
	}
	void modify(int p,int l,int r,int v)
	{
		if (l <= t[p].l && t[p].r <= r)
		{
			t[p].x += v * (t[p].r - t[p].l + 1);
			t[p].lazy += v;
			return;
		}
		push_down(p);
		if (l <= mid)
			modify(ls(p),l,r,v);
		if (r > mid)
			modify(rs(p),l,r,v);
		push_up(p);
	}
	int query(int p,int l,int r)
	{
		if (l <= t[p].l && t[p].r <= r)
			return t[p].x;
		int ans = 0;
		push_down(p);
		if (l <= mid)
			ans += query(ls(p),l,r);
		if (r > mid)
			ans += query(rs(p),l,r);
		return ans;
	}
	//找到第一个非0的位置
	int getpos(int p)
	{
		if (t[p].l == t[p].r)
			return t[p].l;
		push_down(p);
		if (t[ls(p)].x > 0)
			return getpos(ls(p));
		else
			return getpos(rs(p));
	}
} b[N];
void solve()
{
	cin >> n >> m;
	rep1(i,1,n)
		rep1(j,1,m)
		{
			cin >> c;
			if (c == '#')
				a[i][j] = 1;
		}
	rep1(i,1,m)
		b[i].build(1,1,n,i);
	int col = 1;
	while (col <= m)
	{
		while (col <= m && b[col].query(1,1,n) == 0)
			col++;
		if (col > m)
			break;
		int pos = b[col].getpos(1);
		//判断：为q
		if (b[col].query(1,pos + 3,pos + 3) == 0)
		{
			q++;
			b[col].modify(1,pos,pos + 2,-1);
			b[col + 1].modify(1,pos,pos,-1);
			b[col + 1].modify(1,pos + 2,pos + 2,-1);
			b[col + 2].modify(1,pos,pos + 4,-1);
		}
		else
		{
			f++;
			b[col].modify(1,pos,pos + 4,-1);
			b[col + 1].modify(1,pos,pos,-1);
			b[col + 1].modify(1,pos + 2,pos + 2,-1);
			b[col + 2].modify(1,pos,pos,-1);
		}
	}
	cout << q << ' ' << f;
}
signed main()
{
    int t;
#ifdef MULTITEST
    cin >> t;
#else
    t = 1;
#endif
    while (t--)
        solve();
}
```
::::

---

## 作者：DecemberFox (赞：0)

# P13639 [NWRRC 2021] Letters Q and F 题解

## 题目分析

题目给定一个网格，上面由若干个相互不重叠的字母 `Q` 和 `F` 组成，现要求出网格中有多少个字母 `Q` 和 `F`。

## 解法分析

由于网格中填充的字母一定是正确的，因此每一个黑色方格一定属于某一个字母 `Q` 或 `F` 的一部分。

观察两个字母，发现它们都非常规整。四个角中有三个角处都是黑色方格。

因此，首先判断边缘（角落）部分黑色方格所属的部分，显然该处位置的方格肯定也属于字母的某个边缘（角落）部分。

简单来说，假设**从左到右、从上到下遍历网格**，那么第一个找到的黑方格一定是字母 `Q` 或字母 `F` 的左上角。假设该方格不是左上角，那在这样的遍历顺序之下，真正处于左上角的方格应该先被遍历到，与假设矛盾。

在这种遍历方法之下，可以确保**本列之前的所有字符都为 `.`**。

故只要判断到该位置的字符为 `#`，则可以直接确定在字母中的位置从而判断字母类型。

那么在两种字母都有可能的情况下，比如下面的两个 `F`，它是否也有可能为 `Q`。
```
###..
#.###
###..
#.##.
#.#..
..#..
```
观察两个字母，发现在第一列下方的两个字符有着不同，`F` 一定是两个 `#`。

而 `Q` 则一定是两个 `.`，因为字母 `Q` 的左下方的 `_` 处不可能再放入其他字符并能够保证上一列全为 `.`。
```
.###
.#.#
.###
._.#
._.#
```
**因此若同时满足 `F` 和 `Q` 时，该字符为 `F`。**

基于以上判断方法就能够很快判断出字符数量。

最终代码如下：

```cpp line-numbers
char gird[350][350];
bool check(char c,int x,int y)
{
    if(c=='F') //直接判断字符
    {
        if(gird[x][y+1]=='#'&&gird[x][y+2]=='#'&&gird[x+1][y]=='#'&&gird[x+2][y]=='#'
         &&gird[x+3][y]=='#'&&gird[x+4][y]=='#'&&gird[x+2][y+1]=='#')
        {
            gird[x][y]=gird[x][y+1]=gird[x][y+2]=gird[x+1][y]=gird[x+2][y]=
            gird[x+3][y]=gird[x+4][y]=gird[x+2][y+1]='.';
            return true;
        }
    }
    else
    {
        if(gird[x][y+2]=='#'&&gird[x][y+1]=='#'&&gird[x+1][y]=='#'&&gird[x+2][y]=='#'
         &&gird[x+2][y+1]=='#'&&gird[x+1][y+2]=='#'&&gird[x+2][y+2]=='#'&&gird[x+3][y+2]=='#'
         &&gird[x+4][y+2]=='#')
        {
            gird[x][y+2]=gird[x][y+1]=gird[x][y]=gird[x+1][y]=
            gird[x+2][y]=gird[x+2][y+1]=gird[x+1][y+2]=gird[x+2][y+2]=
            gird[x+3][y+2]=gird[x+4][y+2]='.';
            return true;
        }
    }
    return false;
}
void solve()
{
    int i,j,n,m,f(0),q(0);
    read(n,m);
    std::memset(gird,'.',sizeof gird);
    for(i=1;i<=n;++i) scanf("%s",gird[i]+1);
    for(j=1;j<=m;++j)
    {
        for(i=1;i<=n;++i)
        {
            if(gird[i][j]=='#')
            {
                if(check('F',i,j)) ++f;
                else if(check('Q',i,j)) ++q;
            }
        }
    }
    write(q,' ',f);
}
```

---

## 作者：zhuweiqi (赞：0)

注意到不方便直接搜索或 dp，我们直接考虑特殊规律。

首先一个左上角的字符必然是一个字符 P 或者字符 Q 的左上角，然后考虑同时满足两种字符的图案的情况，如果我们先假定这个字符是 P，有没有误判的情况呢？显然是有的（如左图所示）：

```
...aaa..
...a.a..
...aaa..
.aaa.a..
.a.a.a..
.aaa....
...a....
...a....
```

且**仅有这种方式**这个字符才是 Q，然后我们注意到这个图的特征：假设左上角字符为 $(i,j)$，则 $(i+4,j-1)$ 必为白色，且其周围八连通的格子均为黑色，那我们是否能根据这个判定这是两个字符 Q 呢？读者可以自己尝试构造，显然是构造不出来的。要么不符合当前字符是左上角的那个，要么不符合图案同时满足字符 P 和字符 Q 这个条件。

最后的代码就是模拟这个过程：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=302;
int n,m,cq=0,cf=0;
char a[N][N];
bool findf(int x,int y){
	if(x<=n-4 && y<=m-2 && a[x][y]=='#' && a[x+1][y]=='#'  && a[x+2][y]=='#'  && a[x+3][y]=='#'  && a[x+4][y]=='#'  && a[x][y+1]=='#'  && a[x][y+2]=='#'  && a[x+2][y+1]=='#') return 1;
	return 0;
}
void clearf(int x,int y){
	a[x][y]='.',a[x+1][y]='.',a[x+2][y]='.',a[x+3][y]='.',a[x+4][y]='.',a[x][y+1]='.',a[x][y+2]='.',a[x+2][y+1]='.';
	return;
}
bool findq(int x,int y){
	if(x<=n-4 && y<=m-2 && a[x][y]=='#' && a[x+1][y]=='#'  && a[x+2][y]=='#'  && a[x+3][y+2]=='#'  && a[x+4][y+2]=='#'  && a[x][y+1]=='#'  && a[x][y+2]=='#'  && a[x+2][y+1]=='#'   && a[x+2][y+2]=='#'   && a[x+1][y+2]=='#') return 1;
	return 0;
}
void clearq(int x,int y){
	a[x][y]='.',a[x+1][y]='.',a[x+2][y]='.',a[x+3][y+2]='.',a[x+4][y+2]='.',a[x][y+1]='.',a[x][y+2]='.',a[x+1][y+2]='.',a[x+2][y+1]='.',a[x+2][y+2]='.';
	return;
}
bool ful(int x,int y){
	if(x>1 && x<n && y>1 && y<m && a[x][y]=='.' && a[x-1][y-1]=='#' && a[x-1][y]=='#' && a[x-1][y+1]=='#' && a[x][y-1]=='#' && a[x][y+1]=='#' && a[x+1][y-1]=='#' && a[x+1][y]=='#' && a[x+1][y+1]=='#') return 1;
	return 0;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i]+1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(a[i][j]=='#'){
				if(findf(i,j)){
					if(findq(i,j)){
						if(ful(i+4,j-1)){
							cq+=2;
							clearq(i,j);
							clearq(i+3,j-2);
						}
						else {
							cf++;
							clearf(i,j);
						}
					}
					else {
						cf++;
						clearf(i,j);
					}
				}
				else {cq++;clearq(i,j);}
			}
		}
	}
	cout<<cq<<" "<<cf;
	return 0;
}
```

---

