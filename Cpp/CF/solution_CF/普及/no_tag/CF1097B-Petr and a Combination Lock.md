# Petr and a Combination Lock

## 题目描述

Petr has just bought a new car. He's just arrived at the most known Petersburg's petrol station to refuel it when he suddenly discovered that the petrol tank is secured with a combination lock! The lock has a scale of $ 360 $ degrees and a pointer which initially points at zero:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1097B/390f775757c241d3e93f871107696e4a8b8d123d.png)Petr called his car dealer, who instructed him to rotate the lock's wheel exactly $ n $ times. The $ i $ -th rotation should be $ a_i $ degrees, either clockwise or counterclockwise, and after all $ n $ rotations the pointer should again point at zero.

This confused Petr a little bit as he isn't sure which rotations should be done clockwise and which should be done counterclockwise. As there are many possible ways of rotating the lock, help him and find out whether there exists at least one, such that after all $ n $ rotations the pointer will point at zero again.

## 说明/提示

In the first example, we can achieve our goal by applying the first and the second rotation clockwise, and performing the third rotation counterclockwise.

In the second example, it's impossible to perform the rotations in order to make the pointer point at zero in the end.

In the third example, Petr can do all three rotations clockwise. In this case, the whole wheel will be rotated by $ 360 $ degrees clockwise and the pointer will point at zero again.

## 样例 #1

### 输入

```
3
10
20
30
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
3
10
10
10
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
3
120
120
120
```

### 输出

```
YES
```

# 题解

## 作者：ouuan (赞：5)

如果是在打CF的时候碰到这道题肯定是写个爆搜，但如果是赛后做题就可以考虑 $O(n)$（~~常数为360~~）做法。

$f_{i,j}$ 表示转 $i$ 次后是否有可能为 $j$ 度，$f_{0,0}=true,\ f_{i,j}=f_{i-1,(j+a_i)\mod 360}\ or\ f_{i-1,(j-a_i)\mod 360}$ 。

答案就是 $f_{n,0}$ 。

```cpp
#include <iostream>
#include <cstdio>

using namespace std;

const int N=20;
const int M=360;

int n,a[N];
bool f[N][M];

int main()
{
    int i,j;
    
    cin>>n;
    
    for (i=1;i<=n;++i) cin>>a[i];
    
    f[0][0]=true;
    
    for (i=1;i<=n;++i)
    {
        for (j=0;j<M;++j)
        {
            f[i][j]=(f[i-1][(j+a[i])%M]|f[i-1][((j-a[i])%M+M)%M]);
        }
    }
    
    if (f[n][0]) puts("YES");
    else puts("NO");
    
    return 0;
}
```

---

## 作者：yuhooo (赞：2)

emmmm大家看代码吧，思路还是比较清晰的
```cpp
#include <iostream>
using namespace std;
int n,rot,a[20];
inline bool dfs(int u){   //dfs(i):=a[1]～a[i-1]共i-1步转过的角度
	if(rot%360==0&&u==n+1) return 1; //n步刚好走完且转回0度满足条件return true
	if(u<=n){
		int save=rot;
		rot+=a[u]; if(dfs(u+1)) return 1; rot=save; //第u个顺时针+
		rot-=a[u]; if(dfs(u+1)) return 1; rot=save; //第u个逆时针-
	}
	return 0; //以上都不行的话则return false
}
int main() {
	cin>>n; for(int i=1;i<=n;++i) cin>>a[i]; //input
	rot=a[1]; //初始化，使得初始态rot不为0，避免直接return
	if(dfs(2)) {cout<<"YES"<<endl; return 0;}
	cout<<"NO"<<endl;
}
```


---

## 作者：きりと (赞：2)

 **[题目传送门](https://www.luogu.com.cn/problem/CF1097B)**

~~一道基础的DFS题~~

### 算法分析：

$DFS$搜索每次顺时针，逆时针旋转的方案，当转完$n$次时，若当前度数为$360$的倍数，则转到原点，输出$YES$

### 注意：

为了排除负数度数的情况，逆时针旋转时，若度数不够，要加上$360$

### 代码实现：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[16];
bool flag;
void dfs(int x,int ans)
{
	if(x==n)
	{
		if(ans%360==0)
		{
			flag=1;
		}
		return;
	}
	dfs(x+1,ans+a[x]);
	if(ans>=a[x])
	{
		dfs(x+1,ans-a[x]);
	}
	else
	{
		dfs(x+1,360+ans-a[x]);
	}
	return;
}
int main()
{
	cin>>n;
	for(int i=0;i<n;i++)
	{
		cin>>a[i];
	}
	dfs(0,0);
	if(flag)
	{
		cout<<"YES"<<endl;

	}
	else
	{
		cout<<"NO"<<endl;
	}
	return  0;
}
```


---

## 作者：zjinyi (赞：1)

# 开锁问题 题解

## 题目大意
有一个锁，初始指针指向 $0$ 刻度，可进行 $n(1 \le n \le 15)$ 次逆时针或顺时针转动，第 $i$ 次转动 $ a_i(1 \le n \le 15)$ 度，如果可以再次转到 $0$ 刻度，输出 `YES`，否则输出 `NO`。

## 题目解析
大部分题解都使用的是 DFS 二决策枚举，还有使用 [位运算 + 递推](https://www.luogu.com.cn/article/x4vb2ikg) 的，本文就不再赘述。本文介绍一种**二进制枚举**的方法。

我们每次转动都有 $2$ 种选择选择：顺时针转动或逆时针转动。总共有 $n$ 次转动，因为 $n$ 很小，所以我们可以使用一个 $0$ 到 $2 ^ n - 1$ 之间的二进制数字来表示转动的方案。（$2 ^ {15} \approx 3 \times 10 ^ 4$）

例如 $(1100)_2$ 代表的就是先顺时针转动 $2$ 次，再逆时针转动 $2$ 次。

### 位运算简单学习（已学过可跳过）
位运算是一种二进制专用的运算，没有进位和借位，每一位之间相互独立。

按位与 `&`：对两个数字每一位计算，两位都为 `1`，答案为 `1`，至少一位为 `0`，答案为 `0`。

按位或 `|`：对两个数字每一位计算，两位都为 `0`，答案为 `0`，至少一位为 `1`，答案为 `1`。

按位异或 `|`：对两个数字每一位计算，两位不同，答案为 `1`，两位相同，答案为 `0`。

按位非 `~`：对一个数字每一位计算，这一位为 `0`，答案为 `1`，这一位为 `1`，答案为 `0`。

左移 `<<`：对一个数字每一位计算，最左边舍弃，最右边补 `0`。

右移 `>>`：对一个数字每一位计算，最右边舍弃，最左边补 `0`。

注：位运算的运算优先级很低，当你不知道它的运算优先级时，你可以多加一些括号来增高运算优先级。

### 代码
```cpp
#include <iostream> 
using namespace std;
 
int main()
{
	int n; // 输入 
	cin >> n;
	int a[16];
	for (int i = 0; i < n; ++i)
	{
		cin >> a[i];
	}
	for (int i = 0; i < (1 << n); ++i) 
	// 枚举，i 的二进制表示转动方案（从 1 到 2 的 n 次方），j 表示转动到了第几位 
	{
		int sum = 0;
		for (int j = 0; j < n; ++j)
		{
			if ((i >> j & 1) == 1) // i 的二进制的从右往左数第 j 位为 1 
			{
				sum += a[j];
			}
			else
			{
				sum -= a[j];
			}
		}
		if (sum % 360 == 0) // 输出答案 
		{
			cout << "YES";
			return 0;
		}
	}
	cout << "NO";
	
	return 0;
}
```

---

## 作者：Eason_AC (赞：1)

## Content
有一个锁，它只有指针再次指到 $0$ 刻度处才可以开锁（起始状态如图所示，一圈 $360$ 度）。

以下给出 $n$ 个操作及每次转动度数，如果可以通过逆时针或顺时针再次转到 $0$ 度输出 `YES`，否则输出 `NO`。

**数据范围：$1\leqslant n\leqslant 15$，$1\leqslant a_i\leqslant 180$。**
## Solution
不知道为什么 19 年 4 月就做了这题，现在看到这题想写篇题解，于是就有了这篇题解（

我们一看到数据范围 $n\leqslant 15$，因此可能的选择方向的方案数不会超过 $2^{15}$。这是一个非常小的数字，然后你就可以暴搜去一个一个枚举转向方案，看是否有合法的就行了。 

## Code
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;

int n, flag, a[20], used[20];

inline void check() {
	int sum = 0;
	for(int i = 1; i <= n; ++i)
		sum += a[i] * (used[i] ? -1 : 1);
	if(sum % 360 == 0)
		flag = 1;
}

inline void dfs(int x) {
	if(x == n + 1)
		return check();
	dfs(x + 1);
	used[x] = 1;
	dfs(x + 1);
	used[x] = 0;
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		scanf("%d", &a[i]);
	dfs(1);
	printf(flag ? "YES" : "NO");
	return 0;
}
```

---

## 作者：20120511qhc (赞：0)

## 思路部分

由于数据非常小，且每个度数都只能用一次，容易联想到 `dfs`。

以当前处理的度数与目前总度数为状态，每次处理顺时针转和逆时针转两种情况。

## 代码部分

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, a[20], f;
void dfs(int step, int dig){
  if(step > n){
    if(dig % 360 == 0){
      f = 1;
    }
    return;
  }
  dfs(step + 1, dig + a[step]);
  dfs(step + 1, dig - a[step]);
}
int main(){
  cin >> n;
  for(int i = 1; i <= n; i++){
    cin >> a[i];
  }
  dfs(1, 0);
  cout << (f ? "YES\n" : "NO\n");
  return 0;
}
```


---

## 作者：Jerry_heng (赞：0)

这题相当于裸的深搜题，主要讲一下优化。

1. 毫无优化。

```cpp
#include<bits/stdc++.h>
using namespace std;
bool b=0;
int n,a[16];
void dfs(int k,int s){
	if(k>n){
		if(s==0){
			b=1;
		}
		return;
	}
	dfs(k+1,(s+a[k])%360);
	dfs(k+1,(s-a[k]+360)%360);
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	dfs(1,0);
	if(b)cout<<"YES";
	else cout<<"NO";
	return 0;
}
```
交上去——AC！

？

说实话，这题确实**有点水**。


2. 优化。

当我们已经发现一组解时，即 $b=0$，就没有继续搜索的必要了。

由于是深搜，可能在到同一时刻，指针的方向是相同的。

如对于数列 $1,1,2,3$。

搜到第三个数时可能是 $1+1-2=0$。
也可能是 $(-1)+(-1)+2=0$。

这时候就会发现没有必要后面走重复的路。


```cpp
#include<bits/stdc++.h>
using namespace std;
bool b=0,vis[16][360];
int n,a[16];
void dfs(int k,int s){
	if(vis[k][s])return;
	vis[k][s]=1;
	if(k>n){
		if(s==0){
			b=1;
		}
		return;
	}
	dfs(k+1,(s+a[k])%360);
	if(b)return;
	dfs(k+1,(s-a[k]+360)%360);
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	dfs(1,0);
	if(b)cout<<"YES";
	else cout<<"NO";
	return 0;
}
```


---

## 作者：a1ioua (赞：0)

这道题的数据范围较小，所以我们可以使用 DFS 来解决此题。

注意：如果直接在函数内输出，结果会输出多个 YES 和 NO，所以要用 flag 变量来记录。
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, a[20];
bool flag;
void dfs(int x, int angle) {
	if (x > n) {
		if (angle % 360 == 0) flag = true;
		return ;
	}
	dfs(x + 1, angle + a[x]);
	if (angle >= a[x]) dfs(x + 1, angle - a[x]);
	else dfs(x + 1, 360 + angle - a[x]);//不足 0 度时，要加上 360，以防万一。
}
signed solve() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	dfs(1, 0);
	if (flag) printf("yes");
	else printf("no");
	return 0;
}
signed main() { return solve(); }
```

---

## 作者：Zechariah (赞：0)

可以顺时针转可以逆时针转，但是考虑到n很小，可以直接爆搜所有情况
```cpp
#include <bits/stdc++.h>
#define rg register
#define inl inline
typedef long long ll;
#define jh(x,y) (x^=y^=x^=y)
#define lowbit(x) (x&-x)
const int N = 2e5 + 10, mod = 1e9 + 7;
using namespace std;
namespace fast_IO {
    long long read()
    {
        rg long long num = 0;
        rg char ch;
        rg bool flag = false;
        while ((ch = getchar()) == ' ' || ch == '\n' || ch == '\r');
        if (ch == EOF)return ch; if (ch == '-')flag = true; else num = ch ^ 48;
        while ((ch = getchar()) >= '0'&&ch <= '9')
            num = (num << 1) + (num << 3) + (ch ^ 48);
        if (flag)return -num; return num;
    }
    ll max(rg ll a, rg ll b) { if (a > b)return a; return b; }
    ll min(rg ll a, rg ll b) { if (a < b)return a; return b; }
    void write(rg ll x) { if (x < 0)putchar('-'), x = -x; if (x >= 10)write(x / 10); putchar(x % 10 ^ 48); }
};
int n, a[N];
inl void dfs(rg int step, rg int sum)
{
    if (step > n)
    {
        if (sum % 360 == 0) { puts("YES"); exit(0); }
        return;
    }
    dfs(step + 1, sum + a[step]);
    dfs(step + 1, sum - a[step]);
}

int main()
{
    n = fast_IO::read();
    for (rg int i = 1; i <= n; ++i)a[i] = fast_IO::read();
    dfs(1, 0); puts("NO");
    return 0;
}

```

---

