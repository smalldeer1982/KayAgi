# [ARC166A] Replace C or Swap AB

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc166/tasks/arc166_a

`A`, `B`, `C` からなる長さ $ N $ の文字列 $ X,\ Y $ が与えられます．

$ X $ に対して次の $ 3 $ 種の操作を（$ 0 $ 回を含め）何回でも行えるとき，$ X $ を $ Y $ と一致させることが可能であるか否かを判定してください．

- **操作 (1)**：$ X $ に含まれる文字 `C` をひとつ選び， `A` で置き換える．
- **操作 (2)**：$ X $ に含まれる文字 `C` をひとつ選び， `B` で置き換える．
- **操作 (3)**：$ X $ に含まれる部分文字列 `AB` をひとつ選び， `BA` で置き換える．より形式的には，$ X $ のうち $ i $ 文字目が `A` であり $ (i+1) $ 文字目が `B` であるような $ i $ を選び，$ X $ の $ i $ 文字目を `B` で，$ (i+1) $ 文字目を `A` で置き換える．
 
$ T $ 個のテストケースが与えられるので，それぞれについて答えを求めてください．

## 说明/提示

### 制約

- $ 1\leq\ T\leq\ 2\times\ 10^5 $
- $ 1\leq\ N\leq\ 2\times\ 10^5 $
- $ X,\ Y $ は `A`, `B`, `C` からなる長さ $ N $ の文字列である．
- $ 1 $ つの入力に含まれるテストケースについて，$ N $ の総和は $ 2\times\ 10^5 $ 以下である．
 
### Sample Explanation 1

\- $ 1 $ 番目のテストケースについて： $ 0 $ 回の操作により $ X $ を $ Y $ と一致させることが出来ます． - $ 2 $ 番目のテストケースについて： $ 1 $ 回の操作 (2) により $ X $ を $ Y $ と一致させることが出来ます． - $ 4 $ 番目のテストケースについて： $ 1 $ 回の操作 (3) により $ X $ を $ Y $ と一致させることが出来ます． - $ 6 $ 番目のテストケースについて： 例えば操作 (1), 操作 (3), 操作 (1) をこの順に適切な位置に対して行うと，$ X $ は `CCB` → `CAB` → `CBA` → `ABA` と変化して，$ Y $ と一致します．

## 样例 #1

### 输入

```
6
3 ABC ABC
1 C B
1 B C
2 AB BA
2 BA AB
3 CCB ABA```

### 输出

```
Yes
Yes
No
Yes
No
Yes```

## 样例 #2

### 输入

```
7
5 ABABA BABAB
5 ABCBC BBABA
5 CCCCC CBABC
5 BBAAA AAABB
5 AAABB BBAAA
5 ACACB BAACB
5 ACACB BBACA```

### 输出

```
No
Yes
Yes
No
Yes
Yes
No```

# 题解

## 作者：樱雪喵 (赞：5)

首先如果存在某个 $i$，使得 $Y_i$ 是 `C` 且 $X_i$ 不是，那么显然是不合法的，可以直接判掉。  
那么除去上述情况 $Y$ 中为字符 `C` 的位置 $X$ 也只能是 `C`。它们把字符串分成了若干段，可以把每一段分开单独考虑。  
对于只含 `A/B` 的一段 $Y$，我们可以根据个数得出 $X$ 在这段中应该把多少 `C` 替换成 `A`，剩下的换成 `B`。  
发现题意只能从 `AB` 换成 `BA`，等价于把某个 `A` 向后移一个位置。  
那我们希望我们放置的 `A` 尽量靠前，使最后能成功匹配的概率最大。因此根据已知数量，贪心地把靠前的 `C` 都替换成 `A`。  
判断当前 $X$ 中是否每个对应的 `A` 所在位置都不大于它在 $Y$ 中的目标位置即可。


```cpp
const int N=2e5+5;
int T,n;
char s[N],t[N];
vector<int> x,y;
bool solve()
{
	n=read();
	scanf("%s%s",s+1,t+1);
	int lst=0,cnt=0;
	s[n+1]=t[n+1]='C'; 
	for(int i=1;i<=n+1;i++)
	{
		if(t[i]=='C')
		{
			if(s[i]!='C') return 0;
			int cnta=0,cntb=0;
			int sa=0,sb=0;
			x.clear(),y.clear();
			for(int j=lst+1;j<i;j++) 
			{	
				if(t[j]=='A') y.push_back(j);
				if(t[j]=='A') cnta++; else cntb++;
				if(s[j]=='A') sa++;
				else if(s[j]=='B') sb++;
				if(t[j]=='C'&&t[i]!='C') return 0; 
			}
			if(sa>cnta||sb>cntb) return 0;
			for(int j=lst+1;j<i;j++)
			{
				if(s[j]!='C')
				{
					if(s[j]=='A') x.push_back(j);
					continue;
				}
				if(sa<cnta) sa++,x.push_back(j);
			}
			for(int j=0;j<x.size();j++) if(x[j]>y[j]) return 0;
			lst=i;
		}
	}
	return 1;
}
int main()
{
	T=read();
	while(T--)
	{
		int res=solve();
		if(res) printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}
```

---

## 作者：osfly (赞：3)

略带一点思维吧。

个人认为比 B 难想。

先来考虑弱化版的题面：

---

### Case 1

如果 $X$ 串和 $Y$ 串都没有字母 `C`，如何判断是否有解？

观察操作，我们能发现这个操作的本质实际上是让一个位于前面的字母 `A` 挪到其后面的任意的位置，并且前后两个 `A` 的相对位置不会发生改变。

所以，如果：

1. $X$ 串与 $Y$ 串长度相等。

2. $X$ 中 `A` 的数量与 $Y$ 串中 `A` 的数量相等。

3. 对 $X$ 串和 $Y$ 串中的 `A` 从前往后标号，每一组 $X$ 串中的 `A` 的位置比其对应标号的 $Y$ 的 `A` 的位置靠前。

以上三种情况均满足时有解。

解释一下第三种情况。

假设：

$$
\begin{aligned}
X:ABAABB\\
Y:ABBABA\\
\end{aligned}
$$

标号后为：

$$
\begin{aligned}
1\ 2\ 3\ 4\ 5\ 6\ \\
X:ABAABB\\
1\ \ \ \ 2\ 3\ \ \ \ \ \ \ \\
Y:ABBABA\\
1\ \ \ \ \ \ \ \ 2\ \ \ \ 3\\
\end{aligned}
$$

将对应标号的 `A` 的位置写出来为：

$$
\begin{aligned}
X:1\ 3\ 4\\
Y:1\ 4\ 6\\
\end{aligned}
$$

我们发现，相同的标号，$X$ 串的位置都比 $Y$ 串的位置前。

所以这种情况下就是有解的。

再比如：

$$
\begin{aligned}
X:ABABAB\\
Y:ABAABB\\
\end{aligned}
$$

标号后为：

$$
\begin{aligned}
1\ 2\ 3\ 4\ 5\ 6\ \\
X:ABABAB\\
1\ \ \ \ 2\ \ \ \ \ 3\ \ \ \\
Y:ABAABB\\
1\ \ \ \ \ 2\ 3\ \ \ \ \ \ \ \\
\end{aligned}
$$

将对应标号的 `A` 的位置写出来为：

$$
\begin{aligned}
X:1\ 3\ 5\\
Y:1\ 3\ 4\\
\end{aligned}
$$

我们发现，相同的标号，第三组 $X$ 串的位置比 $Y$ 串的位置后。

所以这种情况下就是无解的。

---

### Case 2

升级一下：

如果 $X$ 串有 `C`，$Y$ 串没有 `C`，如何判断是否有解？

根据 `Case 1`，我们知道首先 $X$ 串和 $Y$ 串 `A` 的数量要相等。

贪心地考虑，如果我们要使得 $X$ 串能变成 $Y$ 串，我们 `A` 越前越好。剩下的 `C` 就全部变成 `B` 就行了。

所以我们就能得出这一部分的有解的情况：

1. $X$ 串与 $Y$ 串长度相等。

2. $X$ 串 `A` 的数量加上 `C` 的数量要超过 $Y$ 串的 `A` 的数量。

3. $X$ 串 `A` 的数量不能超过 $Y$ 串的 `A` 的数量。

4. 若我们贪心地把 $X$ 串用 `C` 来凑 `A` 使得 $X$ 串和 $Y$ 串的 `A` 的数量相等后，需要满足 `Case 1` 的条件 $3$。

---

### Case 3

就是原题了。

我们发现，如果存在一个 $i$ 使得 $X_i$ 不为 `C` 且 $Y_i$ 为 `C` 时一定无解。

去除掉这种无解的情况后，$Y$ 串剩余的 `C` 一定都能在 $X$ 串对应的位置找到 `C`。

考虑到操作不能使得 `C` 的位置交换，所以这些 `C` 我们不能把它们变成 `A` 或者 `B`。

此时，整个 $X$ 串和 $Y$ 串就被我们切割成若干段。

我们考虑每一段，此时问题就退化成 `Case 2` 的版本了。

单次询问时间复杂度 $O(n)$。

```
#include<cstdio>
const int N=2e5+10;
int T;
int n;
char s[N],t[N];
int ss[N],tt[N];
bool check()
{
	for(int i=1;i<=n;i++)
		if(s[i]!='C'&&t[i]=='C') return 0;
	int x[N],tot=0;
	x[++tot]=1;
	for(int i=1;i<=n;i++)//切割
		if(t[i]=='C'&&i!=1&&i!=n) x[++tot]=i;
	x[++tot]=n;
	for(int i=1;i<tot;i++)
	{
		int l=x[i],r=x[i+1];
		if(t[l]=='C') l++;
		if(t[r]=='C') r--;
		int sa=0,sc=0,ta=0;
		for(int j=l;j<=r;j++)
		{
			if(s[j]=='A') sa++;
			if(s[j]=='C') sc++;
			if(t[j]=='A') tt[++ta]=j;
		}
		if(sa+sc<ta) return 0;
		if(sa>ta) return 0;
		sc=ta-sa,sa=0;//计算出需要用多少个 C 去变成 A
		for(int j=l;j<=r;j++)
		{
			if(s[j]=='A') ss[++sa]=j;
			if(s[j]=='C'&&sc) ss[++sa]=j,sc--;//贪心地填补 A
		}
		for(int j=1;j<=sa;j++)
			if(ss[j]>tt[j]) return 0;
	}
	return 1;
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%s%s",&n,s+1,t+1);
		if(check()) printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}
```

---

## 作者：lin_A_chu_K_fan (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_arc166_a)
# 题意
给定仅包含大写字母 `A`、`B`、`C`两个长度为 $n$ 的字符串 $X$ 和 $Y$，并规定以下操作：

- 将 $X$ 中的其中一个 `C` 替换成 `A`或 `B`。
- 将 $X$ 中的一个 `AB` 替换为 `BA`。

问能否让 $X$ 变成 $Y$。
# 思路
首先，如果存在 $1 \le i \le N$，使得 $Y_i$ 为 `C` 且 $X_i$ 不是，那么显然不合法，输出 `No`。

因为所有 `C`，可以用若干 `C` 把两个串分成若干段。

还可得，操作二、操作三只能在段内操作，且对于 $X$ 串，其中的 `A` 不能向前移动，`B` 不能向前移动，然后在每个段内模拟即可。

代码就不给了，求关~

---

## 作者：No21 (赞：1)

### 解题思路

一道小模拟，大概黄题难度吧，思路不算很难，实现也很简单（但蒟蒻赛时被小细节卡到 30 分钟才过 qwq） 。

首先，不难发现，A 串中没有任何方法可以在一个不是 C 的位置上创造一个 C，即在 B 串中是 C 的位置在 A 串中初始也必须是 C 而且这个位置的 C 不能被改变，如果有一个位置 B 串中是 C 但是 A 串中不是，那么直接输出 No 即可。否则，A 和 B 两个串均会被起点、终点和每一个 C 分成若干块。

不难发现，操作二和操作三只能在每个块内操作，而且对于 A 串来说，其中的 A 只能向后移动，B 只能向前移动，然后直接在块内模拟处理即可。

```
#include<bits/stdc++.h>
using namespace std;
namespace TO
{
    const int N=2e5+21;
    int t,n,tot=1;
    int k[N];
    int mian()
    {
        cin>>t;
        while(t--)
        {
            cin>>n;
            string a,b;
            cin>>a>>b;
            tot=1;
            k[tot++]=-1;
            bool v=0;
            for(int i=0;i<b.size();i++)
            {
                if(b[i]=='C')
                    k[tot++]=i;
                if(b[i]=='C'&&a[i]!='C')
                {
                    v=1;
                    break;
                }
            }
            if(v==1)
            {
                cout<<"No"<<'\n';
                continue;
            }
            k[tot]=b.size();
            for(int i=1;i<tot;i++)
            {
                int aa=0,bb=0,cc=0;
                for(int j=k[i]+1;j<k[i+1];j++)
                {
                    if(a[j]=='A')
                        aa++;
                    if(a[j]=='C')
                        cc++;
                    if(b[j]=='A')
                    {
                        if(aa==0)
                            cc--;
                        else
                            aa--;
                        if(cc<0)
                        {
                            v=1;
                            break;
                        }
                    }
                }
                if(v==1)
                    break;
                cc=0;
                for(int j=k[i+1]-1;j>k[i];j--)
                {
                    if(a[j]=='B')
                        bb++;
                    if(a[j]=='C')
                        cc++;
                    if(b[j]=='B')
                    {
                        if(bb==0)
                            cc--;
                        else
                            bb--;
                        if(cc<0)
                        {
                            v=1;
                            break;
                        }
                    }
                }
                if(v==1)
                    break;
            }
            if(v==1)
                cout<<"No"<<'\n';
            else
                cout<<"Yes"<<'\n';
        }
        return 0;
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    return TO::mian();
}
```

---

## 作者：__AFO__ (赞：0)

# 题解

[题目传送门](https://www.luogu.com.cn/problem/AT_arc166_a)

## 题目分析

题目中给出了三种操作方式，我们可以发现 $C$ 可以转换为剩余的两个字符，而第三种操作实际上只是把 $A$ 向后移了一位。

由此我们可以知道，因为任何字符都无法变成 $C$，可以先特判，如果第 $2$ 个字符串中有 $C$，那么在第一个字符串中相同的位置不是 $C$,这种情况就是不合法的。

所以我们可以利用 $C$ 的这一特点，将字符串分为几个只有 $A$ 和 $B$ 的字符串，利用第三个操作可以知道 $A$ 越靠前越好，所以，如果 $A$ 数量不够，优先选择靠前的 $C$ 来转换，按照这个操作依次讨论即可。

## 代码详解：


```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n;
string s,k; 
struct nn{
	long long l,r;
}a[200005],cnt[200005];//a数组统计区间的左右端点，cnt数组同每一个区间里两个字符串A字符的位置 
int main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%lld",&n);
		cin>>s>>k;
		long long p=0,q=0,h=0,f=0,w=0;
		for(long long i=0;i<n;i++){
			if(k[i]=='C'){//记录区间 
			q=i-1;
			if(q>=p){
			h++;
			a[h].l=p;
			a[h].r=q;
			}		
			p=i+1;
			if(s[i]!='C'&&k[i]=='C'){//如果不满足C的情况 
				f=1;
				break; 
			}	
			}
		}
		if(k[n-1]!='C'){
			h++;
			a[h].l=p;
			a[h].r=n-1;
		}
		if(f==1) printf("No\n");
		else{
			for(long long i=1;i<=h;i++){
				long long aa=0,bb=0,x=0,y=0,r=0;
				for(long long j=a[i].l;j<=a[i].r;j++){//统计字符个数 
					if(s[j]=='A') aa++;
					if(s[j]=='B') bb++;
					if(k[j]=='A') x++;
					if(k[j]=='B') y++;
					if(s[j]=='C') r++;
				}
				if(aa>x||bb>y||aa+r<x||bb+r<y){//若无论如何操作个数都不符合的情况 
					printf("No\n");
					w=1;
					break;
				}
				r=x-aa;//算出有多少个C要变成A 
				long long o=0,l=0;
				for(long long j=a[i].l;j<=a[i].r;j++){//记录两个字符串A的位置 
					if(r>0&&s[j]=='C'){
						r--;
						o++;
						cnt[o].l=j;
					}
					if(s[j]=='A'){
						o++;
						cnt[o].l=j;
					}
					if(k[j]=='A'){
						l++;
						cnt[l].r=j;
					}
				}
				for(long long j=1;j<=o;j++){
					if(cnt[j].l>cnt[j].r){//只要第一个字符串A的位置一直大于另一个字符串A的位置就是可行的，否则无法完成 
						printf("No\n");
						w=1;
						break;
					}
				}
				if(w==1) break;
			}
			if(w!=1){
				printf("Yes\n");
			}
		}
	}
	return 0;
}
```

---

## 作者：Phartial (赞：0)

没想到吧这题其实可以直接嗯做。

由于没有产生 $\texttt{C}$ 的变换，$Y$ 中的 $\texttt{C}$ 必然未经过任何操作，由此可以将 $Y$ 分割成若干个只由 $\texttt{AB}$ 组成的块，对于每个块，我们从左往右扫，考察每一位：

- $X_i=\texttt{A}$，$Y_i=\texttt{A}$：不用管；
- $X_i=\texttt{A}$，$Y_i=\texttt{B}$：那么我们需要从后面搬一个 $\texttt{B}$ 过来，记录一下需要搬的 $\texttt{B}$ 个数；
- $X_i=\texttt{B}$，$Y_i=\texttt{B}$：不用管；
- $X_i=\texttt{B}$，$Y_i=\texttt{A}$：如果前面需要搬一个 $\texttt{B}$ 就移过去，否则尝试把之前 $\texttt{C}$ 变的一个 $\texttt{B}$ 改为 $\texttt{A}$，然后把之后的 $\texttt{B}$ 整体往前移，如果不存在则无解；
- $X_i=\texttt{C}$，$Y_i=\texttt{A}$：如果前面需要搬一个 $\texttt{B}$ 就把这一位变成 $\texttt{B}$ 然后移过去，否则变 $\texttt{A}$；
- $X_i=\texttt{C}$，$Y_i=\texttt{B}$：直接变 $\texttt{B}$。

模拟一下这个过程，每块结束后看还需不需要从后面搬 $\texttt{B}$ 过来即可。

时间复杂度线性。

[code](https://atcoder.jp/contests/arc166/submissions/56903454).

---

## 作者：DerrickLo (赞：0)

我们可以发现在操作的过程中 `B` 字符的位置只会往前，而不会往后。

我们又发现如果 $Y$ 串中有 `C` 字符，则 $X$ 串中这个字符必须是 `C`，这样就能把 $X$ 串通过 $B$ 串中的 `C` 字符分割成若干段。

那么我们可以贪心的将 `C` 字符变成 `A` 字符和 `B` 字符，对于每个分割后的段，我们把后面的 `C` 都换成 `B`，前面的 `C` 都换成 `A`，然后判断是否符合条件就行了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,aa[200005],bb[200005];
string a,b;
signed main(){
	cin>>t;
	while(t--){
		cin>>n>>a>>b;
		a=" "+a+"C",b=" "+b+"C";
		int flag=1,cntc=0,cntaa=0,cntab=0,cntba=0,cntbb=0,cnt0=0,cnt1=0;
		for(int i=1;i<=n;i++)if(b[i]=='C'&&a[i]!='C'){
			flag=0;
			break;
		}
		if(!flag){
			cout<<"No\n";
			continue;
		}
		for(int i=1;i<=n+1;i++){
			if(b[i]=='C'){
				if(cntaa>cntba||cntab>cntbb){
					flag=0;
					break;
				}
				if(cntba-cntaa+cntbb-cntab!=cntc){
					flag=0;	
					break;
				}
				int cnt=0;
				for(int j=i-1;j>=1&&b[j]!='C';j--){
					if(a[j]=='C'){
						cnt++;
						if(cnt<=cntbb-cntab)a[j]='B';
						else a[j]='A';
					}
				}
				cntc=cntaa=cntab=cntba=cntbb=0;
			}
			else{
				if(a[i]=='C')cntc++;
				if(a[i]=='B')cntab++;
				if(a[i]=='A')cntaa++;
				if(b[i]=='B')cntbb++;
				if(b[i]=='A')cntba++;
			}
		}
		if(!flag){
			cout<<"No\n";
			continue;
		}
		for(int i=1;i<=n;i++)if(a[i]=='B')aa[++cnt0]=i;
		for(int i=1;i<=n;i++)if(b[i]=='B')bb[++cnt1]=i;
		sort(aa+1,aa+cnt0+1);
		sort(bb+1,bb+cnt1+1);
		for(int i=1;i<=cnt0;i++)if(aa[i]<bb[i]){
			flag=0;
			break;
		}
		if(!flag)cout<<"No\n";
		else cout<<"Yes\n";
	}
	return 0;
}
```

---

## 作者：PP__ (赞：0)

黄题。

首先我们发现操作只能将 $X_i =C$ 转换成 $A$ 或 $B$，不能将 $X_i = A | B$ 转换成 $X_i = C$。那么显然我们如果要满足条件，那么对于每一个 $Y_i=C$ 的第 $i$ 位，$X_i$ 也必须为 $C$。如果一个区间全都是 $C$，那么 $X$ 里对应的区间也必须全部是 $C$。

那么我们可以用 $C$ 来把 $Y$ 分割成几个块。对于块内每个人，$Y_i=A|B$，那么我们考虑对于 $X_i$ 如何判断是否满足条件。

由于我们只能改变 $A,B$ 的位置，所以如果 $X$ 中 $A$ 的数量大于 $Y$ 的（对于 $B$ 同理），那么绝对无法完成。那么由于只能将 $AB$ 换成 $BA$ ，所以 $A$ 的位置只可能往后退。那么我们尽量将前面不够的 $C$ 换成 $A$ ，然后一一对应，如果位置往前移动了，则绝对不可能，否则如果一一对应都往后移动的话，则满足条件。

## AC CODE

```c++
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
int t,n,l,wei[200010];
string a,b;
bool check(int l,int r,bool fl)
{
	if(fl == 0)
	{
		for (int i = l;i <= r;i++)
		{
			if(a[i] != 'C')return 0;
		}
		return 1;
	}
	else
	{
		int cnt1 = 0,cnt2 = 0;
		for (int i = l;i <= r;i++)
		{
			if(b[i] == 'A')
			{
				cnt1++;
				wei[cnt1] = i;
			}
			if(b[i] == 'B')cnt2++;
		}
		int ccnt1 = 0,ccnt2 = 0,ccnt3 = 0;
		for (int i = l;i <= r;i++)
		{
			if(a[i] == 'A')ccnt1++;
			else if(a[i] == 'B')ccnt2++;
			else ccnt3++;
		}
		if(ccnt2 > cnt2 || ccnt1 > cnt1)return 0;
		int need = cnt1 - ccnt1,cccnt = 0;
		for (int i = l;i <= r;i++)
		{
			if(a[i] == 'A')
			{
				cccnt++;
				if(wei[cccnt] < i)return 0;
			}
			if(a[i] == 'C' && need)
			{
				a[i] = 'A';
				need--;
				cccnt++;
				if(wei[cccnt] < i)return 0;
			}
		}
		return 1;
	}
}
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		cin >> a >> b;
		bool fl = 1;
		int last = 0;
		for (int j = 1;j < n;j++)
		{
			if(b[j] == 'C' && b[j - 1] != 'C')
			{
				fl &= check(last,j - 1,1);
				last = j;
			}
			else if(b[j] != 'C' && b[j - 1] == 'C')
			{
				fl &= check(last,j - 1,0);
				last = j;
			}
		}
		if(b[n] == 'C')fl &= check(last,n,0);
		else fl &= check(last,n,1);
		if(fl)puts("Yes");
		else puts("No");
	}
	return 0;
}

```

---

## 作者：Eleveslaine (赞：0)

（难度建议：黄）

考虑 $Y_i=\tt C$ 的情况，因为不存在一种操作能产生新的 $\tt C$ 或移动 $\tt C$ 的位置，所以对应的 $X_i$ 必须也为 $\tt C$。这样我们可以按照所有 $Y_i=\tt C$ 的 $i$ 为分割点，把 $X,Y$ 分割成若干子串。

于是问题弱化到 $Y$ 不含 $\tt C$ 的情况。设 $X$ 中 $\tt A,B,C$ 的数量分别为 $x_1,y_1,z_1,Y$ 中 $\tt A,B$ 的数量分别为 $x_2,y_2$。那么首先要满足条件：$y_1\le y_2,x_1\le x_2,(y_2-y_1)+(x_2-x_1)\le z_1$，即 $\tt C$ 的数量足够变化出所需的 $\tt A,B$。

观察操作三的一些过程：

```plain
AAABB
AABAB
AABBA
ABABA
BAABA
```

可以发现，操作三本质上是把 $\tt B$ 不断地向左移动（把 $\tt A$ 向右移动），所以 $X$ 的每个 $\tt B$ 都应该不在 $Y$ 的左边（$X$ 的每个 $\tt A$ 都应该在 $Y$ 的左边）。在判断之前先从右往左贪心地把 $\tt C$ 替换成适当数量的 $\tt B$，数量足够则替换成 $\tt A$（先从左往右贪心地把 $\tt C$ 替换成适当数量的 $\tt A$，数量足够则替换成 $\tt B$）即可。

下面的代码实现了括号里的描述。


```cpp
bool solve(const int &n,string &s1,string &s2)
{
    int last=1;
    vector <pair<int,int> > vec; // 存子串端点
    for(int i=1;i<=n;++i) // 按 s2[i]=C 分割
        if(s2[i]=='C')
        {
            if(s1[i]!='C')
                return false;
            if(last<=i-1)
                vec.push_back({last,i-1});
            last=i+1;
        }
    if(last<=n)
        vec.push_back({last,n});
    for(auto x:vec)
    {
        int l=x.first,r=x.second,x1=0,y1=0,x2=0,y2=0,z1=0;
        vector <int> p1,p2; // 分别存储 s1,s2 中 A 的位置
        for(int i=l;i<=r;++i)
        {
            if(s1[i]=='A') ++x1;
            else if(s1[i]=='B') ++y1;
            else if(s1[i]=='C') ++z1;
            if(s2[i]=='A') ++x2;
            else if(s2[i]=='B') ++y2;
        }
        if(y1<=y2&&x1<=x2&&(y2-y1)+(x2-x1)<=z1)
        {
            int cntA=0;
            for(int i=l;i<=r;++i)
            {
                if(s1[i]=='C'&&cntA+1<=x2-x1)
                    s1[i]='A',++cntA;
                else if(s1[i]=='C')
                    s1[i]='B';
                if(s1[i]=='A')
                    p1.push_back(i);
                if(s2[i]=='A')
                    p2.push_back(i);
            }
            for(int i=0;i<x2;++i)
                if(p1[i]>p2[i])
                    return false;
        }
        else
            return false;
    }
    return true;
}
```

---

## 作者：ZnPdCo (赞：0)

建议评黄，贪心水题。

给定一个由 `A`，`B`，`C` 组成的长度为 $N$ 的字符串 $X$ 和 $Y$。

判断是否存在一系列的操作，使得通过以下操作可以将 $X$ 变为 $Y$。

1. 选择 $ X $ 中的一个字符 `C`，将其替换为 `A`。
2. 选择 $ X $ 中的一个字符 `C`，将其替换为 `B`。
3. 选择 $ X $ 中的一个子字符串 `AB`，将其替换为 `BA`。

---

因为 `A` 或者 `B` 是不能变成 `C` 的，也就是 `C` 不能凭空出现。

另外发现 `C` 是不能移动的（就算把它变成 `A` 或者 `B` 来移动后也不能变回 `C`），如果 `y` 是 `C`，`x` 不是 `C` 时，就说明不可能匹配成功，因为 `C` 是不能移动的。

如果 `x` 和 `y` 都是 `C` 时，如果把 `x` 中的 `C` 变成 `A` 或者 `B`，就会重现上面的 `y` 是 `C`，`x` 不是 `C` 的情况，所以当 `x` 和 `y` 都是 `C` 时，我们不能对这个 `C` 做任何操作。

那么 `C` 左边和右边形成了两个独立的区间，他们互不干涉。区间左边无法移动到区间右边，下面这张图来自官方题解，我感觉非常的清晰：

![](https://cdn.luogu.com.cn/upload/image_hosting/ik6zfxj5.png)

那么我们可以把这几个独立区间分开做。

因为把 `AB` 换为 `BA` 相当于把 `A` 向后移动一位，所以我们优先把 `C` 换成 `A`，这样满足匹配的**概率**更大。直到满足 `y` 中 `A` 的数量，贪心地去做。

那么如何判断是否合法呢？

发现，因为 `A` 只能后移，如果 $A_\text{from} > A_\text{to}$，那么是不能移动到的。

所以存下每次 `A` 的位置，如果当前 `x` 中**最小**的 `A` 的位置大于 `y` 中**最小**的 `A` 的位置，因为 `A` 没法向前移动，我们就认为这是无解的。

为什么是最小的，因为 `A` 是不能变成 `B` 或者 `C` 的，即不能凭空消失，所以只能用最小的，如果用其他的有漏匹配的风险。

另外，因为 `A` 是不能变成 `B` 或者 `C` 的，如果 `x` 的 `A` 或者 `B` 比 `y` 的 `A` 或者 `B` 还多的话，就认为不可能。

```c++
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define noSolve(); printf("No\n");return;
#define haveSolve(); printf("Yes\n");return;
ll t, n;
ll x_a, x_b, x_c, y_a, y_b;
ll last;
ll x_vec[200010], y_vec[200010];
char x[200010], y[200010];

inline void clear() {
	x_a = x_b = x_c = y_a = y_b = last = 0;
}
void fun() {
	scanf("%lld %s %s", &n, x+1, y+1);
	n++;
	x[n] = y[n] = 'C';
	clear();
	for(ll i = 1; i <= n; i++) {
		if(y[i] == 'C') {
			if(x[i] == 'C') {
				if(x_a > y_a || x_b > y_b) {
					noSolve();
				}
				
				for(ll j = last + 1; j < i; j++) {
					if(x[j] == 'C' && x_a < y_a) {
						x_vec[++x_a] = j;
					}
				}
				std::sort(x_vec + 1, x_vec + 1 + x_a, [](const ll &x, const ll &y){return x < y;});
				std::sort(y_vec + 1, y_vec + 1 + y_a, [](const ll &x, const ll &y){return x < y;});
				for(ll i = 1; i <= x_a; i++) {
					if(x_vec[i] > y_vec[i]) {
						noSolve();
					}
				}
				clear();
			}
			else if(x[i] != 'C' && y[i] == 'C') {
				noSolve();
			}
			last = i;
		} else {
			if(x[i] == 'A') x_vec[++x_a] = i;
			if(x[i] == 'B') x_b++;
			if(x[i] == 'C') x_c++;
			if(y[i] == 'A') y_vec[++y_a] = i;
			if(y[i] == 'B') y_b++;
		}
	}
	haveSolve();
}
int main() {
	scanf("%lld", &t);
	while(t--) {
		fun();
	}
} 
```

---

