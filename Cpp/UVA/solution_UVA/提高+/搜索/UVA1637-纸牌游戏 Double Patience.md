# 纸牌游戏 Double Patience

## 题目描述

Double  Patience是一种单人游戏，使用标准的36张牌组。这些牌在洗牌后放在一张桌子上，叠成9叠，每叠4张，面朝上。

牌放下后，玩家转身。每一次，他可以从任意两个牌堆中取出同一等级的顶级牌，然后将它们移除。如果有几种可能性，玩家可以选择任何一种。如果所有的牌都从桌上移除，玩家将赢得游戏，如果一些牌仍然在桌上，并且没有有效的移动，玩家将失败。

乔治喜欢这种游戏。但当有几种可能时，他不知道要选择哪一张。乔治不想多想，所以在这种情况下，他只需从可能的情况中选择一对随机的，并删除它。乔治选择每种情况的可能性相同。

例如，如果最上面的牌是Ks、Kh、Kd、9h、8s、8d、7c、7d和6h，他会删除任何一对在(KS, KH)、(KS, KD)、(KH, KD)、 (8S, 8D)和 (7C, 7D)中的任何一对。删除（Ks,Kh）、（Ks,Kd）、（Kh,Kd）、（8s,8d）和（7c,7d）的概率都为1/5。

请算出在游戏开始时，根据桌上的牌，找出如果乔治按照描述行事，他赢得游戏的可能性是多少。

# 题解

## 作者：Rainy7 (赞：5)


给大家分享一个神奇的做法：记忆化搜索

------------

#### 1.关于输入
像我这种特别讨厌字符串的当然是转换成$int$了，因为和花色不重要，只要把等级-'0'就OK了。

------------

#### 2.想直接暴搜怎么做：
每层dfs都有$9$个参数，代表每堆的数量。

在每层dfs直接**双重循环 枚举**去找 **两堆最高层是 同等级** 的情况，假设总共有$sum$种情况。

对于每种情况都先减去相应牌数，然后往下dfs,并把每一个情况返回的正确率都加起来。

最后把**所有返回的胜率的和**$(cnt)/sum$就是这层dfs的胜率了。

特别注意的是：

**当每一堆都是$0$时，返回$1.0$ (就是胜率)**

**当$sum=0$时，直接返回$0$**


------------

#### 3.处理记忆化
当然啦，这样直接暴搜是会$TLE$的，我们需要优化。

可以发现，在搜索时，可能同一种情况被搜索了$INF$次，因此，想到可以记忆化。

 _~~(注意神奇的地方来了)~~._ 

**用$ans[][][][][][][][][]$来存储每个情况的胜率。**

因为**胜率可能为0**，所以在开一个$bool$数组$a$来判断是否搜索过。

oh对了，如果你jio的写太累了话，我给出两个建议：

1.复制黏贴

2.用宏定义

------------
附上代码：(嘤嘤嘤)
```
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
bool a[5][5][5][5][5][5][5][5][5];//因为胜率可能为0，所以用一个数组来判断 
double ans[5][5][5][5][5][5][5][5][5];//每种情况的胜率 
int p[10][5];
double dfs(int p1,int p2,int p3,int p4,int p5,int p6,int p7,int p8,int p9)
{	if(a[p1][p2][p3][p4][p5][p6][p7][p8][p9])
		return ans[p1][p2][p3][p4][p5][p6][p7][p8][p9];
	a[p1][p2][p3][p4][p5][p6][p7][p8][p9]=1;
	int t[15]={0,p1,p2,p3,p4,p5,p6,p7,p8,p9};
	double cnt=0.0,sum=0.0;//胜率 总数 
	for(int i=1;i<=9;i++)//开始枚举 
		for(int j=i+1;j<=9;j++)
			if(t[i]>0&&t[j]>0&&p[i][t[i]]==p[j][t[j]])//可以取这两堆的排
			{	t[i]--;t[j]--;
				sum++;
				cnt+=dfs(t[1],t[2],t[3],t[4],t[5],t[6],t[7],t[8],t[9]);
				t[i]++;t[j]++;
			}
	if(sum>0)ans[p1][p2][p3][p4][p5][p6][p7][p8][p9]=cnt/sum;
	return ans[p1][p2][p3][p4][p5][p6][p7][p8][p9];//输了o(╥﹏╥)o 
}
int main()
{	a[0][0][0][0][0][0][0][0][0]=1;
	ans[0][0][0][0][0][0][0][0][0]=1.0;
	for(int i=1;i<=9;i++)
	{	string s1,s2,s3,s4;
		cin>>s1>>s2>>s3>>s4;//众所周知花色不重要 
		p[i][1]=s1[0]-'0';
		p[i][2]=s2[0]-'0';
		p[i][3]=s3[0]-'0';
		p[i][4]=s4[0]-'0';
		//printf("%d %d %d %d\n",p[i][1],p[i][2],p[i][3],p[i][4]);
	}
	printf("%.6lf",dfs(4,4,4,4,4,4,4,4,4));
	return 0;
}
```
by 路人七


---

## 作者：小闸蟹 (赞：4)

```cpp
// 这一题利用了类似动态规划的思想
// 枚举每一种合法的情况，然后统计概率和
// 用一下记忆化搜索，降低搜索次数
#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <map>

std::map<std::vector<int>, double> d;
std::array<std::array<std::string, 4>, 9> Card;

// cnt：牌的情况
// c：一共还有c张牌
double DP(std::vector<int> &cnt, int c)
{
    if (c == 0)
    {
        return 1.0;
    }

    if (d.count(cnt) != 0)  // 记忆化搜索
    {
        return d[cnt];
    }

    double Sum = 0.0;
    int Tot = 0;
    for (int i = 0; i < 9; ++i) // 枚举每一堆牌
    {
        if (cnt[i] > 0) // 如果还剩下牌
        {
            for (int j = i + 1; j < 9; ++j)
            {
                if (cnt[j] > 0)
                {
                    // 那就比较一下堆顶的牌是否面值一样
                    // 取首字母就好了，因此是[0]
                    if (Card[i][cnt[i] - 1][0] == Card[j][cnt[j] - 1][0])
                    {
                        ++Tot;  // 统计取了多少次
                        --cnt[i];   // 拿走
                        --cnt[j];

                        Sum += DP(cnt, c - 2);  // 统计概率

                        ++cnt[i];   // 放回去，回溯
                        ++cnt[j];
                    }
                }
            }
        }
    }

    if (Tot == 0)
    {
        return d[cnt] = 0;  // 记忆化
    }
    else
    {
        return d[cnt] = Sum / Tot;  // 记忆化
    }
}

bool Read()
{
    for (int i = 0; i < 9; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if (!(std::cin >> Card[i][j]))
            {
                return false;
            }
        }
    }

    return true;
}

int main()
{
    while (Read())
    {
        // cnt[i]表示第i堆牌里面还剩下多少张
        // 初始时为9堆牌，每堆4张
        std::vector<int> cnt(9, 4);
        d.clear();
        std::printf("%.6lf\n", DP(cnt, 36));
    }

    return 0;
}
```

---

## 作者：wanganze (赞：0)

### 题意
给你九堆牌，每次可以将堆顶的相同牌（不管花色）消除，一旦有相同的随机消除，求成功概率。

**有多组数据。**
### 分析
记忆化搜索。

初始状态就是所有牌堆均有 $4$ 张牌，然后当牌堆空了时成功概率为 $1$。

我们对状态进行压缩，总共有 $5^9$ 种状态（不要忘记空堆），大约 $2\times10^6$。

对于每一个状态，操作一次则总次数加一，而成功数的增加就是这次操作产生的新状态的成功率。
### 实现
判断能否操作就是枚举到的两个牌堆非空且最上层相同。

用数组直接传递状态，压缩实现记忆化。

记得初始化、恢复现场。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e6 + 10,M = 15,K = 10;
int sta[] = {0,4,4,4,4,4,4,4,4,4};
bool st[N];
double ans[N];
char c[M][K],tmp;
int get(int t[])
{
	int res = 0;
	for(int i = 1; i <= 9; i ++) res = res * 5 + t[i];
	return res;
}
double dfs(int t[])
{
	if(st[get(t)]) return ans[get(t)];
	st[get(t)] = 1;
	double res = 0,cnt = 0;
	for(int i = 1; i <= 9; i ++) 
		for(int j = 1; j < i; j ++)
			if(t[i] > 0 && t[j] > 0 && c[i][t[i]] == c[j][t[j]])
			{
				t[i] --,t[j] --;
				res ++;
				cnt += dfs(t);
				t[i] ++,t[j] ++;
			}
	if(res) ans[get(t)] = cnt / res;
	return ans[get(t)];
}
int main()
{
	while(cin>>c[1][1]>>tmp>>c[1][2]>>tmp>>c[1][3]>>tmp>>c[1][4]>>tmp)
	{
		memset(st,0,sizeof st);
		memset(ans,0,sizeof ans);
		st[0] = 1,ans[0] = 1;
		for(int i = 2; i <= 9; i ++) cin>>c[i][1]>>tmp>>c[i][2]>>tmp>>c[i][3]>>tmp>>c[i][4]>>tmp;
		printf("%.6lf\n",dfs(sta));
	}
	return 0;
}
```

---

## 作者：o06660o (赞：0)

# UVA1637 题解

[英文题面](https://onlinejudge.org/external/16/1637.pdf)

## 题意

给出 $9$ 堆牌，每堆牌有 $4$ 张。每次可以拿走两张位于堆顶的牌（需要首字母相同），
如果有多种拿法会等概率的随机选一种。拿完所有牌则游戏胜利，求游戏胜利的概率，精确到小数点后六位。

输入有多组数据，每组数据有 $9$ 行，每行有用空格隔开的 $4$ 张排，最左边是堆底而最右边是堆顶。

## 思路

考虑状态压缩的动态规划。把状态看作一个 $5$ 进制的 $9$ 位数字，状态总数为 $5^9 = 1953125$，可以接受。
也就是说，我们可以用 `int` 来存储当前状态，并在需要的时候可以把它展开为一个 $9$ 元组，
分别表示每个牌堆剩下的牌数。

```cpp
constexpr int N = 9，M = 4;
int encode(const array<int，N>& S) {
    int ret = 0;
    for (int i = 0; i < N; i++) {
        ret *= (M + 1);
        ret += S[i];
    }
    return ret;
}
array<int，N> decode(int S) {
    array<int，N> ret = {};
    for (int i = 0; i < N; i++) {
        ret[i] = S % (M + 1);
        S /= M + 1;
    }
    reverse(all(ret));
    return ret;
}
```

然后定义 $f(S)$ 为从状态 `S` 出发最终游戏胜利的概率。初始条件是 $f(0) = 1$ （没有牌游戏必胜）。
转移方程是后继状态成功概率之和除以后继状态数（使用全概率公式），如果没有后继状态则 $f(S) = 0$。

状态转移的时候我们需要找到两张具有相同等级（也就是首字母）的牌，我们可以把首字母先转换为数字，
然后记录每一个数字对应的牌堆。用两重 `for` 循环枚举即可。这边给出记忆化搜索情况下的转移方程。 

```cpp
constexpr int R = 9;
const map<char, int> CONV = {{'6', 0}, {'7', 1}, {'8', 2}, {'9', 3}, {'T', 4},
                             {'J', 5}, {'Q', 6}, {'K', 7}, {'A', 8}};
double dfs(int S_) {
    /* ... */
    auto S = decode(S_);
    array<vector<int>, R> cards;
    for (int i = 0; i < N; i++) {
        if (S[i] == 0) continue;
        cards[CONV.at(a[i][S[i] - 1][0])].push_back(i);
    }
    for (int k = 0; k < R; k++) {
        int m = cards[k].size();
        for (int i = 0; i < m; i++) {
            for (int j = i + 1; j < m; j++) {
                // 下面的 `ii`, `jj` 就是可以选取的两堆牌
                int ii = cards[k][i], jj = cards[k][j];
                /* ... */
            }
        }
    }
    /* ... */
}
```

## 代码

```cpp
#include <bits/stdc++.h>
#define all(a) a.begin(), a.end()
using namespace std;
using ll = long long;  // 2.15e9, 9.22e18
using pii = pair<int, int>;

constexpr int N = 9, M = 4, R = 9;
constexpr int MAXN = 1953125;  // `pow(5, 9)`
const map<char, int> CONV = {{'6', 0}, {'7', 1}, {'8', 2}, {'9', 3}, {'T', 4},
                             {'J', 5}, {'Q', 6}, {'K', 7}, {'A', 8}};
array<bool, MAXN> vis;
array<double, MAXN> f;  // `dp`
array<array<string, M>, N> a;

int encode(const array<int, N>& S) {
    int ret = 0;
    for (int i = 0; i < N; i++) {
        ret *= (M + 1);
        ret += S[i];
    }
    return ret;
}

array<int, N> decode(int S) {
    array<int, N> ret = {};
    for (int i = 0; i < N; i++) {
        ret[i] = S % (M + 1);
        S /= M + 1;
    }
    reverse(all(ret));
    return ret;
}

double dfs(int S_) {
    if (vis[S_]) return f[S_];
    vis[S_] = 1;
    auto S = decode(S_);
    array<vector<int>, R> cards;
    for (int i = 0; i < N; i++) {
        if (S[i] == 0) continue;
        cards[CONV.at(a[i][S[i] - 1][0])].push_back(i);
    }
    int next_cnt = 0;
    double sum = 0;
    for (int k = 0; k < R; k++) {
        int m = cards[k].size();
        for (int i = 0; i < m; i++) {
            for (int j = i + 1; j < m; j++) {
                int ii = cards[k][i], jj = cards[k][j];
                S[ii]--, S[jj]--;
                next_cnt++;
                sum += dfs(encode(S));
                S[ii]++, S[jj]++;
            }
        }
    }
    if (next_cnt == 0) {
        return f[S_] = 0;
    } else {
        return f[S_] = sum / next_cnt;
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    while (cin >> a[0][0]) {
        vis = {};
        vis[0] = 1;
        f[0] = 1;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                if (!(i == 0 && j == 0)) cin >> a[i][j];
        cout << fixed << setprecision(6) << dfs(MAXN - 1) << "\n";
    }
    return 0;
}
```

---

