# [ABC177E] Coprime

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc177/tasks/abc177_e

$ N $ 個の整数があります。$ i $ 番目の数は $ A_i $ です。

「全ての $ 1\leq\ i\ <\ j\ \leq\ N $ について、$ GCD(A_i,A_j)=1 $」が成り立つとき、$ \{A_i\} $ は pairwise coprime であるといいます。

$ \{A_i\} $ が pairwise coprime ではなく、かつ、$ GCD(A_1,\ldots,A_N)=1 $ であるとき、$ \{A_i\} $ は setwise coprime であるといいます。

$ \{A_i\} $ が pairwise coprime、setwise coprime、そのどちらでもない、のいずれであるか判定してください。

ただし $ GCD(\ldots) $ は最大公約数を表します。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 10^6 $
- $ 1\ \leq\ A_i\leq\ 10^6 $

### Sample Explanation 1

$ GCD(3,4)=GCD(3,5)=GCD(4,5)=1 $ なので pairwise coprime です。

### Sample Explanation 2

$ GCD(6,10)=2 $ なので pairwise coprime ではありませんが、$ GCD(6,10,15)=1 $ なので setwise coprime です。

### Sample Explanation 3

$ GCD(6,10,16)=2 $ なので、pairwise coprime でも setwise coprime でもありません。

## 样例 #1

### 输入

```
3
3 4 5```

### 输出

```
pairwise coprime```

## 样例 #2

### 输入

```
3
6 10 15```

### 输出

```
setwise coprime```

## 样例 #3

### 输入

```
3
6 10 16```

### 输出

```
not coprime```

# 题解

## 作者：Elairin176 (赞：3)

[传送门](https://www.luogu.com.cn/problem/AT_abc177_e)       
一道水题。    
首先考虑暴力。     
我们知道，$\gcd$ 函数的时间复杂度是 $O(\log n)$，如果每次找一个 $i$ 和 $j$ 判断第一个条件，那时间复杂度为 $\frac{n(1+n)}{2}$，即 $O(n^2)$。总时间复杂度为 $O(n^2\log n)$，$n$ 最大为 $10^6$，肯定会 TLE。    
接下来为正解：   
我们可以建立一个桶 $res$，$res_i$ 表示 $i$ 出现了多少遍。     
我们输入一个数字就让 $res_i$ 增加一次，之后枚举 $2$ 到 $10^6$ 所有的因数，对于每个因数，去遍历它的倍数，最后判断倍数的个数。如果倍数的个数等于 $n$，就排除 ```setwise coprime```，如果倍数的个数大于 $1$，就排除 ```pairwise coprime```。      
对于正解的时间复杂度：   
找因数的过程为常数，不计算;找倍数的过程是 $O(\log n)$，总时间复杂度为 $O(\log n)$，可以通过本题。     
CODE：   
```
#include <iostream>
using namespace std;
int n,x,res[1000001];
bool a,b;
int main(void){
	cin>>n;
	a=b=true;
	for(int i=0;i<n;i++){
		cin>>x;
		res[x]++; //桶
	}
	for(int i=2;i<=1000000;i++){//遍历因数
		int cnt=0;
		for(int j=i;j<=1000000;j+=i){//统计倍数
			cnt+=res[j];
		}
		if(cnt>1){//判断
			b=false;
		}
		if(cnt==n){
			a=false;
		}
	}
	if(b){//输出，注意要先输出pairwise coprime
		cout<<"pairwise coprime";
	}else if(a){
		cout<<"setwise coprime";
	}else{
		cout<<"not coprime";
	}
	cout<<endl;
} 
```


---

