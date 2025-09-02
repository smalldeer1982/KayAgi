# 【MGVOI R1-B】完美重排（sort）

## 题目描述

Siby 同学有一个长度为 $n$ 的数组 $a$，其下标编号为 $1 \sim n$。保证数组 $a$ 是一个长度为 $n$ 的排列，也就是说，$1\sim n$ 中的每个正整数都在数组 $a$ 中出现 **恰好一次**。

在此基础上，Siby 同学定义了 **完美重排** 操作：

::::info[完美重排的定义]{open}

* 第一步：选择两个下标 $L,R$（必须满足 $1\le L\le R\le n$）；
  
* 第二步：将 $a_L,...,a_R$ （即数组 $a$ 中下标在 $L$ 和 $R$ 之间的元素）按照 **从小到大** 的顺序重新排序。

::::

例如，若 $a=[4,3,2,1]$，选择 $L=2,R=4$ 进行一次完美重排操作（也就是将 $a_2,a_3,a_4$ 按照从小到大的顺序排序），得到的新数组为 $a'=[4,1,2,3]$。

接下来，他将进行 $Q$ 组询问（询问之间彼此独立），其中第 $i$ 组询问包含两个参数 $x_i,y_i$（$x_i< y_i$），表示询问你有多少种进行 **恰好一次** 完美重排的方案，使得数组 $a$ 中原先下标为 $x_i$ 的元素，在重排后的下标为 $y_i$。

提示：只要完美重排操作中选择的 $L$ 不同或 $R$ 不同，就被认为是两种不同的方案。

## 说明/提示


**【样例 #1】**

::::info[样例 #1 解释]
此样例下，$a=[3,4,1,2]$。

* 对于第一组询问：只需取 $L=1，R=4$ 进行一次完美重排，就能使得 $a_1$ 在重排后的下标为 $3$（重排前：$a=[\red{3},4,1,2]$，重排后：$a'=[1,2,\red{3},4]$）。可以证明这是唯一的一种方案，故方案数为 $1$；

* 对于第二组询问：可以证明，无论如何选取 $L,R$，都不可能使得 $a_1$ 在重排后的下标为 $4$，故方案数为 $0$；

* 对于第三组询问：

1. 第一种方案是取 $L=1，R=4$ 进行一次完美重排（重排前：$a=[3,\red{4},1,2]$，重排后：$a'=[1,2,3,\red{4}]$）；
  
2. 第二种方案是取 $L=2，R=4$ 进行一次完美重排（重排前：$a=[3,\red{4},1,2]$，重排后：$a'=[3,1,2,\red{4}]$），可以验证均满足条件。不存在其它满足条件的方案了，故方案数为 $2$。
::::


**【样例 #2】**

::::info[样例 #2 解释]
此样例下，$a=[6,3,5,7,2,4,1]$。

为了简便，我们用数对 $(i,j)$ 来表示选取 $L=i$，$R=j$ 进行一次完美重排的方案。各组询问对应的所有方案见下表：

| 询问编号 | 方案数 | 方案 1 | 方案 2 | 方案 3 | 方案 4 |
|:-:|:-:|:-:|:-:|:-:|:-:|
| **1** | $2$ | $(1,3)$ | $(1,4)$
| **2** | $1$ | $(1,5)$
| **3** | $0$ |
| **4** | $3$ | $(1,7)$ | $(2,5)$ | $(2,6)$
| **5** | $1$ | $(2,7)$
| **6** | $0$ |
| **7** | $3$ | $(1,7)$ | $(2,6)$ | $(3,6)$
| **8** | $4$ | $(1,6)$ | $(2,6)$ | $(3,6)$ | $(4,6)$ 
| **9** | $1$ | $(5,7)$ |
| **10** | $2$ | $(5,7)$ | $(6,7)$ |

::::



**【样例 #3】**

见附件中的 ```sort/sort3.in``` 与 ```sort/sort3.ans```。

这个样例满足测试点 $7 \sim 12$ 的限制。

**【样例 #4】**

见附件中的 ```sort/sort4.in``` 与 ```sort/sort4.ans```。

这个样例满足测试点 $13 \sim 14$ 的限制。

**【样例 #5】**

见附件中的 ```sort/sort5.in``` 与 ```sort/sort5.ans```。

这个样例满足测试点 $15 \sim 20$ 的限制。



---




**【数据范围】**

对于所有测试点，保证 $2\le n\le 10^4$，$1\le Q\le 2\times 10^3$，$1\le x_i< y_i\le n$，且数组 $a$ 是 $1\sim n$ 的排列。

::cute-table{tuack}

| **测试点编号** | $n \le$ | $Q \le$ |  **特殊性质** |
|:-:|:-:|:-:|:-:|
| $1 \sim 6$ | $20$ | $20$ | 无 | 
| $7 \sim 12$ | $500$ | $100$ | ^ | 
| $13 \sim 14$ | $10^4$ | $2\times 10^3$ | **A** | 
| $15 \sim 20$ | ^ | ^ | 无 | 

特殊性质 **A**：保证 $a_i=n-i+1$。

* 分值分配：每个测试点的分值为 $5$ 分。
  
* 请注意本题特殊的内存限制。

## 样例 #1

### 输入

```
4 3
3 4 1 2
1 3
1 4
2 4```

### 输出

```
1
0
2```

## 样例 #2

### 输入

```
7 10
6 3 5 7 2 4 1
1 3
1 4
1 7
2 3
2 4
2 5
3 5
4 6
5 6
6 7
```

### 输出

```
2
1
0
3
1
0
3
4
1
2```

# 题解

## 作者：zengyongxu (赞：7)

是一道黄体，感觉还不错，来写一篇题解纪念考场的不懈奋斗。

至少，我 AC 了这道题。

[题目传送门](https://www.luogu.com.cn/problem/P13730)

### 解题思路

首先，看到这道题，想到的是 $O(n^2)$ 做法，没细想，然后看到数据范围，正好发现做法不是 $O(n^2)$ 的，而是 $O(nQ)$ 的。~~然后我就发现做法假了。~~

我想到的是双指针，貌似左端点递增的情况下，右端点递减。然后发现不一定，所以双指针错了。

由于我比较懒，所以不想考虑有没有比 $O(nQ)$ 更优的做法了，一直往 $O(nQ)$ 的做法考虑。

### 正解

不妨设当前要让原本在下标为 $x$ 的数在一次完美重排之后变到下标 $y$ 的地方。

依旧是枚举左端点，不妨设当前左端点在下标为 $l$ 的地方。

考虑转化问题。

问题等价于找一个 $r$ 使得 $l \sim r$ 之间有 $y-l$ 个比 $a_x$ 大的数。

不难发现，对于当前的 $l$，$r$ 的取值区间一定是连续的。

设在 $l \sim x$ 的范围内，小于 $a_x$ 的数有 $cnt$ 个。

我们只需要统计，当 $x \leq r \leq n$ 时，有多少个 $r$ 满足 $x \leq r$ 中有 $y - l - cnt$ 个数是小于 $a_x$ 的。

发现上面的值是可以预处理的，使用一个计数数组 $c$，每次统计答案的时候答案加上 $c_{y-l-cnt+1} - c_{y-l-cnt}$ 即可。

同样的 $cnt$ 也是可以处理的。

### 代码 & 代码解释

:::success[AC code]
```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 1e4 + 5;

int n, q, a[N], pos[N];

inline int read(){
	int x = 0; char ch = getchar();
	while (ch < '0' || ch > '9') ch = getchar();
	while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
	return x;
}

int main(){
	ios::sync_with_stdio(0), cin.tie(0);
	
	cin >> n >> q;
	for (int i = 1; i <= n; i ++ ) cin >> a[i];
	while (q -- ){
		memset(pos, 0, sizeof pos);
		int x, y; cin >> x >> y;
		
		int cnta = 0, cntb = 0;
		for (int i = 1; i < x; i ++ ) if (a[i] < a[x]) cnta ++;
		for (int i = x + 1; i <= n; i ++ ){
			if (a[i] < a[x]){
				cntb ++;
				pos[cntb] = i;
			}
		}
		pos[cntb + 1] = n + 1;
		
		int ans = 0;
		for (int i = 1; i <= x; i ++ ){
			int nd = y - i;
			if (i > 1 && a[i - 1] < a[x]) cnta --;
			if (nd - cnta <= cntb) ans += pos[nd - cnta + 1] - pos[nd - cnta];
		}
		
		cout << ans << "\n";
	}
} 
```
:::

代码解释：
1. $pos$ 数组就是上文中的 $c$ 数组。
2. $cnta$ 就是上文中的 $cnt$。
3. $i$ 就是上文中的 $l$。
4. $ans$ 顾名思义就是统计答案的变量。

---

## 作者：zbl2012 (赞：2)

## Solution

### 主要知识点

* 【2】乘法原理
* 【3】递推法
* 【3】前缀和
* 【3】冒泡排序

---

### Subtask 1：测试点 $\bm{1\sim 6}$

直接枚举 $L$ 和 $R$ 然后 ```std::sort()```
模拟即可，时间复杂度 $O(Q\cdot n^3 \log n)$。

---

### Subtask 2：测试点 $\bm{7\sim 12}$

考虑优化 Subtask 1 的做法至 $O(Q\cdot n^2)$。

我们发现，假设刚计算完对区间 $[L,R]$ 进行完美重排后，原先下标为 $x_i$ 的数的新位置为 $z_i$（显然应满足 $L\le x_i \le R$，否则 $x_i$ 不在重排区间内），那么接下来枚举区间 $[L,R+1]$ 时，还用重新模拟一遍排序吗？

实际上没必要。由于我们只关心原先下标为 $x_i$ 的数（记为 $m$）在重排后的位置，所以可以由 $[L,R]$ 这个区间的情况直接递推到 $[L,R+1]$：

* 若 $a_{R+1}<m$，则 $z_i$ 的值增加 $1$；
  
* 若 $a_{R+1}>m$，则 $z_i$ 的值不变。

模拟一下发现是很好理解的，因为当 $a_{R+1}<m$ 时，重排区间新加入的 $a_{R+1}$ 这个元素由于比 $m$ 更小，在排序后将 $m$ “顶”到了后面一个位置（类比冒泡排序）；而 $a_{R+1}>m$ 时，对 $m$ 的位置则没有贡献。

同理，也可以由区间 $[L,R]$ 的情况（$L\le x_i \le R$）递推到区间 $[L-1,R]$：

* 若 $a_{L-1}>m$，则 $z_i$ 的值减小 $1$（将 $a_{L-1}$ 纳入重排区间后，$m$ 被向前“推”了一个位置）；
  
* 若 $a_{L-1}<m$，则 $z_i$ 的值不变。

综上，我们只需用双重循环枚举 $L,R$，并按上述规则实时维护 $z_i$，就能 $O(1)$ 地得出每个区间的答案，时间复杂度 $O(Q\cdot n^2)$。

---

### Subtask3： 测试点 $\bm{13\sim 20}$

考虑将时间复杂度优化至 $O(Q\cdot n)$。

承 Subtask 2，我们只关心 $m$ 的位置，于是考虑将数组 $a$ 重新扫一遍，得到一个新数组 $b$：

* 情况 1：若 $j<x_i$ 且 $a_j>m$，则 $b_j=-1$；
  
* 情况 2：若 $j>x_i$ 且 $a_j<m$，则 $b_j=+1$；

* 其它情况，$b_j=0$。

数组 $b$ 的意义是什么呢？类比上一个 Subtask 的区间递推，我们发现和之前一样，情况 1 可以等效成将 $a_j$ 纳入重排区间后，将 $m$ 向前“推”了一位；而情况 2 可以等效成将 $a_j$ 纳入重排区间后，将 $m$ 向后“顶”了一位。

那么可以观察到：对区间 $[L,R]$ 进行完美重排之后（$L\le x_i\le R$），$m$ 对应的下标就是 $x_i+\sum\limits_{j=L}^R b_j$，这就很清晰了!

于是就等价于问你在值域为 $\{ -1,0,1 \}$ 的数组 $b$ 中，有多少对 $(L,R)$ 满足 $b_L+...+b_R=y_i-x_i$，并且 $L\le x_i\le R$。

一种做法是你可以算出 $b$ 的前缀和 $b'$，化为 $b'_R-b'_{L-1}=y_i-x_i$，然后这就变成了一个 [A - B 数对模板题](https://www.luogu.com.cn/problem/P1102)。当然，我们这里还是采取另一种做法，充分利用一下值域为 $\{ -1,0,1 \}$ 的特性，具体地：

* 第一步，记录 $x_i$ 之前所有 $-1$ 的位置和 $x_i$ 之后所有 $+1$ 的位置。显然，每两个相邻的 $-1$ （或每两个相邻的 $+1$）之间会隔若干个 $0$。
  
* 第二步，根据上述分析，在我们选出的区间中，$+1$ 的个数要恰好比 $-1$ 的个数多 $y_i-x_i$。那么直接枚举 $-1$ 取多少个，这样 $+1$ 取多少个也就确定了。

* 第三步，确定了 $+1$ 和 $-1$ 取多少个之后，只需再用乘法原理统计一下它们后面 / 前面的 $0$ 要怎么选。之前已经记录过所有 $-1$ 和 $+1$ 的位置，注意细节实现一下即可。



时间复杂度 $O(Q\cdot n)$。

---

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,Q,a[15005];
int x,y;
int L[15005],R[15005];
void solve(){
	cin>>n>>Q;
	for(int i=1; i<=n; i++){
		cin>>a[i];
	}
	while(Q--){
		cin>>x>>y;
		int index=x,cntL=0,cntR=0;
		while(index<=n){
			if(a[index]<a[x])
				R[++cntR]=index;
			
			++index;
		}
		index=x;
		while(index>=1){
			if(a[index]>a[x])
				L[++cntL]=index;
			
			--index;
		}
		L[0]=R[0]=x;
		L[cntL+1]=0,R[cntR+1]=n+1;
		int ans=0;
		for(int i=0;true;i++){
			if(y-x+i>cntR||i>cntL)
				break;	
			ans+=(R[y-x+i+1]-R[y-x+i])*(L[i]-L[i+1]);
		}
		cout<<ans<<'\n';
	}
	return;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int _=1;
	while (_--){
		solve();
	}
	return 0;
}
```

---

## 作者：IloveLG (赞：2)

# P13730 【MGVOI R1-B】完美重排（sort）题解
## [P13730 题面传送门](https://www.luogu.com.cn/problem/P13730)
#### 思路：
其实我第一次看到这道题目是也有点懵，这空间范围能写什么啊？当然若按**一般思路**，代码就应该遍历每一次排序，并找到所选数 $v$ 在所选位置 $y$ 的方案数。众所周知，每一次排序都有一个起始点和一个结束点，那我们能否去遍历这个起始点 $L$ 与结束点 $R$ 呢？

显然是可以的，要使该子区间进行排序后满足所选数 $v$ 在所选位置 $y$ 也就等价于所选数 $v$ 是子区间内的第 $y-L$ 大的数，这时就可以实用前缀和预处理一个数组 $t$ 计算比 $v$ 大的数字数，就可以在 $O(1)$ 的时间内计算出 $v$ 是区间内的第几大数，易得区间内比 $v$ 小的数是 $t[R]-t[L-1]$，所以该子区间符合题目要求条件时 $y-L=t[R]-t[L-1]$ 同样成立！方程化简可得 $t[L-1]-L=t[R]-y$，所以就可以**不断遍历子区间左右端点并计算是否符合上述方程。**
#### 关键代码解析:
###### 关键代码 $1$
每次循环初始化并计算前缀和，即计算每个子区间比 $v$ 大的数字的数量。
```
memset(t,0,sizeof(t));
for(int i=1;i<=n;i++)
{
    if(a[i]<v)t[i]=1;
    t[i]+=t[i-1];
}
```
###### 关键代码 $2$
每次循环初始化桶数组 $b$ 并将所遍历的左端点带入方程左侧并标记。
```
memset(b,0,sizeof(b));
for(int L=1;L<=x;L++)
{
    b[t[L-1]+N-L]++;
}
```
###### 关键代码 $3$
每次循环遍历右端点并查询该位置是否被标记。
```
for(int R=y;R<=n;R++)
{
    if(b[t[R]+N-y]>0)
    {
        ans+=b[t[R]+N-y];
    }
}
```
**注：关键代码 $2$ 与关键代码 $3$ 中为防止计算出现负数越界所以将数组下标整体增加。**
## AC代码：
```
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=10010;
const int N1=20010;//双倍大小桶数组
int n,q,a[N],t[N],b[N1];
signed main()
{
    cin>>n>>q;
    for(int i=1;i<=n;i++)
	{
        cin>>a[i];
    }
    while(q--)
	{
        int x,y;
        cin>>x>>y;
        int v=a[x],ans=0;//找到所选数
        memset(t,0,sizeof(t));
        for(int i=1;i<=n;i++)
        {
        	if(a[i]<v)t[i]=1;
        	t[i]+=t[i-1];
		}
		memset(b,0,sizeof(b));
        for(int L=1;L<=x;L++)
        {
        	b[t[L-1]+N-L]++;//为防止重复左端点（见题目样例1第3次询问）
		}//计算子区间左端点
		for(int R=y;R<=n;R++)
		{
			if(b[t[R]+N-y]>0)
			{
				ans+=b[t[R]+N-y];
			}
		}//判断子区间是否成立
        cout<<ans<<"\n";
    }
    return 0;
}
```
评价：题目难度不大但思路推导较为麻烦，但比赛时写错初始化了。

---

## 作者：shijingteng (赞：2)

这道题要我们求出所有符合条件的完美重排个数，很明显，暴力枚举会超时，所以可以尝试优化。

### 题目关键
我们要确保 $a[x]$ 在排序后被移动到位置 $y$。排序后 $a[x]$ 所处的位置就根据它在这一区间中的相对大小而变化。我们可以设 $v = a[x] $，排序后 $v$ 所在的位置就是开头位置加上区间中小于 $v$ 的元素的个数，我们设它为 $K$。

由于 $K$ 是区间中小于 $v$ 的元素的个数，所以可以通过类似前缀和的方式计算它。

### 优化
观察这个前缀和数组，不难发现，它一定是递增的，因为小于 $v$ 的元素的个数不会减少，所以就可以采用二分算法。

通过二分就可以快速求出符合条件的区间最后一位的下标，计算出来后，将这个区间加入到答案中最后输出就可以了。

### 具体代码：
```c++
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1e4+10;
int n,q,a[maxn],x,y,s[maxn],ans;
signed main(){
	scanf("%lld%lld",&n,&q);
	for(int i=1;i<=n;i++) scanf("%lld",a+i);
	while(q--){
		scanf("%lld%lld",&x,&y);
		int v=a[x];
		memset(s,0,sizeof(s));
		for(int i=1;i<=n;i++) s[i]=s[i-1]+(a[i]<v);
		ans=0;
		int minv=min(x,y);
		for(int i=1;i<=minv;i++){
			int rq=s[i-1]+(y-i);
			if(rq<0||rq>s[n]) continue;
			int l=x,r=n,low=n+1;
			while(l<=r){
				int mid=(l+r)>>1;
				if(s[mid]>=rq){
					low=mid;
					r=mid-1;
				}
				else l=mid+1;
			}
			if(low==n+1||s[low]!=rq) continue;
			l=low,r=n;
			int high=low;
			while(l<=r){
				int mid=(l+r)>>1;
				if(s[mid]==rq){
					high=mid;
					l=mid+1;
				}
				else r=mid-1;
			}
			ans+=high-low+1;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：zzym (赞：1)

## 方法思路

**要解决这个问题，我们需要为每个查询 $(x_i, y_i)$ 找到满足条件的 $(L, R)$ 对的数量，其中在完美重排操作后，原位于 $x_i$ 的元素会移动到 $y_i$。**
 
## 关键步骤：
操作会排序子数组 $a[L...R]$，将这部分变为升序。其他部分的元素保持不变。原位于 $x_i$ 的元素 $v = a[x_i]$ 在排序后需要位于 $y_i$。必须满足 $L \leq x_i \leq R$ 且 $L \leq y_i \leq R$，否则 $v$ 无法被移动到 $y_i$。排序后的子数组中，元素 $v$ 的位置取决于它在子数组中的相对排序位置。即，$v$ 应处于子数组的第 $k$ 小位置，其中 $k = y_i - L + 1$。确定 $L$ 的有效范围，确保 $L \leq \min(x_i, y_i)$ 且 $y_i - L + 1$ 是 $v$ 在 $a[L..R]$ 中的排序位置。这可以通过计算 $L = y_i + 1 - v$ 并验证其是否满足 $1 \leq L \leq \min(x_i, y_i)$。一旦确定有效的 $L$，$R$ 必须满足 $R \geq \max(x_i, y_i)$ 且 $R \leq n$。方案数即为 $n - \max(x_i, y_i) + 1$。
 
### AC CODE
```
#include<bits/stdc++.h>
using namespace std;
/*
输入处理：首先读取数组长度  n  和查询次数  Q ，接着读取排列  a 。
查询处理：对于每个查询  (x_i（i是x的下标，下同理）, y_i) ：
计算原位置  x_i  上的值  v = a[x_i] 。
计算满足条件的起始下标  L = y_i + 1 - v 。这里  L  需要满足  1 <=L <=min(x_i, y_i) ，否则该查询结果为 0。
计算满足条件的最小结束下标  R_min = max(x_i, y_i) ，此时  R  的取值范围是  R_min  到  n ，共有  n -R_min + 1  种选择。
输出结果：根据上述计算，直接输出满足条件的  (L, R)  对的数量。
*/
int main() {
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n, Q;
    cin >> n >> Q;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    while (Q--) {
        int x, y;
        cin >> x >> y;
        int v = a[x];
        int ans = 0;
        vector<int> s(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            s[i] = s[i - 1] + (a[i] < v ? 1 : 0);
        }
        int max_L = min(x, y);
        for (int L = 1; L <= max_L; L++) {
            int k = y - L + 1;
            if (k < 1) continue;
            int required = k - 1;
            int min_R = max(x, y);
            int low = min_R;
            int high = n;
 
            int left = low, right = high;
            int start_R = -1;
            while (left <= right) {
                int mid = (left + right) / 2;
                int cnt = s[mid] - s[L - 1];
                if (cnt >= required) {
                    start_R = mid;
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            }
            if (start_R == -1) continue;
            if (s[start_R] - s[L - 1] != required) continue;
 
            left = start_R;
            right = n;
            int end_R = start_R;
            while (left <= right) {
                int mid = (left + right) / 2;
                if (s[mid] - s[L - 1] == required) {
                    end_R = mid;
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
            ans += end_R - start_R + 1;
        }
 
        cout << ans << endl;
    }
    return 0;
}
```
整体复杂度为 $O(Q)$。

求过

---

## 作者：wangyanjing (赞：1)

PS：这是一个很简单的做法。
# Solution

对于一个区间 $[l,r]$，当 $[l,r]$ 中有 $y-l$ 个数小于 $a_x$ 时，它才是合法的。

记：$S_i$ 为 $[1,i]$ 中比 $a_x$ 小的元素个数（前缀和）。  
那么一个区间 $[l,r]$ 中小于 $a_x$ 的数的个数为：$S_r - S_{l-1}$。

然后我们要求：
$$\sum_{l = 1} ^ n\sum_{r = l} ^ n [S_r - S_{l-1} = y-l]$$
$$=\sum_{l = 1} ^ n\sum_{r = l} ^ n [S_r = S_{l-1} + y-l]$$
记：$S_0 = 0$。
$$\because \forall i,S_i \ge S_{i-1}$$
$$\because y-l \ge 0$$
$$\therefore \{i | S_i = S_{l-1} + y-l\} \subseteq \{i|i\ge l\}$$

用桶记录一下每个 $S_i$ 的出现次数即可。
# Code
```cpp
#include<cstdio>
#define ll long long
const int N = 1e4+5;
int a[N],n,q;
int S[N],Cnt[N];
inline ll Ask(int x,int y){
	for(int i = 1;i<=n;++i) S[i] = S[i-1] + (a[i]<a[x]); 
	for(int i = 1;i<=n;++i) ++Cnt[S[i]];
	ll ans = 0;
	for(int l = 1;l<=x;++l) ans += Cnt[y-l+S[l-1]];
	for(int i = 1;i<=n;++i) Cnt[S[i]] = 0;
	return ans;
}
int main(){ 
    std::scanf("%d %d",&n,&q);
	for(int i = 1;i<=n;++i) std::scanf("%d",a+i);
    int x,y;
	while(q--){
        std::scanf("%d %d",&x,&y);
		printf("%lld\n",Ask(x,y));
	}
	return 0;
}
```
时间复杂度：$O(nq)$。

---

## 作者：ylch (赞：1)

考虑对区间 $[L,R]$ 重排之后，若 $a_x$ 在区间的第 $k$ 个位置，也就意味着在 $[L,R]$ 中有 $k-1$ 个小于 $a_x$ 的数字。

设 $a_x$ 当前在区间内的排名为 $k$（即 $[L,R]$ 中有 $k-1$ 个元素比 $a_x$ 小），那么重排后 $a_x$ 的下标应该是 $L+k-1$。要让这个值等于 $y$，可以推导出 $k=y-L+1$，也就是说要有 $y-L$ 个数小于 $a_x$。

所以我们只要预处理出在任意 $[L,R]$ 区间中有多少小于 $a_i$ 的数字，就能做到快速处理询问。这显然可以用前缀和实现。

假设有前缀和数组 $pre_i = \sum_{p=1}^i [a_p < a_x]$，那么在 $[L,R]$ 中比 $a_x$ 小的元素个数就可以表示为 $pre_R-pre_{L-1}$，我们需要让 $pre_R-pre_{L-1}=y-L$，则 $pre_R = y-L+pre_{L-1}$。

所以只要用桶数组统计 $pre_R\ (R \ge y)$ 的值的出现次数就能快速求出答案了。

时间复杂度 $O(nQ)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e4 + 7;

int a[maxn], pre[maxn];

void solve(){
	int n, Q; cin >> n >> Q;
	for(int i = 1; i <= n; i ++){
		cin >> a[i];
	}
	while(Q --){
		int x, y; cin >> x >> y;
		pre[0] = 0;
		for(int i = 1; i <= n; i ++){
			pre[i] = pre[i - 1] + (a[i] < a[x]); // 预处理前缀和
		}
		vector<int> cnt(20005);
		for(int i = y; i <= n; i ++){ // 注意右端点>=y
			cnt[pre[i]] ++;
		}
		ll ans = 0;
		for(int L = 1; L <= x; L ++){
			int T = y - L + pre[L - 1];
			if(T >= 0 && T <= 20000){ // 统计答案，防一手越界
				ans += cnt[T];
			}
		}
		cout << ans << '\n';
	}
}

int main(){
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	solve();
	return 0;
}
```

---

## 作者：QAQ_YTH (赞：0)

看到数据范围我们可以发现，我们的算法时间复杂度应该要在 $O(n)$ 以内。

---

然鹅这并没有什么用，题目想让我们通过改变部分排序来改变元素顺序。我们可以发现在下标从 $l$ 到 $r$ 倘若有 $cnt$ 个数小于 $a_x$ ,那么 $x$ 将会变成 $l+cnt-1$。

---

由上，我们有了一个大致的思路：从 $x$ 往后找 $y-x$ 个小于 $a_x$ 的元素，这个区间便是所有满足条件的中最小的了，然后这个区间如果左边一个元素比 $a_x$ 小就可以向左拓展，右边一个元素比 $a_x$ 大就可以向右拓展，根据乘法原理我们可以得到方案数为向左可拓展的数目加一的和乘上向右可拓展的数目加一的和。

---

但是在测试样例二时，我们可以发现其实在上述拓展完毕后判断，如果左右都还有数则可以继续拓展。我们可以使用函数来实现拓展。

---

代码如下，美美拿下。



```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+11;
int n,q,a[N],x,y,ans;
void find(int l,int r){
	int lans=0,rans=0;
	for(int i=r;i<=n;i++){
		if(a[i]>a[x]){
			rans++;
		}else break;
	}
	for(int i=l;i>=1;i--){
		if(a[i]<a[x]){
			lans++;
		}else break;
	}
	//cout<<lans<<' '<<rans<<'\n';
	ans+=(lans+1)*(rans+1);
	if(l-lans>=1&&r+rans<=n){
		find(l-lans-1,r+rans+1);
	}
	return;
}
int main(){
	//freopen("sort5.in","r",stdin);
	ios::sync_with_stdio(false);
	cin.tie(),cout.tie();
	cin>>n>>q;
	for(int i=1;i<=n;i++)cin>>a[i];
	while(q--){
		cin>>x>>y;
		ans=0;
		int len=y-x,maxn=0,flag=0,cnt=0;
		for(maxn=x+1;maxn<=n;maxn++){
			if(a[maxn]<a[x])cnt++;
			if(cnt==len)break;
		}
		if(cnt!=len){
			cout<<"0\n";
			continue;
		}
		find(x-1,maxn+1);
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：NingMeng_yang (赞：0)

# [P13730 【MGVOI R1-B】完美重排（sort）](https://www.luogu.com.cn/problem/P13730)

### Solution

题目问你有多少种进行恰好一次完美重排的方案，原 $a_x$ 要从 $x$ 移到 $y$，就必须满足 $x$ 和 $y$ 在 $L$ 和 $R$ 之间，因为 $x < y$，所以可以简化为 $L \le x$ 和 $y \ge R$。

设 $s_i$ 是为前 $i$ 个元素比 $sum$ 小的个数，则在 $L$ 和 $R$ 中比 $sum$ 小的数有 $s_R - s_{L - 1}$ 个。重排后位于 $s_R - s_{L - 1} + 1$ 为，对应全局下标 $L + s_R - s_{L - 1}$。要求坐标等于 $y$，则 $s_R = y - L + s_{L - 1}$。

### Code
```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e4+7;

int n,q;
int a[N];

signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	
	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>a[i];
	while(q--)
	{
		int x,y;
		cin>>x>>y;
		int sum=a[x];
		vector<int> s(N,0);
		for(int i=1;i<=n;i++)
		{
			if(a[i]<sum) s[i]=s[i-1]+1;
			else s[i]=s[i-1];
		}
		vector<vector<int> > cnt(N);
		for(int i=1;i<=n;i++) cnt[s[i]].push_back(i);
		int ans=0;
		for(int i=1;i<=x;i++)
		{
			int sum=(y-i)+s[i-1];
			if(sum<0||sum>n) continue;// sum超出合法范围
            // 在cnt[sum]中找≥y的个数,二分查找
			ans+=cnt[sum].end()-lower_bound(cnt[sum].begin(),cnt[sum].end(),y);
		}
        
		cout<<ans<<endl;
	}
	
	return 0;
}
```

---

## 作者：Zskioaert1106 (赞：0)

题目传送门：[P13730 【MGVOI R1-B】完美重排](https://www.luogu.com.cn/problem/P13730)

### 题目分析

观察到数据范围较小，考虑对于每次询问求一次解。

设 $s_i$ 为 $a_1 \sim a_i$ 中小于等于 $a_x$ 的元素个数，可得 $L-1+s_R-s_{L-1}=y$，那么 $L\leqslant x \leqslant R$ 是一组合法解。

$s$ 可以前缀和求出，但枚举每对 $L,R$ 是 $O(n^2)$ 的。发现当 $R$ 增加时，由于 $s_R$ 只增不减，所以贡献非负。$L$ 增加时 $s_{L-1}$ 的增加量也在 $[0,1]$ 之间，故 $L-s_{L-1}$ 的贡献亦非负。

既然满足单调性，就考虑双指针：初始置 $L,R$ 于 $x$，左移枚举 $L$ 时右移 $R$。但是移动 $L,R$ 时有可能贡献不变，因此要开一个 $cnt$ 记录之前有几对能继续贡献现在。

细节见代码。

### 代码实现

```cpp
#include<iostream>
using namespace std;
const int N=10004;
int n,q,a[N],s[N];
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0); 
	cin>>n>>q;
	for(int i=1;i<=n;i++)cin>>a[i];
	while(q--){
		int x,y;
		cin>>x>>y;
		for(int i=1;i<=n;i++){
			s[i]=s[i-1];
			if(a[i]<=a[x])s[i]++;
		}
		int ans=0,l=x-1,r=x,cnt=0;
		while(l>=0){
			while(r<=n&&l+s[r]-s[l]<y)++r;
			if(!cnt&&r>n)break;
			while(l+s[r]-s[l]==y){
				++cnt;
				++r;
			}
			ans+=cnt;
			if(s[l]==s[l-1])cnt=0;
			--l;
		}
		cout<<ans<<'\n';
	}
    return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/231356190)。

---

## 作者：K_yuxiang_rose (赞：0)

注意数据范围，在 $O(nQ)$ 内可以通过。

首先，要将位置 $x$ 的元素换到 $y$，肯定要包含 $[x,y]$。设选中区间的左端点是 $l$，$num=y-l+1$，题目的意思可以转换为在选中的区间内，$a_x$ 是第 $num$ 小的的区间方案数。考虑双指针，设 $sum$ 是当前区间内比 $a_x$ 小的元素个数，当左指针左移时，如果 $a_l<a_x$，则 $num-sum$ 不变，否则减一；当右指针右移时，如果 $a_r>a_x$，则 $num-sum$ 不变，否则加一。当 $num-sum=1$，也就是满足条件时，答案加一，但是如果 $[l-1,r]$ 和 $[l,r+1]$ 都满足条件如何处理？按照之前的思路，当 $a_l<a_x$ 或 $a_r>a_x$ 时，$num-sum$ 不变，那我们可以按照这个条件不断扩展，直到两个指针都不能移动为止，这时通过乘法原理即可求出答案。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[10005];
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int n,q;
	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>a[i];
	while(q--)
	{
		int x,y,sum=0,ans=0;
		cin>>x>>y;
		for(int i=x;i<=y;i++)
			if(a[i]<a[x]) sum++; 
		int l=x,r=y;
		while(1<=l&&r<=n)
		{
			if(sum<y-l)
			{
				if(r==n) break;
				r++,sum+=(a[r]<a[x]);
			}
			else if(sum>y-l)
			{
				if(l==1) break;
				l--,sum+=(a[l]<a[x]);
			}
			else
			{
				int ll=l-1,rr=r+1;
				while(a[ll]<a[x]&&ll>=1) ll--,sum++;
				while(a[rr]>a[x]&&rr<=n) rr++;
				if(rr<=n) sum++;
				ans+=(l-ll)*(rr-r);
				l=ll,r=rr;
			}
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：CSP_S_2023_T2 (赞：0)

### 题意简化

给定数组 $a$，选择一个子区间，对其进行升序排序，求满足下列条件的子区间个数。

- 排序后数组 $a$ 中原先下标为 $x_i$ 的元素，在重排后的下标为 $y_i$。
 

### 思路

以下 $x$ 为题中 $x_i$，$y$ 同理。

显然合法区间必定包含 $[x,y]$。

若选定区间 $[x,y]$，记排序后原先下标为 $x$ 的元素，重排后的下标为 $pos$。

$pos$ 跟我们想要达到的目标 $y$ 有 $y-pos$ 的差距，需要扩大区间以填补差距。

考虑区间 $[i,j]$：

记 $[i,x-1]$ 中 $>a_x$ 的数字个数为 $s$，$[y+1,n]$ 中 $< a_x$ 的数字个数为 $t$，~~稍微动一下脑子就可以得到~~前 $s$ 个数会让 $pos$ 减去 $s$，后 $t$ 个数会让 $pos$ 加上 $t$，$pos$ 就会变为 $pos - s + t$。

也就是要让 $t - s = y - pos$。

很明显，从 $x-1$ 到 $1$ 跑一遍，从 $y+1$ 到 $n$ 跑一遍，即可得到所有的 $s$ 和 $t$。

开两个桶，第一个桶记录 $s$ 的不同取值的个数，第二个桶记录 $t$ 的不同取值的个数，跑一遍算出答案即可。

若第一个桶为 $b$，第二个桶为 $c$，答案大概长这样：$\sum (b_i \times c_{i+y-pos})$。

剩下的都在代码里了。

时间复杂度 $\Theta(Qn\log n)$，足以通过本题（$\log n$ 是排序的时间复杂度）。

### 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 1e4 + 10;
int n, q, a[N], b[N], l[N], r[N], x, y;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i];
    while (q--) {
    	memset(l, 0, sizeof(l));
    	memset(r, 0, sizeof(r));
    	cin >> x >> y;
    	for (int i = x; i <= y; i++) b[i] = a[i];
    	sort(b + x, b + y + 1);
    	int pos;
    	for (int i = x; i <= y; i++) {
    		if (b[i] == a[x]) {
    			pos = i;
    			break;
			}
		}
		int cost = y - pos, gx = 0;
        l[0] = r[0] = 1;  //因为循环是从 x-1 开始，若左端点为 x, s也等于0，要加上这种情况，y同理
		for (int i = y + 1; i <= n; i++) {
			if (a[i] < a[x]) gx++;
			r[gx]++;
		}
		gx = 0;
		for (int i = x - 1; i; i--) {
			if (a[i] > a[x]) gx++;
			l[gx]++;
		}
		int ans = 0;
		for (int i = 0; i + cost <= n; i++) ans += l[i] * r[i + cost];  //计算过程，这里为了保险范围开大一点
		cout << ans << '\n';
	}
    
    return 0;
}
```

其实似乎用双指针更简单一点读者自行探索……

完结撒花。

---

## 作者：Jason_Ming (赞：0)

### 思路

通过观察，我们可以发现，对于每个询问的符合条件的重排操作，$1 \le L \le x_i < y_i \le R \le n$。

通过观察，我们又可以发现，如果一次左端点为 $L$ 的重排操作是符合条件的，那么在 $a_L,...,a_R$ 中有 $x_i - L$ 个比 $a_{x_i}$ 小的数。

对于每次询问，我们可以构造一个数组 $b$，使得 $b_j = \sum_{k=1}^{j} [a_k < a_{x_i}](1 \le j \le n)$。那么，对于每个 $L$，我们只需要知道有多少个右端点 $R$，使得 $b_R - b_{L-1} = y_i - L$。

考虑构造一个数组 $f$，使得 $f_j = \sum_{k=y_i}^{n} [b_k = j](1 \le j < n)$。于是，对于每个 $L$，有 $f_{y_i-L+b_{L-1}}$ 个符合条件的右端点 $R$。

这里画个图帮助大家理解一下最后一句话。我画技拙劣，并且不知道画图里怎么使用 $\LaTeX$，还请见谅。

![](https://cdn.luogu.com.cn/upload/image_hosting/ri09rcfr.png)

最终答案即为 $\sum_{L=1}^{x_i} f_{y_i-L+b_{L-1}}$。

### 代码

```cpp line-numbers
#include<bits/stdc++.h>
using namespace std;

int n,q;
int a[10005],b[10005],f[10005];

int main()
{
    cin>>n>>q;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
    }
    while(q--)
    {
        int x,y,ans=0;
        memset(f,0,sizeof(f));
        cin>>x>>y;
        for(int k=1;k<=n;k++)
        {
            if(a[k]<a[x])
            {
                b[k]=b[k-1]+1;
            }
            else
            {
                b[k]=b[k-1];
            }
            if(k>=y)
            {
                f[b[k]]++;
            }
        }
        for(int l=1;l<=x;l++)
        {
            ans+=f[y-l+b[l-1]];
        }
        cout<<ans<<'\n';
    }
}
```

---

## 作者：medal_dreams (赞：0)

## 题意
求在一个长度为 $n$ 排列 $a$ 中将下标 $x$ 通过排序转化为下标 $y$ 的方案数。
## 思路
首先，看 $Q,n$ 的值，发现 $Q \le 2 \times 10 ^ 3,n \le 1 \times 10 ^ 4$，这启发我们可以使用 $O(Qn)$ 的代码实现。那么也就是在询问中进行求方案，因为询问的是区间，这启发我们进行区间扩展操作。

按照区间扩展的思路去考虑，可以发现影响方案数与这个数原本在这个区间的位置（这里称为排名，为了方便统计，我们记排名为其在整个排列中所在的下标）和其扩展方向每个数的大小有关。

设排名为 $paim$，要转换到的下标为 $y$，我们设我们要转换的下标为 $x$，存储满足 $a_j > a_x$ 且 $j \le x - 1$ 的序列为 $b$。  
对于每次查询分两种情况：
1. $paim = y$  
   那么就让区间向左向右扩展：
   - 如果向右扩展，那么对于任意一个下标 $j \ge y + 1$ 时，如果遇到一个 $a_j < a_x$ 时，只向右扩展无论如何我们都没有办法使它恢复到原来位置，而如果是 $a_j > a_x$ ，那么在排序中只会让 $a_j$ 放在 $a_x$ 后，那么就对 $paim$ 没有影响，可以继续向右扩展。
   - 如果向左扩展，就是向左去判断，对于任意一个下标 $j \le x - 1$，如果 $a_j < a_x$，那么这个扩展到的区间就是可以的，但如果向左扩展遇到 $a_j > a_x$，只向左扩展无论如何我们都无法再次将 $x$ 变换到 $y$。
   - 但是，我们只单独考虑了向右或者向左扩展的情况，如果是同时向右或者向左扩展呢？我们发现如果同时向右向左扩展，设向右扩展遇到了 $cntr$ 个 $a_j < a_x$ 的情况，向左扩展遇到了 $cntl$ 个 $a_j > a_x$ 的情况，那么当 $cntl = cntr$ 的时候，似乎 $x$ 仍不会改变。所以需要单独判断 $cntl$ 和 $cntr$ 这种情况。
2. $paim \ne y$  
   同样也是向左向右扩展，但我们发现因为 $x < y$，所以就应该一直让 $a_x$ 的排名向后去排，所以向右扩展我们要求对于下标 $j \ge y + 1$ 能满足 $a_j < a_x$，但是如果其向左扩展为 $a_j > a_x$ 且 $j \le x - 1$，我们能发现，其对排名也会有影响，会使 $paim - 1$，也就是说，如果向右扩展，只有小于会影响排名，如果向左扩展，只有大于会影响排名。    
   那么分为三种情况为，设 $a_j < a_x$ 且 $j \ge y + 1$ 的个数为 $cnttr$，则为 $y - paim = cnttr$ 与 $y - paim < cnttr$ 和 $y - paim > cnttr$。
   - 对于 $y - paim > cnttr$ 的情况，说明还不够，继续向右扩展。
   - 对于 $y - paim = cnttr$ 的情况，直接增加向右扩展的的方案数。
   - 对于 $y - paim < cnttr$ 的情况，我们需要找原区间左边（即向左扩展）的 $a_j > a_x$ 且 $j \le x - 1$ 的个数。但是我们知道向左扩展中 $a_j < a_x$ 且 $j \le x - 1$ 的数对于我们的排名是没有影响的，所以无论向左多少个都没有影响。那么我们就需要变相记录左扩展中满足 $a_j > a_x$ 且 $j \le x - 1$ 的数的下标，以此来通过这个快速计算有多少种方案。因为向左扩展中 $a_j < a_x$ 且 $j \le x - 1$ 的数对于排名是没有影响的，但他们的个数就是可能区间的个数，所以其应该访问 $b$ 的下标为 $cnttr - (y - paim)$，这里出现的可能的区间数就要加上 $b_{cnttr - (y - paim) + 1} - b_{cnttr - (y - paim)}$（因为我的是从 $1 \sim x - 1$ 记录的 $b$，所以这里是 $b_{cnttr - (y - paim) + 1} - b_{cnttr - (y - paim)}$）。
       
同样是求区间数，我们可以发现如果将里各种情况合并，那么就变成向右扩展求小于和大于的个数，向左扩展求大于和大于的下标，与两个区间共同扩展的，并没有影响答案，于是我们就可以将两种情况合为一体。
## 代码思路
  对于每次询问，先求出排名，记录左边每个大于 $a_x$ 的数的下标，再次记录向左扩展小于 $a_x$ 的数。对于向右扩展，如果出现小于 $a_x$ 的数，那就记录个数，再套上上面第二种情况的二三条即可。
### std
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e4 + 66;
long long a[N],n,q,x,y,lef[N];	
int main()
{
//	freopen("sort5.in","r",stdin);
//	freopen("out.ans","w",stdout);
	ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
	cin >> n >> q;
	for(int i = 1;i <= n;i ++) cin >> a[i];
	for(int i = 1;i <= q;i ++)
	{
		long long paim,cntr = 0,cntl = 0,cntrr = 0;
		//paim 是排名,cntr 是右侧可行的,cntl是左侧可行的,cntrr是右侧不可行的
		cin >> x >> y;
		paim = x;//因为我的排名以下标为标准，所以直接记录x下标
		for(int i = x + 1;i <= y;i ++) if(a[x] > a[i]) paim ++; //算排名就是算这个区间有多少比他小的
		long long tot = 0;
		cntr = paim == y ? 1 : 0;//如果本身就可以那么cntr本身就是1
		for(int i = 1;i <= x;i ++) if(a[x] < a[i]) lef[++ tot] = i;//算左侧比它大的
		for(int i = x;i >= 1;i --) //本身区间也算一个，所以从x开始
		{
			if(a[x] >= a[i]) cntl ++;		//算左侧比他小的（向左扩展）
			else break;//因为如果有比他大的就向左无论如何都不成立了，所以终止
		}
		long long cnt = 0;//记录额外的，也就是左右区间合一块可行的
		for(int i = y + 1;i <= n;i ++)//找右区间（向右扩展）
		{
			if(a[x] > a[i]) cntrr ++;	//如果遇到不行的，就放入不行的计数中
			if(cntrr == (y - paim)) cntr ++;//如果本身就可行，就加到右侧可行的
			if(cntrr - (y - paim) <= tot && cntrr > (y - paim)) cnt += lef[tot - (cntrr - (y - paim)) + 1] - lef[tot - (cntrr - (y - paim))];
			//计算如果在左侧大的数的个数中并且本身也比我们缺的大，就计算，因为我是从下标1开始，所以这里是用tot- 计算俩个大的中间的小的数，这几个小的数都可以算在答案里，因为都包括了那个大数并且左侧小数对答案没影响
			else if(cntrr - (y - paim) > tot) break;//如果比左边大的数都多，那就不用算了
		}
		cout << (cntl * cntr + cnt) << '\n';//输出，左区间单独的和右区间单独的不影响，所以是 * 而左右区间混合的是 +
	}
	return 0;
}
```

---

## 作者：FruitWasTaken (赞：0)

## 出题人题解

### 主要知识点

* 【2】乘法原理
* 【3】递推法
* 【3】前缀和
* 【3】冒泡排序

---

### Subtask 1：测试点 $\bm{1\sim 6}$

直接枚举 $L$ 和 $R$ 然后 ```std::sort()```
模拟即可，时间复杂度 $O(Q\cdot n^3 \log n)$。

---

### Subtask 2：测试点 $\bm{7\sim 12}$

考虑优化 Subtask 1 的做法至 $O(Q\cdot n^2)$。

我们发现，假设刚计算完对区间 $[L,R]$ 进行完美重排后，原先下标为 $x_i$ 的数的新位置为 $z_i$（显然应满足 $L\le x_i \le R$，否则 $x_i$ 不在重排区间内），那么接下来枚举区间 $[L,R+1]$ 时，还用重新模拟一遍排序吗？

实际上没必要。由于我们只关心原先下标为 $x_i$ 的数（记为 $m$）在重排后的位置，所以可以由 $[L,R]$ 这个区间的情况直接递推到 $[L,R+1]$：

* 若 $a_{R+1}<m$，则 $z_i$ 的值增加 $1$；
  
* 若 $a_{R+1}>m$，则 $z_i$ 的值不变。

模拟一下发现是很好理解的，因为当 $a_{R+1}<m$ 时，重排区间新加入的 $a_{R+1}$ 这个元素由于比 $m$ 更小，在排序后将 $m$ “顶”到了后面一个位置（类比冒泡排序）；而 $a_{R+1}>m$ 时，对 $m$ 的位置则没有贡献。

同理，也可以由区间 $[L,R]$ 的情况（$L\le x_i \le R$）递推到区间 $[L-1,R]$：

* 若 $a_{L-1}>m$，则 $z_i$ 的值减小 $1$（将 $a_{L-1}$ 纳入重排区间后，$m$ 被向前“推”了一个位置）；
  
* 若 $a_{L-1}<m$，则 $z_i$ 的值不变。

综上，我们只需用双重循环枚举 $L,R$，并按上述规则实时维护 $z_i$，就能 $O(1)$ 地得出每个区间的答案，时间复杂度 $O(Q\cdot n^2)$。

---

### Subtask3： 测试点 $\bm{13\sim 20}$

考虑将时间复杂度优化至 $O(Q\cdot n)$。

承 Subtask 2，我们只关心 $m$ 的位置，于是考虑将数组 $a$ 重新扫一遍，得到一个新数组 $b$：

* 情况 1：若 $j<x_i$ 且 $a_j>m$，则 $b_j=-1$；
  
* 情况 2：若 $j>x_i$ 且 $a_j<m$，则 $b_j=+1$；

* 其它情况，$b_j=0$。

数组 $b$ 的意义是什么呢？类比上一个 Subtask 的区间递推，我们发现和之前一样，情况 1 可以等效成将 $a_j$ 纳入重排区间后，将 $m$ 向前“推”了一位；而情况 2 可以等效成将 $a_j$ 纳入重排区间后，将 $m$ 向后“顶”了一位。

那么可以观察到：对区间 $[L,R]$ 进行完美重排之后（$L\le x_i\le R$），$m$ 对应的下标就是 $x_i+\sum\limits_{j=L}^R b_j$，这就很清晰了!

于是就等价于问你在值域为 $\{ -1,0,1 \}$ 的数组 $b$ 中，有多少对 $(L,R)$ 满足 $b_L+...+b_R=y_i-x_i$，并且 $L\le x_i\le R$。

一种做法是你可以算出 $b$ 的前缀和 $b'$，化为 $b'_R-b'_{L-1}=y_i-x_i$，然后这就变成了一个 [A - B 数对模板题](https://www.luogu.com.cn/problem/P1102)。当然，我们这里还是采取另一种做法，充分利用一下值域为 $\{ -1,0,1 \}$ 的特性，具体地：

* 第一步，记录 $x_i$ 之前所有 $-1$ 的位置和 $x_i$ 之后所有 $+1$ 的位置。显然，每两个相邻的 $-1$ （或每两个相邻的 $+1$）之间会隔若干个 $0$。
  
* 第二步，根据上述分析，在我们选出的区间中，$+1$ 的个数要恰好比 $-1$ 的个数多 $y_i-x_i$。那么直接枚举 $-1$ 取多少个，这样 $+1$ 取多少个也就确定了。

* 第三步，确定了 $+1$ 和 $-1$ 取多少个之后，只需再用乘法原理统计一下它们后面 / 前面的 $0$ 要怎么选。之前已经记录过所有 $-1$ 和 $+1$ 的位置，注意细节实现一下即可。



时间复杂度 $O(Q\cdot n)$。

注：考虑到这只是 T2，所以并没有卡常数优秀的 $O(Q\cdot n \log n)$ 做法。

---

### 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int n, Q, a[15005];
int x, y;
int L[15005], R[15005];

void solve()
{
	cin >> n >> Q;
	
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
	}

	while (Q--)
	{
		cin >> x >> y;
		
		int index = x, cntL = 0, cntR = 0;
		
		while (index <= n)
		{
			if (a[index] < a[x])
				R[++cntR] = index;
			
			++index;
		}
		
		index = x;
		while (index >= 1)
		{
			if (a[index] > a[x])
				L[++cntL] = index;
			
			--index;
		}
		
		L[0] = R[0] = x;
		L[cntL + 1] = 0, R[cntR + 1] = n + 1;
		
		int ans = 0;
		for (int i = 0; true; i++)
		{
			if (y - x + i > cntR || i > cntL)
				break;
			
			ans += (R[y - x + i + 1] - R[y - x + i]) * (L[i] - L[i + 1]);
		}
		
		cout << ans << '\n';
	}
	
	return;
}
 
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0); 
	
	int _ = 1;
	while (_--)
	{
		solve();
	}
	
	return 0;
}
```

---

