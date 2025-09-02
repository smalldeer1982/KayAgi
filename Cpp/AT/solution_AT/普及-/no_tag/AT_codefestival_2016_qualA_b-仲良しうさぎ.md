# 仲良しうさぎ

## 题目描述

有 $N$ 个数，第 $i$ 个数为 $a_i$。让你求出符合 $a_i = j$ 且 $a_j = i$ 的情况有几种（重复算一种）

## 样例 #1

### 输入

```
4
2 1 4 3```

### 输出

```
2```

## 样例 #2

### 输入

```
3
2 3 1```

### 输出

```
0```

## 样例 #3

### 输入

```
5
5 5 5 5 1```

### 输出

```
1```

# 题解

## 作者：eEfiuys (赞：2)

题目：[AT2031](https://www.luogu.com.cn/problem/AT2031)
## 思路：
- $a(i) = j$, $a(j) = i$，即 $a(a(i)) = i$, $a(a(j)) = j$。
- $2 \le N \le 10^5$, $1 \le a(i) \le N$，所以 $a(a(i))$ 可以直接存下。
- $a(i) = j$ 时算了一次, $a(j) = i$ 时又算了一次，且 $a(i) \not= i$，每个都算了两次，所以最终答案除以 $2$。

------------

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans;
const int N=1e5+1;
int a[N];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<=n;i++)
		if(a[a[i]]==i) //a(i)=j，后面的某一个i即为j，不用考虑a(j)=i。
			ans++;
	cout<<ans/2<<endl; //重复算了一次。
	return 0;
}
```

---

## 作者：·糯· (赞：0)

## 题目分析
我们可以用一个布尔类型的数组来存这两个数有没有被读过，如果未读过就判断它们是否满足条件，满足就将方案数加一并标记成已读过。
## 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100010],sum;
bool vis[100010];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<=n;i++)
		if(!vis[i]&&!vis[a[i]]&&a[a[i]]==i){//都没读过且满足条件
			sum++;
			vis[i]=true;
			vis[a[i]]=true;//标记已读过
		}
	cout<<sum<<endl;
	return 0;
}
```


---

## 作者：Nygglatho (赞：0)

首先，我们会发现，每一个 $a_i$ 都是仅仅指向（等于）一个 $j$，不会指向（等于）其它的数字。\
举个例子：题目的样例 $1$ 中的 $a_1$ 仅仅指向（等于）$2$，而不会指向（等于）$3$ 或 $4$。

那么，我们就可以利用这个特性来编了。既然只指向（等于）一个 $j$，那么我们直接判断一下 $a_j$ 是不是也指向（等于）$i$ 就行了。

由于 $a_i$ 只指向（等于）$j$，我们可以直接把 $a_j$ 写成 $a_{a_i}$。

Code:
```cpp
	ans = 0;
	for (int i = 1; i <= n; i++)
		scanf ("%d", &a[i]);
	for (int i = 1; i <= n; ++i) {
		if (a[a[i]] == i) ans++;
	}
```
最后，由于每一对 $i$ 和 $j$ 都算了一次，一共两次，除以 $2$ 就行了（题目保证了 $a_i \neq i$。）

---

