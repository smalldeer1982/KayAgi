# [ABC060C] Sentou

## 题目描述

在一个公共澡堂里，有一个淋浴器。在按下开关时，淋浴器将会开始运作，在 $T$ 秒内一直流出热水。

如果你在淋浴器运作的情况下时按下开关，水就会从当前时间开始继续运作 $T$ 秒，而不是让淋浴器多运作 $T$ 秒。

在这个淋浴间前，有 $N$ 个人按下开关。第 $i$ 个人在第 $1$ 个人按下开关后的第 $t_i$ 个秒按下开关。请求出淋浴器运作的总时间。

## 说明/提示

- $ 1\ \leq\ N\ \leq\ 200,000 $
- $ 1\ \leq\ T\ \leq\ 10^9 $
- $ 0\ =\ t_1\ <\ t_2\ <\ t_3\ <\ ,\ ...,\ <\ t_{N-1}\ <\ t_N\ \leq\ 10^9 $
- $ T $ 和 $ t_i $ 都是整数。

## 样例 #1

### 输入

```
2 4
0 3```

### 输出

```
7```

## 样例 #2

### 输入

```
2 4
0 5```

### 输出

```
8```

## 样例 #3

### 输入

```
4 1000000000
0 1000 1000000 1000000000```

### 输出

```
2000000000```

## 样例 #4

### 输入

```
1 1
0```

### 输出

```
1```

## 样例 #5

### 输入

```
9 10
0 3 5 7 100 110 200 300 311```

### 输出

```
67```

# 题解

## 作者：wimg6_ (赞：2)

# AT2555 题解

题目指标 [[ARC073A] Sentou](https://www.luogu.com.cn/problem/AT2555) .

该文章同步发表于 [我的博客](https://www.luogu.com.cn/blog/Kingson123456/) 内。

审核一经通过，他人不得盗用博客。若未通过，引用时需注明出处，并私信作者。

### 正解

其实这题就是一道非常适合初学者做的大模拟。

我们可以将 $p_i$ 设为第 $i$ 个人对水产生影响的时刻。

于是我们回到文章中进行阅读，可以发现：

$$p_i=t_i+T$$

同样的，对其进行分类讨论即可。

1. 如果水已经停了，则用户对水的贡献为 $T$ .

2. 如果水还没有停，我们要进行去重操作：

$$t_i-(p_{i-1}-T)$$ 

### 代码

```
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
long long n,q,t,s,p;
int main()
{
	scanf("%lld%lld",&n,&t);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&q);
		if(q<=p) s+=t+q-p;
		else s+=t;
		p=t+q;
	}
	return !printf("%lld",s);
}
```


---

## 作者：little_rubbish (赞：0)

## 思路
输入后排序一遍，然后根据题意进行模拟。
#### 如何进行模拟呢
记录下上一个人按下开关后淋浴器关闭的时间，如果与这次开始的时间有冲突（开始时，淋浴器还处于开着的状态）的话，只加上没重复（多出来）的部分。否则的话，就直接加上 $T$（淋浴器每次流出水时间）。
#### 如何计算没重复的部分
我们记上一次淋浴器关闭的时间为 $sum$，淋浴器每次流出水的时间为 $T$，此次开始的时间为 $t_i$。

我们便可以推出没重复的部分为： $T-(sum-t_i)$。

其中 $sum-t_i$ 表示重复的部分，将淋浴器每次流出水的时间 $T$ 减去重复的部分便是没重复的部分。
## 无注释代码
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,t,ans,sum,a[200001];
int main(){
	cin>>n>>t;
	for(int i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+n+1);
	ans=t;
	sum=t+a[1];
	for(int i=2;i<=n;i++){
		if(a[i]<sum)ans+=t-(sum-a[i]);
		else ans+=t;
		sum=a[i]+t;
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：hyc1026 (赞：0)

直接定义一个计数器累加时间，模拟即可。

如果水停了，计数器累加 $T$。

如果水没停，计数器累加 $T-finish+a_i$，其中 $finish$ 是在没按的情况下，水应该停的时间。

AC Code:

```cpp
#include <bits/stdc++.h>
#define int long long //其实不开 long long 也没事
using namespace std;

int a[200001];

signed main()
{
    int n,t;
    cin >> n >> t;
    for(int i=1; i<=n; i++) cin >> a[i];
    int sum = 0; //计数器
    int finish = 0; //finish
    for(int i=1; i<=n; i++)
    {
        if(finish <= a[i]) sum += t; //停了
        else sum += (t-finish+a[i]); //没有
        finish = a[i] + t; //finish 更新
    }
    cout << sum << endl;
}
```

---

## 作者：Black_Porridge (赞：0)

### 解题思路：

这题真就快乐模拟就行了。每次按开关的时候再覆盖就行了。具体一些细节见代码

### 代码实现：
```
#include <iostream>
using namespace std;

const int N = 5100;
int n, t;

int a[N];

int main()
{
    cin >> n >> t;
    for(int i = 0; i < n; i++)
        cin >> a[i];
    int ans = t, k = t;//ans表示答案 
    //k表示上一个人按下按钮之后水会持续到什么时候停
    for(int i = 1; i < n; i++)
    {
        if(a[i] <= k)//如果这时候水还没停
        {
            ans += t - (k - a[i]);//就加上没有重合的部分
            k = a[i] + t;
        }

        else//否则就直接加上时间
        {
            ans += t;
            k = a[i] + t;
        }
    }
    cout << ans << endl;

    return 0;
}


---

