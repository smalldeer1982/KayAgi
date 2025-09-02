# [ARC048B] AtCoderでじゃんけんを

## 题目描述

### 题意翻译

有 $n$ 个人在猜拳，每个人有一个 AtCoder 值 $r_i$，出拳出的是 $h_i$（这里规定 $1$ 是石头，$2$ 是剪刀，$3$ 是布）。

- 如果他们的 AtCoder 值不相等，AtCoder 值高的获胜。
- 如果他们的 AtCoder 值相等，猜拳赢的获胜。
- 否则平局。

现在每个人都与 $n-1$ 个人猜过了拳，求出最后的结果。

## 说明/提示

$1 \le n,r_i \le 10^5,h_i \in[1,2,3]$。

## 样例 #1

### 输入

```
6
2 1
2 2
3 2
5 3
2 2
3 3```

### 输出

```
2 3 0
0 4 1
4 1 0
5 0 0
0 4 1
3 2 0```

## 样例 #2

### 输入

```
2
1999 3
2000 1```

### 输出

```
0 1 0
1 0 0```

## 样例 #3

### 输入

```
8
3200 2
2800 3
2800 2
2700 1
2800 2
3200 1
2700 1
3200 3```

### 输出

```
6 1 0
2 5 0
3 3 1
0 6 1
3 3 1
6 1 0
0 6 1
6 1 0```

# 题解

## 作者：RioFutaba (赞：1)

# 题意
有 $n$ 个人在猜拳，给定 $r_i$（分数）和 $h_i$（出拳，$1$ 是石头，$2$ 是剪刀，$3$ 是布）每个人跟其他 $n-1$ 个人分别猜一轮。规则如下：
- 如果 $r_i$ 值相同，则猜拳赢了就获胜，出拳一样则平局。
- 否则 $r_i$ 大的获胜。

数据范围：$1\le n,r_i \le 10^5$
# 思路
考虑暴力：依次检查 $n-1$ 个人，统计答案。这样做的复杂度是 $O(n^2)$，无法通过此题。

可以想到使用桶优化。

统计分数 $\le r_i$ 的个数，用于判定赢了的情况（即分数小于 $h_i$），因为 $r_i \le 10^5 $，所以复杂度可以接受。

统计分数为 $h_i$ 所有人的出拳情况，用于判定赢了和平局（猜拳一样即平局）。

剩下的人即为输，可以用总人数减去赢和平局的人。

代码里已经有注释：

```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn=1e5+5;
int n,h[maxn],r[maxn],cnt[maxn],p[maxn],f[maxn][4];
/*
cnt[i]代表分数为i的人数
p[i]代表分数小于i的人数
f[i][j]代表分数为i,出拳为j的情况 
*/ 
int win(int y){
	if(y==1) return 2;           //石头，可以赢剪刀 
	else if(y==2) return 3;           //剪刀，可以赢布 
	else return 1;           // 布，可以赢石头 
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&r[i],&h[i]);
		cnt[r[i]]++;f[r[i]][h[i]]++;           //统计		
	}
	for(int i=1;i<=maxn;i++) p[i]=p[i-1]+cnt[i-1];           //统计 
	for(int i=1;i<=n;i++){
		int x,y,z;           //x是赢，y是负局，z是平局 
		x=p[r[i]];           //分数比自己低 
		x+=f[r[i]][win(h[i])];           //猜拳猜赢 
		z=f[r[i]][h[i]]-1;           //猜拳情况一样，要注意减去自己 
		y=n-x-z-1;           //剩下即为负，要减去自己 
		printf("%d %d %d\n",x,y,z);
	}
	return 0;
}

```

---

## 作者：hinin (赞：0)

### 思路

首先因为 $1 \le N \le 10^5$，$O(N ^ 2)$ 的暴力肯定不行。

我们认为通过按等级分组参与者，记录计算等级胜负和手动胜负所需的信息。

首先，通过取每个等级组的人数累积和，可以在线性时间内计算等级胜负结果。

另一方面，通过记录每个组内剪刀/石头/布的人数，也可以在线性时间内计算手动胜负结果。

 * 保持原始顺序，按参与者评分进行排序（本次为升序）。
 * 参与者至少 1 名符合每个比率时，记录总人数的累计和以及剪刀石头布各自的人数（非累计和）。
 * 为每位参与者计算对战结果。

### 代码

``` cpp
#include <bits/stdc++.h>
// #pragma GCC optimize("Ofast", "-funroll-all-loops")
#define ll long long
#define pii pair<int, int>

#define y1 gigay
#define x first
#define y second

using namespace std;

struct Data { int i, rate, hand, win, lose, draw; };
struct Group { int cumSum, hand1, hand2, hand3; };

int n; 
vector<Data> a; 

bool cmp1(Data a, Data b) 
{
	if (a.rate != b.rate) { return a.rate < b.rate; }
	if (a.hand != b.hand) { return a.hand < b.hand; }

	return a.i < b.i;
}
 
bool cmp2(Data a, Data b) 
{ return a.i < b.i; }
 
int main() 
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> n;

	a.resize(n); 
	for (int i = 0; i < n; i ++) {
		cin >> a[i].rate >> a[i].hand;

		a[i].i = i;
		a[i].win = 0;
		a[i].lose = 0;
		a[i].draw = 0;
	}
 
	sort(a.begin(), a.end(), cmp1);
 
	vector<Group> groups;
	Group group = {0, 0, 0, 0};
	int rateNow = 0;
 
	for (int i = 0; i < n; ++i) {
		if (a[i].rate != rateNow) {
			group.cumSum = i;
			groups.push_back(group);
			group.hand1 = 0;
			group.hand2 = 0;
			group.hand3 = 0;
			rateNow = a[i].rate;
		}
		switch (a[i].hand) {
		case 1:
			group.hand1++;
			break;
		case 2:
			group.hand2++;
			break;
		default:
			group.hand3++;
			break;
		}
	}

	group.cumSum = n;
	groups.push_back(group);
 
	int iGroup = 0;
	for (int i = 0; i < n; ++i) {
		if (i >= groups[iGroup].cumSum) { iGroup++; }
		a[i].win += groups[iGroup - 1].cumSum;
		a[i].lose += n - groups[iGroup].cumSum;
 
		switch (a[i].hand) {
		case 1:
			a[i].win += groups[iGroup].hand2;
			a[i].lose += groups[iGroup].hand3;
			a[i].draw += groups[iGroup].hand1 - 1;
			break;
		case 2:
			a[i].win += groups[iGroup].hand3;
			a[i].lose += groups[iGroup].hand1;
			a[i].draw += groups[iGroup].hand2 - 1;
			break;
		default:
			a[i].win += groups[iGroup].hand1;
			a[i].lose += groups[iGroup].hand2;
			a[i].draw += groups[iGroup].hand3 - 1;
			break;
		}
	}
 
	sort(a.begin(), a.end(), cmp2);
 
	for (auto p : a) 
	{ cout << p.win << " " << p.lose << " " << p.draw << endl; }
 
	return 0;
}
```

---

## 作者：opzc35 (赞：0)

## 题意

有 $N$ 个人玩石头剪刀布（PLUS 版）。第 $i$ 个人的能力值为 $r_i$，他出了 $h_i(h_i\subset[1,2,3])$。任意两个人 PK，能力值高的人获胜，如果能力值相同，则按石头剪刀布的方式决定胜负（1 表示石头，2 表示剪刀，3 表示布）。现在任意两个人 PK，请你求出他们胜负和平局的数量。

## 思路

先考虑暴力算法，您会得到[惊人的结论](https://atcoder.jp/contests/arc048/submissions/61620203)。

思路很简单，暴力模拟就行了。

这里有一个地方需要注意：如何判断哪些拳可以战胜当前出拳。我们通过找规律可以得到：$h_i$ 可以战胜 $h_i\bmod3+1$。

再来考虑优化算法。

由于题目中给出了 $a_i\le10^5$ 这个条件，我们可以考虑开 $10^5$ 长度的数组。也就是桶（后文中用 $T$ 来表示这个桶）。

我们可以令 $T_i$ 为能力值 $<i$ 的人的数量。

我们令 $vis_{i,j}$ 为能力值为 $i$，出拳 $j$ 的人的数量。

我们又知道一个数量关系：$win_i+lose_i+draw_i = n-1$

（$win_i$ 为获胜数量，$lose_i$ 为失败数量，$draw_i$ 为平局数量）。

所以 $lose_i = n - 1 - win_i - lose_i$。

所以我们得到了三个关系：

$win_i = t_i + vis_{r_i,{h_i\bmod3+1}}$

$draw_i = vis_{r_i,h_i}-1$

$lose_i = n - 1 - win_i - draw_i$

## [代码](https://atcoder.jp/contests/arc048/submissions/61620938)

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int r[100005],h[100005];
int win[100005],lose[100005],draw[100005];
int cnt[100005],tmp[100005];
int vis[100005][4];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>r[i]>>h[i];
		tmp[r[i]]++;
		vis[r[i]][h[i]]++;
	}
	for(int i=1;i<=100000;i++){
		cnt[i]=cnt[i-1]+tmp[i-1];
	}
	for(int i=1;i<=n;i++){
		win[i]=cnt[r[i]];//分数小于他的
		win[i]+=vis[r[i]][h[i]%3+1];
		draw[i]+=vis[r[i]][h[i]]-1;//自己这一个肯定不算
		lose[i]=n-win[i]-draw[i]-1;//总共PKn场，失败的数量=总场数-获胜场数-平局场数
	}
	for(int i=1;i<=n;i++){
		cout<<win[i]<<" "<<lose[i]<<" "<<draw[i]<<endl;
	}
	return 0;
}
```

---

## 作者：Night_fall (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_arc048_b)

打暴力是 $O(n^2)$ 的复杂度，$10^5$ 的数据下肯定过不了，考虑其他做法。

------------

可以先进行排序，对于 Atcoder 值小于或大于自己的进行求前、后缀和批量处理，其余再猜拳，可以快很多。

具体流程如下：

1. 读入，用一个数组统计每个 $r_i$ 中 $h_i$ 个数，并按 $r_i$ 排序。

2. 求出不同 $r$ 值的胜局和负局。

3. 处理 $r$ 相同时猜拳。

4. 再变回原本顺序，并输出。

复杂度最高是排序部分，是 $O(n\log n)$。

------------

## Code

代码中有注释。

```cpp
#include<bits/stdc++.h>
using namespace std;

struct node{
	int r,h,id;
	int a[4];
} a[100010];
int h[100010][4];
int last[100010];
int score[4][4]={
	{0,0,0,0},
	{0,2,1,3},
	{0,3,2,1},
	{0,1,3,2},
}; //不想写if了，直接打表

bool cmp(node x, node y){return x.r<y.r;}
bool cmp2(node x, node y){return x.id<y.id;}

int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		scanf("%d%d",&a[i].r,&a[i].h);
		h[a[i].r][a[i].h]++; //统计出拳个数方便批量处理猜拳
		a[i].id=i;
	}
	sort(a+1,a+n+1,cmp); //按r值排序
	int cnt=0; //前缀和变量
	for(int i=n;i;i--){
		if(a[i].r!=a[i+1].r) last[a[i].r]=i; //后缀和
	}
	for(int i=1;i<=n;i++){
		if(i!=1&&a[i].r!=a[i-1].r) cnt=i-1; 
		a[i].a[1]=cnt+h[a[i].r][score[a[i].h][1]]; //求胜场
		a[i].a[2]=h[a[i].r][score[a[i].h][2]]-1; //求平场
		a[i].a[3]=n-last[a[i].r]+h[a[i].r][score[a[i].h][3]]; //求负场
	}
	sort(a+1,a+n+1,cmp2); //变回原来顺序
	for(int i=1;i<=n;i++) printf("%d %d %d\n",a[i].a[1],a[i].a[3],a[i].a[2]);
    return 0;
}
```

于是我们就可以得到：
![](https://cdn.luogu.com.cn/upload/image_hosting/albkoy7s.png)

---

## 作者：hellolin (赞：0)

[题面(洛谷)](https://www.luogu.com.cn/problem/AT_arc048_b)

[题面(AtCoder)](https://atcoder.jp/contests/arc048/tasks/arc048_b)

AtCoder Problems 评级难度：$\texttt{\color{#46ffff}{1290}}$。

## 思路

对于每一级 AtCoder 值，我们设 $x$ 为比当前 AtCoder 值低的人数，$a$ 为出石头人数，$b$ 为出剪刀人数，$c$ 为出布人数，则对于每一个 AtCoder 值在这级的人：

- 出石头，胜场为 $b+x$，平场为 $a-1$，输场为 $N-x-a-b$；
- 出剪刀，胜场为 $c+x$，平场为 $b-1$，输场为 $N-x-b-c$；
- 出布，胜场为 $a+x$，平场为 $c-1$，输场为 $N-x-a-c$。

统计完成后，可以直接输出。

复杂度约为 $O(\max{(N,\max{(R)})})$。

## 代码

``` cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
const static int N = 114514;
int n,tmp,tmp_,x,s;
// 1 石头 / 2 剪刀 / 3 布
struct p
{
    int a,b,c;
    int w[4],l[4],f[4]; // 胜场，输场，平场
}c[N];
vector<pair<int,int>>id;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>tmp>>tmp_;
        
        s=max(s,tmp);
        id.push_back({tmp,tmp_});

        p&j=c[tmp];
        if(tmp_==1)++j.a;
        else if(tmp_==2)++j.b;
        else ++j.c;
    }
    for(int i=1;i<=s;i++)
    {
        p&j=c[i];

        j.w[1]=j.b+x;
        j.l[1]=n-j.a-j.b-x;
        j.f[1]=j.a-1;

        j.w[2]=j.c+x;
        j.l[2]=n-j.c-j.b-x;
        j.f[2]=j.b-1;

        j.w[3]=j.a+x;
        j.l[3]=n-j.a-j.c-x;
        j.f[3]=j.c-1;

        x+=j.a+j.b+j.c;
    }
    for(auto i:id)
        cout<<c[i.fi].w[i.se]<<' '<<c[i.fi].l[i.se]<<' '<<c[i.fi].f[i.se]<<endl;
    return 0;
}
```

---

## 作者：TheSky233 (赞：0)

## Description

有 $n$ 个人在猜拳，每个人有一个 AtCoder 值 $r_i$，出拳出的是 $h_i$（这里规定 $1$ 是石头，$2$ 是剪刀，$3$ 是布）。

- 如果他们的 AtCoder 值不相等，AtCoder 值高的获胜。
- 如果他们的 AtCoder 值相等，猜拳赢的获胜。
- 否则平局。

现在每个人都与 $n-1$ 个人猜过了拳，求出最后的结果。

## Solution

因为 $1 \le n \le 10^5$，$\Theta(n^2)$ 的暴力显然会 T，考虑优化。

我们可以先按 $r_i$ 为第一关键字，$h_i$ 为第二关键字排序，保持 $r_i$ 整体有序，这样就可以在 $\Theta(\log n)$ 的时间内统计出小于（或大于）当前 $r_i$ 的人。

同时因为在 $r_i$ 相同的每一段内，$h_i$ 是有序的，我们又可以用 $\Theta(\log n)$ 的时间统计出当前 $h_i$ 能够赢（或输）多少人。

最后因为每个人比了 $n-1$ 次，平局次数即为 $(n-1)-c_1-c_2$，其中 $c_1$ 为赢的次数，$c_2$ 为输的次数。

时间复杂度：$\Theta(n \log n)$，可以通过本题。

## Code

```cpp
#include<bits/stdc++.h>
#define F(i,a,b) for(int (i)=(a);(i)<=(b);++(i))
using namespace std;

const int N=100000+5;

struct atcoder{
	int r,h,id;
}a[N];
int n;
int lose[N],win[N],draw[N];

int nxt(int k){ // 能赢谁
	return (k+1==4)?1:k+1;
}

int bef(int k){ // 会输给谁
	return (k-1==0)?3:k-1;
}

int binary_search1(int lvl,int pos){ // 查找 r[i] 相同的第一个下标
	int l=pos,r=n,mid=0,ans=0;
	while(l<=r){
		mid=(l+r)>>1;
		if(a[mid].r>lvl) r=mid-1;
		else l=mid+1,ans=mid;
	}
	return ans;
}

int binary_search2(int lvl,int pos){ // 查找 r[i] 相同的最后一个下标
	int l=1,r=pos,mid=0,ans=0;
	while(l<=r){
		mid=(l+r)>>1;
		if(a[mid].r<lvl) l=mid+1;
		else r=mid-1,ans=mid;
	}
	return ans;
}

int binary_search3(int l,int r,int which){ // 在 [l,r] 区间内查找 which 出现的次数
	int mid=0,ansl=-1,ansr=-1;
	int L=l,R=r;
	while(l<=r){
		mid=(l+r)>>1;
		if(a[mid].h<which) l=mid+1;
		else r=mid-1,ansl=mid;
	}
	if(ansl==-1) return 0;
	l=L,r=R;
	while(l<=r){
		mid=(l+r)>>1;
		if(a[mid].h>which) r=mid-1;
		else l=mid+1,ansr=mid;
	}
	if(ansr==-1) return 0;
	return (ansr-ansl+1);
}

int main(){
	scanf("%d",&n);
	F(i,1,n) scanf("%d%d",&a[i].r,&a[i].h),a[i].id=i;
	sort(a+1,a+n+1,[](atcoder a,atcoder b){
		return (a.r==b.r)?a.h<b.h:a.r<b.r;
	});
	F(i,1,n){
		int lstlvl=binary_search1(a[i].r,i);
		int fstlvl=binary_search2(a[i].r,i);
		win[a[i].id]+=(fstlvl-1); //r[i]
		lose[a[i].id]+=(n-lstlvl); //r[i]
		win[a[i].id]+=binary_search3(fstlvl,lstlvl,nxt(a[i].h)); //h[i]
		lose[a[i].id]+=binary_search3(fstlvl,lstlvl,bef(a[i].h)); //h[i]
	}
	F(i,1,n) printf("%d %d %d\n",win[i],lose[i],n-1-win[i]-lose[i]);
}
```

---

