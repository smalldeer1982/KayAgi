# [ARC051C] 掛け算

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc051/tasks/arc051_c

$ N $ 個の整数 $ a_1,\ a_2,\ ...,\ a_N $ が与えられるので、一番小さいものを $ A $ 倍する、という操作を $ B $ 回行います。

この結果できた整数たちを昇順に並べ、順番に出力してください。

ただし出力するときは、出力したい数を $ 10^9\ +\ 7 $ で割ったあまりを出力するようにしてください。

なお、$ 10^9+7 $ で割ったあまりを昇順に並べる、というわけではないことに注意してください。

## 说明/提示

### 制約

- $ 1\ ≦\ N\ ≦\ 50 $
- $ 1\ ≦\ a_i\ ≦\ 1,000,000,000 $
- $ 1\ ≦\ A,\ B\ ≦\ 1,000,000,000 $
- $ A $ は整数である

### Sample Explanation 2

操作の結果、$ 20000,\ 10000200001 $ の $ 2 $ つの整数ができます。$ 10^9+7 $ で割ったあまりを出力することに注意してください。

## 样例 #1

### 输入

```
3 10 3
1 99 10```

### 输出

```
99
100
100```

## 样例 #2

### 输入

```
2 100001 2
1 200000```

### 输出

```
200000
199931```

## 样例 #3

### 输入

```
10 123 1000000000
394632992 714094234 84420 5 3439891 3395 35 58 5001 730```

### 输出

```
954804718
385989482
948741792
268211139
100694402
492858064
955116743
68100851
154525400
479209143```

# 题解

## 作者：wwwwwza (赞：2)

## [题目传送门](https://www.luogu.com.cn/problem/AT_arc051_c)

## 题解
> 对于这道题首先要分类讨论，判断 $A$ 是否等于 $1$。

### 当 $A=1$ 时
直接将输入的数组排序后输出即可。

### 当 $A \neq 1$ 时

1. 按照题目模拟至 $\min\limits_{i=1}^{n} a_i \times A > \max\limits_{i=1}^{n} a_i$，因为 $10^9<2^{30}$，即每个数最多被乘上 $30$ 次，所以可以直接模拟。

2. 接下来就是周期性的模拟了，因为 $\min\limits_{i=1}^{n} a_i \times A > \max\limits_{i=1}^{n} a_i$，所以按照题目模拟一定是先将 $a_1$ 乘上 $A$，再将 $a_2$ 乘上 $A$，以此类推。

3. 将 $B$ 减去最开始模拟所用的步数，最后的结果为 $a_i=a_i \times A^{B/n+(i \leq b \bmod n)}$。

4. 乘多一次 $A$ 的数一定比乘少一次 $A$ 的数小，所以要将乘后的数组分成两段，$[1,b \bmod n]$ 和 $[(b \bmod n) +1,n]$，分别输出。

## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int n,a,b,p[55],cnt=0;
int ksm(int a,int b){//快速幂 
	int sum=1;
	while(b){
		if(b&1)sum=sum*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return sum;
}
signed main(){
	cin >>n>>a>>b;
	for(int i=1;i<=n;i++)cin >>p[i];
	sort(p+1,p+1+n);
	if(a==1){//分类讨论 
		for(int i=1;i<=n;i++)cout <<p[i]<<endl;
		return 0;
	}
	while(b&&p[1]*a<=p[n]){//按题意模拟至可循环计算的状态 
		p[1]*=a;b--;
		sort(p+1,p+1+n);
	} 
	int c=b/n,d=b%n;
	//计算答案 
	for(int i=1;i<=n;i++)p[i]=p[i]*ksm(a,c+(i<=d))%mod;
	//输出答案 
	for(int i=d+1;i<=n;i++)cout <<p[i]<<endl;
	for(int i=1;i<=d;i++)cout <<p[i]<<endl;
	return 0;
}

```

---

## 作者：e4fsrc2e4fsrc2 (赞：0)

## [掛け算](https://www.luogu.com.cn/problem/AT_arc051_c)
## 思路分析
介于已经有一篇题解了，我就再补充一种更好想的做法。~~（但是难调）~~

首先，我们记录下每一个数的初始值和乘 $A$ 的次数，然后用一个小根堆来维护这一个序列，最后用快速幂求出每一个数模 $10^9+7$ 的值即可。

对于小根堆里的数来说，想比较出两个数的大小，就先除以这两个数的最大的可写成 $A^k$ 形式的数，然后累成起来，最后比较大小。

就像这样：
```cpp
//小根堆所用的结构体
struct node{
    ll x;int id,cnt;
    bool operator<(const node&t)const{
        if(t.cnt>cnt){
            ll cntt=t.cnt-cnt,xx=t.x;
            while(xx<x&&cntt)xx*=a,cntt--;
            return!cntt&&xx<x;
        }
        ll cntt=cnt-t.cnt,xx=x;
        while(xx<t.x&&cntt)xx*=a,cntt--;
        return cntt||xx>t.x;
    }
};
```
很显然有一种 $O(b\log n)$ 的做法：
```cpp
while(b--)q.push({q.top().x,q.top().cnt+1}),q.pop();
```
然后我们考虑优化：
- 对于这个序列，如果 $B$ 足够大，那么必然会出现规律：当每个数都当过最小的数后便会出现重复

所以只要求出这段规律的大小即可。

考虑用一个 `vis` 数组维护每个数是否出现过，`cnt` 记录已经出现了多少个不同的数：
```cpp
while(b>0){
        if(cnt==n)break;
        node f=q.top();q.pop();
        if(!vis[f.id])vis[f.id]=1,cntt++;
        _cnt++,cnt[f.id]++,b--;
        q.push({f.x,f.id,f.cnt+1});
    }
```
最后计算出每个数乘 $A$ 的次数即可。

Tip：
1. 要开 `long long`
2. 需要特判 $1$ 的情况
## [AC 代码](https://atcoder.jp/contests/arc051/submissions/48511739)

---

