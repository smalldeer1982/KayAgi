# Bitonix' Patrol

## 题目描述

Byteland is trying to send a space mission onto the Bit-X planet. Their task is complicated by the fact that the orbit of the planet is regularly patrolled by Captain Bitonix, the leader of the space forces of Bit-X.

There are $ n $ stations around Bit-X numbered clockwise from 1 to $ n $ . The stations are evenly placed on a circular orbit, so the stations number $ i $ and $ i+1 $ $ (1<=i&lt;n) $ , and the stations number 1 and $ n $ , are neighboring. The distance between every pair of adjacent stations is equal to $ m $ space miles. To go on a patrol, Captain Bitonix jumps in his rocket at one of the stations and flies in a circle, covering a distance of at least one space mile, before finishing in some (perhaps the starting) station.

Bitonix' rocket moves by burning fuel tanks. After Bitonix attaches an $ x $ -liter fuel tank and chooses the direction (clockwise or counter-clockwise), the rocket flies exactly $ x $ space miles along a circular orbit in the chosen direction. Note that the rocket has no brakes; it is not possible for the rocket to stop before depleting a fuel tank.

For example, assume that $ n=3 $ and $ m=60 $ and Bitonix has fuel tanks with volumes of 10, 60, 90 and 100 liters. If Bitonix starts from station 1, uses the 100-liter fuel tank to go clockwise, then uses the 90-liter fuel tank to go clockwise, and then uses the 10-liter fuel tank to go counterclockwise, he will finish back at station 1. This constitutes a valid patrol. Note that Bitonix does not have to use all available fuel tanks. Another valid option for Bitonix in this example would be to simply use the 60-liter fuel tank to fly to either station 2 or 3.

However, if $ n $ was equal to 3, $ m $ was equal to 60 and the only fuel tanks available to Bitonix were one 10-liter tank and one 100-liter tank, he would have no way of completing a valid patrol (he wouldn't be able to finish any patrol exactly at the station).

The Byteland space agency wants to destroy some of Captain Bitonix' fuel tanks so that he cannot to complete any valid patrol. Find how many different subsets of the tanks the agency can destroy to prevent Captain Bitonix from completing a patrol and output the answer modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 说明/提示

All the fuel tanks are distinct, even if some of them have the same capacity.

## 样例 #1

### 输入

```
7 6 5
5 4 12 6 5
```

### 输出

```
6
```

## 样例 #2

### 输入

```
3 60 2
10 100
```

### 输出

```
4
```

# 题解

## 作者：daniEl_lElE (赞：1)

简单题。这咋 $2900$。

不难发现 $n$ 没用，且所有 $a_i$ 可以按 $a_i\bmod m$ 分类。

分类完了就会发现总共只有 $m$ 种，目标让这 $m$ 种任意组合和不为 $0$。

考虑到这种情况下最多只能选 $7$ 种，复杂度可以做到 $\binom{120}{7}$，但是过不去。

不难发现每个东西要么加要么减，故可以缩到 $\frac{m}{2}$，这时候最多选 $6$ 种，可以通过。

我是直接写的 dfs 剪枝，实际复杂度是小于 $\binom{60}{6}$ 的。

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
#define mid ((l+r)>>1)
using namespace std;
const int mod=1e9+7;
int ans=0,m;
int cntt[61],tp;
bitset<120> mv;
bitset<120> sft(bitset<120> bs,int pos){
	return (bs>>pos)|(bs<<(m-pos));
}
int cnt=0,maxv;
void dfs(int now,bitset<120> bs,int tot,int num){
	(ans+=tot)%=mod;
	cnt++;
	maxv=max(maxv,num);
	if(now==tp+1){
		return ;
	}
	for(int i=now;i<=tp;i++){
		if(!bs[i]){
			bitset<120> nw=bs;
			if(!nw[i]) nw[i]=1;
			if(!nw[m-i]) nw[m-i]=1;
			dfs(i+1,(nw|sft(bs,i)|sft(bs,m-i))&mv,tot*cntt[i]%mod,num+1);
		}
	}
}
bitset<120> ept;
signed main(){
	int n,t; cin>>n>>m>>t;
	tp=min(m,60ll);
	for(int i=1;i<=t;i++){
		int a; cin>>a;
		cntt[min(a%m,m-a%m)]++;
	}
	for(int i=0;i<m;i++) mv.set(i);
	dfs(1,ept,1,0);
	cout<<ans;
	return 0;
}
```

---

