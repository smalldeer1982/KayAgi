# Eugeny and Play List

## 题目描述

Eugeny 的歌单中有 $n$ 首歌，其中第 $i$ 首歌播放 $c_i$ 次，每次播放持续 $t_i$ 分钟。Eugeny 会按顺序播放这 $n$ 首歌，也就是说，Eugeny 会先播放第 $1$ 首歌 $c_1$ 次，第 $2$ 首歌 $c_2$ 次，依此类推。然后有 $m$ 个问题，每个问题为一个正整数 $v_i$，表示第 $v_i$ 分钟时，Eugeny 在播放第几首歌？

## 样例 #1

### 输入

```
1 2
2 8
1 16
```

### 输出

```
1
1
```

## 样例 #2

### 输入

```
4 9
1 2
2 1
1 1
2 2
1 2 3 4 5 6 7 8 9
```

### 输出

```
1
1
2
2
3
4
4
4
4
```

# 题解

## 作者：IGJHL (赞：2)

~~为什么巨翁这么喜欢快读快写~~

## 题目传送门
[点这里](https://www.luogu.com.cn/problem/CF302B) 

## 题目分析
这个题目其实就是让你判断时间在 $v_i$ 分钟 的时候 Eugeny 正在播放哪首歌，而第i首歌会连续播放  $c_i \times t_i$ 分钟。

## 思路
因为  $1 \le n, m \le 10^5$，所以若是每次都从 $1$ 到 $v_i$ 遍历一遍是显然不可行的，因为时间复杂度已经达到了 $O(m \times \max(c_i \times t_i))$, 所以一定会超时。

然后就可以很容易的想到用一个数组去记住播完每首歌的时间，显而易见，这就是**前缀和**。

接着就可以用一个前缀和数组 $s$， 使 $s[i]  \leftarrow s[i - 1] + c[i] \times t[i]$。

那么，我们接下来只需要输出第一个大于等于 $v_i$ 的数的下标就好了。

那我们的最后一个问题就来了: **用什么来查找呢？**

 **1. 最开始会很容易的想到暴力枚举一遍，从 $s[1]$ 一直遍历到第一个大于等于 $v_i$ 的数，但这时间复杂度并不允许——是  $O(nm)$ 的, 那显然，就需要用另一种方法来查找；**
 
 **2. 因为  $c_i, t_i \ge 1$**
 
**所以，不难看出， $s$ 数组是单调增加的。所以，我们自然就可以想到一种查询方式——二分查找。**

一点小扩充：`lower_bound` 和 `upper_bound` 函数：

假设有一个数组 $a$
1. `lower_bound (a + i, a + j + i, k)` 表示 **在 $a[ i ]$ ~ $a[ j + i - 1 ]$ 中第一个不小于 $k$ 的数指针**，因为数组名也是一种指针，那么， 用 `lower_bound(a + i, a + j + i, k)` 的返回值减去数组名 $a$ ，就能得出那个数的下标了。
1. `upper_bound` 与 `lower_bound` 不只是名字，就连功能也几乎一模一样，但它返回的是：**第一个大于查找值的下标的指针** ，其他都与 `lower_bound` 无差别。

而且，这两个函数的内部实现都使用了二分查找，所以复杂度是毫无问题的

最后，程序的时间复杂度就是 $O(m \log n)$ 啦！


## 代码
```cpp
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1e5 + 5;

int s[N];//前缀和数组 

int n, m;

int main()
{
    cin >> n >> m;
	
    for (int i = 1; i <= n; ++ i)
    {
        int c, t;
        cin >> c >> t;

        s[i] = s[i - 1] + c * t;
    }
    for (int i = 1; i <= m; ++ i)
    {
        int v;
        cin >> v;
        
        cout << lower_bound(s + 1, s + n + 1, v) - s << endl;//二分查找一下
    }
    
    return 0;
}
```

感谢观看

---

## 作者：Galex (赞：1)

## 题意
Eugeny 的歌单中有 $n$ 首歌，其中第 $i$ 首歌播放 $c_i$ 次，每次播放持续 $t_i$ 分钟。Eugeny 会按顺序播放这 $n$ 首歌，也就是说，Eugeny 会先播放第 $1$ 首歌 $c_1$ 次，第 $2$ 首歌 $c_2$ 次，依此类推。然后有 $m$ 个问题，每个问题为一个正整数 $v_i$，表示第 $v_i$ 分钟时，Eugeny 在播放第几首歌？

## 思路

这题数据范围 $n,m \le 10^5$，所以直接对于每个 $v_i$ 从第一首歌开始枚举一定会超时。

那怎么办呢？

首先容易想到的肯定是前缀和。用 $s[i]$ 表示前 $i$ 首歌放完需要的时间。显然 $s[i]=s[i-1]+c[i]\times t[i]$。

于是我们的问题转化为：从 $s[1]$ 到 $s[n]$ 中找到第一个不小于 $v_i$ 的数，输出它的下标。

这应该好理解吧，假设 $s[x]$ 是第一个比 $v_i$ 大的数，那么 $s[x-1] \lt v_i$，也就是说前 $x-1$ 首歌已经放完了。又因为 $s[x]$ 是第一个比 $v_i$ 大的数，那么很明显此时在放第 $x$ 首歌。

那么我们该怎么找呢？

第一想法肯定是从 $s[1]$ 开始枚举，找到第一个 $s[x] \gt v_i$。但这样对于时间复杂度并没有优化，仍然是 $O(nm)$。

但是！我们可以发现一个规律，那就是 $s$ 数组是单调的！那么很明显我们可以用二分查找来把复杂度优化到 $O(m\log n)$，也就可以通过此题啦。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int read() {
	int s = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9')
		f = (ch == '-' ? -1 : 1), ch = getchar();
	while (ch >= '0' && ch <= '9')
		s = (s << 1) + (s << 3) + (ch ^ 48), ch = getchar();
	return s * f;
}

int n, m;
int c[100005], t[100005], s[100005];

signed main() {
	n = read(), m = read();
	for (int i = 1; i <= n; i++){
		c[i] = read(), t[i] = read();
		s[i] = s[i - 1] + c[i] * t[i];
	}
	while (m--){
		int x = read();
		printf("%d\n", lower_bound(s + 1, s + n + 1, x) - s);
	}
	return 0;
}
```


---

## 作者：WaterSky (赞：0)

# [CF302B  Eugeny and Play List](https://www.luogu.com.cn/problem/CF302B)

感谢管理员审核！

### 题面翻译
Eugeny 的歌单中有 $n$ 首歌，其中第 $i$ 首歌播放 $c_i$ 次，每次播放持续 $t_i$ 分钟。Eugeny 会按顺序播放这 $n$ 首歌，也就是说，Eugeny 会先播放第 $1$ 首歌 $c_1$ 次，第 $2$ 首歌 $c_2$ 次，依此类推。然后有 $m$ 个问题，每个问题为一个正整数 $v_i$，表示第 $v_i$ 分钟时，Eugeny 在播放第几首歌？

### 题目做法：
**暴力枚举**？戳！

先看数据范围：$1 \le n,m \le 10^5$，$\displaystyle\sum_{i=1}^n c_i \times t_i \le 10^9$，时间复杂度为 $O(m \times \max(c_i,t_i))$。很明显，肯定会超时。

既然枚举错了，那么就去思考一下二分查找。

首先，应该想到，用一个前缀和数组记录**每一首歌播放完毕的时间**，思考后得知，这个前缀和数组是单调上升，满足使用二分查找的条件。

查找什么呢，自然是查找与 $v_i$ 最符合的播放完毕时间。

剩下的也没什么好讲的，代码如下：
```
#include<bits/stdc++.h>
using namespace std;
long long s[1000005],n,m,c,t,v;
int main()
{
    cin>>n>>m;
	for(int i=1;i<=n;i++) 
    	cin>>c>>t,s[i]=s[i-1]+c*t;
    for(int i=1;i<=m;i++) 
    	cin>>v,cout<<lower_bound(s+1,s+n+1,v)-s<<endl;
    return 0;
}
```

---

## 作者：fuwei123 (赞：0)

这道题一上来我想到的是预处理每个时间所对应的歌的编号，但一看数据范围，$v$ 是 $10^9$，直接 pass 掉这个方案。

接下来我想到了，对于每首歌记录一个结构体 $node$，记录这首歌的开始时间和结束时间，枚举 $i$，直到第 $i$ 首歌的结束时间首次大于 $v$，输出这个 $i$。但是这个做法是 $O(nm)$ 的，过不了。

然后我们注意到，上面这个做法**和开始时间无关**，所以可以直接用一个数组 $a_i$ 记录第 $i$ 首歌的结束时间，显然这个 $a$ 数组满足**单调性**，那么我们就要找到比 $v$ 大的最小的 $a_i$，$i$ 就是答案。这就很显然了，既有**单调性**又有找比 $v$ 大的**最小值**，二分！

我们直接二分查找，找到满足条件的之后更新答案，时间复杂度 $O(m\log{n})$，可以通过此题。

下面是 AC 代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5;
int a[N + 5];
int main(){
	ios::sync_with_stdio(0);
	int n, m;
	cin >> n >> m;
	int now = 0;//记录当前是第几分钟 
	for(int i = 1;i <= n;i++){
		int c, t;
		cin >> c >> t;
		now += c * t;
		a[i] = now;
	}
	for(int i = 1;i <= m;i++){
		int x;
		cin >> x;
		int l = 1, r = n, ans = 0;
		while(l <= r){
			int mid = (l + r) / 2;
			if(a[mid] < x)l = mid + 1;
			else{
				r = mid - 1;
				ans = mid;
			}
		}
		cout << ans << "\n";
	}
	return 0;
}
```


---

## 作者：Hughpig (赞：0)

第 $i$ 首歌长 $t_i$，播放 $c_i$ 次。可以看作长 $t_i\times c_i$，但只播放 $1$ 次。

然后对于查询，我们可以记录每首歌结束播放的时间。

设第 $i$ 首歌的结束播放时间为 $r_i$，可得 $r_i=r_{i-1}+c_i\times t_i$。即第 $i-1$ 首歌播完的时间加上第 $i$ 首歌的播放时间。

因为是按顺序播放每首歌的，所以结束播放时间具有单调性。然后二分查找最小的比 $v_i$ 大的 $r_i$ 即可。

目前题解里还没有手写二分的，我来一篇吧。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,time_[100007],c,t,v;//time_ 对应上文的 r

int search(int val)//二分 
{
	int l=1,r=n,mid,ans;//初始将下界设为 1，上界设为 n
	while(l<=r)
	{
		mid=(l+r)>>1;//检测 (l+r)/2，>>1 和 /2 作用相同
		if(time_[mid]>=val)ans=mid,r=mid-1;//如果大于要找到值就记录答案并修改上界
		else l=mid+1;//否则修改下界
	}
	return ans;
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>c>>t,time_[i]=time_[i-1]+c*t;//记录每首歌的结束时间
    while(m--){
        cin>>v;
        cout<<search(v)<<'\n';//输出查找的答案
    }
}
```

---

## 作者：zhouzihe (赞：0)

## 1 观察题目
观察题目，发现可以用一个 $sum_i$ 来记录第 $i$ 首歌放完时的时间，$sum_i=sum_{i-1}+c_i \times t_i$。接着对于每个提问，我们使用二分查找找出第一首结束时间晚于 $v_i$ 的歌。
## 2 code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long int n,m,c,t,v,sum[100005];
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>c>>t;
		sum[i]=sum[i-1]+c*t;
	}
	for(int i=1;i<=m;i++){
		cin>>v;
		cout<<lower_bound(sum+1,sum+n+1,v)-sum<<endl;
	}
	return 0;
}
```


---

## 作者：_HiKou_ (赞：0)

虽然但是，这道题可以不用二分啊。

大家怎么都在发二分啊 XD

注意到，题目中有 $v$ **保证按升序给出**的表述。

也就是说，**可以不用二分法，用线性就可以得出答案**。

具体思路是，先把每一首歌放的时间用一个数组存起来。因为保证 $v$ 按升序给出，我们完全可以在判断完 $v_i$ 后，不重置而直接开始判断 $v_{i+1}$。这和前缀和的思想类似，即设第 $i-1$ 首歌在 $t_i$ 时刻放完，那么当 $t_i< v_i \le t_i+c_i\times t_i$ 时，$v_i$ 时就在放第 $i$ 首歌。

CODE：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,m,i;
ll pls[114514],v[114514];
int main(){
	scanf("%lld%lld",&n,&m);
	for(i=1;i<=n;i++)
	{
		ll c,t;
		scanf("%lld%lld",&c,&t);
		pls[i]=c*t;//每首歌的时间
	}
	ll now=0,cnt=0;//现在的时间与现在放的歌
	for(i=1;i<=m;i++)scanf("%lld",&v[i]);
	for(i=1;i<=m;i++)
	{
		while(now<v[i])cnt++,now+=pls[cnt];
		printf("%lld\n",cnt);
	}
	return 0;
}
```

注：本题在洛谷 RMJ 修复时在 Codeforces 上交。

---

## 作者：Gaode_Sean (赞：0)

这题是一道二分裸题。

设
 $s_i=\displaystyle\sum_{i=1}^n c_i \times t_i$，于是我们能把题意转化成：求最小的 $i$，满足 $v_j \leq s_i$。

对于此类问题，很显然可以用二分解决。为了减少码量，可以用 `lower_bound()` 函数代替手写二分。


## AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+2;
int n,m,s[N];
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){int c,t;scanf("%d%d",&c,&t);s[i]=s[i-1]+c*t;}
	while(m--){int val;scanf("%d",&val);printf("%lld\n",lower_bound(s+1,s+1+n,val)-s);}
	return 0;
}
```

---

