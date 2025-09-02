# [USACO21JAN] Just Stalling B

## 题目描述

Farmer John 有 $N$ 头奶牛（$1\le N\le 20$），高度为 $a_1\ldots a_N$。他的牛栏有 $N$ 个牛棚，高度限制分别为 $b_1\ldots b_N$（例如，如果 $b_5=17$，那么一头高度不超过 $17$ 的奶牛可以住在牛棚 $5$ 里）。Farmer John 有多少种不同的方式安排他的奶牛，使得每头奶牛均住在不同的牛棚里，并且使得每个牛棚的高度限制均得到满足？ 

## 说明/提示

### 样例解释 1

在这个例子中，我们不能将第三头奶牛安排到第一个牛棚里，因为 $3=a_3>b_1=2$。类似地，我们不能将第四头奶牛安排到第一或第三个牛棚里。一种符合高度限制的安排方式为将奶牛 1 安排到牛棚 1，奶牛 2 安排到牛棚 2，奶牛 3 安排到牛棚 3，奶牛 4 安排到牛棚 4。

### 测试点性质

- 测试点 $1-5$ 满足 $N\le 8$。
- 测试点 $6-12$ 没有额外限制。

## 样例 #1

### 输入

```
4
1 2 3 4
2 4 3 4```

### 输出

```
8```

# 题解

## 作者：OIerWu_829 (赞：4)

## [题目传送门](https://www.luogu.com.cn/problem/P9942)

## 思路

**贪心策略：优先给高度高的奶牛安排牛棚。**

先遍历每头牛，计算其可安排的牛棚数，乘到方案总数 $ans$ 中。

再遍历每个牛棚，统计可安排第 $i$ 头牛的牛棚数 $cnt$。

但前 $i-1$ 头牛已经安排了 $i-1$ 个牛棚，所以 $cnt$ 需要减去 $i-1$。

```cpp
#include <iostream>
#include <algorithm>
using namespace std;
int a[30], b[30];
int main()
{
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) cin >> b[i];
	sort(a + 1, a + 1 + n, greater<int>()); // 从大到小排序
	long long ans = 1;
	for (int i = 1; i <= n; i++) {
		int cnt = 0; // 计算每头牛可分配的牛棚数量
		for (int j = 1; j <= n; j++)
		    if (b[j] >= a[i]) cnt++;
		cnt -= (i - 1);
		ans *= cnt;
	}
	cout << ans << endl;
	return 0;
}
```


---

## 作者：juruo_zhanshen (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/P9942)
请先重新阅读一边题目。

## 正文内容
本题与 GESP202312 四级 的 T2 有异曲同工之妙。

我们有一个思路，就是把序列 $a$ 和 $b$ 按降序排序，然后遍历每一头牛，用一个数组 $flag$，表示每一个牛棚是否已被占用。

遍历每一个牛棚，如果牛棚高度 $\ge$ 牛的高度，并且这个牛棚并没有被占用。根据[乘法原理](https://baike.baidu.com/item/%E4%B9%98%E6%B3%95%E5%8E%9F%E7%90%86/7538447)，算出每一头牛可以住的牛棚数，然后相乘，就是最后的结果。

注意：每次找到最高的 $\ge$ 当前牛高度的牛棚，这样可以保证不会在有可以把所有牛都住进牛棚的方案，但找不到的情况。找到就可以把这个牛棚标记一下，然后 `break`。

下面是 $\color{green}{\text{Accepted}}$ 的 `main` 函数代码，$\text{just no \color{red}{read} and write}$
```cpp
int main ( int argc, char *argv[] )
{

    int n;
    read(n);
    int a[n + 5];
    int b[n + 5];
    int flag[n + 5] = {0};
    for (int i = 1; i <= n; i++) read(a[i]);
    for (int i = 1; i <= n; i++) read(b[i]);
    long long ans = 1;
    sort(a + 1, a + n + 1, cmp);
    sort(b + 1, b + n + 1, cmp);
    for (int i = 1; i <= n; i++){
        int cnt = 0;
        for (int j = 1; j <= n; j++)
            if (flag[j] == 0 && b[j] >= a[i])
                cnt++;
        for (int j = 1; j <= n; j++){
            if (flag[j] == 1) continue;
            else{
                flag[j] = 1;
                break;
            }
        }
        ans *= cnt;
    }
    write(ans);
    puts("");
    return 0;
}               /* ----------  end of function main  ---------- */
```

---

## 作者：luogu10086 (赞：2)

[传送门](https://www.luogu.com.cn/problem/P9942)

### PART 1

题目大意：

有 $N$ 头牛以及 $N$ 个牛棚，问有多少种能把牛放进合适的牛棚中（放入牛棚中的牛的身高小于牛棚的高度）的方案。

-------------------

### PART 2

整体思路：


因为高度的问题，我们要从**最高**的牛看起，看这头牛有多少个牛棚可以住；再看第二高的牛，判断又有多少牛棚可以住······

一头牛可住的牛棚数是比它高的所有牛棚数减去比它高的牛的个数（代码如下）。   

```cpp
for(int j = n-1-x;j >= 0;j --)
    if(b[j]>=a[i])
        cnt++;
```

其中 $x$ 表示比这头牛高的牛的个数，$a_i$ 是当前牛的高度，$b_j$ 是牛棚的高度，$cnt$ 是可住的牛棚数。

而所有方案数的计算方式需要乘法原理，也就是说，答案 $ans$ 每次都要变为 $ans \times cnt$。

代码呈现出来就是：`ans*=cnt`。


**举个例子**：                      
-   有 $5$ 头牛与 $5$ 个牛棚。  
    牛的高度为：$1$，$5$，$2$，$8$，$9$。  
    牛棚的高度为：$1$，$5$，$9$，$9$，$9$。


- 我们一眼便可以看出有 $12$ 种方案（如下）。

   ```
    15289 15298 15829 15892
    15928 15982 12589 12598
    12958 12985 12859 12895
    ```

- 我们再推出这个例子的式子：$3 \times 2 \times 2 \times 1 \times 1 = 12$。两个答案符合，验证了我们的思路。


------------------------

### PART 3

代码实现：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,ans=1,cnt;
ll a[30],b[30];//牛与牛棚
int main(){
    cin >> n;
    for(int i = 0;i < n;i ++)cin>>a[i];//牛
    for(int i = 0;i < n;i ++)cin>>b[i];//牛棚
    sort(a,a+n);//排序
    sort(b,b+n);//排序
    int x = 0;
    for(int i = n-1;i >= 0;i --){
        cnt=0;//归零
        for(int j = n-1-x;j >= 0;j --)if(b[j]>=a[i])cnt++;
        ans*=cnt;//乘上可以住的牛棚数
        x++;
    }
    cout<<ans;//输出
}
```

---

## 作者：TruchyR (赞：1)

**UPD:感谢 @continueOI 指正题解最后错误的时间复杂度。**  
不理解为什么 $n\leq20$。  
首先我们将 $a$ 和 $b$ 从小到大排好序。  
可以设 $p_i$ 表示第 $i$ 个牛棚可以容纳编号为 $1\sim p_i$ 的奶牛。  
容易发现，$p$ 也是不降的，使用指针可以 $O(n)$ 求出。  
再设 $f_i$ 表示把 $n$ 头牛中的 $i$ 头住进前 $i$ 个牛棚的方案数：  
- 显然，前面已经选了 $(i-1)$ 头牛。
- 而本来这个牛棚有 $p_i$ 种选择且一定包含这 $(i-1)$ 头牛。
- 所以现在这个牛棚可以让 $(p_i-i+1)$ 头牛中的一头住进去。
- $f_0=1,f_i=(p_i-i+1)f_{i-1}$。


$f_n$ 就是我们要求的答案，加上排序后，时间复杂度 $O(n\log{n})$。
```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;int read();
int n,p,a[25],b[25],res=1;
signed main(){
	n=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=n;i++) b[i]=read();
	sort(a+1,a+1+n);sort(b+1,b+1+n); 
	for(int i=1;i<=n;i++){
		while(a[p+1]<=b[i] && p<n) p++;
		res*=(p-i+1);
	}cout<<res;
	return 0;
}
int read(){
	int Ca=0;char Cr=' ';int Cf=1;
	while(Cr<'0' || Cr>'9'){Cr=getchar();if(Cr=='-'){Cf=-1;}}
	while(Cr>='0' && Cr<='9'){Ca=Ca*10+Cr-48;Cr=getchar();}
	return Ca*Cf;
}
```


---

## 作者：lqsy002 (赞：0)

## 题目大意
将 $n$ 头奶头放进 $n$ 间牛棚内，保证奶牛的高度不超过牛棚的高度，计算方法总数。[题目链接](https://www.luogu.com.cn/problem/P9942)。

## 解题思路
1. 排序后，最高的奶牛受限最多，我们从最高的奶牛开始计算，每头奶牛可以有多少间牛棚可以选择，将所有奶牛的选择性乘起来就是答案。
2. 当前这头牛，可以住在大于等于自己身高的牛棚里，当然需要排除掉其他牛已经占据的牛棚，同时，最高的牛我们自然也安排住进最高的牛棚里。

## 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long ans=1;
int a[30],b[30],flag[30],n;
int main(){
	cin>>n;
	for(int i=1;i<=n;++i)
		cin>>a[i];
	for(int i=1;i<=n;++i)
		cin>>b[i];
	sort(a+1,a+n+1);
	sort(b+1,b+n+1);
	for(int i=n;i>=1;--i){
		int cnt=0;
		for(int j=n;j>=1;--j)
			if(!flag[j]&&b[j]>=a[i])
				cnt++;
		for(int k=n;k>=1;--k)
			if(flag[k])
				continue;
			else{
				flag[k]=1;
				break;
			}
		ans*=cnt;
	}
	cout<<ans;
	return 0;
}
```

---

