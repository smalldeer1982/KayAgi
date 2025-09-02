# Permutation Swap

## 题目描述

You are given an unsorted permutation $ p_1, p_2, \ldots, p_n $ . To sort the permutation, you choose a constant $ k $ ( $ k \ge 1 $ ) and do some operations on the permutation. In one operation, you can choose two integers $ i $ , $ j $ ( $ 1 \le j < i \le n $ ) such that $ i - j = k $ , then swap $ p_i $ and $ p_j $ .

What is the maximum value of $ k $ that you can choose to sort the given permutation?

A permutation is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2, 3, 1, 5, 4] $ is a permutation, but $ [1, 2, 2] $ is not a permutation ( $ 2 $ appears twice in the array) and $ [1, 3, 4] $ is also not a permutation ( $ n = 3 $ but there is $ 4 $ in the array).

An unsorted permutation $ p $ is a permutation such that there is at least one position $ i $ that satisfies $ p_i \ne i $ .

## 说明/提示

In the first test case, the maximum value of $ k $ you can choose is $ 1 $ . The operations used to sort the permutation are:

- Swap $ p_2 $ and $ p_1 $ ( $ 2 - 1 = 1 $ ) $ \rightarrow $ $ p = [1, 3, 2] $
- Swap $ p_2 $ and $ p_3 $ ( $ 3 - 2 = 1 $ ) $ \rightarrow $ $ p = [1, 2, 3] $

In the second test case, the maximum value of $ k $ you can choose is $ 2 $ . The operations used to sort the permutation are:

- Swap $ p_3 $ and $ p_1 $ ( $ 3 - 1 = 2 $ ) $ \rightarrow $ $ p = [1, 4, 3, 2] $
- Swap $ p_4 $ and $ p_2 $ ( $ 4 - 2 = 2 $ ) $ \rightarrow $ $ p = [1, 2, 3, 4] $

## 样例 #1

### 输入

```
7
3
3 1 2
4
3 4 1 2
7
4 2 6 7 5 3 1
9
1 6 7 4 9 2 3 8 5
6
1 5 3 4 2 6
10
3 10 5 2 9 6 7 8 1 4
11
1 11 6 4 8 3 7 5 9 10 2```

### 输出

```
1
2
3
4
3
2
3```

# 题解

## 作者：glx123 (赞：1)

# 题目概述：
为一个序列从小变大排序，且只能交换**下标差为 $k$ 的数**，求 $k$ 的最大值。

# 分析：
由于是交换，并不限次数，显然可得：每个数的下标与它的目标位置下标的绝对值的**最小公倍数**即 $k$ 的最大值。

所以，这是一道求最小公倍数的问题。
# 代码：
```c
#include<bits/stdc++.h>
using namespace std;
int gcd(int a,int b){
	return b==0?a:gcd(b,a%b);
}//虽然有库函数，但有的版本不能用，所以手打一个。 
int main(){
	int t;
	scanf("%d",&t);
	int a[100005];
	while(t--){
		int n,ans=0;
		cin>>n;
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			a[i]=abs(a[i]-i);//求绝对差。 
			ans=max(ans,a[i]);//找最大的差。 
		}
		for(int i=1;i<=n;i++){
			ans=gcd(ans,a[i]);//逐个比较，求最大公因数。 
		}
		cout<<ans<<endl;//输出答案。 
	}
	return 0;
}


```
完成！



---

## 作者：Ql001 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1828B)\
[codeforces传送门](https://codeforces.com/problemset/problem/1828/B)
# 题目分析
因为**题意**为找到最大的整数 $k$ 满足可以通过只交换下标差为 $k$ 的元素使排列被**从小到大**排序，所以我们得分别算出**下标差**，再递归求它们的**最大公因数**，最后输出出来。
#  _code_ 
```cpp
#include<bits/stdc++.h>
using namespace std;
int gcd(int a,int b){
	return b==0?a:gcd(b,a%b);//三目运算，实现递归。 
   /*
   等效于：
   if（b==0）{
   		return a;
   }
   else{
   		return gcd(b,a%b);
   }
   */
}
int a[100050],n,ans;
void solve(){
	cin>>n;
	ans=0;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		a[i]=abs(a[i]-i);
		ans=max(ans,a[i]);
	}
	for(int i=1;i<=n;i++){
		ans=gcd(ans,a[i]);//调用函数，最大公因数 
	}
	cout<<ans<<endl;
}
int main(){
	int t=1;
	cin>>t;
	while(t--){
		solve();
	}
	cout<<endl;
	system("pause");
	return 0;
}
```
最后的最后，[AC记录](https://www.luogu.com.cn/record/118478300)

---

## 作者：封禁用户 (赞：0)

## 题目分析
给定一组数，交换下标差为 $k$ 的数组元素，使数组升序排列。最后输出这个下标差。

其实只需算出每一组下标差，算最大公因数即可。最大公因数可以用函数实现。
```
int gcd(int a,int b){
	if(b==0) return a;
	else return gcd(b,a%b);
}
```
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100050],n,ans;//定义 
int gcd(int a,int b){//最大公因数函数 
	if(b==0) return a;
	else return gcd(b,a%b);
}
int main(){
	int t;
	cin>>t;//输入 
	while(t--){
		cin>>n;//输入 
		ans=0;//赋初值 
		for(int i=1;i<=n;i++){
			cin>>a[i];
			a[i]=abs(a[i]-i);
			ans=max(ans,a[i]);
		}
		for(int i=1;i<=n;i++){
			ans=gcd(ans,a[i]);//求最大公因数 
		}
		cout<<ans<<endl;//输出 
	}
	return 0;
}
```

---

## 作者：Terry2011 (赞：0)

# 题目分析
因为本题要求通过只交换下标差为 $k$ 的元素使排列被从小到大排序。

所以，经过样例观察，我们要分别算出下标差，然后用递归求它们的最大公因数，最后输出出来。
# code
```cpp
#include<bits/stdc++.h>
using namespace std;
int gcd(int a,int b){
	return b==0?a:gcd(b,a%b);//三目运算，实现递归。 
}
int a[100050],n,ans;
void solve(){
	cin>>n;
	ans=0;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		a[i]=abs(a[i]-i);
		ans=max(ans,a[i]);
	}
	for(int i=1;i<=n;i++){
		ans=gcd(ans,a[i]);//调用函数，最大公因数 
	}
	cout<<ans<<endl;
}
int main(){
	int t=1;
	cin>>t;
	while(t--){
		solve();
	}
	return 0;
}  
```

---

## 作者：zzy0618 (赞：0)

[题目链接](https://www.luogu.com.cn/problem/CF1828B)

#### 解题思路

要注意，这里是一个**排列**。一个升序的排列能够满足 $p_i=i$。

所以对于每个 $p_i$，当 $p_i$ 想要从下标为 $i$ 的位置移动到下标为 $p_i$ 的位置的时候，$k$ 的值一定要是 $|p_i-i|$ 的因数。共有 $n$ 个数，那么满足要求 $k$ 的最大值就是 $\gcd^{n}_{i=1} |p_i-i|$。

这里的 $\gcd$ 直接使用 C++ 内置的 ```__gcd``` 即可。

#### 完整代码

记得使用较快的读入方式。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100005;
int t,n,a[N];
signed main(){
	register int i,j,ans;
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(i=1;i<=n;i++)
			scanf("%d",a+i);
		ans=a[1]-1;//要初始一下
		for(i=2;i<=n;i++)
			ans=__gcd(ans,abs(a[i]-i));
		printf("%d\n",ans);
	}
	return 0;
}

```

---

## 作者：arrow_king (赞：0)

# 题意

给你一个长度为 $n$ 的未排序的排列。找到最大的整数 $k$ 满足可以通过只交换**下标差为 $k$** 的元素使排列被从小到大排序。

# 思路

*之前有一道很相似的题，问你可不可以通过只交换下标差为 $k$ 的元素使排列被从小到大排序，其中 $k$ 为常数。*（题外话）

这道题中要求出这个 $k$。首先，我们可以发现对于一个给定的 $k$，$a_{i},a_{i+k},\dots,a_{i+k\lfloor\frac{n-i}{k}\rfloor}\quad(1\le i\le k)$ 这 $\left\lfloor\dfrac{n}{k}\right\rfloor$ 个元素是可以互换位置的，因为任意两个相邻元素都可以两两互换。

如果我现在想把位于 $i$ 的元素挪到 $j$ 位置上去，那么 $k$ 一定可以整除 $\left\vert j-i\right\vert$。

那么思路就很明显了，枚举每个下标 $i$，对于 $p_i$，如果 $p_i\not=i$，那么它的位置就不对，要挪到位置 $p_i$ 上去，那么 $k$ 是 $|p_i-i|$ 的因数。

因为找到最大的 $k$，所以 $k$ 就是对于每一个 $i$ 使得 $p_i\not=i$，$|p_i-i|$ 的最大公因数。

# 代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
#define ll long long
#define il inline
il ll read() {
	ll x=0,f=1;char c=getchar();
	while(c<'0'||c>'9') {if(c=='-') {f=-1;} c=getchar();}
	while(c>='0'&&c<='9') {x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
int t,n;
int a[200005];
il int gcd(int x,int y) {
	if(y==0) return x;
	return gcd(y,x%y);
}
il int Abs(int x) {
	return x>=0?x:-x;
}
int main() {
	t=read();
	while(t--) {
		n=read();
		for(int i=1;i<=n;i++) a[i]=read();
		int ans=0;
		for(int i=1;i<=n;i++) {
			int tmp=Abs(a[i]-i);
			if(ans==0) ans=tmp;
			else if(tmp!=0) ans=gcd(ans,tmp);
		}
		printf("%lld\n",ans);
	}
	return 0;
}

```

---

## 作者：robinyqc (赞：0)

讲一个赛时写的离谱做法。话先说在前面：复杂度 $O(n\sqrt n \log n)$。

### 题意简述

给定一个长度为 $n$ 的排列 $p$，且满足 $\exists i\in[1,n],p_i\neq i$。你需要选定一个正整数 $k$，并进行以下操作若干次：选择两个整数 $i,j\in[1,n],|i-j|=k$，交换 $p_i,p_j$。求能够让排列升序的最大的 $k$。


### 解题思路

我们发现如果固定 $k$，那么可以**互相交换**的下标组成的集合 $S$ 是模 $k$ 的一个同余类的子集，即每一个下标模 $k$ 都是相等的。最终每个 $p_i$ 都要移到 $i$，那么应满足 $p_i\in S$。由此我们可以初步写出一份判断 $k$ 是否可行的代码：

```cpp
bool check(int k) {
    for(int st=1;st<=k;st++) for(int i=st;i<=n;i+=k)
        if(p[i]%k!=st%k) return false;
    return true;
}
```

但是这样不够：判断一个 $k$ 是 $O(n)$ 的，还要枚举 $k$，总的复杂度是 $O(n^2)$ 的。考虑优化。

发现 `check` 函数中，$i\equiv st\pmod k$，因此可以转化为判断 $\forall i\in[1,n],p_i\equiv i \pmod k$ 是否成立。

到这里眉目有点清楚了。我们先来求一个简化版问题：满足 $a\equiv b\pmod k$ 的正整数 $k$ 的集合怎么求？可以转化为：$a-vk=b-wk,v,w\in\mathbb{Z}$ 的正整数解。整理得：$v-w=\dfrac {a-b} k$。由于 $v,w$ 是任意整数，解集就是 $\big\{k\ \big|\ k\in\mathbb{N+},(a-b)\bmod k =0\big\}$。

回到原问题。其实就是求 $p_i\equiv i\pmod k$ 的解的交集的最大值。也就是 $p_i-i$ 的正因数的交集。

到这里问题就解决了。一个数 $x$ 的因数个数有 $O(\sqrt x)$ 个，而且本题怎么也吃不满。用 `std::set` 维护交集，每次加入是 $O(\log n)$ 的。再枚举 $i$，总的复杂度就是 $O(n\sqrt n \log n)$。

这个数据范围，这个复杂度，这个时限，在一些 OJ 上确实过不了。不过你要相信 CF 现代计算机的速度！本人代码只跑了 358 ms。

### 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;

//这里省略了快读快写。下文的 R 代表的就是快读函数。
#define R	myio::read_int()

int n,p[100005];
vector<int> fac[100005]; //储存因数

int solve() {
    n=R;
    for(int i=1;i<=n;i++) p[i]=R;
    set<int> tar,sou;
    for(int i=1;i<=n;i++) sou.insert(i);
    for(int i=1;i<=n;i++) {
        if(i!=p[i]) {
            int dt=abs(i-p[i]);
            for(int j:fac[dt]) {
                if(sou.count(j)) tar.insert(j);
            }
            swap(tar,sou);
            tar.clear();
        }
    }
    return *sou.rbegin();
}

signed main() {
    int t=R;
    for(int i=1;i<=100000;i++) for(int j=i;j<=100000;j+=i) fac[j].push_back(i); //预处理因数
    while(t--) myio::print_int(solve());
    return 0;
}
```

---

