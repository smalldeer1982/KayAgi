# Difference Operations

## 题目描述

You are given an array $ a $ consisting of $ n $ positive integers.

You are allowed to perform this operation any number of times (possibly, zero):

- choose an index $ i $ ( $ 2 \le i \le n $ ), and change $ a_i $ to $ a_i - a_{i-1} $ .

Is it possible to make $ a_i=0 $ for all $ 2\le i\le n $ ?

## 说明/提示

In the first test case, the initial array is $ [5,10] $ . You can perform $ 2 $ operations to reach the goal:

1. Choose $ i=2 $ , and the array becomes $ [5,5] $ .
2. Choose $ i=2 $ , and the array becomes $ [5,0] $ .

In the second test case, the initial array is $ [1,2,3] $ . You can perform $ 4 $ operations to reach the goal:

1. Choose $ i=3 $ , and the array becomes $ [1,2,1] $ .
2. Choose $ i=2 $ , and the array becomes $ [1,1,1] $ .
3. Choose $ i=3 $ , and the array becomes $ [1,1,0] $ .
4. Choose $ i=2 $ , and the array becomes $ [1,0,0] $ .

In the third test case, you can choose indices in the order $ 4 $ , $ 3 $ , $ 2 $ .

## 样例 #1

### 输入

```
4
2
5 10
3
1 2 3
4
1 1 1 1
9
9 9 8 2 4 4 3 5 3```

### 输出

```
YES
YES
YES
NO```

# 题解

## 作者：Dry_ice (赞：2)

[cnblogs浏览](https://www.cnblogs.com/dry-ice/p/cf1708a.html)

[cf题链](https://codeforces.ml/problemset/problem/1708/A) [luogu题链](https://www.luogu.com.cn/problem/CF1708A)

> 这个A题**相对**较难分析。

## Description
目标结果：经过若干次 $a_i=a_i-a_{i-1},i\in\left[2,n\right]\cap\mathbb{Z}$ 的差分操作，使 $\forall a_i=0,i\in\left[2,n\right]\cap\mathbb{Z}$。
答案：返回能否达成目标结果。

## Analysis
我们分数列中的各个数分析。

对于 $a_2$，要使其为 $0$，由于 $a_2$ 只能靠 $a_1$ 来修改，故当且仅当 $a_1|a_2$ 时才可操作。

对于 $a_3$，只能靠 $a_2$ 来修改，若仅考虑原始的 $a_2$，则 $a_2|a_3$，但是由于 $a_2$ 可以被 $a_1$ 修改且满足 $a_1|a_2$，于是只需使 $a_1|a_3$ 即可使 $a_3=0$。

其余同理，故对于原始序列，当且仅当 $\forall a_1|a_i,i\in\left[2,n\right]$ 返回 ```YES```；其他情况均返回 ```NO```。

样例均可作为例子进行验证，模拟较为简单，此处不再赘述。

单组数据时间复杂度 $\mathcal{O}(n)$，可以在线处理也可离线处理。

## Code
本代码以离线处理为例。

```cpp
#include <stdio.h>
const int N = 105;
int n, a[N];
int main(void) {
    int t;
    for (scanf("%d", &t); t--; ) {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
        bool flag = true;
        for (int i = 2; i <= n; ++i)
            if (a[i] % a[1]) flag = false;
        puts (flag ? "YES" : "NO");
    }
    return 0;
}
```

## The end. Thanks.

---

## 作者：Jeremiahy (赞：2)

### 题意

给你一个数列，每次可以将 $a_i$ 变为 $a_i-a_{i-1}$，问能否将 $a_2$ 到 $a_n$ 都变成 $0$？

# 分析

首先，$a_2$ 想要变成零，当且仅当 $a_1$ 是 $ a_2$ 的约数，而对于 $a_3$ 想要变成零，变化前或变化后的 $a_2$ 就得是 $a_3$ 的约数。

那么，是用变化前还是变化后的呢？显然是变化后的。因为我们可以将它们分解为质因数，$a_2$ 所含质因数越少，越有可能成为 $a_3$ 的约数。

因为 $a_2$ 是 $a_1$ 的倍数，所以我们将 $a_2$ 可以变成 $a_1$，那么 $a_3$ 就也是 $a_1$ 的倍数。

以此类推，此题有解当且仅当 $a_2,a_3,\dots,a_n$ 都是 $a_1$ 的倍数才行，所以一个个检查过去就可以。

具体程序实现里，我们可以将 $a$ 数组读入后再一个个判定，遇到不合规的就 ```break```，然后输出。

当然也可以每次只读一个 $a$，节省空间，但需要注意的一个坑点是不能立即 ```break```，要把 $a$ 读完才行。

#### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t, n, a, a1;
bool flag;
signed main() {
	ios::sync_with_stdio(false);//关闭流同步提速
	cin >> t;
	while (t--) {
		flag = false;//初始化
		cin >> n >> a1;
		for (int i = 2; i <= n; i++) {
			cin >> a;
			if (a % a1 && !flag) {//当不合法且第一次时再输出
				flag = true;
				cout << "NO\n";
			}
		}
		if (!flag)
			cout << "YES\n";
	}
	return 0;
}
```


---

## 作者：cachejtt (赞：2)

## 题意
给你一个数列，每次可以将 $a_i$ 变为 $a_i-a_{i-1}$ 问你能否将除了 $a_1$ 以外的所有位置变成 $0$？
## 思路
考虑 $n=2$ 时，当且仅当 $a_2 \bmod a_1=0$ 时，$a_2$ 有机会变成 $0$。

接着考虑 $n=3$ 时，为了让 $a_2$ 变为 $0$，$a_2$仍需满足上述条件，因此在 $a_2$ 减少的过程中，其值必定可以变为 $a_1$。

为什么呢？

不妨设 $a_2=a_1\times k$，则 $a_2$ 在减去 $k-1$ 次 $a_1$ 后，其值自然等于 $a_1$。

故此时我们再观察 $a_3$ 与 $a_2$ 之间的关系，是不是又回到第一步了？也就是仅当 $a_3 \bmod a_2=0$ 时，$a_3$ 有机会变成 $0$。这里的 $a_2$ 的值就等于 $a_1$，也就是说 $a_3 \bmod a_1=0$

以此类推，只有当 $a_2,a_3,\dots,a_n$ 都为 $a_1$ 的倍数时，方才有解，反之则无解。

注意多组数据清零。
## 代码
```cpp
#include<bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define nrep(i, a, b) for (int i = (a); i >= (b); --i)
using namespace std;
int t,n,a[105],flag; 
int main(){
  std::ios::sync_with_stdio(0);
  cin>>t;
  rep(kk,1,t){
    cin>>n;
    flag=1;
    rep(i,1,n){
      cin>>a[i];
      if(i>1){
        if(a[i]%a[1]!=0)flag=0;
      }  
    }
    if(flag==1)cout<<"YES"<<endl;
    else cout<<"NO"<<endl;
  }
  return 0;
}

```

---

## 作者：MH_SLC (赞：2)

## 题目分析
要将除了 $a_1$ 以外的数都变为 $0$ ，这道题我们可以让 $i$ 从 $2$ 开始枚举，枚举到 $n$。
当 $n=2$时：$a_2 \bmod a_1=0$, $a_2$ 就变成了 $0$。

根据以上关系，如果所有的 $a_i$ 都可以除以 $a_1$ 也就是 $a_i \bmod a_1\neq0$ 即可输出 YES，否则输出 NO，可以使用一个布尔型来标记。
```cpp
for (int i = 2; i <= n; i++)
	if (a[i] % a[1])flag = 1;
```
## AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
const int MAX = 1e+5;
inline int read() {
	int x = 0;
	char c = getchar();
	while (c < '0' || c > '9') c = getchar();
	while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
	return x;
}
int T = read(), a[MAX], n;
int main() {
	while (T--) {
		n = read();
		bool flag = 0;
		for (int i = 1; i <= n; i++)a[i] = read();
		for (int i = 2; i <= n; i++)
			if (a[i] % a[1])flag = 1;
		if (flag)cout << "NO" << endl;
		else cout << "YES" << endl;
	}
	return 0;
}

```


---

## 作者：shenyiran (赞：2)

### 分析 
因为题目中 $i (2\leq i\leq n)$，所以第一个数是不会改变的。我们设它为 $m$，那么 $a_i=a_i-a_{i-1}$ 的操作只能在 $a_2 \bmod m$ 值为 $0$ 的情况下才有可能使 $a_2$ 为 $0$。以此类推，$a_3,a_4....a_n$ 都是 $m$ 的倍数，否则无可能实现。
### AC CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[110];
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		int tot=a[1],p=0;
		for(int i=2;i<=n;i++){
			if(a[i]%tot!=0){//判断有无可能
				p=1;
				cout<<"NO\n";
				break;
			}
		}
		if(!p){
			cout<<"YES\n";
		}
	}
	return 0;
} 
```

---

## 作者：xzy090626 (赞：0)

# CF1708A 题解
## 题意
本题多测，共有 $t$ 组数据。

有一个包含 $n$ 个正整数的数列 $a$，你可以反复执行如下操作：
- 选择一个下标 $i(2 \le i \le n)$，然后把 $a_i$ 赋值为 $a_i-a_{i-1}$。

请问，有没有可能将该序列的 $[2,n]$ 区间中的元素全部变为 $0$？

如果能，输出 `YES`；否则，输出 `NO`。

数据范围：$1 \le t \le 100$，$2\le n \le 100$，对于所有的 $i(1\le i \le n)$，有 $1 \le a_i \le 10^9$。
## 分析
我们通过简单的观察，能发现，要使得 $a_i(2 \le i \le n)$ 全部变为 $0$，必须让 $a_i$ 不断地减去 $a_{i-1}$，直到它变为 $0$。

那么我们现在就得面临一个问题：对 $a_i$ 执行该操作 $k(k \in \mathbb{Z})$ 次，其实等价于 $a_i = a_i - k \cdot a_{i-1}$。但是我们容易看出，这个操作不一定能使 $a_i$ 变为 $0$。而且，只有 $a_i$ 能被 $a_{i-1}$ 整除时，通过该操作可以成功。

又因为我们要使得 $a_i$ 都变为 $0$，所以要使得每个 $a_i$ 都整除 $a_{i-1}$ 才行。

这样简单地递推一下，就能发现，只有每个数都能被 $a_1$ 整除才行。

这样就解决了这个问题。

---

## 作者：qip101 (赞：0)


**题意：**

[CF 1708A](https://www.luogu.com.cn/problem/CF1708A)

**Solution：**

先从第二个数入手考虑，要使得第二个数可以变成零，很显然那么第二个数一定是第一个数的倍数。

往下递推，显然要使得第三个数可以变成零，那么第三个数一定是第二个数或变化后的第二个数的倍数。

则可得结论当所有数都是第一个数的倍数时可以完成目标。

**Code：**

```cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
#define MAXN 105
int T,n,a[MAXN];
int main() 
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for (int i=1;i<=n;i++) 
			scanf("%d",&a[i]);
        bool flag=true;
        for (int i=2;i<=n;i++)
            if ((a[i]%a[1])!=0) 
				flag=false;
        puts(flag?"YES":"NO");
    }
    return 0;
}

```

---

## 作者：qfpjm (赞：0)

# 题解

- 显然，如果 $a_i\bmod a_{i-1}\ne 0$，那么该序列显然无法归零。但是如果将 $a_i$ 归零，除非 $a_{i+1,\dots ,n}$ 全为零，否则无法归零。那么我们会考虑吧保留 $a_{i-1}$，即为让 $a_i=a_{i-1}$。

- 这样我们会发现 $a_2=a_1,a_3=a_2=a_1,\dots ,a_{n-1}\dots =a_1$，$a_n=0$。那么问题就化简为 $(a_2,\dots ,a_n)\bmod a_1$ 是否等于零。

- 那么，这题就可以 $O(n)$ 解决。

# 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

int T, n, a[105];

int main()
{
	cin >> T;
	while (T --)
	{
		cin >> n;
		bool flag = 0;
		for (int i = 1 ; i <= n ; i ++)
		{
			cin >> a[i];
		}
		for (int i = 1 ; i <= n ; i ++)
		{
			if (a[i] % a[1] != 0)
			{
				flag = 1;
				puts("NO");
				break;
			}
		}
		if (!flag)
		{
			puts("YES");
		}
	}
}
```


---

## 作者：happy_dengziyue (赞：0)

### 1 视频题解

![](bilibili:BV1eB4y1Y7ZV)

### 2 思路

我们可以发现，$a[2]$ 可以变为 $0$，当且仅当它是 $a[1]$ 的倍数。

同样的，$a[3]$ 减去的数 $a[2]$ 无论如何都是 $a[1]$ 的倍数，使得 $a[3]$也是 $a[1]$ 的倍数。在操作时，我们可以将 $a[2]$ 操作使得 $a[2]=a[1]$，然后将 $a[3]$ 操作为 $0$。

以此类推，当且仅当 $a[i]$ 都是 $a[1]$ 的倍数时有解。

### 3 代码与记录

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
#define max_n 200000
int t;
int n;
int a[max_n+2];
bool ans;
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1708A_1.in","r",stdin);
	freopen("CF1708A_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;++i)scanf("%d",a+i);
		ans=true;
		for(int i=2;i<=n;++i){
			if(a[i]%a[1]){
				ans=false;
				break;
			}
		}
		if(ans)printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/80119002)


By **dengziyue**

---

## 作者：zhicheng (赞：0)

### 思路

让我们先看 $a_2$。它一定是 $a_1$ 的倍数，否则无法变为 $0$。$a_3$ 也一定是操作后 $a_2$ 的倍数。而要确保是倍数，$a_2$ 越小越好，但不能为 $0$。所以先把 $a_2$ 变成 $a_1$ 即可。以此类推，那么所有的数一定都要是 $a_1$ 的倍数。直接判断即可。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,a,q,p,y;
	scanf("%d",&n);
	while(n--){
		y=0;  //清空
		scanf("%d",&a);
		for(int i=1;i<=a;i++){
			scanf("%d",&p);
			if(i==1){
				q=p;  //记录a[1]
			}
			if(p%q){
				y=1; //不满足，打标记
			}
		}
		if(y==0){  //遍历完了都满足
			printf("YES\n");
		}
		else{
			printf("NO\n");
		}
	}
}
```

---

## 作者：_Andy_Lin_ (赞：0)

看起来很难，实际上还蛮水的。

首先从 $2$ 个数的情况开始：

显然，只有 $a_2$ 为 $a_1$ 的倍数时才合法。

而 $a_2$ 在任何时候都是 $a_1$ 的倍数。

因此，推广至 $3$ 个数的情况时， $a_3$ 也为 $a_1$ 的倍数。

以此类推： $a_i$ 为 $a_1$ 的倍数。

必要性证完，接下来证充分性。

首先将 $a_2$ 减至 $a_1$ ，再将 $a_3$ 减至 $a_2$ ，以此类推，直到所有数都相等，然后从后往前以此减即可。

AC Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 101
int T,n,a[N];
bool ok;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);ok=0;
		for(int i=1;i<=n;++i)scanf("%d",a+i);
		for(int i=2;i<=n;++i){
			if(a[i]%a[1]){
				ok=1;puts("NO");break;
			}
		}
		if(!ok)puts("YES");
	}
	return 0;
}
```

---

