# [NOISG 2023 Qualification] Dolls

## 题目描述

Marc 正在教幼儿园的小朋友，他选择套娃来教小朋友们认识物体的大小。

一个套娃有一个自己的尺寸，记为 $a$。如果两个套娃 $x$ 和 $y$ 的尺寸 $a_x$ 和 $a_y$ 可以满足 $a_x-a_y\ge2$，那么套娃 $y$ 可以放在套娃 $x$ 中。

很显然，套娃之间是可以互相嵌套多层的。于是 Marc 想请你回答一些问题：

这些问题持续 $n$ 天。在第 $i$ 天，Marc 购买了一个大小为 $a_i$ 的套娃。他想请你求出，在买完第 $i$ 个套娃后，他用前 $i$ 个套娃最多可以套多少层。

## 说明/提示

### 【数据范围】

|$\text{Subtask}$|分值|特殊性质|
|:-:|:-:|:-:|
|$0$|$0$|样例|
|$1$|$23$|$n\le200$|
|$2$|$14$|$a_i$ 为奇数|
|$3$|$27$|$a_i$ 不为 $4$ 的倍数|
|$4$|$36$|无|

对于 $100\%$ 的数据，$1 \le n \le 100000,1 \le a_i \le 500000$。

## 样例 #1

### 输入

```
5
1 2 3 4 5```

### 输出

```
1 1 2 2 3```

## 样例 #2

### 输入

```
5
2 4 6 8 10
```

### 输出

```
1 2 3 4 5```

## 样例 #3

### 输入

```
5
3 3 1 3 2```

### 输出

```
1 1 2 2 2```

# 题解

## 作者：XiaoZi_qwq (赞：9)

# P10729 [NOISG 2023 Qualification] Dolls 题解
## 前言
有点意思的思维题
## 题意分析
有若干个套娃，第 $i$ 个套娃的尺寸为 $a_i$，一个套娃 $x$ 可以被 套娃 $y$ 嵌套当且仅当 $a_y-a_x \geqslant 2$。求对于前 $i$ 个套娃最多可以嵌套几次。

提两个小问题：  
看到 $a_y-a_x \geqslant 2$，你想到了什么？  
遇到有点棘手的条件，第一步应该怎么做？  
## 逐步分析
### SubTask1:$n\le200$：最初的思考
暴力解法：每次询问对 $a_i$ 排序并去重，记 $f_i$表示到第 $i$ 个套娃时，最大嵌套次数。显然我们有  
$f_i= \begin{cases} f_{i-1}+1 &\text{if } a_{i-1}+1 \not= a_i\\ f_{i-2} +1 &\text{ if }  a_{i-1}+1 = a_i \end{cases}$  
### SubTask2:$a_i$ 都是奇数：特殊情况
由于 $a_i$ 都是奇数，所以一定有          $\forall_i,a_i-a_{i-1}\ge 2$ 那么我们就可以直接按第一种情况转移。  
但是这样是最优的吗？  
显然对于每一个**之前没出现过**的 $a_i$，它都可以使答案增大 $1$ （可以参照样例2）。那么我们可以直接用一个数组记录一个数是否出现过，$O(1)$ 计算贡献即可。
### SubTask3:$a_i$ 都不是 $4$ 的倍数：提示
因为 $a_i$ 都不是 $4$ 的倍数，所以你记录数是否出现过的数组的值可能长这样（ $1$ 表示出现过)：  
$[0,1,1,1,0,1,1,0,0,0,1,0,0]$  
相当明显，**若干连续的 $1$ 形成了一组**。对于每一个组，它们之间的贡献是**叠加**的，而且**互不影响**（不理解可以再看一看递推方程），**它们的贡献只受它们的长度影响**（因为我们并不关心这个组内 $a_i$ 的具体值）。  
所以我们可以枚举这个组的长度（显然只有 $0,1,2,3$ ，四种可能），并求出贡献即可。  
思考一个小问题：如果有一个数出现在了两个组之间（如 $6$ 出现在 $5$ 和 $7$ 之间），这个时候该怎么计算贡献呢？
### 正解：扩展
让我们沿着上面的思路继续思考，因为一个组的贡献只受其长度影响，那么我们只需要维护一个组的长度，而且由上面的枚举可以得知：一个长 $len$ 的组，它对答案的贡献为 $\lceil \dfrac{len}{2} \rceil$。（可以在组内手动推一把验证一下）。 而这个信息可以存储在组内任意一个节点上。   
那么现在我们回到了之前那个问题：当一个数出现在了两个组之间时，我们怎么计算贡献？  
分析一下我们需要干什么：我们需要通过前面一个点和后面一个点分别**找到**它们所在组负责存储信息的点，还需要将它们**合并**。有查有并，这不就是**并查集**嘛！  
通过并查集我们就可以快速进行组长的合并与维护。   
到这里题目就分析完了，具体实现看代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
inline int read(){
  register int x=0,f=1;
  char c=getchar();
  while(c<'0' || '9'<c) f=(c=='-')?-1:1,c=getchar();
  while('0'<=c && c<='9') x=(x<<1)+(x<<3)+c-'0',c=getchar();
  return x*f;
}
const int N=500010;
int n,f[N],ans,sz[N];
bool vis[N];
inline int find(int x){ return f[x]=f[x]==x?x:find(f[x]);}
inline void un(int x,int y){
  int fx=find(x),fy=find(y);
  if(fx==fy) return;
  f[fx]=fy;
  sz[fy]+=sz[fx];
}
int main()
{
  for(int i=1;i<=500000;i++) f[i]=i,sz[i]=1;
  n=read();
  for(int i=1,x;i<=n;i++){
    x=read();
    if(vis[x]) {printf("%d ",ans);continue;}
    vis[x]=true;
    //分类讨论 x 所处位置，不同情况有不同的合并方式
    if(!vis[x+1] && !vis[x-1]) ans++;
    else if(!vis[x+1]) un(x-1,x),ans+=sz[find(x)]%2;
    else if(!vis[x-1]) un(x,x+1),ans+=sz[find(x)]%2;
    else{
      int f1=find(x-1),f2=find(x+1);
      ans-=(sz[f1]+1)/2+(sz[f2]+1)/2;//消除影响
      un(x-1,x),un(x,x+1);
      ans+=(sz[find(x)]+1)/2;//再次计算贡献
    }
    printf("%d ",ans);
  }

  return 0;
}

```

---

## 作者：船酱魔王 (赞：4)

## 题意回顾

给定可重集合 $ S $，你需要支持以下两种操作：

* 加入一个数 $ x $；

* 找到序列 $ T $，使得 $ \forall 2 \le i \le |T|, T_i \ge T_{i-1}+2 $，给出最大化的 $ |T| $。

操作数 $ 10^5 $，值域 $ 5 \times 10^5 $。

## 分析

值域这么小必然是要利用的，单点修改考虑设计线段树合并信息的方式。

对于一个段，两个子段的信息我们合并时，我们只关心两个子段的交界处两个数的情况，所以对于一个段的有后效性的状态只有头尾两个数是否被选取，可以记一个段的信息 $ a_{x,y} $ 表示头被选取的情况为 $ x $，尾被选取的情况为 $ y $，此时的选取数字的个数的最大值。

合并可以 $ fa_{x,y}=\max\{lson_{x,p}+rson_{q,y}\}(p+q \le 1) $，单次合并 $ O(1) $ 量级，查询 $ O(1) $，时间复杂度为 $ O(n \log m) $，$ n $ 为操作数 $ m $ 为值域。

## AC 代码

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 5e5 + 5;
int n;
struct node {
    int oo, xo, ox, xx;
} d[N * 4];
node operator+(node p1, node p2) {
    node p3;
    p3.oo = max(p1.oo + p2.xo, p1.ox + p2.oo);
    p3.ox = max(p1.oo + p2.xx, p1.ox + p2.ox);
    p3.xo = max(p1.xo + p2.xo, p1.xx + p2.oo);
    p3.xx = max(p1.xo + p2.xx, p1.xx + p2.ox);
    return p3;
}
void update(int x, int s, int t, int p) {
    if(s == t) {d[p] = (node){0, 0, 0, 1}; return;}
    int mid = (s + t) >> 1;
    if(x <= mid) update(x, s, mid, p * 2);
    else update(x, mid + 1, t, p * 2 + 1);
    d[p] = d[p * 2] + d[p * 2 + 1];
}
int main() {
    scanf("%d", &n);
    int x;
    int lmq = 5e5;
    for(int i = 1; i <= n; i++) {
        scanf("%d", &x);
        update(x, 1, lmq, 1);
        printf("%d ", d[1].xx);
    }
    printf("\n");
    return 0;
}
```

## 加强

考虑值域和操作数都来到 $ 10^7 $ 量级的情况。

此时，我们发现对于去重后的集合 $ S $，如果两个数的差大于等于 $ 2 $ 且无数介于它们之间，那么他们是否被 $ T $ 选取的状态不会互相影响。

如果把 $ S $ 表示为若干个连续整数段的话，不同段的答案是不影响的，每个段的答案都是（设长度为 $ l $）$ \lceil \frac{l}{2} \rceil $，所以只需要支持单点添加和查询所属极长连续段长度即可。

因为只增不删，所以可以使用并查集，每次 $ i $ 加入时如果相邻的 $ i-1,i+1 $ 存在那么合并，需要维护连通块大小即极长连续段长度。

## 加强版 AC 代码

```cpp
#include <cstdio>
#define R return
const int N=1e6;int n,b[N],t[N],s[N],q,x;
int f(int x){R(t[x]-x)?t[x]=f(t[x]):x;}void m(int x,int y){if(b[y]){x=f(x),y=f(y);if(x!=y)t[x]=y,q-=(s[x]+1)/2+(s[y]+1)/2,s[y]+=s[x],q+=(s[y]+1)/2;}}
int main(){scanf("%d",&n);while(n--){scanf("%d",&x);if(!b[x]){q++,b[x]=1,t[x]=x,s[x]=1,m(x,x-1),m(x,x+1);}printf("%d ",q);}R 0;}
```

---

## 作者：Minche1992 (赞：2)

### Subtask 2 分析

如果所有数都是奇数，那么我们只需要记录不同数字的个数即可。因为两个奇数的差值肯定大于等于 $2$，所以相邻的奇数不会互相影响。我们可以开一个布尔数组 `vis[]` 来标记数字是否出现过，并且维护一个计数器 `cnt[]` 来记录不同数字的个数。代码如下：

```cpp
for (int i = 1; i <= n; i++) {
    cin >> x;
    if (!vis[x]) {
        vis[x] = 1;
        cnt++;
    }
    cout << cnt << ' ';
}
```

### Subtask 3 分析

一开始不容易发现 $a_i$ 不是 $4$ 的倍数有何用处。如果 $a_i$ 不是 $4$ 的倍数，`vis[]` 数组可能会长成这样：

$$
\{ \text{null}, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0 \}
$$

也可能是这样：

$$
\{ \text{null}, 1, 1, 0, 0, 0, 1, 1, 0, 0 \}
$$

观察可以发现，$4$ 的倍数似乎把所有的数分割开了，所有数字被分成长度为 $3$ 的段，因为有一个 $0$ 隔着。每一段的末尾都比下一段的开头至少大 $2$，因此这些段互不干扰。每个段有几种情况：$\{1, 0, 1\}$，$\{0, 0, 1\}$ 等。

接着我们发现，即使没有特殊性质我们也能写了。无论输入的数字如何，`vis[]` 数组总是被 $0$ 分割成许多由 $1$ 组成的小段，这些小段互不影响。我们只需要计算这些小段的总贡献即可。容易发现，对于长度为 $\text{len}$ 的小段，其贡献为：

$$
\left\lfloor \frac{\text{len} + 1}{2} \right\rfloor
$$

~~（其实就是上取整喵）~~

然而，题目要求我们求出对于每个 $i$ 前面的数字的答案，因此我们不能直接使用上面的公式计算，并且对于每一个新出现的 $a_i$，我们需要分类讨论。

#### 情况 1

如果 $a_i$ 的左右两边都还没有数字，即 $\text{vis}_{a_i-1} = 0$ 并且 $\text{vis}_{a_i+1} = 0$，那么只需把 $a_i$ 加入到段中，将 `ans` 加 $1$ 即可。

#### 情况 2

如果 $a_i$ 的左边有数字，右边没有，即 $\text{vis}_{a_i-1} = 1$ 并且 $\text{vis}_{a_i+1} = 0$，那么左边的线段长度会增加 $1$。根据公式 $\left\lfloor \frac{\text{len}+1}{2} \right\rfloor$，如果原来的段长度是偶数，`ans` 需要增加 $1$。右边有数字，左边没有的情况与此类似。

#### 情况 3

如果 $a_i$ 的两边都有数字，即 $\text{vis}_{a_i-1} = 1$ 且 $\text{vis}_{a_i+1} = 1$，这时需要合并两边的线段。我们分别计算合并前后的贡献，公式为：

$$
\Delta \text{ans} = \left\lfloor \frac{\text{len}_1 + \text{len}_2 + 2}{2} \right\rfloor - \left\lfloor \frac{\text{len}_1 + 1}{2} \right\rfloor - \left\lfloor \frac{\text{len}_2 + 1}{2} \right\rfloor
$$

### 信息维护

为了实现上述操作，我们需要维护每个段的信息，特别是段的长度。为了方便合并操作，我们可以使用一个结构体来维护每个段的左右端点及其长度。代码如下：

```cpp
struct Line {
    int l, r, len; // l 和 r 表示线段的左右端点，len 维护线段的长度
} line[maxn];
```

接下来，我们对每种情况分别进行操作：

#### 情况 1

创建一个新的线段，将 `line[x].l` 和 `line[x].r` 都设置为 $x$，长度 $\text{len}$ 设置为 $1$。

#### 情况 2

将 $x$ 加入左边数字所在的线段，将左边线段的右端点 $r$ 设置为 $x$，同时长度加 $1$。右边有数字的情况类似。

#### 情况 3

合并两边的线段，将左边线段的右端点 $r$ 设置为右边线段的右端点，右边线段的左端点设置为左边线段的左端点，并将新线段的长度加 $1$。

### 完整代码

```cpp
#include <iostream>
#include <vector>
using namespace std;
const int maxn = 5e5 + 10;
bool vis[maxn];
struct Line {
    int l, r, len;
} line[maxn];

int main() {
    freopen("dolls.in", "r", stdin);
    freopen("dolls.out", "w", stdout);
    int n;
    cin >> n;
    int x, ans = 0;
    int l, r;
    for (int i = 1; i <= n; i++) {
        cin >> x;
        if (vis[x]) {
            cout << ans << ' ';
            continue;
        }
        else vis[x] = 1;
        if (vis[x-1] == 0 && vis[x+1] == 0) { // case 1
            line[x].l = x;
            line[x].r = x;
            line[x].len = 1;
            ans++;
            cout << ans << ' ';
            continue;
        }
        if (vis[x-1] == 0 && vis[x+1]) { // case 2(1)
            if (line[x+1].len % 2 == 0) ans++;
            line[x].r = line[x+1].r;
            line[x].l = x;
            line[x].len = line[x+1].len + 1;
            line[line[x].r].l--;
            line[line[x].r].len++;
            cout << ans << ' ';
            continue;
        }
        if (vis[x-1] && vis[x+1] == 0) { // case 2(2)
            if (line[x-1].len % 2 == 0) ans++;
            line[x].l = line[x-1].l;
            line[x].r = x;
            line[x].len = line[x-1].len + 1;
            line[line[x].l].r++;
            line[line[x].l].len++;
            cout << ans << ' ';
            continue;
        }
        if (vis[x-1] && vis[x+1]) { // case 3
            l = line[x-1].l;
            r = line[x+1].r;
            ans += (line[l].len + line[r].len + 2) / 2 - (line[l].len + 1) / 2 - (line[r].len + 1) / 2;
            line[l].r = r, line[r].l = l; // 合并
            line[l].len += line[r].len + 1; // 更新长度
            line[r].len = line[l].len;
            cout << ans << ' ';
        }
    }
    return 0;
}
```

---

## 作者：UserJCY (赞：2)

看大家都是用并查集写的，我不是，所以来交一发题解。

### 题意转化

本题可以看作往桶里装数，两个数之间必须间隔至少 $1$ 才能都被选中（即对 $ans$ 带来贡献，否则相邻的只有一个能被选中。

### 分析

题目的特殊性质给了我很好的启发：

第一个特殊性质“$a_i$ 为奇数”，实际上就是每个数都可以被选中，同样例 2。

第二个特殊性质“$a_i$ 不为 $4$ 的倍数”，在填地最满的情况下，形如这样：
```
11101110111
TFTFTFTFTFT
```
其中，```1``` 代表有数，```0``` 代表没数，第二行的 ```T``` 和 ```F``` 分别代表对答案有贡献与无贡献。

### 正解

我们再将以上的特殊性质推广，得到以下结论：

**对于一个连续有数的区间，对答案的贡献为 $\lfloor \frac{len}{2} \rfloor$ 。**

在操作中，每次读入一个数的位置，遵循以下规则操作：

- 如果这个位置原先有数，直接输出 $ans$ ，然后跳过。
  
- 如果这个数的前后有数，当且仅当所有与其相邻的区间长度为偶数，它才对答案有贡献，然后维护区间合并

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
pair<int,int> a[500010];
int ans;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		int x;cin>>x;
		if(a[x]!=make_pair(0,0)){//这个点已经有数了 
			cout<<ans<<' ';
			continue;
		}
		if(a[x-1]==make_pair(0,0)&&a[x+1]==make_pair(0,0)){//这个点周围没有数 
			a[x]=make_pair(x,x);
			ans++;
		}
		else{
			if(a[x-1]!=make_pair(0,0)&&a[x+1]!=make_pair(0,0)){//这个点前后都有数 
				if((a[x-1].second-a[x-1].first+1)%2==0&&(a[x+1].second-a[x+1].first+1)%2==0)ans++;
				a[x]=make_pair(1,1);
				a[a[x-1].first].second=a[x+1].second;
				a[a[x+1].second].first=a[x-1].first;
			}
			else if(a[x-1]!=make_pair(0,0)){//这个点前面有数 
				a[x]=make_pair(a[x-1].first,x);
				a[a[x-1].first].second=x;
				ans+=(a[x].second-a[x].first+1)%2;
			}
			else{//这个点后面有数 
				a[x]=make_pair(x,a[x+1].second);
				a[a[x+1].second].first=x;
				ans+=(a[x].second-a[x].first+1)%2;
			}
		}
		cout<<ans<<' ';
	}
	return 0;
}
```

---

## 作者：_EternalRegrets_ (赞：2)

[传送门](https://www.luogu.com.cn/problem/P10729)

### 题意描述：
>给定 $n$ 个娃娃的大小，如果两个娃娃大小相差不小于 $2$，则大的可以把小的套住。对于 $i$ 从 $1$ 到 $n$，求前 $i$ 个娃娃最多可以套多少层。

### Solution:
对于一个连续数列，易发现最多的层数是数列长度除以二取上整。

同时，多个非连续的连续序列均可以独立考虑

这样，问题就转化为如何维护连续序列。

使用 **并查集** 可以实现这一点。

对于每一个新读入的数字，先看它是否已经出现过。

若已出现过，答案不变。

否则，根据与其相邻的数字分四种情况讨论，并维护并查集。

具体见代码。

### code：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int f[500005];
int sz[500005];
bool vis[500005];

int findf(int x){
	if(f[x]==x){
		return x;
	}
	
	return f[x]=findf(f[x]);
}

void add(int x,int y){
	int fx,fy; fx=findf(x),fy=findf(y);
	if(fx!=fy){
		f[fx]=fy;
		sz[fy]+=sz[fx];
	}
}

signed main(){
	int n; cin>>n;
	
	for(int i=1;i<=500000;i++){
		f[i]=i;
		sz[i]=1;
	}
	
	int ans; ans=0;
	for(int i=1;i<=n;i++){
		int x; cin>>x;
		
		if(vis[x]){
			cout<<ans<<" ";
			continue;
		}
		
		vis[x]=1;
		
		if(vis[x-1] && vis[x+1]){
			int fx,fy; fx=findf(x-1),fy=findf(x+1);
		    ans-=(sz[fx]+1)/2+(sz[fy]+1)/2;
		    
		    add(x,x-1);
			add(x,x+1);
			
		    ans+=(sz[findf(x)]+1)/2;
		}
		else if(vis[x-1]){
			add(x,x-1);
			ans+=sz[findf(x)]%2;
		}
		else if(vis[x+1]){
			add(x,x+1);
			ans+=sz[findf(x)]%2;
		}
		else{
			ans++;
		}
		
		printf("%d ",ans);
	}
	
	return 0;
}
```

---

## 作者：wmy18929355137 (赞：1)

# P10729 [NOISG 2023 Qualification] Dolls 题解
#### 前言:
这题是我打模拟赛时唯一做出来且能提交题解的题

~~（我第一眼想到差分约束可以afo了~~,
## 前置知识:[并查集](https://oi-wiki.org/ds/dsu/)
## 思路:
当每次输入新的套娃 $a_i$ 时，可以将所有满足 $j \in [1,i-1]$ 且 $|a_i-a_j| \leq 1$ 的 $j$ 与 $i$ 连边。设此时连通块个数为 $k$，第 $i$ 个连通块所包含的点的个数为 $sz_i$。因为连边的两个点不能同时选，因此每一次的答案就是: 
$$\displaystyle \sum_{i=1}^k \lceil \frac{sz_i}{2} \rceil$$
然后我们用并查集维护一下 $sz_i$，每一次询问时遍历一遍 $sz_i$ 再计算即可。

然而发现每一次询问都遍历一遍可能会T ~~（？没试过~~,因此考虑优化。我们可以维护上一次答案 $ans$，每一轮开始时先让 $ans \gets ans+1$（新的一个 $sz=1$ 的连通块，且 $\lceil \frac{1}{2} \rceil = 1$），当连通块 $i$ 与连通块 $j$ 连边时，那么就让 $ans \gets ans-\lceil \frac{sz_i}{2} \rceil-\lceil \frac{sz_j}{2} \rceil+\lceil \frac{sz_i+sz_j}{2} \rceil$。这样时间复杂度就降到了 $O(n \alpha(n) + n \log n)$ （$\log$ 是map带来的）。

然后就过了。

**注意 $a_i$ 重复时 $ans$ 不能 $+1$!**


## code:
```cpp
#include <bits/stdc++.h>
using namespace std;

int n;
int f[514514],sz[514514],ans = 0;
map <int,int> mp;

int fd(int x) {
	if (f[x] == x) return x;
	return f[x] = fd(f[x]);
}

void merge(int x,int y) {
	int tx = fd(x);
	int ty = fd(y);
	if (tx != ty) {
		f[tx] = ty;
		ans -= (sz[ty] + 1) / 2;
		ans -= (sz[tx] + 1) / 2;
		sz[ty] += sz[tx];
		ans += (sz[ty] + 1) / 2;
		sz[tx] = 0;
	}
}

int main() {
	cin >> n;
	for (int i = 1; i <= 500000; i++) {
		f[i] = i;
		sz[i] = 1;
	}
	for (int i = 1; i <= n; i++) {
		ans++;
		int x;
		cin >> x;
		if (mp[x]) ans--;
		mp[x] = 1;
		if (mp[x - 1])
			merge(x,x - 1);
		if (mp[x + 1])
			merge(x,x + 1);
		cout << ans << " ";
	}
	return 0;
}
```

---

## 作者：Nuyoah_awa (赞：1)

### 题目大意

给定 $n$ 个数，求其中最多能选几个数使得其两两不相邻。

### 题目分析

我们考虑一般情况下会怎么选，若对于一连续数列 $l, l+1, \dots, r-1, r$，则很明显最多选 $\lceil \dfrac{(l+r)}{2}\rceil$ 个数。

若对于两连续数列 $l_1, \dots, r_1, l_2, \dots, r_2$，因其中间至少相隔一个 $r_1 + 1$，所以可以将两段分开算，答案为 $\lceil \dfrac{(l_1+r_1)}{2}\rceil + \lceil \dfrac{(l_2+r_2)}{2}\rceil$。

拓展到一个序列 $a_1, \dots a_n$，则可视为将其分成 $k$ 个连续段分开算再求和。对于求连续段，用并查集维护即可。

### code
```cpp
#include <iostream>
#include <cstdio>

using namespace std;

const int N = 5e5 + 5;
int n, fa[N], sz[N], ans;
bool cnt[N];

int find(int x){return fa[x] == x ? x : fa[x] = find(fa[x]);}

int main()
{
	scanf("%d", &n);
	for(int i = 0;i <= 5e5 + 1;i++)	fa[i] = i;
	for(int i = 1, x;i <= n;i++)
	{
		scanf("%d", &x);
		if(cnt[x])
		{
			printf("%d ", ans);
			continue;
		}
		cnt[x] = true;
		if(cnt[x-1] && cnt[x+1])
		{
			int fal = find(x-1), far = find(x+1);
			ans -= (sz[fal] + 1) >> 1;
			ans -= (sz[far] + 1) >> 1;
			sz[x] = sz[fal] + sz[far] + 1, fa[fal] = fa[far] = x;
			ans += (sz[x] + 1) >> 1;
		}
		else if(cnt[x-1])
		{
			int fal = find(x-1);
			ans -= (sz[fal] + 1) >> 1;
			sz[x] = sz[fal] + 1, fa[fal] = x;
			ans += (sz[x] + 1) >> 1;
		}
		else if(cnt[x+1])
		{
			int far = find(x+1);
			ans -= (sz[far] + 1) >> 1;
			sz[x] = sz[far] + 1, fa[far] = x;
			ans += (sz[x] + 1) >> 1;
		}
		else
		{
			sz[x] = 1, ans++;
		}
		printf("%d ", ans);
	}
	return 0;
}
```

---

