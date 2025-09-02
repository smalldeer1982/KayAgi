# Row of Tents

## 题目描述

[problemUrl]: https://atcoder.jp/contests/utpc2020/tasks/utpc2020_a

 UT 大学にはテント列というサークル紹介イベントがあります。長さ $ L $ の道があり、 umg くんは位置 $ 0 $ から位置 $ L $ まで一方通行で歩きます。 umg くんには気力というパラメータがあり、その初期値を $ T $ とします。ここで、$ T $ は整数値とします。 umg くんは、距離 $ 1 $ 歩くごとに、気力が $ T $ 未満である場合は 気力が $ 1 $ 回復します。気力が $ T $ である場合は回復しません。

道上には $ N $ 個のテントがあり、$ i $ 番目のテントは位置 $ X_i $ にあります。 umg くんは $ i $ 番目のテントに着くとサークル勧誘にあい、気力が $ A_i $ 減少します。もしここで気力が $ 0 $ 未満になると、 umg くんはその場で倒れてしまいます。

 umg くんが途中で倒れずに位置 $ L $ までたどり着くのに必要な、気力の初期値 $ T $ の最小値を求めてください。

## 说明/提示

### 制約

- 入力は全て整数である。
- $ 1\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ N\ \lt\ L\ \leq\ 10^9 $
- $ 0\lt\ X_1\ \lt\ X_2\ \lt\ \cdots\ \lt\ X_N\ \lt\ L $
- $ 1\ \leq\ A_i\ \leq\ 10^9\ (1\leq\ i\ \leq\ N) $

### Sample Explanation 1

気力の初期値 $ T=6 $ でスタートした場合は以下のような気力の変動になります。 - $ 1 $ 番目のテントにたどり着いて気力が $ 5 $ 減少し、気力が $ 1 $ になる。 - $ 2 $ 番目のテントにたどり着くまでに気力が $ 3 $ 回復し、気力が $ 4 $ になる。 - $ 2 $ 番目のテントにたどり着いて気力が $ 4 $ 減少し、気力が $ 0 $ になる。 - 位置 $ 7 $ にたどり着くまでに気力が $ 3 $ 回復し、気力 $ 3 $ の状態でテント列を終える。 気力の初期値 $ T=5 $ でスタートすると、$ 2 $ 番目のテントで気力が $ 0 $ 未満になってしまうので、答えは $ 6 $ となります。

## 样例 #1

### 输入

```
2 7
1 5
4 4```

### 输出

```
6```

## 样例 #2

### 输入

```
8 11
2 6
3 10
4 8
5 7
7 7
8 1
9 9
10 2```

### 输出

```
42```

# 题解

## 作者：chl090410 (赞：4)

## The Solution to AT_utpc2020_a Row of Tents

### Description

umg 君从位置 $0$ 走到位置 $L$，其中一些指定点位会让 umg 君气力值减少一个指定的数，其余位置可使他的气力值加 $1$，直到恢复初始气力值。umg 的气力值不能小于 $0$。请求出他的最小初始气力值。

### Solution

本题很容易想到暴力算法：依次枚举可能的气力值，若满足要求则输出当前气力值并退出循环，但这样枚举最坏时间复杂度可达 $2\times10^5\times10^9\times2\times10^5=4\times10^{19}$ 次，明显超时，所以考虑优化。

有经验的人很容易就能想到[二分答案](https://oi-wiki.org/basic/binary/)，在此，我先科普一下二分答案的使用条件：

- 暴力可以得出正解（但通常会超时）

- 序列满足单调性，即一个数前面的数都不合法，后面的都合法，而要求的答案就为这个数。

本题刚好满足以上条件：若 umg 的气力值小于 $T$，他就会寄，否则不会，而要求的答案就是 $T$，而暴力也可以求出 $T$。

所以考虑使用二分优化，我们以 $0$ 为左端点，以最大可能减少的气力值 $2\times10^5\times10^9=2\times10^{14}$ 为右端点，二分查找 $T$，别看右端点很大，但二分的时间复杂度为 $O(\log n)$，而 $\log(2\times10^{14})$ 也才不到 $50$，不会超时。

总时间复杂度 $O(N\times\log(NL))$，大概 $10^7$ 次，能通过。

另外，二分是一个应用广泛的算法（如堆（优先队列）、逆序对（归并排序）、最长不下降子序列等），还希望大家都能掌握。

### AC code

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[500005],b[500005],m,k=1,rs;
int n;
bool zyass(int x){
	int ft=x;
	for(int i=1;i<=n;i++){
		ft=ft+a[i]-a[i-1];	
		if(ft>x) ft=x;
		ft-=b[i];
		if(ft<0) return false;
	}
	return true;
}
int ef(int l,int r){
	while(l<=r){
		int mid=(l+r)/2;
		if(zyass(mid)){
			r=mid-1;
		}else{
			l=mid+1;
		}
	} 
	return l;
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i]>>b[i];
		rs+=b[i];
	}
	cout<<ef(0,rs);
	return 0;
}

---

## 作者：A_grasser (赞：4)

- 可能我的代码与tlxjy的代码有些相似，因为我们是一起学的。

## 题意简化

查找一个最小可以走完全程的初始体力值。

## 需要注意的地方

1. 暴力算法过不了，要用更好的算法。
2. 记得开 `long long` 以防止溢出。

## 解法分析

### 一级解法

直接循环枚举。


```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,l;
long long x[200009],a[200009];
bool ok(long long xx){//判断条件 
	long long now=xx;
	for(int i=1;i<=n;i++){
		now=now+x[i]-x[i-1];
		if(now>xx) now=xx;//大于上限就设为上限 
		now-=a[i];
		if(now<0) return 0;//寄了 
	}
	return 1;
}
int main(){
	cin>>n>>l;
	for(int i=1;i<=n;i++){
		scanf("%d %d",&x[i],&a[i]);
	}
	long long i=0;
	while(1){//无限循环 
		if(ok(i)==1){//找到了答案，结束 
			cout<<i;
			return 0;
		}
		i++;
	}
	return 0;
} 
```
但是很显然，这种做法跟暴力搜索几乎没有区别，都会超时。这只是一级解法，能过掉 `a[i]` 比较小的数据。

### 二级解法

有经验的选手对于这种题目，一眼就知道这道题是一个典型的二分，因为它具有单调性。

#### 前置知识：单调性与二分（可直接跳过）

什么是单调性？举个不恰当的例子，你想把老师气到极限，一旦老师气愤值过了极限你就完了，但没达到极限值你又不满意，就形成了一种很尴尬的局面：你想满足自己，不能比极限值少一点或多一点（你就完了），必须刚好在老师气愤值极限。这就是单调性。

我们试研究这道题的单调性：你的体力值少一点，你就寄在半路上了；你体力值多一点，不满足题目最小值的要求。所以，这道题目有单调性，即可以用二分解决。

那什么是二分？比如你想查找严格单调递增的数组中比某个特定值大的最小数，正常情况直接枚举，如果想更优就可用二分方法。下面是二分的图解（我们并不分析它的实现，只是学习思想）：

![](https://cdn.luogu.com.cn/upload/image_hosting/0bxjwj2n.png)

可以看到，每次都将选择部分分成两份，判断条件，继续查找。

我们就有以下的二分板子：

```cpp
while(l<=r){
	int mid=(l+r)/2;
	if(条件成立){
		ans=mid;
		r=mid-1;
	}
	else l=mid+1;
}
```

这个板子可以解决很多二分问题。

用到二分或它的思想的题其实蛮多的，比如归并排序、快速排序、堆等等。

#### 知识讲解完毕

回到问题，我们发现这道题可以做二分后，就能对一级解法的代码进行修改，只要把：

```cpp
while(1){//无限循环 
		if(ok(i)==1){//找到了答案，结束 
			cout<<i;
			return 0;
		}
		i++;
	}
```

改成：

```cpp
while(l<=r){
		long long mid=(l+r)/2;//计算mid 
		if(ok(mid)==1){//找到了答案（可能不是结果） 
			ans=mid;
			r=mid-1;//将上限往左移 
		}
		else l=mid+1;//将下限往右移 
	}
```

这样的做法效率很高，可以从 $O(n)$ 升级到 $O(\log{n})$ 的时间复杂度。

如果想让你的二分主体更好，可以改成这样：

```cpp
while(l<=r){
	long long mid=l+((r-l)>>1);//计算mid 
	if(ok(mid)==1){//找到了答案（可能不是结果） 
		ans=mid;
		r=mid-1;//将上限往左移
	}
	else l=mid+1;//将下限往右移 
}
```
这样不仅能解决 `mid` 溢出的问题，还能加快运算速度（使用了位运算）。


最后说一句，我比较推荐万能头文件，这样可以省去很多不必要的麻烦。

## 完整代码

```cpp
//已通过 
#include<bits/stdc++.h>
//万能头文件
using namespace std;
long long n,l,sum,ans;
long long x[200009],a[200009];
bool ok(long long xx){//判断条件 
	long long now=xx;
	for(int i=1;i<=n;i++){
		now=now+x[i]-x[i-1];
		if(now>xx) now=xx;//大于上限就设为上限 
		now-=a[i];
		if(now<0) return 0;//寄了 
	}
	return 1;
}
int main(){
	cin>>n>>l;
	for(int i=1;i<=n;i++){
		scanf("%d %d",&x[i],&a[i]);
		sum+=a[i];
	}
	long long l=0,r=sum;
	while(l<=r){
		long long mid=(l+r)/2;//计算mid 
		if(ok(mid)==1){//找到了答案（可能不是结果） 
			ans=mid;
			r=mid-1;//将上限往左移
		}
		else l=mid+1;//将下限往右移 
	}
	cout<<ans;
	return 0;
} 
```

---

## 作者：Big_Dinosaur (赞：2)

这个方法时间复杂度只有 $O(n)$，比二分快。

观察发现，如果遇到一个帐篷时气力小于 $0$ 时，剩余气力设为 $d$，初始气力 $T$ 加上 $-d$，剩余气力为 $0$，可以继续。

因此，只要把 $T$ 设为 $0$，遇到帐篷后气力为负数时，将 $T$ 加上气力的相反数，气力设为 $0$ 即可。

## $\color{#abc222}\text{AC Code}$
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
namespace IO {
	inline int r() {
		int z=1,y=0;
		char t=getchar();
		while(t<'0'||t>'9') {
			if(t=='-')z=-1;
			t=getchar();
		}
		while(t<='9'&&t>='0') {
			y=(y<<1)+(y<<3)+(t^48);
			t=getchar();
		}
		return z*y;
	}
	inline void w_(int x) {
		if(x<0) {
			x=-x;
			putchar('-');
		}
		if(x==0)return;
		w_(x/10);
		putchar(x%10+48);
	}
	inline void wln(int x) {
		if(x==0)putchar('0');
		else w_(x);
		putchar('\n');
	}
}
using namespace IO;
namespace D1n0 {
	int n,l,a[1919810],x[1919810],Ans,P;
	inline void _() {
		n=r(),l=r();
		for(int i=1; i<=n; ++i)x[i]=r(),a[i]=r();
		for(int i=1; i<=n; ++i) {
			P=min(Ans,P+x[i]-x[i-1])-a[i];
			if(P<0)Ans+=abs(P),P=0;
		}
		wln(Ans);
	}
}
signed main() {
	D1n0::_();
}
```
这是最优解了，点个赞吧！

---

## 作者：CultReborn (赞：2)

原题链接：[Row of Tents](https://www.luogu.com.cn/problem/AT_utpc2020_a)

很具有代表性的二分答案题，思路简洁，检查函数好写，适合初学二分答案练手，和 [P2678 跳石头](https://www.luogu.com.cn/problem/P2678) 异曲同工。难度为普及/提高-，黄。

# 题目大意（抽象向）

一个有效长度为 $L$ 数轴上有个 $n$ 坐标，坐标 $x_i$ 有对应的赋值 $a_i$。原点有一个可移动点 $u$，有固定的初始值 $T$，一旦到之前给出的坐标 $x_i$，$T$ 会减去 $a_i$，一旦 $T$ 在某个坐标小于 $0$，则 $T$ 不合法。特别的，当 $u$ 未在之前给出的坐标且 $T$ **小于**初始值时，$T$ 会加且仅加上 $1$。求出最小的合法的 $T$。

# 正解思路（详细向）

不难证明在给出坐标固定的情况下，随着 $T$ 的增加，可行性会变大。或者说，如果 $T_0$ 合法，那么大于 $T_0$ 的所有 $T$ 的取值一定合法；如果 $T_0$ 不合法，那么小于 $T_0$ 的所有 $T$ 的取值一定不合法。答案的规律单调，考虑二分。

二分答案下界为 $0$（没有给定坐标时），上界为 $\sum{a_i}$（给定坐标连在一起时）。二分的检查函数也十分好想，只需要从头到尾扫一遍，如果发现 $T$ 小于 $0$，立刻返回 `false`，否则返回 `true`。要注意当 $T$ 大于等于初始值时一定不可以再加 $1$。

二分复杂度为 $O(\log\sum{a_i})$，扫一遍有效长度复杂度为 $O(n)$ 而不是 $O(L)$，因为可以对两个坐标作差来取得 $T$ 的恢复值。程序总复杂度为 $O(n\log\sum{a_i})$。

分析结束，下面是代码，注意数据范围，要开 `long long`。

# 最终代码（丑陋向）

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int maxn = 200005;
int n,L;
LL l = 0,r = 0; // 二分上下界 
struct node{
  int x,v; // 坐标与赋值 
}a[maxn];
bool check(LL T0){ // 核心代码 2 
  int T = T0;
  for(int i = 1;i <= n;++i){
	int dx = a[i].x - a[i - 1].x;
	if(T + dx > T0) T = T0; 
	// 注意，气力最高只能为初始值 
	else T += dx; // 处理空坐标增值 
	T -= a[i].v; // 处理气力减值 
	if(T < 0) return 0; 
  }
  return 1;
}
int main(){
  scanf("%d %d",&n,&L);
  for(int i = 1;i <= n;i++){
	scanf("%d %d",&a[i].x,&a[i].v);
	r += a[i].v;
  }
  while(l <= r){ //核心代码 1 
	LL mid = (l + r) / 2;
	if(!check(mid)) 
	     l = mid + 1; // 我喜欢这样写 
	else r = mid - 1; // 建议固定模板 
  }
  printf("%d",l);
  return 0;
}
```
---
蒟蒻的第一篇题解，觉得不错就点个赞吧 www

---

## 作者：初雪_matt (赞：2)

## 题意

真实难度：黄

一条路上有 $n$ 个帐篷 $x_i$，每到 $1$ 个帐篷就必须消耗 $y_i$ 的体力，体力每走 $1$ 个单位就会回复 $1$，每当体力回复到你选定的值时，将不会继续回复，问经过所有帐篷并且没有在任何帐篷时体力变为负数的情况下，体力最开始的最小值。

## 思路

考虑二分答案。

此题很明显是个二分套路题，单调性一眼就能看出，我们考虑二分体力最开始的值，判断函数按照题意进行模拟即可，需注意的有一下几点。

- 注意不正常的数据范围，需要 $64$ 位整型变量，二分的边界也要注意。

- 为了保险，两个帐篷地点之间用绝对值的情况下，**最好用```llabs```**。

## 代码

仅放关键部分代码。

```cpp
bool check(int t){
    int res=t;
    for(int i=1;i<=n;i++){//循环n个帐篷
        if(i!=1){//注意边界
            if(res+llabs(a[i].x-a[i-1].x)<=t){//题意模拟
                res+=llabs(a[i].x-a[i-1].x);
            }
            else{
                res+=llabs(t-res);
            }
        }
        res-=a[i].y;//经过每个帐篷所耗体力
        if(res<0){//当体力为负数时，则该mid不行
            return 1;
        }
    }
    return 0;
}
```

---

## 作者：L_Obsession_TO (赞：1)

简单二分题。
### 题意
一条路上 $n$ 个点，每个点有一个值，从零开始走，每到一个点，气力就会减去这个值，没到点时，如果气力没有满，每走一步气力加一，气力小于零就会寄。

## 思路
既然气力没满，一步就加一，不用模拟路的总长，只用模拟 $n$ 个点，直接加上前面点的位置减上一个点的位置。

可知气力最大值就是每个点的值的和，答案就在一到这个和中。
### 做法
二分首先确认答案在一个范围中，把左边界定为最小的可能答案，右边界定为最大的。

每次循环取一个中间值判断，符合要求就更新答案和边界。如果中间值成立，就让右边界等于中间值减一，否则让左边界等于中间值加一。

如果左边界大于等于右边界，说明找到最终答案，退出循环。

函数根据题意写。
#### 注
输入顺序是先位置再气力。

代码中有主食。

```
#include<bits/stdc++.h>
#define int long long	//看数据范围 
using namespace std;
int a[1140514],x[1145014];//开小会RE 
int n,m;
int ans,sum;
bool judge(int s){
	int p=s;		//表示当前气力 
	for(int i=1;i<=n;i++){
		p=p+(x[i]-x[i-1]);		//每走一步气力加一 
		if(p>s)p=s;		//超过就定成最大 
		p-=a[i];			
		if(p<0)return 0;//寄 
	}
	return 1;
}

signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>x[i]>>a[i];
		sum+=a[i];
	}
	int l=0,r=sum;			//右边界定为最大值 
	while(l<=r){		//二分模版 
		int mid=(l+r)/2;
		if(judge(mid)){
			ans=mid;
			r=mid-1;
		}else l=mid+1;
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：fantastic_dream (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_utpc2020_a)

这题是模拟题，看到“体力最小值”很容易想到二分答案。

我们可以模拟人向前行进的过程，每当人的体力小于 $T$，就加上两个帐篷间的距离再减去帐篷带来的损耗，一旦体力小于零就返回。

注意：
- 根据这题的数据范围，要开 long long。
- 人的体力上限就是 $T$，不应多加。
- 注意二分上下界。

AC 代码如下：
```
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int n,len;
ll sum=0,ans;
struct tent{
	int pos,val;
}sz[200005];
bool check(ll t){
	ll now=t,pos=0,cnt=0;
	while(cnt<n){
		pos=sz[++cnt].pos;
		if(now<t)	now+=sz[cnt].pos-sz[cnt-1].pos;
		if(now>t)	now=t;
		now-=sz[cnt].val;
		if(now<0)	return false;
	}
	return true;
}
int main(){
	ios::sync_with_stdio(0);
	cin>>n>>len;
	for(int i=1;i<=n;i++){
		cin>>sz[i].pos>>sz[i].val;
		sum+=sz[i].val;
	}
	sz[0].pos=0,sz[0].val=0;
	ll l=1,h=sum,mid;
	while(l<=h){
		mid=(l+h)>>1;
		if(!check(mid))	l=mid+1;
		else	h=mid-1,ans=mid;
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：awdereye (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_utpc2020_a)

### 解题思路
本题为**二分答案板子**，二分 umg 君的初始气力 $T$。
 - 本题需要开 `long long`，因为本题最大范围需要枚举 $2\times 10 ^ {5}\times 10 ^ {9}$。

### 二分范围
本题毫无疑问左范围 $L=0$ ，右范围等于数组 $A$ 加上最大的距离，即 $\max(X _ {i})$。在每一次模拟 umg 君走路时情况，如果 umg 君寄了，就改左范围让中间值尽可能大，反之改右范围。

### 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,L,x[200005],a[200005];
bool find(long long m){
		long long now=m;//now模拟umg君气力
		for(long long i=1;i<=n;i++){
			now+=x[i];
			now-=x[i-1];
			now>m?now=m:now=now;//now不能超过上限						
			now-=a[i];
			if(now<0){//寄了
				return 0;
			}
		}
		return 1;
}
int main(){
		long long l=0,r=0;
		cin>>n>>L;
		for(long long i=1;i<=n;i++){
			cin>>x[i]>>a[i];
			l=max(x[i],l);
			r+=a[i];
		}
		r++;//计算上限
		l=0;
		long long mid;
		while(l<=r){//二分答案
			mid=(l+r)/2;
			if(find(mid)){
				r=mid-1;
			}
			else{
				l=mid+1;
			} 
		}
		cout<<l;
		return 0;
}


```

---

## 作者：Mortidesperatslav (赞：0)

这道题目是一道二分的板子题，所以会有比较多的二分讲解，二分大神可以跳过。

# 关于二分的讲解

## I.What

我们的第一个问题是，什么是二分？

二分，通常是用来解决三个问题。

1. 有序数列查找数。

2. 答案是最大值。

3. 答案是最小值。

但实际上，答案具有单调性的题目大多都可以二分完成。

对于 2 和 3 的问题，如果你感觉毫无头绪，很可能就是二分。

二分的思想非常容易：每次把区间一分为二，判断应该找哪边。

![](https://cdn.luogu.com.cn/upload/image_hosting/32fanzwc.png)

看上面这张图，$mid$ 就是我们查找的位置，如果要求最大值，如果 $mid$ 满足条件，继续搜蓝色区间，否则搜红色区间；如果求最小值，如果满足条件，搜红色区间，否则求蓝色区间。

那么我们就很容易写出一个模板：

求最小值：

```cpp
int l=mn,r=mx,ans=-1;
while(l<=r){
	int mid=(l+r)>>1;
	if(check(mid))ans=mid,r=mid-1;
	else l=mid+1;
}
cout<<ans;
```

求最大值：

```cpp
int l=mn,r=mx,ans=-1;
while(l<=r){
	int mid=(l+r)>>1;
	if(!check(mid))ans=mid,r=mid-1;
	else l=mid+1;
}
cout<<ans;
```

`mn` 表示下限，`mx` 表示上限。这个模板应该说是最好理解、最不容易出错的模板。墙裂建议竞赛中按照这个模板写。

现在，我们知道了什么是二分，就可以去看下一个问题了。

## II.Why

那么，我们为什么要用二分呢？

我们先说一下，二分能做的题都可以用另外一种方法实现。就是用 `for` 循环从 `mn` 到 `mx` 枚举。

所以二分**本质上是为了优化时间**。

单次二分的时间复杂度为 $O(\log n)$，而正常枚举是 $O(n)$，差距会非常大。很多问题里都要用到这种思想，所以二分是我们必须掌握的基础算法。

乌克兰有一位国际水平的大神 Um_nik 有一句名言：“Stop learning useless algorithm,go and learn using binary search.”这句话的意思是：“停止学习无用的算法，去学习使用二分查找。”这说明了二分是非常重要的。

## III.How

那么，这道题怎么用二分解决呢？

我们用上面的最小值模板，只要写 `check` 函数即可。

~~也就是说上面的两个模板可以过一堆题。~~

代码非常简单，注意要开 `long long`。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k,sum=0;
int c[200005],t[200005];
bool check(int heal){
	int xz=heal,sc=0;
	for(register int i=1;i<=n;i++){
		xz+=(c[i]-sc);
		sc=c[i];
		if(xz>heal)xz=heal;//体力不能超出上限
		xz-=t[i];//消耗体力
		if(xz<0)return 0;//倒下了
	}
	return 1;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>k;
	for(register int i=1;i<=n;i++){
		cin>>c[i]>>t[i];
		sum+=t[i];
	}
	int l=0,r=sum,ans=-1;
	while(l<=r){//二分板子
		int mid=(l+r)>>1;
		if(check(mid))ans=mid,r=mid-1;
		else l=mid+1;
	}
	cout<<ans;
}
```

那么，这篇题解完成了，再推荐几道二分好题。

[P1577](https://www.luogu.com.cn/problem/P1577)

这道题难度黄，是更简单的板子。

[P1873](https://www.luogu.com.cn/problem/P1873)

也是板子，黄。

[P1948](https://www.luogu.com.cn/problem/P1948)

这是一道蓝题，建议学习广搜或者 SPFA 最短路后再做。主要难点是图论。

[P2658](https://www.luogu.com.cn/problem/P2658)

这是一道绿题，需要用到二分和搜索，写起来略显复杂，但确实是一道好题。

[P2249](https://www.luogu.com.cn/problem/P2249)

二分查找模板题，难度橙。

[ABC279D](https://www.luogu.com.cn/problem/AT_abc279_d)

题意翻译简单化了题目，赛时难度会更高（其实可以绿）。比较难想到二分，考验技术，难度黄。

求管理审核通过~这是我的第 $23$ 篇题解，请大家支持~

---

