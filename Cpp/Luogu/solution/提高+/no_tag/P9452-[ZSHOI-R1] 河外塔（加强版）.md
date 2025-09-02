# [ZSHOI-R1] 河外塔（加强版）

## 题目背景

河内塔（又称汉诺塔）问题，就是在一块木板上有三个立柱，在柱 1 上放着三个圆盘，小的在上面，大的在下面（初始状态）。让被试将在柱 1 上的三个圆盘移到柱 3 上面（目标状态）。条件是：每次只能移动任何一个柱子上面的一个圆盘，但大的圆盘不能放在小的圆盘上。

通用问题解决者的解决过程即是手段——目的分析的策略。

## 题目描述

但是，你可能没有听过河外塔问题。虽然但是，好像并没有河外塔问题。于是，伟大的 X_Xy 决定创造一个河外塔问题。

既然是河内塔问题的延申，就得有些一样的东西：有三个柱子 
$A$，$B$ 和 $C$ ，以及 $n$ 个圆盘，其中编号为 $i$ 的圆盘的半径长为 $i$，这些圆盘最开始都在 $A$ 上，最终都要顺序（即从上往下从小到大）地移到 $C$ 上。

既然是河内塔问题的延伸，就得有些不同的东西：最开始在 $A$ 上面的圆盘并不是顺序的，由于这个限制，我们也不在意移动过程中的顺序，也就意味着你可以将一个大的圆盘放在小的圆盘上。

但是 X_Xy 很懒，他只想让你操作至多 $10^6$ 次。

## 说明/提示

对于所有数据点：$1\leqslant n \leqslant 4\times 10^4$

| 数据点 | n |
| :----------: | :----------: |
| 1~2 | $\leqslant 10$ |
| 3~4 | $\leqslant 200$ |
| 5~7 | $\leqslant 3\times 10^4 $ |
| 8~10 | $\leqslant 4\times 10^4 $ |

## 样例 #1

### 输入

```
3
1 2 3```

### 输出

```
5
A B
A B
A C
B C
B C```

# 题解

## 作者：聊机 (赞：5)

在高铁上过掉了这个题，因为没看到有人写题解，所以来填补一下空白。

#### 做法：归并排序+卡常

首先数据范围要求我们用 $\log$ 级的算法来解决这道题目，很显然的想到归并排序，可是当我细写的时候就发现并没有“排序套皮”这么简单。

$n$ 的范围是 $4\times10^4$，而操作次数要求我们 $ 10^6$ 以内，这就要求我们常数要在 $1.5$ 倍以内，这对我这种弱鸡来说是非常困难的，如果我们按照归并的常规思路来思考，每次分成两半，我们为给下半部分排序，一定要把上半部分扔出去，这是 $0.5$ 倍的常数，然后分开排好序以后，把这两半合到一起的时候需要 $1$ 倍的常数，把它们合到新的柱子上以后，再一起扔回原来的柱子，又需要 $1$ 倍的常数，总计是 $2.5$ 倍，这样我们保证了递归的每一层都是相同的大小顺序，但是常数太大。

我们需要把刚才的最后一次合并剪掉，这样常数才能满足要求。

如果我们不进行最后一次合并，那就说明我们进行排序完以后的这一段不在原本的柱子上，那你一开始分开的那两段排序完以后也不会在原本的柱子上，我们需要保证它们不会重叠在一起，所以我们需要规定一下让这两段排序完以后都去到哪个柱子，我们设当前这一段所在的柱子是 $p$，要去 $to$ 柱子，我们一开始要把前半段扔到 $to$ 柱子上，然后让后半段合并到 $3-p-to$ (就是另外一根柱子上），再让扔出去的前半段合并到 $p$ 柱子上，最后我们再把这两段合并到 $to$ 柱子上。我们还要注意的是，因为我们只进行了一次合并，所以顺序会颠倒，我们需要让每相邻的两层的排序方式相反。

AC code：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=4e4+2;
int n,a[N];
int tot,a1[N*50],a2[N*50];
#define endl '\n'
#define move(a,b) a1[++tot]=a,a2[tot]=b
#define put(a,b) cout<<(char)('A'+a)<<' '<<(char)('A'+b)<<endl
inline bool comp(int o,int x,int y) {
	if(o) return x>=y;
	else return y>=x;
}
bool cmp(int x,int y) {
	return x>y;
}
void divid(int p,int l,int r,int to,int o) {//参数意义同分析
	if(l==r) {
		move(p,to);
		return ;
	}
	int mid=(l+r)>>1,p2=3-to-p;
	for(int i=l;i<=mid;i++) move(p,to);
	for(int i=l,j=mid;i<=j;i++,j--) swap(a[i],a[j]);//这个reserve千万不要忘记！
	divid(p,mid+1,r,p2,o^1);
	divid(to,l,mid,p,o^1);
	int i=l,j=mid+1;
	while(i<=mid&&j<=r) {
		if(comp(o,a[i],a[j])) move(p,to),++i;
		else move(p2,to),++j;
	}
	while(i<=mid) move(p,to),++i;
	while(j<=r) move(p2,to),++j;
	if(o) stable_sort(a+l,a+r+1);
	else stable_sort(a+l,a+r+1,cmp);
}
int main() {
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	divid(0,1,n,2,1);
	cout<<tot<<endl;
	for(int i=1;i<=tot;i++) put(a1[i],a2[i]);		
	return 0;
} 
```


说实话卡常这一部分我想了很久，就从卡常这一点来说，我认为这还是一道很不错的构造题的。

题外话：建议管理更新一下提交记录，把弱化版的记录删除掉，这样我们才能看到更多关于这题更好的做法。

---

## 作者：Lucky_Xiang (赞：4)

# 题目

[P9452](https://www.luogu.com.cn/problem/P9452)

# 思路

可以按照归并排序的思路进行操作。先把柱子上所有圆盘按照大小分为两堆，再递归排序，最后合并。

但是，合并时如果放回原位总操作次数是 $2n\log n$，只能得到 70 分。为节省操作次数，考虑将排好后的一堆直接移到另一堆上，操作次数 $1.5n\log n$。而这样操作后一定不会把圆盘放回原位，可能会使排序混乱，因此必须合理安排合并后的堆的位置、排序方式（顺序或倒序）以及递归顺序，使得各层排序之间互不干扰。

------

例如，我们要把第一堆的圆盘**顺序**排列后放至第三堆，合理的安排如下：


1. 将较大的圆盘放至第二堆，将较小的圆盘放至第三堆。

2. 将第三堆的圆盘**倒序**排列后放至第一堆。

3. 将第二堆的圆盘**顺序**排列后放至第三堆。

4. 将刚刚放在第一堆的圆盘全部移至第三堆。

------
其中第 2、3 步是通过递归实现的，安排方式也是类似的，只需把其他堆当作第一堆即可。

# 代码
```cpp
int n,x;
vector<int>v[3];
struct state
{
	int fr,to;
};
vector<state>res;
void move(int x,int y)
{
	res.push_back({x,y});
	v[y].push_back(v[x].back());
	v[x].pop_back();
}
int nxt(int x,int k)
{
	return (x+k)%3;
}
void solve(int p,int L,int R,bool op,int k)
{
	//p 表示要排序的堆。
	//L,R 表示排序的范围。
	//op 表示排序方式：op=0 时为顺序排列，op=1 时为倒序排列。
  	//k 表示排好序后堆的位置：k=1 时为 p 的下一堆，k=2 时为 p 的上一堆。
	if(L==R)
	{
		move(p,nxt(p,k));
		return;
	}
	int mid=(L+R)>>1;
	if(!op)
	{
		for(int i=L;i<=R;i++)
		{
			if(v[p].back()<=mid)move(p,nxt(p,k));
			else move(p,nxt(p,3-k));
		}
		solve(nxt(p,k),L,mid,op^1,3-k);
		solve(nxt(p,3-k),mid+1,R,op,3-k);
		for(int i=L;i<=mid;i++)move(p,nxt(p,k));
	}
	else
	{
		for(int i=L;i<=R;i++)
		{
			if(v[p].back()>mid)move(p,nxt(p,k));
			else move(p,nxt(p,3-k));
		}
		solve(nxt(p,k),mid+1,R,op^1,3-k);
		solve(nxt(p,3-k),L,mid,op,3-k);
		for(int i=mid;i<R;i++)move(p,nxt(p,k));
	}
}
int main()
{
	n=read();
	for(int i=1;i<=n;i++)v[0].push_back(x=read());
	reverse(v[0].begin(),v[0].end());
	solve(0,1,n,0,2);
	write(res.size(),1);
	for(auto k:res)
	{
		putchar(k.fr+'A');
		putchar(' ');
		putchar(k.to+'A');
		puts("");
	}
	return 0;
}
```

---

## 作者：鱼跃于渊 (赞：0)

## 做法：
数据加强了啊，$O(n^2)$ 的排序已经不行了，只能使用 $O(n\log n)$ 的排序。
于是我们可以考虑按照归并的思路来进行操作，先按大小分为两组，再递归处理，最后合并。但是普通的归并排序显然操作次数最大会超过 $10^6$ 的限制。  
为了节省操作次数，我们考虑直接将分开的两组合并到一块，这样可以减少 $1$ 倍的常数。  
但是这样会使得排序混乱，于是我们合理地安排合并后的圆盘堆所处的位置。  
举个例子，我们把第 $u$ 柱的圆盘排序后放至第 $v$ 柱，操作如下：  
1. 将前半段放至第 $v$ 柱，后半段放至第 $w$ 柱（即另一根柱子）。  
2. 将前后两段继续递归排序，其中前半段要合并到第 $u$ 柱上。  
3. 将前后两段合并到第 $v$ 柱。  
  
**tip**：由于我们省去了一次合并，所以顺序会颠倒，也就是说我们要让递归中相邻两层的排序方向相反。

## 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=4e4+5;
struct node{
	int x,y;
};
int n,a[N];
vector <node> ans;
void move(int u,int v){
	ans.push_back({u,v});
}
bool cmp(bool op,int x,int y){
	return (!op)^(x>y);
}
void solve(bool op,int l,int r,int u,int v){
	if(l==r){
		move(u,v);
		return;
	}
	int mid=(l+r)>>1,w=3-u-v;
	for(int i=l;i<=mid;i++) move(u,v);
	reverse(a+l,a+mid+1);
	solve(op^1,mid+1,r,u,w);
	solve(op^1,l,mid,v,u);
	int i=l,j=mid+1;
	while(i<=mid&&j<=r){
		if(cmp(op,a[i],a[j])){
			move(u,v);i++;
		}else{
			move(w,v);j++;
		}
	}
	for(;i<=mid;i++) move(u,v);
	for(;j<=r;j++) move(w,v);
	stable_sort(a+l,a+r+1);
	if(!op) reverse(a+l,a+r+1);
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	solve(1,1,n,0,2);
	cout<<ans.size()<<'\n';
	for(auto x:ans)
		cout<<char(x.x+'A')<<' '<<char(x.y+'A')<<'\n';
    return 0;
}
```

---

