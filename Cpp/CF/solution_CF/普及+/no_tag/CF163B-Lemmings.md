# Lemmings

## 题目描述

As you know, lemmings like jumping. For the next spectacular group jump $ n $ lemmings gathered near a high rock with $ k $ comfortable ledges on it. The first ledge is situated at the height of $ h $ meters, the second one is at the height of $ 2h $ meters, and so on (the $ i $ -th ledge is at the height of $ i·h $ meters). The lemmings are going to jump at sunset, and there's not much time left.

Each lemming is characterized by its climbing speed of $ v_{i} $ meters per minute and its weight $ m_{i} $ . This means that the $ i $ -th lemming can climb to the $ j $ -th ledge in ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF163B/30016607ebe88930003ff462753dc7b94c82b700.png) minutes.

To make the jump beautiful, heavier lemmings should jump from higher ledges: if a lemming of weight $ m_{i} $ jumps from ledge $ i $ , and a lemming of weight $ m_{j} $ jumps from ledge $ j $ (for $ i<j $ ), then the inequation $ m_{i}<=m_{j} $ should be fulfilled.

Since there are $ n $ lemmings and only $ k $ ledges ( $ k<=n $ ), the $ k $ lemmings that will take part in the jump need to be chosen. The chosen lemmings should be distributed on the ledges from $ 1 $ to $ k $ , one lemming per ledge. The lemmings are to be arranged in the order of non-decreasing weight with the increasing height of the ledge. In addition, each lemming should have enough time to get to his ledge, that is, the time of his climb should not exceed $ t $ minutes. The lemmings climb to their ledges all at the same time and they do not interfere with each other.

Find the way to arrange the lemmings' jump so that time $ t $ is minimized.

## 说明/提示

Let's consider the first sample case. The fifth lemming (speed 10) gets to the ledge at height 2 in ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF163B/9afdc5b93ef27ce72945708dcc66dfa8da5502ae.png) minutes; the second lemming (speed 2) gets to the ledge at height 4 in 2 minutes; the fourth lemming (speed 2) gets to the ledge at height 6 in 3 minutes. All lemmings manage to occupy their positions in 3 minutes.

## 样例 #1

### 输入

```
5 3 2
1 2 3 2 1
1 2 1 2 10
```

### 输出

```
5 2 4
```

## 样例 #2

### 输入

```
5 3 10
3 4 3 2 1
5 4 3 2 1
```

### 输出

```
4 3 1
```

# 题解

## 作者：汤汤tongtongTOT (赞：2)

对于这道题，我们首先要知道：      
```
1.体重大的老鼠会在体重小的老鼠上方
2.在体积相同的情况下，跑得快的老鼠应该在更上方
3.由于是同时出发，所以老鼠的位置并不很重要，仅有排序的作用
```
于是，我们就可以得出这道题的方法：
```
1.按照体重从大到小排序
2.当体重相同时按照速度从大到小排序
3.二分答案出总时间，然后再判断是否可行
```
注：判断可行与否的条件为：对于每一只老鼠，看它是否满足$j*h/v[i]<mid$   
有$<k$只老鼠满足条件，说明改时间不可行，否则可行      
###  请特别注意： 时间有可能是小数，所以二分中的l,r,mid皆为double类型
同时，这道题的数量级极小，常数却不小，所以特别建议二分答案使用$for$循环的写法：如下所示（代码来自红名大佬[LuoShaoyin](https://www.luogu.com.cn/user/235868)）~~主要是我的代码太丑了QwQ~~
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define int long long
#define double long double
//这里也尽量写成long double比较好
using namespace std;

const int MAXN = 1e5 + 5;
const double eps = 1e-18;
//请二分答案用while的童鞋注意，本题的eps建议设置1e-15一下
int inline read(){
	int x = 0, f = 0; char ch = getchar();
	while(ch < '0' || ch > '9') f ^= (ch == '-'), ch = getchar();
	while(ch >= '0' && ch <= '9') x = x * 10 + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}
//快读板子，不说了
int n, k, h;
struct lem{
	int m, v, id;
	bool operator< (const lem & A) const{
		return m == A.m ? v > A.v : m > A.m;
	}
}a[MAXN];
//结构体
int ans[MAXN], sol[MAXN];
bool check(double t){
	memset(sol, 0, sizeof(sol));
	int i = 1;
	for(int j = k; j; --j){
		bool b = false;
		for(; i <= n; ++i)
			if((double)j * (double)h <= (double)a[i].v * (t + eps)) {
				//化除为乘，写过逆元的童鞋应该都知道这有多重要
				sol[j] = a[i++].id;
				b = true;
				break;
			}
		if(!b) return false;
	}
	return true;
}

signed main(){
	n = read(), k = read(), h = read();
	for(int i = 1; i <= n; ++i) a[i].m = read();
	for(int i = 1; i <= n; ++i) a[i].v = read();
	for(int i = 1; i <= n; ++i) a[i].id = i;
	sort(a + 1, a + n + 1);
	
	double l = 0, r = k * h, mid;//每天一个卡常小技巧，动态区间范围
	for(int cnt = 1; cnt <= 300; ++cnt){
		mid = (l + r) / 2;
		if(check(mid)) r = mid, memcpy(ans, sol, sizeof(ans));
		else l = mid;
	}//在这里，cnt只用遍历300次，精度却可以达到2e-80左右，防止double的精度被卡专用
	for(int i = 1; i <= k; ++i) printf("%lld ", ans[i]);
	//特别注意，本题需要将ans按照重量排序后输出编号
	return 233;
}
```


---

## 作者：pythoner713 (赞：2)

现将所有旅鼠按照体重从小到大排序，然后二分最小时间。

如何check当前二分的时间是否可行？枚举高度$[h,k*h]$，对于每个高度，选择一个体重尽可能小且可以在当前二分时间内爬完的旅鼠。如果不能选到k只旅鼠说明当前时间不可行。

但是由于最小时间有可能不是整数，蒟蒻的我只好二分实数了，被毒瘤的CF出题人卡了好多次...详情请见代码：

```cpp
#include<bits/stdc++.h>
#define ld long double
#define nb 100010
using namespace std;

int n, k, h, cnt, tmp[nb], ans[nb];
ld eps;

struct lemming{
	int v, w, id;
	bool operator < (const lemming &tmp) const{
		return w < tmp.w || (w == tmp.w && v < tmp.v); 
	}	// 将旅鼠按照体重排序
}a[nb];

bool check(ld x){
	// h * j / v <= x
	int now = 1;
	memset(tmp, 0, sizeof(tmp));
	for(int i = 1; i <= n; i++){
		if((ld)h * now <= (x + eps) * (ld)a[i].v){
			tmp[now++] = a[i].id;
		}
	}
	return now > k;
}

int main(){
	cin >> n >> k >> h;
	eps = (n >= 1000 ? 1e-15 : 1e-18);
	// 由于要二分实数，需要考虑精度问题
	// 如果精度低会被毒瘤数据卡，精度太高会超时，于是面向数据编程 
	for(int i = 1; i <= n; i++) a[i].id = i;
	for(int i = 1; i <= n; i++) cin >> a[i].w;
	for(int i = 1; i <= n; i++) cin >> a[i].v;
	sort(a + 1, a + n + 1);
	ld l = 0, r = k * h;
	while(l <= r - eps && cnt++ <= 1000){
		// 如果二分次数太多就终止 
		ld mid = (l + r) / 2;
		if(check(mid)){
			memcpy(ans, tmp, sizeof(ans)); //更新答案 
			r = mid;
		}
		else l = mid;
	}
	for(int i = 1; i <= k; i++) cout << ans[i] << " ";
	return 0;
}
```


---

