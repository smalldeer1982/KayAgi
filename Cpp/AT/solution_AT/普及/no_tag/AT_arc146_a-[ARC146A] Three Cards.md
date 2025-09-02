# [ARC146A] Three Cards

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc146/tasks/arc146_a

$ N $ 枚のカードがあります。カードには $ 1 $ から $ N $ の番号がついています。

カード $ i $ には正整数 $ A_i $ が書かれています。

この中から $ 3 $ 枚のカードを選び、好きな順で書かれている整数を連結し新しく整数を作ります。例えば、$ 1,23,4 $ が書かれたカードを選んだとき、$ 1234 $ や $ 4231 $ を作ることができます。

作ることのできる整数の最大値を求めてください。

## 说明/提示

### 制約

- $ 3\ \le\ N\ \le\ 2\ \times\ 10^5 $
- $ 1\ \le\ A_i\ <\ 10^6 $
- 入力は全て整数である。

### Sample Explanation 1

$ 4,5,8 $ が書かれたカードを選んだ場合、$ 458,485,548,584,845,854 $ を作ることができます。 $ 855 $ 以上の整数を作ることはできないので解は $ 854 $ です。

## 样例 #1

### 输入

```
5
1 4 3 5 8```

### 输出

```
854```

## 样例 #2

### 输入

```
8
813 921 481 282 120 900 555 409```

### 输出

```
921900813```

# 题解

## 作者：Nightsky_Stars (赞：1)

# 思路:
我们先将所有卡片按照长度排序，如果长度相同则字典序大的在前面。那么前三个卡片便是答案，三张卡片一共有 $6$ 种情况，直接枚举即可。

# CODE:


```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll maxn=2e5+10;
struct node{
	ll len;
	string s;
}a[maxn];
ll n;
bool cmp1(node &x,node &y){
	if(x.len==y.len) return x.s>y.s;
	return x.len>y.len;
}
int main(){
	#ifdef ONLINE_JUDGE
    ios::sync_with_stdio(0);
    #endif
    cin.tie(0);
    cout.tie(0);
	cin>>n;
	for(ll i=1;i<=n;i++){
		string s;
		cin>>s;
		a[i].len=s.size();
		a[i].s=s;
	}
	sort(a+1,a+n+1,cmp1);
	string s1=a[1].s+a[2].s+a[3].s;
	string s2=a[1].s+a[3].s+a[2].s;
	string s3=a[2].s+a[3].s+a[1].s;
	string s4=a[2].s+a[1].s+a[3].s;
	string s5=a[3].s+a[2].s+a[1].s;
	string s6=a[3].s+a[1].s+a[2].s;
	cout<<max(s1,max(s2,max(s3,max(s4,max(s5,s6)))))<<"\n";
	#ifndef ONLINE_JUDGE
    system("pause");
    #endif
    return 0;
}

```

---

