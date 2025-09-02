# Buy the String

## 题目描述

You are given four integers $ n $ , $ c_0 $ , $ c_1 $ and $ h $ and a binary string $ s $ of length $ n $ .

A binary string is a string consisting of characters $ 0 $ and $ 1 $ .

You can change any character of the string $ s $ (the string should be still binary after the change). You should pay $ h $ coins for each change.

After some changes (possibly zero) you want to buy the string. To buy the string you should buy all its characters. To buy the character $ 0 $ you should pay $ c_0 $ coins, to buy the character $ 1 $ you should pay $ c_1 $ coins.

Find the minimum number of coins needed to buy the string.

## 说明/提示

In the first test case, you can buy all characters and pay $ 3 $ coins, because both characters $ 0 $ and $ 1 $ costs $ 1 $ coin.

In the second test case, you can firstly change $ 2 $ -nd and $ 4 $ -th symbols of the string from $ 1 $ to $ 0 $ and pay $ 2 $ coins for that. Your string will be $ 00000 $ . After that, you can buy the string and pay $ 5 \cdot 10 = 50 $ coins for that. The total number of coins paid will be $ 2 + 50 = 52 $ .

## 样例 #1

### 输入

```
6
3 1 1 1
100
5 10 100 1
01010
5 10 1 1
11111
5 1 10 1
11111
12 2 1 10
101110110101
2 100 1 10
00```

### 输出

```
3
52
5
10
16
22```

# 题解

## 作者：zhenliu (赞：1)

## 题意简述
- 给一个长度为 $n$ 的 $01$ 字符串，买一个 $0$ 要花 $c_0$ ，买一个 $1$ 要花 $c_1$ 。

- $0$ 、 $1$ 互相转换的花费为 $h$ 。

- 求最小花费。

## 思路
直接比较 $c_1$ 与 $c_0$ $+$ $h$ ，$c_0$ 与 $c_1$ $+$ $h$，从而决定要不要把 $1$ 变为 $0$ ，或把 $0$ 变为 $1$ 。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,c0,c1,h,n;
char c;
int main(){
	scanf("%d",&T);
	while(T--){
		int ans=0;
		scanf("%d %d %d %d",&n,&c0,&c1,&h);
		c=getchar();//把换行符读掉 
		for(int i=1;i<=n;i++){
			c=getchar();
			if(c=='0')ans+=min(c0,h+c1);//比较 
			else ans+=min(c1,h+c0);
		}
		printf("%d\n",ans);
	}
	return 0;
} 
```



---

## 作者：PragmaGCC (赞：1)

作为 Div2 的 A，还是比较 easy 的。

我们可以思考这样一个问题：为什么我们要自己做饭吃？因为我们买菜 + 做菜所耗费的钱总是远小于出去吃餐馆所花的钱。

同理，如果我们把1变成0再买所需要的钱仍然小于买1的钱，那么我们直接把所有1变成0即为最少花费。0->1同理。


而如果无论怎么换都会使总花费增加，那就直接买就可以了。

所以这道题就是一个分类讨论，加一点贪心思想。

```cpp
#include <cstdio>
int read() {
    register int n = 0;
    register char ch = getchar();
    bool f = 1;
    while (ch < '0' || ch > '9') {
        if (ch == '-')
            f = 0;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        n = (n << 3) + (n << 1) + (ch ^ '0');
        ch = getchar();
    }
    return f ? n : -n;
}
char str[1005];
void work() {
    int n = read(), c0 = read(), c1 = read(), k = read();
    scanf("%s", str + 1);
    int tot = 0;
    if (c0 + k < c1) {
        for (int i = 1; i <= n; i++)
            if (str[i] == '1')
                tot++;
        printf("%d\n", c0 * n + tot * k);
    } else if (c1 + k < c0) {
        for (int i = 1; i <= n; i++)
            if (str[i] == '0')
                tot++;
        printf("%d\n", c1 * n + tot * k);
    } else {
        int ans = 0;
        for (int i=1; i<=n; i++) {
            if (str[i] == '0') ans += c0;
            else ans += c1;
        }
        printf("%d\n", ans);
    }
}
int main(void) {
    int T = read();
    while (T--)
        work();
    return 0;
}
```

---

## 作者：Eason_AC (赞：1)

## Content
有 $t$ 组询问，每组询问给出一个长度为 $n$ 的 $0/1$ 串，你可以花 $h$ 的代价把 $0$ 修改成 $1$ 或者把 $1$ 修改成 $0$，也可以花 $c_x$ 的代价删除一个 $x\in[0,1]$。求使得 $0/1$ 串为空的最小代价。

**数据范围：$1\leqslant t\leqslant 10,1\leqslant n,c_0,c_1,h\leqslant 1000$。**
## Solution
设 $x$ 在字符串中出现的次数为 $cnt_x$，那么我们很明显地发现，把所有的 $0$ 删掉的最小代价是 $c_0\times\min(cnt_0,cnt_1+h)$，把所有的 $1$ 删掉的最小代价是 $c_1\times\min(cnt_1,cnt_0+h)$。为什么呢？因为你要把所有的 $0$ 改成 $1$ 或者把所有的 $1$ 改成 $0$，都需要额外的代价，所以我们取最小值就可以使得代价最小。
## Code
```cpp
int t, n, c0, c1, h, a[1007];

int main() {
	t = Rint;
	while(t--) {
		n = Rint, c0 = Rint, c1 = Rint, h = Rint;
		int cnt0 = 0, cnt1 = 0, ans = 0;
		F(i, 1, n) {scanf("%1d", &a[i]); cnt0 += (a[i] == 0), cnt1 += a[i];}
		ans = cnt0 * min(c0, c1 + h) + cnt1 * min(c1, c0 + h);
		printf("%d\n", ans);
	}
	return 0;
}
```

---

## 作者：白鲟 (赞：0)

## 前言
看见大多数人的代码都比较长（？），于是来贡献一篇短些的代码。

完全不压行。感觉是比较优雅的写法。

## 题目分析
一件显然的事情是每一位贡献互相独立。这给贪心带来了很大的便利。

那么只需要考虑每一位改变与不改变哪一种情况代价更小，求和即可。

## 代码
```cpp
#include<algorithm>
#include<cstdio>
using namespace std;
const int maxn=1e3;
int T,n,c[2],h,ans;
char s[maxn+1];
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		ans=0;
		scanf("%d%d%d%d%s",&n,&c[0],&c[1],&h,s+1);
		for(int i=1;i<=n;++i)
			ans+=min(c[s[i]-'0'],c[(s[i]-'0')^1]+h);
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：KSToki (赞：0)

# 题目大意
给你一个长度为 $n$ 的 $01$ 串，买下一个 $0$ 花费 $c0$，买下一个 $1$ 花费 $c1$，将一个 $0$ 改为 $1$ 或 $1$ 改为 $0$ 花费 $h$，问买下这个 $01$ 串的最小花费。
# 分析
水题。显然当换成另一个数买比直接买还便宜时，所有的这个数都应该改了再买，否则直接原价购买全部的。
# 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline int read()
{
    char ch=getchar();
	while(ch<'0'||ch>'9')
		ch=getchar();
	int res=0;
    while(ch>='0'&&ch<='9')
    {
    	res=res*10+ch-'0';
		ch=getchar();
    }
    return res;
}
int T,n,c0,c1,h,x,cnt[2];
int main()
{
	T=read();
	while(T--)
	{
		n=read();
		c0=read();
		c1=read();
		h=read();
		cnt[0]=cnt[1]=0;
		for(int i=1;i<=n;++i)
		{
			scanf("%1d",&x);
			++cnt[x];
		}
		if(c0>c1)
		{
			swap(c0,c1);
			swap(cnt[0],cnt[1]);
		}
		if(c0+h>c1)
			printf("%d\n",c0*cnt[0]+c1*cnt[1]);
		else
			printf("%d\n",c0*n+cnt[1]*h);
	}
	return 0;
}

```


---

