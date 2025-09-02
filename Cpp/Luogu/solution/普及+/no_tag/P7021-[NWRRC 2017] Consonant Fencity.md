# [NWRRC 2017] Consonant Fencity

## 题目描述

在口语中有两种声音：元音和辅音。元音是通过开放的声道发出的声音；而辅音的发音方式是气流至少部分受阻。例如，字母 a 和 $o$ 用来表达元音，而字母 $b$ 和 $p$ 是辅音（例如 bad, pot）。

字母 $y$ 可以作为元音（例如 silly）或辅音（例如 yellow）。字母 $w$ 通常用作辅音（例如 wet），但在另一个元音之后可以发出元音（例如 growth），在某些语言中（例如威尔士语），它甚至可以是单词中的唯一元音。

在这个任务中，我们将 $y$ 和 $w$ 视为元音，所以在英语字母表中有七个元音：a, $e, i, o, u, w$ 和 $y$，其他所有字母都是辅音。

我们定义一个字符串的辅音密度为字符串中连续字母对的数量，这些字母对都是辅音并且大小写不同（小写字母后跟大写字母或反之亦然）。例如，字符串 CoNsoNaNts 的辅音密度是 $2$，字符串 dEsTrUcTiOn 的辅音密度是 $3$，字符串 StRenGtH 的辅音密度是 $5$。

你将得到一个由小写英文字母组成的字符串。你的任务是改变一些字母的大小写，使得所有相同的字母都具有相同的大小写（这意味着，结果字符串中不能同时出现同一个字母的小写和大写形式），并且结果字符串的辅音密度最大化。

## 说明/提示

时间限制：3 秒，内存限制：512 MB。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
consonants
```

### 输出

```
CoNsoNaNts
```

## 样例 #2

### 输入

```
destruction
```

### 输出

```
dEsTrUcTiOn
```

## 样例 #3

### 输入

```
strength
```

### 输出

```
StRenGtH
```

# 题解

## 作者：lizs (赞：2)

## 题意
给你一串字符串，改变一些字母的大小写使得所有相同的字母大小写相同，并且辅音密度尽可能的小， 辅音密度指有多少组相邻且大小写不同的辅音字母。

## 思路
大致思路：由题可知元音字母有 $7$ 个，则辅音字母有 $19$ 个，那么我们可以直接暴力搜索所有可能，对于每一种可能都求取当前的辅音密度，求出最大的辅音密度并记录当前字母大小写情况。

那么如何快速求取辅音密度呢？我们可以用 $c[i][j]$ 来表示 ASCLL 码为 $i$ 和 $j$ 的两个字母相邻的次数，这样我们只用遍历 $26^2$ 次就可以求出当前情况的辅音密度。
```cpp
for (int i = 97; i < 123; ++ i) {
			for (int j = 97; j < 123; ++ j) {
				if (st[i] && !st[j]) res += c[i][j]; // st[i]和st[j]表示ASCLL码为i和j的两个字母的大小情况
			}
		}
```


## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long

const int N = 200; // 'z'的ASCLL码为122所以至少要开123的数组

int c[N][N], maxn;
bool st[N], ans[N]; // st记录每一种情况的字母大小情况，ans记录辅音密度最大时的每个字母大小写情况
char g[] = {' ', 'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'x', 'z'}; // 方便dfs暴搜

bool fy(char s) { // 判断当前字母是否是辅音字母
	if (s != 'a' && s != 'e' && s != 'i' && s != 'o' && s != 'u' && s != 'w' && s != 'y') return true;
	return false;
}

void dfs(int x) { // 用dfs搜索每一种可能
	if (x > 19) {
		int res = 0;
		for (int i = 97; i < 123; ++ i) {
			for (int j = 97; j < 123; ++ j) {
				if (st[i] && !st[j]) res += c[i][j];
			}
		}
		if (maxn < res) {  //如果这种情况比目前最大的辅音密度还大的话就更新
			maxn = res;
			for (int i = 97; i < 123; ++ i) ans[i] = st[i];
		}
		
		return;
	}
	st[g[x]] = true; //选或不选下一个字母
	dfs(x + 1);
	st[g[x]] = false;
	dfs(x + 1);
}

signed main() {
	string s; cin >> s;
	
	for (int i = 0; i < s.size() - 1; ++ i) {
		if (fy(s[i]) && fy(s[i + 1])) {
			int x = s[i], y = s[i + 1];
			c[x][y] += 1;  // 使用二维数组记录这两个相邻字母相邻了多少次
            c[y][x] += 1;
		}
	}
	
	dfs(1); // x为当前字母在g数组中的下标
	
	for (int i = 0; i < s.size(); ++ i) { // 输出
		if (ans[s[i]]) cout << char(s[i] - 32);
		else cout << s[i];
	}
	
	return 0;
}
```

---

## 作者：JoshAlMan (赞：2)

简 单 题。

把问题转化成图论上的问题。

答案显然和序列顺序无关，考虑一个相邻的辅音字母点对 $a, b$，在他们中间加一条边。

考虑把这个图每个点染成两种颜色之一，那么他们的那个权值就是不同颜色之间点的边权和。

那么我们反着考虑一个边的集合怎么样可以黑白染色，显然是一个二分图。

那么问题就变成了求最大权生成二分图。

由于点数只有 $26 - 7 = 19$ 个，可以暴力枚举一组点集暴力更新答案 $O(n^2 2^n)$，也可以递推做到 $(n2^n )$。



---

## 作者：XIxii (赞：0)

### 题意：

  给你一个由小写字母构成的字符串 $s$ ，你可以其中某些字符变成大写字母。例如 $s$ 中有字母 $a$ ，如果想把 $a$ 变成大写，那 $s$ 字符串中的每一个 $a$ 都要变成 $A$ 。

  你需要找出字符对，$s_i$ 和 $s_{i-1}$需要是辅音字母，且 $s_i$ 和 $s_{i-1}$ 中需要一个字母大写另一个小写。$a$ 、 $e$ 、 $i$ 、 $o$ 、 $u$ 、 $w$ 、$y$ 这七个字母是非辅音字母。要求构成尽量多的这样的字符对，输出最后的字符串。

### 思路：

  首先预处理一下 $s$ 字符串中字符相邻的数量，
之后二进制枚举所有字母变成大写的情况。

接着枚举这个字母变成大写之后和其他字母组成成为字符对的数量。也就是结果加上 $w[x][k]$（ $x$ 是变成大写的字母，$k$ 用于枚举 $x$ 和那个字母组成字符对）

  那么如果 $b$ 和 $c$ 在字符串中相邻了，然后 $b$ 和 $c$ 都变成大写怎么处理？

  枚举到 $b$ 变成大写的时候，我们需要加上 $w[x][k]$ 。到下一次枚举到 $c$ 的时候，我们判断 $k$ 是否变成了大写，如果变了，就减去 $w[x][k]$ 。

### 代码：

```
#include <bits/stdc++.h>
using namespace std;
string s;
int w[150][150],que[150],vis[150];
int main()
{
    cin>>s;
    if(s.size()==1)
    {
        cout<<s<<endl;
        return 0;
    }
    for(int i=1;i<s.size();i++)
    {
        w[s[i-1]][s[i]]++;
    }
    int pos=0;
    for(int i='a';i<='z';++i)
    {
        if(i=='a' || i=='e' || i=='o' || i=='u' || i=='i' || i=='w' || i=='y')
        {
            continue;
        }
        que[pos++]=i;
    }
    int ans=0,flag=0;
    for(int i=0;i<(1<<pos);++i)
    {
        int sum=0;
        memset(vis,0,sizeof(vis));
        for(int j=0;j<pos;++j)
        {
            if((1<<j)&i)
            {
                for(int k='a';k<='z';++k)
                {
                    if(k=='a' || k=='e' || k=='o' || k=='u' || k=='i' || k=='w' || k=='y' || k==que[j])
                    {
                        continue;
                    }
                    if(vis[k])
                    {
                        sum-=w[k][que[j]];
                        sum-=w[que[j]][k];
                    }
                    else
                    {
                        sum+=w[k][que[j]];
                        sum+=w[que[j]][k];
                    }
                }
                vis[que[j]]=1;
            }
        }
        if(ans<sum)
        {
            ans=sum;
            flag=i;
        }
    }
    memset(vis,0,sizeof(vis));
    for(int i=0;i<pos;++i)
    {
        if((1<<i)&flag)
        {
            vis[que[i]]=1;
        }
    }
    for(int i=0;i<s.size();++i)
    {
        if(vis[s[i]])
        {
            cout<<char(s[i]-32);
        }
        else 
        {
            cout<<s[i];
        }
    }
    return 0;
}
```

---

## 作者：ybc2025chenyuyang (赞：0)

# 洛谷P7021题解
## 题目大意
题意是给定你一串字符，分为元音字母和辅音字母，将辅音字母变成大写，要构成尽量多的大写字母和小写字母的组合，最后输出改变后的字符串，就这么简单。
## 思路
由于辅音字母的数量才 $19$ 个，少到可以状态压缩，将相邻点建边，边权为 $1$，这样可以将字符串转化为 $1$ 个图。

相邻字符的出现次数可以表现为图的权值，这样去枚举每一种状态，然后内层去找每一步状态得到的权值。

当权值最大时，保留状态，最后将所有状态为 $1$ 的点改为大写，输出。

枚举状态的时候，需要判断是否两个辅音字母挨着，如果挨着的话就跳出去，因为这可能是题目说的。

一开始读错题意，后来改了改，并没有改这一步，就 $OK$ 了。也有可能是到现在题意也没读懂。
## AC code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define rep(i, s, t) for (int i = s; i <= t; i++)
typedef long long ll;
const int N = 1e6 + 5, mod = 1e9 + 7, INF = 0x3f3f3f3f;
int vis_1[300], vis_2[300], a[300][300], vis[1000];
char s[N];
ll i, j, k, t;
int main() {
    scanf("%s", s + 1);
    vis_1['a'] = vis_1['e'] = vis_1['i'] = vis_1['o'] = vis_1['u'] =
        vis_1['w'] = vis_1['y'] = 1;
    for (i = 'a'; i <= 'z'; i++) {
        if (!vis_1[i]) {
            vis_2[i] = t++;
        }
    }
    for (i = 1; s[i + 1]; i++) {
        a[s[i]][s[i + 1]]++;
    }
    ll maxx = 0, flag = 0;
    for (t = 0; t < (1 << 19); t++) {
        ll sum = 0;
        for (i = 'a'; i <= 'z'; i++) {
            if (vis_1[i]) {
                continue;
            }
            int x = vis_2[i];
            for (j = 'a'; j <= 'z'; j++) {
                if (vis_1[j]) {
                    continue;
                }
                int y = vis_2[j];
                if (((t >> x) & 1) != ((t >> y) & 1)) {
                    sum += a[i][j];
                }
            }
        }
        if (sum > maxx) {
            maxx = sum;
            flag = t;
        }
    }
    for (i = 'a'; i <= 'z'; i++) {
        if (flag & (1 << vis_2[i])) {
            vis[i] = 1;
        }
    }
    for (i = 1; s[i]; i++) {
        if (vis[s[i]] && (!vis_1[s[i]])) {
            printf("%c", (char)s[i] - 32);
        } else {
            printf("%c", s[i]);
        }
    }
    puts("");
}
```



---

