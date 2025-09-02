# [ABC382C] Kaiten Sushi

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc382/tasks/abc382_c

とある回転寿司に、$ 1 $ から $ N $ までの番号が付けられた $ N $ 人の人が訪れています。 人 $ i $ の **美食度** は $ A_i $ です。

今からベルトコンベア上を $ M $ 個の寿司が流れます。 $ j $ 番目に流れる寿司の **美味しさ** は $ B_j $ です。 それぞれの寿司は、人 $ 1,2,\dots,N $ の前をこの順に流れていきます。 それぞれの人は、美味しさが自分の美食度以上である寿司が自分の前に流れてきたときはその寿司を取って食べ、それ以外のときは何もしません。 人 $ i $ が取って食べた寿司は、人 $ j\ (j\ >\ i) $ の前にはもう流れてきません。

$ M $ 個の寿司それぞれについて、その寿司を誰が食べるか、あるいは誰も食べないかどうかを求めてください。

## 说明/提示

### 制約

- $ 1\leq\ N,M\ \leq\ 2\times\ 10^5 $
- $ 1\leq\ A_i,B_i\ \leq\ 2\times\ 10^5 $
- 入力は全て整数
 
### Sample Explanation 1

\- $ 1 $ 番目の寿司について、 - まず人 $ 1 $ の前を流れます。$ B_1\ \geq\ A_1 $ なので、人 $ 1 $ はこれを取って食べます。 - 人 $ 2,3 $ の前にはこの寿司は流れてきません。 - $ 2 $ 番目の寿司について、 - まず人 $ 1 $ の前を流れます。$ B_2\ <\ A_1 $ なので、人 $ 1 $ は何もしません。 - 次に人 $ 2 $ の前を流れます。$ B_2\ <\ A_2 $ なので、人 $ 2 $ は何もしません。 - 最後に人 $ 3 $ の前を流れます。$ B_2\ \geq\ A_3 $ なので、人 $ 3 $ はこれを取って食べます。 - $ 3 $ 番目の寿司について、 - まず人 $ 1 $ の前を流れます。$ B_3\ <\ A_1 $ なので、人 $ 1 $ は何もしません。 - 次に人 $ 2 $ の前を流れます。$ B_3\ <\ A_2 $ なので、人 $ 2 $ は何もしません。 - 最後に人 $ 3 $ の前を流れます。$ B_3\ <\ A_3 $ なので、人 $ 3 $ は何もしません。 - よって、誰もこの寿司を食べません。

## 样例 #1

### 输入

```
3 3
3 8 2
5 2 1```

### 输出

```
1
3
-1```

## 样例 #2

### 输入

```
3 3
1 1 1
1 1 1```

### 输出

```
1
1
1```

## 样例 #3

### 输入

```
10 5
60 83 76 45 70 91 37 58 94 22
70 39 52 33 18```

### 输出

```
1
7
4
10
-1```

# 题解

## 作者：FlowerAccepted (赞：4)

# 题目翻译
## 问题陈述：
有 $N$ 个人，编号从 $1$ 到 $N$，他们正在访问一家传送带寿司餐厅。第 $i$ 个人的美食级别是 $A_i$。

现在，将会有 $M$ 份寿司放置在传送带上。第 $j$ 份寿司的美味度为 $B_j$。每份寿司将按照顺序经过编号为 $1$，$2$，$\dots$，$N$ 的人。每个人在看到美味度不低于他们美食级别的寿司经过时，会拿走并吃掉那份寿司；否则，他们什么也不做。一旦第 $i$ 个人拿走并吃掉了寿司，那份寿司就不会再经过编号大于 $i$ 的人。

对于每份 $M$ 份寿司中的一份，请确定是谁吃掉了那份寿司，或者是否没有人吃掉它。

## 约束条件：
$1\le N$，$M\le2\times10^5$

$1\le A_i$，$B_i\le2\times10^5$

所有输入值均为整数。
# 解题思路
首先，我们可以想到一个暴力思路，即先输入每个 $A_i$，同时求 $A$ 序列的最小值，当输入每个 $B_j$ 时，将 $B_j$ 依次与每一个 $A_k$（$1\le k\le n$，$k\in N^*$）进行比较，一旦发现不比 $B_i$ 大的 $A_k$ ，就输出 $k$，如果没有合适的 $A_k$（即 $B_i$ 小于 $A$ 序列的最小值）时，输出 `-1`。但这个思路复杂度 $O(NM)$，这个数是 $10^{10}$ 级别，明显会超时。

其次，我们可以想到对 $A$ 序列**降序**排序，再二分 $B_i$，但这是错误的，因为这无法保证拿到 $B_i$ 的是美味等级小于等于 $B_i$ 且编号最小的人。

最后，我们想到可以使用 $C$ 序列存储 $A$ 序列的**前缀最小值**，即对于每个 $0\le i\le n$，$i\in N^*$，有：

$$C_i=\begin{cases}2\times10^5+5&i=0\\\min(A_i,C_{i-1})&i\ge 1\end{cases}$$

这时，$C$ 序列满足了**单调不增**的特性，同时可以表示第一个小于等于 $x$ 的 $A_i$ 的下标。我们可以使用 STL 中的 `lower_bound` 二分 $C$ 序列，如果返回的不是 $C$ 序列的尾指针（判断是否找到），则输出返回值所代表的 $A_i$ 的下标（即 `lower_bound(c, c + n + 1, b, greater<int>()) - c`），否则输出 `-1`。

这个算法的时间复杂度为 $O(M\log N)$，运算量在 $10^7\sim10^8$ 级别，不会超时。于是我们就通过了此题。

# 代码呈现

```cpp
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstring> // 万能头不是标准
using namespace std;

int a[200005], b, c[200005] = {200005}; // b 随算随输入，无需数组存储    A[i]最大200000，不会超过200005

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
        c[i] = min(a[i], c[i - 1]); // 计算前缀最小值
    }
    for (int i = 1; i <= m; i ++) {
        cin >> b;
        auto it = lower_bound(c + 1, c + n + 1, b, greater<int>()); // lower_bound指针
        if (it - c - 1 < n) { // 判断是否找到
            cout << it - c << '\n';
        } else {
            cout << "-1\n";
        }
    }
    return 0;
}

```

---

## 作者：Lian_zy (赞：2)

### 题目翻译

有 $N$ 个编号从 $1$ 到 $N$ 的人光顾一家传送带寿司店。第 $i$ 个人的美食级别是 $A_i$ 。

现在， $M$ 块寿司将被放在传送带上。第 $j$ 个寿司的美味程度是 $B_j$ 。每块寿司都会按照这个顺序从 $1, 2, \dots, N$ 人面前经过。当美味程度不低于自己美食水平的寿司从面前经过时，每个人都会拿起并吃掉这个寿司；否则，他们什么也不会做。 $i$ 拿起并吃掉的寿司将不再从 $j\ (j > i)$ 面前经过。

对于每个 $M$ 个寿司，确定谁吃了这个寿司，或者是否没人吃。

### 题目分析

~~感觉这题甚至比第四题难~~。

我的第一反应是从每个人的角度考虑，查找他们会吃的第一个寿司，但是每个寿司只能被吃掉一次，而处理这个就会很头疼。

但是，如果你是一个寿司，你要找到一个人把你吃掉~~这是在干什么啊~~，这样就好想多了，因为一个人可以把多个寿司吃掉，没有找到一个人但是他不吃的问题。

于是这道题就迎刃而解了：对于每一个寿司，查找第一个可以把他吃掉的人，就好了。

现在还有一个问题，我们要找到第一个美食级别小于等于当前寿司美味程度的人，即：第一个小于等于 $A_i$ 的 $B_j$。

但是直接这么找就会超时，但是 $B$ 数组又是乱序的，怎么办呢？

只要对 $B$ 数组求一个前缀最小值数组 $P$ 就可以解决了，这时，如果 $P_{mid} \ge A_i$，则 $P_{mid - 1} \ge A_i$，$P_{mid-2} \ge A_i$，$\dots$。这样就保证数组是单调递减的，在上面二分就行了。

### code

``` cpp
#include<bits/stdc++.h>
using namespace std;
#define N 200005
int n,m,a[N],b[N],p[N];
int main(){
	cin>>n>>m;
	p[0]=0x3f3f3f3f;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		p[i]=min(p[i-1],a[i]);
	}
	for(int i=1;i<=m;i++)cin>>b[i];
	for(int i=1;i<=m;i++){//寻找第一个小于等于a[i]的b[j] 
		int l=1,r=n,ans=-1;
		while(l<=r){
			int mid=l+r>>1;
			if(p[mid]<=b[i]){
				ans=mid;
				r=mid-1;
			}else l=mid+1;
		}
		cout<<ans<<endl;
	}
	return 0;
} 
```

---

## 作者：chinazhanghaoxun (赞：2)

## 分析
如题意，我们需要求出吃掉每一个寿司的人，而如果第 $i$ 个寿司被第 $j$ 个人吃掉，那么就可以说明 $b_i\ge a_j$。那么可以考虑对 $b$ 数组排序，如果一个 $a_i$ 连当前 $b_j$ 都接受不了，那么它一定接受不了更往后面的寿司，因为我们已经按降序排序了。按照这个思路，我们可以得到一种类似于双指针的做法，而且是最易理解的一种。
## 做法
按照分析，我们可以知道把 $b$ 按降序排列，一个指针 $i$ 从左往右扫 $b$，对于每个 $b_i$，使用指针 $y$ 按照输入顺序扫 $a$，只要找到了 $a_y \le b_i$，就让 $y$ 指针不动，一直吃到 $a_y > b_i$ 为止。注意还要恢复原序，所以存储的时候应该存储的是结构体。
## 代码+注释
代码很简单，易懂，可以看着注释学习一下。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int a[N];
struct eat{
	int x,id,ans;
}q[N];
bool cmp_x(eat x,eat y){
	return x.x>y.x;
}
bool cmp_id(eat x,eat y){
	return x.id<y.id;
}
int main(){
	int n,m;
	cin>>n>>m; 
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<=m;i++){
		cin>>q[i].x;
		q[i].id=i;//要保存位置，方便恢复顺序
	}
	sort(q+1,q+1+m,cmp_x);//按照美味程度排序 
	int now=1;//a数组的指针 
	for(int i=1;i<=m;i++) {
		while(now!=n+1 && a[now]>q[i].x){//只要当前可以就一直吃 
			now++;
		}
		if(now==n+1) q[i].ans=-1;//没有人吃
		else q[i].ans=now;//记录到结构体中
	}
	sort(q+1,q+1+m,cmp_id);//恢复原来的顺序 
	for(int i=1;i<=m;i++)
		cout<<q[i].ans<<endl;
}
```

---

## 作者：wht_1218 (赞：1)

可以预处理 $mn_i=\min_{j=1}^iA_i$，设将要取的寿司美味度为 $x$，若 $mn_i\le x$ 说明在 $1\sim i$ 个人中会有人拿走寿司。

我们可以依此来进行二分（或者双指针）。

这里提供的是二分做法。


```cpp
#include <bits/stdc++.h>
using namespace std;
constexpr int N=1e6+7;
int n,m,a[N],b[N],mn[N];
int main() {
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>n>>m;
    memset(mn,0x3f,sizeof mn);
	for(int i=1;i<=n;++i)cin>>a[i],mn[i]=min(mn[i-1],a[i]);
	for(int i=1;i<=m;++i)cin>>b[i];
	for(int i=1;i<=m;++i){
		int l=1,r=n,ans=-1;
		while(l<=r){
			int mid=l+r>>1;
			if(mn[mid]<=b[i]){
				r=mid-1;ans=mid;
			}else l=mid+1; 
		}cout<<ans<<"\n";
	}
	
    return 0;
}
```

---

## 作者：sjh0626 (赞：1)

## 题意概括
给定你一个长度为 $N$ 的序列 $a$，在给定你一个长度为 $M$ 的序列 $b$。

$1 \le i \le m$ 时，对于每一个 $b_i$ 都会有一个对应的 $c_i$，$1 \le j \le n$ 时，$c_i$ 定义如下：

- 若存在 $a_j \ge b_i$ 时，$c_i \gets j$ 。
- 反之，$c_i \gets -1$。
## 思路分析
这道题可以充分发挥我们的人类智慧，我们可以先打个暴力。

### 暴力做法
按照题目的要求模拟，代码如下，时间复杂度：$O(nm)$。
```cpp
#include<bits/stdc++.h>
#define sjh0626s return
#define code 0
using namespace std;
int n,m,a[300010],b[300010];
bool vis[300010];
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=m;i++){
		cin>>b[i];
	}
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++){
			if(b[i]>=a[j]){ //若满足条件
				cout<<j<<"\n";
				vis[i]=1;
				break;
			}
		}
		if(!vis[i])cout<<-1<<"\n"; //没人吃寿司
	}
	sjh0626s code;
}
```
很明显，这个代码会 TLE ，我们该怎么优化呢？
### 优化
考虑到 $c_i \ne -1$ 时 $a_i \ge b_i$，所以我们可以对 $b_i$ 进行排序，然后双指针即可完成。

```cpp
#include<bits/stdc++.h>
#define sjh0626s return
#define code 0
using namespace std;
int n,m,a[300010];
int c[300010];
struct sushi{
	int v,id;
}b[300010];
bool cmp(sushi x,sushi y){
	if(x.v!=y.v)return x.v>y.v;
	return x.id<y.id;
}
int main(){
	cin>>n>>m;
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0); 
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=m;i++){
		cin>>b[i].v;
		b[i].id=i;
	}
	sort(b+1,b+m+1,cmp);
	int j=1;
	for(int i=1;i<=n;i++){
		while(b[j].v>=a[i])c[b[j].id]=i,j++; //若符合，则标记，往后延续
	}
	for(int i=1;i<=m;i++)cout<<(c[i]!=0?c[i]:-1)<<"\n";
	sjh0626s code;
}
```

---

## 作者：cqbzcjh (赞：1)

由于寿司是滚动，我们可以将这个问题转换为：**对于每个寿司，求第一个小于等于它的人的位置**。

我们将人的编号记录下来，再按照美食水平从小到大排序。通过二分查找所有小于等于当前寿司的人，他们之中编号的最小值即为答案。其中求编号的最小值可以通过求前缀最小值线性地完成。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,m,b[N],ans[N],minn[N];
struct node{int v,p;}a[N];//p为编号
bool cmp(node x,node y){return x.v<y.v;}
int main(){
	ios::sync_with_stdio(NULL);
	cin.tie(NULL);cout.tie(NULL);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i].v;
		a[i].p=i;
	}
	for(int i=1;i<=m;i++)cin>>b[i];
	sort(a+1,a+n+1,cmp);
	minn[1]=a[1].p;
	for(int i=2;i<=n;i++)
		minn[i]=min(minn[i-1],a[i].p);
	//求前缀最小值
	for(int i=1;i<=m;i++){
		int l=1,r=n;
		//二分查找
		while(l<r){
			int mid=(l+r+1)>>1;
			if(a[mid].v<=b[i])l=mid;
			else r=mid-1;
		}
		if(a[l].v>b[i])ans[i]=-1;//判断无解
		else ans[i]=minn[l];
	}
	for(int i=1;i<=m;i++)cout<<ans[i]<<"\n";
	return 0;
}
```

---

## 作者：hjyowl (赞：1)

### 思路

#### 朴素解法

对于每一个寿司，寻找第一个美食级别小于等于他的人，然后输出，时间复杂度 $\Theta(nm)$，会超时。

#### 正解做法

由于这个序列没有单调性，不可以直接二分。

但是我们可以对 $a$ 求一个前缀最小值，前缀最小值序列一定单调递减，这样答案有了单调性，然后二分找到第一个前缀最小值小于等于当前这个寿司的美味度的人，然后输出即可。

时间复杂度：$\Theta(m \log n)$。

### 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const long long N = 200010;
long long n,m;
long long a[N],b[N],s[N];
bool debug = 0;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin >> n >> m;
	s[0] = 1e18;
	for (long long i = 1; i <= n; i ++ ){
		cin >> a[i];
		s[i] = min(s[i - 1],a[i]);
	}
	for (long long i = 1; i <= m; i ++ ){
		cin >> b[i];
		long long l = 1,r = n;
		while (l < r){
			long long mid = l + r >> 1;
			if (b[i] >= s[mid]){
				r = mid;
			}
			else{
				l = mid + 1;
			}
		}
		if (b[i] >= s[l]){
			cout << l << endl;
		}
		else{
			cout << -1 << endl; 
		}
	}
	return 0;
}
```

---

## 作者：Allen_yang (赞：0)

## 题目描述
大致意思如下：
有 $n$ 个人，每个人有一个品味值 $a_i$，有 $m$ 道寿司，每道寿司的美味值 $b_i$，按照从 $1$ 到 $m$ 的顺序一次经过每个人。对于每个人，如果当前经过他的寿司美味值 $b_j \ge a_i$ 则该寿司会被吃掉，并且不会经过下一个人。

请求出第 $i$ 个寿司是被谁吃掉的，输出编号。如果没有人吃它，则输出 `-1`。
## 题目分析
不安发现，第 $i$ 个寿司如果会被第 $j$ 人吃掉，那么当且仅当 $b_i\ge a_j$ 且 $j$ 最小。也就是说，第 $i$ 个人能吃到 $j$ 号寿司的条件为：$b_j\ge a_i$ 且 $b_j< a_k(k<i)$，可以理解为之前的人没吃过。这是否意味着从 $1$ 到 $n$ 的每个人吃掉的寿司美味值在总体上（只考虑人与人之间的差异）是单调下降的。

那么可以将 $b_j(j\le n)$ 从大到小排序，每次遍历找到 $a_i > b_j$ 的临界坐标并存储之前的 $b_j$ 所对应的答案，下一次 $a_{i + 1}$ 直接从临界坐标开始找就行。
### 题目复杂度
总共相当于遍历了所有的寿司，其总复杂度约为 $\mathcal{O}(m)$。
## 代码实现
```cpp
#include <iostream>
#include <algorithm>
using namespace std;
const int MAXN = 200005;
int a[MAXN], ans[MAXN];
struct Node{
	int del, id;
}b[MAXN];
bool cmp(Node x, Node y){
	return x.del > y.del;
}
int main(){
	int n, m;
	cin >> n >> m;
	for(int i = 1; i <= n; i ++){
		cin >> a[i];
	}
	for(int i = 1; i <= m; i ++){
		cin >> b[i].del;
		b[i].id = i;
		ans[i] = -1;
	}
	sort(b + 1, b + 1 + m, cmp);
	int last = 0;
	for(int i = 1; i <= n; i ++){
		for(int j = last + 1; j <= m; j ++){
			if(b[j].del >= a[i]){
				last = j;
				ans[b[j].id] = i;
			}else{
				break;
			}
		}
	}
	for(int i = 1; i <= m; i ++){
		cout << ans[i] << "\n";
	}
	return 0;
}
```

---

## 作者：Liuhy2996 (赞：0)

## 思路
二分答案，问题转化为 $A_1$ 到 $A_{mid}$ 中有没有一个数小于等于 $B_j$。维护前缀最小值即可。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+10,inf=1e15;
int n,m,x,a[N];
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;++i){
		cin>>a[i];
		if(i>1) a[i]=min(a[i],a[i-1]);
	}
	while(m--){
		cin>>x;
		int l=1,r=n;
		while(l<r){
			int mid=(l+r)>>1;
			if(a[mid]<=x) r=mid;
			else l=mid+1;
		}
		cout<<(a[n]<=x?l:-1)<<endl;
	}
	return 0;
}
```

---

## 作者：JXR_Kalcium (赞：0)

无语了……快排卡到我 $O(N^2)$ 当场趋势。

## 题目大意

现在给定 $N$ 个数 $A_i$，编号分别为 $1,2,\cdots,N$。现给定 $M$ 次询问，每次给定一个数 $B_i$，请查询编号最小的 $j$ 满足 $A_j\le B_i$，若没有满足条件的编号则输出 $-1$，数据范围 $N,M\le 2\times 10^5$。

## 解题思路

首先考虑如何查询所有满足条件的 $j$，再考虑如何查询编号最小。对于满足条件的所有数，可以先对 $A$ 序列从小到大排序，再计每一个 $A_i$ 原先的编号为 $P_i$，这样对于每组询问只需用 $O(\log N)$ 的时间二分，找到分界线 $k$ 即可（即排序后的 $\{A_1,A_2,\cdots,A_k\}\le B_i$）。之后考虑如何计算 $\min_{i=1}^{k} P_i$。可以发现，因为排序后的 $A$ 序列是一定的，所以只需预处理从 $1$ 到任意值中原先编号的最小值。计 $pos_x$ 表示 $\min_{i=1}^{x} P_i$，则有显然的转移：

$$
pos_x\leftarrow \min(pos_{x-1},P_x)
$$

最后的答案即为 $pos_k$，对于 $-1$ 特判一下即可（也可以把二分的边界设为 $-1$）。

## AC 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define endl putchar(10)
#define spc putchar(32)
#define R register
using namespace std;
#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x << " = " << x, endl
#endif

inline ll read()
{
    ll x=0,f=1; char c=getchar();

    while(c<48 || c>57)
    {
        if(c=='-') f=-1;
        c=getchar();
    }

    while(c>47 && c<58)
    x=(x<<1)+(x<<3)+c-48, c=getchar();
    return x*f;
}

inline void write(ll x)
{
    static ll sta[41]; ll top=0;
    if(x<0) putchar('-'), x=-x;
    do sta[top++]=x%10, x/=10; while(x);
    while(top) putchar(sta[--top]+48);
}

ll n,m,x,pos[200002]={INT_MAX},l,r,mid,p;
struct node {ll x,y;} a[200001];
bool cmp(node x, node y) {return x.x<y.x || x.x==y.x && x.y<y.y;}

int main()
{
    n=read(); m=read();
    for(R int i=1; i<=n; ++i) a[i]={read(),i};
    sort(a+1,a+n+1,cmp);
    for(R int i=1; i<=n; ++i) pos[i]=min(pos[i-1],a[i].y);
    pos[0]=-1;
    
    while(m--)
    {
        x=read(); l=0; r=n; p=0;

        while(l<=r)
        {
            mid=l+r>>1;
            if(a[mid].x>x) r=mid-1;
            else l=mid+1, p=mid;
        }

        write(pos[p]); endl;
    }

    return 0;
}
```

---

## 作者：__galaxy_1202__ (赞：0)

掉贡献了，来回回血。
## 解题思路：
考虑到**不会吃当前最美味的寿司的人绝对不会吃其他寿司**。  


因此，我们可以将寿司按美味度从大到小排序，并把每个人的美食品味与编号存到优先队列里，这样就能**把美食品味度比当前所有寿司都大的人逐个踢出，再标记一下，那么当前没被标记的最小编号的人就是这块寿司的答案了。**  


具体实现见代码。
## CODE：

```cpp
#include <queue>
#include <iostream>
#include <algorithm>
using namespace std;
#define int long long
int n, m, a, mm = 1e18, ans[200001];//mm 用于记录最小值，特判 -1.
bool vis[200001];
priority_queue < pair <int, int> > qp;//大根堆，存当前美食品味最高的人和他的编号。
//这里为了省事，利用了 pair 类型在堆里按第一个关键字排序的特性，不用重载运算符了。
priority_queue <int, vector <int>, greater <int> > qwq;//小根堆，存当前最小的没被标记掉的人的编号。
struct node{int x, id;}b[200001];
bool cmp(node a, node b)
{
	if (a.x != b.x) return a.x > b.x;
	return a.id > b.id;
}
signed main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        cin >> a;
        mm = min(mm, a);
        qp.push({a, i});
        qwq.push(i);
    }
	for (int i = 1; i <= m; i++)
	{
		cin >> b[i].x;
		b[i].id = i;
	}
    sort(b + 1, b + m + 1, cmp);
    for (int i = 1; i <= m; i++)
    {
        if (b[i].x < mm)
        {
            ans[b[i].id] = -1;
            continue;
        }
        while (!qp.empty() && qp.top().first > b[i].x) 
        {
            vis[qp.top().second] = 1;
            qp.pop();
        }
        while (!qwq.empty() && vis[qwq.top()]) qwq.pop();//由于只有队首对当前答案有影响，所以只要先踢掉前面的，后面的轮到了再踢。
		ans[b[i].id] = qwq.top();
    }
	for (int i = 1; i <= m; i++) cout << ans[i] << '\n';
    return 0;
}
```

---

## 作者：wei2013 (赞：0)

## 思路：
对于每个人进行考虑，对每个寿司取前缀最小值，显然具有单调性，考虑二分，直接输出二分的结果即可。

时间复杂度：$\mathcal{O(n\log{m})}$。
## code:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN=2e5+5;
int n,m,a[MAXN],b[MAXN],p[MAXN];
signed main(){
    cin>>n>>m;
    p[0]=1e18;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		p[i]=min(p[i-1],a[i]);
	}
	for(int i=1;i<=m;i++){
		cin>>b[i];
	}
    int ans;
    for(int i=1;i<=m;i++){
        ans=lower_bound(p+1,p+n+1,b[i],[](const auto a,const auto b){return a>b;})-p;
        if(ans<=n){
        	cout<<ans<<endl;
		}else{
			cout<<-1<<endl;
		}
    }
    return 0;
}
```

---

## 作者：long_long__int (赞：0)

赛时我先过的 D 再过的 C。

# 题目翻译

有 $n$ 个人和 $m$ 个寿司，第 $i$ 个人对寿司美味度的要求是 $a_i$，每个寿司的美味度是 $b_i$，寿司被放在传送带上（即从第 $1$ 个人开始一个一个摆在那个人的面前），如果第 $i$ 块寿司到了第 $j$ 个人的面前，且 $a_j\le b_i$，那么第 $j$ 个人会吃掉第 $i$ 块寿司，被吃掉的寿司不会经过第 $(j+1)\sim n$ 个人的面前。

# 题目解法

## 算法

思路比较难想。首先，暴力枚举寿司的经过路程的时间复杂度（$O(nm)$）肯定会 TLE，那么可以考虑将前 $i$ 个人的**最小的 $a_i$** 存到数组 $s$ 里，然后对于每块寿司进行二分，找到最前面的 $s_x$ 满足 $s_x\le b_i$ 然后输出 $x$ 即可。时间复杂度 $O(m \log n)$。

## 正确性

- 数组的单调性：因为前几个的最小值不会增大，所以数组 $s$ 满足不上升。
- 为什么得到的结果就是答案：因为满足 $s_x\le b_i$ 的最小的 $x$，一定有 $s_x=a_x$（$s_x$ 一定存在在 $a$ 数组里，如果存在 $s_x<a_x$，就说明前面还有 $y$ 满足 $s_y\le b_i$，与前文中最小的 $x$ 矛盾，所以不存在这样的 $y$）。

代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m;
int a[200500];
int minn[200500];
int bi(int x){
	int l=1,r=n,ans=-1;
	while(l<=r){
		int mid=l+((r-l)>>1);
		if(minn[mid]<=x){
			ans=mid;
			r=mid-1;
		}else{
			l=mid+1;
		}
	}
	return ans;
}
signed main(){
	memset(minn,0x7f,sizeof minn);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		minn[i]=min(minn[i-1],a[i]);
	}
//	for(int i=1;i<=n;i++){
//		cout<<minn[i]<<" ";
//	}
//	puts("");
	for(int i=1;i<=m;i++){
		int b;
		cin>>b;
		cout<<bi(b)<<"\n";
	}
	
	return 0;
}

```

---

## 作者：T_TLucas_Yin (赞：0)

我可能是唯一一个使用线段树的人了。

注意到，当第 $i$ 个寿司顺序流过 $n$ 个人的面前时，会被第一个满足 $A_j\ge B_i$ 的人 $j$ 吃掉。所以对于每一个寿司，我们从整个序列开始二分区间最大值，若当前区间最大值 $\ge B_i$，则再向左半区间查找，否则向右半区间查找。

为了快速获得序列中一个区间内的 $A_i$ 最大值，对 $A$ 数组开一棵线段树存储即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[1000005],b[1000005];
int f[4000005];
void build(int root,int l,int r){
	if(l==r){ f[root]=a[l];return; }
	int mid=(l+r)>>1;
	build(root<<1,l,mid);
	build(root<<1|1,mid+1,r);
	f[root]=min(f[root<<1],f[root<<1|1]);
}
int Find(int root,int l,int r,int fl,int fr){
	if(fl<=l&&r<=fr) return f[root];
	int mid=(l+r)>>1,minn=2e9;
	if(fl<=mid) minn=min(minn,Find(root<<1,l,mid,fl,fr));
	if(fr>mid) minn=min(minn,Find(root<<1|1,mid+1,r,fl,fr));
	return minn;
}
int main(){
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=m;i++) scanf("%d",&b[i]);
	build(1,1,n);
	for(int i=1;i<=m;i++){
		if(f[1]>b[i]){ printf("-1\n");continue; }
		int l=1,r=n,mid,k=n;
		while(l<=r){
			mid=(l+r)>>1;
			if(Find(1,1,n,l,mid)<=b[i]) r=mid-1,k=mid;
			else l=mid+1;
		}
		printf("%d\n",k);
	}
	return 0;
}
```

---

## 作者：fanjiayu666 (赞：0)

### 背景
没打比赛，赛后一天看完题目发现：亏了，亏他那么简单！
### 思路：

#### 题目大意
题目大致意思是，给定 $N$ 个人，$M$ 个食物，每个人有一个等级 $A_i$，每个食物有一个美味值 $B_j$，食物会依次经过第 $[1,2,\dots ,n]$ 个人，当这个食物的美味值大于面前人的等级时，他就会吃掉，并且不再传送到之后的人手里。

#### 思考过程
很容易想到 $O(nm)$ 算法，依次查找每个食品对应的人，但明显超时，因为 $1\le N,M \le 2\times 10^5$。

接下来我们再分析一下：对于每一个食物，只对应一个人，只要大于这个人的等级就会被他吃掉，所以设一个数组 $ans$，记录美味值为 $x$ 的食品会被第 $ans_x$ 个人吃掉。

对于第 $i$ 个人：$ans_{A_i}$ 之后的所有的位置（等价于 $B_j$ 大于 $A_i$ 的可能值）都是第 $i$ 个人吃。

注意：$ans$ 数组要初始化。
#### 主要代码：
```cpp
for(int i=1;i<=n;i++){
    cin>>tmp;
    while(r>tmp){
        r--;
        ans[r]=i;
    }
}
for(int i=1;i<=m;i++){
    cin>>tmp;
    cout<<ans[tmp]<<"\n";
}
```

### 难度建议

本题思维难度有，不是那种一眼题，建议评橙、红，评红有些低，但也合理。

---

## 作者：banglee (赞：0)

## AT_abc382_c [ABC382C] Kaiten Sushi 题解
[洛谷传送门](https://www.luogu.com.cn/problem/AT_abc382_c)

[AtCoder 传送门](https://atcoder.jp/contests/abc382/tasks/abc382_c)
## 思路
考虑构建一个数组 $b$，$b_x$ 表示美味程度为 $x$ 的寿司将被哪个顾客所食用。

从最高的美味程度开始，遍历所有顾客，为每个美味程度 $x$ 填入一个食用该寿司的顾客编号。

对于每位顾客 $i$，检查其美食度。如果当前美味程度 $x$ 大于等于 $a_i$，就将 $b_x$ 更新为 $i$。这样，当递减美味程度时，能够保证 $b$ 数组中存储的顾客永远是第一个能够接受该美味寿司的顾客。

时间复杂度为 $\mathcal{O}(N + M)$。
### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,now=200000,a[200005],b[2000005];
signed main() {
    ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    cin>>n>>m;
    for (int i=1;i<=n;i++)
        cin>>a[i];
    memset(b,-1,sizeof(b));
    for (int i=1;i<=n;i++)
        while (now>=a[i])
            b[now--]=i;
    for (int i=1,x;i<=m;i++)
        cin>>x,cout<<b[x]<<'\n';
    return 0;
}
```

---

## 作者：xiaoke2021 (赞：0)

好题。

---

让我们模拟一下寿司（们）是怎么被吃掉的。

1. 所有寿司端到第 1 个人面前，ta 把 ta 能吃的寿司都吃了；

2. 剩下的寿司端到第 2 个人面前，ta 把 ta 能吃的寿司都吃了；

3. 剩下的寿司端到第 3 个人面前，ta 把 ta 能吃的寿司都吃了；

一直到：

- 剩下的寿司端到第 $n$ 个人面前，ta 把 ta 能吃的寿司都吃了。

所以发现，前面的人先吃，后面的人只能吃剩下的，不难发现寿司是否被一个人吃是与这个寿司端到此人面前的顺序 **无关** 的，因为一个寿司如果能被此人吃掉，那肯定不会被后面人先吃。这是一个伏笔。

那么可以得到思路：对于依次的每一个人，将 ta 能吃到的所有寿司的答案修改为 ta 的编号；对于剩下的寿司，将其答案设为 -1。

这样的话对于每个人都要遍历一遍每个寿司，时间复杂度为 $O(nm)$，无法接受。

上面说过，寿司是否被一个人吃与这个寿司端到此人面前的顺序无关，所以可以将寿司按美味程度排序；对于第 $i$ 个人，用二分搜索 ta 可以吃的美味程度最小的寿司，记其编号为 $pos_i$，则编号在 $[pos_i,pos_{i-1}]$ 内的寿司的答案为 $i$。默认 $pos_0 = m$。

代码很好写。


```cpp
#include<bits/stdc++.h>
using namespace std;
struct T{
	int node,num;
}b[200000+5];
int n,m;
int a[200000+5],bb[200000+5];
int ans[200000+5];
bool cmp(T x,T y){
	return x.num<y.num;
}
int main(){
	memset(ans,-1,sizeof(ans));
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=m;i++) cin>>b[i].num,b[i].node=i;
	sort(b+1,b+1+m,cmp);
	for(int i=1;i<=m;i++) bb[i]=b[i].num;
	int pos=m+1; //相当于 pos[i-1]
	for(int i=1;i<=n;i++){
		int poss=lower_bound(bb+1,bb+pos,a[i])-bb; //相当于 pos[i]
		if(poss<=m){
			for(int j=poss;j<pos;j++) ans[b[j].node]=i;
			pos=poss;
		}
	}for(int i=1;i<=m;i++) cout<<ans[i]<<endl;
	return 0;
}

```

---

## 作者：Cosine_Func (赞：0)

注意到每次都会去掉大于等于某个数的一段区间，考虑排序后二分。需要维护右端点。注意特判无解的情况。时间复杂度 $O(M\times\log M+N\times\log M)$。

核心代码：
```cpp
struct Node{
	itn id,val,vis;
	bool operator<(const Node &b)const{
		return val<b.val;
	}
}b[N];
int n,m,r,a[N],c[N],d[N];
inline void Solve(){
	cin>>n>>m;
	r=m;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<=m;i++)
		cin>>b[i].val,b[i].id=i;
	sort(b+1,b+m+1);
	for(int i=1;i<=m;i++)
		d[i]=b[i].val;
	for(int i=1;i<=n;i++){
		int j=lower_bound(d+1,d+r+1,a[i])-d-1;
		while(d[j+1]>d[j] and d[j]<a[i] and j+1<=r)j++;
		//cout<<'#'<<d[j]<<' '<<a[i]<<endl;
		if(d[j]>=a[i]){
				for(int k=j;k<=r;k++)
					c[b[k].id]=i;
			r=j-1;
		}
	}
	for(int i=1;i<=m;i++)
		cout<<(c[i]?c[i]:-1)<<endl;
}
```
[参考代码](https://atcoder.jp/contests/abc382/submissions/60323176)

---

## 作者：zeroflows (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/AT_abc382_c)

## 思路

首先看一下数据范围。

- $1 \leq N, M \leq 2 \times 10^5$
- $1 \leq A_i, B_i \leq 2 \times 10^5$

这么大的数据范围肯定不能直接写二重循环暴力。

---

考虑一下，应为它是从每个人面前顺序经过的。那我们就可以按照顺序，依次枚举这 $N$ 个人。\
首先记录这些食物对应的序号，再的按照美味度从小到大排序。\
依次枚举这 $N$ 个人，只要发现一个不小于他的品味值的食物，就给这个食物打上标记，同时指针往前移一位。\
如果所有的食物都已经被打上了标记，就提前跳出循环。\
否则到最后的时候，就按照标记输出，如果这个食物没有被打上标记，就输出 `-1`。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
struct no
{
	int x,y;
}h[1000000];
int cmp(no q,no w)
{
	return q.x<w.x;
}
int hh[1000000];
int a[1000000];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(),cout.tie();
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<=m;i++)
	{
		cin>>h[i].x;
		h[i].y=i;
	}
	sort(h+1,h+m+1,cmp);
	int x=m+1;
//	for(int i=1;i<=m;i++)
//	cout<<h[i].x<<" ";
//	cout<<endl;
//	for(int i=1;i<=m;i++)
//	cout<<h[i].y<<" ";
	for(int i=1;i<=n;i++)
	{
		if(x==0)
			break;
		while(1)
		{
			x--;
			if(h[x].x>=a[i])
			{
				hh[h[x].y]=i;
			}
			else
			{
				x++;
				break;
			}
		}
	}
	for(int i=1;i<=m;i++)
	{
		if(hh[i]==0)
		cout<<-1;
		else
		cout<<hh[i];
		cout<<endl;
	}
}
```

---

