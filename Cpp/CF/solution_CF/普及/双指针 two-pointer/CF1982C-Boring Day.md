# Boring Day

## 题目描述

在又一个无聊的日子里，Egor 感到无聊，决定做点什么。但由于他没有朋友，他想出了一个游戏来玩。

Egor 有一叠 $n$ 张牌，从上到下第 $i$ 张牌上写着数字 $a_i$。Egor 想要进行若干轮游戏，直到牌用完。在每一轮中，他可以从牌堆顶端取出非零数量的牌，然后结束本轮。如果本轮取出的牌上的数字之和在 $l$ 到 $r$ 之间（包含 $l$ 和 $r$），则本轮获胜；否则，本轮失败。

Egor 已经记住了牌的顺序。请你帮助 Egor 计算，在这种游戏中他最多能赢多少轮。注意，Egor 并不要求连续获胜。

## 说明/提示

在第一个测试用例中，Egor 可以赢 $3$ 轮：

- 第一轮，取最上面的 $2$ 张牌，数值分别为 $2$ 和 $1$，它们的和为 $3$，在 $[l, r]$ 范围内，获胜。此后牌堆变为 $[11, 3, 7]$。
- 第二轮，取最上面的一张牌，数值为 $11$，大于 $r = 10$，失败。此后牌堆变为 $[3, 7]$。
- 第三轮，取最上面的一张牌，数值为 $3$，获胜。此后牌堆变为 $[7]$。
- 第四轮，只剩最后一张牌，数值为 $7$，获胜。

在第二个测试用例中，无论如何 Egor 都无法获胜。

在第三个测试用例中，每轮取一张牌，第一轮和第三轮失败，第二轮获胜。

在第四个测试用例中，每轮取两张牌，每轮都能获胜。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
8
5 3 10
2 1 11 3 7
10 1 5
17 8 12 11 7 11 21 13 10 8
3 4 5
3 4 2
8 12 25
10 7 5 13 8 9 12 7
2 3 3
5 2
9 7 9
2 10 5 1 3 7 6 2 3
1 8 10
9
5 5 6
1 4 2 6 4```

### 输出

```
3
0
1
4
0
3
1
2```

# 题解

## 作者：jwsdy (赞：13)

# CF1982C Boring Day 题解

[题目传送门](https://www.luogu.com.cn/problem/CF1982C)

## 题目分析

题目主要是想让我们在一个数列中划分出若干个**不相交**的子区间，并保证区间和在 $l$ 到 $r$ 之间，求最多可划分出多少个这样的区间。

我们不难想到使用**双指针算法**，定义 $ll$ 和 $rr$ 分别表示一个区间的左端点下标和右端点下标，维护一个区间。

另外，定义区间和为 $sum$，根据 $l\le sum\le r$ 我们可以分为三种情况讨论：

### $sum<l$：

此时区间和还不够到达要求的最小值 $l$，此时我们需要向区间里加数，则**区间右端点右移**。

### $l\le sum\le r$：

此时刚好满足我们的要求，将结果 $ans$ 加一，并重新往后寻找新的区间，通过更改左端点实现，**别忘记将区间和 $sum$ 清零**。

### $sum>r$：

此时区间和比要求的最大值还要大，则需要减去区间里的数，通过**区间左端点右移**来实现。

### code
```
#include<bits/stdc++.h>
#define endl '\n'
#define int long long
using namespace std;
const int N=2e6+100;
int t;
int a[N];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--){
		int l,r,n;
		cin>>n>>l>>r;
		for(int i=1;i<=n;i++) cin>>a[i];
		int ll=1,rr=0,ans=0,sum=0;
		while(ll<=n&&rr<=n){//保证不越界
			if(sum>=l&&sum<=r){//满足题目要求
				ll=rr+1;//更新区间左端点
				ans++;//答案++
				sum=0;//清零区间和
			}                             
			else if(sum<l){
				rr++;
				sum+=a[rr];//将此数加入当前区间
			}
			else if(sum>r){
				sum-=a[ll];//将此数提出当前区间
				ll++;
			}
		}
		cout<<ans<<endl;
	}
	return 0;//养成好习惯 
}
```

完结撒花！❀

---

## 作者：zg_ji (赞：5)

### 题目分析

简单的一道指针题，我们可以定义两个指针，边遍历边计算。

当我们的区间和小于我的边界 $l$ 时，我就将右指针往后移，同时加上我当前的数。如果我的区间和大于边界 $r$ 时，我就先减去当前的数，再去将我的左边界后移。

当然循环的时候我要注意判断我的两个指针的位置，不让它们超过 $n$ 的值。如果我现在的区间和在 $l$ 和 $r$ 之间时，我就重置我的区间和，将答案加 $1$，将左指针移到右指针后面，同时跳出此次循环。注意右指针要从 $0$ 开始。

### Code

```
#include<bits/stdc++.h>
const int N=1e5+100;
using namespace std;

int T;
int sum;
int ans;
int a[N];
int ji,yu;
int n,l,r;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--)
	{
		ji=1,yu=0;
		ans=0,sum=0;
		cin>>n>>l>>r;
		for(int i=1;i<=n;i++) cin>>a[i];
		while(1)
		{
			if(ji>n||yu>n) break;
			if(sum>=l&&sum<=r)
			{
				sum=0;//如果不将sum清零，你就会爆零 
				ji=yu+1;
				ans++;
				continue;
			}
			if(sum<l) yu++,sum+=a[yu];
			if(sum>r) sum-=a[ji],ji++;
		}
		cout<<ans<<'\n';
	}
	
	return 0;
	
}
```

---

## 作者：xiaoxiongbinggan (赞：3)

# CF1982C Boring Day题解

## 题目分析
给定 $n$ 个数，求区间和使得区间和大小在题目给出的 $l$ 到 $r$ 之间。

一道双指针的题目（有人会说：当然了，标签里都给出了，不是双指针还能是什么），但在考场上可没有标签让你去写规定的算法。那这道题为什么是双指针呢？双指针是什么呢？

### 双指针算法介绍

双指针是指利用两个同向或反向的指针将遍历对象进行遍历，从而达到相应的目的。

### 为什么是双指针算法

本题中需要求出**区间和**，而 $n$ 的范围又是在 $2\times10^5$ 以内的，所以说 $n^2$ 的时间复杂度就得不到满分，此时使用双指针就可以使时间复杂度降为 $n$ 的。

本题应该利用**同向指针**(为什么呢？因为使用反向指针的难以遍历完所有符合题目的区间），两个指针从数组的开头开始遍历。

## 注：

$a$ 数组的范围是 $1\le a \le 10^9$,需要开 $long$ $long$。

##  code:
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
int T;
int n,l,r;
int a[1000000];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n>>l>>r;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		int y=0,z=1;//y为右指针，z为左指针
		int ans=0;//存答案数
		int cnt=0;//存区间和
		while(1){
			if(cnt>=l&&cnt<=r){//若区间和符合题意 
				ans++;
				z=y+1;//将区间缩小
				cnt=0;//区间和清零
				continue;//结束本次循环
			}
			if(cnt<l){//若区间和小于题目规定的最小值
				y++;//右指针向右移，因为题目给出了a数组总为正数，则此操作一定将区间和扩大
				cnt+=a[y];//加上移动后的值
			}
			if(cnt>r){//区间和大于最大值
				cnt-=a[z];//减去最左的值
				z++;//左指针向右移
                       //为什么这里是先减去值，后移动指针？ 因为若先移动指针，则减去的值不是原区间的最左值
			}
			if(y>n||z>n) break;//若指针超出数组的右端点，则说明数组遍历完了，推出此次循环
		}
		cout<<ans<<endl;
	}
	return 0;//不管怎样，一定要写
}
```

---

## 作者：xu_zhihao (赞：3)

### 前言

* 这题在比赛的时候，我充分发挥了人类的智慧，写了一个贪心，结果过了。最后拿到了 $4000$ 名多一点（第一题想了好久）。

### 题目理解

* 这题我个人觉得并不难。我的整体思路是利用双指针，先一直往后加和（后面的指针往后推），直到和不小于 $l$ 时，就将前指针也往后推，假如现所在位置为 $l$。那么就将 $sum-a_l$（$sum$ 为加和变量）。可证明，此方案无后效性，不会对答案造成干扰。

### AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[1000010];
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n,L,R;
		cin>>n>>L>>R;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
		}
		int cnt=0;
		long long sum=0;
		int l=0;
		for(int r=1;r<=n;r++)
		{
			sum+=a[r];
			while(l+1<=r && sum>R)
			{
				sum-=a[++l];
			}
			if(sum>=L && sum<=R)
			{
				cnt++;
				sum=0;
				l=r;
			}
		}
		cout<<cnt<<endl;
	}
}

```

---

## 作者：Specthraimn (赞：1)

# Boring Day 题解
### 大致题意
给一个长为 $n$ 的数列和范围 $l,r$，求能分割子段的最大数量，满足每个子段之和 $sum$，$l \le sum \le r$。
### 解题思路
考虑贪心加双指针，遍历一遍数组，维护一个字段的左右两端 $i,j$，统计答案 $ans$。  

1. 如果该子段和 $sum > r$，说明要减去队头的数，即 $sum-a_i$，并更新队头，将 $i+1$。
2. 如果 $sum < l$，说明要加上队尾的数，即 $sum+a_j$，并更新队尾，将 $j+1$。
3. 否则，该子段满足要求，将 $ans+1$。
   
最后输出答案 $ans$ 即可。
### AC 代码
```cpp
#include <iostream>
#pragma GCC optimize(2)
#pragma GCC optimize(3,"Ofast","inline")
using namespace std;
int t, n, l, r;
int a[100005];
void work(){
	scanf("%d%d%d", &n,&l,&r);
	for(int i = 1; i <= n; i++){
		scanf("%d", &a[i]);
	}
	int i = 1, j = 1, sum = 0, ans = 0;
	while(i <= n && j <= n + 1){
		if(sum < l){
			sum += a[j++];
		}else if(sum > r){
			sum -= a[i++];
		}else{
			sum = 0;
			i = j;
			ans++;
		}
	}
	printf("%d\n", ans);
	return;
}
signed main(){
	scanf("%d", &t);
	while(t--){
		work();
	}
	return 0;
}
```
### 完结撒花✿✿ヽ(°▽°)ノ✿

---

## 作者：HsNu1ly7_ (赞：1)

## 题意

给你 $n$ 个数，以及 $l$ 和 $r$，你每次可以从左往右拿走数，如果你的和在 $l$ 到 $r$ 之间，则你赢了一局，并弃掉所有数字，问你最多能赢几盘。

## 思路

要让赢的次数越多越好，可以用双指针，如果区间和在 $l$ 到 $r$ 之间，就清空，指针指向后面的位置。如果区间和小了，右指针后移，如果区间和大了，左指针后移。

代码（为了方便我把题目中的 $l$ 和 $r$ 命名为 $x$ 和 $y$ ）：

```cpp
#include <bits/stdc++.h>
using namespace std ;
#define int long long
int arr[100010] ;
void solve (){
	int n , x , y ;
	cin >> n >> x >> y ;
	for ( int i = 1 ; i <= n; i++ ){
		cin >> arr[i] ;
	}
	int ans = 0 ;
	int sum = 0 ;//记录区间和
	int l = 1 , r = 0 ;
	while ( l <= n && r <= n ){
		if ( sum >= x && sum <= y ){//区间和在x,y区间内
			sum  = 0 ;
			l = r + 1 ;
			ans++ ;
			continue ;
		}
		if ( sum < x ){//区间和小了，右指针后移
			r++ ;
			sum += arr[r] ;
		}
		if ( sum > y ){//区间和大了，左指针后移
			sum -= arr[l] ;
			l++ ;
		}
	}
	cout << ans << '\n' ;
	return ;
}
signed main (){
	ios::sync_with_stdio(0) ;
	cin.tie(0) ;
	cout.tie(0) ;
	int _ ;
	cin >> _ ;
	while ( _-- ){
		solve () ;
	}
	return 0 ;
}
```

---

## 作者：csxx601cjy (赞：0)

## 题解：[CF1982C Boring Day](https://www.luogu.com.cn/problem/CF1982C)
多日未写题解，掉咕，因此特前来水一篇。
### 题意
给定一个长度为 $n$ 的序列 $a$，你可以把这个序列划分成任意个不相交的子段，请问每个子段的和在 $l$ 到 $r$ 之间的子段数量的最大值是多少。
### 分析
一道码量很短的双指针题，如果你掌握了双指针，就会感觉很~~水~~简单。

首先介绍一下双指针：

> 双指针是一种常用的算法技巧，主要应用于数组、字符串或链表等数据结构的遍历与处理。双指针通过设置两个指针以不同的方式移动，巧妙地解决问题，常见形式包括快慢指针和左右指针。

其中，两个指针就相当于子段的两个端点，但是它们只会前进，不会后退，所以只需遍历一遍。复杂度从枚举端点的 $O(n^2)$ 降到了 $O(n)$。

具体做法见代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,l,r,a[100010];
void solve(){
	cin>>n>>l>>r;
	for(int i=0;i<n;i++)cin>>a[i];
	int i=0,j=-1,ans=0,sum=0;//i和j是两个指针
	while(i<n && j<n){//遍历
		if(l<=sum && sum<=r)ans++,i=j+1,sum=0;//符合要求，记录答案，准备找下一个答案
		if(sum<l)sum+=a[++j];//没到要求，j指针往右移，子段和增加
		if(sum>r)sum-=a[i++];//超过要求，i指针往右移，子段和减少
	}
	cout<<ans<<'\n';
}
int main(){
	cin>>T;
	while(T--)solve();
  //就不写return 0;
}
```

[我当然 AC 了。](https://codeforces.com/problemset/submission/1982/295766614)

---

## 作者：yangxikun (赞：0)

### 题目传送门

[洛谷](https://www.luogu.com.cn/problem/CF1982C) [CF](https://codeforces.com/problemset/problem/1982/C)

### 题目大意

多测。

现在有一摞卡，共 $n$ 张，第 $i$ 张卡上写了数字 $a_i$。

Egor 打算玩若干轮，直到没有卡为止。

每一轮，Egor 抽若干张连续的卡（不能为 0 张），然后计算这些卡上数字的总和。如果和在 $[l,r]$ 之间，这一轮就赢了，否则就输了。

### 解法

我们其实不用管输的情况，可以将其转换为“不取某张牌”。

循环每一张牌，期间如果当前总和超过 $r$，就删掉当前轮的第一张牌。为什么呢？因为题目中说了，要取连续的。如果和在范围内，那么就将和清零，答案加一，同时移动丢弃的牌的指针。

### 题外话

假设取了 2 张牌，和已经 $\ge l$ 了，再取一张牌，和也不会超过 $r$，那么要不要取呢？

答案是不要。这是一道贪心题，就算你留下来之后下一轮用不着，大不了丢掉；但是如果取了，答案就有可能发生变化。

### 代码

[CF 提交记录](https://codeforces.com/problemset/submission/1982/291900421)

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
int a[100005];
void solve(){
	int n,l,r,del=0,sum=0,ans=0;
	cin>>n>>l>>r;
	for(int i=0;i<n;i++)cin>>a[i];
	for(int i=0;i<n;i++){
		sum+=a[i];
		while(sum>r){
			sum-=a[del];
			del++;
		}
		if(sum>=l&&sum<=r){
			ans++;
			sum=0;
			del=i+1;//移动指针
		}
	}
	cout<<ans<<endl;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int t;
	cin>>t;
	while(t--)solve();
	return 0;
}
```

---

## 作者：_you_know_who_ (赞：0)

# 分析
首先从这道题的数据来看，肯定不能用 $O(n^2)$ 来做。那我们就要想办法用 $O(n)$ 来做。
那么我们可以设定一个左边界 from 和一个右边界 end，然后分步判断。

## 判断可以满足要求
如果满足要求，那么就把 from 设成 end 的下一个，这样下一次判断时，就可以把区间边界设为相同的值。

### code(1)
```cpp
if(dq>=l&&dq<=r)
{
    dq=0;
    from=end+1;
    ans++;
}
```

## 判断低于范围
如果低于范围，就把 end 的值增加 $1$，把下一个数放进序列里。

### code(2)
```cpp
if(dq<l)
{
    end++;
    dq+=a[end];
}
```

## 判断超过范围
如果超过范围，就把 from 的值增加 $1$，并从序列的末尾踢掉一个数。

### code(3)
```cpp
if(dq>r)
{
    dq-=a[from];
    from++;
}
```
你们要拷贝吗？还是放一下吧。

# code
```cpp
#include<bits/stdc++.h>//万能头棒棒哒
using namespace std;
int a[100001];
int ans;
int main()
{
	int t;
	scanf("%d",&t);
	for(int pp=1;pp<=t;pp++)
	{
		ans=0;
		int from=1,end=0;
		int dq=0;
		int n,l,r;
		scanf("%d%d%d",&n,&l,&r);
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
		}
		while(from<=n&&end<=n)//没超界
		{
			if(dq>=l&&dq<=r)//在范围内
			{
				dq=0;
				from=end+1;
				ans++;
			}
			if(dq<l)//太小了
			{
				end++;
				dq+=a[end];//放进来
			}
			if(dq>r)//太大了
			{
				dq-=a[from];//踢掉
				from++;
			}
		}
		cout<<ans<<endl;//最后输出结果
	}
	return 0;//不return的话在csp会0分的。
}
```

希望大家多多支持我！

---

