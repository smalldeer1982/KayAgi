# [ARC161A] Make M

## 题目描述

$N$ 是一个正奇数。我们称一个长度为 $N$ 的序列 $S$ 是 **M 型**序列，当前仅当对于所有的 $i=2,4,6,\dots,N-1$（即偶数位），都有 $S_{i-1}<S_{i}$ 且 $S_{i}>S_{i+1}$。

现在给定你一个长度为 $N$ 的序列 $A$，请你判断能否通过将 $A$ 序列里的元素打乱位置使其变为一个 **M 型**序列。

## 样例 #1

### 输入

```
5
1 2 3 4 5```

### 输出

```
Yes```

## 样例 #2

### 输入

```
5
1 6 1 6 1```

### 输出

```
Yes```

## 样例 #3

### 输入

```
5
1 6 6 6 1```

### 输出

```
No```

# 题解

## 作者：良心WA题人 (赞：2)

## 前言

打的时候结论是猜的，所以这是前四道题里最难的一道题（确信）。

## 题意

给定一个数列，问能否确定一个顺序，使得任意下表为偶数的数都严格大于其相邻的两个数。

## 思路

一个朴素的构造方案是排序后前一半放到奇数后一半放到偶数，这样一定可以满足大于等于。那么我们只需要判断是否能够让它不等于。

对于这类问题，一般需要分奇偶性来考虑。现在先考虑更为简单的偶数。不难发现若存在一个数大于了一半就无法构造出来。

那么奇数呢？好像也是大于了一半就无法构造。但是若是 $\dfrac{n+1}{2}$ 个，则有可能全部放在奇数，这时只能全部放在奇数才有解。

综上，我们可以直接判断跨越中间的数是否相等且大于一半即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NN=2e5+4;
int a[NN];
int main()
{
	int n;
	scanf("%d",&n);
	map<int,int>mp;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		mp[a[i]]++;
	}
	sort(a+1,a+1+n);
	if(a[n/2+1]==a[n/2+2]&&mp[a[n/2+1]]>n/2)
		printf("No");
	else
		printf("Yes");
	return 0;
}
```

---

## 作者：FreedomKing (赞：1)

### 思路

简单题。

考虑构造出给定序列的最优解：排序，将从小到大的数间隔分布，使得构造出的序列最优。然后判断构造出的序列是否合法，输出答案。

### AC Code
```
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int a[N],f[N],n,m,t,k;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i+=2) f[i]=a[++t];//构造奇数位
	for(int i=2;i<n;i+=2) f[i]=a[++t];//构造偶数位
	for(int i=2;i<n;i+=2){
		if(!(f[i]>f[i-1]&&f[i]>f[i+1])){//判断是否合法
			cout<<"No";
			return 0;
		}
	}
	cout<<"Yes";
	return 0;
}
```

---

## 作者：几何微粒子 (赞：0)

此题有两种解法（我想到的有两种）。

### I

针对此题是红题，我们可以采用模拟的思路。

我们直接把这个序列强行变成 M 型序列的形式后判断其能否成为 M 型序列即可。

那么我们将序列排序，让 $\left\lfloor n/2 \right\rfloor + 1$ 为界限，$\left\lfloor n/2 \right\rfloor + 1$ 及其之前的店插入到结果序列 $b$ 的奇数位，$\left\lfloor n/2 \right\rfloor + 1$ 以后的点插入到 $b$ 的偶数位。  

我们为了最大化可能，可以让排序后的数依次插入到对应的位置上，尽量地让小的数旁边是小的数，大的数旁边是大的数。 

然后我们只需要判定 $b$ 是否为 M 型序列即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
#define N 200005
int a[N];
int b[N];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	sort(a+1,a+1+n);
	int top=0;
	for(int i=2;i<=n;i+=2){
		top++;
		b[i]=a[n/2+1+top];
	}
	top=0;
	for(int i=1;i<=n;i+=2){
		b[i]=a[++top];
	}
	for(int i=2;i<n;i+=2){
		if(b[i]<=b[i-1]||b[i]<=b[i+1])
			return printf("No"),0;
	}
	printf("Yes");

	return 0;
}
```

### II

一种更加智慧的方法。

我们观察样例可以得知，如果整个序列半数以上都是同一个数，那么这个数必然决定该序列是否为 M 型。

**而这些数只能被填到奇数位上——因为填到其他位置上就有两个相等的数相邻，就寄了。**

- 如果该序列重复的最多的数字不是最小的数，则肯定会有比他更小的数填到偶数位上，结果不符合 M 型序列条件。
- 如果该序列重复的最多的数字已经超过 $\left\lfloor n/2 \right\rfloor + 1$，则奇数位已经无法塞满这种数字，需要偶数位来塞——强制出现上述加粗字体的情况。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 200005
int a[N];
int n;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i];)
	}
	sort(a+1,a+1+n);
	int last,maxlast=-0x7f7f,num;
	for(int i=1;i<=n;i++){
		if(a[i]==a[i-1]){
			last++;
			if(last>=maxlast){//是>= 
				maxlast=last;num=i; 
			}
		}else{
			last=0;
		}
	}
	if(maxlast>n/2+1)
		printf("No");
	else if(maxlast==n/2+1&&num!=a[1])//此时a[1]最小 
		printf("No");
	else
		printf("Yes");

	return 0;
}

```

---

## 作者：梦应归于何处 (赞：0)

[AC记录](https://www.luogu.com.cn/record/111597401)

题目大意：

给出 $ N $ 和 $ N $ 个正整数 $ A_1,A_2,\dots,A_N $，且 $ N $ 为奇数，对于所有偶数下标 $ i $，有 $ A_i > A_{i-1}$ 且 $ A_i > A_{i+1}$。

## 思路

这题首先我们想一下，这个 $A$ 数组把它里面的最大的 $N\div2$ 个数拿出来，摆到 $N\div2$ 个偶数位上，肯定是最优的，所以我们可以先给 $A$ 数组从大到小排个序，然后找前 $N\div2$ 个数中，比 $A_{N\div2}$ 大的数有多少个，然后再求，除了前 $N\div2$ 个数外，有多少个数和 $A_{N\div2}$ 相等。和 $A_{N\div2}$ 相等的数是不能放在 $A_{N\div2}$ 的相邻的位置的。只能放在比 $A_{N\div2}$ 大的数的左边，这里注意一下，不能放在右边边，我们想一下，如果放在了右边，那他右边的右边如果是 $A_{N\div2}$。那么，就会发现 $A_{N\div2}$ 不大于和它相等的数，就会构造失败。所以，只能放在左边。时间复杂度为 $O(N\log N)$。

下面是代码：

~~~cpp
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
ll a[300000];
int main() {
	ll n;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	sort(a + 1, a + n + 1, greater<ll>());
	ll p = n / 2;
	ll cnt = 0;
	for (int i = 1; i <= p; i++) {
		if (a[i] > a[p]) {
			cnt++;
		}
	}
	ll tot = 0;
	for (int i = p + 1; i <= n; i++) {
		if (a[i] == a[p]) {
			tot++;
		} else {
			break;
		}
	}
	if (cnt >= tot) {
		cout << "Yes";
	} else {
		cout << "No";
	}
	return 0;
}
~~~

---

