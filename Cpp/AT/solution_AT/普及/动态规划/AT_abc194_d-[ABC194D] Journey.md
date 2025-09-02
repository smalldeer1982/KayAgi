# [ABC194D] Journey

## 题目描述

在一张有 $n$ 个节点的图上，高桥站在节点 $1$ 处。现在的图没有任何连边。

高桥在图连通之前，会重复执行下列操作：

- 随机选择一个点，每个点被选中的概率在每一次都是相等的，都是 $\frac{1}{n}$。
- 从当前点连一条边到选中的点。图允许重边和自环。然后，去到那个选中的点。

求出其期望操作次数。你的答案与标准答案的误差不超过 $10^{-6}$ 即可被判为通过。

## 样例 #1

### 输入

```
2```

### 输出

```
2.00000000000```

## 样例 #2

### 输入

```
3```

### 输出

```
4.50000000000```

# 题解

## 作者：xQWQx (赞：2)

### 前置
  
[题目链接](https://www.luogu.com.cn/problem/AT_abc194_d)

[AC 记录](https://www.luogu.com.cn/record/190195177)

### 思路

选中第 $s$ 条边的概率是 $\frac{1}{n-s+1}$，要使图联通，至少要连 $n-1$ 条边，所以我们就只需要把 $1$ 到 $n-1$ 每条边的概率加起来就行了。

### 做法

循环增加每一条边的概率，保留 $6$ 位小数输出即可。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    double n,cnt;
    cin>>n;
    for(double i=1;i<n;i++) cnt+=n/i*1.000;//求和
    printf("%.6lf",cnt);//保留6位小数输出
    return 0;
}
```

---

## 作者：Lzh2012 (赞：1)

## 思路：
这是一道数学思维题，求期望次数，其实也就是求选中每一个点的概率之和。一共有 $n$ 个点，所以选中第一点的概率就是 $\frac{1}{n}$，第二点由于没了第一点，概率就变为 $\frac{1}{n-1}$，第三点则是 $\frac{1}{n-2}$，之后以此类推，把所有概率累加起来输出即可（输出是小数，要开`double`）。

最后，代码的话按照思路模拟就好了。

---

## 作者：Luogu_916767 (赞：1)

[In Luogu](https://www.luogu.com.cn/problem/AT_abc194_d)

### 题目大意

一共 $n$ 个点，每次等概率选择一个点与当前所在的点连接并转移至选定的点，问使整个图联通的期望次数是多少。

### 思路分析

易得，选中第 $1$ 个点的概率是 $\frac{1}{n}$，选择第二个点的概率是 $\frac{1}{n-1}$，以此类推，答案就是 $\sum_{i = 2}^{n} \frac{n}{n - i + 1} = \sum_{i = 1}^{n - 1} \frac{n}{i}$，直接计算即可。

### Code

```cpp
#include<bits/stdc++.h>

using namespace std;

double n,ans;

int main(){
    cin>>n;
    for(double i = 1.000; i < n; i ++ ){
        ans += n/i;
    }
    printf("%.9lf",ans);
}
```

---

## 作者：Lyw_and_Segment_Tree (赞：1)

[原题传送门](https://www.luogu.com.cn/problem/AT_abc194_d)  
## 题意简述
> 在一张有 $n$ 个节点的图上，某人在节点 1 处。现在的图没有任何连边。这个人在图连通之前，会重复执行下列操作：
> - 随机选择一个点，每个点被选中的概率在每一次都是相等的，都是 $\frac{1}{n}$
 。
> - 从当前点连一条边到选中的点。图允许重边和自环。然后，去到那个选中的点。

> 求把所有顶点连起来的期望操作次数。

## 开始解题！
首先我们利用一个结论：
> 对于一个概率为 $p$ 的事件，则其期望出现的次数为 $\frac{1}{p}$。

然后我们设当前选中的顶点为 $x$，则概率为 $\frac{n}{n - |x|}$，那么我们一开始有 $x = 1$，最后让 $x = n$，所以答案就是下面这个式子：
$$\sum\limits_{i = 1}^{i \le n-1} \dfrac{n}{i}$$  
然后，由于精度的问题，代码中应该使用 `double` 或 `long double`。  
总结以上结论，可得代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    double ans = 0.0;
    double n;
    cin >> n;
    for(int i=1;i<n;i++){
        ans += n / i; 
    }
    printf("%12lf",ans);
}
```

---

## 作者：Autumn_Dream (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc194_d)

**思路：**

不难看出，选中第 $1$ 个点的概率是 $\frac{1}{n}$，因为场上还有 $n$ 个点；选中第 $2$ 个点的概率是 $\frac{1}{n-1}$，因为场上还有 $n-1$ 个点;选中第 $3$ 个点的概率是 $\frac{1}{n-2}$，因为场上还有 $n-2$ 个点；以此类推。由于最坏的情况是抽了 $n-1$ 个球还没抽到，所以将 $1\sim (n-1)$ 个球的命中率相加即可。模拟相加即可。记得开 `double`。

[Code](https://www.luogu.com.cn/paste/nj8ivw1t)

---

## 作者：tsh_qwq (赞：0)

一道数学题，有一定的思想含量，~~我想了好久~~。

### 进入正题：

#### 题意：

假设有 $n$ 个点，每次从当前所在的点选择一个点与之连接并转移。\
问为了使整个图联通，需要进行多少次转移才能保证形成连通图，且**期望**的转移次数是多少。

#### 思路分析：

选中第 $s$ 条边的概率是：$\frac{1}{n - s + 1}$。

为了使图从无边的状态变为连通图，至少需要添加 $n - 1$ 条边。

为了得到图连通的期望操作次数，我们只需将从第 $1$ 条边到第 $n - 1$ 条边的概率加起来。

可得公式是 $\sum_{i=1}^{n-1} \frac{n}{i}$。

#### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
double n,ans;
int main()
{
	cin>>n;
	for(double i=1;i<=n-1;i++)ans+=(n/i);
	cout<<fixed<<setprecision(11)<<ans;
	return 0;
}
```

---

## 作者：WoodReal12 (赞：0)

## 题意简述

在一张有 $n$ 个节点的图上，高桥站在节点 $1$ 处。现在的图没有任何连边。

高桥在图连通之前，会重复执行下列操作：

- 随机选择一个点，每个点被选中的概率在每一次都是相等的，都是 $\frac{1}{n}$。
- 从当前点连一条边到选中的点。图允许重边和自环。然后，去到那个选中的点。

求出其期望操作次数。

## 思路分析

本题看似是一道图论题，其实不然。

可以把题目转换成有 $n$ 个物品，抽出第一个物品的概率是 $\frac{1}{n}$，抽出第二个物品的概率是 $\frac{1}{n-1}$，以此类推。最终答案就是把 $1$ 到 $n-1$ 每个物品被抽到的概率相加即可，即：
$$
ans=\sum_{i=1}^{n-1}\frac{i}{n}
$$

**注意**：因为精度问题，本题不能使用 float。

时间复杂度为线性。

## 代码
代码难度红。
```cpp
#include <iostream>
#include <iomanip>
#define int long long
using namespace std;
int n;
double ans=0;
signed main(){
	cin>>n;
	for(int i=1;i<n;i++)
		ans+=1.0*n/(n-i);
	cout<<fixed<<setprecision(114514)<<ans<<endl;//保留6位以上即可通过
	return 0;
}
```

---

## 作者：__Creeper__ (赞：0)

### 思路

这道题和图论没什么关系。对于 $n$ 个球，抽出一个的概率是 $\frac{1}{n}$，那么抽第二个时概率是 $\frac{1}{n - 1}$，以此类推。最坏情况下就是抽第 $n−1$ 个球是都没有抽到，所以我们就只需要把 $1$ 到 $n−1$ 每个球抽中的概率加起来就行了。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;

signed main()
{
	cout << fixed << setprecision(15);
    long double n, ans = 0;
    cin >> n;
    for ( int i = 1; i <= n - 1; i++ ) ans += n / i;
    cout << ans <<endl;
    return 0;
}
```

---

## 作者：Contain_Thunder (赞：0)

# 题意简述
有一张 $n$ 个节点的无边图，图在连通之前每次随机抽取一个点然后建边，求期望操作次数（即最大多少次）。
# 思路
这道题似乎和图论没什么关系，首先我们看 $n$ 个球抽出一个的概率是 $\frac{1}{n}$，那么抽第二个时概率是 $\frac{1}{n-1}$ 以此类推。所以最坏情况下就是抽第 $n-1$ 个球是都没有抽到，所以我们就只需要把 $1$ 到 $n-1$ 每个球抽中的概率加起来就行了。
# code
```
#include <bits/stdc++.h>
using namespace std;
int main() {
	int n;
	cin>>n;
	double ans=0.0;
	for(double i=1;i<n;i++) ans+=(double)n/(n-i);
	cout<<fixed<<setprecision(10)<<ans<<endl;
	return 0;
}

```

---

## 作者：nkrqzjc_zzz (赞：0)

### [题目链接](https://www.luogu.com.cn/problem/AT_abc194_d)

------------

### 中文题目

有一个点 $1$ 到点 $N$ 的 $N$ 顶点构成的图，高桥在顶点 $1$。现在这个图表上一条边都没有。

高桥重复以下操作。

操作：

1. （包括现在高桥所在的顶点）从 $N$ 个顶点中随机选择 $1$ 个。各顶点被选择的概率全部为 $\frac{1}{N}$，对于每个选择操作是独立的。

1. 在高桥所在的顶点和被选的顶点之间连上无向边，之后移动到被选的顶点。

请计算在合并图表之前执行的操作次数的期望值。

------------

### 分析

这道题要求你求的东西，其实已经显而易见了。我们一步步来分析。

首先，何为**期望**，学术说法如下：在概率论和统计学中，数学期望（或均值，亦简称期望）是试验中每次可能结果的概率乘以其结果的总和，是最基本的数学特征之一。它反映随机变量平均取值的大小。

那么因为选点是不断增加的，也就是说剩下的点是不断减少的，所以可得答案就是选第一个点的概率，到选第 $n-1$ 个点的概率，结束。

------------

### 代码（酷爱压行呀）

这道题，思想黄，代码红呀。

```cpp
#include<ios>//还用注释吗，自己看吧！
double a,b,i;
main(){
	scanf("%lf",&a);
    for(i=1;i<a;i++)b+=a/i;
    printf("%.12f",b);
}
```


---

## 作者：shenbairui (赞：0)

### 题目分析

本蒟蒻参考了大佬 loser_seele 的方法，采用高中数学的方法：我们这一个东西成功的概率为 $p$，则期望值次数为 $\dfrac{1}{2}p$，具体证明看[这里](https://blog.csdn.net/Emma2oo6/article/details/119392907)，继续看问题，我们设选中的顶点为 $x$，则概率为 $\dfrac{n}{n- |x| }$。我们设一开始 $x$ 为 $1$，最后为 $n$，答案就是所有的和。由于他是从一到 $n$，所以时间复杂度为 $O(n)$。上代码吧！不行，由于精度的问题，所以要用 long double，好像 double 也行，反正 float 不行就对了，保留 $12$ 位小数。

### 上代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
    long double n,ans=0;
    cin>>n;
    for(int i=1;i<=n-1;i++){
        ans+=n/i;
    }
    cout<<cout<<fixed<<setprecision(12)<<s<<endl;
    return 0;
}
```
拜拜！下期见！

---

## 作者：loser_seele (赞：0)

首先要用到高中数学的一个结论：设一个事件成功的概率为 $ p $，则期望次数为 $ \frac{1}{p} $。这个可以用高中数学的等比数列求和公式证明，不详述。

于是回到问题，设已经选中的顶点集为 $ S $，则每次操作相当于问选中一个 $ S $ 外的顶点的概率，这个概率显然为 $ \frac{n}{n-\mid S \mid} $。开始时我们有 $ \mid S \mid =1 $，最后 $ \mid S \mid=n $，所以答案即为所有期望次数的累加和，即为 $ \sum_{i=1}^{n-1} \frac{n}{i} $。为了避免精度误差建议使用 double 实现。

时间复杂度 $ \mathcal{O}(n) $，可以通过。

代码：

```cpp
#import <bits/stdc++.h>
using namespace std;
signed main() 
{
    double n,ans=0;
    cin>>n;
    for(int i=1;i<=n-1;i++)
    ans+=n/i;
    printf("%.12lf",ans);
}
```


---

