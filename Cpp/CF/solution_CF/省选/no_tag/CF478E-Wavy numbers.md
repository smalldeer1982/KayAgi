# Wavy numbers

## 题目描述

我们将一类正整数称为“波浪数”，它的每个数位上的数都大于或小于两边数位上的数。例如，$35270$，$102$，$747$，$20$ 和 $3$ 都是波浪数；而 $123$，$1000$ 和 $2212$ 不是波浪数。

你的任务是找到第 $k$ 小且能被 $n$ 整除的波浪数 $r$。

保证 $r \le 10^{14}$。

## 说明/提示

第一个样例中，前四个能被 $n$ 整除的波浪数为：$492$，$615$，$738$ 和 $1845$。

## 样例 #1

### 输入

```
123 4
```

### 输出

```
1845
```

## 样例 #2

### 输入

```
100 1
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
97461 457
```

### 输出

```
1805270103
```

# 题解

## 作者：lupengheyyds (赞：1)

## 题面

我们将一类正整数称为“波浪数”，它的每个数位上的数都大于或小于两边数位上的数。

你的任务是找到第 $k$ 小的能被 $n$ 整除的波浪数 $r$。

$1\le k,n,r\le 10^{14}$

## 题解

注意到 $\sqrt {10^{14}}=10^7$ 是可以接受的，我们考虑折半搜索。

具体地，搜索两个数 $a,b$ 满足 $a,b< 10^7,a\times 10^7+b\equiv 0\pmod n$

可以先枚举 $b$ ，如果 $r$ 是在这里面的，直接输出答案。并当 $b$ 在整个 $7$ 位上都是“波浪的”，那么保存 $b\mod n$ 的余数，以便处理枚举 $a$ 时的情况。

但是如果在枚举 $a$ 的时候直接用 `unordered_map` 常数太大，可以先用其处理，处理完 $b$ 后经行离散化，在整个 $7$ 位上都是“波浪数”的个数大小不会超过 $900000$，接着用数组存储即可。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
typedef long long ll;
const int VV=1e7+5;
ll k,n,jz[20];
int mmp[10][2][900000];
unordered_map<int,int> mp[10][2];
int lsh[900000];
ll Mod(ll x){
	return (x%n+n)%n;
}
int bit[20];
int Check(ll x,bool d){
	int cnt=0;
	int tmp=x;
	while(x){
		bit[++cnt]=x%10;
		x/=10;
	}
	int up=d?cnt:7;
	for(int i=up;i>=2;i--){
		if(bit[i-1]==bit[i])return i-1;
		if(i<up&&(bit[i+1]>bit[i])==(bit[i]>bit[i-1]))return i-1;
	}
	return -1;
}
ll Ans(ll x){
	for(int i=1;i<1e7;i++){
		ll val=x*1e7+i;
		if(Check(val,1)!=-1)continue;
		if(val>1e14)return -1;
		if(val%n==0)k--;
		if(k==0)return val;
	}
	return -1;
}
int a[VV];
int Find(int x){
	return lower_bound(lsh+1,lsh+1+lsh[0],x)-lsh;
}
signed main(){
	jz[0]=1;for(int i=1;i<=14;i++)jz[i]=jz[i-1]*10;
	cin>>n>>k;
	if((__int128)n*k>=1e14||k>247632541500ll){
		cout<<-1;
		return 0;
	}
	for(int i=1;i<=1e7;i++){
		int chk=Check(i,1);
		if(chk!=-1){
			i+=jz[chk-1]-1;
			continue;
		}
		if(i%n==0)k--;
		a[++a[0]]=i;
		if(k==0){
			cout<<i;
			return 0;
		}		
		if(Check(i,0)==-1)mp[i/1000000][(i/1000000)<(i/100000%10)][Mod(i)]++,lsh[++lsh[0]]=Mod(i);
	}
	sort(lsh+1,lsh+1+lsh[0]);
	lsh[0]=unique(lsh+1,lsh+1+lsh[0])-lsh-1;
	for(int i=0;i<=9;i++){
		for(int j=0;j<=1;j++){
			int cnt=1;
			for(auto val:mp[i][j])
				mmp[i][j][Find(val.first)]=val.second;
		}
	}
	for(int v=1;v<=a[0];v++){
		int i=a[v];
		int cnt=0;
		int tmp=Mod(-i*1e7);
		if(tmp<=1e7){
			int x=Find(tmp);
			if(lsh[x]!=tmp)continue;
			if(i<10||(i/10%10)<(i%10))for(int j=0;j<i%10;j++)cnt+=mmp[j][1][x];
			if(i<10||(i/10%10)>(i%10))for(int j=i%10+1;j<=9;j++)cnt+=mmp[j][0][x];	
		}
		if(k<=cnt){
			cout<<Ans(i);
			return 0;
		}else k-=cnt;
	}
	cout<<-1;
	return 0;
}
```

---

## 作者：_SeeleVollerei_ (赞：1)

*2900 不知道是什么水平，但是能独立做出这题还是很有成就感的。

数据范围上 $10^{14}$ 就很像根号，考虑对于 $n\ge 10^7$ ，直接暴力枚举然后判断即可，复杂度 $O(\frac{10^{14}}{n})$ 。

考虑对于 $n\le 10^7$ 怎么做，因为是整除所以考虑从余数入手，因为 $n$ 较小所以余数也只有 $10^7$ 种。

考虑按照余数对所有的数分类，但是不可能去枚举这 $10^{14}$ 个数，还是考虑从根号 $10^7$ 入手。

考虑对于一个数，十进制下有 14 位，我们将它拆开成两部分，每一部分有 7 位。

对于后 7 位，我们暴力枚举每个数，依据三个东西去给这些数分类。注意这里的数如果不满 7 位，因为要和前 7 位拼接的原因，所以要自动补前导 0 。

1. 首位的数字

2. 首位的数字是否大于第二位的数字

3. $\bmod\ n$ 的余数。

所以我们可以开一个三维的 vector ，把每个数存到对应的类里面。

然后我们暴力枚举前 7 位是什么，显然对于每种可能，与它可拼接的后 7 位最多只有 9 类，暴力枚举即可。

总的时间复杂度为 $O(\sqrt{10^{14}}\times chk)$ ， chk 是判断一个数是否为波浪数的复杂度。

理论上的空间复杂度为 $O(10^7)$ ，但是会发现这个 vector 会爆空间（因为空 vector 实际上也是占空间的），所以分治的边界可以调一下，太小会 TLE ，大了又会 MLE ，最后我的程序是将边界定为 1005000 能在 1.4s 内通过本题。

https://codeforces.ml/contest/478/submission/157365547

---

