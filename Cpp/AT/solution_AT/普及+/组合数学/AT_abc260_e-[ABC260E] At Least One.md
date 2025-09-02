# [ABC260E] At Least One

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc260/tasks/abc260_e

整数 $ M $ および $ N $ 個の整数の組 $ (A_1,\ B_1),\ (A_2,\ B_2),\ \dots,\ (A_N,\ B_N) $ が与えられます。  
 すべての $ i $ について $ 1\ \leq\ A_i\ \lt\ B_i\ \leq\ M $ が成り立っています。

次の条件を満たす数列 $ S $ を**良い数列**と呼びます。

- $ S $ は数列 $ (1,2,3,...,\ M) $ の連続部分列である。
- すべての $ i $ について $ S $ は $ A_i,\ B_i $ の少なくとも一方を含んでいる。

長さ $ k $ の良い数列としてあり得るものの個数を $ f(k) $ とします。  
 $ f(1),\ f(2),\ \dots,\ f(M) $ を列挙してください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 2\ \leq\ M\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ A_i\ \lt\ B_i\ \leq\ M $
- 入力される値はすべて整数

### Sample Explanation 1

良い数列としてあり得るものを列挙すると次のようになります。 - $ (1,2) $ - $ (1,2,3) $ - $ (2,3,4) $ - $ (3,4,5) $ - $ (1,2,3,4) $ - $ (2,3,4,5) $ - $ (1,2,3,4,5) $

## 样例 #1

### 输入

```
3 5
1 3
1 4
2 5```

### 输出

```
0 1 3 2 1```

## 样例 #2

### 输入

```
1 2
1 2```

### 输出

```
2 1```

## 样例 #3

### 输入

```
5 9
1 5
1 7
5 6
5 8
2 6```

### 输出

```
0 0 1 2 4 4 3 2 1```

# 题解

## 作者：wnsyou (赞：15)

# [At Least One](https://www.luogu.com.cn/problem/AT_abc260_e)
## 题意
给定一个整数 $m$ 和 $n$ 对数 $(a_i, b_i)$，我们定义一个 $f(x)$ 函数表示满足以下要求的整数序列数量：

- 整数序列为 $(1, 2, 3 \cdots m)$ 的一个子段且序列长度为 $x$。
- 对于 $1 \leqslant i \leqslant n$，满足 $a_i$ 或者 $b_i$ 在整数序列中出现过(可以都出现，不可以都不出现)。

求 $f(1),f(2)\cdots f(m)$。
## 思路
### 暴力
枚举左右端点，判断是否满足要求，统计答案。

时间复杂度：$O(m ^ 2 \times n)$。
### 优化
枚举左右端点就 $T$ 了，但我们能够发现：如果 $(1, 2, 3 \cdots m)$ 的一个区间 $[l, r]$ 满足要求，则：

- 对于所有 $1 \leqslant i \leqslant l, r \leqslant j \leqslant m$，区间 $[i, j]$ 必然满足要求。

也就是说，对于每个左端点为 $i$，它对答案的贡献**必然是一个区间。**

枚举左端点，对于每个左端点 $i$ 找到最小的 $j$ 使得区间 $[i,j]$ 满足要求，那么 $f(j - i + 1), f((j + 1) - i + 1) \cdots f(m - i + 1)$ 都要加一，这个很明显可以用差分维护。

对了，这个只能提供常数优化，重要的还是思想。
### 最终正解
枚举左端点 $i$ 没问题，但暴力查找最小的 $j$ 是会超时的，怎样优化这个 $O(n \times m)$ 呢？

又是一顿观察，我们可以发现：随着 $i$ 从小到大，最小的 $j$ 是单调不减的，可以考虑使用双指针，左指针每次加 $1$，那么右指针怎么更新呢？

- 很显然，对于一个 $1 \leqslant k \leqslant n$，如果 $a_k \geqslant i + 1$，那么**对于它来说**，右指针并不需要移动，只需保持 $j$ 就行了。
- 反之，如果 $a_k < i + 1$，那么 $j$ 至少也要移动到 $b_k$ 去，即 $j \geqslant b_k$。
- 而如果 $b_k < i$，那么就可以退出 $i$ 循环了，后面的必然都不合法。

做法就出来了，先预处理出当左端点为 $i$ 时，右端点至少为几，假设用 $c$ 数组存储。

- 对于每个 $1 \leqslant i \leqslant n$，$c_{a_i + 1} = \max(c_{a_i + 1}, b_i)$。

然后就是枚举左端点 $i$，枚举的同时更新 $c_i$，取前缀最大值即可，注意左端点最大为 $\min\limits_{1 \leqslant i \leqslant n}\{ b_i\}$。
### 复杂度
- 时间：$O(n + m)$。
- 空间：$O(m)$。

## Code

~~挑战最短代码，不服来战。~~

```cpp
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 2e5 + 10;

int n, m, a, b, c[N], mr, ans[N];

int main () {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> m;
  mr = m;
  for (int i = 1; i <= n; i++) {
    cin >> a >> b;
    c[0] = max(c[0], a), c[a + 1] = max(c[a + 1], b), mr = min(mr, b); // i = 1 时右端点至少为 max(a[i])，更新 c 数组
  }
  for (int i = 1; i <= mr; i++) {
    c[i] = max({c[i - 1], c[i], i}); // 前缀最大值
    ans[c[i] - i + 1]++, ans[m - i + 2]--; // 差分
  }
  for (int i = 1; i <= m; i++) {
    ans[i] += ans[i - 1]; // 还原差分数组
    cout << ans[i] << ' ';
  }
  return 0;
}
```

---

## 作者：roger_yrj (赞：6)

## 前言

学校的一套训练题出了 ABC260 的题目（没错和 @Exp10re 是同一个学校），觉得这道题比较有意思，自己也有一个思维难度比较低的解题思路，所以决心写篇题解。

## 题意

给出 $n$ 对点 $(a_i,b_i)$，在 $[1,m]$ 之间取一段区间。

当每一对点都有一个点在这个区间内时，这个区间合法。

求出不同长度的合法区间分别有多少个。

## 题解

设 $l,r$ 为区间左右端点。

暴力枚举 $r$，算出 $l_{\max}$，更新答案。

因为当 $[l_{\max},r]$ 合法时，$[l_{\max}-1,r]$ 一定也合法。（因为 $[l_{\max},r]$ 包含的数 $[l_{\max}-1,r]$ 也一定包含嘛~）

所以每次将长度为 $r-l+1$ 到 $r$ 的答案 $+1$。

稍微想想就能知道，$r_{\min}=a_{\min}$。

所以 $r$ 在 $r_{\min}$ 和 $m$ 之间枚举。

对于每个 $r$，$l_{\max}$ 怎么算呢。

分两种情况：

- 当 $b_i\le r$ 时，那么 $a_i$ 就没有用了，因为取 $b_i$ 一定更优。
- 当 $b_i>r$ 时，只能取 $a_i$。

全部合起来取 $\min$ 即可。

每次取到新的 $b_i$ 时把相应的 $a_i$ 删掉就行了，这可以用 multiset 或堆维护。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10,INF=1145141919;
int n,m,a[N],b[N],ans[N],l=INF,r=-INF;
vector<int>vis[N];
multiset<int>s;
int main(){
	cin>>n>>m;
	for(int i=1,x,y;i<=n;i++){
		scanf("%d%d",&a[i],&b[i]);
		if(a[i]>b[i])swap(a[i],b[i]);
		r=max(r,a[i]);
		vis[b[i]].push_back(i);
	}
	for(int i=1;i<=n;i++){
		if(b[i]<r)s.insert(b[i]);
		else s.insert(a[i]);
	}
	for(;r<=m;r++){
		int len=vis[r].size();
		for(int i=0;i<len;i++){
			s.insert(b[vis[r][i]]);
			s.erase(s.lower_bound(a[vis[r][i]]));
		}
		l=*s.begin();
		ans[r-l+1]++;
		ans[r+1]--;
	}
	for(int i=1,x=0;i<=m;i++){
		x+=ans[i];
		printf("%d ",x);
	}
}
```

---

## 作者：Exp10re (赞：5)

## 前言

学校的一套训练题出了 ABC260 的题目，觉着这道题比较有意思，自己也有一个时间复杂度比较低的解题思路，所以决心写篇题解。

upd：修改了部分不符合题解规范的语句。

## 题解

我们称一个序列若为“好序列”，则该序列为“合法的”，否则，该序列是“不合法的”。

考虑每一个 $(1,2,3,\cdots,M)$ 的连续子序列都可以用一个数对 $(h,s)$ 表示，其中，$h$ 表示数对的起始位置，$s$ 表示数对的长度，即：数对 $(h,s)$ 表示的序列是 $(h,h+1,\cdots,h+s-1)$。

容易得到：若数对 $(h,s)$ 表示的序列不合法，那么数对 $(h,s-1)$ 和数对 $(h+1,s-1)$ 表示的序列均不合法。

原因显而易见：若 $(h,h+1,\cdots,h+s-1)$ 对于给出的数对 $(A_i,B_i)$ 不包含 $A_i$,$B_i$ 中的任意一个，那么显然其子序列也不包含 $A_i$,$B_i$ 中的任意一个。

考虑维护数列 $a_{1,2,\cdots,M}$，含义为：对于所有以 $i$ 开头的子串，长度小于等于 $a_i$ 的序列都不合法。

那么对于每一组 $(A_i,B_i)$，我们可以得到三个限制条件：

1. 对于所有以 $1$ 开头的子串，长度小于等于 $A_i-1$ 的序列都不合法。
1. 对于所有以 $A_i+1$ 开头的子串，长度小于等于 $B_i-A_i-1$ 的序列都不合法。
1. 对于所有以 $B_i+1$ 开头的子串，长度小于等于 $M-B_i-1$ 的序列都不合法。

即：数对 $(1,A_i-1)$，$(A_i+1,B_i-A_i-1)$，$(B_i+1,M-B_i-1)$ 所表示的序列以及其子序列都不合法。这个结论是显而易见的，因为以上提到的序列均不包含 $A_i$ 和 $B_i$ 中的任意一个。

对所有给出的数对 $(A_i,B_i)$ 执行以上操作，得到以下代码：

```cpp
for(i=1;i<=n;i++)
{
	scanf("%d%d",&ta,&tb);
	a[1]=max(a[1],ta-1);
	a[ta+1]=max(a[ta+1],tb-ta-1);
	a[tb+1]=max(a[tb+1],m-tb);
}
```

对于每一个限制条件 $a_i$，又可以进行以下转移：

```cpp
for(i=1;i<=m;i++)
{
	a[i+1]=max(a[i+1],a[i]-1);
}
```

它的含义为：若数对 $(i,a_i)$ 表示的序列不合法，那么数对 $(i+1,a_i-1)$ 表示的序列一定不合法。

接下来考虑答案的计算：对于长度为 $i$ 的序列，有：长度为 $i$ 的合法序列的个数等于长度为 $i$ 的序列的总个数减去长度为 $i$ 的不合法序列的个数。

长度为 $i$ 的序列的总个数是容易统计的：其个数为 $M-i+1$。考虑对长度为 $i$ 的不合法序列的个数进行计算。结合数组 $a$ 的定义容易得到：长度为 $i$ 的不合法序列的个数等于数组 $a$ 中大于等于 $i$ 的数的个数。

因此考虑反向累加统计数组 $a$ 中有多少个数大于等于 $i$，得到以下代码：

```cpp
for(i=1;i<=m;i++)
{
	cnt[a[i]]++;
}
for(i=m;i>=1;i--)
{
	tot+=cnt[i];
	ans[i]=m-i+1-tot;
}
```

最终顺次输出数组 $ans$ 即可。

总时间复杂度是 $O(N)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int cnt[200010],a[200010],ans[200010];
int main()
{
	int i,j,n,m;
	int ta,tb,tot=0;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++)
	{
		scanf("%d%d",&ta,&tb);
		a[1]=max(a[1],ta-1);
		a[ta+1]=max(a[ta+1],tb-ta-1);
		a[tb+1]=max(a[tb+1],m-tb);
	}
	for(i=1;i<=m;i++)
	{
		a[i+1]=max(a[i+1],a[i]-1);
	}
	for(i=1;i<=m;i++)
	{
		cnt[a[i]]++;
	}
	for(i=m;i>=1;i--)
	{
		tot+=cnt[i];
		ans[i]=m-i+1-tot;
	}
	for(i=1;i<=m;i++)
	{
		printf("%d ",ans[i]);
	}
	return 0;
}
```

---

## 作者：timmark (赞：2)

# ABC 260E 题解

一道很有意思的双指针法题。

满足条件的连续数列，看上去非常双指针。

考虑一个新加入的元素 $i$，他只会影响到那些满足 $A_x=i$ 或 $B_x=i$ 的 $x$，$i$ 被删除同理。

那么，考虑单调性。因为如果 $[l,r]$ 是可行的，那么 $l$ 到 $[r,m]$ 中的任意一个数都是可行的。

那么，我们动态处理每一个数的影响即可。

采用和逛画展类似的思路，设 $a_i$ 表示 $A_i$ 是否在 $[l,r]$ 中，$b_i$ 同理，$cnt$ 表示有几个 $i$ 满足 $a_i=1$ 或 $b_i=1$。对于每一个新加入的 $r$ 我们把那些满足 $A_i=r$ 的位置的 $a_i$ 设为 $1$，如果 $b_i=0$，那么就将 $cnt$ 加 $1$，对于 $B_i=r$ 的 $i$ 同理。

如果 $cnt=n$，那么长度从 $r-l+1$ 到 $m-l+1$ 的合法序列数量都会 $+1$。发现有区间加法操作，~~我们考虑使用线段树解决此问题~~，用差分完成。

然后 $l$ 被删除后，采用和加入类似的维护方法。

最后将答案前缀和处理后输出即可。

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=5e5+5;
int n,m,A[maxn],B[maxn],cnt,ans[maxn];
vector <int> fa[maxn],fb[maxn];//fa_x 表示有那些数的 a_i 等于 x，fb 同理
bool a[maxn],b[maxn],flag;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m ;
	for(int i=1;i<=n;i++){
		cin >> A[i] >> B[i] ;
		fa[A[i]].push_back(i); 
		fb[B[i]].push_back(i);
	}for(int l=1,r=1;l<=m;l++){
		while(r<=m){
			if(flag) break;
			for(int j:fa[r]){
				if(!b[j]) cnt++;
				a[j]=1;
			}for(int j:fb[r]){
				if(!a[j]) cnt++;
				b[j]=1;
			}if(cnt==n){
				flag=1;
				break;
			}r++;
		}if(flag) ans[r-l+1]++,ans[m-l+2]--;
		for(int j:fa[l]){
			if(!b[j]) cnt--;
			a[j]=0;
		}for(int j:fb[l]){
			if(!a[j]) cnt--;
			b[j]=0;
		}if(cnt<n) flag=0,r++;
	}for(int i=1,sum=0;i<=m;i++) cout << (sum+=ans[i]) << " " ;
	return 0;
}
```

---

## 作者：__Ginka__ (赞：1)

### 关键步骤
#### 排序约束对：按 $B_i$ 升序排列，便于后续处理右端点。
#### 预处理最小左端点：通过逆序遍历，维护 $e[i]=\min\{A_j\mid j\ge i\}$。
#### 覆盖条件统计：用前缀和数组 $f$ 标记每个位置是否被所有约束覆盖。
#### 区间贡献计算：对每个右端点 $i$，确定最左端点 $l$，并统计所有区间长度 $k$。

### 公式
对每个右端点 $i$，可行区间为 $[l,i]$，其贡献为：  
$$
\Delta g[l]+=1,\quad\Delta g[i+1]-=1
$$
最终通过前缀和得到 $f(k)=\sum_{j=1}^kg[j]$。

思路较粗糙，建议搭配注释食用代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[200009],b[200009],c[200009],d[200009],e[200009],f[200009],g[200009],h[200009],p[200009],q[200009],r[200009],s[200009],t[200009];
vector<pair<int,int> > v;//存储排序后的(Ai,Bi)
int main()
{
    cin>>n>>m;
    for(int i=0;i<n;i++)
    {
        int x,y;
        cin>>x>>y;
        a[i]=min(x,y);//存Ai和Bi的小值
        b[i]=max(x,y);//存Ai和Bi的大值
        v.push_back({b[i],a[i]});//方便处理右端点
    }
    sort(v.begin(),v.end());//按Bi升序排序
    for(int i=0;i<n;i++)
    {
        c[i]=v[i].first;//存排序后的Bi
        d[i]=v[i].second;//存对应的Ai
    }
    // e[i]:指从i到n-1区间内的最小Ai
    e[n]=1e9;//边界初始值
    for(int i=n-1;i>=0;i--) e[i]=min(d[i],e[i+1]);//逆序维护最小值
    //f[i]:覆盖所有约束的右端点i的最小区间数
    memset(f,0,sizeof(f));
    for(int i=0;i<n;i++)
    {
        f[0]++;//初始所有约束覆盖0点
        if(a[i]<=m) f[a[i]]--;//用差分标记约束结束位置
    }
    for(int i=1;i<=m;i++)
        f[i]+=f[i-1];//前缀和得到覆盖次数
    int mnb;//所有Bi中的最小值
    if(n>0) mnb=c[0];
    else mnb=1e9;
    //g用于差分统计好序列数量
    memset(g,0,sizeof(g));
    for(int i=1;i<=m;i++)//右端点
    {
        if(f[i]>0) continue;//未被所有约束覆盖
        int mb;//Bi<=i的最小Bi对应的Ai
        if(mnb<=i) mb=mnb;
        else mb=1e9;
        int j=upper_bound(c,c+n,i)-c-1;//最后一个Bi<=i的位置
        int ma=1e9;//j之后的最小Ai
        if(j+1<n) ma=e[j+1];
        int lm=min(mb,ma);//最左可能的左端点
        if(lm==1e9) continue;
        //确定可行区间[i-lm+1,i]
        int aa=i-lm+1;//左端点
        int bb=i;//右端点
        if(aa<1) aa=1;//左端点越界处理
        if(aa>bb) continue;
        //差分标记区间贡献
        g[aa]++;
        g[bb+1]--;
    }
    for(int i=1;i<=m;i++)
    {
        g[i]+=g[i-1];
        cout<<g[i]<<" ";
    }
    return 0;
}
```

---

## 作者：Meickol (赞：1)

可能是题解区里最好理解的一篇？

双指针+差分。

显然，当序列 $[L, R]$ 是满足条件的连续序列时，则左边界向左拓展，右边界向右拓展时，得到的新序列依旧满足条件，我们会想到计算贡献。

为防止区间重复，我们固定左边界，区间只往右延伸，右指针一直延伸至第一个位置满足处，则该位置为 $R_{min}$。

即枚举左边界 $L$，然后移动右边界，使得其为满足条件的最小右边界（记为 $R_{min}$），则长度在 $[R_{min} - L + 1, M - L + 1]$ 之间的答案都增加 $1$，这个区间修改用差分优化即可。

我们发现，随着 $L$ 逐渐增大，最小的 $R$ 单调不减，因而可以使用双指针进行优化。



时间复杂度 $O(N+M)$。

```cpp
#define rep(x,y,z) for(int x=y;x<=z;x++)
const int N=2e5+5;
int n,m;
vector<int> v[N]; //v[i]存储 i 这个值在哪些整对数编号中出现过
int cnt[N]; //cnt[i] 记录第 i 对数中的两个数被成功匹配了几个。
int b[N],prefix[N];
void solve(){
	cin>>n>>m;
	rep(i,1,n){
		int a,b;
		cin>>a>>b;
		v[a].push_back(i),v[b].push_back(i);
	}
	int tot=0; //当前区间配对上了多少个整对数
	for(int i=1,j=0;i<=m;i++){ //i为左端点，j为右端点
		while(tot<n && j<m){
			++j;
			for(auto x:v[j]){
				if(!cnt[x]) tot++; //之前第 x 个整数对还没被配对上过
				cnt[x]++;
			}
		}
		if(tot==n) b[j-i+1]++,b[m-i+1+1]--; //区间最小个数为j-i+1，最大最大个数为m-i+1
		for(auto x:v[i]){ //因为下一次左端点i就右移了，因此要在下一次计算前将这次左端点的贡献清除
			cnt[x]--;
			if(!cnt[x]) tot--; //如果清除掉这次左端点的贡献后使得第 x 个整数对没被配对了
		}
	}
	rep(i,1,m) prefix[i]=prefix[i-1]+b[i];
	rep(i,1,m) cout<<prefix[i]<<" ";
}
```

---

## 作者：Transparent (赞：1)

### 题意
已知一个整数 $M$ 和 $N$ 对整数对。对所有的 $1 \leq i \leq N$ ，满足条件 $1 \leq A_i \leq B_i \leq M$。

一个序列 $S$ 被叫做“好的序列”当且仅当它满足以下两个条件：

- $S$ 是 $1,2,3,…,M$ 的一个连续的子序列，即可以找到 $1 \leq l \leq r \leq M$ ，使得 $S$ 可以被写作 $l,l+1,…,r$ 。
- 对于所有的 $1 \leq i \leq n$ ， $S$ 中必须含有 $A_i$ 或 $B_i$ ，或者同时含有 $A_i$ 和 $B_i$ 。

定义 $f(k)$ 表示长度为 $k$ 的“好的序列”的数量。
你需要分别求出 $f(1),f(2),…,f(M)$ 的值。

### 题解
若区间 $[L,R]$ 满足条件，则对任意 $1 \leq x \leq L$ ， $R \leq y \leq M$，区间 $[x,y]$ 同样满足条件。

利用这一性质，可以考虑枚举 $1$ 到 $M$ 的每个数作为起点，向后扩大区间，直到当前区间满足条件，此时，对于任意的 $R \leq x \leq M$ ，区间$[L,x]$均满足条件，那么当前起点就会对 $R-L+1$ 到 $M-L+1$ 的答案做出 $1$ 的贡献。

对上述过程进行优化，每次移动起点时，只需要将 $L$ 对应的数移除，如果 $L$ 被某个数对包含且这个数对的另一个数没有被区间包含，就将 $R$ 不断后移直到这个数对的另一个数被包含在区间内。用线段树维护答案，每找到一个合法区间就将区间 $[R-L+1,M-L+1]$ 的答案加一，最后枚举 $1$ 到 $M$ ，依次查询即可得到所有答案。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define MAXN 200001
class Number {
public:
	Number() {
		id=val=0;
	}
	int id,val;
}a[MAXN<<1];
bool operator<(const Number a,const Number b) {
	return a.val<b.val;
}
int n,m,cnt[MAXN],tot;
long long t[MAXN<<2],add[MAXN<<2];
inline void pushup(int k) {
	t[k]=t[k<<1]+t[k<<1|1];
}
inline void _add(int k,int l,int r,long long v) {
	t[k]+=1ll*(r-l+1)*v;
	add[k]+=v;
}
inline void pushdown(int k,int l,int r,int mid) {
	if(add[k]==0) return;
	_add(k<<1,l,mid,add[k]);
	_add(k<<1|1,mid+1,r,add[k]);
	add[k]=0;
}
void modify(int k,int l,int r,int x,int y,long long v) {
	if(x<=l&&r<=y) return _add(k,l,r,v);
	int mid=(l+r)>>1;pushdown(k,l,r,mid);
	if(x<=mid) modify(k<<1,l,mid,x,y,v);
	if(mid<y) modify(k<<1|1,mid+1,r,x,y,v);
	pushup(k);
}
long long query(int k,int l,int r,int x,int y) {
	if(x<=l&&r<=y) return t[k];
	int mid=(l+r)>>1;pushdown(k,l,r,mid);
	long long res=0;
	if(x<=mid) res+=query(k<<1,l,mid,x,y);
	if(mid<y) res+=query(k<<1|1,mid+1,r,x,y);
	return res;
}
int main() {
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) {
		scanf("%d%d",&a[(i<<1)-1].val,&a[i<<1].val);  
		a[(i<<1)-1].id=a[i<<1].id=i;
	}
	sort(a+1,a+n+n+1);
	for(int l=1,r=0,i=1,j=1;l<=m;) {
		while(i<=(n<<1)&&tot<n) { //向右移动R直到区间满足要求 
			++r;
			while(a[i].val==r) {
				++cnt[a[i].id];
				if(cnt[a[i].id]==1) { //如果之前这个数对没有数被区间包含 
					++tot; //令被包含的数对+1 
				}
				++i; 
			}
		}
		if(tot!=n) { //无论如何都满足要求 
			break;
		}
		modify(1,1,m,r-l+1,m-l+1,1); //记录答案 
		while(j<=(n<<1)&&a[j].val==l) { //将L向右移动 
			--cnt[a[j].id]; //有某个数对的数被移除区间 
			if(!cnt[a[j].id]) { //这个数对没有任何数留在区间内 
				--tot;  
			}
			++j;
		}
		++l;
	}
	for(int i=1;i<=m;i++) {
		printf("%lld ",query(1,1,m,i,i)); //依次查询1~m的答案 
	}
	return 0;
}
```

---

## 作者：lyk2333 (赞：0)

# [ABC260E] At Least One - 题解

## 1.题目大意
给定 $m$ 和 $n$ 对整数 $(a_i, b_i)$，要求对于每个 $k$（$1 \leq k \leq m$），计算满足以下条件的连续子数组 $[l, r]$（长度为 $k$）的数量：对于每一对 $(a_i, b_i)$，子数组至少包含 $a_i$ 或 $b_i$ 中的一个。

## 2.解题思路
本题的核心在于高效地统计满足条件的子数组数量。我们可以利用**差分数组**和**贪心思想**来优化计算。
### 注意：
1. **单调性**：如果子数组 $[l, r]$ 满足条件，那么任何包含 $[l, r]$ 的子数组也一定满足条件。
2. **最小区间**：对于每个 $l$，存在一个最小的 $r$ 使得 $[l, r]$ 满足条件，且这个 $r$ 随 $l$ 增加而单调不减。

### 算法步骤
1. **预处理**：对于每对 $(a_i, b_i)$，记录其影响的范围。
2. **差分数组**：通过差分数组高效统计每个 $k$ 对应的满足条件的子数组数量。
3. **后缀和**：利用后缀和计算最终答案。

## code
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int s[200010],a[200010],ans[200010],n,m;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int xx,yy,ss=0;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) {
        scanf("%d%d",&xx,&yy);
        a[1]=max(a[1],xx-1);
        a[xx+1]=max(a[xx+1],yy-xx-1);
        a[yy+1]=max(a[yy+1],m-yy);
    }
    for(int i=1;i<=m;i++) {
        a[i+1]=max(a[i+1],a[i]-1);
    }
    for(int i=1;i<=m;i++) {
        s[a[i]]++;
    }
    for(int i=m;i>=1;i--) {
        ss+=s[i];
        ans[i]=m-i+1-ss;
    }
    for(int i=1;i<=m;i++) {
        printf("%d ",ans[i]);
    }
    return 0;
}

---

## 作者：_qingshu_ (赞：0)

# Solution：

首先存在个显然的性质，如果 $[L,R]$ 合法，那么 $[L,R+x(x\ge 0)]$ 也一定合法，那么想到差分维护。

既然存在上面的性质，那么可以尝试枚举 $L$ 来拆分贡献，先考虑 $L$ 的合法区间，能想到是 $[1,\min\limits_{i=1}^{n}B_i]$，如果超出了这个范围那么一定无解，反之一定存在至少一组解。

继续考虑对于同一个 $L$ 来说，合法的右端点区间是什么，因为合法 $L$ 区间保证会存在至少一组解，那么 $R=m$ 就是一定可行的，所以只需要考虑合法 $R$ 的左端点即可，这里需要分类讨论。

- $A_i<L$

   那么这些点的 $A_i$ 一定是无法满足的，所以均需要满足 $B_i$，假设排序后存在 $x$ 个，那么限制为 $lim1=\max\limits_{i=1}^{x}B_i$。

- $A_i\ge L$

  那么这些点满足 $R\ge A_i$ 即可，所以取得 $A_i$ 最大值，假设排序后存在 $y$ 个，那么限制为 $lim2=\max\limits_{i=n-y+1}^{n}A_i$。

其中满足 $x+y=n$，合并起来限制就是 $\max(lim1,lim2)$。到这里应该随便怎么搞都可以解决这个问题了，比较优秀的可以使用均摊的思想做到 $\mathcal{O}(n)$。


# Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,ans[1200010],lim,tot,Min=INT_MAX;
pair<int,int>a[1200010];
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		cin>>a[i].first>>a[i].second,
		lim=max(lim,a[i].first),Min=min(Min,a[i].second);
	stable_sort(a+1,a+n+1);
	for(int i=1;i<=Min;i++){
		ans[lim-i+1]++;ans[m-i+2]--;
		while(tot<n&&a[tot+1].first==i)
			lim=max(lim,a[++tot].second);
	}for(int i=1;i<=m;i++)cout<<(ans[i]+=ans[i-1])<<" ";
}

```

---

## 作者：wfc284 (赞：0)

若一个区间满足条件，则其起点必然不能大于 $a_i$ 的最小值，终点不能小于 $b_i$ 的最大值。  
然后考虑每个点会造成多少个 $f(i)$ 的更新。  
记 $[1, p_i]$ 为第 $i$ 个点为终点，有 $\forall x \in [1,p_i]$，区间 $[x, i]$ 满足条件。显然 $p_i$ 单调不减，于是考虑双指针。具体见代码。  
时间复杂度都用在排序上了，$O(n \log n)$。
## Code
```cpp
#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define Linf 0x3f3f3f3f3f3f3f3f
#define re register
#define pii pair<int. int>
#define fi first
#define se second
using namespace std;
const int N = 2e5+2;

int n, m;
vector<int> g[N];
int mx, mn = inf;

int diff[N], f[N];

signed main() {
	cin >> n >> m;
	for(re int i = 1, x, y; i <= n; ++i) {
		scanf("%d%d", &x, &y);
		mx = max(mx, x);
		mn = min(mn, y);
		g[x].push_back(y);
	}	//起点不能大于mn，终点不能小于mx
	for(re int i = 1; i <= m; ++i) 
		if(!g[i].empty()) sort(g[i].begin(), g[i].end(), greater<int>());	//倒序排，方便删除
	
	int p = 1;
	for(re int i = mx; i <= m; ++i) {
		while(p < i && p <= mn) {
			while(!g[p].empty() && g[p].back() <= i) g[p].pop_back();
			if(g[p].empty()) ++p;
			else break;
		}
		
		if(p > mn) ++diff[i-mn+1], --diff[i+1];	//区间[1~mn, i]满足条件
		else ++diff[i-p+1], --diff[i+1];	//区间[1~p, i]满足条件
	}
	
	for(re int i = 1; i <= m; ++i) {
		diff[i] += diff[i-1];
		printf("%d ", diff[i]);
	}
	return 0;
}
```

---

## 作者：yqr123YQR (赞：0)

### 分析
题目求 $(l,r)$ 二元组的数量，枚举 $l$ 必不可少，考虑如何确定 $r$ 的数量。

易知，若 $(l,r)$ 合法（$r<m$），$(l,r+1)$ 亦合法。故只需求得当前 $l$ 下最小的合法的 $r$，此时长度在 $r-l+1\sim m-l+1$ 的方案均会多一种。由于是整体输出答案，差分即可。

考虑优化求最小合法 $r$ 的复杂度。当 $l\to l+1$ 时，会产生影响的二元组形如 $(l,x)$（因为区间不再能覆盖其第一项的值），只需读入时处理最大值，更新 $r$ 时取一遍 $\max$。
### 代码
```cpp
//......
int n, m, en, r, a[maxn + 5][2], g[maxn + 5];
ll path[maxn + 5];
int main()
{
	n = read(), en = m = read();
	for(int i = 1; i <= n; i++) a[i][0] = read(), a[i][1] = read();
	for(int i = 1; i <= n; i++)
      	en = min(en, a[i][1]),
  		r = max(r, a[i][0]),
  		g[a[i][0] + 1] = max(g[a[i][0] + 1], a[i][1]);//预处理 l -> l + 1 带来的影响
	for(int i = 1; i <= en; i++)//en 为 l 的上界
	{
		r = max(r, max(i, g[i]));
		path[r - i + 1]++, path[m - i + 1 + 1]--;//差分
	}
	for(int i = 1; i <= m; i++) printf("%lld ", path[i] += path[i - 1]);
	IO::flush();
	return 0;
}
```

---

