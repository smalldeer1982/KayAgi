# DZY Loves FFT

## 题目描述

### 题目背景
*DZY 喜欢快速傅里叶变换，并乐于使用它。*

[快速傅里叶变换](https://oi-wiki.org/math/poly/fft/)是一种计算卷积的算法。如果 $a$，$b$，$c$ 均为下标从 $0$ 到 $n-1$ 的序列，并且 $c_i = \sum_{j=0}^i a_j \times b_{i-j}$，就可以用快速傅里叶变换来计算 $c$。

DZY 把上面这个式子变成了 $c_i = \max_{j=0}^i a_j \times b_{i-j}$。

其中，$a$ 是从 $1$ 到 $n$ 的**排列**，$b$ 是 $01$ 序列，下标从  $0$ 到 $n-1$。

DZY 需要你计算序列 $c$。

但 DZY 很调皮，他提供了一种方法来得到 $a$ 和 $b$。给定三个整数 $n$，$d$，$x$，使用下面的代码生成 $a$ 和 $b$。

```cpp
//x 为 long long 类型
long long getNextX(){
	x=(x*37+10007)%1000000007;
	return x;
}
void initAB(){
	for(int i=0;i<n;i++) a[i]=i+1;
	for(int i=0;i<n;i++) swap(a[i],a[getNextX()%(i+1)]);
	for(int i=0;i<n;i++)
		if(i<d) b[i]=1;
		else b[i]=0;
	for(int i=0;i<n;i++) swap(b[i],b[getNextX()%(i+1)]);
}
```

## 样例 #1

### 输入

```
3 1 1
```

### 输出

```
1
3
2
```

## 样例 #2

### 输入

```
5 4 2
```

### 输出

```
2
2
4
5
5
```

## 样例 #3

### 输入

```
5 4 3
```

### 输出

```
5
5
5
5
4
```

# 题解

## 作者：封禁用户 (赞：7)

### 题意

这题题意已经很明白了，就不解释了 ~~(doge)~~。

这题的数据生成部分又臭又长，就不附上了，就只展示核心代码。

### 暴力

时间复杂度 $O(n^2)$。

核心代码：
```cpp
	n = read();
	F(i,0,n-1) a[i] = read();
	F(i,0,n-1) b[i] = read();	
	F(i,0,n-1)
	{
		int p = 0;
		F(j,0,i) p = max(p,a[i-j]*b[j]);
		printf("%d\n",p);
	}
```

### 优化

如果认真地看题，就可以注意到题目读入方式是一种类似于生成假随机数的方法，所以只要平均时间复杂度合格就可以，不需要考虑最坏情况的时间复杂度。

因为是求最大值，所以可以从后到前枚举最大值进行转移，就能占掉很多位置，剩下的一点点位置，就直接通过暴力的方法转移就行了。

也可以注意到，并不是所有位置都是有效转移，事实上，对于 $b_i=0$ 的情况可以直接跳过，因为并不会影响答案，所以我们只需要对 $b_i=1$ 时记一个 $nxt_i$，表示下一个 $b_i=1$ 的位置。

核心代码：

```cpp
	n = read();
	F(i,0,n-1) a[i] = read();
	int pr = n+1;
	F(i,0,n-1)
		if(read())
		{
			nxt[pr] = i;
			pr = i; 
		}	
	F(i,0,n)
		if(!nxt[i])
			nxt[i] = n+1; 
	F(i,1,n) id[a[i]] = i;
	for(register int i = n;i >= max(0,n-608);--i)
		for(register int j = nxt[n+1];j < n-id[i];j = nxt[j])
			if(!ans[id[i]+j]) 
				ans[id[i]+j] = i;			
	F(i,0,n-1)
	{
		if(!ans[i]) 
			for(register int j = nxt[n+1];j <= i;j = nxt[j])
				ans[i] = max(ans[i],a[i-j]);
		printf("%d\n",ans[i]);
	}
```




 

---

## 作者：jianhe (赞：4)

首先，可以把 $b$ 序列中的所有 $0$ 去掉。

然后，

我们充分发扬人类智慧：

按照题目所给的生成数据方式显然是随机的。

根据数学直觉，对于随机数据，答案肯定不会离 $n$ 太远。

所以我们只取 $n$ 向前的 $50$ 个数来判断能否取到。

若不能取到，则暴力枚举最大值。

这样速度快得飞起，在 $n=100000$ 时都可以在 $233$ms 内卡过。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=1e5+10;
ll n,d,x,ct,a[N],b[N],c[N],p[N],pos[N];
ll getNextX(){
	x=(x*37+10007)%1000000007;
	return x;
}
void initAB(){
	for(int i=0;i<n;i++) a[i]=i+1;
	for(int i=0;i<n;i++) swap(a[i],a[getNextX()%(i+1)]);
	for(int i=0;i<n;i++)
		if(i<d) b[i]=1;
		else b[i]=0;
	for(int i=0;i<n;i++) swap(b[i],b[getNextX()%(i+1)]);
}
int main(){//我们充分发扬人类智慧：
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>d>>x;initAB();//按照题目所给的生成数据方式显然是随机的。
	for(int i=0;i<n;i++){
		pos[a[i]]=i;
		if(b[i]) p[++ct]=i;
	}
	for(int i=0;i<n;i++){
		bool flag=0;
		for(int j=n;j>=max(1ll,n-50);j--)//根据数学直觉，对于随机数据，答案肯定不会离 n 太远。
            if(i-pos[j]>=0&&b[i-pos[j]]){c[i]=j;flag=1;break;}//所以我们只取 n 向前的 50 个数来判断能否取到。
		if(!flag) for(int j=1;j<=ct&&i-p[j]>=0;j++) c[i]=max(c[i],a[i-p[j]]);//若不能取到，则暴力枚举最大值。
	}
	for(int i=0;i<n;i++) cout<<c[i]<<"\n";//这样速度快得飞起，在 n=100000 时都可以在 233ms 内卡过。
	return 0;
}
```
祝大家在 CSP 中发扬人类智慧，摘得 AK！

---

## 作者：fade_away (赞：2)

## Solution

本质上是个数据分治。

- 考虑当 $d$ 很小的时候，我们可以对于每一个位置，直接枚举所有 $b_i=1$ 的 $i$ 来更新答案，时间复杂度： $O(nd)$ 。

- 考虑当 $d$ 很大的时候，一个数能影响很多个位置，所以我们可以从大到小枚举 $a_i$ ，考虑当前的 $a_i$ 对答案序列的贡献，这样直接做还是 $O(nd)$ 的。但是由于数据随机，我们从大到小求出了若干个数的贡献后，答案序列没被求解的位置会很少，剩下的位置我们可以用上一种方法直接每次 $O(d)$ 求答案。

我们把阙值取成 $\sqrt n$ ，可以证明时间复杂度大概是 $O(n\sqrt n)$ 的。

## Code
```cpp
vector<int> V;
int a[MAXN], b[MAXN], id[MAXN], Ans[MAXN], n, d;

void InitAB() { 
// 
}
signed main() {
#ifndef ONLINE_JUDGE
	freopen("a.in", "r", stdin);
#endif
	InitAB();
	for (int i = 0; i < n ; ++ i) if (b[i]) V.PB(i);

	int N = (int)sqrt(n);
	if (d <= N) {
		for (int i = 0; i < n ; ++ i) {
			int mx = 0;
			for (auto v : V) if (v <= i) upmax(mx, a[i - v]);
			print(mx), putc('\n');
		}
		return 0;
	}

	for (int i = 0; i < n ; ++ i) id[a[i]] = i;
	for (int i = n - N; i <= n ; ++ i)
		for (auto v : V) Ans[id[i] + v] = i;
	for (int i = 0; i < n ; ++ i) {
		if (Ans[i]) continue;
		int mx = 0;
		for (auto v : V) if (v <= i) upmax(mx, a[i - v]);
		Ans[i] = mx;
	}
	for (int i = 0; i < n ; ++ i) print(Ans[i]), putc('\n');
	return 0;
}
```


---

## 作者：Fading (赞：1)

正解是暴力可还行
 
为什么不试试可以过的 bitset 大暴力呢？

直接左移，取&，然后暴力遍历就可以了。

时间复杂度$O(\frac {n^2}{\omega}+n)$。

```cpp

#include<bits/stdc++.h>
#define ll long long
#define ljc 998244353
using namespace std;
inline ll read(){
	ll x=0,f=1;char ch=getchar();
	while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
	while (isdigit(ch)){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
	return x*f;
}
bitset<100001> vis,now,cac;
int a[101010],b[101010],n;
ll d,x;
inline ll getNextX() {
    x = (x * 37 + 10007) % 1000000007;
    return x;
}
inline void initAB() {
    for (int i = 0; i < n; i = i + 1){
        a[i] = i + 1;
    }
    for (int i = 0; i < n; i = i + 1){
        swap(a[i], a[getNextX() % (i + 1)]);
    }
    for (int i = 0; i < n; i = i + 1){
        if (i < d)
            b[i] = 1;
        else
            b[i] = 0;
    }
    for (int i = 0; i < n; i = i + 1){
        swap(b[i], b[getNextX() % (i + 1)]);
    }
}
int id[1010101],c[1010101];
inline bool cmp(int aa,int bb){
	return a[aa]>a[bb];
}
int main(){
	n=read(),d=read(),x=read();
	initAB();
	for (int i=0;i<n;i++){
		now[i]=b[i];id[i]=i;vis[i]=1;
	}
	sort(id,id+n,cmp);
	for (int i=0;i<n;i++){
		cac=vis&(now<<id[i]);
		for (int j=cac._Find_first();j!=cac.size();j=cac._Find_next(j)){
			vis[j]=0;c[j]=a[id[i]];	
		}
	}
	for (int i=0;i<n;i++){
		cout<<c[i]<<endl;
	}
	return 0;
}
```

再讲讲正解。

考虑到数据随机，那么我们枚举答案，从$n$枚举到$n-s$。$s$是一个常量。

如果没有可行的答案，那么就暴力从$1\sim n$扫一遍。

---

