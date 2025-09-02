# Transfusion

## 题目描述

现给定一个数组 $a$ 和 数组的长度 $n$。规定在一次操作中，你可以从 $2$ 到 $n-1$ 中选取任意一个数 $i$，完成下面的一个操作：
- 令 $a_{i-1}$ 减 $1$，令 $a_{i+1}$  加 $1$。
- 令 $a_{i-1}$ 加 $1$，令 $a_{i+1}$  减 $1$。

**每次操作都要保证得到的数为非负数。**
在进行若干次操作后，能否使 $a$ 的每个数都相等？

## 样例 #1

### 输入

```
8
3
3 2 1
3
1 1 3
4
1 2 5 4
4
1 6 6 1
5
6 2 1 4 2
4
1 4 2 1
5
3 1 2 1 3
3
2 4 2```

### 输出

```
YES
NO
YES
NO
YES
NO
NO
NO```

# 题解

## 作者：long_long__int (赞：1)

# 题目翻译

[这里](https://www.luogu.com.cn/paste/6977jr5z)。

# 题目解法

由于每次操作都是隔一个数操作，所以奇数位的总和和偶数位的总和都不变。如果奇数位的平均值不是整数，偶数位的平均这不是整数或者奇数位的平均值不等于偶数位的平均值（无法使奇数位和偶数位的数一样），那么肯定不行。否则可以。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
int n;
void work(){
	double a,b;int sa,sb;//此sb（sum b）非彼sb 
	a=b=sa=sb=0;
	cin>>n;
	for(int i=1;i<=n;i++) {
		int x;
		cin>>x;
		if(i&1) a+=x,sa++;
		else b+=x,sb++;
	}
	a/=sa,b/=sb;
	if(a!=b or int(a)!=a or int(b)!=b) return printf("No\n"),void();
	printf("Yes\n");
}
int main(){
	cin>>T;
	while(T--) work();
	return 0;
}
```

---

## 作者：wuyouawa (赞：1)

### 题目大意

有 $t$ 组数据，每组数据给定一个序列，每次可以对相隔一个元素的两个值一个 $+1$，一个 $-1$，问随意操作后是否可以使得序列所有值相等。

### 思路

考虑贪心。

我们可以发现每次操作过后，总和和平均数是不变的，所以我们先把总和存起来，然后判断平均数是否是整数，如果不是就不行，因为不是的话无法实现全等，如果等于的话，那么我们就再遍历一次，先把 $a_{i+2}$，也就是相隔一个的元素增加或减少把 $a_i$ 变成 $p$ 需要的数，接着把 $a_i$ 变成 $p$，最后判断是否全等即可。

注意开 long long 及清空。
### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,a[200005],s,p,w;//注意开long long 
int main(){
	scanf("%lld",&t);
	while(t--)
	{
		scanf("%lld",&n);
		s=0;//清空 
		for(int i=1;i<=n;i++)
		{
			scanf("%lld",&a[i]);
			s+=a[i];//求和 
		}
		if(s%n==0)
		{
			p=s/n;
			w=0;//清空 
			for(int i=1;i<n-1;i++)
			{
				if(a[i]>p)  a[i+2]+=a[i]-p;
				else  a[i+2]-=(p-a[i]);//加减相应的数
				a[i]=p;//把ai变成p 
			}
			for(int i=1;i<=n;i++)
			{
				if(a[i]==p)  ;
				else  w=1;//记录是否全等 
			}
			if(w==0)  printf("YES\n");
			else  printf("NO\n");//根据记录判断 
		}
		else
		{
			printf("NO\n");//平均数非整数就不行 
		}
	}
	return 0;
} 
```

---

## 作者：SuyctidohanQ (赞：0)

### 题目分析

比较简单。考虑染色。

所有元素能够相等，当且仅当奇数下标的元素平均值是整数，而且奇数下标元素平均值等于偶数下标的元素平均值。

### 代码实现

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
void read ();
ll T, n;
void read () {
	cin >> n;
	ll sum1 = 0, sum2 = 0, x;
	for (ll i = 1; i <= n; i ++) {
		cin >> x;
		if (i % 2) sum1 += x;
		else sum2 += x;
	}
	if (sum1 % ((n + 1) / 2) != 0 || sum2 % (n / 2) != 0 || (sum1 / ((n + 1) / 2)) != sum2 / (n / 2)) cout << "NO" << endl;
	else cout << "YES" << endl;
}
int main () {
	cin >> T;
	while (T --) read ();
	return 0;
}
```

---

## 作者：GeYang (赞：0)

# 题意

给你一个序列，每次对某个数的前后两个数一个加上一，一个减去一，问能不能有某种操作使得所有元素相等。

# 思路

你只能对所有位数的奇偶性相同的数做这些操作。

因为每次操作就是一个数加一，一个数减一，所以序列所有元素总和不变。

所以，位数为奇数的所有数的平均值必须等于位数为偶数的所有数的平均值，才能有机会所有数相等。

如果上面那句话过于冗长，你或许可以看看下面这个例子：一个长度为四的序列，第一位和第三位的平均值要等于第二位和第四位的平均值。

---

## 作者：banglee (赞：0)

## CF2050B Transfusion 题解
[洛谷传送门](https://www.luogu.com.cn/problem/CF2050B)

[Codeforces 传送门](https://codeforces.com/problemset/problem/2050/B)
## 思路
注意到这些运算只改变奇偶性相同的位置上的元素。因此，可以直接求奇数和偶数位置上的元素。

考虑创建两个数组 $od$ 和 $ev$。$od$ 数组表示包含奇数位置上的所有元素，$ev$ 数组表示包含偶数位置上的所有元素。

任意选取数组 $od$ 或 $ev$，然后任意选取相邻的两个元素，从其中一个元素中减去 $1$ 并在另一个元素中加上 $1$。为了使数组 $od$ 中的所有元素相等，$od$ 中所有元素的和必须能被 $|od|$ 整除，$ev$ 中所有元素的和也必须能被 $|ev|$ 整除，其中 $|a|$ 是数组 $a$ 的长度。

此外，要使初始数组的所有元素相等，必须满足 $\dfrac{sum(od)}{|od|} = \dfrac{sum(ev)}{|ev|}$。

最终输出 `YES` 或 `NO` 即可，记得多测清空。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int T;
signed main() {
    ios::sync_with_stdio(!(cin.tie(0) && cout.tie(0)));
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int &x: a)
            cin >> x;
        int ods = 0, evs = 0;
        for (int i = 0; i < n; i++) {
            if (i & 1) ods += a[i];
            else evs += a[i];
        }
        int odc = n / 2, evc = n / 2;
        if (n & 1) evc++;
        if (ods % odc != 0 || evs % evc != 0 || ods / odc != evs / evc) cout << "NO\n";
        else cout << "YES\n";
    }
    return 0;
}
```

---

## 作者：HYdroKomide (赞：0)

### 题意：

给定一个序列，每次可以对相隔一个元素的两个值一个 $+1$，一个 $-1$，问随意操作后是否可以使得序列所有值相等。

### 思路：

考虑经典黑白格染色，将序列染成黑白间隔的颜色。所有操作都只能在某一种颜色上进行，而序列所有元素值之和一定不变。

因此，所有元素能够相等，当且仅当奇数下标的元素平均值是整数，而且奇数下标元素平均值等于偶数下标的元素平均值。

要开 long long。

### 程序如下：

```cpp
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
int T,n;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		long long tot1=0,tot2=0;
		for(int i=1;i<=n;i++){
			int a;
			scanf("%d",&a);
			if(i%2==1)tot1+=a;
			else tot2+=a;
		}
		if(tot1%((n+1)/2)!=0||tot2%(n/2)!=0||(tot1/((n+1)/2))!=tot2/(n/2))printf("NO\n");
		else printf("YES\n");
	}
	return 0;
}
```

### THE END

---

