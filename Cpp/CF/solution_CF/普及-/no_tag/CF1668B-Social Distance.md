# Social Distance

## 题目描述

有一圈共 $m$ 个座椅（编号 $0 \sim m-1$），有 $n$ 个人要坐在上面，第 $i$ 个人左右两边至少要有 $a_i$ 个空座椅，问是否有一种方案可以使得所有人都能坐在上面。

## 说明/提示

样例第一组询问：人数大于座椅数，无解。

样例第二组询问：一种可行解为第一个人坐编号为 $2$ 的座椅，第二个人坐编号为 $0$ 的座椅。

样例第三组询问：第二个人无论坐哪，第一个人都没有位置，无解。

样例第四组询问：一种可行解为第一个人坐编号为 $1$ 的座椅，第二个人坐编号为 $4$ 的座椅，第三个人坐编号为 $7$ 的座椅。

## 样例 #1

### 输入

```
6
3 2
1 1 1
2 4
1 1
2 5
2 1
3 8
1 2 1
4 12
1 2 1 3
4 19
1 2 1 3```

### 输出

```
NO
YES
NO
YES
NO
YES```

# 题解

## 作者：Composite_Function (赞：7)

# 思路

可以发现，第 $i$ 和 $j$ 个人必须间隔椅子把数为它们需求中最大值，否则一定有一个人不满足。

既然这样，无论当前所需间隔最大的人身边做什么人，那个人所需间隔还是最大的间隔。因为题目中说的是最小需求，于是就将当前需求最大的人放在一起，这样就不用再去考虑第二大的人了。接下来再放剩下的，重复执行直至安排完所有人。

------------

# update-证明

~~话说怎么已经交上去的题解还能被撤~~~

给出**思路**的证明：

设共有 $n$ 人，需求间隔为 $a_1 , a_2 , ... , a_{n - 1} , a_{n}$，按从小到大的顺序排列。排好序后的为 $b_1 , b_2 , ... , b_{n-1} , b_{n}$ 。所求即为 $\sum_{i = 1}^n \left\{
\begin{array}{rcl}
\max(b_i , b_{i+1})& &i ≠ n\\
\max(b_1 , b_n)& &i = n\\
\end{array} \right.
$

设 $dis_i=\left\{
\begin{array}{rcl}
|b_{i+1} - b_i|& &i ≠ n\\
|b_n - b_1|& &i = n\\
\end{array} \right.$ 

显然就是求 $\sum_{i = 1}^n dis_i$ 最小值

则最小值为 $a_n - a_1$ 等号当且仅当 $b_1 ≤ b_2 ≤ ... ≤ b_{n-1} ≤ b_n$

得证！(〃￣︶￣)人(￣︶￣〃)

------------

# 代码

```cpp
#include<bits/stdc++.h>
//我最喜欢的万能头
using namespace std;
long long t,n,m,a[200010];
//定义，数组尽量用全局变量
int main(){
    cin>>t;
    while(t--){
        cin>>n>>m;
        for(long long i=1;i<=n;i++) cin>>a[i];
        sort(a+1,a+n+1);
        //排序
        long long num=n;
        //别忘了座的人自己
        for(long long i=1;i<=n;i++)
            num+=(i==1?a[n]:a[i]);
            //第1个人和第n个人排在一起
        cout<<(num<=m?"Yes":"No")<<endl;
    }
    return 0;
    //要养成好习惯哦
}
```

## 粘代码前请三思而后行，做题是为了学习，而不是为了显摆

这是本蒟蒻递交的第一篇题解，希望管理员通过

千山万水总是情，给个点赞行不行~

---

## 作者：white_carton (赞：1)

[$\color{#52C41A}\text{推销博客}$](https://starback24.github.io)

[$\color{#52C41A}\text{题目传送门}$](https://www.luogu.com.cn/problem/CF1668B)

### 思路

首先我将 $a_i$ 称作距离。

容易发现，第 $i$ 个人和第 $j$ 个人之间的距离是 $\max(a_i,a_j)$ ，我们的任务就是最小化 $\sum\limits_{i=1}^n\max(a_i,a_j)+\max(a_1,a_n)$ 。

我们希望将大的距离**尽可能少地计入**，第一大的距离肯定被记作 $2$ 次，第二大的距离要是想被记作 $1$ 次，就必须放在第一大的距离旁边，往后以此类推，我们惊奇地发现，符合这个条件的是个有序序列，所以我们将 $a$ 排一遍序，统计答案即可。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[100100];
void solve(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+1+n);        //排序
	int sum=0;
	for(int i=2;i<=n;i++){
		sum+=a[i];         //排序后a[i]和a[i-1]的max一定是a[i]
	}
	sum+=a[n];            //是个环所以a[n]和a[1]放在一起
	if(sum+n>m){          //别忘了坐在椅子上的人
		cout<<"NO"<<endl;
	}
	else{
		cout<<"YES"<<endl;
	}
}
int main(){
	int t;
	cin>>t;
	while(t--){
		solve();
	}
}

```



---

## 作者：glx123 (赞：0)

# 题目概述
有**一圈**个数为 $m$ 的椅子，有 $n$ 个人，要求每人左右有若干空位，求是否有解。
# 分析
也就是说，相邻两人的距离要大于等于两人需要空位的较大者（我们使用快排一下就能求出较大者了），如果不满足，则无解。
# 代码
```
#include<bits/stdc++.h>
using namespace std;
int main(){
	int T;
	cin>>T;
	while(T--){
		int n,m,a[100050];
		cin>>n>>m;
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
		}
		sort(a+1,a+1+n);//先排序 。 
		long long int sum=0;
		for(int i=2;i<=n;i++){
			sum+=a[i];
		}
		sum+=a[n];//因为是一个圈，max(a[1],a[n])。 
		if(sum+n>m){//别忘了每个人。 
			cout<<"NO\n";
		}else{
			cout<<"YES\n";
		}
	}
	return 0;
}

```
完成！


---

## 作者：Terry2011 (赞：0)

# 题目分析

1. 因为第 $i$ 个人左右两边至少要有 $i$ 个空座椅，所以，两个人之间的距离应为 $i$ 和 $j$ 的最大值。
1. 因此，我们需要使 $\sum _ {i = 1} ^ {n-1}\max(a _ {i},a_{i-1})+\max(a _ {1},a_{n})$ 最小，我们可以通过 sort 排序来实现，让大的数和大的数在一起。

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,a[200010];//定义
int main(){
    cin>>t;
    while(t--){
        cin>>n>>m;
        for(long long i=1;i<=n;i++) cin>>a[i];//输入
        sort(a+1,a+n+1);//排序
        int num=n;//更新
        for(long long i=1;i<=n;i++){
        if(i==1) num+=a[n];
        else num+=a[i];
        }
        if(num<=m) cout<<"Yes"<<endl;
        else cout<<"No"<<endl;
    }
    return 0;
}
```

---

## 作者：wcop114514 (赞：0)

**题目分析**

题目让我们判断能否坐下人。我们可以定义一个变量 $ans$，计算要使用最小的位置数量。

计算方式：将空位最大的人放在一起，这样就不用考虑第二大的人的空位，放旁边行。剩下的以此类推，重复执行直至安排完所有人。

若它大于 $m$ 输出错，否则对。

给大佬们奉上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long//懒人神器 ll a相当于long long a
ll t,n,m,a[1008666];
void solve(){
	cin>>n>>m;//输入
        for(ll i=1;i<=n;i++) cin>>a[i];
        sort(a+1,a+n+1);//从小到大排序
        ll ans=n;
        for(ll i=1;i<=n;i++){//计算
        	if(i==1)ans+=a[n];
        	else
			ans+=a[i];
    	}
    	if(ans<=m)cout<<"YES";//判断
    	else cout<<"NO";
    	cout<<endl;
    return ;
}
int main(){
    cin>>t;
    while(t--)solve();
    return 0;
}
```

---

## 作者：haokee (赞：0)

## 题目大意

- $n$ 个人要坐在 $m$ 个椅子组成的环上面；
- 第 $i$ 个人左右要空 $a_i$ 的位置；
- 判断能否坐下 $n$ 个人。
  
## 思路

既然是两个人互相空位置，那么两个人隔得位置越相近肯定就越好。我们直接排序一遍，这样子相邻的两个人必然空的位置大小最靠近。由于这些椅子组成了一个环，那么第 $1$ 个人就会挨着第 $n$ 个人。我们统计一下至少需要多少个位置，再判断是否匹配条件。

## 代码

```cpp
#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;  // 开long long

const int kMaxN = 5e4 + 1;

ll a[kMaxN], t, n, m, ans;

int main() {
  for (cin >> t; t; --t) {
    cin >> n >> m, ans = 0;
    for (int i = 1; i <= n; ++i) {
      cin >> a[i];
    }
    sort(a + 1, a + n + 1);  // 从小到大排序一遍
    for (int i = 1; i <= n; ++i) {
      ans += a[i == 1 ? n : i] + 1;  // 特判，记得加一
    }
    cout << (ans <= m ? "YES" : "NO") << '\n';  // 判断是否符合条件
  }
  return 0;
}
```

---

## 作者：___cjy__ (赞：0)

# CF1668B Social Distance 题解

[题目传送门](https://www.luogu.com.cn/problem/CF1668B)

[更好的阅读体验](https://www.luogu.com.cn/blog/509668/solution-cf1668b)

### 题目大意：

有 $M$ 个座椅围成一圈，有 $N$ 个人要坐，第 $i$ 个人左右两边至少要有 $a_i$ 个空位。问是否有一种方案使得所有人都能按规定坐在上面。

### 正文：

贪心：当 $a_i$ 的值越大，第 $i$ 个人所占的位置就会越多。我们要尽可能地使两个相邻的人之间空位重合的部分尽量多，即让尽可能多的空位既算在 $a_i$ 又算在 $a_{i+1}$ 之中。

显然的，每次选取 $a_i$ 最大的两个人坐在一起，可以使消耗的位置尽量小。因此我们将 $a_i$ 的值进行升序或者降序的排序，让每一个第 $i$ 个人和第 $i+1$ 个人相邻，并且同时让第 $1$ 个人和第 $N$ 个人相邻，就可以使消耗的座椅数量尽量小。

在上述过程中，每次统计空位数量,即 $\max(a_i, a_{i + 1})$，以及在位置上的人数，最终与 $M$ 的值进行比较，输出结果。

### AC Code：

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 114514

using namespace std;

int T, m, n, a[N], sum;

signed main(){
	cin >> T;
	
	while(T--){
		sum = 0;
		cin >> n >> m;
		for(int i=1; i<=n; i++)
			cin >> a[i];
		sort(a + 1, a + 1 + n);
		a[n + 1] = a[1];
		for(int i=1; i<=n; i++){
			sum += max(a[i], a[i + 1]);
		}
		sum += n;
		if(sum <= m) cout << "YES\n";
		else cout << "NO\n";
	}
	
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

## 思路
读题不难得出，两人之间一定有空位置（你输入的），那就尽量让这空位量变小，所以需要排序一下，把空位最大的和第二大的一起，最小的和第二小的一起等等（注：第一个人和最后一个人挨着），其实两人取最大值就可以了。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,m,a[200010];//定义，long long 一定要开
int main(){
    cin>>t;
    while(t--){//t组询问
        cin>>n>>m;//输入
        for(long long i=1;i<=n;i++) cin>>a[i];
        sort(a+1,a+n+1);//排序
        long long num=n;
        for(long long i=1;i<=n;i++){
        	if(i==1) num+=a[n];
        	else num+=a[i];
		}
		if(num<=m) cout<<"Yes";
		else cout<<"No";
        cout<<endl;
    }//计算并判断
    return 0;//结束
}
```

---

