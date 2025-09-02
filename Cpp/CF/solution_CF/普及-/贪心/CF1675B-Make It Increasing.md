# Make It Increasing

## 题目描述

Given $ n $ integers $ a_1, a_2, \dots, a_n $ . You can perform the following operation on them:

- select any element $ a_i $ ( $ 1 \le i \le n $ ) and divide it by $ 2 $ (round down). In other words, you can replace any selected element $ a_i $ with the value $ \left \lfloor \frac{a_i}{2}\right\rfloor $ (where $ \left \lfloor x \right\rfloor $ is – round down the real number $ x $ ).

Output the minimum number of operations that must be done for a sequence of integers to become strictly increasing (that is, for the condition $ a_1 \lt a_2 \lt \dots \lt a_n $ to be satisfied). Or determine that it is impossible to obtain such a sequence. Note that elements cannot be swapped. The only possible operation is described above.

For example, let $ n = 3 $ and a sequence of numbers $ [3, 6, 5] $ be given. Then it is enough to perform two operations on it:

- Write the number $ \left \lfloor \frac{6}{2}\right\rfloor = 3 $ instead of the number $ a_2=6 $ and get the sequence $ [3, 3, 5] $ ;
- Then replace $ a_1=3 $ with $ \left \lfloor \frac{3}{2}\right\rfloor = 1 $ and get the sequence $ [1, 3, 5] $ .

The resulting sequence is strictly increasing because $ 1 \lt 3 \lt 5 $ .

## 说明/提示

The first test case is analyzed in the statement.

In the second test case, it is impossible to obtain a strictly increasing sequence.

In the third test case, the sequence is already strictly increasing.

## 样例 #1

### 输入

```
7
3
3 6 5
4
5 3 2 1
5
1 2 3 4 5
1
1000000000
4
2 8 7 5
5
8 26 5 21 10
2
5 14```

### 输出

```
2
-1
0
0
4
11
0```

# 题解

## 作者：Failure_Terminator (赞：2)

## Problem

给定一个数列，通过将任意一个数整除 $2$ 的变化，使数列**严格单调递增**，求最少需要的变化次数。

## Solution

由于操作后的数列严格单调递增，所以数列末尾的数即为最大数。

我们需要从数列的末尾开始处理元素，对于第 $i$ 个数，将其不断整除 $2$ 直到 $a_i<a_{i+1}$。

若在做的时候发现 $a_{i+1}=0$，则不可能获得所需的序列。

## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[105];
int main()
{
    cin>>t;
    while(t--){
		cin>>n;
   		for(int i=1;i<=n;i++)
		   	cin>>a[i]; 
    	int ans=0;
    	for(int i=n-1;i>=1;i--){
    		if(a[i+1]==0){
    			ans=-1;
    			break;
			}
        	while(a[i]>=a[i+1]&&a[i]>0){//如果少了后一个判断会导致死循环
           		a[i]/=2;
            	ans++;
        	}
    	}
    	cout<<ans<<endl;
    }
    return 0;
}
```

By **haimo**

---

## 作者：ztrztr (赞：2)

## 题目大意
这道题的意思是：给出序列 $a$，每次选一个数 $a_i$ 让 $a_i = \lfloor \frac{a_i}{2}\rfloor$，请问最少要几次才能把序列 $a$ 变为严格递增，永远不可以的话输出 $-1$。
## 思路
一道贪心题。我们遍历（倒序）$a$ 序列，往前遍历直到这个序列是严格递增，
## 实现
1. 输入组数，再输入 $n$ 和序列 $a$。
2. 倒序遍历，如果一个数是 $0$ 了，退出循环，否则计数器 $+1$。如果遍历结束了还不退出，无解。
3. 输出计数器，无解则输出 $-1$ 
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, a[1005] = {0}, flag = 1, cnt = 0;
int main(){
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) {
    	cin >> n;
        flag = 1, cnt = 0;
    	for (int i = 1; i <= n; i++) cin >> a[i];
    	for (int i = n - 1; i > 0 and flag != 0; i--) {
    		while (a[i] >= a[i + 1]) {
    			if (!a[i]) {
    				flag = 0;//跳出两层循环 
    				break;
    			}
    			a[i] = a[i] / 2;//int默认就是向下取整
				cnt++; 
			}
		}
		if(!flag) cout << "-1" << "\n";
		else cout << cnt << "\n";
	}
    return 0;
}

```

---

## 作者：ttq012 (赞：1)

**Solution**

简单题。

我们从倒数第二个数开始除以 $2$，一直除到和原来相同或者比上一个数小为止。执行这一个操作一直执行到第一个数。

最后判断序列是否单调递增即可。如果是输出执行的次数，否则输出 `-1`。

**Code**

```cpp
#include <bits/stdc++.h>
#define int long long
 
using namespace std;
 
const int N = (int) 2e3 + 10;
int f[N][N];
char s[N], t[N];
char ans[N];
 
signed main() {
    int T;
    cin >> T;
    while (T --) {
        int n;
        cin >> n;
        vector <int> a(n + 1);
        for (int i = 1; i <= n; i ++)
            cin >> a[i];
        bool flag = false;
        int cnt = 0;
        for (int i = n - 1; i; i --) {
            while (a[i] >= a[i + 1]) {
                if (a[i] == (a[i] >> 1)) {
                    flag = true;
                    break;
                }
                cnt ++;
                a[i] >>= 1;
            }
            if (flag)
                break;
        }
        if (flag)
            puts("-1");
        else {
            cout << cnt << '\n';
        }
    }
    return 0;
}

```


---

## 作者：Engulf (赞：1)

可以倒序枚举，如果 $a_{i-1}\ge a_i$ 就不断对 $a_{i-1}$ 做除法。

如果 $a_{i-1}=a_i$ 那么就输出 $-1$。

```cpp
// author: TMJYH09
// create time: 2022/05/05 22:47:46
#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        vector <int> a(n+10);
        for(int i=1;i<=n;i++)cin>>a[i];
        int ans=0;
        for(int i=n;i>=2;i--){
            while(a[i-1]>=a[i]){
                if(a[i-1]==a[i]&&a[i]==0)goto qwq;
                a[i-1]/=2;ans++;
            }
        }
        qwq:bool flag=true;
        for(int i=2;i<=n;i++){
            if(a[i-1]>=a[i]){flag=false;break;}
        }
        if(flag)cout<<ans<<endl;
        else cout<<"-1\n";
    }
    return 0;
}
```

---

## 作者：BetaCutS (赞：0)

## 题目大意

给你一个数列 $a$，每次可以选择任何一个 $a_i$，把它变为 $\left\lfloor\dfrac{a_i}{2}\right\rfloor$，问最少需要多少次操作才能让数列严格递增（$a_{i-1}<a_i<a_{i+1}$）。如果无解，输出 $-1$。

## 算法

贪心。$a_n$ 不变的情况下，留给 $a_1,a_2,a_3,\cdots,a_{n-1}$ 的空位越大，所以 $a_n$ 不变。

从 $n-1$ 开始从后往前扫一遍，每次除以 $2$，让 $a_i<a_{i+1}$ 并统计需要几次。如果 $a_{i+1}=0$，那么 $a_i$ 不能通过除以 $2$ 而小于 $a_{i+1}$，无解。最后把 $a_1,a_2,a_3,\cdots,a_{n-1}$ 所需的次数加起来即可。

## 代码

```cpp
#include<algorithm>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iomanip>
#include<iostream>
#include<queue>
#include<string>
#include<vector>
using namespace std;
const int INF=0x3f3f3f3f;
const int N=31;
const double eps=1e-5;
int read()
{
	char ch=getchar();
	int x=0,f=1;
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-48,ch=getchar();}
	return x*f;
}
int T,n,a[N];
signed main()
{
	T=read();
	while(T--)
	{
		n=read();
		for(int i=1;i<=n;i++)
			a[i]=read();
		int ans=0,flag=1;
		for(int i=n-1;i&&flag;i--)
		{
			while(a[i]>=a[i+1])
			{
				if(!a[i])
				{
					flag=0;
					break;
				}
				a[i]/=2,ans++;
			}
		}
		if(!flag)
			puts("-1");
		else
			printf("%d\n",ans);
	}
	return 0;
}
```


---

## 作者：ryanright (赞：0)

## Description

已知一个长度为 $n$ 的数列 $a$。每次操作可以选择一个 $a_i$，把它变成 $\lfloor\frac{a_i}2\rfloor$。问至少需要多少次操作才能使这个序列严格递增。

## Solution

既然是严格递增，那么我们就要让最后一个数最大，而每次操作只能把元素变小，因此我们不能对最后一个数进行任何操作。最后一个数定下来了，倒数第二个数就要不断操作使得它 **刚刚好** 小于最后一个数，剩下的也是一样。

这里要注意的是，如果我们把一个元素除成了 $0$，那么它的前一个元素也会是 $0$，这需要我们在最后检查一遍整个序列是否是严格递增的。

## Code

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
int a[35];
int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		int n, tot = 0;//操作数tot
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
			scanf("%d", &a[i]);
		for (int i = n - 1; i >= 1; i--)
			while (a[i] >= a[i + 1]) {//除到刚好小于后一个数
				if (!a[i])//除到0要退出，因为再操作没意义
					break;
				tot++;
				a[i] /= 2;
			}
		bool flag = 1;
		for (int i = 1; i < n; i++)//检查递增
			if (a[i] == a[i + 1]) {
				flag = 0;
				break;
			}
		if (flag)
			printf("%d\n", tot);
		else
			puts("-1");
	}
	return 0;
}
```

---

## 作者：cyrxdzj (赞：0)

### 一、思路

显然，最优的操作方式，是从第 $n-1$ 个数一直到第 $1$ 个数，对于每个数，都不断除以二再向下取整，直到该数小于右边的数。

我们可以发现，任何一个**正**数除以二再向下取整，新数一定小于原数。但是，零除以二再向下取整依然是零。

因此，在这两种情况之一下可以判定无解：

1. 正在操作第 $i$ 个数，$i>1$，但是 $a_i$ 被操作到了零。

2. 正在操作第 $i$ 个数，$a_{i+1}=0$。

除此以外的情况一定有解。

### 二、代码

```cpp
#include<cstdio>
using namespace std;
int t;
int n;
long long a[35];
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		int ans=0;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			scanf("%lld",&a[i]);
		}
		for(int i=n-1;i>=1;i--)
		{
			while(a[i]>=a[i+1])
			{
				a[i]/=2;
				ans++;//计数
				if(a[i]==0&&i!=1)
				{
					ans=-1;
					break;
				}
				if(a[i+1]==0)
				{
					ans=-1;
					break;
				}
			}
			if(ans==-1)
			{
				break;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}

```


---

## 作者：SnowTrace (赞：0)

从头开始，记录上一个元素的值，然后不断除，直到为零停止。

最后判断一下即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin >> t;
	while(t--){
		int n,ans  = 0;
		cin >> n;
		int a[n+5];
		for(int i =0;i<n;i++)cin >> a[i];
		for(int i = n-2;i>=0;i--){
			while(a[i+1]<=a[i]){
				a[i]=a[i]/2;
				ans++;
				if(a[i] == 0)break;
			}
		}bool ok = 0;
		for(int i =0;i<n-1;i++){
			if(a[i]>=a[i+1]){
				ok = 1;
				break;
			}
		}if(ok == 1){
			cout << -1 << endl;
		}else{
			cout << ans << endl;
		}
	}
}
```


---

