# Abundant Resources

## 题目描述

[problemUrl]: https://atcoder.jp/contests/nikkei2019-final/tasks/nikkei2019_final_a

東西に細長い土地があります。 この土地は、$ N $ 個の区画が東西に並んだ形をしており、西から $ i $ 番目の区画は区画 $ i $ と呼ばれます。

それぞれの区画には地下資源があることがわかっており、区画 $ i $ の資源埋蔵量は $ A_i $ です。

$ 1 $ 以上 $ N $ 以下のそれぞれの整数 $ k $ について、次の問題の答えを求めてください。

- 連続する $ k $ 個の区画を選んだとき、それらの区画の資源埋蔵量の総和として考えられる最大値はいくらか。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 3000 $
- $ 1\ \leq\ A_i\ \leq\ 10^9 $
- 入力される値はすべて整数である。

### Sample Explanation 1

$ k=1 $ のとき、区画 $ 1 $ を選ぶと資源埋蔵量の総和は $ 4 $ となり、これが最大です。 $ k=2 $ のとき、区画 $ 3,4 $ を選ぶと資源埋蔵量の総和は $ 3+3=6 $ となり、これが最大です。 $ k=3 $ のとき、区画 $ 1,2,3 $ を選ぶと資源埋蔵量の総和は $ 4+1+3=8 $ となり、これが最大です。 $ k=4 $ のとき、区画 $ 1,2,3,4 $ を選ぶと資源埋蔵量の総和は $ 4+1+3+3=11 $ となり、これが最大です。

## 样例 #1

### 输入

```
4
4 1 3 3```

### 输出

```
4
6
8
11```

## 样例 #2

### 输入

```
5
10 20 30 40 50```

### 输出

```
50
90
120
140
150```

## 样例 #3

### 输入

```
10
61049214 115057849 356385814 932678664 505961980 877482753 476308661 571830644 210047210 873430114```

### 输出

```
932678664
1438640644
2316123397
2792432058
3364262702
3720648516
4447740026
4804125840
4919183689
4980232903```

# 题解

## 作者：yzm0325 (赞：4)

额……这题因为一行要输入多个正整数，Python 不大方便，还是回归 C++ 吧。

乍一看，直接打暴力就行。一共三重循环：

第一重控制连续的项数。

第二重控制目前枚举的区间左端点和右端点。

第三重求这个区间所有数的和。

根据这个思路，写出代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, a[3010];
int main() {
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= n; i++) {
        long long maxn = 0; // 要开 long long，3000 个 1e9 级别的相加不炸 int 才怪！
        for(int l = 1, r = i; r <= n; l++, r++) {
            long long sum = 0; // 和上面一样。
            for(int j = l; j <= r; j++) sum += a[j];
            maxn = max(sum, maxn); // 更新最大值。
        }
        cout << maxn << endl; // 注意换行！
    }
    return 0;
}
```

本来觉得三次方的时间复杂度支撑不住 $n=3000$ 的数据，结果竟然卡着时间限制过去了。用时最长的测试点用了接近两秒。

那么怎么稳过这道题呢？我们需要用到**前缀和**这个算法。

我们定义 $a_n$ 的前缀和为 $\displaystyle \sum_{i=1}^na_i$。这样，我们可以用 $O(n)$ 的时间复杂度求出一个数组的前缀和。

```cpp
int n, a[3010];
long long p[3010];
for(int i = 1; i <= n; i++)
    p[i] = a[i] + p[i - 1];
```

那前缀和的作用在哪里呢？我们如果要求这个序列一个区间的区间和（比如下图的红色部分）：

![](https://cdn.luogu.com.cn/upload/image_hosting/yjgaxogy.png)

我们就可以看作右端点的前缀和减去左端点的前缀和。

![](https://cdn.luogu.com.cn/upload/image_hosting/52m8vcah.png)

这样，就在 $O(1)$ 的时间复杂度里求出了区间和。

用到这个题里，就是用前缀和像上面一样优化了最后一个循环。优化后的代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, a[3010];
long long p[3010]; // 开 long long，与上面同理。
int main() {
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= n; i++) // 预处理前缀和。
        p[i] = a[i] + p[i - 1];
    for(int i = 1; i <= n; i++) {
        long long maxn = 0;
        for(int l = 0, r = i; r <= n; l++, r++) {
            long long sum = p[r] - p[l]; // 提前求了前缀和，直接用两端点的前缀和相减。
            maxn = max(sum, maxn);
        }
        cout << maxn << endl;
    }
    return 0;
}
```

完结撒花！

---

## 作者：Acceptedit_ (赞：2)

挑战最短题解！

正常打暴力 $O(n^3)$ 的复杂度不保证过，要用前缀和优化。

首先做一个前缀和预处理，方便后面的区间求和。

然后只要两重循环，第一重循环枚举找的区间长度，第二重循环把控目前枚举的区间（枚举每组左右端点）。而求区间和的任务因为有前缀和的预处理，只需要用两端点的前缀和相减即可，然后更新最大值。

值得注意的是：$b$ 数组和 $sum,maxn$ 变量都需要开 `long long`，因为它们（某项）的最大值可以达到 $3 \times 10^{12}$，会炸 `int`。

AC 代码：

```cpp
#include <bits/stdc++.h>
int n, a[3010]; // n 如题，a 是原数组。
long long b[3010], sum; // b 是前缀和数组，sum 是每次枚举区间的区间和。
int main() {
    std::cin >> n;
    for(int i = 1; i <= n; i++) std::cin >> a[i];
    for(int i = 1; i <= n; i++) b[i] = a[i] + b[i - 1]; // 做前缀和。
    for(int i = 1; i <= n; i++) {
        long long maxn = 0; // 记录区间和的最大值。
        for(int l = 0, r = i; r <= n; l++, r++) sum = b[r] - b[l], maxn = std::max(sum, maxn); // 预处理的作用。
        std::cout << maxn << "\n"; // 要换行。
    } return 0; // 虽然最短题解但 return 0; 好习惯，还是要加的！
}
```


---

## 作者：foryou_ (赞：1)

主要思路：**暴力枚举+前缀和**。

首先，在读入 $a$ 数组时，顺便算出 $a$ 的前缀和数组 $b$，计算公式为 $b_i=b_{i-1}+a_i$。

然后直接枚举题目中的 $i$，对于每一个 $i$，枚举长度为 $i$ 的区间 $[l,r]$，$O(1)$ 地求出每个区间的前缀和并其中的取最大值输出即可。

时间复杂度 $O(n^2)$，可以接受。

Tips：**不开 `long long` 见祖宗**。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int n;
int a[3031],b[3031];

signed main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++) cin>>a[i],b[i]=b[i-1]+a[i]; //读入 a 数组并求出前缀和数组 b
    for(int i=1;i<=n;i++){
        int sum=0;
        for(int l=1,r=i;r<=n;l++,r++) sum=max(sum,b[r]-b[l-1]); //枚举所有长度为 i 的区间并求出区间和最大值
        cout<<sum<<'\n';
    }
    return 0;
}
```

---

## 作者：huyixuanpi (赞：1)

## 思路
这题其实很水。

乍眼一看就是“暴力”，代码很短，时间复杂度较高，但勉强能卡过数据。

需要注意几点：

1. 三重循环边界看好，注意代码中标记的注释。
2. 循环过程中要将统计变量清零。
3. 因为 $A_i \le 10^9$，所以累加和与答案要开 `long long`。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[3030];
long long tot,ans;/*注意开 long long*/
int main()
{
	cin>>n;
	for(int i = 1;i<=n;i++)
	{
		cin>>a[i];
	}
	for(int i = 1; i <= n;i ++) 
	{
		tot=0,ans=0;/*注意初始化*/ 
		for(int j = 1;j <= n-i+1 /*注意这里是 n=i+1，具体原因可以自己实操一下*/;j ++)
		{
			tot=0;/*注意初始化*/ 
			for(int k = j; k </*注意这里是 < 而不是 <= */ j+i; k ++)
			{
				tot+=a[k];//累加和 
			}
			ans=max(ans,tot);/*取最值*/ 
		}
		cout<<ans<<endl;/*别忘了换行！！！*/
	}
	return 0;
}

```


---

## 作者：Pink_Cut_Tree (赞：1)

对于暴力枚举的代码，要写三重循环，时间复杂度是 $O(n^3)$，对于最大数据（$3000$），$O(n^3)$ 的时间复杂度似乎不能胜任。

我们要上一个新的算法：**前缀和**！

关于前缀和，可以参考一下我的[前缀和笔记](https://www.luogu.com.cn/blog/PCT2506/qian-zhui-hu-zhong-yi-post)。

这里再讲一下前缀和。请**务必！务必！认真听！**

我们令读入数据的数组名为 $a$，前缀和数组名为 $sum$。

普通的读入过程：

```cpp
for(int i=1;i<=n;i++){
	cin>>a[i];
}
```

**前缀和读入过程：**

```cpp
for(int i=1;i<=n;i++){
	cin>>a[i];
	b[i]=b[i-1]+a[i];
}
```

在读入的时候就顺便把前缀和生成了。真是好用！

~~食用~~**使用技巧：**

如果我们要求 `a[3]+a[4]+a[5]` 的值，该怎么办呢？

![](https://cdn.luogu.com.cn/upload/image_hosting/9f46v1u4.png)

这一段的区间和，就是右端点的前缀和减去左端点的前缀和。

如：求 $x \sim\ y$ 的区间和就可以用 `sum[y]-sum[x-1]` 来解决。

所以，直接上代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[3005];
#define LL long long //记得开long long
LL sum[3005];
int main() {
    cin>>n;
    for(int i=1;i<=n;i++){
    	cin>>a[i];
    	sum[i]=a[i]+sum[i-1]; //生成前缀和
	} 
	for(int i=1;i<=n;i++){ //这曾循环不能省。
    	LL maxx=0;
    	for(int l=0,r=i;r<=n;l++,r++){ //逐一枚举
    		LL cnt=sum[r]-sum[l];
    		maxx=max(cnt,maxx);
		}
		cout<<maxx<<"\n";
	}
return 0;
}
```

时间复杂度直接被压缩到 $O(n^2)$，是可以过的。

完结撒花！

---

## 作者：rainygame (赞：0)

> 本题可以不需要前缀和。

首先本题是对于每个 $i=1,2,\dots,n$，求 $\max\limits_{l=1}^{n-i+1}\sum\limits_{j=l}^{l+i-1}A_j$。

那么我们首先有一层循环枚举 $i$，然后再用第二层循环枚举 $l$，如果我们再用第三层循环枚举 $j$ 的话，$O(n^3)$ 可能会超时。

所以我们考虑如何求出 $\sum\limits_{j=l}^{l+i-1}A_j$，发现这个等于 $\sum\limits_{j=l-1}^{l+i-2}A_j-A_l+A_{l+i-1}$。所以我们考虑先求出 $\sum\limits_{j=1}^iA_j$，然后再在枚举 $l$ 的时候顺便转换一下。

其实代码更能表达出我的意思：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define MAXN 3001

int n, ans, res;
int a[MAXN];

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for (int i(1); i<=n; ++i) cin >> a[i];

    for (int i(1); i<=n; ++i){
        ans = res = 0;
        for (int j(1); j<=i; ++j) res += a[j];
        ans = max(ans, res);
        for (int j(2); j+i-1<=n; ++j){
            res -= a[j-1];
            res += a[j+i-1];
            ans = max(ans, res);
        }
        cout << ans << '\n';
    }

    return 0;
}

```


---

## 作者：GFyyx (赞：0)

## 解题思路
暴力相加求和 $\Theta(n^3)$ 的时间复杂度超时，考虑优化。

~~所以要用到数列分块，线段树，ST 表。~~

其实这仅仅只是一道前缀和预处理的裸题。

本题运用前缀和不需查询原数组，与其他题解不同，这里介绍滚动数组卡空间。

正常我们使用额外的 $s$ 数组记录前缀和，有 $s_i=s_{i-1}+a_i$。

但是当空间紧张时又不需维护原数组，我们可以直接使用原来的 $a$ 数组记录前缀和。

其中我们新读入 $a_i$ 时，$a_{i-1} = \sum\limits_{x=1}^{i-1}{a_{x}}$，于是有 $a_i = \sum\limits_{x=1}^{i}{a_{x}} = a_{i-1}+a_i$。

这样利用原数组滚动抹去原数据记录前缀和，省去了一个数组，在二维或三维前缀和的题目中使用效果更显著。

MLE 的痛，[血的教训](https://www.luogu.com.cn/problem/P2280)，好好学。

## 上代码（附有注释）
代码很短，码风比较奇特，别直接抄。
```cpp
#include<stdio.h>
#define F for(register int i=1; i<=n; i++)
using namespace std;
long long n,a[114514];
int main(){
	scanf("%lld",&n);
	F scanf("%lld",&a[i]),a[i]+=a[i-1];//滚动前缀和
	long long ans=-1;
	F{for(register int j=i; j<=n; j++)//枚举长度为i,以j结尾的区间。
		ans=a[j]-a[j-i]<=ans?ans:a[j]-a[j-i];
	  printf("%lld\n",ans);//输出答案(AT要打\n)
	}
	return 0;
}
```

---

## 作者：回声之歌 (赞：0)

第一重循环枚举区间长度 $i$，第二重循环枚举任意长度 $i$ 区间的左端 $l$ 和右端 $r$，第三重循环遍历区间 $\left[l, r \right]$ 并计和维护最大值。显然，对于 $1 \le n \le 3000$ 的数据，这样 $O \left(n^3 \right)$ 的思路不稳妥。不难发现，确定 $l, r$ 后，计算区间 $\left[l, r \right]$ 和的过程消耗大量时间，考虑对此过程进行优化，则考虑前缀和思想。

对于 $\forall i \in \left[1, n \right]$，记 $a_i$ 为前 $i$ 项之和，并计算所有 $a_i$，时间复杂度为 $O \left(n \right)$；则对于区间 $\left[l, r \right]$，可通过 $a_r - a_{l - 1}$ 计和，时间复杂度为 $O \left(1 \right)$；则整体复杂度降至 $O \left(n^2 \right)$，成为比较优秀的思路。

参考代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n, mx, a[3005];
int main() {
	scanf("%lld", &n);
	for (int i = 1; i <= n; scanf("%lld", &a[i]), a[i] += a[i - 1], i++);
	for (int i = 1; i <= n; mx = 0, i++) {
		for (int j = 0; j <= n - i; mx = max(mx, a[j + i] - a[j++]));
		printf("%lld\n", mx);
	}
	return 0;
}
```

---

## 作者：Loser_Syx (赞：0)

## 思路

由于要求**连续**的 $i$ 个数的最大值，那么第一眼想到前缀和预处理，用了前缀和维护，每次的复杂度能达到 $O(1)$，那么就可以省去一个暴力枚举的循环（$O(N^3)$ 暴力可能会超时），接下来只要依次枚举长度再求前缀最大值就好了。

这样的复杂度 $O(N^2)$，不用怕超时。

最后，十年 OI 一场空，不开 `long long` 见祖宗。

## 代码

```cpp
#include<bits/stdc++.h>
long long a[114514],s[1919810];
main(){
    int n;
    std::cin >> n;
    for(int i = 1; i <= n; ++i){
        std::cin >> a[i];
        s[i] = s[i-1] + a[i];//前缀和预处理
    }
    for(int len = 1; len <= n; ++len){
        long long ans = 0;
        for(int i = 1; i <= n-len+1; ++i) ans = std::max(ans, s[i+len-1] - s[i-1]);//求最大前缀和
        std::cout << ans << std::endl;
    }
    return 0;
}
```

---

## 作者：PineappleSummer (赞：0)

[$\color{orangered}\text{题目传送门}$](https://www.luogu.com.cn/problem/AT_nikkei2019_final_a)

本篇题解讲述两种做法。
## 做法一
暴力枚举，三重循环。

从 $1$ 到 $n$ 枚举 $i$，再从第 $1$ 项到第 $n-i+1$ 项枚举 $j$，再从第 $j$ 项到第 $j+i-1$ 项枚举 $k$，将 $a_k$ 累加到 $sum$ 上。

对于每个 $j$，比较 $maxn$ 与 $sum$ 的大小，将 $maxn$ 更新为较大值。

对于每个 $i$，输出 $maxn$。

关键代码:
```cpp
for(int i=1;i<=n;i++)//从1到n枚举i
{
	long long maxn=-1;//maxn的初值定为-1
	for(int j=1;j<=n-i+1;j++)//从1到n-i+1枚举j
	{
		long long sum=0;//sum的初值定为0
		for(int k=j;k<=j+i-1;k++) sum+=a[k];//累加a[k]到sum上
		maxn=max(maxn,sum);//取较大值
	}
	printf("%lld\n",maxn);//输出maxn
}
```

## 做法二
前缀和，双重循环。

用 $s_i$ 表示 $a$ 数组前 $i$ 项的和。
```cpp
for(int i=1;i<=n;i++)
{
	scanf("%d",&a[i]);
	s[i]=s[i-1]+a[i];
}
```

从 $1$ 到 $n$ 枚举 $i$，再从第 $1$ 项到第 $n-i+1$ 项枚举 $j$，从 $j$ 到第 $j+i-1$ 项的和为 $s_{j+i-1}-s_{j-1}$，所以将 $maxn$ 更新为 $maxn$ 与 $s_{j+i-1}-s_{j-1}$ 之间的较大值。

关键代码：
```cpp
for(int i=1;i<=n;i++)//从1到n枚举i
{
	long long maxn=-1;//maxn的初值定为-1
	for(int j=1;j<=n-i+1;j++) maxn=max(maxn,s[j+i-1]-s[j-1]);
   //从1到n-i+1枚举j，将maxn更新为maxn与[j+i-1]-s[j-1]之间的较大值
	printf("%lld\n",maxn);//输出maxn
 }
```


------------

**注意事项：不管是暴力做法还是前缀和做法，$maxn$ 都要开 `long long`。**

---

## 作者：CEFqwq (赞：0)

本题可以暴力枚举，但有注意点：

1. $10^9 \times 3 \times 10^3$ 会爆 `int`，要开 `long long`。

2. 存放最大值的变量尽量开小，一般 `INT_MIN`，特殊时候可以开 $-(2^{63}-1)$。

这样就好写了：

```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,a[3005];
int main(){
	cin>>n;
	for(int i=0;i<n;i++)cin>>a[i];
	for(int i=0;i<n;i++){
	    long long mx=INT_MIN;//将mx设置得足够小
	    for(int j=0;j<=n-i+1;j++){
	        long long s=0;
	        for(int k=j;k<=j+i;k++)s+=a[k];//求和
	        mx=max(mx,s);
	    }
	    cout<<mx<<'\n'; //输出最大值
	}
}
```

---

## 作者：__delta_epsilon__ (赞：0)

## 题目大意

给定 $N$ 和长度为 $N$ 的数组 $A$，求在 $A$ 数组中选取连续的 $i$ 项之和的最大值。（$i=1,2,\cdots,N$）

## My thoughts

> 暴力出奇迹。

没想到这题这么水，直接暴力枚举即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int N, A[3020];
signed main(){
	cin >> N;
	for(int i = 1; i <= N; i++) cin >> A[i];
	for(int i = 1; i <= N; i++) {
	    int maxx = -1; // 将最大值设为-1
	    for(int j = 1; j <= N - i + 1; j++){ // 遍历每一种可能的初始值
	        int sum = 0; // 计算总和
	        for(int k = j; k <= j + i - 1; k++){ // 遍历这i个元素
	            sum += A[k]; // 累加
	        }
	        maxx = max(maxx, sum); // 求最大值
	    }
	    cout << maxx << endl; 
	}
	return 0;
}
```

时间复杂度（不标准写法） $ O\left(\dfrac{N(N+1)(N+2)}{6}\right)$。理论上来说，$N=3000$ 是会超时的，但因为这题太水，仍然是卡过了。

---

