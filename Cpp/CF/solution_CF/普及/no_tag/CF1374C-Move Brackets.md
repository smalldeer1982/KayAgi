# Move Brackets

## 题目描述

You are given a bracket sequence $ s $ of length $ n $ , where $ n $ is even (divisible by two). The string $ s $ consists of $ \frac{n}{2} $ opening brackets '(' and $ \frac{n}{2} $ closing brackets ')'.

In one move, you can choose exactly one bracket and move it to the beginning of the string or to the end of the string (i.e. you choose some index $ i $ , remove the $ i $ -th character of $ s $ and insert it before or after all remaining characters of $ s $ ).

Your task is to find the minimum number of moves required to obtain regular bracket sequence from $ s $ . It can be proved that the answer always exists under the given constraints.

Recall what the regular bracket sequence is:

- "()" is regular bracket sequence;
- if $ s $ is regular bracket sequence then "(" + $ s $ + ")" is regular bracket sequence;
- if $ s $ and $ t $ are regular bracket sequences then $ s $ + $ t $ is regular bracket sequence.

For example, "()()", "(())()", "(())" and "()" are regular bracket sequences, but ")(", "()(" and ")))" are not.

You have to answer $ t $ independent test cases.

## 说明/提示

In the first test case of the example, it is sufficient to move the first bracket to the end of the string.

In the third test case of the example, it is sufficient to move the last bracket to the beginning of the string.

In the fourth test case of the example, we can choose last three openning brackets, move them to the beginning of the string and obtain "((()))(())".

## 样例 #1

### 输入

```
4
2
)(
4
()()
8
())()()(
10
)))((((())```

### 输出

```
1
0
1
3```

# 题解

## 作者：Acestar (赞：4)

**Codeforces Round #653 (Div. 3)**

C. Move Brackets

一道签到题吧。


>题意简述：给定一个括号序列，长度为 $n$ 且保证有 $\frac{n}{2}$ 个 "(" 
和 $\frac{n}{2}$ 个 ")"。每次操作可以将第 $i$ 个括号移动到这个序列的最前面或最后面，让你求出最少需要几次操作才能使输入序列变为一个合法的括号序列。输入有 $t$ 组数据。

思路就是把不合法的括号个数找出来，对于每个括号进行一次操作就可以了（当然不需要真的操作，只需要计数）。

对于找不合法的括号，我们要把序列的每一个括号枚举一遍，用 $sum$ 记录 "(" 个数减去 ")" 个数，如果小于0了，那么有一个不合法的右括号 $ans++$，这时要让 $sum=0$，继续统计后面的括号，因为这个右括号已经不合法了，不能用后面的左括号来匹配。

最后输出 $ans$ 就可以了。


```
#include<iostream>
#include<cstdio>
#include<cstring>

using namespace std;

int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		int n;
		scanf("%d",&n);
		char s[60];
		scanf("%s",s);
		int len=strlen(s),sum=0,ans=0;
		for(int i=0; i<len; i++)
		{
			if(s[i]=='(') sum++;
			else sum--;
			if(sum<0) ans++,sum=0;
		}
		printf("%d\n",ans);
	}
	return 0;
}
```


---

## 作者：Clouder (赞：1)

给一个括号序列，每次可将任意括号移至首尾，求最少步数后括号串合法。  

将左括号看做 $1$，右括号看做 $-1$，要求任意位置前缀和非负，即括号匹配。数据保证有解。  

途中某位置前缀和为 $-1$ 时，将当前右括号移至末尾，统计答案，再将前缀和归零。  

大致证明：  

当前串设为 $s_1 + ) + s_2$，其中 $s_1$ 有 $a$ 个左括号，$a$ 个右括号，那么 $s_2$ 中有 $n - 2 \times a - 1$ 个括号，其中 $(n - 2 \times a) \div 2$ 是左括号，$(n - 2 \times a) \div 2 - 1$ 是右括号，将该右括号移至末尾一定能与某左括号匹配。  

数据范围比较仁慈，把 $O(n^2)$ 做法放过去了，实际上无须真的移到末尾。

```cpp
#include <cstdio>
const int maxn = 60;
int T,n;
char s[maxn];
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %s",&n,s+1);
        int ans = 0,sum = 0;
        for(int i = 1;i<=n;++i)
        {
            sum += (s[i] == '(' ? 1 : -1);
            if(sum < 0) ++ans,sum = 0;
        }
        printf("%d\n",ans);
    }
    return 0;
}
```

---

## 作者：PanH (赞：1)

## 题意

给你一个偶数长度的括号串，一半是左括号，一半是右括号，你可以把其中一个左括号或右括号移动到最左端或最右端。求最少需要的步数使该括号串左右括号匹配。

## 做法

其实就是一般的括号匹配，先找到合法的有多少对括号，若删去它们，则剩下的括号一定是类似于这样的：``)))...(((`` 。长度除 $2$ 得到答案。

code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
char s[100005];
int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		cin>>n>>s+1;
		int sum1=0,sum2=0;
		for(int i=1;i<=n;i++)
			if(s[i]=='(')	sum1++;
			else	sum2++,sum2=min(sum1,sum2);
		cout<<n/2-sum2<<endl;
	}
}
```


---

## 作者：zdxx (赞：1)

## 题意
第一行输入一个整数 t，表示数据组数。

对于每组数据：

* 给定一个长为 n 的括号序列；

* 每次你可以选择任意一个括号，将其移至序列最左侧或最右侧；

* 保证可能使括号序列合法，求使括号序列合法的最少操作次数。

$ 1 \leqslant t \leqslant 2000 , 2 \leqslant n \leqslant 50 $。

## 思路
典型的括号匹配题。

因为题目保证可能使括号序列合法，所以`'('`和`')'`数量一定相等。

如果出现`()`的情况则不用移动，已经合法。

如果出现`)(`的情况则需将任意一个移走。

我们统计序列当前括号个数，`'('`有$l$个，`')'`有$r$个。

若这一位是`'('`则`l++`，若这一位是`')'`，如果$l>0$则此时`')'`可以和之前的`'('`匹配，$l--$。

最后输出$ r $即可。

## Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int read(){
	int a=0,x=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')x=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')a=a*10+ch-'0',ch=getchar();
	return a*x;
}
int main(){
	int t=read();
	char x;
	while(t--){
		int n,l=0,r=0;
		scanf("%d\n",&n);
		for(int i=1;i<=n;i++){
			scanf("%c",&x);
			if(x=='(')l++;
			else if(l)l--;
			else r++;
		}
		printf("%d\n",r);
	}
	return 0;
}
```


---

## 作者：45dino (赞：0)

签到题第三题

凭直觉（？）想到贪心

类似[P1739 表达式括号匹配](https://www.luogu.com.cn/problem/P1739)，设 $x$ 是左右括号的个数差，如果是左括号，```x++```，如果是右括号且 $x$ 大于 $0$ ，```x--```，如果是右括号且 $x$ 等于 $0$ ，把这个右括号移走。

反正就是如果不能匹配，就把它扔到后面，以后再说（咕咕法）

喜闻乐见的代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		string s;
		int ans=0,cnt=0,n;
		scanf("%d",&n);
		cin>>s;
		for(int i=0;i<s.size();i++)
		{
			if(s[i]=='(')
				cnt++;
			if(s[i]==')'&&cnt==0)//注意顺序，和下一步不要写反
			{
				ans++;
				s+=")";//这一步可有可无
			}
			if(s[i]==')'&&cnt>0)//注意顺序，和上一步不要写反
				cnt--;
		}
		cout<<ans<<endl;		
	}
	return 0;
}
```


---

## 作者：B_1168 (赞：0)

提供一种赛时想到的玄学方法，求大佬能帮忙证明：

对每一个括号串，维护一个同等长度的数组和一个计数器，使得：

- 初始时计数器(`cnt`)值为$0$，数组(`a[]`)各元素值一律为$0$
- 对括号串元素`s[i]`，如果`s[i]=='('`，则`cnt+=1`，同时`a[i]=cnt`
- 相似的，如果`s[i]==')'`，则`cnt-=1`，同时`a[i]=cnt`

在维护完数组后，遍历数组，求出该数组中所有负数中绝对值最大的数----如没有负数，答案默认为0----随后输出该答案

作为一种赛时想到的玄学算法，并不知道怎么证明，但是的确是能通过的

以下是Python代码（`C++`字符串相关内容有时不好写qwq）：

```python
def calc():
    l=int(input())
    s=str(input())
    a=[]
    cnt=0
    ans=0
    for i in range(0,l):
        if s[i]=='(':
            cnt+=1
            a.append(cnt)
        else:
            cnt-=1
            a.append(cnt)
    for i in range(0,l):
        if(a[i]<0):
            ans=max(ans,-a[i]);
    print(ans)
    
t=int(input())

for i in range(1,t+1):
    calc()
```

感谢管理审核，感谢大佬阅读，欢迎大佬就该解法的证明提供意见！

---

## 作者：PragmaGCC (赞：0)

如果做过[P1739](https://www.luogu.com.cn/problem/P1739)的话，这道题应该难不倒你

首先，因为`(`和`)`的数量是一样的，所以，不会出现`(()))`这种情况，也就是括号的数量不匹配。

那么，出现的只有两种情况：

1. `()`
2. `)(`

对于不匹配的情况，我们只需要将其中一个移到某一边就好了。
实际上，`(`移到左边和`)`移到右边是等价的。

将两种符号换成+1和-1，每有一个`(`代表左侧有一个待匹配括号，如果一个`)`代表匹配到了左侧的一个括号或者未匹配到。当未匹配到时，我们把ans++，代表找到了一个没有被匹配到的括号。
```
#include <bits/stdc++.h>
using namespace std;
int ans, sta;
int T, n;
char s[55];
int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        sta = ans = 0;
        cin >> n >> s;
        for (int i = 0; i < n; i++) {
            if (s[i] == '(')
                sta++;
            else{
                if(sta==0)
                    ans++;
                else
                    sta--;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
```

---

