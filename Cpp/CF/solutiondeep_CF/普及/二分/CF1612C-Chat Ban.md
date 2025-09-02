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

你是一个在著名直播平台上的普通聊天用户。当然，有些时候你只是想放松一下，发一些表情符号。

更具体地说，你想发送一个大小为 $k$ 的表情符号三角形。它由 $2k-1$ 条消息组成。第一条消息包含一个表情符号，第二条消息包含两个表情符号，……，第 $k$ 条消息包含 $k$ 个表情符号，第 $k+1$ 条消息包含 $k-1$ 个表情符号，……，最后一条消息包含一个表情符号。

例如，$k=3$ 时的表情符号三角形由 $5$ 条消息组成：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1612C/2949e1c874315434d0b3c1f5e20dee7c9097dc7a.png)

当然，大多数频道都有自动审核功能。当前聊天的自动审核系统会在你连续发送至少 $x$ 个表情符号后立即封禁你。现在你感兴趣的是，在被封禁之前你会发送多少条消息？或者你可能根本不会被封禁（即发送完所有 $2k-1$ 条消息并成功完成表情符号三角形）？注意，如果你在发送某条消息后被封禁，这条消息也会被计入。

你需要回答 $t$ 个独立的测试用例。

### 题解分析与结论

这些题解主要采用了二分查找和数学公式推导的方法来解决该问题。二分查找的思路是通过判断在某个消息数量下是否满足表情符号总数大于等于 $x$，从而找到被封禁前的最大消息数量。数学公式推导则是通过等差数列求和公式来计算前 $n$ 行和后 $n-1$ 行的表情符号总数，从而直接求解。

### 所选高星题解

#### 1. 作者：Jur_Cai (4星)

**关键亮点：**
- 使用二分查找，分别在前 $k$ 行和后 $k-1$ 行进行二分，思路清晰。
- 代码结构简洁，易于理解。

**代码实现：**
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

#### 2. 作者：DaiRuiChen007 (4星)

**关键亮点：**
- 通过分类讨论，分别处理前 $n$ 行和后 $n-1$ 行的情况，逻辑严谨。
- 使用二分查找优化了时间复杂度。

**代码实现：**
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline bool judge1(int x,int l) {
    return x*(x-1)/2<l;
}
inline int query1(int x) {
    int r=1e9+10,l=1;
    while(l<=r) {
        int mid=(l+r)>>1;
        if(judge1(mid,x)) {
            l=mid+1;
        } else {
            r=mid-1;
        }
    }
    return r;
}
inline bool judge2(int x,int l) {
    return x*(x-1)/2<=l;
}
inline int query2(int x) {
    int r=1e9+1,l=1;
    while(l<=r) {
        int mid=(l+r)>>1;
        if(judge2(mid,x)) {
            l=mid+1;
        } else {
            r=mid-1;
        }
    }
    return r-1;
}
inline int solve(int k,int x) {
    int a=k*(k+1)/2;
    if(a==x) return k;
    if(k*k<=x) return k+k-1;
    if(a>x) {
        int q=query1(x);
        return q;
    } else {
        int s=k*k;
        int q=query2(s-x);
        return k+k-1-q;
    }
}
signed main() {
    int t;
    scanf("%lld",&t);
    while(t--) {
        int k,x;
        scanf("%lld%lld",&k,&x);
        printf("%lld\n",solve(k,x));
    }
    return 0;
}
```

#### 3. 作者：断清秋 (4星)

**关键亮点：**
- 通过分类讨论前 $k$ 行和后 $k-1$ 行的情况，思路清晰。
- 使用二分查找优化了时间复杂度。

**代码实现：**
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

1. **二分查找**：通过二分查找快速定位被封禁前的最大消息数量，时间复杂度为 $O(\log k)$。
2. **分类讨论**：将问题分为前 $k$ 行和后 $k-1$ 行两种情况，分别计算表情符号总数。
3. **等差数列求和公式**：利用等差数列求和公式快速计算前 $n$ 行和后 $n-1$ 行的表情符号总数。

### 可拓展之处

类似的问题可以扩展到其他形状的图案，如矩形、菱形等，同样可以通过二分查找和数学公式推导来解决。

### 推荐相似题目

1. [P1020 导弹拦截](https://www.luogu.com.cn/problem/P1020)
2. [P1044 栈](https://www.luogu.com.cn/problem/P1044)
3. [P1059 明明的随机数](https://www.luogu.com.cn/problem/P1059)

### 个人心得总结

- **调试经历**：在处理二分查找时，边界条件的处理非常重要，稍有不慎就会导致错误。
- **踩坑教训**：在计算等差数列和时，要注意公式的正确性，避免因公式错误导致计算结果不准确。
- **顿悟感想**：通过分类讨论和二分查找的结合，可以高效解决复杂的问题，提升代码的效率和可读性。

---
处理用时：67.22秒