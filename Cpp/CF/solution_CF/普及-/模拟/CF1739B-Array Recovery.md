# Array Recovery

## 题目描述

For an array of non-negative integers $ a $ of size $ n $ , we construct another array $ d $ as follows: $ d_1 = a_1 $ , $ d_i = |a_i - a_{i - 1}| $ for $ 2 \le i \le n $ .

Your task is to restore the array $ a $ from a given array $ d $ , or to report that there are multiple possible arrays.

## 说明/提示

In the second example, there are two suitable arrays: $ [2, 8, 5] $ and $ [2, 8, 11] $ .

## 样例 #1

### 输入

```
3
4
1 0 2 5
3
2 6 3
5
0 0 0 0 0```

### 输出

```
1 1 3 8
-1
0 0 0 0 0```

# 题解

## 作者：binaryBard (赞：3)

读题点 [这里](https://www.luogu.com.cn/problem/CF1739B)

更好的阅读体验点 [这里](https://blog.jerryz.com.cn/article/solution-CF1739B)

# 题意简述

有一个非负整数序列 $a$，定义 $d_1=a_1,d_i=|a_i-a_{i-1}|$。现在给出序列 $d$，问是否能确定唯一的序列 $a$。不能输出 $-1$，否则输出序列 $a$。

# 思路分析

我们通过 $d_i=|a_i-a_{i-1}|$ 可以得到 $a_i=d_i+a_{i-1}$ 或 $a_i=a_{i-1}-d_i$。

当序列 $a$ 只有唯一的一种可能性时， $d_i+a_{i-1}$ 和 $a_{i-1}-d_i$ 其中只能有一个大于或等于 $0$，或是它们的值相等。

所以我们可以求出 $d_i$ 对应的两个 $a_i$ 的值，当不满足条件时输出 $-1$，否则将其中大于或等于 $0$ 的值存入数组即可。

# 代码

```C++
#include<bits/stdc++.h>
using namespace std;
#define N 105

int T,n,d[N],a[N];

int main(){
    cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>d[i];
		}
		a[1]=d[1];
		bool flag=0;
		for(int i=2;i<=n;i++){
			int a1=d[i]+a[i-1],a2=a[i-1]-d[i];
			if(a1>=0&&a2>=0&&a1!=a2){
				cout<<-1<<endl;
				flag=1;
				break;
			}else{
				if(a1>=0) a[i]=a1;
				else a[i]=a2;
			}
		}
		if(!flag){
			for(int i=1;i<=n;i++){
				cout<<a[i]<<" ";
			}
			cout<<endl;
		}
	}
	//system("pause");
	return 0;
}
```

---

## 作者：Larry76 (赞：2)

## 题目大意：

有一个非负整数序列 $A$，定义序列 $D$ 是序列 $A$ 的绝对值差分序列，问给定序列 $D$，能否求出唯一的序列 $A$，若不能，输出 $-1$，否则输出序列 $A$。

## 题目分析：

因为属于差分序列，所以我们不难得出序列 $D$ 的前缀和序列 $S$ 就是序列 $A$ 的一种。

那么不能得出唯一解得情况就很好想了，如果 $S_{i-1}+(-D_i) \ge 0$，那么就说明有多个序列 $A$，理由如下：

因为 $D_i$ 是 $A_{i-1}-A_i$ 的绝对值，所以原差分序列中 $D_i$ 的位置可正可负，如果 $S_{i-1}+(-D_i) < 0$，则说明了原差分序列上 $D_i$ 的位置肯定为非负整数（因为序列 $A$ 是由非负整数构成的），反之则说明原差分序列上 $D_i$ 的位置的正负性不影响序列 $A$ 是一个非负整数序列，故此时序列 $A$ 有多种。

## 代码实现：

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int T;
    cin >> T;

    while (T--) {
        int n;
        int d[200] = {};
        cin >> n;

        for (int i = 1; i <= n; i++)
            cin >> d[i];

        bool inc = 1;
        int a[200] = {};
        a[1] = d[1];

        for (int i = 2; i <= n; i++)
            a[i] = a[i - 1] + d[i];

        for (int i = 2; i <= n; i++) {
            if (a[i - 1] >= d[i] && d[i]) {
                cout << -1 << endl;
                inc = 0;
                break;
            }
        }

        if (!inc)
            continue;

        for (int i = 1; i <= n; i++)
            cout << a[i] << ' ';

        cout << endl;
    }

    return 0;
}
```

---

## 作者：skyskyCCC (赞：1)

## 前言。
题意：[题意传送门](https://www.luogu.com.cn/problem/CF1739B)。

一道较为简单的题。
## 分析。
因为 $d_i=|a_i-a_{i-1}|$ 的式子，且题目要求答案是一个**非负整数**序列。

那么，如果当 $d_i$ 小于 $a_{i-1}$ 且 $a_i$ 不等于 $0$ 的情况下，即 $a_{i-1}-d_i$ 小于 $0$ 时，就会有一个确定的 $a_i$ 的值。

如果 $d_i=0$ 的情况，也会有一个确定的 $a_i$ 的值。

如果存在一个不满足这两种情况的 $d_i$ 的位置，那么就不能出现答案。

满足情况的位置，对于 $2\leq i\leq n$ 的情况，则有 $a_i=\sum_{i=1}^n d_i$ 的答案。

代码如下，仅供参考：
```
#include<iostream>
using namespace std;
int t,n,d[105],sum[105],pd;
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		pd=1;
		for(int i=1;i<=n;i++){
			cin>>d[i];
		}
		sum[1]=d[1];
		for(int i=2;i<=n&&pd==1;i++){
			if(d[i]&&sum[i-1]-d[i]>=0) pd=0;
			sum[i]=sum[i-1]+d[i];
		}
		if(pd==0) cout<<"-1";
		else{
			for(int i=1;i<=n;i++){
				cout<<sum[i]<<" ";
			}
		}
		cout<<"\n";
	}
	return 0;
}
```
## 后记。
不得不说，测评机真的变快了。

---

## 作者：0zhouyq (赞：1)

### CF1739B 题解

[传送门](https://www.luogu.com.cn/problem/CF1739B)

### 思路

因为 $d$ 数组的每一个数都是大于等于 $0$ 的，所以 $a_i=\sum\limits_{j=1}^i$ 的这种情况是一定是可行的。

记数组 $sum_i=\sum\limits_{j=1}^{i}a_i$，当 $a$ 数组为确定的时候，$d_i$ 必须要满足 $d_i<sum_{i-1}$，否则 $a_i$ 就既可以是 $sum_{i-1}-d_i$，又可以是 $sum_{i-1}+d_i$，$a$ 就不是确定的了。所以这种情况就直接输出 $-1$。否则就直接输出 $sum$ 数组。

### AC Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int sum[101]={0};
signed main(){
	int t;
	scanf("%lld",&t);
	while(t--){
		int n;
		scanf("%lld",&n);
		bool flag=true;
		for(int i=1;i<=n;i++){
			int x;
			scanf("%lld",&x);
			if(!flag) continue;
			if(x<=sum[i-1]&&x!=0){
				flag=false;
			}
		    sum[i]=sum[i-1]+x;
		}
		if(flag){
			for(int i=1;i<=n;i++) printf("%lld ",sum[i]);
			printf("\n");
		}
		else printf("-1\n");
	}
	return 0;
}
```

---

## 作者：JHR100330 (赞：0)

# CF1739B Array Recovery 题解

~~我是不会说我第一次交错地方了的。~~

[题目传送门](https://www.luogu.com.cn/problem/CF1739B)

## 题目大意

有一个非负整数序列 $a$，定义 $d_1 = a_2$，$d_i = |a_i - a_{i - 1}|$。现在给出序列d，问是否能确定唯一的序列 $a$。不能输出 $-1$，否则输出序列 $a$。

## 题目分析

绝对值具有双值性：$|a_i - a_{i - 1}| = a_i - a_{i - 1}$ 或 $a_{i - 1} - a_i$。

所以得 $d_i = a_i - a_{i - 1}$ 或 $d_i = a_{i - 1} - a_i$。

则 $a_i = a_{i - 1} + d_i$ 或 $a_i = a_{i - 1} - d_i$。

因为 $a$ 为非负整数序列，$d$ 数组每位的计算需要用到绝对值，所以 $a_{i - 1} + d_i \ge 0$，且 $a_i \ge 0$，所以 $a_i = a_{i - 1} + d_i$ 一定成立。

因为要确定唯一的序列，所以这两条只能有一条成立,得 $a_i = a_{i - 1} - d_i$ 一定不成立，或 $d_i = 0$。

得到 $a_{i - 1} - d_i < 0$。

则如果 $a_{i - 1} \ge d_i$ 且 $d_i \not = 0$ 则无法唯一确定序列 $a$。

# AC Code:

```cpp
#include<bits/stdc++.h>	//万恶之源 
using namespace std;

int d[150], a[150];	//d序列，a序列 
int t, n;			//t组数据，每组n个数 
bool flag;			//记录d序列是否能够唯一确定a序列 

int main() { 
	scanf("%d", &t);	//录入数据个数 
	while(t --){		//遍历t组数据，相当于:for(int k = 1; k <= t; k++) 
		scanf("%d", &n);	//录入数组长度 
		//录入d数组 
		for(int i = 1; i <= n; i ++)
			scanf("%d", &d[i]);
		//初始化默认为合法 
		flag = 1;
		//初始化第一位 
		a[1] = d[1];
		//遍历2到n位 
		for(int i = 2; i <= n; i ++){
			//判断合法性 
			if(d[i] != 0 && d[i] <= a[i - 1]){
				//不合法，改变flag的值 
				flag = 0;
				//退出循环 
				break;
			}
			//计算a数组第i位的值（一定为升序） 
			a[i] = a[i - 1] + d[i];
		}
		if(!flag)	//判断不合法 
			printf("-1");
		else		//判断合法 
			//输出a序列 
			for(int i = 1; i <= n; i ++)
				printf("%d ", a[i]); 
		putchar('\n');	//记得换行 
	}
	//结束程序 
	return 0;
}
```

# 感谢观看

---

## 作者：blsya23a2 (赞：0)

## 分析
方程 $d_i=|a_i-a_{i-1}|$ 的解为 $a_i=a_{i-1}+d_i$ 或 $a_i=a_{i-1}-d_i$。由题知，$a_i\ge0$，所以正确的解一定大于 $0$。如果两个解都大于 $0$ 且不相等，即 $d_i\not=0$，就无法确定唯一解，否则把唯一解存入答案列表。
## 代码
```python
a = int(input())
for b in range(a):
    c,d,e,g = int(input()),list(map(int,input().split())),[],0
    e.append(d[0])
    for f in range(1,c):
        h,i,j = [],e[f-1]+d[f],e[f-1]-d[f]
        if i >= 0:
            h.append(i)
        if j >= 0:
            h.append(j)
        if len(h) == 2 and d[f] != 0:
            g = 1
            break
        else:
            e.append(h[0])
    if g == 0:
        print(*e)
    else:
        print(-1)
```
upd：增强了代码可读性。

---

## 作者：xiaofeng_and_xiaoyu (赞：0)

读题之后可以惊喜地发现：诶？这不是差分吗？

~~众所周知~~差分的逆运算是前缀和。

所以打一个前缀和程序复原就可以了（可以加一个前缀和标签）。

每一个向前递推，如果比它大就只能加，如果小于等于就可加可减，输出 $-1$ 。 

贴出代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t[105],l[105];
int main(){
    int x,y,z;
    cin>>x;
    while(x--){
    	int y;
    	cin>>y;
		bool s=0;
		cin>>l[1];
		t[1]=l[1];
    	for(int i=2;i<=y;i++){
    		cin>>l[i];
		}
		for(int i=2;i<=y;i++){
    		if(l[i]>=t[i-1]||l[i]==0){
    			t[i]=(t[i-1]+l[i]);
			}else{
				cout<<-1<<endl;
				s=1;
				break;
			}
		}
		if(s==0){
			for(int i=1;i<=y;i++){
    			cout<<t[i]<<' ';
			}
			cout<<endl;
		}
		cout<<endl;
	}
    return 0;
}
```
然而这个题有个坑点：是非负数列！

即：其中的元素可以为 $0$ ！

~~这也是为什么我WA了两次~~

于是把
```cpp
l[i]>=t[i-1] //改成 
l[i]>t[i-1]
```
之后，就可以 $\verb!AC!$ 了。

[完整代码](https://www.luogu.com.cn/paste/hzbcv83s)

---

## 作者：Not_lazy (赞：0)

## 题意
有一个非负整数序列 $a$，定义 $d_1=a_1,d_i=|a_i-a_{i-1}|$。现在给出序列 $d$，问是否能确定唯一的序列 $a$。不能输出 `−1`，否则输出序列 $a$。
## 思路
如果 $d_i=0$ 的情况，也会有一个确定的 $a_i$ 的值。

如果存在一个不满足这两种情况的 $d_i$ 的位置，那么就不能出现答案。
对于 $2\leq i\leq n$ 的情况，则 $a_{i}=\sum ^{n}_{i=1}d_i$。
## 代码（仅供参考）
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int sum[101]={0};
signed main(){
	int t;
	scanf("%lld",&t);
	while(t--){
		int n;
		scanf("%lld",&n);
		bool flag=true;
		for(int i=1;i<=n;i++){
			int x;
			scanf("%lld",&x);
			if(!flag) continue;
			if(x<=sum[i-1]&&x!=0){
				flag=false;
			}
		    sum[i]=sum[i-1]+x;
		}
		if(flag){
			for(int i=1;i<=n;i++) printf("%lld ",sum[i]);
			printf("\n");
		}
		else printf("-1\n");
	}
	return 0;
}
```


---

## 作者：alm_crax (赞：0)

### [洛谷题目传送门](https://www.luogu.com.cn/problem/CF1739B)

### [CF原题传送门](https://codeforces.com/problemset/problem/1739/B)

## 思路
根据题目可以得出：

$d_i=a_i-a_{i-1}$ 或 $d_i=a_{i-1}-a_i$。

所以， $a_i$ 有 $a_i=d_i+a_{i-1}$ 和 $a_i=a_{i-1}-d_i$ 两种情况。

题目问序列 $a$ 唯不唯一，即每个 $a_i$ 只能有一种状态。

因为序列 $a$ 非负，所以 $a_i=d_i+a_{i-1}$ 必然存在，则先使 $a_i=\sum\limits_{k=1}^kd_k$。

然后若 $a_i=a_{i-1}-d_i>0$ 就说明 $a_i$ 不唯一，否则唯一。

特殊：若 $d_i=0$ 此时 $a_i$ 两种状态一样。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,d[105],a[105];
bool f;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		f=0;
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&d[i]);
			a[i]=d[i]+a[i-1];
			if(a[i-1]-d[i]>=0&&d[i])
			//是否唯一，d[i]=0时唯一但a[i-1]可能为0，0-0=0，不能做判断
			{
				f=1;
			}
		}
		if(f)
		{
			printf("-1\n");
			continue;
		}
		for(int i=1;i<=n;i++)
		{
			printf("%d ",a[i]);
		}
		puts("");
	}
	return 0;
}
```

---

## 作者：ECEG (赞：0)

# Array Recovery题解
# 分析
因为 $d_i=\left|a_i-a_{i-1}\right|$，所以我们分类讨论。

- $a_i\ge a_{i-1}$ 时

所以 $d_i=a_i-a_{i-1}\Longrightarrow a_i=d_i+a_{i-1}$(因为 $d_i$ 和 $a_{i-1}$ 数组都非负，所以 $a_i$ 非负)

- $a_i<a_{i-1}$ 时

所以 $d_i=a_{i-1}-a_i\Longrightarrow a_i=a_{i-1}-d_i(a_i\ge0)$

当两种情况**都满足**时，那就输出 $-1$。否则就算出 $a_i$。

$n\le100$，稳过。
## AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int qwe=104;
int T,n,a[qwe],d[qwe];
int work(){
	cin>>n;
	for(int i=1;i<=n;++i)cin>>d[i];
	a[1]=d[1];
	for(int i=2;i<=n;++i){//从2开始 
		if(d[i]+a[i-1]>=a[i-1]&&(a[i-1]-d[i]>=0&&a[i-1]-d[i]<a[i-1]))return cout<<-1<<"\n",0;//记得判非负 
		if(d[i]+a[i-1]>=a[i-1])a[i]=d[i]+a[i-1];
		else a[i]=a[i-1]-d[i];
	}
	for(int i=1;i<=n;++i)cout<<a[i]<<" ";putchar('\n');
}
int main(){
	cin>>T;
	while(T--){
		work();
	}
	return 0;
}
```


---

## 作者：Cczzyy20150005 (赞：0)

## 思路
因为序列 $a$ 是非负的，所以只有以下两种情况的序列 $d$ 是对应唯一的 $a$ 的：

1. $a_{i-1} - d_i \lt 0$。  
因为 $a_{i-1}$ 要么加 $d_i$，要么减 $d_i$。而 $d_i$ 非负，所以 $a_{i-1}+d_i$ 是一定非负的，又要让序列 $a$ 唯一，所以肯定要让 $a_{i-1}-d_i \lt 0$。
2. $d_i = 0$。  
明显 $d_i=0$ 时 $a_i$ 只有一种情况。

然后就可以直接模拟算 $a$ 然后看 $d$ 满不满足要求。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int a[1000001],d[1000001];
void solve(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&d[i]);
	a[1]=d[1];
	for(int i=2;i<=n;i++){
		if(a[i-1]-d[i]>=0&&d[i]!=0){
			puts("-1");
			return;
		}else a[i]=d[i]+a[i-1];
	}
	for(int i=1;i<=n;i++)printf("%d ",a[i]);
	puts("");
}
int main(){
	int t;
	cin>>t;
	while(t--)solve();
	return 0;
}

```

---

## 作者：ran_qwq (赞：0)

把题目的式子化简一下：$a_1=d_1$，对于 $2\leq i\leq n$，$a_i=a_{i-1}+d_i$ 或 $a_{i-1}-d_i$。

所以满足要求的一组解为 $a_i=\sum_{i=1}^nd_i$。

那么如何判断解不唯一呢？

对于第 $i$ 个位置的决策：

如果 $d_i=0$，$a_i$ 就确定了。

如果 $a_{i-1}-d_i<0$，因为 $a_i$ 非负，所以 $a_i$ 是唯一的。

如果对于某个位置，以上两种情况都不满足，输出 $-1$。否则第 $i$ 个数输出 $\sum_{i=1}^nd_i$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=110;
int T,n,flag,a[N],d[N];
int main()
{
	cin>>T;
	while(T--)
	{
		cin>>n;
		for(int i=1;i<=n;i++)
			cin>>d[i];
		a[1]=d[1],flag=1;
		for(int i=2;i<=n&&flag;i++)
		{
			if(d[i]&&a[i-1]-d[i]>=0)
				flag=0;
			a[i]=a[i-1]+d[i];
		}
		if(!flag)
			cout<<"-1";
		else
			for(int i=1;i<=n;i++)
				cout<<a[i]<<" ";
		cout<<"\n";
	}
}
```


---

## 作者：luo_shen (赞：0)

### 题面描述
有一个序列 $a$，$a$ 中元素均为非负整数，给定这个序列相邻两个数差的绝对值所组成的序列 $d$，且 $d_1=a_1$。问根据 $d$ 能否反推出一个唯一的序列 $a$。
### 题目分析
因为 $d_i=|a_i-a_{i-1}|$，题目要求的 $a$ 又是一个非负整数序列，若 $d_i<a_{i-1}$ 且 $d_i \not = 0$，则会生成两种 $a_i$ 的值，生成的序列不是唯一的。所以生成的唯一的序列 $a$ 必然是一个单调不降序列。
### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int read(){
    int s=0,f=1;
    char ch=getchar();
    while(ch>'9'||ch<'0'){
        if(ch=='-'){
            f=-1;
        }
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        s=s*10+(ch-'0');
        ch=getchar();
    }
    return s*f;
}
int t,n,d[110],a[110];
void solve(){
    n=read();
    for(int i=1;i<=n;i++){
        d[i]=read();
    }
    a[1]=d[1];
    for(int i=2;i<=n;i++){
        if(d[i]<=a[i-1]&&d[i]!=0){
            puts("-1");
            return;
        }
        a[i]=a[i-1]+d[i];
    }
    for(int i=1;i<=n;i++){
        printf("%d ",a[i]);
    }
    puts("");
}
signed main(){
    t=read();
    while(t--){
        solve();
    }
    return 0;
}
```

---

