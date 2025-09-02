# [ARC170A] Yet Another AB Problem

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc170/tasks/arc170_a

`A`, `B` からなる長さ $ N $ の文字列 $ S,T $ が与えられます．$ S $ の左から $ i $ 番目の文字を $ S_i $ と表します．

あなたは以下の操作を好きな回数（$ 0 $ 回でもよい）繰り返すことができます．

- $ 1\leq\ i\ <\ j\ \leq\ N $ を満たす整数 $ i,j $ を選ぶ． $ S_i $ を `A` で， $ S_j $ を `B` で置き換える．
 
$ S $ を $ T $ に一致させることが可能か判定し，可能な場合必要な最小の操作回数を求めてください．

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ S,T $ は `A`, `B` からなる長さ $ N $ の文字列
- 入力される数値は全て整数
 
### Sample Explanation 1

$ i=1,j=3 $ として操作を行うと $ S $ は `AABBA` に変化します． 次に，$ i=4,j=5 $ として操作を行うと $ S $ は `AABAB` に変化します． よって $ 2 $ 回の操作で $ S $ を $ T $ と一致させることが可能です．また，これが必要な最小の操作回数であることが証明できるので答えは $ 2 $ です．

### Sample Explanation 2

何回操作を行っても $ S $ を $ T $ と一致させることは不可能であることが証明できます．

## 样例 #1

### 输入

```
5
BAABA
AABAB```

### 输出

```
2```

## 样例 #2

### 输入

```
2
AB
BA```

### 输出

```
-1```

# 题解

## 作者：bs_commander (赞：4)

题目的大概意思就是，可以将任意的两个字符换为 `AB`，要将 $S$ 字符串变为 $T$ 字符串。

### 第一步：最优情况

当 $S$ 和 $T$ 不对应，最优的情况当然是把 $S$ 里的 `BA` 换为 `AB`。但并不是每个不对应的 `B` 都能找到 `A`。所以要用一个类似队列的数组，一一对应。
```cpp
for(int i=1;i<=n;i++){
	if(s[i]!=t[i]&&s[i]=='B'){
		ch[++zz]=i;//记录不对应的B
		flag[i]=1;
	}else if(s[i]!=t[i]){
		if(zz-z>=1){
			++z;
			flag[ch[z]]=0;
			s[ch[z]]='A';//改变两个对应的字符
			s[i]='B';
		}
	}
}
cnt=z;//总的次数即为现在改变的次数
```
### 第二步：只变一个
容易发现，不只是 `BA` 可以变为 `AB`，`AA` 和 `BB` 也可以变为 `AB`。所以再次遍历，对于多出来的 `A`，可以在它的前面找一个 `A`，变为 `AB`。同样的，对于 `B`，我们只需要倒序遍历，也可以变为 `AB`。

注意，如果在一个不对应的字符的前面或后面找不到一个一样的，就代表不能变换，直接退出。
```cpp
for(int i=1;i<=n;i++){
	if(s[i]=='A'&&t[i]==s[i])f2++;
	else if(f2==0&&s[i]=='A'&&t[i]!=s[i]){
		printf("-1");//前面没有A
		return 0;
	}else if(s[i]=='A'&&t[i]!=s[i]){
		cnt++;//次数多一
		s[i]='B';//修改
	}
}
f2=0;
for(int i=n;i>=1;i--){
	if(s[i]=='B'&&t[i]==s[i])f2++;
	else if(f2==0&&s[i]=='B'&&t[i]!=s[i]){
		printf("-1");
		return 0;
	}else if(s[i]=='B'&&t[i]!=s[i]){
		cnt++;
		s[i]='A';
	}
}

---

## 作者：Register_int (赞：3)

先来判无解。如果一个位置要改成 $\verb!A!$，那么只要在它右边有一个位置满足 $T_i=\verb!B!$，就一定能改动，反之无解。改成 $\verb!B!$ 同理。

最坏情况下，我们每个位置都需要耗费一次操作，答案为 $\sum[S_i\not=T_i]$。考虑什么情况下能少掉一次操作：若存在两个位置 $i<j$ 满足分别要改成 $\verb!A!,\verb!B!$，即可省掉一次，把这两个一起处理了。从左往右扫一遍贪心匹配掉即可，时间复杂度 $O(n)$。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 2e5 + 10;

int n, ans; char s[MAXN], t[MAXN];

int main() {
	scanf("%d%s%s", &n, s + 1, t + 1);
	for (int i = 1; i <= n; i++) {
		if (t[i] == 'A') break;
		if (s[i] == 'A') return puts("-1"), 0;
	}
	for (int i = n; i; i--) {
		if (t[i] == 'B') break;
		if (s[i] == 'B') return puts("-1"), 0;
	}
	for (int i = 1; i <= n; i++) ans += s[i] != t[i];
	for (int i = 1, j = 0; i <= n; i++) {
		if (s[i] == t[i]) continue;
		if (t[i] == 'A') j++;
		if (t[i] == 'B' && j) j--, ans--;
	}
	printf("%d", ans);
}
```

---

## 作者：Lame_Joke (赞：3)

**终于在 ARC 中 AC 一题了……好激动！**

- ### 题目大意

  题目给出两个只包含 `A` 和 `B` 的字符串 $S,T$（`AB` 串？），每次操作将 $S$ 中两个不同位置的字符分别改成 `A` 和 `B`（`A` 在前，`B` 在后）。求经过若干次这样的操作能否使 $S=T$，若可以，输出最小操作次数，否则，输出 `-1`。

- ### 思路&解法

  不难发现，对于一个要需要改成 `B` 的 `A`，只要它前面有 `A` 那么它就一定能在不影响其它位数的情况下修改成 `B`。当然，由于我们要求的是最小操作次数，所以我们最优情况当然是需要改成 `A` 的 `B` 与需要改成 `B` 的 `A` 匹配，我们可以想到用栈来存之前出现的需要改成 `A` 的 `B` 的位置。为了方便说明，这里设需要改成 `A` 的 `B` 为 $A'$，需要改成 `B` 的 `A` 为 $B'$。当我们遇到 $A'$，入栈，遇到 $B'$ 时判断栈里有没有 $A'$，若有，那么说明它们可以匹配，$ans+1$，弹栈。若没有，判断前面有没有出现过 `A`，若出现过则直接 $ans+1$。否则输出 `-1`。最后我们要判断一下栈是否空了，若没空，判断栈顶的 $A'$ 后面有没有 `B`（包括已经被修改了的 $B'$）若有则 $ans$ 要加上栈内 $A'$ 的数量，若没有则输出 `-1`。

- ###  参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
char s[200005],t[200005];
int n,sum[200005],s1[200005],cnt;
int main()
{
	scanf("%d",&n);
	scanf("%s%s",&s,&t);
	int ans=0;
	if(t[0]=='B'&&s[0]=='A')
	{
		printf("-1");
		return 0;
	}		

	if(t[n-1]=='A'&&s[n-1]=='B')
	{
		printf("-1");
		return 0;
	}
	int s3=0,s2=0;
	for(int i=1;i<n;i++)
	{
		sum[i]=sum[i-1];
		if(s[i-1]=='A') sum[i]++;
	}
	for(int i=0;i<n;++i)
	{
		if(s[i]==t[i]) continue;
		if(s[i]=='B') s1[++cnt]=i;
		else if(s[i]=='A')
		{
			
			if(cnt!=0)
			{
				cnt--;
				ans++;
			}
			else if(sum[i]>0) ans++;
			else
			{
				printf("-1");
				return 0;
			}
			s[i]='B';
		}
	}
	
	if(cnt!=0)
	{
		for(int i=s1[cnt]+1;i<n;i++)
		{
			if(s[i]=='B')
			{
				s2=1;
				break;
			}
		}
		if(s2==0)
		{
			printf("-1");
			return 0;
		}
	}
	printf("%d",ans+cnt);
}
```

  

[AC 记录](https://atcoder.jp/contests/arc170/submissions/49557095)

---

## 作者：fcy20180201 (赞：1)

## 题意
给定只包含 `A` 和 `B` 的字符串 $S,T$，每次操作将 $S$ 中两个不同位置的字符前面的改成 `A` 后面的改成 `B`。请问经过多少次操作才能将 $S$ 变成 $T$（如果不行，输出 `-1`）。

## 思路
将 $S$ 变成 $T$，就是将 $S$ 中与 $T$ 字符不同的位置上的字符变为相同的。我们将 $S$ 为 `B` 而 $T$ 为 `A` 的位置称为“A 类位置”，将 $S$ 为 `A` 而 $T$ 为 `B` 的位置称为“B 类位置”。

显然要使用最少的操作，就要一次修改尽量修改一个“A 类位置”和一个“B 类位置”。所以我们反复找到一个“A 类位置”，其后面有一个“B 类位置”，将这两个位置修改作为一次操作，直到找不到这样一对位置为止。

这时剩下的“B 类位置”一定在所有“A 类位置”前面，所以只能一个一个解决了。对于所有“B 类位置”，都找到左边的一个**本来就为 `A` 的位置**作为操作里前面的位置；对于所有“A 类位置”，都找到右边的一个**本来就为 `B` 的位置**作为操作里后面的位置。（如果找不到这样的位置就无法将 $S$ 变成 $T$）

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,cnt2,ans;
bool flag1,flag2;
stack<int>cnt;
char s[200005],t[200005];
int main(){
	scanf("%d%s%s",&n,s+1,t+1);
	for(int i=1;i<=n;i++){//“A、B 类位置”配对
		if(s[i]=='B' && t[i]=='A')cnt.push(i);
		if(s[i]=='A' && t[i]=='B' && !cnt.empty())ans++,s[cnt.top()]='A',s[i]='B',cnt.pop();
	}
	for(int i=1;i<=n;i++){
		if(s[i]=='A' && t[i]=='A')flag1=true;//找到一个本来就为 A 的位置
		if(s[i]=='A' && t[i]=='B'){
			if(!flag1){printf("-1");return 0;}
			//如果“B 类位置”前没有本来就为 A 的位置，输出 -1
			ans++;
		}
		if(s[i]=='B' && t[i]=='A')flag2=true,ans++;//有“A 类位置”
		if(s[i]=='B' && t[i]=='B')flag2=false;//解决前面的“A 类位置”
	}
	printf("%d",(flag2?-1:ans));
	//如果还有没解决的“A 类位置”, 输出 -1；否则输出答案
	return 0;
}

```

---

## 作者：mgcjade (赞：1)

谨以此片题解纪念我在 ARC 比赛中通过的第一题。

# [AT_arc170_a](https://luogu.com.cn/problem/AT_arc170_a) 的题解

## 题目大意

给出两个字符串 `S` 和 `T` 以及它们的长度，同时存在一种操作：

- 将 $s_i$ 变为 `A` 并将 $s_j$ 变为 `B`，此处 $1 \leq i<j \leq n$。

让你求出在最少多少次后，字符串 `S` 能等于字符串 `T`，如果不能达到目标，就输出 `-1`。

## 思考过程

一看到题，就感觉是贪心，于是打了一个贪心，然后挂了。

于是把样例抄到草稿纸上，寻找规律（自我以为是图论，因为上一场第一题就是图论），~~什么都没有发现~~，发现好像就是单纯的字符串，结果就发现：

- 对于一个 $a_i$ 或 $a_j$，如果它需要进行操作，而没有人可以跟他进行操作，那么此情况无解。
  
- 对于一个 $a_j$，如果它前面由一个需要进行操作的 $a_i$，那么两个数匹配，否则这个数个前面的某个已经匹配好的数匹配。
  
- 对于一个 $a_i$，如果它后面由一个需要进行操作的 $a_j$，那么两个数匹配，否则这个数个后面的某个已经匹配好的数匹配。
  

## 正解

前后遍历一遍，求出所需的最小 `ans`，取较小值。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;

int len;
char s[N], t[N];
queue<int>q;
bool flag;
int ansa, ansb;

int main()
{
    scanf("%d", &len);
    scanf("%s", s + 1);
    scanf("%s", t + 1);

    for (int i = 1; i <= len; i++)
        if (s[i] == 'B' && t[i] == 'A')
            q.push(i), flag = 1;
        else if (s[i] == 'A' && t[i] == 'A')
            flag = 1;
        else if (s[i] == 'A' && t[i] == 'B')
        {
            if (q.size() == 0)
            {
                if (!flag)
                {
                    printf("-1");
                    return 0;
                }
            }
            else
            {
                q.pop();
            }

            ansa++;
        }

    flag = 0;
    ansa += q.size();

    while (!q.empty())
        q.pop();

    for (int i = len; i; i--)
        if (s[i] == 'A' && t[i] == 'B')
            q.push(i), flag = 1;
        else if (s[i] == 'B' && t[i] == 'B')
            flag = 1;
        else if (s[i] == 'B' && t[i] == 'A')
        {
            if (q.size() == 0)
            {
                if (!flag)
                {
                    printf("-1");
                    return 0;
                }
            }
            else
            {
                q.pop();
            }

            ansb++;
        }

    ansb += q.size();

    printf("%d", min(ansa, ansb));
    return 0;
}
```

---

## 作者：wuzijinmlily (赞：0)

ARC 果然不好打，差点没分……

# 题意

给你两个长度为 $N$ 的字符串 $S$ 和 $T$，可将任意的两个字符变为 `A` 和 `B`，使 $S$ 变成 $T$，要求找出最小操作数，如果存在就输出，不存在就输出 `-1`。

# 思路

首先，我们可以先枚举一遍，先判断 $T_i$ 是否为 `A`，如果为真，直接 break，接着判断是否存在 $S_i$ $=$ `A` 且 $T_i$ $=$ `B` 的情况，如果存在，说明字符 $T_1$ 至 $T_i$ 中不存在 `A`，则 $S$ 无法变成 $T$，直接输出 `-1`。接着，倒过来枚举一遍，与上面同理，最后再枚举一遍，更新 $ans$ 和 $cnt$，输出 $ans+cnt$ 即可。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
char s[200001],t[200001];
int main()
{
	scanf("%d",&n);
	cin>>s>>t;
	for(int i=0;i<n;i++)
	{
		if(t[i]=='A')
		{
			break;
		}
		if(s[i]=='A'&&t[i]=='B')
		{
			printf("-1");
			return 0;
		} 
	}
	for(int i=n-1;i>=0;i--)
	{
		if(t[i]=='B')
		{
			break;
		}
		if(s[i]=='B'&&t[i]=='A')
		{
			printf("-1");
			return 0;
		}
	}
	int cnt=0,ans=0;
	for(int i=0;i<n;i++)
	{
		if(s[i]=='A'&&t[i]=='B')
		{
			ans++;
			cnt=max(0,cnt-1);
		}
		if(s[i]=='B'&&t[i]=='A')
		{
			cnt++;
		}
	}
	printf("%d",ans+cnt);
	return 0;
}
```
谢谢反馈，忘记修改了。


---

## 作者：Cure_Wing (赞：0)

[AT_arc170_a [ARC170A] Yet Another AB Problem](https://www.luogu.com.cn/problem/AT_arc170_a)

### 思路

你发现每次操作 $S$ 中的 $B$ 都不会换到左边去，$A$ 也不会换到右边去，所以如果 $T$ 的开头存在一连串的 $B$ 而 $S$ 对应的是一连串的 $A$ 或者 $T$ 的末尾存在一连串的 $A$ 而 $S$ 对应的是一连串的 $B$，那么肯定就是无解。所以在一开始先把左右两段判掉，直接考虑中间的部分。

一种比较好想的交换方式是选择左边 $S_i=B,T_i=A$，右边 $S_j=A,T_j=B$ 然后对 $(i,j)$ 进行操作。然后由于不合法的情况已经不存在了，所以对于多出来的 $S_i=B,T_i=A$，我们一定能在右边找到一个 $j$ 满足 $S_j=T_j=B$。因为这个 $j$ 要么本身存在，要么在一开始 $S_j=A$，而我们会用这段话开头的方式使 $S_j$ 变成 $B$。所以对于多出来的 $S_i=A,T_i=B$，我们也一定能在左边找到一个 $j$ 满足 $S_j=T_j=A$。于是我们就像括号匹配那样暴力匹配，多出来的直接记到答案里即可。

时间复杂度 $O(n)$。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using std::cin;using std::cout;
int n,cnt,ans;
bool flag;
std::string s,t;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
	cin>>n>>s>>t;int l=-1,r=n;
	for(;l<n-1&&t[l+1]=='B';++l)//特判无解
		if(s[l+1]!='B'){cout<<-1;return 0;}
	for(;r>0&&t[r-1]=='A';--r)
		if(s[r-1]!='A'){cout<<-1;return 0;}
	for(int i=l+1;i<r;++i){
		if(s[i]=='B'&&t[i]=='A') ++cnt;//不能匹配单独记录
		if(s[i]=='A'&&t[i]=='B'){--cnt;++ans;}//能匹配就匹配，不能匹配也得上
		cnt=std::max(cnt,0);
	}
	cout<<ans+cnt;//多出来无法匹配直接计入
	return 0;
}
```

---

## 作者：Expert_Dream (赞：0)

我们发现，对于 $i$ 和 $j$ 有三种改变的方式。

- 原 $s_i$ 是 ```B```，$s_j$ 是 ```A```。并且 $t_i$ 是 ```A```，$t_j$ 是 ```B```。如果此时进行了一次改变，必然是同时改变**两**个字符。

- 原 $s_i$ 是 ```A```，$s_j$ 是 ```A```。并且 $t_i$ 是 ```A```，$t_j$ 是 ```B```。如果此时进行了一次改变，必然是同时改变**一**个字符。

- 原 $s_i$ 是 ```B```，$s_j$ 是 ```B```。并且 $t_i$ 是 ```A```，$t_j$ 是 ```B```。如果此时进行了一次改变，必然是同时改变**一**个字符。

显然，第一种是最划算的，所以我们先处理第一种方式，由于需要线性，所以我们可以使用栈的结构来存储，然后对其处理。

然后处理完第一种方式，我们再处理第二第三种方式。

例如第二种，我们只需要找到最早出现的 ```A```。然后改变后面的字符。

第三种也是同理。

[link](https://atcoder.jp/contests/arc170/submissions/49544374)。

---

## 作者：Xiphi (赞：0)

虾头贪心题。可能是我写麻烦了。考虑开 $4$ 个 set：
- $\rm sa$ 记录**没必要**换的 `A` 的下标
- $\rm sb$ 记录**没必要**换的 `B` 的下标
- $\rm sba$ 记录**必须要**换成 `A` 的下标
- $\rm sbb$ 记录**必须要**换成 `B` 的下标

然后对于每种去贪心，先在扫描的过程中，把有前后关系且**距离最近**的两个**必须要**换的下标换掉。可以证明这样是最优的，自证不难。

扫完一遍后，再处理 $\rm sba$ 和 $\rm sab$ 两个东西，首先不难发现两者之间无法互相消除，那就在 $\rm sa$ 或是 $\rm sb$ 中找到可以配套消除的即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
string s,t;
int n;
int main(){
//	freopen("test.in","r",stdin);
//	freopen("test.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
	cin>>n>>s>>t;
	s=" "+s;
	t=" "+t;
	int flag=0,flag1=0,flag2=0;
	int cnt=0;
	set<int> sba,sbb,sa,sb;
	sbb.insert(n+1);
	sbb.insert(0);
	sba.insert(n+1);
	sba.insert(0);
	sa.insert(n+1);
	sa.insert(0);
	sb.insert(n+1);
	sb.insert(0);
	for(int i=1;i<=n;++i){
		if(s[i]=='A')sa.insert(i);
		else sb.insert(i);
		if(s[i]!=t[i]){
			if(s[i]=='B') sba.insert(i);
			else{
				sbb.insert(i);
				if(sba.size()>0){
					auto it1=sba.lower_bound(i);
					if(*it1==0) {
						continue;
					}
					--it1;
					if(*it1==0) {
						continue;
					}
					sba.erase(it1);
					sbb.erase(i);
					cnt++;
				}
			}
		}
	}
	sbb.erase(0);
	sbb.erase(n+1);
	for(auto it=sbb.begin();it!=sbb.end();++it){
		auto it1=sa.lower_bound(*it);
		if(*it1==0||*it1==n+1) {
			cout<<-1;exit(0);
		}
		--it1;
		if(*it1==0) {
			cout<<-1;exit(0);
		}
		sa.erase(it1);
		cnt++;
	}
	sba.erase(0);
	sba.erase(n+1);
	for(auto it=sba.begin();it!=sba.end();++it){
		auto it1=sb.upper_bound(*it);
		if(*it1==n+1){
			cout<<-1,exit(0);
		}
		sb.erase(it1);
		cnt++;
	}
	cout<<cnt<<'\n';
	return 0;
}




```

---

