# 「KDOI-06-J」ION 比赛

## 题目描述

在 ION 比赛中，总共有 $n$ 道题目。每道题目的满分均为 $100$ 分。

第 $i$ 道题有 $a_i$ 个测试点，且该题的所有测试点分值相等，因此 $a_i$ 一定是 $100$ 的因数。每通过一个测试点，你将会得到与该测试点分值相等的分数。

通过一些技术手段，你了解到 ION 比赛今年的 Au 分数线是 $t$ 分。

现在，你在第 $i$ 道题中已经通过了 $b_i$ 个测试点。作为一名策略选手，你想知道：对于任意 $1\le j\le n$，如果你在比赛剩下的时间内死磕第 $j$ 题（不做其他题目），需要至少再多通过几个测试点以获得 Au，也就是说，使你的总分 $\ge t$。

当然，你有可能无法通过死磕某一道题目翻盘（获得 Au），此时你需要输出 `NaN`。

## 说明/提示

**【样例解释 #1】**

容易发现目前的分数是 $100+100+92+40+70+44=446$，而分数线为 $447$，故在任何一道没有拿到满分的题中多通过一个测试点即可。

**【数据范围】**

对于所有数据保证：$1\leq n\leq 7$，$0\leq b_i\leq a_i$，$1\leq a_i\leq 100$ 且 $a_i$ 为 $100$ 的因数，$0\leq t\leq 100n$。

| 测试点编号 | $n$ | $a_i$ | 特殊性质 |
| :----------: | :----------: | :----------: | :----------: |
| $1$ | $\leq7$ | $\leq100$ | 保证目前分数大于等于 $t$ |
| $2\sim3$ | $=1$ | $\leq100$ | 无 |
| $4\sim5$ | $\leq7$ | $=100$ | 无 |
| $6\sim10$ | $\leq7$ | $\leq100$ | 无 |

## 样例 #1

### 输入

```
7
100 100
20 20
25 23
25 10
20 14
25 11
20 0
447```

### 输出

```
NaN
NaN
1
1
1
1
1```

## 样例 #2

### 输入

```
7
100 100
20 20
25 23
25 10
20 14
25 11
20 0
446```

### 输出

```
Already Au.```

## 样例 #3

### 输入

```
7
100 100
20 20
20 10
25 13
20 20
25 16
20 6
509```

### 输出

```
NaN
NaN
3
4
NaN
4
3```

## 样例 #4

### 输入

```
7
100 100
20 19
20 20
25 11
20 20
25 25
20 6
509```

### 输出

```
Already Au.```

# 题解

## 作者：zyn_ (赞：17)

# P9740 「KDOI-06-J」ION 比赛

## 题目大意

比赛有 $n$ 题，第 $i$ 题满分 $100$，共有 $a_i$ 个测试点，你已经做出 $b_i$ 个测试点。这次比赛的 Au 线是 $t$ 分。你决定死磕一道题目，问对于第 $i$ 题，至少再做出多少个测试点，你才能达到 Au 线。

如果现在的分数已经达到 Au 线，输出 `Already Au.`。如果在一道题上，再怎么死磕都不可能达到 Au 线，输出 `NaN`。

$n\le 7,a_i\le 100$。

## 题目分析

如此小的数据范围，直接模拟即可，绝不会 TLE。

首先计算出已得到的分数 $sum$，如果 $\ge t$ 直接 `Already Au.`。

否则，还需得 $t-sum$ 分。

对第 $i$ 题，从 $1$ 到 $a_i-b_i$ 枚举多做出的测试点的数量，发现达到 Au 线就输出。如果直到 AC 第 $i$ 题，都不能达到 Au 线，那么第 $i$ 行就输出 `NaN`。

然后就做完了。

## AC code:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 10
int n,a[N],b[N],t,sum,p,cnt;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i)scanf("%d%d",&a[i],&b[i]),sum+=(100/a[i]*b[i]);
	scanf("%d",&t);if(sum>=t){puts("Already Au.");return 0;}
	for(int i=1;i<=n;++i){
		p=sum;cnt=0;
		while(p<t&&b[i]+cnt<=a[i])++cnt,p+=(100/a[i]);
		//每多过一个点，增加100/a[i]分。cnt是多过的测试点数量
		if(b[i]+cnt==a[i]+1)puts("NaN");
		//上面的循环在b[i]+cnt>a[i]时退出
		//说明在b[i]+cnt==a[i]，即AC第i题时，仍未达到Au线
		else printf("%d\n",cnt);
	}
	return 0;
}
```

## 彩蛋

比赛开始一分钟时，我瞄着本题的样例看。突然感觉……

[小粉兔NOI2020游记](https://www.cnblogs.com/PinkRabbit/p/NOI2020.html)

没错，样例 $1$ 就是小粉兔在 NOI2020 中的成绩！（所以这题叫 ION 比赛啊）

还有，样例 $3,4$ 中的 Au 线 $509$，就是 NOI2023 的 Au 线。

$n\le 7$，自然是对应 NOI 比赛中的笔试，第一天三题，和第二天三题。

## 后记

我看到有一些选手在算「还需多少测试点才能达到 Au 线」时使用数学方法，结果不慎写错，挂分。

**在数据范围小时，使用简单的模拟，避免挂分，才是最重要的**。

---

## 作者：abc1856896 (赞：16)

# **题目大意**
# 「KDOI-06-J」ION 比赛
在 ION 比赛中，总共有 $n$ 道题目。每道题目的满分均为 $100$ 分。

第 $i$ 道题有 $a_i$ 个测试点，且该题的所有测试点分值相等，因此 $a_i$ 一定是 $100$ 的因数。每通过一个测试点，你将会得到与该测试点分值相等的分数。

通过一些技术手段，你了解到 ION 比赛今年的 Au 分数线是 $t$ 分。

现在，你在第 $i$ 道题中已经通过了 $b_i$ 个测试点。作为一名策略选手，你想知道：对于任意 $1\le j\le n$，如果你在比赛剩下的时间内死磕第 $j$ 题（不做其他题目），需要至少再多通过几个测试点以获得 Au，也就是说，使你的总分 $\ge t$。

当然，你有可能无法通过死磕某一道题目翻盘（获得 Au），此时你需要输出 `NaN`。

# **大体思路**
1. 按题意算出总分
2. 如果已经过了分数线，输出，结束程序
3. 否则开始循环，如果这道题已经全部对了，输出
4. 否则，判断可不可以过分数线，输出

# **程序**
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,score,a[105],w[105],sum;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i]>>w[i];
		sum=sum+(100/a[i]*w[i]);
	}
	cin>>score; 
	if(sum>=score) {
		cout<<"Already Au.";
		return 0;	
	}
	for(int i=1;i<=n;i++){
		if(a[i]==w[i]) cout<<"NaN"<<endl;
		else{
			int cha=score-sum,sheng=a[i]-w[i],mei=100/a[i]; 
			if((sheng*mei)<cha) cout<<"NaN"<<endl;
			else {
				if(cha%mei==0) cout<<cha/mei<<endl;
				else cout<<cha/mei+1<<endl;
			}		
		}
	}
	return 0;
}
```


---

## 作者：User_Artist (赞：8)

# 「KDOI-06-J」ION 比赛

## 审题

 题面传送门 [P9740「KDOI-06-J」ION 比赛](https://www.luogu.com.cn/problem/P9740)。

 概括：有 $n$ 道题，其中第 $i$ 道题（$1 \le i \le n$）共 $a_i$ 个测试点，通过了 $b_i$ 个测试点。在知道今年 Au 分数线 $t$ 的前提下，希望知道：
 
 - 仅对于每一道题而言，当前分数再多通过多少测试点才能达到 Au 线 $t$。
 
------------

 那么，方法**很简单**：

1. 因为 $1 \le i \le n$ 的每个 $a_i$ 为 $100$ 的因数，所以可以直接计算测试点 $i$ 分数为 $100\times \frac{b_i}{a_i} $，从而得到已得总分 $score$。如果达到 Au 线即 $score \ge t$ 就直接 `puts("Already Au.")`。注意：输出有一个 `.` 不要漏了。
```
	for(int i = 0; i < n; ++ i) sc += 100 / a[i] * b[i];
	if(sc >= t) {
		puts("Already Au.");
		return 0;
	}
```
2. 对于 $1 \le i \le n$ 的第 $i$ 题的未通过测试点数量即 $a_i - b_i$，如果剩余数量总分值不足以达到 Au 线，直接 `puts("NaN")`。
```
	for(int i = 0; i < n; ++ i)
		if(100 / a[i] * (a[i] - b[i]) < t - sc) {
			puts("NaN");
			continue;
		}
``` 
3. 如果剩余数量总分值足以达到 Au 线，就计算所差的分值 $t - score$，从而得到还要通过多少测试点。
```
	printf("%d\n", (t - sc - 1) / (100 / a[i]) + 1);
``` 

4. 经过分析，复杂度为 $\operatorname{O}(n)$，可行。

------------

### 完整代码

```cpp
#include <cstdio>
int n, t, sc, a[10], b[10];
int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; ++ i) scanf("%d %d", a + i, b + i), sc += 100 / a[i] * b[i];
	scanf("%d", &t);
	if(sc >= t) puts("Already Au.");//达到 Au 线
	else for(int i = 0; i < n; ++ i)
		if(100 / a[i] * (a[i] - b[i]) < t - sc) puts("NaN");//只靠本题无法翻盘
		else printf("%d\n", (t - sc - 1) / (100 / a[i]) + 1);
}
```
------------

### 完结撒花
 欢迎提出疑惑和进行题目上的交流！

---

## 作者：Pink_Cut_Tree (赞：3)

# P9740 「KDOI-06-J」ION 比赛 题解

大水题。

### 解析

我们要进行如下的几步：

1. 判断这个人是否满分了，如果是的，则输出 `Already Au.`，记得输出那个点！

1. 计算出这个人还差多少分，然后逐一判断每一道题 A 掉之后可以不可以拿金即可。

### 代码

```cpp
#include<iostream>
using namespace std;
int n;
int a[10],b[10];
int t;
int point;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i]>>b[i];
		point+=100/a[i]*b[i];
	}
	cin>>t;
	if(point>=t){
		cout<<"Already Au."; return 0;
	}
	int need=t-point; //还差多少分 
	for(int i=1;i<=n;i++){
		int pt=100/a[i]; //每一个测试点的分数 
		int n_gain=100-100/a[i]*b[i]; //没有拿到的分数 
		if(need>n_gain){
			cout<<"NaN\n"; continue;
		}
		if(need%pt==0){
			cout<<need/pt<<"\n";
		}
		else{
			cout<<need/pt+1<<"\n";
		}
	}
return 0;
}
```


---

## 作者：sfqxx1 (赞：2)

这是一篇 python 题解。

## 题意

[题目传送门。](https://www.luogu.com.cn/problem/P9740)


## 思路

一个简单的数学问题。

我们可以通过计算每个题目的剩余测试点和每个测试点的分数来解决。

首先，我们需要计算当前的总分数，然后判断是否已经达到 Au 分数线。如果已经达到，直接输出  `Already Au`。

如果没有达到，我们需要计算每个题目还需要通过多少个测试点才能达到 Au 分数线。这可以通过计算每个题目的剩余测试点和每个测试点的分数来实现。如果某个题目的剩余测试点不足以达到 Au 分数线，输出 `NaN`。

## 代码

```
n = int(input())
problems = []
for _ in range(n):
    problems.append(list(map(int, input().split())))
t = int(input())
#当前总分数
score = 0
for a, b in problems:
    score += b * (100 // a)
if score >= t:#如果已经到达了 Au 分数线
    print("Already Au.")
else:
    for a, b in problems:
    	  #每个测试点的分数
        ok = 100 // a
        #还需要多少测试点
        score2 = (t - score) / ok
        if score2 > a - b:#如果需要的测试点数大于剩余的测试点数
            print("NaN")
        else:
            print(int(-(-score2 // 1)))
```

---

## 作者：lbh666 (赞：2)

题目意思十分简单，请读者自行完成阅读。

## 思路分析

- 开一个变量 $sum$，用来记录死磕前的总分，每道题目的分数怎么计算呢？用 `sum+=100/a[i]*b[i];`，解释一下，`100/a[i]` 算的是每个测试点的分数，再乘上 `b[i]`，也就是通过的分数了。

- 判断一下 $sum$ 是否大等于分数线，如果是，输出 `Already Au.` 即可。

- 如果不是，就遍历每一道题目，如果 $sum$ 加上这道题剩余的分数还不能过线，就输出 `NaN`，否则就计算要用几个测试点的分数才能过线，统计后输出即可。

- 别忘了每次输出要换行。

## AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;

int n,sum=0,t;
int a[15],b[15];

int main(){
	cin>>n;
	for(int i=1;i<=n;++i){
		cin>>a[i]>>b[i];
		sum+=100/a[i]*b[i]; //计算总分 
	}
	cin>>t; 
	if(sum>=t){
		cout<<"Already Au."; //过线直接输出 
		return 0;
	}
	for(int i=1;i<=n;++i){
		int cnt=a[i]-b[i],tot=100/a[i];
		//cnt*tot代表这道题还能加的分数 
		//如果加上剩余的分数能过线，计算需要的测试点数（向上取整） 
		if(sum+(cnt*tot)>=t)cout<<ceil((t-sum)*1.0/tot)<<"\n";
		else cout<<"NaN\n";//否则输出NaN 
	}
	return 0;
}
```

---

## 作者：Juskko (赞：1)

## [题目](https://www.luogu.com.cn/problem/P9740)

## 思路：
先计算总分数 $sum$，$c_i=\frac{100}{a_i}$ 为每道题的每个测试点分数。

1. 如果总分数达到 $Au$ 线，直接输出 `Already Au.` 。

2. 否则计算到达 $Au$ 线还需多少分 $p$，遍历所有题，求出每道题的失分，如果失分大于等于 $p$，则输出$\lceil\frac{p}{c_i}\rceil$，即至少再多通过几个测试点。否则输出 `NaN`。


## Code:
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, t, a[10], b[10], c[10];
int sum = 0;
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i] >> b[i];
		c[i] = 100 / a[i];
		sum += c[i] * b[i];
	}
	cin >> t;
	if (sum >= t) {
		cout << "Already Au." << endl;
	} else {
		double p = t - sum;
		for (int i = 1; i <= n; i++) {
			double l = 100 - c[i] * b[i];
			if (l >= p) {
				cout << ceil(p / c[i]) << endl;
			} else {
				cout << "NaN" << endl;
			}
		}
	}
	return 0;
}
```


---

## 作者：liuruizhe1 (赞：1)

## 题目大意
有 $n$ 道题，每道题满分是 $100$ 分，每道题有 $a_i$ 个测试点，已经做对 $b_i$ 个测试点，已知 $Au$ 分数线为 $t$，问如果死磕一道题，至少再做对几个测试点就能 $Au$，如果分数本身就过了，不用死磕，输出 ```Already Au.```，死磕第 $i$ 题过不了，输出 ```NaN```。
## 思路
先求出一道题每个测试点的分数，看看做对第 $i$ 题全部测试点的分数是否大于等于 $t$ ，是就输出 $t-sum$ 除第 $i$ 题每个测试点分数（要向上取整），否就输出 ```NaN```。
## 代码
```
#include<bits/stdc++.h>
using namespace std;
int n,m,a[10],b[10];
int c[10],sum;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i]>>b[i];
		c[i]=100/a[i];
		sum+=c[i]*b[i];
	}
	cin>>m;
	if(sum>=m){
		cout<<"Already Au.";
		return 0;
	}
	for(int i=1;i<=n;i++){
		if(sum-b[i]*c[i]+a[i]*c[i]>=m){
			cout<<(m-sum+c[i]-1)/c[i]<<"\n";
		}
		else {
			cout<<"NaN\n";
		}
	}
	return 0;
}
```

---

## 作者：flangeborg (赞：1)

#### [题目传送门](https://www.luogu.com.cn/problem/P9740)

### 题目大意
一场比赛，有 $n$ 个题目，对于第 $i$ 个题目，有 $a_i$ 个测试点，当前你已经通过了 $b_i$ 个点，每一道题的总分都为 100 分。设该比赛的分数线为 $t$ 分。

- 如果你当前所得到的总分已经超过了分数线，则输出 ``Already Au.``
- 如果没有达到分数线，你可以选择一道题并且把它 AC，如果你的总分仍未达到 $t$，则输出 ``NaN``。否则，输出你最少需要通过测试点的数量，使得你的总分达到 $t$。

### 解题思路

不难看出，这是一道纯模拟题。先判断出当前总分是否能够超过 $t$。如果没有，我们可以先预处理出每一道题的单个测试点的得分。随即开始枚举每一道题，判断如果 AC 该题能否达到分数线。再根据题目的意思输出出答案即可。

### Code

```cpp
#include<iostream>
using namespace std;
int n,a[15],b[15],c[15],d[15],temp,t;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin >> n;
	for(int i = 1; i <= n; i++)
		cin >> a[i] >> b[i],c[i] = 100 / a[i],d[i] = a[i] - b[i];
	// c[i] 预处理每一道题每个测试点的分数 ，d[i] 是还没有通过的测试点的数量 
	cin >> t;
	for(int i = 1; i <= n; i++)
		temp += c[i] * b[i];
	// 计算总分 
	if(temp >= t)
	{
		cout << "Already Au.";
		return 0;
	}
	int need = t - temp;
	// 还需要的分数数量 
	for(int i = 1; i <= n; i++)
	{
		if(d[i] * c[i] < need) cout << "NaN" << endl; // AC 也无法达到分数线 
		else // AC 能达到分数线 
		{
			int cnt = need / c[i]; // 算出最少所需的测试点数量 
			// c++ 中除法是向下取整的，需要注意 
			if(need % c[i] != 0) cnt++; // 如果不整除，答案需 +1 再输出 
			cout << cnt << endl;
		}
	}
	return 0;
	
}
```


---

## 作者：Harrison_000 (赞：1)

[原题位置](https://www.luogu.com.cn/problem/P9740)

这道题给了我们每道题测试点的数量 $a_i$ 和每道题的得分 $100$，那么我们可以算出每个测试点的分值，又因为输入中给了我们一定能通过的每道题的测试点个数，所以我们能得到一定能得到的分数。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,t,a[10],b[10],f[10],sum; //sum是一定能得到的分数。
signed main(){
	cin >>n;
	for(int i=1;i<=n;i++){
		cin >>a[i] >>b[i];
		f[i]=100/a[i];
		sum+=f[i]*b[i];
	}
	cin >>t;
	if(sum>=t){ //如果一定能得到的分数已经超过了Au线，直接结束程序。
		cout <<"Already Au.";
		return 0;
	}
	bool sk=false;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=a[i]-b[i];j++){
			if(sum+j*f[i]>=t){ //死磕得到的分数+一定能得到的分数大于分数线，死磕就可以获得Au。
				cout <<j <<endl;
				sk=true;
				break;
			}
		}
		if(sk==false){ //把这道题的分拿满都无法获得Au。
			cout <<"NaN" <<endl;
		}
		sk=false;
	}
	return 0;
}
```

---

## 作者：_colin1112_ (赞：1)

## 思路

首先计算出已经获得的分数，判断是否已经到达获奖分数，如果已经到达了，则输出 `Already Au.`，结束程序。

如果没有到达，则依次判断这一道题余下错误的测试点作对后是否可以到达获奖分数，如果不可以，则输出 `NaN`，跳过当前循环；如果可以，就输出至少要再通过多少个测试点才可以获得 Au。

## AC Code

```cpp
#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;
const int E=1e6+5;
ll t,sum,len;
struct wjh{
	ll a,b;
}arr[E];
int main(){
	cin >>t;
	for(int i=1;i<=t;i++)cin >>arr[i].a>>arr[i].b;
	cin >>len;
	for(int i=1;i<=t;i++)sum+=(100/arr[i].a*arr[i].b);
	if(sum>=len){//已经到达分数线
		cout <<"Already Au.";
		exit(0);//同 return 0
	}
	for(int i=1;i<=t;i++){
		ll tmp=100/arr[i].a;
		if(sum+tmp*(arr[i].a-arr[i].b)<len)cout <<"NaN\n";//无解情况
		else{
			cout <<ceil((len-sum)*1.0/tmp)<<endl;//计算至少要再通过多少个测试点才可以获得 Au
		}
	}
	return 0;

```

---

## 作者：Gan_Zhezhi (赞：0)

# [P9740 「KDOI-06-J」ION 比赛](https://www.luogu.com.cn/problem/P9740)

#### 思路

- 每次输入记录拿到的分数，如果大于分数线直接输出。

- 否则循环判断每道题还差几个测试点。

#### 注意

- 分别计算每道题的答案的时候记得向上取整。

---

## AC Code

~~~cpp
#include<iostream>
using namespace std;
const int N=10;
int n,sum,t,a[N],b[N];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i]>>b[i];
		sum+=100/a[i]*b[i];
	}
	cin>>t;
	if(sum>=t){
		cout<<"Already Au.";
        //超过分数线直接输出。
		return 0;
	}
	for(int i=1;i<=n;i++){
		if((a[i]-b[i])*(100/a[i])+sum<t){
			cout<<"NaN\n";
		}
        //下面是向上取整操作，如果通过几个测试点后正好Au直接输出测试点数，否则除完加一。
		else if((t-sum)%(100/a[i])){
			cout<<(t-sum)/(100/a[i])+1<<"\n";
		}
		else{
			cout<<(t-sum)/(100/a[i])<<"\n";
		}
	}
	return 0;
}
~~~

---

## 作者：Xdwjs (赞：0)

$a_i$ 是测试点数量，$b_i$ 是已通过的测试点数量，一个测试点的分数即为 $100\div a_i$，一道题目所获得的分数即为 $100\div a_i \times b_i$。设 $cnt$ 为总分，也就是所有题目所得分数之和，即 $\sum_{i=1}^{n}{100 \div a_i \times b_i}$。

“分数已经达到 Au 线”：即 $cnt\le t$。

“至少再通过多少个测试点才可以获得 Au”：现在分数与 Au 线的相差分数，除以这道题每个测试点的分数。注意要向上取整。即 $\lceil (t-cnt)\div(100\div a_i)\rceil$。

“无法通过这题翻盘（获得 Au）”：现在的分数加上这题挂掉的所有分也达不到 Au 线，即 $(a_i-b_i)\times(100\div a_i)+cnt<t$。

Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n,t;
    cin>>n;
    int a[15],b[15];
    int cnt=0;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i]>>b[i];
        cnt+=100/a[i]*b[i];
    }
    cin>>t;
    if(cnt>=t)
    {
        cout<<"Already Au.";
        return 0;
    }
    for(int i=1;i<=n;i++)
    {
        if((a[i]-b[i])*(100/a[i])+cnt<t) cout<<"NaN"<<endl;
        else cout<<ceil((t-cnt)*1.0/(100/a[i]))<<endl;
    }
    //system("pause");
    return 0;
}
```

---

