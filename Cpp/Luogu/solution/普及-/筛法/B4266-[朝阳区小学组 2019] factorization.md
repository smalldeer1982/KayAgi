# [朝阳区小学组 2019] factorization

## 题目背景

数据为洛谷自造。

## 题目描述

Adleman 非常喜欢数学，最近他遇到了一个棘手的问题：对于一个正整数 $A$，Adleman 发现一些自然数的质因子分解式中没有大于 $A$ 的因子，这样的自然数非常的特殊。Adleman 想知道对于给定的正整数 $A$，一个区间 $[N, N+M]$ 内所有满足上述条件的自然数的个数。

## 说明/提示

### 样例解释

$[30, 40]$ 之间的数质因子分解式如下：
- $30=2\times 3\times 5$
- $31=1\times 31$
- $32=2\times 2\times 2\times 2\times 2$
- $33=3\times 11$
- $34=2\times 17$
- $35=5\times 7$
- $36=2\times 2\times 3\times 3$
- $37=1\times 37$
- $38=2\times 19$
- $39=3\times 13$
- $40=2\times 2\times 2\times 5$

其中 $30,32,36,40$ 的质因子分解式中没有大于 $5$ 的因子，所以一共有 $4$ 个。

### 数据范围

- $50\%$ 的数据满足：$1\leq N,M,A\leq 5000$；
- $100\%$ 的数据满足：$1\leq N,M,A≤50\,000$；

## 样例 #1

### 输入

```
30 10 5```

### 输出

```
4```

# 题解

## 作者：Temp113 (赞：3)

## Solution 1

因为 $1 \le N,M \le 50000$，所以直接枚举 $N \sim N + M$。

对于在此区间的数 $p$，枚举 $2 \sim \sqrt{p}$ 判断，质因子是否大于 $A$。

最后，统计即可。

## Code 1

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, m, a, ans;
bool check(int aa){
	for(int i = 2; i * i <= aa; i++){
		if(!(aa % i) && i > a) return 0;
		while(!(aa % i)) aa /= i;
	}
	if(aa > a) return 0;
	return 1;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie();
	cin >> n >> m >> a;
	for(int i = n; i <= n + m; i++) ans += check(i);
	cout << ans;
	return 0;
}
```

## Solution 2

当然，也可以直接枚举大于 $A$ 的质数（不超过 $N+M$）。

一个数 $p$，若 $q$ 为它的质因子，则一定有：$p=kq$（$k$ 为正整数）。

所以，对于每个大于 $A$ 的质数 $r$，$r$ 的正整数倍中，一定在质因子分解式中，含有 $r$。

最后，统计即可。

## Code 2

精控范围：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 50005;
int n, m, a, ans, tp1, tp2;
bool flg[2 * N];
bool check(int aa){
	for(int i = 2; i * i <= aa; i++) if(!(aa % i)) return 0;
	return 1;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie();
	for(int i = 0; i < 2 * N; i++) flg[i] = 1;
	cin >> n >> m >> a;
	for(int i = a + 1; i <= n + m; i++){
		if(!check(i)) continue;
		tp1 = (n + i - 1) / i;
		tp2 = (n + m) / i;
		for(int j = tp1; j <= tp2; j++) flg[i * j] = 0;
	}
	for(int i = n; i <= n + m; i++) ans += flg[i];
	cout << ans;
	return 0;
}
```

范围略广：

```
#include<bits/stdc++.h>
using namespace std;
const int N = 50005;
int n, m, a, ans;
bool flg[2 * N];
bool check(int aa){
	for(int i = 2; i * i <= aa; i++) if(!(aa % i)) return 0;
	return 1;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie();
	for(int i = 0; i < 2 * N; i++) flg[i] = 1;
	cin >> n >> m >> a;
	for(int i = a + 1; i <= n + m; i++){
		if(!check(i)) continue;
		for(int j = 1; j <= (n + m) / i; j++) flg[i * j] = 0;
	}
	for(int i = n; i <= n + m; i++) ans += flg[i];
	cout << ans;
	return 0;
}
```

---

## 作者：niuniudundun (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/B4266)

# Problem

$[n,n+m]$ 中有多少个数满足质因子分解式中没有大于 $a$ 的因子。

# Solution

输入 $n,m,a$，暴力枚举 $n\sim n+m$。对于每个 $x(n\le x\le n+m)$，判断 $2\sim \sqrt{x}$，有没有数字能整除 $x$。有就用 $x$ 除以这个数，知道除不尽为止。如果这个除数大于 $a$，则 $x$ 不满足要求。如果  $2\sim \sqrt{x}$ 没有数能整除，说明 $x$ 是质数，$x$ 的质因子分解就是 $x=1\times x$，如果 $x$ 大于 $a$，则 $x$ 不满足要求。最后统计满足要求的即可。

# Code

复杂度：$O(m\sqrt{n+m})$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a,ans=0;
bool A(int x,int a){
	for(int i=2;i*i<=x;i++){
		while(x%i==0&&x!=1){
			if(i>a){
				return false;
			}
			x/=i;
		}
	}
	if(x!=1&&x>a){
		return false;
	}
	return true;
}
signed main(){
	cin>>n>>m>>a;
	for(int i=n;i<=n+m;i++){
		if(A(i,a)){
			ans++;
//			cout<<i<<endl;
		}
	}
	cout<<ans<<endl;
	return 0;
}
/*
30 10 5
*/
```

---

## 作者：LINYUHENG2 (赞：1)

## 题目大意
给定 $N,M,A$，求区间 $[N,N+M]$ 有多少数的质因子全部小于 $A$。
## 思路
我们可以枚举大于 $A$ 的因子 $i$，既然 $i$ 是 $A$ 的因子，那么 $i,2i,3i,\dots$ 都有大于 $A$ 的因子，这些数是**不满足**条件的数，将它们的数量记为 $cnt$。

那么，答案就是 $m+1-cnt$。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,a,cnt;
bool t[100005];
bool prime(int n){
    for(int i=2;i*i<=n;i++){
        if(n%i==0) return 0;
    }
    return 1;
}

int main(){
    scanf("%d%d%d",&n,&m,&a);
    for(int i=a+1;i<=n+m;i++){
        if(prime(i)){
            for(int j=1;i*j<=n+m;j++){
                t[i*j]=1;
            }
        }
    }
    for(int i=n;i<=n+m;i++){
        if(t[i]) cnt++;
    }
    printf("%d",m+1-cnt);
    return 0;
}
```

---

## 作者：guoshengyu1231 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/B4266)
## 初步思考
既然是要求一个自然数是否有大于 $A$ 的因子，那我们直接枚举大于 $A$ 的因子 $i$，那么 $i$，$2i$，$3i$ 等都有大于 $A$ 的因子。明白这点应该就很简单了，直接看具体怎么做。
## 具体步骤
- 枚举 $i$ 为大于 $A$ 的因子。判断其是否为质数。
- 如果 $i$ 为质数，那就枚举 $j$ 为倍数，并将 $i\times j$这个数标记为**不**满足条件的数。
- 最后枚举 $i$ 从 $n$ 到 $n+m$，记录 $ans$ 为被标记过的数的数量。最后答案就是 $m+1-ans$。
## 代码

```cpp
#include<bits/stdc++.h> 
using namespace std;
int n,m,k,ans;
bool t[100005];//标记数组 
bool judge(int n)//判断是否为质数 
{
	for(int i=2;i*i<=n;i++) 
	 if(n%i==0) return false;
	return true;
}
int main()
{
	cin>>n>>m>>k;
	for(int i=k+1;i<=n+m;i++)
	 if(judge(i)) for(int j=1;i*j<=n+m;j++) t[i*j]=true;
	for(int i=n;i<=n+m;i++) if(t[i]) ans++;
	cout<<m+1-ans;
	return 0;
}
```

---

## 作者：no_response (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/B4266)
## 题目大意
判断区间 $[n \sim n + m]$ 有多少个数的质因子全部小于 $A$。  
## 解题思路
这道题考察的就是判断质数和分解质因数。

对于每个数 $a_i$，分为两种情况：
- 如果当前数为质数，则他的分解式为 $a_i = 1 \times a_i$。
- 如果当前数为合数，则需要从 $2 \sim \sqrt{a_i}$ 去除 $a_i$，若能整除，即为 $a_i$ 的质因子。

然后依次判断每个质因子是否不大于 $A$，若全部小于，则计数器加一。
## AC CODE
```cpp
#include <bits/stdc++.h>
using namespace std;
vector <int> v1(int x) {
	bool t[50010]; 
	memset(t, 0, sizeof(t));
	t[0] = 1, t[1] = 1;
	for (int i = 2; i * i <= x; i++) { //质数判断
		if (t[i] == 0) {
			for (int j = i * i; j <= x; j += i) {
				t[j] = 1;
			}
		}
	}
	vector <int> ans; //质数数组
	for (int i = 2; i <= x; i++) {
		if (t[i] == 0) {
			ans.push_back(i); //存入
		}
	}
	return ans;
}
int v2(int n, int m, int a) {
	vector <int> prime = v1(a); //质数数组
	int ans = 0;
	for (int i = n; i <= n + m; i++) { //[n, n + m]，在此区间内验证
		int tmp = i;
		bool flag = 1;
		for (int p : prime) {
			if (p * p > tmp) {
				break;
			}
			while (tmp % p == 0) {
				tmp /= p;
			}
		}
		if (tmp > a) { //是否大于A
			flag = 0;
		}
		if (flag == 1) { //是否合法
			ans++;
		}
	}
	return ans;
}
int main() {
	int n, m, a;
	cin >> n >> m >> a;
	cout << v2(n, m, a); //调用函数
	return 0;
}
```
为保持洛谷的良好学习习惯，请勿抄袭。  
**千万别抄袭哦。**  
管理大大辛苦了，各位大佬给蒟蒻点个赞呗。

---

## 作者：lty2023 (赞：0)

- 枚举 $n$ 到 $m$ 之间的数。
- 对于每个数，再枚举 $2$ 到 $a$，在能整除的情况下尽可能的将这个数除以第二次枚举的数。其实就是只用 $a$ 以内的数分解它。
- 如果正好分解完（数字变为 $1$），计数器加一。
- 输出计数器的值。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int a,n,m;
	cin>>n>>m>>a;
	int ans=0;
	for(int i=n;i<=n+m;i++){
		int b=i;
		for(int j=2;j<=a;j++){
			while(b%j==0){
				b/=j;
			}
		}
		if(b==1){
			ans++;
		}
	}
	cout<<ans;
}
```

---

## 作者：yyycj (赞：0)

## 题目简述
给定 $N,M,A$，求 $[N,N+M]$ 中所有质因数都小于等于 $A$ 的数的个数。

## 主要思路
可以直接按题意模拟，求 $n$ 的所有质因数，就可以遍历 $i \in [2,n]$，重复直到 $n \bmod i \neq 0$，$n \gets \frac{n}{i}$。这样 $n$ 除以的所有数都一定是质数，因为合数也由若干个质因数相乘组成，而这些质因数都小于这个合数。等遍历到合数时，$n$ 与这个合数原先的公质因数早就在之前被除完了，公因数同理，这个合数也一定不是 $n$ 的因数。

为了优化代码，$i$ 只需在 $[2,A]$ 这个区间即可，并且只能在这个区间，否则会 `TLE`。最后判断如果 $n=1$，就使答案加 $1$。

## AC Code
```cpp
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

typedef long long ll;
typedef long double db;
const int INT_INF = 0x3f3f3f3f;
const ll LL_INF = 0x3f3f3f3f3f3f3f3f;
// ----------------------------

// ----------------------------

// ----------------------------


int main() {
	int n, m, a; scanf("%d %d %d", &n, &m, &a);
	// ----------------------------
	int j, k, ans = 0;
	for (int i = n; i <= n + m; i++) {
		k = i;
		for (j = 2; j <= a && k > 1; j++) {  // 当 k 的所有质因数都被除完时，可以直接结束循环，进一步优化代码
			while (k % j == 0) k /= j;
		}
		ans += (k == 1);
	}
	// ----------------------------
	printf("%d", ans);
	return 0;
}
```

---

## 作者：LINYUHENG2 (赞：0)

## 题目大意
给定 $N,M,A$，求区间 $[N,N+M]$ 有多少数的质因子全部小于 $A$。
## 思路
我们可以枚举大于 $A$ 的因子 $i$，既然 $i$ 是 $A$ 的因子，那么 $i,2i,3i,\dots$ 都有大于 $A$ 的因子，这些数是**不满足**条件的数，将它们的数量记为 $cnt$。

那么，答案就是 $m+1-cnt$。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,a,cnt;
bool t[100005];
bool prime(int n){
    for(int i=2;i*i<=n;i++){
        if(n%i==0) return 0;
    }
    return 1;
}

int main(){
    scanf("%d%d%d",&n,&m,&a);
    for(int i=a+1;i<=n+m;i++){
        if(prime(i)){
            for(int j=1;i*j<=n+m;j++){
                t[i*j]=1;
            }
        }
    }
    for(int i=n;i<=n+m;i++){
        if(t[i]) cnt++;
    }
    printf("%d",m+1-cnt);
    return 0;
}
```

---

