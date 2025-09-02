# Product of Binary Decimals

## 题目描述

### 二进制小数的乘积
我们称一个数字为二进制小数，如果它是一个正整数，并且其十进制表示中的所有数字都是0或1。例如，$1010111$ 是一个二进制小数，而 $10201$ 和 $787788$ 不是。

给定一个数 $n$，你被要求判断是否可能将 $n$ 表示为一些（不一定是不同的）二进制小数的乘积。

## 说明/提示

前五个测试用例可以表示为二进制小数的乘积如下：

$121 = 11 \times 11$
$1 = 1$ 已经是一个二进制小数。
$14641 = 11 \times 11 \times 11 \times 11$
$12221 = 11 \times 11 \times 101$
$10110 = 10110$ 已经是一个二进制小数。

## 样例 #1

### 输入

```
11
121
1
14641
12221
10110
100000
99
112
2024
12421
1001```

### 输出

```
YES
YES
YES
YES
YES
YES
NO
NO
NO
NO
YES```

# 题解

## 作者：Pink_Cut_Tree (赞：5)

# CF1950D Product of Binary Decimals 题解

建议评红。

### 解析

我们将题目中的 `binary decimal` 简称为“01 数”。

手动打出 $10\sim 10^5$ 的“01 数”。

然后对于每一个 $n$，将其与“01 数”们试除，当出现 $1$ 时代表是若干个“01 数”的乘积，不然不是。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int T;
int x;
bool flag,ans;
int b[]={10,11,100,101,110,111,1000,1001,1010,1011,1100,1101,1110,1111,10000,10001,10010,10011,10100,10101,10110,10111,11000,11001,11010,11011,11100,11101,11110,11111};
void dfs(int x){
	if(x==1||ans==1){ //是“01 数”或已经有“01 数”了
		ans=1; return;
	}
	for(int i=0;i<30;i++){
		if(x%b[i]==0){
			dfs(x/b[i]);
		}
	}
}
int main(){
	cin.tie(0)->sync_with_stdio(0);
	cin>>T;
	while(T--){
		cin>>x;
		ans=0;
		dfs(x);
		if(ans){
			cout<<"Yes\n";
		}
		else{
			cout<<"No\n";
		}
	}
return 0;
}
```

---

## 作者：minVan (赞：4)

**题目大意**

对于一个好数，满足其各个数位均为 $0$ 或 $1$。给定一个 $n$，问其是否能写成多个好数相乘。

**解题思路**

采用预处理，对于一个 $n=i\times j$，若 $n$ 本来就是好数，则满足题意；若 $i,j$ 均满足题意，则 $n$ 也满足题意。

询问时 $\mathcal{O}(1)$ 判断即可，总时间复杂度 $\mathcal{O}(n\sqrt n+t)$，空间复杂度 $\mathcal{O}(n)$。

**AC 代码，请勿抄袭**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5 + 5;
bool vis[N];
inline bool check(int x) {
	while(x) {
		if(x % 10 > 1) {
			return 0;
		}
		x /= 10;
	}
	return 1;
}
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
	for(int i = 1; i < N; i++) {
		if(check(i)) { vis[i] = 1; continue; }
		for(int j = 1; j * j <= i; j++) {
			if(i % j == 0) {
				if(vis[j] && vis[i / j]) {
					vis[i] = 1;
					break;
				}
			}
		}
	}
	int t;
	cin >> t;
	while(t--) {
		int n;
		cin >> n;
		cout << (vis[n] ? "YES\n" : "NO\n");
	}
	return 0;
}
```

---

## 作者：thh_loser (赞：1)

# CF1950D Product of Binary Decimals

### 题意

给出一个数，问能否分解为若干个仅由 $0$，$1$ 组成的因数的积。

### 思路

注意到 $n \le 10^{5}$，可以发现合法的因数除开 $1$ 只有 $14$ 个，因此暴力枚举即可。

### code
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
int ys[14]={10,11,100,101,110,111,1000,1001,1010,1011,1100,1101,1110,1111};//所有合法因数
bool flag;
bool check(int x){
	while(x){
		if(x%10>1)return 0;
		x/=10;
	}
	return 1;
}
void fun(int js){//模拟枚举过程
	if(js>n)return;
	if(js==n){//枚举到了
		flag=1;
		return;
	}
	for(int i=0;i<14;i++){
		if(flag)return;
		fun(js*ys[i]);
	}
}
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		if(check(n)){
			cout<<"YES\n";
			continue;
		}
		flag=0;
		fun(1);//乘法要从1开始
		cout<<(flag?"YES\n":"NO\n");
	}
	return 0;
}
```

---

## 作者：Harrylzh (赞：0)

~~偏暴力做法。~~

发现在 $10^5$ 内题目要求的数没有很多，考虑全部打表出来再爆搜，最多递归不到五次，所以也不会超时。末尾有 $0$ 的一定是 $10$ 的倍数，所以可以先把末尾 $0$ 去掉再搜。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long d[100]={11,101,111,1001,1011,1101,1111,10001,10011,10101,10111,11011,11101,11111,11001};
bool dfs(long long a)
{
	if(a==1)
	{
		return 1;
	}
	bool flag=0;
	for(long long i=0;i<15;i++)
	{
		if(a%d[i]==0)
		{
			flag=flag||(dfs(a/d[i]));
		}
	}
	return flag;
}
int main()
{
	long long t;
	scanf("%lld",&t);
	while(t--)
	{
		long long n;
		scanf("%lld",&n);
		while(n%10==0) n/=10;
		if(dfs(n))
		{
			printf("YES\n");
		}
		else
		{
			printf("NO\n");
		}
	}
	return 0;
}
```

---

