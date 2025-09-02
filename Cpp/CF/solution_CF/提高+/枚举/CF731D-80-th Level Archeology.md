# 80-th Level Archeology

## 题目描述

Archeologists have found a secret pass in the dungeon of one of the pyramids of Cycleland. To enter the treasury they have to open an unusual lock on the door. The lock consists of $ n $ words, each consisting of some hieroglyphs. The wall near the lock has a round switch. Each rotation of this switch changes the hieroglyphs according to some rules. The instruction nearby says that the door will open only if words written on the lock would be sorted in lexicographical order (the definition of lexicographical comparison in given in notes section).

The rule that changes hieroglyphs is the following. One clockwise rotation of the round switch replaces each hieroglyph with the next hieroglyph in alphabet, i.e. hieroglyph $ x $ ( $ 1<=x<=c-1 $ ) is replaced with hieroglyph $ (x+1) $ , and hieroglyph $ c $ is replaced with hieroglyph $ 1 $ .

Help archeologist determine, how many clockwise rotations they should perform in order to open the door, or determine that this is impossible, i.e. no cyclic shift of the alphabet will make the sequence of words sorted lexicographically.

## 说明/提示

Word $ a_{1},a_{2},...,a_{m} $ of length $ m $ is lexicographically not greater than word $ b_{1},b_{2},...,b_{k} $ of length $ k $ , if one of two conditions hold:

- at first position $ i $ , such that $ a_{i}≠b_{i} $ , the character $ a_{i} $ goes earlier in the alphabet than character $ b_{i} $ , i.e. $ a $ has smaller character in the first position where they differ;
- if there is no such position $ i $ and $ m<=k $ , i.e. the first word is a prefix of the second or two words are equal.

The sequence of words is said to be sorted in lexicographical order if each word (except the last one) is lexicographically not greater than the next word.

In the first sample, after the round switch is rotated $ 1 $ position clockwise the words look as follows:

`<br></br>1 3<br></br>2<br></br>3 1 2<br></br>3 1 2 3<br></br>`In the second sample, words are already sorted in lexicographical order.

In the last sample, one can check that no shift of the alphabet will work.

## 样例 #1

### 输入

```
4 3
2 3 2
1 1
3 2 3 1
4 2 3 1 2
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2 5
2 4 2
2 4 2
```

### 输出

```
0
```

## 样例 #3

### 输入

```
4 4
1 2
1 3
1 4
1 2
```

### 输出

```
-1
```

# 题解

## 作者：Nekroz (赞：9)

[blog][blog]

[blog]:https://blog.csdn.net/Diogenes_/article/details/79898713

### 题目解释：

有n个数列，每个数列长度可能不一样，同时有一个c，你有一种操作，让这n个数列中所有小于c的数都加1，所有等于c的数变成0.问你最少可以操作几次可以让这n个数列满足字典序

我们可以发现，对于任意两个相邻的数列，操作数k有一个符合的区间，且k一定小于c，因为进行c次操作之后的数列与原数列相同，相当于有一个循环的过程。只要操作数k在这个区间里面，上面的数列字典序总小于下面的数列。说得通俗一点，有n-1个区间（有特殊情况，看代码），要求这n-1个区间的交。

怎么做这个问题呢，我们可以采取差分+前缀和的方式进行处理，具体方法就是区间两端位置放个++和--，统计时从前到后加起来就可以了。

下面来讨论一下每种情况：

首先假设有两个word，分别叫做a和b，并且我们定义两个word的失配位置为两个word从前往后逐位比较，所找到的第一个有不相同字符的位置。
具体情况有一下四种：

1.失配位置在a，b中（表示没有一个word是另一个word的前缀），且失配位置上的数a比b小。

举个栗子 `a=13`  `b=15` `c=7`明显地，失配位置在第二位，失配位置上的数满足a比b小。画个表格模拟一下：

| 操作次数 | a | b  |
| -
| 0  | 13 | 15 |
| 1  | 24 | 26 |
| 2  | 35 | 37 |  
| 3  | 46 | 40 |
| 4  | 57 | 51 |
| 5  | 60 | 62 |
| 6  | 71 | 73 |

可以看出，失配位置前的数字对结果不产生影响（因为始终相同，无法比较字典序），由表格易知当操作数在$[0, 2] \cup [5, 6]$的情况下是可行的。这个情况比较复杂，因为举其他例子时有可能第二个区间退化成一个数甚至消失，这会不会对我们的程序产生什么影响呢（比如说要特判之类的）？答案是不会。因为假设第二个区间的形式是$[p, q]$，第二个区间消失时一定满足$p = q + 1$(这个很重要，要自己多举几个例子理解一下，我这里就不证明了)，而我们的程序会在$p$的位置+1，在$q + 1$的位置-1，两个加一减一相互抵消了，因此对我们的程序不产生影响。

2.失配位置在a，b中（表示没有一个word是另一个word的前缀），且失配位置上的数a比b大。

仍然举个栗子 `a=14` `b=12` `c=7`，这个相对较易，我就不画表格模拟了，操作数的区间为$[4, 5]$
3.失配位置在a的末尾的后一个位置（a是b的前缀），这个很简单不管你怎么操作a始终比b小，操作区间$[0, c - 1]$

4.失配位置在b的末尾的后一个位置（b是a的前缀），这个也很简单，直接就是无解，不需要进行任何操作，直接输出无解可以，continue也可以（缺少一个区间就永远无法让k满足n-1个区间）。

四种情况讨论完了，具体详情看代码吧。

### Codes
```
#include<cstdio>
#include<vector>
#include<cstring>
using namespace std;
const int MAXN = 1e6 + 10;
const int MAXC = 1e7 + 10;
vector<int> words[MAXN];
int cnt[MAXC], n, c;
void calc(int a, int b)
{
    int index = 0;
    while (index < words[a].size() && index < words[b].size()) //失配位置查询
    {
        if (words[a][index] != words[b][index]) break;
        index++;
    }
    if (index < words[a].size() && index < words[b].size()) // 失配位置在a, b中
    {
        if (words[a][index] < words[b][index]) // 失配位置a小于b
        {
            cnt[0]++;
            cnt[c - words[b][index] + 1]--;
            cnt[c - words[a][index] + 1]++;
            cnt[c]--;
        }
        else
        {
            cnt[c - words[a][index] + 1]++;
            cnt[c - words[b][index] + 1]--;
        }
    }
    else if (index == words[a].size() && index != words[b].size()) //a比b短
    {
        cnt[0]++;                                   
        cnt[c]--;                                  
    }
    else if (index != words[a].size() && index == words[b].size()); // a比b长，无解
    else //a和b一样长
    {
        cnt[0]++;
        cnt[c]--;
    }
}
int main()
{
    scanf("%d%d", &n, &c); 
    for (int i = 1;i <= n;i++)
    {
        int len, w;
        scanf("%d", &len);
        while (len--)
        {
            scanf("%d", &w);
            words[i].push_back(w);
        }
    }
    for (int i = 1;i <= n - 1;i++) calc(i, i + 1);
    bool flag = false;
    int sum = 0;
    for (int i = 0;i < c;i++)
    {
        sum += cnt[i];
        if (sum == n - 1)
        {
            flag = true;
            printf("%d\n", i);
            return 0;
        }
    }
    if (!flag) printf("-1\n");
    return 0;
}

```

---

## 作者：KazamaRuri (赞：1)

蓝诈骗题。

简单处理，将所有数减一，操作变成 ++ 后取模。

发现只要所以相邻两项的字典序限制就好了。

而相邻两项只用考虑第一个不相同的位。

在第一个不相同的位上，我们考虑对答案范围的限制。

设前一位 $x$ 加到取模溢出的操作次数为 $u = c-x$ 以及当前位的信息 $y$ 和 $v$。

若 $x < y$，那么这两位要都不溢出或者都溢出，限制答案范围在 $[0,v-1]$ 或 $[u,k]$，注意是“或”。

若 $x>y$，合法当且仅当只有 $x$ 溢出，即 $[u,v-1]$。

现在问题变成了要找能满足限制的最小位置。

对于二选一，这两个区间如果有交相当于没限制，不然可以直接统计每个位置的被覆盖次数，差分做。

对于强制的限制，直接维护区间并即可。

直接枚举答案，时间复杂度 $O(\sum len + k)$。

要特判掉两串完全相同但是前面更长这种无解情况。


```cpp
#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using ll=long long;
using ull=unsigned long long;
using pii=pair<int,int>;
const int N=1e6+5;
int n,k,m,l[N],r[N],s[N]; vector<int>a[N]; 
int main(){
	scanf("%d%d",&n,&k);
	int tl=0,tr=k,ml=k,mr=0;
	a[0].push_back(0); 
	for(int i=1;i<=n;i++){
		int L,x,flg=1; l[i]=0,r[i]=k;
		scanf("%d",&L); a[i].push_back(L);
		for(int j=1;j<=L;j++){
			scanf("%d",&x),a[i].push_back(--x);
			if(a[i-1][0]>=j&&a[i-1][j]!=x&&flg){
				int u=k-a[i-1][j],v=k-x; flg=0;
				if(a[i-1][j]<x) v-1<u&&(m++,s[0]++,s[v]--,s[u]++,s[k+1]--); 
				else tl=max(tl,u),tr=min(tr,v-1);
			}
		} if(flg&&i-1&&a[i-1][0]>L) return puts("-1")&0;
	}
	for(int i=1;i<=k;i++) s[i]+=s[i-1];
	for(int i=tl;i<=tr;i++) if(s[i]==m) return printf("%d",i%k)&0;
	return puts("-1")&0;
}
```

---

## 作者：henhen_ (赞：1)

这是一道~~非常水~~的紫题。
### 题目大意

[传送门](https://www.luogu.com.cn/problem/CF731D)

### 大致思路

通过观察，不难发现，对于每一个数列，如果操作数达到 $C$，就会和原数列相同，也就是说，我们的操作数在 $\lbrack0,c\rbrack$ 之间。

对于相邻两个数列的相同位数的 $a_i$ 和 $b_i$，有如下 3 种情况：

- $a_i=b_i$：无需操作。

- $a_i>b_i$：操作数在 $\lbrack0,c-a\rbrack$ 和 $\lbrack c-b+1,c-1\rbrack$ 是无效的。

- $a_i<b_i$：操作数在 $\lbrack c-b+1,c-a\rbrack$ 是无效的。

我们用一个数组记录这些不能操作成功的区间，每次将 $a_l+1$，$a_r-1$。

最后，当这个数组的前缀和等于 $0$ 时，操作数是合法的。

### 高清无注释版代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e6+15;
int n,c;
vector<int>g[N];
int sb[N];
void add(int l,int r){
	sb[l]++,sb[r+1]--;
}
signed main(){
	scanf("%lld%lld",&n,&c);
	int x,y;
	for(int i=0;i<n;i++){
		scanf("%lld",&x);
		while(x--){
			scanf("%lld",&y);
			g[i].push_back(y);
		}
	}
	for(int i=0;i<n-1;i++){
		int sz=min(g[i].size(),g[i+1].size());
		int flag=1;
		for(int j=0;j<sz;j++){
			int a=g[i][j],b=g[i+1][j];
			if(a==b) continue;
			else if(a>b) add(0,c-a),add(c-b+1,c-1);
			else add(c-b+1,c-a);
			flag=0;
			break;
		}
		if(flag){
			if(g[i].size()>g[i+1].size()){
				printf("-1\n");
				return 0;
			}
		}
	}
	int cnt=0;
	for(int i=0;i<=c-1;i++){
		cnt+=sb[i];
		if(cnt==0){
//			cout<<"sb"<<endl;
			printf("%lld\n",i);
			return 0;
		}
	}
	printf("-1");
	return 0;
}
```


---

## 作者：Mint_Flipped (赞：0)

题意很好理解，但关键是用什么方法去做这个问题。



设：前一个数列为a[i],后一个为b[j],只要i=j,a[i]>b[j],就要进行+1操作。

同时举一下反例，比如a[i],b[j],i>j,但是前面的元素都是相同的，那么前者的字典序肯定比后者的大，或者还有就是像样例3这样的。

关于这道题的思路，首先我们要明确一点我们无法知道我们要加多少次1，但我们知道我们可以加多少次1，即加多少次1就可以满足前小后大的条件（如果数列的字典序相同，那么我们是可以随便加的）。

例1：
i=j,a[i]<b[j],这个情况，我们只要处理安排a[i],使之继续成立即可。

例2：
1-9 a[i]=2 a[j]=5,[1,4]或者[8,9],a[i]，b[j]同时加上这些值也是成立。

例3：
i=j, a[i]>b[j],我们还是处理啊a[i]，使之成立即可，举例说明，1-9 5 2，[5,7],a[i]，b[j]同时加上这些值就是成立。

例4：
如果相同，[1,m],无论同时加上这些值中的哪个也都是成立的。但如果出现前面的情况，就不行了。

怎么使得区间修改呢？树状数组，差分方法，[l,r],给从c[l]+1,c[r+1]-1，即可。

我们要注意一点，现在树状数组里的数值不是数列的值，而是记录了修改的次数，两者相似，切莫搞混（相似的原因是数列最多修改m次）。

最后记录一下哪个操作出现了n-1次就是答案（注意树状数组不开下标0，所
以1出现了n-1，代表了0次操作出现n-1次）。

代码如下：
```cpp
#include <bits/stdc++.h>
#define ll long long
#define mem(a,b) memset(a,b,sizeof(a))
#define fo1(a,b) for(int a=0;a<b;++a)
#define fo2(a,b) for(int a=1;a<=b;++a)
#define lowbit(a) a&(-a)
using namespace std;
const int maxn=1e6+5;
const int mod=1e9+7;
int c[maxn];
int num[2][maxn];
void update(int x,int y,int n)
{
    while(x<=n)
    {
        c[x]+=y;
        x+=lowbit(x);
    }
}
void two_update(int x,int y,int n)
{
    update(x,1,n);
    update(y+1,-1,n);
}
int query(int x)
{
    int ans=0;
    while(x)
    {
        ans+=c[x];
        x-=lowbit(x);
    }
    return ans;
}
int main()
{
    int n,m,cnt,tecnt,cnr=0;
    bool flag=1;
    cin>>n>>m;
    scanf("%d",&cnt);
    fo1(i,cnt)
    scanf("%d",&num[cnr][i]);
    tecnt=cnt;
    cnr^=1; //这里异或1可以在0 1之间切换，模拟前后数列比较
    fo2(k,n-1)
    {
        scanf("%d",&cnt);
        fo1(i,cnt)
        scanf("%d",&num[cnr][i]);
        if(flag)
        {
            bool flag1=0;
            fo1(i,min(cnt,tecnt))
            {
                if(num[cnr][i]>num[cnr^1][i])
                {
                    flag1=1;
                    two_update(1,m-num[cnr][i]+1,m+5);
                    two_update(m-num[cnr^1][i]+2,m,m+5);
                    break;
                }
                else if(num[cnr][i]<num[cnr^1][i])
                {
                    flag1=1;
                    two_update(m-num[cnr^1][i]+2,m-num[cnr][i]+1,m+5);
                    break;
                }
            }
            if(!flag1)
            {
                if(tecnt>cnt)
                    flag=0;
                else
                    two_update(1,m,m+5);
            }
            tecnt=cnt;
            cnr^=1;
        }
    }
    int ans=-1;
    if(flag)
    {
        fo2(i,m)
        {
            if(query(i)==n-1)
            {
                ans=i-1;
                break;
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}

```

---

## 作者：Bring (赞：0)

[For a better experience please click here.](https://www.cnblogs.com/BrianPeng/p/16928706.html)

## Solution: CF731D 80-th Level Archeology -- Letter, Interval, and Reverse Thinking

Link to the question: [CF](https://codeforces.com/problemset/problem/731/D) [Luogu](https://www.luogu.com.cn/problem/CF731D)

### Preface

*Assertion: "STL `set` is the most 'powerful' tool throughout C++."*

~~"Not because it is capable of various tasks, but because we don't need to code it ourselves."~~

### What is lexicographical order?

Lexicographical order is an ordering of strings based on the ordering of characters. A string is less than another string when, at the first position of difference, the letter in the first string is less than the corresponding letter in the second.

It is the ordering of words in a dictionary.

E.g. In the normal alphabet, 'abceb'<'abdca' since 'c'<'d' at their third position, the first position of difference. Note that we only consider the first position of difference. Even though 'e' is greater than 'c' at the fourth position and 'b' is greater than 'a' at the fifth, they cannot affect our comparison.

P.s. We let the 'empty character' be the smallest. E.g. To compare 'an' and 'and', we may consider the third position of 'an' as the empty character, then 'an'<'and' as the empty character is less than 'd'.

### Back to the question

"One operation replaces each letter with the next letter in the alphabet."

We try to find the number of operations to make all the words in lexicographical order.

Reverse Thinking: One operation replaces each letter **in the alphabet** with its previous one.

E.g. Consider the first example (We use letters to make it more intuitive). The strings are

```
cb
a
bca
bcab
```

and the alphabet is `a<b<c`.

After one operation, the strings become

```
ac
b
cab
cabc
```

which are in lexicographical order.

Reverse Thinking: after one operation, we 'rotate the alphabet' to `c<a<b`. And now, the strings are in lexicographical order **based on our new alphabet.**

**The solution is to find a reordering of the alphabet to make the strings in lexicographical order.**

### How to reorder the alphabet?

"From the order of characters, we develop an order of strings."

Reverse Thinking: From the order of strings, we deduce the order of characters.

E.g. Given that 'ace'<'abd' in some alphabet, we know that 'c'<'b' in that alphabet (and this is the only information we can extract).

The method is: **Find the first position of difference, then the character in the first string at that position is less than the corresponding character in the second string.**

P.s. As we know that the empty character is invariantly the smallest, there is no alphabet satisfying 'and'<'an'.

To deal with this question, we assume that the strings are in lexicographical order in some alphabet, and by comparing strings, we know some orders between characters in that alphabet. At last, we check whether a rotation of the switch results in an alphabet satisfying all conditions.

We know that after rotation, the new alphabet must be in the form of

$a,a+1,\cdots,n-1,n,1,2,\cdots,a-1$

for some $a\in\{1,\cdots, n\},$ which is the smallest character (except empty character).

*In the following text, we use '$<$' to denote the normal comparison between numbers, and '$\prec$' to denote the comparison in alphabetical order.*

##### Case 1:

By comparing two strings, we know that $u\prec v,$ while $u<v.$

E.g. If the strings `1 2 3` < `1 3 2`, then we know that $2\prec 3$ in this alphabet, while $2<3$ in number order.

We may use $u$ and $v$ to restrict the range of $a,$ the smallest character in the new alphabet.

The restriction is: $a\notin [u+1,v]$ because contrarily, if $a$ is in the range, the alphabet is

$a,a+1,\cdots,v,\cdots,n,1,\cdots,u,\cdots,a-1,$ where $v\prec u$ in the alphabet, a contradiction.

We may check that $a$ outside the interval satisfies $u\prec v.$

##### Case 2:

By comparing two strings, we know that $u\prec v,$ while $u>v.$

E.g. If the strings `1 3 2` < `1 2 3`, then we know that $3\prec 2$ in this alphabet, while $3>2$ in number order.

The restriction now is: $a\in [v+1,u].$ (Why?)

### Implementation

To combine all the restrictions, $a$ is

1. not in the **union** of all the intervals of case 1;
2. in the **intersection** of all the intervals of case 2.

For case 2, maintaining the intersection of intervals is easy. Suppose the current interval is $[l,r],$ then its intersection with $[u,v]$ is just $[\max(l,u),\min(r,v)].$ (If the right boundary is less than the left, then we regard it as the empty interval.)

For case 1, maintaining the union of intervals is not so easy. One offline method is to sort all the intervals by left boundaries, and then combine them if they have non-empty intersections.

However, I'd like to introduce an online method of maintaining unions of intervals, which is, sometimes, even easier to implement than the offline method.

#### Use STL `set` to maintain the union of intervals.

~~That's why it is the most powerful tool in C++~~

We let the set store disjoint intervals (i.e. intervals that don't intersect) in order. Whenever we try to add a new interval, we combine it with the existing intervals that intersect with it.

Our data structure:

```cpp
struct T{int l,r;
	bool operator<(T b)const{return r<b.l;}
};
set<T>//our data structure
```

Note the way we define the order between intervals (which is necessary when using `set`). We define an interval to be less than another only when the first is on the left of the second and they are **disjoint**. Thus, if two intervals intersect, the `set` considers them equal (more exactly, neither less than nor greater than).

Another important feature of `set` is its `find()` function, which returns the iterator (the pointer) to the first element that is 'equal' to our input.

Now, suppose we have a set with intervals $\{[1,3],[5,5],[7,9],[10,11]\}$ and we want to add the interval $[2,8]$. What should we do?

1. We use `find()` to search for the first interval that intersects with $[2,8],$ which is $[1,3].$ Combine them to get $[1,8].$ Erase $[1,3]$ in the set. Now, our task becomes "adding $[1,8]$ to the set $\{[5,5],[7,9],[10,11]\}$".
2. We find $[5,5]$ in the set. As it is already contained in $[1,8]$ we erase it from the set. Now, our task becomes "adding $[1,8]$ to the set $\{[7,9],[10,11]\}$".
3. We find $[7,9]$ in the set. Combine it with $[1,8]$ to get $[1,9]$. Now, our task becomes "adding $[1,9]$ to the set $\{[10,11]\}$".
4. As there is no interval in the set that interests with $[1,9],$ we add it to the set. The set becomes $\{[1,9],[10,11]\}.$ Terminate.

The general procedure is: When adding an interval $[u,v]$ to the set $S$,

1. if no interval in $S$ intersects with $[u,v],$ then add it by `insert()` method.
2. otherwise, find the interval $[l,r]\in S$ that intersects with $[u,v].$
3. combine them to get $[\min(u,l),\max(v,r)]$ and make it the new $[u,v].$
4. remove $[l,r]$ from $S.$ Repeat step 1.

#### Derive the answer

* Let $[l,r]$ be the intersection of intervals from case 2, then $a\in[l,r].$

* Let $S$ be the union of intervals from case 1, then $a$ is not contained by any interval in $S$.

We may reformulate the second point: "$[a,a]$ does not intersect with any interval in $S.$" This makes our lives easier as we may use `find()` method to check if there is an interval in $S$ that is 'equal' to $[a,a],$ which means there is an interval that intersects with $[a,a].$

Lastly, if $a$ really exists, the number of operations is $(c+1-a)\bmod c.$ (Why?)

#### Complexity

Time: as there are $n$ strings, there are $O(n)$ restrictions (every comparison between adjacent strings gives at most one restriction). Each restriction in case 1 is an interval, which can only be inserted into the `set`, found by `find()`, and erased once. The `set` operations above take $O(\log n)$ times each (as the set has $O(n)$ elements), so overall the time complexity is $O(n\log n).$

Memory: $O(n).$

#### Code

In the following code, we use $[pl,pr]$ as the interval of 'possibility' (case 2). The `set` for case 1 is named `ip` for 'impossiblilty'.

```cpp
//This program is written by Brian Peng.
#include<bits/stdc++.h>
using namespace std;
#define Rd(a) (a=rd())
#define Gc(a) (a=getchar())
#define Pc(a) putchar(a)
int rd(){
	int x;char c(getchar());bool k;
	while(!isdigit(c)&&c^'-')if(Gc(c)==EOF)exit(0);
	c^'-'?(k=1,x=c&15):k=x=0;
	while(isdigit(Gc(c)))x=x*10+(c&15);
	return k?x:-x;
}
void wr(int a){
	if(a<0)Pc('-'),a=-a;
	if(a<=9)Pc(a|'0');
	else wr(a/10),Pc((a%10)|'0');
}
signed const INF(0x3f3f3f3f),NINF(0xc3c3c3c3);
long long const LINF(0x3f3f3f3f3f3f3f3fLL),LNINF(0xc3c3c3c3c3c3c3c3LL);
#define Ps Pc(' ')
#define Pe Pc('\n')
#define Frn0(i,a,b) for(int i(a);i<(b);++i)
#define Frn1(i,a,b) for(int i(a);i<=(b);++i)
#define Frn_(i,a,b) for(int i(a);i>=(b);--i)
#define Mst(a,b) memset(a,b,sizeof(a))
#define File(a) freopen(a".in","r",stdin),freopen(a".out","w",stdout)
#define N (1000010)
int n,c,w[2][N],l[2],pl(1),pr;
bool t;
struct T{int l,r;
	bool operator<(T b)const{return r<b.l;}
};
set<T>ip;//set of case 1
set<T>::iterator it;
void mdf(int u,int v);//adding a restriction "u is less than v in the alphabet"
signed main(){
	Rd(n),pr=Rd(c);//the possibility interval is originally set as [1,c]
	Rd(l[t]);
	Frn1(i,1,l[t])Rd(w[t][i]);
	Frn1(i,2,n){
		t^=1,cin>>l[t];
		Frn1(i,1,l[t])Rd(w[t][i]);
		w[t][l[t]+1]=0;//set the empty character
		Frn1(i,1,l[t^1])if(w[t][i]!=w[t^1][i]){
			if(!w[t][i])wr(-1),exit(0);//the case when the empty character
			//is greater than another character, which is impossible
			mdf(w[t^1][i],w[t][i]);//add restriction
			break;
		}
	}
	Frn1(i,pl,pr)if(ip.find({i,i})==ip.end())wr((c+1-i)%c),exit(0);
	//check whether i is in the interval [pl,pr] for case 2
	//while not contained in the set for case 1
	wr(-1),exit(0);
}
void mdf(int u,int v){
	if(u<v){//case 1
		++u;//the interval added is [u+1,v]
		while((it=ip.find({u,v}))!=ip.end())//find the interval in the set
		//that intersects with it
			u=min(u,it->l),v=max(u,it->r),ip.erase(it);//combine and remove
		ip.insert({u,v});//insert the combined interval
	}else pl=max(pl,v+1),pr=min(pr,u);//case 2
}

```

### Extension

What if the question becomes that you can reorder the alphabet to any permutation of $\{1,\cdots,c\}$?

We still need to find the restriction between characters. But now, as we don't have a specific reordering pattern, we may treat each restriction $u\prec v$ as a directed edge $u\to v$ in a graph with vertices $\{1,\cdots, c\}.$ Then, we may find the reordering of the alphabet as a topological ordering of the vertices, if it exists (i.e. the graph is a DAG).

Do you want to ask me why I thought about this? Because I originally thought this is the solution, but I found it too difficult to find a topological order being a cycle of $(1,2,\cdots,n).$ Eventually, I came up with this solution, making use of the reordering being a cycle.

*A slight change in question leading to a totally different method,* ~~maybe this is just why algorithms are so intriguing...~~

#### Thanks for your reading. ありがとう！


---

