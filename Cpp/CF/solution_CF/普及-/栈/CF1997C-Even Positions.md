# Even Positions

## 题目描述

Monocarp had a regular bracket sequence $ s $ of length $ n $ ( $ n $ is even). He even came up with his own way to calculate its cost.

He knows that in a regular bracket sequence (RBS), each opening bracket is paired up with the corresponding closing bracket. So he decided to calculate the cost of RBS as the sum of distances between pairs of corresponding bracket pairs.

For example, let's look at RBS (())(). It has three pairs of brackets:

- (\_\_)\_\_: the distance between brackets at position $ 1 $ and at $ 4 $ is $ 4 - 1 = 3 $ ;
- \_()\_\_\_: the distance is $ 3 - 2 = 1 $ ;
- \_\_\_\_(): the distance is $ 6 - 5 = 1 $ .

 So the cost of (())() is $ 3 + 1 + 1 = 5 $ .Unfortunately, due to data corruption, Monocarp lost all characters on odd positions $ s_1, s_3, \dots, s_{n-1} $ . Only characters on even positions ( $ s_2, s_4, \dots, s_{n} $ ) remain. For example, (())() turned to \_(\_)\_).

Monocarp wants to restore his RBS by placing brackets on the odd positions. But since the restored RBS may not be unique, he wants to choose one with minimum cost. It's too hard to do for Monocarp alone, so can you help him?

Reminder: A regular bracket sequence is a string consisting of only brackets, such that this sequence, when inserted 1-s and +-s, gives a valid mathematical expression. For example, (), (()) or (()())() are RBS, while ), ()( or ())(() are not.

## 说明/提示

In the first test case, it's optimal to make $ s $ equal to (())(). The cost of $ s $ will be equal to $ 3 + 1 + 1 = 5 $ .

In the second test case, the only option is to make $ s $ equal to () with cost $ 1 $ .

In the third test case, the only possible RBS is ()()()() with cost $ 1 + 1 + 1 + 1 = 4 $ .

In the fourth test case, it's optimal to make $ s $ equal to (())(()) with cost $ 3 + 1 + 3 + 1 = 8 $ .

## 样例 #1

### 输入

```
4
6
_(_)_)
2
_)
8
_)_)_)_)
8
_(_)_(_)```

### 输出

```
5
1
4
8```

# 题解

## 作者：__Alexander__ (赞：9)

## 思路

这道题属于一道贪心题。

让我们来想想怎么贪心。

首先，我们需要明确一点：构成 $()()()$ 所需的代价是小于构成 $((()))$ 的代价的。

由此，不难得出：

**想要代价尽量小，就需要将右括号尽量靠近左括号。**

也就是说，**从前往后扫时 如果能放右括号，就不放左括号。**

OK，这道题你切了。

代码中用了栈维护括号序列，详情见代码。


```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int _;
char c;
signed main()
{
	scanf("%lld", &_);
	while (_--)
	{
		int n, res = 0;
		scanf("%lld", &n);
		getchar();
		stack<int> st;
		for (int i = 1; i <= n; i++)
		{
			c = getchar();
			if (c == '_')
			{
				if (!st.empty())
				{
					res += i - st.top();
					st.pop();
				}
				else
					st.push(i);
			}
			else if (c == '(')
			{
				st.push(i);
			}
			else
			{
				res += i - st.top();
				st.pop();
			}
		}
		printf("%lld\n", res);
	}
	return 0;
}
```

---

## 作者：CashCollectFactory (赞：6)

注意到，对于任意的 $i \in s$，若 $s_i$ 为待定项，且该项左方有至少一个（到第 $i$ 位为止）未匹配的左括号，则在第 $i$ 位填写右括号可以尽可能大地提前未匹配左括号的“代价”。

由此，我们不难想出这样的贪心策略：能放右括号就放右括号，放不了再放左括号。

根据这个贪心策略补全 $s$ 后，我们就可以直接统计其总代价了。注意到，总代价为所有右括号下标减去左括号下标之和。我们可以分别单独统计左括号下标和与右括号下标和，即可轻松得到答案。

具体实现细节可以参考下方代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int main(){
	int n,T;
	string s;
	cin>>T;
	while(T--){ //多组数据
		ll ans=0;
		int cnt=0;
		cin>>n;
		cin>>s;
		for(int i=0;i<n;i++){
			if(s[i]=='_'){ //贪心补全字符串
				if(cnt==0){
					 s[i]='(';
					 cnt++;
					 continue;
				}
				if(cnt>0){
					s[i]=')';
					cnt--;
					continue;
				}
			}
      //接下来统计总答案
			if(s[i]!='_'){
				if(s[i]=='(') cnt++;
				else cnt--;
			}
		}
		for(int i=0;i<n;i++){
			if(s[i]=='(') ans-=i;
			else ans+=i;
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

~~如果帮到了你，还请点个赞~~

如果哪里有不理解的地方欢迎评论，$2025$ 年以前的评论我看到了的话一定随时答复。

---

## 作者：cfkk (赞：3)

先甩个结论：如果序列中有 $a$ 个左括号，那么答案为 $2a+\dfrac{n}{2}$。

以 $n=8$ 为例。

首先，总距离最小的一定是 `()()()()`。

然后，如果 `(` 不在奇数点，就一定会出现下种情况 `(())`，并且此时，答案会增加 $2$。

因为题目中给出的是在偶数点的括号，所以直接算多出去的部分即可。


```cpp
signed main()
{
    int T=read();
    while(T--)
    {
        int n=read(),cnt=0;
        for(int i=1;i<=n;i++)
        {
            char ch;
            cin>>ch;
            if(ch=='(')cnt++;
        }
        print(n/2+cnt*2);pc(1);
    }
	return 0;
}
```

---

## 作者：2huk (赞：2)

**题意**：有一个匹配的括号序列，只给出了偶数位置的括号。你需要将奇数位置填满，使得每对匹配括号的距离和最小。

**做法**：显然将左括号尽量靠右放更优。我们用栈模拟括号匹配，当不得不放左括号（原串这个位置确定是左括号；或这个位置不确定，且此时栈为空）时，放左括号。否则放右括号。

<https://codeforces.com/contest/1997/submission/273513089>

---

## 作者：Heldivis (赞：1)

## CF1997C

非常奇妙的贪心题目。

容易发现如果可以填入右括号，那么一定填入右括号，否则一定不优。因为该右括号所匹配的左括号一定要在后边匹配，越早匹配越好；且这个位置填左括号一定向后匹配，不如以后再填。维护一个栈记录左括号的位置即可。时间复杂度是线性的。

代码：

```cpp
void Main() {
  n = read(), sum = 0;
  scanf("%s", a + 1);
  for (int i = 1; i <= n; ++i) {
    if (a[i] == '_') {
      if (st.size())
        sum += i - st.back(), st.pop_back();
      else
        st.push_back(i);
    } else {
      if (a[i] == '(')
        st.push_back(i);
      else
        sum += i - st.back(), st.pop_back();
    }
  }
  printf("%lld\n", sum);
}
```

---

## 作者：_O_v_O_ (赞：0)

首先，我们注意到如果没有空位，那么我们就可以直接用一种类似括号匹配的做法来做。

那么有空位呢？我们注意到，如果到空位了：

- 如果括号匹配的栈为空，那么就直接将当前的字符变为 `(`；
- 否则就变为 `)`。

为什么是正确的呢？我们注意到，空位全在奇数上，那么我们就会发现，这种方法都会令一个奇数与一个偶数匹配，所以正确性显然。

---

## 作者：tzzl3035 (赞：0)

# CF1997C 题解
### 题目大意
有 $t$ 组数据，每组给出一个正整数 $n$，$n$ 一定为偶数。接着给出一行长度为 $n$ 的缺失的括号序列，序列的第奇数个用 `_` 代替，表示缺失的位置。定义括号序列的成本为序列中每对括号间的距离之和。请将 `_` 替换为括号，使得括号序列合法且成本最低，输出最小成本。
### 大致思路
括号类题目，离不开栈。且要成本最小，离不开贪心。所以，碰到正常括号，正常处理；碰到缺失的，如果栈为空，按左括号处理，否则按右括号处理即可。
### 核心代码
```cpp
void solve() {
  // 输入
  int n; std::cin >> n;
  std::string s;
  std::cin >> s;
  std::stack<int> st;
  int ans = 0;
  s = " " + s;
  // 计算答案
  for(int i = 1; i <= n; ++i) {
    if(i & 1) {
      if(st.empty()) st.push(i);
      else {
        ans += i - st.top();
        st.pop();
      }
    }
    else {
      if(s[i] == '(') st.push(i);
      else {
        ans += i - st.top();
        st.pop();
      }
    }
  }
  // 输出
  std::cout << ans << '\n';
}

```
### [RESULT](https://codeforces.com/contest/1997/submission/273535762)

---

