# GukiZ hates Boxes

## 题目描述

Professor GukiZ is concerned about making his way to school, because massive piles of boxes are blocking his way.

In total there are $ n $ piles of boxes, arranged in a line, from left to right, $ i $ -th pile ( $ 1<=i<=n $ ) containing $ a_{i} $ boxes. Luckily, $ m $ students are willing to help GukiZ by removing all the boxes from his way. Students are working simultaneously. At time $ 0 $ , all students are located left of the first pile. It takes one second for every student to move from this position to the first pile, and after that, every student must start performing sequence of two possible operations, each taking one second to complete. Possible operations are:

1. If $ i≠n $ , move from pile $ i $ to pile $ i+1 $ ;
2. If pile located at the position of student is not empty, remove one box from it.

GukiZ's students aren't smart at all, so they need you to tell them how to remove boxes before professor comes (he is very impatient man, and doesn't want to wait). They ask you to calculate minumum time $ t $ in seconds for which they can remove all the boxes from GukiZ's way. Note that students can be positioned in any manner after $ t $ seconds, but all the boxes must be removed.

## 说明/提示

First sample: Student will first move to the first pile ( $ 1 $ second), then remove box from first pile ( $ 1 $ second), then move to the second pile ( $ 1 $ second) and finally remove the box from second pile ( $ 1 $ second).

Second sample: One of optimal solutions is to send one student to remove a box from the first pile and a box from the third pile, and send another student to remove a box from the third pile. Overall, $ 5 $ seconds.

Third sample: With a lot of available students, send three of them to remove boxes from the first pile, four of them to remove boxes from the second pile, five of them to remove boxes from the third pile, and four of them to remove boxes from the fourth pile. Process will be over in $ 5 $ seconds, when removing the boxes from the last pile is finished.

## 样例 #1

### 输入

```
2 1
1 1
```

### 输出

```
4
```

## 样例 #2

### 输入

```
3 2
1 0 2
```

### 输出

```
5
```

## 样例 #3

### 输入

```
4 100
3 4 5 4
```

### 输出

```
5
```

# 题解

## 作者：ccrui (赞：6)

## 本题算法：二分+贪心+模拟
#### [直通CF551C](https://www.luogu.com.cn/problem/CF551C)  [博客查看](https://www.luogu.com.cn/blog/ccr666/solution-cf551c)

### 1.时间复杂度

- 如果暴力枚举 $O(n)=n^2$，当 $n=10^9$ 时肯定会爆
 
- 二分法 $O(n)=log_2(n)\times n$ ，
当 $n=10^9$ 时计算结果约是 $31\times10^9$ 

所以用**二分法** ，再把判断函数复杂度减小一点就不会超时了。

### 2.二分

如果 $mid$ 时间内能完成，那么 $mid+1$ 时间内肯定也能完成，如图：
   ![二分图](https://s1.ax1x.com/2022/12/10/zfiai6.png) 
   

### 3.判断函数

用**贪心算法**：要让时间最值，就要让人少走路，多搬箱子。

所以让每一个人搬用全力搬走尽可能多的**末尾**的箱子，还有体力则继续往前推。

**代码如下：**
```cpp
bool check(long long time){
	int last=n;
	for(int i=1;i<=n;i++)b[i]=a[i];
	for(int i=1;i<=m;i++){
		long long tl=time;
		tl-=last;//跑到最后
		while(b[last]<=tl){
			tl-=b[last];
			last--;
			if(last==0)return 1;
		}//取箱子
		b[last]-=tl;//补取
	}
	return 0;
}
```
### 4.你们想要的完整代码：

```cpp
//求管理大大通过
#include<bits/stdc++.h>
using namespace std;
int n,m,a[100005],b[100005];
bool check(long long time){
	int last=n;
	for(int i=1;i<=n;i++)b[i]=a[i];
	for(int i=1;i<=m;i++){
		long long tl=time;
		tl-=last;//跑到最后
		while(b[last]<=tl){
			tl-=b[last];
			last--;
			if(last==0)return 1;
		}//取箱子
		b[last]-=tl;//补取
	}
	return 0;
}//判断函数
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i];
	while(a[n]==0&&n!=0)n--;//去空末尾
	if(n==0){//特判（防止卡常）
		cout<<0;
		return 0;
	}
	long long l=0,r=1000000000000000;//两个边界
	while(l+1<r){
		long long mid=(l+r)>>1;
		if(check(mid))r=mid;
		else l=mid;
	}//二分
	cout<<r;
	return 0;
}
```




---

## 作者：STUDENT00 (赞：3)

**CF** * **2200** 大水题。

初看题目，我们设 $f(x)$ 表示是否可在 $x$ 个单位时间内将箱子全部搬完，则 $f(x)$ 具单调性，故可使用二分求解。

大问题是：

如何判断是否可在 $time$ 个单位时间内将箱子全部搬完？

我们将 $m$ 个人分开考虑，并将每个人的行动抽象为一条平行于 $x$ 轴的线段（后称横线），横线上的某些点会有一条平行于 $y$ 轴的线段（后称竖线），竖线的长度即你对此点 $a$ 值的消耗。

易发现，竖线放在何处贡献均等，故总贡献只在横线长度总和上。

首先，每个人将 $time$ 个单位时间均用去更优。

考虑：对于任意一种分配方案，我们先将其按横线长度升序排列。

那么对于第 $i$ 人与第 $i+1$ 人，如果第 $i$ 人中有竖线，其位置为 $p$；第 $i+1$ 人中也有竖线，其位置为 $q$，并且 $p>q$，那么将第 $i$ 人的位置为 $p$ 的竖线移 $1$ 单位长度至第 $i+1$ 人上，第 $i+1$ 人的位置为 $q$ 的竖线移 $1$ 单位长度至第 $i$ 人上，第 $i$ 人与第 $i+1$ 人总用时不变，并且此操作显然不会更劣。

易得，任意状态均可通过若干次调整到达不可调整状态，并且满足不可调整的状态仅一种，即正确贪心流程：

对于每个人，不断令 $i\leftarrow i+1$，$a_i>0$ 则令 $a_i\leftarrow a_i-1$ 直到 $a_i=0$，重复此操作直到将 $time$ 单位时间消耗完毕。

刚学一个月 C++ 的萌新都会写的 Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100005;
const long long INF=1e18;
typedef long long ll;
int n,m,a[N],b[N];
bool check(ll d){
	memcpy(b,a,sizeof(b));
	for(int i=1,j=1;i<=m;i++){
		ll tmp=d-j+1;
		while(j<=n){
			if(b[j]+1>tmp){
				b[j]-=(tmp-1);
				break;
			}
			tmp-=b[j++]+1;
		}
		if(j==n+1) return 1;	
	}
	return 0;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	while(!a[n]) n--; //特判末尾含若干0的情况，因为末尾的那些0根本不用经过。由于check函数的判定条件为j==n+1，故去此行将出错。
	ll l=0,r=INF;
	ll ans=-1;
	while(l<=r){
		ll mid=l+r>>1;
		if(check(mid)) ans=mid,r=mid-1;
		else l=mid+1;
	}
	printf("%lld",ans);
	return 0;
}

```

---

## 作者：pufanyi (赞：3)

发现正着做比较麻烦，于是考虑二分答案。

如果需要验证的答案为$x$，那我们就让每个人都有$x$秒。

我们考虑让人一个一个来，一个显然的贪心就是让每个人都拿尽量远的箱子。

然后大力模拟即可。

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;

const int maxn = 100005, maxm = 100005;

int aa[maxn];
int now[maxn];
int n, m;

inline bool pan(LL x)
{
	for(int i = 1; i <= n; ++i)
		now[i] = aa[i];
	int noww = n;
	for(int i = 1; i <= m; ++i)
	{
		LL tx = x;
		while(!now[noww] && noww)
			noww--;
		if(!noww)
			return true;
		tx -= noww;
		if(tx < 0)
			return false;
		while(tx >= 0)
		{
			if(now[noww] > tx)
			{
				now[noww] -= tx;
				break;
			}
			else
			{
				tx-= now[noww];
				now[noww] = 0;
				while(!now[noww] && noww)
					noww--;
				if(!noww)
					return true;
			}
		}
	}
	while(!now[noww] && noww)
		noww--;
	return !noww;
}

int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i)
		scanf("%d", &aa[i]);
	LL l = 0, r = 0x3f3f3f3f3f3f3f3f;
	while(l < r)
	{
		LL mid = (l + r) >> 1;
		if(pan(mid))
			r = mid;
		else
			l = mid + 1;
	}
	printf("%I64d\n", l);
	return 0;
}
```

---

## 作者：Light_Star_RPmax_AFO (赞：2)

### 前言

[传送门](https://www.luogu.com.cn/problem/CF551C)

[blog](https://www.luogu.com.cn/blog/JJL0610666/solution-cf551c)

长沙市一中贪心题单 T9。

# 思路

本题解使用了 **贪心，栈，二分**，下面我来详细讲解。

## Part 1

[前置芝士](https://oi.wiki/basic/greedy/)

贪心的结论就是 **少走路，多搬箱，搬最远**。

我们选择一条最长的路，这时候我们肯定先把最远的搬完，不然我们选择这条路便浪费了一段距离。

那么如果我们走完这条路搬完最远处的箱子之后难道又重新回来再搬第二远的吗？答案是否定的，如果你这么想的话，要学会合理分配时间。

**合理分配时间** 便是，在炒菜的时候是可以等烧水的，这里也是一样，我们在来的路上难道不可以先搬完剩下的时间吗？这样是不是就不会浪费任何时间了呢！

## Part 2

[前置芝士](https://oi.wiki/basic/binary/)

如果暴力我们需要有 $O(n^2)$ 的时间复杂度，超时。

这时我们就需要用二分大大缩短时间，到 $O(n \log n)$ 大家可以去算一下是不会超时的。

**科普**：时间复杂度中的 $\log n$ 大多都是 $\log_2 n$。

## Part 3

[前置芝士](https://oi.wiki/ds/stack/)

有了 **贪心** 结论，我们就可以得到越远的越先搬，也就是先进后出。

听到这立马就可以想到数据结构中的栈，先进后出。

我们使用栈保存序号，如果搬完了就弹出。

# AC Code

```
#include <bits/stdc++.h>
#define ll long long
using namespace std;
 
int n,m,a[100010];
stack<int>q;
int sum[100010];
 
bool check(ll mid){
	for(int i = 1;i <= n;i++){
		sum[i] = a[i];
		if(sum[i])q.push(i);//如果本来就没有我们也不需要放入。
	}
	for(int i = 1;i <= m;i++){
		ll time = mid;
		if(q.empty())return 1;//空了就代表搬完了。
		int now = q.top();//我们需要移动到货物所在地，长度便为这些货物的所在地。
		if(time < now)return 0;//如果给的时间都到不了，那么肯定是无法到达的。
		time -= now;//算剩余时间。
		while(time >= 0){//如果还有就可以搬。
			if(sum[now] > time){//如果不能搬完。
				sum[now] -= time;
				break;
			}else{//如果可以搬完就还可以继续帮忙。
				q.pop();
				time -= sum[now];
				sum[now] = 0;
				if(q.empty())return 1;
				now = q.top();
			}
		}
	}
	return q.empty();
}
 
signed main(){
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++){
		scanf("%d",a + i);
	}
	ll l = 0,r = 1e18;
	while(l < r){
		ll mid = (l + r) >> 1;
		if(check(mid))r = mid;
		else l = mid + 1;
	}
	cout<<l;
} 
```



---

## 作者：FANTA5TlC (赞：2)

大家好，我是dyisz

这题二分很好做

1.二分时间

2.判断这个时间能不能搬完

3.如果能，继续缩短时间

思路是这样，上代码

```cpp
#include <bits/stdc++.h> 
using namespace std;
int a[100005];
int l[100005];
int n, m;
bool check(long long x){//判断当时间是x的时候能不能搬完
	for(int i = 1; i <= n; ++i)
		l[i] = a[i];
	int now = n;
	for(int i = 1; i <= m; ++i){
		long long t = x;
		while(!l[now] && now != 0)
			--now;
		if(!now)
			return true;
		t -= now;
		if(t < 0)
			return false;
		while(t >= 0){
			if(l[now] > t){
				l[now] -= t;
				break;
			} else {
				t -= l[now];
				l[now] = 0;
				while(!l[now] && now)
					now--;
				if(!now)
					return true;
			}
		}
	}
	while(!l[now] && now != 0)
		--now;
	return !now;
}
int main(){
	cin >> n >> m;
	for(int i = 1; i <= n; ++i)
		cin >> a[i];
	long long l = 0, r = 1e18;
	while(l < r){//二分
		long long m = (l + r) / 2;
		if(check(m)){
			r = m;
         } else {
			l = m + 1;
         }  
	}
	cout << l << endl;
	return 0;
}
```


---

## 作者：ARIS2_0 (赞：1)

### 思路

本题很容易想到贪心：对于每个时刻，如果人所在的格子有箱子，把其推开，否则向前走一格。

然而这个贪心我不会证，而且实现上也是很困难的，不想 2025 年 D2T1 那样加个 Trick 就好了。

对于这种有 $m$ 个人的问题，**我们考虑将每个人分开讨论**。

考虑如下贪心结论：一个人肯定优先去推**当前局面下最远的那个箱子**，如果那里的箱子推完了，还有多余时间，再去推中间的箱子。

证明：

> 最远的那个箱子，当前的人不推，以后还是要有人去推的。而且走到最远的地方可以**最小化路程上的损耗**，就是说**不会有路程是浪费的**。

有了这个结论，考虑如何应用。发现结论和当前剩余时间相关，那么我们钦定一个时间的话，按照结论进行推箱子的模拟，就能知道这个时间合不合法，二分答案即可。

模拟的时间复杂度是 $O(\max(n,m))$ 的，二分带来的时间复杂度是 $O(\log \sum a_i)$ 的，总时间复杂度 $O(\max(n,m)\log \sum a_i)$。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
constexpr int maxn=1e5+10,inf=1e16;
int n,m,a[maxn],b[maxn];
bool check(int k){
    memcpy(b+1,a+1,sizeof(b[0])*n);
    int z=n;
    while(z>0 and b[z]==0)z--;
    if(z==0)return 1;
    if(k<z)return 0;
    for(int i=1;i<=m;i++){
        int pos=k-z;
        while(z>0 and pos>=b[z]){
            pos-=b[z];
            b[z]=0;
            z--;
        }
        if(z==0)return 1;
        b[z]-=pos;
    }
    return 0;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>a[i];
    int l=0,r=inf,ans=inf;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid))ans=mid,r=mid-1;
        else l=mid+1;
    }
    cout<<ans;
	return 0;
}
/*
g++ -std=c++14 -Wall -Wextra -Wshadow -Wconversion -Wl,--stack=512000000
*/
```

---

## 作者：MuYC (赞：1)

### 这一道题目的考点为二分答案 + 模拟
二分答案我换成了是倍增，因为蒟蒻我怕二分答案写错（害怕二分写错的同学可以跟我一起写倍增啊）。

模拟的时候有一个技巧，就是每次记录一下当前所有物品中第一个没有被搬完的坐标点。
然后大力模拟。

这道题一定要开longlong，写倍增的时初始答案一定要足够大(最好开满longlong)，我这里到了1e17才过。

#### Code:
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,m;
int a[100005],b[100005];
long long ans = 10000110000000000;
int Tw[62] = {1} ;
int F[100005] , R = 0;
int pd(int x)
{
	int flag = 0,nxt = 1;
	for(int i = 1 ; i <= n ; i ++)
	{
		b[i] = a[i];
		if(b[i] == 0)flag ++;
	}
	for(int i = 1 ; i <= m && flag != n; i ++)
	{
		int life = x;
		life -= F[nxt];
		while(b[F[nxt]] <= life && life > 0 && flag < n)
		{
			flag ++,life -= b[F[nxt]],nxt ++;
			life -= (F[nxt] - F[nxt - 1]);
		}
		if(b[F[nxt]] > life && life > 0){
			b[F[nxt]] -= life;
			continue;
		}
	}
	if(flag == n)return 1;
	return 0;
}
void get_ans()
{
	for(int i = 62 ; i >= 0 ; i --)
		if(ans > Tw[i] && pd(ans - Tw[i]) != 0)ans -= Tw[i];
	cout << ans << endl;
}
signed main()
{
	cin >> n >> m;
	for(int i = 1 ; i <= n ; i ++)
	{
		cin >> a[i];
		if(a[i] != 0)R ++ , F[R] = i;
	}
	for(int i = 1 ; i <= 62 ; i ++)
		Tw[i] = Tw[i-1] << 1;
	get_ans();
	return 0;
}
```

---

## 作者：InversionShadow (赞：1)

## CF551C GukiZ hates Boxes 题解

### 题意：

有 $n$个位置，第 $i$ 个位置上有 $a_i$ 个箱子。现在有 $m$ 个人，开始都在 $0$ 位置（即在 $1$ 号位置左边），每一秒钟每个人都可以选择搬走自己位置上的一个箱子或向前走一步（即从位置 $i$ 走到位置 $i+1$）。问最少需要多少时间才可以将箱子全部搬完。

### 思路：

考虑贪心。

$m$ 个人依次考虑，每次肯定先搬走最远的箱子，如果搬完了就把次远的一起搬掉，直到时间用完。

如果暴力肯定超时，这时观察样例。例如样例二，当答案大于等于 $4$ 时，肯定可以，当答案小于 $4$ 时，答案不可以，所以可以发现：

![](https://cdn.luogu.com.cn/upload/image_hosting/zo4fdrhc.png)

正好符合单调性！考虑二分答案。

细节：注意开 ```long long```。

### Code:

```cpp
#include <iostream>

using namespace std;

const int MAXN = 1e6 + 100;

int n, m, a[MAXN], b[MAXN];

bool check(long long x) {
  int last = n;
  for (int i = 1; i <= n; i++) {
    b[i] = a[i];      // 临时数组
  }
  for (int i = 1; i <= m; i++) {
    long long t = x;
    t -= last;       // 时间减少
    while (b[last] <= t) {   // 可以搬完
      t -= b[last];    
      last--;         // 去看次小
      if (last == 0) {   // 如果次小等于零，表示不用搬了
        return 1;
      }
    }
    b[last] -= t;     
  }
  return 0;
}

int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  while (a[n] == 0 && n != 0) {  
    n--;
  }
  if (n == 0) {   // 这里需要特判 n = 0 的情况，防止死循环
    cout << "0";
    return 0;
  }
  long long l = 0, r = 1000000000000000000;  // r 设置成一个极大值，反正二分不会超时
  while (l + 1 < r) {
    long long mid = (l + r) >> 1;
    if (check(mid)) {
      r = mid;
    } else {
      l = mid;
    }
  }
  cout << r << endl;
  return 0;
}
```


---

## 作者：XCDRF_ (赞：0)

# CF551C GukiZ hates Boxes 题解

[原题传送门](https://codeforces.com/problemset/problem/551/C)

[更好的阅读体验](https://www.luogu.com.cn/article/69paoww2)

## 解题思路

本题要求时间最小值，直接维护不好做，考虑二分答案。

既然要保证时间最小，那就要少走路，多搬箱子。所以一个贪心策略就是在时间充足的情况下，把最远的箱子尽量搬完，这样就能让下一个人少走一些路。具体实现可以参考代码。

注意：开始时，最远的箱子不一定在 $n$ 号位置上，而是第一个 $a_i$ 不为 $0$ 的位置上。

## 参考代码

```cpp
#include<iostream>
#define int long long
using namespace std;
const int N=1e5+5;
int n,m,cnt2,mx2;
int a[N],b[N];
bool check(int md){
	int mx=mx2,cnt=cnt2;
	for(int i=1;i<=n;i++) b[i]=a[i];
	for(int i=1;i<=m;i++){
		int x=md;//每人都有mid的时间
		x-=mx;//总路程是确定的
		if(x<0) return 0;
		for(int &j=mx;j;j--){
			if(x>=b[j]){//如果搬完了这个位置的箱子后还有剩余时间，就继续搬
				x-=b[j];
				cnt-=b[j];
				b[j]=0;
			} 
			else{//如果搬不完这个位置的所有箱子，就搬一部分
				b[j]-=x;
				cnt-=x;
				break;
			}
		}
	}
	if(cnt!=0) return 0;//如果没搬完所有箱子，就不行
	return 1;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=n;i;i--){
		cnt2+=a[i];//算箱子总数
		if(!mx2&&a[i]!=0) mx2=i;//求出来第一个有箱子的位置
	}
	int l=1,r=2e14;//右边界稍大一点
	while(l<r){
		int mid=l+r>>1;
		if(check(mid)) r=mid;
		else l=mid+1;
	}
	cout<<l;
	return 0;
}
```

[AC 记录](https://codeforces.com/contest/551/submission/324969329)

---

## 作者：__galaxy_1202__ (赞：0)

## 解题思路：
求推完箱子所需的最短时间，考虑二分。  
考虑贪心，容易发现最优的策略即令每个人推更远的箱子最优。  

接下来撕烤 `check` 函数怎么写。  
基于上面的贪心策略，我们可以枚举每个人，让这个人那当前离他最远且没有被拿完的坐标的箱子，拿到时间不够为止。期间判一下是否拿完即可。

详见代码。
## CODE：

```cpp
#include <iostream>
using namespace std;
typedef long long ll;
int n, m, a[100001], b[100001];
ll ans;
bool check(ll x)
{
	int cur = n;
	for (int i = 1; i <= n; i++) b[i] = a[i];
	for (int i = 1; i <= m; i++)
    {
		ll t = x;
		t -= cur;
		while(b[cur] <= t)
        {
			t -= b[cur--];
			if (cur == 0) return 1;
		}
		b[cur] -= t;
	}
	return 0;
}
int main()
{
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> a[i];
	while (a[n] == 0 && n) --n;
	ll l = 0, r = 1e18;
	while(l <= r)
    {
		ll mid = (l + r) >> 1;
		if (check(mid))
        {
            ans = mid;
            r = mid - 1;
        }
		else l = mid + 1;
	}
	cout << ans;
	return 0;
}

```

---

