# Equalize Prices

## 题目描述

There are $ n $ products in the shop. The price of the $ i $ -th product is $ a_i $ . The owner of the shop wants to equalize the prices of all products. However, he wants to change prices smoothly.

In fact, the owner of the shop can change the price of some product $ i $ in such a way that the difference between the old price of this product $ a_i $ and the new price $ b_i $ is at most $ k $ . In other words, the condition $ |a_i - b_i| \le k $ should be satisfied ( $ |x| $ is the absolute value of $ x $ ).

He can change the price for each product not more than once. Note that he can leave the old prices for some products. The new price $ b_i $ of each product $ i $ should be positive (i.e. $ b_i > 0 $ should be satisfied for all $ i $ from $ 1 $ to $ n $ ).

Your task is to find out the maximum possible equal price $ B $ of all productts with the restriction that for all products the condiion $ |a_i - B| \le k $ should be satisfied (where $ a_i $ is the old price of the product and $ B $ is the same new price of all products) or report that it is impossible to find such price $ B $ .

Note that the chosen price $ B $ should be integer.

You should answer $ q $ independent queries.

## 说明/提示

In the first example query you can choose the price $ B=2 $ . It is easy to see that the difference between each old price and each new price $ B=2 $ is no more than $ 1 $ .

In the second example query you can choose the price $ B=6 $ and then all the differences between old and new price $ B=6 $ will be no more than $ 2 $ .

In the third example query you cannot choose any suitable price $ B $ . For any value $ B $ at least one condition out of two will be violated: $ |1-B| \le 2 $ , $ |6-B| \le 2 $ .

In the fourth example query all values $ B $ between $ 1 $ and $ 7 $ are valid. But the maximum is $ 7 $ , so it's the answer.

## 样例 #1

### 输入

```
4
5 1
1 1 2 3 1
4 2
6 4 8 5
2 2
1 6
3 5
5 2 5
```

### 输出

```
2
6
-1
7
```

# 题解

## 作者：AC_Dolphin (赞：3)

做法与上一个$solution$不同，复杂度更低（上一篇为$O(qnlogn)$，此篇为$O(qn)$）,有严谨证明~~且码风更好~~

考虑两个能够取一个数组的$max$、$min$值的函数：
```cpp
int findmax(int a[],int n){
    int maxn=-1;
    for(register int i(1);i<=n;++i) maxn=max(a[i],maxn);
    return maxn;
}
int findmin(int a[],int n){
    int minn=100000010;
    for(register int i(1);i<=n;++i) minn=min(a[i],minn);
    return minn;
}
```
然后我们知道如果$findmax(a,n)-findmin(a,n)>=k*2$，那么就算最大值变为最大值$-k$、最小值变为最小值$+k$，这两个值也不可能相同，所以此时要输出$-1$

这时候就需要知道$B$能取的最大值是多少。

如果$B$取$findmin(a,n)+k$，那么这个数列中所有数肯定满足$|a_i-B|<=k$，因为：
- 如果$a_i<=B$，那么因为$a_i>=findmin(a,n)$，所以$B-a_i<=B-findmin(a,n)=k$，即$|a_i-B|<=k$
- 如果$a_i>B$,那么因为$a_i<=findmax(a,n)$，且$findmax(a,n)-findmin(a,n)<k*2$，即$findmax(a,n)<k*2+findmin(a,n)$，所以$a_i<k*2+findmin(a,n)=B+k$，所以$|a_i-B|<k$

此时我们完成了$B$可以取$findmin(a,n)+k$的证明，证明$B$无法再取大于$findmin(a,n)+k$的值就很简单了，因为只要取到了一个这样的值，那么$B-findmin(a,n)>k$，说明$a$中的最小值$+=k$也到不了$B$

所以$B_{max}=findmin(a,n)+k$，证毕。

$Code:$
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define MAXN 100010
int a[MAXN],n,cnt,q,k;
inline int read(){
    int f(1),x(0);
    char ch(getchar());
    while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') {x=x*10+ch-'0';ch=getchar();}
    return f*x;
}
int findmax(int a[],int n){
    int maxn=-1;
    for(register int i(1);i<=n;++i) maxn=max(a[i],maxn);
    return maxn;
}
int findmin(int a[],int n){
    int minn=100000010;//ai<=10^8
    for(register int i(1);i<=n;++i) minn=min(a[i],minn);
    return minn;
}    
int main(){
    q=read();
    while(q--){
        n=read(),k=read();
        for(register int i(1);i<=n;++i) a[i]=read();
        if(findmax(a,n)-findmin(a,n)>k*2){
            cout<<-1<<endl;
            continue;
        }
        cout<<findmin(a,n)+k<<endl;
    }
    return 0;
}
```
（码字不易，管理员求通过）

---

## 作者：decoqwq (赞：2)

题意：给定$n$个数，每个数代表一个区间$[max(n-k,1),n+k]$，问这些区间的交集是不是空集，如果不是求出交集的最大值

本题最佳做法$O(\text{读入})$，直接取最右的左端点和最左的右端点比较即可

```
/**************************/
/*It is made by decoration*/
/*gzzkal   gzzkal   gzzkal*/
/*It is made by decoration*/
/**************************/
#include <bits/stdc++.h>
using namespace std;
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n,k;
		cin>>n>>k;
		int l=0,r=0x3f3f3f3f;
		for(int i=1;i<=n;i++)
		{
			int x;
			scanf("%d",&x);
			r=min(r,x+k);
			l=max(l,((x-k)>0?(x-k):1));
		}
		if(l<=r)
		{
			cout<<r<<endl;
		}
		else
		{
			cout<<-1<<endl;
		}
	}
} 
```

---

## 作者：__HHX__ (赞：1)

# 思路
算出当前数能取的最大值与最小值。

如果上一个数的最大值比当前最大值大，那能取的最大值为当前最大值。

因为当前最大值取不到上一个数的最大值。

最小值同理。

最后看 $[min, max]$ 合不合法.合法输出 $max$，非法输出 $-1$。
# 代码
```cpp
#include<iostream>
using namespace std;

int main() {
	int q;
	cin >> q;
	while (q--) {
		long long n, k, maxx = 1e16 + 3,minn = -1e8 - 3;
		cin >> n >> k;
		for (int i = 1, x; i <= n; i++) {
			cin >> x;
			maxx = min(maxx, k + x);
			minn = max(minn, -k + x);
		}
		cout << (maxx >= minn ? maxx : -1) << '\n';
	}
} 
```

---

## 作者：灵光一闪 (赞：1)

这题知道思路后还是蛮简单的

设m为价格变化的极限值（就是题目中的k

思路：用最大值减去最小值，如果这个差``2*m``之间，answer就是最小值+m

Why?

首先，要想有一个中间值，那么这个值肯定要满足这个条件：

### 最小值+m<=中间值&&中间值+m<=最大值

现在把中间值去掉，然后就是：

### 最小值+m+m<=最大值=最小值+2m<=最大值

然后难点就没了……

本人还不是中学党，可能上面有点问题，将就着看吧……

code：
```
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<cstdio>

using namespace std;
int a[105];
int n;
int k,m;
int main(){
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>k>>m;
        for(int j=0;j<k;j++){
            cin>>a[j];
        }
        sort(a,a+k);//排序一下
        if(a[k-1]-a[0]<=2*m){
            cout<<a[0]+m<<endl;//这个也可以写成cout<<a[k-1]-m<<endl;
        }
        else{
            puts("-1");//如果中间值取不到就是-1
        }
    }
    return 0;//结束了
}
```

---

## 作者：CQ_Bob (赞：0)

## 分析

使答案最大，我们必须使 $a$ 中的最小值最大，所以在有解的时候，答案就是 $\min_a+k$。但是，有一种无解的情况，需要我们判断：因为我们在有解时的答案是 $\min_a+k$，所以 $a$ 中的最大值一定能变成小于等于这个值的，而变成这个值需要的最少代价就是两者之间的绝对值，如果这个代价大于 $k$，则一定无解。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int maxx,minn,k,n,t;
const int N=1e6+10;
int a[N];
void init()
{
	cin>>n>>k;
	maxx=0,minn=1145141919810;
	for(int i=1;i<=n;i++) cin>>a[i];
}
int check()
{
	for(int i=1;i<=n;i++) maxx=max(maxx,a[i]),minn=min(minn,a[i]);
	if(abs(minn+k-maxx)>k) return -1;
	else return minn+k;
}
signed main()
{
	cin>>t;
	while(t--)
	{
		init();
		cout<<check()<<endl;
	}
	return 0;
}
```


---

## 作者：knsg251 (赞：0)

## 题目理解
给定一个数组，然后给出一个 $k$，数组中的任何一个数都可以加上 $(-k\sim k)$ 中的任何一个数，求数组能否不变成一个数，且求出这个数的**最大值**。
## 题目分析
首先找到序列中最大的数记为 $maxa_i$，找到序列中最小的数记为 $mina_i$。然后 $t1= \max(maxa_i-k)$ 和 $t2= \min(mina_i+k)$，如果 $t1<t2$ 那么无解，否则输出 $t2$ 即可。
## 代码实现
```cpp
#include <bits/stdc++.h>//万能头 
using namespace std;
int q,n,k,a,cnt;
int main(){
	cin>>q;
	while(q--){
		cin>>n>>k;
		int maxn = 0,minn = 999999999;//初始化 
		for(int i=1;i<=n;i++){
			scanf("%d",&a);//输入 
			minn = min(minn,a + k);//求出最小值 
			if(a > k){//判断两种情况 
				cnt = a - k;
			}else{
				cnt = 1;	
			}
			maxn = max(maxn,cnt);//求出最大值 
		}
		if(minn < maxn){//比较 
			printf("-1\n");//输出特殊情况 
			continue;//下一层 
		}
		printf("%d\n",minn);//正常输出 
	}
	return 0;//over 
} 

```

---

## 作者：Coffee_zzz (赞：0)

一道比较简单的思维题。

### 分析

对于序列中的每一个数，最多可以对它增加 $k$ 或减少 $k$。

因为需要使序列中的每一个数都相等，所以应使序列中较小的数变大，较大的数变小。

考虑这个序列中的最大值与最小值。

我们设这个序列中的最大值为 $ma$，最小值为 $mi$，那么 $mi$ 最多能变成 $mi+k$，$ma$ 最多能变成 $ma-k$。

当 $mi+k<ma-k$ 时，无法使 $mi$ 和 $ma$ 在变化后相等，输出 $-1$。

反之，$mi$ 和 $ma$ 能够在变化后相等，其余数也自然能够在变化后相等，此时最后的数字最大为 $mi+k$，输出 $mi+k$ 即可。

### 代码

```c++
#include <bits/stdc++.h>
using namespace std;
int main(){
	int t,n,i,a,k,ma,mi;
	cin>>t;
	while(t--){
		cin>>n>>k;ma=0,mi=INT_MAX;
		for(i=0;i<n;i++) cin>>a,ma=max(ma,a),mi=min(mi,a);
		if(mi+k<ma-k) cout<<"-1\n";
		else cout<<mi+k<<'\n';
	}
	return 0;
}
```

---

## 作者：Accepted_Error (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1183B)
## 题目大意

通过给出的数组求出最大值 $maxn$ 与最小值 $minn$，选择一个数加上或减去使两值相等且最大。

## 题目分析

根据题意，我们可以得出以下关系式：
$minn+v\le maxn-v$，也就是 $minn+2\times v\le maxn$。

并且题目中已知 $|v|\le k$

那么，如果 $maxn-minn>2\times k$，那么即使 $v$ 取最大值 $k$，$minn+v$ 和 $maxn-v$ 两个数的值也**不可能相等**，此时输出 -1。

然鹅，当 $maxn-minn\le 2\times k$ 时，$v$ 就**有值**使得 $minn+v=maxn-v$ 且我们可以得出此时修改后数的最大值就是 $minn+v$。

## AC Code
```cpp
#include<iostream>
#include<cstdio>
#include<stack>
#include<queue>
#include<vector>
#include<algorithm>
#include<utility>
#include<cmath>
#include<cstring>
#include<string>
#include<map>
#include<set>
#include<cstdlib>
#define ll long long
using namespace std;
const int N=110;
int a[N];
int q,n,k,maxn,minn;
int main()
{
	cin>>q;
	while(q--)//多组输入 
	{
		maxn=-1;
		minn=1e9;
		cin>>n>>k;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			maxn=max(maxn,a[i]);//取最大值 
			minn=min(minn,a[i]);//取最小值 
		}
		if(maxn-minn<=k*2) cout<<minn+k<<endl;//如果最大值与最小值的差在2*k范围内，输出minn+v 
		else cout<<"-1"<<endl;//范围外没有值，输出-1 
	}
	return 0;
}

```

---

## 作者：ylinxin2010 (赞：0)

## CF1183B题解
首先我们应该确定题意。

**题意：** 对于每个数，选择一个 $v$ 让它加上或减去 $v$ 使得最后的数相同并且最大，若不能输出负一。

注意有多组数据！

------------

然后我们应该确定这题的思路。

**本题思路：** 最大值与最小值判断。

1. 将最小值设为极大值，最大值设为极小值。

2. 枚举求最大值与最小值。

3. 判断是否最大值与最小值的差值小于等于 $v \times 2$ 就输出最小值加上 v 否则就输出负一。

4. 不要忘记换行与 return 0 哦。

接下来——上代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n, v, a[105], maxi=0, mini=1e9;
		cin>>n>>v;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			maxi=max(maxi,a[i]);
			mini=min(mini,a[i]);
		} 
		if(maxi-mini<=v*2)
			cout<<mini+v;
		else
			cout<<"-1";
		cout<<endl; 
	}
	return 0;
}
```

---

