# [POI 2023/2024 R1] Budowa lotniska

## 题目背景

译自 [XXXI Olimpiada Informatyczna - I etap](https://sio2.mimuw.edu.pl/c/oi31-1/dashboard/) [Budowa lotniska](https://sio2.mimuw.edu.pl/c/oi31-1/p/bud/)。

## 题目描述

给你一个 $n\times n$ 的地图，地图上有 `.` 有 `X`。

求出最大的 $k$，使得：

在地图上能找到 $m(m\leq 2)$ 个 $1\times k$ 或 $k\times 1$ 的长条，使得长条不交且长条内全是 `.`。

## 说明/提示

样例解释：

```plain
.X...
.XXXX
XX..2
111.2
.X.X2
```

对于所有数据，$1\leq n\leq1500$，$1\leq m\leq2$，地图上只有 `.` 和 `X`。

| 子任务编号 | 附加限制 | 分值 |
| :----------: | :----------: | :----------: |
| 1 | $m=1$ | 20 |
| 2 | $n\leq 30$ | 22 |
| 3 | $n\leq 300$ | 23 |
| 4 |  | 35 |


## 样例 #1

### 输入

```
5 2
.X...
.XXXX
XX...
.....
.X.X.
```

### 输出

```
3
```

## 样例 #2

### 输入

```
2 1
..
..
```

### 输出

```
2
```

## 样例 #3

### 输入

```
2 2
X.
..
```

### 输出

```
1
```

## 样例 #4

### 输入

```
10 2
XXXXXXXXXX
XXXXXXXXXX
XXXXXXXXXX
XXXXXXXXXX
XXXXXXXXXX
..........
XXXXXXXXXX
XXXXXXXXXX
XXXXXXXXXX
XXXXXXXXXX
```

### 输出

```
5
```

## 样例 #5

### 输入

```
10 2
XX.XXXXX.X
XX.XXXXX.X
XX.XXXXX.X
XX.XXXXX.X
XX.XXXXX.X
XX.XXXXX.X
XX.XXXXX.X
XX.XXXXX.X
XX.XXXXX.X
XX.XXXXX.X
```

### 输出

```
10
```

## 样例 #6

### 输入

```
见附件```

### 输出

```
531
```

# 题解

## 作者：Fujxxx (赞：5)

## 提供一种贪心思路
先记录横向和竖向的所有长条并按长度降序排序。

考虑分两种情况讨论。

第一种情况只需输出最长的一个长条即可。

第二种情况考虑再按长条是否相交分两类讨论。

具体操作即直接枚举每一个长条。

当前最长的两条长条恰不相交时取短的那条作为可取到的最大值。

若相交则需取其中一条的整体与另一条被分成的两段这三条线段中第二长的作为可取到的最大值。

遍历完所有长条即得答案。

当需找两条长条时需特别注意要使答案的初值设置为最长长条长度的一半。

这样这道题就可以通过了。

```cpp
#include<bits/stdc++.h>
using namespace std;
struct line{//结构体记录长条的参数 
	int direction,length,fromi,fromj,toi,toj;
}a[10000010],emp;
int n,m,tot,ans;
char mapp[1510][1510];//地图 
inline bool cmp(line x,line y){
	return x.length>y.length;//按长条长度降序排序 
}
inline int sec(int x,int y,int z){//求三个数中第二大的数 
	if(x>y){
		if(y>z) return y;
		return min(x,z);
	}else{
		if(x>z) return x;
		return min(y,z);
	}
}
inline bool check(line x,line y){//检查两个长条是否相交 
	if(x.direction==y.direction){
		return false;//方向相同却被记录为两条不同的长条一定不相交 
	}else if(x.direction==0&&y.direction==1){
		if(x.fromj>=y.fromj&&x.fromj<=y.toj&&y.fromi>=x.fromi&&y.fromi<=x.toi) return true;//方向不同时在范围内就相交 
		return false;
	}else{
		if(y.fromj>=x.fromj&&y.fromj<=x.toj&&x.fromi>=y.fromi&&x.fromi<=y.toi) return true;//与前面同理 
		return false;
	}
}
inline int solve(line x,line y){//相交时的求解函数是解题的关键 
	if(x.direction==0&&y.direction==1){
		return max(sec(x.length,x.fromj-y.fromj,y.toj-x.fromj),sec(y.length,y.fromi-x.fromi,x.toi-y.fromi));
		//取其中一条的整体与另一条被分成的两段中第二长的作为可取到的最大值再取最大即可 
	}else{
		return max(sec(x.length,x.fromi-y.fromi,y.toi-x.fromi),sec(y.length,y.fromj-x.fromj,x.toj-y.fromj));
		//与前面同理 
	}
}
signed main(){
	std::ios::sync_with_stdio(0);
	cin>>n>>m;
	for(register int i=0;i<=n+1;i++) for(register int j=0;j<=n+1;j++)//读入地图 
		if(i==0||j==0||i==n+1||j==n+1) mapp[i][j]='X';//周边围一圈便于后续处理 
		else cin>>mapp[i][j];
	for(register int i=1;i<=n;i++){//记录横向的长条 
		line x=emp;
		for(register int j=1;j<=n;j++){
			if(mapp[i][j-1]=='X'&&mapp[i][j]!='X') x.fromi=i,x.fromj=j;
			if(mapp[i][j+1]=='X'&&mapp[i][j]!='X') x.toi=i,x.toj=j,x.length=x.toj-x.fromj+1,x.direction=1,a[tot]=x,tot++,x=emp;
		}
	}
	for(register int j=1;j<=n;j++){//记录纵向的长条 
		line x=emp;
		for(register int i=1;i<=n;i++){
			if(mapp[i-1][j]=='X'&&mapp[i][j]!='X') x.fromi=i,x.fromj=j;
			if(mapp[i+1][j]=='X'&&mapp[i][j]!='X') x.toi=i,x.toj=j,x.length=x.toi-x.fromi+1,x.direction=0,a[tot]=x,tot++,x=emp;
		}
	}
	sort(a,a+tot,cmp);//按长条长度降序排序 
	if(m==1){
		cout<<a[0].length<<'\n';//取一条时直接输出最长长条即可 
		return 0;
	}
	ans=a[0].length/2;//取两条时的最小值应当是最长长条的一半 
	for(register int i=0,j=1;i<tot;){
		if(!check(a[i],a[j])){//不相交的情况 
			ans=max(ans,a[j].length);//取短的那条作为可取到的最大值 
			i++,j=i+1;//继续向后寻找 
		}else{
			ans=max(ans,solve(a[i],a[j]));//计算其结果作为可取到的最大值 
			j++;//继续向后寻找 
		}
	}
	cout<<ans<<'\n';//最后输出即可 
	return 0;
}
```


---

## 作者：hgckythgcfhk (赞：2)

第 $3$ 篇题解说过了，$O(n^2 \log n^2)$ 无法通过本题，但是，$O(n^4)$ 可以，不仅可以，而且还抢到了最优解。

这里我讲一下怎么卡常。

## Part 0

预处理出所有的横线段和竖线段，按长度降序排序。

```
void init(){bitset<N>b1[N],b2[N];for(int i=1;i<=n;++i)b1[i].reset(),b2[i].reset();
for(int i=1,j;i<=n;++i)for(j=1;j<=n;++j)if(a[i][j]&&!b1[i][j]){line _={i,j,0};for(;i+_.len<=n&&a[i+_.len][j];++_.len)
	b1[i+_.len][j]=1;if(_.len>1)c.emplace_back(_);}sort(c.begin(),c.end());
for(int j=1,i;j<=n;++j)for(i=1;i<=n;++i)if(a[i][j]&&!b2[i][j]){line _={i,j,0};for(;j+_.len<=n&&a[i][j+_.len];++_.len)
	b2[i][j+_.len]=1;if(_.len>1)d.emplace_back(_);}sort(d.begin(),d.end());}
```

预处理的过程中，这个 $b$ 数组不能省略，因为如果省略会导致一条很长的线段被储存为 $len$ 条线段，总线段数变为 $O(n^3)$，时间复杂度 $O(n^6)$，虽然按后面的优化的话 $O(n^6)$ 能过，但这会使排序预处理的时间复杂度变为 $O(n^3 \log n^3)$，找线段的时间复杂度变为 $O(n^3)$，找线段的过程是无法从别的地方卡常的。

还有一个优化是不储存长度为 $1$ 的线段，因为如果选这条线段，答案只能为 $1$，我们可以先判断答案是否为 $0$，然后把 $ans$  的初始值设为 $1$，这样这条线段不会产生任何贡献，可以发现，这个优化是很有用的，因为在随机数据下，越短的线段出现次数的期望值越大，而且假设有一条长度为 $len$ 的横线段，它就可能贡献 $O(len)$ 条竖线段，比如下面这组数据。

```
..........
XXXXXXXXXX
..........
XXXXXXXXXX
..........
XXXXXXXXXX
..........
XXXXXXXXXX
..........
XXXXXXXXXX
```

虽然该数据只有 $5$ 条横线段，但该数据有 $50$ 条长度为 $1$ 的竖线段。

## Part 1

很明显，长度最大的线段就是答案，取最长横线段和最长竖线段的长度的最大值即可。

```
namespace sb1{inline const bool main(){
	for(int i=1;i<=n&&!ans;++i)for(int j=1;j<=n;++j)if(a[i][j]){ans=1;break;}
	if(c.size())ans=max(ans,c[0].len);if(d.size())ans=max(ans,d[0].len);cout<<ans;return 0;}};
```
这里介绍一下这种看起来高级实际上很简单的 namespace 写法，这种写法什么都不需要注意，正常写就行，这个写法的好处是用一个程序写多个程序，并且根据数据判断调用哪个，其实也可以写两个 solve 函数，但比起 namespace，两个函数可能会导致变量或其他函数重名，namespace 写法主函数一般这么写。

```
signed main(){int op;cin>>op;
	if(chk1(op))return sb1::main();
	if(chk2(op))return sb2::main();
	if(chk3(op))return sb3::main();
	......
}
```
sb1 表示 subtask1，sb3 和 sb3 同理。

这样还可以用来解决特殊性质和暴力分不好都得到，数组两维一大一小具体哪个大哪个小需要分情况讨论，平时做题写下一个题懒得新建文件等问题。

## Part 2

我们分这几种情况讨论一下，答案可能为：

1. 次长的横线段。（选两条横线段，见佯例 1）

2. 次长的竖线段。（选两条竖线段，见佯例 2）

3. 最长线段的一半向下取整。（见佯例 4）

4. 选一横一竖的两条不相交的线段。

5. 选一横一竖的两条相交线段。

我们发现，除了最后两种情况以外，排序后都可以 $O(1)$ 的求，第 $4$ 种也比较好求，考虑怎么最暴力的求最后一种情况。如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/ytzihg5f.png)

发现两条相交线段可以分解为 $4$ 条线段，从这 $4$ 条里选最长的两条的，把交点加入到较短的线段，由于情况 $3$ 已经考虑过了所选两条线段来自同一条线段的情况，我们只考虑一横一竖。这样就得到了一份超时的程序。

```
namespace sb2{
	inline bool chk(const line&x,const line&y){return x.x+x.len>y.x&&y.y+y.len>x.y&&x.x<=y.x&&x.y>=y.y;}
	inline const bool main(){int ans=0;for(int i=1;i<=n;++i)for(int j=1;j<=n;++j)ans+=a[i][j];
	if(!ans)return cout<<0,0;if(ans==1)return cout<<0,0;ans=1;
	const int nc=c.size(),nd=d.size();if(nc>1)ans=max(ans,c[1].len);if(nd>1)ans=max(ans,d[1].len);
	if(nc)ans=max(ans,c[0].len>>1);if(nd)ans=max(ans,d[0].len>>1);if(!nc||!nd)return cout<<ans,0;
	for(int i=0;i<nc;++i)for(int j=0;j<nd;++j)if(!chk(c[i],d[j]))ans=max(ans,min(c[i].len,d[j].len));
	for(int i=0;i<nc;++i)for(int j=0;j<nd;++j)if(chk(c[i],d[j])){int xl,xr,yl,yr;
		xl=d[j].x-c[i].x,xr=c[i].len-xl-1;yl=c[i].y-d[j].y,yr=d[j].len-yl-1;
		//cerr<<i<<' '<<j<<" : "<<xl<<' '<<xr<<' '<<yl<<' '<<yr<<'\n';
		ans=max(ans,min(max(xl,xr)+1,max(yl,yr)));ans=max(ans,min(max(xl,xr),max(yl,yr)+1));
	}cout<<ans<<'\n';/*cerr<<"竖\n";debug(c);cerr<<"横\n";debug(d);*/return 0;}};
```

## Part 3

我的这个做法纯属歪打正着，因为我一开始脑抽把线段的个数想成了 $O(n)$，自认为时间复杂度 $O(n^2 \log n^2)$，所以才敢这么写的，但是这份程序在 $n=300$ 的点就超时了，明显不是常数的问题，大家可以自行下载 $n=300$ 的超时数据，解除此程序调试部分的注释，发现线段个数达到了 $10^4$ 的级别，仔细想想看，线段个数确实是 $O(n^2)$ 的，但我已经写了这么长时间，下载了好几组数据去调试，真的要删掉重写吗？不，经常写乱搞做法的我又想乱搞了，我们发现，时间复杂度的瓶颈在最后两种情况的两个循环。

一个正确性显然的结论：长度比 $ans$ 小的线段不会产生任何贡献。

排序后，我们可以直接 break 掉。

但这样还是超时，算一下时间，找线段两次 $O(n^2)$，排序两次 $O(n^2 \log n^2)$，求解最后两种情况虽然不好构造能卡到 $O(n^4)$ 的数据，但运行好几次 $O(n^2)$ 是比较好构造的，大体估计一下：

$$2 \times 1500^2 + 2 \times 1500^2 \times 21 + 2 \times 1500^2>10^8$$

但时间只有 $500ms$，这还是不计输入输出的情况下的时间。

发现时间复杂度的瓶颈在于线段太多，不仅影响排序还会导致最后两种情况进行无意义的循环。

我们能不能一开始就不把不合法的线段存下来？好像不能，但我们可以尽量减少，这样的线段，显然，我们可以在初始化的时候就算出前 $3$ 种情况的解，然后把长度小于初始化时能求出的解的线段弹出。

然后就抢到最优解了。

```
#include<bits/stdc++.h>
#define open ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
using namespace std;constexpr unsigned N=1501;
#define void inline void
#define int register signed
unsigned n;signed ans=1;bitset<N>a[N];
#define debug(e) for(line i:e)cerr<<'('<<i.x<<','<<i.y<<')'<<' '<<i.len<<'\n';
struct line{signed x,y,len;inline bool operator<(const line&b){return len>b.len;}};vector<line>c,d;
void init(){bitset<N>b1[N],b2[N];for(int i=1;i<=n;++i)b1[i].reset(),b2[i].reset();
for(int i=1,j;i<=n;++i)for(j=1;j<=n;++j)if(a[i][j]&&!b1[i][j]){line _={i,j,0};for(;i+_.len<=n&&a[i+_.len][j];++_.len)
	b1[i+_.len][j]=1;if(_.len>ans)c.emplace_back(_),ans=max(ans,_.len>>1);}sort(c.begin(),c.end());
for(int j=1,i;j<=n;++j)for(i=1;i<=n;++i)if(a[i][j]&&!b2[i][j]){line _={i,j,0};for(;j+_.len<=n&&a[i][j+_.len];++_.len)
	b2[i][j+_.len]=1;if(_.len>ans)d.emplace_back(_),ans=max(ans,_.len>>1);}sort(d.begin(),d.end());
	while(c.size()&&(*c.rbegin()).len<ans)c.pop_back();while(d.size()&&(*d.rbegin()).len<ans)d.pop_back();}
namespace sb1{inline const bool main(){ans==1?ans=0:0;
	for(int i=1;i<=n&&!ans;++i)for(int j=1;j<=n;++j)if(a[i][j]){ans=1;break;}
	if(c.size())ans=max(ans,c[0].len);if(d.size())ans=max(ans,d[0].len);cout<<ans;return 0;}};
namespace sb2{
	inline bool chk(const line&x,const line&y){return x.x+x.len>y.x&&y.y+y.len>x.y&&x.x<=y.x&&x.y>=y.y;}
	inline const bool main(){ans==1?ans=0:0;for(int i=1;i<=n;++i)for(int j=1;j<=n;++j)ans+=a[i][j];
	if(!ans)return cout<<0,0;if(ans==1)return cout<<0,0;ans=1;
	const int nc=c.size(),nd=d.size();if(nc>1)ans=max(ans,c[1].len);if(nd>1)ans=max(ans,d[1].len);
	if(nc)ans=max(ans,c[0].len>>1);if(nd)ans=max(ans,d[0].len>>1);if(!nc||!nd)return cout<<ans,0;
	for(int i=0;i<nc;++i)for(int j=0;j<nd;++j)if(!chk(c[i],d[j])){
		ans=max(ans,min(c[i].len,d[j].len));if(ans>=c[i].len||ans>=d[j].len)break;}
	for(int i=0;i<nc;++i)for(int j=0;j<nd;++j)if(chk(c[i],d[j])){int xl,xr,yl,yr;
		xl=d[j].x-c[i].x,xr=c[i].len-xl-1;yl=c[i].y-d[j].y,yr=d[j].len-yl-1;
		//cerr<<i<<' '<<j<<" : "<<xl<<' '<<xr<<' '<<yl<<' '<<yr<<'\n';
		if(ans>=c[i].len||ans>=d[j].len)break;
		ans=max(ans,min(max(xl,xr),d[j].len));ans=max(ans,min(max(yl,yr),c[i].len));
		ans=max(ans,min(max(xl,xr)+1,max(yl,yr)));ans=max(ans,min(max(xl,xr),max(yl,yr)+1));
	}cout<<ans<<'\n';/*cerr<<"竖\n";debug(c);cerr<<"横\n";debug(d);*/return 0;}};
signed main(){open;int m;cin>>n>>m;char t[N];
	for(int i=1,j;i<=n;++i)for(j=1,cin>>t+1;j<=n;++j)a[i][j]=t[j]=='.';
	init();return m==1?sb1::main():sb2::main();
}

```

[测评状态](https://www.luogu.com.cn/record/140383850)

然而，这个做法还可以比我实际写出来的更优，首先为了偷懒没有先求出前两种情况的解，只判了情况 $3$，然后，其实可以在排序之前弹出，只是因为我懒得写 swap 函数。

顺便提一句，不用链表也有快速删除数组中元素的方法。

```
inline void remove(int p,vector<A> a){swap(a[p],a[a.size()-1]);a.pop_back();}
```
但是这个方法会破坏元素顺序，不过对于本题是够用的，因为删完之后还要排序。

其实我实际写出来的就够用了，存进去的线段数一般情况下已经小于 $O(n)$ 了，至于卡到 $O(n^4)$，起码我不会造那样的数据，就算能卡到，把所有优化拉满是能做到平均情况下有 $O(1)$ 条线段的，我给个自己不确定对不对的证明，欢迎大神来 hack。

第 $i$ 长的横线段的长度用 $len_i$ 表示，假设初始化之后能存 $3$ 条线段，那么一定满足 $len_3<len_2$，这与情况 $1$ 矛盾。所以不可能存下 $2$ 条以上的线段，若能存 $2$ 条，一定满足 $len_2>\lfloor \frac{len_1}{2} \rfloor$，否则只能存一条，所以最多只能存 $1$ 条或 $2$ 横线段，竖线段同理。

---

## 作者：Loser_Syx (赞：1)

对 $m$ 值分类讨论。

$m=1$ 显然白给，直接求最长连续 `.` 段即可。

$m=2$ 需要再次分讨，具体分为：

- 选出的两个线段相交。

> 对于此种情况，由于要求 $k$ 最大，所以预处理对于横里竖里每个连通块的长度，记录起始，如此以来便可枚举断点，分成四份，然后再枚举断点归属，这样的话就出现一种可能成为最大的答案：它与其余的三个取最大的两个中的最小值。

- 选出的线段不相交。

> 对于此种情况，先记录每个线段的长度在一个 `multiset` 内，然后枚举其中一个线段，暂时去除与其相交的线段，然后再与剩下的最大长度取 $\min$ 即可，答案可能为那个最小值。

复杂度 $O(n^2 \log n^2)$，考虑优化。

发现 `multiset` 内存放的只有 $n$ 种情况，替换为 `map`，使得复杂度为 $O(n^2 \log n)$。

然后就是空间爆了。

考虑将 `int` 改为 `short`，注意某些地方不能 `short`。

卡过去了，思维及代码严格大于 `std`。

```cpp
struct node {
	short sx, sy, ex, ey, length;
};
int in[1502][1502][2]; // 此处不能 short，因为 line 存的是 n^2 数量个的。
int min(int x, int y) {return x > y ? y : x;}
int max(int x, int y) {return x < y ? y : x;}
char c[1502][1502];
void solve() {
	auto Getchar = [&]() -> char {
		char c = getchar();
		while (c != 'X' && c != '.') c = getchar();
		return c;
	};
	short n, m, i, j, k; cin >> n >> m;
	for (i = 1; i <= n; ++i) {
		for (j = 1; j <= n; ++j) {
			c[i][j] = Getchar();
		}
	}
	vector<node> line;
	for (i = 1; i <= n; ++i) {
		for (j = 1; j <= n; ++j) {
			if (c[i][j] != 'X') {
				line.push_back({i, j, i, j, 0});
				for ( ; j <= n && c[i][j] == '.'; ++j) {
					line.back().ey = j;
					line.back().length++;
					in[i][j][0] = line.size()-1;
				}
			}
		}
	}
	for (i = 1; i <= n; ++i) {
		for (j = 1; j <= n; ++j) {
			if (c[j][i] != 'X') {
				line.push_back({j, i, j, i, 0});
				for ( ; j <= n && c[j][i] == '.'; ++j) {
					line.back().ex = j;
					line.back().length++;
					in[j][i][1] = line.size()-1;
				}
			}
		}
	}
	map<short, int, greater<short> > getK;
	for (const auto i : line) {
		getK[i.length]++;
	}
	int ans = 0;
	auto chkmax = [&](short a, short b, short c, short d) -> void {
		ans = max(ans, min(a, max(max(b, d), c) + 1));
		ans = max(ans, min(a + c + 1, max(b, d)));
	};
	if (m == 1) return cout << ((getK.begin())->first) << '\n', void();
	for (i = 1; i <= n; ++i) {
		for (j = 1; j <= n; ++j) {
			if (c[i][j] != 'X') {
				node a = line[in[i][j][0]], b = line[in[i][j][1]];
				short s1 = j - a.sy, s2 = a.ey - j, s3 = i - b.sx, s4 = b.ex - i;
				chkmax(s1, s3, s2, s4);
				chkmax(s2, s3, s1, s4);
				chkmax(s3, s1, s4, s2);
				chkmax(s4, s1, s3, s2);
			}
		}
	}
	auto delete_value = [&](short x) {
		if (--getK[x] == 0) getK.erase(x);
	};
	for (i = 1; i <= n; ++i) {
		for (j = 1; j <= n; ++j) {
			k = j;
			if (c[i][j] != 'X') {
				for (; j <= n && c[i][j] != 'X'; ++j) {
					delete_value(line[in[i][j][1]].length);
				}
				delete_value(line[in[i][j-1][0]].length);
				if (getK.size())  ans = max(ans, min(line[in[i][j-1][0]].length, (getK.begin())->first));
				for (; k < j; ++k) getK[line[in[i][k][1]].length]++;
				getK[line[in[i][j-1][0]].length]++;
			}
		}
	}
	for (i = 1; i <= n; ++i) {
		for (j = 1; j <= n; ++j) {
			k = j;
			if (c[j][i] != 'X') {
				for (; j <= n && c[j][i] != 'X'; ++j) {
					delete_value(line[in[j][i][0]].length);
				}
				delete_value(line[in[j-1][i][1]].length);
				if (getK.size())  ans = max(ans, min(line[in[j-1][i][1]].length, (getK.begin())->first));
				for (; k < j; ++k) getK[line[in[k][i][0]].length]++;
				getK[line[in[j-1][i][1]].length]++;
			}
		}
	}
	cout << ans << '\n';
}
```

---

## 作者：Tairitempest (赞：0)

## [POI 2023/2024 R1] Budowa lotniska

显然，我们需要对 $m=1$ 和 $m=2$ 分类讨论。

### 当 $m=1$ 时

从横的方向和竖的方向枚举，找到最长段即可。

### 当 $m=2$ 时

提供一种 $n^2$ 复杂度的思路。

我们分类讨论最优解可能的情况：

当两个方块平行且所在的行或列不同的时候，此时找到最优解比较简单，预处理出每行最长段和每列最长段，计算两种方向的次长段即可。

接下来考虑如下思路：预处理出每个格子在这一行中左边的最大段和右边的最大段，及在这一列中上边的最大段和下边的最大段；当我们遍历所有的格子时，对于每个格子，从这四个值当中取次大。这样可以包含两种情况：两个方块平行且所在的行或列相同，且中间至少有一个格子相隔；两个方块不平行，并且其所在的行和列的交点没有被占据。

最后处理剩下的两个情况：两个方块平行且所在的行或列相同，且中间无格子相隔；两个方块不平行，并且其所在的行和列的交点被占据。

对于第一个情况，可以对于每个点，找到从这个格子最多可以向左走多少格，从这个格子最多可以向右走多少格，从这个格子最多可以向上走多少格，从这个格子最多可以向下走多少格，然后我们就可以获得对于每个格子包含它的最长段，分成两半就可以了。

对于第二种情况，我们就可以获得对于每个格子包含它的横向最长段和纵向最长段：对于前者，我们把它与这一列中上边的最大段和下边的最大段长度的最大值比较，取其中较小的；对于后者，我们把它与这一列中左边的最大段和右边的最大段长度的最大值比较，取其中较小的。取前者与后者的最大值就可以了。

通过分类讨论可以包含所有情况。复杂度 $O(n^2)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,m,maxans;
bool c[1510][1510];
int lft[1510][1510],rt[1510][1510],ab[1510][1510],bel[1510][1510];
int maxlft[1510][1510],maxrt[1510][1510],maxab[1510][1510],maxbel[1510][1510];

ll solve1(){
	ll ans=0;
	ll firstmax=0;
	for(int i=1;i<=n;i++){
		if(maxlft[i][n]>firstmax)
			firstmax=maxlft[i][n];
	}
	ans=max(ans,firstmax);
	firstmax=0;
	for(int i=1;i<=n;i++){
		if(maxab[n][i]>firstmax)
			firstmax=maxab[n][i];
	}
	ans=max(ans,firstmax);
	return ans;
}

ll solve2(){
	ll ans=0;
	ll firstmax=0,secondmax=0;
	for(int i=1;i<=n;i++){
		if(maxlft[i][n]>firstmax){
			secondmax=firstmax;
			firstmax=maxlft[i][n];
		}else if(maxlft[i][n]>secondmax){
			secondmax=maxlft[i][n];
		}
	}
	ans=max(ans,secondmax);
	firstmax=0,secondmax=0;
	for(int i=1;i<=n;i++){
		if(maxab[n][i]>firstmax){
			secondmax=firstmax;
			firstmax=maxab[n][i];
		}else if(maxab[n][i]>secondmax){
			secondmax=maxab[n][i];
		}
	}
	ans=max(ans,secondmax);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			ll tmp[4]={maxab[i-1][j],maxbel[i+1][j],maxlft[i][j-1],maxrt[i][j+1]};
			sort(tmp,tmp+4);
			ans=max(ans,tmp[2]);
			if(c[i][j]) continue;
			ans=max(ans,(ll)(max((ab[i][j]+bel[i][j]-1)/2,(lft[i][j]+rt[i][j]-1)/2)));
			ll Hmax=min((int)(max(maxab[i-1][j],maxbel[i+1][j])),lft[i][j]+rt[i][j]-1);
			ll Zmax=min((int)(max(maxlft[i][j-1],maxrt[i][j+1])),ab[i][j]+bel[i][j]-1);
			ans=max({ans,Hmax,Zmax});
		}
	}
	return ans;
}

int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			char tmp;
			cin>>tmp;
			if(tmp=='X') c[i][j]=true;
			else c[i][j]=false;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(c[i][j]){
				lft[i][j]=0;
				ab[i][j]=0;
				maxlft[i][j]=maxlft[i][j-1];
				maxab[i][j]=maxab[i-1][j];
			}else{
				lft[i][j]=lft[i][j-1]+1;
				ab[i][j]=ab[i-1][j]+1;
				maxlft[i][j]=max(maxlft[i][j-1],lft[i][j]);
				maxab[i][j]=max(maxab[i-1][j],ab[i][j]);
			}
		}
	}
	for(int i=n;i>=1;i--){
		for(int j=n;j>=1;j--){
			if(c[i][j]){
				rt[i][j]=0;
				bel[i][j]=0;
				maxrt[i][j]=maxrt[i][j+1];
				maxbel[i][j]=maxbel[i+1][j];
			}else{
				rt[i][j]=rt[i][j+1]+1;
				bel[i][j]=bel[i+1][j]+1;
				maxrt[i][j]=max(maxrt[i][j+1],rt[i][j]);
				maxbel[i][j]=max(maxbel[i+1][j],bel[i][j]);
			}
		}
	}
	if(m==1) cout<<solve1()<<endl;
	else cout<<solve2()<<endl;
	return 0;
}
```

---

## 作者：船酱魔王 (赞：0)

### 题意回顾

在 $ n \times n $ 障碍矩阵上找到 $ m $ 个不交且长度相等的的无障碍段，使得这些段的长度最大。

$ 1 \le n \le 1500 $，$ 1 \le m \le 2 $。

### 分析

如很多段不交的话判定合法性都很难，复杂度可能直接飙升到指数级，但是本题突破口在于 $ 1 \le m \le 2 $，考虑根据 $ m $ 的值分讨。

#### $ m=1 $ 情况

找到矩阵中一段最长的无障碍段，对于每一行和每一列直接暴力找即可（以行为例的实现细节：维护 $ mx $ 表示最大长度，维护 $ ct $ 表示该行第 $ j $ 列往前数连续多少个格子无障碍，实时维护 $ ct $ 并用 $ ct $ 更新 $ mx $ 即可）。

如果我们用类似的实现方式实时维护 $ cc_j $ 表示第 $ j $ 列从第 $ i $ 行往上数连续几个是无障碍格子，可以只按照行从上往下扫一遍即可求出 $ m=1 $ 的解，不用再扫一遍列（本题解给出的参考实现中 $ m=1 $ 是用第一种方法实现的）。

#### $ m=2 $ 情况

用 $ m=1 $ 情况的第二种方法，可以求出矩阵前 $ i $ 行/后 $ i $ 行/前 $ j $ 列/后 $ j $ 列的最长连续无障碍段。

我们发现，如果 $ 2 $ 个无障碍段不相交，那么必然可以划一条水平/竖直的线，把他们分别放置在这条线两边的两个子矩阵中，而这些子矩阵正是上一段描述的那种可以预处理出最大无障碍段长的矩阵。

故考虑对于每条水平/竖直分割线，将两个子矩阵的无障碍段长最大值取 $ \min $，这些值的最优解即为答案。

### 参考实现

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int N = 1505;
int n, m;
char a[N][N];
int f[N];
int g[N];
int h[N];
int e[N];
int cc[N];
int main() {
	cin >> n >> m;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) cin >> a[i][j];
	}
	if(m == 1) {
		int mx = 0;
		int ct = 0;
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= n; j++) {
				if(a[i][j] == '.') ct++, mx = max(mx, ct);
				else ct = 0;
			}
			ct = 0;
		}
		for(int j = 1; j <= n; j++) {
			for(int i = 1; i <= n; i++) {
				if(a[i][j] == '.') ct++, mx = max(mx, ct);
				else ct = 0;
			}
			ct = 0;
		}
		cout << mx << endl;
		return 0;
	}
	int mx, ct;
	mx = 0;
	for(int i = 1; i <= n; i++) {
		ct = 0;
		for(int j = 1; j <= n; j++) {
			if(a[i][j] == '.') ct++, mx = max(mx, ct), cc[j]++, mx = max(mx, cc[j]);
			else ct = cc[j] = 0;
		}
		f[i] = mx;
	}
	memset(cc, 0, sizeof(cc));
	mx = 0;
	for(int i = n; i >= 1; i--) {
		ct = 0;
		for(int j = 1; j <= n; j++) {
			if(a[i][j] == '.') ct++, mx = max(mx, ct), cc[j]++, mx = max(mx, cc[j]);
			else ct = cc[j] = 0;
		}
		g[i] = mx;
	}
	memset(cc, 0, sizeof(cc));
	mx = 0;
	for(int j = 1; j <= n; j++) {
		ct = 0;
		for(int i = 1; i <= n; i++) {
			if(a[i][j] == '.') ct++, mx = max(mx, ct), cc[i]++, mx = max(mx, cc[i]);
			else ct = cc[i] = 0;
		}
		h[j] = mx;
	}
	memset(cc, 0, sizeof(cc));
	mx = 0;
	for(int j = n; j >= 1; j--) {
		ct = 0;
		for(int i = 1; i <= n; i++) {
			if(a[i][j] == '.') ct++, mx = max(mx, ct), cc[i]++, mx = max(mx, cc[i]);
			else ct = cc[i] = 0;
		}
		e[j] = mx;
	}
	int ans = 0;
	for(int i = 1; i < n; i++) {
		ans = max(ans, min(f[i], g[i + 1]));
		ans = max(ans, min(h[i], e[i + 1]));
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：Purslane (赞：0)

# Solution

水中水题。很容易做到 $O(n^2)$，不过我懒，加了个排序（只需要取最大值和次大值，打擂台就是线性的），写了 $O(n^2 \log n)$。

$m=1$ 时输出最长连续段。

$m=2$ 时分三种情况：

- 都是横线。要么是横线最大值和次大值，要么是最大值砍成均匀的两半。
- 都是竖线。同上。
- 一横一竖。不妨枚举竖线。注意到竖线必定有一端无法继续延伸，所以枚举自由段和方向，转化为求若干个两条边在原矩形边上的矩形中横线长度最大值。$O(n^2)$ 预处理即可。

代码：

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1500+10;
int n,m,dp[MAXN][MAXN][4],t[MAXN][MAXN][4],flg[MAXN][MAXN];
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	ffor(i,1,n) {
		string S; cin>>S;
		ffor(j,1,n) if(S[j-1]=='X') flg[i][j]=1;	
	}
	int ans=0;
	vector<int> lenx,leny;
	ffor(i,1,n) ffor(j,1,n) {
		if(!flg[i][j]) t[i][j][0]=t[i-1][j][0]+1,t[i][j][1]=t[i][j-1][1]+1;
		if(!flg[i][j]&&(flg[i+1][j]||i==n)) lenx.push_back(t[i][j][0]);
		if(!flg[i][j]&&(flg[i][j+1]||j==n)) leny.push_back(t[i][j][1]);
	}
	roff(i,n,1) roff(j,n,1) if(!flg[i][j]) t[i][j][2]=t[i][j+1][2]+1,t[i][j][3]=t[i+1][j][3]+1;	
	sort(lenx.begin(),lenx.end(),[](int A,int B) {return A>B;});
	sort(leny.begin(),leny.end(),[](int A,int B) {return A>B;});
	if(lenx.empty()) return cout<<0,0;
	if(m==1) return cout<<max(lenx[0],leny[0]),0;
	if(lenx.size()!=1) ans=max(ans,lenx[1]); ans=max(ans,lenx[0]/2);
	if(leny.size()!=1) ans=max(ans,leny[1]); ans=max(ans,leny[0]/2);
	
	ffor(i,1,n) ffor(j,1,n) dp[i][j][0]=max({dp[i-1][j][0],dp[i][j-1][0],t[i][j][1]});
	ffor(i,1,n) roff(j,n,1) dp[i][j][1]=max({dp[i-1][j][1],dp[i][j+1][1],t[i][j][2]});
	roff(i,n,1) ffor(j,1,n) dp[i][j][2]=max({dp[i+1][j][2],dp[i][j-1][2],t[i][j][1]});
	roff(i,n,1) roff(j,n,1) dp[i][j][3]=max({dp[i+1][j][3],dp[i][j+1][3],t[i][j][2]});
	
	ffor(i,1,n) ffor(j,1,n) if(!flg[i][j]) {
		ans=max(ans,min(t[i][j][3],max({dp[i][j-1][2],dp[i][j+1][3],dp[i-1][n][0]})));	
		ans=max(ans,min(t[i][j][0],max({dp[i][j-1][0],dp[i][j+1][1],dp[i+1][n][2]})));
	}
	cout<<ans;
	return 0;
}
/*
  0
1 t 2
  3
  
0   1
  d 
2   3
*/
```

---

## 作者：Lofty (赞：0)

### 前言：

一道小小的水蓝。

### 正文：

首先看到这题，我第一时间想到的是最大子矩阵，在单调栈的预处理过程中显然可以找到  $m=1$ 时的答案。所以考虑 $m=2$ 时如何扩展。看到求最大值，想到二分答案，再看 $n \le 1500$，推测时间复杂度大约是 $O(n^2 \log n)$。于是考虑复用单调栈预处理过程。

首先需要定下二分范围。由于取一个 $1 \times k$ 和一个 $k \times 1$ 时处理方法特殊，考虑在所有 $1 \times k$ 的最大值与次大值间取 $ k \times 1$ 的值，或反之。贪心取横竖最大值较大者即可。

这里有个小细节，是保证判断时 $n^2$ 复杂度的关键。若当枚举的 $k \times 1$ 与取最大值的 $1 \times k$ 相交于 $pos$，$k-pos<mid$ 并且 $pos<mid$，那么这个 $k$ 一定不是最大的 $k$。

其实显然，因为 $mid$ 在次大值于最大值之间，那长度为 $mid$ 的一定在最大值处截断出来的一段区间。否则就不合法了。

### 代码：

```
constexpr int N=15e2+5;
int n,m;
int a[N][N];
bool v[N][N];
int h[N][N],w[N][N];
int tmph[N][N],tmpw[N][N];
int hl,hr,wl,wr,hi,hj,wi,wj;
bool check_h(int mid)
{
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
			if(a[i][j])
			{
				if(v[i][j])
				{
					if(h[i-1][j]>=mid||hr-h[i][j]>=mid)
						tmpw[i][j]=tmpw[i][j-1]+1;
					else 
					{
						ans=max(ans,tmpw[i][j-1]);
						tmpw[i][j]=0;
					}
				}
				else 
					tmpw[i][j]=tmpw[i][j-1]+1;
			}
			else 
			{
				ans=max(ans,tmpw[i][j-1]);
				tmpw[i][j]=0;
			}
		ans=max(ans,tmpw[i][n]);
	}
	return ans>=mid;
}
bool check_w(int mid)
{
	int ans=0;
	for(int j=1;j<=n;j++)
	{
		for(int i=1;i<=n;i++)
			if(a[i][j])
			{
				if(v[i][j])
				{
					if(w[i][j-1]>=mid||wr-w[i][j]>=mid)
						tmph[i][j]=tmph[i-1][j]+1;
					else 
					{
						ans=max(ans,tmph[i-1][j]);
						tmph[i][j]=0;
					}
				}
				else 
					tmph[i][j]=tmph[i-1][j]+1;
			}
			else 
			{
				ans=max(ans,tmph[i-1][j]);
				tmph[i][j]=0;
			}
		ans=max(ans,tmph[n][j]);
	}
	return ans>=mid;
}
int solve_h()
{
	int l=max(hr/2,hl),r=hr;
	for(int i=hi-hr+1;i<=hi;i++)
		v[i][hj]=1;
	while(l<r)
	{
		int mid=(l+r+1)>>1;
		if(check_h(mid))
			l=mid;
		else
			r=mid-1;
	}
	for(int i=hr-hi;i<=hr;i++)
		v[i][hj]=0;
	return l;
}
int solve_w()
{
	int l=max(wr/2,wl),r=wr;
	for(int j=wj-wr+1;j<=wj;j++)
		v[wi][j]=1;
	while(l<r)
	{
		int mid=(l+r+1)>>1;
		if(check_w(mid))
			l=mid;
		else 
			r=mid-1;
	}
	for(int j=wr-wj;j<=wr;j++)
		v[wi][j]=0;
	return l;
}
int main()
{
	read(n,m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			char s;
			do
			{
				s=gc();
			}while(s!='X'&&s!='.');
			a[i][j]=s=='.';
		}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
			if(a[i][j])
			{
				h[i][j]=h[i-1][j]+1;
				w[i][j]=w[i][j-1]+1;
			}
			else
			{
				if(hr<h[i-1][j])
				{
					hl=hr;hr=h[i-1][j];
					hi=i-1;hj=j;
				}
				else if(hl<h[i-1][j])
					hl=h[i-1][j];
				if(wr<w[i][j-1])
				{
					wl=wr;wr=w[i][j-1];
					wi=i;wj=j-1;
				}
				else if(wl<w[i][j-1])
					wl=w[i][j-1];
				h[i][j]=w[i][j]=0;
			}
		if(wr<w[i][n])
		{
			wl=wr;wr=w[i][n];
			wi=i;wj=n;
		}
		else if(wl<w[i][n])
			wl=w[i][n];
	}
	for(int i=1;i<=n;i++)
		if(hr<h[n][i])
		{
			hl=hr;hr=h[n][i];
			hi=n;hj=i;
		}
		else if(hl<h[n][i])
			hl=h[n][i];
	if(m==1)
		writeln(max(hr,wr));
	else
	{
		int ans=0;
		if(hr>wr)
			ans=solve_h();
		else if(hr<wr)
			ans=solve_w();
		else
			ans=max(solve_h(),solve_w());
		writeln(ans);
	}
	return 0;
}

```

---

## 作者：mango2011 (赞：0)

## Part -1 废话

今天偶遇一道蓝题，切之，貌似很水。

## Part 0 预备知识

无，本题不需要任何高深算法。

## Part 1 分析题目

### Part 1-1

当 $m=1$，时我们直接输出长度最长的长条的长度。

### Part 1-2 难点
根据数据范围，我们就猜出来要二分答案。但是，对于给定的 $k$，我们如何检查呢?

很明显的是，合法的“长条”一定是横着的或竖着的。所以，我们要进行分类讨论。我们分为 $3$ 个部分：

$1.$ 存在两个横着的长条。

$2.$ 存在两个竖着的长条。

$3.$ 存在一横一竖的两个长条。

猛然间，我们发现“**长条不交**”，于是又变得复杂了。接下来考虑一个一个判。

第一、二种情形，我们只需要预处理出以任意点为最下端、右端的点，然后计算即可。坑：当一个长条特别长时，其内部可能有多个长条！

第三种情形是最复杂的，我们考虑先枚举横条的位置。然后，我们发现竖条的摆放位置有许多个：![](https://cdn.luogu.com.cn/upload/image_hosting/poidwif6.png)
所以，我们又要开始分类讨论了。以上图为例，我们如果选定了 $EFGH$ 这个横长条，那么竖着的长条只能放在 $ABML$ 或 $AIJC$ 或 $CDNK$ 或 $BDPO$ 这 $4$ 个矩形区域内。这时，我们又发现了好性质：所有矩形区域，要么含有整一行，要门含有整一列，所以这也是预处理出来的。

于是我们把检查的部分写完了。

## Part 2 完成代码

最后，是美滋滋的代码时间：
```c
#include<bits/stdc++.h>
using namespace std;
const int maxn=1505;
char mp[maxn][maxn];
int n,shu[maxn][maxn],heng[maxn][maxn],shu1[maxn][maxn],l1[maxn],ln[maxn],h1[maxn],hn[maxn];
bool check(int k)
{
    int i,j,c1=0,l;
    for(i=1;i<=n;i++)
    {
        l=-10000;
        for(j=1;j<=n;j++)
        {
            if(heng[i][j]>=k&&j-l>=k)
            {
                l=j;
                c1++;
            }
        }
        if(c1>=2)
        {
            return true;
        }
    }
    c1=0;
    for(j=1;j<=n;j++)
    {
        l=-10000;
        for(i=1;i<=n;i++)
        {
            if(shu[i][j]>=k&&i-l>=k)
            {
                l=i;
                c1++;
            }
        }
        if(c1>=2)
        {
            return true;
        }
    }
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        {
            if(heng[i][j]>=k)
            {
                if(h1[i-1]>=k||hn[i+1]>=k||ln[j+1]>=k||l1[j-k]>=k)
                {
                    return true;
                }
            }
        }
    }
    return false;
}
int main()
{
    int l,r,i,j,mx=0,mid,m;
    scanf("%d%d",&n,&m);
    for(i=1;i<=n;i++)
    {
        getchar();
        for(j=1;j<=n;j++)
        {
            scanf("%c",&mp[i][j]);
            if(mp[i][j]=='.')
            {
                shu[i][j]=shu[i-1][j]+1;
                heng[i][j]=heng[i][j-1]+1;
                mx=max(mx,shu[i][j]);
                mx=max(mx,heng[i][j]);
            }
        }
    }
    for(i=n;i>=1;i--)
    {
        for(j=n;j>=1;j--)
        {
            if(mp[i][j]=='.')
            {
                shu1[i][j]=shu1[i+1][j]+1;
            }
        }
    }
    for(i=1;i<=n;i++)
    {
        h1[i]=h1[i-1];
        l1[i]=l1[i-1];
        for(j=1;j<=n;j++)
        {
            h1[i]=max(h1[i],shu[i][j]);
            l1[i]=max(l1[i],shu[j][i]);
        }
    }
    for(i=n;i>=1;i--)
    {
        hn[i]=hn[i+1];
        ln[i]=ln[i+1];
        for(j=1;j<=n;j++)
        {
            hn[i]=max(hn[i],shu1[i][j]);
            ln[i]=max(ln[i],shu1[j][i]);
        }
    }
    if(m==1)
    {
        printf("%d\n",mx);
    }
    else
    {
        l=0;
        r=n;
        while(l+1<r)
        {
            mid=(l+r)>>1;
            if(check(mid))
            {
                l=mid;
            }
            else
            {
                r=mid;
            }
        }
        if(check(r))
        {
            printf("%d\n",r);
        }
        else
        {
            printf("%d\n",l);
        }
    }
    return 0;
}
```
代码写得很糟糕，千万不要抄。~~当你复制过去后会发现 AC 了。~~

## Part 3 附赠的自测数据

说“谢谢你！”~~（其实样例非常强）~~。

第一组：
```c
输入：
5 2
XX.XX
XX.XX
.....
XX.XX
XX.XX

输出：
2
```
第二组：

```c
输入：
5 2
XXXXX
X...X
XX.XX
XX.XX
XXX..

输出：
2
```
祝您 AC 愉快！


---

## 作者：zaochen (赞：0)

不明白为什么讨论区有人说正解是 $O(n^2 \log n)$，我觉得有一种 $O(n^2)$ 的直接的前缀预处理 + 分类讨论解法，代码跑的飞快，是截止发题解时为止的最优解。

## 预处理

在开始分类讨论前，先预处理下面几项数据：

1. $f_h[i][j]$ 表示从第 $i$ 行第 $j$ 列开始不断向右延伸，总共可以延伸几格。如果第 $i$ 行第 $j$ 列已经是 `X` 则值为 $0$。  
2. $f_l[i][j]$ 表示从第 $i$ 行第 $j$ 列开始不断向下延伸，总共可以延伸几格。如果第 $i$ 行第 $j$ 列已经是 `X` 则值为 $0$。  

这两项的递推公式和 [[NOIP2022] 种花](https://www.luogu.com.cn/problem/P8865) 中类似，不再赘述，预处理的时间复杂度为 $O(n ^ 2)$，直接上计算代码：

```cpp
for (int i = 1; i <= n; i++)
    {
        fh[i][n] = (g[i][n] == '.');
        for (int j = n - 1; j; j--)
        {
            fh[i][j] = (g[i][j] == '.' ? fh[i][j + 1] + 1 : 0);
        }
    }
for (int j = 1; j <= n; j++)
    {
        fl[n][j] = (g[n][j] == '.');
        for (int i = n - 1; i; i--)
        {
            fl[i][j] = (g[i][j] == '.' ? fl[i + 1][j] + 1 : 0);
        }
    }
```

## Subtask 1

当 $m = 1$ 时，所有 $f_h[i][j]$ 与 $f_l[i][j]$ 的最大值就是所求答案。这部分问题求解代码如下：

```cpp
int ans = 0;

if (m == 1)
{
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            ans = max({ans, fl[i][j], fh[i][j]});
        }
}
```

## Subtask 2-4

当 $m = 2$ 时，需要找出两个互不相交的长度相同的长条。这两个长条可以分为三种情况。在开始分类讨论之前，先预处理出下面几个信息。

1. $f^h_{max}[i] = j$ 表示从第 $i$ 行所有连续的横着（$1 \times k$）的长条中，最长的一条的左端点坐标是 $(i, j)$。如果第 $i$ 行全是 `X` 则值为 $0$。  
2. $f^l_{max}[j] = i$ 表示从第 $j$ 列所有连续的竖着（$k \times 1$）的长条中，最长的一条的上端点坐标是 $(i, j)$。如果第 $j$ 列全是 `X` 则值为 $0$。  

另外，横竖交叉的情况的分类讨论中还需要预处理出次长（非严格次长）的连续长条的端点坐标。  
预处理代码如下：  
```cpp
for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
    {
        if (fh[i][j - 1] != 0 || fh[i][j] == 0) // 判断是否为左端点
            continue;
        if (fh[i][j] >= fh[i][fhmax[i]])
            fhmax2[i] = fhmax[i], fhmax[i] = j;
        else if (fh[i][j] > fh[i][fhmax2[i]])
            fhmax2[i] = j;
    }
for (int j = 1; j <= n; j++)
    for (int i = 1; i <= n; i++)
    {
        if (fl[i - 1][j] != 0 || fl[i][j] == 0) // 判断是否为上端点
            continue;
        if (fl[i][j] >= fl[flmax[j]][j])
            flmax2[j] = flmax[j], flmax[j] = i;
        else if (fl[i][j] > fl[flmax2[j]][j])
            flmax2[j] = i;
    }
```



然后可以分下面三类分别统计答案求最大值：

1. 都是横着的长条。两条横着的长条可以根据是否在同一行分类。如果都在第 $i$ 行，则答案可能是把同一个长条拆成不相交两段和一行的两个长条，即 $\max(\lfloor \frac{fh[i][f^h_{max}[i]]}{2} \rfloor, fh[i][f^h_{max2}[i]])$。如果一个在第 $i$ 行，一个在第 $j$ 行（$i \not = j$），则答案可能为 $\min(fh[i][f^h_{max}[i]],fh[j][f^h_{max}[j]])$，枚举取最大值即可，时间复杂度 $O(n^2)$
2. 都是竖着的长条，计算方法类似上一种。

这部分的代码实现如下：

```cpp
for (int i = 1; i <= n; i++)
{
    for (int j = 1; j <= n; j++)
    {
        ans = max({ans, fl[i][j] / 2, fh[i][j] / 2});         // 同一行 / 同一列 一条拆两半
        ans = max({ans, fl[flmax2[j]][j], fh[i][fhmax2[i]]}); // 同一行 / 同一列 两条
        if (i != j) // 两行或两列
            ans = max(ans, min(fh[i][fhmax[i]], fh[j][fhmax[j]])),
            ans = max(ans, min(fl[flmax[i]][i], fl[flmax[j]][j]));
    }
}
```

3. 一个横着的长条，一个竖着的长条，这部分比较复杂。设横着的长条在第 $i$ 行，竖着的长条在第 $j$ 列，则：
  - 若第 $i$ 行最长的一条横着的与第 $j$ 列最长的一条竖着的不相交，则答案 $k$ 可能取这两条长度的较小的一个。
  - 若相交，则可能是把横着的最长的长条换成次长的，就一定不会相交。或者把竖着的最长的换成次长的，这两种情况替换后长度较小的一个求一下最大值即可。
  
上面两种情况的代码实现如下：

```cpp
if (fhmax[i] > j || fhmax[i] + fh[i][fhmax[i]] - 1 < j || flmax[j] > i || flmax[j] + fl[flmax[j]][j] - 1 < i) // 不相交
    ans = max(ans, min(fh[i][fhmax[i]], fl[flmax[j]][j]));
else
{
    ans = max(ans, min(fh[i][fhmax2[i]], fl[flmax[j]][j]));
    ans = max(ans, min(fh[i][fhmax[i]], fl[flmax2[j]][j]));
}
```

- 若第 $i$ 行横着的长条和第 $j$ 列竖着的长条相交，还可能只截取横着的长条从左端点到交点左边，或者交点右边到右端点，或者竖着的长条从上端点到交点上面，或交点下面到下端点。可以看下面的图形象理解一下：  
![](https://cdn.luogu.com.cn/upload/image_hosting/ylhrh4g5.png)

这部分代码实现如下：  
```cpp
ans = max(ans, min(j - fhmax[i], fl[flmax[j]][j]));
ans = max(ans, min(fhmax[i] + fh[i][fhmax[i]] - 1 - j, fl[flmax[j]][j]));
ans = max(ans, min(fh[i][fhmax[i]], i - flmax[j]));
ans = max(ans, min(fh[i][fhmax[i]], flmax[j] + fl[flmax[j]][j] - 1 - i));
```

对于上面十二种情况，计算出每个位置对应的 $k$ 值的可能取值，取最大值即可。时间复杂度 $O(n^2)$。

完整参考代码实现如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
// #define int long long

const int N = 1505;

int n, m;
char g[N][N];

int fh[N][N], fl[N][N];
int fhmax[N], flmax[N],   // 最长的一段的端点
    fhmax2[N], flmax2[N]; // 次长的一段的端点

signed main()
{
    ios::sync_with_stdio(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cin >> g[i][j];

    for (int i = 1; i <= n; i++)
    {
        fh[i][n] = (g[i][n] == '.');
        for (int j = n - 1; j; j--)
        {
            fh[i][j] = (g[i][j] == '.' ? fh[i][j + 1] + 1 : 0);
        }
    }

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            if (fh[i][j - 1] != 0 || fh[i][j] == 0)
                continue;
            if (fh[i][j] >= fh[i][fhmax[i]])
                fhmax2[i] = fhmax[i], fhmax[i] = j;
            else if (fh[i][j] > fh[i][fhmax2[i]])
                fhmax2[i] = j;
        }

    for (int j = 1; j <= n; j++)
    {
        fl[n][j] = (g[n][j] == '.');
        for (int i = n - 1; i; i--)
        {
            fl[i][j] = (g[i][j] == '.' ? fl[i + 1][j] + 1 : 0);
        }
    }
    for (int j = 1; j <= n; j++)
        for (int i = 1; i <= n; i++)
        {
            if (fl[i - 1][j] != 0 || fl[i][j] == 0)
                continue;
            if (fl[i][j] >= fl[flmax[j]][j])
                flmax2[j] = flmax[j], flmax[j] = i;
            else if (fl[i][j] > fl[flmax2[j]][j])
                flmax2[j] = i;
        }

    int ans = 0;
    if (m == 1)
    {
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
            {
                ans = max({ans, fl[i][j], fh[i][j]});
            }
    }
    else
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                ans = max({ans, fl[i][j] / 2, fh[i][j] / 2});         // 同一行 / 同一列 一条拆两半
                ans = max({ans, fl[flmax2[j]][j], fh[i][fhmax2[i]]}); // 同一行 / 同一列 取两条
                if (i != j)
                    ans = max(ans, min(fh[i][fhmax[i]], fh[j][fhmax[j]])),
                    ans = max(ans, min(fl[flmax[i]][i], fl[flmax[j]][j]));
                // 第 i 行取一个横着的长条，第 j 列取一个竖着的长条
                if (fhmax[i] > j || fhmax[i] + fh[i][fhmax[i]] - 1 < j || flmax[j] > i || flmax[j] + fl[flmax[j]][j] - 1 < i) // 不相交
                    ans = max(ans, min(fh[i][fhmax[i]], fl[flmax[j]][j]));
                else
                {
                    ans = max(ans, min(fh[i][fhmax2[i]], fl[flmax[j]][j]));
                    ans = max(ans, min(fh[i][fhmax[i]], fl[flmax2[j]][j]));

                    ans = max(ans, min(j - fhmax[i], fl[flmax[j]][j]));
                    ans = max(ans, min(fhmax[i] + fh[i][fhmax[i]] - 1 - j, fl[flmax[j]][j]));
                    ans = max(ans, min(fh[i][fhmax[i]], i - flmax[j]));
                    ans = max(ans, min(fh[i][fhmax[i]], flmax[j] + fl[flmax[j]][j] - 1 - i));
                }
            }
        }
    }
    cout << ans << endl;

    return 0;
}
```

---

