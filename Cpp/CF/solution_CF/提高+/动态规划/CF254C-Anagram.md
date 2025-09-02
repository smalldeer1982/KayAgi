# Anagram

## 题目描述

String $ x $ is an anagram of string $ y $ , if we can rearrange the letters in string $ x $ and get exact string $ y $ . For example, strings "DOG" and "GOD" are anagrams, so are strings "BABA" and "AABB", but strings "ABBAC" and "CAABA" are not.

You are given two strings $ s $ and $ t $ of the same length, consisting of uppercase English letters. You need to get the anagram of string $ t $ from string $ s $ . You are permitted to perform the replacing operation: every operation is replacing some character from the string $ s $ by any other character. Get the anagram of string $ t $ in the least number of replacing operations. If you can get multiple anagrams of string $ t $ in the least number of operations, get the lexicographically minimal one.

The lexicographic order of strings is the familiar to us "dictionary" order. Formally, the string $ p $ of length $ n $ is lexicographically smaller than string $ q $ of the same length, if $ p_{1}=q_{1} $ , $ p_{2}=q_{2} $ , ..., $ p_{k-1}=q_{k-1} $ , $ p_{k}&lt;q_{k} $ for some $ k $ ( $ 1<=k<=n $ ). Here characters in the strings are numbered from 1. The characters of the strings are compared in the alphabetic order.

## 说明/提示

The second sample has eight anagrams of string $ t $ , that can be obtained from string $ s $ by replacing exactly two letters: "ADBADC", "ADDABC", "CDAABD", "CDBAAD", "CDBADA", "CDDABA", "DDAABC", "DDBAAC". These anagrams are listed in the lexicographical order. The lexicographically minimum anagram is "ADBADC".

## 样例 #1

### 输入

```
ABA
CBA
```

### 输出

```
1
ABC
```

## 样例 #2

### 输入

```
CDBABC
ADCABD
```

### 输出

```
2
ADBADC
```

# 题解

## 作者：JK_LOVER (赞：5)

## 题意
给出 $S$ ， $T$ 两条长度相同的字符串。求让 $S$ 的字符和 $T$ 完全相同，所需要的最小步数。并求出字典序最小的一种。
## 分析
可以发现，对于字符串 $S$ 来说。只需要让
$$
sumS[i] = sumT[i] (i\in U)
$$
那么
$$
ans = \sum_{i\in U}(sumT[i]-sumS[i])\times [sumS[i]<sumT[i]]
$$
贪心的考虑如何让字典序最小。那么就是让多出来的字符尽量靠前。开个桶就可以了。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int read()
{
	int x = 0,f = 0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-'0';ch=getchar();}
	return f?-x:x;
}
const int N = 2100100;
char A[N],B[N],heap[N];
int sumA[30],sumB[30],n,top;
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	scanf("%s%s",A+1,B+1);
	n = strlen(A+1);
	for(int i = 1;i <= n;i++)
	{
		sumA[A[i]-'A'+1]++;
		sumB[B[i]-'A'+1]++;
	}
	for(int i = 26;i >= 1;i--)
	{
		for(int j = sumA[i];j <= sumB[i]-1;j++)
		{
			heap[++top] = char(i-1)+'A';
		}
	}
	printf("%d\n",top);
	for(int i = 1;i <= n;i++)
	{
		int ch = A[i] - 'A' + 1;
		if(sumA[ch] > sumB[ch] && (heap[top] < A[i] || !sumB[ch]))
		{
			cout<<heap[top];
			//putchar(heap[top]),
			--sumA[ch],--sumB[heap[top--]-'A'+1];
		 } 
		
		else 
		{
			cout<<A[i];
			//putchar(A[i]);
			--sumA[ch],--sumB[ch];
		}
	}
	cout<<endl;
}
```


---

## 作者：EnofTaiPeople (赞：3)

虽然此题是蓝题，但简单的算法以及 24 行的 AC 代码让我不得不认为难度在黄色以下。

算法：贪心。

AC 时间：15 分钟。

设第一个字符串为 st1，第二个为 st2，长度为 len，nc[ch-'A'] 为 st1 中 ch 字符的个数，nd[ch-'A'] 为 st2 中 ch 字符的个数，并进行如下处理：
```cpp
for(i=0;i<T;++i){
        if(nd[i]>nc[i])nd[i]-=nc[i],nc[i]=0,ans+=nd[i];
        else nc[i]-=nd[i],nd[i]=0;
        hc[i]=nc[i];
}
```
给大家解释一下，对于每个字符 ch，如果 st1 中数量更多，则多出来的字符要在替换时替换成少的字符，将这些多出来的字符累加，就是第一行的答案；如果 st1 中的数量不多于 st2，那么之前多的字符就要被替换少的字符。从此之后，nd[ch-'A'] 表示需要替换成 ch 的字符个数，nc[ch-'A'] 表示 st1 中剩余需要替换的 ch 字符个数，hc[ch-'A'] 表示st1 中接下来还存在的 ch 字符个数。

第一步答案得出来了，接下来考虑字典序最小的方案，下面介绍字典序最小的贪心策略：
1. 方案：从第一个字符开始，如果必须要替换，即 $nc[ch-'A']=hc[ch-'A']$，那么将其替换成待替换字符中最小的；如果不能替换，即 $nc[ch-'A']=0$，则不替换；如果都可以，即 $nc[ch-'A']>hc[ch-'A']$，如果当前字符比代替换字符中最小的字符小，则不替换，否则替换。
2. 正确性：该方案从前往后确定了答案中字符的最小化，满足字典序最小化以及无后效性。


如果还没有听懂，看一下下面这 24 行 AC 代码：
```cpp
#include<cstdio>
#include<cstring>
const int N=1e5+5,T=26;
char st1[N],st2[N],nt='A';
int hc[N],nc[N],nd[T],len,i,ans;
int main(){
    freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
    scanf("%s%s",st1+1,st2+1);
    len=std::strlen(st1+1);
    for(i=1;i<=len;++i){
        ++nd[st2[i]-'A'];++hc[st1[i]-'A'];++nc[st1[i]-'A'];
    }for(i=0;i<T;++i)
        if(nd[i]>nc[i])nd[i]-=nc[i],nc[i]=0,ans+=nd[i];
        else nc[i]-=nd[i],nd[i]=0;
    while(nd[nt-'A']==0&&nt<='Z')++nt;
    for(i=1;i<=len;++i){
        if(nc[st1[i]-'A'])
            if(nc[st1[i]-'A']==hc[st1[i]-'A']||st1[i]>nt){
                --nd[nt-'A'];--nc[st1[i]-'A'];--hc[st1[i]-'A'];
                st1[i]=nt;while(nd[nt-'A']==0&&nt<='Z')++nt;
            }--hc[st1[i]-'A'];
    }printf("%d\n%s\n",ans,st1+1);return 0;
}
```

---

## 作者：abort (赞：2)

**提醒：记得加 freopen。**  
~~我被卡了半天~~


### 题目理解  
本题的核心任务是将字符串 $ s $ 通过最少的字符替换操作，转换为字符串 $ t $ 的变位词。如果存在多个最少操作次数的结果，要输出字典序最小的那个。

### 题目分析
我们可以很快得出 $ans = \sum_{i=1}^{n} |a_i - b_i|$ 的最小步骤为 $ans / 2$。\
然后我们可以通过枚举 $S$，并找字母来替代他，来求最小的字典序字符串。

### Code
```cpp
#include <bits/stdc++.h>

using namespace std;

string A, B;
int a[30], b[30];
int cnt1[30], cnt2[30];
void read()
{
	cin >> A;
	cin >> B;
}
void solve()
{
	for (int i = 0; i < A.size(); i++)
	{
		a[A[i] - 'A' + 1]++;
	}
	for (int i = 0; i < B.size(); i++)
	{
		b[B[i] - 'A' + 1]++;
	}
	int ans = 0;
	for (int i = 1; i <= 26; i++)
	{
		int num = abs(a[i] - b[i]);
		ans += num;
		if (a[i] >= b[i])
		{
			cnt1[i] += num;
		}
		else
		{
			cnt2[i] += num;
		}
	}
	cout << ans / 2 << endl;
	for (int i = 0; i < A.size(); i++)
	{
		a[A[i] - 'A' + 1]--;
		if (cnt1[A[i] - 'A' + 1])
		{
			for (int j = 1; j <= 26; j++)
			{
				if (j >= A[i] - 'A' + 1 && a[A[i] - 'A' + 1] >= cnt1[A[i] - 'A' + 1])
				{
					break;
				}
				if (cnt2[j])
				{
					cnt1[A[i] - 'A' + 1]--;
					cnt2[j]--;
					A[i] = char('A' + j - 1);
					break;
				}
			}
		}
			
	}
	cout << A << endl;
}


int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	solve();
	return 0;
}
```

---

## 作者：kinglf (赞：0)

**吐槽一下，这题需加 freopen 才能过，卡了我整整两天啊！建议管理员修一下题面，提醒一下。**

## [题意描述](https://www.luogu.com.cn/problem/CF254C)

## 解题思路
有两个字符串 $S$ , $T$ , 长度相同，且都小于或等于 $10^5$ 显然只有线性做法才能过。

定义 $ans$ 为不同字母的个数，易得， $ans=\sum_{i=A}^{Z} \ |boxs[i]-boxt[i]|$ 最小步骤数即 $ans\div2$ ,因为每有一对不同的字符，就要改一次 $S$ 。

然后就是求字典序最小的变换后的 $S$ ，只需要遍历一遍 $S$ ，找不同字母更换就好了。有一个小小的优化（易错点）详见代码。

## AC 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll N=2e6+10;
ll ans=0,cnt1,cnt2,box1[520],box2[520],dft1[520],dft2[520];
char s1[N],s2[N];
int main(){
    freopen("input.txt", "r", stdin);//必须加上，血与泪的教训 
	freopen("output.txt", "w", stdout);//必须加上，血与泪的教训 
	cin.tie(0);
	cin>>s1+1>>s2+1;
	ll len=strlen(s1+1);
	for (ll i=1;i<=len;i++){
		box1[s1[i]]++;
		box2[s2[i]]++;
	}//用桶统计S、T串的各个字母数 
	for (ll i='A';i<='Z';i++){
		ll temp=abs(box1[i]-box2[i]);//temp即两串各字母的差异 
		ans+=temp;             
		if (box1[i]>box2[i]) dft1[i]=temp;
		if (box2[i]>box1[i]) dft2[i]=temp;
	}
	ans/=2;//最小步数 
	for (ll i=1;i<=len;i++){
		box1[s1[i]]--;
		if (dft1[s1[i]]){
			for (ll j='A';j<='Z';j++){
				if (j>=s1[i]&&box1[s1[i]]>=dft1[s1[i]]) break;//非常重要的优化，不加会错 
				if (dft2[j]){
					dft1[s1[i]]--;
					s1[i]=j;
					dft2[j]--;
					break;
				}
			}
		}
	}
	printf ("%lld\n%s\n",ans,s1+1);//大功告成！ 
	
	return 0;
} 
```

---

## 作者：_Cheems (赞：0)

我们用桶 $buc$ 记录每个字符在 $S$ 中的个数减去在 $T$ 中的个数，我们称 $buc<0$ 的字符为 $1$ 类字符，$buc>0$ 的字符为 $2$ 类字符。

显然我们需要且仅需要将 $2$ 类字符换成 $1$ 类字符，于是第一问的答案为 $2$ 类字符的 $buc$ 之和。

然后是第二问。字典序最小，考虑贪心。我们从左往右遍历 $S$ 并维护 $buc$，然后分类讨论。

* $S_i$ 是二类字符：
	* 如果能找到当前最小的满足 $c<S_i$ 的一类字符 $c$，则将 $S_i$ 换成 $c$。
    
   * 如果不能，则判断当前字符是否必须操作，如果是则找到当前最小的一类字符 $c$，并将 $S_i$ 换成 $c$。否则不需操作。
   
* $S_i$ 不是二类字符：跳过即可。

正确性显然，复杂度 $O(n)$，带个 $26$ 的常数。

最后有个坑，就是这道题需要 `freopen`。。。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
 
const int N = 1e5 + 5, P = 26;
int n, buc[P], ans, s[N], mp[P];
char a[N], b[N];
 
signed main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%s%s", a + 1, b + 1);
	n = strlen(a + 1);
	for(int i = 1; i <= n; ++i) ++buc[a[i] - 'A'], --buc[b[i] - 'A'];
	for(int i = n; i >= 1; --i) s[i] = s[mp[a[i] - 'A']] + 1, mp[a[i] - 'A'] = i;
	for(int i = 1; i <= n; ++i){
		if(buc[a[i] - 'A'] > 0){
			int id = -1, id2 = -1;
			for(int j = P; ~j; --j)
				if(buc[j] < 0){
					id2 = j;
					if(j < a[i] - 'A') id = j;
				}
			if(id == -1){
				if(s[i] <= buc[a[i] - 'A']) {
					++buc[id2], --buc[a[i] - 'A'], ++ans;
					a[i] = char('A' + id2);
				}
			}
			else{
				++buc[id], --buc[a[i] - 'A'], ++ans;
				a[i] = char('A' + id);
 			}
		}
	}
	printf("%d\n%s", ans, a + 1);
	return 0;
}
```


---

## 作者：EatBread (赞：0)

## 贪心

#### 关于第一问：

（$T$，$S$ 指题目给的两个字符串）

第一问十分的简单，用一个桶就可以解决（也可以不用）。

首先，很容易得出**字符串 $T$ 的字符的顺序根本不重要**，这里不做解释。

所以可以拿桶直接存 $T$，$S$ 中每个字符出现的次数，然后统计有多少个字符是 $T$ 有，但是 $S$ 没有的，然后输出数量就行了。

证明：对于 $T$ 有，但是 $S$ 没有的字符，就需要一次替换来补上这个字符。

#### 关于第二问：

首先不难想到，要先对需要被补上的字符从小到大排序，因为题目要求字典序最小，所以越前面的字符要越小，排序可以方便计算。

然后从前往后遍历 $S$ 中的每个字符，如果**它是多余的（多余的定义：$S$ 中有，但是 $T$ 没有的字符）**，那么进行判断它要不要被替换。

$1.$ 如果需要被补上的最小的那个字符比当前 $S$ 的这个字符小，那么它要被替换。

$2.$ 如果在这个字符后面，剩下的和他一样的字符不够了（就是假如这个字符多出了 $s$ 个，但是后面只有 $s-1$ 了），那么当前字符就必须被替换。

证明：

对于第 $1$ 点，因为替换了字典序更小，所以要进行替换。

对于第 $2$ 点，是必须的，否则不满足题意。


注意事项：

$1.$ 这题要用 `freopen` 十分的坑，不知道怎么写的人可以看题解抄就行。

$2.$ 注意实时更新桶排序，也就是实时判断 $S$ 和 $T$ 中每个字符还剩多少个。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+5;
int n,k,d=1,s[N],s2[N],ans;
char c[N],c2[N],da[N];
struct sb{
	int a,sum;
}h[N];
signed main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	cin>>c+1>>c2+1;
	n=strlen(c+1);
	for(int i=1; i<=n; i++)s[c[i]-'A'+1]++,s2[c2[i]-'A'+1]++;
	for(int i=1; i<=26; i++)if(s[i]<s2[i])h[++k].a=i,h[k].sum=s2[i]-s[i],ans+=h[k].sum;
	for(int i=1; i<=n; i++){
		int a=c[i]-'A'+1;
		if(s[a]>s2[a]){
			if(h[d].a>a&&s2[a])s[a]--,s2[a]--,da[i]=c[i];
			else{
				da[i]=h[d].a+'A'-1;
				h[d].sum--;
				s[a]--;	
				if(h[d].sum==0)d++;
			}
		}
		else da[i]=c[i];
	}
	cout<<ans<<"\n"<<da+1;
	return 0;
}
```


---

## 作者：Jin_Yichen (赞：0)

## 郑重声明
本题需要使用文件读写，就是这一点卡了我两个小时。

## 思路
其实和第二篇题解思路很类似，但这里多做一点解释：

1. 先把第一个字符串和第二个字符串中的字符整理出来，再比较有哪些字符的数量是不相等的。

2. 如果第一个字符串中的某个字符比第二个字符串中的这个字符少，那么第二个字符串中的这个字符就要替换成其他在第一个字符串中个数少于第二个字符串的字符。可能有点绕，多读几遍就顺了。

3. 为了使方案字典序最小，更改时应从小往大枚举。

其余解释很详细，参考第二篇题解的描述与代码。

---

