# Berserk And Fireball

## 题目描述

有 $n$ 个战士站成一排，第 $i$ 个战士的战力是 $a_i$。所有战士的战力都是两两不同的。

你可以使用两种类型的咒语：

  1. 火球术：你可以消耗 $x$ 点法力值来干掉连续的 $k$ 个战士（你必须干掉正好 $k$ 个，而不能干掉 $\le k$ 个）。

  2. 狂暴术：你可以消耗 $y$ 点法力值，选择站在一起的两个战士使他们展开决斗，战力较弱的那个战士将会被干掉。

我们来举个例子，假设有 $7$ 个战士，其战力分别为 $[2,3,7,8,11,5,4]$，且此时的$k=3$（$k$ 的定义详见火球术）。如果你对战力为 $8$ 与 $11$ 的两个战士施加狂暴术，剩下战士的战力将会变成 $[2,3,7,11,5,4]$（战力为 $8$ 的战士在决斗中战死）。然后如果我们对战力为 $[7,11,5]$ 的战士施加火球术，剩下战士的战力将会变成 $[2,3,4]$。

你想要组建一支军队，因此你想要将所有战士战力的序列从 $a_1,a_2,\cdots,a_n$ 变为 $b_1,b_2,\cdots,b_m$。试计算你所需的最少法力值。

## 样例 #1

### 输入

```
5 2
5 2 3
3 1 4 5 2
3 5```

### 输出

```
8```

## 样例 #2

### 输入

```
4 4
5 1 4
4 3 1 2
2 4 3 1```

### 输出

```
-1```

## 样例 #3

### 输入

```
4 4
2 1 11
1 3 2 4
1 3 2 4```

### 输出

```
0```

# 题解

## 作者：linyihdfj (赞：5)

## D.Berserk And Fireball ##
[博客食用效果更佳](https://www.cnblogs.com/linyihdfj/p/16450318.html)
### 题目描述： ###
[原题面](https://codeforces.com/problemset/problem/1380/D)
### 题目分析： ###
遇到这类题目很明显应该用 $b$ 去匹配 $a$，因为这两个序列两两不相同，所以对于 $b$ 中的每一个元素在 $a$ 中只有唯一的元素可以匹配。所以就记录两个指针，每次找到可以与 $b$ 的这个配对的就好了，那么就是如何考虑代价的问题。 

假设现在考虑的是 $[l,r]$ 中的代价，这里是是指把 $a$ 的这一段删去的代价：

1. 我们可以将这一段全部使用火球术，但是因为可以火球术清理不完所以要先用狂暴术让他们变成 $k$ 的倍数
2. 可以全部使用狂暴术，但是这样做有一个条件就是 $a_{l-1}$ 或 $a_{r+1}$ 大于这一段的最大值，因为这样才能将最大值去掉
3. 如果不满足上述条件但是其实也能使用狂暴术，我们可以使用狂暴术让这一段只剩下 $k$ 个，然后使用火球术清理掉

分析出来这一些那么无解的条件就很好想出来了：
1. $b$ 中未匹配结束但是 $a$ 中已经没了
2. $[l,r]$ 这一段不够使用一次火球术，而且不满足全部使用狂暴术的条件

### 代码详解： ###
```cpp
#include<bits/stdc++.h>
using namespace std;
const long long MAXN = 2e5+5;
const long long INF = 1e18+5;
long long n,m,x,k,y,a[MAXN],b[MAXN];
long long get_ans(long long l,long long r){
	if(l > r)
		return 0;
	long long mx = -1,len = r - l + 1;
	for(long long i=l; i<=r; i++){
		mx = max(mx,a[i]);
	}
	long long ans = 0;
	bool candel = false;
	if(a[l-1] > mx)	candel = true;
	if(a[r + 1] > mx)	candel = true;
	if(len < k && !candel)	return -1;
	long long h = len % k;
	ans = ans + h * y;
	len -= h;
	if(y * k >= x){
		ans += len / k * x;
	} 
	else if(candel){
		ans += len * y;	
	}
	else{
		ans += (len - k) * y + x;
	}
	return ans;
}
int main(){
	cin>>n>>m>>x>>k>>y;
	for(long long i=1; i<=n; i++){
		cin>>a[i];
	}
	for(long long i=1; i<=m; i++){
		cin>>b[i];
	}
	long long l = 1,r = 1,ans = 0;
	bool flag = false;
	while(r <= m){
		long long now_l = l;
		while(l <= n && a[l] != b[r]){
			l++;
		}
		long long tmp = get_ans(now_l,l-1);
		if(tmp == -1 || l == n + 1){
			flag = true;
			break;
		}
		ans += tmp;
		l++;r++;
	} 
	long long tmp = get_ans(l,n);//不能忘记最后的一小段的处理 
	if(tmp == -1){
		flag = true;
	}
	else{
		ans += tmp;
	}
	if(flag){
		printf("-1\n");
	}
	else{
		printf("%lld\n",ans);
	}
	return 0;
}
```
我们可能出现 $b$ 全部匹配完了但是 $a$ 却没有的情况，需要将 $a$ 中剩下的这一部分去掉。因为无论如何都必须将这一段不足 $k$ 的倍数的这写用狂暴术删掉所以就可以提前全删掉。

---

## 作者：灵茶山艾府 (赞：2)

贪心。

先判断 $b$ 是否为 $a$ 的子序列。我的写法是记录 $a$ 中每个元素的位置，然后依次读入 $b$ 中的元素，得到每个需要消灭的区间 $[l,r]$，注意边界。

对于每个需要消灭的区间 $[l,r]$，记区间内的人数为 $cnt$，有如下贪心策略：

1. 若 $cnt<k$ 则只能用法术 $2$，若区间最大值大于区间两侧的最大值，是无法消灭整个区间的，输出 $-1$，否则可以用法术 $2$ 消灭整个区间；

2. 若 $cnt\ge k$ 则需要比较 $x$ 和 $k*y$ 的大小，若 $k*y$ 小则同策略 $1$。注意，若区间最大值大于区间两侧的最大值，则需要在剩下 $k$ 个人时使用一次法术 $1$，不然无法消灭该区间；

3. 接上，若 $x$ 小则可以先用法术 $2$ 消灭 $cnt\%k$ 个人，然后对剩下的人用 $\frac{cnt}{k}$ 次法术 $1$ 即可消灭该区间。

AC 代码 (Golang)：

```go
package main

import (
	"bufio"
	. "fmt"
	"os"
)

func main() {
	in := bufio.NewReader(os.Stdin)
	var n, m, r int
	var x, k, y, sum int64
	Fscan(in, &n, &m, &x, &k, &y)
	a := make([]int, n)
	pos := make([]int, n+1)
	for i := range a {
		Fscan(in, &a[i])
		pos[a[i]] = i // 记录 a 中每个元素的出现位置
	}

	l := -1
	do := func() {
		cnt := int64(r - l - 1) // 需要消灭的人数
		if cnt < 0 { // 说明 b 不是 a 的子序列
			Print(-1)
			os.Exit(0)
		}
		maxP := 0 // 需要消灭的人的最大 power 值
		for _, v := range a[l+1 : r] {
			if v > maxP {
				maxP = v
			}
		}
		edgeP := 0 // 区间两侧的最大 power 值
		if l >= 0 {
			edgeP = a[l]
		}
		if r < n && a[r] > edgeP {
			edgeP = a[r]
		}
		if cnt < k { // 情况 1
			if maxP > edgeP {
				Print(-1)
				os.Exit(0)
			}
			sum += cnt * y
		} else if k*y < x { // 情况 2
			if maxP < edgeP {
				sum += cnt * y
			} else {
				sum += (cnt-k)*y + x
			}
		} else { // 情况 3
			sum += cnt%k*y + cnt/k*x
		}
	}
	for ; m > 0; m-- {
		Fscan(in, &r)
		r = pos[r]
		do() // 处理范围 [l+1,r-1]
		l = r
	}
	r = n
	do() // 处理范围 [l+1,n-1]
	Print(sum)
}
```



---

## 作者：SmallTownKid (赞：0)

其实这题不够2000分的难度，就是个分类讨论。考验代码能力。坑点也都比较明确，理清思路就好做了。

首先可以发现，有两种操作，花费 $x$ 消灭连续的 $k$ 个，花费 $y$ 消灭一个。很直观的一个想法是，谁性价比高就尽可能用谁，不过这里可能会有些问题。因为花费 $y$ 消灭一个的操作有前提条件，必须是一个大消灭一个小，但如果我们要消灭的一个数大于夹在它两边的要保留的数的话，那么这个数无法只通过 $y$ 消去。所以要在这里特判。还有一个特判的点就是，如果块长小于 $k$ ，那么一定只能用 $y$ 操作，而如果此时出现了上述的矛盾，就是 $-1$ 。块长大于等于 $k$ 的时候一定不会出现 $-1$ ，因为我们总是可以把块长变为 $k$ 的倍数，然后用 $x$ 操作消去。

$code:$
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,x,k,y,ans;
int pos[200010],a[200010],b[200010];
bool check()
{
	int l=0,tot=0;
	for(int i=1;i<=m;i++)
	{
		while(a[l]!=b[i])
		{
			l++;
			if(l>n)
			return 0;
		}
		if(a[l]==b[i])
		{
			pos[l]=1;
			tot++;
		}
	}
	return tot==m;
}
signed main()
{
	cin>>n>>m>>x>>k>>y;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	for(int i=1;i<=m;i++)
	{
		cin>>b[i];
	}
	if(!check())
	{
		puts("-1");
		return 0;
	}
	pos[n+1]=1;
	int last=0,maxn=0;
	for(int i=1;i<=n+1;i++)
	{
		if(pos[i]==1)
		{
			int len=i-last-1;//块长 
			if(len<k)//块长<k，只能使用y魔法 
			{
				if(maxn>max(a[last],a[i]))
				{
					puts("-1");
					return 0;
				}
				else
				{
					ans+=len*y;
					maxn=0;
				}
			}
			else//块长大于等于k 
			{
				if(x>y*k)//y魔法更划算
				{
					if(maxn>max(a[last],a[i]))
					{
						ans+=(len-k)*y+x;//最后k个用x消灭 
					}
					else
					{
						ans+=len*y;
					}
				}
				else//x魔法更划算 
				{
					ans+=(len%k)*y+((len-len%k)/k*x);
				} 
			}
			maxn=0; 
			last=i;//更新last的位置
		}
		else//更新块中要消灭的数的最大值 
		{
			maxn=max(maxn,a[i]);
		}
	}
	cout<<ans;
	return 0;
}
```

---

