# Flower City Fence

## 题目描述

Anya lives in the Flower City. By order of the city mayor, she has to build a fence for herself.

The fence consists of $ n $ planks, each with a height of $ a_i $ meters. According to the order, the heights of the planks must not increase. In other words, it is true that $ a_i \ge a_j $ for all $ i < j $ .

Anya became curious whether her fence is symmetrical with respect to the diagonal. In other words, will she get the same fence if she lays all the planks horizontally in the same order.

For example, for $ n = 5 $ , $ a = [5, 4, 3, 2, 1] $ , the fence is symmetrical. Because if all the planks are laid horizontally, the fence will be $ [5, 4, 3, 2, 1] $ , as shown in the diagram.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1862C/bee85e28c2f6c75c9cfffe7860d8e27020ca6057.png) On the left is the fence $ [5, 4, 3, 2, 1] $ , on the right is the same fence laid horizontally

But for $ n = 3 $ , $ a = [4, 2, 1] $ , the fence is not symmetrical. Because if all the planks are laid horizontally, the fence will be $ [3, 2, 1, 1] $ , as shown in the diagram.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1862C/61240a948afb884e3b78ad7f150c3256a48031f7.png) On the left is the fence $ [4, 2, 1] $ , on the right is the same fence laid horizontally

Help Anya and determine whether her fence is symmetrical.

## 说明/提示

In the first and second test cases of the example, the fence is symmetrical.

In the third test case of the example, the fence is not symmetrical. If the planks are laid horizontally, the fence will be $ [3, 2, 1, 1] $ .

In the fourth test case of the example, the fence is not symmetrical. If the planks are laid horizontally, the fence will be $ [1, 1] $ .

In the fifth and sixth test cases of the example, the fence is symmetrical.

In the seventh test case of the example, the fence is not symmetrical. If the planks are laid horizontally, the fence will be $ [2, 1, 1, 1, 1, 1] $ .

## 样例 #1

### 输入

```
7
5
5 4 3 2 1
3
3 1 1
3
4 2 1
1
2
5
5 3 3 1 1
5
5 5 5 3 3
2
6 1```

### 输出

```
YES
YES
NO
NO
YES
YES
NO```

# 题解

## 作者：One_JuRuo (赞：7)

## 思路

原题中已经告诉了我们一种快速判断的方法，我们可以用这个方法来判断。

观察一下横着摆的方式，第一列的高度为 $a_i\ge 1$ 的个数，第二列的高度为 $a_i\ge 2$ 的个数 $\cdots$。

所以我们只需要逐列判断两种方式的高度是否一样就行了。

因为题目中给定了数组 $a$ 是单调不升的，所以我们可以用一个变量 $j$ 存最后一个 $a_j\ge i$ 的位置，下一次 $i$ 变大了一，就循环找到下一个 $j$ 的位置即可。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[200005],j,flag;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n),j=n,flag=0;//记得j要赋初始值
		for(int i=1;i<=n;++i) scanf("%d",&a[i]);
		for(int i=1;i<=n;++i)
		{
			while(a[j]<i) --j;//找到对应的j
			if(a[i]!=j){flag=1;break;}//如果不满足，则标记并break
		}
		if(flag) printf("NO\n");
		else printf("YES\n");
	}
}
```

---

## 作者：lfxxx (赞：7)

考虑每个木板在水平放置后对每个位置上产生的贡献。

稍微手玩几组样例：

![](https://cdn.luogu.com.cn/upload/image_hosting/2v3lraw7.png?x-oss-process=image/resize,m_lfit,h_340,w_450)

不难发现一个高度为 $h$ 的木板在水平放置后会是位置 $[1,h]$ 上高度增加 $1$。

但是高度最大是 $10^9$ 这该怎么办？

根据上面的结论，只有当最高的木板高度与 $n$ 一致时才有可能相同，因此考虑直接差分维护即可，笔者代码实现为了方便清空直接写了 map 维护差分数组。

```cpp
#include<bits/stdc++.h>
//#define int long long
using namespace std;
const int maxn = 2e5+114;
int n;
map<int,int> a,b; 
void work(){
	a.clear(),b.clear();
	cin>>n;
	int mx=0;
	for(int i=1;i<=n;i++){
		cin>>a[i];	
		mx=max(a[i],mx);
		b[1]++,b[a[i]+1]--; 
	}
	if(mx!=n){
		cout<<"NO\n";
		return ;
	}
	for(int i=1;i<=n;i++) b[i]+=b[i-1];
	for(int i=1;i<=n;i++){
		if(a[i]!=b[i]){
			cout<<"NO\n";
			return ;
		}
	}
	cout<<"YES\n";
}
int T;
int main(){
ios::sync_with_stdio(0);
cin.tie(0);
cout.tie(0);
cin>>T;
while(T--) work();

return 0;
}
```


---

## 作者：Wf_yjqd (赞：5)

题面是非常好的提示，直接模拟这个过程就好了。

------------

发现将所有横过来以后，第 $i$ 个位置为原来的数组中 $\ge i$ 的个数。

显然若值域 $>n$ 肯定不行，否则排序二分求出新数组的每个数即可。

最后对比两个数组是否一样,复杂度 $\operatorname{O}(n\log n)$。

------------

放个代码吧。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+84;
int T,n,a[maxn],b[maxn];
inline bool check(){
    for(int i=1;i<=n;i++)
        if(lower_bound(b+1,b+n+1,i)-b-1!=n-a[i])
            return 0;
    return 1;
}
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
            b[i]=a[i];
        }
        sort(b+1,b+n+1);
        if(b[n]>n){
            puts("NO");
            continue;
        }
        puts(check()?"YES":"NO");
    }
    return 0;
}
```


---

## 作者：Jorisy (赞：2)

我们考虑以左下角为原点建立坐标系，那么“对角线”就是 $y=x$。

首先容易想到，如果存在 $a_i$，那么 $n$ 就要 $\ge a_i$，因为在 $y=x$ 一侧有 $a_i$ 个，那么在另一侧就应当有对应的 $a_i$ 个，而另一侧（右下）最长就是 $n$。

但这还没结束。

如果一个较小的 $a_i$ 堆叠过多也是无解的。

那这个我们可以知道，如果 $a$ 的第 $a_i$ 个是 $<i$ 的，那么也是无解。
```cpp
#include<bits/stdc++.h>
using namespace std;

int n,a[200005];

void sol()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	for(int i=1;i<=n;i++)
	{
		if(a[i]>n||a[a[i]]<i)
		{
			puts("No");
			return;
		}
	}
	puts("Yes");
}

int main()
{
	int t;
	scanf("%d\n",&t);
	while(t--) sol();
	return 0;
}
```

---

## 作者：dyyzy (赞：2)

## 思路

首先我们看到这个图。

![123](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1862C/bee85e28c2f6c75c9cfffe7860d8e27020ca6057.png)

发现一个高度为 $a_i$ 的栅栏翻转之后的状态等价于 $1$ 到 $a_i$ 都加上一层。所以我们可以使用一个数组记录翻转后每层的层数，问题变为：进行若干次区间加 $1$，完成后询问 $1$ 到 $n$ 每一位的值。很容易想到利用差分优化。这样，我们就有了 $a_i \le 2 \times 10^5$ 的做法。

因为 $n \le 2 \times 10^5$，我们很容易发现，当 $a_i > 2 \times 10^5$ 时，答案都是无解，所以正解就呼之欲出了。

## 实现流程

记录一个差分数组 $b$，每读入一个 $a_i$，若其大于 $2 \times 10^5$，直接记录无解，否则将 $ b_1 + 1$，$ b_{a_i+1} - 1 $。最后使用前缀和计算 $b$ 数组，和 $a$ 进行比较即可。

## 代码

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cmath>
#include<map>
#include<set>
#include<queue>
using namespace std;
#define int long long
inline int read(){
	int x=0,flag=1;char ch=getchar();
	while(ch<'0' || ch>'9'){flag=(ch=='-')?-1:1;ch=getchar();}
	while(ch>='0' && ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*flag;
}
const int N=2e5+10;
int a[N],b[N];
signed main(){
	int T;cin>>T;
	while(T--){
		int n;cin>>n;
		b[0]=0;
		bool res=true;
		for(int i=1;i<=n;++i) b[i]=0;
		for(int i=1;i<=n;++i){
			cin>>a[i];
			if(a[i]>200000) res=false;
			if(!res) continue;
			b[1]++;b[a[i]+1]--;
		}
		if(res){
			for(int i=1;i<=n;++i) b[i]+=b[i-1];
			for(int i=1;i<=n;++i) if(b[i]!=a[i]) res=false;
		}
		if(res) cout<<"YES\n";
		else cout<<"NO\n";
	}
}
```


---

## 作者：SamHJD (赞：1)

## [CF1862C Flower City Fence](https://www.luogu.com.cn/problem/CF1862C)

### 题意

给你一个长为 $n$ 的序列，$a_i$ 表示在平面直角坐标系中画一个 $(i-1,0),(i,a_i)$ 的矩形。问你这 $n$ 个矩形拼起来的形状是否根据 $y=x$ 对称。

### 解法

看似简单，却一时想不出怎么优雅解决，不妨重新理解问题的对称条件。

对于第 $i$ 个数 $a_i$，若要对称，第 $j$ 列也要恰好有 $a_i$ 个数，并且从头连续，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/7du2ic0b.png)

我们想从第二个矩形看是否对称，即看蓝色标记的位置是否长度也为 $3$。蓝色标记的矩形数量代表的就是 $a_i\ge2$ 的个数，因为它的 $y$ 坐标是 $2$。

那么问题便转化为，是否对于每一个 $i$，大于等于 $i$ 的 $a_i$ 个数等于 $a_i$。想到树状数组。

具体的，我们在树状数组每一个位置 $a_i$ 上加一，不用担心越界，因为只要有 $a_i$ 大于 $n$ 那么一定是不对称的。然后获取大于等于 $i$ 的数就可以用 $n-sum(i-1)$ 计算出，判断即可。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n,a[N],t[N];
//树状数组
int lowbit(int x){return x&-x;}
void add(int x,int k){for(int i=x;i<=n;i+=lowbit(i)) t[i]+=k;}
int sum(int x){int res=0;for(int i=x;i;i-=lowbit(i)) res+=t[i];return res;}
void solve(){
    scanf("%d",&n);
    for(int i=1;i<=n;++i) scanf("%d",&a[i]);
    for(int i=1;i<=n;++i){
        if(a[i]>n){
            printf("NO\n");
            return;
        }
    }
    memset(t,0,sizeof(t));//多测要清空
    for(int i=1;i<=n;++i) add(a[i],1);
    bool f=0;
    for(int i=1;i<=n;++i){
        if(n-sum(i-1)!=a[i]) f=1;//不对称
    }
    if(f) printf("NO\n");
    else printf("YES\n");
}
int T;
int main(){
    scanf("%d",&T);
    while(T--) solve();
    return 0;
}
```

---

## 作者：Aisaka_Taiga (赞：0)

昨天半夜脑子抽了写了个麻烦的做法。

首先来看这个图：

![](https://cdn.luogu.com.cn/upload/image_hosting/kyjj2c1o.png)

这是样例里 `5 5 5 3 3` 的情况。

我们发现最上面的红色的两个长度为 $3$ 的，竖着放的长度相同的木板数量是等于横着放的最短的木板长度的。

然后看下面红色的部分，就是又加了一段长度相同的木板的数量，然后要等于横着放出现的第二小的木板长度。

棕色的是做了差分后的值，其实不需要，是本人脑子抽了想的。

所以我们直接 $1\sim n$ 扫一遍把元素相同的区间长度放入一个数组，然后再 $n\sim 1$ 扫一遍，把长度去重，然后两个数组一比较，都相同就是输出 `YES`，反之则为 `NO`。

```cpp

#include <bits/stdc++.h>

#define int long long
#define N 1000100

using namespace std;

inline int read(){int f=1,x=0;char ch;do{ch=getchar();if(ch=='-')f=-1;}while(ch<'0'||ch>'9');do{x=x*10+ch-'0';ch=getchar();}while(ch>='0'&&ch<='9');return f*x;}

int T, n, a[N], stk1[N], stk2[N], top1, top2;

signed main()
{
    T = read();
    while(T --)
    {
        int flag = 0, last = 0;
        n = read();
        int t = 1;
        top1 = 0, top2 = 0;
        for(int i = 1; i <= n; i ++) a[i] = read();
        for(int i = 1; i <= n; i ++)
        {
            if(a[i] == last) t ++;
            else stk1[top1 ++] = t, t = 1, last = a[i];
        }
        stk1[top1] = t;
        a[n + 1] = 0;
        for(int i = n; i >= 1; i --)
            if(a[i] - a[i + 1] != 0) stk2[++ top2] = a[i] - a[i + 1];
        if(top1 != top2) flag = 1;
        for(int i = 1; i <= top1; i ++)
            if(stk1[i] != stk2[i]) {flag = 1; break;}
        if(flag == 1) cout << "NO" << '\n';
        else cout << "YES" << '\n';
    }
    return 0;
}
```

---

## 作者：tbdsh (赞：0)

# 题意简述
[更好的阅读体验](/blog/tianbiandeshenghuo11/solution-cf1862c)

[洛谷原题](/problem/cf1862c)

[CodeForces 原题](https://codeforces.com/contest/1862/problem/c)

有 $t$ 组数据。每组数据给定 $n$ 个木板组成的栅栏，高度分别为 $a_1,a_2,\dots,a_n(a_1\ge a_2\ge \dots\ge a_n)$。

现在，请你判断这个栅栏是否是对称的。即原本的栅栏和横向铺设的栅栏是否相同。

如果这个栅栏是对称的，输出 `YES`，否则，输出 `NO`（大小写不敏感）。

# 分析
首先不难发现：如果 $a_i\ne n$，答案一定是 `NO`。

对于其他情况，以样例为例子，我们来观察一下：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1862C/bee85e28c2f6c75c9cfffe7860d8e27020ca6057.png)

可以发现，我们先插入了一个长度为 $5$ 的栅栏，然后是长度为 $4$ 的，再是长度为 $3$、$2$、$1$ 的。

事实上，如果 $a_i\ne a_{i+1}$ 且 $a_j=a_i(j<i)$，我们会插入 $a_i-a{i+1}$ 个长度为 $j$ 的栅栏。

那么，我们就模拟一下，看最后得到的序列和原序列是否相同即可。

时间复杂度：$O(n)$。

空间复杂度：$O(n)$。

# Code
```cpp
#include<bits/stdc++.h>

using namespace std;
const int MAXN = 2e5 + 5;
int n, a[MAXN];
bool cmp(int a, int b){
  return a > b;
}
void Solve(){
  cin >> n;
  for (int i = 1; i <= n; i++){
    cin >> a[i];
  }
  a[n + 1] = 0;
  if (a[1] != n){
    cout << "NO\n";
    return ;
  }
  vector<int> b; 
  for (int i = 1; i <= n; i++){
    while (a[i] == a[i + 1]){
      i++;
    }
    int x = i;
    for (int j = 1; j <= a[i] - a[i + 1]; j++){
      b.push_back(x);
    }
  }
  sort(b.begin(), b.end(), cmp);
  for (int i = 1; i <= n; i++){
    if (a[i] != b[i - 1]){
      cout << "NO\n";
      return ;
    }
  }
  cout << "YES\n";
}
int main(){
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int t;
  cin >> t;
  while (t--){
    Solve();
  }
  return 0;
}
```

---

## 作者：Hyh_111 (赞：0)

## Solution

我们可以发现，如果满足要求，那么竖直放置第 $i$ 行的木板长度为 $a_{n-i+1}$。所以我们只需要算出竖直放置后每行的木板长度即可。

我们可以采用线段树计算每行的木板长度。对于每个 $a_i$，把第 $1$ 到第 $a_i$ 行的木板长度都加上 $1$。最后计算第 $i$ 行木板长度是否和 $a_{n-i+1}$ 相等即可。

## Code

注：为了方便维护，代码中线段树的倒数第 $i$ 个叶结点代表第 $i$ 行。

```cpp
#include <bits/stdc++.h>
using namespace std;
int T;
int n;
int a[200005];

struct SegmentTree
{
    int l,r,sum,laz;
    #define l(p) tree[p].l
    #define r(p) tree[p].r
    #define sum(p) tree[p].sum
    #define laz(p) tree[p].laz
}tree[800005];

void pushup(int p)
{
    sum(p) = sum(p << 1) + sum(p * 2 + 1);
}

void pushdown(int p)
{
	if (laz(p))
	{
		sum(p * 2) += (r(p * 2) - l(p * 2) + 1) * laz(p);
		sum(p * 2 + 1) += (r(p * 2 + 1) - l(p * 2 + 1) + 1) * laz(p);
		laz(p * 2) += laz(p);
		laz(p * 2 + 1) += laz(p);
		laz(p) = 0;
	}
}

void build(int p,int l,int r)
{
	l(p) = l,r(p) = r,laz(p) = 0,sum(p) = 0;
	if (l == r)
		return;
	int mid = l + ((r - l) >> 1);
	build(p * 2,l,mid);
	build(p * 2 + 1,mid + 1,r);
	pushup(p);
}

void add(int p,int l,int r,int x)
{
	if (l <= l(p) && r(p) <= r)
	{
		sum(p) += (r(p) - l(p) + 1) * x;
		laz(p) += x;
		return;
	}
	pushdown(p);
	int mid = l(p) + (r(p) - l(p)) / 2;
	if (l <= mid) add(p * 2,l,r,x);
	if (r > mid) add(p * 2 + 1,l,r,x);
	pushup(p);
	return;
}

int query(int p,int l,int r)
{
	if (l <= l(p) && r(p) <= r)
		return sum(p);
	pushdown(p);
	int mid = l(p) + (r(p) - l(p)) / 2;
	int ans = 0;
	if (l <= mid) ans += query(p * 2,l,r);
	if (r > mid) ans += query(p * 2 + 1,l,r);
	pushup(p);
	return ans;
}

//以上为线段树基本操作

int main()
{
    cin >> T;
    while (T--)
    {
        int n;
        cin >> n;
        build(1,1,n);//记得初始化
        for (int i = 1; i <= n; i++)
            cin >> a[i];
        for (int i = 1; i <= n; i++)
            add(1,1,a[i],1);//区间加1
        for (int i = n; i >= 1; i--)
            if (query(1,i,i) != a[i])//如果不符合条件直接退出循环
            {
                puts("NO");
                goto R;
            }
        puts("YES");
        R:;
    }
    return 0;
}

```

---

## 作者：rickyxrc (赞：0)

本文章遵守知识共享协议 CC-BY-NC-SA，同步发表于洛谷题解区，转载时须在文章的任一位置附上原文链接和作者署名（rickyxrc）。推荐在[我的个人博客](https://blog.rickyxrc.cc)阅读。

## 题面大意

给你一个方格组成的图形，试计算其沿 x 轴翻转后是否和原来一致。

## 解题思路

首先有如下性质：若任意一格高度大于 $n$，则翻转后显然找不到格子和它匹配，所以判断无解。

然后考虑每个柱子的高度，高度为 $h$ 的柱子会对翻转后 $[1,h]$ 的柱子高度贡献 $1$，不难想到前缀和。

```cpp
#include<stdio.h>

#define maxn 200007

int T;
int n,li[maxn],flg,cnt[maxn];

int main(){
	scanf("%d",&T);
	while(T--){
		flg=1;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			cnt[i]=0,
			scanf("%d",li+i);
		
		for(int i=1;i<=n;i++)
			if(li[i] > n){	
				flg = 0;
				break;
			}
		if(!flg){
			puts("NO");
			continue;
		}
		
		for(int i=1;i<=n;i++)
			cnt[1]++,cnt[li[i]+1]--;
		for(int i=1;i<=n;i++)
			cnt[i] += cnt[i-1];
		
		for(int i=1;i<=n;i++)
			if(li[i] != cnt[i]){	
				flg = 0;
				break;
			}
		if(!flg){
			puts("NO");
			continue;
		}
		puts("YES");
	}
	return 0;
}
```


---

## 作者：bryce (赞：0)

## 思路分析
设一个木板高度为 $h$，如果要把这个木板水平放置，其实就是在区间 $[1,h]$ 的高度上增加了 $1$。

但是高度可能会超过 $n$，所以只需要特判一下就行了，剩下的就用差分去维护就行了。
## 代码
```cpp
#include<iostream>

using namespace std;

inline int read(){register int x = 0, f = 1;register char c = getchar();while (c < '0' || c > '9'){if (c == '-') f = -1;c = getchar();}while (c >= '0' && c <= '9'){x = (x << 1) + (x << 3) + (c ^ 48);c = getchar();}return x * f;}
inline void write(int x){if (x < 0) putchar('-'), x = -x;if (x > 9) write(x / 10);putchar(x % 10 + '0');}

const int N = 2e5 + 10;
int T, n;
int a[N], cf[N], maxn;

int main(){
	T = read();
	while (T--){
		n = read(), maxn = 0;
		for (int i = 1; i <= n; i++) a[i] = read(), maxn = max(maxn, a[i]), cf[i] = 0;
		if (maxn > n){
			cout << "NO" << endl;
			continue;
		}
		for (int i = 1; i <= n; i++) cf[1]++, cf[a[i] + 1]--;
		bool f = 0;
		for (int i = 1; i <= n; i++){
			cf[i] += cf[i - 1];
			if (cf[i] != a[i]){
				cout << "NO" << endl;
				f = 1;
				break;
			}
		}
		if (!f) cout << "YES" << endl;
	} 
	return 0;
}
```


---

## 作者：细数繁星 (赞：0)

很有意思的一道题目！

在栅栏横向摆放后，第一个栅栏的高度是多少呢？当然是高度大于等于 $1$ 的栅栏的个数。第二个栅栏的高度是多少呢？当然是高度大于等于 $2$ 的栅栏的个数。第 $i$ 个栅栏的高度是多少呢？当然是高度大于等于 $i$ 的栅栏的个数。

因此，横向摆放后栅栏的个数必定有 $\max a$ 个，如果想让栅栏对称，那么前提条件就是 $\max a$ 必须等于 $n$，所以说题目里的 $a_i\le 10^9$ 是唬人的，我们可以直接将 $a_i$ 的数据范围看做是 $a_i\le n$。

但果这样挨个算的话，复杂度是 $O(tn^2)$，虽然 CF 评测机很强，但是这样也会 TLE，所以接下来考虑优化。

优化的办法是用一个数组 `sum`，`sum[i]` 就表示栅栏 $i$ 横向摆放的高度，再定义一个数组 `dict`，表示数组 $a$ 里有 `dict[i]` 个数为 $i$。

如果一个数大于等于 $k$，那么它必然会大于 $k-1$，$k-2$，所以不难想到，**`sum` 数组是 `dict` 数组的后缀和数组**。

接下来要做的就容易了，如果 `sum != arr`，那肯定不对称了。否则就是对称的。

代码时间到：

```cpp
#include <cstring>
#include <map>
#include <iostream>
using namespace std;

int arr[214514];
int n;
map<int,int> dict;
int sum[214514];

void solve()
{
    memset(sum, 0, sizeof(sum));
    memset(arr, 0, sizeof(arr));
    dict.clear();
    cin >> n;
    int maxest = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
        maxest = max(maxest, arr[i]);
        dict[arr[i]]++;
    }
    if (maxest != n)
    {
        cout << "NO\n";
        return;
    }
    for (int i = n; i >= 1; i--)
    {
        sum[i] = sum[i + 1] + dict[i];
        if (sum[i] != arr[i])
        {
            cout << "NO\n";
            return;
        }
        // cout << dict[i] << ' ';
    }
    cout << "YES\n";

}

int main()
{
    int t;
    cin >> t;
    while (t--) solve();
}
```

---

## 作者：Rain_javalearner (赞：0)

题目说对称的意义是横过来放置也一样，那么我们就横过来放。不难发现横过来放是一个区间修改，将一段范围的高度加一，所以我们直接差分维护即可。

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
 
int t, n, a[200005], p[200005];
 
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		for(int i = 1 ; i<= n ; i++) {
			scanf("%d", a+i);
		}
		if(a[1] > n) {
			puts("NO");
			continue;
		}
		for(int i = 1 ; i<= n ; i++) {
			p[i] = 0;
		}
		for(int i = 1 ; i<= n ; i++) {
			p[1]++, p[a[i]+1]--;
		}
		for(int i = 1 ; i <= n ; i++) {
			p[i] += p[i-1];
		}
		bool F = true;
		for(int i = 1 ; i <= n  ;i++) {
			if(a[i] != p[i]) F = false;
		}
		if(!F) puts("NO");
		else puts("YES");
	}
	return 0;
}
```


---

## 作者：ax_by_c (赞：0)

首先，先判一下底边是否相等。

也就是说如果 $n$ 和 $a_1$ 不相等的话，就已经是不合法的了。

那么现在的值域就变成 $n$ 了。

然后再来思考一个问题。

翻转后的第 $i$ 列的个数是多少？

很显然是 $\sum_{i=1}^n [a_i \ge i]$。

那么用二分或者双指针求一下上面这个东西，并和原先的 $a_i$ 进行比较即可。

核心代码：

```cpp
int n;
int a[N];
int fc(int h)
{
	int res=0;
	int l=1,r=n;
	while(l<=r)
	{
		int mid=l+((r-l)>>1);
		if(a[mid]>=h)
		{
			res=max(res,mid);
			l=mid+1;
		}
		else
		{
			r=mid-1;
		}
	}
	return res;
}
void solve()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	if(n!=a[1])
	{
		puts("NO");
		return ;
	}
	for(int i=1;i<=n;i++)
	{
		if(a[i]!=fc(i))
		{
			puts("NO");
			return ;
		}
	}
	puts("YES");
}
```

---

## 作者：sunkuangzheng (赞：0)

**【题目分析】**

首先注意到如果数组里有大于 $n$ 的数字肯定无解，因为大于 $n$ 的地方会给横轴贡献，导致图案不对称。

现在我们的原数组里所有元素 $\le n$，我们要做的事情等价于对于每个 $a_i$ 给 $1\sim a_i$ 中的 $j$ 的 $b_j \gets b_j+1$。于是你发现差分一下就做完了。

**【代码】**


```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[500005],b[500005];
bool work(){
    cin >> n;int flag = 0;
    for(int i = 1;i <= n;i ++) b[i] = 0;
    for(int i = 1;i <= n;i ++){
        cin >> a[i];
        if(a[i] > n) flag = 1;
        else b[a[i]+1] --;
    }b[1] = n;if(flag) return 0;
    for(int i = 1;i <= n;i ++){
        b[i] += b[i-1];
        if(b[i] != a[i]) return 0;
    }return 1;
}
int main(){
    cin >> t;
    while(t --)
        cout << (work() ? "YES\n" : "NO\n");
}
```

---

