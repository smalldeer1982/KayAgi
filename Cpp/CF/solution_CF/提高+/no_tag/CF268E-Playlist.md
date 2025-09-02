# Playlist

## 题目描述

Manao's friends often send him new songs. He never listens to them right away. Instead, he compiles them into a playlist. When he feels that his mind is open to new music, he opens the playlist and starts to listen to the songs.

Of course, there are some songs that Manao doesn't particuarly enjoy. To get more pleasure from the received songs, he invented the following procedure of listening to the playlist:

- If after listening to some song Manao realizes that he liked it, then he remembers it and starts to listen to the next unlistened song.
- If after listening to some song Manao realizes that he did not like it, he listens to all the songs he liked up to this point and then begins to listen to the next unlistened song.

For example, if Manao has four songs in the playlist, A, B, C, D (in the corresponding order) and he is going to like songs A and C in the end, then the order of listening is the following:

1. Manao listens to A, he likes it, he remembers it.
2. Manao listens to B, he does not like it, so he listens to A, again.
3. Manao listens to C, he likes the song and he remembers it, too.
4. Manao listens to D, but does not enjoy it and re-listens to songs A and C.

That is, in the end Manao listens to song A three times, to song C twice and songs B and D once. Note that if Manao once liked a song, he will never dislike it on a subsequent listening.

Manao has received $ n $ songs: the $ i $ -th of them is $ l_{i} $ seconds long and Manao may like it with a probability of $ p_{i} $ percents. The songs could get on Manao's playlist in any order, so Manao wants to know the maximum expected value of the number of seconds after which the listening process will be over, for all possible permutations of the songs in the playlist.

## 说明/提示

Consider the first test case. If Manao listens to the songs in the order in which they were originally compiled, the mathematical expectation will be equal to 467.5 seconds. The maximum expected value is obtained by putting the first song at the end of the playlist.

Consider the second test case. The song which is 360 seconds long should be listened to first. The song 300 seconds long which Manao will dislike for sure should be put in the end.

## 样例 #1

### 输入

```
3
150 20
150 50
100 50
```

### 输出

```
537.500000000
```

## 样例 #2

### 输入

```
4
300 0
300 50
240 50
360 80
```

### 输出

```
2121.000000000
```

# 题解

## 作者：Tarsal (赞：1)

## 题目大意：

有 $n$ 首长度为 $l[i]$ 的歌，每首歌 $\text{Manao}$ 有 $ p[i]$ 的概率喜欢。在听歌时，若 $\text{Manao}$ 听到了一首不喜欢的歌他会再听完这首歌后返回去听之前所有喜欢的歌。问 $\text{Manao}$ 听完这 $n$ 首歌的时间期望最大是多少。听歌的顺序由我们来安排。

## 题解

大概也是一个简单的贪心？

因为题目是要我们构造这个序列满足总期望最大。

先考虑最简单的情况，如果只有 $2$ 首歌，他们的长度，概率分别为 $l_a, l_b, p_a$ 和 $p_b$。

这个时候我们使得后面那首歌更加的容易被人误解即好。

那么他们的期望就是 $l_a \times p_a \times (1 - p_b$ 和 $l_b \times p_b \times (1 - p_a)$。

这时候取最大值就行了。

只要以这个为条件去排序就行了。

那么构造出了方案以后，应该怎么去求最后的期望和?

把前面累加一下，记录一下，因为单调性可以显然的证出来。

也就是 :

$$(\sum_{i = 1}^{n}{l_i \times p_i}) \times (1 - p_k)$$

## 代码

代码也很好实现。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define Rep(x, a, b) for(int x = a; x <= b; ++ x)
#define Dep(x, a, b) for(int x = a; x >= b; -- x)
#define Next(i, x) for(int i = head[x]; i ; i = e[i].nxt)
int read() {
    char c = getchar(); int x = 0, f = 1;
    while(c < '0' || c > '9') { if(c == '-') f = -1; c = getchar();}
    while(c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * f;
}
const int maxn = 50005;
const int maxm = 1 << 22;
const int Max = (1 << 22) - 1;
const int XRZ = 998244353;
struct node { double l, p;} a[maxn]; double tmp, ans;
bool cmp(node a, node b) { return a.l * a.p * (1 - b.p) - b.l * b.p * (1 - a.p) > 1e-9;}
signed main() { int n = read();
	Rep(i, 1, n) scanf("%lf%lf", &a[i].l, &a[i].p), a[i].p /= 100.0, ans += a[i].l;
	sort(a + 1, a + n + 1, cmp);
    Rep(i, 1, n) ans += tmp * (1 - a[i].p), tmp += a[i].l * a[i].p;
	printf("%.9lf\n", ans);
	return 0;
}
```

---

