# Messy

## 题目描述

You are fed up with your messy room, so you decided to clean it up.

Your room is a bracket sequence $ s=s_{1}s_{2}\dots s_{n} $ of length $ n $ . Each character of this string is either an opening bracket '(' or a closing bracket ')'.

In one operation you can choose any consecutive substring of $ s $ and reverse it. In other words, you can choose any substring $ s[l \dots r]=s_l, s_{l+1}, \dots, s_r $ and change the order of elements in it into $ s_r, s_{r-1}, \dots, s_{l} $ .

For example, if you will decide to reverse substring $ s[2 \dots 4] $ of string $ s= $ "((()))" it will be equal to $ s= $ "()(())".

A regular (aka balanced) bracket sequence is a bracket sequence that can be transformed into a correct arithmetic expression by inserting characters '1' and '+' between the original characters of the sequence. For example, bracket sequences "()()", "(())" are regular (the resulting expressions are: "(1)+(1)", "((1+1)+1)"), and ")(" and "(" are not.

A prefix of a string $ s $ is a substring that starts at position $ 1 $ . For example, for $ s= $ "(())()" there are $ 6 $ prefixes: "(", "((", "(()", "(())", "(())(" and "(())()".

In your opinion, a neat and clean room $ s $ is a bracket sequence that:

- the whole string $ s $ is a regular bracket sequence;
- and there are exactly $ k $ prefixes of this sequence which are regular (including whole $ s $ itself).

For example, if $ k = 2 $ , then "(())()" is a neat and clean room.

You want to use at most $ n $ operations to make your room neat and clean. Operations are applied one after another sequentially.

It is guaranteed that the answer exists. Note that you do not need to minimize the number of operations: find any way to achieve the desired configuration in $ n $ or less operations.

## 说明/提示

In the first example, the final sequence is "()(()())", where two prefixes are regular, "()" and "()(()())". Note, that all the operations except "5 8" in the example output are useless (they do not change $ s $ ).

## 样例 #1

### 输入

```
4
8 2
()(())()
10 3
))()()()((
2 1
()
2 1
)(
```

### 输出

```
4
3 4
1 1
5 8
2 2
3
4 10
1 4
6 7
0
1
1 2
```

# 题解

## 作者：wind_whisper (赞：0)

## $\text{Description}$
给出一个长度为 $n$ 的括号序列，你每次可以翻转一个区间，请在 $n$ 次操作内使序列变为合法序列且恰好有 $k$ 个前缀是合法前缀（包括本身）.  
保证存在合法解.  
$n\le2000$
## $\text{Solution}$
令前 $k-1$ 个都是 $()$ 的形状，然后填成 $(((((...)))))$ 即可.  
$n^2$ 暴力就可过.  
（预处理一些东西应该可以线性，但是懒得打了）.
## $\text{Code}$
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define debug(...) fprintf(stderr,__VA_ARGS__)
const int N=2e5+100;
inline ll read(){
  ll x(0),f(1);char c=getchar();
  while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
  while(isdigit(c)) {x=(x<<1)+(x<<3)+c-'0';c=getchar();}
  return x*f;
}
int n,m,k;
char s[N];
int l,r;
signed main(){
#ifndef ONLINE_JUDGE
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
#endif
  int T=read();
  while(T--){
    n=read();k=read();
    scanf(" %s",s+1);
    --k;int x=n/2,y=n/2;
    printf("%d\n",n);
    for(int i=1;i<=n;i++){
      if((k>0&&i%2==0)||(!x)){
	l=r=i;
	while(s[r]=='(') ++r;
	printf("%d %d\n",l,r);
	swap(s[l],s[r]);
	--k;--y;
      }
      else{
	l=r=i;
	while(s[r]==')') ++r;
	printf("%d %d\n",l,r);
	swap(s[l],s[r]);
	--x;
      }
    }
  }
  return 0;
}
/*

*/

```


---

## 作者：C锥 (赞：0)

构造体.

看到题目说最多操作 $ n $ 次, 也就是说, 你随便构造出一个符合要求的括号序列, 都可以由给定序列变过去.

我们就一个字符一个字符的匹配, 如果给定序列当前位置 $ l $ 和合法序列不一样, 那么我们就从后面位置 $ r $ 找一个和合法序列当前位置一样的, 把区间 $ [l,r] $ 倒置就好了.

这样操作次数一定不会超过 $ n $次的.(最多就有 $ n $ 个位置要交换嘛)

复杂度 $ O(n^2) $.

---

