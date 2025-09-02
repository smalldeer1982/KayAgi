# [GCJ 2011 #1C] Space Emergency

## 题目描述

太空中发生了紧急情况！你需要尽快将你的舰队旗舰从恒星 $0$ 送到恒星 $N$，途中必须按编号递增顺序依次经过所有恒星（$0 \rightarrow 1 \rightarrow \ldots \rightarrow N$）。你的旗舰通常以 $0.5$ 秒差距每小时的速度航行。

除了派出旗舰外，你还可以命令工程师在不同的恒星上建造最多 $L$ 个加速器。建造一个加速器需要 $t$ 小时，所有 $L$ 个加速器可以并行建造。当你的旗舰从一个已完成加速器的恒星出发前往下一个恒星时，它的速度将提升为 $1$ 秒差距每小时。

如果旗舰在从某个恒星前往下一个恒星的途中，该恒星上的加速器建造完成，那么旗舰会在加速器完成的瞬间开始以更快的速度前进。

如果你合理建造加速器，使旗舰尽快到达恒星 $N$，那么旗舰需要多少小时才能到达？

## 说明/提示

**说明**

在第二个测试用例中，我们可以建造一个加速器。两段距离分别为 $[10, 4]$。我们在第一个恒星建造加速器。经过 $4$ 小时，旗舰已前进 $2$ 秒差距，此时加速器建造完成。旗舰再用 $8$ 小时到达恒星 $1$，然后再用 $8$ 小时到达目的地恒星 $2$。

注意：本题设定的宇宙中，光速远大于 $1$ 秒差距每小时，因此无需考虑相对论效应。

**数据范围**

- $1 \leq T \leq 100$。
- $1 \leq C \leq 1000$。
- $C \leq N$。
- $1 \leq a_i \leq 10^4$。
- $0 \leq t \leq 10^{11}$。
- $t$ 为偶数。

**小数据范围（12 分，测试集 1 - 可见）**

- $1 \leq N \leq 1000$。
- $0 \leq L \leq 2$。
- 时间限制：3 秒。

**大数据范围（25 分，测试集 2 - 隐藏）**

- $1 \leq N \leq 10^6$。
- $0 \leq L \leq N$。
- 时间限制：6 秒。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2
2 20 8 2 3 5
1 4 2 2 10 4```

### 输出

```
Case #1: 54
Case #2: 20```

# 题解

## 作者：hlb44 (赞：2)

~~所以说我是第一个通过的？~~

[题目传送门](https://www.luogu.com.cn/problem/P13372)

阅读题目，我们可以发现基础时间是所有段在没有加速器的情况下的总时间。

接着我们对于每个段，计算如果在其起点放置加速器，可能节省的时间。

然后，我们定义候选段是那些在加速器建造完成后仍有部分旅程的段。现在我们只需要对每个候选段可能的节省时间降序排序，选择前 $L$ 个最大的节省时间，累加总节省时间。

最后的答案就是用基础时间减去总节省时间得到的最短总时间。

代码：


```cpp
#include<bits/stdc++.h>
using namespace std;

int main() {
	int T;
	cin>>T;
	for(int case_num=1; case_num<=T; ++case_num) {
		long long L,t,N,C;
		cin>>L>>t>>N>>C;
		vector<long long>a(C);
		for(int i=0; i<C; ++i) {
			cin>>a[i];
		}
		vector<long long>s;
		for(int i=0; i<N; ++i) {
			s.push_back(a[i%C]);
		}
		long long time=0;
		vector<long long>cl;
		long long sum=0;
		for(int i=0; i<N; ++i) {
			long long d=s[i];
			time+=2*d;
			sum+=2*d;
			if(sum>t) {
				long long cnt=sum-t;
				if(cnt>d*2) {
					cnt=d*2;
				}
				cl.push_back(cnt/2);
			}
		}
		sort(cl.rbegin(),cl.rend());
		long long ans=0;
		for(int i=0; i<min(L,(long long)cl.size()); ++i) {
			ans+=cl[i];
		}
		cout<<"Case #"<<case_num<<": "<<(time-ans)<<endl;
	}
	return 0;
}
```

---

