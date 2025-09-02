# VECTAR9 - Mangu Numbers

## 题目描述

 When Changu was introduced to the concept of prime numbers, he was so glad that, after one days happy work, he was able to generate the first thirteen prime numbers. He has the ability that, given any number, he can tell whether or not it is divisible by any of the first thirteen primes. The first thirteen prime numbers are 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, and 41; their product is 304250263527210. A number is called 'mangu' if it is divisible by at least one of the first thirteen primes. Thus, the first number that is not 'mangu' is 1, and the second is 43. Changu wrote all the 'mangu' numbers in ascending order in a list.

 Your task is to find out, given k, what is the k-th element in the list.

## 样例 #1

### 输入

```
2
2
3```

### 输出

```
3
4```

# 题解

## 作者：yingjingxu_NaS2O3 (赞：4)

感觉没什么思维难度，~~建议降黄~~。

## 思路

首先我们看到倍数有一个很明显的容斥。

不妨先考虑两个数的情况，对于一个数 $n$，小于等于 $n$ 且能被 $a,b$ 整除的数的数量为

$$\lfloor \frac{n}{a}\rfloor+\lfloor \frac{n}{b} \rfloor-\lfloor \frac{n}{ab} \rfloor$$

考虑推广到 $m$ 个数。对于一个数 $n$，小于等于 $n$ 且能被 $a_1,a_2,a_3,\cdots,a_n$ 整除的数的数量为

$$\left(\lfloor \frac{n}{a_1}\rfloor+\lfloor \frac{n}{a_2}\rfloor+\cdots+\lfloor \frac{n}{a_m}\rfloor\right)-\left(\lfloor \frac{n}{a_1a_2}\rfloor+\lfloor \frac{n}{a_2a_3}\rfloor+\cdots+\lfloor \frac{n}{a_{m-1}a_m}\rfloor\right)+\cdots+(-1)^{m}\left\lfloor \frac{n}{\prod_{i=1}^m a_i} \right\rfloor$$

注意到随着 $n$ 的增大这个答案一定单调不降，可以从不从这个式子而从这些数入手。若 $n$ 增大为 $n'$，$n$ 以内的数字数量不会受到影响，而会增加 $n$ 至 $n'$ 之间满足条件的数的数量，这个数总是大于等于 $0$，所以答案单调不降。

二分即可，下界是 $1$，上界是题目给定的 $304250263527210$。

时间复杂度 $O(\log \prod a_i)$。

## 代码

放个检查函数好了。

```cpp
void dfs(int n,int c,int p,bool f)
{
	if(!prime[p])
	{
		if(c==1)
			return;
		res+=(f?1:-1)*n/c;
		return;
	}
	dfs(n,c,p+1,f);
	dfs(n,c*prime[p],p+1,!f);
}
bool check(int x)
{
	res=0;
	dfs(x,1,1,0);
	if(res==n)
		ans=x;
	return res<n;
}
```

---

## 作者：e4fsrc2e4fsrc2 (赞：0)

## [VECTAR9 - Mangu Numbers](https://www.luogu.com.cn/problem/SP27319)
~~题外话：由于将题意看成“能被”看成“只能被”，虚空调试 2.5h。~~
## 题意分析
首先，题目要求输出第 $n$ 个能被 $2,3,5,7,11,13,17, 19,23,29,31,37,41$ 整除的数，可以想到用 **二分+容斥** 来解决这个题。

我们二分当前数是多少，然后用容斥算出在 $mid$ 个数中，有多少个数能被那堆质数整除（设为 $x$），然后比较 $x$ 与 $n$ 的大小，更新 $l,r$ 的取值范围。

对于当前枚举到的数 $x$ 来说，一共有 $\left\lfloor \frac x2 \right\rfloor+\left\lfloor \frac x3 \right\rfloor+\left\lfloor \frac x5 \right\rfloor+\cdots+\left\lfloor \frac x{41} \right\rfloor+\left\lfloor \frac x{2\times3} \right\rfloor+\cdots+\left\lfloor \frac x{37\times41} \right\rfloor+\cdots+\left\lfloor \frac x{2\times3\times\dots\times41} \right\rfloor$ 个数满足题意，这显然是单调不降的，所以可以二分。
## AC 代码
```cpp
#include<bits/stdc++.h>
#define ll unsigned long long
#define R register int
using namespace std;
ll n,T,res,a[13]={2ull,3ull,5ull,7ull,11ull,13ull,17ull,19ull,23ull,29ull,31ull,37ull,41ull};
void dfs(ll n,ll x,int id,int cnt){
    if(id>12){
        if(x==1)return;
        // cout<<x<<' '<<cnt<<'\n';
        if(cnt&1)res+=n/x;
        else res-=n/x;
        return;
    }
    dfs(n,x,id+1,cnt),dfs(n,x*a[id],id+1,cnt+1);
}
void solve(){
    cin>>n;
    ll l=1,r=304250263527210,ans=0;
    while(l<=r){
        ll mid=l+r>>1;
        res=0,dfs(mid,1,0,0);
        // cout<<'\n';
        // cout<<mid<<' '<<res<<'\n';
        if(res<n){
            l=mid+1;
        }
        else r=mid-1;
        if(res==n)ans=mid;
    }
    cout<<ans<<'\n';
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>T;
    while(T--)solve();
    return 0;
}

```

---

