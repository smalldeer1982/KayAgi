# Mausoleum

## 题目描述

King of Berland Berl IV has recently died. Hail Berl V! As a sign of the highest achievements of the deceased king the new king decided to build a mausoleum with Berl IV's body on the main square of the capital.

The mausoleum will be constructed from $ 2n $ blocks, each of them has the shape of a cuboid. Each block has the bottom base of a $ 1×1 $ meter square. Among the blocks, exactly two of them have the height of one meter, exactly two have the height of two meters, ..., exactly two have the height of $ n $ meters.

The blocks are arranged in a row without spacing one after the other. Of course, not every arrangement of blocks has the form of a mausoleum. In order to make the given arrangement in the form of the mausoleum, it is necessary that when you pass along the mausoleum, from one end to the other, the heights of the blocks first were non-decreasing (i.e., increasing or remained the same), and then — non-increasing (decrease or remained unchanged). It is possible that any of these two areas will be omitted. For example, the following sequences of block height meet this requirement:

- $ [1,2,2,3,4,4,3,1] $ ;
- $ [1,1] $ ;
- $ [2,2,1,1] $ ;
- $ [1,2,3,3,2,1] $ .

Suddenly, $ k $ more requirements appeared. Each of the requirements has the form: " $ h[x_{i}] $ sign $ _{i} $ $ h[y_{i}] $ ", where $ h[t] $ is the height of the $ t $ -th block, and a sign $ _{i} $ is one of the five possible signs: '=' (equals), '<' (less than), '>' (more than), '<=' (less than or equals), '>=' (more than or equals). Thus, each of the $ k $ additional requirements is given by a pair of indexes $ x_{i} $ , $ y_{i} $ ( $ 1<=x_{i},y_{i}<=2n $ ) and sign sign $ _{i} $ .

Find the number of possible ways to rearrange the blocks so that both the requirement about the shape of the mausoleum (see paragraph 3) and the $ k $ additional requirements were met.

## 样例 #1

### 输入

```
3 0
```

### 输出

```
9
```

## 样例 #2

### 输入

```
3 1
2 > 3
```

### 输出

```
1
```

## 样例 #3

### 输入

```
4 1
3 = 6
```

### 输出

```
3
```

# 题解

## 作者：宇智波—鼬 (赞：6)

# 蒟蒻的第一篇题解
那啥，~~我做了5小时交了11次，勿喷~~  
诶，蒟蒻就是蒟蒻~~~    
话说此题一天内从灰到紫，从紫到黑也是神了    
闲话少说，本人认为此题贴DP不太合适，更多的是递推
#### 从放第一本书开始推，每次放两本相同高度的，设$f_{i,j}$为左边放i本书，右边放j本书的方案，放书的时候判断一下是否合法，如果合法，$f_{i,j}$+=$f_{i-2,j}$,$f_{i-1,j-1}$,$f_{i,j-2}$  ，这个方程应该不难理解   

至于条件可以用邻接表，注意一下邻接表的数据范围，因为书的位置有200个，正反都存一遍就好了
#### 符号的正反：注意与 >= 相对的是 <= ， 不是 < 
这是我用了 N(N>20) 次调试换来的······

#### 得到的结果要除以3，因为当放最后两本书时，$f_{i-2,j}$==$f_{i-1,j-1}$==$f_{i,j-2}$
上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,f[210][210],tot,k,ans;
long long head[210],next11[410],ver[410],edge[410];
//一定开long long，一定开long long，一定开long long
void add(long long x,long long y,long long z){
    next11[++tot]=head[x],ver[tot]=y,edge[tot]=z,head[x]=tot;
}//邻接表

bool spfa(long long l,long long r,long long ll,long long rr){
//寻找出边，l表示放的两本书中左边的那本，r是右边那本，ll表示没有放书的区间的左端点，rr表示右端点，可知 ll~rr 中的书高度都大于将要放的两本书
    for(int i=head[l];i;i=next11[i])
    {
        int y=ver[i],z=edge[i];
        if(y==r){
            if(z==2||z==4) return false;
        }//特判，等于的情况只可能：出边为放的另一本书的位置
        else if(z<=2) {
            if(y<ll||y>rr) return false;
        }
        else if(z>=4) {
            if(y>ll&&y<rr) return false;
        }
        else if(z==3) return false;
    }//寻找与左端点有关的条件
    for(long long i=head[r];i;i=next11[i])
    {
        long long y=ver[i],z=edge[i];
        if(y==l){
            if(z==2||z==4) return false;
        }
        else if(z<=2) {
            if(y<ll||y>rr) return false;
        }
        else if(z>=4) {
            if(y>ll&&y<rr) return false;
        }
        else if(z==3) return false;
    }//同上
    return true;
}

int main(){
    cin>>n>>k;
    for(int i=1;i<=k;i++)
    {
        long long x,y,z=0;
        string c;
        cin>>x>>c>>y;
        if(c[1]=='=')
        {
            if(c[0]=='<') z=1;
            else z=5;
        }
        else {
            if(c[0]=='=') z=3;
            if(c[0]=='<') z=2;
            if(c[0]=='>') z=4;
        }
        if(x==y)
        {
            if(z==2||z==4)
            {
                cout<<0;
                return 0;
            }
            else continue;
        }
        add(x,y,z);
        add(y,x,6-z);//懂我为什么强调了吧
    }
    f[0][0]=1;
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<=2*i;j++)
        {
            if(j>=2&&(k==0||spfa(j-1 , j , j+1 , 2*n-2*i+j)))
                f[j][2*i-j]+=f[j-2][2*i-j];
            if(j>=1&&2*i-j>=1&&(k==0||spfa( j , 2*n-2*i+j+1 , j+1 , 2*n-2*i+j)))
 				f[j][2*i-j]+=f[j-1][2*i-j-1];
            if(2*i-j>=2&&(k==0||spfa(2*n-2*i+j+1 , 2*n-2*i+j+2 , j+1 , 2*n-2*i+j)))
                f[j][2*i-j]+=f[j][2*i-j-2];
        }//自行理解，最好画个图
    }
    for(int i=0;i<=2*n;i++) ans+=f[i][2*n-i];//ans累加，
    cout<<ans/3;//重要
    return 0;
}
```

蒟蒻告退~~~
如有问题请私信

---

## 作者：Yansuan_HCl (赞：3)

## 分析

构造数列使 $[1, n]$ 每个数出现两次，要求序列单峰并满足 $k$ 个限制，数数。

这种题我是不会做的。但是我们发现，**从峰上劈开，左右区间分别满足单调性**。这样，就可以**从小到大加入数字 $[1, n]$**，从而可以快速通过加入的区间来判断两个位置的大小。具体地说，假设当前已经填完了 $[1,l]\cup [r,2n]$，那么**未填位置上的值一定大于填了数位置上的值**。因此，我们可以 dp.

## 题解

设当前填到 $[1,l]\cup [r,2n]$，则可以：

- 把数放到 $a_{l+1}, a_{l+2}$。
- 把数放到 $a_{r-2}, a_{r-1}$。
- 把数放到 $a_{l+1}, a_{r-1}$。

对于三种状况分别判断是否能满足相应位置的限制，即可进行转移。

状态数 $O(n^2)$，转移 $O(1)$，实际上[跑得很快（截至题解发布日最优解 rk1）](https://www.luogu.com.cn/record/79289815)。

## 代码

```cpp
// 这里采用记忆化搜索
const int N = 75;
struct Lim { int op, to; }; // op=-2:lt -1:le 0:eq 1:ge 2:gt
BS<Lim> g[N]; 
int n, m;

// 要求满足单峰的限制
// 每次从小到大填入两个数, 若单峰则一定只能在两边放入
// 1. 放左边 2. 放右边 3. 各一个
// 这样"未填"就意味着大于 i 
ll f[N][N];
struct Range { int l1, r1, l2, r2; };
bool inRange(int pos, Range rg) {
	if (pos >= rg.l1 && pos <= rg.r1) return 1;
	if (pos >= rg.l2 && pos <= rg.r2) return 1;
	return 0;
}
bool check(int p, int q, int l, int r) { // 当前已填 [1,l] \cup [r, 2n], 这次加入的是哪两个(p<q)
	// 三种不同情况，<i 和 >i 的区间
	// q==l:
	// [1,p-1]\cup [r,2n] < i
	// [q+1,r-1] > i
	// p==l:
	// [1,p-1]\cup [q+1,2n] < i
	// [p+1,q-1] > i
	// p==r:
	// [1,l]\cup [q+1,2n] < i
	// [l+1,p-1] > i
	Range lt[3] {{1, p - 1, r, 2 * n}, {1, p - 1, q + 1, 2 * n}, {1, l, q + 1, 2 * n}},
		gt[3] {{q + 1, r - 1, -1, -1}, {p + 1, q - 1, -1, -1}, {l + 1, p - 1, -1, -1}};
	int sts = (q == l) ? 0 : ((p == l) ? 1 : 2);
	int i = (l + 2 * n - r + 1) / 2 + 1;
	for (Lim lim : g[p]) 
		switch (lim.op) {
			case 0: if (lim.to != q && lim.to != p) return 0; break;
			case 1: if (!inRange(lim.to, lt[sts]) && lim.to != q && lim.to != p) return 0; break;
			case 2: if (!inRange(lim.to, lt[sts])) return 0; break;
			case -1: if (!inRange(lim.to, gt[sts]) && lim.to != q && lim.to != p) return 0; break;
			case -2: if (!inRange(lim.to, gt[sts])) return 0; break;
		}
	for (Lim lim : g[q]) 
		switch (lim.op) {
			case 0: if (lim.to != q && lim.to != p) return 0; break;
			case 1: if (!inRange(lim.to, lt[sts]) && lim.to != q && lim.to != p) return 0; break;
			case 2: if (!inRange(lim.to, lt[sts])) return 0; break;
			case -1: if (!inRange(lim.to, gt[sts]) && lim.to != q && lim.to != p) return 0; break;
			case -2: if (!inRange(lim.to, gt[sts])) return 0; break;
		}
	return 1;
}

ll dp(int l, int r) { // 当前已经填到哪里 
	if (r == l + 1) { 
//		clog << l << ' ' << r << " 1" << endl;
		return 1;
	}
	if (f[l][r] != -1) return f[l][r];
	ll &ans = f[l][r]; ans = 0;
	if (check(l + 1, l + 2, l + 2, r))
		ans += dp(l + 2, r);
	if (check(r - 2, r - 1, l, r - 2))
		ans += dp(l, r - 2);
	if (check(l + 1, r - 1, l + 1, r - 1))
		ans += dp(l + 1, r - 1);
//	clog << l << ' ' << r << ' ' << (l + 2 * n - r + 1) / 2 + 1 << ' ' << ans << endl;
	return ans;
}

int main() {
	ms(f, 0xff);
	rd(n, m);
	U (i, 1, m) {
		int u, v; string op;
		cin >> u >> op >> v;
		if (op == ">") g[u] += Lim{2, v}, g[v] += Lim{-2, u};
		if (op == ">=")  g[u] += Lim{1, v}, g[v] += Lim{-1, u};
		if (op == "=") g[u] += Lim{0, v}, g[v] += Lim{0, u};
		if (op == "<=") g[u] += Lim{-1, v}, g[v] += Lim{1, u};
		if (op == "<") g[u] += Lim{-2, v}, g[v] += Lim{2, u};
	}
	printf("%lld", dp(0, n * 2 + 1) / 3);
	return 0;
}
```

## 类似的题目

[P3200 \[HNOI2009\]有趣的数列](https://www.luogu.com.cn/problem/P3200)

该题也运用了类似的构造思想，写出 dp, 从而最终转化为网格图走路问题用卡特兰数计算。

---

## 作者：Itst (赞：3)

### CF的DP好题
### 因为序列要满足单峰，所以考虑按顺序在没有加入数字的序列位置的最左和最右加入元素，这样序列将会一直满足单峰性质
### 考虑状态$f_{i,j}$表示左边已经填了$i$个，右边填了$j$个的方案，考虑第$i$个数字的转移，有$3$种：
### $a:$将这两个$i$都放在序列最左边；$b:$将这两个$i$放在序列最右边；$c.$将这两个$i$一个放一边。
### 对于$K$个约束条件我们可以在加入的时候直接判断：当前加入的两个数相等，没加入的位置的数必定比当前加的数$i$大，而其他地方一定比$i$小。
### 最后的答案是$\frac{\sum\limits_{i=0}^{2n}f_{i,2n-i}}{3}$，除3是因为对于最后一次加入，$abc$三种方案都是可行的，但是我们只能算一种。
### 注意判断约束条件时的细节。
```
#include<bits/stdc++.h>
#define int long long
using namespace std;

int ans[72][72] , numOp[72];

vector < int > num[72] , op[72];
map < string , int > opToNum;

bool ifOK(int l , int r , int que1 , int que2){
//特别注意判断que1位置与que2位置有联系的情况
	for(int i = 0 ; i < numOp[que1] ; i++)
		switch(op[que1][i]){
			case 1:
				if(num[que1][i] < r && num[que1][i] > l || num[que1][i] == que2)
					return 0;
				break;
			case 2:
				if(num[que1][i] < r && num[que1][i] > l && num[que1][i] != que2)
					return 0;
				break;
			case 3:
				if(!(num[que1][i] == que2))
					return 0;
				break;
			case 4:
				if(!(num[que1][i] <= r && num[que1][i] >= l || num[que1][i] == que2))
					return 0;
				break;
			case 5:
				if(!(num[que1][i] < r && num[que1][i] > l) || num[que1][i] == que2)
					return 0;
		}
	for(int i = 0 ; i < numOp[que2] ; i++)
		switch(op[que2][i]){
			case 1:
				if(num[que2][i] < r && num[que2][i] > l || num[que2][i] == que1)
					return 0;
				break;
			case 2:
				if(num[que2][i] < r && num[que2][i] > l && num[que2][i] != que1)
					return 0;
				break;
			case 3:
				if(!(num[que2][i] == que1))
					return 0;
				break;
			case 4:
				if(!(num[que2][i] <= r && num[que2][i] >= l || num[que2][i] == que1))
					return 0;
				break;
			case 5:
				if(!(num[que2][i] < r && num[que2][i] > l) || num[que2][i] == que1)
					return 0;
		}
	return 1;
}

main(){
	opToNum.insert(make_pair(">" , 1));
	opToNum.insert(make_pair(">=" , 2));
	opToNum.insert(make_pair("=" , 3));
	opToNum.insert(make_pair("<=" , 4));
	opToNum.insert(make_pair("<" , 5));
	int N , K;
	for(cin >> N >> K ; K ; K--){
		int a , b , t;
		string s;
		cin >> a >> s >> b;
		t = opToNum.find(s)->second;
		if(a == b)
			if(t == 1 || t == 5){
				cout << 0;
				return 0;
			}
			else
				continue;
		num[a].push_back(b);
		op[a].push_back(t);
		num[b].push_back(a);
		op[b].push_back(6 - t);
		numOp[a]++;
		numOp[b]++;
	}
	ans[0][0] = 1;
	for(int i = 1 ; i <= N ; i++){
    //DP
		for(int j = 2 * i ; j >= 2 ; j--)
			if(ans[j - 2][2 * i - j] && ifOK(j , 2 * N - 2 * i + j + 1 , j , j - 1))
				ans[j][2 * i - j] += ans[j - 2][2 * i - j];
		for(int j = 2 * i ; j >= 2 ; j--)
			if(ans[2 * i - j][j - 2] && ifOK(2 * i - j , 2 * N - j + 1 , 2 * N - j + 1 , 2 * N - j + 2))
				ans[2 * i - j][j] += ans[2 * i - j][j - 2];
		for(int j = 1 ; j < 2 * i ; j++)
			if(ans[2 * i - j - 1][j - 1] && ifOK(2 * i - j , 2 * N - j + 1 , 2 * i - j , 2 * N - j + 1))
				ans[2 * i - j][j] += ans[2 * i - j - 1][j - 1];
	}
	int all = 0;
	for(int i = 0 ; i <= 2 * N ; i++)
		all += ans[i][2 * N - i];
	cout << all / 3;
	return 0;
}
```

---

## 作者：Lynkcat (赞：2)

这道题再次让我感受到了动态规划的巧妙，~~好像前几天做的很多搜索题我也是这么说的~~。


首先看第一个限制条件，构造的序列必须为单峰序列，说明最大的数集中在整个序列的中间部分，于是我们将这 $2n$ 个数字从 $n$ ~ $1$ 的顺序向外扩散，可以用区间 $dp$ 实现。

我们设计状态 $f(i,j)$ 表示放置 $i$ 到 $j$ 这段区间的方案数，因为每次我们总是放两本相同的书，我们有三种放置方案，全放左边，一本放左边一本放右边和全放右边，假设没有 $k$ 个限制，那么我们显然可以得到这样一个方程 $f(i,j)=f(i,j-2)+f(i+2,j)+f(i+1,j-1)$ 。

接下来考虑判断 $k$ 个限制，现在我们知道，在求解放置 $(i,j)$ 的时候，$(i,j-2)$ $(i+2,j)$ $(i+1,j-1)$ 肯定已经放置完毕，放过的部分数的大小一定大于当前放置的两个数，利用这个性质来判断当前方案符不符合 $k$ 个限制即可。

``` c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k,M,x,y,l,r,bl,a[100][100],f[100][100];
string ch;
signed main()
{
	cin>>n>>k;M=n*2;
	for (int i=1;i<=k;i++)
	{
		cin>>x>>ch>>y;
		if (ch=="<") a[x][y]=1,a[y][x]=6-a[x][y];
		if (ch=="<=") a[x][y]=2,a[y][x]=6-a[x][y];
		if (ch=="=") a[x][y]=3,a[y][x]=6-a[x][y];
		if (ch==">=") a[x][y]=4,a[y][x]=6-a[x][y];
		if (ch==">") a[x][y]=5,a[y][x]=6-a[x][y];
	}
	for (int i=1;i<M;i++)
	  if (a[i][i+1]>1&&a[i][i+1]<5||a[i][i+1]==0) f[i][i+1]=1;
	for (int i=2;i<=M;i+=2)
	  for (int j=1;j+i-1<=M;j++)
	  {
	  	l=j;r=j+i-1;
	  	if (!f[l][r]){
	  	if (a[l][r]>1&&a[l][r]<5||a[l][r]==0)
	  	{
	  		bl=1;
	  		for (int i1=l+1;i1<=r-1;i1++)
	  		  if (a[l][i1]>2) 
	  		  {
	  		  	bl=0;
	  		  	break;
	  		  }
	  		for (int i1=l+1;i1<=r-1;i1++)
	  		  if (a[r][i1]>2||bl==0) 
	  		  {
	  		  	bl=0;
	  		  	break;
	  		  }
	  		if (bl) f[l][r]+=f[l+1][r-1];
	  	}//一左一右
	  	if (a[l][l+1]>1&&a[l][l+1]<5||a[l][l+1]==0)
	  	{
	  		bl=1;
	  		for (int i1=l+2;i1<=r;i1++)
	  		  if (a[l][i1]>2) 
	  		  {
	  		  	bl=0;
	  		  	break;
	  		  }
	  		for (int i1=l+2;i1<=r;i1++)
	  		  if (a[l+1][i1]>2||bl==0) 
	  		  {
	  		  	bl=0;
	  		  	break;
	  		  }
	  		if (bl) f[l][r]+=f[l+2][r];
	  	}//全放左
	  	if (a[r][r-1]>1&&a[r][r-1]<5||a[r][r-1]==0)
	  	{
	  		bl=1;
	  		for (int i1=l;i1<=r-2;i1++)
	  		  if (a[r][i1]>2) 
	  		  {
	  		  	bl=0;
	  		  	break;
	  		  }
	  		for (int i1=l;i1<=r-2;i1++)
	  		  if (a[r-1][i1]>2||bl==0) 
	  		  {
	  		  	bl=0;
	  		  	break;
	  		  }
	  		if (bl) f[l][r]+=f[l][r-2];
	  	}}//全放右
	  }
	cout<<f[1][M];
}
```

---

## 作者：Hoks (赞：0)

## 前言
比较好玩的 dp 题。

摘自[杂题选做 Part 4. dp](https://www.luogu.com.cn/training/660942)。
## 思路分析
比较难搞的条件其实就是这个单峰。

我们如何才能去满足这个单峰呢？

注意到我们最后肯定也是要把 $n$ 填进去的，那么从填那两个 $n$ 的地方断开，左边就是单增的，右边就是单降的。

因为这两边都是单调的，所以如果我们考虑，从小往大的填（每次把两个 $i$ 都填进去），那么就不可能空着填。

只有三种情况：
1. 左边填两个 $i$。
2. 右边填两个 $i$。
3. 左右各填一个 $i$。

如果我们选择了空开填，那么当且仅当空开的那个位置是峰顶才可以。

但是我们保证了从小到大，从旁边到中间，所以这个空开的地方显然是不可能为峰顶的。

所以填的方法也只有上述三种。

那么直接定义 $f_{i,j}$ 表示前面填了 $i$ 个后面填了 $j$ 个的方案数。

那么我们有转移 $f_{i,j}\rightarrow f_{i+2,j}+f_{i,j-2}+f_{i+1,j-1}$。

剩下还需要考虑的一个问题就是 $m$ 个限制条件。

反正 $n$ 这么小，直接存进邻接矩阵暴力判。

因为我们填的顺序是从小到大的，所以如果出现了要求填的数比没填的数大/相等显然是爆炸的。

还有一个限制就是一次性放进去两个数的时候这两个数也不能有大小偏序关系。

需要注意的是，当你只剩下一对数要填是方案数是 $0/1$ 不是 $0/3$，注意除以 $3$。

复杂度很低，卡满也就 $O(n^4)$，常数还很小（有剪枝而且枚举不全嘛），所以跑的飞快。
## 代码
使用了记搜写，的确好写。

```cpp
#include<bits/stdc++.h>
#define int long long
#define mid ((l+r)>>1)
#define ls (p<<1)
#define rs (ls|1)
using namespace std;
const int N=1e2+10,M=6e5+10,V=1e3,mod=1e9+7,INF=0x3f3f3f3f3f3f3f3f;
int n,m,a[N][N],f[N][N];char s[N];
namespace Fast_IO
{
	static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
	#define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
	inline int read()
	{
		int x(0),t(1);char fc(getchar());
		while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
		while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
		return x*t;
	}
	inline void flush(){fwrite(out,1,length,stdout);length=0;}
	inline void put(char c){if(length==9999999) flush();out[length++]=c;}
	inline void put(string s){for(char c:s) put(c);}
	inline void print(long long x)
	{
		if(x<0) put('-'),x=-x;
		if(x>9) print(x/10);
		put(x%10+'0');
	}
	inline bool chk(char c) { return !(c=='>'||c=='<'||c=='='||c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
	inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
	inline void rd(char s[],int&n)
	{
		s[++n]=getchar();
		while(chk(s[n])) s[n]=getchar();
		while(ck(s[n])) s[++n]=getchar();
		n--;
	}
}
using namespace Fast_IO;
inline int dfs(int l,int r)
{
	if(f[l][r]!=-1) return f[l][r];
	for(int i=1;i<=l;i++) for(int j=l+1;j<r;j++)
		if(a[i][j]==1||a[i][j]==4||a[i][j]==2) return f[l][r]=0;
	for(int i=r;i<=2*n;i++) for(int j=l+1;j<r;j++)
		if(a[i][j]==1||a[i][j]==4||a[i][j]==2) return f[l][r]=0;
	if(l+1==r) return f[l][r]=1;int ans=0;
	if(a[l+1][l+2]!=1&&a[l+1][l+2]!=3) ans+=dfs(l+2,r);
	if(a[r-1][r-2]!=1&&a[r-1][r-2]!=3) ans+=dfs(l,r-2);
	if(a[l+1][r-1]!=1&&a[l+1][r-1]!=3) ans+=dfs(l+1,r-1);
	if(r-l==3) ans/=3;return f[l][r]=ans;
}
inline void solve()
{
	n=read(),m=read();memset(f,-1,sizeof f);
	for(int i=1,x,y,l;i<=m;i++)
	{
		x=read();l=0;rd(s,l);y=read();
		if(l==1)
		{
			if(s[1]=='>') a[x][y]=1,a[y][x]=3;
			if(s[1]=='=') a[x][y]=a[y][x]=2;
			if(s[1]=='<') a[x][y]=3,a[y][x]=1;
			continue;
		}
		if(s[1]=='>'&&s[2]=='=') a[x][y]=4,a[y][x]=5;
		if(s[1]=='<'&&s[2]=='=') a[x][y]=5,a[y][x]=4;
	}print(dfs(0,2*n+1));
}
signed main()
{
	int T=1;
	// T=read();
	while(T--) solve();
	genshin:;flush();return 0;
}
```

---

## 作者：LJ07 (赞：0)

## 题目描述

[题目传送门](https://www.luogu.com.cn/problem/CF567F)

## 思路简述

我们容易发现，因为序列是满足单峰性质的，所以对于区间 $[l,r]$, 当前最小值 $v$ 的分布只有 $3$ 种情况：

1. $l$，$l+1$
2. $l$，$r$
3. $r-1$，$r$

所以我们不难发现，如果我们从小到大填进数字，每次剩下来的没填数字的区间一定是连续的，也就是只可能有一个区间没有填进数字。

设 $f(l,r)$ 表示从小到大填数，现在要填完 $[l,r]$ 这段区间的所有方案数（此时未填数字是唯一确定的），我们每次可以用 $f(l+2,r)$，$f(l+1,r-1)$，$f(l,r-2)$ 去更新 $f(l,r)$。

现在我们问题就剩下如何判断当前转移是否合法了。

高妙的判法其他题解已经讲过了，这里介绍一个简单粗暴的判法。

其实它的限制跟差分约束类似，所以我们可以每次判断暴力建边，因为边权非正，所以我们可以跑 tarjan 判断：

1. 如果有大小超过 $2$ 的环，那么 pass。
1. 如果有负环那么 pass。

虽然跑得偏慢，但是复杂度正确可以通过此题，并且好写。

## 代码展示

~~喜提最劣解。~~

[click here](https://www.luogu.com.cn/paste/xnzbauff)



---

