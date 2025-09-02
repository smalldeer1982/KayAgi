# 题目信息

# Concatenated Multiples

## 题目描述

You are given an array $ a $ , consisting of $ n $ positive integers.

Let's call a concatenation of numbers $ x $ and $ y $ the number that is obtained by writing down numbers $ x $ and $ y $ one right after another without changing the order. For example, a concatenation of numbers $ 12 $ and $ 3456 $ is a number $ 123456 $ .

Count the number of ordered pairs of positions $ (i,j) $ ( $ i≠j $ ) in array $ a $ such that the concatenation of $ a_{i} $ and $ a_{j} $ is divisible by $ k $ .

## 说明/提示

In the first example pairs $ (1,2) $ , $ (1,3) $ , $ (2,3) $ , $ (3,1) $ , $ (3,4) $ , $ (4,2) $ , $ (4,3) $ suffice. They produce numbers $ 451 $ , $ 4510 $ , $ 110 $ , $ 1045 $ , $ 1012 $ , $ 121 $ , $ 1210 $ , respectively, each of them is divisible by $ 11 $ .

In the second example all $ n(n-1) $ pairs suffice.

In the third example no pair is sufficient.

## 样例 #1

### 输入

```
6 11
45 1 10 12 11 7
```

### 输出

```
7
```

## 样例 #2

### 输入

```
4 2
2 78 4 10
```

### 输出

```
12
```

## 样例 #3

### 输入

```
5 2
3 7 19 3 3
```

### 输出

```
0
```

# AI分析结果

### 题目内容
# 拼接倍数

## 题目描述
给定一个由 $n$ 个正整数组成的数组 $a$ 。

我们将数字 $x$ 和 $y$ 的拼接定义为通过按顺序依次写下数字 $x$ 和 $y$ 而得到的数字。例如，数字 $12$ 和 $3456$ 的拼接是数字 $123456$ 。

计算数组 $a$ 中满足拼接 $a_{i}$ 和 $a_{j}$ （$i≠j$）所得数字能被 $k$ 整除的有序位置对 $(i,j)$ 的数量。

## 说明/提示
在第一个示例中，对 $(1,2)$ 、 $(1,3)$ 、 $(2,3)$ 、 $(3,1)$ 、 $(3,4)$ 、 $(4,2)$ 、 $(4,3)$ 满足条件。它们分别产生数字 $451$ 、 $4510$ 、 $110$ 、 $1045$ 、 $1012$ 、 $121$ 、 $1210$ ，每个数字都能被 $11$ 整除。

在第二个示例中，所有 $n(n - 1)$ 对都满足条件。

在第三个示例中，没有满足条件的对。

## 样例 #1
### 输入
```
6 11
45 1 10 12 11 7
```
### 输出
```
7
```

## 样例 #2
### 输入
```
4 2
2 78 4 10
```
### 输出
```
12
```

## 样例 #3
### 输入
```
5 2
3 7 19 3 3
```
### 输出
```
0
```

### 算法分类
数学

### 综合分析与结论
这几道题解的核心思路都是基于数学中余数的性质，通过预处理数据来优化计算满足条件的有序对数量的过程。难点在于如何巧妙地利用拼接操作对余数的影响进行预处理，以及如何选择合适的数据结构来高效存储和查询预处理后的数据。

### 所选的题解
 - **作者：BLUESKY007 (5星)**
    - **关键亮点**：思路清晰，详细阐述了从余数角度思考问题的过程，利用`map`存储预处理数据，并且给出了两种不同常数优化程度的代码。
    - **个人心得**：提到本题卡常严重，分享了自己代码在常数优化前后的不同运行情况。
```cpp
// 第一个代码版本
#include<cstdio>//CF1029D
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<map> 

using namespace std;

map<int,int>mp[11];

const int N=2e5+5;

const long long shi[11]={1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000,10000000000};

int ws(int u){
	return (int)log10(u)+1;
}

int n,k,a[N],mo[N];

long long ans;

int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		mo[i]=a[i]%k;
	} 
	for(int i=1;i<=n;i++){
		for(int j=1;j<=10;j++){
			mp[j][(int)(((shi[j]%k)*mo[i])%k)]++;
		}
	}
	for(int i=1;i<=n;i++){
		int w=ws(a[i]);
		ans+=mp[w][(k-mo[i])%k];
		if((int)((((shi[w]%k)*mo[i])%k)+mo[i])%k==0){
			ans--;
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```
核心实现思想：先对每个数取模得到余数`mo[i]`，然后遍历所有数，对每个数考虑后接不同位数`j`时的余数情况，将余数出现的次数存入`mp[j]`。最后再遍历数组，根据当前数的位数`w`，从`mp[w]`中找到能与之组成`k`倍数的数的个数累加到`ans`，并特判自身拼接自身的情况。
```cpp
// 第二个代码版本
#include<cstdio>//CF1029D
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<map> 

using namespace std;

map<int,int>mp[11];

const int N=2e5+5;

int ws(int u){
	return (int)log10(u)+1;
}

int n,k,a[N],mo[11][N];

long long ans;

int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		mo[0][i]=a[i]%k;
		for(int j=1;j<=10;j++){
			mo[j][i]=(int)(((long long)mo[j-1][i]*10)%k);
		}
	} 
	for(int i=1;i<=n;i++){
		for(int j=1;j<=10;j++){
			if(mo[j][i]){
				mp[j][mo[j][i]]++;
			}
			else{
				mp[j][0]++;
			}
		}
	}
	for(int i=1;i<=n;i++){
		int w=ws(a[i]);
		if(mo[0][i]){
			ans+=mp[w][k-mo[0][i]];
		}
		else{
			ans+=mp[w][0];
		}
		if((mo[w][i]+mo[0][i])%k==0){
			ans--;
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```
核心实现思想：与第一个版本类似，只是预处理余数的方式有所不同，通过`mo[j][i]`记录`a[i]`乘以`10^j`后对`k`取模的结果，后续统计和计算`ans`的方式相同。
 - **作者：fighter (4星)**
    - **关键亮点**：分析了不同数据结构在本题中的应用，从常规`map`优化到哈希表，详细说明了优化原因，代码实现清晰。
```cpp
#include <bits/stdc++.h>
#define ll long long
#define MAX 200005
#define P 10007
using namespace std;

ll n, k;
ll a[MAX], p[20], lg[MAX];
struct hash_map {
    int head[MAX], Next[MAX], cnt;
    ll val[MAX], tot[MAX];
    
    hash_map(){
        cnt = 0;
        memset(head, 0, sizeof(head));
        memset(Next, 0, sizeof(Next));
        memset(val, 0, sizeof(val));
        memset(tot, 0, sizeof(tot));
    }
    
    void insert(ll x) {
        ll k = x%P;
        for(int i = head[k]; i; i = Next[i]) {
            if(val[i] == x) {
                tot[i]++;
                return;
            }
        }
        cnt++;
        Next[cnt] = head[k];
        head[k] = cnt;
        val[cnt] = x;
        tot[cnt] = 1;
    }

    ll find(ll x) {
        ll k = x%P;
        for(int i = head[k]; i; i = Next[i]) {
            if(val[i] == x) {
                return tot[i];
            }
        }
        return 0;
    }
}mp[15];

int main() {
    cin >> n >> k;
    p[0] = 1;
    for(int i = 1; i <= 10; i++) {
        p[i] = p[i-1]*10%k;
    }
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        ll tmp = a[i];
        while(tmp) {
            lg[i]++;
            tmp /= 10;
        }
    }
    for(int i = 1; i <= 10; i++){
        for(int j = 1; j <= n; j++){
            mp[i].insert(a[j]%k*p[i]%k);
        }
    }
    
    ll t, ans = 0;
    for(int i = 1; i <= n; i++){
        t = ((k-a[i])%k+k)%k;
        ans += mp[lg[i]].find(t);
        if((a[i]%k*p[lg[i]]%k+a[i]%k)%k == 0){
            ans--;
        }
    }
    cout << ans << endl;

    return 0;
}
```
核心实现思想：先预处理出`10^x mod k`的值`p[x]`，然后计算每个数`a[i]`的位数`lg[i]`。接着将`a[j] * p[i] mod k`的值插入到哈希表`mp[i]`中。最后遍历数组，根据当前数`a[i]`的位数`lg[i]`从哈希表`mp[lg[i]]`中查询能与之组成`k`倍数的数的个数累加到`ans`，并特判自身拼接自身的情况。

### 最优关键思路或技巧
1. **余数性质的运用**：通过分析拼接操作对余数的影响，将问题转化为寻找满足特定余数关系的数对，大大减少了计算量。
2. **预处理优化**：提前计算并存储一些中间结果（如每个数后接不同位数时的余数情况），避免在后续计算中重复计算，提高了算法效率。
3. **数据结构选择**：根据需求选择合适的数据结构，如`map`或哈希表来存储和查询预处理后的数据，进一步优化时间复杂度。

### 同类型题或类似算法套路
此类题目通常围绕数论中的整除、余数等概念，结合数组操作。常见套路是利用数论性质对问题进行转化，通过预处理减少重复计算，选择高效数据结构存储和查询数据。

### 洛谷相似题目推荐
1. **P1025 数的划分**：涉及整数划分问题，与本题类似，需利用数学性质和预处理优化求解。
2. **P1403 [AHOI2005]约数研究**：通过对约数概念的运用和简单数学推导求解，锻炼数论思维。
3. **P2669 [NOIP2015 普及组] 金币**：结合简单数学运算和循环结构，与本题一样需要对问题进行合理分析和优化。 

---
处理用时：94.10秒