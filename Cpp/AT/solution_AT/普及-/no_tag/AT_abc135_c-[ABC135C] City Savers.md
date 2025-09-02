# [ABC135C] City Savers

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc135/tasks/abc135_c

$ N+1 $ 個の街があり、$ i $ 番目の街は $ A_i $ 体のモンスターに襲われています。

$ N $ 人の勇者が居て、$ i $ 番目の勇者は $ i $ 番目または $ i+1 $ 番目の街を襲っているモンスターを合計で $ B_i $ 体まで倒すことができます。

$ N $ 人の勇者がうまく協力することで、合計して最大で何体のモンスターを倒せるでしょうか。

## 说明/提示

### 制約

- 入力は全て整数である。
- $ 1\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ 10^9 $
- $ 1\ \leq\ B_i\ \leq\ 10^9 $

### Sample Explanation 1

以下のようにモンスターを倒すと、合計 $ 9 $ 体のモンスターを倒すことができ、このときが最大です。 - $ 1 $ 番目の勇者が $ 1 $ 番目の街を襲っているモンスターを $ 2 $ 体、$ 2 $ 番目の街を襲っているモンスターを $ 2 $ 体倒します。 - $ 2 $ 番目の勇者が $ 2 $ 番目の街を襲っているモンスターを $ 3 $ 体、$ 3 $ 番目の街を襲っているモンスターを $ 2 $ 体倒します。

## 样例 #1

### 输入

```
2
3 5 2
4 5```

### 输出

```
9```

## 样例 #2

### 输入

```
3
5 6 3 8
5 100 8```

### 输出

```
22```

## 样例 #3

### 输入

```
2
100 1 1
1 100```

### 输出

```
3```

# 题解

## 作者：LuffyLuo (赞：5)

山雨欲来风满楼，不开……见祖宗

以上为本人发离骚不过确实是本题的一个坑点。

#### 题目

题目的意思可以理解为若英雄序号为 $i$,那么他可以击打序号为 $i$ 与 $i+1$ 的怪兽。但双方皆两败俱伤，都会扣去自身的能量，所以请求出英雄们最多能打败多少怪兽。

刚看题目的翻译，我根本不知道后半段，~~这里恕我吐槽一下~~。

#### 分析

此题难度不大，用到了一点点贪心——英雄一定要先打序号与自己相同的怪兽，再打败序号为 $i+1$ 的怪兽。因为，如果英雄先打 $i+1$ 的怪兽，没打赢，但序号为 $i+1$ 的英雄可以碾压它，但却打不了比序号为 $i$ 的英雄还逊色的 $i$ 的怪兽，也就是说，我们能打败的怪兽能量就少了。

所以本题贪心很简单，英雄先打序号与自己相同的怪兽，再打败序号为 $i+1$ 的怪兽。

不过要看一下数据范围每个怪兽的能量为十亿，但是数量却是有十万，如果英雄可以打败他们，那么他们相乘会很打，所以数据类型要开大。

那么我们就可以愉快的做题。

#### 代码
```cpp
#include<bits/stdc++.h>
const int luogu=100010;
using namespace std;
int monster[luogu],hero[luogu];
int main(){
	int n,i,j;long long ans=0;//ans指的是怪兽的能量
	scanf("%d",&n);
	for(i=1;i<=n+1;i++)
		scanf("%d",&monster[i]);
	for(i=1;i<=n;i++)
		scanf("%d",&hero[i]);
	for(i=1;i<=n;i++){
		for(j=0;j<=1;j++){
			if(hero[i]>=monster[i+j]){//分情况讨论
				hero[i]-=monster[i+j];
				ans+=monster[i+j];
				monster[i+j]=0;
			}
			else{
				ans+=hero[i];
				monster[i+j]-=hero[i];
				hero[i]=0;
			}
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```
//不用说谢谢，不因客套，只因能见您的笑容，以及您电脑上的 AC，您已经回报。

//祝大家信息学越来越棒哦！

---

## 作者：liangbowen (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT4891)

小学生又双叒叕来写题解啦！

这题的翻译貌似不完整。

所谓怪兽与英雄的对决，就是**双方同时扣同样的血，直到一方为零**。

弄懂题后，你会发现，这题不是考贪心，而是模拟。

写一个函数用于模拟怪兽与英雄的对决。

再遍历所有英雄，对攻击范围内的怪物进行对决。

累加一下总伤害即可。


## 送上满分代码：


```cpp
#include <iostream>
#include <cstdio>
#define N 100005
using namespace std;
int a[N], b[N];
long long sum;
void PK(int &x, int &y)  //模拟怪兽与英雄的对决。 
//这里的取址符可以使参数改变。
//也就是说，不加取址符，若在函数中改变了参数的值，参数仍不变。
//而加了取址符就能改变参数的值。 
{
	int tx = x, ty = y;
	if (x > y) x -= ty, y = 0, sum += ty;	
	else if (x == y) x = 0, y = 0, sum += ty;
	else if (x < y) x = 0, y -= tx, sum += tx;
}
int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n+1; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= n; i++) scanf("%d", &b[i]);
	for (int i = 1; i <= n; i++)
	{
		PK(a[i], b[i]);
		PK(a[i+1], b[i]);
	}
	printf("%lld\n", sum);  //记得加上祖传换行。 
	return 0;
}
```


---

## 作者：_ZhouYuHan_ (赞：1)

### 思路
考虑两种情况：

+ 英雄打当前城镇的怪物

如果英雄数量比当前城镇怪物数量多，那么英雄数量减去当前城镇怪物数量，当前城镇怪物数量清空。

如果英雄数量比当前城镇怪物数量少，那么当前城镇怪物数量减去英雄数量，英雄数量清空。

+ 英雄打下一个城镇的怪物

同上

需要注意的是，应先打当前城镇的怪物，如果还有多再打下一个城镇的怪物，因为只有自己才能打到当前城镇的怪物。

AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long g[100002],y[100001],s;
int n;
int main() {
	cin>>n;
	for(int i=1; i<=n+1; i++)
		cin>>g[i];//读入怪物 
	for(int i=1; i<=n; i++)
		cin>>y[i];//读入英雄 
	for(int i=1; i<=n; i++) {
		if(y[i]>=g[i]) {//分2种情况考虑 
			y[i]-=g[i];
			s+=g[i];//计数器累加 
			g[i]=0;
			if(y[i]>=g[i+1]) {//也要分2种情况考虑 
				y[i]-=g[i+1];
				s+=g[i+1];//同上
				g[i+1]=0;
			} else {
				g[i+1]-=y[i];
				s+=y[i];//同上
				y[i]=0;
			}
		} else {
			g[i]-=y[i];
			s+=y[i];//同上
			y[i]=0;
		}
	}
	cout<<s;
	return 0;
}
```


---

## 作者：Starw (赞：0)

~~题目名中文翻译：奥特曼打怪兽。~~

### 题目大意：

有 $n$ 个英雄和 $n+1$ 个城市，第 $i$ 个城市有 $A_i$ **个**怪兽袭击，第$i$ 个英雄可以攻击 $B_i$ 个怪兽,但只能攻击 $i$ 和 $i+1$ 城市的怪兽。

### 思路：

模拟即可，对于每个英雄，可以分为以下三种情况：

1. 太弱了，自己所在的城市的怪兽还打不完；

2. 一般般，可以打完自己所在的城市的怪兽，或许还可以帮下一个城市打一部分怪兽；

3. 很厉害，可以打完自己所在的城市和下一个城市的怪兽。

按上面三种情况写个分支结构即可模拟。

### 代码：

```cpp
#include<bits/stdc++.h>//万能头 
#define re register int
using namespace std;
int m[100005];
int main(){
	int n,h;
	long long ans=0;//要开long long
	scanf("%d",&n);
	for(re i=1;i<=n+1;i++)
		scanf("%d",&m[i]);
	for(re i=1;i<=n;i++){
		scanf("%d",&h);
		if(h<m[i]){//连自己所在的城市的怪兽还打不完
			m[i]-=h;
			ans+=h;
			h=0;
		}else{//可以打完自己所在的城市的怪兽
			h-=m[i];
			ans+=m[i];
			m[i]=0;
		}
		if(h>0)//若还能打 
			if(h<m[i+1]){//帮下一个城市打一部分怪兽 
				m[i+1]-=h;
				ans+=h;
				h=0;
			}else{//可以直接打完下一个城市的怪兽
				h-=m[i+1];
				ans+=m[i+1];
				m[i+1]=0;
			}
	}
	printf("%lld\n",ans);//AT不换行 爆零泪两行 
	return 0;//好习惯 
}
```


---

## 作者：shAdomOvO (赞：0)

# 题解

其实，我这道题写了很久，但是并不是不会，而是被题面卡住了。

说实话，我觉得这个题面有点差错，下面是我根据自己的理解重新写的题面。

## 题面

总共有 $ N+1 $ 个城镇，每个城镇都被一定数量的怪兽攻击，有 $ N $ 个英雄。

每个英雄可以攻击到自己对应的 $ N_i $ 和 $ N_{i+1} $ 城镇中的怪兽。

问最多可以击败多少个怪兽。

输入共三行，第一行一个数 $ N $，表示英雄的数量。

第二行 $ N+1 $ 个数，分别为 $ A_1,A_2,A_3 \cdots A_{n+1}  $ 表示每个城镇有多少个怪物袭击。

第三行有 $ N $ 个数，分别是 $ B_1,B_2\cdots B_n $，表示第 $ i $ 个英雄可以击败几个怪兽。

输出一个数，最多可以击败多少怪兽。

## 思路

这题的正解应该是 $O(n)$ 算法，~~因为我就是最优解~~ ，因为每个英雄只能攻击自己这个城镇和下一个城镇，所以，很容易就可以想到贪心。

因为如果按顺序扫，自己先打别人的，就没有人打自己的了。

### 证明 
设两个城镇的英雄可以打败的怪兽数量分别是 $\texttt x$ 和 $\texttt y $，若可以打完自己的，显然继续去打别人的是一定最优的~~总不能待着看戏吧~~。

若 $\texttt x $ 先打别人的，并且自己还不能够将自己的打完。

将别人的打完了，那等到 $\texttt y $ 时，$\texttt y $只能打下一个人的怪兽了。

显然，若 $\texttt y $ 足够大，将会剩下许多，而 $\texttt x$ 那边又没打完。这样就会浪费很多。

这里需要注意有一些坑点需要打 `long long` ，数据最大可以到 $ 10^{14} $ 会爆 `int` 。

## 代码（请勿抄袭）
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,i,j,a[100010],b[100010],ans,here;
int main(){
	ios::sync_with_stdio(false);//读入优化
	cin>>n;
	for(i=1;i<=n+1;i++)cin>>a[i];//每个城镇的怪兽数量 
	for(i=1;i<=n;i++)cin>>b[i];//每个城镇怪物的数量
	for(i=1;i<=n;i++){//循环英雄
		if(a[i]<=0)goto here;//怪兽已为 0 直接打下一个城镇的怪兽 
		if(b[i]>a[i]){//英雄多一些
			b[i]-=a[i];
			ans+=a[i];
			here: 
			ans+=min(a[i+1],b[i]);//若a[i+1]<b[i] 说明能全部击败显然答案架上怪兽数量 
			//若a[i+1]>b[i] 说明不能全部击败，答案加上英雄可以打败的数量 
			a[i+1]-=b[i];
		}
		else ans+=b[i];
	} 
	cout<<ans;
}
```


---

## 作者：zjr027 (赞：0)

思路

因为第 $ i $ 英雄只能打第 $ i $ 个和 $ i + 1 $ 个城镇的怪物，

而且问最多能打败多少怪物。

所以我就用了一个贪心的方法来做。

也就是循环每一个英雄，

然后看对应的第 $ i $ 个城镇和第 $ i + 1 $ 个城镇，

让这个英雄能打败多少怪物就打多少。

注意：

+ 数据要开 long long。
+ 循环第 $ i $ 个英雄时，要把第 $ i $ 个和 $ i + 1 $ & 个城镇都考虑进去。

时间复杂度： $ O(n) $ 

不会超时。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
long long a[100005], b[100005];
int main(){
	long long n, ans = 0; // 英雄总数和能打败的怪物总数
	cin >> n; // 输入
	for(long long i = 1;i <= n + 1;i++){
		cin >> a[i];
	} 
	for(long long i = 1;i <= n;i++){
		cin >> b[i];
	}
	for(long long i = 1;i <= n;i++){ // 循环每一个英雄
		if(b[i] >= a[i]){ // 能清空第 i 个城镇的怪物
			ans += a[i]; 
			b[i] -= a[i];
			a[i] -= a[i];
			if(b[i] >= a[i + 1]){ // 还能清空第 i 个城镇的怪物
				ans += a[i + 1];
				b[i] -= a[i + 1];
				a[i + 1] -= a[i + 1];
			}
			else{ // 能清空第 i + 1 个城镇的怪物，就清理多少
				ans += b[i]; 
				a[i + 1] -= b[i];
				b[i] -= b[i];
			}
		}
		else{ // 能清空第 i 个城镇的怪物，就清理多少
			ans += b[i];
			a[i] -= b[i];
			b[i] -= b[i];
		}
	}
	cout << ans << endl; 
	return 0;
}
```



---

## 作者：Gmt丶FFF (赞：0)

# 看着还没有人发题解，赶快自己发一篇

这题主要是一种思维，不是正着去加，而是倒过来减，具体看代码注释。

```
#include<iostream>
#define ll long long //初始化
using namespace std;
int main()
{
	ll n,guai[100001],ying[100000],k=0;
	cin>>n;
	for(int i=0;i<=n;i++)
	{
		cin>>guai[i];
	}	
	for(int i=0;i<n;i++)
	{
		cin>>ying[i];
	}
    //前面的都是输入。
	for(int i=n;i>0;i--)//倒着看
	{
		if(ying[i-1]>=guai[i])//如果可以全部干掉
		{
			ying[i-1]-=guai[i];
			k+=guai[i];
			guai[i]=0; //计数，英雄减去实力，怪物初始为0
			if(ying[i-1]>=guai[i-1])//如果还可以再打一坡。
			{
				ying[i-1]-=guai[i-1];
				k+=guai[i-1];
				guai[i-1]=0;//跟上面操作一样
				continue;//注意：必须加continue，否则可能会进入else
			}
			else 
			{
				guai[i-1]-=ying[i-1];
				k+=ying[i-1];//怪物数量变少，击败怪物数量都是英雄剩下的实力
				continue;//同上
			}
		}
		else
		{
			k+=ying[i-1];
			guai[i]-=ying[i-1];//击败怪物数
		}
	}
	cout<<k<<endl;
	return 0;
} 
```
整个代码复杂性不高，可是这题还有坑。不开long long就十分地惨。

# ~~AT不加endl，WA两行泪~~


---

