# Restoring Painting

## 题目描述

有一个九宫格，每个格子的值都在 $[1,n]$ 的区间内，现给出它上下左右四格的值，要求每一个 $2\times2$ 的方格的总和都相等，请你求出共有多少种填法。如果 $2\times2$ 格子的总和等于 $0$ ，则表示有数据被记错了。如果在不同的 $2\times2$ 的方格中包含两个不同的整数，则认为两个 $2\times2$ 的方格是不同的。

## 样例 #1

### 输入

```
2 1 1 1 2
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3 3 1 2 3
```

### 输出

```
6
```

# 题解

## 作者：fuxuantong123 (赞：3)

# CF675B Restoring Painting 题解
## 思路
首先在 $3\times3$ 的格子里有四个重复的 $2\times2$ 的格子，其中最中间的数是都重合的，所以有 $n$ 种可能。

四个角上的数差值不变，同时加减，设四个角最大值为 $mx$，则有 $n-mx$ 种可能。

所以答案就是 $n\times (n-mx)$。
## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int s[10];
signed main(){
	int n,a,b,c,d;
	scanf("%lld%lld%lld%lld%lld",&n,&a,&b,&c,&d);
	s[1]=a+b;
	s[2]=a+c;
	s[3]=d+b;
	s[4]=d+c;
	sort(s+1,s+5);
	int fw=s[4]-s[1];
	fw+=1;
	printf("%lld",max(0ll,n*(n-fw+1)));
return 0;
}
```




---

## 作者：N_z_ (赞：3)

## 题意
有一个九宫格，每个格子的值都在 $[1,n]$ 区间内，现给出它上下左右四格的值，每一个 $2\times2$ 的方格的总和都相等，求共有多少种填法。
## 思路
我们假设这个九宫格长这样：
|$x_1$|$a$|$x_2$|
| :-----------: | :-----------: | :-----------: |
|$b$|$x_3$|$c$|
|$x_4$|$d$|$x_5$|
那么由题意，我们可以知道：
$$x_1+a+b+x_3=a+x_2+x_3+c=b+x_3+x_4+d=x_3+c+d+x_5$$

消去 $x_3$ :
$$x_1+a+b=a+x_2+c=b+x_4+d=c+d+x_5$$

由此我们知道， $x_3$ 对满足要求没有影响，我们只要求出其它的填法数再 $\times n$ 即可。

再化一下式子：
$$
\begin{cases}
x_1+b&=x_2+c\\
x_1+a&=x_4+d\\
x_1+a+b&=x_5+c+d\\
\end{cases}
$$
$$
\begin{cases}
x_2&=x_1+b-c\\
x_4&=x_1+a-d\\
x_5&=x_1+a+b-c-d\\
\end{cases}$$
从 $1$ 到 $n$ 枚举 $x_1$ ，判断 $x_1+b-c$ 、 $x_1+a-d$ 、 $x_1+a+b-c-d$ 是否都在 $[1,n]$ 区间内即可。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main()
{
    int n,a,b,c,d;
    cin>>n>>a>>b>>c>>d;
    int ans=0;
    for(int x=1;x<=n;x++)
    if(1<=x+a-d&&x+a-d<=n)
    if(1<=x+b-c&&x+b-c<=n)
    if(1<=x+a+b-c-d&&x+a+b-c-d<=n)
    ans++;
    cout<<ans*n<<endl;
}
```

---

## 作者：shenbairui (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/CF675B)
### 题目大意
有一个九宫格，每个格子的值都在 $[1,n]$ 的区间内，现给出它上下左右四格的值，要求每一个 $2\times2$ 的方格的总和都相等，请你求出共有多少种填法。
### 题目分析
考虑使用暴力枚举 $O(n)$ 算法，通过枚举 $a_{1,1}$ 的值，直接通过这个值来计算出 $a_{1,3},a_{3,1},a_{3,3}$ 的值即可。

```cpp
    for (int i=1;i<=n+1;i++) {   
        int j = i + d - a; 
        int k = i + c - b; 
        int l = j + c - b; 
        if (1 <= min({i, j, k, l}) && max({i, j, k, l}) <= n) ans += n;
        
      }
```
###   代码如下


```cpp
#include<bits/stdc++.h>
using namespace std;
int ans,n,a,b,c,d;
int main() {
    cin>>n>>a>>b>>c>>d;
    for (int i=1;i<=n+1;i++) {   
        int j = i + d - a; 
        int k = i + c - b; 
        int l = j + c - b; 
        if (1 <= min({i, j, k, l}) && max({i, j, k, l}) <= n) ans += n;
        
    }
    cout<<ans;
    return 0;
}
```

[通过记录](https://codeforces.com/contest/675/submission/282733796)

下次见！拜拜！

---

## 作者：jess1ca1o0g3 (赞：1)

题意：给定九宫格以及 $(1,2),(2,1),(2,3),(3,2)$ 四个数，在空中填数满足在 $[1,n]$ 中，有多少种不同的填法。

观察样例，发现答案是 $x\times n$，共 $x$ 组，每一组四个角的数一样，所以每一组选好四个角后 $2,2$ 有 $n$ 种选法。而四个角的填法取决于两两之和最大的减最小的加 $1$，从这个数 $k$ 开始一定有解，所以 $x=n-k+1$。还要注意到可能会出现负数，最后再和 $0$ 取 $\max$，并且开 `long long`。复杂度 $\mathcal{O}(1)$。[代码](https://paste.ubuntu.com/p/7j4dqXtBqw/)。

---

## 作者：ridewind2013 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF675B)

## 分析

有一个九宫格，每个格子的值都在 $[1,n]$ 的区间内，现给出它上下左右四格的值，要求每一个 $2  \times 2$ 的方格的总和都相等，请你求出共有多少种填法。

## 思路

最中间的数所有 $2 \times 2$ 的格子都包含，所以有 $n$ 种填法，设四个角最大值为 $a$，有 $n-a$ 种填法。所以最后答案就是 $n \times (n-a)$。还要注意到可能会出现负数，最后再和 $0$ 取最大值。

## 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;//不开long long见祖宗
int main(){
	ll n,a,b,c,d;
	cin>>n>>a>>b>>c>>d;
	ll a=max(max(a+b,a+c),max(d+b,d+c))-min(min(a+b,a+c),min(d+b,d+c));
	cout<<max(0ll,n*(n-a));
	return 0;
}
```

---

## 作者：1234567890sjx (赞：0)

再不写题解咕值要没了。

因为要求四个 $2\times 2$ 的格子的和都相等，而且四个 $2\times 2$ 的格子都包含了 $a_{2,2}$，所以 $1\le a_{2,2}\le n$，共有 $n$ 种选法。

然后考虑枚举左上角 $a_{1,1}$ 的值，直接通过这个值来计算出 $a_{1,3}$，$a_{3,1}$，$a_{3,3}$ 的值即可。模拟实现，时间复杂度为 $O(n)$。

```cpp
void fun() {
  int s = 0;
  for (int i = 1; i <= n; i++) {
    int a11 = i;
    int a13 = i + d - 1;
    int a31 = i + c - b;
    int a33 = j + c - b;
    int _[4] = {a11, a13, a31, a33};
    sort(_, _ + 4);
    if (_[0] >= 1 && _[3] <= n) s += n;
  }
  cout << s << '\n';
}
```

---

## 作者：mahaoming (赞：0)

# CF675B Restoring Painting 题解

### 思路

首先，容斥原理，九宫格中四个 $2$ $×$ $2$ 中都含有中间那一个数，所以中间那一个数是多少无所谓，一至 $n$ 都行。所以答案要 $×$ $n$。

然后考虑未给数中最小的一个，它加上 $|a-d|+|b-c|$ 就是未给数中最大的一个，所以未给数中最小的一个为未给数中最大的一个减 $|a-d|+|b-c|$。未给数中最大的一个 最大为 $n$，所以未给数中最小的一个最大为 $n-(|a-d|+|b-c|)$，也就是 $n-|a-d|-|b-c|$。未给数中最小的一个最小为 $1$。所以未给数有 $n$ $×$ $(n-|a-d|-|b-c|)$ 种情况。

最后不要忘记与 $0$ 取最大值。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,a,b,c,d;
int main(){
	cin>>n>>a>>b>>c>>d;
	cout<<max(n*(n-abs(a-d)-abs(b-c)),0ll);
	return 0;
}


```

---

## 作者：andyli (赞：0)

考虑枚举左上角的格子中的数。根据每个 $2\times 2$ 格子中的数和相等，且中间格子是共用的，容易推出其他三个角格子的数，判断是否在 $\left[1,n\right]$ 中，若在，则因为中间格子任意，此时答案加上 $n$。  

时间复杂度 $O(n)$。
```cpp
int main() {
    dR(int, n, a, b, c, d);
    i64 ans = 0;
    _for (i, 1, n + 1) {   // top left
        int j = i + d - a; // bottom left
        int k = i + c - b; // top right
        int l = j + c - b; // bottom right

        if (1 <= Min(i, j, k, l) && Max(i, j, k, l) <= n) {
            ans += n;
        }
    }
    print(ans);
    return 0;
}
```

---

