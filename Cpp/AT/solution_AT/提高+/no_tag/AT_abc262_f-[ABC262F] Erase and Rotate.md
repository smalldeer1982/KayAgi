# [ABC262F] Erase and Rotate

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc262/tasks/abc262_f

$ 1,2,\ldots,N $ がちょうど $ 1 $ 回ずつ現れる数列 $ P\ =\ (p_1,p_2,\ldots,p_N) $ が与えられます。  
あなたは以下の操作のうち $ 1 $ つを選んで行うことを $ 0 $ 回以上 $ K $ 回以下繰り返せます。

- $ P $ の項を $ 1 $ つ選び、削除する。
- $ P $ の末尾の項を先頭に移動させる。

操作後の $ P $ として考えられるもののうち辞書順で最小のものを求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 0\ \leq\ K\ \leq\ N-1 $
- $ 1\ \leq\ p_i\ \leq\ N $
- $ (p_1,p_2,\ldots,p_N) $ には $ 1,2,\ldots,N $ がちょうど $ 1 $ 回ずつ現れる。
- 入力はすべて整数

### Sample Explanation 1

以下のように操作をすると $ P $ は $ (1,2,3) $ になります。 - 先頭の項を削除する。これによって $ P $ は $ (5,2,3,1) $ になる。 - 末尾の項を先頭に移動させる。これによって $ P $ は $ (1,5,2,3) $ になる。 - 先頭から $ 2 $ 番目の項を削除する。これによって $ P $ は $ (1,2,3) $ になる。 また、辞書順で $ (1,2,3) $ より小さい数列は操作後の $ P $ として考えられません。よってこれが答えです。

### Sample Explanation 2

操作を $ 1 $ 回も行えない場合があります。

## 样例 #1

### 输入

```
5 3
4 5 2 3 1```

### 输出

```
1 2 3```

## 样例 #2

### 输入

```
3 0
3 2 1```

### 输出

```
3 2 1```

## 样例 #3

### 输入

```
15 10
12 10 7 2 8 11 9 1 6 14 3 15 13 5 4```

### 输出

```
1 3 4 7 2 8 11 9```

# 题解

## 作者：Rnfmabj (赞：5)

## ABC262F

*2334

卡手的构造题，不是很难想，主要是细节比较多。

### 题意

给定一个排列 $p$。你可以最多执行 $k$ 次操作。

- 删除一个数。
- 将 $p$ 中末尾的数移到开头。

找出字典序最小的 $p$。

### 题解

显然我们需要贪心地把靠前的位置放上较小的数，考虑怎么把这些小数放到前面去。

不妨先考虑怎么最小化第一位。我们可以在 $k$ 次操作内将其移到最终排列开头的位置有：

1. 第 $1$ 至第 $k$ 位。只要删掉前面的所有数就好。注意整个过程中不能也没必要执行任何移动操作。
2. 第 $n-k+1$ 至第 $n$ 位。后面的数可以选择移到开头，也可以选择直接删掉，但是在处理完目标位置之后就不能再执行移动操作了。

容易发现，这两类位置是“互斥”的。即，你只能从中选择一种方式构造第一位。显然，我们会选择最小的那一位。

但是由于可能出现 $\frac{n}{2} \le k$ 的情况，即两个位置集合有交集，导致同一个位置可能有两个构造方式，故需要对两种情况分类讨论。

------

先来看第一种情况。

由于没有移动，所以等价于直接在原排列上删除 $k$ 个数然后最小化字典序，直接用单调队列推一次就好了。

具体就是维护一个单调队列，但是全程只能弹出 $k$ 次，再多就不弹了。由于字典序的性质可以证明这样做的正确性是对的。注意如果最后维护完发现弹出次数还有剩余，即只删除了小于 $k$ 个数，那么就需要接着从末尾弹直到把次数用完。

原因是字典序中，原串前缀的字典序小于原串。

这样得到的单调队列即为第一种情况下的答案。

--------

再看第二种情况。

我们一定会从第 $n-k+1$ 至第 $n$ 位中选择最小的那一位，设该位为 $p$。

然后可以发现第 $p+1$ 位至第 $n$ 位都是需要操作的，要么被删除要么被移走，不然我们没办法将 $p$ 移动到开头。

既然怎样都是要操作的，操作次数省不掉，那么我们在找到 $p$ 之后直接对 $p$ 至 $n$ 维护一个标准的单调队列就可以了。单调队列中的元素将被保留至答案中的开头，所以这样可以最小化答案的前面部分。但是这一段中的末尾元素有可能会被后面接上的第 $1$ 至第 $p-1$ 位干掉，这个接下来再做。

对于第 $1$ 至第 $p-1$ 位，我们还剩下 $k-(n-p+1)$ 次操作。我们要最小化这个部分的字典序——那么就转化为了第一种情况，做一遍只能弹出 $k-(n-p+1)$ 次的单调队列即可。对于这部分的末尾同第一部分处理，也是有多余操作就弹到用完为止。

然后我们发现这样的单调队列的第一位是有可能比前面 $p$ 至 $n$ 位得到的单调队列的末尾更优的，所以要检查一下，如果更优那么第 $p$ 至 $n$ 位得到的单调队列就需要弹出末尾元素。

最后把 $p$ 至 $n$ 位得到的单调队列和 $1$ 至 $p-1$ 位的单调队列拼起来就是这种情况下的答案。

-------

最后，比较两种情况下答案的字典序，选择更优的打印即可。

时间复杂度 $O(n)$。

### 代码

相对简单，但是有不少细节。

```cpp
const ll maxn=2e5+5;
ll n,k,a[maxn];
ll q[maxn],tp;
ll b[maxn],hd;
vector<ll>ans1;
vector<ll>ans2;
void solve(){
	n=R,k=R;
	for(ll i=1;i<=n;i++){
		a[i]=R;
	}
	// 第一种情况
	for(ll i=1,cnt=0;i<=n;i++){
		while(tp&&a[i]<a[q[tp]]&&cnt<k)tp--,cnt++;//最多弹出k次
		q[++tp]=i;
		if(i==n){
			while(tp&&cnt<k)cnt++,tp--;//注意在最后一位的剩余操作
		}
	}
	for(ll i=1;i<=tp;i++)ans1.push_back(a[q[i]]);//记录答案
	// 第二种情况
	tp=0;
	a[n+1]=1ll<<60;
	ll p=n+1;
	//找到 p
	for(ll i=n;i>n-k;i--){
		if(a[i]<a[p])p=i;
	}
	//单调队列，弹出次数不会超过k次
	for(ll i=p;i<=n;i++){
		while(tp&&a[i]<a[q[tp]])tp--;
		q[++tp]=i;
	}
	k-=(n-p+1);//减去已经消耗的次数
	for(ll i=1;i<p;i++){
		while(hd&&k&&a[b[hd]]>a[i])hd--,k--;
		b[++hd]=i;//第 1 至 p-1 位的单调队列
	}
	while(k)hd--,k--;//如果操作次数还有剩余，同第一种情况
	while(hd&&tp&&a[q[tp]]>a[b[1]])tp--;//如果更优
	for(ll i=1;i<=tp;i++)ans2.push_back(a[q[i]]);
	for(ll i=1;i<=hd;i++)ans2.push_back(a[b[i]]);//记录答案
	if(ans1<ans2)for(auto it:ans1)wk(it);
	else for(auto it:ans2)wk(it);//选择更优的打印
	return ;
}
```



---

## 作者：Missa (赞：1)

庆祝 AT 复活，把自己赛后写的做题笔记拿来当题解

内心：没想到自己写的笔记还有用了

----------

不是特别难的思维题。

打完 E 还剩 1h，如果专心想说不定能想出来，然而看到通过人数仅 172 就放弃了，这是以后要杜绝的。

-------

题意：给定一个排列 $\{a_n\}$，有两种操作：

- 将最后数提到最前（Rotate）

- 删除一个数（Erase）

求操作 $k$ 次后最小字典序。

-----------

最小字典序看着是贪心。如果只有旋转，选最后 $k$ 个数中最小数与 $a_1$ 作比较。如果只有删除，迭代：在前 $k+1$ 个数中选取最小数 $a_i$，删去 $a_1-a_{i-1}$，然后把 $k$ 减去 $i-1$，对第二个数做一样的操作。如果到最后操作有剩余，就从后往前删。用线段树能做到 $O(n \log n)$，用单调栈能做到 $O(n)$。

这给我们的启示是第一个数的选择其实不多。现在考虑至少旋转一次的情况。

为了更好讨论，我们发现：旋转后删除与旋转前删除效果一致，所以强制先旋转在删除，且旋转后删除不占用操作次数。同时，我们应该让旋转过去的最后一个数不被删除，为防止一个状态被多次讨论。

那么就明晰了：只用讨论旋转过去后第一个数为从后往前 $k$ 数中最小数的情况。此时再做删除操作，复杂度同最前分析。

于是我们就得到了解法。其中关键的一步是统一了旋转与删除，即“先旋转后删除”。之后发现旋转过去后的数一定只是顺水推舟。先分别讨论了只有一种操作的情况也是一个重要的铺垫。

```cpp
#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;
const int M = 200005;
int n, a[M], k, cost[M], b[M], pl;
struct node{
    int mnd, mnp;
    bool operator < (const node &t) const{
        return mnd < t.mnd;
    }
};
node min(node x, node y) {return x < y ? x : y;}
struct sg2{
    node s[M << 2];
    void clear(){
        memset(s, 0, sizeof(s));
    }
    void build(int o, int l, int r){
        if(l == r) {s[o] = {a[l], l}; return;}
        int mid = l + r >> 1;
        build(o<<1, l, mid); build(o<<1|1, mid+1, r);
        s[o] = min(s[o<<1], s[o<<1|1]);
    }
	node query(int o, int l, int r, int x, int y){
		if(x <= l && r <= y) return s[o];
		int mid = l + r >> 1; node ans = {(int)1e9, (int)1e9};
		if(x <= mid) ans = min(ans, query(o<<1, l, mid, x, y));
		if(y > mid) ans = min(ans, query(o<<1|1, mid+1, r, x, y));
		return ans;
	}
}t;
void print(vector<int> t){
    for(auto i : t) printf("%d ", i);
    puts("");
}
vector<int> solve(){
    vector<int> ans; t.clear(); t.build(1, 1, n);
    int l = 1, c = k;
    while(l <= n){
        int tmpp = t.query(1, 1, n, l, max(l+c, n-pl+2+c)).mnp;
        // printf("tmpp = %d c = %d l = %d\n", tmpp, c, l);
        for(int i = l; i < tmpp; i++) c -= cost[i];
        ans.push_back(a[tmpp]); l = tmpp + 1;
    }
    for(int i = l; i <= n; i++) ans.push_back(a[i]);
    for(int i = 1; i <= c; i++) ans.pop_back();
    return ans;
}
int main(){
    scanf("%d %d", &n, &k); pl = 100000000;
    for(int i = 1; i <= n; i++){
        scanf("%d", &a[i]); cost[i] = 1;
    }
    vector<int> ans1 = solve();
    // print(ans1);
    if(k == 0) {print(ans1); return 0;}
    pl = t.query(1, 1, n, n-k+1, n).mnp;
    for(int i = 1; i <= n-pl+1; i++) b[i] = a[i+pl-1], cost[i] = 0;
    for(int i = 1; i < pl; i++) b[i+n-pl+1] = a[i];
    for(int i = 1; i <= n; i++) a[i] = b[i];
    k -= n-pl+1;
    // lim = n-pl+1;
    vector<int> ans2 = solve();
    // print(ans2);
    vector<int> ans = min(ans1, ans2);
    print(ans); return 0;
}
```

---

## 作者：cosf (赞：0)

我们先考虑没有旋转操作应该怎么做。

有个显然的贪心就是用单调栈维护，只不过出栈次数不能大于 $k$。并且，如果出栈次数小于 $k$，我们可以把最后的几项弹出去。

加上了旋转操作，我们可以枚举最终的第一位是什么。令 $a_i$ 表示 $i$ 在 $p_i$ 中的位置（即 $a_{p_i} = i$）。则如果 $a_i \le k + 1$，可以通过删除前面的所有数让 $a_i$ 成为第一位；如果 $n + 1 - a_i \le k$，则可以通过旋转或者删除后面的数将其成为第一位。

对于第一种情况，直接单调栈即可。对于第二种情况，如果想要让 $a_i + 1$ 到 $n$ 之间的数出栈，可以不用记录出栈次数，因为将 $a_i$ 旋转至第一位时可以顺带把它们删掉。

最终复杂度 $O(n)$。

```cpp
#include <iostream>
#include <vector>
using namespace std;

#define MAXN 400005

int a[MAXN], p[MAXN];

int n, k;

ostream &operator<<(ostream &a, vector<int> &b)
{
    for (int &i : b)
    {
        a << i << ' ';
    }
    return a;
}

int main()
{
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
    {
        cin >> p[i];
        p[i + n] = p[i];
        a[p[i]] = i;
    }
    for (int i = 1; i <= n; i++)
    {
        vector<int> res = {n + 1};
        if (a[i] <= k + 1)
        {
            vector<int> cur = {i}; // 听说用 vector 当栈比用 stack 当栈好（？
            int s = 0;
            int c = k - a[i] + 1;
            for (int j = a[i] + 1; j <= n; j++)
            {
                while (c > 0 && s > 0 && cur.at(s) > p[j])
                {
                    cur.pop_back();
                    s--;
                    c--;
                }
                cur.push_back(p[j]);
                s++;
            }
            while (c > 0)
            {
                cur.pop_back();
                c--;
            }
            res = min(res, cur);
        }
        if (n + 1 - a[i] <= k)
        {
            vector<int> cur = {a[i]}; // 这里的 cur 不是值，因为要判断将 cur.top 弹出时是否统计次数。
            int s = 0;
            int c = k - n - 1 + a[i];
            for (int j = a[i] + 1; j < a[i] + n; j++)
            {
                while (s > 0 && (cur.at(s) <= n || c > 0) &&  p[cur.at(s)] > p[j])
                {
                    if (cur.at(s) > n)
                    {
                        c--;
                    }
                    cur.pop_back();
                    s--;
                }
                cur.push_back(j);
                s++;
            }
            while (c > 0)
            {
                cur.pop_back();
                c--;
            }
            for (int &i : cur)
            {
                i = p[i];
            }
            res = min(res, cur);
        }
        if (res != vector<int>({n + 1}))
        {
            cout << res << endl;
            return 0;
        }
    }
    return 0;
}

```

---

