# Unusual Competitions

## 题目描述

A bracketed sequence is called correct (regular) if by inserting "+" and "1" you can get a well-formed mathematical expression from it. For example, sequences "(())()", "()" and "(()(()))" are correct, while ")(", "(()" and "(()))(" are not.

The teacher gave Dmitry's class a very strange task — she asked every student to come up with a sequence of arbitrary length, consisting only of opening and closing brackets. After that all the students took turns naming the sequences they had invented. When Dima's turn came, he suddenly realized that all his classmates got the correct bracketed sequence, and whether he got the correct bracketed sequence, he did not know.

Dima suspects now that he simply missed the word "correct" in the task statement, so now he wants to save the situation by modifying his sequence slightly. More precisely, he can the arbitrary number of times (possibly zero) perform the reorder operation.

The reorder operation consists of choosing an arbitrary consecutive subsegment (substring) of the sequence and then reordering all the characters in it in an arbitrary way. Such operation takes $ l $ nanoseconds, where $ l $ is the length of the subsegment being reordered. It's easy to see that reorder operation doesn't change the number of opening and closing brackets. For example for "))((" he can choose the substring ")(" and do reorder ")()(" (this operation will take $ 2 $ nanoseconds).

Since Dima will soon have to answer, he wants to make his sequence correct as fast as possible. Help him to do this, or determine that it's impossible.

## 说明/提示

In the first example we can firstly reorder the segment from first to the fourth character, replacing it with "()()", the whole sequence will be "()()())(". And then reorder the segment from the seventh to eighth character, replacing it with "()". In the end the sequence will be "()()()()", while the total time spent is $ 4 + 2 = 6 $ nanoseconds.

## 样例 #1

### 输入

```
8
))((())(```

### 输出

```
6```

## 样例 #2

### 输入

```
3
(()```

### 输出

```
-1```

# 题解

## 作者：tommymio (赞：3)

思路非常简单，借助两条性质解决。

- 一个子串重排后是一个合法的括号串，那么这个子串内的左括号数一定等于右括号数.
- 对于一对匹配的括号$[L,R]$，如果$[1,L-1]$的子串重排后合法且$[R+1,N]$的子串重排后也合法，那么将这对括号匹配而不重排一定是最优策略.

考虑实现，借助栈匹配括号并判断其是否合法，合法则从答案中减去这对括号的贡献，预处理前缀和，时间复杂度为$O(n)$.

```
#include<cstdio>
int top=0;
int st[1000005],sum[1000005];
char a[1000005];
int main() {
	int n,res;
	scanf("%d%s",&n,a+1);
	res=n;
	for(register int i=1;i<=n;++i) {
		if(a[i]=='(') sum[i]=sum[i-1]+1;
		else sum[i]=sum[i-1]-1;
	}
	if(sum[n]!=0) {printf("-1\n");return 0;}
	for(register int i=1;i<=n;++i) {
		if(a[i]=='(') {st[++top]=i;}
		else if(top) {
			if(sum[st[top]-1]==0&&sum[n]-sum[i]==0) res-=i-st[top]+1;
			--top;
		}
	}
	printf("%d\n",res);
	return 0;
}
```


---

## 作者：sycqwq (赞：2)

估计放反了，这能当2C？

说题意：

有一个括号串，要让括号全部匹配，至少要改变几个括号的位置？如果不能全部匹配，则输出-1


说思路：

这就是个括号匹配。。。首先，扫一遍看左括号和有括号是否相等，不相等直接输出-1。

再观察（此时左括号和右括号数量相同），找到一个没匹配上的右括号，++ans，++r（ans为答案，r为没匹配上的右括号的数量），然后到下一个左括号时，--r，++ans，说明交换位置，少了一个没匹配上的。

剩下的按括号匹配问题即可

代码：

```cpp
#include<bits/stdc++.h>
#define inf 2147283647
using namespace std;
int ans,l,r;
int main(){
    int n;
    cin>>n;
    string s;
    cin>>s;
    int l1=s.size();
    for(int i=0;i<l1;i++)
    {
        if(s[i]=='(')
            ++l;
        if(s[i]==')')
            ++r;
    }
    if(l!=r)
    {
        cout<<-1;
        return 0;
    }
    l=0,r=0;
    for(int i=0;i<l1;i++)
    {
        if(s[i]==')')
        {
            if(l==0)//如果前面没有'('就没有匹配上
            {
                ++r;
                ++ans;
            }
            else//有的话，左括号--
                --l;
        }
        if(s[i]=='(')
        {
            if(r==0)//没有没匹配上的右括号，正常
            {
                ++l;
            }
            else//否则交换
            {
                --r;
                ++ans;
            }
        }
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：xht (赞：1)

前缀和一下，从前缀和为 $0$ 的位置将序列分成若干段。

对于每一段，如果它是负的，则这一段必须要重排，否则不用。

```cpp
const int N = 1e6 + 7;
int n, c[2], a[N], ans;
char s[N];

int main() {
	rd(n), rds(s, n);
	for (int i = 1; i <= n; i++)
		if (s[i] == '(') c[0]++;
		else c[1]++;
	if (c[0] != c[1]) return print(-1), 0;
	for (int i = 1, p = 0; i <= n; i++) {
		if (s[i] == '(') a[i] = a[i-1] + 1;
		else a[i] = a[i-1] - 1;
		if (!a[i]) {
			bool ok = 0;
			for (int j = p + 1; j <= i; j++)
				if (a[j] < 0) ok = 1;
			if (ok) ans += i - p;
			p = i;
		}
	}
	print(ans);
	return 0;
}
```


---

## 作者：VinstaG173 (赞：0)

感觉这场的 2B 和 1A 放反了（平衡难度？

很容易想到我们每次重排一定是将一个括号数可以匹配的区间重排，并且这个区间原先不匹配。

因此我们令 `(` 为 $1$， `)` 为 $-1$，则这个区间的任意前缀和$<=0$ 且只有整个区间的和 $=0$。

于是我们只要扫一遍，出现前缀和 $<0$ 时标记， $=0$ 时处理并解除标记，就可以在 $O(n)$ 时间内解决了。

具体看代码。

```cpp
#include<cstdio>
int n;
char s[1000007];
int sum,ans,flg,lst=-1;
int main()
{
	scanf(" %d %s",&n,s);
	for(int i=0;i<n;++i)
	{
		if(s[i]=='(')++sum;
		else --sum;
		if(sum<0)flg=1;//标记
		else if(sum==0)
		{
			if(flg)ans+=i-lst;//该区间需要重排
			lst=i;flg=0;//解除标记，存储新左端点
		}
	}
	if(sum)printf("-1");//不可能匹配
	else printf("%d\n",ans);
	return 0;
}
```

---

