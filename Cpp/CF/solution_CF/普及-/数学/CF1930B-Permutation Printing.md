# Permutation Printing

## 题目描述

You are given a positive integer $ n $ .

Find a permutation $ ^\dagger $ $ p $ of length $ n $ such that there do not exist two distinct indices $ i $ and $ j $ ( $ 1 \leq i, j < n $ ; $ i \neq j $ ) such that $ p_i $ divides $ p_j $ and $ p_{i+1} $ divides $ p_{j+1} $ .

Refer to the Notes section for some examples.

Under the constraints of this problem, it can be proven that at least one $ p $ exists.

 $ ^\dagger $ A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 说明/提示

In the first test case, $ p=[4,1,2,3] $ is a valid permutation. However, the permutation $ p=[1,2,3,4] $ is not a valid permutation as we can choose $ i=1 $ and $ j=3 $ . Then $ p_1=1 $ divides $ p_3=3 $ and $ p_2=2 $ divides $ p_4=4 $ . Note that the permutation $ p=[3, 4, 2, 1] $ is also not a valid permutation as we can choose $ i=3 $ and $ j=2 $ . Then $ p_3=2 $ divides $ p_2=4 $ and $ p_4=1 $ divides $ p_3=2 $ .

In the second test case, $ p=[1,2,3] $ is a valid permutation. In fact, all $ 6 $ permutations of length $ 3 $ are valid.

## 样例 #1

### 输入

```
2
4
3```

### 输出

```
4 1 2 3
1 2 3```

# 题解

## 作者：Kawaii_qiuw (赞：5)

**题意：**

你有构造一个长度为 $n$ 的排列 $p$，满足以下性质：

当 $p_i < p_j$ 时，$p_i + 1 < p_j + 1$。

**解题思路：**

首先我们考虑到，不能让两个较大的数挨在一起，需要在它们之间插入一个小数，满足题目要求。

当奇数位上的数整体都比偶数位上的数小时，若 $p_i < p_j$，则 $p_i + 1 < p_j + 1$。所以可以让奇数位上的数递增，偶数位的数递减。

**代码：**


```
#include <bits/stdc++.h>
using namespace std;
int main()
{
	int t, n;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		int l = 1, r = n;
		while(l <= r)
		{
			printf("%d ", l);
			l++;
			if(l > r)	break;
			printf("%d ", r);
			r--;
		}
	}
	printf("/n");
	return 0;
}
```

---

## 作者：__zyq_666_kpzc__ (赞：2)

### [先看题](https://www.luogu.com.cn/problem/CF1930B)
### 思路分析
我们可以构造一个数列，满足 $a_i < a_j$ 并且 $a_{i+1}>a_{j+1}$，这样一定符合题目要求，因为如果 $a_i \mid a_j$，那么 $a_i \le a_j$ 必定成立；同理，如果 $a_{i+1} $ 不被 $ a_{j+1}$ 整除，那么 $a_i > a_j$ 必定成立。
### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,t,l,r,a[100005],m=0;
signed main(){
	cin>>t;
	while(t--){
		cin>>n;
		l=1,r=n,m=0;
		while(l<=r){
			l++;
			a[++m]=l;
			if(l<r){
			    a[++m]=r;
    			r--;
			}
		}
		for(int i=1;i<=m;i++){
		    cout<<a[i]<<" ";
		}
		cout<<"\n";
	}
    return 0;
}
```

---

## 作者：joker_opof_qaq (赞：2)

### 题意简述

构造一个长度为 $n$ 的数列使得不存在 $a_i | a_j$ 且 $a_{i+1} | a_{j+1}$。

### 思路来源

因为数列不存在相同的数字，所以如果存在 $a$ 是 $b$ 的倍数，则一定是 $a>b$,所以只需构造奇数位递增，偶数位递减。且满足偶数位的所有数均大于奇数位，此时若 $a_i > a_j$ 则 $a_{i+1} < a_{j+1}$，必定成立。

ac code:
```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<iomanip>
#include<cstring>
#include<string>
#include<cmath>
#include<queue>
#include<map>
#include<list>
#include<stack>
#include<cctype>
#include<cstdlib>
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+ch-48;ch=getchar();}
	return x*f;
}
inline void write(int x) {
	if (x<0)x=-x,putchar('-');
	if (x>9)write(x/10);
	putchar(x%10+'0');
}
int main(){
	int t=read();
	while(t--){
		int l=1,r=read();
		while(l<=r){
			cout<<l++<<" ";
			if(l<=r)cout<<r--<<" ";
		}
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：新哲 (赞：1)

# CF1930B 题解

[题目传送门](https://www.luogu.com.cn/problem/CF1930B)

### 题目分析
因为数列一定不存在相同的数字，所以如果存在 $a$ 是 $b$ 的倍数，则一定是 $a < b$，所以只需构造奇数位递增，偶数位递减。且满足偶数位的所有数均大于奇数位。即构造一个数列，满足 $a_i < a_j$ 时，同时满足 $a_{i+1} < a_{j+1}$ 。

### AC Code

```c++
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int T, l, r;
    cin >> T;
    while (T--)
    {
        l = 1;
        cin >> r;
        while (l <= r)
        {
            cout << l << " ";
            l++;
            if (l <= r) {
                cout << r << " ";
                r--;
            }
        }
        cout << "\n";
    }
    return 0;
}

```

---

## 作者：_Maverick_ (赞：1)

## 题面大意
你有一个长度为 $n$ 的排列 $a$，满足以下性质：
- 使得  $a_i>a_j$  时 $a_i+1<a_j+1$。
## 思路
我们只要不把两个较大的数放一块就行了，然后再将两个相邻的较大数之间插入一个较小数即可。
  
然后考虑如何构造，我们不难发现当偶数位上的每个数都比奇数位上的数大时，数列可以满足当 $a_i>a_j$ 时， $a_i+1<a_j+1$。所以我们让奇数位上数递增，让偶数位上的数递减。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std; 
int T;
int n;
int main() {
	cin >> T;
	while (T--) {
		cin >> n;
		int l = 1, r = n;
		while (l <= r) {
			cout << l << " ";
			l++;
			if (l > r) {
				break;
			}
			cout << r << " ";
			r--;
		}
		cout << endl;
	}
	return 0;
}
```
~~其实费常简单~~

---

## 作者：QingDeng_Star (赞：1)

## 题意
构造一个序列，保证当 $a_i<a_j$ 时，$a_{i+1}<a_{j+1}$。
## 思路
通过观察样例可得当每一个偶数位上的数都比对应的奇数位大的时候，可以满足条件，那么代码就很好敲啦！
## 无注释代码来喽

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--)
	{
		int n;
		cin>>n; 
		int a=1,b=n;
		while(a<=b)
		{
			if(b-a==1) 
			{
				cout<<a<<" ";
				break;
			}
			else
			{
				cout<<a<<" ";
				a++; 
				cout<<b<<" ";
				b--;
			}
		}
		cout<<endl;
	}
    return 0;
}
```

---

## 作者：JOE_ZengYuQiao_0928 (赞：1)

### [先看题](https://www.luogu.com.cn/problem/CF1930B)
### 思路分析
要使 $x \mid y$，那么 $x$ 一定不大于 $y$。

我们可以让构造出来的序列任选出两个数 $i$ 和 $j$，使得 $p_i<p_j$ 的同时 $p_{i+1}>p_{j+1}$。

而一个偶数位上的最小数大于奇数位上的最大数的序列可以满足以上条件。

### 参考代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2005;
int n;
signed main(){
	int T;
	cin>>T;
	while(T--){
		cin>>n;
		int l=1,r=n;
		while(l<=r){
			cout<<l<<" ";
			l++;
			if(l>r)break;
			cout<<r<<" ";
			r--;
		}
		cout<<"\n";
	}
    return 0;
}
```

---

## 作者：liangkairui (赞：0)

# [Permutation Printing](https://www.luogu.com.cn/problem/CF1930B) 题解
## 题意
~~其实很好懂~~，就是让我们构造一个数列，使得当 $a_i > a_j$ 时，$a_{i+1} < a_{j+1}$。或者是当 $a_i < a_j$ 时，$a_{i+1} > a_{j+1}$。
## 思路
首先想到需要不要让相邻的两个较大数放在一起，而是在它们之中插入一个较小的数，满足题目构造要求。

然后考虑如何构造，我们~~不难~~发现当偶数位上的每个数都比奇数位上的数大时，数列可以满足当 $a_i > a_j$ 时，$a_{i+1} < a_{j+1}$。所以我们让奇数位上数递增，让偶数位上的数递减。
## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+7;
int ans[N],cnt=0;
int main()
{
	int temp;
	scanf("%d",&temp);
	while(temp--){
		int n;
		scanf("%d",&n);
		cnt=0;
		int left=1,right=n;
		while(left<=right){
			ans[++cnt]=left++;
			if(left<=right)ans[++cnt]=right--;
		}
		for(int i=1;i<=cnt;i++){
			cout<<ans[i]<<" ";
		}
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：王逸辰 (赞：0)

# CF1930B Permutation Printing 题解
## 思路
题意很好理解，我就不说了。

由题意得当 $a_i>a_j$ 时，那么 $a_{i+1}<a_{j+1}$。

所以构造的思路就出来了：我们只要不把两个较大的数放一块不就行了，然后再将两个相邻的较大数之间插入一个较小数即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t,a,b;
	cin>>t;
	while(t--){
		cin>>b,a=1;
		while(a<=b){
			cout<<a++<<" ";
			if(a<=b)
				cout<<b--<<" ";
		}
		puts("");
	}
	return 0;
}
```

---

## 作者：WhisperingWillow (赞：0)

考虑简单地构造。

因为 $p_i\in{\left\lfloor\dfrac{n}{2}\right\rfloor,n}$ 时，$p_i\mid p_j$ 恒不成立，则对于每个 $i\in[1,\left\lfloor\dfrac{n}{2}\right\rfloor]$可以构造在奇数位构造 $i$，偶数位构造 $n-i+1$。

特判一下 $n\equiv 1\pmod 2$ 的情况。

---

## 作者：Jerry_heng (赞：0)

考虑使 $a_i>a_j,a_{i+1}<a_{j+1}$ 或 $a_i<a_j,a_{i+1}>a_{j+1}$。

AC 代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[100010];
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		int now=0,l=1,r=n,flag=0;
		while(l<=r){
			if(!flag)a[++now]=l++;
			else a[++now]=r--;
			flag^=1;
		}
		for(int i=1;i<=n;i++)printf("%d ",a[i]);
		puts("");
	}
	return 0;
}
```

---

## 作者：Hero_Broom (赞：0)

## 题目描述

**[题目链接](https://www.luogu.com.cn/problem/CF1930B)**

你有构造一个长度为 $n$ 的排列 $p$，满足以下性质：

- 不存在 $i \ne j$ 使得 $p_i \mid p_j$ 并且 $p_{i+1} \mid p_{j+1}$。

## 题目分析

虽然说数列要求满足的性质有点奇怪，但我们稍加分析一下便可以得到，题目是要求我们构造一个序列，使 $\forall i, j \in [1,n]$，当 $a_i>a_j$ 时，满足 $a_{i+1}>a_{j+1}$。

就比如说我们可以观察一下样例：第一组测试数据的输出是 `4 1 2 3`，若 $i=2,j=3$，则 $a_{i+1}=2,a_{j+1}=3$，而正好，$a_i<a_j,a_{i+1}<a_{j+1}$，符合我们的分析结论。

那么要怎么得到这么个数列呢，观察一下样例便可以得到，当奇数位小于它对应的偶数位时，就可以满足要求了。

所以我们可以在代码中加入两个新变量 $x,y$，如果要保证上面的条件成立的话，将 $x$ 初始化为 $1$，$y$ 初始化为 $n$，当 $x \le y$ 时（为的是保证生成的数不会重复），将 $x$ 输出后，若 $x \le y$，就把 $y$ 也输出，然后 `x++,y--`，这一步是为了防止死循环。最后只需要输出换行来进行下一组数据的操作即可。

因此我们就能愉快地把代码写出来啦！如果还没懂的可以看看代码注释。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,x,y;
int main(){
	scanf("%d",&T);//多组测试数据
	while(T--){
		scanf("%d",&n);
		x=1,y=n;//初始化x,y
		while(x<=y){//主循环
			printf("%d ",x++);//x++用在函数内表示先输出x，再将x自增
			if(x<=y) printf("%d ",y--);//x<=y保证不会构造出重复的数据
		}
		printf("\n");//输出换行来进行下一组数据的操作
	}
}
```

---

