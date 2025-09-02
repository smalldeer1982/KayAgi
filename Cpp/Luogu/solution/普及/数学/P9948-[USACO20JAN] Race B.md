# [USACO20JAN] Race B

## 题目描述

Bessie 正在参加一场 $K$（$1\le K\le 10^9$）米的跑步比赛。她从 $0$ 米每秒的速度开始比赛。在每一秒中，她可以选择将她的速度增加 $1$ 米每秒，保持速度不变，或者将她的速度减少 $1$ 米每秒。例如，在第一秒中，她可以将她的速度增加到 $1$ 米每秒，跑 $1$ 米，或者保持她的速度 $0$ 米每秒不变，跑 $0$ 米。Bessie 的速度不会降低到小于零。

Bessie 始终朝着终点线的方向跑，她想要花费整数秒的时间完成比赛。此外，她不想在终点时跑得太快：在 Bessie 跑完 $K$ 米的时刻，她希望她的速度不超过 $X$（$1\le X\le 10^5$）米每秒。Bessie 想要对于 $N$（$1\le N\le 1000$）个不同的 $X$ 值知道她多快可以完成比赛。 

## 说明/提示

### 样例解释 1

当 $X=1$ 时，一种最优方案为：

1. 将速度增加到 $1$ 米/秒，跑 $1$ 米
2. 将速度增加到 $2$ 米/秒，跑 $2$ 米，总计跑 $3$ 米
3. 将速度保持在 $2$ 米/秒，总计跑 $5$ 米
4. 将速度保持在 $2$ 米/秒，总计跑 $7$ 米
5. 将速度保持在 $2$ 米/秒，总计跑 $9$ 米
6. 将速度降低到 $1$ 米/秒，总计跑 $10$ 米

当 $X=3$ 时，一种最优方案为：

1. 将速度增加到 $1$ 米/秒，跑 $1$ 米
2. 将速度增加到 $2$ 米/秒，总计跑 $3$ 米
3. 将速度增加到 $3$ 米/秒，总计跑 $6$ 米
4. 将速度保持在 $3$ 米/秒，总计跑 $9$ 米
5. 将速度保持在 $3$ 米/秒，总计跑 $12$ 米

注意当 $X=3$ 时，以下方案是不合法的：

1. 将速度增加到 $1$ 米/秒，跑 $1$ 米
2. 将速度增加到 $2$ 米/秒，总计跑 $3$ 米
3. 将速度增加到 $3$ 米/秒，总计跑 $6$ 米
4. 将速度增加到 $4$ 米/秒，总计跑 $10$ 米

这是因为在 Bessie 跑完 $10$ 米的时刻，她的速度是 $4$ 米/秒。 

## 样例 #1

### 输入

```
10 5
1
2
3
4
5```

### 输出

```
6
5
5
4
4```

# 题解

## 作者：Sirius6699 (赞：3)

# 题解：洛谷P9948 [USACO20JAN] Race B
蒟蒻第一篇题解，[看题面点这里](https://www.luogu.com.cn/problem/P9948)
## 题目大意：
 Bessie 以 $0$ 米每秒的起始速度，用整数秒时间跑 $K$ 米，每秒可以将速度增加 $1$ 米、保持或减少 $1$ 米，在终点时速度不超过 $X$ 米每秒。计算对于 $N$ 个不同的 $X$ 值，跑完的最短时间。
## 普通版思路：

**这道题的分我们一步一步拿。**

首先，**如果她一直加速，最后速度可能也没有超过 $X$**，因此我们先算出直线加速到终点时的速度：
```cpp
  while(MIN<k)
  //如果MIN小于k则将MIN加上i，最后将MIN的值重新赋为i-1。
  {
      MIN+=i;
      i++;
  }
  MIN=i-1;
```
~~分数到账。~~
然后我们定义一个函数 $time$ 来处理其他情况：
```cpp
int time(int a)
{
    if (a>=MIN) return MIN;
    int num=(a-1)*a/2;
    int sum=0;
    t=a;
    while(1)
    {
        sum+=t;
        if(num+(sum-t)*2+t>=k)
        {
            ans=a-1+(t-a)*2+1;
            /*题目要求， Bessie 的速度不能超过 X ，
            所以需要将速度从 t 降低到 t-1 ，再降低到 t-2 ，直到降低
            a。所以最小时间为 a-1+(t-a)*2+1 。*/
            return ans;
        }
        if(num+sum*2>=k)
        {
            ans=a-1+(t-a+1)*2;
            /*此时 Bessie 的速度可以保持不变，
            最小时间为 a-1+(t-a+1)*2 。*/
            return ans;
        }
        t++;
    }
}
```
### 代码分析：
- $k$ 表示比赛的距离，单位为米。
- $n$ 表示不同的速度值的数量。
- $x$ 表示每个速度值。


------------
 - 现在有人要问了：



`num=(a-1)*a/2`，----什么意思呀？

`if(num+(sum-t)*2+t>=k)`, ----为什么这么写啊？

`if(num+sum*2>=k)`，----看不懂怎么办？

首先，第一段代码的作用是计算 Bessie 跑完 $a$ 米时的最小时间。
 $num$ 表示前 `a-1` 秒 Bessie 按照最大速度跑步的总路程。就是**等差数列求和**

接下来，通过不断增加 $t$ 的值，$sum$ 。在每次循环中，判断根据当前累加和和已知的 $num$ 值，是否满足条件：

 - 如果 `num+(sum-t)*2+t>=k`，表示在当前累加和的基础上继续增加 $t$ 的值，加上前面的累加和，可以超过或等于 $k$ 。那么此时的最小时间 $ans$ 等于 `a-1+(t-a)*2+1`，**即当前 $a$ 米距离的最小时间再加上后面 `t-a` 米距离的最小时间再加上 $1$ 秒**。（因为在尝试增加 $t$ 的值之后，Bessie 可以选择增加速度使得总时间不变）。
 - 如果 `num+sum*2>=k`，表示在当前累加和的基础上继续增加 $t$ 的值，可以超过或等于 $k$ 。那么此时的最小时间 $ans$ 等于 `a-1+(t-a+1)*2`，**即当前 $a$ 米距离的最小时间再加上后面 `t-a+1` 米距离的最小时间**。这里不需要额外增加 1 秒，因为在尝试增加 $t$ 的值之后，Bessie 不能再增加速度。

------------
好了，最后主函数直接不断输入输出就行了！
## 核心代码：
```cpp
signed main()
{
//	using namespace std;
/*-------------关闭同步流-------------*/
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
/*------------------------------------*/
	cin>>k>>n;
	int i=1;
	while(MIN<k)/*如果MIN小于k则将MIN加上i，最后将MIN的值重新赋为i-1。*/
	{
	    MIN+=i;
	    i++;
	}
	MIN=i-1;
	FOR(i,1,n)
	{
		cin>>x;
		cout<<time(x)<<endl;
	}
	return 0;
}
```


------------

以上就是本题的**基本思路**，但一些大佬会觉得这题解~~太水了，又唠叨，~~ 不严谨，那么......

## 数学版思路
**思维难度有点大**

**可以跳过！**

对于每个固定的 $X$，Bessie 想要花费恰好整数秒完成比赛，因此可以考虑使用数学方法进行求解。

首先考虑当速度为 $t$ 时，Bessie 跑了多少米。在第 $i$ 秒，她的速度为 $v_i$，那么她跑的距离为 $v_1+v_2+...+v_i$ 米。显然，$v_1=0$，因此 $v_2=v_3=...=v_{t+1}=1,v_{t+2}=v_{t+3}=...=v_{2t}=2$，以此类推，$v_{(k-1)t+1}=v_{(k-1)t+2}=...=v_{kt}=t$。

可以发现，当速度为 $t$ 时，经过 $t-1$ 秒后 Bessie 的速度从 $0$ 增加到 $t$，并且跑了 $\frac{(t-1)t}{2}$ 米；经过 $t$ 秒后，Bessie 的速度保持不变，跑了 $t^2$ 米；经过 $t+1$ 秒后，Bessie 的速度从 $t$ 减少到 $t-1$，并且跑了 $t^2+t$ 米；经过 $t+2$ 秒后，Bessie 的速度从 $t-1$ 减少到 $t-2$，并且跑了 $t^2+2t$ 米，以此类推。

因此要求出 Bessie 在速度为 $t$ 时，第 $k$ 米的位置。当 Bessie 的速度在 $[1, t]$ 区间内逐渐增加时，她跑的距离为 $\frac{(t-1)t}{2}+(t^2)+(t^2+t)+...+[t^2+(k-(t-1)t-1)t]$，即 $\frac{(t-1)t}{2}+t^2(\lfloor\frac{k}{t}\rfloor-t+\frac{2}{t})+\frac{(k-(t-1)t-1)(k-(t-1)t)}{2}$ 米。

当 Bessie 的速度在 $[t, X]$ 区间内保持不变时，她跑的距离为 $\frac{(t-1)t}{2}+t^2(\lfloor\frac{k}{t}\rfloor-t+1)$ 米。

最后再考虑当速度为 $t-1$ 时，Bessie 跑了多少米。速度为 $t-1$ 时，当 Bessie 跑完 $k$ 米时，她的速度为 $t$，因此可以使用之前的公式计算。但是需要注意的是，在速度从 $t-1$ 降低到 $t$ 的时刻，Bessie 的速度必须小于等于 $X$，因此需要将速度从 $t$ 降低到 $t-1$，再降低到 $t-2$，直到降低到 $a$。因此最小时间为 $a-1+(t-a)\times2+1$。


## 完结撒花！Bye!

---

## 作者：Treap_Kongzs (赞：2)

备赛USACO25JAN祭

# P9948 [USACO20JAN] Race B 题解

## 题面分析

~~零帧起手~~从 $0\space m/s$ 开始，每秒有三种决策：
- 加速 $1\space m/s$

- 减速 $1\space m/s$

- 维持原速

当冲过 $K\space m$ 的终点时，速度不得超过 $X\space m/s$。求符合题意的最小时间。

## 解法分析

首先，为了使时间最小化，我们不会且不可以随意减速。

那只要还没到终点，我们就放肆加速，这样时间肯定是最小的。然而终点限速为 $X\space m/s$，那我们还需要适时开始减速。整个运动过程的速度-时间图象大体如下所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/2a6viwbu.png)

然而求完成这个距离的时间显然不好写程序，那我们倒过来，求**运动多少秒会达到甚至超出这个距离呢**？

因为是先加速后减速，所以一定存在一个最大速度 $maxv$。本题的最巧妙的处理来了：

- 对于前面的~~零帧起手~~从零加速阶段，我们直接用 `while` 循环累加算出距离。

- 后面的减速阶段是从 $maxv$ 减速到 $X$
，我们可以视作**从 $X$ 到 $maxv$ 的加速过程**，这样就可以和上面的加速过程放在一起处理。

当我们两个阶段的距离之和**第一次**大于等于题面的距离时，就说明我们找到了最小的 $maxv$（再小一点就还跑不到），此时我们所累加的时间就是答案。

设两个变量 $updis$ 和 $downdis$ 表示加速、减速两个阶段各自运动的距离。一开始先累加 $updis$，当当前速度大于等于 $X$ 时开始两个变量一起累加（我们把减速倒过来变成从 $X$ 到 $maxv$ 的加速了），累加到距离之和大于等于 $K$ 时就退出，返回累加得到的时间，搞定！

我们打一下样例的数据表验证一下：

```plain
k = 10	x = 1
updis	downdis	t
1	0	1
1	1	2
3	1	3
3	3	4
6	3	5
6	6	6

k = 10	x = 2
updis	downdis	t
1	0	1
3	0	2
3	2	3
6	2	4
6	5	5

k = 10	x = 3
updis	downdis	t
1	0	1
3	0	2
6	0	3
6	3	4
10	3	5

k = 10	x = 4
updis	downdis	t
1	0	1
3	0	2
6	0	3
10	0	4

k = 10	x = 5
updis	downdis	t
1	0	1
3	0	2
6	0	3
10	0	4
```

~~这个`\t`的支持太糟糕了~~

我们发现，其实这个题目包含三种情况：

1. $updis$ 和 $downdis$ 都累加完以后才满足退出条件（如样例第 $1,2$ 组数据）。

表现在图像上是三段运动，即加速、以 $maxv$ 匀速、减速三段。这是因为我们是 OI，时间是量子化的（不连续的，以整数变化），直接转折的 $maxv$ 那个时刻是小数，取不到，就只能匀速一段时间了。

2. $updis$ 先累加，只累加了它就可以退出了（如样例第 $3$ 组数据）。

表现在图象上是直接转折，两段运动。就是取得到 $maxv$ 的情况。

3. 从头到尾 $downdis$ 就没累加过，只加了 $updis$ 就退出了（如样例第 $4,5$ 组数据）。

在图象上就是一条直线往上冲，不转折向下了。

你想，如果还没加速到 $X\space m/s$，我们就到终点了，那还减速干什么？

如果正面讨论这三种情况，那该多么痛苦！我们的 $maxv$ 又如何求解呢？然而我们的代码没有众多的特判，一个函数优雅的解决了这两个问题。化繁为简，这就是信息学竞赛的魅力吧。:-)

## 算法分析

没有二分，没有数学，算不上贪心，我们就是**小模拟**。

题目有 $n$ 个 $X$，每个 $X$ 处理的时间 $t$ 有：

$$
\begin{aligned}
\frac{0+maxv}{2}\times t+\frac{X+maxv}{2}\times t&=K\\
t\times(maxv+\frac{X}{2})&=K\\
\therefore t&=\frac{K}{maxv+\frac{X}{2}}
\end{aligned}
$$

所以复杂度为 $O(\frac{K}{maxv+\frac{X}{2}})$，由于后面是两个变量一起累加的，这个上界跑不满。

总时间复杂度为 $\Theta(n\frac{K}{maxv+\frac{X}{2}})$。当数据最糟：距离为 $10^9\space m$，且最终 $X=1\space m/s$ 时，我们算得的 $t=63245$。算上 $n=1000$，总运算量约为 $6 \times 10^7$。

$\therefore$ 这个时间复杂度足以通过本题。$\Box$

## 源码分享

```cpp
#include<bits/stdc++.h>
using namespace std;

int solve(int dis,int maxv)
{
    int ans=0;
    int updis=0,downdis=0;
    int v=0;
    //cout<<"k = "<<dis<<"\tx = "<<maxv<<endl;
    //cout<<"updis\tdowndis\tt\n";
    while(1)
    {
        v++;
        updis+=v;
        ans++;
        //cout<<updis<<'\t'<<downdis<<'\t'<<ans<<endl;
        if(updis+downdis>=dis)return ans;//累加一个就退出
        if(v>=maxv)
        {
            downdis+=v;
            ans++;
            //cout<<updis<<'\t'<<downdis<<'\t'<<ans<<endl;
            if(updis+downdis>=dis)return ans;//累加两个才退出
        }
    }
}

int main()
{
    int k=0,n=0;
    cin>>k>>n;
    for(int i=1;i<=n;i++)
    {
        int x=0;
        cin>>x;
        cout<<solve(k,x);
        if(i<n)cout<<endl;
    }
    return 0;
}
```

## 参考链接

[官方题解](https://usaco.org/current/data/sol_race_bronze_jan20.html)

感谢希沃白板满足了我画图软件的需求（

---

## 作者：superLouis (赞：1)

## 题解：P9948 [USACO20JAN] Race B

update：2024.11.23 【中文标点符号】与【英文、数字、公式或汉字】或【汉字】与【汉字】之间删去了不应添加的多余空格。

----------

我们话不多说，直接进入正题！

----------
### 1. 题意简述
一头奶牛以 $0$ 米每秒的速度开始跑步，每秒可以将速度增加 $1$ 米每秒，不变，或减少 $1$ 米每秒。她希望在跑完 $K$ 米用整数秒，并且跑完第 $K$ 米时的速度不超过 $X$ 米每秒。请问对每一个给定的 $X$，最少需要多少秒跑完？

----------
### 2. 大致思路
- 贪心？我想了半个小时都没有想出正确的解法，总是有返利出现。
- 动态规划？显然，这道题必须升维，$X^2$ 大小的数组根本开不下。
- 二分？大致是我的解法。

#### 关于二分解法
首先我们要想清楚二分什么？是最快的速度？时间？还是别的？我的方案是拿时间进行二分。

决定好了二分的对象，就应当思考 `check` 函数该怎么写。

关于 `check` 函数，我们会传入时间 `t` 和当时的  `x` 。我需要使用 $O(1)$ 的时间复杂度写 `check` 才能不超时。所以我们必须用数学的方法解决。

显然，我们为了让跑的距离尽量远，奶牛的速度就一定是这样的：
$$
1 ⇒ 2 ⇒ ... ⇒ mx ⇒ ...
$$
随后会分成两种情况：

1.  $ mx ⇒ mx-1 ⇒ ... ⇒ x+1 ⇒ x $
2.  $ mx-1 ⇒ mx-2 ⇒ ... ⇒ x+1 ⇒ x $

如果 `mid + x` 为偶数，则是第一种情况；  
如果 `mid + x` 为奇数，则是第二种情况。

注意！！！如果 `t <= x`，就直接是：
$$
1 ⇒ 2 ⇒ ... ⇒ t - 1 ⇒ t
$$

回到正题，为了计算上面的 `mx`，我们可以解一个方程：
$$
mx + (mx - x + 1) = t \\
2mx = t + x - 1 \\
mx = \frac{t+x-1}{2}
$$
为了更简便的计算，我把 `mx` 取为了 `(t + x) / 2`。

现在要计算的未知数都算完了，该算距离了。  
距离是**每秒走的米数之和**，而每秒的米数都是公差为 $1$ 的等差数列，可以用等差数列求和公式来计算。
$$
\frac{（首项 + 末项）\times 项数}{2} 
$$

#### 代码大致是这样的：
```cpp
int sum(int l, int r) {
	int a = min(l, r), b = max(l, r);
	return (a + b) * (b - a + 1) >> 1;
} 
int maxlen(int t, int x) {
	if (t <= x) return sum(1, t); // 速度根本升不到 x 以上
	int speed = (t + x) >> 1;
	if ((t + x) & 1) return sum(1, speed) + sum(speed, x);
	return sum(1, speed) + sum(speed - 1, x); 
}
bool check(int t, int x) {
	return maxlen(t, x) >= k;
}
```
我们回到主函数的二分，左右端点是什么呢？  
显然，左端点是 $1$，但右端点不好确定。

注意到 $K$ 取最大，$X$ 取最小时就是右端点，我们计算即可。

山峰公式告诉我们：
$$
1+2+3+...+k+...+3+2+1=k^2
$$
而此时 $k^2 = 10^9$，则 $k ≈ 31622$。此时，$1+2+3+...+k+...+3+2+1$ 一共有 $k \times 2 + 1$ 个元素，所以右端点就是 $31622 \times 2 + 1 + 1 = 63246$ （最后的 `+1` 时以防外一的，可不加）。

现在差不多思路讲完了，上代码！

----------
### 3. 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int k, n, x;
int sum(int l, int r) {
	int a = min(l, r), b = max(l, r);
	return (a + b) * (b - a + 1) >> 1;
} 
int maxlen(int t, int x) {
	if (t <= x) return sum(1, t); // 速度根本升不到 x 以上
	int speed = (t + x) >> 1;
	if ((t + x) & 1) return sum(1, speed) + sum(speed, x);
	return sum(1, speed) + sum(speed - 1, x); 
}
bool check(int t, int x) {
	return maxlen(t, x) >= k;
}
signed main() {
	cin >> k >> n;
	while (n--) {
		cin >> x;
		int l = 1, r = 63246, ans = 1e9 + 10;
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (check(mid, x)) r = mid - 1, ans = min(ans, mid);
			else l = mid + 1;
		}
		cout << ans << "\n";
	}
	return 0;
}
```
俗话说的好：“十年 OI 一场空，不开 long long 见祖宗。”  
果真，不开 long long 才给我 40 分。

[在这里看我是如何“见祖宗”的。](https://www.luogu.com.cn/record/189518037)
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long 
int k, n, x;
int sum(int l, int r) {
	int a = min(l, r), b = max(l, r);
	return (a + b) * (b - a + 1) >> 1;
} 
int maxlen(int t, int x) {
	if (t <= x) return sum(1, t); // 速度根本升不到 x 以上
	int speed = (t + x) >> 1;
	if ((t + x) & 1) return sum(1, speed) + sum(speed, x);
	return sum(1, speed) + sum(speed - 1, x); 
}
bool check(int t, int x) {
	return maxlen(t, x) >= k;
}
signed main() {
	cin >> k >> n;
	while (n--) {
		cin >> x;
		int l = 1, r = 63246, ans = 1e9 + 10;
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (check(mid, x)) r = mid - 1, ans = min(ans, mid);
			else l = mid + 1;
		}
		cout << ans << "\n";
	}
	return 0;
}
```
这才是满分的代码。

[见完祖宗回来了！](https://www.luogu.com.cn/record/189517856)

----------
写题解不容易，请管理员通过吧！（QwQ）

读者们，点个赞再走吧~

---

## 作者：continueOI (赞：1)

一道数学题。

首先，由于 $k$ 只有一个，所以我们可以直接先预处理出一直加速到达终点所需的时间 $minn$，然后进行分类讨论。

- $x \ge minn$，直接输出 $minn$ 值即可。

- $x < minn$，根据小小的贪心，尽可能的不断加速，可以发现，Bessie 的速度的函数图像应有两种情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/5fluc8z9.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/icy7bn58.png)

我们可以先算出前半段在 $x$ 以下的速度所通过的路程，再循环枚举顶点，判断两种情况是否可以到达终点，来求得所需时间。

具体代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int k,n,x,t,minn;
void solve(int lim){
	if(lim>=minn){
		cout<<minn<<'\n';
		return;
	}
	const int sum1=(lim-1)*lim/2;
	int sum2=0;
	for(t=lim;;t++){
		sum2+=t;
		if(sum1+(sum2-t)*2+t>=k){
			cout<<lim-1+(t-lim)*2+1<<'\n';
			return;
		}
		if(sum1+sum2*2>=k){
			cout<<lim-1+(t-lim+1)*2<<'\n';
			return;
		}
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>k>>n;
	int sum=0;
	for(int i=1;;i++){
		sum+=i;
		if(sum>=k){
			minn=i;
			break;
		}
	}
	while(n--){
		cin>>x;
		solve(x);
	}
	return 0;
}
```


---

## 作者：Misserina (赞：0)

发现没人用二分？那么我发一发我的思路吧

使用 DP 方式递推显然不是最优解，因为何时加速何时减速会随时间变化而变化。

建立一个 $n^2$ 大小的空间也不可取，因为数据范围 $1 \le X \le 10^5$ 容易 MLE。

因此，考虑二分，检查每一个时长 $t$ 情况下奶牛最长跑的距离，逐步缩小范围。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
unsigned k,n,x;
unsigned fun(unsigned a,unsigned b) {
	if (a>b) swap(a,b);
	return (a+b)*(b-a+1)/2;
}
unsigned maxd(unsigned mxtime,unsigned x) {
	if (mxtime<=x) return fun(1,mxtime);
	unsigned maxspeed=(mxtime+x)/2;
	if ((mxtime+x)%2==0) return fun(1,maxspeed)+fun(x,maxspeed-1);
	return fun(1,maxspeed)+fun(x,maxspeed);
}
int main() {
	scanf("%u%u",&k,&n);
	for (int i=1;i<=n;i++) {
		scanf("%u",&x);
		unsigned lt=1;
		unsigned rt=63246; //x=1,k=1e9时的极端值是63245
		while (lt<=rt) {
			unsigned md=(lt+rt)/2;
			if (maxd(md,x)>=k) rt=md-1;
			else lt=md+1;
		}
		printf("%u\n",lt);
	}
}
```

---

