# Thanos Sort

## 题目描述

[灭霸排序](https://codegolf.stackexchange.com/questions/182221/implement-the-thanos-sorting-algorithm)是一种超级反派排序算法。

它是这样运行的：  
对于一个序列$a$,满足$\forall i<j,a_i\le a_j$，就停止排序；  
否则删掉这个序列的左半边或右半边。   
按此规则重复执行，直到满足上述条件。  

现在给你一个序列，对其进行这种排序算法后，最大长度会是多少呢？

## 说明/提示

$n\in\{1,2,4,8,16\}$  
$1\le a_i\le 100$

## 样例 #1

### 输入

```
4
1 2 2 4
```

### 输出

```
4
```

## 样例 #2

### 输入

```
8
11 12 1 2 13 14 3 4
```

### 输出

```
2
```

## 样例 #3

### 输入

```
4
7 6 5 4
```

### 输出

```
1
```

# 题解

## 作者：Doveqise (赞：1)

这道题根据题意模拟吧emmm数据范围只有16海星  
（暴力水）（CF愚人节系列）  
分治求解OwO  
细节见代码↓
```c++
#include<bits/stdc++.h>
using namespace std;
int a[17],ans=1;
bool pd(int l,int r){
  for(int i=l;i<r;i++) if(a[i]>a[i+1]) return 0;
  return 1;}
void solve(int l,int r){
  if(l>=r)return;
  if(pd(l,r))ans=max(ans,r-l+1);
  int mid=(l+r)>>1;
  solve(l,mid);solve(mid+1,r);
}
signed main(){
  int n;scanf("%d",&n);
  for(int i=1;i<=n;i++)scanf("%d",&a[i]);
  solve(1,n);printf("%d",ans);
  return 0;
}
```

---

## 作者：破忆 (赞：1)

### 题目大意
给一个序列，如果不是递增就删掉一半，然后重复执行


------------

### 解法
n不大，完全可以纯模拟

用**分治**解决，代码短，思路清晰

------------
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=20;
int n,a[maxn];
int read(){
	int ret=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-f;ch=getchar();}
	while(ch>='0'&&ch<='9') ret=ret*10+ch-48,ch=getchar();
	return ret*f;
}
int DFS(int L,int R){//表示从L到R最长能保留的长度
	if(R<=L) return 1;
	int mid=L+R>>1;
	for(int i=L;i<R;i++) if(a[i]>a[i+1]) return max(DFS(L,mid),DFS(mid+1,R));//如果不满足，就拆成2半，挑长度较长的
	return R-L+1;//满足条件直接弹出长度
}
int main(){
// 	freopen("CF1145A.in","r",stdin);
// 	freopen("CF1145A.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++) a[i]=read();
	printf("%d\n",DFS(1,n));
	return 0;
}
```


---

## 作者：jxbe6666 (赞：0)

### 题意
给一个序列，如果不是递增就删掉一半，然后重复执行，求它的最大长度。

-----

### 思路
分治，可以采用 $\texttt{dfs}$ 递归。

-----

### 代码

-----

```c++
#include <bits/stdc++.h>
using namespace std;
const int N = 20;
int n, a[N];
int read()
{
    int ret = 0, f = 1;
    char ch = getchar();
    while (ch > '9' || ch < '0')
    {
        if (ch == '-')
            f = -f;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
        ret = ret * 10 + ch - 48, ch = getchar();
    return ret * f;
}
int dfs(int L, int R)
{ //表示从L到R最长能保留的长度
    if (R <= L)
        return 1;
    int mid = L + R >> 1;
    for (int i = L; i < R; i++)
        if (a[i] > a[i + 1])
            return max(dfs(L, mid), dfs(mid + 1, R)); //如果不满足，就拆成2半，挑长度较长的
    return R - L + 1;
}
int main()
{
    n = read();
    for (int i = 1; i <= n; i++)
        a[i] = read();
    printf("%d\n", dfs(1, n));
    return 0;
}

```


---

## 作者：Yizhixiaoyun (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1145A)

~~这种水题居然错了好几次~~。

## 题目分析

本题做法考虑**分治**。

我们先对序列进行判断，判断其是一个单调不减的数列。

如果是那么返回，返回的最大长度就是当前的序列长度。

否则就将序列拆成两半，分别判断序列前一半以及后一半继续判断，直到运行到可以返回为止。

## 贴上代码

```cpp
#include<iostream>
using namespace std;
int max(int a,int b){if(a>b) return a;return b;}
int n,a[25];
int ans=1;
bool work(int l,int r){
	for(register int i=l;i<r;++i){
		if(a[i]>a[i+1]) return false;
	}
	return true; 
}
void solve(int l,int r){
	if(l>=r) return;
	if(work(l,r)==true) ans=max(r-l+1,ans);
	int mid=(l+r)>>1;
	solve(l,mid);solve(mid+1,r);
}
int main(){
	cin>>n;
	for(register int i=1;i<=n;++i) cin>>a[i];
	solve(1,n);
	cout<<ans;
}
```

---

## 作者：Luo_gu_ykc (赞：0)

## 题目大意
给定一个序列，如果这个序列是单调不减的，就停止排序，否则就将这个序列折半(可以折左边的，也可以折右边的)。
给你一个长度为 $n$ 的序列 $a$，问最后的最大长度能达到多少。
## 思路
分治思想，先看这个序列是否单调不减。
1. 是

	- 那么就与长度取 $\max$。
    
2. 不是

	- 分类讨论折左边还是右边。
    
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 25;
int n, a[N], ans;
bool check(int x, int y){ // 判断是否单调不减
	for(int i = x + 1; i <= y; i++){
		if(a[i - 1] > a[i]){
			return false;
		}
	}
	return true;
}
void help(int lt, int rt){
	int mid = (lt + rt) >> 1;
	if(check(lt, rt) == false){ // 不是
		help(lt, mid); // 折掉右边
		help(mid + 1, rt); // 折掉左边
	} else {
		ans = max(ans, rt - lt + 1); // 统计长度
		return ;
	}
}
int main(){
	cin >> n;
	for(int i = 1; i <= n; i++){
		cin >> a[i];
	}
	help(1, n);
	cout << ans; 
	return 0;
}
```

---

## 作者：清清老大 (赞：0)

## 思路

本题可以通过分治的方法解决。

因为灭霸排序每次删去一半的数字，所以可以用递归函数。函数先判断数组是否已经排序，如果已经排序就返回数组长度，如果没有排序则用递归分类讨论删去的是前一半还是后一半，算完后再返回它们之中最大的长度。当左端点大于等于右端点时，返回 $1$ 。在主函数内调用这个函数就可以得到答案了。

## 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

int a[20] = {0};

bool is_sorted(int l,int r)
{
    for(int i = l;i < r;i ++)
    {
        if(a[i] > a[i + 1])
        {
            return false;
        }
    }
    return true;
}

int solve(int l,int r)
{
    if(l >= r)
    {
        return 1;
    }
    if(is_sorted(l,r))
    {
        return r - l + 1;
    }
    else
    {
        return max(solve(l,(l + r) / 2),solve(((l + r) / 2) + 1,r));
    }
}

int main()
{
    int n;
    cin >> n;
    for(int i = 1;i <= n;i ++)
    {
        cin >> a[i];
    }
    cout << solve(1,n);
}
```


---

## 作者：YYen (赞：0)

### 思路：分治
先判断原序列是否是不减序列，如果是长度就为序列长度；如果不是递归判断序列前一半和序列后一半。

### 代码：
```cpp
#include <iostream>
#include <cstring>
#include <bitset>
using namespace std;

int a[20]; 

// 计算下标l~r之间的最大长度 
int check(int l, int r)
{
    bool flag = true;
    for (int i = l + 1; i <= r; i++) if (a[i] < a[i - 1]) flag = false;
    if (flag) return r - l + 1;
    int a = check(l, (r + l) / 2);
    int b = check((r + l) / 2 + 1, r);
    return max(a, b);
}

int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    cout << check(1, n) << endl;
    return 0;
}
```


---

## 作者：CZQ_King (赞：0)

~~分治啥玩意，又不能吃~~

思路：

大约是打表，因为$n$很小，而且只可能是二的幂：
- 如果$n=16$那么判断$0$到$15$是否单调递增，如果是，直接输出$16$并结束
- 如果$n\ge8$那么判断$0$到$7$和$8$到$15$是否单调递增，如果是，直接输出$8$并结束
- 如果$n\ge4$那么判断$0$到$3$、$4$到$7$、$8$到$11$、$12$到$15$是否单调递增，如果是，直接输出$4$并结束
- 以此类推，如果都没有直接输出$1$。

首先放出判断单调递增的函数：
```cpp
bool f(int l,int len){//左端点和长度
	if(l>=n)return 0;//如果不在范围内返回0（这个十分重要）
	for(int i=l+1;i<l+len;i++)
		if(a[i-1]>a[i])return 0;//如果不单调递增返回0
	return 1;//单调递增返回1
}
```

那么我们只需要调用函数，多次判断即可（强迫症福利）：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[16];//零浪费
bool f(int l,int len){//判断单调递增的函数
	if(l>=n)return 0;
	for(int i=l+1;i<l+len;i++)
		if(a[i-1]>a[i])return 0;
	return 1;
}
int main(){
	cin>>n;
	for(int i=0;i<n;i++)cin>>a[i];
	if(n==16)if(f(0,16)                                                           ){cout<<0x10;return 0;}//如果=16（16进制输出只是为了对齐
	if(n>=8) if(f(0,8 )||                        f(8,8)                           ){cout<<0x08;return 0;}//>=8的情况
	if(n>=4) if(f(0,4 )||        f(4,4)||        f(8,4)||         f(12,4)         ){cout<<0x04;return 0;}//>=4的情况
	if(n>=2) if(f(0,2 )||f(2,2)||f(4,2)||f(6,2)||f(8,2)||f(10,2)||f(12,2)||f(14,2)){cout<<0x02;return 0;}//>=2的情况
	puts("1");//都没有
}
```

---

## 作者：徐致远 (赞：0)

首先这题的数据范围非常小，而且n是2的整数次幂，所以我们可以先枚举答案的大小，从大到小，每次折半。

由于最后的序列必定为原序列上连续的一段，所以直接枚举最后剩余的区间就行了。然后检查合法性。

```cpp
#include<cstdio>
using namespace std;
const int maxn=20;
int n,A[maxn];
inline int read()
{
	int ret=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();}
	while(ch>='0'&&ch<='9'){ret=ret*10+ch-'0';ch=getchar();}
	return ret*f;
}
int main()
{
	n=read();
	for(int i=1;i<=n;i++) A[i]=read();
	for(int ans=n;ans>=1;ans/=2)
	{
		for(int i=1;i<=n-ans+1;i+=ans)
		{
			bool suc=true;
			for(int j=i;j<i+ans-1;j++)
				if(A[j]>A[j+1])
					suc=false;
			if(suc)
			{
				printf("%d\n",ans);
				return 0;
			}
		}
	}
	return 0;
}
```

---

