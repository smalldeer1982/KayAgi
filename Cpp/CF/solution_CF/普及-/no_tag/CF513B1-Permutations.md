# Permutations

## 题目描述

You are given a permutation $ p $ of numbers $ 1,2,...,n $ . Let's define $ f(p) $ as the following sum:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF513B1/01b3997850b3844bd3627bf7c28ebf2176a4c489.png)Find the lexicographically $ m $ -th permutation of length $ n $ in the set of permutations having the maximum possible value of $ f(p) $ .

## 说明/提示

In the first example, both permutations of numbers {1, 2} yield maximum possible $ f(p) $ which is equal to 4. Among them, $ (2,1) $ comes second in lexicographical order.

## 样例 #1

### 输入

```
2 2
```

### 输出

```
2 1 
```

## 样例 #2

### 输入

```
3 2
```

### 输出

```
1 3 2 
```

# 题解

## 作者：Universal_xtr (赞：2)

新人 Universal_xtr 的第二篇题解。

## 思路

仔细观察题面，不难发现 $f$ 函数 $\sum_{i=1}^{n} \sum_{j=i}^{n} \min_{x=i}^{j} p_x$ 其实就是求 $n$ 的某个排列 $p$ 的每一个子段的最小值。我们可以枚举 $n$ 的全排列，而对于每一个排列 $perm_i$，求出它所有子段的最小值之和 $s$，如果 $s$ 大于当前最大值 $ans$，则更新 $ans$；又如果 $s$ 等于 $ans$，统计个数加 $1$ 。


**ps：在这题，求每个子段的最小值可以暴力枚举左右端点，再用列表切片和 `min` 函数求出。**

## 注意事项

- 枚举全排列时要按字典序枚举，这样可以保证输出的第 $m$  个排列符合题目要求。
- 如果当前的个数已经大于 $m$ 了，那可以直接 `return` 掉。
- 如果当前的个数恰好等于 $m$，输出后就可以直接结束程序（`sys.exit()`）。

- 函数开始一定要 `global` 引入全局变量，否则会抛出 `UnBoundLocalError` 。

现在奉上 AC 代码：
```python
import sys
n,m=map(int,input().split())
sys.setrecursionlimit(1000001) #自行定义递归最大深度，防止默认长度的系统栈爆掉
l=[]
cnt,ans=0,-2147483648
def perm(depth:int):
    global ans,cnt #全局化cnt和ans
    if cnt>m:return #如果当前个数已经超过所需的m了，那证明当前的"最大值"不是真的最大值，所以直接退出
    if depth==n+1:
        s=0
        for i in range(0,len(l)-1):
            for j in range(i+1,len(l)):s+=min(l[i:j+1]) #求出每个子段的最小值
        if s>ans: #更新答案
            cnt=0
            ans=s
        if s==ans:cnt+=1
        if cnt==m: #条件成立
            print(*l)
            sys.exit() #找到了就直接结束程序
        return
    for i in range(1,n+1): #枚举全排列
        if i in l:continue
        l.append(i)
        perm(depth+1)
        l.pop()
perm(1)
```
感谢收看！

update on 2021.10.3 15:00：增加了代码的注释。

---

## 作者：Fire_flame (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/solution/CF513B1)

# 分析
首先解释一下 $f(p)$ 的公式部分：枚举一个集合里的一些数，把它们的最小值记录下来，最后求和。

当 $f(p)$ 最大时，把字典序最大的第 $m$ 个排列作为输出。

发现这个题目实际上是一个枚举全排列的题目。

用深搜完成：

```cpp
for(int i=1;i<=n;i++){
		if(!used[i]){
			a[d]=i;
			used[i]=1;
			dfs(d+1);
			used[i]=0;
		}
}
```

然后枚举每一个排列的 $f(p)$ 值，求出它们中的最小值。

```cpp
for(int i=1;i<=n;i++){
	for(int j=i;j<=n;j++){
		int k=1e9;
		for(int t=i;t<=j;t++){
			k=min(a[t],k);
		}
		h+=k;
	}
}
```

最后记录一下 $f(p)$ 的最大值
```cpp
if(h>ans){
	ans=h;
	cnt=0;
}
if(h==ans)cnt++;
```

最终代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,cnt,ans;
int a[55];
int used[55];
void dfs(int d){
	if(cnt>=m)return ;
	if(d>n){
		int h=0;
		for(int i=1;i<=n;i++){
			for(int j=i;j<=n;j++){
				int k=1e9;
				for(int t=i;t<=j;t++){
					k=min(a[t],k);
				}
				h+=k;
			}
		}
		if(h>ans){
			ans=h;
			cnt=0;
		}
		if(h==ans)cnt++;
		if(cnt==m){
			for(int i=1;i<=n;i++)printf("%d ",a[i]);
			return ;
		}
		return ;
	}
	for(int i=1;i<=n;i++){
		if(!used[i]){
			a[d]=i;
			used[i]=1;
			dfs(d+1);
			used[i]=0;
		}
	}
}
int main(){
	scanf("%d%d",&n,&m);
	dfs(1);
	return 0;
}
```


---

## 作者：xvl_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF513B1)

一道枚举题。

数据范围非常小，考虑暴力枚举全排列。

可以 `dfs` 两次，第一次求出能使 $f(p)$ 取得的最大值。第二次求出第 $m$ 个排列。

注意一下，第二次 `dfs` 的时候需要按字典序枚举。

### Code

```cpp
#include <bits/stdc++.h>
#define ll long long
#define INF 1e9
using namespace std;
int n, m, cnt = 1, maxf = -INF;
int res[10];
bool vis[10];
void dfs1(int cur) {
    if (cur > n) {
        int sum = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = i; j <= n; j++) {
                int minp = INF;
                for (int k = i; k <= j; k++) minp = min(minp, res[k]);
                sum += minp;
            }
        }
        maxf = max(maxf, sum);
        return ;
    }
    for (int i = 1; i <= n; i++) {
        if (vis[i]) continue;
        vis[i] = 1;
        res[cur] = i;
        dfs1(cur + 1);
        vis[i] = 0;
    }
}
void dfs2(int cur) {
    if (cur > n) {
        int sum = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = i; j <= n; j++) {
                int minp = INF;
                for (int k = i; k <= j; k++) minp = min(minp, res[k]);
                sum += minp;
            }
        }
        if (sum == maxf) {
            if (cnt == m) {
                for (int i = 1; i <= n; i++) cout << res[i] << " ";
                exit(0);
            }
            cnt++;
        }
        return ;
    }
    for (int i = 1; i <= n; i++) {
        if (vis[i]) continue;
        vis[i] = 1;
        res[cur] = i;
        dfs2(cur + 1);
        vis[i] = 0;
    }
}
signed main() {
    ios :: sync_with_stdio(0);
    cin >> n >> m;
    dfs1(1);
    memset(vis, 0, sizeof(vis));
    dfs2(1);
    return 0;
}
```


---

## 作者：封禁用户 (赞：0)

# 题目描述

[Permutations](https://www.luogu.com.cn/problem/CF513B1)

# 算法思路

先枚举所有排列求出最大的 $f_{p}$，然后枚举所有排列，求出所有使得 $f_{p}$ 最大的长度为 $n$ 的排列中，字典序第 $m$ 小的排列。

数据范围 $n=8$，可以使用 c++ 函数库里的 ```next_permutation```，不知道 ```next_permutation``` 的同学可以[点这里](https://blog.csdn.net/weixin_52115456/article/details/127626074)。

### 时间复杂度：$O(n^3 n!)$。

## 代码
```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=20;
ll n,m,minn,maxx,cnt,ans,a[N];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		a[i]=i;
	}
	do
	{
		ans=0;
		for(int i=1;i<=n;i++)
		{
			for(int j=i;j<=n;j++)
			{
				minn=n+1;
				for(int k=i;k<=j;k++)
				{
					minn=min(minn,a[k]);
				}
				ans+=minn;
			}
		}
		maxx=max(maxx,ans);
	}
	while(next_permutation(a+1,a+n+1));
	for(int i=1;i<=n;i++)
	{
		a[i]=i;
	}
	do
	{
		ans=0;
		for(int i=1;i<=n;i++)
		{
			for(int j=i;j<=n;j++)
			{
				minn=n+1;
				for(int k=i;k<=j;k++)
				{
					minn=min(minn,a[k]);
				}
				ans+=minn;
			}
		}
		if(ans==maxx)
		{
			cnt++;
		}
		if(cnt==m)
		{
			for(int i=1;i<=n;i++)
			{
				cout<<a[i]<<" ";
			}
			cout<<"\n";
			return 0;
		}
	}
	while(next_permutation(a+1,a+n+1));
	return 0;
}
```

---

## 作者：WangBng (赞：0)

因为此题 n 很小，考虑 $O(n! \times n^3)$ 的算法。

通过头文件 `algorithm` 自带的 `next_permutation` 枚举全排列，$O(n^3)$ 计算 $\sum\limits_{i=1}^{n}\sum\limits_{j=i}^{n}\min(a_i,a_{i+1}\cdot\cdot\cdot a_j)$

Code：

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int a[15];
int main(){
	int n,m,ans=0,mas=0,baxms=0,cnt=0;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		a[i]=i;
	}
	do{
		ans=0;mas=0;
		for(int i=1;i<=n;i++){
			for(int j=i;j<=n;j++){
				mas=n+1;
				for(int k=i;k<=j;k++){
					mas=min(mas,a[k]);
				}
				ans+=mas;
			}
		}
		baxms=max(baxms,ans);
	}while(next_permutation(a+1,a+n+1));
	for(int i=1;i<=n;i++){
		a[i]=i;
	}
	do{
		ans=0;mas=0;
		for(int i=1;i<=n;i++){
			for(int j=i;j<=n;j++){
				mas=n+1;
				for(int k=i;k<=j;k++){
					mas=min(mas,a[k]);
				}
				ans+=mas;
			}
		}
		if(ans==baxms){
			cnt++;
		}
		if(cnt==m){
			for(int i=1;i<=n;i++){
				cout<<a[i]<<" ";
			}
			return 0;
		}
	}while(next_permutation(a+1,a+n+1));
	return 0;
}

```

---

## 作者：Eason_AC (赞：0)

## Content
给定两个整数 $n,m$。定义 $f(p)=\sum\limits_{l=1}^n\sum\limits_{r=l}^n\min\limits_{i=l}^rp_i$，其中 $p$ 为一个长度为 $n$ 的排列。现在，请你求出所有使得 $f(p)$ 最大的长度为 $n$ 的排列中，字典序第 $m$ 小的排列。

**数据范围：$1\leqslant n\leqslant 8$。**
## Solution
看到数据范围马上想到一种很 naive 的 $O(n!\cdot n^3)$ 的做法：先枚举所有的排列求出最大的 $f(p)$，然后再枚举所有的排列扫到使得 $f(p)$ 最大的字典序第 $m$ 小的排列。

`next_permutation` 可以更方便地枚举全排列，具体看代码。
## Code
```cpp
namespace Solution {
	const int N = 17;
	int n, m, mx, p[N];
	
	iv Main() {
		read(n, m); F(int, i, 1, n) p[i] = i;
		do {
			int sum = 0;
			F(int, l, 1, n) F(int, r, l, n) {
				int mn = 10;
				F(int, i, l, r) mn = min(mn, p[i]);
				sum += mn;
			}
			mx = max(mx, sum);
		}while(next_permutation(p + 1, p + n + 1));
		int cnt = 0;
		F(int, i, 1, n) p[i] = i;
		do {
			int sum = 0;
			F(int, l, 1, n) F(int, r, l, n) {
				int mn = 10;
				F(int, i, l, r) mn = min(mn, p[i]);
				sum += mn;
			}
			if(sum == mx) {
				cnt++;
				if(cnt == m) {
					F(int, i, 1, n) printf("%d%c", p[i], " \n"[i == n]);
					break;
				}
			}
		}while(next_permutation(p + 1, p + n + 1));
		return;
	}
}
```

---

