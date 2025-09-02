# Фото на память - 2 (round version)

## 题目描述

许多年过去了，$ n $个朋友在派对相聚。自从上一次聚会，科技已经发生了巨大的进步，所以相机已经有了自拍功能，所以不需要其中的一个朋友站在相机前而因此不能参与合照。
拍照的过程可以按如下方式简化。在照片中，每个朋友占据一块长方形的像素块：站在第$ i $个位置的人占据着宽度为$ w_i $，高度为$ h_i $的像素块。当然，在照相时，每个人都可以躺下来，此时他会占据一个宽度为$ h_i $，高度为$ w_i $的像素块。
整个照片将会有$ W \times H $的大小，$ W $是照片的总宽度，$ H $是照片的总高度。朋友们想确定整张照片的最小的大小。请帮助他们。

## 样例 #1

### 输入

```
3
10 1
20 2
30 3
```

### 输出

```
180
```

## 样例 #2

### 输入

```
3
3 1
2 2
4 3
```

### 输出

```
21
```

## 样例 #3

### 输入

```
1
5 10
```

### 输出

```
50
```

# 题解

## 作者：octal (赞：5)

# 一道纯贪心
## 既然没有题解，我就发一篇

[go to 博客食用](https://www.cnblogs.com/zhouzhihao/p/11216118.html)
------------

这道题主要就是

不能钻牛角尖

题目中的拍照，一个人不能站或趴在另一个人身上（要这样想题目就难了不少）


# 大致思路如下：

枚举高度,算出对应的最小的宽（这里要用到贪心），乘一下，打擂台，就OK了

关于枚举高度，那就从最大值开始递减可以尽量节约时间

由于数据很弱，下面这个弱弱的代码就能AC


```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int w,h;
}a[1050];
int n;
long long ans=2e9;
int main()
{
	cin>>n;
	int max_h=0,min_h=2e9;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i].w>>a[i].h;
		max_h=max(max_h,a[i].h);
		max_h=max(max_h,a[i].w);
		
		min_h=min(min_h,a[i].h);
		min_h=min(min_h,a[i].w);
	}
	
	for(int i=max_h;i>=min_h;i--)
	{
		bool flag=false;
		int w=0;
		for(int j=1;j<=n;j++)
		{
			int maxn=max(a[j].h,a[j].w);
			int minn=min(a[j].h,a[j].w);
			if(minn>i)//两边长都超出此高度,直接break外层循环 
			{
				flag=true;
				break;
			}
			if(maxn>i) w+=maxn;//maxn不能做高,只能加进宽 
			else w+=minn;//两边长都在高度范围内,从贪心的角度,选小的加进去 
		}
		if(flag) break;
		long long t=w*i;
		ans=min(ans,t);
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：tZEROちゃん (赞：0)

本题的困难版本是 [CF529B](https://www.luogu.com.cn/problem/CF529B)。

因为 $n$ 很小，只有 $10^3$，你考虑枚举高度。

对于一个固定的高度，我们考虑贪心的计算宽度。

具体的，我们记 $a_i,b_i$ 分别为小的值和大的值，如果说 $a_i$ 就已经超出固定的高度了，那肯定这个高度就不能选。如果 $b_i$ 还没超过，那你肯定让 $a_i$ 当高，因为这样可以使宽度尽可能小，但是如果 $b_i$ 超过限制了 $a_i$ 没超过，那只能被迫选 $a_i$ 了。

证明是显然的，因为要让面积小，在高度固定情况下，只要让宽度尽可能小就行。那肯定能选短边当宽就选短边。

代码也很好写：

```cpp
#include<bits/stdc++.h>
using namespace std;

#define rep(i, l, r) for(auto i = (l); i <= (r); ++i)
#define per(i, r, l) for(auto i = (r); i >= (l); --i)


const int N = 1e3 + 10;
pair<int, int> p[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n; cin >> n;
  rep (i, 1, n) {
    cin >> p[i].fi >> p[i].se;
    if (p[i].fi > p[i].se) swap(p[i].fi, p[i].se);
  }
  i64 ans = 1e18;
  rep (a, 1, 1008) {
    int b = 0;
    rep (i, 1, n) {
      if (p[i].fi > a) goto skip;
      b += (p[i].se <= a ? p[i].fi : p[i].se);
    }
    ans = min(ans, (i64)a * b);
    skip: ;
  }
  cout << ans << '\n';
  return ~~(0 ^ 0);
}
```

---

## 作者：Underage_potato (赞：0)

## Solution

本题使用贪心解决。

枚举所有可能的 $H_i$，并使得 $W_i$ 最小，然后使用贪心：最大值开始递减枚举高度，算出对应的最小的宽，最后乘出来进行比较就完成了。

时间复杂度 $O(n^2)$ 因为 $1\le n \le 1000$ 所以可以通过本题。

## AC Code:

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
struct edge{
	ll w,h;
};edge e[100010];
ll n,ans=10000000000;
ll maxh,minh=100000000000;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>e[i].w;cin>>e[i].h;
		maxh=max(maxh,max(e[i].w,e[i].h));
		minh=min(minh,min(e[i].w,e[i].h));
	}
	for(int i=maxh;i>=minh;i--){
		ll now=0;
		bool f=1;
		for(int j=1;j<=n;j++){
			ll maxn=max(e[j].w,e[j].h),minn=min(e[j].w,e[j].h);
			if(minn>i){
				f=0;
				break;
			}
			if(maxn>i){
				now+=maxn;
			}
			else{
				now+=minn;
			}
		}
		if(!f){
			break;
		}
		ll t=now*i;
		ans=min(ans,t);
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：water_three (赞：0)

[题目链接](https://www.luogu.com.cn/problem/CF524B)

### 思路：
首先根据题目中的数据范围可以得出大概是 $n^2$ 的时间复杂度。

然后又因为 $n$ 和 $h_i$ 的值都小于 $10^3$，所以我们考虑枚举**可能**的 $H$，在此基础上使得 $W$ 最小，贪心解决。

### 注意：
- 当有任意一个 $i$ 使得 $a_i>H$ 且 $b_i>H$ 时无解。
- 当没有任意一个数等于 $H$ 时无解。
- 当 $a_i$ 和 $b_i$ 中有数大于 $k$ 时，只能将 $W$ 加上最大的数。

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[1001],b[1001];
int main() {
	scanf("%d",&n);
	for(int i=1; i<=n; i++) {
		scanf("%d%d",&a[i],&b[i]);
	}
	if(n==1) {//特判n==1
		cout<<a[1]*b[1]<<endl;
		return 0;
	}
	long long res=100000000000;
	for(int k=1; k<=1001; k++) {
		long long ans=0;
		int pan=0;
		for(int i=1;i<=n&&pan!=-1;i++){
			if(a[i]>k&&b[i]>k)pan=-1;
			if(a[i]==k||b[i]==k)pan=1;
		}
		if(pan==-1||pan==0)continue;//如果无解
		for(int i=1;i<=n;i++){
			if(max(a[i],b[i])<=k)ans+=min(a[i],b[i]);
			else ans+=max(a[i],b[i]);
		}
		 res=min(res,ans*k);
	}
	cout<<res<<endl;
}
```


---

