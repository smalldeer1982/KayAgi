# Candy Box (easy version)

## 题目描述

This problem is actually a subproblem of problem G from the same contest.

There are $ n $ candies in a candy box. The type of the $ i $ -th candy is $ a_i $ ( $ 1 \le a_i \le n $ ).

You have to prepare a gift using some of these candies with the following restriction: the numbers of candies of each type presented in a gift should be all distinct (i. e. for example, a gift having two candies of type $ 1 $ and two candies of type $ 2 $ is bad).

It is possible that multiple types of candies are completely absent from the gift. It is also possible that not all candies of some types will be taken to a gift.

Your task is to find out the maximum possible size of the single gift you can prepare using the candies you have.

You have to answer $ q $ independent queries.

If you are Python programmer, consider using PyPy instead of Python when you submit your code.

## 说明/提示

In the first query, you can prepare a gift with two candies of type $ 8 $ and one candy of type $ 5 $ , totalling to $ 3 $ candies.

Note that this is not the only possible solution — taking two candies of type $ 4 $ and one candy of type $ 6 $ is also valid.

## 样例 #1

### 输入

```
3
8
1 4 8 4 5 6 3 8
16
2 1 3 3 4 3 4 4 1 3 2 2 2 4 1 1
9
2 2 4 4 4 7 7 7 7
```

### 输出

```
3
10
9
```

# 题解

## 作者：luo_shen (赞：3)

## 题意简述
有 $t$ 组数据，在 $n$ 个数中选出 $num$ 个数，使得每个数 $i$ 出现的次数 $num_i$ 均不相同。
## 思路说明
因为题目要求我们求出每个数出现的次数 $num_i$ 的和，所以我们可以用桶排将总次数先统计出来再进行从大到小的排序，算出每个数可以选出的次数并同时计算出结果。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,b[201000],x;
bool cmp(int x,int y){		   //排序函数，使得sort排出的数是从大到小的 
	return x>y;
}
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>x;
			b[x]++;         //桶排记录 
		}
		sort(b+1,b+n+1,cmp);   //按数量从大到小排序 
		int ans=0,k=2147483647; //初始化，k取极大值 
		for(int i=1;i<=n;i++){
			k--;		//已经选过的数量要去掉 
			k=min(k,b[i]);  /*在要选的数量和现在的这种糖果的数量中取最少的数量，并记录。
					  因为是从大到小排序，所以如果这种糖果都满足不了k，那么下一种
					  糖果依然满足不了k,所以直接用min取到最小值 
								*/ 
			ans=ans+k;
			if(!k){	        //如果能取的数量已经取完了，那么直接结束循环。如果不结束，那么k会变成负数导致结果变小 
				break;
			}
		}
		cout<<ans<<endl;
		for(int i=1;i<=n;i++){  //将桶排b数组清零，这题不能用memset清零，#27会超时 
			b[i]=0;
		} 
	}
	return 0;
} 
```


---

## 作者：__HHX__ (赞：2)

# 思路
先拿桶记录一遍每个糖果出现了多少次。

然后再拿一个桶记录正好能取当前数量的糖果一共有多少种。

从大向小枚举，若当前有多的种数，就把当前糖果种数 $-1$ 加进当前糖果数 $-1$ 的桶里。

记录答案就变成了：
```cpp
for(int i = n; i >= 1; i--) {
	if(cnt2[i]) {
		ans += i;
		cnt2[i - 1] += cnt2[i] - 1;
	}
}
```

时间复杂度 $O(n)$ 可比排序 $O(n \log n)$ 还快。
# 代码
```cpp
#include<iostream>
using namespace std;

const int MaxN = 2e5 + 3;

int cnt[MaxN], cnt2[MaxN];

int main() {
	int q;
	cin >> q;
	while (q--) {
		int n, ans = 0;
		cin >> n;
		fill(cnt, cnt + n + 1, 0);
		fill(cnt2, cnt2 + n + 1, 0);
		for(int i = 1, x; i <= n; i++) {
			cin >> x;
			cnt[x]++;
		}
		for(int i = 1; i <= n; i++) {
			cnt2[cnt[i]]++;
		}
		for(int i = n; i >= 1; i--) {
			if(cnt2[i]) {
				ans += i;
				cnt2[i - 1] += cnt2[i] - 1;
			}
		}
		cout << ans <<'\n';
	}
}
```

---

## 作者：___Yang__ (赞：2)

## 题目大意
本题共有 $q$ 组数据。你有 $n$ 块糖果，第 $i$ 块糖果的种类是 $a_i$ 你选出来的糖果，需要满足**任意两种糖果的数量都不能相等**，求你最多能够选出来多少块糖果。
## 思路
本题主要算法是贪心，用一个数组保存每种糖果的数量，然后从大到小排序，在每次循坏中能取多少糖果就取多少，保证每次都是最优解，都加到 $ans$ 中，输出即可。
## 代码
```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
int q,n,a[200010],b;
bool cmp(int c,int d){//cmp函数，不解释
	return c>d;
}
int main(){
	cin>>q;
	while(q--){
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>b;
			a[b]++;//使b类的糖果加1 
		}
		sort(a+1,a+n+1,cmp);
		int ans=0,p=2147483647;//p取int最大值，方便之后取最小值
		for(int i=1;i<=n;i++){
			p--; 
			p=min(p,a[i]);//能取多少糖果就取多少，保证最优解
			ans+=p;
			if(p==0)break;//如果 p=0 ，说明糖果取完了，不能再取了，要退出循环 
		}
		cout<<ans<<"\n";
		for(int i=1;i<=n;i++)a[i]=0;//不能用 memset(a,0,sizeof(a)) ，经测试会导致 #27 超时
	}
	return 0;//华丽结束
}
``` 

---

## 作者：thomas_zjl (赞：1)

数据范围中我们知道糖果的种类的数字是小于糖果的数量的。

所以我们可以使用一个桶来存每种糖果的数量。

然后在排序，从大都小取糖果即可。

接下来的细节在代码里。

```cpp
#include<bits/stdc++.h>
using namespace std;
int sum[200005];//桶
int main(){
    int q;
    scanf("%d",&q);
    while(q--){
        int n;
        int a;
        scanf("%d",&n);
        int ans=0;
        for(int i=1;i<=n;i++){
            scanf("%d",&a);
            sum[a]++;
        }
        sort(sum+1,sum+1+n);
        int jl=2147483637;//这里代表了要取糖果的数量。
        for(int i=n;i>=1;i--){
        	jl--;//一开始要-1，是因为每种糖果是数量不能重复。
        	jl=min(jl,sum[i]);//取二者中最小的。
        	ans+=jl;//然后把二者较小的给加进答案。
			if(jl==0)//如果这个数是0,就没有在循环下去的意义了，直接跳出循环。
        		break;
		}
        printf("%d\n",ans);
        for(int i=1;i<=n;i++)
        	sum[i]=0;
       //清0（一开始用memset超时了）
    }
}
```


---

## 作者：2011FYCCCTA (赞：0)

# [原题](https://www.luogu.com.cn/problem/CF1183D)
一遍 AC~

---
### 分析

此题可以用贪心做。

很明显，为了让选出来的糖果数尽量大，最优策略就是尽量拿包含糖果最多的种类，因此我们可以从大到小排序此种类所包含的糖果数，记为 $c$ 数组，每一次加上 $c_i$（表示包含糖果数第 $i$ 大的种类）。

但如上做法无法处理这种情况：$c_i$ 与 $c_{i + 1}$ 一样。为解决这个问题，我们可以定义一个**全局**变量记录当前加上的糖果数量，记为 $m$，仅当 $m > c_i$ 时才将 $m$ 设为 $c_i$，否则 $m$ 需要减 $1$（最多只能选择 $m - 1$ 颗），当进行完如上操作后，若 $m < 0$，需要退出循环，否则将结果加上 $m$。

---
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int q , n , a[200005] , ans;
vector<int> v;

bool cmp(int a , int b)
{
    return a > b;
}

int main()
{
    cin >> q;
    while (q--)
    {
        cin >> n;
        ans = 0; v.clear();
        for (int i = 1 ; i <= n ; i++) cin >> a[i];
        
        sort(a + 1 , a + n + 1);
        for (int i = 1 ; i <= n ; i++)
        {
            if (i == 1 || a[i] != a[i - 1]) v.push_back(1);
            else ++v[v.size() - 1];
        }
        //在排序时我们并不需要知道每颗糖果所对应的种类是什么
        sort(v.begin() , v.end() , cmp);

        int mina = 2e5 + 5;
        for (int i = 0 ; i < v.size() ; i++)
        {
            if (v[i] >= mina) --mina;
            else mina = v[i];
            if (mina < 0) break;
            ans += mina;
        }
        cout << ans << endl;
    }
    return 0; 
}
```
[评测记录，突然发现我的算法好慢啊](https://www.luogu.com.cn/record/113501987)

---

## 作者：Neilchenyinuo (赞：0)

## Solution 

1. 拿桶记录每个糖果出现的次数。

2. 再拿一个桶，统计正好能取当前数量的糖果一共有多少种。

3. 从大到小枚举，如果当前可以选，就将当前种数减一，加入前一种糖果中并统计块数。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int cnt1[N],cnt2[N],q,n,x;
signed main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0); 
	cin>>q;
	while(q--)
	{
		int ans=0;
		cin>>n;
		for(int i=1;i<=n;i++)
			cnt1[i]=cnt2[i]=0;
		for(int i=1;i<=n;i++)
		{
			cin>>x;
			cnt1[x]++;
		}
		for(int i=1;i<=n;i++)
			cnt2[cnt1[i]]++;
		for(int i=n;i>=1;i--)
			if(cnt2[i])
			{
				ans+=i;
				cnt2[i-1]+=cnt2[i]-1;
			}
		cout<<ans<<"\n";
	}
	return 0;
} 
```

---

## 作者：Abeeel51 (赞：0)

#### 题意
你有 $n$ 块糖果，第 $i$ 块糖果的种类是 $a_i$。你想选出来若干块糖果送给别人。你选出来的糖果需要满足任意两种糖果的数量都不能相等。求你最多能够选出来多少块糖果。你需要回答 $q$ 组询问。
#### 题解
记录每种糖果的数量，然后使用快排函数，要写一个比较函数，因为是越大的越先算，小的后算，排序用一个桶来存储每一个量，计算糖果数量的最小值，然后输出。

因为有多组数据，还比较大，我选择不写 $\texttt{memset}$ 函数。但是非要写的话不写 $\texttt{sizeof}$ 也可以过，因为 $\texttt{sizeof}$ 很耗时间。

#### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[200005];
bool comp(int x,int y){return x>y;}
int main(int argc, const char * argv[]) {
    // insert code here...
    int Q;
    scanf("%d",&Q);
    while(Q--){//不写memset因为多组数据会超时
        int n;
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            int t;
            scanf("%d",&t);
            a[t]++;
        }
        sort(a+1,a+n+1,comp);
        int Out=0;
        int MIN=0x7f7f7f7f;//糖果数量极大值
        for(int i=1;i<=n;i++){
            MIN--;MIN=min(MIN,a[i]);Out+=MIN;if(MIN==0) break;
        }
        printf("%d\n",Out);
        for(int i=1;i<=n;i++) a[i]=0;
    }
    return 0;
}
```


---

## 作者：int32 (赞：0)

## $\textsf{Solution}$

先用 $\verb!map!$ 把所有种类先统计一遍，然后**从大到小**排序，依次贪心取出即可。

具体实现可以不用 $\verb!map!$，细节在代码中。

时间复杂度为 $\mathcal{O}(qn\log n)$

## $\textsf{Code}$


```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
int n;
long long v;
int c[(int)(2e5+10)];//map
signed main(){
	cin>>T;
	while(T--){
		v=0;//注意多测清零
		cin>>n;
		for(int i=1,a;i<=n;i++) cin>>a,++c[a];//统计个数
		stable_sort(c+1,c+n+1);//排序
		int y=1e9;//极大值
		for(int i=n;i;i--){//升序排序，降序遍历
			--y;//注意！不能重复！需要减一！
			y=min(y,c[i]);
			if(y==0) break;//取完了
			v+=y;
		}
		cout<<v<<'\n';
		for(int i=1;i<=n;i++) c[i]=0;//手动清零，memset 超时 #27
	}
	return 0;
}
```

---

## 作者：wucstdio (赞：0)

由于种类相同的糖果之间是没有区分的，所以我们可以很容易地想到先记录$cnt[i]$表示种类为$i$的糖果数量。

接下来我们将$cnt$数组排序，然后从高到低贪心选择即可。

时间复杂度$O(n\log n)$

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#define ll long long
using namespace std;
int t,n,cnt[200005];
ll ans;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			int x;
			scanf("%d",&x);
			cnt[x]++;
		}
		sort(cnt+1,cnt+n+1);
		int now=1000000000;
		ans=0;
		for(int i=n;i>=1;i--)
		{
			now--;
			now=min(now,cnt[i]);
			if(now==0)break;
			ans+=now;
		}
		printf("%I64d\n",ans);
		for(int i=1;i<=n;i++)cnt[i]=0;
	}
	return 0;
}
```

---

## 作者：decoqwq (赞：0)

按照题意模拟即可，用桶存每种类型的出现次数，然后从大到小取当前可以取得的数目，贪心即可
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
		map<int,int> mp,mpp;
		vector<int> vc;
		int n;
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			int x;
			scanf("%d",&x);
			mp[x]++;
			if(mp[x]==1)
			{
				vc.push_back(x);
			}
		}
		int ans=0;
		for(int i=0;i<vc.size();i++)
		{
			if(!mpp[mp[vc[i]]])
			{
				ans+=mp[vc[i]];
				mpp[mp[vc[i]]]=1;
			}
			else
			{
				for(int j=mp[vc[i]]-1;j>=1;j--)
				{
					if(!mpp[j])
					{
						ans+=j;
						mpp[j]=1;
						break;
					}
				}
			}
		}
		cout<<ans<<endl;
	}
} 
  ```

---

