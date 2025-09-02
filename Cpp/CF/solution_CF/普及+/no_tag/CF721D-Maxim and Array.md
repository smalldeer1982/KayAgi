# Maxim and Array

## 题目描述

Recently Maxim has found an array of $ n $ integers, needed by no one. He immediately come up with idea of changing it: he invented positive integer $ x $ and decided to add or subtract it from arbitrary array elements. Formally, by applying single operation Maxim chooses integer $ i $ ( $ 1<=i<=n $ ) and replaces the $ i $ -th element of array $ a_{i} $ either with $ a_{i}+x $ or with $ a_{i}-x $ . Please note that the operation may be applied more than once to the same position.

Maxim is a curious minimalis, thus he wants to know what is the minimum value that the product of all array elements (i.e. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF721D/ae24ba75281e48338d849938ea05477ca771d520.png)) can reach, if Maxim would apply no more than $ k $ operations to it. Please help him in that.

## 样例 #1

### 输入

```
5 3 1
5 4 3 5 2
```

### 输出

```
5 4 3 5 -1 
```

## 样例 #2

### 输入

```
5 3 1
5 4 3 5 5
```

### 输出

```
5 4 0 5 5 
```

## 样例 #3

### 输入

```
5 3 1
5 4 4 5 5
```

### 输出

```
5 1 4 5 5 
```

## 样例 #4

### 输入

```
3 2 7
5 4 2
```

### 输出

```
5 11 -5 
```

# 题解

## 作者：xzggzh1 (赞：3)

题意 ：

$n$ 个数，最多进行 $k$ 次操作，每次可以 $+x$ 或 $-x$ ,求当
$$\prod_{i=1}^na_i$$ 

最小时的每个元素。

---


这道题要用到经典的贪心策略：


若要使得，

$$\prod_{i=1}^n \lvert a_i\rvert$$

变到最大，每次需要取出来，

$$ u =\min_{i=1}^n |a_i|$$

将 $u$ 变成 $u+x$ 。

---

反之，若要使那个式子减到最小（其中 $x \leq |a_i| $），也是取出绝对值最小的 $u$ 变成 $u-x$ 。

这样这个题就很好做了，求连乘的最小值，先搞到结果为负。

然后开一个优先队列每次取一个绝对值最小的数把他绝对值搞大就好了。

---

核心代码：

```cpp

struct qnode {
	ll v;
	bool operator < (const qnode &r) const {return abs(a[v])>abs(a[r.v]);}
	qnode (ll vv) {v=vv;}
};
int main () {
	n=read();k=read();x=read();
	for (int i=1;i<=n;i++) a[i]=read();
	int cnt=0;for (int i=1;i<=n;i++) if (a[i]<0) cnt++;
	priority_queue<qnode>q;
	for (int i=1;i<=n;i++)q.push(i);
	int tot=0,f=0;
	while (q.size()&&tot<k) {
		qnode tt=q.top();
		q.pop();
		if (a[tt.v]<0) {
			if (cnt%2==0) {
				//负变成正 
				a[tt.v]+=x;
				if (a[tt.v]>=0) cnt--;
			} else a[tt.v]-=x;
		} else {
			if (cnt%2==0) {
				//正变成负 
				a[tt.v]-=x;
				if(a[tt.v]<0) cnt++;
			} else a[tt.v]+=x;
		}
		q.push(tt.v);
		tot++;
	}
	for (int i=1;i<=n;i++) printf("%lld ",a[i]);
}
```

---

## 作者：Misty_Post (赞：1)

题意：          
$n$ 个数，最多进行 $k$ 次操作，每次可以 $+x$ 或 $-x$ ,求当$\Pi_{i-1}^na_i$ 最小时的每个元素。         

分析：            
显然的，当这些数乘起来是一个正数时，我们如果把一个最靠近 $0$ 的正数变成负数，或把一个最靠近 $0$ 的负数变成正数，就可以用很小的代价取到较小值。

所以，如果我们发现它们初始乘起来是正数，那就找到一个绝对值最小的数，尽量把它变号，就可以用最小代价取到负数。

然后呢？

既然已经变成负数了，那肯定是绝对值的乘积越大越好（数字越小）。

如果某个数的绝对值较小，那么无论加 $x$ 还是减 $x$，它对乘积的影响较小。
但是如果这个数的绝对值变大，对乘积影响会变大。因此，应该优先选择对绝对值最小的数进行操作，使其绝对值增大，从而最大化绝对值的乘积。

所以可以开一个小根堆，每次找绝对值最小的数，扩大它的绝对值就好啦。

```
#include<bits/stdc++.h>
using namespace std;
#define ll long long
priority_queue<pair<ll, ll>, vector<pair<ll, ll> >, greater<pair<ll, ll> > > q;
ll n,k,x,a[1000000],re[1000000];
int main(){
	ll rep=0;//判断正负，0为正，1为负 
	cin>>n>>k>>x;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]<0){
			rep^=1;
			re[i]=-1;//负数 
		}
		else{
			re[i]=1;//正数 
		} 
		q.push({abs(a[i]),i});
	}
	while(1){
		if(q.empty()||!(k)){
			break;
		}
		pair<ll,ll> xx=q.top();
		//cout<<"*"<<xx.first<<" "<<xx.second<<endl;
		q.pop();
		if(a[xx.second]<0){
			if(rep==0){
				a[xx.second]+=x;
				if(a[xx.second]>=0){
					rep=1;
				}
			}
			else{
				a[xx.second]-=x;
			}
		}
		else{
			if(rep==0){
				a[xx.second]-=x;
				if(a[xx.second]<0){
					rep=1;
				}
			}
			else{
				a[xx.second]+=x;
			}
		}
		k--;
		q.push({a[xx.second],xx.second});
	}
	for(int i=1;i<=n;i++){
		cout<<a[i]<<" ";
	}
}
//CF已AC
```

---

