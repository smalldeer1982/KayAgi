# Well-known Numbers

## 题目描述

Numbers $ k $ -bonacci ( $ k $ is integer, $ k&gt;1 $ ) are a generalization of Fibonacci numbers and are determined as follows:

- $ F(k,n)=0 $ , for integer $ n $ , $ 1<=n&lt;k $ ;
- $ F(k,k)=1 $ ;
- $ F(k,n)=F(k,n-1)+F(k,n-2)+...+F(k,n-k) $ , for integer $ n $ , $ n&gt;k $ .

Note that we determine the $ k $ -bonacci numbers, $ F(k,n) $ , only for integer values of $ n $ and $ k $ .

You've got a number $ s $ , represent it as a sum of several (at least two) distinct $ k $ -bonacci numbers.

## 样例 #1

### 输入

```
5 2
```

### 输出

```
3
0 2 3
```

## 样例 #2

### 输入

```
21 5
```

### 输出

```
3
4 1 16
```

# 题解

## 作者：boluo2014 (赞：2)

这道题目很简单啊。
### 思路

先理解这个数列怎么算就可以了。

正常的菲斐波那契数列是前两项的和，而这里就是前面所有的和。我们先把这个数列搞出来，有手即可。没有的话，可以去买一个。

而由于题目保证数据有解，所以制度要不断地从这个数中减去一个最接近它且小于等于它的扩展斐波那契数，接下来依次遍历，找到小于且最接近新的数的扩展斐波那契数，以此类推，直到这个数变成 $0$。

### 代码
第一步，先构造 $f$，也就是那个数列。
```
for(i=2;f[i-1]<s;i++)
{
    for(j=max(1,i-k);j<=i-1;j++)
    {
        f[i]+=f[j];
    }
}
```
第二步，依次找下来。
```
for(i=s;i>=1;i--)//再大的不管
{
    if(s>=f[i])
    {
        s-=f[i];
        c++;//计数器+1
        ans[c]=f[i];//做个标记，方便输出
    }
}
```
为了避免个数太少，所以随便在后面加几个 $0$。

比如：
```
ans[c+1]=ans[c+2]=0;
c+=2;
```
后面输出就可以了。
```
for(i=1;i<=c-1;i++)
{
    cout<<ans[i]<<' ';
}
cout<<ans[c]<<endl;
```
会了吗？

---

## 作者：HllwEureka (赞：2)

**我们可以用数学归纳法证明。**

```cpp
结论：重复从s中减掉最大的Fi，一定能使s=0。不是很清楚为什么就可以这样
```


若对于正整数k∀s∈[0,Fk−1]该结论成立，则∀s∈[Fk,Fk+1−1]，其下最大的Fi为Fk，而s−Fk∈[0,Fk−1−1]，其必然也能按上述方法减至0。
而因为k=1时该结论成立，所以∀s该结论均成立。

```
#include <cstdio>
#include <algorithm>
using namespace std;
int const N=1e5+10;
long long f[N];
int n,m,ans[N];
int main()
{
    int s,k; scanf("%d%d",&s,&k);
    int n; f[1]=1;
    for(n=2;f[n-1]<s;n++)
        for(int j=max(1,n-k);j<=n-1;j++) f[n]+=f[j];
    int m=0;
    for(int i=n-1;i>=1&&s;i--) if(f[i]<=s) ans[++m]=f[i],s-=f[i];
    if(m<2) ans[++m]=0;
    printf("%d\n",m);
    for(int i=1;i<=m;i++) printf("%d ",ans[i]);
    puts("");
    return 0;
}
```


---

## 作者：pitiless0514 (赞：1)

## CF225B Well-known Numbers
#### 1.题目描述：

将一个数拆成若干个 $k$ 阶斐波那契数的和，要求总数不小于 $2$ 。
#### 2.解析：

我们都知道传统的斐波那契数列是 $f_i=f_{i-1}+f_{i-2}$ 。是将前两个数加起来作为自己的值。而扩展的斐波那契数列就是将自己的前 $k$ 个数加起来作为自己的值。

然后在 $f_k$ 之前的数为 $0$ ， $f_k=1$ 。

我们发现 $k$ 很大。直接去求就死了。

那么我们可以把 $k$ 当为 $1$ ，然后所有数减去一个 $k$ 。

这样就是从 $0$ 开始了，然后因为在 $k$ 之前的数都为 $0$ 。
所以不需要考虑这些数的值，然后计算每个 $f$ 就做前缀和就完事了。

然后因为我们知道斐波那契数在几千次后已经很大了，同理的我们只用求几千次的 $k$ 阶斐波那契数，然后从大到小往下取。

如果取出来，个数不满，那就加上 $0$ 就是了。

因为 $0$ 也是一个满足要求的斐波那契数。

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int N = 50000;
int sum,k,s[N],f[N],tot,ans[N],num;
signed main(){
	ios::sync_with_stdio(0);cin.tie(0),cout.tie(0);
	cin>>sum>>k;
	
	//你模拟一下，就发现他就是加前面的k个
	f[0]=0;f[1]=1;f[2]=1;
	s[0]=0;s[1]=1;s[2]=2;
	int g=0;
	for(int i=3;i<=4000;i++){
		int it=max(i-k,(int)1);
		f[i]=s[i-1]-s[it-1];
		s[i]=s[i-1]+f[i];
		if(f[i]<0){
			g=i-1;
			break;
		}
	}
	for(int i=g;i>=1;i--){
		if(sum>=f[i]){
			sum-=f[i];
			ans[++num]=f[i];
		}
	}
	if(num<=2){
		ans[++num]=0;
	}
	sort(ans+1,ans+num+1);
	cout<<num<<"\n";
	for(int i=1;i<=num;i++){
		cout<<ans[i]<<" ";
	}
	return 0;
}
```


---

## 作者：OIerZhang (赞：0)

# [CF225B Well-known Numbers](https://www.luogu.com.cn/problem/CF225B)

这真的有这么难，还需要看题解吗……

## 思路

我看到楼上大佬用数学归纳法证明一定有解，真的根本没有必要。我们再仔细看看英文题面的输出格式，里面很明确地说了，“数据保证有解”。

那么就可以直接写代码啦！

不要被 $s \le 10^9$ 的数据吓到了，普通斐波那契数列的第 $100$ 项就已经有 $20$ 位了，数组最多开到 $100$。

只需要先暴力求出数列，再从大到小枚举数列中元素，加入答案即可。

注意有两个坑点：

1. 暴力求出数列可能会 UB，需要特判，超过 $10^9$ 就不用求了。
2. $s$ 至少要拆成两个数，不够的话在后面补 $0$ 即可。

## 代码

```cpp
#include <iostream>
using namespace std;

int a[105], ans[105], cnt;

int main()
{
	int n, k, pos;
	cin >> n >> k;
	a[2] = 1;
	for (int i = 3; i <= 100; i++) // 暴力求数列
	{
		if (a[i - 1] > 1e9) // 1 号坑
		{
			pos = i - 1;
			break;
		}
		for (int j = max(1, i - k); j < i; j++)
		{
			a[i] += a[j];
		}
	}
	for (int i = pos; i >= 1; i--) // 枚举数列中元素
	{
		if (a[i] == 0)
			break;
		if (a[i] > n)
			continue;
		ans[++cnt] = a[i];
		n -= a[i];
	}
	if (cnt < 2) // 2 号坑
		cnt = 2;
	cout << cnt << endl;
	for (int i = 1; i <= cnt; i++)
		cout << ans[i] << ' ';
	return 0;
}
```

不要让你我账号搁浅。  
拒绝抄袭，从我做起。

---

## 作者：QWQ_123 (赞：0)

根据斐波那契数列的增长速度（也就是 $k=2$ 时），我们发现，实际上很快这个数组就会 $\ge 10^9$，所以这个数组其实有效数值很短。

所以考虑算出来，然后依次从高往低考虑，只要能选就选（因为最后还有 $1$，所以无论如何都可以取完）。

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int s, k;
vector<int> res;
ll sum = 0;

int main() {
	res.push_back(1);
	sum = 1;
	scanf("%d%d", &s, &k);
	for (int i = k + 2, j = k; sum <= 1000000000; ++i) {
		res.push_back(sum);
		sum += res.back();
		// cout << sum << ' ' << i << ' ' << j << ' ';
		if (i - j > k) {
			sum -= res[j - k];
			++j;
		}
		// cout << sum << endl;
	}

	vector<int> ans;

	for (int i = (int)res.size() - 1; i >= 0; --i) {
		int t = s / res[i];
		s %= res[i];

		for (int j = 1; j <= t; ++j) ans.push_back(res[i]);
	}

	if (ans.size() == 1) ans.push_back(0);

	printf("%d\n", (int)ans.size());
	for (auto  v : ans) printf("%d ", v);

	return 0;
}
```

---

