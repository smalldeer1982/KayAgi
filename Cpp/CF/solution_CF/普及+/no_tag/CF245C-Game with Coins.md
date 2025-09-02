# Game with Coins

## 题目描述

两个海盗 Polycarpus 和 Vasily 玩了一个非常有趣的游戏。他们有 $n$ 个装有硬币的箱子，这些箱子都有一个从 $1$ 到 $n$ 的整数编号。编号为 $i$ 的箱子有 $a_{i}$ 个硬币。

Polycarpus 和 Vasily 轮流出手。 Polycarpus 首先出手。在移动过程中，玩家可以选择一个正整数 $x$ $(2×x+1 \leq n)$ 并从每个编号为 $x$ 、 $2 \times x$ 、$2 \times x+1$ 的箱子中取出一个硬币。 可能会发现某些箱子没有硬币，在这种情况下，不会从这个箱子中取出硬币。当所有箱子都没有硬币时，游戏结束。

Polycarpys 非常懒，但是他又想知道游戏最少可以玩几轮，于是他把这个任务交给了你。

## 样例 #1

### 输入

```
1
1
```

### 输出

```
-1
```

## 样例 #2

### 输入

```
3
1 2 3
```

### 输出

```
3
```

# 题解

## 作者：DiDi123 (赞：15)

# 一、题意
给你一个数列 $\{a_n\}$ ，每次操作你可以选择一个正整数 $x(2x+1\leq n)$，使得 $a_x,a_{2x},a_{2x+1}$ 每项减一，求最少多少次操作可以使数列每项小于等于 $0$。

# 二、分析
这道题就是一个**贪心**。

首先，我们发现如果 $n\leq2$ 的话是无法进行操作的，所以不行；其次，如果 $n$ 为偶数时，$x=\frac{n}{2}-1,2x+1<n$，而 $x=\frac{n}{2},2x+1>n$，所以此时也是不行的，直接输出 $-1$。

$n$ 满足要求的时候，我们应该考虑**倒序**枚举，因为比较后面的项只能又前面的项来更新它，而自己是无法更新更后面的项的，所以这些项只有一种选择，如果大于零就必须一次减到零。这样，显然的，当 $x>\lfloor \frac{n}{2}\rfloor$ 时，必须每次不断操作让 $a_x=0$。

那当 $1\leq x\leq \lfloor \frac{n}{2}\rfloor$ 时呢？假设此时我们已经让 $a_{x+1}\sim a_n$ 都小于等于 $0$ 了，那么 $a_x$ 有两种选择，第一种是让 $a_x-1,a_{2x}-1,a_{2x+1}-1$ 第二种是让 $a_x-1,a_{x+1/x-1}-1,a_{\lfloor \frac{x}{2}\rfloor}-1$，由于 $a_{x+1}\sim a_n$ 已经满足条件了，所以第一种有点浪费，根据贪心的想法，我们选择第二种。

综上，直接倒序扫一遍 $a$ 就好了，让每个 $a_x=0$（注意是三项一起减）。

# 三、代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define MAXN 101
int n, a[MAXN], ans;
int con(int x) {
	if (x & 1) return x - 1;
	return x + 1;
}
int main() {
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	if (n < 3 || !(n & 1)) {
		cout << -1;
		return 0;
	}
	for (int i = n; i >= 1; i--)
		if (a[i] > 0) a[con(i)] -= a[i], a[i >> 1] -= a[i], ans += a[i], a[i] = 0;
	cout << ans;
}
```


---

## 作者：AKPC (赞：15)

### 题意
给一个长度 $n$ 的数列 $a$，每次操作选择一个 $i$，将 $a_i,a_{2i},a_{2i+1}$ 减去任意一个 $x$，代价为 $x$，求当所有元素值均 $\leq 0$ 时代价最小值。
### 思路
这题在于模拟。

首先当 $n=1$ 或 $n$ 是个偶数的时候，无论如何也访问不了 $n$ 号箱子，特判在前输出 $-1$。

如果满足条件，那么**倒序**枚举每次操作即可，当枚举 $i$ 是偶数，$a_i,a_i+1,a_{0.5i}$ 减去 $a_{0.5i}$，当枚举 $i$ 是奇数，$a_i,a_i-1,a_{0.5i}$ 减去 $a_{0.5i}$。

为什么倒序呢？

因为顺序时 $i>\lfloor\dfrac{n}{2}\rfloor$ 操作无法执行，毕竟他们不可以更新比 $n$ 更大的项，所以 $\lfloor\dfrac{n}{2}\rfloor+1\sim n$ 的所有箱子需要倒序枚举操作，让前面的项更新自身并操作中减去自身，这样后面的项都会清空，还得益于前面的项。

考虑 $1\sim\lfloor\dfrac{n}{2}\rfloor$ 的每个项，可以正序（选取 $a_i,a_{2i},a_{2i+1}$）亦可倒序，但是选择正序的时候操作，后面的都清空了，再减多少也没有意义，还不如逆序操作减前面没动过的的数更有意义。也就是说整个过程均为倒序。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,a[101],ans;
signed main(){
	cin>>n;
	for (int i=1;i<=n;i++) cin>>a[i];
	if (n==1||n%2==0) {cout<<-1;return 0;}
	for (int i=n;i>=1;i--){
		if (a[i]<=0) continue;
		if (i%2==0) ans+=a[i],a[i+1]-=a[i],a[i/2]-=a[i],a[i]=0;
		else ans+=a[i],a[i-1]-=a[i],a[i/2]-=a[i],a[i]=0;
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：Shadow_Lord (赞：4)

# 题意：
每次从编号为  $x$ , $2 \times x$ , $2 \times x+1$  的箱子中取出一个金币，求最少把所有箱子都清空的次数，无解输出零。


# 思路：

首先 $n=1$ 或  $n$ 为偶数时即 $n$ $\bmod$ $2$ $=$ $0$ 无解,否则直接倒序枚举贪心，如果是偶数，则 $i+1$ , $i/2$  减去  $a_i$  的金币数 ，如果是奇数，则 $i-1$,$(i-1)/2$  减去  $a_i$  的金币数。



```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=105;
int n,a[N],ans;
int main()
{
    ios::sync_with_stdio(false);//关闭同步流 
    cin.tie(0);
    cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
    }
    if(n==1||n%2==0)
    {
        cout<<"-1"; //无解
        return 0;
    }
    for(int i=n;i>=1;i--)
    {
        if(a[i]>0)
        {
            ans+=a[i];
            a[i>>1]-=a[i];
            if(i%2==0)
            a[i+1]-=a[i];
            else a[i-1]-=a[i];
        }
    }
    cout<<ans;//直接输出
    return 0;
}
```


---

## 作者：XXh0919 (赞：2)

纯纯的贪心

### 题目大意

给定一个数列 $\{a_n\}$，每次操作可以选择一个正整数 $x(2x+1\leq n)$，使得 $a_x,a_{2x},a_{2x+1}$每项减 $1$，求最少多少次操作可以使数列每项小于等 $0$。

通过读题可以发现，当 $n<3$ 时，我们是无法进行操作的，而且当 $n$ 为偶数时也是不行的，所以我们就可以直接输出 $-1$。

之后我们就倒序枚举即可得出答案，因为我们要从大往小倒序枚举，直到找到第一个有硬币的项，并且取走它及另外两个项的硬币，一直循环，直到硬币全部消失。

### Code：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[500000],ans;
int f(int x){
	if (x%2==1) return x-1;
	return x+1;
}
int main(){
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	if (n<=2||!(n%2==1)){
		cout<<-1;
		return 0;
	}
	for(int i=n;i>=1;i--){
    if (a[i]>0)a[f(i)]-=a[i];
    a[i>>1]-=a[i];
    ans+=a[i];
    a[i]=0;
   }
	cout << ans;
}
```
（本代码已作防抄袭处理）

管理员求过！！！！

---

## 作者：bj12z_donglinxi (赞：1)

## 题目背景

[自己看题去](https://www.luogu.com.cn/problem/CF245C)

## 基本思路

一道很简单的贪心题。

先来观察下，我们会发现：

#### 当 $n$ 为偶数时，$n$ 号箱子不能选。

#### 当 $n$ 为 $1$ 时，$1$ 号箱子同样不能选。

因此，我们需要在枚举开始前整个特判 ：

```cpp
if (n == 1) puts("-1");//n = 1
else if (n % 2 == 0) puts("-1");//n为偶数
```

剩下的，只需要进行一次简单的倒序枚举即可得出最终答案。

```cpp
for (int i = n ; i >= 1 ; i--) {//倒序循环
			if (a[i] <= 0) continue;
			else {//模拟
				ans += a[i];
				a[i * 2] -= a[i];
				i % 2 == 0 ? a[i - 1] -= a[i];
				a[i + 1] = a[i];
			}
		}
```
为甚魔要这样呢，因为我们要从大往小倒序枚举，直到找到第一个有币的项，并且删掉它及另外两个项的币，以此往复。

## CODE

```cpp
#include <iostream>
using namespace std;

int n, ans;
int a[114514];

int main() {
	scanf("%d", &n);
	for (int i = 1 ; i <= n ; i++) 
		scanf("%d", &a[i]);
   //两个特判
	if (n == 1) puts("-1");//n = 1
	else if (n % 2 == 0) puts("-1");//n为偶数 
	else {
		for (int i = n ; i >= 1 ; i--) {//倒序循环
			if (a[i] <= 0) continue;
			else {//让干啥就干啥
				ans += a[i];
				a[i * 2] -= a[i];
				i % 2 == 0 ? a[i - 1] -= a[i];
				a[i + 1] = a[i];
			}
		}
		printf("%d\n", ans)
	}
	return 0;//完结撒花！
}
//拒绝抄袭题解，共创和谐洛谷
```

---

## 作者：AstaSunch_ (赞：0)

# 题意简述
有 $x$ 个箱子，每次从 $x,2x,2x+1$ 的箱子编号中取出所有金币，直到箱子为空，输出这个次数，如果永远无法全部清空，输出 $-1$。
# 题目思路
贪心，水。

枚举可以发现，在 $x\equiv0\pmod{2}$ 时，无论 $x$ 为多少，最后一个箱子永远无法被选择到，即这种情况无解。

下面要**倒序**枚举，从大到小，选择一个箱子，并清空剩下的两个箱子。

注意特判 $x=1$ 无解的情况。

# Code
```cpp
 
#include<iostream>
using namespace std;
int n,a[1005],sum;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    if(n==1||n%2==0) cout<<"-1";
    else{
        for(int i=n;i>=1;i--){
            if(a[i]>0)
            {
                sum+=a[i],a[i*2]-=a[i];
                i%2==0?a[i-1]-=a[i]:a[i+1]-=a[i];
            }
        }
        cout<<sum;
    }
}


```


---

## 作者：aimcf (赞：0)

贪心水题。

容易发现，当 $n\bmod 2 = 0$ 的时候，$n$ 号箱子是无法选择到的。

同理，当 $n=1$ 的时候，$1$ 号箱子也是无法选择到的。

否则，可以从大到小选择，直接暴力枚举第一个有硬币的箱子，删掉这个箱子的硬币和另外两个箱子的硬币即可。

这种方法是基本上没有浪费的，为最优的贪心方案。时间复杂度 $O(\sum a_i)$。

```cpp
#include <bits/stdc++.h>

using namespace std;

signed main()
{
  int n;
  cin >> n;
  vector <int> a(110);
  for (int i = 1; i <= n; i ++)
    cin >> a[i];
  if (n == 1 || (~n & 1))
    cout << "-1\n";
  else
  {
    int cnt = 0;
    for (int i = n; i; i --)
    {
      int p1 = i, p2 = i >> 1, p3;
      if (i & 1)
        p3 = i - 1;
      else
        p3 = i + 1;
      while (a[i] > 0)
        a[p1] --, a[p2] --, a[p3] --, cnt ++;
    }
    cout << cnt << '\n';
  }
  return 0;
}

```


---

## 作者：wxzzzz (赞：0)

### 题意

给出一个序列 $a$，每次操作选一个数 $x$，将 $a_x,a_{2x},a_{2x+1}$ 减一，问最快几次操作使得 $a_i=0\text{ }(1\le i\le n)$。

### 思路

可以想到下面两条：

1. 如果当前 $x$ 是最优的，那么最优的办法就是将 $a_x,a_{2x},a_{2x+1}$ 减到 $0$。

1. 只能从后往前枚举 $2x$ 或 $2x+1$，因为正序枚举在 $x\ge \dfrac{n}{2}$ 时无法进行。

思路就出来了：

1. 倒序枚举 $i$。

1. 如果 $i$ 为偶数，则将 $a_{\frac{i}{2}},a_i,a_{i+1}$ 减去 $a_i$；如果 $i$ 为奇数，则将 $a_{\frac{i-1}{2}},a_{i-1},a_{i}$ 减去 $a_i$。

最后，要特判 $n<3$ 和 $n$ 为偶数的两种情况，是不可能取完的。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, ans, a[100005];
int main() {
    cin >> n;

    if (n < 3 || n % 2 == 0) {
        cout << "-1";
        return 0;
    }

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
	}

    for (int i = n; i >= 1; i--) {
        if (!a[i])
            continue;
        a[i / 2] = max(a[i / 2] - a[i], 0);
        if (i % 2)
            a[i - 1] = max(a[i - 1] - a[i], 0);
        else
            a[i + 1] = max(a[i + 1] - a[i], 0);
        ans += a[i], a[i] = 0;
    }

    cout << ans;
    return 0;
}
```

---

