# Military Trainings

## 题目描述

### 题目大意
有 $n$ 个坦克，从1到n编号，它们要进行消息传输。

每一次传输如下，列表中第一个坦克将信息传输到列表中的某个坦克。接收到该消息的坦克将其进一步发送到列表后的某个坦克。该过程将继续进行，直到最后一个坦克收到消息。可能不是列表中的所有坦克都会收到消息，但列表中的最后一个坦克必须收到消息。

当最后一个坦克收到消息时，它将挪到第一个位置，并发送一条消息。当信息到达最后一个坦克时，该坦克移动到列的开头，并将下一条信息发送到列表的末尾，依此类推。因此，当列中的坦克返回到其原始顺序时，练习就完成了。

在两个坦克之间传输信息需要一秒钟，然而，并非总是一个坦克可以将信息传输给另一个坦克。让我们考虑列中的两个坦克，使它们中的第一个是从开始计数的列中的第i个，第二个是列中的j个，并假设第二个坦克的编号为x。然后，如果$ i<j $ and $ i>=j-a_{x} $ 则可以传输。

你会得到坦克的数量，以及所有坦克的信息接收半径。您必须帮助Smart Beaver并组织消息传输，使所有消息的总传输时间尽可能短。

## 样例 #1

### 输入

```
3
2
1
1
```

### 输出

```
5
```

## 样例 #2

### 输入

```
5
2
2
2
2
2
```

### 输出

```
10
```

# 题解

## 作者：szh_AK_all (赞：1)

不理解题解区里的为什么都是 dp 做法，明明有更简洁且好想的做法的。

## 分析
题目相当于是让我们模拟 $n$ 轮操作，每轮操作需要花费最少的步数让消息从第一辆坦克传递到最后一辆坦克，很明显我们对于当前坦克，应当贪心的将信息传递给能传递的最靠后的一辆坦克，也就是说我们需要求出每辆坦克可以传递的最靠后的坦克。

考虑倒着枚举每辆坦克，容易发现随着坦克的编号不断变小，坦克可以传递的最靠后的坦克的编号也会不断变小。因为当坦克编号有 $i$ 变为 $j$ 时，原先不能到达 $i$ 号坦克的坦克 $k$ 应当满足 $i<k-a_k$，又因为我们是倒着枚举坦克，所以 $j<i<k-a_k$，也就是说不能到达 $i$ 号坦克的坦克也无法到达 $j$ 号坦克。

维护便很简单了。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[100005], nxt[100005];

int main() {
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	int ans = 0;
	for (int k = 1; k <= n; k++) {
		int p = n;
		for (int i = n - 1; i >= 1; i--) {
			while (i < p - a[p])
				p--;
			nxt[i] = p;
		}
		int now = 1;
		while (1) {
			now = nxt[now];
			ans++;
			if (now == n)
				break;
		}
		int kk = a[n];
		for (int i = n; i >= 2; i--)
			a[i] = a[i - 1];
		a[1] = kk;
	}
	cout << ans;
}
```

---

## 作者：Saka_Noa (赞：1)

 考虑朴素的 DP 方程，设 $f_i$ 表示从 $1 \sim i$ 需要的最小步数。则：
 $$f_i = \min_{i-a_i < j < i} f_j+1$$  
 将这个 DP 作 $n$ 轮即可。复杂度 $O(n^3)$  
 
 对于一个 $i$，考虑优化选 $j$ 的过程。看上去每次选的 $j$ 都是一样的，发现对于可以到达的 $j$， $j - a_j$ 最小的 $j$ 是最优的。记 $i$ 可到达的其他所有点为 $k$。因为 $k$ 能到达的点 $j$ 都能到达，而 $j$ 可以到达 $k$ 不能到达的点。所以我们可以把选点过程记录下来。具体来说，使用 `ST` 表预处理出 $l,r$ 中 $k - a_k$ 最小的点。每次 $O(1)$ 查询，总复杂度 $O(n^2)$。
 
 ```
 
 #include<bits/stdc++.h>


using namespace std;

const int N = 2e6 + 500;

int n;
int a[N];
int lg[N];
int st[N][30];

int query(int l, int r) {
    int j = lg[r - l + 1];
    int sp = 1 << j;
    bool tag = a[st[l][j]] <= a[st[r - sp + 1][j]];
    return tag ? st[l][j] : st[r - sp + 1][j];
}

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) scanf("%d", &a[i]), a[i + n] = a[i]; 
    for(int i = 1; i <= n << 1; ++i) a[i] = max(1, i - a[i]);
    
    lg[0] = -1;
    for(int i = 1; i <= n << 1; ++i) lg[i] = lg[i >> 1] + 1;

    for(int i = 1; i <= n << 1; ++i) st[i][0] = i;

    for(int j = 1; j <= lg[n << 1] + 1; ++j) {
        for(int i = 1; i <= n << 1; ++i) {
            int sp = 1 << (j - 1);
            bool tag = a[st[i][j - 1]] <= a[st[i + sp][j - 1]];
            st[i][j] = tag ? st[i][j - 1] : st[i + sp][j - 1];
        }
    }

    int ans = 0;
    for(int k = 1; k <= n; ++k) {
        int i = k + n - 1, j = a[k + n - 1];
        ans++;
        while(k < j) {
            int t = query(j, i - 1); 
            i = t, j = a[t];
            //cerr << max(i, i - n) << " " << j << endl;
            ans++;
        }
    }
    printf("%d", ans);
    return 0;
}

```

---

## 作者：xiaohaoaibiancheng66 (赞：1)

# 思路
建议先阅读[弱化版题解](https://www.luogu.com.cn/blog/xiaohao-aibiancheng/solution-cf207b1)。

由于需要将最后一个放到第一个，不如把 $a$ 数组首尾相接，将其变为一个长 $2n$ 的数组：$a_1,a_2\dots a_n,a_1,\dots a_n$。问题随即变成求 $1$ 传递到 $n$、$2\sim n-1\dots n\sim 2n-1$。

对于每个 $x$，从 $x-a_x$ 接收消息肯定不是最优的，很容易举出反例。但是对于每个 $x$，**如果起点不能直接发送消息给它**，从 $y=x-a_x\sim x-1$ 中 $y-a_y$ 最小的 $y$ 接收消息肯定是最优的。

为什么？

反证法：如果有一个非 $y$ 的 $z$，有一 $k$，且 $z-a_z\le k<y-a_y$，则 $y$ 不优。但是 $y-a_y\le z-a_z$，与假设矛盾。

所以每次只需查到 $y$ 即可。运用 ST 表，可以将查询降到 $O(1)$。所以总时间复杂度为 $O(n\log n+n^2)=O(n^2)$。在本题 $n\le 10^4$，时限 $3$ 秒的情况下可以通过。
# AC code
```cpp
#include<bits/stdc++.h>
using namespace std;

int Log[1000000];
int st[600000][30];
int a[600000];

//ST 表部分
void init(int n)
{
	Log[0]=Log[1]=0;
	for(int i=2;i<=n;i++)Log[i]=Log[i/2]+1;
}

void Build(int n)
{
	for(int i=0;i<=n;i++)st[i][0]=i;
	for(int j=1;j<=Log[n]+1;j++)
		for(int i=0;i<=n;i++) 
			st[i][j]=((a[st[i][j-1]]<=a[st[i+(1<<(j-1))][j-1]])?st[i][j-1]:st[i+(1<<(j-1))][j-1]);
}

inline int Query(int l,int r)
{
	int t=Log[r-l+1];
	return (a[st[l][t]]<=a[st[r-(1<<t)+1][t]])?st[l][t]:st[r-(1<<t)+1][t];
}
	
int main()
{
	int n;
	cin>>n;
	init(2*n);
	for(int i=1;i<=n;i++)cin>>a[i],a[i+n]=a[i];
	for(int i=1;i<=n+n;i++)a[i]=max(i-a[i],1);//预处理，减少代码长度。
	Build(2*n);
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		int l=a[i+n-1],r=i+n-1,cnt=1;//如果 l<i 直接从起点发送，先把 1 加上
		while(i<l)
		{
			int t=Query(l,r-1);l=a[t],r=t;//查询，更新
			cnt++;
		}
        ans+=cnt;
	}
	cout<<ans;
	return 0;
}
```

---

