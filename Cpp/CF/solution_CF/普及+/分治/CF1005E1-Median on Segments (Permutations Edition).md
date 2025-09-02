# Median on Segments (Permutations Edition)

## 题目描述

#### 题目翻译

给定 $1\sim n$ 的排列 $(1\leq n\leq 2\times 10^5)$，求中位数为 $m$ 的子段个数（子段长度为偶数时，取其第 $\frac k 2$ 项，$k$ 为子段长度）

## 样例 #1

### 输入

```
5 4
2 4 5 3 1
```

### 输出

```
4
```

## 样例 #2

### 输入

```
5 5
1 2 3 4 5
```

### 输出

```
1
```

## 样例 #3

### 输入

```
15 8
1 15 2 14 3 13 4 8 12 5 11 6 10 7 9
```

### 输出

```
48
```

# 题解

## 作者：Phartial (赞：3)

考虑在什么情况下一段区间的中位数是 $m$。

可以发现，如果区间长度是偶数，当且仅当小于等于 $m$ 的数的数量等于大于 $m$ 的数的数量的情况下中位数是 $m$。

如果长度是奇数的话就是小于等于 $m$ 的数的数量比大于 $m$ 的数的数量多 $1$。

写成数学语言如下：

$$
\begin{cases}
a_r-a_{l-1}=b_r-b_{l-1} & \text{if}\ \ r-l+1\equiv 0\pmod 2\\
a_r-a_{l-1}+1=b_r-b_{l-1} & \text{otherwise.}\\
\end{cases}
$$

（$a_i$ 表示前 $i$ 个数中小于等于 $m$ 的数的个数，$b_i$ 表示前 $i$ 个数中大于 $m$ 的数的个数。）

然后随便推一下式子就可以变成这个样子：

$$
\begin{cases}
a_r-b_r=a_{l-1}-b_{l-1} & \text{if}\ \ r-l+1\equiv 0\pmod 2\\
a_r-b_r+1=a_{l-1}-b_{l-1} & \text{otherwise.}\\
\end{cases}
$$

注意到式子左右两边没有关联，所以可以直接用一个 map 存 $a_i-b_i$ 的值出现的个数，然后从左往右枚举 $r$ 就好了。

```cpp
#include <map>
#include <iostream>

using namespace std;
using LL = long long;

const int kN = 2e5 + 1;

int n, m, a[kN], v, s;
LL ans;
map<int, LL> p = {{0, 1}};

int main(){
  cin >> n >> m;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    if (a[i] == m) v = i;
  }
  for (int i = 1; i < v; ++i) {
    ++p[s += (a[i] > m ? -1 : 1)];
  }
  for (int i = v; i <= n; ++i) {
    s += (a[i] > m ? -1 : 1), ans += p[s] + p[s - 1];
  }
  printf("%lld", ans);
  return 0;
}
```

---

## 作者：SoyTony (赞：2)

# 题意
求给定一个 $1\sim n$ **排列**中子段中位数为 $m$ 的个数。（当子段长为偶数时，中间相对靠左的为中位数）
# 思路
既然是排列，根据题面的定义没有重复的元素，于是可以知道当 $m$ 为中位数时，对于一个奇数长的子段，大于等于 $m$ 的个数与小于等于 $m$ 的个数相等；对于一个偶数长的子段，大于等于 $m$ 的个数等于小于等于 $m$ 的个数减 $1$。

设 $cnt1(i),cnt2(i)$ 分别表示 $[1,i]$ 中小于等于和大于等于 $m$ 的个数。

于是，对于奇数长的子段 $[l,r]$，可以写作：
$$cnt1(r)-cnt1(l-1)=cnt2(r)-cnt2(l-1)$$
即：
$$cnt2(r)-cnt1(r)=cnt2(l-1)-cnt1(l-1)$$
同理，对于偶数长的子段 $[l,r]$，可以写作：
$$cnt1(r)-cnt1(l-1)+1=cnt2(r)-cnt2(l-1)$$
即：
$$cnt2(r)-cnt1(r)-1=cnt2(l-1)-cnt1(l-1)$$

这样一来，我们可以先求出 $cnt1$ 和 $cnt2$，从 $[1,n]$ 枚举 $r$，再动态地把这两个信息加入 map 中。要注意的一点是，要区分奇数还是偶数，所以要开两个 map 分类讨论。（这种比较简单粗暴）

此外，$0$ 在 $cnt$ 中对应的实质为 $1$（前缀和统计），因此不要忘记在偶数 map 中加入一个 $0$。
# 码
```cpp
int n,m;
int a[maxn];
int cnt1[maxn],cnt2[maxn];
map<int,int> mp1,mp2;
ll ans;
int main(){
    n=read(),m=read();
    for(int i=1;i<=n;++i){
        a[i]=read();
        if(a[i]<=m) ++cnt1[i];
        if(a[i]>=m) ++cnt2[i];
        cnt1[i]+=cnt1[i-1],cnt2[i]+=cnt2[i-1];
    }
    ++mp2[0];
    for(int i=1;i<=n;++i){
        int x=cnt2[i]-cnt1[i];
        if(i&1){
            ans+=mp1[x-1]+mp2[x];
            ++mp1[x];
        }
        else{
            ans+=mp2[x-1]+mp1[x];
            ++mp2[x];
        }
    }
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：__Deng_Rui_Song__ (赞：1)

~~这么水的一道题居然没有 tj，我来水一发~~

# problem

[传送门](https://www.luogu.com.cn/problem/CF1005E1)

题意很明显，我就不叙述了。

# solution

q1：怎么快速判断一个区间合法呢？

a1：我们让小于等于 $m$ 的设为 $-1$，大于 $m$ 的设为 $1$，首先区间内肯定有 $m$ 才行，让我们考虑 $2$ 种情况：

1. 区间和为 $0$：![](https://cdn.luogu.com.cn/upload/image_hosting/mr4mwlop.png)中位数必然是 $m$

2. 区间和为 $-1$：![](https://cdn.luogu.com.cn/upload/image_hosting/00fnde6w.png)中位数必然也是 $m$

q2：怎么维护区间和呢？

a2：这么煎蛋，前缀和啊！

q3：可是这样做时间复杂度为 $\mathcal{O}(n^2)$ 啊，题目不允许，怎么优化？

a3：用计数数组维护在元素 $m$ 后面前缀和为 $i$ 的数量即可。

# code

```
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int M = 2e5;
int n, m, id, ans, a[200005], pre[200005], cnt[400005];
signed main() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    if (a[i] == m) id = i;// 记录m的位置
    a[i] = (a[i] <= m ? -1 : 1);// 映射
    pre[i] = pre[i - 1] + a[i];// 前缀和
    if (id) cnt[pre[i] + M]++;// 维护计数数组
  }
  for (int i = 0; i < id; i++) ans += cnt[pre[i] + M] + cnt[pre[i] - 1 + M];
  cout << ans;
  return 0;
}
```

[AC 记录](http://vjudge.net/solution/56828685/sUM2HykqfBOvivcruRcT)

---

## 作者：Hoks (赞：1)

## 前言 
[题目传送门](https://www.luogu.com.cn/problem/CF1005E1)，[个人博客](https://www.luogu.com.cn/blog/Hok/solution-cf1005e1)个人博客内食用效果可能不会更佳。

## 题意分析
首先关注到题目要让我们求的是中位数，考虑中位数的性质：

当序列中数的总个数为奇数时，大于他中位数的数和小于中位数的数的个数相同。

当序列中数的总个数为偶数时，有题目条件得，大于他中位数的数和小于中位数的数的个数比多 $1$ 个。

考虑 $dy_i$ 为 $1\sim i$ 大于 $m$ 的数的个数，$xy_i$ 为从 $1\sim i$ 小于 $m$ 的数的个数。

借用前缀和的思想，就可以得到区间 $l\sim r$ 中大于 $m$ 的数的个数即为 $dy_r-dy_{i-1}$，小于 $m$ 的数的个数即为 $xy_r-xy_{i-1}$。

设值为 $m$ 的那个数的位置为 $v$，用 $i$ 遍历 $1\sim n$，考虑用前缀和的方式计算答案总数。将奇数与偶数分类讨论，分别用上面中位数的性质判断。

储存一个 $mp_i$ 表示从中大于 $m$ 的数比小于 $m$ 的数多或者少 $i$ 个的前缀区间个数。

每次碰到符合情况的 $i$，只需加上 $mp_{dy_i-xy_i}$ 即可。

接着给 $mp_{dy_i-xy_i}+1$，反复循环上述操作即可。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,k,s;
int a[200010],xy[200010],dy[200010];
int ans;
map<int,int>mp1,mp2;
int read()
{
    char c=getchar();int x=0;
    while(!isdigit(c)) c=getchar();
    while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return x;
}
signed main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++)
    {
        a[i]=read();
        if(a[i]>=m) dy[i]++;
        if(a[i]<=m) xy[i]++;
        if(a[i]==m) k=i;
        dy[i]+=dy[i-1],xy[i]+=xy[i-1];
    }
    mp2[0]++;
    for(int i=1;i<=n;i++)
    {
        int x=dy[i]-xy[i];
        if(i&1) ans+=mp1[x-1]+mp2[x],mp1[x]++;
        else ans+=mp2[x-1]+mp1[x],mp2[x]++;
    }
    printf("%lld",ans);
    return 0;
}
```

完结撒花！

---

## 作者：zjwwjhy (赞：0)

写在前面：此题中，如果序列长度为偶数，**选**第 $k/2$ 项， $k$ 为子段长度

------------------
#  $Thought$ 

1.这题的重点在于如何快速找到**从 $i$ 开始，大于 $m$ 的数的个数 - 小于 $m$ 的数的个数等于1或0的区间个数**。

2.由于我们只需要知道个数，所以大于 $m$ 的数就直接赋值为 $1$ ，小于 $m$ 的数直接赋值为 $-1$ ，然后我们选择用 $cnt[i]$ 记录从第 $1$ 个数到第 $j$ 个数（ $j$ 大于等于 $m$ 所在的位置）等于 $i$ 的 $j$ 的个数。

3.枚举左端点（不大于 $m$ 所在的位置），这时 $cnt[sum[i]]$ 表示的是从 $i$ 开始，大于 $m$ 的数的个数等于小于 $m$ 的数的个数的区间个数( $sum[i]$ 为前缀和)。

3（附）.为什么呢？有图为证![](https://cdn.luogu.com.cn/upload/image_hosting/k6sxodr6.png)

4.没啦

#  $Code$ 

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define gc getchar
inline ll read(){
	ll x = 0; char ch = gc(); bool positive = 1;
	for (; !isdigit(ch); ch = gc())	if (ch == '-')	positive = 0;
	for (; isdigit(ch); ch = gc())	x = x * 10 + ch - '0';
	return positive ? x : -x;
}
int n,m,nl[200020],cnt[200020],id;
int mp[200020*2];
ll ans;
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		nl[i]=read();
		if(nl[i]==m) id=i;
		if(nl[i]>=m) cnt[i]=cnt[i-1]+1;
		else if(nl[i]<m) cnt[i]=cnt[i-1]-1;
	}
	for(int i=id;i<=n;i++){
		mp[cnt[i]+n]++;
	}
	for(int i=0;i<id;i++){
		ans+=mp[cnt[i]+n+1]+mp[cnt[i]+n+2];
	}
	cout<<ans<<endl;
	return 0;
}
```


---

