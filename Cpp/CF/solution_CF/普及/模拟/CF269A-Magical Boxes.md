# Magical Boxes

## 题目描述

Emuskald is a well-known illusionist. One of his trademark tricks involves a set of magical boxes. The essence of the trick is in packing the boxes inside other boxes.

From the top view each magical box looks like a square with side length equal to $ 2^{k} $ ( $ k $ is an integer, $ k>=0 $ ) units. A magical box $ v $ can be put inside a magical box $ u $ , if side length of $ v $ is strictly less than the side length of $ u $ . In particular, Emuskald can put 4 boxes of side length $ 2^{k-1} $ into one box of side length $ 2^{k} $ , or as in the following figure:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF269A/80c511ed150137d08b669bf5e500bfa82c8a8fe8.png)Emuskald is about to go on tour performing around the world, and needs to pack his magical boxes for the trip. He has decided that the best way to pack them would be inside another magical box, but magical boxes are quite expensive to make. Help him find the smallest magical box that can fit all his boxes.

## 说明/提示

Picture explanation. If we have 3 boxes with side length 2 and 5 boxes with side length 1, then we can put all these boxes inside a box with side length 4, for example, as shown in the picture.

In the second test case, we can put all four small boxes into a box with side length 2.

## 样例 #1

### 输入

```
2
0 3
1 5
```

### 输出

```
3
```

## 样例 #2

### 输入

```
1
0 4
```

### 输出

```
1
```

## 样例 #3

### 输入

```
2
1 10
2 2
```

### 输出

```
3
```

# 题解

## 作者：hongshixiaobai (赞：1)

## CF269A

### 思路

读题后容易想到对于每种大小的盒子去看它需要多大的盒子才能全部装下，最后求最大值即可。

虽然到这里就很简单了，但是有一个很恶心的细节：如果只有 $1$ 个盒子，那么你必须再做 $1$ 个盒子去装下它（我也不知道为啥）。

### AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int i,n,a,k,maxn,t,tt;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
	cin>>n;
	for(i = 1;i<=n;++i)
	{
		cin>>k>>a;
		t = k;
        tt = a;
		while(a>1)
		{
			a = ceil(a/4.0);
			t++;
		}
        if(tt == 1)t++;
		maxn = max(maxn,t);
	}
	cout<<maxn;
} 
```

---

## 作者：_int123_ (赞：1)

题目：

## Magical Boxes

### 题意

给你 $n$ 种不同的盒子，每种盒子由两个数据描述——$k,a$，$k$ 表示这个盒子的边长为 $2^k$，$a$ 表示这种盒子有 $a$ 个，盒子里可以放盒子，但同一个盒子里放的盒子不能重叠，但不能放和它一样大的盒子，请找出一个最小的盒子，使得可以在这个盒子里放下所有盒子。

### 思路：

不难看出，一个大箱子里只能装下四个比它小一点的箱子，于是这道题就变成了一个进制转换问题，题目要求满四进一。

### AC 代码：

```cpp
#include<bits/stdc++.h>//万能头文件 
using namespace std;
int n;
int ans;//记录答案 
int maxx;
int k,a;//题目中的 k,a 
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);//加速 
	cin>>n;//输入 
    for(int i=1;i<=n;i++)
    {
		cin>>k>>a;//输入 
        maxx=max(k,maxx);//记录最大的 k 
        int q=0,sum=1;
        while(sum<a) sum*=4,q++;//看看是几倍 
        ans=max(ans,k+q);//记录答案 
    }
    if(ans==maxx) ans++;//大小为 k 的盒子需要一个 k+1 的盒子来装，所以 ans++ 
    cout<<ans;//输出 
    return 0;
}

```

完结撒花！！！

---

## 作者：miraculously (赞：1)

题目大意：

题面有一点点问题，盒子是正方体没有被翻译出来。

分析：

这题可以用贪心，以盒子的边长从小到大考虑，一个大盒子能装四个比正好它小的盒子，统计当前盒子数，如果大盒子能装下小盒子，那么盒子数除以 $4$，否则要多用一个大盒子，盒子数除以 $4$ 再加上 $1$。当盒子数为 $1$ 时看一下当前长度，如果刚好等于最大盒子数长度加一，否则，直接输出长度。

代码如下（有注释）：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct name{
	int x,y;
}bl[100001];
int n,cnt1,cnt2;//cnt1记录当前所需最小长度，cnt2是当前长度所需的最小盒子数
bool cmp(name a,name b)
{
	return a.x<b.x;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	scanf("%d%d",&bl[i].x,&bl[i].y);
	sort(bl+1,bl+n+1,cmp);
	cnt1=bl[1].x;
	cnt2=bl[1].y;//从长度最小开始枚举
	for(int i=2;i<=n;i++)
	{
		if(bl[i].x==cnt1)
		cnt2=cnt2+bl[i].y;
		else
		{
			for(int j=1;j<=bl[i].x-cnt1;j++)
			{
				if(cnt2%4==0)
				cnt2=cnt2/4;//如果刚好被装下
				else
				cnt2=cnt2/4+1;//装不下就加1个盒子
				if(cnt2==1)
				break;
			}
			cnt1=bl[i].x;//更新长度
			cnt2=max(cnt2,bl[i].y);//更新最小所需的盒子数
		}
	}
	while(1)
	{
		if(cnt2==1)
		break;
		if(cnt2%4==0)
		cnt2=cnt2/4;
		else
		cnt2=cnt2/4+1;
		cnt1++;
	}
	if(cnt1==bl[n].x)
	printf("%d",cnt1+1);
	else
	printf("%d",cnt1);
}
```


---

## 作者：baiABC (赞：1)

我们可以对每个不同的 $k$ 分别考虑。设答案边长为 $t$，则可以由面积关系列出这样的式子：
$$2^t\times 2^t \geq 2^k\times 2^k\times a$$
即
$$2^{2t-2k}\geq a$$
于是我们可以找到最小的 $2t-2k$（设为 $x$），则 $t\geq \lceil x/2\rceil+k$。
注意一个盒子不能装下和它一样大的盒子，所以 $t\geq k+1$。

拿到了最优解。
### 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
   int n, ans = 0;
   ios::sync_with_stdio(0);
   cin >> n;
   for(int i = 0; i < n; ++i)
   {
      int a, b, x = 0; cin >> a >> b;
      while((1<<x) < b) ++x;
      ans = max(ans, max(1,(x+1)>>1)+a);
   }
   cout << ans << '\n';
   return 0;
}
```

---

## 作者：RaymondOccam (赞：0)

### 思路

因为 $k$ 一定是整数，所以能装下边长 $2^k$ 的盒子最小边长为 $2^{k+1}$。

边长为 $2^k$ 的盒子中能装下的边长为 $2^{k-1}$ 的盒子数量：

$$
\frac{2^{k}\times 2^{k}}{2^{k-1}\times 2^{k-1}}
$$

$$
= \frac{2^{2k}}{2^{2(k-1)}}
$$

$$
= 4
$$

综上得到思路，对于每个盒子信息的处理：

1. 确定最大的盒子边长 $2^{maxk}$，后面需要用到。
2. 确定一个 $q=\lfloor\log^a_4\rfloor$，表示装下这 $a$ 个盒子所需要的边长 $2^{k+q}$ 中的 $q$。
3. 记录答案 $res\leftarrow \max(res,k+q)$。

需要注意当 $res=maxk$ 时，说明需要一个更大的盒子装下边长为 $2^{maxk}$ 的盒子，$res\leftarrow res+1$ 即可。

### 代码


```cpp
#include <iostream>
int n;
int k, a;
int res, maxk, _log, mul;
int main () {
  std::cin.tie (0) -> sync_with_stdio (false);
  std::cin >> n;
  for (int i = 1; i <= n; i++) {
    mul = 1, _log = 0;
    std::cin >> k >> a;
    while (mul < a) {
      _log++, mul <<= 2;
    }
    maxk = std::max (maxk, k);
    res = std::max (res, k + _log);
  }
  res += not (res ^ maxk);
  std::cout << res;
  return 0;
}
```

---

## 作者：huangrenheluogu (赞：0)

贪心。

记 $(x,k)$ 表示 $x$ 个边长为 $2^k$ 的箱子。

对于 $(x,p),(y,q),p\lt q$，显然是尽量把小箱子装到大箱子里面，如果不可以放，就把 $p$ 摆成 $q$ 的形式。

上面的例子中，$(1,q)$ 是可以装 $(4^{q-p},p)$ 的。

模拟这个过程就可以了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5 + 5;
struct node{
	int x, y;
}a[N];
int n, tmp, ans;
inline bool operator < (node x, node y){
	return x.x < y.x;
}
signed main(){
//	freopen("data.in", "r", stdin);
//	freopen("code.out", "w", stdout);
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%d%d", &a[i].x, &a[i].y);
	}
	sort(a + 1, a + n + 1);
	for(int i = 1; i < n; i++){
		tmp = a[i + 1].x - a[i].x;
		if(tmp >= 16) continue ;
		a[i].y -= (1ll << tmp * 2) * a[i + 1].y;
		if(a[i].y > 0) a[i + 1].y += (a[i].y - 1 >> tmp * 2) + 1;
	}
	ans = a[n].x;
	tmp = 1;
	while((1ll << tmp * 2) < a[n].y) tmp++;
	ans += tmp;
	printf("%d\n", ans);
	return 0;
}
```

---

