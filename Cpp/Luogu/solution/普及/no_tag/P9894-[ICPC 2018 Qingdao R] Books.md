# [ICPC 2018 Qingdao R] Books

## 题目描述

DreamGrid 昨天去了书店。书店里总共有 $n$ 本书。因为 DreamGrid 非常富有，他按照以下策略购买书籍：

- 按顺序从第 1 本书到第 $n$ 本书检查这 $n$ 本书。
- 对于当前检查的每本书，如果 DreamGrid 有足够的钱（不少于书的价格），他就会买下这本书，他的钱会减少书的价格。
- 如果他的钱少于当前检查的书的价格，他将跳过这本书。

BaoBao 对 DreamGrid 的财富感到好奇。你需要告诉他 DreamGrid 在买书前可能带的最大金额，这个金额是一个非负整数。他所知道的只有 $n$ 本书的价格和 DreamGrid 总共买了多少本书，用 $m$ 表示。

## 说明/提示

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
4
4 2
1 2 4 8
4 0
100 99 98 97
2 2
10000 10000
5 3
0 0 0 0 1```

### 输出

```
6
96
Richman
Impossible```

# 题解

## 作者：封禁用户 (赞：2)

# 思路：
分类讨论，分为 $3$ 种情况：

1. 免费的书的数量大于 $m$ 这是不可能的，因为免费书肯定买的起，即 Impossible。
2. $n=m$ 即 DreamGrid 买了所有书，这样他手上的钱是任意的，即 Richman 。
3. 其它情况。对于其他情况，则需自己计算。依题意，免费书必须买，所以先用 $m-$ 免费书本数，然后再按顺序买完 （$m-$ 免费书本数），然后他剩下的钱就是剩下的书中最便宜的价格为 $-1$ 的书，这样她刚好买不起。





---

## 作者：lidagua1004 (赞：2)

## 思路：
$0$ 元的物品先买，买完后若 $m<0$ 或 $m<n$ 则不可能，输出`Impossible`。若 $m=n$ 则输出`Richman`。否则，输出前 $m$ 本书的价格之和加上剩下的中最小的价格减一。可以证明这样最优。
## 代码
```cpp
#include<bits/stdc++.h> 
#define int long long//要开longlong
using namespace std;
int a[100500];
void f(){//多组样例
	int n,m,ans=0,d=INT_MAX;
    cin>>n>>m;
	for(int i=1;i<=n;i++){
	    cin>>a[i];
	    if(!a[i]) i--,n--,m--;//若0则不计入
	}
	if(m>n||m<0){//判Impossible
		cout<<"Impossible\n";
		return;
	}
	if(n==m){//判Richman
    	cout<<"Richman\n";
   		return;
   }
	for(int i=1;i<=m;i++) ans+=a[i];//加和
	for(int i=m+1;i<=n;i++) d=min(d,a[i]);//求最小
	cout<<ans+d-1<<"\n";
}
signed main(){
	int n;cin>>n;
	while(n--) f();
	return 0;
}
```

---

## 作者：Yuki_Ever (赞：1)

## 题目大意
给出 $n$ 本书和每本书的价格 $a_i$，以及要买的书数量 $m$。对于每本书，按顺序依次判断当前书的价格与剩余钱数，如果足够买就一定会买，否则跳过这本书。求在买 $m$ 本书的情况下最开始至多应该有多少钱。
## solve
考虑贪心。可以较为容易的得出一下结论：

买且仅买前 $m$ 本书，将总和累计，并加上 $a_{m+1}$，最后再将钱数 $-1$。 

可以如下证明此结论：

如果在前 $m$ 本书中少买任何一本，对于总钱数来说，能在之后买到的书价格不会超过前 $m$ 本书中不买的书。所以总价格一定不会更大。证毕。

于是算法大致完成。但一定要考虑到价格为 $0$ 的书的情况。在计算前 $m$ 本书的时候，定义双指针，如果 $m$ 本之后有价格为 $0$ 的书，则必须买，累计一下即可。特别地，价格为 $0$ 的书数比 $m$ 大则输出 Richman；$m$ 比 $n$ 大就输出 Impossible。



具体实现详见代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int t;
int f[1000009];
signed main() {
	scanf("%lld",&t);
	while(t--){
		int n,m;
		scanf("%lld%lld",&n,&m);
		int f0=0;	//0
		for(int i=1;i<=n;i++){
			scanf("%lld",&f[i]);
			if(f[i]==0)f0++;
		}
		if(n==m){cout<<"Richman"<<"\n";continue;}
		if(m<f0){cout<<"Impossible"<<"\n";continue;}
		int book=0;	//累计价格
		int minn=4e18;  //打擂台，定义为极大值
		m-=f0;	//处理0
		for(int i=1,j=1;i<=n;i++){
        			//双指针
			if(f[i]){
				if(j<=m) book+=f[i];
				else minn=min(minn,f[i]-1);
				j++;
			}
		}
		book+=minn;
		cout<<book<<"\n";
	}
	return 0;
}
```


---

## 作者：Lyw_and_Segment_Tree (赞：1)

[原题传送门](https://www.luogu.com.cn/problem/P9894)  
## 题意简述
> 首先输入一个整数 $T$，表示数据组数。其中每组数据的内容如下：  
> 首先输入两个整数 $n$ 和 $m$，分别表示有 $n$ 本书和要买 $m$ 本书。然后输入 $n$ 个整数 $a_i$，第 $i$ 个整数 $a_i$ 表示第 $i$ 本书的价格。  
> 试求出一个答案 $ans$ 它表示买下前 $m$ 本书所需的最少钱数。但是，如果能把所有书买下，输出 `Richman`，而如果不能 **恰好** 买下 $m$ 本输出 `Impossible`。否则输出 $ans$。

## 开始解题！
先看题面，关注到会有三种输出，所以决定分类讨论。  
接下来看样例。 
输入：
```
...
4 2
1 2 4 8
...
```  
输出：
```
6
...
```  
然后继续看题目。关注到输出的是最大价格，也就是说要先将前 $m$ 本书买下，然后再加上一个值使得这个最大价格小于 $(\sum\limits_{i=1}^{m} a_i) + \min(a_m+1,a_m+2,...,a_n)$，也就是加上 $\min(a_{m+1},a_{m+2},...,a_n) - 1$。这也就是一般情况。    
然后判断另一种情况，如果 $n = m$，根据题意，应输出 `Richman`。  
最后再判断一种情况，如果 $a_i = 0$，那么应该将 $n$ 和 $m$ 的值减去一，并重新输入 $a_i$。当 $m < 0$ 或 $m > n$ 的情况下输出 `Impossible`，因为这些情况都不合法。比如只有 3 本书，你却想买 4 本书，这肯定是不行的。再比如说样例中出现的 `0 0 0 0 1` 的情况，此时买 3 本书的最优解和买 4 本书的最优解相同，不符合题目中 **恰好** 买到 $m$ 本的定义。故也是不合法情况。  
综合上述结论，可得代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,T;
long long a[100005];
long long sum(int first,int last){
    long long ans=0;
    for(int i=first;i<last;i++) ans+=a[i];
    return ans;
}
long long min(int first,int last){
    long long Min=INT_MAX;
    for(int i=first;i<last;i++) Min>a[i]?Min=a[i]:Min=Min;
    return Min;
}
int main(){
    cin>>T;
    for(int i=1;i<=T;i++){
        cin>>n>>m;
        for(int j=0;j<n;j++){
            cin>>a[j];
            if(!a[j]){
                --j,--n,--m;
            }
        }
        if(n==m){
            cout<<"Richman"<<endl;
        }else if(m<0||m>n){
            cout<<"Impossible"<<endl;
        }else{
            long long ans=sum(0,m)+min(m,n)-1;
            cout<<ans<<endl;
        }
    }
}
```
[AC记录](https://www.luogu.com.cn/record/137577691)

---

## 作者：abc1856896 (赞：1)

# 题目大意
输入书的总本数和已经购买的书的本数以及每本书的价格。

如果他有足够的钱（不低于书价），他会买这本书，他的钱会按书的价格减少。

如果他的钱低于现在检查的书的价格，他会跳过那本书。

求输入书的总本数和已经购买的书的本数以及每本书的价格

# 大体思路
首先贪心得不到正确的结果，因为有 $0$，所以要换个想法。

我们肯定要将价格为 $0$ 的书先买走，然后从前往后买。买够 $m$ 本书之后 $(sum)$，在剩下的书中选择一本最便宜的书买不起 (也就是 $\min-1$)，最后总的钱数 $sum+$$\min-1$ 就是答案。记得要特判！

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[1000005];
long long n,m,t;
int main(){
    cin>>t;
    while(t--) {
        scanf("%d%d",&n,&m);
        long long k=0,i,minn=INT_MAX;
        for(i=1;i<=n;i++) {
			cin>>a[i];
            if(a[i]==0) k++;
            minn=min(minn,a[i]);
        }
        if(k>m){
            cout<<"Impossible"<<endl;
            continue;
        }
        else if(n==m) {
            cout<<"Richman"<<endl;
            continue;
        }
        else if(m==0) {
            cout<<minn-1<<endl;
            continue;
        }//特判
        long long sum=0;
        int p;
        for(i=1;i<=n;i++) {
            if(k==m) {
                p=i;
                break;
            }
            if(a[i]!=0) {
                sum+=a[i];
                k++;
            }
        }//买书检查
        minn=INT_MAX;
        for(int i=p;i<=n;i++) {
            if(a[i]!=0)  minn=min(a[i],minn);
        }
        cout<<sum+minn-1<<endl;
    }
    return 0;
}
```


---

## 作者：Ahws_rwhy (赞：1)

其实本题是一道贪心题（签到题）。

思路：

其实看到这题我们应该可以联想到这 $2$ 种特殊情况：

- 如果把所有书都买了，输出 ```Richman```。
- 价格是 $0$ 元的书一定会购买，在此我们设有 $x$ 本这样的书，当 $x>m$ 时，一定不可能买到 $m$ 本，输出 ```Impossible```。

- 当 $m>x$ 时，首先肯定会挑选 $x$ 个价格为 $0$ 的书籍，然后从前往后在价格不为 $0$ 的书籍里面贪心挑选 $m-x$ 本书籍。

代码：

```
	while(t--) {
			sum=0;
			cin>>n>>m;
			for(int i=1; i<=n; i++) {
				cin>>a[i];
				if(a[i]==0) {
					sum++;
				}
			}
			if(n==m) cout<<"Richman\n";
			else if(sum>m) cout<<"Impossible\n";
			else {
				m-=sum;
				minn=1e9;
				p=0;
				ans=0;
				while(m!=0) {
					if(a[p]) {
						ans+=a[p];
						m--;
						p++;//贪心
					} 
					else {
						p++;
					}
				}
				for(int i=p; i<=n; i++)
					if(a[i]!=0)
						minn=min(minn,a[i]);
				ans+=minn-1;
				cout<<ans<<endl;
			}
```

---

## 作者：juruo_zhanshen (赞：1)

# 前言 
~~比赛为提交原因：看不懂英文题面，没有难度评级。总之就是不敢看~~

比赛后，我看了一下题目，发现有两道黄题，现在来发一下题解。

---
现在进入正题。

定义数组 `cost`。

根据样例可以得知，一共有三种形式的输出：钱数、`Richman`、`Impossible`。

首先考虑两个特殊的输出：`Richman` 和 `Impossible`。
1. 不难发现，当且仅当 $n = m$ 时，输出 `Richman` 。
2. 不难发现，当且仅当 `cost` 中 $0$ 的个数 $>m$ 时，输出 `Impossible`。

接下来考虑输出钱数。

1. 观察样例第三行，可以发现，他最多的钱数就是：前 $m$ 本书的价格之和 $+$ 剩下书本最价钱 $-1$。
2. 现在加上价格为 $0$ 的书。如果一本书的价格为 $0$，那么它可以直接拿走。定义变量 `zero` 表示 $0$ 的个数。所以结果是：前 $m-zero$ 本书的价格之和 $+$ 剩下书本最价钱 $-1$。

至此，问题完美解决。

# AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;

int main ( int argc, char *argv[] )
{
    int t, n, m;
    cin >> t;
    while (t--){
        cin >> n >> m;
        int zero = 0;
        int cost[n + 5];
        for (int i = 0; i < n; i++){
            cin >> cost[i];
            if (cost[i] == 0) zero++;
        }
        if (zero > m) cout << "Impossible" << endl;
        else if (n == m) cout << "Richman" << endl;
        else{
            int i;
            long long ans = 0; // 不开 long long 见祖宗
            m -= zero;
            for (i = 0; i < n; i++){
                if (m == 0) break;
                if (cost[i]){
                    ans += cost[i];
                    m--;
                }
            }
            int tmp = INT_MAX; // int 型可以容纳的最大的数
            for (int j = i; j < n; j++) // 遍历剩下书本的钱数
                if (cost[j])
                    tmp = min(tmp, cost[j]);
            cout << ans + tmp - 1 << endl;
        }
    }
    return 0;
}               /* ----------  end of function main  ---------- */
```

希望这篇题解能给你带来帮助。点个赞吧。

---

## 作者：sfqxx1 (赞：0)

[题目传送门。](https://www.luogu.com.cn/problem/P9894)

## 思路

这题可以分成以下几种情况考虑：

1. 若 $m=n$，输出 `richman`。

2. 若价格为 $0$ 的书数量大于 $m$，输出 `impossible` 即可。

3. 正常情况。我们先统计 $0$ 的个数 $k$，因为 $0$ 的时候是可以直接拿走的，统计完以后我们用 $m-k$，得到剩下要买书的数量，从第一本遍历过来就可以。若 $m-k$ 等于 $0$，则说明他要买 $m$ 本书，书架里有 $m$ 本免费的书，这时候直接统计其他不为 $0$ 的书的最小值 $-1$ 即可。最后输出答案。

## 代码
```
T = int(input())
for _ in range(T):
    n, m = map(int,input().split())
    a = list(map(int,input().split()))
    k = 0
    mi = pow(10,9)+ 5
    for i in range(n):
        if a[i] == 0:
            k += 1
        if mi > a[i]:
            mi = a[i]
    if k > m:
        print("Impossible")
        continue
    if n == m:
        print("Richman")
        continue
    if m == 0:
        print(mi - 1)
        continue

    s = 0
    for i in range(n):
        if k == m:
            break
        if a[i] != 0:
            s += a[i]
            k += 1
    mi = pow(10,9) + 5
    for j in range(i, n):
        if a[j] != 0:
            mi = min(a[j], mi)
    print(s + mi - 1)
```

---

## 作者：wwd_ewen (赞：0)

本题就是一个简单的贪心题。
### 思路
输入书的价格，如果书的价格为 $0$ 元就忽略不管。如果 $n=m$ 能全买就输出 `Richman` 结束；如果 $0$ 元书的数量超过了 $m$ 则输出 `Impossible` 结束。

如果都不符合，输出前 $m$ 本书的价格和加上剩下中最小的价格减 $1$ 就可以了！
```cpp
//洛谷P9894 
#include <stdio.h>
#include <string.h>
typedef long long ll; //要开long long 
ll a[100005];
ll min(ll a,ll b) {return a<b?a:b;}
int main()
{
	ll t; scanf("%lld",&t);
	while(t--)
	{
		memset(a,0,sizeof(a)); //清空数组 
		ll n,m; scanf("%lld %lld",&n,&m);
		ll sum=0,xiao=2147483647,mm=m; //sum累加0的个数，xiao以后用于剩下书中最小的价格再减1，mm用于判断0的个数 
		for(ll i=1;i<=n;i++) //0元的物品先购买
		{
			scanf("%lld",&a[i]);
			if(a[i]==0) i--,n--,m--,sum++; //要计算0的个数 
		}
		if(n==m) printf("Richman\n"); //能全买直接输出 
		else if(sum>mm) printf("Impossible\n"); //一定不能买到m本书 
		else
		{
			sum=0; //sum后面用作答案输出 
			for(ll i=1;i<=m;i++) sum+=a[i]; //累加m本书 
			for(ll i=m+1;i<=n;i++) xiao=min(xiao,a[i]); //求剩下书中最小的价格 
			sum=sum+xiao-1; //前m本书的价格加上剩下书中最小的价格 
			printf("%lld\n",sum);
		}
	}
	return 0;
}
```

---

## 作者：niuzh (赞：0)

## 思路

本题可以说是模拟题。

设序列中序列中的 $0$ 的数量为 $x$，
把这题分成 $3$ 部分来做：

1. 如果 $n=m$，要买 $n$ 本书，在输入后直接输出 `Richman`。

1. 如果 $x>m$，$0$ 元的书一定会被购买，输出 `Impossible`。

1. 如果 $x \le m$，$x$ 个 $0$ 元的书一定会购买，所以只用从头到尾买 $m-x$ 本价格不为 $0$ 元的书。题目又要求最大，要再加上最后一本后面最便宜的不为 $0$ 书的价钱减 $1$。

## 代码
```
/*
 * @FilePath: P9894 Books.cpp
 * @Author: niu-zh
 */
#include<bits/stdc++.h>
#define ll long long             // 一定开 long long
using namespace std;
const int N=1e5+10;
int a[N];
int main()
{
	int t;
	cin>>t;
	while (t--)
	{
		ll n,m,x=0;
		cin>>n>>m;
		for (int i=1; i<=n; i++)
		{
			cin>>a[i];
			if (a[i]==0)// 记录 0 的个数
			{
				x++;
			}
		}
		if (n==m)// n==m 的情况
		{
			cout<<"Richman\n";
			continue;
		}
		if (x>m)// 0 的个数比 m 多的情况
		{
			cout<<"Impossible\n";
			continue;
		}
		ll minn=1e18,u=1,ans=0;
		m-=x;
		while (m!=0)//购买 m-x本书
		{
			if (a[u])
			{
				ans+=a[u];//只取最前面的没买的书，如果不买这本买后面更贵或价格相等的书，则当前书一定被买。买后面跟便宜的书则与题目中要求总钱数最大矛盾
				m--;
			}
			u++;
		}
		for (int i=u; i<=n; i++)//总钱数最大化
		{
			if (a[i])
			{
				minn=min(minn,a[i]);
			}
		}
		ans+=minn-1;
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：zheng_zx (赞：0)

## P9894 [ICPC2018 Qingdao R] Books

[题目传送门](https://www.luogu.com.cn/problem/P9894)

### 分析

---

思维题。先将 $0$ 元的物品全部买下，如果剩下的 $m<0$ 或 $m>n$ 则输出 ```Impossible```，$m=n$ 则输出 ```Richman```，其他情况的最优解释将前 $m$ 本全部买下，再加上后面的最小值 $-1$ 即可。

代码中会出现 ```accumulate``` 函数和 ```min_element``` 函数。不懂的点这里：

- [```accumulate``` 函数的用法](https://blog.csdn.net/qq_40803710/article/details/80273811)

- [```min_element``` 函数的用法](https://zhuanlan.zhihu.com/p/435905136)

### Code：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, T, a[100007];

int main(){
    cin >> T;
    while(T--){
        cin >> n >> m;
        for(int i = 0; i < n; ++i) {
            cin >> a[i];
            if(!a[i])
                --i, --n, --m;
        }
        if(m < 0 || m > n)
            puts("Impossible");
        else if(m == n)
            puts("Richman");
        else{
            long long ans = accumulate(a, a + m, 0ll) + *min_element(a + m, a + n) - 1;        
            cout << ans << endl;
        }
    }
    return 0;
}
```

---

