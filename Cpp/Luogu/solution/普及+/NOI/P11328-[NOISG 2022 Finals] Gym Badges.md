# [NOISG 2022 Finals] Gym Badges

## 题目描述

你是一只初始等级为 $0$ 的 $\text{Wabbit}$。你希望到 $n$ 个比赛中提升自己的实力，并收集这些比赛的徽章。

目前将要举行的比赛共有 $N$ 个。第 $i$ 个比赛可以用 $L_i$ 和 $X_i$ 来描述。如果你的当前等级 $\le L_i$，那么你可以参加第 $i$ 个比赛，让自己的等级提升 $X_i$ 并获得一个徽章。

你可以以任意顺序参加这些比赛。求出如果按照最佳顺序参加，你最多可以获得多少个徽章。

## 说明/提示

**【样例 #1 解释】**

一种最优的参加方式为 $3 \to 4 \to 1 \to 5$。

**【样例 #2 解释】**

一种最优的参加方式为 $1 \to 3 \to 4 \to 2$。

**【数据范围】**

|$\text{Subtask}$|分值|特殊性质|
|:-:|:-:|:-:|
|$0$|$0$|样例|
|$1$|$15$|$1\le N\le10$|
|$2$|$9$|所有 $L_i$ 均相等|
|$3$|$27$|$1\le N\le5000$|
|$4$|$49$|无|

对于 $100\%$ 的数据，$1 \le N \le 5 \times 10 ^ 5, 1 \le X_i, L_i \le 10 ^ 9$。

## 样例 #1

### 输入

```
5
4 6 3 5 2
10 6 4 8 12
```

### 输出

```
4```

## 样例 #2

### 输入

```
5
3 9 4 2 6
10 10 10 10 10```

### 输出

```
4```

# 题解

## 作者：ycy1124 (赞：9)

### 题意
题面很详细，注意一下是先过关再升级。
### 思路
很一眼的返回贪心，难点在于开始时的排序。

首先很容易被题目误导想到按 $l_i$ 从小到大排序，可这是错的。因为你通过的最后一个比赛并不需要通过后等级尽量小，所以会错。

考虑换一种排序方式，按 $x_i+l_i$ 从小到大排序。证明：当你什么时候会更换两场比赛的顺序呢。显然是你先选上一场比赛就无法比下一场，交换后两场都可以比。这种情况即 $x_i+sum>l_j$ 且 $x_j+sum<l_i$，也就等于按 $x_i+l_i$ 排序。

接下来考虑反悔贪心，当当前这一个比赛无法满足时，显然替换掉前面比赛中 $x$ 值最大的一场，于是可以拿个大根堆来维护。
### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct Node{
    int x,l;
}a[500005];
int b[500005];
int n,tot,sum;
inline bool cmp(Node x1,Node x2){
    return x1.l+x1.x<x2.l+x2.x;
}
inline void work1(int x){
    if(x*2+1<=tot&&b[x*2+1]>b[x]&&b[x*2]<b[x*2+1]){
        swap(b[x],b[x*2+1]);
        work1(x*2+1);
    }
    else if(x*2<=tot&&b[x*2]>b[x]){
        swap(b[x*2],b[x]);
        work1(x*2);
    }
}
inline void work(int x){
    if(x!=1&&b[x]>b[x/2]){
        swap(b[x],b[x/2]);
        work(x/2);
    }
}
signed main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i].x;
    }
    for(int i=1;i<=n;i++){
        cin>>a[i].l;
    }
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n;i++){
        if(sum>a[i].l){
            if(b[1]>a[i].x){
                swap(b[1],b[tot]);
                sum-=b[tot];
                --tot; 
                work1(1);
                b[++tot]=a[i].x;
                sum+=b[tot];
                work(tot);
            }
        }
        else{
            sum+=a[i].x;
            b[++tot]=a[i].x;
            work(tot);
        }
    }
    cout<<tot;
    return 0;
}
```
[AC 记录。](https://www.luogu.com.cn/record/200350069)

---

## 作者：niumachaoren (赞：6)

## 前言
忘了

## 题目大意

有 $n$ 个物品，每个物品有截止时间 $l_i$ 以及耗时 $x_i$，问最多能选出多少物品满足条件。

## 思路

看着题目长得就非常像[P4053](https://www.luogu.com.cn/problem/P4053)，都是有一个物品耗时和截止时间，但是请注意，这道题的不同之处在于 **物品可以先判定截止时间，再将耗时计入总和** （本人赛时看错了耽误了时间）。

首先我们读题到这里大概能想到一个反悔贪心的思路，所以要先确定排序关键字，拍了几组数据后发现，**无论是直接按 $l_i$ 排序还是直接按 $x_i$ 排序都比较容易丢失一些更新信息**，所以考虑推式子，进行愉快的邻项交换法。

考虑有物品 $i$ 和物品 $j$，当前相对位置是 $i$ 在 $j$ 之前，并且枚举到 $j$ 时，前面物品耗时总和是 $sum$（不含 $x_i$）。那么此时将 $i$,$j$ 交换更优当且仅当：
$$
  sum+x_i>l_j
$$
$$
  sum+x_j\leq l_i
$$
理解起来也很简单，**交换前枚举到 $j$ 时无法选择了，而交换之后两者都可以选择**。

进行移项后有

$$
  l_j-x_i < sum \leq l_i-x_j
$$
即
$$
  l_j+x_j<l_i+x_i
$$

于是按照 $l+x$ 关键字升序排序，进行贪心。

具体贪心方法就是，如果当前 $sum \leq l_i$，直接加入该物品会使答案更优，所以直接毫不犹豫的去加入。只有当前 $sum>l_i$ 时，无论如何操作都无法使答案更优，所以我们此时唯一能做的就是在使答案不会更劣的前提下令 $sum$ 尽可能的小，因为这样做可以令之后的决策空间更大。

所以等同于选择一个之前选择过的最劣（即最大的） $x_j$ 且 $x_j>x_i$，令其与枚举到的 $x_i$ 交换即可。这样能在保证答案不减的前提下 $sum$ 尽可能的小。考虑优先队列优化，边枚举边入队，要交换时弹出队头计算再将当前的入队即可。


```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
inline void read(int &x){
	x=0;char ch=getchar();
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
}
const int maxn=1e6+10;
using namespace std;
struct node{
	int l,x;
	bool operator<(node b){
		return x+l<b.x+b.l;
	}
}a[maxn];
int n;
priority_queue<int>q;	
signed main(){
	read(n);
	for(int i=1;i<=n;i++)read(a[i].x);
	for(int i=1;i<=n;i++)read(a[i].l);
	sort(a+1,a+1+n);
	int sum=0;
	for(int i=1;i<=n;i++){
		int x=a[i].x,l=a[i].l;
		if(sum<=l){
			sum+=x;
			q.push(x);
		}
		else {
			if(x<q.top()){
				sum+=(x-q.top());
				q.pop();
				q.push(x);
			}
		}
	}
	cout<<q.size();
	return 0;
}
```

---

## 作者：yi_hr (赞：5)

## 思路
### 反悔贪心
本题属于贪心题，而贪心主要分为两个主要部分，分别是贪心序与贪心策略，那下面我们就从这两个方面分析以下这个题。  

**贪心序：** 本题考虑对每个比赛的 $X_i + L_i$ （即完成比赛后的最大等级）升序排序，这样每次选完成后最小的比赛一定在当前为止最优。  

**贪心策略：** 我们遍历每一个比赛，若满足 $L_i$ 大于等于当前已选择的比赛的最大完成等级，即可以选则此比赛，直接选择。否则，若之前已完成的比赛的最大的 $X_i$ 大于当前比赛的比赛所获得的 $X_i$，穿越回比赛这个最大等级比赛时间前，反悔一下，将此最大比赛替换为我们选中的比赛。  
## 实现
我们可以用一个堆（priority_queue）来记录我们已选择的比赛中的最大获得的等级 $X_{max}$，选择新比赛时直接加入堆中，每次返回堆顶即 $X_{max}$。  
## 代码
```cpp
#include<bits/stdc++.h>
#define check (!q.empty())&&(q.top()>t.xi)&&(tt-q.top()<=t.li)
using namespace std;
const int N=5e5+5;
int n;
priority_queue<int> q;
struct node{
	int xi,li;
	bool operator <(const node &x)const{
		return xi+li<x.xi+x.li;
	}
}a[N],t;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int tt=0,cnt=0;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].xi;
	}
	for(int i=1;i<=n;i++){
		cin>>a[i].li;
	}
	sort(a+1,a+1+n);
	for(int i=1;i<=n;i++){
		t=a[i];
		if(tt<=t.li){ 
			tt+=t.xi;
			q.push(t.xi);
			cnt++;
		}else if(check){
			tt+=t.xi-q.top();
			q.pop();
			q.push(t.xi);
		}
	}
	cout<<cnt;
	return 0;
}
```

---

## 作者：fish_love_cat (赞：2)

五倍经验：P12916，P11457，P11328，P4053，AT_cf17_final_d

---

把题目转化成截止时间和耗时就好理解了。

把比赛视作任务，升级视作耗时，那么每个任务都有一个截止时间 $L_i+X_i$。

于是有贪心思路，让截止时间急的优先完成。

但这是错的，有一个完不成了，那么无论如何都会少一个任务，于是不一定舍弃当前任务，可以贪心的找一个前面很长的任务扔掉节约时间。

于是套一个优先队列，做完了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct fish{
    int fix,ed;
    bool operator <(const fish &x)const{
        return fix<x.fix;
    }
    int id,st;
}a[1500005];
bool cmp(fish x,fish y){
    return x.ed<y.ed;
}
priority_queue<fish>q;
int sum;
vector<fish>ans;
signed main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
    cin>>a[i].fix;
    for(int i=1;i<=n;i++)
    cin>>a[i].ed,a[i].id=i,a[i].ed+=a[i].fix;
    sort(a+1,a+1+n,cmp);
    for(int i=1;i<=n;i++){
        a[i].st=sum+1;
        sum+=a[i].fix;
        q.push(a[i]);
        while(sum>a[i].ed)
        sum-=q.top().fix,q.pop();
    }
    cout<<q.size()<<'\n';
    // int st=1;
    // while(!q.empty())ans.push_back(q.top()),q.pop();
    // sort(ans.begin(),ans.end(),cmp);
    // for(int i=0;i<ans.size();i++)cout<<ans[i].id<<' '<<st<<'\n',st+=ans[i].fix;
    return 0;
}
```

---

## 作者：why17 (赞：2)

~~总感觉做过一道类似的题，但记不清是啥了……~~

### 题目分析：
题目大意是有 $N$ 场比赛，每场比赛有一个参加的前提 $L$，当前等级**小于等于**此值才能参加该比赛。每场比赛还有一个 $X$，即参加完该比赛可以增加的等级。现在问怎样安排参赛顺序才能使参加的比赛场次最多。

### 解题思路：
很容易想到贪心，但是再仔细一想：贪心是将局部最优解作为整体最优解，而在这道题目中，局部最优**不一定**就是全局最优。

这个时候就要用到**反悔贪心**了。顾名思义，就是在选择过程中可以“反悔”，如果枚举到后面发现前面的选择并非最优，则可以对之前的局部最优解进行修改。

### 实现步骤：
首先对每个比赛的 $L$ 和 $X$ 进行排序处理。将 $L+X$ 按从小到大的顺序排列，如果相等就按照 $X$ 从小到大排列（肯定要先参加增加等级少的比赛，这样可以参加更多的比赛）

接下来遍历排序后的比赛。我们可以维护一个优先队列（最大堆），储存当前已经选择参加的比赛。再使用一个变量 $lev$ 来累加当前的等级。如果当前等级小于等于比赛的等级要求 $L$，就直接参加该比赛，把这场比赛的 $X$ 加入到优先队列中。如果当前等级超过了比赛的等级要求，就往前找，看有没有已经在优先队列中（即已经被选择的比赛）的 $X$ 值比当前比赛的 $X$ 值大。如果有，就把前面的那场比赛从队列里踢出来，把新的比赛加进去（注意要修改 $lev$ 的值）。

最后附上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
struct node{
	int l,x;
}c[500005];
bool cmp(node a,node b){
	if(a.l+a.x==b.l+b.x) return a.x<b.x;
	return a.l+a.x<b.l+b.x;
}
priority_queue<int> q;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>c[i].x;
    for(int i=1;i<=n;i++) cin>>c[i].l;
    sort(c+1,c+n+1,cmp);
    int lev=0;
    for(int i=1;i<=n;i++){
    	if(lev<=c[i].l){
    		q.push(c[i].x);
    		lev+=c[i].x;
		}
		else{
			if(!q.empty()&&q.top()>c[i].x){
				lev-=q.top();
				q.pop();
				lev+=c[i].x;
				q.push(c[i].x);
			}
		}
	}
	cout<<q.size();
    return 0;
}
```

---

## 作者：lam_dyr (赞：2)

# P11328 \[NOISG 2022 Finals] Gym Badges 题解

### [原题传送门](https://www.luogu.com.cn/problem/P11328)

## 题意

输入：输入包含比赛的数量 $N$，每个比赛的等级提升值 $X_i$ 和参加等级限制 $L_i$。

初始等级：初始等级为 $0$。

参加条件：只有当当前等级小于等于 $L_i$ 时，才能参加第 $i$ 个比赛，参加后等级提升 $X_i$。

目标：找到参加比赛的最佳顺序，使得获得的徽章数量最多。

输出：输出最多可以获得的徽章数量。

## solution

第一眼看到这题：最优方案？绿题？~~那 90% 是 dp 了…~~

于是我打了**~~基于动态规划的贪心选择~~** /kk

状态定义：$dp_{i,j}$ 表示考虑前 $i$ 个比赛，当前等级为 $j$ 时，最多可以获得的徽章数量。

排序：按照 $l + x$ 的值升序排序所有比赛。排序的目的是为了在后续的动态规划过程中，优先考虑那些更早可以参加的比赛。

动态转移：对于每个比赛 $i$，有两种选择：

- 不参加比赛 $i$：$dp_{i,j} = dp_{i-1,j}$。
- 参加比赛 $i$：如果当前等级 $j$ 大于等于比赛的等级限制 $l_i$，则可以参加比赛。$dp_{i,j + x_i} = \max (dp_{i,j + x_i}, dp_{i-1,j} + 1)$。

结果： 最终答案是 $\max (dp_{n,j})$，其中 $j$ 取所有可能的等级值。

优化：
由于等级值可能很大，不能直接使用二维数组来存储 $dp$ 数组。因此，可以使用一个 `map` 来动态存储 $dp$ 值。

另外，我们只需要记录当前可以达到的等级，不需要记录所有可能的等级。

****喜提 15pts。****

[提交记录](https://www.luogu.com.cn/record/196107319)

看来 dp 不可行。~~看了眼题解~~，考虑贪心。

### 全新思路：基于优先队列的反悔贪心

排序：按照 $l + x$ 的值升序排序所有比赛。

优先队列：使用优先队列（大根堆）来维护当前选择的比赛，优先队列中存储的是比赛的 $x$ 值。

贪心选择：遍历所有比赛，如果当前等级 $lvl$ 小于等于比赛的等级限制 $l_i$，则直接参加比赛，更新等级 $lvl$，并将比赛的 $x$ 值加入优先队列。

如果当前等级 $lvl$ 大于比赛的等级限制 $l_i$，则尝试进行反悔操作。

反悔操作：如果优先队列不为空，且优先队列中最大的 $x$ 值大于当前比赛的 $x$ 值，则进行反悔操作：
将当前等级 $lvl$ 减去优先队列中最大的 $x$ 值，再加上当前比赛的 $x$ 值。
将优先队列中最大的 $x$ 值弹出，并将当前比赛的 $x$ 值加入优先队列。

结果：最终的徽章数量就是参加的比赛数量。

## Code

```cpp
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
struct Gam {
    int x;
    int l;
    int id;
};
bool cmp(const Gam &a, const Gam &b) {
    return a.l + a.x < b.l + b.x;
}
int main() {
    int n;
    cin >> n;
    Gam g[n];
    for (int i = 1; i <= n; ++i) {
        cin >> g[i].x;
        g[i].id = i;
    }
    for (int i = 1; i <= n; ++i) 
        cin >> g[i].l;
    sort(g + 1, g + 1 + n, cmp);
    int lvl = 0;
    int cnt = 0;
    priority_queue<int> pq;
    for (int i = 1; i <= n; ++i) {
        if (lvl <= g[i].l) {
            lvl += g[i].x;
            pq.push(g[i].x);
            cnt++;
        } 
		else if (!pq.empty() && pq.top() > g[i].x && lvl - pq.top() <= g[i].l) {
            lvl += g[i].x - pq.top();
            pq.pop();
            pq.push(g[i].x);
        }
    }
    cout << cnt << endl;
    return 0;
}

```

---

## 作者：abc1856896 (赞：2)

反悔贪心题。

# Solution

首先有一个误区，这道题题面看起来很像某反悔贪心的板子题，然而仔细读题就可以发现这个题是先判断，再计算。

考虑反悔贪心。

手搓样例后可以发现，大体框架是不会变的，但问题在于如何确定比赛的顺序，即排序顺序。

我们不妨设两个下标 $i$ 和 $j$，$i$ 在 $j$ 前面。注意到当且仅当交换前只有单个无法选择，而交换之后两者都可以选。即 $k+x_i > l_j$ 且 $k+x_j \le l_i$，整理得 $l_i+x_i>l_j+x_j$。跑反悔贪心模板即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
struct node{
	int l;
	int x;
};
node a[1000005];
bool cmp(node k1,node k2) {
	return k1.l+k1.x<k2.l+k2.x;
}
int ans;
priority_queue<int> q;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) {
		cin>>a[i].x;
	}
	for(int i=1;i<=n;i++) {
		cin>>a[i].l;
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++) {
		if(ans<=a[i].l) {
			ans+=a[i].x;
			q.push(a[i].x);
		}
		else {
			if(a[i].x<q.top()) {
				ans+=(a[i].x-q.top());
				q.pop();
				q.push(a[i].x);
			}
		}
	}
	cout<<q.size();
	return 0;
}
```

---

## 作者：er_mao_jpg (赞：1)

## P11328 Gym Badges 题解
题目传送门：[P11328 [NOISG 2022 Finals] Gym Badges](https://www.luogu.com.cn/problem/P11328) 。

### 闲话

从 [P4053 [JSOI2007] 建筑抢修](https://www.luogu.com.cn/problem/P4053) 讨论区的多倍经验帖来的，直接把原题代码改了输入输出提交发现：[补兑！](https://www.luogu.com.cn/record/224370847) 所以大家在看多倍经验的时候还是得老实看题啊（叹气）。

### 题意大意
有 $N$ 个比赛。第 $i$ 个比赛可以用 $L_i$ 和 $X_i$ 来描述。当前等级 $\le L_i$ 时，那么可以参加第 $i$ 个比赛，等级提升 $X_i$。

初始等级为 $0$，问最多可以参加多少场比赛。

### 思路分析
和 [P4053 [JSOI2007] 建筑抢修](https://www.luogu.com.cn/problem/P4053) 一样，是一个反悔贪心。

原来的贪心策略如下。

设当前的等级为 $now$。因为等级要求更低的比赛会在等级提升的过程中先无法参加，所以我们先参加等级要求低的比赛。我们就以等级要求 $L_i$ 为第一关键字将比赛从大到小排序。

当目前参加比赛数 $ans$ 一定时，我们还是先让 $now$ 尽量小一点。从这一点就可以想出反悔机制：参加到第 $i$ 场比赛时，如果 $L_i \ge now$，我们就参加这次比赛，$ans + 1$，并将这次比赛加入以提升等级 $X_i$ 为关键字的大根堆中；如果 $ L_i < now$，那么取出大根堆的堆顶，若堆顶元素的提升等级比当前比赛多，那将当前比赛替换掉在堆顶的比赛，$now$ 减去堆顶，再将本次比赛存入大根堆里，$ans$ 值不变。

如此将 $n$ 场比赛都扫一遍，就可以得出答案。

但是和建筑抢修不一样的是，建筑抢修的要求为现在的时间 $now$ 加上当前建筑的修理时间 $X_i$ 小于规定时间 $L_i$，而本题中要求现在的等级 $now$ 小于规定等级 $L_i$ 时才能参加比赛，比赛后等级加 $x_i$。

这样的话我们就发现：用 $L_i$ 作为关键字排序好像不能保证正确性。

那么我们想一想，假设现在的等级为 $now$，我们有两场比赛，它们的等级要求分别为 $L_a$ 和 $L_b$，提升等级分别为 $X_a$ 和 $X_b$，那么只有在参加了比赛 a 之后我们不能参加比赛 b，但参加了比赛 b 之后还可以参加比赛 a 时，我们会先参加比赛 b，即 $now + X_b \le L_a$ 且 $now + X_a > L_b$。由此推知 $X_b + L_b \le X_a + L_a$ 时先选择比赛 b 更优。如此，在给比赛排序时以 $L_i + X_i$ 为关键字从小到大排序即可。其他贪心方法不变。

其余细节实现请见代码。
### 代码

```c++
#include <bits/stdc++.h>
using namespace std;

long long n, ans, now;
long long a, b;

struct node{
	long long X, L;
}num[500010];

priority_queue <long long> q;//优先队列默认大根堆 

bool cmp(node x, node y){ 
	return x.L + x.X < y.L + y.X;//以L_i + x_i 为关键字从小到大排序 
}

int main(){
	ios::sync_with_stdio(false);//解绑，加快输入输出速度 
	cin.tie(0);
	cout.tie(0);
	
	cin >> n;
	for(int i = 1; i <= n; i++){
		cin >> num[i].X;
	}
	for(int i = 1; i <= n; i++){
		cin >> num[i].L;
	}
	
	sort(num + 1, num + 1 + n, cmp);//排序
	
	for(int i = 1; i <= n ;i++){
		if(now <= num[i].L){
			ans++;
			now += num[i].X;
			q.push(num[i].X);//将该比赛入堆 
		}else{
			if(q.top() > num[i].X){//反悔操作 
				now += num[i].X;
				now -= q.top();
				q.pop();
				q.push(num[i].X);			
			}
		}
	}
	
	cout << ans << '\n';
	return 0;
} 
```
### 写在最后
帮到你的话请点赞题解喵，点赞题解谢谢喵

---

## 作者：zhuangzhihe (赞：1)

非常好的一道反悔自动机练习题。

 与这题十分类似：[P11457 Job Completion G](https://www.luogu.com.cn/problem/P11328)，感兴趣可以先去做一下。

观察这道题时，我们不难看出它的本质：你可以将自己的等级视为时间，比赛视为任务，然后这道题就被我们成功转化为上述的题目了。

第一眼观看时，可以看出，这道题应该与每项工作的紧急程度有关。因为显而易见的，如果一项工作完成后还可以完成其他的工作，但其它工作完成后就不能再完成这项工作了，我们应当先完成这项工作。

举个例子，假设我们现在已经耗费了 $100000$ 的时间，工作 $a$ 的截止开始时间为 $114514$，工作所需时间为 $2$，工作 $b$ 的截止开始时间为 $123456$，工作所需时间为 $20000$，此时如果先完成 $b$，时间就变成 $120000$，此时无法再完成 $a$。但如果先完成 $a$，此时时间变为 $100002$，我们仍有充足的时间去完成 $b$。所以可以得出结论，我们一般应当先完成最紧急的任务。

然而“紧急”是如何定义的呢？我们可以先猜想，截止开始时间越早，这项工作就越紧急。然而很快可以给出反例。

假设我们现在已经耗费了 $100000$ 的时间，工作 $a$ 的截止开始时间为 $114514$，工作所需时间为 $2$，工作 $b$ 的截止开始时间为 $114513$，工作所需时间为 $20000$，此时如果先完成 $b$，时间就变成 $120000$，此时无法再完成 $a$。但如果先完成 $a$，此时时间变为 $100002$，我们仍有充足的时间去完成 $b$。

上面这个例子仅仅是在开头的例子上将 $b$ 的截止开始时间修改为了 $114513$，此时会发现，我们仍然是先完成 $a$ 更划算，但此时 $b$ 的截止开始时间显然比 $a$ 更早，因此我们的猜想被推翻了。

然而再观察这个例子，我们可以发现它的截止结束时间就是他的截止开始时间加上它的所需完成时间，也就是说，在这个截止结束时间之前，你必须要完成这项工作，而不是开始你的工作。

我们继续猜想，会不会一项工作的紧急程度是由截止结束时间决定的呢？观看上面两个例子，会发现该结论在上述例子中均成立。那么我们再使用数学证明。

设两个工作截止开始时间为 $s_i$ 与 $s_j$，完成所需时间为 $t_i$ 与 $t_j$，当前已耗费的时间为 $time$，如果我们的最优选择方式为先完成工作 $i$ 再完成工作 $j$，也就是说先完成工作 $i$ 能完成工作 $j$，反之则不行，那么显然有两个不等式，分别是 $time+t_i\le s_j$ 与 $time+t_j>s_i$。

将第一个式子两边各加上 $t_j$，第二个式子两边同加上 $t_i$，可以得到 $time+t_i+t_j\le s_j+t_j$ 与 $time+t_j+t_i>s_i+t_i$，发现此时两个式子的左边相同，利用不等式的传递性可得 $s_j+t_j>s_i+t_i$，显然，我们可以将之理解为，如果先完成工作 $i$ 能完成工作 $j$，反之不行，那么工作 $i$ 的截止结束时间一定早于工作 $j$，也就是一般来说，我们应当先完成截止结束时间较早的工作。

所以，我们可以给每项工作按照截止结束时间升序排序，然后依次处理，确认是否完成这项工作。

然而，这个结论在面对一大堆工作时会出问题。我们的结论仅适用于先完成 $i$ 时能完成 $j$，反之不行的情况。如果两个工作一定冲突，我们该选谁呢？很显然，我们应当选择消耗时间较少的而非截止结束时间较早的。

有时也许由于我们的贪心，在前面选择了一个截止结束时间较早但耗时大于当前工作的，并且此时时间不够我们完成这项工作了，那么这就是前面所说的两个工作一定冲突的情况了。我们应当舍弃前面那个耗时较大的而选择现在这个。但如果前面耗时反而更小，那么我们就不用管，就当无事发生。

这样一种思路我们当然可以用大根堆来维护。我们先处理最紧急的，并依次往越来越不紧急的顺序去处理，每次处理时先将这次工作的耗时放进大根堆，如果时间充足就先完成这项工作，否则我们弹出之前耗时最长的工作，也就是大根堆的堆顶，然后再来完成这项工作。当然，如果这项工作本身就是耗时最长的，由于前面我们已经将它放入大根堆中，所以会直接将它自己弹出。然后再修改当前工作时间。

这时也许有同学要问，如果这项工作的耗时会导致工作时间不够怎么办？这种情况我们其实完全不用担心。因为我们是按照紧急程度升序排序后再处理的。凡是放入大根堆的，都一定是我们已经完成的工作。已完成的工作显然在此次工作之前处理，也就是说它的截止结束时间较早，在截止结束时间较早，且它的耗时大于我们当前工作的耗时的情况下，显然如果这项工作能完成，那么放弃这项工作去完成当前工作也是没有问题的。

都讲到这里了，思路已经十分清晰，接下来代码也很好实现了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define N 550005
int n,ans,t;
pair<int,int> a[N];
priority_queue<int> q;
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i].second;
    for(int i=1;i<=n;i++) cin>>a[i].first,a[i].first+=a[i].second;
	sort(a+1,a+n+1);//排序
	for(int i=1;i<=n;i++){
		q.push(a[i].second);//放入大根堆
		if(t+a[i].second<=a[i].first){//能完成就完成
			ans++;
			t+=a[i].second;
		}else{//不能完成就放弃耗时最长的
			t+=(a[i].second-q.top());
			q.pop();
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：yedalong (赞：1)

## Solution

一个很明显的反悔贪心。

我们先考虑以最优顺序遍历，如何得到最多的勋章。首先，我们可以先用一个变量 $sum$ 储存现在进行到多少时间了。对于每一个比赛，我们都选择参加，但是如果参加不了，就可以选择不参加一个以前或现在参加的增长等级最多的一个比赛（反悔），如果参加得了，那么直接统计答案加 $1$。\
对于如何寻找花费时间最长的比赛，可以考虑使用大根堆进行维护。

接下来我们思考最优顺序。很多同学看到的第一眼就是按照 $L_i<L_j$ 来排序，但是这样有没有一种可能，就是 $X_i+sum>L_j\land X_j+sum\le L_i$，这样我们的策略就错误了。\
针对上面我们提出的可能，可以通过移项列出不等式组：

$$\begin{aligned}
\begin{cases}
L_ j-X_i<sum\\
L_i-X_j\ge sum
\end{cases}
\end{aligned}$$

解得：
$$\begin{aligned}
L_j-X_i<sum\le L_i-X_j
\end{aligned}$$

即：
$$\begin{aligned}
L_j-X_i<L_i-X_j
\end{aligned}$$

移项得：
$$\begin{aligned}
L_j+X_j<L_i+X_i
\end{aligned}$$
接着我们就发现其实只要按照 $L+X$ 进行从小到大排序，就可以解决这个问题，于是，排序的问题也解决了。 

## AC code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
struct build{int t1,t2;}arr[500005];
bool cmp(build a,build b){return a.t2+a.t1<b.t2+b.t1;}
int n,sum;
priority_queue<int> q; 
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
	cin>>n;
    for(int i = 1;i<=n;i++) cin>>arr[i].t1;
    for(int i = 1;i<=n;i++) cin>>arr[i].t2;
    sort(arr+1,arr+1+n,cmp);
    for(int i = 1;i<=n;i++){
        sum+=arr[i].t1;
        q.push(arr[i].t1);
        if(sum-arr[i].t1>arr[i].t2){
            sum-=q.top();
            q.pop();
        }
    }
    cout<<q.size();
    return 0;
}
```

---

## 作者：To_Carpe_Diem (赞：1)

## 题目大意
一共有 $n$ 场比赛，你的初始等级是 $0$，每场比赛有等级限制和升级贡献，分别是 $L_i$ 和 $X_i$，你现在可以选择**任意的比赛顺序**参加，使得你参加的比赛尽可能的多。

## 思路
这里我们考虑**贪心**，但是如何贪？

思路 $1$ 是按照 $X_i$ 从小到大排序，但是以下例子可以 hack 掉这种想法。

```
括号内为编号
3
1 100 (1)
100 1 (2)
2 101 (3)
排序后
1 100 (1)
2 101 (3)
100 1 (2)
你会按照 (1) -> (3) 的顺序参加两场。
然鹅正确的顺序是 (2) -> (1) -> (3)，可以参加三场。
```

思路 $2$ 是按照 $L_i$ 从小到大排序，但是以下例子可以 hack 掉这种想法。

```
括号内为编号
3
10 1 (1)
1 4 (2)
2 3 (3)
排序后
10 1 (1)
2 3 (3)
1 4 (2)
你会按照 (1) 的顺序参加一场比赛。
然鹅正确的顺序是 (2) -> (3) 或 (3) -> (2) 或 (2) -> (1) 的顺序参加两场比赛。
```

思路 $3$ 按照 $X_i + L_i$ 从小到大排序，为什么呢？

举个例子，当你在抉择两个比赛先选哪一个的时候，什么情况下**交换比赛顺序**最优呢？

当你当前的等级加上本次枚举的比赛所贡献的等级小于等于之前一个比赛的等级限制，且当前的等级加上之前的比赛所贡献的等级大于本次枚举的比赛的等级限制时，交换两个比赛的顺序一定**最优**，很绕吧？让我们举个例子。
```
cnt 为当前的等级,x1,l1,x2,l2 分别为两个比赛的数值。
即 (cnt + x1 > l2 && cnt + x2 <= l1) 时，互换顺序可以使两个比赛一起参加。
```

形式化的讲：

$$cnt + X_1 > L_2$$
$$cnt + X_2 \le L_1$$

可化为：

$$cnt > L_2 - X_1$$
$$cnt \le L_1 - X_2 $$

则有：

$$L_2 - X_1 < cnt \le L_1 - X_2$$

交换一下可以得到：

$$L_2 + X_2 < X_1 + L_1$$

于是我们可以按照 $X_i + L_i$ 的顺序来进行排序。

接下来可以用**反悔贪心**来对这题进行求解。

我们可以在每次遇到比赛的时候先参加，把本次比赛的需要的贡献加入一个大根堆，在遇到下一个比赛的时候判断当前的 $cnt$，若 $cnt \le L_i$，则没有什么问题，直接参加就好，无所谓。若是 $cnt > L_i$，则可以找一个一个之前贡献等级最大减掉，这个可以找大根堆的堆顶，减去后把堆顶删掉，再把本次的贡献 $X_i$ 加入堆即可。

## 代码
```cpp
#include<iostream>
#include<queue>
#include<set> 
#include<algorithm>
#define int long long
using namespace std;

const int MAXN = 5 * 1e5 + 5;
int T,n;
struct node{
	int l,x;
}c[MAXN];
priority_queue<int> q;
bool cmp(node x,node y){
	return x.l + x.x < y.x + y.l; 
}

signed main(){
	
	cin >> n;
	
	for(int i = 1;i <= n;i ++){
		cin >> c[i].x;
	}
	for(int i = 1;i <= n;i ++){
		cin >> c[i].l;
	}
	
	sort(c + 1,c + n + 1,cmp);
	
	int cnt = 0,ans = 0;
	
	for(int i = 1;i <= n;i ++){
		if(cnt <= c[i].l){
			ans ++;
			cnt += c[i].x;
			q.push(c[i].x);
		}
		else{
			if(!q.empty() && q.top() > c[i].x){
				cnt += (c[i].x - q.top());
				q.pop();
				q.push(c[i].x);
			}
		}
	}
	cout << ans << '\n'; 
	return 0;
}
```

---

## 作者：XCDRF_ (赞：1)

# P11328 \[NOISG 2022 Finals] Gym Badges 题解

[原题传送门](https://www.luogu.com.cn/problem/P11328)

[更好的阅读体验](https://www.luogu.com.cn/article/s55z7ggi)

## 解题思路

考虑贪心，将比赛按照 $l_i+x_i$ 升序排序，一定是优的。

可以换个角度证明，假设一开始我的等级是无穷大，等级可以自己控制降低，也可以通过比赛一次降低 $x_i$，降到零为止。每个比赛都要让等级降到 $l_i+x_i$ 以下才能参加。贪心地，每次参加 $l_i+x_i$ 最大的比赛，给后面的比赛留出下降的空间，这样可以使参加的比赛最多。

把上述过程反过来看，就是要按照 $l_i+x_i$ 升序参加比赛。

当然，一直贪心肯定不能保证正确性。如果答案队列中有一个提升等级特别大的，完成这个比赛后，等级已经超过了下一个比赛的最高等级，就放不进去了，可能因为这一个比赛错过了许多比赛。这时可以进行一次反悔操作，用新比赛把这个提升等级特别大的比赛替换掉。

再思考一下，做这个操作的条件是什么？

1. 答案队列中需要有比赛来替换，也就是答案队列不空。
2. 新比赛提升等级要比最大提升等级小，不然还不如不换。
3. 将提升等级最大的比赛取出来后，当前等级要比新比赛的最大参加等级要小，不然取出来了新比赛也放不进去。（~~不过这个条件判不判都能 AC~~）

提升等级最大的比赛用一个大根堆维护即可。

记得开 long long。

## 参考代码

```cpp
#include<iostream>
#include<algorithm>
#include<queue>
#define int long long
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
const int N=5e5+5;
int t,n;
pii a[N];
bool cmp(pii a,pii b){
	return a.fi+a.se<b.fi+b.se;//按照 l+x 升序排序
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i].se;
	for(int i=1;i<=n;i++) cin>>a[i].fi;
	sort(a+1,a+n+1,cmp);
	priority_queue<int> q;
	int now=0,cnt=0;
	for(int i=1;i<=n;i++){
		pii t=a[i];
		if(now<=t.fi){//能放就直接放
			now+=t.se;
			q.push(t.se);
			cnt++;
		}
		else if(!q.empty()&&q.top()>t.se&&now-q.top()<=t.fi){//分别对应上述的三个条件
			now+=t.se-q.top();
			q.pop();
			q.push(t.se);
		}
	}
	cout<<cnt;
	return 0;
} 
```

[AC 记录](https://www.luogu.com.cn/record/196076980)

---

## 作者：dangerous_DZR (赞：0)

建议先刷一下[建筑抢修](https://www.luogu.com.cn/problem/P4053)。
### 分析
首先看完题面（题目标签）可以发现，这道题的解法是贪心。贪心的关键就在于要贪什么 ~~（当然不是心）~~ 和怎么贪 ~~（用手贪）~~，而这道题我们肯定要尽可能先参加限制等级低的比赛来得到更多徽章 ~~（贪徽章）~~，所以我们先将比赛按照限制等级升序排序。~~（不是我怎么这么喜欢用删除线和括号）~~。

但是如果当前等级还是高于比赛的限制等级呢？重温一遍贪心策略：我们要在参加尽可能多的比赛的情况下让自己的等级尽可能低（为了参加后面更多的比赛）。所以我们可以把已经参加过的比赛中增加等级最高的一个比赛换掉而参加当前比赛。
### 实现
第一步排序显然可以用 pair 或结构体加自定义排序实现，那第二步呢？直接搜索复杂度太高，还要维护插入和删除操作，于是我们就将优先队列设为贪心手段，每次若当前比赛能参加就参加，否则将其与已参加比赛中增加等级最高的比赛替换，总徽章数不变。当然注意到题目中的比赛等级限制是在参赛前的，而每次判断时都要对当前等级加上或减去参赛后增加等级，所以为了方便我们可以在输入时把限制等级加上参赛所加等级，相当于把限制放在比赛后（有点啰嗦勿喷）。  
最后放出我的神经代码（码风极为粗鄙）：
```cpp
#include <bits/stdc++.h>
#define int long long 
using namespace std;
struct t{
	int x, y;
}a[500010];
int n, sum, ans;
priority_queue<int> q;
bool cmp(t i, t j){
	return i.y < j.y;
}
signed main(){
	cin >> n;
	for (int i = 1; i <= n; i ++)cin >> a[i].x;
	for (int i = 1; i <= n && cin >> a[i].y; i ++)a[i].y += a[i].x;//预处理加上比赛后所提升的等级
	sort(a + 1, a + n + 1, cmp);
	for (int i = 1; i <= n; i ++){
		q.push(a[i].x), sum += a[i].x;
		if (sum <= a[i].y)ans ++;//贪心
		else sum -= q.top(), q.pop();//若超出限制就替换比赛
	}
	cout << ans;
	return 0;
}
```

---

## 作者：Delete_error (赞：0)

### 前话：
[Link](https://www.luogu.com.cn/problem/P11328)。
### 得到顺序：
对于一个徽章，我们发现 $L+X$ 等价于获得徽章后的最大等级，我们下文将 $L$ 写为 $T_1$，$L+X$ 写为 $T_2$。

我们先考虑如何确定得到顺序，用邻项交换法思考，设当前等级为 $now$，当 $a$ 和 $b$ 先拿 $a$ 更优时，当且仅当先拿完 $a$ 后仍然可以拿 $b$ 即获得 $b$ 后等级不超过最大等级，同时当先拿完 $b$ 后拿不了 $a$ 即获得 $a$ 后等级超过最大等级，可以用两个不等式表示：
$$now+a_{T_1}+b_{T_1}\le b_{T_2}$$
$$now+b_{T_1}+a_{T_1}>a_{T_2}$$
合并为：
$$a_{T_2}<now+a_{T_1}+b_{T_1}\le b_{T_2}$$
即：
$$a_{T_2}<b_{T_2}$$
那么就按这个排序，则答案方案一定是总序列的子序列，即得到顺序固定。
### 反悔贪心：
设当前等级为 $now$，当前要拿的是 $c$，如果能拿就先拿且答案加一；不能拿则一定当前加入了 $c$ 的方案有一个徽章拿不了，又因为 $now$ 越小后面的徽章拿的可能越大，则踢掉当前方案中 $T_1$ 最大的获得徽章，由于加入 $c$ 踢掉最大的，则答案不变。因为答案方案一定是总序列的子序列，则这样反悔贪心是正确的，不会改变先后顺序。
### code:
排序和大根堆维护都为 $O(n\log n)$。

```
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
const int  MAXN=5e5+5;
ll t,n;
struct Node{
	ll s,t;
}stu[MAXN];
bool cmp(Node a,Node b){
	return a.s+a.t<b.s+b.t;
}
int main(){
	t=1;
	while(t--){
		cin>>n;
		priority_queue<ll> q;
		ll sum=0,ans=0;
		for(int i=1;i<=n;i++) cin>>stu[i].t;
		for(int i=1;i<=n;i++) cin>>stu[i].s;
		sort(stu+1,stu+n+1,cmp);
		for(int i=1;i<=n;i++){
			q.push(stu[i].t);
			if(sum<=stu[i].s){
				sum+=stu[i].t;
				ans++;
			}
			else{
				sum+=stu[i].t;
				sum-=q.top();
				q.pop();
			}
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

有问题私信,中考不一定会在，但看到一定会回复。

---

## 作者：gac497 (赞：0)

# 问题描述

有一只初始等级为 $0$ 的 Wabbit，它希望通过参加一系列比赛来提升自己的等级，并收集徽章。每个比赛有两个属性：$L_i$ 和 $X_i$。如果 Wabbit 的当前等级不超过 $L_i$，那么它可以参加这个比赛，提升自己的等级 $X_i$，并获得一个徽章。Wabbit 可以以任意顺序参加比赛，要求最大化收集到的徽章数量。

# 解题思路

## 1. 问题分析：
 - 比赛的顺序会影响 Wabbit 能否参加后续的比赛。因此，我们需要找到一个最优的参加顺序。
 - 我们可以将比赛按照某种规则排序，使得在参加比赛时，Wabbit 的等级尽可能小，从而能够参加更多的比赛。

## 2. 排序策略：
 - 我们可以将比赛按照 $L_i + X_i$ 从小到大排序。这样做的原因是，我们希望优先参加那些对等级要求较低且提升较小的比赛，以便后续能够参加更多的比赛。

## 3. 贪心算法：
 - 使用一个优先队列（最大堆）来维护当前已经参加的比赛。如果当前的总等级超过了某个比赛的 $L_i$，我们可以选择放弃之前某个比赛，以腾出空间参加新的比赛。

# 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
struct node{
	int c,k;	
}a[500010];
int n,sum,ans;
priority_queue<int>q;
bool cmp(node x,node y){
	return x.c+x.k<y.c+y.k;
} 
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i].c);
	}
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i].k);
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++){
		q.push(a[i].c);
		if(sum>a[i].k){
			sum-=q.top();
			q.pop();
			ans--;
		}
		sum+=a[i].c;
		ans++;
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：MoGuYun_12 (赞：0)

思路：反悔贪心。

先将每个比赛按照 $S_i + X_i$ 升序排序，可以用调整法证明此顺序一定最优。

按序遍历每个比赛，能选就选。不能选就在已选择比赛中找到最大的一个 $X_i$ 把它删去，我们可能因为这一个比赛导致其他的比赛放不进去。这就是一次反悔操作，反悔之后就有可能让新的比赛容纳进去。

每次找最大的过程可以用大根堆维护，时间复杂度 $O(n\log n)$。


```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int N = 5e5+5;
int n;
struct node{
	ll l,x,r;
}a[N];
bool cmp(node a,node b){
	return a.r<b.r; 
}
priority_queue <ll> q;
int main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i].x;
	for(int i=1;i<=n;i++) cin>>a[i].l;
	for(int i=1;i<=n;i++) a[i].r=a[i].l+a[i].x;
	sort(a+1,a+n+1,cmp);
	ll sum=0;
	for(int i=1;i<=n;i++){
		q.push(a[i].x),sum+=a[i].x;
		if(sum>a[i].r){
			sum-=q.top(),q.pop(); //反悔操作
		}
	}
	cout<<q.size(); //队列长度即为答案
	return 0;
}

```

---

## 作者：HYdroKomide (赞：0)

### 题意：

有一些徽章，想要获得一个徽章必须等级不超过某一个值，获得一个徽章会提升一定的等级，问最多获得多少个徽章。

### 思路：

板题的反悔贪心，把徽章按照 $X_i+L_i$ 的**获得后最高等级**排序。

维护一个大根堆，从大到小给所有徽章按等级数排序。然后顺序遍历所有徽章，如果当前徽章本身就可以获得，直接加入大根堆。如果当前徽章不能获得，将它和堆里最大的数进行比较。如果它比堆里最大的徽章等级数少，而且将堆里最大的徽章等级数量去掉后可以获得当前的徽章，那就可以直接将堆里最大的值抛掉，新的徽章压入堆。

最终结果即为堆的大小。

可以证明上述方法正确，在需要更换堆中元素时总时长不减，同时徽章获得数只会单调递增。时间复杂度 $O(Tn\log n)$。

注意开 long long。

### 代码如下：

```cpp
#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
const int N=5e5+5;
int T,n;
struct JOB{long long s,t;}a[N];
bool operator<(JOB x,JOB y){return x.t==y.t?x.s<y.s:x.t<y.t;}
bool cmp(JOB x,JOB y){return x.s+x.t<y.s+y.t;}
priority_queue<JOB,vector<JOB>,less<JOB> >q;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i].t);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i].s);
	sort(a+1,a+n+1,cmp);
	long long curt=0;
	for(int i=1;i<=n;i++){
		if(curt<=a[i].s){
			q.push(a[i]);
			curt+=a[i].t;
		}
		else{
			JOB u=q.top();
			if(a[i].t<u.t&&curt-u.t<=a[i].s){
				q.pop();
				curt-=u.t;
				q.push(a[i]);
				curt+=a[i].t;
			}
		}
	}
	printf("%d\n",q.size());
	return 0;
}
```

### THE END

---

## 作者：K_yuxiang_rose (赞：0)

我们先考虑怎么将这个数列排序。先设两个下标 $i$ 和 $j$，$i<j$，将 $i$ 之前的等级设为 $sum$，那么它们交换后比交换前更优，当且仅当：

$sum+x_i>l_j$ 并且 $sum+x_j\le l_i$。

整理后得 $x_j+l_j<x_i+l_i$。

现在再来考虑怎么贪心。如果这个比赛可以参加，那么就参加，并将代价放进优先队列以后反悔用。如果不能参加，就弹出现在代价最大的比赛然后参加这个比赛，特别地，如果这个比赛代价最大，那就选择忽略这个比赛。这时少参加了一个比赛，又多参加了一个比赛，因此答案不用更新。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
priority_queue<int> q;
struct node
{
	int x,l;
}a[500005];
bool cmp(node i,node j)
{
	return i.l+i.x<j.l+j.x;
}
signed main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i].x;
	for(int i=1;i<=n;i++) cin>>a[i].l;
	int sum=0,ans=0;
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++)
	{
		q.push(a[i].x);
		if(sum<=a[i].l) ans++,sum+=a[i].x;
		else sum+=a[i].x-q.top(),q.pop();
	}
	cout<<ans;
	return 0;
}
```

---

