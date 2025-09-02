# Treasure Hunt

## 题目描述

After the big birthday party, Katie still wanted Shiro to have some more fun. Later, she came up with a game called treasure hunt. Of course, she invited her best friends Kuro and Shiro to play with her.

The three friends are very smart so they passed all the challenges very quickly and finally reached the destination. But the treasure can only belong to one cat so they started to think of something which can determine who is worthy of the treasure. Instantly, Kuro came up with some ribbons.

A random colorful ribbon is given to each of the cats. Each color of the ribbon can be represented as an uppercase or lowercase Latin letter. Let's call a consecutive subsequence of colors that appears in the ribbon a subribbon. The beauty of a ribbon is defined as the maximum number of times one of its subribbon appears in the ribbon. The more the subribbon appears, the more beautiful is the ribbon. For example, the ribbon aaaaaaa has the beauty of $ 7 $ because its subribbon a appears $ 7 $ times, and the ribbon abcdabc has the beauty of $ 2 $ because its subribbon abc appears twice.

The rules are simple. The game will have $ n $ turns. Every turn, each of the cats must change strictly one color (at one position) in his/her ribbon to an arbitrary color which is different from the unchanged one. For example, a ribbon aaab can be changed into acab in one turn. The one having the most beautiful ribbon after $ n $ turns wins the treasure.

Could you find out who is going to be the winner if they all play optimally?

## 说明/提示

In the first example, after $ 3 $ turns, Kuro can change his ribbon into ooooo, which has the beauty of $ 5 $ , while reaching such beauty for Shiro and Katie is impossible (both Shiro and Katie can reach the beauty of at most $ 4 $ , for example by changing Shiro's ribbon into SSiSS and changing Katie's ribbon into Kaaaa). Therefore, the winner is Kuro.

In the fourth example, since the length of each of the string is $ 9 $ and the number of turn is $ 15 $ , everyone can change their ribbons in some way to reach the maximal beauty of $ 9 $ by changing their strings into zzzzzzzzz after 9 turns, and repeatedly change their strings into azzzzzzzz and then into zzzzzzzzz thrice. Therefore, the game ends in a draw.

## 样例 #1

### 输入

```
3
Kuroo
Shiro
Katie
```

### 输出

```
Kuro
```

## 样例 #2

### 输入

```
7
treasurehunt
threefriends
hiCodeforces
```

### 输出

```
Shiro
```

## 样例 #3

### 输入

```
1
abcabc
cbabac
ababca
```

### 输出

```
Katie
```

## 样例 #4

### 输入

```
15
foPaErcvJ
mZaxowpbt
mkuOlaHRE
```

### 输出

```
Draw
```

# 题解

## 作者：俺是小程 (赞：1)

## 先来看看官方题解的节选  :(自己翻的,不好请多多谅解)   
 - 容易发现最优答案一定是长度为1的子串。 因此，为了使字符串尽可能美丽，我们将选择字符串中最多出现的**字母**，并尽可能的用选定的字母替换所有其他字母。

 #### 下面是几种情况。      

1. 如果n小于或等于剩余字母的数量，只需将选定字母的数量加上n即为得分。

2. 如果用所选字母替换所有字母后,还剩下的替换次数 n 是偶数，我们可以选择一个任意字母，用其他字母代替，换回来,并重复该动作，直到n到0为止。

3. 否则，我们不会替换所有其他字母。 相反，我们将替换这些字母，直到剩下1个字母（现在n是偶数），然后用另一个与我们选择的字母不同的字母替换该字母。 之后，用我们选择的字母替换那封信。

4. 现在n又成了偶数，我们重复上面讨论的动作。

我觉得讲得挺清楚了.如果存在疑问,可以看看下面几组样例.   
- aaaaa -> aaaab -> aaaac -> aaaaa (n = 3)   
- aaa -> aab -> aaa (n = 2)

所以可以发现,当且仅当一个字符串全是某个字母,且 n = 1 时才需要考虑"换不回来"的情况,此时的答案变成字符串长度 - 1  
最后的最后,注意字母有小写和大写.~~我打比赛的时候没注意结果没A qwq~~   
```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
typedef pair<int, int> P;
const int MAXN = 1e9 + 20;

int N;
string s1, s2, s3;

int solve(string s)
{
	int m['z' - 'A' + 1] = {0};
	for(int i = 0; i < (int) s.size(); i++)
		m[s[i] - 'A']++;
	
	P ans(0, 0);
	for(int i = 0; i < ('z' - 'A' + 1); i++)
		if(m[i] > ans.first) 
			ans.first = m[i], ans.second = i;

	if(N <= (int)s.length() - ans.first) return ans.first + N;
	else 
	{
		if((ans.first == (int) s.length()) && N == 1) return s.length() - 1;
		else return s.length();
	}
}

int main()
{
	cin>>N;
	cin>>s1>>s2>>s3;

	int a, b, c;
	a = solve(s1),
	b = solve(s2),
	c = solve(s3);
	//cout<<a<<" "<<b<<" "<<c<<endl;

	if((a > b) && (a > c)) puts("Kuro");
	else if((b > a) && (b > c)) puts("Shiro");
	else if((c > a) && (c > b)) puts("Katie");
	else puts("Draw");
	return 0;
}

```

---

## 作者：Leaper_lyc (赞：0)

易证最优答案一定是长度为 $1$ 的子串。

对此我们可以找到每个字符串中出现次数最多的长度为 $1$ 的子串，将它作为“标准”，其他位置的字符能改就改，最后能有多少个“标准”，答案就是多少。

那如何求出出现次数最多的那个字符的出现次数呢？

开个桶维护不就好了。

代码：
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

#define maxn 100005

char a[maxn], b[maxn], c[maxn];

int t1[maxn], t2[maxn], t3[maxn];
// 三个字符串，三个桶
int cnta, cntb, cntc, ansa, ansb, ansc;

signed main() {
    int n, len;
    cin >> n;
    cin >> (a + 1) >> (b + 1) >> (c + 1);
    len = strlen(a + 1);
    for (int i = 1; i <= len; i++) {
        t1[a[i]]++;
        t2[b[i]]++;
        t3[c[i]]++;
        cnta = max(cnta, t1[a[i]]);
        cntb = max(cntb, t2[b[i]]);
        cntc = max(cntc, t3[c[i]]);
    }
    if (cnta + n <= len) ansa = cnta + n;
    else {
        if (n == 1 && cnta == len) ansa = len - 1;
        else ansa = len;
    }
    if (cntb + n <= len) ansb = cntb + n;
    else {
        if (n == 1 && cntb == len) ansb = len - 1;
        else ansb = len;
    }
    if (cntc + n <= len) ansc = cntc + n;
    else {
        if (n == 1 && cntc == len) ansc = len - 1;
        else ansc = len;
    }
    if (ansa > ansb && ansa > ansc) puts("Kuro");
    else if (ansb > ansa && ansb > ansc) puts("Shiro");
    else if (ansc > ansa && ansc > ansb) puts("Katie");
    else puts("Draw");
}
```
有不懂的可以直接问，一般情况下在线。

---

