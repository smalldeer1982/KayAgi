# [ABC167F] Bracket Sequencing

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc167/tasks/abc167_f

以下のいずれかの条件を満たす文字列を**括弧列**と定義します。

1. 空文字列
2. ある括弧列 $ A $ が存在して、`(`, $ A $, `)` をこの順に連結した文字列
3. ある空でない括弧列 $ A $, $ B $ が存在して、$ A $, $ B $ をこの順に連結した文字列

$ N $ 個の文字列 $ S_i $ が与えられます。$ S_i $ 全てを好きな順序で連結するとき、括弧列を構成することはできますか。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^6 $
- $ S_i $ の文字列長の合計は $ 10^6 $ 以下
- $ S_i $ は `(`, `)` のみからなる空でない文字列

### Sample Explanation 1

`(()`, `)` の順に連結すると括弧列になります。

## 样例 #1

### 输入

```
2
)
(()```

### 输出

```
Yes```

## 样例 #2

### 输入

```
2
)(
()```

### 输出

```
No```

## 样例 #3

### 输入

```
4
((()))
((((((
))))))
()()()```

### 输出

```
Yes```

## 样例 #4

### 输入

```
3
(((
)
)```

### 输出

```
No```

# 题解

## 作者：CYZZ (赞：6)

# [Bracket Sequencing](https://www.luogu.com.cn/problem/AT_abc167_f)
学校模拟赛出了的一道贪心题。
## 思路
考虑如何将这 $n$ 个字符串排序，因为每个字符串里已经匹配的括号无法对整个的答案造成影响，所以可以把每个字符串中**已经匹配**的括号删掉，化简到 $\texttt{))))((((}$ 的形式，也就是左边全是 $\texttt{)}$ 右边全是 $\texttt{(}$。

考虑贪心，由于最左边有剩余的左括号，我们每放一个存在剩右括号的字符串，都会消耗一部分左括号，我们肯定是让消耗少的优先放前面。（每次都会补充多余消耗的左括号，所以左括号会一直变大，而每次选择消耗最少的，显然更优。）

把左边的安排完后，右边同理：一定是优先让消耗右括号少的放在右边。

综上：对于每个字符串剩下 $a$ 个左括号，剩下 $b$ 个右括号。

如果 $a\ge b$ 其放到左边，否则，都放在右边。

- 对于左边的字符串，$b$ 越小，越往左边。
- 对于右边的字符串，$a$ 越小，越在右边。

最后，把按顺序排好的字符串连起来，检查它是不是一个合法的括号序列即可。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,tot1,tot2;
string ans;
struct str
{
    string s;
    int l,r;
}a[1000005],b[1000005];
str get_new(string s)//预处理每个字符串
{
    int len=s.size(),cnt1=0,cnt2=0;
    stack<char>stk;
    for(int i=0;i<len;i++)
    {
        if(s[i]==')'&&!stk.empty()&&stk.top()=='(')
            stk.pop();
        else
            stk.push(s[i]);
    }
    string ret="";
    for(int i=stk.size()-1;i>=0;i--)
    {
        char tp=stk.top();
        ret+=tp;
        if(tp=='(')
            cnt1++;//左括号的数量
        else
            cnt2++;//右括号的数量
        stk.pop();
    }
    reverse(ret.begin(),ret.end());//因为是倒序从栈里取出来的，所以最后要翻转
    return {ret,cnt1,cnt2};
}
bool cmp1(str x,str y)
{
    return x.r<y.r;
}
bool cmp2(str x,str y)
{
    return x.l>y.l;
}
bool check()//判断是不是合法括号序列
{
    int len=ans.size();
    stack<char>stk;
    for(int i=0;i<len;i++)
    {
        if(ans[i]==')')
        {
            if(stk.empty()||stk.top()==')')
                return 0;
            else
                stk.pop();
        }
        else
            stk.push('(');
    }
    return stk.empty();
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        string s;
        cin >> s;
        str tmp=get_new(s);
        if(tmp.s=="")
            continue;
        if(tmp.l>=tmp.r)
            a[++tot1]=tmp;//放在左边
        else
            b[++tot2]=tmp;//放在右边
    }
    sort(a+1,a+tot1+1,cmp1);//按b的值排序
    sort(b+1,b+tot2+1,cmp2);//按a的值排序
    for(int i=1;i<=tot1;i++)
    {
        ans+=a[i].s;
    }
    for(int i=1;i<=tot2;i++)
    {
        ans+=b[i].s;//把左右连起来
    }
    if(check())
        printf("Yes");
    else
        printf("No");
}

```
希望本篇题解能帮到大家！！！

---

## 作者：Presentation_Emitter (赞：3)

草这题不是那个 ICPC WF 的阳光普照 H 题吗，不过这种题撞了也比较正常。

考虑删掉原括号序列中的所有匹配的括号对，之后每个括号序列就都形如 `)))...))((...(((` 的形式，即前半部分全为右括号，后半部分全为左括号。某个部分可能为空，即全为左括号或全为右括号。记右括号数量为 $r$，左括号数量为 $l$。

考虑构造一个合法的方案。发现括号序列共有两种：

- $r \le l$。

按 $r$ 从小到大放置。$r$ 个右括号相当于要求放置前的数列的左括号数量 $-$ 右括号数量 $\ge r$，不难发现这个差值是单调不减的，于是这个贪心是正确的。

- $r \gt l$。

考虑将串翻转，发现本质上与上面的情况相同，于是按 $l$ 从大到小放置即可。

---

## 作者：Danno0v0 (赞：3)

~~打 Pokemmo 时发现过不去对面的剩饭吉利蛋陷入了沉思。于是结合吉利蛋的疯狂生蛋突然发现好像可以这么做。~~

对于一个串，将左括号记为 +1，右括号记为 -1，于是我们便可以处理出两个东西：

- `lowest`:该串所有前缀和其中的最小值。

- `all`:该串总和。

于是我们发现假设我们当前的总和为 `p`，那么我们要保证 `p` $+$ `lowest` $\geqslant 0$ ，在加入这个串后 `p` $\rightarrow$ `all` $+$ `p`。

好极了，现在来考虑顺序吧。

把串分成四类分开考虑。

- `lowest` $\geqslant 0$，`all`$\geqslant 0$ 

显然随便加，而且一开始就加进去。让 `p` 尽可能大。

- `lowest` $\geqslant 0$，`all`$< 0$

显然不可能出现。

- `lowest` $<0$，`all` $\geqslant$ $0$

有点意思了。

对于这样一个串，我们可以知道，当我们试图加入这样一个串时，只要成功加入，`p` 就不降。

也就是说，我们只需要尽可能加入能加入的串就好了。

具体做法按照 `lowest` 从大到小排个序就好了。

- `lowest` $<0$，`all` $<0$ 

开始快乐了。很明显最后再来加这一类。

怎么办呢。

加入，我们遵从着：

> 只要成功加入， `p` 就一定会下降；既然如此，就应该让 `lowest` 小的串先加入，这样才能保证能加进去。

于是我们来一组 hack：

```
(p=9)
string1:lowest=-8 all=-4
string2:lowest=-6 all=-1
```

那么换一种：

> 要让 `p` 尽可能慢速地下降，于是应该先让 `all` 小的串先假如。

于是又来一组 hack：

```
(p=8)
string1:lowest=-8 all=-2
string2:lowest=-6 all=-1
```

好！（赞赏）

于是应该怎么排序呢。

这个时候我们充分发挥想象力，看看倒着会怎么样。

比方说：

```
string:lowest=-8,all=-3
```

假如在某个时刻我们捡起了这个串，那么捡起后我们的 `p` 一定大于等于 $5$ 。

倒着看，也就是我们要让 `p` 大于等于 $(8-3)=5$ 我们才能加入这个串。

于是所有的此类串倒着看都可以处理成诸如“`p` 大于某个数时，给 `p` 加上某个数”。

我们给定一个初始值，经过这些操作，就会得到终值。

将反过来看的操作反过来，就变成终值经过操作变成初始值。

意味着只需要终值小于等于 `p` 那么 `p` 就可以经过全部这些操作了！

意味着只需要终值尽可能小就可以了。

意味着，我们按照 `all` $-$ `lowest` 的大小从小到大，这样终值就会最小了！

由于这是反的，意味着实际加入时的顺序是按 `all` $-$ `lowest` 从大到小的顺序加入的。

那么这一类的顺序也就确定了。

然后就没了。

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
struct qur
{
	int lowest,all,id,sss;
}qurs[2000001],purs[2000001];
int n,all,qcnt,pcnt,ans[1000001],acnt;
string p;
bool cmp1(qur a,qur b)
{
	return a.lowest>b.lowest;
}
bool cmp2(qur a,qur b)
{
	return a.sss>b.sss;
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>p;
		int k=0,low=0;
		for(int j=0;j<p.size();j++)
		{
			if(p[j]=='(') k++;
			else k--;
			low=min(k,low);
		}
		if(low>=0) all+=k,ans[++acnt]=i;
		else
		{
			if(k>=0) qurs[++qcnt].lowest=low,qurs[qcnt].all=k,qurs[qcnt].id=i;
			else purs[++pcnt].lowest=low,purs[pcnt].all=k,purs[pcnt].id=i,purs[pcnt].sss=purs[pcnt].all-purs[pcnt].lowest;
		}
	} 
	sort(qurs+1,qurs+1+qcnt,cmp1);
	sort(purs+1,purs+1+pcnt,cmp2);
	for(int i=1;i<=qcnt;i++)
	{
		if(all+qurs[i].lowest<0)
		{
			cout<<"No"<<endl;
			return 0;
		}
		all+=qurs[i].all; 
		ans[++acnt]=qurs[i].id;
	}
	for(int i=1;i<=pcnt;i++)
	{
		if(all+purs[i].lowest<0)
		{
			cout<<"No"<<endl;
			return 0;
		}
		all+=purs[i].all;
		ans[++acnt]=purs[i].id;
	}
	if(all)
	{
		cout<<"No"<<endl;
		return 0;
	}
	cout<<"Yes"<<endl;
}
```


---

## 作者：Zhao_daodao (赞：1)

# [题目传送门](https://www.luogu.com.cn/problem/AT_abc167_f)
# 题目描述
输入一个整数 $n$，以及 $n$ 个字符串。其中只包含 $\texttt{(}$ 和 $\texttt{)}$。问是否可以通过排列组合是组合成的字符串成为一个合法的 **括号序列**。
# 题目分析
对于每一个括号序列，在序列内部化简后一定成为一堆右括号和一堆左括号
左括号，一个右括号。也就是类似 $))))(((($。  

显然剩的左括号的最多,字符串放在最左边。比如 $\texttt{(((}$。


同理，最右边一定是剩的右括号最多的字符串。

先把左括号剩的多的在左边安排好：由于最左边有剩余的左括号，我们每放一个 存在剩右括号的字符串，都会消耗一部分左括号，我们肯定是让消耗少的优先放前面。

### 证明
每次都会补充多余消耗的左括号，所以左括号会一直变大，而每次选择
消耗最少的，显然更优。

### 综上
对于每个字符串 剩下的左括号 $a$，剩下的右括号 $b$。
+ 如果 $a\ge b$，就放到左边。
+ 否则放在右边。
+ 对于左边的字符串，$b$ 越小，越在左边。
+ 对于右边的字符串，$a$ 越小，越在右边。


只需要用用结构体排序，然后看最后方案是否能匹配即可。

# 参考代码
```cpp
#include<bits/stdc++.h>
// #define int long long
using namespace std;
const int MAXN=1e6+5;
int n;
struct node{
    int zuo;
    int you;
}a[MAXN];
int Max(int a,int b){return a>b?a:b;}
bool cmp(node p,node q){
    int pfl=1,qfl=1;//1 右 0 左
    if(p.zuo>=p.you)pfl=0;
    if(q.zuo>=q.you)qfl=0;
    if(pfl!=qfl)
        return pfl<qfl;
    if(!pfl)return p.you<p.you;
    return p.zuo>p.zuo;
}
void check(){
    int zzuo=0,yyou=0;
    for(int i=1;i<=n;i++){
        int t=zzuo;
        zzuo=max(zzuo-a[i].you,int(0));
        yyou+=(a[i].you-(t-zzuo));
        zzuo+=a[i].zuo;
    }
    if(zzuo==yyou&&zzuo==0)
        cout<<"Yes";
    else cout<<"No";
    exit(0);
}
signed main(){
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);
    cin>>n;
    for(int i=1;i<=n;i++){
        string q;
        cin>>q;
        for(int t=0;t<q.size();t++){
            if(q[t]=='(')
                a[i].zuo++;
            else{
                if(a[i].zuo)a[i].zuo--;
                else a[i].you++;
            }
        }
    }
    sort(a+1,a+n+1,cmp);
    check();
}// 已做防抄处理
```

---

## 作者：AbsMatt (赞：1)

## [题目传送器](https://www.luogu.com.cn/problem/AT_abc167_f)
## [更爽的阅读体验](https://www.luogu.com.cn/blog/yaohaoyou/solution-at-abc167-f)

# 题意
翻译讲的很清楚了，这里不做过多的解释了。

# 思路
### 做法
1. 为了方便后续的操作，我们把输入的 $n$ 个字符串提前进行处理，将可以匹配的括号消除掉，将最后的字符串分段存入 vector。

2. 进行排序：对于每个字符串，令剩下的左括号数为 $a$，剩下的右括号数为 $b$。如果 $a \ge b$，其放到左边。否则，都放在右边。对于左边的字符串，$b$ 越小，越在左边。对于右边的字符串，$a$ 越大，越在左边。

3. 排序后从左往右遍历最后的字符串，进行检查。

### 排序证明
由于最左边有剩余的左括号，我们每放一个 存在剩右括号的字符串，都会消耗一部分左括号，我们肯定是让消耗少的优先放前面。每次都会补充多余消耗的左括号，所以左括号会一直变大，而每次选择消耗最少的，显然更优。

# 总结
时间复杂度为 $O(n \times \log_2n)$，排序时间最长。注意关流同步。
## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 10;
int n, ans = 0;
vector<pair<int, int> > v[maxn];  // first 为长度，second 为 0 代表连续 first 个都是 (,second 为 1 代表连续 second 个都是).
string ss[maxn];
struct node
{
    int a, b, id;
} s[maxn];
bool cmp(node x, node y)  // 排序
{
    if (x.a >= x.b)
    {
        if (y.a >= y.b)
            return x.b < y.b;
        return 1;
    }
    else
    {
        if (y.a < y.b)
            return x.a > y.a;
        return 0;
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        // 1. 提前处理
        cin >> ss[i];
        int now = 1, lst0 = -1;
        bool typ = (ss[i][0] == ')');
        for (int j = 1; j < ss[i].length(); j++)
        {
            if (bool(ss[i][j] == ')') == typ)
                now++;
            else
            {
                if (typ)
                    ans += now;
                else
                    ans -= now;
                if (typ)
                {
                    if (lst0 != -1)
                    {
                        int minus = min(v[i][lst0].first, now);
                        v[i][lst0].first -= minus;
                        now -= minus;
                    }
                }
                else
                    lst0 = v[i].size();
                v[i].push_back({now, typ});
                typ = bool(ss[i][j] == ')');
                now = 1;
            }
        }
        if (typ)
            ans += now;
        else
            ans -= now;
        if (typ)
        {
            if (lst0 != -1)
            {
                int minus = min(v[i][lst0].first, now);
                v[i][lst0].first -= minus;
                now -= minus;
            }
        }
        v[i].push_back({now, typ});
    }

    // 2. 求出每个字符串的 a 和 b 并排序
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < v[i].size(); j++)
        {
            if (v[i][j].second)
                s[i].b += v[i][j].first;
            else
                s[i].a += v[i][j].first;
        }
        s[i].id = i;
    }
    sort(s + 1, s + n + 1, cmp);

    // 最后进行检查
    int now = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < v[s[i].id].size(); j++)
        {
            if (v[s[i].id][j].second)
                now -= v[s[i].id][j].first;
            else
                now += v[s[i].id][j].first;
            if (now < 0)
            {
                cout<<"No";
                exit(0);
            }
        }
    }
    // 输出
    if (now == 0)
        cout<<"Yes";
    else
        cout<<"No";
}
```

---

## 作者：gxp123 (赞：0)

# 题解 abc167 F -  Bracket Sequencing

[atcoder 链接](https://atcoder.jp/contests/abc167/tasks/abc167_f)

[luogu 链接](https://www.luogu.com.cn/problem/AT_abc167_f)

## 题意

第一行给出一个 $n$ 表示有 $n$ 个只含有 $\texttt{(,)}$ 的括号序列。（$1\le n\le 10^6$）

之后 $n$ 行，每行一个括号序列。

如果可以通过排列这 $n$ 个括号序列使得其成为一个合法括号序列（即左右括号一一匹配），输出 $\text{Yes}$；如果不能，输出 $\text{No}$。

## 题解

如果我们把 `(` 看成 `1` ，`)` 看成 `-1` 。

则一个括号序列合法的条件就是所有数的和为 $0$ ，且对于任意前 $i$ 个数的和，我们都要其 $> 0$ 。

所以每个字符串我们就只维护它的两个信息：

- 总和
- 最小值（指前缀和中最小的一个）

然后我们就可以进行判断了。

贪心的去考虑。

我们把这些字符串分为总和 $< 0$ 的和总和 $\ge 0$ 的。

对于总和 $\ge 0$ ，如果它的最小值加上我们当前使用字符串的和还大于 $0$ 的话，把它放到这个位置一定是合法的。

所以我们把总和 $\ge 0$ 按照前缀和中的最小值从大到小排序，一次使用，如果不能使用，则一定无解。

证明是显然的。
> 假设遇到了一个字符串 $s$，最小值加总和小于 $0$ ，则对于其他没使用且总和大于 $0$ 的，它们的最小值一定比 $s$ 还小。
>
> 如果选总和小于 $0$ 的，只会让差距越来越大。
>
> **证毕。**

此时我们的就只剩下总和小于 $s$ 的字符串了。

如果我们只用上面的两个信息，是无法正确的贪心的。

反例是好举出的。

考虑如果这个数据是合法的，所以它最后一定会减到 $0$ 。

所以最后一个字符串的最小值一定就是它的总和。

如果最小值小于总和，则一定不合法。

这让我们可以考虑再维护一个信息：总和和最小值的差。

则越靠后的字符串，这个差越小一定不会更劣。

这样子我们就按照这个差从大到小使用字符串，判断是否合法。

时间复杂度：$O(n \log n)$ 。

## code

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
const int maxN = 1e6 + 10;
char s[maxN];
vector<pair<int,pii> > b;
vector<pii> a;
int n,m;

int main(){
    scanf("%d",&n);
    int d = 1,dmin = 0;
    for(int i = 1,sn ; i <= n ; ++i){
        scanf("%s",s + 1);
        sn = strlen(s + 1);
        d = 0,dmin = 0;
        for(int j = 1 ; j <= sn ; ++j){
            d += (s[j] == '(') ? 1 : -1;
            dmin = min(d,dmin);
        }
        if(d < 0){
            b.push_back(make_pair(dmin - d,make_pair(dmin,d)));
        }else   a.push_back(make_pair(dmin,d));
    }
    sort(a.begin(),a.end());
    sort(b.begin(),b.end());
    int i = a.size() - 1,j = b.size() - 1;
    d = 0;
    for (; i >= 0 ; --i){
        if(d + a[i].first < 0){
            puts("No");
            return 0;
        }
        d += a[i].second;
    }
    for (j = 0 ; j < b.size() ; ++j){
        if(d + b[j].second.first < 0){
            puts("No");
            return 0;
        }
        d += b[j].second.second;
    }
    if(d == 0)  puts("Yes");
    else        puts("No");
    return 0;
}
```

---

