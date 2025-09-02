# [NERC 2019] DevOps Best Practices

## 题目描述

**Daisy** 是 RainyDay 公司的一名高级软件工程师。她刚刚为产品实现了三个新功能：第一个功能使产品能够运行，第二个功能使产品运行得更快，第三个功能使产品运行得更正确。公司鼓励对新功能进行至少一些测试，因此 Daisy 指派她的实习生 **Demid** 为这些新功能编写测试用例。

有趣的是，这三个功能在 Demid 的开发服务器（编号为 1）上通过了所有测试，但在其他某些服务器上可能会测试失败。

Demid 完成任务后，Daisy 指派你将这三个功能部署到公司的所有 $n$ 台服务器上。对于每个功能 $f$ 和每台服务器 $s$，Daisy 会告诉你她是否希望将功能 $f$ 部署到服务器 $s$ 上。如果她希望部署，即使功能 $f$ 在服务器 $s$ 上测试失败也必须部署；如果她不希望部署，则不能部署。

公司有两种重要的部署工具：持续部署（CD）和持续测试（CT）。CD 可以在多对服务器之间建立有向图形式的连接，而 CT 可以配置在某些服务器上。

如果从服务器 $s_1$ 到服务器 $s_2$ 配置了 CD，那么每当 $s_1$ 接收到新功能 $f$ 时，系统会启动以下部署流程将 $f$ 部署到 $s_2$：

1. 如果功能 $f$ 已经部署在服务器 $s_2$ 上，则不进行任何操作。
2. 否则，如果服务器 $s_1$ 未配置 CT，则 $s_1$ 会直接将功能 $f$ 部署到 $s_2$，不进行测试。
3. 否则，服务器 $s_1$ 会对功能 $f$ 运行测试。如果测试失败，则不进行任何操作；如果测试通过，则将功能 $f$ 部署到 $s_2$。

你需要配置 CD/CT 系统，之后 Demid 会将所有三个功能部署到他的开发服务器上。你的 CD/CT 系统必须确保每个功能仅被部署到 Daisy 指定的服务器集合。

由于公司计算资源有限，你最多只能建立 $264$ 条 CD 连接。

## 说明/提示

第一个样例测试的 CD/CT 系统配置如下图所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/stnjo553.png)

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
3
1 1 1
1 0 1
1 1 1
1 1 1
0 0 0
1 0 1```

### 输出

```
Possible
1 1 1
2
3 2
1 3```

## 样例 #2

### 输入

```
2
1 1 1
0 0 1
1 1 1
1 1 0```

### 输出

```
Impossible```

# 题解

## 作者：ttmttntff (赞：0)

题意：有三个信道，每个信道发送一种信号。每个节点须对接到发送对应要求信号的节点上，并将该信号处理后传递给下一节点。构造信号传输模式。

三个信道只有开/闭两种状态，所以只有八种信号。许多节点的功能都是相同的，所以试将节点由功能进行分类。

第一类节点类似过滤器，通过配置 CT （见题面），将收到的信号经过滤后发送。举例来说，若输入信号为 110 ，过滤信道为 011 ，则输出信号为 010 。

为了减少传递的数量，我们引入第二类节点，整合来自两个节点的信号。举例来说，若输入信号为 100 和 010 ，则输出信号为 110 。这类节点不应被配置 CT 。

因为信号模式极少，功能性节点很少，绝大多数都是直接接收信号即可。

分析知如有解，这种方式构造的解传递数不会超过 $n+1$ 。

```cpp
//洛谷P12937
#include <iostream>
#include <vector>
using namespace std;

int main()
{
	int n;
	cin >> n;
	//a为节点通道开闭需求,b为节点通道开闭状态
	vector <int> a(n + 1), b(n + 1);
	for (int i = 1; i <= n; i++) {
		int a_1, a_2, a_3;
		cin >> a_1 >> a_2 >> a_3;
		a[i] = (a_1 << 2) + (a_2 << 1) + a_3;
	}
	for (int i = 1; i <= n; i++) {
		int b_1, b_2, b_3;
		cin >> b_1 >> b_2 >> b_3;
		b[i] = (b_1 << 2) + (b_2 << 1) + b_3;
		b[i] &= a[i];
	}

	//特定通道开闭状态接口
	int f[8] = { 0,0,0,0,0,0,0,1 };
	vector <int> cb(n + 1);
	vector <vector<int> > cd(n + 1);
	//是否已满足开闭需求
	vector <bool> d(n + 1);
	d[1] = 1;

	for (int i = 0; i < 600; i++) {
		for (int j = 1; j <= n; j++) {
			if (d[j])
				continue;
			int A = a[j];
			if (f[A]) {
				cd[f[A]].push_back(j);
				f[b[j]] = j;
				d[j] = 1;
				continue;
			}
			if (i < 300)
				continue;
			if (A == 3 && f[1] && f[2]) {
				cb[j] = 1;
				cd[f[1]].push_back(j);
				cd[f[2]].push_back(j);
				f[3] = j;
				d[j] = 1;
				break;
			}
			if (A == 5 && f[1] && f[4]) {
				cb[j] = 1;
				cd[f[1]].push_back(j);
				cd[f[4]].push_back(j);
				f[5] = j;
				d[j] = 1;
				break;
			}
			if (A == 6 && f[2] && f[4]) {
				cb[j] = 1;
				cd[f[2]].push_back(j);
				cd[f[4]].push_back(j);
				f[6] = j;
				d[j] = 1;
				break;
			}
		}
	}

	for (int i = 1; i <= n; i++)
		if (!d[i]) {
			cout << "Impossible" << endl;
			return 0;
		}
	int m = 0;
	for (int i = 1; i <= n; i++)
		m += (int)cd[i].size();
	if (m > 264) {
		cout << "Impossible" << endl;
		return 0;
	}
	cout << "Possible" << endl;
	for (int i = 1; i <= n; i++)
		cout << !cb[i] << " ";
	cout << endl << m << endl;
	for (int i = 1; i <= n; i++)
		for (auto it = cd[i].begin(); it < cd[i].end(); it++)
			cout << i << " " << *it << endl;
	return 0;
}
```

---

