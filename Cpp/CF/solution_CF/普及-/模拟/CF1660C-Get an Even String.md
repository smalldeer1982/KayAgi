# Get an Even String

## 题目描述

A string $ a=a_1a_2\dots a_n $ is called even if it consists of a concatenation (joining) of strings of length $ 2 $ consisting of the same characters. In other words, a string $ a $ is even if two conditions are satisfied at the same time:

- its length $ n $ is even;
- for all odd $ i $ ( $ 1 \le i \le n - 1 $ ), $ a_i = a_{i+1} $ is satisfied.

For example, the following strings are even: "" (empty string), "tt", "aabb", "oooo", and "ttrrrroouuuuuuuukk". The following strings are not even: "aaa", "abab" and "abba".

Given a string $ s $ consisting of lowercase Latin letters. Find the minimum number of characters to remove from the string $ s $ to make it even. The deleted characters do not have to be consecutive.

## 说明/提示

In the first test case you can remove the characters with indices $ 6 $ , $ 7 $ , and $ 9 $ to get an even string "aabbddcc".

In the second test case, each character occurs exactly once, so in order to get an even string, you must remove all characters from the string.

In the third test case, you can get an even string "aaaabb" by removing, for example, $ 4 $ -th and $ 6 $ -th characters, or a string "aabbbb" by removing the $ 5 $ -th character and any of the first three.

## 样例 #1

### 输入

```
6
aabbdabdccc
zyx
aaababbb
aabbcc
oaoaaaoo
bmefbmuyw```

### 输出

```
3
3
2
0
2
7```

# 题解

## 作者：Dedaka (赞：16)

## 题意简述

------------
- 给定 $T$ 组数据，每组数据包括一个字符串 $s$。

- 可删除字符串中任意个字母。

- 目标状态：最终的字符串长度是偶数，每个奇数位上的字母都和它下一位上的字母相同。

- 询问最少需删去的字母个数。

- $1 \leq t \leq 10^4$，$1 \leq \left| s \right| \leq 2 \times 10^5$。

## 题目分析

------------
本题有两种解法，本蒟蒻不会动态规划，是用 **贪心** 做的。

### 思路

------------
从前往后扫，用一个数组记录字母出现次数。如果当前字母出现两次，那么说明这个字母对可以 **最快匹配**，此时清空数组（其他字母肯定没有用了，否则不满足题目要求），同时记录总共的字母数减 $2$（一对）。最后剩下的个数就是所需删去的字母个数。

### 细节

------------
记得最后清空数组（有可能最后有未匹配的）！

## 代码

------------
```cpp
#include<bits/stdc++.h>
#define mx 30
using namespace std;
int t,c[mx];
string s;
int main(){
	cin>>t;
	while(t--){
		cin>>s;
		int l=s.length(),cnt=l;
		for(int i=0;i<l;i++){
			int tmp=s[i]-'a';
			c[tmp]++;
			if(c[tmp]==2){//该字母已匹配 
				cnt-=2;
				memset(c,0,sizeof(c));//清空 awa 
			}
		}
		cout<<cnt<<endl;
		memset(c,0,sizeof(c));
	}
	return 0;
}
```


---

## 作者：ajhuhe (赞：2)

# 题目简述

给定 $T$ 组测试数据，每组一个字符串 $s$，要删去若干字符后使 $s$ 满足：
1.长度为偶数。2.其中第 $i$ 位 ($i$ 为奇数) 字符与它的下一位字符相同。

# 题目分析

这道题既可采用**贪心**也可采用 **DP** 。但我的原则是能贪就贪，毕竟 DP 不是所有人都愿意去写的。
## 贪心策略

因为结果长度必须为偶数，又要有两两字符相等，那么可以得出一个初步的策略。用 cnt 数组记录每一个字符出现的次数，出现次数为偶数次的就是剩下的字符。那么答案就是总长度与剩下字符总数的差。但是通过模拟，发现样例的最后一组数据就出错了。

``
bmefbmuyw
``

经模拟后得到

``
bmbm
``

显然不符合要求。那么进一步贪心，每次统计到两个相同的字符时就清空 cnt 数组。这样做的好处是让两个相同字符之间的字符都失效，即无法与之后的字符匹配成一对。由于是每次统计到两个相同的字符时就清空 cnt 数组，所以两个相同字符之间一定没有其他相同字符了。
## 整理

遍历字符串 $s$ ，每统计到两个字符相同时就清空 cnt 数组，并记录这两个字符。最后用字符串总长度减去记录的总字符数即可。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int t,len,cnt[27];
int main()
{
	cin>>t;
	while(t--)
	{
		int sum=0;
		memset(cnt,0,sizeof(cnt));
		cin>>s;
		len=s.length();
		for(int i=0;i<len;i++)
		{
			cnt[s[i]-'a'+1]++;//桶思想，统计次数 
			if(cnt[s[i]-'a'+1]==2)//每出现相同字符就清空 cnt 数组 
			{
				memset(cnt,0,sizeof(cnt));
				sum+=2;//记录数量 
			}
		}
		cout<<len-sum<<endl;//输出答案 
	}
	return 0;
}
```

---

## 作者：ttq012 (赞：2)

这个题还是很有意思的。

**第一部分：题目大意**

定义一个字符串 $s$ 在长度 $n$ 是偶数并且对于任意的一个奇数 $i$ 都有 $s_i = s_{i+1}$，那么 $s$ 就是偶数的字符串。现在给定一个字符串 $t$，求字符串 $t$ **最少**删除几个字符之后变成偶数的字符串。

**第二部分：思路**

我们定义一个数组 $last_i$ 代表 $i$ 字符最后出现的下标时哪里，如果没有出现过是 $-1$，$next_i$ 代表下一个和 $t_i$ 字符一样的字符的下标的位置，如果没有就是 $-1$。

然后循环枚举每一个不等于 $-1$ 的 $last_i$，加入一个 $[i, last_i]$ 的区间。

然后就是区间覆盖问题了，定义 $cnt$ 为最多选择多少个区间让这些选择到的区间没有重叠（包括端点处），那么答案就是 $n-2\times cnt$。

时间复杂度瓶颈在于排序的 $O(\sum N\times \log \sum N)$。

**第三部分：代码**

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

int a[1000010];
int last[222222];
int nxt[1000010];

bool cmp(pair<int,int> a, pair<int,int> b) {
    return a.second < b.second;
}

signed main() {
    int T;
    cin >> T;
    while (T --) {
        string s;
        cin >> s;
        int n = s.size();
        for (int i = 0; i < 26; i ++)
            last[i] = -1;
        for (int i = 0; i < n; i ++)
            nxt[i] = -1;
        for (int i = 0; i < n; i ++) {
            if (last[s[i] - 'a'] != -1) {
                nxt[last[s[i] - 'a']] = i;
            }
            last[s[i] - 'a'] = i;
        }
        vector <pair<int,int> > qj;
        int cnt = 0;
        for (int i = 0; i < n; i ++)
            if (nxt[i] != -1)
                qj.push_back(make_pair(i, nxt[i]));
        int len = qj.size();
        sort (qj.begin(), qj.end(), cmp);
        int llast = -1;
        for (int i = 0; i < len; i ++)
            if (qj[i].first > llast) {
                llast = qj[i].second;
                cnt += 2;
            }
        printf ("%lld\n", n - cnt);
    }
    return 0;
}

```



---

## 作者：tZEROちゃん (赞：2)

> 给定字符串 $s$，删除尽可能少的元素使得 $a_i = a_{i + 1}$ 且 $i$ 奇数。

贪心即可。

题目要求使得删除的元素数量尽可能少，不难想到以下的贪心策略。

- 从前往后扫一遍，找到相同的就把中间的都删了。

这样显然所删除的元素是最少的，比如对于字符串 $s = \texttt{abcabcb}$，不妨设 $k$ 表示要删掉的字符数。

- $i = 1$，只有 $\tt a$ 一个字母，不管。
- $i = 2$，有 $\tt a, b$ 两个了，但是没有相同的，不管。
- $i = 3$，有 $\tt a, b, c$ 三个了，但是还是没有相同的，继续。
- $i = 4$，有两个 $\tt a$，将中间的都删掉，$k = 2$。
- $i = 5$，有两个 $\tt a$，但是前面处理过这部分了，我们就不管，还有一个 $\tt b$。
- $i = 6$，有 $\tt b, c$ 了，没有相同的。
- $i = 7$，有两个 $\tt b$，删掉 $\tt c$，$k = 3$。

所以答案是 $3$，不难发现这样是最优的。

```cpp
const int N = 200;
int a[N];

void solve() {
  string s;
  cin >> s;
  int ans = 0;
  LL len = s.size();
  memset(a, 0, sizeof a);
  for (int i = 0; i < len; ++i) {
    a[s[i]]++;
    if (a[s[i]] == 2) {
      memset(a, 0, sizeof a);
      ans += 2;
    }
  }
  printf("%d", s.size() - ans);
  putchar('\n');
  return ;
}

int main(){
  multiCase() solve();
  return 0;
}
```

---

## 作者：EtHereal_Algorithm (赞：1)

## CF1660C Get an Even String

upd 2022-4-20：修改了贪心思路。

这篇题解主要讲贪心的证明。

首先简述一下贪心的过程：

### 贪心的过程：

对于这个字符串 `aaabcbabbb`：

首先看第一个字符 `a`，往后找第一个和 `a` 相等的字符，就在它后面，删除中间的字符。（虽然没有）

继续，看第三个字符 `a`，暂时没有相同。

往后看：发现 `bcb` 可以匹配，那么前面的 `a` 什么的就没有用了。

继续，看第八个字符 `b`。往后找第一个和 `b` 相等的字符，在他后面，删除中间的字符。（虽然没有）

最后有多余的字符，全部删掉。

### 贪心的证明：

两个相同的字符（不妨设其为 `a`）之间的东西可以全部删掉，无非有这几种：

`axyza`，即中间没有任何重复的，显然全部删掉。

`abxba`，即中间存在一组相同的，那么我们如果保留 `aa`，那么 `bxb` 就没用了。和贪心的代价相同。

`abxyab`，即里面一个，外面一个形成相同的一组。那么考虑保留 `aa`，`bxyb` 就没有用了，和贪心的代价相同。

如果存在嵌套，如 `abccba`，同理可以得到：保留任意一组，剩下的都没有用了。`abcbca` 等情况同理。

### 贪心的代码：
```cpp
#include <bits/stdc++.h>
#define up(i,l,r) for(int i=(l);i<=(r);i++)
#define down(i,r,l) for(int i=(r);i>=(l);i--)
typedef long long ll;
using namespace std;
inline int read(){
    int f = 1, x = 0;
	char ch;
    do{ch = getchar();if(ch == '-')f = -1;}while(ch < '0' || ch > '9');
    do{x = x * 10 + ch - '0';ch = getchar();}while(ch >= '0' && ch <= '9');
    return f * x;
}
void print(int x){
	if(x > 9) print(x / 10);
	putchar(x % 10 + '0');
}
int bins[128];//桶思想记录出现次数
void clb()
{
	up(i, 0, 127) bins[i] = 0;
}
int main()
{
	int t;
	cin >> t;
	while(t--)
	{
		string str;
		cin >> str;
		int n, ans; ans = n = str.size();
		clb();//初始化
		//由于最后的需要删掉不好处理，所以我们把答案初始化为 n，每次删除操作就-2。
		up(i, 0, n - 1)
			if(++bins[int(str[i])] == 2)//一旦到达 2 个，
			{
				ans -= 2;//删掉
				clb();//中间的都没用了
			}
  		print(ans); puts("");
	}
	return 0;
}
```

---

## 作者：CodeMao (赞：1)

本蒟蒻第三篇题解。

这是一道好题，有那么一丢丢的思维。

下面讲一下**思路**：

- 读入部分省略。
  
- 答案为 $ans$ , $ans$ 初值为 $s$ 字符串的长度，因为后面要不断地减。
  
- 还有一个桶 $f$ , 用来记录每个字母出现的个数。
  
- 从前到后将 $s$ 串扫描一遍，每次统计每个字母出现的个数，然后判断这个字母是不是已经出现了两次，如果是的，则将 `ans-=2` , 然后将桶清空。
  
- 这里解释一下为什么要将桶清空：因为这个字母已经出现了两次，说明这个字母已经可以匹配了，所以现在统计的其他字母都没用了，所以将桶清空。
  
- 最后输出 $ans$ 即可。
  

下面附上 `AC` 代码：

```cpp
#include <cstdio>
#include <cstring> //strlen、memset函数所在的库
#define maxn 200005
#define maxm 35
using namespace std;
int t,ans;
int f[maxm];
char s[maxn];
inline void in(int &a){ //快速读入
    a=0;char ch=getchar();
    while(ch<'0'||ch>'9')
        ch=getchar();
    while(ch>='0'&&ch<='9'){
        a=(a<<1)+(a<<3)+(ch^48);
        ch=getchar();
    }
}
int main(){
    in(t);
    while(t--){
        memset(f,0,sizeof(f));
        scanf("%s",s);
        ans=strlen(s); //将ans赋值为s串的长度
        //strlen函数的作用是测量字符串的长度
        for(int i=0;s[i];++i){ //见思路
            f[s[i]-'a']++;
            if(f[s[i]-'a']==2){
                ans-=2;
                memset(f,0,sizeof(f));
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
```

---

## 作者：ivyjiao (赞：1)

这道题我是运用贪心和桶的思想去解的。

做法就是把字符串从前往后扫一遍，先假定为全部删除，然后扫到一个字符就存在桶里，如果这个字符出现了两次（匹配了）就将要删的数量减 $2$，然后清空桶。

注意多测要清空！字符串的下标是从 $0$ 开始的！

```cpp
#include<iostream>
#include<cstring>
using namespace std;
int t,ss[100];
string s;
int main(){
	cin>>t;
	while(t--){
		cin>>s;
		int len=s.length(),ans=len;
		for(int i=0;i<len;i++){//注意字符串的下标是从0开始的！
			int tt=s[i]-'a';
			ss[tt]++;//桶的思想
			if(ss[tt]==2){
				ans-=2;
				memset(ss,0,sizeof(ss));//必须清空
			}
		}
		cout<<ans<<endl;
		memset(ss,0,sizeof(ss));
	}
}

```


---

## 作者：Supor__Shoep (赞：0)

这里教大家一个做模拟题的诀窍——逆向思考。

正如题目所说的，要求最少删除字符的个数，那么我们就可以求出最多留下的字符的个数，然后用总个数减就可以了。

那么我们该怎么得出最多留下的字符的个数呢？非常简单，我们定义一个 $vis$ 数组，这个数组在找到 **一对** 字符之前都是有效的。我们在一个范围内扫一遍，如果找到了一对字符，那么我们就清空 $vis$ 数组，并且记录答案加二，因为已经找到了一对字符之后，中间所有的字符都是无效的，即必须删除，不过后面有没有字符可以与之配对。

于是我们就可以轻轻松松地过了此题。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int len;
char s[200005];
int vis[30];
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%s",s+1);
		len=strlen(s+1);
		int ans=0;
		memset(vis,0,sizeof(vis));
		for(int i=1;i<=len;i++)
		{
			if(vis[s[i]-'a'])
			{
				memset(vis,0,sizeof(vis));
				ans+=2;
			}
			else	vis[s[i]-'a']=1;
		}
		printf("%d\n",len-ans);
	}
	return 0;
}
```

---

## 作者：Hisaishi_Kanade (赞：0)

### 一、题意

给出 $t$ 个字符串，问最少删几个是的对于 任意奇数 $i$ $\left(1\le i\le n-1\right)$，都有 $a_i=a_{i+1}$。

### 二、思路&正解

看到“最少”这个词我们就应该反应过来：这是贪心题。

怎么贪心呢？如果我们去贪心至少删几个，问题就变得十分复杂。

此时我们就要想到一个词——**正难则反**。

转变思路，不直接求**最少能删几个字符**，转而求**最多能保留几个字符**，不就十分简单了？

那么，怎么求最多保留多少呢？

别的题解已经讲的很清楚了，只要找到某两个字符一样，把中间不一样的全删了，计数器加二，最后输出`s.length()-ans`。

所以需要一个桶来辅助计算。

### 三、代码

有了上面的思路，代码就很简单了，不是吗？

```cpp
#include <iostream>
#include <string.h>
using namespace std;
int t,ans;
int seen[205];//seen是see的过去分词，这里表示“见过”的意思
string s;
int main(){
	ios::sync_with_stdio(false);//这两行都是读入优化，
	cin.tie(0);cout.tie(0);      //不过正式考试不建议使用，这玩意跟freopen对着干
	cin>>t;//这是数据组数
	while(t--){//执行t次
		ans=0;
		memset(seen,0,sizeof seen);//清零
		cin>>s;
		for(int i=0;i<s.length();i++){//字符串下标从0开始
			++seen[s[i]];//似乎前置会快一点
			if(seen[s[i]]==2){
				ans+=2;
				memset(seen,0,sizeof seen);
			}/*
				我见过这个字符两次了，就把它中间全删了
				注意ans存的不是最终答案，而是能保留多少字符。
			 */
		}
		printf("%d\n",s.length()-ans);
	}
	return(0);
}

```

---

## 作者：lanretE (赞：0)

看到这道题我首先想到 dp，然后想了五分钟没想出来，所以我用了贪心。

题目要让所有奇数位和后一位相同，那么可以想到，记当前一位字符为 $c$ ，那么在它后面并离它最近的另一个 $c$ 一定是和它匹配的。所以，我们需要一个数组记录每个字符出现的次数并定义一个 $ans$，初值为字符串长度，如果发现当前字符出现两次，就把 $ans$ 减 $2$。

最后减完的 $ans$ 是永远匹配不上，即需要我们删掉的字符数量，就是我们的答案了。

```cpp
#include<iostream>
#include<cstring>
using namespace std;
string s;
int cnt[30];
int main(){
	int t; cin>>t;
	while(t--){
		cin>>s; int len=s.length();
		int ans=len;
		for(int i=0;i<len;++i){
			++cnt[s[i]-'a'];
			if(cnt[s[i]-'a']==2){
				memset(cnt,0,sizeof cnt);
				ans-=2;
			}
		}
		cout<<ans<<endl;
		memset(cnt,0,sizeof cnt);//一定注意要重置 
	}
	return 0;
}
```


---

## 作者：user470883 (赞：0)

## 思路：
逆向思维贪心题。

这道题当然也可以用动态规划做，然鹅我们都知道，贪心的时间复杂度是明显的比动态规划要更优的，所以我还是选择贪心的算法了。

与其说删掉，其实意思就是说让我们留下了哪些数，再满足条件，逆向思维就体现在这里。

思维只是让你更好想，依靠着贪心思路，不难发现这样一条写代码法则（不会表达呜呜呜）。

* 从前往后扫一遍，如果字母出现两次，立即把夹在中间的删掉

通过观察样例，易得这个规律是正确的。

**注意事项**：

不要忘记清空数组啦！

## AC CODE：
```
#include<bits/stdc++.h>
#define yangzdAKIOI long long
#define INF 2000000000
#define jerrleeAKIOI int
#define CZY signed
#define piggy123AKIOI return 0;
#define mian main
#define mina main
#define fro for
#define ofr for
#define tin int
#define itn int
#define retrun return
#define retunr return
using namespace std;

int a[114];

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	itn t;
	cin >> t;
	while(t--)
	{
		string s;
		cin >> s;
		int ans=s.size();
		for(int i = 0 ; i < s.size();i++)
		{
			a[s[i]-'a']++;
			if(a[s[i]-'a']==2)
			{
				ans-=2;
				memset(a,0,sizeof(a));
			}
		}
		cout << ans << endl;
		memset(a,0,sizeof(a));
	}
	
	return 0;
}

/*Things to check before submit:
1. did you forget long long ?
2. did you still CE?
3. = or == , n or m ,++ or -- , i or j , > or >= , < or <=
4. If contains "not", why not Reverse thinking or few affect?
5. is there anything extra to output?
6. keep it simple
7. can part of the code can with c++function replace?
8. smile while submit the code*/
```
有问题私我，谢谢。

---

## 作者：yuheng_wang080904 (赞：0)

## 题意

$t$ 组数据，每组数据给定一个字符串，问你至少删去几个字母后可以使原字符串变成符合以下要求的字符串：设这个字符串为 $s$，字母个数为偶数 $n$，那么对于任意奇数 $i(1\le i\le n)$，有 $s_i=s_{i+1}$。 

## 思路

**贪心**最容易想到，也是本题最简单的思路。

怎么贪心呢？就是用一个数组 $nl$ 来统计当前字母出现的次数，每当发现有一个字母出现次数为两次时，这个字母就被保留下来，其他统计表里统计到的字母全部都应该删去，然后统计表清空，注意是清空！可以用 $ans$ 记录答案，初始为字符串的长度，每次统计表清空时 $ans-=2$，到最后 $ans$ 就是答案了。

我们来证明以下这种算法的正确性：假如有一个区间里，你没有让那两个字母配对，那么当你继续往下找时，你肯定会让另一个和这个区间内的一个原来是要被删去的字母进行配对，然而你也只能配成一对，不会让可以配成的对数增多，而且你还有可能破坏了后面所要配成的一对，因此反而可能减少对数的个数，因此原方法最优。

## 代码

接下来贴我的代码，很简单的一个贪心的实现。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int main(){
    cin>>t;
    while(t--){
        string s;
        cin>>s;
        int ans=s.size(),nl[30];
        //ans为答案，nl数组用来统计字母个数
        for(int i=0;i<30;i++)nl[i]=0;
        for(int i=0;i<s.size();i++){
            nl[s[i]-'a']++;
            if(nl[s[i]-'a']==2){
                ans-=2;
                for(int i=0;i<30;i++)nl[i]=0;
                //注意此处为清空整张统计表，而非清空这个字母在表里的个数
            }
        }
        cout<<ans<<endl;
    }
}
```


---

