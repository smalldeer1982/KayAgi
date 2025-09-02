# Choosing Cubes

## 题目描述

Dmitry 有 $n$ 个立方体，从左到右编号为 $1$ 到 $n$。编号为 $f$ 的立方体是他最喜欢的。

Dmitry 把所有立方体扔在桌子上，第 $i$ 个立方体显示的数值为 $a_i$（$1 \le a_i \le 100$）。之后，他将立方体按照数值从大到小的顺序重新排列。如果有两个立方体显示相同的数值，它们可以以任意顺序排列。

排序后，Dmitry 移除了前 $k$ 个立方体。然后他想知道，他最喜欢的立方体是否被移除了（注意排序后它的位置可能发生了变化）。

例如，如果 $n=5$，$f=2$，$a = [4, \color{green}3, 3, 2, 3]$（最喜欢的立方体用绿色标出），$k = 2$，可能发生以下情况：

- 排序后 $a=[4, \color{green}3, 3, 3, 2]$，由于最喜欢的立方体排在第二位，它会被移除。
- 排序后 $a=[4, 3, \color{green}3, 3, 2]$，由于最喜欢的立方体排在第三位，它不会被移除。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
12
5 2 2
4 3 3 2 3
5 5 3
4 2 1 3 5
5 5 2
5 2 4 1 3
5 5 5
1 2 5 4 3
5 5 4
3 1 2 4 5
5 5 5
4 3 2 1 5
6 5 3
1 2 3 1 2 3
10 1 1
1 1 1 1 1 1 1 1 1 1
1 1 1
42
5 2 3
2 2 1 1 2
2 1 1
2 1
5 3 1
3 3 2 3 2```

### 输出

```
MAYBE
YES
NO
YES
YES
YES
MAYBE
MAYBE
YES
YES
YES
NO```

# 题解

## 作者：NTT__int128 (赞：8)

# CF1980B Choosing Cubes题解
令 $tmp=a_f$。

首先，对于序列 $a$ 排序。会有以下几种情况：

- 如果所有值为 $tmp$ 的方块都在第 $k$ 个之后，则答案为 $\texttt{NO}$。

- 如果所有值为 $tmp$ 的方块都在第 $k$ 个之前或在第 $k$ 个，则答案为 $\texttt{YES}$。

- 其余情况答案为 $\texttt{MAYBE}$。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std ;
const int N = 1e2 + 5 ;
int t , n , f , k , a[N] ;
bool cmp(int x , int y)
{
	return x > y ;
}
void work()
{
	cin >> n >> f >> k ;
	for(int i = 1 ; i <= n ; i++)	cin >> a[i] ;
	int tmp = a[f] ;
	sort(a + 1 , a + n + 1 , cmp) ;
	if(a[k] > tmp)	cout << "NO\n" ;//所有值为f的方块都在第k个之后
	else if(a[k] < tmp || k == n || (a[k] == tmp && a[k + 1] < tmp))	cout <<"YES\n" ;//所有值为f的方块都在第k个之前或在第k个
	else	cout << "MAYBE\n" ;
	return ;
}
int main()
{
	ios::sync_with_stdio(0) ;
	cin.tie(0) ;
	cout.tie(0) ;
	cin >> t ;
	while(t--)	work() ;
	return 0 ;
}
```

---

## 作者：ikunTLE (赞：6)

[题目传送门](https://www.luogu.com.cn/problem/CF1980B)

### 思路

对于这个问题，我们需要考虑两个因素：喜欢的立方体和移除的立方体数量。

首先，要找出最喜欢的立方体在排序后的位置，并比较它的位置和移除的立方体数量，以确定最终结果。

1. 找到最喜欢的立方体在排序后的位置：

- 对立方体的值进行非递增排序。
- 找到最喜欢的立方体的值在排序后的位置。

2. 比较最喜欢的立方体位置（下面简称为 $pos$）和移除的立方体数量（下面简称为 $num$）：

- 如果 $pos \le num$，那么它可能会被移除。（`YES`）
- 如果 $pos > num$，那么它不会被移除。（`NO`）
- 如果 $pos$ 在 $num$ 之后，无法确定是否被移除。（`MAYBE`）

---

## 作者：toolong114514 (赞：2)

# CF1980B Choosing Cubes 题解
## 题面翻译
Dimtry 有 $n$ 个立方体，第 $i$ 个立方体的价值为 $a_i$，他最喜欢第 $f$ 个立方体。

接下来 Dimtry 会把立方体按 $a$ 从大到小排序（价值相同的立方体顺序任意），使得排完序后 $a$ 单调不增，并且拿走此时的前 $k$ 个立方体。

现在给定 $n,f,k,\{a_1,a_2,\cdots,a_n\}$（保证 $1\le f,k\le n\le100,1\le a_i\le 100$），试判断 Dimtry 喜欢的（即原来的第 $f$ 个）立方体是否会被拿走。

如果在所有情况下都会被拿走，输出 ```YES```。

如果在所有情况下都不会被拿走，输出 ```NO```。

如果在所有情况下，有可能被拿走，有可能不被拿走，输出 ```MAYBE```。

本题单个测试点存在多组测试数据，保证测试数据组数 $t$ 不超过 $1000$。
## 解题思路
首先保存原来第 $f$ 个立方体的价值 $a_f$，并对 $a$ 排序，然后分成两类讨论。

第一类：价值为 $a_f$ 的立方体只有一个。

此时，Dimtry 喜欢的立方体在排序后位置确定。

记这个立方体现在的下标为 $f'$。

若 $f'\le k$，输出 ```YES```，否则输出 ```NO```。

第二类：有多个立方体的价值为 $a_f$。

排序后，记最左端值为 $a_f$ 的 $a$ 下标为 $l$，记最右端值为 $a_f$ 的 $a$ 下标为 $r$。显然，$1\le l\le r\le n$。

若 $r\le k$，输出 ```YES```。

若 $l\le k<r$，输出 ```MAYBE```。

若 $k<l$，输出 ```NO```。

上述做法的正确性显然，证明无需赘述。

查找一次所需的 $f',l$ 或 $r$ 的时间复杂度为 $O(n)$，排序一次的时间复杂度为 $O(n\log n)$。

所以总的时间复杂度为 $O(tn\log n)$，可以通过本题。
## 参考代码
```cpp
#include<algorithm>
#include<iostream>
using namespace std;
int t,n,f,k;
int a[105];
bool cmp(int pre,int nxt){
	return pre>nxt;
}
int main(){
	ios::sync_with_stdio(false);
	cin>>t;
	while(t--){
		cin>>n>>f>>k;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		int tmp=a[f];
		sort(a+1,a+n+1,cmp);
		int cnt=0;
		for(int i=1;i<=n;i++){
			if(a[i]==tmp) cnt++;
		}
		if(cnt>1){
			bool f1=false,f2=false;
			for(int i=1;i<=k;i++){
				if(a[i]==tmp){
					f1=true;
					break;
				}
			}
			for(int i=k+1;i<=n;i++){
				if(a[i]==tmp){
					f2=true;
					break;
				} 
			}
			if(f1&&f2) cout<<"MAYBE\n";
			else if(f1&&!f2) cout<<"YES\n";
			else if(!f1&&f2) cout<<"NO\n";
		}else{
			for(int i=1;i<=n;i++){
				if(a[i]==tmp){
					if(i<=k) cout<<"YES\n";
					else cout<<"NO\n";
					break;
				}
			}
		}
	}
}
```
[本代码可以通过 CF 的评测。](https://www.luogu.com.cn/record/161251080)

Written by [toolong114514](https://www.luogu.com/user/477821) on 2024/6/4.

---

## 作者：NEKO_Daze (赞：2)

洛谷题目传送门：[CF1980B](https://www.luogu.com.cn/problem/CF1980B)   | |  CF原题传送门：[1980B](https://codeforces.com/contest/1980/problem/B)

#### 简要题意

将 $n$ 个立方体，第 $i$ 个立方体的值是 $a_i$。将这些立方体按值**从大到小排序**后，取出前 $k$ 个立方体，问这其中是否有**排序前**的第 $f$ 个立方体。

当两个立方体值相同时，可以随意排序。

#### 思路

为了方便，我改为从小到大排序，然后从后往前取立方体，那么我们只要记一开始第 $f$ 个立方体的值 $a_f$ 为 $ss$，排完序后要取出后 $k$ 个立方体，那么判断 $ss$ 与第 $n-k$ 个立方体的大小关系即可。具体分为三种情况：

* $a_{n-k} < ss$，即剩余立方体中值最大的立方体的值比 $ss$ 大，必然不会取到，输出 `YES`；
* $a_{n-k} = a_{n-k+1} = ss$，即从后往前取的最后一个立方体与余立方体中值最大的立方体的值相等， $ss$ 可能也混在其中，输出 `MAYBE`；
* $a_{n-k} > ss$，即剩余立方体中值最大的立方体的值比 $ss$ 小，必然在取到的立方体中，输出 `NO`。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
int a[105],n,k,f;
int ss;
int main(){
	cin.tie(0);
	cin>>T;
	while(T--){
		cin>>n>>f>>k;
		for(int i=1;i<=n;i++)cin>>a[i];
		ss=a[f];
		sort(a+1,a+n+1);
		if(a[n-k]<ss)puts("Yes");
		else if(a[n-k+1]==ss&&a[n-k]==ss)puts("Maybe");
		else puts("No");
	}
    return 0；
}
```

---

## 作者：Stars_visitor_tyw (赞：1)

## CF1980B Choosing Cubes 题解
### 分析
简单分类讨论。

观察到之所以会出现“有可能被拿走，有可能不被拿走”的情况，是因为 $a_f$ 可能有多个，且将序列排序后多个 $a_f$ 可能有的下标小于或等于 $k$，而有的大于 $k$。

思路就很明确了，对序列排序。遍历序列找到第一个值为 $a_f$ 的元素的下标，记为 $lt$，找到最后一个值为 $a_f$ 的元素的下标，记为 $rt$。

- 若 $lt=rt$，当 $lt \le k$ 时，输出 `YES`；当 $lt>k$ 时，输出 `NO`。

- 若 $lt \neq rt$，当 $lt>k$ 时，输出 `NO`；当 $lt \le k$ 并且 $rt \le k$ 时，输出 `YES`；当 $lt \le k$ 并且 $rt>k$ 时，输出 `MAYBE`。

注意：题目中的 $f$ 为排序之前的，需要提前记录 $a_f$ 的值。
### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, a[105], k, f;
bool cmp(int x, int y){return x>y;}
signed main()
{
    int t;
    for(cin>>t;t;t--)
    {
        cin>>n>>f>>k;
        for(int i=1;i<=n;i++)
        {
            cin>>a[i];
        }
        int af=a[f];
        sort(a+1,a+1+n,cmp);
        int lt=0, rt=0;
        for(int i=1;i<=n;i++)
        {
            if(a[i]==af&&!lt)
            {
                lt=i;
            }
            if(a[i]==af)
            {
                rt=i;
            }
        }
        if(lt==rt)
        {
            if(lt<=k)
            {
                cout<<"YES\n";
            }
            else
            {
                cout<<"NO\n";
            }
        }
        else
        {
            if(lt>k)
            {
                cout<<"NO\n";
            }
            else if(lt<=k&&rt<=k)
            {
                cout<<"YES\n";
            }
            else
            {
                cout<<"MAYBE\n";
            }
        }
    }
}
```

---

## 作者：FXLIR (赞：1)

### 题意
有 $n$ 个立方体，编号为 $1$ 到 $n$，第 $i$  个立方体显示的数值为 $a_i$。

现在将所有立方体按照数值从大到小排序（数值相等的立方体可以按**任意顺序**排序），然后取出前 $k$ 个立方体，问取出的立方体中有没有**原本**编号为 $f$ 的立方体。如果有，输出 `YES`，如果没有，输出 `NO`，如果可能有，输出 `MAYBE`。

### 做法
因为排序后编号可能会混乱，所以可以先用一个变量记录下原本编号为 $f$ 的立方体显示的数值 $a_f$，然后再将数值排序。

接下来，进行分类讨论：

设 $a_f$ 为 $num$。

- 如果所有数值为 $num$ 的立方体都被拿出，或所有立方体都被拿出，那么原本编号为 $f$ 的立方体肯定被拿出了，输出 `YES`。

- 如果前 $k$ 个立方体的数值都比 $num$ 大，那么原本编号为 $f$ 的立方体肯定没有被拿出，输出 `NO`。

- 否则，原本编号为 $k$ 的立方体可能被拿出了，也可能没有，输出 `MAYBE` 即可。

### AC code
```cpp
#include<iostream>
#include<algorithm>
#define int long long
using namespace std;
const int N=1e2+5;
int t,n,k,f,num,a[N];
bool cmp(int x,int y){
	return x>y;
}
signed main(){
	cin>>t;
	while(t--){
		cin>>n>>f>>k;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		num=a[f];
		sort(a+1,a+n+1,cmp);
		if(a[k]==num&&a[k+1]<num||k==n||a[k]<num){
			cout<<"YES";
		}else if(a[k]>num){
			cout<<"NO";
		}else{
			cout<<"MAYBE";
		}
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：Dream_Mr_li (赞：0)

## 思路

我们先对立方体的值进行顺序排序。

然后，我们判断最喜欢的立方体在排序后的位置以及与之相邻的立方体的值，以确定是否会被移除。具体判断条件如下：

- 如果最喜欢的立方体在前 $k$ 个立方体中，并且它的值与第 $k$ 个立方体的值相同且第 $k+1$ 个立方体的值小于它的值，或者 $k$ 等于 $n$（即所有立方体都被移除），或者第 $k$ 个立方体的值小于它的值，则最喜欢的立方体一定会被移除。

- 如果最喜欢的立方体的值大于第 $k$ 个立方体的值，则一定不会被移除。

 - 否则，可能会被移除。

## 代码实现

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e2+10;

// 比较函数，用于排序
bool cmp(int x,int y) {
    return x > y;
}

int t,n,f,k,a[N],jl;

signed main() {
    cin >> t;
    while(t--) {
   
        cin >> n >> f >> k;
        
        for(int i = 1; i <= n; i++) {
            cin >> a[i];
        }
      	
      	jl=a[f];
      	
        sort(a + 1, a + n + 1, cmp); // 顺序排序

        if((a[k] == jl && a[k + 1] < jl) || k == n || a[k] < jl) {
            cout << "YES\n"; // 一定会被移除
        } else if(a[k] > jl) {
            cout << "NO\n"; // 一定不会被移除
        } else {
            cout << "MAYBE\n"; // 可能会被移除
        }
    }
    return 0;
}
```

---

## 作者：chenlongli (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1980B)
### 思路
我们可以先将数字降序排序。

如果这个数字一定不会删除，那么最后一个删除的数字一定会大于我们最喜欢的数字。

如果这个数字一定会删除，那么就有一下几种可能，要么序列被全部删除了，那么这时的 $k$ 值就会和 $n$ 的值一样，也有可能是因为最后一个删除的数字已经小于我们最喜欢的数字，但如果我们最喜欢的数是和最后一个删除的数字一样，并且第一个没被删除的数字比我们最喜欢的数小，那么我们此时最喜欢的数就是最后一个被删除的数。

如果都不满足上面的两种情况，那么这个最喜欢的数字就可能被删除，也可能没被删除。
### code
```cpp
#include<bits/stdc++.h>
using namespace std;
bool cmp(int s1,int s2)
{
	return s1>s2;
}
int main()
{
    int t;
    cin>>t;
    for (int i=0;i<t;i++)
    {
    	int n,a,b;
    	cin>>n>>a>>b;
    	int c[n];
    	for (int j=0;j<n;j++)
    	{
    		cin>>c[j];
		}
		int z=c[a-1];
		sort(c,c+n,cmp);
		if (c[b-1]>z)
		{
			cout<<"no"<<endl;
		}
		else
		{
			if (c[b-1]<z)
			{
				cout<<"yes"<<endl;
			}
			else
			{
				if ((c[b-1]==z&&c[b]<z)||b==n||c[b-1]<z)
				{
					cout<<"yes"<<endl;
				}
				else 
				{
					cout<<"maybe"<<endl;
				}
			}
		}
	}
}
```

---

## 作者：GeYang (赞：0)

# 题意

某人有 $n$ 个正方体，从左到右编号，其中，他最喜欢第 $f$ 个正方体。接着，他把这些正方体按降序排列，同样编号的正方体排列后顺序任意。然后他删除了前 $k$ 个正方体，问他最喜欢的正方体有没有可能被删除。

# 思路

既然同样编号的正方体排序后可以在不同位置，所以可以将编号相同的正方体视为同一个正方体。

所以只需要先降序排序，再看与他最喜欢的正方体编号一样的正方体的位置，然后做分类讨论即可。

- 排序后，这一类正方体都在第 $k$ 个正方体之后，那么一定不会被删除。

- 排序后，所有正方体都在第 $k$ 个正方体之前，那么一点会被删除。

- 排序后，删除了全部正方体，那么一定会被删除。

- 排序后，有一个这种正方体是第 $k$ 个，但是在它之后的正方体编号都比它小，那么一定会被删除。

- 若以上情况都不是，那就有可能被删除，有可能被保留。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[105],t,n,f,k,ans;
bool cmp(int a,int b)
{
	return a>b;
}
void solve()
{
	cin>>n>>f>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	ans=a[f];
	sort(a+1,a+n+1,cmp);
	if(a[k]>ans) cout<<"NO\n";
	else if((a[k]==ans&&a[k+1]<ans)||k==n||a[k]<ans) cout<<"YES\n";
	else cout<<"MAYBE\n";
	return;
}
int main()
{
	cin>>t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：YuYuanPQ (赞：0)

设 Dmitry 喜欢的立方体的值为 $lik=a_f$（排序会打乱顺序，需要先存下来）。

按照题意降序排序，并分类讨论。

对于所有的 $a_i=lik$：

- 当所有 $i \leq k$ 时，那么这些立方体必然会被移除，故答案为 `YES`。

- 当所有 $i>k$ 时，那么这些立方体必然不会被移除，故答案为 `NO`。

- 当一部分 $i \leq k$，另一部分 $i>k$ 时，那么这些立方体有可能被移除，故答案为 `MAYBE`。

重要提醒（也可能并不重要）：**"the first $k$ cubes"是"前 $k$ 个"的意思**

~~英语不好，导致读题时一直理解题意，卡了很久，吐槽~~

## Code

[Link](https://codeforces.com/contest/1980/submission/263960315)

---

## 作者：Hacker_Cracker (赞：0)

## CF1980B Choosing Cubes
### Solution
我们首先要找到索引是 $k$ 的立方体 $a_f$ ，这里记为 $res$ ，然后进行降序排序。排完序后我们找到第 $k+1$ 个数 ，即未被移除的最大立方体。

下面分类讨论：
+ 第一种情况，$a_{k+1} =  a_k  =  res$ ，这时无法确定 $res$ 是否被移除，输出 `MAYBE` 。
+ 弟二种情况，$a_{k+1} < res$ ，此时 $res$ 必会被移除。输出 `YES` 。
+ 其他情况，$res$ 必定不会移除，就输出 `NO` 。

**注意！每次操作之前要清空数组。**
### [AC](https://www.luogu.com.cn/record/161246449) Code
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int MAXN=1e2+10;
int a[MAXN];
bool cmp(int a,int b){
	return a>b;
}
int main(){
	int T;
	cin>>T;
	while(T--){
		memset(a,0,sizeof(a));
		int n,f,k,tmp=0;
		cin>>n>>f>>k;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			if(i==f) tmp=a[i];
		}
		sort(a+1,a+n+1,cmp);
		if(a[k+1]>=tmp){
			if(a[k]==tmp&&a[k+1]==tmp) puts("MAYBE");
			else puts("NO");
		}else puts("YES");
	}
	return 0;
} 
```

---

