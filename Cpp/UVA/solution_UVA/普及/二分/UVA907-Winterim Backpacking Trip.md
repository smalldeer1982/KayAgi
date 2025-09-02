# Winterim Backpacking Trip

## 题目描述

你在进行一次远足。你现在已知路上有 $N$ 个营地，你这次远足将耗时 $K$ 个夜晚和每两个营地之间的距离。

你的每个夜晚必须在一个营地度过且你不可以走回头路。也就是说，你白天必须得走到某一个营地。

现在你需要求出：你走的最多的那天走了多远？

## 说明/提示

$N$ 小于等于 $600$ , $K$ 小于等于 $300$ 。

## 样例 #1

### 输入

```
4 3
7
2
6
4
5```

### 输出

```
8```

# 题解

## 作者：__owowow__ (赞：4)

### UVA907 Winterim Backpacking Trip 题解
[洛谷传送门](https://www.luogu.com.cn/problem/UVA907)
$\\$
[UVA传送门](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=11&page=show_problem&problem=848#google_vignette)
### 题意
要把一个长 $n$ 的序列分成 $k$ 份，使得最长的序列尽量短。
$\\$
**有多测！**~~调试了好久~~
### 思路
最大，最小，考虑二分答案。关键代码如下：
```cpp
bool check(int num){
    int cnt=0,sum=0;
    for(int i=1;i<=n;i++){
        if(a[i]>num) return false;//如果单独按长度比num大，就不行，返回
        sum+=a[i];
        if(sum>num) sum=a[i],cnt++;
    }
    return cnt<=k;
}
```
### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a[1000],ans;
int l,r,mid;
bool check(int num){
    int cnt=0,sum=0;
    for(int i=1;i<=n;i++){
        if(a[i]>num) return false;
        sum+=a[i];
        if(sum>num) sum=a[i],cnt++;
    }
    return cnt<=k;
}
int main(){
    while(cin>>n>>k){//多测
        l=1,r=0,ans=0;//赋初值
        n++;//一定要加一
        for(int i=1;i<=n;i++) cin>>a[i],r+=a[i];
            while(l<=r){//二分模版
                mid=(l+r)/2;
                if(check(mid)) r=mid-1,ans=mid;
                else l=mid+1;
            }
        cout<<ans<<endl;//输出
    }

    return 0;//华丽结束
}
```

---

## 作者：Shadow_T (赞：2)

CSP 前夕，写一篇题解，希望这不是我的最后一篇。

这题打开题面，求的是最小的最大距离。很容易的，我们可以想到二分答案。对于每一个 $mid$ 判断可以理解为贪心，对于如果可以走就走，不能走才度过夜晚。如果最终的度过夜晚数不超过 $k$，则我们是为可以，尝试缩小答案；否则放大答案。

这里给大家解答一个二分的常见问题：什么时候用 $(l+r+1)\div2$ 什么时候用 $(l+r)\div2$ 呢？其实只要看如果在放大答案的时候如果是 $l=mid$，那么就要加一。如果是 $l=mid+1$ 就不用。

注意多测且这题输入的是 $n+1$ 个数。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int s[602];
int n,k;
bool check(int x)
{
	int l=0,day=0;
	for(int i=1;i<=n+1;i++)
	{
		if(s[i]>x) return false;
		l+=s[i];
		if(l>x) day++,l=s[i];
	}
	return day<=k;
}
void solve()
{
	for(int i=1;i<=n+1;i++)
	cin>>s[i];
	int l=1,r=1e9,ans;
	while(l<r)
	{
		int mid=(l+r)/2;
		if(check(mid)) ans=mid,r=mid;
		else l=mid+1;
	}
	cout<<ans<<"\n";
}
int main()
{
	while(cin>>n>>k) 
	solve();
}
```

最后祝大家和我自己 rp++！

---

## 作者：zhouzihang1 (赞：1)

# UVA907 Winterim Backpacking Trip 题解

[洛谷传送门](https://www.luogu.com.cn/problem/UVA907)

[UVA 传送门](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=11&page=show_problem&problem=848)

[博客，更好的阅读体验](https://www.luogu.com.cn/blog/827018/uva907-winterim-backpacking-trip-ti-xie)

## 题意

有 $N+2$ 个节点，选出 $K$ 个节点使得被分开的区间**最大和最小**。

## 思路

通过**最大和最小**可以想到二分。

那么，二分的上届和下届就应该分别是 $\sum_{i=1}^{n} a_i$ 和 $1$。

表示走的最远的这一天最远能走 $\sum_{i=1}^{n} a_i$，最近能走 $1$。

对于 $check$ 函数，我们可以开两个变量分别统计天数和走的路程。

如果从上一个营地到当前走的距离已经超过二分的 $mid$ 了，就让计数器加一，最后统计出走的天数就可以返回了。

## Code

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N=6e2+10;
int n,k,a[N];
bool check(int m)
{
	int cnt=0,sum=0;//cnt统计天数,sum累加路程 
	for(int i=1;i<=n;i++)
	{
		if(a[i]>m) return 0;//一次走的就比m大那肯定不行 
		sum+=a[i];
		if(sum>m) sum=a[i],cnt++;//记得把sum赋值为a[i],因为从i开始是新的一天 
	}
	return cnt<=k;
}
void solve()
{
	int l=1,r=0,mid,ans=0;n++;
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),r+=a[i];//输入 & 计算二分上届 
	while(l<=r)//二分板子 
	{
		mid=l+r>>1;
		if(check(mid)) r=mid-1,ans=mid;
		else l=mid+1;
	}
	printf("%d\n",ans);
}
int main()
{
	while(scanf("%d%d",&n,&k)!=EOF) solve();
	//有多测！有多测！有多测！ 
	return 0;
}

```

---

## 作者：zhangjiting (赞：1)

## 题意

你在进行一次远足。你现在已知路上有 $N$ 个营地，你这次远足将耗时 $K$ 个夜晚和每两个营地之间的距离。

你的每个夜晚必须在一个营地度过且你不可以走回头路。也就是说，你白天必须得走到某一个营地。

现在你需要求出你走的最多的那天走了多远？

## 思路

看到最大值最小，想到 dp。

$dp_{i,j}$ 表示从 $j$ 个数字中切 $i$ 次所得的最小的最大值。

可以推出转移方程式：

$dp_{i,j}=\min(dp_{i,j},\max(dp_{i-1,k},s_{k-j}))$。

$s$ 数组是 $a$ 数组的前缀和，$s_{k-j}$ 表示 $a_j$ 到 $a_k$ 的和。

答案就是 $dp_{k,n+1}$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int dp[305][605],a[605],sum[605];
int main(){
	int n,k;
    while(scanf("%d%d",&n,&k)!=EOF){
		memset(dp,0,sizeof(dp));memset(a,0,sizeof(a));memset(sum,0,sizeof(sum));
		for(int i=1;i<=n+1;i++){
			cin>>a[i];
			dp[0][i]=sum[i]=sum[i-1]+a[i];
		}
		for(int i=1;i<=k;i++)
			for(int j=1;j<=n+1;j++){
				dp[i][j]=INT_MAX;
				for(int k=1;k<=j;k++)
					dp[i][j]=min(dp[i][j],max(dp[i-1][k],sum[j]-sum[k]));
			}
		cout<<dp[k][n+1];
	}
	return 0;
}
```




---

## 作者：Kun_is_Me (赞：0)

# UVA907 Winterim Backpacking Trip 题解

~~又是每周一篇的题解。~~

[安插 Luogu 题墓传送门。](https://www.luogu.com.cn/problem/UVA907)

[安插 UVA 题墓传送门。](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=11&page=show_problem&problem=848)

[安插专栏传送门。](https://www.luogu.com.cn/article/t4l3u4kd)

### 题意描述。

现在，你正在进行一场远足。（~~不就是远足嘛。~~）你现在已知路上有 $n$ 个营地，你这次远足将耗时 $k$ 个夜晚和每两个营地之间的距离。

你的每个夜晚必须在一个营地度过且你不可以走回头路。也就是说，你白天必须得走到某一个营地。

现在你需要求出：你走的最多的那天走了多远？

其实就是求最小的最大距离。（好绕。）

### 解题思路。

很容易想到二分，对吧？

我们只需要对每一个 $mid$（代码中为 $md$）进行处理就可以了。

至于怎么处理嘛，贪心会吧？

如果可以走就走，不能走才度过夜晚。（~~不能熬夜欧~~）如果最终的度过夜晚数不超过 $k$，则认为可以，尝试缩小答案；否则放大答案。

### 上代码。

```cpp
#include<bits/stdc++.h>//万能头好！
using namespace std;
int n,k,a[1000],ans;
int l,r,mid;
bool check(int num)
{
    int cnt=0,sum=0;
    for(int i=1;i<=n;i++){
        if(a[i]>num) return false;
        sum+=a[i];
        if(sum>num) sum=a[i],cnt++;
    }
    return cnt<=k;
}
int main()
{
    while(cin>>n>>k)//多测好！
    {
        l=1,r=0,ans=0;
        n++;
        for(int i=1;i<=n;i++) cin>>a[i],r+=a[i];
        while(l<=r)//二分好！
        {
            mid=(l+r)/2;
            if(check(mid)) r=mid-1,ans=mid;
            else l=mid+1;
        }
        cout<<ans<<endl;
    }

    return 0;//
}
```

---

