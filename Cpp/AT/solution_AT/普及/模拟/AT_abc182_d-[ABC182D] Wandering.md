# [ABC182D] Wandering

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc182/tasks/abc182_d

数列 $ A_1,\ A_2,\ A_3,\ \dots,\ A_N $ が与えられます。 この数列は負の要素を含むかもしれません。  
 数直線上の座標 $ 0 $ に置かれているロボットが、以下の動作を順に行います。

- 正の向きに $ A_1 $ 進む。
- 正の向きに $ A_1 $ 進み、正の向きに $ A_2 $ 進む。
- 正の向きに $ A_1 $ 進み、正の向きに $ A_2 $ 進み、正の向きに $ A_3 $ 進む。

$ \hspace{140pt}\ \vdots $

- 正の向きに $ A_1 $ 進み、正の向きに $ A_2 $ 進み、正の向きに $ A_3 $ 進み、$ \dots $ 、正の向きに $ A_N $ 進む。

動作開始時から終了時までのロボットの座標の最大値を求めてください。

## 说明/提示

### 制約

- $ 1\ \le\ N\ \le\ 200000 $
- $ -10^8\ \le\ A_i\ \le\ 10^8 $
- 入力はすべて整数

### Sample Explanation 1

ロボットは以下のように動きます。 - 正の向きに $ 2 $ 進み、座標が $ 2 $ になる。 - 正の向きに $ 2 $ 進み、座標が $ 4 $ になる。続けて正の向きに $ -1 $ 進み、座標が $ 3 $ になる。 - 正の向きに $ 2 $ 進み、座標が $ 5 $ になる。続けて正の向きに $ -1 $ 進み、座標が $ 4 $ になる。更に正の向きに $ -2 $ 進み、座標が $ 2 $ になる。 動作中の座標の最大値は $ 5 $ なので、 $ 5 $ を出力してください。

### Sample Explanation 3

この場合最初にいた座標 $ 0 $ が最大値です。

## 样例 #1

### 输入

```
3
2 -1 -2```

### 输出

```
5```

## 样例 #2

### 输入

```
5
-2 1 3 -1 -1```

### 输出

```
2```

## 样例 #3

### 输入

```
5
-1000 -1000 -1000 -1000 -1000```

### 输出

```
0```

# 题解

## 作者：So_noSlack (赞：3)

[洛谷链接](https://www.luogu.com.cn/problem/AT_abc182_d)&[Atcoder 链接](https://www.luogu.com.cn/remoteJudgeRedirect/atcoder/abc182_d)

本篇题解为此题**较简单做法**及**较少码量**，并且码风优良，请放心阅读。

## 题目简述

从数轴的原点开始向正方向走。

第一次向前走 $a_1$ 步，第二次向前走 $a_1+a_2$，以此类推。

求走过的**最大位置**。

## 思路

首先直接**模拟**时间复杂度 $O(n^2)$，看一下**数据范围** $(1 \le N \le 2 \times 10^5)$ 得知此方法**会超时**。

那么就需要一点优化，用**前缀和**即可解决此题，没学过前缀和的建议看[这个](https://oi-wiki.org/basic/prefix-sum/)。**通过前缀和求出前 $i$ 项的和**就很容易解决此题了：

```cpp
for(int i = 1; i <= n; i ++) {
		cin >> a[i];
		pre[i] = pre[i - 1] + a[i];
	}
```

先**预处理前缀和**，在预处理的过程中**同步求最大值**，但因为此题的**答案即最大值有可能在过程中产生**，**故需要 $O(N)$ 遍历前缀和求最大**，此时间复杂度可以接受。

经过以上分析和前缀和优化，很容易即可得出**代码**了：

```cpp
#include<iostream>
using namespace std;

int n, a[200005];
long long pre[200005], maxn[200005]; // 前缀和数组及最大前缀和数组

int main() {
	cin >> n;
	for(int i = 1; i <= n; i ++) {
		cin >> a[i];
		pre[i] = pre[i - 1] + a[i]; // 预处理前缀和
		maxn[i] = max(maxn[i - 1], pre[i]); // 预处理前缀和最大值
	}
	long long temp, ans = -0x3f3f3f3f; // ans 要求最大值，所以建议赋值一个足够小的负数
	for(int i = 1; i <= n; i ++) {
		ans = max(ans, maxn[i] + temp); // 遍历求最大值
		temp += pre[i]; // 一点点模拟
	}
	cout << ans << endl; // 输出，换行好习惯
	return 0;
}
```

[提交记录](https://www.luogu.com.cn/record/117611510)

$$\text{The End!}$$

---

## 作者：xxxalq (赞：1)

[原题链接](https://www.luogu.com.cn/problem/AT_abc182_d)

## 题目简述+思路分析：

对于每一个 $i$ 机器人都会把 $\sum_{j=1}^{i-1} A_j$ 都再走一遍，然后把 $A_i$ 也走一遍，这么看好像求前缀和最大值就可以了，但是这一题的答案可能会出现在过程中，所以就要 $O(n)$ 时间复杂度枚举一遍求 $\max$ 就行了。

## 代码：

```cpp
#include<iostream>
#fefine ll long long
using namespace std;
ll n,s[200010],maxn[200010],ans;//s前缀和数组，amxn记录最大前缀，ans记录答案
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>s[i];//直接输入前缀和
        s[i]+=s[i-1];//计算前缀和
        maxn[i]=max(maxn[i-1],s[i]);
    }
    ll tmp=0;//tmp记录到i位置走了多远
    for(int i=1;i<=n;i++){
        ans=max(ans,maxn[i]+tmp);
        tmp+=s[i];
    }
    cout<<ans;
    return 0;
}
```


---

## 作者：xuhanxi_dada117 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc182_d)

# 题目大意

有一个机器人，他从 0 开始。

第一次向前走 $a_1$ ,第二次向前走 $a_1+a_2$ ，以此类推。

求机器人走过的最大位置。

# 解法

## 暴力 / 模拟

没什么好说的，暴力谁不会打呀。

时间复杂度： $O(n^2)$  无法 AC 。

## 正解

考虑到有许多次走动是重复的。

所以，我们可以预处理出每段路的长度，和走这段路的**前缀最大值。**

这样，我们只要枚举 $i$ 表示 $n$ 段路，每段路计算最后走到这里的答案，求最大值即可。

## 代码

```cpp
#include<bits/stdc++.h>
#define N 200010
using namespace std;
int n,a[N],arr[N],Max[N],ans=0,x=0;
int main(){
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>a[i];
        arr[i]=arr[i-1]+a[i];
        Max[i]=max(Max[i-1],arr[i]);
    }
    for(int i=1;i<=n;++i){
        ans=max(ans,Max[i]+x);
        x+=arr[i];
    }
    cout<<ans;
    return 0;
}
```



# 后记

你以为结束了吗？

并没有。

提交上述代码能够获得 0 分的好成绩。

那么怎么满分呢？

## **十年 OI 一场空，不开 long long 见祖宗！**

谢谢。

---

## 作者：loser_seele (赞：0)

首先直接模拟是 $ \mathcal{O}(n^2) $ 的，显然不能通过。

但观察到计算中一堆过程其实是重复的，所以考虑递推。

首先枚举 $ i $，记录当前第 $ i $ 次操作能达到的坐标及假设当前在坐标 $ 0 $ 时这之前的操作能达到的坐标最大值，这些都可以 $ \mathcal{O}(1) $ 更新计算。

然后直接模拟，对于每个 $ i $ 计算出当前坐标之后用当前位置更新当前能达到的最大值，更新答案，然后更新当前坐标即可。

时间复杂度 $ \mathcal{O}(n) $，可以通过。注意数据范围要开 long long。

代码：

```cpp
#import <bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5 + 5;
const int MOD = 1e9 + 7;
int n, a[MAXN], pre[MAXN], ma[MAXN];
signed main() 
{
    cin>>n;
    for (int i = 1; i <= n; i++) 
    {
        cin>>a[i];
        pre[i] = pre[i - 1] + a[i];
        ma[i] = max(ma[i - 1], pre[i]);
    }
    int now = 0, ans = 0;
    for (int i = 1; i <= n; i++) 
    {
        ans = max(ans, now + ma[i]);
        now = now + pre[i];
    }
    cout<<ans;
}
```


---

