# [GCJ 2022 Qualification] d1000000

## 题目描述

虽然最常见的骰子有 6 个面，每个面显示 1 到 6 的不同整数，但许多游戏会使用其他类型的骰子。特别地，$d_k$ 表示一个有 $k$ 个面的骰子，每个面显示 1 到 $k$ 的不同整数。$d6$ 是标准骰子，$d4$ 有四个面，而 $d1000000$ 有一百万个面。

![](https://cdn.luogu.com.cn/upload/image_hosting/b9fu60so.png)

在这个问题中，我们从一个包含 $\mathbf{N}$ 个骰子的集合开始。第 $i$ 个骰子是 $d\mathbf{S}_i$，即它有 $\mathbf{S}_i$ 个面，分别显示 1 到 $\mathbf{S}_i$ 的整数。从 $x$ 开始、长度为 $\ell$ 的顺子是指整数序列 $x$, $x + 1$, $\cdots$, $x + (\ell - 1)$。我们需要选择部分（或全部）骰子，并从每个骰子中选取一个数字来组成一个顺子。用这种方式我们能组成的最长顺子有多长？


## 说明/提示

**样例解释**

在样例 #1 中，有多个方法可以用所有 4 个骰子组成一个顺子。上图展示了一种可能的方式。

在样例 #2 中，由于所有骰子的最大面数都不超过 5，因此无法组成超过 5 个骰子的顺子。有多种方法可以组成恰好 5 个骰子的顺子，例如：从两个 $d5$ 中选取 4 和 5，再从三个 $d4$ 中选取 1、2 和 3，形成顺子 $1, 2, 3, 4, 5$。

在样例 #3 中，可以通过丢弃一个 $d4$ 并使用剩余的 $d4$、$d5$ 和 $d6$ 获取 1 到 4，用 $d7$ 获取 5 到 7，用 $d10$ 获取 8 和 9，从而组成顺子 $1, 2, 3, 4, 5, 6, 7, 8, 9$。无法组成长度为 10 的顺子，因此这是最优解。

在样例 #4 中，我们只能组成长度为 1 的顺子，但可以通过从给定的 $d10$ 中任选一个数字来实现。

**限制条件**

- $1 \leq \mathbf{T} \leq 100$。

**测试集 1（9 分，可见评测结果）**

- $1 \leq \mathbf{N} \leq 10$。
- $4 \leq \mathbf{S}_i \leq 20$，对所有 $i$ 成立。

**测试集 2（11 分，可见评测结果）**

- $1 \leq \mathbf{N} \leq 10^5$。
- $4 \leq \mathbf{S}_i \leq 10^6$，对所有 $i$ 成立。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
4
4
6 10 12 8
6
5 4 5 4 4 4
10
10 10 7 6 7 4 4 5 7 4
1
10```

### 输出

```
Case #1: 4
Case #2: 5
Case #3: 9
Case #4: 1```

# 题解

## 作者：GeorgeDeng (赞：3)

你有 $n$ 个骰子，第 $i$ 个骰子有 $S_i$ 个面，让你摆出顺子。

因为顺子是有序的，所以，我们可以给 $S$ 排个序。然后，用 $now$ 标记现在应该摆出的点数，如果当前的 $now \le S_i$，说明当前的骰子可以摆出当前点数，$now \larr now+1$，$ans \larr ans+1$，最后输出答案即可。

代码：

```cpp
#include <iostream>
#include <algorithm>
#define int long long
using namespace std;

int n;
int a[100005];//就是S数组
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int _;
    cin>>_;
    for(int i = 1;i<=_;i++){
        cout<<"Case #"<<i<<": ";
        cin>>n;
        for(int i = 1;i<=n;i++){
            cin>>a[i];
        }
        sort(a+1,a+1+n);
        int now = 1;
        int cnt = 0;//就是ans
        for(int i = 1;i<=n;i++){
            if(a[i]>=now){//如果可以摆出当前的点数
                now++;//点数++，答案++
                cnt++;
            }
        }
        cout<<cnt<<endl;//输出答案
    }
    return 0;
}
```

---

## 作者：zhouxiaodong (赞：3)

> **题外话**：
> - 作者做这道题是发现这道题的满分是 $20$ 分，很奇怪。希望管理员有空的时候能改成 $100$ 分，看着也舒服一点......
> - 作者做这道题是发现这道题的限时是 $5.00s$ 至 $15.00s$，应该是为了关照其他语言（~听同学说 Go 这个语言运行很慢???~）。
# 思路
- **排序骰子面数**：首先将骰子的面数按升序排序。这样我们可以从小到大逐步构建顺子。
- **贪心选择**：对于排序后的骰子面数数组，我们希望每个骰子至少能提供一个比当前顺子最大值大1的数字。具体来说，假设当前顺子的最大值是 $maxn$，那么下一个骰子必须至少能提供 $maxn+1$ 的数字。也就是说，骰子的面数 $a_i$ 必须至少为 $maxn+1$。这样，我们可以从该骰子中选择 $maxn+1$，从而将顺子扩展到 $maxn+1$。
- 更新顺子长度：每次成功选择一个骰子后，顺子的长度增加 $1$，同时 $maxn$ 也增加 $1$。如果骰子的面数不足以提供 $maxn+1$，则跳过该骰子。

# AC Code
``````````cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int t;
	cin>>t;
	for(int i=1;i<=t;i++)
	{
		int n;
		cin>>n;
		int a[100010];
		for(int j=1;j<=n;j++)
		{
			cin>>a[j];
		}
		stable_sort(a+1,a+n+1);
		int maxn=0;
		int res=0;
		for(int j=1;j<=n;j++)
		{
			if(a[j]>=maxn+1)
			{
				maxn+=1;
				res+=1;
			}
		}
		cout<<"Case #"<<i<<": "<<res<<"\n";
	}
	return 0;
}
``````````

---

## 作者：Ghosty_Neutrino (赞：2)

## 题意
给定 $N$ 个骰子，第 $i$ 个骰子为 $d_{a_i}$（面数为 $a_i$）。

要求选择若干骰子（可全选），从每个选中的骰子中选一个数，组成最长的连续序列。求这个最长连续序列的长度。
## 分析
先将骰子按面数从小到大排序，然后采用贪心策略逐步构建最长连续序列。

首先初始化当前连续序列长度为 $0$。

遍历排序后的骰子数组，对于每个骰子：
* 如果当前骰子的面数 $\ge$ 当前连续序列长度 $+1$，则可以将该骰子加入序列，序列长度加 1。
* 否则，跳过该骰子。

排序后，每个骰子的面数是递增的。如果当前骰子的面数足够大（$\ge$ 当前序列长度 $+1$），则它一定可以作为序列的下一个元素，从而扩展序列长度。
## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int t,n;
int main() {
    scanf("%d",&t);
    for(int i=1;i<=t;i++){
        scanf("%d",&n);
        vector<int> a(n);
        for(int j=0;j<n;j++) scanf("%d",&a[j]);
        sort(a.begin(),a.end());
        int cur=0;
        for(int num:a){
            if(num>=cur+1) cur++;
        }
        printf("Case #%d: %d\n",i,cur);
    }
    return 0;
}
```

---

## 作者：封禁用户 (赞：2)

## [题目传送门](https://www.luogu.com.cn/problem/P12981)

又是第一个发题解的。

### 思路
这道题要求找出能用骰子组成的最长连续整数序列。我们先将骰子按面数排序，然后贪心地从 $1$ 开始逐个匹配，若当前骰子面数 $\ge$ 所需数字则计入顺子并递增数字，最终得到的顺子长度即为答案。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
void av() {
    int T;
    cin >> T;
    for (int t = 1; t <= T; ++t) {
        int N;
        cin >> N;
        vector<int> S(N);
        for (int i = 0; i < N; ++i) {
            cin >> S[i];
        }
        sort(S.begin(), S.end());
        int ast = 0;
        int cc = 1;
        for (int i = 0; i < N; ++i) {
            if (S[i] >= cc) {
                ast++;
                cc++;
            }
        }
        cout << "Case #" << t << ": " << ast << endl;
    }
}
int main() {
    av();
    return 0;
}
```

---

## 作者：IkillDream (赞：1)

# P12981 题解

## 思路

我们将骰子面数按升序排序。

然后从最小的骰子开始，尝试构建最长顺子。

注意到第 $i$ 个骰子至少需要 $\ge i$ 的面数才能参与长度为 $i$ 的顺子。

## [AC](https://www.luogu.com.cn/record/222078986) 代码

```c++
#include <bits/stdc++.h>
using namespace std;
int main() {
    int t;
    cin >> t;
    for (int kkk03 = 1; kkk03 <= t; kkk03++) {
        int n;
        cin >> n;
        int kkk04[100010];
        for (int i = 0; i < n; i++) cin >> kkk04[i];
        sort(kkk04, kkk04 + n);
        int kkk05 = 0;
        for (int i = 0; i < n; i++) {
            if (kkk04[i] > kkk05) {
                kkk05++;
            }
        }
        cout << "Case #" << kkk03 << ": " << kkk05 << "\n";
    }
    return 0;
}
```

---

## 作者：TFX_Y (赞：1)

## 思路

想要组成的顺子最长，只有选择最优策略，即优先选择点数小的骰子。因为如果现在选了点数小的骰子，在后面便可以选择更大点数的骰子。

因此，我们可以对这些骰子进行从小到大的排序并遍历，在选择点数小的骰子的同时，记录一下当前的点数，并判断下一个骰子是否可以连上。如果可以连上，则选择当前点数 $+1$ 的面并更新当前点数，以便后面连上更多的骰子。

## 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,s[100005];
int solve(){
	int lst=0,ans=0;
	for(int i=1;i<=n;i++){
		if(s[i]>lst){
			lst++;
			ans++;
		}
	}
	return ans;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	for(int k=1;k<=t;k++){
		cin>>n;
		for(int i=1;i<=n;i++) cin>>s[i];
		sort(s+1,s+n+1);
		cout<<"Case #"<<k<<": "<<solve()<<"\n";
	}
	return 0;
} 
```

---

## 作者：bz029 (赞：0)

### 思路
由题目知，此题为贪心题。

想要组成的顺子最长，只有优先选择点数小的骰子才行。因为现在选了点数小的骰子，在后面就可以选择点数更大的骰子。

因此，我们可以对这些骰子进行升序排序并遍历，判断此骰子的点数 $a_i$ 大于已选骰子数（也就是目前顺子的最大点数）$sum$，就可以将它加入顺子，也就是让 $sum$ 加 $1$。

最后输出 $sum$，即可。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;

int t,n,a[N],o; 

void work(){
	int sum=0;//多测要清空 
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+n+1);//排序 
	for(int i=1;i<=n;i++){
		if(a[i]>sum) sum++;//判断 
	}
	cout<<"Case #"<<o<<": "<<sum<<endl;
}

signed main(){
	cin>>t;
	while(t--){
		o++;
		work();
	}
	
	return 0;
}

```

---

## 作者：皓月星辉 (赞：0)

## PART1 简化题意
本题有多组数据，对于每组数据，给定 $n$ 表示集合个数和 $n$ 个整数 $a_1$ 到 $a_n$ 表示每个集合的大小，第 $i$ 个集合表示从 $1$ 到 $n$ 的所有整数，要求从若干个集合中每个集合选取一个数，共同构成一个公差为 $1$ 的等差数列，求能获得的最长的等差数列的长度。
## PART2 分析
考虑贪心，令等差数列的首项为 $1$，将集合按大小从小到大排序，依次处理，假设从第 $1$ 个集合到第 $i - 1$ 个集合，能获得的最长的等差数列的长度为 $ans_{i-1}$，那么，从第 $1$ 个集合到第 $i$ 个集合，能获得的最长的等差数列的长度 $ans_i$ 为 $ans_{i-1} + 1$ 和 $a_i$ 中较小的数，这是因为如果第 $i$ 个集合取不到 $ans_{i-1}+1$ 的话，那这个集合就无数可选，对答案没有贡献。
## PART3 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long T,x,n,a[100005],ans[100005];
int main()
{
  cin>>T;
  x=T;
  while(T--)
  {
    cin>>n;
    for(int i=1;i<=n;i++)
    {
      cin>>a[i];
      ans[i]=0;//清空上一问答案
    }
    sort(a+1,a+n+1);//排序
    for(int i=1;i<=n;i++)ans[i]=min(ans[i-1]+1,a[i]);//依次处理
    cout<<"Case #"<<x-T<<": "<<ans[n]<<endl;
  }
  return 0;
}
```
## 结语
~~本题解由本人亲自编写，引用请注明来源。~~

抄题解可耻，请勿直接复制。

---

## 作者：StormWhip (赞：0)

## 思路
考虑贪心，处理到顺子中的某一个数字时，选择能选取到这个数字的面数最小的的一个骰子，显然这样做一定最优。因此将骰子的面数从小到大排序，依次尝试选取骰子即可，时间复杂度 $O(nT)$。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5;
int T,n,a[N],now,p;
void Solve()
{
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+n+1);
	now=1;p=1;
	while(p<=n)
	{
		if(a[p]>=now) now++;
		p++;
	}
	cout<<now-1<<"\n";
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>T;
	for(int c=1;c<=T;c++)
	{
		cout<<"Case #"<<c<<": ";
		Solve();
	}
	return 0;
}
```

---

## 作者：LG086 (赞：0)

一共 $N$ 个骰子，每个骰子有 $s_i$ 面，可以表示 $1$ 到 $s_i$ 之间的不同整数。要搞成一个最长的顺子，我们可以先对这些骰子按 $s_i$ 从小到大排序，然后从 $s_1$ 开始遍历。记 $lst=1,ans=0$，若当前 $s_i\ge lst$，则 $ans \leftarrow ans+1,lst \leftarrow lst+1$。这样就可以求出最长顺子的长度，即 $ans$ 的值。

代码略。

---

