# System Testing

## 题目描述

Vasya likes taking part in Codeforces contests. When a round is over, Vasya follows all submissions in the system testing tab.

There are $ n $ solutions, the $ i $ -th of them should be tested on $ a_i $ tests, testing one solution on one test takes $ 1 $ second. The solutions are judged in the order from $ 1 $ to $ n $ . There are $ k $ testing processes which test solutions simultaneously. Each of them can test at most one solution at a time.

At any time moment $ t $ when some testing process is not judging any solution, it takes the first solution from the queue and tests it on each test in increasing order of the test ids. Let this solution have id $ i $ , then it is being tested on the first test from time moment $ t $ till time moment $ t + 1 $ , then on the second test till time moment $ t + 2 $ and so on. This solution is fully tested at time moment $ t + a_i $ , and after that the testing process immediately starts testing another solution.

Consider some time moment, let there be exactly $ m $ fully tested solutions by this moment. There is a caption "System testing: $ d $ %" on the page with solutions, where $ d $ is calculated as

 $ $$$d = round\left(100\cdot\frac{m}{n}\right), $ $ </p><p>where  $ round(x) = \\lfloor{x + 0.5}\\rfloor $  is a function which maps every real to the nearest integer.</p><p>Vasya calls a submission <span class="tex-font-style-it">interesting</span> if there is a time moment (possibly, non-integer) when the solution is being tested on some test  $ q $ , and the caption says "System testing:  $ q$$$%". Find the number of interesting solutions.

Please note that in case when multiple processes attempt to take the first submission from the queue at the same moment (for instance, at the initial moment), the order they take the solutions does not matter.

## 说明/提示

Consider the first example. At time moment $ 0 $ both solutions start testing. At time moment $ 49 $ the first solution is fully tested, so at time moment $ 49.5 $ the second solution is being tested on the test $ 50 $ , and the caption says "System testing: $ 50 $ %" (because there is one fully tested solution out of two). So, the second solution is interesting.

Consider the second example. At time moment $ 0 $ the first and the second solutions start testing. At time moment $ 32 $ the first solution is fully tested, the third solution starts testing, the caption says "System testing: $ 25 $ %". At time moment $ 32 + 24.5 = 56.5 $ the third solutions is being tested on test $ 25 $ , the caption is still the same, thus this solution is interesting. After that the third solution is fully tested at time moment $ 32 + 33 = 65 $ , the fourth solution is fully tested at time moment $ 65 + 1 = 66 $ . The captions becomes "System testing: $ 75 $ %", and at time moment $ 74.5 $ the second solution is being tested on test $ 75 $ . So, this solution is also interesting. Overall, there are two interesting solutions.

## 样例 #1

### 输入

```
2 2
49 100
```

### 输出

```
1
```

## 样例 #2

### 输入

```
4 2
32 100 33 1
```

### 输出

```
2
```

## 样例 #3

### 输入

```
14 5
48 19 6 9 50 20 3 42 38 43 36 21 44 6
```

### 输出

```
5
```

# 题解

## 作者：__LiChangChao__ (赞：0)

## 题意

有 $n$ 份代码正在评测队列中，评测机可以同时评测 $k$ 份代码，第 $i$ 份代码对应的题目的测试点数量为 $a_i$，每个测试点的测试需要 $1$ 秒，对于第 $i$ 秒，定义 $d=\lfloor\frac{100\times m}{n}+0.5\rfloor$，其中 $m$ 是已经评测完的代码的数量，若一份代码正在评测它的第 $p$ 个测试点且 $p=q$ ，则称其为有趣的代码，问有多少份代码是有趣的。

## 思路

观察数据范围发现： $1\le n\le 1000,1\le k\le 100,1\le a_i \le 150$，显然，评测完所有代码所需时间为 $\lceil \frac{\sum^{i\le n}_{i=1}}{k} \rceil$，当 $k=1,n=1000,a_i=150$ 时，所需时间为 $\frac{1000\times 150}{1}=150000$，所以暴力枚举每一秒，计算当前正在评测的代码是否为有趣的代码即可。

时间复杂度约为 $O(n^2a_i)$，极限约为 $1.5\times 10^8$，足以通过本题。

## 代码
```
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e3+5,maxa=155,maxt=maxn*maxa;
int n,k,a[maxn],ans,finish,start[maxn];
bool ok[maxn];//是否评测完成
bool tj[maxn];//是否被统计过
int main() {
	scanf("%d%d",&n,&k);
	for(int i=1; i<=n; i++)scanf("%d",&a[i]);
	int ed=k;//当前评测到了哪一份代码
	for(int i=1; i<=maxt; i++) {
		int nw=0,m=min(ed,n);
		int d=floor((finish*100.0/n)+0.5);
		for(int j=1; j<=m; j++){
			if(!ok[j]){
				if(i-start[j]==d&&!tj[j]){
					ans++;
					tj[j]=1;
				} 
			} 
			if(i-start[j]==a[j]){
				ok[j]=1,nw++;
			}
		}
		finish+=nw,ed+=nw;//加上该秒评测完成的代码
		for(int j=1; j<=min(ed,n); j++){
			if(!start[j]&&j>k)start[j]=i;//记录开始评测时间
		}
	}
	printf("%d",ans);
}
```

---

