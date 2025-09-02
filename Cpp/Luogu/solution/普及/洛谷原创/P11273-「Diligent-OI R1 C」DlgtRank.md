# 「Diligent-OI R1 C」DlgtRank

## 题目描述

给你一个长为 $n$ 的序列 $a_1\sim a_n$。这里定义 $a_i$ 的**排名**为 $a$ 中**严格大于** $a_i$ 的数的个数 $+1$。

现有一些操作来更改 $a$ 中的元素。所有操作之前会事先给你一个常量 $k$。每次操作前，定义 $a_i$ 是**可移动**的，当且仅当**仅将 $a_i$ 的值加上 $k$，其他值不变**后，$a_i$ 的排名不变。否则 $a_i$ 在这次操作是不可移动的。然后这次操作为：将序列中所有可移动的数加上 $k$。

可以证明经过若干次操作后，$a$ 中所有值都会变成可移动的，并且第一次达到这种状态时，后面的操作也会是这种状态。也就是说，无论做多少次操作，$a$ 中每个值为**不可移动**状态的次数是有限的。

现在询问，做足够多次这个操作后，$a$ 中每个值为**不可移动**状态的次数是多少。

## 说明/提示

#### 样例 #1 解释

初始的 $a_1=1,a_2=3,a_3=4$。

操作一次后 $a_1=2,a_2=3,a_3=5$。$a_2$ 不可移动，是因为如果仅将 $a_2$ 加上 $1$，它的排名会由 $2$ 变成 $1$。

操作两次后 $a_1=2,a_2=4,a_3=6$。$a_1$ 不可移动，是因为如果仅将 $a_1$ 加上 $1$，它的排名会由 $3$ 变成 $2$。

操作三次后 $a_1=3,a_2=5,a_3=7$。这次操作所有值都是可移动的了。可以证明再操作任意多次也不会再出现不可移动的状态了。

因此过程中 $a_1$ 有一次不可移动，$a_2$ 有一次不可移动，$a_3$ 没有不可移动的时候。

#### 数据范围与约定

对于 $100\%$ 数据，$1\le n\le2\times10^5$，$1\le k,a_i\le10^9$。

| Subtask 编号 | $n\le$ | 特殊性质 | 分值 |
| :----------: | :----------: | :----------: | :----------: |
| $0$ | $1$ | ABC | $4$ |
| $1$ | $100$ | C | $14$ |
| $2$ | $100$ | 无 | $13$ |
| $3$ | $3000$ | C | $18$ |
| $4$ | $3000$ | 无 | $16$ |
| $5$ | $2\times10^5$ | A | $6$ |
| $6$ | $2\times10^5$ | BC | $8$ |
| $7$ | $2\times10^5$ | C | $7$ |
| $8$ | $2\times10^5$ | 无 | $14$ |

特殊性质 A：所有的 $a_i$ 都相等。

特殊性质 B：对于任意的 $i<n$ 满足 $a_{i+1}=a_i+k$。

特殊性质 C：对于任意的 $i\neq j$ 满足 $a_i\neq a_j$。

## 样例 #1

### 输入

```
3 1
1 3 4```

### 输出

```
1 1 0```

## 样例 #2

### 输入

```
6 2
1 2 5 6 7 8```

### 输出

```
4 3 3 2 1 0```

## 样例 #3

### 输入

```
8 10
1 14 5 14 19 19 8 10```

### 输出

```
5 1 4 1 0 0 3 2```

# 题解

## 作者：fish_love_cat (赞：8)

嗯，还算是简单题吧。

---

首先拿到题目后很容易想到排序。

依题意得，最大值答案一定是 $0$，因为无论怎么加都一定是第一。

容易发现相同数字的答案一定相同，所以直接忽视已经处理过的数字。（特殊性质 A）

我们可以把原问题转化到数轴上。~~然后你就会发现这题怎么这么像堵车（~~

思考发现，当一个数在初始局面下因为前面的一个数堵住时，那么答案将是前面一个数的答案加一，这是容易证明的。（特殊性质 B）

因为每当前面停下，当前数必然也会有一次停下，而且还要额外算上初始局面的一次不可移动。~~这就和堵车时前面的车动一下你动一下，前面停你也停一样谔谔~~。

形式化的讲，$ans_i=ans_{i+1}+1$。注意，这里的 $i$ 越大表示越前面，即 $a_{i+1}>a_i$。

好了，那么恭喜你拿到了 [$18\text{pts}$](https://www.luogu.com.cn/record/187972728) 的高分。

---

现在让我们来研究初始数据不直接堵住的情况吧。

举个栗子：

![](https://cdn.luogu.com.cn/upload/image_hosting/ngu5td2g.png)

（注：$k=1$）

根据上文结论，二号车会被堵一次。

如果一号车被二号车堵的话，那么一号车将会被堵两次。

幸运的是，一号车只有开到 $a_2-1=9$ 的时候，才会被堵。也就是说，在一号车到 $9$ 前，是不会被堵的。

通过计算知道，一号车到 $9$ 要开 $\frac{a_2-a_1-k-1}{k}+1=8$ 次操作。

然后发现等开到的时候都不堵了。所以 $ans_1=0$。

---

仔细研究栗子以及打个暴力研究多组 hack 后可以发现，一辆车到达堵车的点所用的操作次数，刚好可以抵掉在初始局面就堵的答案。

证明：

显然如果两车同时在运动，它们间的距离将不会改变。

前车堵住了，后车花费一次操作缩短距离，与此同时堵车的次数减一。

然后你会发现，如果距离缩短 $k$，必然会少堵一次车。也就是说答案会减少开上去的操作次数。

那么直接套式子算操作次数和原本的答案即可。

然后做完了。

---

主体代码：

```cpp
for(int i=1;i<=n;i++)
    if(a[i].x+k>=a[i-1].x&&a[i].x!=a[i-1].x)
	a[i].ans=a[i-1].ans+1;
    else a[i].ans=max(1ll,a[i-1].ans-max(0ll,a[i-1].x-a[i].x-k-1)/k);
//码的很繁琐，最好直接用上面的结论，写我这个特别容易写挂谔谔（
```

**注意答案不能为负。**

---

## 作者：Night_sea_64 (赞：8)

出题人题解。

题目中的那个操作很复杂。但是其实不需要模拟中间是怎么做的，可以直接计算最后的值。

首先很显然的一点就是，操作任意次数后，每个数的排名都不会变化。

然后容易发现，最大值永远都是可移动的。然后次大值最多只有第一次是不可移动的，后面都可移动。然后第三大值最多到第二次是不可移动的，后面都可移动。以此类推。所以最多 $n-1$ 次操作后，所有的值都会变为可移动的。

于是从大到小排序，记录所有值都稳定可移动之后变为多少，比如第 $n$ 次操作后的值。最大值肯定是加上 $n\times k$。然后依次对后面的值计算。

后面的值要想一直保持移动，那根据“可移动”的定义可以看出，移动的时候，跟前一个值的差距不能小于等于 $k$，否则是不可移动的。

所以稳定可移动的状态下，相邻两个值的差距也不能小于等于 $k$。同时可知，如果差距大于 $k$，就一定是可移动的，一定会移动。也就是说能保持这样的差距就不会有更大的差距。

综上所述，最大值后面的值有两种情况：

1. 加上了 $n\times k$ 也能和前面的值保持大于 $k$ 的差距，那就是加上 $n\times k$。
2. 否则这个值能加多少次 $k$ 就加多少次 $k$。

```cpp
#include<iostream>
#include<algorithm>
#define int long long
using namespace std;
int n,k,pos[200010],ans[200010];
struct node{int x,id;}a[200010];
bool cmp(const node &x,const node &y){
    return x.x>y.x;
}
signed main()
{
    cin>>n>>k;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i].x;
        a[i].id=i;
    }
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n;i++)
    {
        if(a[i].x!=a[i-1].x)
        {
            if(i==1)pos[i]=a[i].x+n*k;
            else pos[i]=a[i].x+min(n,(pos[i-1]-k-a[i].x-1)/k)*k;
        }
        else pos[i]=pos[i-1];
        ans[a[i].id]=n-(pos[i]-a[i].x)/k;
    }
    for(int i=1;i<=n;i++)cout<<ans[i]<<" ";
    cout<<endl;
    return 0;
}
```

---

## 作者：Milky_Cat (赞：7)

假设数组有序。

我们来设想一下，有 $n$ 个箱子，每个箱子宽度为 $k$。这些箱子分别有一个坐标，每次能移动的箱子就移动，问每个箱子有多少次没法移动。我们发现，这其实是把这道题目具象化了（虽然这样一来会导致箱子重叠在一起，这是不可想象的）。

仔细一想，就会发现每个数不可移动的个数和排名比这个数小 $1$ 的数不可移动次数有关，因为当前数可能被排名小 $1$ 的数挡住。

那么，我们只要找到每个数和排名小 $1$ 的数移动次数的关系就行了。

+ 如果距离小于等于 $k$，在排名小 $1$ 的数移动前，当前数不能移动，所以移动次数是排名小 $1$ 的数加上 $1$。

+ 如果距离在 $[k+1,2k]$ 范围内，在排名小 $1$ 的数移动前，当前数可以移动 $1$ 次，所以移动次数等于排名小 $1$ 的数。

+ 如果距离更大，以此类推，移动次数会小于排名小 $1$ 的数，距离在 $[nk+1,(n+1)k]$ 内，移动次数就是排名小 $1$ 的数减去 $n-1$。

于是我们排个序就做完了 qwq。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, k;
struct node{
	int vl, id, ans, tag;
}a[200005];
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> n >> k;
    for (int i = 1; i <= n; i++){
    	cin >> a[i].vl;
    	a[i].id = i;
	}
	sort(a + 1, a + 1 + n, [](node u, node v){return u.vl > v.vl;});
	a[1].ans = 0;
	for (int i = 2; i <= n; i++){
		if (a[i - 1].vl - a[i].vl <= k && a[i - 1].vl != a[i].vl)
			a[i].ans = a[i - 1].ans + 1;
		else if (a[i - 1].vl - a[i].vl <= 2 * k)
			a[i].ans = a[i - 1].ans;
		else
			a[i].ans = max(a[i - 1].ans - (a[i - 1].vl - a[i].vl - k - 1) / k, 0ll);
	}
	sort(a + 1, a + 1 + n, [](node u, node v){return u.id < v.id;});
	for (int i = 1; i <= n; i++)
		cout << a[i].ans << " "; 
	return 0;
}
```

---

## 作者：OpheebopZ (赞：5)

好题哇（虽然 OpheebopZ 不知道怎么形容

## 思路
先离散化一下，把重复的 $a _ i$ 排序并合并相同的得到序列 $b$，记其长度为 $m$，显然相同的 $a _ i$ 其不可移动的次数是一样的。

自己在纸上推了一下，可以发现一个规律：**在第 $i$ 次操作后 $b _ {m - i}$ 就绝对永远可以移动了**。所以说我们只要求出 $b _ i$ 在绝对永远可以移动之前可以移动多少次，最后用绝对永远可以移动的操作数减去它，就是 $b _ i$ 无法移动的次数了。

记 $b _ i$ 在绝对永远可以移动之前可以移动的次数为 $d _ i$，则有 $d _ i = \min(\sum ^ {m} _ {j = i} \lfloor \frac{ b _ {j + 1} - b _ {j} - 1 }{ k } \rfloor, m - i)$。其中 $\lfloor \frac{ b _ {j + 1} - b _ {j} - 1 }{ k } \rfloor$ 指 $b _ j$ 移到被 $b _ {j + 1}$ "卡到" 不能移动前能移动的次数，对它求后缀和并和 $m - i$ 取最小值就能求出每个 $d _ i$ 了。

最后用 $m - i$ 减去每个 $d _ i$ 就是每个 $b _ i$ 不可移动的次数了。

## 实现
讲的可能有点烦，直接上赛时代码。时间复杂度 $O(n \log n)$。


```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 5;
int n, m, k;
int a[MAXN], b[MAXN], c[MAXN], d[MAXN];

void discrete() { // 离散化
	sort(b + 1, b + n + 1);
	m = unique(b + 1, b + n + 1) - (b + 1);
}

int query(int x) { return lower_bound(b + 1, b + m + 1, x) - b; }

int main() {
	cin >> n >> k;
	for (int i = 1; i <= n; i++) { cin >> a[i]; b[i] = a[i]; }
	discrete(); b[m + 1] = 0x3f3f3f3f;
	for (int i = m - 1; i >= 1; i--) d[i] = min(d[i + 1] + (b[i + 1] - b[i] - 1) / k, m - i); // 求 d[i]
	for (int i = 1; i <= m; i++) c[i] = m - i - d[i]; // 答案
	for (int i = 1; i <= n; i++) cout << c[query(a[i])] << " ";
	return 0;
}
```

点个赞再走吧，OpheebopZ 感谢你。

---

## 作者：CaiZi (赞：3)

## DlgtRank 题解
**[题目链接](https://www.luogu.com.cn/problem/P11273)**
### 题目分析
首先肯定先排序然后去重，因为数字顺序对答案是没有影响的，以下记 $a'$ 为排序去重后的 $a$，$a'$ 的长度为 $n'$。

题目说的很绕，其实可移动就是指 $a'_i+k<a'_{i+1}$。显然的，$a'_{n'}$ 永远都可移动。然后，若 $a'_{n'-1}+k<a'_{n'}$，则 $a'_{n'-1}$ 永远可移动，否则 $a'_{n'-1}$ 不可以移动次数为 $1$，因为当 $a'_{n'}$ 加 $k$ 时，它们之间差肯定 $>k$。

理解完题目，我们会发现，若永远不移动 $a'_i$，则 $a'_{i-1}$ 的可移动次数为 $\lfloor\frac{a'_{i+1}-a'_i-1}{k}\rfloor$。以此类推，设 $b'_i$ 表示第 $a'_i$ 的不可移动次数，我们可以根据 $b'_i$ 推出 $b'_{i-1}$，转移为 $b'_i=\max\{b'_{i+1}-\lfloor\frac{a'_{i+1}-a'_i-1}{k}\rfloor+1,0\}$，因为我们可以先让 $a'_i$ 不断靠近 $a'_{i+1}$，所以可以直接相减。

最后再按照输入编号还原 $b$ 即可。
### 代码展示
时间复杂度 $O(n\log n)$。
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int x,y,z;
}a[200001];
int n,m;
inline bool cmp1(node _1,node _2){
	return _1.x<_2.x;
}
inline bool cmp2(node _1,node _2){
	return _1.y<_2.y;
}
signed main(){
    cin.tie(nullptr)->sync_with_stdio(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++){
    	cin>>a[i].x;
    	a[i].y=i;
	}
	sort(a+1,a+n+1,cmp1);
	for(int i=n-1;i>=1;i--){
		if(a[i].x==a[i+1].x){
			a[i].z=a[i+1].z;
		}
		else{
			a[i].z=max(a[i+1].z-(a[i+1].x-a[i].x-1)/m+1,0);
		}
	}
	sort(a+1,a+n+1,cmp2);
	for(int i=1;i<=n;i++){
		cout<<a[i].z<<' ';
	}
    return 0;
}
```
**[提交记录](https://www.luogu.com.cn/record/188009637)**

---

## 作者：dci66666 (赞：2)

这个题，纯找规律。

怎么说呢，当时脑子一热，写了，就过了。

我们在样例中可以发现，比如一段连续的序列就必须多推一个，但是，理智告诉我们，比如差值极大时就会减很多值。

所以，我们考虑倒退（先从大到小排序）：最大第一个值的答案一定是零，再往后推，如果在相邻的值差一次可以达到的话，那么就会答案 $+1$。但是如果一次达不到的话，考虑到前面的值可能也会被推迟。所以我们计算出会被推迟的轮数，在样例中找下规律。~~嗯，就可以发现将前面的答案减去推迟轮数就行~~了。

怎么理解呢？其实就是本来如果两个值没有相互关系（比如相等），但是由于前一个值的推迟，后一个值也会推迟。但是由于可能中间有一定的差值，使得在前面值推迟时后面值不会被推迟，所以减掉贡献就行了。

还没懂？上代码吧（代码也是非常简单啊）。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=4e5+50;
int n,k,ans[N],mp[N];
struct node{
	int num,id;
}a[N];
int read(){
	int x=0;
	char c=getchar();
	while(c>'9'||c<'0')c=getchar();
	while(c<='9'&&c>='0'){
		x=x*10+c-48;
		c=getchar();
	}
	return x;
}
bool cmp(node q,node w){
	if(q.num!=w.num)return q.num>w.num;
	return q.id<w.id;
}
int main(){
	n=read();k=read();
	for(int i=1;i<=n;i++){
		a[i].num=read();
		a[i].id=i;
	}
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<=n;i++){
		mp[a[i].id]=i;
	}
	ans[1]=0;
	for(int i=2;i<=n;i++){
		if(a[i].num==a[i-1].num){
			ans[i]=ans[i-1];
			continue;
		}
		int t=a[i-1].num-a[i].num;
		int num=(t-1)/k;
		ans[i]=max(ans[i-1]-num+1,0);
	}
	for(int i=1;i<=n;i++){
		printf("%d ",ans[mp[i]]);
	}
}
```

---

## 作者：ny_Dacong (赞：2)

# 思路

首先，为了方便计算排名，我们肯定要对 $a$ 排序。因此，下文的 $a$ 是已经按照**从大到小**排好序的序列。

因为 $k > 0$，所以 $a_1$ **在任何一轮一定是可以移动的**，移动完之后它的排名依然是 $1$。（注意这里的 $a$ 已经排序，$a_1$ 是最大的）。所以，记录答案 $ans_1 = 0$。

接下来考虑 $a_2$。有两种情况：

- $a_2+k < a_1$。在这种情况下，$a_2$ 移动之后不会比 $a_1$ 大，所以接下来**每一次**它都可以跟 $a_1$ **一起移动**。因此，$ans_2 = ans_1$。
- 否则在这一轮，$a_2$ 移动之后就会“篡位”，只有**等待直到满足条件**才可以跟 $a_1$ 一起移动。那么，应该等待多少轮呢？答案是 $1$，因为一轮之后 $a_1$ 变成 $a_1+k$，原式变为 $a_2+k < a_1+k$ 是否满足。两边同时消去 $k$，留下 $a_2 < a_1$。因为数组已经排好序，所以这个条件成立，因此，$ans_2 = ans_1+1$。

接下来考虑将这种想法扩展。对于 $a_i$ 和 $a_{i+1}$，假设 $a_i$ 已经**可以移动**：

- $a_{i+1}+k < a_i$。则 $a_{i+1}$ 可以跟着 $a_i$ 移动。$ans_{i+1} = ans_i$。
- 否则，由上面的推断可以得知，$a_{i+1}$ 还要等待一轮。$ans_{i+1} = ans_i+1$。

那么还有一种特殊情况，就是 $a_i$ 还不能移动的时候，$a_{i+1}$ 就已经可以移动了。那么应该将这种情况减去。

举个例子：

比如 $[11,10,1],k = 3$，此时 $10$ 还不能移动，但是 $1$ 已经可以移动了。

移动一轮之后，序列变为 $[14,10,4]$。此时三个数都可以移动。但是我们发现最终的答案数字 $1$ 反倒比数字 $10$ 小 $1$。原因就在于 $1$ 可以比 $10$ 多移动一轮。

---

思路就是这样。实现不难。

在实现的时候，可以用 `for` 语句递推实现。

# AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
pair<int,int> num[200005];
int ans[200005];
int main(){
	scanf("%d%d",&n,&m);
	for(int i = 1; i <= n; i++){
		scanf("%d",&num[i].first);
		num[i].second = i;
	}
	sort(num+1,num+1+n,greater<pair<int,int>>());
	for(int i = 2; i <= n; i++){
		if(num[i].first == num[i-1].first){
			ans[num[i].second] = ans[num[i-1].second];
		}else{
			if((num[i-1].first-num[i].first)%m == 0){
				ans[num[i].second] = ans[num[i-1].second]+2-(num[i-1].first-num[i].first)/m;
			}else{
				ans[num[i].second] = ans[num[i-1].second]+1-(num[i-1].first-num[i].first)/m;
			}
		}
		if(ans[num[i].second] < 0){
			ans[num[i].second] = 0;
		}
	}
	for(int i = 1; i <= n; i++){
		printf("%d ",ans[i]);
	}
	return 0;
}
```

---

## 作者：chenxi2009 (赞：1)

# 思路
先给数组排序。最大的一个数字无论如何都不受限。

对于一个数字，在比它大的数字还可能受限的情况下，它很可能要受限，所以它的答案和比它下一个（更大的）数字的答案密切相关。\
由于它可能和下一个数差值 $>k$ 从而在更大的一个数受限时可以进行若干次操作，所以归纳一下 $ans_i$ 有以下若干种情况：
- $a_i=a_{i+1},ans_i\leftarrow ans_{i+1}$（显然相等的数受限次数相等）
- $a_i<a_{i+1},ans_i\leftarrow\max(0,ans_{i+1}-\left\lceil\frac{a_{i+1}-k-a_i}{k}\right\rceil)$\*

\*：$\frac{a_{i+1}-k-a_i}{k}$ 向上取整之后就是在 $a_{i+1}$ 不动的情况下，$a_i$ 可以移动的次数，完全移动不了的情况取整后为 $-1$，直接归纳进来了。和 $0$ 取大值是因为有可能差距过大导致 $a_i$ 一直是自由的。

详见代码，时间复杂度 $O(n\log n)$。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int lcl;
	long long a;
};
int n,k;
long long ans[200001],cnt[200001];
node a[200001];
inline bool cmp(node a,node b){
	return a.a < b.a; 
}
int main(){
	scanf("%d%d",&n,&k);
	for(int i = 1;i <= n;i ++){//需要按顺序输出答案，所以需要记录原位置 
		scanf("%lld",&a[i].a);
		a[i].lcl = i; 
	}
	sort(a + 1,a + n + 1,cmp);
	for(int i = n - 1;i;i --){
		if(a[i + 1].a == a[i].a)ans[a[i].lcl] = ans[a[i + 1].lcl];
		else ans[a[i].lcl] = max(0ll,ans[a[i + 1].lcl] + 1 - (a[i + 1].a - a[i].a - 1) / k);//推了一下式子 
	} 
	for(int i = 1;i <= n;i ++)printf("%lld ",ans[i]);
	return 0;
}
```

---

## 作者：wjr_jok (赞：1)

结论题。

首先一个很明显的性质是最大的数不可移动状态次数为 $0$，于是很容易想到排序后从大到小考虑。

然后发现对于一个排名为 $x$ 的数，它的不可移动次数最多是等排名为 $x-1$ 的数变为永久可移动之后再移动，所以 $+1$ 即可。

但是有的数一开始就可以移动，然后它再怎么也得等到上一位全部移动完之后才能变成永久可移动的，所以它最优的方案就是先移动，直到它比上一位的数小为止，即减去它与上一位的数的差除以 $k$。

最后注意数字相同以及负数的情况，逆序递推即可。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
struct jgt{
	int x,y;
} xl[200001];
int n,k;
int sc[200001];
bool cmp(jgt x,jgt y){
	return x.x>y.x;
}
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>xl[i].x,xl[i].y=i;
	}
	sort(xl+1,xl+n+1,cmp);
	sc[xl[1].y]=0;
	for(int i=2;i<=n;i++){
		sc[xl[i].y]=max(0,sc[xl[i-1].y]+1-(xl[i-1].x==xl[i].x)-(xl[i-1].x-xl[i].x-1)/k);
	}
	for(int i=1;i<=n;i++){
		cout<<sc[i]<<" ";
	}
	return 0;
}
```

---

## 作者：queenbee (赞：1)

# P11273 「Diligent-OI R1 C」DlgtRank 题解

## 思路
[题目传送门](https://www.luogu.com.cn/problem/P11273)，对于序列 $a$，易得出序列中所有相同数字的不可移动的次数是相同的，所以优先考虑对序列 $a$ 去重。去重后观察到序列排名为第 $i$ 名的元素，它是否可移动取决于第 $i-1$ 名，所以再考虑对序列 $a$ 进行降序排列。

设每个元素的不可移动次数为 $t$。

 因为无严格大于 $a_1$ 的元素，所以 $a_1$ 的名次移动后不会改变，因此 $t_{a_1}=0$。

当 $a_{i-1}-a_i \le k$ 时，元素 $a_i$ 需要等元素 $a_{i-1}$ 移动为 $a_{i-1}+k$ 时才可进行移动，所以 $t_{a_i}=t_{a_{i-1}}+1$。

当 $a_{i-1}-a_i>k$ 时，$a_{i}$ 可以进行移动，当 $a_{i-1}-(a_i+n \times k)<k$ 时停止移动，所以此时 $t_{a_i}=t_{a_{i-1}}+1-(a_{i-1}-a_i-1) \div k$，考虑情况 $t_{a_{i-1}}+1<(a_{i-1}-a_i-1) \div k$ 时 $t_{a_{i-1}}$ 应为 $0$。所以添加判断 $t_{a_i}=\max (0,t_{a_{i-1}}+1-(a_{i-1}-a_i-1) \div k)$。

则有递推式:

$t_{a_{i}} = \begin{cases}t_{a_{i-1}}+1 &\text{if } a_{i-1}-a_i \le k \\ \max(0,t_{a_{i-1}}+1-(a_{i-1}-a_i-1) \div k) &\text{if } a_{i-1}-a_i>k \\
0 &\text{if } i=1
\end{cases}$

最后按照原序列 $a$ 输出 $t_{a_i}$ 即可。

## 程序
```
#include<bits/stdc++.h> //我爱万能头 
using namespace std;
const int N=2e5+10;
int n,m,k;
int a[N],b[N];
map<int,int>t;
bool ct(int a,int b){	//降序排列 
	return a>b;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		b[i]=a[i];
	}
	sort(b+1,b+n+1,ct);	//排序 
	m=unique(b+1,b+n+1)-(b+1);	//去重 
	t[b[1]]=0; //赋值 
	for(int i=2;i<=m;i++){	//递推式处理 
		if(b[i-1]-b[i]>k){
			t[b[i]]=max(0,t[b[i-1]]+1-(b[i-1]-b[i]-1)/k);
		}
		else{
			t[b[i]]=t[b[i-1]]+1;
		}
	}
	for(int i=1;i<=n;i++){
		cout<<t[a[i]]<<" ";
	}
	return 0;	//完结撒花 
}
```

---

## 作者：LDY_ (赞：0)

瞎搞题

首先注意到大小相同数的排名的变化互不干扰且同步，从小到大排个序，去个重先。

其次，注意到当一个数可移动后，下一轮比他小的那个数一定会移动，以此我们可以考虑用大数向小数更新答案。

把数增大抽象成向后移动，可以想象一下堵车的场景，从前到后（数从大到小）车队一点点挪动，易得后一辆车绝对不会超过前一辆车，发现只有以下情况：第一，一开始就被前一辆车卡住，那么只有等前一辆车动了后才能动，即上一个数的答案加一。第二，能够往前走一段，这种情况我们首先可以算出车可移动多少次。之后又分两种小情况。到前一辆车前被卡住了一会，以及到前一辆车前时前一辆车已经可以走了。前者还需加上一些答案。

### 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
int N,k;
int a[200005];
int cnt;
int num[200005];
int tim[200005];
int b[200005],id[200005];
int main(){
	scanf("%d%d",&N,&k);
	for(int i=1;i<=N;i++){
		scanf("%d",&a[i]);
		b[i]=a[i];
	}
    sort(a+1,a+N+1);
    int n=unique(a+1,a+N+1)-a-1;
    num[n]=0;
    for(int i=1;i<=N;i++){
    	id[i]=lower_bound(a+1,a+n+1,b[i])-a;
	}//离散化处理排名 
    for(int i=n-1;i>=1;i--){
    	if(a[i+1]-a[i]<=k){
    		num[i]+=num[i+1]+1;//情况一 
		}
		else{
			tim[i]=(a[i+1]-a[i]-1)/k;//提前能移动多少次 
			if(tim[i]<=num[i+1]) num[i]+=num[i+1]+1-tim[i];//情况二 
		}
	}
	for(int i=1;i<=N;i++) cout<<num[id[i]]<<" ";
	return 0;
} 
```

---

## 作者：SamHJD (赞：0)

将 $a_i$ 从小到大排序。记 $t_i$ 为 $i$ 变为始终可移动的操作轮数，$p_i$ 为 $i$ 变为始终可移动时的值，初值 $t_n=0,p_n=a_n$，从后往前递推。

$a_i$ 相同的 $i$ 答案显然相同。对于 $a_i\ne a_{i+1}$ 的 $i$，若 $a_i+p_{i+1}\times k<t_{i+1}$，即 $i+1$ 变为始终可移动状态前 $i$ 没有追上 $i+1$，那么 $i$ 从一开始即为始终可移动的，$t_i=0,p_i=a_i$。否则在第 $t_i+1$ 轮操作前 $i$ 的值必为 $p_{i+1}-((p_{i+1}-a_i-1)\bmod k)-1$，$i$ 会在 $i+1$ 变为始终可移动状态的后一轮操作中变为始终可移动状态，$p_i=p_{i+1}-((p_{i+1}-a_i-1)\bmod k)-1,t_i=t_{i+1}+1$。

$i$ 的值在变为始终可移动状态前期望会加 $t_i$ 次 $k$，实际加了 $\dfrac{p_i-a_i}{k}$ 次，因此有 $t_i-\dfrac{p_i-a_i}{k}$ 轮操作 $i$ 为不可移动的。

```cpp
#include <bits/stdc++.h>
#define int long long
#define rep(i,k,n) for(int i=k;i<=n;++i)
#define per(i,n,k) for(int i=n;i>=k;--i)
using namespace std;
template<typename T>
inline void read(T &x){
	x=0;int f=1;char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);c=getchar()) x=(x<<3)+(x<<1)+(c-'0');
	x*=f;
}
const int N=2e5+10;
int n,k,a[N],ans[N];
pair<int,int> f[N],p[N];
signed main(){
    read(n);read(k);
    rep(i,1,n) read(a[i]),p[i]={a[i],i};
    sort(p+1,p+n+1);f[n]={p[n].first,0};
    per(i,n-1,1){
        if(p[i].first==p[i+1].first){f[i]=f[i+1];continue;}
        if((f[i+1].second+1)*k<f[i+1].first-p[i].first) f[i]={p[i].first,0};
        else f[i]={f[i+1].first-(f[i+1].first-p[i].first-1)%k-1,f[i+1].second+1};
    }
    rep(i,1,n-1) ans[p[i].second]=f[i].second-(f[i].first-p[i].first)/k;
    rep(i,1,n) printf("%lld ",ans[i]);
	return 0;
}
```

---

## 作者：mahaihang1 (赞：0)

## 思路
对于一次操作，将序列中所有可移动的数加上 $k$ 与将所有不能移动的数减去 $k$ 是等价的；同时，一个数是可移动等价于它比后继小至少 $k+1$。

因此，想要让整个序列的 $a_i$ 都变成可移动的，因为相同的 $a_i$ 最终值是一样的，考虑将所有数降序排序去重后进行操作。

对于不能移动的数，只要一直减 $k$ 使得它比前一个数小至少 $k+1$ 即可。
## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=200010;
int n,k,a[N],b[N],maxx,c[N];
map <int,int> cnt,ans;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i],b[i]=a[i];
	sort(b+1,b+1+n);
	int m=unique(b+1,b+1+n)-b-1;
	c[m]=b[m];
	for(int i=m-1;i>=1;i--){
		c[i]=b[i];
		if(c[i]+k<c[i+1]) continue;
		else ans[b[i]]=ceil((c[i]-(c[i+1]-k)+1)*1.0/k),c[i]=c[i]-ans[b[i]]*k;
	} 
	for(int i=1;i<=n;i++) cout<<ans[a[i]]<<" ";	
	return 0;
}

```

---

## 作者：yanxu_cn (赞：0)

## 思路
个人感觉这题代码难度不太高，实现都比较基础，但是思路有一定难度。题目给的三组样例强度都不怎么样，建议自己造个样例手搓一下。数据最好大一些，容易发现问题。

这篇题解会用分析样例的方法帮助一步一步探求正解。这其中会有一些错误的结论，本题解也会写出来并标记是错误的结论（这样可以更好地表达思维过程）。

先根据题目给的样例分析一下规律。

结论一：最大的数永远可以移动。

结论二：数组的顺序对于结果（不是答案）无影响。

结论三：同一组数据中相同的数据对应的答案相同。

>以上三个结论正确性均显然。由于处理很简单，下文直接保证数据单调不降。

~~结论四：输入中大的数对应的答案一定更小（答案单调不降）。~~ 

>结论是不正确的。可以举一个反例如下：
>```plain
>3 20
>1 114514 114520
>```
>随便手搓一下，正确答案显然是：
>```plain
>0 1 0
>```
>显然与上述结论不符（由此可见自己搓一组样例的重要性）。

结论五：答案一定是连续的，相邻两个答案中，前一个答案不会大于后一个答案加一。

>证明：
>
>**以下数组标号从 $0$ 开始，首轮为第 $1$ 轮。**
>
>根据上述结论，不妨将所有数从小到大排序。
>
>我们注意到，对于 $k\in\{x\in\N_+|1\le x<n\}$，显然如果第 $s$ 轮 $a_k$ 可以移动，那么无论这一轮 $a_{k-1}$ 是否可以移动，第 $a_{k-1}$ 一定可以移动。则我们可以得出除去第 $1$ 轮外，其他轮中 $a_{k-1}$ 不能移动的次数不多于 $a_{k}$ 总的不能移动的次数。故结论成立。

如果没有注意到结论四的问题，其实也可以得出比较基础的接近通过的做法：将数据排序，从大到小处理，若 $a_i-a_{i-1}>k$ 则首次可以更新，则 $ans_{a_{i-1}}=ans_{a_i}$；否则 $ans_{a_{i-1}}=ans_{a_i}+1$。这样的话就可以写出这样的代码。那么理论上就能获得 $18$ pts 的“高分”。
```cpp
#include<bits/stdc++.h>
using namespace std;
constexpr int maxn=2000007;
unordered_map<int,vector<int>>umap;
int a[maxn],b[maxn],c[maxn];
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	
	int n,k,cnt;
	cin>>n>>k;
	for(int i=0;i<n;i++)
	{
		cin>>a[i];
		umap[a[i]].push_back(i);
	}
	sort(a,a+n);
	unique(a,a+n);
	cnt=umap.size();
	a[cnt]=2e9+3;//保证 a[cnt]-a[cnt-1]>k
	for(int i=cnt-1;i>=0;i--)
	{
		b[i]=a[i+1]-a[i]>k?b[i+1]:b[i+1]+1;
		for(auto j:umap[a[i]])
		{
			c[j]=b[i];
		}
	}
	for(int i=0;i<n;i++)
	{
		cout<<c[i]<<' ';
	}
	return 0;
}
```
交上去发现是过了 Subtask #0 #5 #6。分析原因：这三个子任务都满足了答案单调递增的性质。而其他有可能不符合。

根据第四个结论的反例考虑是如何“回退”的。我们假设 $a_i$ 不变，此时 $a_{i-1}$ 可更新的次数为 $cnt=\displaystyle\LARGE[\normalsize\frac{a_{i}-a_{i-1}-1}{k}\LARGE]$。我们注意到如果 $cnt>ans_{a_i}$，则 $ans_{a_{i-1}}=0$；否则 $ans_{a_{i-1}}=ans_{a_{i}}+1-cnt$。总体上就是 $ans_{a_{i-1}}=\max\{0,ans_{a_{i}}+1-cnt\}$。

## 代码
贴一份本人调了半天跑的还算可以的满分代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
constexpr int maxn=2000007;
unordered_map<int,vector<int>>umap;
long long a[maxn],b[maxn],c[maxn];
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int n,k,cnt;
	cin>>n>>k;
	for(int i=0;i<n;i++)
	{
		cin>>a[i];
		umap[a[i]].push_back(i);
	}
	sort(a,a+n);
	unique(a,a+n);
	cnt=umap.size();
	a[cnt]=2e9+7;
	for(int i=cnt-1;i>=0;i--)
	{
		if(a[i+1]-a[i]<=k)b[i]=b[i+1]+1;
		else if(a[i+1]-a[i]>(b[i+1]+1)*k)b[i]=0;
		else b[i]=b[i+1]+1-(a[i+1]-a[i]-1)/k;
		auto ttmp=move(umap[a[i]]);//移动语义，减小常数
		for(auto j:ttmp)
		{
			c[j]=b[i];
		}
	}
	for(int i=0;i<n;i++)
	{
		cout<<c[i]<<' ';
	}
	return 0;
}
```

---

