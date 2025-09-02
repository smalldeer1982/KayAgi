# Settlement of Guinea Pigs

## 题目描述

Dasha loves guinea pigs very much. In this regard, she decided to settle as many guinea pigs at home as possible and developed a plan for the next $ n $ days. Every day, she will either buy a new guinea pig or call a doctor to examine all her pets.

Unfortunately, the store where she was going to buy guinea pigs does not understand them. Therefore, it cannot determine their gender. Dasha can't do it either. The only one who can help is a doctor.

To keep guinea pigs, aviaries are needed. Dasha plans to buy them in the same store. Unfortunately, only one species is sold there — a double aviary. No more than two guinea pigs can live in it.

Since Dasha does not want to cause moral injury to her pets — she will not settle two guinea pigs of different genders in one aviary.

Help Dasha calculate how many aviaries in the worst case you need to buy so that you can be sure that at no moment of time do two guinea pigs of different genders live in the same aviary.

As part of this task, we believe that guinea pigs have only two genders — male and female.

## 说明/提示

In the first set of input data, Dasha needs to put each guinea pig in a separate enclosure, since she does not know their gender.

In the second set of input data, Dasha will buy $ 0 $ guinea pigs, which means she will need $ 0 $ aviaries.

In the third set of input data, you even need $ 3 $ aviaries to put each guinea pig in a separate aviary before the doctor arrives at the $ 4 $ th day. When she finds out their gender, at least two guinea pigs will be of the same gender and they can be placed in one aviary, and the third in another aviary. Thus, she will have one free aviary in which she can settle a new guinea pig. So answer is $ 3 $ .

In the fourth set of input data, we show that $ 4 $ is the optimal answer.

To begin with, we note that the first four guinea pigs can be placed one at a time in an aviary. Then a doctor will come and determine their gender. Among these four guinea pigs there will be at least one pair of the same gender, because: either male guinea pigs are at least $ 2 $ , or they are not more than $ 1 $ , which means that the female is at least $ 3 $ . Now we can put this couple in one aviary, and the other two in separate ones. We will have one more empty aviary where we can put a new pig.

Now let's show that the answer is at least $ 4 $ . Let's say that among the first $ 4 $ guinea pigs, $ 3 $ are female and $ 1 $ is male. We need at least $ 3 $ aviaries to settle them. Then, when we buy a new guinea pig, we will need another aviary in which we will put it, since we do not know its gender.

## 样例 #1

### 输入

```
6
3
1 1 1
3
2 2 2
5
1 1 1 2 1
10
1 2 1 2 1 2 1 2 1 2
20
1 2 1 1 1 1 1 2 1 2 1 2 2 1 1 1 1 1 1 1
20
2 1 1 2 1 1 2 1 2 2 1 1 1 2 2 1 1 1 1 2```

### 输出

```
3
0
3
4
12
9```

# 题解

## 作者：zhangzihou (赞：4)

题意：已知 $x$ 只豚鼠的性别，有 $y$ 只豚鼠的性别未知，求至少需要用多少个笼子来关这些豚鼠（每个笼子只能放性别相同的豚鼠）。

设已知 $cnt1$ 只豚鼠的性别，有 $cnt2$ 只豚鼠的性别未知。

最坏情况下需要 $cnt2+\lfloor \frac{2}{cnt1}\rfloor+1$ 个笼子。记为 $calc(cnt1,cnt2)$ 

  $calc$ 函数如下：
 
 ```
 int calc(int cnt1,int cnt2){
	int ret=0;
	if(cnt2<=1)  return cnt1+cnt2;
	ret=cnt1+cnt2/2+1;
	return ret;
}
```
 $cnt1$ 和 $cnt2$ 在计算时维护，每次维护更新一下答案。
 
 代码：
 ```
#include<bits/stdc++.h>
using namespace std;
#define ms(x,y) memset(x,y,sizeof(x))
#define ll long long
const int M=114514;
const int N=1e5+10;
int a[N];
int calc(int cnt1,int cnt2){
	int ret=0;
	if(cnt2<=1)  return cnt1+cnt2;
	ret=cnt1+cnt2/2+1;
	return ret;
}
int main()
{
	int t;
	scanf("%d",&t);
	while(t--){
		int n;
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
		}
		int cnt1=0,cnt2=0,ans=0;
		for(int i=1;i<=n;i++){
			if(a[i]==1){
				cnt1++;
			}
			else{
				cnt2=cnt2+cnt1;
				cnt1=0;
			}
			ans=max(ans,calc(cnt1,cnt2));
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：Walrus (赞：2)

## 题意
感觉这个题目翻译有点问题，缺少了一些关键点，这里我重新阐述一下题意。有 $t$ 组测试数据，对于每组测试数据有 $n$ 次操作，分别记录于 $b$ 数组中，其中若 $b_i=1$，则代表购买一只豚鼠，若 $b_i=2$，则代表鉴定一只豚鼠的性别，你需要把这些豚鼠放在一些笼子里，有几个约束条件，问你**最坏情况下需要多少个笼子**。条件如下；

- 每个笼子最多可以放两只豚鼠。
- 每个笼子里只能存在一种性别的豚鼠（即同为公或者同为母）。
- 你不能将两只同种性别的豚鼠放两个笼子里。（要是可以那答案不就是 $b$ 数组中 $2$ 的数量）。

## 分析
不难发现，当你啥也不知道时，你肯定要给所有豚鼠都买个笼子。贪心来想，你想要答案最大，那么就要考虑最坏情况，也就是一个笼子最好放一只豚鼠，但是同性的必须放一起，我们可以一边遍历 $b$ 数组一边统计答案，当你遍历到 $b_i=2$ 时，又贪心想，如果有偶数只豚鼠，那显然没辙，只能对半分性别，但是如果有奇数只，那就可以把以前偶数只豚鼠对半分，新来的单独开一个笼子，这样答案就会最大化了。


## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int b[N], n, t, ans, flag, sum;//sum 为每次遍历 b 数组时统计的答案，flag 表示之前的豚鼠数。 
int main() {
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin >> t;
	while(t--) {
		memset(b, 0, sizeof b);
		ans = flag = sum = 0;
		cin >> n;
		for(int i = 1; i <= n; i++) 
			cin >> b[i];
		for(int i = 1; i <= n; i++) {
			if(b[i] & 1) 
				flag++, sum++;
			else {
				if(!flag) sum = 0;
				else sum = (flag >> 1) + 1;
			}
			ans = max(ans, sum);
		}
		cout << ans << '\n';
	}
	return 0;
}
```


本文章是用于补充讲解，我发现现在好多题解都不写推理过程的，本来 CF 的题目翻译就有点模糊，漏掉了一些关键点，导致可能是读者理解困难，希望这篇帖子对读者有更深刻的帮助。

---

## 作者：_luouhgy_ (赞：2)

以下内容均手码。

## 题目大意

一共 $n$ 次输入，输入 $1$ 就买 $1$ 只不知道性别的豚鼠，输入 $2$ 就分辨出现在所有豚鼠的性别， $1$ 个笼子可以放 $2$ 只**性别相同**的豚鼠，求**最少**需要买多少个笼子。

## 思路

不同性别的豚鼠不能放在同一个笼子，所以每只不知道性别的豚鼠都需要一个笼子。

因为问的是**最少**需要买多少个笼子，所以设有 $cnt$ 只已知性别的豚鼠，最坏的情况就是有 $1$ 只雄豚鼠和 $n - 1$ 雌豚鼠，就需要 $1$ 个笼子装雄豚鼠， $\lceil (n - 1) \div 2\rceil$ 个笼子装雌豚鼠，一共 $\lceil (n - 1) \div 2\rceil + 1$ 个笼子。

## Code

 ```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int main(){
	cin>>t;
	while(t--){
		int n,a[100005],cnt1=0,cnt2=0,ans=0;//初始化 
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			if(a[i]==1){//买1只不知道性别的豚鼠 
				cnt1++;
				cnt2++;
			}else if(cnt2!=0){//统计需要的笼子数 
				cnt1=ceil(1.0*(cnt2-1)/2.0)+1.0;
			}
			ans=max(ans,cnt1);//注意需在循环中找答案 
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：Special_Tony (赞：1)

# 思路
首先我们要把当前的猪分成两类——有性别和无性别。无性猪只能一猪一笼，有性别时最坏情况下是 $\lfloor\frac s2\rfloor+1$ 个笼（没有有性猪时要特判）。需要的笼子就是它们之和。
# 代码
```cpp
# include <bits/stdc++.h>
typedef long long ll;
using namespace std;
int t, n, x, sum, tot, maxx;
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> t;
	while (t --) {
		cin >> n;
		maxx = sum = tot = 0;
		for (int i = 0; i < n; ++ i) {
			cin >> x;
			if (x < 2)
				++ tot;
			else
				sum += tot, tot = 0;
			maxx = max (maxx, (sum >> 1) + tot + (sum > 0));
		}
		cout << maxx << '\n';
	}
	return 0;
}
```

---

## 作者：Eterna (赞：0)

不能将两只同种性别的豚鼠放两个笼子里，所以性别不确定的豚鼠只能单独一间。

题目不告诉我们豚鼠具体的性别是什么，所以只能考虑最坏情况。

当 $b_i=1$ 时：

获得一只未知性别豚鼠，应该将其关进单独的房间。

当 $b_i=2$ 时：

将新豚鼠的性别假设为当前数量最少的性别。使答案最大化。

---

## 作者：Infinite_Loop (赞：0)

# CF1802B
## 题意
给定一个长度为 $n$ 的数组 $b$，对于每个 $b_{i}$ 有两种情况:

- 当 $b_{i} = 1$ 时，则代表购买一只豚鼠。
- 当 $b_{i} = 2$ 时，则代表测出每只豚鼠的性别。

现在你需要将这些豚鼠放进一些笼子里，问在最坏情况下笼子的最少数量。

笼子的约束条件：

- 每个笼子最多只能放两只豚鼠。
- 每个笼子的豚鼠性别要相同。
## 思路
本题在购买豚鼠的时候就要将豚鼠放进笼子里，并不是在最后放进笼子，且在任意时刻都可以调换每只豚鼠的位置（我一开始理解错了）。

知道了这个坑点后，我们就可以考虑模拟。

因为我们知道在不测豚鼠性别的情况下，我们只能把新购买的豚鼠一只占一个笼子。在测出所有豚鼠性别后，假设有 $x$ 只豚鼠，那么笼子最多是 $\lfloor \frac{n+2}{2} \rfloor$ 个。

于是我们可以用 $sum$ 记录豚鼠的数量，$ans1$ 记录有豚鼠的笼子的数量，$ans2$ 记录已经使用的笼子数量。从 $1$ 枚举到 $n$，在第 $i$ 个操作时有以下两种情况：

- 当 $b_{i} = 1$ 时，将 $sum$ 加上一，比较 $ans1$ 和 $ans2$ 的大小，如果相等，没有空笼子，将 $ans1$ 和 $ans2$ 都加上一；如果 $ans2$ 大，代表有空笼子，将 $ans1$ 加上一。
- 当 $b_{i} = 2$ 时，标记 $ans1$ 等于 $\lfloor \frac{sum+2}{2} \rfloor$ 即可。

最后输出 $ans2$ 即可。

本题需要注意的：

- 当 $sum = 0$ 且有第二种操作，这时要标记 $ans1$ 等于 $0$。
- 输出要换行。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int t,n,a[N];
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		int sum=0,ans1=0,ans2=0;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			if(a[i]==1){
				sum++;
				if(ans2>ans1){
					ans1++;
				}else{
					ans1++;
					ans2++;
				}
			}else{
				int now=(sum+2)/2;
				if(sum==0)now=0;
				ans1=now;
			}
		}
		cout<<ans2<<'\n';
	}
	return 0;
}
```

---

## 作者：P_VICVIC_R (赞：0)

~~这题竟然还能交题解。~~

----

看眼题，~~发现没翻译输入是啥（参见别的题解）~~，有一个豚鼠爱好者要给鼠鼠们“分寝”，不能“混寝”，但是有鼠鼠性别未知，有的已知，问最少多少间“寝室”。

那么对于未知性别者，只能住单间（不然就有概率出现~~男女鼠混寝~~）。

对于已知的，我们这么想：一共 $n$ 只豚鼠，两种性别，有没有感觉很像小学的抽屉原理：如果有三只以上，那么必然存在可以放在一个笼子的。

我们浅浅推一下：

| 总数 | 需要的笼子数 |                             原因                             |
| :--: | :----------: | :----------------------------------------------------------: |
|  1   |      1       |                      无关性别都要有一个                      |
|  2   |      2       |           有可能异性但也有可能同性，所以最坏要两个           |
|  3   |      2       | 抽屉原理，怎么都有一对同性，所以先给其中两只开一间，剩下两个参照一只时的答案要一间 |
|  4   |      3       | 也是一定有一对同性所以先给其中两只开一间，剩下两个参照两只时的答案要两间 |
|  5   |      3       | 一定有两对同性所以先给其中四只开两间，剩下两个参照一只时的答案要一间 |

我们发现其实超过三只时就可以用抽屉原理对应到前面的情况了，所以简单取个最大值就解决了。

代码太烂不放了，可以参照别人的。

---

## 作者：_xxxxx_ (赞：0)

### 题意

有 $n$ 个操作。每次操作给出一个数 $x$。

1. 若 $x=1$，则代表买入了一只豚鼠。

2. 若 $x=2$，则代表现在知道了**已经买过**的**所有**豚鼠的性别。

两只不同性别的豚鼠不能在同一个笼子里，每个笼子最多只能装 $2$ 只豚鼠。问最坏情况下要买多少个笼子才能装得下全部的豚鼠。

### 分析

显然可以知道，如果没有操作二，最坏情况就只能每个豚鼠分一个笼子。

因为操作二能知道已经买过的所有豚鼠性别，所以可以在线做。每次处理出现操作二时要用多少的笼子才能一定装完前面买过的豚鼠。

对于操作二进行分类讨论。记进行完操作二后知道了 $x$ 只豚鼠的性别。

1. 当 $x$ 为偶数时，最坏情况为同性配对完后，雌性和雄性都剩一只，要为他们都配一个笼子，此时需要 $\frac{x-2}{2}+2$ 个笼子。

2. 当 $x$ 为奇数时，最坏情况为同性配对完后，剩一只雌性或雄性，需要再开一个笼子，此时需要 $\left\lfloor\dfrac{x}{2}\right\rfloor+1$ 个笼子。

化简可以发现，上述两种情况皆需 $\left\lfloor\dfrac{x}{2}\right\rfloor+1$ 个笼子。

另外注意一下没有买豚鼠不会有剩的豚鼠，代码实现就不难了。

### 代码

```cpp
#include <iostream>
#include <cmath>
#include <string.h>
#include <cstdio>
#include <algorithm>
#define LL long long
using namespace std;
const int N = 1e5 + 10;
const int INF = 0x3f3f3f3f;
int T;
int n;
int buy, ans, cnt;
//buy:现在已经买了多少只豚鼠
//ans:记录需要多少个笼子
//cnt:到了一个操作二，装完已买的豚鼠需要多少个笼 
signed main()
{
	scanf("%d", &T);
	while(T--)
	{
		buy = ans = cnt = 0;
		scanf("%d", &n);
		for(int i = 1; i <= n; i++)//在线处理 
		{
			int opt;
			scanf("%d", &opt);
			if(opt == 1)
			{
				buy++;
				cnt++;
				//最坏给每个豚鼠分一个笼 
			}
			if(opt == 2) 
			{
				if(buy == 0)
				{
					cnt = 0;
					//没买豚鼠就不用笼子 
				}
				else
				{
					cnt = buy / 2 + 1;
					//奇偶皆为x/2+1 
				}
			}
			ans = max(ans, cnt);
		}
		printf("%d\n", ans);
	}
	return 0;
}
```


---

## 作者：LOvO (赞：0)

# CF1802B Settlement of Guinea Pigs 题解

~~这题目翻译太那啥了，我把那一大串英文放进百度翻译才看懂。。。~~

## 题意简述：

有一个人，做了 $n$ 个如下操作。

操作一：买回一只不知性别的豚鼠。

操作二：请医生鉴别所有不知性别的豚鼠的性别。

将同性的豚鼠一对一对地装进笼子里，求最坏情况下需要几个笼子。

## 解题思路：

- 如果你不知道某些豚鼠的性别时，在最坏情况下，你必须给它们每只一个笼子。
- 如果你已经鉴别出奇数只豚鼠的性别，设有 $k$ 只豚鼠，你必须给它们买 $\left\lceil\frac{k}{2}\right\rceil$ 个笼子。
- 如果你已经鉴别出偶数只豚鼠的性别，设有 $k$ 只豚鼠，在最坏情况下，你必须给它们买 $\left \lceil \frac{k}{4} \right \rceil$ 个笼子。

## Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
int tot, maxx, sum; //tot为有几只豚鼠，sum为至少需要的笼子的个数。
int main() {
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while(t--) {
		maxx = -1;
		tot = sum = 0;
		int n;
		cin >> n;
		while(n--) {
			int x;
			cin >> x;
			if (x == 1) tot++, sum++;
			else
				if (tot == 0) sum = 0;
				else sum = tot / 2 + 1;
			maxx = max(maxx, sum);
		}
		cout << maxx << endl;
	}
	return 0;
}
```

---

## 作者：Furina_Saikou (赞：0)

## 补充翻译

对于每个 $ b_i $ ，如果是 $ 1 $ 表示第 $ i $ 天买了一只豚鼠，如果是 $ 2 $ 表示第 $ i $ 天鉴定了已经有的豚鼠的性别。

## 思路

我们边读入边用一个 $ cnt $ 变量记录目前需要的笼子数，$ num $ 变量记录豚鼠数，$ ans $ 变量记录过去到现在需要的最大笼子数。

对于 $ cnt $ 变量，我们读到 $ 1 $ 就直接 ` cnt++ `，读到 $ 2 $ 就重新计算需要笼子数。

对于计算需要的笼子数，未鉴定的豚鼠需要单独的笼子装，而已经鉴定过的 $ x $ 只豚鼠，最坏情况是：$ 1 $ 只是雄性，剩下 $ x - 1 $ 只都是雌性，那么就需要 $ 1 $ 个笼子装雄性，再用 $ \lceil ( x - 1 ) \div 2 \rceil $ 个笼子装雌性。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,cnt,num,ans;
signed main()
{
	cin>>t;
	while(t--)
	{
		cin>>n;
		cnt=num=ans=0;//初始化
		for(int i=1,x;i<=n;i++)
		{
			cin>>x;
			if(x==1)
			{
				cnt++;//性别不明的要单独一个笼子
				num++;
			}else if(num)
			{
				cnt=ceil(1.0*(num-1)/2)+1;//重新计算笼子数，乘1.0为了保留精度
			}
			ans=max(cnt,ans);//答案是过程中的最大值，不是最终值
		}
		cout<<ans<<"\n";
	}
}
```


---

## 作者：封禁用户 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1802B)

[CF链接](https://codeforces.com/problemset/problem/1802/B)
## 题意
有 $p$ 只性别已知的豚鼠和 $q$ 只性别未知的豚鼠，在每个笼子只能关押性别相同的两只豚鼠的情况下，最坏需要购买几个笼子。
## 思路
一种贪心想法，最坏肯定是每只豚鼠都~~非常奢侈的~~有个笼子，然后模拟遍历数组，当数组元素值为 $2$ 的时候，假设有奇数只豚鼠，就把原来配好的豚鼠分掉，重新~~非常奢侈的~~买个笼子，使结果最坏；偶数个就只能直接分了。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int read(){
	//快读自行bdfs
	//否则 #2 TLE
}
void solve(){
	int a[10000001]={0};
	int an=0,p=0,su=0;
	int n;
	n=read();//定义读取
	for(int i=1;i<=n;i++){
		a[i]=read();
		if(a[i]%2){
			p++;
			su++;
		}
		else{
			if(p==0) su=0;
			else su=p/2+1;
		}//判断
		an=max(an,su);//最坏的情况
	}
	cout<<an<<endl;
	return;//结束
}
signed main(){
	int t=0;
	t=read();
	while(t--) solve();//t组数据
	return 0;//完结撒花
}
```

---

## 作者：Miyamizu_Mitsuha (赞：0)

## 思路
题目不难理解，对于每一天的计划，用两个变量 $x$ 和 $y$ 表示，其中 $x$ 表示已知性别的豚鼠数，$y$ 表示未知性别的豚鼠数。每天的 $x$ 和 $y$ 可以通过遍历计划得到。

对于已知性别的豚鼠，需要确定它们最多需要的笼子数。可以分为两种情况讨论：

+ 当 $x=0$ 时，表示还没有已知性别的豚鼠，所需的笼子数为 $0$。

+ 当 $x>0$ 时，最差情况之一是有 $1$ 只雄性豚鼠和 $x-1$ 只雌性豚鼠，这时所需的笼子数为 $\left\lceil\frac{x-1}{2}\right\rceil+1$。

遍历计划时，每次进行二操作之前和所有操作结束后更新一个最大值来得到最少需要买多少个笼子。
## 代码
```cpp
#include <iostream>
using namespace std;

void solve() {
    int n;
    cin >> n;
    int x = 0, y = 0, ans = 0;
    for (int i = 1; i <= n; i++) {
        int b;
        cin >> b;
        if (b == 1)
            y++;
        if (b == 2) {
            if (!x)
                ans = max(ans, x / 2 + y);
            else
                ans = max(ans, x / 2 + 1 + y);
            x += y;
            y = 0;
        }
    }
    if (!x)
        ans = max(ans, x / 2 + y);
    else
        ans = max(ans, x / 2 + 1 + y);
    x += y;
    y = 0;
    cout << ans << endl;
}

int main() {
    int t;
    cin >> t;
    for (int i = 1; i <= t; i++) solve();//我超周礼
    return 0;
}

```


---

## 作者：IYSY2009I (赞：0)

在每一天，情况都可以用两个字母 $x,y$ 表示。其中 $x$ 表示已知性别的天竺鼠数，$y$ 表示未知性别的天竺鼠数。每天的 $x,y$ 显然是可以轻松求出来的，于是我们只需要通过这两个数求出每一天所需的笼子数目，然后输出最大值就可以了。

首先有 $y$ 只天竺鼠性别未知，只能为每只天竺鼠提供单独的笼子。

接下来我们来考虑一下已知 $x$ 只已知性别的天竺鼠最多需要的笼子数，然后加上 $y$ 就可以了。我们分两种情况讨论。

1. $x=0$。显然所需的笼子数为 $0$。
1. $x>0$。不难发现此时最差情况之一是有 $1$ 只雄天竺鼠和 $x-1$ 只雌天竺鼠（证明过程略去），答案就是 $\left\lceil\dfrac{x-1}{2}\right\rceil+1$。

另外在代码编写难度方面还有一个小优化：注意到当 $x1 \ge x2$ 且 $y1 \ge y2$ 时，前面的答案显然大于等于后面的答案，所以我们只需要在每次进行二操作之前和所有操作结束后更新最大值即可。

代码：

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<1)+(x<<3)+c-'0';
		c=getchar();
	}
	return x*f;
}
void solve(){
	int n;
	scanf("%d",&n);
	int x=0,y=0,ans=0;
	for(int i=1;i<=n;i++){
		int b;
		scanf("%d",&b);
		if(b==1) y++;
		if(b==2){
			if(!x) ans=max(ans,x/2+y);
			else ans=max(ans,x/2+1+y);
			x+=y;
			y=0;
		}
	}
	if(!x) ans=max(ans,x/2+y);
	else ans=max(ans,x/2+1+y);
	x+=y;
	y=0;
	printf("%d\n",ans);
	return;
}
int main(){
	int t=read();
	for(int i=1;i<=t;i++)
		solve();
	return 0;
}
```


---

## 作者：olegekei (赞：0)

## 思路
假设当前未知性别的豚鼠有 $x$ 只，已知性别的豚鼠有 $y$ 只。

为了保证异性豚鼠不在同一个笼子里，未知性别的豚鼠一定是单独一个笼子，也就是说当前最少需要 $x$ 个笼子。接下来考虑已知性别的豚鼠。

对于这道题，我们需要考虑最坏情况，可以分出几种情况进行讨论：

- $y=1$。

	此时需要 $1$ 个笼子，无论性别男女。

- $y=2$。

	此时两豚鼠可能同性也可能异性，最坏情况下为两只同性，需要 $2$ 个笼子。

- $y=3$。

	此时三只豚鼠必有两只同性，安排到一个笼子里，剩下一只异性放到另一个笼子里，需要 $2$ 个笼子。

- $y=4$。

	此时最坏情况为三只同性，一只异性，需要 $3$ 个笼子。

而对于 $y>4$ 的情况，考虑 $y=5$ 时必有两对同性豚鼠，可以安排到两个笼子里，然后变成 $y=1$ 的情况，所以当 $y>4$ 时可以类比到 $y \le 4$ 的所有情况中。

则最后答案为 $\max(x+2\times\left \lfloor \dfrac{y-1}{4} \right \rfloor+a_{(y-1 \bmod 4)+1})$，其中 $a=\{1,2,2,3\}$，注意实时更新 $x,y$ 取最大值即可。
## 代码
```cpp
#include<iostream>
using namespace std;
int n,m;
int work(int res){
	int now=(res-1)/4;
	res=(res-1)%4+1;
	now<<=1;
	if(res==1)now++;
	if(res==2||res==3)now+=2;
	if(res==4)now+=3;
	return now;
}
int main(){
ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
int t;
cin>>t;
while(t--){
	cin>>n;
	int ans=0;
	int cnt=0,res=0;
	for(int i=1,x;i<=n;i++){
		cin>>x;
		if(x==1)cnt++;
		else{
			ans=max(ans,cnt+work(res));
			res+=cnt;
			cnt=0;
		}
	}
	ans=max(ans,cnt+work(res));
	cout<<ans<<'\n';
}
return 0;
}
```

---

## 作者：inc1ude_c (赞：0)

设当前已知性别的鼠的个数为 $a$，不知性别的鼠的个数为 $b$。

对于某一天：

- 如果买了一只新的，但这只你也不知道性别是啥，所以 $b$ 加一。

- 如果请了医生，那么 $b$ 只鼠你都知道性别了，所以 $a$ 加上 $b$，$b$ 清为 $0$。

答案显然就是每天最坏要多少笼子的最大值。

考虑如何计算当天最坏要多少笼子：

- 对于 $b$ 只你不知道性别的鼠，只能给每只不知性别的鼠都买一个专属的笼子来居住。

- 对于 $a$ 只你知道性别的鼠，设有 $x$ 只雄的，$a-x$ 只雌的，就要买 $\max\left\{\left \lceil \frac{x}{2} \right \rceil ,\left \lceil \frac{a-x}{2} \right \rceil \right\}$ 只笼子，该式子最大值为 $\left \lfloor \frac{a}{2} \right \rfloor +1$。

所以当天最坏要 $b+\left \lfloor \frac{a}{2} \right \rfloor +1$ 只笼子。特别的，如果 $a=0$，那么最坏要 $b$ 只笼子。

---

## 作者：隐仞Mrsu (赞：0)

# 题意
将豚鼠关到若干间房里，在满足要求的同时，使得使用的房间数尽量最少。

要求包括：
- 一间房最多只能关**两只**豚鼠；
- 已知两豚鼠性别**相同**后，才能关进**同一间房**。

输入 $n$ 个数，每个数 $b_i$ 表示第 $i$ 天的计划：
- 当 $b_i=1$ 时，得到一只新的豚鼠，性别未知；
- 当 $b_i=2$ 时，检测所有已得到了的豚鼠的性别。

# 分析
题目告诉我们，当 $b_i=2$ 时，会做“检测所有已得到了的豚鼠的性别”这件事，但不告诉我们豚鼠具体的性别是什么。

所以我们要保证，在能面对**最极端**的性别情况的同时，让房间数量**最少**。

因此，我们要假设每只获得的豚鼠的性别，构造出最极端的情况，从而求出能够承担各种情况的最少房间数量。

由于已知性别相同的两只豚鼠才能被关进同一间房，那么如果每天获得的豚鼠性比都相同，则消耗的房间最少，但这并非最极端的情况。而当未确认性别的豚鼠，**假设的性别尽量持平**的时候，消耗的房间数会最多，情况最极端。

# 算法思路
### 当 $b_i=1$ 时
获得一只豚鼠，更新未知性别的豚鼠的数量。因为其性别是假设的，所以不能和别的豚鼠关在一起。于是，若有空房，则将其关在空房内；若没有空房了，就新建一个房间，将其关进去。

### 当 $b_i=2$ 时
更新豚鼠性别的数据，比较当前未知性别的豚鼠数量，将该新豚鼠的性别假设为当前数量最少的性别。

此时，如果已经有同性别的豚鼠单身住在一间房，则将新豚鼠和该豚鼠共同关在一起，并腾出一间空房间；若无，则新豚鼠继续单独住在一间房。

# 代码
```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int N = 1e6+60;
LL _,n,b[N];
void work(){
	cin>>n;
	for(LL i=1;i<=n;i++){
		cin>>b[i];
	}
	LL m[3]={0,0,0},w[3]={0,0,0};  //住了i只公、母豚鼠的房间数量 
	LL unk=0,emp=0,res=0;  //未知性别的豚鼠数量，空房的数量，结果值 
	for(LL i=1;i<=n;i++){
		if(b[i]==1){ 
			if(emp){
				emp--;  //使用一间空房 
				unk++;  //增加一只未知性别的豚鼠 
			}
			else{
				res++;  //总房间的结果数量加一 
				unk++;  //增加一只未知性别的豚鼠 
			}
		}
		if(b[i]==2){
			if(!unk)continue;
			//处理未知性别的豚鼠 
			while(unk){
				if(m[1]>=w[1]){
					//当公的数量大于等于比母的，假设这只为母 
					if(w[1]==0){
						//豚鼠自己住进一间房 
						w[1]++; 
						unk--;
					}
					else{
						//将该豚鼠和原有的另一只同性别豚鼠关在一起 
						w[1]--;
						w[2]++;
						unk--;
						emp++;
					}
				}
				else{
					//当母的数量比公的多，假设这只为公 
					if(m[1]==0){
						//豚鼠自己住进一间房 
						m[1]++;
						unk--;
					}
					else{
						//将该豚鼠和原有的另一只同性别豚鼠关在一起 
						m[1]--;
						m[2]++;
						unk--;
						emp++;
					}
				}
			}
			
		}
	} 
	cout<<res<<'\n';
}
int main(){
	ios::sync_with_stdio(false);
	cin>>_;
	while(_--){
		work();
	}
} 
```


---

## 作者：ztrztr (赞：0)

在 <https://ztrztr.top/archives/246> 食用更佳。

# B. Settlement of Guinea Pigs

又是一道水题，毕竟这只蒟蒻只会做水题。

## 题意

Dasha 很喜欢豚鼠，她在 $n$ 天内要不是买豚鼠，要不是请医生来看豚鼠。

Dasha 和宠物店都无法分辨豚鼠的性别（思考人生），只能在医生来查看豚鼠的时候为这些豚鼠做性别鉴定。

为了豚鼠，Dasha 打算给它们买一些笼子，但宠物店里卖的笼子只能放最多 $2$ 只豚鼠。由于她不想让她的豚鼠遭受道德伤害，一个笼子里只能放同一种性别的豚鼠。

求 Dasha 最少需要买多少个笼子。

## 思路

对于每一天，如果昨天是买宠物且买了超过 $3$ 只豚鼠：

- 判断

  - 如果买了奇数只豚鼠，那么 $\text{sum} + \lfloor \frac{cnt}{2} \rfloor$，计数器清为 $1$。

  - 否则 $\text{sum} + \frac{cnt}{2} - 1$，计数器清为 $2$。

- `Max = max(Max, sum + cnt);`

## 代码

```cpp
/**
 * @Author: ztrztr
 * @Email: ztrztr2011@163.com
 * @Date: 2023/3/9 19:03:08
 * @LastEditors: ztrztr
 * @LastEditTime: 2023/3/9 19:03:08
 * Description: 
 * Copyright: Copyright (©)}) 2023 ztrztr. All rights reserved.
 */
#include <bits/stdc++.h>
 
using namespace std;
//I AK IOI
int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    long long T; cin >> T;
    while (T --) {
        long long n, cnt = 0, tmp = 0; cin >> n;
        long long a[100005];
        long long Max = 0;
        for (int i = 1; i <= n; i ++) {
            int x; cin >> x;
            a[i] = x;
            if (x == 1) cnt ++;
            if (x == 2) {
                if(a[i - 1] == 1 and cnt >= 3) {
					if(cnt % 2 == 1) {
						tmp += cnt / 2;
						cnt = 1;
					} else {
						tmp += cnt / 2 - 1;
						cnt = 2;
					}
				}
            }  
            Max = max(Max, tmp + cnt);
        }
        cout << Max << "\n";
    }
    return 0;
}
```



---

