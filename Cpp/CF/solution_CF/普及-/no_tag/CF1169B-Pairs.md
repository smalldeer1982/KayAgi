# Pairs

## 题目描述

Toad Ivan has $ m $ pairs of integers, each integer is between $ 1 $ and $ n $ , inclusive. The pairs are $ (a_1, b_1), (a_2, b_2), \ldots, (a_m, b_m) $ .

He asks you to check if there exist two integers $ x $ and $ y $ ( $ 1 \leq x < y \leq n $ ) such that in each given pair at least one integer is equal to $ x $ or $ y $ .

## 说明/提示

In the first example, you can't choose any $ x $ , $ y $ because for each such pair you can find a given pair where both numbers are different from chosen integers.

In the second example, you can choose $ x=2 $ and $ y=4 $ .

In the third example, you can choose $ x=1 $ and $ y=2 $ .

## 样例 #1

### 输入

```
4 6
1 2
1 3
1 4
2 3
2 4
3 4
```

### 输出

```
NO
```

## 样例 #2

### 输入

```
5 4
1 2
2 3
3 4
4 5
```

### 输出

```
YES
```

## 样例 #3

### 输入

```
300000 5
1 2
1 2
1 2
1 2
1 2
```

### 输出

```
YES
```

# 题解

## 作者：Trimsteanima (赞：4)

### Description
给定一个范围$n$和$m$个数对$(a_i,b_i)$（$a_i$和$b_i$都在$[1,n]$的范围内）。请问能否找到$x$、$y$$(1 \leq x < y \leq n)$使得$m$个数对中至少有一个数等于$x$或等于$y$。

### Solution
$x$和$y$显然肯定是$a_1$和$b_1$中的其中一个数，所以可以以$a_1$和$b_1$作为基准。记录下每个数组中与$a_1$和$b_1$不相同的数，分为$x$或$y$中有一个数为$a _ 1$或$b_1$两种情况，再将剩下一个数的情况进行统计，判断是否可以满足条件。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 3e6 + 10;
int n, m, a, b, x, y, sum, sum1, sum2, sum3, a1[N], a2[N];
int main() {
    scanf("%d%d%d%d", &n, &m, &x, &y);
    sum1 = sum = 1;
    for (int i = 1; i < m; i++) {
        scanf("%d%d", &a, &b);
        if (a == x || b == x) sum++; else sum2 = std::max(sum2, std::max(++a1[a], ++a1[b]));
        if (a == y || b == y) sum1++;else sum3 = std::max(sum3, std::max(++a2[a], ++a2[b]));
    }
    if (sum + sum2 == m || sum1 + sum3 == m) puts("YES"); else puts("NO");
    return 0;
}
```

---

## 作者：YangXiaopei (赞：1)

## 题目大意：

给出 $m$ 对 $n$ 以内的数对，求是否有两个数，使得在每个数对中，至少一个与这两个数的一个相等。

## Solution:

我们可以以 $a_{1},b_{1}$ 为基准，记录每个 $a_{i},b_{i}$ 不一样的数，分为 $x$ 或 $y$ 中有一个数为 $a_{i}$ 或 $b_{i}$ 两种情况，再将剩下一个数的情况进行统计，判断是否可以满足条件。

最后输出即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, a, b, x, y, sum, sum1, sum2, sum3, a1[3000005], a2[4000005];
int main() {
    cin >> n >> m >> x >> y;
    sum1 = sum = 1;
    for(int i = 1; i < m; i++){
        cin >> a >> b;
        if(a == x || b == x){
            sum++;
        }
        else{
            sum2 = max(sum2, max(++a1[a], ++a1[b]));
        }
        if(a == y || b == y){
            sum1++;
        }
        else{
            sum3 = max(sum3, max(++a2[a], ++a2[b]));
        }
    }
    if(sum + sum2 == m || sum1 + sum3 == m){
        cout << "YES";
        return 0;
    }
    cout << "NO";
    return 0;
}
```

---

## 作者：JustinXiaoJunyang (赞：1)

前排芝士：

Q： `max` 是甚么函数？

A ：这个函数是求两个整数之间较大值。

思路分析

给出 $n$ 和 $m$ 以及 $m$ 个数对$(a_i,b_i)$。能否找到 $x$ 和 $y(1\le x<y\le n)$ 使得 $m$ 个数对中至少有一个数等于 $x$ 或等于 $y$。

$x$ 和 $y$ 显然是 $a_1$ 中的其中一个数，所以可以 $a_1$ 作基准。记录每个数组中与 $a_1$ 不相同的数，分为 $x$ 或 $y$ 中有一个数为 $a_1$ 或 $b_1$ 两种情况，再将剩下一个数的情况进行统计，判断是否可以满足条件 jio 可以了。

参考代码：

只给核心的哈！

```
int a, b;
cin >> a >> b;
if (a == x || b == x) sum++;
else sum2 = max(sum2, max(++a1[a], ++a1[b]));
if (a == y || b == y) sum1++;
else sum3 = max(sum3, max(++a2[a], ++a2[b]));
```

上面的核心代码就是摘自枚举 $m
$ 个数对的循环代码。

[AC 记录](https://www.luogu.com.cn/record/69136254)，不用贴全套代码了。

---

## 作者：yf最qhhh (赞：1)

思路：输入的第一个数对作为
(a,b)，再从后面的数对里去找一对数，作为
(c,d)，然后分别去试每种情况就行了。~~（暴力枚举）~~

看其他题解都是二维数组，那我来写一个一维数组的做法吧（其实都一样）一堆暴力if就行了

注意事项:
**long long!!!!!**

```cpp
#include<iostream>
#define ll long long 
using namespace std;
ll A[1000005],B[1000005];
bool pan(ll x,ll y,ll m){
	ll M=m;
	while(M--){
		if(
		A[m-M]!=x&&
		A[m-M]!=y&&
		B[m-M]!=x&&
		B[m-M]!=y)
		{
			return false;
		}
	}
	return true;
}
int main(){
	ll n,m;
	scanf("%lld%lld",&n,&m);
	ll M=m;
	ll lin;
	while(M--){
		scanf("%lld%lld",&A[m-M],&B[m-M]);
		if(
		A[m-M]!=A[1]&&
		A[m-M]!=B[m-M]&&
		B[m-M]!=A[1]&&
		B[m-M]!=B[1])
		{
			lin=m-M;
		}
	}
	if(
	pan(A[1],B[1],m)||
	pan(A[1],B[lin],m)||
	pan(A[1],A[lin],m)||
	pan(B[1],A[lin],m)||
	pan(B[1],B[lin],m))
	{
		cout<<"YES"<<endl;
		return 0;
	}
	cout<<"NO"<<endl;
}
```
(我if写成这样是方便看，太多了看着眼花）

---

## 作者：rainbow_cat (赞：0)

和明显 $x,y$ 之间的一个肯定是 $a_1$ 和 $b_1$ 中的一个。那么我们枚举 $x$ 是 $a_1$ 和 $b_1$ 中的一个和 $y$ 是 $a_1$ 和 $b_1$ 中的一个。接下来，我们确定另一个数，另一个数肯定是非确定值以外包含数量最多的那个数。然后判断包含 $x$ 或 $y$ 的数量是否为 $m$ 即可。
### Code：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,a,b,x,y,sumx,sumy,maxn,maxm,numx[3000010],numy[3000010];
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m>>x>>y;
	sumx=sumy=1;
	for(int i=1;i<m;i++)
	{
		cin>>a>>b;
		if(a==x||b==x)sumx++;//记录x的个数
		else maxn=max(maxn,max(++numx[a],++numx[b]));//记录可能的y的个数
		if(a==y||b==y)sumy++;//记录y的个数
		else maxm=max(maxm,max(++numy[a],++numy[b]));//记录可能x的个数
	}
	if(sumx+maxn==m||sumy+maxm==m)cout<<"YES";
	else cout<<"NO";
	return 0;
}
```

---

## 作者：F_Mu (赞：0)

题意： _**m**_ 对数，问是否存在x和y使得这m对数中的一个数字等于 _**x**_ 或者等于 _**y**_ 。

分析：分别设置第一对数的第一个数或者第二个数是x。假设第 _**k**_ 对中没有 _**x**_ ，设 _**k**_ 的第一个数为 _**y1**_ ，第二个数为 _**y2**_ ，继续枚举看 _**y1**_ 或 _**y2**_ 是否满足条件
```cpp
#include <bits/stdc++.h>

#define maxn 300005
#define mod 1000000007
#define inf 0x3f3f3f3f
#define start ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define ll long long
#define LL long long
#define endl '\n'
using namespace std;
int a[maxn][2];
int m;

void judge(int x) {
    bool flag = true;
    int y1, y2, cnt;
    for (int i = 2; i <= m; ++i) {
        if (a[i][0] == x || a[i][1] == x)
            continue;
        else {
            y1 = a[i][0];//将该对数的first作为y1
            y2 = a[i][1];//将该对数的second作为y2
            cnt = i;
            flag = false;
            break;
        }
    }
    if (flag) {//如果都存在x，y可以任意取
        cout << "YES" << endl;
        exit(0);
    }
    flag = true;
    for (int i = cnt; i <= m; ++i) {
        if (a[i][0] == y1 || a[i][1] == y1 || a[i][0] == x || a[i][1] == x)
            continue;
        else {
            flag = false;
            break;
        }
    }
    if (flag) {
        cout << "YES" << endl;
        exit(0);
    }
    flag = true;
    for (int i = cnt; i <= m; ++i) {
        if (a[i][0] == y2 || a[i][1] == y2 || a[i][0] == x || a[i][1] == x)
            continue;
        else {
            flag = false;
            break;
        }
    }
    if (flag) {
        cout << "YES" << endl;
        exit(0);
    }
}

int main() {
    start;
    int n;
    cin >> n >> m;
    for (int i = 1; i <= m; ++i)
        cin >> a[i][0] >> a[i][1];
    judge(a[1][0]);//将第一对数的first作为x
    judge(a[1][1]);//将第一对数的second作为x
    cout << "NO" << endl;
    return 0;
}
```


---

