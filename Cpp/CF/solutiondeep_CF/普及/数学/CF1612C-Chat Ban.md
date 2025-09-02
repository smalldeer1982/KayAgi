# 题目信息

# Chat Ban

## 题目描述

You are a usual chat user on the most famous streaming platform. Of course, there are some moments when you just want to chill and spam something.

More precisely, you want to spam the emote triangle of size $ k $ . It consists of $ 2k-1 $ messages. The first message consists of one emote, the second one — of two emotes, ..., the $ k $ -th one — of $ k $ emotes, the $ k+1 $ -th one — of $ k-1 $ emotes, ..., and the last one — of one emote.

For example, the emote triangle for $ k=3 $ consists of $ 5 $ messages:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1612C/2949e1c874315434d0b3c1f5e20dee7c9097dc7a.png)Of course, most of the channels have auto moderation. Auto moderator of the current chat will ban you right after you spam at least $ x $ emotes in succession (you can assume you are the only user in the chat). Now you are interested — how many messages will you write before getting banned? Or maybe you will not get banned at all (i.e. will write all $ 2k-1 $ messages and complete your emote triangle successfully)? Note that if you get banned as a result of writing a message, this message is also counted.

You have to answer $ t $ independent test cases.

## 说明/提示

Let's analyze the test cases of the example.

1. In the first test case, you write three messages containing $ 1 $ , $ 2 $ and $ 3 $ emotes respectively, and since $ 1 + 2 + 3 \ge 6 $ , you get banned after that.
2. In the second test case, you write four messages containing $ 1 $ , $ 2 $ , $ 3 $ and $ 4 $ emotes respectively, and since $ 1 + 2 + 3 + 4 \ge 7 $ , you get banned after that.
3. In the third test case, you write one message containing exactly $ 1 $ emote. It doesn't get you banned, since $ 1 < 2 $ , but you have already finished posting your emote triangle. So you wrote one message successfully.
4. In the fourth test case, you write four messages containing $ 1 $ , $ 2 $ , $ 3 $ and $ 2 $ emotes respectively, and since $ 1 + 2 + 3 + 2 \ge 7 $ , you get banned after that.
5. In the fifth test case, you write three messages containing $ 1 $ , $ 2 $ and $ 1 $ emote respectively. It doesn't get you banned, since $ 1 + 2 + 1 < 5 $ , but you have already finished posting your emote triangle. So you wrote three messages successfully.
6. In the sixth test case, since $ x = 1 $ , you get banned as soon as you send your first message.
7. The seventh test case is too large to analyze, so we'll skip it.

## 样例 #1

### 输入

```
7
4 6
4 7
1 2
3 7
2 5
100 1
1000000000 923456789987654321```

### 输出

```
3
4
1
4
3
1
1608737403```

# AI分析结果

### 题目内容重写
# Chat Ban

## 题目描述

你是一个在著名流媒体平台上聊天的普通用户。当然，有时你只想放松一下，发一些表情符号。

更具体地说，你想发送一个大小为 $k$ 的表情符号三角形。它由 $2k-1$ 条消息组成。第一条消息包含一个表情符号，第二条消息包含两个表情符号，……，第 $k$ 条消息包含 $k$ 个表情符号，第 $k+1$ 条消息包含 $k-1$ 个表情符号，……，最后一条消息包含一个表情符号。

例如，$k=3$ 时的表情符号三角形由 $5$ 条消息组成：

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1612C/2949e1c874315434d0b3c1f5e20dee7c9097dc7a.png)当然，大多数频道都有自动审核。当前聊天的自动审核器会在你连续发送至少 $x$ 个表情符号后立即封禁你。现在你感兴趣的是——在封禁之前你会发送多少条消息？或者你可能根本不会被封禁（即你会发送所有 $2k-1$ 条消息并成功完成你的表情符号三角形）？注意，如果你因为发送某条消息而被封禁，这条消息也会被计入。

你需要回答 $t$ 个独立的测试用例。

## 说明/提示

让我们分析一下示例的测试用例。

1. 在第一个测试用例中，你发送了三条消息，分别包含 $1$、$2$ 和 $3$ 个表情符号，由于 $1 + 2 + 3 \ge 6$，你在这之后被封禁。
2. 在第二个测试用例中，你发送了四条消息，分别包含 $1$、$2$、$3$ 和 $4$ 个表情符号，由于 $1 + 2 + 3 + 4 \ge 7$，你在这之后被封禁。
3. 在第三个测试用例中，你发送了一条消息，包含恰好 $1$ 个表情符号。它不会让你被封禁，因为 $1 < 2$，但你已经完成了表情符号三角形的发送。所以你成功发送了一条消息。
4. 在第四个测试用例中，你发送了四条消息，分别包含 $1$、$2$、$3$ 和 $2$ 个表情符号，由于 $1 + 2 + 3 + 2 \ge 7$，你在这之后被封禁。
5. 在第五个测试用例中，你发送了三条消息，分别包含 $1$、$2$ 和 $1$ 个表情符号。它不会让你被封禁，因为 $1 + 2 + 1 < 5$，但你已经完成了表情符号三角形的发送。所以你成功发送了三条消息。
6. 在第六个测试用例中，由于 $x = 1$，你发送第一条消息后立即被封禁。
7. 第七个测试用例太大，无法分析，所以我们跳过它。

## 样例 #1

### 输入

```
7
4 6
4 7
1 2
3 7
2 5
100 1
1000000000 923456789987654321```

### 输出

```
3
4
1
4
3
1
1608737403```

### 题解分析与结论

本题的核心在于如何高效地计算在发送表情符号三角形时，何时会被封禁。由于数据范围较大（$k \leq 10^9$，$x \leq 10^{18}$），暴力解法显然不可行。因此，大多数题解采用了二分查找的方法，利用等差数列求和公式来快速计算前 $n$ 行的表情符号总数。

### 评分较高的题解

#### 题解作者：Jur_Cai (评分：4星)
- **关键亮点**：该题解清晰地使用了二分查找，并且通过分类讨论（前 $k$ 行和后 $k-1$ 行）来简化问题。代码结构清晰，逻辑严谨。
- **代码核心思想**：通过二分查找确定在发送多少条消息后会被封禁。前 $k$ 行的表情符号总数可以通过等差数列求和公式计算，后 $k-1$ 行的总数则通过类似的方法计算。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main() {
	int T;
	scanf("%lld",&T);
	while(T--) {
		long long k,x;
		scanf("%lld%lld",&k,&x);
		if(x>=(k+1)*k/2+k*(k-1)/2) cout<<k*2-1<<'\n';
		else {
			if(x==k*(k+1)/2) cout<<k<<'\n';
			else if(x<k*(k+1)/2) {
				int l=1,r=k,ans=1;
				while(l<=r) {
					int mid=(l+r)>>1;
					if((1+mid)*mid/2==x) {
						ans=mid;
						break;
					} else if((1+mid)*mid/2>x) {
						ans=mid;
						r=mid-1;
					} else l=mid+1;
				}
				cout<<ans<<'\n';
			} else {
				int l=1,r=k-1,ans=1;
				x-=k*(k+1)/2;
				while(l<=r) {
					int mid=(l+r)>>1;
					if((k-1+mid)*(k-mid)/2==x) {
						ans=mid;
						break;
					} else if((k-1+mid)*(k-mid)/2>x) {
						ans=mid;
						l=mid+1;
					} else r=mid-1;
				}
				cout<<k+k-ans<<'\n';
			}
		}
	}
	return 0;
}
```

#### 题解作者：Lijunzhuo (评分：4星)
- **关键亮点**：该题解同样使用了二分查找，并且通过分类讨论（前 $k$ 行和后 $k-1$ 行）来简化问题。代码结构清晰，逻辑严谨。
- **代码核心思想**：通过二分查找确定在发送多少条消息后会被封禁。前 $k$ 行的表情符号总数可以通过等差数列求和公式计算，后 $k-1$ 行的总数则通过类似的方法计算。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long T,n,k,sum,ans,w,l,r,mid;
long long dengcha(long long l,long long r){return (l+r)*(r-l+1)/2;}
long long da(long long l)
{
    long long t=dengcha(1,l);
    if(l>n)
    {
    	l-=n;
		w=dengcha(n-l,n-1);
        t=dengcha(1,n)+w;
    }
	return t;
}
bool cmp(long long l)
{
	return da(l)<=k;
}
int main()
{
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld%lld",&n,&k);
		if(n*n<=k)
		{
			printf("%lld\n",2*n-1);
			continue;
		}
		l=0;
		r=2*n;
		while(l+1<r)
		{
			mid=(l+r)>>1;
			if(cmp(mid))
			{
				ans=mid;
				l=mid;
			}else r=mid;
		}
		printf("%lld\n",da(ans)<k?ans+1:ans);
	}
	return 0;
}
```

### 最优关键思路与技巧
- **二分查找**：由于问题的单调性，二分查找是解决此类问题的有效方法。
- **等差数列求和**：通过等差数列求和公式快速计算前 $n$ 行的表情符号总数。
- **分类讨论**：将问题分为前 $k$ 行和后 $k-1$ 行两种情况，简化计算。

### 可拓展之处
- **类似问题**：可以应用于其他需要快速计算区间和的问题，如区间最大子段和、区间最小值等。
- **优化思路**：在处理大数据范围时，二分查找和数学公式的结合是常见的优化手段。

### 推荐题目
1. [P1020 导弹拦截](https://www.luogu.com.cn/problem/P1020)
2. [P1045 最大子段和](https://www.luogu.com.cn/problem/P1045)
3. [P1083 借教室](https://www.luogu.com.cn/problem/P1083)

### 个人心得摘录
- **调试经历**：在处理二分查找时，边界条件的处理非常重要，稍有不慎就会导致错误。
- **踩坑教训**：在计算等差数列和时，要注意数据类型的溢出问题，使用 `long long` 可以有效避免。

---
处理用时：63.17秒