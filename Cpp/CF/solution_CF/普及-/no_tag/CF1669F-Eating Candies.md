# Eating Candies

## 题目描述

There are $ n $ candies put from left to right on a table. The candies are numbered from left to right. The $ i $ -th candy has weight $ w_i $ . Alice and Bob eat candies.

Alice can eat any number of candies from the left (she can't skip candies, she eats them in a row).

Bob can eat any number of candies from the right (he can't skip candies, he eats them in a row).

Of course, if Alice ate a candy, Bob can't eat it (and vice versa).

They want to be fair. Their goal is to eat the same total weight of candies. What is the most number of candies they can eat in total?

## 说明/提示

For the first test case, Alice will eat one candy from the left and Bob will eat one candy from the right. There is no better way for them to eat the same total amount of weight. The answer is $ 2 $ because they eat two candies in total.

For the second test case, Alice will eat the first three candies from the left (with total weight $ 7 $ ) and Bob will eat the first three candies from the right (with total weight $ 7 $ ). They cannot eat more candies since all the candies have been eaten, so the answer is $ 6 $ (because they eat six candies in total).

For the third test case, there is no way Alice and Bob will eat the same non-zero weight so the answer is $ 0 $ .

For the fourth test case, Alice will eat candies with weights $ [7, 3, 20] $ and Bob will eat candies with weights $ [10, 8, 11, 1] $ , they each eat $ 30 $ weight. There is no better partition so the answer is $ 7 $ .

## 样例 #1

### 输入

```
4
3
10 20 10
6
2 1 4 2 4 1
5
1 2 4 8 16
9
7 3 20 5 15 1 11 8 10```

### 输出

```
2
6
0
7```

# 题解

## 作者：IvanZhang2009 (赞：6)

## 题意
有很多颗糖摆成 $n$ 堆，两个人来吃糖。一个人从前往后吃，每次吃掉一堆；另一个人从后往前吃，每次吃掉一堆。如果两个人不能一起吃一堆糖，且两人吃的糖总数相同，问两个人最多一共可以吃多少**堆**糖。

## 解法
考虑双指针。不会出门右拐[看这里](https://oi-wiki.org/misc/two-pointer/)。

一个指针 $x$ 从前往后去跑第一个人吃的糖，另一个指针 $y$ 从后往前，看要使从后往前吃的糖总数**大于等于**从前往后吃的糖 需要吃到哪里。如果能使从后往前吃的糖总数**等于**从前往后吃的糖，那么和答案进行比较。

也就是说，每次 ``x++``，然后一直让 ``y--`` 使得 $\sum^{x}_{i=1}{a_i}\le\sum^{n}_{i=y}{a_i}$。

## 代码
```cpp
#define REP(i,a,n) for(int i=(a);i<(n);i++)
int n;
int a[200005];
void Main(){
    cin>>n;
    REP(i,0,n)cin>>a[i];
    int x=0,y=n-1;   //两个指针，一个往后，一个往前
    int sum1=0,sum2=0,ans=0;  //sum1记录前缀和,sum2记录后缀和，ans记录答案
    while(x<=y){
        sum1+=a[x];
        while(y>x&&sum2<sum1)sum2+=a[y],y--;
        if(sum2==sum1)ans=max(ans,x+n-y);  //如果能使两人吃到的糖相同，记录答案。
        x++;
    }
    cout<<ans<<endl;
}
```

---

## 作者：GI录像机 (赞：2)

## 思路简述：

既然只能连续地吃糖果，那我们考虑维护一个前缀和一个后缀。

显然，时间复杂度为 $O(n^2)$ 的做法是，枚举每一个前后缀，并比较他们的值，如果相等就记录。

但这样的复杂度我们显然不能接受，于是考虑优化。我们发现，$1\le w_i\le 10^4$，这说明，我们的前缀之间**两两不等**！因而，我们可以用一个 map 容器来存储前缀，再用后缀的值来寻找，这样复杂度就变成了 $O(n\log{n})$。最后注意判断两者吃的糖果有没有交集。

## 参考代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int read() {
	int f = 1, x = 0;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-')f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0';
		c = getchar();
	}
	return f * x;
}
void write(int x) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x > 9)write(x / 10);
	putchar(x % 10 + '0');
}
int t = read();
int main() {
	while (t--) {
		int n = read(), ans = 0, a[int(2e5) + 10], hsum[int(2e5 + 10)], tsum[int(2e5) + 10];
		map<int, int>mp;
		tsum[n + 1] = hsum[0] = 0;
		for (int i = 1; i <= n; i++) {
			a[i] = read();
			hsum[i] = hsum[i - 1] + a[i];
			mp[hsum[i]] = i;
		}
		for (int i = n; i >= 1; i--) {
			tsum[i] = tsum[i + 1] + a[i];
			if (mp[tsum[i]] && i > mp[tsum[i]])ans = max(ans, n - i + 1 + mp[tsum[i]]);
		}
		write(ans);
		putchar('\n');
	}
	return 0;
}
```


---

## 作者：happy_dengziyue (赞：2)

### 1 思路

首先设 $sl[i]=\sum_{j=1}^ia[j]$，$sr[i]=\sum_{j=i}^na[j]$，即前缀和和后缀和。

我们可以发现，设 `Alice` 吃 $[1,i]$，`Bob` 吃 $[x,n]$，则必有 $sl[i]=sr[x]$。

那么我们枚举每一个 $i$ ，然后二分处理 $x$ 即可。

### 2 代码与记录

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
#define max_n 200000
int t;
int n;
int a[max_n+2];
int sl[max_n+2];
int sr[max_n+2];
int ans;
int ask(int l,int r,int x){
	int mid;
	int res=-1;
	while(l<=r){
		mid=(l+r)>>1;
		if(x==sr[mid]){
			res=mid;
			break;
		}
		if(x<sr[mid])l=mid+1;
		else r=mid-1;
	}
	return res;
}
int ma(int a,int b){
	return a>b?a:b;
}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1669F_1.in","r",stdin);
	freopen("CF1669F_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;++i)scanf("%d",a+i);
		sl[0]=0;
		for(int i=1;i<=n;++i)sl[i]=sl[i-1]+a[i];
		sr[n+1]=0;
		for(int i=n;i>=1;--i)sr[i]=sr[i+1]+a[i];
		ans=0;
		for(int i=1,x;i<=n;++i){
			x=ask(i+1,n,sl[i]);
			if(x!=-1)ans=ma(ans,i+n-x+1);
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/74393582)

By **dengziyue**

---

## 作者：charleshe (赞：0)

由于 $\text{Alice}$ 只能从左边开始吃糖，$\text{Bob}$ 只能从右边开始吃糖，因此这段过程可以抽象成：从数列的左右两边取数。

自然想到 `deque` 或者使用双指针。这篇题解用的是 `deque`。

每次判断：

- 如果 $\text{Alice}$ 所吃的糖的总质量小于 $\text{Bob}$ 的：直接给 $\text{Alice}$ 一颗糖（很简单，因为要使两人的糖的质量相等就要尽量平均）。

- 如果 $\text{Alice}$ 所吃的糖的总质量大于 $\text{Bob}$ 的：直接给 $\text{Bob}$ 一颗糖（同上）。

- 如果 $\text{Alice}$ 所吃的糖的总质量等于 $\text{Bob}$ 的：更新两人可吃的最大糖数，并塞给 $\text{Alice}$ 一颗糖（给 $\text{Bob}$ 也可以）。

由于每次判断都会取走一颗糖，因此上面操作会执行 $n$ 次（$n$ 为一次数据中糖的数量）。时间复杂度可以接受。

综上，本题就做完了。

注意事项：

- **大赛建议不要使用 `deque` 容器。** 因为 `deque` 常数极大，稍不留心就会 TLE。解决方案：数组模拟（即双指针）很好用。

- 本题多测。

- 当队列空时，此时 $\text{Alice}$ 和 $\text{Bob}$ 的糖果的质量有可能相等，**因此在队列清空后需要再判断一次能否更新两人可吃的最大糖数。**

想到这些，代码便好写了。

```cpp
#include <iostream>
#include <queue>
using namespace std;
deque<int> q;
int t,n,a;
int main(){
	cin>>t;
	while(t--){
		q.clear();
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a;
			q.push_back(a);//从双端队列队尾插入元素，保证最后的队列状态同输入时的状态
		}
		int alice=0,bob=0,ar=0,br=0;//alice存Alice吃的糖的质量，bob亦然；ar存Alice吃的糖果数，br亦然。
		int ans=0;
		while(!q.empty()){
			if(alice==bob){
				ans=ar+br;
				alice+=q.front();
				ar++;
				q.pop_front();
			}
			else if(alice<bob){
				alice+=q.front();
				q.pop_front();
				ar++;
			}
			else{
				bob+=q.back();
				q.pop_back();
				br++;
			}
		}
		if(alice==bob) ans=ar+br;//注意这里还要再判断一次
		cout<<ans<<endl;
	}
	return 0;
}
```


---

