# Game with Reversing

## 题目描述

Alice and Bob are playing a game. They have two strings $ S $ and $ T $ of the same length $ n $ consisting of lowercase latin letters. Players take turns alternately, with Alice going first.

On her turn, Alice chooses an integer $ i $ from $ 1 $ to $ n $ , one of the strings $ S $ or $ T $ , and any lowercase latin letter $ c $ , and replaces the $ i $ -th symbol in the chosen string with the character $ c $ .

On his turn, Bob chooses one of the strings $ S $ or $ T $ , and reverses it. More formally, Bob makes the replacement $ S := \operatorname{rev}(S) $ or $ T := \operatorname{rev}(T) $ , where $ \operatorname{rev}(P) = P_n P_{n-1} \ldots P_1 $ .

The game lasts until the strings $ S $ and $ T $ are equal. As soon as the strings become equal, the game ends instantly.

Define the duration of the game as the total number of moves made by both players during the game. For example, if Alice made $ 2 $ moves in total, and Bob made $ 1 $ move, then the duration of this game is $ 3 $ .

Alice's goal is to minimize the duration of the game, and Bob's goal is to maximize the duration of the game.

What will be the duration of the game, if both players play optimally? It can be shown that the game will end in a finite number of turns.

## 说明/提示

In the first test case, in her turn, Alice can replace the third symbol of the string $ S $ with x. After that, both strings will become equal to "abxde" and the game will end after one move. Since Alice's goal is to finish the game in as few moves as possible, this move will be one of her optimal first moves, and the final answer will be $ 1 $ .

In the second test case, in her turn, Alice can replace the fifth symbol of the string $ T $ with h. After this move, $ S = $ "hello", $ T = $ "olleh". Then Bob makes his turn. In his turn, he must reverse one of the strings. If Bob chooses the string $ S $ , then after his turn both strings will be equal to "olleh", and if he chooses the string $ T $ , then after his turn both strings will be equal to "hello". Thus, after the presented first move of Alice, the game will definitely end in $ 2 $ moves. It can be shown that there is no strategy for Alice to finish the game in less than $ 2 $ moves, with both players playing optimally. The final answer is $ 2 $ .

In the third test case, in her first move, Alice can replace the second symbol of the string $ S $ with c. After this move, $ S = $ "ac", $ T = $ "cd". Then Bob makes his turn. If Bob reverses the string $ S $ , then after his turn $ S = $ "ca", $ T = $ "cd". Then it is easy to see that in this case Alice can definitely finish the game on the $ 3 $ -rd move, by replacing the second symbol of the string $ T $ with a, after which both strings will become equal to "ca". If Bob reverses the string $ T $ , then after his turn $ S = $ "ac", $ T = $ "dc". In this case, Alice can also definitely finish the game on the $ 3 $ rd move, by replacing the first symbol of the string $ S $ with d, after which both strings will become equal to "dc". Thus, Alice can definitely finish the game in $ 3 $ moves regardless of Bob's moves. It can be shown that the game cannot end in less than $ 3 $ moves, with both players playing optimally.

In the fifth test case, the strings $ S $ and $ T $ are equal, so the game will end without starting, in $ 0 $ moves.

## 样例 #1

### 输入

```
7
5
abcde
abxde
5
hello
olleo
2
ab
cd
7
aaaaaaa
abbbbba
1
q
q
6
yoyoyo
oyoyoy
8
abcdefgh
hguedfbh```

### 输出

```
1
2
3
9
0
2
6```

# 题解

## 作者：无钩七不改名 (赞：3)

我们只需要盯着一个字符串改变就好了，改到与另一个字符串或者另一个字符串翻转后的串一样。所需次数便是这两种对应方式的最小操作次数的最小值。约等于对应的不一样的位数的两倍，但是需要处理一些细节。比如最后一下是否不用翻转。

很容易发现，当翻转次数为偶数时候，可以当做没翻处理。

结合代码应该很容易理解。

```cpp
#include<bits/stdc++.h>
using namespace std;

int t,n;
char a[100005],b[100005];
int ans1,ans2;

int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d %s %s",&n,a,b);
		ans1=0;ans2=0;
		for(int i(0);i<n;i++){
			if(a[i]!=b[i])ans1++;
			if(a[i]!=b[n-1-i])ans2++;
		}
		if(ans1<=1){
			printf("%d\n",ans1);
			continue;
		}
		if(ans2<=1){
			printf("%d\n",2);
			continue;
		}
		int x=(1<<30);
		if(ans1%2)x=min(x,ans1*2-1);
		else x=min(x,ans1*2);
		if(ans2%2)x=min(x,ans2*2);
		else x=min(x,ans2*2-1);
		printf("%d\n",x);
	}
	return 0;
} 
```


---

## 作者：Lagerent (赞：2)

考虑到小 S 的操作除了使得操作次数增加之外，她的策略（即选 $S$ 或 $T$ 进行翻转）对于整场游戏的结果并没有影响。在 $S$ 上翻转一次和在 $T$ 上翻转一次实际上使得两个字符串的对应位置是一样的。

考虑小 L 的策略一定是把其中的一个串中和另一个串不一样的字符变得一样。那么我们可以考虑正着对应和反着对应。即 $S_i = T_i$ 或 $S_i = T_{n - i + 1}$。

我们扫一遍整个串，把正着对应不一样的字符数量和反着对应不一样的字符数量记录一下，然后再想明白操作奇偶性所对应串的状态就可以了。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define rep(a, b, c) for(int (a) = (b); (a) <= (c); ++ (a))
#define per(a, b, c) for(int (a) = (b); (a) >= (c); -- (a))
using namespace std;
 
const int N = 100010;
char str1[N], str2[N];
 
void solve() {
	int n;
	scanf("%d", &n);
	scanf("%s%s", str1 + 1, str2 + 1);
	int tot1 = 0, tot2 = 0;
	rep(i, 1, n) {
		if(str1[i] != str2[i]) ++ tot1;
		if(str1[i] != str2[n - i + 1]) ++ tot2;
	}
	if(tot1 == 0) {
		puts("0"); return;
	}
	else if(tot2 == 0) {
		puts("2"); return;
	}
	int ans = 1e8;
	if(tot1 % 2 == 0) ans = min(ans, tot1 * 2);
	else ans = min(ans, tot1 * 2 - 1);
	if(tot2 % 2 == 0) ans = min(ans, tot2 * 2 - 1);
	else ans = min(ans, tot2 * 2);
	printf("%d\n", ans);
}
 
int main() {
	int T;
	scanf("%d", &T);
	while(T -- ) solve();
	return 0;
}
```

---

## 作者：c1ampy (赞：2)

假设 Bob 翻转的字符串为 $ S $，那么 $ S $ 的各字符相对于 $ T $ 的各字符都发生了相对位置的变动；而如果 Bob 翻转的字符串为 $ T $，那么 $ S $ 的各字符相对于 $ T $ 的各字符发生的相对位置的变动，与翻转字符串 $ S $ 是相同的。故在此意义上，我们可以认为 Bob 每次均翻转同一个字符串。

显然，将一个字符串翻转偶数次，相当于没有翻转；将一个字符串翻转奇数次，相当于只翻转了一次。

设 $ S $ 与 $ T $ 之间有 $ d $ 对字符不同，$ S $ 与 $ \operatorname{rev}(T) $ 之间有 $ d^\prime $ 对字符不同。在我们将问题进行以上等效转化后，两人的操作可以简化为以下两种情况：

- Alice 修改了 $ S $ 中的 $ d $ 个字符，使得 $ S^\prime = T $，而 Bob 对 $ T $ 进行了偶数次翻转，游戏结束。
- Alice 修改了 $ S $ 中的 $ d^\prime $ 个字符，使得 $ S^\prime = \operatorname{rev}(T) $，而 Bob 对 $ T $ 进行了奇数次翻转，游戏结束。

根据 Alice 为先手的信息与 $ d $（或 $ d^\prime $）的奇偶性，不难分类讨论出 Bob 的操作次数，进而得到游戏轮数。

将以上两种情况的轮数比较即可得到答案。

注：别忘了特判 $ S = T $ 与 $ S = \operatorname{rev}(T) $ 的情况。

```cpp
#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);

    int T;
    cin >> T;
    while (T--) {
        int n;
        string S, T, T_reversed;
        cin >> n >> S >> T;
        T_reversed = string(T.rbegin(), T.rend());

        if (S == T) {
            cout << "0\n";
            continue;
        }
        if (S == T_reversed) {
            cout << "2\n";
            continue;
        }

        int ans_T = 0;
        for (int i = 0; i < n; ++i) {
            ans_T += S[i] != T[i];
        }
        int ans_T_reversed = 0;
        for (int i = 0; i < n; ++i) {
            ans_T_reversed += S[i] != T_reversed[i];
        }
        ans_T = ans_T & 1 ? (ans_T << 1) - 1 : ans_T << 1;
        ans_T_reversed = ans_T_reversed & 1 ? ans_T_reversed << 1 : (ans_T_reversed << 1) - 1;
        cout << min(ans_T, ans_T_reversed) << '\n';
    }

    return 0;
}
```

---

## 作者：huangrenheluogu (赞：1)

## Preface

打比赛的时候打完 B 感觉没了，但是这个 C 还是比较水的。

## Solution

**声明：下文中 Alice 指的都是中文翻译的 小 L，下文中 Bob 指的是中文翻译中的 小 S。**

发现 Alice 的游戏是主动的，可以选择改（改成一样的）或者不改，而 Bob 在 Alice 不改的时候被迫翻转，就会导致一样的局面。

所以，我认为，Bob 是不会改变序列的本质的。如果改变了，我们等他翻过来就可以了。即 Alice 主动，Bob 被动。而 Alice 要做的，就是尽快做完。

考虑正态和出态，枚举正序和反序，看哪个更优，就是本题的大致思路。

我们已经知道了 Bob 要更改多少次，我用 $ans1$ 表示在正序的情况下，用 $ans2$ 表示在反序的情况下。下面附上 $ans1,ans2$ 统计方式。

```cpp
for(int i = 0; i < n; i++){
   ans1 += (s1[i] != s2[i]);
   ans2 += (s1[i] != s2[n - i - 1]);
}
```

- 处理 $ans1$。

如果 Alice 要更改奇数次，那么在 Bob 不翻转之前就已经好了，所以就是 $ans1\times2-1$。

而如果是偶数次，则 Alice 要等 Bob 做完才结束，所以就是 $ans1\times2$。

- 处理 $ans2$。

同理。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int T, n, ans1, ans2;
string s1, s2;
inline void read(int &res){
	char ch=getchar();int f=1;res=0;
	while('0'>ch||ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while('0'<=ch&&ch<='9'){
		res=(res<<1)+(res<<3)+(ch^48);
		ch=getchar();
	}
	res*=f;
}
signed main(){
	read(T);
	while(T--){
		read(n);
		ans1 = ans2 = 0;
		cin >> s1 >> s2;
		for(int i = 0; i < n; i++){
			ans1 += (s1[i] != s2[i]);
			ans2 += (s1[i] != s2[n - i - 1]);
		}
		if(ans1 & 1) ans1 = ans1 * 2 - 1;
		else ans1 = ans1 * 2; 
		if(ans2 & 1) ans2 = ans2 * 2;
		else ans2 = ans2 * 2 - 1;
		ans2 = max(ans2, 2);
		printf("%d\n", min(ans1, ans2));
	}
	return 0;
}
```

---

## 作者：BugGod (赞：0)

首先来看翻转操作，显然的，翻转偶数次等同于没翻转。而小 L 的操作有两种选择：变为没有翻转的或者变为翻转一次的。我们可以分类讨论，取较小值。

CODE：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int Quantico_tql,n,a1,a2,ans;
string s,t;
void solve()
{
    cin>>n>>s>>t;
    a1=a2=0;ans=9e18;
    for(int i=0;i<s.size();i++)
    {
        a1+=(s[i]!=t[i]);//变为未翻转的
        a2+=(s[i]!=t[n-i-1]);//变为翻转一次的
    }
    if(!a1){cout<<"0\n";return ;}//完全一样
    if(!a2){cout<<"2\n";return ;}//小 L 等待小 S 翻转一次
    if(a1%2^1)ans=a1<<1;
    else ans=(a1<<1)-1;
    if(a2%2^1)ans=min(ans,(a2<<1)-1);
    else ans=min(ans,a2<<1);
    cout<<ans<<'\n';
}
signed main()
{
    cin>>Quantico_tql;
    while(Quantico_tql--)solve();
    return 0;
}
```

---

## 作者：_sunkuangzheng_ (赞：0)

**【分析】**

发现翻字符串两次不会对答案造成影响，因此统计出初始状态下翻与不翻的不同位数，并结合奇偶性，判断结束状态时的情况。注意最后的细节处理。

特别提醒：特判不同位数是 $0$ 的情况！

**【代码】**

```cpp
#include <bits/stdc++.h>
using namespace std;
int t,n;
string a,b;
int main(){
	cin >> t;
	while(t --){
		cin >> n >> a >> b;
		if(a == b){cout << 0 << endl;continue;}
		int ans1 = 0,ans2 = 0;
		for(int i = 0;i < n;i ++) ans1 += (a[i] != b[i]),ans2 += (a[i] != b[n-i-1]);
		if(ans2 == 0) ans2 ++;
		if(ans1 < ans2) cout << 2 * ans1 - (ans1 % 2 == 1) << endl;
		else if(ans1 > ans2) cout << 2 * ans2 - (ans2 % 2 == 0) << endl;
		else cout << ans1 * 2 - 1 << endl;
	}
	return 0;
}
```

---

