# [NERC 2018]  Guest Student

## 题目背景

翻译自 [NERC 2018](https://neerc.ifmo.ru/archive/2018/neerc-2018-statement.pdf) G 题。

## 题目描述

你作为某知名大学的客座学生，你想要在那里学习 $k$ 节课，但同时很遗憾，对于每周，你只有特定的时间才能有空去听课，如果 $a_i = 1$，说明周 $i$ 你有空，反之则没空。

你需要安排一个合理的日程，使得你去听第一节课到最后一节课中间经过的时间最短，当然第一节课听什么的顺序由你决定。

## 说明/提示

对于所有数据，保证 $1 \leq t \leq 10000$，$1 \leq k \leq 10^8$ 且 $a_i \in \{0,1\}$。

对于样例一，从周二开始听课听到下周二，经过 $8$ 天。

## 样例 #1

### 输入

```
3
2
0 1 0 0 0 0 0
100000000
1 0 0 0 1 0 1
1
1 0 0 0 0 0 0```

### 输出

```
8
233333332
1```

# 题解

## 作者：Genshineer (赞：2)

考虑将中间经过的时间分成三段：若干个整星期，前面的散块，后面的散块。

可以先考虑没有前面的散块的做法：

- 设经过了 $res$ 个整星期，记每个整星期有 $cnt$ 天有空，显然中间每次有空都选择听课是最优的，可以发现 $res=7\times\lfloor\dfrac{k-1}{cnt}\rfloor$，此时剩下需要安排的课程数为 $k-\lfloor\dfrac{res}{7}\rfloor\times cnt$。由于剩下的天数不超过 $7$，所以可以直接扫过整个星期并累加答案。

```cpp
int get(int x) {
	int res = 7 * ((x - 1) / cnt);
	x -= (res / 7) * cnt;
	for (int i = 1; i <= 7 and x; i++) {
		res++;
		x -= a[i];
	}
	return res;
}
```

接下来可以发现，前面的散块只有 $6$ 种情况，即以一个星期的每天作为开头的散块，不妨考虑直接“旋转” `a` 数组，从星期一开头开始枚举，每次统计完答案直接把开头的元素扔到数组尾部。可以证明，这一做法与直接处理前面的散块是等价的，从而极大地降低了程序地实现难度。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int TestCase, k, a[10], ans, cnt;

void rtt() { // Rotate
	int tmp = a[1];
	for (int i = 1; i < 7; i++) a[i] = a[i + 1];
	a[7] = tmp;
}

int get(int x) {
	int res = 7 * ((x - 1) / cnt);
	x -= (res / 7) * cnt;
	for (int i = 1; i <= 7 and x; i++) {
		res++;
		x -= a[i];
	}
	return res;
}

signed main() {
//Fast IO
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

	cin >> TestCase;
	while (TestCase--) {
		cin >> k;
		cnt = 0, ans = 1e18;
		for (int i = 1; i <= 7; i++) cin >> a[i], cnt += a[i];
		for (int i = 1; i <= 7; i++) {
			ans = min(ans, get(k));
			rtt();
		}
		cout << ans - 1<< "\n";
	}
}
```

另给出官方题解供参考：

```cpp
#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < int(n); i++)

const int N = 7;

int main() {
    int testCaseCount;
    cin >> testCaseCount;
    forn(testCase, testCaseCount) {
        int k;
        cin >> k;
        vector<int> a(N);
        forn(i, N)
            cin >> a[i];
        int sum = accumulate(a.begin(), a.end(), 0);
        int result = INT_MAX;
        forn(i, N)
            if (a[i] == 1) {
                int n = max(0, k / sum - 1);
                int j = i, cur = n * sum, m = n * 7;
                while (cur < k) {
                    cur += a[j];
                    j = (j + 1) % N;
                    m++;
                }
                result = min(result, m);
            }
        cout << result << endl;
    }
}
```

---

## 作者：what_can_I_do (赞：1)

[传送门](https://www.luogu.com.cn/problem/P9797)

我怎么越来越弱了，被橙题给难了一天！

首先，一看到这题，我们就可以想到周期问题了。

我们用一个循环枚举如果星期 $i$ 能听课就从星期 $i$ 开始听课。然后我们先把那节课听了，接下来周期就是从 $i+1$ 听到 $i$ 的课（若 $i+1$ 为 $8$，则改为 $1$），周期长为 $7$ 天。计算有几个周期的话就是先把 $k$ 减去 $1$，相当于减去第一次听的课，接下来只要除以一个星期能听的课的课程数就行，再乘 $7$ 计算天数。

但是我们注意到这样子做会导致可能会余下一个没进行完的周期，此时只要暴力求解该周期需要几天听课就行了。

# CODE:
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		int k,a[15],sum=0,ans=999999999,cnt=0;
		scanf("%d",&k),k--;
		for(register int i=1;i<=7;i++) scanf("%d",&a[i]),sum+=a[i],a[i+7]=a[i];
		for(register int j=1;j<=7;j++)
		{
			if(!a[j]) continue;
			cnt=k/sum*7+1;
			int kk=k%sum;
			if(!kk){ans=min(ans,cnt);continue;}
			for(register int i=j+1;i<=j+7;i++)
			{
				if(a[i]) kk--;
				cnt++;
				if(!kk){ans=min(ans,cnt);break;}
			}
			cnt=0;
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：linyukun (赞：1)

## 1. 前言
本文的分析会比较通俗，自己要多去思考，麻烦一定 _仔细全部看完_，有异议、不懂或认为可以优化请私信反馈呢。  

## 2. 题目解析：
首先，这是一道数学推导题。所以，我们考虑模拟。  
~~毕竟谁在有简单解的情况下还去推易错的式子啊。~~  
对于模拟，我们有一个简单的思路，就是**一天天过，能上课就上课，直到 $k=0$ 停止**，看看过去几天。然后**每个起始日都模拟一遍，取最小值**。  
显然时间复杂度劣的要命，但是没关系，先写出来再优化。  
挂代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long T,k,sum,minn,cnt;
bool b[10];
int main(){
	cin>>T;
	while(T--){
		minn=999999999;
		sum=0;
		cin>>k;
		for(int i=1;i<=7;i++){
			cin>>b[i];
		}
		for(int i=1;i<=7;i++){
			if(b[i]){
				int j=i,kk=k;
				cnt=0;
				while(kk>0){
					cnt++;
					if(b[j])kk--;
					j++;
					if(j==8)j=1;
				}
				minn=min(minn,cnt);
			}
		}
		cout<<minn<<"\n";
	}
	return 0;
}
```  
然后，我们考虑优化这个代码。  
它的主要耗时在哪？在遍历无法上课的日子。所以我们想到一种优化：
+ 首先，只有上课的日子才做出了贡献。
+ 其次，不上课的日子只提供天数。
+ 所以，我们想到存下上课的日子和它们间隔的天数。
+ 最后，选择使用结构体存下上课的日子，处理出间隔，只遍历结构体数组。遍历一个元素就上一节课，同时日子过去它与上一个元素间隔的天数。

代码如下：
```cpp#include<bits/stdc++.h>
using namespace std;
long long T,k,l,minn,cnt;
bool b;
struct aaa{
	int day,sum;
}a[10];
int main(){
	cin>>T;
	while(T--){
		minn=999999999;
		l=0;
		cin>>k;
		for(int i=1;i<=7;i++){
			cin>>b;
			if(b){
				l++;
				a[l].day=i;
			}
		}
		for(int i=2;i<=l;i++){
			a[i].sum=a[i].day-a[i-1].day;
		}
		if(l==1){
			a[1].sum=7;
		}
		else{
			a[1].sum=7-(a[l].day-a[1].day);
		}
		for(int i=1;i<=l;i++){
			int j=i,kk=k-1;
			cnt=1;
			while(kk>0){
				kk--;
				j++;
				if(j>l)j=1;
				cnt+=a[j].sum;
			}
			minn=min(minn,cnt);
		}
		cout<<minn<<"\n";
	}
	return 0;
}
```

但是，这个代码仍然会慢的要命。  
我们又发现，每一周的情况都是一样的，所以我们可以统计一下每周能上的课数。  
每 $7$ 天统一累计一次，写出如下优化代码。

```cpp
while(kk>num){
	kk-=num;
	cnt+=7;
}
```

我们惊喜的发现，这个优化毛用也没有。  
为什么呢？因为 $7$ 天还是太小了。我们要用更大的单位，比如 $7000000$ 天。  
但这同时带来了另一个问题：大数解决了，但是剩下了几十万天也够我们的朴素遍历跑半天了。  
所以，使用多次处理的方式，每次循环以 $1000$ 倍为跨度倍数，兼顾了速度和遗留的数据量。
## 3. 提示要点：
* 注意处理间隔日期时，**第一天存的是与最后一天的间隔，只有一个的话就是一周**。

## 4. 代码写作：
理论存在，实践开始。  

代码理有详细的注释幺~
```cpp
#include<bits/stdc++.h>
using namespace std;
long long T,k,l,minn,cnt,num;
bool b;
struct aaa{
	int day,sum;
}a[10];
int main(){
	cin>>T;
	while(T--){
		minn=999999999;//开得很大
		num=0;
		l=0;//记得初始化
		cin>>k;
		for(int i=1;i<=7;i++){
			cin>>b;
			if(b){//如果有空，记录下来，增加总天数
				num++;
				l++;
				a[l].day=i;
			}
		}
		for(int i=2;i<=l;i++){//差值
			a[i].sum=a[i].day-a[i-1].day;
		}
		if(l==1){//特判。只有一天时，一周之后才能再上
			a[1].sum=7;
		}
		else{
			a[1].sum=7-(a[l].day-a[1].day);
		}
		for(int i=1;i<=l;i++){
			int j=i,kk=k-1;
			cnt=1;//开始时上了一天的课
			while(kk>num*100000000){
				kk-=num*100000000;
				cnt+=700000000;
			}
			while(kk>num*100000){
				kk-=num*100000;
				cnt+=700000;
			}
			while(kk>num*100){
				kk-=num*100;
				cnt+=700;
			}
			while(kk>num){
				kk-=num;
				cnt+=7;
			}
			//以上就是千倍（差值）循环优化，十或百倍没有什么优化的意义。
			while(kk>0){
				kk--;
				j++;
				if(j>l)j=1;
				cnt+=a[j].sum;
				//挨个寻找，cnt加上两个可以上课日子的时间差，要上的课减少一节。
			}
			minn=min(minn,cnt);//找到最小
		}
		cout<<minn<<"\n";
	}
	return 0;
}
```

## 5. 总结鸣谢：
**本题是一道考验耐心思维的模拟，难度适中。**  
**另：还有感谢管理大大的的审核。**

---

## 作者：Practice_Account (赞：0)

### 题目大意

[原题！](https://www.luogu.com.cn/problem/P9797)

读入一个数字 $k$ 和 七个字符 $a_i$，且 $a_i∈\{0,1\}$。

当 $a_i = 1$ 时，说明周 $i$ 你有空，反之则没空。

让我们求**最短的从第一节课到最后一节课所经过的时间（单位：天）**。

# #

### 解题方法

直接模拟即可！

详细看代码：

```
#include<bits/stdc++.h>
using namespace std;
int a[8];
int main(){
	int T;
	std::cin >> T;
	while(T --){
		int k, day = 0, week, ans = INT_MAX;
		std::cin >> k;
		for(int i = 1; i <= 7; i ++){
			std::cin >> a[i];
			day += a[i];
		}
		for(int i = 1; i <= 7; i ++){
			week = k % day + day;
			int tot = 0;
			int j = i;
			for(tot = 1; ; tot ++){
				if(a[j] == 1){
					week --;
				}
				j = j % 7 + 1;
				if(week == 0) break;
			}
			ans = std::min(tot, ans);
		}
		ans = ans + (k / day - 1) * 7;
		std::cout << ans << endl;
	}
	return 0;
}
```

---

