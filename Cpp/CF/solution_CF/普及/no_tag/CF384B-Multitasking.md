# Multitasking

## 题目描述

Iahub wants to enhance his multitasking abilities. In order to do this, he wants to sort $ n $ arrays simultaneously, each array consisting of $ m $ integers.

Iahub can choose a pair of distinct indices $ i $ and $ j $ $ (1<=i,j<=m,i≠j) $ . Then in each array the values at positions $ i $ and $ j $ are swapped only if the value at position $ i $ is strictly greater than the value at position $ j $ .

Iahub wants to find an array of pairs of distinct indices that, chosen in order, sort all of the $ n $ arrays in ascending or descending order (the particular order is given in input). The size of the array can be at most ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF384B/423105717bb2ab1ec1635f735571b59733cc0d8f.png) (at most ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF384B/423105717bb2ab1ec1635f735571b59733cc0d8f.png) pairs). Help Iahub, find any suitable array.

## 说明/提示

Consider the first sample. After the first operation, the arrays become $ [1,3,2,5,4] $ and $ [1,2,3,4,5] $ . After the second operation, the arrays become $ [1,2,3,5,4] $ and $ [1,2,3,4,5] $ . After the third operation they become $ [1,2,3,4,5] $ and $ [1,2,3,4,5] $ .

## 样例 #1

### 输入

```
2 5 0
1 3 2 5 4
1 4 3 2 5
```

### 输出

```
3
2 4
2 3
4 5
```

## 样例 #2

### 输入

```
3 2 1
1 2
2 3
3 4
```

### 输出

```
1
2 1
```

# 题解

## 作者：hyacinth_lpy (赞：1)

根据题意，排序的步数绝对不可以超过 $\cfrac{m×(m−1)}{2}$ 步，所以，我们为什么不直接输出 $\cfrac{m×(m−1)}{2}$ 呢，就这样，第一行输出就这样完成了。$\\$
第二步，就是下面的输出，我们可以采取每一次交换两个的方法，来保证这个数组按照规定顺序排序，当然，顺序和逆序肯定是不一样的。
## Code
```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
using namespace std;
typedef long long ll;
inline int read()
{
    int x=0,y=1;
    char c=getchar();
    while(c<'0' || c>'9')
    {
        if(c=='-')y=-1;
        c=getchar();
    }
    while(c>='0' && c<='9')x=(x<<3)+(x<<1)+c-'0',c=getchar();
    return x*y;
}int __lcm(int a,int b){return a*b/__gcd(a,b);}
bool prime(int n)
{
	if(n<2)return false;
	for(int i=2;i<=sqrt(n);i++)if(n%i==0)return false;
	return true;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie();cout.tie();
	//freopen("","r",stdin);
	//freopen("","w",stdout);
	int n,m,k;
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)
	{
		int o;
		cin>>o;
	}
	cout<<m*(m-1)/2<<endl;
	if(k==1)for(int i=1;i<=m;i++)for(int j=m;j>=i+1;j--)cout<<j<<' '<<j-1<<endl;
	else for(int i=1;i<=m;i++)for(int j=1;j<=m-i;j++)cout<<j<<' '<<j+1<<endl;
	return 0;
}
```

---

## 作者：LouYiYang1 (赞：1)

## 思路
因为这道题并不需要求最小步数，只要在限定步数之内即可。那我们可以想到一个不是最优步数的做法。那就是每次交换相邻两个数字，这样做的话不仅可以保证排序结束后数组一定有序，且不会超出步数限制。但是需要注意的是升序和降序数字交换的前后顺序是不一样的。

## AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, k;
int a;
int main() {
	cin>>n>>m>>k;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin>>a;
		}
	}
	cout<<m * (m - 1) / 2<<"\n";
	if (!k) {
		for (int i = 1; i <= m; i++) {
			for (int j = 1; j <= m - i; j++) {
				cout<<j<<" "<<j+1<<"\n";
			}
		}
	} else {
		for (int i = 1; i <= m; i++) {
			for (int j = m; j >= i + 1; j--) {
				cout<<j<<" "<<j-1<<"\n";
			}
		}
	}
	return 0;
}
```

---

## 作者：headache (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF384B)


---

## 闲聊
由于是翻译题，对于输入的数据没有具体解释，根据自己想法，下面是还原版。

第一行输入三个整数 $n,m,k$，表示 $n$ 个长度为 $m$ 的数组和一个排序方式。

$\bullet$ 当 $k=0$ 时，数组升序排序。

$\bullet$ 当 $k=1$ 时，数组降序排序。

接着输入 $n$ 个长度为 $m$ 的数组。

最后输出步数与任意一种排序方案。

## 思路
这道题实际上与 $n$ 无关。

对于交换元素次数，题目只规定了上界，所以并不要求最优方案。

相应得我们可以采取每一次交换两个的方法保证按规定顺序排序，也不会超出步数限制。

## 代码展示
```
#include<bits/stdc++.h>
using namespace std;
int n,m,k,x;
int main(){
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++) cin>>x;
	}
	cout<<m*(m-1)/2<<endl;
	if(k==0){
		for(int i=1;i<=m;i++){
			for(int j=1;j<=m-i;j++) cout<<j<<" <<j+1<<endl;
		}
	}
	else if(k==1){
		for(int i=1;i<=m;i++){
			for(int j=m;j>=i+1;j--)	cout<<j<<" "<<j-1<<endl;
		}
	}
	return 0;
}
```

---

## 作者：lhs_chris (赞：0)

# 题目大意
给你 $n$ 个长度为 $m$ 的数组和一个只能为 $0$ 或者 $1$ 的整数 $k$。要求你同时对所有数组进行最多 $\frac {m \times (m-1)}{2}$ 次交换操作使得所有数组按题目要求的升序或者降序排序好。

当 $k$ 为 $0$ 时，数组必须按升序排序，否则必须按降序排序。

进行交换操作时选择两个位置 $i$ 和 $j$，只有当位置 $i$ 的值**严格大于**位置 $j$ 的值时，才会交换两者位置。

# 思路
因为这道题并不需要求最小步数，只要在限定步数之内即可。那我们可以想到一个不是最优步数的做法。那就是每次交换相邻两个数字，这样做的话不仅可以保证排序结束后数组一定有序，且不会超出步数限制。但是需要注意的是升序和降序数字交换的前后顺序是不一样的。

# 代码
```cpp
#include<bits/stdc++.h>
#include<cstring>
#include<queue>
#include<set>
#include<stack>
#include<vector>
#include<map>
#define ll long long
#define lhs printf("\n");
using namespace std;
const int N=1e5+10;
const int M=2024;
const int inf=0x3f3f3f3f;
int n,m,k; 
int a;
int ans;
int main()
{
	scanf("%d%d%d",&n,&m,&k);
  //这道题和n没关系，只和m,k有关系。
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			scanf("%d",&a);
		} 
	}
	printf("%d\n",m*(m-1)/2);//直接输出
  //注意顺序
	if(!k)
	{
		for(int i=1;i<=m;i++)
		{
			for(int j=1;j<=m-i;j++)
			{
				printf("%d %d\n",j,j+1);
			}
		}
	} 
	else
	{
		for(int i=1;i<=m;i++)
		{
			for(int j=m;j>=i+1;j--)
			{
				printf("%d %d\n",j,j-1);
			}
		}
	}
	return 0;
}
```

---

## 作者：N_z_ (赞：0)

## 前言
不是啥正经解法。
## 思路
我们仔细观察一下题目，发现它说要在内$m*(m-1)/2$ 步给 $n$ 个 $m$ 位序列排序。

$m*(m-1)/2$ ，那么我们考虑每两位进行一个交换，刚好 $m*(m-1)/2$ 步，且一定排好了序。

具体见代码。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,m,k;
	cin>>n>>m>>k;
	cout<<m*(m-1)/2<<endl;
	if(k)for(int x=m;x>1;x--)for(int y=m;y>m-x+1;y--)cout<<y<<' '<<y-1<<endl;
	else for(int x=m-1;x;x--)for(int y=1;y<=x;y++)cout<<y<<' '<<y+1<<endl;
}
```
## 后记
~~只要读入个 $m$ 就行了。~~

---

