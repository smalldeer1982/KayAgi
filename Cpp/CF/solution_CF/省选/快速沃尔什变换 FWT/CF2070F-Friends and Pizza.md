# Friends and Pizza

## 题目描述

Monocarp 有 $n$ 个披萨，第 $i$ 个披萨包含 $a_i$ 片。披萨用从 A 开始的拉丁字母大写字符表示（第 $n$ 个披萨对应第 $n$ 个拉丁字母）。

Monocarp 还有 $m$ 个朋友，他想要邀请其中恰好两人来吃披萨。对于每个朋友，Monocarp 知道该朋友喜欢哪些披萨。

当朋友到达 Monocarp 家后，每个披萨的处理方式如下：

- 如果该披萨不被任何被邀请的朋友喜欢，Monocarp 将吃掉它；
- 如果该披萨恰好被一位被邀请的朋友喜欢，该朋友将吃掉它；
- 如果该披萨被两位朋友都喜欢，他们将尝试分食。若披萨包含偶数片，两人各吃一半；若包含奇数片，他们会因争夺额外一片而发生争吵——Monocarp 不喜欢这种情况。

对于每个 $k$ 从 $0$ 到 $\sum a_i$，计算选择两个朋友的方式数，使得朋友不会争吵且 Monocarp 恰好吃掉 $k$ 片。

## 说明/提示

以第一个示例的所有朋友对为例：

- 邀请朋友 $1$ 和 $2$：他们将吃掉披萨 $1$ 和 $2$，Monocarp 吃披萨 $3$；
- 邀请朋友 $1$ 和 $3$：他们将吃掉所有披萨；
- 邀请朋友 $1$ 和 $4$：他们将吃披萨 $1$ 和 $2$，Monocarp 吃披萨 $3$；
- 邀请朋友 $1$ 和 $5$：他们将吃掉所有披萨；
- 邀请朋友 $1$ 和 $6$：他们将吃披萨 $1$ 和 $3$，Monocarp 吃披萨 $2$；
- 邀请朋友 $2$ 和 $3$：因披萨 $2$ 发生争吵；
- 邀请朋友 $2$ 和 $4$：因披萨 $2$ 发生争吵；
- 邀请朋友 $2$ 和 $5$：因披萨 $2$ 发生争吵；
- 邀请朋友 $2$ 和 $6$：他们将吃掉所有披萨；
- 邀请朋友 $3$ 和 $4$：因披萨 $2$ 发生争吵；
- 邀请朋友 $3$ 和 $5$：因披萨 $2$ 发生争吵；
- 邀请朋友 $3$ 和 $6$：因披萨 $3$ 发生争吵；
- 邀请朋友 $4$ 和 $5$：因披萨 $2$ 发生争吵；
- 邀请朋友 $4$ 和 $6$：他们将吃掉所有披萨；
- 邀请朋友 $5$ 和 $6$：因披萨 $3$ 发生争吵。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3 6
A AB ABC AB BC C
2 3 5```

### 输出

```
4 0 0 1 0 2 0 0 0 0 0```

# 题解

## 作者：wishapig (赞：2)

设第 $i$ 个人喜欢吃的蛋糕的 bitmask 为 $s[i]$，设所有奇数片蛋糕的 bitmask 为 $D$

那么能选 $i,j$ 两个人当且仅当 $s[i]\cap s[j]\cap D=0$

考虑某个 bitmask $k$ 能被哪几对 $i,j$ 得到，即求出：
$$
cnt[k]=\sum_{1\le i<j\le m}[s[i]\cap s[j]\cap D=0][s[i]|s[j]=k]
$$
这是子集卷积的变形，即：
$$
cnt[k]=\sum_{1\le i<j\le m}[(s[i]\cap D)\cap (s[j]\cap D)=0][s[i]|s[j]=k]
$$
考察正常的子集卷积的推导方式：
$$
i\cup j=k\\
i\cap j=0\Rightarrow |i|+|j|=|i\cup j|
$$
因此加上一维 popcnt，内层使用 FWT 做 or 卷积即可。

那么在这里
$$
i\cup j=k\\
i\cap j\cap D=0\Rightarrow |i\cap D|+|j\cap D|=|(i\cap D)\cup (j\cap D)|=|(i\cup j)\cap D|
$$
于是初始化时：
$$
a[\operatorname{popcnt}(i\cap D)][i]+=1
$$
在取出答案时：
$$
ans=a[\operatorname{popcnt}(i\cap D)][i]
$$
就做完了，注意要把 $i=j$ 的多算的部分减掉，再把答案除以二

时间复杂度 $O(2^n\times n^2+\sum a_i)$，空间复杂度 $O(2^n\times n)$

---

## 作者：Starrykiller (赞：2)

果然还是对 SPS 的理解不够深刻。

没有奇数片的限制怎么办？状压一下，做一个高维前缀和（FWT OR），然后自己卷上自己，再 IFWT 回去。这样会重复算选两个相同人的限制，而且一对人会被算两次，但是减掉是简单的。

如果全是奇数片怎么办？不难发现这要求 AND 不交，这就是[子集卷积](https://www.luogu.com.cn/problem/P6097)。

简述做法：考虑关键性质，若 $S\cap T=\varnothing$，有 $|S\cup T|=|S|+|T|$。于是添加占位维变成 $x^{|S|}y^{S}$，于是我们就有 $\Theta(n)$ 个长为 $2^n$ 的 SPS。对第二维做 OR 卷积，第一维做加法卷积，总时间复杂度是 $\Theta(n^22^n)$ 的。

考虑原问题，只限制奇数片的不交，把奇数片的状压成 $T$，那么我们将占位维设成 $x^{|S\cap T|}y^S$ 即可。

时间复杂度 $\Theta(n^22^n)$。

小圆抱抱/kel

---

## 作者：Purslane (赞：1)

# Solution

很简单的 *3000。

记 $S$ 为所有出现次数为奇数的披萨构成的集合。

相当于给你若干个集合 $T_i$，对于所有满足 $(T_i \cap T_j) \cap S = \varnothing $ 的二元组 $(i,j)$，统计 $T_i \cup T_j$ 的所有可能值。

发现前者的限制是啥呢，就是 $|T_i \cap S| + |T_j \cap S| = |(T_i \cap T_j) \cap S|$，这个和子集卷积的形式非常相似，那直接做就行了啊。

复杂度 $O(n^22^n)$。

φ(>ω<*)

代码非常好写：

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=20+5,MAXM=(1<<20)+10;
int n,m,a[MAXN],S,T[MAXM],mul[MAXN][MAXM],ans[MAXN][MAXM],fin[MAXM],res[MAXM]; 
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	int tot=0;
	ffor(i,1,m) {
		string S;
		cin>>S;
		for(auto ch:S) T[i]|=(1<<(ch-'A'));	
	}
	ffor(i,1,n) {cin>>a[i],tot+=a[i];if(a[i]&1) S|=(1<<i-1);}
	ffor(i,1,m) mul[__builtin_popcount(T[i]&S)][T[i]]++;
	ffor(i,0,n) ffor(j,0,n-1) ffor(k,0,(1<<n)-1) if(k&(1<<j)) mul[i][k]+=mul[i][k-(1<<j)];
	ffor(i,0,n) ffor(j,0,n-i) ffor(k,0,(1<<n)-1) ans[i+j][k]+=mul[i][k]*mul[j][k];
	ffor(i,0,n) ffor(j,0,n-1) ffor(k,0,(1<<n)-1) if(k&(1<<j)) ans[i][k]-=ans[i][k-(1<<j)];
	ffor(i,0,n) ffor(j,0,(1<<n)-1) if(i==__builtin_popcount(j&S)) fin[j]+=ans[i][j];
	ffor(i,1,m) if((T[i]&S)==0) fin[T[i]]--;
	ffor(i,0,(1<<n)-1) fin[i]/=2;
	ffor(i,0,(1<<n)-1) {
		int ot=0;
		ffor(j,1,n) if(!(i&(1<<j-1))) ot+=a[j];
		res[ot]+=fin[i];
	}
	ffor(i,0,tot) cout<<res[i]<<' ';
	return 0;
}
```

---

## 作者：PTqwq (赞：1)

首先转化一下条件，设 $a_i$ 为第 $i$ 个顾客喜欢的披萨集合，$s_i$ 为第 $i$ 个顾客喜欢的块数是奇数的披萨集合，$S$ 为所有块数是奇数的披萨集合。那么 $(i, j)$ 合法当且仅当 $s_i \cap s_j \cap S = \varnothing$。

然后观察一下可以发现条件其实与 $(s_i \cap S) \cap (s_j \cap S) = \varnothing$ 等价，那么设 $t_i = s_i \cap S$，然后我们再观察一下发现：

$$s_i \cap S = a_i \cap S$$
$$(a_i \cap S) \cup (a_j \cap S) = ((a_i \cup a_j) \cap S)$$

这样我们就可以子集卷积了，$i$ 贡献到 $F_{|a_i \cap S|, a_i}$ 然后自己卷自己，然后查询 $i$ 卷完之后的也是查询 $G_{|i \cap S|, i}$，其中第一维维护的是 $|a_i \cap S|$，第二维维护的是集合，显然当 $|a_i| + |a_j| = |a_i \cup a_j|$ 的时候两个集合无交，这样就可以根据第一维维护的东西来指定集合不交了，然后剩下的就是 OR 卷积了。

时间复杂度 $O(2^nn^2 + \sum a_i)$，可以通过。

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

namespace PTqwq {

int readqwq() {
    int x = 0;
    bool f = false;
    char c = getchar();
    for (; c < '0' || c > '9'; c = getchar()) f |= (c == '-');
    for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c - '0');
    if (f) {
        x = -x;
    }
    return x;
}

ll readllqwq() {
    ll x = 0;
    bool f = false;
    char c = getchar();
    for (; c < '0' || c > '9'; c = getchar()) f |= (c == '-');
    for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c - '0');
    if (f) {
        x = -x;
    }
    return x;
}

const int N = 5e5 + 10;

int n, m, a[N], b[40], t[N], sum, z, val[1 << 20];
ll ans[N], f[1 << 20];
char s[40];
ll valf[30][1 << 20];
ll valg[30][1 << 20];

void FWT(int x) {
    for (int i = 2; i <= (1 << n); i *= 2) {
        for (int j = 0; j < (1 << n); j += i) {
            for (int k = 0; k < i / 2; ++ k) {
                valf[x][j + k + i / 2] += valf[x][j + k];
            }
        }
    }
}

void IFWT(int x) {
    for (int i = 2; i <= (1 << n); i *= 2) {
        for (int j = 0; j < (1 << n); j += i) {
            for (int k = 0; k < i / 2; ++ k) {
                valg[x][j + k + i / 2] -= valg[x][j + k];
            }
        }
    }
}

void Solve() {
    n = readqwq();
    m = readqwq();
    sum = 0;
    for (int i = 1; i <= m; ++ i) {
        scanf("%s", s);
        int k = strlen(s);
        a[i] = 0;
        for (int j = 0; j < k; ++ j) {
            int u = s[j] - 'A';
            a[i] |= (1 << u);
        }
    }
    z = 0;
    for (int i = 0; i < n; ++ i) {
        b[i] = readqwq();
        sum += b[i];
        if (b[i] % 2 == 1) {
            z |= (1 << i);
        }
    }
    for (int i = 1; i <= m; ++ i) {
        t[i] = a[i];
        t[i] &= z;
    }

    for (int i = 0; i < (1 << n); ++ i) {
        val[i] = 0;
        for (int j = 0; j < n; ++ j) {
            if ((i >> j) & 1) {
                val[i] += b[j];
            }
        }
    }

    for (int i = 0; i <= sum + 1; ++ i) {
        ans[i] = 0;
    }
    for (int i = 0; i <= n; ++ i) {
        for (int j = 0; j < (1 << n); ++ j) {
            valf[i][j] = 0;
        }
    }
    for (int i = 1; i <= m; ++ i) {
        int cnt = 0;
        for (int j = 0; j < n; ++ j) {
            if ((t[i] >> j) & 1) {
                cnt ++;
            }
        }
        valf[cnt][a[i]] ++;
    }
    for (int i = 0; i <= n; ++ i) {
        FWT(i);
    }
    for (int i = 0; i <= n; ++ i) {
        for (int j = 0; j < (1 << n); ++ j) {
            valg[i][j] = 0;
        }
        for (int j = 0; j <= i; ++ j) {
            for (int k = 0; k < (1 << n); ++ k) {
                valg[i][k] += (valf[j][k] * valf[i - j][k]);
            }
        }
        IFWT(i);
    }
    for (int i = 0; i < (1 << n); ++ i) {
        int cnt = 0;
        for (int j = 0; j < n; ++ j) {
            if (((i & z) >> j) & 1) {
                cnt ++;
            }
        }
        f[i] = valg[cnt][i];
    }
    for (int i = 1; i <= m; ++ i) {
        if (t[i] == 0) {
            f[a[i]] --;
        }
    }
    for (int i = 0; i < (1 << n); ++ i) {
        ans[val[i]] += f[i];
    }
    for (int i = sum; i >= 0; -- i) {
        ans[i] >>= 1;
        printf("%lld%c", ans[i], ' ');
    }
    printf("\n");
}

}

int main() {
    PTqwq::Solve();

    return 0;
}
```

---

