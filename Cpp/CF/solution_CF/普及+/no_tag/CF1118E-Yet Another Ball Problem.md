# Yet Another Ball Problem

## 题目描述

The king of Berland organizes a ball! $ n $ pair are invited to the ball, they are numbered from $ 1 $ to $ n $ . Each pair consists of one man and one woman. Each dancer (either man or woman) has a monochrome costume. The color of each costume is represented by an integer from $ 1 $ to $ k $ , inclusive.

Let $ b_i $ be the color of the man's costume and $ g_i $ be the color of the woman's costume in the $ i $ -th pair. You have to choose a color for each dancer's costume (i.e. values $ b_1, b_2, \dots, b_n $ and $ g_1, g_2, \dots g_n $ ) in such a way that:

1. for every $ i $ : $ b_i $ and $ g_i $ are integers between $ 1 $ and $ k $ , inclusive;
2. there are no two completely identical pairs, i.e. no two indices $ i, j $ ( $ i \ne j $ ) such that $ b_i = b_j $ and $ g_i = g_j $ at the same time;
3. there is no pair such that the color of the man's costume is the same as the color of the woman's costume in this pair, i.e. $ b_i \ne g_i $ for every $ i $ ;
4. for each two consecutive (adjacent) pairs both man's costume colors and woman's costume colors differ, i.e. for every $ i $ from $ 1 $ to $ n-1 $ the conditions $ b_i \ne b_{i + 1} $ and $ g_i \ne g_{i + 1} $ hold.

Let's take a look at the examples of bad and good color choosing (for $ n=4 $ and $ k=3 $ , man is the first in a pair and woman is the second):

Bad color choosing:

- $ (1, 2) $ , $ (2, 3) $ , $ (3, 2) $ , $ (1, 2) $ — contradiction with the second rule (there are equal pairs);
- $ (2, 3) $ , $ (1, 1) $ , $ (3, 2) $ , $ (1, 3) $ — contradiction with the third rule (there is a pair with costumes of the same color);
- $ (1, 2) $ , $ (2, 3) $ , $ (1, 3) $ , $ (2, 1) $ — contradiction with the fourth rule (there are two consecutive pairs such that colors of costumes of men/women are the same).

Good color choosing:

- $ (1, 2) $ , $ (2, 1) $ , $ (1, 3) $ , $ (3, 1) $ ;
- $ (1, 2) $ , $ (3, 1) $ , $ (2, 3) $ , $ (3, 2) $ ;
- $ (3, 1) $ , $ (1, 2) $ , $ (2, 3) $ , $ (3, 2) $ .

You have to find any suitable color choosing or say that no suitable choosing exists.

## 样例 #1

### 输入

```
4 3
```

### 输出

```
YES
3 1
1 3
3 2
2 3
```

## 样例 #2

### 输入

```
10 4
```

### 输出

```
YES
2 1
1 3
4 2
3 4
4 3
3 2
2 4
4 1
1 4
3 1
```

## 样例 #3

### 输入

```
13 4
```

### 输出

```
NO
```

# 题解

## 作者：furbzy (赞：2)

首先我们要认真[读题](https://www.luogu.com.cn/problem/CF1118E)

蒟蒻模拟题。

我们考虑一共有多少方案。

首先对于第一个数，可以取任意一个 $1 \sim k$ 的整数，一共 $k$ 种方案。那么第二个数呢？因为不能和第一个数重复，所以第二个数有 $k-1$ 种方案。

**所以取两个数有 $k \times (k-1) = k^2-k$ 种方案。如果 $n \leq k^2-k$，那么输出 yes，否则无解，输出 no。**

接下来我们考虑怎么编排方案。

设每次取出的两数为 $a,b$。

根据题意，有 $a_{i-1} \neq a_i,b_{i-1} \neq b_i$。

显然，我们不能按顺序枚举。

**所以，我们考虑每输出一对方案 $a,b$，就输出另一对方案 $b,a$。**

话不多说，上AC代码：

```c
#include<bits/stdc++.h>
#define ri register int
#define in inline
using namespace std;
in int read()	//快读 
{
	int ans=0;
	bool j=false;
	char c=getchar();
	while(!(isdigit(c)))
	{
		if(c=='-')
		j=true;
		c=getchar();
	}
	while(isdigit(c))
	{
		ans=(ans<<3)+(ans<<1)+(c^48);
		c=getchar();
	}
	return j? ~ans+1:ans;
}
int main()
{
	//freopen("a.in","r",stdin);    本人调代码时习惯加文件操作
	//freopen("escape.out","w",stdout);    此处无用，可删 
	long long m,n,cnt=0;    //cnt表示已输出cnt个数对 
	scanf("%lld %lld",&m,&n);
	if(m>n*n-n)
	{
		printf("no");  //输出任意字母的大小写都行
		return 0;
	}
	printf("yes\n");
	for(ri i=1;i<=n;i++)
	{
		for(ri j=i;cnt<m&&j<=n;j++)    //i前面的已经枚举过 
		{
			if(i==j)
			continue;
			if(cnt<=m-2)    //还需输出>=2个数对 
			printf("%d %d\n%d %d\n",i,j,j,i);
			else
			printf("%d %d",i,j);
			cnt+=2;
		}
		if(cnt>=m)
		break;
	}
	return 0;
}
```
本人第一次写题解，写的不好，请多指教。

~~说实话这应该是红题。~~

---

## 作者：decoqwq (赞：2)

考虑贪心

直接$1-2\ 2-3\ 3-4...$即可

易得有$n^2-n$对

如果$k\leq n^2-n$，依次输出即可，否则就不行
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    long long n,k;
    cin>>n>>k;
    if(n>k*(k-1))
    {
        cout<<"No";
        return 0;
    }
    cout<<"Yes"<<endl;
    int del=1,flag=0,now=0;
    for(;flag==0;del++)
    {
        for(int j=1;j<=k;j++)
        {
            ++now;
            printf("%d %d\n",j,(j+del)>k?(j+del)%k:(j+del));
            if(now==n)
            {
                flag=1;
                break;
            }
        }
    }
}
```

---

## 作者：Crazyouth (赞：1)

## 分析

~~这题怎么也不应该有绿啊。~~

我们考虑一种非常简单的构造方式（以 $k=4$ 为例）：

```
1 2
1 3
1 4
2 3
2 4
3 4
```
显然这个构造不符合要求，也不是构造最多组数的策略，但是注意到在每一组 $(a_i,b_i)$ 接上一组 $(b_i,a_i)$ 就可以弥补这两个缺点，即：

```
1 2
2 1
1 3
3 1
...
```

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
vector<pair<int,int>> ans;
int main()
{
	int n,k,a=1,b=2;
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		if(b==k+1) a++,b=a+1;
		if(a==k+1||b==k+1)
		{
			cout<<"NO";
			return 0;
		}
		ans.push_back({a,b});
		if(i==n) break;
		ans.push_back({b,a});
		i++;
		b++;
	}
	cout<<"YES"<<endl;
	for(auto p:ans) cout<<p.first<<' '<<p.second<<endl;
}
```

---

## 作者：jiangruibo (赞：0)

### 思路；
做法：找到一组的就倒过来即找到第二组，若 $k\times (k - 1) < n $ 则一定达不到那么多的组数，输出 NO 即可。
### 代码： 
```~~~~
#include <bits/stdc++.h>
//#pragma GCC optimize(1)
//#pragma GCC optimize(2)
//#pragma GCC optimize(3)
#define int long long
#define endl "\n"
#define ull unsigned long long
#define write(n,x) cout<<setprecision(n)<<fixed<<x
typedef long long LL;
using namespace std;

signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n,k;
	cin>>n>>k;
	if(k*(k-1)<n)//如果所有加起来的个数都不满足
	{
		cout<<"No"<<endl;
		return 0;
	}
	cout<<"Yes"<<endl;
	int temp=n;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=i;j++)
		{
			if(i!=j) //题目限制
			{
				temp--;
				cout<<i<<" "<<j<<endl;
				if(temp==0)//如果个数已够
				{
					return 0;
				}
           //倒过来
				temp--;
				cout<<j<<" "<<i<<endl;
				if(temp==0)//如果个数已够
				{
					return 0;
				}
			}
		}
	}
	return 0;
}
/*
*/
```

---

## 作者：Merge_all (赞：0)

### 题目要求
- 对于每个 $b_{i}$ 和 $g_{i}$ 都是1到$k$之间的整数；
- 没有相同的 $b_{i}=b_{j}$ ，$g_{i}=g_{j}$；
- $b_{i} \neq g_{i}$
- 对于 $i$ 从 1 到 $n$ 都满足 $b_{i}\neq b_{i+1}$ 和 $g_{i}\neq g_{i+1}$

### 思路：
每一轮设定 $b_{i}$ 和 $g_{i}$ 的差值，$b_{i}$ 和 $g_{i}$ 同加 1，这样可以不重复。下一轮就把差值增加 1，相当于在下一轮中 $b_{j}=b_{i}$ 但 $g_{j}=g_{j}+1$ 或者 $g_{j}=g_{i}$ 但 $b_{j}=b_{j}+1$

### 代码：
```c
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
#define int long long
int n, k;
int b[N], g[N];
map<pair<int, int>, bool> vis;

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> k;
	if(k * (k - 1) < n) {
		cout << "NO";
		return 0;
	}
	b[1] = 0, g[1] = 1;
	vis[{0, 1}] = 1;
	for (int i = 2; i <= n; i ++) {
		b[i] = (b[i - 1] + 1) % k, g[i] = (g[i - 1] + 1) % k;
		if(vis[{b[i], g[i]}]){
			g[i] ++;
			g[i] %= k;
		}
		vis[{b[i], g[i]}] = 1;
	}
	cout << "YES\n";
	for (int i = 1; i <= n; i ++) {
		cout << b[i] + 1 << ' ' << g[i] + 1 << endl;
	}
	return 0;
}
```

---

## 作者：xu_zhihao (赞：0)

### 题目理解：
   - 有点像模拟，构造合法二元组。第一，合法二元组一定只有 $k \times(k+1)$ 个，这个非常好证明，即二元组中的 $a_i$ 有 $k$ 种数字选法，$b_i$ 有 $k-1$ 种数字选法。所以如果 $n$ 大于 $k\times(k-1)$，那即为无解。
   - 接下来讨论有解情况。
   
       - 当 $k  \bmod 2=0$，只用枚举每一种合法的二元组 $(a_i,b_i)$，既可以输出 $(a_i,b_i)$ 和 $(b_i,a_i)$，记为一组。输出 $ \frac{n}{2}$ 组即可。
       - $k  \bmod 2=1$，前 $ \frac{n-1}{2}$ 组与上列方法相同，最后一个二元组单独输出即可。
       
### AC 代码：

   
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	long long int n,k;
	cin>>n>>k;
	long long int sum=k*(k-1);
	if(n>sum)
	{
		cout<<"NO";
		return 0;
	}
	int cnt=0;
	int p=1;
	cout<<"YES"<<endl;
	int u=0;
	for(int i=k;i>=1;i--)
	{
		
		for(int j=k-i+2;j<=k;j++)
		{
			cout<<p<<" "<<j;
			cout<<endl;
			cout<<j<<" "<<p;
			cout<<endl;
			cnt+=2;
			u=j+1;
			if(cnt+1>=n)
			{
				break;
			}
		}
		if(cnt+1>=n)
		{
			break;
		}
		p++;
	}
	if(n%2==1)
	{
		if(u==k+1)
		{
			p++;
			u=k-(k-p+1)+2;
		}
		cout<<p<<" "<<u;
	}
	return 0;
} 
```

[AC 记录](https://www.luogu.com.cn/record/152120685)

~~这个蒟蒻码风真丑。~~

---

## 作者：_VEGETABLE_OIer_xlc (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1118E)

易得 $k$ 个数共能组成 $k^2-k$ 个二元数组。

所以若 $n>k^2-k$ 时无解。

那么有解怎么办呢？

输出中说：对于相邻两个二元组，对应的 $a_i$ 和 $b_i$ 不同。

那么就不能直接循环输出了。

~~通过观察样例 1 可得~~，我们只要在输出 $a$ 和 $b$ 时再输出 $b$ 和 $a$ 就可以了。

这告诉我们，关注样例是重要的。

~~感觉这题只有橙。~~

AC 代码奉上。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll n,k,cnt=1;
int main(){
	cin>>n>>k;
	if(n>k*(k-1))
	{
		cout<<"NO";
		return 0;
	}
	cout<<"YES"<<endl;
	for(int i=1;i<=k;i++)
	{
		for(int j=i+1;j<=k;j++)
		{
			cout<<i<<" "<<j<<endl;
			cnt++;
			if(cnt>n)return 0;
			cout<<j<<" "<<i<<endl;
			cnt++;
			if(cnt>n)return 0;
		}
	}
	return 0;
}
```

---

## 作者：lmz_ (赞：0)

我们先来考虑无解情况。

第一个数可以选择 $k$ 种数，第二个数因为不能选择第一个数，只能选择 $k-1$ 种数字，则两个数一共有 $k \times (k-1)$ 种选择，化简后就是 $k^2-k$ 种，如果 $k^2-k \leq n$，则无解，直接输出`NO`。

如果有解，先输出`YES`，我们再来思考正解。

我们假设第 $i$ 个二元组为 $(a_i,b_i)$，最优情况下，第 $i+1$ 个二元组应该为 $(b_i,a_i)$，因为这样可以让数字不变的情况下，二元组最多，也方便计算。

我们使用双层循环枚举 $(a_i,b_i)$，每次输出两个二元组 $(a_i,b_i)$ 和 $(b_i,a_i)$，如果已经输出 $n$ 个了，就不再输出。

代码：
```cpp
#include<bits/stdc++.h>
#define ull unsigned long long
#define ud unsigned double
#define db double
#define ll long long
using namespace std;
const int maxn = 1e6,INF=0x7fffffff;
ll n,k,s;
int main(){
	cin>>n>>k;
	if(n>k*k-k){
		cout<<"No";
		return 0;
	}
	cout<<"Yes\n";
	for(int i=1;i<=k;i++){
		for(int j=i;j<=k&&s<n;j++){
			if(i==j) continue;
			if(n-s>=2) cout<<i<<' '<<j<<endl<<j<<' '<<i<<endl;
			else cout<<i<<' '<<j<<endl;
			s+=2;
		}
		if(s>=n) break;
	}
	return 0;
}
```
生活小技巧：你谷的爬虫有问题，交两次就好了，第二次爬取的是第一次的结果。

---

